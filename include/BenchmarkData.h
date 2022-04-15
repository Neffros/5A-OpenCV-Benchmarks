#pragma once

#include <vector>

#include "../Annotator/src/TableMatches.h"
#include "SolutionData.h"

struct BenchmarkData
{
	std::vector<TableMatches> dataset;
	std::vector<SolutionData> solutions;

	BenchmarkData(std::vector<TableMatches> dataset, std::vector<SolutionData> solutions) : dataset(dataset), solutions(solutions) { }
};
