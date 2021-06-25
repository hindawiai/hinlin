<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/adreno-smmu-priv.h>
#समावेश <linux/io-pgtable.h>
#समावेश "msm_drv.h"
#समावेश "msm_mmu.h"

काष्ठा msm_iommu अणु
	काष्ठा msm_mmu base;
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	atomic_t pagetables;
पूर्ण;

#घोषणा to_msm_iommu(x) container_of(x, काष्ठा msm_iommu, base)

काष्ठा msm_iommu_pagetable अणु
	काष्ठा msm_mmu base;
	काष्ठा msm_mmu *parent;
	काष्ठा io_pgtable_ops *pgtbl_ops;
	phys_addr_t ttbr;
	u32 asid;
पूर्ण;
अटल काष्ठा msm_iommu_pagetable *to_pagetable(काष्ठा msm_mmu *mmu)
अणु
	वापस container_of(mmu, काष्ठा msm_iommu_pagetable, base);
पूर्ण

अटल पूर्णांक msm_iommu_pagetable_unmap(काष्ठा msm_mmu *mmu, u64 iova,
		माप_प्रकार size)
अणु
	काष्ठा msm_iommu_pagetable *pagetable = to_pagetable(mmu);
	काष्ठा io_pgtable_ops *ops = pagetable->pgtbl_ops;
	माप_प्रकार unmapped = 0;

	/* Unmap the block one page at a समय */
	जबतक (size) अणु
		unmapped += ops->unmap(ops, iova, 4096, शून्य);
		iova += 4096;
		size -= 4096;
	पूर्ण

	iommu_flush_iotlb_all(to_msm_iommu(pagetable->parent)->करोमुख्य);

	वापस (unmapped == size) ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक msm_iommu_pagetable_map(काष्ठा msm_mmu *mmu, u64 iova,
		काष्ठा sg_table *sgt, माप_प्रकार len, पूर्णांक prot)
अणु
	काष्ठा msm_iommu_pagetable *pagetable = to_pagetable(mmu);
	काष्ठा io_pgtable_ops *ops = pagetable->pgtbl_ops;
	काष्ठा scatterlist *sg;
	माप_प्रकार mapped = 0;
	u64 addr = iova;
	अचिन्हित पूर्णांक i;

	क्रम_each_sg(sgt->sgl, sg, sgt->nents, i) अणु
		माप_प्रकार size = sg->length;
		phys_addr_t phys = sg_phys(sg);

		/* Map the block one page at a समय */
		जबतक (size) अणु
			अगर (ops->map(ops, addr, phys, 4096, prot, GFP_KERNEL)) अणु
				msm_iommu_pagetable_unmap(mmu, iova, mapped);
				वापस -EINVAL;
			पूर्ण

			phys += 4096;
			addr += 4096;
			size -= 4096;
			mapped += 4096;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम msm_iommu_pagetable_destroy(काष्ठा msm_mmu *mmu)
अणु
	काष्ठा msm_iommu_pagetable *pagetable = to_pagetable(mmu);
	काष्ठा msm_iommu *iommu = to_msm_iommu(pagetable->parent);
	काष्ठा adreno_smmu_priv *adreno_smmu =
		dev_get_drvdata(pagetable->parent->dev);

	/*
	 * If this is the last attached pagetable क्रम the parent,
	 * disable TTBR0 in the arm-smmu driver
	 */
	अगर (atomic_dec_वापस(&iommu->pagetables) == 0)
		adreno_smmu->set_ttbr0_cfg(adreno_smmu->cookie, शून्य);

	मुक्त_io_pgtable_ops(pagetable->pgtbl_ops);
	kमुक्त(pagetable);
पूर्ण

पूर्णांक msm_iommu_pagetable_params(काष्ठा msm_mmu *mmu,
		phys_addr_t *ttbr, पूर्णांक *asid)
अणु
	काष्ठा msm_iommu_pagetable *pagetable;

	अगर (mmu->type != MSM_MMU_IOMMU_PAGETABLE)
		वापस -EINVAL;

	pagetable = to_pagetable(mmu);

	अगर (ttbr)
		*ttbr = pagetable->ttbr;

	अगर (asid)
		*asid = pagetable->asid;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा msm_mmu_funcs pagetable_funcs = अणु
		.map = msm_iommu_pagetable_map,
		.unmap = msm_iommu_pagetable_unmap,
		.destroy = msm_iommu_pagetable_destroy,
पूर्ण;

अटल व्योम msm_iommu_tlb_flush_all(व्योम *cookie)
अणु
पूर्ण

अटल व्योम msm_iommu_tlb_flush_walk(अचिन्हित दीर्घ iova, माप_प्रकार size,
		माप_प्रकार granule, व्योम *cookie)
अणु
पूर्ण

अटल व्योम msm_iommu_tlb_add_page(काष्ठा iommu_iotlb_gather *gather,
		अचिन्हित दीर्घ iova, माप_प्रकार granule, व्योम *cookie)
अणु
पूर्ण

अटल स्थिर काष्ठा iommu_flush_ops null_tlb_ops = अणु
	.tlb_flush_all = msm_iommu_tlb_flush_all,
	.tlb_flush_walk = msm_iommu_tlb_flush_walk,
	.tlb_add_page = msm_iommu_tlb_add_page,
पूर्ण;

काष्ठा msm_mmu *msm_iommu_pagetable_create(काष्ठा msm_mmu *parent)
अणु
	काष्ठा adreno_smmu_priv *adreno_smmu = dev_get_drvdata(parent->dev);
	काष्ठा msm_iommu *iommu = to_msm_iommu(parent);
	काष्ठा msm_iommu_pagetable *pagetable;
	स्थिर काष्ठा io_pgtable_cfg *ttbr1_cfg = शून्य;
	काष्ठा io_pgtable_cfg ttbr0_cfg;
	पूर्णांक ret;

	/* Get the pagetable configuration from the करोमुख्य */
	अगर (adreno_smmu->cookie)
		ttbr1_cfg = adreno_smmu->get_ttbr1_cfg(adreno_smmu->cookie);
	अगर (!ttbr1_cfg)
		वापस ERR_PTR(-ENODEV);

	pagetable = kzalloc(माप(*pagetable), GFP_KERNEL);
	अगर (!pagetable)
		वापस ERR_PTR(-ENOMEM);

	msm_mmu_init(&pagetable->base, parent->dev, &pagetable_funcs,
		MSM_MMU_IOMMU_PAGETABLE);

	/* Clone the TTBR1 cfg as starting poपूर्णांक क्रम TTBR0 cfg: */
	ttbr0_cfg = *ttbr1_cfg;

	/* The incoming cfg will have the TTBR1 quirk enabled */
	ttbr0_cfg.quirks &= ~IO_PGTABLE_QUIRK_ARM_TTBR1;
	ttbr0_cfg.tlb = &null_tlb_ops;

	pagetable->pgtbl_ops = alloc_io_pgtable_ops(ARM_64_LPAE_S1,
		&ttbr0_cfg, iommu->करोमुख्य);

	अगर (!pagetable->pgtbl_ops) अणु
		kमुक्त(pagetable);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/*
	 * If this is the first pagetable that we've allocated, send it back to
	 * the arm-smmu driver as a trigger to set up TTBR0
	 */
	अगर (atomic_inc_वापस(&iommu->pagetables) == 1) अणु
		ret = adreno_smmu->set_ttbr0_cfg(adreno_smmu->cookie, &ttbr0_cfg);
		अगर (ret) अणु
			मुक्त_io_pgtable_ops(pagetable->pgtbl_ops);
			kमुक्त(pagetable);
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण

	/* Needed later क्रम TLB flush */
	pagetable->parent = parent;
	pagetable->ttbr = ttbr0_cfg.arm_lpae_s1_cfg.ttbr;

	/*
	 * TODO we would like each set of page tables to have a unique ASID
	 * to optimize TLB invalidation.  But iommu_flush_iotlb_all() will
	 * end up flushing the ASID used क्रम TTBR1 pagetables, which is not
	 * what we want.  So क्रम now just use the same ASID as TTBR1.
	 */
	pagetable->asid = 0;

	वापस &pagetable->base;
पूर्ण

अटल पूर्णांक msm_fault_handler(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev,
		अचिन्हित दीर्घ iova, पूर्णांक flags, व्योम *arg)
अणु
	काष्ठा msm_iommu *iommu = arg;
	अगर (iommu->base.handler)
		वापस iommu->base.handler(iommu->base.arg, iova, flags);
	pr_warn_ratelimited("*** fault: iova=%16lx, flags=%d\n", iova, flags);
	वापस 0;
पूर्ण

अटल व्योम msm_iommu_detach(काष्ठा msm_mmu *mmu)
अणु
	काष्ठा msm_iommu *iommu = to_msm_iommu(mmu);

	iommu_detach_device(iommu->करोमुख्य, mmu->dev);
पूर्ण

अटल पूर्णांक msm_iommu_map(काष्ठा msm_mmu *mmu, uपूर्णांक64_t iova,
		काष्ठा sg_table *sgt, माप_प्रकार len, पूर्णांक prot)
अणु
	काष्ठा msm_iommu *iommu = to_msm_iommu(mmu);
	माप_प्रकार ret;

	/* The arm-smmu driver expects the addresses to be sign extended */
	अगर (iova & BIT_ULL(48))
		iova |= GENMASK_ULL(63, 49);

	ret = iommu_map_sgtable(iommu->करोमुख्य, iova, sgt, prot);
	WARN_ON(!ret);

	वापस (ret == len) ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक msm_iommu_unmap(काष्ठा msm_mmu *mmu, uपूर्णांक64_t iova, माप_प्रकार len)
अणु
	काष्ठा msm_iommu *iommu = to_msm_iommu(mmu);

	अगर (iova & BIT_ULL(48))
		iova |= GENMASK_ULL(63, 49);

	iommu_unmap(iommu->करोमुख्य, iova, len);

	वापस 0;
पूर्ण

अटल व्योम msm_iommu_destroy(काष्ठा msm_mmu *mmu)
अणु
	काष्ठा msm_iommu *iommu = to_msm_iommu(mmu);
	iommu_करोमुख्य_मुक्त(iommu->करोमुख्य);
	kमुक्त(iommu);
पूर्ण

अटल स्थिर काष्ठा msm_mmu_funcs funcs = अणु
		.detach = msm_iommu_detach,
		.map = msm_iommu_map,
		.unmap = msm_iommu_unmap,
		.destroy = msm_iommu_destroy,
पूर्ण;

काष्ठा msm_mmu *msm_iommu_new(काष्ठा device *dev, काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा msm_iommu *iommu;
	पूर्णांक ret;

	अगर (!करोमुख्य)
		वापस ERR_PTR(-ENODEV);

	iommu = kzalloc(माप(*iommu), GFP_KERNEL);
	अगर (!iommu)
		वापस ERR_PTR(-ENOMEM);

	iommu->करोमुख्य = करोमुख्य;
	msm_mmu_init(&iommu->base, dev, &funcs, MSM_MMU_IOMMU);
	iommu_set_fault_handler(करोमुख्य, msm_fault_handler, iommu);

	atomic_set(&iommu->pagetables, 0);

	ret = iommu_attach_device(iommu->करोमुख्य, dev);
	अगर (ret) अणु
		kमुक्त(iommu);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस &iommu->base;
पूर्ण
