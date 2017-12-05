
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lib.h"


 symtable * symtable_new()
{
     symtable * t = malloc(sizeof( symtable));
    t->capacity = 1124;
    t->symbols = malloc(t->capacity*sizeof( symbol));
    t->temporary = 1;
    t->size = 1;
    return t;
}

static void symtable_grow( symtable * t) 
{
    t->capacity += 1124;
    t->symbols = realloc(t->symbols,t->capacity*sizeof( symbol));
    if(t->symbols == NULL) 
    {
      fprintf(stderr,"Error attempting to grow symbol table (actual size is %d)\n",t->size);
        exit(1);
    }
}

 symbol * symtable_const( symtable * t, long int v) 
{
    unsigned int i;
    for ( i=1 ; i<t->size && t->symbols[i].u.value != v; i++ );
    if(i==t->size)
    {
        if(t->size==t->capacity)
          symtable_grow(t);
         symbol *s = &(t->symbols[t->size]);
        s->kind = CONSTANT;
        s->u.value = v;
        ++ (t->size);
        return s;
    }
    else 
    {
        return &(t->symbols[i]);
    }
}

 symbol * symtable_get( symtable * t, const char * id) 
{
    unsigned int i;
    
    for ( i=1 ; i<t->size && strcmp(t->symbols[i].u.name,id) != 0; i++ );
    if(i<t->size)
      return &(t->symbols[i]);
    return NULL;
}

 symbol * symtable_put( symtable * t, const char * id) 
{
    if(t->size==t->capacity)
      symtable_grow(t);
     symbol *s = &(t->symbols[t->size]);
    s->kind = NAME;
    strcpy(s->u.name,id);
    ++ (t->size);
    return s;
}

void symtable_dump( symtable * t)
{
    unsigned int i;
    for ( i=1 ; i<t->size; i++ )
    {
      if(t->symbols[i].kind==CONSTANT)
        printf("       %p = %ld\n",&(t->symbols[i]),t->symbols[i].u.value);
      if(t->symbols[i].kind==NAME)
        printf("       %p = %s\n",&(t->symbols[i]),t->symbols[i].u.name);
    }
    printf("       --------\n");
}

void symtable_free( symtable * t)
{
    free(t->symbols);
    free(t);
}

 code * code_new()
{
     code * r = malloc(sizeof( code));
    r->capacity = 1124;
    r->quads = malloc(r->capacity*sizeof( quad));
    r->nextquad = 1;
    return r;
}

static void code_grow( code * c)
{
    c->capacity += 1124;
    c->quads = realloc(c->quads,c->capacity*sizeof( quad));
    if(c->quads == NULL) 
    {
      fprintf(stderr,"Error attempting to grow quad list (actual size is %d)\n",c->nextquad);
        exit(1);
    }
}

void gencode( code * c,
              enum quad_kind k,
               symbol * s1,
               symbol * s2,
               symbol * s3)
{
    if ( c->nextquad == c->capacity )
        code_grow(c);
     quad * q = &(c->quads[c->nextquad]);
    q->kind = k;
    q->sym1 = s1;
    q->sym2 = s2;
    q->sym3 = s3;
    ++ (c->nextquad);
}

 symbol *newtemp( symtable * t)
{
   symbol * s;
  name_t name;
  sprintf(name,"t%d",t->temporary);
  s = symtable_put(t,name);
  ++ (t->temporary);
  return s;
}

static void symbol_dump( symbol * s)
{
    switch ( s->kind )
    {
        case NAME:
            printf("%s",s->u.name);
            break;
        case CONSTANT:
            printf("%ld",s->u.value);
            break;
        default:
            break;
    }
}

static void quad_dump( quad * q)
{
    switch ( q->kind )
    {
        case BOP_PLUS:
            symbol_dump(q->sym1);
            printf(" := ");
            symbol_dump(q->sym2);
            printf(" + ");
            symbol_dump(q->sym3);
            break;
        case BOP_MINUS:
            symbol_dump(q->sym1);
            printf(" := ");
            symbol_dump(q->sym2);
            printf(" - ");
            symbol_dump(q->sym3);
            break;
        case BOP_MULT:
            symbol_dump(q->sym1);
            printf(" := ");
            symbol_dump(q->sym2);
            printf(" * ");
            symbol_dump(q->sym3);
            break;
        case UOP_MINUS:
            symbol_dump(q->sym1);
            printf(" := ");
            printf("- ");
            symbol_dump(q->sym2);
            break;
        case CALL_PRINT:
            printf("print ");
            symbol_dump(q->sym1);
            break;
        case COPY:
            symbol_dump(q->sym1);
            printf(" := ");
            symbol_dump(q->sym2);
            break;
        default:
            printf("BUG\n");
            break;
    }
}

void code_dump( code * c)
{
    unsigned int i;
    for ( i=1 ; i<c->nextquad ; i++ )
    {
        printf("%4u | ",i);
        quad_dump(&(c->quads[i]));
        printf("\n");
    }
}

void code_free( code * c)
{
    free(c->quads);
    free(c);
}


//finale code gen

void intermediaryToMIPS( symtable* t,  code* quads)
{
    unsigned int i;
    quad *q;
    char* sym2 = (char*)malloc(sizeof(char)*TINTS);
    char* sym3 = (char*)malloc(sizeof(char)*TINTS);
    //ouverture fichier
    FILE *fp = fopen("MIPS.s", "w");


    
    //declaration des variables
    fputs(".data \n",fp);

    for ( i=1 ; i<t->size; i++ )
    {
      
      if(t->symbols[i].kind==NAME)
        {
            fprintf(fp, "%s ", t->symbols[i].u.name);
            fprintf(fp,":");
            fprintf(fp, " .word \n" );
        }
    }


    //traduction des quads
    fputs(".text \n",fp);
     for ( i=1 ; i<quads->nextquad; i++ )
    {
        q = &(quads->quads[i]);
        switch ( q->kind )
        {
            case BOP_PLUS:
                
                getArguments_INT(q,fp,sym2,sym3);
                fprintf(fp, "add $t0 %s %s \n",sym2,sym3 ); //add     $t0, $t0, $t1   # Add x and y  
                fprintf(fp, "sw $t0 %s \n", q->sym1->u.name); // sw      $t1, sum  
            break;
            case BOP_MINUS:

                getArguments_INT(q,fp,sym2,sym3);
                fprintf(fp, "sub $t0 %s %s \n",sym2,sym3 ); 
                fprintf(fp, "sw $t0 %s \n", q->sym1->u.name); 
                break;
            case BOP_MULT:
                getArguments_INT(q,fp,sym2,sym3);
                fprintf(fp, "mult $t0 %s %s \n",sym2,sym3 ); 
                fprintf(fp, "sw $t0 %s \n", q->sym1->u.name); 
                break;
            case UOP_MINUS:
                getArguments_INT(q,fp,sym2,sym3);
                fprintf(fp, "sub $t0 0 %s \n",sym2 );
                fprintf(fp, "sw $t0 %s \n", q->sym1->u.name);  
                break;
            case CALL_PRINT:
               
                if(q->sym1->kind==NAME)
                {
                    
                    fprintf(fp, "lw $t0 %s\n",q->sym1->u.name );  
                    fprintf(fp, "printint $t0");
                }
                else
                {
                    fprintf(fp, "printint %ld\n",q->sym1->u.value );
                }
              
                break;
            case COPY:
                getArguments_INT(q,fp,sym2,sym3);
                fprintf(fp, "sw %s %s\n",sym2,q->sym1->u.name );
                break;
            default:
                printf("BUG\n");
                break;
        }
    }
}



void getArguments_INT(  quad* q,FILE* fp, char* sym2, char* sym3)
{

    if(q->sym2!=NULL)
    {
        if(q->sym2->kind==NAME)
        {
            sprintf(sym2, "$t2");
            fprintf(fp, "lw $t2 %s\n",q->sym2->u.name );  //lw      $t1, x 
        }
        else
        {
             itoa(q->sym2->u.value, sym2);
        }
    }
    else
    {
        sym2='\0';
    }

    if(q->sym3!=NULL)
    {

        if(q->sym3->kind==NAME)
        {
            sprintf(sym3, "$t3");
            fprintf(fp, "lw $t3 %s\n",q->sym3->u.name );  //lw      $t1, x 
        }
        else
        {
             itoa(q->sym3->u.value, sym3);
        }
     }
    else
    {
        sym3='\0';
    }
    
}

char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

