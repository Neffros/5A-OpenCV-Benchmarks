// Created by Quentin Pamart on 14/04/2022.

#include <iostream>
#include <opencv2/opencv.hpp>
#include "TableMatches.h"
#include "DataSerializer.h"

int main(int argc, char ** argv){
    TableMatches tableMatches;
    tableMatches.imageName = "UNE IMAGE";
    CardMatch card;
    card.cardValue = Value::Ace;
    card.cardType = Type::Diamonds;
    card.pos1 = cv::Point2f(0,1);
    card.pos2 = cv::Point2f(1,2);
    card.pos3 = cv::Point2f(2,5);
    card.pos4 = cv::Point2f(6,3);
    tableMatches.cards = std::vector<CardMatch>({
        card
    });

    DataSerializer::writeData("testData.json", tableMatches);
    TableMatches res = DataSerializer::readData("testData.json");

    return 0;
}