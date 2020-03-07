//
// Created by ritik on 04/03/20.
//

#include "Ritik.h"

extern int done;
extern int matrix[12][10];
void init_ledger(ledger *pq) {
    for (int i = 0; i < 100; ++i) {
        pq->priority[i]=NULL;
    }
    add_rat(pq, 0);
    add_node(pq->priority[0],1,1);
}

void add_rat(ledger *pq, int cost) {
    rat *new=malloc(sizeof(rat));
    new->steps=0;
    new->path=NULL;
    new->cost=cost;
    new->done=0;
    new->next=pq->priority[cost];
    pq->priority[cost]=new;

}

void add_node(rat *block, int x, int y) {
    node *new= malloc(sizeof(node));
    new->x=x;
    new->y=y;
    new->next = block->path;
    block->path=new;
    block->steps=(block->steps)+1;
}

int travel(ledger *pq, int i,int max) {
    int ret = max;
    rat *jerry = pq->priority[i];
    while(jerry!=NULL){
        if(jerry->done == 1){

            if(jerry->cost <=ret){
                ret=jerry->cost;
            }
            jerry=jerry->next;
        }
        else{
            int action_len=0;
            int action[4]={0};
            action_len=choose_action(action,jerry);

            if(action_len == 0){
                rat *temp=jerry;
                jerry=jerry->next;
                delete_rat(pq,temp);
            } else if (action_len == 1){
                int act=0;
                for (int j = 0; j < 4; ++j) {
                    if(action[j]==1){
                        act = j+1;
                    }
                }
                int new_cost=take_action(jerry,act);
                if(new_cost != jerry->cost){
                    rat *temp=jerry;
                    jerry=jerry->next;
                    move_rat(pq,temp,new_cost);
                } else{
                    jerry=jerry->next;
                }

            } else if (action_len==2){
                int c[2]={0}, k=0;
                for (int j = 0; j < 4; ++j) {
                    if(action[j]==1){
                        c[k]=j+1;
                        k++;
                    }
                }
                rat *tom=split(jerry);
                int cost_jerry=take_action(jerry,c[0]);
                int cost_tom=take_action(tom,c[1]);
                if(cost_jerry != jerry->cost){
                    rat *temp=jerry;
                    jerry=jerry->next;
                    move_rat(pq,temp,cost_jerry);
                }else{
                    jerry=jerry->next;
                }
                tom->cost=cost_tom;
                tom->next=pq->priority[cost_tom];
                pq->priority[cost_tom]=tom;
            } else if(action_len == 3){
                int c[3]={0}, k=0;
                for (int j = 0; j < 4; ++j) {
                    if(action[j]==1){
                        c[k]=j+1;
                        k++;
                    }
                }
                rat *tom=split(jerry);
                rat *mickey=split(jerry);
                int cost_jerry=take_action(jerry,c[0]);
                int cost_tom=take_action(tom,c[1]);
                int cost_mickey=take_action(mickey,c[2]);
                if(cost_jerry != jerry->cost){
                    rat *temp=jerry;
                    jerry=jerry->next;
                    move_rat(pq,temp,cost_jerry);
                }else{
                    jerry=jerry->next;
                }
                tom->cost=cost_tom;
                tom->next=pq->priority[cost_tom];
                pq->priority[cost_tom]=tom;
                mickey->cost=cost_mickey;
                mickey->next=pq->priority[cost_mickey];
                pq->priority[cost_mickey]=mickey;
            }



        }
    }

    return ret;
}

int choose_action(int *action,rat *jerry) {
    int x=jerry->path->x, y=jerry->path->y;
    node *path=jerry->path;
    int cost=jerry->cost;
    int x1=x+1,y1=y+1,x2=x-1,y2=y-1;
    action[0] = is_possible(path,x,y2,cost);//left
    action[1] = is_possible(path,x,y1,cost);//right
    action[2]=is_possible(path,x2,y,cost);//up
    action[3]=is_possible(path,x1,y,cost);//down
    int len=0;
    for (int i = 0; i < 4; ++i) {
        if(action[i]==1){
            len++;
        }
    }
    return len;
}

int is_possible(node *path, int x, int y,int cost) {
    int ret=0;
    int x_back=-1,y_back=-1;
    if(path->next!=NULL){
        x_back=path->next->x, y_back=path->next->y;
    }

    if(x != x_back || y !=y_back){
        if(matrix[x][y]!=-1 && matrix[x][y] > cost){
            ret=1;
        }
    }
    return ret;
}

void delete_rat(ledger *pq, rat *dead) {
    node *path=dead->path;
    node *fr;
    while(path!=NULL){
        fr=path;
        path=path->next;
        free(fr);
    }
    remove_rat(pq,dead);
}

void remove_rat(ledger *pq, rat *dead) {
    int index=dead->cost;
    rat *prev=pq->priority[index];
    if(prev==dead){
        pq->priority[index]=dead->next;
        free(dead);
    }
    else{
        while(prev->next!=dead){
            prev=prev->next;
        }
        prev->next=dead->next;
        free(dead);
    }
}

int take_action(rat *jerry, int choice) {
    jerry->path->action=choice;
    int mx=jerry->path->x, my=jerry->path->y;
    if(matrix[mx][my] != 122){
        matrix[mx][my]=jerry->cost;
    }

    int ret=jerry->cost;
    int x,y;
    switch (choice){
        case 1://left

            x = jerry->path->x;
            y=jerry->path->y-1;
            add_node(jerry,x,y);
            if(matrix[x][y] == 122){
                ret+=1;
            }
            if(matrix[x][y]==1000){
                jerry->done=1;
            }
            break;
        case 2://right

            x= jerry->path->x;
            y=jerry->path->y+1;
            add_node(jerry,x,y);
            if(matrix[x][y] == 122){
                ret+=1;
            }
            if(matrix[x][y]==1000){
                jerry->done=1;
            }
            break;
        case 3://up

            x= jerry->path->x-1;
            y=jerry->path->y;
            add_node(jerry,x,y);
            if(matrix[x][y] == 122){
                ret+=1;
            }
            if(matrix[x][y]==1000){
                jerry->done=1;
            }
            break;
        case 4://down

            x= jerry->path->x+1;
            y=jerry->path->y;
            add_node(jerry,x,y);
            if(matrix[x][y] == 122){
                ret+=1;
            }
            if(matrix[x][y]==1000){
                jerry->done=1;
            }
            break;
        default:
            break;
    }
    return ret;
}

rat *split(rat *mouse) {
    rat *kid=malloc(sizeof(rat));
    kid->next=NULL;
    kid->path=NULL;
    kid->steps=mouse->steps;
    kid->cost=mouse->cost;
    kid->done=mouse->done;
    node *ptr=mouse->path;
    node *kidptr=kid->path;
    while(ptr!=NULL){
        node *new=malloc(sizeof(node));
        if(new != NULL){
            new->y=ptr->y;
            new->x=ptr->x;
            new->action=ptr->action;
            new->next=NULL;
            if(kidptr == NULL){
                kid->path=new;
                kidptr=new;
            } else{
                kidptr->next=new;
                kidptr=new;
            }
            ptr=ptr->next;
        }
        else{
            printf("Go to Hell\n");
        }

    }
    return kid;
}

void move_rat(ledger *pq, rat *jerry, int new_cost) {
    int index=jerry->cost;
    rat *prev= pq->priority[index];
    if(prev!=jerry){
        while(prev->next!=jerry){
            prev=prev->next;
        }
        prev->next=jerry->next;
    } else if(prev == jerry){
        pq->priority[index]=jerry->next;
    }
    jerry->cost=new_cost;
    jerry->next=pq->priority[new_cost];
    pq->priority[new_cost]=jerry;


}

void print_path(ledger *pq,FILE *fptr) {
    int flag =0;
    for (int i = 0; i < 100 && flag==0; ++i) {
        rat *ptr=pq->priority[i];
        while (ptr!=NULL && flag==0){
            if(ptr->done==1){
                path_print(ptr->path->next,fptr);
                flag=1;
            }
            ptr=ptr->next;
        }
    }
}

void path_print(node *head,FILE *fptr) {
    if(head !=NULL){
        path_print(head->next,fptr);
        int action=head->action;
        switch (action){
            case 1:
                fprintf(fptr,"action:Left,position(%d,%d)\n",head->x,head->y);
                break;
            case 2:
                fprintf(fptr,"action:Right,position(%d,%d)\n",head->x,head->y);
                break;
            case 3:
                fprintf(fptr,"action:Up,position(%d,%d)\n",head->x,head->y);
                break;
            case 4:
                fprintf(fptr,"action:Down,position(%d,%d)\n",head->x,head->y);
                break;
            default:
                break;
        }

    }
}
void disp_path() {
    char buffer[10000];
    FILE *fptr=fopen("PATH.txt","r");
    while(fscanf(fptr,"%s",buffer) != EOF){
        printf("%s\n",buffer);
    }
    fclose(fptr);
}



void read_inp() {
    FILE *fptr;
    fptr = fopen("input.txt","r");
    if(fptr != NULL){
        for (int i = 0; i < 12; ++i) {
            for (int j = 0; j < 10; ++j) {
                fscanf(fptr,"%d",&matrix[i][j]);
            }
        }
    }
    fclose(fptr);

}

void take_maze_input() {
    FILE *fptr;
    int n;
    fptr=fopen("input.txt","w");
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 10; ++j) {
            scanf("%d",&n);
            fprintf(fptr,"%d ",n);
        }
        fprintf(fptr,"\n");
    }
    fclose(fptr);
}

