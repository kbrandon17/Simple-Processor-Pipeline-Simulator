# Simple Processor Pipeline Simulator
This project involves implementing a cycle-accurate simulator for a simple in-order processor pipeline with a configurable pipeline width. The simulator reads an instruction trace, models the movement of each instruction through the pipeline, and tracks performance metrics such as total execution time and instruction type histogram.

## System Description
The processor pipeline consists of five stages: Instruction Fetch (IF), Instruction Decode and Read Operands (ID), Instruction Issue and Execute (EX), Memory access (MEM), and Writeback results/Retire (WB). The pipeline is W-wide superscalar, allowing W pipelines to run in parallel. Each instruction must pass through all five stages sequentially.

## Assumptions
* No branch prediction.
* All instruction fetches and memory accesses hit in the L1 caches.
* Integer and floating point operations execute in 1 cycle.
* Branch instructions delay instruction fetch until after execution.
* Loads and stores access the L1 data cache in 1 cycle.
## Input Trace Format
The simulator consumes a trace with the following format:

* Instruction Program Counter (PC)
* Instruction Type (1-5): Integer, Floating Point, Branch, Load, or Store
* List of PC values for instructions the current instruction depends on
## Tracking Dependences
Dependences fall into three categories:

* Structural Hazards: Instructions sharing the same functional unit cannot execute simultaneously.
* Control Hazards: Branch instructions halt instruction fetch until after execution.
* Data Hazards: Instructions cannot proceed until all data dependencies are satisfied.
## Running Replications
Six replications are run for each configuration, each containing 1 million instructions. Replications start at different points in the trace, with data dependencies on preceding instructions ignored in subsequent replications.

Experimental Design
A two-factor experimental design measures the impact of pipeline width (W) and workload trace (T). The pipeline width has four levels (1-4), and three traces are provided. Six replications are run for each configuration to estimate impact and variation allocation.

## Performance Metrics
Performance metrics include:

* Simulation Clock (cycles)
* Total Execution Time (cycles)
* Histogram of retired instructions by type

## Acknowledgments
This project is part of CMPT 305 at Simon Fraser University.
