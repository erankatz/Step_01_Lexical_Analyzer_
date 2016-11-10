/***********************/
/* FILE NAME: driver.c */
/***********************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <stdlib.h>
/*****************/
/* INCLUDE FILES */
/*****************/
#include "../../HEADER_FILES/util.h"
#include "LinearAlgebra1Master.h"
#include "../../HEADER_FILES/errormsg.h"
#include "../../BISON/BISON_01_For_First_Exercise/tiger.tab.h"


YYSTYPE yylval;

int yylex(void); /* prototype for the lexing function */

string tokname(int tok)
{
	switch (tok) {
	case (FLOAT):		return "FLOAT";
	case (STRING):		return "STRING";
	case (ID):			return "ID";
	case (COMMA):		return "COMMA";
	case (INT):			return "INT";
	case (COLON):		return "COLON";
	case (SEMICOLON):	return "SEMICOLON";
	case (LPAREN):		return "LPAREN";
	case (RPAREN):		return "RPAREN";
	case (LBRACK):		return "LBRACK";
	case (RBRACK):		return "RBRACK";
	case (LBRACE):		return "LBRACE";
	case (RBRACE):		return "RBRACE";
	case (DOT):			return "DOT";
	case (PLUS):		return "PLUS";
	case (MINUS):		return "MINUS";
	case (TIMES):		return "TIMES";
	case (DIVIDE):		return "DIVIDE";
	case (EQ):			return "EQ";
	case (NEQ):			return "NEQ";
	case (LT):			return "LT";
	case (LE):			return "LE";
	case (GT):			return "GT";
	case (GE):			return "GE";
	case (AND):			return "AND";
	case (OR):			return "OR";
	case (ASSIGN):		return "ASSIGN";
	case (ARRAY):		return "ARRAY";
	case (IF):			return "IF";
	case (THEN):		return "THEN";
	case (ELSE):		return "ELSE";
	case (WHILE):		return "WHILE";
	case (FOR):			return "FOR";
	case (TO):			return "TO";
	case (DO):			return "DO";
	case (LET):			return "LET";
	case (IN):			return "IN";
	case (END):			return "END";
	case (OF):			return "OF";
	case (BREAK):		return "BREAK";
	case (NIL):			return "NIL";
	case (FUNCTION):	return "FUNCTION";
	case (VAR):			return "VAR";
	case (TYPE):		return "TYPE";
	default:			return "BAD_TOKEN";
	}
}

float FractionToFloat(char *str)
{
	char *text = strdup(str);
	int num1;
	int num2;
	float ret;

	num1 = atoi(strtok(text, "/"));
	num2 = atoi(strtok(NULL, "/"));
	ret =  (float)num1 / (float)num2;
	return ret;
}


int main(int argc, char **argv)
{
	char* fname;
	int tok, left_row;
	int openBar;
	int i;
	int j;
	float **mat;
	float **mat2, **mat3;
	int right;
	float multiplier;
	
	if (argc != 2)
	{
		fprintf(stderr,"usage: a.out filename\n");
		return 0;
	}
	
	mat = RandomizeMatrix(M, N);
	SaveMatrixToFile(mat, M, N, MATRIXFILE);
	FreeMatrix(mat,M);
	fname = MATRIXFILE ;
	EM_reset(fname) ;

	printf("\n\n") ;
	
	mat = CreateMatrix(M, N);

	i = 0;
	j = 0;
	openBar = 0;
	for (;;)
	{
		tok = yylex();
		if (tok == 0) break;
		switch (tok) {
		case INT:
			if (i < M && j < N)
			{
				mat[i][j] = yylval.ival;
				j++;
			}
			else {
				printf("Syntax Error");
			}
			break;
		case FLOAT:
			if (i < M && j < N)
			{
				mat[i][j] = yylval.fval;
				j++;
			}
			else {
				printf("Syntax Error");
			}
			break;
		case LBRACK:
			if (openBar == TRUE)
			{
				printf("Syntax Error");
			}
			openBar = TRUE;
			break;
		case RBRACK:
			i++;
			if (i == M && j == N)
				break;
			else {
				printf("Syntax Error");
			}
		case SEMICOLON:
			if (i < N)
			{
				j = 0;
				i++;
			}
			break;
		default:
			printf("Syntax Error");
		}

	}

	fname = OPERATIONFILE;
	right = 0;
	multiplier = 1;
	
	EM_reset(fname);

	for (;;)
	{
		tok = yylex();
		if (tok == 0) break;
		switch (tok) {
		case ARROW:
			right = 1;
			mat2 = CreateElementaryMatrix(M, N);
			break;
		case ROWID:
			if (right)
			{
				mat2[left_row-1][yylval.ival-1] = multiplier;
			}
			else {
				left_row = yylval.ival;
			}
			multiplier = 1;
			break;
		case NEWLINE:
			right = 0;
			multiplier = 1;
			mat3 = MatrixMultiplication(mat2, mat, M, N);
			FreeMatrix(mat2,M);
			FreeMatrix(mat,M);
			mat = mat3;
			break;
		case INT:
			multiplier = yylval.ival;
			break;
		case FRACTION:
			multiplier = FractionToFloat(yylval.sval);
			break;
		default:
			printf("%s ", tokname(tok));
			break;
		}
	}
	SaveMatrixToFile(mat, M, N, "out.txt");
	fname=argv[0];
	EM_reset(fname);

	for(;;)
	{
		tok=yylex();
		if (tok==0) break;
		switch(tok) {
		case ID:
			printf("%s(%s) ",tokname(tok),yylval.sval);
			break;
		case STRING:
			printf("%s(%s) ",tokname(tok),yylval.sval);
			break;
		case INT:
			printf("%s(%d) ",tokname(tok),yylval.ival);
			break;
		case FLOAT:
			printf("%s(%f) ",tokname(tok),yylval.fval);
			break;
		case SEMICOLON:
			printf("%s\n\n",tokname(tok));
			break;
		default:
			printf("%s ",tokname(tok));
			break;
		}
	}

	printf("\n");
	
	return 0;
}
