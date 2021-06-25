<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012,2013 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#अगर_अघोषित __ARM64_KVM_ARM_H__
#घोषणा __ARM64_KVM_ARM_H__

#समावेश <यंत्र/esr.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/types.h>

/* Hyp Configuration Register (HCR) bits */
#घोषणा HCR_ATA		(UL(1) << 56)
#घोषणा HCR_FWB		(UL(1) << 46)
#घोषणा HCR_API		(UL(1) << 41)
#घोषणा HCR_APK		(UL(1) << 40)
#घोषणा HCR_TEA		(UL(1) << 37)
#घोषणा HCR_TERR	(UL(1) << 36)
#घोषणा HCR_TLOR	(UL(1) << 35)
#घोषणा HCR_E2H		(UL(1) << 34)
#घोषणा HCR_ID		(UL(1) << 33)
#घोषणा HCR_CD		(UL(1) << 32)
#घोषणा HCR_RW_SHIFT	31
#घोषणा HCR_RW		(UL(1) << HCR_RW_SHIFT)
#घोषणा HCR_TRVM	(UL(1) << 30)
#घोषणा HCR_HCD		(UL(1) << 29)
#घोषणा HCR_TDZ		(UL(1) << 28)
#घोषणा HCR_TGE		(UL(1) << 27)
#घोषणा HCR_TVM		(UL(1) << 26)
#घोषणा HCR_TTLB	(UL(1) << 25)
#घोषणा HCR_TPU		(UL(1) << 24)
#घोषणा HCR_TPC		(UL(1) << 23)
#घोषणा HCR_TSW		(UL(1) << 22)
#घोषणा HCR_TAC		(UL(1) << 21)
#घोषणा HCR_TIDCP	(UL(1) << 20)
#घोषणा HCR_TSC		(UL(1) << 19)
#घोषणा HCR_TID3	(UL(1) << 18)
#घोषणा HCR_TID2	(UL(1) << 17)
#घोषणा HCR_TID1	(UL(1) << 16)
#घोषणा HCR_TID0	(UL(1) << 15)
#घोषणा HCR_TWE		(UL(1) << 14)
#घोषणा HCR_TWI		(UL(1) << 13)
#घोषणा HCR_DC		(UL(1) << 12)
#घोषणा HCR_BSU		(3 << 10)
#घोषणा HCR_BSU_IS	(UL(1) << 10)
#घोषणा HCR_FB		(UL(1) << 9)
#घोषणा HCR_VSE		(UL(1) << 8)
#घोषणा HCR_VI		(UL(1) << 7)
#घोषणा HCR_VF		(UL(1) << 6)
#घोषणा HCR_AMO		(UL(1) << 5)
#घोषणा HCR_IMO		(UL(1) << 4)
#घोषणा HCR_FMO		(UL(1) << 3)
#घोषणा HCR_PTW		(UL(1) << 2)
#घोषणा HCR_SWIO	(UL(1) << 1)
#घोषणा HCR_VM		(UL(1) << 0)

/*
 * The bits we set in HCR:
 * TLOR:	Trap LORegion रेजिस्टर accesses
 * RW:		64bit by शेष, can be overridden क्रम 32bit VMs
 * TAC:		Trap ACTLR
 * TSC:		Trap SMC
 * TSW:		Trap cache operations by set/way
 * TWE:		Trap WFE
 * TWI:		Trap WFI
 * TIDCP:	Trap L2CTLR/L2ECTLR
 * BSU_IS:	Upgrade barriers to the inner shareable करोमुख्य
 * FB:		Force broadcast of all मुख्यtenance operations
 * AMO:		Override CPSR.A and enable संकेतing with VA
 * IMO:		Override CPSR.I and enable संकेतing with VI
 * FMO:		Override CPSR.F and enable संकेतing with VF
 * SWIO:	Turn set/way invalidates पूर्णांकo set/way clean+invalidate
 * PTW:		Take a stage2 fault अगर a stage1 walk steps in device memory
 */
#घोषणा HCR_GUEST_FLAGS (HCR_TSC | HCR_TSW | HCR_TWE | HCR_TWI | HCR_VM | \
			 HCR_BSU_IS | HCR_FB | HCR_TAC | \
			 HCR_AMO | HCR_SWIO | HCR_TIDCP | HCR_RW | HCR_TLOR | \
			 HCR_FMO | HCR_IMO | HCR_PTW )
#घोषणा HCR_VIRT_EXCP_MASK (HCR_VSE | HCR_VI | HCR_VF)
#घोषणा HCR_HOST_NVHE_FLAGS (HCR_RW | HCR_API | HCR_APK | HCR_ATA)
#घोषणा HCR_HOST_NVHE_PROTECTED_FLAGS (HCR_HOST_NVHE_FLAGS | HCR_TSC)
#घोषणा HCR_HOST_VHE_FLAGS (HCR_RW | HCR_TGE | HCR_E2H)

/* TCR_EL2 Registers bits */
#घोषणा TCR_EL2_RES1		((1 << 31) | (1 << 23))
#घोषणा TCR_EL2_TBI		(1 << 20)
#घोषणा TCR_EL2_PS_SHIFT	16
#घोषणा TCR_EL2_PS_MASK		(7 << TCR_EL2_PS_SHIFT)
#घोषणा TCR_EL2_PS_40B		(2 << TCR_EL2_PS_SHIFT)
#घोषणा TCR_EL2_TG0_MASK	TCR_TG0_MASK
#घोषणा TCR_EL2_SH0_MASK	TCR_SH0_MASK
#घोषणा TCR_EL2_ORGN0_MASK	TCR_ORGN0_MASK
#घोषणा TCR_EL2_IRGN0_MASK	TCR_IRGN0_MASK
#घोषणा TCR_EL2_T0SZ_MASK	0x3f
#घोषणा TCR_EL2_MASK	(TCR_EL2_TG0_MASK | TCR_EL2_SH0_MASK | \
			 TCR_EL2_ORGN0_MASK | TCR_EL2_IRGN0_MASK | TCR_EL2_T0SZ_MASK)

/* VTCR_EL2 Registers bits */
#घोषणा VTCR_EL2_RES1		(1U << 31)
#घोषणा VTCR_EL2_HD		(1 << 22)
#घोषणा VTCR_EL2_HA		(1 << 21)
#घोषणा VTCR_EL2_PS_SHIFT	TCR_EL2_PS_SHIFT
#घोषणा VTCR_EL2_PS_MASK	TCR_EL2_PS_MASK
#घोषणा VTCR_EL2_TG0_MASK	TCR_TG0_MASK
#घोषणा VTCR_EL2_TG0_4K		TCR_TG0_4K
#घोषणा VTCR_EL2_TG0_16K	TCR_TG0_16K
#घोषणा VTCR_EL2_TG0_64K	TCR_TG0_64K
#घोषणा VTCR_EL2_SH0_MASK	TCR_SH0_MASK
#घोषणा VTCR_EL2_SH0_INNER	TCR_SH0_INNER
#घोषणा VTCR_EL2_ORGN0_MASK	TCR_ORGN0_MASK
#घोषणा VTCR_EL2_ORGN0_WBWA	TCR_ORGN0_WBWA
#घोषणा VTCR_EL2_IRGN0_MASK	TCR_IRGN0_MASK
#घोषणा VTCR_EL2_IRGN0_WBWA	TCR_IRGN0_WBWA
#घोषणा VTCR_EL2_SL0_SHIFT	6
#घोषणा VTCR_EL2_SL0_MASK	(3 << VTCR_EL2_SL0_SHIFT)
#घोषणा VTCR_EL2_T0SZ_MASK	0x3f
#घोषणा VTCR_EL2_VS_SHIFT	19
#घोषणा VTCR_EL2_VS_8BIT	(0 << VTCR_EL2_VS_SHIFT)
#घोषणा VTCR_EL2_VS_16BIT	(1 << VTCR_EL2_VS_SHIFT)

#घोषणा VTCR_EL2_T0SZ(x)	TCR_T0SZ(x)

/*
 * We configure the Stage-2 page tables to always restrict the IPA space to be
 * 40 bits wide (T0SZ = 24).  Systems with a PARange smaller than 40 bits are
 * not known to exist and will अवरोध with this configuration.
 *
 * The VTCR_EL2 is configured per VM and is initialised in kvm_arm_setup_stage2().
 *
 * Note that when using 4K pages, we concatenate two first level page tables
 * together. With 16K pages, we concatenate 16 first level page tables.
 *
 */

#घोषणा VTCR_EL2_COMMON_BITS	(VTCR_EL2_SH0_INNER | VTCR_EL2_ORGN0_WBWA | \
				 VTCR_EL2_IRGN0_WBWA | VTCR_EL2_RES1)

/*
 * VTCR_EL2:SL0 indicates the entry level क्रम Stage2 translation.
 * Interestingly, it depends on the page size.
 * See D.10.2.121, VTCR_EL2, in ARM DDI 0487C.a
 *
 *	-----------------------------------------
 *	| Entry level		|  4K  | 16K/64K |
 *	------------------------------------------
 *	| Level: 0		|  2   |   -     |
 *	------------------------------------------
 *	| Level: 1		|  1   |   2     |
 *	------------------------------------------
 *	| Level: 2		|  0   |   1     |
 *	------------------------------------------
 *	| Level: 3		|  -   |   0     |
 *	------------------------------------------
 *
 * The table roughly translates to :
 *
 *	SL0(PAGE_SIZE, Entry_level) = TGRAN_SL0_BASE - Entry_Level
 *
 * Where TGRAN_SL0_BASE is a magic number depending on the page size:
 * 	TGRAN_SL0_BASE(4K) = 2
 *	TGRAN_SL0_BASE(16K) = 3
 *	TGRAN_SL0_BASE(64K) = 3
 * provided we take care of ruling out the unsupported हालs and
 * Entry_Level = 4 - Number_of_levels.
 *
 */
#अगर_घोषित CONFIG_ARM64_64K_PAGES

#घोषणा VTCR_EL2_TGRAN			VTCR_EL2_TG0_64K
#घोषणा VTCR_EL2_TGRAN_SL0_BASE		3UL

#या_अगर defined(CONFIG_ARM64_16K_PAGES)

#घोषणा VTCR_EL2_TGRAN			VTCR_EL2_TG0_16K
#घोषणा VTCR_EL2_TGRAN_SL0_BASE		3UL

#अन्यथा	/* 4K */

#घोषणा VTCR_EL2_TGRAN			VTCR_EL2_TG0_4K
#घोषणा VTCR_EL2_TGRAN_SL0_BASE		2UL

#पूर्ण_अगर

#घोषणा VTCR_EL2_LVLS_TO_SL0(levels)	\
	((VTCR_EL2_TGRAN_SL0_BASE - (4 - (levels))) << VTCR_EL2_SL0_SHIFT)
#घोषणा VTCR_EL2_SL0_TO_LVLS(sl0)	\
	((sl0) + 4 - VTCR_EL2_TGRAN_SL0_BASE)
#घोषणा VTCR_EL2_LVLS(vtcr)		\
	VTCR_EL2_SL0_TO_LVLS(((vtcr) & VTCR_EL2_SL0_MASK) >> VTCR_EL2_SL0_SHIFT)

#घोषणा VTCR_EL2_FLAGS			(VTCR_EL2_COMMON_BITS | VTCR_EL2_TGRAN)
#घोषणा VTCR_EL2_IPA(vtcr)		(64 - ((vtcr) & VTCR_EL2_T0SZ_MASK))

/*
 * ARM VMSAv8-64 defines an algorithm क्रम finding the translation table
 * descriptors in section D4.2.8 in ARM DDI 0487C.a.
 *
 * The algorithm defines the expectations on the translation table
 * addresses क्रम each level, based on PAGE_SIZE, entry level
 * and the translation table size (T0SZ). The variable "x" in the
 * algorithm determines the alignment of a table base address at a given
 * level and thus determines the alignment of VTTBR:BADDR क्रम stage2
 * page table entry level.
 * Since the number of bits resolved at the entry level could vary
 * depending on the T0SZ, the value of "x" is defined based on a
 * Magic स्थिरant क्रम a given PAGE_SIZE and Entry Level. The
 * पूर्णांकermediate levels must be always aligned to the PAGE_SIZE (i.e,
 * x = PAGE_SHIFT).
 *
 * The value of "x" क्रम entry level is calculated as :
 *    x = Magic_N - T0SZ
 *
 * where Magic_N is an पूर्णांकeger depending on the page size and the entry
 * level of the page table as below:
 *
 *	--------------------------------------------
 *	| Entry level		|  4K    16K   64K |
 *	--------------------------------------------
 *	| Level: 0 (4 levels)	| 28   |  -  |  -  |
 *	--------------------------------------------
 *	| Level: 1 (3 levels)	| 37   | 31  | 25  |
 *	--------------------------------------------
 *	| Level: 2 (2 levels)	| 46   | 42  | 38  |
 *	--------------------------------------------
 *	| Level: 3 (1 level)	| -    | 53  | 51  |
 *	--------------------------------------------
 *
 * We have a magic क्रमmula क्रम the Magic_N below:
 *
 *  Magic_N(PAGE_SIZE, Level) = 64 - ((PAGE_SHIFT - 3) * Number_of_levels)
 *
 * where Number_of_levels = (4 - Level). We are only पूर्णांकerested in the
 * value क्रम Entry_Level क्रम the stage2 page table.
 *
 * So, given that T0SZ = (64 - IPA_SHIFT), we can compute 'x' as follows:
 *
 *	x = (64 - ((PAGE_SHIFT - 3) * Number_of_levels)) - (64 - IPA_SHIFT)
 *	  = IPA_SHIFT - ((PAGE_SHIFT - 3) * Number of levels)
 *
 * Here is one way to explain the Magic Formula:
 *
 *  x = log2(Size_of_Entry_Level_Table)
 *
 * Since, we can resolve (PAGE_SHIFT - 3) bits at each level, and another
 * PAGE_SHIFT bits in the PTE, we have :
 *
 *  Bits_Entry_level = IPA_SHIFT - ((PAGE_SHIFT - 3) * (n - 1) + PAGE_SHIFT)
 *		     = IPA_SHIFT - (PAGE_SHIFT - 3) * n - 3
 *  where n = number of levels, and since each poपूर्णांकer is 8bytes, we have:
 *
 *  x = Bits_Entry_Level + 3
 *    = IPA_SHIFT - (PAGE_SHIFT - 3) * n
 *
 * The only स्थिरraपूर्णांक here is that, we have to find the number of page table
 * levels क्रम a given IPA size (which we करो, see stage2_pt_levels())
 */
#घोषणा ARM64_VTTBR_X(ipa, levels)	((ipa) - ((levels) * (PAGE_SHIFT - 3)))

#घोषणा VTTBR_CNP_BIT     (UL(1))
#घोषणा VTTBR_VMID_SHIFT  (UL(48))
#घोषणा VTTBR_VMID_MASK(size) (_AT(u64, (1 << size) - 1) << VTTBR_VMID_SHIFT)

/* Hyp System Trap Register */
#घोषणा HSTR_EL2_T(x)	(1 << x)

/* Hyp Coprocessor Trap Register Shअगरts */
#घोषणा CPTR_EL2_TFP_SHIFT 10

/* Hyp Coprocessor Trap Register */
#घोषणा CPTR_EL2_TCPAC	(1 << 31)
#घोषणा CPTR_EL2_TAM	(1 << 30)
#घोषणा CPTR_EL2_TTA	(1 << 20)
#घोषणा CPTR_EL2_TFP	(1 << CPTR_EL2_TFP_SHIFT)
#घोषणा CPTR_EL2_TZ	(1 << 8)
#घोषणा CPTR_EL2_RES1	0x000032ff /* known RES1 bits in CPTR_EL2 */
#घोषणा CPTR_EL2_DEFAULT	CPTR_EL2_RES1

/* Hyp Debug Configuration Register bits */
#घोषणा MDCR_EL2_E2TB_MASK	(UL(0x3))
#घोषणा MDCR_EL2_E2TB_SHIFT	(UL(24))
#घोषणा MDCR_EL2_TTRF		(1 << 19)
#घोषणा MDCR_EL2_TPMS		(1 << 14)
#घोषणा MDCR_EL2_E2PB_MASK	(UL(0x3))
#घोषणा MDCR_EL2_E2PB_SHIFT	(UL(12))
#घोषणा MDCR_EL2_TDRA		(1 << 11)
#घोषणा MDCR_EL2_TDOSA		(1 << 10)
#घोषणा MDCR_EL2_TDA		(1 << 9)
#घोषणा MDCR_EL2_TDE		(1 << 8)
#घोषणा MDCR_EL2_HPME		(1 << 7)
#घोषणा MDCR_EL2_TPM		(1 << 6)
#घोषणा MDCR_EL2_TPMCR		(1 << 5)
#घोषणा MDCR_EL2_HPMN_MASK	(0x1F)

/* For compatibility with fault code shared with 32-bit */
#घोषणा FSC_FAULT	ESR_ELx_FSC_FAULT
#घोषणा FSC_ACCESS	ESR_ELx_FSC_ACCESS
#घोषणा FSC_PERM	ESR_ELx_FSC_PERM
#घोषणा FSC_SEA		ESR_ELx_FSC_EXTABT
#घोषणा FSC_SEA_TTW0	(0x14)
#घोषणा FSC_SEA_TTW1	(0x15)
#घोषणा FSC_SEA_TTW2	(0x16)
#घोषणा FSC_SEA_TTW3	(0x17)
#घोषणा FSC_SECC	(0x18)
#घोषणा FSC_SECC_TTW0	(0x1c)
#घोषणा FSC_SECC_TTW1	(0x1d)
#घोषणा FSC_SECC_TTW2	(0x1e)
#घोषणा FSC_SECC_TTW3	(0x1f)

/* Hyp Prefetch Fault Address Register (HPFAR/HDFAR) */
#घोषणा HPFAR_MASK	(~UL(0xf))
/*
 * We have
 *	PAR	[PA_Shअगरt - 1	: 12] = PA	[PA_Shअगरt - 1 : 12]
 *	HPFAR	[PA_Shअगरt - 9	: 4]  = FIPA	[PA_Shअगरt - 1 : 12]
 */
#घोषणा PAR_TO_HPFAR(par)		\
	(((par) & GENMASK_ULL(PHYS_MASK_SHIFT - 1, 12)) >> 8)

#घोषणा ECN(x) अणु ESR_ELx_EC_##x, #x पूर्ण

#घोषणा kvm_arm_exception_class \
	ECN(UNKNOWN), ECN(WFx), ECN(CP15_32), ECN(CP15_64), ECN(CP14_MR), \
	ECN(CP14_LS), ECN(FP_ASIMD), ECN(CP10_ID), ECN(PAC), ECN(CP14_64), \
	ECN(SVC64), ECN(HVC64), ECN(SMC64), ECN(SYS64), ECN(SVE), \
	ECN(IMP_DEF), ECN(IABT_LOW), ECN(IABT_CUR), \
	ECN(PC_ALIGN), ECN(DABT_LOW), ECN(DABT_CUR), \
	ECN(SP_ALIGN), ECN(FP_EXC32), ECN(FP_EXC64), ECN(SERROR), \
	ECN(BREAKPT_LOW), ECN(BREAKPT_CUR), ECN(SOFTSTP_LOW), \
	ECN(SOFTSTP_CUR), ECN(WATCHPT_LOW), ECN(WATCHPT_CUR), \
	ECN(BKPT32), ECN(VECTOR32), ECN(BRK64)

#घोषणा CPACR_EL1_FPEN		(3 << 20)
#घोषणा CPACR_EL1_TTA		(1 << 28)
#घोषणा CPACR_EL1_DEFAULT	(CPACR_EL1_FPEN | CPACR_EL1_ZEN_EL1EN)

#पूर्ण_अगर /* __ARM64_KVM_ARM_H__ */
