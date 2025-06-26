#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

struct player
{
int lives;
int time;
string currentLocation;
vector<string>inventory;
string currentgoal;
vector<string>memoriesFound;
string  araState;
bool finalModuleFound;

};

struct location
{
string description;
string locations;
bool isHostile;
};

struct action
{
string sourceLocation;
string entry;
string destinationLocation;
string endMessage;

};
void playGame;
void sleep(int time_ms);
int load_Locations(vector<location>& locations, const string& file);
int load_Actions(vector<action>& actions, const string& file);
void initialize_player(player & player);
void show_Scene(player & player , const vector<location>& locations);
string handle_Entry();
void process_Action(string & entry, player, vector<action> actions,const vector<location>& locations);
bool verify_EndConditions(player);
void handle_hostile_environment(player&player);
void discover_memory(player&player, string & memory);
void interact_with_Ara(player);
void handle_final_choice(player);
void show_final_ending(const player);
void show_credits();
void final_game();
