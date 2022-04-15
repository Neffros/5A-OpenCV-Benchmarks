#include <iostream>

#include "../Annotator/src/TableMatches.h"
#include "../Annotator/src/DataSerializer.h"

#include "../include/strategy/BaseLiorSolutionStrategy.h"
#include "../include/strategy/BaseQuentinSolutionStrategy.h"

void benchmark()
{
	std::vector expectedTableMatches = {
		DataSerializer::readData("testData.json")
	};

	std::vector<std::shared_ptr<ISolutionStrategy>> strategies
	{
		std::make_shared<BaseLiorSolutionStrategy>(),
		std::make_shared<BaseQuentinSolutionStrategy>(),
	};

	for (auto tableMatches : expectedTableMatches)
	{
		for (auto strategy : strategies)
		{
			// benchmark solution
		}
	}
}

int main()
{
	return 0;
}