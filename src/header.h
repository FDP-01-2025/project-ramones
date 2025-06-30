#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

struct player                                  //Represents all the data and current state of the player.
{

int lives;                                   //Player's remaining lives.
int time;                                   //Time remaining in seconds.
string currentLocation;                    //The 'id' of the location where the player is located.
vector<string>inventory;                  //List of items the player has collected.
string currentgoal;                      //The current objective shown to the player
vector<string>memoriesFound;            //List of memory fragments the player has discovered.
string  araState;                      // Saves the current status of the relationship with ARA (NEUTRAL, HELPFUL, HOSTILE).
bool finalModuleFound;                //It becomes 'true' when the player finds the key item at the end.




};

struct location                          //Represents a place in the game world.
{
string description;                    //Location identifier
string locations;                     //The text the player sees when at this location.
bool isHostile;                      //'true' if the location is dangerous
};

struct action                          //Represents a possible action or interaction in the game.
{
string sourceLocation;               //The 'id' of the location where you must be to perform the action.
string entry;                       //The exact command the player must type.
string destinationLocation;        //The 'id' of the location the player will move to if the action is successful.
string endMessage;                //The message that is displayed when the action completes successfully.

};

void playGame();//The main function that orchestrates the entire game loop.
void sleep(int time_ms);//Pauses the execution of the program for a specified time.
int load_Locations(vector<location>& locations, const string& file);//Read location data
int load_Actions(vector<action>& actions, const string& file);//Reads action/puzzle data from a text file.
void initialize_player(player & player);//Sets the player's initial values ​​at the start of a game.
void show_Scene(player & player , const vector<location>& locations);//Displays the description of the player's current location and status.
string handle_Entry();//Captures and returns the command the player types.
void process_Action(string & entry, player, vector<action> actions,const vector<location>& locations);//Processes the player's command and updates the game state.
bool verify_EndConditions(player);//Checks if the player has lost (no lives/time) or won.
void handle_hostile_environment(player&player);//Manages what happens when the player is in a hostile zone.
void discover_memory(player&player, string & memory);//Handles the event of finding a new memory fragment.
void interact_with_Ara(player);//Manage dialogue and key decisions with the character ARA.
void handle_final_choice(player);//Manages the sequence of end-game decisions.
void show_final_ending(const player);//Displays the final text corresponding to the decision made.
void show_credits();//Displays the game's ending credits.

