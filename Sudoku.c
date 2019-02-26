#include <stdio.h>
#include  <stdlib.h>
#include <stdbool.h>

 int rows = 9;
 int columns = 9;
 int elements; 

int board[9][9];
bool start[9][9];

bool checkThreebyThree(int f[][9], int, int );
bool checkRow(int a[][9], int);
bool checkColumn(int c[][9], int);
bool checkThreebyThree(int k[][9], int, int);
bool checkPuzzle(int u[][9]);
char *possiblemoves(int x[][9], int, int);
int getValueIn(int a[][9], int, int);
bool isFull(int x[][9]);
void addGuess(int x[][9], int, int, int);
void reset(int x[][9]);



bool checkRow(int x[9][9], int row){

   int check = 0; 

   for(int a = 0; a < 9; a++){

     check += x[a][row];
   }

   if(check == 45){
   return true;
   }

   else{
     return false; 
   }

}

bool checkColumn(int x[9][9], int column){
  
  int check = 0; 

  for(int a = 0; a < 9; a++){

    check += x[column][a];
  }

  if(check == 45){
    return true;
  }
  else{
    return false; 
  }
}

bool checkThreebyThree(int x[9][9], int startRow, int startColumn){

  int check = 0; 

    for(int i = startRow; i < 3; i++){

      for(int a = startColumn; a < 3; a++){

        check += x[a][i];
      }
    }

    if(check == 45){
      return true;
    }

    else{
      return false; 
    }
}

//@param game board
//@returns true if board is solved
//@returns false if it is not 
bool checkPuzzle(int x[9][9]){
  //check all rows and columns
  for(int a = 0; a < 9; a++){

    if(checkRow(x, a) == false){
      return false;
    }
    if(checkColumn(x, a) == false){
      return false;
    }
  }
  //check all 3x3 grids 

    for(int j = 0; j<=6; j+=3){

        for(int al = 0; al <= 6; al+=3){

          if(checkThreebyThree(x, j, al) == false){
            return false;
          }
        }
    }

    return true;
}

int deduce(int number){


    if(number == 3 || number == 6 || number == 0){
      return number; 
    }

    if(number > 6){

      return 6;
    }

    if(number < 3){
      return 0;
    }

    else{

      return 3;

    }

  }


bool movePossibleThree(int x[][9], int row, int column, int value){


    for(int i = row; i < row+3; i++){

      for(int a = column; a < column+3; a++){
        
        if (x[a][i] == value){

          return false;
        }
      }
    }

    return true; 
}


bool canMove(int x[9][9], int row, int column, int value){


  for(int i = 0; i < 9; i++){
      if(x[i][column] == value){
        return false;
      }
      
      if(x[row][i] == value){
        return false;
      }

      if(movePossibleThree(x, deduce(column), deduce(row), value) == false){
        return false;
      }

  }

        return true;

}

void possibleMoves(int x[9][9], int row, int column){


    printf("Possible moves in (%d,%d) are: ", row, column);

    for(int a = 0; a <= 9; a++){


        if(canMove(x, row, column, a)){
          printf("%d, ", a);
        }
    
    }
}

//@param board
//@param value location
//@returns the value in the given square
int getValueIn(int x[9][9], int row, int colu){
  
  return x[row][colu];
}




bool isFull(int x[9][9]){

  for(int i = 0; i < 9; i++){
    for(int a = 0; a < 9; a++){
      if(x[a][i] == 0){
        return false;
      }
    }
  }
  return true; 
}

void addGuess(int x[rows][columns], int row, int colu, int guess){
  if(getValueIn(x, row, colu) == 0){
    x[row][colu] = guess; 
  }
  else{
    printf("\nERROR - Move cannot be made at specified location");
    return;
  }
}

void reset(int x[rows][columns]){

  for(int i = 0; i < 9; i++){

    for(int a = 0; a < 9; a++){
      
      if(start[a][i] == true){
        x[a][i] = 0;
      }
    }
  }
}



//Displays the puzzle in its current state 
void Display(int x[9][9]){

      printf("\n\n");

  for(int i = 0; i < 9; i++){

    
   if(i%3==0){
      printf("------------\n");
    }


    for(int a = 0; a < 9; a++){

      if(a % 3 == 0){
      printf("|");

      }
      printf("%d", x[a][i]);
      
    }
    printf("\n");

  }
    printf("------------\n");
}

//Displays the puzzle of boolean values 
void Displaybool(bool x[9][9]){

  for(int i = 0; i < 9; i++){

    for(int a = 0; a < 9; a++){
      printf("%s ", x[a][i]?"T": "F");
    }
    printf("\n");

  }

  printf("\n\n");
}

//a function that creates an empty puzzle and sets the boolean puzzle to blank also 
void CreateSudokuPuzzle(int x[9][9], bool y[9][9]){

    for(int i = 0; i < 9; i++){

      for(int a = 0; a < 9; a++){

        x[a][i] = 0; 
        y[a][i] = true; 
      }
    }


}
//—sets the given square to the given value as an initial value that cannot be changed by the puzzle solver
//@param board 
//@param row and column location
//@param value to be set to initial
void setInitValue(int x[9][9], int row, int colu, int value){

  x[row][colu] = value; 
  start[row][colu] = false; 

}

void move(int x[9][9]){
  
    int row, column, value;

    printf("Where would you like to move? \n");
    
    printf("X coordinate:  ");
    scanf("%d", &row);
    printf("\nY coordinate:  ");
    scanf("%d", &column);
    printf("Which value would you like to add? ");
    scanf("%d", &value);
    addGuess(x, row, column, value);

}

void check(int x[9][9]){

  int row, column;

printf("X coordinate:  ");
    scanf("%d", &row);
    printf("\nY coordinate:  ");
    scanf("%d", &column);

    possibleMoves(x, row, column);
}


void game(int x[9][9]){

  printf("REMEMEBER --- Row & Column number as 'X' , 'Y' coordinates between 1 to 9");
  do{
    

    Display(x);

    int f;

    printf("\n 1 Make move");
    printf("\n 2 Clear board");
    printf("\n 3 Check potential moves at give coordinates");
    printf("\n 4 Quit");

    scanf("%d", &f);

  switch(f){
    
    case 1:
      move(x);
      break;

    case 2:
      reset(x);
      break;

    case 3:
    check(x);
    break;

    case 4:
    exit(0);

    
    default:
    printf("ERROR -- Improper input");
  }





  }while(isFull(x) == false && checkPuzzle(x) == false);
}


int main(void) {

bool x = true; 

do{
  int userInput;

  printf("\tWELCOME TO SUDOKU!!\n");
  printf("Would you like to play a game?\n\t1 yes \n\t2 no\n\n");


  scanf("%d", &userInput);

  switch(userInput){
    case 1:
        CreateSudokuPuzzle(board,start);
        game(board);
        break;

  case 2:
        printf("\nHave a great day!");
        exit(0);

  default:
  printf("Invalid  input!!!");

  }
}while(x);

  
  Display(board);
  possibleMoves(board, 0, 6);



  return 0;
}
