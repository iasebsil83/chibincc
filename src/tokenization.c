/*
#include "chibicc.h"

// Consumes the current token if it matches `op`.
bool equal(Token *tok, char *op) {
  return memcmp(tok->loc, op, tok->len) == 0 && op[tok->len] == '\0';
}

// Ensure that the current token is `op`.
Token *skip(Token *tok, char *op) {
  if (!equal(tok, op))
    error_tok(tok, "expected '%s'", op);
  return tok->next;
}

bool consume(Token **rest, Token *tok, char *str) {
  if (equal(tok, str)) {
    *rest = tok->next;
    return true;
  }
  *rest = tok;
  return false;
}

static bool startswith(char *p, char *q) {
  return strncmp(p, q, strlen(q)) == 0;
}

static int from_hex(char c) {
  if ('0' <= c && c <= '9')
    return c - '0';
  if ('a' <= c && c <= 'f')
    return c - 'a' + 10;
  return c - 'A' + 10;
}

// Read a punctuator token from p and returns its length.
static int read_punct(char *p) {
  static char *kw[] = {
    "<<=", ">>=", "...", "==", "!=", "<=", ">=", "->", "+=",
    "-=", "*=", "/=", "++", "--", "%=", "&=", "|=", "^=", "&&",
    "||", "<<", ">>", "##",
  };

  for (int i = 0; i < sizeof(kw) / sizeof(*kw); i++)
    if (startswith(p, kw[i]))
      return strlen(kw[i]);

  return ispunct(*p) ? 1 : 0;
}

static bool is_keyword(Token *tok) {
  static HashMap map;

  if (map.capacity == 0) {
    static char *kw[] = {
      "return", "if", "else", "for", "while", "int", "sizeof", "char",
      "struct", "union", "short", "long", "void", "typedef", "_Bool",
      "enum", "static", "goto", "break", "continue", "switch", "case",
      "default", "extern", "_Alignof", "_Alignas", "do", "signed",
      "unsigned", "const", "volatile", "auto", "register", "restrict",
      "__restrict", "__restrict__", "_Noreturn", "float", "double",
      "typeof", "asm", "_Thread_local", "__thread", "_Atomic",
      "__attribute__",
    };

    for (int i = 0; i < sizeof(kw) / sizeof(*kw); i++)
      hashmap_put(&map, kw[i], (void *)1);
  }

  return hashmap_get2(&map, tok->loc, tok->len);
}

static int read_escaped_char(char **new_pos, char *p) {
  if ('0' <= *p && *p <= '7') {
    // Read an octal number.
    int c = *p++ - '0';
    if ('0' <= *p && *p <= '7') {
      c = (c << 3) + (*p++ - '0');
      if ('0' <= *p && *p <= '7')
        c = (c << 3) + (*p++ - '0');
    }
    *new_pos = p;
    return c;
  }

  if (*p == 'x') {
    // Read a hexadecimal number.
    p++;
    if (!isxdigit(*p))
      error_at(p, "invalid hex escape sequence");

    int c = 0;
    for (; isxdigit(*p); p++)
      c = (c << 4) + from_hex(*p);
    *new_pos = p;
    return c;
  }

  *new_pos = p + 1;

  // Escape sequences are defined using themselves here. E.g.
  // '\n' is implemented using '\n'. This tautological definition
  // works because the compiler that compiles our compiler knows
  // what '\n' actually is. In other words, we "inherit" the ASCII
  // code of '\n' from the compiler that compiles our compiler,
  // so we don't have to teach the actual code here.
  //
  // This fact has huge implications not only for the correctness
  // of the compiler but also for the security of the generated code.
  // For more info, read "Reflections on Trusting Trust" by Ken Thompson.
  // https://github.com/rui314/chibicc/wiki/thompson1984.pdf
  switch (*p) {
  case 'a': return '\a';
  case 'b': return '\b';
  case 't': return '\t';
  case 'n': return '\n';
  case 'v': return '\v';
  case 'f': return '\f';
  case 'r': return '\r';
  // [GNU] \e for the ASCII escape character is a GNU C extension.
  case 'e': return 27;
  default: return *p;
  }
}

// Find a closing double-quote.
static char *string_literal_end(char *p) {
  char *start = p;
  for (; *p != '"'; p++) {
    if (*p == '\n' || *p == '\0')
      error_at(start, "unclosed string literal");
    if (*p == '\\')
      p++;
  }
  return p;
}

static Token *read_string_literal(char *start, char *quote) {
  char *end = string_literal_end(quote + 1);
  char *buf = calloc(1, end - quote);
  int len = 0;

  for (char *p = quote + 1; p < end;) {
    if (*p == '\\')
      buf[len++] = read_escaped_char(&p, p + 1);
    else
      buf[len++] = *p++;
  }

  Token *tok = new_token(TK_STR, start, end + 1);
  tok->ty = array_of(ty_char, len + 1);
  tok->str = buf;
  return tok;
}

// Read a UTF-8-encoded string literal and transcode it in UTF-16.
//
// UTF-16 is yet another variable-width encoding for Unicode. Code
// points smaller than U+10000 are encoded in 2 bytes. Code points
// equal to or larger than that are encoded in 4 bytes. Each 2 bytes
// in the 4 byte sequence is called "surrogate", and a 4 byte sequence
// is called a "surrogate pair".
static Token *read_utf16_string_literal(char *start, char *quote) {
  char *end = string_literal_end(quote + 1);
  uint16_t *buf = calloc(2, end - start);
  int len = 0;

  for (char *p = quote + 1; p < end;) {
    if (*p == '\\') {
      buf[len++] = read_escaped_char(&p, p + 1);
      continue;
    }

    uint32_t c = decode_utf8(&p, p);
    if (c < 0x10000) {
      // Encode a code point in 2 bytes.
      buf[len++] = c;
    } else {
      // Encode a code point in 4 bytes.
      c -= 0x10000;
      buf[len++] = 0xd800 + ((c >> 10) & 0x3ff);
      buf[len++] = 0xdc00 + (c & 0x3ff);
    }
  }

  Token *tok = new_token(TK_STR, start, end + 1);
  tok->ty = array_of(ty_ushort, len + 1);
  tok->str = (char *)buf;
  return tok;
}

// Read a UTF-8-encoded string literal and transcode it in UTF-32.
//
// UTF-32 is a fixed-width encoding for Unicode. Each code point is
// encoded in 4 bytes.
static Token *read_utf32_string_literal(char *start, char *quote, Type *ty) {
  char *end = string_literal_end(quote + 1);
  uint32_t *buf = calloc(4, end - quote);
  int len = 0;

  for (char *p = quote + 1; p < end;) {
    if (*p == '\\')
      buf[len++] = read_escaped_char(&p, p + 1);
    else
      buf[len++] = decode_utf8(&p, p);
  }

  Token *tok = new_token(TK_STR, start, end + 1);
  tok->ty = array_of(ty, len + 1);
  tok->str = (char *)buf;
  return tok;
}

static Token *read_char_literal(char *start, char *quote, Type *ty) {
  char *p = quote + 1;
  if (*p == '\0')
    error_at(start, "unclosed char literal");

  int c;
  if (*p == '\\')
    c = read_escaped_char(&p, p + 1);
  else
    c = decode_utf8(&p, p);

  char *end = strchr(p, '\'');
  if (!end)
    error_at(p, "unclosed char literal");

  Token *tok = new_token(TK_NUM, start, end + 1);
  tok->val = c;
  tok->ty = ty;
  return tok;
}

static bool convert_pp_int(Token *tok) {
  char *p = tok->loc;

  // Read a binary, octal, decimal or hexadecimal number.
  int base = 10;
  if (!strncasecmp(p, "0x", 2) && isxdigit(p[2])) {
    p += 2;
    base = 16;
  } else if (!strncasecmp(p, "0b", 2) && (p[2] == '0' || p[2] == '1')) {
    p += 2;
    base = 2;
  } else if (*p == '0') {
    base = 8;
  }

  int64_t val = strtoul(p, &p, base);

  // Read U, L or LL suffixes.
  bool l = false;
  bool u = false;

  if (startswith(p, "LLU") || startswith(p, "LLu") ||
      startswith(p, "llU") || startswith(p, "llu") ||
      startswith(p, "ULL") || startswith(p, "Ull") ||
      startswith(p, "uLL") || startswith(p, "ull")) {
    p += 3;
    l = u = true;
  } else if (!strncasecmp(p, "lu", 2) || !strncasecmp(p, "ul", 2)) {
    p += 2;
    l = u = true;
  } else if (startswith(p, "LL") || startswith(p, "ll")) {
    p += 2;
    l = true;
  } else if (*p == 'L' || *p == 'l') {
    p++;
    l = true;
  } else if (*p == 'U' || *p == 'u') {
    p++;
    u = true;
  }

  if (p != tok->loc + tok->len)
    return false;

  // Infer a type.
  Type *ty;
  if (base == 10) {
    if (l && u)
      ty = ty_ulong;
    else if (l)
      ty = ty_long;
    else if (u)
      ty = (val >> 32) ? ty_ulong : ty_uint;
    else
      ty = (val >> 31) ? ty_long : ty_int;
  } else {
    if (l && u)
      ty = ty_ulong;
    else if (l)
      ty = (val >> 63) ? ty_ulong : ty_long;
    else if (u)
      ty = (val >> 32) ? ty_ulong : ty_uint;
    else if (val >> 63)
      ty = ty_ulong;
    else if (val >> 32)
      ty = ty_long;
    else if (val >> 31)
      ty = ty_uint;
    else
      ty = ty_int;
  }

  tok->kind = TK_NUM;
  tok->val = val;
  tok->ty = ty;
  return true;
}

// The definition of the numeric literal at the preprocessing stage
// is more relaxed than the definition of that at the later stages.
// In order to handle that, a numeric literal is tokenized as a
// "pp-number" token first and then converted to a regular number
// token after preprocessing.
//
// This function converts a pp-number token to a regular number token.
static void convert_pp_number(Token *tok) {
  // Try to parse as an integer constant.
  if (convert_pp_int(tok))
    return;

  // If it's not an integer, it must be a floating point constant.
  char *end;
  long double val = strtold(tok->loc, &end);

  Type *ty;
  if (*end == 'f' || *end == 'F') {
    ty = ty_float;
    end++;
  } else if (*end == 'l' || *end == 'L') {
    ty = ty_ldouble;
    end++;
  } else {
    ty = ty_double;
  }

  if (tok->loc + tok->len != end)
    error_tok(tok, "invalid numeric constant");

  tok->kind = TK_NUM;
  tok->fval = val;
  tok->ty = ty;
}

void convert_pp_tokens(Token *tok) {
  for (Token *t = tok; t->kind != TK_EOF; t = t->next) {
    if (is_keyword(t))
      t->kind = TK_KEYWORD;
    else if (t->kind == TK_PP_NUM)
      convert_pp_number(t);
  }
}

// Initialize line info for all tokens.
static void add_line_numbers(Token *tok) {
  char *p = current_file->contents;
  int n = 1;

  do {
    if (p == tok->loc) {
      tok->line_no = n;
      tok = tok->next;
    }
    if (*p == '\n')
      n++;
  } while (*p++);
}

Token *tokenize_string_literal(Token *tok, Type *basety) {
  Token *t;
  if (basety->size == 2)
    t = read_utf16_string_literal(tok->loc, tok->loc);
  else
    t = read_utf32_string_literal(tok->loc, tok->loc, basety);
  t->next = tok->next;
  return t;
}

// Returns the contents of a given file.
static char *read_file(char *path) {
  FILE *fp;

  if (strcmp(path, "-") == 0) {
    // By convention, read from stdin if a given filename is "-".
    fp = stdin;
  } else {
    fp = fopen(path, "r");
    if (!fp)
      return NULL;
  }

  char *buf;
  size_t buflen;
  FILE *out = open_memstream(&buf, &buflen);

  // Read the entire file.
  for (;;) {
    char buf2[4096];
    int n = fread(buf2, 1, sizeof(buf2), fp);
    if (n == 0)
      break;
    fwrite(buf2, 1, n, out);
  }

  if (fp != stdin)
    fclose(fp);

  // Make sure that the last line is properly terminated with '\n'.
  fflush(out);
  if (buflen == 0 || buf[buflen - 1] != '\n')
    fputc('\n', out);
  fputc('\0', out);
  fclose(out);
  return buf;
}

File **get_input_files(void) {
  return input_files;
}

File* new_file(char *name, int file_no, char *contents) {
  File* file = malloc(sizeof(File));
  file->name = name;
  file->display_name = name;
  file->file_no = file_no;
  file->contents = contents;
  return file;
}

static uint32_t read_universal_char(char *p, int len) {
  uint32_t c = 0;
  for (int i = 0; i < len; i++) {
    if (!isxdigit(p[i]))
      return 0;
    c = (c << 4) | from_hex(p[i]);
  }
  return c;
}*/
















// ---------------- IMPORTATIONS ----------------

//lexicon
#include "context.c"






// ---------------- TOOLS ----------------

//read body including nested instructions themselves
ulng readWholeInstructionBody(Parsing__ctx* ctx) {
	/*IO__ctxt__printLF("BODY STEP1 [");
	str* TECHT = Parsing__ctx__toStr(ctx);
	IO__printLF(TECHT);
	str__free(TECHT);
	IO__ctxt__printLF("BODY STEP1 ]");*/

	istr* icontent   = ctx->icontent;
	ulng  startIndex = icontent->index;

	//end of line => end of instruction
	//IO__ctxt__printLF("BODY STEP2");
	while(true) {
		if(Parsing__ctx__inc(ctx)) { break; }
		chr c = Parsing__ctx__get(ctx);
		if(c == '\n'){ break; }
	}
	//IO__ctxt__printLF("BODY STEP3");

	//update value now that we have it
	ulng bodyLength = icontent->index - startIndex;
	str* body       = Str__new(bodyLength);
	//IO__ctxt__printLF("BODY STEP4");
	for(ulng i=0ULL; i < bodyLength; i++) { str__indexAssign(body, i, str__index(icontent->s, startIndex + i)); }
	//IO__ctxt__printLF("BODY STEP5");

	//return token
	return (ulng)body;
}

//specific token reading
token* newDefinitionToken_TypeCopy(Parsing__ctx* ctx, ubyt scope) {
	token* tok = Token__new(ctx, NC__ROLE_DEFINITION | scope | NC__DEF_SCOPE_KIND_COPY);
	tok->body  = readWholeInstructionBody(ctx);
	return tok;
}

token* newDefinitionToken_Structure(Parsing__ctx* ctx, ubyt scope) {
	token* tok = Token__new(ctx, NC__ROLE_DEFINITION | scope | NC__DEF_SCOPE_KIND_STRUCTURE);
	tok->body  = readWholeInstructionBody(ctx);
	return tok;
}

token* newDefinitionToken_Function(Parsing__ctx* ctx, ubyt scope) {
	token* tok = Token__new(ctx, NC__ROLE_DEFINITION | scope | NC__DEF_SCOPE_KIND_FUNCTION);
	tok->body  = readWholeInstructionBody(ctx);
	return tok;
}

token* newDefinitionToken_DataItem(Parsing__ctx* ctx, ubyt scope) {
	token* tok = Token__new(ctx, NC__ROLE_DEFINITION | scope | NC__DEF_SCOPE_KIND_DATA);
	tok->body  = readWholeInstructionBody(ctx);
	return tok;
}

token* newExecutionToken_If(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_IF);
	tok->body  = readWholeInstructionBody(ctx);
	return tok;
}

token* newExecutionToken_For(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_FOR);
	tok->body  = readWholeInstructionBody(ctx);
	return tok;
}

token* newExecutionToken_While(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_WHILE);
	tok->body  = readWholeInstructionBody(ctx);
	return tok;
}

token* newExecutionToken_Switch(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_SWITCH);
	tok->body  = readWholeInstructionBody(ctx);
	return tok;
}

token* newExecutionToken_Break(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_BREAK);
	tok->body  = readWholeInstructionBody(ctx);
	return tok;
}

token* newExecutionToken_Continue(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_CONTINUE);
	tok->body  = readWholeInstructionBody(ctx);
	return tok;
}

token* newExecutionToken_Return(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_RETURN);
	tok->body  = readWholeInstructionBody(ctx);
	return tok;
}

token* newExecutionToken_VFC(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_VFC);
	tok->body  = readWholeInstructionBody(ctx);
	return tok;
}

token* newExecutionToken_Assign(Parsing__ctx* ctx) {
	token* tok = Token__new(ctx, NC__ROLE_EXECUTION | NC__EXE_STATEMENT_ASSIGN);
	tok->body  = readWholeInstructionBody(ctx);
	return tok;
}




//error function
void Tokenization__error(Parsing__ctx* ctx, str* s) {
	IO__printLF(Parsing__ctx__toStr(ctx));
	str* content = ctx->icontent->s;

	//print full line
	ulng startIndex = ctx->icontent->index;
	ulng length     = 0ULL;
	while(startIndex + length < content->length){
		if(str__index(content, startIndex + length) == '\n') { break; }
		length++;
	}
	content->data   = content->data + startIndex; //edit directly into content string because, at this state,
	content->length = length;                     //we don't care, end of program is imminent
	IO__printLF(content);

	//error
	Err__error(s, Err__FAILURE);
}



//parsing entry point
lst* Tokenization__run(str* filename, str* inputText) {
	lst*          tokens = Lst__new();
	Parsing__ctx* ctx    = Parsing__Ctx__new(filename, inputText);

	//as long as we got things to read
	ulng debugStartIndex = 0ULL;
	while(true) {
		if(Parsing__ctx__inc(ctx)) { break; }
		chr c = Parsing__ctx__get(ctx);

		//dbug
		istr* currentIStr = ctx->icontent;
		IO__printChr('[');
		for(ulng aaa=debugStartIndex; aaa <= currentIStr->index; aaa++) {
			IO__printChr(str__index(currentIStr->s, aaa));
		}
		//str* TESTUX = Parsing__ctx__toStr(ctx);
		//IO__printLF(TESTUX);
		//str__free(TESTUX);
		debugStartIndex = currentIStr->index;
		IO__printChr(']');
		IO__printChr('\n');

		//skip beginning indent
		if(c == '\t') { continue; }

		//1st rank : ROLE
		ubyt scope;
		switch(c) {



			//DEF
			case 'd':
				IO__ctxt__printLF("DEF {");

				//2nd rank : DEF SCOPE
				if(Parsing__ctx__inc(ctx)) { Tokenization__error(ctx, s("Missing DEF SCOPE.")); }
				c = Parsing__ctx__get(ctx);
				scope = '\xff'; //invalid value for DEF SCOPE
				switch(c) {
					case 'i':
						if(scope == '\xff') { scope = NC__DEF_SCOPE_INTERN; IO__ctxt__printLF("SCOPE i"); }
					case 'x':
						if(scope == '\xff') { scope = NC__DEF_SCOPE_EXTERN; IO__ctxt__printLF("SCOPE e"); }
					case 's':
						if(scope == '\xff') { scope = NC__DEF_SCOPE_SHARED; IO__ctxt__printLF("SCOPE s"); }
					case 'l':
						if(scope == '\xff') { scope = NC__DEF_SCOPE_LOCAL; IO__ctxt__printLF("SCOPE l"); }

						//3rd rank : DEF SCOPE KIND
						if(Parsing__ctx__inc(ctx)) { Tokenization__error(ctx, s("Missing DEF SCOPE KIND.")); }
						switch(Parsing__ctx__get(ctx)){
							case 'c': lst__append(tokens, (byt*)newDefinitionToken_TypeCopy( ctx, scope)); break;
							case 's': lst__append(tokens, (byt*)newDefinitionToken_Structure(ctx, scope)); break;
							case 'f': lst__append(tokens, (byt*)newDefinitionToken_Function( ctx, scope)); break;
							case 'd': lst__append(tokens, (byt*)newDefinitionToken_DataItem( ctx, scope)); break;
							default: Tokenization__error(ctx, s("Missing DEF SCOPE KIND."));
						}
					break;
					default: Tokenization__error(ctx, s("Invalid DEF SCOPE given."));
				}
				IO__ctxt__printLF("DEF }");
			break;



			//EXE
			case 'x':
				IO__ctxt__printLF("EXE {");

				//2nd rank : EXE STATEMENT
				if(Parsing__ctx__inc(ctx)) { Tokenization__error(ctx, s("Invalid DEF SCOPE given.")); }
				switch(Parsing__ctx__get(ctx)) {
					case 'i': lst__append(tokens, (byt*)newExecutionToken_If(      ctx)); break;
					case 'f': lst__append(tokens, (byt*)newExecutionToken_For(     ctx)); break;
					case 'w': lst__append(tokens, (byt*)newExecutionToken_While(   ctx)); break;
					case 's': lst__append(tokens, (byt*)newExecutionToken_Switch(  ctx)); break;
					case 'b': lst__append(tokens, (byt*)newExecutionToken_Break(   ctx)); break;
					case 'c': lst__append(tokens, (byt*)newExecutionToken_Continue(ctx)); break;
					case 'r': lst__append(tokens, (byt*)newExecutionToken_Return(  ctx)); break;
					case 'v': lst__append(tokens, (byt*)newExecutionToken_VFC(     ctx)); break;
					//case '': lst__append(tokens, (byt*)newExecutionToken_(ctx)); break;
					//case '': lst__append(tokens, (byt*)newExecutionToken_(ctx)); break;
					//case '': lst__append(tokens, (byt*)newExecutionToken_(ctx)); break;
					//case '': lst__append(tokens, (byt*)newExecutionToken_(ctx)); break;
					//case '': lst__append(tokens, (byt*)newExecutionToken_(ctx)); break;
					//case '': lst__append(tokens, (byt*)newExecutionToken_(ctx)); break;
					//case '': lst__append(tokens, (byt*)newExecutionToken_(ctx)); break;
					case 'a': lst__append(tokens, (byt*)newExecutionToken_Assign(  ctx)); break;
					default: Tokenization__error(ctx, s("Invalid EXE STATEMENT given."));
				}
				IO__ctxt__printLF("EXE }");
			break;



			//undefined
			default: Tokenization__error(ctx, s("Invalid ROLE given."));
		}
	}

	IO__ctxt__printLF("END REACHED");

	//final result
	return tokens;
}



// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< semi-old stuff
/*
		if(Oiam__chr_str(c, v.numbers)) {
			lst__append(tokens, (byt*)newToken(TK_PP_NUM, ctx));
			ctx->preceededBySpace = false;
			continue;
		}

		//identifier or keyword
		int ident_len = read_ident(p);
		if(ident_len) {
			cur = cur->next = new_token(TK_IDENT, p, p + ident_len);
			p += cur->len;
			continue;
		}

		//punctuators
		int punct_len = read_punct(p);
		if (punct_len) {
			cur = cur->next = new_token(TK_PUNCT, p, p + punct_len);
			p += cur->len;
			continue;
		}
		Parsing__ctx__printLocationLF(ctx->pc);
		Err__error(s("Invalid syntax for preprocessing tokenization.");
	}

	//return tokens
	return tokens;
}
*/
