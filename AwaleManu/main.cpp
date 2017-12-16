//
//  main.cpp
//  Awale
//
//  Created by Pierre TASSEL on 14/12/2017.
//  Copyright © 2017 Pierre TASSEL. All rights reserved.
//
#define LOG_MAX_CAILLOUX 8
#define LOG_MAX_CAILLOUX_MAIN 6
#define NB_CASES 6
#include <iostream>
#include <bitset>
#include <stdio.h>
#include <stdlib.h>

/**
*  il y a 80 cailloux sur le plateau, inutile d'utiliser plus de 8 bits pour
*  representer le nombre de cailloux par case
**/
struct Cases_joueur {
	unsigned case_joueur : LOG_MAX_CAILLOUX;
};

/**
*  on arrete la partie quand un des deux joueurs a plus de 25 cailloux, soit 6 bits
**/
struct Main_joueur {
	unsigned main_joueur : LOG_MAX_CAILLOUX_MAIN;
};

struct Position {
	Cases_joueur cases_jeux[2 * NB_CASES];
	Main_joueur pris_joueur;
	Main_joueur pris_ordi;
};


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

int evaluation(Position* courante, bool ordi_joueur1) {
	if (ordi_joueur1) {
		return courante->pris_ordi.main_joueur - courante->pris_joueur.main_joueur;
	}
	return courante->pris_joueur.main_joueur - courante->pris_ordi.main_joueur;
}

// FONCTION DEBUG QUI AFFICHE LE JEUX
void afficherJeux(Position *courante) {
	std::cout << std::endl;
	for (int i = 0; i < (3*NB_CASES); i++) {
		std::cout << "-";
	}
	std::cout << std::endl;
	for (int i = (2*NB_CASES)-1; i > (NB_CASES - 1); i--) {
		std::cout << "| " << courante->cases_jeux[i].case_joueur << " | ";
	}
	std::cout << std::endl;
	for (int i = 0; i < NB_CASES; i++) {
		std::cout << "| " << courante->cases_jeux[i].case_joueur << " | ";
	}
	std::cout << std::endl;
	for (int i = 0; i < (3 * NB_CASES); i++) {
		std::cout << "-";
	}
	std::cout << std::endl;
}

bool coupValide(Position *courante, int i, bool ordi_joueur1) {
	if ((i - 1) < 0 || (i - 1) > NB_CASES) {
		return false;
	}
	if (ordi_joueur1) {
		return courante->cases_jeux[i - 1].case_joueur > 0;
	}
	return courante->cases_jeux[i + NB_CASES - 1].case_joueur > 0;;
}

void jouerCoup(Position* suivant, Position* courante, int case_a_jouer, bool ordi_joueur1) {
	int i = case_a_jouer - 1;
	// On copie d'abord la memoire pour copier la situation courante dans la suivante
	//std::cout << "cp 1 :" << std::endl;
	//afficherJeux(courante);
	memcpy(suivant, courante, sizeof(Position));
	//std::cout << "cp 2 :" << std::endl;
	//afficherJeux(suivant);
	// on prend dans la main les cailloux
	int main;
	if (!ordi_joueur1) {
		i += NB_CASES;
	}
	for (int j = 0; j <= (NB_CASES * 2); j++) {
		suivant->cases_jeux[j].case_joueur = courante->cases_jeux[j].case_joueur;
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
			std::cout << "case courante prise " << case_courante << std::endl;
			suivant->pris_ordi.main_joueur += suivant->cases_jeux[case_courante].case_joueur;
			suivant->cases_jeux[case_courante].case_joueur = 0;
			case_courante--;
		}
	}
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
		//(ie le coup joué par l'adversaire, donc le min des fils) est inférieure a la valeur courante
		//d'alpha beta, alors l'adversaire ne devrait pas choisir ce fils donc on ne calcul pas le reste de l'arbre
		//inversement si la valeur d'alpha beta est inférieure a la valeur alpha beta du pere (ie coup de l'ordi, le max des fils)
		//on ne choisira pas cette branche donc on ne calcule pas le reste de l'arbre
		if ((ordi_joueur1 && (alp_bet_val > bound_a_b)) || (!ordi_joueur1 && (alp_bet_val < bound_a_b))) {
			return alp_bet_val;
		}
		// on joue le coup i
		// ecrire la fn coupValide(pos_courante,ordi_joue,i)
		// elle teste si on peut prendre les pions dans la
		// case i et les jouer (si pas de pion alors elle retourne invalide). La position de dÈpart
		// est pos_courante
		if (coupValide(courante, i + 1, ordi_joueur1)) {
			// ecrire la fn :
			//jouerCoup(&prochaine_position, courante, i, ordi_joueur1);
			// on joue le coup i a partir de la position
			// pos_courante et on met le rÈsultat
			// dans pos_next
			jouerCoup(&prochaine_position, courante, i + 1, ordi_joueur1);
			// pos_next devient la position courante, et on change le joueur
			tab_valeurs[i] = valeurMinMax(&prochaine_position, profondeur + 1, profondeur_max, !ordi_joueur1, alp_bet_val);
			//la valeur d'alpha beta devient le min/max de la valeur calculée et de la valeur alpha beta courante
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
	//on renvoie la valeur de l'alpha beta qui est le min/max calculé dynamiquement
	return alp_bet_val;
}

int prochain_coup(Position* courante, int profondeur) {
	Position prochaine_position;
	int valeursMinMax[NB_CASES];
	int case_a_jouer = 1;
	//on commence a calculer l'arbre a partir de la case jouable la plus a "petite"
	while (!coupValide(courante, case_a_jouer, true) && case_a_jouer <= NB_CASES) {
		case_a_jouer++;
	}
	//si aucune case n'est jouable -> on renvoie -1 (une erreur)
	if (case_a_jouer > NB_CASES) {
		return -1;
	}
	//on initialise le resultat en calculant la valeur minmax du sous arbre a partir du coup de base
	jouerCoup(&prochaine_position, courante, case_a_jouer, true);
	valeursMinMax[case_a_jouer - 1] = valeurMinMax(&prochaine_position, 1, profondeur, false, 100);
	for (int i = case_a_jouer; i < NB_CASES; i++) {
		if (coupValide(courante, i + 1, true)) {
			//on calcule donc tous les sous arbres correspondants a chaque coups qui sont jouables
			jouerCoup(&prochaine_position, courante, i + 1, true);
			valeursMinMax[i] = valeurMinMax(&prochaine_position, 1, profondeur, false, 100);
			//On est dans le cas ou l'on calcule le coup a jouer par l'ordi donc on prend le max des valeurs minmax des fils
			if (valeursMinMax[i] > valeursMinMax[case_a_jouer - 1]) {
				//on modifie la valeur de resultat le cas echeant
				case_a_jouer = i + 1;
			}
		}
	}
	return case_a_jouer;
}

void initGame(Position *courant) {
	for (int i = 0; i < (NB_CASES * 2); i++) {
		courant->cases_jeux[i].case_joueur = 4;
	}
	courant->pris_joueur.main_joueur = 0;
	courant->pris_ordi.main_joueur = 0;
}

int main(int argc, const char * argv[]) {
	Position position;
	Position positionSuivante;
	bool ordi_joue = true;
	initGame(&position);
	int coup = 0;
	afficherJeux(&position);
	while (1) {
		if (ordi_joue) {
			coup = prochain_coup(&position, 3);
			std::cout << coup << std::endl;
		}
		else {
			std::cout << "Coup joueur (de 1 a " << NB_CASES << ") : ";
			std::cin >> coup;
		}
		jouerCoup(&positionSuivante, &position, coup, ordi_joue);
		position = positionSuivante;
		afficherJeux(&position);
		ordi_joue = ordi_joue ? false : true;
		//afficherJeux(&positionSuivante);
	}
	return 0;
}
