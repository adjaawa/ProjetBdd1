#include <stdlib.h>
#include <stdio.h>
#include "JSON_checker.h"
int main(int argc, char* argv[]) {
FILE *fic;
int c;
 if (argc > 1)
    {
        fic = fopen (argv[1], "r"); //Ouverture du fichier
    }
  if (fic == NULL)
    {
      fprintf(stderr, "\nErreur: Impossible de lire le fichier \n");
      return(EXIT_FAILURE);
    }
  JSON_checker jc = new_JSON_checker(20);
  while ((c = fgetc(fic)) != EOF)
    {
        if (c <= 0) {
            break;
        }
        if (!JSON_checker_char(jc, c)) {
            fprintf(stderr, "JSON_checker_char: syntax error\n");
            exit(1);     
        }
        else
        	printf("format valide\n");
        	exit(1);        
    }
  fclose(fic);
  if (!JSON_checker_done(jc)) {
        fprintf(stderr, "JSON_checker_end: syntax error\n");
        exit(1);
    	}
    	else 
    		printf("format valide");
    		exit(1);
  return(EXIT_SUCCESS);
}