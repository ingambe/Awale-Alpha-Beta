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

int* casesAccesibleAdversaire(Position* courante, bool ordi_joueur1);
int nbTrouAdversairePeutUtiliser(Position* courante, bool ordi_joueur1, int nombre_cailloux_trou);
int evaluation(Position* courante, bool ordi_joueur1);

#endif /* Evaluation_hpp */
