External polymorphism, and thus type erasure, does not require all member functions to be the same.
We can simplify things down to just what the types have in common, their *common interface subset.*

Here, each of our animals have extra member functions.
This doesn't affect our `Animal_Wrapper` at all, and it still functions just as before.

We can't *use* these extra member functions through the `Animal_Wrapper`, but that's just like member functions a derived class has that its base class does not have.
