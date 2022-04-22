#pragma once

#include "../Annotator/src/TableMatches.h"

struct FalsePositiveCardData
{
    std::string imagePath;
    Type type;
    Value value;

    FalsePositiveCardData(
        const Value& value,
        const Type& type,
        const std::string& imagePath
    ) : imagePath(imagePath), type(type), value(value) { }

    nlohmann::json toJson() const
    {
        nlohmann::json result;

        result["type"] = (ushort) this->type;
        result["value"] = (ushort) this->value;

        return result;
    }
};