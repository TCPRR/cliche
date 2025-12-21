#include "bindings.h"
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>
int parseUTML(char* Document) {
    
    // Parse XML from string
    xmlDocPtr doc = xmlReadMemory(Document, strlen(Document), NULL, NULL, 0);
    if (!doc) {
        printf("Failed to parse XML\n");
        return 1;
    }
    
    // get root element
    xmlNodePtr root = xmlDocGetRootElement(doc); //proper formed code should have it as <utml>
    if (!root) {
        printf("Empty document\n");
        xmlFreeDoc(doc);
        return 1;
    }
    
    printf("Root node: %s\n\n", root->name);
    printf("Children:\n");
    
    // stupih recursive goez here
    for (xmlNodePtr child = root->children; child; child = child->next) {
        if (child->type == XML_ELEMENT_NODE) {
            xmlChar *content = xmlNodeGetContent(child);
            printf("  - %s: %s\n", child->name, content);
            xmlFree(content);
        }
    }
    
    // cleanup
    xmlFreeDoc(doc);
	xmlCleanupParser();
    return 0;
}