/* ------------------------------------------------------------------- */
/*           Developped by Theo GACHET and Kawtar EL MAMOUN            */
/* ------------------------------------------------------------------- */

#ifndef HACHAGE_H
#define HACHAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOM_FICHIER "mots_courants.txt"
#define LG_MOT      28
#define BASE        128

typedef struct element {
  int             occ;
  char            mot[LG_MOT];
  struct element  *suivant;
} Element;

typedef struct hashtable {
  unsigned int    taille;
  unsigned int    nbElements;
  unsigned int    nbOccupiedEntries;
  Element         **keys;
} HashTable;

void creation_dictionnaire(HashTable ht, char* nom_fichier);
void init_hashtable(HashTable *ht, int taille_table);
void lecture_fichier(HashTable *ht, char* nom_fichier);
void inserer_absent(HashTable *ht, char *mot, unsigned long int cle);
void inserer_present(HashTable *ht, char *mot, unsigned long int cle);
void inserer_mot(HashTable *ht, char *mot);
void supprimer_mot(HashTable* ht, char* mot);
void afficher_alveole(HashTable* ht, unsigned long int cle);
void afficher_table(HashTable* ht);
void param_table_hachage(HashTable* ht);
void recherche_taille(HashTable *ht, char* nom_fichier, int taille_table);

int mot_dans_table(HashTable *ht, char *mot);
int calcul_cle(char *string, int taille_table);
int puissance(int i);
int premier(int n);

#endif