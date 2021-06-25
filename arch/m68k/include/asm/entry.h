<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __M68K_ENTRY_H
#घोषणा __M68K_ENTRY_H

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/page.h>
#अगर_घोषित __ASSEMBLY__
#समावेश <यंत्र/thपढ़ो_info.h>
#पूर्ण_अगर

/*
 * Stack layout in 'ret_from_exception':
 *
 *	This allows access to the syscall arguments in रेजिस्टरs d1-d5
 *
 *	 0(sp) - d1
 *	 4(sp) - d2
 *	 8(sp) - d3
 *	 C(sp) - d4
 *	10(sp) - d5
 *	14(sp) - a0
 *	18(sp) - a1
 *	1C(sp) - a2
 *	20(sp) - d0
 *	24(sp) - orig_d0
 *	28(sp) - stack adjusपंचांगent
 *	2C(sp) - [ sr              ] [ क्रमmat & vector ]
 *	2E(sp) - [ pc-hiword       ] [ sr              ]
 *	30(sp) - [ pc-loword       ] [ pc-hiword       ]
 *	32(sp) - [ क्रमmat & vector ] [ pc-loword       ]
 *		  ^^^^^^^^^^^^^^^^^   ^^^^^^^^^^^^^^^^^
 *			M68K		  COLDFIRE
 */

/* the following macro is used when enabling पूर्णांकerrupts */
#अगर defined(MACH_ATARI_ONLY)
	/* block out HSYNC = ipl 2 on the atari */
#घोषणा ALLOWINT	(~0x500)
#अन्यथा
	/* portable version */
#घोषणा ALLOWINT	(~0x700)
#पूर्ण_अगर /* machine compilation types */

#अगर_घोषित __ASSEMBLY__
/*
 * This defines the normal kernel pt-regs layout.
 *
 * regs a3-a6 and d6-d7 are preserved by C code
 * the kernel करोesn't mess with usp unless it needs to
 */
#घोषणा SWITCH_STACK_SIZE	(6*4+4)	/* includes वापस address */

#अगर_घोषित CONFIG_COLDFIRE
#अगर_घोषित CONFIG_COLDFIRE_SW_A7
/*
 * This is made a little more tricky on older ColdFires. There is no
 * separate supervisor and user stack poपूर्णांकers. Need to artअगरicially
 * स्थिरruct a usp in software... When करोing this we need to disable
 * पूर्णांकerrupts, otherwise bad things will happen.
 */
.globl sw_usp
.globl sw_ksp

.macro SAVE_ALL_SYS
	move	#0x2700,%sr		/* disable पूर्णांकrs */
	btst	#5,%sp@(2)		/* from user? */
	bnes	6f			/* no, skip */
	movel	%sp,sw_usp		/* save user sp */
	addql	#8,sw_usp		/* हटाओ exception */
	movel	sw_ksp,%sp		/* kernel sp */
	subql	#8,%sp			/* room क्रम exception */
	clrl	%sp@-			/* stkadj */
	movel	%d0,%sp@-		/* orig d0 */
	movel	%d0,%sp@-		/* d0 */
	lea	%sp@(-32),%sp		/* space क्रम 8 regs */
	moveml	%d1-%d5/%a0-%a2,%sp@
	movel	sw_usp,%a0		/* get usp */
	movel	%a0@-,%sp@(PT_OFF_PC)	/* copy exception program counter */
	movel	%a0@-,%sp@(PT_OFF_FORMATVEC)/*copy exception क्रमmat/vector/sr */
	bra	7f
	6:
	clrl	%sp@-			/* stkadj */
	movel	%d0,%sp@-		/* orig d0 */
	movel	%d0,%sp@-		/* d0 */
	lea	%sp@(-32),%sp		/* space क्रम 8 regs */
	moveml	%d1-%d5/%a0-%a2,%sp@
	7:
.endm

.macro SAVE_ALL_INT
	SAVE_ALL_SYS
	moveq	#-1,%d0			/* not प्रणाली call entry */
	movel	%d0,%sp@(PT_OFF_ORIG_D0)
.endm

.macro RESTORE_USER
	move	#0x2700,%sr		/* disable पूर्णांकrs */
	movel	sw_usp,%a0		/* get usp */
	movel	%sp@(PT_OFF_PC),%a0@-	/* copy exception program counter */
	movel	%sp@(PT_OFF_FORMATVEC),%a0@-/*copy exception क्रमmat/vector/sr */
	moveml	%sp@,%d1-%d5/%a0-%a2
	lea	%sp@(32),%sp		/* space क्रम 8 regs */
	movel	%sp@+,%d0
	addql	#4,%sp			/* orig d0 */
	addl	%sp@+,%sp		/* stkadj */
	addql	#8,%sp			/* हटाओ exception */
	movel	%sp,sw_ksp		/* save ksp */
	subql	#8,sw_usp		/* set exception */
	movel	sw_usp,%sp		/* restore usp */
	rte
.endm

.macro RDUSP
	movel	sw_usp,%a3
.endm

.macro WRUSP
	movel	%a3,sw_usp
.endm

#अन्यथा /* !CONFIG_COLDFIRE_SW_A7 */
/*
 * Modern ColdFire parts have separate supervisor and user stack
 * poपूर्णांकers. Simple load and restore macros क्रम this हाल.
 */
.macro SAVE_ALL_SYS
	move	#0x2700,%sr		/* disable पूर्णांकrs */
	clrl	%sp@-			/* stkadj */
	movel	%d0,%sp@-		/* orig d0 */
	movel	%d0,%sp@-		/* d0 */
	lea	%sp@(-32),%sp		/* space क्रम 8 regs */
	moveml	%d1-%d5/%a0-%a2,%sp@
.endm

.macro SAVE_ALL_INT
	move	#0x2700,%sr		/* disable पूर्णांकrs */
	clrl	%sp@-			/* stkadj */
	pea	-1:w			/* orig d0 */
	movel	%d0,%sp@-		/* d0 */
	lea	%sp@(-32),%sp		/* space क्रम 8 regs */
	moveml	%d1-%d5/%a0-%a2,%sp@
.endm

.macro RESTORE_USER
	moveml	%sp@,%d1-%d5/%a0-%a2
	lea	%sp@(32),%sp		/* space क्रम 8 regs */
	movel	%sp@+,%d0
	addql	#4,%sp			/* orig d0 */
	addl	%sp@+,%sp		/* stkadj */
	rte
.endm

.macro RDUSP
	/*move	%usp,%a3*/
	.word	0x4e6b
.endm

.macro WRUSP
	/*move	%a3,%usp*/
	.word	0x4e63
.endm

#पूर्ण_अगर /* !CONFIG_COLDFIRE_SW_A7 */

.macro SAVE_SWITCH_STACK
	lea	%sp@(-24),%sp		/* 6 regs */
	moveml	%a3-%a6/%d6-%d7,%sp@
.endm

.macro RESTORE_SWITCH_STACK
	moveml	%sp@,%a3-%a6/%d6-%d7
	lea	%sp@(24),%sp		/* 6 regs */
.endm

#अन्यथा /* !CONFIG_COLDFIRE */

/*
 * All other types of m68k parts (68000, 680x0, CPU32) have the same
 * entry and निकास code.
 */

/*
 * a -1 in the orig_d0 field signअगरies
 * that the stack frame is NOT क्रम syscall
 */
.macro SAVE_ALL_INT
	clrl	%sp@-			/* stk_adj */
	pea	-1:w			/* orig d0 */
	movel	%d0,%sp@-		/* d0 */
	moveml	%d1-%d5/%a0-%a2,%sp@-
.endm

.macro SAVE_ALL_SYS
	clrl	%sp@-			/* stk_adj */
	movel	%d0,%sp@-		/* orig d0 */
	movel	%d0,%sp@-		/* d0 */
	moveml	%d1-%d5/%a0-%a2,%sp@-
.endm

.macro RESTORE_ALL
	moveml	%sp@+,%a0-%a2/%d1-%d5
	movel	%sp@+,%d0
	addql	#4,%sp			/* orig d0 */
	addl	%sp@+,%sp		/* stk adj */
	rte
.endm


.macro SAVE_SWITCH_STACK
	moveml	%a3-%a6/%d6-%d7,%sp@-
.endm

.macro RESTORE_SWITCH_STACK
	moveml	%sp@+,%a3-%a6/%d6-%d7
.endm

#पूर्ण_अगर /* !CONFIG_COLDFIRE */

/*
 * Register %a2 is reserved and set to current task on MMU enabled प्रणालीs.
 * Non-MMU प्रणालीs करो not reserve %a2 in this way, and this definition is
 * not used क्रम them.
 */
#अगर_घोषित CONFIG_MMU

#घोषणा curptr a2

#घोषणा GET_CURRENT(पंचांगp) get_current पंचांगp
.macro get_current reg=%d0
	movel	%sp,\लeg
	andl	#-THREAD_SIZE,\लeg
	movel	\लeg,%curptr
	movel	%curptr@,%curptr
.endm

#अन्यथा

#घोषणा GET_CURRENT(पंचांगp)

#पूर्ण_अगर /* CONFIG_MMU */

#अन्यथा /* C source */

#घोषणा STR(X) STR1(X)
#घोषणा STR1(X) #X

#घोषणा SAVE_ALL_INT				\
	"clrl	%%sp@-;"    /* stk_adj */	\
	"pea	-1:w;"	    /* orig d0 = -1 */	\
	"movel	%%d0,%%sp@-;" /* d0 */		\
	"moveml	%%d1-%%d5/%%a0-%%a2,%%sp@-"

#घोषणा GET_CURRENT(पंचांगp) \
	"movel	%%sp,"#पंचांगp"\n\t" \
	"andw	#-"STR(THREAD_SIZE)","#पंचांगp"\n\t" \
	"movel	"#पंचांगp",%%a2\n\t" \
	"movel	%%a2@,%%a2"

#पूर्ण_अगर

#पूर्ण_अगर /* __M68K_ENTRY_H */
