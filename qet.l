%{
/* DNI_1: 45567904M NOMBRE_1: Nicolas Herrero, Julian    */
/* DNI_2: 74233276V NOMBRE_2: Gallego Rodriguez, Patricia */
int tipo=0;
%}




%%
[<]+[^>]*[>]						if(tipo==2) printf("%s",yytext);
("<HEAD>"|"<head>")(.|\n|\t)*("</HEAD>"|"</head>")	if(tipo==2) printf("%s",yytext);
" "*"("[A-Z]*"$"?					if(tipo==1) printf("%s",yytext);
" "*"("[A-Z]*"$"?"-"[A-Z]*"$"?				if(tipo==1) printf("%s",yytext);
" "*"("[A-Z]*"$"?"-"[0-9]*"$"?				if(tipo==1) printf("%s",yytext);
" "*"("[A-Z]*"$"?"-"[A-Z]*"$"?"-"[A-Z]*"$"?		if(tipo==1) printf("%s",yytext);
" "*"("[A-Z]*"$"?"-"[A-Z]*"$"?"-"[0-9]*"$"?		if(tipo==1) printf("%s",yytext);
" "*"(. .) ))"						if(tipo==1) printf("%s",yytext); else printf(".\n");
" "*"(, "						if(tipo==1) printf("%s",yytext);
\n							if(tipo==1) printf("%s",yytext);
\t							if(tipo==1) printf("%s",yytext);
" "*")"							if(tipo==1) printf("%s",yytext);
" "*\n" "*						if(tipo==1) printf("%s",yytext);
%%
int yywrap(void){return 1;}

main (int argc,char **argv){
int cont;
	if(argc==3){
		yyin = fopen(argv[2],"r");
		if(strcmp(argv[1],"-h")==0)
			tipo=1;
		if(strcmp(argv[1],"-a")==0)
			tipo=2;
		if (!yyin){
			printf("Error no puedo abrir %s\n",argv[2]);
			//exit (1);
		}
		if(tipo==1)
			yylex();
		if(tipo==2){
			yylex();
			printf("\n");
		}
	}
	else{
		printf("Uso: %s {-h|-a} Fichero.\n",argv[0]);
		exit(1);
	}
return 0;
}
