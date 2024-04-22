#include <stdio.h>
#include <ctype.h>

/*
NOTES
*I am still struggling to find a way to validate dates upon input. 
*I will have to save that task for when I improve
*04/20/2024 Validating the dates were simpler than expected. Theres
still some degree of trust that the user can be reasonable about dates
But at least now it can tell that years should be four elements long,
months should be one or two elements long but not above 12 in value, and days should
be one or two elements long but never above 31 in value.

Less than 200 lines!
*/

int exists(char *target) {
	FILE *checkExists;
	
	checkExists = fopen(target, "r");
	if(checkExists == NULL){
		return 0;
	}
	else {
		fclose(checkExists);
		return 1;
	}
}

int numPlaces(int n) {//Recursive
	if (n < 0) return 0;
	else if (n < 10) return 1; //Single digits are proceeded with a zero. 2 is min
	return 1 + numPlaces(n / 10);
}

void clearBuffer() {
	int c;
	while((c = getchar()) != '\n' && c != EOF){};
}

void writeIt(char *pathway) {
	FILE *fjournal;
	char newEntry[2048];
	fjournal = fopen(pathway, "w");
	
	scanf(" %2048[^\n]", newEntry);//This is COOOOOOL. Its basically a custom formatter that reads up to 2048 characters
	clearBuffer();
	printf(newEntry);
	fprintf(fjournal, newEntry);
	
	fclose(fjournal);
	
}

void journalWrite() {
	int year = 0;
	int month = 0;
	int day = 0;
	int process = 1;
	int overwriteChoice;
	
	
	do{
		printf("Year[XXXX]:\n");
		scanf("%d", &year);
		clearBuffer();
	}while(numPlaces(year) != 4);
	do{
		printf("\nMonth[XX]:\n");
		scanf("%d", &month);
		clearBuffer();
	}while((numPlaces(month) != 1 && numPlaces(month) != 2) || month > 12); //Two conditions satisfy this one
	do{
		printf("\nDay[XX]:\n");
		scanf("%d", &day);
		clearBuffer();
	}while((numPlaces(day) != 1 && numPlaces(day) != 2) || day > 31); //Two conditions satisfy this one	
	
	
	char target[30];
	
	sprintf(target, "C:\\Journal\\%d%02d%02d.txt", year, month, day);
	//printf(target); //Checks target
	if(exists(target) == 0){//The file does not exist so make it and lets write in it
		writeIt(target);
	}
	else {//The file does exist so lets make sure we want to overwrite it
		while(process == 1){
			printf("A file already exists for this date. Overwrite? [1 for yes/0 for no]: \n");
			scanf("%d", &overwriteChoice);
			clearBuffer();
			if (overwriteChoice == 1){//WRITE FILE
				process = 0;
				writeIt(target);
				//write the file
			}
			else if (overwriteChoice == 0){//DEFAULT: DO NOT WRITE FILE
				process = 0;
				printf("\nThe file was NOT overwritten\n");
			}
			else {
				printf("\nERROR THAT WAS NOT A CHOICE\n");
			}
			
			
		}
	}
}

void journalRead() {//READ JOURNAL ENTRIES IF THEY EXIST. ELSE TELL USER NO.
	FILE *fjournal;
	int year = 0;
	int month = 0;
	int day = 0;
	int process = 1;
	int counter = 0;
	
	while(process != 0){
		//Verify number of digits
		do{
			printf("Year[XXXX]:\n");
			scanf("%d", &year);
			clearBuffer();
		}while(numPlaces(year) != 4);
		do{
			printf("\nMonth[XX]:\n");
			scanf("%d", &month);
			clearBuffer();
		}while(numPlaces(month) != 1 && numPlaces(month) != 2); //Two conditions satisfy this one
		do{
			printf("\nDay[XX]:\n");
			scanf("%d", &day);
			clearBuffer();
		}while(numPlaces(day) != 1 && numPlaces(day) != 2); //Two conditions satisfy this one
		
		char target[30]; //Was 25 if that matters
		
		//The %02d pads the numbers with leading zeros
		sprintf(target, "C:\\Journal\\%d%02d%02d.txt", year, month, day);
		
		//printf(target);
		fjournal = (fopen(target, "r"));
		
		if(fjournal == NULL){
			printf("\nError! Entry not found!\n");
			process = 0;
		}
		else {
			char entry = fgetc(fjournal);
			while(entry != EOF) {
				printf("%c", entry);
				entry = fgetc(fjournal);
				counter++;
				if(counter == 50) {
					printf("\n");
					counter = 0;
				}
			}
			fclose(fjournal);
			process = 0;
		}
	}
}

int main() {
	int selector = 1;
	int command;
	
	
	while(selector == 1) {
		printf("OPTIONS: EXIT[0], READ[1] or WRITE[2]\n");
		scanf("%d", &command);
		clearBuffer();
		
		
		if(command == 1) {
			journalRead();
			selector = 0;
		}
		else if(command == 2) {
			journalWrite();
			selector = 0;
		}
		else if(command == 0) {
			break;
		}
			
		else{
			printf("ERROR: ENTER A 1 OR A 2\n");
		}
	}
	
	
	return 0;
}
