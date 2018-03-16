//
// Created by cat on 18-1-30.
//

#ifndef GOBANG_STAGE_H
#define GOBANG_STAGE_H

#include <vector>
#include "actor.h"

using std::string;
using std::vector;

typedef actor *pactor;

class stage {

public:

    explicit stage(const string &name);

    ~stage();

    void addActor(actor &a);

    void drawAll();
    void deleteAll();
    void hideAll();

    void hideActorById(int id);
    void hideActorByName(const string &name);

    actor &getActorById(int id);
    actor &getActorByName(const string &name);

    bool deleteActorById(int id);
    bool deleteActorByName(const string &name);

    size_t getActorNums();

private:
    string name;
    vector<pactor> pactors;
};

#endif //GOBANG_STAGE_H
