#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Verification de l'extension de l'entrée (Json ou XML)
int verifierInput(int argc,char const *argv[])
	{
		int i;
		for (i = 1; i < argc ; i++)
		{
			if(strcmp("-i",argv[i])==0)
				{  
					//Verification de l'input i
					if(i+1<argc)   // Verifier le format du fichier
						{
							if(strcmp("xml",argv[i+1])==0)// Pour un fichier xml
								{
									
									return 1;
								}
							else if (strcmp("json",argv[i+1])==0) // Pour un fichier json
								{
									
									return 2;
								}
						}
				}
		}
		return 0;
	}

//Verification de la trace 
int Trace(int argc,char const *argv[])
	{
		int i;
		for (i = 1; i < argc ; i++)
			{
				if(strcmp("-t",argv[i])==0)
					{
						return 1;
					}
			}
		return 0;
	}

//Vérification du fichier de sortie qui a pour extension '.svg'
int verifierOutput(int argc,char const *argv[])
	{

		int i;
		int t;
		for (i = 1; i < argc ; i++)
			{
				if(strcmp("-o",argv[i])==0)
					{
            					if(i+1<argc)
							{
								t = strlen(argv[i+1]);
								if(t>4)
									{
            		
										if(argv[i+1][t-1]=='g' && argv[i+1][t-2]=='v' && argv[i+1][t-3]=='s' && argv[i+1][t-4]=='.')
											{
												return 1;
            										}
            								}
          						}
					}
			}
			return 0;
	}

//Recupère le nom du fichier de sortie
char* getName(int argc,char const *argv[])
	{
		int i;
		for (i = 1; i < argc ; i++)
			{
				if(strcmp("-o",argv[i])==0)
					{
						return (char *)argv[i+1];
					}
			}
		return NULL;
	}

//Recupere le nom du l'input si c'est un fichier
char* Input_Fichier_Flux(int argc,char const *argv[])
	{
		int i;
		for (i = 1; i < argc ; i++)
			{
				if(strcmp("-f",argv[i])==0 || strcmp("-h",argv[i])==0 )
					{
						return (char *)argv[i+1];
					}
			}
		return 0;
	}

//Recupere le nom de l'input si c'est un flux http
/*char* Input_Flux(int argc,char const *argv[])
	{
		int i;
		for (i = 1; i < argc ; i++)
			{
				if(strcmp("-h",argv[i])==0)
					{
		  				return (char *)argv[i+1];
					}
			}
	return 0 ;
	}	*/
	

int main(int argc,char const *argv[])
{
	
	int failed = 0;
	if (!verifierInput(argc,argv))
		{
		printf("Vous n'avez pas renseinger l'option -i [-i xml/json]\n");
		failed=1;
	}
	
	if (!verifierOutput(argc,argv))
		{
		printf("Vous n'avez pas renseiger l'option -o [-o nomfichier.svg]\n");
		failed=1;
	}
	if (!Input_Fichier_Flux(argc,argv))
		{
		printf("Vous n'avez pas renseinger l'option -f [-f FichierInput] ou -h [-h url_HTTP]\n");
		failed=1;
	}
	/*if (!Input_Flux(argc,argv))
		{
		printf("Vous n'avez pas renseinger l'option -h [-h url_HTTP]\n");
		failed=1;
	}	*/


	if(!failed) {
		FILE* file = NULL;
		file = fopen(getName(argc,argv),"w+");
		if(Trace(argc,argv)==1)
			{
			printf("Success.\nLes traces seront affichées.\n ");
		}
		else
			printf("Success\nLes traces ne seront pas affichées\n");
	}
	return 0;
}
