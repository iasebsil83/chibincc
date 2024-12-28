// ---------------- IMPORTATIONS ----------------

//value parsing
#include "value.c"






// ---------------- SPECIFIC ----------------

//specific token reading
token* Tokenization__newDefinitionToken_TypeCopy(Parsing__ctx* ctx, ubyt scope) {
	token* tok = Token__new(ctx, NC__ROLE_DEFINITION | scope | NC__DEF_SCOPE_KIND_COPY);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}

token* Tokenization__newDefinitionToken_Structure(Parsing__ctx* ctx, ubyt scope) {
	token* tok = Token__new(ctx, NC__ROLE_DEFINITION | scope | NC__DEF_SCOPE_KIND_STRUCTURE);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}

token* Tokenization__newDefinitionToken_Function(Parsing__ctx* ctx, ubyt scope) {
	token* tok = Token__new(ctx, NC__ROLE_DEFINITION | scope | NC__DEF_SCOPE_KIND_FUNCTION);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}

token* Tokenization__newDefinitionToken_DataItem(Parsing__ctx* ctx, ubyt scope) {
	token* tok = Token__new(ctx, NC__ROLE_DEFINITION | scope | NC__DEF_SCOPE_KIND_DATA);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}

token* Tokenization__newExecutionToken_If(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_IF);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}

token* Tokenization__newExecutionToken_For(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_FOR);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}

token* Tokenization__newExecutionToken_While(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_WHILE);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}

token* Tokenization__newExecutionToken_Switch(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_SWITCH);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}

token* Tokenization__newExecutionToken_Break(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_BREAK);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}

token* Tokenization__newExecutionToken_Continue(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_CONTINUE);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}

token* Tokenization__newExecutionToken_Return(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_RETURN);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}

token* Tokenization__newExecutionToken_VFC(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_VFC);
	tok->body  = Value__readWholeInstructionBody(ctx, false);
	return tok;
}






// ---------------- MAIN ENTRY POINT ----------------

//text to token list
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
				if(Parsing__ctx__inc(ctx)) { Tokenization__error(ctx, ctxt__toStr("Missing DEF SCOPE.")); }
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
						if(Parsing__ctx__inc(ctx)) { Tokenization__error(ctx, ctxt__toStr("Missing DEF SCOPE KIND.")); }
						switch(Parsing__ctx__get(ctx)){
							case 'c': lst__append(tokens, (byt*)Tokenization__newDefinitionToken_TypeCopy( ctx, scope)); break;
							case 's': lst__append(tokens, (byt*)Tokenization__newDefinitionToken_Structure(ctx, scope)); break;
							case 'f': lst__append(tokens, (byt*)Tokenization__newDefinitionToken_Function( ctx, scope)); break;
							case 'd': lst__append(tokens, (byt*)Tokenization__newDefinitionToken_DataItem( ctx, scope)); break;
							default: Tokenization__error(ctx, ctxt__toStr("Missing DEF SCOPE KIND."));
						}
					break;
					default: Tokenization__error(ctx, ctxt__toStr("Invalid DEF SCOPE given."));
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
				if(Parsing__ctx__inc(ctx)) { Tokenization__error(ctx, ctxt__toStr("Invalid DEF SCOPE given.")); }
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
					default: Tokenization__error(ctx, ctxt__toStr("Invalid EXE STATEMENT given."));
				}
				#ifdef DEBUG_AVAILABLE
				Parsing__ctx__debug(ctx, "} EXE");
				#endif
			break;



			//end of subcontent
			case '}':
				if(!inSubcontent) { Tokenization__error(ctx, ctxt__toStr("Can't have end-of-subcontent out of subcontent.")); }
				reachedEndOfSubcontent = true;
				remaining = false;
			break;

			//undefined
			default: Tokenization__error(ctx, ctxt__toStr("Invalid ROLE given."));
		}
	}
	if(inSubcontent && !reachedEndOfSubcontent) { Tokenization__error(ctx, ctxt__toStr("Incomplete subcontent at end of file.")); }

	//debug
	#ifdef DEBUG_AVAILABLE
	if(inSubcontent) { Parsing__ctx__debug(ctx, "ENDING SUBTOKENIZATION");     }
	else             { Parsing__ctx__debug(ctx, "ENDING GLOBAL TOKENIZATION"); }
	#endif

	//final result
	return tokens;
}

//parsing entry point
lst* Tokenization__run(str* filename, str* inputText) {
	Parsing__ctx* ctx = Parsing__Ctx__new(filename, inputText);
	return Tokenization__tokenize(ctx, false);
}
