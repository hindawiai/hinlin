<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * dmic.c  --  SoC audio क्रम Generic Digital MICs
 *
 * Author: Liam Girdwood <lrg@slimlogic.co.uk>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>

#घोषणा MAX_MODESWITCH_DELAY 70
अटल पूर्णांक modeचयन_delay;
module_param(modeचयन_delay, uपूर्णांक, 0644);

अटल पूर्णांक wakeup_delay;
module_param(wakeup_delay, uपूर्णांक, 0644);

काष्ठा dmic अणु
	काष्ठा gpio_desc *gpio_en;
	पूर्णांक wakeup_delay;
	/* Delay after DMIC mode चयन */
	पूर्णांक modeचयन_delay;
पूर्ण;

अटल पूर्णांक dmic_daiops_trigger(काष्ठा snd_pcm_substream *substream,
			       पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा dmic *dmic = snd_soc_component_get_drvdata(component);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_STOP:
		अगर (dmic->modeचयन_delay)
			mdelay(dmic->modeचयन_delay);

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops dmic_dai_ops = अणु
	.trigger	= dmic_daiops_trigger,
पूर्ण;

अटल पूर्णांक dmic_aअगर_event(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event) अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा dmic *dmic = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		अगर (dmic->gpio_en)
			gpiod_set_value_cansleep(dmic->gpio_en, 1);

		अगर (dmic->wakeup_delay)
			msleep(dmic->wakeup_delay);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		अगर (dmic->gpio_en)
			gpiod_set_value_cansleep(dmic->gpio_en, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver dmic_dai = अणु
	.name = "dmic-hifi",
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_CONTINUOUS,
		.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE
			| SNDRV_PCM_FMTBIT_S24_LE
			| SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.ops    = &dmic_dai_ops,
पूर्ण;

अटल पूर्णांक dmic_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा dmic *dmic;

	dmic = devm_kzalloc(component->dev, माप(*dmic), GFP_KERNEL);
	अगर (!dmic)
		वापस -ENOMEM;

	dmic->gpio_en = devm_gpiod_get_optional(component->dev,
						"dmicen", GPIOD_OUT_LOW);
	अगर (IS_ERR(dmic->gpio_en))
		वापस PTR_ERR(dmic->gpio_en);

	device_property_पढ़ो_u32(component->dev, "wakeup-delay-ms",
				 &dmic->wakeup_delay);
	device_property_पढ़ो_u32(component->dev, "modeswitch-delay-ms",
				 &dmic->modeचयन_delay);
	अगर (wakeup_delay)
		dmic->wakeup_delay  = wakeup_delay;
	अगर (modeचयन_delay)
		dmic->modeचयन_delay  = modeचयन_delay;

	अगर (dmic->modeचयन_delay > MAX_MODESWITCH_DELAY)
		dmic->modeचयन_delay = MAX_MODESWITCH_DELAY;

	snd_soc_component_set_drvdata(component, dmic);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget dmic_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_OUT_E("DMIC AIF", "Capture", 0,
			       SND_SOC_NOPM, 0, 0, dmic_aअगर_event,
			       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_INPUT("DMic"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route पूर्णांकercon[] = अणु
	अणु"DMIC AIF", शून्य, "DMic"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_dmic = अणु
	.probe			= dmic_component_probe,
	.dapm_widमाला_लो		= dmic_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(dmic_dapm_widमाला_लो),
	.dapm_routes		= पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(पूर्णांकercon),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक dmic_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;
	u32 chans;
	काष्ठा snd_soc_dai_driver *dai_drv = &dmic_dai;

	अगर (pdev->dev.of_node) अणु
		err = of_property_पढ़ो_u32(pdev->dev.of_node, "num-channels", &chans);
		अगर (err && (err != -EINVAL))
			वापस err;

		अगर (!err) अणु
			अगर (chans < 1 || chans > 8)
				वापस -EINVAL;

			dai_drv = devm_kzalloc(&pdev->dev, माप(*dai_drv), GFP_KERNEL);
			अगर (!dai_drv)
				वापस -ENOMEM;

			स_नकल(dai_drv, &dmic_dai, माप(*dai_drv));
			dai_drv->capture.channels_max = chans;
		पूर्ण
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_dmic, dai_drv, 1);
पूर्ण

MODULE_ALIAS("platform:dmic-codec");

अटल स्थिर काष्ठा of_device_id dmic_dev_match[] = अणु
	अणु.compatible = "dmic-codec"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dmic_dev_match);

अटल काष्ठा platक्रमm_driver dmic_driver = अणु
	.driver = अणु
		.name = "dmic-codec",
		.of_match_table = dmic_dev_match,
	पूर्ण,
	.probe = dmic_dev_probe,
पूर्ण;

module_platक्रमm_driver(dmic_driver);

MODULE_DESCRIPTION("Generic DMIC driver");
MODULE_AUTHOR("Liam Girdwood <lrg@slimlogic.co.uk>");
MODULE_LICENSE("GPL");
