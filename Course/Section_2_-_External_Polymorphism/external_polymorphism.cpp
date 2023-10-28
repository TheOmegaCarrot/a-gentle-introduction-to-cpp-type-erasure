#include <iostream>

class Animal
{

public:

  Animal() = default;
  Animal(const Animal&) = delete;
  Animal(Animal&&) = delete;
  Animal& operator=(const Animal&) = delete;
  Animal& operator=(Animal&&) = delete;
  virtual ~Animal() = default;

  // here is our interface
  virtual void speak() const = 0;
};

class Cat : public Animal
{

public:

  Cat() = default;
  Cat(const Cat&) = delete;
  Cat(Cat&&) = delete;
  Cat& operator=(const Cat&) = delete;
  Cat& operator=(Cat&&) = delete;
  ~Cat() override = default;

  void speak() const override
  {
    std::cout << "Meow!\n";
  }
};

class Dog : public Animal
{

public:

  Dog() = default;
  Dog(const Dog&) = delete;
  Dog(Dog&&) = delete;
  Dog& operator=(const Dog&) = delete;
  Dog& operator=(Dog&&) = delete;
  ~Dog() override = default;

  void speak() const override
  {
    std::cout << "Woof!\n";
  }
};

class Horse : public Animal
{

public:

  Horse() = default;
  Horse(const Horse&) = delete;
  Horse(Horse&&) = delete;
  Horse& operator=(const Horse&) = delete;
  Horse& operator=(Horse&&) = delete;
  ~Horse() override = default;

  void speak() const override
  {
    std::cout << "Neigh!\n";
  }
};
