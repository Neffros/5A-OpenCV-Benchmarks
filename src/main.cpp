#include <iostream>

#include "../Annotator/src/TableMatches.h"
#include "../Annotator/src/DataSerializer.h"

#include "../include/BenchmarkData.h"

#include "../include/strategy/BaseLiorSolutionStrategy.h"
#include "../include/strategy/BaseQuentinSolutionStrategy.h"

SolutionExecutionData benchmarkImageSolution(std::shared_ptr<ISolutionStrategy> strategy, cv::Mat image, TableMatches expectedMatches)
{
	// TODO: add chrono for execution data

	return SolutionExecutionData(ExecutionData(0.1f), strategy->execute(image, expectedMatches));
}

BenchmarkData benchmark(
	std::vector<TableMatches> expectedTableMatches,
	std::vector<std::shared_ptr<ISolutionStrategy>> strategies
)
{
	std::vector<SolutionData> solutions;

	solutions.reserve(strategies.size());

	for (std::shared_ptr<ISolutionStrategy> strategy : strategies)
		solutions.push_back(SolutionData(strategy->getName()));

	BenchmarkData graph(expectedTableMatches, solutions);

	for (TableMatches tableMatches : expectedTableMatches)
	{
		cv::Mat image = cv::imread(tableMatches.imagePath);

		for (int i = 0; i < strategies.size(); ++i)
			graph.solutions[i].benchmarks.push_back(benchmarkImageSolution(strategies[i], image, tableMatches));
	}
	
	return graph;
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

	DataSerializer::writeData("test.json", data);

	return 0;
}