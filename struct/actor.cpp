#include <string>
#include <iostream>
#include "position.h"
#include "actor.h"

using std::clog;
using std::endl;
using std::string;

actor::actor(const string &name, position pos) : id(this->total++), name(name), pos(pos) {
    clog << "(actor)[" << this->id << "] " << this->name << " : constructor at " << pos << endl;
}

actor::~actor() {
    total--;
    clog << "(actor)[" << this->id << "] " << this->name << " : destructor." << endl;
}

int actor::doDraw() {
    this->visible = true;
    clog << "(actor)[" << this->id << "] " << this->name << " : draw at " << this->pos << endl;
    return 0;
}

void actor::doHide() {
    this->visible = false;
    clog << "(actor)[" << this->id << "] " << this->name << " : hide." << endl;
}

void actor::setPostion(const position pos) {
    clog << "(actor)[" << this->id << "] " << this->name << " : set pos from " << this->pos << " to " << pos << endl;
    this->pos.x = pos.x;
    this->pos.y = pos.y;
}

void actor::setPostion(int x, int y) {
    clog << "(actor)[" << this->id << "] " << this->name << " : set pos from " << this->pos << " to (" << x << " ," << y << ")" << endl;
    this->pos.x = x;
    this->pos.y = y;
}

void actor::setName(const string &name) {
    clog << "(actor)[" << this->id << "] " << this->name << " : set name \"" << name << "\"" << endl;
    this->name = name;
}

bool actor::isVisible() {
    return this->visible;
}

const string &actor::getName() {
    return this->name;
}

const position &actor::getPostion() {
    return this->pos;
}

int actor::getId() {
    return this->id;
}

int actor::total = 0;
