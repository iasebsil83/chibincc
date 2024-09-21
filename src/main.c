// ---------------- DEPENDENCIES ----------------

//standards
#include "std.c"






// ---------------- OPTIONS ----------------

//options
byt OPTION__COMMON = '\x00'; //defaulted to true
byt OPTION__PIC = '\x01';
byt OPTION__X = '\x02'; //BYT
byt OPTION__INCLUDE = '\x03'; //TAB[STR]
byt OPTION__PREPROCESSOR = '\x04';
byt OPTION__M = '\x05';
byt OPTION__MD = '\x06';
byt OPTION__MMD = '\x07';
byt OPTION__MP = '\x08';
byt OPTION__ASM = '\x09';
byt OPTION__C   = '\x0a';
byt OPTION__CC1 = '\x0b';
byt OPTION__HASH = '\x0c';
byt OPTION__STATIC = '\x0d';
byt OPTION__SHARED = '\x0e';
byt OPTION__MF = '\x0f';
byt OPTION__MT = '\x10';
byt OPTION__OUTPUT = '\x11';
byt OPTION__HELP = '\x12';






// ---------------- EXECUTION ----------------

//output shortcuts
void printBooOpt(opt* o) {
	if(opt__enabled(o)) {
		IO__println(
			str__add(str__add(s("  Boolean option '--"), o->long_name), s("' is enabled."))
		);
	}
}

void printTextOpt(opt* o) {
	if(opt__enabled(o)) {
		IO__println(
			str__add(str__add(str__add(str__add(s("  Text option '--"), o->long_name), s("' is enabled with value \"")), o->value), s("\"."))
		);
	}
}



//main
byt zmain(tab* args) {

	//arguments
	tab* opts = Tab__new(19, NULL);
	tab_opt__indexAssign(opts, OPTION__COMMON      , Opt__new('O', s("common"), false));
	tab_opt__indexAssign(opts, OPTION__PIC         , Opt__new('i', s("pic"), false));
	tab_opt__indexAssign(opts, OPTION__X           , Opt__new('x', s("x"), true));
	tab_opt__indexAssign(opts, OPTION__INCLUDE     , Opt__new('I', s("include"), false));
	tab_opt__indexAssign(opts, OPTION__PREPROCESSOR, Opt__new('p', s("preprocessor"), false));
	tab_opt__indexAssign(opts, OPTION__M           , Opt__new('m', s("m"), false));
	tab_opt__indexAssign(opts, OPTION__MD          , Opt__new('d', s("md"), false));
	tab_opt__indexAssign(opts, OPTION__MMD         , Opt__new('M', s("mmd"), false));
	tab_opt__indexAssign(opts, OPTION__MP          , Opt__new('P', s("mp"), false));
	tab_opt__indexAssign(opts, OPTION__ASM         , Opt__new('s', s("asm"), false));
	tab_opt__indexAssign(opts, OPTION__C           , Opt__new('c', s("c"), false));
	tab_opt__indexAssign(opts, OPTION__CC1         , Opt__new('C', s("cc1"), false));
	tab_opt__indexAssign(opts, OPTION__HASH        , Opt__new('H', s("hash"), false));
	tab_opt__indexAssign(opts, OPTION__STATIC      , Opt__new('T', s("static"), false));
	tab_opt__indexAssign(opts, OPTION__SHARED      , Opt__new('S', s("shared"), false));
	tab_opt__indexAssign(opts, OPTION__MF          , Opt__new('f', s("mf"), true));
	tab_opt__indexAssign(opts, OPTION__MT          , Opt__new('t', s("mt"), true));
	tab_opt__indexAssign(opts, OPTION__OUTPUT      , Opt__new('o', s("output"), true));
	tab_opt__indexAssign(opts, OPTION__HELP        , Opt__new('h', s("help"), false));
	//IO__println(s("ALPHA"));
	Arg__parse(args, opts);
	//IO__println(s("BETA"));

	//print options statuses
	IO__println(s("Options ("));
	printBooOpt(tab_opt__index(opts, OPTION__COMMON));
	printBooOpt(tab_opt__index(opts, OPTION__PIC));
	printTextOpt(tab_opt__index(opts, OPTION__X));
	printBooOpt(tab_opt__index(opts, OPTION__INCLUDE));
	printBooOpt(tab_opt__index(opts, OPTION__PREPROCESSOR));
	printBooOpt(tab_opt__index(opts, OPTION__M));
	printBooOpt(tab_opt__index(opts, OPTION__MD));
	printBooOpt(tab_opt__index(opts, OPTION__MMD));
	printBooOpt(tab_opt__index(opts, OPTION__MP));
	printBooOpt(tab_opt__index(opts, OPTION__ASM));
	printBooOpt(tab_opt__index(opts, OPTION__C));
	printBooOpt(tab_opt__index(opts, OPTION__CC1));
	printBooOpt(tab_opt__index(opts, OPTION__HASH));
	printBooOpt(tab_opt__index(opts, OPTION__STATIC));
	printBooOpt(tab_opt__index(opts, OPTION__SHARED));
	printTextOpt(tab_opt__index(opts, OPTION__MF));
	printTextOpt(tab_opt__index(opts, OPTION__MT));
	printTextOpt(tab_opt__index(opts, OPTION__OUTPUT));
	printBooOpt(tab_opt__index(opts, OPTION__HELP));

	//print real arguments
	IO__println(s(")\nReal arguments ("));
	for(ulng i=0UL; i < args->length; i++) {
		IO__println( str__add(str__add(s("  \""), tab_str__index(args,i)), s("\",")) );
	}
	IO__println(s(")"));

	return Err__SUCCESS;
}
