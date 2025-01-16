// ---------------- PROGRAM INTEGRITY ----------------

//error shortcuts
void Program__errorIfGlobalScope(boo global) {
	if(global) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Token only allowed in local scope.")); }
}
void Program__errorIfLocalScope(boo global) {
	if(!global) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Token only allowed in global scope.")); }
}
void Program__errorIfSubcontent(lst* body, ulng index) {
	valueArg* v = (valueArg*)lst__index(body, index);
	if(v->id == VARG__SUBCONTENT) {
		Parsing__ctx__errorLF(ctx, str__add(ulng__toStr(index+1ULL), ctxt__toStr("th value of token is a subcontent => not allowed here.")) );
	}
}
void Program__errorIfNotSubcontent(lst* body, ulng index) {
	valueArg* v = (valueArg*)lst__index(body, index);
	if(v->id != VARG__SUBCONTENT) {
		Parsing__ctx__errorLF(ctx, str__add(ulng__toStr(index+1ULL), ctxt__toStr("th value of token is not a subcontent => expected one here.")) );
	}
}
void Program__errorInAdditionnalIFBlock() {
	Parsing__ctx__errorLF(ctx, ctxt__toStr("Expected NAME value \"i\" or \"e\" in additionnal IF block."));
}

//program structure integrity check (recursive tool) : includes storage of GLOBAL TOKENS ONLY!!! into the given program structure
//mod Program { voi token.checkIntegrity(program p, boo global) {...} }
// => t.^Program.checkIntegrity(p, true)
void Program__token__checkTokenIntegrity(token* t, program* p, boo global) {
	valueArg* v1;
	ulng bodyLength = lst__length(t->body);
	ulng valueIndex;
	boo  elseReached = false; //IF statements
	str* textContent;
	switch(t->id & NC__ROLE_MASK) {
		case NC__ROLE_EXECUTION:
			switch(t->id & NC__EXE_STATEMENT_MASK) {



				//IF
				case NC__EXE_STATEMENT_IF:
					Program__errorIfGlobalScope(global);
					if(bodyLength < 2ULL) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Missing value in EXE IF statement (at least 2 required).")); }
					Program__errorIfSubcontent(   t->body, 0ULL); //condition
					Program__errorIfNotSubcontent(t->body, 1ULL); //and its associated sub

					//additionnal block(s)
					valueIndex = 2ULL;
					while(valueIndex < bodyLength) {
						if(elseReached) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Cannot have another IF additionnal block after ELSE.")); }
						v1          = (valueArg*)lst__index(t->body, valueIndex); //elif-else indicator
						textContent = (str*)(v1->content);
						if(v1->id != VARG__NAME)        { Program__errorInAdditionnalIFBlock(); }
						if(textContent->length != 1ULL) { Program__errorInAdditionnalIFBlock(); }
						switch(str__index(textContent, 0ULL)) {
							case 'i': break;
							case 'e': elseReached = true; break;
							default: Program__errorInAdditionnalIFBlock();
						}
						valueIndex++;
						if(valueIndex >= bodyLength) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Missing subcontent in IF additionnal block.")); }
						Program__errorIfNotSubcontent(t->body, valueIndex); //and its associated sub
						valueIndex++;
					}
				break;

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
		str* debugOutput     = debugTokens(tokens, 0ULL);
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
