// ---------------- ANYTHING ----------------

//anything
//





// ---------------- PREPROCESS ----------------

//preprocess
str* preprocess(str* inputPath, tab* includeDirs) {

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

	return inputText;
}
