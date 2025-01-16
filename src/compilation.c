// ---------------- DEPENDENCIES ----------------

//compilation steps
#include "tokenization.c"
#include "asm.c"
#include "obj.c"






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

	//tokenize its content & sort them
	Parsing__ctx* ctx = Parsing__Ctx__new(inputPath, inputText);
	program*      p   = Program__fromCtx(ctx, outputPath); //output path for debug only
	str__free(inputText);

	//compile ordered tokens into ASM
	str* result = ASM__build(p);
	//program__free(p); <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< don't free for the moment

	//return resulted ASM
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
	str* result = OBJ__build(asmText, SDLDeps, usePIC);
	str__free(asmText);

	//return resulted OBJ
	return result;
}
