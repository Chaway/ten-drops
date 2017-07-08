#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

struct Drop{
    int val[4];
    int sum;
};

void print_Matrix(int (*m)[6]){
    for (int i = 0; i < 6; i++){
        printf("\n row %d : ",i+1);
        for (int j = 0; j < 6; j++){
            printf("%d  ",m[i][j]);
        }
    }
    printf("\n");
}

void print_drops(struct Drop (*drops)[8]){
    for (int i = 1; i < 7; i++){
        printf("\n row %d : ",i);
        for (int j = 1; j < 7; j++){
            printf("%d  ",drops[i][j].sum);
        }
    }
}

void initial_drops(int row,int col,struct Drop (*drops)[8]){
    drops[row-1][col].val[0] = 1;
    drops[row+1][col].val[1] = 1;
    drops[row][col-1].val[2] = 1;
    drops[row][col+1].val[3] = 1;
    drops[row-1][col].sum ++;
    drops[row+1][col].sum ++;
    drops[row][col-1].sum ++;
    drops[row][col+1].sum ++;
}
int is_complete(int (*m)[6]){
    for (int i = 0;i < 6;i++){
        for(int j=0; j < 6;j++){
            if(m[i][j] > 0)
            return 1;
        }
    }
    return 0;

}

int is_empty(struct Drop (*drops)[8]){
    for (int i = 1; i < 7; i++){
        for (int j = 1; j < 7; j++){
            if (drops[i][j].sum != 0)
                return 1;
        }
    }
    return 0;
}

void process_matrix(int row,int col,int (*m)[6]){
    if (m[row-1][col-1] < 4){
        m[row-1][col-1] ++;
        return;
    }
    else{
        struct Drop drops[8][8]= {0};
        struct Drop next_drops[8][8]= {0};
        m[row-1][col-1] = 0;
        initial_drops(row,col,drops);
        while(is_empty(drops)){
            //print_drops(drops);
            for (int i = 0; i < 6; i++){
                for (int j = 0; j < 6; j++){
                    int weight = m[i][j] + drops[i+1][j+1].sum;
                    // absorb drops
                    if (m[i][j] == 0){
                        next_drops[i][j+1].val[0] = drops[i+1][j+1].val[0];
                        next_drops[i+2][j+1].val[1] = drops[i+1][j+1].val[1];
                        next_drops[i+1][j].val[2] = drops[i+1][j+1].val[2];
                        next_drops[i+1][j+2].val[3] = drops[i+1][j+1].val[3];
                    }
                    else if ( weight < 4 || weight == 4){
                        m[i][j] = weight;
                    }
                    else if (weight > 4){
                        m[i][j] = 0;
                        next_drops[i][j+1].val[0] = 1;
                        next_drops[i+2][j+1].val[1] = 1;
                        next_drops[i+1][j].val[2] = 1;
                        next_drops[i+1][j+2].val[3] = 1;
                    }
                    /*
                    else if (weight == 6){
                        //printf("\n 6 drops! \n");
                        //assert(0);
                        int filled[drops[i+1][j+1].sum];
                        int inf = 0;
                        for (int t = 0; t < 4; t++){
                            if (drops[i+1][j+1].val[t] > 0){
                                filled[inf] = t;
                                inf ++;
                            }
                         }                        
     		            srand((unsigned)time(NULL));
                        int ran = rand()%inf;


                        for (int t = 0; t < 4; t++){
                               if (drops[i+1][j+1].val[t] > 0){
                                     filled[inf] = t;
                                     inf ++;
                               }
                         }

                        m[i][j] = 0;
                        next_drops[i][j+1].val[0] = 1;
                        next_drops[i+2][j+1].val[1] = 1;
                        next_drops[i+1][j].val[2] = 1;
                        next_drops[i+1][j+2].val[3] = 1;

                        switch filled[ran]:
                          case 0:
                              next_drops[i][j+1].val[0] ++;
                              break;
                          case 1:
                              next_drops[i+2][j+1].val[1] ++;
                              break;
                          case 2:
                              next_drops[i+1][j].val[2] ++;
                              break;
                          case 3:
                              next_drops[i+1][j+2].val[3] ++;
                              break;
                    }
                    else{
                        printf("\n drops exceed 7 \n");
                        assert(0);
                    }*/
                }
            }
            for (int i = 0; i < 6; i++){
                for (int j = 0; j < 6; j++){
                    int sum = 0;
                    for (int t = 0; t < 4; t++)
                    {
                        drops[i+1][j+1].val[t] = next_drops[i+1][j+1].val[t];
                        sum = sum + next_drops[i+1][j+1].val[t];
                    }
                    drops[i+1][j+1].sum = sum;
                }
            }
        }
    }
}



int main(){
    int m[6][6] = {{2,3,2,3,4,4},{4,3,2,2,4,4},{0,1,1,0,4,3},{2,0,4,4,3,2},{4,2,3,2,0,0},{1,0,2,3,3,0}};
    printf("Input game matrix:\n");
 /*   for (int i = 0; i < 6; i++){
        printf("row %d : \n",i+1);
        for (int j = 0; j < 6; j++){
            scanf("%d",&m[i][j]);
        }

    }
*/
    printf("\nInitial Matrix: \n");
    print_Matrix(m);
    printf("\n");
    int times = 0;
    while(is_complete(m)){
        ++times;
        printf("\nInput Element location: \n");
        int row,col;
        scanf("%d",&row);scanf("%d",&col);
        process_matrix(row,col,m);
        printf("\nAfter No.%d process: \n",times);
        print_Matrix(m);
    }

    printf("\n Game Over! \n");
    return 0;
}
