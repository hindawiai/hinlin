<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  byt_cr_dpcm_rt5640.c - ASoc Machine driver क्रम Intel Byt CR platक्रमm
 *
 *  Copyright (C) 2014 Intel Corp
 *  Author: Subhransu S. Prusty <subhransu.s.prusty@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/dmi.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>
#समावेश <sound/soc-acpi.h>
#समावेश <dt-bindings/sound/rt5640.h>
#समावेश "../../codecs/rt5640.h"
#समावेश "../atom/sst-atom-controls.h"
#समावेश "../common/soc-intel-quirks.h"

क्रमागत अणु
	BYT_RT5640_DMIC1_MAP,
	BYT_RT5640_DMIC2_MAP,
	BYT_RT5640_IN1_MAP,
	BYT_RT5640_IN3_MAP,
	BYT_RT5640_NO_INTERNAL_MIC_MAP,
पूर्ण;

क्रमागत अणु
	BYT_RT5640_JD_SRC_GPIO1		= (RT5640_JD_SRC_GPIO1 << 4),
	BYT_RT5640_JD_SRC_JD1_IN4P	= (RT5640_JD_SRC_JD1_IN4P << 4),
	BYT_RT5640_JD_SRC_JD2_IN4N	= (RT5640_JD_SRC_JD2_IN4N << 4),
	BYT_RT5640_JD_SRC_GPIO2		= (RT5640_JD_SRC_GPIO2 << 4),
	BYT_RT5640_JD_SRC_GPIO3		= (RT5640_JD_SRC_GPIO3 << 4),
	BYT_RT5640_JD_SRC_GPIO4		= (RT5640_JD_SRC_GPIO4 << 4),
पूर्ण;

क्रमागत अणु
	BYT_RT5640_OVCD_TH_600UA	= (6 << 8),
	BYT_RT5640_OVCD_TH_1500UA	= (15 << 8),
	BYT_RT5640_OVCD_TH_2000UA	= (20 << 8),
पूर्ण;

क्रमागत अणु
	BYT_RT5640_OVCD_SF_0P5		= (RT5640_OVCD_SF_0P5 << 13),
	BYT_RT5640_OVCD_SF_0P75		= (RT5640_OVCD_SF_0P75 << 13),
	BYT_RT5640_OVCD_SF_1P0		= (RT5640_OVCD_SF_1P0 << 13),
	BYT_RT5640_OVCD_SF_1P5		= (RT5640_OVCD_SF_1P5 << 13),
पूर्ण;

#घोषणा BYT_RT5640_MAP(quirk)		((quirk) &  GENMASK(3, 0))
#घोषणा BYT_RT5640_JDSRC(quirk)		(((quirk) & GENMASK(7, 4)) >> 4)
#घोषणा BYT_RT5640_OVCD_TH(quirk)	(((quirk) & GENMASK(12, 8)) >> 8)
#घोषणा BYT_RT5640_OVCD_SF(quirk)	(((quirk) & GENMASK(14, 13)) >> 13)
#घोषणा BYT_RT5640_JD_NOT_INV		BIT(16)
#घोषणा BYT_RT5640_MONO_SPEAKER		BIT(17)
#घोषणा BYT_RT5640_DIFF_MIC		BIT(18) /* शेष is single-ended */
#घोषणा BYT_RT5640_SSP2_AIF2		BIT(19) /* शेष is using AIF1  */
#घोषणा BYT_RT5640_SSP0_AIF1		BIT(20)
#घोषणा BYT_RT5640_SSP0_AIF2		BIT(21)
#घोषणा BYT_RT5640_MCLK_EN		BIT(22)
#घोषणा BYT_RT5640_MCLK_25MHZ		BIT(23)
#घोषणा BYT_RT5640_NO_SPEAKERS		BIT(24)

#घोषणा BYTCR_INPUT_DEFAULTS				\
	(BYT_RT5640_IN3_MAP |				\
	 BYT_RT5640_JD_SRC_JD1_IN4P |			\
	 BYT_RT5640_OVCD_TH_2000UA |			\
	 BYT_RT5640_OVCD_SF_0P75 |			\
	 BYT_RT5640_DIFF_MIC)

/* in-dअगरf or dmic-pin + jdsrc + ovcd-th + -sf + jd-inv + terminating entry */
#घोषणा MAX_NO_PROPS 6

काष्ठा byt_rt5640_निजी अणु
	काष्ठा snd_soc_jack jack;
	काष्ठा clk *mclk;
पूर्ण;
अटल bool is_bytcr;

अटल अचिन्हित दीर्घ byt_rt5640_quirk = BYT_RT5640_MCLK_EN;
अटल पूर्णांक quirk_override = -1;
module_param_named(quirk, quirk_override, पूर्णांक, 0444);
MODULE_PARM_DESC(quirk, "Board-specific quirk override");

अटल व्योम log_quirks(काष्ठा device *dev)
अणु
	पूर्णांक map;
	bool has_mclk = false;
	bool has_ssp0 = false;
	bool has_ssp0_aअगर1 = false;
	bool has_ssp0_aअगर2 = false;
	bool has_ssp2_aअगर2 = false;

	map = BYT_RT5640_MAP(byt_rt5640_quirk);
	चयन (map) अणु
	हाल BYT_RT5640_DMIC1_MAP:
		dev_info(dev, "quirk DMIC1_MAP enabled\n");
		अवरोध;
	हाल BYT_RT5640_DMIC2_MAP:
		dev_info(dev, "quirk DMIC2_MAP enabled\n");
		अवरोध;
	हाल BYT_RT5640_IN1_MAP:
		dev_info(dev, "quirk IN1_MAP enabled\n");
		अवरोध;
	हाल BYT_RT5640_IN3_MAP:
		dev_info(dev, "quirk IN3_MAP enabled\n");
		अवरोध;
	हाल BYT_RT5640_NO_INTERNAL_MIC_MAP:
		dev_info(dev, "quirk NO_INTERNAL_MIC_MAP enabled\n");
		अवरोध;
	शेष:
		dev_err(dev, "quirk map 0x%x is not supported, microphone input will not work\n", map);
		अवरोध;
	पूर्ण
	अगर (BYT_RT5640_JDSRC(byt_rt5640_quirk)) अणु
		dev_info(dev, "quirk realtek,jack-detect-source %ld\n",
			 BYT_RT5640_JDSRC(byt_rt5640_quirk));
		dev_info(dev, "quirk realtek,over-current-threshold-microamp %ld\n",
			 BYT_RT5640_OVCD_TH(byt_rt5640_quirk) * 100);
		dev_info(dev, "quirk realtek,over-current-scale-factor %ld\n",
			 BYT_RT5640_OVCD_SF(byt_rt5640_quirk));
	पूर्ण
	अगर (byt_rt5640_quirk & BYT_RT5640_JD_NOT_INV)
		dev_info(dev, "quirk JD_NOT_INV enabled\n");
	अगर (byt_rt5640_quirk & BYT_RT5640_MONO_SPEAKER)
		dev_info(dev, "quirk MONO_SPEAKER enabled\n");
	अगर (byt_rt5640_quirk & BYT_RT5640_NO_SPEAKERS)
		dev_info(dev, "quirk NO_SPEAKERS enabled\n");
	अगर (byt_rt5640_quirk & BYT_RT5640_DIFF_MIC)
		dev_info(dev, "quirk DIFF_MIC enabled\n");
	अगर (byt_rt5640_quirk & BYT_RT5640_SSP0_AIF1) अणु
		dev_info(dev, "quirk SSP0_AIF1 enabled\n");
		has_ssp0 = true;
		has_ssp0_aअगर1 = true;
	पूर्ण
	अगर (byt_rt5640_quirk & BYT_RT5640_SSP0_AIF2) अणु
		dev_info(dev, "quirk SSP0_AIF2 enabled\n");
		has_ssp0 = true;
		has_ssp0_aअगर2 = true;
	पूर्ण
	अगर (byt_rt5640_quirk & BYT_RT5640_SSP2_AIF2) अणु
		dev_info(dev, "quirk SSP2_AIF2 enabled\n");
		has_ssp2_aअगर2 = true;
	पूर्ण
	अगर (is_bytcr && !has_ssp0)
		dev_err(dev, "Invalid routing, bytcr detected but no SSP0-based quirk, audio cannot work with SSP2 on bytcr\n");
	अगर (has_ssp0_aअगर1 && has_ssp0_aअगर2)
		dev_err(dev, "Invalid routing, SSP0 cannot be connected to both AIF1 and AIF2\n");
	अगर (has_ssp0 && has_ssp2_aअगर2)
		dev_err(dev, "Invalid routing, cannot have both SSP0 and SSP2 connected to codec\n");

	अगर (byt_rt5640_quirk & BYT_RT5640_MCLK_EN) अणु
		dev_info(dev, "quirk MCLK_EN enabled\n");
		has_mclk = true;
	पूर्ण
	अगर (byt_rt5640_quirk & BYT_RT5640_MCLK_25MHZ) अणु
		अगर (has_mclk)
			dev_info(dev, "quirk MCLK_25MHZ enabled\n");
		अन्यथा
			dev_err(dev, "quirk MCLK_25MHZ enabled but quirk MCLK not selected, will be ignored\n");
	पूर्ण
पूर्ण

अटल पूर्णांक byt_rt5640_prepare_and_enable_pll1(काष्ठा snd_soc_dai *codec_dai,
					      पूर्णांक rate)
अणु
	पूर्णांक ret;

	/* Configure the PLL beक्रमe selecting it */
	अगर (!(byt_rt5640_quirk & BYT_RT5640_MCLK_EN)) अणु
		/* use bitघड़ी as PLL input */
		अगर ((byt_rt5640_quirk & BYT_RT5640_SSP0_AIF1) ||
		    (byt_rt5640_quirk & BYT_RT5640_SSP0_AIF2)) अणु
			/* 2x16 bit slots on SSP0 */
			ret = snd_soc_dai_set_pll(codec_dai, 0,
						  RT5640_PLL1_S_BCLK1,
						  rate * 32, rate * 512);
		पूर्ण अन्यथा अणु
			/* 2x15 bit slots on SSP2 */
			ret = snd_soc_dai_set_pll(codec_dai, 0,
						  RT5640_PLL1_S_BCLK1,
						  rate * 50, rate * 512);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (byt_rt5640_quirk & BYT_RT5640_MCLK_25MHZ) अणु
			ret = snd_soc_dai_set_pll(codec_dai, 0,
						  RT5640_PLL1_S_MCLK,
						  25000000, rate * 512);
		पूर्ण अन्यथा अणु
			ret = snd_soc_dai_set_pll(codec_dai, 0,
						  RT5640_PLL1_S_MCLK,
						  19200000, rate * 512);
		पूर्ण
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(codec_dai->component->dev, "can't set pll: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(codec_dai, RT5640_SCLK_S_PLL1,
				     rate * 512, SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(codec_dai->component->dev, "can't set clock %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा BYT_CODEC_DAI1	"rt5640-aif1"
#घोषणा BYT_CODEC_DAI2	"rt5640-aif2"

अटल पूर्णांक platक्रमm_घड़ी_control(काष्ठा snd_soc_dapm_widget *w,
				  काष्ठा snd_kcontrol *k, पूर्णांक  event)
अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा snd_soc_dai *codec_dai;
	काष्ठा byt_rt5640_निजी *priv = snd_soc_card_get_drvdata(card);
	पूर्णांक ret;

	codec_dai = snd_soc_card_get_codec_dai(card, BYT_CODEC_DAI1);
	अगर (!codec_dai)
		codec_dai = snd_soc_card_get_codec_dai(card, BYT_CODEC_DAI2);

	अगर (!codec_dai) अणु
		dev_err(card->dev,
			"Codec dai not found; Unable to set platform clock\n");
		वापस -EIO;
	पूर्ण

	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		अगर (byt_rt5640_quirk & BYT_RT5640_MCLK_EN) अणु
			ret = clk_prepare_enable(priv->mclk);
			अगर (ret < 0) अणु
				dev_err(card->dev,
					"could not configure MCLK state\n");
				वापस ret;
			पूर्ण
		पूर्ण
		ret = byt_rt5640_prepare_and_enable_pll1(codec_dai, 48000);
	पूर्ण अन्यथा अणु
		/*
		 * Set codec घड़ी source to पूर्णांकernal घड़ी beक्रमe
		 * turning off the platक्रमm घड़ी. Codec needs घड़ी
		 * क्रम Jack detection and button press
		 */
		ret = snd_soc_dai_set_sysclk(codec_dai, RT5640_SCLK_S_RCCLK,
					     48000 * 512,
					     SND_SOC_CLOCK_IN);
		अगर (!ret) अणु
			अगर (byt_rt5640_quirk & BYT_RT5640_MCLK_EN)
				clk_disable_unprepare(priv->mclk);
		पूर्ण
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(card->dev, "can't set codec sysclk: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget byt_rt5640_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Internal Mic", शून्य),
	SND_SOC_DAPM_SPK("Speaker", शून्य),
	SND_SOC_DAPM_SUPPLY("Platform Clock", SND_SOC_NOPM, 0, 0,
			    platक्रमm_घड़ी_control, SND_SOC_DAPM_PRE_PMU |
			    SND_SOC_DAPM_POST_PMD),

पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_rt5640_audio_map[] = अणु
	अणु"Headphone", शून्य, "Platform Clock"पूर्ण,
	अणु"Headset Mic", शून्य, "Platform Clock"पूर्ण,
	अणु"Internal Mic", शून्य, "Platform Clock"पूर्ण,
	अणु"Speaker", शून्य, "Platform Clock"पूर्ण,

	अणु"Headset Mic", शून्य, "MICBIAS1"पूर्ण,
	अणु"IN2P", शून्य, "Headset Mic"पूर्ण,
	अणु"Headphone", शून्य, "HPOL"पूर्ण,
	अणु"Headphone", शून्य, "HPOR"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_rt5640_पूर्णांकmic_dmic1_map[] = अणु
	अणु"DMIC1", शून्य, "Internal Mic"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_rt5640_पूर्णांकmic_dmic2_map[] = अणु
	अणु"DMIC2", शून्य, "Internal Mic"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_rt5640_पूर्णांकmic_in1_map[] = अणु
	अणु"Internal Mic", शून्य, "MICBIAS1"पूर्ण,
	अणु"IN1P", शून्य, "Internal Mic"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_rt5640_पूर्णांकmic_in3_map[] = अणु
	अणु"Internal Mic", शून्य, "MICBIAS1"पूर्ण,
	अणु"IN3P", शून्य, "Internal Mic"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_rt5640_ssp2_aअगर1_map[] = अणु
	अणु"ssp2 Tx", शून्य, "codec_out0"पूर्ण,
	अणु"ssp2 Tx", शून्य, "codec_out1"पूर्ण,
	अणु"codec_in0", शून्य, "ssp2 Rx"पूर्ण,
	अणु"codec_in1", शून्य, "ssp2 Rx"पूर्ण,

	अणु"AIF1 Playback", शून्य, "ssp2 Tx"पूर्ण,
	अणु"ssp2 Rx", शून्य, "AIF1 Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_rt5640_ssp2_aअगर2_map[] = अणु
	अणु"ssp2 Tx", शून्य, "codec_out0"पूर्ण,
	अणु"ssp2 Tx", शून्य, "codec_out1"पूर्ण,
	अणु"codec_in0", शून्य, "ssp2 Rx"पूर्ण,
	अणु"codec_in1", शून्य, "ssp2 Rx"पूर्ण,

	अणु"AIF2 Playback", शून्य, "ssp2 Tx"पूर्ण,
	अणु"ssp2 Rx", शून्य, "AIF2 Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_rt5640_ssp0_aअगर1_map[] = अणु
	अणु"ssp0 Tx", शून्य, "modem_out"पूर्ण,
	अणु"modem_in", शून्य, "ssp0 Rx"पूर्ण,

	अणु"AIF1 Playback", शून्य, "ssp0 Tx"पूर्ण,
	अणु"ssp0 Rx", शून्य, "AIF1 Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_rt5640_ssp0_aअगर2_map[] = अणु
	अणु"ssp0 Tx", शून्य, "modem_out"पूर्ण,
	अणु"modem_in", शून्य, "ssp0 Rx"पूर्ण,

	अणु"AIF2 Playback", शून्य, "ssp0 Tx"पूर्ण,
	अणु"ssp0 Rx", शून्य, "AIF2 Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_rt5640_stereo_spk_map[] = अणु
	अणु"Speaker", शून्य, "SPOLP"पूर्ण,
	अणु"Speaker", शून्य, "SPOLN"पूर्ण,
	अणु"Speaker", शून्य, "SPORP"पूर्ण,
	अणु"Speaker", शून्य, "SPORN"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_rt5640_mono_spk_map[] = अणु
	अणु"Speaker", शून्य, "SPOLP"पूर्ण,
	अणु"Speaker", शून्य, "SPOLN"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new byt_rt5640_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Internal Mic"),
	SOC_DAPM_PIN_SWITCH("Speaker"),
पूर्ण;

अटल काष्ठा snd_soc_jack_pin rt5640_pins[] = अणु
	अणु
		.pin	= "Headphone",
		.mask	= SND_JACK_HEADPHONE,
	पूर्ण,
	अणु
		.pin	= "Headset Mic",
		.mask	= SND_JACK_MICROPHONE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक byt_rt5640_aअगर1_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *dai = asoc_rtd_to_codec(rtd, 0);

	वापस byt_rt5640_prepare_and_enable_pll1(dai, params_rate(params));
पूर्ण

/* Please keep this list alphabetically sorted */
अटल स्थिर काष्ठा dmi_प्रणाली_id byt_rt5640_quirk_table[] = अणु
	अणु	/* Acer Iconia Tab 8 W1-810 */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Iconia W1-810"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_DMIC1_MAP |
					BYT_RT5640_JD_SRC_JD1_IN4P |
					BYT_RT5640_OVCD_TH_1500UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* Acer One 10 S1002 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "One S1002"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_IN1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_DIFF_MIC |
					BYT_RT5640_SSP0_AIF2 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire SW5-012"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_DMIC1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "ARCHOS"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "ARCHOS 80 Cesium"),
		पूर्ण,
		.driver_data = (व्योम *)(BYTCR_INPUT_DEFAULTS |
					BYT_RT5640_MONO_SPEAKER |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "ARCHOS"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "ARCHOS 140 CESIUM"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_IN1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "ME176C"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_IN1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "T100TA"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_IN1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "T100TAF"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_IN1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_MONO_SPEAKER |
					BYT_RT5640_DIFF_MIC |
					BYT_RT5640_SSP0_AIF2 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* Chuwi Vi8 (CWI506) */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "i86"),
			/* The above are too generic, also match BIOS info */
			DMI_MATCH(DMI_BIOS_VERSION, "CHUWI.D86JLBNR"),
		पूर्ण,
		.driver_data = (व्योम *)(BYTCR_INPUT_DEFAULTS |
					BYT_RT5640_MONO_SPEAKER |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु
		/* Chuwi Vi10 (CWI505) */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Hampoo"),
			DMI_MATCH(DMI_BOARD_NAME, "BYT-PF02"),
			DMI_MATCH(DMI_SYS_VENDOR, "ilife"),
			DMI_MATCH(DMI_PRODUCT_NAME, "S165"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_IN1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_DIFF_MIC |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु
		/* Chuwi Hi8 (CWI509) */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Hampoo"),
			DMI_MATCH(DMI_BOARD_NAME, "BYT-PA03C"),
			DMI_MATCH(DMI_SYS_VENDOR, "ilife"),
			DMI_MATCH(DMI_PRODUCT_NAME, "S806"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_IN1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_MONO_SPEAKER |
					BYT_RT5640_DIFF_MIC |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Circuitco"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Minnowboard Max B3 PLATFORM"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_DMIC1_MAP),
	पूर्ण,
	अणु	/* Connect Tablet 9 */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Connect"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Tablet 9"),
		पूर्ण,
		.driver_data = (व्योम *)(BYTCR_INPUT_DEFAULTS |
					BYT_RT5640_MONO_SPEAKER |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Venue 8 Pro 5830"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_DMIC1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_MONO_SPEAKER |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* Estar Beauty HD MID 7316R */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Estar"),
			DMI_MATCH(DMI_PRODUCT_NAME, "eSTAR BEAUTY HD Intel Quad core"),
		पूर्ण,
		.driver_data = (व्योम *)(BYTCR_INPUT_DEFAULTS |
					BYT_RT5640_MONO_SPEAKER |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* Glavey TM800A550L */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "AMI Corporation"),
			DMI_MATCH(DMI_BOARD_NAME, "Aptio CRB"),
			/* Above strings are too generic, also match on BIOS version */
			DMI_MATCH(DMI_BIOS_VERSION, "ZY-8-BI-PX4S70VTR400-X423B-005-D"),
		पूर्ण,
		.driver_data = (व्योम *)(BYTCR_INPUT_DEFAULTS |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "HP ElitePad 1000 G2"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_IN1_MAP |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* HP Pavilion x2 10-k0XX, 10-n0XX */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HP Pavilion x2 Detachable"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_DMIC1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_1500UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* HP Pavilion x2 10-p0XX */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HP x2 Detachable 10-p0XX"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_DMIC1_MAP |
					BYT_RT5640_JD_SRC_JD1_IN4P |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* HP Stream 7 */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "HP Stream 7 Tablet"),
		पूर्ण,
		.driver_data = (व्योम *)(BYTCR_INPUT_DEFAULTS |
					BYT_RT5640_MONO_SPEAKER |
					BYT_RT5640_JD_NOT_INV |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* I.T.Works TW891 */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "To be filled by O.E.M."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "TW891"),
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "To be filled by O.E.M."),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "TW891"),
		पूर्ण,
		.driver_data = (व्योम *)(BYTCR_INPUT_DEFAULTS |
					BYT_RT5640_MONO_SPEAKER |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* Lamina I8270 / T701BR.SE */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "Lamina"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "T701BR.SE"),
		पूर्ण,
		.driver_data = (व्योम *)(BYTCR_INPUT_DEFAULTS |
					BYT_RT5640_MONO_SPEAKER |
					BYT_RT5640_JD_NOT_INV |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* Lenovo Miix 2 8 */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "20326"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "Hiking"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_DMIC1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_MONO_SPEAKER |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* Lenovo Miix 3-830 */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_EXACT_MATCH(DMI_PRODUCT_VERSION, "Lenovo MIIX 3-830"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_IN1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_MONO_SPEAKER |
					BYT_RT5640_DIFF_MIC |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* Linx Linx7 tablet */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "LINX"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "LINX7"),
		पूर्ण,
		.driver_data = (व्योम *)(BYTCR_INPUT_DEFAULTS |
					BYT_RT5640_MONO_SPEAKER |
					BYT_RT5640_JD_NOT_INV |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* Mele PCG03 Mini PC */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "Mini PC"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "Mini PC"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_NO_INTERNAL_MIC_MAP |
					BYT_RT5640_NO_SPEAKERS |
					BYT_RT5640_SSP0_AIF1),
	पूर्ण,
	अणु	/* MPMAN Converter 9, similar hw as the I.T.Works TW891 2-in-1 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MPMAN"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Converter9"),
		पूर्ण,
		.driver_data = (व्योम *)(BYTCR_INPUT_DEFAULTS |
					BYT_RT5640_MONO_SPEAKER |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु
		/* MPMAN MPWIN895CL */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "MPMAN"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "MPWIN8900CL"),
		पूर्ण,
		.driver_data = (व्योम *)(BYTCR_INPUT_DEFAULTS |
					BYT_RT5640_MONO_SPEAKER |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* MSI S100 tablet */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Micro-Star International Co., Ltd."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "S100"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_IN1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_MONO_SPEAKER |
					BYT_RT5640_DIFF_MIC |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* Nuvison/TMax TM800W560 */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "TMAX"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "TM800W560L"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_IN1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_JD_NOT_INV |
					BYT_RT5640_DIFF_MIC |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* Onda v975w */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "AMI Corporation"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "Aptio CRB"),
			/* The above are too generic, also match BIOS info */
			DMI_EXACT_MATCH(DMI_BIOS_VERSION, "5.6.5"),
			DMI_EXACT_MATCH(DMI_BIOS_DATE, "07/25/2014"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_IN1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_DIFF_MIC |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* Pipo W4 */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "AMI Corporation"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "Aptio CRB"),
			/* The above are too generic, also match BIOS info */
			DMI_MATCH(DMI_BIOS_VERSION, "V8L_WIN32_CHIPHD"),
		पूर्ण,
		.driver_data = (व्योम *)(BYTCR_INPUT_DEFAULTS |
					BYT_RT5640_MONO_SPEAKER |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* Poपूर्णांक of View Mobii TAB-P800W (V2.0) */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "AMI Corporation"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "Aptio CRB"),
			/* The above are too generic, also match BIOS info */
			DMI_EXACT_MATCH(DMI_BIOS_VERSION, "3BAIR1014"),
			DMI_EXACT_MATCH(DMI_BIOS_DATE, "10/24/2014"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_IN1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_MONO_SPEAKER |
					BYT_RT5640_DIFF_MIC |
					BYT_RT5640_SSP0_AIF2 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* Poपूर्णांक of View Mobii TAB-P800W (V2.1) */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "AMI Corporation"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "Aptio CRB"),
			/* The above are too generic, also match BIOS info */
			DMI_EXACT_MATCH(DMI_BIOS_VERSION, "3BAIR1013"),
			DMI_EXACT_MATCH(DMI_BIOS_DATE, "08/22/2014"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_IN1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_MONO_SPEAKER |
					BYT_RT5640_DIFF_MIC |
					BYT_RT5640_SSP0_AIF2 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* Poपूर्णांक of View Mobii TAB-P1005W-232 (V2.0) */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "POV"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "I102A"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_IN1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_DIFF_MIC |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु
		/* Prowise PT301 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Prowise"),
			DMI_MATCH(DMI_PRODUCT_NAME, "PT301"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_IN1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_DIFF_MIC |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु
		/* Teclast X89 */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "TECLAST"),
			DMI_MATCH(DMI_BOARD_NAME, "tPAD"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_IN3_MAP |
					BYT_RT5640_JD_SRC_JD1_IN4P |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_1P0 |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* Toshiba Satellite Click Mini L9W-B */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "SATELLITE Click Mini L9W-B"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_DMIC1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_1500UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_SSP0_AIF1 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* Toshiba Encore WT8-A */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "TOSHIBA WT8-A"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_DMIC1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_JD_NOT_INV |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* Toshiba Encore WT10-A */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "TOSHIBA WT10-A-103"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_DMIC1_MAP |
					BYT_RT5640_JD_SRC_JD1_IN4P |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_SSP0_AIF2 |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* Voyo Winpad A15 */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "AMI Corporation"),
			DMI_MATCH(DMI_BOARD_NAME, "Aptio CRB"),
			/* Above strings are too generic, also match on BIOS date */
			DMI_MATCH(DMI_BIOS_DATE, "11/20/2014"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5640_IN1_MAP |
					BYT_RT5640_JD_SRC_JD2_IN4N |
					BYT_RT5640_OVCD_TH_2000UA |
					BYT_RT5640_OVCD_SF_0P75 |
					BYT_RT5640_DIFF_MIC |
					BYT_RT5640_MCLK_EN),
	पूर्ण,
	अणु	/* Catch-all क्रम generic Insyde tablets, must be last */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Insyde"),
		पूर्ण,
		.driver_data = (व्योम *)(BYTCR_INPUT_DEFAULTS |
					BYT_RT5640_MCLK_EN |
					BYT_RT5640_SSP0_AIF1),

	पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * Note this MUST be called beक्रमe snd_soc_रेजिस्टर_card(), so that the props
 * are in place beक्रमe the codec component driver's probe function parses them.
 */
अटल पूर्णांक byt_rt5640_add_codec_device_props(स्थिर अक्षर *i2c_dev_name)
अणु
	काष्ठा property_entry props[MAX_NO_PROPS] = अणुपूर्ण;
	काष्ठा device *i2c_dev;
	पूर्णांक ret, cnt = 0;

	i2c_dev = bus_find_device_by_name(&i2c_bus_type, शून्य, i2c_dev_name);
	अगर (!i2c_dev)
		वापस -EPROBE_DEFER;

	चयन (BYT_RT5640_MAP(byt_rt5640_quirk)) अणु
	हाल BYT_RT5640_DMIC1_MAP:
		props[cnt++] = PROPERTY_ENTRY_U32("realtek,dmic1-data-pin",
						  RT5640_DMIC1_DATA_PIN_IN1P);
		अवरोध;
	हाल BYT_RT5640_DMIC2_MAP:
		props[cnt++] = PROPERTY_ENTRY_U32("realtek,dmic2-data-pin",
						  RT5640_DMIC2_DATA_PIN_IN1N);
		अवरोध;
	हाल BYT_RT5640_IN1_MAP:
		अगर (byt_rt5640_quirk & BYT_RT5640_DIFF_MIC)
			props[cnt++] =
				PROPERTY_ENTRY_BOOL("realtek,in1-differential");
		अवरोध;
	हाल BYT_RT5640_IN3_MAP:
		अगर (byt_rt5640_quirk & BYT_RT5640_DIFF_MIC)
			props[cnt++] =
				PROPERTY_ENTRY_BOOL("realtek,in3-differential");
		अवरोध;
	पूर्ण

	अगर (BYT_RT5640_JDSRC(byt_rt5640_quirk)) अणु
		props[cnt++] = PROPERTY_ENTRY_U32(
				    "realtek,jack-detect-source",
				    BYT_RT5640_JDSRC(byt_rt5640_quirk));

		props[cnt++] = PROPERTY_ENTRY_U32(
				    "realtek,over-current-threshold-microamp",
				    BYT_RT5640_OVCD_TH(byt_rt5640_quirk) * 100);

		props[cnt++] = PROPERTY_ENTRY_U32(
				    "realtek,over-current-scale-factor",
				    BYT_RT5640_OVCD_SF(byt_rt5640_quirk));
	पूर्ण

	अगर (byt_rt5640_quirk & BYT_RT5640_JD_NOT_INV)
		props[cnt++] = PROPERTY_ENTRY_BOOL("realtek,jack-detect-not-inverted");

	ret = device_add_properties(i2c_dev, props);
	put_device(i2c_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक byt_rt5640_init(काष्ठा snd_soc_pcm_runसमय *runसमय)
अणु
	काष्ठा snd_soc_card *card = runसमय->card;
	काष्ठा byt_rt5640_निजी *priv = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(runसमय, 0)->component;
	स्थिर काष्ठा snd_soc_dapm_route *custom_map = शून्य;
	पूर्णांक num_routes = 0;
	पूर्णांक ret;

	card->dapm.idle_bias_off = true;

	/* Start with RC clk क्रम jack-detect (we disable MCLK below) */
	अगर (byt_rt5640_quirk & BYT_RT5640_MCLK_EN)
		snd_soc_component_update_bits(component, RT5640_GLB_CLK,
			RT5640_SCLK_SRC_MASK, RT5640_SCLK_SRC_RCCLK);

	rt5640_sel_asrc_clk_src(component,
				RT5640_DA_STEREO_FILTER |
				RT5640_DA_MONO_L_FILTER	|
				RT5640_DA_MONO_R_FILTER	|
				RT5640_AD_STEREO_FILTER	|
				RT5640_AD_MONO_L_FILTER	|
				RT5640_AD_MONO_R_FILTER,
				RT5640_CLK_SEL_ASRC);

	ret = snd_soc_add_card_controls(card, byt_rt5640_controls,
					ARRAY_SIZE(byt_rt5640_controls));
	अगर (ret) अणु
		dev_err(card->dev, "unable to add card controls\n");
		वापस ret;
	पूर्ण

	चयन (BYT_RT5640_MAP(byt_rt5640_quirk)) अणु
	हाल BYT_RT5640_IN1_MAP:
		custom_map = byt_rt5640_पूर्णांकmic_in1_map;
		num_routes = ARRAY_SIZE(byt_rt5640_पूर्णांकmic_in1_map);
		अवरोध;
	हाल BYT_RT5640_IN3_MAP:
		custom_map = byt_rt5640_पूर्णांकmic_in3_map;
		num_routes = ARRAY_SIZE(byt_rt5640_पूर्णांकmic_in3_map);
		अवरोध;
	हाल BYT_RT5640_DMIC1_MAP:
		custom_map = byt_rt5640_पूर्णांकmic_dmic1_map;
		num_routes = ARRAY_SIZE(byt_rt5640_पूर्णांकmic_dmic1_map);
		अवरोध;
	हाल BYT_RT5640_DMIC2_MAP:
		custom_map = byt_rt5640_पूर्णांकmic_dmic2_map;
		num_routes = ARRAY_SIZE(byt_rt5640_पूर्णांकmic_dmic2_map);
		अवरोध;
	पूर्ण

	ret = snd_soc_dapm_add_routes(&card->dapm, custom_map, num_routes);
	अगर (ret)
		वापस ret;

	अगर (byt_rt5640_quirk & BYT_RT5640_SSP2_AIF2) अणु
		ret = snd_soc_dapm_add_routes(&card->dapm,
					byt_rt5640_ssp2_aअगर2_map,
					ARRAY_SIZE(byt_rt5640_ssp2_aअगर2_map));
	पूर्ण अन्यथा अगर (byt_rt5640_quirk & BYT_RT5640_SSP0_AIF1) अणु
		ret = snd_soc_dapm_add_routes(&card->dapm,
					byt_rt5640_ssp0_aअगर1_map,
					ARRAY_SIZE(byt_rt5640_ssp0_aअगर1_map));
	पूर्ण अन्यथा अगर (byt_rt5640_quirk & BYT_RT5640_SSP0_AIF2) अणु
		ret = snd_soc_dapm_add_routes(&card->dapm,
					byt_rt5640_ssp0_aअगर2_map,
					ARRAY_SIZE(byt_rt5640_ssp0_aअगर2_map));
	पूर्ण अन्यथा अणु
		ret = snd_soc_dapm_add_routes(&card->dapm,
					byt_rt5640_ssp2_aअगर1_map,
					ARRAY_SIZE(byt_rt5640_ssp2_aअगर1_map));
	पूर्ण
	अगर (ret)
		वापस ret;

	अगर (byt_rt5640_quirk & BYT_RT5640_MONO_SPEAKER) अणु
		ret = snd_soc_dapm_add_routes(&card->dapm,
					byt_rt5640_mono_spk_map,
					ARRAY_SIZE(byt_rt5640_mono_spk_map));
	पूर्ण अन्यथा अगर (!(byt_rt5640_quirk & BYT_RT5640_NO_SPEAKERS)) अणु
		ret = snd_soc_dapm_add_routes(&card->dapm,
					byt_rt5640_stereo_spk_map,
					ARRAY_SIZE(byt_rt5640_stereo_spk_map));
	पूर्ण
	अगर (ret)
		वापस ret;

	अगर (byt_rt5640_quirk & BYT_RT5640_MCLK_EN) अणु
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
		ret = clk_prepare_enable(priv->mclk);
		अगर (!ret)
			clk_disable_unprepare(priv->mclk);

		अगर (byt_rt5640_quirk & BYT_RT5640_MCLK_25MHZ)
			ret = clk_set_rate(priv->mclk, 25000000);
		अन्यथा
			ret = clk_set_rate(priv->mclk, 19200000);

		अगर (ret) अणु
			dev_err(card->dev, "unable to set MCLK rate\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (BYT_RT5640_JDSRC(byt_rt5640_quirk)) अणु
		ret = snd_soc_card_jack_new(card, "Headset",
					    SND_JACK_HEADSET | SND_JACK_BTN_0,
					    &priv->jack, rt5640_pins,
					    ARRAY_SIZE(rt5640_pins));
		अगर (ret) अणु
			dev_err(card->dev, "Jack creation failed %d\n", ret);
			वापस ret;
		पूर्ण
		snd_jack_set_key(priv->jack.jack, SND_JACK_BTN_0,
				 KEY_PLAYPAUSE);
		snd_soc_component_set_jack(component, &priv->jack, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक byt_rt5640_codec_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
			    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
			SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *channels = hw_param_पूर्णांकerval(params,
						SNDRV_PCM_HW_PARAM_CHANNELS);
	पूर्णांक ret, bits;

	/* The DSP will covert the FE rate to 48k, stereo */
	rate->min = rate->max = 48000;
	channels->min = channels->max = 2;

	अगर ((byt_rt5640_quirk & BYT_RT5640_SSP0_AIF1) ||
	    (byt_rt5640_quirk & BYT_RT5640_SSP0_AIF2)) अणु
		/* set SSP0 to 16-bit */
		params_set_क्रमmat(params, SNDRV_PCM_FORMAT_S16_LE);
		bits = 16;
	पूर्ण अन्यथा अणु
		/* set SSP2 to 24-bit */
		params_set_क्रमmat(params, SNDRV_PCM_FORMAT_S24_LE);
		bits = 24;
	पूर्ण

	/*
	 * Default mode क्रम SSP configuration is TDM 4 slot, override config
	 * with explicit setting to I2S 2ch. The word length is set with
	 * dai_set_tdm_slot() since there is no other API exposed
	 */
	ret = snd_soc_dai_set_fmt(asoc_rtd_to_cpu(rtd, 0),
				  SND_SOC_DAIFMT_I2S     |
				  SND_SOC_DAIFMT_NB_NF   |
				  SND_SOC_DAIFMT_CBS_CFS);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set format to I2S, err %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_tdm_slot(asoc_rtd_to_cpu(rtd, 0), 0x3, 0x3, 2, bits);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set I2S config, err %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक byt_rt5640_aअगर1_startup(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_pcm_hw_स्थिरraपूर्णांक_single(substream->runसमय,
			SNDRV_PCM_HW_PARAM_RATE, 48000);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops byt_rt5640_aअगर1_ops = अणु
	.startup = byt_rt5640_aअगर1_startup,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops byt_rt5640_be_ssp2_ops = अणु
	.hw_params = byt_rt5640_aअगर1_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEF(dummy,
	DAILINK_COMP_ARRAY(COMP_DUMMY()));

SND_SOC_DAILINK_DEF(media,
	DAILINK_COMP_ARRAY(COMP_CPU("media-cpu-dai")));

SND_SOC_DAILINK_DEF(deepbuffer,
	DAILINK_COMP_ARRAY(COMP_CPU("deepbuffer-cpu-dai")));

SND_SOC_DAILINK_DEF(ssp2_port,
	/* overwritten क्रम ssp0 routing */
	DAILINK_COMP_ARRAY(COMP_CPU("ssp2-port")));
SND_SOC_DAILINK_DEF(ssp2_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC(
	/* overwritten with HID */ "i2c-10EC5640:00",
	/* changed w/ quirk */	"rt5640-aif1")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("sst-mfld-platform")));

अटल काष्ठा snd_soc_dai_link byt_rt5640_dais[] = अणु
	[MERR_DPCM_AUDIO] = अणु
		.name = "Baytrail Audio Port",
		.stream_name = "Baytrail Audio",
		.nonatomic = true,
		.dynamic = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ops = &byt_rt5640_aअगर1_ops,
		SND_SOC_DAILINK_REG(media, dummy, platक्रमm),
	पूर्ण,
	[MERR_DPCM_DEEP_BUFFER] = अणु
		.name = "Deep-Buffer Audio Port",
		.stream_name = "Deep-Buffer Audio",
		.nonatomic = true,
		.dynamic = 1,
		.dpcm_playback = 1,
		.ops = &byt_rt5640_aअगर1_ops,
		SND_SOC_DAILINK_REG(deepbuffer, dummy, platक्रमm),
	पूर्ण,
		/* back ends */
	अणु
		.name = "SSP2-Codec",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
						| SND_SOC_DAIFMT_CBS_CFS,
		.be_hw_params_fixup = byt_rt5640_codec_fixup,
		.nonatomic = true,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.init = byt_rt5640_init,
		.ops = &byt_rt5640_be_ssp2_ops,
		SND_SOC_DAILINK_REG(ssp2_port, ssp2_codec, platक्रमm),
	पूर्ण,
पूर्ण;

/* SoC card */
अटल अक्षर byt_rt5640_codec_name[SND_ACPI_I2C_ID_LEN];
#अगर !IS_ENABLED(CONFIG_SND_SOC_INTEL_USER_FRIENDLY_LONG_NAMES)
अटल अक्षर byt_rt5640_दीर्घ_name[40]; /* = "bytcr-rt5640-*-spk-*-mic" */
#पूर्ण_अगर
अटल अक्षर byt_rt5640_components[32]; /* = "cfg-spk:* cfg-mic:*" */

अटल पूर्णांक byt_rt5640_suspend(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_component *component;

	अगर (!BYT_RT5640_JDSRC(byt_rt5640_quirk))
		वापस 0;

	क्रम_each_card_components(card, component) अणु
		अगर (!म_भेद(component->name, byt_rt5640_codec_name)) अणु
			dev_dbg(component->dev, "disabling jack detect before suspend\n");
			snd_soc_component_set_jack(component, शून्य, शून्य);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक byt_rt5640_resume(काष्ठा snd_soc_card *card)
अणु
	काष्ठा byt_rt5640_निजी *priv = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_component *component;

	अगर (!BYT_RT5640_JDSRC(byt_rt5640_quirk))
		वापस 0;

	क्रम_each_card_components(card, component) अणु
		अगर (!म_भेद(component->name, byt_rt5640_codec_name)) अणु
			dev_dbg(component->dev, "re-enabling jack detect after resume\n");
			snd_soc_component_set_jack(component, &priv->jack, शून्य);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* use space beक्रमe codec name to simplअगरy card ID, and simplअगरy driver name */
#घोषणा SOF_CARD_NAME "bytcht rt5640" /* card name will be 'sof-bytcht rt5640' */
#घोषणा SOF_DRIVER_NAME "SOF"

#घोषणा CARD_NAME "bytcr-rt5640"
#घोषणा DRIVER_NAME शून्य /* card name will be used क्रम driver name */

अटल काष्ठा snd_soc_card byt_rt5640_card = अणु
	.owner = THIS_MODULE,
	.dai_link = byt_rt5640_dais,
	.num_links = ARRAY_SIZE(byt_rt5640_dais),
	.dapm_widमाला_लो = byt_rt5640_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(byt_rt5640_widमाला_लो),
	.dapm_routes = byt_rt5640_audio_map,
	.num_dapm_routes = ARRAY_SIZE(byt_rt5640_audio_map),
	.fully_routed = true,
	.suspend_pre = byt_rt5640_suspend,
	.resume_post = byt_rt5640_resume,
पूर्ण;

काष्ठा acpi_chan_package अणु   /* ACPICA seems to require 64 bit पूर्णांकegers */
	u64 aअगर_value;       /* 1: AIF1, 2: AIF2 */
	u64 mघड़ी_value;    /* usually 25MHz (0x17d7940), ignored */
पूर्ण;

अटल पूर्णांक snd_byt_rt5640_mc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	अटल स्थिर अक्षर * स्थिर map_name[] = अणु "dmic1", "dmic2", "in1", "in3", "none" पूर्ण;
	__maybe_unused स्थिर अक्षर *spk_type;
	स्थिर काष्ठा dmi_प्रणाली_id *dmi_id;
	काष्ठा byt_rt5640_निजी *priv;
	काष्ठा snd_soc_acpi_mach *mach;
	स्थिर अक्षर *platक्रमm_name;
	काष्ठा acpi_device *adev;
	bool sof_parent;
	पूर्णांक ret_val = 0;
	पूर्णांक dai_index = 0;
	पूर्णांक i, cfg_spk;
	पूर्णांक aअगर;

	is_bytcr = false;
	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/* रेजिस्टर the soc card */
	byt_rt5640_card.dev = &pdev->dev;
	mach = byt_rt5640_card.dev->platक्रमm_data;
	snd_soc_card_set_drvdata(&byt_rt5640_card, priv);

	/* fix index of codec dai */
	क्रम (i = 0; i < ARRAY_SIZE(byt_rt5640_dais); i++) अणु
		अगर (!म_भेद(byt_rt5640_dais[i].codecs->name,
			    "i2c-10EC5640:00")) अणु
			dai_index = i;
			अवरोध;
		पूर्ण
	पूर्ण

	/* fixup codec name based on HID */
	adev = acpi_dev_get_first_match_dev(mach->id, शून्य, -1);
	अगर (adev) अणु
		snम_लिखो(byt_rt5640_codec_name, माप(byt_rt5640_codec_name),
			 "i2c-%s", acpi_dev_name(adev));
		put_device(&adev->dev);
		byt_rt5640_dais[dai_index].codecs->name = byt_rt5640_codec_name;
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
				byt_rt5640_quirk |= BYT_RT5640_SSP0_AIF1;
			पूर्ण अन्यथा  अगर (chan_package.aअगर_value == 2) अणु
				dev_info(&pdev->dev, "BIOS Routing: AIF2 connected\n");
				byt_rt5640_quirk |= BYT_RT5640_SSP0_AIF2;
			पूर्ण अन्यथा अणु
				dev_info(&pdev->dev, "BIOS Routing isn't valid, ignored\n");
				pkg_found = false;
			पूर्ण
		पूर्ण

		अगर (!pkg_found) अणु
			/* no BIOS indications, assume SSP0-AIF2 connection */
			byt_rt5640_quirk |= BYT_RT5640_SSP0_AIF2;
		पूर्ण

		/* change शेषs क्रम Baytrail-CR capture */
		byt_rt5640_quirk |= BYTCR_INPUT_DEFAULTS;
	पूर्ण अन्यथा अणु
		byt_rt5640_quirk |= BYT_RT5640_DMIC1_MAP |
				    BYT_RT5640_JD_SRC_JD2_IN4N |
				    BYT_RT5640_OVCD_TH_2000UA |
				    BYT_RT5640_OVCD_SF_0P75;
	पूर्ण

	/* check quirks beक्रमe creating card */
	dmi_id = dmi_first_match(byt_rt5640_quirk_table);
	अगर (dmi_id)
		byt_rt5640_quirk = (अचिन्हित दीर्घ)dmi_id->driver_data;
	अगर (quirk_override != -1) अणु
		dev_info(&pdev->dev, "Overriding quirk 0x%lx => 0x%x\n",
			 byt_rt5640_quirk, quirk_override);
		byt_rt5640_quirk = quirk_override;
	पूर्ण

	/* Must be called beक्रमe रेजिस्टर_card, also see declaration comment. */
	ret_val = byt_rt5640_add_codec_device_props(byt_rt5640_codec_name);
	अगर (ret_val)
		वापस ret_val;

	log_quirks(&pdev->dev);

	अगर ((byt_rt5640_quirk & BYT_RT5640_SSP2_AIF2) ||
	    (byt_rt5640_quirk & BYT_RT5640_SSP0_AIF2)) अणु
		byt_rt5640_dais[dai_index].codecs->dai_name = "rt5640-aif2";
		aअगर = 2;
	पूर्ण अन्यथा अणु
		aअगर = 1;
	पूर्ण

	अगर ((byt_rt5640_quirk & BYT_RT5640_SSP0_AIF1) ||
	    (byt_rt5640_quirk & BYT_RT5640_SSP0_AIF2))
		byt_rt5640_dais[dai_index].cpus->dai_name = "ssp0-port";

	अगर (byt_rt5640_quirk & BYT_RT5640_MCLK_EN) अणु
		priv->mclk = devm_clk_get(&pdev->dev, "pmc_plt_clk_3");
		अगर (IS_ERR(priv->mclk)) अणु
			ret_val = PTR_ERR(priv->mclk);

			dev_err(&pdev->dev,
				"Failed to get MCLK from pmc_plt_clk_3: %d\n",
				ret_val);

			/*
			 * Fall back to bit घड़ी usage क्रम -ENOENT (घड़ी not
			 * available likely due to missing dependencies), bail
			 * क्रम all other errors, including -EPROBE_DEFER
			 */
			अगर (ret_val != -ENOENT)
				वापस ret_val;
			byt_rt5640_quirk &= ~BYT_RT5640_MCLK_EN;
		पूर्ण
	पूर्ण

	अगर (byt_rt5640_quirk & BYT_RT5640_NO_SPEAKERS) अणु
		cfg_spk = 0;
		spk_type = "none";
	पूर्ण अन्यथा अगर (byt_rt5640_quirk & BYT_RT5640_MONO_SPEAKER) अणु
		cfg_spk = 1;
		spk_type = "mono";
	पूर्ण अन्यथा अणु
		cfg_spk = 2;
		spk_type = "stereo";
	पूर्ण

	snम_लिखो(byt_rt5640_components, माप(byt_rt5640_components),
		 "cfg-spk:%d cfg-mic:%s aif:%d", cfg_spk,
		 map_name[BYT_RT5640_MAP(byt_rt5640_quirk)], aअगर);
	byt_rt5640_card.components = byt_rt5640_components;
#अगर !IS_ENABLED(CONFIG_SND_SOC_INTEL_USER_FRIENDLY_LONG_NAMES)
	snम_लिखो(byt_rt5640_दीर्घ_name, माप(byt_rt5640_दीर्घ_name),
		 "bytcr-rt5640-%s-spk-%s-mic", spk_type,
		 map_name[BYT_RT5640_MAP(byt_rt5640_quirk)]);
	byt_rt5640_card.दीर्घ_name = byt_rt5640_दीर्घ_name;
#पूर्ण_अगर

	/* override plaक्रमm name, अगर required */
	platक्रमm_name = mach->mach_params.platक्रमm;

	ret_val = snd_soc_fixup_dai_links_platक्रमm_name(&byt_rt5640_card,
							platक्रमm_name);
	अगर (ret_val)
		वापस ret_val;

	sof_parent = snd_soc_acpi_sof_parent(&pdev->dev);

	/* set card and driver name */
	अगर (sof_parent) अणु
		byt_rt5640_card.name = SOF_CARD_NAME;
		byt_rt5640_card.driver_name = SOF_DRIVER_NAME;
	पूर्ण अन्यथा अणु
		byt_rt5640_card.name = CARD_NAME;
		byt_rt5640_card.driver_name = DRIVER_NAME;
	पूर्ण

	/* set pm ops */
	अगर (sof_parent)
		dev->driver->pm = &snd_soc_pm_ops;

	ret_val = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &byt_rt5640_card);

	अगर (ret_val) अणु
		dev_err(&pdev->dev, "devm_snd_soc_register_card failed %d\n",
			ret_val);
		वापस ret_val;
	पूर्ण
	platक्रमm_set_drvdata(pdev, &byt_rt5640_card);
	वापस ret_val;
पूर्ण

अटल काष्ठा platक्रमm_driver snd_byt_rt5640_mc_driver = अणु
	.driver = अणु
		.name = "bytcr_rt5640",
	पूर्ण,
	.probe = snd_byt_rt5640_mc_probe,
पूर्ण;

module_platक्रमm_driver(snd_byt_rt5640_mc_driver);

MODULE_DESCRIPTION("ASoC Intel(R) Baytrail CR Machine driver");
MODULE_AUTHOR("Subhransu S. Prusty <subhransu.s.prusty@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:bytcr_rt5640");
