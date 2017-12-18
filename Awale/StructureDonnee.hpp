//
//  StructureDonnee.hpp
//  Awale
//
//  Created by Pierre TASSEL on 17/12/2017.
//  Copyright © 2017 Pierre TASSEL. All rights reserved.
//

#ifndef StructureDonnee_hpp
#define StructureDonnee_hpp
#define LOG_MAX_CAILLOUX 8
#define LOG_MAX_CAILLOUX_MAIN 6
#define NB_CASES 10

#include <stdio.h>


/**
*  il y a 80 cailloux sur le plateau, inutile d'utiliser plus de 8 bits pour
*  representer le nombre de cailloux par case
**/
struct Cases_joueur {
	unsigned case_joueur : LOG_MAX_CAILLOUX;
};

/**
*  on arrete la partie quand un des deux joueurs a plus de 25 cailloux, soit 6 bits
**/
struct Main_joueur {
	unsigned main_joueur : LOG_MAX_CAILLOUX_MAIN;
};

struct Position {
	Cases_joueur cases_jeux[2 * NB_CASES];
	Main_joueur pris_joueur;
	Main_joueur pris_ordi;
	bool ordi_joue;
	bool ordi_joueur1;
};


#endif /* StructureDonnee_hpp */
