<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright(c) 2019-2020 Intel Corporation.

/*
 * Intel SOF Machine Driver with Realtek rt5682 Codec
 * and speaker codec MAX98357A or RT1015.
 */
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/dmi.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/sof.h>
#समावेश <sound/rt5682.h>
#समावेश <sound/soc-acpi.h>
#समावेश "../../codecs/rt1015.h"
#समावेश "../../codecs/rt5682.h"
#समावेश "../../codecs/hdac_hdmi.h"
#समावेश "../common/soc-intel-quirks.h"
#समावेश "hda_dsp_common.h"
#समावेश "sof_maxim_common.h"
#समावेश "sof_realtek_common.h"

#घोषणा NAME_SIZE 32

#घोषणा SOF_RT5682_SSP_CODEC(quirk)		((quirk) & GENMASK(2, 0))
#घोषणा SOF_RT5682_SSP_CODEC_MASK			(GENMASK(2, 0))
#घोषणा SOF_RT5682_MCLK_EN			BIT(3)
#घोषणा SOF_RT5682_MCLK_24MHZ			BIT(4)
#घोषणा SOF_SPEAKER_AMP_PRESENT		BIT(5)
#घोषणा SOF_RT5682_SSP_AMP_SHIFT		6
#घोषणा SOF_RT5682_SSP_AMP_MASK                 (GENMASK(8, 6))
#घोषणा SOF_RT5682_SSP_AMP(quirk)	\
	(((quirk) << SOF_RT5682_SSP_AMP_SHIFT) & SOF_RT5682_SSP_AMP_MASK)
#घोषणा SOF_RT5682_MCLK_BYTCHT_EN		BIT(9)
#घोषणा SOF_RT5682_NUM_HDMIDEV_SHIFT		10
#घोषणा SOF_RT5682_NUM_HDMIDEV_MASK		(GENMASK(12, 10))
#घोषणा SOF_RT5682_NUM_HDMIDEV(quirk)	\
	((quirk << SOF_RT5682_NUM_HDMIDEV_SHIFT) & SOF_RT5682_NUM_HDMIDEV_MASK)
#घोषणा SOF_RT1011_SPEAKER_AMP_PRESENT		BIT(13)
#घोषणा SOF_RT1015_SPEAKER_AMP_PRESENT		BIT(14)
#घोषणा SOF_RT1015_SPEAKER_AMP_100FS		BIT(15)
#घोषणा SOF_RT1015P_SPEAKER_AMP_PRESENT		BIT(16)
#घोषणा SOF_MAX98373_SPEAKER_AMP_PRESENT	BIT(17)
#घोषणा SOF_MAX98360A_SPEAKER_AMP_PRESENT	BIT(18)

/* Default: MCLK on, MCLK 19.2M, SSP0  */
अटल अचिन्हित दीर्घ sof_rt5682_quirk = SOF_RT5682_MCLK_EN |
					SOF_RT5682_SSP_CODEC(0);

अटल पूर्णांक is_legacy_cpu;

अटल काष्ठा snd_soc_jack sof_hdmi[3];

काष्ठा sof_hdmi_pcm अणु
	काष्ठा list_head head;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक device;
पूर्ण;

काष्ठा sof_card_निजी अणु
	काष्ठा clk *mclk;
	काष्ठा snd_soc_jack sof_headset;
	काष्ठा list_head hdmi_pcm_list;
	bool common_hdmi_codec_drv;
पूर्ण;

अटल पूर्णांक sof_rt5682_quirk_cb(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	sof_rt5682_quirk = (अचिन्हित दीर्घ)id->driver_data;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id sof_rt5682_quirk_table[] = अणु
	अणु
		.callback = sof_rt5682_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Circuitco"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Minnowboard Max"),
		पूर्ण,
		.driver_data = (व्योम *)(SOF_RT5682_SSP_CODEC(2)),
	पूर्ण,
	अणु
		.callback = sof_rt5682_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "AAEON"),
			DMI_MATCH(DMI_PRODUCT_NAME, "UP-CHT01"),
		पूर्ण,
		.driver_data = (व्योम *)(SOF_RT5682_SSP_CODEC(2)),
	पूर्ण,
	अणु
		.callback = sof_rt5682_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Intel Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "WhiskeyLake Client"),
		पूर्ण,
		.driver_data = (व्योम *)(SOF_RT5682_MCLK_EN |
					SOF_RT5682_MCLK_24MHZ |
					SOF_RT5682_SSP_CODEC(1)),
	पूर्ण,
	अणु
		/*
		 * Dooly is hatch family but using rt1015 amp so it
		 * requires a quirk beक्रमe "Google_Hatch".
		 */
		.callback = sof_rt5682_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Dooly"),
		पूर्ण,
		.driver_data = (व्योम *)(SOF_RT5682_MCLK_EN |
					SOF_RT5682_MCLK_24MHZ |
					SOF_RT5682_SSP_CODEC(0) |
					SOF_SPEAKER_AMP_PRESENT |
					SOF_RT1015_SPEAKER_AMP_PRESENT |
					SOF_RT1015_SPEAKER_AMP_100FS |
					SOF_RT5682_SSP_AMP(1)),
	पूर्ण,
	अणु
		.callback = sof_rt5682_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_FAMILY, "Google_Hatch"),
		पूर्ण,
		.driver_data = (व्योम *)(SOF_RT5682_MCLK_EN |
					SOF_RT5682_MCLK_24MHZ |
					SOF_RT5682_SSP_CODEC(0) |
					SOF_SPEAKER_AMP_PRESENT |
					SOF_RT5682_SSP_AMP(1)),
	पूर्ण,
	अणु
		.callback = sof_rt5682_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Intel Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Ice Lake Client"),
		पूर्ण,
		.driver_data = (व्योम *)(SOF_RT5682_MCLK_EN |
					SOF_RT5682_SSP_CODEC(0)),
	पूर्ण,
	अणु
		.callback = sof_rt5682_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_FAMILY, "Google_Volteer"),
			DMI_MATCH(DMI_OEM_STRING, "AUDIO-MAX98373_ALC5682I_I2S_UP4"),
		पूर्ण,
		.driver_data = (व्योम *)(SOF_RT5682_MCLK_EN |
					SOF_RT5682_SSP_CODEC(0) |
					SOF_SPEAKER_AMP_PRESENT |
					SOF_MAX98373_SPEAKER_AMP_PRESENT |
					SOF_RT5682_SSP_AMP(2) |
					SOF_RT5682_NUM_HDMIDEV(4)),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक sof_hdmi_init(काष्ठा snd_soc_pcm_runसमय *rtd)
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

अटल पूर्णांक sof_rt5682_codec_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा sof_card_निजी *ctx = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;
	काष्ठा snd_soc_jack *jack;
	पूर्णांक ret;

	/* need to enable ASRC function क्रम 24MHz mclk rate */
	अगर ((sof_rt5682_quirk & SOF_RT5682_MCLK_EN) &&
	    (sof_rt5682_quirk & SOF_RT5682_MCLK_24MHZ)) अणु
		rt5682_sel_asrc_clk_src(component, RT5682_DA_STEREO1_FILTER |
					RT5682_AD_STEREO1_FILTER,
					RT5682_CLK_SEL_I2S1_ASRC);
	पूर्ण

	अगर (sof_rt5682_quirk & SOF_RT5682_MCLK_BYTCHT_EN) अणु
		/*
		 * The firmware might enable the घड़ी at
		 * boot (this inक्रमmation may or may not
		 * be reflected in the enable घड़ी रेजिस्टर).
		 * To change the rate we must disable the घड़ी
		 * first to cover these हालs. Due to common
		 * घड़ी framework restrictions that करो not allow
		 * to disable a घड़ी that has not been enabled,
		 * we need to enable the घड़ी first.
		 */
		ret = clk_prepare_enable(ctx->mclk);
		अगर (!ret)
			clk_disable_unprepare(ctx->mclk);

		ret = clk_set_rate(ctx->mclk, 19200000);

		अगर (ret)
			dev_err(rtd->dev, "unable to set MCLK rate\n");
	पूर्ण

	/*
	 * Headset buttons map to the google Reference headset.
	 * These can be configured by userspace.
	 */
	ret = snd_soc_card_jack_new(rtd->card, "Headset Jack",
				    SND_JACK_HEADSET | SND_JACK_BTN_0 |
				    SND_JACK_BTN_1 | SND_JACK_BTN_2 |
				    SND_JACK_BTN_3,
				    &ctx->sof_headset, शून्य, 0);
	अगर (ret) अणु
		dev_err(rtd->dev, "Headset Jack creation failed: %d\n", ret);
		वापस ret;
	पूर्ण

	jack = &ctx->sof_headset;

	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOLUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOLUMEDOWN);
	ret = snd_soc_component_set_jack(component, jack, शून्य);

	अगर (ret) अणु
		dev_err(rtd->dev, "Headset Jack call-back failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण;

अटल व्योम sof_rt5682_codec_निकास(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;

	snd_soc_component_set_jack(component, शून्य, शून्य);
पूर्ण

अटल पूर्णांक sof_rt5682_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा sof_card_निजी *ctx = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक clk_id, clk_freq, pll_out, ret;

	अगर (sof_rt5682_quirk & SOF_RT5682_MCLK_EN) अणु
		अगर (sof_rt5682_quirk & SOF_RT5682_MCLK_BYTCHT_EN) अणु
			ret = clk_prepare_enable(ctx->mclk);
			अगर (ret < 0) अणु
				dev_err(rtd->dev,
					"could not configure MCLK state");
				वापस ret;
			पूर्ण
		पूर्ण

		clk_id = RT5682_PLL1_S_MCLK;

		/* get the tplg configured mclk. */
		clk_freq = sof_dai_get_mclk(rtd);

		/* mclk from the quirk is the first choice */
		अगर (sof_rt5682_quirk & SOF_RT5682_MCLK_24MHZ) अणु
			अगर (clk_freq != 24000000)
				dev_warn(rtd->dev, "configure wrong mclk in tplg, please use 24MHz.\n");
			clk_freq = 24000000;
		पूर्ण अन्यथा अगर (clk_freq == 0) अणु
			/* use शेष mclk अगर not specअगरied correct in topology */
			clk_freq = 19200000;
		पूर्ण अन्यथा अगर (clk_freq < 0) अणु
			वापस clk_freq;
		पूर्ण
	पूर्ण अन्यथा अणु
		clk_id = RT5682_PLL1_S_BCLK1;
		clk_freq = params_rate(params) * 50;
	पूर्ण

	pll_out = params_rate(params) * 512;

	ret = snd_soc_dai_set_pll(codec_dai, 0, clk_id, clk_freq, pll_out);
	अगर (ret < 0)
		dev_err(rtd->dev, "snd_soc_dai_set_pll err = %d\n", ret);

	/* Configure sysclk क्रम codec */
	ret = snd_soc_dai_set_sysclk(codec_dai, RT5682_SCLK_S_PLL1,
				     pll_out, SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		dev_err(rtd->dev, "snd_soc_dai_set_sysclk err = %d\n", ret);

	/*
	 * slot_width should equal or large than data length, set them
	 * be the same
	 */
	ret = snd_soc_dai_set_tdm_slot(codec_dai, 0x0, 0x0, 2,
				       params_width(params));
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "set TDM slot err:%d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा snd_soc_ops sof_rt5682_ops = अणु
	.hw_params = sof_rt5682_hw_params,
पूर्ण;

अटल पूर्णांक sof_rt1015_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक i, fs, ret;

	अगर (!snd_soc_card_get_codec_dai(card, "rt1015-aif"))
		वापस 0;

	अगर (sof_rt5682_quirk & SOF_RT1015_SPEAKER_AMP_100FS)
		fs = 100;
	अन्यथा
		fs = 64;

	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
		ret = snd_soc_dai_set_pll(codec_dai, 0, RT1015_PLL_S_BCLK,
					  params_rate(params) * fs,
					  params_rate(params) * 256);
		अगर (ret < 0) अणु
			dev_err(card->dev, "failed to set pll\n");
			वापस ret;
		पूर्ण
		/* Configure sysclk क्रम codec */
		ret = snd_soc_dai_set_sysclk(codec_dai, RT1015_SCLK_S_PLL,
					     params_rate(params) * 256,
					     SND_SOC_CLOCK_IN);
		अगर (ret < 0) अणु
			dev_err(card->dev, "failed to set sysclk\n");
			वापस ret;
		पूर्ण

		अगर (sof_rt5682_quirk & SOF_RT1015_SPEAKER_AMP_100FS) अणु
			अगर (!म_भेद(codec_dai->component->name, "i2c-10EC1015:00")) अणु
				ret = snd_soc_dai_set_tdm_slot(codec_dai,
							       0x0, 0x1, 4, 24);
				अगर (ret < 0) अणु
					dev_err(card->dev, "failed to set tdm slot\n");
					वापस ret;
				पूर्ण
			पूर्ण

			अगर (!म_भेद(codec_dai->component->name, "i2c-10EC1015:01")) अणु
				ret = snd_soc_dai_set_tdm_slot(codec_dai,
							       0x0, 0x2, 4, 24);
				अगर (ret < 0) अणु
					dev_err(card->dev, "failed to set tdm slot\n");
					वापस ret;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_ops sof_rt1015_ops = अणु
	.hw_params = sof_rt1015_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_link_component platक्रमm_component[] = अणु
	अणु
		/* name might be overridden during probe */
		.name = "0000:00:1f.3"
	पूर्ण
पूर्ण;

अटल पूर्णांक sof_card_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा sof_card_निजी *ctx = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_component *component = शून्य;
	काष्ठा snd_soc_dapm_context *dapm = &card->dapm;
	अक्षर jack_name[NAME_SIZE];
	काष्ठा sof_hdmi_pcm *pcm;
	पूर्णांक err;
	पूर्णांक i = 0;

	/* HDMI is not supported by SOF on Baytrail/CherryTrail */
	अगर (is_legacy_cpu)
		वापस 0;

	अगर (list_empty(&ctx->hdmi_pcm_list))
		वापस -EINVAL;

	अगर (ctx->common_hdmi_codec_drv) अणु
		pcm = list_first_entry(&ctx->hdmi_pcm_list, काष्ठा sof_hdmi_pcm,
				       head);
		component = pcm->codec_dai->component;
		वापस hda_dsp_hdmi_build_controls(card, component);
	पूर्ण

	list_क्रम_each_entry(pcm, &ctx->hdmi_pcm_list, head) अणु
		component = pcm->codec_dai->component;
		snम_लिखो(jack_name, माप(jack_name),
			 "HDMI/DP, pcm=%d Jack", pcm->device);
		err = snd_soc_card_jack_new(card, jack_name,
					    SND_JACK_AVOUT, &sof_hdmi[i],
					    शून्य, 0);

		अगर (err)
			वापस err;

		err = hdac_hdmi_jack_init(pcm->codec_dai, pcm->device,
					  &sof_hdmi[i]);
		अगर (err < 0)
			वापस err;

		i++;
	पूर्ण

	अगर (sof_rt5682_quirk & SOF_MAX98373_SPEAKER_AMP_PRESENT) अणु
		/* Disable Left and Right Spk pin after boot */
		snd_soc_dapm_disable_pin(dapm, "Left Spk");
		snd_soc_dapm_disable_pin(dapm, "Right Spk");
		err = snd_soc_dapm_sync(dapm);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस hdac_hdmi_jack_port_init(component, &card->dapm);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new sof_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Spk"),
	SOC_DAPM_PIN_SWITCH("Left Spk"),
	SOC_DAPM_PIN_SWITCH("Right Spk"),

पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget sof_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_SPK("Spk", शून्य),
	SND_SOC_DAPM_SPK("Left Spk", शून्य),
	SND_SOC_DAPM_SPK("Right Spk", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget dmic_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIC("SoC DMIC", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route sof_map[] = अणु
	/* HP jack connectors - unknown अगर we have jack detection */
	अणु "Headphone Jack", शून्य, "HPOL" पूर्ण,
	अणु "Headphone Jack", शून्य, "HPOR" पूर्ण,

	/* other jacks */
	अणु "IN1P", शून्य, "Headset Mic" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route speaker_map[] = अणु
	/* speaker */
	अणु "Spk", शून्य, "Speaker" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route speaker_map_lr[] = अणु
	अणु "Left Spk", शून्य, "Left SPO" पूर्ण,
	अणु "Right Spk", शून्य, "Right SPO" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route dmic_map[] = अणु
	/* digital mics */
	अणु"DMic", शून्य, "SoC DMIC"पूर्ण,
पूर्ण;

अटल पूर्णांक speaker_codec_init_lr(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	वापस snd_soc_dapm_add_routes(&rtd->card->dapm, speaker_map_lr,
				       ARRAY_SIZE(speaker_map_lr));
पूर्ण

अटल पूर्णांक speaker_codec_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	पूर्णांक ret;

	ret = snd_soc_dapm_add_routes(&card->dapm, speaker_map,
				      ARRAY_SIZE(speaker_map));

	अगर (ret)
		dev_err(rtd->dev, "Speaker map addition failed: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक dmic_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	पूर्णांक ret;

	ret = snd_soc_dapm_new_controls(&card->dapm, dmic_widमाला_लो,
					ARRAY_SIZE(dmic_widमाला_लो));
	अगर (ret) अणु
		dev_err(card->dev, "DMic widget addition failed: %d\n", ret);
		/* Don't need to add routes अगर widget addition failed */
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_add_routes(&card->dapm, dmic_map,
				      ARRAY_SIZE(dmic_map));

	अगर (ret)
		dev_err(card->dev, "DMic map addition failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा snd_soc_codec_conf rt1015_amp_conf[] = अणु
	अणु
		.dlc = COMP_CODEC_CONF("i2c-10EC1015:00"),
		.name_prefix = "Left",
	पूर्ण,
	अणु
		.dlc = COMP_CODEC_CONF("i2c-10EC1015:01"),
		.name_prefix = "Right",
	पूर्ण,
पूर्ण;

/* sof audio machine driver क्रम rt5682 codec */
अटल काष्ठा snd_soc_card sof_audio_card_rt5682 = अणु
	.name = "rt5682", /* the sof- prefix is added by the core */
	.owner = THIS_MODULE,
	.controls = sof_controls,
	.num_controls = ARRAY_SIZE(sof_controls),
	.dapm_widमाला_लो = sof_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(sof_widमाला_लो),
	.dapm_routes = sof_map,
	.num_dapm_routes = ARRAY_SIZE(sof_map),
	.fully_routed = true,
	.late_probe = sof_card_late_probe,
पूर्ण;

अटल काष्ठा snd_soc_dai_link_component rt5682_component[] = अणु
	अणु
		.name = "i2c-10EC5682:00",
		.dai_name = "rt5682-aif1",
	पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_dai_link_component dmic_component[] = अणु
	अणु
		.name = "dmic-codec",
		.dai_name = "dmic-hifi",
	पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_dai_link_component max98357a_component[] = अणु
	अणु
		.name = "MX98357A:00",
		.dai_name = "HiFi",
	पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_dai_link_component max98360a_component[] = अणु
	अणु
		.name = "MX98360A:00",
		.dai_name = "HiFi",
	पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_dai_link_component rt1015_components[] = अणु
	अणु
		.name = "i2c-10EC1015:00",
		.dai_name = "rt1015-aif",
	पूर्ण,
	अणु
		.name = "i2c-10EC1015:01",
		.dai_name = "rt1015-aif",
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_link *sof_card_dai_links_create(काष्ठा device *dev,
							  पूर्णांक ssp_codec,
							  पूर्णांक ssp_amp,
							  पूर्णांक dmic_be_num,
							  पूर्णांक hdmi_num)
अणु
	काष्ठा snd_soc_dai_link_component *idisp_components;
	काष्ठा snd_soc_dai_link_component *cpus;
	काष्ठा snd_soc_dai_link *links;
	पूर्णांक i, id = 0;

	links = devm_kzalloc(dev, माप(काष्ठा snd_soc_dai_link) *
			     sof_audio_card_rt5682.num_links, GFP_KERNEL);
	cpus = devm_kzalloc(dev, माप(काष्ठा snd_soc_dai_link_component) *
			     sof_audio_card_rt5682.num_links, GFP_KERNEL);
	अगर (!links || !cpus)
		जाओ devm_err;

	/* codec SSP */
	links[id].name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
					"SSP%d-Codec", ssp_codec);
	अगर (!links[id].name)
		जाओ devm_err;

	links[id].id = id;
	links[id].codecs = rt5682_component;
	links[id].num_codecs = ARRAY_SIZE(rt5682_component);
	links[id].platक्रमms = platक्रमm_component;
	links[id].num_platक्रमms = ARRAY_SIZE(platक्रमm_component);
	links[id].init = sof_rt5682_codec_init;
	links[id].निकास = sof_rt5682_codec_निकास;
	links[id].ops = &sof_rt5682_ops;
	links[id].nonatomic = true;
	links[id].dpcm_playback = 1;
	links[id].dpcm_capture = 1;
	links[id].no_pcm = 1;
	links[id].cpus = &cpus[id];
	links[id].num_cpus = 1;
	अगर (is_legacy_cpu) अणु
		links[id].cpus->dai_name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
							  "ssp%d-port",
							  ssp_codec);
		अगर (!links[id].cpus->dai_name)
			जाओ devm_err;
	पूर्ण अन्यथा अणु
		/*
		 * Currently, On SKL+ platक्रमms MCLK will be turned off in sof
		 * runसमय suspended, and it will go पूर्णांकo runसमय suspended
		 * right after playback is stop. However, rt5682 will output
		 * अटल noise अगर sysclk turns off during playback. Set
		 * ignore_pmकरोwn_समय to घातer करोwn rt5682 immediately and
		 * aव्योम the noise.
		 * It can be हटाओd once we can control MCLK by driver.
		 */
		links[id].ignore_pmकरोwn_समय = 1;
		links[id].cpus->dai_name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
							  "SSP%d Pin",
							  ssp_codec);
		अगर (!links[id].cpus->dai_name)
			जाओ devm_err;
	पूर्ण
	id++;

	/* dmic */
	अगर (dmic_be_num > 0) अणु
		/* at least we have dmic01 */
		links[id].name = "dmic01";
		links[id].cpus = &cpus[id];
		links[id].cpus->dai_name = "DMIC01 Pin";
		links[id].init = dmic_init;
		अगर (dmic_be_num > 1) अणु
			/* set up 2 BE links at most */
			links[id + 1].name = "dmic16k";
			links[id + 1].cpus = &cpus[id + 1];
			links[id + 1].cpus->dai_name = "DMIC16k Pin";
			dmic_be_num = 2;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < dmic_be_num; i++) अणु
		links[id].id = id;
		links[id].num_cpus = 1;
		links[id].codecs = dmic_component;
		links[id].num_codecs = ARRAY_SIZE(dmic_component);
		links[id].platक्रमms = platक्रमm_component;
		links[id].num_platक्रमms = ARRAY_SIZE(platक्रमm_component);
		links[id].ignore_suspend = 1;
		links[id].dpcm_capture = 1;
		links[id].no_pcm = 1;
		id++;
	पूर्ण

	/* HDMI */
	अगर (hdmi_num > 0) अणु
		idisp_components = devm_kzalloc(dev,
				   माप(काष्ठा snd_soc_dai_link_component) *
				   hdmi_num, GFP_KERNEL);
		अगर (!idisp_components)
			जाओ devm_err;
	पूर्ण
	क्रम (i = 1; i <= hdmi_num; i++) अणु
		links[id].name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
						"iDisp%d", i);
		अगर (!links[id].name)
			जाओ devm_err;

		links[id].id = id;
		links[id].cpus = &cpus[id];
		links[id].num_cpus = 1;
		links[id].cpus->dai_name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
							  "iDisp%d Pin", i);
		अगर (!links[id].cpus->dai_name)
			जाओ devm_err;

		idisp_components[i - 1].name = "ehdaudio0D2";
		idisp_components[i - 1].dai_name = devm_kaप्र_लिखो(dev,
								  GFP_KERNEL,
								  "intel-hdmi-hifi%d",
								  i);
		अगर (!idisp_components[i - 1].dai_name)
			जाओ devm_err;

		links[id].codecs = &idisp_components[i - 1];
		links[id].num_codecs = 1;
		links[id].platक्रमms = platक्रमm_component;
		links[id].num_platक्रमms = ARRAY_SIZE(platक्रमm_component);
		links[id].init = sof_hdmi_init;
		links[id].dpcm_playback = 1;
		links[id].no_pcm = 1;
		id++;
	पूर्ण

	/* speaker amp */
	अगर (sof_rt5682_quirk & SOF_SPEAKER_AMP_PRESENT) अणु
		links[id].name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
						"SSP%d-Codec", ssp_amp);
		अगर (!links[id].name)
			जाओ devm_err;

		links[id].id = id;
		अगर (sof_rt5682_quirk & SOF_RT1015_SPEAKER_AMP_PRESENT) अणु
			links[id].codecs = rt1015_components;
			links[id].num_codecs = ARRAY_SIZE(rt1015_components);
			links[id].init = speaker_codec_init_lr;
			links[id].ops = &sof_rt1015_ops;
		पूर्ण अन्यथा अगर (sof_rt5682_quirk & SOF_RT1015P_SPEAKER_AMP_PRESENT) अणु
			sof_rt1015p_dai_link(&links[id]);
		पूर्ण अन्यथा अगर (sof_rt5682_quirk &
				SOF_MAX98373_SPEAKER_AMP_PRESENT) अणु
			links[id].codecs = max_98373_components;
			links[id].num_codecs = ARRAY_SIZE(max_98373_components);
			links[id].init = max98373_spk_codec_init;
			links[id].ops = &max_98373_ops;
			/* feedback stream */
			links[id].dpcm_capture = 1;
		पूर्ण अन्यथा अगर (sof_rt5682_quirk &
				SOF_MAX98360A_SPEAKER_AMP_PRESENT) अणु
			links[id].codecs = max98360a_component;
			links[id].num_codecs = ARRAY_SIZE(max98360a_component);
			links[id].init = speaker_codec_init;
		पूर्ण अन्यथा अगर (sof_rt5682_quirk &
				SOF_RT1011_SPEAKER_AMP_PRESENT) अणु
			sof_rt1011_dai_link(&links[id]);
		पूर्ण अन्यथा अणु
			links[id].codecs = max98357a_component;
			links[id].num_codecs = ARRAY_SIZE(max98357a_component);
			links[id].init = speaker_codec_init;
		पूर्ण
		links[id].platक्रमms = platक्रमm_component;
		links[id].num_platक्रमms = ARRAY_SIZE(platक्रमm_component);
		links[id].nonatomic = true;
		links[id].dpcm_playback = 1;
		links[id].no_pcm = 1;
		links[id].cpus = &cpus[id];
		links[id].num_cpus = 1;
		अगर (is_legacy_cpu) अणु
			links[id].cpus->dai_name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
								  "ssp%d-port",
								  ssp_amp);
			अगर (!links[id].cpus->dai_name)
				जाओ devm_err;

		पूर्ण अन्यथा अणु
			links[id].cpus->dai_name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
								  "SSP%d Pin",
								  ssp_amp);
			अगर (!links[id].cpus->dai_name)
				जाओ devm_err;
		पूर्ण
	पूर्ण

	वापस links;
devm_err:
	वापस शून्य;
पूर्ण

अटल पूर्णांक sof_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_dai_link *dai_links;
	काष्ठा snd_soc_acpi_mach *mach;
	काष्ठा sof_card_निजी *ctx;
	पूर्णांक dmic_be_num, hdmi_num;
	पूर्णांक ret, ssp_amp, ssp_codec;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	अगर (pdev->id_entry && pdev->id_entry->driver_data)
		sof_rt5682_quirk = (अचिन्हित दीर्घ)pdev->id_entry->driver_data;

	dmi_check_प्रणाली(sof_rt5682_quirk_table);

	mach = pdev->dev.platक्रमm_data;

	/* A speaker amp might not be present when the quirk claims one is.
	 * Detect this via whether the machine driver match includes quirk_data.
	 */
	अगर ((sof_rt5682_quirk & SOF_SPEAKER_AMP_PRESENT) && !mach->quirk_data)
		sof_rt5682_quirk &= ~SOF_SPEAKER_AMP_PRESENT;

	अगर (soc_पूर्णांकel_is_byt() || soc_पूर्णांकel_is_cht()) अणु
		is_legacy_cpu = 1;
		dmic_be_num = 0;
		hdmi_num = 0;
		/* शेष quirk क्रम legacy cpu */
		sof_rt5682_quirk = SOF_RT5682_MCLK_EN |
						SOF_RT5682_MCLK_BYTCHT_EN |
						SOF_RT5682_SSP_CODEC(2);
	पूर्ण अन्यथा अणु
		dmic_be_num = 2;
		hdmi_num = (sof_rt5682_quirk & SOF_RT5682_NUM_HDMIDEV_MASK) >>
			 SOF_RT5682_NUM_HDMIDEV_SHIFT;
		/* शेष number of HDMI DAI's */
		अगर (!hdmi_num)
			hdmi_num = 3;
	पूर्ण

	/* need to get मुख्य घड़ी from pmc */
	अगर (sof_rt5682_quirk & SOF_RT5682_MCLK_BYTCHT_EN) अणु
		ctx->mclk = devm_clk_get(&pdev->dev, "pmc_plt_clk_3");
		अगर (IS_ERR(ctx->mclk)) अणु
			ret = PTR_ERR(ctx->mclk);

			dev_err(&pdev->dev,
				"Failed to get MCLK from pmc_plt_clk_3: %d\n",
				ret);
			वापस ret;
		पूर्ण

		ret = clk_prepare_enable(ctx->mclk);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev,
				"could not configure MCLK state");
			वापस ret;
		पूर्ण
	पूर्ण

	dev_dbg(&pdev->dev, "sof_rt5682_quirk = %lx\n", sof_rt5682_quirk);

	ssp_amp = (sof_rt5682_quirk & SOF_RT5682_SSP_AMP_MASK) >>
			SOF_RT5682_SSP_AMP_SHIFT;

	ssp_codec = sof_rt5682_quirk & SOF_RT5682_SSP_CODEC_MASK;

	/* compute number of dai links */
	sof_audio_card_rt5682.num_links = 1 + dmic_be_num + hdmi_num;

	अगर (sof_rt5682_quirk & SOF_SPEAKER_AMP_PRESENT)
		sof_audio_card_rt5682.num_links++;

	अगर (sof_rt5682_quirk & SOF_MAX98373_SPEAKER_AMP_PRESENT)
		sof_max98373_codec_conf(&sof_audio_card_rt5682);
	अन्यथा अगर (sof_rt5682_quirk & SOF_RT1011_SPEAKER_AMP_PRESENT)
		sof_rt1011_codec_conf(&sof_audio_card_rt5682);
	अन्यथा अगर (sof_rt5682_quirk & SOF_RT1015P_SPEAKER_AMP_PRESENT)
		sof_rt1015p_codec_conf(&sof_audio_card_rt5682);

	dai_links = sof_card_dai_links_create(&pdev->dev, ssp_codec, ssp_amp,
					      dmic_be_num, hdmi_num);
	अगर (!dai_links)
		वापस -ENOMEM;

	sof_audio_card_rt5682.dai_link = dai_links;

	अगर (sof_rt5682_quirk & SOF_RT1015_SPEAKER_AMP_PRESENT) अणु
		sof_audio_card_rt5682.codec_conf = rt1015_amp_conf;
		sof_audio_card_rt5682.num_configs = ARRAY_SIZE(rt1015_amp_conf);
	पूर्ण

	INIT_LIST_HEAD(&ctx->hdmi_pcm_list);

	sof_audio_card_rt5682.dev = &pdev->dev;

	/* set platक्रमm name क्रम each dailink */
	ret = snd_soc_fixup_dai_links_platक्रमm_name(&sof_audio_card_rt5682,
						    mach->mach_params.platक्रमm);
	अगर (ret)
		वापस ret;

	ctx->common_hdmi_codec_drv = mach->mach_params.common_hdmi_codec_drv;

	snd_soc_card_set_drvdata(&sof_audio_card_rt5682, ctx);

	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev,
					  &sof_audio_card_rt5682);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id board_ids[] = अणु
	अणु
		.name = "sof_rt5682",
	पूर्ण,
	अणु
		.name = "tgl_max98357a_rt5682",
		.driver_data = (kernel_uदीर्घ_t)(SOF_RT5682_MCLK_EN |
					SOF_RT5682_SSP_CODEC(0) |
					SOF_SPEAKER_AMP_PRESENT |
					SOF_RT5682_SSP_AMP(1) |
					SOF_RT5682_NUM_HDMIDEV(4)),
	पूर्ण,
	अणु
		.name = "jsl_rt5682_rt1015",
		.driver_data = (kernel_uदीर्घ_t)(SOF_RT5682_MCLK_EN |
					SOF_RT5682_MCLK_24MHZ |
					SOF_RT5682_SSP_CODEC(0) |
					SOF_SPEAKER_AMP_PRESENT |
					SOF_RT1015_SPEAKER_AMP_PRESENT |
					SOF_RT5682_SSP_AMP(1)),
	पूर्ण,
	अणु
		.name = "tgl_max98373_rt5682",
		.driver_data = (kernel_uदीर्घ_t)(SOF_RT5682_MCLK_EN |
					SOF_RT5682_SSP_CODEC(0) |
					SOF_SPEAKER_AMP_PRESENT |
					SOF_MAX98373_SPEAKER_AMP_PRESENT |
					SOF_RT5682_SSP_AMP(1) |
					SOF_RT5682_NUM_HDMIDEV(4)),
	पूर्ण,
	अणु
		.name = "jsl_rt5682_max98360a",
		.driver_data = (kernel_uदीर्घ_t)(SOF_RT5682_MCLK_EN |
					SOF_RT5682_MCLK_24MHZ |
					SOF_RT5682_SSP_CODEC(0) |
					SOF_SPEAKER_AMP_PRESENT |
					SOF_MAX98360A_SPEAKER_AMP_PRESENT |
					SOF_RT5682_SSP_AMP(1)),
	पूर्ण,
	अणु
		.name = "cml_rt1015_rt5682",
		.driver_data = (kernel_uदीर्घ_t)(SOF_RT5682_MCLK_EN |
					SOF_RT5682_MCLK_24MHZ |
					SOF_RT5682_SSP_CODEC(0) |
					SOF_SPEAKER_AMP_PRESENT |
					SOF_RT1015_SPEAKER_AMP_PRESENT |
					SOF_RT1015_SPEAKER_AMP_100FS |
					SOF_RT5682_SSP_AMP(1)),
	पूर्ण,
	अणु
		.name = "tgl_rt1011_rt5682",
		.driver_data = (kernel_uदीर्घ_t)(SOF_RT5682_MCLK_EN |
					SOF_RT5682_SSP_CODEC(0) |
					SOF_SPEAKER_AMP_PRESENT |
					SOF_RT1011_SPEAKER_AMP_PRESENT |
					SOF_RT5682_SSP_AMP(1) |
					SOF_RT5682_NUM_HDMIDEV(4)),
	पूर्ण,
	अणु
		.name = "jsl_rt5682_rt1015p",
		.driver_data = (kernel_uदीर्घ_t)(SOF_RT5682_MCLK_EN |
					SOF_RT5682_MCLK_24MHZ |
					SOF_RT5682_SSP_CODEC(0) |
					SOF_SPEAKER_AMP_PRESENT |
					SOF_RT1015P_SPEAKER_AMP_PRESENT |
					SOF_RT5682_SSP_AMP(1)),
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sof_audio = अणु
	.probe = sof_audio_probe,
	.driver = अणु
		.name = "sof_rt5682",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.id_table = board_ids,
पूर्ण;
module_platक्रमm_driver(sof_audio)

/* Module inक्रमmation */
MODULE_DESCRIPTION("SOF Audio Machine driver");
MODULE_AUTHOR("Bard Liao <bard.liao@intel.com>");
MODULE_AUTHOR("Sathya Prakash M R <sathya.prakash.m.r@intel.com>");
MODULE_AUTHOR("Brent Lu <brent.lu@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:sof_rt5682");
MODULE_ALIAS("platform:tgl_max98357a_rt5682");
MODULE_ALIAS("platform:jsl_rt5682_rt1015");
MODULE_ALIAS("platform:tgl_max98373_rt5682");
MODULE_ALIAS("platform:jsl_rt5682_max98360a");
MODULE_ALIAS("platform:cml_rt1015_rt5682");
MODULE_ALIAS("platform:tgl_rt1011_rt5682");
MODULE_ALIAS("platform:jsl_rt5682_rt1015p");
