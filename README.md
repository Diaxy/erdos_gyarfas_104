# erdos_gyarfas_104

[![reproducibility-smoke](https://github.com/Diaxy/erdos_gyarfas_104/actions/workflows/smoke.yml/badge.svg)](https://github.com/Diaxy/erdos_gyarfas_104/actions/workflows/smoke.yml)

Computer-assisted lower bound for simple cubic bipartite counterexamples to the Erdős–Gyárfás conjecture.

## Main result

Every simple cubic bipartite graph on at most **102 vertices** contains a cycle of length **4, 8, or 16**. Consequently, any simple cubic bipartite counterexample to the Erdős–Gyárfás conjecture has order at least

\[
|V(G)| \ge 104.
\]

Status: **computer-assisted / computationally verified**.

The order-102 computation was certified on 2026-08-12 and independently reconstructed after a runtime reset on 2026-08-13.

## Repository layout

- `REPRODUCE.md` — build and reproduction instructions, expected counters, and the exact boundary of the public snapshot.
- `paper/` — manuscript artifact/hash record. Manuscript sources/PDFs are release/arXiv artifacts rather than theorem-producing code.
- `src/final_loose/` — retained theorem-producing loose-C10 partition generator and independently implemented summary verifier.
- `src/reproduction/` — public reconstruction programs used to reproduce certified branch counters without pretending to be missing historical source snapshots.
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

The full certified search accounts for **60,681,193,266 candidate extensions** across the three branches and produces zero completions.

See `reports/ORDER102_CERTIFIED.md`, `reports/CLEAN_REPRODUCTION_2026-08-13.md`, and `REPRODUCE.md` for exact counters, hashes, and reproduction commands.

## Public reproduction status

The final loose-C10 generator/verifier sources are included directly.

For the no-C10 branch, `src/reproduction/no_c10_side51.cpp` is a public reconstruction of the proved RGS schedule and branch predicates. During the final publication sanity pass on 2026-08-16 it freshly reproduced the certified side-51 vector exactly:

```text
states=440620 attempted=125589272 structural=4639096
c8=45300852 c10=70099730 c16=5108976
accepted=440618 completions=0
```

A clean reconstructed implementation of the singly-chorded/no-loose branch is retained in `src/audit/chorded_no_loose_primary.cpp`; the clean-reconstruction report records its exact side-51 replay.

The durable order-102 report also records SHA-256 hashes for the original theorem-producing no-C10 and singly-chorded generator/verifier snapshots. Those four exact historical source files and the original full binary certificate archive are not claimed to have been recovered. Their hashes and replay results remain preserved in the reports. See `reports/SOURCE_PROVENANCE.md` for the precise release boundary.

Historical experimental reductions explicitly marked retracted in the audit are intentionally omitted from the public theorem-producing source tree.

## Compiler environment used for the certified run

- Debian
- `g++ 14.2.0`
- AMD EPYC 9V74 allocation
- 4-core cgroup CPU quota
- 4 GiB memory limit

The public GitHub Actions smoke workflow compiles every included C++ source and performs small end-to-end generator/verifier checks. It is a build-integrity check, not a substitute for the full side-51 computation.

## Citation

Please cite the accompanying preprint once the arXiv identifier is available.
