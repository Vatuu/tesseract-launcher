#include "library_parser.h"

#include "utils/json_utils.h"

namespace Tesseract::Launcher {

    MainJarEntry LibraryParser::parseJar(QJsonObject& json) {
        return {
                .hash = JsonUtils::jsonString(json, "sha1"),
                .fileSize = json["size"].toInt(),
                .url = JsonUtils::jsonString(json, "url")};
    }

    LibraryEntry LibraryParser::parseEntry(RulesParser& rulesParser, QJsonObject& json) {
        QJsonObject obj = json["downloads"].toObject()["artifact"].toObject();
        LibraryEntry entry = {
                .name = JsonUtils::jsonString(json, "name"),
                .path = JsonUtils::jsonString(obj, "path"),
                .hash = JsonUtils::jsonString(obj, "sha1"),
                .fileSize = obj["size"].toInt(),
                .url = JsonUtils::jsonString(obj, "url")
        };
        if(obj.contains("rules")) {
            QJsonArray ruleArray = obj["rules"].toArray();
            entry.rule = rulesParser.parseRules(ruleArray);
        }
        return entry;
    }

    std::vector<LibraryEntry> LibraryParser::parseEntries(RulesParser& rulesParser, QJsonArray& json) {
        std::vector<LibraryEntry> libs;
        for(const auto& ref : json) {
            QJsonObject obj = ref.toObject();
            libs.push_back(parseEntry(rulesParser, obj));
        }
        return libs;
    }

}



