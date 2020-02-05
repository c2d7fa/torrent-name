#include <stdio.h>
#include <stdbool.h>

struct parse_result {
  bool success;
  char* name;
};

struct parse_result parse_file(FILE* file);

int main(int argc, char* argv[]) {
  if (argc != 2) {  // argv[0] is program name
    printf("Error: Expected exactly 1 argument, given %d\n", argc - 1);
    return 3;
  }

  char* filename = argv[1];

  FILE* file = fopen(filename, "r");

  if (!file) {
    printf("Error: Could not open the file '%s' for reading\n", filename);
    return 1;
  }

  struct parse_result result = parse_file(file);

  if (!result.success) {
    printf("Error: Could not parse '%s' as .torrent file\n", filename);
  } else {
    puts(result.name);
  }

  bool error = fclose(file) != 0;

  if (error) {
    puts("Error: Unexpected error while closing file\n");
    return 2;
  }

  if (result.success) {
    return 0;
  } else {
    return 4;
  }
}

// Returned name is valid until next call to parse_file.
struct parse_result parse_file(FILE* file) {
  static char buffer[0x1000];

  static const char* trigger = "4:name";

  // Search for 4:name
  int found = 0;
  while (trigger[found] != '\0') {
    int ch = fgetc(file);
    if (ch == EOF) return (struct parse_result){false};

    if (ch == trigger[found]) {
      found++;
    } else {
      found = 0;
      if (ch == trigger[found]) {
        found++;
      }
    }
  }

  // Now we read the length of the name
  int length;
  fscanf(file, "%ud", &length);

  // Then we read the name itself
  fgetc(file); // Skip ':'
  fgets(buffer, length + 1, file);

  return (struct parse_result){true, buffer};
}

