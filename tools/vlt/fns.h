void *emalloc(int);
int parse(char *);
int yylex(void);
void error(Line *, char *, ...);
void lexinit(void);
ASTNode *node(int, ...);
ASTNode *nodecat(ASTNode *, ASTNode *);
void astinit(void);
ASTNode *newscope(int, Symbol *, ASTNode *, Type *);
void scopeup(void);
Symbol *getsym(SymTab *, int, char *);
Type *type(int, ...);
int asteq(ASTNode*, ASTNode*);
Symbol *decl(Symbol *, int, ASTNode *, Type *, ASTNode *);
Symbol *portdecl(Symbol *, int, ASTNode *, Type *, ASTNode *);
void typecheck(ASTNode *, Type *);
ASTNode *cfold(ASTNode *, Type *);
ASTNode *repl(ASTNode *, ASTNode *);
void typeok(Line *, Type *);
void clearmarks(void);
int markstr(char *);
int strmark(char *);
uint hash(char *);
ASTNode *makenumb(Const *, int, Const *);
int cfgparse(char *);
void cfgerror(Line *, char *, ...);
int expect(int);
void findmod(CModule *);
void matchports(CModule *);
CWire *getwire(CDesign *, char *);
int clog2(uint);
