#include <iostream>
#include <fstream>

#include "../Annotator/src/TableMatches.h"
#include "../Annotator/src/DataSerializer.h"

#include "../include/BenchmarkData.h"

#include "../include/strategy/BaseLiorSolutionStrategy.h"
#include "../include/strategy/BaseQuentinSolutionStrategy.h"

SolutionExecutionData benchmarkImageSolution(
	const std::shared_ptr<ISolutionStrategy>& strategy,
	const cv::Mat& image,
	const TableMatches& expectedMatches
)
{
	// TODO: add chrono for execution data

	return SolutionExecutionData(ExecutionData(0.1f), strategy->execute(image, expectedMatches));
}

BenchmarkData benchmark(
	const std::vector<TableMatches>& expectedTableMatches,
	const std::vector<std::shared_ptr<ISolutionStrategy>>& strategies
)
{
	std::vector<SolutionData> solutions;

    std::cout << "Reading cards atlas..." << std::endl;
    cv::Mat cardsAtlas = cv::imread("resources/cards.jpg");

    // building atlas similarities
    std::map<std::string, std::map<std::string, double>> similarityMap;
    {
        const std::vector<int> cardTypes = {
            14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2
        };
        const std::vector<std::string> colors = {
            "Clubs", "Spades", "Diamonds", "Hearts"
        };

        int width = cardsAtlas.cols / 4;
        int height = cardsAtlas.rows / 13;

        cv::Mat card;
        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 13; ++j){
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

                for(int i2 = 0; i2 < 4; ++i2){
                    for(int j2 = 0; j2 < 13; ++j2){
                        card = cardsAtlas(cv::Rect(i2 * width + 5, j2 * height + 5, width - 5, height - 5));
                        cv::cvtColor(card, tmp, cv::COLOR_BGR2GRAY);

                        card = tmp;
                        cv::resize(tmp, card, cv::Size(width * 2, height * 2));
                        cardNameStream.str("");
                        cardNameStream << cardTypes[j2] << colors[i2];
                        std::string card2Name = cardNameStream.str();

                        cv::Mat res;
                        cv::absdiff(newCard.data, card, res);
                        res.convertTo(res, CV_8UC1);

                        res = res.reshape(1, res.total() * res.channels());
                        std::vector<uchar> vec = res.isContinuous() ? res : res.clone();

                        double matchRate = 1-static_cast<double>(std::count_if(vec.begin(), vec.end(),
                                              [] (int i) { return i > 10; })) / (vec.size());

                        //double matchRate = 1-cv::norm(newCard.data, card, cv::NORM_L2);

                        similarityMap[cardName][card2Name] = matchRate;
                    }
                }
            }
        }
    }

    std::cout << "Done, starting benchmark..." << std::endl;

	solutions.reserve(strategies.size());

	for (const std::shared_ptr<ISolutionStrategy>& strategy : strategies) {
        strategy->similarityMap = similarityMap;
        solutions.push_back(SolutionData(strategy->getName()));
    }

	BenchmarkData graph(expectedTableMatches, solutions);

	for (TableMatches tableMatches : expectedTableMatches)
	{
		const cv::Mat image = cv::imread(tableMatches.imagePath);

		for (int i = 0; i < strategies.size(); ++i)
			graph.solutions[i].benchmarks.push_back(benchmarkImageSolution(strategies[i], image, tableMatches));
	}

	return graph;
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
	std::vector<TableMatches> expectedTableMatches = {
		DataSerializer::readData("testData.json")
	};

	std::vector<std::shared_ptr<ISolutionStrategy>> strategies
	{
		std::make_shared<BaseLiorSolutionStrategy>(),
		std::make_shared<BaseQuentinSolutionStrategy>(),
	};

	BenchmarkData data = benchmark(expectedTableMatches, strategies);

	writeJSON(data.toJson(), "testGraph.json");

	return 0;
}