#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <variant>


namespace common
{

    std::vector<std::string> readInputs(std::string fileName){

        std::string inputTextItem;
        std::vector<std::string> inputs;
        std::ifstream inputFile(fileName);

        while (std::getline(inputFile, inputTextItem)){
            inputs.push_back(inputTextItem);
        }
        inputFile.close();
        if (inputs.size() < 1){
            throw std::runtime_error("No inputs were read - file there?");
        }
        return inputs;
    };

    std::vector<int> readInputsAsInt(std::string fileName){

        std::string inputTextItem;
        std::vector<int> inputs;
        std::ifstream inputFile(fileName);

        while (std::getline(inputFile, inputTextItem)){
            inputs.push_back(std::stoi(inputTextItem));
        }
        if (inputs.size() < 1){
            throw std::runtime_error("No inputs were read - file there?");
        }
        inputFile.close();
        return inputs;
    };

    int sumVector(std::vector<int> vect){
        int s = 0;
        for (int i = 0; i < vect.size(); i++){
            s += vect[i];
        }
        return s;
    };

    std::vector<std::string> splitInput(
        std::string inputItem, 
        std::string delimiter = " "
    ){
        int wordEndIndex = inputItem.find(delimiter);
        int distanceBeginIndex = wordEndIndex + delimiter.length();
        return {
            inputItem.substr(0, wordEndIndex),
            inputItem.substr(distanceBeginIndex)
        };

    }
}
