

//Constantes pour taille des  variables
#define TINTS 12 //taille max d'un int en string : 10 chiffre + un signe + marquer fin de chaine '\0'

/* TABLE DES SYMBOLES */

typedef char name_t[8];

typedef struct symbol_t {
  enum { NAME, CONSTANT } kind;
    union {
        name_t name;
        long int value;
    } u;
}symbol;

typedef struct symtable_t {
    unsigned int capacity;
    unsigned int temporary;
    unsigned int size;
     symbol * symbols;
}symtable;

 symtable * symtable_new();

 symbol * symtable_const( symtable * t, long int v);

 symbol * symtable_get( symtable * t, const char * s);

 symbol * symtable_put( symtable * t, const char * s);

void symtable_dump( symtable * t);

void symtable_free( symtable * t);


/* QUADRUPLETS ET CODE */

typedef struct quad_t {
  enum quad_kind { BOP_PLUS, BOP_MINUS, BOP_MULT, UOP_MINUS, UOP_PLUS, COPY, CALL_PRINT } kind;
   symbol * sym1;
   symbol * sym2;
   symbol * sym3;
}quad;

typedef struct code_t {
    unsigned int capacity;
    unsigned int nextquad;
     quad * quads;
}code;

 code * code_new();

void gencode( code * c,
              enum quad_kind k,
               symbol * s1,
               symbol * s2,
               symbol * s3);

 symbol *newtemp( symtable * t);

void code_dump( code * c);

void code_free( code * c);


//finale code gen

void getArguments_INT( quad* q, FILE* fp,char* sym2, char* sym3);

void intermediaryToMIPS(  symtable* tds,   code* quads);

char* itoa(int i, char b[]);
