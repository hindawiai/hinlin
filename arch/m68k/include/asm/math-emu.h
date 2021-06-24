<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_M68K_SETUP_H
#घोषणा _ASM_M68K_SETUP_H

#समावेश <यंत्र/setup.h>
#समावेश <linux/linkage.h>

/* Status Register bits */

/* accrued exception bits */
#घोषणा FPSR_AEXC_INEX	3
#घोषणा FPSR_AEXC_DZ	4
#घोषणा FPSR_AEXC_UNFL	5
#घोषणा FPSR_AEXC_OVFL	6
#घोषणा FPSR_AEXC_IOP	7

/* exception status bits */
#घोषणा FPSR_EXC_INEX1	8
#घोषणा FPSR_EXC_INEX2	9
#घोषणा FPSR_EXC_DZ	10
#घोषणा FPSR_EXC_UNFL	11
#घोषणा FPSR_EXC_OVFL	12
#घोषणा FPSR_EXC_OPERR	13
#घोषणा FPSR_EXC_Sन_अंक	14
#घोषणा FPSR_EXC_BSUN	15

/* quotient byte, assumes big-endian, of course */
#घोषणा FPSR_QUOTIENT(fpsr) (*((चिन्हित अक्षर *) &(fpsr) + 1))

/* condition code bits */
#घोषणा FPSR_CC_न_अंक	24
#घोषणा FPSR_CC_INF	25
#घोषणा FPSR_CC_Z	26
#घोषणा FPSR_CC_NEG	27


/* Control रेजिस्टर bits */

/* rounding mode */
#घोषणा	FPCR_ROUND_RN	0		/* round to nearest/even */
#घोषणा FPCR_ROUND_RZ	1		/* round to zero */
#घोषणा FPCR_ROUND_RM	2		/* minus infinity */
#घोषणा FPCR_ROUND_RP	3		/* plus infinity */

/* rounding precision */
#घोषणा FPCR_PRECISION_X	0	/* दीर्घ द्विगुन */
#घोषणा FPCR_PRECISION_S	1	/* द्विगुन */
#घोषणा FPCR_PRECISION_D	2	/* भग्न */


/* Flags to select the debugging output */
#घोषणा PDECODE		0
#घोषणा PEXECUTE	1
#घोषणा PCONV		2
#घोषणा PNORM		3
#घोषणा PREGISTER	4
#घोषणा PINSTR		5
#घोषणा PUNIMPL		6
#घोषणा PMOVEM		7

#घोषणा PMDECODE	(1<<PDECODE)
#घोषणा PMEXECUTE	(1<<PEXECUTE)
#घोषणा PMCONV		(1<<PCONV)
#घोषणा PMNORM		(1<<PNORM)
#घोषणा PMREGISTER	(1<<PREGISTER)
#घोषणा PMINSTR		(1<<PINSTR)
#घोषणा PMUNIMPL	(1<<PUNIMPL)
#घोषणा PMMOVEM		(1<<PMOVEM)

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>

जोड़ fp_mant64 अणु
	अचिन्हित दीर्घ दीर्घ m64;
	अचिन्हित दीर्घ m32[2];
पूर्ण;

जोड़ fp_mant128 अणु
	अचिन्हित दीर्घ दीर्घ m64[2];
	अचिन्हित दीर्घ m32[4];
पूर्ण;

/* पूर्णांकernal representation of extended fp numbers */
काष्ठा fp_ext अणु
	अचिन्हित अक्षर lowmant;
	अचिन्हित अक्षर sign;
	अचिन्हित लघु exp;
	जोड़ fp_mant64 mant;
पूर्ण;

/* C representation of FPU रेजिस्टरs */
/* NOTE: अगर you change this, you have to change the assembler offsets
   below and the size in <यंत्र/fpu.h>, too */
काष्ठा fp_data अणु
	काष्ठा fp_ext fpreg[8];
	अचिन्हित पूर्णांक fpcr;
	अचिन्हित पूर्णांक fpsr;
	अचिन्हित पूर्णांक fpiar;
	अचिन्हित लघु prec;
	अचिन्हित लघु rnd;
	काष्ठा fp_ext temp[2];
पूर्ण;

#अगर_घोषित FPU_EMU_DEBUG
बाह्य अचिन्हित पूर्णांक fp_debugprपूर्णांक;

#घोषणा dprपूर्णांक(bit, fmt, ...) (अणु			\
	अगर (fp_debugprपूर्णांक & (1 << (bit)))		\
		pr_info(fmt, ##__VA_ARGS__);		\
पूर्ण)
#अन्यथा
#घोषणा dprपूर्णांक(bit, fmt, ...)	no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

#घोषणा uprपूर्णांक(str) (अणु					\
	अटल पूर्णांक __count = 3;				\
							\
	अगर (__count > 0) अणु				\
		pr_err("You just hit an unimplemented "	\
		       "fpu instruction (%s)\n", str);	\
		pr_err("Please report this to ....\n");	\
		__count--;				\
	पूर्ण						\
पूर्ण)

#घोषणा FPDATA		((काष्ठा fp_data *)current->thपढ़ो.fp)

#अन्यथा	/* __ASSEMBLY__ */

#घोषणा FPDATA		%a2

/* offsets from the base रेजिस्टर to the भग्नing poपूर्णांक data in the task काष्ठा */
#घोषणा FPD_FPREG	(TASK_THREAD+THREAD_FPREG+0)
#घोषणा FPD_FPCR	(TASK_THREAD+THREAD_FPREG+96)
#घोषणा FPD_FPSR	(TASK_THREAD+THREAD_FPREG+100)
#घोषणा FPD_FPIAR	(TASK_THREAD+THREAD_FPREG+104)
#घोषणा FPD_PREC	(TASK_THREAD+THREAD_FPREG+108)
#घोषणा FPD_RND		(TASK_THREAD+THREAD_FPREG+110)
#घोषणा FPD_TEMPFP1	(TASK_THREAD+THREAD_FPREG+112)
#घोषणा FPD_TEMPFP2	(TASK_THREAD+THREAD_FPREG+124)
#घोषणा FPD_SIZखातापूर्ण	(TASK_THREAD+THREAD_FPREG+136)

/* offsets on the stack to access saved रेजिस्टरs,
 * these are only used during inकाष्ठाion decoding
 * where we always know how deep we're on the stack.
 */
#घोषणा FPS_DO		(PT_OFF_D0)
#घोषणा FPS_D1		(PT_OFF_D1)
#घोषणा FPS_D2		(PT_OFF_D2)
#घोषणा FPS_A0		(PT_OFF_A0)
#घोषणा FPS_A1		(PT_OFF_A1)
#घोषणा FPS_A2		(PT_OFF_A2)
#घोषणा FPS_SR		(PT_OFF_SR)
#घोषणा FPS_PC		(PT_OFF_PC)
#घोषणा FPS_EA		(PT_OFF_PC+6)
#घोषणा FPS_PC2		(PT_OFF_PC+10)

.macro	fp_get_fp_reg
	lea	(FPD_FPREG,FPDATA,%d0.w*4),%a0
	lea	(%a0,%d0.w*8),%a0
.endm

/* Macros used to get/put the current program counter.
 * 020/030 use a dअगरferent stack frame then 040/060, क्रम the
 * 040/060 the वापस pc poपूर्णांकs alपढ़ोy to the next location,
 * so this only needs to be modअगरied क्रम jump inकाष्ठाions.
 */
.macro	fp_get_pc dest
	move.l	(FPS_PC+4,%sp),\dest
.endm

.macro	fp_put_pc src,jump=0
	move.l	\src,(FPS_PC+4,%sp)
.endm

.macro	fp_get_instr_data	f,s,dest,label
	getuser	\प,%sp@(FPS_PC+4)@(0),\dest,\label,%sp@(FPS_PC+4)
	addq.l	#\s,%sp@(FPS_PC+4)
.endm

.macro	fp_get_instr_word	dest,label,addr
	fp_get_instr_data	w,2,\dest,\label,\चddr
.endm

.macro	fp_get_instr_दीर्घ	dest,label,addr
	fp_get_instr_data	l,4,\dest,\label,\चddr
.endm

/* These macros are used to पढ़ो from/ग_लिखो to user space
 * on error we jump to the fixup section, load the fault
 * address पूर्णांकo %a0 and jump to the निकास.
 * (derived from <यंत्र/uaccess.h>)
 */
.macro	getuser	size,src,dest,label,addr
|	म_लिखो	,"[\size<%08x]",1,\चddr
.Lu1\@:	moves\size	\src,\dest

	.section .fixup,"ax"
	.even
.Lu2\@:	move.l	\चddr,%a0
	jra	\label
	.previous

	.section __ex_table,"a"
	.align	4
	.दीर्घ	.Lu1\@,.Lu2\@
	.previous
.endm

.macro	putuser	size,src,dest,label,addr
|	म_लिखो	,"[\size>%08x]",1,\चddr
.Lu1\@:	moves\size	\src,\dest
.Lu2\@:

	.section .fixup,"ax"
	.even
.Lu3\@:	move.l	\चddr,%a0
	jra	\label
	.previous

	.section __ex_table,"a"
	.align	4
	.दीर्घ	.Lu1\@,.Lu3\@
	.दीर्घ	.Lu2\@,.Lu3\@
	.previous
.endm

/* work around binutils idiocy */
old_gas=-1
.irp    gas_ident.x .x
old_gas=old_gas+1
.endr
.अगर !old_gas
.irp	m b,w,l
.macro	getuser.\m src,dest,label,addr
	getuser .\m,\src,\dest,\label,\चddr
.endm
.macro	putuser.\m src,dest,label,addr
	putuser .\m,\src,\dest,\label,\चddr
.endm
.endr
.endअगर

.macro	movestack	nr,arg1,arg2,arg3,arg4,arg5
	.अगर	\नr
	movestack	(\नr-1),\चrg2,\चrg3,\चrg4,\चrg5
	move.l	\चrg1,-(%sp)
	.endअगर
.endm

.macro	म_लिखो	bit=-1,string,nr=0,arg1,arg2,arg3,arg4,arg5
#अगर_घोषित FPU_EMU_DEBUG
	.data
.Lpdata\@:
	.string	"\string"
	.previous

	movem.l	%d0/%d1/%a0/%a1,-(%sp)
	.अगर	\मit+1
#अगर 0
	moveq	#\मit,%d0
	andw	#7,%d0
	btst	%d0,fp_debugprपूर्णांक+((31-\मit)/8)
#अन्यथा
	btst	#\मit,fp_debugprपूर्णांक+((31-\मit)/8)
#पूर्ण_अगर
	jeq	.Lpskip\@
	.endअगर
	movestack	\नr,\चrg1,\चrg2,\चrg3,\चrg4,\चrg5
	pea	.Lpdata\@
	jsr	prपूर्णांकk
	lea	((\नr+1)*4,%sp),%sp
.Lpskip\@:
	movem.l	(%sp)+,%d0/%d1/%a0/%a1
#पूर्ण_अगर
.endm

.macro	prपूर्णांकx	bit,fp
#अगर_घोषित FPU_EMU_DEBUG
	movem.l	%d0/%a0,-(%sp)
	lea	\पp,%a0
#अगर 0
	moveq	#'+',%d0
	tst.w	(%a0)
	jeq	.Lx1\@
	moveq	#'-',%d0
.Lx1\@:	म_लिखो	\मit," %c",1,%d0
	move.l	(4,%a0),%d0
	bclr	#31,%d0
	jne	.Lx2\@
	म_लिखो	\मit,"0."
	jra	.Lx3\@
.Lx2\@:	म_लिखो	\मit,"1."
.Lx3\@:	म_लिखो	\मit,"%08x%08x",2,%d0,%a0@(8)
	move.w	(2,%a0),%d0
	ext.l	%d0
	म_लिखो	\मit,"E%04x",1,%d0
#अन्यथा
	म_लिखो	\मit," %08x%08x%08x",3,%a0@,%a0@(4),%a0@(8)
#पूर्ण_अगर
	movem.l	(%sp)+,%d0/%a0
#पूर्ण_अगर
.endm

.macro	debug	instr,args
#अगर_घोषित FPU_EMU_DEBUG
	\instr	\चrgs
#पूर्ण_अगर
.endm


#पूर्ण_अगर	/* __ASSEMBLY__ */

#पूर्ण_अगर	/* _ASM_M68K_SETUP_H */
