# Advanced Algorithms in C

All the code written for the **Advanced Algorithms in C** course (Université Paris-Saclay): tutorials, graded labs and exam exercises, focused on dynamic data structures, binary trees, and recursive and iterative algorithms.

---

## Contents

### TD0 – Binary search tree basics
- Creating nodes, insertion and search in a BST
- Preorder, inorder and postorder traversals
- Height and depth of a node
- Deleting a node and destroying a tree
- **Goal:** master the basics needed for the rest of the course.

### TD1 – Binary tree exercises
- Creating nodes, height, mirror of a tree (new tree or in place)
- **Iterative** preorder traversal with a hand-made stack
- Counting nodes with given properties, checking whether a tree is full
- **Goal:** get comfortable with recursion and pointers on trees.

### PPQ – Graded lab: lists with a given sum
- Recursively generates every list of integers in `[p1, p2]` whose sum is `q`
- Linked lists (`Block`) and lists of lists (`BlockList`)
- Intermediate solutions are freed as soon as they are no longer needed
- **Goal:** advanced recursion and memory management on nested lists.

### TER – Graded lab: circular FIFO queue
- A FIFO queue stored as a **circular linked list**, accessed through its last element
- `enqueue` (add at the end) and `dequeue` (remove at the head), both in **O(1)**
- **Goal:** pointer handling and circular structures.

### Exams
Typical exam functions (2023-2024 and 2024-2025):
- Counting nodes with given properties (internal nodes at a given depth or height, cherries, leaf grandchildren…)
- Checking BSTs and height-balanced ("Fibonacci-type") trees, in O(n²) and O(n) versions
- Simplifying and transforming trees

---

## Files

| File | Content |
|------|---------|
| `td0_bst_basics.c` | BST basics: insertion, search, traversals, deletion |
| `td1_binary_trees.c` | Binary tree exercises, iterative traversal with a stack |
| `sum_partitions.c` | Graded lab PPQ: every list in `[p1, p2]` with sum `q` |
| `circular_queue.c` | Graded lab TER: circular FIFO queue in O(1) |
| `exam_2023_2024.c` | Exam 2023-2024 |
| `exam_2024_2025.c` | Exam 2024-2025 |

---

## Notes
- Every function comes with its time complexity.
- Each file is independent, with its own `main` for testing.
- All dynamic memory is freed (checked with AddressSanitizer).

---

## Build
Each file compiles on its own:

```bash
gcc -Wall -Wextra -o program file.c
./program
```

To check memory errors and leaks:

```bash
gcc -g -fsanitize=address,undefined -o program file.c
./program
```
