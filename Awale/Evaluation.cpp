//
//  Evaluation.cpp
//  Awale
//
//  Created by Pierre TASSEL on 17/12/2017.
//  Copyright © 2017 Pierre TASSEL. All rights reserved.
//

#include "Evaluation.hpp"

/**
 *  Renvoi les cases accesible pour un joueur donne
 *  @bool joueur1 : cases accessible par le joueur 1
 **/
int* casesAccesiblesJoueur(Position* courante, bool joueur1){
    int* cases_accessibles = new int[NB_CASES];
    if (joueur1) {
        for(int i = 0; i < NB_CASES; i++){
            cases_accessibles[i] = courante->cases_jeux[i + courante->cases_jeux[i].case_joueur].case_joueur % (2 * NB_CASES);
        }
    } else {
        for(int i = NB_CASES; i <  2 * NB_CASES; i++){
            cases_accessibles[i - NB_CASES] = courante->cases_jeux[i + courante->cases_jeux[i].case_joueur].case_joueur % (2 * NB_CASES);
        }
    }
    return cases_accessibles;
}

/**
 * Retourne le nombre de case possedant @nombre_cailloux_trou que l'on peut acceder a partir de @cases_accessible
 **/
int nbTrouPeutUtiliser(Position* courante, int* cases_accessible, int nombre_cailloux_trou){
    int compteur = 0;
    for(int i = 0; i < NB_CASES; i++){
        // -1 car pour capturer il faut poser un cailloux
        if(courante->cases_jeux[*(cases_accessible + i)].case_joueur == (nombre_cailloux_trou - 1)){
            compteur++;
        }
    }
    return compteur;
}


/**
 *  Au lieu d'evaluer juste les scores, on evalue aussi la situation
 *  On regarde si ça cree des occasions pour l'adversaire en lui permettant
 *  D'acceder a des trous ou il pourra manger des cailloux par exemple
 **/
int evaluation(Position* courante, bool ordi_joueur1){
    int evalutation = 0;
    int* accessible_j1 = casesAccesiblesJoueur(courante, true);
    int* accessible_j2 = casesAccesiblesJoueur(courante, false);
    int a1 = 6;
    int a2 = 20;
    int a3 = 93;
    int a4 = 93;
    int a5 = 13;
    int a6 = 87;
    // permettra de calculer le nombre de puis permettant d'acceder au cote adverse
    int nombrePuits = 0;
    if(ordi_joueur1 && courante->ordi_joue){
        // cas ou l'ordi est le joueur 1 et nous somme le joueur 1
        evalutation += a1 * nbTrouPeutUtiliser(courante, accessible_j2, 2);
        evalutation += a2 * nbTrouPeutUtiliser(courante, accessible_j2, 3);
        evalutation += a3 * nbTrouPeutUtiliser(courante, accessible_j1, 2);
        evalutation += a4 * nbTrouPeutUtiliser(courante, accessible_j1, 3);
        for(int i = 0; i < NB_CASES; i++){
            // si le j2 peut acceder a notre cote on augmente le compteur
            if(*(accessible_j2 + i) < NB_CASES){
                nombrePuits++;
            }
        }
        evalutation += a5 * nombrePuits;
        nombrePuits = 0;
        for(int i = 0; i < NB_CASES; i++){
            // si on peut acceder au cote de l'adversaire on incremente le compteur
            if(*(accessible_j1 + i) > NB_CASES){
                nombrePuits++;
            }
        }
        evalutation += a6 * nombrePuits;
        
    } else if(!ordi_joueur1 && courante->ordi_joue){
        // cas ou l'ordi est le joueur 2 et nous somme le joueur 2
        evalutation += a1 * nbTrouPeutUtiliser(courante, accessible_j1, 2);
        evalutation += a2 * nbTrouPeutUtiliser(courante, accessible_j1, 3);
        evalutation += a3 * nbTrouPeutUtiliser(courante, accessible_j2, 2);
        evalutation += a4 * nbTrouPeutUtiliser(courante, accessible_j2, 3);
        for(int i = 0; i < NB_CASES; i++){
            // si le j2 peut acceder a notre cote on augmente le compteur
            if(*(accessible_j1 + i) > NB_CASES){
                nombrePuits++;
            }
        }
        evalutation += a5 * nombrePuits;
        nombrePuits = 0;
        for(int i = 0; i < NB_CASES; i++){
            // si on peut acceder au cote de l'adversaire on incremente le compteur
            if(*(accessible_j2 + i) < NB_CASES){
                nombrePuits++;
            }
        }
        evalutation += a6 * nombrePuits;
    } else if (ordi_joueur1 && !courante->ordi_joue){
        // cas ou l'ordi est le joueur 1 et nous somme le joueur 2
        evalutation += a1 * nbTrouPeutUtiliser(courante, accessible_j1, 2);
        evalutation += a2 * nbTrouPeutUtiliser(courante, accessible_j1, 3);
        evalutation += a3 * nbTrouPeutUtiliser(courante, accessible_j2, 2);
        evalutation += a4 * nbTrouPeutUtiliser(courante, accessible_j2, 3);
        for(int i = 0; i < NB_CASES; i++){
            // si le j2 peut acceder a notre cote on augmente le compteur
            if(*(accessible_j1 + i) > NB_CASES){
                nombrePuits++;
            }
        }
        evalutation += a5 * nombrePuits;
        nombrePuits = 0;
        for(int i = 0; i < NB_CASES; i++){
            // si on peut acceder au cote de l'adversaire on incremente le compteur
            if(*(accessible_j2 + i) < NB_CASES){
                nombrePuits++;
            }
        }
        evalutation += a6 * nombrePuits;
    } else {
        // cas ou l'ordi est le joueur 2 et nous somme le joueur 1
        evalutation += a1 * nbTrouPeutUtiliser(courante, accessible_j2, 2);
        evalutation += a2 * nbTrouPeutUtiliser(courante, accessible_j2, 3);
        evalutation += a3 * nbTrouPeutUtiliser(courante, accessible_j1, 2);
        evalutation += a4 * nbTrouPeutUtiliser(courante, accessible_j1, 3);
        for(int i = 0; i < NB_CASES; i++){
            // si le j2 peut acceder a notre cote on augmente le compteur
            if(*(accessible_j2 + i) < NB_CASES){
                nombrePuits++;
            }
        }
        evalutation += a5 * nombrePuits;
        nombrePuits = 0;
        for(int i = 0; i < NB_CASES; i++){
            // si on peut acceder au cote de l'adversaire on incremente le compteur
            if(*(accessible_j1 + i) > NB_CASES){
                nombrePuits++;
            }
        }
        evalutation += a6 * nombrePuits;
    }
    if(accessible_j1 != NULL){
        delete accessible_j1;
    }
    accessible_j1 = NULL;
    if(accessible_j2 != NULL){
        delete accessible_j2;
    }
    accessible_j2 = NULL;
    return evalutation;
}

