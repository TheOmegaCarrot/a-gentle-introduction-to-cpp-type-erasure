# What's Next?

This course has intended to serve as an introduction to implementing type erasure.
Thus, there are some further details which are not covered here.

This course covered an *owning* form of type erasure, where the type erasure wrapper object *owns* the polymorphic object.
The `Animal` class allocates memory for the animal it contains, and is responsible for deleting it.
Alternatively, an `Animal_Reference` class could be created, which behaves more like a pointer, much like `std::string_view`.
This has the advantage of not requiring a heap allocation, but has the disadvantage of it being possible for the pointer to dangle.
Implementing `Animal_Reference` is left as an exercise for the reader; but as a hint, consider how the actual `Dog`, `Sheep`, or whichever animal object is stored.

The second technique not covered here is a *small object optimization.*
If you are familiar with the common small *string* optimization, this is essentially the same idea.
In the small string optimization, a short enough string can be stored without a heap allocation.
Instead, the character array is stored inside the string object itself, rather than containing a pointer to a heap-allocated character array.
This does require some extra bookkeeping, as you must keep track of whether the small object optimization is being used.
Perhaps this course may be extended in the future to cover a small object optimization.
