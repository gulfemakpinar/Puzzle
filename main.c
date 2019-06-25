#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
 char *word; //word and corresponding hint
 char *clue;
 int x; //Starting x and y positions
 int y;
 char direction; //H for horizontal, V for vertical
 int f; //solved or not
} Word_t;
Word_t* loadTextFile( FILE* myFile, int nrWords );
void displayBoard(int rows, int cols, char** myBoard);
int isBoardFilled(int rows, int cols, char** myBoard);
char** createArray(int rows, int cols);
int findIndex(int arr[], int size, int val);
void playGame(char** myBoard, int words, Word_t *word, int x, int y, int countToFinish);
char** updateBoard(char** myBoard, Word_t *words, int solve);
int main()
{
char** board;
FILE *inp;
int row,col,w;
Word_t* word;
char name[20];
puts("CMPE HW1 PUZZLE GAME\n\n");
puts("Enter name of text file: ");
scanf("%s",name);
if((inp =fopen(name,"r+"))==NULL)
    puts("File could not be opened.");

fscanf(inp,"%d%d%d",&row,&col,&w);
printf("Game is %d rows x %d cols with %d words\n",row,col,w);
word=(Word_t*)malloc(sizeof(Word_t)*w);
word=loadTextFile(inp,w);
board=createArray(row,col);
playGame(board,w,word,col,row,0);
free(word);
free(board);


}


Word_t* loadTextFile(FILE* myFile, int nrWords ){
Word_t* word=(Word_t*)malloc(sizeof(Word_t)*nrWords+1);


for(int i=0;i<nrWords;i++){

      word[i].clue=(char*)malloc(sizeof(char)*200);
      word[i].word=(char*)malloc(sizeof(char)*20);
      fscanf(myFile," %c %d %d %s %[^\n]s",&(word[i].direction),&(word[i].y),&(word[i].x),word[i].word,word[i].clue);

}
printf("Word and clues are read!\n");
fclose(myFile);
return word;

}

char** createArray(int rows, int cols){

    char** temp=(char**)malloc(sizeof(char*)*rows);
    for(int i=0;i<rows;i++){

        temp[i]=(char*)malloc(sizeof(char)*cols);

    }
    for (int i = 0; i <  rows; i++)
      for (int j = 0; j < cols; j++)
        temp[i][j]='#';

return temp;
}

void displayBoard(int rows, int cols, char** myBoard){
printf("          ");
for(int i=0;i<cols;i++){
    printf("%d  ",i+1);
}
printf("\n          ");
for(int i=0;i<cols;i++){
    printf("-- ");
}

printf("\n");
for(int i=0;i<rows;i++){
    printf("%d        |",i+1);
    for(int j=0;j<cols;j++){
        printf("%c  ",myBoard[i][j]);
    }
puts("\n");
}

}
int isBoardFilled(int rows, int cols, char** myBoard){
for (int i = 0; i <  rows; i++)
      for (int j = 0; j < cols; j++)
        if(myBoard[i][j]=='_')
            return 0;
        return 1;

}

int findIndex(int arr[], int size, int val){
    for(int i=0;i<size;i++){
        if(arr[i]==val)
            return 1;
    }
    return 0;
}

char** updateBoard(char** myBoard, Word_t *words, int solve){

if(solve!=0){
        if((*words).direction=='V'){
    for (int i = 0; i < strlen((*words).word); i++){
            myBoard[i+(*words).y-1][((*words).x)-1]=(*words).word[i];
        }
        }else{
         for (int i = 0; i < strlen((*words).word); i++){
            myBoard[(*words).y-1][i+(*words).x-1]=(*words).word[i];
        }
        }

}else{
if((*words).direction=='V'){
    for (int i = 0; i < strlen((*words).word); i++){
            myBoard[i+(*words).y-1][((*words).x)-1]='_';
        }
        }else{
         for (int i = 0; i < strlen((*words).word); i++){
            myBoard[(*words).y-1][i+(*words).x-1]='_';
        }
        }

}
return myBoard;
}


void playGame(char** myBoard, int words, Word_t *word, int x, int y, int countToFinish){
    for(int i=0;i<words;i++){
        updateBoard(myBoard,word+i,0);
    }


int current=0;
while(countToFinish<words&&current!=-1){
        printf("Current puzzle:\n");
displayBoard(y,x,myBoard);
    printf("Ask for hint:\n");
    printf("#  Direction    row  col\n");
    printf("-------------------------------\n");
    for(int i=0;i<words;i++){
            if(word[i].f==0){
            if(word[i].direction=='H')
        printf("%d: Horizontal   %d    %d\n",i+1,word[i].y,word[i].x);
        else
        printf("%d: Vertical     %d    %d\n",i+1,word[i].y,word[i].x);
            }
    }
    printf("Enter -1 to exit\n");
    printf("Which word  to solve next?:");
    scanf("%d",&current);
    if((current<-1||current>words)){
            printf("Invalid number!\n");
        continue;
    }else if(word[current-1].f==1){
        printf("That word has been solved before\n");
        continue;
    }
    printf("Current hint: %s\n",word[current-1].clue);
    printf("Enter your solution: ");
    char* answer=(char*)malloc(sizeof(char)*20);
    scanf("%s",answer);
    if(strcmp(answer,word[current-1].word)==0){
        printf("Correct!\n");
        word[current-1].f=1;
        updateBoard(myBoard,word+current-1,word[current-1].f=1);
        countToFinish++;
        if(isBoardFilled(y,x,myBoard)==1)
            break;
    }else
    printf("WRONG ANSWER!\n");

}
printf("current puzzle:\n");
displayBoard(y,x,myBoard);
puts("Congratulations! You beat the puzzle!");

}
