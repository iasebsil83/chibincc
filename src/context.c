// ---------------- DEFINITIONS ----------------

//standards
#include "std.c"






// ---------------- VALUES ----------------

//id
#define VALUE__NAME       ((byt)'\x00')
#define VALUE__LITERAL1   ((byt)'\x01')
#define VALUE__LITERAL2   ((byt)'\x02')
#define VALUE__LITERAL4   ((byt)'\x03')
#define VALUE__LITERAL8   ((byt)'\x04')
#define VALUE__CALL       ((byt)'\x05')
#define VALUE__SUBCONTENT ((byt)'\x06')






// ---------------- TOKENS ----------------

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

//type-related generated content : atoms
const uint ATOM__dataItem = 20;
const uint ATOM__dataDcl = 21;
atm* dataItem__toAtm(dataItem* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__dataItem;
	a->data = (ptr)e;
	return a;
}
atm* dataDcl__toAtm(dataDcl* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__dataDcl;
	a->data = (ptr)e;
	return a;
}

//global data structures
typedef struct {
	str* name;
	lst* params; //lst[atm]
} call;
typedef struct {
	ubyt          id;
	ulng          content; //fixed type that depends on token ID
	Parsing__ctx* ctx;
} token;

//type-related generated content : atoms
const uint ATOM__call = 22;
const uint ATOM__token = 23;
atm* call__toAtm(call* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__call;
	a->data = (ptr)e;
	return a;
}
atm* token__toAtm(token* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__token;
	a->data = (ptr)e;
	return a;
}



//specific data structures
typedef struct {
	atm* condition;
	lst* block;      //lst[atm]
	lst* elifBlocks; //lst[lst[atm]], can be empty
	lst* elseBlock;  //lst[atm], can be NULL
} Xif;
typedef struct {
	dataItem* iterVar;
	atm*      iterVarInitValue;
	atm*      iterCondition;
	atm*      iterOperation;
	lst*      block; //lst[atm]
} Xfor;
typedef struct {
	atm* condition;
	lst* block; //lst[atm]
} Xwhile;
typedef struct {
	atm* condition;
	lst* keys;   //lst[atm]
	lst* blocks; //lst[atm]
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

//type-related generated content : atoms
const uint ATOM__Xif = 24;
const uint ATOM__Xfor = 25;
const uint ATOM__Xwhile = 26;
const uint ATOM__Xswitch = 27;
const uint ATOM__Dcpy = 28;
const uint ATOM__Dstc = 29;
const uint ATOM__Dfunction = 30;
atm* Xif__toAtm(Xif* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__Xif;
	a->data = (ptr)e;
	return a;
}
atm* Xfor__toAtm(Xfor* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__Xfor;
	a->data = (ptr)e;
	return a;
}
atm* Xwhile__toAtm(Xwhile* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__Xwhile;
	a->data = (ptr)e;
	return a;
}
atm* Xswitch__toAtm(Xswitch* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__Xswitch;
	a->data = (ptr)e;
	return a;
}
atm* Dcpy__toAtm(Dcpy* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__Dcpy;
	a->data = (ptr)e;
	return a;
}
atm* Dstc__toAtm(Dstc* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__Dstc;
	a->data = (ptr)e;
	return a;
}
atm* Dfunction__toAtm(Dfunction* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__Dfunction;
	a->data = (ptr)e;
	return a;
}

//program
typedef struct {
	ubyt* parentType;
	str*  name;
	boo   primitive;
	atm*  data;
} type;
const uint ATOM__type = 31;
atm* type__toAtm(program* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__type;
	a->data = (ptr)e;
	return a;
}

typedef struct {
	lst* types;     //lst[type]
	lst* globalDat; //lst[dataItem]
	lst* globalAsg; //lst[call]
	lst* functions; //lst[Dfunction]
} program;
const uint ATOM__program = 32;
atm* program__toAtm(program* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__program;
	a->data = (ptr)e;
	return a;
}
