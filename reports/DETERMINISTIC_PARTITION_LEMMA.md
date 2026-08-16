# Deterministic depth-20 partition lemma

## Statement

Fix a rooted restricted-growth search, including all hereditary rejection predicates and the canonical loose-root orientation rule. Let `D` be a fixed block depth. Run the deterministic DFS from the root, but when an accepted state at block depth `D` is first reached, stop descending and assign that state the next task identifier in DFS encounter order.

Then:

1. the prefix computation together with the descendant subtrees of all listed tasks is exactly the original rooted search tree;
2. the descendant subtrees of distinct tasks are disjoint;
3. assigning task `i` to worker `i mod W` is a partition of all depth-`D` descendant work for any `W>=1`;
4. summing prefix counters once and subtree counters over all task IDs reproduces the monolithic search counters exactly.

## Proof

Every recursive edge of the search tree increases the number of accepted blocks by one. Therefore two distinct states first encountered at the same block depth `D` cannot be ancestors of one another. Their descendant subtrees are consequently disjoint.

Every monolithic DFS path either terminates or is rejected before depth `D`, in which case all its decisions are included in the prefix computation, or else it reaches a unique first state at depth `D`. In the latter case all subsequent nodes of that path lie in the descendant subtree of that unique task state. Hence prefix plus all task subtrees is exhaustive.

Task identifiers are assigned deterministically in encounter order. The congruence classes modulo `W` are a disjoint partition of the integers `0,...,T-1`, so worker assignment neither duplicates nor removes a task. Counter additivity gives the final statement. No isomorphism identification, memoization, or heuristic pruning is involved.

## Implementation controls

The verifier independently regenerates the prefix and exact task list from the fixed root. A worker certificate is accepted only for the pinned `(V,D,W,worker)` header and exact sequence of task IDs assigned to that worker. Each task stream has separately checked canonical zero padding. EOF is checked after the worker end marker.

The global aggregator requires exactly workers `0,...,W-1`, identical prefix/task metadata, the expected number of assigned tasks per congruence class, zero completions, and a SHA-256 digest for every chunk.

## Exact regression

At side `V=43`, `D=20`, `W=4`, the independent worker replays aggregate to the historical monolithic canonical-root search exactly:

- states: 2,921,354
- attempted: 591,819,668
- structural: 26,773,905
- C8: 367,498,577
- C16: 194,625,833
- accepted: 2,921,353
- canonical root prunes: 606
- completions: 0

The depth-20 task frontier has 37,494 tasks. Its largest individual subtree accounts for only about 0.755% of the historical `V=43` subtree work, compared with approximately 87.5% for the earlier shallow 86-task partition.

For side `V=49` the four theorem-candidate generators aggregate exactly to the monolithic discovery counters before independent replay:

- states: 63,836,683
- attempted: 17,853,721,756
- structural: 713,072,950
- C8: 9,828,149,705
- C16: 7,248,662,419
- accepted: 63,836,682
- canonical root prunes: 606
- completions: 0
