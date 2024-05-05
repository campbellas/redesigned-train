#include <stdio.h>
#include <stdbool.h>


bool fileExistsAndReadable(char *filepath) {	//Checks if a file exists and is readable. If it exists, return true. If it does not, return false.
	FILE *checkExists;
	
	checkExists = fopen(filepath, "r");
	if(checkExists == NULL){
		return false;
	}
	else {
		fclose(checkExists);
		return true;
	}
}

bool fileExistsAndReadable2(FILE** filepointer) {
	if(filepointer == NULL) return false;
	else return true;
}
int numPlaces(int n) {//Recursive
	if (n < 0) return 0;
	else if (n < 10) return 1; //Single digits are proceeded with a zero. 2 is min
	return 1 + numPlaces(n / 10);
}

int countDigit(int n) {
	if (n == 0) return 1;
	int count = 0;
	
	while(n != 0) {
		n = n/10;
		count++;
	}
	return count;
}

void clearBuffer() {
	int c;
	while((c = getchar()) != '\n' && c != EOF){};
}

void writeIt(FILE** filepathway) {
	char newEntry[2048];
	
	
	scanf(" %2047[^\n]", newEntry);//READ UP TO 2047 TO BECAUSE ARRAYS START AT 0 AND TO PREVENT LEAKING DATA
	clearBuffer();
	printf(newEntry);
	fprintf(*filepathway, newEntry);
	
}

void journalWrite() {
	int year = 0;
	int month = 0;
	int day = 0;
	int process = 1;
	int overwriteChoice;
	FILE *queryfile;
	
	do{
		printf("Year[XXXX]:\n");
		scanf("%d", &year);
		clearBuffer();
	}while(countDigit(year) != 4);
	
	do{
		printf("\nMonth[XX]:\n");
		scanf("%d", &month);
		clearBuffer();
	}while((countDigit(month) != 1 && countDigit(month) != 2) || month > 12); //Two conditions satisfy this one
	
	do{
		printf("\nDay[XX]:\n");
		scanf("%d", &day);
		clearBuffer();
	}while((countDigit(day) != 1 && countDigit(day) != 2) || day > 31); //Two conditions satisfy this one	
	
	char target[30];
	
	sprintf(target, "C:\\Journal\\%d%02d%02d.txt", year, month, day);
	queryfile = fopen(target, "r+");
	
	if(fileExistsAndReadable2(&queryfile) == false) {
		queryfile = freopen(target, "w", queryfile);
		writeIt(&queryfile);
		fclose(queryfile);
	}
	
	else {
		while(process == 1) {
			printf("A file already exists for this date. Overwrite? [1 for yes/0 for no]: \n");
			scanf("%d", &overwriteChoice);
			clearBuffer();
			if(overwriteChoice == 1) {
				process = 0;
				queryfile = freopen(target, "w", queryfile);
				writeIt(&queryfile);
				fclose(queryfile);
			
			}
			else if(overwriteChoice == 0) {
				process = 0;
				printf("\nThe file was NOT overwritten\n");
				fclose(queryfile);
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
		}while(countDigit(year) != 4);
		
		do{
			printf("\nMonth[XX]:\n");
			scanf("%d", &month);
			clearBuffer();
		}while(countDigit(month) != 1 && countDigit(month) != 2); //Two conditions satisfy this one
		
		do{
			printf("\nDay[XX]:\n");
			scanf("%d", &day);
			clearBuffer();
		}while(countDigit(day) != 1 && countDigit(day) != 2); //Two conditions satisfy this one
		
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
	int command = 0;
	
	
	while(selector == 1) {
		printf("\n\nOPTIONS: EXIT[0], READ[1] or WRITE[2]\n");
		scanf("%d", &command);
		clearBuffer();
		
		
		if(command == 1) {
			journalRead();
			command = 3;
		}
		else if(command == 2) {
			journalWrite();
			command = 3;
		}
		else if(command == 0) {
			selector = 0;
		}
			
		else{
			printf("ERROR: ENTER A 1 OR A 2\n");
		}
	}
	return 0;
}
