#include "patternrecognizer.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>
#include <iterator>

PatternRecognizer::PatternRecognizer(const std::string &path) {

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
        ptn.rowcol = std::make_pair(matrix.size(), matrix.front().size());
        fillthemap(patterns[ptn.rowcol], ptn);
    }
    // 输出所有模式
    for (auto &item : patterns) {
        std::cout << std::endl << item.first.first << "x" << item.first.second << ": " << std::endl;
        for (auto &it : item.second) {
            std::cout << '[' << it.rawstr << " - (" << it.target.first
                  << ", " << it.target.second << ")]" << std::endl;
        }
    }
    std::cout << "Initialization done" << std::endl;
}

void PatternRecognizer::fillthemap(std::set<Pattern> &pset, Pattern &ptn) {
    auto gridState = GridState::Nil;
    for (int i = 0; i < (int)ptn.rawstr.length(); ++i) {
        if (ptn.rawstr[i] == '#') continue;
        switch (ptn.rawstr[i]) {
        case 'x': gridState = GridState::Proponent; break;
        case 'o': gridState = GridState::Opponent; break;
        case '_': gridState = GridState::Nil; break;
        }  // 检查点的位置，0为第一个
        std::cout << "points.insert: (" << i / ptn.rowcol.second
                  << ", " << i % ptn.rowcol.second << ") "
                  << ptn.rawstr[i] << std::endl;
        ptn.points.insert({{i / ptn.rowcol.second, i % ptn.rowcol.second}, gridState});
    }
    pset.insert(ptn);
}

Position PatternRecognizer::query(const int board[TS][TS], const int proponent) {

    for (int i = 0; i < TS; ++i) {
        for (int j = 0; j < TS; ++j) {
            std::cout << board[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    for (auto &mptns : patterns) {
        unsigned row = mptns.first.first, col = mptns.first.second;
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
                    return {i + ptn.target.first, j + ptn.target.second};
                    CONTINUE: continue;
                }
            }
        }
    }
    throw 2333;
    return {-1, -1};
}
