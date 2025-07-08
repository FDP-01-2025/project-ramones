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
            cout << "\nEstas en: " << loc.locations << endl;
            cout << loc.description << endl;
            break;
        }
    }

     // Filter available actions
    vector<action> disponibles;
    for (const auto& act : actions) {
        if (act.sourceLocation == player.currentLocation) {
            disponibles.push_back(act);
        }
    }

    if (disponibles.empty()) {
        cout << "No hay acciones disponibles aquí." << endl;
        return;
    }

    // Show Menu
    cout << "\nQue accion vas a tomar?" << endl;
    for (size_t i = 0; i < disponibles.size(); ++i) {
        cout << i + 1 << ". " << disponibles[i].entry << endl;
    }

    // Read entrance
    int eleccion = 0;
    while (true) {
        cout << "Ingresa el numero de la accion: ";
        if (!(cin >> eleccion) || eleccion < 1 || eleccion > (int)disponibles.size()) {
            cout << "Opcion invalida. Intenta otra vez." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore();
            break;
        }
    }

    // this process the action that the player choose
    string entrada = disponibles[eleccion - 1].entry;
    process_Action(entrada, player, actions, locations);
}

// Main function of the game
void playGame() {
    vector<location> locations;
    vector<action> actions;
    player player;

    string locationsFile = "locations.txt";
    string actionsFile = "actions.txt";

    if (load_Locations(locations, locationsFile, player) != 0) {
        cout << "Fallo al cargar la ubicación." << endl;
        return;
    }

    if (load_Actions(actions, actionsFile) != 0) {
        cout << "Error al cargar las acciones." << endl;
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
            cout << "\nTu tiempo se ha agotado... el reactor ha explotado." << endl;
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
    cout << endl << "Gracias por jugar... Hasta la proxima" << endl;
}
