// ---------------- DEPENDENCIES ----------------

//standards
#include "std.c"

//compilation
#include "assembler.c"






// ---------------- OPTIONS ----------------

//options
byt OPTION__ASM     = '\x00';
byt OPTION__HELP    = '\x01';
byt OPTION__INCLUDE = '\x02';
byt OPTION__LINK    = '\x03';
byt OPTION__OUTPUT  = '\x04';
byt OPTION__PRE     = '\x05'; //preprocessor
byt OPTION__PIC     = '\x06';
byt OPTION__SDL     = '\x07';

//compilation modes
byt MODE__PRE = '\x00'; //preprocessor
byt MODE__ASM = '\x01';
byt MODE__OBJ = '\x02';






// ---------------- TOOLS ----------------

//help menu
void printUsage(tab* opts) {
	IO__ctxt__printLF("Usage: chibincc [options] <files>...");
	IO__ctxt__printLF("\nCompile NC source code into object format.\n");
	Opt__printUsage(opts);
	Syscall__exit(Err__SUCCESS);
}

tab* collectDependencies_SDL(opt* o){
	tab* deps;
	if(opt__enabled(o)){
		deps = str__splitByChr(o->value, ':');

		//check if library exists
		for(ulng d=0UL; d < deps->length; d++) {
			//str* p = tab_str__index(deps, d);
			//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< TODO (check absolute paths + in standard paths (/lib) + in LD_LIBRARY_PATH)
			//Path__errorIfNotFIle(p, Err__FAILURE);
		}
	}else{ deps = Tab__new(0ULL, NULL); }
	return deps;
}

tab* collectDependencies_includes(opt* o){
	tab* deps;
	if(opt__enabled(o)){
		deps = str__splitByChr(o->value, ':');

		//check if directory exists
		for(ulng d=0UL; d < deps->length; d++) {
			Path__errorIfNotDir(tab_str__index(deps, d), Err__FAILURE);
		}
	}else{ deps = Tab__new(0ULL, NULL); }
	return deps;
}






// ---------------- EXECUTION ----------------

//main
byt zmain(tab* args) {

	//opts & args
	tab* opts = Tab__new(8UL, NULL);
	tab_opt__indexAssign(opts, OPTION__ASM, Opt__new(
		'a', ctxt__toStr("asm"), false,
		Tab__new_2(
			ctxt__toStr("Compile until Assembly code only."),
			ctxt__toStr("Produce '.asm' files.")
		)
	));
	tab_opt__indexAssign(opts, OPTION__HELP, Opt__new(
		'h', ctxt__toStr("help"), false,
		Tab__new_1(
			ctxt__toStr("Show this help menu.")
		)
	));
	tab_opt__indexAssign(opts, OPTION__INCLUDE, Opt__new(
		'i', ctxt__toStr("include"), true,
		Tab__new_2(
			ctxt__toStr("Add include directories."),
			ctxt__toStr("If multiples, use colons ':' as separator.")
		)
	));
	tab_opt__indexAssign(opts, OPTION__LINK, Opt__new(
		'l', ctxt__toStr("link"), true,
		Tab__new_2(
			ctxt__toStr("Add required SDL dependencies."),
			ctxt__toStr("If multiples, use colons ':' as separator.")
		)
	));
	tab_opt__indexAssign(opts, OPTION__OUTPUT, Opt__new(
		'o', ctxt__toStr("output"), true,
		Tab__new_2(
			ctxt__toStr("Set the name of the output result file."),
			ctxt__toStr("Only applicable when compiling a single file.")
		)
	));
	tab_opt__indexAssign(opts, OPTION__PRE, Opt__new(
		'p', ctxt__toStr("prep"), false,
		Tab__new_2(
			ctxt__toStr("Only run preprocessor over given code."),
			ctxt__toStr("Produce '.nc.p' files.")
		)
	));
	tab_opt__indexAssign(opts, OPTION__PIC, Opt__new(
		'P', ctxt__toStr("PIC"), false,
		Tab__new_2(
			ctxt__toStr("Compile using Position Independant Code mechanisms."),
			ctxt__toStr("(required for making SDL files)")
		)
	));
	tab_opt__indexAssign(opts, OPTION__SDL, Opt__new(
		's', ctxt__toStr("sdl"), false,
		Tab__new_3(
			ctxt__toStr("Compile into an SDL instead of an object file."),
			ctxt__toStr("Option '-P/--pic' is automatically enabled with it."),
			ctxt__toStr("Produce '.sdl' files.")
		)
	));
	Arg__parse(args, opts);

	//help menu
	if(opt__enabled(tab_opt__index(opts, OPTION__HELP))) {
		printUsage(opts);
	}

	//output opt with multiple args
	str* outputPath = NULL;
	opt* o          = tab_opt__index(opts, OPTION__OUTPUT);
	if(opt__enabled(o)) {
		if(args->length > 1){
			Err__error(ctxt__toStr("Cannot have option '-o/--output' with multiple files as input."), 1);
		}
		outputPath = o->value;
	}

	//get SDL dependencies
	tab* SDLDeps = collectDependencies_SDL(tab_opt__index(opts, OPTION__LINK));

	//get include dirs
	tab* includeDirs = collectDependencies_includes(tab_opt__index(opts, OPTION__INCLUDE));

	//compilation mode : OBJ (default)
	byt mode = MODE__OBJ;

	//compilation mode : ASM
	if(opt__enabled(tab_opt__index(opts, OPTION__ASM))) { mode = MODE__ASM; }

	//compilation mode : PRE
	if(opt__enabled(tab_opt__index(opts, OPTION__PRE))) {
		if(mode != MODE__OBJ) { Err__error(ctxt__toStr("Cannot have both '-a/--asm' and '-p/--prep'."), 1); }
		mode = MODE__PRE;
	}

	//store PIC info
	boo usePIC = opt__enabled(tab_opt__index(opts, OPTION__PIC));

	//compile each file
	for(ulng f=0UL; f < args->length; f++) {
		str* inputPath = tab_str__index(args, f);
		Path__errorIfNotFile(inputPath, Err__FAILURE);

		//debug
		IO__ctxt__print("Compiling file '");
		IO__print(inputPath);
		IO__ctxt__printLF("' {");

		//preprocessor
		if(mode == MODE__PRE) {
			if(outputPath == NULL) { outputPath = str__add(Path__name(inputPath), ctxt__toStr(".nc.p")); }
			//str* result = preprocess(inputPath, includeDirs);
			//IO__writeFile(outputPath, result);
			//str__free(result);
		}

		//assembly
		else if(mode == MODE__ASM) {
			if(outputPath == NULL) { outputPath = str__add(Path__name(inputPath), ctxt__toStr(".asm")); }
			str* result = compile(inputPath, includeDirs);
			IO__writeFile(outputPath, result);
			str__free(result);
		}

		//object (default)
		else {
			if(outputPath == NULL) { outputPath = str__add(Path__name(inputPath), ctxt__toStr(".o")); }
			str* result = assemble(inputPath, includeDirs); //, SDLDeps, usePIC)
			IO__writeFile(outputPath, result);
			str__free(result);
		}

		//debug
		IO__printChr('}');
		IO__printChr('\n');
	}

	//terminated successfully
	return Err__SUCCESS;
}
