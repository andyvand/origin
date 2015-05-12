# Latent Semantic Indexing #

## Project Description ##
Create a library/framework for creating and querying an arbitrary LSI space.

### Parts ###
There are two parts to the project:
  * LSI space creation
  * LSI Query Space.


## Considerations ##
List of things to which careful consideration should be paid to.
  * Clearly defined classes/functions which decouple the algorithm from the reading of the input, and writing of the output.



## Links ##
Nice Description of LSI [Description of LSI](http://c2.com/cgi/wiki?LatentSemanticIndexing)

Wikipedia description of LSI [Wikipedia LSI](http://en.wikipedia.org/wiki/Latent_semantic_indexing)

## Nice To Have ##
Here are a list of different thing which would be nice to have within the library:
  * Thesaurus integration (using either word net or something else like that).
  * pre-implemented parts which allow for multiple different inputs or outputs to be easily created and managed.
  * The algorithm (especially the building of the LSI Space) needs to be easily run in parallel.
  * It would be nice to have some simple preprocessing functions that help handle the text prior to it being handled by LSI.
  * It would be nice to be able to be able to output an update-able version of an LSI space such that it could be run on a smaller scale with out having to re-process each corpus.