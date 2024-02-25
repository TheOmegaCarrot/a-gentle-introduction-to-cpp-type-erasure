#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <stdexcept>
#include <string_view>

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

#endif
