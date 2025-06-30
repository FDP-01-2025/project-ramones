#include "header.h"

void playGame()
{
}

void sleep(int time_ms)
{

}

int load_Locations(vector<location> &locations, const string &file)
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
                handle_hostile_environment(player);
            }
            
        }return 0;
        
    }
    
    cout << "Ubicacion desconocida" << endl;
    
}

int load_Actions(vector<action> &actions, const string &file)
{
    return 0;
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
    return string();
}

void process_Action(string &entry, player, vector<action> actions, const vector<location> &locations)
{
}

void handle_hostile_environment(player &player)
{
}

void discover_memory(player&player, string & memory)
{
}

void show_credits()
{
}

void final_game()
{
}