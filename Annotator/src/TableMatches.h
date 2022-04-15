#pragma once

#include <string>
#include "opencv2/core/types.hpp"
#include "../../json/single_include/nlohmann/json.hpp"


enum class Type : unsigned short {
    Clubs = 0,
    Spades = 1,
    Diamonds = 2,
    Hearts = 3
};

enum class Value : unsigned short{
    Ace = 14,
    King = 13,
    Queen = 12,
    Jack = 11,
    Ten = 10,
    Nine = 9,
    Eight = 8,
    Seven = 7,
    Six = 6,
    Five = 5,
    Four = 4,
    Three = 3,
    Two = 2
};

struct CardMatch {
    Value cardValue;
    Type cardType;

    cv::Point2f pos1;
    cv::Point2f pos2;
    cv::Point2f pos3;
    cv::Point2f pos4;
};

class TableMatches {
public:
    std::string imagePath;
    std::vector<Card> cards;

    nlohmann::json toJson();
    static TableMatches fromJson(const nlohmann::json& data);

    TableMatches() = default;
};


