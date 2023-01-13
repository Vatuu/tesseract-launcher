#pragma once

#include <string>
#include <map>
#include <qsystemdetection.h>

namespace Tesseract::Launcher {

    class OSUtils {
    private:
        static const inline std::map<QString, QString> OS_MAP = { {"darwin", "osx"}, {"winnt", "windows"} };
        static const inline std::map<QString, QString> ARCH_MAP = { {"i186", "x86"}, {"x86_64", "x64"} };
    public:
        static QString getOSName() {
            QString kernel = QSysInfo::kernelType();
            if(OS_MAP.contains(kernel)) {
                return OS_MAP.at(kernel);
            }
            return kernel;
        }

        static QString getOSArchitecture() {
            QString arch = QSysInfo::currentCpuArchitecture();
            if(ARCH_MAP.contains(arch)) {
                return ARCH_MAP.at(arch);
            }
            return arch;
        }

        static QString getOSVersion() {
            return QSysInfo::productVersion();
        }
    };
}