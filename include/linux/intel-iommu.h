<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright तऊ 2006-2015, Intel Corporation.
 *
 * Authors: Ashok Raj <ashok.raj@पूर्णांकel.com>
 *          Anil S Keshavamurthy <anil.s.keshavamurthy@पूर्णांकel.com>
 *          David Woodhouse <David.Woodhouse@पूर्णांकel.com>
 */

#अगर_अघोषित _INTEL_IOMMU_H_
#घोषणा _INTEL_IOMMU_H_

#समावेश <linux/types.h>
#समावेश <linux/iova.h>
#समावेश <linux/पन.स>
#समावेश <linux/idr.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/list.h>
#समावेश <linux/iommu.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/dmar.h>
#समावेश <linux/ioasid.h>
#समावेश <linux/bitfield.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/iommu.h>

/*
 * VT-d hardware uses 4KiB page size regardless of host page size.
 */
#घोषणा VTD_PAGE_SHIFT		(12)
#घोषणा VTD_PAGE_SIZE		(1UL << VTD_PAGE_SHIFT)
#घोषणा VTD_PAGE_MASK		(((u64)-1) << VTD_PAGE_SHIFT)
#घोषणा VTD_PAGE_ALIGN(addr)	(((addr) + VTD_PAGE_SIZE - 1) & VTD_PAGE_MASK)

#घोषणा VTD_STRIDE_SHIFT        (9)
#घोषणा VTD_STRIDE_MASK         (((u64)-1) << VTD_STRIDE_SHIFT)

#घोषणा DMA_PTE_READ		BIT_ULL(0)
#घोषणा DMA_PTE_WRITE		BIT_ULL(1)
#घोषणा DMA_PTE_LARGE_PAGE	BIT_ULL(7)
#घोषणा DMA_PTE_SNP		BIT_ULL(11)

#घोषणा DMA_FL_PTE_PRESENT	BIT_ULL(0)
#घोषणा DMA_FL_PTE_US		BIT_ULL(2)
#घोषणा DMA_FL_PTE_ACCESS	BIT_ULL(5)
#घोषणा DMA_FL_PTE_सूचीTY	BIT_ULL(6)
#घोषणा DMA_FL_PTE_XD		BIT_ULL(63)

#घोषणा ADDR_WIDTH_5LEVEL	(57)
#घोषणा ADDR_WIDTH_4LEVEL	(48)

#घोषणा CONTEXT_TT_MULTI_LEVEL	0
#घोषणा CONTEXT_TT_DEV_IOTLB	1
#घोषणा CONTEXT_TT_PASS_THROUGH 2
#घोषणा CONTEXT_PASIDE		BIT_ULL(3)

/*
 * Intel IOMMU रेजिस्टर specअगरication per version 1.0 खुला spec.
 */
#घोषणा	DMAR_VER_REG	0x0	/* Arch version supported by this IOMMU */
#घोषणा	DMAR_CAP_REG	0x8	/* Hardware supported capabilities */
#घोषणा	DMAR_ECAP_REG	0x10	/* Extended capabilities supported */
#घोषणा	DMAR_GCMD_REG	0x18	/* Global command रेजिस्टर */
#घोषणा	DMAR_GSTS_REG	0x1c	/* Global status रेजिस्टर */
#घोषणा	DMAR_RTADDR_REG	0x20	/* Root entry table */
#घोषणा	DMAR_CCMD_REG	0x28	/* Context command reg */
#घोषणा	DMAR_FSTS_REG	0x34	/* Fault Status रेजिस्टर */
#घोषणा	DMAR_FECTL_REG	0x38	/* Fault control रेजिस्टर */
#घोषणा	DMAR_FEDATA_REG	0x3c	/* Fault event पूर्णांकerrupt data रेजिस्टर */
#घोषणा	DMAR_FEADDR_REG	0x40	/* Fault event पूर्णांकerrupt addr रेजिस्टर */
#घोषणा	DMAR_FEUADDR_REG 0x44	/* Upper address रेजिस्टर */
#घोषणा	DMAR_AFLOG_REG	0x58	/* Advanced Fault control */
#घोषणा	DMAR_PMEN_REG	0x64	/* Enable Protected Memory Region */
#घोषणा	DMAR_PLMBASE_REG 0x68	/* PMRR Low addr */
#घोषणा	DMAR_PLMLIMIT_REG 0x6c	/* PMRR low limit */
#घोषणा	DMAR_PHMBASE_REG 0x70	/* pmrr high base addr */
#घोषणा	DMAR_PHMLIMIT_REG 0x78	/* pmrr high limit */
#घोषणा DMAR_IQH_REG	0x80	/* Invalidation queue head रेजिस्टर */
#घोषणा DMAR_IQT_REG	0x88	/* Invalidation queue tail रेजिस्टर */
#घोषणा DMAR_IQ_SHIFT	4	/* Invalidation queue head/tail shअगरt */
#घोषणा DMAR_IQA_REG	0x90	/* Invalidation queue addr रेजिस्टर */
#घोषणा DMAR_ICS_REG	0x9c	/* Invalidation complete status रेजिस्टर */
#घोषणा DMAR_IQER_REG	0xb0	/* Invalidation queue error record रेजिस्टर */
#घोषणा DMAR_IRTA_REG	0xb8    /* Interrupt remapping table addr रेजिस्टर */
#घोषणा DMAR_PQH_REG	0xc0	/* Page request queue head रेजिस्टर */
#घोषणा DMAR_PQT_REG	0xc8	/* Page request queue tail रेजिस्टर */
#घोषणा DMAR_PQA_REG	0xd0	/* Page request queue address रेजिस्टर */
#घोषणा DMAR_PRS_REG	0xdc	/* Page request status रेजिस्टर */
#घोषणा DMAR_PECTL_REG	0xe0	/* Page request event control रेजिस्टर */
#घोषणा	DMAR_PEDATA_REG	0xe4	/* Page request event पूर्णांकerrupt data रेजिस्टर */
#घोषणा	DMAR_PEADDR_REG	0xe8	/* Page request event पूर्णांकerrupt addr रेजिस्टर */
#घोषणा	DMAR_PEUADDR_REG 0xec	/* Page request event Upper address रेजिस्टर */
#घोषणा DMAR_MTRRCAP_REG 0x100	/* MTRR capability रेजिस्टर */
#घोषणा DMAR_MTRRDEF_REG 0x108	/* MTRR शेष type रेजिस्टर */
#घोषणा DMAR_MTRR_FIX64K_00000_REG 0x120 /* MTRR Fixed range रेजिस्टरs */
#घोषणा DMAR_MTRR_FIX16K_80000_REG 0x128
#घोषणा DMAR_MTRR_FIX16K_A0000_REG 0x130
#घोषणा DMAR_MTRR_FIX4K_C0000_REG 0x138
#घोषणा DMAR_MTRR_FIX4K_C8000_REG 0x140
#घोषणा DMAR_MTRR_FIX4K_D0000_REG 0x148
#घोषणा DMAR_MTRR_FIX4K_D8000_REG 0x150
#घोषणा DMAR_MTRR_FIX4K_E0000_REG 0x158
#घोषणा DMAR_MTRR_FIX4K_E8000_REG 0x160
#घोषणा DMAR_MTRR_FIX4K_F0000_REG 0x168
#घोषणा DMAR_MTRR_FIX4K_F8000_REG 0x170
#घोषणा DMAR_MTRR_PHYSBASE0_REG 0x180 /* MTRR Variable range रेजिस्टरs */
#घोषणा DMAR_MTRR_PHYSMASK0_REG 0x188
#घोषणा DMAR_MTRR_PHYSBASE1_REG 0x190
#घोषणा DMAR_MTRR_PHYSMASK1_REG 0x198
#घोषणा DMAR_MTRR_PHYSBASE2_REG 0x1a0
#घोषणा DMAR_MTRR_PHYSMASK2_REG 0x1a8
#घोषणा DMAR_MTRR_PHYSBASE3_REG 0x1b0
#घोषणा DMAR_MTRR_PHYSMASK3_REG 0x1b8
#घोषणा DMAR_MTRR_PHYSBASE4_REG 0x1c0
#घोषणा DMAR_MTRR_PHYSMASK4_REG 0x1c8
#घोषणा DMAR_MTRR_PHYSBASE5_REG 0x1d0
#घोषणा DMAR_MTRR_PHYSMASK5_REG 0x1d8
#घोषणा DMAR_MTRR_PHYSBASE6_REG 0x1e0
#घोषणा DMAR_MTRR_PHYSMASK6_REG 0x1e8
#घोषणा DMAR_MTRR_PHYSBASE7_REG 0x1f0
#घोषणा DMAR_MTRR_PHYSMASK7_REG 0x1f8
#घोषणा DMAR_MTRR_PHYSBASE8_REG 0x200
#घोषणा DMAR_MTRR_PHYSMASK8_REG 0x208
#घोषणा DMAR_MTRR_PHYSBASE9_REG 0x210
#घोषणा DMAR_MTRR_PHYSMASK9_REG 0x218
#घोषणा DMAR_VCCAP_REG		0xe00 /* Virtual command capability रेजिस्टर */
#घोषणा DMAR_VCMD_REG		0xe10 /* Virtual command रेजिस्टर */
#घोषणा DMAR_VCRSP_REG		0xe20 /* Virtual command response रेजिस्टर */

#घोषणा DMAR_IQER_REG_IQEI(reg)		FIELD_GET(GENMASK_ULL(3, 0), reg)
#घोषणा DMAR_IQER_REG_ITESID(reg)	FIELD_GET(GENMASK_ULL(47, 32), reg)
#घोषणा DMAR_IQER_REG_ICESID(reg)	FIELD_GET(GENMASK_ULL(63, 48), reg)

#घोषणा OFFSET_STRIDE		(9)

#घोषणा dmar_पढ़ोq(a) पढ़ोq(a)
#घोषणा dmar_ग_लिखोq(a,v) ग_लिखोq(v,a)
#घोषणा dmar_पढ़ोl(a) पढ़ोl(a)
#घोषणा dmar_ग_लिखोl(a, v) ग_लिखोl(v, a)

#घोषणा DMAR_VER_MAJOR(v)		(((v) & 0xf0) >> 4)
#घोषणा DMAR_VER_MINOR(v)		((v) & 0x0f)

/*
 * Decoding Capability Register
 */
#घोषणा cap_5lp_support(c)	(((c) >> 60) & 1)
#घोषणा cap_pi_support(c)	(((c) >> 59) & 1)
#घोषणा cap_fl1gp_support(c)	(((c) >> 56) & 1)
#घोषणा cap_पढ़ो_drain(c)	(((c) >> 55) & 1)
#घोषणा cap_ग_लिखो_drain(c)	(((c) >> 54) & 1)
#घोषणा cap_max_amask_val(c)	(((c) >> 48) & 0x3f)
#घोषणा cap_num_fault_regs(c)	((((c) >> 40) & 0xff) + 1)
#घोषणा cap_pgsel_inv(c)	(((c) >> 39) & 1)

#घोषणा cap_super_page_val(c)	(((c) >> 34) & 0xf)
#घोषणा cap_super_offset(c)	(((find_first_bit(&cap_super_page_val(c), 4)) \
					* OFFSET_STRIDE) + 21)

#घोषणा cap_fault_reg_offset(c)	((((c) >> 24) & 0x3ff) * 16)
#घोषणा cap_max_fault_reg_offset(c) \
	(cap_fault_reg_offset(c) + cap_num_fault_regs(c) * 16)

#घोषणा cap_zlr(c)		(((c) >> 22) & 1)
#घोषणा cap_isoch(c)		(((c) >> 23) & 1)
#घोषणा cap_mgaw(c)		((((c) >> 16) & 0x3f) + 1)
#घोषणा cap_sagaw(c)		(((c) >> 8) & 0x1f)
#घोषणा cap_caching_mode(c)	(((c) >> 7) & 1)
#घोषणा cap_phmr(c)		(((c) >> 6) & 1)
#घोषणा cap_plmr(c)		(((c) >> 5) & 1)
#घोषणा cap_rwbf(c)		(((c) >> 4) & 1)
#घोषणा cap_afl(c)		(((c) >> 3) & 1)
#घोषणा cap_nकरोms(c)		(((अचिन्हित दीर्घ)1) << (4 + 2 * ((c) & 0x7)))
/*
 * Extended Capability Register
 */

#घोषणा	ecap_rps(e)		(((e) >> 49) & 0x1)
#घोषणा ecap_smpwc(e)		(((e) >> 48) & 0x1)
#घोषणा ecap_flts(e)		(((e) >> 47) & 0x1)
#घोषणा ecap_slts(e)		(((e) >> 46) & 0x1)
#घोषणा ecap_slads(e)		(((e) >> 45) & 0x1)
#घोषणा ecap_vcs(e)		(((e) >> 44) & 0x1)
#घोषणा ecap_smts(e)		(((e) >> 43) & 0x1)
#घोषणा ecap_dit(e)		(((e) >> 41) & 0x1)
#घोषणा ecap_pds(e)		(((e) >> 42) & 0x1)
#घोषणा ecap_pasid(e)		(((e) >> 40) & 0x1)
#घोषणा ecap_pss(e)		(((e) >> 35) & 0x1f)
#घोषणा ecap_eafs(e)		(((e) >> 34) & 0x1)
#घोषणा ecap_nwfs(e)		(((e) >> 33) & 0x1)
#घोषणा ecap_srs(e)		(((e) >> 31) & 0x1)
#घोषणा ecap_ers(e)		(((e) >> 30) & 0x1)
#घोषणा ecap_prs(e)		(((e) >> 29) & 0x1)
#घोषणा ecap_broken_pasid(e)	(((e) >> 28) & 0x1)
#घोषणा ecap_dis(e)		(((e) >> 27) & 0x1)
#घोषणा ecap_nest(e)		(((e) >> 26) & 0x1)
#घोषणा ecap_mts(e)		(((e) >> 25) & 0x1)
#घोषणा ecap_ecs(e)		(((e) >> 24) & 0x1)
#घोषणा ecap_iotlb_offset(e) 	((((e) >> 8) & 0x3ff) * 16)
#घोषणा ecap_max_iotlb_offset(e) (ecap_iotlb_offset(e) + 16)
#घोषणा ecap_coherent(e)	((e) & 0x1)
#घोषणा ecap_qis(e)		((e) & 0x2)
#घोषणा ecap_pass_through(e)	(((e) >> 6) & 0x1)
#घोषणा ecap_eim_support(e)	(((e) >> 4) & 0x1)
#घोषणा ecap_ir_support(e)	(((e) >> 3) & 0x1)
#घोषणा ecap_dev_iotlb_support(e)	(((e) >> 2) & 0x1)
#घोषणा ecap_max_handle_mask(e) (((e) >> 20) & 0xf)
#घोषणा ecap_sc_support(e)	(((e) >> 7) & 0x1) /* Snooping Control */

/* Virtual command पूर्णांकerface capability */
#घोषणा vccap_pasid(v)		(((v) & DMA_VCS_PAS)) /* PASID allocation */

/* IOTLB_REG */
#घोषणा DMA_TLB_FLUSH_GRANU_OFFSET  60
#घोषणा DMA_TLB_GLOBAL_FLUSH (((u64)1) << 60)
#घोषणा DMA_TLB_DSI_FLUSH (((u64)2) << 60)
#घोषणा DMA_TLB_PSI_FLUSH (((u64)3) << 60)
#घोषणा DMA_TLB_IIRG(type) ((type >> 60) & 3)
#घोषणा DMA_TLB_IAIG(val) (((val) >> 57) & 3)
#घोषणा DMA_TLB_READ_DRAIN (((u64)1) << 49)
#घोषणा DMA_TLB_WRITE_DRAIN (((u64)1) << 48)
#घोषणा DMA_TLB_DID(id)	(((u64)((id) & 0xffff)) << 32)
#घोषणा DMA_TLB_IVT (((u64)1) << 63)
#घोषणा DMA_TLB_IH_NONLEAF (((u64)1) << 6)
#घोषणा DMA_TLB_MAX_SIZE (0x3f)

/* INVALID_DESC */
#घोषणा DMA_CCMD_INVL_GRANU_OFFSET  61
#घोषणा DMA_ID_TLB_GLOBAL_FLUSH	(((u64)1) << 4)
#घोषणा DMA_ID_TLB_DSI_FLUSH	(((u64)2) << 4)
#घोषणा DMA_ID_TLB_PSI_FLUSH	(((u64)3) << 4)
#घोषणा DMA_ID_TLB_READ_DRAIN	(((u64)1) << 7)
#घोषणा DMA_ID_TLB_WRITE_DRAIN	(((u64)1) << 6)
#घोषणा DMA_ID_TLB_DID(id)	(((u64)((id & 0xffff) << 16)))
#घोषणा DMA_ID_TLB_IH_NONLEAF	(((u64)1) << 6)
#घोषणा DMA_ID_TLB_ADDR(addr)	(addr)
#घोषणा DMA_ID_TLB_ADDR_MASK(mask)	(mask)

/* PMEN_REG */
#घोषणा DMA_PMEN_EPM (((u32)1)<<31)
#घोषणा DMA_PMEN_PRS (((u32)1)<<0)

/* GCMD_REG */
#घोषणा DMA_GCMD_TE (((u32)1) << 31)
#घोषणा DMA_GCMD_SRTP (((u32)1) << 30)
#घोषणा DMA_GCMD_SFL (((u32)1) << 29)
#घोषणा DMA_GCMD_EAFL (((u32)1) << 28)
#घोषणा DMA_GCMD_WBF (((u32)1) << 27)
#घोषणा DMA_GCMD_QIE (((u32)1) << 26)
#घोषणा DMA_GCMD_SIRTP (((u32)1) << 24)
#घोषणा DMA_GCMD_IRE (((u32) 1) << 25)
#घोषणा DMA_GCMD_CFI (((u32) 1) << 23)

/* GSTS_REG */
#घोषणा DMA_GSTS_TES (((u32)1) << 31)
#घोषणा DMA_GSTS_RTPS (((u32)1) << 30)
#घोषणा DMA_GSTS_FLS (((u32)1) << 29)
#घोषणा DMA_GSTS_AFLS (((u32)1) << 28)
#घोषणा DMA_GSTS_WBFS (((u32)1) << 27)
#घोषणा DMA_GSTS_QIES (((u32)1) << 26)
#घोषणा DMA_GSTS_IRTPS (((u32)1) << 24)
#घोषणा DMA_GSTS_IRES (((u32)1) << 25)
#घोषणा DMA_GSTS_CFIS (((u32)1) << 23)

/* DMA_RTADDR_REG */
#घोषणा DMA_RTADDR_RTT (((u64)1) << 11)
#घोषणा DMA_RTADDR_SMT (((u64)1) << 10)

/* CCMD_REG */
#घोषणा DMA_CCMD_ICC (((u64)1) << 63)
#घोषणा DMA_CCMD_GLOBAL_INVL (((u64)1) << 61)
#घोषणा DMA_CCMD_DOMAIN_INVL (((u64)2) << 61)
#घोषणा DMA_CCMD_DEVICE_INVL (((u64)3) << 61)
#घोषणा DMA_CCMD_FM(m) (((u64)((m) & 0x3)) << 32)
#घोषणा DMA_CCMD_MASK_NOBIT 0
#घोषणा DMA_CCMD_MASK_1BIT 1
#घोषणा DMA_CCMD_MASK_2BIT 2
#घोषणा DMA_CCMD_MASK_3BIT 3
#घोषणा DMA_CCMD_SID(s) (((u64)((s) & 0xffff)) << 16)
#घोषणा DMA_CCMD_DID(d) ((u64)((d) & 0xffff))

/* FECTL_REG */
#घोषणा DMA_FECTL_IM (((u32)1) << 31)

/* FSTS_REG */
#घोषणा DMA_FSTS_PFO (1 << 0) /* Primary Fault Overflow */
#घोषणा DMA_FSTS_PPF (1 << 1) /* Primary Pending Fault */
#घोषणा DMA_FSTS_IQE (1 << 4) /* Invalidation Queue Error */
#घोषणा DMA_FSTS_ICE (1 << 5) /* Invalidation Completion Error */
#घोषणा DMA_FSTS_ITE (1 << 6) /* Invalidation Time-out Error */
#घोषणा DMA_FSTS_PRO (1 << 7) /* Page Request Overflow */
#घोषणा dma_fsts_fault_record_index(s) (((s) >> 8) & 0xff)

/* FRCD_REG, 32 bits access */
#घोषणा DMA_FRCD_F (((u32)1) << 31)
#घोषणा dma_frcd_type(d) ((d >> 30) & 1)
#घोषणा dma_frcd_fault_reason(c) (c & 0xff)
#घोषणा dma_frcd_source_id(c) (c & 0xffff)
#घोषणा dma_frcd_pasid_value(c) (((c) >> 8) & 0xfffff)
#घोषणा dma_frcd_pasid_present(c) (((c) >> 31) & 1)
/* low 64 bit */
#घोषणा dma_frcd_page_addr(d) (d & (((u64)-1) << PAGE_SHIFT))

/* PRS_REG */
#घोषणा DMA_PRS_PPR	((u32)1)
#घोषणा DMA_PRS_PRO	((u32)2)

#घोषणा DMA_VCS_PAS	((u64)1)

#घोषणा IOMMU_WAIT_OP(iommu, offset, op, cond, sts)			\
करो अणु									\
	cycles_t start_समय = get_cycles();				\
	जबतक (1) अणु							\
		sts = op(iommu->reg + offset);				\
		अगर (cond)						\
			अवरोध;						\
		अगर (DMAR_OPERATION_TIMEOUT < (get_cycles() - start_समय))\
			panic("DMAR hardware is malfunctioning\n");	\
		cpu_relax();						\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा QI_LENGTH	256	/* queue length */

क्रमागत अणु
	QI_FREE,
	QI_IN_USE,
	QI_DONE,
	QI_ABORT
पूर्ण;

#घोषणा QI_CC_TYPE		0x1
#घोषणा QI_IOTLB_TYPE		0x2
#घोषणा QI_DIOTLB_TYPE		0x3
#घोषणा QI_IEC_TYPE		0x4
#घोषणा QI_IWD_TYPE		0x5
#घोषणा QI_EIOTLB_TYPE		0x6
#घोषणा QI_PC_TYPE		0x7
#घोषणा QI_DEIOTLB_TYPE		0x8
#घोषणा QI_PGRP_RESP_TYPE	0x9
#घोषणा QI_PSTRM_RESP_TYPE	0xa

#घोषणा QI_IEC_SELECTIVE	(((u64)1) << 4)
#घोषणा QI_IEC_IIDEX(idx)	(((u64)(idx & 0xffff) << 32))
#घोषणा QI_IEC_IM(m)		(((u64)(m & 0x1f) << 27))

#घोषणा QI_IWD_STATUS_DATA(d)	(((u64)d) << 32)
#घोषणा QI_IWD_STATUS_WRITE	(((u64)1) << 5)
#घोषणा QI_IWD_FENCE		(((u64)1) << 6)
#घोषणा QI_IWD_PRQ_DRAIN	(((u64)1) << 7)

#घोषणा QI_IOTLB_DID(did) 	(((u64)did) << 16)
#घोषणा QI_IOTLB_DR(dr) 	(((u64)dr) << 7)
#घोषणा QI_IOTLB_DW(dw) 	(((u64)dw) << 6)
#घोषणा QI_IOTLB_GRAN(gran) 	(((u64)gran) >> (DMA_TLB_FLUSH_GRANU_OFFSET-4))
#घोषणा QI_IOTLB_ADDR(addr)	(((u64)addr) & VTD_PAGE_MASK)
#घोषणा QI_IOTLB_IH(ih)		(((u64)ih) << 6)
#घोषणा QI_IOTLB_AM(am)		(((u8)am) & 0x3f)

#घोषणा QI_CC_FM(fm)		(((u64)fm) << 48)
#घोषणा QI_CC_SID(sid)		(((u64)sid) << 32)
#घोषणा QI_CC_DID(did)		(((u64)did) << 16)
#घोषणा QI_CC_GRAN(gran)	(((u64)gran) >> (DMA_CCMD_INVL_GRANU_OFFSET-4))

#घोषणा QI_DEV_IOTLB_SID(sid)	((u64)((sid) & 0xffff) << 32)
#घोषणा QI_DEV_IOTLB_QDEP(qdep)	(((qdep) & 0x1f) << 16)
#घोषणा QI_DEV_IOTLB_ADDR(addr)	((u64)(addr) & VTD_PAGE_MASK)
#घोषणा QI_DEV_IOTLB_PFSID(pfsid) (((u64)(pfsid & 0xf) << 12) | \
				   ((u64)((pfsid >> 4) & 0xfff) << 52))
#घोषणा QI_DEV_IOTLB_SIZE	1
#घोषणा QI_DEV_IOTLB_MAX_INVS	32

#घोषणा QI_PC_PASID(pasid)	(((u64)pasid) << 32)
#घोषणा QI_PC_DID(did)		(((u64)did) << 16)
#घोषणा QI_PC_GRAN(gran)	(((u64)gran) << 4)

/* PASID cache invalidation granu */
#घोषणा QI_PC_ALL_PASIDS	0
#घोषणा QI_PC_PASID_SEL		1
#घोषणा QI_PC_GLOBAL		3

#घोषणा QI_EIOTLB_ADDR(addr)	((u64)(addr) & VTD_PAGE_MASK)
#घोषणा QI_EIOTLB_IH(ih)	(((u64)ih) << 6)
#घोषणा QI_EIOTLB_AM(am)	(((u64)am) & 0x3f)
#घोषणा QI_EIOTLB_PASID(pasid) 	(((u64)pasid) << 32)
#घोषणा QI_EIOTLB_DID(did)	(((u64)did) << 16)
#घोषणा QI_EIOTLB_GRAN(gran) 	(((u64)gran) << 4)

/* QI Dev-IOTLB inv granu */
#घोषणा QI_DEV_IOTLB_GRAN_ALL		1
#घोषणा QI_DEV_IOTLB_GRAN_PASID_SEL	0

#घोषणा QI_DEV_EIOTLB_ADDR(a)	((u64)(a) & VTD_PAGE_MASK)
#घोषणा QI_DEV_EIOTLB_SIZE	(((u64)1) << 11)
#घोषणा QI_DEV_EIOTLB_PASID(p)	((u64)((p) & 0xfffff) << 32)
#घोषणा QI_DEV_EIOTLB_SID(sid)	((u64)((sid) & 0xffff) << 16)
#घोषणा QI_DEV_EIOTLB_QDEP(qd)	((u64)((qd) & 0x1f) << 4)
#घोषणा QI_DEV_EIOTLB_PFSID(pfsid) (((u64)(pfsid & 0xf) << 12) | \
				    ((u64)((pfsid >> 4) & 0xfff) << 52))
#घोषणा QI_DEV_EIOTLB_MAX_INVS	32

/* Page group response descriptor QW0 */
#घोषणा QI_PGRP_PASID_P(p)	(((u64)(p)) << 4)
#घोषणा QI_PGRP_PDP(p)		(((u64)(p)) << 5)
#घोषणा QI_PGRP_RESP_CODE(res)	(((u64)(res)) << 12)
#घोषणा QI_PGRP_DID(rid)	(((u64)(rid)) << 16)
#घोषणा QI_PGRP_PASID(pasid)	(((u64)(pasid)) << 32)

/* Page group response descriptor QW1 */
#घोषणा QI_PGRP_LPIG(x)		(((u64)(x)) << 2)
#घोषणा QI_PGRP_IDX(idx)	(((u64)(idx)) << 3)


#घोषणा QI_RESP_SUCCESS		0x0
#घोषणा QI_RESP_INVALID		0x1
#घोषणा QI_RESP_FAILURE		0xf

#घोषणा QI_GRAN_NONG_PASID		2
#घोषणा QI_GRAN_PSI_PASID		3

#घोषणा qi_shअगरt(iommu)		(DMAR_IQ_SHIFT + !!ecap_smts((iommu)->ecap))

काष्ठा qi_desc अणु
	u64 qw0;
	u64 qw1;
	u64 qw2;
	u64 qw3;
पूर्ण;

काष्ठा q_inval अणु
	raw_spinlock_t  q_lock;
	व्योम		*desc;          /* invalidation queue */
	पूर्णांक             *desc_status;   /* desc status */
	पूर्णांक             मुक्त_head;      /* first मुक्त entry */
	पूर्णांक             मुक्त_tail;      /* last मुक्त entry */
	पूर्णांक             मुक्त_cnt;
पूर्ण;

काष्ठा dmar_pci_notअगरy_info;

#अगर_घोषित CONFIG_IRQ_REMAP
/* 1MB - maximum possible पूर्णांकerrupt remapping table size */
#घोषणा INTR_REMAP_PAGE_ORDER	8
#घोषणा INTR_REMAP_TABLE_REG_SIZE	0xf
#घोषणा INTR_REMAP_TABLE_REG_SIZE_MASK  0xf

#घोषणा INTR_REMAP_TABLE_ENTRIES	65536

काष्ठा irq_करोमुख्य;

काष्ठा ir_table अणु
	काष्ठा irte *base;
	अचिन्हित दीर्घ *biपंचांगap;
पूर्ण;

व्योम पूर्णांकel_irq_remap_add_device(काष्ठा dmar_pci_notअगरy_info *info);
#अन्यथा
अटल अंतरभूत व्योम
पूर्णांकel_irq_remap_add_device(काष्ठा dmar_pci_notअगरy_info *info) अणु पूर्ण
#पूर्ण_अगर

काष्ठा iommu_flush अणु
	व्योम (*flush_context)(काष्ठा पूर्णांकel_iommu *iommu, u16 did, u16 sid,
			      u8 fm, u64 type);
	व्योम (*flush_iotlb)(काष्ठा पूर्णांकel_iommu *iommu, u16 did, u64 addr,
			    अचिन्हित पूर्णांक size_order, u64 type);
पूर्ण;

क्रमागत अणु
	SR_DMAR_FECTL_REG,
	SR_DMAR_FEDATA_REG,
	SR_DMAR_FEADDR_REG,
	SR_DMAR_FEUADDR_REG,
	MAX_SR_DMAR_REGS
पूर्ण;

#घोषणा VTD_FLAG_TRANS_PRE_ENABLED	(1 << 0)
#घोषणा VTD_FLAG_IRQ_REMAP_PRE_ENABLED	(1 << 1)
#घोषणा VTD_FLAG_SVM_CAPABLE		(1 << 2)

बाह्य पूर्णांक पूर्णांकel_iommu_sm;
बाह्य spinlock_t device_करोमुख्य_lock;

#घोषणा sm_supported(iommu)	(पूर्णांकel_iommu_sm && ecap_smts((iommu)->ecap))
#घोषणा pasid_supported(iommu)	(sm_supported(iommu) &&			\
				 ecap_pasid((iommu)->ecap))

काष्ठा pasid_entry;
काष्ठा pasid_state_entry;
काष्ठा page_req_dsc;

/*
 * 0: Present
 * 1-11: Reserved
 * 12-63: Context Ptr (12 - (haw-1))
 * 64-127: Reserved
 */
काष्ठा root_entry अणु
	u64     lo;
	u64     hi;
पूर्ण;

/*
 * low 64 bits:
 * 0: present
 * 1: fault processing disable
 * 2-3: translation type
 * 12-63: address space root
 * high 64 bits:
 * 0-2: address width
 * 3-6: aval
 * 8-23: करोमुख्य id
 */
काष्ठा context_entry अणु
	u64 lo;
	u64 hi;
पूर्ण;

/* si_करोमुख्य contains mulitple devices */
#घोषणा DOMAIN_FLAG_STATIC_IDENTITY		BIT(0)

/*
 * When VT-d works in the scalable mode, it allows DMA translation to
 * happen through either first level or second level page table. This
 * bit marks that the DMA translation क्रम the करोमुख्य goes through the
 * first level page table, otherwise, it goes through the second level.
 */
#घोषणा DOMAIN_FLAG_USE_FIRST_LEVEL		BIT(1)

/*
 * Doमुख्य represents a भव machine which demands iommu nested
 * translation mode support.
 */
#घोषणा DOMAIN_FLAG_NESTING_MODE		BIT(2)

काष्ठा dmar_करोमुख्य अणु
	पूर्णांक	nid;			/* node id */

	अचिन्हित	iommu_refcnt[DMAR_UNITS_SUPPORTED];
					/* Refcount of devices per iommu */


	u16		iommu_did[DMAR_UNITS_SUPPORTED];
					/* Doमुख्य ids per IOMMU. Use u16 since
					 * करोमुख्य ids are 16 bit wide according
					 * to VT-d spec, section 9.3 */

	bool has_iotlb_device;
	काष्ठा list_head devices;	/* all devices' list */
	काष्ठा list_head subdevices;	/* all subdevices' list */
	काष्ठा iova_करोमुख्य iovad;	/* iova's that beदीर्घ to this करोमुख्य */

	काष्ठा dma_pte	*pgd;		/* भव address */
	पूर्णांक		gaw;		/* max guest address width */

	/* adjusted guest address width, 0 is level 2 30-bit */
	पूर्णांक		agaw;

	पूर्णांक		flags;		/* flags to find out type of करोमुख्य */

	पूर्णांक		iommu_coherency;/* indicate coherency of iommu access */
	पूर्णांक		iommu_snooping; /* indicate snooping control feature*/
	पूर्णांक		iommu_count;	/* reference count of iommu */
	पूर्णांक		iommu_superpage;/* Level of superpages supported:
					   0 == 4KiB (no superpages), 1 == 2MiB,
					   2 == 1GiB, 3 == 512GiB, 4 == 1TiB */
	u64		max_addr;	/* maximum mapped address */

	u32		शेष_pasid;	/*
					 * The शेष pasid used क्रम non-SVM
					 * traffic on mediated devices.
					 */

	काष्ठा iommu_करोमुख्य करोमुख्य;	/* generic करोमुख्य data काष्ठाure क्रम
					   iommu core */
पूर्ण;

काष्ठा पूर्णांकel_iommu अणु
	व्योम __iomem	*reg; /* Poपूर्णांकer to hardware regs, भव addr */
	u64 		reg_phys; /* physical address of hw रेजिस्टर set */
	u64		reg_size; /* size of hw रेजिस्टर set */
	u64		cap;
	u64		ecap;
	u64		vccap;
	u32		gcmd; /* Holds TE, EAFL. Don't need SRTP, SFL, WBF */
	raw_spinlock_t	रेजिस्टर_lock; /* protect रेजिस्टर handling */
	पूर्णांक		seq_id;	/* sequence id of the iommu */
	पूर्णांक		agaw; /* agaw of this iommu */
	पूर्णांक		msagaw; /* max sagaw of this iommu */
	अचिन्हित पूर्णांक 	irq, pr_irq;
	u16		segment;     /* PCI segment# */
	अचिन्हित अक्षर 	name[13];    /* Device Name */

#अगर_घोषित CONFIG_INTEL_IOMMU
	अचिन्हित दीर्घ 	*करोमुख्य_ids; /* biपंचांगap of करोमुख्यs */
	काष्ठा dmar_करोमुख्य ***करोमुख्यs; /* ptr to करोमुख्यs */
	spinlock_t	lock; /* protect context, करोमुख्य ids */
	काष्ठा root_entry *root_entry; /* भव address */

	काष्ठा iommu_flush flush;
#पूर्ण_अगर
#अगर_घोषित CONFIG_INTEL_IOMMU_SVM
	काष्ठा page_req_dsc *prq;
	अचिन्हित अक्षर prq_name[16];    /* Name क्रम PRQ पूर्णांकerrupt */
	काष्ठा completion prq_complete;
	काष्ठा ioasid_allocator_ops pasid_allocator; /* Custom allocator क्रम PASIDs */
#पूर्ण_अगर
	काष्ठा q_inval  *qi;            /* Queued invalidation info */
	u32 *iommu_state; /* Store iommu states between suspend and resume.*/

#अगर_घोषित CONFIG_IRQ_REMAP
	काष्ठा ir_table *ir_table;	/* Interrupt remapping info */
	काष्ठा irq_करोमुख्य *ir_करोमुख्य;
	काष्ठा irq_करोमुख्य *ir_msi_करोमुख्य;
#पूर्ण_अगर
	काष्ठा iommu_device iommu;  /* IOMMU core code handle */
	पूर्णांक		node;
	u32		flags;      /* Software defined flags */

	काष्ठा dmar_drhd_unit *drhd;
पूर्ण;

/* Per subdevice निजी data */
काष्ठा subdev_करोमुख्य_info अणु
	काष्ठा list_head link_phys;	/* link to phys device siblings */
	काष्ठा list_head link_करोमुख्य;	/* link to करोमुख्य siblings */
	काष्ठा device *pdev;		/* physical device derived from */
	काष्ठा dmar_करोमुख्य *करोमुख्य;	/* aux-करोमुख्य */
	पूर्णांक users;			/* user count */
पूर्ण;

/* PCI करोमुख्य-device relationship */
काष्ठा device_करोमुख्य_info अणु
	काष्ठा list_head link;	/* link to करोमुख्य siblings */
	काष्ठा list_head global; /* link to global list */
	काष्ठा list_head table;	/* link to pasid table */
	काष्ठा list_head subdevices; /* subdevices sibling */
	u32 segment;		/* PCI segment number */
	u8 bus;			/* PCI bus number */
	u8 devfn;		/* PCI devfn number */
	u16 pfsid;		/* SRIOV physical function source ID */
	u8 pasid_supported:3;
	u8 pasid_enabled:1;
	u8 pri_supported:1;
	u8 pri_enabled:1;
	u8 ats_supported:1;
	u8 ats_enabled:1;
	u8 auxd_enabled:1;	/* Multiple करोमुख्यs per device */
	u8 ats_qdep;
	काष्ठा device *dev; /* it's शून्य क्रम PCIe-to-PCI bridge */
	काष्ठा पूर्णांकel_iommu *iommu; /* IOMMU used by this device */
	काष्ठा dmar_करोमुख्य *करोमुख्य; /* poपूर्णांकer to करोमुख्य */
	काष्ठा pasid_table *pasid_table; /* pasid table */
पूर्ण;

अटल अंतरभूत व्योम __iommu_flush_cache(
	काष्ठा पूर्णांकel_iommu *iommu, व्योम *addr, पूर्णांक size)
अणु
	अगर (!ecap_coherent(iommu->ecap))
		clflush_cache_range(addr, size);
पूर्ण

/* Convert generic काष्ठा iommu_करोमुख्य to निजी काष्ठा dmar_करोमुख्य */
अटल अंतरभूत काष्ठा dmar_करोमुख्य *to_dmar_करोमुख्य(काष्ठा iommu_करोमुख्य *करोm)
अणु
	वापस container_of(करोm, काष्ठा dmar_करोमुख्य, करोमुख्य);
पूर्ण

/*
 * 0: पढ़ोable
 * 1: writable
 * 2-6: reserved
 * 7: super page
 * 8-10: available
 * 11: snoop behavior
 * 12-63: Host physical address
 */
काष्ठा dma_pte अणु
	u64 val;
पूर्ण;

अटल अंतरभूत व्योम dma_clear_pte(काष्ठा dma_pte *pte)
अणु
	pte->val = 0;
पूर्ण

अटल अंतरभूत u64 dma_pte_addr(काष्ठा dma_pte *pte)
अणु
#अगर_घोषित CONFIG_64BIT
	वापस pte->val & VTD_PAGE_MASK & (~DMA_FL_PTE_XD);
#अन्यथा
	/* Must have a full atomic 64-bit पढ़ो */
	वापस  __cmpxchg64(&pte->val, 0ULL, 0ULL) &
			VTD_PAGE_MASK & (~DMA_FL_PTE_XD);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool dma_pte_present(काष्ठा dma_pte *pte)
अणु
	वापस (pte->val & 3) != 0;
पूर्ण

अटल अंतरभूत bool dma_pte_superpage(काष्ठा dma_pte *pte)
अणु
	वापस (pte->val & DMA_PTE_LARGE_PAGE);
पूर्ण

अटल अंतरभूत पूर्णांक first_pte_in_page(काष्ठा dma_pte *pte)
अणु
	वापस !((अचिन्हित दीर्घ)pte & ~VTD_PAGE_MASK);
पूर्ण

बाह्य काष्ठा dmar_drhd_unit * dmar_find_matched_drhd_unit(काष्ठा pci_dev *dev);
बाह्य पूर्णांक dmar_find_matched_atsr_unit(काष्ठा pci_dev *dev);

बाह्य पूर्णांक dmar_enable_qi(काष्ठा पूर्णांकel_iommu *iommu);
बाह्य व्योम dmar_disable_qi(काष्ठा पूर्णांकel_iommu *iommu);
बाह्य पूर्णांक dmar_reenable_qi(काष्ठा पूर्णांकel_iommu *iommu);
बाह्य व्योम qi_global_iec(काष्ठा पूर्णांकel_iommu *iommu);

बाह्य व्योम qi_flush_context(काष्ठा पूर्णांकel_iommu *iommu, u16 did, u16 sid,
			     u8 fm, u64 type);
बाह्य व्योम qi_flush_iotlb(काष्ठा पूर्णांकel_iommu *iommu, u16 did, u64 addr,
			  अचिन्हित पूर्णांक size_order, u64 type);
बाह्य व्योम qi_flush_dev_iotlb(काष्ठा पूर्णांकel_iommu *iommu, u16 sid, u16 pfsid,
			u16 qdep, u64 addr, अचिन्हित mask);

व्योम qi_flush_piotlb(काष्ठा पूर्णांकel_iommu *iommu, u16 did, u32 pasid, u64 addr,
		     अचिन्हित दीर्घ npages, bool ih);

व्योम qi_flush_dev_iotlb_pasid(काष्ठा पूर्णांकel_iommu *iommu, u16 sid, u16 pfsid,
			      u32 pasid, u16 qdep, u64 addr,
			      अचिन्हित पूर्णांक size_order);
व्योम qi_flush_pasid_cache(काष्ठा पूर्णांकel_iommu *iommu, u16 did, u64 granu,
			  u32 pasid);

पूर्णांक qi_submit_sync(काष्ठा पूर्णांकel_iommu *iommu, काष्ठा qi_desc *desc,
		   अचिन्हित पूर्णांक count, अचिन्हित दीर्घ options);
/*
 * Options used in qi_submit_sync:
 * QI_OPT_WAIT_DRAIN - Wait क्रम PRQ drain completion, spec 6.5.2.8.
 */
#घोषणा QI_OPT_WAIT_DRAIN		BIT(0)

बाह्य पूर्णांक dmar_ir_support(व्योम);

व्योम *alloc_pgtable_page(पूर्णांक node);
व्योम मुक्त_pgtable_page(व्योम *vaddr);
काष्ठा पूर्णांकel_iommu *करोमुख्य_get_iommu(काष्ठा dmar_करोमुख्य *करोमुख्य);
पूर्णांक क्रम_each_device_करोमुख्य(पूर्णांक (*fn)(काष्ठा device_करोमुख्य_info *info,
				     व्योम *data), व्योम *data);
व्योम iommu_flush_ग_लिखो_buffer(काष्ठा पूर्णांकel_iommu *iommu);
पूर्णांक पूर्णांकel_iommu_enable_pasid(काष्ठा पूर्णांकel_iommu *iommu, काष्ठा device *dev);
काष्ठा dmar_करोमुख्य *find_करोमुख्य(काष्ठा device *dev);
काष्ठा device_करोमुख्य_info *get_करोमुख्य_info(काष्ठा device *dev);
काष्ठा पूर्णांकel_iommu *device_to_iommu(काष्ठा device *dev, u8 *bus, u8 *devfn);

#अगर_घोषित CONFIG_INTEL_IOMMU_SVM
बाह्य व्योम पूर्णांकel_svm_check(काष्ठा पूर्णांकel_iommu *iommu);
बाह्य पूर्णांक पूर्णांकel_svm_enable_prq(काष्ठा पूर्णांकel_iommu *iommu);
बाह्य पूर्णांक पूर्णांकel_svm_finish_prq(काष्ठा पूर्णांकel_iommu *iommu);
पूर्णांक पूर्णांकel_svm_bind_gpasid(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev,
			  काष्ठा iommu_gpasid_bind_data *data);
पूर्णांक पूर्णांकel_svm_unbind_gpasid(काष्ठा device *dev, u32 pasid);
काष्ठा iommu_sva *पूर्णांकel_svm_bind(काष्ठा device *dev, काष्ठा mm_काष्ठा *mm,
				 व्योम *drvdata);
व्योम पूर्णांकel_svm_unbind(काष्ठा iommu_sva *handle);
u32 पूर्णांकel_svm_get_pasid(काष्ठा iommu_sva *handle);
पूर्णांक पूर्णांकel_svm_page_response(काष्ठा device *dev, काष्ठा iommu_fault_event *evt,
			    काष्ठा iommu_page_response *msg);

काष्ठा पूर्णांकel_svm_dev अणु
	काष्ठा list_head list;
	काष्ठा rcu_head rcu;
	काष्ठा device *dev;
	काष्ठा पूर्णांकel_iommu *iommu;
	काष्ठा iommu_sva sva;
	u32 pasid;
	पूर्णांक users;
	u16 did;
	u16 dev_iotlb:1;
	u16 sid, qdep;
पूर्ण;

काष्ठा पूर्णांकel_svm अणु
	काष्ठा mmu_notअगरier notअगरier;
	काष्ठा mm_काष्ठा *mm;

	अचिन्हित पूर्णांक flags;
	u32 pasid;
	पूर्णांक gpasid; /* In हाल that guest PASID is dअगरferent from host PASID */
	काष्ठा list_head devs;
	काष्ठा list_head list;
पूर्ण;
#अन्यथा
अटल अंतरभूत व्योम पूर्णांकel_svm_check(काष्ठा पूर्णांकel_iommu *iommu) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_INTEL_IOMMU_DEBUGFS
व्योम पूर्णांकel_iommu_debugfs_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम पूर्णांकel_iommu_debugfs_init(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_INTEL_IOMMU_DEBUGFS */

बाह्य स्थिर काष्ठा attribute_group *पूर्णांकel_iommu_groups[];
bool context_present(काष्ठा context_entry *context);
काष्ठा context_entry *iommu_context_addr(काष्ठा पूर्णांकel_iommu *iommu, u8 bus,
					 u8 devfn, पूर्णांक alloc);

#अगर_घोषित CONFIG_INTEL_IOMMU
बाह्य पूर्णांक iommu_calculate_agaw(काष्ठा पूर्णांकel_iommu *iommu);
बाह्य पूर्णांक iommu_calculate_max_sagaw(काष्ठा पूर्णांकel_iommu *iommu);
बाह्य पूर्णांक dmar_disabled;
बाह्य पूर्णांक पूर्णांकel_iommu_enabled;
बाह्य पूर्णांक पूर्णांकel_iommu_gfx_mapped;
#अन्यथा
अटल अंतरभूत पूर्णांक iommu_calculate_agaw(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक iommu_calculate_max_sagaw(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	वापस 0;
पूर्ण
#घोषणा dmar_disabled	(1)
#घोषणा पूर्णांकel_iommu_enabled (0)
#पूर्ण_अगर

#पूर्ण_अगर
