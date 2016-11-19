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

void replace_rows(float **mat,int left)
{
	int tok = yylex();
	if (tok == ROWID && yylval.ival <= N && yylval.ival > 0)
	{
		float *temp = mat[yylval.ival - 1];
		mat[yylval.ival - 1] = mat[left - 1];
		mat[left - 1] = temp;
	}
	else 
	{
		printf("Syntax Error");
	}
}
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
	/*char *text = strdup(str);
	int num1;
	int num2;
	float ret;

	num1 = atoi(strtok(text, "/"));
	num2 = atoi(strtok(NULL, "/"));
	ret =  (float)num1 / (float)num2;
	return ret;*/
	return 5;
}

void readMatrix(float **mat)
{
	int i = 0;
	int j = 0;
	int openBar =FALSE;
	int tok;

	//Read Matrix From file
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
				printf("Syntax Error: Error reading matrix the matrix should by 3 by 3 size");
				exit(1);
			}
			break;
		case FLOAT:
			if (i < M && j < N)
			{
				mat[i][j] = yylval.fval;
				j++;
			}
			else {
				printf("Syntax Error : Error reading matrix the matrix should by 3 by 3 size");
				exit(1);
			}
			break;
		case LBRACK:
			if (openBar == TRUE)
			{
				printf("Syntax Error : Missing Barcket");
				exit(1);
			}
			openBar = TRUE;
			break;
		case RBRACK:
			i++;
			if (i == M && j == N)
				break;
			else {
				printf("Syntax Error : Missing Barcket");
				exit(1);
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
			exit(1);
		}

	}
}

float** readOperationFile(char *fname, float **mat)
{
	int tok, left_row;
	int openBar;
	int i = 0;
	int j = 0;
	float **mat2, **mat3;
	int right = 0;
	float multiplier = 1;
	bool row_in_left_apears_on_right = FALSE;

	EM_reset(fname);
	mat2 = NULL;
	//Read Operation File

	for (;;)
	{
		tok = yylex();
		if (tok == 0)
		{
			if (mat2 != NULL)
			{
				mat3 = MatrixMultiplication(mat2, mat);
				FreeMatrix(mat2, M);
				FreeMatrix(mat, M);
				mat = mat3;
				if (!row_in_left_apears_on_right)
				{
					printf("The row in the left size must apear on the right side");
					exit(1);
				}
			}
			break;
		}
		switch (tok) {
		case ARROW:
			//printf("arrow");
			right = 1;
			mat2 = CreateElementaryMatrix(M, N);
			break;
		case ROWID:
			//printf("rowid");
			if (yylval.ival <= N)
			{
				if (right)
				{
					mat2[left_row - 1][yylval.ival - 1] = multiplier;
					if (left_row == yylval.ival)
					{
						row_in_left_apears_on_right = TRUE;
					}
				}
				else {
					
					left_row = yylval.ival;
				}
				multiplier = 1;
			}
			else
			{
				printf("Only opration on 3 by 3 matrix allowed");
				exit(1);
			}
			break;
		case NEWLINE:
			//printf("\n");
			if (mat2 != NULL)
			{
				mat3 = MatrixMultiplication(mat2, mat);
				FreeMatrix(mat2, M);
				FreeMatrix(mat, M);
				mat = mat3;
				if (!row_in_left_apears_on_right)
				{
					printf("The row in the left size must apear on the right side");
					exit(1);
				}
			}
			right = 0;
			multiplier = 1;
			mat2 = NULL;
			row_in_left_apears_on_right = FALSE;
			break;
		case INT:
			//printf("int");
			multiplier = yylval.ival;
			break;
		case FRACTION:
			//printf(*yylval.sval);
			multiplier = FractionToFloat(yylval.sval);
			break;
		case REPLACEARROW:
			//printf("replacearrow");
			replace_rows(mat, left_row);
			tok = yylex();
			if (tok != NEWLINE)
			{
				printf("The Syntax of new line is RX <--> RY");
				exit(1);
			}
			break;
		default:
			//printf("%s ", tokname(tok));
			break;
		}
	}
	return mat;
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
	bool row_in_left_apears_on_right = FALSE;
		
	if (argc == 3)
	{
		fname = argv[1];
	}
	else if (argc == 2)
	{

		mat = RandomizeMatrix(M, N);
		SaveMatrixToFile(mat, M, N, MATRIXFILE);
		FreeMatrix(mat, M);
		fname = MATRIXFILE;
	} else {

		fprintf(stderr,"usage: a.out filename\n");
		return 0;
	}
	
	EM_reset(fname);
	
	printf("\n\n") ;
	
	mat = CreateMatrix(M, N);
	
	readMatrix(mat);
	if (argc == 2)
	{
		fname = argv[1];
	}
	else {
		fname = argv[2];
	}

	mat = readOperationFile(fname,mat);
	
	SaveMatrixToFile(mat, M, N, "out.txt");
	PrintMatrix(mat,M,N);
	
	return 0;
}
