#include <stdio.h>
#include <stdlib.h>
#include "Ritik.h"

int matrix[12][10]= {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -5, 120, 120, 122, 122, 120, 120, 120, -1, -1, 120, -1, -1, -1, 120, -1,
                     -1, 122, -1, -1, 122, 122, 122, 122, 122, 120, 120, 122, -1, -1, -1, 120, 120, 120, -1, 120, 120, -1, -1, -1, 120, -1, -1, 122, -1,
                     122, -1, -1, -1, -1, -1, 120, 120, 120, 120, 122, 120, 120, -1, -1, 120, -1, 120, -1, 122, 122, -1, 120, -1, -1, -1, -1, 120,
                     -1, 122, -1, -1, -1, -1, -1, 120, 122, 122, -1, 122, 122, 120, 120, -1, -1, 120, -1, 120, 120, 122, 122, -1, 1000, -1, -1, -1,
                     -1, -1, -1, -1, -1, -1, -1, -1};
int done;

void take_choise(int *user_choise);

int main() {


    ledger pq;
    init_ledger(&pq);
    int max=100;
    done=0;
    int user_choise;
    do{
        printf("######################################################################\n");
        printf("1.Enter your own maze\n");
        printf("2.Solve the maze\n");
        printf("3.Print the solution\n");
        printf("4.Exit\n");
        take_choise(&user_choise);
        printf("######################################################################\n");
        switch (user_choise){
            case 1:
                take_maze_input();
                break;
            case 2:
                read_inp();
                while(!done){
                    done=1;
                    for (int i = 0; i < max; ++i) {
                        if(pq.priority[i]!=NULL){
                            done=0;
                            max = travel(&pq,i,max);
                        }
                    }
                }
                FILE *fptr;
                fptr = fopen("PATH.txt","w");
                print_path(&pq,fptr);
                fclose(fptr);
                break;
            case 3:
                disp_path();
            default:
                break;
        }
    }while (user_choise !=4);




    return 0;
}

void take_choise(int *user_choise) {
    do{
        printf("Enter the appropriate number: ");
        scanf("%d", user_choise);
    }while((*user_choise) < 1 || (*user_choise) > 4);
}
