#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define BOARD_SIZE 3

typedef enum {
EMPTY, X, O
} State;

State board[BOARD_SIZE][BOARD_SIZE];
State currTurn = X;
State sideOfAI;

void initBoard();
void playTwoPlayer();
void getPlayersMove(int* row, int* col);
void makeMove(int row, int col);
int checkDraw();
int gameFinished(int row, int col);
void getLineBreak(char lineBreak[]);
void printBoard();
void updateBoard(int row, int col);
void changeTurn();
int isFilled(int row, int col);
int checkWin(int row, int col);

int main(){
	initBoard();
	playTwoPlayer();

	return EXIT_SUCCESS;
}


void initBoard(){
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			board[i][j] = EMPTY;
		}
	}
}


void playTwoPlayer(){
	int row, col;
	while(1){
		if(currTurn == X){
			puts("\n-----------------------------\nPlayer 1's turn! (X)");
		}else{
			puts("\n-----------------------------\nPlayer 2's turn! (O)");
		}
			
		getPlayersMove(&row, &col);
		makeMove(row, col);
		
		if(gameFinished(row, col) == 1){
			break;
		}
		
		changeTurn();
	}
}


void makeMove(int row, int col){
	updateBoard(row - 1, col - 1);
	printBoard();
}


int gameFinished(int row, int col){
	if(checkWin(row - 1, col - 1)){
		if(currTurn == X){
			printf("\n\nPlayer 1 has won!\n");
		}else{
			printf("\n\nPlayer 2 has won!\n");
		}
		return 1;
	}
	
	if(checkDraw(board) == 1){
		puts("\n\nThe game is a draw!\n");
		return 1;
	}
	
	return 0;
}


void getPlayersMove(int* row, int* col){
	puts("Enter the row followed by the column: ");
	while(1){
		if(scanf("%d %d", row, col) == 2){
			if(*row > BOARD_SIZE || *col > BOARD_SIZE || *row < 1 || *col < 1){
				printf("Invalid row or column. Values must be between 1 and %d.\n", BOARD_SIZE);
				continue;
			}else if(isFilled(*row - 1, *col - 1)){
				puts("That square is filled.");
				continue;
			}else{
				break;
			}
		}else{
			fseek(stdin,0,SEEK_END);
			puts("Invalid value.");
			continue;
		}
	}
}


void changeTurn(){
	if(currTurn == X){
		currTurn = O;
	}else{
		currTurn = X;
	}
}


void printBoard(){
	puts("");
	char lineBreak[BOARD_SIZE * 4] = "";
	getLineBreak(lineBreak);
	
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
			printf("\n      %s\n", lineBreak);
		}
	}
	puts("");
}


void getLineBreak(char lineBreak[]){
	int amount = floor(BOARD_SIZE * 3.85);
	for(int i = 0; i < amount; i++){
		strcat(lineBreak, "-");
	}
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


int checkDraw(){
	int numFilled = 0;
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			if(board[i][j] != EMPTY){
				numFilled++;
			}
		}
	}
	
	if(numFilled >= 9){
		return 1;
	}else{
		return 0;
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
	
	if(horiCount == BOARD_SIZE || vertCount == BOARD_SIZE ||
	diag1Count == BOARD_SIZE || diag2Count == BOARD_SIZE){
		return 1;
	}else{
		return 0;
	}
}