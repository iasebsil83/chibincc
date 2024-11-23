// ---------------- DEPENDENCIES ----------------

//preprocess
#include "compiler.c"






// ---------------- ASSEMBLING ----------------

//assembling
str* buildObj(str* inputASM) {
	return inputASM;
}






// ---------------- ASSEMBLE ----------------

//assemble
str* assemble(str* inputPath, tab* includeDirs) {

	//debug
	IO__println(s("  Assembling {"));
	IO__print(s("    inputPath["));
	IO__print(inputPath);
	IO__println(s("    ]"));
	IO__print(s("    inc["));
	for(ulng i=0UL; i < includeDirs->length; i++) { IO__print(tab_str__index(includeDirs, i)); IO__print(s(", ")); }
	IO__println(s("]"));
	IO__println(s("  }"));

	//compile first
	str* asm = compile(inputPath, includeDirs);

	//assemble
	str* result = buildObj(asm);
	//str__free(asm); <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< DONT FREE FOR THE MOMENT AS IT IS EXACTLY THE SAME THING AS RESULT

	//return result
	return result;
}
