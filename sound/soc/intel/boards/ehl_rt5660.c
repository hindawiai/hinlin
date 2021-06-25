<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2020 Intel Corporation

/*
 * ehl_rt5660 - ASOC Machine driver क्रम Elkhart Lake platक्रमms
 * with rt5660 codec
 */

#समावेश <linux/acpi.h>
#समावेश <sound/core.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gfp.h>
#समावेश <sound/jack.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>

#समावेश "hda_dsp_common.h"
#समावेश "../../codecs/rt5660.h"

#घोषणा DUAL_CHANNEL 2
#घोषणा HDMI_LINK_START 3
#घोषणा HDMI_LINE_END 6
#घोषणा NAME_SIZE	32
#घोषणा IDISP_CODEC_MASK	0x4

काष्ठा sof_card_निजी अणु
	काष्ठा list_head hdmi_pcm_list;
	bool idisp_codec;
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5660_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Speaker"),
	/* There are two MICBIAS in rt5660, each क्रम one MIC */
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Headset Mic2"),
	SOC_DAPM_PIN_SWITCH("Line Out"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget rt5660_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Speaker", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic2", शून्य),
	SND_SOC_DAPM_MIC("SoC DMIC", शून्य),
	SND_SOC_DAPM_LINE("Line Out", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5660_map[] = अणु
	अणु"Speaker", शून्य, "SPO"पूर्ण,

	अणु"Headset Mic", शून्य, "MICBIAS1"पूर्ण,
	अणु"Headset Mic2", शून्य, "MICBIAS2"पूर्ण,

	अणु"IN1P", शून्य, "Headset Mic"पूर्ण,
	अणु"IN2P", शून्य, "Headset Mic2"पूर्ण,

	अणु"Line Out", शून्य, "LOUTL"पूर्ण,
	अणु"Line Out", शून्य, "LOUTR"पूर्ण,

	अणु"DMic", शून्य, "SoC DMIC"पूर्ण,
पूर्ण;

काष्ठा sof_hdmi_pcm अणु
	काष्ठा list_head head;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक device;
पूर्ण;

अटल पूर्णांक hdmi_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा sof_card_निजी *ctx = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_dai *dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा sof_hdmi_pcm *pcm;

	pcm = devm_kzalloc(rtd->card->dev, माप(*pcm), GFP_KERNEL);
	अगर (!pcm)
		वापस -ENOMEM;

	/* dai_link id is 1:1 mapped to the PCM device */
	pcm->device = rtd->dai_link->id;
	pcm->codec_dai = dai;

	list_add_tail(&pcm->head, &ctx->hdmi_pcm_list);

	वापस 0;
पूर्ण

अटल पूर्णांक card_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा sof_card_निजी *ctx = snd_soc_card_get_drvdata(card);
	काष्ठा sof_hdmi_pcm *pcm;

	अगर (list_empty(&ctx->hdmi_pcm_list))
		वापस -ENOENT;

	अगर (!ctx->idisp_codec)
		वापस 0;

	pcm = list_first_entry(&ctx->hdmi_pcm_list, काष्ठा sof_hdmi_pcm, head);

	वापस hda_dsp_hdmi_build_controls(card, pcm->codec_dai->component);
पूर्ण

अटल पूर्णांक rt5660_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	ret = snd_soc_dai_set_sysclk(codec_dai,
				     RT5660_SCLK_S_PLL1,
				     params_rate(params) * 512,
				     SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "snd_soc_dai_set_sysclk err = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_pll(codec_dai, 0,
				  RT5660_PLL1_S_BCLK,
				  params_rate(params) * 50,
				  params_rate(params) * 512);
	अगर (ret < 0)
		dev_err(codec_dai->dev, "can't set codec pll: %d\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा snd_soc_ops rt5660_ops = अणु
	.hw_params = rt5660_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEF(ssp0_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("SSP0 Pin")));

SND_SOC_DAILINK_DEF(rt5660_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-10EC5660:00", "rt5660-aif1")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("0000:00:1f.3")));

SND_SOC_DAILINK_DEF(dmic_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("DMIC01 Pin")));
SND_SOC_DAILINK_DEF(dmic_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("dmic-codec", "dmic-hifi")));
SND_SOC_DAILINK_DEF(dmic16k,
	DAILINK_COMP_ARRAY(COMP_CPU("DMIC16k Pin")));

SND_SOC_DAILINK_DEF(idisp1_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("iDisp1 Pin")));
SND_SOC_DAILINK_DEF(idisp1_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2", "intel-hdmi-hifi1")));

SND_SOC_DAILINK_DEF(idisp2_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("iDisp2 Pin")));
SND_SOC_DAILINK_DEF(idisp2_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2", "intel-hdmi-hifi2")));

SND_SOC_DAILINK_DEF(idisp3_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("iDisp3 Pin")));
SND_SOC_DAILINK_DEF(idisp3_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2", "intel-hdmi-hifi3")));

SND_SOC_DAILINK_DEF(idisp4_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("iDisp4 Pin")));
SND_SOC_DAILINK_DEF(idisp4_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2", "intel-hdmi-hifi4")));

अटल काष्ठा snd_soc_dai_link ehl_rt5660_dailink[] = अणु
	/* back ends */
	अणु
		.name = "SSP0-Codec",
		.id = 0,
		.no_pcm = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ops = &rt5660_ops,
		.nonatomic = true,
		SND_SOC_DAILINK_REG(ssp0_pin, rt5660_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "dmic48k",
		.id = 1,
		.ignore_suspend = 1,
		.dpcm_capture = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(dmic_pin, dmic_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "dmic16k",
		.id = 2,
		.ignore_suspend = 1,
		.dpcm_capture = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(dmic16k, dmic_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp1",
		.id = 5,
		.init = hdmi_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp1_pin, idisp1_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp2",
		.id = 6,
		.init = hdmi_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp2_pin, idisp2_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp3",
		.id = 7,
		.init = hdmi_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp3_pin, idisp3_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp4",
		.id = 8,
		.init = hdmi_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp4_pin, idisp4_codec, platक्रमm),
	पूर्ण,
पूर्ण;

/* SoC card */
अटल काष्ठा snd_soc_card snd_soc_card_ehl_rt5660 = अणु
	.name = "ehl-rt5660",
	.owner = THIS_MODULE,
	.dai_link = ehl_rt5660_dailink,
	.num_links = ARRAY_SIZE(ehl_rt5660_dailink),
	.dapm_widमाला_लो = rt5660_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(rt5660_widमाला_लो),
	.dapm_routes = rt5660_map,
	.num_dapm_routes = ARRAY_SIZE(rt5660_map),
	.controls = rt5660_controls,
	.num_controls = ARRAY_SIZE(rt5660_controls),
	.fully_routed = true,
	.late_probe = card_late_probe,
पूर्ण;

/* If hdmi codec is not supported, चयन to use dummy codec */
अटल व्योम hdmi_link_init(काष्ठा snd_soc_card *card,
			   काष्ठा sof_card_निजी *ctx,
			   काष्ठा snd_soc_acpi_mach *mach)
अणु
	काष्ठा snd_soc_dai_link *link;
	पूर्णांक i;

	अगर (mach->mach_params.common_hdmi_codec_drv &&
	    (mach->mach_params.codec_mask & IDISP_CODEC_MASK)) अणु
		ctx->idisp_codec = true;
		वापस;
	पूर्ण

	/*
	 * अगर HDMI is not enabled in kernel config, or
	 * hdmi codec is not supported
	 */
	क्रम (i = HDMI_LINK_START; i <= HDMI_LINE_END; i++) अणु
		link = &card->dai_link[i];
		link->codecs[0].name = "snd-soc-dummy";
		link->codecs[0].dai_name = "snd-soc-dummy-dai";
	पूर्ण
पूर्ण

अटल पूर्णांक snd_ehl_rt5660_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_acpi_mach *mach;
	काष्ठा snd_soc_card *card = &snd_soc_card_ehl_rt5660;
	काष्ठा sof_card_निजी *ctx;
	पूर्णांक ret;

	card->dev = &pdev->dev;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;
	INIT_LIST_HEAD(&ctx->hdmi_pcm_list);
	snd_soc_card_set_drvdata(card, ctx);

	mach = pdev->dev.platक्रमm_data;
	ret = snd_soc_fixup_dai_links_platक्रमm_name(card,
						    mach->mach_params.platक्रमm);
	अगर (ret)
		वापस ret;

	hdmi_link_init(card, ctx, mach);

	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id ehl_board_ids[] = अणु
	अणु .name = "ehl_rt5660" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver snd_ehl_rt5660_driver = अणु
	.driver = अणु
		.name = "ehl_rt5660",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.probe = snd_ehl_rt5660_probe,
	.id_table = ehl_board_ids,
पूर्ण;

module_platक्रमm_driver(snd_ehl_rt5660_driver);

MODULE_DESCRIPTION("ASoC Intel(R) Elkhartlake + rt5660 Machine driver");
MODULE_AUTHOR("libin.yang@intel.com");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:ehl_rt5660");
