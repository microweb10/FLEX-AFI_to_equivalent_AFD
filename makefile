
COMP=g++
OPC=-o
COMPFLEX=flex

qet: lex.yy.c
	$(COMP) $(OPC) qet lex.yy.c

lex.yy.c:
	$(COMPFLEX) qet.l

afi2afd:
	$(COMP) $(OPC) afi2afd afi2afd.cpp

	


