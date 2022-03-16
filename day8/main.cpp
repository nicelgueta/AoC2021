#include <vector>
#include "../utils.h"
#include <iostream>


using namespace std;

bool TEST = true;

string fileName = TEST ? "test_input.txt" : "inputs.txt";

vector<pair<vector<string>,vector<string>>> getInputs () {
    vector<string> inputs = common::readInputs(fileName);
    vector<pair<vector<string>, vector<string>>> inputSplits = {};
    for (string item: inputs){
        vector<string> defOuts = common::splitInput(item, "|", true);
        vector<string> digitDefs= common::splitInput(defOuts[0], " ", true);
        vector<string> digitOuts= common::splitInput(defOuts[1], " ", true);
        inputSplits.push_back(
                pair<vector<string>, vector<string>> (digitDefs, digitOuts)
        );
    }
    return inputSplits;
}

int main ()
{
    
    // first part - how many times do 1 (2), 4(4), 7(3), 8(7) appear
    cout << getInputs();

}