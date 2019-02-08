/*
 * Author: Rushdi Al-Hasan
 * 
 *
 *
 *
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 30


//struct to hold player info
struct player{
	
	int id;
	bool isDead;
	char type;//A/H
	int cont; //keep track of where player is

};

//strcut to hold continent info
struct continent{
	
	int numH, numA;// keeps track of how many A/H 
	int H[5];
	int A[5];
	bool dragon;//true if dragon exist on continent, false otherwise
	
};

struct continent con[4]; //array of continents
struct player p[MAX]; // array of player structs

int numInFile = -1;//keeps track of players in file

pthread_mutex_t lock;

// function to print initial setup
void printInitial(){

//	printf("Initial Setup: \n");
//	printf("\n");

	printf("Player		Type		Continent ");
	for(int i = 0; i < numInFile; i++){

		printf("\n %d		 %c		" ,p[i].id, p[i].type);
		if(p[i].cont == -1)// if player continent is -1 then its in the queue
			printf("%s","queue");
	
			
		else
			printf("%d",p[i].cont);

		if(con[0].dragon == true && p[i].cont == 0 &&  p[i+1].cont == 1){
			printf("\n");
			printf(" Dragon				%d",0);
		}
		else if(con[1].dragon == true && p[i].cont == 1  && p[i+1].cont == 2){
			printf("\n");
			printf(" Dragon				%d",1);
		}
		else if(con[2].dragon == true && p[i].cont == 2  && p[i+1].cont == 3){
			printf("\n");
			printf(" Dragon				%d",2);
		}
		else if(con[3].dragon == true && p[i].cont == 2 && p[i+1].cont == 4){
			printf("\n");
			printf(" Dragon				%d",3);
		}
	}
}
void shiftPlayerQ(){
	
//	int back = numInFile - 1;
	for(int i = 0; i < numInFile;i++){
		if(i == numInFile-1 ){
			p[i-1].id = p[i].id;
			p[i-1].type = p[i].type;
			p[i-1].cont = p[i].cont;
			p[i].id = -1;
			p[i].type = ' ';
			p[i].cont = -1;
		}
		else{
			p[i].id = p[i+1].id;
			p[i].type = p[i+1].type;
			p[i].cont = p[i+1].cont;
//			back--;
		}
	}	

}

void addPlayerToQ(int param, char type){
	
	int count = 0;
	while(p[count].id != -1){

		count++;
	}
	p[count].id = param;
	p[count].type = type;
	p[count].cont = -1;
	

}

void *fight(void* val){
	
	int temp;
	temp = (long) val;
	printf("\n");
	pthread_mutex_lock(&lock);
	//A = 4 and H = 1 -> A= 4 and H = 0
	if(con[temp].numA == 4 && con[temp].numH == 1){
		con[temp].numH -=1;
		addPlayerToQ(con[temp].H[0],'H');
		for(int i = 0; i < 5;i++){
			if(i == 4)
				con[temp].H[i-1] = con[temp].H[i];
			else
				con[temp].H[i] = con[temp].H[i+1];
		}
		if(con[temp].dragon == true){

			con[temp].numA -=1;
			addPlayerToQ(con[temp].A[0],'A');
			for(int i = 0; i < 5; i++){
				if(i == 4)
					con[temp].A[i-1] = con[temp].A[i];
				else
					con[temp].A[i] = con[temp].A[i+1];

			}
		}
		
	}
	//A= 3 and H = 2 -> A= 3 and H = 1
	else if(con[temp].numA == 3 && con[temp].numH == 2){
		con[temp].numH -= 1;
		addPlayerToQ(con[temp].H[0],'H');
		for(int i = 0; i < 5; i++){

			if(i == 4)
				con[temp].H[i-1] = con[temp].H[i];
			else
				con[temp].H[i] = con[temp].H[i+1];

		}
		if(con[temp].dragon == true){
			con[temp].numA -= 1;
			addPlayerToQ(con[temp].A[0],'A');
			for(int i = 0; i < 5; i++){
				if(i == 4 )
					con[temp].A[i-1] = con[temp].A[i];
				else
					con[temp].A[i] = con[temp].A[i+1];
				

			}
		}
	}
	//A=2 AND H = 3 -> A=1 and H =3 
	else if(con[temp].numA == 2 && con[temp].numH == 3){
		con[temp].numA -= 1;
		addPlayerToQ(con[temp].A[0],'A');
		for(int i = 0; i < 5; i++){
			if(i == 4)
				con[temp].A[i-1] = con[temp].A[i];
			else 
				con[temp].A[i] = con[temp].A[i+1];

		}
		if(con[temp].dragon == true){
			con[temp].numA -= 1;
			addPlayerToQ(con[temp].A[1],'A');
			for(int i = 0; i < 5; i++){

				if(i == 4)
					con[temp].A[i-1] = con[temp].A[i];
				else
					con[temp].A[i] = con[temp].A[i+1];

			}
		}
	}
	//A = 1 and H = 4 -> A = 0 and H = 4
	else if(con[temp].numA == 1 && con[temp].numH == 4){
		con[temp].numA -= 1;
		addPlayerToQ(con[temp].A[0],'A');
		for(int i = 0; i < 5; i++){
			if(i == 4)
				con[temp].A[i-1] = con[temp].A[i];
			else
				con[temp].A[i] = con[temp].A[i+1];

		}
		if(con[temp].dragon == true){
			con[temp].numH -= 1;
			addPlayerToQ(con[temp].H[0],'H');
			for(int i = 0; i < 5; i++){
				if(i == 4)
					con[temp].H[i-1] = con[temp].H[i];
				else
					con[temp].H[i] = con[temp].H[i+1];				

			}
		}

	}
	//shift continents
	

	//make sure 5 players on each continent
	


	
	pthread_mutex_unlock(&lock);	


	pthread_exit(NULL);
		
}


int main(int argc, char *argv[]){

	FILE *fp;
	fp = fopen("players.dat", "r");
	char c ;
	
	// initialize continent struct.
	for(int i = 0; i <4; i++){
		for(int j = 0; j <5 ; j++){
			con[i].A[j] = -1;
		       	con[i].H[j] = -1;
			con[i].numA = 0 , con[i].numH = 0;
		}
		con[i].dragon = false;
	}
	
	printf("\n");
	
	int i= 1;	
	while((c=getc(fp)) != EOF){//grab everything from file as char unitl EndOfFile
		if(c == 'D'){//id you reach a D
			c=getc(fp);//read next char to see where dragongoes
			
			if(c == '0'){
				con[0].dragon = true;
			}
			else if(c == '1'){

				con[1].dragon = true;
			}
			else if(c == '2'){
				con[2].dragon = true;

			}
			else{

				con[3].dragon = true;
			}
		}
		else{
			numInFile++;
			p[numInFile].id = i;
			p[numInFile].isDead = false;
			p[numInFile].type = c;
			p[numInFile].cont = -1;
			i++;
		}
	}

	
	//assign first 20 players initially to correct continents
	int h1=0,h2=0,h3=0,h4=0;
	int a1=0,a2=0,a3=0,a4=0;
	
	for(int i = 0; i  < 20; i++){
		
		if(i < 5){
			p[i].cont=0;
			if(p[i].type == 'H'){
				con[0].H[con[0].numH] = p[i].id;
				con[0].numH++;
			}
			else{
				
				
				con[0].A[con[0].numA] = p[i].id;
				con[0].numA++;
			}			
		}
		else if (i > 4 && i < 10){
			p[i].cont=1;
			if(p[i].type == 'H'){
				
				con[1].H[con[1].numH] = p[i].id;
				con[1].numH++;
			}
			else{
				con[1].A[con[1].numA] = p[i].id;
				con[1].numA++;
			}	
		
		}
		else if(i > 9 && i < 15){
			p[i].cont=2;
			if(p[i].type == 'H'){
				con[2].H[con[2].numH] = p[i].id;
				con[2].numH++;
			}
			else{
				con[2].A[con[2].numA] = p[i].id;
				con[2].numA++;
			}
		}
		else if(i > 14 && i < 20){
			p[i].cont = 3;
			if(p[i].type == 'H'){
				con[3].H[con[3].numH] = p[i].id;
				con[3].numH++;
				}
			else{
				con[3].A[con[3].numA] = p[i].id;
				con[3].numA++;
			}
		}
		
	}
	
	printInitial();	
	printf("\n");
	printf("\n");
	
	//now shift queue
	for(int i = 0; i < 20; i++){
		shiftPlayerQ();
	}
	printInitial();
	printf("\n");

	// Create threads
	pthread_t ids[4];

	for(long i = 0; i < 4; i++){
		ids[i] = i;
		pthread_create(&ids[i],NULL,fight,(void*)i);
	}

	for(int i = 0; i < 4; i++){
		pthread_join(ids[i], NULL);
	}
	printf("\n");
	printInitial();
	printf("\n");
	printf("%d %d %d %d %d", con[0].A[0], con[0].A[1],con[0].A[2],con[0].A[3],con[0].A[4]);
	
	printf("\n");	
	//close file
	fclose(fp);
	return 0;
}


