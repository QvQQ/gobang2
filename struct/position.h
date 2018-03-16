#ifndef POSITION_H
#define POSITION_H

#include <ostream>

using std::ostream;

struct position {
    int x = 0, y = 0;

    position(int x, int y);
    friend ostream &operator<<(ostream &out, const position &p);
};

#endif // POSITION_H
