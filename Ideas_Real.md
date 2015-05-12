An arbitrary precision real number one that stores real numbers with varying
degrees of precision.

## Project ##

Design and implement an arbitrary precision integer. The use of the type
should be trivial::

```
	origin::real i = ...
```

The real type must also be usuable with every standard numeric algorithm that
accepts real-valued arguments.

## Considerations ##

A trivial implementation can be achieved by wrapping MPFR's real type.

## Extensions ##

Consider large fixed-width integers whose precision is determined by a
template argument (e.g., `integer<128>`).

## Links ##

FIXME: Link to known bigint implementations.