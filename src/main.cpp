#include <iostream>

#include "../Annotator/src/TableMatches.h"
#include "../Annotator/src/DataSerializer.h"
#include "../include/strategy/BaseLiorSolutionStrategy.h"

void benchmark()
{
	std::vector expectedTableMatches = {
		DataSerializer::readData("testData.json")
	};

	BaseLiorSolutionStrategy liorStrategy;

	for (auto tableMatches : expectedTableMatches)
	{
		// benchmark each solution
	}
}

int main()
{
	return 0;
}