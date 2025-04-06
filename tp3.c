#include <stdio.h>
#include <stdlib.h>

typedef struct Noeud {
    int valeur;
    struct Noeud* suivant;
    struct Noeud* precedent;
} Noeud;

Noeud* creerNoeud(int valeur) {
    Noeud* nouveau = (Noeud*)malloc(sizeof(Noeud));
    nouveau->valeur = valeur;
    nouveau->suivant = NULL;
    nouveau->precedent = NULL;
    return nouveau;
}

void affiche(Noeud* debut) {
    Noeud* temp = debut;
    printf("Liste : ");
    while (temp != NULL) {
        printf("%d ", temp->valeur);
        temp = temp->suivant;
    }
    printf("\n");
}

void afficheInverse(Noeud* debut) {
    Noeud* temp = debut;
    while (temp->suivant != NULL)
        temp = temp->suivant;

    printf("Liste Inversee : ");
    while (temp != NULL) {
        printf("%d ", temp->valeur);
        temp = temp->precedent;
    }
    printf("\n");
}

Noeud* ajouterD(Noeud* debut, int valeur) {
    Noeud* nouveau = creerNoeud(valeur);
    if (debut != NULL) {
        nouveau->suivant = debut;
        debut->precedent = nouveau;
    }
    return nouveau;
}

Noeud* ajouterF(Noeud* debut, int valeur) {
    Noeud* nouveau = creerNoeud(valeur);
    if (debut == NULL) {
        return nouveau;
    }
    Noeud* temp = debut;
    while (temp->suivant != NULL)
        temp = temp->suivant;
    temp->suivant = nouveau;
    nouveau->precedent = temp;
    return debut;
}

int taille(Noeud* debut) {
    int c = 0;
    Noeud* temp = debut;
    while (temp != NULL) {
        c++;
        temp = temp->suivant;
    }
    return c;
}

Noeud* insertion(Noeud* debut, int pos, int valeur) {
    if (pos < 1 || pos > taille(debut) + 1) return debut;
    if (pos == 1) return ajouterD(debut, valeur);
    Noeud* nouveau = creerNoeud(valeur);
    Noeud* temp = debut;
    for (int i = 1; i < pos - 1; i++)
        temp = temp->suivant;

    nouveau->suivant = temp->suivant;
    nouveau->precedent = temp;
    if (temp->suivant != NULL)
        temp->suivant->precedent = nouveau;
    temp->suivant = nouveau;
    return debut;
}

Noeud* rechercher(Noeud* debut, int valeur) {
    Noeud* temp = debut;
    while (temp != NULL) {
        if (temp->valeur == valeur)
            return temp;
        temp = temp->suivant;
    }
    return NULL;
}
Noeud* suppressionD(Noeud* debut) {
    Noeud* temp = debut;
    debut = debut->suivant;
    if (debut != NULL)
        debut->precedent = NULL;
    free(temp);
    return debut;
}
Noeud* suppressionF(Noeud* debut) {
    Noeud* temp = debut;
    while (temp->suivant != NULL)
        temp = temp->suivant;
    temp->precedent->suivant = NULL;
    free(temp);
    return debut;
}
Noeud* suppressionP(Noeud* debut, int pos) {
    if (pos < 1 || pos > taille(debut)) return debut;
    if (pos == 1) return suppressionD(debut);
    Noeud* temp = debut;
    for (int i = 1; i < pos; i++)
        temp = temp->suivant;
    temp->precedent->suivant = temp->suivant;
    if (temp->suivant != NULL)
        temp->suivant->precedent = temp->precedent;
    free(temp);
    return debut;
}
Noeud* modifierD(Noeud* debut, int valeur) {
    if (debut != NULL)
        debut->valeur = valeur;
    return debut;
}
Noeud* modifierF(Noeud* debut, int valeur) {
    Noeud* temp = debut;
    while (temp->suivant != NULL)
        temp = temp->suivant;
    temp->valeur = valeur;
    return debut;
}
Noeud* modifierP(Noeud* debut, int pos, int valeur) {
    if (pos < 1 || pos > taille(debut)) return debut;
    Noeud* temp = debut;
    for (int i = 1; i < pos; i++)
     temp = temp->suivant;
    temp->valeur = valeur;
    return debut;
}
Noeud* tri(Noeud* debut) {
    if (debut == NULL || debut->suivant == NULL) {
        return debut; 
    }

    Noeud* i, * j, * temp;
    int tmp_val;

   
    for (i = debut; i != NULL; i = i->suivant) {
        for (j = i->suivant; j != NULL; j = j->suivant) {
           
            if (i->valeur > j->valeur) {
             
                tmp_val = i->valeur;
                i->valeur = j->valeur;
                j->valeur = tmp_val;

               
                if (i->precedent != NULL) {
                    i->precedent->suivant = j;
                }
                if (j->suivant != NULL) {
                    j->suivant->precedent = i;
                }

               
                temp = i->suivant;
                i->suivant = j->suivant;
                j->suivant = temp;

                temp = i->precedent;
                i->precedent = j->precedent;
                j->precedent = temp;

                if (i->precedent == NULL) {
                    debut = i;
                }

                if (j->precedent == NULL) {
                    debut = j;
                }
            }
        }
    }
    return debut;
}


int main() {
    Noeud* debut = NULL;
    int choix, valeur, pos;

  
    debut = ajouterF(debut, 30);  
    debut = ajouterF(debut, 10);
    debut = ajouterF(debut, 20);  
    debut = ajouterF(debut, 40);  

   
    printf("Liste initiale :\n");
    affiche(debut);

    do {
        printf("1. Ajouter en debut\n2. Ajouter en fin\n3. Afficher\n4. Afficher inverse\n5. Insertion\n6. Rechercher\n7. Supprimer debut\n8. Supprimer fin\n9. Supprimer position\n10. Modifier debut\n11. Modifier fin\n12. Modifier position\n13. Trier\n14. Quitter\n");
        printf("Choisissez une option: ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                printf("Entrez la valeur: ");
                scanf("%d", &valeur);
                debut = ajouterD(debut, valeur);
                break;
            case 2:
                printf("Entrez la valeur: ");
                scanf("%d", &valeur);
                debut = ajouterF(debut, valeur);
                break;
            case 3:
                affiche(debut);
                break;
            case 4:
                afficheInverse(debut);
                break;
            case 5:
                printf("Entrez la position et la valeur: ");
                scanf("%d %d", &pos, &valeur);
                debut = insertion(debut, pos, valeur);
                break;
            case 6:
                printf("Entrez la valeur a rechercher: ");
                scanf("%d", &valeur);
                Noeud* trouve = rechercher(debut, valeur);
                if (trouve != NULL)
                    printf("Valeur trouvee: %d\n", trouve->valeur);
                else
                    printf("Valeur non trouvee.\n");
                break;
            case 7:
                debut = suppressionD(debut);
                break;
            case 8:
                debut = suppressionF(debut);
                break;
            case 9:
                printf("Entrez la position a supprimer: ");
                scanf("%d", &pos);
                debut = suppressionP(debut, pos);
                break;
            case 10:
                printf("Entrez la nouvelle valeur: ");
                scanf("%d", &valeur);
                debut = modifierD(debut, valeur);
                break;
            case 11:
                printf("Entrez la nouvelle valeur: ");
                scanf("%d", &valeur);
                debut = modifierF(debut, valeur);
                break;
            case 12:
                printf("Entrez la position et la nouvelle valeur: ");
                scanf("%d %d", &pos, &valeur);
                debut = modifierP(debut, pos, valeur);
                break;
            case 13:
                debut = tri(debut);
                break;
            case 14:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    } while (choix != 14);

    return 0;
}
