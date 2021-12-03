#include <iostream>
#include <string>
#include <vector>

#include "../utils.h"

using namespace std;


int main()
{
    vector<string> inputs = common::readInputs("input.txt");
    vector<string> actions;
    vector<int> distances;
    for (int i = 0; i < inputs.size(); i++){
        vector<string> splitInput = common::splitInput(inputs[i]);
        string action = splitInput[0];
        int distance = stoi(splitInput[1]);
        actions.push_back(action);
        distances.push_back(distance);
    }
    cout << "\nPart 1: \n";
    int horizontalPosition = 0;
    int depth = 0;

    for (int i = 0; i < actions.size(); i++){
        int distance = distances[i];
        string action = actions[i];
        if (action=="forward"){horizontalPosition+=distance;}
        else if (action=="up"){depth-=distance;}
        else if (action=="down"){depth+=distance;}
        else {throw invalid_argument("What do I do with "+action+"?\n");}
    }

    cout << "Final HP " << horizontalPosition << endl;
    cout << "Final Depth " << depth << endl;
    cout << "Product (answer) " << horizontalPosition * depth << endl;

    cout << "\nPart 2: \n";
    int aim = 0;
    horizontalPosition = 0;
    depth = 0;

    for (int i = 0; i < actions.size(); i++){
        int distance = distances[i];
        string action = actions[i];
        if (action == "forward"){
            horizontalPosition += distance;
            depth += (aim * distance);
        }
        else if (action=="up"){aim-=distance;}
        else if (action=="down"){aim+=distance;}
        else {throw invalid_argument("What do I do with "+action+"?\n");}

    }
    cout << "Final HP " << horizontalPosition << endl;
    cout << "Final Depth " << depth << endl;
    cout << "Product (answer) " << horizontalPosition * depth << endl;
}