#include <vector>
#include "../utils.h"
#include <iostream>
#include <algorithm>


using namespace std;

bool TEST = false;


vector<pair<vector<string>,vector<string>>> getInputs () {
    string fileName = TEST ? "test_input.txt" : "input.txt";
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

    vector<int> uniques = {2,4,3,7};

    vector<pair<vector<string>,vector<string>>> inputs = getInputs();
    int times = 0;
    for (pair<vector<string>,vector<string>> combs: inputs){
        vector<string> outs = combs.second;
        for (string set: outs){
            if (
                std::find(
                    uniques.begin(), 
                    uniques.end(), 
                    set.length()
                ) != uniques.end()
            ){
                times++;
            } else {
                // nowt
            }
        }
    }
    cout << "found " << times << " times" << endl;


}