#include <stdio.h>
#include <stdlib.h>

/*
 *File circulaire FIFO
 *
 * Ce fichier contient l'implémentation d'une file FIFO utilisant
 * une structure circulaire. L'ajout (enqueue) et la suppression (dequeue)
 * sont garantis en temps constant O(1). 
 * Les éléments sont des blocs chaînés.
 * 
 * La complexité temporelle de chaque fonction est indiquée.
 */

// -------------------- Structures --------------------
typedef struct Bloc { 
    int valeur; 
    struct Bloc *suivant;
} Bloc; 

typedef Bloc *File;  // Pointeur vers le dernier élément de la file

// -------------------- Fonctions --------------------

/*
 * @brief Ajoute un élément à la fin de la file (enqueue)
 * @param x Valeur à insérer
 * @param F_ptr Adresse du pointeur vers le dernier élément de la file
 * Complexité : O(1)
 */
void entree(int x, File *F_ptr){
    File F = *F_ptr; 
    Bloc *N = (Bloc *)malloc(sizeof(Bloc));

    if (N == NULL){
        perror("Erreur d'allocation pour entree");
        exit(EXIT_FAILURE);
    }
    N->valeur = x; 

    if (F == NULL){
        // Cas file vide : N pointe sur lui-même
        N->suivant = N;
    } else {
        // Cas file non vide : insertion après le dernier maillon
        N->suivant = F->suivant; // N pointe sur la tête
        F->suivant = N;          // ancien dernier pointe sur N
    }
    *F_ptr = N; // N devient le nouveau dernier élément
}

/*
 * @brief Retire l'élément de la tête de la file (dequeue)
 * @param x Pointeur pour stocker la valeur retirée
 * @param F_ptr Adresse du pointeur vers le dernier élément de la file
 * Complexité : O(1)
 */
void sortie(int *x, File *F_ptr){
    File F = *F_ptr; 

    if (F == NULL){
        perror("Erreur : tentative de sortie sur une file vide.");
        exit(EXIT_FAILURE);
    }

    // Déterminer la tête
    Bloc *H = F->suivant;
    *x = H->valeur;

    if (F == H){
        // Cas : un seul élément
        *F_ptr = NULL; 
    } else {
        // Cas : plusieurs éléments, F pointe sur le nouveau premier
        F->suivant = H->suivant;
    }
    free(H);
}

/*
 * @brief Affiche tous les éléments de la file sans la modifier
 * @param F Le dernier élément de la file
 * Complexité : O(n)
 */
void afficherFile(File F){
    if (F == NULL){
        printf("File vide\n");
        return;
    }
    Bloc *courant = F->suivant; // tête
    do {
        printf("%d ", courant->valeur);
        courant = courant->suivant;
    } while (courant != F->suivant);
    printf("\n");
}

// -------------------- Main pour tester --------------------
int main(){
    File racine = NULL; 
    int valeurSortie;

    printf("Enqueue 10, 20, 30\n");
    entree(10, &racine);
    entree(20, &racine);
    entree(30, &racine);

    printf("Etat de la file : ");
    afficherFile(racine);

    sortie(&valeurSortie, &racine);
    printf("Valeur sortie : %d\n", valeurSortie);
    sortie(&valeurSortie, &racine);
    printf("Valeur sortie : %d\n", valeurSortie);

    printf("Etat final de la file : ");
    afficherFile(racine);

    // Nettoyage final
    while (racine != NULL){
        sortie(&valeurSortie, &racine);
    }

    return 0;
}
