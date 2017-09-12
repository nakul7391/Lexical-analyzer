#include <stdio.h>
#include <string.h>
#include "global.h"
#include "lex.h"

char byte;

static char* res_kwords_data[] = {"const", "volatile", "extern", "auto", "register",
   						   "static", "signed", "unsigned", "short", "long",
						   "double", "char", "int", "float", "struct",
						   "union", "enum", "void", "typedef",
						  };

static char* res_kwords_non_data[] = {"goto", "return", "continue", "break",
							   "if", "else", "for", "while", "do",
							   "switch", "case", "default","sizeof", "NULL"
							  };

void lex_begin()
{
      while( ( byte = fgetc(fptr_src)) != EOF )
      {
          switch( byte )
          {
              case '#':/*preprocessor*/
                    handle_preprocessor();
                    break;
              case 'a'... 'z':/*search words*/
                    handle_words();
                    break;
              case '(':printf("O_BRACE\n");
                    break;
              case ')':printf("C_BRACE\n");
                    break;
              case '=':printf("ASSIGNMENT\n");
                    break;
              case ';':printf("END OF STATEMENT\n");
                    break;
              case ' ':
                      break;
              case '\t':
                      break;
              case '\n':
                      break;
              case '0' ... '9':/*handle constant*/
                              handle_constant();
                              break;
              case '<':byte = fgetc(fptr_src);
                      if(byte != '=')
                      fseek(fptr_src,-1L,SEEK_CUR);
                      printf("RELTATIONAL OPERATOR\n");
                      break;
              case '>':byte = fgetc(fptr_src);
                      if(byte != '=')
                      fseek(fptr_src,-1L,SEEK_CUR);
                      printf("RELTATIONAL OPERATOR\n");
                      break;
              case '+':byte = fgetc(fptr_src);
                      if(byte == '+')
                      printf("UNARY OPERATOR\n");
                      else
                      {
                      fseek(fptr_src,-1L,SEEK_CUR);
                      printf("OPERATOR\n");
                      }
                      break;
              case '{':printf("O_CURLY_BRACE\n");
                      break;
              case '}':printf("C_CURLY_BRACE\n");
                      break;
              case '\"':/*get string*/
                      get_string();
                      break;
          }
      }
}

void handle_preprocessor()
{
    char buff[100];
    int i = 0;
    while( byte != ' ' && byte != '<' && byte != '\"')
    {
        byte = fgetc(fptr_src);
        buff[i++] = byte;
    }
    fseek(fptr_src,-1L,SEEK_CUR);
    buff[i] = '\0';
    printf("PREPROCESSOR\n");
    i = 0;
    while( byte != '<' && byte != '\"')
    {
        byte = fgetc(fptr_src);
    }
    buff[i++] = byte;
    byte = fgetc(fptr_src);
    while( byte != '\n' && byte != '>' && byte != '\"' )
    {
        buff[i++] = byte;
        byte = fgetc(fptr_src);
    }
    buff[i++] = byte;
    buff[i] = '\0';
    printf("HEADER FILE\n");
}

int handle_words()
{
    //printf("here");
    int i = 0;
    char buff[1000];
    while( byte != ' ' && byte != '(' && byte != ')' && byte != '\t' && byte != '+' && byte != '-' && byte != '<' && byte != '>')
    {
        buff[i++] = byte;
        byte = fgetc(fptr_src);
    }
    buff[i] = '\0';
    //printf("buff %s\n",buff);
    i = 0;
    while( res_kwords_data[i] != NULL)
    {
        if( strcmp(buff,res_kwords_data[i++]) == 0 )
        {
          printf("KEYWORD %s\n",buff);
          fseek(fptr_src,-1L,SEEK_CUR);
          return 0 ;
        }
    }

    i = 0;
    while(res_kwords_non_data[i] != NULL )
    {
        if( strcmp(buff,res_kwords_non_data[i++]) == 0 )
        {
            printf("KEYWORD %s\n",buff);
            fseek(fptr_src,-1L,SEEK_CUR);
            return 0;
        }
    }

    printf("IDENTIFIER %s\n",buff);
    fseek(fptr_src,-1L,SEEK_CUR);
}

void handle_constant()
{
    while( byte != ' ' && byte != '(' && byte != ')' && byte != '+' && byte != '>' && byte != '<' && byte != ';')
    {
        byte = fgetc(fptr_src);
    }

    printf("CONSTANT\n");
    fseek(fptr_src,-1L,SEEK_CUR);
}

void get_string()
{
    byte = fgetc(fptr_src);
    while( (byte = fgetc(fptr_src)) != '\"');

    printf("STRING\n");
}
