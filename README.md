# Lydia

![Lydia CI pipeline](https://github.com/whitemech/lydia/workflows/Lydia%20CI%20pipeline/badge.svg)
![](https://img.shields.io/badge/iso-c%2B%2B17-ff69b4)
[![](https://img.shields.io/badge/build-cmake-lightgrey)](cmake.org/)
[![](https://img.shields.io/badge/test-Catch2-yellow)](https://github.com/catchorg/Catch2/)
[![](https://img.shields.io/badge/license-LGPLv3%2B-blue)](./LICENSE)

Lydia is a tool for LDLf translation to DFA and for LDLf synthesis.

## Requirements

We use CMake as a build tool. Please 
check the [official website](https://cmake.org/)
to download it for your platform.

## Build

To build from source, clone the repository:
```
git clone https://github.com/whitemech/lydia.git --recursive
cd lydia
```

To build:

```bash
mkdir build && cd build
cmake ..
make -j4
```
Afterwards, to run the tests:
```
make test
```

## Development

Set up your development environment:

```
sudo apt-get install clang-9.0 \
    clang-format-9.0 \
    clang-tidy-9.0 \
    gcovr

```

To configure the build, use the flag `-DENABLE_COVERAGE=ON`

In `scripts/` you can find useful scripts for development. In particular:

- `scripts/apply-clang-format.sh` applies the fixes provided by
  `clang-format`.
- `scripts/apply-clang-tidy.sh` applies the fixes provided by
  `clang-tidy`.
  
The same scripts but with the `check` prefix lets you check whether
fixes are needed or not.
