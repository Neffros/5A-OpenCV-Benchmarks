#pragma once

#include <vector>

#include "../Annotator/src/TableMatches.h"
#include "SolutionData.h"

struct BenchmarkData
{
    std::vector<SolutionData> solutions;
    std::vector<TableMatches> dataset;

	BenchmarkData(std::vector<TableMatches> dataset, std::vector<SolutionData> solutions) : dataset(dataset), solutions(solutions) { }

    nlohmann::json toJson() const
    {
        nlohmann::json result;

        auto solutions = nlohmann::json::array();

        for (auto& solution : this->solutions)
            solutions.push_back(solution.toJson());

        result["solutions"] = solutions;

        auto dataset = nlohmann::json::array();

        for (auto& matches : this->dataset)
            dataset.push_back(matches.toJson());

        result["dataset"] = dataset;

        return result;
    }
};
