#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Verifier les paramétres d'entrées(Json ou XML)
int verifierInput(int argc,char const *argv[]){
	int i;
	for (i = 1; i < argc ; i++)
	{
		if(strcmp("-i",argv[i])==0){ //Verification de l'input i
            if(i+1<argc){
            	if(strcmp("xml",argv[i+1])==0 ){// Pour un fichier xml
            		return 1;
            	}else if (strcmp("json",argv[i+1])==0){// Pour un fichier json
            		return 2;
            	}
            }
		}
	}
	return 0;
}
//Verifier la trace 
int Trace(int argc,char const *argv[]){
	int i;
	for (i = 1; i < argc ; i++)
	{
		if(strcmp("-t",argv[i])==0){
            return 1;
		}
	}
	return 0;
}
//
int verifierOutput(int argc,char const *argv[]){

	int i;
	int t;
	for (i = 1; i < argc ; i++)
	{
		if(strcmp("-o",argv[i])==0){
            if(i+1<argc){
            	t = strlen(argv[i+1]);
            	if(t>4){
            		
            		if(argv[i+1][t-1]=='g' && argv[i+1][t-2]=='v' && argv[i+1][t-3]=='s' && argv[i+1][t-4]=='.'){
            			return 1;
            		}
            	}
            }
		}
	}
	return 0;
}
char* getName(int argc,char const *argv[]){
	int i;
	for (i = 1; i < argc ; i++)
	{
		if(strcmp("-o",argv[i])==0){
			return (char *)argv[i+1];
		}
	}
	return NULL;
}
char* Input_Fichier(int argc,char const *argv[]){
	int i;
	for (i = 1; i < argc ; i++)
	{
		if(strcmp("-f",argv[i])==0){



			return (char *)argv[i+1];
		}
	}
	return 0;
}
char* Input_Flux(int argc,char const *argv[]){
	int i;
	for (i = 1; i < argc ; i++)
	{
		if(strcmp("-h",argv[i])==0){
		  }	return (char *)argv[i+1];
		}
	}
	return 0 ;
}
int main(int argc,char const *argv[])
{
	
	int failed = 0;
	if(!verifierInput(argc,argv)){
		printf("Vous n'avez renseinger l'option -i [-i xml/json]\n");
		failed=1;
	}
	if(!verifierOutput(argc,argv)){
		printf("Vous n'avez renseinger l'option -o [-o nomfichier.svg]\n");
		failed=1;
	}
	if(!verifierInput(argc,argv)){
		printf("Vous n'avez renseinger l'option -f [-f FichierInput]\n");
		failed=1;
	}
	if(!verifierInput(argc,argv)){
		printf("Vous n'avez renseinger l'option -h [-h url_HTTP]\n");
		failed=1;
		}	


	if(!failed){
		FILE* file = NULL;
		file = fopen(getName(argc,argv),"w+");
		printf("Bravo vous avez avez reussit\n");
		if(Trace(argc,argv)){
			printf("Affichage de la trace !");
		}
	}
	return 0;
}
