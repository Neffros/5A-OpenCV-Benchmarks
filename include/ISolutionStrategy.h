#pragma once

#include "CompareData.h"
#include "../Annotator/src/TableMatches.h"
#define TOLERANCE_CENTER_DISTANCE 10

struct ISolutionStrategy
{
    virtual CompareData execute(cv::Mat image, TableMatches expected) const = 0;
};
