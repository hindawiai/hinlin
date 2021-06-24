<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * max98925.c -- ALSA SoC Stereo MAX98925 driver
 * Copyright 2013-15 Maxim Integrated Products
 */
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/cdev.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश "max98925.h"

अटल स्थिर अक्षर *स्थिर dai_text[] = अणु
	"Left", "Right", "LeftRight", "LeftRightDiv2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर max98925_boost_voltage_text[] = अणु
	"8.5V", "8.25V", "8.0V", "7.75V", "7.5V", "7.25V", "7.0V", "6.75V",
	"6.5V", "6.5V", "6.5V", "6.5V", "6.5V", "6.5V",	"6.5V", "6.5V"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(max98925_boost_voltage,
	MAX98925_CONFIGURATION, M98925_BST_VOUT_SHIFT,
	max98925_boost_voltage_text);

अटल स्थिर अक्षर *स्थिर hpf_text[] = अणु
	"Disable", "DC Block", "100Hz",	"200Hz", "400Hz", "800Hz",
पूर्ण;

अटल स्थिर काष्ठा reg_शेष max98925_reg[] = अणु
	अणु 0x0B, 0x00 पूर्ण, /* IRQ Enable0 */
	अणु 0x0C, 0x00 पूर्ण, /* IRQ Enable1 */
	अणु 0x0D, 0x00 पूर्ण, /* IRQ Enable2 */
	अणु 0x0E, 0x00 पूर्ण, /* IRQ Clear0 */
	अणु 0x0F, 0x00 पूर्ण, /* IRQ Clear1 */
	अणु 0x10, 0x00 पूर्ण, /* IRQ Clear2 */
	अणु 0x11, 0xC0 पूर्ण, /* Map0 */
	अणु 0x12, 0x00 पूर्ण, /* Map1 */
	अणु 0x13, 0x00 पूर्ण, /* Map2 */
	अणु 0x14, 0xF0 पूर्ण, /* Map3 */
	अणु 0x15, 0x00 पूर्ण, /* Map4 */
	अणु 0x16, 0xAB पूर्ण, /* Map5 */
	अणु 0x17, 0x89 पूर्ण, /* Map6 */
	अणु 0x18, 0x00 पूर्ण, /* Map7 */
	अणु 0x19, 0x00 पूर्ण, /* Map8 */
	अणु 0x1A, 0x06 पूर्ण, /* DAI Clock Mode 1 */
	अणु 0x1B, 0xC0 पूर्ण, /* DAI Clock Mode 2 */
	अणु 0x1C, 0x00 पूर्ण, /* DAI Clock Divider Denominator MSBs */
	अणु 0x1D, 0x00 पूर्ण, /* DAI Clock Divider Denominator LSBs */
	अणु 0x1E, 0xF0 पूर्ण, /* DAI Clock Divider Numerator MSBs */
	अणु 0x1F, 0x00 पूर्ण, /* DAI Clock Divider Numerator LSBs */
	अणु 0x20, 0x50 पूर्ण, /* Format */
	अणु 0x21, 0x00 पूर्ण, /* TDM Slot Select */
	अणु 0x22, 0x00 पूर्ण, /* DOUT Configuration VMON */
	अणु 0x23, 0x00 पूर्ण, /* DOUT Configuration IMON */
	अणु 0x24, 0x00 पूर्ण, /* DOUT Configuration VBAT */
	अणु 0x25, 0x00 पूर्ण, /* DOUT Configuration VBST */
	अणु 0x26, 0x00 पूर्ण, /* DOUT Configuration FLAG */
	अणु 0x27, 0xFF पूर्ण, /* DOUT HiZ Configuration 1 */
	अणु 0x28, 0xFF पूर्ण, /* DOUT HiZ Configuration 2 */
	अणु 0x29, 0xFF पूर्ण, /* DOUT HiZ Configuration 3 */
	अणु 0x2A, 0xFF पूर्ण, /* DOUT HiZ Configuration 4 */
	अणु 0x2B, 0x02 पूर्ण, /* DOUT Drive Strength */
	अणु 0x2C, 0x90 पूर्ण, /* Filters */
	अणु 0x2D, 0x00 पूर्ण, /* Gain */
	अणु 0x2E, 0x02 पूर्ण, /* Gain Ramping */
	अणु 0x2F, 0x00 पूर्ण, /* Speaker Amplअगरier */
	अणु 0x30, 0x0A पूर्ण, /* Threshold */
	अणु 0x31, 0x00 पूर्ण, /* ALC Attack */
	अणु 0x32, 0x80 पूर्ण, /* ALC Atten and Release */
	अणु 0x33, 0x00 पूर्ण, /* ALC Infinite Hold Release */
	अणु 0x34, 0x92 पूर्ण, /* ALC Configuration */
	अणु 0x35, 0x01 पूर्ण, /* Boost Converter */
	अणु 0x36, 0x00 पूर्ण, /* Block Enable */
	अणु 0x37, 0x00 पूर्ण, /* Configuration */
	अणु 0x38, 0x00 पूर्ण, /* Global Enable */
	अणु 0x3A, 0x00 पूर्ण, /* Boost Limiter */
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत max98925_dai_क्रमागत =
	SOC_ENUM_SINGLE(MAX98925_GAIN, 5, ARRAY_SIZE(dai_text), dai_text);

अटल स्थिर काष्ठा soc_क्रमागत max98925_hpf_क्रमागत =
	SOC_ENUM_SINGLE(MAX98925_FILTERS, 0, ARRAY_SIZE(hpf_text), hpf_text);

अटल स्थिर काष्ठा snd_kcontrol_new max98925_hpf_sel_mux =
	SOC_DAPM_ENUM("Rc Filter MUX Mux", max98925_hpf_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new max98925_dai_sel_mux =
	SOC_DAPM_ENUM("DAI IN MUX Mux", max98925_dai_क्रमागत);

अटल पूर्णांक max98925_dac_event(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा max98925_priv *max98925 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		regmap_update_bits(max98925->regmap,
			MAX98925_BLOCK_ENABLE,
			M98925_BST_EN_MASK |
			M98925_ADC_IMON_EN_MASK | M98925_ADC_VMON_EN_MASK,
			M98925_BST_EN_MASK |
			M98925_ADC_IMON_EN_MASK | M98925_ADC_VMON_EN_MASK);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		regmap_update_bits(max98925->regmap,
			MAX98925_BLOCK_ENABLE, M98925_BST_EN_MASK |
			M98925_ADC_IMON_EN_MASK | M98925_ADC_VMON_EN_MASK, 0);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget max98925_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("DAI_OUT", "HiFi Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MUX("DAI IN MUX", SND_SOC_NOPM, 0, 0,
				&max98925_dai_sel_mux),
	SND_SOC_DAPM_MUX("Rc Filter MUX", SND_SOC_NOPM, 0, 0,
				&max98925_hpf_sel_mux),
	SND_SOC_DAPM_DAC_E("Amp Enable", शून्य, MAX98925_BLOCK_ENABLE,
			M98925_SPK_EN_SHIFT, 0, max98925_dac_event,
			SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("Global Enable", MAX98925_GLOBAL_ENABLE,
			M98925_EN_SHIFT, 0, शून्य, 0),
	SND_SOC_DAPM_OUTPUT("BE_OUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route max98925_audio_map[] = अणु
	अणु"DAI IN MUX", "Left", "DAI_OUT"पूर्ण,
	अणु"DAI IN MUX", "Right", "DAI_OUT"पूर्ण,
	अणु"DAI IN MUX", "LeftRight", "DAI_OUT"पूर्ण,
	अणु"DAI IN MUX", "LeftRightDiv2", "DAI_OUT"पूर्ण,
	अणु"Rc Filter MUX", "Disable", "DAI IN MUX"पूर्ण,
	अणु"Rc Filter MUX", "DC Block", "DAI IN MUX"पूर्ण,
	अणु"Rc Filter MUX", "100Hz", "DAI IN MUX"पूर्ण,
	अणु"Rc Filter MUX", "200Hz", "DAI IN MUX"पूर्ण,
	अणु"Rc Filter MUX", "400Hz", "DAI IN MUX"पूर्ण,
	अणु"Rc Filter MUX", "800Hz", "DAI IN MUX"पूर्ण,
	अणु"Amp Enable", शून्य, "Rc Filter MUX"पूर्ण,
	अणु"BE_OUT", शून्य, "Amp Enable"पूर्ण,
	अणु"BE_OUT", शून्य, "Global Enable"पूर्ण,
पूर्ण;

अटल bool max98925_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX98925_VBAT_DATA:
	हाल MAX98925_VBST_DATA:
	हाल MAX98925_LIVE_STATUS0:
	हाल MAX98925_LIVE_STATUS1:
	हाल MAX98925_LIVE_STATUS2:
	हाल MAX98925_STATE0:
	हाल MAX98925_STATE1:
	हाल MAX98925_STATE2:
	हाल MAX98925_FLAG0:
	हाल MAX98925_FLAG1:
	हाल MAX98925_FLAG2:
	हाल MAX98925_REV_VERSION:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool max98925_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX98925_IRQ_CLEAR0:
	हाल MAX98925_IRQ_CLEAR1:
	हाल MAX98925_IRQ_CLEAR2:
	हाल MAX98925_ALC_HOLD_RLS:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल DECLARE_TLV_DB_SCALE(max98925_spk_tlv, -600, 100, 0);

अटल स्थिर काष्ठा snd_kcontrol_new max98925_snd_controls[] = अणु
	SOC_SINGLE_TLV("Speaker Volume", MAX98925_GAIN,
		M98925_SPK_GAIN_SHIFT, (1<<M98925_SPK_GAIN_WIDTH)-1, 0,
		max98925_spk_tlv),
	SOC_SINGLE("Ramp Switch", MAX98925_GAIN_RAMPING,
				M98925_SPK_RMP_EN_SHIFT, 1, 0),
	SOC_SINGLE("ZCD Switch", MAX98925_GAIN_RAMPING,
				M98925_SPK_ZCD_EN_SHIFT, 1, 0),
	SOC_SINGLE("ALC Switch", MAX98925_THRESHOLD,
				M98925_ALC_EN_SHIFT, 1, 0),
	SOC_SINGLE("ALC Threshold", MAX98925_THRESHOLD, M98925_ALC_TH_SHIFT,
				(1<<M98925_ALC_TH_WIDTH)-1, 0),
	SOC_ENUM("Boost Output Voltage", max98925_boost_voltage),
पूर्ण;

/* codec sample rate and n/m भागiders parameter table */
अटल स्थिर काष्ठा अणु
	पूर्णांक rate;
	पूर्णांक  sr;
	पूर्णांक भागisors[3][2];
पूर्ण rate_table[] = अणु
	अणु
		.rate = 8000,
		.sr = 0,
		.भागisors = अणु अणु1, 375पूर्ण, अणु5, 1764पूर्ण, अणु1, 384पूर्ण पूर्ण
	पूर्ण,
	अणु
		.rate = 11025,
		.sr = 1,
		.भागisors = अणु अणु147, 40000पूर्ण, अणु1, 256पूर्ण, अणु147, 40960पूर्ण पूर्ण
	पूर्ण,
	अणु
		.rate = 12000,
		.sr = 2,
		.भागisors = अणु अणु1, 250पूर्ण, अणु5, 1176पूर्ण, अणु1, 256पूर्ण पूर्ण
	पूर्ण,
	अणु
		.rate = 16000,
		.sr = 3,
		.भागisors = अणु अणु2, 375पूर्ण, अणु5, 882पूर्ण, अणु1, 192पूर्ण पूर्ण
	पूर्ण,
	अणु
		.rate = 22050,
		.sr = 4,
		.भागisors = अणु अणु147, 20000पूर्ण, अणु1, 128पूर्ण, अणु147, 20480पूर्ण पूर्ण
	पूर्ण,
	अणु
		.rate = 24000,
		.sr = 5,
		.भागisors = अणु अणु1, 125पूर्ण, अणु5, 588पूर्ण, अणु1, 128पूर्ण पूर्ण
	पूर्ण,
	अणु
		.rate = 32000,
		.sr = 6,
		.भागisors = अणु अणु4, 375पूर्ण, अणु5, 441पूर्ण, अणु1, 96पूर्ण पूर्ण
	पूर्ण,
	अणु
		.rate = 44100,
		.sr = 7,
		.भागisors = अणु अणु147, 10000पूर्ण, अणु1, 64पूर्ण, अणु147, 10240पूर्ण पूर्ण
	पूर्ण,
	अणु
		.rate = 48000,
		.sr = 8,
		.भागisors = अणु अणु2, 125पूर्ण, अणु5, 294पूर्ण, अणु1, 64पूर्ण पूर्ण
	पूर्ण,
पूर्ण;

अटल अंतरभूत पूर्णांक max98925_rate_value(काष्ठा snd_soc_component *component,
		पूर्णांक rate, पूर्णांक घड़ी, पूर्णांक *value, पूर्णांक *n, पूर्णांक *m)
अणु
	पूर्णांक ret = -EINVAL;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rate_table); i++) अणु
		अगर (rate_table[i].rate >= rate) अणु
			*value = rate_table[i].sr;
			*n = rate_table[i].भागisors[घड़ी][0];
			*m = rate_table[i].भागisors[घड़ी][1];
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम max98925_set_sense_data(काष्ठा max98925_priv *max98925)
अणु
	/* set VMON slots */
	regmap_update_bits(max98925->regmap,
		MAX98925_DOUT_CFG_VMON,
		M98925_DAI_VMON_EN_MASK, M98925_DAI_VMON_EN_MASK);
	regmap_update_bits(max98925->regmap,
		MAX98925_DOUT_CFG_VMON,
		M98925_DAI_VMON_SLOT_MASK,
		max98925->v_slot << M98925_DAI_VMON_SLOT_SHIFT);
	/* set IMON slots */
	regmap_update_bits(max98925->regmap,
		MAX98925_DOUT_CFG_IMON,
		M98925_DAI_IMON_EN_MASK, M98925_DAI_IMON_EN_MASK);
	regmap_update_bits(max98925->regmap,
		MAX98925_DOUT_CFG_IMON,
		M98925_DAI_IMON_SLOT_MASK,
		max98925->i_slot << M98925_DAI_IMON_SLOT_SHIFT);
पूर्ण

अटल पूर्णांक max98925_dai_set_fmt(काष्ठा snd_soc_dai *codec_dai,
				 अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा max98925_priv *max98925 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक invert = 0;

	dev_dbg(component->dev, "%s: fmt 0x%08X\n", __func__, fmt);
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		/* set DAI to slave mode */
		regmap_update_bits(max98925->regmap,
			MAX98925_DAI_CLK_MODE2,
			M98925_DAI_MAS_MASK, 0);
		max98925_set_sense_data(max98925);
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		/*
		 * set left channel DAI to master mode,
		 * right channel always slave
		 */
		regmap_update_bits(max98925->regmap,
			MAX98925_DAI_CLK_MODE2,
			M98925_DAI_MAS_MASK, M98925_DAI_MAS_MASK);
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
	हाल SND_SOC_DAIFMT_CBM_CFS:
	शेष:
		dev_err(component->dev, "DAI clock mode unsupported");
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		invert = M98925_DAI_WCI_MASK;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		invert = M98925_DAI_BCI_MASK;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		invert = M98925_DAI_BCI_MASK | M98925_DAI_WCI_MASK;
		अवरोध;
	शेष:
		dev_err(component->dev, "DAI invert mode unsupported");
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(max98925->regmap, MAX98925_FORMAT,
			M98925_DAI_BCI_MASK | M98925_DAI_WCI_MASK, invert);
	वापस 0;
पूर्ण

अटल पूर्णांक max98925_set_घड़ी(काष्ठा max98925_priv *max98925,
		काष्ठा snd_pcm_hw_params *params)
अणु
	अचिन्हित पूर्णांक dai_sr = 0, घड़ी, mdll, n, m;
	काष्ठा snd_soc_component *component = max98925->component;
	पूर्णांक rate = params_rate(params);
	/* BCLK/LRCLK ratio calculation */
	पूर्णांक blr_clk_ratio = params_channels(params) * max98925->ch_size;

	चयन (blr_clk_ratio) अणु
	हाल 32:
		regmap_update_bits(max98925->regmap,
			MAX98925_DAI_CLK_MODE2,
			M98925_DAI_BSEL_MASK, M98925_DAI_BSEL_32);
		अवरोध;
	हाल 48:
		regmap_update_bits(max98925->regmap,
			MAX98925_DAI_CLK_MODE2,
			M98925_DAI_BSEL_MASK, M98925_DAI_BSEL_48);
		अवरोध;
	हाल 64:
		regmap_update_bits(max98925->regmap,
			MAX98925_DAI_CLK_MODE2,
			M98925_DAI_BSEL_MASK, M98925_DAI_BSEL_64);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (max98925->sysclk) अणु
	हाल 6000000:
		घड़ी = 0;
		mdll  = M98925_MDLL_MULT_MCLKx16;
		अवरोध;
	हाल 11289600:
		घड़ी = 1;
		mdll  = M98925_MDLL_MULT_MCLKx8;
		अवरोध;
	हाल 12000000:
		घड़ी = 0;
		mdll  = M98925_MDLL_MULT_MCLKx8;
		अवरोध;
	हाल 12288000:
		घड़ी = 2;
		mdll  = M98925_MDLL_MULT_MCLKx8;
		अवरोध;
	शेष:
		dev_info(max98925->component->dev, "unsupported sysclk %d\n",
					max98925->sysclk);
		वापस -EINVAL;
	पूर्ण

	अगर (max98925_rate_value(component, rate, घड़ी, &dai_sr, &n, &m))
		वापस -EINVAL;

	/* set DAI_SR to correct LRCLK frequency */
	regmap_update_bits(max98925->regmap,
			MAX98925_DAI_CLK_MODE2,
			M98925_DAI_SR_MASK, dai_sr << M98925_DAI_SR_SHIFT);
	/* set DAI m भागider */
	regmap_ग_लिखो(max98925->regmap,
		MAX98925_DAI_CLK_DIV_M_MSBS, m >> 8);
	regmap_ग_लिखो(max98925->regmap,
		MAX98925_DAI_CLK_DIV_M_LSBS, m & 0xFF);
	/* set DAI n भागider */
	regmap_ग_लिखो(max98925->regmap,
		MAX98925_DAI_CLK_DIV_N_MSBS, n >> 8);
	regmap_ग_लिखो(max98925->regmap,
		MAX98925_DAI_CLK_DIV_N_LSBS, n & 0xFF);
	/* set MDLL */
	regmap_update_bits(max98925->regmap, MAX98925_DAI_CLK_MODE1,
			M98925_MDLL_MULT_MASK, mdll << M98925_MDLL_MULT_SHIFT);
	वापस 0;
पूर्ण

अटल पूर्णांक max98925_dai_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *params,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max98925_priv *max98925 = snd_soc_component_get_drvdata(component);

	चयन (params_width(params)) अणु
	हाल 16:
		regmap_update_bits(max98925->regmap,
				MAX98925_FORMAT,
				M98925_DAI_CHANSZ_MASK, M98925_DAI_CHANSZ_16);
		max98925->ch_size = 16;
		अवरोध;
	हाल 24:
		regmap_update_bits(max98925->regmap,
				MAX98925_FORMAT,
				M98925_DAI_CHANSZ_MASK, M98925_DAI_CHANSZ_24);
		max98925->ch_size = 24;
		अवरोध;
	हाल 32:
		regmap_update_bits(max98925->regmap,
				MAX98925_FORMAT,
				M98925_DAI_CHANSZ_MASK, M98925_DAI_CHANSZ_32);
		max98925->ch_size = 32;
		अवरोध;
	शेष:
		pr_err("%s: format unsupported %d",
				__func__, params_क्रमmat(params));
		वापस -EINVAL;
	पूर्ण
	dev_dbg(component->dev, "%s: format supported %d",
				__func__, params_क्रमmat(params));
	वापस max98925_set_घड़ी(max98925, params);
पूर्ण

अटल पूर्णांक max98925_dai_set_sysclk(काष्ठा snd_soc_dai *dai,
				   पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max98925_priv *max98925 = snd_soc_component_get_drvdata(component);

	चयन (clk_id) अणु
	हाल 0:
		/* use MCLK क्रम Left channel, right channel always BCLK */
		regmap_update_bits(max98925->regmap,
				MAX98925_DAI_CLK_MODE1,
				M98925_DAI_CLK_SOURCE_MASK, 0);
		अवरोध;
	हाल 1:
		/* configure dai घड़ी source to BCLK instead of MCLK */
		regmap_update_bits(max98925->regmap,
				MAX98925_DAI_CLK_MODE1,
				M98925_DAI_CLK_SOURCE_MASK,
				M98925_DAI_CLK_SOURCE_MASK);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	max98925->sysclk = freq;
	वापस 0;
पूर्ण

#घोषणा MAX98925_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops max98925_dai_ops = अणु
	.set_sysclk = max98925_dai_set_sysclk,
	.set_fmt = max98925_dai_set_fmt,
	.hw_params = max98925_dai_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver max98925_dai[] = अणु
	अणु
		.name = "max98925-aif1",
		.playback = अणु
			.stream_name = "HiFi Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000,
			.क्रमmats = MAX98925_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "HiFi Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000,
			.क्रमmats = MAX98925_FORMATS,
		पूर्ण,
		.ops = &max98925_dai_ops,
	पूर्ण
पूर्ण;

अटल पूर्णांक max98925_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा max98925_priv *max98925 = snd_soc_component_get_drvdata(component);

	max98925->component = component;
	regmap_ग_लिखो(max98925->regmap, MAX98925_GLOBAL_ENABLE, 0x00);
	/* It's not the शेष but we need to set DAI_DLY */
	regmap_ग_लिखो(max98925->regmap,
			MAX98925_FORMAT, M98925_DAI_DLY_MASK);
	regmap_ग_लिखो(max98925->regmap, MAX98925_TDM_SLOT_SELECT, 0xC8);
	regmap_ग_लिखो(max98925->regmap, MAX98925_DOUT_HIZ_CFG1, 0xFF);
	regmap_ग_लिखो(max98925->regmap, MAX98925_DOUT_HIZ_CFG2, 0xFF);
	regmap_ग_लिखो(max98925->regmap, MAX98925_DOUT_HIZ_CFG3, 0xFF);
	regmap_ग_लिखो(max98925->regmap, MAX98925_DOUT_HIZ_CFG4, 0xF0);
	regmap_ग_लिखो(max98925->regmap, MAX98925_FILTERS, 0xD8);
	regmap_ग_लिखो(max98925->regmap, MAX98925_ALC_CONFIGURATION, 0xF8);
	regmap_ग_लिखो(max98925->regmap, MAX98925_CONFIGURATION, 0xF0);
	/* Disable ALC muting */
	regmap_ग_लिखो(max98925->regmap, MAX98925_BOOST_LIMITER, 0xF8);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_max98925 = अणु
	.probe			= max98925_probe,
	.controls		= max98925_snd_controls,
	.num_controls		= ARRAY_SIZE(max98925_snd_controls),
	.dapm_routes		= max98925_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(max98925_audio_map),
	.dapm_widमाला_लो		= max98925_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(max98925_dapm_widमाला_लो),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config max98925_regmap = अणु
	.reg_bits         = 8,
	.val_bits         = 8,
	.max_रेजिस्टर     = MAX98925_REV_VERSION,
	.reg_शेषs     = max98925_reg,
	.num_reg_शेषs = ARRAY_SIZE(max98925_reg),
	.अस्थिर_reg     = max98925_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg     = max98925_पढ़ोable_रेजिस्टर,
	.cache_type       = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक max98925_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret, reg;
	u32 value;
	काष्ठा max98925_priv *max98925;

	max98925 = devm_kzalloc(&i2c->dev,
			माप(*max98925), GFP_KERNEL);
	अगर (!max98925)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, max98925);
	max98925->regmap = devm_regmap_init_i2c(i2c, &max98925_regmap);
	अगर (IS_ERR(max98925->regmap)) अणु
		ret = PTR_ERR(max98925->regmap);
		dev_err(&i2c->dev,
				"Failed to allocate regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(i2c->dev.of_node, "vmon-slot-no", &value)) अणु
		अगर (value > M98925_DAI_VMON_SLOT_1E_1F) अणु
			dev_err(&i2c->dev, "vmon slot number is wrong:\n");
			वापस -EINVAL;
		पूर्ण
		max98925->v_slot = value;
	पूर्ण
	अगर (!of_property_पढ़ो_u32(i2c->dev.of_node, "imon-slot-no", &value)) अणु
		अगर (value > M98925_DAI_IMON_SLOT_1E_1F) अणु
			dev_err(&i2c->dev, "imon slot number is wrong:\n");
			वापस -EINVAL;
		पूर्ण
		max98925->i_slot = value;
	पूर्ण

	ret = regmap_पढ़ो(max98925->regmap, MAX98925_REV_VERSION, &reg);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Read revision failed\n");
		वापस ret;
	पूर्ण

	अगर ((reg != MAX98925_VERSION) && (reg != MAX98925_VERSION1)) अणु
		ret = -ENODEV;
		dev_err(&i2c->dev, "Invalid revision (%d 0x%02X)\n",
			ret, reg);
		वापस ret;
	पूर्ण

	dev_info(&i2c->dev, "device version 0x%02X\n", reg);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_max98925,
			max98925_dai, ARRAY_SIZE(max98925_dai));
	अगर (ret < 0)
		dev_err(&i2c->dev,
				"Failed to register component: %d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max98925_i2c_id[] = अणु
	अणु "max98925", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max98925_i2c_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id max98925_of_match[] = अणु
	अणु .compatible = "maxim,max98925", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max98925_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver max98925_i2c_driver = अणु
	.driver = अणु
		.name = "max98925",
		.of_match_table = of_match_ptr(max98925_of_match),
	पूर्ण,
	.probe  = max98925_i2c_probe,
	.id_table = max98925_i2c_id,
पूर्ण;

module_i2c_driver(max98925_i2c_driver)

MODULE_DESCRIPTION("ALSA SoC MAX98925 driver");
MODULE_AUTHOR("Ralph Birt <rdbirt@gmail.com>, Anish kumar <anish.kumar@maximintegrated.com>");
MODULE_LICENSE("GPL");
