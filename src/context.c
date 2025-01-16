// ---------------- DEFINITIONS ----------------

//standards
#include "std.c"






// VALUES

//id
#define VALUE__NAME       ((byt)'\x00')
#define VALUE__LITERAL1   ((byt)'\x01')
#define VALUE__LITERAL2   ((byt)'\x02')
#define VALUE__LITERAL4   ((byt)'\x03')
#define VALUE__LITERAL8   ((byt)'\x04')
#define VALUE__CALL       ((byt)'\x05')
#define VALUE__SUBCONTENT ((byt)'\x06')

//specific data structures
typedef struct {
	byt  id;
	ulng content;
} value;






// TOKENS

//NC syntax : ROLE
#define NC__ROLE_DEFINITION ((ubyt)'\x00')
#define NC__ROLE_EXECUTION  ((ubyt)'\x80')
#define NC__ROLE_MASK       ((ubyt)'\x80')

//NC syntax : DEF SCOPE
#define NC__DEF_SCOPE_INTERN  ((ubyt)'\x00')
#define NC__DEF_SCOPE_EXTERN  ((ubyt)'\x40')
#define NC__DEF_SCOPE_SHARED  ((ubyt)'\x20')
#define NC__DEF_SCOPE_LOCAL   ((ubyt)'\x60')
#define NC__DEF_SCOPE_MASK    ((ubyt)'\x60')
#define NC__DEF_SCOPE_INVALID ((ubyt)'\xff') //value not allowed for DEF_SCOPE

//NC syntax : EXE STATEMENT
#define NC__EXE_STATEMENT_IF       ((ubyt)'\x00')
#define NC__EXE_STATEMENT_FOR      ((ubyt)'\x08')
#define NC__EXE_STATEMENT_WHILE    ((ubyt)'\x10')
#define NC__EXE_STATEMENT_SWITCH   ((ubyt)'\x18')
#define NC__EXE_STATEMENT_BREAK    ((ubyt)'\x20')
#define NC__EXE_STATEMENT_CONTINUE ((ubyt)'\x28')
#define NC__EXE_STATEMENT_RETURN   ((ubyt)'\x30')
#define NC__EXE_STATEMENT_VFC      ((ubyt)'\x38')
#define NC__EXE_STATEMENT_UNDEF1   ((ubyt)'\x40')
#define NC__EXE_STATEMENT_UNDEF2   ((ubyt)'\x48')
#define NC__EXE_STATEMENT_UNDEF3   ((ubyt)'\x50')
#define NC__EXE_STATEMENT_UNDEF4   ((ubyt)'\x58')
#define NC__EXE_STATEMENT_UNDEF5   ((ubyt)'\x60')
#define NC__EXE_STATEMENT_UNDEF6   ((ubyt)'\x68')
#define NC__EXE_STATEMENT_UNDEF7   ((ubyt)'\x70')
#define NC__EXE_STATEMENT_UNDEF8   ((ubyt)'\x78')
#define NC__EXE_STATEMENT_MASK     ((ubyt)'\x78')

//NC syntax : DEF SCOPE KIND
#define NC__DEF_SCOPE_KIND_COPY      ((ubyt)'\x00')
#define NC__DEF_SCOPE_KIND_STRUCTURE ((ubyt)'\x08')
#define NC__DEF_SCOPE_KIND_FUNCTION  ((ubyt)'\x10')
#define NC__DEF_SCOPE_KIND_DATA      ((ubyt)'\x18')
#define NC__DEF_SCOPE_KIND_MASK      ((ubyt)'\x18')

//NC syntax : LIMITS
const ulng NC__NAME_LENGTH_MAX = 64ULL; //looks like this: abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghabcd

//data
typedef struct {
	str* type;
	str* name;
	ulng value;
	boo  global;
	ulng offset; //for ASM generation
} dataItem;
typedef struct {
	str* type;
	str* name;
} dataDcl;

//global data structures
typedef struct {
	str* name;
	lst* params; //lst[value]
} call;
typedef struct {
	ubyt          id;
	ulng          content; //variable type
	Parsing__ctx* ctx;
} token;

//specific data structures
typedef struct {
	value* condition;
	lst*   block;      //lst[token]
	lst*   elifBlocks; //lst[lst[token]], can be empty
	lst*   elseBlock;  //lst[token], can be NULL
} Xif;
typedef struct {
	dataItem* iterVar;
	value*    iterVarInitValue;
	value*    iterCondition;
	value*    iterOperation;
	lst*      block; //lst[token]
} Xfor;
typedef struct {
	value* condition;
	value* block;
} Xwhile;
typedef struct {
	value* condition;
	lst*   keys;   //lst[value]
	lst*   blocks; //lst[value]
} Xswitch;
typedef struct {
	str* srcType;
	str* name;
} Dcpy;
typedef struct {
	str* name;
	lst* fields; //lst[dataDcl]
} Dstc;
typedef struct {
	str* name;
	str* returnType;
	lst* params; //lst[dataDcl]
} Dfunction;

//program
typedef struct {
	lst* cpyTypes;  //lst[Dcpy]
	lst* stcTypes;  //lst[Dstc]
	lst* globalDat; //lst[dataItem]
	lst* globalAsg; //lst[call]
	lst* functions; //lst[Dfunction]
} program;






// ---------------- TOOLS ----------------

//token
token* Token__new(Parsing__ctx* ctx, ubyt id) { //DON'T INSTANCIATE BODY !
	token* t = malloc(sizeof(token));
	t->id    = id;
	t->ctx   = Parsing__ctx__copy(ctx);
	t->body  = NULL;
	return t;
}
void token__free(token* t) {
	if(t->body != NULL) { lst__free(t->body, false); }
	Parsing__ctx__free(t->ctx);
	free(t);
}
