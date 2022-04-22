#pragma once

#include "../Annotator/src/TableMatches.h"

struct CardData
{
    std::vector<Characteristics> characteristics;
    float matchRate;
    Type type;
    Value value;

    CardData(
        const Value& value,
        const Type& type,
        const std::vector<Characteristics>& characteristics,
        const float& matchRate
    ) : characteristics(characteristics), matchRate(matchRate), type(type), value(value) { }

    nlohmann::json toJson() const
    {
        nlohmann::json result;

        auto characteristics = nlohmann::json::array();
        
        for (auto characteristic : this->characteristics)
            characteristics.push_back(characteristic);

        result["characteristics"] = characteristics;
        result["matchRate"] = (float)this->matchRate;
        result["type"] = (ushort)this->type;
        result["value"] = (ushort)this->value;

        return result;
    }
};