#pragma once
#ifndef _UTILS_H
#define _UTILS_H

#include <string>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <variant>
#include <functional>
#include <regex>

namespace common
{


    std::string ltrim(const std::string &s) {
        return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
    }
 
    std::string rtrim(const std::string &s) {
        return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
    }

    inline std::vector<std::string> readInputs(std::string fileName){

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

    inline std::vector<int> readInputsAsInt(std::string fileName){

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

    inline int sumVector(std::vector<int> vect){
        int s = 0;
        for (int i = 0; i < vect.size(); i++){
            s += vect[i];
        }
        return s;
    };

    inline std::vector<std::string> splitInput(
            std::string inputItem, 
            std::string delimiter = " ",
            bool trim = false
        ){
        std::vector<std::string> ret = {};
        int i = 0;
        int wordEndIndex = inputItem.find(delimiter);
        int distanceBeginIndex = wordEndIndex + delimiter.length();
        while (wordEndIndex < inputItem.length()){
            string _item = inputItem.substr(0, wordEndIndex);
            ret.push_back(trim ? ltrim(rtrim(_item)) : _item);
            // change input item
            inputItem = inputItem.substr(distanceBeginIndex);
            wordEndIndex = inputItem.find(delimiter);
            distanceBeginIndex = wordEndIndex + delimiter.length();
        }
        // final item

        ret.push_back(trim ? ltrim(rtrim(inputItem)) : inputItem);


        return ret;

    };

    inline std::vector<std::string> pythonStyleFilter(
        std::function<bool (std::string, int matchCriteria, int charIndex)> mappedFunc,
        std::vector<std::string> vect,
        int matchCriteria,
        int charIndex
    ){
        std::vector<std::string> itemsToKeep;
        for (int i = 0; i < vect.size(); i++){
            if (mappedFunc(vect[i], matchCriteria, charIndex)){
                itemsToKeep.push_back(vect[i]);
            }
        }
        return itemsToKeep;
    };

    inline std::vector<std::string> strSubVector(
        std::vector<std::string> vect,
        int start = 0,
        int end = -1
    ){  
        end = end == -1 ? vect.size() : end;
        int subVectorSize = end - start;
        std::vector<std::string> subVector;

        for (int j = 0; j < subVectorSize; j++){
            subVector.push_back(vect[start + j]);
        }
        return subVector;
    }
    
}

#endif