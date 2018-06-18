#ifndef __TOKEN_H
#define __TOKEN_H
	#include "HeaderPadrao.h"

	typedef struct {
		char nome[str_size];
		char lexema[str_size];
		unsigned long int linha;
	} Token;

	bool Token_equals(Token *elem1, Token *elem2);

	Token* new_Token(const char nome[str_size], char *lexema, unsigned long int linha);
	int del_Token(void* self);

	/* Tokens da Linguagem */
	#define MAIN "MAIN"
	#define INT "INT"
	#define FLOAT "FLOAT"
	#define IF "IF"
	#define ELSE "ELSE"
	#define WHILE "WHILE"
	#define FOR "FOR"
	#define READ "READ"
	#define PRINT "PRINT"
	#define LBRACKET "LBRACKET"
	#define RBRACKET "RBRACKET"
	#define LBRACE "LBRACE"
	#define RBRACE "RBRACE"
	#define COMMA "COMMA"
	#define PCOMMA "PCOMMA"
	#define ATTR "ATTR"
	#define LT "LT"
	#define LE "LE"
	#define GT "GT"
	#define GE "GE"
	#define EQ "EQ"
	#define NE "NE"
	#define OR "OR"
	#define AND "AND"
	#define PLUS "PLUS"
	#define MINUS "MINUS"
	#define MULT "MULT"
	#define DIV "DIV"
	#define ID "ID"
	#define INTEGER_CONST "INTEGER_CONST"
	#define FLOAT_CONST "FLOAT_CONST"

#endif //__TOKEN_H