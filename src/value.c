// ---------------- IMPORTATIONS ----------------

//bases
#include "context.c"






// ---------------- SPECIFIC ----------------

//numbers
void Value__parseByte_error(Parsing__ctx* ctx){ Tokenization__error(ctx, ctxt__toStr("Not enough character to parse ubyt (2 hex required after '1' delimiter).")); }
valueArg* Value__parseByte(Parsing__ctx* ctx) {
	printf("VALUE PARSING BYTE\n");
	str* expectedStr = Str__new(2ULL);

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
	printf("VALUE PARSED BYTE [%02x]\n", (ubyt)(result->content));
	return result;
}



//short
void Value__parseShort_error(Parsing__ctx* ctx){ Tokenization__error(ctx, ctxt__toStr("Not enough character to parse ushr (4 hex required after '2' delimiter).")); }
valueArg* Value__parseShort(Parsing__ctx* ctx) {
	printf("VALUE PARSING SHORT\n");
	str* expectedStr = Str__new(4ULL);

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
	printf("VALUE PARSED SHORT [%04x]\n", (ushr)(result->content));
	return result;
}



//integer
void Value__parseInteger_error(Parsing__ctx* ctx){ Tokenization__error(ctx, ctxt__toStr("Not enough character to parse uint (8 hex required after '4' delimiter).")); }
valueArg* Value__parseInteger(Parsing__ctx* ctx) {
	printf("VALUE PARSING INTEGER\n");
	str* expectedStr = Str__new(8ULL);

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
	printf("VALUE PARSED INTEGER [%08x]\n", (uint)(result->content));
	return result;
}



//long
void Value__parseLong_error(Parsing__ctx* ctx){ Tokenization__error(ctx, ctxt__toStr("Not enough character to parse ulng (16 hex required after '8' delimiter).")); }
valueArg* Value__parseLong(Parsing__ctx* ctx) {
	printf("VALUE PARSING LONG\n");
	str* expectedStr = Str__new(16ULL);

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
	printf("VALUE PARSED LONG [%016llx]\n", (ulng)(result->content));
	return result;
}



//subcontent
valueArg* Value__parseSubcontent(Parsing__ctx* ctx) {
	printf("VALUE PARSING SUBCONTENT\n");
	valueArg* result = malloc(sizeof(valueArg));
	result->id       = VALUE_ARG__SUBCONTENT;
	result->content  = (ulng)Tokenization__tokenize(ctx, true);
	printf("VALUE PARSED SUBCONTENT\n");
	return result;
}



//call
valueArg* Value__parseCall(Parsing__ctx* ctx) {
	printf("VALUE PARSING CALL\n");
	valueArg* result = malloc(sizeof(valueArg));
	result->id       = VALUE_ARG__CALL;
	result->content  = (ulng)Value__readWholeInstructionBody(ctx, true);
	printf("VALUE PARSED CALL\n");
	return result;
}



//name (return true if reached end of instruction)
boo Value__parseName(chr c, lst* body, Parsing__ctx* ctx, boo inCall) {
	printf("VALUE PARSING NAME\n");
	boo inName           = true;
	boo maxLengthReached = false;
	boo endOfInstruction = false;

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

			//end of instruction => set EOI flag, store NAME, return (or separator if inCall)
			case '\n': if(!inCall) { endOfInstruction = true; }

			//end of name => store NAME, return
			case ':':
				v->content = (ulng)str__sub(name->s, 0ULL, name->index);
				lst__append(body, (byt*)v);
				inName = false; //<=> return
			break;

			//store NAME, parse subcontent, return
			case '{':
				if(inCall) { Tokenization__error(ctx, ctxt__toStr("Subcontents are not allowed in call parameters.")); }
				v->content = (ulng)str__sub(name->s, 0ULL, name->index);
				lst__append(body, (byt*)v);
				lst__append(body, (byt*)Value__parseSubcontent(ctx));
				inName = false; //<=> return
			break;

			//store NAME, parse call, return
			case '(':
				v->content = (ulng)str__sub(name->s, 0ULL, name->index);
				lst__append(body, (byt*)v);
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

	//free temporay structure
	printf("VALUE PARSED NAME [");
	name->s->length = name->index + 1LL;
	IO__print(name->s);
	printf("]\n");
	istr__free(name, true);

	//share the information whether other values are to be parsed or not for the current instruction
	return endOfInstruction;
}






// ---------------- MAIN ENTRY POINT ----------------

//read body including nested instructions themselves (value parsing)
lst* Value__readWholeInstructionBody(Parsing__ctx* ctx, boo inCall) {
	printf("PARSING VALUE CHAIN\n");
	lst* body = Lst__new();

	/*IO__ctxt__printLF("BODY STEP1 [");
	str* TECHT = Parsing__ctx__toStr(ctx);
	IO__printLF(TECHT);
	str__free(TECHT);
	IO__ctxt__printLF("BODY STEP1 ]");*/

	//starting position
	//istr* icontent   = ctx->icontent;
	//ulng  startIndex = icontent->index;

	//end of line => end of instruction
	//IO__ctxt__printLF("BODY STEP2");
	boo remaining = true;
	while(remaining) {
		if(Parsing__ctx__inc(ctx)) { break; }
		chr c = Parsing__ctx__get(ctx);

		//indent => skip it
		if(c == '\t') { continue; }

		//value detection from 1st character
		printf("PARSING VALUE ITEM\n");
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
		printf("PARSED VALUE ITEM\n");
	}
	//IO__ctxt__printLF("BODY STEP3");

	//update value now that we have it
	//ulng bodyLength = icontent->index - startIndex;
	//str* body       = Str__new(bodyLength);
	//IO__ctxt__printLF("BODY STEP4");
	//for(ulng i=0ULL; i < bodyLength; i++) { str__indexAssign(body, i, str__index(icontent->s, startIndex + i)); }
	//IO__ctxt__printLF("BODY STEP5");

	//return value args (which is token's value)
	printf("PARSED VALUE CHAIN\n");
	return body;
}
