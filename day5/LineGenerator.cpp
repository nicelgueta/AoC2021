#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include "LineGenerator.h"
#include "../utils.h"

using namespace std;

LineGenerator::LineGenerator() : 
    maxX(0),
    maxY(0)
    {};


void LineGenerator::loadFile(string filePath){

    string inputLine;
    ifstream inputFile(filePath);

    while (getline(inputFile, inputLine)){
        // it over lines
        regex const pointsReg("([0-9]+\\,[0-9]+).*([0-9]+\\,[0-9]+)");
        smatch sm;
        pair<int, int> pointA;
        pair<int, int> pointB;
        if (regex_search(inputLine, sm, pointsReg)) {
            vector<string> pointAStr = common::splitInput(sm[1], ",");
            pointA = pair<int, int>(stoi(pointAStr[0]), stoi(pointAStr[1]));
            
            
            vector<string> pointBStr = common::splitInput(sm[2], ",");
            pointB = pair<int, int>(stoi(pointBStr[0]), stoi(pointBStr[1]));
            
            // 
            if (pointA.first > maxX){maxX=pointA.first;}
            if (pointA.second > maxY){maxY=pointA.second;}
            if (pointB.first > maxX){maxX=pointB.first;}
            if (pointB.second > maxY){maxY=pointB.second;}
        };
        pair<pair<int, int>, pair<int, int>> coord(pointA, pointB);
        lines.push_back(coord);

    }
    inputFile.close();
    if (lines.size() < 1){
        throw runtime_error("No inputs were read - file there?");
    }
}

int LineGenerator::size() const {
    return lines.size();
}

pair<pair<int, int>, pair<int, int>> 
    LineGenerator::getCoords(int lineNo) const {
    return lines[lineNo];
}