#include "ast.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

int main(int argc,char **argv){
	char *name = "program".c_str();
	char *type = "int".c_str();

	field_declaration *f_d = new field_declaration(name,type);

}