<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * IOMMU API क्रम ARM architected SMMU implementations.
 *
 * Copyright (C) 2013 ARM Limited
 *
 * Author: Will Deacon <will.deacon@arm.com>
 */

#अगर_अघोषित _ARM_SMMU_H
#घोषणा _ARM_SMMU_H

#समावेश <linux/atomic.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/io-64-nonatomic-hi-lo.h>
#समावेश <linux/io-pgtable.h>
#समावेश <linux/iommu.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

/* Configuration रेजिस्टरs */
#घोषणा ARM_SMMU_GR0_sCR0		0x0
#घोषणा ARM_SMMU_sCR0_VMID16EN		BIT(31)
#घोषणा ARM_SMMU_sCR0_BSU		GENMASK(15, 14)
#घोषणा ARM_SMMU_sCR0_FB		BIT(13)
#घोषणा ARM_SMMU_sCR0_PTM		BIT(12)
#घोषणा ARM_SMMU_sCR0_VMIDPNE		BIT(11)
#घोषणा ARM_SMMU_sCR0_USFCFG		BIT(10)
#घोषणा ARM_SMMU_sCR0_GCFGFIE		BIT(5)
#घोषणा ARM_SMMU_sCR0_GCFGFRE		BIT(4)
#घोषणा ARM_SMMU_sCR0_EXIDENABLE	BIT(3)
#घोषणा ARM_SMMU_sCR0_GFIE		BIT(2)
#घोषणा ARM_SMMU_sCR0_GFRE		BIT(1)
#घोषणा ARM_SMMU_sCR0_CLIENTPD		BIT(0)

/* Auxiliary Configuration रेजिस्टर */
#घोषणा ARM_SMMU_GR0_sACR		0x10

/* Identअगरication रेजिस्टरs */
#घोषणा ARM_SMMU_GR0_ID0		0x20
#घोषणा ARM_SMMU_ID0_S1TS		BIT(30)
#घोषणा ARM_SMMU_ID0_S2TS		BIT(29)
#घोषणा ARM_SMMU_ID0_NTS		BIT(28)
#घोषणा ARM_SMMU_ID0_SMS		BIT(27)
#घोषणा ARM_SMMU_ID0_ATOSNS		BIT(26)
#घोषणा ARM_SMMU_ID0_PTFS_NO_AARCH32	BIT(25)
#घोषणा ARM_SMMU_ID0_PTFS_NO_AARCH32S	BIT(24)
#घोषणा ARM_SMMU_ID0_NUMIRPT		GENMASK(23, 16)
#घोषणा ARM_SMMU_ID0_CTTW		BIT(14)
#घोषणा ARM_SMMU_ID0_NUMSIDB		GENMASK(12, 9)
#घोषणा ARM_SMMU_ID0_EXIDS		BIT(8)
#घोषणा ARM_SMMU_ID0_NUMSMRG		GENMASK(7, 0)

#घोषणा ARM_SMMU_GR0_ID1		0x24
#घोषणा ARM_SMMU_ID1_PAGESIZE		BIT(31)
#घोषणा ARM_SMMU_ID1_NUMPAGENDXB	GENMASK(30, 28)
#घोषणा ARM_SMMU_ID1_NUMS2CB		GENMASK(23, 16)
#घोषणा ARM_SMMU_ID1_NUMCB		GENMASK(7, 0)

#घोषणा ARM_SMMU_GR0_ID2		0x28
#घोषणा ARM_SMMU_ID2_VMID16		BIT(15)
#घोषणा ARM_SMMU_ID2_PTFS_64K		BIT(14)
#घोषणा ARM_SMMU_ID2_PTFS_16K		BIT(13)
#घोषणा ARM_SMMU_ID2_PTFS_4K		BIT(12)
#घोषणा ARM_SMMU_ID2_UBS		GENMASK(11, 8)
#घोषणा ARM_SMMU_ID2_OAS		GENMASK(7, 4)
#घोषणा ARM_SMMU_ID2_IAS		GENMASK(3, 0)

#घोषणा ARM_SMMU_GR0_ID3		0x2c
#घोषणा ARM_SMMU_GR0_ID4		0x30
#घोषणा ARM_SMMU_GR0_ID5		0x34
#घोषणा ARM_SMMU_GR0_ID6		0x38

#घोषणा ARM_SMMU_GR0_ID7		0x3c
#घोषणा ARM_SMMU_ID7_MAJOR		GENMASK(7, 4)
#घोषणा ARM_SMMU_ID7_MINOR		GENMASK(3, 0)

#घोषणा ARM_SMMU_GR0_sGFSR		0x48
#घोषणा ARM_SMMU_sGFSR_USF		BIT(1)

#घोषणा ARM_SMMU_GR0_sGFSYNR0		0x50
#घोषणा ARM_SMMU_GR0_sGFSYNR1		0x54
#घोषणा ARM_SMMU_GR0_sGFSYNR2		0x58

/* Global TLB invalidation */
#घोषणा ARM_SMMU_GR0_TLBIVMID		0x64
#घोषणा ARM_SMMU_GR0_TLBIALLNSNH	0x68
#घोषणा ARM_SMMU_GR0_TLBIALLH		0x6c
#घोषणा ARM_SMMU_GR0_sTLBGSYNC		0x70

#घोषणा ARM_SMMU_GR0_sTLBGSTATUS	0x74
#घोषणा ARM_SMMU_sTLBGSTATUS_GSACTIVE	BIT(0)

/* Stream mapping रेजिस्टरs */
#घोषणा ARM_SMMU_GR0_SMR(n)		(0x800 + ((n) << 2))
#घोषणा ARM_SMMU_SMR_VALID		BIT(31)
#घोषणा ARM_SMMU_SMR_MASK		GENMASK(31, 16)
#घोषणा ARM_SMMU_SMR_ID			GENMASK(15, 0)

#घोषणा ARM_SMMU_GR0_S2CR(n)		(0xc00 + ((n) << 2))
#घोषणा ARM_SMMU_S2CR_PRIVCFG		GENMASK(25, 24)
क्रमागत arm_smmu_s2cr_privcfg अणु
	S2CR_PRIVCFG_DEFAULT,
	S2CR_PRIVCFG_DIPAN,
	S2CR_PRIVCFG_UNPRIV,
	S2CR_PRIVCFG_PRIV,
पूर्ण;
#घोषणा ARM_SMMU_S2CR_TYPE		GENMASK(17, 16)
क्रमागत arm_smmu_s2cr_type अणु
	S2CR_TYPE_TRANS,
	S2CR_TYPE_BYPASS,
	S2CR_TYPE_FAULT,
पूर्ण;
#घोषणा ARM_SMMU_S2CR_EXIDVALID		BIT(10)
#घोषणा ARM_SMMU_S2CR_CBNDX		GENMASK(7, 0)

/* Context bank attribute रेजिस्टरs */
#घोषणा ARM_SMMU_GR1_CBAR(n)		(0x0 + ((n) << 2))
#घोषणा ARM_SMMU_CBAR_IRPTNDX		GENMASK(31, 24)
#घोषणा ARM_SMMU_CBAR_TYPE		GENMASK(17, 16)
क्रमागत arm_smmu_cbar_type अणु
	CBAR_TYPE_S2_TRANS,
	CBAR_TYPE_S1_TRANS_S2_BYPASS,
	CBAR_TYPE_S1_TRANS_S2_FAULT,
	CBAR_TYPE_S1_TRANS_S2_TRANS,
पूर्ण;
#घोषणा ARM_SMMU_CBAR_S1_MEMATTR	GENMASK(15, 12)
#घोषणा ARM_SMMU_CBAR_S1_MEMATTR_WB	0xf
#घोषणा ARM_SMMU_CBAR_S1_BPSHCFG	GENMASK(9, 8)
#घोषणा ARM_SMMU_CBAR_S1_BPSHCFG_NSH	3
#घोषणा ARM_SMMU_CBAR_VMID		GENMASK(7, 0)

#घोषणा ARM_SMMU_GR1_CBFRSYNRA(n)	(0x400 + ((n) << 2))

#घोषणा ARM_SMMU_GR1_CBA2R(n)		(0x800 + ((n) << 2))
#घोषणा ARM_SMMU_CBA2R_VMID16		GENMASK(31, 16)
#घोषणा ARM_SMMU_CBA2R_VA64		BIT(0)

#घोषणा ARM_SMMU_CB_SCTLR		0x0
#घोषणा ARM_SMMU_SCTLR_S1_ASIDPNE	BIT(12)
#घोषणा ARM_SMMU_SCTLR_CFCFG		BIT(7)
#घोषणा ARM_SMMU_SCTLR_HUPCF		BIT(8)
#घोषणा ARM_SMMU_SCTLR_CFIE		BIT(6)
#घोषणा ARM_SMMU_SCTLR_CFRE		BIT(5)
#घोषणा ARM_SMMU_SCTLR_E		BIT(4)
#घोषणा ARM_SMMU_SCTLR_AFE		BIT(2)
#घोषणा ARM_SMMU_SCTLR_TRE		BIT(1)
#घोषणा ARM_SMMU_SCTLR_M		BIT(0)

#घोषणा ARM_SMMU_CB_ACTLR		0x4

#घोषणा ARM_SMMU_CB_RESUME		0x8
#घोषणा ARM_SMMU_RESUME_TERMINATE	BIT(0)

#घोषणा ARM_SMMU_CB_TCR2		0x10
#घोषणा ARM_SMMU_TCR2_SEP		GENMASK(17, 15)
#घोषणा ARM_SMMU_TCR2_SEP_UPSTREAM	0x7
#घोषणा ARM_SMMU_TCR2_AS		BIT(4)
#घोषणा ARM_SMMU_TCR2_PASIZE		GENMASK(3, 0)

#घोषणा ARM_SMMU_CB_TTBR0		0x20
#घोषणा ARM_SMMU_CB_TTBR1		0x28
#घोषणा ARM_SMMU_TTBRn_ASID		GENMASK_ULL(63, 48)

#घोषणा ARM_SMMU_CB_TCR			0x30
#घोषणा ARM_SMMU_TCR_EAE		BIT(31)
#घोषणा ARM_SMMU_TCR_EPD1		BIT(23)
#घोषणा ARM_SMMU_TCR_A1			BIT(22)
#घोषणा ARM_SMMU_TCR_TG0		GENMASK(15, 14)
#घोषणा ARM_SMMU_TCR_SH0		GENMASK(13, 12)
#घोषणा ARM_SMMU_TCR_ORGN0		GENMASK(11, 10)
#घोषणा ARM_SMMU_TCR_IRGN0		GENMASK(9, 8)
#घोषणा ARM_SMMU_TCR_EPD0		BIT(7)
#घोषणा ARM_SMMU_TCR_T0SZ		GENMASK(5, 0)

#घोषणा ARM_SMMU_VTCR_RES1		BIT(31)
#घोषणा ARM_SMMU_VTCR_PS		GENMASK(18, 16)
#घोषणा ARM_SMMU_VTCR_TG0		ARM_SMMU_TCR_TG0
#घोषणा ARM_SMMU_VTCR_SH0		ARM_SMMU_TCR_SH0
#घोषणा ARM_SMMU_VTCR_ORGN0		ARM_SMMU_TCR_ORGN0
#घोषणा ARM_SMMU_VTCR_IRGN0		ARM_SMMU_TCR_IRGN0
#घोषणा ARM_SMMU_VTCR_SL0		GENMASK(7, 6)
#घोषणा ARM_SMMU_VTCR_T0SZ		ARM_SMMU_TCR_T0SZ

#घोषणा ARM_SMMU_CB_CONTEXTIDR		0x34
#घोषणा ARM_SMMU_CB_S1_MAIR0		0x38
#घोषणा ARM_SMMU_CB_S1_MAIR1		0x3c

#घोषणा ARM_SMMU_CB_PAR			0x50
#घोषणा ARM_SMMU_CB_PAR_F		BIT(0)

#घोषणा ARM_SMMU_CB_FSR			0x58
#घोषणा ARM_SMMU_FSR_MULTI		BIT(31)
#घोषणा ARM_SMMU_FSR_SS			BIT(30)
#घोषणा ARM_SMMU_FSR_UUT		BIT(8)
#घोषणा ARM_SMMU_FSR_ASF		BIT(7)
#घोषणा ARM_SMMU_FSR_TLBLKF		BIT(6)
#घोषणा ARM_SMMU_FSR_TLBMCF		BIT(5)
#घोषणा ARM_SMMU_FSR_EF			BIT(4)
#घोषणा ARM_SMMU_FSR_PF			BIT(3)
#घोषणा ARM_SMMU_FSR_AFF		BIT(2)
#घोषणा ARM_SMMU_FSR_TF			BIT(1)

#घोषणा ARM_SMMU_FSR_IGN		(ARM_SMMU_FSR_AFF |		\
					 ARM_SMMU_FSR_ASF |		\
					 ARM_SMMU_FSR_TLBMCF |		\
					 ARM_SMMU_FSR_TLBLKF)

#घोषणा ARM_SMMU_FSR_FAULT		(ARM_SMMU_FSR_MULTI |		\
					 ARM_SMMU_FSR_SS |		\
					 ARM_SMMU_FSR_UUT |		\
					 ARM_SMMU_FSR_EF |		\
					 ARM_SMMU_FSR_PF |		\
					 ARM_SMMU_FSR_TF |		\
					 ARM_SMMU_FSR_IGN)

#घोषणा ARM_SMMU_CB_FAR			0x60

#घोषणा ARM_SMMU_CB_FSYNR0		0x68
#घोषणा ARM_SMMU_FSYNR0_WNR		BIT(4)

#घोषणा ARM_SMMU_CB_S1_TLBIVA		0x600
#घोषणा ARM_SMMU_CB_S1_TLBIASID		0x610
#घोषणा ARM_SMMU_CB_S1_TLBIVAL		0x620
#घोषणा ARM_SMMU_CB_S2_TLBIIPAS2	0x630
#घोषणा ARM_SMMU_CB_S2_TLBIIPAS2L	0x638
#घोषणा ARM_SMMU_CB_TLBSYNC		0x7f0
#घोषणा ARM_SMMU_CB_TLBSTATUS		0x7f4
#घोषणा ARM_SMMU_CB_ATS1PR		0x800

#घोषणा ARM_SMMU_CB_ATSR		0x8f0
#घोषणा ARM_SMMU_ATSR_ACTIVE		BIT(0)


/* Maximum number of context banks per SMMU */
#घोषणा ARM_SMMU_MAX_CBS		128

#घोषणा TLB_LOOP_TIMEOUT		1000000	/* 1s! */
#घोषणा TLB_SPIN_COUNT			10

/* Shared driver definitions */
क्रमागत arm_smmu_arch_version अणु
	ARM_SMMU_V1,
	ARM_SMMU_V1_64K,
	ARM_SMMU_V2,
पूर्ण;

क्रमागत arm_smmu_implementation अणु
	GENERIC_SMMU,
	ARM_MMU500,
	CAVIUM_SMMUV2,
	QCOM_SMMUV2,
पूर्ण;

काष्ठा arm_smmu_s2cr अणु
	काष्ठा iommu_group		*group;
	पूर्णांक				count;
	क्रमागत arm_smmu_s2cr_type		type;
	क्रमागत arm_smmu_s2cr_privcfg	privcfg;
	u8				cbndx;
पूर्ण;

काष्ठा arm_smmu_smr अणु
	u16				mask;
	u16				id;
	bool				valid;
	bool				pinned;
पूर्ण;

काष्ठा arm_smmu_device अणु
	काष्ठा device			*dev;

	व्योम __iomem			*base;
	अचिन्हित पूर्णांक			numpage;
	अचिन्हित पूर्णांक			pgshअगरt;

#घोषणा ARM_SMMU_FEAT_COHERENT_WALK	(1 << 0)
#घोषणा ARM_SMMU_FEAT_STREAM_MATCH	(1 << 1)
#घोषणा ARM_SMMU_FEAT_TRANS_S1		(1 << 2)
#घोषणा ARM_SMMU_FEAT_TRANS_S2		(1 << 3)
#घोषणा ARM_SMMU_FEAT_TRANS_NESTED	(1 << 4)
#घोषणा ARM_SMMU_FEAT_TRANS_OPS		(1 << 5)
#घोषणा ARM_SMMU_FEAT_VMID16		(1 << 6)
#घोषणा ARM_SMMU_FEAT_FMT_AARCH64_4K	(1 << 7)
#घोषणा ARM_SMMU_FEAT_FMT_AARCH64_16K	(1 << 8)
#घोषणा ARM_SMMU_FEAT_FMT_AARCH64_64K	(1 << 9)
#घोषणा ARM_SMMU_FEAT_FMT_AARCH32_L	(1 << 10)
#घोषणा ARM_SMMU_FEAT_FMT_AARCH32_S	(1 << 11)
#घोषणा ARM_SMMU_FEAT_EXIDS		(1 << 12)
	u32				features;

	क्रमागत arm_smmu_arch_version	version;
	क्रमागत arm_smmu_implementation	model;
	स्थिर काष्ठा arm_smmu_impl	*impl;

	u32				num_context_banks;
	u32				num_s2_context_banks;
	DECLARE_BITMAP(context_map, ARM_SMMU_MAX_CBS);
	काष्ठा arm_smmu_cb		*cbs;
	atomic_t			irptndx;

	u32				num_mapping_groups;
	u16				streamid_mask;
	u16				smr_mask_mask;
	काष्ठा arm_smmu_smr		*smrs;
	काष्ठा arm_smmu_s2cr		*s2crs;
	काष्ठा mutex			stream_map_mutex;

	अचिन्हित दीर्घ			va_size;
	अचिन्हित दीर्घ			ipa_size;
	अचिन्हित दीर्घ			pa_size;
	अचिन्हित दीर्घ			pgsize_biपंचांगap;

	u32				num_global_irqs;
	u32				num_context_irqs;
	अचिन्हित पूर्णांक			*irqs;
	काष्ठा clk_bulk_data		*clks;
	पूर्णांक				num_clks;

	spinlock_t			global_sync_lock;

	/* IOMMU core code handle */
	काष्ठा iommu_device		iommu;
पूर्ण;

क्रमागत arm_smmu_context_fmt अणु
	ARM_SMMU_CTX_FMT_NONE,
	ARM_SMMU_CTX_FMT_AARCH64,
	ARM_SMMU_CTX_FMT_AARCH32_L,
	ARM_SMMU_CTX_FMT_AARCH32_S,
पूर्ण;

काष्ठा arm_smmu_cfg अणु
	u8				cbndx;
	u8				irptndx;
	जोड़ अणु
		u16			asid;
		u16			vmid;
	पूर्ण;
	क्रमागत arm_smmu_cbar_type		cbar;
	क्रमागत arm_smmu_context_fmt	fmt;
पूर्ण;
#घोषणा ARM_SMMU_INVALID_IRPTNDX	0xff

काष्ठा arm_smmu_cb अणु
	u64				ttbr[2];
	u32				tcr[2];
	u32				mair[2];
	काष्ठा arm_smmu_cfg		*cfg;
पूर्ण;

क्रमागत arm_smmu_करोमुख्य_stage अणु
	ARM_SMMU_DOMAIN_S1 = 0,
	ARM_SMMU_DOMAIN_S2,
	ARM_SMMU_DOMAIN_NESTED,
	ARM_SMMU_DOMAIN_BYPASS,
पूर्ण;

काष्ठा arm_smmu_करोमुख्य अणु
	काष्ठा arm_smmu_device		*smmu;
	काष्ठा io_pgtable_ops		*pgtbl_ops;
	अचिन्हित दीर्घ			pgtbl_quirks;
	स्थिर काष्ठा iommu_flush_ops	*flush_ops;
	काष्ठा arm_smmu_cfg		cfg;
	क्रमागत arm_smmu_करोमुख्य_stage	stage;
	काष्ठा mutex			init_mutex; /* Protects smmu poपूर्णांकer */
	spinlock_t			cb_lock; /* Serialises ATS1* ops and TLB syncs */
	काष्ठा iommu_करोमुख्य		करोमुख्य;
पूर्ण;

काष्ठा arm_smmu_master_cfg अणु
	काष्ठा arm_smmu_device		*smmu;
	s16				smendx[];
पूर्ण;

अटल अंतरभूत u32 arm_smmu_lpae_tcr(स्थिर काष्ठा io_pgtable_cfg *cfg)
अणु
	u32 tcr = FIELD_PREP(ARM_SMMU_TCR_TG0, cfg->arm_lpae_s1_cfg.tcr.tg) |
		FIELD_PREP(ARM_SMMU_TCR_SH0, cfg->arm_lpae_s1_cfg.tcr.sh) |
		FIELD_PREP(ARM_SMMU_TCR_ORGN0, cfg->arm_lpae_s1_cfg.tcr.orgn) |
		FIELD_PREP(ARM_SMMU_TCR_IRGN0, cfg->arm_lpae_s1_cfg.tcr.irgn) |
		FIELD_PREP(ARM_SMMU_TCR_T0SZ, cfg->arm_lpae_s1_cfg.tcr.tsz);

       /*
	* When TTBR1 is selected shअगरt the TCR fields by 16 bits and disable
	* translation in TTBR0
	*/
	अगर (cfg->quirks & IO_PGTABLE_QUIRK_ARM_TTBR1) अणु
		tcr = (tcr << 16) & ~ARM_SMMU_TCR_A1;
		tcr |= ARM_SMMU_TCR_EPD0;
	पूर्ण अन्यथा
		tcr |= ARM_SMMU_TCR_EPD1;

	वापस tcr;
पूर्ण

अटल अंतरभूत u32 arm_smmu_lpae_tcr2(स्थिर काष्ठा io_pgtable_cfg *cfg)
अणु
	वापस FIELD_PREP(ARM_SMMU_TCR2_PASIZE, cfg->arm_lpae_s1_cfg.tcr.ips) |
	       FIELD_PREP(ARM_SMMU_TCR2_SEP, ARM_SMMU_TCR2_SEP_UPSTREAM);
पूर्ण

अटल अंतरभूत u32 arm_smmu_lpae_vtcr(स्थिर काष्ठा io_pgtable_cfg *cfg)
अणु
	वापस ARM_SMMU_VTCR_RES1 |
	       FIELD_PREP(ARM_SMMU_VTCR_PS, cfg->arm_lpae_s2_cfg.vtcr.ps) |
	       FIELD_PREP(ARM_SMMU_VTCR_TG0, cfg->arm_lpae_s2_cfg.vtcr.tg) |
	       FIELD_PREP(ARM_SMMU_VTCR_SH0, cfg->arm_lpae_s2_cfg.vtcr.sh) |
	       FIELD_PREP(ARM_SMMU_VTCR_ORGN0, cfg->arm_lpae_s2_cfg.vtcr.orgn) |
	       FIELD_PREP(ARM_SMMU_VTCR_IRGN0, cfg->arm_lpae_s2_cfg.vtcr.irgn) |
	       FIELD_PREP(ARM_SMMU_VTCR_SL0, cfg->arm_lpae_s2_cfg.vtcr.sl) |
	       FIELD_PREP(ARM_SMMU_VTCR_T0SZ, cfg->arm_lpae_s2_cfg.vtcr.tsz);
पूर्ण

/* Implementation details, yay! */
काष्ठा arm_smmu_impl अणु
	u32 (*पढ़ो_reg)(काष्ठा arm_smmu_device *smmu, पूर्णांक page, पूर्णांक offset);
	व्योम (*ग_लिखो_reg)(काष्ठा arm_smmu_device *smmu, पूर्णांक page, पूर्णांक offset,
			  u32 val);
	u64 (*पढ़ो_reg64)(काष्ठा arm_smmu_device *smmu, पूर्णांक page, पूर्णांक offset);
	व्योम (*ग_लिखो_reg64)(काष्ठा arm_smmu_device *smmu, पूर्णांक page, पूर्णांक offset,
			    u64 val);
	पूर्णांक (*cfg_probe)(काष्ठा arm_smmu_device *smmu);
	पूर्णांक (*reset)(काष्ठा arm_smmu_device *smmu);
	पूर्णांक (*init_context)(काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य,
			काष्ठा io_pgtable_cfg *cfg, काष्ठा device *dev);
	व्योम (*tlb_sync)(काष्ठा arm_smmu_device *smmu, पूर्णांक page, पूर्णांक sync,
			 पूर्णांक status);
	पूर्णांक (*def_करोमुख्य_type)(काष्ठा device *dev);
	irqवापस_t (*global_fault)(पूर्णांक irq, व्योम *dev);
	irqवापस_t (*context_fault)(पूर्णांक irq, व्योम *dev);
	पूर्णांक (*alloc_context_bank)(काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य,
				  काष्ठा arm_smmu_device *smmu,
				  काष्ठा device *dev, पूर्णांक start);
	व्योम (*ग_लिखो_s2cr)(काष्ठा arm_smmu_device *smmu, पूर्णांक idx);
	व्योम (*ग_लिखो_sctlr)(काष्ठा arm_smmu_device *smmu, पूर्णांक idx, u32 reg);
पूर्ण;

#घोषणा INVALID_SMENDX			-1
#घोषणा cfg_smendx(cfg, fw, i) \
	(i >= fw->num_ids ? INVALID_SMENDX : cfg->smendx[i])
#घोषणा क्रम_each_cfg_sme(cfg, fw, i, idx) \
	क्रम (i = 0; idx = cfg_smendx(cfg, fw, i), i < fw->num_ids; ++i)

अटल अंतरभूत पूर्णांक __arm_smmu_alloc_biपंचांगap(अचिन्हित दीर्घ *map, पूर्णांक start, पूर्णांक end)
अणु
	पूर्णांक idx;

	करो अणु
		idx = find_next_zero_bit(map, end, start);
		अगर (idx == end)
			वापस -ENOSPC;
	पूर्ण जबतक (test_and_set_bit(idx, map));

	वापस idx;
पूर्ण

अटल अंतरभूत व्योम __iomem *arm_smmu_page(काष्ठा arm_smmu_device *smmu, पूर्णांक n)
अणु
	वापस smmu->base + (n << smmu->pgshअगरt);
पूर्ण

अटल अंतरभूत u32 arm_smmu_पढ़ोl(काष्ठा arm_smmu_device *smmu, पूर्णांक page, पूर्णांक offset)
अणु
	अगर (smmu->impl && unlikely(smmu->impl->पढ़ो_reg))
		वापस smmu->impl->पढ़ो_reg(smmu, page, offset);
	वापस पढ़ोl_relaxed(arm_smmu_page(smmu, page) + offset);
पूर्ण

अटल अंतरभूत व्योम arm_smmu_ग_लिखोl(काष्ठा arm_smmu_device *smmu, पूर्णांक page,
				   पूर्णांक offset, u32 val)
अणु
	अगर (smmu->impl && unlikely(smmu->impl->ग_लिखो_reg))
		smmu->impl->ग_लिखो_reg(smmu, page, offset, val);
	अन्यथा
		ग_लिखोl_relaxed(val, arm_smmu_page(smmu, page) + offset);
पूर्ण

अटल अंतरभूत u64 arm_smmu_पढ़ोq(काष्ठा arm_smmu_device *smmu, पूर्णांक page, पूर्णांक offset)
अणु
	अगर (smmu->impl && unlikely(smmu->impl->पढ़ो_reg64))
		वापस smmu->impl->पढ़ो_reg64(smmu, page, offset);
	वापस पढ़ोq_relaxed(arm_smmu_page(smmu, page) + offset);
पूर्ण

अटल अंतरभूत व्योम arm_smmu_ग_लिखोq(काष्ठा arm_smmu_device *smmu, पूर्णांक page,
				   पूर्णांक offset, u64 val)
अणु
	अगर (smmu->impl && unlikely(smmu->impl->ग_लिखो_reg64))
		smmu->impl->ग_लिखो_reg64(smmu, page, offset, val);
	अन्यथा
		ग_लिखोq_relaxed(val, arm_smmu_page(smmu, page) + offset);
पूर्ण

#घोषणा ARM_SMMU_GR0		0
#घोषणा ARM_SMMU_GR1		1
#घोषणा ARM_SMMU_CB(s, n)	((s)->numpage + (n))

#घोषणा arm_smmu_gr0_पढ़ो(s, o)		\
	arm_smmu_पढ़ोl((s), ARM_SMMU_GR0, (o))
#घोषणा arm_smmu_gr0_ग_लिखो(s, o, v)	\
	arm_smmu_ग_लिखोl((s), ARM_SMMU_GR0, (o), (v))

#घोषणा arm_smmu_gr1_पढ़ो(s, o)		\
	arm_smmu_पढ़ोl((s), ARM_SMMU_GR1, (o))
#घोषणा arm_smmu_gr1_ग_लिखो(s, o, v)	\
	arm_smmu_ग_लिखोl((s), ARM_SMMU_GR1, (o), (v))

#घोषणा arm_smmu_cb_पढ़ो(s, n, o)	\
	arm_smmu_पढ़ोl((s), ARM_SMMU_CB((s), (n)), (o))
#घोषणा arm_smmu_cb_ग_लिखो(s, n, o, v)	\
	arm_smmu_ग_लिखोl((s), ARM_SMMU_CB((s), (n)), (o), (v))
#घोषणा arm_smmu_cb_पढ़ोq(s, n, o)	\
	arm_smmu_पढ़ोq((s), ARM_SMMU_CB((s), (n)), (o))
#घोषणा arm_smmu_cb_ग_लिखोq(s, n, o, v)	\
	arm_smmu_ग_लिखोq((s), ARM_SMMU_CB((s), (n)), (o), (v))

काष्ठा arm_smmu_device *arm_smmu_impl_init(काष्ठा arm_smmu_device *smmu);
काष्ठा arm_smmu_device *nvidia_smmu_impl_init(काष्ठा arm_smmu_device *smmu);
काष्ठा arm_smmu_device *qcom_smmu_impl_init(काष्ठा arm_smmu_device *smmu);

व्योम arm_smmu_ग_लिखो_context_bank(काष्ठा arm_smmu_device *smmu, पूर्णांक idx);
पूर्णांक arm_mmu500_reset(काष्ठा arm_smmu_device *smmu);

#पूर्ण_अगर /* _ARM_SMMU_H */
