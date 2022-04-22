#include "../../include/strategy/ALiorSolutionStrategy.h"

struct ComparePokerCard
{
	const PokerCard& card;
	ComparePokerCard(const PokerCard& card) : card(card) {}

	bool operator()(const PokerCard& foundCard)
	{
		return card.getType() == foundCard.getType()
			&& card.getValue() == foundCard.getValue()
			&& card.tableEdges == foundCard.tableEdges;
	}
};

// TODO : Generalize with templating and comparator as parameter

std::vector<PokerCard> findFalsePositiveCards(const std::vector<PokerCard>& cardsInImage, const std::vector<PokerCard>& foundCards)
{
	std::vector<PokerCard> falsePositiveCards;

	for (const auto& card : cardsInImage)
	{
		if (!std::any_of(
			foundCards.begin(),
			foundCards.end(),
			ComparePokerCard(card)
		))
			falsePositiveCards.push_back(card);
	}

	return falsePositiveCards;
}

CompareData ALiorSolutionStrategy::compare(const TableMatches& expected, const SolutionAResult& output, const cv::Mat& image) const
{
    std::cout << "Solution Lior FOUND " << output.cardsInImage.size() << " cards" << std::endl;

	CompareData result{};
	std::vector<PokerCard> foundCards;

	for (const CardMatch& currentCard : expected.cards)
	{
		const cv::Point2f centerExpected = (currentCard.pos1 + currentCard.pos2 + currentCard.pos3 + currentCard.pos4) / 4;
		const auto& found = std::find_if(
			output.cardsInImage.begin(),
			output.cardsInImage.end(),
			[&centerExpected](const PokerCard& c) -> bool {
				const auto& outputEdges = c.tableEdges;
				const cv::Point2f centerOutput = (outputEdges[0] + outputEdges[1] + outputEdges[2] + outputEdges[3]) / 4;
				const double distance = norm(centerOutput - centerExpected);

				std::cout << distance << std::endl;

				return distance < TOLERANCE_CENTER_DISTANCE;
			}
		);

		double matchRate = 0;

		if (found != std::end(output.cardsInImage)) {
			static const std::vector<std::string> colors = { "Clubs", "Spades", "Diamonds", "Hearts" };

			std::stringstream cardNameStream;
			cardNameStream << (int)currentCard.cardValue << colors[(int)currentCard.cardType]; // valeur -> couleur
			std::string cardName = cardNameStream.str();

			cardNameStream.str("");
			cardNameStream << (int)found->getType() << (int)found->getValue();
			std::string card2Name = cardNameStream.str();

			matchRate = similarityMap.at(cardName).at(card2Name);

			foundCards.push_back(*found);
		}

		CardData cardData(currentCard.cardValue, currentCard.cardType, currentCard.characteristics, matchRate);
		result.existingCards.push_back(cardData);
	}

	for (const auto& falsePositiveCard : findFalsePositiveCards(output.cardsInImage, foundCards))
		result.falsePositiveCards.push_back(FalsePositiveCardData((Value)falsePositiveCard.getValue(), (Type)falsePositiveCard.getType(), image, falsePositiveCard.tableEdges));

    return result;
}
