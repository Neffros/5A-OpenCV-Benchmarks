#include "../../include/strategy/ALiorSolutionStrategy.h"

CompareData ALiorSolutionStrategy::compare(TableMatches expected, SolutionAResult output) const {
    // TD : Comparer expected et output

    int expectedCount = expected.cards.size();

    CompareData result{};

    std::cout << "Solution Lior FOUND " << output.cardsInImage.size() << " cards" << std::endl;

    for (int i = 0; i < expectedCount; ++i) {
        auto currentCard = expected.cards[i];
        double matchRate = 0;

        cv::Point2f centerExpected =
                (currentCard.pos1 + currentCard.pos2 + currentCard.pos3 + currentCard.pos4) / 4;

        auto found = std::find_if(output.cardsInImage.begin(), output.cardsInImage.end(),
                          [centerExpected, currentCard](const PokerCard &c) -> bool {
            auto outputEdges = c.tableEdges;
            cv::Point2f centerOutput = (outputEdges[0] + outputEdges[1] + outputEdges[2] + outputEdges[3]) / 4;
            double distance = norm(centerOutput - centerExpected);
            bool test = distance < TOLERANCE_CENTER_DISTANCE;
            return test;
        });


        /*auto found = std::find_if(output.cardsInImage.begin(), output.cardsInImage.end(),
                                  [currentCard](const PokerCard &c) -> bool {
                                      return (int) c.getType() == (int) currentCard.cardType &&
                                             (int) c.getValue() == (int) currentCard.cardValue;
                                  });*/
        bool testIt = found != output.cardsInImage.end();
        if (testIt) {
            // found, check distance

            /*auto outputEdges = found->getImageEdges();
            cv::Point2f centerOutput = (outputEdges[0] + outputEdges[1] + outputEdges[2] + outputEdges[3]) / 4;
            double distance = norm(centerOutput - centerExpected);
            if (distance < TOLERANCE_CENTER_DISTANCE) {
                if (distance == 0) matchRate = 1;
                else {
                    matchRate = TOLERANCE_CENTER_DISTANCE / distance;
                    matchRate = matchRate > 1 ? 1 : matchRate;
                }
            }*/

            const std::vector<std::string> colors = {
                "Clubs", "Spades", "Diamonds", "Hearts"
            };

            std::stringstream cardNameStream;
            cardNameStream << (int) currentCard.cardValue << colors.at((int)currentCard.cardType);    // valeur -> couleur
            std::string cardName = cardNameStream.str();

            cardNameStream.str("");
            cardNameStream << (int) found->getValue() << colors.at((int)found->getType());
            std::string card2Name = cardNameStream.str();

            matchRate = similarityMap.at(cardName).at(card2Name);
        }
        CardData cardData(currentCard.cardValue, currentCard.cardType, matchRate);
        result.existingCards.push_back(cardData);
    }

    // todo faux positifs
    return result;
}
