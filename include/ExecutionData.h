#pragma once

struct ExecutionData
{
	float executionTime;

	ExecutionData(float executionTime) : executionTime(executionTime) { }

    nlohmann::json toJson() const
    {
        nlohmann::json result;

        result["executionTime"] = this->executionTime;

        return result;
    }
};
