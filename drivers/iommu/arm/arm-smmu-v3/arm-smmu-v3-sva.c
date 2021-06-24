<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Implementation of the IOMMU SVA API क्रम the ARM SMMUv3
 */

#समावेश <linux/mm.h>
#समावेश <linux/mmu_context.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/slab.h>

#समावेश "arm-smmu-v3.h"
#समावेश "../../iommu-sva-lib.h"
#समावेश "../../io-pgtable-arm.h"

काष्ठा arm_smmu_mmu_notअगरier अणु
	काष्ठा mmu_notअगरier		mn;
	काष्ठा arm_smmu_ctx_desc	*cd;
	bool				cleared;
	refcount_t			refs;
	काष्ठा list_head		list;
	काष्ठा arm_smmu_करोमुख्य		*करोमुख्य;
पूर्ण;

#घोषणा mn_to_smmu(mn) container_of(mn, काष्ठा arm_smmu_mmu_notअगरier, mn)

काष्ठा arm_smmu_bond अणु
	काष्ठा iommu_sva		sva;
	काष्ठा mm_काष्ठा		*mm;
	काष्ठा arm_smmu_mmu_notअगरier	*smmu_mn;
	काष्ठा list_head		list;
	refcount_t			refs;
पूर्ण;

#घोषणा sva_to_bond(handle) \
	container_of(handle, काष्ठा arm_smmu_bond, sva)

अटल DEFINE_MUTEX(sva_lock);

/*
 * Check अगर the CPU ASID is available on the SMMU side. If a निजी context
 * descriptor is using it, try to replace it.
 */
अटल काष्ठा arm_smmu_ctx_desc *
arm_smmu_share_asid(काष्ठा mm_काष्ठा *mm, u16 asid)
अणु
	पूर्णांक ret;
	u32 new_asid;
	काष्ठा arm_smmu_ctx_desc *cd;
	काष्ठा arm_smmu_device *smmu;
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य;

	cd = xa_load(&arm_smmu_asid_xa, asid);
	अगर (!cd)
		वापस शून्य;

	अगर (cd->mm) अणु
		अगर (WARN_ON(cd->mm != mm))
			वापस ERR_PTR(-EINVAL);
		/* All devices bound to this mm use the same cd काष्ठा. */
		refcount_inc(&cd->refs);
		वापस cd;
	पूर्ण

	smmu_करोमुख्य = container_of(cd, काष्ठा arm_smmu_करोमुख्य, s1_cfg.cd);
	smmu = smmu_करोमुख्य->smmu;

	ret = xa_alloc(&arm_smmu_asid_xa, &new_asid, cd,
		       XA_LIMIT(1, (1 << smmu->asid_bits) - 1), GFP_KERNEL);
	अगर (ret)
		वापस ERR_PTR(-ENOSPC);
	/*
	 * Race with unmap: TLB invalidations will start targeting the new ASID,
	 * which isn't assigned yet. We'll करो an invalidate-all on the old ASID
	 * later, so it करोesn't matter.
	 */
	cd->asid = new_asid;
	/*
	 * Update ASID and invalidate CD in all associated masters. There will
	 * be some overlap between use of both ASIDs, until we invalidate the
	 * TLB.
	 */
	arm_smmu_ग_लिखो_ctx_desc(smmu_करोमुख्य, 0, cd);

	/* Invalidate TLB entries previously associated with that context */
	arm_smmu_tlb_inv_asid(smmu, asid);

	xa_erase(&arm_smmu_asid_xa, asid);
	वापस शून्य;
पूर्ण

अटल काष्ठा arm_smmu_ctx_desc *arm_smmu_alloc_shared_cd(काष्ठा mm_काष्ठा *mm)
अणु
	u16 asid;
	पूर्णांक err = 0;
	u64 tcr, par, reg;
	काष्ठा arm_smmu_ctx_desc *cd;
	काष्ठा arm_smmu_ctx_desc *ret = शून्य;

	asid = arm64_mm_context_get(mm);
	अगर (!asid)
		वापस ERR_PTR(-ESRCH);

	cd = kzalloc(माप(*cd), GFP_KERNEL);
	अगर (!cd) अणु
		err = -ENOMEM;
		जाओ out_put_context;
	पूर्ण

	refcount_set(&cd->refs, 1);

	mutex_lock(&arm_smmu_asid_lock);
	ret = arm_smmu_share_asid(mm, asid);
	अगर (ret) अणु
		mutex_unlock(&arm_smmu_asid_lock);
		जाओ out_मुक्त_cd;
	पूर्ण

	err = xa_insert(&arm_smmu_asid_xa, asid, cd, GFP_KERNEL);
	mutex_unlock(&arm_smmu_asid_lock);

	अगर (err)
		जाओ out_मुक्त_asid;

	tcr = FIELD_PREP(CTXDESC_CD_0_TCR_T0SZ, 64ULL - vabits_actual) |
	      FIELD_PREP(CTXDESC_CD_0_TCR_IRGN0, ARM_LPAE_TCR_RGN_WBWA) |
	      FIELD_PREP(CTXDESC_CD_0_TCR_ORGN0, ARM_LPAE_TCR_RGN_WBWA) |
	      FIELD_PREP(CTXDESC_CD_0_TCR_SH0, ARM_LPAE_TCR_SH_IS) |
	      CTXDESC_CD_0_TCR_EPD1 | CTXDESC_CD_0_AA64;

	चयन (PAGE_SIZE) अणु
	हाल SZ_4K:
		tcr |= FIELD_PREP(CTXDESC_CD_0_TCR_TG0, ARM_LPAE_TCR_TG0_4K);
		अवरोध;
	हाल SZ_16K:
		tcr |= FIELD_PREP(CTXDESC_CD_0_TCR_TG0, ARM_LPAE_TCR_TG0_16K);
		अवरोध;
	हाल SZ_64K:
		tcr |= FIELD_PREP(CTXDESC_CD_0_TCR_TG0, ARM_LPAE_TCR_TG0_64K);
		अवरोध;
	शेष:
		WARN_ON(1);
		err = -EINVAL;
		जाओ out_मुक्त_asid;
	पूर्ण

	reg = पढ़ो_sanitised_ftr_reg(SYS_ID_AA64MMFR0_EL1);
	par = cpuid_feature_extract_अचिन्हित_field(reg, ID_AA64MMFR0_PARANGE_SHIFT);
	tcr |= FIELD_PREP(CTXDESC_CD_0_TCR_IPS, par);

	cd->ttbr = virt_to_phys(mm->pgd);
	cd->tcr = tcr;
	/*
	 * MAIR value is pretty much स्थिरant and global, so we can just get it
	 * from the current CPU रेजिस्टर
	 */
	cd->mair = पढ़ो_sysreg(mair_el1);
	cd->asid = asid;
	cd->mm = mm;

	वापस cd;

out_मुक्त_asid:
	arm_smmu_मुक्त_asid(cd);
out_मुक्त_cd:
	kमुक्त(cd);
out_put_context:
	arm64_mm_context_put(mm);
	वापस err < 0 ? ERR_PTR(err) : ret;
पूर्ण

अटल व्योम arm_smmu_मुक्त_shared_cd(काष्ठा arm_smmu_ctx_desc *cd)
अणु
	अगर (arm_smmu_मुक्त_asid(cd)) अणु
		/* Unpin ASID */
		arm64_mm_context_put(cd->mm);
		kमुक्त(cd);
	पूर्ण
पूर्ण

अटल व्योम arm_smmu_mm_invalidate_range(काष्ठा mmu_notअगरier *mn,
					 काष्ठा mm_काष्ठा *mm,
					 अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा arm_smmu_mmu_notअगरier *smmu_mn = mn_to_smmu(mn);
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = smmu_mn->करोमुख्य;
	माप_प्रकार size = end - start + 1;

	अगर (!(smmu_करोमुख्य->smmu->features & ARM_SMMU_FEAT_BTM))
		arm_smmu_tlb_inv_range_asid(start, size, smmu_mn->cd->asid,
					    PAGE_SIZE, false, smmu_करोमुख्य);
	arm_smmu_atc_inv_करोमुख्य(smmu_करोमुख्य, mm->pasid, start, size);
पूर्ण

अटल व्योम arm_smmu_mm_release(काष्ठा mmu_notअगरier *mn, काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा arm_smmu_mmu_notअगरier *smmu_mn = mn_to_smmu(mn);
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = smmu_mn->करोमुख्य;

	mutex_lock(&sva_lock);
	अगर (smmu_mn->cleared) अणु
		mutex_unlock(&sva_lock);
		वापस;
	पूर्ण

	/*
	 * DMA may still be running. Keep the cd valid to aव्योम C_BAD_CD events,
	 * but disable translation.
	 */
	arm_smmu_ग_लिखो_ctx_desc(smmu_करोमुख्य, mm->pasid, &quiet_cd);

	arm_smmu_tlb_inv_asid(smmu_करोमुख्य->smmu, smmu_mn->cd->asid);
	arm_smmu_atc_inv_करोमुख्य(smmu_करोमुख्य, mm->pasid, 0, 0);

	smmu_mn->cleared = true;
	mutex_unlock(&sva_lock);
पूर्ण

अटल व्योम arm_smmu_mmu_notअगरier_मुक्त(काष्ठा mmu_notअगरier *mn)
अणु
	kमुक्त(mn_to_smmu(mn));
पूर्ण

अटल काष्ठा mmu_notअगरier_ops arm_smmu_mmu_notअगरier_ops = अणु
	.invalidate_range	= arm_smmu_mm_invalidate_range,
	.release		= arm_smmu_mm_release,
	.मुक्त_notअगरier		= arm_smmu_mmu_notअगरier_मुक्त,
पूर्ण;

/* Allocate or get existing MMU notअगरier क्रम this अणुकरोमुख्य, mmपूर्ण pair */
अटल काष्ठा arm_smmu_mmu_notअगरier *
arm_smmu_mmu_notअगरier_get(काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य,
			  काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक ret;
	काष्ठा arm_smmu_ctx_desc *cd;
	काष्ठा arm_smmu_mmu_notअगरier *smmu_mn;

	list_क्रम_each_entry(smmu_mn, &smmu_करोमुख्य->mmu_notअगरiers, list) अणु
		अगर (smmu_mn->mn.mm == mm) अणु
			refcount_inc(&smmu_mn->refs);
			वापस smmu_mn;
		पूर्ण
	पूर्ण

	cd = arm_smmu_alloc_shared_cd(mm);
	अगर (IS_ERR(cd))
		वापस ERR_CAST(cd);

	smmu_mn = kzalloc(माप(*smmu_mn), GFP_KERNEL);
	अगर (!smmu_mn) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_cd;
	पूर्ण

	refcount_set(&smmu_mn->refs, 1);
	smmu_mn->cd = cd;
	smmu_mn->करोमुख्य = smmu_करोमुख्य;
	smmu_mn->mn.ops = &arm_smmu_mmu_notअगरier_ops;

	ret = mmu_notअगरier_रेजिस्टर(&smmu_mn->mn, mm);
	अगर (ret) अणु
		kमुक्त(smmu_mn);
		जाओ err_मुक्त_cd;
	पूर्ण

	ret = arm_smmu_ग_लिखो_ctx_desc(smmu_करोमुख्य, mm->pasid, cd);
	अगर (ret)
		जाओ err_put_notअगरier;

	list_add(&smmu_mn->list, &smmu_करोमुख्य->mmu_notअगरiers);
	वापस smmu_mn;

err_put_notअगरier:
	/* Frees smmu_mn */
	mmu_notअगरier_put(&smmu_mn->mn);
err_मुक्त_cd:
	arm_smmu_मुक्त_shared_cd(cd);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम arm_smmu_mmu_notअगरier_put(काष्ठा arm_smmu_mmu_notअगरier *smmu_mn)
अणु
	काष्ठा mm_काष्ठा *mm = smmu_mn->mn.mm;
	काष्ठा arm_smmu_ctx_desc *cd = smmu_mn->cd;
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = smmu_mn->करोमुख्य;

	अगर (!refcount_dec_and_test(&smmu_mn->refs))
		वापस;

	list_del(&smmu_mn->list);
	arm_smmu_ग_लिखो_ctx_desc(smmu_करोमुख्य, mm->pasid, शून्य);

	/*
	 * If we went through clear(), we've alपढ़ोy invalidated, and no
	 * new TLB entry can have been क्रमmed.
	 */
	अगर (!smmu_mn->cleared) अणु
		arm_smmu_tlb_inv_asid(smmu_करोमुख्य->smmu, cd->asid);
		arm_smmu_atc_inv_करोमुख्य(smmu_करोमुख्य, mm->pasid, 0, 0);
	पूर्ण

	/* Frees smmu_mn */
	mmu_notअगरier_put(&smmu_mn->mn);
	arm_smmu_मुक्त_shared_cd(cd);
पूर्ण

अटल काष्ठा iommu_sva *
__arm_smmu_sva_bind(काष्ठा device *dev, काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक ret;
	काष्ठा arm_smmu_bond *bond;
	काष्ठा arm_smmu_master *master = dev_iommu_priv_get(dev);
	काष्ठा iommu_करोमुख्य *करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = to_smmu_करोमुख्य(करोमुख्य);

	अगर (!master || !master->sva_enabled)
		वापस ERR_PTR(-ENODEV);

	/* If bind() was alपढ़ोy called क्रम this अणुdev, mmपूर्ण pair, reuse it. */
	list_क्रम_each_entry(bond, &master->bonds, list) अणु
		अगर (bond->mm == mm) अणु
			refcount_inc(&bond->refs);
			वापस &bond->sva;
		पूर्ण
	पूर्ण

	bond = kzalloc(माप(*bond), GFP_KERNEL);
	अगर (!bond)
		वापस ERR_PTR(-ENOMEM);

	/* Allocate a PASID क्रम this mm अगर necessary */
	ret = iommu_sva_alloc_pasid(mm, 1, (1U << master->ssid_bits) - 1);
	अगर (ret)
		जाओ err_मुक्त_bond;

	bond->mm = mm;
	bond->sva.dev = dev;
	refcount_set(&bond->refs, 1);

	bond->smmu_mn = arm_smmu_mmu_notअगरier_get(smmu_करोमुख्य, mm);
	अगर (IS_ERR(bond->smmu_mn)) अणु
		ret = PTR_ERR(bond->smmu_mn);
		जाओ err_मुक्त_pasid;
	पूर्ण

	list_add(&bond->list, &master->bonds);
	वापस &bond->sva;

err_मुक्त_pasid:
	iommu_sva_मुक्त_pasid(mm);
err_मुक्त_bond:
	kमुक्त(bond);
	वापस ERR_PTR(ret);
पूर्ण

काष्ठा iommu_sva *
arm_smmu_sva_bind(काष्ठा device *dev, काष्ठा mm_काष्ठा *mm, व्योम *drvdata)
अणु
	काष्ठा iommu_sva *handle;
	काष्ठा iommu_करोमुख्य *करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = to_smmu_करोमुख्य(करोमुख्य);

	अगर (smmu_करोमुख्य->stage != ARM_SMMU_DOMAIN_S1)
		वापस ERR_PTR(-EINVAL);

	mutex_lock(&sva_lock);
	handle = __arm_smmu_sva_bind(dev, mm);
	mutex_unlock(&sva_lock);
	वापस handle;
पूर्ण

व्योम arm_smmu_sva_unbind(काष्ठा iommu_sva *handle)
अणु
	काष्ठा arm_smmu_bond *bond = sva_to_bond(handle);

	mutex_lock(&sva_lock);
	अगर (refcount_dec_and_test(&bond->refs)) अणु
		list_del(&bond->list);
		arm_smmu_mmu_notअगरier_put(bond->smmu_mn);
		iommu_sva_मुक्त_pasid(bond->mm);
		kमुक्त(bond);
	पूर्ण
	mutex_unlock(&sva_lock);
पूर्ण

u32 arm_smmu_sva_get_pasid(काष्ठा iommu_sva *handle)
अणु
	काष्ठा arm_smmu_bond *bond = sva_to_bond(handle);

	वापस bond->mm->pasid;
पूर्ण

bool arm_smmu_sva_supported(काष्ठा arm_smmu_device *smmu)
अणु
	अचिन्हित दीर्घ reg, fld;
	अचिन्हित दीर्घ oas;
	अचिन्हित दीर्घ asid_bits;
	u32 feat_mask = ARM_SMMU_FEAT_COHERENCY;

	अगर (vabits_actual == 52)
		feat_mask |= ARM_SMMU_FEAT_VAX;

	अगर ((smmu->features & feat_mask) != feat_mask)
		वापस false;

	अगर (!(smmu->pgsize_biपंचांगap & PAGE_SIZE))
		वापस false;

	/*
	 * Get the smallest PA size of all CPUs (sanitized by cpufeature). We're
	 * not even pretending to support AArch32 here. Abort अगर the MMU outमाला_दो
	 * addresses larger than what we support.
	 */
	reg = पढ़ो_sanitised_ftr_reg(SYS_ID_AA64MMFR0_EL1);
	fld = cpuid_feature_extract_अचिन्हित_field(reg, ID_AA64MMFR0_PARANGE_SHIFT);
	oas = id_aa64mmfr0_parange_to_phys_shअगरt(fld);
	अगर (smmu->oas < oas)
		वापस false;

	/* We can support bigger ASIDs than the CPU, but not smaller */
	fld = cpuid_feature_extract_अचिन्हित_field(reg, ID_AA64MMFR0_ASID_SHIFT);
	asid_bits = fld ? 16 : 8;
	अगर (smmu->asid_bits < asid_bits)
		वापस false;

	/*
	 * See max_pinned_asids in arch/arm64/mm/context.c. The following is
	 * generally the maximum number of bindable processes.
	 */
	अगर (arm64_kernel_unmapped_at_el0())
		asid_bits--;
	dev_dbg(smmu->dev, "%d shared contexts\n", (1 << asid_bits) -
		num_possible_cpus() - 2);

	वापस true;
पूर्ण

अटल bool arm_smmu_iopf_supported(काष्ठा arm_smmu_master *master)
अणु
	वापस false;
पूर्ण

bool arm_smmu_master_sva_supported(काष्ठा arm_smmu_master *master)
अणु
	अगर (!(master->smmu->features & ARM_SMMU_FEAT_SVA))
		वापस false;

	/* SSID and IOPF support are mandatory क्रम the moment */
	वापस master->ssid_bits && arm_smmu_iopf_supported(master);
पूर्ण

bool arm_smmu_master_sva_enabled(काष्ठा arm_smmu_master *master)
अणु
	bool enabled;

	mutex_lock(&sva_lock);
	enabled = master->sva_enabled;
	mutex_unlock(&sva_lock);
	वापस enabled;
पूर्ण

पूर्णांक arm_smmu_master_enable_sva(काष्ठा arm_smmu_master *master)
अणु
	mutex_lock(&sva_lock);
	master->sva_enabled = true;
	mutex_unlock(&sva_lock);

	वापस 0;
पूर्ण

पूर्णांक arm_smmu_master_disable_sva(काष्ठा arm_smmu_master *master)
अणु
	mutex_lock(&sva_lock);
	अगर (!list_empty(&master->bonds)) अणु
		dev_err(master->dev, "cannot disable SVA, device is bound\n");
		mutex_unlock(&sva_lock);
		वापस -EBUSY;
	पूर्ण
	master->sva_enabled = false;
	mutex_unlock(&sva_lock);

	वापस 0;
पूर्ण

व्योम arm_smmu_sva_notअगरier_synchronize(व्योम)
अणु
	/*
	 * Some MMU notअगरiers may still be रुकोing to be मुक्तd, using
	 * arm_smmu_mmu_notअगरier_मुक्त(). Wait क्रम them.
	 */
	mmu_notअगरier_synchronize();
पूर्ण
