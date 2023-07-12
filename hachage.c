/* ------------------------------------------------------------------- */
/*           Developped by Theo GACHET and Kawtar EL MAMOUN            */
/* ------------------------------------------------------------------- */

#include "hachage.h"

// Fonction d’optimisation qui cherche la taille optimale d’une table de hachage afin de répondre aux exigences concernant le facteur de charge.
void recherche_taille(HashTable *ht, char* nom_fichier, int taille_table)
{
  init_hashtable(ht, taille_table);
  lecture_fichier(ht, nom_fichier);
  float loadFactor = 1.0 * ht->nbOccupiedEntries / ht->taille;
  //printf("\n%lf",loadFactor);
  while(loadFactor<0.75 || !premier(taille_table))
  {
    taille_table = taille_table*0.99;
    recherche_taille(ht, nom_fichier, taille_table);
    break;
  }
}

// Alloue la mémoire et initialise la table de hachage comme un tableau de taille prédéfinie que l’on remplit de listes chaînées vides (NULL).
void init_hashtable(HashTable *ht, int taille_table)
{
  ht->taille = taille_table;
  ht->nbElements = 0;
  ht->nbOccupiedEntries = 0 ;
  ht->keys = (Element**)malloc(ht->taille*sizeof(Element));

  for(int i = 0; i<ht->taille;i++)
    ht->keys[i] = NULL; // on initialise les listes chaînées
}

// Lit le fichier en argument et insert chaque mot dans la table de hachage.
void lecture_fichier(HashTable *ht, char* nom_fichier)
{
  FILE *fichier;
  char mot[LG_MOT];

  fichier = fopen(nom_fichier, "r");
  
  if(!fichier)
  {
    printf("Erreur lors de l'ouverture du fichier");
    return;
  }

  while(fscanf(fichier, "%s", mot)==1)
  {
    inserer_mot(ht,mot);
    //printf("Insertion du mot \"%s\" de clé %d.\n",mot,calcul_cle(mot));
  }
  fclose(fichier);
}

// Calcule la clé d’un mot.
int calcul_cle(char *string, int taille_table) // *string est un pointeur de string
{
  unsigned long long int cle = 0 ;
  int i = 0 ;

  while ((*string) != '\0')   // \0 est le caractère de fin de chaîne
  {
    cle += cle % taille_table + ((*string) * (int) puissance(i)) % taille_table;
    i++;
    string++;
  }
  return cle % taille_table ;
}

// Renvoie la base de calcul (ici 128) à la puissance i (pour la fonction de hachage).
int puissance(int i)
{
  int k = 1;
  for(int j=0;j<i;j++)
  {
    k = BASE*k;
  }
  return k;
}

// Renvoie 1 si n est premier, 0 sinon.
int premier(int n)
{
	int i;
	for(i=2;i<=n/2;i++)
	{
		if(n%i!=0)
			continue;
		else
			return 0;
	}
	return 1;
}

// Renvoie 1 si un mot est dans la table, 0 sinon.
int mot_dans_table(HashTable *ht, char *mot)
{
  unsigned long int cle = calcul_cle(mot, ht->taille);
  int trouve = 0;

  Element* element = ht->keys[cle];

  while(!trouve && element) // (element!=NULL) = (element)
  {
    trouve = (strcmp(mot, element->mot)==0); // strcmp renvoie 0 si les deux mots sont les mêmes
    element = element->suivant;
  }
  return trouve;
}

// Insert un mot dans la table de hachage.
void inserer_mot(HashTable *ht, char *mot)
{
  if(mot_dans_table(ht, mot)) inserer_present(ht, mot, calcul_cle(mot,ht->taille));
  else inserer_absent(ht, mot, calcul_cle(mot,ht->taille));
}

// Insert la première apparition d’un mot dans la table de hachage.
void inserer_absent(HashTable *ht, char *mot, unsigned long int cle)
{
  ht->nbElements++;

  Element* element = (Element*) malloc(sizeof(Element));
  strcpy(element->mot, mot);

  // si la table chaînée à l'indice cle est vide
  if (ht->keys[cle] == NULL) ht->nbOccupiedEntries++ ;

  // élément inséré en tête de liste, à l'indice i
  element->suivant = ht->keys[cle];
  ht->keys[cle] = element ;
  element->occ = 1;
}

// Augmente l’occurrence d’un mot dans la table de hachage.
void inserer_present(HashTable *ht, char *mot, unsigned long int cle)
{
  ht->nbElements++;

  Element *actuel = ht->keys[cle];

  while (actuel != NULL)
  {
    if(strcmp(mot, actuel->mot)==0)
    {
      actuel->occ++;
      return;
    }
    actuel = actuel->suivant;
  }
}

// Supprime un mot de la table de hachage.
void supprimer_mot(HashTable* ht, char* mot)
{
  ht->nbElements++;
  unsigned long int cle = calcul_cle(mot, ht->taille);

  int trouve = 1;

  // chercher le mot dans la liste tout en memorisant son precedent
  Element *prec = NULL;
  Element *actuel = ht->keys[cle];

  while (actuel != NULL && (strcmp(mot, actuel->mot)!=0))
  { 
    prec = actuel;
    actuel = actuel->suivant;
  }

  if (actuel == NULL) trouve = 0;

  else
  {
    // retirer le mot de la liste chaînée
    if (prec == NULL) // le mot est le premier élément de la liste : son suivant devient la tete
      ht->keys[cle] = actuel->suivant;  // fonctionne aussi si c'est le seul élément de la liste
    else              // sinon on chaîne son precedent à son suivant
      prec->suivant = actuel->suivant;

    free(actuel);
  }

  if(trouve) printf("Le mot \"%s\" a bien été supprimé de la table de hachage.\n", mot);
  else printf("Le mot \"%s\" n'est pas présent dans la table de hachage.\n", mot);
  // on décrémente nbOccupiedEntries si l'alvéole est désormais vide
  if (ht->keys[cle] == NULL) ht->nbOccupiedEntries-- ;
}

// Affiche une alvéole de la table de hachage selon la clé fournie en argument.
void afficher_alveole(HashTable* ht, unsigned long int cle)
{
  Element *element = ht->keys[cle];
  printf("[%d] -> ",cle);
  while (element != NULL)
    {
        printf("%s (%d) -> ", element->mot, element->occ);
        element = element->suivant;
    }
  printf("NULL\n");
}

// Affiche la table de hachage.
void afficher_table(HashTable* ht)
{
  printf("\n\nAffichage de la table de hachage :\n\n");
  for(int i=0;i<ht->taille;i++)
  {
    afficher_alveole(ht, i);
  }
  printf("\n");
}

// Affiche les caractéristiques d’une table de hachage.
void param_table_hachage(HashTable* ht)
{
	/* A loadFactor = 0.75 offers a good tradeoff between time and space cost. */
	float loadFactor = 1.0 * ht->nbOccupiedEntries / ht->taille;

	printf("\n------- Caractéristiques de la table de hachage -------\n");
	printf("Load Factor       : %.2f \n", loadFactor);
	printf("Mots              : %u \n", ht->nbElements);
  printf("Alvéoles          : %u \n", ht->taille);
	printf("Alvéoles occupées : %u \n", ht->nbOccupiedEntries);
	printf("--------------------------------------------------------\n\n");
}
