#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include "utilities.h"
#include <cstring>

using namespace std;

const char WORD_FILE[] = "words.txt";
const char TEST_FILE[] = "test.txt";
const int MAX_WORDS = 9000;

int runOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum);
void quickSort(char words[][MAXWORDLEN + 1], int start, int end);
void partition(char words[][MAXWORDLEN + 1], int start, int end, int& partitionIndex);
bool found(const char words[][MAXWORDLEN + 1], int start, int end, char target[]);

int main() {
	char words[MAX_WORDS][MAXWORDLEN + 1];
	
	int nWords = getWords(words, 1000, TEST_FILE);
	if (nWords < 1) {
		cerr << "No words were loaded, so I can't play the game";
		return 0;
	}

	cerr << "How many rounds do you want to play? ";
	int n_rounds; cin >> n_rounds;
	if (n_rounds < 0) {
		cout << "The number of rounds must be positive" << endl;
		return 0;
	}
	cin.ignore(10000, '\n');
	quickSort(words, 0, nWords - 1);

	int currentRound = 0;
	int random = randInt(0, 2);
	char secretWord[MAXWORDLEN + 1];
	strcpy(secretWord, words[random]);
	cout << "The secret word is " << strlen(secretWord) << " letters long\n";
	while (currentRound < n_rounds) {
		cerr << "secret word: " << secretWord << endl;
		int score = 0;		
		if (runOneRound(words, nWords, random) == 2)
			cerr << "you found the secret word\n";
		currentRound++;
	}

	return 0;
}

bool found(const char words[][MAXWORDLEN + 1], int start, int end, char target[]) {
	while (start <= end) {
		int middle = (start + end) / 2;
		if (strcmp(words[middle], target) == 0) {
			return true;
		}
		else if (strcmp(words[middle], target) < 0) 
			start = middle + 1;
		else
			end = middle - 1;
	}
	return false;
}

int runOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum) {
	if (nWords <= 0 || wordnum >= nWords || wordnum < 0) return -1;
	cerr << "Probe word: ";
	char secretWord[MAXWORDLEN + 1];
	strcpy(secretWord, words[wordnum]);

	/*for (int i = 0; i < nWords; ++i) {
		cout << words[i] << endl;
	}*/

	const char MAX_PROBE_SIZE = 100;
	char probeWord[MAX_PROBE_SIZE];
	cin.getline(probeWord, MAX_PROBE_SIZE - 1);

	bool validSyntax = true;
	if (strlen(probeWord) < MINWORDLEN || strlen(probeWord) > MAXWORDLEN) {
		cout << "Your probe word must be a word of 4 to 6 lower case letters.\n";
		return -2;
	}

	for (int i = 0; probeWord[i] != '\0'; ++i) {
		if (!islower(probeWord[i])) {
			cout << "Your probe word must be a word of 4 to 6 lower case letters.\n";
			return -2;
		}
	}

	if (!found(words, 0, nWords - 1, probeWord)) {
		cout << "I don't know that word.\n";
		return -2;
	}

	if (strcmp(secretWord, probeWord) == 0) {
		return 2;
	}
	int nStars = 0, nPlanets = 0;
	for (int i = 0; secretWord[i] != '\0'; ++i) {
		for (int j = 0; probeWord[j] != '\0'; ++j) {
			if ((secretWord[i] == probeWord[j]) && (i != j)) {
				nPlanets++;
				secretWord[i] = '0';
				probeWord[j] = '1';
			}
			else if ((secretWord[i] == probeWord[j]) && (i == j)) {
				nStars++;
				secretWord[i] = '2';
				probeWord[j] = '3';
			}
		}
	}
	cout << "Stars: " << nStars << ", Planets: " << nPlanets << endl;
	return 0;
}

void quickSort(char words[][MAXWORDLEN + 1], int start, int end) {
	if (start >= end) return; //stop once the leftIndex is greater than the right index
	int partitionIndex;
	partition(words, start, end, partitionIndex); //partition the array into 2 parts
	quickSort(words, start, partitionIndex - 1); //recursively (divide and conquer) sort the array from start to middle
	quickSort(words, partitionIndex + 1, end); //from middle to end
}

void partition(char words[][MAXWORDLEN + 1], int start, int end, int& partitionIndex) {
	char pivot[MAXWORDLEN + 1]; //choose last element to be the pivot
	strcpy(pivot, words[end]);
	partitionIndex = start; //partition index is initalized to the first index
	for (int i = start; i < end; ++i) { //iterate through the array
		if (strcmp(words[i], words[end]) < 0) {
			char temp[MAXWORDLEN + 1];
			strcpy(temp, words[i]); //swap the element with the element corresponding to the partition index
			strcpy(words[i], words[partitionIndex]);
			strcpy(words[partitionIndex], temp);
			partitionIndex++;
		}
	}
	char temp[MAXWORDLEN + 1];
	strcpy(temp, words[end]);
	strcpy(words[end], words[partitionIndex]);
	strcpy(words[partitionIndex], temp);
}