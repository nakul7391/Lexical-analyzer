/*Lexical analyzer */
#include <stdio.h>
#include <string.h>
#include "global.h"
#include "lex.h"

int main(int argc, char *argv[] )
{
		if(argc < 2 )
		{
			printf("Invalid arguments\n");
			printf("Try ./a.out --help\n");
			return 1;
		}

		if( strcmp(argv[1],"--help") == 0 )
		{
			printf("./a.out <file.c>\n");
			return 2;
		}

		/*open source file*/
		fptr_src = fopen(argv[1],"r");

		if( fptr_src == NULL )
		{
				perror("");
				printf("Unable to open file\n");
				return 3;
		}

		lex_begin();

		/*close file*/
		fclose(fptr_src);
		return 0;
}
