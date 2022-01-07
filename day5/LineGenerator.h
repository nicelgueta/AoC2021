#pragma once
#include <vector>
#include <string>



class LineGenerator
{
    private:
        // pair of pairs: coord of A coord of B
        std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> lines;
    public:
        LineGenerator();
        ~LineGenerator(){};
        int maxX;
        int maxY;
        // getters
        std::pair<std::pair<int, int>, std::pair<int, int>> 
            getCoords(int lineNo) const;
        int size() const;
        
        // setters
        void loadFile(std::string filePath);
};