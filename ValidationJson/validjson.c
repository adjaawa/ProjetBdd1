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
  JSON_checker jc = new_JSON_checker(20); //new_JSON_checker commence le processus de verification en creant un objet JSON_checker jc
 //Il prend en paramètre un entier qui designe le nombre maximum d'emboitements
  while ((c = fgetc(fic)) != EOF) //While ths stream is not at the end of file
    {
        if (c <= 0) {
            break;
        }
        if (!JSON_checker_char(jc, c)) { //Verifie chaque caractère. S'il retourner 'faux', un message d'erreur et l'objet est detruit
            fprintf(stderr, "JSON_checker_char: syntax error\n");
            exit(1);     
        }
        else
        	printf("format valide\n");
        	exit(1);        
    }
  fclose(fic); //Fermeture du fichier
  if (!JSON_checker_done(jc)) { /* Si chaque appelle de la fonction Json_checker_char a retourné 'vrai', la fonction Json_checker_done
  supprime le Json_checker et retourne vrai si le test Json est valide. Sinon, un message d'erreur.*/
        fprintf(stderr, "JSON_checker_end: syntax error\n");
        exit(1);
    	}
    	else 
    		printf("format valide");
    		exit(1);
  return(EXIT_SUCCESS);
}
