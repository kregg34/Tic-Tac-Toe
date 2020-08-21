#include <stdlib.h>
#include <stdio.h>

const int BOARD_SIZE = 3;

typedef enum {
EMPTY, X, O
} State;

State board[3][3];
State currTurn = X;
State sideOfAI;
int numTurns = 0;

void initBoard();
int getSelectedOption();
void playTwoPlayer();
void getPlayersMove(int* row, int* col);
void playAgainstAI();
void getAIMove(int* row, int* col);
void pickSide();
void makeMove(int row, int col);
int gameFinished(int row, int col);
void printBoard();
void updateBoard(int row, int col);
void changeTurn();
int isFilled(int row, int col);
int checkWin(int row, int col);

int main(){
	initBoard();
	
	puts("\nOptions:\nType \"1\" to play two-player.\nType \"2\" to play against an AI.");
	int selectedOption = getSelectedOption();
	
	if(selectedOption == 1){
		playTwoPlayer();
	}else{
		pickSide();
		playAgainstAI();
	}

	return EXIT_SUCCESS;
}


void initBoard(){
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			board[i][j] = EMPTY;
		}
	}
}


int getSelectedOption(){
	int selectedOption;
	while(1){
		if(scanf("%d", &selectedOption) == 1){
			if(selectedOption == 1){
				puts("You selected to play two-player.");
				return 1;
			}else if(selectedOption == 2){
				puts("You selected to play against an AI.");
				return 2;
			}else{
				fseek(stdin,0,SEEK_END);
				puts("Invalid option!");
				continue;
			}
		}else{
			fseek(stdin,0,SEEK_END);
			puts("Invalid value.");
			continue;
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


void pickSide(){
	puts("\nOptions:\nType 1 to play first.\nType 2 to play second.");
	int selectedSide;
	while(1){
		if(scanf("%d", &selectedSide) == 1){
			if(selectedSide == 1){
				sideOfAI = O;
				break;
			}else if(selectedSide == 2){
				sideOfAI = X;
				break;
			}else{
				fseek(stdin,0,SEEK_END);
				puts("Invalid value.");
				continue;
			}
		}else{
			fseek(stdin,0,SEEK_END);
			puts("Invalid value.");
			continue;
		}
	}
}


void playAgainstAI(){
	int row, col;
	while(1){
		if(currTurn != sideOfAI){
			puts("Your turn!");
			getPlayersMove(&row, &col);
		}else{
			puts("The AI is thinking...!");
			getAIMove(&row, &col);
		}
			
		makeMove(row, col);
		
		if(gameFinished(row, col) == 1){
			break;
		}
		
		changeTurn();
	}
}


// Uses a backtracking algorithm
void getAIMove(int* row, int* col){
	
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
	
	numTurns++;
	if(numTurns == 9){
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
				puts("Invalid row or column. Values must be between 1 and 3.");
				continue;
			}else{
				break;
			}
		}else{
			fseek(stdin,0,SEEK_END);
			puts("Invalid value.");
			continue;
		}
		
		if(isFilled(*row - 1, *col - 1)){
			puts("That square is filled.");
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