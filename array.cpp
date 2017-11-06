#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string value);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int split(string a[], int n, string splitter);
void quickSort(string a[], int start, int end);
void partition(string a[], int start, int end, int& partitionIndex);



int main() {
	string set[8] = { "Howard", "tofu", "Anna", "Calvin", "Godwin", "Tofu", "Jherz" ,"Tofu"};
	string sub[3] = { "Howard", "Godwin", "Tofu" };
	string empty[4] = { "" };
	assert(positionOfMax(set, 8) == 1);
	assert(positionOfMax(set, 0) == -1);
	assert(positionOfMax(empty, 4) == 0);
	assert(positionOfMax(set, -1) == -1);
	assert(positionOfMax(set, -1) == -1);
	assert(rotateLeft(set, 8, 2) == 2 && set[2] == "Calvin" && set[3] == "Godwin" && set[7] == "Anna");
	assert(rotateLeft(set, 0, 2) == -1);
	assert(rotateLeft(set, 2, -1) == -1);
	string set1[8] = { "Howard", "tofu", "Anna", "Calvin", "Godwin", "Tofu", "Jherz" ,"Tofu" };
	assert(rotateLeft(set1, 4, 2) == 2 && set1[2] == "Calvin" && set1[3] == "Anna");
	
	string set2[8] = { "Howard", "tofu", "Anna", "Calvin", "Godwin", "Tofu", "Jherz" ,"Tofu" };
	assert(rotateLeft(set2, 0, -1) == -1);
	assert(countRuns(set2, 8) == 8);
	
	string set3[8] = { "Howard", "Howard", "Anna" };
	assert(countRuns(set3, 2) == 1);
	assert(countRuns(set3, 0) == 0);
	assert(countRuns(set3, -1) == -1);
	
	string h[7] = { "selina", "reed", "diana", "tony", "", "logan", "peter" };
	assert(positionOfMax(h, 7) == 3);
	assert(flip(h, 4) == 4 && h[0] == "tony" && h[3] == "selina" && h[6] == "peter");
	assert(flip(set2, 0) == 0);
	assert(flip(set2, -1) == -1);
	assert(flip(set2, 5) == 5);
	
	string set4[3] = { "Anna", "is", "my gf" };
	string set5[6] = { "Anna", "is", "a", "baller" };
	assert(flip(set4, 0) == 0 && set4[0] == "Anna");
	assert(differ(set1, 8, set3, 8) == 1);
	assert(differ(set1, 8, set3, 0) == 0);
	assert(differ(set1, 5, set3, -1) == -1);
	//assert(differ(set4, 3, set5, 2) == 1);
	assert(subsequence(set4, 2, set5, 4) == -1);
	string set6[4] = {};
	assert(subsequence(set6, 4, set5, 0) == 0);
	assert(subsequence(set6, 0, set5, 0) == 0);
	string set7[5] = { "-2", "1", "2", "3", "4" };
	string set8[5] = { "1", "2", "3" };
	string set9[2] = { "3", "4" };
	assert(subsequence(set7, -1, set8, 0) == -1);
	assert(subsequence(set7, 3, set8, 3) == -1);
	assert(subsequence(set7, 5, set8, 1) == 1);
	assert(subsequence(set7, 5, set9, 1) == 3);
	//assert(subsequence(set6, 2, set5, 1) == 1);
	assert(subsequence(set7, 5, set8, 3) == 1);

	assert(lookupAny(set7, 5, set8, 3) == 1);
	assert(lookupAny(set7, -1, set8, 5) == -1);
	assert(lookupAny(set7, 2, set9, 2) == -1);
	assert(lookupAny(set7, 0, set9, 0) == -1);

	string set10[5] = { "7", "-2", "5", "3", "0" };

	assert(split(set7, 2, "4") == 2);
	assert(split(set10, 3, "7") == 2);

	string f[7] = { "selina", "reed", "diana", "tony", "", "logan", "peter" };
	assert(lookup(f, 7, "logan") == 5);
	assert(lookup(f, 7, "diana") == 2);
	assert(lookup(f, 2, "diana") == -1);
	assert(positionOfMax(f, 7) == 3);

	string g[4] = { "selina", "reed", "peter", "sue" };
	assert(differ(f, 4, g, 4) == 2);
	assert(appendToAll(g, 4, "?") == 4 && g[0] == "selina?" && g[3] == "sue?");
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "peter?" && g[3] == "reed?");

	string e[4] = { "diana", "tony", "", "logan" };
	assert(subsequence(f, 7, e, 4) == 2);

	string d[5] = { "reed", "reed", "reed", "tony", "tony" };
	assert(countRuns(d, 5) == 2);

	string y[3] = { "peter", "diana", "steve" };
	assert(lookupAny(f, 7, y, 3) == 2);
	assert(flip(y, 3) == 3 && y[0] == "steve" && y[2] == "peter");

	assert(split(f, 7, "peter") == 3);

	cerr << "All tests succeeded" << endl;
	
	return 0;
}

int appendToAll(string a[], int n, string value) {
	if (n < 0) return -1;
	for (int i = 0; i < n; ++i) {
		a[i] += value;
	}
	return n;
}

int lookup(const string a[], int n, string value) {
	if (n < 0) return -1;
	for (int i = 0; i < n; ++i) {
		if (a[i] == value) {
			return i;
		}
	}
	return -1;
}

int positionOfMax(const string a[], int n) {
	if (n <= 0) return -1;
	int largestIndex = 0;
	for (int i = 0; i < n; ++i) {
		if (a[i] > a[largestIndex])
			largestIndex = i;
	}
	return largestIndex;
}

int rotateLeft(string a[], int n, int pos) {
	if (n < 0 || pos >= n || pos < 0) return -1;
	string temp = a[pos];
	for (int i = pos; i < n - 1; ++i) {
		a[i] = a[i + 1];
	}
	a[n - 1] = temp;
	return pos;
}

int countRuns(const string a[], int n) {
	if (n < 0) return -1;
	else if (n == 0) return 0;
	int count = 1;
	for (int i = 0; i < n - 1; ++i) {
		if (a[i] != a[i + 1]) 
			count++;
	}
	return count;
}
 
int flip(string a[], int n) {
	if (n < 0) return -1;
	for (int i = 0; i < n/2; ++i) {
		string temp = a[i];
		a[i] = a[n - i - 1];
		a[n - i - 1] = temp;
	}
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0) return -1;
	int smaller = n1;
	if (n2 < n1)
		smaller = n2;
	for (int i = 0; i < smaller; ++i) {
		if (a1[i] != a2[i]) {
			return i;
		}
	}
	return smaller;
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0) return -1;
	if (n2 == 0) return 0;
	int temp = 0, count = 0;
	for(int i = 0; i < n2; ++i) {
		for (int j = temp; j < n1; ++j) {
			if(a2[i] == a1[j]) {
				temp = (j + 1);
				count++;
				if (count == n2) 
					return j - count + 1;
				break;
			}
			else 
				count = 0;
			temp++;
		}
	}
	return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
	if (n1 <= 0 || n2 <= 0) return -1;
	for (int i = 0; i < n1; ++i) {
		for (int j = 0; j < n2; ++j) {
			if (a1[i] == a2[j])
				return i;
		}
	}
	return -1;
}

int split(string a[], int n, string splitter) {
	if (n < 0) return -1;
	quickSort(a, 0, n - 1);
	for (int i = 0; i < n; ++i) {
		if (a[i] >= splitter) return i;
	}
	return n;
}

void quickSort(string a[], int start, int end) {
	if (start >= end) return;
	int partitionIndex;
	partition(a, start, end, partitionIndex);
	quickSort(a, start, partitionIndex - 1);
	quickSort(a, partitionIndex + 1, end);
}

void partition(string a[], int start, int end, int& partitionIndex) {
	string pivot = a[end];
	partitionIndex = start;
	for (int i = start; i < end; ++i) {
		if (a[i] <= a[end]) {
			string temp = a[i];
			a[i] = a[partitionIndex];
			a[partitionIndex] = temp;
			partitionIndex++;
		}
	}
	string temp = a[end];
	a[end] = a[partitionIndex];
	a[partitionIndex] = temp;
}




