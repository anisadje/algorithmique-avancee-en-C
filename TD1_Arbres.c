#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Portfolio GitHub - Arbres Binaires
 *
 * Ce fichier contient des fonctions essentielles pour manipuler
 * des arbres binaires, incluant :
 * - Création et insertion de nœuds
 * - Parcours (itératif et récursif)
 * - Comptage de nœuds selon différentes propriétés
 * - Vérification de propriétés de l'arbre (complet, miroir)
 * 
 * Complexité temporelle de chaque fonction indiquée.
 */

// -------------------- Définition de la structure --------------------
typedef struct Noeud {
    int valeur; 
    struct Noeud *SAG; // sous-arbre gauche
    struct Noeud *SAD; // sous-arbre droit
} Noeud; 

typedef Noeud *Arbre; // Arbre désigne la racine

// -------------------- Fonctions utilitaires --------------------

/**
 * @brief Retourne le maximum entre deux entiers
 * @param a Premier entier
 * @param b Second entier
 * @return int Le maximum
 * Complexité : O(1)
 */
int maximum(int a, int b){
    if(a > b) return a;
    return b;
}

// -------------------- Création de nœuds --------------------

/**
 * @brief Crée un nœud avec ses sous-arbres
 * @param G Sous-arbre gauche
 * @param D Sous-arbre droit
 * @param v Valeur du nœud
 * @return Arbre Nouveau nœud
 * Complexité : O(1)
 */
Arbre creerNoeudAvecFils(Arbre G, Arbre D, int v){
    Arbre tmp = (Arbre)malloc(sizeof(Noeud));
    if(tmp == NULL){
        perror("Erreur d'allocation mémoire"); 
        exit(EXIT_FAILURE);
    }
    tmp->valeur = v;
    tmp->SAG = G;
    tmp->SAD = D;
    return tmp;
}

/**
 * @brief Crée un nœud sans fils (feuille)
 * @param v Valeur du nœud
 * @return Arbre Nouveau nœud feuille
 * Complexité : O(1)
 */
Arbre creerNoeudSimple(int v){
    return creerNoeudAvecFils(NULL, NULL, v);
}

// -------------------- Hauteur d'un arbre --------------------

/**
 * @brief Calcule la hauteur d'un arbre
 * @param racine Racine de l'arbre
 * @return int Hauteur
 * Complexité : O(n)
 */
int hauteur(Arbre racine){
    if(racine == NULL) return 0;
    return 1 + maximum(hauteur(racine->SAG), hauteur(racine->SAD));
}

// -------------------- Miroir d'un arbre --------------------

/**
 * @brief Renvoie un nouvel arbre miroir
 * @param racine Racine de l'arbre original
 * @return Arbre Racine du miroir
 * Complexité : O(n)
 */
Arbre Fmiroir(Arbre racine){
    if(racine == NULL) return NULL;
    Arbre miroir_D = Fmiroir(racine->SAD);
    Arbre miroir_G = Fmiroir(racine->SAG);
    return creerNoeudAvecFils(miroir_D, miroir_G, racine->valeur);
}

/**
 * @brief Transforme l'arbre en son miroir (in-place)
 * @param racine Racine de l'arbre
 * Complexité : O(n)
 */
void Pmiroir(Arbre racine){
    if(racine == NULL) return;
    Arbre tmp = racine->SAG;
    racine->SAG = racine->SAD;
    racine->SAD = tmp;
    Pmiroir(racine->SAG);
    Pmiroir(racine->SAD);
}

/**
 * @brief Vérifie si deux arbres sont miroirs
 * @param A1 Première racine
 * @param A2 Deuxième racine
 * @return true si miroirs, false sinon
 * Complexité : O(n)
 */
bool SontMiroirs(Arbre A1, Arbre A2){
    if(A1 == NULL && A2 == NULL) return true;
    if(A1 == NULL || A2 == NULL || A1->valeur != A2->valeur) return false;
    return SontMiroirs(A1->SAG, A2->SAD) && SontMiroirs(A1->SAD, A2->SAG);
}

// -------------------- Implémentation d'une pile --------------------
typedef struct ElementPile{
    Arbre ptr; 
    struct ElementPile *suivant; 
} ElementPile; 

typedef struct {
    ElementPile *sommet; 
} Pile; 

Pile *creer_pile(){
    Pile *P = (Pile*)malloc(sizeof(Pile)); 
    if(P == NULL){
        perror("Erreur d'allocation pile");
        exit(EXIT_FAILURE);
    }
    P->sommet = NULL;
    return P;
}

bool estVide(Pile *P){
    return P->sommet == NULL;
}

void empiler(Pile *P, Arbre racine){
    ElementPile *nouvel_element = (ElementPile*)malloc(sizeof(ElementPile)); 
    if(nouvel_element == NULL){
        perror("Erreur d'allocation ElementPile");
        exit(EXIT_FAILURE);
    }
    nouvel_element->ptr = racine;
    nouvel_element->suivant = P->sommet;
    P->sommet = nouvel_element;
}

Arbre depiler(Pile *P){
    if(estVide(P)) return NULL;
    ElementPile *tmp = P->sommet; 
    Arbre racine = tmp->ptr;
    P->sommet = tmp->suivant; 
    free(tmp); 
    return racine;
}

// -------------------- Affichage préfixe itératif --------------------
/**
 * @brief Affiche l'arbre en parcours préfixe itératif
 * @param racine Racine de l'arbre
 * Complexité : O(n)
 */
void AffichagePrefixe(Arbre racine){
    if(racine == NULL) return;
    Pile *pile = creer_pile();
    empiler(pile, racine);

    while(!estVide(pile)){
        Arbre X = depiler(pile);
        printf("%d ", X->valeur);
        if(X->SAD) empiler(pile, X->SAD);
        if(X->SAG) empiler(pile, X->SAG);
    }
    printf("\n");
}

// -------------------- Fonctions de comptage --------------------

int CompteSansAsc(Arbre racine){
    if(!racine || racine->valeur == 0) return 0;
    int leftVal = (racine->SAG && racine->SAG->valeur);
    int rightVal = (racine->SAD && racine->SAD->valeur);
    if(!leftVal && !rightVal)
        return 1 + CompteSansAsc(racine->SAG) + CompteSansAsc(racine->SAD);
    else
        return CompteSansAsc(racine->SAG) + CompteSansAsc(racine->SAD);
}

int CompteSansDesc(Arbre racine){
    if(!racine || racine->valeur == 0) return 0;
    int SAG_val = (racine->SAG && racine->SAG->valeur);
    int SAD_val = (racine->SAD && racine->SAD->valeur);
    if(!SAG_val && !SAD_val)
        return 1 + CompteSansDesc(racine->SAG) + CompteSansDesc(racine->SAD);
    else
        return CompteSansDesc(racine->SAG) + CompteSansDesc(racine->SAD);
}

int CompteHEgalP(Arbre racine, int profondeur_actuelle, int hauteur_totale){
    if(!racine) return 0;
    int count = 0;
    if(racine->valeur && (hauteur_totale - profondeur_actuelle == 1)) count = 1;
    count += CompteHEgalP(racine->SAG, profondeur_actuelle + 1, hauteur_totale);
    count += CompteHEgalP(racine->SAD, profondeur_actuelle + 1, hauteur_totale);
    return count;
}

bool EstComplet(Arbre racine){
    if(!racine) return true;
    if((racine->SAG == NULL) != (racine->SAD == NULL)) return false;
    return EstComplet(racine->SAG) && EstComplet(racine->SAD);
}

// -------------------- Main pour tests --------------------
int main() {
    // Création d'un petit arbre binaire
    Arbre racine = creerNoeudSimple(1);
    racine->SAG = creerNoeudSimple(0);
    racine->SAD = creerNoeudSimple(1);
    racine->SAD->SAG = creerNoeudSimple(1);
    racine->SAD->SAD = creerNoeudSimple(0);

    printf("Hauteur: %d\n", hauteur(racine));
    printf("CompteSansAsc: %d\n", CompteSansAsc(racine));
    printf("CompteSansDesc: %d\n", CompteSansDesc(racine));

    int h = hauteur(racine);
    printf("CompteHEgalP: %d\n", CompteHEgalP(racine, 0, h));
    printf("EstComplet: %s\n", EstComplet(racine) ? "Vrai" : "Faux");

    printf("Affichage Prefixe: ");
    AffichagePrefixe(racine);

    return 0;
}
