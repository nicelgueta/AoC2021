
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <algorithm>
#include "Board.h"
#include "../utils.h"

using namespace std;

bool TEST = false;

vector<int> getInputs(string input)
{
    stringstream inputStream(input);
    string inputNumberStr;
    vector<int> retVect;

    while (getline(inputStream, inputNumberStr, ','))
    {
        retVect.push_back(stoi(inputNumberStr));
    }
    return retVect;
}
vector<vector<vector<int>>> getMatrices(vector<string> &inputLines)
{
    vector<vector<vector<int>>> matrices;
    matrices.reserve(inputLines.size());
    int boardNumber = -1;
    for (int i = 0; i < inputLines.size(); i++)
    {
        if (inputLines[i].length() < 1)
        {
            vector<vector<int>> newMatrix;
            newMatrix.reserve(5);
            matrices.push_back(newMatrix);
            boardNumber++;
            continue;
        }
        stringstream line(inputLines[i]);
        string numberStr;
        vector<int> newRow;
        newRow.reserve(5);
        while (getline(line, numberStr, ' '))
        {
            if (numberStr==""){ continue; }
            newRow.push_back(stoi(numberStr));
        }
        matrices[boardNumber].push_back(newRow);

    }
    return matrices;
}

enum Strategy{
    Win,
    Lose
};

void play(
        vector<Board> &boards, 
        vector<int> generatedInputs, 
        Strategy strat = Win
    ){
    // play
    for (int i = 0; i < boards.size(); i++){
        boards[i].beginGame();
    }
    vector<Board> * pBoards = &boards;
    vector<Board> roundWinners;

    // add names of boards that are playing in order to remove
    // them for part 2
    vector<string> stillPlaying;

    for (int i = 0; i < boards.size(); i++){
        stillPlaying.push_back(boards[i].getName());
    }
    for (int i = 0; i < generatedInputs.size(); i++){
        // cout << "__________\nPlaying round " << i << "\n------------\n";
        int numberDrawn = generatedInputs[i];
        // cout << "------Number Drawn: " << numberDrawn << endl;
        // each board checks themselves
        for (int j = 0; j < boards.size(); j++){
            Board &gameBoard = pBoards->at(j);
            pair<int,int> coordinates = gameBoard.searchNumber(numberDrawn);
            if (coordinates.first > -1){
                // found number
                gameBoard.markValue(coordinates.first, coordinates.second);
                
                // check for any wins
                if (gameBoard.checkRowMarked(coordinates.first) ||
                gameBoard.checkColMarked(coordinates.second) ){
                    if (! gameBoard.alreadyWon){
                        gameBoard.setWinScores(
                            numberDrawn, 
                            gameBoard.sumUnmarked()
                        );
                        roundWinners.push_back(gameBoard);
                    }
                }
                // gameBoard.printBoard(Marked);
            }
        }

        // any winners from round?
        if (roundWinners.size() > 0 and strat == Win){
            cout << "\n****\n" << roundWinners.size() << " winners in round ";
            cout << i << endl << "****\n";
            for (int k = 0; k < roundWinners.size(); k++){
                
                cout << roundWinners[k].getName();
                cout << ": remaining number sum: " << roundWinners[k].sumUnmarked();
                cout << "\nScore to submit: " << numberDrawn * roundWinners[k].sumUnmarked();
                cout << endl;
            }
            if (strat==Win){
                break;
            }
        }
        if (roundWinners.size() == boards.size()){
            // final player has won their card
            Board &lastBoard = roundWinners[roundWinners.size()-1];
            cout << lastBoard.getName();
            cout << ": remaining number sum: " << lastBoard.sumUnmarked();
            cout << "\nScore to submit: " << numberDrawn * lastBoard.sumUnmarked();
            cout << endl; 
            break;
        }
    }

    // // end round check last winner
    // if (strat == Lose){
    //     Board &lastBoard = roundWinners[roundWinners.size()-1];
    //     cout << lastBoard.getName();
    //     cout << ": remaining number sum: " << lastBoard.winScores.second;
    //     cout << "\nScore to submit: " << lastBoard.winScores.first * lastBoard.winScores.second;
    //     cout << endl;
    // }
}

void playPart(vector<string> inputLines, int partNumber)
{
    vector<int> generatedInputs = getInputs(inputLines[0]);
    vector<string> boardInputs = common::strSubVector(inputLines, 1);
    vector<vector<vector<int>>> matrices = getMatrices(boardInputs);
    vector<Board> boards;
    for (int i = 0; i < matrices.size(); i++){
        Board game(matrices[i], "Bing Board #"+to_string(i));
        boards.push_back(game);
    }
    if (partNumber == 1){
        play(boards, generatedInputs, Win);
    } else if (partNumber == 2){
        play(boards, generatedInputs, Lose);
    }
}

int main()

{
    string inputFileName = TEST ? "test_input.txt" : "input.txt";
    vector<string> inputLines = common::readInputs(inputFileName);

    cout << "Part 1:\n\n";
    playPart(inputLines, 1);

    cout << "\nPart 2:\n\n";
    playPart(inputLines, 2);
}