# Section 1: Introduction

Inheritance and virtual functions allow for *runtime polymorphism*,
where the true type of an object is not known until runtime.
This is possible because every type in the inheritance tree shares a *common interface*.
A classic example is an `Animal` base class, and multiple derived types, such as `Cat`, `Dog`, `Horse`, and so on.
All of these animal types can have an `void speak()` member function, where each animal can do different things.

A major downside of this approach is that `Cat`, `Dog`, and `Horse` must actually inherit from `Animal` for this to work.
Suppose someone else wrote a `Sheep` class, and this `Sheep` has a `void speak()` member function.
If this `Sheep` does not inherit from *our* `Animal` class, then we cannot refer to it through an `Animal*`, even though it implements the right interface!
In order to use this `Sheep` class alongside our existing animals, we would have to modify the `Sheep` class to inherit from `Animal`.
`Sheep` would have to have been designed to work with our `Animal` class hierarchy.
This may be difficult if `Sheep` is from a third-party library; plus, nobody wants to break somebody else's code.

Type erasure is one way to solve this.
With type erasure, any class that implements a `void speak()` member function can be used in the same way,
even if it does not inherit from *anything*.
If `Animal` were not a base class, but a clever type-erasing wrapper, much like `std::function`,
we could use a `Sheep`, `Elephant`, or anything else that implements a `void speak()` member function.
If we do it correctly, we would not even have to modify our `Animal` wrapper to support a new type of animal;
as long as the new animal has a `void speak()` member function, it would just work!

There are two key parts to implementing this approach: **external polymorphism** and **templates**.

In the following sections, external polymorphism will be introduced, and then it will be automated with templates.
Throughout the process, we will actually implement the previously described `Animal` type-erasing wrapper.
