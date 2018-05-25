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
        str[pos] = 'x';
        fillthemap(map, str, p);
        str[pos] = 'o';
        fillthemap(map, str, p);
        str[pos] = '#';
    }
}
