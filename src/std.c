// ---------------- DEPENDENCIES ----------------

//memory
#include <stdlib.h> //malloc(), free(), exit()

//output
#include <stdio.h> //putchar(), fopen(), fgetc(), fputc(), fclose(), fseek(), ftell(), open_memstream()






// ---------------- ROOTS ----------------

//precompiler/compiler options
#define GENERATE_TOSTR
#define DEBUG_AVAILABLE
#define INTERNAL_ERRORS
#define LOG_FILEPATH

//shortcut notations for types
typedef char      byt;
typedef short     shr;
typedef long long lng;

//unsigned
typedef unsigned char      ubyt;
typedef unsigned short     ushr;
typedef unsigned int       uint;
typedef unsigned long long ulng;

//now that we have "uint" declared
const uint ATOM__byt  = 0;
const uint ATOM__shr  = 1;
const uint ATOM__int  = 2;
const uint ATOM__lng  = 3;
const uint ATOM__ubyt = 4;
const uint ATOM__ushr = 5;
const uint ATOM__uint = 6;
const uint ATOM__ulng = 7;

//float
typedef float flt;
const uint ATOM__flt = 8;
typedef double dbl;
const uint ATOM__dbl = 9;

//booleans
typedef byt boo;
const uint ATOM__boo = 10;
const boo false = '\x00';
const boo true  = '\x01';

//pointers
typedef ubyt* ptr;
const uint ATOM__ptr = 11;






// ---------------- GENERATED AT COMPILE TIME : ATOMS ----------------

//atom structure
typedef struct {
	ubyt id;
	ptr  data;
} atm;

//atom constants
const uint ATOM__atm = -1;

//catch up root types toAtm()
atm* byt__toAtm(byt e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__byt;
	a->data = (ptr)e;
	return a;
}
atm* shr__toAtm(shr e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__shr;
	a->data = (ptr)e;
	return a;
}
atm* int__toAtm(int e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__int;
	a->data = (ptr)e;
	return a;
}
atm* lng__toAtm(lng e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__lng;
	a->data = (ptr)e;
	return a;
}
atm* ubyt__toAtm(ubyt e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__ubyt;
	a->data = (ptr)e;
	return a;
}
atm* ushr__toAtm(ushr e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__ushr;
	a->data = (ptr)e;
	return a;
}
atm* uint__toAtm(uint e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__uint;
	a->data = (ptr)e;
	return a;
}
atm* ulng__toAtm(ulng e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__ulng;
	a->data = (ptr)e;
	return a;
}
atm* flt__toAtm(flt e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__flt;
	a->data = (ptr)e;
	return a;
}
atm* dbl__toAtm(dbl e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__dbl;
	a->data = (ptr)e;
	return a;
}
atm* boo__toAtm(boo e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__boo;
	a->data = (ptr)e;
	return a;
}
atm* ptr__toAtm(ptr e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__ptr;
	a->data = (ptr)e;
	return a;
}






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

//type-related generated content : atoms
const uint ATOM__tab = 12;
atm* tab__toAtm(tab* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__tab;
	a->data = (ptr)e;
	return a;
}

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

//type-related generated content : atoms
const uint ATOM__lst_item = 13;
atm* lst_item__toAtm(lst_item* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__lst_item;
	a->data = (ptr)e;
	return a;
}

typedef struct {
	lst_item* firstItem;
} lst;

//type-related generated content : atoms
const uint ATOM__lst = 14;
atm* lst__toAtm(lst* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__lst;
	a->data = (ptr)e;
	return a;
}

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

//type-related generated content : atoms
const uint ATOM__chr = 15;
atm* chr__toAtm(chr e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__chr;
	a->data = (ptr)e;
	return a;
}
const uint ATOM__str = 16;
atm* str__toAtm(str* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__str;
	a->data = (ptr)e;
	return a;
}

//methods
str* Str__new(ulng length) {
	str* s    = malloc(sizeof(str));
	if(length == 0UL) { s->data = NULL;                         }
	else              { s->data = malloc(length * sizeof(chr)); }
	s->length = length;
	return s;
}
str* ctxt__toStr(chr* data) { //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< TEMPORARY
	str* s    = malloc(sizeof(str));
	s->data   = NULL;
	s->length = 0UL;
	if(data != NULL) {
		chr* dataInit = data;
		while(data[0] != '\0'){
			data++;
			s->length++;
		}
		s->data = malloc(s->length);
		for(ulng i=0; i < s->length; i++) { s->data[i] = dataInit[i]; }
	}
	return s;
}
void str__free(str* s){
	free(s->data);
	free(s);
}
chr str__index(str* s, ulng index) {
	return s->data[index];
}
void str__indexAssign(str* s, ulng index, chr value) {
	s->data[index] = value;
}
str* str__copy(str* s) {
	str* s2 = Str__new(s->length);
	for(ulng i=0ULL; i < s->length; i++) { str__indexAssign(s2, i, str__index(s, i)); }
	return s2;
}
void str__fill(str* s, chr c) {
	for(ulng i=0; i < s->length; i++) { str__indexAssign(s, i, c); }
}
str* str__sub(str* s, ulng firstIndex, ulng lastIndex) {
	if(lastIndex == (ulng)-1L) {
		lastIndex = s->length - 1UL;
	}
	if(firstIndex > lastIndex) { return NULL; } //empty or out of possible scope
	ulng newLength = lastIndex - firstIndex + 1UL;
	if(newLength == s->length) { return str__copy(s); } //nothing to operate
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
str* str__expandTabs(str* s, ulng expansionLength) {
	str* result = Str__new(s->length + (expansionLength-1LL) * str__countChr(s, '\t'));
	ulng extendedIndex    = 0ULL;
	for(ulng index=0ULL; index < s->length; index++) {
		chr c = str__index(s, index);
		if(c == '\t') {
			for(ulng d=0ULL; d < expansionLength; d++) {
				str__indexAssign(result, extendedIndex, ' ');
				extendedIndex++;
			}
		} else {
			str__indexAssign(result, extendedIndex, c);
			extendedIndex++;
		}
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






// ---------------- GENERATED AT COMPILE TIME : toStr ----------------

//toStr
// This part is not obvious, here are some rules/principles to know about toStr method generation :
//   - A compilation option enables or not those method generation.
//     An additionnal precompiler option can also be set to have specific behavior in sources depending on whether we have those methods or not, but this is completely optionnal.
//   - Types declared via type-copy does NOT generate a toStr() method (=> only root primitives + structures concerned)
//   - A second parameter "ulng depth=0xff..." (-1LL) is set in every method (as for every block, the compiler will get rid of unused parameters at compile time).
//   - These generated methods are overridable (if user defines one, it is used as is instead of being generated).
#ifdef  GENERATE_TOSTR
//str* atm__toStr(atm* e, ulng depth); //special generation for atoms : at end of code
str* ulng__toStr(ulng e) {
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
str* byt__toStr(byt e) {
	return ulng__toStr(e); //shortcut for here, but it must be defined completely in final version
}
str* shr__toStr(shr e) {
	return ulng__toStr(e); //shortcut for here, but it must be defined completely in final version
}
str* int__toStr(int e) {
	return ulng__toStr(e); //shortcut for here, but it must be defined completely in final version
}
str* lng__toStr(lng e) {
	return ulng__toStr(e); //shortcut for here, but it must be defined completely in final version
}
str* ubyt__toStr(ubyt e) {
	return ulng__toStr(e); //shortcut for here, but it must be defined completely in final version
}
str* ushr__toStr(ushr e) {
	return ulng__toStr(e); //shortcut for here, but it must be defined completely in final version
}
str* uint__toStr(uint e) {
	return ulng__toStr(e); //shortcut for here, but it must be defined completely in final version
}
str* ptr__toStr(ptr e) {
	str* n = ulng__toStr(e);        //shortcut for here, but it must be defined in HEX in final version
	str* result = ctxt__toStr("p");
	result = str__addSelf(result, n);
	str__free(n);
	return result;
}

//catching up each previously declared structure type
str* tab__toStr(tab* e, ulng depth) { //default generation
	str* result = Str__new(0ULL);
	str* BEGINNING = ctxt__toStr("tab{");
	result = str__addSelf(result, BEGINNING);
	str__free(BEGINNING);

	//prepare depth spacing
	boo hasDepth    = (depth != -1LL);
	str* depthSpace = NULL;
	if(hasDepth) {
		depthSpace = Str__new(depth);
		str__fill(depthSpace, '\t');
	}

	//field1 : length
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD1 = ctxt__toStr("length:"); //name
	result = str__addSelf(result, FIELD1);
	str__free(FIELD1);
	str* fieldValue = ulng__toStr(e->length); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//field2 : data
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD2 = ctxt__toStr("data:"); //name
	result = str__addSelf(result, FIELD2);
	str__free(FIELD2);
	fieldValue = ptr__toStr(e->data); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);

	//last spacing
	if(hasDepth) {
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
	}
	result = str__addChrSelf(result, '}');
	return result;
}
str* lst_item__toStr(lst_item* e, ulng depth) { //default generation
	str* result = Str__new(0ULL);
	str* BEGINNING = ctxt__toStr("lst_item{");
	result = str__addSelf(result, BEGINNING);
	str__free(BEGINNING);

	//prepare depth spacing
	boo hasDepth    = (depth != -1LL);
	str* depthSpace = NULL;
	if(hasDepth) {
		depthSpace = Str__new(depth);
		str__fill(depthSpace, '\t');
	}

	//field1 : next
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD1 = ctxt__toStr("next:"); //name
	result = str__addSelf(result, FIELD1);
	str__free(FIELD1);
	str* fieldValue = ptr__toStr(e->next); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//field2 : data
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD2 = ctxt__toStr("data:"); //name
	result = str__addSelf(result, FIELD2);
	str__free(FIELD2);
	fieldValue = ptr__toStr(e->data); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);

	//last spacing
	if(hasDepth) {
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
	}
	result = str__addChrSelf(result, '}');
	return result;
}
str* lst__toStr(lst* e, ulng depth) { //default generation
	str* result = Str__new(0ULL);
	str* BEGINNING = ctxt__toStr("lst{");
	result = str__addSelf(result, BEGINNING);
	str__free(BEGINNING);

	//prepare depth spacing
	boo hasDepth    = (depth != -1LL);
	str* depthSpace = NULL;
	if(hasDepth) {
		depthSpace = Str__new(depth);
		str__fill(depthSpace, '\t');
	}

	//field1 : firstItem
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD1 = ctxt__toStr("firstItem:"); //name
	result = str__addSelf(result, FIELD1);
	str__free(FIELD1);
	str* fieldValue = ulng__toStr(e->firstItem); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//last spacing
	if(hasDepth) {
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
	}
	result = str__addChrSelf(result, '}');
	return result;
}
/*str* str__toStr(str* e, ulng depth) { //default generation
	str* result = Str__new(0ULL);
	str* BEGINNING = ctxt__toStr("str{");
	result = str__addSelf(result, BEGINNING);
	str__free(BEGINNING);

	//prepare depth spacing
	boo hasDepth    = (depth != -1LL);
	str* depthSpace = NULL;
	if(hasDepth) {
		depthSpace = Str__new(depth);
		str__fill(depthSpace, '\t');
	}

	//field1 : length
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD1 = ctxt__toStr("length:"); //name
	result = str__addSelf(result, FIELD1);
	str__free(FIELD1);
	str* fieldValue = ulng__toStr(e->length); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//field2 : data
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD2 = ctxt__toStr("data:"); //name
	result = str__addSelf(result, FIELD2);
	str__free(FIELD2);
	fieldValue = ptr__toStr(e->data); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);

	//last spacing
	if(hasDepth) {
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
	}
	result = str__addChrSelf(result, '}');
	return result;
}*/
#endif






// ---------------- CUSTOM toStr OVERRIDES ----------------

//common
str* boo__toStr(boo e) { //not an override
	if(e) { return ctxt__toStr("true"); }
	return ctxt__toStr("false");
}
str* chr__toStr(chr e) { //not an override
	str* result = Str__new(3ULL);
	str__indexAssign(result, 0ULL, '\'');
	str__indexAssign(result, 1ULL, e);
	str__indexAssign(result, 2ULL, '\'');
	return result;
}
str* str__toStr(str* e) {
	str* result = Str__new(e->length + 2ULL);
	str__indexAssign(result, 0ULL,             '"');
	str__indexAssign(result, e->length + 1ULL, '"');
	for(ulng i=0ULL; i < e->length; i++) { str__indexAssign(result, i+1ULL, str__index(e, i)); }
	return result;
}
str* tab_str__toStr(tab* e, ulng depth) {
	str* result = ctxt__toStr("(");

	//prepare depth spacing
	boo hasDepth    = (depth != -1LL);
	str* depthSpace = NULL;
	if(hasDepth) {
		depthSpace = Str__new(depth);
		str__fill(depthSpace, '\t');
	}

	//for each element
	for(ulng i=0ULL; i < e->length; i++) {

		//spacing
		if(hasDepth) {
			result = str__addChrSelf(result, '\n');
			result = str__addSelf(result, depthSpace);
			result = str__addChrSelf(result, '\t');
		}

		//item
		str* itemValue = str__toStr(tab_str__index(e, i)); //data
		result = str__addSelf(result, itemValue);
		str__free(itemValue);
		result = str__addChrSelf(result, ',');
	}

	//last spacing
	if(hasDepth) {
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
	}
	result = str__addChrSelf(result, ')');
	return result;
}
str* lst_str__toStr(lst* e, ulng depth) {
	str* result = ctxt__toStr("[");

	//prepare depth spacing
	boo hasDepth    = (depth != -1LL);
	str* depthSpace = NULL;
	if(hasDepth) {
		depthSpace = Str__new(depth);
		str__fill(depthSpace, '\t');
	}

	//for each element
	for(ulng i=0ULL; i < e->length; i++) {

		//spacing
		if(hasDepth) {
			result = str__addChrSelf(result, '\n');
			result = str__addSelf(result, depthSpace);
			result = str__addChrSelf(result, '\t');
		}

		//item
		str* itemValue = str__toStr((str*)lst__index(e, i)); //data
		result = str__addSelf(result, itemValue);
		str__free(itemValue);
		result = str__addChrSelf(result, ',');
	}

	//last spacing
	if(hasDepth) {
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
	}
	result = str__addChrSelf(result, ']');
	return result;
}






// ---------------- INDEXED TEXT ----------------

//indexed strings
typedef struct {
	str* s;
	ulng index;
} istr;

//type-related generated content : atoms
const uint ATOM__istr = 17;
atm* istr__toAtm(istr* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__istr;
	a->data = (ptr)e;
	return a;
}

//type-related generated content : toStr
str* istr__toStr(istr* e, ulng depth) { //default generation
	str* result = Str__new(0ULL);
	str* BEGINNING = ctxt__toStr("istr{");
	result = str__addSelf(result, BEGINNING);
	str__free(BEGINNING);

	//prepare depth spacing
	boo hasDepth    = (depth != -1LL);
	str* depthSpace = NULL;
	if(hasDepth) {
		depthSpace = Str__new(depth);
		str__fill(depthSpace, '\t');
	}

	//field1 : s
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD1 = ctxt__toStr("s:"); //name
	result = str__addSelf(result, FIELD1);
	str__free(FIELD1);
	str* fieldValue = str__toStr(e->s); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//field2 : index
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD2 = ctxt__toStr("index:"); //name
	result = str__addSelf(result, FIELD2);
	str__free(FIELD2);
	fieldValue = ulng__toStr(e->index); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);

	//last spacing
	if(hasDepth) {
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
	}
	result = str__addChrSelf(result, '}');
	return result;
}

//istr functions
istr* IStr__new(ulng length) {
	istr* i  = malloc(sizeof(istr));
	i->s     = Str__new(length);
	i->index = -1LL;
	return i;
}
istr* IStr__fromStr(str* s) {
	istr* i  = malloc(sizeof(istr));
	i->s     = s;
	i->index = -1LL;
	return i;
}
void istr__free(istr* i, boo freeContent) {
	if(freeContent) { str__free(i->s); }
	free(i);
}
boo istr__forward(istr* i, ulng step) {
	if((i->index + step) >= i->s->length) { return true; } //could not forward => ret true
	i->index += step;
	return false;
}
boo istr__inc(istr* i) { return istr__forward(i, 1ULL); }
chr istr__get(istr* i) {
	return i->s->data[i->index];
}
void istr__set(istr* i, chr value) {
	i->s->data[i->index] = value;
}
boo istr__push(istr* i, chr value) {
	if(istr__inc(i)) { return true; }
	istr__set(i, value);
	return false;
}






// ---------------- IO ----------------

//terminal
ulng Term__TAB_LENGTH = 8ULL;

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


//type-related generated content : atoms
const uint ATOM__IO__file = 18;
atm* IO__file__toAtm(IO__file* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__IO__file;
	a->data = (ptr)e;
	return a;
}

//type-related generated content : toStr
str* IO__file__toStr(IO__file* e, ulng depth) { //default generation
	str* result = Str__new(0ULL);
	str* BEGINNING = ctxt__toStr("IO__file{");
	result = str__addSelf(result, BEGINNING);
	str__free(BEGINNING);

	//prepare depth spacing
	boo hasDepth    = (depth != -1LL);
	str* depthSpace = NULL;
	if(hasDepth) {
		depthSpace = Str__new(depth);
		str__fill(depthSpace, '\t');
	}

	//field1 : length
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD1 = ctxt__toStr("length:"); //name
	result = str__addSelf(result, FIELD1);
	str__free(FIELD1);
	str* fieldValue = ulng__toStr(e->length); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//field2 : c_ptr
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD2 = ctxt__toStr("c_ptr:"); //name
	result = str__addSelf(result, FIELD2);
	str__free(FIELD2);
	fieldValue = ptr__toStr(e->c_ptr); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);

	//last spacing
	if(hasDepth) {
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
	}
	result = str__addChrSelf(result, '}');
	return result;
}

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
	str__free(s);
}
void IO__ctxt__printLF(chr* c) {
	str* s = ctxt__toStr(c);
	IO__printLF(s);
	str__free(s);
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






// ---------------- ERRORS / LOGS ----------------

//definitions
const ubyt Err__SUCCESS  = '\x00';
const ubyt Err__FAILURE  = '\x01';
const ubyt Err__CONTINUE = Err__SUCCESS;

//header text
str Log__HEADER[] = { //Log__HEADER is a tab actually
	{ 10ULL, "[ DEBUG ] " },
	{ 10ULL, "[       ] " }, //LOAD0
	{ 10ULL, "[*      ] " },
	{ 10ULL, "[**     ] " },
	{ 10ULL, "[***    ] " },
	{ 10ULL, "[ ***   ] " },
	{ 10ULL, "[  ***  ] " },
	{ 10ULL, "[   *** ] " },
	{ 10ULL, "[    ***] " },
	{ 10ULL, "[     **] " },
	{ 10ULL, "[      *] " }, //LOAD9
	{ 10ULL, "[ INFO  ] " },
	{ 10ULL, "[WARNING] " },
	{ 10ULL, "[ ERROR ] " }
#ifdef INTERNAL_ERRORS
	,{ 10ULL, "[INT ERR] " }
#endif
};
#ifdef INTERNAL_ERRORS
ulng Log__HEADER__length = 15ULL;
#else
ulng Log__HEADER__length = 14ULL;
#endif

//log level (= HEADER indexes)
const ubyt Log__LEVEL__DEBUG   = '\x00';
const ubyt Log__LEVEL__LOAD0   = '\x01';
const ubyt Log__LEVEL__LOAD1   = '\x02';
const ubyt Log__LEVEL__LOAD2   = '\x03';
const ubyt Log__LEVEL__LOAD3   = '\x04';
const ubyt Log__LEVEL__LOAD4   = '\x05';
const ubyt Log__LEVEL__LOAD5   = '\x06';
const ubyt Log__LEVEL__LOAD6   = '\x07';
const ubyt Log__LEVEL__LOAD7   = '\x08';
const ubyt Log__LEVEL__LOAD8   = '\x09';
const ubyt Log__LEVEL__LOAD9   = '\x0a';
const ubyt Log__LEVEL__INFO    = '\x0b';
const ubyt Log__LEVEL__WARNING = '\x0c';
const ubyt Log__LEVEL__ERROR   = '\x0d';
#ifdef INTERNAL_ERRORS
const ubyt Log__LEVEL__INTERR  = '\x0d';
#endif
const ubyt Log__LEVEL__NONE    = '\xff'; //out of range of Log__HEADER

//level filtration
ubyt Log__level = Log__LEVEL__LOAD0; //default value

//generic output
void Log__print(str* msg, boo header, str* filename, ubyt level) {
	if(level < Log__HEADER__length) {
		if(level < Log__level) { return; }
		if(header) { IO__print(Log__HEADER + level); } //<=> Log__HEADER[level]
	}
	#ifdef LOG_FILENAME
	IO__print(filename);
	str* separator = ctxt__toStr(": ");
	IO__print(separator);
	str__free(separator);
	#endif
	IO__print(msg);
}
void Log__printLF(str* msg, boo header, str* filename, ubyt level) {
	if(level < Log__HEADER__length) {
		if(level < Log__level) { return; }
		if(header) { IO__print(Log__HEADER + level); }
	}
	#ifdef LOG_FILENAME
	IO__print(filename);
	str* separator = ctxt__toStr(": ");
	IO__print(separator);
	str__free(separator);
	#endif
	IO__printLF(msg);
}

//debug - warning - error
#ifdef DEBUG_AVAILABLE
	void Log__debug(str* msg, boo header, str* filename)   { Log__print(  msg, header, filename, Log__LEVEL__DEBUG); }
	void Log__debugLF(str* msg, boo header, str* filename) { Log__printLF(msg, header, filename, Log__LEVEL__DEBUG); }

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< TEMPORARY FOR CTXT
	void Log__ctxt__debug(chr* msg, boo header, str* filename) {
		str* s_msg = ctxt__toStr(msg);
		Log__debug(s_msg, header, filename);
		str__free(s_msg);
	}
	void Log__ctxt__debugLF(chr* msg, boo header, str* filename) {
		str* s_msg = ctxt__toStr(msg);
		Log__debugLF(s_msg, header, filename);
		str__free(s_msg);
	}
#endif
/* NOT USED YET
void Log__info(     str* msg, boo header, str* filename)           { Log__print(  msg, header, filename, Log__LEVEL__INFO);    }
void Log__infoLF(   str* msg, boo header, str* filename)           { Log__printLF(msg, header, filename, Log__LEVEL__INFO);    }
void Log__warning(  str* msg, boo header, str* filename)           { Log__print(  msg, header, filename, Log__LEVEL__WARNING); }
void Log__warningLF(str* msg, boo header, str* filename)           { Log__printLF(msg, header, filename, Log__LEVEL__WARNING); }*/
void Log__error(    str* msg, boo header, str* filename)           { Log__print(  msg, header, filename, Log__LEVEL__ERROR);   }
void Log__errorLF(  str* msg, boo header, str* filename, ubyt err) { Log__printLF(msg, header, filename, Log__LEVEL__ERROR);
	if(err != Err__CONTINUE) { Syscall__exit(err); }
}

//internal errors
#ifdef INTERNAL_ERRORS
void Log__internal(  str* msg, boo header, str* filename) { Log__print(  msg, header, filename, Log__LEVEL__INTERR); Syscall__exit(Err__FAILURE); }
void Log__internalLF(str* msg, boo header, str* filename) { Log__printLF(msg, header, filename, Log__LEVEL__INTERR); Syscall__exit(Err__FAILURE); }
#endif






// ---------------- ARGS ----------------

//definitions
typedef struct {
	chr  short_name;
	str* long_name;
	boo  textRequired;
	str* value;
	tab* description; //tab[str]
} opt;

//type-related generated content : atoms
const uint ATOM__opt = 19;
atm* opt__toAtm(opt* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__opt;
	a->data = (ptr)e;
	return a;
}

//type-related generated content : toStr
str* opt__toStr(opt* e, ulng depth) { //default generation
	str* result = Str__new(0ULL);
	str* BEGINNING = ctxt__toStr("opt{");
	result = str__addSelf(result, BEGINNING);
	str__free(BEGINNING);

	//prepare depth spacing
	boo hasDepth    = (depth != -1LL);
	str* depthSpace = NULL;
	if(hasDepth) {
		depthSpace = Str__new(depth);
		str__fill(depthSpace, '\t');
	}

	//field1 : short_name
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD1 = ctxt__toStr("short_name:"); //name
	result = str__addSelf(result, FIELD1);
	str__free(FIELD1);
	str* fieldValue = chr__toStr(e->short_name); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//field2 : long_name
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD2 = ctxt__toStr("long_name:"); //name
	result = str__addSelf(result, FIELD2);
	str__free(FIELD2);
	fieldValue = str__toStr(e->long_name); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//field3 : textRequired
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD3 = ctxt__toStr("textRequired:"); //name
	result = str__addSelf(result, FIELD3);
	str__free(FIELD3);
	fieldValue = boo__toStr(e->textRequired); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//field4 : value
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD4 = ctxt__toStr("value:"); //name
	result = str__addSelf(result, FIELD4);
	str__free(FIELD4);
	fieldValue = str__toStr(e->value); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);

	//field5 : description
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD5 = ctxt__toStr("description:"); //name
	result = str__addSelf(result, FIELD5);
	str__free(FIELD5);
	fieldValue = tab_str__toStr(e->description); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);

	//last spacing
	if(hasDepth) {
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
	}
	result = str__addChrSelf(result, '}');
	return result;
}

//functions
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
			Log__errorLF(
				str__add(str__add(ctxt__toStr("Option '--"), o->long_name), ctxt__toStr("' requires a value (nothing given).")),
				true, __FILENAME__, Err__FAILURE
			);
		}
		if(str__index(tab_str__index(args, argIndex[0]),0) == '-') {
			Log__errorLF(
				str__add(str__add(ctxt__toStr("Option '--"), o->long_name), ctxt__toStr("' requires a value (another option given).")),
				true, __FILENAME__, Err__FAILURE
			);
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
			if(a->length == 1UL) { Log__errorLF(ctxt__toStr("Missing argument name to lonely '-'."), true, __FILENAME__, Err__FAILURE); }
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
				Log__errorLF(
					str__add(str__add( ctxt__toStr("Undefined option '"), a), ctxt__toStr("'.\n")),
					true, __FILENAME__, Err__FAILURE
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
	str* output = ctxt__toStr("Options:\n");
	for(ulng optIndex=0UL; optIndex < opts->length; optIndex++) {
		opt* o = tab_opt__index(opts, optIndex);

		//classic option header
		output = str__add(
			output,
			str__add(
				str__add(
					str__addChr(ctxt__toStr("\n  -"), o->short_name),
					ctxt__toStr(", --")
				),
				o->long_name
			)
		);

		//required argument or nothing
		if(o->textRequired) {
			output = str__add(output, ctxt__toStr(" <"));
			output = str__addChr(output, o->short_name);
			output = str__add(output, ctxt__toStr("> "));
		} else {
			output = str__add(output, ctxt__toStr("     "));
		}

		//header padding
		ulng headerPaddingLength = longestOptLength - (o->long_name)->length;
		if(headerPaddingLength > 0UL) {
			str* headerPadding = Str__new(headerPaddingLength);
			for(ulng s=0UL; s < headerPaddingLength; s++) { str__indexAssign(headerPadding, s, ' '); }
			output = str__add(output, headerPadding);
			str__free(headerPadding);
		}
		output = str__add(output, ctxt__toStr(": "));

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
		Log__errorLF(
			str__add(str__add(ctxt__toStr("Path '"), path), ctxt__toStr("' is not a directory.")),
			true, __FILENAME__, err
		);
	}
}
void Path__errorIfNotFile(str* path, byt err) {
	if(!Path__isFile(path)){
		Log__errorLF(
			str__add(str__add(ctxt__toStr("Path '"), path), ctxt__toStr("' is not a file.")),
			true, __FILENAME__, err
		);
	}
}






// ---------------- CONVERSIONS ----------------

//str -> unsigned
ubyt chr__fromHexToUByt(chr c) {
	if(c >= '0' && c <= '9'){ return c - '0';          }
	if(c >= 'a' && c <= 'f'){ return c - 'a' + '\x0a'; }
	return '\xff';
}
ubyt str__toUByt(str* input) {
	if(input->length < 2ULL) {
		Log__errorLF(
			str__add(str__add(ctxt__toStr("String \""), input), ctxt__toStr("\" too short to be converted into UByt (at least 2 characters required).")),
			true, __FILENAME__, Err__FAILURE
		);
	}
	ubyt pow1 = chr__fromHexToUByt(str__index(input, 0ULL));
	ubyt pow0 = chr__fromHexToUByt(str__index(input, 1ULL));
	return pow1 << 4 | pow0;
}
ushr str__toUShr(str* input) {
	if(input->length < 4ULL) {
		Log__errorLF(
			str__add(str__add(ctxt__toStr("String \""), input), ctxt__toStr("\" too short to be converted into UShr (at least 4 characters required).")),
			true, __FILENAME__, Err__FAILURE
		);
	}
	ushr pow3 = chr__fromHexToUByt(str__index(input, 0ULL));
	ushr pow2 = chr__fromHexToUByt(str__index(input, 1ULL));
	ushr pow1 = chr__fromHexToUByt(str__index(input, 2ULL));
	ushr pow0 = chr__fromHexToUByt(str__index(input, 3ULL));
	return \
		pow3 << 12 | pow2 << 8 | \
		pow1 <<  4 | pow0;
}
uint str__toUInt(str* input) {
	if(input->length < 8ULL) {
		Log__errorLF(
			str__add(str__add(ctxt__toStr("String \""), input), ctxt__toStr("\" too short to be converted into UInt (at least 8 characters required).")),
			true, __FILENAME__, Err__FAILURE
		);
	}
	uint pow7 = chr__fromHexToUByt(str__index(input, 0ULL));
	uint pow6 = chr__fromHexToUByt(str__index(input, 1ULL));
	uint pow5 = chr__fromHexToUByt(str__index(input, 2ULL));
	uint pow4 = chr__fromHexToUByt(str__index(input, 3ULL));
	uint pow3 = chr__fromHexToUByt(str__index(input, 4ULL));
	uint pow2 = chr__fromHexToUByt(str__index(input, 5ULL));
	uint pow1 = chr__fromHexToUByt(str__index(input, 6ULL));
	uint pow0 = chr__fromHexToUByt(str__index(input, 7ULL));
	return \
		pow7 << 28 | pow6 << 24 | \
		pow5 << 20 | pow4 << 16 | \
		pow3 << 12 | pow2 <<  8 | \
		pow1 <<  4 | pow0;
}
ulng str__toULng(str* input) {
	if(input->length < 16ULL) {
		Log__errorLF(
			str__add(str__add(ctxt__toStr("String \""), input), ctxt__toStr("\" too short to be converted into ULng (at least 16 characters are required).")),
			true, __FILENAME__, Err__FAILURE
		);
	}
	ulng powF = chr__fromHexToUByt(str__index(input,  0ULL));
	ulng powE = chr__fromHexToUByt(str__index(input,  1ULL));
	ulng powD = chr__fromHexToUByt(str__index(input,  2ULL));
	ulng powC = chr__fromHexToUByt(str__index(input,  3ULL));
	ulng powB = chr__fromHexToUByt(str__index(input,  4ULL));
	ulng powA = chr__fromHexToUByt(str__index(input,  5ULL));
	ulng pow9 = chr__fromHexToUByt(str__index(input,  6ULL));
	ulng pow8 = chr__fromHexToUByt(str__index(input,  7ULL));
	ulng pow7 = chr__fromHexToUByt(str__index(input,  8ULL));
	ulng pow6 = chr__fromHexToUByt(str__index(input,  9ULL));
	ulng pow5 = chr__fromHexToUByt(str__index(input, 10ULL));
	ulng pow4 = chr__fromHexToUByt(str__index(input, 11ULL));
	ulng pow3 = chr__fromHexToUByt(str__index(input, 12ULL));
	ulng pow2 = chr__fromHexToUByt(str__index(input, 13ULL));
	ulng pow1 = chr__fromHexToUByt(str__index(input, 14ULL));
	ulng pow0 = chr__fromHexToUByt(str__index(input, 15ULL));
	return \
		powF << 60 | powE << 56 | \
		powD << 52 | powC << 48 | \
		powB << 44 | powA << 40 | \
		pow9 << 36 | pow8 << 32 | \
		pow7 << 28 | pow6 << 24 | \
		pow5 << 20 | pow4 << 16 | \
		pow3 << 12 | pow2 <<  8 | \
		pow1 <<  4 | pow0;
}

//unsigned -> str
chr ubyt__lastHexDigit(ubyt u) {
	if(u < '\x0a') { return '0' + u; }
	return 'a' + u - '\x0a';
}






// ---------------- PARSING ----------------

//definition
typedef struct {
	str*  filename;
	ulng  lineNbr;
	ulng  columnNbr;
	istr* icontent;
	boo   detectedLF;
} Parsing__ctx;

//type-related generated content : atoms
const uint ATOM__Parsing__ctx = 19;
atm* Parsing__ctx__toAtm(Parsing__ctx* e) {
	atm* a  = malloc(sizeof(atm));
	a->id   = ATOM__Parsing__ctx;
	a->data = (ptr)e;
	return a;
}

//type-related generated content : toStr
str* Parsing__ctx__toStr(Parsing__ctx* e, ulng depth) { //default generation
	str* result = Str__new(0ULL);
	str* BEGINNING = ctxt__toStr("Parsing__ctx{");
	result = str__addSelf(result, BEGINNING);
	str__free(BEGINNING);

	//prepare depth spacing
	boo hasDepth    = (depth != -1LL);
	str* depthSpace = NULL;
	if(hasDepth) {
		depthSpace = Str__new(depth);
		str__fill(depthSpace, '\t');
	}

	//field1 : filename
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD1 = ctxt__toStr("filename:"); //name
	result = str__addSelf(result, FIELD1);
	str__free(FIELD1);
	str* fieldValue = str__toStr(e->filename); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//field2 : lineNbr
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD2 = ctxt__toStr("lineNbr:"); //name
	result = str__addSelf(result, FIELD2);
	str__free(FIELD2);
	fieldValue = ulng__toStr(e->lineNbr); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//field3 : columnNbr
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD3 = ctxt__toStr("columnNbr:"); //name
	result = str__addSelf(result, FIELD3);
	str__free(FIELD3);
	fieldValue = ulng__toStr(e->columnNbr); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);
	result = str__addChrSelf(result, ',');

	//field4 : icontent
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD4 = ctxt__toStr("icontent:"); //name
	result = str__addSelf(result, FIELD4);
	str__free(FIELD4);
	fieldValue = istr__toStr(e->icontent); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);

	//field5 : detectedLF
	if(hasDepth) { //spacing
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
		result = str__addChrSelf(result, '\t');
	}
	str* FIELD5 = ctxt__toStr("detectedLF:"); //name
	result = str__addSelf(result, FIELD5);
	str__free(FIELD5);
	fieldValue = boo__toStr(e->detectedLF); //data
	result = str__addSelf(result, fieldValue);
	str__free(fieldValue);

	//last spacing
	if(hasDepth) {
		result = str__addChrSelf(result, '\n');
		result = str__addSelf(result, depthSpace);
	}
	result = str__addChrSelf(result, '}');
	return result;
}

//functions
Parsing__ctx* Parsing__Ctx__new(str* filename, str* content) {
	Parsing__ctx* ctx = malloc(sizeof(Parsing__ctx));
	ctx->filename   = filename;
	ctx->lineNbr    = 1ULL;
	ctx->columnNbr  = 1ULL;
	ctx->icontent   = IStr__fromStr(content);
	ctx->detectedLF = false;
	return ctx;
}
chr Parsing__ctx__get(Parsing__ctx* ctx) { return istr__get(ctx->icontent); }
//void Parsing__ctx__set(Parsing__ctx* ctx, chr value) { istr__set(cxt->content, value); } //not used yet
boo Parsing__ctx__inc(Parsing__ctx* ctx) {
	if(istr__inc(ctx->icontent)) { return true; } //can't go further => can't go further

	//last character was a line feed => update line indicators
	if(ctx->detectedLF) { ctx->detectedLF = false; ctx->lineNbr++; ctx->columnNbr = 0ULL; }

	//LF behavior
	if(istr__get(ctx->icontent) == '\n') { ctx->detectedLF = true; }

	//regular behavior
	ctx->columnNbr++;
	return false;
}
void Parsing__ctx__free(Parsing__ctx* ctx) {
	istr__free(ctx->icontent, false);
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
	resultStr         = str__addSelf(resultStr, columnNbrStr);
	str__free(columnNbrStr);
	return resultStr;
}
Parsing__ctx* Parsing__ctx__copy(Parsing__ctx* ctx) {
	Parsing__ctx* ctx2    = Parsing__Ctx__new(ctx->filename, ctx->icontent->s);
	ctx2->lineNbr         = ctx->lineNbr;
	ctx2->columnNbr       = ctx->columnNbr;
	ctx2->icontent->index = ctx->icontent->index;
	return ctx2;
}
void Parsing__ctx__printLineIndicator(Parsing__ctx* ctx, ubyt level) { //level='\xff' (disabled)
	Log__printLF(Parsing__ctx__toStr(ctx), true, __FILENAME__, level);
	str* content = ctx->icontent->s;

	//set beginning & end of line
	ulng begIndex, endIndex;
	if(ctx->icontent->index == -1LL){ begIndex = 0ULL; endIndex = 0ULL; } //invalid value (istr starting index)
	else {
		begIndex = ctx->icontent->index - (ctx->columnNbr-1LL);
		endIndex = ctx->icontent->index;
	}
	if(begIndex > endIndex) { begIndex = 0ULL; } //that mean we are in the first line (cannot subtract columnNbr)

	//read to get real end of line
	while(endIndex < content->length){
		if(str__index(content, endIndex) == '\n') { break; }
		endIndex++;
	}

	//print full line
	str* rawConcernedLine = str__sub(content, begIndex, endIndex);
	str* concernedLine    = str__expandTabs(rawConcernedLine, Term__TAB_LENGTH);
	Log__print(concernedLine, true, __FILENAME__, level);
	str__free(concernedLine);

	//prepare position indicator
	ulng realColumnNbr     = (Term__TAB_LENGTH-1LL)*str__countChr(rawConcernedLine, '\t') + ctx->columnNbr;
	str__free(rawConcernedLine);
	ulng positionIndex     =  realColumnNbr - 1LL;
	str* positionIndicator = Str__new(realColumnNbr);
	for(ulng i=0ULL; i < positionIndex; i++) { str__indexAssign(positionIndicator, i, '-'); }
	str__indexAssign(positionIndicator, positionIndex, '^');

	//print position indicator
	Log__printLF(positionIndicator, true, __FILENAME__, level);
	str__free(positionIndicator);
}
#ifdef DEBUG_AVAILABLE
void Parsing__ctx__debug(Parsing__ctx* ctx, chr* msg){ //str* msg){ //use of chr* is a tmp shortcut
	Log__ctxt__debugLF("", true, __FILENAME__);
	Parsing__ctx__printLineIndicator(ctx, Log__LEVEL__DEBUG);
	Log__ctxt__debugLF(msg, true, __FILENAME__);
}
//TEMPORARY <<<<<<<<<<<<<<<<<<<<<<<
void Parsing__ctx__debug_WITHOUT_LF(Parsing__ctx* ctx, chr* msg){ //str* msg){ //use of chr* is a tmp shortcut
	Log__ctxt__debugLF("", true, __FILENAME__);
	Parsing__ctx__printLineIndicator(ctx, Log__LEVEL__DEBUG);
	Log__ctxt__debug(msg, true);
}//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#endif
void Parsing__ctx__errorLF(Parsing__ctx* ctx, str* s) {
	Parsing__ctx__printLineIndicator(ctx, Log__LEVEL__ERROR);
	Log__errorLF(s, true, __FILENAME__, Err__FAILURE);
}
void Parsing__ctx__internalLF(Parsing__ctx* ctx, str* s) {
	Parsing__ctx__printLineIndicator(ctx, Log__LEVEL__INTERR);
	Log__internalLF(s, true, __FILENAME__);
}
