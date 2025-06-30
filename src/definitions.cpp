#include "header.h"

void playGame()
{
}

void sleep(int time_seconds)
{
    time_seconds=900;
    if (time_seconds >=900)
    {
        cout<< "Se te acabo el tiempo. El reator ha explotado." << endl;
        cout << "=====GAME OVER=====" << endl;
        
    }
    
}

int load_Locations(vector<location> &locations, const string &file, player &player)
{
    for (const auto &loc : locations)
    {
        if (loc.locations==player.currentLocation)
        {
            cout<< "Estas en: " << loc.locations << endl;
            cout<< loc.description<< endl;
            if (loc.isHostile)
            {
                cout<< "Este lugar es hostil!" << endl;
                cout << "Ten cuidado!" << endl;
                final_game();
            }
            
        }return 0;
        
    }
    
    cout << "Ubicacion desconocida" << endl;
    
}

int load_Actions(vector<action> &actions, const string &file)
{

}

void initialize_player(player &player)
{
    player.time=0;
    player.currentLocation="Start";
    player.currentgoal= "Encuentra modulos de memoria";
    player.araState="Neutral";
    player.finalModuleFound= false;
}

void show_Scene(player &player, const vector<location> &locations)
{
}

string handle_Entry()
{
    string input;
    cout<< "Que accion vas a tomar?"<< endl;
    getline(cin,input);

    return string(input);
}

void process_Action(string &entry, player player, vector<action> actions, const vector<location> &locations)
{
    for (auto &action :actions)
    {
        if (action.sourceLocation== player.currentLocation && action.entry==entry)
        {
            cout<< action.endMessage << endl;
            player.currentLocation =  action.destinationLocation;
            show_Scene(player, locations);
            return;    
        }
        
    }
    cout << "No se puede hacer eso aqui." << endl;
}
void discover_memory(player&player, string & memory)
{
    player.memoriesFound.push_back(memory);
    cout << "Has encontrado un modulo de memoria: " << memory << endl;
}

void show_credits()
{
    cout << "==========CREDITOS============" << endl;
    cout << "Dyrected by: Alejandro Ayala" << endl;
}

void final_game()
{
    cout << "    LLegaste al modulo final    " << endl;
    cout << "Felicidades por completar el juego." << endl;
}