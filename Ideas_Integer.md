An arbitrary precision integer is one that can store values much larger than
the built-in integer types. There are, of course, trade-offs.

## Project ##

Design and implement an arbitrary precision integer. The use of the type
should be trivial::

```
	origin::integer i = ...
```

The integer type must also be usuable with every standard numeric algorithm
that takes integer arguments. Arbitrary precision integers must also
interoperate seemlessly with arbitrary precision real numbers.

## Considerations ##

A trivial implementation can be achieved by wrapping GMP's integer type that
accepts integer arguments.

## Extensions ##

Consider large fixed-width integers whose precision is determined by a
template argument (e.g., `integer<128>`). These could be implemented in terms
of the internals of an arbitrary precision integer, or this could be a separate
project.

## Links ##

FIXME: Link to known bigint implementations.