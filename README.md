# Arithmos

A lightweight mathematics library written in C, focused on performance,
clarity, and learning-oriented implementation.

---

## Overview

Arithmos is a personal project aimed at exploring optimization techniques in C
while implementing a broad range of mathematical concepts.

The primary goal of the library is performance: all functions are written and
optimized for general random inputs. The focus is to make implementations as
fast and efficient as possible under typical usage conditions.

Arithmos is not restricted to a specific branch of mathematics, although some
areas receive more focus than others depending on development progress and
interest.

---

## Design Goals

- High performance for general-purpose inputs  
- Readable and well-documented source code  
- Modular structure by mathematical area  
- Designed for Linux-type systems  

---

## Platform Support

Arithmos is currently developed for **Linux-based systems**.

Support for other operating systems (Windows, macOS, BSD, etc.) is **not guaranteed**.

---

## Installation

⚠ **Installation support is currently a work in progress.**

At this time, the library cannot be installed system-wide via the provided
CMake configuration files.

For now, Arithmos is intended to be:

- Built locally
- Used directly within the project directory
- Or manually integrated into other projects

Proper installation targets and packaging support will be added in the future.

---

## Project Structure

The project is divided into mathematical areas. Each area has:

- Its own header file
- Its own implementation file(s)
- A unified top-level library header

You may include:

- The full library via `arithmos.h`
- Individual mathematical areas via their specific headers, e.g `numeric.h` or `algebra.h`.

---

## Build System

Arithmos uses **CMake** as its primary build system. Convenience `make` targets are provided for common workflows.

To obtain a copy of the library and setup CMake, run the following commands:

```bash
git clone https://github.com/pieterteb/Arithmos.git
cd Arithmos
mkdir build
cd build
cmake ..
cmake --build .
```

To improve the behaviour of `clangd` and `clang-tidy`, run the following commands from the project root directory:

```bash
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
ln -s compile_commands.json ../
```

### Build Types

There are four build modes:

#### Debug

Builds the project with debug symbols and no optimization. Useful for debugging and testing purposes.

```bash
make debug
```

---

#### Release

Builds the optimized production version.

```bash
make release
```

---

#### Tests

Compiles and runs the test suite for the implemented functions. Used to validate correctness.

```bash
make tests
ctest
```

---

#### Bench (Work in Progress)

Builds benchmarking tools for comparing different implementations of functions.

```bash
make bench
```

This mode is intended to:

- Compare algorithmic approaches
- Measure optimization impact
- Experiment with low-level performance improvements

⚠ Bench mode is still under development.

---

## Usage

Include the full library:

```c
#include "arithmos.h"
```

Or include specific areas:

```c
#include "algebra.h"
#include "numeric.h"
```

Or include specifics:
```c
#include "core/types.h"
#include "numeric/gcd.h"
```

Example:

```c
#include <stdio.h>

#include "arithmos.h"

int main(void) {
    arith_u64 a = 15;
    arith_u64 b = 24;

    arith_u64 gcd = arith_gcd_u64(a, b);

    printf("gcd of %lu and %lu is: %lu\n", a, b, gcd);

    return 0;
}
```

---

## Optimization Philosophy

All implementations are designed with the assumption of **random inputs**. Benchmarks are run using both the **GCC and Clang** compilers. While optimizations **prioritize Clang builds**, large performance differences between GCC and Clang are considered undesirable and treated as bugs.

This project serves as a learning platform for:

- Low-level performance tuning
- Compiler behavior exploration
- Algorithmic efficiency improvements

---

## Roadmap

- [ ] Improve benchmark framework
- [ ] Add performance comparison reports
- [ ] Add proper CMake installation support
- [ ] Add support for installing specific modules
- [ ] Investigate SIMD/vectorization optimizations

---

## Contributing

This is primarily a personal learning project,
but suggestions and discussions are welcome.

---

## License

This project is licensed under the GNU General Public License v3.0 or later (GPL-3.0-or-later).
See the LICENSE file for details.
