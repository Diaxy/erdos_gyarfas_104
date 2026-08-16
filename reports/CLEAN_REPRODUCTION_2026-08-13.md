# Clean reproduction of the certified order-102 checkpoint

Date: 2026-08-13.

This note records a fresh reconstruction after a runtime reset. The reconstruction started from the durable source/checkpoint material and did not rely on the previous order-102 processes.

## Result

The fresh run independently reproduces the certified theorem:

**Every simple cubic bipartite graph on at most 102 vertices contains C4, C8, or C16.**

Therefore the simple cubic bipartite Erdős–Gyárfás lower bound is **104**.

## Loose C10 branch

Fresh generator aggregate:
- states 195,070,645
- attempted 59,187,096,573
- structural 2,277,801,756
- C8 31,916,478,091
- C16 24,797,746,082
- accepted 195,070,644
- root prunes 606
- completions 0

The five fresh summary certificates have exactly the same SHA-256 values as the durable order-102 checkpoint:
- w0 `7b0a4e5f49aca97eac6c1cd52536d9daaa5d98f0fbe917ec7e8a353aaebf146e`
- w1 `ac6f50e6d8614bc275a6eb34299c1d3e68adf5fbd27b8ffe54b0190b436af146e`
- w2 `8179412e7396feafcb16fd77336f2e7a900fbe100a6b52161463ecd901f0b600`
- w3 `8331819465cc664fe2410bf05f0926c8126b78795fe056ca101fd8c2905d63f9`
- w4 `983854a48a9e7449286e2b9247839973e71ed9012678f00fbc4377eea856830b`

The fresh independent summary verifier source SHA-256 is `79f5ca980ca2ee91a8613da56ebf5359b1c76e07948a1f57c8b435e56c2d3524`, distinct from the verifier source hash preserved in the original durable order-102 checkpoint. It uses generic simple Berge-path closure tests rather than the discovery generator's fast pair-block oracle.

Fresh replay status:
- worker 0: ACCEPT
- worker 1: ACCEPT
- worker 2: ACCEPT
- worker 3: ACCEPT
- worker 4: independently covered by three deterministic task-index shards; all three ACCEPT_SHARD with exit 0, covering 2500 + 2499 + 2499 = 7498 task records exactly once.

The durable checkpoint additionally contains an earlier monolithic worker-4 ACCEPT, so the sharded fresh verification is an extra cross-check rather than the only support for that worker.

## No-C10 branch

Fresh aggregate:
- states 440,620
- attempted 125,589,272
- structural 4,639,096
- C8 45,300,852
- C10 70,099,730
- C16 5,108,976
- accepted 440,618
- completions 0

Both fresh orbit certificates independently replay: ACCEPT.

Fresh certificate SHA-256:
- orbit1 `c9b7dfef13095599700650f858ee61b517965794666a1f490f7703370ff8df50`
- orbit2 `18a444597e2f65ab48e3a1f8dfc9f23c346d3dd01fbdff152b80481b4ae224cc`

## Singly-chorded / no-loose branch

Fresh counters:
- states 4,633,780
- attempted 1,368,507,421
- structural 51,631,441
- C8 428,140,046
- loose C10 627,517,857
- C16 256,584,298
- accepted 4,633,779
- completions 0

Independent direct-incidence replay: ACCEPT.

Fresh certificate SHA-256: `c2f3b2cb85d13ef2f4d0840b9aafa0564d91181863c3d8a14a223dfba392518c`

## Integrity controls

Fresh order-102 summary certificate set:
- full five-worker set: CERTIFICATE_SET_ACCEPT
- missing worker: rejected
- duplicate worker: rejected
- truncation: rejected
- trailing data: rejected
- wrong worker/header/coverage assignment: rejected

## Runtime environment

- AMD EPYC 9V74 allocation
- cgroup CPU quota: 4 cores (`cpu.max = 400000 100000`)
- cgroup memory limit: 4 GiB
- g++ 14.2.0
- clang++ 17.0.0 available

## Conclusion

The clean reconstruction reproduces the durable order-102 theorem with identical loose discovery certificates and a separately reconstructed independent verifier. No discrepancy, survivor, or new completeness defect was found.
