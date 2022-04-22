#include "../../include/strategy/AQuentinSolutionStrategy.h"
#include <iostream>

Type getColor(const std::string& color)
{
	if (color == "Clubs")
		return Type::Clubs;
	else if (color == "Spades")
		return Type::Spades;
	else if (color == "Diamonds")
		return Type::Diamonds;
	else
		return Type::Hearts;
}

struct CompareCardInImage
{
	const CardInImage& card;
	CompareCardInImage(const CardInImage& card) : card(card) {}

	bool operator()(const CardInImage& foundCard)
	{
		return card.card.cardColor == foundCard.card.cardColor
			&& card.card.cardType == foundCard.card.cardType
			&& card.positions == foundCard.positions;
	}
};

std::vector<CardInImage> findFalsePositiveCards(const std::vector<CardInImage>& cardsInImage, const std::vector<CardInImage>& foundCards)
{
	std::vector<CardInImage> falsePositiveCards;

	for (const auto& card : cardsInImage)
	{
		if (!std::any_of(
			foundCards.begin(),
			foundCards.end(),
			CompareCardInImage(card)
		))
			falsePositiveCards.push_back(card);
	}

	return falsePositiveCards;
}

CompareData AQuentinSolutionStrategy::compare(const TableMatches& expected, const SolutionBResult& output, const cv::Mat& image) const
{
	std::cout << "Solution Quentin FOUND " << output.cardsInImage.size() << " cards" << std::endl;

	CompareData result;
	std::vector<CardInImage> foundCards;

	for (const CardMatch& currentCard : expected.cards)
	{
		const cv::Point2f centerExpected = (currentCard.pos1 + currentCard.pos2 + currentCard.pos3 + currentCard.pos4) / 4;
		const auto& found = std::find_if(
			output.cardsInImage.begin(),
			output.cardsInImage.end(),
			[&centerExpected](const CardInImage& c) -> bool {
				const auto& outputEdges = c.positions;
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
			cardNameStream << (int)found->card.cardType << found->card.cardColor;
			std::string card2Name = cardNameStream.str();

			matchRate = similarityMap.at(cardName).at(card2Name);

			foundCards.push_back(*found);
		}

		CardData cardData(currentCard.cardValue, currentCard.cardType, currentCard.characteristics, matchRate);
		result.existingCards.push_back(cardData);
	}

	for (const auto& falsePositiveCard : findFalsePositiveCards(output.cardsInImage, foundCards))
		result.falsePositiveCards.push_back(FalsePositiveCardData((Value)falsePositiveCard.card.cardType, getColor(falsePositiveCard.card.cardColor), image, falsePositiveCard.positions));

	return result;
}