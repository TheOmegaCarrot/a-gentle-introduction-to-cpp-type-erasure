#include <iostream>
#include <stdexcept>
#include <string_view>
#include <vector>

#include "zoo.hpp"

class Animal
{
private:

  class Animal_Base
  {

  public:

    Animal_Base() = default;
    Animal_Base(const Animal_Base&) = delete;
    Animal_Base(Animal_Base&&) = delete;
    Animal_Base& operator=(const Animal_Base&) = delete;
    Animal_Base& operator=(Animal_Base&&) = delete;
    virtual ~Animal_Base() = default;

    // here is our interface
    virtual void speak() const = 0;
    virtual bool can_eat(std::string_view) const = 0;

    // this needs to be a part of the interface for these internals to work
    virtual Animal_Base* clone() const = 0;
  };

  template <typename T>
  class Animal_Wrapper : public Animal_Base
  {
  private:

    T wrapped_animal;

  public:

    Animal_Wrapper() = default;

    explicit Animal_Wrapper(T animal)
        : wrapped_animal {animal}
    { }

    Animal_Wrapper(const Animal_Wrapper&) = delete;
    Animal_Wrapper(Animal_Wrapper&&) = delete;
    Animal_Wrapper& operator=(const Animal_Wrapper&) = delete;
    Animal_Wrapper& operator=(Animal_Wrapper&&) = delete;
    ~Animal_Wrapper() override = default;

    void speak() const override
    {
      wrapped_animal.speak();
    }

    bool can_eat(std::string_view food) const override
    {
      return wrapped_animal.can_eat(food);
    }

    // fortunately copying is easy
    // this DOES mean that any animal we are wrapping has to be copyable
    Animal_Wrapper* clone() const override
    {
      return new Animal_Wrapper(wrapped_animal);
    }
  };

  Animal_Base* erased_animal = nullptr;

  // here is the null-checking private member function
  void null_check() const
  {
    if ( erased_animal == nullptr ) {
      throw std::runtime_error("Attempt to use a null Animal!");
    }
  }

public:

  // default constructor leaves the Animal in a null state
  // (but that's ok)
  Animal() = default;

  Animal(const Animal& src)
      // remember, the Animal_Base has the clone() member function,
      // not the Animal class
      : erased_animal {src.erased_animal->clone()}
  { }

  Animal(Animal&& src) noexcept
      : erased_animal {src.erased_animal}
  { }

  Animal& operator=(const Animal& rhs)
  {

    // handle self-assignment
    if ( this == &rhs ) {
      return *this;
    }

    // deleting a null pointer is ok and does nothing
    delete erased_animal;

    // copy the erased animal
    erased_animal = rhs.erased_animal->clone();

    return *this;
  }

  Animal& operator=(Animal&& rhs) noexcept
  {

    // handle self-assignment
    if ( this == &rhs ) {
      return *this;
    }

    // can't have a memory leak!
    delete erased_animal;

    erased_animal = rhs.erased_animal;

    return *this;
  }

  ~Animal()
  {
    // can't have a memory leak!
    delete erased_animal;
  }

  // here is our templated constructor
  // this will create the right type of Animal_Wrapper
  // this lets us do:
  // Animal my_animal{Sheep{}};
  template <typename Some_Animal>
  explicit Animal(const Some_Animal& animal_to_erase)
      : erased_animal(new Animal_Wrapper<Some_Animal>(animal_to_erase))
  { }

  // and here is our templated assignment operator
  // this is how we can:
  // my_animal = Horse{};
  template <typename Some_Animal>
  Animal& operator=(const Some_Animal& animal_to_erase)
  {

    // can't have a memory leak!
    delete erased_animal;

    erased_animal = new Animal_Wrapper<Some_Animal>(animal_to_erase);

    return *this;
  }

  // You can also do versions of the templated constructor and assignment operator
  // that take their parameters by move, but for the sake of simplicity,
  // those will be left out of this example

  // here is how our type erased animal can speak!
  void speak() const
  {
    // gotta make sure we're not null!
    null_check();

    // and the virtual function call will handle it from here,
    // using the external polymorphism machinery we've been building
    // in Section 2
    erased_animal->speak();
  }

  bool can_eat(std::string_view food) const
  {
    null_check();

    return erased_animal->can_eat(food);
  }
};

int main()
{
  // Let's try it out!

  // It can start out as null
  Animal my_animal;

  try {

    my_animal.speak();  // it is null, so this should throw

    std::cout << "Something went wrong!\n";

  } catch ( const std::runtime_error& e ) {

    std::cout << e.what() << '\n';
  }

  // Let's put an animal in there!

  my_animal = zoo::Horse {};

  my_animal.speak();

  // Now let's reassign it!

  my_animal = zoo::Dog {};

  my_animal.speak();  // will "woof" because there is a dog in there!

  // What about another Animal?
  Animal another_animal(zoo::Sheep {});

  another_animal.speak();

  // What about assigning an animal to another?
  my_animal = another_animal;

  my_animal.speak();  // will "baa" like the sheep that's in there!

  // And we don't need to do any cleanup ourselves!
  return 0;
}
