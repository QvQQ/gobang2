#ifndef PATTERNRECOGNIZER_H
#define PATTERNRECOGNIZER_H

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>

class PatternRecognizer
{
public:
    PatternRecognizer(const std::string &path);

private:
    struct Pattern {
        std::string raw;
        std::pair<int, int> pos;
        bool operator<(const Pattern &a) const { return raw < a.raw; }
    };
    std::set<Pattern> rawPatterns;
    std::map<std::pair<int, int>, std::map<std::string, std::pair<int, int>>> patterns;
    //   map(     pair(3, 3)    ,      map("xxooxxxxx",      pair(2, 1)       )))
    void fillthemap(std::map<std::string, std::pair<int, int>> &map, std::string &s, const std::pair<int, int> &p);
};

#endif // PATTERNRECOGNIZER_H
