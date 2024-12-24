 // ---------------- IMPORTATIONS ----------------

//bases
#include "context.c"






// ---------------- SPECIFIC ----------------

//cyclic calls
lst* Tokenization__tokenize(         Parsing__ctx* ctx, boo inSubContent);
lst* Value__readWholeInstructionBody(Parsing__ctx* ctx, boo inCall      );

//numbers
void Value__parseByte_error(Parsing__ctx* ctx){ Tokenization__error(ctx, ctxt__toStr("Not enough character to parse ubyt (2 hex required after '1' delimiter).")); }
valueArg* Value__parseByte(Parsing__ctx* ctx) {
	str* expectedStr = Str__new(2ULL);

	//debug
	#ifdef DEBUG_AVAILABLE
	Parsing__ctx__debug(ctx, "VALUE PARSING BYTE");
	#endif

	//read expected sequence
	if(Parsing__ctx__inc(ctx)) { Value__parseByte_error(ctx); }
	str__indexAssign(expectedStr, 0ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseByte_error(ctx); }
	str__indexAssign(expectedStr, 1ULL, Parsing__ctx__get(ctx));

	//parse literal
	ubyt literal = str__toUByt(expectedStr);
	str__free(expectedStr);

	//return as a generic valueArg element
	valueArg* result = malloc(sizeof(valueArg));
	result->id       = VALUE_ARG__LITERAL1;
	result->content  = (ubyt)literal;

	//debug
	#ifdef DEBUG_AVAILABLE
	Parsing__ctx__debug_WITHOUT_LF(ctx, "VALUE PARSED BYTE");
	if(Log__LEVEL__DEBUG >= Log__level) { printf("[%02x]\n", (ubyt)(result->content)); } //TEMPORARY FOR printf USE
	#endif

	//return result
	return result;
}



//short
void Value__parseShort_error(Parsing__ctx* ctx){ Tokenization__error(ctx, ctxt__toStr("Not enough character to parse ushr (4 hex required after '2' delimiter).")); }
valueArg* Value__parseShort(Parsing__ctx* ctx) {
	str* expectedStr = Str__new(4ULL);

	//debug
	#ifdef DEBUG_AVAILABLE
	Parsing__ctx__debug(ctx, "VALUE PARSING SHORT");
	#endif

	//read expected sequence
	if(Parsing__ctx__inc(ctx)) { Value__parseShort_error(ctx); }
	str__indexAssign(expectedStr, 0ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseShort_error(ctx); }
	str__indexAssign(expectedStr, 1ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseShort_error(ctx); }
	str__indexAssign(expectedStr, 2ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseShort_error(ctx); }
	str__indexAssign(expectedStr, 3ULL, Parsing__ctx__get(ctx));

	//parse literal
	ushr literal = str__toUShr(expectedStr);
	str__free(expectedStr);

	//return as a generic valueArg element
	valueArg* result = malloc(sizeof(valueArg));
	result->id       = VALUE_ARG__LITERAL2;
	result->content  = (ushr)literal;

	//debug
	#ifdef DEBUG_AVAILABLE
	Parsing__ctx__debug_WITHOUT_LF(ctx, "VALUE PARSED SHORT");
	if(Log__LEVEL__DEBUG >= Log__level) { printf("[%04x]\n", (ushr)(result->content)); } //TEMPORARY FOR printf USE
	#endif

	//return result
	return result;
}



//integer
void Value__parseInteger_error(Parsing__ctx* ctx){ Tokenization__error(ctx, ctxt__toStr("Not enough character to parse uint (8 hex required after '4' delimiter).")); }
valueArg* Value__parseInteger(Parsing__ctx* ctx) {
	str* expectedStr = Str__new(8ULL);

	#ifdef DEBUG_AVAILABLE
	Parsing__ctx__debug(ctx, "VALUE PARSING INTEGER");
	#endif

	//read expected sequence
	if(Parsing__ctx__inc(ctx)) { Value__parseInteger_error(ctx); }
	str__indexAssign(expectedStr,  0ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseInteger_error(ctx); }
	str__indexAssign(expectedStr,  1ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseInteger_error(ctx); }
	str__indexAssign(expectedStr,  2ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseInteger_error(ctx); }
	str__indexAssign(expectedStr,  3ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseInteger_error(ctx); }
	str__indexAssign(expectedStr,  4ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseInteger_error(ctx); }
	str__indexAssign(expectedStr,  5ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseInteger_error(ctx); }
	str__indexAssign(expectedStr,  6ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseInteger_error(ctx); }
	str__indexAssign(expectedStr,  7ULL, Parsing__ctx__get(ctx));

	//parse literal
	uint literal = str__toUInt(expectedStr);
	str__free(expectedStr);

	//return as a generic valueArg element
	valueArg* result = malloc(sizeof(valueArg));
	result->id       = VALUE_ARG__LITERAL4;
	result->content  = (uint)literal;

	//debug
	#ifdef DEBUG_AVAILABLE
	Parsing__ctx__debug_WITHOUT_LF(ctx, "VALUE PARSED INTEGER");
	if(Log__LEVEL__DEBUG >= Log__level) { printf("[%08x]\n", (uint)(result->content)); } //TEMPORARY FOR printf USE
	#endif

	//return result
	return result;
}



//long
void Value__parseLong_error(Parsing__ctx* ctx){ Tokenization__error(ctx, ctxt__toStr("Not enough character to parse ulng (16 hex required after '8' delimiter).")); }
valueArg* Value__parseLong(Parsing__ctx* ctx) {
	str* expectedStr = Str__new(16ULL);

	//debug
	#ifdef DEBUG_AVAILABLE
	Parsing__ctx__debug(ctx, "VALUE PARSING LONG");
	#endif

	//read expected sequence
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(ctx); }
	str__indexAssign(expectedStr,  0ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(ctx); }
	str__indexAssign(expectedStr,  1ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(ctx); }
	str__indexAssign(expectedStr,  2ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(ctx); }
	str__indexAssign(expectedStr,  3ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(ctx); }
	str__indexAssign(expectedStr,  4ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(ctx); }
	str__indexAssign(expectedStr,  5ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(ctx); }
	str__indexAssign(expectedStr,  6ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(ctx); }
	str__indexAssign(expectedStr,  7ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(ctx); }
	str__indexAssign(expectedStr,  8ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(ctx); }
	str__indexAssign(expectedStr,  9ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(ctx); }
	str__indexAssign(expectedStr, 10ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(ctx); }
	str__indexAssign(expectedStr, 11ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(ctx); }
	str__indexAssign(expectedStr, 12ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(ctx); }
	str__indexAssign(expectedStr, 13ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(ctx); }
	str__indexAssign(expectedStr, 14ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(ctx); }
	str__indexAssign(expectedStr, 15ULL, Parsing__ctx__get(ctx));

	//parse literal
	ulng literal = str__toULng(expectedStr);
	str__free(expectedStr);

	//return as a generic valueArg element
	valueArg* result = malloc(sizeof(valueArg));
	result->id       = VALUE_ARG__LITERAL8;
	result->content  = (ulng)literal;

	//debug
	#ifdef DEBUG_AVAILABLE
	Parsing__ctx__debug_WITHOUT_LF(ctx, "VALUE PARSED LONG");
	if(Log__LEVEL__DEBUG >= Log__level) { printf("[%016llx]\n", (ulng)(result->content)); } //TEMPORARY FOR printf USE
	#endif

	//return result
	return result;
}



//subcontent
valueArg* Value__parseSubcontent(Parsing__ctx* ctx) {
	valueArg* result = malloc(sizeof(valueArg));
	result->id       = VALUE_ARG__SUBCONTENT;
	result->content  = (ulng)Tokenization__tokenize(ctx, true);
	return result;
}



//call
valueArg* Value__parseCall(Parsing__ctx* ctx) {
	valueArg* result = malloc(sizeof(valueArg));
	result->id       = VALUE_ARG__CALL;
	result->content  = (ulng)Value__readWholeInstructionBody(ctx, true);
	return result;
}



//name (return true if reached end of instruction)
boo Value__parseName(chr c, lst* body, Parsing__ctx* ctx, boo inCall) {
	boo inName           = true;
	boo maxLengthReached = false;
	boo endOfInstruction = false;

	//debug
	#ifdef DEBUG_AVAILABLE
	Parsing__ctx__debug(ctx, "VALUE PARSING NAME(s)");
	#endif

	//prepare NAME storage
	istr* name = IStr__new(NC__NAME_LENGTH_MAX);
	istr__push(name, c);

	//prepare the value container
	valueArg* v = malloc(sizeof(valueArg));
	v->id       = VALUE_ARG__NAME;

	//read name
	while(inName){
		if(Parsing__ctx__inc(ctx)) { break; }
		c = Parsing__ctx__get(ctx);

		//look for end delimiter
		switch(c) {



			//end of instruction => set EOI flag and then continue as it was end-of-name
			case '\n': if(!inCall) { endOfInstruction = true; }

			//end of name
			case ':':

				//store name
				v->content = (ulng)str__sub(name->s, 0ULL, name->index);
				lst__append(body, (byt*)v);

				//debug
				#ifdef DEBUG_AVAILABLE
				Parsing__ctx__debug_WITHOUT_LF(ctx, "NAME IS \"");
				//paliative for the moment. previous debug call should contain this <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				Log__debug((str*)(v->content), false);
				Log__ctxt__debugLF("\"", false);
				#endif

				//continue the right way (return)
				inName = false; //<=> return
			break;



			//start a new subcontent
			case '{':
				if(inCall) { Tokenization__error(ctx, ctxt__toStr("Subcontents are not allowed in call parameters.")); }

				//store name
				v->content = (ulng)str__sub(name->s, 0ULL, name->index);
				lst__append(body, (byt*)v);

				//debug
				#ifdef DEBUG_AVAILABLE
				Parsing__ctx__debug_WITHOUT_LF(ctx, "NAME IS \"");
				//paliative for the moment. previous debug call should contain this <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				Log__debug((str*)(v->content), false);
				Log__ctxt__debugLF("\"", false);
				#endif

				//continue parsing on the right way (parseSubcontent, return)
				lst__append(body, (byt*)Value__parseSubcontent(ctx));
				inName = false; //<=> return
			break;



			//start a new call
			case '(':

				//store name
				v->content = (ulng)str__sub(name->s, 0ULL, name->index);
				lst__append(body, (byt*)v);

				//debug
				#ifdef DEBUG_AVAILABLE
				Parsing__ctx__debug_WITHOUT_LF(ctx, "NAME IS \"");
				//paliative for the moment. previous debug call should contain this <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				Log__debug((str*)(v->content), false);
				Log__ctxt__debugLF("\"", false);
				#endif

				//continue parsing on the right way (parseCall, return)
				lst__append(body, (byt*)Value__parseCall(ctx));
				inName = false; //<=> return
			break;



			//end of call
			case ')':
				if(!inCall) { Tokenization__error(ctx, ctxt__toStr("Can't have end-of-call outside a call.")); }
				endOfInstruction = true;
			break;



			//no delimiter => regular part of the name
			default:
				if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' || c == '.' || c == '*') { //NAMEs charset
					if(maxLengthReached) { Tokenization__error(ctx, ctxt__toStr("Too much characters in NAME.")); }
					if(istr__push(name, c)) { maxLengthReached = true; }
				}
				else { Tokenization__error(ctx, ctxt__toStr("Unauthorized middle character in NAME.")); }
		}
	}

	//debug
	#ifdef DEBUG_AVAILABLE
	Parsing__ctx__debug(ctx, "VALUE PARSED NAME(s)");
	#endif

	//free temporay structure
	name->s->length = name->index + 1LL;
	istr__free(name, true);

	//share the information whether other values are to be parsed or not for the current instruction
	return endOfInstruction;
}






// ---------------- MAIN ENTRY POINT ----------------

//read body including nested instructions themselves (value parsing)
lst* Value__readWholeInstructionBody(Parsing__ctx* ctx, boo inCall) {
	lst* body = Lst__new();

	//debug
	#ifdef DEBUG_AVAILABLE
	if(inCall) { Parsing__ctx__debug(ctx, "PARSING VALUE CHAIN INSIDE CALL"); }
	else       { Parsing__ctx__debug(ctx, "PARSING VALUE CHAIN");             }
	#endif

	//reading value chain
	boo remaining = true;
	while(remaining) {
		if(Parsing__ctx__inc(ctx)) { break; }
		chr c = Parsing__ctx__get(ctx);

		//indent => skip it
		if(c == '\t') { continue; }

		//value detection from 1st character
		switch(c) {

			//end of instruction => end of value parsing (or nothing if reading call parameters)
			case '\n': if(!inCall) { remaining = false; } break;

			//ubyte detected
			case '1': lst__append(body, (byt*)Value__parseByte(ctx)); break;

			//ushort detected
			case '2': lst__append(body, (byt*)Value__parseShort(ctx)); break;

			//uinteger detected
			case '4': lst__append(body, (byt*)Value__parseInteger(ctx)); break;

			//ulong detected
			case '8': lst__append(body, (byt*)Value__parseLong(ctx)); break;

			//end of call
			case ')':
				if(!inCall) { Tokenization__error(ctx, ctxt__toStr("Can't have end-of-call outside a call.")); }
				remaining = false;
			break;

			//subcontent
			case '{':
				if(inCall) { Tokenization__error(ctx, ctxt__toStr("Subcontents are not allowed in call parameters.")); }
				lst__append(body, (byt*)Value__parseSubcontent(ctx));
			break;

			//other (calls are not allowed here, they must be preceeded by a NAME => only in Value__parseName)
			default:

				//name detected (1 name detected can lead to several valueArg)
				if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
					if(Value__parseName(c, body, ctx, inCall)){ remaining = false; }
				}

				//unauthorized beginning character
				else { Tokenization__error(ctx, ctxt__toStr("Unauthorized beginning character in instruction value.")); }
		}
	}

	//debug
	#ifdef DEBUG_AVAILABLE
	if(inCall) { Parsing__ctx__debug(ctx, "PARSED VALUE CHAIN INSIDE_CALL"); }
	else       { Parsing__ctx__debug(ctx, "PARSED VALUE CHAIN");             }
	#endif

	//return value args (which is token's value)
	return body;
}
