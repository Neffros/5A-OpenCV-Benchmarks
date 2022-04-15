#include "../../include/strategy/ALiorSolutionStrategy.h"

CompareData ALiorSolutionStrategy::compare(TableMatches expected, SolutionAResult output) const {
    // TD : Comparer expected et output

    int expectedCount = expected.cards.size();

    CompareData result{};

    for (int i = 0; i < expectedCount; ++i) {
        auto currentCard = expected.cards[i];
        float matchRate = 0;

        auto found = std::find_if(output.cardsInImage.begin(), output.cardsInImage.end(),
                                  [currentCard](const PokerCard &c) -> bool {
                                      return (int) c.getType() == (int) currentCard.cardType &&
                                             (int) c.getValue() == (int) currentCard.cardValue;
                                  });
        if (found != std::end(output.cardsInImage)) {
            // found, check distance

            cv::Point2f centerExpected =
                    (currentCard.pos1 + currentCard.pos2 + currentCard.pos3 + currentCard.pos4) / 4;
            auto outputEdges = found->getImageEdges();
            cv::Point2f centerOutput = (outputEdges[0] + outputEdges[1] + outputEdges[2] + outputEdges[3]) / 4;
            double distance = norm(centerOutput - centerExpected);
            if (distance < TOLERANCE_CENTER_DISTANCE) {
                if (distance == 0) matchRate = 1;
                else {
                    matchRate = TOLERANCE_CENTER_DISTANCE / distance;
                    matchRate = matchRate > 1 ? 1 : matchRate;
                }
            }
        }
        CardData cardData(currentCard.cardValue, currentCard.cardType, matchRate);
        result.existingCards.push_back(cardData);
    }

    // todo faux positifs
    return result;
}
