#pragma once

#include "CardData.h"
#include "FalsePositiveCardData.h"

struct CompareData
{
	std::vector<CardData> existingCards;
	std::vector<FalsePositiveCardData> falsePositiveCards;

    nlohmann::json toJson() const
    {
        nlohmann::json result;
        auto existingCards = nlohmann::json::array();
        auto falsePositiveCards = nlohmann::json::array();

        for (auto& card : this->existingCards)
            existingCards.push_back(card.toJson());

        for (auto& card : this->falsePositiveCards)
            falsePositiveCards.push_back(card.toJson());

        result["existingCards"] = existingCards;
        result["falsePositiveCards"] = falsePositiveCards;

        return result;
    }
};
