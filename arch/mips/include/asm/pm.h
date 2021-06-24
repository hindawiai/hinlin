<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2014 Imagination Technologies Ltd
 *
 * PM helper macros क्रम CPU घातer off (e.g. Suspend-to-RAM).
 */

#अगर_अघोषित __ASM_PM_H
#घोषणा __ASM_PM_H

#अगर_घोषित __ASSEMBLY__

#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/regdef.h>

/* Save CPU state to stack क्रम suspend to RAM */
.macro SUSPEND_SAVE_REGS
	subu	sp, PT_SIZE
	/* Call preserved GPRs */
	LONG_S	$16, PT_R16(sp)
	LONG_S	$17, PT_R17(sp)
	LONG_S	$18, PT_R18(sp)
	LONG_S	$19, PT_R19(sp)
	LONG_S	$20, PT_R20(sp)
	LONG_S	$21, PT_R21(sp)
	LONG_S	$22, PT_R22(sp)
	LONG_S	$23, PT_R23(sp)
	LONG_S	$28, PT_R28(sp)
	LONG_S	$30, PT_R30(sp)
	LONG_S	$31, PT_R31(sp)
	/* A couple of CP0 रेजिस्टरs with space in pt_regs */
	mfc0	k0, CP0_STATUS
	LONG_S	k0, PT_STATUS(sp)
.endm

/* Restore CPU state from stack after resume from RAM */
.macro RESUME_RESTORE_REGS_RETURN
	.set	push
	.set	noreorder
	/* A couple of CP0 रेजिस्टरs with space in pt_regs */
	LONG_L	k0, PT_STATUS(sp)
	mtc0	k0, CP0_STATUS
	/* Call preserved GPRs */
	LONG_L	$16, PT_R16(sp)
	LONG_L	$17, PT_R17(sp)
	LONG_L	$18, PT_R18(sp)
	LONG_L	$19, PT_R19(sp)
	LONG_L	$20, PT_R20(sp)
	LONG_L	$21, PT_R21(sp)
	LONG_L	$22, PT_R22(sp)
	LONG_L	$23, PT_R23(sp)
	LONG_L	$28, PT_R28(sp)
	LONG_L	$30, PT_R30(sp)
	LONG_L	$31, PT_R31(sp)
	/* Pop and वापस */
	jr	ra
	 addiu	sp, PT_SIZE
	.set	pop
.endm

/* Get address of अटल suspend state पूर्णांकo t1 */
.macro LA_STATIC_SUSPEND
	la	t1, mips_अटल_suspend_state
.endm

/* Save important CPU state क्रम early restoration to global data */
.macro SUSPEND_SAVE_STATIC
#अगर_घोषित CONFIG_EVA
	/*
	 * Segment configuration is saved in global data where it can be easily
	 * reloaded without depending on the segment configuration.
	 */
	mfc0	k0, CP0_PAGEMASK, 2	/* SegCtl0 */
	LONG_S	k0, SSS_SEGCTL0(t1)
	mfc0	k0, CP0_PAGEMASK, 3	/* SegCtl1 */
	LONG_S	k0, SSS_SEGCTL1(t1)
	mfc0	k0, CP0_PAGEMASK, 4	/* SegCtl2 */
	LONG_S	k0, SSS_SEGCTL2(t1)
#पूर्ण_अगर
	/* save stack poपूर्णांकer (poपूर्णांकing to GPRs) */
	LONG_S	sp, SSS_SP(t1)
.endm

/* Restore important CPU state early from global data */
.macro RESUME_RESTORE_STATIC
#अगर_घोषित CONFIG_EVA
	/*
	 * Segment configuration must be restored prior to any access to
	 * allocated memory, as it may reside outside of the legacy kernel
	 * segments.
	 */
	LONG_L	k0, SSS_SEGCTL0(t1)
	mtc0	k0, CP0_PAGEMASK, 2	/* SegCtl0 */
	LONG_L	k0, SSS_SEGCTL1(t1)
	mtc0	k0, CP0_PAGEMASK, 3	/* SegCtl1 */
	LONG_L	k0, SSS_SEGCTL2(t1)
	mtc0	k0, CP0_PAGEMASK, 4	/* SegCtl2 */
	tlbw_use_hazard
#पूर्ण_अगर
	/* restore stack poपूर्णांकer (poपूर्णांकing to GPRs) */
	LONG_L	sp, SSS_SP(t1)
.endm

/* flush caches to make sure context has reached memory */
.macro SUSPEND_CACHE_FLUSH
	.बाह्य	__wback_cache_all
	.set	push
	.set	noreorder
	la	t1, __wback_cache_all
	LONG_L	t0, 0(t1)
	jalr	t0
	 nop
	.set	pop
 .endm

/* Save suspend state and flush data caches to RAM */
.macro SUSPEND_SAVE
	SUSPEND_SAVE_REGS
	LA_STATIC_SUSPEND
	SUSPEND_SAVE_STATIC
	SUSPEND_CACHE_FLUSH
.endm

/* Restore saved state after resume from RAM and वापस */
.macro RESUME_RESTORE_RETURN
	LA_STATIC_SUSPEND
	RESUME_RESTORE_STATIC
	RESUME_RESTORE_REGS_RETURN
.endm

#अन्यथा /* __ASSEMBLY__ */

/**
 * काष्ठा mips_अटल_suspend_state - Core saved CPU state across S2R.
 * @segctl:	CP0 Segment control रेजिस्टरs.
 * @sp:		Stack frame where GP रेजिस्टर context is saved.
 *
 * This काष्ठाure contains minimal CPU state that must be saved in अटल kernel
 * data in order to be able to restore the rest of the state. This includes
 * segmentation configuration in the हाल of EVA being enabled, as they must be
 * restored prior to any kदो_स्मृति'd memory being referenced (even the stack
 * poपूर्णांकer).
 */
काष्ठा mips_अटल_suspend_state अणु
#अगर_घोषित CONFIG_EVA
	अचिन्हित दीर्घ segctl[3];
#पूर्ण_अगर
	अचिन्हित दीर्घ sp;
पूर्ण;

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_PM_HELPERS_H */
