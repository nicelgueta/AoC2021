#pragma once
#include <vector>
#include <string>
#include <map>

class WireMap
{
    private:
        std::map<char, std::vector<int>> wire_map;
        std::map<int, std::vector<int>> index_map;
        std::map<int, bool> uniques_found;
        std::map<int, std::string> uniques_str;
        std::map<std::string, int> uniques_int;
        bool check_complete();
        int check_match(char letter, std::string target);
    public:
        WireMap();
        ~WireMap(){};

        void check(std::string pattern);
        void deduce(
            std::vector<std::string> len5patts,
            std::vector<std::string> len6patts
        );

        int translate(std::string pattern);

        

};