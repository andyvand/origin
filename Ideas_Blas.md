A basic linear algebra system (BLAS, more or less), is an API for libraries
that perorm common linear algebra operaitons such as vector and matrix
multiplication.

There are a large number of C++ BLAS implementations in existence. To name a
few of the popular ones:

  * Eigen
  * MTL
  * Boost.uBlas

Why does Origin need one? Because Origin wants an easy to use, reasonably efficient, C++11-based linear algebra library that uses new language features (in particular move semantics), and integrates closely with other Origin facilities such as concept checking and ranges.

## Project ##

Design a basic linear algebra library.

The library should support dynamically allocated vectors and matrices that support the basic operations of linear algebra: scalar multiplication, matrix addition, and matrix multiplication. It should support algorithms covering BLAS requirements levels 1, 2, and 3.

## Considerations ##

The design should cleanly separate the underlying data representation from its numerical aspects.

## Extensions ##

Extend and optimize the library for fixed-size matrices.

Extend the library for arbitrary-dimensions (e.g., 3 and 4 dimensional matrices). It's not clear (to me) what mathematical operations should be supported for such structures.


## Links ##
GNU Scientific Library (This contains a BLAS library as well as additional functionality) [GNU GSL](http://www.gnu.org/software/gsl/manual/html_node/index.html)

GSL Interface specifications from GNU [Interface Specifications ](http://www.gnu.org/software/gsl/manual/html_node/GSL-BLAS-Interface.html)

## Nice To Have ##
It might be nice to have SIMD instruction options available for some of the operations.