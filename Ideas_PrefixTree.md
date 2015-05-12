A prefix tree or [trie](http://en.wikipedia.org/wiki/Trie) is an ordered tree
data structure that stores keys having a sequential structure (typically
strings). A prefix tree guarantees that every descendent of a node has the same
prefix.

## Project ##

Design a generic prefix tree library.

A generic prefix tree must be parameterized over its key type, which must
be Iterable. Note that the type is not restricted to only strings. In theory,
we could build prefix trees for lists of integers as easily as lists of
characters. The tree should also be parameterized over a weak order that
compares the elements of the key type.

The interface should provide a method for finding all keys that start with
a given prefix (i.e., `tree.starts_with(k)`). Additionally the data structure
should be adapted to provide the usual Set, Multiset, Map, and Multimap
concepts.

## Considerations ##

How will each node store its children? Will the node contain an array that
maps each value to a child, or will the set of children be dynamically
assigned.

Will the prefix tree own its keys or index into another data set? Can the
library be designed to do both?

## Extensions ##

Implement path compression. Instead of each branch of the tree representing
a single element of the key, it can represent a common prefix (a sub-key) of
its descendents.

## Links ##