#include "TableMatches.h"

TableMatches TableMatches::fromJson(const nlohmann::json& data) {
    TableMatches result;
    result.imagePath = data["imagePath"];
    result.cards = std::vector<CardMatch>();

    for(auto& card : data["cards"]){
        CardMatch cardObj;
        cardObj.cardType = (Type) card["type"];
        cardObj.cardValue = (Value) card["value"];
        auto characteristics = card["characteristics"];
        for(const auto& characteristic : characteristics)
        {
            cardObj.characteristics.push_back((Characteristics)characteristic);
        }
        auto points = card["points"];
        cardObj.pos1 = cv::Point2f(points[0][0], points[0][1]); // 0 -> x ; 1 -> y
        cardObj.pos2 = cv::Point2f(points[1][0], points[1][1]);
        cardObj.pos3 = cv::Point2f(points[2][0], points[2][1]);
        cardObj.pos4 = cv::Point2f(points[3][0], points[3][1]);
        result.cards.push_back(cardObj);
    }

    return result;
}

nlohmann::json TableMatches::toJson() const
{
    nlohmann::json result;

    result["imagePath"] = imagePath;
    auto cardsArray = nlohmann::json::array();
    for(auto& card : cards){
        auto cardObject = nlohmann::json::object();
        auto characteristicsArray = nlohmann::json::array();
        cardObject["type"] = (ushort) card.cardType;
        cardObject["value"] = (ushort) card.cardValue;
        auto pointsArray = nlohmann::json::array({
            {card.pos1.x, card.pos1.y},
            {card.pos2.x, card.pos2.y},
            {card.pos3.x, card.pos3.y},
            {card.pos4.x, card.pos4.y},
        });
        for(auto characteristic: card.characteristics)
        {
            characteristicsArray.push_back(characteristic);
        }
        cardObject["characteristics"] = characteristicsArray;
        cardObject["points"] = pointsArray;
        cardsArray.push_back(cardObject);
    }
    result["cards"] = cardsArray;

    return result;
}
