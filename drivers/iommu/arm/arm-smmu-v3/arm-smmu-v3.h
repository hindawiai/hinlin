<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * IOMMU API क्रम ARM architected SMMUv3 implementations.
 *
 * Copyright (C) 2015 ARM Limited
 */

#अगर_अघोषित _ARM_SMMU_V3_H
#घोषणा _ARM_SMMU_V3_H

#समावेश <linux/bitfield.h>
#समावेश <linux/iommu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/sizes.h>

/* MMIO रेजिस्टरs */
#घोषणा ARM_SMMU_IDR0			0x0
#घोषणा IDR0_ST_LVL			GENMASK(28, 27)
#घोषणा IDR0_ST_LVL_2LVL		1
#घोषणा IDR0_STALL_MODEL		GENMASK(25, 24)
#घोषणा IDR0_STALL_MODEL_STALL		0
#घोषणा IDR0_STALL_MODEL_FORCE		2
#घोषणा IDR0_TTENDIAN			GENMASK(22, 21)
#घोषणा IDR0_TTENDIAN_MIXED		0
#घोषणा IDR0_TTENDIAN_LE		2
#घोषणा IDR0_TTENDIAN_BE		3
#घोषणा IDR0_CD2L			(1 << 19)
#घोषणा IDR0_VMID16			(1 << 18)
#घोषणा IDR0_PRI			(1 << 16)
#घोषणा IDR0_SEV			(1 << 14)
#घोषणा IDR0_MSI			(1 << 13)
#घोषणा IDR0_ASID16			(1 << 12)
#घोषणा IDR0_ATS			(1 << 10)
#घोषणा IDR0_HYP			(1 << 9)
#घोषणा IDR0_COHACC			(1 << 4)
#घोषणा IDR0_TTF			GENMASK(3, 2)
#घोषणा IDR0_TTF_AARCH64		2
#घोषणा IDR0_TTF_AARCH32_64		3
#घोषणा IDR0_S1P			(1 << 1)
#घोषणा IDR0_S2P			(1 << 0)

#घोषणा ARM_SMMU_IDR1			0x4
#घोषणा IDR1_TABLES_PRESET		(1 << 30)
#घोषणा IDR1_QUEUES_PRESET		(1 << 29)
#घोषणा IDR1_REL			(1 << 28)
#घोषणा IDR1_CMDQS			GENMASK(25, 21)
#घोषणा IDR1_EVTQS			GENMASK(20, 16)
#घोषणा IDR1_PRIQS			GENMASK(15, 11)
#घोषणा IDR1_SSIDSIZE			GENMASK(10, 6)
#घोषणा IDR1_SIDSIZE			GENMASK(5, 0)

#घोषणा ARM_SMMU_IDR3			0xc
#घोषणा IDR3_RIL			(1 << 10)

#घोषणा ARM_SMMU_IDR5			0x14
#घोषणा IDR5_STALL_MAX			GENMASK(31, 16)
#घोषणा IDR5_GRAN64K			(1 << 6)
#घोषणा IDR5_GRAN16K			(1 << 5)
#घोषणा IDR5_GRAN4K			(1 << 4)
#घोषणा IDR5_OAS			GENMASK(2, 0)
#घोषणा IDR5_OAS_32_BIT			0
#घोषणा IDR5_OAS_36_BIT			1
#घोषणा IDR5_OAS_40_BIT			2
#घोषणा IDR5_OAS_42_BIT			3
#घोषणा IDR5_OAS_44_BIT			4
#घोषणा IDR5_OAS_48_BIT			5
#घोषणा IDR5_OAS_52_BIT			6
#घोषणा IDR5_VAX			GENMASK(11, 10)
#घोषणा IDR5_VAX_52_BIT			1

#घोषणा ARM_SMMU_CR0			0x20
#घोषणा CR0_ATSCHK			(1 << 4)
#घोषणा CR0_CMDQEN			(1 << 3)
#घोषणा CR0_EVTQEN			(1 << 2)
#घोषणा CR0_PRIQEN			(1 << 1)
#घोषणा CR0_SMMUEN			(1 << 0)

#घोषणा ARM_SMMU_CR0ACK			0x24

#घोषणा ARM_SMMU_CR1			0x28
#घोषणा CR1_TABLE_SH			GENMASK(11, 10)
#घोषणा CR1_TABLE_OC			GENMASK(9, 8)
#घोषणा CR1_TABLE_IC			GENMASK(7, 6)
#घोषणा CR1_QUEUE_SH			GENMASK(5, 4)
#घोषणा CR1_QUEUE_OC			GENMASK(3, 2)
#घोषणा CR1_QUEUE_IC			GENMASK(1, 0)
/* CR1 cacheability fields करोn't quite follow the usual TCR-style encoding */
#घोषणा CR1_CACHE_NC			0
#घोषणा CR1_CACHE_WB			1
#घोषणा CR1_CACHE_WT			2

#घोषणा ARM_SMMU_CR2			0x2c
#घोषणा CR2_PTM				(1 << 2)
#घोषणा CR2_RECINVSID			(1 << 1)
#घोषणा CR2_E2H				(1 << 0)

#घोषणा ARM_SMMU_GBPA			0x44
#घोषणा GBPA_UPDATE			(1 << 31)
#घोषणा GBPA_ABORT			(1 << 20)

#घोषणा ARM_SMMU_IRQ_CTRL		0x50
#घोषणा IRQ_CTRL_EVTQ_IRQEN		(1 << 2)
#घोषणा IRQ_CTRL_PRIQ_IRQEN		(1 << 1)
#घोषणा IRQ_CTRL_GERROR_IRQEN		(1 << 0)

#घोषणा ARM_SMMU_IRQ_CTRLACK		0x54

#घोषणा ARM_SMMU_GERROR			0x60
#घोषणा GERROR_SFM_ERR			(1 << 8)
#घोषणा GERROR_MSI_GERROR_ABT_ERR	(1 << 7)
#घोषणा GERROR_MSI_PRIQ_ABT_ERR		(1 << 6)
#घोषणा GERROR_MSI_EVTQ_ABT_ERR		(1 << 5)
#घोषणा GERROR_MSI_CMDQ_ABT_ERR		(1 << 4)
#घोषणा GERROR_PRIQ_ABT_ERR		(1 << 3)
#घोषणा GERROR_EVTQ_ABT_ERR		(1 << 2)
#घोषणा GERROR_CMDQ_ERR			(1 << 0)
#घोषणा GERROR_ERR_MASK			0x1fd

#घोषणा ARM_SMMU_GERRORN		0x64

#घोषणा ARM_SMMU_GERROR_IRQ_CFG0	0x68
#घोषणा ARM_SMMU_GERROR_IRQ_CFG1	0x70
#घोषणा ARM_SMMU_GERROR_IRQ_CFG2	0x74

#घोषणा ARM_SMMU_STRTAB_BASE		0x80
#घोषणा STRTAB_BASE_RA			(1UL << 62)
#घोषणा STRTAB_BASE_ADDR_MASK		GENMASK_ULL(51, 6)

#घोषणा ARM_SMMU_STRTAB_BASE_CFG	0x88
#घोषणा STRTAB_BASE_CFG_FMT		GENMASK(17, 16)
#घोषणा STRTAB_BASE_CFG_FMT_LINEAR	0
#घोषणा STRTAB_BASE_CFG_FMT_2LVL	1
#घोषणा STRTAB_BASE_CFG_SPLIT		GENMASK(10, 6)
#घोषणा STRTAB_BASE_CFG_LOG2SIZE	GENMASK(5, 0)

#घोषणा ARM_SMMU_CMDQ_BASE		0x90
#घोषणा ARM_SMMU_CMDQ_PROD		0x98
#घोषणा ARM_SMMU_CMDQ_CONS		0x9c

#घोषणा ARM_SMMU_EVTQ_BASE		0xa0
#घोषणा ARM_SMMU_EVTQ_PROD		0xa8
#घोषणा ARM_SMMU_EVTQ_CONS		0xac
#घोषणा ARM_SMMU_EVTQ_IRQ_CFG0		0xb0
#घोषणा ARM_SMMU_EVTQ_IRQ_CFG1		0xb8
#घोषणा ARM_SMMU_EVTQ_IRQ_CFG2		0xbc

#घोषणा ARM_SMMU_PRIQ_BASE		0xc0
#घोषणा ARM_SMMU_PRIQ_PROD		0xc8
#घोषणा ARM_SMMU_PRIQ_CONS		0xcc
#घोषणा ARM_SMMU_PRIQ_IRQ_CFG0		0xd0
#घोषणा ARM_SMMU_PRIQ_IRQ_CFG1		0xd8
#घोषणा ARM_SMMU_PRIQ_IRQ_CFG2		0xdc

#घोषणा ARM_SMMU_REG_SZ			0xe00

/* Common MSI config fields */
#घोषणा MSI_CFG0_ADDR_MASK		GENMASK_ULL(51, 2)
#घोषणा MSI_CFG2_SH			GENMASK(5, 4)
#घोषणा MSI_CFG2_MEMATTR		GENMASK(3, 0)

/* Common memory attribute values */
#घोषणा ARM_SMMU_SH_NSH			0
#घोषणा ARM_SMMU_SH_OSH			2
#घोषणा ARM_SMMU_SH_ISH			3
#घोषणा ARM_SMMU_MEMATTR_DEVICE_nGnRE	0x1
#घोषणा ARM_SMMU_MEMATTR_OIWB		0xf

#घोषणा Q_IDX(llq, p)			((p) & ((1 << (llq)->max_n_shअगरt) - 1))
#घोषणा Q_WRP(llq, p)			((p) & (1 << (llq)->max_n_shअगरt))
#घोषणा Q_OVERFLOW_FLAG			(1U << 31)
#घोषणा Q_OVF(p)			((p) & Q_OVERFLOW_FLAG)
#घोषणा Q_ENT(q, p)			((q)->base +			\
					 Q_IDX(&((q)->llq), p) *	\
					 (q)->ent_dwords)

#घोषणा Q_BASE_RWA			(1UL << 62)
#घोषणा Q_BASE_ADDR_MASK		GENMASK_ULL(51, 5)
#घोषणा Q_BASE_LOG2SIZE			GENMASK(4, 0)

/* Ensure DMA allocations are naturally aligned */
#अगर_घोषित CONFIG_CMA_ALIGNMENT
#घोषणा Q_MAX_SZ_SHIFT			(PAGE_SHIFT + CONFIG_CMA_ALIGNMENT)
#अन्यथा
#घोषणा Q_MAX_SZ_SHIFT			(PAGE_SHIFT + MAX_ORDER - 1)
#पूर्ण_अगर

/*
 * Stream table.
 *
 * Linear: Enough to cover 1 << IDR1.SIDSIZE entries
 * 2lvl: 128k L1 entries,
 *       256 lazy entries per table (each table covers a PCI bus)
 */
#घोषणा STRTAB_L1_SZ_SHIFT		20
#घोषणा STRTAB_SPLIT			8

#घोषणा STRTAB_L1_DESC_DWORDS		1
#घोषणा STRTAB_L1_DESC_SPAN		GENMASK_ULL(4, 0)
#घोषणा STRTAB_L1_DESC_L2PTR_MASK	GENMASK_ULL(51, 6)

#घोषणा STRTAB_STE_DWORDS		8
#घोषणा STRTAB_STE_0_V			(1UL << 0)
#घोषणा STRTAB_STE_0_CFG		GENMASK_ULL(3, 1)
#घोषणा STRTAB_STE_0_CFG_ABORT		0
#घोषणा STRTAB_STE_0_CFG_BYPASS		4
#घोषणा STRTAB_STE_0_CFG_S1_TRANS	5
#घोषणा STRTAB_STE_0_CFG_S2_TRANS	6

#घोषणा STRTAB_STE_0_S1FMT		GENMASK_ULL(5, 4)
#घोषणा STRTAB_STE_0_S1FMT_LINEAR	0
#घोषणा STRTAB_STE_0_S1FMT_64K_L2	2
#घोषणा STRTAB_STE_0_S1CTXPTR_MASK	GENMASK_ULL(51, 6)
#घोषणा STRTAB_STE_0_S1CDMAX		GENMASK_ULL(63, 59)

#घोषणा STRTAB_STE_1_S1DSS		GENMASK_ULL(1, 0)
#घोषणा STRTAB_STE_1_S1DSS_TERMINATE	0x0
#घोषणा STRTAB_STE_1_S1DSS_BYPASS	0x1
#घोषणा STRTAB_STE_1_S1DSS_SSID0	0x2

#घोषणा STRTAB_STE_1_S1C_CACHE_NC	0UL
#घोषणा STRTAB_STE_1_S1C_CACHE_WBRA	1UL
#घोषणा STRTAB_STE_1_S1C_CACHE_WT	2UL
#घोषणा STRTAB_STE_1_S1C_CACHE_WB	3UL
#घोषणा STRTAB_STE_1_S1CIR		GENMASK_ULL(3, 2)
#घोषणा STRTAB_STE_1_S1COR		GENMASK_ULL(5, 4)
#घोषणा STRTAB_STE_1_S1CSH		GENMASK_ULL(7, 6)

#घोषणा STRTAB_STE_1_S1STALLD		(1UL << 27)

#घोषणा STRTAB_STE_1_EATS		GENMASK_ULL(29, 28)
#घोषणा STRTAB_STE_1_EATS_ABT		0UL
#घोषणा STRTAB_STE_1_EATS_TRANS		1UL
#घोषणा STRTAB_STE_1_EATS_S1CHK		2UL

#घोषणा STRTAB_STE_1_STRW		GENMASK_ULL(31, 30)
#घोषणा STRTAB_STE_1_STRW_NSEL1		0UL
#घोषणा STRTAB_STE_1_STRW_EL2		2UL

#घोषणा STRTAB_STE_1_SHCFG		GENMASK_ULL(45, 44)
#घोषणा STRTAB_STE_1_SHCFG_INCOMING	1UL

#घोषणा STRTAB_STE_2_S2VMID		GENMASK_ULL(15, 0)
#घोषणा STRTAB_STE_2_VTCR		GENMASK_ULL(50, 32)
#घोषणा STRTAB_STE_2_VTCR_S2T0SZ	GENMASK_ULL(5, 0)
#घोषणा STRTAB_STE_2_VTCR_S2SL0		GENMASK_ULL(7, 6)
#घोषणा STRTAB_STE_2_VTCR_S2IR0		GENMASK_ULL(9, 8)
#घोषणा STRTAB_STE_2_VTCR_S2OR0		GENMASK_ULL(11, 10)
#घोषणा STRTAB_STE_2_VTCR_S2SH0		GENMASK_ULL(13, 12)
#घोषणा STRTAB_STE_2_VTCR_S2TG		GENMASK_ULL(15, 14)
#घोषणा STRTAB_STE_2_VTCR_S2PS		GENMASK_ULL(18, 16)
#घोषणा STRTAB_STE_2_S2AA64		(1UL << 51)
#घोषणा STRTAB_STE_2_S2ENDI		(1UL << 52)
#घोषणा STRTAB_STE_2_S2PTW		(1UL << 54)
#घोषणा STRTAB_STE_2_S2R		(1UL << 58)

#घोषणा STRTAB_STE_3_S2TTB_MASK		GENMASK_ULL(51, 4)

/*
 * Context descriptors.
 *
 * Linear: when less than 1024 SSIDs are supported
 * 2lvl: at most 1024 L1 entries,
 *       1024 lazy entries per table.
 */
#घोषणा CTXDESC_SPLIT			10
#घोषणा CTXDESC_L2_ENTRIES		(1 << CTXDESC_SPLIT)

#घोषणा CTXDESC_L1_DESC_DWORDS		1
#घोषणा CTXDESC_L1_DESC_V		(1UL << 0)
#घोषणा CTXDESC_L1_DESC_L2PTR_MASK	GENMASK_ULL(51, 12)

#घोषणा CTXDESC_CD_DWORDS		8
#घोषणा CTXDESC_CD_0_TCR_T0SZ		GENMASK_ULL(5, 0)
#घोषणा CTXDESC_CD_0_TCR_TG0		GENMASK_ULL(7, 6)
#घोषणा CTXDESC_CD_0_TCR_IRGN0		GENMASK_ULL(9, 8)
#घोषणा CTXDESC_CD_0_TCR_ORGN0		GENMASK_ULL(11, 10)
#घोषणा CTXDESC_CD_0_TCR_SH0		GENMASK_ULL(13, 12)
#घोषणा CTXDESC_CD_0_TCR_EPD0		(1ULL << 14)
#घोषणा CTXDESC_CD_0_TCR_EPD1		(1ULL << 30)

#घोषणा CTXDESC_CD_0_ENDI		(1UL << 15)
#घोषणा CTXDESC_CD_0_V			(1UL << 31)

#घोषणा CTXDESC_CD_0_TCR_IPS		GENMASK_ULL(34, 32)
#घोषणा CTXDESC_CD_0_TCR_TBI0		(1ULL << 38)

#घोषणा CTXDESC_CD_0_AA64		(1UL << 41)
#घोषणा CTXDESC_CD_0_S			(1UL << 44)
#घोषणा CTXDESC_CD_0_R			(1UL << 45)
#घोषणा CTXDESC_CD_0_A			(1UL << 46)
#घोषणा CTXDESC_CD_0_ASET		(1UL << 47)
#घोषणा CTXDESC_CD_0_ASID		GENMASK_ULL(63, 48)

#घोषणा CTXDESC_CD_1_TTB0_MASK		GENMASK_ULL(51, 4)

/*
 * When the SMMU only supports linear context descriptor tables, pick a
 * reasonable size limit (64kB).
 */
#घोषणा CTXDESC_LINEAR_CDMAX		ilog2(SZ_64K / (CTXDESC_CD_DWORDS << 3))

/* Command queue */
#घोषणा CMDQ_ENT_SZ_SHIFT		4
#घोषणा CMDQ_ENT_DWORDS			((1 << CMDQ_ENT_SZ_SHIFT) >> 3)
#घोषणा CMDQ_MAX_SZ_SHIFT		(Q_MAX_SZ_SHIFT - CMDQ_ENT_SZ_SHIFT)

#घोषणा CMDQ_CONS_ERR			GENMASK(30, 24)
#घोषणा CMDQ_ERR_CERROR_NONE_IDX	0
#घोषणा CMDQ_ERR_CERROR_ILL_IDX		1
#घोषणा CMDQ_ERR_CERROR_ABT_IDX		2
#घोषणा CMDQ_ERR_CERROR_ATC_INV_IDX	3

#घोषणा CMDQ_PROD_OWNED_FLAG		Q_OVERFLOW_FLAG

/*
 * This is used to size the command queue and thereक्रमe must be at least
 * BITS_PER_LONG so that the valid_map works correctly (it relies on the
 * total number of queue entries being a multiple of BITS_PER_LONG).
 */
#घोषणा CMDQ_BATCH_ENTRIES		BITS_PER_LONG

#घोषणा CMDQ_0_OP			GENMASK_ULL(7, 0)
#घोषणा CMDQ_0_SSV			(1UL << 11)

#घोषणा CMDQ_PREFETCH_0_SID		GENMASK_ULL(63, 32)
#घोषणा CMDQ_PREFETCH_1_SIZE		GENMASK_ULL(4, 0)
#घोषणा CMDQ_PREFETCH_1_ADDR_MASK	GENMASK_ULL(63, 12)

#घोषणा CMDQ_CFGI_0_SSID		GENMASK_ULL(31, 12)
#घोषणा CMDQ_CFGI_0_SID			GENMASK_ULL(63, 32)
#घोषणा CMDQ_CFGI_1_LEAF		(1UL << 0)
#घोषणा CMDQ_CFGI_1_RANGE		GENMASK_ULL(4, 0)

#घोषणा CMDQ_TLBI_0_NUM			GENMASK_ULL(16, 12)
#घोषणा CMDQ_TLBI_RANGE_NUM_MAX		31
#घोषणा CMDQ_TLBI_0_SCALE		GENMASK_ULL(24, 20)
#घोषणा CMDQ_TLBI_0_VMID		GENMASK_ULL(47, 32)
#घोषणा CMDQ_TLBI_0_ASID		GENMASK_ULL(63, 48)
#घोषणा CMDQ_TLBI_1_LEAF		(1UL << 0)
#घोषणा CMDQ_TLBI_1_TTL			GENMASK_ULL(9, 8)
#घोषणा CMDQ_TLBI_1_TG			GENMASK_ULL(11, 10)
#घोषणा CMDQ_TLBI_1_VA_MASK		GENMASK_ULL(63, 12)
#घोषणा CMDQ_TLBI_1_IPA_MASK		GENMASK_ULL(51, 12)

#घोषणा CMDQ_ATC_0_SSID			GENMASK_ULL(31, 12)
#घोषणा CMDQ_ATC_0_SID			GENMASK_ULL(63, 32)
#घोषणा CMDQ_ATC_0_GLOBAL		(1UL << 9)
#घोषणा CMDQ_ATC_1_SIZE			GENMASK_ULL(5, 0)
#घोषणा CMDQ_ATC_1_ADDR_MASK		GENMASK_ULL(63, 12)

#घोषणा CMDQ_PRI_0_SSID			GENMASK_ULL(31, 12)
#घोषणा CMDQ_PRI_0_SID			GENMASK_ULL(63, 32)
#घोषणा CMDQ_PRI_1_GRPID		GENMASK_ULL(8, 0)
#घोषणा CMDQ_PRI_1_RESP			GENMASK_ULL(13, 12)

#घोषणा CMDQ_SYNC_0_CS			GENMASK_ULL(13, 12)
#घोषणा CMDQ_SYNC_0_CS_NONE		0
#घोषणा CMDQ_SYNC_0_CS_IRQ		1
#घोषणा CMDQ_SYNC_0_CS_SEV		2
#घोषणा CMDQ_SYNC_0_MSH			GENMASK_ULL(23, 22)
#घोषणा CMDQ_SYNC_0_MSIATTR		GENMASK_ULL(27, 24)
#घोषणा CMDQ_SYNC_0_MSIDATA		GENMASK_ULL(63, 32)
#घोषणा CMDQ_SYNC_1_MSIADDR_MASK	GENMASK_ULL(51, 2)

/* Event queue */
#घोषणा EVTQ_ENT_SZ_SHIFT		5
#घोषणा EVTQ_ENT_DWORDS			((1 << EVTQ_ENT_SZ_SHIFT) >> 3)
#घोषणा EVTQ_MAX_SZ_SHIFT		(Q_MAX_SZ_SHIFT - EVTQ_ENT_SZ_SHIFT)

#घोषणा EVTQ_0_ID			GENMASK_ULL(7, 0)

/* PRI queue */
#घोषणा PRIQ_ENT_SZ_SHIFT		4
#घोषणा PRIQ_ENT_DWORDS			((1 << PRIQ_ENT_SZ_SHIFT) >> 3)
#घोषणा PRIQ_MAX_SZ_SHIFT		(Q_MAX_SZ_SHIFT - PRIQ_ENT_SZ_SHIFT)

#घोषणा PRIQ_0_SID			GENMASK_ULL(31, 0)
#घोषणा PRIQ_0_SSID			GENMASK_ULL(51, 32)
#घोषणा PRIQ_0_PERM_PRIV		(1UL << 58)
#घोषणा PRIQ_0_PERM_EXEC		(1UL << 59)
#घोषणा PRIQ_0_PERM_READ		(1UL << 60)
#घोषणा PRIQ_0_PERM_WRITE		(1UL << 61)
#घोषणा PRIQ_0_PRG_LAST			(1UL << 62)
#घोषणा PRIQ_0_SSID_V			(1UL << 63)

#घोषणा PRIQ_1_PRG_IDX			GENMASK_ULL(8, 0)
#घोषणा PRIQ_1_ADDR_MASK		GENMASK_ULL(63, 12)

/* High-level queue काष्ठाures */
#घोषणा ARM_SMMU_POLL_TIMEOUT_US	1000000 /* 1s! */
#घोषणा ARM_SMMU_POLL_SPIN_COUNT	10

#घोषणा MSI_IOVA_BASE			0x8000000
#घोषणा MSI_IOVA_LENGTH			0x100000

क्रमागत pri_resp अणु
	PRI_RESP_DENY = 0,
	PRI_RESP_FAIL = 1,
	PRI_RESP_SUCC = 2,
पूर्ण;

काष्ठा arm_smmu_cmdq_ent अणु
	/* Common fields */
	u8				opcode;
	bool				substream_valid;

	/* Command-specअगरic fields */
	जोड़ अणु
		#घोषणा CMDQ_OP_PREFETCH_CFG	0x1
		काष्ठा अणु
			u32			sid;
		पूर्ण prefetch;

		#घोषणा CMDQ_OP_CFGI_STE	0x3
		#घोषणा CMDQ_OP_CFGI_ALL	0x4
		#घोषणा CMDQ_OP_CFGI_CD		0x5
		#घोषणा CMDQ_OP_CFGI_CD_ALL	0x6
		काष्ठा अणु
			u32			sid;
			u32			ssid;
			जोड़ अणु
				bool		leaf;
				u8		span;
			पूर्ण;
		पूर्ण cfgi;

		#घोषणा CMDQ_OP_TLBI_NH_ASID	0x11
		#घोषणा CMDQ_OP_TLBI_NH_VA	0x12
		#घोषणा CMDQ_OP_TLBI_EL2_ALL	0x20
		#घोषणा CMDQ_OP_TLBI_EL2_ASID	0x21
		#घोषणा CMDQ_OP_TLBI_EL2_VA	0x22
		#घोषणा CMDQ_OP_TLBI_S12_VMALL	0x28
		#घोषणा CMDQ_OP_TLBI_S2_IPA	0x2a
		#घोषणा CMDQ_OP_TLBI_NSNH_ALL	0x30
		काष्ठा अणु
			u8			num;
			u8			scale;
			u16			asid;
			u16			vmid;
			bool			leaf;
			u8			ttl;
			u8			tg;
			u64			addr;
		पूर्ण tlbi;

		#घोषणा CMDQ_OP_ATC_INV		0x40
		#घोषणा ATC_INV_SIZE_ALL	52
		काष्ठा अणु
			u32			sid;
			u32			ssid;
			u64			addr;
			u8			size;
			bool			global;
		पूर्ण atc;

		#घोषणा CMDQ_OP_PRI_RESP	0x41
		काष्ठा अणु
			u32			sid;
			u32			ssid;
			u16			grpid;
			क्रमागत pri_resp		resp;
		पूर्ण pri;

		#घोषणा CMDQ_OP_CMD_SYNC	0x46
		काष्ठा अणु
			u64			msiaddr;
		पूर्ण sync;
	पूर्ण;
पूर्ण;

काष्ठा arm_smmu_ll_queue अणु
	जोड़ अणु
		u64			val;
		काष्ठा अणु
			u32		prod;
			u32		cons;
		पूर्ण;
		काष्ठा अणु
			atomic_t	prod;
			atomic_t	cons;
		पूर्ण atomic;
		u8			__pad[SMP_CACHE_BYTES];
	पूर्ण ____cacheline_aligned_in_smp;
	u32				max_n_shअगरt;
पूर्ण;

काष्ठा arm_smmu_queue अणु
	काष्ठा arm_smmu_ll_queue	llq;
	पूर्णांक				irq; /* Wired पूर्णांकerrupt */

	__le64				*base;
	dma_addr_t			base_dma;
	u64				q_base;

	माप_प्रकार				ent_dwords;

	u32 __iomem			*prod_reg;
	u32 __iomem			*cons_reg;
पूर्ण;

काष्ठा arm_smmu_queue_poll अणु
	kसमय_प्रकार				समयout;
	अचिन्हित पूर्णांक			delay;
	अचिन्हित पूर्णांक			spin_cnt;
	bool				wfe;
पूर्ण;

काष्ठा arm_smmu_cmdq अणु
	काष्ठा arm_smmu_queue		q;
	atomic_दीर्घ_t			*valid_map;
	atomic_t			owner_prod;
	atomic_t			lock;
पूर्ण;

काष्ठा arm_smmu_cmdq_batch अणु
	u64				cmds[CMDQ_BATCH_ENTRIES * CMDQ_ENT_DWORDS];
	पूर्णांक				num;
पूर्ण;

काष्ठा arm_smmu_evtq अणु
	काष्ठा arm_smmu_queue		q;
	u32				max_stalls;
पूर्ण;

काष्ठा arm_smmu_priq अणु
	काष्ठा arm_smmu_queue		q;
पूर्ण;

/* High-level stream table and context descriptor काष्ठाures */
काष्ठा arm_smmu_strtab_l1_desc अणु
	u8				span;

	__le64				*l2ptr;
	dma_addr_t			l2ptr_dma;
पूर्ण;

काष्ठा arm_smmu_ctx_desc अणु
	u16				asid;
	u64				ttbr;
	u64				tcr;
	u64				mair;

	refcount_t			refs;
	काष्ठा mm_काष्ठा		*mm;
पूर्ण;

काष्ठा arm_smmu_l1_ctx_desc अणु
	__le64				*l2ptr;
	dma_addr_t			l2ptr_dma;
पूर्ण;

काष्ठा arm_smmu_ctx_desc_cfg अणु
	__le64				*cdtab;
	dma_addr_t			cdtab_dma;
	काष्ठा arm_smmu_l1_ctx_desc	*l1_desc;
	अचिन्हित पूर्णांक			num_l1_ents;
पूर्ण;

काष्ठा arm_smmu_s1_cfg अणु
	काष्ठा arm_smmu_ctx_desc_cfg	cdcfg;
	काष्ठा arm_smmu_ctx_desc	cd;
	u8				s1fmt;
	u8				s1cdmax;
पूर्ण;

काष्ठा arm_smmu_s2_cfg अणु
	u16				vmid;
	u64				vttbr;
	u64				vtcr;
पूर्ण;

काष्ठा arm_smmu_strtab_cfg अणु
	__le64				*strtab;
	dma_addr_t			strtab_dma;
	काष्ठा arm_smmu_strtab_l1_desc	*l1_desc;
	अचिन्हित पूर्णांक			num_l1_ents;

	u64				strtab_base;
	u32				strtab_base_cfg;
पूर्ण;

/* An SMMUv3 instance */
काष्ठा arm_smmu_device अणु
	काष्ठा device			*dev;
	व्योम __iomem			*base;
	व्योम __iomem			*page1;

#घोषणा ARM_SMMU_FEAT_2_LVL_STRTAB	(1 << 0)
#घोषणा ARM_SMMU_FEAT_2_LVL_CDTAB	(1 << 1)
#घोषणा ARM_SMMU_FEAT_TT_LE		(1 << 2)
#घोषणा ARM_SMMU_FEAT_TT_BE		(1 << 3)
#घोषणा ARM_SMMU_FEAT_PRI		(1 << 4)
#घोषणा ARM_SMMU_FEAT_ATS		(1 << 5)
#घोषणा ARM_SMMU_FEAT_SEV		(1 << 6)
#घोषणा ARM_SMMU_FEAT_MSI		(1 << 7)
#घोषणा ARM_SMMU_FEAT_COHERENCY		(1 << 8)
#घोषणा ARM_SMMU_FEAT_TRANS_S1		(1 << 9)
#घोषणा ARM_SMMU_FEAT_TRANS_S2		(1 << 10)
#घोषणा ARM_SMMU_FEAT_STALLS		(1 << 11)
#घोषणा ARM_SMMU_FEAT_HYP		(1 << 12)
#घोषणा ARM_SMMU_FEAT_STALL_FORCE	(1 << 13)
#घोषणा ARM_SMMU_FEAT_VAX		(1 << 14)
#घोषणा ARM_SMMU_FEAT_RANGE_INV		(1 << 15)
#घोषणा ARM_SMMU_FEAT_BTM		(1 << 16)
#घोषणा ARM_SMMU_FEAT_SVA		(1 << 17)
#घोषणा ARM_SMMU_FEAT_E2H		(1 << 18)
	u32				features;

#घोषणा ARM_SMMU_OPT_SKIP_PREFETCH	(1 << 0)
#घोषणा ARM_SMMU_OPT_PAGE0_REGS_ONLY	(1 << 1)
#घोषणा ARM_SMMU_OPT_MSIPOLL		(1 << 2)
	u32				options;

	काष्ठा arm_smmu_cmdq		cmdq;
	काष्ठा arm_smmu_evtq		evtq;
	काष्ठा arm_smmu_priq		priq;

	पूर्णांक				gerr_irq;
	पूर्णांक				combined_irq;

	अचिन्हित दीर्घ			ias; /* IPA */
	अचिन्हित दीर्घ			oas; /* PA */
	अचिन्हित दीर्घ			pgsize_biपंचांगap;

#घोषणा ARM_SMMU_MAX_ASIDS		(1 << 16)
	अचिन्हित पूर्णांक			asid_bits;

#घोषणा ARM_SMMU_MAX_VMIDS		(1 << 16)
	अचिन्हित पूर्णांक			vmid_bits;
	DECLARE_BITMAP(vmid_map, ARM_SMMU_MAX_VMIDS);

	अचिन्हित पूर्णांक			ssid_bits;
	अचिन्हित पूर्णांक			sid_bits;

	काष्ठा arm_smmu_strtab_cfg	strtab_cfg;

	/* IOMMU core code handle */
	काष्ठा iommu_device		iommu;

	काष्ठा rb_root			streams;
	काष्ठा mutex			streams_mutex;
पूर्ण;

काष्ठा arm_smmu_stream अणु
	u32				id;
	काष्ठा arm_smmu_master		*master;
	काष्ठा rb_node			node;
पूर्ण;

/* SMMU निजी data क्रम each master */
काष्ठा arm_smmu_master अणु
	काष्ठा arm_smmu_device		*smmu;
	काष्ठा device			*dev;
	काष्ठा arm_smmu_करोमुख्य		*करोमुख्य;
	काष्ठा list_head		करोमुख्य_head;
	काष्ठा arm_smmu_stream		*streams;
	अचिन्हित पूर्णांक			num_streams;
	bool				ats_enabled;
	bool				sva_enabled;
	काष्ठा list_head		bonds;
	अचिन्हित पूर्णांक			ssid_bits;
पूर्ण;

/* SMMU निजी data क्रम an IOMMU करोमुख्य */
क्रमागत arm_smmu_करोमुख्य_stage अणु
	ARM_SMMU_DOMAIN_S1 = 0,
	ARM_SMMU_DOMAIN_S2,
	ARM_SMMU_DOMAIN_NESTED,
	ARM_SMMU_DOMAIN_BYPASS,
पूर्ण;

काष्ठा arm_smmu_करोमुख्य अणु
	काष्ठा arm_smmu_device		*smmu;
	काष्ठा mutex			init_mutex; /* Protects smmu poपूर्णांकer */

	काष्ठा io_pgtable_ops		*pgtbl_ops;
	atomic_t			nr_ats_masters;

	क्रमागत arm_smmu_करोमुख्य_stage	stage;
	जोड़ अणु
		काष्ठा arm_smmu_s1_cfg	s1_cfg;
		काष्ठा arm_smmu_s2_cfg	s2_cfg;
	पूर्ण;

	काष्ठा iommu_करोमुख्य		करोमुख्य;

	काष्ठा list_head		devices;
	spinlock_t			devices_lock;

	काष्ठा list_head		mmu_notअगरiers;
पूर्ण;

अटल अंतरभूत काष्ठा arm_smmu_करोमुख्य *to_smmu_करोमुख्य(काष्ठा iommu_करोमुख्य *करोm)
अणु
	वापस container_of(करोm, काष्ठा arm_smmu_करोमुख्य, करोमुख्य);
पूर्ण

बाह्य काष्ठा xarray arm_smmu_asid_xa;
बाह्य काष्ठा mutex arm_smmu_asid_lock;
बाह्य काष्ठा arm_smmu_ctx_desc quiet_cd;

पूर्णांक arm_smmu_ग_लिखो_ctx_desc(काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य, पूर्णांक ssid,
			    काष्ठा arm_smmu_ctx_desc *cd);
व्योम arm_smmu_tlb_inv_asid(काष्ठा arm_smmu_device *smmu, u16 asid);
व्योम arm_smmu_tlb_inv_range_asid(अचिन्हित दीर्घ iova, माप_प्रकार size, पूर्णांक asid,
				 माप_प्रकार granule, bool leaf,
				 काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य);
bool arm_smmu_मुक्त_asid(काष्ठा arm_smmu_ctx_desc *cd);
पूर्णांक arm_smmu_atc_inv_करोमुख्य(काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य, पूर्णांक ssid,
			    अचिन्हित दीर्घ iova, माप_प्रकार size);

#अगर_घोषित CONFIG_ARM_SMMU_V3_SVA
bool arm_smmu_sva_supported(काष्ठा arm_smmu_device *smmu);
bool arm_smmu_master_sva_supported(काष्ठा arm_smmu_master *master);
bool arm_smmu_master_sva_enabled(काष्ठा arm_smmu_master *master);
पूर्णांक arm_smmu_master_enable_sva(काष्ठा arm_smmu_master *master);
पूर्णांक arm_smmu_master_disable_sva(काष्ठा arm_smmu_master *master);
काष्ठा iommu_sva *arm_smmu_sva_bind(काष्ठा device *dev, काष्ठा mm_काष्ठा *mm,
				    व्योम *drvdata);
व्योम arm_smmu_sva_unbind(काष्ठा iommu_sva *handle);
u32 arm_smmu_sva_get_pasid(काष्ठा iommu_sva *handle);
व्योम arm_smmu_sva_notअगरier_synchronize(व्योम);
#अन्यथा /* CONFIG_ARM_SMMU_V3_SVA */
अटल अंतरभूत bool arm_smmu_sva_supported(काष्ठा arm_smmu_device *smmu)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool arm_smmu_master_sva_supported(काष्ठा arm_smmu_master *master)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool arm_smmu_master_sva_enabled(काष्ठा arm_smmu_master *master)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक arm_smmu_master_enable_sva(काष्ठा arm_smmu_master *master)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक arm_smmu_master_disable_sva(काष्ठा arm_smmu_master *master)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत काष्ठा iommu_sva *
arm_smmu_sva_bind(काष्ठा device *dev, काष्ठा mm_काष्ठा *mm, व्योम *drvdata)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत व्योम arm_smmu_sva_unbind(काष्ठा iommu_sva *handle) अणुपूर्ण

अटल अंतरभूत u32 arm_smmu_sva_get_pasid(काष्ठा iommu_sva *handle)
अणु
	वापस IOMMU_PASID_INVALID;
पूर्ण

अटल अंतरभूत व्योम arm_smmu_sva_notअगरier_synchronize(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_ARM_SMMU_V3_SVA */
#पूर्ण_अगर /* _ARM_SMMU_V3_H */
