<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Miscellaneous Arm SMMU implementation and पूर्णांकegration quirks
// Copyright (C) 2019 Arm Limited

#घोषणा pr_fmt(fmt) "arm-smmu: " fmt

#समावेश <linux/bitfield.h>
#समावेश <linux/of.h>

#समावेश "arm-smmu.h"


अटल पूर्णांक arm_smmu_gr0_ns(पूर्णांक offset)
अणु
	चयन (offset) अणु
	हाल ARM_SMMU_GR0_sCR0:
	हाल ARM_SMMU_GR0_sACR:
	हाल ARM_SMMU_GR0_sGFSR:
	हाल ARM_SMMU_GR0_sGFSYNR0:
	हाल ARM_SMMU_GR0_sGFSYNR1:
	हाल ARM_SMMU_GR0_sGFSYNR2:
		वापस offset + 0x400;
	शेष:
		वापस offset;
	पूर्ण
पूर्ण

अटल u32 arm_smmu_पढ़ो_ns(काष्ठा arm_smmu_device *smmu, पूर्णांक page,
			    पूर्णांक offset)
अणु
	अगर (page == ARM_SMMU_GR0)
		offset = arm_smmu_gr0_ns(offset);
	वापस पढ़ोl_relaxed(arm_smmu_page(smmu, page) + offset);
पूर्ण

अटल व्योम arm_smmu_ग_लिखो_ns(काष्ठा arm_smmu_device *smmu, पूर्णांक page,
			      पूर्णांक offset, u32 val)
अणु
	अगर (page == ARM_SMMU_GR0)
		offset = arm_smmu_gr0_ns(offset);
	ग_लिखोl_relaxed(val, arm_smmu_page(smmu, page) + offset);
पूर्ण

/* Since we करोn't care क्रम sGFAR, we can करो without 64-bit accessors */
अटल स्थिर काष्ठा arm_smmu_impl calxeda_impl = अणु
	.पढ़ो_reg = arm_smmu_पढ़ो_ns,
	.ग_लिखो_reg = arm_smmu_ग_लिखो_ns,
पूर्ण;


काष्ठा cavium_smmu अणु
	काष्ठा arm_smmu_device smmu;
	u32 id_base;
पूर्ण;

अटल पूर्णांक cavium_cfg_probe(काष्ठा arm_smmu_device *smmu)
अणु
	अटल atomic_t context_count = ATOMIC_INIT(0);
	काष्ठा cavium_smmu *cs = container_of(smmu, काष्ठा cavium_smmu, smmu);
	/*
	 * Cavium CN88xx erratum #27704.
	 * Ensure ASID and VMID allocation is unique across all SMMUs in
	 * the प्रणाली.
	 */
	cs->id_base = atomic_fetch_add(smmu->num_context_banks, &context_count);
	dev_notice(smmu->dev, "\tenabling workaround for Cavium erratum 27704\n");

	वापस 0;
पूर्ण

अटल पूर्णांक cavium_init_context(काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य,
		काष्ठा io_pgtable_cfg *pgtbl_cfg, काष्ठा device *dev)
अणु
	काष्ठा cavium_smmu *cs = container_of(smmu_करोमुख्य->smmu,
					      काष्ठा cavium_smmu, smmu);

	अगर (smmu_करोमुख्य->stage == ARM_SMMU_DOMAIN_S2)
		smmu_करोमुख्य->cfg.vmid += cs->id_base;
	अन्यथा
		smmu_करोमुख्य->cfg.asid += cs->id_base;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा arm_smmu_impl cavium_impl = अणु
	.cfg_probe = cavium_cfg_probe,
	.init_context = cavium_init_context,
पूर्ण;

अटल काष्ठा arm_smmu_device *cavium_smmu_impl_init(काष्ठा arm_smmu_device *smmu)
अणु
	काष्ठा cavium_smmu *cs;

	cs = devm_kपुनः_स्मृति(smmu->dev, smmu, माप(*cs), GFP_KERNEL);
	अगर (!cs)
		वापस ERR_PTR(-ENOMEM);

	cs->smmu.impl = &cavium_impl;

	वापस &cs->smmu;
पूर्ण


#घोषणा ARM_MMU500_ACTLR_CPRE		(1 << 1)

#घोषणा ARM_MMU500_ACR_CACHE_LOCK	(1 << 26)
#घोषणा ARM_MMU500_ACR_S2CRB_TLBEN	(1 << 10)
#घोषणा ARM_MMU500_ACR_SMTNMB_TLBEN	(1 << 8)

पूर्णांक arm_mmu500_reset(काष्ठा arm_smmu_device *smmu)
अणु
	u32 reg, major;
	पूर्णांक i;
	/*
	 * On MMU-500 r2p0 onwards we need to clear ACR.CACHE_LOCK beक्रमe
	 * ग_लिखोs to the context bank ACTLRs will stick. And we just hope that
	 * Secure has also cleared SACR.CACHE_LOCK क्रम this to take effect...
	 */
	reg = arm_smmu_gr0_पढ़ो(smmu, ARM_SMMU_GR0_ID7);
	major = FIELD_GET(ARM_SMMU_ID7_MAJOR, reg);
	reg = arm_smmu_gr0_पढ़ो(smmu, ARM_SMMU_GR0_sACR);
	अगर (major >= 2)
		reg &= ~ARM_MMU500_ACR_CACHE_LOCK;
	/*
	 * Allow unmatched Stream IDs to allocate bypass
	 * TLB entries क्रम reduced latency.
	 */
	reg |= ARM_MMU500_ACR_SMTNMB_TLBEN | ARM_MMU500_ACR_S2CRB_TLBEN;
	arm_smmu_gr0_ग_लिखो(smmu, ARM_SMMU_GR0_sACR, reg);

	/*
	 * Disable MMU-500's not-particularly-beneficial next-page
	 * prefetcher क्रम the sake of errata #841119 and #826419.
	 */
	क्रम (i = 0; i < smmu->num_context_banks; ++i) अणु
		reg = arm_smmu_cb_पढ़ो(smmu, i, ARM_SMMU_CB_ACTLR);
		reg &= ~ARM_MMU500_ACTLR_CPRE;
		arm_smmu_cb_ग_लिखो(smmu, i, ARM_SMMU_CB_ACTLR, reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा arm_smmu_impl arm_mmu500_impl = अणु
	.reset = arm_mmu500_reset,
पूर्ण;

अटल u64 mrvl_mmu500_पढ़ोq(काष्ठा arm_smmu_device *smmu, पूर्णांक page, पूर्णांक off)
अणु
	/*
	 * Marvell Armada-AP806 erratum #582743.
	 * Split all the पढ़ोq to द्विगुन पढ़ोl
	 */
	वापस hi_lo_पढ़ोq_relaxed(arm_smmu_page(smmu, page) + off);
पूर्ण

अटल व्योम mrvl_mmu500_ग_लिखोq(काष्ठा arm_smmu_device *smmu, पूर्णांक page, पूर्णांक off,
			       u64 val)
अणु
	/*
	 * Marvell Armada-AP806 erratum #582743.
	 * Split all the ग_लिखोq to द्विगुन ग_लिखोl
	 */
	hi_lo_ग_लिखोq_relaxed(val, arm_smmu_page(smmu, page) + off);
पूर्ण

अटल पूर्णांक mrvl_mmu500_cfg_probe(काष्ठा arm_smmu_device *smmu)
अणु

	/*
	 * Armada-AP806 erratum #582743.
	 * Hide the SMMU_IDR2.PTFSv8 fields to sidestep the AArch64
	 * क्रमmats altogether and allow using 32 bits access on the
	 * पूर्णांकerconnect.
	 */
	smmu->features &= ~(ARM_SMMU_FEAT_FMT_AARCH64_4K |
			    ARM_SMMU_FEAT_FMT_AARCH64_16K |
			    ARM_SMMU_FEAT_FMT_AARCH64_64K);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा arm_smmu_impl mrvl_mmu500_impl = अणु
	.पढ़ो_reg64 = mrvl_mmu500_पढ़ोq,
	.ग_लिखो_reg64 = mrvl_mmu500_ग_लिखोq,
	.cfg_probe = mrvl_mmu500_cfg_probe,
	.reset = arm_mmu500_reset,
पूर्ण;


काष्ठा arm_smmu_device *arm_smmu_impl_init(काष्ठा arm_smmu_device *smmu)
अणु
	स्थिर काष्ठा device_node *np = smmu->dev->of_node;

	/*
	 * Set the impl क्रम model-specअगरic implementation quirks first,
	 * such that platक्रमm पूर्णांकegration quirks can pick it up and
	 * inherit from it अगर necessary.
	 */
	चयन (smmu->model) अणु
	हाल ARM_MMU500:
		smmu->impl = &arm_mmu500_impl;
		अवरोध;
	हाल CAVIUM_SMMUV2:
		वापस cavium_smmu_impl_init(smmu);
	शेष:
		अवरोध;
	पूर्ण

	/* This is implicitly MMU-400 */
	अगर (of_property_पढ़ो_bool(np, "calxeda,smmu-secure-config-access"))
		smmu->impl = &calxeda_impl;

	अगर (of_device_is_compatible(np, "nvidia,tegra194-smmu"))
		वापस nvidia_smmu_impl_init(smmu);

	smmu = qcom_smmu_impl_init(smmu);

	अगर (of_device_is_compatible(np, "marvell,ap806-smmu-500"))
		smmu->impl = &mrvl_mmu500_impl;

	वापस smmu;
पूर्ण
