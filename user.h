/* ------------------------------------------------------------------- */
/*           Developped by Theo GACHET and Kawtar EL MAMOUN            */
/* ------------------------------------------------------------------- */

#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hachage.h"

void prediction(HashTable *ht, HashTable *dico);
void pred_dico(HashTable *ht, char* saisie, int nb);
void inserer_mot_saisie(HashTable *ht, HashTable *dico);
void inserer_acronyme_nom(HashTable *ht);
void supprimer_mot_saisie(HashTable *ht);
void modifier_occurences(HashTable *ht);
void modifier_orthographe(HashTable *ht);
void occurences(HashTable *ht);
void saisie_phrase(HashTable *ht, HashTable *dico);

int debut_mot(char* debut, char* mot);

#endif