#include <iostream>
#include <string>

template <typename T>
T add(const T& a, const T& b)
{
  return a + b;
}

// NOLINTBEGIN(cppcoreguidelines-special-member-functions)

class Base
{
public:

  Base() = default;
  virtual ~Base() = default;

  virtual void foo()
  {
    std::cout << "Hello from base!\n";
  };
};

class Derived_A
{
public:

  Derived_A() = default;
  virtual ~Derived_A() = default;

  virtual void foo()
  {
    std::cout << "Hello from derived A!\n";
  };
};

class Derived_B
{
public:

  Derived_B() = default;
  virtual ~Derived_B() = default;

  virtual void foo()
  {
    std::cout << "Hello from derived B!\n";
  };
};

// NOLINTEND(cppcoreguidelines-special-member-functions)

int main()
{
  std::cout << "Adding 1 and 8: " << add(1, 8) << '\n';

  using namespace std::literals;
  std::cout << "Adding \"Hello \" and \"World \": "
            << add<std::string>("Hello", "World") << '\n';
}
