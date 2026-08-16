# C14 extension of the structural root hierarchy

**Date:** 2026-08-11  
**Status:** PROVEN structural reduction; branch-level computations independently cross-checked. This does not assert a computational frontier near order 1020.

## Theorem

Let `G` be a simple cubic bipartite graph of order at most 1020 containing no C4, C8 or C16. In the branch in which C6, C10 and C12 are also absent, `G` must contain C14. Any such C14 is a shortest cycle and induces a loose Berge-7 root in the associated linear symmetric 3-uniform incidence structure.

Consequently the structural search architecture through order 1020 may be decomposed into the following disjoint cases:

1. loose C10 present;
2. no C10 and C6 present;
3. C10 present but no loose C10, hence singly-chorded C10;
4. no C10, no C6, but C12 present, hence a loose Berge-6 root;
5. no C10, no C6, no C12; then C14 is forced and gives a loose Berge-7 root.

## Proof

Assume C6, C10 and C12 are absent. Together with bipartiteness and the target restrictions, cycles of lengths 4,6,8,10,12 and 16 are absent. If C14 were also absent, every cycle would have length at least 18. The cubic Moore bound for even girth 18 is

`2(1 + 2 + 4 + 8 + 16 + 32 + 64 + 128 + 256) = 1022`.

Thus a cubic graph of girth at least 18 has at least 1022 vertices, contradicting `|V(G)| <= 1020`. Hence C14 exists.

Since every smaller even cycle length is absent, this C14 is a shortest cycle. In a cubic graph a chord of a shortest cycle creates a shorter cycle. In the incidence formulation, a cycle block whose third point is another nonincident cycle point is such a chord; two cycle blocks sharing the same external third point likewise create a shorter cycle through that point. Therefore the seven third points are external and pairwise distinct, yielding the loose Berge-7 root.

QED.

## Exact branch module

A fixed root is

`{0,1,7},{1,2,8},{2,3,9},{3,4,10},{4,5,11},{5,6,12},{0,6,13}`.

The branch rejects structural violations and newly created C6, C8, C10, C12 and C16. Two separately written exact cycle-oracle implementations agree at `v=64`:

`states=82 attempted=23935 structural=786 c6=3904 c8=10126 c10=8596 c12=442 c16=0 accepted=81 completions=0`.

The primary implementation runs in about 0.007 s at v=64; the independent implementation gives the same counters in about 0.009 s.

At v=45 the primary branch has only

`states=16 attempted=2473 structural=113 c6=1137 c8=962 c10=224 c12=22 c16=0 accepted=15 completions=0`.

These are branch-level observations, not full-order theorem claims.

## Perspective

The same shortest-cycle/Moore principle can be continued with longer non-power-of-two girth roots, but additional branches are useful only if the computational frontier approaches the relevant structural threshold. The C14 module is recorded because it removes the next natural barrier after the C12 extension while remaining extremely small computationally.
