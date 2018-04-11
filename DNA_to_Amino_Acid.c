#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* const codon_table[4][4][4] =
{
  {
    {"Phe", "Phe", "Leu", "Leu"},
    {"Ser", "Ser", "Ser", "Ser"},
    {"Tyr", "Tyr", "Stop", "Stop"},
    {"Cys", "Cys", "Stop", "Trp"}
  },
  {
    {"Leu", "Leu", "Leu", "Leu"},
    {"Pro", "Pro", "Pro", "Pro"},
    {"His", "His", "Gln", "Gln"},
    {"Arg", "Arg", "Arg", "Arg"}
  },
  {
    {"Ile", "Ile", "Ile", "Met"},
    {"Thr", "Thr", "Thr", "Thr"},
    {"Asn", "Asn", "Lys", "Lys"},
    {"Ser", "Ser", "Arg", "Arg"}
  },
  {
    {"Val", "Val", "Val", "Val"},
    {"Ala", "Ala", "Ala", "Ala"},
    {"Asp", "Asp", "Glu", "Glu"},
    {"Gly", "Gly", "Gly", "Gly"}
  }
};

int check_nucleobase_array(char* nucleobase_array, size_t nucleobase_count)
{
  if(nucleobase_array == NULL)
  {
    return 1;
  }

  for(size_t i = 0; i < nucleobase_count; ++i)
  {
    if(nucleobase_array[i] < 0 || nucleobase_array[i] > 3)
    {
      return 0;
    }
  }
  return 1;
}

size_t nucleobase_to_aminoacid(char* nucleobase_array, size_t nucleobase_count, char*** aminoacid_array)
{
  if(nucleobase_array == NULL)
  {
    return 1;
  }

  size_t aminoacid_count = nucleobase_count/3;

  (*aminoacid_array) = malloc(aminoacid_count * sizeof(**aminoacid_array));

  for(size_t i = 0, slow_i = 0; slow_i < aminoacid_count; i+=3, slow_i+=1)
  {
    (*aminoacid_array)[slow_i] = codon_table[
        (size_t)nucleobase_array[i]
      ][
        (size_t)nucleobase_array[i+1]
      ][
        (size_t)nucleobase_array[i+2]
      ];
  }

  return aminoacid_count;
}

int main()
{
  printf("Enter DNA sequence in 5' → 3' direction.\n");

  char* input_string = NULL;
  size_t n = 0;
  ssize_t line_length = getline(&input_string, &n, stdin);
  if(line_length == -1)
  {
    printf("Failed to read a line.\n");
    return 0;
  }

  char* nucleobase_array = malloc(line_length);
  size_t nucleobase_count;
  for(nucleobase_count = 0; input_string[nucleobase_count]!='\n'; ++nucleobase_count)
  {
    nucleobase_array[nucleobase_count] =
      input_string[nucleobase_count] == 't' ? 0 :
      input_string[nucleobase_count] == 'c' ? 1 :
      input_string[nucleobase_count] == 'a' ? 2 :
      input_string[nucleobase_count] == 'g' ? 3 : -1;
  }

  if(!check_nucleobase_array(nucleobase_array, nucleobase_count))
  {
    printf("Erroneous input: %s\n", input_string);
    return 0;
  }

  char** aminoacid_array = NULL;
  size_t aminoacid_count = nucleobase_to_aminoacid(nucleobase_array, nucleobase_count, &aminoacid_array);

  for(size_t i = 0; i < aminoacid_count; ++i)
  {
    if(i!=0)
    {
      printf(" + ");
    }
    printf("%s", aminoacid_array[i]);
  }
  printf("\n");

  free(input_string);
  free(aminoacid_array);

  return 0;
};
