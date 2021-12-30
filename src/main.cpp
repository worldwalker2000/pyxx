#include <iostream>
#include <string>
#include <fstream>

char getc(std::ifstream& input)
{
  char c;
  input.get(c);

  return c;
}

// I know that this function is worthless but it keeps the code consistent
char peekc(std::ifstream& input)
{
  return input.peek();
}

int main(int argc, char** argv)
{
  ++argv;
  --argc;

  while (argc > 0) {
    std::string name = *argv++;

    std::ifstream input(name, std::ios::in);
    if (!input.is_open()) std::cout << "Failed to open file " << name << std::endl;

    std::string output_name = name.substr(0, name.length() - 2);
    std::ofstream output(output_name, std::ios::out);
    if (!output.is_open()) std::cout << "Failed to open file " << output_name << std::endl;

    int tabs = 0;
    bool in_quotes = false;
    bool in_meat = false;

    while (input.good()) {
      char current = getc(input);

      auto normal = [&output, current, tabs, &in_meat]() {
        if (!in_meat) {
          in_meat = true;
          for (int i = 0; i < tabs; ++i) {
            output << "\t";
          }
        }

        output << current;
      };

      if (!in_quotes) {
        if (current == ';') {
          // ignore ;
        }
        else if (current == '{') {
          output << ":";
          ++tabs;
        }
        else if (current == '}') {
          --tabs;
        }
        else if (current == '\n') {
          output << "\n";
          in_meat = false;
        }
        else if (current == ' ') {
          if (in_quotes) std::cout << "ERROR" << std::endl;
          if (in_meat) output << " ";
        }
        else if (current == '+') {
          if (peekc(input) == '+') {
            output << "+=1";
            getc(input); // consume the next +
          } else {
            normal();
          }
        }
        else if (current == '-') {
          if (peekc(input) == '-') {
            output << "-=1";
            getc(input); // consume the next -
          } else {
            normal();
          }
        }
        else if (current == '!') {
          if (peekc(input) != '=' && (peekc(input) == '!' || peekc(input) == 'T' || peekc(input) == 'F')) { // this is a mess
            output << "not ";
          } else {
            normal();
          }
        }
        else if (current == '&') {
          if (peekc(input) == '&') {
            output << "and";
            getc(input); // consume the next &
          } else {
            normal();
          }
        }
        else if (current == '|') {
          if (peekc(input) == '|') {
            output << "or";
            getc(input); // consume the next |
          } else {
            normal();
          }
        } else if (current == '"' || current == '\'') {
          output << current;
          in_quotes = true;
        } else {
          normal();
        }
      } else { // in quotes
        if (current == '\\') {
          if (peekc(input) == '"' || peekc(input) == '\'') {
            output << "\\" << getc(input); // consume the " or '
          } else {
            normal();
          }
        }
        else if (current == '"' || current == '\'') {
          output << current;
          in_quotes = false;
        } else {
          normal();
        }
      }
    }

    --argc;
  }


  return 0;
}
