// ---------------- DEPENDENCIES ----------------

//compilation
#include "preprocessor.c"






// ---------------- COMPILING ----------------

//
str* buildAssembly(tab_tok* pproc_tokens) {
	return ;
}






// ---------------- MAIN ----------------

//compile
str* compile(str* inputPath, tab* includeDirs) { //, tab* SDLDeps, boo usePIC) {

	//debug
	IO__println(s("  Compiling {"));
	IO__print(s("    inputPath["));
	IO__print(inputPath);
	IO__println(s("    ]"));
	IO__print(s("    inc["));
	for(ulng i=0UL; i < includeDirs->length; i++) { IO__print(tab_str__index(includeDirs, i)); IO__print(s(", ")); }
	IO__println(s("]"));
	//IO__print(s("    SDLDeps["));
	//for(ulng i=0UL; i < SDLDeps->length; i++) { IO__print(tab_str__index(SDLDeps, i)); IO__print(s(", ")); }
	//IO__println(s("]"));
	//if(usePIC) { IO__println(s("    usePIC[true]")); }
	//else       { IO__println(s("    usePIC[false]")); }
	IO__println(s("  }"));

	//preprocess first
	tab_tok* pproc_tokens = preprocess(inputPath, includeDirs);

	//compile
	str* text = buildAssembly(pproc_tokens);
	tab_tok__free(pproc_tokens);

	//return result
	return result;
}
  Obj *prog = parse(tok);

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
