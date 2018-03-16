#include <iostream>
#include "chessman.h"

using std::clog;
using std::endl;

chessman::chessman(string name, position pos) : actor(name, pos) {
    ;
}

chessman::~chessman() {
    ;
}

int chessman::doDraw() {
    clog << "(chessman)" << this->name << " : draw." << endl;
    return actor::doDraw();
}

void chessman::doHide() {
    clog << "(chessman)" << this->name << " : hide." << endl;
    return actor::doHide();
}

