#ifndef DSPDR3_DATASTRUCTS_H
#define DSPDR3_DATASTRUCTS_H




typedef struct node_tag{
    int x;
    int y;
    int action;
    struct node_tag *next;
}node;

typedef struct rat_tag{
    int cost;
    int done;
    int steps;
    node *path;
    struct rat_tag *next;
}rat;

typedef struct ledger_tag{
    rat *priority[100];
}ledger;
typedef enum status_code{failure,success}status;

typedef struct dlnode_tag{
    int x;
    int y;
    struct dlnode_tag *next;
    struct dlnode_tag *prev;
}dlnode;




















#endif //DSPDR3_DATASTRUCTS_H
