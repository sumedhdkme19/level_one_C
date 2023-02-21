#include<stdio.h>

struct sudukoboard{
    int board[9][9];
    int submatrix[9][9];
};
typedef struct sudukoboard sboard;

sboard input_board(){ //Inputs a 9X9 2D matrix representing a suduko board
    sboard s;
    for (int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            scanf("%d",&s.board[i][j]);
        }
    }
    return s;
}

void get_submatrix(sboard *s) // gets all the 9 sub-matrices of a suduko board in a 1X9 1D array form
{ 
    /*The logic of the nested-loop iterations is such that it starts from the left
    top corner sub-matrix then moves vertically down covering the remaining 2 sub-matrices on the left side.
    Then it moves horizontally to the right, starts from the top [the top center submatrix] and moves down again.
    This procedure is repeated for the last 3 sub-matrices on the right side as well. The matrix numbers is
    sequential and is in the order of appearence in this iteration.
    */
    int i, j, k, l, r, c;
    r = 0; //used for the row indexing of the submatrix 2D array
    c = 0; //used for the column indexing of the submatrix 2D array
    for(l = 1; l<=3; l++){ //helps in horizontal displacement from left-to-right in 3 steps, that is, 0-2 -> 3-5 -> 6-8
        for(i=1; i<=3; i++){ // helps in vertical displacement from top-to-bottom in 3 steps, that is, 0-2 -> 3-5 -> 6-8
            for(j=(i-1)*3; j<i*3; j++){ //row operating loop
                for(k=(l-1)*3; k<l*3; k++){ //column operating loop
                    s->submatrix[r][c] = s->board[j][k];
                    c++;
                }
            }
            r++; //The row indexer is incerment after each submatrix is successfully extracted
            c = 0; //The column indexer is set to 0 again so the next submatrix can be taken in next array of the sub-matrix 2D array
        }

    }
}

void display_submatrix(sboard s){
    printf("\n");
    for (int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            printf("%d ",s.submatrix[i][j]);
        }
        printf("\n");
    }
}

int check_for_completeness(sboard s){
    for (int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(s.board[i][j] == 0){ //here 0 represents void or incompleteness in the suduko board
                return 0;
            }
        }
    }
    return 1;
    
}
int check_for_rows(sboard s, int invr[9]){
    int c, o;
    c = 0;
    o = 0;
    for (int i=0; i<9; i++){
        for(int j=0; j<8; j++){
            c = o;
            for(int k=j+1;k<9;k++){
                if(s.board[i][j] == 0)
                    break;
                if(s.board[i][j] == s.board[i][k]){
                    invr[i] = i+1;
                    c++;
                    break;
                }
                if(c!=o){ //This condition checks whether a row is inviable already, if so then it breaks to the next row
                break;
            }
            }
        }
    }
   if(o !=0){
        return 0;
    }
    return 1;
}
int check_for_columns(sboard s, int invc[9]) //This functions checks for the columns that have repetition of elements
{
    int c, o;
    c = 0;
    o = 0;
    for (int i=0; i<9; i++){
        for(int j=0; j<8; j++){
            c = o;
            for(int k=j+1;k<9;k++){
                if(s.board[j][i] == 0)
                    break;
                if(s.board[j][i] == s.board[k][i]){
                    invc[i] = i+1;
                    c++;
                    break;
                }
                if(c!=o){ //This condition checks whether a column is inviable already, if so then it breaks to the next column
                    break;
            }
            }
        }
    }
    if(o !=0){
        return 0;
    }
    return 1;

}

int check_for_submatrix(sboard s, int invsm[9]){
    int c, o;
    c = 0;
    o = 0;
    for (int i=0; i<9; i++){
        for(int j=0; j<8; j++){
            o = c;
            for(int k=j+1;k<9;k++){
                if(s.submatrix[i][j] == 0)
                    break;
                if(s.submatrix[i][j] == s.submatrix[i][k]){ 
                    invsm[i] = i+1;
                    c++;
                    break;
                }
            }
            if(c!=o){ //This condition checks whether a submatrix is inviable already, if so then it breaks to the next sub-matrix
                break;
            }
        }
    }
    if(o != 0){
        return 0;
    }
    return 1;
}

void checker(sboard s){
    int invr[9] = {0,0,0,0,0,0,0,0,0};
    int invc[9] = {0,0,0,0,0,0,0,0,0};
    int invsm[9] = {0,0,0,0,0,0,0,0,0};
    int cr = check_for_rows(s, invr);
    int ccl = check_for_columns(s, invc);
    int cc = check_for_completeness(s);
    int csm = check_for_submatrix(s, invsm);

    if(cc && ccl && cr && csm){
        printf("\ncomplete\n");
    }
    else if(ccl && cr && csm && !cc){
        printf("\nincomplete but viable\n");
    }
    else{
        printf("non-viable\n rows: ");
        for(int i=0; i<9; i++){
            if(invr[i] != 0)
                printf("%d ", invr[i]);
        }
        printf("\n columns: ");
        for(int i=0; i<9; i++){
            if(invc[i] != 0)
                printf("%d ", invc[i]);
        }
        printf("\n sub-matrices: ");
        for(int i=0; i<9; i++){
            if(invsm[i] != 0)
                printf("%d ", invsm[i]);
        }
        printf("\n");

    }
}
int main(){
    printf("Hello World!\n");
    sboard s;
    s = input_board(); 
    get_submatrix(&s); 
    checker(s);
    return 0;
}
