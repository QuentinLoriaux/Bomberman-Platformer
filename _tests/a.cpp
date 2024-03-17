

int main(){

    créer_la_fenetre();
    créer_fonts();
    choisir_default_mode();

    // Pour changer eventuellement de mode : menu => jeu
    while(mode != END){ 
        // Events, assets, not_found textures
        Initialisation_des_variable_communes_a_tout_mode();
        
        chargement_assets();
        initialisation_mode_specific();
        
        while (mode!= END){
            process_events();

            if (duree_d_une_frame_passee){
                actualisation_variables();
                affichage();
            }
        }
    }
}


