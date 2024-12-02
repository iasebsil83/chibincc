// ---------------- DEPENDENCIES ----------------

//compilation
#include "preprocessor.c"






// ---------------- COMPILING ----------------

//
str* buildAssembly(lst* pproc_tokens) {
	str* resultText = Str__new(0ULL);
	str* ID_TEXT       = s("\tid:    ");
	str* VALUE_TEXT    = s("\tvalue: ");
	str* CONTEXT_TEXT  = s("\tctx:   ");
	str* LOCATION_TEXT = s("\tloc:   ");
	for(ulng t=0ULL; t < lst__length(pproc_tokens); t++) {
		token* tok = (token*)lst__index(pproc_tokens, t);

		//ID
		str* idStr = ulng__toStr(tok->id);
		resultText = str__addSelf(resultText, idStr);
		str__free(idStr);
		resultText = str__addChrSelf(resultText, '\n');

		//body
		resultText = str__addSelf(resultText, (str*)(tok->body));
		resultText = str__addChrSelf(resultText, '\n');

		//location
		str* location = Parsing__ctx__toStr(tok->ctx);
		resultText = str__addSelf(resultText, location);
		str__free(location);
		resultText = str__addChrSelf(resultText, '\n');
		resultText = str__addChrSelf(resultText, '\n');
	}
	str__free(ID_TEXT      );
	str__free(VALUE_TEXT   );
	str__free(CONTEXT_TEXT );
	str__free(LOCATION_TEXT);
	return resultText;
}






// ---------------- MAIN ----------------

//compile
str* compile(str* inputPath, tab* includeDirs) { //, tab* SDLDeps, boo usePIC) {

	//debug
	IO__ctxt__printLF("  Compiling {");
	IO__ctxt__print("    inputPath[");
	IO__print(inputPath);
	IO__ctxt__printLF("    ]");
	IO__ctxt__print("    inc[");
	for(ulng i=0UL; i < includeDirs->length; i++) { IO__print(tab_str__index(includeDirs, i)); IO__ctxt__print(", "); }
	IO__ctxt__printLF("]");
	//IO__print("    SDLDeps["));
	//for(ulng i=0UL; i < SDLDeps->length; i++) { IO__print(tab_str__index(SDLDeps, i)); IO__print(", ")); }
	//IO__printLF("]"));
	//if(usePIC) { IO__printLF("    usePIC[true]")); }
	//else       { IO__printLF("    usePIC[false]")); }
	IO__ctxt__printLF("  }");

	//preprocess first
	lst* pproc_tokens = preprocess(inputPath, includeDirs);

	//compile
	str* result = buildAssembly(pproc_tokens);
	for(ulng t=0ULL; t < lst__length(pproc_tokens); t++) { token__free((token*)lst__index(pproc_tokens, t)); }
	lst__free(pproc_tokens, false);

	//return result
	return result;
}
/*  Obj *prog = parse(tok);

  // Open a temporary output buffer.
  char *buf;
  size_t buflen;
  FILE *output_buf = open_memstream(&buf, &buflen);

  // Traverse the AST to emit assembly.
  codegen(prog, output_buf);
  fclose(output_buf);

  // Write the asembly text to a file.
  FILE *out = open_file(output_file);
  fwrite(buf, buflen, 1, out);
  fclose(out);
*/
