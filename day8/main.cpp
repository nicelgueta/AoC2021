#include <vector>
#include "../utils.h"
#include <iostream>
#include <algorithm>
#include "wiremap.h"


using namespace std;

bool TEST = true;


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
    cout << "Part 1: found " << times << " times" << endl;


    int total = 0;
    for (pair<vector<string>,vector<string>> combs: inputs){
        vector<string> defs = combs.first;
        vector<string> outs = combs.second;

        WireMap wm = WireMap();
        // pull out uniques and lens
        vector<string> len5s = {};
        vector<string> len6s = {};
        for (string patt: defs){
            if (patt.length() == 5){len5s.push_back(patt);}
            if (patt.length() == 6){len6s.push_back(patt);}
            wm.check(patt);
        }

        // run deduction
        wm.deduce(len5s, len6s);

        // run translation of outputs
        string result = "";
        for (string patt: outs){
            char res = '0' + wm.translate(patt);
            result += res;
        }

        cout << "result " << result << endl;
        int final_result = std::stoi(result);

        total+=final_result;
       
    }
    
    cout << "Final total: " << total << endl;


}