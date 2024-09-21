// ---------------- DEPENDENCIES ----------------

//memory
#include <stdlib.h> //malloc(), free(), exit()

//output
#include <stdio.h> //putchar()



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
	str* s = malloc(sizeof(str));
	s->data   = malloc(length * sizeof(chr));
	s->length = length;
	return s;
}
str* s(chr* data) { //just a C related shortcut
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
str* tab_str__index(tab* t, ulng index) {
	return (str*)tab_ptr_byt__index(t, index);
}
void tab_str__indexAssign(tab* t, ulng index, str* value) {
	tab_ptr_byt__indexAssign(t, index, (byt*)value);
}






// ---------------- IO ----------------

//functions
void IO__printChr(chr c) {
	putchar(c);
}
void IO__print(str* s) {
	for(ulng i=0UL; i < s->length; i++) {
		IO__printChr(str__index(s,i));
	}
}
void IO__println(str* s) {
	IO__print(s);
	IO__printChr('\n');
}






// ---------------- ERRORS ----------------

//definitions
const ubyt Err__SUCCESS = '\x00';
const ubyt Err__FAILURE = '\x01';
str Err__DEBUG_HEADER = { 8, "[DEBUG] " };
str Err__WARNN_HEADER = { 8, "[WARNN] " };
str Err__ERROR_HEADER = { 8, "[ERROR] " };
#define Err__DEBUG

//functions
void Err__debug(str* msg) {
	#ifdef Err__DEBUG
	IO__print(&Err__DEBUG_HEADER);
	IO__println(msg);
	#endif
}
void Err__warning(str* msg) {
	IO__print(&Err__WARNN_HEADER);
	IO__println(msg);
}
void Err__error(str* msg, ubyt err) {
	IO__print(&Err__WARNN_HEADER);
	IO__println(msg);
	exit(err);
}






// ---------------- ARGS ----------------

//definitions
typedef struct {
	chr  short_name;
	str* long_name;
	boo  textRequired;
	str* value;
} opt;
opt* Opt__new(chr short_name, str* long_name, boo textRequired) {
	opt* o = malloc(sizeof(opt));
	o->short_name   = short_name;
	o->long_name    = long_name;
	o->textRequired = textRequired;
	o->value        = NULL;
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
