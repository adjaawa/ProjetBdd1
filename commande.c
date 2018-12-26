#include<stdio.h>
#include<stdlib.h>
#define MIN_REQUIRED 8 /*Nombre minimum de paramètres*/

int main(int argc, char const *argv[]) {
     if (argc < MIN_REQUIRED) {
      printf("Erreur syntaxique");
   }

    int i;
    for (i=0;i<argc;i++) {
        printf("%s\n",argv[i]);
    }
    return 0;
}
