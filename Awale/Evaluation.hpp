//
//  Evaluation.hpp
//  Awale
//
//  Created by Pierre TASSEL on 17/12/2017.
//  Copyright � 2017 Pierre TASSEL. All rights reserved.
//

#ifndef Evaluation_hpp
#define Evaluation_hpp

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <stdio.h>
#include "StructureDonnee.hpp"
#include "FonctionsUtilitaires.hpp"
#include "Define.hpp"

int* casesAccesiblesJoueur(Position* courante, bool joueur1);
int nbTrouAdversairePeutUtiliser(Position* courante, int nombre_cailloux_trou);
int evaluation(Position* courante);
int basicEvaluation(Position* courante);
#endif /* Evaluation_hpp */
