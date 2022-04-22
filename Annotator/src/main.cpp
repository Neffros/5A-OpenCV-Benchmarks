#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "TableMatches.h"
#include "DataSerializer.h"

std::vector<std::vector<cv::Point>> cardPositions;
int currentIndex = 0;

std::vector<cv::Point> roiPoints;
std::vector<std::string> cardDefinitions;
std::string name;
bool inputCardName = false;

const std::map< std::string, unsigned short> cardTypes = {
        {"clubs", 0},
        {"spades", 1},
        {"diamonds",2},
        {"hearts", 3},
};

const std::map<std::string, unsigned short> cardValues = {

        { "two",2},
        { "three",3},
        {"four", 4},
        {"five", 5},
        {"six", 6 },
        {"seven", 7},
        {"eight", 8},
        {"nine",9},
        { "ten",10},
        { "jack",11},
        { "queen",12},
        {"king",13},
        { "ace",14},
};

const std::map<std::string, unsigned short> cardCharacteristics = {
        {"clear", 0},
        {"angled", 1},
        { "bright", 2},
        { "hidden", 3},
        { "dark", 4}
};

//function called on click, gets the click position
void callBackFunc(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        if(currentIndex == 4)
        {
            roiPoints.clear();
            currentIndex = 0;
        }
        roiPoints.emplace_back(x,y);
        currentIndex++;
    }
}

//displays the image
void drawImg(cv::Mat img)
{
    cv::Mat output = img.clone();
    if(roiPoints.size() == 4)
    {
        std::cout << "insert [card value] [card type] [card carcteristics each seperated by a space]" << std::endl;
        std::cout << "available characteristics : clear, angled, bright, hidden, dark" << std::endl;
        cv::polylines(output,roiPoints,true, cv::Scalar(255,0,0),4, cv::LINE_8, 0);
        cv::polylines(img,roiPoints,true, cv::Scalar(255,0,0),4, cv::LINE_8, 0);
        cv::putText(output, "Input the card value and type as : [cardvalue] [type]", roiPoints[0], cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0,0,255), 2);
        inputCardName = true;
    }
    cv::imshow("img", output);
}

//split the string and puts it to lower
std::vector<std::string> split (std::string s, std::string delimiter) {

    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {

        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

int main(int argc, char ** argv){
    std::cout << "argument:" << argv[1] << std::endl;
    cv::Mat img = cv::imread(argv[1]);
    cv::namedWindow("img");

    //verify if argv is correct
    if(img.empty())
    {
        std::cout << "Image does not exist in path" << std::endl;
        return -1;
    }

    cv::setMouseCallback("img", callBackFunc);

    bool finished = false;
    //compute every 16 frames while the esc key isn't pressed
    while(!finished)
    {
        if(inputCardName)
        {
            std::getline (std::cin,name);
            std::cout << "card registered. return to the image to annotate more cards or press esc on the image to finish." << std::endl;
            cardDefinitions.emplace_back(name);

            cv::putText(img, name, roiPoints[0], cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0,0,255), 2);
            inputCardName = false;
            cardPositions.emplace_back(roiPoints);
            roiPoints.clear();
        }
        drawImg(img);
        if (cv::waitKey(16) == 27) finished = true;
    }

    cv::destroyAllWindows();

    //serialize user data
    std::vector<CardMatch> cards;
    for(auto index = 0; index < cardPositions.size(); ++index)
    {
        CardMatch card;
        std::vector<std::string> words = split(cardDefinitions[index], " ");
        if(words.size() < 2)
        {
            std::cerr << "invalid card format for input: " << cardDefinitions[index] << std::endl;
            return -1;
        }
        if (!cardValues.contains(words[0])) {
            std::cerr << "invalid card value for input: " << words[0] << std::endl;
            return -1;
        }
        auto itValue = cardValues.find(words[0]);
        card.cardValue =(Value)itValue->second;

        if(!cardTypes.contains(words[1]))
        {
            std::cerr << "invalid card type for input: " << words[1] <<std::endl;
            return -1;
        }
        if(words.size() == 2)
        {
            card.characteristics.push_back(Characteristics::Clear);
        }
        else
        {
            for(int i = 2; i < words.size(); ++i)
            {
                if (!cardCharacteristics.contains(words[i]))
                {
                    std::cout << words[i] << " is not recognized as a characteristic" << std::endl;
                    continue;
                }

                auto itCharacterstics = cardCharacteristics.find(words[i]);
                card.characteristics.push_back((Characteristics)itCharacterstics->second);

            }
            if(card.characteristics.empty())
            {
                card.characteristics.push_back(Characteristics::Clear);
            }
        }


        auto itType = cardTypes.find(words[1]);
        card.cardType =(Type)itType->second;

        card.pos1 = cardPositions[index][0];
        card.pos2 = cardPositions[index][1];
        card.pos3 = cardPositions[index][2];
        card.pos4 = cardPositions[index][3];

        cards.emplace_back(card);
    }
    TableMatches tableMatches;
    tableMatches.imagePath = argv[1];
    tableMatches.cards = cards;

    DataSerializer::writeData("testData.json", tableMatches);

    return 0;
}