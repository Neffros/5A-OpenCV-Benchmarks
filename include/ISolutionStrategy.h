#pragma once

#include "CompareData.h"
#include "../Annotator/src/TableMatches.h"

struct ISolutionStrategy
{
    virtual CompareData execute(cv::Mat image, TableMatches expected) const = 0;
    virtual std::string getName() const = 0;
};
