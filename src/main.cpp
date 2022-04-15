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

	std::vector<ISolutionStrategy*> strategies
	{
		new BaseLiorSolutionStrategy(),
		new BaseQuentinSolutionStrategy(),
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