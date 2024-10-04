#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_NUM_OF_WORDS 6000

bool processguess(const char* theanswer, const char* theguess) {
	//the clue
	char clue[6] = {'-','-','-','-','-','\0'};
	//flag for used letters in the word
	bool answerflags[5] = { false, false ,false ,false ,false };

	//first pass
	for (int i = 0; i < 5; i++) {
		if (theguess[i] == theanswer[i]) {
			clue[i] = 'G';
			answerflags[i] = true;
		}
	}

	//second pass
	for (int i = 0; i < 5; i++) {
		if (clue[i] == '-') {
			for (int j = 0; j < 5; j++) {
				if (theguess[i] == theanswer[j] && !answerflags[j]) {
					clue[i] = 'Y';
					answerflags[j] = true;
					break;
				}
			}
		}
	}

	printf("\t\t %s\n", clue);
	return strcmp(clue, "GGGGG") == 0;
}

int main() {

	//load the words
	char** wordslist = calloc(MAX_NUM_OF_WORDS,sizeof(char*));
	int wordcount = 0;
	char* fiveletterword = malloc(6 * sizeof(char));
	FILE* wordsfile = fopen("words.txt", "r");

	while (fscanf(wordsfile, "%s", fiveletterword) != EOF && wordcount < MAX_NUM_OF_WORDS) {
		wordslist[wordcount] = fiveletterword;
		wordcount++;
		fiveletterword = malloc(6 * sizeof(char));
	}

	fclose(wordsfile);


	//start the game
	//pick a word randomly
	srand(time(NULL));
	char* answer = wordslist[rand() % wordcount];


	//game loop
	int guessnum = 0;
	bool guessed = false;
	char* guess = malloc(6 * sizeof(char));
	
	while (guessnum < 6 && !guessed) {
		//get guess from player
		printf("input a five letter word and press enter: ");
		scanf("%s", guess);
		printf("you have guessed %s\n", guess);
		guessnum++;

		//process guess
		guessed = processguess(answer, guess);
	}

	//display end of game message
	if (guessed) {
		printf("Congratulations ! you did it in %d times\n", guessnum);
	}
	else {
		printf("Epic fail...the correct word is %s\n", answer);
	}

	for (int i = 0; i < wordcount; i++) {
		free(wordslist[i]);
	}
	free(wordslist);
	//free(fiveletterword); //its said double freeing ? mhm whetevre
	free(guess);

	return 0;
}