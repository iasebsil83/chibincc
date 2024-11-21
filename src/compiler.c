// ---------------- DEPENDENCIES ----------------

//compilation
#include "assembler.c"






// ---------------- ANYTHING ----------------

//anything
//





// ---------------- COMPILE ----------------

//compile
str* compile(str* inputPath, tab* includeDirs, tab* SDLDeps, boo usePIC) {

	//debug
	IO__println(s("  Compiling {"));
	IO__print(s("    inputPath["));
	IO__print(inputPath);
	IO__println(s("    ]"));
	IO__print(s("    inc["));
	for(ulng i=0UL; i < includeDirs->length; i++) { IO__print(tab_str__index(includeDirs, i)); IO__print(s(", ")); }
	IO__println(s("]"));
	IO__print(s("    SDLDeps["));
	for(ulng i=0UL; i < SDLDeps->length; i++) { IO__print(tab_str__index(SDLDeps, i)); IO__print(s(", ")); }
	IO__println(s("]"));
	if(usePIC) { IO__println(s("    usePIC[true]")); }
	else       { IO__println(s("    usePIC[false]")); }
	IO__println(s("  }"));

	//read input file
	str* inputText = IO__readFile(inputPath);

	return inputText;
}
