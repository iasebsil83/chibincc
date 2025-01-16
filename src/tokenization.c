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
void Tokenization__errorIfGlobalScope(boo global) {
	if(global) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Token only allowed in local scope.")); }
}
void Tokenization__errorIfLocalScope(boo global) {
	if(!global) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Token only allowed in global scope.")); }
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
void Tokenization__errorInAdditionnalIFBlock() {
	Parsing__ctx__errorLF(ctx, ctxt__toStr("Expected NAME value \"i\" or \"e\" in additionnal IF block."));
}



//specific token reading : Type copy
token* Tokenization__newDefinitionToken_TypeCopy(Parsing__ctx* ctx, ubyt scope) {
	Tokenization__errorIfLocalGlobalScope(global);

	//read value list given with NC instruction
	lst* body = Value__readWholeInstructionBody(ctx, false);

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
token* Tokenization__newDefinitionToken_Structure(Parsing__ctx* ctx, ubyt scope) {
	token* tok = Token__new(ctx, NC__ROLE_DEFINITION | scope | NC__DEF_SCOPE_KIND_STRUCTURE);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}



//specific token reading : Function
token* Tokenization__newDefinitionToken_Function(Parsing__ctx* ctx, ubyt scope) {
	token* tok = Token__new(ctx, NC__ROLE_DEFINITION | scope | NC__DEF_SCOPE_KIND_FUNCTION);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}



//specific token reading : Data item
token* Tokenization__newDefinitionToken_DataItem(Parsing__ctx* ctx, ubyt scope) {
	token* tok = Token__new(ctx, NC__ROLE_DEFINITION | scope | NC__DEF_SCOPE_KIND_DATA);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}



//specific token reading : If
token* Tokenization__newExecutionToken_If(Parsing__ctx* ctx, boo global) {
	Tokenization__errorIfGlobalScope(global);

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
		if(textContent->length != 1ULL) { Tokenization__errorInAdditionnalIFBlock(); }
		switch(str__index(textContent, 0ULL)) {
			case 'i': lst__append(instance->elifBlocks, currentBlock); break;
			case 'e': instance->elseBlock = currentBlock;              break;
			default:  Tokenization__errorInAdditionnalIFBlock();
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
token* Tokenization__newExecutionToken_For(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_FOR);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}



//specific token reading : While
token* Tokenization__newExecutionToken_While(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_WHILE);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}



//specific token reading : Switch
token* Tokenization__newExecutionToken_Switch(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_SWITCH);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}



//specific token reading : Break
token* Tokenization__newExecutionToken_Break(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_BREAK);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}



//specific token reading : Continue
token* Tokenization__newExecutionToken_Continue(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_CONTINUE);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}



//specific token reading : Return
token* Tokenization__newExecutionToken_Return(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_RETURN);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}



//specific token reading : Void-returning Function Call
token* Tokenization__newExecutionToken_VFC(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_VFC);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}






// ---------------- MAIN EXECUTION ----------------

//parsing context to token list (main tokenization entry point)
lst* Tokenization__tokenize(Parsing__ctx* ctx, boo inSubcontent) {
	lst* tokens = Lst__new();

	//debug
	#ifdef DEBUG_AVAILABLE
	if(inSubcontent) { Parsing__ctx__debug(ctx, "BEGINNING SUBTOKENIZATION");     }
	else             { Parsing__ctx__debug(ctx, "BEGINNING GLOBAL TOKENIZATION"); }
	#endif

	//for subcontents only
	boo reachedEndOfSubcontent = false;

	//as long as we got things to read
	boo remaining = true;
	while(remaining) {
		if(Parsing__ctx__inc(ctx)) { break; }
		chr c = Parsing__ctx__get(ctx);

		//skip beginning indent or line feed
		if(c == '\t' || c == '\n') { continue; }

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
							case 'c': lst__append(tokens, (byt*)Tokenization__newDefinitionToken_TypeCopy( ctx, scope)); break;
							case 's': lst__append(tokens, (byt*)Tokenization__newDefinitionToken_Structure(ctx, scope)); break;
							case 'f': lst__append(tokens, (byt*)Tokenization__newDefinitionToken_Function( ctx, scope)); break;
							case 'd': lst__append(tokens, (byt*)Tokenization__newDefinitionToken_DataItem( ctx, scope)); break;
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
					case 'i': lst__append(tokens, (byt*)Tokenization__newExecutionToken_If(      ctx)); break;
					case 'f': lst__append(tokens, (byt*)Tokenization__newExecutionToken_For(     ctx)); break;
					case 'w': lst__append(tokens, (byt*)Tokenization__newExecutionToken_While(   ctx)); break;
					case 's': lst__append(tokens, (byt*)Tokenization__newExecutionToken_Switch(  ctx)); break;
					case 'b': lst__append(tokens, (byt*)Tokenization__newExecutionToken_Break(   ctx)); break;
					case 'c': lst__append(tokens, (byt*)Tokenization__newExecutionToken_Continue(ctx)); break;
					case 'r': lst__append(tokens, (byt*)Tokenization__newExecutionToken_Return(  ctx)); break;
					case 'v': lst__append(tokens, (byt*)Tokenization__newExecutionToken_VFC(     ctx)); break;
					//case '': lst__append(tokens, (byt*)Tokenization__newExecutionToken_(ctx)); break;
					//case '': lst__append(tokens, (byt*)Tokenization__newExecutionToken_(ctx)); break;
					//case '': lst__append(tokens, (byt*)Tokenization__newExecutionToken_(ctx)); break;
					//case '': lst__append(tokens, (byt*)Tokenization__newExecutionToken_(ctx)); break;
					//case '': lst__append(tokens, (byt*)Tokenization__newExecutionToken_(ctx)); break;
					//case '': lst__append(tokens, (byt*)Tokenization__newExecutionToken_(ctx)); break;
					//case '': lst__append(tokens, (byt*)Tokenization__newExecutionToken_(ctx)); break;
					//case '': lst__append(tokens, (byt*)Tokenization__newExecutionToken_(ctx)); break;
					default: Parsing__ctx__errorLF(ctx, ctxt__toStr("Invalid EXE STATEMENT given."));
				}
				#ifdef DEBUG_AVAILABLE
				Parsing__ctx__debug(ctx, "} EXE");
				#endif
			break;



			//end of subcontent
			case '}':
				if(!inSubcontent) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Can't have end-of-subcontent out of subcontent.")); }
				reachedEndOfSubcontent = true;
				remaining = false;
			break;

			//undefined
			default: Parsing__ctx__errorLF(ctx, ctxt__toStr("Invalid ROLE given."));
		}
	}
	if(inSubcontent && !reachedEndOfSubcontent) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Incomplete subcontent at end of file.")); }

	//debug
	#ifdef DEBUG_AVAILABLE
	if(inSubcontent) { Parsing__ctx__debug(ctx, "ENDING SUBTOKENIZATION");     }
	else             { Parsing__ctx__debug(ctx, "ENDING GLOBAL TOKENIZATION"); }
	#endif

	//final result
	return tokens;
}

//program structure integrity check (recursive tool) : includes storage of GLOBAL TOKENS ONLY!!! into the given program structure
//mod Program { voi token.checkIntegrity(program p, boo global) {...} }
// => t.^Program.checkIntegrity(p, true)
void Program__token__checkTokenIntegrity(token* t, program* p, boo global) {
	valueArg* v1;

				case NC__EXE_STATEMENT_FOR:
					Program__errorIfGlobalScope(global);
					if()
				break;

				case NC__EXE_STATEMENT_WHILE:
					Program__errorIfGlobalScope(global);
					if()
				break;

				case NC__EXE_STATEMENT_SWITCH:
					Program__errorIfGlobalScope(global);
					if()
				break;

				case NC__EXE_STATEMENT_BREAK:
					Program__errorIfGlobalScope(global);
					if()
				break;

				case NC__EXE_STATEMENT_CONTINUE:
					Program__errorIfGlobalScope(global);
					if()
				break;

				case NC__EXE_STATEMENT_RETURN:
					Program__errorIfGlobalScope(global);
					if()
				break;

				//allowed in both scopes
				case NC__EXE_STATEMENT_VFC:
					if()
					if(global) {
						if(t->body)
						lst__append(p->globalAsg, (byt*)t);
					}
				break;

				//undefined token (should never occur)
				default: Parsing__ctx__internalLF(ctx, ctxt__toStr("Undefined execution token parsed."));
			}
		break;
		case NC__ROLE_DEFINITION:
			switch(t->id & NC__DEF_SCOPE_MASK) {
				case NC__DEF_SCOPE_INTERN: resultText = str__addChrSelf(resultText, 'i'); break;
				case NC__DEF_SCOPE_EXTERN: resultText = str__addChrSelf(resultText, 'e'); break;
				case NC__DEF_SCOPE_SHARED: resultText = str__addChrSelf(resultText, 's'); break;
				case NC__DEF_SCOPE_LOCAL:  resultText = str__addChrSelf(resultText, 'l'); break;
				default:
					Parsing__ctx__errorLF(ctx, ctxt__toStr("Incomplete subcontent at end of file."));
			}
			switch(t->id & NC__DEF_SCOPE_KIND_MASK) {
				case NC__DEF_SCOPE_KIND_COPY:      resultText = str__addChrSelf(resultText, 'c'); break;
				case NC__DEF_SCOPE_KIND_STRUCTURE: resultText = str__addChrSelf(resultText, 's'); break;
				case NC__DEF_SCOPE_KIND_FUNCTION:  resultText = str__addChrSelf(resultText, 'f'); break;
				case NC__DEF_SCOPE_KIND_DATA:      resultText = str__addChrSelf(resultText, 'd'); break;
				default:
					Parsing__ctx__errorLF(ctx, ctxt__toStr("Incomplete subcontent at end of file."));
			}
		break;
		default:
			Parsing__ctx__errorLF(ctx, ctxt__toStr("Incomplete subcontent at end of file."));
	}
}






// ---------------- CONVERSION ----------------

//convert a list of tokens into a CORRECT program element
//mod Program { program lst[token].toProgram() {...} }
// => l.^Program.toProgram()
program* Program__lst_token__toProgram(lst* tokens) {

	//create main program structure
	program* p = malloc(sizeof(program));
	p->types     = Lst__new();
	p->globalDat = Lst__new();
	p->globalAsg = Lst__new();
	p->functions = Lst__new();

	//read EVERY token recursively
	for(ulng i=0ULL; i < lst__length((lst*)tokens); i++) {
		token* t = (token*)lst__index((lst*)tokens, i);
		Program__token__checkTokenIntegrity(t, p, true); //also store GLOBAL TOKENS ONLY!!! into program
	}
	return p;
}



//parsing entry point
program* Program__fromCtx(Parsing__ctx* ctx, str* outputPath) { //outputPath for debug only

	//linear tokenization, reading NC content line by line (doesn't mean we don't have recursion !)
	lst* tokens = Tokenization__tokenize(ctx, false);

	//debug
	#ifdef DEBUG_AVAILABLE
	if(Log__level <= Log__LEVEL__DEBUG) {
		str* ending = ctxt__toStr(".tok"); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< to remove using constant
		str* debugOutputPath = str__add(outputPath, ending);
		str* debugOutput     = lst_token__toStr(tokens, 0ULL);
		IO__writeFile(debugOutputPath, debugOutput);
		str__free(ending); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< as well
		str__free(debugOutputPath);
		str__free(debugOutput);
	}
	#endif

	//then convert into program instance
	program* p = Program__lst_token__toProgram(tokens);
	lst__free(tokens, false); //free token list on the surface only, internal elements are saved inside program structure
	return p;
}
