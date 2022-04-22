#include "../../include/strategy/AQuentinSolutionStrategy.h"
#include <iostream>

Type getColor(const std::string& color);

CompareData AQuentinSolutionStrategy::compare(TableMatches expected, SolutionBResult output) const
{
	// TD : Comparer expected et output

    int expectedCount = expected.cards.size();
    std::cout << "Solution Quentin FOUND " << output.cardsInImage.size() << " cards" << std::endl;

    CompareData result{};

    for (int i = 0; i < expectedCount; ++i) {
        auto currentCard = expected.cards[i];
        double matchRate = 0;

        cv::Point2f centerExpected =
                (currentCard.pos1 + currentCard.pos2 + currentCard.pos3 + currentCard.pos4) / 4;

        auto found = std::find_if(output.cardsInImage.begin(), output.cardsInImage.end(),
                                  [centerExpected](const CardInImage &c) -> bool {
                                      auto outputEdges = c.positions;
                                      cv::Point2f centerOutput = (outputEdges[0] + outputEdges[1] + outputEdges[2] + outputEdges[3]) / 4;
                                      double distance = norm(centerOutput - centerExpected);
                                      std::cout << distance << std::endl;
                                      return distance < TOLERANCE_CENTER_DISTANCE;
                                  });

        if (found != std::end(output.cardsInImage)) {
            const std::vector<std::string> colors = {
                "Clubs", "Spades", "Diamonds", "Hearts"
            };

            std::stringstream cardNameStream;
            cardNameStream << (int) currentCard.cardValue << colors[(int)currentCard.cardType];    // valeur -> couleur
            std::string cardName = cardNameStream.str();

            cardNameStream.str("");
            cardNameStream << (int) found->card.cardType << found->card.cardColor;
            std::string card2Name = cardNameStream.str();

            matchRate = similarityMap.at(cardName).at(card2Name);
            CardData cardData(currentCard.cardValue, currentCard.cardType, matchRate);
            result.existingCards.push_back(cardData);
        }
        else
        {
            //false positive
            FalsePositiveCardData cardData(currentCard.cardValue, currentCard.cardType);
            result.falsePositiveCards.push_back(cardData);
        }

    }

    // todo faux positifs
    return result;
}

Type getColor(const std::string& color){
    if(color == "Clubs"){
        return Type::Clubs;
    } else if(color == "Spades"){
        return Type::Spades;
    } else if(color == "Diamonds") {
        return Type::Diamonds;
    } else
        return Type::Hearts;
}