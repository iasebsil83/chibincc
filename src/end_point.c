// ---------------- GENERATED AT COMPILE TIME : ATOM FINALIZATION ----------------
#define SUBATOM_DECOMPOSITION
#ifdef  GENERATE_TOSTR
str* atm__toStr(atm* e, ulng depth) { //special generation for atoms
	switch(e->id) {

		//redirections
		case ATOM__byt:      return byt__toStr(e->data);
		case ATOM__shr:      return shr__toStr(e->data);
		case ATOM__int:      return int__toStr(e->data);
		case ATOM__lng:      return lng__toStr(e->data);
		case ATOM__ubyt:     return ubyt__toStr(e->data);
		case ATOM__ushr:     return ushr__toStr(e->data);
		case ATOM__uint:     return uint__toStr(e->data);
		case ATOM__ulng:     return ulng__toStr(e->data);
		case ATOM__flt:      return flt__toStr(e->data);
		case ATOM__dbl:      return dbl__toStr(e->data);
		case ATOM__boo:      return boo__toStr(e->data);
		case ATOM__ptr:      return ptr__toStr(e->data);
		case ATOM__tab:      return tab__toStr(e->data);
		case ATOM__lst_item: return lst_item__toStr(e->data);
		case ATOM__lst:      return lst__toStr(e->data);
		case ATOM__str:      return str__toStr(e->data);
		case ATOM__istr:     return istr__toStr(e->data);
		case ATOM__:    return __toStr(e->data);
		case ATOM__:    return __toStr(e->data);

		//special case for sub-atoms
		case ATOM__atm:{
			str* result = Str__new(0ULL);
			str* BEGINNING = ctxt__toStr("atm{");
			result = str__addSelf(result, BEGINNING);
			str__free(BEGINNING);

			//prepare depth spacing
			boo hasDepth    = (depth != -1LL);
			str* depthSpace = NULL;
			if(hasDepth) {
				depthSpace = Str__new(depth);
				str__fill(depthSpace, '\t');
			}

			//field1 : id
			if(hasDepth) { //spacing
				result = str__addChrSelf(result, '\n');
				result = str__addSelf(result, depthSpace);
				result = str__addChrSelf(result, '\t');
			}
			str* FIELD1 = ctxt__toStr("id:"); //name
			result = str__addSelf(result, FIELD1);
			str__free(FIELD1);
			fieldValue = uint__toStr(e->id); ///data
			result = str__addSelf(result, fieldValue);
			str__free(fieldValue);
			result = str__addChrSelf(result, ',');

			//field2 : data
			if(hasDepth) { //spacing
				result = str__addChrSelf(result, '\n');
				result = str__addSelf(result, depthSpace);
				result = str__addChrSelf(result, '\t');
			}
			str* FIELD2 = ctxt__toStr("data:"); //name
			result = str__addSelf(result, FIELD2);
			str__free(FIELD2);
			#ifdef SUBATOM_DECOMPOSITION
			fieldValue = atm__toStr(e->data); //data (recursive call)
			#else
			fieldValue = ptr__toStr(e->data); //data
			#endif
			result = str__addSelf(result, fieldValue);
			str__free(fieldValue);

			//last spacing
			if(hasDepth) {
				result = str__addChrSelf(result, '\n');
				result = str__addSelf(result, depthSpace);
			}
			result = str__addChrSelf(result, '}');
			return result;
		}

		//not defined (internal error)
		default: return NULL;
	}
}
#endif
