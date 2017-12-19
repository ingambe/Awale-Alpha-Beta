//
//  TestGenerationCoefficient.hpp
//  Awale
//
//  Created by Pierre TASSEL on 19/12/2017.
//  Copyright © 2017 Pierre TASSEL. All rights reserved.
//

#ifndef TestGenerationCoefficient_hpp
#define TestGenerationCoefficient_hpp

#include <stdio.h>
#include "StructureDonnee.hpp"
#include "FonctionsUtilitaires.hpp"

int basicEvaluationMod(Position* courante);
int valeurMinMaxMod(Position *courante, int profondeur, int profondeur_max, int bound_a_b, bool coef, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
void determinerCoeff();
int prochain_coup_2(Position* courante, int profondeur);
int prochain_coup_1(Position* courante, int profondeur, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);

#endif /* TestGenerationCoefficient_hpp */
