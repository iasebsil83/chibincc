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

//type-related generated content : toStr
str* dataItem__toStr(dataItem* e, ulng depth) { //default generation
	str* result = Str__new(0ULL);
	str* BEGINNING = ctxt__toStr("dataItem{");
	result = str__addSelf(result, BEGINNING);
	str__free(BEGINNING);

	//prepare depth spacing
	boo hasDepth    = (depth != -1LL);
	str* depthSpace = NULL;
	if(hasDepth) {
		depthSpace = Str__new(depth);
		str__fill(depthSpace, '\t');
	}

	//field1 : type
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD1 = ctxt__toStr("type:"); //name
	result = str__addSelf(result, FIELD1);
	str__free(FIELD1);
	str* fieldValue = str__toStr(e->type); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//field2 : name
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD2 = ctxt__toStr("name:"); //name
	result = str__addSelf(result, FIELD2);
	str__free(FIELD2);
	fieldValue = str__toStr(e->name); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//field3 : value
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD3 = ctxt__toStr("value:"); //name
	result = str__addSelf(result, FIELD3);
	str__free(FIELD3);
	fieldValue = ulng__toStr(e->value); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//field4 : global
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD4 = ctxt__toStr("global:"); //name
	result = str__addSelf(result, FIELD4);
	str__free(FIELD4);
	fieldValue = boo__toStr(e->global); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);

	//field5 : offset
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD5 = ctxt__toStr("offset:"); //name
	result = str__addSelf(result, FIELD5);
	str__free(FIELD5);
	fieldValue = ulng__toStr(e->offset); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);

	//last spacing
	if(hasDepth) {
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
	}
	result = str__addChrSelf(result, '}');
	return result;
}
str* dataDcl__toStr(dataDcl* e, ulng depth) { //default generation
	str* result = Str__new(0ULL);
	str* BEGINNING = ctxt__toStr("dataDcl{");
	result = str__addSelf(result, BEGINNING);
	str__free(BEGINNING);

	//prepare depth spacing
	boo hasDepth    = (depth != -1LL);
	str* depthSpace = NULL;
	if(hasDepth) {
		depthSpace = Str__new(depth);
		str__fill(depthSpace, '\t');
	}

	//field1 : type
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD1 = ctxt__toStr("type:"); //name
	result = str__addSelf(result, FIELD1);
	str__free(FIELD1);
	str* fieldValue = str__toStr(e->type); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//field2 : name
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD2 = ctxt__toStr("name:"); //name
	result = str__addSelf(result, FIELD2);
	str__free(FIELD2);
	fieldValue = str__toStr(e->name); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//last spacing
	if(hasDepth) {
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
	}
	result = str__addChrSelf(result, '}');
	return result;
}



//global data structures
typedef struct {
	str* name;
	lst* params; //lst[dataDcl]
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

//type-related generated content : toStr
str* lst_dataDcl__toStr(lst* e, ulng depth) { //manual override
	str* result = ctxt__toStr("[");

	//prepare depth spacing
	boo hasDepth    = (depth != -1LL);
	str* depthSpace = NULL;
	if(hasDepth) {
		depthSpace = Str__new(depth);
		str__fill(depthSpace, '\t');
	}

	//for each element
	for(ulng i=0ULL; i < e->length; i++) {

		//spacing
		if(hasDepth) {
			result = str__addChrSelf(result, '\n');
			result = str__addSelf(result, depthSpace);
			result = str__addChrSelf(result, '\t');
		}

		//item
		str* itemValue = dataDcl__toStr((dataDcl*)lst__index(e, i)); //data
		result = str__addSelf(result, itemValue);
		str__free(itemValue);
		result = str__addChrSelf(result, ',');
	}

	//last spacing
	if(hasDepth) {
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
	}
	result = str__addChrSelf(result, ']');
	return result;
}
str* call__toStr(call* e, ulng depth) { //default generation
	str* result = Str__new(0ULL);
	str* BEGINNING = ctxt__toStr("call{");
	result = str__addSelf(result, BEGINNING);
	str__free(BEGINNING);

	//prepare depth spacing
	boo hasDepth    = (depth != -1LL);
	str* depthSpace = NULL;
	if(hasDepth) {
		depthSpace = Str__new(depth);
		str__fill(depthSpace, '\t');
	}

	//field1 : name
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD1 = ctxt__toStr("name:"); //name
	result = str__addSelf(result, FIELD1);
	str__free(FIELD1);
	str* fieldValue = str__toStr(e->name); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//field2 : params
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD2 = ctxt__toStr("params:"); //name
	result = str__addSelf(result, FIELD2);
	str__free(FIELD2);
	fieldValue = lst_dataDcl__toStr(e->params, depth+1ULL); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//last spacing
	if(hasDepth) {
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
	}
	result = str__addChrSelf(result, '}');
	return result;
}
str* token__toStr(token* e, ulng depth) { //default generation
	str* result = Str__new(0ULL);
	str* BEGINNING = ctxt__toStr("token{");
	result = str__addSelf(result, BEGINNING);
	str__free(BEGINNING);

	//prepare depth spacing
	boo hasDepth    = (depth != -1LL);
	str* depthSpace = NULL;
	if(hasDepth) {
		depthSpace = Str__new(depth);
		str__fill(depthSpace, '\t');
	}

	//field1 : id
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD1 = ctxt__toStr("id:"); //name
	result = str__addSelf(result, FIELD1);
	str__free(FIELD1);
	str* fieldValue = ubyt__toStr(e->id); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//field2 : content
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD2 = ctxt__toStr("content:"); //name
	result = str__addSelf(result, FIELD2);
	str__free(FIELD2);
	fieldValue = ulng__toStr(e->content); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//field3 : ctx
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD3 = ctxt__toStr("ctx:"); //name
	result = str__addSelf(result, FIELD3);
	str__free(FIELD3);
	fieldValue = Parsing__ctx__toStr(e->ctx, depth+1ULL); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//last spacing
	if(hasDepth) {
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
	}
	result = str__addChrSelf(result, '}');
	return result;
}



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

//type-related generated content : toStr
str* lst_dataDcl__toStr(lst* e, ulng depth) { //manual override
	str* result = ctxt__toStr("[");

	//prepare depth spacing
	boo hasDepth    = (depth != -1LL);
	str* depthSpace = NULL;
	if(hasDepth) {
		depthSpace = Str__new(depth);
		str__fill(depthSpace, '\t');
	}

	//for each element
	for(ulng i=0ULL; i < e->length; i++) {

		//spacing
		if(hasDepth) {
			result = str__addChrSelf(result, '\n');
			result = str__addSelf(result, depthSpace);
			result = str__addChrSelf(result, '\t');
		}

		//item
		str* itemValue = dataDcl__toStr((dataDcl*)lst__index(e, i)); //data
		result = str__addSelf(result, itemValue);
		str__free(itemValue);
		result = str__addChrSelf(result, ',');
	}

	//last spacing
	if(hasDepth) {
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
	}
	result = str__addChrSelf(result, ']');
	return result;
}
str* call__toStr(call* e, ulng depth) { //default generation
	str* result = Str__new(0ULL);
	str* BEGINNING = ctxt__toStr("call{");
	result = str__addSelf(result, BEGINNING);
	str__free(BEGINNING);

	//prepare depth spacing
	boo hasDepth    = (depth != -1LL);
	str* depthSpace = NULL;
	if(hasDepth) {
		depthSpace = Str__new(depth);
		str__fill(depthSpace, '\t');
	}

	//field1 : name
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD1 = ctxt__toStr("name:"); //name
	result = str__addSelf(result, FIELD1);
	str__free(FIELD1);
	str* fieldValue = str__toStr(e->name); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//field2 : params
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD2 = ctxt__toStr("params:"); //name
	result = str__addSelf(result, FIELD2);
	str__free(FIELD2);
	fieldValue = lst_dataDcl__toStr(e->params, depth+1ULL); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//last spacing
	if(hasDepth) {
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
	}
	result = str__addChrSelf(result, '}');
	return result;
}
str* token__toStr(token* e, ulng depth) { //default generation
	str* result = Str__new(0ULL);
	str* BEGINNING = ctxt__toStr("token{");
	result = str__addSelf(result, BEGINNING);
	str__free(BEGINNING);

	//prepare depth spacing
	boo hasDepth    = (depth != -1LL);
	str* depthSpace = NULL;
	if(hasDepth) {
		depthSpace = Str__new(depth);
		str__fill(depthSpace, '\t');
	}

	//field1 : id
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD1 = ctxt__toStr("id:"); //name
	result = str__addSelf(result, FIELD1);
	str__free(FIELD1);
	str* fieldValue = ubyt__toStr(e->id); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//field2 : content
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD2 = ctxt__toStr("content:"); //name
	result = str__addSelf(result, FIELD2);
	str__free(FIELD2);
	fieldValue = ulng__toStr(e->content); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//field3 : ctx
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD3 = ctxt__toStr("ctx:"); //name
	result = str__addSelf(result, FIELD3);
	str__free(FIELD3);
	fieldValue = Parsing__ctx__toStr(e->ctx, depth+1ULL); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//last spacing
	if(hasDepth) {
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
	}
	result = str__addChrSelf(result, '}');
	return result;
}



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
