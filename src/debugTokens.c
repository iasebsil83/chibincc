// ---------------- SPECIFIC TOOLS ----------------

//conversions
str* Dcpy__toStr(Dcpy* c, ulng depth) {
	str* DCPY_TEXT    = ctxt__toStr("Dcpy{\n");
	str* NAME_TEXT    = ctxt__toStr("name:    ");
	str* SRCTYPE_TEXT = ctxt__toStr("srcType: ");
	str* result = Str__new(0ULL);
	result = str__addSelf(result, DCPY_TEXT);
	ulng subDepth = depth + 1ULL;
	for(ulng i=0ULL; i < subDepth; i++){ result = str__addChrSelf(result, '\t'); }
	result = str__addSelf(result, NAME_TEXT);
	result = str__addSelf(result, c->name);
	result = str__addChrSelf(result, '\n');
	for(ulng i=0ULL; i < subDepth; i++){ result = str__addChrSelf(result, '\t'); }
	result = str__addSelf(result, SRCTYPE_TEXT);
	result = str__addSelf(result, c->srcType);
	result = str__addChrSelf(result, '\n');
	for(ulng i=0ULL; i < depth; i++){ result = str__addChrSelf(result, i, '\t'); }

	//text conversion
	str* header = ctxt__toStr("Dcpy <");
	result = str__addSelf(result, header);
	str__free(header);
	result = str__addSelf(result, c->srcType);
	result = str__addChrSelf(result, ',');
	result = str__addSelf(result, c->name);
	result = str__addChrSelf(result, '>');
	result = str__addChrSelf(result, '\n');
	return result;
}
str* Dstc__toStr(Dstc* s, ulng depth) {
	str* result = Str__new(depth);
	for(ulng i=0ULL; i < depth; i++){ result = str__indexAssign(result, i, '\t'); }

	//text conversion
	str* header = ctxt__toStr("Dstc <");
	result = str__addSelf(result, header);
	str__free(header);
	result = str__addSelf(result, s->name);
	result = str__addChrSelf(result, ',');
	result = str__addChrSelf(result, '[');

	//fields
	for(ulng i=0ULL; i < lst__length(s->fields); i++) {
		dataDcl* d = (dataDcl*)lst__index(s->fields, i);
		result = str__addChrSelf(result, d->type);
		result = str__addChrSelf(result, ':');
		result = str__addChrSelf(result, d->name);
		result = str__addChrSelf(result, ',');
	}
	result = str__addChrSelf(result, ']');
	result = str__addChrSelf(result, '>');
	result = str__addChrSelf(result, '\n');
	return result;
}
str* Dfunction__toStr(Dfunction* f, ulng depth) {
	str* result = Str__new(depth);
	for(ulng i=0ULL; i < depth; i++){ result = str__indexAssign(result, i, '\t'); }

	//text conversion
	str* header = ctxt__toStr("Dfunction <");
	result = str__addSelf(result, header);
	str__free(header);
	result = str__addSelf(result, f->name);
	result = str__addChrSelf(result, ',');
	result = str__addSelf(result, f->returnType);
	result = str__addChrSelf(result, ',');
	result = str__addChrSelf(result, '[');

	//params
	for(ulng i=0ULL; i < lst__length(f->params); i++) {
		dataDcl* d = (dataDcl*)lst__index(f->params, i);
		result = str__addSelf(result, d->type);
		result = str__addChrSelf(result, ':');
		result = str__addSelf(result, d->name);
		result = str__addChrSelf(result, ',');
	}
	result = str__addChrSelf(result, ']');
	result = str__addChrSelf(result, '>');
	result = str__addChrSelf(result, '\n');
	return result;
}
str* dataItem__toStr(dataItem* d, ulng depth) {
	str* result = Str__new(depth);
	for(ulng i=0ULL; i < depth; i++){ result = str__indexAssign(result, i, '\t'); }

	//text conversion
	str* header = ctxt__toStr("dataItem <");
	result = str__addSelf(result, header);
	str__free(header);
	result = str__addSelf(result, d->type);
	result = str__addChrSelf(result, ',');
	result = str__addSelf(result, d->name);
	result = str__addChrSelf(result, ',');
	str* valueStr = value__toStr(d->value);
	result = str__addSelf(result, valueStr);
	str__free(valueStr);
	result = str__addChrSelf(result, ',');
	if(d->global){ result = str__addChrSelf(result, 'G'); }
	else         { result = str__addChrSelf(result, 'L'); }
	//result = str__addChrSelf(result, ',');
	//result = str__addSelf(result, d->offset); <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	result = str__addChrSelf(result, '>');
	result = str__addChrSelf(result, '\n');
	return result;
}
str* Xif__toStr(Xif* i, ulng depth) {
	str* result = Str__new(depth);
	for(ulng j=0ULL; j < depth; j++){ result = str__indexAssign(result, j, '\t'); }

	//text conversion
	str* header = ctxt__toStr("Xif <");
	result = str__addSelf(result, header);
	str__free(header);
	value* valueStr = value__toStr(i->condition);
	result = str__addSelf(result, valueStr);
	str__free(valueStr);

			s = lst_token__toStr((lst*)(v->content), depth+1ULL);
			result = str__addSelf(result, s);
			str__free(s);

	result = str__addSelf(result, d->type);
	result = str__addChrSelf(result, ',');
	result = str__addSelf(result, d->name);
	result = str__addChrSelf(result, ',');
	result = str__addSelf(result, d->value);
	result = str__addChrSelf(result, ',');
	if(d->global){ result = str__addChrSelf(result, 'G'); }
	else         { result = str__addChrSelf(result, 'L'); }
	//result = str__addChrSelf(result, ',');
	//result = str__addSelf(result, d->offset); <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	result = str__addChrSelf(result, '>');
	result = str__addChrSelf(result, '\n');
	return result;
}
str* Xfor__toStr(Xfor* f, ulng depth) {
	return ctxt__toStr("");
}
str* Xwhile__toStr(Xwhile*, ulng depth) {
	return ctxt__toStr();
}
str* Xswitch__toStr(Xswitch* s, ulng depth) {
}
str* call__toStr(call* c, ulng depth) {
	str* CALL_TEXT   = ctxt__toStr("call{\n");
	str* NAME_TEXT   = ctxt__toStr("name:   ");
	str* PARAMS_TEXT = ctxt__toStr("params: [\n");
	str* result = Str__new(0ULL);
	result = str__addSelf(result, CALL_TEXT);
	ulng subDepth = depth + 1ULL;
	for(ulng i=0ULL; i < subDepth; i++){ result = str__addChrSelf(result, '\t'); }
	result = str__addSelf(result, NAME_TEXT);
	result = str__addSelf(result, c->name);
	result = str__addChrSelf(result, '\n');
	for(ulng i=0ULL; i < subDepth; i++){ result = str__addChrSelf(result, '\t'); }
	result = str__addSelf(result, PARAMS_TEXT);
	for(ulng i=0ULL; i < lst__length(c->params); i++){
		str* s = value__toStr((value*)lst__index(c->params, i), subDepth);
		result = str__addSelf(result, s);
		str__free(s);
		result = str__addChrSelf(result, ',');
	}
	result = str__addChrSelf(result, ']');
	result = str__addChrSelf(result, '\n');
	for(ulng i=0ULL; i < depth; i++){ result = str__addChrSelf(result, '\t'); }
	result = str__addChrSelf(result, '}');
	str__free(CALL_TEXT);
	str__free(NAME_TEXT);
	str__free(PARAMS_TEXT);
	return result;
}






// ---------------- GENERIC TOOLS ----------------

//values
str* token__toStr(token* t, ulng depth);
str* lst_token__toStr(lst* tokens, ulng depth);
str* value__toStr(value* v, ulng depth) {
	str* result = Str__new(0ULL);
	str* s;
	for(ulng i=0; i < depth; i++){ result = str__addChrSelf(result, '\t'); }
	switch(v->id) {
		case VALUE_NAME:
			result = str__addChrSelf(result, 'N');
			result = str__addChrSelf(result, '"');
			s = str__copy((str*)(v->content));
			result = str__addSelf(result, s);
			str__free(s);
			result = str__addChrSelf(result, '"');
			return result;
		break;
		case VALUE__LITERAL1:
			result = str__addChrSelf(result, '1');
			result = str__addChrSelf(result, '"');
			s = ulng__toStr((ubyt)(v->content));
			result = str__addSelf(result, s);
			str__free(s);
			result = str__addChrSelf(result, '"');
			return result;
		break;
		case VALUE__LITERAL2:
			result = str__addChrSelf(result, '2');
			result = str__addChrSelf(result, '"');
			s = ulng__toStr((ushr)(v->content));
			result = str__addSelf(result, s);
			str__free(s);
			result = str__addChrSelf(result, '"');
			return result;
		break;
		case VALUE__LITERAL4:
			result = str__addChrSelf(result, '4');
			result = str__addChrSelf(result, '"');
			s = ulng__toStr((uint)(v->content));
			result = str__addSelf(result, s);
			str__free(s);
			result = str__addChrSelf(result, '"');
			return result;
		break;
		case VALUE__LITERAL8:
			result = str__addChrSelf(result, '8');
			result = str__addChrSelf(result, '"');
			s = ulng__toStr((ulng)(v->content));
			result = str__addSelf(result, s);
			str__free(s);
			result = str__addChrSelf(result, '"');
			return result;
		break;
		case VALUE__CALL:
			result = str__addSelf(result, call__toStr((call*)(v->content)) );
		break;
		case VALUE__SUBCONTENT:
			s = lst_token__toStr((lst*)(v->content), depth);
			result = str__addSelf(result, s);
			str__free(s);
		break;
		default:
			printf("[%02x]\n", v->id);
			Log__internalLF(ctxt__toStr("Invalid value ID in str conversion."), true);
	}
	return result;
}



//produce assembly text from tokens
str* token__toStr(token* t, ulng depth) {
	str* TOKEN_TEXT    = ctxt__toStr("token{\n");
	str* CTX_TEXT      = ctxt__toStr("ctx:     ");
	str* ID_TEXT       = ctxt__toStr("id:      ");
	str* CONTENT_TEXT  = ctxt__toStr("content: ");
	str* BREAK_TEXT    = ctxt__toStr("break\n");
	str* CONTINUE_TEXT = ctxt__toStr("continue\n");
	ulng subDepth = depth + 1ULL;
	str* result = Str__new(0ULL);
	result      = str__addSelf(result, TOKEN_TEXT);
	for(ulng i=0ULL; i < depth; i++){ result = str__addChrSelf(result, '\t'); }

	//1:location
	result   = str__addSelf(result, CTX_TEXT);
	str* ctxText = Parsing__ctx__toStr(tok->ctx);
	result   = str__addSelf(result, ctxText);
	str__free(ctxText);
	result   = str__addChrSelf(result, '\n');
	for(ulng i=0ULL; i < depth; i++){ result = str__addChrSelf(result, '\t'); }

	//2:ID
	result = str__addSelf(result, ID_TEXT);
	str* idStr = ulng__toStr((ulng)(t->id));
	result = str__addSelf(result, idStr);
	str__free(idStr);
	result = str__addChrSelf(result, ' ');

	//3:content => redirection
	str* contentText = NULL;
	switch(t->id & NC__ROLE_MASK) {

		//EXE
		case NC__ROLE_EXECUTION:
			result = str__addChrSelf(result, 'X');
			result = str__addChrSelf(result, '\n');
			for(ulng i=0; i < depth; i++){ result = str__addChrSelf(result, '\t'); }
			result = str__addSelf(result, CONTENT_TEXT);

			//EXE STATEMENT
			switch(t->id & NC__EXE_STATEMENT_MASK) {
				case NC__EXE_STATEMENT_IF:       contentText = x_if__toStr(    (x_fi*    )(t->content), subDepth); break;
				case NC__EXE_STATEMENT_FOR:      contentText = x_for__toStr(   (x_for*   )(t->content), subDepth); break;
				case NC__EXE_STATEMENT_WHILE:    contentText = x_while__toStr( (x_while* )(t->content), subDepth); break;
				case NC__EXE_STATEMENT_SWITCH:   contentText = x_switch__toStr((x_switch*)(t->content), subDepth); break;
				case NC__EXE_STATEMENT_RETURN:   contentText = valueArg__toStr((x_return*)(t->content), subDepth); break;
				case NC__EXE_STATEMENT_VFC:      contentText = call__toStr(    (call*    )(t->content), subDepth); break;
				case NC__EXE_STATEMENT_BREAK:    result = str__addSelf(result, BREAK_TEXT);    break;
				case NC__EXE_STATEMENT_CONTINUE: result = str__addSelf(result, CONTINUE_TEXT); break;
				default: Parsing__ctx__internalLF(t->ctx, ctxt__toStr("Undefined EXE STATEMENT in previously parsed token."), true);
			}
		break;

		//DEF
		case NC__ROLE_DEFINITION:
			result = str__addChrSelf(result, 'D');

			//DEF SCOPE
			switch(t->id & NC__DEF_SCOPE_MASK) {
				case NC__DEF_SCOPE_INTERN: result = str__addChrSelf(result, 'i'); break;
				case NC__DEF_SCOPE_EXTERN: result = str__addChrSelf(result, 'e'); break;
				case NC__DEF_SCOPE_SHARED: result = str__addChrSelf(result, 's'); break;
				case NC__DEF_SCOPE_LOCAL:  result = str__addChrSelf(result, 'l'); break;
				default: Parsing__ctx__internalLF(t->ctx, ctxt__toStr("Undefined DEF SCOPE in previously parsed token."), true);
			}
			result = str__addChrSelf(result, '\n');
			for(ulng i=0; i < depth; i++){ result = str__addChrSelf(result, '\t'); }
			result = str__addSelf(result, CONTENT_TEXT);

			//DEF SCOPE KIND
			switch(t->id & NC__DEF_SCOPE_KIND_MASK) {
				case NC__DEF_SCOPE_KIND_COPY:      contentText = d_cpy__toStr(     (d_cpy*     )(t->content), subDepth); break;
				case NC__DEF_SCOPE_KIND_STRUCTURE: contentText = d_stc__toStr(     (d_stc*     )(t->content), subDepth); break;
				case NC__DEF_SCOPE_KIND_FUNCTION:  contentText = d_function__toStr((d_function*)(t->content), subDepth); break;
				case NC__DEF_SCOPE_KIND_DATA:      contentText = dataItem__toStr(  (dataItem*  )(t->content), subDepth); break;
				default: Parsing__ctx__internalLF(t->ctx, ctxt__toStr("Undefined DEF SCOPE KIND in previously parsed token."), true);
			}
		break;
		default: Parsing__ctx__internalLF(t->ctx, ctxt__toStr("Undefined ROLE in previously parsed token."), true);
	}
	if(contentText != NULL) {
		result  = str__addSelf(result, contentText);
		str__free(contentText);
	}
	result = str__addChrSelf(result, '\n');
	for(ulng i=0; i < depth; i++){ result = str__addChrSelf(result, '\t'); }
	result = str__addChrSelf(result, '}');

	//return result
	str__free(TOKEN_TEXT);
	str__free(BREAK_TEXT);
	str__free(CONTINUE_TEXT);
	str__free(ID_TEXT  );
	str__free(CONTINUE_TEXT);
	str__free(CTX_TEXT );
	return result;
}

str* lst_token__toStr(lst* tokens, ulng depth) {
	depth++;
	str* result = Str__new(2ULL);
	result = str__indexAssign(result, 0ULL, '[');
	for(ulng t=0ULL; t < lst__length(tokens); t++) {
		token* tok     = (token*)lst__index(tokens, t);
		str*   tokText = token__toStr(tok, depth);
		result = str__addSelf(result, tokText);
		str__free(tokText);
		result = str__addChrSelf(result, ',');
	}
	result = str__addChrSelf(result, ']');
	return result;
}
