#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Etudiant {
    int id;
    char nom[50];
    float moyenne;
    struct Etudiant* suivant;
    struct Etudiant* precedent;
} Etudiant;

Etudiant* creer_etudiant() {
    Etudiant* nouveau = (Etudiant*)malloc(sizeof(Etudiant));
    if (nouveau == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return NULL;
    }

    printf("Saisir l'IID de l'étudiant : ");
    scanf("%d", &nouveau->id);
    getchar();
    printf("Saisir le nom de l'étudiant : ");
    scanf("%s", nouveau->nom);
    printf("Saisir la moyenne de l'étudiant : ");
    scanf("%f", &nouveau->moyenne);

    nouveau->suivant = NULL;
    nouveau->precedent = NULL;

    return nouveau;
}

Etudiant* ajouter_position(Etudiant* tete, Etudiant* nouveau, int position) {
    if (position < 1) {
        printf("Position invalide.\n");
        return tete;
    }

    if (position == 1) {
        nouveau->suivant = tete;
        if (tete != NULL) {
            tete->precedent = nouveau;
        }
        return nouveau;
    }

    Etudiant* temp = tete;
    int i = 1;
    while (temp != NULL && i < position - 1) {
        temp = temp->suivant;
        i++;
    }

    if (temp == NULL) {
        printf("Position en dehors de la liste.\n");
        return tete;
    }

    nouveau->suivant = temp->suivant;
    nouveau->precedent = temp;
    if (temp->suivant != NULL) {
        temp->suivant->precedent = nouveau;
    }
    temp->suivant = nouveau;

    return tete;
}

Etudiant* supprimer_position(Etudiant* tete, int position) {
    if (position < 1) {
        printf("Position invalide.\n");
        return tete;
    }

    Etudiant* temp = tete;
    int i = 1;
    while (temp != NULL && i < position) {
        temp = temp->suivant;
        i++;
    }

    if (temp == NULL) {
        printf("Position en dehors de la liste.\n");
        return tete;
    }

    if (temp->precedent != NULL) {
        temp->precedent->suivant = temp->suivant;
    } else {
        tete = temp->suivant;
    }

    if (temp->suivant != NULL) {
        temp->suivant->precedent = temp->precedent;
    }

    free(temp);
    return tete;
}

void afficher_liste(Etudiant* tete) {
    Etudiant* temp = tete;
    while (temp != NULL) {
        printf("ID: %d, Nom: %s, Moyenne: %.2f\n", temp->id, temp->nom, temp->moyenne);
        temp = temp->suivant;
    }
}

Etudiant* derniere_cellule(Etudiant* tete) {
    Etudiant* temp = tete;
    while (temp != NULL && temp->suivant != NULL) {
        temp = temp->suivant;
    }
    return temp;
}

void afficher_liste_inverse(Etudiant* dernier) {
    Etudiant* temp = dernier;
    while (temp != NULL) {
        printf("ID: %d, Nom: %s, Moyenne: %.2f\n", temp->id, temp->nom, temp->moyenne);
        temp = temp->precedent;
    }
}

int chercher_etudiant(Etudiant* tete, int id) {
    Etudiant* temp = tete;
    while (temp != NULL) {
        if (temp->id == id) {
            return 1;
        }
        temp = temp->suivant;
    }
    return 0;
}

void separer_par_moyenne(Etudiant* tete, Etudiant** liste_mention, Etudiant** liste_non_mention) {
    Etudiant* temp = tete;
    while (temp != NULL) {
        Etudiant* nouveau = (Etudiant*)malloc(sizeof(Etudiant));
        if (nouveau == NULL) {
            printf("Erreur d'allocation mémoire.\n");
            return;
        }
        nouveau->id = temp->id;
        strcpy(nouveau->nom, temp->nom);
        nouveau->moyenne = temp->moyenne;
        nouveau->suivant = NULL;
        nouveau->precedent = NULL;

        if (temp->moyenne >= 10) {
            *liste_mention = ajouter_position(*liste_mention, nouveau, 1);
        } else {
            *liste_non_mention = ajouter_position(*liste_non_mention, nouveau, 1);
        }

        temp = temp->suivant;
    }
}

int main() {
    Etudiant* tete = NULL;
    Etudiant* liste_mention = NULL;
    Etudiant* liste_non_mention = NULL;
    int choix, position, id;

    do {
        printf("\nMenu de gestion des etudiants :\n");
        printf("1. Ajouter un etudiant\n");
        printf("2. Afficher la liste des etudiants\n");
        printf("3. Ajouter un etudiant à une position donnée\n");
        printf("4. Supprimer un etudiant d'une position donnée\n");
        printf("5. Rechercher un etudiant par ID\n");
        printf("6. Afficher la liste des etudiants en sens inverse\n");
        printf("7. Séparer les étudiants par moyenne\n");
        printf("8. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                Etudiant* etudiant = creer_etudiant();
                tete = ajouter_position(tete, etudiant, 1);
                break;
            }
            case 2:
                afficher_liste(tete);
                break;
            case 3: {
                printf("Entrez la position à laquelle ajouter l'étudiant : ");
                scanf("%d", &position);
                Etudiant* etudiant = creer_etudiant();
                tete = ajouter_position(tete, etudiant, position);
                break;
            }
            case 4:
                printf("Entrez la position à laquelle supprimer l'étudiant : ");
                scanf("%d", &position);
                tete = supprimer_position(tete, position);
                break;
            case 5:
                printf("Entrez l'I D de l'étudiant à rechercher : ");
                scanf("%d", &id);
                if (chercher_etudiant(tete, id)) {
                    printf("L'étudiant avec l'I D %d a été trouvé.\n", id);
                } else {
                    printf("L'étudiant avec l'I D %d n'a pas été trouvé.\n", id);
                }
                break;
            case 6: {
                Etudiant* dernier = derniere_cellule(tete);
                afficher_liste_inverse(dernier);
                break;
            }
            case 7:
                separer_par_moyenne(tete, &liste_mention, &liste_non_mention);
                printf("Etudiants avec mention :\n");
                afficher_liste(liste_mention);
                printf("Etudiants sans mention :\n");
                afficher_liste(liste_non_mention);
                break;
            case 8:
                printf("Au revoir \n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 8);

    return 0;
}