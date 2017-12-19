//
//  FonctionsUtilitaires.hpp
//  Awale
//
//  Created by Pierre TASSEL on 17/12/2017.
//  Copyright � 2017 Pierre TASSEL. All rights reserved.
//

#ifndef FonctionsUtilitaires_hpp
#define FonctionsUtilitaires_hpp

#include <stdio.h>
#include "StructureDonnee.hpp"
#include "Evaluation.hpp"
#include "Define.hpp"

bool positionFinale(Position *courante);
bool coupValide(Position *courante, int i);
void jouerCoup(Position* suivant, Position* courante, int case_a_jouer);
bool estLeJoueur1(Position *courante);
int valeurMinMax(Position *courante, int profondeur, int profondeur_max, int bound_a_b);
void initGame(Position *courant, bool ordi_commence);
int evaluerGagnant(Position *position);
void afficherJeux(Position *courante);

#endif /* FonctionsUtilitaires_hpp */
