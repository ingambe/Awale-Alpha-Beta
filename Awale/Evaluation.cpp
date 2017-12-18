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
int* casesAccesiblesJoueur(Position* courante, bool joueur1) {
	int* cases_accessibles = new int[NB_CASES];
	if (joueur1) {
		for (int i = 0; i < NB_CASES; i++) {
			cases_accessibles[i] = courante->cases_jeux[i + courante->cases_jeux[i].case_joueur].case_joueur % (2 * NB_CASES);
		}
	}
	else {
		for (int i = NB_CASES; i < 2 * NB_CASES; i++) {
			cases_accessibles[i - NB_CASES] = courante->cases_jeux[i + courante->cases_jeux[i].case_joueur].case_joueur % (2 * NB_CASES);
		}
	}
	return cases_accessibles;
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
*  On regarde si �a cree des occasions pour l'adversaire en lui permettant
*  D'acceder a des trous ou il pourra manger des cailloux par exemple
**/
int evaluation(Position* courante, bool ordi_joueur1) {
	bool ordi_joueur1 = courante->ordi_joueur1;
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
	if (ordi_joueur1 && courante->ordi_joue) {
		// cas ou l'ordi est le joueur 1 et nous somme le joueur 1
		evalutation += a1 * nbTrouPeutUtiliser(courante, accessible_j2, 2);
		evalutation += a2 * nbTrouPeutUtiliser(courante, accessible_j2, 3);
		evalutation += a3 * nbTrouPeutUtiliser(courante, accessible_j1, 2);
		evalutation += a4 * nbTrouPeutUtiliser(courante, accessible_j1, 3);
		for (int i = 0; i < NB_CASES; i++) {
			// si le j2 peut acceder a notre cote on augmente le compteur
			if (*(accessible_j2 + i) < NB_CASES) {
				nombrePuits++;
			}
		}
		evalutation += a5 * nombrePuits;
		nombrePuits = 0;
		for (int i = 0; i < NB_CASES; i++) {
			// si on peut acceder au cote de l'adversaire on incremente le compteur
			if (*(accessible_j1 + i) > NB_CASES) {
				nombrePuits++;
			}
		}
		evalutation += a6 * nombrePuits;

	}
	else if (!ordi_joueur1 && courante->ordi_joue) {
		// cas ou l'ordi est le joueur 2 et nous somme le joueur 2
		evalutation += a1 * nbTrouPeutUtiliser(courante, accessible_j1, 2);
		evalutation += a2 * nbTrouPeutUtiliser(courante, accessible_j1, 3);
		evalutation += a3 * nbTrouPeutUtiliser(courante, accessible_j2, 2);
		evalutation += a4 * nbTrouPeutUtiliser(courante, accessible_j2, 3);
		for (int i = 0; i < NB_CASES; i++) {
			// si le j1 peut acceder a notre cote on augmente le compteur
			if (*(accessible_j1 + i) > NB_CASES) {
				nombrePuits++;
			}
		}
		evalutation += a5 * nombrePuits;
		nombrePuits = 0;
		for (int i = 0; i < NB_CASES; i++) {
			// si on peut acceder au cote de l'adversaire on incremente le compteur
			if (*(accessible_j2 + i) < NB_CASES) {
				nombrePuits++;
			}
		}
		evalutation += a6 * nombrePuits;
	}
	else if (ordi_joueur1 && !courante->ordi_joue) {
		// cas ou l'ordi est le joueur 1 et nous somme le joueur 2
		evalutation += a1 * nbTrouPeutUtiliser(courante, accessible_j1, 2);
		evalutation += a2 * nbTrouPeutUtiliser(courante, accessible_j1, 3);
		evalutation += a3 * nbTrouPeutUtiliser(courante, accessible_j2, 2);
		evalutation += a4 * nbTrouPeutUtiliser(courante, accessible_j2, 3);
		for (int i = 0; i < NB_CASES; i++) {
			// si le j1 peut acceder a notre cote on augmente le compteur
			if (*(accessible_j1 + i) > NB_CASES) {
				nombrePuits++;
			}
		}
		evalutation += a5 * nombrePuits;
		nombrePuits = 0;
		for (int i = 0; i < NB_CASES; i++) {
			// si on peut acceder au cote de l'adversaire on incremente le compteur
			if (*(accessible_j2 + i) < NB_CASES) {
				nombrePuits++;
			}
		}
		evalutation += a6 * nombrePuits;
	}
	else {
		// cas ou l'ordi est le joueur 2 et nous somme le joueur 1
		evalutation += a1 * nbTrouPeutUtiliser(courante, accessible_j2, 2);
		evalutation += a2 * nbTrouPeutUtiliser(courante, accessible_j2, 3);
		evalutation += a3 * nbTrouPeutUtiliser(courante, accessible_j1, 2);
		evalutation += a4 * nbTrouPeutUtiliser(courante, accessible_j1, 3);
		for (int i = 0; i < NB_CASES; i++) {
			// si le j2 peut acceder a notre cote on augmente le compteur
			if (*(accessible_j2 + i) < NB_CASES) {
				nombrePuits++;
			}
		}
		evalutation += a5 * nombrePuits;
		nombrePuits = 0;
		for (int i = 0; i < NB_CASES; i++) {
			// si on peut acceder au cote de l'adversaire on incremente le compteur
			if (*(accessible_j1 + i) > NB_CASES) {
				nombrePuits++;
			}
		}
		evalutation += a6 * nombrePuits;
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

/**
*  Cette version de la fonctiond d'evaluation est utilise quand
*  on cherche les meuilleurs coefficiants pour a1, a2, ..., aN
**/
int evaluation(Position* courante, int a1, int a2, int a3, int a4, int a5, int a6) {
	bool ordi_joueur1 = courante->ordi_joueur1;
	int evalutation = 0;
	int* accessible_j1 = casesAccesiblesJoueur(courante, true);
	int* accessible_j2 = casesAccesiblesJoueur(courante, false);
	// permettra de calculer le nombre de puis permettant d'acceder au cote adverse
	int nombrePuits = 0;
	if (ordi_joueur1 && courante->ordi_joue) {
		// cas ou l'ordi est le joueur 1 et nous somme le joueur 1
		evalutation += a1 * nbTrouPeutUtiliser(courante, accessible_j2, 2);
		evalutation += a2 * nbTrouPeutUtiliser(courante, accessible_j2, 3);
		evalutation += a3 * nbTrouPeutUtiliser(courante, accessible_j1, 2);
		evalutation += a4 * nbTrouPeutUtiliser(courante, accessible_j1, 3);
		for (int i = 0; i < NB_CASES; i++) {
			// si le j2 peut acceder a notre cote on augmente le compteur
			if (*(accessible_j2 + i) < NB_CASES) {
				nombrePuits++;
			}
		}
		evalutation += a5 * nombrePuits;
		nombrePuits = 0;
		for (int i = 0; i < NB_CASES; i++) {
			// si on peut acceder au cote de l'adversaire on incremente le compteur
			if (*(accessible_j1 + i) > NB_CASES) {
				nombrePuits++;
			}
		}
		evalutation += a6 * nombrePuits;

	}
	else if (!ordi_joueur1 && courante->ordi_joue) {
		// cas ou l'ordi est le joueur 2 et nous somme le joueur 2
		evalutation += a1 * nbTrouPeutUtiliser(courante, accessible_j1, 2);
		evalutation += a2 * nbTrouPeutUtiliser(courante, accessible_j1, 3);
		evalutation += a3 * nbTrouPeutUtiliser(courante, accessible_j2, 2);
		evalutation += a4 * nbTrouPeutUtiliser(courante, accessible_j2, 3);
		for (int i = 0; i < NB_CASES; i++) {
			// si le j1 peut acceder a notre cote on augmente le compteur
			if (*(accessible_j1 + i) > NB_CASES) {
				nombrePuits++;
			}
		}
		evalutation += a5 * nombrePuits;
		nombrePuits = 0;
		for (int i = 0; i < NB_CASES; i++) {
			// si on peut acceder au cote de l'adversaire on incremente le compteur
			if (*(accessible_j2 + i) < NB_CASES) {
				nombrePuits++;
			}
		}
		evalutation += a6 * nombrePuits;
	}
	else if (ordi_joueur1 && !courante->ordi_joue) {
		// cas ou l'ordi est le joueur 1 et nous somme le joueur 2
		evalutation += a1 * nbTrouPeutUtiliser(courante, accessible_j1, 2);
		evalutation += a2 * nbTrouPeutUtiliser(courante, accessible_j1, 3);
		evalutation += a3 * nbTrouPeutUtiliser(courante, accessible_j2, 2);
		evalutation += a4 * nbTrouPeutUtiliser(courante, accessible_j2, 3);
		for (int i = 0; i < NB_CASES; i++) {
			// si le j1 peut acceder a notre cote on augmente le compteur
			if (*(accessible_j1 + i) > NB_CASES) {
				nombrePuits++;
			}
		}
		evalutation += a5 * nombrePuits;
		nombrePuits = 0;
		for (int i = 0; i < NB_CASES; i++) {
			// si on peut acceder au cote de l'adversaire on incremente le compteur
			if (*(accessible_j2 + i) < NB_CASES) {
				nombrePuits++;
			}
		}
		evalutation += a6 * nombrePuits;
	}
	else {
		// cas ou l'ordi est le joueur 2 et nous somme le joueur 1
		evalutation += a1 * nbTrouPeutUtiliser(courante, accessible_j2, 2);
		evalutation += a2 * nbTrouPeutUtiliser(courante, accessible_j2, 3);
		evalutation += a3 * nbTrouPeutUtiliser(courante, accessible_j1, 2);
		evalutation += a4 * nbTrouPeutUtiliser(courante, accessible_j1, 3);
		for (int i = 0; i < NB_CASES; i++) {
			// si le j2 peut acceder a notre cote on augmente le compteur
			if (*(accessible_j2 + i) < NB_CASES) {
				nombrePuits++;
			}
		}
		evalutation += a5 * nombrePuits;
		nombrePuits = 0;
		for (int i = 0; i < NB_CASES; i++) {
			// si on peut acceder au cote de l'adversaire on incremente le compteur
			if (*(accessible_j1 + i) > NB_CASES) {
				nombrePuits++;
			}
		}
		evalutation += a6 * nombrePuits;
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

int basicEvaluation(Position* courante) {
	return 5 * (courante->pris_ordi.main_joueur - courante->pris_joueur.main_joueur);
}

int basicEvaluationMod(Position* courante) {
    return 5 * (courante->pris_joueur.main_joueur - courante->pris_ordi.main_joueur);
}

int prochain_coup_1(Position* courante, int profondeur, int a1, int a2, int a3, int a4, int a5, int a6) {
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
	valeursMinMax[case_a_jouer - 1] = valeurMinMaxMod(&prochaine_position, 1, profondeur, 100, true, a1, a2, a3, a4, a5, a6);
	for (int i = case_a_jouer; i < NB_CASES; i++) {
		if (coupValide(courante, i + 1)) {
			//on calcule donc tous les sous arbres correspondants a chaque coups qui sont jouables
			jouerCoup(&prochaine_position, courante, i + 1);
			valeursMinMax[i] = valeurMinMaxMod(&prochaine_position, 1, profondeur, 100, true, a1, a2, a3, a4, a5, a6);
			//On est dans le cas ou l'on calcule le coup a jouer par l'ordi donc on prend le max des valeurs minmax des fils
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
	valeursMinMax[case_a_jouer - 1] = valeurMinMaxMod(&prochaine_position, 1, profondeur, 100, false, 0, 0, 0, 0, 0, 0);
	for (int i = case_a_jouer; i < NB_CASES; i++) {
		if (coupValide(courante, i + 1)) {
			//on calcule donc tous les sous arbres correspondants a chaque coups qui sont jouables
			jouerCoup(&prochaine_position, courante, i + 1);
			valeursMinMax[i] = valeurMinMaxMod(&prochaine_position, 1, profondeur, 100, false, 0, 0, 0, 0, 0, 0);
			//On est dans le cas ou l'on calcule le coup a jouer par l'ordi donc on prend le max des valeurs minmax des fils
			if (valeursMinMax[i] < valeursMinMax[case_a_jouer - 1]) {
				//on modifie la valeur de resultat le cas echeant
				case_a_jouer = i + 1;
			}
		}
	}
	return case_a_jouer;
}

int valeurMinMaxMod(Position *courante, int profondeur, int profondeur_max, int bound_a_b, bool coef, int a1, int a2, int a3, int a4, int a5, int a6) {
	Position prochaine_position;
	int alp_bet_val = courante->ordi_joue ? -100 : 100;
	int tab_valeurs[NB_CASES];
	if (positionFinale(courante)) {
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
		if (coef) {
			return evaluation(courante, a1, a2, a3, a4, a5, a6);
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
			tab_valeurs[i] = valeurMinMax(&prochaine_position, profondeur + 1, profondeur_max, alp_bet_val);
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

int jouerPartieDeuxRobot(int a1, int a2, int a3, int a4, int a5, int a6) {
	srand(time(NULL));
	Position position;
	Position positionSuivante;
	bool ordi_commence = true;
	bool j1 = true;
	initGame(&position, ordi_commence);
	int coup = 0;
	int nbCoup = 0;
	while (!positionFinale(&position) && nbCoup < 1000) {
		if (position.ordi_joue) {
			coup = prochain_coup_1(&position, 5, a1, a2, a3, a4, a5, a6);
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
	int coeff[6];
	int maximum = 0;
	int resultat = 0;
	for (int a1 = -40; a1 <= 40; a1++) {
		for (int a2 = -40; a1 <= 40; a1++) {
			for (int a3 = -40; a1 <= 40; a1++) {
				for (int a4 = -40; a1 <= 40; a1++) {
					for (int a5 = -40; a1 <= 40; a1++) {
						for (int a6 = -40; a1 <= 40; a1++) {
							resultat = 0;
							for (int i = 0; i < 50; i++) {
								resultat += jouerPartieDeuxRobot(a1, a2, a3, a4, a5, a6);
							}
							if (resultat > maximum) {
								maximum = resultat;
								coeff[0] = a1;
								coeff[1] = a2;
								coeff[2] = a3;
								coeff[3] = a4;
								coeff[4] = a5;
								coeff[5] = a6;
								std::cout << "Meuilleur coeff trouvee : " << std::endl;
								std::cout << "a1 : " << a1 << " a2 : " << a2 << " a3 : " << a3 << " a4 : " << a4 << " a5 : " << a5 << " a6 : " << a6 << std::endl;
								std::cout << "resultat : " << maximum << " / 50" << std::endl;
							}
						}
						std::cout << "le programme tourne toujours, maximum : " << maximum << std::endl;
					}
				}
			}
		}
	}
}
