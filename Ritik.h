#ifndef DSPDR3_RITIK_H
#define DSPDR3_RITIK_H

#include <stdlib.h>
#include<stdio.h>

#include "datastructs.h"
void init_ledger(ledger *pq);
status add_rat(ledger *pq,int cost);
status add_node(rat *block, int x,int y);
int travel(ledger *pq, int i,int max);
int choose_action(int action[],rat *jerry);
int is_possible(node *path,int x,int y,int cost);
status delete_rat(ledger *pq,rat *dead);
status remove_rat(ledger *pq,rat *dead);
int take_action(rat *jerry,int choice);//return new cost
rat *split(rat *mouse);
void move_rat(ledger *pq,rat *jerry, int new_cost);
void print_path(ledger *pq,FILE *fptr);
void path_print(node *head,FILE *fptr);
void read_inp();
void take_maze_input();
void disp_path();
void critical_path_print();


#endif //DSPDR3_RITIK_H
