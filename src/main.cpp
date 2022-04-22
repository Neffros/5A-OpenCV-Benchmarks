#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

#include "../Annotator/src/TableMatches.h"
#include "../Annotator/src/DataSerializer.h"

#include "../include/BenchmarkData.h"

#include "../include/strategy/BaseLiorSolutionStrategy.h"
#include "../include/strategy/BaseQuentinSolutionStrategy.h"

std::map<std::string, std::map<std::string, double>> createSimilarityMap()
{
    static const std::vector<int> cardTypes = { 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2 };
    static const std::vector<std::string> colors = { "Clubs", "Spades", "Diamonds", "Hearts" };

    const cv::Mat cardsAtlas = cv::imread("resources/cards.jpg");
    const int width = cardsAtlas.cols / 4;
    const int height = cardsAtlas.rows / 13;
    
    std::map<std::string, std::map<std::string, double>> similarityMap;
    cv::Mat card;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 13; ++j)
        {
            card = cardsAtlas(cv::Rect(i * width + 5, j * height + 5, width - 5, height - 5));
            cv::Mat tmp;
            cv::cvtColor(card, tmp, cv::COLOR_BGR2GRAY);

            card = tmp;
            cv::resize(tmp, card, cv::Size(width * 2, height * 2));

            Card newCard(card, cardTypes[j], colors[i]);

            std::stringstream cardNameStream;
            cardNameStream << cardTypes[j] << colors[i];
            std::string cardName = cardNameStream.str();

            cv::Mat hist1Mat, hist2Mat;

            for (int k = 0; k < colors.size(); ++k)
            {
                for (int l = 0; l < cardTypes.size(); ++l)
                {
                    card = cardsAtlas(cv::Rect(k * width + 5, l * height + 5, width - 5, height - 5));
                    cv::cvtColor(card, tmp, cv::COLOR_BGR2GRAY);

                    card = tmp;
                    cv::resize(tmp, card, cv::Size(width * 2, height * 2));
                    cardNameStream.str("");
                    cardNameStream << cardTypes[l] << colors[k];
                    std::string card2Name = cardNameStream.str();

                    cv::Mat res;
                    cv::absdiff(newCard.data, card, res);
                    res.convertTo(res, CV_8UC1);

                    res = res.reshape(1, res.total() * res.channels());
                    std::vector<uchar> vec = res.isContinuous() ? res : res.clone();

                    similarityMap[cardName][card2Name] = 1 - static_cast<double>(std::count_if(vec.begin(), vec.end(), [](int i) { return i > 10; })) / (vec.size());
                }
            }
        }
    }

    return similarityMap;
}

BenchmarkData benchmark(
	const std::vector<TableMatches>& expectedTableMatches,
	const std::vector<std::shared_ptr<ISolutionStrategy>>& solutions
)
{
    std::cout << "Reading cards atlas..." << std::endl;

    auto similarityMap = createSimilarityMap();

    std::cout << "Done, starting benchmark..." << std::endl;

    std::vector<SolutionData> solutionResults;
    solutionResults.reserve(solutions.size());

	for (const std::shared_ptr<ISolutionStrategy>& solution : solutions)
    {
        solution->similarityMap = similarityMap;
        solutionResults.push_back(SolutionData(solution->getName()));
    }

	for (TableMatches tableMatches : expectedTableMatches)
	{
		const cv::Mat image = cv::imread(tableMatches.imagePath);

		for (int i = 0; i < solutions.size(); ++i)
            solutionResults[i].benchmarks.push_back(solutions[i]->execute(image, tableMatches));
	}

    return BenchmarkData(expectedTableMatches, solutionResults);
}

void writeJSON(const nlohmann::json& data, const std::string& filePath)
{
	std::ofstream file;

	file.open(filePath);
	file << data << std::endl;
	file.close();
}

int main()
{
    // TODO : Add Benchmarker class

	const std::vector<TableMatches> expectedTableMatches = {
		DataSerializer::readData("testData.json")
	};

	const std::vector<std::shared_ptr<ISolutionStrategy>> solutions
	{
		std::make_shared<BaseLiorSolutionStrategy>(),
		std::make_shared<BaseQuentinSolutionStrategy>(),
	};

	writeJSON(benchmark(expectedTableMatches, solutions).toJson(), "testGraph.json");

	return 0;
}