# A Gentle Introduction to C++ Type Erasure

This is intended to serve as an accessible introduction to implementing type erasure in C++.

Existing familiarity with modern C++ is assumed, such as classes, polymorphism, and templates.

---

# How Does This Course Work?

If you go click on the `Course` you will be presented with a list of the sections.
Each section (or subsection) has a `README.md`, which will be presented much like this document you're currently reading.
A large part of the course is in the example code that we will be building up over the course of the course.
Take your time, and make sure you understand each step along the way.

You are encouraged to clone this repository for yourself to compile and run the examples (see section on compiling).
You are also encouraged to tinker with the examples, to really understand what is going on.

---

# What if I have Questions?

If you have questions, issues are a great way to ask them.

---

# Compiling

Compiling this requires only `cmake` and a C++17 compiler.

To build this from the command line:

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel 4 # or however many cores your CPU has, but these examples don't take long to compile
```

The executables for each example will automatically be placed in the same directory as the example `.cpp` file they were compiled from.

If you do not have `cmake` installed, then there is an alternative.
These examples do not require any special compiler options, so you can simply invoke your compiler directly:

```
g++ example.cpp -o example
```
