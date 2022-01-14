
#include <string>
#include <vector>
#include <iostream>
#include <math.h>  
#include "../utils.h"
#include <map>

using namespace std;

int TEST = false;

string fileName = TEST ? "test_input.txt" : "input.txt";

vector<int> getAges() {
    string inputStr = common::readInputs(fileName)[0];
    vector<string> inputStrVec = common::splitInput(inputStr, ",");
    vector<int> inputAges = {};
    for (int i = 0; i < inputStrVec.size(); i++){
        inputAges.push_back(stoi(inputStrVec[i]));
    }
    return inputAges;

}

long getTotal(int days){
    map<int,long> ageMap = {};
    for (int i = 0; i < 9; i++){
        ageMap[i] = 0;
    }
    vector<int> ages = getAges();
    for (int i: ages){
        ageMap[i]++;
    }
    int x = 0;
    while (x < days){
        map<int,long> newAgeMap = {};
        for (int i = 0; i < 9; i++){
            newAgeMap[i] = 0;
        }
        for (auto const& [key, val] : ageMap){
            if(val < 1) continue;
            int newAge = key - 1;
            if (newAge == -1){
                newAgeMap[8]+=val;
                newAge = 6;
            }
            newAgeMap[newAge]+=val;
        }
        ageMap = newAgeMap;
        x++;
    }
    long total = 0;
    for (auto const& [key, val] : ageMap) total+=val;
    return total;
}

int main()
{
    cout << "Part 1: total after " << 80 << " days: " << getTotal(80) << endl;
    cout << "Part 1: total after " << 256 << " days: " << getTotal(256) << endl;
}
