#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Date {
    char jour[3];
    char mois[3];
    char annee[5];
} date;

typedef struct Produit {
    char Nom_produit[50];
    char Reference[100];
    float Montant;
    date DateAchat;
} produit;

typedef struct Liste {
    produit cellule;
    struct Liste *suiv;
} liste;

liste *creer_liste_produits() {
    return NULL;
}

int est_vide(liste *tete) {
    return tete == NULL;
}

produit creer_produit() {
    produit p;
    printf("Nom du produit: ");
    scanf("%49s", p.Nom_produit);
    printf("Référence: ");
    scanf("%99s", p.Reference);
    printf("Montant: ");
    scanf("%f", &p.Montant);
    printf("Date d'achat (JJ MM AAAA): ");
    scanf("%2s %2s %4s", p.DateAchat.jour, p.DateAchat.mois, p.DateAchat.annee);
    return p;
}

void afficher_produit(produit p) {
    printf("Nom: %s | Réf: %s | Montant: %.2f | Date: %s/%s/%s\n",
           p.Nom_produit, p.Reference, p.Montant, p.DateAchat.jour, p.DateAchat.mois, p.DateAchat.annee);
}

liste *ajouter_debut(liste *tete) {
    liste *nouveau = (liste *)malloc(sizeof(liste));
    if (!nouveau) {
        printf("Erreur d'allocation mémoire.\n");
        return tete;
    }
    nouveau->cellule = creer_produit();
    nouveau->suiv = tete;
    return nouveau;
}

liste *ajouter_fin(liste *tete) {
    liste *nouveau = (liste *)malloc(sizeof(liste));
    if (!nouveau) {
        printf("Erreur d'allocation mémoire.\n");
        return tete;
    }
    nouveau->cellule = creer_produit();
    nouveau->suiv = NULL;
    if (tete == NULL)
        return nouveau;

    liste *temp = tete;
    while (temp->suiv != NULL)
        temp = temp->suiv;
    temp->suiv = nouveau;
    return tete;
}

void afficher_produits(liste *tete) {
    if (est_vide(tete)) {
        printf("La liste est vide.\n");
        return;
    }
    liste *temp = tete;
    while (temp != NULL) {
        afficher_produit(temp->cellule);
        temp = temp->suiv;
    }
}

int longueur(liste *tete) {
    int count = 0;
    while (tete != NULL) {
        count++;
        tete = tete->suiv;
    }
    return count;
}

void filtrer_date(liste *tete, date dt) {
    liste *temp = tete;
    int trouve = 0;
    while (temp != NULL) {
        if (strcmp(temp->cellule.DateAchat.jour, dt.jour) == 0 &&
            strcmp(temp->cellule.DateAchat.mois, dt.mois) == 0 &&
            strcmp(temp->cellule.DateAchat.annee, dt.annee) == 0) {
            afficher_produit(temp->cellule);
            trouve = 1;
        }
        temp = temp->suiv;
    }
    if (!trouve)
        printf("Aucun produit trouvé pour cette date.\n");
}

liste *supprimer_debut(liste *tete) {
    if (est_vide(tete)) {
        printf("Liste vide.\n");
        return tete;
    }
    liste *temp = tete;
    tete = tete->suiv;
    free(temp);
    return tete;
}

void supprimer_fin(liste **tete) {
    if (*tete == NULL) {
        printf("Liste vide.\n");
        return;
    }
    if ((*tete)->suiv == NULL) {
        free(*tete);
        *tete = NULL;
        return;
    }
    liste *temp = *tete;
    while (temp->suiv->suiv != NULL)
        temp = temp->suiv;
    free(temp->suiv);
    temp->suiv = NULL;
}


liste *rembourser(liste *tete, char *refer) {
    if (est_vide(tete))
        return tete;

    if (strcmp(tete->cellule.Reference, refer) == 0)
        return supprimer_debut(tete);

    liste *temp = tete, *prev = NULL;
    while (temp != NULL && strcmp(temp->cellule.Reference, refer) != 0) {
        prev = temp;
        temp = temp->suiv;
    }
    if (temp == NULL)
        return tete;

    prev->suiv = temp->suiv;
    free(temp);
    return tete;
}

void liberer_liste(liste *tete) {
    while (tete != NULL) {
        liste *temp = tete;
        tete = tete->suiv;
        free(temp);
    }
}

int main() {
    liste *stock = creer_liste_produits();
    int choix;
    char ref[100];
    date dt;

    do {
        printf("\nMenu:\n");
        printf("1. Ajouter produit au debut\n");
        printf("2. Ajouter produit a la fin\n");
        printf("3. Afficher la liste\n");
        printf("4. Supprimer premier produit\n");
        printf("5. Supprimer dernier produit\n");
        printf("6. Supprimer par reference\n");
        printf("7. Filtrer par date\n");
        printf("8. Longueur de la liste\n");
        printf("0. Quitter\n");
        printf("Choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                stock = ajouter_debut(stock);
                break;
            case 2:
                stock = ajouter_fin(stock);
                break;
            case 3:
                afficher_produits(stock);
                break;
            case 4:
                stock = supprimer_debut(stock);
                break;
            case 5:
                supprimer_fin(&stock);
                break;
            case 6:
                printf("Référence du produit à supprimer: ");
                scanf("%99s", ref);
                stock = rembourser(stock, ref);
                break;
            case 7:
                printf("Date (JJ MM AAAA): ");
                scanf("%2s %2s %4s", dt.jour, dt.mois, dt.annee);
                filtrer_date(stock, dt);
                break;
            case 8:
                printf("Longueur de la liste: %d\n", longueur(stock));
                break;
            case 0:
                printf("Fin du programme. Libération de la mémoire...\n");
                liberer_liste(stock);
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    return 0;
}
