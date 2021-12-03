#include <iostream>
#include <string>
#include <vector>

#include "../utils.h"

using namespace std;

bool checkLarger(int depth, int nextDepth){
    return nextDepth > depth ? 1 : 0;
}

vector<int> getWindow(int index, vector<int> vect){
    vector<int> window;
    for (int j = 0; j < 3; j++){
        window.push_back(vect[index + j]);
    }
    return window;
}

int getNumberLarger(vector<int> inputs){
    int numberLarger = 0;
    for (int i = 0; i < (inputs.size() - 1); i++){
        int depth  = inputs[i];
        int nextDepth = inputs[i + 1];
        numberLarger += checkLarger(depth, nextDepth);
    }
    return numberLarger;
}

int main()
{
    vector<int> inputs = common::readInputsAsInt("input.txt");
    cout << "\n -- Part 1 --\n";
    cout << "answer: " << getNumberLarger(inputs) << endl;
    cout << "\n -- Part 2 --\n";
    
    // no rolling windows of 3 items (arr len - window size - 1)
    int noWindows = inputs.size()-2;
    vector<int> windowSums;
    int windowCount = 0;
    for (int i = 0; i < inputs.size(); i++){
        if (windowCount == noWindows){
            // bail cos we can't make anymore
            break;
        }
        vector<int> window = getWindow(i, inputs);
        windowSums.push_back(common::sumVector(window));
        windowCount++;
    }
    cout << "answer: " << getNumberLarger(windowSums) << endl;

}