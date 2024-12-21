// ---------------- DEPENDENCIES ----------------

//compilation steps
#include "tokenization.c"
#include "buildASM.c"
#include "buildOBJ.c"






// ---------------- COMPILATION HIGHER STEPS ----------------

//compile
str* compileIntoASM(str* inputPath, tab* includeDirs) {

	//debug
	IO__ctxt__printLF("  Compiling into ASM {");
	IO__ctxt__print("    inputPath[");
	IO__print(inputPath);
	IO__ctxt__printLF("    ]");
	IO__ctxt__print("    inc[");
	for(ulng i=0UL; i < includeDirs->length; i++) { IO__print(tab_str__index(includeDirs, i)); IO__ctxt__print(", "); }
	IO__ctxt__printLF("]");
	IO__ctxt__printLF("  }");

	//read given file
	str* inputText = IO__readFile(inputPath);

	//tokenize its content
	lst* tokens = Tokenization__run(inputPath, inputText);
	free(inputText);

	//compile tokens into ASM
	str* result = buildASM(tokens, 0ULL);
	for(ulng t=0ULL; t < lst__length(tokens); t++) { token__free((token*)lst__index(tokens, t)); }
	lst__free(tokens, false);

	//return result
	return result;
}

str* compileIntoOBJ(str* inputPath, tab* includeDirs, tab* SDLDeps, boo usePIC) {

	//debug
	IO__ctxt__printLF("  Compiling into OBJ {");
	IO__ctxt__print("    inputPath[");
	IO__print(inputPath);
	IO__ctxt__printLF("    ]");
	IO__ctxt__print("    inc[");
	for(ulng i=0UL; i < includeDirs->length; i++) { IO__print(tab_str__index(includeDirs, i)); IO__ctxt__print(", "); }
	IO__ctxt__printLF("]");
	IO__ctxt__print("    SDLDeps[");
	for(ulng i=0UL; i < SDLDeps->length; i++) { IO__print(tab_str__index(SDLDeps, i)); IO__ctxt__print(", "); }
	IO__ctxt__printLF("]");
	if(usePIC) { IO__ctxt__printLF("    usePIC[true]");  }
	else       { IO__ctxt__printLF("    usePIC[false]"); }
	IO__ctxt__printLF("  }");

	//compile into ASM first
	str* asmText = compileIntoASM(inputPath, includeDirs);

	//use it now to compile into OBJ
	str* result = buildOBJ(asmText, SDLDeps, usePIC);
	str__free(asmText);
	return result;
}
