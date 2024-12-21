// ---------------- DEFINITIONS ----------------

//internal structures
#include "tokenization.c"





// ---------------- PREPROCESS ----------------

//preprocess
lst* preprocess(str* inputPath, tab* includeDirs) {

	//debug
	IO__ctxt__printLF("  Preprocessing {");
	IO__ctxt__print("    inputPath[");
	IO__print(inputPath);
	IO__ctxt__printLF("    ]");
	IO__ctxt__print("    inc[");
	for(ulng i=0ULL; i < includeDirs->length; i++) { IO__print(tab_str__index(includeDirs, i)); IO__printChr(','); }
	IO__ctxt__printLF("]");
	IO__ctxt__printLF("  }");

	//read input file
	str* inputText = IO__readFile(inputPath);

	//tokenize text
	lst* result = Tokenization__run(inputPath, inputText); //, v);
	free(inputText);

	//return token table
	return result;
}
