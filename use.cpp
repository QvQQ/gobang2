#include <iostream>

#include "instance/chessboard.h"
#include "instance/chessman.h"
#include "struct/stage.h"

using std::cout;
using std::endl;

void test(stage &s);

int use() {

    stage stage1("stage1");

    chessman chessman1("chessman1", position(2, 3));
    chessman chessman2("chessman2", position(20, 30));
    chessman chessman3("chessman3", position(200, 300));

    //chessman1.setName("cm2333");

    stage1.addActor(chessman1);
    stage1.addActor(chessman2);
    stage1.addActor(chessman3);

    stage1.drawAll();
    stage1.hideAll();

    stage1.deleteActorByName("chessman2");
    stage1.getActorByName("chessman3").setPostion(22, 33);
    stage1.getActorByName("chessman3").setPostion(position(222, 333));

    test(stage1);

    return 0;
}

void test(stage &s){

    chessman *c1 = dynamic_cast<chessman*>(&s.getActorByName("chessman3"));
    c1->doDraw();
    s.deleteAll();

}
