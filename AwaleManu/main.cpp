//
//  main.cpp
//  Awale
//
//  Created by Pierre TASSEL on 14/12/2017.
//  Copyright © 2017 Pierre TASSEL. All rights reserved.
//
#define LOG_MAX_CAILLOUX 8
#define LOG_MAX_CAILLOUX_MAIN 6
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
	Cases_joueur cases_jeux[10];
	Main_joueur pris_joueur;
	Main_joueur pris_ordi;
	bool ordi_joue;
};


bool positionFinale(Position *courante, bool ordi_joueur1) {
	if (courante->pris_ordi.main_joueur >= 25 || courante->pris_joueur.main_joueur >= 25) {
		return true;
	}
	else {
		int somme = 0;
		if (courante->ordi_joue && ordi_joueur1) {
			for (int i = 0; i < 5; i++) {
				somme += courante->cases_jeux[i].case_joueur;
			}
		}
		else if (courante->ordi_joue && !ordi_joueur1) {
			for (int i = 5; i < 10; i++) {
				somme += courante->cases_jeux[i].case_joueur;
			}
		}
		else if (!courante->ordi_joue && ordi_joueur1) {
			for (int i = 5; i < 10; i++) {
				somme += courante->cases_jeux[i].case_joueur;
			}
		}
		else {
			for (int i = 0; i < 5; i++) {
				somme += courante->cases_jeux[i].case_joueur;
			}
		}
		return somme == 0;
	}
	return false;
}

int evaluation(Position* courante, bool ordi_joueur1) {
	int resultat = 0;
	if (courante->ordi_joue && ordi_joueur1) {
		for (int i = 0; i < 5; i++) {
			resultat += courante->cases_jeux[i].case_joueur;
		}
	}
	else if (courante->ordi_joue && !ordi_joueur1) {
		for (int i = 5; i < 10; i++) {
			resultat += courante->cases_jeux[i].case_joueur;
		}
	}
	else if (!courante->ordi_joue && ordi_joueur1) {
		for (int i = 5; i < 10; i++) {
			resultat += courante->cases_jeux[i].case_joueur;
		}
	}
	else {
		for (int i = 0; i < 5; i++) {
			resultat += courante->cases_jeux[i].case_joueur;
		}
	}
	return resultat;
}

// FONCTION DEBUG QUI AFFICHE LE JEUX
void afficherJeux(Position *courante) {
	std::cout << std::endl;
	for (int i = 0; i < 20; i++) {
		std::cout << "-";
	}
	std::cout << std::endl;
	for (int i = 9; i > 4; i--) {
		std::cout << "| " << courante->cases_jeux[i].case_joueur << " | ";
	}
	std::cout << std::endl;
	for (int i = 0; i < 5; i++) {
		std::cout << "| " << courante->cases_jeux[i].case_joueur << " | ";
	}
	std::cout << std::endl;
	for (int i = 0; i < 20; i++) {
		std::cout << "-";
	}
	std::cout << std::endl;
}

bool coupValide(Position *courante, int i, bool ordi_joueur1) {
	if (i < 0 || i > 4) {
		return false;
	}
	if (courante->ordi_joue && ordi_joueur1) {
		return courante->cases_jeux[i].case_joueur > 0;
	}
	else if (courante->ordi_joue && !ordi_joueur1) {
		return courante->cases_jeux[i + 5].case_joueur > 0;
	}
	else if (!courante->ordi_joue && ordi_joueur1) {
		return courante->cases_jeux[i + 5].case_joueur > 0;
	}
	else if (!courante->ordi_joue && !ordi_joueur1) {
		return courante->cases_jeux[i].case_joueur > 0;
	}
	return false;
}

void jouerCoup(Position* suivant, Position* courante, int i, bool ordi_joueur1) {
	// On copie d'abord la memoire pour copier la situation courante dans la suivante
	std::cout << "cp 1 :" << std::endl;
	afficherJeux(courante);
	memcpy(suivant, courante, sizeof(Position));
	std::cout << "cp 2 :" << std::endl;
	afficherJeux(suivant);
	// on prend dans la main les cailloux
	int main;
	// pour savoir si on est le joueur en haut ou en bas
	bool j_en_haut;
	if (courante->ordi_joue && ordi_joueur1) {
		main = courante->cases_jeux[i].case_joueur;
		suivant->cases_jeux[i].case_joueur = 0;
		j_en_haut = false;
	}
	else if (courante->ordi_joue && !ordi_joueur1) {
		i = 9 - i;
		main = courante->cases_jeux[i].case_joueur;
		suivant->cases_jeux[i].case_joueur = 0;
		j_en_haut = true;
	}
	else if (!courante->ordi_joue && ordi_joueur1) {
		i = 9 - i;
		main = courante->cases_jeux[i + 5].case_joueur;
		suivant->cases_jeux[i].case_joueur = 0;
		j_en_haut = true;
	}
	else {
		main = courante->cases_jeux[i].case_joueur;
		suivant->cases_jeux[i].case_joueur = 0;
		j_en_haut = false;
	}
	while (main > 0) {
		if (j_en_haut) {
			i--;
			if (i == 0) {
				i = 9;
			}
		}
		else {
			i++;
			if (i == 10) {
				i = 0;
			}
		}
		suivant->cases_jeux[i].case_joueur++;
		main--;
	}

}

int valeurMinMax(Position *courante, int profondeur, int profondeur_max, bool ordi_joueur1, int bound_a_b) {
	Position prochaine_position;
	int alp_bet_val = ordi_joueur1 ? -100 : 100;
	int tab_valeurs[10];
	if (positionFinale(courante, ordi_joueur1)) {
		// retourner 40 si ordi gagne, -40 si il perd et 0 si null
	}
	if (profondeur == profondeur_max) {
		return evaluation(courante, ordi_joueur1);
	}
	for (int i = 0; i < 10; i++) {
		//si on calcule le coup de l'ordinateur (ie on prend le max) mais que la valeur d'alpha beta du pere
		//(ie le coup joué par l'adversaire, donc le min des fils) est inférieure a la valeur courante
		//d'alpha beta, alors l'adversaire ne devrait pas choisir ce fils donc on ne calcul pas le reste de l'arbre
		if (ordi_joueur1 && (alp_bet_val > bound_a_b)) {
			return alp_bet_val;
		}
		else {
			//inversement si la valeur d'alpha beta est inférieure a la valeur alpha beta du pere (ie coup de l'ordi, le max des fils)
			//on ne choisira pas cette branche donc on ne calcule pas le reste de l'arbre
			if (alp_bet_val < bound_a_b) return alp_bet_val;
		}
		// on joue le coup i
		// ecrire la fn coupValide(pos_courante,ordi_joue,i)
		// elle teste si on peut prendre les pions dans la
		// case i et les jouer (si pas de pion alors elle retourne invalide). La position de dÈpart
		// est pos_courante
		if (coupValide(courante, i, ordi_joueur1)) {
			// ecrire la fn :
			//jouerCoup(&prochaine_position, courante, i, ordi_joueur1);
			// on joue le coup i a partir de la position
			// pos_courante et on met le rÈsultat
			// dans pos_next
			jouerCoup(&prochaine_position, courante, i, ordi_joueur1);
			// pos_next devient la position courante, et on change le joueur
			tab_valeurs[i] = valeurMinMax(&prochaine_position, profondeur + 1, profondeur_max, !ordi_joueur1, alp_bet_val);
			//la valeur d'alpha beta devient le min/max de la valeur calculée et de la valeur alpha beta courante
			//(min/max selon le joueur ordi ou adversaire)
			alp_bet_val = ordi_joueur1 ? ((alp_bet_val > tab_valeurs[i]) ? alp_bet_val : tab_valeurs[i]) : ((alp_bet_val < tab_valeurs[i]) ? alp_bet_val : tab_valeurs[i]);
		}
		else {
			if (courante->ordi_joue) {
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

void initGame(Position *courant, bool ordi_j1) {
	for (int i = 0; i < 10; i++) {
		courant->cases_jeux[i].case_joueur = 4;
	}
	courant->pris_joueur.main_joueur = 0;
	courant->pris_ordi.main_joueur = 0;
	courant->ordi_joue = ordi_j1;
}

int main(int argc, const char * argv[]) {
	Position position;
	initGame(&position, true);
	int i = 0;
	while (!positionFinale(&position, true)) {
		Position positionSuivante;
		int coup = 0;
		std::cout << "Coup joueur" << (i + 1) << "(de 1 a 5)" << " : ";
		std::cin >> coup;
		jouerCoup(&positionSuivante, &position, coup - 1, i == 0);
		position = positionSuivante;
		afficherJeux(&positionSuivante);
		i = (i + 1) % 2;
	}
	return 0;
}
