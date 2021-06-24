<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc.
 * Author: Jianxin Pan <jianxin.pan@amlogic.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/पन.स>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <dt-bindings/घातer/meson-a1-घातer.h>
#समावेश <linux/arm-smccc.h>
#समावेश <linux/firmware/meson/meson_sm.h>
#समावेश <linux/module.h>

#घोषणा PWRC_ON		1
#घोषणा PWRC_OFF	0

काष्ठा meson_secure_pwrc_करोमुख्य अणु
	काष्ठा generic_pm_करोमुख्य base;
	अचिन्हित पूर्णांक index;
	काष्ठा meson_secure_pwrc *pwrc;
पूर्ण;

काष्ठा meson_secure_pwrc अणु
	काष्ठा meson_secure_pwrc_करोमुख्य *करोमुख्यs;
	काष्ठा genpd_onecell_data xlate;
	काष्ठा meson_sm_firmware *fw;
पूर्ण;

काष्ठा meson_secure_pwrc_करोमुख्य_desc अणु
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक flags;
	अक्षर *name;
	bool (*is_off)(काष्ठा meson_secure_pwrc_करोमुख्य *pwrc_करोमुख्य);
पूर्ण;

काष्ठा meson_secure_pwrc_करोमुख्य_data अणु
	अचिन्हित पूर्णांक count;
	काष्ठा meson_secure_pwrc_करोमुख्य_desc *करोमुख्यs;
पूर्ण;

अटल bool pwrc_secure_is_off(काष्ठा meson_secure_pwrc_करोमुख्य *pwrc_करोमुख्य)
अणु
	पूर्णांक is_off = 1;

	अगर (meson_sm_call(pwrc_करोमुख्य->pwrc->fw, SM_A1_PWRC_GET, &is_off,
			  pwrc_करोमुख्य->index, 0, 0, 0, 0) < 0)
		pr_err("failed to get power domain status\n");

	वापस is_off;
पूर्ण

अटल पूर्णांक meson_secure_pwrc_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	पूर्णांक ret = 0;
	काष्ठा meson_secure_pwrc_करोमुख्य *pwrc_करोमुख्य =
		container_of(करोमुख्य, काष्ठा meson_secure_pwrc_करोमुख्य, base);

	अगर (meson_sm_call(pwrc_करोमुख्य->pwrc->fw, SM_A1_PWRC_SET, शून्य,
			  pwrc_करोमुख्य->index, PWRC_OFF, 0, 0, 0) < 0) अणु
		pr_err("failed to set power domain off\n");
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक meson_secure_pwrc_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	पूर्णांक ret = 0;
	काष्ठा meson_secure_pwrc_करोमुख्य *pwrc_करोमुख्य =
		container_of(करोमुख्य, काष्ठा meson_secure_pwrc_करोमुख्य, base);

	अगर (meson_sm_call(pwrc_करोमुख्य->pwrc->fw, SM_A1_PWRC_SET, शून्य,
			  pwrc_करोमुख्य->index, PWRC_ON, 0, 0, 0) < 0) अणु
		pr_err("failed to set power domain on\n");
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा SEC_PD(__name, __flag)			\
[PWRC_##__name##_ID] =				\
अणु						\
	.name = #__name,			\
	.index = PWRC_##__name##_ID,		\
	.is_off = pwrc_secure_is_off,	\
	.flags = __flag,			\
पूर्ण

अटल काष्ठा meson_secure_pwrc_करोमुख्य_desc a1_pwrc_करोमुख्यs[] = अणु
	SEC_PD(DSPA,	0),
	SEC_PD(DSPB,	0),
	/* UART should keep working in ATF after suspend and beक्रमe resume */
	SEC_PD(UART,	GENPD_FLAG_ALWAYS_ON),
	/* DMC is क्रम DDR PHY ana/dig and DMC, and should be always on */
	SEC_PD(DMC,	GENPD_FLAG_ALWAYS_ON),
	SEC_PD(I2C,	0),
	SEC_PD(PSRAM,	0),
	SEC_PD(ACODEC,	0),
	SEC_PD(AUDIO,	0),
	SEC_PD(OTP,	0),
	SEC_PD(DMA,	0),
	SEC_PD(SD_EMMC,	0),
	SEC_PD(RAMA,	0),
	/* SRAMB is used as ATF runसमय memory, and should be always on */
	SEC_PD(RAMB,	GENPD_FLAG_ALWAYS_ON),
	SEC_PD(IR,	0),
	SEC_PD(SPICC,	0),
	SEC_PD(SPIFC,	0),
	SEC_PD(USB,	0),
	/* NIC is क्रम the Arm NIC-400 पूर्णांकerconnect, and should be always on */
	SEC_PD(NIC,	GENPD_FLAG_ALWAYS_ON),
	SEC_PD(PDMIN,	0),
	SEC_PD(RSA,	0),
पूर्ण;

अटल पूर्णांक meson_secure_pwrc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	काष्ठा device_node *sm_np;
	काष्ठा meson_secure_pwrc *pwrc;
	स्थिर काष्ठा meson_secure_pwrc_करोमुख्य_data *match;

	match = of_device_get_match_data(&pdev->dev);
	अगर (!match) अणु
		dev_err(&pdev->dev, "failed to get match data\n");
		वापस -ENODEV;
	पूर्ण

	sm_np = of_find_compatible_node(शून्य, शून्य, "amlogic,meson-gxbb-sm");
	अगर (!sm_np) अणु
		dev_err(&pdev->dev, "no secure-monitor node\n");
		वापस -ENODEV;
	पूर्ण

	pwrc = devm_kzalloc(&pdev->dev, माप(*pwrc), GFP_KERNEL);
	अगर (!pwrc)
		वापस -ENOMEM;

	pwrc->fw = meson_sm_get(sm_np);
	of_node_put(sm_np);
	अगर (!pwrc->fw)
		वापस -EPROBE_DEFER;

	pwrc->xlate.करोमुख्यs = devm_kसुस्मृति(&pdev->dev, match->count,
					   माप(*pwrc->xlate.करोमुख्यs),
					   GFP_KERNEL);
	अगर (!pwrc->xlate.करोमुख्यs)
		वापस -ENOMEM;

	pwrc->करोमुख्यs = devm_kसुस्मृति(&pdev->dev, match->count,
				     माप(*pwrc->करोमुख्यs), GFP_KERNEL);
	अगर (!pwrc->करोमुख्यs)
		वापस -ENOMEM;

	pwrc->xlate.num_करोमुख्यs = match->count;
	platक्रमm_set_drvdata(pdev, pwrc);

	क्रम (i = 0 ; i < match->count ; ++i) अणु
		काष्ठा meson_secure_pwrc_करोमुख्य *करोm = &pwrc->करोमुख्यs[i];

		अगर (!match->करोमुख्यs[i].index)
			जारी;

		करोm->pwrc = pwrc;
		करोm->index = match->करोमुख्यs[i].index;
		करोm->base.name = match->करोमुख्यs[i].name;
		करोm->base.flags = match->करोमुख्यs[i].flags;
		करोm->base.घातer_on = meson_secure_pwrc_on;
		करोm->base.घातer_off = meson_secure_pwrc_off;

		pm_genpd_init(&करोm->base, शून्य, match->करोमुख्यs[i].is_off(करोm));

		pwrc->xlate.करोमुख्यs[i] = &करोm->base;
	पूर्ण

	वापस of_genpd_add_provider_onecell(pdev->dev.of_node, &pwrc->xlate);
पूर्ण

अटल काष्ठा meson_secure_pwrc_करोमुख्य_data meson_secure_a1_pwrc_data = अणु
	.करोमुख्यs = a1_pwrc_करोमुख्यs,
	.count = ARRAY_SIZE(a1_pwrc_करोमुख्यs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson_secure_pwrc_match_table[] = अणु
	अणु
		.compatible = "amlogic,meson-a1-pwrc",
		.data = &meson_secure_a1_pwrc_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_secure_pwrc_match_table);

अटल काष्ठा platक्रमm_driver meson_secure_pwrc_driver = अणु
	.probe = meson_secure_pwrc_probe,
	.driver = अणु
		.name		= "meson_secure_pwrc",
		.of_match_table	= meson_secure_pwrc_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(meson_secure_pwrc_driver);
MODULE_LICENSE("Dual MIT/GPL");
