#include <iostream>
#include <string_view>

namespace zoo {
class Cat
{

public:

  Cat() = default;
  Cat(const Cat&) = default;
  Cat(Cat&&) = default;
  Cat& operator=(const Cat&) = default;
  Cat& operator=(Cat&&) = default;
  ~Cat() = default;

  void speak() const
  {
    std::cout << "Meow!\n";
  }

  bool can_eat(std::string_view food) const
  {
    return food == "cat food";
  }
};

class Dog
{

public:

  Dog() = default;
  Dog(const Dog&) = default;
  Dog(Dog&&) = default;
  Dog& operator=(const Dog&) = default;
  Dog& operator=(Dog&&) = default;
  ~Dog() = default;

  void speak() const
  {
    std::cout << "Woof!\n";
  }

  bool can_eat(std::string_view food) const
  {
    return food == "dog food";
  }
};

class Horse
{

public:

  Horse() = default;
  Horse(const Horse&) = default;
  Horse(Horse&&) = default;
  Horse& operator=(const Horse&) = default;
  Horse& operator=(Horse&&) = default;
  ~Horse() = default;

  void speak() const
  {
    std::cout << "Neigh!\n";
  }

  bool can_eat(std::string_view food) const
  {
    return food == "hay";
  }
};

class Sheep
{

public:

  Sheep() = default;
  Sheep(const Sheep&) = default;
  Sheep(Sheep&&) = default;
  Sheep& operator=(const Sheep&) = default;
  Sheep& operator=(Sheep&&) = default;
  ~Sheep() = default;

  void speak() const
  {
    std::cout << "Baa!\n";
  }

  bool can_eat(std::string_view food) const
  {
    return food == "grass";
  }
};
}  // namespace zoo
