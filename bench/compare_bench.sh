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


# Function to build a branch with a specific compiler
build_branch() {
    local branch=$1
    local compiler=$2
    local build_dir=$3

    echo "=== Building branch '$branch' with '$compiler' ==="

    git checkout "$branch"

    # Clean build directory
    rm -rf "$build_dir"
    mkdir -p "$build_dir"

    # Build Arithmos library
    cmake -S . -B "$build_dir" \
        -DCMAKE_BUILD_TYPE=Bench \
        -DCMAKE_C_COMPILER=$compiler
    cmake --build "$build_dir" -j

    # Compile benchmark manually linking the library
    g++ -std=c++20 -O3 -march=native \
        -Iinclude \
        "$BENCH_SOURCE" \
        -L "$build_dir/src" -larithmos \
        -o "$build_dir/$BENCH_BIN"
}


# Function to run benchmark and collect perf stats
run_bench() {
    local build_dir=$1
    local out_prefix=$2

    echo "=== Running benchmark in $build_dir ==="
    echo "--- Google Benchmark Output ---"
    $build_dir/$BENCH_BIN --benchmark_out="$out_prefix.json" --benchmark_out_format=json

    echo "--- perft stats ---"
    perf stat -e cycles,instructions,branches,branch-misses,cache-references,cache-misses \
        "$build_dir/$BENCH_BIN" 2> "$out_prefix.perf"
}


# Build both branches
build_branch "$BASE_BRANCH" "$BASE_COMPILER" "$BASE_BUILD_DIR"
build_branch "$DEV_BRANCH" "$DEV_COMPILER" "$DEV_BUILD_DIR"
