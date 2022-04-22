#pragma once

#include "SolutionExecutionData.h"
#include "../Annotator/src/TableMatches.h"

constexpr auto TOLERANCE_CENTER_DISTANCE = 100;

struct ISolutionStrategy
{
    virtual SolutionExecutionData execute(cv::Mat image, TableMatches expected) const = 0;
    virtual std::string getName() const = 0;

    std::map<std::string, std::map<std::string, double>> similarityMap;
};
