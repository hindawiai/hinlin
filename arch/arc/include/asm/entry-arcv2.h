<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_ARC_ENTRY_ARCV2_H
#घोषणा __ASM_ARC_ENTRY_ARCV2_H

#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/dsp-impl.h>
#समावेश <यंत्र/irqflags-arcv2.h>
#समावेश <यंत्र/thपढ़ो_info.h>	/* For THREAD_SIZE */

/*
 * Interrupt/Exception stack layout (pt_regs) क्रम ARCv2
 *   (End of काष्ठा aligned to end of page [unless nested])
 *
 *  INTERRUPT                          EXCEPTION
 *
 *    manual    ---------------------  manual
 *              |      orig_r0      |
 *              |      event/ECR    |
 *              |      bta          |
 *              |      user_r25     |
 *              |      gp           |
 *              |      fp           |
 *              |      sp           |
 *              |      r12          |
 *              |      r30          |
 *              |      r58          |
 *              |      r59          |
 *  hw स्वतःsave ---------------------
 *    optional  |      r0           |
 *              |      r1           |
 *              ~                   ~
 *              |      r9           |
 *              |      r10          |
 *              |      r11          |
 *              |      blink        |
 *              |      lpe          |
 *              |      lps          |
 *              |      lpc          |
 *              |      ei base      |
 *              |      ldi base     |
 *              |      jli base     |
 *              ---------------------
 *  hw स्वतःsave |       pc / eret   |
 *   mandatory  | stat32 / erstatus |
 *              ---------------------
 */

/*------------------------------------------------------------------------*/
.macro INTERRUPT_PROLOGUE

	; (A) Beक्रमe jumping to Interrupt Vector, hardware micro-ops did following:
	;   1. SP स्वतः-चयनed to kernel mode stack
	;   2. STATUS32.Z flag set अगर in U mode at समय of पूर्णांकerrupt (U:1,K:0)
	;   3. Auto save: (mandatory) Push PC and STAT32 on stack
	;                 hardware करोes even अगर CONFIG_ARC_IRQ_NO_AUTOSAVE
	;   4. Auto save: (optional) r0-r11, blink, LPE,LPS,LPC, JLI,LDI,EI
	;
	; (B) Manually saved some regs: r12,r25,r30, sp,fp,gp, ACCL pair

#अगर_घोषित CONFIG_ARC_IRQ_NO_AUTOSAVE
	; carve pt_regs on stack (हाल #3), PC/STAT32 alपढ़ोy on stack
	sub	sp, sp, SZ_PT_REGS - 8

	__SAVE_REGखाता_HARD
#अन्यथा
	; carve pt_regs on stack (हाल #4), which grew partially alपढ़ोy
	sub	sp, sp, PT_r0
#पूर्ण_अगर

	__SAVE_REGखाता_SOFT
.endm

/*------------------------------------------------------------------------*/
.macro EXCEPTION_PROLOGUE

	; (A) Beक्रमe jumping to Exception Vector, hardware micro-ops did following:
	;   1. SP स्वतः-चयनed to kernel mode stack
	;   2. STATUS32.Z flag set अगर in U mode at समय of exception (U:1,K:0)
	;
	; (B) Manually save the complete reg file below

	sub	sp, sp, SZ_PT_REGS	; carve pt_regs

	; _HARD saves r10 clobbered by _SOFT as scratch hence comes first

	__SAVE_REGखाता_HARD
	__SAVE_REGखाता_SOFT

	st	r0, [sp]	; orig_r0

	lr	r10, [eret]
	lr	r11, [erstatus]
	ST2	r10, r11, PT_ret

	lr	r10, [ecr]
	lr	r11, [erbta]
	ST2	r10, r11, PT_event

	; OUTPUT: r10 has ECR expected by EV_Trap
.endm

/*------------------------------------------------------------------------
 * This macro saves the रेजिस्टरs manually which would normally be स्वतःsaved
 * by hardware on taken पूर्णांकerrupts. It is used by
 *   - exception handlers (which करोn't have स्वतःsave)
 *   - पूर्णांकerrupt स्वतःsave disabled due to CONFIG_ARC_IRQ_NO_AUTOSAVE
 */
.macro __SAVE_REGखाता_HARD

	ST2	r0,  r1,  PT_r0
	ST2	r2,  r3,  PT_r2
	ST2	r4,  r5,  PT_r4
	ST2	r6,  r7,  PT_r6
	ST2	r8,  r9,  PT_r8
	ST2	r10, r11, PT_r10

	st	blink, [sp, PT_blink]

	lr	r10, [lp_end]
	lr	r11, [lp_start]
	ST2	r10, r11, PT_lpe

	st	lp_count, [sp, PT_lpc]

	; skip JLI, LDI, EI क्रम now
.endm

/*------------------------------------------------------------------------
 * This macros saves a bunch of other रेजिस्टरs which can't be स्वतःsaved क्रम
 * various reasons:
 *   - r12: the last caller saved scratch reg since hardware saves in pairs so r0-r11
 *   - r30: मुक्त reg, used by gcc as scratch
 *   - ACCL/ACCH pair when they exist
 */
.macro __SAVE_REGखाता_SOFT

	ST2	gp, fp, PT_r26		; gp (r26), fp (r27)

	st	r12, [sp, PT_sp + 4]
	st	r30, [sp, PT_sp + 8]

	; Saving pt_regs->sp correctly requires some extra work due to the way
	; Auto stack चयन works
	;  - U mode: retrieve it from AUX_USER_SP
	;  - K mode: add the offset from current SP where H/w starts स्वतः push
	;
	; 1. Utilize the fact that Z bit is set अगर Intr taken in U mode
	; 2. Upon entry SP is always saved (क्रम any inspection, unwinding etc),
	;    but on वापस, restored only अगर U mode

	lr	r10, [AUX_USER_SP]	; U mode SP

	; ISA requires ADD.nz to have same dest and src reg opeअक्रमs
	mov.nz	r10, sp
	add.nz	r10, r10, SZ_PT_REGS	; K mode SP

	st	r10, [sp, PT_sp]	; SP (pt_regs->sp)

#अगर_घोषित CONFIG_ARC_CURR_IN_REG
	st	r25, [sp, PT_user_r25]
	GET_CURR_TASK_ON_CPU	r25
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARC_HAS_ACCL_REGS
	ST2	r58, r59, PT_r58
#पूर्ण_अगर

	/* clobbers r10, r11 रेजिस्टरs pair */
	DSP_SAVE_REGखाता_IRQ
.endm

/*------------------------------------------------------------------------*/
.macro __RESTORE_REGखाता_SOFT

	LD2	gp, fp, PT_r26		; gp (r26), fp (r27)

	ld	r12, [sp, PT_r12]
	ld	r30, [sp, PT_r30]

	; Restore SP (पूर्णांकo AUX_USER_SP) only अगर वापसing to U mode
	;  - क्रम K mode, it will be implicitly restored as stack is unwound
	;  - Z flag set on K is inverse of what hardware करोes on पूर्णांकerrupt entry
	;    but that करोesn't really matter
	bz	1f

	ld	r10, [sp, PT_sp]	; SP (pt_regs->sp)
	sr	r10, [AUX_USER_SP]
1:

#अगर_घोषित CONFIG_ARC_CURR_IN_REG
	ld	r25, [sp, PT_user_r25]
#पूर्ण_अगर

	/* clobbers r10, r11 रेजिस्टरs pair */
	DSP_RESTORE_REGखाता_IRQ

#अगर_घोषित CONFIG_ARC_HAS_ACCL_REGS
	LD2	r58, r59, PT_r58
#पूर्ण_अगर
.endm

/*------------------------------------------------------------------------*/
.macro __RESTORE_REGखाता_HARD

	ld	blink, [sp, PT_blink]

	LD2	r10, r11, PT_lpe
	sr	r10, [lp_end]
	sr	r11, [lp_start]

	ld	r10, [sp, PT_lpc]	; lp_count can't be target of LD
	mov	lp_count, r10

	LD2	r0,  r1,  PT_r0
	LD2	r2,  r3,  PT_r2
	LD2	r4,  r5,  PT_r4
	LD2	r6,  r7,  PT_r6
	LD2	r8,  r9,  PT_r8
	LD2	r10, r11, PT_r10
.endm


/*------------------------------------------------------------------------*/
.macro INTERRUPT_EPILOGUE

	; INPUT: r0 has STAT32 of calling context
	; INPUT: Z flag set अगर वापसing to K mode

	; _SOFT clobbers r10 restored by _HARD hence the order

	__RESTORE_REGखाता_SOFT

#अगर_घोषित CONFIG_ARC_IRQ_NO_AUTOSAVE
	__RESTORE_REGखाता_HARD

	; SP poपूर्णांकs to PC/STAT32: hw restores them despite NO_AUTOSAVE
	add	sp, sp, SZ_PT_REGS - 8
#अन्यथा
	add	sp, sp, PT_r0
#पूर्ण_अगर

.endm

/*------------------------------------------------------------------------*/
.macro EXCEPTION_EPILOGUE

	; INPUT: r0 has STAT32 of calling context

	btst	r0, STATUS_U_BIT	; Z flag set अगर K, used in restoring SP

	ld	r10, [sp, PT_event + 4]
	sr	r10, [erbta]

	LD2	r10, r11, PT_ret
	sr	r10, [eret]
	sr	r11, [erstatus]

	__RESTORE_REGखाता_SOFT
	__RESTORE_REGखाता_HARD

	add	sp, sp, SZ_PT_REGS
.endm

.macro FAKE_RET_FROM_EXCPN
	lr      r9, [status32]
	bic     r9, r9, STATUS_AE_MASK
	or      r9, r9, STATUS_IE_MASK
	kflag   r9
.endm

/* Get thपढ़ो_info of "current" tsk */
.macro GET_CURR_THR_INFO_FROM_SP  reg
	bmskn \लeg, sp, THREAD_SHIFT - 1
.endm

/* Get CPU-ID of this core */
.macro  GET_CPU_ID  reg
	lr  \लeg, [identity]
	xbfu \लeg, \लeg, 0xE8	/* 00111    01000 */
				/* M = 8-1  N = 8 */
.endm

#पूर्ण_अगर
