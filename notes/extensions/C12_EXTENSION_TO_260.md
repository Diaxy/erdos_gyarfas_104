# C12 extension of the structural decomposition

**Date:** 2026-08-11  
**Status:** PROVEN structural reduction, using the published cage lower bound `n(3,14) >= 262` (De la Cruz--Pizaña, EJC 2026).

## Theorem

Let `G` be a simple cubic bipartite graph of order at most 260 containing no C4, C8 or C16. Then `G` belongs to exactly one of the following four search classes:

1. a loose C10 is present;
2. no C10 is present and a C6 is present;
3. a C10 is present but no loose C10 is present, hence a singly-chorded C10 is present;
4. no C10 and no C6 are present; then a C12 is present, and every shortest C12 has a loose Berge-6 incidence root.

The first three classes are the corrected C10 decomposition. Class 4 extends the architecture beyond the previous order-126 barrier.

## Proof

Assume class 4: no C10 and no C6. Together with the target restrictions and bipartiteness, cycles of lengths 4,6,8,10 are absent. Suppose C12 were also absent. Then the girth is at least 14.

If the girth is exactly 14, the published cage bound `n(3,14) >= 262` gives `|V(G)| >= 262`. If the girth is larger, bipartiteness makes it even; girth 16 is excluded by the target assumption, so the next possibility is girth at least 18, whose cubic Moore bound is already `2(1+2+...+2^8)=1022`. In either case `|V(G)| >= 262`, contradicting `|V(G)| <= 260`. Hence C12 exists and, because no shorter cycle exists, the girth is exactly 12.

Take a shortest 12-cycle in the Levi graph and write its alternating point/block sequence as six cycle points and six cycle blocks. Each cycle block has one third incident point. Such a third point cannot be another nonincident cycle point: that edge is a chord of the 12-cycle and, together with one of the two cycle arcs, creates a cycle shorter than 12. Two distinct cycle blocks cannot share the same external third point either: the two edges through that point plus the shorter arc between the blocks again create a cycle shorter than 12. Thus all six third points are external and pairwise distinct. The induced incidence root is therefore a loose Berge 6-cycle on 12 points.

The four cases are disjoint and exhaustive. QED.

## Search branch

A future class-4 search may fix the root

`{0,1,6},{1,2,7},{2,3,8},{3,4,9},{4,5,10},{0,5,11}`

and apply the fixed-root RGS coverage theorem while rejecting structural violations and newly created C6, C8, C10 and C16.

Two separately written exact cycle-oracle implementations reproduce the same branch counters:

- `v=44`: states 41, attempted 8,326, structural 324, C6 2,790, C8 4,107, C10 1,017, C16 48, accepted 40, completions 0;
- `v=63` (order 126): states 91,986, attempted 40,711,525, structural 1,143,214, C6 6,363,598, C8 17,226,739, C10 15,265,077, C16 620,912, accepted 91,985, completions 0;
- `v=64` (order 128), primary exploratory branch run: states 115,843, attempted 62,891,397, structural 1,669,381, C6 10,919,134, C8 26,339,967, C10 22,883,009, C16 964,064, accepted 115,842, completions 0.

These are branch-level observations only. They do not certify the complete graph orders 126 or 128 without the other search classes.
