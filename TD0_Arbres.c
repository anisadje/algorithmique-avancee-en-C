#include <stdio.h>
#include <stdlib.h>

/*
 * Ce document contient les codes de base à maîtriser pour valider la matière.
 * Il comprend les opérations classiques sur les arbres binaires de recherche :
 * création, insertion, recherche, parcours et suppression.
 */

// -------------------- Définition de la structure --------------------
typedef struct Noeud {
    int valeur; 
    struct Noeud *gauche;   // sous-arbre gauche
    struct Noeud *droit;    // sous-arbre droit
} Noeud;

typedef Noeud *Arbre; // Arbre désigne la racine de type Noeud*

// -------------------- Création d'un nœud --------------------
Arbre creerNoeud(int v){
    Arbre nouveau_noeud = (Arbre)malloc(sizeof(Noeud)); 
    if (nouveau_noeud != NULL) {
        nouveau_noeud->valeur = v; 
        nouveau_noeud->gauche = NULL; 
        nouveau_noeud->droit = NULL;
    }
    return nouveau_noeud;
}

// -------------------- Insertion dans un arbre binaire de recherche --------------------
Arbre inserer(Arbre racine, int v){
    if (racine == NULL){
        return creerNoeud(v);
    }

    if(v < racine->valeur){
        racine->gauche = inserer(racine->gauche, v);
    } else if(v > racine->valeur){
        racine->droit = inserer(racine->droit, v);
    }
    // Si v == racine->valeur, on ne fait rien (pas de doublon)
    return racine;
}

// -------------------- Recherche d'une valeur --------------------
Arbre rechercher(Arbre racine, int v){
    if(racine == NULL || racine->valeur == v){
        return racine;
    }
    if(v > racine->valeur){
        return rechercher(racine->droit, v);
    } else {
        return rechercher(racine->gauche, v);
    }
}

// -------------------- Hauteur et profondeur --------------------
int maximum(int a, int b){
    return (a > b) ? a : b;
}

// Hauteur de l'arbre (nombre de niveaux - 1)
int hauteur(Arbre racine){
    if(racine == NULL) return -1;
    return 1 + maximum(hauteur(racine->gauche), hauteur(racine->droit));
}

// Profondeur d'un nœud à partir de la racine
int profondeur(Arbre racine, int v, int niveau){
    if(racine == NULL) return -1;
    if(racine->valeur == v) return niveau;

    int res_gauche = profondeur(racine->gauche, v, niveau + 1);
    if(res_gauche != -1) return res_gauche;

    return profondeur(racine->droit, v, niveau + 1);
}

// -------------------- Trouver le minimum --------------------
Arbre trouverMin(Arbre racine){
    while(racine && racine->gauche != NULL){
        racine = racine->gauche;
    }
    return racine;
}

// -------------------- Parcours de l'arbre --------------------
void visiterPrefixe(Arbre racine){
    if(racine == NULL) return;
    printf("%d ", racine->valeur);       // Racine
    visiterPrefixe(racine->gauche);      // Sous-arbre gauche
    visiterPrefixe(racine->droit);       // Sous-arbre droit
}

void visiterInfixe(Arbre racine){
    if(racine == NULL) return;
    visiterInfixe(racine->gauche);       // Sous-arbre gauche
    printf("%d ", racine->valeur);       // Racine
    visiterInfixe(racine->droit);        // Sous-arbre droit
}

void visiterSuffixe(Arbre racine){
    if(racine == NULL) return;
    visiterSuffixe(racine->gauche);      // Sous-arbre gauche
    visiterSuffixe(racine->droit);       // Sous-arbre droit
    printf("%d ", racine->valeur);       // Racine
}

// -------------------- Suppression d'un nœud --------------------
Arbre supprimerNoeud(Arbre racine, int v){
    if(racine == NULL) return racine;

    if(v < racine->valeur){
        racine->gauche = supprimerNoeud(racine->gauche, v);
    } else if(v > racine->valeur){
        racine->droit = supprimerNoeud(racine->droit, v);
    } else {
        // Cas 1 : pas d'enfant ou un seul enfant
        if(racine->gauche == NULL){
            Arbre temp = racine->droit;
            free(racine);
            return temp;
        } else if(racine->droit == NULL){
            Arbre temp = racine->gauche;
            free(racine);
            return temp;
        }
        // Cas 2 : deux enfants
        Arbre temp = trouverMin(racine->droit);
        racine->valeur = temp->valeur;
        racine->droit = supprimerNoeud(racine->droit, temp->valeur);
    }
    return racine;
}

// -------------------- Destruction de l'arbre --------------------
void detruireArbre(Arbre racine){
    if(racine != NULL){
        detruireArbre(racine->gauche);
        detruireArbre(racine->droit);
        free(racine);
    }
}

// -------------------- Exemple d'utilisation --------------------
int main(){
    Arbre racine = NULL;

    // Insertion des valeurs
    racine = inserer(racine, 50);
    racine = inserer(racine, 30);
    racine = inserer(racine, 70);
    racine = inserer(racine, 20);
    racine = inserer(racine, 40);
    racine = inserer(racine, 60);
    racine = inserer(racine, 80);

    printf("Parcours prefixe : ");
    visiterPrefixe(racine);
    printf("\n");

    printf("Parcours infixe : ");
    visiterInfixe(racine);
    printf("\n");

    printf("Parcours suffixe : ");
    visiterSuffixe(racine);
    printf("\n");

    printf("Hauteur de l'arbre : %d\n", hauteur(racine));
    printf("Profondeur du noeud 40 : %d\n", profondeur(racine, 40, 0));

    // Suppression d'un nœud
    racine = supprimerNoeud(racine, 70);
    printf("Parcours infixe après suppression de 70 : ");
    visiterInfixe(racine);
    printf("\n");

    detruireArbre(racine);

    return 0;
}
