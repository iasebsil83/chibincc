// ---------------- DEPENDENCIES ----------------

//compilation steps
#include "tokenization.c"
#include "buildASM.c"
#include "buildOBJ.c"






// ---------------- COMPILATION HIGHER STEPS ----------------

//compile
str* compileIntoASM(str* inputPath, tab* includeDirs) {

	//debug <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< into one call
	#ifdef DEBUG_AVAILABLE
	Err__ctxt__debugLF("Compiling into ASM {");
	Err__ctxt__debug("\tinputPath[");
	if(Err__debug_traces){
		IO__print(inputPath);
		IO__ctxt__printLF("]");
		Err__ctxt__debug("\tincludeDirs[");
		for(ulng i=0UL; i < includeDirs->length; i++) { IO__print(tab_str__index(includeDirs, i)); IO__ctxt__print(", "); }
		IO__ctxt__printLF("]");
	}
	Err__ctxt__debugLF("}");
	#endif

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

	//debug <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< into one call
	#ifdef DEBUG_AVAILABLE
	Err__ctxt__debugLF("Compiling into OBJ {");
	Err__ctxt__debug("\tinputPath[");
	if(Err__debug_traces) {
		IO__print(inputPath);
		IO__ctxt__printLF("]");
		Err__ctxt__debug("\tincludeDirs[");
		for(ulng i=0UL; i < includeDirs->length; i++) { IO__print(tab_str__index(includeDirs, i)); IO__ctxt__print(", "); }
		IO__ctxt__printLF("]");
		Err__ctxt__debug("\tSDLDeps[");
		for(ulng i=0UL; i < SDLDeps->length; i++) { IO__print(tab_str__index(SDLDeps, i)); IO__ctxt__print(", "); }
		IO__ctxt__printLF("]");
	}
	if(usePIC) { Err__ctxt__debugLF("\tusePIC[true]");  }
	else       { Err__ctxt__debugLF("\tusePIC[false]"); }
	Err__ctxt__debugLF("}");
	#endif

	//compile into ASM first
	str* asmText = compileIntoASM(inputPath, includeDirs);

	//use it now to compile into OBJ
	str* result = buildOBJ(asmText, SDLDeps, usePIC);
	str__free(asmText);
	return result;
}
