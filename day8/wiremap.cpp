#include <vector>
#include <iostream>
#include <string>
#include "wiremap.h"
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

WireMap::WireMap(
): uniques_found({}) {
    map<int, vector<int>> _indexMap = {
        {0, {0,1,2,4,5,6}},
        {1, {2,5}},
        {2, {0,2,3,4,6}},
        {3, {0,2,3,5,6}},
        {4, {1,2,3,5}},
        {5, {0,1,3,5,6}},
        {6, {0,1,3,4,5,6}},
        {7, {0,2,5}},
        {8, {0,1,2,3,4,5,6}},
        {9, {0,1,2,3,5,6}}
    };
    map<char, vector<int>> _wireMap = {};
    vector<char> wires = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    for (char wire: wires){
        _wireMap[wire] = {};
        for (int i = 0; i < 8; i++){
            _wireMap[wire].push_back(i);
        }
    }   
    index_map = _indexMap;
    wire_map = _wireMap;
}

void WireMap::check(string pattern){
    map<int, int> uniques = {{2,1},{4,4},{3,7},{7,8}};
    for (auto const& [len, val] : uniques){
        if (len == pattern.length()){
            for (int i = 0; i < len; i++){
                wire_map[pattern[i]] = index_map[uniques[len]];
            }
            uniques_found[uniques[len]] = true;
            uniques_str[uniques[len]] = pattern;
            uniques_int[pattern] = uniques[len];
        }
    }
    
}

bool WireMap::check_complete() {
    if (
        uniques_found[1] &&
        uniques_found[4] &&
        uniques_found[7] &&
        uniques_found[8]
    ){
        return true;
    } else {
        return false;
    }
}

int WireMap::check_match(char letter, string target){
    if (
        std::find(
            target.begin(), 
            target.end(), 
            letter
        ) != target.end()
    ){
        return 1;
    } else {
        return 0;
    }
}

void WireMap::deduce(
    vector<string> len5patts, 
    vector<string> len6patts 
){
    if (! check_complete()){
        throw std::runtime_error("Unique patterns not yet found");
    }
    
    vector<int> len5s = {2,3,5};
    vector<int> len6s = {0,6,9};

    // 3 will have both letters from 1
    for (int j = 0; j < len5patts.size(); j++){
        string patt = len5patts[j];
        int found = 0;
        for (int i = 0;i < patt.length();i++){
            found += check_match(patt[i], uniques_str[1]);
        }
        if (found == 2){
            uniques_str[3] = patt;
            uniques_int[patt] = 3;
            len5patts.erase(len5patts.begin()+j);
            break;
        }
    }

    // 2 will be missing two segments from 4
    for (int j = 0; j < len5patts.size(); j++){
        string patt = len5patts[j];
        int found = 0;
        for (int i = 0;i < patt.length();i++){
            found += check_match(patt[i], uniques_str[4]);
        }
        if (found == 2){
            uniques_str[2] = patt;
            uniques_int[patt] = 2;
            len5patts.erase(len5patts.begin()+j);
            break;
        }
    }

    // last one must be 5
    uniques_str[5] = len5patts[0];
    uniques_int[len5patts[0]] = 5;

    // len 6s
    // 6 will miss one letter from 1
    for (int j = 0; j < len6patts.size(); j++){
        string patt = len6patts[j];
        int found = 0;
        for (int i = 0;i < patt.length();i++){
            found += check_match(patt[i], uniques_str[1]);
        }
        if (found == 1){
            uniques_str[6] = patt;
            uniques_int[patt] = 6;
            len6patts.erase(len6patts.begin()+j);
            break;
        }
    }

    // 0 will miss one letter from 4
    for (int j = 0; j < len6patts.size(); j++){
        string patt = len6patts[j];
        int found = 0;
        for (int i = 0;i < patt.length();i++){
            found += check_match(patt[i], uniques_str[4]);
        }
        if (found == 3){
            uniques_str[0] = patt;
            uniques_int[patt] = 0;
            len6patts.erase(len6patts.begin()+j);
            break;
        }
    }

    // remainder must be 9
    uniques_str[9] = len6patts[0];
    uniques_int[len6patts[0]] = 9;

    // for (int i = 0; i < 10; i++){
    //     cout << i << " = " << uniques_str[i] << endl;
    //     cout << "uniques_int[" << uniques_str[i] << "] = " << uniques_int[uniques_str[i]] << endl;
    // }

}

int WireMap::translate(string pattern){
    int digit;
    for (auto const& [patt, numba]: uniques_int){
        if (patt.length() != pattern.length()){
            continue;
        }
        int captured = 0;
        for (int i = 0; i < patt.length(); i++){
            char letter = patt[i];
            captured+=check_match(letter, pattern);
        }
        if (captured==pattern.length()){
            digit = numba;
            break;
        }
    }
    return digit;
}





