// ---------------- DEPENDENCIES ----------------

//memory
#include <stdlib.h> //malloc(), exit()

//output
#include <stdio.h> //putc()



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
	byt* data;
}

//methods
tab* tab__new(ulng length, byt* initialData) {
	tab* t  = malloc(sizeof(tab));
	t->data = malloc(length * sizeof(byt*));
	if(initialData != NULL) {
		for(ulng i=0UL; i < length; i++) {
			t->data[i] = initialData[i];
		}
	}
	return t;
}
byt* tab__index(uint index) {
	return t->data[index];
}






// ---------------- LISTS ----------------

//definitions
typedef struct {
	byt* next;
	byt* data;
} lst;

//methods
void lst__append(lst* l, byt* element) {
	lst* newItem = l;
	if(newItem != NULL) {
		newItem = newItem->next;
		while(newItem->next != NULL) { newItem = newItem->next; }
	}
	newItem = malloc(sizeof(lst));
	newItem->data = e;
	newItem->next = NULL;
}
byt* lst__index(lst* l, ulng index) {
	lst* current = l;
	for(ulng i=0UL; i < index; i++) {
		if(current == NULL) { return NULL; }
		current = current->next;
	}
	if(current == NULL) { return NULL; }
	return current->data;
}
byt* lst__last(lst* l) {
	if(l == NULL){ return NULL; }
	lst* last = l;
	while(last->next != NULL) { last = last->next; }
	return last->data;
}





// ---------------- TEXT ----------------

//definitions
typedef byt chr;
typedef struct {
	ulng length;
	chr* data;
} str;

//methods
str* str__new(chr* data) {
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
str* s(chr* data) { return str__new(data); } //just a shortcut
chr str__index(str* s, ulng index) {
	return s->data[index];
}
void str__indexAssign(str* s, ulng index, chr value) {
	s->data[index] = value;
}
str* str__sub(str* s, ulng firstIndex, ulng lastIndex) {
	if(lastIndex == (ulng)-1L) { //<=> -1L
		lastIndex = s->length;
	}
	if(firstIndex >= lastIndex) { return NULL; } //empty or out of possible scope
	ulng newLength = lastIndex - firstIndex + 1UL;
	if(newLength == s->length) { return s; } //nothing to operate
	str* newS = str__new(newLength, NULL);
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






// ---------------- IO ----------------

//functions
void IO__printChr(chr c) {
	putc(c);
}
void IO__print(str* s) {
	for(ulng i=0UL; i < s->length; i++) {
		IO__printChr(str__index(s,i));
	}
}
void IO__println(str* s) {
	IO__print(s);
	IO_printChr('\n');
}






// ---------------- ERRORS ----------------

//definitions
const ubyt Err__SUCCESS = '\x00';
const ubyt Err__FAILURE = '\x01';
const str  Err__DEBUG_HEADER = { 8, "[DEBUG] " };
const str  Err__WARNN_HEADER = { 8, "[WARNN] " };
const str  Err__ERROR_HEADER = { 8, "[ERROR] " };
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
	IO__print(msg);
}
void Err__error(str* msg, ubyt err) {
	IO__print(&Err__WARNN_HEADER);
	IO__print(msg);
	exit(err);
}






// ---------------- ARGS ----------------

//definitions
typedef struct {
	chr  short_name;
	str* long_name;
	boo  enabled;
	str* value;
} opt;

//functions
void Arg__detectedOption(opt* o, tab* args, ulng argIndex) {
}
void Arg__parse(tab* args, tab* opts) {

	//for each argument
	for(ulng argIndex=0UL; argIndex < args->length; argIndex++){
		str* a = tab__index(args, argIndex);

		//look for matching option
		if(str__index(a,0) == '-'){

			//special case: lonely '-'
			if(a->length == 1UL) {
				Err__error(s("Missing argument name to lonely '-'."), 1);
			}
			boo foundMatching = false;

			//long options
			if(str__index(a,1) == '-') {
				str* cutArg = str__sub(a, 2, -1); //cutting starting "--"

				//for each option
				for(ulng optIndex=0UL; optIndex < opts->length; optIndex++){
					opt* o = tab__index(opts, optIndex);

					//matching
					if(str__equal(cutArg, o->long_name)) {
						Arg__detectedOption(o, args, argIndex);
						foundMatching = true;
						break;
					}
				}
			}

			//short options
			else {
				str* cutArg = str__sub(a, 1, -1); //cutting starting "-"

				for(ulng optIndex=0UL; optIndex < opts->length; optIndex++){
					opt* o = tab__index(opts, optIndex);

					//matching
					if(str__equal(cutArg, o->short_name)) {
						Arg__detectedOption(o, args, argIndex);
						foundMatching = true;
						break;
					}
				}
			}

			//no matching option found
			if(!foundMatching) {
				Err__error(
					str__add( str__add(s("Undefined option '"), a), "'."),
					1
				);
			}
		}
	}
}
