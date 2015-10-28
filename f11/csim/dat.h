typedef struct UOp UOp;

enum {
	OPTINVAL,
	OPTALU,
	OPTLOAD,
	OPTSTORE,
	OPTBRANCH,
};

enum {
	ALUINVAL,
	ALUSWAB,
	ALUCOM,
	ALUNEG,
	ALUADC,
	ALUSBC,
	ALUTST,
	ALUROR,
	ALUROL,
	ALUASR,
	ALUASL,
	ALUSXT,
	ALUMOV,
	ALUCMP,
	ALUADD,
	ALUSUB,
	ALUBIT,
	ALUBIC,
	ALUBIS,
	ALUMUL1,
	ALUMUL2,
	ALUASH,
	ALUASHC1,
	ALUASHC2,
	ALUASHC3,
	ALUDIV1,
	ALUDIV2,
	ALUDIV3,
	ALUXOR,
	ALUCCOP,
};
extern char *opname[];
extern char *condname[];

enum {
	CONDAL=1,
	CONDNE,
	CONDEQ,
	CONDGE,
	CONDLT,
	CONDGT,
	CONDLE,
	CONDPL,
	CONDHI,
	CONDLOS,
	CONDMI,
	CONDVC,
	CONDVS,
	CONDCC,
	CONDCS
};

struct UOp {
	uchar type, alu, byte, fl;
	uchar r[2];
	uchar d;
	ushort v;
};
#pragma varargck type "U" UOp *

extern UOp uops[];
extern int nuops;

enum {
	SRCD = 8,
	DSTA,
	DSTD,
	IMM,
	NREGS,
};

ushort (*fetch)(void);
ushort (*getpc)(void);
