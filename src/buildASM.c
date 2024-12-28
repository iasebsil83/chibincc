// ---------------- DEPENDENCIES ----------------

//nothing for the moment
//#include ".c"






// ---------------- TOOLS ----------------

//{}






// ---------------- COMPILATION ----------------

//produce assembly text from tokens
str* buildASM(lst* tokens) {
	str* resultText = Str__new(0ULL);
	for(ulng t=0ULL; t < lst__length(tokens); t++) {
		token* tok = (token*)lst__index(tokens, t);

		//redirection
		/*switch(tok->id & NC__ROLE_MASK) {
			case NC__ROLE_EXECUTION:
				switch(tok->id & NC__EXE_STATEMENT_MASK) {
					case NC__EXE_STATEMENT_IF:       resultText = str__addSelf(resultText, ); break;
					case NC__EXE_STATEMENT_FOR:      resultText = str__addSelf(resultText, ); break;
					case NC__EXE_STATEMENT_WHILE:    resultText = str__addSelf(resultText, ); break;
					case NC__EXE_STATEMENT_SWITCH:   resultText = str__addSelf(resultText, ); break;
					case NC__EXE_STATEMENT_BREAK:    resultText = str__addSelf(resultText, ); break;
					case NC__EXE_STATEMENT_CONTINUE: resultText = str__addSelf(resultText, ); break;
					case NC__EXE_STATEMENT_RETURN:   resultText = str__addSelf(resultText, ); break;
					case NC__EXE_STATEMENT_VFC:      resultText = str__addSelf(resultText, ); break;
					default:                         resultText = str__addSelf(resultText, ); break;
				}
			break;
			case NC__ROLE_DEFINITION:
				switch(tok->id & NC__DEF_SCOPE_MASK) {
					case NC__DEF_SCOPE_INTERN: resultText = str__addSelf(resultText, ); break;
					case NC__DEF_SCOPE_EXTERN: resultText = str__addSelf(resultText, ); break;
					case NC__DEF_SCOPE_SHARED: resultText = str__addSelf(resultText, ); break;
					case NC__DEF_SCOPE_LOCAL:  resultText = str__addSelf(resultText, ); break;
					default:                   resultText = str__addSelf(resultText, );
				}
				switch(tok->id & NC__DEF_SCOPE_KIND_MASK) {
					case NC__DEF_SCOPE_KIND_COPY:      resultText = str__addSelf(resultText, ); break;
					case NC__DEF_SCOPE_KIND_STRUCTURE: resultText = str__addSelf(resultText, ); break;
					case NC__DEF_SCOPE_KIND_FUNCTION:  resultText = str__addSelf(resultText, ); break;
					case NC__DEF_SCOPE_KIND_DATA:      resultText = str__addSelf(resultText, ); break;
					default:                           resultText = str__addSelf(resultText, ); break;
				}
			break;
			default: resultText = str__addChrSelf(resultText, '?');
		}*/
	}
	return resultText;
}
