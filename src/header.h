#ifndef HEADER_H
#define HEADER_H
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
string  araState;                      // saves the current status of the relationship with ARA (NEUTRAL, HELPFUL, HOSTILE).
bool finalModuleFound;                //it becomes 'true' when the player finds the key item at the end.




};

struct location                          //represents a place in the game world.
{
string description;                    
string locations;                    
bool isHostile;                      //'true' if the location is dangerous
};

struct action                          //represents a possible action or interaction in the game.
{
string sourceLocation;             
string entry;                      //the exact command the player must type.
string destinationLocation;        
string endMessage;                
};

void playGame();                        //the main function that orchestrates the entire game loop.
void sleep(int time_seconds);                            //pauses the execution of the program for a specified time.
int load_Locations(vector<location>& locations, const string& file, player& player);                //read location data
int load_Actions(vector<action>& actions, const string& file);          //reads action/puzzle data from a text file.
void initialize_player(player& player);                //sets the player's initial values ​​at the start of a game.
void showArt(const std::string& archivo);
void show_Scene(const player& player , const vector<location>& locations);               //displays the description of the player's current location and status.
string handle_Entry();                  //captures and returns the command the player types.
void process_Action(string &entry, player player, vector<action> actions, const vector<location> &locations) ;     //processes the player's command and updates the game state.
bool verify_EndConditions(player);          //checks if the player has lost or won.
void discover_memory(player&player, string & memory);       //mandles the event of finding a new memory fragment.
void interact_with_Ara(player);         //manage dialogue and key decisions with the character ARA.
void handle_final_choice(player);           //manages the sequence of end-game decisions.
void show_final_ending(const player);           //displays the final text corresponding to the decision made.
void show_credits();                    //displays the game's ending credits.
void final_game();                              //displays the final message after the credits
#endif
