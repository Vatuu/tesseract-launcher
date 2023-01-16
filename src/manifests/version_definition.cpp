#include "version_definition.h"

#include "utils/os_utils.h"
#include "utils/json_utils.h"
#include "rules_parser.h"
#include <QJsonArray>
#include <QJsonObject>
#include <map>

namespace Tesseract::Launcher {

    std::string CLIArg::serialize() {
        return "--" + key + (value.has_value() ? " " + value.value() : "");
    }

    void VersionDefinition::parseJson(const QJsonDocument& doc) {
        mainClass = JsonUtils::jsonString(doc.object(), "mainClass");
        version =  JsonUtils::jsonString(doc.object(), "id");

        QJsonObject javaObj = doc.object()["javaVersion"].toObject();
        java = {
                .component =  JsonUtils::jsonString(javaObj, "component"),
                .majorVersion = static_cast<short>(javaObj["majorVersion"].toInt())};

        QJsonArray libs = doc.object()["libraries"].toArray();
        libraries = LibraryParser::parseEntries(rulesParser, libs);
    }
}




