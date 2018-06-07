#include "patternrecognizer.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>
#include <iterator>

PatternRecognizer::PatternRecognizer(const std::string &path) {
    initialize(path);
}

void PatternRecognizer::initialize(const std::string &path) {

    if (!patterns.empty()) patterns.clear();

    std::ifstream in(path);
    std::string line;
    std::vector<std::string> matrix;

    while (in) {
        matrix.clear();
        do {
            if (!std::getline(in, line)) break;
            if (line.empty()) break;
            matrix.push_back(line);
        } while (true);
        if (matrix.empty()) continue;
        line = matrix.back();
        if (line[0] == '/') continue;
        auto b = line.find_first_of("0123456789");
        if(b == std::string::npos) throw;

        std::stringstream ss;
        Pattern ptn;
        ss << line.substr(b);
        ss >> ptn.target.first >> ptn.target.second;
        ss.clear();  // essential
        std::for_each(matrix.begin(), matrix.end(), [&] (const std::string &s) { ss << s; });
        ss >> line;

        ptn.rawstr = std::string(line.begin(), line.end());
        std::cout << "rawstr(" << ptn.rawstr.length() << "): [" << ptn.rawstr << "]" << std::endl;
        ptn.rowcol = std::make_pair(matrix.size(), line.length()/matrix.size());
        fillthemap(patterns[ptn.rowcol], ptn);
        std::cout << std::endl;
    }
    // 输出所有模式
    std::cout << std::endl;
    for (auto &item : patterns) {
        std::cout << item.first.first << "x" << item.first.second
                  << "(" << item.second.size() << "): " << std::endl;
        for (auto &it : item.second) {
            std::cout << "    [" << it.rawstr << " - (" << it.target.first
                  << ", " << it.target.second << ")]" << std::endl;
        }
    }
    std::cout << "Initialization done!\n" << std::endl;
}

void PatternRecognizer::fillthemap(std::set<Pattern> &pset, Pattern &ptn) {
    auto gridState = GridState::Nil;
    std::cout << "    points.insert: [";
    for (int i = 0; i < (int)ptn.rawstr.length(); ++i) {
        switch (ptn.rawstr[i]) {
        case 'x':
            gridState = GridState::Proponent; break;
        case 'o':
            gridState = GridState::Opponent; break;
        case '_':
            gridState = GridState::Nil; break;
        default: continue;
        }  // 检查点的位置，0为第一个
        std::cout << "(" << i / ptn.rowcol.second
                  << ", " << i % ptn.rowcol.second << ") "
                  << ptn.rawstr[i] << ", ";
        ptn.points.insert({{i / ptn.rowcol.second, i % ptn.rowcol.second}, gridState});
    }
    std::cout << "]" << std::endl;
    pset.insert(ptn);
}

Position PatternRecognizer::query(const int board[TS][TS], const int proponent) {
    std::cout << "Query: ";
    for (auto &mptns : patterns) {
        unsigned row = mptns.first.first, col = mptns.first.second;
        std::cout << row << "x" << col << " -> ";
        for (unsigned i = 0; i <= TS - row; ++i) {
            for (unsigned j = 0; j <= TS - col; ++j) {

                for (auto &ptn : mptns.second) {
                    for (auto &point : ptn.points) {
                        auto grid = board[i + point.first.first][j + point.first.second];
                        if (!grid) {
                            if (point.second != GridState::Nil)
                                goto CONTINUE;
                        } else if (proponent == grid) {
                            if (point.second != GridState::Proponent)
                                goto CONTINUE;
                        } else {
                            if (point.second != GridState::Opponent)
                                goto CONTINUE;
                        }
                    }
                    std::cout << "end(" << i + ptn.target.first << ", " << j + ptn.target.second << ")" << std::endl;
                    return {i + ptn.target.first, j + ptn.target.second};
                    CONTINUE: continue;
                }
            }
        }
    }
    std::cout << "not found" << std::endl;
    throw 2333;
    return {-1, -1};
}
