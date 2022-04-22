#pragma once

#include "CompareData.h"
#include "../Annotator/src/TableMatches.h"
#define TOLERANCE_CENTER_DISTANCE 100

struct ISolutionStrategy
{
    virtual CompareData execute(cv::Mat image, TableMatches expected) const = 0;
    virtual std::string getName() const = 0;

    std::map<std::string, std::map<std::string, double>> similarityMap;
};
