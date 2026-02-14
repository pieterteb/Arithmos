#!/usr/bin/env bash
set -euo pipefail


# Usage:
# ./compare_bench.sh <bench_source> <base_branch> <base_compiler> <dev_branch> <dev_compiler>


BENCH_SOURCE=$1
BENCH_BIN="${BENCH_SOURCE%.cpp}"

BASE_BRANCH=$2
BASE_COMPILER=$3
DEV_BRANCH=$4
DEV_COMPILER=$5

BASE_BUILD_DIR="build_base"
DEV_BUILD_DIR="build_dev"

RESULTS_DIR="bench/results"
mkdir -p "$RESULTS_DIR"


# Exit if perf is not available.
command -v perf >/dev/null || { echo "perf not found"; exit 1; }


# Function to build a branch with a specific compiler.
build_branch() {
    local branch=$1
    local compiler=$2
    local build_dir=$3

    echo "Building '$branch' ($compiler)"

    git checkout "$branch"

    rm -rf "$build_dir"

    cmake -S . -B "$build_dir" \
        -DCMAKE_BUILD_TYPE=Bench \
        -DCMAKE_C_COMPILER=$compiler \
        -DCMAKE_CXX_COMPILER=${compiler/cc/++}

    cmake --build "$build_dir" --parallel
}


# Function to run benchmark and collect perf stats.
run_bench() {
    local build_dir=$1
    local prefix=$2
    local compiler=$3

    echo "Running $build_dir"

    echo "Commit:   $(git rev-parse HEAD)" > "${prefix}.meta"
    echo "Compiler: $compiler" >> "${prefix}.meta"

    taskset -c 0 \
        "$build_dir/$BENCH_BIN" \
        --benchmark_min_time=1 \
        --benchmark_repetitions=5 \
        --benchmark_report_aggregates_only=true \
        --benchmark_out="${prefix}.json" \
        --benchmark_out_format=json
}


build_branch "$BASE_BRANCH" "$BASE_COMPILER" "$BASE_BUILD_DIR"
build_branch "$DEV_BRANCH" "$DEV_COMPILER" "$DEV_BUILD_DIR"

run_bench "$BASE_BUILD_DIR" "$RESULTS_DIR/base" "$BASE_COMPILER"
run_bench "$DEV_BUILD_DIR" "$RESULTS_DIR/dev" "$DEV_COMPILER"


echo "Done"
