#ifndef GOBANG2_H
#define GOBANG2_H

#define MAX_INT (((unsigned)(-1)) >> 1)
#define MIN_INT (MAX_INT + 1)

#define INCECO 10

#define TS     15
#define CON    5

#define DEP    2
#define RUL    "rules.txt"

#define GT     0
#define PL     0

typedef enum {
    Nil = 0, Black = 1, White = -1
} Oval;

typedef struct {
    int weight;
    Oval val;
} Grid;

typedef struct {
    Grid grids[TS][TS];
    int score;
    int ngrid;
} Board;

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Oval val;
    Oval who;
    int  score;
} Rule;

typedef struct GameTree {
    struct GameTree *prev;
    struct GameTree **branch;
    int _nbranch;
    long _sleaf;
    int depth;
    int nleaf;
    void *leaf;
} GTree;

int test();

Point  workout(Board *, const int, Board **);
int    down(Board *, const Oval, const int, const int);
GTree *init_rules(const char *);
int    evaluate(Board *);
int    isfinish(Board *, const int, const int);

Board *bd_cpy(const Board *);
Board *bd_cre(const int [TS][TS]);

void   gt_prt(GTree *const, const int);
GTree *gt_cre(const void *, const long);
GTree *gt_add(GTree *const, const void *, const long);
void   gt_del(GTree *);

#endif // GOBANG2_H
