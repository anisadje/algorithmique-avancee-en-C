#include <stdio.h>
#include <stdlib.h>

/*
 * Portfolio GitHub - Listes et PPQ
 *
 * Ce fichier contient le code pour générer toutes les listes d'entiers
 * dans un intervalle [p1, p2] dont la somme vaut q. 
 * Les listes sont représentées par des structures chaînées (Bloc), 
 * et les ensembles de listes par BlocDeBlocs.
 *
 * Chaque fonction est commentée et la complexité est indiquée.
 */

// -------------------- Structures --------------------
typedef struct Bloc {
    int valeur;
    struct Bloc *suivant;
} *Bloc;

typedef struct BlocDeBlocs {
    Bloc solution; 
    struct BlocDeBlocs *suivant; 
} *BlocDeBlocs;

// -------------------- Fonctions sur Bloc --------------------

/*
 * @brief Ajoute un entier en tête d'une liste (Bloc)
 * @param element La valeur entière à ajouter
 * @param B La tête de la liste existante
 * @return Bloc La nouvelle tête de la liste
 * Complexité : O(1)
 */
Bloc AjouterEnTete(int element, Bloc B){
    Bloc nouveau_bloc = (Bloc)malloc(sizeof(*nouveau_bloc));
    if (nouveau_bloc == NULL) {
        perror("Erreur d'allocation dans AjouterEnTete");
        exit(EXIT_FAILURE);
    }
    nouveau_bloc->valeur = element; 
    nouveau_bloc->suivant = B; 
    return nouveau_bloc;
}

/*
 * @brief Libère tous les maillons d'une seule liste d'entiers (Bloc)
 * @param B La tête de la liste
 * Complexité : O(n) où n est la longueur de la liste
 */
void LibererBloc(Bloc B){
    Bloc courant = B;
    Bloc suivant_temp; 
    while (courant != NULL){
        suivant_temp = courant->suivant; 
        free(courant);
        courant = suivant_temp;
    }
}

// -------------------- Fonctions sur BlocDeBlocs --------------------

/*
 * @brief Concatène deux listes de BlocDeBlocs
 * @param B1 Première liste
 * @param B2 Deuxième liste
 * @return BlocDeBlocs La tête de la liste concaténée
 * Complexité : O(n) où n = longueur de B1
 */
BlocDeBlocs Concatener(BlocDeBlocs B1, BlocDeBlocs B2){
    if (B1 == NULL) return B2; 
    if (B2 == NULL) return B1; 

    BlocDeBlocs courant = B1;
    while (courant->suivant != NULL){
        courant = courant->suivant;
    }
    courant->suivant = B2; 
    return B1;
}

/*
 * @brief Crée un nouveau maillon de type BlocDeBlocs
 * @param B La solution à stocker
 * @param suivant Le BlocDeBlocs suivant
 * @return BlocDeBlocs Nouveau maillon alloué
 * Complexité : O(1)
 */
BlocDeBlocs CreerBlocDeBlocs(Bloc B, BlocDeBlocs suivant){
    BlocDeBlocs nv_maillon = (BlocDeBlocs)malloc(sizeof(*nv_maillon));
    if (nv_maillon == NULL) {
        perror("Erreur d'allocation mémoire pour CreerBlocDeBlocs");
        exit(EXIT_FAILURE);
    }
    nv_maillon->solution = B; 
    nv_maillon->suivant = suivant;
    return nv_maillon;
}

/*
 * @brief Libère l'intégralité d'une liste de BlocDeBlocs
 * @param BB La tête de la liste de BlocDeBlocs
 * Complexité : O(n*m) où n = longueur de BB, m = longueur moyenne des Blocs
 */
void LibererBlocDeBlocs(BlocDeBlocs BB){
    BlocDeBlocs courant = BB; 
    BlocDeBlocs suivant_temp; 
    while (courant != NULL){
        suivant_temp = courant->suivant; 
        LibererBloc(courant->solution);
        free(courant); 
        courant = suivant_temp;
    }
}

// -------------------- PPQ : liste de listes dont la somme vaut q --------------------

/*
 * @brief Génère toutes les listes d'entiers dans [p1, p2] dont la somme vaut q
 * @param p1 Borne inférieure
 * @param p2 Borne supérieure
 * @param q Somme cible
 * @return BlocDeBlocs La liste de toutes les solutions
 * Complexité : Exponentielle O((p2-p1+1)^q) dans le pire cas
 */
BlocDeBlocs PPQ(int p1, int p2, int q){
    if (q == 0) return CreerBlocDeBlocs(NULL, NULL); // solution vide
    if (q < p1) return NULL; // impossible

    BlocDeBlocs resultat = NULL;

    for (int i = p1; i <= p2; i++){
        int q_restant = q - i;
        if (q_restant >= 0){
            BlocDeBlocs solutionsIntermediaires = PPQ(p1, p2, q_restant); 
            if (solutionsIntermediaires != NULL){
                BlocDeBlocs solutionsPrefixees = NULL; 
                BlocDeBlocs courant_intermediaire = solutionsIntermediaires;

                while (courant_intermediaire != NULL){
                    Bloc NouvelleListe = AjouterEnTete(i, courant_intermediaire->solution);
                    BlocDeBlocs NouveauMaillon = CreerBlocDeBlocs(NouvelleListe, NULL); 
                    solutionsPrefixees = Concatener(solutionsPrefixees, NouveauMaillon); 
                    courant_intermediaire = courant_intermediaire->suivant;
                }

                resultat = Concatener(resultat, solutionsPrefixees);
                LibererBlocDeBlocs(solutionsIntermediaires);
            }
        }
    }
    return resultat; 
}

// -------------------- Affichage --------------------
void AfficherBloc(Bloc B){
    printf("[");
    while (B != NULL){
        printf("%d", B->valeur);
        B = B->suivant;
        if (B != NULL) printf(", ");
    }
    printf("]");
}

void AfficherBlocDeBlocs(BlocDeBlocs BB){
    while (BB != NULL){
        AfficherBloc(BB->solution);
        printf(" ");
        BB = BB->suivant;
    }
    printf("\n");
}

// -------------------- Exemple de main --------------------
int main() {
    int p1 = 2, p2 = 4, q = 9;

    BlocDeBlocs resultat = PPQ(p1, p2, q); 

    printf("Solutions pour p1=%d, p2=%d, q=%d:\n", p1, p2, q);
    AfficherBlocDeBlocs(resultat); 

    LibererBlocDeBlocs(resultat);

    return 0;
}
