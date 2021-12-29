#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* read_file(char* path)
{
  FILE* file = fopen(path, "r");
  if(file == NULL) {
    fprintf(stderr, "Failed to load file %s.\n", path);
    exit(1);
  }

  fseek(file, 0, SEEK_END);
  unsigned long file_length = ftell(file);
  fseek(file, 0, SEEK_SET);

  char* buffer = (char*) malloc(file_length + 1); // +1 for null terminator
  if(buffer == NULL) {
    fprintf(stderr, "Failed to make buffer for reading file %s.\n", path);
    exit(1);
  }

  if(fread(buffer, 1, file_length, file) != file_length) {
    fprintf(stderr, "Failed to read file %s.\n", path);
    exit(1);
  }

  buffer[file_length] = '\0'; // Add null terminator to end of buffer so it plays nice

  fclose(file);

  return buffer;
}

int main(int argc, char** argv)
{
  ++argv; // skip program path
  --argc;

  while (argc > 0) {
    char* name = *argv++;
    char* program = read_file(name);

    // debug
    // printf("File:\n%s\n", program);

    name[strlen(name) - 2]  ='\0';
    FILE* output = fopen(name, "w");

    int curr = 0;
    int tabs = 0;
    bool in_quotes = false;
    bool in_meat = false; // the "meat" of the line is the actual code not the spaces or tabs infront
    char c;
    while ((c = program[curr++]) != '\0') {
      if (c == ';') {
        // ignore ;
      } else if (c == '{') {
        fputc(':', output);
        ++tabs;
      } else if (c == '}') {
        --tabs;
      } else if (c == '\n') {
        fputc('\n', output);
        in_meat = false;
      } else if(c == '"') {
        fputc('"', output);
        in_quotes = !in_quotes;
      } else if(c == ' ') {
        if (in_meat || in_quotes) fputc(' ', output);
      } else if (c == '+') {
        if (program[curr] == '+') { // just curr not curr +1 because curr gets incremented in the loop head thus curr already is the next char
          fputc('+', output);
          fputc('=', output);
          fputc('1', output);
          ++curr; // skip next plus
        } else fputc('+', output);
      } else if (c == '-') {
        if (program[curr] == '-') { // just curr not curr +1 because curr gets incremented in the loop head thus curr already is the next char
          fputc('-', output);
          fputc('=', output);
          fputc('1', output);
          ++curr; // skip next plus
        } else fputc('-', output);
      } else {
        if (!in_meat) {
          in_meat = true;
          for (int i = 0; i < tabs; ++i) fputc('\t', output);
        }
        fputc(c, output);
      }
    }
    
    fclose(output);
    
    free(program);
    --argc;
  }

  return 0;
}
