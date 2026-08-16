# Order 102 certified checkpoint

Status date: 2026-08-12.

## Theorem

Every simple cubic bipartite graph on at most 102 vertices contains a cycle of length 4, 8, or 16. Consequently any simple cubic bipartite counterexample to the Erdős–Gyárfás conjecture has order at least 104.

Status: COMPUTER-ASSISTED / COMPUTATIONALLY VERIFIED.

## Loose C10 branch

Canonical loose-root orientation; deterministic depth-20 partition; W=5 summary certificates. All five independent summary verifiers returned ACCEPT and independently regenerated every assigned subtree with exact incidence-path C8 and MITM C16 oracles.

Verified global aggregate:
- states: 195,070,645
- attempted: 59,187,096,573
- structural rejects: 2,277,801,756
- C8 rejects: 31,916,478,091
- C16 rejects: 24,797,746,082
- accepted children: 195,070,644
- canonical root prunes: 606
- completions: 0
- depth-20 tasks: 37,494

- w0: replay elapsed 31:43.54, user 1558.92 s, peak RSS 4092 KiB; cert 487445 B; SHA-256 `7b0a4e5f49aca97eac6c1cd52536d9daaa5d98f0fbe917ec7e8a353aaebf146e`
- w1: replay elapsed 27:59.27, user 1394.85 s, peak RSS 4092 KiB; cert 487445 B; SHA-256 `ac6f50e6d8614bc275a6eb34299c1d3e68adf5fbd27b8ffe54b0190b436af146e`
- w2: replay elapsed 36:38.33, user 1529.97 s, peak RSS 4080 KiB; cert 487445 B; SHA-256 `8179412e7396feafcb16fd77336f2e7a900fbe100a6b52161463ecd901f0b600`
- w3: replay elapsed 38:06.76, user 1982.15 s, peak RSS 3888 KiB; cert 487445 B; SHA-256 `8331819465cc664fe2410bf05f0926c8126b78795fe056ca101fd8c2905d63f9`
- w4: replay elapsed 31:35.97, user 1429.35 s, peak RSS 4088 KiB; cert 487380 B; SHA-256 `983854a48a9e7449286e2b9247839973e71ed9012678f00fbc4377eea856830b`

Manifest checker confirms exactly workers 0..4 and task IDs 0..37,493 once each. Missing worker, duplicate worker, truncation, trailing data, wrong-worker assignment, and an altered subtree counter are rejected. Summary format has no padding bits.

## No-C10 branch

Fresh dual-oracle reproduction and independent replays ACCEPT.
- states: 440,620
- attempted: 125,589,272
- structural: 4,639,096
- C8: 45,300,852
- C10: 70,099,730
- C16: 5,108,976
- accepted: 440,618
- completions: 0

Certificates:
- orbit1 SHA-256 `3562f53345ce56071e5ad506327e488f54936fff37006a6c567b60006033496a`
- orbit2 SHA-256 `741d15fa8e3b06ee9f930c4eeebee63f2ecb63ee3e6040bcd52b83748c7e1419`

## Singly-chorded C10, no loose C10

Independent generator and verifier use different loose-C10 and cycle oracles. Replay ACCEPT.
- states: 4,633,780
- attempted: 1,368,507,421
- structural: 51,631,441
- C8: 428,140,046
- loose-C10: 627,517,857
- C16: 256,584,298
- accepted: 4,633,779
- completions: 0

Certificate SHA-256 `39c00a38593ce1b9cc19fa2f35e7f6fa88485180038d88d8f8a14c84be9f2cdf`. Replay elapsed 27:56.06, user 908.56 s, peak RSS 4076 KiB.

## Trusted source snapshot hashes

- partition summary generator: `55ae8cb5dcc80a5db3d0a7303caa68bc4ebdfe9fd734e4b45f8614007f08ebad`
- independent summary verifier: `c87a908d37de70507349998c0d6ff04c9bb94b1b79b693648c2c890c757932e1`
- no-C10 generator: `f56d2678b98d927c5d4229826a032808d681626ae20f5b2dfd5368fb5ee4cc83`
- no-C10 verifier: `2ebbd53266cc2baec64eff0654d215cab60e8d2e78178d22aa42e7cbb872e7dd`
- chorded generator: `e04b4a788764fec44e30a6bc8aab172b075b3105626da2f1ab8812129b92c521`
- chorded verifier: `130e0a47e354bff29da541e754fe18b6ca9b90d888891e0964d5bfb794a609c7`

Environment: Debian g++ 14.2.0, AMD EPYC 9V74, cgroup CPU quota 4 cores, memory limit 4 GiB.
