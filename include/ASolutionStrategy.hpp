#pragma once

#include "ISolutionStrategy.h"

template <typename Result>
struct ASolutionStrategy : public ISolutionStrategy
{
    virtual CompareData compare(const TableMatches& expected, const Result& output, const cv::Mat& image) const = 0;
    virtual Result computeSolution(const cv::Mat& image) const = 0;

    SolutionExecutionData execute(const cv::Mat& image, const TableMatches& expected) const override
    {
        const std::chrono::time_point<std::chrono::system_clock> timerStart = std::chrono::system_clock::now();
        const Result output = this->computeSolution(image);
        const float executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - timerStart).count() / 1000.0;

        return SolutionExecutionData(ExecutionData(executionTime), this->compare(expected, output, image));
    }
};
