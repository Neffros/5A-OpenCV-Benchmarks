#pragma once

#include "../Annotator/src/TableMatches.h"

struct CardData
{
    float matchRate;
    Type type;
    Value value;

    CardData(Value value, Type type, float matchRate) : value(value), type(type), matchRate(matchRate) { }

    nlohmann::json toJson() const
    {
        nlohmann::json result;

        result["matchRate"] = (float)this->matchRate;
        result["type"] = (ushort)this->type;
        result["value"] = (ushort)this->value;

        return result;
    }
};