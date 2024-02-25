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
