//
// Created by ritik on 04/03/20.
//

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
    int steps;
    node *path;
    struct rat_tag *next;
}rat;

typedef struct ledger_tag{
    rat *priority[100];
}ledger;






















#endif //DSPDR3_DATASTRUCTS_H

