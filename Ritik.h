//
// Created by ritik on 04/03/20.
//

#ifndef DSPDR3_RITIK_H
#define DSPDR3_RITIK_H

#include <stdlib.h>

#include "datastructs.h"
void init_ledger(ledger *pq);
void add_rat(ledger *pq,int cost);
void add_node(rat *block, int x,int y);
void travel(ledger *pq, int i);
int choose_action(int action[],int x,int y,node *path);
int is_possible(node *path,int x,int y);
void delete_rat(ledger *pq,rat *dead);
void remove_rat(ledger *pq,rat *dead);
int take_action(rat *jerry,int choice);//return new cost
rat *split(rat *mouse);
void move_rat(ledger *pq,rat *jerry, int new_cost);
#endif //DSPDR3_RITIK_H
