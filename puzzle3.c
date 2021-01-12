#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>

void textDisplay();
void initializeBox(int level, int box[level][level]);
void renderBox(int level, int box[level][level],int difficulty);
void bellSound();
int swap(int level, int box[level][level], int direction, int spaceIndex[2], int makeSound);
void shuffleBox(int level, int box[level][level], int spaceIndex[2], int difficulty);
int getKeyPress();
int gameWon(int level, int box[level][level]);
void solutionDisplay();
void loadAnimation();

int top = -1;
int stack[200];
int solution[200];
int length = -1;
int movesCount = 0;

int main(){
	textDisplay("WELCOME TO NUMBER PUZZLE GAME!\n");
	int level,difficulty;
	do{
		textDisplay("Enter Level(2-10): ");
		scanf("%d",&level);
	}while(level>10 || level<2);
	
	int box[level][level];

	initializeBox(level,box);
	int spaceIndex[] = {level-1, level-1};
	textDisplay("Choose Difficulty option: ");
	textDisplay("1.Beginner");
	textDisplay("2.Intermediate");
	textDisplay("3.Pro");
	textDisplay("Enter your choice(1/2/3): ");
	do{
		scanf("%d",&difficulty);
	}while(difficulty>3 || difficulty<1);
	

	shuffleBox(level, box, spaceIndex, difficulty);
	while(gameWon(level,box)){
		shuffleBox(level, box, spaceIndex,difficulty);
	}
	
	textDisplay("Press Enter key to start the game!");
	getchar();
	getchar();
	system("clear");
	textDisplay("Tip => Use W A S D keys to move the empty space!");
	loadAnimation();
	usleep(1000000);
	int solutionDisplayFlag = 0;
	while(1){
		system("clear");
		renderBox(level,box,difficulty);
		if(solutionDisplayFlag){
			solutionDisplay();
		}
		printf("\nWaiting for your move.....\n\n[press q to quit]\t[h for solution]\t[z for undo]\n");
		int toDo = getKeyPress();
		if(toDo == 0){
			continue;
		}
		else if(toDo == -1){
			break;
		}
		else if(toDo == 5){
			solutionDisplayFlag = 1;
		}
		else if(toDo == 6){
			if(top == -1){
				continue;
			}
			else if(stack[top] == 1){
				swap(level,box,2,spaceIndex,0);
				--top;
			}
			else if(stack[top] == 3){
				swap(level,box,4,spaceIndex,0);
				--top;
			}
			else if(stack[top] == 2){
				swap(level,box,1,spaceIndex,0);
				--top;
			}
			else if(stack[top] == 4){
				swap(level,box,3,spaceIndex,0);
				--top;
			}	
			movesCount--;
		}
		else{	
			if(swap(level,box,toDo,spaceIndex,1)==1){
				stack[++top] = toDo;
				movesCount++;
			}
		}
		
		if(gameWon(level,box) == 1){
			system("clear");
			renderBox(level,box,difficulty);
			textDisplay("YOU WON ;)!");
			break;
		}	
		
	}
	
}


void loadAnimation(){
	char* wish = "....";
    int length = strlen(wish);
    printf("\n");
    for(int i=0;i<=length;i++){
    	for(int j=0;j<i;j++){
    		printf("%c",wish[j]);
    		fflush(stdout);
    		usleep(190000);
    	}
    	printf("\r");
    	for(int k=0;k<i;k++){
    		printf(" ");
    	}
    	//printf("\n");   	
    }
}


void textDisplay(char *text){
    int length = strlen(text);
    printf("\n");
    for(int i=0;i<length;i++){
    	printf("%c",text[i]);
    	fflush(stdout);
    	usleep(9999);
    }
}

void solutionDisplay(){
	printf("\nSolution => ");
	for(int i=length;i>=0;i--){
		if(solution[i]==1){
			printf("Down->");
		}
		else if(solution[i]==2){
			printf("up->");
		}
		else if(solution[i]==3){
			printf("Left->");
		}
		else if(solution[i]==4){
			printf("Right->");
		}
	}
	printf("\n\n");
}


void initializeBox(int level,int box[level][level]){
	for(int i=1;i<=level;i++){
		for(int j=1;j<=level;j++){
			box[i-1][j-1] = ((i-1)*level)+j;
		}
	}
}

void renderBox(int level,int box[level][level],int difficulty){
	char emptySpace = ' ';
	char verticalBorder = '|';
	char* horizontalBorder = "-----";
	char *mode;
	if(difficulty == 1){
		mode = "Beginner";
	}
	else if(difficulty == 2){
		mode = "Intermediate";
	}
	else{
		mode = "Pro";
	}
	printf("Moves = %d\t\tDifficulty level = %s\n\n",movesCount,mode);
	for(int i=0;i<level;i++){
		for(int k=0; k<level;k++){
			printf("%5s",horizontalBorder);
		}
		printf("\n");
		for(int j=0;j<level;j++){
			if(box[i][j] == (level*level)){
				printf("| %c  ",emptySpace);
			}
			else{
				if(box[i][j]>9){ 
					printf("| %d ",box[i][j]);
				}else{
					printf("| %d  ",box[i][j]);
				}	
			}
			if(j == level-1){
				printf("|");
			}
		}
		printf("\n");
	}
	for(int i=0; i<level;i++){
		printf("%5s",horizontalBorder);
	}
	printf("\n");
}

void bellSound(){
	printf("\a");
}


int swap(int level, int box[level][level], int direction, int spaceIndex[2], int makeSound){
	if(direction == 1){ 
		if(spaceIndex[0] == 0){
			if(makeSound == 1){
				bellSound();
			}
			return 0;
		}
		else{
			int temp = box[spaceIndex[0]-1][spaceIndex[1]];
			box[spaceIndex[0]-1][spaceIndex[1]] = box[spaceIndex[0]][spaceIndex[1]];
			box[spaceIndex[0]][spaceIndex[1]] = temp;
			spaceIndex[0] = spaceIndex[0]-1;
			spaceIndex[1] = spaceIndex[1];
		}
	}
	else if(direction == 2){
		if(spaceIndex[0] == level-1){
			if(makeSound == 1){
				bellSound();
			}
			return 0;
		}
		else{
			int temp = box[spaceIndex[0]+1][spaceIndex[1]];
			box[spaceIndex[0]+1][spaceIndex[1]] = box[spaceIndex[0]][spaceIndex[1]];
			box[spaceIndex[0]][spaceIndex[1]] = temp;
			spaceIndex[0] = spaceIndex[0]+1;
			spaceIndex[1] = spaceIndex[1];
		}
	}
	else if(direction == 3){
		if(spaceIndex[1] == level-1){
			if(makeSound == 1){
				bellSound();
			}
			return 0;
		}
		else{
			int temp = box[spaceIndex[0]][spaceIndex[1]+1];
			box[spaceIndex[0]][spaceIndex[1]+1] = box[spaceIndex[0]][spaceIndex[1]];
			box[spaceIndex[0]][spaceIndex[1]] = temp;
			spaceIndex[0] = spaceIndex[0];
			spaceIndex[1] = spaceIndex[1]+1;
		}
	}
	else if(direction == 4){
		if(spaceIndex[1] == 0){
			if(makeSound == 1){
				bellSound();
			}
			return 0;
		}
		else{
			int temp = box[spaceIndex[0]][spaceIndex[1]-1];
			box[spaceIndex[0]][spaceIndex[1]-1] = box[spaceIndex[0]][spaceIndex[1]];
			box[spaceIndex[0]][spaceIndex[1]] = temp;
			spaceIndex[0] = spaceIndex[0];
			spaceIndex[1] = spaceIndex[1]-1;
		}
	}
	return 1;

}

void shuffleBox(int level, int box[level][level], int spaceIndex[2], int difficulty){
	srand(time(0));
	int no_of_shuffles =  difficulty*20;
	for(int i=0;i<no_of_shuffles;i++){
		int dir = (rand()%4)+1;
		if(length>=0){
			if((solution[length] + dir != 3) && (solution[length] + dir != 7)){
				if(swap(level,box,dir,spaceIndex,0)==1){
					if(gameWon(level,box)==1){
						length = -1;
					}
					solution[++length] = dir;
				}		
			}
		}
		else{
			if(swap(level,box,dir,spaceIndex,0)==1){
				solution[++length] = dir;
			}
		}
	}
}

int getKeyPress(){
	int direction = 0;
	char ch = getchar();
    switch(tolower(ch)) { 
        case 'w':
           	//arrow up
       		direction = 1;
           	break;
       	case 's':
         	//arrow down
            direction = 2;
            break;
        case 'd':
           	//arrow right
        	direction = 3;
            break;
        case 'a':
           	// arrow left
        	direction = 4;
           	break;
        case 'q':
        	direction = -1;
        	break;
        case 'h':
        	direction = 5;
        	break;
        case 'z':
        	direction = 6;
        	break;
	}
	return direction;
}

int gameWon(int level, int box[level][level]){
	for(int i=1;i<=level;i++){
		for(int j=1;j<=level;j++){
			if(box[i-1][j-1] != ((i-1)*level)+j){
				return 0;
			}
		}
	}
	return 1;
}