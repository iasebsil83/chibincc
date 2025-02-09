// ---------------- IMPORTATIONS ----------------

//value parsing
#include "value.c"
#include "program.c"

//debug
#ifdef DEBUG_AVAILABLE
#include "debugTokens.c"
#endif






// ---------------- TOKEN INTEGRITY ----------------

//error shortcuts
void NC__errorIfGlobalScope(boo global) {
	if(global) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Unit only allowed in local scope.")); }
}
void NC__errorIfLocalScope(boo global) {
	if(!global) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Unit only allowed in global scope.")); }
}
valueArg* lst_valueArg__getRespectingID(lst* body, ulng index, ubyt targettedID, boo mustMatch) { //!mustMatch = mustNotMatch
	valueArg* v = (valueArg*)lst__index(body, index);
	if(mustMatch){
		if(v->id != targettedID) { Parsing__ctx__errorLF(ctx, str__add(ulng__toStr(index+1ULL), ctxt__toStr("th value of token has an invalid type here (must match ID %d).")) ); } //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< add ID
	}else{
		if(v->id == targettedID) { Parsing__ctx__errorLF(ctx, str__add(ulng__toStr(index+1ULL), ctxt__toStr("th value of token has an invalid type here (must NOT match ID %d).")) ); } //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< add ID
	}
	return v;
}
void NC__errorInAdditionnalIFBlock() {
	Parsing__ctx__errorLF(ctx, ctxt__toStr("Expected NAME value \"i\" or \"e\" in additionnal IF block."));
}



//specific token reading : Type copy
atm* NC__newDef_TypeCopy(Parsing__ctx* ctx, program* prog, boo global, ubyt scope) {
	NC__errorIfLocalScope(global);

	//read value list given with NC instruction
	lst* body = Lst__new();
	Value__readWholeInstructionBody(ctx, body, false);

	//create instance
	d_cpy* instance = malloc(sizeof(d_cpy));

	//mandatory elements
	ulng bodyLength = lst__length(body);
	if(bodyLength != 2ULL) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Missing value in IF statement (at least 2 required).")); }

	//name
	valueArg* v    = lst_valueArg__getRespectingID(body, 0ULL, VARG__NAME, true);
	instance->name = (str*)(v->content);
	free(v);

	//srcType
	v                 = lst_valueArg__getRespectingID(body, 0ULL, VARG__NAME, true);
	instance->srcType = (str*)(v->content);
	free(v);

	//free body structure (that should only refer to freed elements now)
	lst__free(body, false);

	//return as generic token
	token* tok   = Token__new(ctx, NC__ROLE_DEFINITION | scope | NC__DEF_SCOPE_KIND_COPY);
	tok->content = (ulng)instance;
	return tok;
}



//specific token reading : Type structure
token* NC__newDef_Structure(Parsing__ctx* ctx, ubyt scope) {
	token* tok = Token__new(ctx, NC__ROLE_DEFINITION | scope | NC__DEF_SCOPE_KIND_STRUCTURE);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}



//specific token reading : Function
token* NC__newDefinitionToken_Function(Parsing__ctx* ctx, ubyt scope) {
	token* tok = Token__new(ctx, NC__ROLE_DEFINITION | scope | NC__DEF_SCOPE_KIND_FUNCTION);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}



//specific token reading : Data item
token* NC__newDefinitionToken_DataItem(Parsing__ctx* ctx, ubyt scope) {
	token* tok = Token__new(ctx, NC__ROLE_DEFINITION | scope | NC__DEF_SCOPE_KIND_DATA);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}



//specific token reading : If
atm* NC__newExe__If(Parsing__ctx* ctx, boo global) {
	NC__errorIfGlobalScope(global);

	//read value list given with NC instruction
	lst* body = Value__readWholeInstructionBody(ctx, false);

	//create instance
	x_if* instance = malloc(sizeof(x_if));
	instance->elifBlocks = Lst__new();
	instance->elseBlock  = NULL;

	//mandatory elements
	ulng bodyLength = lst__length(body);
	if(bodyLength < 2ULL) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Missing value in IF statement (at least 2 required).")); }

	//1:condition
	instance->condition = lst_valueArg__getRespectingID(body, 0ULL, VARG__SUBCONTENT, false);

	//2:first block
	valueArg* v     = lst_valueArg__getRespectingID(body, 1ULL, VARG__SUBCONTENT, true);
	instance->block = (lst*)(v->content); //lst[token]
	free(v);

	//additionnal block(s)
	ulng      valueIndex  = 2ULL;
	str*      textContent;
	lst*      currentBlock; //lst[token]
	while(valueIndex < bodyLength) {
		if(instance->elseBlock != NULL) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Cannot have another IF additionnal block after ELSE.")); }

		//elif-else indicator (just extracting it for the moment)
		v = lst_valueArg__getRespectingID(body, valueIndex, VARG__NAME, true);
		textContent = (str*)(v->content);
		free(v);
		valueIndex++;

		//associated subcontent
		if(valueIndex >= bodyLength) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Missing subcontent in IF additionnal block.")); }
		v            = lst_valueArg__getRespectingID(body, valueIndex, VARG__SUBCONTENT, true);
		currentBlock = (lst*)(v->content);
		free(v);
		valueIndex++;

		//now, analyse indicator
		if(textContent->length != 1ULL) { NC__errorInAdditionnalIFBlock(); }
		switch(str__index(textContent, 0ULL)) {
			case 'i': lst__append(instance->elifBlocks, currentBlock); break;
			case 'e': instance->elseBlock = currentBlock;              break;
			default:  NC__errorInAdditionnalIFBlock();
		}
	}

	//free body structure (that should only refer to freed elements now)
	lst__free(body, false);

	//return as generic token
	token* tok   = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_IF);
	tok->content = (ulng)instance;
	return tok;
}



//specific token reading : For
token* NC__newExe__For(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_FOR);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}



//specific token reading : While
token* NC__newExe__While(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_WHILE);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}



//specific token reading : Switch
token* NC__newExe__Switch(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_SWITCH);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}



//specific token reading : Break
token* NC__newExe__Break(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_BREAK);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}



//specific token reading : Continue
token* NC__newExe__Continue(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_CONTINUE);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}



//specific token reading : Return
token* NC__newExe__Return(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_RETURN);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}



//specific token reading : Void-returning Function Call
token* NC__newExe__VFC(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_VFC);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}






// ---------------- MAIN EXECUTION ----------------

//redirection from any NC unit to its specific parsing function
atm* NC__parseOne(Parsing__ctx* ctx, boo global) {

	//read next useful character
	while(true) {
		if(Parsing__ctx__inc(ctx)) { return NULL; } //no more unit to read
		chr c = Parsing__ctx__get(ctx);             //NULL means end-of-program OR end-of-subcontent if global=false

		//skip beginning indent or line feed
		if(c != '\t' && c != '\n') { break; }
	}

	//1st rank : ROLE
	ubyt scope;
	switch(c) {



		//DEF
		case 'd':
			#ifdef DEBUG_AVAILABLE
			Parsing__ctx__debug(ctx, "DEF {");
			#endif

			//2nd rank : DEF SCOPE
			if(Parsing__ctx__inc(ctx)) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Missing DEF SCOPE.")); }
			c = Parsing__ctx__get(ctx);
			scope = NC__DEF_SCOPE_INVALID;
			switch(c) {
				case 'i':
					if(scope == NC__DEF_SCOPE_INVALID) { scope = NC__DEF_SCOPE_INTERN; }
				case 'x':
					if(scope == NC__DEF_SCOPE_INVALID) { scope = NC__DEF_SCOPE_EXTERN; }
				case 's':
					if(scope == NC__DEF_SCOPE_INVALID) { scope = NC__DEF_SCOPE_SHARED; }
				case 'l':
					if(scope == NC__DEF_SCOPE_INVALID) { scope = NC__DEF_SCOPE_LOCAL;  }

					//3rd rank : DEF SCOPE KIND
					if(Parsing__ctx__inc(ctx)) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Missing DEF SCOPE KIND.")); }
					switch(Parsing__ctx__get(ctx)){
						case 'c': return NC__newDef_TypeCopy( ctx, global, scope);
						case 's': return NC__newDef_Structure(ctx, global, scope);
						case 'f': return NC__newDef_Function( ctx, global, scope);
						case 'd': return NC__newDef_DataItem( ctx, global, scope);
						default: Parsing__ctx__errorLF(ctx, ctxt__toStr("Missing DEF SCOPE KIND."));
					}
				break;
				default: Parsing__ctx__errorLF(ctx, ctxt__toStr("Invalid DEF SCOPE given."));
			}
			#ifdef DEBUG_AVAILABLE
			Parsing__ctx__debug(ctx, "} DEF");
			#endif
		break;



		//EXE
		case 'x':
			#ifdef DEBUG_AVAILABLE
			Parsing__ctx__debug(ctx, "EXE {");
			#endif

			//2nd rank : EXE STATEMENT
			if(Parsing__ctx__inc(ctx)) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Invalid DEF SCOPE given.")); }
			switch(Parsing__ctx__get(ctx)) {
				case 'i': return NC__newExe__If(      ctx, global);
				case 'f': return NC__newExe__For(     ctx, global);
				case 'w': return NC__newExe__While(   ctx, global);
				case 's': return NC__newExe__Switch(  ctx, global);
				case 'b': return NC__newExe__Break(   ctx, global);
				case 'c': return NC__newExe__Continue(ctx, global);
				case 'r': return NC__newExe__Return(  ctx, global);
				case 'v': return NC__newExe__VFC(     ctx, global);
				default: Parsing__ctx__errorLF(ctx, ctxt__toStr("Invalid EXE STATEMENT given."));
			}
			#ifdef DEBUG_AVAILABLE
			Parsing__ctx__debug(ctx, "} EXE");
			#endif
		break;

		//end of local subcontent
		case '}':
			if(global) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Can't have end-of-local-subcontent '}' in global scope.")); }
			return NULL; //special value meaning end-of-subcontent
		break;

		//undefined
		default: Parsing__ctx__errorLF(ctx, ctxt__toStr("Invalid ROLE given."));
	}

	//should never be executed
	//<<<<<<<<<<<<<<<<<<<<< internal error to put here
	return NULL;
}

//parsing entry point
program* NC__parse(Parsing__ctx* ctx, str* outputPath) { //outputPath for debug only
	str* ASG = ctxt__toStr("asg");

	//prepare whole program instance
	program* p = malloc(sizeof(program));
	p->types     = Lst__new();
	p->globalDat = Lst__new();
	p->globalAsg = Lst__new();
	p->functions = Lst__new();

	//parse NC units until end-of-program
	while(true) {
		atm* a = NC__parseOne(ctx, true);

		//reached end-of-program
		if(a == NULL) { break; }

		//distribute unit to correct program stucture location
		switch(a->id) {
			case ATOM__type:
				lst__append(p->types, (ubyt*)a->data);
			break;
			case ATOM__dataItem:
				lst__append(p->globalDat, (ubyt*)a->data);
			break;
			case ATOM__call: {
				call* c = (call*)(a->data);
				if(!str__equal(c->name, ASG)) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Only \"asg\" calls are allowed in global scope.")); }
				lst__append(p->globalAsg, (ubyt*)a->data);
			} break;
			case ATOM__Dfunction:
				lst__append(p->functions, (ubyt*)a->data);
			break;
			default:
				Parsing__ctx__errorLF(ctx, ctxt__toStr("Instruction not allowed in global scope."));
		}
		free(a); //free atom structure BUT NOT ITS DATA (data is now held into program structure)
	}

	//debug
	#ifdef DEBUG_AVAILABLE
	if(Log__level <= Log__LEVEL__DEBUG) {
		str* ending = ctxt__toStr(".prg"); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< to remove using constant
		str* debugOutputPath = str__add(outputPath, ending);
		str* debugOutput     = Program__toStr(p, 0ULL);
		IO__writeFile(debugOutputPath, debugOutput);
		str__free(ending); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< as well
		str__free(debugOutputPath);
		str__free(debugOutput);
	}
	#endif

	//program is good
	str__free(ASG);
	return p;
}
