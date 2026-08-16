# Reproduction guide

This repository accompanies the computer-assisted proof that every simple cubic bipartite graph on at most 102 vertices contains a cycle of length 4, 8, or 16.

The certified theorem used three disjoint rooted branches. The original durable checkpoint and clean-reconstruction records are in `reports/ORDER102_CERTIFIED.md` and `reports/CLEAN_REPRODUCTION_2026-08-13.md`.

## Requirements

A recent C++17 compiler is sufficient for the public C++ sources. The certified computation used Debian and GCC 14.2.0. The code uses `unsigned __int128`, so GCC or Clang is recommended.

```bash
mkdir -p build
```

## 1. No-C10 branch: direct public side-51 reproduction

`src/reproduction/no_c10_side51.cpp` is a public reconstruction of branch B from the proved RGS schedule and branch predicates. It is not relabeled as the missing historical source snapshot.

```bash
g++ -O3 -std=c++17 -DSIDE=51 \
  src/reproduction/no_c10_side51.cpp -o build/no_c10
./build/no_c10
```

Expected theorem counters:

```text
states=440620
attempted=125589272
structural=4639096
c8=45300852
c10=70099730
c16=5108976
accepted=440618
completions=0
```

This exact vector was freshly reproduced again when the public repository was prepared on 2026-08-16.

## 2. Singly-chorded / no-loose-C10 branch

A clean reconstructed direct-incidence implementation is retained as
`src/audit/chorded_no_loose_primary.cpp`.

```bash
g++ -O3 -std=c++17 -DSIDE=51 \
  src/audit/chorded_no_loose_primary.cpp -o build/chorded
./build/chorded
```

Expected theorem counters are:

```text
states=4633780
attempted=1368507421
structural=51631441
c8=428140046
loose10=627517857
c16=256584298
accepted=4633779
completions=0
```

This branch is substantially heavier than the no-C10 reproduction. The clean-reconstruction record reports an independent direct-incidence replay with these exact counters. The original theorem-producing source snapshot is identified by SHA-256 in the provenance record but is not present as an ordinary source file in the durable tree.

## 3. Loose-C10 branch: deterministic summary certificates

The retained theorem-producing sources are:

- `src/final_loose/partition_summary_gen.cpp`
- `src/final_loose/partition_summary_verify.cpp`

Build for the certified side cap and task depth:

```bash
g++ -O3 -std=c++17 -DSIDE=51 -DTASK_DEPTH=20 \
  src/final_loose/partition_summary_gen.cpp -o build/loose_gen

g++ -O3 -std=c++17 -DSIDE=51 -DTASK_DEPTH=20 \
  src/final_loose/partition_summary_verify.cpp -o build/loose_verify
```

Generate five deterministic worker certificates:

```bash
for w in 0 1 2 3 4; do
  ./build/loose_gen "$w" 5 "worker${w}.egps"
done
```

Verify every worker independently:

```bash
for w in 0 1 2 3 4; do
  ./build/loose_verify "$w" 5 "worker${w}.egps"
done
```

The aggregate certified counters are:

```text
states=195070645
attempted=59187096573
structural=2277801756
c8=31916478091
c16=24797746082
accepted=195070644
rootprune=606
completions=0
tasks=37494
```

The five durable certificate SHA-256 digests are listed in `reports/ORDER102_CERTIFIED.md` and `reports/CLEAN_REPRODUCTION_2026-08-13.md`.

## 4. Fast CI smoke checks

The GitHub Actions workflow `.github/workflows/smoke.yml` compiles every public C++ source and runs small generator/verifier round trips. These checks are deliberately much smaller than the certified side-51 computation; their role is to detect build breakage and accidental changes to the public proof code.

## 5. What the public snapshot does and does not contain

The public repository contains the final loose-C10 theorem-producing source, safe audit/control implementations, a fresh exact side-51 no-C10 reproducer, structural and coverage proofs, the certified counters, certificate hashes, and the clean-reconstruction record.

It does **not** claim that the four missing historical no-C10 / singly-chorded generator-verifier source snapshots or the original binary certificate archive have been recovered. Their exact SHA-256 identifiers and replay records are preserved in `reports/SOURCE_PROVENANCE.md` and `reports/ORDER102_CERTIFIED.md`.

No retracted partial-state isomorphism pruning, noncanonical D5 reduction, all-C10-to-loose reduction, heuristic subtree equivalence, or experimental C32 pruning is used in the theorem-producing pipeline.
