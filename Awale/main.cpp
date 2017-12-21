//
//  main.cpp
//  Awale
//
//  Created by Pierre TASSEL on 14/12/2017.
//  Copyright � 2017 Pierre TASSEL. All rights reserved.
//
#include <iostream>
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include "StructureDonnee.hpp"
#include "Evaluation.hpp"
#include "FonctionsUtilitaires.hpp"
#include "TestGenerationCoefficient.hpp"
#include "Define.hpp"

int prochain_coup(Position* courante, int profondeur) {
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
	valeursMinMax[case_a_jouer - 1] = valeurMinMax(&prochaine_position, 1, profondeur, -1000000);
	for (int i = case_a_jouer; i < NB_CASES; i++) {
		if (coupValide(courante, i + 1)) {
			//on calcule donc tous les sous arbres correspondants a chaque coups qui sont jouables
			jouerCoup(&prochaine_position, courante, i + 1);
			valeursMinMax[i] = valeurMinMax(&prochaine_position, 1, profondeur, valeursMinMax[case_a_jouer - 1]);
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
	if (argc > 1) {
        // si on appel depuis la ligne de commande avec un argument en plus alors
        // on lance l'appel a la fonction qui cherche les meuilleurs coefficients de la
        // fonction d'evaluation
		determinerCoeff();
	}
	else {
        // sinon on lance une partie normale
		Position position;
		Position positionSuivante;
		int choix_debut;
		std::cout << "L'ordinateur commence ? (0 pour Oui, 1 pour Non) : ";
		std::cin >> choix_debut;
		bool ordi_commence = (choix_debut == 0);
		initGame(&position, ordi_commence);
		int coup = 0;
		while (!positionFinale(&position)) {
			if (position.ordi_joue) {
				coup = prochain_coup(&position, 8);
				std::cout << "L'ordinateur a joue : " << coup << std::endl;
			}
			else {
				std::cout << "Coup joueur (de 1 a " << NB_CASES << ") : ";
				std::cin >> coup;
			}
			while(!coupValide(&position, coup)) {
                std::cout << "Le coup " << coup << " est non valide, avez vous fait une erreur ?" << std::endl;
                std::cout << "Coup joueur (de 1 a " << NB_CASES << ") : ";
                std::cin >> coup;
			}
			jouerCoup(&positionSuivante, &position, coup);
			position = positionSuivante;
			afficherJeux(&position);
		}
		int gagnant = evaluerGagnant(&position);
		std::cout << "Le jeu est termine le gagnant est le joueur :" << gagnant << (((position.ordi_joueur1 && gagnant == 1) || (!position.ordi_joueur1 && gagnant == 2)) ? "(l'IA)" : "(l'adversaire)") << std::endl;
		std::cin >> gagnant;
	}
	return 0;
}
