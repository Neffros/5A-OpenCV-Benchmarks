#pragma once

#include "ISolutionStrategy.h"

template <typename Result>
struct ASolutionStrategy : public ISolutionStrategy
{
    virtual CompareData compare(TableMatches expected, Result output) const = 0;
    virtual Result computeSolution(cv::Mat image) const = 0;

    SolutionExecutionData execute(cv::Mat image, TableMatches expected) const override
    {
        std::chrono::time_point<std::chrono::system_clock> timerStart = std::chrono::system_clock::now();
        Result output = this->computeSolution(image);
        float executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - timerStart).count() / 1000.0;

        return SolutionExecutionData(ExecutionData(executionTime), this->compare(expected, output));
    }
};
