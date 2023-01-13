#pragma once

#include "library_parser.h"
#include "argument_parser.h"
#include "rules_parser.h"

#include <string>
#include <optional>
#include <utility>
#include <vector>

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace Tesseract::Launcher {

    enum ReleaseType { RELEASE, SNAPSHOT, OLD_BETA, OLD_ALPHA };

    struct JavaVersion {
        std::string component;
        short majorVersion;
    };

    class CLIArg {
    private:
        std::string key;
        std::optional<std::string> value;
    public:
        explicit CLIArg(std::string key, std::optional<std::string> value = std::nullopt) : key(std::move(key)), value(std::move(value)) { };
        std::string serialize();
    };

    struct StartingArgs {
        std::vector<CLIArg> game, jvm;
    };

    class VersionDefinition {

    private:
        RulesParser rulesParser;
        LibraryParser libraryParser;

    public:
        std::string mainClass, version;
        ReleaseType releaseType;
        JavaVersion java;
        StartingArgs args;
        MainJarEntry client, server;
        std::vector<LibraryEntry> libraries;
        QDateTime releaseTime;

        VersionDefinition(QByteArrayView jsonData);
        void parseJson(const QJsonDocument& doc);
    };


}