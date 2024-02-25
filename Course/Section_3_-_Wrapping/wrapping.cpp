#include <iostream>
#include <stdexcept>

#include "Animal.hpp"
#include "zoo.hpp"

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
