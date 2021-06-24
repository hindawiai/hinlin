<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_KREGS_H
#घोषणा _ASM_IA64_KREGS_H

/*
 * Copyright (C) 2001-2002 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */
/*
 * This file defines the kernel रेजिस्टर usage convention used by Linux/ia64.
 */

/*
 * Kernel रेजिस्टरs:
 */
#घोषणा IA64_KR_IO_BASE		0	/* ar.k0: legacy I/O base address */
#घोषणा IA64_KR_TSSD		1	/* ar.k1: IVE uses this as the TSSD */
#घोषणा IA64_KR_PER_CPU_DATA	3	/* ar.k3: physical per-CPU base */
#घोषणा IA64_KR_CURRENT_STACK	4	/* ar.k4: what's mapped in IA64_TR_CURRENT_STACK */
#घोषणा IA64_KR_FPU_OWNER	5	/* ar.k5: fpu-owner (UP only, at the moment) */
#घोषणा IA64_KR_CURRENT		6	/* ar.k6: "current" task poपूर्णांकer */
#घोषणा IA64_KR_PT_BASE		7	/* ar.k7: page table base address (physical) */

#घोषणा _IA64_KR_PASTE(x,y)	x##y
#घोषणा _IA64_KR_PREFIX(n)	_IA64_KR_PASTE(ar.k, n)
#घोषणा IA64_KR(n)		_IA64_KR_PREFIX(IA64_KR_##n)

/*
 * Translation रेजिस्टरs:
 */
#घोषणा IA64_TR_KERNEL		0	/* itr0, dtr0: maps kernel image (code & data) */
#घोषणा IA64_TR_PALCODE		1	/* itr1: maps PALcode as required by EFI */
#घोषणा IA64_TR_CURRENT_STACK	1	/* dtr1: maps kernel's memory- & रेजिस्टर-stacks */

#घोषणा IA64_TR_ALLOC_BASE	2 	/* itr&dtr: Base of dynamic TR resource*/
#घोषणा IA64_TR_ALLOC_MAX	64 	/* Max number क्रम dynamic use*/

/* Processor status रेजिस्टर bits: */
#घोषणा IA64_PSR_BE_BIT		1
#घोषणा IA64_PSR_UP_BIT		2
#घोषणा IA64_PSR_AC_BIT		3
#घोषणा IA64_PSR_MFL_BIT	4
#घोषणा IA64_PSR_MFH_BIT	5
#घोषणा IA64_PSR_IC_BIT		13
#घोषणा IA64_PSR_I_BIT		14
#घोषणा IA64_PSR_PK_BIT		15
#घोषणा IA64_PSR_DT_BIT		17
#घोषणा IA64_PSR_DFL_BIT	18
#घोषणा IA64_PSR_DFH_BIT	19
#घोषणा IA64_PSR_SP_BIT		20
#घोषणा IA64_PSR_PP_BIT		21
#घोषणा IA64_PSR_DI_BIT		22
#घोषणा IA64_PSR_SI_BIT		23
#घोषणा IA64_PSR_DB_BIT		24
#घोषणा IA64_PSR_LP_BIT		25
#घोषणा IA64_PSR_TB_BIT		26
#घोषणा IA64_PSR_RT_BIT		27
/* The following are not affected by save_flags()/restore_flags(): */
#घोषणा IA64_PSR_CPL0_BIT	32
#घोषणा IA64_PSR_CPL1_BIT	33
#घोषणा IA64_PSR_IS_BIT		34
#घोषणा IA64_PSR_MC_BIT		35
#घोषणा IA64_PSR_IT_BIT		36
#घोषणा IA64_PSR_ID_BIT		37
#घोषणा IA64_PSR_DA_BIT		38
#घोषणा IA64_PSR_DD_BIT		39
#घोषणा IA64_PSR_SS_BIT		40
#घोषणा IA64_PSR_RI_BIT		41
#घोषणा IA64_PSR_ED_BIT		43
#घोषणा IA64_PSR_BN_BIT		44
#घोषणा IA64_PSR_IA_BIT		45

/* A mask of PSR bits that we generally करोn't want to inherit across a clone2() or an
   execve().  Only list flags here that need to be cleared/set क्रम BOTH clone2() and
   execve().  */
#घोषणा IA64_PSR_BITS_TO_CLEAR	(IA64_PSR_MFL | IA64_PSR_MFH | IA64_PSR_DB | IA64_PSR_LP | \
				 IA64_PSR_TB  | IA64_PSR_ID  | IA64_PSR_DA | IA64_PSR_DD | \
				 IA64_PSR_SS  | IA64_PSR_ED  | IA64_PSR_IA)
#घोषणा IA64_PSR_BITS_TO_SET	(IA64_PSR_DFH | IA64_PSR_SP)

#घोषणा IA64_PSR_BE	(__IA64_UL(1) << IA64_PSR_BE_BIT)
#घोषणा IA64_PSR_UP	(__IA64_UL(1) << IA64_PSR_UP_BIT)
#घोषणा IA64_PSR_AC	(__IA64_UL(1) << IA64_PSR_AC_BIT)
#घोषणा IA64_PSR_MFL	(__IA64_UL(1) << IA64_PSR_MFL_BIT)
#घोषणा IA64_PSR_MFH	(__IA64_UL(1) << IA64_PSR_MFH_BIT)
#घोषणा IA64_PSR_IC	(__IA64_UL(1) << IA64_PSR_IC_BIT)
#घोषणा IA64_PSR_I	(__IA64_UL(1) << IA64_PSR_I_BIT)
#घोषणा IA64_PSR_PK	(__IA64_UL(1) << IA64_PSR_PK_BIT)
#घोषणा IA64_PSR_DT	(__IA64_UL(1) << IA64_PSR_DT_BIT)
#घोषणा IA64_PSR_DFL	(__IA64_UL(1) << IA64_PSR_DFL_BIT)
#घोषणा IA64_PSR_DFH	(__IA64_UL(1) << IA64_PSR_DFH_BIT)
#घोषणा IA64_PSR_SP	(__IA64_UL(1) << IA64_PSR_SP_BIT)
#घोषणा IA64_PSR_PP	(__IA64_UL(1) << IA64_PSR_PP_BIT)
#घोषणा IA64_PSR_DI	(__IA64_UL(1) << IA64_PSR_DI_BIT)
#घोषणा IA64_PSR_SI	(__IA64_UL(1) << IA64_PSR_SI_BIT)
#घोषणा IA64_PSR_DB	(__IA64_UL(1) << IA64_PSR_DB_BIT)
#घोषणा IA64_PSR_LP	(__IA64_UL(1) << IA64_PSR_LP_BIT)
#घोषणा IA64_PSR_TB	(__IA64_UL(1) << IA64_PSR_TB_BIT)
#घोषणा IA64_PSR_RT	(__IA64_UL(1) << IA64_PSR_RT_BIT)
/* The following are not affected by save_flags()/restore_flags(): */
#घोषणा IA64_PSR_CPL	(__IA64_UL(3) << IA64_PSR_CPL0_BIT)
#घोषणा IA64_PSR_IS	(__IA64_UL(1) << IA64_PSR_IS_BIT)
#घोषणा IA64_PSR_MC	(__IA64_UL(1) << IA64_PSR_MC_BIT)
#घोषणा IA64_PSR_IT	(__IA64_UL(1) << IA64_PSR_IT_BIT)
#घोषणा IA64_PSR_ID	(__IA64_UL(1) << IA64_PSR_ID_BIT)
#घोषणा IA64_PSR_DA	(__IA64_UL(1) << IA64_PSR_DA_BIT)
#घोषणा IA64_PSR_DD	(__IA64_UL(1) << IA64_PSR_DD_BIT)
#घोषणा IA64_PSR_SS	(__IA64_UL(1) << IA64_PSR_SS_BIT)
#घोषणा IA64_PSR_RI	(__IA64_UL(3) << IA64_PSR_RI_BIT)
#घोषणा IA64_PSR_ED	(__IA64_UL(1) << IA64_PSR_ED_BIT)
#घोषणा IA64_PSR_BN	(__IA64_UL(1) << IA64_PSR_BN_BIT)
#घोषणा IA64_PSR_IA	(__IA64_UL(1) << IA64_PSR_IA_BIT)

/* User mask bits: */
#घोषणा IA64_PSR_UM	(IA64_PSR_BE | IA64_PSR_UP | IA64_PSR_AC | IA64_PSR_MFL | IA64_PSR_MFH)

/* Default Control Register */
#घोषणा IA64_DCR_PP_BIT		 0	/* privileged perक्रमmance monitor शेष */
#घोषणा IA64_DCR_BE_BIT		 1	/* big-endian शेष */
#घोषणा IA64_DCR_LC_BIT		 2	/* ia32 lock-check enable */
#घोषणा IA64_DCR_DM_BIT		 8	/* defer TLB miss faults */
#घोषणा IA64_DCR_DP_BIT		 9	/* defer page-not-present faults */
#घोषणा IA64_DCR_DK_BIT		10	/* defer key miss faults */
#घोषणा IA64_DCR_DX_BIT		11	/* defer key permission faults */
#घोषणा IA64_DCR_DR_BIT		12	/* defer access right faults */
#घोषणा IA64_DCR_DA_BIT		13	/* defer access bit faults */
#घोषणा IA64_DCR_DD_BIT		14	/* defer debug faults */

#घोषणा IA64_DCR_PP	(__IA64_UL(1) << IA64_DCR_PP_BIT)
#घोषणा IA64_DCR_BE	(__IA64_UL(1) << IA64_DCR_BE_BIT)
#घोषणा IA64_DCR_LC	(__IA64_UL(1) << IA64_DCR_LC_BIT)
#घोषणा IA64_DCR_DM	(__IA64_UL(1) << IA64_DCR_DM_BIT)
#घोषणा IA64_DCR_DP	(__IA64_UL(1) << IA64_DCR_DP_BIT)
#घोषणा IA64_DCR_DK	(__IA64_UL(1) << IA64_DCR_DK_BIT)
#घोषणा IA64_DCR_DX	(__IA64_UL(1) << IA64_DCR_DX_BIT)
#घोषणा IA64_DCR_DR	(__IA64_UL(1) << IA64_DCR_DR_BIT)
#घोषणा IA64_DCR_DA	(__IA64_UL(1) << IA64_DCR_DA_BIT)
#घोषणा IA64_DCR_DD	(__IA64_UL(1) << IA64_DCR_DD_BIT)

/* Interrupt Status Register */
#घोषणा IA64_ISR_X_BIT		32	/* execute access */
#घोषणा IA64_ISR_W_BIT		33	/* ग_लिखो access */
#घोषणा IA64_ISR_R_BIT		34	/* पढ़ो access */
#घोषणा IA64_ISR_NA_BIT		35	/* non-access */
#घोषणा IA64_ISR_SP_BIT		36	/* speculative load exception */
#घोषणा IA64_ISR_RS_BIT		37	/* mandatory रेजिस्टर-stack exception */
#घोषणा IA64_ISR_IR_BIT		38	/* invalid रेजिस्टर frame exception */
#घोषणा IA64_ISR_CODE_MASK	0xf

#घोषणा IA64_ISR_X	(__IA64_UL(1) << IA64_ISR_X_BIT)
#घोषणा IA64_ISR_W	(__IA64_UL(1) << IA64_ISR_W_BIT)
#घोषणा IA64_ISR_R	(__IA64_UL(1) << IA64_ISR_R_BIT)
#घोषणा IA64_ISR_NA	(__IA64_UL(1) << IA64_ISR_NA_BIT)
#घोषणा IA64_ISR_SP	(__IA64_UL(1) << IA64_ISR_SP_BIT)
#घोषणा IA64_ISR_RS	(__IA64_UL(1) << IA64_ISR_RS_BIT)
#घोषणा IA64_ISR_IR	(__IA64_UL(1) << IA64_ISR_IR_BIT)

/* ISR code field क्रम non-access inकाष्ठाions */
#घोषणा IA64_ISR_CODE_TPA	0
#घोषणा IA64_ISR_CODE_FC	1
#घोषणा IA64_ISR_CODE_PROBE	2
#घोषणा IA64_ISR_CODE_TAK	3
#घोषणा IA64_ISR_CODE_LFETCH	4
#घोषणा IA64_ISR_CODE_PROBEF	5

#पूर्ण_अगर /* _ASM_IA64_kREGS_H */
