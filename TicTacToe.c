#include <stdlib.h>
#include <stdio.h>

const int BOARD_SIZE = 3;

typedef enum {
EMPTY, X, O
} State;

State board[3][3];
State currTurn = X;
int numTurns = 0;

void initBoard();
void printBoard();
void updateBoard(int row, int col);
void flipCurrentTurn();
int isFilled(int row, int col);
int checkWin(int row, int col);

int main(){
	initBoard();
	
	int row, col;
	while(1){
		if(currTurn == X){
			puts("\n-----------------------------\nPlayer 1's turn! (X)\n");
		}else{
			puts("\n-----------------------------\nPlayer 2's turn! (O)\n");
		}
		
		puts("Enter the row followed by the column: ");
		if(scanf("%d %d", &row, &col) == 2){
			if(row > BOARD_SIZE || col > BOARD_SIZE || row < 1 || col < 1){
				puts("Invalid row or column. Values must be between 1 and 3.");
				continue;
			}
		}else{
			fseek(stdin,0,SEEK_END);
			puts("Invalid value.");
			continue;
		}
		
		if(isFilled(row - 1, col - 1)){
			puts("That square is filled.");
			continue;
		}
		
		numTurns++;
		updateBoard(row - 1, col - 1);
		printBoard();
		
		if(checkWin(row - 1, col - 1)){
			if(currTurn == X){
				printf("\n\nPlayer 1 has won!\n");
			}else{
				printf("\n\nPlayer 2 has won!\n");
			}
			break;
		}
		
		if(numTurns == 9){
			puts("\n\nThe game is a draw!\n");
			break;
		}
		
		flipCurrentTurn();
	}

	return EXIT_SUCCESS;
}


void flipCurrentTurn(){
	if(currTurn == X){
		currTurn = O;
	}else{
		currTurn = X;
	}
}


void initBoard(){
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			board[i][j] = EMPTY;
		}
	}
}


void printBoard(){
	puts("");
	for(int i = 0; i < BOARD_SIZE; i++){
		printf("      ");
		for(int j = 0; j < BOARD_SIZE; j++){
			switch(board[i][j]){
				case 1:
					printf("X");
					break;	
				case 2:
					printf("O");
					break;	
				default:
					printf(" ");
					break;
			}
			if(j != BOARD_SIZE - 1){
				printf(" | ");
			}
		}
		if(i != BOARD_SIZE - 1){
			printf("\n      ----------\n");
		}
	}
	puts("");
}


void updateBoard(int row, int col){
	if(currTurn == X){
		board[row][col] = X;
	}else{
		board[row][col] = O;
	}
}


int isFilled(int row, int col){
	if(board[row][col] == 0){
		return 0;
	}else{
		return 1;
	}
}


int checkWin(int row, int col){
	int horiCount = 0, vertCount = 0, diag1Count = 0, diag2Count = 0;
	for(int i = 0; i < BOARD_SIZE; i++){
		//horizontal check
		if(board[row][i] == currTurn){
			horiCount++;
		}
		
		//vertical check
		if(board[i][col] == currTurn){
			vertCount++;
		}
		
		//horizontal check
		if(board[i][i] == currTurn){
			diag1Count++;
		}
		
		//other horizontal check
		if(board[i][BOARD_SIZE - i - 1] == currTurn){
			diag2Count++;
		}
	}
	
	if(horiCount == 3 || vertCount == 3 || diag1Count == 3 || diag2Count == 3){
		return 1;
	}else{
		return 0;
	}
}