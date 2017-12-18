//
//  main.cpp
//  Awale
//
//  Created by Pierre TASSEL on 14/12/2017.
//  Copyright � 2017 Pierre TASSEL. All rights reserved.
//
#define LOG_MAX_CAILLOUX 8
#define LOG_MAX_CAILLOUX_MAIN 6
#define NB_CASES 10
#include <iostream>
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include "StructureDonnee.hpp"
#include "Evaluation.hpp"
#include "FonctionsUtilitaires.hpp"

int prochain_coup(Position* courante, int profondeur, bool ordi_joueur1) {
	Position prochaine_position;
	int valeursMinMax[NB_CASES];
	int case_a_jouer = 1;
	//on commence a calculer l'arbre a partir de la case jouable la plus a "petite"
	while (!coupValide(courante, case_a_jouer, ordi_joueur1) && case_a_jouer <= NB_CASES) {
		case_a_jouer++;
	}
	//si aucune case n'est jouable -> on renvoie -1 (une erreur)
	if (case_a_jouer > NB_CASES) {
		return -1;
	}
	//on initialise le resultat en calculant la valeur minmax du sous arbre a partir du coup de base
	jouerCoup(&prochaine_position, courante, case_a_jouer, ordi_joueur1);
	valeursMinMax[case_a_jouer - 1] = valeurMinMax(&prochaine_position, 1, profondeur, ordi_joueur1, 100);
	for (int i = case_a_jouer; i < NB_CASES; i++) {
		if (coupValide(courante, i + 1, ordi_joueur1)) {
			//on calcule donc tous les sous arbres correspondants a chaque coups qui sont jouables
			jouerCoup(&prochaine_position, courante, i + 1, ordi_joueur1);
			valeursMinMax[i] = valeurMinMax(&prochaine_position, 1, profondeur, ordi_joueur1, 100);
			//On est dans le cas ou l'on calcule le coup a jouer par l'ordi donc on prend le max des valeurs minmax des fils
			if (valeursMinMax[i] > valeursMinMax[case_a_jouer - 1]) {
				//on modifie la valeur de resultat le cas echeant
				case_a_jouer = i + 1;
			}
		}
	}
	return case_a_jouer;
}

int main(int argc, const char * argv[]) {
	if (!true) {
		determinerCoeff();
	}
	else {
		Position position;
		Position positionSuivante;
		int choix_debut;
		std::cout << "L'ordinateur commence ? (0 pour Oui, 1 pour Non) : ";
		std::cin >> choix_debut;
		bool ordi_commence = (choix_debut == 0);
		initGame(&position, ordi_commence);
		int coup = 0;
		while (!positionFinale(&position, ordi_commence)) {
			if (position.ordi_joue) {
				coup = prochain_coup(&position, 5, ordi_commence);
				std::cout << "L'ordinateur a joue : " << coup << std::endl;
			}
			else {
				std::cout << "Coup joueur (de 1 a " << NB_CASES << ") : ";
				std::cin >> coup;
			}
			if (!coupValide(&position, coup, ordi_commence)) {
				std::cout << "le coup : " << coup << " est non valide il a ete jouee par " << (position.ordi_joue ? "l'ordinateur" : "l'adversaire") << std::endl;
				return 0;
			}
			jouerCoup(&positionSuivante, &position, coup, ordi_commence);
			position = positionSuivante;
			afficherJeux(&position, ordi_commence);
		}
	}
	return 0;
}
