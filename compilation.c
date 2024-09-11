#include<stdio.h>
#include<cstring>
#include <ctype.h>
#include <stdlib.h>

#define program 1
#define cd 2
#define pv 3
#define pt 4
#define var 5
#define dp 6
#define integer 7
#define charr 8
#define begin 9
#define end 10
#define v 11
#define aff 12
#define iff 13
#define then 14
#define elsee 15
#define whilee 16
#define doo 17
#define read 18
#define readln 20
#define write 21
#define po 22
#define pf 23
#define oppadd 24
#define oppmul 25
#define nb 26
#define id 27
#define writeln 28
#define opprel 29

/*typedef struct{

  int lexeme;
  int typee;

}case_table;

int Nb_cases_table_symbole = 0;

case_table table_symbole[100];

int UniLexId(int s){
  if(s>=1 && s <= 29){

    return s;
  }

  return 27;
}



int AnalLex(){

int etat=0;
while(1){

    ignorer_espaces();

    int currentChar = fgetc(sourceFile);

    if (currentChar == EOF)
    {
        return EOF;
    }

    switch(etat){

    case 0 :


    }


}

}*/


//Definition d'une pile

struct Pile {
	int data;
	struct Pile* next;
};

struct Pile* newNode(int data)
{
	struct Pile* Pile =(struct Pile*)malloc(sizeof(struct Pile));
	Pile->data = data;
	Pile->next = NULL;
	return Pile;
}

int isEmpty(struct Pile* root)
{
	return !root;
}

void push(struct Pile** root, int data)
{
	struct Pile* Pile = newNode(data);
	Pile->next = *root;
	*root = Pile;
	printf("%d pushed to stack\n", data);
}

int pop(struct Pile** root)
{
	if (isEmpty(*root))
		return -1;
	struct Pile* temp = *root;
	*root = (*root)->next;
	int popped = temp->data;
	free(temp);

	return popped;
}

int peek(struct Pile* root)
{
	if (isEmpty(root))
		return -1;
	return root->data;
}

//

// Definition d'une case de tableau des symbole
typedef struct
{
    char lexeme[20];
    int token;
    int tyype;
} case_table;
 // maximum des caes  = 100
case_table table_symbole[100];

FILE *sourceFile;

long currentFilePosition;

 // L'indice courant dans Tableau
int symbolTableSize = 0;

 // Permettre d'ignorer les espaces lors de lecture
void ignorer_espaces()
{
    int currentChar;

    while ((currentChar = fgetc(sourceFile)) != EOF && (currentChar == ' ' || currentChar == '\n' || currentChar == '\t'));
    ungetc(currentChar, sourceFile);
}

//si lexeme une mot cle retourne le mot cle sinon retourne id

int UnilexId(const char *lexeme)
{
    for (int i = 0; i < symbolTableSize; ++i)
    {
        if (strcmp(table_symbole[i].lexeme, lexeme) == 0)
        {
            return table_symbole[i].token;
        }
    }
    return id;
}

//si lexeme une mot cle retourne 0 sinon retourne son @ dans tableau des symboles si n'existe pas elle l'ajout et retourne son @
case_table *RangerId(const char *lexeme)
{
    for (int i = 0; i < symbolTableSize; ++i)
    {
        if (strcmp(table_symbole[i].lexeme, lexeme) == 0)
        {
            return &table_symbole[i];
        }
    }

    case_table newEntry;
    strcpy(newEntry.lexeme, lexeme);
    newEntry.token = id;
    table_symbole[symbolTableSize++] = newEntry;
    return &table_symbole[symbolTableSize - 1];
}
//Cette pile pour avoir les deux id ou id et nb d'une expression pour pouvoir tester la compatiblite de type
struct Pile* pile = NULL;
// varibla pour tester si on est en dehors de la declaration
int Dehors_Dcl = 0;

// Analyseur Lexical
int symbole_suivant()
{

    ignorer_espaces();

    int currentChar = fgetc(sourceFile);

    if (currentChar == EOF)
    {
        return EOF;
    }

    switch (currentChar)
    {
    case ';':
        printf(" ; ");
        return 3;
    case ',':
        printf(" , ");
        return 11;
    case '.':
        return 4;
    case ':':
       /* if ((currentChar = symbole_suivant()) == '=')
        {

            printf(" sta3l:= ");
            return 12;
        }
        else
        {
            ungetc(currentChar, sourceFile);
            printf(" sta3l: ");
            return 6;
        }*/
        printf(" : ");
    return 6;
    case '(':
            printf(" ( ");
        return 22;
    case ')':
        printf(" ) ");
        return 23;
    case '+':
    case '-':
        return 24;
    case '*':
    case '/':
    case '%':
        return 25;
    case '=':
        printf(" = ");
        return 29;
    case '<':
        printf(" < ");
        return 29;
    case '>':
        printf(" > ");
        return 29;
    default:

        if (isalpha(currentChar))
        {
            ungetc(currentChar, sourceFile);
            char identifier[20];
            fscanf(sourceFile, "%s", identifier);
            int token;
            if ((token = UnilexId(identifier)) != 27)
            {

                printf("%d ",token);
                return token;

            }
            else
            {
                case_table* c = RangerId(identifier);

                push(&pile,c->tyype);

                printf("id");
                return 27;
            }
        }

    }


    return 0;
}

int symbole;
void dcl();
void inst_comp();
void d1();
int symbole_suivant();
void erreur();
void accepter(int);
void p();
void l_id();
void l1();
void type();
void inst();
void l_inst();
void l_inst1();
void i();
void exp();
void exp_simple();
void exp1();
void terme();
void exp_simple1();
void terme1();
void facteur();


/*int symbole_suivant()
{
	int s;
	printf("donner le symbole suivant:\n");
	scanf("%d",&s);
	return s;
}*/

// Fonctions Pour Semantique

// Prend 2 type en parametre et tester si ils sont compatibles

int Test_Semantique(int type0,int type1){

    return type0 == type1;


}


//Fonctions Pour Traducteur

struct Pile* pile1 = NULL;

// imprimer dans un fichier destination les instructions pour une machine a pile

void emmettre(const char* c){


    FILE *sourceFile;

    sourceFile = fopen("sourceFile.txt","a");

    if(sourceFile == NULL){
        printf("Erreur lors de l'overture");
    }
    else{
        fprintf(sourceFile,"%s\n",c);
        fclose(sourceFile);
    }



}

// Retourne un integer pour letiquette concerne
int cree_Etiq(){

    int i;
    return ++i;

}



void erreur()
{
	printf("symbole non accepte !\n");
}

void accepter(int t)
{
    if(Dehors_Dcl == 0){
        if (symbole == t )

		symbole=symbole_suivant();
	else
	{
	erreur();
	}
    }
    else{


  // test semantique en dehors de declaration
    if (symbole == t && Test_Semantique(pop(&pile),pop(&pile)))

		symbole=symbole_suivant();
	else
	{
	erreur();
	}

    }

}

void p()
{
	if(symbole == program)
	{
		accepter(program);
		accepter(id);
		accepter(pv);
		dcl();
		inst_comp();
	    if (symbole == pt)
	    printf("algorithme correcte...:)");

	}
	else
		printf("erreur syntaxique...\n");
}

void dcl()
{
	d1();
}

void d1()
{
	if(symbole == var)
	{
		accepter(var);
		l_id();
		accepter(dp);
		type();
		accepter(pv);
		d1();
	}
	Dehors_Dcl = 1;

}

void l_id()
{
	if(symbole==id)
	{
		accepter(id);
		l1();
	}
			else
	{
	printf("erreur : pas de vaiable.. \n");	}

}

void l1()
{
	if(symbole==v)
	{
		accepter(v);
		accepter(id);
		l1();
	}

}

void type()
{
		if(symbole == integer)
		accepter(integer);
		else {
		if (symbole==charr)
		accepter(charr);
			else
	{
	printf("type invalide ..\n");
	}
}

}

void inst_comp()
{
	if(symbole==begin)
	{
		accepter(begin);
		inst();
		accepter(end);
	}
		else
	{
	printf("erreur de begin end \n");
	}

}

void inst()
{
l_inst();
}

void l_inst()
{
		i();
		l_inst1();

}

void l_inst1()
{
	if(symbole==pv)
	{
		accepter(pv);
		i();
		l_inst1();
	}

}

void i()
{
	if(symbole==id)

	{   //traducteur
	    const char* ch = (char*)(pop(&pile));
        emmettre("valeurg");
        emmettre(ch);
        //
		accepter(id);
		//
        emmettre(":=");
        //
		accepter(aff);
		exp_simple();
	}
	else{
		if (symbole==iff)
		{
		accepter(iff);exp();accepter(then);
		// traducteur
        emmettre("Allersifaux sortie");
        //
		i();
		accepter(elsee);
		i();
		// traducteur
        emmettre("Etiq sortie");
        //
		}
			else{
				if (symbole==whilee)
		{
		accepter(whilee);
		// traducteur
		cree_Etiq();
        emmettre("Etiq Test");
        //
        exp();
        // traducteur
        cree_Etiq();
        emmettre("Allersifaux sortie");
        //
        accepter(doo);i();
        // traducteur
        cree_Etiq();
        emmettre("Allera test");
        cree_Etiq();
        emmettre("Etiq sortie");
        //
		}
			else{
		if (symbole==read)
		{
		accepter(read);accepter(po);;accepter(id);accepter(pf);
			}
			else{
			 if (symbole==readln)
		{
		accepter(readln);accepter(po);;accepter(id);accepter(pf);
			}
			else{
			if (symbole==write)
		{
		accepter(write);accepter(po);;accepter(id);accepter(pf);
			}
			else{
			if (symbole==writeln)
		{
		accepter(writeln);accepter(po);;accepter(id);accepter(pf);
			}


	}}}}}
}

}


void exp()
{

		exp_simple();
		exp1();

}

void exp1()
{
	if(symbole==opprel)
	{
		accepter(opprel);
		exp_simple();
	}

			else
	{
	printf("erreur pas de addition \n");
	}

}

void exp_simple()
{
		terme();
		exp_simple1();

}

void exp_simple1()
{
	if(symbole==oppadd)
	{
		accepter(oppadd);
		terme();
		exp_simple1();
	}


}

void terme()
{
	facteur();
	terme1();
}

void terme1()
{
		if(symbole==oppmul)
	{
		accepter(oppmul);
		// traducteur
		push(&pile1,'*');
		const char* ch = (char*)(pop(&pile));
        emmettre("Empiler");
        emmettre(ch);
        //
		facteur();
		terme1();
	}

}

void facteur()
{
		if(symbole==id){

		accepter(id);
		//traducteur
		const char* ch = (char*)(pop(&pile));
        emmettre("valeurd");
        emmettre(ch);
        //
		}
		else{
		if(symbole==nb){
        // traducteur
        emmettre("Empiler");
		const char* ch = (char*)(pop(&pile));
        emmettre(ch);
        //
		accepter(nb);}
			else{
			if(symbole==po)
			{
		accepter(po);
		exp_simple();
		accepter(pf);
		// traducteur
		const char* ch = (char*)(pop(&pile1));
        emmettre(ch);
        //
			}
		else
	{
	printf("erreur de id \n");
	}
}
}
}
void addToSymbolTable(int token, const char *lexeme)
{
    case_table newEntry;
    strcpy(newEntry.lexeme, lexeme);
    newEntry.token = token;
    table_symbole[symbolTableSize++] = newEntry;
}
void initSymbolTable()
{
    addToSymbolTable(program, "program");
    addToSymbolTable(id, "id");
    addToSymbolTable(pv, ";");
    addToSymbolTable(pt, ".");
    addToSymbolTable(var, "var");
    addToSymbolTable(dp, ":");
    addToSymbolTable(integer, "integer");
    addToSymbolTable(charr, "char");
    addToSymbolTable(begin, "begin");
    addToSymbolTable(end, "end");
    addToSymbolTable(v, ",");
    addToSymbolTable(aff, ":=");
    addToSymbolTable(iff, "if");
    addToSymbolTable(then, "then");
    addToSymbolTable(elsee, "else");
    addToSymbolTable(whilee, "while");
    addToSymbolTable(doo, "do");
    addToSymbolTable(read, "read");
    addToSymbolTable(readln, "readln");
    addToSymbolTable(write, "write");
    addToSymbolTable(writeln, "writeln");
    addToSymbolTable(po, "(");
    addToSymbolTable(pf, ")");
    addToSymbolTable(oppadd, "+");
    addToSymbolTable(opprel, "opprel");
    addToSymbolTable(oppmul, "*");


}
void Traducteur(){


   initSymbolTable();
   sourceFile = fopen("text.txt", "r");
    if (sourceFile == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier source");

    }

    symbole = symbole_suivant();

    p();




    if (symbole == EOF)
    {
        printf("\n******** Analyse syntaxique réussie ************\n");
    }
    else
    {
        printf("Erreur syntaxique.\n");
    }

    fclose(sourceFile);



}


int main()
{
	Traducteur();


    return 0;

}
