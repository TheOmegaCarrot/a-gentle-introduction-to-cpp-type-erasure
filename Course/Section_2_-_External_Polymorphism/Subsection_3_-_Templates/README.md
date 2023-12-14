Well, that certainly works fine for a single class, but doing that for multiple classes would lead to a lot of code duplication.

Fortunately, we can use templates to write one class template, `Animal_Wrapper`, that can be instantiated for anything that implements the `Animal` interface!
