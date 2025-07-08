#include <iostream>
#include "header.h"
#include <fstream>
#include <sstream>

void showArt(const std::string& file)
{
    ifstream inFile(file);
    if (!inFile.is_open()) {
        cerr << "Could not open file: " << file << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }

    inFile.close();
}

int main() {
    showArt("assets/ECOS-art.txt");
    cout << endl << "Press ENTER to begin your story..." << endl;
    cin.ignore();

    playGame();

    return 0;
}
