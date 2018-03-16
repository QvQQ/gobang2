#include "chessboard.h"

chessboard::chessboard(string name, position pos) : actor(name, pos) {
    ;
}

chessboard::~chessboard(){
    ;
}

int chessboard::doDraw() {
    return actor::doDraw();
}

void chessboard::doHide() {
    return actor::doHide();
}
