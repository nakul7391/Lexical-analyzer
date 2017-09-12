#ifndef LEX_H
#define LEX_H

void lex_begin();

void handle_preprocessor();

void handle_library();

int handle_words();

void handle_constant();

void get_string();
#endif
