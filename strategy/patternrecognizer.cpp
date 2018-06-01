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
    Pattern ptn;

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
        ss << line.substr(b);
        ss >> ptn.pos.first >> ptn.pos.second;
        ss.clear();  // essential
        std::for_each(matrix.begin(), matrix.end(), [&] (const std::string &s) { ss << s; });
        ss >> line;
        ptn.raw = std::string(line.begin(), line.end());
        std::cout << "at " << ptn.pos.first << ", "
                  << ptn.pos.second << " with raw:" << ptn.raw << std::endl;
        rawPatterns.insert(ptn);
        auto row = matrix.size(), col = matrix.front().size();
        fillthemap(patterns[std::make_pair(row, col)], ptn.raw, ptn.pos);
    }
    for (auto &item : patterns) {
        std::cout << std::endl << item.first.first << "x" << item.first.second << ": " << std::endl;
        for (auto &it : item.second) {
            std::cout << it.first << " - (" << it.second.first
                  << ", " << it.second.second << ")" << std::endl;
        }
    }
    std::cout << "Initialization done" << std::endl;
}

void PatternRecognizer::fillthemap(std::map<std::string, std::pair<int, int>> &map,
                                   std::string &str, const std::pair<int, int> &p) {

    auto pos = str.find_first_of('#');
    if (pos == std::string::npos) {
        map[str] = p;
    } else {
        str[pos] = '_';
        fillthemap(map, str, p);
        str[pos] = 'x';
        fillthemap(map, str, p);
        str[pos] = 'o';
        fillthemap(map, str, p);
        str[pos] = '#';
    }
}

Position PatternRecognizer::query(const int board[TS][TS]) {

    unsigned row(0), col(0);
    std::string strseq;
    char c;

    for (int i = 0; i < TS; ++i) {
        for (int j = 0; j < TS; ++j) {
            std::cout << board[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    unsigned sum(0);
    for (auto &pt : patterns) {
        row = pt.first.first;
        col = pt.first.second;
        for (unsigned i = 0; i <= TS - row; ++i) {
            for (unsigned j = 0; j <= TS - col; ++j) {

                for (unsigned k = i; k < row + i; ++k) {
                    for (unsigned l = j; l < col + j; ++l) {
                        switch(static_cast<char>(board[k][l])) {  // black: 1  white: -1
                            case  0: c = '_'; break;
                            case  1: c = 'x'; break;
                            case -1: c = 'o'; break;
                        }
                        strseq.append(1, c);
                    }
                }
                auto element = pt.second.find(strseq);
                std::cout << std::boolalpha
                          << ++sum << ". "
                          << (element != pt.second.end())
                          << " " << row << "x" << col << ": " << strseq << std::endl
                          << std::noboolalpha;
                strseq.clear();
            }
        }

    }
    return {-1, -1};
}
