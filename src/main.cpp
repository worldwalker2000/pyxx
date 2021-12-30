#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

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

    std::vector<std::pair<int, std::string>> lines;

    int tabs = 0;
    while (input.good() && !input.eof()) {
      char current;

      if (peekc(input) == '#') {
        while ((current = getc(input) != '\n')) {
          // just consume all the coment chars
        }
        
        continue;
      }

      std::stringstream current_line;

      bool in_quotes = false;

      int tab_change = 0;

      // clear out lines leading white space
      while (peekc(input) == ' ' || peekc(input) == '\t' | peekc(input) == '\n') {
        getc(input);
      }

      while ((current = getc(input)) > -1 && !input.eof()) {
        if (in_quotes) {
          bool escaped = false;
          if (current != '"' && !escaped) {
            current_line << current;
            
            if (current == '\\') {
              escaped = true;
            }
            if (escaped && current == '"') {
              escaped = false;
            }
          } else {
            current_line << '"';
            in_quotes = false;
          }
        } else { // not in quotes
          if (current != ';' && current != '{' && current != '}') {
            if (current == '+' && peekc(input) == '+') {
              current_line << " += 1";
              getc(input); // consume extra +
            } else if (current == '-' && peekc(input) == '-') {
              current_line << " -= 1";
              getc(input); // consume extra +
            } else if (current == '!' && peekc(input) != '=') {
              current_line << "not ";
            } else if (current == '&' && peekc(input) == '&') {
              current_line << "and";
              getc(input); // consume extra &
            } else if (current == '|' && peekc(input) == '|') {
              current_line << "or";
              getc(input); // consume extra |
            } else {
              current_line << current;

              if (current == '"') {
                in_quotes = true;
              } 
            }
          }

          if (current == ';') {
            break;
          }

          if (current == '{') {
            current_line << ':';
            tab_change = 1;
            break;
          }

          if (current == '}') {
            tab_change = -1;
            break;
          }
        }
      }

      // std::cout << current_line.str() << std::endl;

      lines.push_back(std::make_pair(tabs, current_line.str()));
      tabs += tab_change;
    }

    std::string output_name = name.substr(0, name.length() - 2);
    std::ofstream output(output_name, std::ios::out);
    if (!output.is_open()) std::cout << "Failed to open file " << output_name << std::endl;

    for (auto [tabs, line] : lines) {
      for (int i = 0; i < tabs; ++i) {
        output << '\t';
      }

      output << line << '\n';
      
      // debug
      // std::cout << tabs << "\t" << line << std::endl;
    }

    --argc;
  }


  return 0;
}
