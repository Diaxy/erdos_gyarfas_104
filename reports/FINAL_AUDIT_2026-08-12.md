# Final theorem-pipeline audit — 2026-08-12

## Scope

Audit performed before the final frontier campaign.  The safe inherited theorem entering the campaign is

> every simple cubic bipartite graph on at most 96 vertices contains C4, C8, or C16,

hence a cubic-bipartite Erdős--Gyárfás counterexample has order at least 98.

The inherited order-96 claim has both a canonical-root certificate/replay and a completely no-prune loose-branch replay, so the safe inherited theorem does not depend on canonical-root pruning.

## Mathematical coverage audit

### Incidence translation
A simple cubic bipartite graph is the Levi graph of a 3-uniform 3-regular incidence structure. If C4 is absent, the incidence structure is linear. Simple incidence cycles C_(2k) are exactly Berge k-cycles.

Disconnected graphs cause no coverage issue: if a disconnected graph avoids C4,C8,C16 then each cubic component avoids them, so any counterexample has a connected counterexample component of no larger order.

### C10 two-type theorem
Rechecked directly. In a linear Berge 5-cycle B_i={p_i,p_(i+1),x_i}, x_i is either external or the unique opposite cycle point p_(i+3). Repeated external third points are excluded by linearity (adjacent positions) or a Berge 4-cycle (nonadjacent positions). Two opposite chords are excluded by linearity (distance two) or a Berge 4-cycle (adjacent positions). Hence exactly loose or singly-chorded.

Independent exhaustive local audit: all 10^5 assignments x_i in five cycle labels plus five external labels were rebuilt as Levi graphs and tested with a fresh simple-cycle DFS. Counts:

- invalid 3-set: 67,232
- nonlinear: 29,748
- linear but C8-present: 2,300
- singly-chorded C10: 600
- loose C10: 120
- OTHER: 0

### Three-way decomposition (<126)
For a C4,C8,C16-free target below order 126 exactly one case holds: A loose C10 exists; B no C10 exists; C C10 exists but no loose C10 exists. Case C has a singly-chorded root by the two-type theorem. In B, absence of C6 as well would give girth at least 12, and the cubic Moore bound is 126, contradiction. Thus B has a triangle root. The three cases are disjoint and exhaustive.

### Triangle-root first-block orbits
For the normalized Berge triangle, the least unfinished cycle point 0 has available co-points {4,new,new}; restricted growth leaves exactly {0,4,6} and {0,6,7}. Thus the two triangle-root first-block orbits are complete.

### Fixed-root RGS coverage
Reproved by first-appearance relabeling of non-root points. At the least unfinished point, a target block has 0,1,2 unseen co-points, corresponding exactly to existing-existing, existing-old, old-(old+1). Lexicographic incident-block ordering removes only block-order permutations.

Fresh non-vacuous independent comparisons:

Loose root:
- v=10: RGS 88, generic fixed-label 88, exact sets equal.
- v=11: RGS 2,930, generic fixed-label 2,930, exact sets equal.

Singly-chorded root:
- v=9: 3/3 rooted-isomorphism classes.
- v=10: 107/107 classes.
- v=11: raw RGS 1,069 vs generic fixed-label 1,850 because of the two external labels; after canonicalization under their permutations both give exactly 925 classes, element-for-element equal.

## Canonical loose-root orientation audit

The reduction is applied only after all five loose-cycle vertices have acquired their third incidence. For each of the 10 D5 orientations, a label-free key is computed. External points are encoded by their 5-bit incidence pattern among the five completion slots (codes 1..31); root points are encoded as 32 plus transformed root label. The identity orientation is retained iff its key is lexicographically minimal (ties retained).

Fresh boundary enumeration, independently rebuilt:
- admissible boundary states: 692
- retained: 86
- pruned: 606
- minimum multiplicities: 588x1, 101x2, 3x10

Fresh full regressions:
- v=38: states 258,325; attempted 38,184,311; structural 1,902,332; C8 27,885,137; C16 8,138,518; accepted 258,324; root prunes 606; completions 0.
- v=43 generator: exact historical counters states 2,921,354; attempted 591,819,668; structural 26,773,905; C8 367,498,577; C16 194,625,833; accepted 2,921,353; root prunes 606; completions 0.
- v=43 independent replay: ACCEPT with the same counters.

The completeness argument uses only choice of orientation of the same loose root before first-appearance relabeling; it does not identify distinct partial RGS continuation states.

## Cycle-oracle audit

Generator:
- structural check enforces degree <=3 and linearity;
- C8 uses the linear pair-block characterization of a three-old-block Berge path between two points of the candidate block;
- C16 uses a simple 7-old-block Berge-path DFS, cached only within one unchanged parent state.

Verifier:
- C8 uses exact simple incidence-path length 6;
- C16 uses meet-in-the-middle exact incidence paths of length 14;
- per-state caches are discarded before child recursion.

Fresh v=38 full-stream generator/verifier agreement:
- 38,184,311 candidate decisions under canonical-root pruning;
- verifier ACCEPT.

Cross-compiler regression: GCC and Clang generate byte-identical v=38 certificates. ASan+UBSan v=38 run: same counters/hash, zero diagnostics.

## Compact certificate audit

Two bits per deterministic candidate outcome: structural/C8/C16/accepted. Header pins magic/version/side. Verifier reconstructs all candidate order, checks every outcome, then canonical zero padding and EOF.

Fresh malformed-certificate controls at v=38:
- outcome corruption: rejected at candidate 0;
- truncation: rejected;
- trailing byte: rejected;
- nonzero unused padding bit: rejected.

## Explicitly excluded / retracted components

None of the following are used by the theorem-producing pipeline:

- RETRACTED all-C10 -> loose-C10 normalization;
- RETRACTED D5 boundary-signature pruning with noncanonical external renaming;
- RETRACTED partial-incidence-isomorphism memoization (continuation-equivalence fails);
- any heuristic subtree equivalence;
- experimental C32 pruning.

Canonical-root orientation is a different, narrower reduction: it chooses an orientation of one fixed loose root and has fresh exact regressions plus independent replay.

## Side 49 / order 98 audit status

No-C10 was freshly reconstructed with two different cycle-oracle architectures and both give exactly states 183,942; attempted 45,874,608; structural 1,721,548; C8 13,691,966; C10 28,607,894; C16 1,669,260; accepted 183,940; completions 0. Fresh certificates and independent replays ACCEPT both triangle-root orbits.

Singly-chorded/no-loose was freshly reconstructed with two independent loose-C10 detectors; both agree on states 2,036,390; attempted 552,366,143; structural 21,724,033; C8 184,010,104; loose-C10 253,470,247; C16 91,125,370; accepted 2,036,389; completions 0.

Loose-C10 final order-98 computation is treated separately and remains non-theorem until a complete independent replay is accepted.

## Status after audit

No new mathematical or implementation completeness defect has been found. The safe lower bound remains 98 until the final order-98 loose proof is independently accepted.
