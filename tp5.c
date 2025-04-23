#include <stdio.h>
#include <stdlib.h>

typedef struct Noeud {
    int valeur;
    struct Noeud *suivant;
} Noeud;

Noeud *cree(int _value) {
    Noeud *NV = (Noeud *)malloc(sizeof(Noeud));
    NV->valeur = _value;
    NV->suivant = NULL;
    return NV;
}

void affiche(Noeud *debut) {
    if (debut == NULL) {
        printf("La liste est vide\n");
        return;
    }
    
    Noeud *courant = debut;
    do {
        printf("Valeur: %d | Adresse: %p | Suivant: %p\n", 
               courant->valeur, courant, courant->suivant);
        courant = courant->suivant;
    } while (courant != debut);
}

int taille(Noeud* debut) {
    if (debut == NULL) return 0;
    
    int cpt = 1;
    Noeud* ptr = debut;
    while (ptr->suivant != debut) {
        cpt++;
        ptr = ptr->suivant;
    }
    return cpt;
}

Noeud *ajouterD(Noeud *debut, int val) {
    Noeud *NV = cree(val);
    if (debut == NULL) {
        NV->suivant = NV;
        return NV;
    }
    
    Noeud *ptr = debut;
    while (ptr->suivant != debut)
        ptr = ptr->suivant;
    
    ptr->suivant = NV;
    NV->suivant = debut;
    return NV;
}

Noeud *ajouterF(Noeud *debut, int val) {
    Noeud *NV = cree(val);
    if (debut == NULL) {
        NV->suivant = NV;
        return NV;
    }
    
    Noeud *ptr = debut;
    while (ptr->suivant != debut)
        ptr = ptr->suivant;
    
    ptr->suivant = NV;
    NV->suivant = debut;
    return debut;
}

Noeud *ajouterM(Noeud *debut, int pos, int val) {
    int t = taille(debut);
    if (pos < 1 || pos > t+1) {
        printf("Position invalide\n");
        return debut;
    }
    
    if (pos == 1) return ajouterD(debut, val);
    
    Noeud *NV = cree(val);
    Noeud *ptr = debut;
    
    for (int i = 1; i < pos - 1; i++)
        ptr = ptr->suivant;
    
    NV->suivant = ptr->suivant;
    ptr->suivant = NV;
    return debut;
}

Noeud *supprimerD(Noeud *debut) {
    if (debut == NULL) return NULL;
    
    if (debut->suivant == debut) {
        free(debut);
        return NULL;
    }
    
    Noeud *ptr = debut;
    while (ptr->suivant != debut)
        ptr = ptr->suivant;
    
    Noeud *tmp = debut;
    ptr->suivant = debut->suivant;
    debut = debut->suivant;
    free(tmp);
    return debut;
}

Noeud *supprimerF(Noeud *debut) {
    if (debut == NULL) return NULL;
    
    if (debut->suivant == debut) {
        free(debut);
        return NULL;
    }
    
    Noeud *ptr = debut;
    while (ptr->suivant->suivant != debut)
        ptr = ptr->suivant;
    
    free(ptr->suivant);
    ptr->suivant = debut;
    return debut;
}

Noeud *supprimerM(Noeud *debut, int pos) {
    int t = taille(debut);
    if (debut == NULL || pos < 1 || pos > t) {
        printf("Position invalide\n");
        return debut;
    }
    
    if (pos == 1) return supprimerD(debut);
    
    Noeud *ptr = debut;
    for (int i = 1; i < pos - 1; i++)
        ptr = ptr->suivant;
    
    Noeud *tmp = ptr->suivant;
    ptr->suivant = tmp->suivant;
    free(tmp);
    return debut;
}

int main() {
    Noeud *debut = NULL;
    
    // Exemple d'utilisation
    debut = ajouterD(debut, 10);
    debut = ajouterF(debut, 20);
    debut = ajouterM(debut, 2, 15);
    
    printf("Liste initiale:\n");
    affiche(debut);
    
    debut = supprimerM(debut, 2);
    printf("\nAprès suppression:\n");
    affiche(debut);
    
    return 0;
}