#include <stdio.h>

//#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
//#include <libxml/xpathInternals.h>

void print_xpath_nodes(xmlNodeSetPtr nodes, FILE* output);

int 
main(int argc, char **argv) {
//	printf("test");
	xmlInitParser();	
//	fprintf(stdout, "init");
//    FILE *out = fopen('/dev/null', O_WRONLY);
    xmlXPathContextPtr xpathCtx; 
    xmlXPathObjectPtr xpathObj; 
	xmlDocPtr doc;
	xmlChar *string = malloc(10000);
    doc = xmlParseFile("standard");   
    xpathCtx = xmlXPathNewContext(doc);
//    int res = xmlXPathRegisterNs(xpathCtx, BAD_CAST "xs", BAD_CAST "http://www.w3.org/2001/XMLSchema");
//    xmlXPathRegisterNs(xpathCtx, "fn", "http://www.w3.org/2005/xpath-functions");
  //  if (res == -1){
//	fprintf(stdout, "ERROR!");
//	return 1;
//}
	__AFL_INIT();
//uint8_t buf[3000]; 
//__AFL_INIT();
//while (__AFL_LOOP(1000)) {
	#define BUF_SIZE 3024
/*
char buffer[BUF_SIZE];
size_t contentSize = 1; // includes NULL
 Preallocate space.  We could just allocate one char here, 
but that wouldn't be efficient. 
char *content = malloc(sizeof(char) * BUF_SIZE);
if(content == NULL)
{
    perror("Failed to allocate content");
    exit(1);
}
content[0] = '\0'; // make null-terminated

//__AFL_INIT();

while(fgets(buffer, BUF_SIZE, stdin))
{
    char *old = content;
    contentSize += strlen(buffer);
    content = realloc(content, contentSize);
    if(content == NULL)
    {
        perror("Failed to reallocate content");
        free(old);
        exit(2);
    }
    strcat(content, buffer);
}

if(ferror(stdin))
{
    free(content);
    perror("Error reading from stdin.");
    exit(3);
}
*/
/*	FILE *f = fopen(argv[1], "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	xmlChar *string = malloc(fsize + 1);
	fread(string, fsize, 1, f);
	fclose(f);
	string[fsize] = 0;
*/

//	xmlChar *string = malloc(5000);
	int total = read(0, string, 10000);
	string[total] = 0;
///	return 1;
//	xmlDocPtr doc;
//    xmlXPathContextPtr xpathCtx; 
//    xmlXPathObjectPtr xpathObj; 
//    doc = xmlParseFile("test.xml");	
//    xpathCtx = xmlXPathNewContext(doc);

//while (__AFL_LOOP(1000)) {
//	   xmlXPathContextPtr xpathCtx;    
//xmlXPathObjectPtr xpathObj;

      //  xmlDocPtr doc;
    //doc = xmlParseFile("standard");
      //  xmlDocPtr doc;
    //doc = xmlParseFile("standard");
//   xpathCtx = xmlXPathNewContext(doc);

 //   memset(buf, 0, 3000);
   //     read_bytes = read(0, buf, 3000);
//    memset(buf, 0, 3000);
//    read(0, buf, 3000);
    xpathObj = xmlXPathEvalExpression(string, xpathCtx);
    fprintf(stdout, "%p", xpathObj);
    //if(xpathObj != NULL) {
	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx); 
    //return 1;
  //  }
    
//}
    return 0;
	//if(xpathObj == NULL) {
//        fprintf(stderr,"Error: unable to evaluate xpath expression \"%s\"\n", xpathExpr);
//        xmlXPathFreeContext(xpathCtx); 
//        xmlFreeDoc(doc); 
        //return(-1);
    //} else {
//	fprintf(stdout, "its all good");
//	return 0;
//	}

//    print_xpath_nodes(xpathObj->nodesetval, stderr);
}


void
print_xpath_nodes(xmlNodeSetPtr nodes, FILE* output) {
    xmlNodePtr cur;
    int size;
    int i;
    
    
    size = (nodes) ? nodes->nodeNr : 0;
    
    fprintf(output, "Result (%d nodes):\n", size);
    for(i = 0; i < size; ++i) {
	
	
	if(nodes->nodeTab[i]->type == XML_NAMESPACE_DECL) {
	    xmlNsPtr ns;
	    
	    ns = (xmlNsPtr)nodes->nodeTab[i];
	    cur = (xmlNodePtr)ns->next;
	    if(cur->ns) { 
	        fprintf(output, "= namespace \"%s\"=\"%s\" for node %s:%s\n", 
		    ns->prefix, ns->href, cur->ns->href, cur->name);
	    } else {
	        fprintf(output, "= namespace \"%s\"=\"%s\" for node %s\n", 
		    ns->prefix, ns->href, cur->name);
	    }
	} else if(nodes->nodeTab[i]->type == XML_ELEMENT_NODE) {
	    cur = nodes->nodeTab[i];   	    
	    if(cur->ns) { 
    	        fprintf(output, "= element node \"%s:%s\"\n", 
		    cur->ns->href, cur->name);
	    } else {
    	        fprintf(output, "= element node \"%s\"\n", 
		    cur->name);
	    }
	} else {
	    cur = nodes->nodeTab[i];    
	    fprintf(output, "= node \"%s\": type %d\n", cur->name, cur->type);
	}
    }
}
