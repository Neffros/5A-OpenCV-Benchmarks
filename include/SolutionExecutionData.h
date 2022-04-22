#pragma once

#include "CompareData.h"
#include "ExecutionData.h"

#include <utility>

struct SolutionExecutionData
{
	CompareData comparison;
	ExecutionData performance;

	SolutionExecutionData(ExecutionData performance, CompareData comparison) : performance(performance), comparison(std::move(comparison)) { }

    nlohmann::json toJson() const
    {
        nlohmann::json result;

        result["comparison"] = this->comparison.toJson();
        result["performance"] = this->performance.toJson();

        return result;
    }
};
