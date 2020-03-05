//
// Created by ritik on 04/03/20.
//

#include "Ritik.h"


extern matrix[12][10];
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
    new->next=pq->priority[cost];
    pq->priority[cost]=new;
}

void add_node(rat *block, int x, int y) {
    node *new= malloc(sizeof(node));
    new->x=x;
    new->y=y;
    new->next = block->path;
    block->path=new;
    block->steps=block->steps+1;
}

void travel(ledger *pq, int i) {
    rat *jerry=pq->priority[i];
    while(jerry !=NULL){
        int action_choises=0;
        node *path = jerry->path;
        int x=path->x;
        int y=path->y;
        int action[4]={0};
        action_choises=choose_action(action,x,y,path);

        if(action_choises==0){
            rat *dead=jerry;
            jerry=jerry->next;
            delete_rat(pq,dead);
        }
        else if (action_choises == 1){
            int choice=0;
            for (int i = 0; i < 4; ++i) {
                if(action[i]==1){
                    choice=i+1;
                }
            }
            int new_cost=take_action(jerry,choice);
            if(new_cost!=jerry->cost){
                rat *temp=jerry;
                jerry=jerry->next;
                move_rat(pq,temp,new_cost);
            } else{
                jerry=jerry->next;
            }

        }
        else if (action_choises == 2){
            int c1,c2,flag=0;

            for (int i = 0; i < 4 && flag==0; ++i) {
                if(action[i]==1){
                    c1=i+1;
                    flag=1;
                }
            }
            for (int i = c1; i < 4; ++i) {
                if(action[i]==1){
                    c2=i+1;
                }
            }
            rat *tom=split(jerry);//inserting new rat just after the previous one
            int new_costJ=take_action(jerry,c1);
            int new_costT=take_action(tom,c2);
            if(new_costJ!=jerry->cost){
                rat *temp=jerry;
                jerry=jerry->next;
                move_rat(pq,temp,new_costJ);
            } else{
                jerry=jerry->next;
            }
            tom->next=pq->priority[new_costT];
            pq->priority[new_costT]=tom;
            tom->cost=new_costT;

        }
        else if(action_choises==3){
            int ac[3],j=0;
            for (int ik = 0; ik < 4; ++ik) {
                if(action[ik]!=0){
                    ac[j]=ik+1;
                    j++;
                }
            }
            rat *kani=split(jerry);
            rat *soni = split(jerry);
            int costJ=take_action(jerry,ac[0]);
            int costK=take_action(kani,ac[1]);
            int costS=take_action(soni,ac[2]);
            if(costJ!=jerry->cost){
                rat *temp=jerry;
                jerry=jerry->next;
                move_rat(pq,temp,costJ);
            } else{
                jerry=jerry->next;
            }
            kani->next=pq->priority[costK];
            pq->priority[costK]=kani;
            soni->next=pq->priority[costS];
            pq->priority[costS]=soni;


        }

    }

}

int choose_action(int *action, int x, int y, node *path) {
    int x1=x+1,y1=y+1,x2=x-1,y2=y-1;
    action[0] = is_possible(path,x,y2);//left
    action[1] = is_possible(path,x,y1);//right
    action[2]=is_possible(path,x2,y);//up
    action[3]=is_possible(path,x1,y);//down
    int len=0;
    for (int i = 0; i < 4; ++i) {
        if(action[i]==1){
            len++;
        }
    }
    return len;
}

int is_possible(node *path, int x, int y) {
    int ret=0;
    int x_back=-1,y_back=-1;
    if(path->next!=NULL){
        x_back=path->next->x, y_back=path->next->y;
    }

    if(x != x_back || y !=y_back){
        if(matrix[x][y]!=-1){
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
    int ret=jerry->cost;
    int x,y;
    switch (choice){
        case 1://left

            x = jerry->path->x;
            y=jerry->path->y-1;
            add_node(jerry,x,y);
            ret=jerry->cost+matrix[x][y];
            break;
        case 2://right

            x= jerry->path->x;
            y=jerry->path->y+1;
            add_node(jerry,x,y);
            ret=jerry->cost+matrix[x][y];
            break;
        case 3://up

            x= jerry->path->x-1;
            y=jerry->path->y;
            add_node(jerry,x,y);
            ret=jerry->cost+matrix[x][y];
            break;
        case 4://down

            x= jerry->path->x+1;
            y=jerry->path->y;
            add_node(jerry,x,y);
            ret=jerry->cost+matrix[x][y];
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



























