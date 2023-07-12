/* ------------------------------------------------------------------- */
/*           Developped by Theo GACHET and Kawtar EL MAMOUN            */
/* ------------------------------------------------------------------- */

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hachage.h"
#include "user.h"
#include "liste.h"

void option_quitter(GtkButton *button, gpointer data);
void option_activer(GtkButton *button, gpointer data);
void option_predire(GtkButton *button, gpointer data);
void option_saisir_phrase(GtkButton *button, gpointer data);
void option_ajouter_mot(GtkButton *button, gpointer data);
void option_supprimer_mot(GtkButton *button, gpointer data);
void option_ajouter_acronyme(GtkButton *button, gpointer data);
void option_afficher_occurrences(GtkButton *button, gpointer data);
void option_modifier_occurences(GtkButton *button, gpointer data);
void option_modifier_orthographe(GtkButton *button, gpointer data);
void option_caract_dico_pred(GtkButton *button, gpointer data);
void option_caract_dico_fr(GtkButton *button, gpointer data);
void option_afficher_dico_pred(GtkButton *button, gpointer data);
void option_afficher_dico_fr(GtkButton * button, gpointer data);
void option_alveole_par_cle(GtkButton *button, gpointer data);
void option_alveole_par_mot(GtkButton *button, gpointer data);

gboolean button_clicked = FALSE;

int prediction_statut = 1;
HashTable ht, dico;

/* Affichage Ã©tat prÃ©diction de saisie*/
GtkWidget *statut;

int main(int argc, char *argv[]) {

    recherche_taille(&ht, "mots_courants.txt", 653); // taille obtenue expÃ©rimentalement via la fonction
    recherche_taille(&dico, "dictionnaire.txt", 52963); // taille obtenue expÃ©rimentalement via la fonction

    gtk_init(&argc, &argv);
    
    /* FenÃªtre principale */
    GtkWidget *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_window_set_title(GTK_WINDOW(window), "Programme de saisie intuitive dÃ©veloppÃ© par EL MAMOUN & GACHET");
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    /* Tableau */
    GtkWidget *vbox; 
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    
    /* Affichage logo */
    GtkWidget *logo;
    logo = gtk_image_new_from_file("mines.png");
    gtk_box_pack_start(GTK_BOX(vbox), logo, FALSE, FALSE, 0);

    /* Option activation saisie intuitive */
    statut = gtk_label_new("La prÃ©diction de saisie est activÃ©e");
    gtk_container_add(GTK_CONTAINER(window), statut);
    gtk_box_pack_start(GTK_BOX(vbox), statut, FALSE, FALSE, 0);

    GtkWidget* bouton = gtk_button_new_with_label("Cliquez pour activer/dÃ©sactiver la prÃ©diction");
    g_signal_connect(bouton, "clicked", G_CALLBACK(option_activer), NULL);
    gtk_container_add(GTK_CONTAINER(window), bouton);
    gtk_box_pack_start(GTK_BOX(vbox), bouton, FALSE, FALSE, 0);

    GtkWidget* bouton1 = gtk_button_new_with_label("PrÃ©dire 3 suggestions pour un mot non-complet");
    g_signal_connect(bouton1, "clicked", G_CALLBACK(option_predire), NULL);
    gtk_container_add(GTK_CONTAINER(window), bouton1);
    gtk_box_pack_start(GTK_BOX(vbox), bouton1, FALSE, FALSE, 0);

    GtkWidget* bouton2 = gtk_button_new_with_label("Saisir une phrase dans le dictionnaire");
    g_signal_connect(bouton2, "clicked", G_CALLBACK(option_saisir_phrase), NULL);
    gtk_container_add(GTK_CONTAINER(window), bouton2);
    gtk_box_pack_start(GTK_BOX(vbox), bouton2, FALSE, FALSE, 0);

    GtkWidget* bouton3 = gtk_button_new_with_label("Ajouter un mot dans le dictionnaire de prÃ©diction");
    g_signal_connect(bouton3, "clicked", G_CALLBACK(option_ajouter_mot), NULL);
    gtk_container_add(GTK_CONTAINER(window), bouton3);
    gtk_box_pack_start(GTK_BOX(vbox), bouton3, FALSE, FALSE, 0);

    GtkWidget* bouton4 = gtk_button_new_with_label("Supprimer un mot du dictionnaire de prÃ©diction");
    g_signal_connect(bouton4, "clicked", G_CALLBACK(option_supprimer_mot), NULL);
    gtk_container_add(GTK_CONTAINER(window), bouton4);
    gtk_box_pack_start(GTK_BOX(vbox), bouton4, FALSE, FALSE, 0);

    GtkWidget* bouton5 = gtk_button_new_with_label("Ajouter un nom ou acronyme dans le dictionnaire");
    g_signal_connect(bouton5, "clicked", G_CALLBACK(option_ajouter_acronyme), NULL);
    gtk_container_add(GTK_CONTAINER(window), bouton5);
    gtk_box_pack_start(GTK_BOX(vbox), bouton5, FALSE, FALSE, 0);

    GtkWidget* bouton6 = gtk_button_new_with_label("Afficher le nombre d'occurrences d'un mot");
    g_signal_connect(bouton6, "clicked", G_CALLBACK(option_afficher_occurrences), NULL);
    gtk_container_add(GTK_CONTAINER(window), bouton6);
    gtk_box_pack_start(GTK_BOX(vbox), bouton6, FALSE, FALSE, 0);

    GtkWidget* bouton7 = gtk_button_new_with_label("Modifier le nombre d'occurrences d'un mot");
    g_signal_connect(bouton7, "clicked", G_CALLBACK(option_modifier_occurences), NULL);
    gtk_container_add(GTK_CONTAINER(window), bouton7);
    gtk_box_pack_start(GTK_BOX(vbox), bouton7, FALSE, FALSE, 0);

    GtkWidget* bouton8 = gtk_button_new_with_label("Modifier l'orthographe d'un mot");
    g_signal_connect(bouton8, "clicked", G_CALLBACK(option_modifier_orthographe), NULL);
    gtk_container_add(GTK_CONTAINER(window), bouton8);
    gtk_box_pack_start(GTK_BOX(vbox), bouton8, FALSE, FALSE, 0);

    GtkWidget* bouton9 = gtk_button_new_with_label("Afficher les caractÃ©ristiques du dictionnaire de prÃ©diction");
    g_signal_connect(bouton9, "clicked", G_CALLBACK(option_caract_dico_pred), NULL);
    gtk_container_add(GTK_CONTAINER(window), bouton9);
    gtk_box_pack_start(GTK_BOX(vbox), bouton9, FALSE, FALSE, 0);

    GtkWidget* bouton10 = gtk_button_new_with_label("Afficher les caractÃ©ristiques du dictionnaire franÃ§ais");
    g_signal_connect(bouton10, "clicked", G_CALLBACK(option_caract_dico_fr), NULL);
    gtk_container_add(GTK_CONTAINER(window), bouton10);
    gtk_box_pack_start(GTK_BOX(vbox), bouton10, FALSE, FALSE, 0);

    GtkWidget* bouton11 = gtk_button_new_with_label("Afficher le dictionnaire de prÃ©diction");
    g_signal_connect(bouton11, "clicked", G_CALLBACK(option_afficher_dico_pred), NULL);
    gtk_container_add(GTK_CONTAINER(window), bouton11);
    gtk_box_pack_start(GTK_BOX(vbox), bouton11, FALSE, FALSE, 0);

    GtkWidget* bouton12 = gtk_button_new_with_label("Afficher le dictionnaire franÃ§ais");
    g_signal_connect(bouton12, "clicked", G_CALLBACK(option_afficher_dico_fr), NULL);
    gtk_container_add(GTK_CONTAINER(window), bouton12);
    gtk_box_pack_start(GTK_BOX(vbox), bouton12, FALSE, FALSE, 0);

    GtkWidget* bouton13 = gtk_button_new_with_label("Afficher une alvÃ©ole Ã  partir d'une clÃ©");
    g_signal_connect(bouton13, "clicked", G_CALLBACK(option_alveole_par_cle), NULL);
    gtk_container_add(GTK_CONTAINER(window), bouton13);
    gtk_box_pack_start(GTK_BOX(vbox), bouton13, FALSE, FALSE, 0);

    GtkWidget* bouton14 = gtk_button_new_with_label("Afficher une alvÃ©ole Ã  partir d'un mot");
    g_signal_connect(bouton14, "clicked", G_CALLBACK(option_alveole_par_mot), NULL);
    gtk_container_add(GTK_CONTAINER(window), bouton14);
    gtk_box_pack_start(GTK_BOX(vbox), bouton14, FALSE, FALSE, 0);

    GtkWidget* bouton15 = gtk_button_new_with_label("Quitter");
    g_signal_connect(bouton15, "clicked", G_CALLBACK(option_quitter), NULL);
    gtk_container_add(GTK_CONTAINER(window), bouton15);
    gtk_box_pack_start(GTK_BOX(vbox), bouton15, FALSE, FALSE, 0);

    
    gtk_widget_show_all(window);
    gtk_main();

    return EXIT_SUCCESS;
}

void option_quitter(GtkButton *button, gpointer data) {
    g_print("Vous avez quittÃ© l'application !");
    gtk_main_quit();
}
void option_activer(GtkButton *button, gpointer data) {
    prediction_statut = (prediction_statut==0);
    if (prediction_statut == 1) gtk_label_set_text(GTK_LABEL(statut), "La prÃ©diction de saisie est activÃ©e");
    else gtk_label_set_text(GTK_LABEL(statut), "La prÃ©diction de saisie est dÃ©sactivÃ©e");
}
void option_predire(GtkButton *button, gpointer data) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
    GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
        "Vous avez choisi l'option : PrÃ©dire 3 suggestions pour un mot non-complet. \n Cliquez sur OK puis rÃ©alisez la saisie sur votre terminal :)");
    gtk_window_set_modal(GTK_WINDOW(dialog), FALSE);
    gtk_dialog_run(GTK_DIALOG(dialog));
    prediction(&ht, &dico);
    gtk_widget_destroy(dialog);
}
void option_saisir_phrase(GtkButton *button, gpointer data) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
    GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
        "Vous avez choisi l'option : Saisir une phrase dans le dictionnaire. \n Cliquez sur OK puis rÃ©alisez la saisie sur votre terminal :)");
    gtk_window_set_modal(GTK_WINDOW(dialog), FALSE);
    gtk_dialog_run(GTK_DIALOG(dialog));
    saisie_phrase(&ht, &dico);
    gtk_widget_destroy(dialog);    
}

void option_ajouter_mot(GtkButton *button, gpointer data){
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
    GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
        "Vous avez choisi l'option : Ajouter un mot dans le dictionnaire de prÃ©diction. \n Cliquez sur OK puis rÃ©alisez la saisie sur votre terminal :)");
    gtk_window_set_modal(GTK_WINDOW(dialog), FALSE);
    gtk_dialog_run(GTK_DIALOG(dialog));
    inserer_mot_saisie(&ht, &dico);
    gtk_widget_destroy(dialog);  

}

void option_supprimer_mot(GtkButton *button, gpointer data) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
    GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
        "Vous avez choisi l'option : Supprimer un mot du dictionnaire de prÃ©diction. \n Cliquez sur OK puis rÃ©alisez la saisie sur votre terminal :)");
    gtk_window_set_modal(GTK_WINDOW(dialog), FALSE);
    gtk_dialog_run(GTK_DIALOG(dialog));
    supprimer_mot_saisie(&ht);
    gtk_widget_destroy(dialog);  

}

void option_ajouter_acronyme(GtkButton *button, gpointer data) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
    GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
        "Vous avez choisi l'option : Ajouter un acronyme dans le dictionnaire. \n Cliquez sur OK puis rÃ©alisez la saisie sur votre terminal :)");
    gtk_window_set_modal(GTK_WINDOW(dialog), FALSE);
    gtk_dialog_run(GTK_DIALOG(dialog));
    inserer_acronyme_nom(&ht);
    gtk_widget_destroy(dialog);  
}

void option_afficher_occurrences(GtkButton *button, gpointer data) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
    GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
        "Vous avez choisi l'option : Afficher le nombre d'occurrences d'un mot. \n Cliquez sur OK puis rÃ©alisez la saisie sur votre terminal :)");
    gtk_window_set_modal(GTK_WINDOW(dialog), FALSE);
    gtk_dialog_run(GTK_DIALOG(dialog));
    occurences(&ht);
    gtk_widget_destroy(dialog);  
}

void option_modifier_occurences(GtkButton *button, gpointer data) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
    GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
        "Vous avez choisi l'option : Modifier le nombre d'occurrences d'un mot. \n Cliquez sur OK puis rÃ©alisez la saisie sur votre terminal :)");
    gtk_window_set_modal(GTK_WINDOW(dialog), FALSE);
    gtk_dialog_run(GTK_DIALOG(dialog));
    modifier_occurences(&ht);
    gtk_widget_destroy(dialog);  
}

void option_modifier_orthographe(GtkButton *button, gpointer data) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
    GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
        "Vous avez choisi l'option : Modifier l'orthographe d'un mot. \n Cliquez sur OK puis rÃ©alisez la saisie sur votre terminal :)");
    gtk_window_set_modal(GTK_WINDOW(dialog), FALSE);
    gtk_dialog_run(GTK_DIALOG(dialog));
    modifier_orthographe(&ht);
    gtk_widget_destroy(dialog);  
}

void option_caract_dico_pred(GtkButton *button, gpointer data) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
    GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
        "Vous avez choisi l'option : Afficher les caractÃ©ristiques du dictionnaire de prÃ©diction. \n Cliquez sur OK puis rÃ©alisez la saisie sur votre terminal :)");
    gtk_window_set_modal(GTK_WINDOW(dialog), FALSE);
    gtk_dialog_run(GTK_DIALOG(dialog));
    param_table_hachage(&ht);
    gtk_widget_destroy(dialog);  

}

void option_caract_dico_fr(GtkButton *button, gpointer data) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
    GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
        "Vous avez choisi l'option : Afficher les caractÃ©ristiques du dictionnaire franÃ§ais. \n Cliquez sur OK puis rÃ©alisez la saisie sur votre terminal :)");
    gtk_window_set_modal(GTK_WINDOW(dialog), FALSE);
    gtk_dialog_run(GTK_DIALOG(dialog));
    param_table_hachage(&dico);
    gtk_widget_destroy(dialog);  
}

void option_afficher_dico_pred(GtkButton *button, gpointer data) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
    GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
        "Vous avez choisi l'option : Afficher le dictionnaire de prÃ©diction. \n Cliquez sur OK puis rÃ©alisez la saisie sur votre terminal :)");
    gtk_window_set_modal(GTK_WINDOW(dialog), FALSE);
    gtk_dialog_run(GTK_DIALOG(dialog));
    afficher_table(&ht);
    gtk_widget_destroy(dialog);  
}

void option_afficher_dico_fr(GtkButton * button, gpointer data) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
    GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
        "Vous avez choisi l'option : Afficher le dictionnaire franÃ§ais. \n Cliquez sur OK puis rÃ©alisez la saisie sur votre terminal :)");
    gtk_window_set_modal(GTK_WINDOW(dialog), FALSE);
    gtk_dialog_run(GTK_DIALOG(dialog));
    afficher_table(&dico);
    gtk_widget_destroy(dialog);  
}

void option_alveole_par_cle(GtkButton *button, gpointer data) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
    GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
        "Vous avez choisi l'option : Afficher une alvÃ©ole Ã  partir d'une clÃ©. \n Cliquez sur OK puis rÃ©alisez la saisie sur votre terminal :)");
    gtk_window_set_modal(GTK_WINDOW(dialog), FALSE);
    gtk_dialog_run(GTK_DIALOG(dialog));
    int cle;
    printf("\nSaisir une clÃ© pour afficher son alvÃ©ole : ");
    scanf("%d", &cle);
    afficher_alveole(&ht, cle);
    printf("\n");
    gtk_widget_destroy(dialog); 
}

void option_alveole_par_mot(GtkButton *button, gpointer data) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
    GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
        "Vous avez choisi l'option : Afficher une alvÃ©ole Ã  partir d'un mot. \n Cliquez sur OK puis rÃ©alisez la saisie sur votre terminal :)");
    gtk_window_set_modal(GTK_WINDOW(dialog), FALSE);
    gtk_dialog_run(GTK_DIALOG(dialog));
    char saisie[LG_MOT];
    printf("\nSaisir un mot pour afficher son alvÃ©ole : ");
    scanf("%s", saisie);
    afficher_alveole(&ht, calcul_cle(saisie, ht.taille));
    printf("\n");
    gtk_widget_destroy(dialog);
}