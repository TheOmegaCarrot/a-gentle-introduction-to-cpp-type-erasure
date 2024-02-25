#include <iostream>
#include <stdexcept>

#include "Animal.hpp"
#include "zoo.hpp"

class not_an_animal
{

  void speak()
  {
    std::cout << "I don't have a can_eat member function!\n";
  }
};

int main()
{
  // Let's see how this can go wrong!

  // It can start out as null
  Animal my_animal;

  my_animal = not_an_animal {};

  return 0;
}
