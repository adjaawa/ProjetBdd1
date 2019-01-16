#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <libxml/parser.h>
#include "JSON_checker.h"
// #include "ext.h"
#include "svg.c"
// declaration de la structure node
struct node *head = NULL;
int px=300 , py=50;
int test(svg* psvg,char *fileName)
{
    xmlDocPtr doc;
    xmlNode * roo_element = NULL;

    doc = xmlReadFile(fileName, NULL, XML_PARSE_NOBLANKS | XML_PARSE_NOERROR | XML_PARSE_NOWARNING | XML_PARSE_NONET);
    if (doc != NULL)
    {
        roo_element = xmlDocGetRootElement(doc);
//ON VERIFIE SI LE DOCUMENT CONTENANT LE CODE XML PASSE EN PARAMETRE EST VIDE
        if (roo_element != NULL)
        {
            return 1;
        }
        else{
        fprintf(stderr, "Document not parsed successfully.\n");
        return 0;
        }
    }
    else{
        printf("le fichier est nul\n");
        return 0;
    } 

    
    xmlFreeDoc(doc);       // free document
    xmlCleanupParser();    // Free globals

}

struct node {
	char *nomEntite;
	char *id;
	char *nom;
	char *prenom;
	char *association;
	char *date;

	struct node *next;
};

void insert(char *a, char *b, char *c, char *d, char *e, char *f){
        struct node *temp;
        temp = (struct node*)malloc(sizeof(struct node));
        temp->nomEntite = a;
        temp->id = b;
        temp->nom = c;
        temp->prenom = d;
        temp->association = e;
        temp->date = f;
        temp->next = head;
        head= temp;


}    

svg* svg_create(int width, int height)
{
    svg* psvg = malloc(sizeof(svg));

    if(psvg != NULL)
    {
        *psvg = (svg){.svg = NULL, .width = width, .height = height, .finalized = false};

        psvg->svg = malloc(1);

        sprintf(psvg->svg, "%s", "\0");

        appendstringtosvg(psvg, "<svg width='");
        appendnumbertosvg(psvg, width);
        appendstringtosvg(psvg, "px' height='");
        appendnumbertosvg(psvg, height);
        appendstringtosvg(psvg, "px' xmlns='http://www.w3.org/2000/svg' version='1.1' xmlns:xlink='http://www.w3.org/1999/xlink'>\n");

        return psvg;
    }
    else
    {
        return NULL;
    }
}

// extraction et génération pour xml
void traverse_dom_trees(svg* psvg,xmlNode * a_node)
{
    xmlNode *cur_node = NULL;
   
    for (cur_node = a_node; cur_node; cur_node = cur_node->next)
    {
               char *pol, *dev, *stat, *srcz, *dstz;
                if(strcmp((const char *)cur_node->name,(const char *)"nomEntite") == 0){
                       xmlChar *a = xmlNodeGetContent(cur_node);
                       printf("Nom entite: %s\n", a);
                       printf("jzjejejej\n");
           
                       svg_rectangle(psvg, 150, 90, px-15, py, "#FFFFFF", "#0000FF", 2, 2, 2);
                       svg_rectangle(psvg, 150, 90, px-15, py+34, "#FFFFFF", "#0000FF", 2, 2, 2);
                       svg_text(psvg, px+15, py+15, "sans-serif", 18, "#000000", "#000000",a);
                       py=py+300;
                       
                 }
	            else if(strcmp((const char *)cur_node->name,(const char *)"id") == 0)  {
                		 printf("je suis en dndnd\n");
	                    xmlChar *b = xmlNodeGetContent(cur_node);
	                        printf("ID : %s\n", b);
	                        
	                       svg_text(psvg, px+15, py-250, "sans-serif", 16, "#000000", "#000000",b);
	                       
	                        }
	            else if(strcmp((const char *)cur_node->name,(const char *)"nom") == 0){
	                    xmlChar *c = xmlNodeGetContent(cur_node);
	                        printf("NOM : %s\n", c);
	                        
	                        svg_text(psvg, px+15, py-225, "sans-serif", 16, "#000000", "#000000",c);
	                        
	                        }
	            else if(strcmp((const char *)cur_node->name,(const char *)"prenom") == 0){
	                    xmlChar *d = xmlNodeGetContent(cur_node);
                        printf("PRENOM : %s\n", d);
                        
                        svg_text(psvg, px+15, py-200, "sans-serif", 16, "#000000", "#000000",d);
                        
                        }
           
                else if(strcmp((const char *)cur_node->name,(const char *)"association") == 0){
                        xmlChar *e = xmlNodeGetContent(cur_node);
                         printf("ASSOCIATION : %s\n", e);
                         svg_ellipse(psvg, 360, 260, 75, 30, "#FFFFFF", "#0000FF", 2);
                         svg_text(psvg, px+18, py-390, "sans-serif", 18, "#000000", "#000000",e);
                         svg_line(psvg, "#0000FF", 2, 432, 265, 285, 265);
                         svg_line(psvg, "#0000FF", 2, 350, 230, 350, 175);
                         svg_line(psvg, "#0000FF", 2, 350, 350, 350, 288);
                        
                        }
               
                     
               else if(strcmp((const char *)cur_node->name,(const char *)"date") == 0){
                        xmlChar *f = xmlNodeGetContent(cur_node);
                         printf("DATE : %s\n", f);
                        }

        traverse_dom_trees(psvg,cur_node->children);
							    
    }
    
}
 //Json
/*int validateJson(char* filename) {
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
       /* fprintf(stderr, "JSON_checker_end: syntax error\n");
        exit(1);
      }
      else 
        printf("format valide");
        exit(1);
  return(EXIT_SUCCESS);
}
*/

int main(int argc, char *argv[])
{   
    /* Les options de la ligne de commande */
    int option;
    /* Variables nous permettant de compter le nombre de parametres renseignes par l'utilisateur */
    int count_i, count_h, count_f, count_o, count_t;
    count_i = count_h = count_f = count_o = 0, count_t = 0;

    /*Variable pour stocker le format saisi par l'utilisateur*/
    char * file_format;
    /*Variable pour stocker le nom du fichier en entree*/
    char * fichier_entree;
    /*Variable pour stocker le nom du fichier en sorti*/
    char * fichier_sortie;
    FILE* json_file = NULL;
    svg* psvg;
    /*if(argc <= 1)
        afficher_aide(argv);*/

    /*On parcours la commande saisie en recuperant chaque fois une option 
    et en incrementant le compteur de l'option correspondant*/
    while((option = getopt(argc, argv, "i:th:f:o:")) != -1){
        switch (option)
        {
            case 'i':
                count_i++;
                file_format = optarg;
                break;
            case 't':
                count_t++;
                break;
            case 'h':
                count_h++;
                fichier_entree = optarg;
                break;
            case 'f':
                count_f++;
                fichier_entree = optarg;
                break;
            case 'o':
                count_o++;
                fichier_sortie = optarg;
		        break;
        }
    }

    /*Suivant le nombre de parametres renseignes par l'utilisateur, on effectue les traitements necessaires*/
    if (count_i == 1){
        if (strcmp(file_format, "json") == 0 || strcmp(file_format, "xml") == 0){
            if (count_h == 1 ^ count_f == 1) {
                if (count_o == 1){
                    if (strcmp(file_format, "xml")==0){
                        //Validation du fichier json
                        if(test(psvg,fichier_entree)){
                            printf("Fichier xml valide\n"); 
    						// svg* psvg;
   							svg* psvg = svg_create(1920, 800);

                             xmlDocPtr doc = xmlReadFile(fichier_entree, NULL, XML_PARSE_NOBLANKS | XML_PARSE_NOERROR | XML_PARSE_NOWARNING | XML_PARSE_NONET);
                             xmlNode * roo_element  = xmlDocGetRootElement(doc);
                             traverse_dom_trees(psvg, roo_element);   
   							 svg_save(psvg, "fichier.svg");
                            
 							 
                        }
                    }

                    //xml
                }
                else{
                    (count_o > 1) ? printf("Veuillez renseigner un seul nom pour le fichier en sorti\n") : printf("Veuillez renseigner un argument pour la sortie\n");
                    exit(EXIT_FAILURE);
                }
            }
            else{
                printf("Veuillez renseigner une entree de donnee <-h flux http | -f fichier>\n");
                exit(EXIT_FAILURE);
            }
        }
        else{
            printf("Veuillez renseigner un format du fichier en entree correct <-i json|xml>\n");
            exit(EXIT_FAILURE);
        }
    }
    else{
        (count_i > 1) ? printf("Veuillez renseigner un seul format pour le fichier en entree\n") : printf("Veuillez renseigner le format du fichier en entree <-i json|xml>\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}
