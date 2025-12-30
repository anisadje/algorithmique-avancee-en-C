#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Arbres Binaires - Codes pour l'examen 2023-2024
 *
 * Ce fichier contient les fonctions classiques et avancées
 * sur les arbres binaires et ABR :
 * - Détection de feuilles et nœuds internes
 * - Comptage de nœuds à profondeur ou hauteur donnée
 * - Vérification d'ABR et d'arbres spécifiques
 * - Simplification de l'arbre
 * 
 * La complexité temporelle de chaque fonction est indiquée.
 */

// -------------------- Définition de la structure --------------------
typedef struct Noeud {
    int valeur; 
    struct Noeud *SAG; // sous-arbre gauche
    struct Noeud *SAD; // sous-arbre droit
} Noeud; 

typedef Noeud *Arbre;

// -------------------- Fonctions utilitaires --------------------

// Vérifie si un nœud est une feuille
// Complexité : O(1)
bool estFeuille(Arbre a) {
    if (a != NULL && a->SAG == NULL && a->SAD == NULL) return true;
    return false;
}

// Vérifie si un nœud est interne (non-feuille)
// Complexité : O(1)
bool estInterne(Arbre a) {
    if (a != NULL && (a->SAG != NULL || a->SAD != NULL)) return true;
    return false;
}

// Compte le nombre de nœuds internes dans un arbre
// Complexité : O(n)
int compterInternes(Arbre a) {
    if (a == NULL || estFeuille(a)) return 0;
    return 1 + compterInternes(a->SAG) + compterInternes(a->SAD);
}

// Vérifie si l'arbre a au moins trois nœuds internes
// Complexité : O(n)
bool AuMoinsTroisNoeudsInternes(Arbre a) {
    int nb = compterInternes(a);
    if (nb >= 3) return true;
    return false;
}

// -------------------- Fonctions de comparaison et élagage --------------------

// Vérifie si a1 est un élagage de a2
// Complexité : O(n)
bool Elagage(Arbre a1, Arbre a2) {
    if (a1 == NULL) return true;
    if (a2 == NULL) return false;

    if (estFeuille(a1)) return true;

    if (a1->valeur != a2->valeur) return false;

    return Elagage(a1->SAG, a2->SAG) && Elagage(a1->SAD, a2->SAD);
}

// Vérifie si toutes les feuilles ont la valeur 1
// Complexité : O(n)
bool TOUTBLANC(Arbre a) {
    if (a == NULL) return true;
    if (estFeuille(a)) {
        if (a->valeur == 1) return true;
        return false;
    }

    if (TOUTBLANC(a->SAG) && TOUTBLANC(a->SAD)) return true;
    return false;
}

// -------------------- Simplification de l'arbre --------------------

// Simplifie l'arbre : si deux feuilles de même couleur sont filles d'un nœud,
// elles sont supprimées et le nœud devient une feuille
// Complexité : O(n)
void SIMPLIFIE(Arbre *a) {
    if (*a == NULL || estFeuille(*a)) return;

    SIMPLIFIE(&((*a)->SAG));
    SIMPLIFIE(&((*a)->SAD));

    if (estFeuille((*a)->SAG) && estFeuille((*a)->SAD)) {
        if ((*a)->SAG->valeur == (*a)->SAD->valeur) {
            int couleur = (*a)->SAG->valeur;
            free((*a)->SAG);
            free((*a)->SAD);
            (*a)->SAG = NULL;
            (*a)->SAD = NULL;
            (*a)->valeur = couleur;
        }
    }
}

// -------------------- Comptage de nœuds internes --------------------

// Compte les nœuds internes à profondeur P
// Complexité : O(n)
int CompteNoeudsInternesProfondeurP(Arbre a, int p) {
    if (a == NULL) return 0;
    if (p == 0) {
        if (estInterne(a)) return 1;
        return 0;
    }
    return CompteNoeudsInternesProfondeurP(a->SAG, p - 1) +
           CompteNoeudsInternesProfondeurP(a->SAD, p - 1);
}

// Comptage de nœuds internes à hauteur H
// Complexité : O(n)
void verifHauteur(Arbre a, int h_cible, int *h_noeud, int *nb) {
    if (a == NULL) {
        *h_noeud = -1;
        return;
    }

    int hG = -1, hD = -1;
    verifHauteur(a->SAG, h_cible, &hG, nb);
    verifHauteur(a->SAD, h_cible, &hD, nb);

    if (hG > hD) *h_noeud = 1 + hG;
    else *h_noeud = 1 + hD;

    if (*h_noeud == h_cible && estInterne(a)) (*nb)++;
}

int CompteNoeudsInternesHauteurH(Arbre a, int h) {
    int h_res = 0, nb = 0;
    verifHauteur(a, h, &h_res, &nb);
    return nb;
}

// -------------------- Recherche de valeur dans ABR --------------------

// Compte le nombre de nœuds valant x dans un ABR
// Complexité : O(n) pour un arbre non équilibré, O(log n) pour un ABR équilibré
int CompteXDansABR(Arbre a, int x) {
    if (a == NULL) return 0;
    if (a->valeur == x)
        return 1 + CompteXDansABR(a->SAG, x) + CompteXDansABR(a->SAD, x);
    if (x < a->valeur) return CompteXDansABR(a->SAG, x);
    return CompteXDansABR(a->SAD, x);
}

// Vérification qu'un arbre est ABR (utilitaire avec bornes)
// Complexité : O(n)
bool estABR_Util(Arbre a, long min, long max) {
    if (a == NULL) return true;
    if (a->valeur <= min || a->valeur >= max) return false;
    return estABR_Util(a->SAG, min, a->valeur) &&
           estABR_Util(a->SAD, a->valeur, max);
}

// Fonction principale pour tester si un arbre est ABR
// Complexité : O(n)
bool EstABR(Arbre a) {
    return estABR_Util(a, -2147483648L, 2147483647L);
}

// -------------------- Exemple de main --------------------
int main() {
    // Création d'un petit arbre binaire pour test
    Arbre racine = malloc(sizeof(Noeud));
    racine->valeur = 10;
    racine->SAG = malloc(sizeof(Noeud));
    racine->SAG->valeur = 5;
    racine->SAG->SAG = racine->SAG->SAD = NULL;
    racine->SAD = malloc(sizeof(Noeud));
    racine->SAD->valeur = 15;
    racine->SAD->SAG = racine->SAD->SAD = NULL;

    printf("Nombre de nœuds internes >= 3: %s\n", AuMoinsTroisNoeudsInternes(racine) ? "Oui" : "Non");
    printf("Arbre est ABR: %s\n", EstABR(racine) ? "Oui" : "Non");

    printf("Compte de nœuds valant 5 dans ABR: %d\n", CompteXDansABR(racine, 5));
    printf("Compte de nœuds internes à profondeur 1: %d\n", CompteNoeudsInternesProfondeurP(racine, 1));
    printf("Compte de nœuds internes à hauteur 1: %d\n", CompteNoeudsInternesHauteurH(racine, 1));

    // Libération mémoire
    free(racine->SAG);
    free(racine->SAD);
    free(racine);

    return 0;
}
