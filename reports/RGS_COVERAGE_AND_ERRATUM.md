# Fixed-root RGS coverage theorem and erratum

## ERRATUM

The previous `C10_SPLIT_REDUCTION.md` assumed `C10 present => loose C10 present`. This is false because singly-chorded C10s exist. That split is withdrawn.

## Correct three-way split

For graph order <126 in the target class (simple cubic bipartite, avoiding C4,C8,C16):

1. loose C10 present -> loose pentagon root;
2. no C10 -> if also no C6, girth >=12, but cubic Moore bound gives order >=126; hence C6 exists and the triangle-root search applies, rejecting all C10;
3. C10 present but no loose C10 -> by the two-type local classification every C10 is singly chorded; root one singly-chorded pentagon and reject newly created loose C10s.

The three classes are disjoint and exhaustive.

## Fixed-root RGS coverage theorem

Fix a labeled partial linear 3-uniform root R on labels 0,...,r-1 embedded in a target symmetric V_3 configuration H. The RGS recursion repeatedly takes the least introduced incomplete point p, and generates its missing incident blocks in lexicographic order. Co-points may be existing labels >p, the next unseen label `old`, or—when both are unseen—the pair `(old,old+1)`.

Relabel the points of H outside R in order of first appearance under this point-major traversal. Then induction on the missing target blocks shows that every target block is offered by the RGS candidate rule:

- 0 unseen co-points -> its existing pair (q,r) occurs in the candidate list;
- 1 unseen -> the unseen point is exactly `old`;
- 2 unseen -> they are exactly `(old,old+1)`.

The lexicographic `last_q,last_r` condition removes only permutations of the same incident block set. After each accepted target block the `introduced` counter agrees with first-appearance relabeling, preserving the induction invariant. Thus every target containing the fixed root has an isomorphic representative branch.

This applies to both the 10-point loose root and the 9-point singly-chorded root.

Pruning by degree, repeated point-pairs, C8/C16, and branch-specific forbidden C10 type is hereditary and therefore cannot remove a valid target satisfying the branch assumptions.
