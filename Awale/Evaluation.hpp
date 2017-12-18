//
//  Evaluation.hpp
//  Awale
//
//  Created by Pierre TASSEL on 17/12/2017.
//  Copyright � 2017 Pierre TASSEL. All rights reserved.
//

#ifndef Evaluation_hpp
#define Evaluation_hpp
#define NB_CASES 10

#include <stdio.h>
#include "StructureDonnee.hpp"
#include "FonctionsUtilitaires.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>

int* casesAccesiblesJoueur(Position* courante, bool joueur1);
int nbTrouAdversairePeutUtiliser(Position* courante, int nombre_cailloux_trou);
int evaluation(Position* courante);
//int basicEvaluation(Position* courante);
int basicEvaluationMod(Position* courante);
int valeurMinMaxMod(Position *courante, int profondeur, int profondeur_max, int bound_a_b, bool coef, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
void determinerCoeff();
int prochain_coup_2(Position* courante, int profondeur);
int prochain_coup_1(Position* courante, int profondeur, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
int basicEvaluationMod(Position* courante);
#endif /* Evaluation_hpp */
