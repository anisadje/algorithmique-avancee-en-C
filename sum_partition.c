#include <stdio.h>
#include <stdlib.h>

/*
 * Lists of integers with a given sum (graded lab "PPQ")
 *
 * Generates every list of integers taken in [p1, p2] whose sum is q.
 * A list is a linked list (Block), and a set of lists is a linked
 * list of lists (BlockList).
 *
 * The time complexity of each function is given.
 */

// -------------------- Structures --------------------
typedef struct Block {
    int value;
    struct Block *next;
} *Block;

typedef struct BlockList {
    Block solution;
    struct BlockList *next;
} *BlockList;

// -------------------- Functions on Block --------------------

/*
 * @brief Adds an integer at the head of a list
 * @param element The value to add
 * @param B The head of the existing list
 * @return Block The new head of the list
 * Complexity: O(1)
 */
Block AddToHead(int element, Block B){
    Block new_block = (Block)malloc(sizeof(*new_block));
    if (new_block == NULL) {
        perror("Allocation error in AddToHead");
        exit(EXIT_FAILURE);
    }
    new_block->value = element;
    new_block->next = B;
    return new_block;
}

/*
 * @brief Returns a copy of a list
 * @param B The head of the list to copy
 * @return Block The head of the copy
 * Complexity: O(n) where n is the length of the list
 */
Block CopyBlock(Block B){
    if (B == NULL) return NULL;
    return AddToHead(B->value, CopyBlock(B->next));
}

/*
 * @brief Frees every cell of one list
 * @param B The head of the list
 * Complexity: O(n) where n is the length of the list
 */
void FreeBlock(Block B){
    Block current = B;
    Block next_tmp;
    while (current != NULL){
        next_tmp = current->next;
        free(current);
        current = next_tmp;
    }
}

// -------------------- Functions on BlockList --------------------

/*
 * @brief Concatenates two lists of lists
 * @param B1 First list
 * @param B2 Second list
 * @return BlockList The head of the concatenated list
 * Complexity: O(n) where n is the length of B1
 */
BlockList Concatenate(BlockList B1, BlockList B2){
    if (B1 == NULL) return B2;
    if (B2 == NULL) return B1;

    BlockList current = B1;
    while (current->next != NULL){
        current = current->next;
    }
    current->next = B2;
    return B1;
}

/*
 * @brief Creates a new BlockList cell
 * @param B The solution to store
 * @param next The next cell
 * @return BlockList The new cell
 * Complexity: O(1)
 */
BlockList NewBlockList(Block B, BlockList next){
    BlockList new_cell = (BlockList)malloc(sizeof(*new_cell));
    if (new_cell == NULL) {
        perror("Allocation error in NewBlockList");
        exit(EXIT_FAILURE);
    }
    new_cell->solution = B;
    new_cell->next = next;
    return new_cell;
}

/*
 * @brief Frees a whole list of lists
 * @param BB The head of the list of lists
 * Complexity: O(n*m) where n = length of BB, m = average length of the lists
 */
void FreeBlockList(BlockList BB){
    BlockList current = BB;
    BlockList next_tmp;
    while (current != NULL){
        next_tmp = current->next;
        FreeBlock(current->solution);
        free(current);
        current = next_tmp;
    }
}

// -------------------- PPQ: every list whose sum is q --------------------

/*
 * @brief Generates every list of integers in [p1, p2] whose sum is q
 * @param p1 Lower bound (must be > 0)
 * @param p2 Upper bound
 * @param q Target sum
 * @return BlockList The list of all the solutions
 * Complexity: exponential, O((p2-p1+1)^q) in the worst case
 */
BlockList PPQ(int p1, int p2, int q){
    if (q == 0) return NewBlockList(NULL, NULL); // the empty solution
    if (q < p1) return NULL; // impossible

    BlockList result = NULL;

    for (int i = p1; i <= p2; i++){
        int remaining = q - i;
        if (remaining >= 0){
            BlockList partial = PPQ(p1, p2, remaining);
            if (partial != NULL){
                BlockList prefixed = NULL;
                BlockList current = partial;

                while (current != NULL){
                    // the partial solutions are freed below, so we prepend i to a copy
                    Block new_list = AddToHead(i, CopyBlock(current->solution));
                    BlockList new_cell = NewBlockList(new_list, NULL);
                    prefixed = Concatenate(prefixed, new_cell);
                    current = current->next;
                }

                result = Concatenate(result, prefixed);
                FreeBlockList(partial);
            }
        }
    }
    return result;
}

// -------------------- Printing --------------------
void PrintBlock(Block B){
    printf("[");
    while (B != NULL){
        printf("%d", B->value);
        B = B->next;
        if (B != NULL) printf(", ");
    }
    printf("]");
}

void PrintBlockList(BlockList BB){
    while (BB != NULL){
        PrintBlock(BB->solution);
        printf(" ");
        BB = BB->next;
    }
    printf("\n");
}

// -------------------- Example --------------------
int main() {
    int p1 = 2, p2 = 4, q = 9;

    BlockList result = PPQ(p1, p2, q);

    printf("Solutions for p1=%d, p2=%d, q=%d:\n", p1, p2, q);
    PrintBlockList(result);

    FreeBlockList(result);

    return 0;
}
