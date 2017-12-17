//
//  FonctionsUtilitaires.cpp
//  Awale
//
//  Created by Pierre TASSEL on 17/12/2017.
//  Copyright © 2017 Pierre TASSEL. All rights reserved.
//

#include "FonctionsUtilitaires.hpp"

// FONCTION DEBUG QUI AFFICHE LE JEUX
void afficherJeux(Position *courante, bool ordi_commence) {
    std::cout << std::endl;
    for (int i = 0; i < (3*NB_CASES); i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
    for (int i = 0; i < NB_CASES; i++) {
        std::cout << "| " << courante->cases_jeux[i].case_joueur << " | ";
    }
    if(!ordi_commence){
        std::cout << "      score : " << courante->pris_ordi.main_joueur << std::endl;
    } else{
        std::cout << "      score : " << courante->pris_joueur.main_joueur << std::endl;
    }
    std::cout << std::endl;
    for (int i = (2 * NB_CASES) - 1; i >= NB_CASES; i--) {
        std::cout << "| " << courante->cases_jeux[i].case_joueur << " | ";
    }
    if(!ordi_commence){
        std::cout << "      score : " << courante->pris_joueur.main_joueur << std::endl;
    } else{
        std::cout << "      score : " << courante->pris_ordi.main_joueur << std::endl;
    }
    std::cout << std::endl;
    for (int i = 0; i < (3 * NB_CASES); i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
}

bool positionFinale(Position *courante, bool ordi_joueur1) {
    if (courante->pris_ordi.main_joueur >= (8*NB_CASES) || courante->pris_joueur.main_joueur >= (8*NB_CASES)) {
        return true;
    }
    else {
        int somme = 0;
        if (ordi_joueur1) {
            for (int i = 0; i < NB_CASES; i++) {
                somme += courante->cases_jeux[i].case_joueur;
            }
        }
        else {
            for (int i = NB_CASES; i < (NB_CASES * 2); i++) {
                somme += courante->cases_jeux[i].case_joueur;
            }
        }
        return somme == 0;
    }
    return false;
}

bool coupValide(Position *courante, int i, bool ordi_joueur1) {
    if ((i - 1) < 0 || (i - 1) > NB_CASES) {
        return false;
    }
    if(ordi_joueur1 && courante->ordi_joue) {
        return courante->cases_jeux[i - 1].case_joueur > 0;
    } else if(ordi_joueur1 && !courante->ordi_joue) {
        return courante->cases_jeux[i + NB_CASES - 1].case_joueur > 0;
    } else if (!ordi_joueur1 && courante->ordi_joue){
        return courante->cases_jeux[i + NB_CASES - 1].case_joueur > 0;
    } else {
        return courante->cases_jeux[i - 1].case_joueur > 0;
    }
}

void jouerCoup(Position* suivant, Position* courante, int case_a_jouer, bool ordi_joueur1) {
    int i = case_a_jouer - 1;
    // On copie d'abord la memoire pour copier la situation courante dans la suivante
    memcpy(suivant, courante, sizeof(Position));
    // on prend dans la main les cailloux
    int main;
    // si c'est le tour du joueur 2
    if ((!ordi_joueur1 && courante->ordi_joue) || (ordi_joueur1 && !courante->ordi_joue)) {
        i += NB_CASES;
    }
    main = courante->cases_jeux[i].case_joueur;
    suivant->cases_jeux[i].case_joueur = 0;
    int case_courante = i + 1;
    while (main > 0) {
        case_courante = case_courante % (NB_CASES * 2);
        if (case_courante == i) {
            case_courante++;
        }
        suivant->cases_jeux[case_courante].case_joueur++;
        case_courante++;
        main--;
    }
    case_courante = (case_courante - 1) % (NB_CASES * 2);
    if (ordi_joueur1) {
        while (case_courante >= NB_CASES && (suivant->cases_jeux[case_courante].case_joueur == 2 || suivant->cases_jeux[case_courante].case_joueur == 3)) {
            suivant->pris_ordi.main_joueur += suivant->cases_jeux[case_courante].case_joueur;
            suivant->cases_jeux[case_courante].case_joueur = 0;
            case_courante --;
        }
    }
    else {
        while (case_courante >= 0 && case_courante < NB_CASES && (suivant->cases_jeux[case_courante].case_joueur == 2 || suivant->cases_jeux[case_courante].case_joueur == 3)) {
            suivant->pris_ordi.main_joueur += suivant->cases_jeux[case_courante].case_joueur;
            suivant->cases_jeux[case_courante].case_joueur = 0;
            case_courante--;
        }
    }
    suivant->ordi_joue = !courante->ordi_joue;
}

int valeurMinMax(Position *courante, int profondeur, int profondeur_max, bool ordi_joueur1, int bound_a_b) {
    Position prochaine_position;
    int alp_bet_val = ordi_joueur1 ? -100 : 100;
    int tab_valeurs[NB_CASES];
    if (positionFinale(courante, ordi_joueur1)) {
        if (courante->pris_ordi.main_joueur > courante->pris_joueur.main_joueur) {
            return 40;
        }
        else {
            if (courante->pris_ordi.main_joueur < courante->pris_joueur.main_joueur) {
                return -40;
            }
            return 0;
        }
    }
    if (profondeur == profondeur_max) {
        return evaluation(courante, ordi_joueur1);
    }
    for (int i = 0; i < NB_CASES; i++) {
        //si on calcule le coup de l'ordinateur (ie on prend le max) mais que la valeur d'alpha beta du pere
        //(ie le coup jouÈ par l'adversaire, donc le min des fils) est infÈrieure a la valeur courante
        //d'alpha beta, alors l'adversaire ne devrait pas choisir ce fils donc on ne calcul pas le reste de l'arbre
        //inversement si la valeur d'alpha beta est infÈrieure a la valeur alpha beta du pere (ie coup de l'ordi, le max des fils)
        //on ne choisira pas cette branche donc on ne calcule pas le reste de l'arbre
        if ((ordi_joueur1 && (alp_bet_val > bound_a_b)) || (!ordi_joueur1 && (alp_bet_val < bound_a_b))) {
            return alp_bet_val;
        }
        if (coupValide(courante, i + 1, ordi_joueur1)) {
            jouerCoup(&prochaine_position, courante, i + 1, ordi_joueur1);
            // pos_next devient la position courante, et on change le joueur
            tab_valeurs[i] = valeurMinMax(&prochaine_position, profondeur + 1, profondeur_max, !ordi_joueur1, alp_bet_val);
            //la valeur d'alpha beta devient le min/max de la valeur calculÈe et de la valeur alpha beta courante
            //(min/max selon le joueur ordi ou adversaire)
            if ((ordi_joueur1 && (alp_bet_val < tab_valeurs[i])) || (!ordi_joueur1 && (alp_bet_val > tab_valeurs[i]))) {
                alp_bet_val = tab_valeurs[i];
            }
        }
        else {
            if (ordi_joueur1) {
                tab_valeurs[i] = -100;
            }
            else {
                tab_valeurs[i] = 100;
            }
        }
    }
    //on renvoie la valeur de l'alpha beta qui est le min/max calculÈ dynamiquement
    return alp_bet_val;
}

void initGame(Position *courant, bool ordi_commence) {
    for (int i = 0; i < (NB_CASES * 2); i++) {
        courant->cases_jeux[i].case_joueur = 4;
    }
    courant->pris_joueur.main_joueur = 0;
    courant->pris_ordi.main_joueur = 0;
    courant->ordi_joue = ordi_commence;
}

/**
 *  1 si joueur 1, 2 si joueur 2, 0 si null
 **/
int evaluerGagnant(Position *position, bool ordi_j1){
    // si ordi j1 et il gagne
    if(ordi_j1 && position->pris_ordi.main_joueur > position->pris_joueur.main_joueur){
        return 1;
    } else if(!ordi_j1 && position->pris_ordi.main_joueur > position->pris_joueur.main_joueur){
        // si ordi j2 et il gagne
        return  2;
    } else if(ordi_j1 && position->pris_ordi.main_joueur < position->pris_joueur.main_joueur){
        // si ordi j1 et il perd
        return 2;
    } else if(!ordi_j1 && position->pris_ordi.main_joueur < position->pris_joueur.main_joueur){
        // si ordi j2 et il perd
        return 1;
    }
    // sinon il y a match null
    return 0;
}
