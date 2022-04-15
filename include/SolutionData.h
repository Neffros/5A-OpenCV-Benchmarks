#pragma once

#include <string>
#include <vector>

#include "SolutionExecutionData.h"

struct SolutionData
{
	std::vector<SolutionExecutionData> benchmarks;
	std::string name;

	SolutionData(std::string name) : benchmarks(), name(name) { }

    nlohmann::json toJson() const
    {
        nlohmann::json result;

        auto benchmarks = nlohmann::json::array();

        for (auto& benchmark : this->benchmarks)
            benchmarks.push_back(benchmark.toJson());

        result["benchmarks"] = benchmarks;
        result["name"] = this->name;

        return result;
    }
};
