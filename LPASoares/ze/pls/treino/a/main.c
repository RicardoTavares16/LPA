#include <stdlib.h>
#include <stdio.h>


int horseyhorse(int x, int y, int moves,int **board){
    int result = 0;
    moves --;

    if(board[x][y] == 0){
        board[x][y] = 1;
        result++;
    }
    if(moves >= 0){
        result += horseyhorse(x-2,y+1,moves,board);
        result += horseyhorse(x-2,y-1,moves,board);
        result += horseyhorse(x+2,y+1,moves,board);
        result += horseyhorse(x+2,y-1,moves,board);
        result += horseyhorse(x+1,y-2,moves,board);  
        result += horseyhorse(x+1,y+2,moves,board);
        result += horseyhorse(x-1,y+2,moves,board);
        result += horseyhorse(x-1,y-2,moves,board);
        
    }
    return  result;
}

int main(){
    int i, numberKnights, x, y, moves, output;
    int **board;
    output=0;
    board = (int**) malloc(400 * sizeof(int));

	for (i = 0; i < 400; ++i) {
		board[i] = (int*) calloc(400, sizeof(int));
	}
    scanf("%d",&numberKnights); 
    for(i=0; i< numberKnights; i++){
        scanf("%d %d %d",&x,&y,&moves);
        x+=200;
        y+=200;
        output += horseyhorse(x,y,moves,board);
    }
    printf("%d\n",output);
    return 0;
}



