<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IOMMU API क्रम QCOM secure IOMMUs.  Somewhat based on arm-smmu.c
 *
 * Copyright (C) 2013 ARM Limited
 * Copyright (C) 2017 Red Hat
 */

#समावेश <linux/atomic.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-iommu.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/io-64-nonatomic-hi-lo.h>
#समावेश <linux/io-pgtable.h>
#समावेश <linux/iommu.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kconfig.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_iommu.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/qcom_scm.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश "arm-smmu.h"

#घोषणा SMMU_INTR_SEL_NS     0x2000

क्रमागत qcom_iommu_clk अणु
	CLK_IFACE,
	CLK_BUS,
	CLK_TBU,
	CLK_NUM,
पूर्ण;

काष्ठा qcom_iommu_ctx;

काष्ठा qcom_iommu_dev अणु
	/* IOMMU core code handle */
	काष्ठा iommu_device	 iommu;
	काष्ठा device		*dev;
	काष्ठा clk_bulk_data clks[CLK_NUM];
	व्योम __iomem		*local_base;
	u32			 sec_id;
	u8			 num_ctxs;
	काष्ठा qcom_iommu_ctx	*ctxs[];   /* indexed by asid-1 */
पूर्ण;

काष्ठा qcom_iommu_ctx अणु
	काष्ठा device		*dev;
	व्योम __iomem		*base;
	bool			 secure_init;
	u8			 asid;      /* asid and ctx bank # are 1:1 */
	काष्ठा iommu_करोमुख्य	*करोमुख्य;
पूर्ण;

काष्ठा qcom_iommu_करोमुख्य अणु
	काष्ठा io_pgtable_ops	*pgtbl_ops;
	spinlock_t		 pgtbl_lock;
	काष्ठा mutex		 init_mutex; /* Protects iommu poपूर्णांकer */
	काष्ठा iommu_करोमुख्य	 करोमुख्य;
	काष्ठा qcom_iommu_dev	*iommu;
	काष्ठा iommu_fwspec	*fwspec;
पूर्ण;

अटल काष्ठा qcom_iommu_करोमुख्य *to_qcom_iommu_करोमुख्य(काष्ठा iommu_करोमुख्य *करोm)
अणु
	वापस container_of(करोm, काष्ठा qcom_iommu_करोमुख्य, करोमुख्य);
पूर्ण

अटल स्थिर काष्ठा iommu_ops qcom_iommu_ops;

अटल काष्ठा qcom_iommu_dev * to_iommu(काष्ठा device *dev)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	अगर (!fwspec || fwspec->ops != &qcom_iommu_ops)
		वापस शून्य;

	वापस dev_iommu_priv_get(dev);
पूर्ण

अटल काष्ठा qcom_iommu_ctx * to_ctx(काष्ठा qcom_iommu_करोमुख्य *d, अचिन्हित asid)
अणु
	काष्ठा qcom_iommu_dev *qcom_iommu = d->iommu;
	अगर (!qcom_iommu)
		वापस शून्य;
	वापस qcom_iommu->ctxs[asid - 1];
पूर्ण

अटल अंतरभूत व्योम
iommu_ग_लिखोl(काष्ठा qcom_iommu_ctx *ctx, अचिन्हित reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, ctx->base + reg);
पूर्ण

अटल अंतरभूत व्योम
iommu_ग_लिखोq(काष्ठा qcom_iommu_ctx *ctx, अचिन्हित reg, u64 val)
अणु
	ग_लिखोq_relaxed(val, ctx->base + reg);
पूर्ण

अटल अंतरभूत u32
iommu_पढ़ोl(काष्ठा qcom_iommu_ctx *ctx, अचिन्हित reg)
अणु
	वापस पढ़ोl_relaxed(ctx->base + reg);
पूर्ण

अटल अंतरभूत u64
iommu_पढ़ोq(काष्ठा qcom_iommu_ctx *ctx, अचिन्हित reg)
अणु
	वापस पढ़ोq_relaxed(ctx->base + reg);
पूर्ण

अटल व्योम qcom_iommu_tlb_sync(व्योम *cookie)
अणु
	काष्ठा qcom_iommu_करोमुख्य *qcom_करोमुख्य = cookie;
	काष्ठा iommu_fwspec *fwspec = qcom_करोमुख्य->fwspec;
	अचिन्हित i;

	क्रम (i = 0; i < fwspec->num_ids; i++) अणु
		काष्ठा qcom_iommu_ctx *ctx = to_ctx(qcom_करोमुख्य, fwspec->ids[i]);
		अचिन्हित पूर्णांक val, ret;

		iommu_ग_लिखोl(ctx, ARM_SMMU_CB_TLBSYNC, 0);

		ret = पढ़ोl_poll_समयout(ctx->base + ARM_SMMU_CB_TLBSTATUS, val,
					 (val & 0x1) == 0, 0, 5000000);
		अगर (ret)
			dev_err(ctx->dev, "timeout waiting for TLB SYNC\n");
	पूर्ण
पूर्ण

अटल व्योम qcom_iommu_tlb_inv_context(व्योम *cookie)
अणु
	काष्ठा qcom_iommu_करोमुख्य *qcom_करोमुख्य = cookie;
	काष्ठा iommu_fwspec *fwspec = qcom_करोमुख्य->fwspec;
	अचिन्हित i;

	क्रम (i = 0; i < fwspec->num_ids; i++) अणु
		काष्ठा qcom_iommu_ctx *ctx = to_ctx(qcom_करोमुख्य, fwspec->ids[i]);
		iommu_ग_लिखोl(ctx, ARM_SMMU_CB_S1_TLBIASID, ctx->asid);
	पूर्ण

	qcom_iommu_tlb_sync(cookie);
पूर्ण

अटल व्योम qcom_iommu_tlb_inv_range_nosync(अचिन्हित दीर्घ iova, माप_प्रकार size,
					    माप_प्रकार granule, bool leaf, व्योम *cookie)
अणु
	काष्ठा qcom_iommu_करोमुख्य *qcom_करोमुख्य = cookie;
	काष्ठा iommu_fwspec *fwspec = qcom_करोमुख्य->fwspec;
	अचिन्हित i, reg;

	reg = leaf ? ARM_SMMU_CB_S1_TLBIVAL : ARM_SMMU_CB_S1_TLBIVA;

	क्रम (i = 0; i < fwspec->num_ids; i++) अणु
		काष्ठा qcom_iommu_ctx *ctx = to_ctx(qcom_करोमुख्य, fwspec->ids[i]);
		माप_प्रकार s = size;

		iova = (iova >> 12) << 12;
		iova |= ctx->asid;
		करो अणु
			iommu_ग_लिखोl(ctx, reg, iova);
			iova += granule;
		पूर्ण जबतक (s -= granule);
	पूर्ण
पूर्ण

अटल व्योम qcom_iommu_tlb_flush_walk(अचिन्हित दीर्घ iova, माप_प्रकार size,
				      माप_प्रकार granule, व्योम *cookie)
अणु
	qcom_iommu_tlb_inv_range_nosync(iova, size, granule, false, cookie);
	qcom_iommu_tlb_sync(cookie);
पूर्ण

अटल व्योम qcom_iommu_tlb_add_page(काष्ठा iommu_iotlb_gather *gather,
				    अचिन्हित दीर्घ iova, माप_प्रकार granule,
				    व्योम *cookie)
अणु
	qcom_iommu_tlb_inv_range_nosync(iova, granule, granule, true, cookie);
पूर्ण

अटल स्थिर काष्ठा iommu_flush_ops qcom_flush_ops = अणु
	.tlb_flush_all	= qcom_iommu_tlb_inv_context,
	.tlb_flush_walk = qcom_iommu_tlb_flush_walk,
	.tlb_add_page	= qcom_iommu_tlb_add_page,
पूर्ण;

अटल irqवापस_t qcom_iommu_fault(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा qcom_iommu_ctx *ctx = dev;
	u32 fsr, fsynr;
	u64 iova;

	fsr = iommu_पढ़ोl(ctx, ARM_SMMU_CB_FSR);

	अगर (!(fsr & ARM_SMMU_FSR_FAULT))
		वापस IRQ_NONE;

	fsynr = iommu_पढ़ोl(ctx, ARM_SMMU_CB_FSYNR0);
	iova = iommu_पढ़ोq(ctx, ARM_SMMU_CB_FAR);

	अगर (!report_iommu_fault(ctx->करोमुख्य, ctx->dev, iova, 0)) अणु
		dev_err_ratelimited(ctx->dev,
				    "Unhandled context fault: fsr=0x%x, "
				    "iova=0x%016llx, fsynr=0x%x, cb=%d\n",
				    fsr, iova, fsynr, ctx->asid);
	पूर्ण

	iommu_ग_लिखोl(ctx, ARM_SMMU_CB_FSR, fsr);
	iommu_ग_लिखोl(ctx, ARM_SMMU_CB_RESUME, ARM_SMMU_RESUME_TERMINATE);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक qcom_iommu_init_करोमुख्य(काष्ठा iommu_करोमुख्य *करोमुख्य,
				  काष्ठा qcom_iommu_dev *qcom_iommu,
				  काष्ठा device *dev)
अणु
	काष्ठा qcom_iommu_करोमुख्य *qcom_करोमुख्य = to_qcom_iommu_करोमुख्य(करोमुख्य);
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	काष्ठा io_pgtable_ops *pgtbl_ops;
	काष्ठा io_pgtable_cfg pgtbl_cfg;
	पूर्णांक i, ret = 0;
	u32 reg;

	mutex_lock(&qcom_करोमुख्य->init_mutex);
	अगर (qcom_करोमुख्य->iommu)
		जाओ out_unlock;

	pgtbl_cfg = (काष्ठा io_pgtable_cfg) अणु
		.pgsize_biपंचांगap	= qcom_iommu_ops.pgsize_biपंचांगap,
		.ias		= 32,
		.oas		= 40,
		.tlb		= &qcom_flush_ops,
		.iommu_dev	= qcom_iommu->dev,
	पूर्ण;

	qcom_करोमुख्य->iommu = qcom_iommu;
	qcom_करोमुख्य->fwspec = fwspec;

	pgtbl_ops = alloc_io_pgtable_ops(ARM_32_LPAE_S1, &pgtbl_cfg, qcom_करोमुख्य);
	अगर (!pgtbl_ops) अणु
		dev_err(qcom_iommu->dev, "failed to allocate pagetable ops\n");
		ret = -ENOMEM;
		जाओ out_clear_iommu;
	पूर्ण

	/* Update the करोमुख्य's page sizes to reflect the page table क्रमmat */
	करोमुख्य->pgsize_biपंचांगap = pgtbl_cfg.pgsize_biपंचांगap;
	करोमुख्य->geometry.aperture_end = (1ULL << pgtbl_cfg.ias) - 1;
	करोमुख्य->geometry.क्रमce_aperture = true;

	क्रम (i = 0; i < fwspec->num_ids; i++) अणु
		काष्ठा qcom_iommu_ctx *ctx = to_ctx(qcom_करोमुख्य, fwspec->ids[i]);

		अगर (!ctx->secure_init) अणु
			ret = qcom_scm_restore_sec_cfg(qcom_iommu->sec_id, ctx->asid);
			अगर (ret) अणु
				dev_err(qcom_iommu->dev, "secure init failed: %d\n", ret);
				जाओ out_clear_iommu;
			पूर्ण
			ctx->secure_init = true;
		पूर्ण

		/* TTBRs */
		iommu_ग_लिखोq(ctx, ARM_SMMU_CB_TTBR0,
				pgtbl_cfg.arm_lpae_s1_cfg.ttbr |
				FIELD_PREP(ARM_SMMU_TTBRn_ASID, ctx->asid));
		iommu_ग_लिखोq(ctx, ARM_SMMU_CB_TTBR1, 0);

		/* TCR */
		iommu_ग_लिखोl(ctx, ARM_SMMU_CB_TCR2,
				arm_smmu_lpae_tcr2(&pgtbl_cfg));
		iommu_ग_लिखोl(ctx, ARM_SMMU_CB_TCR,
			     arm_smmu_lpae_tcr(&pgtbl_cfg) | ARM_SMMU_TCR_EAE);

		/* MAIRs (stage-1 only) */
		iommu_ग_लिखोl(ctx, ARM_SMMU_CB_S1_MAIR0,
				pgtbl_cfg.arm_lpae_s1_cfg.mair);
		iommu_ग_लिखोl(ctx, ARM_SMMU_CB_S1_MAIR1,
				pgtbl_cfg.arm_lpae_s1_cfg.mair >> 32);

		/* SCTLR */
		reg = ARM_SMMU_SCTLR_CFIE | ARM_SMMU_SCTLR_CFRE |
		      ARM_SMMU_SCTLR_AFE | ARM_SMMU_SCTLR_TRE |
		      ARM_SMMU_SCTLR_M | ARM_SMMU_SCTLR_S1_ASIDPNE |
		      ARM_SMMU_SCTLR_CFCFG;

		अगर (IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
			reg |= ARM_SMMU_SCTLR_E;

		iommu_ग_लिखोl(ctx, ARM_SMMU_CB_SCTLR, reg);

		ctx->करोमुख्य = करोमुख्य;
	पूर्ण

	mutex_unlock(&qcom_करोमुख्य->init_mutex);

	/* Publish page table ops क्रम map/unmap */
	qcom_करोमुख्य->pgtbl_ops = pgtbl_ops;

	वापस 0;

out_clear_iommu:
	qcom_करोमुख्य->iommu = शून्य;
out_unlock:
	mutex_unlock(&qcom_करोमुख्य->init_mutex);
	वापस ret;
पूर्ण

अटल काष्ठा iommu_करोमुख्य *qcom_iommu_करोमुख्य_alloc(अचिन्हित type)
अणु
	काष्ठा qcom_iommu_करोमुख्य *qcom_करोमुख्य;

	अगर (type != IOMMU_DOMAIN_UNMANAGED && type != IOMMU_DOMAIN_DMA)
		वापस शून्य;
	/*
	 * Allocate the करोमुख्य and initialise some of its data काष्ठाures.
	 * We can't really do anything meaningful until we've added a
	 * master.
	 */
	qcom_करोमुख्य = kzalloc(माप(*qcom_करोमुख्य), GFP_KERNEL);
	अगर (!qcom_करोमुख्य)
		वापस शून्य;

	अगर (type == IOMMU_DOMAIN_DMA &&
	    iommu_get_dma_cookie(&qcom_करोमुख्य->करोमुख्य)) अणु
		kमुक्त(qcom_करोमुख्य);
		वापस शून्य;
	पूर्ण

	mutex_init(&qcom_करोमुख्य->init_mutex);
	spin_lock_init(&qcom_करोमुख्य->pgtbl_lock);

	वापस &qcom_करोमुख्य->करोमुख्य;
पूर्ण

अटल व्योम qcom_iommu_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा qcom_iommu_करोमुख्य *qcom_करोमुख्य = to_qcom_iommu_करोमुख्य(करोमुख्य);

	iommu_put_dma_cookie(करोमुख्य);

	अगर (qcom_करोमुख्य->iommu) अणु
		/*
		 * NOTE: unmap can be called after client device is घातered
		 * off, क्रम example, with GPUs or anything involving dma-buf.
		 * So we cannot rely on the device_link.  Make sure the IOMMU
		 * is on to aव्योम unघड़ीed accesses in the TLB inv path:
		 */
		pm_runसमय_get_sync(qcom_करोमुख्य->iommu->dev);
		मुक्त_io_pgtable_ops(qcom_करोमुख्य->pgtbl_ops);
		pm_runसमय_put_sync(qcom_करोमुख्य->iommu->dev);
	पूर्ण

	kमुक्त(qcom_करोमुख्य);
पूर्ण

अटल पूर्णांक qcom_iommu_attach_dev(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	काष्ठा qcom_iommu_dev *qcom_iommu = to_iommu(dev);
	काष्ठा qcom_iommu_करोमुख्य *qcom_करोमुख्य = to_qcom_iommu_करोमुख्य(करोमुख्य);
	पूर्णांक ret;

	अगर (!qcom_iommu) अणु
		dev_err(dev, "cannot attach to IOMMU, is it on the same bus?\n");
		वापस -ENXIO;
	पूर्ण

	/* Ensure that the करोमुख्य is finalized */
	pm_runसमय_get_sync(qcom_iommu->dev);
	ret = qcom_iommu_init_करोमुख्य(करोमुख्य, qcom_iommu, dev);
	pm_runसमय_put_sync(qcom_iommu->dev);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Sanity check the करोमुख्य. We करोn't support करोमुख्यs across
	 * dअगरferent IOMMUs.
	 */
	अगर (qcom_करोमुख्य->iommu != qcom_iommu) अणु
		dev_err(dev, "cannot attach to IOMMU %s while already "
			"attached to domain on IOMMU %s\n",
			dev_name(qcom_करोमुख्य->iommu->dev),
			dev_name(qcom_iommu->dev));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qcom_iommu_detach_dev(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	काष्ठा qcom_iommu_करोमुख्य *qcom_करोमुख्य = to_qcom_iommu_करोमुख्य(करोमुख्य);
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	काष्ठा qcom_iommu_dev *qcom_iommu = to_iommu(dev);
	अचिन्हित i;

	अगर (WARN_ON(!qcom_करोमुख्य->iommu))
		वापस;

	pm_runसमय_get_sync(qcom_iommu->dev);
	क्रम (i = 0; i < fwspec->num_ids; i++) अणु
		काष्ठा qcom_iommu_ctx *ctx = to_ctx(qcom_करोमुख्य, fwspec->ids[i]);

		/* Disable the context bank: */
		iommu_ग_लिखोl(ctx, ARM_SMMU_CB_SCTLR, 0);

		ctx->करोमुख्य = शून्य;
	पूर्ण
	pm_runसमय_put_sync(qcom_iommu->dev);
पूर्ण

अटल पूर्णांक qcom_iommu_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			  phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot, gfp_t gfp)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	काष्ठा qcom_iommu_करोमुख्य *qcom_करोमुख्य = to_qcom_iommu_करोमुख्य(करोमुख्य);
	काष्ठा io_pgtable_ops *ops = qcom_करोमुख्य->pgtbl_ops;

	अगर (!ops)
		वापस -ENODEV;

	spin_lock_irqsave(&qcom_करोमुख्य->pgtbl_lock, flags);
	ret = ops->map(ops, iova, paddr, size, prot, GFP_ATOMIC);
	spin_unlock_irqrestore(&qcom_करोमुख्य->pgtbl_lock, flags);
	वापस ret;
पूर्ण

अटल माप_प्रकार qcom_iommu_unmap(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			       माप_प्रकार size, काष्ठा iommu_iotlb_gather *gather)
अणु
	माप_प्रकार ret;
	अचिन्हित दीर्घ flags;
	काष्ठा qcom_iommu_करोमुख्य *qcom_करोमुख्य = to_qcom_iommu_करोमुख्य(करोमुख्य);
	काष्ठा io_pgtable_ops *ops = qcom_करोमुख्य->pgtbl_ops;

	अगर (!ops)
		वापस 0;

	/* NOTE: unmap can be called after client device is घातered off,
	 * क्रम example, with GPUs or anything involving dma-buf.  So we
	 * cannot rely on the device_link.  Make sure the IOMMU is on to
	 * aव्योम unघड़ीed accesses in the TLB inv path:
	 */
	pm_runसमय_get_sync(qcom_करोमुख्य->iommu->dev);
	spin_lock_irqsave(&qcom_करोमुख्य->pgtbl_lock, flags);
	ret = ops->unmap(ops, iova, size, gather);
	spin_unlock_irqrestore(&qcom_करोमुख्य->pgtbl_lock, flags);
	pm_runसमय_put_sync(qcom_करोमुख्य->iommu->dev);

	वापस ret;
पूर्ण

अटल व्योम qcom_iommu_flush_iotlb_all(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा qcom_iommu_करोमुख्य *qcom_करोमुख्य = to_qcom_iommu_करोमुख्य(करोमुख्य);
	काष्ठा io_pgtable *pgtable = container_of(qcom_करोमुख्य->pgtbl_ops,
						  काष्ठा io_pgtable, ops);
	अगर (!qcom_करोमुख्य->pgtbl_ops)
		वापस;

	pm_runसमय_get_sync(qcom_करोमुख्य->iommu->dev);
	qcom_iommu_tlb_sync(pgtable->cookie);
	pm_runसमय_put_sync(qcom_करोमुख्य->iommu->dev);
पूर्ण

अटल व्योम qcom_iommu_iotlb_sync(काष्ठा iommu_करोमुख्य *करोमुख्य,
				  काष्ठा iommu_iotlb_gather *gather)
अणु
	qcom_iommu_flush_iotlb_all(करोमुख्य);
पूर्ण

अटल phys_addr_t qcom_iommu_iova_to_phys(काष्ठा iommu_करोमुख्य *करोमुख्य,
					   dma_addr_t iova)
अणु
	phys_addr_t ret;
	अचिन्हित दीर्घ flags;
	काष्ठा qcom_iommu_करोमुख्य *qcom_करोमुख्य = to_qcom_iommu_करोमुख्य(करोमुख्य);
	काष्ठा io_pgtable_ops *ops = qcom_करोमुख्य->pgtbl_ops;

	अगर (!ops)
		वापस 0;

	spin_lock_irqsave(&qcom_करोमुख्य->pgtbl_lock, flags);
	ret = ops->iova_to_phys(ops, iova);
	spin_unlock_irqrestore(&qcom_करोमुख्य->pgtbl_lock, flags);

	वापस ret;
पूर्ण

अटल bool qcom_iommu_capable(क्रमागत iommu_cap cap)
अणु
	चयन (cap) अणु
	हाल IOMMU_CAP_CACHE_COHERENCY:
		/*
		 * Return true here as the SMMU can always send out coherent
		 * requests.
		 */
		वापस true;
	हाल IOMMU_CAP_NOEXEC:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल काष्ठा iommu_device *qcom_iommu_probe_device(काष्ठा device *dev)
अणु
	काष्ठा qcom_iommu_dev *qcom_iommu = to_iommu(dev);
	काष्ठा device_link *link;

	अगर (!qcom_iommu)
		वापस ERR_PTR(-ENODEV);

	/*
	 * Establish the link between iommu and master, so that the
	 * iommu माला_लो runसमय enabled/disabled as per the master's
	 * needs.
	 */
	link = device_link_add(dev, qcom_iommu->dev, DL_FLAG_PM_RUNTIME);
	अगर (!link) अणु
		dev_err(qcom_iommu->dev, "Unable to create device link between %s and %s\n",
			dev_name(qcom_iommu->dev), dev_name(dev));
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	वापस &qcom_iommu->iommu;
पूर्ण

अटल व्योम qcom_iommu_release_device(काष्ठा device *dev)
अणु
	काष्ठा qcom_iommu_dev *qcom_iommu = to_iommu(dev);

	अगर (!qcom_iommu)
		वापस;

	iommu_fwspec_मुक्त(dev);
पूर्ण

अटल पूर्णांक qcom_iommu_of_xlate(काष्ठा device *dev, काष्ठा of_phandle_args *args)
अणु
	काष्ठा qcom_iommu_dev *qcom_iommu;
	काष्ठा platक्रमm_device *iommu_pdev;
	अचिन्हित asid = args->args[0];

	अगर (args->args_count != 1) अणु
		dev_err(dev, "incorrect number of iommu params found for %s "
			"(found %d, expected 1)\n",
			args->np->full_name, args->args_count);
		वापस -EINVAL;
	पूर्ण

	iommu_pdev = of_find_device_by_node(args->np);
	अगर (WARN_ON(!iommu_pdev))
		वापस -EINVAL;

	qcom_iommu = platक्रमm_get_drvdata(iommu_pdev);

	/* make sure the asid specअगरied in dt is valid, so we करोn't have
	 * to sanity check this अन्यथाwhere, since 'asid - 1' is used to
	 * index पूर्णांकo qcom_iommu->ctxs:
	 */
	अगर (WARN_ON(asid < 1) ||
	    WARN_ON(asid > qcom_iommu->num_ctxs)) अणु
		put_device(&iommu_pdev->dev);
		वापस -EINVAL;
	पूर्ण

	अगर (!dev_iommu_priv_get(dev)) अणु
		dev_iommu_priv_set(dev, qcom_iommu);
	पूर्ण अन्यथा अणु
		/* make sure devices iommus dt node isn't referring to
		 * multiple dअगरferent iommu devices.  Multiple context
		 * banks are ok, but multiple devices are not:
		 */
		अगर (WARN_ON(qcom_iommu != dev_iommu_priv_get(dev))) अणु
			put_device(&iommu_pdev->dev);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस iommu_fwspec_add_ids(dev, &asid, 1);
पूर्ण

अटल स्थिर काष्ठा iommu_ops qcom_iommu_ops = अणु
	.capable	= qcom_iommu_capable,
	.करोमुख्य_alloc	= qcom_iommu_करोमुख्य_alloc,
	.करोमुख्य_मुक्त	= qcom_iommu_करोमुख्य_मुक्त,
	.attach_dev	= qcom_iommu_attach_dev,
	.detach_dev	= qcom_iommu_detach_dev,
	.map		= qcom_iommu_map,
	.unmap		= qcom_iommu_unmap,
	.flush_iotlb_all = qcom_iommu_flush_iotlb_all,
	.iotlb_sync	= qcom_iommu_iotlb_sync,
	.iova_to_phys	= qcom_iommu_iova_to_phys,
	.probe_device	= qcom_iommu_probe_device,
	.release_device	= qcom_iommu_release_device,
	.device_group	= generic_device_group,
	.of_xlate	= qcom_iommu_of_xlate,
	.pgsize_biपंचांगap	= SZ_4K | SZ_64K | SZ_1M | SZ_16M,
पूर्ण;

अटल पूर्णांक qcom_iommu_sec_ptbl_init(काष्ठा device *dev)
अणु
	माप_प्रकार psize = 0;
	अचिन्हित पूर्णांक spare = 0;
	व्योम *cpu_addr;
	dma_addr_t paddr;
	अचिन्हित दीर्घ attrs;
	अटल bool allocated = false;
	पूर्णांक ret;

	अगर (allocated)
		वापस 0;

	ret = qcom_scm_iommu_secure_ptbl_size(spare, &psize);
	अगर (ret) अणु
		dev_err(dev, "failed to get iommu secure pgtable size (%d)\n",
			ret);
		वापस ret;
	पूर्ण

	dev_info(dev, "iommu sec: pgtable size: %zu\n", psize);

	attrs = DMA_ATTR_NO_KERNEL_MAPPING;

	cpu_addr = dma_alloc_attrs(dev, psize, &paddr, GFP_KERNEL, attrs);
	अगर (!cpu_addr) अणु
		dev_err(dev, "failed to allocate %zu bytes for pgtable\n",
			psize);
		वापस -ENOMEM;
	पूर्ण

	ret = qcom_scm_iommu_secure_ptbl_init(paddr, psize, spare);
	अगर (ret) अणु
		dev_err(dev, "failed to init iommu pgtable (%d)\n", ret);
		जाओ मुक्त_mem;
	पूर्ण

	allocated = true;
	वापस 0;

मुक्त_mem:
	dma_मुक्त_attrs(dev, psize, cpu_addr, paddr, attrs);
	वापस ret;
पूर्ण

अटल पूर्णांक get_asid(स्थिर काष्ठा device_node *np)
अणु
	u32 reg;

	/* पढ़ो the "reg" property directly to get the relative address
	 * of the context bank, and calculate the asid from that:
	 */
	अगर (of_property_पढ़ो_u32_index(np, "reg", 0, &reg))
		वापस -ENODEV;

	वापस reg / 0x1000;      /* context banks are 0x1000 apart */
पूर्ण

अटल पूर्णांक qcom_iommu_ctx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_iommu_ctx *ctx;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा qcom_iommu_dev *qcom_iommu = dev_get_drvdata(dev->parent);
	काष्ठा resource *res;
	पूर्णांक ret, irq;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->dev = dev;
	platक्रमm_set_drvdata(pdev, ctx);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ctx->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ctx->base))
		वापस PTR_ERR(ctx->base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -ENODEV;

	/* clear IRQs beक्रमe रेजिस्टरing fault handler, just in हाल the
	 * boot-loader left us a surprise:
	 */
	iommu_ग_लिखोl(ctx, ARM_SMMU_CB_FSR, iommu_पढ़ोl(ctx, ARM_SMMU_CB_FSR));

	ret = devm_request_irq(dev, irq,
			       qcom_iommu_fault,
			       IRQF_SHARED,
			       "qcom-iommu-fault",
			       ctx);
	अगर (ret) अणु
		dev_err(dev, "failed to request IRQ %u\n", irq);
		वापस ret;
	पूर्ण

	ret = get_asid(dev->of_node);
	अगर (ret < 0) अणु
		dev_err(dev, "missing reg property\n");
		वापस ret;
	पूर्ण

	ctx->asid = ret;

	dev_dbg(dev, "found asid %u\n", ctx->asid);

	qcom_iommu->ctxs[ctx->asid - 1] = ctx;

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_iommu_ctx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_iommu_dev *qcom_iommu = dev_get_drvdata(pdev->dev.parent);
	काष्ठा qcom_iommu_ctx *ctx = platक्रमm_get_drvdata(pdev);

	platक्रमm_set_drvdata(pdev, शून्य);

	qcom_iommu->ctxs[ctx->asid - 1] = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ctx_of_match[] = अणु
	अणु .compatible = "qcom,msm-iommu-v1-ns" पूर्ण,
	अणु .compatible = "qcom,msm-iommu-v1-sec" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver qcom_iommu_ctx_driver = अणु
	.driver	= अणु
		.name		= "qcom-iommu-ctx",
		.of_match_table	= ctx_of_match,
	पूर्ण,
	.probe	= qcom_iommu_ctx_probe,
	.हटाओ = qcom_iommu_ctx_हटाओ,
पूर्ण;

अटल bool qcom_iommu_has_secure_context(काष्ठा qcom_iommu_dev *qcom_iommu)
अणु
	काष्ठा device_node *child;

	क्रम_each_child_of_node(qcom_iommu->dev->of_node, child)
		अगर (of_device_is_compatible(child, "qcom,msm-iommu-v1-sec"))
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक qcom_iommu_device_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *child;
	काष्ठा qcom_iommu_dev *qcom_iommu;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा clk *clk;
	पूर्णांक ret, max_asid = 0;

	/* find the max asid (which is 1:1 to ctx bank idx), so we know how
	 * many child ctx devices we have:
	 */
	क्रम_each_child_of_node(dev->of_node, child)
		max_asid = max(max_asid, get_asid(child));

	qcom_iommu = devm_kzalloc(dev, काष्ठा_size(qcom_iommu, ctxs, max_asid),
				  GFP_KERNEL);
	अगर (!qcom_iommu)
		वापस -ENOMEM;
	qcom_iommu->num_ctxs = max_asid;
	qcom_iommu->dev = dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res) अणु
		qcom_iommu->local_base = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(qcom_iommu->local_base))
			वापस PTR_ERR(qcom_iommu->local_base);
	पूर्ण

	clk = devm_clk_get(dev, "iface");
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "failed to get iface clock\n");
		वापस PTR_ERR(clk);
	पूर्ण
	qcom_iommu->clks[CLK_IFACE].clk = clk;

	clk = devm_clk_get(dev, "bus");
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "failed to get bus clock\n");
		वापस PTR_ERR(clk);
	पूर्ण
	qcom_iommu->clks[CLK_BUS].clk = clk;

	clk = devm_clk_get_optional(dev, "tbu");
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "failed to get tbu clock\n");
		वापस PTR_ERR(clk);
	पूर्ण
	qcom_iommu->clks[CLK_TBU].clk = clk;

	अगर (of_property_पढ़ो_u32(dev->of_node, "qcom,iommu-secure-id",
				 &qcom_iommu->sec_id)) अणु
		dev_err(dev, "missing qcom,iommu-secure-id property\n");
		वापस -ENODEV;
	पूर्ण

	अगर (qcom_iommu_has_secure_context(qcom_iommu)) अणु
		ret = qcom_iommu_sec_ptbl_init(dev);
		अगर (ret) अणु
			dev_err(dev, "cannot init secure pg table(%d)\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, qcom_iommu);

	pm_runसमय_enable(dev);

	/* रेजिस्टर context bank devices, which are child nodes: */
	ret = devm_of_platक्रमm_populate(dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to populate iommu contexts\n");
		वापस ret;
	पूर्ण

	ret = iommu_device_sysfs_add(&qcom_iommu->iommu, dev, शून्य,
				     dev_name(dev));
	अगर (ret) अणु
		dev_err(dev, "Failed to register iommu in sysfs\n");
		वापस ret;
	पूर्ण

	ret = iommu_device_रेजिस्टर(&qcom_iommu->iommu, &qcom_iommu_ops, dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to register iommu\n");
		वापस ret;
	पूर्ण

	bus_set_iommu(&platक्रमm_bus_type, &qcom_iommu_ops);

	अगर (qcom_iommu->local_base) अणु
		pm_runसमय_get_sync(dev);
		ग_लिखोl_relaxed(0xffffffff, qcom_iommu->local_base + SMMU_INTR_SEL_NS);
		pm_runसमय_put_sync(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_iommu_device_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_iommu_dev *qcom_iommu = platक्रमm_get_drvdata(pdev);

	bus_set_iommu(&platक्रमm_bus_type, शून्य);

	pm_runसमय_क्रमce_suspend(&pdev->dev);
	platक्रमm_set_drvdata(pdev, शून्य);
	iommu_device_sysfs_हटाओ(&qcom_iommu->iommu);
	iommu_device_unरेजिस्टर(&qcom_iommu->iommu);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused qcom_iommu_resume(काष्ठा device *dev)
अणु
	काष्ठा qcom_iommu_dev *qcom_iommu = dev_get_drvdata(dev);

	वापस clk_bulk_prepare_enable(CLK_NUM, qcom_iommu->clks);
पूर्ण

अटल पूर्णांक __maybe_unused qcom_iommu_suspend(काष्ठा device *dev)
अणु
	काष्ठा qcom_iommu_dev *qcom_iommu = dev_get_drvdata(dev);

	clk_bulk_disable_unprepare(CLK_NUM, qcom_iommu->clks);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops qcom_iommu_pm_ops = अणु
	SET_RUNTIME_PM_OPS(qcom_iommu_suspend, qcom_iommu_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id qcom_iommu_of_match[] = अणु
	अणु .compatible = "qcom,msm-iommu-v1" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver qcom_iommu_driver = अणु
	.driver	= अणु
		.name		= "qcom-iommu",
		.of_match_table	= qcom_iommu_of_match,
		.pm		= &qcom_iommu_pm_ops,
	पूर्ण,
	.probe	= qcom_iommu_device_probe,
	.हटाओ	= qcom_iommu_device_हटाओ,
पूर्ण;

अटल पूर्णांक __init qcom_iommu_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&qcom_iommu_ctx_driver);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&qcom_iommu_driver);
	अगर (ret)
		platक्रमm_driver_unरेजिस्टर(&qcom_iommu_ctx_driver);

	वापस ret;
पूर्ण
device_initcall(qcom_iommu_init);
