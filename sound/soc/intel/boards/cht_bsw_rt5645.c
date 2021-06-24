<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  cht-bsw-rt5645.c - ASoc Machine driver क्रम Intel Cherryview-based platक्रमms
 *                     Cherrytrail and Braswell, with RT5645 codec.
 *
 *  Copyright (C) 2015 Intel Corp
 *  Author: Fang, Yang A <yang.a.fang@पूर्णांकel.com>
 *	        N,Harshapriya <harshapriya.n@पूर्णांकel.com>
 *  This file is modअगरied from cht_bsw_rt5672.c
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/dmi.h>
#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>
#समावेश <sound/soc-acpi.h>
#समावेश "../../codecs/rt5645.h"
#समावेश "../atom/sst-atom-controls.h"
#समावेश "../common/soc-intel-quirks.h"

#घोषणा CHT_PLAT_CLK_3_HZ	19200000
#घोषणा CHT_CODEC_DAI1	"rt5645-aif1"
#घोषणा CHT_CODEC_DAI2	"rt5645-aif2"

काष्ठा cht_acpi_card अणु
	अक्षर *codec_id;
	पूर्णांक codec_type;
	काष्ठा snd_soc_card *soc_card;
पूर्ण;

काष्ठा cht_mc_निजी अणु
	काष्ठा snd_soc_jack jack;
	काष्ठा cht_acpi_card *acpi_card;
	अक्षर codec_name[SND_ACPI_I2C_ID_LEN];
	काष्ठा clk *mclk;
पूर्ण;

#घोषणा CHT_RT5645_MAP(quirk)	((quirk) & GENMASK(7, 0))
#घोषणा CHT_RT5645_SSP2_AIF2     BIT(16) /* शेष is using AIF1  */
#घोषणा CHT_RT5645_SSP0_AIF1     BIT(17)
#घोषणा CHT_RT5645_SSP0_AIF2     BIT(18)
#घोषणा CHT_RT5645_PMC_PLT_CLK_0 BIT(19)

अटल अचिन्हित दीर्घ cht_rt5645_quirk = 0;

अटल व्योम log_quirks(काष्ठा device *dev)
अणु
	अगर (cht_rt5645_quirk & CHT_RT5645_SSP2_AIF2)
		dev_info(dev, "quirk SSP2_AIF2 enabled");
	अगर (cht_rt5645_quirk & CHT_RT5645_SSP0_AIF1)
		dev_info(dev, "quirk SSP0_AIF1 enabled");
	अगर (cht_rt5645_quirk & CHT_RT5645_SSP0_AIF2)
		dev_info(dev, "quirk SSP0_AIF2 enabled");
	अगर (cht_rt5645_quirk & CHT_RT5645_PMC_PLT_CLK_0)
		dev_info(dev, "quirk PMC_PLT_CLK_0 enabled");
पूर्ण

अटल पूर्णांक platक्रमm_घड़ी_control(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *k, पूर्णांक  event)
अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा snd_soc_dai *codec_dai;
	काष्ठा cht_mc_निजी *ctx = snd_soc_card_get_drvdata(card);
	पूर्णांक ret;

	codec_dai = snd_soc_card_get_codec_dai(card, CHT_CODEC_DAI1);
	अगर (!codec_dai)
		codec_dai = snd_soc_card_get_codec_dai(card, CHT_CODEC_DAI2);

	अगर (!codec_dai) अणु
		dev_err(card->dev, "Codec dai not found; Unable to set platform clock\n");
		वापस -EIO;
	पूर्ण

	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		ret = clk_prepare_enable(ctx->mclk);
		अगर (ret < 0) अणु
			dev_err(card->dev,
				"could not configure MCLK state");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Set codec sysclk source to its पूर्णांकernal घड़ी because codec PLL will
		 * be off when idle and MCLK will also be off when codec is
		 * runसमय suspended. Codec needs घड़ी क्रम jack detection and button
		 * press. MCLK is turned off with घड़ी framework or ACPI.
		 */
		ret = snd_soc_dai_set_sysclk(codec_dai, RT5645_SCLK_S_RCCLK,
					48000 * 512, SND_SOC_CLOCK_IN);
		अगर (ret < 0) अणु
			dev_err(card->dev, "can't set codec sysclk: %d\n", ret);
			वापस ret;
		पूर्ण

		clk_disable_unprepare(ctx->mclk);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget cht_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Int Mic", शून्य),
	SND_SOC_DAPM_MIC("Int Analog Mic", शून्य),
	SND_SOC_DAPM_SPK("Ext Spk", शून्य),
	SND_SOC_DAPM_SUPPLY("Platform Clock", SND_SOC_NOPM, 0, 0,
			platक्रमm_घड़ी_control, SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cht_rt5645_audio_map[] = अणु
	अणु"IN1P", शून्य, "Headset Mic"पूर्ण,
	अणु"IN1N", शून्य, "Headset Mic"पूर्ण,
	अणु"DMIC L1", शून्य, "Int Mic"पूर्ण,
	अणु"DMIC R1", शून्य, "Int Mic"पूर्ण,
	अणु"IN2P", शून्य, "Int Analog Mic"पूर्ण,
	अणु"IN2N", शून्य, "Int Analog Mic"पूर्ण,
	अणु"Headphone", शून्य, "HPOL"पूर्ण,
	अणु"Headphone", शून्य, "HPOR"पूर्ण,
	अणु"Ext Spk", शून्य, "SPOL"पूर्ण,
	अणु"Ext Spk", शून्य, "SPOR"पूर्ण,
	अणु"Headphone", शून्य, "Platform Clock"पूर्ण,
	अणु"Headset Mic", शून्य, "Platform Clock"पूर्ण,
	अणु"Int Mic", शून्य, "Platform Clock"पूर्ण,
	अणु"Int Analog Mic", शून्य, "Platform Clock"पूर्ण,
	अणु"Int Analog Mic", शून्य, "micbias1"पूर्ण,
	अणु"Int Analog Mic", शून्य, "micbias2"पूर्ण,
	अणु"Ext Spk", शून्य, "Platform Clock"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cht_rt5650_audio_map[] = अणु
	अणु"IN1P", शून्य, "Headset Mic"पूर्ण,
	अणु"IN1N", शून्य, "Headset Mic"पूर्ण,
	अणु"DMIC L2", शून्य, "Int Mic"पूर्ण,
	अणु"DMIC R2", शून्य, "Int Mic"पूर्ण,
	अणु"Headphone", शून्य, "HPOL"पूर्ण,
	अणु"Headphone", शून्य, "HPOR"पूर्ण,
	अणु"Ext Spk", शून्य, "SPOL"पूर्ण,
	अणु"Ext Spk", शून्य, "SPOR"पूर्ण,
	अणु"Headphone", शून्य, "Platform Clock"पूर्ण,
	अणु"Headset Mic", शून्य, "Platform Clock"पूर्ण,
	अणु"Int Mic", शून्य, "Platform Clock"पूर्ण,
	अणु"Ext Spk", शून्य, "Platform Clock"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cht_rt5645_ssp2_aअगर1_map[] = अणु
	अणु"AIF1 Playback", शून्य, "ssp2 Tx"पूर्ण,
	अणु"ssp2 Tx", शून्य, "codec_out0"पूर्ण,
	अणु"ssp2 Tx", शून्य, "codec_out1"पूर्ण,
	अणु"codec_in0", शून्य, "ssp2 Rx" पूर्ण,
	अणु"codec_in1", शून्य, "ssp2 Rx" पूर्ण,
	अणु"ssp2 Rx", शून्य, "AIF1 Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cht_rt5645_ssp2_aअगर2_map[] = अणु
	अणु"AIF2 Playback", शून्य, "ssp2 Tx"पूर्ण,
	अणु"ssp2 Tx", शून्य, "codec_out0"पूर्ण,
	अणु"ssp2 Tx", शून्य, "codec_out1"पूर्ण,
	अणु"codec_in0", शून्य, "ssp2 Rx" पूर्ण,
	अणु"codec_in1", शून्य, "ssp2 Rx" पूर्ण,
	अणु"ssp2 Rx", शून्य, "AIF2 Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cht_rt5645_ssp0_aअगर1_map[] = अणु
	अणु"AIF1 Playback", शून्य, "ssp0 Tx"पूर्ण,
	अणु"ssp0 Tx", शून्य, "modem_out"पूर्ण,
	अणु"modem_in", शून्य, "ssp0 Rx" पूर्ण,
	अणु"ssp0 Rx", शून्य, "AIF1 Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cht_rt5645_ssp0_aअगर2_map[] = अणु
	अणु"AIF2 Playback", शून्य, "ssp0 Tx"पूर्ण,
	अणु"ssp0 Tx", शून्य, "modem_out"पूर्ण,
	अणु"modem_in", शून्य, "ssp0 Rx" पूर्ण,
	अणु"ssp0 Rx", शून्य, "AIF2 Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new cht_mc_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Int Mic"),
	SOC_DAPM_PIN_SWITCH("Int Analog Mic"),
	SOC_DAPM_PIN_SWITCH("Ext Spk"),
पूर्ण;

अटल काष्ठा snd_soc_jack_pin cht_bsw_jack_pins[] = अणु
	अणु
		.pin	= "Headphone",
		.mask	= SND_JACK_HEADPHONE,
	पूर्ण,
	अणु
		.pin	= "Headset Mic",
		.mask	= SND_JACK_MICROPHONE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक cht_aअगर1_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	/* set codec PLL source to the 19.2MHz platक्रमm घड़ी (MCLK) */
	ret = snd_soc_dai_set_pll(codec_dai, 0, RT5645_PLL1_S_MCLK,
				  CHT_PLAT_CLK_3_HZ, params_rate(params) * 512);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set codec pll: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(codec_dai, RT5645_SCLK_S_PLL1,
				params_rate(params) * 512, SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set codec sysclk: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cht_rt5645_quirk_cb(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	cht_rt5645_quirk = (अचिन्हित दीर्घ)id->driver_data;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id cht_rt5645_quirk_table[] = अणु
	अणु
		/* Strago family Chromebooks */
		.callback = cht_rt5645_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_FAMILY, "Intel_Strago"),
		पूर्ण,
		.driver_data = (व्योम *)CHT_RT5645_PMC_PLT_CLK_0,
	पूर्ण,
	अणु
	पूर्ण,
पूर्ण;

अटल पूर्णांक cht_codec_init(काष्ठा snd_soc_pcm_runसमय *runसमय)
अणु
	काष्ठा snd_soc_card *card = runसमय->card;
	काष्ठा cht_mc_निजी *ctx = snd_soc_card_get_drvdata(runसमय->card);
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(runसमय, 0)->component;
	पूर्णांक jack_type;
	पूर्णांक ret;

	अगर ((cht_rt5645_quirk & CHT_RT5645_SSP2_AIF2) ||
	    (cht_rt5645_quirk & CHT_RT5645_SSP0_AIF2)) अणु
		/* Select clk_i2s2_asrc as ASRC घड़ी source */
		rt5645_sel_asrc_clk_src(component,
					RT5645_DA_STEREO_FILTER |
					RT5645_DA_MONO_L_FILTER |
					RT5645_DA_MONO_R_FILTER |
					RT5645_AD_STEREO_FILTER,
					RT5645_CLK_SEL_I2S2_ASRC);
	पूर्ण अन्यथा अणु
		/* Select clk_i2s1_asrc as ASRC घड़ी source */
		rt5645_sel_asrc_clk_src(component,
					RT5645_DA_STEREO_FILTER |
					RT5645_DA_MONO_L_FILTER |
					RT5645_DA_MONO_R_FILTER |
					RT5645_AD_STEREO_FILTER,
					RT5645_CLK_SEL_I2S1_ASRC);
	पूर्ण

	अगर (cht_rt5645_quirk & CHT_RT5645_SSP2_AIF2) अणु
		ret = snd_soc_dapm_add_routes(&card->dapm,
					cht_rt5645_ssp2_aअगर2_map,
					ARRAY_SIZE(cht_rt5645_ssp2_aअगर2_map));
	पूर्ण अन्यथा अगर (cht_rt5645_quirk & CHT_RT5645_SSP0_AIF1) अणु
		ret = snd_soc_dapm_add_routes(&card->dapm,
					cht_rt5645_ssp0_aअगर1_map,
					ARRAY_SIZE(cht_rt5645_ssp0_aअगर1_map));
	पूर्ण अन्यथा अगर (cht_rt5645_quirk & CHT_RT5645_SSP0_AIF2) अणु
		ret = snd_soc_dapm_add_routes(&card->dapm,
					cht_rt5645_ssp0_aअगर2_map,
					ARRAY_SIZE(cht_rt5645_ssp0_aअगर2_map));
	पूर्ण अन्यथा अणु
		ret = snd_soc_dapm_add_routes(&card->dapm,
					cht_rt5645_ssp2_aअगर1_map,
					ARRAY_SIZE(cht_rt5645_ssp2_aअगर1_map));
	पूर्ण
	अगर (ret)
		वापस ret;

	अगर (ctx->acpi_card->codec_type == CODEC_TYPE_RT5650)
		jack_type = SND_JACK_HEADPHONE | SND_JACK_MICROPHONE |
					SND_JACK_BTN_0 | SND_JACK_BTN_1 |
					SND_JACK_BTN_2 | SND_JACK_BTN_3;
	अन्यथा
		jack_type = SND_JACK_HEADPHONE | SND_JACK_MICROPHONE;

	ret = snd_soc_card_jack_new(runसमय->card, "Headset",
				    jack_type, &ctx->jack,
				    cht_bsw_jack_pins, ARRAY_SIZE(cht_bsw_jack_pins));
	अगर (ret) अणु
		dev_err(runसमय->dev, "Headset jack creation failed %d\n", ret);
		वापस ret;
	पूर्ण

	rt5645_set_jack_detect(component, &ctx->jack, &ctx->jack, &ctx->jack);


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

	ret = clk_set_rate(ctx->mclk, CHT_PLAT_CLK_3_HZ);

	अगर (ret)
		dev_err(runसमय->dev, "unable to set MCLK rate\n");

	वापस ret;
पूर्ण

अटल पूर्णांक cht_codec_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
			    काष्ठा snd_pcm_hw_params *params)
अणु
	पूर्णांक ret;
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
			SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *channels = hw_param_पूर्णांकerval(params,
						SNDRV_PCM_HW_PARAM_CHANNELS);

	/* The DSP will covert the FE rate to 48k, stereo, 24bits */
	rate->min = rate->max = 48000;
	channels->min = channels->max = 2;

	अगर ((cht_rt5645_quirk & CHT_RT5645_SSP0_AIF1) ||
		(cht_rt5645_quirk & CHT_RT5645_SSP0_AIF2)) अणु

		/* set SSP0 to 16-bit */
		params_set_क्रमmat(params, SNDRV_PCM_FORMAT_S16_LE);

		/*
		 * Default mode क्रम SSP configuration is TDM 4 slot, override config
		 * with explicit setting to I2S 2ch 16-bit. The word length is set with
		 * dai_set_tdm_slot() since there is no other API exposed
		 */
		ret = snd_soc_dai_set_fmt(asoc_rtd_to_cpu(rtd, 0),
					SND_SOC_DAIFMT_I2S     |
					SND_SOC_DAIFMT_NB_NF   |
					SND_SOC_DAIFMT_CBS_CFS
			);
		अगर (ret < 0) अणु
			dev_err(rtd->dev, "can't set format to I2S, err %d\n", ret);
			वापस ret;
		पूर्ण

		ret = snd_soc_dai_set_fmt(asoc_rtd_to_codec(rtd, 0),
					SND_SOC_DAIFMT_I2S     |
					SND_SOC_DAIFMT_NB_NF   |
					SND_SOC_DAIFMT_CBS_CFS
			);
		अगर (ret < 0) अणु
			dev_err(rtd->dev, "can't set format to I2S, err %d\n", ret);
			वापस ret;
		पूर्ण

		ret = snd_soc_dai_set_tdm_slot(asoc_rtd_to_cpu(rtd, 0), 0x3, 0x3, 2, 16);
		अगर (ret < 0) अणु
			dev_err(rtd->dev, "can't set I2S config, err %d\n", ret);
			वापस ret;
		पूर्ण

	पूर्ण अन्यथा अणु

		/* set SSP2 to 24-bit */
		params_set_क्रमmat(params, SNDRV_PCM_FORMAT_S24_LE);

		/*
		 * Default mode क्रम SSP configuration is TDM 4 slot
		 */
		ret = snd_soc_dai_set_fmt(asoc_rtd_to_codec(rtd, 0),
					SND_SOC_DAIFMT_DSP_B |
					SND_SOC_DAIFMT_IB_NF |
					SND_SOC_DAIFMT_CBS_CFS);
		अगर (ret < 0) अणु
			dev_err(rtd->dev, "can't set format to TDM %d\n", ret);
			वापस ret;
		पूर्ण

		/* TDM 4 slots 24 bit, set Rx & Tx biपंचांगask to 4 active slots */
		ret = snd_soc_dai_set_tdm_slot(asoc_rtd_to_codec(rtd, 0), 0xF, 0xF, 4, 24);
		अगर (ret < 0) अणु
			dev_err(rtd->dev, "can't set codec TDM slot %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cht_aअगर1_startup(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_pcm_hw_स्थिरraपूर्णांक_single(substream->runसमय,
			SNDRV_PCM_HW_PARAM_RATE, 48000);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops cht_aअगर1_ops = अणु
	.startup = cht_aअगर1_startup,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops cht_be_ssp2_ops = अणु
	.hw_params = cht_aअगर1_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEF(dummy,
	DAILINK_COMP_ARRAY(COMP_DUMMY()));

SND_SOC_DAILINK_DEF(media,
	DAILINK_COMP_ARRAY(COMP_CPU("media-cpu-dai")));

SND_SOC_DAILINK_DEF(deepbuffer,
	DAILINK_COMP_ARRAY(COMP_CPU("deepbuffer-cpu-dai")));

SND_SOC_DAILINK_DEF(ssp2_port,
	DAILINK_COMP_ARRAY(COMP_CPU("ssp2-port")));
SND_SOC_DAILINK_DEF(ssp2_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-10EC5645:00", "rt5645-aif1")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("sst-mfld-platform")));

अटल काष्ठा snd_soc_dai_link cht_dailink[] = अणु
	[MERR_DPCM_AUDIO] = अणु
		.name = "Audio Port",
		.stream_name = "Audio",
		.nonatomic = true,
		.dynamic = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ops = &cht_aअगर1_ops,
		SND_SOC_DAILINK_REG(media, dummy, platक्रमm),
	पूर्ण,
	[MERR_DPCM_DEEP_BUFFER] = अणु
		.name = "Deep-Buffer Audio Port",
		.stream_name = "Deep-Buffer Audio",
		.nonatomic = true,
		.dynamic = 1,
		.dpcm_playback = 1,
		.ops = &cht_aअगर1_ops,
		SND_SOC_DAILINK_REG(deepbuffer, dummy, platक्रमm),
	पूर्ण,
	/* CODEC<->CODEC link */
	/* back ends */
	अणु
		.name = "SSP2-Codec",
		.id = 0,
		.no_pcm = 1,
		.init = cht_codec_init,
		.be_hw_params_fixup = cht_codec_fixup,
		.nonatomic = true,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ops = &cht_be_ssp2_ops,
		SND_SOC_DAILINK_REG(ssp2_port, ssp2_codec, platक्रमm),
	पूर्ण,
पूर्ण;

/* use space beक्रमe codec name to simplअगरy card ID, and simplअगरy driver name */
#घोषणा SOF_CARD_RT5645_NAME "bytcht rt5645" /* card name 'sof-bytcht rt5645' */
#घोषणा SOF_CARD_RT5650_NAME "bytcht rt5650" /* card name 'sof-bytcht rt5650' */
#घोषणा SOF_DRIVER_NAME "SOF"

#घोषणा CARD_RT5645_NAME "chtrt5645"
#घोषणा CARD_RT5650_NAME "chtrt5650"
#घोषणा DRIVER_NAME शून्य /* card name will be used क्रम driver name */

/* SoC card */
अटल काष्ठा snd_soc_card snd_soc_card_chtrt5645 = अणु
	.owner = THIS_MODULE,
	.dai_link = cht_dailink,
	.num_links = ARRAY_SIZE(cht_dailink),
	.dapm_widमाला_लो = cht_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(cht_dapm_widमाला_लो),
	.dapm_routes = cht_rt5645_audio_map,
	.num_dapm_routes = ARRAY_SIZE(cht_rt5645_audio_map),
	.controls = cht_mc_controls,
	.num_controls = ARRAY_SIZE(cht_mc_controls),
पूर्ण;

अटल काष्ठा snd_soc_card snd_soc_card_chtrt5650 = अणु
	.owner = THIS_MODULE,
	.dai_link = cht_dailink,
	.num_links = ARRAY_SIZE(cht_dailink),
	.dapm_widमाला_लो = cht_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(cht_dapm_widमाला_लो),
	.dapm_routes = cht_rt5650_audio_map,
	.num_dapm_routes = ARRAY_SIZE(cht_rt5650_audio_map),
	.controls = cht_mc_controls,
	.num_controls = ARRAY_SIZE(cht_mc_controls),
पूर्ण;

अटल काष्ठा cht_acpi_card snd_soc_cards[] = अणु
	अणु"10EC5640", CODEC_TYPE_RT5645, &snd_soc_card_chtrt5645पूर्ण,
	अणु"10EC5645", CODEC_TYPE_RT5645, &snd_soc_card_chtrt5645पूर्ण,
	अणु"10EC5648", CODEC_TYPE_RT5645, &snd_soc_card_chtrt5645पूर्ण,
	अणु"10EC3270", CODEC_TYPE_RT5645, &snd_soc_card_chtrt5645पूर्ण,
	अणु"10EC5650", CODEC_TYPE_RT5650, &snd_soc_card_chtrt5650पूर्ण,
पूर्ण;

अटल अक्षर cht_rt5645_codec_name[SND_ACPI_I2C_ID_LEN];

काष्ठा acpi_chan_package अणु   /* ACPICA seems to require 64 bit पूर्णांकegers */
	u64 aअगर_value;       /* 1: AIF1, 2: AIF2 */
	u64 mघड़ी_value;    /* usually 25MHz (0x17d7940), ignored */
पूर्ण;

अटल पूर्णांक snd_cht_mc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = snd_soc_cards[0].soc_card;
	काष्ठा snd_soc_acpi_mach *mach;
	स्थिर अक्षर *platक्रमm_name;
	काष्ठा cht_mc_निजी *drv;
	काष्ठा acpi_device *adev;
	bool sof_parent;
	bool found = false;
	bool is_bytcr = false;
	पूर्णांक dai_index = 0;
	पूर्णांक ret_val = 0;
	पूर्णांक i;
	स्थिर अक्षर *mclk_name;

	drv = devm_kzalloc(&pdev->dev, माप(*drv), GFP_KERNEL);
	अगर (!drv)
		वापस -ENOMEM;

	mach = pdev->dev.platक्रमm_data;

	क्रम (i = 0; i < ARRAY_SIZE(snd_soc_cards); i++) अणु
		अगर (acpi_dev_found(snd_soc_cards[i].codec_id) &&
			(!म_भेदन(snd_soc_cards[i].codec_id, mach->id, 8))) अणु
			dev_dbg(&pdev->dev,
				"found codec %s\n", snd_soc_cards[i].codec_id);
			card = snd_soc_cards[i].soc_card;
			drv->acpi_card = &snd_soc_cards[i];
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		dev_err(&pdev->dev, "No matching HID found in supported list\n");
		वापस -ENODEV;
	पूर्ण

	card->dev = &pdev->dev;
	प्र_लिखो(drv->codec_name, "i2c-%s:00", drv->acpi_card->codec_id);

	/* set correct codec name */
	क्रम (i = 0; i < ARRAY_SIZE(cht_dailink); i++)
		अगर (!म_भेद(card->dai_link[i].codecs->name,
			    "i2c-10EC5645:00")) अणु
			card->dai_link[i].codecs->name = drv->codec_name;
			dai_index = i;
		पूर्ण

	/* fixup codec name based on HID */
	adev = acpi_dev_get_first_match_dev(mach->id, शून्य, -1);
	अगर (adev) अणु
		snम_लिखो(cht_rt5645_codec_name, माप(cht_rt5645_codec_name),
			 "i2c-%s", acpi_dev_name(adev));
		put_device(&adev->dev);
		cht_dailink[dai_index].codecs->name = cht_rt5645_codec_name;
	पूर्ण

	/*
	 * swap SSP0 अगर bytcr is detected
	 * (will be overridden अगर DMI quirk is detected)
	 */
	अगर (soc_पूर्णांकel_is_byt()) अणु
		अगर (mach->mach_params.acpi_ipc_irq_index == 0)
			is_bytcr = true;
	पूर्ण

	अगर (is_bytcr) अणु
		/*
		 * Baytrail CR platक्रमms may have CHAN package in BIOS, try
		 * to find relevant routing quirk based as करोne on Winकरोws
		 * platक्रमms. We have to पढ़ो the inक्रमmation directly from the
		 * BIOS, at this stage the card is not created and the links
		 * with the codec driver/pdata are non-existent
		 */

		काष्ठा acpi_chan_package chan_package;

		/* क्रमmat specअगरied: 2 64-bit पूर्णांकegers */
		काष्ठा acpi_buffer क्रमmat = अणुमाप("NN"), "NN"पूर्ण;
		काष्ठा acpi_buffer state = अणु0, शून्यपूर्ण;
		काष्ठा snd_soc_acpi_package_context pkg_ctx;
		bool pkg_found = false;

		state.length = माप(chan_package);
		state.poपूर्णांकer = &chan_package;

		pkg_ctx.name = "CHAN";
		pkg_ctx.length = 2;
		pkg_ctx.क्रमmat = &क्रमmat;
		pkg_ctx.state = &state;
		pkg_ctx.data_valid = false;

		pkg_found = snd_soc_acpi_find_package_from_hid(mach->id,
							       &pkg_ctx);
		अगर (pkg_found) अणु
			अगर (chan_package.aअगर_value == 1) अणु
				dev_info(&pdev->dev, "BIOS Routing: AIF1 connected\n");
				cht_rt5645_quirk |= CHT_RT5645_SSP0_AIF1;
			पूर्ण अन्यथा  अगर (chan_package.aअगर_value == 2) अणु
				dev_info(&pdev->dev, "BIOS Routing: AIF2 connected\n");
				cht_rt5645_quirk |= CHT_RT5645_SSP0_AIF2;
			पूर्ण अन्यथा अणु
				dev_info(&pdev->dev, "BIOS Routing isn't valid, ignored\n");
				pkg_found = false;
			पूर्ण
		पूर्ण

		अगर (!pkg_found) अणु
			/* no BIOS indications, assume SSP0-AIF2 connection */
			cht_rt5645_quirk |= CHT_RT5645_SSP0_AIF2;
		पूर्ण
	पूर्ण

	/* check quirks beक्रमe creating card */
	dmi_check_प्रणाली(cht_rt5645_quirk_table);
	log_quirks(&pdev->dev);

	अगर ((cht_rt5645_quirk & CHT_RT5645_SSP2_AIF2) ||
	    (cht_rt5645_quirk & CHT_RT5645_SSP0_AIF2))
		cht_dailink[dai_index].codecs->dai_name = "rt5645-aif2";

	अगर ((cht_rt5645_quirk & CHT_RT5645_SSP0_AIF1) ||
	    (cht_rt5645_quirk & CHT_RT5645_SSP0_AIF2))
		cht_dailink[dai_index].cpus->dai_name = "ssp0-port";

	/* override plaक्रमm name, अगर required */
	platक्रमm_name = mach->mach_params.platक्रमm;

	ret_val = snd_soc_fixup_dai_links_platक्रमm_name(card,
							platक्रमm_name);
	अगर (ret_val)
		वापस ret_val;

	अगर (cht_rt5645_quirk & CHT_RT5645_PMC_PLT_CLK_0)
		mclk_name = "pmc_plt_clk_0";
	अन्यथा
		mclk_name = "pmc_plt_clk_3";

	drv->mclk = devm_clk_get(&pdev->dev, mclk_name);
	अगर (IS_ERR(drv->mclk)) अणु
		dev_err(&pdev->dev, "Failed to get MCLK from %s: %ld\n",
			mclk_name, PTR_ERR(drv->mclk));
		वापस PTR_ERR(drv->mclk);
	पूर्ण

	snd_soc_card_set_drvdata(card, drv);

	sof_parent = snd_soc_acpi_sof_parent(&pdev->dev);

	/* set card and driver name */
	अगर (sof_parent) अणु
		snd_soc_card_chtrt5645.name = SOF_CARD_RT5645_NAME;
		snd_soc_card_chtrt5645.driver_name = SOF_DRIVER_NAME;
		snd_soc_card_chtrt5650.name = SOF_CARD_RT5650_NAME;
		snd_soc_card_chtrt5650.driver_name = SOF_DRIVER_NAME;
	पूर्ण अन्यथा अणु
		snd_soc_card_chtrt5645.name = CARD_RT5645_NAME;
		snd_soc_card_chtrt5645.driver_name = DRIVER_NAME;
		snd_soc_card_chtrt5650.name = CARD_RT5650_NAME;
		snd_soc_card_chtrt5650.driver_name = DRIVER_NAME;
	पूर्ण

	/* set pm ops */
	अगर (sof_parent)
		pdev->dev.driver->pm = &snd_soc_pm_ops;

	ret_val = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret_val) अणु
		dev_err(&pdev->dev,
			"snd_soc_register_card failed %d\n", ret_val);
		वापस ret_val;
	पूर्ण
	platक्रमm_set_drvdata(pdev, card);
	वापस ret_val;
पूर्ण

अटल काष्ठा platक्रमm_driver snd_cht_mc_driver = अणु
	.driver = अणु
		.name = "cht-bsw-rt5645",
	पूर्ण,
	.probe = snd_cht_mc_probe,
पूर्ण;

module_platक्रमm_driver(snd_cht_mc_driver)

MODULE_DESCRIPTION("ASoC Intel(R) Braswell Machine driver");
MODULE_AUTHOR("Fang, Yang A,N,Harshapriya");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:cht-bsw-rt5645");
