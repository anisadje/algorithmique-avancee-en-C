# ALGORITHMIQUE AVANCÉE EN C

Ce dépôt contient l’ensemble des codes réalisés dans le cadre du cours **Algorithmique Avancée en C**. Il regroupe les travaux dirigés, travaux pratiques et exercices d’examen, avec un accent sur la manipulation de structures dynamiques, les arbres binaires et les algorithmes récursifs et itératifs.

---

## Contenu du dépôt

### TD0 – Notions de base
- **Description** : Introduction aux concepts fondamentaux en C :
  - Déclaration et manipulation de structures (`struct`)
  - Allocation dynamique (`malloc`, `free`)
  - Parcours récursif et itératif de structures simples
- **Objectif** : Maîtriser les bases nécessaires pour les TD suivants et TP.

### TD1 – Exercices sur les arbres binaires
- **Description** : Exercices issus du TD du professeur sur les arbres binaires :
  - Création, insertion et recherche de nœuds
  - Parcours préfixe, infixe et suffixe (récursif et itératif)
  - Suppression de nœuds et destruction d’arbres
  - Calcul de hauteur et de profondeur
- **Complexité** : Chaque fonction est annotée avec sa complexité temporelle.
- **Objectif** : Comprendre et manipuler efficacement les arbres binaires.

### PPQ – TP noté : Partition de la somme
- **Description** : Génération récursive de toutes les listes d’entiers dont la somme vaut `q`.
  - Gestion de la mémoire avec libération automatique des solutions intermédiaires.
  - Utilisation de listes chaînées (`Bloc`) et de listes de listes (`BlocDeBlocs`).
- **Objectif** : Apprendre la récursion avancée et la manipulation dynamique de listes complexes.

### TER – TP noté : File FIFO circulaire
- **Description** : Implémentation d’une **file FIFO circulaire** en C.
  - Fonctions principales : `entree` (ajout en fin) et `sortie` (suppression en tête).
  - Optimisation en **O(1)** pour l’insertion et la suppression.
- **Objectif** : Comprendre la gestion des files circulaires et des pointeurs en C.

### Examens
- **Description** : Fonctions types pour les examens 2023-2024 et 2024-2025 :
  - Comptage de nœuds selon différentes propriétés (`sans ascendants`, `sans descendants`, `hauteur = profondeur`, etc.)
  - Vérification de l’état complet ou miroir des arbres
  - Parcours préfixe itératif et récursif
  - Vérification d’arbres de type Fibonacci
- **Objectif** : Préparer les exercices d’examen en maîtrisant les structures d’arbres et les algorithmes associés.

---

## Organisation des fichiers

| Fichier | Contenu |
|---------|---------|
| `TD0.c` | Codes de base, structures et fonctions simples |
| `TD1.c` | Exercices sur les arbres binaires du TD du professeur |
| `PPQ.c` | Exercice TP noté : génération de partitions de somme |
| `TER.c` | Exercice TP noté : implémentation de la file FIFO circulaire |
| `Examens.c` | Codes types pour préparer les examens (2023-2025) |

---

## Notes
- Toutes les fonctions sont documentées avec un **`@brief`** et leur complexité.
- La mémoire dynamique est toujours libérée pour éviter les fuites.
- Les fichiers sont indépendants et peuvent être compilés séparément.
- Les parcours d’arbres sont proposés en versions **récursive** et **itérative**.

---

## Compilation
Pour compiler chaque fichier C, utilisez :

```bash
gcc -o nom_du_programme fichier.c
./nom_du_programme
