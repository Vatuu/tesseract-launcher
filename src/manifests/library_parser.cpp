#include "library_parser.h"

#include "utils/json_utils.h"

namespace Tesseract::Launcher {

    MainJarEntry LibraryParser::parseJar(QJsonObject& json) {
        return {
                .hash = JsonUtils::jsonString(json, "sha1"),
                .fileSize = json["size"].toInt(),
                .url = JsonUtils::jsonString(json, "url")};
    }

    LibraryEntry LibraryParser::parseEntry(QJsonObject& json) {
        QJsonObject obj = json["downloads"].toObject()["artifact"].toObject();
        return {
                .name = JsonUtils::jsonString(json, "name"),
                .path = JsonUtils::jsonString(obj, "path"),
                .hash = JsonUtils::jsonString(obj, "sha1"),
                .fileSize = obj["size"].toInt(),
                .url = JsonUtils::jsonString(obj, "url")
        };
    }

    std::vector<LibraryEntry> LibraryParser::parseEntries(RulesParser& rulesParser, QJsonArray& json) {
        std::vector<LibraryEntry> libs;
        for(const auto& ref : json) {
            QJsonObject obj = ref.toObject();
            if(json.contains("rules")) {
                RuleResults rules = rulesParser.parseRules(obj["rules"].toArray());
                if(RULES_DISALLOW(rules)) continue;
            }
            libs.push_back(parseEntry(obj));
        }
        return libs;
    }

}



