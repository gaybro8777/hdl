typedef struct Line Line;
typedef struct ASTNode ASTNode;
typedef struct Const Const;
typedef struct Symbol Symbol;
typedef struct SymTab SymTab;
typedef struct Type Type;

enum {
	SYMHASH = 128,
};

struct Line {
	char *filen;
	int lineno;
};

struct Type {
	uchar t, sign;
	ASTNode *sz, *lo, *hi;
	Type *elem;
	Type *next;
};

enum {
	TYPINVALID,
	TYPUNSZ,
	TYPBITS,
	TYPBITV,
	TYPREAL,
	TYPMEM,
	TYPEVENT,
};

extern Type *inttype, *realtype, *timetype, *bittype, *sbittype, *unsztype, *eventtype;

struct Const {
	mpint *n, *x;
	uchar sz, sign;
};

struct ASTNode {
	int t;
	union {
		struct {
			int op;
			ASTNode *n1, *n2, *n3, *n4;
		};
		ASTNode *n;
		int i;
		double d;
		char *str;
		Const cons;
		Symbol *sym;
		struct {
			SymTab *st;
			ASTNode *n;
		} sc;
		struct {
			char *name;
			ASTNode *n;
		} pcon;
		struct {
			char *name;
			ASTNode *param;
			ASTNode *ports;
		} minst;
	};
	int isconst;
	Type *type;
	ASTNode *attrs;
	ASTNode *next, **last;
	Line;
};

struct Symbol {
	char *name;
	int t;
	Line;
	Symbol *next, *portnext;
	SymTab *st;
	ASTNode *n;
	Type *type;
	int dir;
	ASTNode *attrs;
};

enum {
	SYMNONE,
	SYMNET,
	SYMREG,
	SYMPARAM,
	SYMLPARAM,
	SYMFUNC,
	SYMTASK,
	SYMBLOCK,
	SYMMODULE,
	SYMPORT,
	SYMEVENT,
	SYMGENVAR,
	SYMMINST,
};

enum {
	PORTUND = 0,
	PORTIN = 1,
	PORTIO = 2,
	PORTOUT = 3,
	PORTNET = 4,
	PORTREG = 8,
};

struct SymTab {
	Symbol *sym[SYMHASH];
	SymTab *up;
	Symbol *ports, **lastport;
};
extern SymTab *scope;
extern SymTab global;

enum {
	ASTINVAL,
	ASTALWAYS,
	ASTASS,
	ASTCASS,
	ASTAT,
	ASTATTR,
	ASTBIN,
	ASTBLOCK,
	ASTCALL,
	ASTCASE,
	ASTCASIT,
	ASTCAT,
	ASTCINT,
	ASTCONST,
	ASTCREAL,
	ASTDASS,
	ASTDELAY,
	ASTDISABLE,
	ASTFOR,
	ASTFORK,
	ASTFUNC,
	ASTGENCASE,
	ASTGENIF,
	ASTGENFOR,
	ASTHIER,
	ASTINITIAL,
	ASTMODULE,
	ASTMINSTN,
	ASTMINSTO,
	ASTIDX,
	ASTIF,
	ASTPCON,
	ASTREPEAT,
	ASTSTRING,
	ASTSYM,
	ASTTASK,
	ASTTCALL,
	ASTTERN,
	ASTTRIG,
	ASTUN,
	ASTWAIT,
	ASTWHILE,
};

enum {
	OPINVAL,
	OPADD,
	OPAND,
	OPASL,
	OPASR,
	OPDIV,
	OPEQ,
	OPEQS,
	OPEVOR,
	OPEXP,
	OPGE,
	OPGT,
	OPLAND,
	OPLE,
	OPLNOT,
	OPLOR,
	OPLSL,
	OPLSR,
	OPLT,
	OPMOD,
	OPMUL,
	OPNEGEDGE,
	OPNEQ,
	OPNEQS,
	OPNOT,
	OPNXOR,
	OPOR,
	OPPOSEDGE,
	OPRAND,
	OPRNAND,
	OPRNOR,
	OPROR,
	OPRXNOR,
	OPRXOR,
	OPSUB,
	OPUMINUS,
	OPUPLUS,
	OPXOR,
	OPMAX,
};

#pragma varargck type "A" int
#pragma varargck type "O" int
extern Line *curline;
#define NOPE (abort(), nil)
#define lint 1
#define lerror error
