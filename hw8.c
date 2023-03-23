#include <stdio.h>
#include<stdbool.h>
#define SIZE 9

void initArray(int x[][9],int size,FILE *set){
    int i,j;
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            x[i][j] = 0; //fscanf(set,"%d",&x[i][j]);
        }
    }
}

void readSudoku(int x[][9], FILE *inp){// reads a sudoku file into array x
    int i,j;
    
    for(i = 0;i<SIZE;++i){
        for(j = 0;j<SIZE;++j){
            fscanf(inp,"%d",&x[i][j]);
        }
    }
}

void printSudoku(int x[][9]){ // prints a soduko board
    int i,j,k,l;
    for (l=0;l<3;l++){
     for(k=0;k<3;k++){
        for(i=0;i<3;i++){
            for(j=0;j<3;j++){
                printf("%d",x[i+l][j+k]);
            }
            if((i==0)||(i==1)){
                printf("|");
            }        
        }
        printf("\n");
     }
     if((l==0)||(l==1)){
      printf("-----------");
     }
     printf("\n");
    }
}

bool checknum(int x[][9],int y[][9]){
    int i,j;
    bool failed = true;
     for(i=0; i<SIZE; i++){
        for(j=0; j<SIZE; j++){
            if((x[i][j]!=0)&&(x[i][j]!=y[i][j])){
                failed = false;
            }
        }
    }
    return failed;
}

bool checkSudoku(int x[][9]){ // returns true if x is a valid sudoku boards and false otherwise
    int i,j,k,l,sum=0;
    bool condition = true;

    for(i=0; i<SIZE; i++){
        for(j=0; j<SIZE; j++){
            sum += x[i][j];
        }
        if(sum != 45){
            condition = false;
        }
         sum = 0;
    }

    for(i=0; i<SIZE; i++){
        for(j=0; j<SIZE; j++){
            sum =sum + x[j][i];
        }
        if(sum != 45){
            condition = false;
        }
         sum = 0;
    }

    //repeat for 9 subgrids box
    for(l=0; l<3; l++){
        for(k=0; k<3; k++){
            
            //find the sum of each 3 by 3 subgrids
            for(i=0; i<3; i++){
                for(j=0; j<3; j++){
                    sum += x[i+l*3][j+k*3];
                }
            }
                
                if(sum != 45){
                condition = false;
                }
                sum = 0;
        }
    }

    return condition;
}

int main(void){
    int row,colum;
    int sudoku[SIZE][SIZE];
    int board[SIZE][SIZE];// sudoku is a two dimensional array that holds all the values of the board
    FILE *inp;
    bool valid,outcome=false;
    inp = fopen("sudoku1.txt", "r");
    
    if (inp == NULL){
        return -1;
    }
    else{

        readSudoku(sudoku,inp);
        initArray(board,9);
        printSudoku(board);
        do{
             select(board,row,colum);
             checknum(board,sudoku);
        }while(outcome);
        valid = checkSudoku(sudoku);
        if(valid){
            printf("This is a valid sudoku puzzle.\n");
        }
        else{
            printf("This is not a valid sudoku puzzle.\n");
        }
    }
}




