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

	//load vocabulary
	//vocab* v = initVocab();

	//tokenize text
	IO__ctxt__printLF("ALPHA");
	lst* result = Tokenization__run(inputPath, inputText); //, v);
	IO__ctxt__printLF("BETA");
	free(inputText);

	//return token table
	return result;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/*Token *tok = NULL;

  // Process -include option
  for (int i = 0; i < opt_include.len; i++) {
    char *incl = opt_include.data[i];

    char *path;
    if (file_exists(incl)) {
      path = incl;
    } else {
      path = search_include_paths(incl);
      if (!path)
        error("-include: %s: %s", incl, strerror(errno));
    }

    Token *tok2 = must_tokenize_file(path);
    tok = append_tokens(tok, tok2);
  }

  // Tokenize and parse.
  Token *tok2 = must_tokenize_file(base_file);
  tok = append_tokens(tok, tok2);
  tok = preprocess(tok);
*/
