 // ---------------- IMPORTATIONS ----------------

//bases
#include "context.c"






// ---------------- SPECIFIC ----------------

//cyclic calls
lst* Tokenization__tokenize(         Parsing__ctx* ctx, boo inSubContent);
lst* Value__readWholeInstructionBody(Parsing__ctx* ctx, boo inCall      );

//numbers
void Value__parseByte_error(Parsing__ctx* ctx){ Parsing__ctx__errorLF(ctx, ctxt__toStr("Not enough character to parse ubyt (2 hex required after '1' delimiter).")); }
atm* Value__parseByte(Parsing__ctx* ctx) {
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

	//debug
	#ifdef DEBUG_AVAILABLE
	Parsing__ctx__debug_WITHOUT_LF(ctx, "VALUE PARSED BYTE");
	if(Log__LEVEL__DEBUG >= Log__level) { printf("[%02x]\n", literal); } //TEMPORARY FOR printf USE
	#endif

	//return result
	return ubyt__toAtm(literal);
}



//short
void Value__parseShort_error(Parsing__ctx* ctx){ Parsing__ctx__errorLF(ctx, ctxt__toStr("Not enough character to parse ushr (4 hex required after '2' delimiter).")); }
atm* Value__parseShort(Parsing__ctx* ctx) {
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

	//debug
	#ifdef DEBUG_AVAILABLE
	Parsing__ctx__debug_WITHOUT_LF(ctx, "VALUE PARSED SHORT");
	if(Log__LEVEL__DEBUG >= Log__level) { printf("[%04x]\n", literal); } //TEMPORARY FOR printf USE
	#endif

	//return result
	return ushr__toAtm(literal);
}



//integer
void Value__parseInteger_error(Parsing__ctx* ctx){ Parsing__ctx__errorLF(ctx, ctxt__toStr("Not enough character to parse uint (8 hex required after '4' delimiter).")); }
atm* Value__parseInteger(Parsing__ctx* ctx) {
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

	//debug
	#ifdef DEBUG_AVAILABLE
	Parsing__ctx__debug_WITHOUT_LF(ctx, "VALUE PARSED INTEGER");
	if(Log__LEVEL__DEBUG >= Log__level) { printf("[%08x]\n", literal); } //TEMPORARY FOR printf USE
	#endif

	//return result
	return uint__toAtm(literal);
}



//long
void Value__parseLong_error(Parsing__ctx* ctx){ Parsing__ctx__errorLF(ctx, ctxt__toStr("Not enough character to parse ulng (16 hex required after '8' delimiter).")); }
atm* Value__parseLong(Parsing__ctx* ctx) {
	str* expectedStr = Str__new(16ULL);

	//debug
	#ifdef DEBUG_AVAILABLE
	Parsing__ctx__debug(ctx, "VALUE PARSING LONG");
	#endif

	//read expected sequence (can have been made in a for, but not optimized)
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

	//debug
	#ifdef DEBUG_AVAILABLE
	Parsing__ctx__debug_WITHOUT_LF(ctx, "VALUE PARSED LONG");
	if(Log__LEVEL__DEBUG >= Log__level) { printf("[%016llx]\n", result); } //TEMPORARY FOR printf USE
	#endif

	//return as atm
	return ulng__toAtm(literal);
}



//subcontent
atm* Value__parseSubcontent(Parsing__ctx* ctx) {
	lst* subcontent = Lst__new();

	//read NC instructions until end-of-subcontent
	while(true) {
		atm* a = NC__parseOne(ctx, false);

		//reached end-of-subcontent
		if(a == NULL) { break; }

		//add NC instruction
		lst__append(subcontent, (ubyt*)a);
	}

	//return as atm
	return lst__toAtm(subcontent);
}



//call
atm* Value__parseCall(Parsing__ctx* ctx, str* name) {
	call* c   = malloc(sizeof(call));
	c->name   = name;
	c->params = Lst__new();
	Value__readWholeInstructionBody(ctx, c->params, true); //call params can be empty at the end

	//debug
	#ifdef DEBUG_AVAILABLE
	Parsing__ctx__debug_WITHOUT_LF(ctx, "CALL NAME IS \"");
	//paliative for the moment. previous debug call should contain this <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	Log__debug(name, false);
	Log__ctxt__debugLF("\"", false);
	#endif

	//return as atm
	return call__toAtm(c);
}



//name (return true if reached end of instruction)
boo Value__parseName(Parsing__ctx* ctx, lst* body, boo inCall) {
	boo inName           = true;
	boo maxLengthReached = false;
	boo EOI              = false; //End-Of-Instruction flag. It becomes End-Of-Call flag if inCall

	//debug
	#ifdef DEBUG_AVAILABLE
	Parsing__ctx__debug(ctx, "VALUE PARSING NAME(s)");
	#endif

	//prepare NAME storage
	istr* name = IStr__new(NC__NAME_LENGTH_MAX);
	istr__push(name, Parsing__ctx__get(ctx));

	//prepare NAME value container
	atm* atmResult = malloc(sizeof(atm));
	atmResult->id  = ATOM__str;

	//read NAME
	while(inName){
		if(Parsing__ctx__inc(ctx)) { break; }
		chr c = Parsing__ctx__get(ctx);

		//look for end delimiter
		switch(c) {



			//end-of-instruction => set EOI flag and then continue as it was end-of-name
			case '\n': if(!inCall) { EOI = true; }

			//end-of-name
			case ':':

				//transfer stored NAME into final result
				atmResult->data = (ptr)str__sub(name->s, 0ULL, name->index);
				lst__append(body, (byt*)atmResult);

				//debug
				#ifdef DEBUG_AVAILABLE
				Parsing__ctx__debug_WITHOUT_LF(ctx, "NAME IS \"");
				//paliative for the moment. previous debug call should contain this <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				Log__debug((str*)(atmResult->data), false);
				Log__ctxt__debugLF("\"", false);
				#endif

				//continue the right way (return)
				inName = false; //<=> return
			break;



			//start a new subcontent
			case '{':
				if(inCall) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Subcontents are not allowed in call parameters.")); }

				//transfer stored NAME into final result
				atmResult->data = (ptr)str__sub(name->s, 0ULL, name->index);
				lst__append(body, (byt*)atmResult);

				//debug
				#ifdef DEBUG_AVAILABLE
				Parsing__ctx__debug_WITHOUT_LF(ctx, "NAME IS \"");
				//paliative for the moment. previous debug call should contain this <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				Log__debug((str*)(atmResult->data), false);
				Log__ctxt__debugLF("\"", false);
				#endif

				//continue parsing the right way (parseSubcontent, return)
				lst__append(body, (byt*)Value__parseSubcontent(ctx));
				inName = false; //<=> return
			break;



			//start a new call
			case '(':

				//our atmResult won't be used because we will directly store an ATOM__call instead of an ATOM__str
				free(atmResult);

				//continue parsing on the right way (parseCall, return)
				lst__append(
					body,
					(byt*)Value__parseCall(ctx, str__sub(name->s, 0ULL, name->index)) //call name given as parameter
				);
				inName = false; //<=> return
			break;



			//end-of-call
			case ')':
				if(!inCall) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Can't have end-of-call outside a call.")); }

				//transfer stored NAME into final result
				atmResult->data = (ptr)str__sub(name->s, 0ULL, name->index);
				lst__append(body, (byt*)atmResult);

				//debug
				#ifdef DEBUG_AVAILABLE
				Parsing__ctx__debug_WITHOUT_LF(ctx, "NAME IS \"");
				//paliative for the moment. previous debug call should contain this <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				Log__debug((str*)(atmResult->data), false);
				Log__ctxt__debugLF("\"", false);
				#endif

				//continue parsing the right way
				EOI    = true;
				inName = false; //<=> return
			break;



			//no delimiter => regular part of the name
			default:
				if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' || c == '.' || c == '*') { //NAMEs charset
					if(maxLengthReached) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Too much characters in NAME.")); }
					if(istr__push(name, c)) { maxLengthReached = true; }
				}
				else { Parsing__ctx__errorLF(ctx, ctxt__toStr("Unauthorized middle character in NAME.")); }
		}
	}

	//debug
	#ifdef DEBUG_AVAILABLE
	Parsing__ctx__debug(ctx, "VALUE PARSED NAME(s)");
	#endif

	//free temporary structure
	istr__free(name, true);

	//share whether we must continue parsing values or stop here (for the current instruction)
	return EOI;
}






// ---------------- MAIN ENTRY POINT ----------------

//read body including nested instructions themselves (value parsing)
void Value__readWholeInstructionBody(Parsing__ctx* ctx, lst* body, boo inCall) {

	//debug
	#ifdef DEBUG_AVAILABLE
	if(inCall) { Parsing__ctx__debug(ctx, "PARSING VALUE CHAIN INSIDE CALL"); }
	else       { Parsing__ctx__debug(ctx, "PARSING VALUE CHAIN");             }
	#endif

	//as long as nothing is stopping the algorithm
	while(true) {

		//read next useful character
		while(true) {
			if(Parsing__ctx__inc(ctx)) { return; } //no more value to read
			chr c = Parsing__ctx__get(ctx);

			//skip line feeds ONLY IF IN CALL
			if(inCall && c == '\n') { continue; }

			//indent or value separator => skip it
			if(c != '\t' && c != ':') { break; }
		}

		//value detection from 1st character
		switch(c) {

			//end-of-instruction => end of value parsing
			case '\n': return;

			//ubyte detected
			case '1': lst__append(body, (ubyt*)Value__parseByte(ctx));

			//ushort detected
			case '2': lst__append(body, (ubyt*)Value__parseShort(ctx));

			//uinteger detected
			case '4': lst__append(body, (ubyt*)Value__parseInteger(ctx));

			//ulong detected
			case '8': lst__append(body, (ubyt*)Value__parseLong(ctx));

			//end of call => if inCall, our body is now full with its parameters
			case ')':
				if(!inCall) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Can't have end-of-call outside a call.")); }

				//debug
				#ifdef DEBUG_AVAILABLE
				if(inCall) { Parsing__ctx__debug(ctx, "PARSED VALUE CHAIN INSIDE_CALL"); }
				#endif
				return;
			break;

			//subcontent
			case '{':
				if(inCall) { Parsing__ctx__errorLF(ctx, ctxt__toStr("Subcontents are not allowed in call parameters.")); }
				lst__append(body, (ubyt*)Value__parseSubcontent(ctx));
			break;

				//other (beginning-of-call is not allowed here, it must be preceeded by a NAME => only in Value__parseName)
				default:

					//name detected
					if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
						if(Value__parseName(ctx, body, inCall)) { return; } //true if received end-of-instruction OR end-of-call
						// => in all cases, we stop our body parsing : body is full
						//no more value to stick to our instruction / no more value to read as call parameter

						//debug
						#ifdef DEBUG_AVAILABLE
						if(inCall) { Parsing__ctx__debug(ctx, "PARSED VALUE CHAIN INSIDE_CALL"); }
						else       { Parsing__ctx__debug(ctx, "PARSED VALUE CHAIN");             }
						#endif
					}

				//unauthorized beginning character
				else { Parsing__ctx__errorLF(ctx, ctxt__toStr("Unauthorized beginning character in instruction value.")); }
		}
	}

	//debug
	#ifdef DEBUG_AVAILABLE
	if(inCall) { Parsing__ctx__debug(ctx, "PARSED VALUE CHAIN INSIDE_CALL"); }
	else       { Parsing__ctx__debug(ctx, "PARSED VALUE CHAIN");             }
	#endif
}
