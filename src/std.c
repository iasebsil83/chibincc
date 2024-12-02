// ---------------- DEPENDENCIES ----------------

//memory
#include <stdlib.h> //malloc(), free(), exit()

//output
#include <stdio.h> //putchar(), fopen(), fgetc(), fputc(), fclose(), fseek(), ftell(), open_memstream()






// ---------------- ROOTS ----------------

//shortcut notations for types
typedef          char       byt;
typedef unsigned char      ubyt;
typedef unsigned int       uint;
typedef          long long  lng;
typedef unsigned long long ulng;


//booleans
typedef byt boo;
boo false = '\x00';
boo true  = '\x01';






// ---------------- SYSTEM ----------------

//syscalls
void Syscall__exit(byt err) {
	exit(err);
}





// ---------------- TABLES ----------------

//definitions
typedef struct {
	ulng length;
	byt** data;
} tab;

//methods
tab* Tab__new(ulng length, byt** initialData) {
	tab* t    = malloc(sizeof(tab));
	t->length = length;
	t->data   = malloc(length * sizeof(byt*));
	if(initialData != NULL) {
		for(ulng i=0UL; i < length; i++) {
			t->data[i] = initialData[i];
		}
	}
	return t;
}
byt* tab_ptr_byt__index(tab* t, ulng index) {
	return (t->data)[index];
}
void tab_ptr_byt__indexAssign(tab* t, ulng index, byt* element) {
	(t->data)[index] = element;
}
void tab__freeData(tab* t) {
	for(ulng i=0UL; i < t->length; i++) {
		free(tab_ptr_byt__index(t,i));
	}
}
void tab__freeStructure(tab* t) {
	free(t->data);
	free(t);
}
void tab__freeAll(tab* t) {
	tab__freeData(t);
	tab__freeStructure(t);
}






// ---------------- LISTS ----------------

//definitions
typedef struct {
	byt* next;
	byt* data;
} lst_item;
typedef struct {
	lst_item* firstItem;
} lst;

//methods
lst* Lst__new() {
	lst* l = malloc(sizeof(lst));
	l->firstItem = NULL;
	return l;
}
lst_item* lst__lastItem(lst* l) {
	if(l->firstItem == NULL){ return NULL; }
	lst_item* last = l->firstItem;
	while(last->next != NULL) { last = (lst_item*)(last->next); }
	return last;
}
ulng lst__length(lst* l) {
	if(l->firstItem == NULL){ return 0UL; }
	ulng length = 1UL;
	lst_item* last = l->firstItem;
	while(last->next != NULL) { last = (lst_item*)(last->next); length++; }
	return length;
}
void lst__append(lst* l, byt* element) {
	lst_item* newItem = malloc(sizeof(lst_item));
	newItem->data = element;
	newItem->next = NULL;

	//connect to correct part
	lst_item* lastItem = lst__lastItem(l);
	if(lastItem == NULL){ l->firstItem   =       newItem; }
	else                { lastItem->next = (byt*)newItem; }
}
lst_item* lst__indexItem(lst* l, ulng index) {
	lst_item* current = l->firstItem;
	for(ulng i=0UL; i < index; i++) {
		if(current == NULL) { return NULL; }
		current = (lst_item*)(current->next);
	}
	if(current == NULL) { return NULL; }
	return current;
}
byt* lst__index(lst* l, ulng index) {
	lst_item* targettedItem = lst__indexItem(l, index);
	if(targettedItem == NULL) { return NULL; }
	return targettedItem->data;
}
byt* lst__last(lst* l) {
	lst_item* lastItem = lst__lastItem(l);
	if(lastItem == NULL) { return NULL; }
	return lastItem->data;
}
void lst__free(lst* l, boo freeData) {
	ulng len = lst__length(l);
	for(ulng i=0UL; i < len; i++) {
		lst_item* currentItem = lst__indexItem(l, i);
		if(freeData) { free(currentItem->data); }
		free(currentItem);
	}
	free(l);
}






// ---------------- TEXT ----------------

//definitions
typedef byt chr;
typedef struct {
	ulng length;
	chr* data;
} str;

//methods
str* Str__new(ulng length) {
	str* s    = malloc(sizeof(str));
	if(length == 0UL) { s->data = NULL;                         }
	else              { s->data = malloc(length * sizeof(chr)); }
	s->length = length;
	return s;
}
str* ctxt__toStr(chr* data) { //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< TEMPORARY
	str* s = malloc(sizeof(str));
	s->data   = data;
	s->length = 0UL;
	if(data != NULL) {
		while(data[0] != '\0'){
			data++;
			s->length++;
		}
	}
	return s;
}
void str__free(str* s){
	free(s->data);
	free(s);
}
str* s(chr* data) { return ctxt__toStr(data); } //shortcut notation <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< TEMPORARY AS WELL
chr str__index(str* s, ulng index) {
	return s->data[index];
}
void str__indexAssign(str* s, ulng index, chr value) {
	s->data[index] = value;
}
str* str__sub(str* s, ulng firstIndex, ulng lastIndex) {
	if(lastIndex == (ulng)-1L) {
		lastIndex = s->length - 1UL;
	}
	if(firstIndex >= lastIndex) { return NULL; } //empty or out of possible scope
	ulng newLength = lastIndex - firstIndex + 1UL;
	if(newLength == s->length) { return s; } //nothing to operate
	str* newS = Str__new(newLength);
	for(ulng i=firstIndex; i <= lastIndex; i++) {
		newS->data[i-firstIndex] = str__index(s,i);
	}
	return newS;
}
boo str__equal(str* s1, str* s2) {
	if(s1->length != s2->length) { return false; }
	for(ulng i=0UL; i < s1->length; i++) {
		if(s1->data[i] != s2->data[i]) { return false; }
	}
	return true;
}
str* str__add(str* s1, str* s2) {
	str* s3 = Str__new(s1->length + s2->length);
	for(ulng i=0UL; i < s1->length; i++) {
		str__indexAssign(s3, i, str__index(s1,i));
	}
	for(ulng i=0UL; i < s2->length; i++) {
		str__indexAssign(s3, s1->length+i, str__index(s2,i));
	}
	return s3;
}
str* str__addSelf(str* s1, str* s2) {
	str* s3 = str__add(s1, s2);
	str__free(s1);
	return s3;
}
str* str__addChr(str* s, chr c) {
	str* r = Str__new(s->length+1);
	for(ulng i=0UL; i < s->length; i++) {
		str__indexAssign(r, i, str__index(s,i));
	}
	str__indexAssign(r, s->length, c);
	return r;
}
str* str__addChrSelf(str* s, chr c) {
	str* s2 = str__addChr(s, c);
	str__free(s);
	return s2;
}
str* tab_str__index(tab* t, ulng index) {
	return (str*)tab_ptr_byt__index(t, index);
}
void tab_str__indexAssign(tab* t, ulng index, str* value) {
	tab_ptr_byt__indexAssign(t, index, (byt*)value);
}
ulng str__findFirstChr(str* s, chr c, ulng offset) {
	if(offset >= s->length) { return (ulng)-1L; }

	for(ulng t=offset; t < s->length; t++) {
		if(str__index(s, t) == c) { return t; }
	}
	return (ulng)-1L;
}
ulng str__findLastChr(str* s, chr c) {
	ulng lastIndex = (ulng)-1L;
	for(ulng t=0UL; t < s->length; t++) {
		if(str__index(s, t) == c) { lastIndex = t; }
	}
	return lastIndex;
}
ulng str__countChr(str* s, chr c) {
	ulng cnt = 0UL;
	for(ulng t=0UL; t < s->length; t++) {
		if(str__index(s, t) == c) { cnt++; }
	}
	return cnt;
}
tab* str__findAllChr(str* s, chr c) { //returning tab[ulng]
	ulng len = str__countChr(s, c);
	tab* result = Tab__new(len, NULL);

	//store indexes
	ulng currentIndex = 0UL;
	for(ulng t=0UL; t < s->length; t++) {
		if(str__index(s, t) == c) {
			tab_ptr_byt__indexAssign(result, currentIndex, (byt*)t);
			currentIndex++;
		}
	}
	return result;
}
tab* str__splitByChr(str* s, chr c) {
	tab* indexes = str__findAllChr(s, c);
	tab* result = Tab__new(indexes->length + 1UL, NULL);
	ulng startIndex = 0UL;
	for(ulng i=0UL; i < indexes->length; i++) {
		ulng currentIndex = (ulng)tab_ptr_byt__index(indexes, i);

		//create current str (can be empty)
		str* currentStr = Str__new(currentIndex - startIndex);
		for(ulng t=0UL; t < currentStr->length; t++) {
			str__indexAssign(
				currentStr, t,
				str__index(s, startIndex+t)
			);
		}
		tab_str__indexAssign(result, i, currentStr);

		//update startIndex
		startIndex = currentIndex+1UL;
	}
	return result;
}
chr* str__toCtxt(str* s) {
	chr* ctxt = malloc(s->length+1UL);
	for(ulng i=0UL; i < s->length; i++) { ctxt[i] = str__index(s, i); }
	ctxt[s->length] = '\0';
	return ctxt;
}
tab* Tab__new_1(str* elem1) { //intermediate to declare literal tab of str : length=1UL <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< TEMPORARY
	tab* t = Tab__new(1UL, NULL);
	tab_str__indexAssign(t, 0UL, elem1);
	return t;
}
tab* Tab__new_2(str* elem1, str* elem2) { //intermediate to declare literal tab of str : length=2UL <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< TEMPORARY
	tab* t = Tab__new(2UL, NULL);
	tab_str__indexAssign(t, 0UL, elem1);
	tab_str__indexAssign(t, 1UL, elem2);
	return t;
}
tab* Tab__new_3(str* elem1, str* elem2, str* elem3) { //intermediate to declare literal tab of str : length=3UL <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< TEMPORARY
	tab* t = Tab__new(3UL, NULL);
	tab_str__indexAssign(t, 0UL, elem1);
	tab_str__indexAssign(t, 1UL, elem2);
	tab_str__indexAssign(t, 2UL, elem3);
	return t;
}
boo Oiam__chr_str(chr a, str* b) {
	for(ulng c=0ULL; c < b->length; c++) {
		if(a == str__index(b, c)) { return true; }
	}
	return false;
}

//indexed strings
typedef struct {
	str* s;
	ulng index;
} istr;
/*istr* IStr__new(ulng length) { //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< NOT USED YET
	istr* i  = malloc(sizeof(istr));
	i->s     = Str__new(length);
	i->index = -1LL;
	return i;
}*/
istr* IStr__fromStr(str* s) {
	istr* i  = malloc(sizeof(istr));
	i->s     = s;
	i->index = -1LL;
	return i;
}
void istr__free(istr* i) { free(i); }
boo istr__forward(istr* i, ulng step) {
	if((i->index + step) >= i->s->length) { return true; } //could not forward => ret true
	i->index += step;
	return false;
}
boo istr__inc(istr* i) { return istr__forward(i, 1ULL); }
chr istr__get(istr* i) {
	return i->s->data[i->index];
}
/*void istr__set(istr* i, chr value) { //<<<<<<<<<<<<<<<<<<<<< NOT USED YET
	i->s->data[i->index] = value;
}*/






// ---------------- IO ----------------

//definitions
chr  IO__MODE_READ[]  = "r";
chr  IO__MODE_WRITE[] = "w";
ulng IO__SEEK__BEG = 0ULL;
ulng IO__SEEK__CUR = 1ULL;
ulng IO__SEEK__END = 2ULL;
int IO__EOF = -1;
typedef struct {
	ulng  length;
	FILE* c_ptr;
} IO__file;

//functions
void IO__printChr(chr c) {
	putchar(c);
}
void IO__print(str* s) {
	for(ulng i=0UL; i < s->length; i++) {
		IO__printChr(str__index(s,i));
	}
}
void IO__printLF(str* s) {
	IO__print(s);
	IO__printChr('\n');
}
ulng IO__file__index(IO__file* f) {
	return ftell(f->c_ptr);
}
void IO__file__seek(IO__file* f, ulng offset, ulng ref) {
	fseek(f->c_ptr, offset, ref);
}
ulng IO__file__calculateLength(IO__file* f, boo fromBeginning) {
	ulng firstPos;
	if(fromBeginning){ firstPos = 0ULL;               }
	else             { firstPos = IO__file__index(f); }
	IO__file__seek(f, 0ULL, IO__SEEK__END);
	ulng lastPos = IO__file__index(f);
	IO__file__seek(f, firstPos, IO__SEEK__BEG);
	f->length = lastPos;
	return lastPos - firstPos;
}
IO__file* IO__open(str* path, chr* mode) {
	chr* cpath = str__toCtxt(path);
	IO__file* f = malloc(sizeof(IO__file));
	f->c_ptr = fopen(cpath, mode);
	IO__file__calculateLength(f, true);
	return f;
}
int IO__file__readChr(IO__file* f) {
	return fgetc(f->c_ptr);
}
str* IO__file__readUntil(IO__file* f, int end) {
	str* biggestResult = Str__new(f->length);
	ulng c=0ULL;
	while(c < f->length) {
		int i = IO__file__readChr(f);
		if(i == IO__EOF || i == (int)end) {
			break;
		}
		str__indexAssign(biggestResult, c, (chr)i);
		c++;
	}
	if(c == f->length) { return biggestResult; }
	str* cutResult = str__sub(biggestResult, 0UL, c-1UL); //file allows to read less bytes than expected
	str__free(biggestResult);
	return cutResult;
}
str* IO__file__read(IO__file* f) {
	return IO__file__readUntil(f, IO__EOF);
}
void IO__file__writeChr(IO__file* f, chr c) {
	fputc(c, f->c_ptr);
}
void IO__file__write(IO__file* f, str* text) {
	for(ulng c=0UL; c <  text->length; c++) { IO__file__writeChr(f, str__index(text,c)); }
}
void IO__file__close(IO__file* f) {
	fclose(f->c_ptr);
}
str* IO__readFile(str* path) {
	IO__file* f = IO__open(path, IO__MODE_READ);
	str*  s = IO__file__read(f);
	IO__file__close(f);
	return s;
}
void IO__writeFile(str* path, str* text) {
	IO__file* f = IO__open(path, IO__MODE_WRITE);
	IO__file__write(f, text);
	IO__file__close(f);
}
//void IO__file__flush(IO__file* f) {
//	fflush(f->c_ptr);
//}

//ctx print shortcuts <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< TEMPORARY
void IO__ctxt__print(chr* c) {
	str* s = ctxt__toStr(c);
	IO__print(s);
	free(s);
}
void IO__ctxt__printLF(chr* c) {
	str* s = ctxt__toStr(c);
	IO__printLF(s);
	free(s);
}

/*//dynamic memory buffer
typedef struct {
	IO__file* metadata;
	ubyt*     addr;
} dmb;

//module
dmb* Dmb__new() {
	dmb* d = malloc(sizeof(dmb));
	d->metadata        = malloc(sizeof(IO__file));
	d->metadata->c_ptr = open_memstream(&(d->addr), &(d->metadata->length));
	return d;
}

void dmb__flush(dmb* d) {
	IO__file__flush(d->metadata);
}*/






// ---------------- ERRORS ----------------

//definitions
const ubyt Err__SUCCESS = '\x00';
const ubyt Err__FAILURE = '\x01';
str Err__DEBUG_HEADER = { 10, "[ DEBUG ] " };
str Err__WARNN_HEADER = { 10, "[WARNING] " };
str Err__ERROR_HEADER = { 10, "[ ERROR ] " };
#define Err__DEBUG

//functions
void Err__debug(str* msg) {
	#ifdef Err__DEBUG
	IO__print(&Err__DEBUG_HEADER);
	IO__printLF(msg);
	#endif
}
void Err__warning(str* msg) {
	IO__print(&Err__WARNN_HEADER);
	IO__printLF(msg);
}
void Err__error(str* msg, ubyt err) {
	IO__print(&Err__ERROR_HEADER);
	IO__printLF(msg);
	Syscall__exit(err);
}






// ---------------- ARGS ----------------

//definitions
typedef struct {
	chr  short_name;
	str* long_name;
	boo  textRequired;
	str* value;
	tab* description;
} opt;
opt* Opt__new(chr short_name, str* long_name, boo textRequired, tab* description) {
	opt* o = malloc(sizeof(opt));
	o->short_name   = short_name;
	o->long_name    = long_name;
	o->textRequired = textRequired;
	o->value        = NULL;
	o->description  = description;
	return o;
}
opt* tab_opt__index(tab* t, ulng index) {
	return (opt*)tab_ptr_byt__index(t, index);
}
void tab_opt__indexAssign(tab* t, ulng index, opt* value) {
	tab_ptr_byt__indexAssign(t, index, (byt*)value);
}
boo opt__enabled(opt* o) {
	return (boo)(ulng)(o->value);
}

//functions
void Arg__detectedOption(opt* o, tab* args, ulng* argIndex) {

	//value will be set into o->value or EXIT PROGRAM
	if(o->textRequired){
		argIndex[0]++;

		//error cases
		if(argIndex[0] >= args->length) {
			Err__error( str__add(str__add(s("Option '--"), o->long_name), s("' requires a value (nothing given).")), Err__FAILURE);
		}
		if(str__index(tab_str__index(args, argIndex[0]),0) == '-') {
			Err__error( str__add(str__add(s("Option '--"), o->long_name), s("' requires a value (another option given).")), Err__FAILURE);
		}

		//store given value
		o->value = tab_str__index(args, argIndex[0]);
		return;
	}

	//no value has been set; however, option is enabled
	o->value = (str*)(ulng)true;
}
void Arg__parse(tab* args, tab* opts) {
	lst* realArgs        = Lst__new();
	ulng realArgs_length = 0UL;

	//for each argument
	for(ulng argIndex=1UL; argIndex < args->length; argIndex++){
		str* a = tab_str__index(args, argIndex);

		//look for matching option
		if(str__index(a,0) == '-'){

			//special case: lonely '-'
			if(a->length == 1UL) { Err__error(s("Missing argument name to lonely '-'."), 1); }
			boo foundMatching = false;

			//long options
			if(str__index(a,1) == '-') {
				str* cutArg = str__sub(a, 2, -1); //cutting starting "--"

				//for each option
				for(ulng optIndex=0UL; optIndex < opts->length; optIndex++){
					opt* o = tab_opt__index(opts, optIndex);

					//matching
					if(str__equal(cutArg, o->long_name)) {
						Arg__detectedOption(o, args, &argIndex);
						foundMatching = true;
						break;
					}
				}
			}

			//short options
			else {
				for(ulng optIndex=0UL; optIndex < opts->length; optIndex++){
					opt* o = tab_opt__index(opts, optIndex);

					//matching
					if(str__index(a,1) == o->short_name) {
						Arg__detectedOption(o, args, &argIndex);
						foundMatching = true;
						break;
					}
				}
			}

			//no matching option found
			if(!foundMatching) {
				Err__error(
					str__add(str__add( s("Undefined option '"), a), s("'.\n")),
					1
				);
			}
		}

		//not an option => real argument
		else {
			lst__append(realArgs, (byt*)a);
			realArgs_length++;
		}
	}

	//free original "args" elements (disabled if argc,argv are allocated out of heap)
	//tab__freeData(args);
	//free(args->data);

	//set a table of real arguments instead
	args->length = realArgs_length;
	args->data   = malloc(realArgs_length * sizeof(byt*));
	for(ulng i=0UL; i < realArgs_length; i++) {
		tab_str__indexAssign(
			args, i,
			(str*)lst__index(realArgs, i)
		);
	}
	lst__free(realArgs, false);
}
void Opt__printUsage(tab* opts) {

	//get longest option name
	ulng longestOptLength = 0UL;
	for(ulng optIndex=0UL; optIndex < opts->length; optIndex++) {
		opt* o = tab_opt__index(opts, optIndex);
		if((o->long_name)->length > longestOptLength) {
			longestOptLength = (o->long_name)->length;
		}
	}

	//multiple description lines : description padding
	str* descriptionPadding = Str__new(longestOptLength + 15);
	for(ulng s=0UL; s < descriptionPadding->length; s++) { str__indexAssign(descriptionPadding, s, ' '); }

	//prepare output
	str* output = s("Options:\n");
	for(ulng optIndex=0UL; optIndex < opts->length; optIndex++) {
		opt* o = tab_opt__index(opts, optIndex);

		//classic option header
		output = str__add(
			output,
			str__add(
				str__add(
					str__addChr(s("\n  -"), o->short_name),
					s(", --")
				),
				o->long_name
			)
		);

		//required argument or nothing
		if(o->textRequired) {
			output = str__add(output, s(" <"));
			output = str__addChr(output, o->short_name);
			output = str__add(output, s("> "));
		} else {
			output = str__add(output, s("     "));
		}

		//header padding
		ulng headerPaddingLength = longestOptLength - (o->long_name)->length;
		if(headerPaddingLength > 0UL) {
			str* headerPadding = Str__new(headerPaddingLength);
			for(ulng s=0UL; s < headerPaddingLength; s++) { str__indexAssign(headerPadding, s, ' '); }
			output = str__add(output, headerPadding);
			str__free(headerPadding);
		}
		output = str__add(output, s(": "));

		//description lines
		ulng d = 0UL;
		while(true){
			output = str__add(output, tab_str__index(o->description, d));
			output = str__addChr(output, '\n');
			d++;

			//print custom padding for next line
			if(d >= (o->description)->length) { break; } //no more lines => stop here
			output = str__add(output, descriptionPadding);
		}
	}
	str__free(descriptionPadding);

	//print result
	IO__print(output);
}






// ---------------- PATH ----------------

//functions
str* Path__name(str* path) {
	ulng lastDotIndex = str__findLastChr(path, '.');
	if(lastDotIndex == (ulng)-1L) { return path; }
	return str__sub(path, 0, lastDotIndex-1UL);
}
boo Path__isDir(str* path) { //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< TODO
	return true;
}
boo Path__isFile(str* path) { //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< TODO
	return true;
}
void Path__errorIfNotDir(str* path, byt err) {
	if(!Path__isDir(path)){
		Err__error(
			str__add(str__add(s("Path '"), path), s("' is not a directory.")),
			err
		);
	}
}
void Path__errorIfNotFile(str* path, byt err) {
	if(!Path__isFile(path)){
		Err__error(
			str__add(str__add(s("Path '"), path), s("' is not a file.")),
			err
		);
	}
}






// ---------------- CONVERSIONS ----------------

//unsigned -> str
chr ubyt__lastHexDigit(ubyt u) {
	if(u < '\x0a') { return '0' + u; }
	return 'a' + u - '\x0a';
}
str* ulng__toStr(ulng u) {
	str* result;

	//separate digits
	ulng rest          = u;
	ulng tenPowJ_digit = rest / 10000000000000000000ULL;
	rest -= 10000000000000000000ULL * tenPowJ_digit;

	ulng tenPowI_digit = rest / 1000000000000000000ULL;
	rest -= 1000000000000000000ULL * tenPowI_digit;

	ulng tenPowH_digit = rest / 100000000000000000ULL;
	rest -= 100000000000000000ULL * tenPowH_digit;

	ulng tenPowG_digit = rest / 10000000000000000ULL;
	rest -= 10000000000000000ULL * tenPowG_digit;

	ulng tenPowF_digit = rest / 1000000000000000ULL;
	rest -= 1000000000000000ULL * tenPowF_digit;

	ulng tenPowE_digit = rest / 100000000000000ULL;
	rest -= 100000000000000ULL * tenPowE_digit;

	ulng tenPowD_digit = rest / 10000000000000ULL;
	rest -= 10000000000000ULL * tenPowD_digit;

	ulng tenPowC_digit = rest / 1000000000000ULL;
	rest -= 1000000000000ULL * tenPowC_digit;

	ulng tenPowB_digit = rest / 100000000000ULL;
	rest -= 100000000000ULL * tenPowB_digit;

	ulng tenPowA_digit = rest / 10000000000ULL;
	rest -= 10000000000ULL * tenPowA_digit;

	ulng tenPow9_digit = rest / 1000000000ULL;
	rest -= 1000000000ULL * tenPow9_digit;

	ulng tenPow8_digit = rest / 100000000ULL;
	rest -= 100000000ULL * tenPow8_digit;

	ulng tenPow7_digit = rest / 10000000ULL;
	rest -= 10000000ULL * tenPow7_digit;

	ulng tenPow6_digit = rest / 1000000ULL;
	rest -= 1000000ULL * tenPow6_digit;

	ulng tenPow5_digit = rest / 100000ULL;
	rest -= 100000ULL * tenPow5_digit;

	ulng tenPow4_digit = rest / 10000ULL;
	rest -= 10000ULL * tenPow4_digit;

	ulng tenPow3_digit = rest / 1000ULL;
	rest -= 1000ULL * tenPow3_digit;

	ulng tenPow2_digit = rest / 100ULL;
	rest -= 100ULL * tenPow2_digit;

	ulng tenPow1_digit = rest / 10ULL;
	rest -= 10ULL * tenPow1_digit;

	//write in string
	if(tenPowJ_digit){
		result = Str__new(20LL);
		str__indexAssign(result,  0LL, ubyt__lastHexDigit(tenPowJ_digit));
		str__indexAssign(result,  1LL, ubyt__lastHexDigit(tenPowI_digit));
		str__indexAssign(result,  2LL, ubyt__lastHexDigit(tenPowH_digit));
		str__indexAssign(result,  3LL, ubyt__lastHexDigit(tenPowG_digit));
		str__indexAssign(result,  4LL, ubyt__lastHexDigit(tenPowF_digit));
		str__indexAssign(result,  5LL, ubyt__lastHexDigit(tenPowE_digit));
		str__indexAssign(result,  6LL, ubyt__lastHexDigit(tenPowD_digit));
		str__indexAssign(result,  7LL, ubyt__lastHexDigit(tenPowC_digit));
		str__indexAssign(result,  8LL, ubyt__lastHexDigit(tenPowB_digit));
		str__indexAssign(result,  9LL, ubyt__lastHexDigit(tenPowA_digit));
		str__indexAssign(result, 10LL, ubyt__lastHexDigit(tenPow9_digit));
		str__indexAssign(result, 11LL, ubyt__lastHexDigit(tenPow8_digit));
		str__indexAssign(result, 12LL, ubyt__lastHexDigit(tenPow7_digit));
		str__indexAssign(result, 13LL, ubyt__lastHexDigit(tenPow6_digit));
		str__indexAssign(result, 14LL, ubyt__lastHexDigit(tenPow5_digit));
		str__indexAssign(result, 15LL, ubyt__lastHexDigit(tenPow4_digit));
		str__indexAssign(result, 16LL, ubyt__lastHexDigit(tenPow3_digit));
		str__indexAssign(result, 17LL, ubyt__lastHexDigit(tenPow2_digit));
		str__indexAssign(result, 18LL, ubyt__lastHexDigit(tenPow1_digit));
		str__indexAssign(result, 19LL, ubyt__lastHexDigit(rest));
	} else if(tenPowI_digit){
		result = Str__new(19LL);
		str__indexAssign(result,  0LL, ubyt__lastHexDigit(tenPowI_digit));
		str__indexAssign(result,  1LL, ubyt__lastHexDigit(tenPowH_digit));
		str__indexAssign(result,  2LL, ubyt__lastHexDigit(tenPowG_digit));
		str__indexAssign(result,  3LL, ubyt__lastHexDigit(tenPowF_digit));
		str__indexAssign(result,  4LL, ubyt__lastHexDigit(tenPowE_digit));
		str__indexAssign(result,  5LL, ubyt__lastHexDigit(tenPowD_digit));
		str__indexAssign(result,  6LL, ubyt__lastHexDigit(tenPowC_digit));
		str__indexAssign(result,  7LL, ubyt__lastHexDigit(tenPowB_digit));
		str__indexAssign(result,  8LL, ubyt__lastHexDigit(tenPowA_digit));
		str__indexAssign(result,  9LL, ubyt__lastHexDigit(tenPow9_digit));
		str__indexAssign(result, 10LL, ubyt__lastHexDigit(tenPow8_digit));
		str__indexAssign(result, 11LL, ubyt__lastHexDigit(tenPow7_digit));
		str__indexAssign(result, 12LL, ubyt__lastHexDigit(tenPow6_digit));
		str__indexAssign(result, 13LL, ubyt__lastHexDigit(tenPow5_digit));
		str__indexAssign(result, 14LL, ubyt__lastHexDigit(tenPow4_digit));
		str__indexAssign(result, 15LL, ubyt__lastHexDigit(tenPow3_digit));
		str__indexAssign(result, 16LL, ubyt__lastHexDigit(tenPow2_digit));
		str__indexAssign(result, 17LL, ubyt__lastHexDigit(tenPow1_digit));
		str__indexAssign(result, 18LL, ubyt__lastHexDigit(rest));
	} else if(tenPowH_digit){
		result = Str__new(18LL);
		str__indexAssign(result,  0LL, ubyt__lastHexDigit(tenPowH_digit));
		str__indexAssign(result,  1LL, ubyt__lastHexDigit(tenPowG_digit));
		str__indexAssign(result,  2LL, ubyt__lastHexDigit(tenPowF_digit));
		str__indexAssign(result,  3LL, ubyt__lastHexDigit(tenPowE_digit));
		str__indexAssign(result,  4LL, ubyt__lastHexDigit(tenPowD_digit));
		str__indexAssign(result,  5LL, ubyt__lastHexDigit(tenPowC_digit));
		str__indexAssign(result,  6LL, ubyt__lastHexDigit(tenPowB_digit));
		str__indexAssign(result,  7LL, ubyt__lastHexDigit(tenPowA_digit));
		str__indexAssign(result,  8LL, ubyt__lastHexDigit(tenPow9_digit));
		str__indexAssign(result,  9LL, ubyt__lastHexDigit(tenPow8_digit));
		str__indexAssign(result, 10LL, ubyt__lastHexDigit(tenPow7_digit));
		str__indexAssign(result, 11LL, ubyt__lastHexDigit(tenPow6_digit));
		str__indexAssign(result, 12LL, ubyt__lastHexDigit(tenPow5_digit));
		str__indexAssign(result, 13LL, ubyt__lastHexDigit(tenPow4_digit));
		str__indexAssign(result, 14LL, ubyt__lastHexDigit(tenPow3_digit));
		str__indexAssign(result, 15LL, ubyt__lastHexDigit(tenPow2_digit));
		str__indexAssign(result, 16LL, ubyt__lastHexDigit(tenPow1_digit));
		str__indexAssign(result, 17LL, ubyt__lastHexDigit(rest));
	} else if(tenPowG_digit){
		result = Str__new(17LL);
		str__indexAssign(result,  0LL, ubyt__lastHexDigit(tenPowG_digit));
		str__indexAssign(result,  1LL, ubyt__lastHexDigit(tenPowF_digit));
		str__indexAssign(result,  2LL, ubyt__lastHexDigit(tenPowE_digit));
		str__indexAssign(result,  3LL, ubyt__lastHexDigit(tenPowD_digit));
		str__indexAssign(result,  4LL, ubyt__lastHexDigit(tenPowC_digit));
		str__indexAssign(result,  5LL, ubyt__lastHexDigit(tenPowB_digit));
		str__indexAssign(result,  6LL, ubyt__lastHexDigit(tenPowA_digit));
		str__indexAssign(result,  7LL, ubyt__lastHexDigit(tenPow9_digit));
		str__indexAssign(result,  8LL, ubyt__lastHexDigit(tenPow8_digit));
		str__indexAssign(result,  9LL, ubyt__lastHexDigit(tenPow7_digit));
		str__indexAssign(result, 10LL, ubyt__lastHexDigit(tenPow6_digit));
		str__indexAssign(result, 11LL, ubyt__lastHexDigit(tenPow5_digit));
		str__indexAssign(result, 12LL, ubyt__lastHexDigit(tenPow4_digit));
		str__indexAssign(result, 13LL, ubyt__lastHexDigit(tenPow3_digit));
		str__indexAssign(result, 14LL, ubyt__lastHexDigit(tenPow2_digit));
		str__indexAssign(result, 15LL, ubyt__lastHexDigit(tenPow1_digit));
		str__indexAssign(result, 16LL, ubyt__lastHexDigit(rest));
	} else if(tenPowF_digit){
		result = Str__new(16LL);
		str__indexAssign(result,  0LL, ubyt__lastHexDigit(tenPowF_digit));
		str__indexAssign(result,  1LL, ubyt__lastHexDigit(tenPowE_digit));
		str__indexAssign(result,  2LL, ubyt__lastHexDigit(tenPowD_digit));
		str__indexAssign(result,  3LL, ubyt__lastHexDigit(tenPowC_digit));
		str__indexAssign(result,  4LL, ubyt__lastHexDigit(tenPowB_digit));
		str__indexAssign(result,  5LL, ubyt__lastHexDigit(tenPowA_digit));
		str__indexAssign(result,  6LL, ubyt__lastHexDigit(tenPow9_digit));
		str__indexAssign(result,  7LL, ubyt__lastHexDigit(tenPow8_digit));
		str__indexAssign(result,  8LL, ubyt__lastHexDigit(tenPow7_digit));
		str__indexAssign(result,  9LL, ubyt__lastHexDigit(tenPow6_digit));
		str__indexAssign(result, 10LL, ubyt__lastHexDigit(tenPow5_digit));
		str__indexAssign(result, 11LL, ubyt__lastHexDigit(tenPow4_digit));
		str__indexAssign(result, 12LL, ubyt__lastHexDigit(tenPow3_digit));
		str__indexAssign(result, 13LL, ubyt__lastHexDigit(tenPow2_digit));
		str__indexAssign(result, 14LL, ubyt__lastHexDigit(tenPow1_digit));
		str__indexAssign(result, 15LL, ubyt__lastHexDigit(rest));
	} else if(tenPowE_digit){
		result = Str__new(15LL);
		str__indexAssign(result,  0LL, ubyt__lastHexDigit(tenPowE_digit));
		str__indexAssign(result,  1LL, ubyt__lastHexDigit(tenPowD_digit));
		str__indexAssign(result,  2LL, ubyt__lastHexDigit(tenPowC_digit));
		str__indexAssign(result,  3LL, ubyt__lastHexDigit(tenPowB_digit));
		str__indexAssign(result,  4LL, ubyt__lastHexDigit(tenPowA_digit));
		str__indexAssign(result,  5LL, ubyt__lastHexDigit(tenPow9_digit));
		str__indexAssign(result,  6LL, ubyt__lastHexDigit(tenPow8_digit));
		str__indexAssign(result,  7LL, ubyt__lastHexDigit(tenPow7_digit));
		str__indexAssign(result,  8LL, ubyt__lastHexDigit(tenPow6_digit));
		str__indexAssign(result,  9LL, ubyt__lastHexDigit(tenPow5_digit));
		str__indexAssign(result, 10LL, ubyt__lastHexDigit(tenPow4_digit));
		str__indexAssign(result, 11LL, ubyt__lastHexDigit(tenPow3_digit));
		str__indexAssign(result, 12LL, ubyt__lastHexDigit(tenPow2_digit));
		str__indexAssign(result, 13LL, ubyt__lastHexDigit(tenPow1_digit));
		str__indexAssign(result, 14LL, ubyt__lastHexDigit(rest));
	} else if(tenPowD_digit){
		result = Str__new(14LL);
		str__indexAssign(result,  0LL, ubyt__lastHexDigit(tenPowD_digit));
		str__indexAssign(result,  1LL, ubyt__lastHexDigit(tenPowC_digit));
		str__indexAssign(result,  2LL, ubyt__lastHexDigit(tenPowB_digit));
		str__indexAssign(result,  3LL, ubyt__lastHexDigit(tenPowA_digit));
		str__indexAssign(result,  4LL, ubyt__lastHexDigit(tenPow9_digit));
		str__indexAssign(result,  5LL, ubyt__lastHexDigit(tenPow8_digit));
		str__indexAssign(result,  6LL, ubyt__lastHexDigit(tenPow7_digit));
		str__indexAssign(result,  7LL, ubyt__lastHexDigit(tenPow6_digit));
		str__indexAssign(result,  8LL, ubyt__lastHexDigit(tenPow5_digit));
		str__indexAssign(result,  9LL, ubyt__lastHexDigit(tenPow4_digit));
		str__indexAssign(result, 10LL, ubyt__lastHexDigit(tenPow3_digit));
		str__indexAssign(result, 11LL, ubyt__lastHexDigit(tenPow2_digit));
		str__indexAssign(result, 12LL, ubyt__lastHexDigit(tenPow1_digit));
		str__indexAssign(result, 13LL, ubyt__lastHexDigit(rest));
	} else if(tenPowC_digit){
		result = Str__new(13LL);
		str__indexAssign(result,  0LL, ubyt__lastHexDigit(tenPowC_digit));
		str__indexAssign(result,  1LL, ubyt__lastHexDigit(tenPowB_digit));
		str__indexAssign(result,  2LL, ubyt__lastHexDigit(tenPowA_digit));
		str__indexAssign(result,  3LL, ubyt__lastHexDigit(tenPow9_digit));
		str__indexAssign(result,  4LL, ubyt__lastHexDigit(tenPow8_digit));
		str__indexAssign(result,  5LL, ubyt__lastHexDigit(tenPow7_digit));
		str__indexAssign(result,  6LL, ubyt__lastHexDigit(tenPow6_digit));
		str__indexAssign(result,  7LL, ubyt__lastHexDigit(tenPow5_digit));
		str__indexAssign(result,  8LL, ubyt__lastHexDigit(tenPow4_digit));
		str__indexAssign(result,  9LL, ubyt__lastHexDigit(tenPow3_digit));
		str__indexAssign(result, 10LL, ubyt__lastHexDigit(tenPow2_digit));
		str__indexAssign(result, 11LL, ubyt__lastHexDigit(tenPow1_digit));
		str__indexAssign(result, 12LL, ubyt__lastHexDigit(rest));
	} else if(tenPowB_digit){
		result = Str__new(12LL);
		str__indexAssign(result,  0LL, ubyt__lastHexDigit(tenPowB_digit));
		str__indexAssign(result,  1LL, ubyt__lastHexDigit(tenPowA_digit));
		str__indexAssign(result,  2LL, ubyt__lastHexDigit(tenPow9_digit));
		str__indexAssign(result,  3LL, ubyt__lastHexDigit(tenPow8_digit));
		str__indexAssign(result,  4LL, ubyt__lastHexDigit(tenPow7_digit));
		str__indexAssign(result,  5LL, ubyt__lastHexDigit(tenPow6_digit));
		str__indexAssign(result,  6LL, ubyt__lastHexDigit(tenPow5_digit));
		str__indexAssign(result,  7LL, ubyt__lastHexDigit(tenPow4_digit));
		str__indexAssign(result,  8LL, ubyt__lastHexDigit(tenPow3_digit));
		str__indexAssign(result,  9LL, ubyt__lastHexDigit(tenPow2_digit));
		str__indexAssign(result, 10LL, ubyt__lastHexDigit(tenPow1_digit));
		str__indexAssign(result, 11LL, ubyt__lastHexDigit(rest));
	} else if(tenPowA_digit){
		result = Str__new(11LL);
		str__indexAssign(result,  0LL, ubyt__lastHexDigit(tenPowA_digit));
		str__indexAssign(result,  1LL, ubyt__lastHexDigit(tenPow9_digit));
		str__indexAssign(result,  2LL, ubyt__lastHexDigit(tenPow8_digit));
		str__indexAssign(result,  3LL, ubyt__lastHexDigit(tenPow7_digit));
		str__indexAssign(result,  4LL, ubyt__lastHexDigit(tenPow6_digit));
		str__indexAssign(result,  5LL, ubyt__lastHexDigit(tenPow5_digit));
		str__indexAssign(result,  6LL, ubyt__lastHexDigit(tenPow4_digit));
		str__indexAssign(result,  7LL, ubyt__lastHexDigit(tenPow3_digit));
		str__indexAssign(result,  8LL, ubyt__lastHexDigit(tenPow2_digit));
		str__indexAssign(result,  9LL, ubyt__lastHexDigit(tenPow1_digit));
		str__indexAssign(result, 10LL, ubyt__lastHexDigit(rest));
	} else if(tenPow9_digit){
		result = Str__new(10LL);
		str__indexAssign(result, 0LL, ubyt__lastHexDigit(tenPow9_digit));
		str__indexAssign(result, 1LL, ubyt__lastHexDigit(tenPow8_digit));
		str__indexAssign(result, 2LL, ubyt__lastHexDigit(tenPow7_digit));
		str__indexAssign(result, 3LL, ubyt__lastHexDigit(tenPow6_digit));
		str__indexAssign(result, 4LL, ubyt__lastHexDigit(tenPow5_digit));
		str__indexAssign(result, 5LL, ubyt__lastHexDigit(tenPow4_digit));
		str__indexAssign(result, 6LL, ubyt__lastHexDigit(tenPow3_digit));
		str__indexAssign(result, 7LL, ubyt__lastHexDigit(tenPow2_digit));
		str__indexAssign(result, 8LL, ubyt__lastHexDigit(tenPow1_digit));
		str__indexAssign(result, 9LL, ubyt__lastHexDigit(rest));
	} else if(tenPow8_digit){
		result = Str__new(9LL);
		str__indexAssign(result, 0LL, ubyt__lastHexDigit(tenPow8_digit));
		str__indexAssign(result, 1LL, ubyt__lastHexDigit(tenPow7_digit));
		str__indexAssign(result, 2LL, ubyt__lastHexDigit(tenPow6_digit));
		str__indexAssign(result, 3LL, ubyt__lastHexDigit(tenPow5_digit));
		str__indexAssign(result, 4LL, ubyt__lastHexDigit(tenPow4_digit));
		str__indexAssign(result, 5LL, ubyt__lastHexDigit(tenPow3_digit));
		str__indexAssign(result, 6LL, ubyt__lastHexDigit(tenPow2_digit));
		str__indexAssign(result, 7LL, ubyt__lastHexDigit(tenPow1_digit));
		str__indexAssign(result, 8LL, ubyt__lastHexDigit(rest));
	} else if(tenPow7_digit){
		result = Str__new(8LL);
		str__indexAssign(result, 0LL, ubyt__lastHexDigit(tenPow7_digit));
		str__indexAssign(result, 1LL, ubyt__lastHexDigit(tenPow6_digit));
		str__indexAssign(result, 2LL, ubyt__lastHexDigit(tenPow5_digit));
		str__indexAssign(result, 3LL, ubyt__lastHexDigit(tenPow4_digit));
		str__indexAssign(result, 4LL, ubyt__lastHexDigit(tenPow3_digit));
		str__indexAssign(result, 5LL, ubyt__lastHexDigit(tenPow2_digit));
		str__indexAssign(result, 6LL, ubyt__lastHexDigit(tenPow1_digit));
		str__indexAssign(result, 7LL, ubyt__lastHexDigit(rest));
	} else if(tenPow6_digit){
		result = Str__new(7LL);
		str__indexAssign(result, 0LL, ubyt__lastHexDigit(tenPow6_digit));
		str__indexAssign(result, 1LL, ubyt__lastHexDigit(tenPow5_digit));
		str__indexAssign(result, 2LL, ubyt__lastHexDigit(tenPow4_digit));
		str__indexAssign(result, 3LL, ubyt__lastHexDigit(tenPow3_digit));
		str__indexAssign(result, 4LL, ubyt__lastHexDigit(tenPow2_digit));
		str__indexAssign(result, 5LL, ubyt__lastHexDigit(tenPow1_digit));
		str__indexAssign(result, 6LL, ubyt__lastHexDigit(rest));
	} else if(tenPow5_digit){
		result = Str__new(6LL);
		str__indexAssign(result, 0LL, ubyt__lastHexDigit(tenPow5_digit));
		str__indexAssign(result, 1LL, ubyt__lastHexDigit(tenPow4_digit));
		str__indexAssign(result, 2LL, ubyt__lastHexDigit(tenPow3_digit));
		str__indexAssign(result, 3LL, ubyt__lastHexDigit(tenPow2_digit));
		str__indexAssign(result, 4LL, ubyt__lastHexDigit(tenPow1_digit));
		str__indexAssign(result, 5LL, ubyt__lastHexDigit(rest));
	} else if(tenPow4_digit){
		result = Str__new(5LL);
		str__indexAssign(result, 0LL, ubyt__lastHexDigit(tenPow4_digit));
		str__indexAssign(result, 1LL, ubyt__lastHexDigit(tenPow3_digit));
		str__indexAssign(result, 2LL, ubyt__lastHexDigit(tenPow2_digit));
		str__indexAssign(result, 3LL, ubyt__lastHexDigit(tenPow1_digit));
		str__indexAssign(result, 4LL, ubyt__lastHexDigit(rest));
	} else if(tenPow3_digit){
		result = Str__new(4LL);
		str__indexAssign(result, 0LL, ubyt__lastHexDigit(tenPow3_digit));
		str__indexAssign(result, 1LL, ubyt__lastHexDigit(tenPow2_digit));
		str__indexAssign(result, 2LL, ubyt__lastHexDigit(tenPow1_digit));
		str__indexAssign(result, 3LL, ubyt__lastHexDigit(rest));
	} else if(tenPow2_digit){
		result = Str__new(3LL);
		str__indexAssign(result, 0LL, ubyt__lastHexDigit(tenPow2_digit));
		str__indexAssign(result, 1LL, ubyt__lastHexDigit(tenPow1_digit));
		str__indexAssign(result, 2LL, ubyt__lastHexDigit(rest));
	} else if(tenPow1_digit){
		result = Str__new(2LL);
		str__indexAssign(result, 0LL, ubyt__lastHexDigit(tenPow1_digit));
		str__indexAssign(result, 1LL, ubyt__lastHexDigit(rest));
	} else {
		result = Str__new(1LL);
		str__indexAssign(result, 0LL, ubyt__lastHexDigit(rest));
	}
	return result;
}




// ---------------- PARSING ----------------

//location
typedef struct {
	str*  filename;
	ulng  lineNbr;
	ulng  columnNbr;
	istr* icontent;
} Parsing__ctx;
Parsing__ctx* Parsing__Ctx__new(str* filename, str* content) {
	Parsing__ctx* ctx = malloc(sizeof(Parsing__ctx));
	ctx->filename  = filename;
	ctx->lineNbr   = 1ULL;
	ctx->columnNbr = 1ULL;
	ctx->icontent   = IStr__fromStr(content);
	return ctx;
}
chr Parsing__ctx__get(Parsing__ctx* ctx) { return istr__get(ctx->icontent); }
//void Parsing__ctx__set(Parsing__ctx* ctx, chr value) { istr__set(cxt->content, value); } //not used yet
boo Parsing__ctx__inc(Parsing__ctx* ctx) {
	if(istr__inc(ctx->icontent)) { return true; } //can't go further => can't go further

	//forward localization elements
	chr c = istr__get(ctx->icontent);
	if(c == '\n') { ctx->lineNbr++; ctx->columnNbr = 0ULL; } //new line
	else          {                 ctx->columnNbr++;      } //regular character
	return false;
}
void Parsing__ctx__free(Parsing__ctx* ctx) {
	istr__free(ctx->icontent);
	free(ctx);
}
str* Parsing__ctx__toStr(Parsing__ctx* ctx) {
	str* resultStr = str__addChr(ctx->filename, ':');

	//lineNbr
	str* lineNbrStr = ulng__toStr(ctx->lineNbr);
	resultStr = str__addSelf(resultStr, lineNbrStr);
	str__free(lineNbrStr);
	resultStr = str__addChrSelf(resultStr, ':');

	//columnNbr
	str* columnNbrStr = ulng__toStr(ctx->columnNbr);
	resultStr = str__addSelf(resultStr, columnNbrStr);
	str__free(columnNbrStr);
	return resultStr;
}
Parsing__ctx* Parsing__ctx__copy(Parsing__ctx* ctx) {
	Parsing__ctx* ctx2 = Parsing__Ctx__new(ctx->filename, ctx->icontent->s);
	ctx2->lineNbr         = ctx->lineNbr;
	ctx2->columnNbr       = ctx->columnNbr;
	ctx2->icontent->index = ctx->icontent->index;
	return ctx2;
}
