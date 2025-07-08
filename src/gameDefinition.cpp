#include <iostream>
#include <string>
#include <vector>
#include "header.h"

using namespace std;

// Function to show available actions and interact with the player
void showAndChooseAction(vector<action>& actions, player& player, const vector<location>& locations) {
    // Show current location description
    for (const auto& loc : locations) {
        if (loc.locations == player.currentLocation) {
            cout << "\nYou are in: " << loc.locations << endl;
            cout << loc.description << endl;
            break;
        }
    }

    // Filter available actions
    vector<action> available;
    for (const auto& act : actions) {
        if (act.sourceLocation == player.currentLocation) {
            available.push_back(act);
        }
    }

    if (available.empty()) {
        cout << "There are no available actions here." << endl;
        return;
    }

    // Show menu
    cout << "\nWhat action will you take?" << endl;
    for (size_t i = 0; i < available.size(); ++i) {
        cout << i + 1 << ". " << available[i].entry << endl;
    }

    // Read choice
    int choice = 0;
    while (true) {
        cout << "Enter the number of the action: ";
        if (!(cin >> choice) || choice < 1 || choice > (int)available.size()) {
            cout << "Invalid option. Try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore();
            break;
        }
    }

    // Process the chosen action
    string input = available[choice - 1].entry;
    process_Action(input, player, actions, locations);
}

// Main game function
void playGame() {
    vector<location> locations;
    vector<action> actions;
    player player;

    string locationsFile = "locations.txt";
    string actionsFile = "actions.txt";

    if (load_Locations(locations, locationsFile, player) != 0) {
        cout << "Failed to load location data." << endl;
        return;
    }

    if (load_Actions(actions, actionsFile) != 0) {
        cout << "Failed to load action data." << endl;
        return;
    }

    // Initialize player before starting
    initialize_player(player);

    // Main game loop
    while (player.time > 0 && !player.finalModuleFound) {
        showAndChooseAction(actions, player, locations);
        interact_with_Ara(player);

        if (verify_EndConditions(player)) {
            handle_final_choice(player);
            break;
        }

        if (player.time <= 0) {
            cout << "\nYour time is up... the reactor has exploded." << endl;
            showArt("assets/ascii-art.txt");
            return;
        }
    }

    show_final_ending(player);

    if (player.memoriesFound.size() >= 3 && player.time > 0) {
        showArt("assets/missioncompleted-art.txt");
    } else if (player.time <= 0) {
        showArt("assets/ascii-art.txt");
    }

    final_game();
    show_credits();
    cout << endl << "Thank you for playing... See you next time." << endl;
}
