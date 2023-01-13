#pragma once

#include <map>
#include <optional>
#include <QJsonObject>

namespace Tesseract::Launcher {

    class JsonUtils {
    public:
        static inline std::string jsonString(QJsonObject obj, const QString& key) {
            return obj[key].toString().toStdString();
        }

        template<typename T>
        static inline std::optional<T> optional(QJsonObject& obj, std::string key) {
            if(obj.contains(QString::fromStdString(key)))
                return std::nullopt;
            QVariant var = obj[QString::fromStdString(key)].toVariant();
            if(!var.canConvert<T>())
                return std::nullopt;
            return var.value<T>();
        }
    };
}