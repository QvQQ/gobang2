#ifndef PATTERNRECOGNIZER_H
#define PATTERNRECOGNIZER_H

#include <iostream>
#include <map>
#include <unordered_set>
#include <set>
#include <vector>
#include <string>
#include <numeric>

#define TS 15

using Position = std::pair<int, int>;

class PatternRecognizer
{
public:
    PatternRecognizer(const std::string &path);
    void initialize(const std::string &path);
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
    struct comparer {  // 自定义key排序
        bool operator()(const std::pair<int, int> &pair1, const std::pair<int, int> &pair2) const {
            int max1 = std::max(pair1.first, pair1.second);
            int max2 = std::max(pair2.first, pair2.second);
            if (max1 > max2)
                return true;
            else if (max1 < max2)
                return false;
            else return pair1 > pair2;
        }
    };
    std::map<std::pair<int, int>, std::set<Pattern>, comparer> patterns;

    void fillthemap(std::set<Pattern> &pset, Pattern &ptn);
};

#endif // PATTERNRECOGNIZER_H
