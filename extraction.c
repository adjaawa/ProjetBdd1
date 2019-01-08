#include <stdio.h>
#include <libxml/parser.h>
#include <stdlib.h>
#include <libxml/tree.h>
 
void print_content( xmlNode* root )
{
  xmlNode* current = NULL;
  for ( current=root; current!=NULL; current=current->next )
  {
    if ( current->type==XML_ELEMENT_NODE )
      printf( "node type: %s\n", current->name );
    if (strcmp((char*)current->name,"labyrinth")==0)
    {
      printf( "  length: %s\n", (const char*)xmlGetProp( current, (const xmlChar*)"length" ) );
      printf( "  width:  %s\n", (const char*)xmlGetProp( current, (const xmlChar*)"width"  ) );
      printf( "  name:   %s\n", (const char*)xmlGetProp( current, (const xmlChar*)"name"   ) );
    }
    print_content( current->children );
  }
}
 
int main( int a, char** b)
{
  xmlDoc*  doc  = NULL;
  xmlNode* root = NULL;
  doc = xmlReadFile( "assoc.xsd", NULL, 0 );
   
  if ( doc==NULL )
    return 0;
   
  root = xmlDocGetRootElement( doc );
  print_content( root );
  xmlFreeDoc( doc );
  xmlCleanupParser();  
return 1;
}
