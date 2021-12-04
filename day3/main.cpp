#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <bitset>

#include "../utils.h"

using namespace std;

array<int, 12> findBitCounts(vector<string> &binStrings){
    // find bits most common with 1

    array<int, 12> bitCounts = { 0 };

    for (int i = 0; i < binStrings.size(); i++){
        string binString = binStrings[i];
        for (int j = 0; j < 12; j++){
            char bit = binString[j];
            int is1 = bit - 48; // ascii chars start at 48 with 0, so 1 is 49
            bitCounts[j] += is1;
        }
    }
    return bitCounts;
}
bitset<12> findGamma(array<int, 12> &bitCounts, int &inputFormSize){
    
    // count # of 1s. number of 0s will be input size - 1s
    // count for each 12 bits
    
    bitset<12> gamma;
    for (int i = 0; i < 12; i++){

        cout << "bitCounts[" << i << "] = " << bitCounts[i] << endl;

        int leastCommon1s = bitCounts[i] < (inputFormSize - bitCounts[i]);

        // set bit position j of bit to be set 
        // inverse owing to right to left for bitsets
        size_t j = (12 - (i+1));
        gamma.set(j, (1-leastCommon1s));  
    }
    cout << "Gamma=" << gamma.to_string();
    cout << "(" << gamma.to_ulong() << ")" << endl;
    return gamma;
}

pair<array<int, 12>, array<int, 12>> findMostLeastCommon(
    array<int, 12> &bitCounts, int inputFormSize
){
    // filters numbers by bit position until only 1 is left
    // uses counts and formsize to work out most common
    // returns array of 1 or 0 ints

    array<int, 12> oxygenMosts = {0};
    array<int, 12> co2Leasts = {0};
    for (int i = 0; i < 12; i++){
        int noOfOnes = bitCounts[i];
        int noZeroes = (inputFormSize - bitCounts[i]);
        oxygenMosts[i] = noOfOnes >= noZeroes;
        co2Leasts[i] = !(noOfOnes >= noZeroes);
    }


    return make_pair(oxygenMosts, co2Leasts);

}
bool testFirstChar(string binString, int matchCriteria, int charIndex){
    char targetBit = binString[charIndex];
    if ((targetBit - 48) == matchCriteria){
        return true;
    } else {
        return false;
    }
}
bitset<12> findRating(
    vector<string> &binStrings,
    string mostOrLeast
){
    vector<string> binStringsToKeep = binStrings;
    bitset<12> finalBitSet;
    for (int i = 0; i < 12; i++){
        
        // count new totals
        array<int,12> bitCounts = findBitCounts(binStringsToKeep);
        pair<
            array<int,12>, 
            array<int,12>
        > mostLeastCommon =  findMostLeastCommon(
            bitCounts, binStringsToKeep.size()
        );
        array<int,12> mostLeastArr = mostOrLeast == "most" ? mostLeastCommon.first : mostLeastCommon.second;
        binStringsToKeep = common::pythonStyleFilter(
            testFirstChar, 
            binStringsToKeep,
            mostLeastArr[i],
            i
        );
        if (binStringsToKeep.size() == 1){
            finalBitSet = bitset<12>(binStringsToKeep[0]);
            return finalBitSet;
        }
    }
    throw runtime_error("Reached end without finding a rating!");
}


int main()
{
    
    vector<string> binStrings = common::readInputs("input.txt");
    
    int inputFormSize = binStrings.size();

    cout << "Part 1\n";
    array<int, 12> bitCounts = findBitCounts(binStrings);


    bitset<12> gamma = findGamma(bitCounts, inputFormSize);
    bitset<12> epsilon = ~gamma;

    int powerConsumption = gamma.to_ulong() * epsilon.to_ulong();

    cout << "Epsilon=" << epsilon.to_string();
    cout << "(" << epsilon.to_ulong() << ")" << endl;
    cout << "Answer: " << powerConsumption << endl;

    cout << "\n\nPart 2\n";

    bitset<12> oxgenRating = findRating(binStrings, "most");
    bitset<12> co2Rating = findRating(binStrings, "least");

    int lifeSupportRating = oxgenRating.to_ulong() * co2Rating.to_ulong();

    cout << "oxgenRating=" << oxgenRating.to_string();
    cout << "(" << oxgenRating.to_ulong() << ")" << endl;

    cout << "co2Rating=" << co2Rating.to_string();
    cout << "(" << co2Rating.to_ulong() << ")" << endl;

    cout << "Answer: " << lifeSupportRating << endl;
    



}