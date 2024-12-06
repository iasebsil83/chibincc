// ---------------- IMPORTATIONS ----------------

//bases
#include "context.c"






// ---------------- SPECIFIC ----------------

//numbers
void Value__parseByte_error(){ Tokenization__error(ctx, s("Not enough character to parse ubyt (2 hex required after '1' delimiter).")); }
valueArg* Value__parseByte(istr* icontent) {
	str* expectedStr = Str__new(2ULL);

	//read expected sequence
	if(Parsing__ctx__inc(ctx)) { Value__parseByte_error(); }
	str__indexAssign(expectedStr, 0ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseByte_error(); }
	str__indexAssign(expectedStr, 1ULL, Parsing__ctx__get(ctx));

	//parse literal
	ubyt literal = str__toUByt(expectedStr);
	str__free(expectedStr);

	//return as a generic valueArg element
	valueArg* result = malloc(sizeof(valueArg));
	result->id       = VALUE_ARG__LITERAL1;
	result->content  = (ubyt*)literal;
	return result;
}



//short
void Value__parseShort_error(){ Tokenization__error(ctx, s("Not enough character to parse ushr (4 hex required after '2' delimiter).")); }
valueArg* Value__parseShort(istr* icontent) {
	str* expectedStr = Str__new(4ULL);

	//read expected sequence
	if(Parsing__ctx__inc(ctx)) { Value__parseShort_error(); }
	str__indexAssign(expectedStr, 0ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseShort_error(); }
	str__indexAssign(expectedStr, 1ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseShort_error(); }
	str__indexAssign(expectedStr, 2ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseShort_error(); }
	str__indexAssign(expectedStr, 3ULL, Parsing__ctx__get(ctx));

	//parse literal
	ushr literal = str__toUShr(expectedStr);
	str__free(expectedStr);

	//return as a generic valueArg element
	valueArg* result = malloc(sizeof(valueArg));
	result->id       = VALUE_ARG__LITERAL2;
	result->content  = (ubyt*)literal;
	return result;
}



//integer
void Value__parseInteger_error(){ Tokenization__error(ctx, s("Not enough character to parse uint (8 hex required after '4' delimiter).")); }
valueArg* Value__parseInteger(istr* icontent) {
	str* expectedStr = Str__new(8ULL);

	//read expected sequence
	if(Parsing__ctx__inc(ctx)) { Value__parseInteger_error(); }
	str__indexAssign(expectedStr,  0ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseInteger_error(); }
	str__indexAssign(expectedStr,  1ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseInteger_error(); }
	str__indexAssign(expectedStr,  2ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseInteger_error(); }
	str__indexAssign(expectedStr,  3ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseInteger_error(); }
	str__indexAssign(expectedStr,  4ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseInteger_error(); }
	str__indexAssign(expectedStr,  5ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseInteger_error(); }
	str__indexAssign(expectedStr,  6ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseInteger_error(); }
	str__indexAssign(expectedStr,  7ULL, Parsing__ctx__get(ctx));

	//parse literal
	uint literal = str__toUInt(expectedStr);
	str__free(expectedStr);

	//return as a generic valueArg element
	valueArg* result = malloc(sizeof(valueArg));
	result->id       = VALUE_ARG__LITERAL4;
	result->content  = (ubyt*)literal;
	return result;
}



//long
void Value__parseLong_error(){ Tokenization__error(ctx, s("Not enough character to parse ulng (16 hex required after '8' delimiter).")); }
valueArg* Value__parseLong(istr* icontent) {
	str* expectedStr = Str__new(16ULL);

	//read expected sequence
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(); }
	str__indexAssign(expectedStr,  0ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(); }
	str__indexAssign(expectedStr,  1ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(); }
	str__indexAssign(expectedStr,  2ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(); }
	str__indexAssign(expectedStr,  3ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(); }
	str__indexAssign(expectedStr,  4ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(); }
	str__indexAssign(expectedStr,  5ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(); }
	str__indexAssign(expectedStr,  6ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(); }
	str__indexAssign(expectedStr,  7ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(); }
	str__indexAssign(expectedStr,  8ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(); }
	str__indexAssign(expectedStr,  9ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(); }
	str__indexAssign(expectedStr, 10ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(); }
	str__indexAssign(expectedStr, 11ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(); }
	str__indexAssign(expectedStr, 12ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(); }
	str__indexAssign(expectedStr, 13ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(); }
	str__indexAssign(expectedStr, 14ULL, Parsing__ctx__get(ctx));
	if(Parsing__ctx__inc(ctx)) { Value__parseLong_error(); }
	str__indexAssign(expectedStr, 15ULL, Parsing__ctx__get(ctx));

	//parse literal
	ulng literal = str__toULng(expectedStr);
	str__free(expectedStr);

	//return as a generic valueArg element
	valueArg* result = malloc(sizeof(valueArg));
	result->id       = VALUE_ARG__LITERAL8;
	result->content  = (ubyt*)literal;
	return result;
}



//subcontent
valueArg* Value__parseSubcontent(Parsing__ctx* ctx) {
	lst* subcontent = Tokenization__tokenize(ctx, ); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	//return as a generic valueArg element
	valueArg* result = malloc(sizeof(valueArg));
	result->id       = VALUE_ARG__SUBCONTENT;
	result->content  = (ubyt*)subcontent;
	return result;
}



//call
valueArg* Value__parseCall(Parsing__ctx* ctx) {
	lst* subValue = Value__readWholeInstructionBody(ctx); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	//return as a generic valueArg element
	valueArg* result = malloc(sizeof(valueArg));
	result->id       = VALUE_ARG__CALL;
	result->content  = (ubyt*)subValue;
	return result;
}



//name (return true if reached end of instruction)
boo Value__parseName(lst* body, Parsing__ctx* ctx) {
	
}






// ---------------- MAIN ENTRY POINT ----------------

//read body including nested instructions themselves (value parsing)
lst* Value__readWholeInstructionBody(Parsing__ctx* ctx) {
	lst* body = Lst__new();

	/*IO__ctxt__printLF("BODY STEP1 [");
	str* TECHT = Parsing__ctx__toStr(ctx);
	IO__printLF(TECHT);
	str__free(TECHT);
	IO__ctxt__printLF("BODY STEP1 ]");*/

	//starting position
	istr* icontent   = ctx->icontent;
	ulng  startIndex = icontent->index;

	//end of line => end of instruction
	//IO__ctxt__printLF("BODY STEP2");
	boo remaining = true;
	while(remaining) {
		if(Parsing__ctx__inc(ctx)) { break; }
		chr c = Parsing__ctx__get(ctx);
		switch(c) {

			//end of instruction => end of value parsing
			case '\n': remaining = false; break;

			//ubyte detected
			case '1': lst__append(body, (byt*)Value__parseByte(icontent)); break;

			//ushort detected
			case '2': lst__append(body, (byt*)Value__parseShort(icontent)); break;

			//uinteger detected
			case '4': lst__append(body, (byt*)Value__parseInteger(icontent)); break;

			//ulong detected
			case '8': lst__append(body, (byt*)Value__parseLong(icontent)); break;

			//subcontent
			case '{': lst__append(body, (byt*)Value__parseSubcontent(ctx)); break;

			//other
			default:

				//name detected (1 name detected can lead to several valueArg)
				if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
					if(Value__parseName(body, icontent)){ remaining = false; }
				}

				//unauthorized beginning character
				else{ Tokenization_error(ctx, s("Unauthorized beginning character in instruction value.")); }
		}
	}
	//IO__ctxt__printLF("BODY STEP3");

	//update value now that we have it
	//ulng bodyLength = icontent->index - startIndex;
	//str* body       = Str__new(bodyLength);
	//IO__ctxt__printLF("BODY STEP4");
	//for(ulng i=0ULL; i < bodyLength; i++) { str__indexAssign(body, i, str__index(icontent->s, startIndex + i)); }
	//IO__ctxt__printLF("BODY STEP5");

	//return value args (which is token's value)
	return body;
}
