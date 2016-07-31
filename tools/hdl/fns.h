void *emalloc(int);
void *erealloc(void *, int, int, int);
int yylex(void);
void error(Line *, char *, ...);
void warn(Line *, char *, ...);
int parse(char *);
ASTNode *node(int, ...);
Nodes *nlcat(Nodes *, Nodes *);
ASTNode *newscope(SymTab *, int, Symbol *);
void scopeup(void);
Symbol *decl(SymTab *, Symbol *, int, int, ASTNode *, Type *);
ASTNode *vardecl(SymTab *, ASTNode *, int, ASTNode *, Type *, ASTNode *);
Symbol *getsym(SymTab *, int, char *);
ASTNode *fsmstate(Symbol *);
void fsmstart(ASTNode *);
void fsmend(void);
void typeor(Type *, int, Type *, int, Type **, int *);
Type *type(int, ...);
void enumstart(Type *);
Type *enumend(void);
void enumdecl(Symbol *, ASTNode *);
void checksym(Symbol *);
void astprint(ASTNode *, int);
void consparse(Const *, char *);
void typecheck(ASTNode *, Type *);
void typefinal(Type *, int, Type **, int *);
ASTNode *nodedup(ASTNode *);
int consteq(Const *, Const *);
int nodeeq(ASTNode *, ASTNode *, void *);
int ptreq(ASTNode *, ASTNode *, void *);
ASTNode *mkcint(Const *);
Nodes *descend(ASTNode *, void (*pre)(ASTNode *), Nodes *(*)(ASTNode *));
ASTNode *onlyone(Nodes *);
Nodes *descendnl(Nodes *, void (*pre)(ASTNode *), Nodes *(*)(ASTNode *));
ASTNode *constfold(ASTNode *);
void compile(Nodes *);
#define nodeput free
OpData *getopdata(int);
ASTNode *fsmgoto(Symbol *);
Nodes *nl(ASTNode *);
void nlput(Nodes *);
ASTNode *fsmcompile(ASTNode *);
Nodes *nls(ASTNode *, ...);
ASTNode *mkblock(Nodes *);
Nodes *unmkblock(ASTNode *);
int descendsum(ASTNode *, int (*)(ASTNode *));
void nlprint(Nodes *, int);
Nodes *nldup(Nodes *);
void structstart(void);
void structend(Type *, int, Type **, int *, Symbol *);
void setpackdef(Nodes *, ASTNode *);
void defpackdef(ASTNode *);
ASTNode *typconc(ASTNode *);
ASTNode *nodeadd(ASTNode *, ASTNode *);
ASTNode *nodemul(ASTNode *, ASTNode *);
ASTNode *nodewidth(ASTNode *, ASTNode *);
ASTNode *nodesub(ASTNode *, ASTNode *);
ASTNode *nodeaddi(ASTNode *a, int i);
ASTNode *defaultval(Type *);
ASTNode *enumsz(Type *);
int clog2(uint);
ASTNode *semcomp(ASTNode *);
ASTNode *nodededup(ASTNode *, ASTNode *);
int clearaux(ASTNode *);
BitSet *bsnew(int);
void bsreset(BitSet *);
int bsadd(BitSet *, int);
int bstest(BitSet *, int);
int bsiter(BitSet *, int);
void bscopy(BitSet *, BitSet *);
int bscmp(BitSet *, BitSet *);
void bsunion(BitSet *, BitSet *, BitSet *);
void bsminus(BitSet *, BitSet *, BitSet *);
void bsinter(BitSet *, BitSet *, BitSet *);
int bsrem(BitSet *, int);
int bscnt(BitSet *);
BitSet* bsgrow(BitSet *, int);
BitSet* bsdup(BitSet *);
#define bsfree free
void bscntgr(BitSet *, BitSet *, int *, int *);
void addsym(SymTab *, Symbol *);
void verilog(ASTNode *);
Symbol *findclock(Symbol *);
ASTNode *dangle(ASTNode *, ASTNode *);
ASTNode *mkcast(Type *, int, ASTNode *);
