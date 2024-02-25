Our `Animal_Wrapper` definitely *works,* but it's a bit clunky to use.
If you use `std::function`, then it's as simple as:

```cpp
#include <functional>
#include <iostream>

void say_hello() {
    std::cout << "Hello!\n";
}

int main() {
    std::function<void()> my_function = &say_hello;

    my_function();

    my_function = [](){
        std::cout << "Lambda\n";
    };

    my_function();

    std::function<void()> another_function = my_function;

    my_function();
    another_function();
}
```

There's no pointers to remember to delete and you can copy it like anything else.
How this essentially works is that the equivalents to our `Animal` base class and the `Animal_Wrapper` we wrote are private classes *inside* `std::function`.
The rest of `std::function` is just providing a nice wrapper around that little external polymorphism tree.

This does have some implications, namely that the type erased object can contain a null pointer!
What should we do if someone tries to `my_animal.speak()` but `my_animal` has a null pointer?
The only thing we really *can* do is throw an exception.
We can wrap that logic in a little private member function what we call at the start of every function that uses the internal `Animal_Base*`.

We just need to add a few things to make this work:

- A virtual `clone` member function to make copying possible,
- A class that can handle managing all of the `new`ed pointers, including deleting them
- A templated constructor and assignment operator to assign animals to the type erased class

These examples are getting long, so the `Animal` type erasure class is in `Animal.hpp`, all of the different types of animals are in `zoo.hpp`.
`wrapped.cpp` has a little demo of `Animal`, and you can try to compile `error.cpp` to see what kind of compiler errors you get if you try to assign to an `Animal` with something that doesn't implement the right member functions.
