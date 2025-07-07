#include <iostream>
#include <string>
#include <vector>
#include "header.h"

void playGame(){

    vector<location> locations;
    vector<action> actions;
    player player;

    string locationsFile= "locations.txt";
    string actionsFile= "actions.txt";

    showArt("assets/ECOS-art.txt");
    cout << endl << "Presiona ENTER para empezar tu aventura...." << endl;
    cin.ignore();
    
     if (load_Locations(locations, locationsFile, player)==0) //to load locations
     {
        cout << "Fallo al cargar la ubicacion." << endl;
        return;
     }
        if (load_Actions(actions, actionsFile)==0)
        {
            cout << "Error al cargar las acciones" << endl; //to load actions of the player
            return ;
        }
initialize_player(player);                                   //initializing the principal scene and locations 
show_Scene(player, locations);

            while (player.time>0 && !player.finalModuleFound)
            {
                string entrada= handle_Entry();
                process_Action(entrada, player, actions, locations);
                interact_with_Ara(player);                      // to interact with ARA

                if (verify_EndConditions(player))                   //to verify the final conditions
                {
                    handle_final_choice(player);
                    break;
                }
                if (player.time <= 0) {
                    cout << endl<<"Tu tiempo se ha agotado... el reactor ha explotado." << endl;
                    showArt("assets/ascii-art.txt"); // show game over
                    return;
            }
        
    show_final_ending(player); // at the end of the game, show the following credits and ending
    if (player.memoriesFound.size() >=3 && player.time >0)
    {
        showArt("assets/missioncompleted-art.txt");
    }        else if (player.time<=0)
        {
            showArt("assets/ascii-art.txt");
        }
        
    
    final_game();
    show_credits();   
    cout << endl << "Gracias por jugar...Hasta la proxima" << endl;    
}
