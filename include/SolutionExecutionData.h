#pragma once

#include "CompareData.h"
#include "ExecutionData.h"

struct SolutionExecutionData
{
	ExecutionData benchmark;
	CompareData match;

	SolutionExecutionData(ExecutionData benchmark, CompareData match) : benchmark(benchmark), match(match) { }
};
