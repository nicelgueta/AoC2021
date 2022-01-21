#include <vector>
#include "../utils.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

bool TEST = false;

vector<int> getInput(){
    string fileName = TEST ? "test_input.txt" : "input.txt";
    string inputLine = common::readInputs(fileName)[0];
    vector<string> inputs = common::splitInput(inputLine, ",");
    vector<int> ret = {};
    for( string item : inputs){
        ret.push_back(stoi(item));
    }
    return ret;
}

int main ()
{
    vector<int> locations = getInput();

    // sort and find median
    sort(locations.begin(), locations.end());
    int median = locations[ceil(locations.size() * 0.5)];
    int fuelSpent = 0;
    for (int loc: locations){fuelSpent+=(abs(loc - median));}

    cout << "Part 1" << endl;
    cout << "fuelSpent: " << fuelSpent << endl;

    // part 2 - fuel cost increases 
    // like a regression problem, we want to minimise sum of sq diffs
    int sumLocations = 0;
    for (int n : locations)
      sumLocations += n;
    int mean = ceil(sumLocations / locations.size());
    
    fuelSpent = 0;
    for (int loc: locations){
      fuelSpent+=(abs(loc - mean) * (abs(loc - mean) + 1) / 2 );}

    cout << "Part 2" << endl;
    cout << "fuelSpent: " << fuelSpent << endl;

}