<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IOMMU API क्रम Renesas VMSA-compatible IPMMU
 * Author: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *
 * Copyright (C) 2014-2020 Renesas Electronics Corporation
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-iommu.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/io-pgtable.h>
#समावेश <linux/iommu.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_iommu.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>

#अगर defined(CONFIG_ARM) && !defined(CONFIG_IOMMU_DMA)
#समावेश <यंत्र/dma-iommu.h>
#अन्यथा
#घोषणा arm_iommu_create_mapping(...)	शून्य
#घोषणा arm_iommu_attach_device(...)	-ENODEV
#घोषणा arm_iommu_release_mapping(...)	करो अणुपूर्ण जबतक (0)
#घोषणा arm_iommu_detach_device(...)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा IPMMU_CTX_MAX		8U
#घोषणा IPMMU_CTX_INVALID	-1

#घोषणा IPMMU_UTLB_MAX		48U

काष्ठा ipmmu_features अणु
	bool use_ns_alias_offset;
	bool has_cache_leaf_nodes;
	अचिन्हित पूर्णांक number_of_contexts;
	अचिन्हित पूर्णांक num_utlbs;
	bool setup_imbuscr;
	bool twobit_imttbcr_sl0;
	bool reserved_context;
	bool cache_snoop;
	अचिन्हित पूर्णांक ctx_offset_base;
	अचिन्हित पूर्णांक ctx_offset_stride;
	अचिन्हित पूर्णांक utlb_offset_base;
पूर्ण;

काष्ठा ipmmu_vmsa_device अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा iommu_device iommu;
	काष्ठा ipmmu_vmsa_device *root;
	स्थिर काष्ठा ipmmu_features *features;
	अचिन्हित पूर्णांक num_ctx;
	spinlock_t lock;			/* Protects ctx and करोमुख्यs[] */
	DECLARE_BITMAP(ctx, IPMMU_CTX_MAX);
	काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्यs[IPMMU_CTX_MAX];
	s8 utlb_ctx[IPMMU_UTLB_MAX];

	काष्ठा iommu_group *group;
	काष्ठा dma_iommu_mapping *mapping;
पूर्ण;

काष्ठा ipmmu_vmsa_करोमुख्य अणु
	काष्ठा ipmmu_vmsa_device *mmu;
	काष्ठा iommu_करोमुख्य io_करोमुख्य;

	काष्ठा io_pgtable_cfg cfg;
	काष्ठा io_pgtable_ops *iop;

	अचिन्हित पूर्णांक context_id;
	काष्ठा mutex mutex;			/* Protects mappings */
पूर्ण;

अटल काष्ठा ipmmu_vmsa_करोमुख्य *to_vmsa_करोमुख्य(काष्ठा iommu_करोमुख्य *करोm)
अणु
	वापस container_of(करोm, काष्ठा ipmmu_vmsa_करोमुख्य, io_करोमुख्य);
पूर्ण

अटल काष्ठा ipmmu_vmsa_device *to_ipmmu(काष्ठा device *dev)
अणु
	वापस dev_iommu_priv_get(dev);
पूर्ण

#घोषणा TLB_LOOP_TIMEOUT		100	/* 100us */

/* -----------------------------------------------------------------------------
 * Registers Definition
 */

#घोषणा IM_NS_ALIAS_OFFSET		0x800

/* MMU "context" रेजिस्टरs */
#घोषणा IMCTR				0x0000		/* R-Car Gen2/3 */
#घोषणा IMCTR_INTEN			(1 << 2)	/* R-Car Gen2/3 */
#घोषणा IMCTR_FLUSH			(1 << 1)	/* R-Car Gen2/3 */
#घोषणा IMCTR_MMUEN			(1 << 0)	/* R-Car Gen2/3 */

#घोषणा IMTTBCR				0x0008		/* R-Car Gen2/3 */
#घोषणा IMTTBCR_EAE			(1 << 31)	/* R-Car Gen2/3 */
#घोषणा IMTTBCR_SH0_INNER_SHAREABLE	(3 << 12)	/* R-Car Gen2 only */
#घोषणा IMTTBCR_ORGN0_WB_WA		(1 << 10)	/* R-Car Gen2 only */
#घोषणा IMTTBCR_IRGN0_WB_WA		(1 << 8)	/* R-Car Gen2 only */
#घोषणा IMTTBCR_SL0_TWOBIT_LVL_1	(2 << 6)	/* R-Car Gen3 only */
#घोषणा IMTTBCR_SL0_LVL_1		(1 << 4)	/* R-Car Gen2 only */

#घोषणा IMBUSCR				0x000c		/* R-Car Gen2 only */
#घोषणा IMBUSCR_DVM			(1 << 2)	/* R-Car Gen2 only */
#घोषणा IMBUSCR_BUSSEL_MASK		(3 << 0)	/* R-Car Gen2 only */

#घोषणा IMTTLBR0			0x0010		/* R-Car Gen2/3 */
#घोषणा IMTTUBR0			0x0014		/* R-Car Gen2/3 */

#घोषणा IMSTR				0x0020		/* R-Car Gen2/3 */
#घोषणा IMSTR_MHIT			(1 << 4)	/* R-Car Gen2/3 */
#घोषणा IMSTR_ABORT			(1 << 2)	/* R-Car Gen2/3 */
#घोषणा IMSTR_PF			(1 << 1)	/* R-Car Gen2/3 */
#घोषणा IMSTR_TF			(1 << 0)	/* R-Car Gen2/3 */

#घोषणा IMMAIR0				0x0028		/* R-Car Gen2/3 */

#घोषणा IMELAR				0x0030		/* R-Car Gen2/3, IMEAR on R-Car Gen2 */
#घोषणा IMEUAR				0x0034		/* R-Car Gen3 only */

/* uTLB रेजिस्टरs */
#घोषणा IMUCTR(n)			((n) < 32 ? IMUCTR0(n) : IMUCTR32(n))
#घोषणा IMUCTR0(n)			(0x0300 + ((n) * 16))		/* R-Car Gen2/3 */
#घोषणा IMUCTR32(n)			(0x0600 + (((n) - 32) * 16))	/* R-Car Gen3 only */
#घोषणा IMUCTR_TTSEL_MMU(n)		((n) << 4)	/* R-Car Gen2/3 */
#घोषणा IMUCTR_FLUSH			(1 << 1)	/* R-Car Gen2/3 */
#घोषणा IMUCTR_MMUEN			(1 << 0)	/* R-Car Gen2/3 */

#घोषणा IMUASID(n)			((n) < 32 ? IMUASID0(n) : IMUASID32(n))
#घोषणा IMUASID0(n)			(0x0308 + ((n) * 16))		/* R-Car Gen2/3 */
#घोषणा IMUASID32(n)			(0x0608 + (((n) - 32) * 16))	/* R-Car Gen3 only */

/* -----------------------------------------------------------------------------
 * Root device handling
 */

अटल काष्ठा platक्रमm_driver ipmmu_driver;

अटल bool ipmmu_is_root(काष्ठा ipmmu_vmsa_device *mmu)
अणु
	वापस mmu->root == mmu;
पूर्ण

अटल पूर्णांक __ipmmu_check_device(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा ipmmu_vmsa_device *mmu = dev_get_drvdata(dev);
	काष्ठा ipmmu_vmsa_device **rootp = data;

	अगर (ipmmu_is_root(mmu))
		*rootp = mmu;

	वापस 0;
पूर्ण

अटल काष्ठा ipmmu_vmsa_device *ipmmu_find_root(व्योम)
अणु
	काष्ठा ipmmu_vmsa_device *root = शून्य;

	वापस driver_क्रम_each_device(&ipmmu_driver.driver, शून्य, &root,
				      __ipmmu_check_device) == 0 ? root : शून्य;
पूर्ण

/* -----------------------------------------------------------------------------
 * Read/Write Access
 */

अटल u32 ipmmu_पढ़ो(काष्ठा ipmmu_vmsa_device *mmu, अचिन्हित पूर्णांक offset)
अणु
	वापस ioपढ़ो32(mmu->base + offset);
पूर्ण

अटल व्योम ipmmu_ग_लिखो(काष्ठा ipmmu_vmsa_device *mmu, अचिन्हित पूर्णांक offset,
			u32 data)
अणु
	ioग_लिखो32(data, mmu->base + offset);
पूर्ण

अटल अचिन्हित पूर्णांक ipmmu_ctx_reg(काष्ठा ipmmu_vmsa_device *mmu,
				  अचिन्हित पूर्णांक context_id, अचिन्हित पूर्णांक reg)
अणु
	वापस mmu->features->ctx_offset_base +
	       context_id * mmu->features->ctx_offset_stride + reg;
पूर्ण

अटल u32 ipmmu_ctx_पढ़ो(काष्ठा ipmmu_vmsa_device *mmu,
			  अचिन्हित पूर्णांक context_id, अचिन्हित पूर्णांक reg)
अणु
	वापस ipmmu_पढ़ो(mmu, ipmmu_ctx_reg(mmu, context_id, reg));
पूर्ण

अटल व्योम ipmmu_ctx_ग_लिखो(काष्ठा ipmmu_vmsa_device *mmu,
			    अचिन्हित पूर्णांक context_id, अचिन्हित पूर्णांक reg, u32 data)
अणु
	ipmmu_ग_लिखो(mmu, ipmmu_ctx_reg(mmu, context_id, reg), data);
पूर्ण

अटल u32 ipmmu_ctx_पढ़ो_root(काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्य,
			       अचिन्हित पूर्णांक reg)
अणु
	वापस ipmmu_ctx_पढ़ो(करोमुख्य->mmu->root, करोमुख्य->context_id, reg);
पूर्ण

अटल व्योम ipmmu_ctx_ग_लिखो_root(काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्य,
				 अचिन्हित पूर्णांक reg, u32 data)
अणु
	ipmmu_ctx_ग_लिखो(करोमुख्य->mmu->root, करोमुख्य->context_id, reg, data);
पूर्ण

अटल व्योम ipmmu_ctx_ग_लिखो_all(काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्य,
				अचिन्हित पूर्णांक reg, u32 data)
अणु
	अगर (करोमुख्य->mmu != करोमुख्य->mmu->root)
		ipmmu_ctx_ग_लिखो(करोमुख्य->mmu, करोमुख्य->context_id, reg, data);

	ipmmu_ctx_ग_लिखो(करोमुख्य->mmu->root, करोमुख्य->context_id, reg, data);
पूर्ण

अटल u32 ipmmu_utlb_reg(काष्ठा ipmmu_vmsa_device *mmu, अचिन्हित पूर्णांक reg)
अणु
	वापस mmu->features->utlb_offset_base + reg;
पूर्ण

अटल व्योम ipmmu_imuasid_ग_लिखो(काष्ठा ipmmu_vmsa_device *mmu,
				अचिन्हित पूर्णांक utlb, u32 data)
अणु
	ipmmu_ग_लिखो(mmu, ipmmu_utlb_reg(mmu, IMUASID(utlb)), data);
पूर्ण

अटल व्योम ipmmu_imuctr_ग_लिखो(काष्ठा ipmmu_vmsa_device *mmu,
			       अचिन्हित पूर्णांक utlb, u32 data)
अणु
	ipmmu_ग_लिखो(mmu, ipmmu_utlb_reg(mmu, IMUCTR(utlb)), data);
पूर्ण

/* -----------------------------------------------------------------------------
 * TLB and microTLB Management
 */

/* Wait क्रम any pending TLB invalidations to complete */
अटल व्योम ipmmu_tlb_sync(काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्य)
अणु
	अचिन्हित पूर्णांक count = 0;

	जबतक (ipmmu_ctx_पढ़ो_root(करोमुख्य, IMCTR) & IMCTR_FLUSH) अणु
		cpu_relax();
		अगर (++count == TLB_LOOP_TIMEOUT) अणु
			dev_err_ratelimited(करोमुख्य->mmu->dev,
			"TLB sync timed out -- MMU may be deadlocked\n");
			वापस;
		पूर्ण
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम ipmmu_tlb_invalidate(काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्य)
अणु
	u32 reg;

	reg = ipmmu_ctx_पढ़ो_root(करोमुख्य, IMCTR);
	reg |= IMCTR_FLUSH;
	ipmmu_ctx_ग_लिखो_all(करोमुख्य, IMCTR, reg);

	ipmmu_tlb_sync(करोमुख्य);
पूर्ण

/*
 * Enable MMU translation क्रम the microTLB.
 */
अटल व्योम ipmmu_utlb_enable(काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्य,
			      अचिन्हित पूर्णांक utlb)
अणु
	काष्ठा ipmmu_vmsa_device *mmu = करोमुख्य->mmu;

	/*
	 * TODO: Reference-count the microTLB as several bus masters can be
	 * connected to the same microTLB.
	 */

	/* TODO: What should we set the ASID to ? */
	ipmmu_imuasid_ग_लिखो(mmu, utlb, 0);
	/* TODO: Do we need to flush the microTLB ? */
	ipmmu_imuctr_ग_लिखो(mmu, utlb, IMUCTR_TTSEL_MMU(करोमुख्य->context_id) |
				      IMUCTR_FLUSH | IMUCTR_MMUEN);
	mmu->utlb_ctx[utlb] = करोमुख्य->context_id;
पूर्ण

/*
 * Disable MMU translation क्रम the microTLB.
 */
अटल व्योम ipmmu_utlb_disable(काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्य,
			       अचिन्हित पूर्णांक utlb)
अणु
	काष्ठा ipmmu_vmsa_device *mmu = करोमुख्य->mmu;

	ipmmu_imuctr_ग_लिखो(mmu, utlb, 0);
	mmu->utlb_ctx[utlb] = IPMMU_CTX_INVALID;
पूर्ण

अटल व्योम ipmmu_tlb_flush_all(व्योम *cookie)
अणु
	काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्य = cookie;

	ipmmu_tlb_invalidate(करोमुख्य);
पूर्ण

अटल व्योम ipmmu_tlb_flush(अचिन्हित दीर्घ iova, माप_प्रकार size,
				माप_प्रकार granule, व्योम *cookie)
अणु
	ipmmu_tlb_flush_all(cookie);
पूर्ण

अटल स्थिर काष्ठा iommu_flush_ops ipmmu_flush_ops = अणु
	.tlb_flush_all = ipmmu_tlb_flush_all,
	.tlb_flush_walk = ipmmu_tlb_flush,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Doमुख्य/Context Management
 */

अटल पूर्णांक ipmmu_करोमुख्य_allocate_context(काष्ठा ipmmu_vmsa_device *mmu,
					 काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्य)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&mmu->lock, flags);

	ret = find_first_zero_bit(mmu->ctx, mmu->num_ctx);
	अगर (ret != mmu->num_ctx) अणु
		mmu->करोमुख्यs[ret] = करोमुख्य;
		set_bit(ret, mmu->ctx);
	पूर्ण अन्यथा
		ret = -EBUSY;

	spin_unlock_irqrestore(&mmu->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम ipmmu_करोमुख्य_मुक्त_context(काष्ठा ipmmu_vmsa_device *mmu,
				      अचिन्हित पूर्णांक context_id)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mmu->lock, flags);

	clear_bit(context_id, mmu->ctx);
	mmu->करोमुख्यs[context_id] = शून्य;

	spin_unlock_irqrestore(&mmu->lock, flags);
पूर्ण

अटल व्योम ipmmu_करोमुख्य_setup_context(काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्य)
अणु
	u64 ttbr;
	u32 पंचांगp;

	/* TTBR0 */
	ttbr = करोमुख्य->cfg.arm_lpae_s1_cfg.ttbr;
	ipmmu_ctx_ग_लिखो_root(करोमुख्य, IMTTLBR0, ttbr);
	ipmmu_ctx_ग_लिखो_root(करोमुख्य, IMTTUBR0, ttbr >> 32);

	/*
	 * TTBCR
	 * We use दीर्घ descriptors and allocate the whole 32-bit VA space to
	 * TTBR0.
	 */
	अगर (करोमुख्य->mmu->features->twobit_imttbcr_sl0)
		पंचांगp = IMTTBCR_SL0_TWOBIT_LVL_1;
	अन्यथा
		पंचांगp = IMTTBCR_SL0_LVL_1;

	अगर (करोमुख्य->mmu->features->cache_snoop)
		पंचांगp |= IMTTBCR_SH0_INNER_SHAREABLE | IMTTBCR_ORGN0_WB_WA |
		       IMTTBCR_IRGN0_WB_WA;

	ipmmu_ctx_ग_लिखो_root(करोमुख्य, IMTTBCR, IMTTBCR_EAE | पंचांगp);

	/* MAIR0 */
	ipmmu_ctx_ग_लिखो_root(करोमुख्य, IMMAIR0,
			     करोमुख्य->cfg.arm_lpae_s1_cfg.mair);

	/* IMBUSCR */
	अगर (करोमुख्य->mmu->features->setup_imbuscr)
		ipmmu_ctx_ग_लिखो_root(करोमुख्य, IMBUSCR,
				     ipmmu_ctx_पढ़ो_root(करोमुख्य, IMBUSCR) &
				     ~(IMBUSCR_DVM | IMBUSCR_BUSSEL_MASK));

	/*
	 * IMSTR
	 * Clear all पूर्णांकerrupt flags.
	 */
	ipmmu_ctx_ग_लिखो_root(करोमुख्य, IMSTR, ipmmu_ctx_पढ़ो_root(करोमुख्य, IMSTR));

	/*
	 * IMCTR
	 * Enable the MMU and पूर्णांकerrupt generation. The दीर्घ-descriptor
	 * translation table क्रमmat करोesn't use TEX remapping. Don't enable AF
	 * software management as we have no use क्रम it. Flush the TLB as
	 * required when modअगरying the context रेजिस्टरs.
	 */
	ipmmu_ctx_ग_लिखो_all(करोमुख्य, IMCTR,
			    IMCTR_INTEN | IMCTR_FLUSH | IMCTR_MMUEN);
पूर्ण

अटल पूर्णांक ipmmu_करोमुख्य_init_context(काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्य)
अणु
	पूर्णांक ret;

	/*
	 * Allocate the page table operations.
	 *
	 * VMSA states in section B3.6.3 "Control of Secure or Non-secure memory
	 * access, Long-descriptor क्रमmat" that the NStable bit being set in a
	 * table descriptor will result in the NStable and NS bits of all child
	 * entries being ignored and considered as being set. The IPMMU seems
	 * not to comply with this, as it generates a secure access page fault
	 * अगर any of the NStable and NS bits isn't set when running in
	 * non-secure mode.
	 */
	करोमुख्य->cfg.quirks = IO_PGTABLE_QUIRK_ARM_NS;
	करोमुख्य->cfg.pgsize_biपंचांगap = SZ_1G | SZ_2M | SZ_4K;
	करोमुख्य->cfg.ias = 32;
	करोमुख्य->cfg.oas = 40;
	करोमुख्य->cfg.tlb = &ipmmu_flush_ops;
	करोमुख्य->io_करोमुख्य.geometry.aperture_end = DMA_BIT_MASK(32);
	करोमुख्य->io_करोमुख्य.geometry.क्रमce_aperture = true;
	/*
	 * TODO: Add support क्रम coherent walk through CCI with DVM and हटाओ
	 * cache handling. For now, delegate it to the io-pgtable code.
	 */
	करोमुख्य->cfg.coherent_walk = false;
	करोमुख्य->cfg.iommu_dev = करोमुख्य->mmu->root->dev;

	/*
	 * Find an unused context.
	 */
	ret = ipmmu_करोमुख्य_allocate_context(करोमुख्य->mmu->root, करोमुख्य);
	अगर (ret < 0)
		वापस ret;

	करोमुख्य->context_id = ret;

	करोमुख्य->iop = alloc_io_pgtable_ops(ARM_32_LPAE_S1, &करोमुख्य->cfg,
					   करोमुख्य);
	अगर (!करोमुख्य->iop) अणु
		ipmmu_करोमुख्य_मुक्त_context(करोमुख्य->mmu->root,
					  करोमुख्य->context_id);
		वापस -EINVAL;
	पूर्ण

	ipmmu_करोमुख्य_setup_context(करोमुख्य);
	वापस 0;
पूर्ण

अटल व्योम ipmmu_करोमुख्य_destroy_context(काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्य)
अणु
	अगर (!करोमुख्य->mmu)
		वापस;

	/*
	 * Disable the context. Flush the TLB as required when modअगरying the
	 * context रेजिस्टरs.
	 *
	 * TODO: Is TLB flush really needed ?
	 */
	ipmmu_ctx_ग_लिखो_all(करोमुख्य, IMCTR, IMCTR_FLUSH);
	ipmmu_tlb_sync(करोमुख्य);
	ipmmu_करोमुख्य_मुक्त_context(करोमुख्य->mmu->root, करोमुख्य->context_id);
पूर्ण

/* -----------------------------------------------------------------------------
 * Fault Handling
 */

अटल irqवापस_t ipmmu_करोमुख्य_irq(काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्य)
अणु
	स्थिर u32 err_mask = IMSTR_MHIT | IMSTR_ABORT | IMSTR_PF | IMSTR_TF;
	काष्ठा ipmmu_vmsa_device *mmu = करोमुख्य->mmu;
	अचिन्हित दीर्घ iova;
	u32 status;

	status = ipmmu_ctx_पढ़ो_root(करोमुख्य, IMSTR);
	अगर (!(status & err_mask))
		वापस IRQ_NONE;

	iova = ipmmu_ctx_पढ़ो_root(करोमुख्य, IMELAR);
	अगर (IS_ENABLED(CONFIG_64BIT))
		iova |= (u64)ipmmu_ctx_पढ़ो_root(करोमुख्य, IMEUAR) << 32;

	/*
	 * Clear the error status flags. Unlike traditional पूर्णांकerrupt flag
	 * रेजिस्टरs that must be cleared by writing 1, this status रेजिस्टर
	 * seems to require 0. The error address रेजिस्टर must be पढ़ो beक्रमe,
	 * otherwise its value will be 0.
	 */
	ipmmu_ctx_ग_लिखो_root(करोमुख्य, IMSTR, 0);

	/* Log fatal errors. */
	अगर (status & IMSTR_MHIT)
		dev_err_ratelimited(mmu->dev, "Multiple TLB hits @0x%lx\n",
				    iova);
	अगर (status & IMSTR_ABORT)
		dev_err_ratelimited(mmu->dev, "Page Table Walk Abort @0x%lx\n",
				    iova);

	अगर (!(status & (IMSTR_PF | IMSTR_TF)))
		वापस IRQ_NONE;

	/*
	 * Try to handle page faults and translation faults.
	 *
	 * TODO: We need to look up the faulty device based on the I/O VA. Use
	 * the IOMMU device क्रम now.
	 */
	अगर (!report_iommu_fault(&करोमुख्य->io_करोमुख्य, mmu->dev, iova, 0))
		वापस IRQ_HANDLED;

	dev_err_ratelimited(mmu->dev,
			    "Unhandled fault: status 0x%08x iova 0x%lx\n",
			    status, iova);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ipmmu_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा ipmmu_vmsa_device *mmu = dev;
	irqवापस_t status = IRQ_NONE;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mmu->lock, flags);

	/*
	 * Check पूर्णांकerrupts क्रम all active contexts.
	 */
	क्रम (i = 0; i < mmu->num_ctx; i++) अणु
		अगर (!mmu->करोमुख्यs[i])
			जारी;
		अगर (ipmmu_करोमुख्य_irq(mmu->करोमुख्यs[i]) == IRQ_HANDLED)
			status = IRQ_HANDLED;
	पूर्ण

	spin_unlock_irqrestore(&mmu->lock, flags);

	वापस status;
पूर्ण

/* -----------------------------------------------------------------------------
 * IOMMU Operations
 */

अटल काष्ठा iommu_करोमुख्य *__ipmmu_करोमुख्य_alloc(अचिन्हित type)
अणु
	काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्य;

	करोमुख्य = kzalloc(माप(*करोमुख्य), GFP_KERNEL);
	अगर (!करोमुख्य)
		वापस शून्य;

	mutex_init(&करोमुख्य->mutex);

	वापस &करोमुख्य->io_करोमुख्य;
पूर्ण

अटल काष्ठा iommu_करोमुख्य *ipmmu_करोमुख्य_alloc(अचिन्हित type)
अणु
	काष्ठा iommu_करोमुख्य *io_करोमुख्य = शून्य;

	चयन (type) अणु
	हाल IOMMU_DOMAIN_UNMANAGED:
		io_करोमुख्य = __ipmmu_करोमुख्य_alloc(type);
		अवरोध;

	हाल IOMMU_DOMAIN_DMA:
		io_करोमुख्य = __ipmmu_करोमुख्य_alloc(type);
		अगर (io_करोमुख्य && iommu_get_dma_cookie(io_करोमुख्य)) अणु
			kमुक्त(io_करोमुख्य);
			io_करोमुख्य = शून्य;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस io_करोमुख्य;
पूर्ण

अटल व्योम ipmmu_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *io_करोमुख्य)
अणु
	काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्य = to_vmsa_करोमुख्य(io_करोमुख्य);

	/*
	 * Free the करोमुख्य resources. We assume that all devices have alपढ़ोy
	 * been detached.
	 */
	iommu_put_dma_cookie(io_करोमुख्य);
	ipmmu_करोमुख्य_destroy_context(करोमुख्य);
	मुक्त_io_pgtable_ops(करोमुख्य->iop);
	kमुक्त(करोमुख्य);
पूर्ण

अटल पूर्णांक ipmmu_attach_device(काष्ठा iommu_करोमुख्य *io_करोमुख्य,
			       काष्ठा device *dev)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	काष्ठा ipmmu_vmsa_device *mmu = to_ipmmu(dev);
	काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्य = to_vmsa_करोमुख्य(io_करोमुख्य);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (!mmu) अणु
		dev_err(dev, "Cannot attach to IPMMU\n");
		वापस -ENXIO;
	पूर्ण

	mutex_lock(&करोमुख्य->mutex);

	अगर (!करोमुख्य->mmu) अणु
		/* The करोमुख्य hasn't been used yet, initialize it. */
		करोमुख्य->mmu = mmu;
		ret = ipmmu_करोमुख्य_init_context(करोमुख्य);
		अगर (ret < 0) अणु
			dev_err(dev, "Unable to initialize IPMMU context\n");
			करोमुख्य->mmu = शून्य;
		पूर्ण अन्यथा अणु
			dev_info(dev, "Using IPMMU context %u\n",
				 करोमुख्य->context_id);
		पूर्ण
	पूर्ण अन्यथा अगर (करोमुख्य->mmu != mmu) अणु
		/*
		 * Something is wrong, we can't attach two devices using
		 * dअगरferent IOMMUs to the same करोमुख्य.
		 */
		dev_err(dev, "Can't attach IPMMU %s to domain on IPMMU %s\n",
			dev_name(mmu->dev), dev_name(करोमुख्य->mmu->dev));
		ret = -EINVAL;
	पूर्ण अन्यथा
		dev_info(dev, "Reusing IPMMU context %u\n", करोमुख्य->context_id);

	mutex_unlock(&करोमुख्य->mutex);

	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < fwspec->num_ids; ++i)
		ipmmu_utlb_enable(करोमुख्य, fwspec->ids[i]);

	वापस 0;
पूर्ण

अटल व्योम ipmmu_detach_device(काष्ठा iommu_करोमुख्य *io_करोमुख्य,
				काष्ठा device *dev)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्य = to_vmsa_करोमुख्य(io_करोमुख्य);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < fwspec->num_ids; ++i)
		ipmmu_utlb_disable(करोमुख्य, fwspec->ids[i]);

	/*
	 * TODO: Optimize by disabling the context when no device is attached.
	 */
पूर्ण

अटल पूर्णांक ipmmu_map(काष्ठा iommu_करोमुख्य *io_करोमुख्य, अचिन्हित दीर्घ iova,
		     phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot, gfp_t gfp)
अणु
	काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्य = to_vmsa_करोमुख्य(io_करोमुख्य);

	अगर (!करोमुख्य)
		वापस -ENODEV;

	वापस करोमुख्य->iop->map(करोमुख्य->iop, iova, paddr, size, prot, gfp);
पूर्ण

अटल माप_प्रकार ipmmu_unmap(काष्ठा iommu_करोमुख्य *io_करोमुख्य, अचिन्हित दीर्घ iova,
			  माप_प्रकार size, काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्य = to_vmsa_करोमुख्य(io_करोमुख्य);

	वापस करोमुख्य->iop->unmap(करोमुख्य->iop, iova, size, gather);
पूर्ण

अटल व्योम ipmmu_flush_iotlb_all(काष्ठा iommu_करोमुख्य *io_करोमुख्य)
अणु
	काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्य = to_vmsa_करोमुख्य(io_करोमुख्य);

	अगर (करोमुख्य->mmu)
		ipmmu_tlb_flush_all(करोमुख्य);
पूर्ण

अटल व्योम ipmmu_iotlb_sync(काष्ठा iommu_करोमुख्य *io_करोमुख्य,
			     काष्ठा iommu_iotlb_gather *gather)
अणु
	ipmmu_flush_iotlb_all(io_करोमुख्य);
पूर्ण

अटल phys_addr_t ipmmu_iova_to_phys(काष्ठा iommu_करोमुख्य *io_करोमुख्य,
				      dma_addr_t iova)
अणु
	काष्ठा ipmmu_vmsa_करोमुख्य *करोमुख्य = to_vmsa_करोमुख्य(io_करोमुख्य);

	/* TODO: Is locking needed ? */

	वापस करोमुख्य->iop->iova_to_phys(करोमुख्य->iop, iova);
पूर्ण

अटल पूर्णांक ipmmu_init_platक्रमm_device(काष्ठा device *dev,
				      काष्ठा of_phandle_args *args)
अणु
	काष्ठा platक्रमm_device *ipmmu_pdev;

	ipmmu_pdev = of_find_device_by_node(args->np);
	अगर (!ipmmu_pdev)
		वापस -ENODEV;

	dev_iommu_priv_set(dev, platक्रमm_get_drvdata(ipmmu_pdev));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा soc_device_attribute soc_needs_opt_in[] = अणु
	अणु .family = "R-Car Gen3", पूर्ण,
	अणु .family = "RZ/G2", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा soc_device_attribute soc_denylist[] = अणु
	अणु .soc_id = "r8a774a1", पूर्ण,
	अणु .soc_id = "r8a7795", .revision = "ES1.*" पूर्ण,
	अणु .soc_id = "r8a7795", .revision = "ES2.*" पूर्ण,
	अणु .soc_id = "r8a7796", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर devices_allowlist[] = अणु
	"ee100000.mmc",
	"ee120000.mmc",
	"ee140000.mmc",
	"ee160000.mmc"
पूर्ण;

अटल bool ipmmu_device_is_allowed(काष्ठा device *dev)
अणु
	अचिन्हित पूर्णांक i;

	/*
	 * R-Car Gen3 and RZ/G2 use the allow list to opt-in devices.
	 * For Other SoCs, this वापसs true anyway.
	 */
	अगर (!soc_device_match(soc_needs_opt_in))
		वापस true;

	/* Check whether this SoC can use the IPMMU correctly or not */
	अगर (soc_device_match(soc_denylist))
		वापस false;

	/* Check whether this device can work with the IPMMU */
	क्रम (i = 0; i < ARRAY_SIZE(devices_allowlist); i++) अणु
		अगर (!म_भेद(dev_name(dev), devices_allowlist[i]))
			वापस true;
	पूर्ण

	/* Otherwise, करो not allow use of IPMMU */
	वापस false;
पूर्ण

अटल पूर्णांक ipmmu_of_xlate(काष्ठा device *dev,
			  काष्ठा of_phandle_args *spec)
अणु
	अगर (!ipmmu_device_is_allowed(dev))
		वापस -ENODEV;

	iommu_fwspec_add_ids(dev, spec->args, 1);

	/* Initialize once - xlate() will call multiple बार */
	अगर (to_ipmmu(dev))
		वापस 0;

	वापस ipmmu_init_platक्रमm_device(dev, spec);
पूर्ण

अटल पूर्णांक ipmmu_init_arm_mapping(काष्ठा device *dev)
अणु
	काष्ठा ipmmu_vmsa_device *mmu = to_ipmmu(dev);
	पूर्णांक ret;

	/*
	 * Create the ARM mapping, used by the ARM DMA mapping core to allocate
	 * VAs. This will allocate a corresponding IOMMU करोमुख्य.
	 *
	 * TODO:
	 * - Create one mapping per context (TLB).
	 * - Make the mapping size configurable ? We currently use a 2GB mapping
	 *   at a 1GB offset to ensure that शून्य VAs will fault.
	 */
	अगर (!mmu->mapping) अणु
		काष्ठा dma_iommu_mapping *mapping;

		mapping = arm_iommu_create_mapping(&platक्रमm_bus_type,
						   SZ_1G, SZ_2G);
		अगर (IS_ERR(mapping)) अणु
			dev_err(mmu->dev, "failed to create ARM IOMMU mapping\n");
			ret = PTR_ERR(mapping);
			जाओ error;
		पूर्ण

		mmu->mapping = mapping;
	पूर्ण

	/* Attach the ARM VA mapping to the device. */
	ret = arm_iommu_attach_device(dev, mmu->mapping);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to attach device to VA mapping\n");
		जाओ error;
	पूर्ण

	वापस 0;

error:
	अगर (mmu->mapping)
		arm_iommu_release_mapping(mmu->mapping);

	वापस ret;
पूर्ण

अटल काष्ठा iommu_device *ipmmu_probe_device(काष्ठा device *dev)
अणु
	काष्ठा ipmmu_vmsa_device *mmu = to_ipmmu(dev);

	/*
	 * Only let through devices that have been verअगरied in xlate()
	 */
	अगर (!mmu)
		वापस ERR_PTR(-ENODEV);

	वापस &mmu->iommu;
पूर्ण

अटल व्योम ipmmu_probe_finalize(काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;

	अगर (IS_ENABLED(CONFIG_ARM) && !IS_ENABLED(CONFIG_IOMMU_DMA))
		ret = ipmmu_init_arm_mapping(dev);

	अगर (ret)
		dev_err(dev, "Can't create IOMMU mapping - DMA-OPS will not work\n");
पूर्ण

अटल व्योम ipmmu_release_device(काष्ठा device *dev)
अणु
	arm_iommu_detach_device(dev);
पूर्ण

अटल काष्ठा iommu_group *ipmmu_find_group(काष्ठा device *dev)
अणु
	काष्ठा ipmmu_vmsa_device *mmu = to_ipmmu(dev);
	काष्ठा iommu_group *group;

	अगर (mmu->group)
		वापस iommu_group_ref_get(mmu->group);

	group = iommu_group_alloc();
	अगर (!IS_ERR(group))
		mmu->group = group;

	वापस group;
पूर्ण

अटल स्थिर काष्ठा iommu_ops ipmmu_ops = अणु
	.करोमुख्य_alloc = ipmmu_करोमुख्य_alloc,
	.करोमुख्य_मुक्त = ipmmu_करोमुख्य_मुक्त,
	.attach_dev = ipmmu_attach_device,
	.detach_dev = ipmmu_detach_device,
	.map = ipmmu_map,
	.unmap = ipmmu_unmap,
	.flush_iotlb_all = ipmmu_flush_iotlb_all,
	.iotlb_sync = ipmmu_iotlb_sync,
	.iova_to_phys = ipmmu_iova_to_phys,
	.probe_device = ipmmu_probe_device,
	.release_device = ipmmu_release_device,
	.probe_finalize = ipmmu_probe_finalize,
	.device_group = IS_ENABLED(CONFIG_ARM) && !IS_ENABLED(CONFIG_IOMMU_DMA)
			? generic_device_group : ipmmu_find_group,
	.pgsize_biपंचांगap = SZ_1G | SZ_2M | SZ_4K,
	.of_xlate = ipmmu_of_xlate,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Probe/हटाओ and init
 */

अटल व्योम ipmmu_device_reset(काष्ठा ipmmu_vmsa_device *mmu)
अणु
	अचिन्हित पूर्णांक i;

	/* Disable all contexts. */
	क्रम (i = 0; i < mmu->num_ctx; ++i)
		ipmmu_ctx_ग_लिखो(mmu, i, IMCTR, 0);
पूर्ण

अटल स्थिर काष्ठा ipmmu_features ipmmu_features_शेष = अणु
	.use_ns_alias_offset = true,
	.has_cache_leaf_nodes = false,
	.number_of_contexts = 1, /* software only tested with one context */
	.num_utlbs = 32,
	.setup_imbuscr = true,
	.twobit_imttbcr_sl0 = false,
	.reserved_context = false,
	.cache_snoop = true,
	.ctx_offset_base = 0,
	.ctx_offset_stride = 0x40,
	.utlb_offset_base = 0,
पूर्ण;

अटल स्थिर काष्ठा ipmmu_features ipmmu_features_rcar_gen3 = अणु
	.use_ns_alias_offset = false,
	.has_cache_leaf_nodes = true,
	.number_of_contexts = 8,
	.num_utlbs = 48,
	.setup_imbuscr = false,
	.twobit_imttbcr_sl0 = true,
	.reserved_context = true,
	.cache_snoop = false,
	.ctx_offset_base = 0,
	.ctx_offset_stride = 0x40,
	.utlb_offset_base = 0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ipmmu_of_ids[] = अणु
	अणु
		.compatible = "renesas,ipmmu-vmsa",
		.data = &ipmmu_features_शेष,
	पूर्ण, अणु
		.compatible = "renesas,ipmmu-r8a774a1",
		.data = &ipmmu_features_rcar_gen3,
	पूर्ण, अणु
		.compatible = "renesas,ipmmu-r8a774b1",
		.data = &ipmmu_features_rcar_gen3,
	पूर्ण, अणु
		.compatible = "renesas,ipmmu-r8a774c0",
		.data = &ipmmu_features_rcar_gen3,
	पूर्ण, अणु
		.compatible = "renesas,ipmmu-r8a774e1",
		.data = &ipmmu_features_rcar_gen3,
	पूर्ण, अणु
		.compatible = "renesas,ipmmu-r8a7795",
		.data = &ipmmu_features_rcar_gen3,
	पूर्ण, अणु
		.compatible = "renesas,ipmmu-r8a7796",
		.data = &ipmmu_features_rcar_gen3,
	पूर्ण, अणु
		.compatible = "renesas,ipmmu-r8a77961",
		.data = &ipmmu_features_rcar_gen3,
	पूर्ण, अणु
		.compatible = "renesas,ipmmu-r8a77965",
		.data = &ipmmu_features_rcar_gen3,
	पूर्ण, अणु
		.compatible = "renesas,ipmmu-r8a77970",
		.data = &ipmmu_features_rcar_gen3,
	पूर्ण, अणु
		.compatible = "renesas,ipmmu-r8a77990",
		.data = &ipmmu_features_rcar_gen3,
	पूर्ण, अणु
		.compatible = "renesas,ipmmu-r8a77995",
		.data = &ipmmu_features_rcar_gen3,
	पूर्ण, अणु
		/* Terminator */
	पूर्ण,
पूर्ण;

अटल पूर्णांक ipmmu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ipmmu_vmsa_device *mmu;
	काष्ठा resource *res;
	पूर्णांक irq;
	पूर्णांक ret;

	mmu = devm_kzalloc(&pdev->dev, माप(*mmu), GFP_KERNEL);
	अगर (!mmu) अणु
		dev_err(&pdev->dev, "cannot allocate device data\n");
		वापस -ENOMEM;
	पूर्ण

	mmu->dev = &pdev->dev;
	spin_lock_init(&mmu->lock);
	biपंचांगap_zero(mmu->ctx, IPMMU_CTX_MAX);
	mmu->features = of_device_get_match_data(&pdev->dev);
	स_रखो(mmu->utlb_ctx, IPMMU_CTX_INVALID, mmu->features->num_utlbs);
	dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(40));

	/* Map I/O memory and request IRQ. */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mmu->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(mmu->base))
		वापस PTR_ERR(mmu->base);

	/*
	 * The IPMMU has two रेजिस्टर banks, क्रम secure and non-secure modes.
	 * The bank mapped at the beginning of the IPMMU address space
	 * corresponds to the running mode of the CPU. When running in secure
	 * mode the non-secure रेजिस्टर bank is also available at an offset.
	 *
	 * Secure mode operation isn't clearly करोcumented and is thus currently
	 * not implemented in the driver. Furthermore, preliminary tests of
	 * non-secure operation with the मुख्य रेजिस्टर bank were not successful.
	 * Offset the रेजिस्टरs base unconditionally to poपूर्णांक to the non-secure
	 * alias space क्रम now.
	 */
	अगर (mmu->features->use_ns_alias_offset)
		mmu->base += IM_NS_ALIAS_OFFSET;

	mmu->num_ctx = min(IPMMU_CTX_MAX, mmu->features->number_of_contexts);

	/*
	 * Determine अगर this IPMMU instance is a root device by checking क्रम
	 * the lack of has_cache_leaf_nodes flag or renesas,ipmmu-मुख्य property.
	 */
	अगर (!mmu->features->has_cache_leaf_nodes ||
	    !of_find_property(pdev->dev.of_node, "renesas,ipmmu-main", शून्य))
		mmu->root = mmu;
	अन्यथा
		mmu->root = ipmmu_find_root();

	/*
	 * Wait until the root device has been रेजिस्टरed क्रम sure.
	 */
	अगर (!mmu->root)
		वापस -EPROBE_DEFER;

	/* Root devices have mandatory IRQs */
	अगर (ipmmu_is_root(mmu)) अणु
		irq = platक्रमm_get_irq(pdev, 0);
		अगर (irq < 0)
			वापस irq;

		ret = devm_request_irq(&pdev->dev, irq, ipmmu_irq, 0,
				       dev_name(&pdev->dev), mmu);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "failed to request IRQ %d\n", irq);
			वापस ret;
		पूर्ण

		ipmmu_device_reset(mmu);

		अगर (mmu->features->reserved_context) अणु
			dev_info(&pdev->dev, "IPMMU context 0 is reserved\n");
			set_bit(0, mmu->ctx);
		पूर्ण
	पूर्ण

	/*
	 * Register the IPMMU to the IOMMU subप्रणाली in the following हालs:
	 * - R-Car Gen2 IPMMU (all devices रेजिस्टरed)
	 * - R-Car Gen3 IPMMU (leaf devices only - skip root IPMMU-MM device)
	 */
	अगर (!mmu->features->has_cache_leaf_nodes || !ipmmu_is_root(mmu)) अणु
		ret = iommu_device_sysfs_add(&mmu->iommu, &pdev->dev, शून्य,
					     dev_name(&pdev->dev));
		अगर (ret)
			वापस ret;

		ret = iommu_device_रेजिस्टर(&mmu->iommu, &ipmmu_ops, &pdev->dev);
		अगर (ret)
			वापस ret;

#अगर defined(CONFIG_IOMMU_DMA)
		अगर (!iommu_present(&platक्रमm_bus_type))
			bus_set_iommu(&platक्रमm_bus_type, &ipmmu_ops);
#पूर्ण_अगर
	पूर्ण

	/*
	 * We can't create the ARM mapping here as it requires the bus to have
	 * an IOMMU, which only happens when bus_set_iommu() is called in
	 * ipmmu_init() after the probe function वापसs.
	 */

	platक्रमm_set_drvdata(pdev, mmu);

	वापस 0;
पूर्ण

अटल पूर्णांक ipmmu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ipmmu_vmsa_device *mmu = platक्रमm_get_drvdata(pdev);

	iommu_device_sysfs_हटाओ(&mmu->iommu);
	iommu_device_unरेजिस्टर(&mmu->iommu);

	arm_iommu_release_mapping(mmu->mapping);

	ipmmu_device_reset(mmu);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ipmmu_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा ipmmu_vmsa_device *mmu = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक i;

	/* Reset root MMU and restore contexts */
	अगर (ipmmu_is_root(mmu)) अणु
		ipmmu_device_reset(mmu);

		क्रम (i = 0; i < mmu->num_ctx; i++) अणु
			अगर (!mmu->करोमुख्यs[i])
				जारी;

			ipmmu_करोमुख्य_setup_context(mmu->करोमुख्यs[i]);
		पूर्ण
	पूर्ण

	/* Re-enable active micro-TLBs */
	क्रम (i = 0; i < mmu->features->num_utlbs; i++) अणु
		अगर (mmu->utlb_ctx[i] == IPMMU_CTX_INVALID)
			जारी;

		ipmmu_utlb_enable(mmu->root->करोमुख्यs[mmu->utlb_ctx[i]], i);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ipmmu_pm  = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(शून्य, ipmmu_resume_noirq)
पूर्ण;
#घोषणा DEV_PM_OPS	&ipmmu_pm
#अन्यथा
#घोषणा DEV_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा platक्रमm_driver ipmmu_driver = अणु
	.driver = अणु
		.name = "ipmmu-vmsa",
		.of_match_table = of_match_ptr(ipmmu_of_ids),
		.pm = DEV_PM_OPS,
	पूर्ण,
	.probe = ipmmu_probe,
	.हटाओ	= ipmmu_हटाओ,
पूर्ण;

अटल पूर्णांक __init ipmmu_init(व्योम)
अणु
	काष्ठा device_node *np;
	अटल bool setup_करोne;
	पूर्णांक ret;

	अगर (setup_करोne)
		वापस 0;

	np = of_find_matching_node(शून्य, ipmmu_of_ids);
	अगर (!np)
		वापस 0;

	of_node_put(np);

	ret = platक्रमm_driver_रेजिस्टर(&ipmmu_driver);
	अगर (ret < 0)
		वापस ret;

#अगर defined(CONFIG_ARM) && !defined(CONFIG_IOMMU_DMA)
	अगर (!iommu_present(&platक्रमm_bus_type))
		bus_set_iommu(&platक्रमm_bus_type, &ipmmu_ops);
#पूर्ण_अगर

	setup_करोne = true;
	वापस 0;
पूर्ण
subsys_initcall(ipmmu_init);
