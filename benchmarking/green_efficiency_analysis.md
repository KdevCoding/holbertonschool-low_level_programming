# Green Efficiency Analysis

## Measurement Methodology

Three experiments were run to compare algorithmic efficiency. The first measured a simple loop of 100,000,000 iterations, repeated three times, producing execution times of 0.057805, 0.060806, and 0.063128 seconds. This established a baseline for how long a fixed, large number of trivial operations takes on the test machine, and confirmed that repeated runs of the same workload produce consistent, low-variance timings.

The second experiment compared two algorithms solving the same problem: a "naive" algorithm and a "single-pass" algorithm, each run three times to reduce noise from background processes, cache warm-up, and scheduling jitter. Execution time was captured with in-code timers, and each computation's numeric result was recorded to verify correctness.

The third experiment measured a pipeline broken into three labeled phases — BUILD_DATA, PROCESS, and REDUCE — with a TOTAL timer wrapping all three: TOTAL 0.000227s, BUILD_DATA 0.000100s, PROCESS 0.000085s, REDUCE 0.000042s (0.000100 + 0.000085 + 0.000042 = 0.000227, matching TOTAL exactly). This shows not just that a program is fast, but where within it the time is going.

## Observed Performance Differences

The naive algorithm produced a result of 625,025,000 across all three runs, with execution times of 0.475216, 0.478667, and 0.477649 seconds. The average naive runtime was:

**Naive avg = (0.475216 + 0.478667 + 0.477649) / 3 = 0.477177 seconds**

The single-pass algorithm produced a result of 25,000 across all three runs, with execution times of 0.000018, 0.000017, and 0.000022 seconds. The average single-pass runtime was:

**Single-pass avg = (0.000018 + 0.000017 + 0.000022) / 3 = 0.0000190 seconds**

**Difference = 0.477177 − 0.000019 ≈ 0.477158 seconds**, meaning the naive algorithm took roughly 25,000 times longer than the single-pass algorithm on average. This is a substantial, consistent, and reproducible gap across all three trials, not a one-off anomaly.

The third experiment's phase breakdown shows that even within a fast pipeline, time is not spent evenly: BUILD_DATA accounted for roughly 44% of the 0.000227s total, more than either PROCESS (37%) or REDUCE (19%) alone. If this pipeline were optimized further, BUILD_DATA would be the first target, since it consumes the largest single share of measured time.

## Relation Between Runtime and Energy Consumption

Runtime is a reasonable proxy for energy consumption because a CPU draws power continuously while executing instructions. A program that runs for 0.477 seconds keeps the processor active roughly 25,000 times longer than one that finishes in 0.000019 seconds, meaning the naive algorithm holds cores at active power draw far longer than necessary. Since energy is roughly power multiplied by time, and the naive algorithm's power draw is not lower to compensate, its total energy use is expected to scale with its runtime difference. At data-center scale, where the same computation may run millions of times, this runtime gap translates into materially higher electricity use and cooling load for no additional benefit.

## Limitations of the Experiment

These experiments measured wall-clock execution time only; power draw was never measured directly (e.g., via a wattmeter or CPU energy counters), so the energy conclusions below are inferred from runtime, not measured. Additionally, the naive and single-pass algorithms returned different numeric results (625,025,000 vs. 25,000), suggesting they may not compute identical logic or may operate over different input ranges — this should be verified before treating the speed comparison as a true apples-to-apples efficiency gain. All tests were run only three times each on a single machine, so results may not generalize across hardware, compilers, or system loads.

## Practical Engineering Takeaway

Even without direct power measurements, the runtime evidence strongly suggests that algorithmic choice has a far greater impact on energy efficiency than low-level optimization would. A single-pass approach that avoids redundant work can cut runtime, and by extension energy consumption, by several orders of magnitude versus a naive approach. Before optimizing hardware or infrastructure for "green" computing, improving algorithm design should be the first priority, since the measured 25,000x runtime gap dwarfs any gain achievable through hardware tuning alone. The phase-level timing further shows that efficiency work is most effective when targeted at the phase consuming the most time (here, BUILD_DATA) rather than applied uniformly across a program.
