"Well, that makes sense, but what if the member function takes parameters and/or returns something?"

Excellent question! We can just pass those parameters to the wrapped `Sheep`, and return what it returns!

To illustrate this, let's add another member function to our `Animal` interface.
`bool can_eat(std::string_view)` is a pretty simple function, but it works as an example.

The biggest hurdle here is avoiding expensive copying of parameters.
You may want to take parameters by reference in many cases, but in this example, `std::string_view` is very cheap to copy.
