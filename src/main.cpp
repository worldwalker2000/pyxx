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

void ungetc(std::ifstream& input)
{
  input.unget();
}

void consume(std::ifstream& input, int n = 1)
{
  for (int i = 0; i < n; ++i) {
    getc(input);
  }
}

void consume_all(std::ifstream& input, char what)
{
  while(peekc(input) == what) {
    getc(input);
  }
}

// not including
void consume_until(std::ifstream& input, char what)
{
  while(peekc(input) != what) {
    getc(input);
  }
}

bool detect_word(char current, std::ifstream& input, std::string word)
{
  bool found = true;
  if (current != word[0]) found = false;

  int n_walked = 0;
  for (size_t i = 1; i < word.length(); ++i) {
    if ((int) peekc(input) == EOF) {
      found = false;
      break;
    }
    if (word[i] != getc(input)) {
      found = false;
    }
    ++n_walked;
  }

  for (int i = 0; i < n_walked; ++i) {
    ungetc(input);
  }

  return found;
}

void parse(std::ifstream& input, std::vector<std::pair<int, std::string>>& lines, int tabs = 0, int lambdas = 0, bool main_parser = true)
{
  int starting_tab = tabs;
  bool can_return = false;

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
        if (current != ';' && current != '{' && current != '}' && current != '\n') {
          if (detect_word(current, input, "++")) {
            current_line << " += 1";
            consume(input); // consume extra +
          } else if (detect_word(current, input, "--")) {
            current_line << " -= 1";
            consume(input); // consume extra +
          } else if (current == '!' && peekc(input) != '=') {
            current_line << "not ";
          } else if (detect_word(current, input, "&&")) {
            current_line << "and";
            consume(input); // consume extra &
          } else if (detect_word(current, input, "||")) {
            current_line << "or";
            consume(input); // consume extra |
          } else if (detect_word(current, input, "true")) {
            current_line << "True";
            consume(input, 3); // consume rest of true or just rue
          } else if (detect_word(current, input, "false")) {
            current_line << "False";
            consume(input, 4); // consume rest of false or just alse
          } else if (detect_word(current, input, "  ")) { // this may seem strange but its to get rid of tons of extra spaces preceding a { like in the funkybraces.pyxx test file
            current_line << " ";
            consume_all(input, ' '); // consume all extra ' '
          } else if(detect_word(current, input, "lambda")) {
            current_line << "lambda_func_" << ++lambdas;

            consume_until(input, '(');
            std::stringstream func;
            func << "def lambda_func_" << lambdas;
            char c;
            while ((c = getc(input)) != ')') {
              func << c;
            }
            func << ")";

            lines.push_back(std::make_pair(tabs, func.str()));

            parse(input, lines, tabs, lambdas, false);

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

        if (current == '\n') {
          break;
        }
      }
    }

    // debug
    // std::cout << current_line.str() << std::endl;

    std::string line = current_line.str();
    if (line == ":") {
      lines[lines.size() - 1].second += ":"; // so that you can put the { on the next line
    } else {
      lines.push_back(std::make_pair(tabs, current_line.str()));
    }

    tabs += tab_change;
    if (tab_change > 0) {
      can_return = true;
    }

    if (!main_parser && can_return && tabs == starting_tab) {
      return;
    }
  }
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

    parse(input, lines);

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
