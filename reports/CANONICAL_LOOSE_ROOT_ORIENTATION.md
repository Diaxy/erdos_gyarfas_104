# Canonical loose-root orientation

## Scope

The loose-C10 branch fixes the rooted Berge 5-cycle

`{0,1,5}, {1,2,6}, {2,3,7}, {3,4,8}, {0,4,9}`

and applies one symmetry reduction when all five cycle points `0,...,4` have acquired their third incidence. The rule chooses an orientation of this same embedded loose root; it does **not** identify arbitrary partial RGS states.

## Label-free score

For each of the ten dihedral orientations of the loose pentagon, the five cycle points and the five root-private points are transformed by the corresponding root automorphism. A non-root point occurring in the five completion blocks is encoded by its five-bit incidence pattern among those completion slots, rather than by its RGS label.

For each transformed cycle anchor, encode and sort the two non-anchor entries of its completion block. Root points are represented by transformed root labels and non-root points by their incidence patterns. Concatenating the five pairs gives a ten-entry orientation key.

The state is retained exactly when the identity orientation has lexicographically minimum key; ties are retained.

## Coverage

Let a complete target in the loose-C10 branch contain a chosen loose root. Among the ten orientations of that root choose one whose label-free key is minimum, orient the root accordingly, and then apply the usual first-appearance relabeling of all non-root points used in the fixed-root RGS coverage theorem.

The key depends on non-root points only through their incidence patterns among the five completion slots, so first-appearance relabeling does not change it. Therefore the RGS representative of the oriented target reaches a boundary state for which the identity orientation is minimum and survives the symmetry rule. Subsequent degree, linearity, C8, and C16 tests are invariant under the root orientation.

The final theorem-producing code calls the orientation test at the first boundary with all five cycle points complete. In a state that has survived the preceding structural and C8 tests, the five completion incidences cannot collapse in a way that invalidates the key: a block containing two adjacent cycle points would repeat an already used pair and violate linearity, while a block containing two nonadjacent cycle points closes the corresponding Berge 4-cycle and is rejected as C8. Thus the admissible canonical boundary is precisely the distinct-completion-block regime used in the coverage argument.

Hence every valid loose-rooted target retains at least one RGS representative.

## Independent audits

The complete admissible boundary enumeration contains:

- 692 boundary states;
- 86 retained states;
- 606 pruned states.

The number of minimizing dihedral orientations is:

- 1 for 588 states;
- 2 for 101 states;
- 10 for 3 states.

Non-vacuous full-completion comparisons also preserve every rooted isomorphism class:

- side 11: 305 / 305 classes retained;
- side 12: 5,469 / 5,469 classes retained.

At side 38, the canonical-root generator and separately implemented verifier agree on all 38,184,311 candidate decisions and on the final counters. At side 43, the independent replay likewise reproduces the historical canonical-root counters exactly.

## Excluded earlier ideas

This rule is not the earlier retracted D5 boundary signature with greedy external relabeling, and it is not partial-incidence-isomorphism memoization. Those mechanisms are not used by the theorem-producing pipeline.
