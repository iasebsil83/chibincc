// ---------------- DEFINITIONS ----------------

//internal structures
#include "tokenize.c"





// ---------------- PREPROCESS ----------------

//preprocess
tab* preprocess(str* inputPath, tab* includeDirs) {

	//debug
	IO__println(s("  Preprocessing {"));
	IO__print(s("    inputPath["));
	IO__print(inputPath);
	IO__println(s("    ]"));
	IO__print(s("    inc["));
	for(ulng i=0UL; i < includeDirs->length; i++) { IO__print(tab_str__index(includeDirs, i)); IO__print(s(", ")); }
	IO__println(s("]"));
	IO__println(s("  }"));

	//read input file
	str* inputText = IO__readFile(inputPath);

	//load vocabulary
	vocab* v = initVocab();

	//tokenize text
	tab* result = tokenize(inputPath, inputText, v);
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
