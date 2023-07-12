
--- CONTENU DU DOSSIER ---

REPORT EL-MAMOUN-GACHET.pdf : notre rapport, nous conseillons fortement sa lecture pour saisir le fonctionnement du programme

main_avec_interface.c : code principal, interactions basée sur le terminal et sur une interface graphique interactive
main_sans_interface.c : code principal, interactions basée uniquement sur le terminal (en cas de problème de module graphique ou simplement par choix) 
hachage.c / hachage.h : module contenant les structures et fonctions utiles pour la table de hachage
liste.c / liste.h     : module contenant les fonctions utiles pour manipuler les listes chaînées
user.c / user.h       : module contenant les fonctions utiles pour assurer les demandes de l'utilisateur
Makefile              : fichier permettant le découpage modulaire et assurant la structure du code lors de la compilation
mines.png             : image utile pour l'interface
README                : présent document
mots_courants.txt     : dictionnaire de prédiction initial fourni sur CAMPUS
dictionnaire.txt      : dictionnaire de la langue française

--- INSTRUCTIONS D'EXÉCUTION ---

Pour exécuter le code avec une interface sur le terminal, utilisez les commandes suivantes :
    make all_without_interface
    ./all_without_interface

Pour exécuter le code avec une interface gtk, il faut d'abord installer la librairie gtk : 
    sudo apt-get update
    sudo apt-get install libgtk-3-dev
    
Une fois la librairie installée, vous pouvez afficher l'interface interactive avec les commandes suivantes;
    make all_w_interface
    ./all_w_interface


--- CHOIX DE LA TAILLE DE LA TABLE DE HACHAGE ---

Facteur de compression : fc = k / n ( = 0.75 est la valeur optimale )
k = nombre d'alvéoles occupées
n = nombre total d'alvéoles ( = taille de la table )
Les tailles des tables de hachage sont des nombres premiers pour éviter les diviseurs communs et réduire les collisions
