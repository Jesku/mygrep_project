#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

// Function to search for a string within another string and display its position
void searchStringAndPosition(const string& originalString, const string& searchString) {
	// Create lowercase versions of the original and search strings
	string lowerOriginal = originalString;
	string lowerSearch = searchString;

	// Convert both strings to lowercase
	transform(lowerOriginal.begin(), lowerOriginal.end(), lowerOriginal.begin(), ::tolower);
	transform(lowerSearch.begin(), lowerSearch.end(), lowerSearch.begin(), ::tolower);

	// Perform case-insensitive search
	size_t found = lowerOriginal.find(lowerSearch);

	// Display the result of the search
	if (found != string::npos) {
		cout << "\"" << searchString << "\" found in \"" << originalString << "\" in position " << found << endl << endl;
	}
	else {
		cout << "\"" << searchString << "\" NOT found in \"" << originalString << "\"" << endl << endl;
	}
}

// Function to search for occurrences of a string in a file and display the count
void searchStringInFileOccurrencesOnly(const string& filename, const string& searchInFile, bool countOccurrence) {
	ifstream file(filename);
	if (!file) {
		cerr << "Error: Cannot open file " << filename << endl;
		return;
	}

	string line;
	int lineCount = 0;
	while (getline(file, line)) {
		if (line.find(searchInFile) != string::npos) {
			lineCount++;
		}
	}

	cout << "Occurrences of lines containing \"" << searchInFile << "\": " << lineCount << endl;
}

// Function to search for a string in a file and display the line numbers where it occurs
void searchStringInFileLineNumbersOnly(const string& filename, const string& searchInFile, bool lineNumbering) {
	ifstream file(filename);
	if (!file) {
		cerr << "Error: Cannot open file " << filename << endl;
		return;
	}

	string line;
	int lineNumber = 1;
	while (getline(file, line)) {
		if (line.find(searchInFile) != string::npos) {
			cout << "Line \"" << searchInFile << "\" is found on number: " << lineNumber << endl;
		}
		lineNumber++;
	}
}

// Function to search for a string in a file and display both line numbers and occurrences
void searchStringInFileLineNumbersAndOccurrences(const string& filename, const string& searchInFile, bool lineNumbering, bool countOccurrence) {
	ifstream file(filename);
	if (!file) {
		cerr << "Error: Cannot open file " << filename << endl;
		return;
	}

	string line;
	int lineNumber = 1;
	int lineCount = 0;
	while (getline(file, line)) {
		if (line.find(searchInFile) != string::npos) {
			cout << lineNumber << ":" << line << endl;
			lineCount++;
		}
		lineNumber++;
	}

	cout << "Occurrences of lines containing \"" << searchInFile << "\": " << lineCount << endl;
}

// Function to search for a string in a file and display lines that do not contain it
void searchStringInFileReverseSearch(const string& filename, const string& searchInFile, bool reverseSearch) {
	ifstream file(filename);
	if (!file) {
		cerr << "Error: Cannot open file " << filename << endl;
		return;
	}

	string line;
	while (getline(file, line)) {
		if (line.find(searchInFile) == string::npos) {
			cout << line << endl;
		}
	}
}

// Function to search for a string in a file ignoring case sensitivity
void searchStringInFileIgnoreCase(const string& filename, const string& searchInFile, bool ignoreCase) {
	ifstream file(filename);
	if (!file) {
		cerr << "Error: Cannot open file " << filename << endl;
		return;
	}

	string line;
	while (getline(file, line)) {
		string lowercaseLine = line;
		transform(lowercaseLine.begin(), lowercaseLine.end(), lowercaseLine.begin(), ::tolower);
		string lowercaseSearch = searchInFile;
		transform(lowercaseSearch.begin(), lowercaseSearch.end(), lowercaseSearch.begin(), ::tolower);
		if (lowercaseLine.find(lowercaseSearch) != string::npos) {
			cout << line << endl;
		}
	}
}

// Function to search for a string in a file with all specified options
void searchStringInFileAllOptions(const string& filename, const string& searchInFile, bool lineNumbering, bool countOccurrence, bool ignoreCase, bool reverseSearch) {
	ifstream file(filename);
	if (!file) {
		cerr << "Error: Cannot open file " << filename << endl;
		return;
	}

	string line;
	int lineNumber = 1;
	int lineCount = 0;

	while (getline(file, line)) {
		string lineToSearch = line;
		string searchPattern = searchInFile;

		// Apply ignore case if enabled
		if (ignoreCase) {
			transform(lineToSearch.begin(), lineToSearch.end(), lineToSearch.begin(), ::tolower);
			transform(searchPattern.begin(), searchPattern.end(), searchPattern.begin(), ::tolower);
		}

		// Perform reverse search if enabled
		bool searchStringFound = (lineToSearch.find(searchPattern) != string::npos);
		if (reverseSearch) {
			searchStringFound = !searchStringFound;
		}

		// Output based on options
		if (searchStringFound) {
			if (lineNumbering && countOccurrence) {
				cout << lineNumber << ":" << line << endl;
			}
			else if (lineNumbering) {
				cout << "Line \"" << searchInFile << "\" is found on number: " << lineNumber << endl;
			}
			lineCount++;
		}
		lineNumber++;
	}

	// Output occurrence count if requested
	if (countOccurrence) {
		cout << "Occurrences of lines containing \"" << searchInFile << "\": " << lineCount << endl;
	}
}

int main(int argc, char* argv[]) {
	string originalString;
	string searchString;

	// Prompt the user to input the string to search within and the search string
	cout << "Give a string from which to search for: ";
	getline(cin, originalString);

	cout << "Give search string: ";
	getline(cin, searchString);

	// Perform search within the given string
	searchStringAndPosition(originalString, searchString);

	// Check if the required number of command-line arguments is provided
	if (argc < 3) {
		cerr << "Usage: " << argv[0] << " <filename> <searchInFile> [-oo | -ol | -olo | -or | -oi | -olori]" << endl;
		return 1;
	}

	// Extract command-line arguments
	string filename = argv[1];
	string searchInFile = argv[2];
	bool lineNumbering = false;
	bool countOccurrence = false;
	bool ignoreCase = false;
	bool reverseSearch = false;
	
	// Check if file exists
	ifstream file(filename);
	if (!file) {
		cerr << "Error: File " << filename << " does not exist." << endl;
		return 1;
	}

	// Check if file is successfully opened
	if (!file.is_open()) {
		cerr << "Error: Unable to open file " << filename << endl;
		return 1;
	}

	// Parse additional command-line options and perform the corresponding search 
	if (argc > 3) {
		string option = argv[3];
		if (option == "-olo") {
			lineNumbering = true;
			countOccurrence = true;
			searchStringInFileLineNumbersAndOccurrences(filename, searchInFile, lineNumbering, countOccurrence);
		}
		else if (option == "-ol") {
			lineNumbering = true;
			searchStringInFileLineNumbersOnly(filename, searchInFile, lineNumbering);
		}
		else if (option == "-oo") {
			countOccurrence = true;
			searchStringInFileOccurrencesOnly(filename, searchInFile, countOccurrence);
		}
		else if (option == "-oi") {
			ignoreCase = true;
			searchStringInFileIgnoreCase(filename, searchInFile, ignoreCase);
		}
		else if (option == "-or") {
			reverseSearch = true;
			searchStringInFileReverseSearch(filename, searchInFile, reverseSearch);
		}
		else if (option == "-olori") {
			lineNumbering = true;
			countOccurrence = true;
			ignoreCase = true;
			reverseSearch = true;
			searchStringInFileAllOptions(filename, searchInFile, lineNumbering, countOccurrence, ignoreCase, reverseSearch);
		}
		else {
			cerr << "Invalid option: " << option << endl;
			return 1;
		}
	}

	return 0;
}