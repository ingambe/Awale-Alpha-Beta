//
//  TestGenerationCoefficient.cpp
//  Awale
//
//  Created by Pierre TASSEL on 19/12/2017.
//  Copyright © 2017 Pierre TASSEL. All rights reserved.
//

#include "TestGenerationCoefficient.hpp"

/**
 *  Cette version de la fonctiond d'evaluation est utilise quand
 *  on cherche les meuilleurs coefficiants pour a1, a2, ..., aN
 **/
int evaluation(Position* courante, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) {
    bool ordi_joueur1 = courante->ordi_joueur1;
    int evalutation = 0;
    int* accessible_j1 = casesAccesiblesJoueur(courante, true);
    int* accessible_j2 = casesAccesiblesJoueur(courante, false);
    if (ordi_joueur1 && courante->ordi_joue) {
        // cas ou l'ordi est le joueur 1 et nous somme le joueur 1
        int compteur_case3 = 0;
        int compteur_case2 = 0;
        int compteurTrouVide = 0;
        //nb de trou accessible chez l'adversaire
        int compteurCasesAccessiblesAdversaire = 0;
        // nb de trou accessible chez nous par l'adversaire
        int compteurCasesAccessibles = 0;
        int plusDeVingCailloux = 0;
        for (int i = 0; i < NB_CASES; i++) {
            // -1 car pour capturer il faut poser un cailloux
            // rajout condition (i != *(cases_accessible + i) || i >= (2 * NB_CASES)) car casesAccesiblesJoueur renvoit la case courante si il y a 0 cailloux dedans
            // donc si on peut acceder a notre case il faut que l'on puisse faire un tour complet
            if (courante->cases_jeux[*(accessible_j2 + i)].case_joueur == 2 && (i != *(accessible_j2 + i) || i >= (2 * NB_CASES))) {
                compteur_case3++;
            }
            if (courante->cases_jeux[*(accessible_j2 + i)].case_joueur == 0 && (i != *(accessible_j2 + i) || i >= (2 * NB_CASES))) {
                compteur_case2++;
            }
            if(courante->cases_jeux[i].case_joueur == 0){
                compteurTrouVide++;
            }
            if(*(accessible_j1 + i) >= NB_CASES){
                compteurCasesAccessiblesAdversaire++;
            }
            if(*(accessible_j2 + i) < NB_CASES){
                compteurCasesAccessibles++;
            }
            if(courante->cases_jeux[i].case_joueur > (2 * NB_CASES)){
                plusDeVingCailloux++;
            }
        }
        evalutation += a1 * compteur_case3;
        evalutation += a2 * courante->pris_ordi.main_joueur;
        evalutation += a3 * compteurCasesAccessibles;
        evalutation += a4 * compteur_case2;
        evalutation += a5 * compteurTrouVide;
        evalutation += a6 * courante->pris_joueur.main_joueur;
        evalutation += a7 * compteurCasesAccessiblesAdversaire;
        evalutation += a8 * plusDeVingCailloux;
    }
    else if (!ordi_joueur1 && courante->ordi_joue) {
        // cas ou l'ordi est le joueur 2 et nous somme le joueur 2
        int compteur_case3 = 0;
        int compteur_case2 = 0;
        int compteurTrouVide = 0;
        //nb de trou accessible chez l'adversaire
        int compteurCasesAccessiblesAdversaire = 0;
        // nb de trou accessible chez nous par l'adversaire
        int compteurCasesAccessibles = 0;
        int plusDeVingCailloux = 0;
        for (int i = 0; i < NB_CASES; i++) {
            // -1 car pour capturer il faut poser un cailloux
            // rajout condition (i != *(cases_accessible + i) || i >= (2 * NB_CASES)) car casesAccesiblesJoueur renvoit la case courante si il y a 0 cailloux dedans
            // donc si on peut acceder a notre case il faut que l'on puisse faire un tour complet
            if (courante->cases_jeux[*(accessible_j1 + i) + NB_CASES].case_joueur == 2 && (i + NB_CASES != *(accessible_j1 + i) || i >= (2 * NB_CASES))) {
                compteur_case3++;
            }
            if (courante->cases_jeux[*(accessible_j1 + i) + NB_CASES].case_joueur == 0 && (i + NB_CASES != *(accessible_j1 + i) || i >= (2 * NB_CASES))) {
                compteur_case2++;
            }
            if(courante->cases_jeux[i + NB_CASES].case_joueur == 0){
                compteurTrouVide++;
            }
            if(*(accessible_j1 + i) >= NB_CASES){
                compteurCasesAccessibles++;
            }
            if(*(accessible_j2 + i) < NB_CASES){
                compteurCasesAccessiblesAdversaire++;
            }
            if(courante->cases_jeux[i + NB_CASES].case_joueur > (2 * NB_CASES)){
                plusDeVingCailloux++;
            }
        }
        evalutation += a1 * compteur_case3;
        evalutation += a2 * courante->pris_ordi.main_joueur;
        evalutation += a3 * compteurCasesAccessibles;
        evalutation += a4 * compteur_case2;
        evalutation += a5 * compteurTrouVide;
        evalutation += a6 * courante->pris_joueur.main_joueur;
        evalutation += a7 * compteurCasesAccessiblesAdversaire;
        evalutation += a8 * plusDeVingCailloux;
    }
    else if (ordi_joueur1 && !courante->ordi_joue) {
        // cas ou l'ordi est le joueur 1 et nous somme le joueur 2
        int compteur_case3 = 0;
        int compteur_case2 = 0;
        int compteurTrouVide = 0;
        //nb de trou accessible chez l'adversaire
        int compteurCasesAccessiblesAdversaire = 0;
        // nb de trou accessible chez nous par l'adversaire
        int compteurCasesAccessibles = 0;
        int plusDeVingCailloux = 0;
        for (int i = 0; i < NB_CASES; i++) {
            // -1 car pour capturer il faut poser un cailloux
            // rajout condition (i != *(cases_accessible + i) || i >= (2 * NB_CASES)) car casesAccesiblesJoueur renvoit la case courante si il y a 0 cailloux dedans
            // donc si on peut acceder a notre case il faut que l'on puisse faire un tour complet
            if (courante->cases_jeux[*(accessible_j1 + i) + NB_CASES].case_joueur == 2 && (i + NB_CASES != *(accessible_j1 + i) || i >= (2 * NB_CASES))) {
                compteur_case3++;
            }
            if (courante->cases_jeux[*(accessible_j1 + i) + NB_CASES].case_joueur == 0 && (i + NB_CASES != *(accessible_j1 + i) || i >= (2 * NB_CASES))) {
                compteur_case2++;
            }
            if(courante->cases_jeux[i + NB_CASES].case_joueur == 0){
                compteurTrouVide++;
            }
            if(*(accessible_j1 + i) >= NB_CASES){
                compteurCasesAccessibles++;
            }
            if(*(accessible_j2 + i) < NB_CASES){
                compteurCasesAccessiblesAdversaire++;
            }
            if(courante->cases_jeux[i + NB_CASES].case_joueur > (2 * NB_CASES)){
                plusDeVingCailloux++;
            }
        }
        evalutation += a1 * compteur_case3;
        evalutation += a2 * courante->pris_joueur.main_joueur;
        evalutation += a3 * compteurCasesAccessibles;
        evalutation += a4 * compteur_case2;
        evalutation += a5 * compteurTrouVide;
        evalutation += a6 * courante->pris_ordi.main_joueur;
        evalutation += a7 * compteurCasesAccessiblesAdversaire;
        evalutation += a8 * plusDeVingCailloux;
    }
    else {
        // cas ou l'ordi est le joueur 2 et nous somme le joueur 1
        int compteur_case3 = 0;
        int compteur_case2 = 0;
        int compteurTrouVide = 0;
        //nb de trou accessible chez l'adversaire
        int compteurCasesAccessiblesAdversaire = 0;
        // nb de trou accessible chez nous par l'adversaire
        int compteurCasesAccessibles = 0;
        int plusDeVingCailloux = 0;
        for (int i = 0; i < NB_CASES; i++) {
            // -1 car pour capturer il faut poser un cailloux
            // rajout condition (i != *(cases_accessible + i) || i >= (2 * NB_CASES)) car casesAccesiblesJoueur renvoit la case courante si il y a 0 cailloux dedans
            // donc si on peut acceder a notre case il faut que l'on puisse faire un tour complet
            if (courante->cases_jeux[*(accessible_j2 + i)].case_joueur == 2 && (i != *(accessible_j2 + i) || i >= (2 * NB_CASES))) {
                compteur_case3++;
            }
            if (courante->cases_jeux[*(accessible_j2 + i)].case_joueur == 0 && (i != *(accessible_j2 + i) || i >= (2 * NB_CASES))) {
                compteur_case2++;
            }
            if(courante->cases_jeux[i].case_joueur == 0){
                compteurTrouVide++;
            }
            if(*(accessible_j1 + i) >= NB_CASES){
                compteurCasesAccessiblesAdversaire++;
            }
            if(*(accessible_j2 + i) < NB_CASES){
                compteurCasesAccessibles++;
            }
            if(courante->cases_jeux[i].case_joueur > (2 * NB_CASES)){
                plusDeVingCailloux++;
            }
        }
        evalutation += a1 * compteur_case3;
        evalutation += a2 * courante->pris_joueur.main_joueur;
        evalutation += a3 * compteurCasesAccessibles;
        evalutation += a4 * compteur_case2;
        evalutation += a5 * compteurTrouVide;
        evalutation += a6 * courante->pris_ordi.main_joueur;
        evalutation += a7 * compteurCasesAccessiblesAdversaire;
        evalutation += a8 * plusDeVingCailloux;
    }
    if (accessible_j1 != NULL) {
        delete accessible_j1;
    }
    accessible_j1 = NULL;
    if (accessible_j2 != NULL) {
        delete accessible_j2;
    }
    accessible_j2 = NULL;
    return evalutation;
}

int prochain_coup_1(Position* courante, int profondeur, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) {
    Position prochaine_position;
    int valeursMinMax[NB_CASES];
    int case_a_jouer = 1;
    //on commence a calculer l'arbre a partir de la case jouable la plus a "petite"
    while (!coupValide(courante, case_a_jouer) && case_a_jouer <= NB_CASES) {
        case_a_jouer++;
    }
    //si aucune case n'est jouable -> on renvoie -1 (une erreur)
    if (case_a_jouer > NB_CASES) {
        return -1;
    }
    //on initialise le resultat en calculant la valeur minmax du sous arbre a partir du coup de base
    jouerCoup(&prochaine_position, courante, case_a_jouer);
    valeursMinMax[case_a_jouer - 1] = valeurMinMaxMod(&prochaine_position, 1, profondeur, -100, true, a1, a2, a3, a4, a5, a6, a7, a8);
    for (int i = case_a_jouer; i < NB_CASES; i++) {
        if (coupValide(courante, i + 1)) {
            //on calcule donc tous les sous arbres correspondants a chaque coups qui sont jouables
            jouerCoup(&prochaine_position, courante, i + 1);
            valeursMinMax[i] = valeurMinMaxMod(&prochaine_position, 1, profondeur, valeursMinMax[case_a_jouer - 1], true, a1, a2, a3, a4, a5, a6, a7, a8);            //On est dans le cas ou l'on calcule le coup a jouer par l'ordi donc on prend le max des valeurs minmax des fils
            if (valeursMinMax[i] > valeursMinMax[case_a_jouer - 1]) {
                //on modifie la valeur de resultat le cas echeant
                case_a_jouer = i + 1;
            }
        }
    }
    return case_a_jouer;
}

int prochain_coup_2(Position* courante, int profondeur) {
    Position prochaine_position;
    int valeursMinMax[NB_CASES];
    int case_a_jouer = 1;
    //on commence a calculer l'arbre a partir de la case jouable la plus a "petite"
    while (!coupValide(courante, case_a_jouer) && case_a_jouer <= NB_CASES) {
        case_a_jouer++;
    }
    //si aucune case n'est jouable -> on renvoie -1 (une erreur)
    if (case_a_jouer > NB_CASES) {
        return -1;
    }
    //on initialise le resultat en calculant la valeur minmax du sous arbre a partir du coup de base
    jouerCoup(&prochaine_position, courante, case_a_jouer);
    for (int i = case_a_jouer; i < NB_CASES; i++) {
        valeursMinMax[i] = valeurMinMaxMod(&prochaine_position, 1, profondeur, valeursMinMax[case_a_jouer - 1], false, 0, 0, 0, 0, 0, 0, 0, 0);
        if (coupValide(courante, i + 1)) {
            //on calcule donc tous les sous arbres correspondants a chaque coups qui sont jouables
            jouerCoup(&prochaine_position, courante, i + 1);
            valeursMinMax[i] = valeurMinMaxMod(&prochaine_position, 1, profondeur, 100, false, 0, 0, 0, 0, 0, 0, 0, 0);
            //On est dans le cas ou l'on calcule le coup a jouer par l'ordi donc on prend le max des valeurs minmax des fils
            if (valeursMinMax[i] < valeursMinMax[case_a_jouer - 1]) {
                //on modifie la valeur de resultat le cas echeant
                case_a_jouer = i + 1;
            }
        }
    }
    return case_a_jouer;
}

int valeurMinMaxMod(Position *courante, int profondeur, int profondeur_max, int bound_a_b, bool coef, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) {
    Position prochaine_position;
    int alp_bet_val = courante->ordi_joue ? -10000000 : 10000000;
    int tab_valeurs[NB_CASES];
    if (positionFinale(courante)) {
        if (courante->pris_ordi.main_joueur > courante->pris_joueur.main_joueur) {
            return 40000000;
        }
        else {
            if (courante->pris_ordi.main_joueur < courante->pris_joueur.main_joueur) {
                return -40000000;
            }
            return 0;
        }
    }
    if (profondeur == profondeur_max) {
        if (coef) {
            return evaluation(courante, a1, a2, a3, a4, a5, a6, a7, a8);
        }
        else {
            return basicEvaluation(courante);
        }
    }
    for (int i = 0; i < NB_CASES; i++) {
        //si on calcule le coup de l'ordinateur (ie on prend le max) mais que la valeur d'alpha beta du pere
        //(ie le coup jou� par l'adversaire, donc le min des fils) est inf�rieure a la valeur courante
        //d'alpha beta, alors l'adversaire ne devrait pas choisir ce fils donc on ne calcul pas le reste de l'arbre
        //inversement si la valeur d'alpha beta est inf�rieure a la valeur alpha beta du pere (ie coup de l'ordi, le max des fils)
        //on ne choisira pas cette branche donc on ne calcule pas le reste de l'arbre
        if ((courante->ordi_joue && (alp_bet_val > bound_a_b)) || (!courante->ordi_joue && (alp_bet_val < bound_a_b))) {
            return alp_bet_val;
        }
        if (coupValide(courante, i + 1)) {
            jouerCoup(&prochaine_position, courante, i + 1);
            // pos_next devient la position courante, et on change le joueur
            tab_valeurs[i] = valeurMinMaxMod(&prochaine_position, profondeur + 1, profondeur_max, alp_bet_val, coef, a1, a2 ,a3 ,a4,a5,a6,a7,a8);
            //la valeur d'alpha beta devient le min/max de la valeur calcul�e et de la valeur alpha beta courante
            //(min/max selon le joueur ordi ou adversaire)
            if ((courante->ordi_joue && (alp_bet_val < tab_valeurs[i])) || (!courante->ordi_joue && (alp_bet_val > tab_valeurs[i]))) {
                alp_bet_val = tab_valeurs[i];
            }
        }
        else {
            if (courante->ordi_joue) {
                tab_valeurs[i] = -1000000;
            }
            else {
                tab_valeurs[i] = 1000000;
            }
        }
    }
    //on renvoie la valeur de l'alpha beta qui est le min/max calcul� dynamiquement
    return alp_bet_val;
}

int jouerPartieDeuxRobot(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) {
    srand((unsigned int) time(NULL));
    Position position;
    Position positionSuivante;
    bool ordi_commence = true;
    bool j1 = true;
    initGame(&position, ordi_commence);
    int coup = 0;
    int nbCoup = 0;
    while (!positionFinale(&position) && nbCoup < 1000) {
        if (position.ordi_joue) {
            coup = prochain_coup_1(&position, 5, a1, a2, a3, a4, a5, a6, a7, a8);
        }
        else {
            coup = prochain_coup_2(&position, 5);
        }
        if (!coupValide(&position, coup)) {
            std::cout << "bug moteur jeux" << std::endl;
            afficherJeux(&position);
            std::cout << "le coup : " << coup << (position.ordi_joue && ordi_commence ? " joue par le joueur 1" : " joue par le joueur 2") << std::endl;
            std::cout << "robot pierre : " << (ordi_commence ? " oui" : " non") << std::endl;
            std::cout << "robot : " << ordi_commence << " tour robot :" << position.ordi_joue << std::endl;
            exit(0);
        }
        jouerCoup(&positionSuivante, &position, coup);
        position = positionSuivante;
        j1 = !j1;
        nbCoup++;
    }
    int gagnant = evaluerGagnant(&position);
    // si c'est l'ordi qui gagne (la fonction avec les parametres choisis)
    if (gagnant == 1 && ordi_commence) {
        return 1;
    }
    else if (gagnant == 2 && !ordi_commence) {
        return 1;
    }
    return 0;
}

void determinerCoeff() {
    int coeff[8];
    int maximum = 0;
    int resultat = 0;
    for (int a1 = -10; a1 <= 10; a1++) {
        for (int a2 = -10; a2 <= 10; a2++) {
            for (int a3 = -10; a3 <= 10; a3++) {
                for (int a4 = -10; a4 <= 10; a4++) {
                    for (int a5 = -10; a5 <= 10; a5++) {
                        for (int a6 = -10; a6 <= 10; a6++) {
                            for (int a7 = -10; a7 <= 10; a7++) {
                                for (int a8 = -10; a8 <= 10; a8++) {
                                    resultat = 0;
                                    for (int i = 0; i < 20; i++) {
                                        resultat += jouerPartieDeuxRobot(a1, a2, a3, a4, a5, a6, a7, a8);
                                    }
                                    if (resultat >= maximum) {
                                        maximum = resultat;
                                        coeff[0] = a1;
                                        coeff[1] = a2;
                                        coeff[2] = a3;
                                        coeff[3] = a4;
                                        coeff[4] = a5;
                                        coeff[5] = a6;
                                        coeff[6] = a7;
                                        coeff[7] = a8;
                                        std::cout << "Meuilleur coeff trouvee : " << std::endl;
                                        std::cout << "a1 : " << a1 << " a2 : " << a2 << " a3 : " << a3 << " a4 : " << a4 << " a5 : " << a5 << " a6 : " << a6 << " a7 : " << a7 << " a8 : " << a8 <<  std::endl;
                                        std::cout << "resultat : " << maximum << " / 20" << std::endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
