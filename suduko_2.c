#include<stdio.h>

struct sudukoboard{
    int board[9][9];
    int submatrix[9][9];
};
typedef struct sudukoboard sboard;

sboard input_board(){
    sboard s;
    for (int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            scanf("%d",&s.board[i][j]);
        }
    }
    return s;
}

void get_submatrix(sboard *s){
    int i, j, k, l, r, c;
    r = 0;
    c = 0;
    for(l = 1; l<=3; l++){
        for(i=1; i<=3; i++){
            for(j=(i-1)*3; j<i*3; j++){
                for(k=(l-1)*3; k<l*3; k++){
                    s->submatrix[r][c] = s->board[j][k];
                    c++;
                }
            }
            r++;
            c = 0;
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
            if(s.board[i][j] == 0){
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
        for(int j=0; j<9; j++){
            c = o;
            for(int k=j+1;k<8;k++){
                if(s.board[i][j] == s.board[i][k] && s.submatrix[i][j] != 0){
                    invr[i] = i+1;
                    c++;
                    break;
                }
                if(c!=o){
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
int check_for_columns(sboard s, int invc[9]){
    int c, o;
    c = 0;
    o = 0;
    for (int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            c = o;
            for(int k=j+1;k<8;k++){
                if(s.board[j][i] == s.board[k][i] && s.submatrix[j][i] != 0){
                    invc[i] = i+1;
                    c++;
                    break;
                }
                if(c!=o){
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
        for(int j=0; j<9; j++){
            o = c;
            for(int k=j+1;k<8;k++){
                if(s.submatrix[i][j] == s.submatrix[i][k] && s.submatrix[i][j] != 0){ 
                    invsm[i] = i+1;
                    c++;
                    break;
                }
            }
            if(c!=o){
                break;
            }
        }
    }
    if(o != 0){
        return 0;
    }
    return 1;
}
int main(){
    printf("Hello World!\n");
    sboard s;
    s = input_board();
    get_submatrix(&s);
    int invr[9] = {0,0,0,0,0,0,0,0,0};
    int invc[9] = {0,0,0,0,0,0,0,0,0};
    int invsm[9] = {0,0,0,0,0,0,0,0,0};
    printf("\n\n");
    if(check_for_completeness(s) && check_for_columns(s, invc) && check_for_rows(s,invc) && check_for_submatrix(s, invsm)){
        printf("complete\n");
    }
    else if(check_for_columns(s, invc) && check_for_rows(s,invc) && check_for_submatrix(s, invsm) && !check_for_completeness(s)){
        printf("incomplete but viable\n");
    }
    else{
        ///need to write this part....
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
    printf("\n\n");
    display_submatrix(s);
    return 0;
}
