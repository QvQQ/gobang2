#include <ostream>
#include "position.h"

using std::ostream;

position::position(int x, int y) : x(x), y(y) {}

ostream &operator<<(ostream &out, const position &p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}
