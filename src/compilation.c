// ---------------- DEPENDENCIES ----------------

//compilation steps
#include "tokenization.c"
#include "buildASM.c"
#include "buildOBJ.c"

//debug
#ifdef DEBUG_AVAILABLE
#include "debugTokens.c"
#endif






// ---------------- COMPILATION HIGHER STEPS ----------------

//compile
str* compileIntoASM(str* inputPath, tab* includeDirs, str* outputPath) { //outputPath for debug only

	//debug <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< into one call
	#ifdef DEBUG_AVAILABLE
	Log__ctxt__debugLF("Compiling into ASM {", true);
	Log__ctxt__debug("\tinputPath[", true);
	Log__debug(inputPath, false);
	Log__ctxt__debugLF("]", false);
	Log__ctxt__debug("\tincludeDirs[", true);
	for(ulng i=0UL; i < includeDirs->length; i++) { Log__debug(tab_str__index(includeDirs, i), false); Log__ctxt__debug(", ", false); }
	Log__ctxt__debugLF("]", false);
	Log__ctxt__debugLF("}", true);
	#endif

	//read given file
	str* inputText = IO__readFile(inputPath);

	//tokenize its content
	lst* tokens = Tokenization__run(inputPath, inputText);
	str__free(inputText);

	//debug
	#ifdef DEBUG_AVAILABLE
	if(Log__level <= Log__LEVEL__DEBUG) {
		str* ending = ctxt__toStr(".debug"); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< to remove using constant
		str* debugOutputPath = str__add(outputPath, ending);
		str* debugOutput     = debugTokens(tokens, 0ULL);
		IO__writeFile(debugOutputPath, debugOutput);
		str__free(ending); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< as well
		str__free(debugOutputPath);
		str__free(debugOutput);
	}
	#endif

	//compile tokens into ASM
	str* result = buildASM(tokens);
	//for(ulng t=0ULL; t < lst__length(tokens); t++) { token__free((token*)lst__index(tokens, t)); } //don't free for the moment <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//lst__free(tokens, false);

	//return result
	return result;
}

str* compileIntoOBJ(str* inputPath, tab* includeDirs, tab* SDLDeps, boo usePIC, str* outputPath) { //outputPath for debug only

	//debug <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< into one call
	#ifdef DEBUG_AVAILABLE
	Log__ctxt__debugLF("Compiling into OBJ {", true);
	Log__ctxt__debug("\tinputPath[", true);
	Log__debug(inputPath, false);
	Log__ctxt__debugLF("]", false);
	Log__ctxt__debug("\tincludeDirs[", true);
	for(ulng i=0UL; i < includeDirs->length; i++) { Log__debug(tab_str__index(includeDirs, i), false); Log__ctxt__debug(", ", false); }
	Log__ctxt__debugLF("]", false);
	Log__ctxt__debug("\tSDLDeps[", true);
	for(ulng i=0UL; i < SDLDeps->length; i++) { Log__debug(tab_str__index(SDLDeps, i), false); Log__ctxt__debug(", ", false); }
	Log__ctxt__debugLF("]", false);
	if(usePIC) { Log__ctxt__debugLF("\tusePIC[true]", true);  }
	else       { Log__ctxt__debugLF("\tusePIC[false]", true); }
	Log__ctxt__debugLF("}", true);
	#endif

	//compile into ASM first
	str* asmText = compileIntoASM(inputPath, includeDirs, outputPath);

	//use it now to compile into OBJ
	str* result = buildOBJ(asmText, SDLDeps, usePIC);
	str__free(asmText);
	return result;
}
