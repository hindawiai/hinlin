<शैली गुरु>
/*
 * Copyright (C) 1995-1999 Gary Thomas, Paul Mackerras, Cort Dougan.
 */
#अगर_अघोषित _ASM_POWERPC_PPC_ASM_H
#घोषणा _ASM_POWERPC_PPC_ASM_H

#समावेश <linux/stringअगरy.h>
#समावेश <यंत्र/यंत्र-compat.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/feature-fixups.h>

#अगर_घोषित __ASSEMBLY__

#घोषणा SZL			(BITS_PER_LONG/8)

/*
 * Macros क्रम storing रेजिस्टरs पूर्णांकo and loading रेजिस्टरs from
 * exception frames.
 */
#अगर_घोषित __घातerpc64__
#घोषणा SAVE_GPR(n, base)	std	n,GPR0+8*(n)(base)
#घोषणा REST_GPR(n, base)	ld	n,GPR0+8*(n)(base)
#घोषणा SAVE_NVGPRS(base)	SAVE_8GPRS(14, base); SAVE_10GPRS(22, base)
#घोषणा REST_NVGPRS(base)	REST_8GPRS(14, base); REST_10GPRS(22, base)
#अन्यथा
#घोषणा SAVE_GPR(n, base)	stw	n,GPR0+4*(n)(base)
#घोषणा REST_GPR(n, base)	lwz	n,GPR0+4*(n)(base)
#घोषणा SAVE_NVGPRS(base)	sपंचांगw	13, GPR0+4*13(base)
#घोषणा REST_NVGPRS(base)	lmw	13, GPR0+4*13(base)
#पूर्ण_अगर

#घोषणा SAVE_2GPRS(n, base)	SAVE_GPR(n, base); SAVE_GPR(n+1, base)
#घोषणा SAVE_4GPRS(n, base)	SAVE_2GPRS(n, base); SAVE_2GPRS(n+2, base)
#घोषणा SAVE_8GPRS(n, base)	SAVE_4GPRS(n, base); SAVE_4GPRS(n+4, base)
#घोषणा SAVE_10GPRS(n, base)	SAVE_8GPRS(n, base); SAVE_2GPRS(n+8, base)
#घोषणा REST_2GPRS(n, base)	REST_GPR(n, base); REST_GPR(n+1, base)
#घोषणा REST_4GPRS(n, base)	REST_2GPRS(n, base); REST_2GPRS(n+2, base)
#घोषणा REST_8GPRS(n, base)	REST_4GPRS(n, base); REST_4GPRS(n+4, base)
#घोषणा REST_10GPRS(n, base)	REST_8GPRS(n, base); REST_2GPRS(n+8, base)

#घोषणा SAVE_FPR(n, base)	stfd	n,8*TS_FPRWIDTH*(n)(base)
#घोषणा SAVE_2FPRS(n, base)	SAVE_FPR(n, base); SAVE_FPR(n+1, base)
#घोषणा SAVE_4FPRS(n, base)	SAVE_2FPRS(n, base); SAVE_2FPRS(n+2, base)
#घोषणा SAVE_8FPRS(n, base)	SAVE_4FPRS(n, base); SAVE_4FPRS(n+4, base)
#घोषणा SAVE_16FPRS(n, base)	SAVE_8FPRS(n, base); SAVE_8FPRS(n+8, base)
#घोषणा SAVE_32FPRS(n, base)	SAVE_16FPRS(n, base); SAVE_16FPRS(n+16, base)
#घोषणा REST_FPR(n, base)	lfd	n,8*TS_FPRWIDTH*(n)(base)
#घोषणा REST_2FPRS(n, base)	REST_FPR(n, base); REST_FPR(n+1, base)
#घोषणा REST_4FPRS(n, base)	REST_2FPRS(n, base); REST_2FPRS(n+2, base)
#घोषणा REST_8FPRS(n, base)	REST_4FPRS(n, base); REST_4FPRS(n+4, base)
#घोषणा REST_16FPRS(n, base)	REST_8FPRS(n, base); REST_8FPRS(n+8, base)
#घोषणा REST_32FPRS(n, base)	REST_16FPRS(n, base); REST_16FPRS(n+16, base)

#घोषणा SAVE_VR(n,b,base)	li b,16*(n);  stvx n,base,b
#घोषणा SAVE_2VRS(n,b,base)	SAVE_VR(n,b,base); SAVE_VR(n+1,b,base)
#घोषणा SAVE_4VRS(n,b,base)	SAVE_2VRS(n,b,base); SAVE_2VRS(n+2,b,base)
#घोषणा SAVE_8VRS(n,b,base)	SAVE_4VRS(n,b,base); SAVE_4VRS(n+4,b,base)
#घोषणा SAVE_16VRS(n,b,base)	SAVE_8VRS(n,b,base); SAVE_8VRS(n+8,b,base)
#घोषणा SAVE_32VRS(n,b,base)	SAVE_16VRS(n,b,base); SAVE_16VRS(n+16,b,base)
#घोषणा REST_VR(n,b,base)	li b,16*(n); lvx n,base,b
#घोषणा REST_2VRS(n,b,base)	REST_VR(n,b,base); REST_VR(n+1,b,base)
#घोषणा REST_4VRS(n,b,base)	REST_2VRS(n,b,base); REST_2VRS(n+2,b,base)
#घोषणा REST_8VRS(n,b,base)	REST_4VRS(n,b,base); REST_4VRS(n+4,b,base)
#घोषणा REST_16VRS(n,b,base)	REST_8VRS(n,b,base); REST_8VRS(n+8,b,base)
#घोषणा REST_32VRS(n,b,base)	REST_16VRS(n,b,base); REST_16VRS(n+16,b,base)

#अगर_घोषित __BIG_ENDIAN__
#घोषणा STXVD2X_ROT(n,b,base)		STXVD2X(n,b,base)
#घोषणा LXVD2X_ROT(n,b,base)		LXVD2X(n,b,base)
#अन्यथा
#घोषणा STXVD2X_ROT(n,b,base)		XXSWAPD(n,n);		\
					STXVD2X(n,b,base);	\
					XXSWAPD(n,n)

#घोषणा LXVD2X_ROT(n,b,base)		LXVD2X(n,b,base);	\
					XXSWAPD(n,n)
#पूर्ण_अगर
/* Save the lower 32 VSRs in the thपढ़ो VSR region */
#घोषणा SAVE_VSR(n,b,base)	li b,16*(n);  STXVD2X_ROT(n,R##base,R##b)
#घोषणा SAVE_2VSRS(n,b,base)	SAVE_VSR(n,b,base); SAVE_VSR(n+1,b,base)
#घोषणा SAVE_4VSRS(n,b,base)	SAVE_2VSRS(n,b,base); SAVE_2VSRS(n+2,b,base)
#घोषणा SAVE_8VSRS(n,b,base)	SAVE_4VSRS(n,b,base); SAVE_4VSRS(n+4,b,base)
#घोषणा SAVE_16VSRS(n,b,base)	SAVE_8VSRS(n,b,base); SAVE_8VSRS(n+8,b,base)
#घोषणा SAVE_32VSRS(n,b,base)	SAVE_16VSRS(n,b,base); SAVE_16VSRS(n+16,b,base)
#घोषणा REST_VSR(n,b,base)	li b,16*(n); LXVD2X_ROT(n,R##base,R##b)
#घोषणा REST_2VSRS(n,b,base)	REST_VSR(n,b,base); REST_VSR(n+1,b,base)
#घोषणा REST_4VSRS(n,b,base)	REST_2VSRS(n,b,base); REST_2VSRS(n+2,b,base)
#घोषणा REST_8VSRS(n,b,base)	REST_4VSRS(n,b,base); REST_4VSRS(n+4,b,base)
#घोषणा REST_16VSRS(n,b,base)	REST_8VSRS(n,b,base); REST_8VSRS(n+8,b,base)
#घोषणा REST_32VSRS(n,b,base)	REST_16VSRS(n,b,base); REST_16VSRS(n+16,b,base)

/*
 * b = base रेजिस्टर क्रम addressing, o = base offset from रेजिस्टर of 1st EVR
 * n = first EVR, s = scratch
 */
#घोषणा SAVE_EVR(n,s,b,o)	evmergehi s,s,n; stw s,o+4*(n)(b)
#घोषणा SAVE_2EVRS(n,s,b,o)	SAVE_EVR(n,s,b,o); SAVE_EVR(n+1,s,b,o)
#घोषणा SAVE_4EVRS(n,s,b,o)	SAVE_2EVRS(n,s,b,o); SAVE_2EVRS(n+2,s,b,o)
#घोषणा SAVE_8EVRS(n,s,b,o)	SAVE_4EVRS(n,s,b,o); SAVE_4EVRS(n+4,s,b,o)
#घोषणा SAVE_16EVRS(n,s,b,o)	SAVE_8EVRS(n,s,b,o); SAVE_8EVRS(n+8,s,b,o)
#घोषणा SAVE_32EVRS(n,s,b,o)	SAVE_16EVRS(n,s,b,o); SAVE_16EVRS(n+16,s,b,o)
#घोषणा REST_EVR(n,s,b,o)	lwz s,o+4*(n)(b); evmergelo n,s,n
#घोषणा REST_2EVRS(n,s,b,o)	REST_EVR(n,s,b,o); REST_EVR(n+1,s,b,o)
#घोषणा REST_4EVRS(n,s,b,o)	REST_2EVRS(n,s,b,o); REST_2EVRS(n+2,s,b,o)
#घोषणा REST_8EVRS(n,s,b,o)	REST_4EVRS(n,s,b,o); REST_4EVRS(n+4,s,b,o)
#घोषणा REST_16EVRS(n,s,b,o)	REST_8EVRS(n,s,b,o); REST_8EVRS(n+8,s,b,o)
#घोषणा REST_32EVRS(n,s,b,o)	REST_16EVRS(n,s,b,o); REST_16EVRS(n+16,s,b,o)

/* Macros to adjust thपढ़ो priority क्रम hardware multithपढ़ोing */
#घोषणा HMT_VERY_LOW	or	31,31,31	# very low priority
#घोषणा HMT_LOW		or	1,1,1
#घोषणा HMT_MEDIUM_LOW  or	6,6,6		# medium low priority
#घोषणा HMT_MEDIUM	or	2,2,2
#घोषणा HMT_MEDIUM_HIGH or	5,5,5		# medium high priority
#घोषणा HMT_HIGH	or	3,3,3
#घोषणा HMT_EXTRA_HIGH	or	7,7,7		# घातer7 only

#अगर_घोषित CONFIG_PPC64
#घोषणा ULONG_SIZE 	8
#अन्यथा
#घोषणा ULONG_SIZE	4
#पूर्ण_अगर
#घोषणा __VCPU_GPR(n)	(VCPU_GPRS + (n * ULONG_SIZE))
#घोषणा VCPU_GPR(n)	__VCPU_GPR(__REG_##n)

#अगर_घोषित __KERNEL__

/*
 * We use __घातerpc64__ here because we want the compat VDSO to use the 32-bit
 * version below in the अन्यथा हाल of the अगरdef.
 */
#अगर_घोषित __घातerpc64__

#घोषणा STACKFRAMESIZE 256
#घोषणा __STK_REG(i)   (112 + ((i)-14)*8)
#घोषणा STK_REG(i)     __STK_REG(__REG_##i)

#अगर_घोषित PPC64_ELF_ABI_v2
#घोषणा STK_GOT		24
#घोषणा __STK_PARAM(i)	(32 + ((i)-3)*8)
#अन्यथा
#घोषणा STK_GOT		40
#घोषणा __STK_PARAM(i)	(48 + ((i)-3)*8)
#पूर्ण_अगर
#घोषणा STK_PARAM(i)	__STK_PARAM(__REG_##i)

#अगर_घोषित PPC64_ELF_ABI_v2

#घोषणा _GLOBAL(name) \
	.align 2 ; \
	.type name,@function; \
	.globl name; \
name:

#घोषणा _GLOBAL_TOC(name) \
	.align 2 ; \
	.type name,@function; \
	.globl name; \
name: \
0:	addis r2,r12,(.TOC.-0b)@ha; \
	addi r2,r2,(.TOC.-0b)@l; \
	.localentry name,.-name

#घोषणा DOTSYM(a)	a

#अन्यथा

#घोषणा XGLUE(a,b) a##b
#घोषणा GLUE(a,b) XGLUE(a,b)

#घोषणा _GLOBAL(name) \
	.align 2 ; \
	.globl name; \
	.globl GLUE(.,name); \
	.pushsection ".opd","aw"; \
name: \
	.quad GLUE(.,name); \
	.quad .TOC.@tocbase; \
	.quad 0; \
	.popsection; \
	.type GLUE(.,name),@function; \
GLUE(.,name):

#घोषणा _GLOBAL_TOC(name) _GLOBAL(name)

#घोषणा DOTSYM(a)	GLUE(.,a)

#पूर्ण_अगर

#अन्यथा /* 32-bit */

#घोषणा _ENTRY(n)	\
	.globl n;	\
n:

#घोषणा _GLOBAL(n)	\
	.stअसल __stringअगरy(n:F-1),N_FUN,0,0,n;\
	.globl n;	\
n:

#घोषणा _GLOBAL_TOC(name) _GLOBAL(name)

#घोषणा DOTSYM(a)	a

#पूर्ण_अगर

/*
 * __kprobes (the C annotation) माला_दो the symbol पूर्णांकo the .kprobes.text
 * section, which माला_लो emitted at the end of regular text.
 *
 * _ASM_NOKPROBE_SYMBOL and NOKPROBE_SYMBOL just adds the symbol to
 * a blacklist. The क्रमmer is क्रम core kprobe functions/data, the
 * latter is क्रम those that incdentially must be excluded from probing
 * and allows them to be linked at more optimal location within text.
 */
#अगर_घोषित CONFIG_KPROBES
#घोषणा _ASM_NOKPROBE_SYMBOL(entry)			\
	.pushsection "_kprobe_blacklist","aw";		\
	PPC_LONG (entry) ;				\
	.popsection
#अन्यथा
#घोषणा _ASM_NOKPROBE_SYMBOL(entry)
#पूर्ण_अगर

#घोषणा FUNC_START(name)	_GLOBAL(name)
#घोषणा FUNC_END(name)

/* 
 * LOAD_REG_IMMEDIATE(rn, expr)
 *   Loads the value of the स्थिरant expression 'expr' into register 'rn'
 *   using immediate inकाष्ठाions only.  Use this when it's important not
 *   to reference other data (i.e. on ppc64 when the TOC poपूर्णांकer is not
 *   valid) and when 'expr' is a स्थिरant or असलolute address.
 *
 * LOAD_REG_ADDR(rn, name)
 *   Loads the address of label 'name' into register 'rn'.  Use this when
 *   you करोn't particularly need immediate inकाष्ठाions only, but you need
 *   the whole address in one रेजिस्टर (e.g. it's a काष्ठाure address and
 *   you want to access various offsets within it).  On ppc32 this is
 *   identical to LOAD_REG_IMMEDIATE.
 *
 * LOAD_REG_ADDR_PIC(rn, name)
 *   Loads the address of label 'name' into register 'run'. Use this when
 *   the kernel करोesn't run at the linked or relocated address. Please
 *   note that this macro will clobber the lr रेजिस्टर.
 *
 * LOAD_REG_ADDRBASE(rn, name)
 * ADDROFF(name)
 *   LOAD_REG_ADDRBASE loads part of the address of label 'name' पूर्णांकo
 *   रेजिस्टर 'rn'.  ADDROFF(name) वापसs the reमुख्यder of the address as
 *   a स्थिरant expression.  ADDROFF(name) is a चिन्हित expression < 16 bits
 *   in size, so is suitable क्रम use directly as an offset in load and store
 *   inकाष्ठाions.  Use this when loading/storing a single word or less as:
 *      LOAD_REG_ADDRBASE(rX, name)
 *      ld	rY,ADDROFF(name)(rX)
 */

/* Be careful, this will clobber the lr रेजिस्टर. */
#घोषणा LOAD_REG_ADDR_PIC(reg, name)		\
	bl	0f;				\
0:	mflr	reg;				\
	addis	reg,reg,(name - 0b)@ha;		\
	addi	reg,reg,(name - 0b)@l;

#अगर defined(__घातerpc64__) && defined(HAVE_AS_ATHIGH)
#घोषणा __AS_ATHIGH high
#अन्यथा
#घोषणा __AS_ATHIGH h
#पूर्ण_अगर

.macro __LOAD_REG_IMMEDIATE_32 r, x
	.अगर (\ष) >= 0x8000 || (\ष) < -0x8000
		lis \ल, (\ष)@__AS_ATHIGH
		.अगर (\ष) & 0xffff != 0
			ori \ल, \ल, (\ष)@l
		.endअगर
	.अन्यथा
		li \ल, (\ष)@l
	.endअगर
.endm

.macro __LOAD_REG_IMMEDIATE r, x
	.अगर (\ष) >= 0x80000000 || (\ष) < -0x80000000
		__LOAD_REG_IMMEDIATE_32 \ल, (\ष) >> 32
		sldi	\ल, \ल, 32
		.अगर (\ष) & 0xffff0000 != 0
			oris \ल, \ल, (\ष)@__AS_ATHIGH
		.endअगर
		.अगर (\ष) & 0xffff != 0
			ori \ल, \ल, (\ष)@l
		.endअगर
	.अन्यथा
		__LOAD_REG_IMMEDIATE_32 \ल, \ष
	.endअगर
.endm

#अगर_घोषित __घातerpc64__

#घोषणा LOAD_REG_IMMEDIATE(reg, expr) __LOAD_REG_IMMEDIATE reg, expr

#घोषणा LOAD_REG_IMMEDIATE_SYM(reg, पंचांगp, expr)	\
	lis	पंचांगp, (expr)@highest;		\
	lis	reg, (expr)@__AS_ATHIGH;	\
	ori	पंचांगp, पंचांगp, (expr)@higher;	\
	ori	reg, reg, (expr)@l;		\
	rldimi	reg, पंचांगp, 32, 0

#घोषणा LOAD_REG_ADDR(reg,name)			\
	ld	reg,name@got(r2)

#घोषणा LOAD_REG_ADDRBASE(reg,name)	LOAD_REG_ADDR(reg,name)
#घोषणा ADDROFF(name)			0

/* offsets क्रम stack frame layout */
#घोषणा LRSAVE	16

#अन्यथा /* 32-bit */

#घोषणा LOAD_REG_IMMEDIATE(reg, expr) __LOAD_REG_IMMEDIATE_32 reg, expr

#घोषणा LOAD_REG_IMMEDIATE_SYM(reg,expr)		\
	lis	reg,(expr)@ha;		\
	addi	reg,reg,(expr)@l;

#घोषणा LOAD_REG_ADDR(reg,name)		LOAD_REG_IMMEDIATE_SYM(reg, name)

#घोषणा LOAD_REG_ADDRBASE(reg, name)	lis	reg,name@ha
#घोषणा ADDROFF(name)			name@l

/* offsets क्रम stack frame layout */
#घोषणा LRSAVE	4

#पूर्ण_अगर

/* various errata or part fixups */
#अगर defined(CONFIG_PPC_CELL) || defined(CONFIG_PPC_FSL_BOOK3E)
#घोषणा MFTB(dest)			\
90:	mfspr dest, SPRN_TBRL;		\
BEGIN_FTR_SECTION_NESTED(96);		\
	cmpwi dest,0;			\
	beq-  90b;			\
END_FTR_SECTION_NESTED(CPU_FTR_CELL_TB_BUG, CPU_FTR_CELL_TB_BUG, 96)
#अन्यथा
#घोषणा MFTB(dest)			MFTBL(dest)
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_8xx
#घोषणा MFTBL(dest)			mftb dest
#घोषणा MFTBU(dest)			mftbu dest
#अन्यथा
#घोषणा MFTBL(dest)			mfspr dest, SPRN_TBRL
#घोषणा MFTBU(dest)			mfspr dest, SPRN_TBRU
#पूर्ण_अगर

#अगर_अघोषित CONFIG_SMP
#घोषणा TLBSYNC
#अन्यथा
#घोषणा TLBSYNC		tlbsync; sync
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC64
#घोषणा MTOCRF(FXM, RS)			\
	BEGIN_FTR_SECTION_NESTED(848);	\
	mtcrf	(FXM), RS;		\
	FTR_SECTION_ELSE_NESTED(848);	\
	mtocrf (FXM), RS;		\
	ALT_FTR_SECTION_END_NESTED_IFCLR(CPU_FTR_NOEXECUTE, 848)
#पूर्ण_अगर

/*
 * This inकाष्ठाion is not implemented on the PPC 603 or 601; however, on
 * the 403GCX and 405GP tlbia IS defined and tlbie is not.
 * All of these inकाष्ठाions exist in the 8xx, they have magical घातers,
 * and they must be used.
 */

#अगर !defined(CONFIG_4xx) && !defined(CONFIG_PPC_8xx)
#घोषणा tlbia					\
	li	r4,1024;			\
	mtctr	r4;				\
	lis	r4,KERNELBASE@h;		\
	.machine push;				\
	.machine "power4";			\
0:	tlbie	r4;				\
	.machine pop;				\
	addi	r4,r4,0x1000;			\
	bdnz	0b
#पूर्ण_अगर


#अगर_घोषित CONFIG_IBM440EP_ERR42
#घोषणा PPC440EP_ERR42 isync
#अन्यथा
#घोषणा PPC440EP_ERR42
#पूर्ण_अगर

/* The following stops all load and store data streams associated with stream
 * ID (ie. streams created explicitly).  The embedded and server mnemonics क्रम
 * dcbt are dअगरferent so this must only be used क्रम server.
 */
#घोषणा DCBT_BOOK3S_STOP_ALL_STREAM_IDS(scratch)	\
       lis     scratch,0x60000000@h;			\
       dcbt    0,scratch,0b01010

/*
 * toreal/fromreal/tophys/tovirt macros. 32-bit BookE makes them
 * keep the address पूर्णांकact to be compatible with code shared with
 * 32-bit classic.
 *
 * On the other hand, I find it useful to have them behave as expected
 * by their name (ie always करो the addition) on 64-bit BookE
 */
#अगर defined(CONFIG_BOOKE) && !defined(CONFIG_PPC64)
#घोषणा toreal(rd)
#घोषणा fromreal(rd)

/*
 * We use addis to ensure compatibility with the "classic" ppc versions of
 * these macros, which use rs = 0 to get the tophys offset in rd, rather than
 * converting the address in r0, and so this version has to करो that too
 * (i.e. set रेजिस्टर rd to 0 when rs == 0).
 */
#घोषणा tophys(rd,rs)				\
	addis	rd,rs,0

#घोषणा tovirt(rd,rs)				\
	addis	rd,rs,0

#या_अगर defined(CONFIG_PPC64)
#घोषणा toreal(rd)		/* we can access c000... in real mode */
#घोषणा fromreal(rd)

#घोषणा tophys(rd,rs)                           \
	clrldi	rd,rs,2

#घोषणा tovirt(rd,rs)                           \
	rotldi	rd,rs,16;			\
	ori	rd,rd,((KERNELBASE>>48)&0xFFFF);\
	rotldi	rd,rd,48
#अन्यथा
#घोषणा toreal(rd)	tophys(rd,rd)
#घोषणा fromreal(rd)	tovirt(rd,rd)

#घोषणा tophys(rd, rs)	addis	rd, rs, -PAGE_OFFSET@h
#घोषणा tovirt(rd, rs)	addis	rd, rs, PAGE_OFFSET@h
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_BOOK3S_64
#घोषणा MTMSRD(r)	mपंचांगsrd	r
#घोषणा MTMSR_EERI(reg)	mपंचांगsrd	reg,1
#अन्यथा
#घोषणा MTMSRD(r)	mपंचांगsr	r
#घोषणा MTMSR_EERI(reg)	mपंचांगsr	reg
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */

/* The boring bits... */

/* Condition Register Bit Fields */

#घोषणा	cr0	0
#घोषणा	cr1	1
#घोषणा	cr2	2
#घोषणा	cr3	3
#घोषणा	cr4	4
#घोषणा	cr5	5
#घोषणा	cr6	6
#घोषणा	cr7	7


/*
 * General Purpose Registers (GPRs)
 *
 * The lower हाल r0-r31 should be used in preference to the upper
 * हाल R0-R31 as they provide more error checking in the assembler.
 * Use R0-31 only when really nessesary.
 */

#घोषणा	r0	%r0
#घोषणा	r1	%r1
#घोषणा	r2	%r2
#घोषणा	r3	%r3
#घोषणा	r4	%r4
#घोषणा	r5	%r5
#घोषणा	r6	%r6
#घोषणा	r7	%r7
#घोषणा	r8	%r8
#घोषणा	r9	%r9
#घोषणा	r10	%r10
#घोषणा	r11	%r11
#घोषणा	r12	%r12
#घोषणा	r13	%r13
#घोषणा	r14	%r14
#घोषणा	r15	%r15
#घोषणा	r16	%r16
#घोषणा	r17	%r17
#घोषणा	r18	%r18
#घोषणा	r19	%r19
#घोषणा	r20	%r20
#घोषणा	r21	%r21
#घोषणा	r22	%r22
#घोषणा	r23	%r23
#घोषणा	r24	%r24
#घोषणा	r25	%r25
#घोषणा	r26	%r26
#घोषणा	r27	%r27
#घोषणा	r28	%r28
#घोषणा	r29	%r29
#घोषणा	r30	%r30
#घोषणा	r31	%r31


/* Floating Poपूर्णांक Registers (FPRs) */

#घोषणा	fr0	0
#घोषणा	fr1	1
#घोषणा	fr2	2
#घोषणा	fr3	3
#घोषणा	fr4	4
#घोषणा	fr5	5
#घोषणा	fr6	6
#घोषणा	fr7	7
#घोषणा	fr8	8
#घोषणा	fr9	9
#घोषणा	fr10	10
#घोषणा	fr11	11
#घोषणा	fr12	12
#घोषणा	fr13	13
#घोषणा	fr14	14
#घोषणा	fr15	15
#घोषणा	fr16	16
#घोषणा	fr17	17
#घोषणा	fr18	18
#घोषणा	fr19	19
#घोषणा	fr20	20
#घोषणा	fr21	21
#घोषणा	fr22	22
#घोषणा	fr23	23
#घोषणा	fr24	24
#घोषणा	fr25	25
#घोषणा	fr26	26
#घोषणा	fr27	27
#घोषणा	fr28	28
#घोषणा	fr29	29
#घोषणा	fr30	30
#घोषणा	fr31	31

/* AltiVec Registers (VPRs) */

#घोषणा	v0	0
#घोषणा	v1	1
#घोषणा	v2	2
#घोषणा	v3	3
#घोषणा	v4	4
#घोषणा	v5	5
#घोषणा	v6	6
#घोषणा	v7	7
#घोषणा	v8	8
#घोषणा	v9	9
#घोषणा	v10	10
#घोषणा	v11	11
#घोषणा	v12	12
#घोषणा	v13	13
#घोषणा	v14	14
#घोषणा	v15	15
#घोषणा	v16	16
#घोषणा	v17	17
#घोषणा	v18	18
#घोषणा	v19	19
#घोषणा	v20	20
#घोषणा	v21	21
#घोषणा	v22	22
#घोषणा	v23	23
#घोषणा	v24	24
#घोषणा	v25	25
#घोषणा	v26	26
#घोषणा	v27	27
#घोषणा	v28	28
#घोषणा	v29	29
#घोषणा	v30	30
#घोषणा	v31	31

/* VSX Registers (VSRs) */

#घोषणा	vs0	0
#घोषणा	vs1	1
#घोषणा	vs2	2
#घोषणा	vs3	3
#घोषणा	vs4	4
#घोषणा	vs5	5
#घोषणा	vs6	6
#घोषणा	vs7	7
#घोषणा	vs8	8
#घोषणा	vs9	9
#घोषणा	vs10	10
#घोषणा	vs11	11
#घोषणा	vs12	12
#घोषणा	vs13	13
#घोषणा	vs14	14
#घोषणा	vs15	15
#घोषणा	vs16	16
#घोषणा	vs17	17
#घोषणा	vs18	18
#घोषणा	vs19	19
#घोषणा	vs20	20
#घोषणा	vs21	21
#घोषणा	vs22	22
#घोषणा	vs23	23
#घोषणा	vs24	24
#घोषणा	vs25	25
#घोषणा	vs26	26
#घोषणा	vs27	27
#घोषणा	vs28	28
#घोषणा	vs29	29
#घोषणा	vs30	30
#घोषणा	vs31	31
#घोषणा	vs32	32
#घोषणा	vs33	33
#घोषणा	vs34	34
#घोषणा	vs35	35
#घोषणा	vs36	36
#घोषणा	vs37	37
#घोषणा	vs38	38
#घोषणा	vs39	39
#घोषणा	vs40	40
#घोषणा	vs41	41
#घोषणा	vs42	42
#घोषणा	vs43	43
#घोषणा	vs44	44
#घोषणा	vs45	45
#घोषणा	vs46	46
#घोषणा	vs47	47
#घोषणा	vs48	48
#घोषणा	vs49	49
#घोषणा	vs50	50
#घोषणा	vs51	51
#घोषणा	vs52	52
#घोषणा	vs53	53
#घोषणा	vs54	54
#घोषणा	vs55	55
#घोषणा	vs56	56
#घोषणा	vs57	57
#घोषणा	vs58	58
#घोषणा	vs59	59
#घोषणा	vs60	60
#घोषणा	vs61	61
#घोषणा	vs62	62
#घोषणा	vs63	63

/* SPE Registers (EVPRs) */

#घोषणा	evr0	0
#घोषणा	evr1	1
#घोषणा	evr2	2
#घोषणा	evr3	3
#घोषणा	evr4	4
#घोषणा	evr5	5
#घोषणा	evr6	6
#घोषणा	evr7	7
#घोषणा	evr8	8
#घोषणा	evr9	9
#घोषणा	evr10	10
#घोषणा	evr11	11
#घोषणा	evr12	12
#घोषणा	evr13	13
#घोषणा	evr14	14
#घोषणा	evr15	15
#घोषणा	evr16	16
#घोषणा	evr17	17
#घोषणा	evr18	18
#घोषणा	evr19	19
#घोषणा	evr20	20
#घोषणा	evr21	21
#घोषणा	evr22	22
#घोषणा	evr23	23
#घोषणा	evr24	24
#घोषणा	evr25	25
#घोषणा	evr26	26
#घोषणा	evr27	27
#घोषणा	evr28	28
#घोषणा	evr29	29
#घोषणा	evr30	30
#घोषणा	evr31	31

/* some stab codes */
#घोषणा N_FUN	36
#घोषणा N_RSYM	64
#घोषणा N_SLINE	68
#घोषणा N_SO	100

#घोषणा RFSCV	.दीर्घ 0x4c0000a4

/*
 * Create an endian fixup trampoline
 *
 * This starts with a "tdi 0,0,0x48" inकाष्ठाion which is
 * essentially a "trap never", and thus akin to a nop.
 *
 * The opcode क्रम this inकाष्ठाion पढ़ो with the wrong endian
 * however results in a b . + 8
 *
 * So essentially we use that trick to execute the following
 * trampoline in "reverse endian" अगर we are running with the
 * MSR_LE bit set the "wrong" way क्रम whatever endianness the
 * kernel is built क्रम.
 */

#अगर_घोषित CONFIG_PPC_BOOK3E
#घोषणा FIXUP_ENDIAN
#अन्यथा
/*
 * This version may be used in HV or non-HV context.
 * MSR[EE] must be disabled.
 */
#घोषणा FIXUP_ENDIAN						   \
	tdi   0,0,0x48;	  /* Reverse endian of b . + 8		*/ \
	b     191f;	  /* Skip trampoline अगर endian is good	*/ \
	.दीर्घ 0xa600607d; /* mfmsr r11				*/ \
	.दीर्घ 0x01006b69; /* xori r11,r11,1			*/ \
	.दीर्घ 0x00004039; /* li r10,0				*/ \
	.दीर्घ 0x6401417d; /* mपंचांगsrd r10,1			*/ \
	.दीर्घ 0x05009f42; /* bcl 20,31,$+4			*/ \
	.दीर्घ 0xa602487d; /* mflr r10				*/ \
	.दीर्घ 0x14004a39; /* addi r10,r10,20			*/ \
	.दीर्घ 0xa6035a7d; /* mtsrr0 r10				*/ \
	.दीर्घ 0xa6037b7d; /* mtsrr1 r11				*/ \
	.दीर्घ 0x2400004c; /* rfid				*/ \
191:

/*
 * This version that may only be used with MSR[HV]=1
 * - Does not clear MSR[RI], so more robust.
 * - Slightly smaller and faster.
 */
#घोषणा FIXUP_ENDIAN_HV						   \
	tdi   0,0,0x48;	  /* Reverse endian of b . + 8		*/ \
	b     191f;	  /* Skip trampoline अगर endian is good	*/ \
	.दीर्घ 0xa600607d; /* mfmsr r11				*/ \
	.दीर्घ 0x01006b69; /* xori r11,r11,1			*/ \
	.दीर्घ 0x05009f42; /* bcl 20,31,$+4			*/ \
	.दीर्घ 0xa602487d; /* mflr r10				*/ \
	.दीर्घ 0x14004a39; /* addi r10,r10,20			*/ \
	.दीर्घ 0xa64b5a7d; /* mthsrr0 r10			*/ \
	.दीर्घ 0xa64b7b7d; /* mthsrr1 r11			*/ \
	.दीर्घ 0x2402004c; /* hrfid				*/ \
191:

#पूर्ण_अगर /* !CONFIG_PPC_BOOK3E */

#पूर्ण_अगर /*  __ASSEMBLY__ */

/*
 * Helper macro क्रम exception table entries
 */
#घोषणा EX_TABLE(_fault, _target)		\
	stringअगरy_in_c(.section __ex_table,"a";)\
	stringअगरy_in_c(.balign 4;)		\
	stringअगरy_in_c(.दीर्घ (_fault) - . ;)	\
	stringअगरy_in_c(.दीर्घ (_target) - . ;)	\
	stringअगरy_in_c(.previous)

#अगर_घोषित CONFIG_PPC_FSL_BOOK3E
#घोषणा BTB_FLUSH(reg)			\
	lis reg,BUCSR_INIT@h;		\
	ori reg,reg,BUCSR_INIT@l;	\
	mtspr SPRN_BUCSR,reg;		\
	isync;
#अन्यथा
#घोषणा BTB_FLUSH(reg)
#पूर्ण_अगर /* CONFIG_PPC_FSL_BOOK3E */

#पूर्ण_अगर /* _ASM_POWERPC_PPC_ASM_H */
