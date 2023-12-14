#include <iostream>
#include <string_view>
#include <vector>

// Here is our existing inheritance tree
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

class Cat : public Animal
{

public:

  Cat() = default;
  Cat(const Cat&) = default;
  Cat(Cat&&) = default;
  Cat& operator=(const Cat&) = default;
  Cat& operator=(Cat&&) = default;
  ~Cat() override = default;

  void speak() const override
  {
    std::cout << "Meow!\n";
  }

  bool can_eat(std::string_view food) const override
  {
    return food == "cat food";
  }
};

class Dog : public Animal
{

public:

  Dog() = default;
  Dog(const Dog&) = default;
  Dog(Dog&&) = default;
  Dog& operator=(const Dog&) = default;
  Dog& operator=(Dog&&) = default;
  ~Dog() override = default;

  void speak() const override
  {
    std::cout << "Woof!\n";
  }

  bool can_eat(std::string_view food) const override
  {
    return food == "dog food";
  }
};

// and here are our animals that doesn't inherit from `Animal`

namespace lib {
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
}  // namespace lib

// We can write an AnimalWrapper that can handle Horse, Sheep,
// as well as whatever else implements the right interface!
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

  myAnimals.emplace_back(new Cat {});
  myAnimals.emplace_back(new Dog {});

  // Huzzah! Our template works!
  myAnimals.emplace_back(new Animal_Wrapper<lib::Horse> {});
  myAnimals.emplace_back(new Animal_Wrapper<lib::Sheep> {});

  for ( Animal* animal : myAnimals ) {
    animal->speak();
    std::cout << "Can this animal eat grass? " << std::boolalpha
              << animal->can_eat("grass") << '\n';
    delete animal;
  }
}
