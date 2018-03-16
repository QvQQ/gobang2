//
// Created by cat on 18-1-30.
//

#ifndef GOBANG_ACTOR_H
#define GOBANG_ACTOR_H

#include "position.h"

using std::string;

class actor {

public:

    actor(const string &name, position pos);
    ~actor();

    virtual int doDraw();
    virtual void doHide();

    void setPostion(const position pos);
    void setPostion(int x, int y);
    void setName(const string &name);

    bool isVisible();

    const string &getName();
    const position &getPostion();

    static int getTotal() {
        return actor::total;
    }
    int getId();

private:
    int id;
    static int total;

protected:
    string name;
    position pos;
    bool visible = false;
};

#endif //GOBANG_ACTOR_H
