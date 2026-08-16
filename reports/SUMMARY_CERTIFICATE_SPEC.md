# Deterministic subtree-summary certificate

## Purpose

The earlier partition certificate serialized two bits for every candidate outcome. This is useful for direct generator/verifier stream comparison but grows linearly with the number of candidate extensions (several GB at side 49).

The summary format keeps the same deterministic depth-20 task partition and the same exhaustive independent replay, but stores one exact counter record per assigned task instead of one outcome record per candidate.

## Worker certificate

Header pins magic `EGPS`, format version, side `V`, task depth `D`, total worker count `W`, and worker index.

For each task assigned to the worker, in deterministic task-ID order, the generator stores task ID and exact subtree counts: states, attempted candidate extensions, structural rejects, C8 rejects, C16 rejects, accepted children, and completions. The file ends with one end marker and canonical EOF. There is no bit padding in this format.

## Independent verification

The verifier does not trust the stored subtree counters. It independently regenerates the canonical-root prefix and deterministic task list. For every task assigned to its worker it independently searches the complete subtree with the verifier's cycle oracles (exact incidence-path C8 and MITM C16), recomputes all counters, and compares the resulting record exactly with the certificate. It rejects any task-ID, counter, header, truncation, or trailing-data mismatch and any nonzero completion count.

Thus every candidate decision is still recomputed by the verifier. The certificate merely records compact per-subtree commitments rather than the full discovery outcome stream.

## Global coverage

The global aggregator requires exactly workers `0,...,W-1`, identical prefix/task metadata, exact congruence-class task counts, zero completions, and SHA-256 for each worker certificate. Prefix counters are added once and subtree counters over all workers once.

## Exact validation

Side 38, W=4: four independent replays aggregate exactly to `states=258325 attempted=38184311 structural=1902332 c8=27885137 c16=8138518 accepted=258324 rootprune=606 completions=0`; worker certificates are about 595 KiB.

Side 43, W=4: aggregate exactly `states=2921354 attempted=591819668 structural=26773905 c8=367498577 c16=194625833 accepted=2921353 rootprune=606 completions=0`; each worker certificate is about 609 KiB.

Side 43, W=5: five independently replayed worker certificates aggregate to the same exact monolithic counters; each certificate is about 477 KiB.

## Negative controls

Validated at side 38: wrong task ID rejected; altered subtree counter rejected after independent subtree replay; truncation rejected; trailing data rejected; missing worker chunk rejected by global aggregator; duplicate worker chunk rejected by global aggregator.

This format changes only proof serialization, not search-space coverage or pruning.
