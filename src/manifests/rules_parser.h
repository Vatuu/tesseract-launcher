#pragma once

#include <QJsonObject>
#include <QJsonArray>
#include <map>
#include <string>
#include <functional>
#include <utility>

#define RULES_DISALLOW(rules) rules.find("allow") != rules.cend() && !rules["allow"]

namespace Tesseract::Launcher {

    class AbstractRule {
    public:
        virtual void parseJson(QJsonObject& json) { };
        virtual bool evaluate() { return false; };
    };

    using ParserRegistry = std::map<QString, std::function<std::shared_ptr<AbstractRule>()>>;
    using RuleResults = std::map<QString, bool>;

    class RulesParser {
    private:
        static ParserRegistry createRuleParsers();
        bool checkRule(QString key, QJsonObject& obj);
    public:
        const ParserRegistry RULES_PARSERS = createRuleParsers();
        RuleResults parseRules(QJsonArray& array);
    };
}
