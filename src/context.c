// ---------------- DEFINITIONS ----------------

//standards
#include "std.c"

//cycling calls
str* buildAssembly(lst* pproc_tokens, ulng depth);
lst* Tokenization__tokenize(Parsing__ctx* ctx, boo inSubContent);
lst* Value__readWholeInstructionBody(Parsing__ctx* ctx, boo inCall);

//values
const byt VALUE_ARG__NAME       = '\x00';
const byt VALUE_ARG__LITERAL1   = '\x01';
const byt VALUE_ARG__LITERAL2   = '\x02';
const byt VALUE_ARG__LITERAL4   = '\x03';
const byt VALUE_ARG__LITERAL8   = '\x04';
const byt VALUE_ARG__CALL       = '\x05';
const byt VALUE_ARG__SUBCONTENT = '\x06';
typedef struct {
	byt  id;
	ulng content;
} valueArg;



//NC syntax : ROLE
const ubyt NC__ROLE_DEFINITION = '\x00';
const ubyt NC__ROLE_EXECUTION  = '\x80';

//NC syntax : DEF SCOPE
const ubyt NC__DEF_SCOPE_INTERN = '\x00';
const ubyt NC__DEF_SCOPE_EXTERN = '\x40';
const ubyt NC__DEF_SCOPE_SHARED = '\x20';
const ubyt NC__DEF_SCOPE_LOCAL  = '\x60';

//NC syntax : EXE STATEMENT
const ubyt NC__EXE_STATEMENT_IF       = '\x00';
const ubyt NC__EXE_STATEMENT_FOR      = '\x08';
const ubyt NC__EXE_STATEMENT_WHILE    = '\x10';
const ubyt NC__EXE_STATEMENT_SWITCH   = '\x18';
const ubyt NC__EXE_STATEMENT_BREAK    = '\x20';
const ubyt NC__EXE_STATEMENT_CONTINUE = '\x28';
const ubyt NC__EXE_STATEMENT_RETURN   = '\x30';
const ubyt NC__EXE_STATEMENT_VFC      = '\x38';
const ubyt NC__EXE_STATEMENT_UNDEF1   = '\x40';
const ubyt NC__EXE_STATEMENT_UNDEF2   = '\x48';
const ubyt NC__EXE_STATEMENT_UNDEF3   = '\x50';
const ubyt NC__EXE_STATEMENT_UNDEF4   = '\x58';
const ubyt NC__EXE_STATEMENT_UNDEF5   = '\x60';
const ubyt NC__EXE_STATEMENT_UNDEF6   = '\x68';
const ubyt NC__EXE_STATEMENT_UNDEF7   = '\x70';
const ubyt NC__EXE_STATEMENT_ASSIGN   = '\x78';

//NC syntax : DEF SCOPE KIND
const ubyt NC__DEF_SCOPE_KIND_COPY      = '\x00';
const ubyt NC__DEF_SCOPE_KIND_STRUCTURE = '\x08';
const ubyt NC__DEF_SCOPE_KIND_FUNCTION  = '\x10';
const ubyt NC__DEF_SCOPE_KIND_DATA      = '\x18';

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
token* Token__new(Parsing__ctx* ctx, byt id) { //DON'T INSTANCIATE BODY !
	token* t = malloc(sizeof(token));
	t->id    = id;
	t->ctx   = Parsing__ctx__copy(ctx);
	return t;
}
void token__free(token* t) {

	//free value depending on what is stored inside
	switch(t->id) {
	}

	//free other fields & the structure itself
	lst__free(t->body, false);
	Parsing__ctx__free(t->ctx);
	free(t);
}






// ---------------- GENERIC ----------------

//error during global tokenization
void Tokenization__error(Parsing__ctx* ctx, str* s) {
	IO__printLF(Parsing__ctx__toStr(ctx));
	str* content = ctx->icontent->s;

	//get beginning & end of line
	ulng endIndex = ctx->icontent->index;
	while(endIndex < content->length){
		if(str__index(content, endIndex) == '\n') { break; }
		endIndex++;
	}

	//print full line
	str* concernedLine = str__sub(content, ctx->icontent->index - (ctx->columnNbr-1LL), endIndex);
	//IO__printChr('@');
	IO__printLF(concernedLine);
	//IO__printChr('@');
	str__free(concernedLine);

	//print position indicator
	ulng positionIndex     = ctx->columnNbr - 1LL;
	str* positionIndicator = Str__new(ctx->columnNbr);
	for(ulng i=0ULL; i < positionIndex; i++) { str__indexAssign(positionIndicator, i, ' '); }
	str__indexAssign(positionIndicator, positionIndex, '^');
	IO__printLF(positionIndicator);
	str__free(positionIndicator);

	//error
	Err__error(s, Err__FAILURE);
}
