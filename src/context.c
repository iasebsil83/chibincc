//file
typedef struct {
	chr* name;
	int  file_no;
	chr* contents;

	// For #line directive
	chr* display_name;
	int  line_delta;
} File;



//member
typedef struct Member Member;
struct Member {
  Member *next;
  Type *ty;
  Token *tok; // for error message
  Token *name;
  int idx;
  int align;
  int offset;

  // Bitfield
  bool is_bitfield;
  int bit_offset;
  int bit_width;
};



//type
typedef struct Type Type;
typedef enum {
	TY_VOI,
	TY_BOO,
	TY_CHR,
	TY_SHR,
	TY_INT,
	TY_LNG,
	TY_FLT,
	TY_DBL,
	TY_ENM,
	TY_PTR,
	TY_FCT,
	TY_ARR,
	TY_VLA, // variable-length array <<<<<<<<<<< useful ?
	TY_STC
} TypeKind;

struct Type {
  TypeKind kind;
  int size;           // sizeof() value
  int align;          // alignment
  bool is_unsigned;   // unsigned or signed
  bool is_atomic;     // true if _Atomic
  Type *origin;       // for type compatibility check

  // Pointer-to or array-of type. We intentionally use the same member
  // to represent pointer/array duality in C.
  //
  // In many contexts in which a pointer is expected, we examine this
  // member instead of "kind" member to determine whether a type is a
  // pointer or not. That means in many contexts "array of T" is
  // naturally handled as if it were "pointer to T", as required by
  // the C spec.
  Type *base;

  // Declaration
  Token *name;
  Token *name_pos;

  // Array
  int array_len;

  // Variable-length array
  Node *vla_len; // # of elements
  Obj *vla_size; // sizeof() value

  // Struct
  Member *members;
  bool is_flexible;
  bool is_packed;

  // Function type
  Type *return_ty;
  Type *params;
  bool is_variadic;
  Type *next;
};



//hideset
typedef struct Hideset Hideset;
struct Hideset {
  Hideset *next;
  char *name;
};



//relocation ?required
typedef struct Relocation Relocation;
struct Relocation {
  Relocation* next;
  int         offset;
  chr**       label;
  lng         addend;
};



//obj ?required
typedef struct Obj Obj;
struct Obj {
  Obj*   next;
  chr*   name;     // Variable name
  Type*  ty;       // Type
  Token* tok;      // representative token
  boo    is_local; // local or global/function
  int    align;    // alignment

  // Local variable
  int offset;

  // Global variable or function
  bool is_function;
  bool is_definition;
  bool is_static;

  // Global variable
  boo         is_tentative;
  boo         is_tls;
  chr*        init_data;
  Relocation* rel;

  // Function
  boo   is_inline;
  Obj*  params;
  Node* body;
  Obj*  locals;
  Obj*  va_area;
  Obj*  alloca_bottom;
  int   stack_size;

  // Static inline function
  boo      is_live;
  boo      is_root;
  tab_str* refs;
};



//AST nodes ?required
typedef enum {
  ND_NULL_EXPR, // Do nothing
  ND_ADD,       // +
  ND_SUB,       // -
  ND_MUL,       // *
  ND_DIV,       // /
  ND_NEG,       // unary -
  ND_MOD,       // %
  ND_BITAND,    // &
  ND_BITOR,     // |
  ND_BITXOR,    // ^
  ND_SHL,       // <<
  ND_SHR,       // >>
  ND_EQ,        // ==
  ND_NE,        // !=
  ND_LT,        // <
  ND_LE,        // <=
  ND_ASSIGN,    // =
  ND_COND,      // ?:
  ND_COMMA,     // ,
  ND_MEMBER,    // . (struct member access)
  ND_ADDR,      // unary &
  ND_DEREF,     // unary *
  ND_NOT,       // !
  ND_BITNOT,    // ~
  ND_LOGAND,    // &&
  ND_LOGOR,     // ||
  ND_RETURN,    // "return"
  ND_IF,        // "if"
  ND_FOR,       // "for" or "while"
  ND_DO,        // "do"
  ND_SWITCH,    // "switch"
  ND_CASE,      // "case"
  ND_BLOCK,     // { ... }
  ND_GOTO,      // "goto"
  ND_GOTO_EXPR, // "goto" labels-as-values
  ND_LABEL,     // Labeled statement
  ND_LABEL_VAL, // [GNU] Labels-as-values
  ND_FUNCALL,   // Function call
  ND_EXPR_STMT, // Expression statement
  ND_STMT_EXPR, // Statement expression
  ND_VAR,       // Variable
  ND_VLA_PTR,   // VLA designator
  ND_NUM,       // Integer
  ND_CAST,      // Type cast
  ND_MEMZERO,   // Zero-clear a stack variable
  ND_ASM,       // "asm"
  ND_CAS,       // Atomic compare-and-swap
  ND_EXCH,      // Atomic exchange
} NodeKind;

typedef struct Node Node;
struct Node {
  NodeKind kind; // Node kind
  Node *next;    // Next node
  Type *ty;      // Type, e.g. int or pointer to int
  Token *tok;    // Representative token

  Node *lhs;     // Left-hand side
  Node *rhs;     // Right-hand side

  // "if" or "for" statement
  Node *cond;
  Node *then;
  Node *els;
  Node *init;
  Node *inc;

  // "break" and "continue" labels
  char *brk_label;
  char *cont_label;

  // Block or statement expression
  Node *body;

  // Struct member access
  Member *member;

  // Function call
  Type *func_ty;
  Node *args;
  bool pass_by_stack;
  Obj *ret_buffer;

  // Goto or labeled statement, or labels-as-values
  char *label;
  char *unique_label;
  Node *goto_next;

  // Switch
  Node *case_next;
  Node *default_case;

  // Case
  long begin;
  long end;

  // "asm" string literal
  char *asm_str;

  // Atomic compare-and-swap
  Node *cas_addr;
  Node *cas_old;
  Node *cas_new;

  // Atomic op= operators
  Obj *atomic_addr;
  Node *atomic_expr;

  // Variable
  Obj *var;

  // Numeric literal
  int64_t val;
  long double fval;
};



//hasmaps ?required
typedef struct {
  char *key;
  int keylen;
  void *val;
} HashEntry;

typedef struct {
  HashEntry *buckets;
  int capacity;
  int used;
} HashMap;
























// ---------------- DEFINITIONS ----------------

//potential issue localization
typedef struct {
	str* filename;
	ulng lineNbr;
	ulng columnNbr;
} loc;



//parsing contexts
typedef struct {
	boo  atBOL
	boo  preceededBySpace;
	loc* currentLocation;
} PPCcontext;



//token
const byt TOKEN__IDENTIFIER = '\x00';
const byt TOKEN__PUNCTUATOR = '\x01';
const byt TOKEN__KEYWORD    = '\x02';
const byt TOKEN__LIT_STR    = '\x03';
const byt TOKEN__LIT_NUM    = '\x04';
const byt TOKEN__PP_NUM     = '\x05'; //preprocessing numbers
const byt TOKEN__EOF        = '\x06';
typedef struct {
	byt  id;
	ulng value;
	loc* location;
	boo  atBOL; //at Beginning Of Line
	boo  preceededBySpace;
} Token;






// ---------------- TOOLS ----------------

//locations
void loc__print(loc* l) {
	str* lineNbrStr   = ulng__toStr(l->lineNbr);
	str* columnNbrStr = ulng__toStr(l->columnNbr);

	//output
	IO__print(l->filename);
	IO__printChr(':');
	IO__print(lineNbrStr);
	IO__printChr(':');
	IO__print(columnNbrStr);

	//free
	str__free(lineNbrStr);
	str__free(columnNbrStr);
}
