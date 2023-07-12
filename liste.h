/* ------------------------------------------------------------------- */
/*           Developped by Theo GACHET and Kawtar EL MAMOUN            */
/* ------------------------------------------------------------------- */

#ifndef LISTE_H
#define LISTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hachage.h"

Element* fusion_listes(Element* a, Element* b);
Element* miroir_liste(Element* tete);

void afficher_liste(Element* tete);
void inserer_noeud(Element** tete, char* mot, int occ);
void diviser_liste(Element* source, Element** frontRef, Element** backRef);
void tri_fusion_liste(Element** tete);

int longueur_liste(Element *tete);

#endif