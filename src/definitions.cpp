#include "header.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

void sleep(int time_seconds) // each action wastes time, if time reaches 0, it's game over
{
    time_seconds = 450;
    if (time_seconds >= 450)
    {
        cout << "Time is up. The reactor has exploded." << endl;
        cout << "=====GAME OVER=====" << endl << endl;
        cout << "                                                                        !!!!!AJAJAJAJAJAJAJA" << endl;
    }
}

int load_Locations(vector<location> &locations, const string &file, player &player)
{
    ifstream inFile(file);
    if (!inFile.is_open()) {
        cerr << "Error opening file: " << file << endl;
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

    // Initial location
    if (!locations.empty()) {
        player.currentLocation = locations[0].locations;
    }
    return 0;
}

int load_Actions(vector<action> &actions, const string &file)
{
    ifstream inFile(file);
    if (!inFile.is_open()) {
        cerr << "Error opening file: " << file << endl;
        return 1;
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

void initialize_player(player &player) // initial player setup
{
    player.time = 450;
    player.currentLocation = "Incubation room";
    player.currentgoal = "Find memory modules";
    player.memoriesFound = {};
    player.araState = "Deactivated";
    player.finalModuleFound = false;
}

void show_Scene(const player &player, const vector<location> &locations)
{
    cout << "Time remaining: " << player.time << endl;

    for (const auto &loc : locations)
    {
        if (loc.locations == player.currentLocation)
        {
            cout << "You are in: " << loc.locations << endl;
            cout << loc.description << endl;

            if (loc.isHostile)
            {
                cout << "This place is hostile... something moves in the shadows." << endl;
                showArt("assets/ancient_healer.txt");

                if (player.araState == "Deactivated")
                {
                    showArt("assets/ancient_healer.txt");
                    cout << "\nWithout ARA active, you rely only on your instincts..." << endl;
                    cout << "\nWhat do you do?" << endl;
                    cout << "1. Hide behind a console." << endl;
                    cout << "2. Face the noise with a tool you found." << endl;
                    string decision;
                    getline(cin, decision);

                    if (decision == "1")
                    {
                        cout << "\nYou wait silently as a monstrous figure walks past..." << endl;
                        cout << "You survived... for now." << endl;
                    }
                    else if (decision == "2")
                    {
                        cout << "\nYou jump toward the figure, but you're easily overpowered..." << endl;
                        cout << "You did not survive the encounter." << endl;
                        cout << "===== GAME OVER =====" << endl;
                        showArt("assets/ascii-art.txt");
                        exit(0);
                    }
                    else
                    {
                        cout << "\nYou hesitated too long... and that was your end." << endl;
                        cout << "===== GAME OVER =====" << endl;
                        showArt("assets/ascii-art.txt");
                        exit(0);
                    }
                }
                else
                {
                    cout << "ARA analyzes the environment and activates an automatic defense. You've avoided danger." << endl;
                }
            }

            return;
        }
    }

    cout << "Unknown location..." << endl;
}

string handle_Entry() // reads the player's input
{
    string input;
    cout << "What action will you take?" << endl;
    getline(cin, input);
    return input;
}

void process_Action(string &entry, player &player, const vector<action> &actions, const vector<location> &locations)
{
    bool actionFound = false;
    for (auto &action : actions)
    {
        if (action.sourceLocation == player.currentLocation && action.entry == entry)
        {
            cout << action.endMessage << endl;
            player.currentLocation = action.destinationLocation;
            player.time -= 45;

            if (player.currentLocation == "Experiments lab") {
                string memoria = "Experiment Memory";
                discover_memory(player, memoria);
            } else if (player.currentLocation == "Star Observatory") {
                string memoria = "A Glimpse of the Past";
                discover_memory(player, memoria);
            } else if (player.currentLocation == "Final module") {
                string memoria = "Ara's Final Memory";
                discover_memory(player, memoria);
            }

            show_Scene(player, locations);
            if (player.time <= 0)
            {
                cout << "Your time has run out... the reactor exploded. Your mission was a failure." << endl;
            }
            actionFound = true;
            break;
        }
    }
}

bool verify_EndConditions(const player &player)
{
    return player.memoriesFound.size() >= 3 && player.time > 0;
}

void discover_memory(player &player, string &memory)
{
    player.memoriesFound.push_back(memory);
    cout << "You have found a memory module: " << memory << endl;
}

void interact_with_Ara(player &player)
{
    if (player.araState == "Deactivated")
    {
        cout << "ARA is being activated..." << endl;
        player.araState = "Active";
        cout << "ARA: Hello, " << player.currentLocation << " looks interesting. Let me accompany you from now on." << endl;
    }
    else if (player.araState == "Active")
    {
        cout << "ARA: Remember, your current goal is: " << player.currentgoal << endl;
    }
}

void handle_final_choice(player &player)
{
    cout << "You've reached the end, you've gathered all memory modules... Now you must make a decision." << endl;
    cout << "1. Sacrifice yourself to save the ship." << endl;
    cout << "2. Merge with ARA and uncover the truth of your origin." << endl;
    cout << "3. Disconnect and escape." << endl;
    string choice;
    getline(cin, choice);

    if (choice == "1")
    {
        player.finalModuleFound = true;
        cout << "You sacrificed yourself heroically... the ship was saved from its doomed destruction. You die, but leave a message in the system: We are not just lines of code. We are... something more. Control your actions... or face the consequences." << endl;
    }
    else if (choice == "2")
    {
        player.finalModuleFound = true;
        cout << "By merging with ARA, you discover that you are the original mind behind the experiment. ARA is a copy of your consciousness and caused the accident to prevent your deletion. You faint... then awaken in an enhanced body with memories of both. You escape just before the collapse. A doubt remains: are you still you or ARA?" << endl;
        showArt("assets/fusion.txt");
    }
    else if (choice == "3")
    {
        player.finalModuleFound = true;
        cout << "You escape, but with fragmented memories, wondering what you've forgotten. ARA disappears, though sometimes you hear her voice in your mind." << endl;
    }
    else
    {
        cout << "Invalid choice... fate will decide for you..." << endl;
        player.finalModuleFound = true;
    }
}

void show_final_ending(const player player)
{
    if (player.time <= 0)
    {
        cout << "Your time is up. You couldn’t prevent the explosion... many lives and knowledge were lost." << endl;
        cout << player.currentgoal << " was a failure!!" << endl;
    }
    else if (player.memoriesFound.size() >= 3)
    {
        cout << "You recovered your memories and completed the objective..." << endl;
        cout << "Mission Completed" << endl;
    }
    else
    {
        cout << "You survived, but lost much of yourself along the way..." << endl;
    }
}

void final_game()
{
    cout << "    You've reached the final module    " << endl;
    cout << "Congratulations on completing the game." << endl;
}

void show_credits()
{
    cout << endl;
    cout << "==================================================" << endl;
    cout << "                      C R E D I T S              " << endl;
    cout << "==================================================" << endl;
    cout << endl;

    cout << " - Game Name:            ECOS" << endl;
    cout << " - Story:                JULIO PARADA" << endl;
    cout << " - Programming:          RAMones" << endl;
    cout << " - ASCII Art:            ALEJANDRO AYALA, WILMER CABEZAS & ASCIIFLOW" << endl;
    cout << " - Game Engine:          Custom C++ Console Engine" << endl;
    cout << " - Tools:                Visual Studio Code / g++" << endl;
    cout << " - Testing & QA:         Visual Studio Code" << endl;
    cout << " - Inspiration:          Warframe, SOMA, Dead Space, and Undertale" << endl;
    cout << endl;

    cout << " - License and Rights:" << endl;
    cout << " - This game is a personal project and not for commercial use." << endl;
    cout << " - All inspiration and references belong to their original creators." << endl;
    cout << endl;

    cout << "==================================================" << endl;
    cout << "        Thank you for playing! See you soon.      " << endl;
    cout << "==================================================" << endl;
    cout << endl;
}
