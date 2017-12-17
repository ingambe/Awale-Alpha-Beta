//
//  FonctionsUtilitaires.hpp
//  Awale
//
//  Created by Pierre TASSEL on 17/12/2017.
//  Copyright © 2017 Pierre TASSEL. All rights reserved.
//

#ifndef FonctionsUtilitaires_hpp
#define FonctionsUtilitaires_hpp

#define LOG_MAX_CAILLOUX 8
#define LOG_MAX_CAILLOUX_MAIN 6
#define NB_CASES 10
#include <stdio.h>
#include "StructureDonnee.hpp"
#include "Evaluation.hpp"

bool positionFinale(Position *courante, bool ordi_joueur1);
bool coupValide(Position *courante, int i, bool ordi_joueur1);
void jouerCoup(Position* suivant, Position* courante, int case_a_jouer, bool ordi_joueur1);
int valeurMinMax(Position *courante, int profondeur, int profondeur_max, bool ordi_joueur1, int bound_a_b);
void initGame(Position *courant, bool ordi_commence);
int evaluerGagnant(Position *position, bool ordi_j1);

#endif /* FonctionsUtilitaires_hpp */
