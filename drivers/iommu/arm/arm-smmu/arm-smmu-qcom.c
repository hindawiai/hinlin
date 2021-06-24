<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2019, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/adreno-smmu-priv.h>
#समावेश <linux/of_device.h>
#समावेश <linux/qcom_scm.h>

#समावेश "arm-smmu.h"

काष्ठा qcom_smmu अणु
	काष्ठा arm_smmu_device smmu;
	bool bypass_quirk;
	u8 bypass_cbndx;
पूर्ण;

अटल काष्ठा qcom_smmu *to_qcom_smmu(काष्ठा arm_smmu_device *smmu)
अणु
	वापस container_of(smmu, काष्ठा qcom_smmu, smmu);
पूर्ण

अटल व्योम qcom_adreno_smmu_ग_लिखो_sctlr(काष्ठा arm_smmu_device *smmu, पूर्णांक idx,
		u32 reg)
अणु
	/*
	 * On the GPU device we want to process subsequent transactions after a
	 * fault to keep the GPU from hanging
	 */
	reg |= ARM_SMMU_SCTLR_HUPCF;

	arm_smmu_cb_ग_लिखो(smmu, idx, ARM_SMMU_CB_SCTLR, reg);
पूर्ण

#घोषणा QCOM_ADRENO_SMMU_GPU_SID 0

अटल bool qcom_adreno_smmu_is_gpu_device(काष्ठा device *dev)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	पूर्णांक i;

	/*
	 * The GPU will always use SID 0 so that is a handy way to uniquely
	 * identअगरy it and configure it क्रम per-instance pagetables
	 */
	क्रम (i = 0; i < fwspec->num_ids; i++) अणु
		u16 sid = FIELD_GET(ARM_SMMU_SMR_ID, fwspec->ids[i]);

		अगर (sid == QCOM_ADRENO_SMMU_GPU_SID)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल स्थिर काष्ठा io_pgtable_cfg *qcom_adreno_smmu_get_ttbr1_cfg(
		स्थिर व्योम *cookie)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = (व्योम *)cookie;
	काष्ठा io_pgtable *pgtable =
		io_pgtable_ops_to_pgtable(smmu_करोमुख्य->pgtbl_ops);
	वापस &pgtable->cfg;
पूर्ण

/*
 * Local implementation to configure TTBR0 with the specअगरied pagetable config.
 * The GPU driver will call this to enable TTBR0 when per-instance pagetables
 * are active
 */

अटल पूर्णांक qcom_adreno_smmu_set_ttbr0_cfg(स्थिर व्योम *cookie,
		स्थिर काष्ठा io_pgtable_cfg *pgtbl_cfg)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = (व्योम *)cookie;
	काष्ठा io_pgtable *pgtable = io_pgtable_ops_to_pgtable(smmu_करोमुख्य->pgtbl_ops);
	काष्ठा arm_smmu_cfg *cfg = &smmu_करोमुख्य->cfg;
	काष्ठा arm_smmu_cb *cb = &smmu_करोमुख्य->smmu->cbs[cfg->cbndx];

	/* The करोमुख्य must have split pagetables alपढ़ोy enabled */
	अगर (cb->tcr[0] & ARM_SMMU_TCR_EPD1)
		वापस -EINVAL;

	/* If the pagetable config is शून्य, disable TTBR0 */
	अगर (!pgtbl_cfg) अणु
		/* Do nothing अगर it is alपढ़ोy disabled */
		अगर ((cb->tcr[0] & ARM_SMMU_TCR_EPD0))
			वापस -EINVAL;

		/* Set TCR to the original configuration */
		cb->tcr[0] = arm_smmu_lpae_tcr(&pgtable->cfg);
		cb->ttbr[0] = FIELD_PREP(ARM_SMMU_TTBRn_ASID, cb->cfg->asid);
	पूर्ण अन्यथा अणु
		u32 tcr = cb->tcr[0];

		/* Don't call this again अगर TTBR0 is alपढ़ोy enabled */
		अगर (!(cb->tcr[0] & ARM_SMMU_TCR_EPD0))
			वापस -EINVAL;

		tcr |= arm_smmu_lpae_tcr(pgtbl_cfg);
		tcr &= ~(ARM_SMMU_TCR_EPD0 | ARM_SMMU_TCR_EPD1);

		cb->tcr[0] = tcr;
		cb->ttbr[0] = pgtbl_cfg->arm_lpae_s1_cfg.ttbr;
		cb->ttbr[0] |= FIELD_PREP(ARM_SMMU_TTBRn_ASID, cb->cfg->asid);
	पूर्ण

	arm_smmu_ग_लिखो_context_bank(smmu_करोमुख्य->smmu, cb->cfg->cbndx);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_adreno_smmu_alloc_context_bank(काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य,
					       काष्ठा arm_smmu_device *smmu,
					       काष्ठा device *dev, पूर्णांक start)
अणु
	पूर्णांक count;

	/*
	 * Assign context bank 0 to the GPU device so the GPU hardware can
	 * चयन pagetables
	 */
	अगर (qcom_adreno_smmu_is_gpu_device(dev)) अणु
		start = 0;
		count = 1;
	पूर्ण अन्यथा अणु
		start = 1;
		count = smmu->num_context_banks;
	पूर्ण

	वापस __arm_smmu_alloc_biपंचांगap(smmu->context_map, start, count);
पूर्ण

अटल पूर्णांक qcom_adreno_smmu_init_context(काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य,
		काष्ठा io_pgtable_cfg *pgtbl_cfg, काष्ठा device *dev)
अणु
	काष्ठा adreno_smmu_priv *priv;

	/* Only enable split pagetables क्रम the GPU device (SID 0) */
	अगर (!qcom_adreno_smmu_is_gpu_device(dev))
		वापस 0;

	/*
	 * All tarमाला_लो that use the qcom,adreno-smmu compatible string *should*
	 * be AARCH64 stage 1 but द्विगुन check because the arm-smmu code assumes
	 * that is the हाल when the TTBR1 quirk is enabled
	 */
	अगर ((smmu_करोमुख्य->stage == ARM_SMMU_DOMAIN_S1) &&
	    (smmu_करोमुख्य->cfg.fmt == ARM_SMMU_CTX_FMT_AARCH64))
		pgtbl_cfg->quirks |= IO_PGTABLE_QUIRK_ARM_TTBR1;

	/*
	 * Initialize निजी पूर्णांकerface with GPU:
	 */

	priv = dev_get_drvdata(dev);
	priv->cookie = smmu_करोमुख्य;
	priv->get_ttbr1_cfg = qcom_adreno_smmu_get_ttbr1_cfg;
	priv->set_ttbr0_cfg = qcom_adreno_smmu_set_ttbr0_cfg;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_smmu_client_of_match[] __maybe_unused = अणु
	अणु .compatible = "qcom,adreno" पूर्ण,
	अणु .compatible = "qcom,mdp4" पूर्ण,
	अणु .compatible = "qcom,mdss" पूर्ण,
	अणु .compatible = "qcom,sc7180-mdss" पूर्ण,
	अणु .compatible = "qcom,sc7180-mss-pil" पूर्ण,
	अणु .compatible = "qcom,sc8180x-mdss" पूर्ण,
	अणु .compatible = "qcom,sdm845-mdss" पूर्ण,
	अणु .compatible = "qcom,sdm845-mss-pil" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक qcom_smmu_cfg_probe(काष्ठा arm_smmu_device *smmu)
अणु
	अचिन्हित पूर्णांक last_s2cr = ARM_SMMU_GR0_S2CR(smmu->num_mapping_groups - 1);
	काष्ठा qcom_smmu *qsmmu = to_qcom_smmu(smmu);
	u32 reg;
	u32 smr;
	पूर्णांक i;

	/*
	 * With some firmware versions ग_लिखोs to S2CR of type FAULT are
	 * ignored, and writing BYPASS will end up written as FAULT in the
	 * रेजिस्टर. Perक्रमm a ग_लिखो to S2CR to detect अगर this is the हाल and
	 * अगर so reserve a context bank to emulate bypass streams.
	 */
	reg = FIELD_PREP(ARM_SMMU_S2CR_TYPE, S2CR_TYPE_BYPASS) |
	      FIELD_PREP(ARM_SMMU_S2CR_CBNDX, 0xff) |
	      FIELD_PREP(ARM_SMMU_S2CR_PRIVCFG, S2CR_PRIVCFG_DEFAULT);
	arm_smmu_gr0_ग_लिखो(smmu, last_s2cr, reg);
	reg = arm_smmu_gr0_पढ़ो(smmu, last_s2cr);
	अगर (FIELD_GET(ARM_SMMU_S2CR_TYPE, reg) != S2CR_TYPE_BYPASS) अणु
		qsmmu->bypass_quirk = true;
		qsmmu->bypass_cbndx = smmu->num_context_banks - 1;

		set_bit(qsmmu->bypass_cbndx, smmu->context_map);

		arm_smmu_cb_ग_लिखो(smmu, qsmmu->bypass_cbndx, ARM_SMMU_CB_SCTLR, 0);

		reg = FIELD_PREP(ARM_SMMU_CBAR_TYPE, CBAR_TYPE_S1_TRANS_S2_BYPASS);
		arm_smmu_gr1_ग_लिखो(smmu, ARM_SMMU_GR1_CBAR(qsmmu->bypass_cbndx), reg);
	पूर्ण

	क्रम (i = 0; i < smmu->num_mapping_groups; i++) अणु
		smr = arm_smmu_gr0_पढ़ो(smmu, ARM_SMMU_GR0_SMR(i));

		अगर (FIELD_GET(ARM_SMMU_SMR_VALID, smr)) अणु
			/* Ignore valid bit क्रम SMR mask extraction. */
			smr &= ~ARM_SMMU_SMR_VALID;
			smmu->smrs[i].id = FIELD_GET(ARM_SMMU_SMR_ID, smr);
			smmu->smrs[i].mask = FIELD_GET(ARM_SMMU_SMR_MASK, smr);
			smmu->smrs[i].valid = true;

			smmu->s2crs[i].type = S2CR_TYPE_BYPASS;
			smmu->s2crs[i].privcfg = S2CR_PRIVCFG_DEFAULT;
			smmu->s2crs[i].cbndx = 0xff;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qcom_smmu_ग_लिखो_s2cr(काष्ठा arm_smmu_device *smmu, पूर्णांक idx)
अणु
	काष्ठा arm_smmu_s2cr *s2cr = smmu->s2crs + idx;
	काष्ठा qcom_smmu *qsmmu = to_qcom_smmu(smmu);
	u32 cbndx = s2cr->cbndx;
	u32 type = s2cr->type;
	u32 reg;

	अगर (qsmmu->bypass_quirk) अणु
		अगर (type == S2CR_TYPE_BYPASS) अणु
			/*
			 * Firmware with quirky S2CR handling will substitute
			 * BYPASS ग_लिखोs with FAULT, so poपूर्णांक the stream to the
			 * reserved context bank and ask क्रम translation on the
			 * stream
			 */
			type = S2CR_TYPE_TRANS;
			cbndx = qsmmu->bypass_cbndx;
		पूर्ण अन्यथा अगर (type == S2CR_TYPE_FAULT) अणु
			/*
			 * Firmware with quirky S2CR handling will ignore FAULT
			 * ग_लिखोs, so trick it to ग_लिखो FAULT by asking क्रम a
			 * BYPASS.
			 */
			type = S2CR_TYPE_BYPASS;
			cbndx = 0xff;
		पूर्ण
	पूर्ण

	reg = FIELD_PREP(ARM_SMMU_S2CR_TYPE, type) |
	      FIELD_PREP(ARM_SMMU_S2CR_CBNDX, cbndx) |
	      FIELD_PREP(ARM_SMMU_S2CR_PRIVCFG, s2cr->privcfg);
	arm_smmu_gr0_ग_लिखो(smmu, ARM_SMMU_GR0_S2CR(idx), reg);
पूर्ण

अटल पूर्णांक qcom_smmu_def_करोमुख्य_type(काष्ठा device *dev)
अणु
	स्थिर काष्ठा of_device_id *match =
		of_match_device(qcom_smmu_client_of_match, dev);

	वापस match ? IOMMU_DOMAIN_IDENTITY : 0;
पूर्ण

अटल पूर्णांक qcom_sdm845_smmu500_reset(काष्ठा arm_smmu_device *smmu)
अणु
	पूर्णांक ret;

	/*
	 * To address perक्रमmance degradation in non-real समय clients,
	 * such as USB and UFS, turn off रुको-क्रम-safe on sdm845 based boards,
	 * such as MTP and db845, whose firmwares implement secure monitor
	 * call handlers to turn on/off the रुको-क्रम-safe logic.
	 */
	ret = qcom_scm_qsmmu500_रुको_safe_toggle(0);
	अगर (ret)
		dev_warn(smmu->dev, "Failed to turn off SAFE logic\n");

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_smmu500_reset(काष्ठा arm_smmu_device *smmu)
अणु
	स्थिर काष्ठा device_node *np = smmu->dev->of_node;

	arm_mmu500_reset(smmu);

	अगर (of_device_is_compatible(np, "qcom,sdm845-smmu-500"))
		वापस qcom_sdm845_smmu500_reset(smmu);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा arm_smmu_impl qcom_smmu_impl = अणु
	.cfg_probe = qcom_smmu_cfg_probe,
	.def_करोमुख्य_type = qcom_smmu_def_करोमुख्य_type,
	.reset = qcom_smmu500_reset,
	.ग_लिखो_s2cr = qcom_smmu_ग_लिखो_s2cr,
पूर्ण;

अटल स्थिर काष्ठा arm_smmu_impl qcom_adreno_smmu_impl = अणु
	.init_context = qcom_adreno_smmu_init_context,
	.def_करोमुख्य_type = qcom_smmu_def_करोमुख्य_type,
	.reset = qcom_smmu500_reset,
	.alloc_context_bank = qcom_adreno_smmu_alloc_context_bank,
	.ग_लिखो_sctlr = qcom_adreno_smmu_ग_लिखो_sctlr,
पूर्ण;

अटल काष्ठा arm_smmu_device *qcom_smmu_create(काष्ठा arm_smmu_device *smmu,
		स्थिर काष्ठा arm_smmu_impl *impl)
अणु
	काष्ठा qcom_smmu *qsmmu;

	/* Check to make sure qcom_scm has finished probing */
	अगर (!qcom_scm_is_available())
		वापस ERR_PTR(-EPROBE_DEFER);

	qsmmu = devm_kपुनः_स्मृति(smmu->dev, smmu, माप(*qsmmu), GFP_KERNEL);
	अगर (!qsmmu)
		वापस ERR_PTR(-ENOMEM);

	qsmmu->smmu.impl = impl;

	वापस &qsmmu->smmu;
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused qcom_smmu_impl_of_match[] = अणु
	अणु .compatible = "qcom,msm8998-smmu-v2" पूर्ण,
	अणु .compatible = "qcom,sc7180-smmu-500" पूर्ण,
	अणु .compatible = "qcom,sc8180x-smmu-500" पूर्ण,
	अणु .compatible = "qcom,sdm630-smmu-v2" पूर्ण,
	अणु .compatible = "qcom,sdm845-smmu-500" पूर्ण,
	अणु .compatible = "qcom,sm8150-smmu-500" पूर्ण,
	अणु .compatible = "qcom,sm8250-smmu-500" पूर्ण,
	अणु .compatible = "qcom,sm8350-smmu-500" पूर्ण,
	अणु पूर्ण
पूर्ण;

काष्ठा arm_smmu_device *qcom_smmu_impl_init(काष्ठा arm_smmu_device *smmu)
अणु
	स्थिर काष्ठा device_node *np = smmu->dev->of_node;

	अगर (of_match_node(qcom_smmu_impl_of_match, np))
		वापस qcom_smmu_create(smmu, &qcom_smmu_impl);

	अगर (of_device_is_compatible(np, "qcom,adreno-smmu"))
		वापस qcom_smmu_create(smmu, &qcom_adreno_smmu_impl);

	वापस smmu;
पूर्ण
