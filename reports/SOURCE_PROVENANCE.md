# Source provenance

This public repository is a curated publication snapshot of the Erdős–Gyárfás cubic-bipartite project originally developed on the private branch

`Diaxy/ChatGPT_Private:mathresearch/eg-cubic-bipartite-20260810`.

The durable project head used when preparing this snapshot is

`fb2f63d12ccc3de11447d69e7965f2fd3ee1e7d0`

(`Add clean reproduction of certified Erdős–Gyárfás order 102`, 2026-08-13).

## Theorem-producing checkpoint history

- order-98 checkpoint: `f7c53812345dcae362afc09d3a44158ffdae40d5`
- summary-certificate specification: `8a88e6ff33137caa21e27cb248110a312191218d`
- depth-partition summary generator source: `3834485ec2d1699aee1365e1906eb9c56a96da0f`
- order-100 checkpoint: `cac483cf3c5b3d1a2012f648434c25efadaee8b8`
- order-102 certified checkpoint: `324b887686ece5153d0af6d59e83f9509cd7d331`
- independent summary-verifier source: `1d58514e8c71d27507e806f4ce1be5f399323466`
- final frontier provenance update: `d4d8e22d71f42307ea93ccd1308b120cdaff5851`
- clean reconstruction: `fb2f63d12ccc3de11447d69e7965f2fd3ee1e7d0`

## Exact source hashes recorded by the certified order-102 checkpoint

- loose partition-summary generator: `55ae8cb5dcc80a5db3d0a7303caa68bc4ebdfe9fd734e4b45f8614007f08ebad`
- loose independent summary verifier: `c87a908d37de70507349998c0d6ff04c9bb94b1b79b693648c2c890c757932e1`
- no-C10 generator: `f56d2678b98d927c5d4229826a032808d681626ae20f5b2dfd5368fb5ee4cc83`
- no-C10 verifier: `2ebbd53266cc2baec64eff0654d215cab60e8d2e78178d22aa42e7cbb872e7dd`
- singly-chorded generator: `e04b4a788764fec44e30a6bc8aab172b075b3105626da2f1ab8812129b92c521`
- singly-chorded verifier: `130e0a47e354bff29da541e754fe18b6ca9b90d888891e0964d5bfb794a609c7`

The public `src/final_loose/` files are the retained final loose-C10 source files from the durable branch. The public `src/audit/` directory contains safe audit/control implementations retained by the final theorem-pipeline audit.

## Public reproduction sources added for release

The public repository also contains reconstruction sources whose purpose is to make the certified branch logic directly rerunnable even where an exact historical source snapshot did not survive as an ordinary file. These files are explicitly distinguished from the historical theorem-producing hashes above.

`src/reproduction/no_c10_side51.cpp` was reconstructed from the proved restricted-growth schedule, the two complete triangle-root first-extension orbits, and the branch rejection order structural -> C8 -> C10 -> C16. During the publication sanity pass on 2026-08-16, a fresh GCC `-O3` side-51 run reproduced the certified aggregate exactly:

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

`src/audit/chorded_no_loose_primary.cpp` is a clean reconstructed direct-incidence implementation retained from the post-reset validation work. The clean-reproduction record reports the side-51 branch counters and independent replay. It is not relabeled as the missing original source snapshot whose SHA-256 is recorded above.

## Current release boundary

The public GitHub snapshot does **not** claim to be a complete binary certificate archive. In particular, the original order-102 binary certificates and the exact final no-C10 / singly-chorded generator-verifier source snapshots are identified by hashes and replay records in `ORDER102_CERTIFIED.md`, but those four exact historical source files are not present as ordinary files in the final durable project tree from which this snapshot was assembled.

The public reconstruction programs improve practical reproducibility but do not alter this provenance statement. They are not substituted into the historical source-hash ledger.

A future archival release may add the exact historical binaries/source objects if recovered from the durable computation archive. Until then, the theorem should be read together with the certified hash manifest, clean-reproduction report, public reconstruction programs, and the exact retained loose-C10 generator/verifier.

## Excluded historical experiments

The following retracted/unsafe ideas were deliberately not promoted into the public theorem-producing source tree:

- the false reduction `all C10 -> loose C10`;
- the earlier D5 signature using noncanonical external relabeling;
- partial-incidence-isomorphism memoization;
- heuristic subtree equivalence;
- experimental C32 pruning.

They are not used in the certified order-102 theorem.
