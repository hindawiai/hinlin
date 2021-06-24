<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014-15 Synopsys, Inc. (www.synopsys.com)
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __ASM_ARC_ENTRY_H
#घोषणा __ASM_ARC_ENTRY_H

#समावेश <यंत्र/unistd.h>		/* For NR_syscalls defination */
#समावेश <यंत्र/arcregs.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/processor.h>	/* For VMALLOC_START */
#समावेश <यंत्र/mmu.h>

#अगर_घोषित CONFIG_ISA_ARCOMPACT
#समावेश <यंत्र/entry-compact.h>	/* ISA specअगरic bits */
#अन्यथा
#समावेश <यंत्र/entry-arcv2.h>
#पूर्ण_अगर

/* Note on the LD/ST addr modes with addr reg wback
 *
 * LD.a same as LD.aw
 *
 * LD.a    reg1, [reg2, x]  => Pre Incr
 *      Eff Addr क्रम load = [reg2 + x]
 *
 * LD.ab   reg1, [reg2, x]  => Post Incr
 *      Eff Addr क्रम load = [reg2]
 */

.macro PUSH reg
	st.a	\लeg, [sp, -4]
.endm

.macro PUSHAX aux
	lr	r9, [\चux]
	PUSH	r9
.endm

.macro POP reg
	ld.ab	\लeg, [sp, 4]
.endm

.macro POPAX aux
	POP	r9
	sr	r9, [\चux]
.endm

/*--------------------------------------------------------------
 * Helpers to save/restore Scratch Regs:
 * used by Interrupt/Exception Prologue/Epilogue
 *-------------------------------------------------------------*/
.macro  SAVE_R0_TO_R12
	PUSH	r0
	PUSH	r1
	PUSH	r2
	PUSH	r3
	PUSH	r4
	PUSH	r5
	PUSH	r6
	PUSH	r7
	PUSH	r8
	PUSH	r9
	PUSH	r10
	PUSH	r11
	PUSH	r12
.endm

.macro RESTORE_R12_TO_R0
	POP	r12
	POP	r11
	POP	r10
	POP	r9
	POP	r8
	POP	r7
	POP	r6
	POP	r5
	POP	r4
	POP	r3
	POP	r2
	POP	r1
	POP	r0

.endm

/*--------------------------------------------------------------
 * Helpers to save/restore callee-saved regs:
 * used by several macros below
 *-------------------------------------------------------------*/
.macro SAVE_R13_TO_R24
	PUSH	r13
	PUSH	r14
	PUSH	r15
	PUSH	r16
	PUSH	r17
	PUSH	r18
	PUSH	r19
	PUSH	r20
	PUSH	r21
	PUSH	r22
	PUSH	r23
	PUSH	r24
.endm

.macro RESTORE_R24_TO_R13
	POP	r24
	POP	r23
	POP	r22
	POP	r21
	POP	r20
	POP	r19
	POP	r18
	POP	r17
	POP	r16
	POP	r15
	POP	r14
	POP	r13
.endm

/*--------------------------------------------------------------
 * Collect User Mode callee regs as काष्ठा callee_regs - needed by
 * विभाजन/करो_संकेत/unaligned-access-emulation.
 * (By शेष only scratch regs are saved on entry to kernel)
 *
 * Special handling क्रम r25 अगर used क्रम caching Task Poपूर्णांकer.
 * It would have been saved in task->thपढ़ो.user_r25 alपढ़ोy, but to keep
 * the पूर्णांकerface same it is copied पूर्णांकo regular r25 placeholder in
 * काष्ठा callee_regs.
 *-------------------------------------------------------------*/
.macro SAVE_CALLEE_SAVED_USER

	mov	r12, sp		; save SP as ref to pt_regs
	SAVE_R13_TO_R24

#अगर_घोषित CONFIG_ARC_CURR_IN_REG
	; Retrieve orig r25 and save it with rest of callee_regs
	ld	r12, [r12, PT_user_r25]
	PUSH	r12
#अन्यथा
	PUSH	r25
#पूर्ण_अगर

.endm

/*--------------------------------------------------------------
 * Save kernel Mode callee regs at the समय of Contect Switch.
 *
 * Special handling क्रम r25 अगर used क्रम caching Task Poपूर्णांकer.
 * Kernel simply skips saving it since it will be loaded with
 * incoming task poपूर्णांकer anyways
 *-------------------------------------------------------------*/
.macro SAVE_CALLEE_SAVED_KERNEL

	SAVE_R13_TO_R24

#अगर_घोषित CONFIG_ARC_CURR_IN_REG
	sub     sp, sp, 4
#अन्यथा
	PUSH	r25
#पूर्ण_अगर
.endm

/*--------------------------------------------------------------
 * Opposite of SAVE_CALLEE_SAVED_KERNEL
 *-------------------------------------------------------------*/
.macro RESTORE_CALLEE_SAVED_KERNEL

#अगर_घोषित CONFIG_ARC_CURR_IN_REG
	add     sp, sp, 4  /* skip usual r25 placeholder */
#अन्यथा
	POP	r25
#पूर्ण_अगर
	RESTORE_R24_TO_R13
.endm

/*--------------------------------------------------------------
 * Opposite of SAVE_CALLEE_SAVED_USER
 *
 * ptrace tracer or unaligned-access fixup might have changed a user mode
 * callee reg which is saved back to usual r25 storage location
 *-------------------------------------------------------------*/
.macro RESTORE_CALLEE_SAVED_USER

#अगर_घोषित CONFIG_ARC_CURR_IN_REG
	POP	r12
#अन्यथा
	POP	r25
#पूर्ण_अगर
	RESTORE_R24_TO_R13

	; SP is back to start of pt_regs
#अगर_घोषित CONFIG_ARC_CURR_IN_REG
	st	r12, [sp, PT_user_r25]
#पूर्ण_अगर
.endm

/*--------------------------------------------------------------
 * Super FAST Restore callee saved regs by simply re-adjusting SP
 *-------------------------------------------------------------*/
.macro DISCARD_CALLEE_SAVED_USER
	add     sp, sp, SZ_CALLEE_REGS
.endm

/*-------------------------------------------------------------
 * given a tsk काष्ठा, get to the base of it's kernel mode stack
 * tsk->thपढ़ो_info is really a PAGE, whose bottom hoists stack
 * which grows upwards towards thपढ़ो_info
 *------------------------------------------------------------*/

.macro GET_TSK_STACK_BASE tsk, out

	/* Get task->thपढ़ो_info (this is essentially start of a PAGE) */
	ld  \out, [\टsk, TASK_THREAD_INFO]

	/* Go to end of page where stack begins (grows upwards) */
	add2 \out, \out, (THREAD_SIZE)/4

.endm

/*
 * @reg [OUT] thपढ़ो_info->flags of "current"
 */
.macro GET_CURR_THR_INFO_FLAGS  reg
	GET_CURR_THR_INFO_FROM_SP  \लeg
	ld  \लeg, [\लeg, THREAD_INFO_FLAGS]
.endm

#अगर_घोषित CONFIG_SMP

/*-------------------------------------------------
 * Retrieve the current running task on this CPU
 * 1. Determine curr CPU id.
 * 2. Use it to index पूर्णांकo _current_task[ ]
 */
.macro  GET_CURR_TASK_ON_CPU   reg
	GET_CPU_ID  \लeg
	ld.as  \लeg, [@_current_task, \लeg]
.endm

/*-------------------------------------------------
 * Save a new task as the "current" task on this CPU
 * 1. Determine curr CPU id.
 * 2. Use it to index पूर्णांकo _current_task[ ]
 *
 * Coded dअगरferently than GET_CURR_TASK_ON_CPU (which uses LD.AS)
 * because ST r0, [r1, offset] can ONLY have s9 @offset
 * जबतक   LD can take s9 (4 byte insn) or LIMM (8 byte insn)
 */

.macro  SET_CURR_TASK_ON_CPU    tsk, पंचांगp
	GET_CPU_ID  \टmp
	add2 \टmp, @_current_task, \टmp
	st   \टsk, [\टmp]
#अगर_घोषित CONFIG_ARC_CURR_IN_REG
	mov r25, \टsk
#पूर्ण_अगर

.endm


#अन्यथा   /* Uniprocessor implementation of macros */

.macro  GET_CURR_TASK_ON_CPU    reg
	ld  \लeg, [@_current_task]
.endm

.macro  SET_CURR_TASK_ON_CPU    tsk, पंचांगp
	st  \टsk, [@_current_task]
#अगर_घोषित CONFIG_ARC_CURR_IN_REG
	mov r25, \टsk
#पूर्ण_अगर
.endm

#पूर्ण_अगर /* SMP / UNI */

/* ------------------------------------------------------------------
 * Get the ptr to some field of Current Task at @off in task काष्ठा
 *  -Uses r25 क्रम Current task ptr अगर that is enabled
 */

#अगर_घोषित CONFIG_ARC_CURR_IN_REG

.macro GET_CURR_TASK_FIELD_PTR  off,  reg
	add \लeg, r25, \off
.endm

#अन्यथा

.macro GET_CURR_TASK_FIELD_PTR  off,  reg
	GET_CURR_TASK_ON_CPU  \लeg
	add \लeg, \लeg, \off
.endm

#पूर्ण_अगर	/* CONFIG_ARC_CURR_IN_REG */

#पूर्ण_अगर  /* __ASM_ARC_ENTRY_H */
