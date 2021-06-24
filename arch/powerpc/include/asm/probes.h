<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_PROBES_H
#घोषणा _ASM_POWERPC_PROBES_H
#अगर_घोषित __KERNEL__
/*
 * Definitions common to probes files
 *
 * Copyright IBM Corporation, 2012
 */
#समावेश <linux/types.h>

प्रकार u32 ppc_opcode_t;
#घोषणा BREAKPOINT_INSTRUCTION	0x7fe00008	/* trap */

/* Trap definitions per ISA */
#घोषणा IS_TW(instr)		(((instr) & 0xfc0007fe) == 0x7c000008)
#घोषणा IS_TD(instr)		(((instr) & 0xfc0007fe) == 0x7c000088)
#घोषणा IS_TDI(instr)		(((instr) & 0xfc000000) == 0x08000000)
#घोषणा IS_TWI(instr)		(((instr) & 0xfc000000) == 0x0c000000)

#अगर_घोषित CONFIG_PPC64
#घोषणा is_trap(instr)		(IS_TW(instr) || IS_TD(instr) || \
				IS_TWI(instr) || IS_TDI(instr))
#अन्यथा
#घोषणा is_trap(instr)		(IS_TW(instr) || IS_TWI(instr))
#पूर्ण_अगर /* CONFIG_PPC64 */

#अगर_घोषित CONFIG_PPC_ADV_DEBUG_REGS
#घोषणा MSR_SINGLESTEP	(MSR_DE)
#अन्यथा
#घोषणा MSR_SINGLESTEP	(MSR_SE)
#पूर्ण_अगर

/* Enable single stepping क्रम the current task */
अटल अंतरभूत व्योम enable_single_step(काष्ठा pt_regs *regs)
अणु
	regs->msr |= MSR_SINGLESTEP;
#अगर_घोषित CONFIG_PPC_ADV_DEBUG_REGS
	/*
	 * We turn off Critical Input Exception(CE) to ensure that the single
	 * step will be क्रम the inकाष्ठाion we have the probe on; अगर we करोn't,
	 * it is possible we'd get the single step reported क्रम CE.
	 */
	regs->msr &= ~MSR_CE;
	mtspr(SPRN_DBCR0, mfspr(SPRN_DBCR0) | DBCR0_IC | DBCR0_IDM);
#अगर_घोषित CONFIG_PPC_47x
	isync();
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण


#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर	/* _ASM_POWERPC_PROBES_H */
