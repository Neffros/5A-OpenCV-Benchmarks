#pragma once

#include "../Annotator/src/TableMatches.h"

struct FalsePositiveCardData
{
    Type type;
    Value value;

    FalsePositiveCardData(Value value, Type type) : value(value), type(type) { }

    nlohmann::json toJson() const
    {
        nlohmann::json result;

        result["type"] = (ushort) this->type;
        result["value"] = (ushort) this->value;

        return result;
    }
};