#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/xmlschemas.h>

int validation_xml(char *xmlfile, char *xsdfile) {
	xmlDocPtr pdoc;
	xmlSchemaPtr pschema;
	xmlSchemaParserCtxtPtr ctxt;
	int vret;


	//Ouverture du fichier xsd
	ctxt=xmlSchemaNewParserCtxt(xsdfile);
	xmlSchemaSetParserErrors(ctxt, (xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr);

	pschema=xmlSchemaParse(ctxt);
	xmlSchemaFreeParserCtxt(ctxt);

	pdoc=xmlReadFile(xmlfile, NULL, 0);
	//Si le fichier xml n'a pas pu etre ouvert correctement on signale l'erreur
	if (pdoc==NULL)
		printf("XML: Impossible d'analyser %s\n",xmlfile);
	//sinon on verifie la validité
	else 
	{
		pValidCtxt=xmlSchemaNewValidCtxt(pschema); //Chargement du contenu du XML schema
		xmlSchemaSetValidErrors(vctxt, (xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr);
		vret=xmlSchemaValidateDoc(pValidCtxt,pdoc);//On valide le fichier a partir du schema xsd
		if (vret==0)
			printf("Le document %s est VALIDE\n",xmlfile);
		else
			printf("Le document %s n'est PAS VALIDE\n",xmlfile);
		xmlSchemaFreeValidCtxt(pValidCtxt);
		xmlFreeDoc(pdoc);

	}
return 0;
}
