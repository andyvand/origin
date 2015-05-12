The ultimate goal of the Origin Project is to investigate the feasibility of
creating a unified set of abstractions across a variety of computational
domains. These abstractions correlate roughly to the notion of _concepts_,
or classes of types. Our focus is primarily on defining abstractions that
correspond to algorithms or operations rather than simply finding types that
share common interfaces. Moreover, we are looking for these algorithms to be
implemented as efficiently as possible, regardless of the types on which they
operate.

Essentially, the Origin Project is an experiment in large scale [GenericProgramming
generic programming]. We are seeking abstractions and genericity by evaluating
a broad set of concrete implementations.

## Simplicity ##
Origin strives for simplicity in its interfaces. We firmly believe that a good
software component (class, function, module, etc.) is one that does one job
and does it well.

## Expressivity ##

## Complexity ##
There are a number of programming techniques that inherently raise the
complexity of an interface.

### Generative Programming ###

### Expression Templates ###
Origin does not use expression templates in any of its data structures---even
when it is known when the approach can be used to dramatically improve the
efficiency of some operations.