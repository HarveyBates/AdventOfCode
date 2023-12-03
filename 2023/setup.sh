#!/bin/bash

dir_name=""

while getopts d:h-: flag; do
  case "${flag}" in
    d) 
      dir_name="${OPTARG}" ;;
    h) 
      echo "-h			Show help information."
      echo "-d    	Day (creates folder with this name)."
      exit 0
      ;;
    \?) 
      echo "Invalid option: -"{$OPTARG}"" >&3
      exit 1 ;;
    :)
      echo "Option -{$OPTARG} requires an argument" >&2
      exit 1 ;;
  esac
done

shift "$(( OPTIND - 1))"

# Check directory name was supplied
if [[ "$dir_name" == "" ]]; then
  echo "Directory name (-d) not provided. Exiting."
  exit 1
fi

# Check if directory already exists
if [[ -d "$dir_name" ]]; then
  echo "Directory already exists. Exiting"
  exit 1
fi

# Setup directory with base files
mkdir "$dir_name"
touch "${dir_name}/main.c"
touch "${dir_name}/input.txt"

# Default main.c setup
echo "// AOC: ${dir_name}
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 1024

void solve_pt1(const char* filename) {
  char line[LINE_LEN];
  int answer = 0;

  FILE* file = fopen(filename, \"r\");
  if (!file) {
    return;
  }

  while (fgets(line, sizeof(line), file)) {
    printf(\"%s\\n\", line);
  }

  fclose(file);
  printf(\"Part 1: %d\\n\", answer);
}

int main(){
  const char* filename = \"input.txt\";
  solve_pt1(filename);
  return 0;
}" >> "${dir_name}/main.c"

cd "$dir_name"
