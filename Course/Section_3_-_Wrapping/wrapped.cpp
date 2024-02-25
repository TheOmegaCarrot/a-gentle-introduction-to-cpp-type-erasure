#include <iostream>
#include <string_view>
#include <vector>

#include "zoo.hpp"

// We can write the parent of our new inheritance tree!
class Animal
{

public:

  Animal() = default;
  Animal(const Animal&) = default;
  Animal(Animal&&) = default;
  Animal& operator=(const Animal&) = default;
  Animal& operator=(Animal&&) = default;
  virtual ~Animal() = default;

  // here is our interface
  virtual void speak() const = 0;
  virtual bool can_eat(std::string_view) const = 0;
};

// This is the same template as before!
template <typename T>
class Animal_Wrapper : public Animal
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
};

int main()
{
  std::vector<Animal*> myAnimals;

  // All of these library types are doing polymorphism without them
  // inheriting from a common parent!
  myAnimals.emplace_back(new Animal_Wrapper<zoo::Cat> {});
  myAnimals.emplace_back(new Animal_Wrapper<zoo::Dog> {});
  myAnimals.emplace_back(new Animal_Wrapper<zoo::Horse> {});
  myAnimals.emplace_back(new Animal_Wrapper<zoo::Sheep> {});

  for ( Animal* animal : myAnimals ) {
    animal->speak();
    std::cout << "Can this animal eat grass? " << std::boolalpha
              << animal->can_eat("grass") << '\n';
    delete animal;
  }
}
