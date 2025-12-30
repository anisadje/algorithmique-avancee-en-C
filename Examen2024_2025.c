#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*
 * Arbres Binaires - Codes pour l'examen 2024-2025
 *
 * Ce fichier contient les fonctions classiques et avancées
 * sur les arbres binaires et ABR :
 * - Comptage de feuilles, petits-fils et queues de cerises
 * - Transformation de l'arbre (mirroir, queue de cerises)
 * - Vérification d'arbre type Fibonacci
 * 
 * La complexité temporelle de chaque fonction est indiquée.
 */

// -------------------- Définition de la structure --------------------
typedef struct Noeud {
    int valeur; 
    struct Noeud *SAG; // sous-arbre gauche
    struct Noeud *SAD; // sous-arbre droit
} Noeud; 

typedef Noeud *Arbre; // Arbre désigne la racine

// -------------------- Fonctions sur les arbres --------------------

// -------------------- Nombre de petits-fils feuilles --------------------
// Complexité : O(n)
int NombreDePetitsFilsFeuilles(Arbre A) {
    if (A == NULL) return 0;
    int cpt = 0;

    if (A->SAG != NULL) {
        if (A->SAG->SAG != NULL && A->SAG->SAG->SAG == NULL && A->SAG->SAG->SAD == NULL)
            cpt++;
        if (A->SAG->SAD != NULL && A->SAG->SAD->SAG == NULL && A->SAG->SAD->SAD == NULL)
            cpt++;
    }

    if (A->SAD != NULL) {
        if (A->SAD->SAG != NULL && A->SAD->SAG->SAG == NULL && A->SAD->SAG->SAD == NULL)
            cpt++;
        if (A->SAD->SAD != NULL && A->SAD->SAD->SAG == NULL && A->SAD->SAD->SAD == NULL)
            cpt++;
    }

    return cpt;
}

// -------------------- Compte des queues de cerises --------------------
// Complexité : O(n)
int CompteQueuesDeCerises(Arbre A) {
    if (A == NULL) return 0;

    int estQueue = 0;
    if (A->SAG != NULL && A->SAD != NULL) {
        bool gFeuille = (A->SAG->SAG == NULL && A->SAG->SAD == NULL);
        bool dFeuille = (A->SAD->SAG == NULL && A->SAD->SAD == NULL);
        if (gFeuille && dFeuille) estQueue = 1;
    }

    return estQueue + CompteQueuesDeCerises(A->SAG) + CompteQueuesDeCerises(A->SAD);
}

// -------------------- Création de queues de cerises à profondeur P --------------------
// Complexité : O(n)
void RPQDCPP(Arbre *A, int P) {
    if (*A == NULL) return;

    if (P == 0) {
        if ((*A)->SAG == NULL && (*A)->SAD == NULL) {
            (*A)->SAG = malloc(sizeof(Noeud));
            (*A)->SAD = malloc(sizeof(Noeud));
            (*A)->SAG->SAG = NULL;
            (*A)->SAG->SAD = NULL;
            (*A)->SAD->SAG = NULL;
            (*A)->SAD->SAD = NULL;
        }
        return;
    }

    RPQDCPP(&((*A)->SAG), P - 1);
    RPQDCPP(&((*A)->SAD), P - 1);
}

// -------------------- Compte nœuds internes >= x dans un ABR --------------------
// Complexité : O(n)
int CompteXOuPlusDansABR(Arbre A, int x) {
    if (A == NULL) return 0;

    int cpt = 0;
    bool estInterne = (A->SAG != NULL || A->SAD != NULL);
    if (estInterne && A->valeur >= x) cpt = 1;

    if (A->valeur < x) return CompteXOuPlusDansABR(A->SAD, x);
    return cpt + CompteXOuPlusDansABR(A->SAG, x) + CompteXOuPlusDansABR(A->SAD, x);
}

// -------------------- Compte des feuilles valant 1 --------------------
// Complexité : O(n)
int CompteFVrai(Arbre A) {
    if (A == NULL) return 0;
    if (A->SAG == NULL && A->SAD == NULL) {
        if (A->valeur == 1) return 1;
        return 0;
    }
    return CompteFVrai(A->SAG) + CompteFVrai(A->SAD);
}

// Compte les feuilles valant 1 à profondeur P
// Complexité : O(n)
int CompteFVraiProfondeurP(Arbre A, int P) {
    if (A == NULL) return 0;
    if (P == 0) {
        if (A->SAG == NULL && A->SAD == NULL) {
            if (A->valeur == 1) return 1;
            return 0;
        }
        return 0;
    }
    return CompteFVraiProfondeurP(A->SAG, P - 1) + CompteFVraiProfondeurP(A->SAD, P - 1);
}

// -------------------- Hauteur de l'arbre --------------------
// Complexité : O(n)
int hauteur(Arbre A) {
    if (A == NULL) return -1;
    int hg = hauteur(A->SAG);
    int hd = hauteur(A->SAD);
    if (hg > hd) return hg + 1;
    return hd + 1;
}

// -------------------- Vérification arbre type Fibonacci --------------------
// Version 1 : simple, récursive
// Complexité : O(n^2)
bool ArbreFibonacci_V1(Arbre A) {
    if (A == NULL) return true;
    int hg = hauteur(A->SAG);
    int hd = hauteur(A->SAD);
    if (hg - hd > 1 || hd - hg > 1) return false;
    return ArbreFibonacci_V1(A->SAG) && ArbreFibonacci_V1(A->SAD);
}

// Version 2 : retour hauteur et booléen
// Complexité : O(n)
void f_V2(Arbre A, int *h, bool *estFibo) {
    if (A == NULL) { *h = -1; *estFibo = true; return; }
    int hG, hD; bool efG, efD;
    f_V2(A->SAG, &hG, &efG);
    f_V2(A->SAD, &hD, &efD);
    *h = (hG > hD) ? 1 + hG : 1 + hD;
    *estFibo = efG && efD && (hG - hD <= 1 && hD - hG <= 1);
}

// Version 3 : booléen passé par pointeur
// Complexité : O(n)
void f_V3(Arbre A, int *h, bool *estFibo) {
    if (A == NULL) { *h = -1; return; }
    int hG, hD;
    f_V3(A->SAG, &hG, estFibo);
    f_V3(A->SAD, &hD, estFibo);
    *h = (hG > hD) ? 1 + hG : 1 + hD;
    if (hG - hD > 1 || hD - hG > 1) *estFibo = false;
}

// -------------------- Main pour tests --------------------
int main() {
    // Création d'un arbre pour tests
    Arbre racine = malloc(sizeof(Noeud));
    racine->valeur = 1;
    racine->SAG = malloc(sizeof(Noeud));
    racine->SAG->valeur = 1;
    racine->SAG->SAG = racine->SAG->SAD = NULL;
    racine->SAD = malloc(sizeof(Noeud));
    racine->SAD->valeur = 0;
    racine->SAD->SAG = racine->SAD->SAD = NULL;

    printf("Nombre de petits-fils feuilles: %d\n", NombreDePetitsFilsFeuilles(racine));
    printf("Compte queues de cerises: %d\n", CompteQueuesDeCerises(racine));

    int h;
    bool estFibo = true;
    f_V2(racine, &h, &estFibo);
    printf("Hauteur de l'arbre: %d\n", h);
    printf("Arbre type Fibonacci: %s\n", estFibo ? "Oui" : "Non");

    printf("Nombre de feuilles valant 1: %d\n", CompteFVrai(racine));

    // Libération mémoire simple
    free(racine->SAG);
    free(racine->SAD);
    free(racine);

    return 0;
}
