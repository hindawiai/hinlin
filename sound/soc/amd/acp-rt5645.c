<शैली गुरु>
/*
 * Machine driver क्रम AMD ACP Audio engine using Realtek RT5645 codec
 *
 * Copyright 2017 Advanced Micro Devices, Inc.
 *
 * This file is modअगरied from rt288 machine driver
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 *
 */

#समावेश <sound/core.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/jack.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/acpi.h>

#समावेश "../codecs/rt5645.h"

#घोषणा CZ_PLAT_CLK 24000000

अटल काष्ठा snd_soc_jack cz_jack;

अटल पूर्णांक cz_aअगर1_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	पूर्णांक ret = 0;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);

	ret = snd_soc_dai_set_pll(codec_dai, 0, RT5645_PLL1_S_MCLK,
				  CZ_PLAT_CLK, params_rate(params) * 512);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set codec pll: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(codec_dai, RT5645_SCLK_S_PLL1,
				params_rate(params) * 512, SND_SOC_CLOCK_OUT);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set codec sysclk: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cz_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	पूर्णांक ret;
	काष्ठा snd_soc_card *card;
	काष्ठा snd_soc_component *codec;

	codec = asoc_rtd_to_codec(rtd, 0)->component;
	card = rtd->card;

	ret = snd_soc_card_jack_new(card, "Headset Jack",
				SND_JACK_HEADPHONE | SND_JACK_MICROPHONE |
				SND_JACK_BTN_0 | SND_JACK_BTN_1 |
				SND_JACK_BTN_2 | SND_JACK_BTN_3,
				&cz_jack, शून्य, 0);
	अगर (ret) अणु
		dev_err(card->dev, "HP jack creation failed %d\n", ret);
		वापस ret;
	पूर्ण

	rt5645_set_jack_detect(codec, &cz_jack, &cz_jack, &cz_jack);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_ops cz_aअगर1_ops = अणु
	.hw_params = cz_aअगर1_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEF(designware1,
	DAILINK_COMP_ARRAY(COMP_CPU("designware-i2s.1.auto")));
SND_SOC_DAILINK_DEF(designware2,
	DAILINK_COMP_ARRAY(COMP_CPU("designware-i2s.2.auto")));

SND_SOC_DAILINK_DEF(codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-10EC5650:00", "rt5645-aif1")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("acp_audio_dma.0.auto")));

अटल काष्ठा snd_soc_dai_link cz_dai_rt5650[] = अणु
	अणु
		.name = "amd-rt5645-play",
		.stream_name = "RT5645_AIF1",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.init = cz_init,
		.ops = &cz_aअगर1_ops,
		SND_SOC_DAILINK_REG(designware1, codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "amd-rt5645-cap",
		.stream_name = "RT5645_AIF1",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.ops = &cz_aअगर1_ops,
		SND_SOC_DAILINK_REG(designware2, codec, platक्रमm),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget cz_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphones", शून्य),
	SND_SOC_DAPM_SPK("Speakers", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Int Mic", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cz_audio_route[] = अणु
	अणु"Headphones", शून्य, "HPOL"पूर्ण,
	अणु"Headphones", शून्य, "HPOR"पूर्ण,
	अणु"RECMIXL", शून्य, "Headset Mic"पूर्ण,
	अणु"RECMIXR", शून्य, "Headset Mic"पूर्ण,
	अणु"Speakers", शून्य, "SPOL"पूर्ण,
	अणु"Speakers", शून्य, "SPOR"पूर्ण,
	अणु"DMIC L2", शून्य, "Int Mic"पूर्ण,
	अणु"DMIC R2", शून्य, "Int Mic"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new cz_mc_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphones"),
	SOC_DAPM_PIN_SWITCH("Speakers"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Int Mic"),
पूर्ण;

अटल काष्ठा snd_soc_card cz_card = अणु
	.name = "acprt5650",
	.owner = THIS_MODULE,
	.dai_link = cz_dai_rt5650,
	.num_links = ARRAY_SIZE(cz_dai_rt5650),
	.dapm_widमाला_लो = cz_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(cz_widमाला_लो),
	.dapm_routes = cz_audio_route,
	.num_dapm_routes = ARRAY_SIZE(cz_audio_route),
	.controls = cz_mc_controls,
	.num_controls = ARRAY_SIZE(cz_mc_controls),
पूर्ण;

अटल पूर्णांक cz_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा snd_soc_card *card;

	card = &cz_card;
	cz_card.dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, card);
	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &cz_card);
	अगर (ret) अणु
		dev_err(&pdev->dev,
				"devm_snd_soc_register_card(%s) failed: %d\n",
				cz_card.name, ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id cz_audio_acpi_match[] = अणु
	अणु "AMDI1002", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, cz_audio_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver cz_pcm_driver = अणु
	.driver = अणु
		.name = "cz-rt5645",
		.acpi_match_table = ACPI_PTR(cz_audio_acpi_match),
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.probe = cz_probe,
पूर्ण;

module_platक्रमm_driver(cz_pcm_driver);

MODULE_AUTHOR("akshu.agrawal@amd.com");
MODULE_DESCRIPTION("cz-rt5645 audio support");
MODULE_LICENSE("GPL v2");
