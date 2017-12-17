//
//  Evaluation.hpp
//  Awale
//
//  Created by Pierre TASSEL on 17/12/2017.
//  Copyright © 2017 Pierre TASSEL. All rights reserved.
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

int* casesAccesibleAdversaire(Position* courante, bool ordi_joueur1);
int nbTrouAdversairePeutUtiliser(Position* courante, bool ordi_joueur1, int nombre_cailloux_trou);
int evaluation(Position* courante, bool ordi_joueur1);
int basicEvaluation(Position* courante);
int valeurMinMaxModifie(Position *courante, int profondeur, int profondeur_max, bool ordi_joueur1, int bound_a_b, int a1, int a2, int a3, int a4, int a5, int a6);
void determinerCoeff();
#endif /* Evaluation_hpp */
