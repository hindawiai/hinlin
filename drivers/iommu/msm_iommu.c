<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2010-2011, Code Aurora Forum. All rights reserved.
 *
 * Author: Stepan Moskovchenko <stepanm@codeaurora.org>
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/io-pgtable.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/iommu.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/of_iommu.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/sizes.h>

#समावेश "msm_iommu_hw-8xxx.h"
#समावेश "msm_iommu.h"

#घोषणा MRC(reg, processor, op1, crn, crm, op2)				\
__यंत्र__ __अस्थिर__ (							\
"   mrc   "   #processor "," #op1 ", %0,"  #crn "," #crm "," #op2 "\n"  \
: "=r" (reg))

/* biपंचांगap of the page sizes currently supported */
#घोषणा MSM_IOMMU_PGSIZES	(SZ_4K | SZ_64K | SZ_1M | SZ_16M)

अटल DEFINE_SPINLOCK(msm_iommu_lock);
अटल LIST_HEAD(qcom_iommu_devices);
अटल काष्ठा iommu_ops msm_iommu_ops;

काष्ठा msm_priv अणु
	काष्ठा list_head list_attached;
	काष्ठा iommu_करोमुख्य करोमुख्य;
	काष्ठा io_pgtable_cfg	cfg;
	काष्ठा io_pgtable_ops	*iop;
	काष्ठा device		*dev;
	spinlock_t		pgtlock; /* pagetable lock */
पूर्ण;

अटल काष्ठा msm_priv *to_msm_priv(काष्ठा iommu_करोमुख्य *करोm)
अणु
	वापस container_of(करोm, काष्ठा msm_priv, करोमुख्य);
पूर्ण

अटल पूर्णांक __enable_घड़ीs(काष्ठा msm_iommu_dev *iommu)
अणु
	पूर्णांक ret;

	ret = clk_enable(iommu->pclk);
	अगर (ret)
		जाओ fail;

	अगर (iommu->clk) अणु
		ret = clk_enable(iommu->clk);
		अगर (ret)
			clk_disable(iommu->pclk);
	पूर्ण
fail:
	वापस ret;
पूर्ण

अटल व्योम __disable_घड़ीs(काष्ठा msm_iommu_dev *iommu)
अणु
	अगर (iommu->clk)
		clk_disable(iommu->clk);
	clk_disable(iommu->pclk);
पूर्ण

अटल व्योम msm_iommu_reset(व्योम __iomem *base, पूर्णांक ncb)
अणु
	पूर्णांक ctx;

	SET_RPUE(base, 0);
	SET_RPUEIE(base, 0);
	SET_ESRRESTORE(base, 0);
	SET_TBE(base, 0);
	SET_CR(base, 0);
	SET_SPDMBE(base, 0);
	SET_TESTBUSCR(base, 0);
	SET_TLBRSW(base, 0);
	SET_GLOBAL_TLBIALL(base, 0);
	SET_RPU_ACR(base, 0);
	SET_TLBLKCRWE(base, 1);

	क्रम (ctx = 0; ctx < ncb; ctx++) अणु
		SET_BPRCOSH(base, ctx, 0);
		SET_BPRCISH(base, ctx, 0);
		SET_BPRCNSH(base, ctx, 0);
		SET_BPSHCFG(base, ctx, 0);
		SET_BPMTCFG(base, ctx, 0);
		SET_ACTLR(base, ctx, 0);
		SET_SCTLR(base, ctx, 0);
		SET_FSRRESTORE(base, ctx, 0);
		SET_TTBR0(base, ctx, 0);
		SET_TTBR1(base, ctx, 0);
		SET_TTBCR(base, ctx, 0);
		SET_BFBCR(base, ctx, 0);
		SET_PAR(base, ctx, 0);
		SET_FAR(base, ctx, 0);
		SET_CTX_TLBIALL(base, ctx, 0);
		SET_TLBFLPTER(base, ctx, 0);
		SET_TLBSLPTER(base, ctx, 0);
		SET_TLBLKCR(base, ctx, 0);
		SET_CONTEXTIDR(base, ctx, 0);
	पूर्ण
पूर्ण

अटल व्योम __flush_iotlb(व्योम *cookie)
अणु
	काष्ठा msm_priv *priv = cookie;
	काष्ठा msm_iommu_dev *iommu = शून्य;
	काष्ठा msm_iommu_ctx_dev *master;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(iommu, &priv->list_attached, करोm_node) अणु
		ret = __enable_घड़ीs(iommu);
		अगर (ret)
			जाओ fail;

		list_क्रम_each_entry(master, &iommu->ctx_list, list)
			SET_CTX_TLBIALL(iommu->base, master->num, 0);

		__disable_घड़ीs(iommu);
	पूर्ण
fail:
	वापस;
पूर्ण

अटल व्योम __flush_iotlb_range(अचिन्हित दीर्घ iova, माप_प्रकार size,
				माप_प्रकार granule, bool leaf, व्योम *cookie)
अणु
	काष्ठा msm_priv *priv = cookie;
	काष्ठा msm_iommu_dev *iommu = शून्य;
	काष्ठा msm_iommu_ctx_dev *master;
	पूर्णांक ret = 0;
	पूर्णांक temp_size;

	list_क्रम_each_entry(iommu, &priv->list_attached, करोm_node) अणु
		ret = __enable_घड़ीs(iommu);
		अगर (ret)
			जाओ fail;

		list_क्रम_each_entry(master, &iommu->ctx_list, list) अणु
			temp_size = size;
			करो अणु
				iova &= TLBIVA_VA;
				iova |= GET_CONTEXTIDR_ASID(iommu->base,
							    master->num);
				SET_TLBIVA(iommu->base, master->num, iova);
				iova += granule;
			पूर्ण जबतक (temp_size -= granule);
		पूर्ण

		__disable_घड़ीs(iommu);
	पूर्ण

fail:
	वापस;
पूर्ण

अटल व्योम __flush_iotlb_walk(अचिन्हित दीर्घ iova, माप_प्रकार size,
			       माप_प्रकार granule, व्योम *cookie)
अणु
	__flush_iotlb_range(iova, size, granule, false, cookie);
पूर्ण

अटल व्योम __flush_iotlb_page(काष्ठा iommu_iotlb_gather *gather,
			       अचिन्हित दीर्घ iova, माप_प्रकार granule, व्योम *cookie)
अणु
	__flush_iotlb_range(iova, granule, granule, true, cookie);
पूर्ण

अटल स्थिर काष्ठा iommu_flush_ops msm_iommu_flush_ops = अणु
	.tlb_flush_all = __flush_iotlb,
	.tlb_flush_walk = __flush_iotlb_walk,
	.tlb_add_page = __flush_iotlb_page,
पूर्ण;

अटल पूर्णांक msm_iommu_alloc_ctx(अचिन्हित दीर्घ *map, पूर्णांक start, पूर्णांक end)
अणु
	पूर्णांक idx;

	करो अणु
		idx = find_next_zero_bit(map, end, start);
		अगर (idx == end)
			वापस -ENOSPC;
	पूर्ण जबतक (test_and_set_bit(idx, map));

	वापस idx;
पूर्ण

अटल व्योम msm_iommu_मुक्त_ctx(अचिन्हित दीर्घ *map, पूर्णांक idx)
अणु
	clear_bit(idx, map);
पूर्ण

अटल व्योम config_mids(काष्ठा msm_iommu_dev *iommu,
			काष्ठा msm_iommu_ctx_dev *master)
अणु
	पूर्णांक mid, ctx, i;

	क्रम (i = 0; i < master->num_mids; i++) अणु
		mid = master->mids[i];
		ctx = master->num;

		SET_M2VCBR_N(iommu->base, mid, 0);
		SET_CBACR_N(iommu->base, ctx, 0);

		/* Set VMID = 0 */
		SET_VMID(iommu->base, mid, 0);

		/* Set the context number क्रम that MID to this context */
		SET_CBNDX(iommu->base, mid, ctx);

		/* Set MID associated with this context bank to 0*/
		SET_CBVMID(iommu->base, ctx, 0);

		/* Set the ASID क्रम TLB tagging क्रम this context */
		SET_CONTEXTIDR_ASID(iommu->base, ctx, ctx);

		/* Set security bit override to be Non-secure */
		SET_NSCFG(iommu->base, mid, 3);
	पूर्ण
पूर्ण

अटल व्योम __reset_context(व्योम __iomem *base, पूर्णांक ctx)
अणु
	SET_BPRCOSH(base, ctx, 0);
	SET_BPRCISH(base, ctx, 0);
	SET_BPRCNSH(base, ctx, 0);
	SET_BPSHCFG(base, ctx, 0);
	SET_BPMTCFG(base, ctx, 0);
	SET_ACTLR(base, ctx, 0);
	SET_SCTLR(base, ctx, 0);
	SET_FSRRESTORE(base, ctx, 0);
	SET_TTBR0(base, ctx, 0);
	SET_TTBR1(base, ctx, 0);
	SET_TTBCR(base, ctx, 0);
	SET_BFBCR(base, ctx, 0);
	SET_PAR(base, ctx, 0);
	SET_FAR(base, ctx, 0);
	SET_CTX_TLBIALL(base, ctx, 0);
	SET_TLBFLPTER(base, ctx, 0);
	SET_TLBSLPTER(base, ctx, 0);
	SET_TLBLKCR(base, ctx, 0);
पूर्ण

अटल व्योम __program_context(व्योम __iomem *base, पूर्णांक ctx,
			      काष्ठा msm_priv *priv)
अणु
	__reset_context(base, ctx);

	/* Turn on TEX Remap */
	SET_TRE(base, ctx, 1);
	SET_AFE(base, ctx, 1);

	/* Set up HTW mode */
	/* TLB miss configuration: perक्रमm HTW on miss */
	SET_TLBMCFG(base, ctx, 0x3);

	/* V2P configuration: HTW क्रम access */
	SET_V2PCFG(base, ctx, 0x3);

	SET_TTBCR(base, ctx, priv->cfg.arm_v7s_cfg.tcr);
	SET_TTBR0(base, ctx, priv->cfg.arm_v7s_cfg.ttbr);
	SET_TTBR1(base, ctx, 0);

	/* Set prrr and nmrr */
	SET_PRRR(base, ctx, priv->cfg.arm_v7s_cfg.prrr);
	SET_NMRR(base, ctx, priv->cfg.arm_v7s_cfg.nmrr);

	/* Invalidate the TLB क्रम this context */
	SET_CTX_TLBIALL(base, ctx, 0);

	/* Set पूर्णांकerrupt number to "secure" पूर्णांकerrupt */
	SET_IRPTNDX(base, ctx, 0);

	/* Enable context fault पूर्णांकerrupt */
	SET_CFEIE(base, ctx, 1);

	/* Stall access on a context fault and let the handler deal with it */
	SET_CFCFG(base, ctx, 1);

	/* Redirect all cacheable requests to L2 slave port. */
	SET_RCISH(base, ctx, 1);
	SET_RCOSH(base, ctx, 1);
	SET_RCNSH(base, ctx, 1);

	/* Turn on BFB prefetch */
	SET_BFBDFE(base, ctx, 1);

	/* Enable the MMU */
	SET_M(base, ctx, 1);
पूर्ण

अटल काष्ठा iommu_करोमुख्य *msm_iommu_करोमुख्य_alloc(अचिन्हित type)
अणु
	काष्ठा msm_priv *priv;

	अगर (type != IOMMU_DOMAIN_UNMANAGED)
		वापस शून्य;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		जाओ fail_nomem;

	INIT_LIST_HEAD(&priv->list_attached);

	priv->करोमुख्य.geometry.aperture_start = 0;
	priv->करोमुख्य.geometry.aperture_end   = (1ULL << 32) - 1;
	priv->करोमुख्य.geometry.क्रमce_aperture = true;

	वापस &priv->करोमुख्य;

fail_nomem:
	kमुक्त(priv);
	वापस शून्य;
पूर्ण

अटल व्योम msm_iommu_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा msm_priv *priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&msm_iommu_lock, flags);
	priv = to_msm_priv(करोमुख्य);
	kमुक्त(priv);
	spin_unlock_irqrestore(&msm_iommu_lock, flags);
पूर्ण

अटल पूर्णांक msm_iommu_करोमुख्य_config(काष्ठा msm_priv *priv)
अणु
	spin_lock_init(&priv->pgtlock);

	priv->cfg = (काष्ठा io_pgtable_cfg) अणु
		.pgsize_biपंचांगap = msm_iommu_ops.pgsize_biपंचांगap,
		.ias = 32,
		.oas = 32,
		.tlb = &msm_iommu_flush_ops,
		.iommu_dev = priv->dev,
	पूर्ण;

	priv->iop = alloc_io_pgtable_ops(ARM_V7S, &priv->cfg, priv);
	अगर (!priv->iop) अणु
		dev_err(priv->dev, "Failed to allocate pgtable\n");
		वापस -EINVAL;
	पूर्ण

	msm_iommu_ops.pgsize_biपंचांगap = priv->cfg.pgsize_biपंचांगap;

	वापस 0;
पूर्ण

/* Must be called under msm_iommu_lock */
अटल काष्ठा msm_iommu_dev *find_iommu_क्रम_dev(काष्ठा device *dev)
अणु
	काष्ठा msm_iommu_dev *iommu, *ret = शून्य;
	काष्ठा msm_iommu_ctx_dev *master;

	list_क्रम_each_entry(iommu, &qcom_iommu_devices, dev_node) अणु
		master = list_first_entry(&iommu->ctx_list,
					  काष्ठा msm_iommu_ctx_dev,
					  list);
		अगर (master->of_node == dev->of_node) अणु
			ret = iommu;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा iommu_device *msm_iommu_probe_device(काष्ठा device *dev)
अणु
	काष्ठा msm_iommu_dev *iommu;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&msm_iommu_lock, flags);
	iommu = find_iommu_क्रम_dev(dev);
	spin_unlock_irqrestore(&msm_iommu_lock, flags);

	अगर (!iommu)
		वापस ERR_PTR(-ENODEV);

	वापस &iommu->iommu;
पूर्ण

अटल व्योम msm_iommu_release_device(काष्ठा device *dev)
अणु
पूर्ण

अटल पूर्णांक msm_iommu_attach_dev(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा msm_iommu_dev *iommu;
	काष्ठा msm_priv *priv = to_msm_priv(करोमुख्य);
	काष्ठा msm_iommu_ctx_dev *master;

	priv->dev = dev;
	msm_iommu_करोमुख्य_config(priv);

	spin_lock_irqsave(&msm_iommu_lock, flags);
	list_क्रम_each_entry(iommu, &qcom_iommu_devices, dev_node) अणु
		master = list_first_entry(&iommu->ctx_list,
					  काष्ठा msm_iommu_ctx_dev,
					  list);
		अगर (master->of_node == dev->of_node) अणु
			ret = __enable_घड़ीs(iommu);
			अगर (ret)
				जाओ fail;

			list_क्रम_each_entry(master, &iommu->ctx_list, list) अणु
				अगर (master->num) अणु
					dev_err(dev, "domain already attached");
					ret = -EEXIST;
					जाओ fail;
				पूर्ण
				master->num =
					msm_iommu_alloc_ctx(iommu->context_map,
							    0, iommu->ncb);
				अगर (IS_ERR_VALUE(master->num)) अणु
					ret = -ENODEV;
					जाओ fail;
				पूर्ण
				config_mids(iommu, master);
				__program_context(iommu->base, master->num,
						  priv);
			पूर्ण
			__disable_घड़ीs(iommu);
			list_add(&iommu->करोm_node, &priv->list_attached);
		पूर्ण
	पूर्ण

fail:
	spin_unlock_irqrestore(&msm_iommu_lock, flags);

	वापस ret;
पूर्ण

अटल व्योम msm_iommu_detach_dev(काष्ठा iommu_करोमुख्य *करोमुख्य,
				 काष्ठा device *dev)
अणु
	काष्ठा msm_priv *priv = to_msm_priv(करोमुख्य);
	अचिन्हित दीर्घ flags;
	काष्ठा msm_iommu_dev *iommu;
	काष्ठा msm_iommu_ctx_dev *master;
	पूर्णांक ret;

	मुक्त_io_pgtable_ops(priv->iop);

	spin_lock_irqsave(&msm_iommu_lock, flags);
	list_क्रम_each_entry(iommu, &priv->list_attached, करोm_node) अणु
		ret = __enable_घड़ीs(iommu);
		अगर (ret)
			जाओ fail;

		list_क्रम_each_entry(master, &iommu->ctx_list, list) अणु
			msm_iommu_मुक्त_ctx(iommu->context_map, master->num);
			__reset_context(iommu->base, master->num);
		पूर्ण
		__disable_घड़ीs(iommu);
	पूर्ण
fail:
	spin_unlock_irqrestore(&msm_iommu_lock, flags);
पूर्ण

अटल पूर्णांक msm_iommu_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			 phys_addr_t pa, माप_प्रकार len, पूर्णांक prot, gfp_t gfp)
अणु
	काष्ठा msm_priv *priv = to_msm_priv(करोमुख्य);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&priv->pgtlock, flags);
	ret = priv->iop->map(priv->iop, iova, pa, len, prot, GFP_ATOMIC);
	spin_unlock_irqrestore(&priv->pgtlock, flags);

	वापस ret;
पूर्ण

अटल व्योम msm_iommu_sync_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			       माप_प्रकार size)
अणु
	काष्ठा msm_priv *priv = to_msm_priv(करोमुख्य);

	__flush_iotlb_range(iova, size, SZ_4K, false, priv);
पूर्ण

अटल माप_प्रकार msm_iommu_unmap(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			      माप_प्रकार len, काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा msm_priv *priv = to_msm_priv(करोमुख्य);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->pgtlock, flags);
	len = priv->iop->unmap(priv->iop, iova, len, gather);
	spin_unlock_irqrestore(&priv->pgtlock, flags);

	वापस len;
पूर्ण

अटल phys_addr_t msm_iommu_iova_to_phys(काष्ठा iommu_करोमुख्य *करोमुख्य,
					  dma_addr_t va)
अणु
	काष्ठा msm_priv *priv;
	काष्ठा msm_iommu_dev *iommu;
	काष्ठा msm_iommu_ctx_dev *master;
	अचिन्हित पूर्णांक par;
	अचिन्हित दीर्घ flags;
	phys_addr_t ret = 0;

	spin_lock_irqsave(&msm_iommu_lock, flags);

	priv = to_msm_priv(करोमुख्य);
	iommu = list_first_entry(&priv->list_attached,
				 काष्ठा msm_iommu_dev, करोm_node);

	अगर (list_empty(&iommu->ctx_list))
		जाओ fail;

	master = list_first_entry(&iommu->ctx_list,
				  काष्ठा msm_iommu_ctx_dev, list);
	अगर (!master)
		जाओ fail;

	ret = __enable_घड़ीs(iommu);
	अगर (ret)
		जाओ fail;

	/* Invalidate context TLB */
	SET_CTX_TLBIALL(iommu->base, master->num, 0);
	SET_V2PPR(iommu->base, master->num, va & V2Pxx_VA);

	par = GET_PAR(iommu->base, master->num);

	/* We are dealing with a supersection */
	अगर (GET_NOFAULT_SS(iommu->base, master->num))
		ret = (par & 0xFF000000) | (va & 0x00FFFFFF);
	अन्यथा	/* Upper 20 bits from PAR, lower 12 from VA */
		ret = (par & 0xFFFFF000) | (va & 0x00000FFF);

	अगर (GET_FAULT(iommu->base, master->num))
		ret = 0;

	__disable_घड़ीs(iommu);
fail:
	spin_unlock_irqrestore(&msm_iommu_lock, flags);
	वापस ret;
पूर्ण

अटल bool msm_iommu_capable(क्रमागत iommu_cap cap)
अणु
	वापस false;
पूर्ण

अटल व्योम prपूर्णांक_ctx_regs(व्योम __iomem *base, पूर्णांक ctx)
अणु
	अचिन्हित पूर्णांक fsr = GET_FSR(base, ctx);
	pr_err("FAR    = %08x    PAR    = %08x\n",
	       GET_FAR(base, ctx), GET_PAR(base, ctx));
	pr_err("FSR    = %08x [%s%s%s%s%s%s%s%s%s%s]\n", fsr,
			(fsr & 0x02) ? "TF " : "",
			(fsr & 0x04) ? "AFF " : "",
			(fsr & 0x08) ? "APF " : "",
			(fsr & 0x10) ? "TLBMF " : "",
			(fsr & 0x20) ? "HTWDEEF " : "",
			(fsr & 0x40) ? "HTWSEEF " : "",
			(fsr & 0x80) ? "MHF " : "",
			(fsr & 0x10000) ? "SL " : "",
			(fsr & 0x40000000) ? "SS " : "",
			(fsr & 0x80000000) ? "MULTI " : "");

	pr_err("FSYNR0 = %08x    FSYNR1 = %08x\n",
	       GET_FSYNR0(base, ctx), GET_FSYNR1(base, ctx));
	pr_err("TTBR0  = %08x    TTBR1  = %08x\n",
	       GET_TTBR0(base, ctx), GET_TTBR1(base, ctx));
	pr_err("SCTLR  = %08x    ACTLR  = %08x\n",
	       GET_SCTLR(base, ctx), GET_ACTLR(base, ctx));
पूर्ण

अटल व्योम insert_iommu_master(काष्ठा device *dev,
				काष्ठा msm_iommu_dev **iommu,
				काष्ठा of_phandle_args *spec)
अणु
	काष्ठा msm_iommu_ctx_dev *master = dev_iommu_priv_get(dev);
	पूर्णांक sid;

	अगर (list_empty(&(*iommu)->ctx_list)) अणु
		master = kzalloc(माप(*master), GFP_ATOMIC);
		master->of_node = dev->of_node;
		list_add(&master->list, &(*iommu)->ctx_list);
		dev_iommu_priv_set(dev, master);
	पूर्ण

	क्रम (sid = 0; sid < master->num_mids; sid++)
		अगर (master->mids[sid] == spec->args[0]) अणु
			dev_warn(dev, "Stream ID 0x%hx repeated; ignoring\n",
				 sid);
			वापस;
		पूर्ण

	master->mids[master->num_mids++] = spec->args[0];
पूर्ण

अटल पूर्णांक qcom_iommu_of_xlate(काष्ठा device *dev,
			       काष्ठा of_phandle_args *spec)
अणु
	काष्ठा msm_iommu_dev *iommu;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&msm_iommu_lock, flags);
	list_क्रम_each_entry(iommu, &qcom_iommu_devices, dev_node)
		अगर (iommu->dev->of_node == spec->np)
			अवरोध;

	अगर (!iommu || iommu->dev->of_node != spec->np) अणु
		ret = -ENODEV;
		जाओ fail;
	पूर्ण

	insert_iommu_master(dev, &iommu, spec);
fail:
	spin_unlock_irqrestore(&msm_iommu_lock, flags);

	वापस ret;
पूर्ण

irqवापस_t msm_iommu_fault_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा msm_iommu_dev *iommu = dev_id;
	अचिन्हित पूर्णांक fsr;
	पूर्णांक i, ret;

	spin_lock(&msm_iommu_lock);

	अगर (!iommu) अणु
		pr_err("Invalid device ID in context interrupt handler\n");
		जाओ fail;
	पूर्ण

	pr_err("Unexpected IOMMU page fault!\n");
	pr_err("base = %08x\n", (अचिन्हित पूर्णांक)iommu->base);

	ret = __enable_घड़ीs(iommu);
	अगर (ret)
		जाओ fail;

	क्रम (i = 0; i < iommu->ncb; i++) अणु
		fsr = GET_FSR(iommu->base, i);
		अगर (fsr) अणु
			pr_err("Fault occurred in context %d.\n", i);
			pr_err("Interesting registers:\n");
			prपूर्णांक_ctx_regs(iommu->base, i);
			SET_FSR(iommu->base, i, 0x4000000F);
		पूर्ण
	पूर्ण
	__disable_घड़ीs(iommu);
fail:
	spin_unlock(&msm_iommu_lock);
	वापस 0;
पूर्ण

अटल काष्ठा iommu_ops msm_iommu_ops = अणु
	.capable = msm_iommu_capable,
	.करोमुख्य_alloc = msm_iommu_करोमुख्य_alloc,
	.करोमुख्य_मुक्त = msm_iommu_करोमुख्य_मुक्त,
	.attach_dev = msm_iommu_attach_dev,
	.detach_dev = msm_iommu_detach_dev,
	.map = msm_iommu_map,
	.unmap = msm_iommu_unmap,
	/*
	 * Nothing is needed here, the barrier to guarantee
	 * completion of the tlb sync operation is implicitly
	 * taken care when the iommu client करोes a ग_लिखोl beक्रमe
	 * kick starting the other master.
	 */
	.iotlb_sync = शून्य,
	.iotlb_sync_map = msm_iommu_sync_map,
	.iova_to_phys = msm_iommu_iova_to_phys,
	.probe_device = msm_iommu_probe_device,
	.release_device = msm_iommu_release_device,
	.device_group = generic_device_group,
	.pgsize_biपंचांगap = MSM_IOMMU_PGSIZES,
	.of_xlate = qcom_iommu_of_xlate,
पूर्ण;

अटल पूर्णांक msm_iommu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *r;
	resource_माप_प्रकार ioaddr;
	काष्ठा msm_iommu_dev *iommu;
	पूर्णांक ret, par, val;

	iommu = devm_kzalloc(&pdev->dev, माप(*iommu), GFP_KERNEL);
	अगर (!iommu)
		वापस -ENODEV;

	iommu->dev = &pdev->dev;
	INIT_LIST_HEAD(&iommu->ctx_list);

	iommu->pclk = devm_clk_get(iommu->dev, "smmu_pclk");
	अगर (IS_ERR(iommu->pclk)) अणु
		dev_err(iommu->dev, "could not get smmu_pclk\n");
		वापस PTR_ERR(iommu->pclk);
	पूर्ण

	ret = clk_prepare(iommu->pclk);
	अगर (ret) अणु
		dev_err(iommu->dev, "could not prepare smmu_pclk\n");
		वापस ret;
	पूर्ण

	iommu->clk = devm_clk_get(iommu->dev, "iommu_clk");
	अगर (IS_ERR(iommu->clk)) अणु
		dev_err(iommu->dev, "could not get iommu_clk\n");
		clk_unprepare(iommu->pclk);
		वापस PTR_ERR(iommu->clk);
	पूर्ण

	ret = clk_prepare(iommu->clk);
	अगर (ret) अणु
		dev_err(iommu->dev, "could not prepare iommu_clk\n");
		clk_unprepare(iommu->pclk);
		वापस ret;
	पूर्ण

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	iommu->base = devm_ioremap_resource(iommu->dev, r);
	अगर (IS_ERR(iommu->base)) अणु
		dev_err(iommu->dev, "could not get iommu base\n");
		ret = PTR_ERR(iommu->base);
		जाओ fail;
	पूर्ण
	ioaddr = r->start;

	iommu->irq = platक्रमm_get_irq(pdev, 0);
	अगर (iommu->irq < 0) अणु
		ret = -ENODEV;
		जाओ fail;
	पूर्ण

	ret = of_property_पढ़ो_u32(iommu->dev->of_node, "qcom,ncb", &val);
	अगर (ret) अणु
		dev_err(iommu->dev, "could not get ncb\n");
		जाओ fail;
	पूर्ण
	iommu->ncb = val;

	msm_iommu_reset(iommu->base, iommu->ncb);
	SET_M(iommu->base, 0, 1);
	SET_PAR(iommu->base, 0, 0);
	SET_V2PCFG(iommu->base, 0, 1);
	SET_V2PPR(iommu->base, 0, 0);
	par = GET_PAR(iommu->base, 0);
	SET_V2PCFG(iommu->base, 0, 0);
	SET_M(iommu->base, 0, 0);

	अगर (!par) अणु
		pr_err("Invalid PAR value detected\n");
		ret = -ENODEV;
		जाओ fail;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(iommu->dev, iommu->irq, शून्य,
					msm_iommu_fault_handler,
					IRQF_ONESHOT | IRQF_SHARED,
					"msm_iommu_secure_irpt_handler",
					iommu);
	अगर (ret) अणु
		pr_err("Request IRQ %d failed with ret=%d\n", iommu->irq, ret);
		जाओ fail;
	पूर्ण

	list_add(&iommu->dev_node, &qcom_iommu_devices);

	ret = iommu_device_sysfs_add(&iommu->iommu, iommu->dev, शून्य,
				     "msm-smmu.%pa", &ioaddr);
	अगर (ret) अणु
		pr_err("Could not add msm-smmu at %pa to sysfs\n", &ioaddr);
		जाओ fail;
	पूर्ण

	ret = iommu_device_रेजिस्टर(&iommu->iommu, &msm_iommu_ops, &pdev->dev);
	अगर (ret) अणु
		pr_err("Could not register msm-smmu at %pa\n", &ioaddr);
		जाओ fail;
	पूर्ण

	bus_set_iommu(&platक्रमm_bus_type, &msm_iommu_ops);

	pr_info("device mapped at %p, irq %d with %d ctx banks\n",
		iommu->base, iommu->irq, iommu->ncb);

	वापस ret;
fail:
	clk_unprepare(iommu->clk);
	clk_unprepare(iommu->pclk);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id msm_iommu_dt_match[] = अणु
	अणु .compatible = "qcom,apq8064-iommu" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक msm_iommu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा msm_iommu_dev *iommu = platक्रमm_get_drvdata(pdev);

	clk_unprepare(iommu->clk);
	clk_unprepare(iommu->pclk);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver msm_iommu_driver = अणु
	.driver = अणु
		.name	= "msm_iommu",
		.of_match_table = msm_iommu_dt_match,
	पूर्ण,
	.probe		= msm_iommu_probe,
	.हटाओ		= msm_iommu_हटाओ,
पूर्ण;

अटल पूर्णांक __init msm_iommu_driver_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&msm_iommu_driver);
	अगर (ret != 0)
		pr_err("Failed to register IOMMU driver\n");

	वापस ret;
पूर्ण
subsys_initcall(msm_iommu_driver_init);

