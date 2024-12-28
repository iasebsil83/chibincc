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
		case VARG__NAME:
			result = str__addChrSelf(result, 'N');
			result = str__addChrSelf(result, '"');
			s1 = str__copy((str*)(v->content));
			result = str__addSelf(result, s1);
			str__free(s1);
			result = str__addChrSelf(result, '"');
			return result;
		break;
		case VARG__LITERAL1:
			result = str__addChrSelf(result, '1');
			result = str__addChrSelf(result, '"');
			s1 = ulng__toStr((ubyt)(v->content));
			result = str__addSelf(result, s1);
			str__free(s1);
			result = str__addChrSelf(result, '"');
			return result;
		break;
		case VARG__LITERAL2:
			result = str__addChrSelf(result, '2');
			result = str__addChrSelf(result, '"');
			s1 = ulng__toStr((ushr)(v->content));
			result = str__addSelf(result, s1);
			str__free(s1);
			result = str__addChrSelf(result, '"');
			return result;
		break;
		case VARG__LITERAL4:
			result = str__addChrSelf(result, '4');
			result = str__addChrSelf(result, '"');
			s1 = ulng__toStr((uint)(v->content));
			result = str__addSelf(result, s1);
			str__free(s1);
			result = str__addChrSelf(result, '"');
			return result;
		break;
		case VARG__LITERAL8:
			result = str__addChrSelf(result, '8');
			result = str__addChrSelf(result, '"');
			s1 = ulng__toStr((ulng)(v->content));
			result = str__addSelf(result, s1);
			str__free(s1);
			result = str__addChrSelf(result, '"');
			return result;
		break;
		case VARG__CALL:
			result = str__addChrSelf(result, 'C');
			result = str__addChrSelf(result, '(');
			result = str__addChrSelf(result, '\n');
			for(ulng i=0ULL; i < lst__length((lst*)(v->content)); i++){
				s1 = Value__toStr((valueArg*)lst__index((lst*)(v->content), i), depth+1ULL);
				result = str__addSelf(result, s1);
				str__free(s1);
				result = str__addChrSelf(result, ',');
				result = str__addChrSelf(result, '\n');
			}
			for(ulng i=0; i < depth; i++){ result = str__addChrSelf(result, '\t'); }
			result = str__addChrSelf(result, ')');
		break;
		case VARG__SUBCONTENT:
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
			Log__errorLF(ctxt__toStr("[INTERNAL ERROR] INVALID VALUE ID given !"), true, Err__FAILURE);
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
		str* idStr = ulng__toStr((ulng)(tok->id));
		resultText = str__addSelf(resultText, idStr);
		str__free(idStr);
		resultText = str__addChrSelf(resultText, ' ');

		//ID decomposition
		switch(tok->id & NC__ROLE_MASK) {
			case NC__ROLE_EXECUTION:
				resultText = str__addChrSelf(resultText, 'X');
				switch(tok->id & NC__EXE_STATEMENT_MASK) {
					case NC__EXE_STATEMENT_IF:       resultText = str__addChrSelf(resultText, 'i'); break;
					case NC__EXE_STATEMENT_FOR:      resultText = str__addChrSelf(resultText, 'f'); break;
					case NC__EXE_STATEMENT_WHILE:    resultText = str__addChrSelf(resultText, 'w'); break;
					case NC__EXE_STATEMENT_SWITCH:   resultText = str__addChrSelf(resultText, 's'); break;
					case NC__EXE_STATEMENT_BREAK:    resultText = str__addChrSelf(resultText, 'b'); break;
					case NC__EXE_STATEMENT_CONTINUE: resultText = str__addChrSelf(resultText, 'c'); break;
					case NC__EXE_STATEMENT_RETURN:   resultText = str__addChrSelf(resultText, 'r'); break;
					case NC__EXE_STATEMENT_VFC:      resultText = str__addChrSelf(resultText, 'v'); break;
					default:                         resultText = str__addChrSelf(resultText, '?'); break;
				}
			break;
			case NC__ROLE_DEFINITION:
				resultText = str__addChrSelf(resultText, 'D');
				switch(tok->id & NC__DEF_SCOPE_MASK) {
					case NC__DEF_SCOPE_INTERN: resultText = str__addChrSelf(resultText, 'i'); break;
					case NC__DEF_SCOPE_EXTERN: resultText = str__addChrSelf(resultText, 'e'); break;
					case NC__DEF_SCOPE_SHARED: resultText = str__addChrSelf(resultText, 's'); break;
					case NC__DEF_SCOPE_LOCAL:  resultText = str__addChrSelf(resultText, 'l'); break;
					default:                   resultText = str__addChrSelf(resultText, '?');
				}
				switch(tok->id & NC__DEF_SCOPE_KIND_MASK) {
					case NC__DEF_SCOPE_KIND_COPY:      resultText = str__addChrSelf(resultText, 'c'); break;
					case NC__DEF_SCOPE_KIND_STRUCTURE: resultText = str__addChrSelf(resultText, 's'); break;
					case NC__DEF_SCOPE_KIND_FUNCTION:  resultText = str__addChrSelf(resultText, 'f'); break;
					case NC__DEF_SCOPE_KIND_DATA:      resultText = str__addChrSelf(resultText, 'd'); break;
					default:                           resultText = str__addChrSelf(resultText, '?'); break;
				}
			break;
			default: resultText = str__addChrSelf(resultText, '?');
		}
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
