/* ------------------------------------------------------------------- */
/*           Developped by Theo GACHET and Kawtar EL MAMOUN            */
/* ------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hachage.h"
#include "user.h"
#include "liste.h"

void main(void)
{
  // cette ligne efface le contenu de la console pour plus de visibilité
  printf("\e[1;1H\e[2J");

  // on commence par charger les bases de données
  HashTable ht;
  HashTable dico;
  recherche_taille(&ht, "mots_courants.txt", 653); // taille obtenue expérimentalement via la fonction
  recherche_taille(&dico, "dictionnaire.txt", 52963); // taille obtenue expérimentalement via la fonction

  int quitter = 0;
  int prediction_statut = 0;
  
  while (!quitter)
  {
    // // Efface la console
    printf("\n --------------------------------------------------------------------------------\n");
    printf(" | Bienvenue ! Ce programme a été développé par Théo GACHET et Kawtar EL MAMOUN |\n");
    printf(" --------------------------------------------------------------------------------\n");
    printf(" |  0  : Quitter l'application                                                  |\n");
    printf(" |  1  : Activer/Désactiver la prédiction de saisie (statut actuel : ");
    if(prediction_statut==1) printf("ON)        |\n"); else printf("OFF)       |\n");
    printf(" |  2  : Prédire 3 suggestions pour un mot non-complet                          |\n");  // ajouter les mots de la phrase dans le dictionnaire ? prédiction ? -> 4 cas
    printf(" |  3  : Saisir une phrase dans le dictionnaire                                 |\n");
    printf(" |  4  : Ajouter un mot dans le dictionnaire de prédiction                      |\n");
    printf(" |  5  : Supprimer un mot du dictionnaire de prédiction                         |\n");
    printf(" |  6  : Ajouter un nom ou acronyme dans le dictionnaire                        |\n");  // = mot "mal orthographié"
    printf(" |  7  : Afficher le nombre d'occurrences d'un mot                              |\n");
    printf(" |  8  : Modifier le nombre d'occurrences d'un mot                              |\n");
    printf(" |  9  : Modifier l'orthographe d'un mot                                        |\n"); // = supprime le mot et insert la nouvelle orthographe en conservant le nombre d'occurences
    printf(" |  10 : Afficher les caractéristiques du dictionnaire de prédiction            |\n");
    printf(" |  11 : Afficher les caractéristiques du dictionnaire français                 |\n");
    printf(" |  12 : Afficher le dictionnaire de prédiction                                 |\n");
    printf(" |  13 : Afficher le dictionnaire français                                      |\n");
    printf(" |  14 : Afficher une alvéole à partir d'une clé                                |\n");
    printf(" |  15 : Afficher une alvéole à partir d'un mot                                 |\n");
    printf(" --------------------------------------------------------------------------------\n");
    
    int choix;
    printf("\nChoix ? ");
    scanf("%d", &choix);

    switch (choix)
    {
      case 0 :
        printf("\nAu revoir !\n");
        quitter = 1;
        break;
      case 1 :
        printf("\e[1;1H\e[2J");
        prediction_statut = (prediction_statut==0);
        break;
      case 2 :
        printf("\e[1;1H\e[2J");
        prediction(&ht, &dico);
        break;
      case 3 :
        printf("\e[1;1H\e[2J");
        saisie_phrase(&ht, &dico);
        break;
      case 4 :
        printf("\e[1;1H\e[2J");
        inserer_mot_saisie(&ht, &dico);
        break;
      case 5 :
        printf("\e[1;1H\e[2J");
        supprimer_mot_saisie(&ht);
        break;
      case 6 :
        printf("\e[1;1H\e[2J");
        inserer_acronyme_nom(&ht);
        break;
      case 7 :
        printf("\e[1;1H\e[2J");
        occurences(&ht);
        break;
      case 8 :
        printf("\e[1;1H\e[2J");
        modifier_occurences(&ht);
        break;
      case 9 :
        printf("\e[1;1H\e[2J");
        modifier_orthographe(&ht);
        printf("\nL'orthographe du mot est à jour et son occurence est conservée.\n");
        break;
      case 10 :
        printf("\e[1;1H\e[2J");
        param_table_hachage(&ht);
        break;
      case 11 :
        printf("\e[1;1H\e[2J");
        param_table_hachage(&dico);
        break;
      case 12 :
        printf("\e[1;1H\e[2J");
        afficher_table(&ht);
        break;
      case 13 :
        printf("\e[1;1H\e[2J");
        afficher_table(&dico);
        break;
      case 14 :
        printf("\e[1;1H\e[2J");
        int cle;
        printf("\nSaisir une clé pour afficher son alvéole : ");
        scanf("%d", &cle);
        afficher_alveole(&ht, cle);
        printf("\n");
        break;
      case 15 :
        printf("\e[1;1H\e[2J");
        char saisie[LG_MOT];
        printf("\nSaisir un mot pour afficher son alvéole : ");
        scanf("%s", saisie);
        afficher_alveole(&ht, calcul_cle(saisie, ht.taille));
        printf("\n");
        break;
      default :
        printf("\e[1;1H\e[2J");
        printf("\nChoix incorrect\n");
        break;
    }
  }
}