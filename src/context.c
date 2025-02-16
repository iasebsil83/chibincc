// ---------------- DEFINITIONS ----------------

//standards
#include "std.c"






// ---------------- NC ----------------

//NC syntax
const ulng NC__NAME_LENGTH_MAX = 64ULL; //this long: abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghabcd
const ubyt NC__SCOPE_INVALID = '\x00';
const ubyt NC__SCOPE_INTERN  = '\x01';
const ubyt NC__SCOPE_EXTERN  = '\x02';
const ubyt NC__SCOPE_SHARED  = '\x03';
const ubyt NC__SCOPE_LOCAL   = '\x04';

//data
typedef struct {
	boo  constant;
	str* type;
	str* name;
	ulng value;
	boo  global;
	byt  scope;
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

//type-related generated content : atoms
const uint ATOM__call = 22;
atm* call__toAtm(call* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__call;
	a->data = (ptr)e;
	return a;
}



//specific data structures
typedef struct {
	atm* condition;
	lst* block;      //lst[atm]
	lst* elifBlocks; //lst[atm] where each atm is a lst[atm], can be empty
	lst* elseBlock;  //lst[atm], can be NULL
} Xif;
typedef struct {
	dataItem* iterVar;
	atm*      condition;
	atm*      operation;
	lst*      block; //lst[atm]
} Xfor;
typedef struct {
	atm* condition;
	lst* block; //lst[atm]
} Xwhile;
typedef struct {
	atm* key;
	lst* block;
} switchEntry;
typedef struct {
	atm* condition;
	lst* entries; //lst[switchEntry]
} Xswitch;
const byt JUMP__BRK = '\x00';
const byt JUMP__CTN = '\x01';
const byt JUMP__RET = '\x02';
typedef byt Xjump;
typedef struct {
	str* srcType;
	str* name;
	byt  scope;
} Dcpy;
typedef struct {
	str* name;
	lst* fields; //lst[dataDcl]
	byt  scope;
} Dstc;
typedef struct {
	str* name;
	str* returnType;
	lst* params; //lst[dataDcl]
	lst* block; //lst[atm]
	byt  scope;
} Dfunction;

//type-related generated content : atoms
const uint ATOM__Xif = 24;
const uint ATOM__Xfor = 25;
const uint ATOM__Xwhile = 26;
const uint ATOM__switchEntry = 27;
const uint ATOM__Xswitch = 28;
const uint ATOM__Xjump = 29;
const uint ATOM__Dcpy = 30;
const uint ATOM__Dstc = 31;
const uint ATOM__Dfunction = 32;
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
atm* switchEntry__toAtm(switchEntry* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__switchEntry;
	a->data = (ptr)e;
	return a;
}
atm* Xswitch__toAtm(Xswitch* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__Xswitch;
	a->data = (ptr)e;
	return a;
}
atm* Xjump__toAtm(Xjump e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__Xjump;
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
	byt*  scope;
} type;
const uint ATOM__type = 33;
atm* type__toAtm(type* e) {
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
const uint ATOM__program = 34;
atm* program__toAtm(program* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__program;
	a->data = (ptr)e;
	return a;
}



//generated as soon as used
const uint ATOM__lst_atm = 35;
atm* lst_atm__toAtm(lst* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__lst_atm;
	a->data = (ptr)e;
	return a;
}
