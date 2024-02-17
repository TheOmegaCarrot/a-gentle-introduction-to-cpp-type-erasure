Here, the library doesn't provide an inheritance tree at all!
Instead, there are simple a handful of classes that share a common interface.

If we want to use these classes polymorphically, we still can!
We can write the `Animal` base class ourselves, and use the templated wrapper from the last section.

This is the core of type erasure.
We are taking a set of types that were not designed to be used polymorphically, but we are still able to use them polymorphically.
The only requirement is the common interface between them.
In this example, each type of animal (`Cat`, `Dog`, `Horse`, `Sheep`) only needs to have two specific member functions: `void speak() const` and `bool can_eat(std::string_view food) const`.
