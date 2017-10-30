#include <iostream>
#include <string>
#include <cctype>
#include <cassert>

using namespace std;

void resetVariables(int& octave, char& accidental, bool& singleNote, bool& canBeAccidental, bool& canBeOctave);
bool validNotes(string song);
bool validBeats(string song);
bool hasCorrectSyntax(string song);
int encodeSong(string song, string& instructions, int& badBeat);
char encodeNote(int octave, char noteLetter, char accidentalSign);

int main() {
	string instrs;
	int badb;
	instrs = "xxx"; badb = -999;
	assert(hasCorrectSyntax("C#5/"));
	assert(hasCorrectSyntax(""));
	assert(!hasCorrectSyntax("C"));
	assert(!hasCorrectSyntax("#"));
	assert(!hasCorrectSyntax("3")); 
	assert(hasCorrectSyntax("/"));
	assert(hasCorrectSyntax("A/"));
	assert(hasCorrectSyntax("B/"));
	assert(hasCorrectSyntax("C/")); 
	assert(hasCorrectSyntax("D/"));
	assert(hasCorrectSyntax("E/"));
	assert(hasCorrectSyntax("F/"));
	assert(hasCorrectSyntax("G/"));
	assert(!hasCorrectSyntax("H/"));
	assert(!hasCorrectSyntax("e/"));
	assert(!hasCorrectSyntax("#/"));
	assert(!hasCorrectSyntax("5/"));
	assert(!hasCorrectSyntax("#5/"));
	assert(!hasCorrectSyntax("C#"));
	assert(!hasCorrectSyntax("C5"));
	assert(!hasCorrectSyntax("C#5"));
	assert(!hasCorrectSyntax("C5#/"));
	assert(hasCorrectSyntax("C#/"));

	/*assert(encodeSong("F##/", instrs, badb) == 2 && instrs == "xxx" && badb == 1);
	assert(hasCorrectSyntax("D5//D/"));
	instrs = "xxx"; badb = -999;
	assert(encodeSong("D8/56/", instrs, badb)== 2 && instrs == "xxx" && badb == 1);
	cout << instrs << "\t" <<badb << endl;
	assert(!hasCorrectSyntax("D5//Z/"));
	instrs = "xxx"; badb = -999; // so we can detect whether these get changed
	assert(encodeSong("D5//D/", instrs, badb) == 0 && instrs == "R H"  &&  badb == -999);
	instrs = "xxx"; badb = -999; // so we can detect whether these get changed
	assert(encodeSong("D5//Z/", instrs, badb) == 1 && instrs == "xxx"  &&  badb == -999);
	encodeSong("D5//D8/", instrs, badb);
	assert(encodeSong("D5//D8/", instrs, badb) == 2 && instrs == "xxx" &&  badb == 3);*/
	//cout << "bad beat: " << badb << endl;
	//cout << instrs << endl;
	return 0;
}

bool validNotes(string song) {
	for (int i = 0; i < song.length(); ++i) {
		if ((song[i] > 'G' && song[i] != 'b') || (song[i] < 'A' && song[i] != '#' && song[i] != '/' && !isdigit(song[i])))
			return false;
	}
	return true;
}

bool validBeats(string song) {
	return song.length() == 0 || song[song.length() - 1] == '/';
}


bool hasCorrectSyntax(string song) {
	if (!validNotes(song) || !validBeats(song)) return false;
	bool nextCanBeAccidental = false;
	bool nextCanBeOctave = false;
	int begIndex = 0;
	for (int i = 0; i < song.length(); ++i) {
		if (song[i] == '/') {
			string beat = song.substr(begIndex, i - begIndex + 1);
			if (!isalpha(beat[begIndex]) && beat[begIndex] != '/') {
				return false;
			}
			begIndex = i + 1;
			cout << "beat: " << beat;
			for (int j = 0; j < beat.length(); ++j) {		
				if (isalpha(beat[j])) {
					nextCanBeAccidental = true;
					nextCanBeOctave = true;
				}
				else if ((beat[j] == '#' || beat[j] == 'b') && nextCanBeAccidental) {
					nextCanBeAccidental = false;
				}
				else if (isdigit(beat[j]) && nextCanBeOctave) {
					nextCanBeAccidental = false;
					nextCanBeOctave = false;
				}
				else if (beat[j] == '/') {
					cout << "end of beat\n";
				}
				else {
					return false;
				}
			}
		}
	}
	return true;
}

void resetVariables(int& octave, char& accidental, bool& singleNote, bool& canBeAccidental, bool& canBeOctave) {
	octave = 4;
	accidental = ' ';
	singleNote = true;
	canBeAccidental = true;
	canBeOctave = true;
}

int encodeSong(string song, string& instructions, int& badBeat) {
	if (!hasCorrectSyntax(song)) return 1;
	string tempInstructions = instructions;
	instructions.clear();
	int begIndex = 0;
	int beatNumber = 0;
	bool nextCanBeAccidental = false;
	bool nextCanBeOctave = false;
	char accidental = ' ';
	char noteLetter;
	int octave = 4;
	for (int i = 0; i < song.length(); ++i) {
		if (song[i] == '/') {
			beatNumber++;
			cerr << "beatNumber: " << beatNumber << endl;
			string beat = song.substr(begIndex, i - begIndex + 1);
			string encodedBeat = "";
			if (beat.length() == 1) {
				instructions += ' ';
				begIndex = i + 1;
				continue;
			}
			if (!isalpha(song[begIndex])) {
				cerr << i << ": " << song[begIndex] << endl;
				badBeat = beatNumber;
				instructions = tempInstructions;
				return 2;
			}
			begIndex = i + 1;
			bool onlyOneNote = true;
			bool isChord = false;
			for (int j = 0; j < beat.length(); j++) {
				if (isalpha(beat[j]) && beat[j] != 'b') {
					if (!onlyOneNote) {
						isChord = true;
						encodedBeat += encodeNote(octave, noteLetter, accidental);
						//cout << "instructions: " << notes << endl;
					}
					resetVariables(octave, accidental, onlyOneNote, nextCanBeAccidental, nextCanBeOctave);
					noteLetter = beat[j];
				}
				else if ((beat[j] == '#' || beat[j] == 'b') && nextCanBeAccidental) {
					accidental = beat[j];
					nextCanBeAccidental = false;
				}
				else if (isdigit(beat[j]) && nextCanBeOctave) {
					octave = beat[j] - '0';
					if ((octave >= 6 && ((noteLetter == 'C' && accidental == '#') || noteLetter != 'C'))
						|| (octave <= 2 && noteLetter != 'B' && accidental != '#')) {
						badBeat = beatNumber;
						instructions = tempInstructions;
						return 2;
					}

					//cout << "octave: " << octave << endl;
					nextCanBeAccidental = false;
					nextCanBeOctave = false;
				}
				else if (beat[j] == '/') {
					encodedBeat += encodeNote(octave, noteLetter, accidental);
					//cout << notes << endl;
				}
			}
			if (isChord) {
				//cout << "is chord is true\n";
				encodedBeat = "[" + encodedBeat + "]";
			}
			cerr << "incrementing beatnumber\n";
			instructions += encodedBeat;
		}
	}
	return 0;
}

//*************************************
//  encodeNote
//*************************************

// Given an octave number, a note letter, and an accidental sign, return
// the character that the indicated note is encoded as if it is playable.
// Return a space character if it is not playable.
//
// First parameter:   the octave number (the integer 4 is the number of the
//                    octave that starts with middle C, for example).
// Second parameter:  an upper case note letter, 'A' through 'G'
// Third parameter:   '#', 'b', or ' ' (meaning no accidental sign)
//
// Examples:  encodeNote(4, 'A', ' ') returns 'Q'
//            encodeNote(4, 'A', '#') returns '%'
//            encodeNote(4, 'H', ' ') returns ' '

char encodeNote(int octave, char noteLetter, char accidentalSign)
{
	// This check is here solely to report a common CS 31 student error.
	if (octave > 9)
	{
		cerr << "********** encodeNote was called with first argument = "
			<< octave << endl;
	}

	// Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
	//      to -1, 0,   1,   2,   3, ...,  11, 12

	int note;
	switch (noteLetter)
	{
	case 'C':  note = 0; break;
	case 'D':  note = 2; break;
	case 'E':  note = 4; break;
	case 'F':  note = 5; break;
	case 'G':  note = 7; break;
	case 'A':  note = 9; break;
	case 'B':  note = 11; break;
	default:   return ' ';
	}
	switch (accidentalSign)
	{
	case '#':  note++; break;
	case 'b':  note--; break;
	case ' ':  break;
	default:   return ' ';
	}

	// Convert ..., A#1, B1, C2, C#2, D2, ... to
	//         ..., -2,  -1, 0,   1,  2, ...

	int sequenceNumber = 12 * (octave - 2) + note;

	string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
	if (sequenceNumber < 0 || sequenceNumber >= keymap.size())
		return ' ';
	return keymap[sequenceNumber];
}

