#ifndef PATTERNRECOGNIZER_H
#define PATTERNRECOGNIZER_H

#include <iostream>
#include <map>
#include <unordered_set>
#include <set>
#include <vector>
#include <string>

#define TS 15

using Position = std::pair<int, int>;

class PatternRecognizer
{
public:
    PatternRecognizer(const std::string &path);
    Position query(const int board[TS][TS], const int curr);

private:
    enum class GridState { Nil, Opponent, Proponent};
    struct hasher {  // 自定义hash函数
        std::size_t operator()(const std::pair<Position, GridState> &point) const {
            return std::hash<int>()(point.first.first) ^ std::hash<int>()(point.first.second);
        }
    };
    struct Pattern {
        Position target;
        Position rowcol;
        std::string rawstr;
        std::unordered_set<std::pair<Position, GridState>, hasher> points;
        bool operator<(const Pattern &a) const { return rawstr < a.rawstr; }
    };
    std::map<std::pair<int, int>, std::set<Pattern>> patterns;

    void fillthemap(std::set<Pattern> &pset, Pattern &ptn);
};

#endif // PATTERNRECOGNIZER_H
