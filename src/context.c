// ---------------- DEFINITIONS ----------------

//standards
#include "std.c"

//calls
typedef struct {
	str* name;
	lst* params; //lst[valueArg]
} call;

//values
#define VARG__NAME       ((byt)'\x00')
#define VARG__LITERAL1   ((byt)'\x01')
#define VARG__LITERAL2   ((byt)'\x02')
#define VARG__LITERAL4   ((byt)'\x03')
#define VARG__LITERAL8   ((byt)'\x04')
#define VARG__CALL       ((byt)'\x05')
#define VARG__SUBCONTENT ((byt)'\x06')
typedef struct {
	byt  id;
	ulng content;
} valueArg;



//NC syntax : ROLE
#define NC__ROLE_DEFINITION ((ubyt)'\x00')
#define NC__ROLE_EXECUTION  ((ubyt)'\x80') //C is just UNFAIR !!!!!!!!!
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

//tokens
typedef struct {
	ubyt          id;
	lst*          body; //lst[valueArg]
	Parsing__ctx* ctx;
} token;






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






// ---------------- GENERIC ----------------

//error during global tokenization
void Tokenization__error(Parsing__ctx* ctx, str* s) {
	Parsing__ctx__printLineIndicator(ctx, Log__LEVEL__ERROR);
	Log__errorLF(s, true, Err__FAILURE);
}
