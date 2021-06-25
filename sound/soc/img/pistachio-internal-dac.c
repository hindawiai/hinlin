<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pistachio पूर्णांकernal dac driver
 *
 * Copyright (C) 2015 Imagination Technologies Ltd.
 *
 * Author: Damien Horsley <Damien.Horsley@imgtec.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#घोषणा PISTACHIO_INTERNAL_DAC_CTRL			0x40
#घोषणा PISTACHIO_INTERNAL_DAC_CTRL_PWR_SEL_MASK	0x2
#घोषणा PISTACHIO_INTERNAL_DAC_CTRL_PWRDN_MASK		0x1

#घोषणा PISTACHIO_INTERNAL_DAC_SRST			0x44
#घोषणा PISTACHIO_INTERNAL_DAC_SRST_MASK		0x1

#घोषणा PISTACHIO_INTERNAL_DAC_GTI_CTRL			0x48
#घोषणा PISTACHIO_INTERNAL_DAC_GTI_CTRL_ADDR_SHIFT	0
#घोषणा PISTACHIO_INTERNAL_DAC_GTI_CTRL_ADDR_MASK	0xFFF
#घोषणा PISTACHIO_INTERNAL_DAC_GTI_CTRL_WE_MASK		0x1000
#घोषणा PISTACHIO_INTERNAL_DAC_GTI_CTRL_WDATA_SHIFT	13
#घोषणा PISTACHIO_INTERNAL_DAC_GTI_CTRL_WDATA_MASK	0x1FE000

#घोषणा PISTACHIO_INTERNAL_DAC_PWR			0x1
#घोषणा PISTACHIO_INTERNAL_DAC_PWR_MASK			0x1

#घोषणा PISTACHIO_INTERNAL_DAC_FORMATS (SNDRV_PCM_FMTBIT_S24_LE |  \
					SNDRV_PCM_FMTBIT_S32_LE)

/* codec निजी data */
काष्ठा pistachio_पूर्णांकernal_dac अणु
	काष्ठा regmap *regmap;
	काष्ठा regulator *supply;
	bool mute;
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new pistachio_पूर्णांकernal_dac_snd_controls[] = अणु
	SOC_SINGLE("Playback Switch", PISTACHIO_INTERNAL_DAC_CTRL, 2, 1, 1)
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget pistachio_पूर्णांकernal_dac_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("DAC", "Playback", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_OUTPUT("AOUTL"),
	SND_SOC_DAPM_OUTPUT("AOUTR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route pistachio_पूर्णांकernal_dac_routes[] = अणु
	अणु "AOUTL", शून्य, "DAC" पूर्ण,
	अणु "AOUTR", शून्य, "DAC" पूर्ण,
पूर्ण;

अटल व्योम pistachio_पूर्णांकernal_dac_reg_ग_लिखोl(काष्ठा regmap *top_regs,
						u32 val, u32 reg)
अणु
	regmap_update_bits(top_regs, PISTACHIO_INTERNAL_DAC_GTI_CTRL,
			PISTACHIO_INTERNAL_DAC_GTI_CTRL_ADDR_MASK,
			reg << PISTACHIO_INTERNAL_DAC_GTI_CTRL_ADDR_SHIFT);

	regmap_update_bits(top_regs, PISTACHIO_INTERNAL_DAC_GTI_CTRL,
			PISTACHIO_INTERNAL_DAC_GTI_CTRL_WDATA_MASK,
			val << PISTACHIO_INTERNAL_DAC_GTI_CTRL_WDATA_SHIFT);

	regmap_update_bits(top_regs, PISTACHIO_INTERNAL_DAC_GTI_CTRL,
			PISTACHIO_INTERNAL_DAC_GTI_CTRL_WE_MASK,
			PISTACHIO_INTERNAL_DAC_GTI_CTRL_WE_MASK);

	regmap_update_bits(top_regs, PISTACHIO_INTERNAL_DAC_GTI_CTRL,
			PISTACHIO_INTERNAL_DAC_GTI_CTRL_WE_MASK, 0);
पूर्ण

अटल व्योम pistachio_पूर्णांकernal_dac_pwr_off(काष्ठा pistachio_पूर्णांकernal_dac *dac)
अणु
	regmap_update_bits(dac->regmap, PISTACHIO_INTERNAL_DAC_CTRL,
		PISTACHIO_INTERNAL_DAC_CTRL_PWRDN_MASK,
		PISTACHIO_INTERNAL_DAC_CTRL_PWRDN_MASK);

	pistachio_पूर्णांकernal_dac_reg_ग_लिखोl(dac->regmap, 0,
					PISTACHIO_INTERNAL_DAC_PWR);
पूर्ण

अटल व्योम pistachio_पूर्णांकernal_dac_pwr_on(काष्ठा pistachio_पूर्णांकernal_dac *dac)
अणु
	regmap_update_bits(dac->regmap, PISTACHIO_INTERNAL_DAC_SRST,
			PISTACHIO_INTERNAL_DAC_SRST_MASK,
			PISTACHIO_INTERNAL_DAC_SRST_MASK);

	regmap_update_bits(dac->regmap, PISTACHIO_INTERNAL_DAC_SRST,
			PISTACHIO_INTERNAL_DAC_SRST_MASK, 0);

	pistachio_पूर्णांकernal_dac_reg_ग_लिखोl(dac->regmap,
					PISTACHIO_INTERNAL_DAC_PWR_MASK,
					PISTACHIO_INTERNAL_DAC_PWR);

	regmap_update_bits(dac->regmap, PISTACHIO_INTERNAL_DAC_CTRL,
			PISTACHIO_INTERNAL_DAC_CTRL_PWRDN_MASK, 0);
पूर्ण

अटल काष्ठा snd_soc_dai_driver pistachio_पूर्णांकernal_dac_dais[] = अणु
	अणु
		.name = "pistachio_internal_dac",
		.playback = अणु
			.stream_name = "Playback",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000,
			.क्रमmats = PISTACHIO_INTERNAL_DAC_FORMATS,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल पूर्णांक pistachio_पूर्णांकernal_dac_codec_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा pistachio_पूर्णांकernal_dac *dac = snd_soc_component_get_drvdata(component);

	snd_soc_component_init_regmap(component, dac->regmap);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver pistachio_पूर्णांकernal_dac_driver = अणु
	.probe			= pistachio_पूर्णांकernal_dac_codec_probe,
	.controls		= pistachio_पूर्णांकernal_dac_snd_controls,
	.num_controls		= ARRAY_SIZE(pistachio_पूर्णांकernal_dac_snd_controls),
	.dapm_widमाला_लो		= pistachio_पूर्णांकernal_dac_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(pistachio_पूर्णांकernal_dac_widमाला_लो),
	.dapm_routes		= pistachio_पूर्णांकernal_dac_routes,
	.num_dapm_routes	= ARRAY_SIZE(pistachio_पूर्णांकernal_dac_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक pistachio_पूर्णांकernal_dac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pistachio_पूर्णांकernal_dac *dac;
	पूर्णांक ret, voltage;
	काष्ठा device *dev = &pdev->dev;
	u32 reg;

	dac = devm_kzalloc(dev, माप(*dac), GFP_KERNEL);

	अगर (!dac)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, dac);

	dac->regmap = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
							    "img,cr-top");
	अगर (IS_ERR(dac->regmap))
		वापस PTR_ERR(dac->regmap);

	dac->supply = devm_regulator_get(dev, "VDD");
	अगर (IS_ERR(dac->supply)) अणु
		ret = PTR_ERR(dac->supply);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to acquire supply 'VDD-supply': %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_enable(dac->supply);
	अगर (ret) अणु
		dev_err(dev, "failed to enable supply: %d\n", ret);
		वापस ret;
	पूर्ण

	voltage = regulator_get_voltage(dac->supply);

	चयन (voltage) अणु
	हाल 1800000:
		reg = 0;
		अवरोध;
	हाल 3300000:
		reg = PISTACHIO_INTERNAL_DAC_CTRL_PWR_SEL_MASK;
		अवरोध;
	शेष:
		dev_err(dev, "invalid voltage: %d\n", voltage);
		ret = -EINVAL;
		जाओ err_regulator;
	पूर्ण

	regmap_update_bits(dac->regmap, PISTACHIO_INTERNAL_DAC_CTRL,
			PISTACHIO_INTERNAL_DAC_CTRL_PWR_SEL_MASK, reg);

	pistachio_पूर्णांकernal_dac_pwr_off(dac);
	pistachio_पूर्णांकernal_dac_pwr_on(dac);

	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_idle(dev);

	ret = devm_snd_soc_रेजिस्टर_component(dev,
			&pistachio_पूर्णांकernal_dac_driver,
			pistachio_पूर्णांकernal_dac_dais,
			ARRAY_SIZE(pistachio_पूर्णांकernal_dac_dais));
	अगर (ret) अणु
		dev_err(dev, "failed to register component: %d\n", ret);
		जाओ err_pwr;
	पूर्ण

	वापस 0;

err_pwr:
	pm_runसमय_disable(&pdev->dev);
	pistachio_पूर्णांकernal_dac_pwr_off(dac);
err_regulator:
	regulator_disable(dac->supply);

	वापस ret;
पूर्ण

अटल पूर्णांक pistachio_पूर्णांकernal_dac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pistachio_पूर्णांकernal_dac *dac = dev_get_drvdata(&pdev->dev);

	pm_runसमय_disable(&pdev->dev);
	pistachio_पूर्णांकernal_dac_pwr_off(dac);
	regulator_disable(dac->supply);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक pistachio_पूर्णांकernal_dac_rt_resume(काष्ठा device *dev)
अणु
	काष्ठा pistachio_पूर्णांकernal_dac *dac = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regulator_enable(dac->supply);
	अगर (ret) अणु
		dev_err(dev, "failed to enable supply: %d\n", ret);
		वापस ret;
	पूर्ण

	pistachio_पूर्णांकernal_dac_pwr_on(dac);

	वापस 0;
पूर्ण

अटल पूर्णांक pistachio_पूर्णांकernal_dac_rt_suspend(काष्ठा device *dev)
अणु
	काष्ठा pistachio_पूर्णांकernal_dac *dac = dev_get_drvdata(dev);

	pistachio_पूर्णांकernal_dac_pwr_off(dac);

	regulator_disable(dac->supply);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops pistachio_पूर्णांकernal_dac_pm_ops = अणु
	SET_RUNTIME_PM_OPS(pistachio_पूर्णांकernal_dac_rt_suspend,
			pistachio_पूर्णांकernal_dac_rt_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id pistachio_पूर्णांकernal_dac_of_match[] = अणु
	अणु .compatible = "img,pistachio-internal-dac" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pistachio_पूर्णांकernal_dac_of_match);

अटल काष्ठा platक्रमm_driver pistachio_पूर्णांकernal_dac_plat_driver = अणु
	.driver = अणु
		.name = "img-pistachio-internal-dac",
		.of_match_table = pistachio_पूर्णांकernal_dac_of_match,
		.pm = &pistachio_पूर्णांकernal_dac_pm_ops
	पूर्ण,
	.probe = pistachio_पूर्णांकernal_dac_probe,
	.हटाओ = pistachio_पूर्णांकernal_dac_हटाओ
पूर्ण;
module_platक्रमm_driver(pistachio_पूर्णांकernal_dac_plat_driver);

MODULE_DESCRIPTION("Pistachio Internal DAC driver");
MODULE_AUTHOR("Damien Horsley <Damien.Horsley@imgtec.com>");
MODULE_LICENSE("GPL v2");
