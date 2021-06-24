<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 1999 Hewlett-Packard (Frank Rowand)
 * Copyright (C) 1999 Philipp Rumpf <prumpf@tux.org>
 * Copyright (C) 1999 SuSE GmbH
 */

#अगर_अघोषित _PARISC_ASSEMBLY_H
#घोषणा _PARISC_ASSEMBLY_H

#घोषणा CALLEE_FLOAT_FRAME_SIZE	80

#अगर_घोषित CONFIG_64BIT
#घोषणा LDREG	ldd
#घोषणा STREG	std
#घोषणा LDREGX  ldd,s
#घोषणा LDREGM	ldd,mb
#घोषणा STREGM	std,ma
#घोषणा SHRREG	shrd
#घोषणा SHLREG	shld
#घोषणा ANDCM   andcm,*
#घोषणा	COND(x)	* ## x
#घोषणा RP_OFFSET	16
#घोषणा FRAME_SIZE	128
#घोषणा CALLEE_REG_FRAME_SIZE	144
#घोषणा REG_SZ		8
#घोषणा ASM_ULONG_INSN	.dword
#अन्यथा	/* CONFIG_64BIT */
#घोषणा LDREG	ldw
#घोषणा STREG	stw
#घोषणा LDREGX  ldwx,s
#घोषणा LDREGM	ldwm
#घोषणा STREGM	stwm
#घोषणा SHRREG	shr
#घोषणा SHLREG	shlw
#घोषणा ANDCM   andcm
#घोषणा COND(x)	x
#घोषणा RP_OFFSET	20
#घोषणा FRAME_SIZE	64
#घोषणा CALLEE_REG_FRAME_SIZE	128
#घोषणा REG_SZ		4
#घोषणा ASM_ULONG_INSN	.word
#पूर्ण_अगर

#घोषणा CALLEE_SAVE_FRAME_SIZE (CALLEE_REG_FRAME_SIZE + CALLEE_FLOAT_FRAME_SIZE)

#अगर_घोषित CONFIG_PA20
#घोषणा LDCW		ldcw,co
#घोषणा BL		b,l
# अगरdef CONFIG_64BIT
#  define PA_ASM_LEVEL	2.0w
# अन्यथा
#  define PA_ASM_LEVEL	2.0
# endअगर
#अन्यथा
#घोषणा LDCW		ldcw
#घोषणा BL		bl
#घोषणा PA_ASM_LEVEL	1.1
#पूर्ण_अगर

#अगर_घोषित __ASSEMBLY__

#अगर_घोषित CONFIG_64BIT
/* the 64-bit pa gnu assembler unक्रमtunately शेषs to .level 1.1 or 2.0 so
 * work around that क्रम now... */
	.level 2.0w
#पूर्ण_अगर

#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/types.h>

#समावेश <यंत्र/यंत्रregs.h>

	sp	=	30
	gp	=	27
	ipsw	=	22

	/*
	 * We provide two versions of each macro to convert from physical
	 * to भव and vice versa. The "_r1" versions take one argument
	 * रेजिस्टर, but trashes r1 to करो the conversion. The other
	 * version takes two arguments: a src and destination रेजिस्टर.
	 * However, the source and destination रेजिस्टरs can not be
	 * the same रेजिस्टर.
	 */

	.macro  tophys  grvirt, grphys
	ldil    L%(__PAGE_OFFSET), \grphys
	sub     \grvirt, \grphys, \grphys
	.endm
	
	.macro  tovirt  grphys, grvirt
	ldil    L%(__PAGE_OFFSET), \grvirt
	add     \grphys, \grvirt, \grvirt
	.endm

	.macro  tophys_r1  gr
	ldil    L%(__PAGE_OFFSET), %r1
	sub     \gr, %r1, \gr
	.endm
	
	.macro  tovirt_r1  gr
	ldil    L%(__PAGE_OFFSET), %r1
	add     \gr, %r1, \gr
	.endm

	.macro delay value
	ldil	L%\खalue, 1
	lकरो	R%\खalue(1), 1
	addib,UV,n -1,1,.
	addib,NUV,n -1,1,.+8
	nop
	.endm

	.macro	debug value
	.endm

	.macro shlw r, sa, t
	zdep	\ल, 31-(\sa), 32-(\sa), \ट
	.endm

	/* And the PA 2.0W shअगरt left */
	.macro shld r, sa, t
	depd,z	\ल, 63-(\sa), 64-(\sa), \ट
	.endm

	/* Shअगरt Right - note the r and t can NOT be the same! */
	.macro shr r, sa, t
	extru \ल, 31-(\sa), 32-(\sa), \ट
	.endm

	/* pa20w version of shअगरt right */
	.macro shrd r, sa, t
	extrd,u \ल, 63-(\sa), 64-(\sa), \ट
	.endm

	/* load 32-bit 'value' into 'reg' compensating क्रम the ldil
	 * sign-extension when running in wide mode.
	 * WARNING!! neither 'value' nor 'reg' can be expressions
	 * containing '.'!!!! */
	.macro	load32 value, reg
	ldil	L%\खalue, \लeg
	lकरो	R%\खalue(\लeg), \लeg
	.endm

	.macro loadgp
#अगर_घोषित CONFIG_64BIT
	ldil		L%__gp, %r27
	lकरो		R%__gp(%r27), %r27
#अन्यथा
	ldil		L%$global$, %r27
	lकरो		R%$global$(%r27), %r27
#पूर्ण_अगर
	.endm

#घोषणा SAVE_SP(r, where) mfsp r, %r1 ! STREG %r1, where
#घोषणा REST_SP(r, where) LDREG where, %r1 ! mtsp %r1, r
#घोषणा SAVE_CR(r, where) mfctl r, %r1 ! STREG %r1, where
#घोषणा REST_CR(r, where) LDREG where, %r1 ! mtctl %r1, r

	.macro	save_general	regs
	STREG %r1, PT_GR1 (\लegs)
	STREG %r2, PT_GR2 (\लegs)
	STREG %r3, PT_GR3 (\लegs)
	STREG %r4, PT_GR4 (\लegs)
	STREG %r5, PT_GR5 (\लegs)
	STREG %r6, PT_GR6 (\लegs)
	STREG %r7, PT_GR7 (\लegs)
	STREG %r8, PT_GR8 (\लegs)
	STREG %r9, PT_GR9 (\लegs)
	STREG %r10, PT_GR10(\लegs)
	STREG %r11, PT_GR11(\लegs)
	STREG %r12, PT_GR12(\लegs)
	STREG %r13, PT_GR13(\लegs)
	STREG %r14, PT_GR14(\लegs)
	STREG %r15, PT_GR15(\लegs)
	STREG %r16, PT_GR16(\लegs)
	STREG %r17, PT_GR17(\लegs)
	STREG %r18, PT_GR18(\लegs)
	STREG %r19, PT_GR19(\लegs)
	STREG %r20, PT_GR20(\लegs)
	STREG %r21, PT_GR21(\लegs)
	STREG %r22, PT_GR22(\लegs)
	STREG %r23, PT_GR23(\लegs)
	STREG %r24, PT_GR24(\लegs)
	STREG %r25, PT_GR25(\लegs)
	/* r26 is saved in get_stack and used to preserve a value across virt_map */
	STREG %r27, PT_GR27(\लegs)
	STREG %r28, PT_GR28(\लegs)
	/* r29 is saved in get_stack and used to poपूर्णांक to saved रेजिस्टरs */
	/* r30 stack poपूर्णांकer saved in get_stack */
	STREG %r31, PT_GR31(\लegs)
	.endm

	.macro	rest_general	regs
	/* r1 used as a temp in rest_stack and is restored there */
	LDREG PT_GR2 (\लegs), %r2
	LDREG PT_GR3 (\लegs), %r3
	LDREG PT_GR4 (\लegs), %r4
	LDREG PT_GR5 (\लegs), %r5
	LDREG PT_GR6 (\लegs), %r6
	LDREG PT_GR7 (\लegs), %r7
	LDREG PT_GR8 (\लegs), %r8
	LDREG PT_GR9 (\लegs), %r9
	LDREG PT_GR10(\लegs), %r10
	LDREG PT_GR11(\लegs), %r11
	LDREG PT_GR12(\लegs), %r12
	LDREG PT_GR13(\लegs), %r13
	LDREG PT_GR14(\लegs), %r14
	LDREG PT_GR15(\लegs), %r15
	LDREG PT_GR16(\लegs), %r16
	LDREG PT_GR17(\लegs), %r17
	LDREG PT_GR18(\लegs), %r18
	LDREG PT_GR19(\लegs), %r19
	LDREG PT_GR20(\लegs), %r20
	LDREG PT_GR21(\लegs), %r21
	LDREG PT_GR22(\लegs), %r22
	LDREG PT_GR23(\लegs), %r23
	LDREG PT_GR24(\लegs), %r24
	LDREG PT_GR25(\लegs), %r25
	LDREG PT_GR26(\लegs), %r26
	LDREG PT_GR27(\लegs), %r27
	LDREG PT_GR28(\लegs), %r28
	/* r29 poपूर्णांकs to रेजिस्टर save area, and is restored in rest_stack */
	/* r30 stack poपूर्णांकer restored in rest_stack */
	LDREG PT_GR31(\लegs), %r31
	.endm

	.macro	save_fp 	regs
	fstd,ma  %fr0, 8(\लegs)
	fstd,ma	 %fr1, 8(\लegs)
	fstd,ma	 %fr2, 8(\लegs)
	fstd,ma	 %fr3, 8(\लegs)
	fstd,ma	 %fr4, 8(\लegs)
	fstd,ma	 %fr5, 8(\लegs)
	fstd,ma	 %fr6, 8(\लegs)
	fstd,ma	 %fr7, 8(\लegs)
	fstd,ma	 %fr8, 8(\लegs)
	fstd,ma	 %fr9, 8(\लegs)
	fstd,ma	%fr10, 8(\लegs)
	fstd,ma	%fr11, 8(\लegs)
	fstd,ma	%fr12, 8(\लegs)
	fstd,ma	%fr13, 8(\लegs)
	fstd,ma	%fr14, 8(\लegs)
	fstd,ma	%fr15, 8(\लegs)
	fstd,ma	%fr16, 8(\लegs)
	fstd,ma	%fr17, 8(\लegs)
	fstd,ma	%fr18, 8(\लegs)
	fstd,ma	%fr19, 8(\लegs)
	fstd,ma	%fr20, 8(\लegs)
	fstd,ma	%fr21, 8(\लegs)
	fstd,ma	%fr22, 8(\लegs)
	fstd,ma	%fr23, 8(\लegs)
	fstd,ma	%fr24, 8(\लegs)
	fstd,ma	%fr25, 8(\लegs)
	fstd,ma	%fr26, 8(\लegs)
	fstd,ma	%fr27, 8(\लegs)
	fstd,ma	%fr28, 8(\लegs)
	fstd,ma	%fr29, 8(\लegs)
	fstd,ma	%fr30, 8(\लegs)
	fstd	%fr31, 0(\लegs)
	.endm

	.macro	rest_fp 	regs
	fldd	0(\लegs),	 %fr31
	fldd,mb	-8(\लegs),       %fr30
	fldd,mb	-8(\लegs),       %fr29
	fldd,mb	-8(\लegs),       %fr28
	fldd,mb	-8(\लegs),       %fr27
	fldd,mb	-8(\लegs),       %fr26
	fldd,mb	-8(\लegs),       %fr25
	fldd,mb	-8(\लegs),       %fr24
	fldd,mb	-8(\लegs),       %fr23
	fldd,mb	-8(\लegs),       %fr22
	fldd,mb	-8(\लegs),       %fr21
	fldd,mb	-8(\लegs),       %fr20
	fldd,mb	-8(\लegs),       %fr19
	fldd,mb	-8(\लegs),       %fr18
	fldd,mb	-8(\लegs),       %fr17
	fldd,mb	-8(\लegs),       %fr16
	fldd,mb	-8(\लegs),       %fr15
	fldd,mb	-8(\लegs),       %fr14
	fldd,mb	-8(\लegs),       %fr13
	fldd,mb	-8(\लegs),       %fr12
	fldd,mb	-8(\लegs),       %fr11
	fldd,mb	-8(\लegs),       %fr10
	fldd,mb	-8(\लegs),       %fr9
	fldd,mb	-8(\लegs),       %fr8
	fldd,mb	-8(\लegs),       %fr7
	fldd,mb	-8(\लegs),       %fr6
	fldd,mb	-8(\लegs),       %fr5
	fldd,mb	-8(\लegs),       %fr4
	fldd,mb	-8(\लegs),       %fr3
	fldd,mb	-8(\लegs),       %fr2
	fldd,mb	-8(\लegs),       %fr1
	fldd,mb	-8(\लegs),       %fr0
	.endm

	.macro	callee_save_भग्न
	fstd,ma	 %fr12,	8(%r30)
	fstd,ma	 %fr13,	8(%r30)
	fstd,ma	 %fr14,	8(%r30)
	fstd,ma	 %fr15,	8(%r30)
	fstd,ma	 %fr16,	8(%r30)
	fstd,ma	 %fr17,	8(%r30)
	fstd,ma	 %fr18,	8(%r30)
	fstd,ma	 %fr19,	8(%r30)
	fstd,ma	 %fr20,	8(%r30)
	fstd,ma	 %fr21,	8(%r30)
	.endm

	.macro	callee_rest_भग्न
	fldd,mb	-8(%r30),   %fr21
	fldd,mb	-8(%r30),   %fr20
	fldd,mb	-8(%r30),   %fr19
	fldd,mb	-8(%r30),   %fr18
	fldd,mb	-8(%r30),   %fr17
	fldd,mb	-8(%r30),   %fr16
	fldd,mb	-8(%r30),   %fr15
	fldd,mb	-8(%r30),   %fr14
	fldd,mb	-8(%r30),   %fr13
	fldd,mb	-8(%r30),   %fr12
	.endm

#अगर_घोषित CONFIG_64BIT
	.macro	callee_save
	std,ma	  %r3,	 CALLEE_REG_FRAME_SIZE(%r30)
	mfctl	  %cr27, %r3
	std	  %r4,	-136(%r30)
	std	  %r5,	-128(%r30)
	std	  %r6,	-120(%r30)
	std	  %r7,	-112(%r30)
	std	  %r8,	-104(%r30)
	std	  %r9,	 -96(%r30)
	std	 %r10,	 -88(%r30)
	std	 %r11,	 -80(%r30)
	std	 %r12,	 -72(%r30)
	std	 %r13,	 -64(%r30)
	std	 %r14,	 -56(%r30)
	std	 %r15,	 -48(%r30)
	std	 %r16,	 -40(%r30)
	std	 %r17,	 -32(%r30)
	std	 %r18,	 -24(%r30)
	std	  %r3,	 -16(%r30)
	.endm

	.macro	callee_rest
	ldd	 -16(%r30),    %r3
	ldd	 -24(%r30),   %r18
	ldd	 -32(%r30),   %r17
	ldd	 -40(%r30),   %r16
	ldd	 -48(%r30),   %r15
	ldd	 -56(%r30),   %r14
	ldd	 -64(%r30),   %r13
	ldd	 -72(%r30),   %r12
	ldd	 -80(%r30),   %r11
	ldd	 -88(%r30),   %r10
	ldd	 -96(%r30),    %r9
	ldd	-104(%r30),    %r8
	ldd	-112(%r30),    %r7
	ldd	-120(%r30),    %r6
	ldd	-128(%r30),    %r5
	ldd	-136(%r30),    %r4
	mtctl	%r3, %cr27
	ldd,mb	-CALLEE_REG_FRAME_SIZE(%r30),    %r3
	.endm

#अन्यथा /* ! CONFIG_64BIT */

	.macro	callee_save
	stw,ma	 %r3,	CALLEE_REG_FRAME_SIZE(%r30)
	mfctl	 %cr27, %r3
	stw	 %r4,	-124(%r30)
	stw	 %r5,	-120(%r30)
	stw	 %r6,	-116(%r30)
	stw	 %r7,	-112(%r30)
	stw	 %r8,	-108(%r30)
	stw	 %r9,	-104(%r30)
	stw	 %r10,	-100(%r30)
	stw	 %r11,	 -96(%r30)
	stw	 %r12,	 -92(%r30)
	stw	 %r13,	 -88(%r30)
	stw	 %r14,	 -84(%r30)
	stw	 %r15,	 -80(%r30)
	stw	 %r16,	 -76(%r30)
	stw	 %r17,	 -72(%r30)
	stw	 %r18,	 -68(%r30)
	stw	  %r3,	 -64(%r30)
	.endm

	.macro	callee_rest
	ldw	 -64(%r30),    %r3
	ldw	 -68(%r30),   %r18
	ldw	 -72(%r30),   %r17
	ldw	 -76(%r30),   %r16
	ldw	 -80(%r30),   %r15
	ldw	 -84(%r30),   %r14
	ldw	 -88(%r30),   %r13
	ldw	 -92(%r30),   %r12
	ldw	 -96(%r30),   %r11
	ldw	-100(%r30),   %r10
	ldw	-104(%r30),   %r9
	ldw	-108(%r30),   %r8
	ldw	-112(%r30),   %r7
	ldw	-116(%r30),   %r6
	ldw	-120(%r30),   %r5
	ldw	-124(%r30),   %r4
	mtctl	%r3, %cr27
	ldw,mb	-CALLEE_REG_FRAME_SIZE(%r30),   %r3
	.endm
#पूर्ण_अगर /* ! CONFIG_64BIT */

	.macro	save_specials	regs

	SAVE_SP  (%sr0, PT_SR0 (\लegs))
	SAVE_SP  (%sr1, PT_SR1 (\लegs))
	SAVE_SP  (%sr2, PT_SR2 (\लegs))
	SAVE_SP  (%sr3, PT_SR3 (\लegs))
	SAVE_SP  (%sr4, PT_SR4 (\लegs))
	SAVE_SP  (%sr5, PT_SR5 (\लegs))
	SAVE_SP  (%sr6, PT_SR6 (\लegs))

	SAVE_CR  (%cr17, PT_IASQ0(\लegs))
	mtctl	 %r0,	%cr17
	SAVE_CR  (%cr17, PT_IASQ1(\लegs))

	SAVE_CR  (%cr18, PT_IAOQ0(\लegs))
	mtctl	 %r0,	%cr18
	SAVE_CR  (%cr18, PT_IAOQ1(\लegs))

#अगर_घोषित CONFIG_64BIT
	/* cr11 (sar) is a funny one.  5 bits on PA1.1 and 6 bit on PA2.0
	 * For PA2.0 mtsar or mtctl always ग_लिखो 6 bits, but mfctl only
	 * पढ़ोs 5 bits.  Use mfctl,w to पढ़ो all six bits.  Otherwise
	 * we lose the 6th bit on a save/restore over पूर्णांकerrupt.
	 */
	mfctl,w  %cr11, %r1
	STREG    %r1, PT_SAR (\लegs)
#अन्यथा
	SAVE_CR  (%cr11, PT_SAR  (\लegs))
#पूर्ण_अगर
	SAVE_CR  (%cr19, PT_IIR  (\लegs))

	/*
	 * Code immediately following this macro (in पूर्णांकr_save) relies
	 * on r8 containing ipsw.
	 */
	mfctl    %cr22, %r8
	STREG    %r8,   PT_PSW(\लegs)
	.endm

	.macro	rest_specials	regs

	REST_SP  (%sr0, PT_SR0 (\लegs))
	REST_SP  (%sr1, PT_SR1 (\लegs))
	REST_SP  (%sr2, PT_SR2 (\लegs))
	REST_SP  (%sr3, PT_SR3 (\लegs))
	REST_SP  (%sr4, PT_SR4 (\लegs))
	REST_SP  (%sr5, PT_SR5 (\लegs))
	REST_SP  (%sr6, PT_SR6 (\लegs))
	REST_SP  (%sr7, PT_SR7 (\लegs))

	REST_CR	(%cr17, PT_IASQ0(\लegs))
	REST_CR	(%cr17, PT_IASQ1(\लegs))

	REST_CR	(%cr18, PT_IAOQ0(\लegs))
	REST_CR	(%cr18, PT_IAOQ1(\लegs))

	REST_CR (%cr11, PT_SAR	(\लegs))

	REST_CR	(%cr22, PT_PSW	(\लegs))
	.endm


	/* First step to create a "relied upon translation"
	 * See PA 2.0 Arch. page F-4 and F-5.
	 *
	 * The ssm was originally necessary due to a "PCxT bug".
	 * But someone decided it needed to be added to the architecture
	 * and this "feature" went पूर्णांकo rev3 of PA-RISC 1.1 Arch Manual.
	 * It's been carried क्रमward पूर्णांकo PA 2.0 Arch as well. :^(
	 *
	 * "ssm 0,%r0" is a NOP with side effects (prefetch barrier).
	 * rsm/ssm prevents the अगरetch unit from speculatively fetching
	 * inकाष्ठाions past this line in the code stream.
	 * PA 2.0 processor will single step all insn in the same QUAD (4 insn).
	 */
	.macro	pcxt_ssm_bug
	rsm	PSW_SM_I,%r0
	nop	/* 1 */
	nop	/* 2 */
	nop	/* 3 */
	nop	/* 4 */
	nop	/* 5 */
	nop	/* 6 */
	nop	/* 7 */
	.endm

	/*
	 * ASM_EXCEPTIONTABLE_ENTRY
	 *
	 * Creates an exception table entry.
	 * Do not convert to a assembler macro. This won't work.
	 */
#घोषणा ASM_EXCEPTIONTABLE_ENTRY(fault_addr, except_addr)	\
	.section __ex_table,"aw"			!	\
	.word (fault_addr - .), (except_addr - .)	!	\
	.previous


#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर
