#include <iostream>
#include <memory>
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

class Horse : public Animal
{

public:

  Horse() = default;
  Horse(const Horse&) = default;
  Horse(Horse&&) = default;
  Horse& operator=(const Horse&) = default;
  Horse& operator=(Horse&&) = default;
  ~Horse() override = default;

  void speak() const override
  {
    std::cout << "Neigh!\n";
  }

  bool can_eat(std::string_view food) const override
  {
    return food == "hay";
  }
};

// and here is our Sheep that doesn't inherit from `Animal`

namespace zoo {
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

// but we can make a Sheep_Wrapper that does!
class Sheep_Wrapper : public Animal
{
private:

  // we hold onto a real sheep
  zoo::Sheep wrapped_sheep;

public:

  Sheep_Wrapper() = default;

  // we make a constructor that takes a sheep
  explicit Sheep_Wrapper(zoo::Sheep sheep)
      : wrapped_sheep {sheep}  // in real code,
  // you should move or forward in the sheep
  // but this is just an introduction
  { }

  Sheep_Wrapper(const Sheep_Wrapper&) = delete;
  Sheep_Wrapper(Sheep_Wrapper&&) = delete;
  Sheep_Wrapper& operator=(const Sheep_Wrapper&) = delete;
  Sheep_Wrapper& operator=(Sheep_Wrapper&&) = delete;
  ~Sheep_Wrapper() override = default;

  // and we just implement the Animal interface by calling
  // the member functions of the real Sheep!
  void speak() const override
  {
    wrapped_sheep.speak();
  }

  bool can_eat(std::string_view food) const override
  {
    return wrapped_sheep.can_eat(food);
  }
};

int main()
{
  std::vector<Animal*> myAnimals;

  myAnimals.emplace_back(new Cat {});
  myAnimals.emplace_back(new Dog {});
  myAnimals.emplace_back(new Horse {});

  // This would not work, because Sheep does not inherit from Animal
  // myAnimals.emplace_back(new Sheep {});

  // but this does work!
  // Because Sheep_Wrapper does inherit from Animal!
  myAnimals.emplace_back(new Sheep_Wrapper {});

  for ( Animal* animal : myAnimals ) {
    animal->speak();
    std::cout << "Can this animal eat grass? " << std::boolalpha
              << animal->can_eat("grass") << '\n';
    delete animal;
  }
}
