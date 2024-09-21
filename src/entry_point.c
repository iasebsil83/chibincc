// ---------------- ENTRY POINT ----------------

//main program
#include "main.c"

//C main link
int main(int argc, char** argv) {
	tab* args = malloc(sizeof(tab));
	args->length = argc;
	if(argc == 0){
		args->data = NULL;
	} else {
		args->data = malloc(argc * sizeof(str*));
		for(ulng i=0UL; i < argc; i++) {
			args->data[i] = (byt*)s(argv[i]);
		}
	}
	return zmain(args); //end of process => no need to free "args" afterwards
}
