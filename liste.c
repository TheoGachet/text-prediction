/* ------------------------------------------------------------------- */
/*           Developped by Theo GACHET and Kawtar EL MAMOUN            */
/* ------------------------------------------------------------------- */

#include "liste.h"

void afficher_liste(Element* tete)
{
    Element* actuel = tete;
    while (actuel)
    {
        printf("%s (%d) —> ", actuel->mot, actuel->occ);
        actuel = actuel->suivant;
    }
    printf("NULL\n");
}

// renvoie la longueur de la liste. En O(n).
int longueur_liste(Element *tete)
{
    int longueur = 0;
    while (tete != NULL)
    {
        longueur++;
        tete = tete->suivant;
    }
    return longueur;
}
 
// insérer un nouveau nœud au début de la liste chaînée
void inserer_noeud(Element** tete, char* mot, int occ)
{
    Element* nouveau = (Element*) malloc(sizeof(Element));
    nouveau->occ = occ;
    strcpy(nouveau->mot, mot);
    nouveau->suivant = *tete;
    *tete = nouveau;
}

// Renvoie le miroir d'une liste chainee. En O(n).
Element* miroir_liste(Element* tete)
{
    Element* actuel = tete;
    Element* liste = NULL;

    while (actuel != NULL)
    {
        inserer_noeud(&liste, actuel->mot, actuel->occ);
        actuel = actuel->suivant;
    }
    return liste;
}

// Prend deux listes triées par ordre croissant et fusionne leurs nœuds pour former une plus grande liste triée (et retournée).
Element* fusion_listes(Element* a, Element* b)
{
    if (a == NULL) return b; // cas de base
 
    else if (b == NULL) return a;
 
    Element* longueurult = NULL;

    if (a->occ <= b->occ)
    {
        longueurult = a;
        longueurult->suivant = fusion_listes(a->suivant, b);
    }
    else {
        longueurult = b;
        longueurult->suivant = fusion_listes(a, b->suivant);
    }
 
    return longueurult;
}
 
// Divise une liste chaînée en deux parties à peu près égales et met les nœuds de chaque partie dans des pointeurs de pointeurs différents.
void diviser_liste(Element* source, Element** frontRef, Element** backRef)
{
    // si la longueur est inférieure à 2, on la traite séparément
    if (source == NULL || source->suivant == NULL)
    {
        *frontRef = source;
        *backRef = NULL;
        return;
    }
 
    Element* slow = source;
    Element* fast = source->suivant;
 
    // avance `fast` de deux nœuds et avance `slow` d'un nœud
    while (fast != NULL)
    {
        fast = fast->suivant;
        if (fast != NULL)
        {
            slow = slow->suivant;
            fast = fast->suivant;
        }
    }
 
    // `slow` est avant le milieu de la liste, donc on le divise en deux à ce moment.
    *frontRef = source;
    *backRef = slow->suivant;
    slow->suivant = NULL;
}

// Trier une liste chaînée donnée à l'aide de l'algorithme de tri par fusion
void tri_fusion_liste(Element** tete)
{
    // cas de base — longueur 0 ou 1
    if (*tete == NULL || (*tete)->suivant == NULL) {
        return;
    }
 
    Element* a;
    Element* b;
 
    // divise `tete` en sous-listes `a` et `b`
    diviser_liste(*tete, &a, &b);
 
    // trie récursivementment les sous-listes
    tri_fusion_liste(&a);
    tri_fusion_liste(&b);
 
    // réponse = fusionner les deux listes triées
    *tete = fusion_listes(a, b);
}