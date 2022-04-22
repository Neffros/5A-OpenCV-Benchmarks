#pragma once

#include "../Annotator/src/TableMatches.h"
#include <opencv2/imgcodecs.hpp>

struct FalsePositiveCardData
{
    static int i;

    std::string imagePath;
    Type type;
    Value value;

    FalsePositiveCardData(
        const Value& value,
        const Type& type,
        const cv::Mat& tableImage,
        const std::vector<cv::Point2f>& positions
    ) : type(type), value(value)
    {
        this->imagePath = FalsePositiveCardData::generateCardImage(tableImage, positions);
    }

    nlohmann::json toJson() const
    {
        nlohmann::json result;

        result["imagePath"] = this->imagePath;
        result["type"] = (ushort) this->type;
        result["value"] = (ushort) this->value;

        return result;
    }

private:
    static std::string generateCardImage(const cv::Mat& tableImage, const std::vector<cv::Point2f>& positions)
    {
        cv::Point2f max(positions[0]);
        cv::Point2f min(positions[0]);

        for (const auto& position : positions)
        {
            min.x = std::min(min.x, position.x);
            min.y = std::min(min.y, position.y);
            max.x = std::max(max.x, position.x);
            max.y = std::max(max.y, position.y);
        }

        const cv::Mat cardImage = tableImage(cv::Rect(min.x, min.y, max.x - min.x, max.y - min.y));
        const std::string path = "./false_positives/" + std::to_string(i++) + ".jpg";

        cv::imwrite(path, cardImage);

        return path;
    }
};
