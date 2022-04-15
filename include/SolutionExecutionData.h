#pragma once

#include "CompareData.h"
#include "ExecutionData.h"

struct SolutionExecutionData
{
	CompareData comparison;
	ExecutionData performance;

	SolutionExecutionData(ExecutionData performance, CompareData comparison) : performance(performance), comparison(comparison) { }

    nlohmann::json toJson() const
    {
        nlohmann::json result;

        result["comparison"] = this->comparison.toJson();
        result["performance"] = this->performance.toJson();

        return result;
    }
};
