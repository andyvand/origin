A fixed-point number implementation that uses the [Q](http://en.wikipedia.org/wiki/Q_(number_format)) number format.

## Project ##

Design and implement a generic fixed-point number implementation using the
[Q](http://en.wikipedia.org/wiki/Q_(number_format)) number format.

```
	origin::fixed<8, 24> i = ...
```

Where 8 is the number of bits reserved for the integer part of the number, and
24 is the number of bits used for the fraction.

## Considerations ##

This project is fairly straightforward. A simple implementation could wrap
libfixmath, but the implementation would benefit significantly from the
inlining and constexpr features of C++.

## Links ##

> - http://en.wikipedia.org/wiki/Q_(number_format)
> - http://code.google.com/p/libfixmath/