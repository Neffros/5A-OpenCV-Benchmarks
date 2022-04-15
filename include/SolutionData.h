#pragma once

#include <string>
#include <vector>

#include "SolutionExecutionData.h"

struct SolutionData
{
	std::vector<SolutionExecutionData> benchmarks;
	std::string name;

	SolutionData(std::string name) : benchmarks(), name(name) { }
};
