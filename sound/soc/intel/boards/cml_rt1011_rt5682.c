<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright(c) 2019 Intel Corporation.

/*
 * Intel Cometlake I2S Machine driver क्रम RT1011 + RT5682 codec
 */

#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/dmi.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/rt5682.h>
#समावेश <sound/soc-acpi.h>
#समावेश "../../codecs/rt1011.h"
#समावेश "../../codecs/rt5682.h"
#समावेश "../../codecs/hdac_hdmi.h"
#समावेश "hda_dsp_common.h"

/* The platक्रमm घड़ी outमाला_दो 24Mhz घड़ी to codec as I2S MCLK */
#घोषणा CML_PLAT_CLK	24000000
#घोषणा CML_RT1011_CODEC_DAI "rt1011-aif"
#घोषणा CML_RT5682_CODEC_DAI "rt5682-aif1"
#घोषणा NAME_SIZE 32

#घोषणा SOF_RT1011_SPEAKER_WL		BIT(0)
#घोषणा SOF_RT1011_SPEAKER_WR		BIT(1)
#घोषणा SOF_RT1011_SPEAKER_TL		BIT(2)
#घोषणा SOF_RT1011_SPEAKER_TR		BIT(3)

/* Default: Woofer speakers  */
अटल अचिन्हित दीर्घ sof_rt1011_quirk = SOF_RT1011_SPEAKER_WL |
					SOF_RT1011_SPEAKER_WR;

अटल पूर्णांक sof_rt1011_quirk_cb(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	sof_rt1011_quirk = (अचिन्हित दीर्घ)id->driver_data;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id sof_rt1011_quirk_table[] = अणु
	अणु
		.callback = sof_rt1011_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Google"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Helios"),
	पूर्ण,
		.driver_data = (व्योम *)(SOF_RT1011_SPEAKER_WL | SOF_RT1011_SPEAKER_WR |
					SOF_RT1011_SPEAKER_TL | SOF_RT1011_SPEAKER_TR),
	पूर्ण,
	अणु
	पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_jack hdmi_jack[3];

काष्ठा hdmi_pcm अणु
	काष्ठा list_head head;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक device;
पूर्ण;

काष्ठा card_निजी अणु
	अक्षर codec_name[SND_ACPI_I2C_ID_LEN];
	काष्ठा snd_soc_jack headset;
	काष्ठा list_head hdmi_pcm_list;
	bool common_hdmi_codec_drv;
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new cml_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("WL Ext Spk"),
	SOC_DAPM_PIN_SWITCH("WR Ext Spk"),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new cml_rt1011_tt_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("TL Ext Spk"),
	SOC_DAPM_PIN_SWITCH("TR Ext Spk"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget cml_rt1011_rt5682_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("WL Ext Spk", शून्य),
	SND_SOC_DAPM_SPK("WR Ext Spk", शून्य),
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("SoC DMIC", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget cml_rt1011_tt_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("TL Ext Spk", शून्य),
	SND_SOC_DAPM_SPK("TR Ext Spk", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cml_rt1011_rt5682_map[] = अणु
	/*WL/WR speaker*/
	अणु"WL Ext Spk", शून्य, "WL SPO"पूर्ण,
	अणु"WR Ext Spk", शून्य, "WR SPO"पूर्ण,

	/* HP jack connectors - unknown अगर we have jack detection */
	अणु "Headphone Jack", शून्य, "HPOL" पूर्ण,
	अणु "Headphone Jack", शून्य, "HPOR" पूर्ण,

	/* other jacks */
	अणु "IN1P", शून्य, "Headset Mic" पूर्ण,

	/* DMIC */
	अणु"DMic", शून्य, "SoC DMIC"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cml_rt1011_tt_map[] = अणु
	/*TL/TR speaker*/
	अणु"TL Ext Spk", शून्य, "TL SPO" पूर्ण,
	अणु"TR Ext Spk", शून्य, "TR SPO" पूर्ण,
पूर्ण;

अटल पूर्णांक cml_rt5682_codec_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा card_निजी *ctx = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;
	काष्ठा snd_soc_jack *jack;
	पूर्णांक ret;

	/* need to enable ASRC function क्रम 24MHz mclk rate */
	rt5682_sel_asrc_clk_src(component, RT5682_DA_STEREO1_FILTER |
					RT5682_AD_STEREO1_FILTER,
					RT5682_CLK_SEL_I2S1_ASRC);

	/*
	 * Headset buttons map to the google Reference headset.
	 * These can be configured by userspace.
	 */
	ret = snd_soc_card_jack_new(rtd->card, "Headset Jack",
				    SND_JACK_HEADSET | SND_JACK_BTN_0 |
				    SND_JACK_BTN_1 | SND_JACK_BTN_2 |
				    SND_JACK_BTN_3,
				    &ctx->headset, शून्य, 0);
	अगर (ret) अणु
		dev_err(rtd->dev, "Headset Jack creation failed: %d\n", ret);
		वापस ret;
	पूर्ण

	jack = &ctx->headset;

	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOLUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOLUMEDOWN);
	ret = snd_soc_component_set_jack(component, jack, शून्य);
	अगर (ret)
		dev_err(rtd->dev, "Headset Jack call-back failed: %d\n", ret);

	वापस ret;
पूर्ण;

अटल व्योम cml_rt5682_codec_निकास(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;

	snd_soc_component_set_jack(component, शून्य, शून्य);
पूर्ण

अटल पूर्णांक cml_rt1011_spk_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	पूर्णांक ret = 0;
	काष्ठा snd_soc_card *card = rtd->card;

	अगर (sof_rt1011_quirk & (SOF_RT1011_SPEAKER_TL |
				SOF_RT1011_SPEAKER_TR)) अणु

		ret = snd_soc_add_card_controls(card, cml_rt1011_tt_controls,
					ARRAY_SIZE(cml_rt1011_tt_controls));
		अगर (ret)
			वापस ret;

		ret = snd_soc_dapm_new_controls(&card->dapm,
					cml_rt1011_tt_widमाला_लो,
					ARRAY_SIZE(cml_rt1011_tt_widमाला_लो));
		अगर (ret)
			वापस ret;

		ret = snd_soc_dapm_add_routes(&card->dapm, cml_rt1011_tt_map,
					ARRAY_SIZE(cml_rt1011_tt_map));

		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cml_rt5682_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक clk_id, clk_freq, pll_out, ret;

	clk_id = RT5682_PLL1_S_MCLK;
	clk_freq = CML_PLAT_CLK;

	pll_out = params_rate(params) * 512;

	ret = snd_soc_dai_set_pll(codec_dai, 0, clk_id, clk_freq, pll_out);
	अगर (ret < 0)
		dev_warn(rtd->dev, "snd_soc_dai_set_pll err = %d\n", ret);

	/* Configure sysclk क्रम codec */
	ret = snd_soc_dai_set_sysclk(codec_dai, RT5682_SCLK_S_PLL1,
				     pll_out, SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		dev_warn(rtd->dev, "snd_soc_dai_set_sysclk err = %d\n", ret);

	/*
	 * slot_width should be equal or large than data length, set them
	 * be the same
	 */
	ret = snd_soc_dai_set_tdm_slot(codec_dai, 0x0, 0x0, 2,
				       params_width(params));
	अगर (ret < 0)
		dev_warn(rtd->dev, "set TDM slot err:%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक cml_rt1011_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai;
	काष्ठा snd_soc_card *card = rtd->card;
	पूर्णांक srate, i, ret = 0;

	srate = params_rate(params);

	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु

		/* 100 Fs to drive 24 bit data */
		ret = snd_soc_dai_set_pll(codec_dai, 0, RT1011_PLL1_S_BCLK,
					  100 * srate, 256 * srate);
		अगर (ret < 0) अणु
			dev_err(card->dev, "codec_dai clock not set\n");
			वापस ret;
		पूर्ण

		ret = snd_soc_dai_set_sysclk(codec_dai,
					     RT1011_FS_SYS_PRE_S_PLL1,
					     256 * srate, SND_SOC_CLOCK_IN);
		अगर (ret < 0) अणु
			dev_err(card->dev, "codec_dai clock not set\n");
			वापस ret;
		पूर्ण

		/*
		 * Codec TDM is configured as 24 bit capture/ playback.
		 * 2 CH PB is करोne over 4 codecs - 2 Woofers and 2 Tweeters.
		 * The Left woofer and tweeter plays the Left playback data
		 * and  similar by the Right.
		 * Hence 2 codecs (1 T and 1 W pair) share same Rx slot.
		 * The feedback is captured क्रम each codec inभागidually.
		 * Hence all 4 codecs use 1 Tx slot each क्रम feedback.
		 */
		अगर (sof_rt1011_quirk & (SOF_RT1011_SPEAKER_WL |
					SOF_RT1011_SPEAKER_WR)) अणु
			अगर (!म_भेद(codec_dai->component->name, "i2c-10EC1011:00")) अणु
				ret = snd_soc_dai_set_tdm_slot(codec_dai,
							       0x4, 0x1, 4, 24);
				अगर (ret < 0)
					अवरोध;
			पूर्ण

			अगर (!म_भेद(codec_dai->component->name, "i2c-10EC1011:01")) अणु
				ret = snd_soc_dai_set_tdm_slot(codec_dai,
							       0x8, 0x2, 4, 24);
				अगर (ret < 0)
					अवरोध;
			पूर्ण
		पूर्ण

		अगर (sof_rt1011_quirk & (SOF_RT1011_SPEAKER_TL |
					SOF_RT1011_SPEAKER_TR)) अणु
			अगर (!म_भेद(codec_dai->component->name, "i2c-10EC1011:02")) अणु
				ret = snd_soc_dai_set_tdm_slot(codec_dai,
							       0x1, 0x1, 4, 24);
				अगर (ret < 0)
					अवरोध;
			पूर्ण

			अगर (!म_भेद(codec_dai->component->name, "i2c-10EC1011:03")) अणु
				ret = snd_soc_dai_set_tdm_slot(codec_dai,
							       0x2, 0x2, 4, 24);
				अगर (ret < 0)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (ret < 0)
		dev_err(rtd->dev,
			"set codec TDM slot for %s failed with error %d\n",
			codec_dai->component->name, ret);
	वापस ret;
पूर्ण

अटल काष्ठा snd_soc_ops cml_rt5682_ops = अणु
	.hw_params = cml_rt5682_hw_params,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops cml_rt1011_ops = अणु
	.hw_params = cml_rt1011_hw_params,
पूर्ण;

अटल पूर्णांक sof_card_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा card_निजी *ctx = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_component *component = शून्य;
	अक्षर jack_name[NAME_SIZE];
	काष्ठा hdmi_pcm *pcm;
	पूर्णांक ret, i = 0;

	अगर (list_empty(&ctx->hdmi_pcm_list))
		वापस -EINVAL;

	अगर (ctx->common_hdmi_codec_drv) अणु
		pcm = list_first_entry(&ctx->hdmi_pcm_list, काष्ठा hdmi_pcm,
				       head);
		component = pcm->codec_dai->component;
		वापस hda_dsp_hdmi_build_controls(card, component);
	पूर्ण

	list_क्रम_each_entry(pcm, &ctx->hdmi_pcm_list, head) अणु
		component = pcm->codec_dai->component;
		snम_लिखो(jack_name, माप(jack_name),
			 "HDMI/DP, pcm=%d Jack", pcm->device);
		ret = snd_soc_card_jack_new(card, jack_name,
					    SND_JACK_AVOUT, &hdmi_jack[i],
					    शून्य, 0);
		अगर (ret)
			वापस ret;

		ret = hdac_hdmi_jack_init(pcm->codec_dai, pcm->device,
					  &hdmi_jack[i]);
		अगर (ret < 0)
			वापस ret;

		i++;
	पूर्ण

	वापस hdac_hdmi_jack_port_init(component, &card->dapm);
पूर्ण

अटल पूर्णांक hdmi_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा card_निजी *ctx = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_dai *dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा hdmi_pcm *pcm;

	pcm = devm_kzalloc(rtd->card->dev, माप(*pcm), GFP_KERNEL);
	अगर (!pcm)
		वापस -ENOMEM;

	pcm->device = dai->id;
	pcm->codec_dai = dai;

	list_add_tail(&pcm->head, &ctx->hdmi_pcm_list);

	वापस 0;
पूर्ण

/* Cometlake digital audio पूर्णांकerface glue - connects codec <--> CPU */

SND_SOC_DAILINK_DEF(ssp0_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("SSP0 Pin")));
SND_SOC_DAILINK_DEF(ssp0_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-10EC5682:00",
				CML_RT5682_CODEC_DAI)));

SND_SOC_DAILINK_DEF(ssp1_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("SSP1 Pin")));
SND_SOC_DAILINK_DEF(ssp1_codec_2spk,
	DAILINK_COMP_ARRAY(
	/* WL */ COMP_CODEC("i2c-10EC1011:00", CML_RT1011_CODEC_DAI),
	/* WR */ COMP_CODEC("i2c-10EC1011:01", CML_RT1011_CODEC_DAI)));
SND_SOC_DAILINK_DEF(ssp1_codec_4spk,
	DAILINK_COMP_ARRAY(
	/* WL */ COMP_CODEC("i2c-10EC1011:00", CML_RT1011_CODEC_DAI),
	/* WR */ COMP_CODEC("i2c-10EC1011:01", CML_RT1011_CODEC_DAI),
	/* TL */ COMP_CODEC("i2c-10EC1011:02", CML_RT1011_CODEC_DAI),
	/* TR */ COMP_CODEC("i2c-10EC1011:03", CML_RT1011_CODEC_DAI)));


SND_SOC_DAILINK_DEF(dmic_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("DMIC01 Pin")));

SND_SOC_DAILINK_DEF(dmic16k_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("DMIC16k Pin")));

SND_SOC_DAILINK_DEF(dmic_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("dmic-codec", "dmic-hifi")));

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

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("0000:00:1f.3")));

अटल काष्ठा snd_soc_dai_link cml_rt1011_rt5682_dailink[] = अणु
	/* Back End DAI links */
	अणु
		/* SSP0 - Codec */
		.name = "SSP0-Codec",
		.id = 0,
		.init = cml_rt5682_codec_init,
		.निकास = cml_rt5682_codec_निकास,
		.ignore_pmकरोwn_समय = 1,
		.ops = &cml_rt5682_ops,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(ssp0_pin, ssp0_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "dmic01",
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
		SND_SOC_DAILINK_REG(dmic16k_pin, dmic_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp1",
		.id = 3,
		.init = hdmi_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp1_pin, idisp1_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp2",
		.id = 4,
		.init = hdmi_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp2_pin, idisp2_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp3",
		.id = 5,
		.init = hdmi_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp3_pin, idisp3_codec, platक्रमm),
	पूर्ण,
	अणु
		/*
		 * SSP1 - Codec : added to end of list ensuring
		 * reuse of common topologies क्रम other end poपूर्णांकs
		 * and changing only SSP1's codec
		 */
		.name = "SSP1-Codec",
		.id = 6,
		.dpcm_playback = 1,
		.dpcm_capture = 1, /* Capture stream provides Feedback */
		.no_pcm = 1,
		.init = cml_rt1011_spk_init,
		.ops = &cml_rt1011_ops,
		SND_SOC_DAILINK_REG(ssp1_pin, ssp1_codec_2spk, platक्रमm),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_codec_conf rt1011_conf[] = अणु
	अणु
		.dlc = COMP_CODEC_CONF("i2c-10EC1011:00"),
		.name_prefix = "WL",
	पूर्ण,
	अणु
		.dlc = COMP_CODEC_CONF("i2c-10EC1011:01"),
		.name_prefix = "WR",
	पूर्ण,
	/* single configuration काष्ठाure क्रम 2 and 4 channels */
	अणु
		.dlc = COMP_CODEC_CONF("i2c-10EC1011:02"),
		.name_prefix = "TL",
	पूर्ण,
	अणु
		.dlc = COMP_CODEC_CONF("i2c-10EC1011:03"),
		.name_prefix = "TR",
	पूर्ण,
पूर्ण;

/* Cometlake audio machine driver क्रम RT1011 and RT5682 */
अटल काष्ठा snd_soc_card snd_soc_card_cml = अणु
	.name = "cml_rt1011_rt5682",
	.owner = THIS_MODULE,
	.dai_link = cml_rt1011_rt5682_dailink,
	.num_links = ARRAY_SIZE(cml_rt1011_rt5682_dailink),
	.codec_conf = rt1011_conf,
	.num_configs = ARRAY_SIZE(rt1011_conf),
	.dapm_widमाला_लो = cml_rt1011_rt5682_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(cml_rt1011_rt5682_widमाला_लो),
	.dapm_routes = cml_rt1011_rt5682_map,
	.num_dapm_routes = ARRAY_SIZE(cml_rt1011_rt5682_map),
	.controls = cml_controls,
	.num_controls = ARRAY_SIZE(cml_controls),
	.fully_routed = true,
	.late_probe = sof_card_late_probe,
पूर्ण;

अटल पूर्णांक snd_cml_rt1011_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_dai_link *dai_link;
	काष्ठा card_निजी *ctx;
	काष्ठा snd_soc_acpi_mach *mach;
	स्थिर अक्षर *platक्रमm_name;
	पूर्णांक ret, i;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&ctx->hdmi_pcm_list);
	mach = pdev->dev.platक्रमm_data;
	snd_soc_card_cml.dev = &pdev->dev;
	platक्रमm_name = mach->mach_params.platक्रमm;

	dmi_check_प्रणाली(sof_rt1011_quirk_table);

	dev_dbg(&pdev->dev, "sof_rt1011_quirk = %lx\n", sof_rt1011_quirk);

	/* when 4 speaker is available, update codec config */
	अगर (sof_rt1011_quirk & (SOF_RT1011_SPEAKER_TL |
				SOF_RT1011_SPEAKER_TR)) अणु
		क्रम_each_card_prelinks(&snd_soc_card_cml, i, dai_link) अणु
			अगर (!म_भेद(dai_link->codecs[0].dai_name,
				    CML_RT1011_CODEC_DAI)) अणु
				dai_link->codecs = ssp1_codec_4spk;
				dai_link->num_codecs = ARRAY_SIZE(ssp1_codec_4spk);
			पूर्ण
		पूर्ण
	पूर्ण

	/* set platक्रमm name क्रम each dailink */
	ret = snd_soc_fixup_dai_links_platक्रमm_name(&snd_soc_card_cml,
						    platक्रमm_name);
	अगर (ret)
		वापस ret;

	ctx->common_hdmi_codec_drv = mach->mach_params.common_hdmi_codec_drv;

	snd_soc_card_set_drvdata(&snd_soc_card_cml, ctx);

	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, &snd_soc_card_cml);
पूर्ण

अटल काष्ठा platक्रमm_driver snd_cml_rt1011_rt5682_driver = अणु
	.probe = snd_cml_rt1011_probe,
	.driver = अणु
		.name = "cml_rt1011_rt5682",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(snd_cml_rt1011_rt5682_driver);

/* Module inक्रमmation */
MODULE_DESCRIPTION("Cometlake Audio Machine driver - RT1011 and RT5682 in I2S mode");
MODULE_AUTHOR("Naveen Manohar <naveen.m@intel.com>");
MODULE_AUTHOR("Sathya Prakash M R <sathya.prakash.m.r@intel.com>");
MODULE_AUTHOR("Shuming Fan <shumingf@realtek.com>");
MODULE_AUTHOR("Mac Chiang <mac.chiang@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:cml_rt1011_rt5682");
