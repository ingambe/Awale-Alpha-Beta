//
//  main.cpp
//  Awale
//
//  Created by Pierre TASSEL on 14/12/2017.
//  Copyright © 2017 Pierre TASSEL. All rights reserved.
//
#define LOG_MAX_CAILLOUX 8
#define LOG_MAX_CAILLOUX_MAIN 6
#include <iostream>
#include <bitset>
#include <stdio.h>
#include <stdlib.h>

/**
 *  il y a 80 cailloux sur le plateau, inutile d'utiliser plus de 8 bits pour
 *  representer le nombre de cailloux par case
 **/
struct Cases_joueur {
    unsigned case_joueur:LOG_MAX_CAILLOUX;
};

/**
 *  on arrete la partie quand un des deux joueurs a plus de 25 cailloux, soit 6 bits
 **/
struct Main_joueur {
    unsigned main_joueur:LOG_MAX_CAILLOUX_MAIN;
};

struct Position {
    Cases_joueur cases_joueur[5];
    Cases_joueur cases_ordi[5];
    Main_joueur pris_joueur;
    Main_joueur pris_ordi;
    bool ordi_joue;
};


bool positionFinale(Position *courante){
    if(courante->pris_ordi.main_joueur >= 25 || courante->pris_joueur.main_joueur >= 25){
        return true;
    } else {
        int somme = 0;
        if(courante->ordi_joue){
            for(int i = 0; i < 5; i++){
                somme += courante->cases_ordi[i].case_joueur;
            }
        } else {
            for(int i = 0; i < 5; i++){
                somme += courante->cases_joueur[i].case_joueur;
            }
        }
        return somme == 0;
    }
    return false;
}

int evaluation(Position* courante){
    int resultat = 0;
    if(courante->ordi_joue){
        for(int i = 0; i < 5; i++){
            resultat += courante->cases_ordi[i].case_joueur;
        }
    } else {
        for(int i = 0; i < 5; i++){
            resultat += courante->cases_joueur[i].case_joueur;
        }
    }
    return resultat;
}

bool coupValide(Position *courante, int i, bool ordi_joueur1){
    if(courante->ordi_joue && ordi_joueur1){
        return i >= 0 && i <= 4 && (courante->cases_ordi[i].case_joueur > 0);
    } else if (courante->ordi_joue && !ordi_joueur1){
        return i >= 5 && i <= 9 && (courante->cases_ordi[i].case_joueur > 0);
    } else if (!courante->ordi_joue && ordi_joueur1){
        return i >= 5 && i <= 9 && (courante->cases_joueur[i].case_joueur > 0);
    } else if(!courante->ordi_joue && !ordi_joueur1){
        return i >= 0 && i <= 4 && (courante->cases_joueur[i].case_joueur > 0);
    }
    return false;
}

void jouerCoup(Position* suivant, Position* courante, int i, bool ordi_joueur1){
    // On copie d'abord la memoire
    memcpy(suivant, courante, sizeof(Position));
    // d'abord on deplace les cailloux
    if(courante->ordi_joue){
        suivant->cases_ordi[i].case_joueur = 0;
        for(int j = courante->cases_ordi[i].case_joueur;  j >= 1; j--){
            
        }
    } else {
        
    }
}

int valeurMinMax(Position *courante, int profondeur, int profondeur_max, bool ordi_joueur1){
    Position prochaine_position;
    int tab_valeurs[6];
    if(positionFinale(courante)){
        // retourner 40 si ordi gagne, -40 si il perd et 0 si null
    }
    if(profondeur == profondeur_max){
        return evaluation(courante);
    }
    for(int i = 0; i < 5; i++){
        // on joue le coup i
        // ecrire la fn coupValide(pos_courante,ordi_joue,i)
        // elle teste si on peut prendre les pions dans la
        // case i et les jouer (si pas de pion alors elle retourne invalide). La position de dÈpart
        // est pos_courante
        if (coupValide(courante, i, ordi_joueur1)){
            // ecrire la fn :
            //jouerCoup(&prochaine_position, courante, i, ordi_joueur1);
            // on joue le coup i a partir de la position
            // pos_courante et on met le rÈsultat
            // dans pos_next
            jouerCoup(&prochaine_position, courante, i, ordi_joueur1);
            // pos_next devient la position courante, et on change le joueur
            tab_valeurs[i]=valeurMinMax(&prochaine_position, profondeur + 1, profondeur_max, ordi_joueur1);
        } else {
            if (courante->ordi_joue){
                tab_valeurs[i] = -100;
            } else {
                tab_valeurs[i] = 100;
            }
        }
    }
    unsigned int indice = 0;
    if (courante->ordi_joue){
        // ecrire le code: res contient le MAX de
        // tab_valeurs
        for(int i = 1; i < 5; i++){
            if(tab_valeurs[i] > tab_valeurs[indice]){
                indice = i;
            }
        }
    } else {
        // ecrire le code : res contient le MIN de
        // tab_valeurs
        for(int i = 1; i < 5; i++){
            if(tab_valeurs[i] < tab_valeurs[indice]){
                indice = i;
            }
        }
    }
    return indice;
}

int main(int argc, const char * argv[]) {
    Position *position = (Position *) calloc(1, sizeof(Position));
    return 0;
}
