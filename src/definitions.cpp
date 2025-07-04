
#include "header.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct player
{
     int time;
    string currentLocation;
    string currentgoal;
    vector<string> memoriesFound;
    string araState;
    bool finalModuleFound;
};
    struct location
    {
        string locations;
        string description;
        bool isHostile;
    };

        struct action
        {
            string sourceLocation;
            string entry;
            string destinationLocation;
            string endMessage;
        };
        
    


void playGame()
{
}

void sleep(int time_seconds) //this works for the time, every action that the player does, it waste time, if the time reachs 0, the game is over.
{
    time_seconds=900;
    if (time_seconds >=900)
    {
        cout<< "Se te acabo el tiempo. El reator ha explotado." << endl;
        cout << "=====GAME OVER=====" << endl << endl;
        cout << "                                                                        !!!!!AJAJAJAJAJAJAJA" << endl;
        
    }
    
}

int load_Locations(vector<location> &locations, const string &file, player &player)
{
     ifstream inFile(file);
    if (!inFile.is_open()) {
        cerr << "Error al abrir archivo: " << file << endl;
        return 1;
    }
         string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        location loc;
        string hostile;

        getline(ss, loc.locations, '|');
        getline(ss, loc.description, '|');
        getline(ss, hostile, '|');
        loc.isHostile = (hostile == "1");

        locations.push_back(loc);
    }

    inFile.close();

    // Ubicación inicial
    if (!locations.empty()) {
        player.currentLocation = locations[0].locations;
    }

    return 0;
}

int load_Actions(vector<action> &actions, const string &file)
{
     ifstream inFile(file); // Abrir archivo
    if (!inFile.is_open()) {
        cerr << "Error al abrir el archivo: " << file << endl;
        return 1; // código de error
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        action act;

        getline(ss, act.sourceLocation, '|');     
        getline(ss, act.entry, '|');               
        getline(ss, act.destinationLocation, '|'); 
        getline(ss, act.endMessage, '|');          

        actions.push_back(act);                  
    }

    inFile.close();
return 0;
}

void initialize_player(player &player)  //basic features of the player, time, location, goals, etc.
{
    player.time=10;
    player.currentLocation="Start";
    player.currentgoal= "Encuentra modulos de memoria";
    player.memoriesFound={};
    player.araState="Desactivada";
    player.finalModuleFound= false;
}

void show_Scene(player &player, const vector<location> &locations)  //shows the current scene or location of the player, it depends on the history.
{
    cout << "Tiempo restante: " << player.time << endl;
    for (const auto &loc : locations)
    {
        if (loc.locations==player.currentLocation)
        {
            cout<< "Estas en: " << loc.locations << endl;
            cout<< loc.description<< endl;
            if (loc.isHostile)
            {
                cout<< "Este lugar es hostil!..." << endl;
                cout << "Ten cuidado!" << endl;
                final_game();
            }
            
        }return;
        
    }
    
    cout << "Ubicacion desconocida..." << endl;
    
}

string handle_Entry() // it reads the decitions that the the player is gonna take throughout the game
{
    string input;
    cout<< "Que accion vas a tomar?"<< endl;
    getline(cin,input);

    return string(input);
}

void process_Action(string &entry, player player, vector<action> actions, const vector<location> &locations) 
{// it simply process the action of the player, it reads if it fits on the ".txt" and show the message that corresponds to the action.
    bool actionFound = false;
    for (auto &action :actions)
    {
        if (action.sourceLocation== player.currentLocation && action.entry==entry)
        {
            cout<< action.endMessage << endl;
            player.currentLocation =  action.destinationLocation;
            player.time -= 10;
                if (player.currentLocation == "Laboratorio de experimentos") {
                string memoria = "Memoria del experimento";
                discover_memory(player, memoria);
            } else if (player.currentLocation == "Observatorio estelar") {
                string memoria = "Una mirada al pasado";
                discover_memory(player, memoria);
            } else if (player.currentLocation == "Modulo Final") {
                string memoria = "Última memoria de Ara";
                discover_memory(player, memoria);
            }

            show_Scene(player, locations);
                if (player.time <=0)
                {
                    cout << "Tu tiempo se agoto... el reactor ha explotado. Tu mision fue un fracaso." << endl;
                }
                    actionFound= true;
                    break;
            return;    
        }
        if (!actionFound)
        {
            cout << "No puedes hacer eso aqui..." << endl;
            player.time -= 10;
        }
        
    }
    cout << "No se puede hacer eso aqui. Intenta otra vez." << endl;
}
bool verify_EndConditions(player &player) //checks the conditions of the players and based them on a final of the game.
{
    return player.memoriesFound.size() >= 3 && player.time > 0;
}
void discover_memory(player&player, string & memory) // just shows the update of the account of modules of memories that the player has, and it tells to the player every time it found a module.
{
    player.memoriesFound.push_back(memory);
    cout << "Has encontrado un modulo de memoria: " << memory << endl;
}

void interact_with_Ara(player &player) // it checks the state of ARA and its messages.
{
if(player.araState=="Desactivada")
{
    cout<< " ARA esta siendo activada..." << endl;
    player.araState= "Activa";
    cout << "ARA: Hola, " << player.currentLocation << "parece interesante. Dejame acompanarte en adelante." << endl;
    }   else if (player.araState=="Activa")
    {
        cout << "ARA: Recuerda que tu objetivo actual es: " << player.currentgoal << endl;
    }

}
void handle_final_choice(player &player) // based a final cout depending on the player's decition and shows a fragment of the final it chosed
{
    cout<< "Has llegado al final, has conseguido todos los modulos de memoria...Ahora debes tomar una desicion." << endl;
    cout<< "1. Sacrificarte para salvar la nave" << endl;
    cout << "2.Fucionarte con ARA, descubrir la verdad de todo tu origen." << endl;
    cout << "3.Desconectarte y escapar." << endl;
    string choice;
    getline(cin, choice);

        if (choice=="1")
        {
            player.finalModuleFound=true;
            cout<< "Te sacrificaste heroicamente... la nave ha sido salvada de su fatidica destruccion. Mueres, pero dejas un mensaje en la red: No somos solo líneas de código. Somos... algo más. Controlen sus acciones... o se atendran a las consecuencias." << endl;
            }else if (choice== "2")
            {
                player.finalModuleFound=true;
                cout << "Al fusionarte con ARA descubres que tu eres la mente principal del experimento, ARA es una copia de tu conciencia original y fue quien causó el accidente para evitar que te borraran debido al fallo del experimento, luego de esto... desmayas. Despiertas en un cuerpo mejorado con los recuerdos de ambos y escapas justo antes del colapso. Queda la duda de si eres tú o ARA. " << endl;
                }else if (choice== "3")
                {
                    player.finalModuleFound=true;
                    cout <<"Escapas, pero con fragmentos de memoria vacíos, preguntándote qué olvidaste. ARA desaparece, aunque a veces escuchas su voz en tu cabeza" << endl;
                    }else
                    {
                        cout << "Eleccion invalida... el destino decidira por ti..."<< endl;
                        player.finalModuleFound=true;
                    }  
}
void show_final_ending(const player player) // couts(texts) for the different endings onf the game.
{
 if (player.time >=900)
 {
    cout << "Tu tiempo se ha agotado. No pudiste evitar la explosion... muchas vidas y conocimiento se han perdido." << endl;
    cout << player.currentgoal << "Ha sido un fracaso!!" << endl;
    } else if (player.memoriesFound.size() >= 3)
    {
        cout << "Recuperaste tus recuerdos y el objetivo fue comletado... " << endl;
        cout << "Mision Completada" << endl;
        } else
        {
            cout << " Sobreviviste, pero perdiste gran parte de ti en el camino..." << endl;
        }
}
void final_game() // final message after complete the game( any ending)
{
    cout << "    LLegaste al modulo final    " << endl;
    cout << "Felicidades por completar el juego." << endl;
}
void show_credits() // credits of the developers of this game.
{
    cout << "==========CREDITOS============" << endl;
    cout << "" << endl;
}
