<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2007-2010 Advanced Micro Devices, Inc.
 * Author: Joerg Roedel <jroedel@suse.de>
 *         Leo Duran <leo.duran@amd.com>
 */

#अगर_अघोषित _ASM_X86_AMD_IOMMU_TYPES_H
#घोषणा _ASM_X86_AMD_IOMMU_TYPES_H

#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/msi.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pci.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/io-pgtable.h>

/*
 * Maximum number of IOMMUs supported
 */
#घोषणा MAX_IOMMUS	32

/*
 * some size calculation स्थिरants
 */
#घोषणा DEV_TABLE_ENTRY_SIZE		32
#घोषणा ALIAS_TABLE_ENTRY_SIZE		2
#घोषणा RLOOKUP_TABLE_ENTRY_SIZE	(माप(व्योम *))

/* Capability offsets used by the driver */
#घोषणा MMIO_CAP_HDR_OFFSET	0x00
#घोषणा MMIO_RANGE_OFFSET	0x0c
#घोषणा MMIO_MISC_OFFSET	0x10

/* Masks, shअगरts and macros to parse the device range capability */
#घोषणा MMIO_RANGE_LD_MASK	0xff000000
#घोषणा MMIO_RANGE_FD_MASK	0x00ff0000
#घोषणा MMIO_RANGE_BUS_MASK	0x0000ff00
#घोषणा MMIO_RANGE_LD_SHIFT	24
#घोषणा MMIO_RANGE_FD_SHIFT	16
#घोषणा MMIO_RANGE_BUS_SHIFT	8
#घोषणा MMIO_GET_LD(x)  (((x) & MMIO_RANGE_LD_MASK) >> MMIO_RANGE_LD_SHIFT)
#घोषणा MMIO_GET_FD(x)  (((x) & MMIO_RANGE_FD_MASK) >> MMIO_RANGE_FD_SHIFT)
#घोषणा MMIO_GET_BUS(x) (((x) & MMIO_RANGE_BUS_MASK) >> MMIO_RANGE_BUS_SHIFT)
#घोषणा MMIO_MSI_NUM(x)	((x) & 0x1f)

/* Flag masks क्रम the AMD IOMMU exclusion range */
#घोषणा MMIO_EXCL_ENABLE_MASK 0x01ULL
#घोषणा MMIO_EXCL_ALLOW_MASK  0x02ULL

/* Used offsets पूर्णांकo the MMIO space */
#घोषणा MMIO_DEV_TABLE_OFFSET   0x0000
#घोषणा MMIO_CMD_BUF_OFFSET     0x0008
#घोषणा MMIO_EVT_BUF_OFFSET     0x0010
#घोषणा MMIO_CONTROL_OFFSET     0x0018
#घोषणा MMIO_EXCL_BASE_OFFSET   0x0020
#घोषणा MMIO_EXCL_LIMIT_OFFSET  0x0028
#घोषणा MMIO_EXT_FEATURES	0x0030
#घोषणा MMIO_PPR_LOG_OFFSET	0x0038
#घोषणा MMIO_GA_LOG_BASE_OFFSET	0x00e0
#घोषणा MMIO_GA_LOG_TAIL_OFFSET	0x00e8
#घोषणा MMIO_MSI_ADDR_LO_OFFSET	0x015C
#घोषणा MMIO_MSI_ADDR_HI_OFFSET	0x0160
#घोषणा MMIO_MSI_DATA_OFFSET	0x0164
#घोषणा MMIO_INTCAPXT_EVT_OFFSET	0x0170
#घोषणा MMIO_INTCAPXT_PPR_OFFSET	0x0178
#घोषणा MMIO_INTCAPXT_GALOG_OFFSET	0x0180
#घोषणा MMIO_CMD_HEAD_OFFSET	0x2000
#घोषणा MMIO_CMD_TAIL_OFFSET	0x2008
#घोषणा MMIO_EVT_HEAD_OFFSET	0x2010
#घोषणा MMIO_EVT_TAIL_OFFSET	0x2018
#घोषणा MMIO_STATUS_OFFSET	0x2020
#घोषणा MMIO_PPR_HEAD_OFFSET	0x2030
#घोषणा MMIO_PPR_TAIL_OFFSET	0x2038
#घोषणा MMIO_GA_HEAD_OFFSET	0x2040
#घोषणा MMIO_GA_TAIL_OFFSET	0x2048
#घोषणा MMIO_CNTR_CONF_OFFSET	0x4000
#घोषणा MMIO_CNTR_REG_OFFSET	0x40000
#घोषणा MMIO_REG_END_OFFSET	0x80000



/* Extended Feature Bits */
#घोषणा FEATURE_PREFETCH	(1ULL<<0)
#घोषणा FEATURE_PPR		(1ULL<<1)
#घोषणा FEATURE_X2APIC		(1ULL<<2)
#घोषणा FEATURE_NX		(1ULL<<3)
#घोषणा FEATURE_GT		(1ULL<<4)
#घोषणा FEATURE_IA		(1ULL<<6)
#घोषणा FEATURE_GA		(1ULL<<7)
#घोषणा FEATURE_HE		(1ULL<<8)
#घोषणा FEATURE_PC		(1ULL<<9)
#घोषणा FEATURE_GAM_VAPIC	(1ULL<<21)
#घोषणा FEATURE_EPHSUP		(1ULL<<50)
#घोषणा FEATURE_SNP		(1ULL<<63)

#घोषणा FEATURE_PASID_SHIFT	32
#घोषणा FEATURE_PASID_MASK	(0x1fULL << FEATURE_PASID_SHIFT)

#घोषणा FEATURE_GLXVAL_SHIFT	14
#घोषणा FEATURE_GLXVAL_MASK	(0x03ULL << FEATURE_GLXVAL_SHIFT)

/* Note:
 * The current driver only support 16-bit PASID.
 * Currently, hardware only implement upto 16-bit PASID
 * even though the spec says it could have upto 20 bits.
 */
#घोषणा PASID_MASK		0x0000ffff

/* MMIO status bits */
#घोषणा MMIO_STATUS_EVT_INT_MASK	(1 << 1)
#घोषणा MMIO_STATUS_COM_WAIT_INT_MASK	(1 << 2)
#घोषणा MMIO_STATUS_PPR_INT_MASK	(1 << 6)
#घोषणा MMIO_STATUS_GALOG_RUN_MASK	(1 << 8)
#घोषणा MMIO_STATUS_GALOG_OVERFLOW_MASK	(1 << 9)
#घोषणा MMIO_STATUS_GALOG_INT_MASK	(1 << 10)

/* event logging स्थिरants */
#घोषणा EVENT_ENTRY_SIZE	0x10
#घोषणा EVENT_TYPE_SHIFT	28
#घोषणा EVENT_TYPE_MASK		0xf
#घोषणा EVENT_TYPE_ILL_DEV	0x1
#घोषणा EVENT_TYPE_IO_FAULT	0x2
#घोषणा EVENT_TYPE_DEV_TAB_ERR	0x3
#घोषणा EVENT_TYPE_PAGE_TAB_ERR	0x4
#घोषणा EVENT_TYPE_ILL_CMD	0x5
#घोषणा EVENT_TYPE_CMD_HARD_ERR	0x6
#घोषणा EVENT_TYPE_IOTLB_INV_TO	0x7
#घोषणा EVENT_TYPE_INV_DEV_REQ	0x8
#घोषणा EVENT_TYPE_INV_PPR_REQ	0x9
#घोषणा EVENT_TYPE_RMP_FAULT	0xd
#घोषणा EVENT_TYPE_RMP_HW_ERR	0xe
#घोषणा EVENT_DEVID_MASK	0xffff
#घोषणा EVENT_DEVID_SHIFT	0
#घोषणा EVENT_DOMID_MASK_LO	0xffff
#घोषणा EVENT_DOMID_MASK_HI	0xf0000
#घोषणा EVENT_FLAGS_MASK	0xfff
#घोषणा EVENT_FLAGS_SHIFT	0x10

/* feature control bits */
#घोषणा CONTROL_IOMMU_EN        0x00ULL
#घोषणा CONTROL_HT_TUN_EN       0x01ULL
#घोषणा CONTROL_EVT_LOG_EN      0x02ULL
#घोषणा CONTROL_EVT_INT_EN      0x03ULL
#घोषणा CONTROL_COMWAIT_EN      0x04ULL
#घोषणा CONTROL_INV_TIMEOUT	0x05ULL
#घोषणा CONTROL_PASSPW_EN       0x08ULL
#घोषणा CONTROL_RESPASSPW_EN    0x09ULL
#घोषणा CONTROL_COHERENT_EN     0x0aULL
#घोषणा CONTROL_ISOC_EN         0x0bULL
#घोषणा CONTROL_CMDBUF_EN       0x0cULL
#घोषणा CONTROL_PPRLOG_EN       0x0dULL
#घोषणा CONTROL_PPRINT_EN       0x0eULL
#घोषणा CONTROL_PPR_EN          0x0fULL
#घोषणा CONTROL_GT_EN           0x10ULL
#घोषणा CONTROL_GA_EN           0x11ULL
#घोषणा CONTROL_GAM_EN          0x19ULL
#घोषणा CONTROL_GALOG_EN        0x1CULL
#घोषणा CONTROL_GAINT_EN        0x1DULL
#घोषणा CONTROL_XT_EN           0x32ULL
#घोषणा CONTROL_INTCAPXT_EN     0x33ULL

#घोषणा CTRL_INV_TO_MASK	(7 << CONTROL_INV_TIMEOUT)
#घोषणा CTRL_INV_TO_NONE	0
#घोषणा CTRL_INV_TO_1MS		1
#घोषणा CTRL_INV_TO_10MS	2
#घोषणा CTRL_INV_TO_100MS	3
#घोषणा CTRL_INV_TO_1S		4
#घोषणा CTRL_INV_TO_10S		5
#घोषणा CTRL_INV_TO_100S	6

/* command specअगरic defines */
#घोषणा CMD_COMPL_WAIT          0x01
#घोषणा CMD_INV_DEV_ENTRY       0x02
#घोषणा CMD_INV_IOMMU_PAGES	0x03
#घोषणा CMD_INV_IOTLB_PAGES	0x04
#घोषणा CMD_INV_IRT		0x05
#घोषणा CMD_COMPLETE_PPR	0x07
#घोषणा CMD_INV_ALL		0x08

#घोषणा CMD_COMPL_WAIT_STORE_MASK	0x01
#घोषणा CMD_COMPL_WAIT_INT_MASK		0x02
#घोषणा CMD_INV_IOMMU_PAGES_SIZE_MASK	0x01
#घोषणा CMD_INV_IOMMU_PAGES_PDE_MASK	0x02
#घोषणा CMD_INV_IOMMU_PAGES_GN_MASK	0x04

#घोषणा PPR_STATUS_MASK			0xf
#घोषणा PPR_STATUS_SHIFT		12

#घोषणा CMD_INV_IOMMU_ALL_PAGES_ADDRESS	0x7fffffffffffffffULL

/* macros and definitions क्रम device table entries */
#घोषणा DEV_ENTRY_VALID         0x00
#घोषणा DEV_ENTRY_TRANSLATION   0x01
#घोषणा DEV_ENTRY_PPR           0x34
#घोषणा DEV_ENTRY_IR            0x3d
#घोषणा DEV_ENTRY_IW            0x3e
#घोषणा DEV_ENTRY_NO_PAGE_FAULT	0x62
#घोषणा DEV_ENTRY_EX            0x67
#घोषणा DEV_ENTRY_SYSMGT1       0x68
#घोषणा DEV_ENTRY_SYSMGT2       0x69
#घोषणा DEV_ENTRY_IRQ_TBL_EN	0x80
#घोषणा DEV_ENTRY_INIT_PASS     0xb8
#घोषणा DEV_ENTRY_EINT_PASS     0xb9
#घोषणा DEV_ENTRY_NMI_PASS      0xba
#घोषणा DEV_ENTRY_LINT0_PASS    0xbe
#घोषणा DEV_ENTRY_LINT1_PASS    0xbf
#घोषणा DEV_ENTRY_MODE_MASK	0x07
#घोषणा DEV_ENTRY_MODE_SHIFT	0x09

#घोषणा MAX_DEV_TABLE_ENTRIES	0xffff

/* स्थिरants to configure the command buffer */
#घोषणा CMD_BUFFER_SIZE    8192
#घोषणा CMD_BUFFER_UNINITIALIZED 1
#घोषणा CMD_BUFFER_ENTRIES 512
#घोषणा MMIO_CMD_SIZE_SHIFT 56
#घोषणा MMIO_CMD_SIZE_512 (0x9ULL << MMIO_CMD_SIZE_SHIFT)

/* स्थिरants क्रम event buffer handling */
#घोषणा EVT_BUFFER_SIZE		8192 /* 512 entries */
#घोषणा EVT_LEN_MASK		(0x9ULL << 56)

/* Constants क्रम PPR Log handling */
#घोषणा PPR_LOG_ENTRIES		512
#घोषणा PPR_LOG_SIZE_SHIFT	56
#घोषणा PPR_LOG_SIZE_512	(0x9ULL << PPR_LOG_SIZE_SHIFT)
#घोषणा PPR_ENTRY_SIZE		16
#घोषणा PPR_LOG_SIZE		(PPR_ENTRY_SIZE * PPR_LOG_ENTRIES)

#घोषणा PPR_REQ_TYPE(x)		(((x) >> 60) & 0xfULL)
#घोषणा PPR_FLAGS(x)		(((x) >> 48) & 0xfffULL)
#घोषणा PPR_DEVID(x)		((x) & 0xffffULL)
#घोषणा PPR_TAG(x)		(((x) >> 32) & 0x3ffULL)
#घोषणा PPR_PASID1(x)		(((x) >> 16) & 0xffffULL)
#घोषणा PPR_PASID2(x)		(((x) >> 42) & 0xfULL)
#घोषणा PPR_PASID(x)		((PPR_PASID2(x) << 16) | PPR_PASID1(x))

#घोषणा PPR_REQ_FAULT		0x01

/* Constants क्रम GA Log handling */
#घोषणा GA_LOG_ENTRIES		512
#घोषणा GA_LOG_SIZE_SHIFT	56
#घोषणा GA_LOG_SIZE_512		(0x8ULL << GA_LOG_SIZE_SHIFT)
#घोषणा GA_ENTRY_SIZE		8
#घोषणा GA_LOG_SIZE		(GA_ENTRY_SIZE * GA_LOG_ENTRIES)

#घोषणा GA_TAG(x)		(u32)(x & 0xffffffffULL)
#घोषणा GA_DEVID(x)		(u16)(((x) >> 32) & 0xffffULL)
#घोषणा GA_REQ_TYPE(x)		(((x) >> 60) & 0xfULL)

#घोषणा GA_GUEST_NR		0x1

#घोषणा IOMMU_IN_ADDR_BIT_SIZE  52
#घोषणा IOMMU_OUT_ADDR_BIT_SIZE 52

/*
 * This biपंचांगap is used to advertise the page sizes our hardware support
 * to the IOMMU core, which will then use this inक्रमmation to split
 * physically contiguous memory regions it is mapping पूर्णांकo page sizes
 * that we support.
 *
 * 512GB Pages are not supported due to a hardware bug
 */
#घोषणा AMD_IOMMU_PGSIZES	((~0xFFFUL) & ~(2ULL << 38))

/* Bit value definition क्रम dte irq remapping fields*/
#घोषणा DTE_IRQ_PHYS_ADDR_MASK	(((1ULL << 45)-1) << 6)
#घोषणा DTE_IRQ_REMAP_INTCTL_MASK	(0x3ULL << 60)
#घोषणा DTE_IRQ_REMAP_INTCTL    (2ULL << 60)
#घोषणा DTE_IRQ_REMAP_ENABLE    1ULL

/*
 * AMD IOMMU hardware only support 512 IRTEs despite
 * the architectural limitation of 2048 entries.
 */
#घोषणा DTE_INTTAB_ALIGNMENT    128
#घोषणा DTE_INTTABLEN_VALUE     9ULL
#घोषणा DTE_INTTABLEN           (DTE_INTTABLEN_VALUE << 1)
#घोषणा DTE_INTTABLEN_MASK      (0xfULL << 1)
#घोषणा MAX_IRQS_PER_TABLE      (1 << DTE_INTTABLEN_VALUE)

#घोषणा PAGE_MODE_NONE    0x00
#घोषणा PAGE_MODE_1_LEVEL 0x01
#घोषणा PAGE_MODE_2_LEVEL 0x02
#घोषणा PAGE_MODE_3_LEVEL 0x03
#घोषणा PAGE_MODE_4_LEVEL 0x04
#घोषणा PAGE_MODE_5_LEVEL 0x05
#घोषणा PAGE_MODE_6_LEVEL 0x06
#घोषणा PAGE_MODE_7_LEVEL 0x07

#घोषणा PM_LEVEL_SHIFT(x)	(12 + ((x) * 9))
#घोषणा PM_LEVEL_SIZE(x)	(((x) < 6) ? \
				  ((1ULL << PM_LEVEL_SHIFT((x))) - 1): \
				   (0xffffffffffffffffULL))
#घोषणा PM_LEVEL_INDEX(x, a)	(((a) >> PM_LEVEL_SHIFT((x))) & 0x1ffULL)
#घोषणा PM_LEVEL_ENC(x)		(((x) << 9) & 0xe00ULL)
#घोषणा PM_LEVEL_PDE(x, a)	((a) | PM_LEVEL_ENC((x)) | \
				 IOMMU_PTE_PR | IOMMU_PTE_IR | IOMMU_PTE_IW)
#घोषणा PM_PTE_LEVEL(pte)	(((pte) >> 9) & 0x7ULL)

#घोषणा PM_MAP_4k		0
#घोषणा PM_ADDR_MASK		0x000ffffffffff000ULL
#घोषणा PM_MAP_MASK(lvl)	(PM_ADDR_MASK & \
				(~((1ULL << (12 + ((lvl) * 9))) - 1)))
#घोषणा PM_ALIGNED(lvl, addr)	((PM_MAP_MASK(lvl) & (addr)) == (addr))

/*
 * Returns the page table level to use क्रम a given page size
 * Pagesize is expected to be a घातer-of-two
 */
#घोषणा PAGE_SIZE_LEVEL(pagesize) \
		((__ffs(pagesize) - 12) / 9)
/*
 * Returns the number of ptes to use क्रम a given page size
 * Pagesize is expected to be a घातer-of-two
 */
#घोषणा PAGE_SIZE_PTE_COUNT(pagesize) \
		(1ULL << ((__ffs(pagesize) - 12) % 9))

/*
 * Aligns a given io-भव address to a given page size
 * Pagesize is expected to be a घातer-of-two
 */
#घोषणा PAGE_SIZE_ALIGN(address, pagesize) \
		((address) & ~((pagesize) - 1))
/*
 * Creates an IOMMU PTE क्रम an address and a given pagesize
 * The PTE has no permission bits set
 * Pagesize is expected to be a घातer-of-two larger than 4096
 */
#घोषणा PAGE_SIZE_PTE(address, pagesize)		\
		(((address) | ((pagesize) - 1)) &	\
		 (~(pagesize >> 1)) & PM_ADDR_MASK)

/*
 * Takes a PTE value with mode=0x07 and वापसs the page size it maps
 */
#घोषणा PTE_PAGE_SIZE(pte) \
	(1ULL << (1 + ffz(((pte) | 0xfffULL))))

/*
 * Takes a page-table level and वापसs the शेष page-size क्रम this level
 */
#घोषणा PTE_LEVEL_PAGE_SIZE(level)			\
	(1ULL << (12 + (9 * (level))))

/*
 * Bit value definition क्रम I/O PTE fields
 */
#घोषणा IOMMU_PTE_PR (1ULL << 0)
#घोषणा IOMMU_PTE_U  (1ULL << 59)
#घोषणा IOMMU_PTE_FC (1ULL << 60)
#घोषणा IOMMU_PTE_IR (1ULL << 61)
#घोषणा IOMMU_PTE_IW (1ULL << 62)

/*
 * Bit value definition क्रम DTE fields
 */
#घोषणा DTE_FLAG_V  (1ULL << 0)
#घोषणा DTE_FLAG_TV (1ULL << 1)
#घोषणा DTE_FLAG_IR (1ULL << 61)
#घोषणा DTE_FLAG_IW (1ULL << 62)

#घोषणा DTE_FLAG_IOTLB	(1ULL << 32)
#घोषणा DTE_FLAG_GV	(1ULL << 55)
#घोषणा DTE_FLAG_MASK	(0x3ffULL << 32)
#घोषणा DTE_GLX_SHIFT	(56)
#घोषणा DTE_GLX_MASK	(3)
#घोषणा DEV_DOMID_MASK	0xffffULL

#घोषणा DTE_GCR3_VAL_A(x)	(((x) >> 12) & 0x00007ULL)
#घोषणा DTE_GCR3_VAL_B(x)	(((x) >> 15) & 0x0ffffULL)
#घोषणा DTE_GCR3_VAL_C(x)	(((x) >> 31) & 0x1fffffULL)

#घोषणा DTE_GCR3_INDEX_A	0
#घोषणा DTE_GCR3_INDEX_B	1
#घोषणा DTE_GCR3_INDEX_C	1

#घोषणा DTE_GCR3_SHIFT_A	58
#घोषणा DTE_GCR3_SHIFT_B	16
#घोषणा DTE_GCR3_SHIFT_C	43

#घोषणा GCR3_VALID		0x01ULL

#घोषणा IOMMU_PAGE_MASK (((1ULL << 52) - 1) & ~0xfffULL)
#घोषणा IOMMU_PTE_PRESENT(pte) ((pte) & IOMMU_PTE_PR)
#घोषणा IOMMU_PTE_PAGE(pte) (iommu_phys_to_virt((pte) & IOMMU_PAGE_MASK))
#घोषणा IOMMU_PTE_MODE(pte) (((pte) >> 9) & 0x07)

#घोषणा IOMMU_PROT_MASK 0x03
#घोषणा IOMMU_PROT_IR 0x01
#घोषणा IOMMU_PROT_IW 0x02

#घोषणा IOMMU_UNITY_MAP_FLAG_EXCL_RANGE	(1 << 2)

/* IOMMU capabilities */
#घोषणा IOMMU_CAP_IOTLB   24
#घोषणा IOMMU_CAP_NPCACHE 26
#घोषणा IOMMU_CAP_EFR     27

/* IOMMU IVINFO */
#घोषणा IOMMU_IVINFO_OFFSET     36
#घोषणा IOMMU_IVINFO_EFRSUP     BIT(0)

/* IOMMU Feature Reporting Field (क्रम IVHD type 10h */
#घोषणा IOMMU_FEAT_GASUP_SHIFT	6

/* IOMMU Extended Feature Register (EFR) */
#घोषणा IOMMU_EFR_XTSUP_SHIFT	2
#घोषणा IOMMU_EFR_GASUP_SHIFT	7
#घोषणा IOMMU_EFR_MSICAPMMIOSUP_SHIFT	46

#घोषणा MAX_DOMAIN_ID 65536

/* Protection करोमुख्य flags */
#घोषणा PD_DMA_OPS_MASK		(1UL << 0) /* करोमुख्य used क्रम dma_ops */
#घोषणा PD_DEFAULT_MASK		(1UL << 1) /* करोमुख्य is a शेष dma_ops
					      करोमुख्य क्रम an IOMMU */
#घोषणा PD_PASSTHROUGH_MASK	(1UL << 2) /* करोमुख्य has no page
					      translation */
#घोषणा PD_IOMMUV2_MASK		(1UL << 3) /* करोमुख्य has gcr3 table */

बाह्य bool amd_iommu_dump;
#घोषणा DUMP_prपूर्णांकk(क्रमmat, arg...)				\
	करो अणु							\
		अगर (amd_iommu_dump)				\
			pr_info("AMD-Vi: " क्रमmat, ## arg);	\
	पूर्ण जबतक(0);

/* global flag अगर IOMMUs cache non-present entries */
बाह्य bool amd_iommu_np_cache;
/* Only true अगर all IOMMUs support device IOTLBs */
बाह्य bool amd_iommu_iotlb_sup;

काष्ठा irq_remap_table अणु
	raw_spinlock_t lock;
	अचिन्हित min_index;
	u32 *table;
पूर्ण;

बाह्य काष्ठा irq_remap_table **irq_lookup_table;

/* Interrupt remapping feature used? */
बाह्य bool amd_iommu_irq_remap;

/* kmem_cache to get tables with 128 byte alignement */
बाह्य काष्ठा kmem_cache *amd_iommu_irq_cache;

/*
 * Make iterating over all IOMMUs easier
 */
#घोषणा क्रम_each_iommu(iommu) \
	list_क्रम_each_entry((iommu), &amd_iommu_list, list)
#घोषणा क्रम_each_iommu_safe(iommu, next) \
	list_क्रम_each_entry_safe((iommu), (next), &amd_iommu_list, list)

#घोषणा APERTURE_RANGE_SHIFT	27	/* 128 MB */
#घोषणा APERTURE_RANGE_SIZE	(1ULL << APERTURE_RANGE_SHIFT)
#घोषणा APERTURE_RANGE_PAGES	(APERTURE_RANGE_SIZE >> PAGE_SHIFT)
#घोषणा APERTURE_MAX_RANGES	32	/* allows 4GB of DMA address space */
#घोषणा APERTURE_RANGE_INDEX(a)	((a) >> APERTURE_RANGE_SHIFT)
#घोषणा APERTURE_PAGE_INDEX(a)	(((a) >> 21) & 0x3fULL)

/*
 * This काष्ठा is used to pass inक्रमmation about
 * incoming PPR faults around.
 */
काष्ठा amd_iommu_fault अणु
	u64 address;    /* IO भव address of the fault*/
	u32 pasid;      /* Address space identअगरier */
	u16 device_id;  /* Originating PCI device id */
	u16 tag;        /* PPR tag */
	u16 flags;      /* Fault flags */

पूर्ण;


काष्ठा iommu_करोमुख्य;
काष्ठा irq_करोमुख्य;
काष्ठा amd_irte_ops;

#घोषणा AMD_IOMMU_FLAG_TRANS_PRE_ENABLED      (1 << 0)

#घोषणा io_pgtable_to_data(x) \
	container_of((x), काष्ठा amd_io_pgtable, iop)

#घोषणा io_pgtable_ops_to_data(x) \
	io_pgtable_to_data(io_pgtable_ops_to_pgtable(x))

#घोषणा io_pgtable_ops_to_करोमुख्य(x) \
	container_of(io_pgtable_ops_to_data(x), \
		     काष्ठा protection_करोमुख्य, iop)

#घोषणा io_pgtable_cfg_to_data(x) \
	container_of((x), काष्ठा amd_io_pgtable, pgtbl_cfg)

काष्ठा amd_io_pgtable अणु
	काष्ठा io_pgtable_cfg	pgtbl_cfg;
	काष्ठा io_pgtable	iop;
	पूर्णांक			mode;
	u64			*root;
	atomic64_t		pt_root;    /* pgtable root and pgtable mode */
पूर्ण;

/*
 * This काष्ठाure contains generic data क्रम  IOMMU protection करोमुख्यs
 * independent of their use.
 */
काष्ठा protection_करोमुख्य अणु
	काष्ठा list_head dev_list; /* List of all devices in this करोमुख्य */
	काष्ठा iommu_करोमुख्य करोमुख्य; /* generic करोमुख्य handle used by
				       iommu core code */
	काष्ठा amd_io_pgtable iop;
	spinlock_t lock;	/* mostly used to lock the page table*/
	u16 id;			/* the करोमुख्य id written to the device table */
	पूर्णांक glx;		/* Number of levels क्रम GCR3 table */
	u64 *gcr3_tbl;		/* Guest CR3 table */
	अचिन्हित दीर्घ flags;	/* flags to find out type of करोमुख्य */
	अचिन्हित dev_cnt;	/* devices asचिन्हित to this करोमुख्य */
	अचिन्हित dev_iommu[MAX_IOMMUS]; /* per-IOMMU reference count */
पूर्ण;

/*
 * Structure where we save inक्रमmation about one hardware AMD IOMMU in the
 * प्रणाली.
 */
काष्ठा amd_iommu अणु
	काष्ठा list_head list;

	/* Index within the IOMMU array */
	पूर्णांक index;

	/* locks the accesses to the hardware */
	raw_spinlock_t lock;

	/* Poपूर्णांकer to PCI device of this IOMMU */
	काष्ठा pci_dev *dev;

	/* Cache pdev to root device क्रम resume quirks */
	काष्ठा pci_dev *root_pdev;

	/* physical address of MMIO space */
	u64 mmio_phys;

	/* physical end address of MMIO space */
	u64 mmio_phys_end;

	/* भव address of MMIO space */
	u8 __iomem *mmio_base;

	/* capabilities of that IOMMU पढ़ो from ACPI */
	u32 cap;

	/* flags पढ़ो from acpi table */
	u8 acpi_flags;

	/* Extended features */
	u64 features;

	/* IOMMUv2 */
	bool is_iommu_v2;

	/* PCI device id of the IOMMU device */
	u16 devid;

	/*
	 * Capability poपूर्णांकer. There could be more than one IOMMU per PCI
	 * device function अगर there are more than one AMD IOMMU capability
	 * poपूर्णांकers.
	 */
	u16 cap_ptr;

	/* pci करोमुख्य of this IOMMU */
	u16 pci_seg;

	/* start of exclusion range of that IOMMU */
	u64 exclusion_start;
	/* length of exclusion range of that IOMMU */
	u64 exclusion_length;

	/* command buffer भव address */
	u8 *cmd_buf;
	u32 cmd_buf_head;
	u32 cmd_buf_tail;

	/* event buffer भव address */
	u8 *evt_buf;

	/* Base of the PPR log, अगर present */
	u8 *ppr_log;

	/* Base of the GA log, अगर present */
	u8 *ga_log;

	/* Tail of the GA log, अगर present */
	u8 *ga_log_tail;

	/* true अगर पूर्णांकerrupts क्रम this IOMMU are alपढ़ोy enabled */
	bool पूर्णांक_enabled;

	/* अगर one, we need to send a completion रुको command */
	bool need_sync;

	/* Handle क्रम IOMMU core code */
	काष्ठा iommu_device iommu;

	/*
	 * We can't rely on the BIOS to restore all values on reinit, so we
	 * need to stash them
	 */

	/* The iommu BAR */
	u32 stored_addr_lo;
	u32 stored_addr_hi;

	/*
	 * Each iommu has 6 l1s, each of which is करोcumented as having 0x12
	 * रेजिस्टरs
	 */
	u32 stored_l1[6][0x12];

	/* The l2 indirect रेजिस्टरs */
	u32 stored_l2[0x83];

	/* The maximum PC banks and counters/bank (PCSup=1) */
	u8 max_banks;
	u8 max_counters;
#अगर_घोषित CONFIG_IRQ_REMAP
	काष्ठा irq_करोमुख्य *ir_करोमुख्य;
	काष्ठा irq_करोमुख्य *msi_करोमुख्य;

	काष्ठा amd_irte_ops *irte_ops;
#पूर्ण_अगर

	u32 flags;
	अस्थिर u64 *cmd_sem;
	u64 cmd_sem_val;

#अगर_घोषित CONFIG_AMD_IOMMU_DEBUGFS
	/* DebugFS Info */
	काष्ठा dentry *debugfs;
#पूर्ण_अगर
	/* IRQ notअगरier क्रम IntCapXT पूर्णांकerrupt */
	काष्ठा irq_affinity_notअगरy पूर्णांकcapxt_notअगरy;
पूर्ण;

अटल अंतरभूत काष्ठा amd_iommu *dev_to_amd_iommu(काष्ठा device *dev)
अणु
	काष्ठा iommu_device *iommu = dev_to_iommu_device(dev);

	वापस container_of(iommu, काष्ठा amd_iommu, iommu);
पूर्ण

#घोषणा ACPIHID_UID_LEN 256
#घोषणा ACPIHID_HID_LEN 9

काष्ठा acpihid_map_entry अणु
	काष्ठा list_head list;
	u8 uid[ACPIHID_UID_LEN];
	u8 hid[ACPIHID_HID_LEN];
	u16 devid;
	u16 root_devid;
	bool cmd_line;
	काष्ठा iommu_group *group;
पूर्ण;

काष्ठा devid_map अणु
	काष्ठा list_head list;
	u8 id;
	u16 devid;
	bool cmd_line;
पूर्ण;

/*
 * This काष्ठा contains device specअगरic data क्रम the IOMMU
 */
काष्ठा iommu_dev_data अणु
	/*Protect against attach/detach races */
	spinlock_t lock;

	काष्ठा list_head list;		  /* For करोमुख्य->dev_list */
	काष्ठा llist_node dev_data_list;  /* For global dev_data_list */
	काष्ठा protection_करोमुख्य *करोमुख्य; /* Doमुख्य the device is bound to */
	काष्ठा pci_dev *pdev;
	u16 devid;			  /* PCI Device ID */
	bool iommu_v2;			  /* Device can make use of IOMMUv2 */
	काष्ठा अणु
		bool enabled;
		पूर्णांक qdep;
	पूर्ण ats;				  /* ATS state */
	bool pri_tlp;			  /* PASID TLB required क्रम
					     PPR completions */
	bool use_vapic;			  /* Enable device to use vapic mode */
	bool defer_attach;

	काष्ठा ratelimit_state rs;        /* Ratelimit IOPF messages */
पूर्ण;

/* Map HPET and IOAPIC ids to the devid used by the IOMMU */
बाह्य काष्ठा list_head ioapic_map;
बाह्य काष्ठा list_head hpet_map;
बाह्य काष्ठा list_head acpihid_map;

/*
 * List with all IOMMUs in the प्रणाली. This list is not locked because it is
 * only written and पढ़ो at driver initialization or suspend समय
 */
बाह्य काष्ठा list_head amd_iommu_list;

/*
 * Array with poपूर्णांकers to each IOMMU काष्ठा
 * The indices are referenced in the protection करोमुख्यs
 */
बाह्य काष्ठा amd_iommu *amd_iommus[MAX_IOMMUS];

/*
 * Structure defining one entry in the device table
 */
काष्ठा dev_table_entry अणु
	u64 data[4];
पूर्ण;

/*
 * One entry क्रम unity mappings parsed out of the ACPI table.
 */
काष्ठा unity_map_entry अणु
	काष्ठा list_head list;

	/* starting device id this entry is used क्रम (including) */
	u16 devid_start;
	/* end device id this entry is used क्रम (including) */
	u16 devid_end;

	/* start address to unity map (including) */
	u64 address_start;
	/* end address to unity map (including) */
	u64 address_end;

	/* required protection */
	पूर्णांक prot;
पूर्ण;

/*
 * List of all unity mappings. It is not locked because as runसमय it is only
 * पढ़ो. It is created at ACPI table parsing समय.
 */
बाह्य काष्ठा list_head amd_iommu_unity_map;

/*
 * Data काष्ठाures क्रम device handling
 */

/*
 * Device table used by hardware. Read and ग_लिखो accesses by software are
 * locked with the amd_iommu_pd_table lock.
 */
बाह्य काष्ठा dev_table_entry *amd_iommu_dev_table;

/*
 * Alias table to find requestor ids to device ids. Not locked because only
 * पढ़ो on runसमय.
 */
बाह्य u16 *amd_iommu_alias_table;

/*
 * Reverse lookup table to find the IOMMU which translates a specअगरic device.
 */
बाह्य काष्ठा amd_iommu **amd_iommu_rlookup_table;

/* size of the dma_ops aperture as घातer of 2 */
बाह्य अचिन्हित amd_iommu_aperture_order;

/* largest PCI device id we expect translation requests क्रम */
बाह्य u16 amd_iommu_last_bdf;

/* allocation biपंचांगap क्रम करोमुख्य ids */
बाह्य अचिन्हित दीर्घ *amd_iommu_pd_alloc_biपंचांगap;

/*
 * If true, the addresses will be flushed on unmap समय, not when
 * they are reused
 */
बाह्य bool amd_iommu_unmap_flush;

/* Smallest max PASID supported by any IOMMU in the प्रणाली */
बाह्य u32 amd_iommu_max_pasid;

बाह्य bool amd_iommu_v2_present;

बाह्य bool amd_iommu_क्रमce_isolation;

/* Max levels of glxval supported */
बाह्य पूर्णांक amd_iommu_max_glx_val;

/*
 * This function flushes all पूर्णांकernal caches of
 * the IOMMU used by this driver.
 */
बाह्य व्योम iommu_flush_all_caches(काष्ठा amd_iommu *iommu);

अटल अंतरभूत पूर्णांक get_ioapic_devid(पूर्णांक id)
अणु
	काष्ठा devid_map *entry;

	list_क्रम_each_entry(entry, &ioapic_map, list) अणु
		अगर (entry->id == id)
			वापस entry->devid;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक get_hpet_devid(पूर्णांक id)
अणु
	काष्ठा devid_map *entry;

	list_क्रम_each_entry(entry, &hpet_map, list) अणु
		अगर (entry->id == id)
			वापस entry->devid;
	पूर्ण

	वापस -EINVAL;
पूर्ण

क्रमागत amd_iommu_पूर्णांकr_mode_type अणु
	AMD_IOMMU_GUEST_IR_LEGACY,

	/* This mode is not visible to users. It is used when
	 * we cannot fully enable vAPIC and fallback to only support
	 * legacy पूर्णांकerrupt remapping via 128-bit IRTE.
	 */
	AMD_IOMMU_GUEST_IR_LEGACY_GA,
	AMD_IOMMU_GUEST_IR_VAPIC,
पूर्ण;

#घोषणा AMD_IOMMU_GUEST_IR_GA(x)	(x == AMD_IOMMU_GUEST_IR_VAPIC || \
					 x == AMD_IOMMU_GUEST_IR_LEGACY_GA)

#घोषणा AMD_IOMMU_GUEST_IR_VAPIC(x)	(x == AMD_IOMMU_GUEST_IR_VAPIC)

जोड़ irte अणु
	u32 val;
	काष्ठा अणु
		u32 valid	: 1,
		    no_fault	: 1,
		    पूर्णांक_type	: 3,
		    rq_eoi	: 1,
		    dm		: 1,
		    rsvd_1	: 1,
		    destination	: 8,
		    vector	: 8,
		    rsvd_2	: 8;
	पूर्ण fields;
पूर्ण;

#घोषणा APICID_TO_IRTE_DEST_LO(x)    (x & 0xffffff)
#घोषणा APICID_TO_IRTE_DEST_HI(x)    ((x >> 24) & 0xff)

जोड़ irte_ga_lo अणु
	u64 val;

	/* For पूर्णांक remapping */
	काष्ठा अणु
		u64 valid	: 1,
		    no_fault	: 1,
		    /* ------ */
		    पूर्णांक_type	: 3,
		    rq_eoi	: 1,
		    dm		: 1,
		    /* ------ */
		    guest_mode	: 1,
		    destination	: 24,
		    ga_tag	: 32;
	पूर्ण fields_remap;

	/* For guest vAPIC */
	काष्ठा अणु
		u64 valid	: 1,
		    no_fault	: 1,
		    /* ------ */
		    ga_log_पूर्णांकr	: 1,
		    rsvd1	: 3,
		    is_run	: 1,
		    /* ------ */
		    guest_mode	: 1,
		    destination	: 24,
		    ga_tag	: 32;
	पूर्ण fields_vapic;
पूर्ण;

जोड़ irte_ga_hi अणु
	u64 val;
	काष्ठा अणु
		u64 vector	: 8,
		    rsvd_1	: 4,
		    ga_root_ptr	: 40,
		    rsvd_2	: 4,
		    destination : 8;
	पूर्ण fields;
पूर्ण;

काष्ठा irte_ga अणु
	जोड़ irte_ga_lo lo;
	जोड़ irte_ga_hi hi;
पूर्ण;

काष्ठा irq_2_irte अणु
	u16 devid; /* Device ID क्रम IRTE table */
	u16 index; /* Index पूर्णांकo IRTE table*/
पूर्ण;

काष्ठा amd_ir_data अणु
	u32 cached_ga_tag;
	काष्ठा irq_2_irte irq_2_irte;
	काष्ठा msi_msg msi_entry;
	व्योम *entry;    /* Poपूर्णांकer to जोड़ irte or काष्ठा irte_ga */
	व्योम *ref;      /* Poपूर्णांकer to the actual irte */

	/**
	 * Store inक्रमmation क्रम activate/de-activate
	 * Guest भव APIC mode during runसमय.
	 */
	काष्ठा irq_cfg *cfg;
	पूर्णांक ga_vector;
	पूर्णांक ga_root_ptr;
	पूर्णांक ga_tag;
पूर्ण;

काष्ठा amd_irte_ops अणु
	व्योम (*prepare)(व्योम *, u32, bool, u8, u32, पूर्णांक);
	व्योम (*activate)(व्योम *, u16, u16);
	व्योम (*deactivate)(व्योम *, u16, u16);
	व्योम (*set_affinity)(व्योम *, u16, u16, u8, u32);
	व्योम *(*get)(काष्ठा irq_remap_table *, पूर्णांक);
	व्योम (*set_allocated)(काष्ठा irq_remap_table *, पूर्णांक);
	bool (*is_allocated)(काष्ठा irq_remap_table *, पूर्णांक);
	व्योम (*clear_allocated)(काष्ठा irq_remap_table *, पूर्णांक);
पूर्ण;

#अगर_घोषित CONFIG_IRQ_REMAP
बाह्य काष्ठा amd_irte_ops irte_32_ops;
बाह्य काष्ठा amd_irte_ops irte_128_ops;
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_AMD_IOMMU_TYPES_H */
