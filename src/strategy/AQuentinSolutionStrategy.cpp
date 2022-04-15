#include "../../include/strategy/AQuentinSolutionStrategy.h"

Type getColor(const std::string& color);

CompareData AQuentinSolutionStrategy::compare(TableMatches expected, SolutionBResult output) const
{
	// TD : Comparer expected et output

    int expectedCount = expected.cards.size();

    CompareData result{};

    for(int i = 0; i < expectedCount; ++i){
        auto currentCard = expected.cards[i];
        float matchRate = 0;

        auto found = std::find_if(output.cardsInImage.begin(), output.cardsInImage.end(), [currentCard] (const CardInImage& c) -> bool {
            return (int) getColor(c.card.cardColor) == (int) currentCard.cardType && (int) c.card.cardType == (int) currentCard.cardValue;
        });
        if(found != std::end(output.cardsInImage)){
            // found, check distance

            cv::Point2f centerExpected = (currentCard.pos1 + currentCard.pos2 + currentCard.pos3 + currentCard.pos4) / 4;
            auto outputEdges = found->positions;
            cv::Point2f centerOutput = (outputEdges[0] + outputEdges[1] + outputEdges[2] + outputEdges[3]) / 4;
            double distance = norm(centerOutput - centerExpected);
            if(distance < TOLERANCE_CENTER_DISTANCE){
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