#include <iostream>
#include <memory>
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

  virtual void foo() = 0;
};

class Derived_A final : public Base
{
public:

  Derived_A() = default;
  ~Derived_A() final = default;

  void foo() final
  {
    std::cout << "Hello from derived A!\n";
  };
};

class Derived_B final : public Base
{
public:

  Derived_B() = default;
  ~Derived_B() final = default;

  void foo() final
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
            << add<std::string>("Hello ", "World") << '\n';

  std::unique_ptr<Base> A {new Derived_A};
  std::unique_ptr<Base> B {new Derived_B};

  A->foo();
  B->foo();
}
