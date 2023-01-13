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

    bool RulesParser::checkRule(QString key, QJsonObject& obj) {
        if(!RULES_PARSERS.contains(key))
            return false;
        std::shared_ptr<AbstractRule> rule = RULES_PARSERS.at(key)();
        rule->parseJson(obj);
        return rule->evaluate();
    }

    RuleResults RulesParser::parseRules(QJsonArray& array) {
        RuleResults actions;
        for(const QJsonValueConstRef& ref : array) {
            QJsonObject obj = ref.toObject();
            bool rulesPassed = true;
            for(const QString& key : obj.keys()) {
                if(key == "action")
                    continue;
                QJsonObject ruleObj = obj[key].toObject();
                if(!(rulesPassed = checkRule(key, ruleObj)))
                    break;
            }
            actions[obj["action"].toString()] = rulesPassed;
        }
        return actions;
    }
}