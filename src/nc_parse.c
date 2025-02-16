// ---------------- IMPORTATIONS ----------------

//value parsing
#include "value.c"

//debug
#ifdef DEBUG_AVAILABLE
//#include "debugTokens.c"
#endif






// ---------------- SPECIFIC UNIT PARSING ----------------

//general error shortcuts
void NC__errorIfGlobalScope(Parsing__ctx* ctx, boo global) {
	if(global) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Unit only allowed in local scope.")); }
}
void NC__errorIfLocalScope(Parsing__ctx* ctx, boo global) {
	if(!global) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Unit only allowed in global scope.")); }
}
atm* lst_atm__getRespectingID(Parsing__ctx* ctx, lst* body, ulng index, ubyt targettedID, boo mustMatch) { //!mustMatch = mustNotMatch
	atm* a = (atm*)lst__index(body, index);
	if(mustMatch){
		if(a->id != targettedID) { Parsing__ctx__errorLF(ctx, str__add(ulng__toStr(index+1ULL), ctxt__toStr("th value of unit has an invalid type here (must match ID %d).")) ); } //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< add ID
	}else{
		if(a->id == targettedID) { Parsing__ctx__errorLF(ctx, str__add(ulng__toStr(index+1ULL), ctxt__toStr("th value of unit has an invalid type here (must NOT match ID %d).")) ); } //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< add ID
	}
	return a;
}



//specific parsing: Type copy
atm* NC__newDef_TypeCopy(Parsing__ctx* ctx, boo global, byt scope) {
	NC__errorIfLocalScope(ctx, global);

	//read value list given with NC instruction
	lst* body = Lst__new();
	Value__readWholeInstructionBody(ctx, body, false);

	//create instance
	Dcpy* instance  = malloc(sizeof(Dcpy));
	instance->scope = scope;

	//mandatory elements
	ulng bodyLength = lst__length(body);
	if(bodyLength != 2ULL) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Missing value in type copy declaration (2 required).")); }

	//name
	atm* a         = lst_atm__getRespectingID(ctx, body, 0ULL, ATOM__str, true);
	instance->name = (str*)(a->data);
	free(a);

	//srcType
	a                 = lst_atm__getRespectingID(ctx, body, 1ULL, ATOM__str, true);
	instance->srcType = (str*)(a->data);
	free(a);

	//free body structure (that should only refer to freed elements now)
	lst__free(body, false);

	//return as generic atm
	return Dcpy__toAtm(instance);
}



//specific parsing: Type structure
atm* NC__newDef_Structure(Parsing__ctx* ctx, boo global, byt scope) {
	NC__errorIfLocalScope(ctx, global);

	//read value list given with NC instruction
	lst* body = Lst__new();
	Value__readWholeInstructionBody(ctx, body, false);

	//create instance
	Dstc* instance  = malloc(sizeof(Dstc));
	instance->scope = scope;

	//mandatory elements
	ulng bodyLength = lst__length(body);
	if(bodyLength <= 2ULL) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Missing value in structure type declaration (at least 3 required).")); }

	//name
	atm* a         = lst_atm__getRespectingID(ctx, body, 0ULL, ATOM__str, true);
	instance->name = (str*)(a->data);
	free(a);

	//check fields length: without the beginning name, we must have a pair number of values (=> 2 values per field)
	if(bodyLength%2ULL == 0ULL) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Incomplete field in structure type declaration (must have 2 values per field).")); }
	ulng fieldsNumber = (bodyLength-1LL)/2ULL;

	//fields
	instance->fields = Lst__new();
	for(ulng f=0ULL; f < fieldsNumber; f++) {
		dataDcl* dd = malloc(sizeof(dataDcl));

		//read field type
		a = lst_atm__getRespectingID(ctx, body, 1ULL + 2ULL*f, ATOM__str, true);
		dd->type = (str*)(a->data);
		free(a);

		//read field name
		a = lst_atm__getRespectingID(ctx, body, 2ULL + 2ULL*f, ATOM__str, true);
		dd->name = (str*)(a->data);
		free(a);

		//store field
		lst__append(instance->fields, (ubyt*)dd);
	}

	//free body structure (that should only refer to freed elements now)
	lst__free(body, false);

	//return as generic atm
	return Dstc__toAtm(instance);
}



//specific parsing: Function
atm* NC__newDef_Function(Parsing__ctx* ctx, boo global, byt scope) {
	NC__errorIfLocalScope(ctx, global);

	//read value list given with NC instruction
	lst* body = Lst__new();
	Value__readWholeInstructionBody(ctx, body, false);

	//create instance
	Dfunction* instance = malloc(sizeof(Dfunction));
	instance->scope     = scope;

	//mandatory elements
	ulng bodyLength = lst__length(body);
	if(bodyLength <= 2ULL) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Missing value in function declaration (at least 3 required).")); }

	//return type
	atm* a               = lst_atm__getRespectingID(ctx, body, 0ULL, ATOM__str, true);
	instance->returnType = (str*)(a->data);
	free(a);

	//name
	a              = lst_atm__getRespectingID(ctx, body, 1ULL, ATOM__str, true);
	instance->name = (str*)(a->data);
	free(a);

	//block <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< DONT CHECK INSIDE BLOCKS FOR THE MOMENT
	a               = lst_atm__getRespectingID(ctx, body, bodyLength-1LL, ATOM__lst_atm, true);
	instance->block = (str*)(a->data);
	free(a);

	//check parameters: without return type, name, and block, we must have a pair number of values (=> 2 values per parameter)
	if(bodyLength%2ULL == 0ULL) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Incomplete parameter in function declaration (must have 2 values per parameter).")); }
	ulng paramsNumber = (bodyLength-3LL)/2ULL;

	//fields
	instance->params = Lst__new();
	for(ulng p=0ULL; p < paramsNumber; p++) {
		dataDcl* dd = malloc(sizeof(dataDcl));

		//read param type
		a = lst_atm__getRespectingID(ctx, body, 2ULL + 2ULL*p, ATOM__str, true);
		dd->type = (str*)(a->data);
		free(a);

		//read param name
		a = lst_atm__getRespectingID(ctx, body, 3ULL + 2ULL*p, ATOM__str, true);
		dd->name = (str*)(a->data);
		free(a);

		//store param
		lst__append(instance->params, (ubyt*)dd);
	}

	//free body structure (that should only refer to freed elements now)
	lst__free(body, false);

	//return as generic atm
	return Dfunction__toAtm(instance);
}



//specific parsing: Data item
atm* NC__newDef_DataItem(Parsing__ctx* ctx, boo global, byt scope) {

	//read value list given with NC instruction
	lst* body = Lst__new();
	Value__readWholeInstructionBody(ctx, body, false);

	//create instance
	dataItem* instance = malloc(sizeof(dataItem));
	instance->global   = global;

	//mandatory elements
	ulng bodyLength = lst__length(body);
	if(bodyLength != 3ULL) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Missing value in data item declaration (3 required).")); }

	//behavior
	atm* a = lst_atm__getRespectingID(ctx, body, 0ULL, ATOM__str, true);
	str* s = (str*)(a->data);
	free(a);
	if(s->length != 1ULL) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Incorect behavior in data item declaration (only 1 character expected).")); }
	switch(str__index(s, 0ULL)){
		case 'c': instance->constant = true;  break;
		case 'v': instance->constant = false; break;
		default:  Parsing__ctx__errorLF(ctx, ctxt__toStr("Incorect behavior in data item declaration ('c' or 'v' expected)."));
	}
	str__free(s);

	//type
	a              = lst_atm__getRespectingID(ctx, body, 1ULL, ATOM__str, true);
	instance->type = (str*)(a->data);
	free(a);

	//name
	a              = lst_atm__getRespectingID(ctx, body, 2ULL, ATOM__str, true);
	instance->name = (str*)(a->data);
	free(a);

	//free body structure (that should only refer to freed elements now)
	lst__free(body, false);

	//return as generic atm
	return dataItem__toAtm(instance);
}



//specific parsing: If
atm* NC__newExe__If(Parsing__ctx* ctx, boo global) {
	NC__errorIfGlobalScope(ctx, global);

	//read value list given with NC instruction
	lst* body = Lst__new();
	Value__readWholeInstructionBody(ctx, body, false);

	//create instance
	Xif* instance = malloc(sizeof(Xif));
	instance->elifBlocks = Lst__new();
	instance->elseBlock  = NULL;

	//mandatory elements
	ulng bodyLength = lst__length(body);
	if(bodyLength < 2ULL) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Missing value in IF statement (at least 2 required).")); }

	//1:condition
	instance->condition = lst_atm__getRespectingID(ctx, body, 0ULL, ATOM__lst_atm, false);

	//2:first block <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< DONT CHECK INSIDE BLOCKS FOR THE MOMENT
	atm* a          = lst_atm__getRespectingID(ctx, body, 1ULL, ATOM__lst_atm, true);
	instance->block = (lst*)(a->data);
	free(a);

	//additionnal block(s)
	ulng      bodyIndex = 2ULL;
	str*      textContent;
	lst*      currentBlock; //lst[atm]
	while(bodyIndex < bodyLength) {
		if(instance->elseBlock != NULL) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Cannot have another IF additionnal block after ELSE.")); }

		//elif-else indicator (just extracting it for the moment)
		a = lst_atm__getRespectingID(ctx, body, bodyIndex, ATOM__str, true);
		textContent = (str*)(a->data);
		free(a);
		bodyIndex++;

		//associated subcontent
		if(bodyIndex >= bodyLength) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Missing associated subcontent in IF additionnal block.")); }
		currentBlock = lst_atm__getRespectingID(ctx, body, bodyIndex, ATOM__lst_atm, true); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< DONT CHECK INSIDE BLOCKS FOR THE MOMENT
		bodyIndex++;

		//now, analyse indicator
		if(textContent->length != 1ULL) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Expected value of only 1 character in additionnal IF block.")); }
		switch(str__index(textContent, 0ULL)) {
			case 'i': lst__append(instance->elifBlocks, currentBlock); break;
			case 'e': instance->elseBlock = currentBlock;              break;
			default:  Parsing__ctx__errorLF(ctx, ctxt__toStr("Expected value \"i\" or \"e\" in additionnal IF block."));
		}
		str__free(textContent);
	}

	//free body structure (that should only refer to freed elements now)
	lst__free(body, false);

	//return as generic atm
	return Xif__toAtm(instance);
}



//specific parsing: For
atm* NC__newExe__For(Parsing__ctx* ctx, boo global) {
	NC__errorIfGlobalScope(ctx, global);

	//read value list given with NC instruction
	lst* body = Lst__new();
	Value__readWholeInstructionBody(ctx, body, false);

	//create instance
	Xfor* instance                = malloc(sizeof(Xfor));
	instance->iterVar             = malloc(sizeof(dataItem));
	(instance->iterVar)->constant = false;
	(instance->iterVar)->global   = false;

	//mandatory elements
	ulng bodyLength = lst__length(body);
	if(bodyLength != 6ULL) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Missing value in FOR statement (6 required).")); }

	//1:iterVar type
	atm* a                    = lst_atm__getRespectingID(ctx, body, 0ULL, ATOM__str, true);
	(instance->iterVar)->type = (str*)(a->data);
	free(a);

	//2:iterVar name
	a                         = lst_atm__getRespectingID(ctx, body, 1ULL, ATOM__str, true);
	(instance->iterVar)->name = (str*)(a->data);
	free(a);

	//3:iterVar value
	(instance->iterVar)->value = lst_atm__getRespectingID(ctx, body, 2ULL, ATOM__lst_atm, false);

	//4:condition
	instance->condition = lst_atm__getRespectingID(ctx, body, 3ULL, ATOM__lst_atm, false);

	//5:operation
	instance->operation = lst_atm__getRespectingID(ctx, body, 4ULL, ATOM__lst_atm, false);

	//6:block <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< DONT CHECK INSIDE BLOCKS FOR THE MOMENT
	a               = lst_atm__getRespectingID(ctx, body, 5ULL, ATOM__lst_atm, true);
	instance->block = (lst*)(a->data);
	free(a);

	//free body structure (that should only refer to freed elements now)
	lst__free(body, false);

	//return as generic atm
	return Xfor__toAtm(instance);
}



//specific parsing: While
atm* NC__newExe__While(Parsing__ctx* ctx, boo global) {
	NC__errorIfGlobalScope(ctx, global);

	//read value list given with NC instruction
	lst* body = Lst__new();
	Value__readWholeInstructionBody(ctx, body, false);

	//create instance
	Xwhile* instance = malloc(sizeof(Xwhile));

	//mandatory elements
	ulng bodyLength = lst__length(body);
	if(bodyLength != 2ULL) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Missing value in WHILE statement (2 required).")); }

	//1:condition
	instance->condition = lst_atm__getRespectingID(ctx, body, 0ULL, ATOM__lst_atm, false);

	//2:block <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< DONT CHECK INSIDE BLOCKS FOR THE MOMENT
	atm* a          = lst_atm__getRespectingID(ctx, body, 1ULL, ATOM__lst_atm, true);
	instance->block = (lst*)(a->data);
	free(a);

	//free body structure (that should only refer to freed elements now)
	lst__free(body, false);

	//return as generic atm
	return Xwhile__toAtm(instance);
}



//specific parsing: Switch
atm* NC__newExe__Switch(Parsing__ctx* ctx, boo global) {
	NC__errorIfGlobalScope(ctx, global);

	//read value list given with NC instruction
	lst* body = Lst__new();
	Value__readWholeInstructionBody(ctx, body, false);

	//create instance
	Xswitch* instance = malloc(sizeof(Xswitch));
	instance->entries = Lst__new();

	//mandatory elements
	ulng bodyLength = lst__length(body);
	if(bodyLength < 2ULL) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Missing value in SWITCH statement (at least 2 required).")); }

	//1:condition
	instance->condition = lst_atm__getRespectingID(ctx, body, 0ULL, ATOM__lst_atm, false);

	//additionnal block(s)
	ulng bodyIndex = 1ULL;
	lst* currentBlock; //lst[atm]
	while(bodyIndex < bodyLength) {
		switchEntry* s = malloc(sizeof(switchEntry));

		//key
		s->key = lst_atm__getRespectingID(ctx, body, bodyIndex, ATOM__lst_atm, false);
		bodyIndex++;

		//associated subcontent
		if(bodyIndex >= bodyLength) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Missing associated subcontent in SWITCH case.")); }
		s->block = lst_atm__getRespectingID(ctx, body, bodyIndex, ATOM__lst_atm, true); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< DONT CHECK INSIDE BLOCKS FOR THE MOMENT
		bodyIndex++;

		//store entry
		lst__append(instance->entries, s);
	}

	//free body structure (that should only refer to freed elements now)
	lst__free(body, false);

	//return as generic atm
	return Xswitch__toAtm(instance);
}



//specific parsing: Break
atm* NC__newExe__Break(Parsing__ctx* ctx, boo global) {
	NC__errorIfGlobalScope(ctx, global);

	//read value list given with NC instruction
	lst* body = Lst__new();
	Value__readWholeInstructionBody(ctx, body, false);

	//must have no value
	if(lst__length(body) != 0ULL) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Found value(s) in BREAK statement (nothing expected).")); }
	lst__free(body, false);

	//return as generic atm
	return Xjump__toAtm(JUMP__BRK);
}



//specific parsing: Continue
atm* NC__newExe__Continue(Parsing__ctx* ctx, boo global) {
	NC__errorIfGlobalScope(ctx, global);

	//read value list given with NC instruction
	lst* body = Lst__new();
	Value__readWholeInstructionBody(ctx, body, false);

	//must have no value
	if(lst__length(body) != 0ULL) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Found value(s) in CONTINUE statement (nothing expected).")); }
	lst__free(body, false);

	//return as generic atm
	return Xjump__toAtm(JUMP__CTN);
}



//specific parsing: Return
atm* NC__newExe__Return(Parsing__ctx* ctx, boo global) {
	NC__errorIfGlobalScope(ctx, global);

	//read value list given with NC instruction
	lst* body = Lst__new();
	Value__readWholeInstructionBody(ctx, body, false);

	//must have no value
	if(lst__length(body) != 0ULL) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Found value(s) in RETURN statement (nothing expected).")); }
	lst__free(body, false);

	//return as generic atm
	return Xjump__toAtm(JUMP__RET);
}



//specific parsing: Void-returning Function Call
atm* NC__newExe__VFC(Parsing__ctx* ctx, boo global) {
	NC__errorIfGlobalScope(ctx, global);

	//read value list given with NC instruction
	lst* body = Lst__new();
	Value__readWholeInstructionBody(ctx, body, false);

	//must have no value
	if(lst__length(body) != 1ULL) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Missing value in VFC statement (1 expected).")); }

	//get call value
	atm* a = lst_atm__getRespectingID(ctx, body, 0ULL, ATOM__call, true);

	//free body structure (that should only refer to freed elements now)
	lst__free(body, false);

	//return as generic atm
	return a;
}






// ---------------- MAIN EXECUTION ----------------

//redirection from any NC unit to its specific parsing function
atm* NC__parseOne(Parsing__ctx* ctx, boo global) {

	//read next useful character
	chr c;
	while(true) {
		if(Parsing__ctx__inc(ctx)) { return NULL; } //no more unit to read
		c = Parsing__ctx__get(ctx);             //NULL means end-of-program OR end-of-subcontent if global=false

		//skip beginning indent or line feed
		if(c != '\t' && c != '\n') { break; }
	}

	//1st rank : ROLE
	byt scope;
	switch(c) {



		//DEF
		case 'd':
			#ifdef DEBUG_AVAILABLE
			Parsing__ctx__debug(ctx, "DEF {");
			#endif

			//2nd rank : DEF SCOPE
			if(Parsing__ctx__inc(ctx)) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Missing DEF SCOPE.")); }
			c = Parsing__ctx__get(ctx);
			scope = NC__SCOPE_INVALID;
			switch(c) {
				case 'i':
					if(scope == NC__SCOPE_INVALID) { scope = NC__SCOPE_INTERN; }
				case 'x':
					if(scope == NC__SCOPE_INVALID) { scope = NC__SCOPE_EXTERN; }
				case 's':
					if(scope == NC__SCOPE_INVALID) { scope = NC__SCOPE_SHARED; }
				case 'l':
					if(scope == NC__SCOPE_INVALID) { scope = NC__SCOPE_LOCAL;  }

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
