
# Newton-Fractal_ISPC

Small demo program that renders the Newton fractal for the equation

\[
z^n - 1 = 0
\]

The heavy pixel computation is implemented in **ISPC** (SIMD on CPU).  
A simple C++ driver calls the ISPC kernel and writes the result to a **PPM** image.

---

## Requirements

- CMake ≥ 3.16  
- C++20 compiler (gcc / clang / MSVC)  
- [ISPC](https://ispc.github.io/) installed and available on `PATH`  


Tested on Linux with `gcc` and `ispc`.

---

## Build

From the repository root:

```bash
mkdir build
cd build

# if ispc is on PATH:
cmake ..

# or, if you need to point to a specific ispc binary:
# cmake -DISPC_EXECUTABLE=/full/path/to/ispc ..

cmake --build .
````

This will produce the executable:

```text
build/NewtonFractal_ISPC
```

---

## Run

Basic usage:

```bash
./NewtonFractal_ISPC [degree]
```

Where:

* `degree` – degree of the polynomial in ( z^n - 1 ) (default: 5, must be ≥ 2)

Examples:

```bash
# default n = 5
./NewtonFractal_ISPC

# n = 7
./NewtonFractal_ISPC 7
```

The program writes an image called:

```text
newton-ispc.ppm
```

You can open it in any viewer that supports PPM (e.g. `eog`, `gimp`, `krita`, etc.).


