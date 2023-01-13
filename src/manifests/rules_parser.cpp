#include <memory>
#include <regex>

#include "rules_parser.h"
#include "utils/os_utils.h"
#include "utils/json_utils.h"

namespace Tesseract::Launcher {

    class OSRule : public AbstractRule {
    private:
        std::optional<QString> name, architecture, version;
    public:
        void parseJson(QJsonObject &json) override {
            name = JsonUtils::optional<QString>(json, "name");
            architecture = JsonUtils::optional<QString>(json, "arch");
            version = JsonUtils::optional<QString>(json, "version");
        }

        bool evaluate() override {
            if(name.has_value() && name.value() != OSUtils::getOSName())
                return false;
            if(architecture.has_value() && architecture.value() != OSUtils::getOSArchitecture())
                return false;
            if(version.has_value() && QRegularExpression(version.value()).match(OSUtils::getOSVersion()).hasMatch())
                return false;
            return true;
        }
    };

    ParserRegistry RulesParser::createRuleParsers() {
        ParserRegistry parsers;
        parsers["os"] = []() { return std::shared_ptr<AbstractRule>(new OSRule()); };
        return parsers;
    }

    RuleSet RulesParser::parseRules(QJsonArray& array) {
        RuleSet set;
        for(const QJsonValueConstRef& ref : array) {
            QJsonObject rule = ref.toObject();
            std::vector<std::shared_ptr<AbstractRule>> rules;
            for(const QString& key : rule.keys()) {
                if(key == "action")
                    continue;
                QJsonObject ruleObj = rule[key].toObject();
                if(!RULES_PARSERS.contains(key)) {
                    rules.push_back(std::make_shared<AbstractRule>());
                    //TODO Throw unknown rule
                    continue;
                }
                std::shared_ptr<AbstractRule> rulePtr = RULES_PARSERS.at(key)();
                rulePtr->parseJson(ruleObj);
                rules.push_back(rulePtr);
            }
            ManifestRule manifestRule = {
                    .action = rule["action"].toString(),
                    .rules = rules};
            set.push_back(manifestRule);
        }
        return set;
    }

    RuleResults RulesParser::evaluateRules(RuleSet &rules) {
        RuleResults actions;
        for(const auto& rule : rules) {
            bool rulesPassed = true;
            for(const auto& condition : rule.rules) {
                if(!(rulesPassed = condition->evaluate()))
                    break;
            }
            actions[rule.action] = rulesPassed;
        }
        return actions;
    }
}