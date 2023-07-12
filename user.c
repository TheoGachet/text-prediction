/* ------------------------------------------------------------------- */
/*           Developped by Theo GACHET and Kawtar EL MAMOUN            */
/* ------------------------------------------------------------------- */

#include "user.h"
#include "liste.h"

// on saisit un mot et on affiche les prédictions et leur occurences
void prediction(HashTable *ht, HashTable *dico)
{
  // on commence par saisir le début du mot
  char saisie[LG_MOT];
  printf("\nSaisir le début d'un mot : ");
  scanf("%s", saisie);

  // on créé une liste chaînée qui relie les mots de la table de hachage qui commencent par "debut"
  Element* liste = NULL;

  for(int i=0;i<ht->taille;i++) // on parcourt la liste keys[i]
  {
    Element *element = ht->keys[i];
    while (element != NULL)
    {
      if(debut_mot(saisie, element->mot)) inserer_noeud(&liste, element->mot, element->occ);
      element = element->suivant;
    }
  }

  int longueur = longueur_liste(liste);

  if (longueur == 0)
  {
    printf("\nLa table de hachage initiale ne comporte aucun mot commençant par %s.", saisie);
    pred_dico(dico, saisie, 3);
    return ;
  }

  tri_fusion_liste(&liste);
  liste = miroir_liste(liste);
  //afficher_liste(liste);
  
  if (longueur == 1)  // on traite les cas séparément pour éviter une segmentation fault
  {
    printf("\nSuggestion via le dictionnaire de prédiction :  : \"%s\" (%d)", liste->mot, liste->occ);
    pred_dico(dico, saisie, 2);
  }
  
  else if (longueur == 2)
  {
    printf("\nSuggestion via le dictionnaire de prédiction :  : \"%s\" (%d) - \"%s\" (%d)", liste->mot, liste->occ, liste->suivant->mot, liste->suivant->occ);
    pred_dico(dico, saisie, 2);
  }
  
  else
  {
    printf("\nSuggestion via le dictionnaire de prédiction :  : \"%s\" (%d) - \"%s\" (%d) - \"%s\" (%d)", liste->mot, liste->occ, liste->suivant->mot, liste->suivant->occ, liste->suivant->suivant->mot, liste->suivant->suivant->occ);
  }
}

// affiche nb suggestions commençant par "saisie" provenant du dictionnaire français
void pred_dico(HashTable *ht, char* saisie, int nb)
{
  Element* liste = NULL;
  int compteur = 0;   // la variable compteur va faire qu'on ajoute seulement 3 mots dans la liste chaînée des mots qui commencent comme "saisie" étant donné que tous les mots du dictionnaire n'ont qu'une seule occurence (les mots proposés seront donc triés par ordre alphabétique)
  for(int i=0;i<ht->taille;i++)
  {
    Element *element = ht->keys[i];
    while (element != NULL && compteur < 3)
    {
      if(debut_mot(saisie, element->mot))
      {
        inserer_noeud(&liste, element->mot, element->occ);
        compteur ++;
      }
      element = element->suivant;
      
    }
  }

  int longueur = longueur_liste(liste);

  if (longueur == 0) printf("\nLe dictionnaire français ne comporte aucun mot commençant par %s", saisie);
  else
  {
    tri_fusion_liste(&liste);
    liste = miroir_liste(liste);
    //afficher_liste(liste);
    if (nb == 1)  // on traite les cas séparément en fonction du nombre de suggestions nécessaire
    {
      printf("\nComplément de suggestion via le dictionnaire français : \"%s\"\n", liste->mot);
    }
    else if (nb == 2)
    {
      if (longueur == 1) printf("\nComplément de suggestion via le dictionnaire français : \"%s\"\n", liste->mot);
      else printf("\nComplément de suggestion via le dictionnaire français : \"%s\" - \"%s\"\n", liste->mot, liste->suivant->mot);
    }
    else if (nb == 3)
    {
      if (longueur == 1) printf("\nComplément de suggestion via le dictionnaire français : \"%s\"\n", liste->mot);
      else if (longueur == 2) printf("\nComplément de suggestion via le dictionnaire français : \"%s\" - \"%s\"\n", liste->mot, liste->suivant->mot);
      else printf("\nComplément de suggestion via le dictionnaire français : \"%s\" - \"%s\" - \"%s\"\n", liste->mot, liste->suivant->mot, liste->suivant->suivant->mot);
    }
  }
}

// insérer = ajouter si non existant ou incrémenter l'occ si existant
void inserer_mot_saisie(HashTable *ht, HashTable *dico)
{
  char saisie[LG_MOT];
  printf("\nSaisir le mot à insérer dans le dictionnaire de prédiction : ");
  scanf("%s", saisie);
  if(mot_dans_table(dico, saisie))
  {
    inserer_mot(ht,saisie);
    printf("Le mot \"%s\" a bien été inséré dans le dictionnaire de prédiction.\n", saisie);
  }
  else
  {
    printf("Le mot \"%s\" n'est pas correctement orthographié, veuillez réessayer\n", saisie);
    inserer_mot_saisie(ht, dico);
  }
}

// insérer = ajouter si non existant ou incrémenter l'occ si existant
void inserer_acronyme_nom(HashTable *ht)
{
  char saisie[LG_MOT];
  printf("\nSaisir le mot à insérer dans le dictionnaire de prédiction : ");
  scanf("%s", saisie);
  inserer_mot(ht,saisie);
  printf("Le mot \"%s\" a bien été inséré dans le dictionnaire de prédiction.\n", saisie);
}

// supprimer = supprimer le mot et toutes ses occurences
void supprimer_mot_saisie(HashTable *ht)
{
  char saisie[LG_MOT];
  printf("\nSaisir le mot à supprimer de la table de hachage : ");
  scanf("%s", saisie);
  if(mot_dans_table(ht, saisie)) supprimer_mot(ht, saisie);
  else
  {
    printf("Le mot \"%s\" n'est pas correctement orthographié, veuillez réessayer\n", saisie);
    supprimer_mot_saisie(ht);
  }
}

void occurences(HashTable *ht)
{
  char saisie[LG_MOT];
  printf("\nSaisir le mot dont vous souhaitez connaître le nombre d'apparition(s) : ");
  scanf("%s", saisie);

  unsigned long int cle = calcul_cle(saisie, ht->taille);
  Element *element = ht->keys[cle];
  while (element != NULL)
  {
    if((strcmp(saisie, element->mot)==0))
    {
      printf("Le mot %s est présent %d fois dans la liste de hachage.\n", saisie, element->occ);
      printf("Il a donc une fréquence d'apparition qui vaut : %d/%d\n", element->occ,ht->nbElements);
      return ;
    }
    element = element->suivant;
  }
  printf("Le mot \"%s\" n'est pas présent dans la table de hachage\n", saisie);
}

void modifier_occurences(HashTable *ht)
{
  char saisie[LG_MOT];
  int occ_saisie;
  printf("\nSaisir le mot dont vous voulez modifier le nombre d'occurences : ");
  scanf("%s", saisie);
  printf("Saisir le nombre d'occurences à assigner au mot \"%s\" : ", saisie);
  scanf("%d", &occ_saisie);

  unsigned long int cle = calcul_cle(saisie, ht->taille);
  Element *element = ht->keys[cle];
  while (element != NULL)
  {
    if((strcmp(saisie, element->mot)==0))
    {
      element->occ = occ_saisie;
      printf("Le mot \"%s\" a désormais une occurence de %d\n", saisie, occ_saisie);
      return ;
    }
    element = element->suivant;
  }
  printf("Le mot \"%s\" n'est pas présent dans la table de hachage\n", saisie);
}

void modifier_orthographe(HashTable *ht)
{
  char saisie[LG_MOT];
  char nouveau[LG_MOT];
  int occ_saisie;
  printf("\nSaisir le mot dont vous voulez modifier l'orthographe : ");
  scanf("%s", saisie);
  printf("\nSaisir la nouvelle orthographe du mot : ");
  scanf("%s", nouveau);

  unsigned long int cle = calcul_cle(saisie, ht->taille);
  Element *element = ht->keys[cle];
  int occurences = 0;

  while (element != NULL)
  {
    if((strcmp(saisie, element->mot)==0))
    {
      occurences = element->occ;
      supprimer_mot(ht, saisie);
      inserer_mot(ht, nouveau);

      unsigned long int cle_bis = calcul_cle(nouveau, ht->taille);
      Element *element_bis = ht->keys[cle_bis];

      while (element_bis != NULL)
      {
        if((strcmp(nouveau, element_bis->mot)==0))
        {
          element_bis->occ = occurences;
          return ;
        }
        element_bis = element_bis->suivant;
      }
      return ;
    }
    element = element->suivant;
  }
  printf("Le mot \"%s\" n'est pas présent dans la table de hachage\n", saisie);
}


void saisie_phrase(HashTable *ht, HashTable *dico)
{
  char saisie[LG_MOT*100];
  printf("\n\nSaisie : ");
  scanf("%s", saisie);

  char mot[LG_MOT][LG_MOT]={""};
  int i=0,j=0,k=0;
  while (saisie[k]!='\0')
  {
    j=0;
    while((saisie[k]!=' ')&&(saisie[k]!='\0'))
    {
      mot[i][j]+=saisie[k];
      k++;                    // lettres de la phrase
      j++;                    // lettres du mot
    }
    k++;
    i++;                      // nombre de mots
  }
  for (k=0;k<i;k++)
  {
    if(mot_dans_table(dico, mot[k])) inserer_mot(ht, mot[k]);
  }
  printf("\e[1;1H\e[2J");
  printf("\nTous les mots correctement orthographiés ont été insérés.\n");
}

// renvoie 1 si "mot" commence par "debut", et 0 sinon
int debut_mot(char* debut, char* mot)
{
  int lg_debut = strlen(debut);
  int lg_mot = strlen(mot);

  if (lg_debut > lg_mot) return 0;

  for (int i=0;i<lg_debut;i++) if (debut[i] != mot[i]) return 0;

  return 1;
}