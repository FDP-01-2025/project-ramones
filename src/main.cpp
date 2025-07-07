#include <iostream>
#include "header.h"
#include <fstream>
#include <sstream>

void showArt(const std::string& archivo)
{
    ifstream inFile(archivo);
        if (!inFile.is_open()) {
            cerr << "No se pudo abrir el archivo: " << archivo << endl;
            return;
        }

        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }

    inFile.close();
}

int main(){
    showArt("assets/ECOS-art.txt");
        cout<< endl << "Presiona ENTER para comenzar tu historia..." << endl;
        cin.ignore();

        playGame();

        cout << endl << "Gracias por jugar...Hasta la proxima" << endl;


 return 0;
}