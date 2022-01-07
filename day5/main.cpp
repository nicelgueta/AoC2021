#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h> 

#include "../utils.h"
#include "Board.h"
#include "LineGenerator.h"

using namespace std;

bool TEST = false;

int main()
{
    string inputFile  = TEST ? "test_input.txt" : "input.txt";

    LineGenerator lineGen;
    lineGen.loadFile(inputFile);

    Board mainBoard("b", lineGen.maxX + 1, lineGen.maxY + 1);
    for (int i = 0; i < lineGen.size(); i++){
        pair<pair<int, int>, pair<int,int>> coords = lineGen.getCoords(i);
        pair<int, int> pointA = coords.first;
        pair<int, int> pointB = coords.second;

        pair<int, int> yLine(pointA.second, pointB.second);
        pair<int, int> xLine(pointA.first, pointB.first);

        double gradient;
        int yDelta = (yLine.second - yLine.first);
        int xDelta = (xLine.second - xLine.first);
        // if (xLine.second - xLine.first == 0){
        //     gradient = 0;
        // } else {
        //     gradient = yDelta / xDelta;
        // }
        // int c = yLine.first - (gradient * xLine.first);

        // horizontal or vertical lines
        if (xDelta == 0 || yDelta == 0){
            // cout << "------start line-----\n";
            if (xDelta == 0){
                // vertical line
                int x = xLine.first;
                if(yDelta < 0){
                    for(int i = 0;i >= yDelta; i--){
                        int y = yLine.first - i;
                        mainBoard.incrementValue(y, x);
                    }
                } else {
                    for(int i = 0;i <= yDelta; i++){
                        int y = yLine.first + i;
                        mainBoard.incrementValue(y, x);
                    }
                }
            } else if (yDelta == 0) {
                // horizontal line
                int y = yLine.first;
                if(xDelta < 0){
                    for(int i = 0;i >= xDelta; i--){
                        int x = xLine.first - i;
                        mainBoard.incrementValue(y, x);
                    }
                } else {
                    for(int i = 0;i <= xDelta; i++){
                        int x = xLine.first + i;
                        mainBoard.incrementValue(y, x);
                    }
                }
            }   
        } else {
            cout << "------NOT------\n";
            cout << "xLine.first " << xLine.first << endl;
            cout << "xLine.second " << xLine.first << endl;
            cout << "yLine.first " << yLine.first << endl;
            cout << "yLine.second " << yLine.first << endl;
        }

        
    }
    // mainBoard.printBoard();
    cout << "Part 1 answer: " << mainBoard.findNoGtEt(2) << endl;


}