#include <iostream>
  using std::cout;
  using std::cerr;
  using std::endl;

#include <SFML/Graphics.hpp>

#include "termcolor.hpp"

#define PRINT_DEBUG cout << termcolor::green << "DEBUG :: " << __FILE__ << " :: " << __FUNCTION__ << " :: " << __LINE__ << termcolor::reset << "\n  -- "
#define PRINT_WARNING cout << termcolor::yellow << "WARNING :: " << __FILE__ << " :: " << __FUNCTION__ << " :: " << __LINE__ << termcolor::reset << "\n  -- "
#define PRINT_ERROR cout << termcolor::red << "ERROR :: " << __FILE__ << " :: " << __FUNCTION__ << " :: " << __LINE__ << termcolor::reset << "\n  -- "
