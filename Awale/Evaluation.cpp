//
//  Evaluation.cpp
//  Awale
//
//  Created by Pierre TASSEL on 17/12/2017.
//  Copyright � 2017 Pierre TASSEL. All rights reserved.
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
            cases_accessibles[i] = (i + courante->cases_jeux[i].case_joueur) % (2 * NB_CASES);
        }
    } else {
        for(int i = (2 * NB_CASES - 1); i >= NB_CASES; i--){
            if((i - courante->cases_jeux[i - NB_CASES].case_joueur) % (2 * NB_CASES) >= 0){
                cases_accessibles[i - NB_CASES] = (i - courante->cases_jeux[i - NB_CASES].case_joueur) % (2 * NB_CASES);
            }
            else {
                int k = (i - courante->cases_jeux[i - NB_CASES].case_joueur) % (2 * NB_CASES);
                while (k < 0) {
                    k += (2 * NB_CASES);
                }
                cases_accessibles[i - NB_CASES] = k;
            }
        }
    }
    return cases_accessibles;
}

int* caseAtteignable(Position* position) {
	int* res = new int[NB_CASES * 2];
	for (int i = 0; i < 2 * NB_CASES; i++) {
		//la case atteignable est celle qui se trouve a N places plus loin (N = nombre de cailloux) + le nombre de saut de la case de départ
		//(ie le quotient du nombre de cailloux par le nombre de cases total)
		res[i] = i + position->cases_jeux[i].case_joueur + (int)((position->cases_jeux[i].case_joueur) / (NB_CASES * 2));
	}
	return res;
}

/**
* Retourne le nombre de case possedant @nombre_cailloux_trou que l'on peut acceder a partir de @cases_accessible
**/
int nbTrouPeutUtiliser(Position* courante, int* cases_accessible, int nombre_cailloux_trou) {
	int compteur = 0;
	for (int i = 0; i < NB_CASES; i++) {
		// -1 car pour capturer il faut poser un cailloux
		if (courante->cases_jeux[*(cases_accessible + i)].case_joueur == (nombre_cailloux_trou - 1)) {
			compteur++;
		}
	}
	return compteur;
}

/**
*  Au lieu d'evaluer juste les scores, on evalue aussi la situation
*  On regarde si ca cree des occasions pour l'adversaire en lui permettant
*  D'acceder a des trous ou il pourra manger des cailloux par exemple
**/
int evaluation(Position* courante) {
    bool ordi_joueur1 = courante->ordi_joueur1;
    int evalutation = 0;
    /*int* accessible_j1 = casesAccesiblesJoueur(courante, true);
    int* accessible_j2 = casesAccesiblesJoueur(courante, false);*/
	int* casesAccessibles = caseAtteignable(courante);
    if (ordi_joueur1) {
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
            if ((courante->cases_jeux[*(casesAccessibles + i + NB_CASES)].case_joueur + (int)(courante->cases_jeux[i + NB_CASES].case_joueur / (NB_CASES * 2))) == 2) {
                compteur_case3++;
            }
            if ((courante->cases_jeux[*(casesAccessibles + i + NB_CASES)].case_joueur + (int)(courante->cases_jeux[i + NB_CASES].case_joueur / (NB_CASES * 2))) == 1) {
                compteur_case2++;
            }
            if(courante->cases_jeux[i].case_joueur == 0){
                compteurTrouVide++;
            }
            if(*(casesAccessibles + i) >= NB_CASES){
                compteurCasesAccessiblesAdversaire++;
            }
            if(*(casesAccessibles + i + NB_CASES) < NB_CASES){
                compteurCasesAccessibles++;
            }
            if(courante->cases_jeux[i].case_joueur > (2 * NB_CASES)){
                plusDeVingCailloux++;
            }
        }
        evalutation += A1 * compteur_case3;
        evalutation += A2 * courante->pris_ordi.main_joueur;
        evalutation += A3 * compteurCasesAccessibles;
        evalutation += A4 * compteur_case2;
        evalutation += A5 * compteurTrouVide;
        evalutation += A6 * courante->pris_joueur.main_joueur;
        evalutation += A7 * compteurCasesAccessiblesAdversaire;
        evalutation += A8 * plusDeVingCailloux;
    }
    else if (!ordi_joueur1) {
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
            if ((courante->cases_jeux[*(casesAccessibles + i)].case_joueur + (int)(courante->cases_jeux[i].case_joueur / (NB_CASES * 2))) == 2) {
                compteur_case3++;
            }
            if ((courante->cases_jeux[*(casesAccessibles + i)].case_joueur + (int)(courante->cases_jeux[i].case_joueur / (NB_CASES * 2))) == 1) {
                compteur_case2++;
            }
            if(courante->cases_jeux[i + NB_CASES].case_joueur == 0){
                compteurTrouVide++;
            }
            if(*(casesAccessibles + i) >= NB_CASES){
                compteurCasesAccessibles++;
            }
            if(*(casesAccessibles + i + NB_CASES) < NB_CASES){
                compteurCasesAccessiblesAdversaire++;
            }
            if(courante->cases_jeux[i + NB_CASES].case_joueur > (2 * NB_CASES)){
                plusDeVingCailloux++;
            }
        }
        evalutation += A1 * compteur_case3;
        evalutation += A2 * courante->pris_ordi.main_joueur;
        evalutation += A3 * compteurCasesAccessibles;
        evalutation += A4 * compteur_case2;
        evalutation += A5 * compteurTrouVide;
        evalutation += A6 * courante->pris_joueur.main_joueur;
        evalutation += A7 * compteurCasesAccessiblesAdversaire;
        evalutation += A8 * plusDeVingCailloux;
    }
	if (casesAccessibles != NULL) {
		delete casesAccessibles;
	}
	casesAccessibles = NULL;
    return evalutation;
}

int basicEvaluation(Position* courante) {
	return 5 * (courante->pris_ordi.main_joueur - courante->pris_joueur.main_joueur);
}
