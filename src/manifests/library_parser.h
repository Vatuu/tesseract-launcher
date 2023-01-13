#pragma once

#include "rules_parser.h"

#include <string>
#include <QJsonObject>

namespace Tesseract::Launcher {

    struct LibraryEntry {
        ManifestRule rule;
        std::string name, path, hash;
        long fileSize;
        std::string url;
    };

    struct MainJarEntry {
        std::string hash;
        long fileSize;
        std::string url;
    };

    class LibraryParser {
    private:
        static LibraryEntry parseEntry(QJsonObject& json);
    public:
        static std::vector<LibraryEntry> parseEntries(RulesParser& ruleParser, QJsonArray& json);
        static MainJarEntry parseJar(QJsonObject& json);
    };
}