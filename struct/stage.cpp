#include <iostream>
#include <vector>
#include <memory>
#include "actor.h"
#include "stage.h"

using std::clog;
using std::endl;
using std::vector;
using std::string;
using std::unique_ptr;

typedef actor *pactor;

stage::stage(const string &name) : name(name) {
    clog << "(stage)" << this->name << " : constructor." << endl;
}

stage::~stage() { clog << "(stage)" << this->name << " : destructor." << endl; }

void stage::addActor(actor &a) {
    this->pactors.emplace_back(&a);
    clog << "(stage)" << this->name << " add one actor : [" << a.getId() << "] " << a.getName() << a.getPostion() << endl;
}

void stage::drawAll() {
    for (auto &pactor : this->pactors)
        pactor->doDraw();
}

void stage::deleteAll() {
    this->pactors.clear();
}

void stage::hideAll() {
    for (auto &pactor : this->pactors)
        pactor->doHide();
}

void stage::hideActorById(int id) {
    for (auto &pactor : this->pactors) {
        if (pactor->getId() == id) {
            pactor->doHide();
            clog << "(stage)" << this->name << " hide one actor : [" << pactor->getId() << "] " << pactor->getName() << pactor->getPostion() << endl;
        }
    }
    throw "id not found.";
}

void stage::hideActorByName(const string &name) {
    for (auto &pactor : this->pactors) {
        if (pactor->getName() == name) {
            pactor->doHide();
            clog << "(stage)" << this->name << " hide one actor : [" << pactor->getId() << "] " << pactor->getName() << pactor->getPostion() << endl;
        }
    }
    throw "name not found.";
}

actor &stage::getActorById(int id) {
    for (auto &pactor : this->pactors) {
        if (pactor->getId() == id) {
            clog << "(stage)" << this->name << " found one actor : [" << pactor->getId() << "] " << pactor->getName() << pactor->getPostion() << endl;
            return *pactor;
        }
    }
    throw "id not found.";
}

actor &stage::getActorByName(const string &name) {
    for (auto &pactor : this->pactors) {
        if (pactor->getName() == name) {
            clog << "(stage)" << this->name << " found one actor : [" << pactor->getId() << "] " << pactor->getName() << pactor->getPostion() << endl;
            return *pactor;
        }
    }
    throw "name not found.";
}

bool stage::deleteActorById(int id) {
    for (auto iter = this->pactors.begin(); iter != this->pactors.end(); ++iter) {
        if ((*iter)->getId() == id) {
            (*iter)->doHide();
            clog << "(stage)" << this->name << " del one actor : [" << (*iter)->getId() << "] " << (*iter)->getName() << (*iter)->getPostion() << endl;
            this->pactors.erase(iter);
            return true;
        }
    }
    return false;
}

bool stage::deleteActorByName(const string &name) {
    for (auto iter = this->pactors.begin(); iter != this->pactors.end(); ++iter) {
        if ((*iter)->getName() == name) {
            (*iter)->doHide();
            clog << "(stage)" << this->name << " del one actor : [" << (*iter)->getId() << "] " << (*iter)->getName() << (*iter)->getPostion() << endl;
            this->pactors.erase(iter);
            return true;
        }
    }
    return false;
}

size_t stage::getActorNums() {
    clog << "(stage)" << this->name << " get actor nums : " << this->pactors.size() << endl;
    return this->pactors.size();
}
