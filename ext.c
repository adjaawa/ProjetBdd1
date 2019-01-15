#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include"ext.h"
struct node *head = NULL;
int px=300 , py=50;
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
void traverse_dom_trees(svg* psvg,xmlNode * a_node)
{
    xmlNode *cur_node = NULL;
    
    
    for (cur_node = a_node; cur_node; cur_node = cur_node->next)
    {
               char *pol, *dev, *stat, *srcz, *dstz;
                if(strcmp((const char *)cur_node->name,(const char *)"nomEntite") == 0){
                 xmlChar *a = xmlNodeGetContent(cur_node);
                        printf("Nom entite: %s\n", a);
                       
                       svg_rectangle(psvg, 150, 90, px-15, py, "#FFFFFF", "#0000FF", 2, 2, 2);
                       svg_rectangle(psvg, 150, 90, px-15, py+34, "#FFFFFF", "#0000FF", 2, 2, 2);
                       svg_text(psvg, px+15, py+15, "sans-serif", 18, "#000000", "#000000",a);
                       py=py+300;
                       
                        }
             else if(strcmp((const char *)cur_node->name,(const char *)"id") == 0)  {
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
int test(svg* psvg,char *fileName)
{
    xmlDocPtr doc;
    xmlNode *roo_element = NULL;

    doc = xmlReadFile(fileName, NULL, XML_PARSE_NOBLANKS | XML_PARSE_NOERROR | XML_PARSE_NOWARNING | XML_PARSE_NONET);
    if (doc == NULL)
    {
        fprintf(stderr, "Document not parsed successfully.\n");
        return 0;
    } 

    roo_element = xmlDocGetRootElement(doc);
//ON VERIFIE SI LE DOCUMENT CONTENANT LE CODE XML PASSE EN PARAMETRE EST VIDE
    if (roo_element == NULL)
 {
        fprintf(stderr, "empty document\n");
        xmlFreeDoc(doc);
        return 0;
    }
	
    printf("Root Node is %s\n", roo_element->name);
    traverse_dom_trees(psvg,roo_element);

    xmlFreeDoc(doc);       // free document
    xmlCleanupParser();    // Free globals
  
    return 0;
}
