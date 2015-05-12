# Introduction #
This page describes how to get started with the Origin C++0x libraries.

# Prerequisites #
## Programs and Libraries ##
The Origin C++0x Libraries have two prerequisites:

  * [CMake](http://www.cmake.org/) -- Origin uses CMake as the build system.

## Compilers ##
You also need a compiler that implements the following C++0x features:

  * Move Semantics
  * Auto and Decltype
  * Variadic Templates
  * Constant Expressions
  * Lambda Expressions
  * Uniform Initialization
  * Initializer Lists
  * ...

Your standard library must also provide:

  * Tuples
  * Type Traits
  * ...

Currently, the only known option for compiling the Origin C++0x Libraries is GCC. Notes are given for other compilers below.

### GCC ###
Must currently be compiled out of SVN. Instructions for acquiring GCC can be found [here](http://gcc.gnu.org/svn.html). Installation instructions can be found [here](http://gcc.gnu.org/install/). Because Origin tracks GCC's evolution through SVN, we typically only build the C and C++ compilers and skip the bootstrap build.

Note that GCC has a number dependencies itself (e.g., GMP, MPFR, MPC, etc.). We found it useful to install these locally with the prefix `~/opt` so they don't collide with your distributions versions. Typically, these only need to be downloaded and compiled once. However, GCC will infrequently change their minimum required version of its dependencies, and you will have to go through this process again.


### Visual C++ ###
Not tested, but VS 2010 does not support variadic templates, this is unlikely.

### Clang ###
Does not currently include sufficient language support to compile the Origin C++0x libraries.

# Getting the Source Code #
Since Origin does not currently have any releases, the only way to get the source code is to check it out from Subversion. Instructions for doing so can be found here:

http://code.google.com/p/origin/source/checkout


# Building Origin #

## Linux and Mac ##
In order to build Origin on Linux or Mac, you must first install the [prerequisite software](#Prerequisites.md), including an a [SVN build of GCC](#GCC.md).

Origin uses CMake as the build system and relies on a number environment variables to control the build. _Before running CMake_, make sure that the following environment variables are set.

| **Variable** | **Description** |
|:-------------|:----------------|
| `CXX` | Absolute path to the SVN-built g++ executable |
| `LD_LIBRARY_PATH` | Paths to the library's for GMP, MPFR, MPC, etc. |
| `ORIGIN_ROOT` | The path to the top-level Origin directory |

Note that `LD_LIBRARY_PATH` may be `DYLIB_LIBRARY_PATH` on Mac OS X.

Note that you could also set `PATH` to include the binaries to the custom-built GCC. This would replace the `CXX` variable.

### Configuration ###
To build Origin, change into the `$ORIGIN_ROOT` directory and create a build directory. Change into the build directory and run `cmake` to configure the build. You can optionally run `ccmake` to launch a configuration editor and manually change build options.

```
$ cd $ORIGIN_ROOT
$ mkdir build
$ cd build
$ cmake ..
$ ccmake .
```

Important configuration settings are:

| **Setting** | **Description** |
|:------------|:----------------|
| CMAKE\_BUILD\_TYPE | Choose either `Debug` or `Release` |
| CMAKE\_INSTALL\_PREFIX | The path where Origin will be installed |
| ORIGIN\_BUILD\_TESTS | If set, builds the test suite |

We recommend setting the installation prefix to something in your home directory, e.g., `~/opt`. This makes sure that you don't affect the system build.

### Build ###
After configuration has finished, build Origin. Unless the `ORIGIN_BUILD_TESTS` macro has been set, this is virtually a "no-op". Origin is primary comprised of header files, there are no components to build. This may change in the future.

Build Origin (and possibly the test suites) by running `make`. Run the test suite by running `make test`.

```
$ make
$ make test
```

### Installation ###
After building Origin, it can be installed by running `make install`.

## Windows ##
Since Visual C++ is not an option, you would need to build GCC from subversion on Windows. MinGW or Cygwin may be viable solutions, but we haven't tested these. Our best suggestion is to run a Linux distribution as a virtual operating system and then follow the [build instructions Linux (or Mac)](#Linux_and_Mac.md).