#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

struct player                                  
{
                                  
int time;                                   //time remaining in seconds.
string currentLocation;                    //the 'id' of the location where the player is located.                
string currentgoal;                      //the current objective shown to the player
vector<string>memoriesFound;            
string  araState;                      // Saves the current status of the relationship with ARA (NEUTRAL, HELPFUL, HOSTILE).
bool finalModuleFound;                //It becomes 'true' when the player finds the key item at the end.




};

struct location                          //Represents a place in the game world.
{
string description;                    
string locations;                    
bool isHostile;                      //'true' if the location is dangerous
};

struct action                          //Represents a possible action or interaction in the game.
{
string sourceLocation;             
string entry;                      //The exact command the player must type.
string destinationLocation;        
string endMessage;                
};

void playGame();                        //The main function that orchestrates the entire game loop.
void sleep(int time_seconds);                            //Pauses the execution of the program for a specified time.
int load_Locations(vector<location>& locations, const string& file, player &player);                //Read location data
int load_Actions(vector<action>& actions, const string& file);          //Reads action/puzzle data from a text file.
void initialize_player(player & player);                //Sets the player's initial values ​​at the start of a game.
void show_Scene(player & player , const vector<location>& locations);               //Displays the description of the player's current location and status.
string handle_Entry();                  //Captures and returns the command the player types.
void process_Action(string & entry, player, vector<action> actions,const vector<location>& locations);        //Processes the player's command and updates the game state.
bool verify_EndConditions(player);          //Checks if the player has lost or won.
void discover_memory(player&player, string & memory);       //Handles the event of finding a new memory fragment.
void interact_with_Ara(player);         //Manage dialogue and key decisions with the character ARA.
void handle_final_choice(player);           //Manages the sequence of end-game decisions.
void show_final_ending(const player);           //Displays the final text corresponding to the decision made.
void show_credits();                    //Displays the game's ending credits.
void final_game();                              //displays the final message after the credits
