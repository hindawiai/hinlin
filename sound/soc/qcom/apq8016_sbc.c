<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/jack.h>
#समावेश <sound/soc.h>
#समावेश <uapi/linux/input-event-codes.h>
#समावेश <dt-bindings/sound/apq8016-lpass.h>
#समावेश "common.h"

काष्ठा apq8016_sbc_data अणु
	काष्ठा snd_soc_card card;
	व्योम __iomem *mic_iomux;
	व्योम __iomem *spkr_iomux;
	काष्ठा snd_soc_jack jack;
	bool jack_setup;
पूर्ण;

#घोषणा MIC_CTRL_TER_WS_SLAVE_SEL	BIT(21)
#घोषणा MIC_CTRL_QUA_WS_SLAVE_SEL_10	BIT(17)
#घोषणा MIC_CTRL_TLMM_SCLK_EN		BIT(1)
#घोषणा	SPKR_CTL_PRI_WS_SLAVE_SEL_11	(BIT(17) | BIT(16))
#घोषणा DEFAULT_MCLK_RATE		9600000

अटल पूर्णांक apq8016_sbc_dai_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_dai *codec_dai;
	काष्ठा snd_soc_component *component;
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा apq8016_sbc_data *pdata = snd_soc_card_get_drvdata(card);
	पूर्णांक i, rval;

	चयन (cpu_dai->id) अणु
	हाल MI2S_PRIMARY:
		ग_लिखोl(पढ़ोl(pdata->spkr_iomux) | SPKR_CTL_PRI_WS_SLAVE_SEL_11,
			pdata->spkr_iomux);
		अवरोध;

	हाल MI2S_QUATERNARY:
		/* Configure the Quat MI2S to TLMM */
		ग_लिखोl(पढ़ोl(pdata->mic_iomux) | MIC_CTRL_QUA_WS_SLAVE_SEL_10 |
			MIC_CTRL_TLMM_SCLK_EN,
			pdata->mic_iomux);
		अवरोध;
	हाल MI2S_TERTIARY:
		ग_लिखोl(पढ़ोl(pdata->mic_iomux) | MIC_CTRL_TER_WS_SLAVE_SEL |
			MIC_CTRL_TLMM_SCLK_EN,
			pdata->mic_iomux);

		अवरोध;

	शेष:
		dev_err(card->dev, "unsupported cpu dai configuration\n");
		वापस -EINVAL;

	पूर्ण

	अगर (!pdata->jack_setup) अणु
		काष्ठा snd_jack *jack;

		rval = snd_soc_card_jack_new(card, "Headset Jack",
					     SND_JACK_HEADSET |
					     SND_JACK_HEADPHONE |
					     SND_JACK_BTN_0 | SND_JACK_BTN_1 |
					     SND_JACK_BTN_2 | SND_JACK_BTN_3 |
					     SND_JACK_BTN_4,
					     &pdata->jack, शून्य, 0);

		अगर (rval < 0) अणु
			dev_err(card->dev, "Unable to add Headphone Jack\n");
			वापस rval;
		पूर्ण

		jack = pdata->jack.jack;

		snd_jack_set_key(jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
		snd_jack_set_key(jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
		snd_jack_set_key(jack, SND_JACK_BTN_2, KEY_VOLUMEUP);
		snd_jack_set_key(jack, SND_JACK_BTN_3, KEY_VOLUMEDOWN);
		pdata->jack_setup = true;
	पूर्ण

	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु

		component = codec_dai->component;
		/* Set शेष mclk क्रम पूर्णांकernal codec */
		rval = snd_soc_component_set_sysclk(component, 0, 0, DEFAULT_MCLK_RATE,
				       SND_SOC_CLOCK_IN);
		अगर (rval != 0 && rval != -ENOTSUPP) अणु
			dev_warn(card->dev, "Failed to set mclk: %d\n", rval);
			वापस rval;
		पूर्ण
		rval = snd_soc_component_set_jack(component, &pdata->jack, शून्य);
		अगर (rval != 0 && rval != -ENOTSUPP) अणु
			dev_warn(card->dev, "Failed to set jack: %d\n", rval);
			वापस rval;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम apq8016_sbc_add_ops(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_dai_link *link;
	पूर्णांक i;

	क्रम_each_card_prelinks(card, i, link)
		link->init = apq8016_sbc_dai_init;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget apq8016_sbc_dapm_widमाला_लो[] = अणु

	SND_SOC_DAPM_MIC("Handset Mic", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Secondary Mic", शून्य),
	SND_SOC_DAPM_MIC("Digital Mic1", शून्य),
	SND_SOC_DAPM_MIC("Digital Mic2", शून्य),
पूर्ण;

अटल पूर्णांक apq8016_sbc_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा snd_soc_card *card;
	काष्ठा apq8016_sbc_data *data;
	काष्ठा resource *res;
	पूर्णांक ret;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	card = &data->card;
	card->dev = dev;
	card->owner = THIS_MODULE;
	card->dapm_widमाला_लो = apq8016_sbc_dapm_widमाला_लो;
	card->num_dapm_widमाला_लो = ARRAY_SIZE(apq8016_sbc_dapm_widमाला_लो);

	ret = qcom_snd_parse_of(card);
	अगर (ret)
		वापस ret;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "mic-iomux");
	data->mic_iomux = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(data->mic_iomux))
		वापस PTR_ERR(data->mic_iomux);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "spkr-iomux");
	data->spkr_iomux = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(data->spkr_iomux))
		वापस PTR_ERR(data->spkr_iomux);

	snd_soc_card_set_drvdata(card, data);

	apq8016_sbc_add_ops(card);
	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
पूर्ण

अटल स्थिर काष्ठा of_device_id apq8016_sbc_device_id[] __maybe_unused = अणु
	अणु .compatible = "qcom,apq8016-sbc-sndcard" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, apq8016_sbc_device_id);

अटल काष्ठा platक्रमm_driver apq8016_sbc_platक्रमm_driver = अणु
	.driver = अणु
		.name = "qcom-apq8016-sbc",
		.of_match_table = of_match_ptr(apq8016_sbc_device_id),
	पूर्ण,
	.probe = apq8016_sbc_platक्रमm_probe,
पूर्ण;
module_platक्रमm_driver(apq8016_sbc_platक्रमm_driver);

MODULE_AUTHOR("Srinivas Kandagatla <srinivas.kandagatla@linaro.org");
MODULE_DESCRIPTION("APQ8016 ASoC Machine Driver");
MODULE_LICENSE("GPL v2");
