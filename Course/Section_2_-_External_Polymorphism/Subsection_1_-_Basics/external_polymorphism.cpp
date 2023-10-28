#include <iostream>
#include <memory>
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
};

// and here is our Sheep that doesn't inherit from `Animal`

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
};

// but we can make a SheepWrapper that does!
class SheepWrapper : public Animal
{
private:

  // we hold onto a real sheep
  Sheep wrappedSheep;

public:

  SheepWrapper() = default;

  // we make a constructor that takes a sheep
  explicit SheepWrapper(Sheep sheep)
      : wrappedSheep {sheep}  // in real code,
  // you should move or forward in the sheep
  // but this is just an introduction
  { }

  SheepWrapper(const SheepWrapper&) = delete;
  SheepWrapper(SheepWrapper&&) = delete;
  SheepWrapper& operator=(const SheepWrapper&) = delete;
  SheepWrapper& operator=(SheepWrapper&&) = delete;
  ~SheepWrapper() override = default;

  // and we just implement the Animal interface by calling
  // the member functions of the real Sheep!
  void speak() const override
  {
    wrappedSheep.speak();
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
  // Because SheepWrapper does inherit from Animal!
  myAnimals.emplace_back(new SheepWrapper {});

  for ( Animal* animal : myAnimals ) {
    animal->speak();
    delete animal;
  }
}
