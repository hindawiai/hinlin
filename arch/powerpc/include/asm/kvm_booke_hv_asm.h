<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2010-2011 Freescale Semiconductor, Inc.
 */

#अगर_अघोषित ASM_KVM_BOOKE_HV_ASM_H
#घोषणा ASM_KVM_BOOKE_HV_ASM_H

#समावेश <यंत्र/feature-fixups.h>

#अगर_घोषित __ASSEMBLY__

/*
 * All exceptions from guest state must go through KVM
 * (except क्रम those which are delivered directly to the guest) --
 * there are no exceptions क्रम which we fall through directly to
 * the normal host handler.
 *
 * 32-bit host
 * Expected inमाला_दो (normal exceptions):
 *   SCRATCH0 = saved r10
 *   r10 = thपढ़ो काष्ठा
 *   r11 = appropriate SRR1 variant (currently used as scratch)
 *   r13 = saved CR
 *   *(r10 + THREAD_NORMSAVE(0)) = saved r11
 *   *(r10 + THREAD_NORMSAVE(2)) = saved r13
 *
 * Expected inमाला_दो (crit/mcheck/debug exceptions):
 *   appropriate SCRATCH = saved r8
 *   r8 = exception level stack frame
 *   r9 = *(r8 + _CCR) = saved CR
 *   r11 = appropriate SRR1 variant (currently used as scratch)
 *   *(r8 + GPR9) = saved r9
 *   *(r8 + GPR10) = saved r10 (r10 not yet clobbered)
 *   *(r8 + GPR11) = saved r11
 *
 * 64-bit host
 * Expected inमाला_दो (GEN/GDBELL/DBG/CRIT/MC exception types):
 *  r10 = saved CR
 *  r13 = PACA_POINTER
 *  *(r13 + PACA_EX##type + EX_R10) = saved r10
 *  *(r13 + PACA_EX##type + EX_R11) = saved r11
 *  SPRN_SPRG_##type##_SCRATCH = saved r13
 *
 * Expected inमाला_दो (TLB exception type):
 *  r10 = saved CR
 *  r12 = extlb poपूर्णांकer
 *  r13 = PACA_POINTER
 *  *(r12 + EX_TLB_R10) = saved r10
 *  *(r12 + EX_TLB_R11) = saved r11
 *  *(r12 + EX_TLB_R13) = saved r13
 *  SPRN_SPRG_GEN_SCRATCH = saved r12
 *
 * Only the bolted version of TLB miss exception handlers is supported now.
 */
.macro DO_KVM पूर्णांकno srr1
#अगर_घोषित CONFIG_KVM_BOOKE_HV
BEGIN_FTR_SECTION
	mtocrf	0x80, r11	/* check MSR[GS] without clobbering reg */
	bf	3, 1975f
	b	kvmppc_handler_\पूर्णांकno\()_\srr1
1975:
END_FTR_SECTION_IFSET(CPU_FTR_EMB_HV)
#पूर्ण_अगर
.endm

#पूर्ण_अगर /*__ASSEMBLY__ */
#पूर्ण_अगर /* ASM_KVM_BOOKE_HV_ASM_H */
