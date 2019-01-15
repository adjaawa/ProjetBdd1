#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include"svg.h"


//declaration de la strcuture node et ses varables 
struct node {
	char *nomEntite;
	char *id;
	char *nom;
	char *prenom;
	char *association;
	char *date;

	struct node *next;
};

void insert(char *a, char *b, char *c, char *d, char *e, char *f,char *g);
void traverse_dom_trees(svg* psvg,xmlNode * a_node);
int test();
