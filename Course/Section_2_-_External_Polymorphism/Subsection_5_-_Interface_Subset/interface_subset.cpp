#include <iostream>
#include <string_view>
#include <vector>

namespace lib {
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

  void meow() const
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

  void bark() const
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

  bool m_is_being_ridden = false;

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

  // return success/error
  bool ride()
  {
    if ( ! m_is_being_ridden ) {
      m_is_being_ridden = true;
      return true;
    } else {
      return false;
    }
  }

  // return success/error
  bool stop_riding()
  {
    if ( m_is_being_ridden ) {
      m_is_being_ridden = false;
      return true;
    } else {
      return false;
    }
  }

  bool is_being_ridden() const
  {
    return m_is_being_ridden;
  }

  bool can_eat(std::string_view food) const
  {
    return food == "hay";
  }
};

class Sheep
{

  bool m_is_woolly = true;

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

  // return success/error
  bool shear()
  {
    if ( m_is_woolly ) {
      m_is_woolly = false;
      return true;
    } else {
      return false;
    }
  }

  void wait_for_wool_to_grow()
  {
    m_is_woolly = true;
  }

  bool can_eat(std::string_view food) const
  {
    return food == "grass";
  }
};
}  // namespace lib

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
  myAnimals.emplace_back(new Animal_Wrapper<lib::Cat> {});
  myAnimals.emplace_back(new Animal_Wrapper<lib::Dog> {});
  myAnimals.emplace_back(new Animal_Wrapper<lib::Horse> {});
  myAnimals.emplace_back(new Animal_Wrapper<lib::Sheep> {});

  for ( Animal* animal : myAnimals ) {
    animal->speak();
    std::cout << "Can this animal eat grass? " << std::boolalpha
              << animal->can_eat("grass") << '\n';
    delete animal;
  }
}
