# erdos_gyarfas_104

Computer-assisted lower bound for simple cubic bipartite counterexamples to the Erdős–Gyárfás conjecture.

## Main result

Every simple cubic bipartite graph on at most **102 vertices** contains a cycle of length **4, 8, or 16**. Consequently, any simple cubic bipartite counterexample to the Erdős–Gyárfás conjecture has order at least

\[
|V(G)| \ge 104.
\]

Status: **computer-assisted / computationally verified**.

The order-102 computation was certified on 2026-08-12 and independently reconstructed after a runtime reset on 2026-08-13.

## Repository layout

- `paper/` — preprint artifact/hash record; the generated PDF is intended for the public release/arXiv deposit.
- `src/final_loose/` — theorem-producing loose-C10 partition generator and independently implemented summary verifier.
- `src/audit/` — exact audit/control programs used to validate the RGS search, cycle oracles, fixed roots, and compact certificates.
- `reports/` — theorem, audit, coverage, partition, certificate, clean-reproduction, and source-provenance records.
- `notes/extensions/` — proved structural extensions beyond the order-104 theorem; branch-level computations there are not additional certified lower-bound claims.

## Order-102 aggregate

The three exhaustive branches are:

1. a loose C10 is present;
2. no C10 is present (hence, below order 126, a C6 root is forced);
3. a C10 is present but no loose C10 is present (hence a singly-chorded C10 root).

All three branches have zero completions at side cap 51 (graph order 102).

The dominant loose-C10 branch contains 59,187,096,573 candidate decisions and was split deterministically into 37,494 depth-20 tasks. Five summary certificates were independently replayed with exact incidence-path C8 tests and meet-in-the-middle C16 tests.

See `reports/ORDER102_CERTIFIED.md` and `reports/CLEAN_REPRODUCTION_2026-08-13.md` for exact counters and SHA-256 values.

## Reproducibility note

This repository is a curated publication snapshot from the research branch `mathresearch/eg-cubic-bipartite-20260810` of `Diaxy/ChatGPT_Private` (durable project head `fb2f63d12ccc3de11447d69e7965f2fd3ee1e7d0`).

The final loose-C10 generator/verifier sources are included directly. Audit/control sources included here are the safe versions retained by the final theorem-pipeline audit. Historical experimental reductions explicitly marked retracted in the audit are intentionally omitted from the public `src/` tree.

The durable order-102 report also records SHA-256 hashes for the theorem-producing no-C10 and singly-chorded generator/verifier snapshots. The corresponding exact historical source files and full binary certificate archives are not included in this initial GitHub snapshot; their hashes and replay results are preserved in the reports. See `reports/SOURCE_PROVENANCE.md` for the precise release boundary.

## Compiler environment used for the certified run

- Debian
- `g++ 14.2.0`
- AMD EPYC 9V74 allocation
- 4-core cgroup CPU quota
- 4 GiB memory limit

## Citation

Please cite the accompanying preprint once the arXiv identifier is available.
