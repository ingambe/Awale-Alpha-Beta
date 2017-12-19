//
//  FonctionsUtilitaires.cpp
//  Awale
//
//  Created by Pierre TASSEL on 17/12/2017.
//  Copyright © 2017 Pierre TASSEL. All rights reserved.
//

#include "FonctionsUtilitaires.hpp"

// FONCTION DEBUG QUI AFFICHE LE JEUX
void afficherJeux(Position *courante) {
	bool ordi_commence = courante->ordi_joueur1;
	std::cout << std::endl;
	for (int i = 0; i < (3 * NB_CASES); i++) {
		std::cout << "-";
	}
	std::cout << std::endl;
	for (int i = 0; i < NB_CASES; i++) {
		std::cout << "| " << courante->cases_jeux[i].case_joueur << " | ";
	}
	if (ordi_commence) {
		std::cout << "      score : " << courante->pris_ordi.main_joueur << std::endl;
	}
	else {
		std::cout << "      score : " << courante->pris_joueur.main_joueur << std::endl;
	}
	std::cout << std::endl;
	for (int i = (2 * NB_CASES) - 1; i >= NB_CASES; i--) {
		std::cout << "| " << courante->cases_jeux[i].case_joueur << " | ";
	}
	if (ordi_commence) {
		std::cout << "      score : " << courante->pris_joueur.main_joueur << std::endl;
	}
	else {
		std::cout << "      score : " << courante->pris_ordi.main_joueur << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < (3 * NB_CASES); i++) {
		std::cout << "-";
	}
	std::cout << std::endl;
}

bool positionFinale(Position *courante) {
	bool ordi_joueur1 = courante->ordi_joueur1;
	//on regarde s'il reste des puits non vide au joueur courant
	int somme = 0;
	if (courante->pris_ordi.main_joueur >= (8 * NB_CASES) || courante->pris_joueur.main_joueur >= (8 * NB_CASES)) {
		return true;
	}
	else {
		if (courante->ordi_joue && ordi_joueur1) {
			for (int i = 0; i < NB_CASES; i++) {
				somme += courante->cases_jeux[i].case_joueur;
			}
		}
		else if (courante->ordi_joue && !ordi_joueur1) {
			for (int i = NB_CASES; i < 2 * NB_CASES; i++) {
				somme += courante->cases_jeux[i].case_joueur;
			}
		}
		else if (!courante->ordi_joue && ordi_joueur1) {
			for (int i = NB_CASES; i < 2 * NB_CASES; i++) {
				somme += courante->cases_jeux[i].case_joueur;
			}
		}
		else {
			for (int i = 0; i < NB_CASES; i++) {
				somme += courante->cases_jeux[i].case_joueur;
			}
		}
	}
	return somme == 0;
}

bool coupValide(Position *courante, int i) {
	bool ordi_joueur1 = courante->ordi_joueur1;
	if ((i - 1) < 0 || (i - 1) >= NB_CASES) {
		return false;
	}
	if (ordi_joueur1 && courante->ordi_joue) {
		return courante->cases_jeux[i - 1].case_joueur > 0;
	}
	else if (ordi_joueur1 && !courante->ordi_joue) {
		return courante->cases_jeux[i + NB_CASES - 1].case_joueur > 0;
	}
	else if (!ordi_joueur1 && courante->ordi_joue) {
		return courante->cases_jeux[i + NB_CASES - 1].case_joueur > 0;
	}
	else {
		return courante->cases_jeux[i - 1].case_joueur > 0;
	}
}

/**
*  Determine si on est le joueur 1
**/
bool estLeJoueur1(Position *courante) {
	bool ordi_commence = courante->ordi_joueur1;
	return (ordi_commence && courante->ordi_joue) || (!ordi_commence && !courante->ordi_joue);
}

/**
*  Joue le coup en fonction du joeur
**/
void jouerCoup(Position* suivant, Position* courante, int case_a_jouer) {
	bool joueur1 = courante->ordi_joueur1;
	int i = case_a_jouer - 1;
	// On copie d'abord la memoire pour copier la situation courante dans la suivante
	memcpy(suivant, courante, sizeof(Position));
	// on prend dans la main les cailloux
	int main;
	// si c'est le tour du joueur 2
	if ((courante->ordi_joue && !joueur1) || (!courante->ordi_joue && joueur1)) {
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
		else {
			suivant->cases_jeux[case_courante].case_joueur++;
			case_courante++;
			main--;
		}
	}
	case_courante = (case_courante - 1) % (NB_CASES * 2);
	//si c'est au joueur 1 de jouer on ne regarde que les puits du joueur2 
	if ((courante->ordi_joue && joueur1) || (!courante->ordi_joue && !joueur1)) {
		while (case_courante >= NB_CASES && (suivant->cases_jeux[case_courante].case_joueur == 2 || suivant->cases_jeux[case_courante].case_joueur == 3)) {
			//On ajoute les cailloux au score du joueur
			if (courante->ordi_joue) {
				suivant->pris_ordi.main_joueur += suivant->cases_jeux[case_courante].case_joueur;
			}
			else {
				suivant->pris_joueur.main_joueur += suivant->cases_jeux[case_courante].case_joueur;
			}
			suivant->cases_jeux[case_courante].case_joueur = 0;
			case_courante--;
		}
	}
	else {
		while (case_courante >= 0 && case_courante < NB_CASES && (suivant->cases_jeux[case_courante].case_joueur == 2 || suivant->cases_jeux[case_courante].case_joueur == 3)) {
			if (courante->ordi_joue) {
				suivant->pris_ordi.main_joueur += suivant->cases_jeux[case_courante].case_joueur;
			}
			else {
				suivant->pris_joueur.main_joueur += suivant->cases_jeux[case_courante].case_joueur;
			}
			suivant->cases_jeux[case_courante].case_joueur = 0;
			case_courante--;
		}
	}
    suivant->ordi_joue = !courante->ordi_joue;
    // on check si l'adversaire a encore des cailloux
    int nbCaillouxTerrain = 0;
    // si on est le joueur 2
    if ((courante->ordi_joue && !joueur1) || (!courante->ordi_joue && joueur1)) {
        for(int i = 0; i < NB_CASES; i++){
            if(courante->cases_jeux[i].case_joueur > 0){
                return;
            } else {
                nbCaillouxTerrain += courante->cases_jeux[i].case_joueur;
            }
        }
        if(courante->ordi_joue){
            courante->pris_ordi.main_joueur += nbCaillouxTerrain;
        } else {
            courante->pris_joueur.main_joueur += nbCaillouxTerrain;
        }
    } else {
        for(int i = NB_CASES; i < (2 * NB_CASES); i++){
            if(courante->cases_jeux[i].case_joueur > 0){
                return;
            } else {
                nbCaillouxTerrain += courante->cases_jeux[i].case_joueur;
            }
        }
        if(courante->ordi_joue){
            courante->pris_ordi.main_joueur += nbCaillouxTerrain;
        } else {
            courante->pris_joueur.main_joueur += nbCaillouxTerrain;
        }
    }
}

int valeurMinMax(Position *courante, int profondeur, int profondeur_max, int bound_a_b) {
	Position prochaine_position;
	int alp_bet_val = courante->ordi_joue ? -1000000 : 1000000;
	int tab_valeurs[NB_CASES];
	bool ordi_joueur1 = courante->ordi_joueur1;
	if (positionFinale(courante)) {
		if (courante->pris_ordi.main_joueur > courante->pris_joueur.main_joueur) {
			return (40000 * (profondeur_max - profondeur));
		}
		else {
			if (courante->pris_ordi.main_joueur < courante->pris_joueur.main_joueur) {
				return -(40000 * (profondeur_max - profondeur));
			}
			return 0;
		}
	}
	if (profondeur == profondeur_max) {
		return evaluation(courante);
	}
	for (int i = 0; i < NB_CASES; i++) {
		//si on calcule le coup de l'ordinateur (ie on prend le max) mais que la valeur d'alpha beta du pere
		//(ie le coup jou» par l'adversaire, donc le min des fils) est inf»rieure a la valeur courante
		//d'alpha beta, alors l'adversaire ne devrait pas choisir ce fils donc on ne calcul pas le reste de l'arbre
		//inversement si la valeur d'alpha beta est inf»rieure a la valeur alpha beta du pere (ie coup de l'ordi, le max des fils)
		//on ne choisira pas cette branche donc on ne calcule pas le reste de l'arbre
		if ((courante->ordi_joue && (alp_bet_val > bound_a_b)) || (!courante->ordi_joue && (alp_bet_val < bound_a_b))) {
			return alp_bet_val;
		}
		if (coupValide(courante, i + 1)) {
			jouerCoup(&prochaine_position, courante, i + 1);
			// pos_next devient la position courante
			tab_valeurs[i] = valeurMinMax(&prochaine_position, profondeur + 1, profondeur_max, alp_bet_val);
			//la valeur d'alpha beta devient le min/max de la valeur calcul»e et de la valeur alpha beta courante
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
	//on renvoie la valeur de l'alpha beta qui est le min/max calcul» dynamiquement
	return alp_bet_val;
}

void initGame(Position *courant, bool ordi_commence) {
	for (int i = 0; i < (NB_CASES * 2); i++) {
		courant->cases_jeux[i].case_joueur = 4;
	}
	courant->pris_joueur.main_joueur = 0;
	courant->pris_ordi.main_joueur = 0;
	courant->ordi_joue = ordi_commence;
	courant->ordi_joueur1 = ordi_commence;
}

/**
*  1 si joueur 1, 2 si joueur 2, 0 si null
**/
int evaluerGagnant(Position *position) {
	// si ordi j1 et il gagne
	if (position->ordi_joueur1 && position->pris_ordi.main_joueur > position->pris_joueur.main_joueur) {
		return 1;
	}
	else if (!position->ordi_joueur1 && position->pris_ordi.main_joueur > position->pris_joueur.main_joueur) {
		// si ordi j2 et il gagne
		return  2;
	}
	else if (position->ordi_joueur1 && position->pris_ordi.main_joueur < position->pris_joueur.main_joueur) {
		// si ordi j1 et il perd
		return 2;
	}
	else if (!position->ordi_joueur1 && position->pris_ordi.main_joueur < position->pris_joueur.main_joueur) {
		// si ordi j2 et il perd
		return 1;
	}
	// sinon il y a match null
	return 0;
}
