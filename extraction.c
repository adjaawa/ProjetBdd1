#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>

//declaration de la strcuture node et ses varables 
struct node {
        char *nomEntite;
        char *id;
        char *nom;
        char *prenom;
        char *association;
       char  *date;

        struct node *next;
            };
        struct node *head = NULL;
//declaration de la fonction insert et Initialisation des variables a,b,c,d et e
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
// declaration de la fonction traverse_dom_trees qui permet de parcourir les noeuds et ensuite afficher leur valeur
void traverse_dom_trees(xmlNode * a_node)
{
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next)
    {
                char *pol, *dev, *stat, *srcz, *dstz;
                if(strcmp((const char *)cur_node->name,(const char *)"nomEntite") == 0){
                 xmlChar *a = xmlNodeGetContent(cur_node);
                        printf("Nom entite: %s\n", a);
                      
                        }
             else if(strcmp((const char *)cur_node->name,(const char *)"id") == 0)  {
                    xmlChar *b = xmlNodeGetContent(cur_node);
                        printf("ID : %s\n", b);
                        dev = strdup(b);
                       
                        }
            else if(strcmp((const char *)cur_node->name,(const char *)"nom") == 0){
                    xmlChar *c = xmlNodeGetContent(cur_node);
                        printf("NOM : %s\n", c);
                        stat = strdup(c);
                       
                        }
            else if(strcmp((const char *)cur_node->name,(const char *)"prenom") == 0){
                    xmlChar *d = xmlNodeGetContent(cur_node);
                        printf("PRENOM : %s\n", d);
                        srcz = strdup(d);
                        
                        }
           
                else if(strcmp((const char *)cur_node->name,(const char *)"association") == 0){
                        xmlChar *e = xmlNodeGetContent(cur_node);
                         printf("ASSOCIATION : %s\n", e);
                        dstz = strdup(e);
                        }
               else if(strcmp((const char *)cur_node->name,(const char *)"date") == 0){
                        xmlChar *f = xmlNodeGetContent(cur_node);
                         printf("DATE : %s\n", f);
                        }

 

        traverse_dom_trees(cur_node->children);
    }
}
int main(int argc, char **argv)
{
    xmlDocPtr doc;
    xmlNode *roo_element = NULL;
//VERIFICATION DU NOMBRE D'ARGUMENT
    if (argc != 2)
    {
        printf("\nArgument Invalid \n");
        return(1);
    }

//VERIFICATION DE LA VALIDITE DU DOCUMENT CONTENANT LE CODE XML PASSE EN PARAMETRE
    doc = xmlReadFile(argv[1], NULL, XML_PARSE_NOBLANKS | XML_PARSE_NOERROR | XML_PARSE_NOWARNING | XML_PARSE_NONET);
    if (doc == NULL)
    {
        fprintf(stderr, "Document invalide.\n");
        return 0;
    }

    roo_element = xmlDocGetRootElement(doc);
//ON VERIFIE SI LE DOCUMENT CONTENANT LE CODE XML PASSE EN PARAMETRE EST VIDE
    if (roo_element == NULL)
 {
        fprintf(stderr, "Document vide\n");
        xmlFreeDoc(doc);
        return 0;
    }

    printf("Root Node is %s\n", roo_element->name);
    traverse_dom_trees(roo_element);

    xmlFreeDoc(doc);       // free document
    xmlCleanupParser();    // Free globals
    return 0;
}
