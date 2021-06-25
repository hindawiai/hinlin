<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  bytcr_rt5651.c - ASoc Machine driver क्रम Intel Byt CR platक्रमm
 *  (derived from bytcr_rt5640.c)
 *
 *  Copyright (C) 2015 Intel Corp
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/dmi.h>
#समावेश <linux/input.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>
#समावेश <sound/soc-acpi.h>
#समावेश "../../codecs/rt5651.h"
#समावेश "../atom/sst-atom-controls.h"
#समावेश "../common/soc-intel-quirks.h"

क्रमागत अणु
	BYT_RT5651_DMIC_MAP,
	BYT_RT5651_IN1_MAP,
	BYT_RT5651_IN2_MAP,
	BYT_RT5651_IN1_IN2_MAP,
पूर्ण;

क्रमागत अणु
	BYT_RT5651_JD_शून्य	= (RT5651_JD_शून्य << 4),
	BYT_RT5651_JD1_1	= (RT5651_JD1_1 << 4),
	BYT_RT5651_JD1_2	= (RT5651_JD1_2 << 4),
	BYT_RT5651_JD2		= (RT5651_JD2 << 4),
पूर्ण;

क्रमागत अणु
	BYT_RT5651_OVCD_TH_600UA  = (6 << 8),
	BYT_RT5651_OVCD_TH_1500UA = (15 << 8),
	BYT_RT5651_OVCD_TH_2000UA = (20 << 8),
पूर्ण;

क्रमागत अणु
	BYT_RT5651_OVCD_SF_0P5	= (RT5651_OVCD_SF_0P5 << 13),
	BYT_RT5651_OVCD_SF_0P75	= (RT5651_OVCD_SF_0P75 << 13),
	BYT_RT5651_OVCD_SF_1P0	= (RT5651_OVCD_SF_1P0 << 13),
	BYT_RT5651_OVCD_SF_1P5	= (RT5651_OVCD_SF_1P5 << 13),
पूर्ण;

#घोषणा BYT_RT5651_MAP(quirk)		((quirk) & GENMASK(3, 0))
#घोषणा BYT_RT5651_JDSRC(quirk)		(((quirk) & GENMASK(7, 4)) >> 4)
#घोषणा BYT_RT5651_OVCD_TH(quirk)	(((quirk) & GENMASK(12, 8)) >> 8)
#घोषणा BYT_RT5651_OVCD_SF(quirk)	(((quirk) & GENMASK(14, 13)) >> 13)
#घोषणा BYT_RT5651_DMIC_EN		BIT(16)
#घोषणा BYT_RT5651_MCLK_EN		BIT(17)
#घोषणा BYT_RT5651_MCLK_25MHZ		BIT(18)
#घोषणा BYT_RT5651_SSP2_AIF2		BIT(19) /* शेष is using AIF1  */
#घोषणा BYT_RT5651_SSP0_AIF1		BIT(20)
#घोषणा BYT_RT5651_SSP0_AIF2		BIT(21)
#घोषणा BYT_RT5651_HP_LR_SWAPPED	BIT(22)
#घोषणा BYT_RT5651_MONO_SPEAKER		BIT(23)
#घोषणा BYT_RT5651_JD_NOT_INV		BIT(24)

#घोषणा BYT_RT5651_DEFAULT_QUIRKS	(BYT_RT5651_MCLK_EN | \
					 BYT_RT5651_JD1_1   | \
					 BYT_RT5651_OVCD_TH_2000UA | \
					 BYT_RT5651_OVCD_SF_0P75)

/* jack-detect-source + inv + dmic-en + ovcd-th + -sf + terminating entry */
#घोषणा MAX_NO_PROPS 6

काष्ठा byt_rt5651_निजी अणु
	काष्ठा clk *mclk;
	काष्ठा gpio_desc *ext_amp_gpio;
	काष्ठा gpio_desc *hp_detect;
	काष्ठा snd_soc_jack jack;
पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping *byt_rt5651_gpios;

/* Default: jack-detect on JD1_1, पूर्णांकernal mic on in2, headseपंचांगic on in3 */
अटल अचिन्हित दीर्घ byt_rt5651_quirk = BYT_RT5651_DEFAULT_QUIRKS |
					BYT_RT5651_IN2_MAP;

अटल पूर्णांक quirk_override = -1;
module_param_named(quirk, quirk_override, पूर्णांक, 0444);
MODULE_PARM_DESC(quirk, "Board-specific quirk override");

अटल व्योम log_quirks(काष्ठा device *dev)
अणु
	अगर (BYT_RT5651_MAP(byt_rt5651_quirk) == BYT_RT5651_DMIC_MAP)
		dev_info(dev, "quirk DMIC_MAP enabled");
	अगर (BYT_RT5651_MAP(byt_rt5651_quirk) == BYT_RT5651_IN1_MAP)
		dev_info(dev, "quirk IN1_MAP enabled");
	अगर (BYT_RT5651_MAP(byt_rt5651_quirk) == BYT_RT5651_IN2_MAP)
		dev_info(dev, "quirk IN2_MAP enabled");
	अगर (BYT_RT5651_MAP(byt_rt5651_quirk) == BYT_RT5651_IN1_IN2_MAP)
		dev_info(dev, "quirk IN1_IN2_MAP enabled");
	अगर (BYT_RT5651_JDSRC(byt_rt5651_quirk)) अणु
		dev_info(dev, "quirk realtek,jack-detect-source %ld\n",
			 BYT_RT5651_JDSRC(byt_rt5651_quirk));
		dev_info(dev, "quirk realtek,over-current-threshold-microamp %ld\n",
			 BYT_RT5651_OVCD_TH(byt_rt5651_quirk) * 100);
		dev_info(dev, "quirk realtek,over-current-scale-factor %ld\n",
			 BYT_RT5651_OVCD_SF(byt_rt5651_quirk));
	पूर्ण
	अगर (byt_rt5651_quirk & BYT_RT5651_DMIC_EN)
		dev_info(dev, "quirk DMIC enabled");
	अगर (byt_rt5651_quirk & BYT_RT5651_MCLK_EN)
		dev_info(dev, "quirk MCLK_EN enabled");
	अगर (byt_rt5651_quirk & BYT_RT5651_MCLK_25MHZ)
		dev_info(dev, "quirk MCLK_25MHZ enabled");
	अगर (byt_rt5651_quirk & BYT_RT5651_SSP2_AIF2)
		dev_info(dev, "quirk SSP2_AIF2 enabled\n");
	अगर (byt_rt5651_quirk & BYT_RT5651_SSP0_AIF1)
		dev_info(dev, "quirk SSP0_AIF1 enabled\n");
	अगर (byt_rt5651_quirk & BYT_RT5651_SSP0_AIF2)
		dev_info(dev, "quirk SSP0_AIF2 enabled\n");
	अगर (byt_rt5651_quirk & BYT_RT5651_MONO_SPEAKER)
		dev_info(dev, "quirk MONO_SPEAKER enabled\n");
	अगर (byt_rt5651_quirk & BYT_RT5651_JD_NOT_INV)
		dev_info(dev, "quirk JD_NOT_INV enabled\n");
पूर्ण

#घोषणा BYT_CODEC_DAI1	"rt5651-aif1"
#घोषणा BYT_CODEC_DAI2	"rt5651-aif2"

अटल पूर्णांक byt_rt5651_prepare_and_enable_pll1(काष्ठा snd_soc_dai *codec_dai,
					      पूर्णांक rate, पूर्णांक bclk_ratio)
अणु
	पूर्णांक clk_id, clk_freq, ret;

	/* Configure the PLL beक्रमe selecting it */
	अगर (!(byt_rt5651_quirk & BYT_RT5651_MCLK_EN)) अणु
		clk_id = RT5651_PLL1_S_BCLK1;
		clk_freq = rate * bclk_ratio;
	पूर्ण अन्यथा अणु
		clk_id = RT5651_PLL1_S_MCLK;
		अगर (byt_rt5651_quirk & BYT_RT5651_MCLK_25MHZ)
			clk_freq = 25000000;
		अन्यथा
			clk_freq = 19200000;
	पूर्ण
	ret = snd_soc_dai_set_pll(codec_dai, 0, clk_id, clk_freq, rate * 512);
	अगर (ret < 0) अणु
		dev_err(codec_dai->component->dev, "can't set pll: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(codec_dai, RT5651_SCLK_S_PLL1,
				     rate * 512, SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(codec_dai->component->dev, "can't set clock %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक platक्रमm_घड़ी_control(काष्ठा snd_soc_dapm_widget *w,
				  काष्ठा snd_kcontrol *k, पूर्णांक  event)
अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा snd_soc_dai *codec_dai;
	काष्ठा byt_rt5651_निजी *priv = snd_soc_card_get_drvdata(card);
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
		अगर (byt_rt5651_quirk & BYT_RT5651_MCLK_EN) अणु
			ret = clk_prepare_enable(priv->mclk);
			अगर (ret < 0) अणु
				dev_err(card->dev,
					"could not configure MCLK state");
				वापस ret;
			पूर्ण
		पूर्ण
		ret = byt_rt5651_prepare_and_enable_pll1(codec_dai, 48000, 50);
	पूर्ण अन्यथा अणु
		/*
		 * Set codec घड़ी source to पूर्णांकernal घड़ी beक्रमe
		 * turning off the platक्रमm घड़ी. Codec needs घड़ी
		 * क्रम Jack detection and button press
		 */
		ret = snd_soc_dai_set_sysclk(codec_dai, RT5651_SCLK_S_RCCLK,
					     48000 * 512,
					     SND_SOC_CLOCK_IN);
		अगर (!ret)
			अगर (byt_rt5651_quirk & BYT_RT5651_MCLK_EN)
				clk_disable_unprepare(priv->mclk);
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(card->dev, "can't set codec sysclk: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5651_ext_amp_घातer_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_card *card = w->dapm->card;
	काष्ठा byt_rt5651_निजी *priv = snd_soc_card_get_drvdata(card);

	अगर (SND_SOC_DAPM_EVENT_ON(event))
		gpiod_set_value_cansleep(priv->ext_amp_gpio, 1);
	अन्यथा
		gpiod_set_value_cansleep(priv->ext_amp_gpio, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget byt_rt5651_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Internal Mic", शून्य),
	SND_SOC_DAPM_SPK("Speaker", शून्य),
	SND_SOC_DAPM_LINE("Line In", शून्य),
	SND_SOC_DAPM_SUPPLY("Platform Clock", SND_SOC_NOPM, 0, 0,
			    platक्रमm_घड़ी_control, SND_SOC_DAPM_PRE_PMU |
			    SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("Ext Amp Power", SND_SOC_NOPM, 0, 0,
			    rt5651_ext_amp_घातer_event,
			    SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_rt5651_audio_map[] = अणु
	अणु"Headphone", शून्य, "Platform Clock"पूर्ण,
	अणु"Headset Mic", शून्य, "Platform Clock"पूर्ण,
	अणु"Internal Mic", शून्य, "Platform Clock"पूर्ण,
	अणु"Speaker", शून्य, "Platform Clock"पूर्ण,
	अणु"Speaker", शून्य, "Ext Amp Power"पूर्ण,
	अणु"Line In", शून्य, "Platform Clock"पूर्ण,

	अणु"Headset Mic", शून्य, "micbias1"पूर्ण, /* lowerहाल क्रम rt5651 */
	अणु"Headphone", शून्य, "HPOL"पूर्ण,
	अणु"Headphone", शून्य, "HPOR"पूर्ण,
	अणु"Speaker", शून्य, "LOUTL"पूर्ण,
	अणु"Speaker", शून्य, "LOUTR"पूर्ण,
	अणु"IN2P", शून्य, "Line In"पूर्ण,
	अणु"IN2N", शून्य, "Line In"पूर्ण,

पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_rt5651_पूर्णांकmic_dmic_map[] = अणु
	अणु"DMIC L1", शून्य, "Internal Mic"पूर्ण,
	अणु"DMIC R1", शून्य, "Internal Mic"पूर्ण,
	अणु"IN2P", शून्य, "Headset Mic"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_rt5651_पूर्णांकmic_in1_map[] = अणु
	अणु"Internal Mic", शून्य, "micbias1"पूर्ण,
	अणु"IN1P", शून्य, "Internal Mic"पूर्ण,
	अणु"IN3P", शून्य, "Headset Mic"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_rt5651_पूर्णांकmic_in2_map[] = अणु
	अणु"Internal Mic", शून्य, "micbias1"पूर्ण,
	अणु"IN2P", शून्य, "Internal Mic"पूर्ण,
	अणु"IN3P", शून्य, "Headset Mic"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_rt5651_पूर्णांकmic_in1_in2_map[] = अणु
	अणु"Internal Mic", शून्य, "micbias1"पूर्ण,
	अणु"IN1P", शून्य, "Internal Mic"पूर्ण,
	अणु"IN2P", शून्य, "Internal Mic"पूर्ण,
	अणु"IN3P", शून्य, "Headset Mic"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_rt5651_ssp0_aअगर1_map[] = अणु
	अणु"ssp0 Tx", शून्य, "modem_out"पूर्ण,
	अणु"modem_in", शून्य, "ssp0 Rx"पूर्ण,

	अणु"AIF1 Playback", शून्य, "ssp0 Tx"पूर्ण,
	अणु"ssp0 Rx", शून्य, "AIF1 Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_rt5651_ssp0_aअगर2_map[] = अणु
	अणु"ssp0 Tx", शून्य, "modem_out"पूर्ण,
	अणु"modem_in", शून्य, "ssp0 Rx"पूर्ण,

	अणु"AIF2 Playback", शून्य, "ssp0 Tx"पूर्ण,
	अणु"ssp0 Rx", शून्य, "AIF2 Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_rt5651_ssp2_aअगर1_map[] = अणु
	अणु"ssp2 Tx", शून्य, "codec_out0"पूर्ण,
	अणु"ssp2 Tx", शून्य, "codec_out1"पूर्ण,
	अणु"codec_in0", शून्य, "ssp2 Rx"पूर्ण,
	अणु"codec_in1", शून्य, "ssp2 Rx"पूर्ण,

	अणु"AIF1 Playback", शून्य, "ssp2 Tx"पूर्ण,
	अणु"ssp2 Rx", शून्य, "AIF1 Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route byt_rt5651_ssp2_aअगर2_map[] = अणु
	अणु"ssp2 Tx", शून्य, "codec_out0"पूर्ण,
	अणु"ssp2 Tx", शून्य, "codec_out1"पूर्ण,
	अणु"codec_in0", शून्य, "ssp2 Rx"पूर्ण,
	अणु"codec_in1", शून्य, "ssp2 Rx"पूर्ण,

	अणु"AIF2 Playback", शून्य, "ssp2 Tx"पूर्ण,
	अणु"ssp2 Rx", शून्य, "AIF2 Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new byt_rt5651_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Internal Mic"),
	SOC_DAPM_PIN_SWITCH("Speaker"),
	SOC_DAPM_PIN_SWITCH("Line In"),
पूर्ण;

अटल काष्ठा snd_soc_jack_pin bytcr_jack_pins[] = अणु
	अणु
		.pin	= "Headphone",
		.mask	= SND_JACK_HEADPHONE,
	पूर्ण,
	अणु
		.pin	= "Headset Mic",
		.mask	= SND_JACK_MICROPHONE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक byt_rt5651_aअगर1_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	snd_pcm_क्रमmat_t क्रमmat = params_क्रमmat(params);
	पूर्णांक rate = params_rate(params);
	पूर्णांक bclk_ratio;

	अगर (क्रमmat == SNDRV_PCM_FORMAT_S16_LE)
		bclk_ratio = 32;
	अन्यथा
		bclk_ratio = 50;

	वापस byt_rt5651_prepare_and_enable_pll1(codec_dai, rate, bclk_ratio);
पूर्ण

अटल स्थिर काष्ठा acpi_gpio_params pov_p1006w_hp_detect = अणु 1, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params pov_p1006w_ext_amp_en = अणु 2, 0, true पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping byt_rt5651_pov_p1006w_gpios[] = अणु
	अणु "hp-detect-gpios", &pov_p1006w_hp_detect, 1, पूर्ण,
	अणु "ext-amp-enable-gpios", &pov_p1006w_ext_amp_en, 1, पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक byt_rt5651_pov_p1006w_quirk_cb(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	byt_rt5651_quirk = (अचिन्हित दीर्घ)id->driver_data;
	byt_rt5651_gpios = byt_rt5651_pov_p1006w_gpios;
	वापस 1;
पूर्ण

अटल पूर्णांक byt_rt5651_quirk_cb(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	byt_rt5651_quirk = (अचिन्हित दीर्घ)id->driver_data;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id byt_rt5651_quirk_table[] = अणु
	अणु
		/* Chuwi Hi8 Pro (CWI513) */
		.callback = byt_rt5651_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hampoo"),
			DMI_MATCH(DMI_PRODUCT_NAME, "X1D3_C806N"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5651_DEFAULT_QUIRKS |
					BYT_RT5651_IN2_MAP |
					BYT_RT5651_HP_LR_SWAPPED |
					BYT_RT5651_MONO_SPEAKER),
	पूर्ण,
	अणु
		/* Chuwi Vi8 Plus (CWI519) */
		.callback = byt_rt5651_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hampoo"),
			DMI_MATCH(DMI_PRODUCT_NAME, "D2D3_Vi8A1"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5651_DEFAULT_QUIRKS |
					BYT_RT5651_IN2_MAP |
					BYT_RT5651_HP_LR_SWAPPED |
					BYT_RT5651_MONO_SPEAKER),
	पूर्ण,
	अणु
		/* Complet Electro Serv MY8307 */
		.callback = byt_rt5651_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Complet Electro Serv"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MY8307"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5651_DEFAULT_QUIRKS |
					BYT_RT5651_IN2_MAP |
					BYT_RT5651_MONO_SPEAKER |
					BYT_RT5651_JD_NOT_INV),
	पूर्ण,
	अणु
		/* I.T.Works TW701, Ployer Momo7w and Trekstor ST70416-6
		 * (these all use the same मुख्यboard) */
		.callback = byt_rt5651_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_BIOS_VENDOR, "INSYDE Corp."),
			/* Partial match क्रम all of itWORKS.G.WI71C.JGBMRBA,
			 * TREK.G.WI71C.JGBMRBA0x and MOMO.G.WI71C.MABMRBA02 */
			DMI_MATCH(DMI_BIOS_VERSION, ".G.WI71C."),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5651_DEFAULT_QUIRKS |
					BYT_RT5651_IN2_MAP |
					BYT_RT5651_SSP0_AIF1 |
					BYT_RT5651_MONO_SPEAKER),
	पूर्ण,
	अणु
		/* Jumper EZpad 7 */
		.callback = byt_rt5651_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Jumper"),
			DMI_MATCH(DMI_PRODUCT_NAME, "EZpad"),
			/* Jumper12x.WJ2012.bsBKRCP05 with the version dropped */
			DMI_MATCH(DMI_BIOS_VERSION, "Jumper12x.WJ2012.bsBKRCP"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5651_DEFAULT_QUIRKS |
					BYT_RT5651_IN2_MAP |
					BYT_RT5651_JD_NOT_INV),
	पूर्ण,
	अणु
		/* KIANO SlimNote 14.2 */
		.callback = byt_rt5651_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "KIANO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "KIANO SlimNote 14.2"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5651_DEFAULT_QUIRKS |
					BYT_RT5651_IN1_IN2_MAP),
	पूर्ण,
	अणु
		/* Minnowboard Max B3 */
		.callback = byt_rt5651_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Circuitco"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Minnowboard Max B3 PLATFORM"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5651_IN1_MAP),
	पूर्ण,
	अणु
		/* Minnowboard Turbot */
		.callback = byt_rt5651_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ADI"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Minnowboard Turbot"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5651_MCLK_EN |
					BYT_RT5651_IN1_MAP),
	पूर्ण,
	अणु
		/* Poपूर्णांक of View mobii wपूर्णांकab p1006w (v1.0) */
		.callback = byt_rt5651_pov_p1006w_quirk_cb,
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "BayTrail"),
			/* Note 105b is Foxcon's USB/PCI venकरोr id */
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "105B"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "0E57"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5651_DMIC_MAP |
					BYT_RT5651_OVCD_TH_2000UA |
					BYT_RT5651_OVCD_SF_0P75 |
					BYT_RT5651_DMIC_EN |
					BYT_RT5651_MCLK_EN |
					BYT_RT5651_SSP0_AIF1),
	पूर्ण,
	अणु
		/* VIOS LTH17 */
		.callback = byt_rt5651_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "VIOS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LTH17"),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5651_IN1_IN2_MAP |
					BYT_RT5651_JD1_1 |
					BYT_RT5651_OVCD_TH_2000UA |
					BYT_RT5651_OVCD_SF_1P0 |
					BYT_RT5651_MCLK_EN),
	पूर्ण,
	अणु
		/* Yours Y8W81 (and others using the same मुख्यboard) */
		.callback = byt_rt5651_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_BIOS_VENDOR, "INSYDE Corp."),
			/* Partial match क्रम all devs with a W86C मुख्यboard */
			DMI_MATCH(DMI_BIOS_VERSION, ".F.W86C."),
		पूर्ण,
		.driver_data = (व्योम *)(BYT_RT5651_DEFAULT_QUIRKS |
					BYT_RT5651_IN2_MAP |
					BYT_RT5651_SSP0_AIF1 |
					BYT_RT5651_MONO_SPEAKER),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * Note this MUST be called beक्रमe snd_soc_रेजिस्टर_card(), so that the props
 * are in place beक्रमe the codec component driver's probe function parses them.
 */
अटल पूर्णांक byt_rt5651_add_codec_device_props(काष्ठा device *i2c_dev)
अणु
	काष्ठा property_entry props[MAX_NO_PROPS] = अणुपूर्ण;
	पूर्णांक cnt = 0;

	props[cnt++] = PROPERTY_ENTRY_U32("realtek,jack-detect-source",
				BYT_RT5651_JDSRC(byt_rt5651_quirk));

	props[cnt++] = PROPERTY_ENTRY_U32("realtek,over-current-threshold-microamp",
				BYT_RT5651_OVCD_TH(byt_rt5651_quirk) * 100);

	props[cnt++] = PROPERTY_ENTRY_U32("realtek,over-current-scale-factor",
				BYT_RT5651_OVCD_SF(byt_rt5651_quirk));

	अगर (byt_rt5651_quirk & BYT_RT5651_DMIC_EN)
		props[cnt++] = PROPERTY_ENTRY_BOOL("realtek,dmic-en");

	अगर (byt_rt5651_quirk & BYT_RT5651_JD_NOT_INV)
		props[cnt++] = PROPERTY_ENTRY_BOOL("realtek,jack-detect-not-inverted");

	वापस device_add_properties(i2c_dev, props);
पूर्ण

अटल पूर्णांक byt_rt5651_init(काष्ठा snd_soc_pcm_runसमय *runसमय)
अणु
	काष्ठा snd_soc_card *card = runसमय->card;
	काष्ठा snd_soc_component *codec = asoc_rtd_to_codec(runसमय, 0)->component;
	काष्ठा byt_rt5651_निजी *priv = snd_soc_card_get_drvdata(card);
	स्थिर काष्ठा snd_soc_dapm_route *custom_map;
	पूर्णांक num_routes;
	पूर्णांक report;
	पूर्णांक ret;

	card->dapm.idle_bias_off = true;

	/* Start with RC clk क्रम jack-detect (we disable MCLK below) */
	अगर (byt_rt5651_quirk & BYT_RT5651_MCLK_EN)
		snd_soc_component_update_bits(codec, RT5651_GLB_CLK,
			RT5651_SCLK_SRC_MASK, RT5651_SCLK_SRC_RCCLK);

	चयन (BYT_RT5651_MAP(byt_rt5651_quirk)) अणु
	हाल BYT_RT5651_IN1_MAP:
		custom_map = byt_rt5651_पूर्णांकmic_in1_map;
		num_routes = ARRAY_SIZE(byt_rt5651_पूर्णांकmic_in1_map);
		अवरोध;
	हाल BYT_RT5651_IN2_MAP:
		custom_map = byt_rt5651_पूर्णांकmic_in2_map;
		num_routes = ARRAY_SIZE(byt_rt5651_पूर्णांकmic_in2_map);
		अवरोध;
	हाल BYT_RT5651_IN1_IN2_MAP:
		custom_map = byt_rt5651_पूर्णांकmic_in1_in2_map;
		num_routes = ARRAY_SIZE(byt_rt5651_पूर्णांकmic_in1_in2_map);
		अवरोध;
	शेष:
		custom_map = byt_rt5651_पूर्णांकmic_dmic_map;
		num_routes = ARRAY_SIZE(byt_rt5651_पूर्णांकmic_dmic_map);
	पूर्ण
	ret = snd_soc_dapm_add_routes(&card->dapm, custom_map, num_routes);
	अगर (ret)
		वापस ret;

	अगर (byt_rt5651_quirk & BYT_RT5651_SSP2_AIF2) अणु
		ret = snd_soc_dapm_add_routes(&card->dapm,
					byt_rt5651_ssp2_aअगर2_map,
					ARRAY_SIZE(byt_rt5651_ssp2_aअगर2_map));
	पूर्ण अन्यथा अगर (byt_rt5651_quirk & BYT_RT5651_SSP0_AIF1) अणु
		ret = snd_soc_dapm_add_routes(&card->dapm,
					byt_rt5651_ssp0_aअगर1_map,
					ARRAY_SIZE(byt_rt5651_ssp0_aअगर1_map));
	पूर्ण अन्यथा अगर (byt_rt5651_quirk & BYT_RT5651_SSP0_AIF2) अणु
		ret = snd_soc_dapm_add_routes(&card->dapm,
					byt_rt5651_ssp0_aअगर2_map,
					ARRAY_SIZE(byt_rt5651_ssp0_aअगर2_map));
	पूर्ण अन्यथा अणु
		ret = snd_soc_dapm_add_routes(&card->dapm,
					byt_rt5651_ssp2_aअगर1_map,
					ARRAY_SIZE(byt_rt5651_ssp2_aअगर1_map));
	पूर्ण
	अगर (ret)
		वापस ret;

	ret = snd_soc_add_card_controls(card, byt_rt5651_controls,
					ARRAY_SIZE(byt_rt5651_controls));
	अगर (ret) अणु
		dev_err(card->dev, "unable to add card controls\n");
		वापस ret;
	पूर्ण

	अगर (byt_rt5651_quirk & BYT_RT5651_MCLK_EN) अणु
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

		अगर (byt_rt5651_quirk & BYT_RT5651_MCLK_25MHZ)
			ret = clk_set_rate(priv->mclk, 25000000);
		अन्यथा
			ret = clk_set_rate(priv->mclk, 19200000);

		अगर (ret)
			dev_err(card->dev, "unable to set MCLK rate\n");
	पूर्ण

	report = 0;
	अगर (BYT_RT5651_JDSRC(byt_rt5651_quirk))
		report = SND_JACK_HEADSET | SND_JACK_BTN_0;
	अन्यथा अगर (priv->hp_detect)
		report = SND_JACK_HEADSET;

	अगर (report) अणु
		ret = snd_soc_card_jack_new(runसमय->card, "Headset",
				    report, &priv->jack, bytcr_jack_pins,
				    ARRAY_SIZE(bytcr_jack_pins));
		अगर (ret) अणु
			dev_err(runसमय->dev, "jack creation failed %d\n", ret);
			वापस ret;
		पूर्ण

		अगर (report & SND_JACK_BTN_0)
			snd_jack_set_key(priv->jack.jack, SND_JACK_BTN_0,
					 KEY_PLAYPAUSE);

		ret = snd_soc_component_set_jack(codec, &priv->jack,
						 priv->hp_detect);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक byt_rt5651_codec_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
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

	अगर ((byt_rt5651_quirk & BYT_RT5651_SSP0_AIF1) ||
	    (byt_rt5651_quirk & BYT_RT5651_SSP0_AIF2)) अणु
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
				  SND_SOC_DAIFMT_CBS_CFS
				  );

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

अटल स्थिर अचिन्हित पूर्णांक rates_48000[] = अणु
	48000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_48000 = अणु
	.count = ARRAY_SIZE(rates_48000),
	.list  = rates_48000,
पूर्ण;

अटल पूर्णांक byt_rt5651_aअगर1_startup(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
			SNDRV_PCM_HW_PARAM_RATE,
			&स्थिरraपूर्णांकs_48000);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops byt_rt5651_aअगर1_ops = अणु
	.startup = byt_rt5651_aअगर1_startup,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops byt_rt5651_be_ssp2_ops = अणु
	.hw_params = byt_rt5651_aअगर1_hw_params,
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
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-10EC5651:00", "rt5651-aif1")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("sst-mfld-platform")));

अटल काष्ठा snd_soc_dai_link byt_rt5651_dais[] = अणु
	[MERR_DPCM_AUDIO] = अणु
		.name = "Audio Port",
		.stream_name = "Audio",
		.nonatomic = true,
		.dynamic = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ops = &byt_rt5651_aअगर1_ops,
		SND_SOC_DAILINK_REG(media, dummy, platक्रमm),
	पूर्ण,
	[MERR_DPCM_DEEP_BUFFER] = अणु
		.name = "Deep-Buffer Audio Port",
		.stream_name = "Deep-Buffer Audio",
		.nonatomic = true,
		.dynamic = 1,
		.dpcm_playback = 1,
		.ops = &byt_rt5651_aअगर1_ops,
		SND_SOC_DAILINK_REG(deepbuffer, dummy, platक्रमm),
	पूर्ण,
	/* CODEC<->CODEC link */
	/* back ends */
	अणु
		.name = "SSP2-Codec",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
						| SND_SOC_DAIFMT_CBS_CFS,
		.be_hw_params_fixup = byt_rt5651_codec_fixup,
		.nonatomic = true,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.init = byt_rt5651_init,
		.ops = &byt_rt5651_be_ssp2_ops,
		SND_SOC_DAILINK_REG(ssp2_port, ssp2_codec, platक्रमm),
	पूर्ण,
पूर्ण;

/* SoC card */
अटल अक्षर byt_rt5651_codec_name[SND_ACPI_I2C_ID_LEN];
#अगर !IS_ENABLED(CONFIG_SND_SOC_INTEL_USER_FRIENDLY_LONG_NAMES)
अटल अक्षर byt_rt5651_दीर्घ_name[50]; /* = "bytcr-rt5651-*-spk-*-mic[-swapped-hp]" */
#पूर्ण_अगर
अटल अक्षर byt_rt5651_components[50]; /* = "cfg-spk:* cfg-mic:*" */

अटल पूर्णांक byt_rt5651_suspend(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_component *component;

	अगर (!BYT_RT5651_JDSRC(byt_rt5651_quirk))
		वापस 0;

	क्रम_each_card_components(card, component) अणु
		अगर (!म_भेद(component->name, byt_rt5651_codec_name)) अणु
			dev_dbg(component->dev, "disabling jack detect before suspend\n");
			snd_soc_component_set_jack(component, शून्य, शून्य);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक byt_rt5651_resume(काष्ठा snd_soc_card *card)
अणु
	काष्ठा byt_rt5651_निजी *priv = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_component *component;

	अगर (!BYT_RT5651_JDSRC(byt_rt5651_quirk))
		वापस 0;

	क्रम_each_card_components(card, component) अणु
		अगर (!म_भेद(component->name, byt_rt5651_codec_name)) अणु
			dev_dbg(component->dev, "re-enabling jack detect after resume\n");
			snd_soc_component_set_jack(component, &priv->jack,
						   priv->hp_detect);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* use space beक्रमe codec name to simplअगरy card ID, and simplअगरy driver name */
#घोषणा SOF_CARD_NAME "bytcht rt5651" /* card name will be 'sof-bytcht rt5651' */
#घोषणा SOF_DRIVER_NAME "SOF"

#घोषणा CARD_NAME "bytcr-rt5651"
#घोषणा DRIVER_NAME शून्य /* card name will be used क्रम driver name */

अटल काष्ठा snd_soc_card byt_rt5651_card = अणु
	.name = CARD_NAME,
	.driver_name = DRIVER_NAME,
	.owner = THIS_MODULE,
	.dai_link = byt_rt5651_dais,
	.num_links = ARRAY_SIZE(byt_rt5651_dais),
	.dapm_widमाला_लो = byt_rt5651_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(byt_rt5651_widमाला_लो),
	.dapm_routes = byt_rt5651_audio_map,
	.num_dapm_routes = ARRAY_SIZE(byt_rt5651_audio_map),
	.fully_routed = true,
	.suspend_pre = byt_rt5651_suspend,
	.resume_post = byt_rt5651_resume,
पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_params ext_amp_enable_gpios = अणु 0, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping cht_rt5651_gpios[] = अणु
	/*
	 * Some boards have I2cSerialBusV2, GpioIo, GpioInt as ACPI resources,
	 * other boards may  have I2cSerialBusV2, GpioInt, GpioIo instead.
	 * We want the GpioIo one क्रम the ext-amp-enable-gpio.
	 */
	अणु "ext-amp-enable-gpios", &ext_amp_enable_gpios, 1, ACPI_GPIO_QUIRK_ONLY_GPIOIO पूर्ण,
	अणु पूर्ण,
पूर्ण;

काष्ठा acpi_chan_package अणु   /* ACPICA seems to require 64 bit पूर्णांकegers */
	u64 aअगर_value;       /* 1: AIF1, 2: AIF2 */
	u64 mघड़ी_value;    /* usually 25MHz (0x17d7940), ignored */
पूर्ण;

अटल पूर्णांक snd_byt_rt5651_mc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अटल स्थिर अक्षर * स्थिर mic_name[] = अणु "dmic", "in1", "in2", "in12" पूर्ण;
	काष्ठा byt_rt5651_निजी *priv;
	काष्ठा snd_soc_acpi_mach *mach;
	स्थिर अक्षर *platक्रमm_name;
	काष्ठा acpi_device *adev;
	काष्ठा device *codec_dev;
	bool sof_parent;
	bool is_bytcr = false;
	पूर्णांक ret_val = 0;
	पूर्णांक dai_index = 0;
	पूर्णांक i;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/* रेजिस्टर the soc card */
	byt_rt5651_card.dev = &pdev->dev;

	mach = byt_rt5651_card.dev->platक्रमm_data;
	snd_soc_card_set_drvdata(&byt_rt5651_card, priv);

	/* fix index of codec dai */
	क्रम (i = 0; i < ARRAY_SIZE(byt_rt5651_dais); i++) अणु
		अगर (!म_भेद(byt_rt5651_dais[i].codecs->name,
			    "i2c-10EC5651:00")) अणु
			dai_index = i;
			अवरोध;
		पूर्ण
	पूर्ण

	/* fixup codec name based on HID */
	adev = acpi_dev_get_first_match_dev(mach->id, शून्य, -1);
	अगर (adev) अणु
		snम_लिखो(byt_rt5651_codec_name, माप(byt_rt5651_codec_name),
			 "i2c-%s", acpi_dev_name(adev));
		put_device(&adev->dev);
		byt_rt5651_dais[dai_index].codecs->name = byt_rt5651_codec_name;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "Error cannot find '%s' dev\n", mach->id);
		वापस -ENODEV;
	पूर्ण

	codec_dev = bus_find_device_by_name(&i2c_bus_type, शून्य,
					    byt_rt5651_codec_name);
	अगर (!codec_dev)
		वापस -EPROBE_DEFER;

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
				byt_rt5651_quirk |= BYT_RT5651_SSP0_AIF1;
			पूर्ण अन्यथा  अगर (chan_package.aअगर_value == 2) अणु
				dev_info(&pdev->dev, "BIOS Routing: AIF2 connected\n");
				byt_rt5651_quirk |= BYT_RT5651_SSP0_AIF2;
			पूर्ण अन्यथा अणु
				dev_info(&pdev->dev, "BIOS Routing isn't valid, ignored\n");
				pkg_found = false;
			पूर्ण
		पूर्ण

		अगर (!pkg_found) अणु
			/* no BIOS indications, assume SSP0-AIF2 connection */
			byt_rt5651_quirk |= BYT_RT5651_SSP0_AIF2;
		पूर्ण
	पूर्ण

	/* check quirks beक्रमe creating card */
	dmi_check_प्रणाली(byt_rt5651_quirk_table);

	अगर (quirk_override != -1) अणु
		dev_info(&pdev->dev, "Overriding quirk 0x%lx => 0x%x\n",
			 byt_rt5651_quirk, quirk_override);
		byt_rt5651_quirk = quirk_override;
	पूर्ण

	/* Must be called beक्रमe रेजिस्टर_card, also see declaration comment. */
	ret_val = byt_rt5651_add_codec_device_props(codec_dev);
	अगर (ret_val) अणु
		put_device(codec_dev);
		वापस ret_val;
	पूर्ण

	/* Cherry Trail devices use an बाह्यal amplअगरier enable gpio */
	अगर (soc_पूर्णांकel_is_cht() && !byt_rt5651_gpios)
		byt_rt5651_gpios = cht_rt5651_gpios;

	अगर (byt_rt5651_gpios) अणु
		devm_acpi_dev_add_driver_gpios(codec_dev, byt_rt5651_gpios);
		priv->ext_amp_gpio = devm_fwnode_gpiod_get(&pdev->dev,
							   codec_dev->fwnode,
							   "ext-amp-enable",
							   GPIOD_OUT_LOW,
							   "speaker-amp");
		अगर (IS_ERR(priv->ext_amp_gpio)) अणु
			ret_val = PTR_ERR(priv->ext_amp_gpio);
			चयन (ret_val) अणु
			हाल -ENOENT:
				priv->ext_amp_gpio = शून्य;
				अवरोध;
			शेष:
				dev_err(&pdev->dev, "Failed to get ext-amp-enable GPIO: %d\n",
					ret_val);
				fallthrough;
			हाल -EPROBE_DEFER:
				put_device(codec_dev);
				वापस ret_val;
			पूर्ण
		पूर्ण
		priv->hp_detect = devm_fwnode_gpiod_get(&pdev->dev,
							codec_dev->fwnode,
							"hp-detect",
							GPIOD_IN,
							"hp-detect");
		अगर (IS_ERR(priv->hp_detect)) अणु
			ret_val = PTR_ERR(priv->hp_detect);
			चयन (ret_val) अणु
			हाल -ENOENT:
				priv->hp_detect = शून्य;
				अवरोध;
			शेष:
				dev_err(&pdev->dev, "Failed to get hp-detect GPIO: %d\n",
					ret_val);
				fallthrough;
			हाल -EPROBE_DEFER:
				put_device(codec_dev);
				वापस ret_val;
			पूर्ण
		पूर्ण
	पूर्ण

	put_device(codec_dev);

	log_quirks(&pdev->dev);

	अगर ((byt_rt5651_quirk & BYT_RT5651_SSP2_AIF2) ||
	    (byt_rt5651_quirk & BYT_RT5651_SSP0_AIF2))
		byt_rt5651_dais[dai_index].codecs->dai_name = "rt5651-aif2";

	अगर ((byt_rt5651_quirk & BYT_RT5651_SSP0_AIF1) ||
	    (byt_rt5651_quirk & BYT_RT5651_SSP0_AIF2))
		byt_rt5651_dais[dai_index].cpus->dai_name = "ssp0-port";

	अगर (byt_rt5651_quirk & BYT_RT5651_MCLK_EN) अणु
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
			byt_rt5651_quirk &= ~BYT_RT5651_MCLK_EN;
		पूर्ण
	पूर्ण

	snम_लिखो(byt_rt5651_components, माप(byt_rt5651_components),
		 "cfg-spk:%s cfg-mic:%s%s",
		 (byt_rt5651_quirk & BYT_RT5651_MONO_SPEAKER) ? "1" : "2",
		 mic_name[BYT_RT5651_MAP(byt_rt5651_quirk)],
		 (byt_rt5651_quirk & BYT_RT5651_HP_LR_SWAPPED) ?
			" cfg-hp:lrswap" : "");
	byt_rt5651_card.components = byt_rt5651_components;
#अगर !IS_ENABLED(CONFIG_SND_SOC_INTEL_USER_FRIENDLY_LONG_NAMES)
	snम_लिखो(byt_rt5651_दीर्घ_name, माप(byt_rt5651_दीर्घ_name),
		 "bytcr-rt5651-%s-spk-%s-mic%s",
		 (byt_rt5651_quirk & BYT_RT5651_MONO_SPEAKER) ?
			"mono" : "stereo",
		 mic_name[BYT_RT5651_MAP(byt_rt5651_quirk)],
		 (byt_rt5651_quirk & BYT_RT5651_HP_LR_SWAPPED) ?
			"-hp-swapped" : "");
	byt_rt5651_card.दीर्घ_name = byt_rt5651_दीर्घ_name;
#पूर्ण_अगर

	/* override plaक्रमm name, अगर required */
	platक्रमm_name = mach->mach_params.platक्रमm;

	ret_val = snd_soc_fixup_dai_links_platक्रमm_name(&byt_rt5651_card,
							platक्रमm_name);
	अगर (ret_val)
		वापस ret_val;

	sof_parent = snd_soc_acpi_sof_parent(&pdev->dev);

	/* set card and driver name */
	अगर (sof_parent) अणु
		byt_rt5651_card.name = SOF_CARD_NAME;
		byt_rt5651_card.driver_name = SOF_DRIVER_NAME;
	पूर्ण अन्यथा अणु
		byt_rt5651_card.name = CARD_NAME;
		byt_rt5651_card.driver_name = DRIVER_NAME;
	पूर्ण

	/* set pm ops */
	अगर (sof_parent)
		pdev->dev.driver->pm = &snd_soc_pm_ops;

	ret_val = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &byt_rt5651_card);

	अगर (ret_val) अणु
		dev_err(&pdev->dev, "devm_snd_soc_register_card failed %d\n",
			ret_val);
		वापस ret_val;
	पूर्ण
	platक्रमm_set_drvdata(pdev, &byt_rt5651_card);
	वापस ret_val;
पूर्ण

अटल काष्ठा platक्रमm_driver snd_byt_rt5651_mc_driver = अणु
	.driver = अणु
		.name = "bytcr_rt5651",
	पूर्ण,
	.probe = snd_byt_rt5651_mc_probe,
पूर्ण;

module_platक्रमm_driver(snd_byt_rt5651_mc_driver);

MODULE_DESCRIPTION("ASoC Intel(R) Baytrail CR Machine driver for RT5651");
MODULE_AUTHOR("Pierre-Louis Bossart <pierre-louis.bossart@linux.intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:bytcr_rt5651");
