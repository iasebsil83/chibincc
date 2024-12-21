// ---------------- DEPENDENCIES ----------------

//nothing for the moment
//#include ".c"






// ---------------- TOOLS ----------------

str* buildASM(lst* tokens, ulng depth);

//output <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< TEMPORARY DEBUG
str* Value__toStr(valueArg* v, ulng depth) {
	str* result = Str__new(0ULL);
	str* s1;
	for(ulng i=0; i < depth; i++){ result = str__addChrSelf(result, '\t'); }
	switch(v->id) {
		case '\x00': // VALUE_ARG__NAME:
			result = str__addChrSelf(result, 'N');
			result = str__addChrSelf(result, '"');
			s1 = str__copy((str*)(v->content));
			result = str__addSelf(result, s1);
			str__free(s1);
			result = str__addChrSelf(result, '"');
			return result;
		break;
		case '\x01': //VALUE_ARG__LITERAL1:
			result = str__addChrSelf(result, '1');
			result = str__addChrSelf(result, '"');
			s1 = ulng__toStr((ubyt)(v->content));
			str__free(s1);
			result = str__addChrSelf(result, '"');
			return result;
		break;
		case '\x02': //VALUE_ARG__LITERAL2:
			result = str__addChrSelf(result, '2');
			result = str__addChrSelf(result, '"');
			s1 = ulng__toStr((ushr)(v->content));
			str__free(s1);
			result = str__addChrSelf(result, '"');
			return result;
		break;
		case '\x03': //VALUE_ARG__LITERAL4:
			result = str__addChrSelf(result, '4');
			result = str__addChrSelf(result, '"');
			s1 = ulng__toStr((uint)(v->content));
			str__free(s1);
			result = str__addChrSelf(result, '"');
			return result;
		break;
		case '\x04': //VALUE_ARG__LITERAL8:
			result = str__addChrSelf(result, '8');
			result = str__addChrSelf(result, '"');
			s1 = ulng__toStr((ulng)(v->content));
			str__free(s1);
			result = str__addChrSelf(result, '"');
			return result;
		break;
		case '\x05': //VALUE_ARG__CALL:
			result = str__addChrSelf(result, 'C');
			result = str__addChrSelf(result, '(');
			result = str__addChrSelf(result, '\n');
			for(ulng i=0ULL; i < lst__length((lst*)(v->content)); i++){
				s1 = Value__toStr((valueArg*)lst__index((lst*)(v->content), i), depth+1ULL);
				result = str__addSelf(result, s1);
				str__free(s1);
				result = str__addChrSelf(result, ',');
			}
			for(ulng i=0; i < depth; i++){ result = str__addChrSelf(result, '\t'); }
			result = str__addChrSelf(result, ')');
		break;
		case '\x06': //VALUE_ARG__SUBCONTENT:
			result = str__addChrSelf(result, 'S');
			result = str__addChrSelf(result, '{');
			result = str__addChrSelf(result, '\n');
			s1 = buildASM((lst*)(v->content), depth+1ULL);
			result = str__addSelf(result, s1);
			str__free(s1);
			for(ulng i=0; i < depth; i++){ result = str__addChrSelf(result, '\t'); }
			result = str__addChrSelf(result, '}');
		break;
		default:
			printf("[%02x]\n", v->id);
			Err__error(ctxt__toStr("[INTERNAL ERROR] INVALID VALUE ID given !"), Err__FAILURE);
	}
	return result;
}






// ---------------- COMPILATION ----------------

//produce assembly text from tokens
str* buildASM(lst* tokens, ulng depth) {
	str* resultText = Str__new(0ULL);
	str* ID_TEXT   = ctxt__toStr("id:   ");
	str* CTX_TEXT  = ctxt__toStr("ctx:  ");
	str* BODY_TEXT = ctxt__toStr("body: ");
	for(ulng t=0ULL; t < lst__length(tokens); t++) {
		token* tok = (token*)lst__index(tokens, t);

		//ID
		for(ulng i=0; i < depth; i++){ resultText = str__addChrSelf(resultText, '\t'); }
		resultText = str__addSelf(resultText, ID_TEXT);
		str* idStr = ulng__toStr(tok->id);
		resultText = str__addSelf(resultText, idStr);
		str__free(idStr);
		resultText = str__addChrSelf(resultText, '\n');

		//location
		for(ulng i=0; i < depth; i++){ resultText = str__addChrSelf(resultText, '\t'); }
		resultText   = str__addSelf(resultText, CTX_TEXT);
		str* ctxText = Parsing__ctx__toStr(tok->ctx);
		resultText   = str__addSelf(resultText, ctxText);
		str__free(ctxText);
		resultText   = str__addChrSelf(resultText, '\n');

		//body
		for(ulng i=0; i < depth; i++){ resultText = str__addChrSelf(resultText, '\t'); }
		resultText = str__addSelf(resultText, BODY_TEXT);
		str* currentValueText;
		resultText = str__addChrSelf(resultText, '[');
		for(ulng b=0ULL; b < lst__length(tok->body); b++) {
			currentValueText = Value__toStr((valueArg*)lst__index(tok->body, b), depth);
			resultText = str__addSelf(resultText, currentValueText);
			str__free(currentValueText);
			resultText = str__addChrSelf(resultText, ',');
		}
		resultText = str__addChrSelf(resultText, ']');
		resultText = str__addChrSelf(resultText, '\n');
		resultText = str__addChrSelf(resultText, '\n');
	}
	str__free(ID_TEXT  );
	str__free(BODY_TEXT);
	str__free(CTX_TEXT );
	return resultText;
}
