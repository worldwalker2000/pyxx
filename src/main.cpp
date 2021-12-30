#include <iostream>
#include <string>
#include <fstream>

char getc(std::ifstream& input)
{
  char c;
  input.get(c);

  return c;
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
      char current;
      //char consumed;
      switch (current = getc(input)) {
        case ';':
          // ignore ;
          break;
        case '{':
          output << ":";
          ++tabs;
          break;
        case '}':
          --tabs;
          break;
        case '\n':
          output << "\n";
          in_meat = false;
          break;
        case '"':
          output << "\"";
          in_quotes = !in_quotes;
          break;
        case ' ':
          if (in_meat || in_quotes) output << " ";
          break;
        case '+': {
            char consumed;
            if ((consumed = getc(input)) == '+') {
              output << "+=1";
            } else {
              output << "+" << consumed;
            }
          }
          break;
        case '-': {
            char consumed;
            if ((consumed = getc(input)) == '-') {
              output << "-=1";
            } else {
              output << "-" << consumed;
            }
          }
          break;
        default:
          if (!in_meat) {
            in_meat = true;
            for (int i = 0; i < tabs; ++i) {
              output << "\t";
            }
          }

          output << current;
          break;
      }
    }

    --argc;
  }

  return 0;
}
