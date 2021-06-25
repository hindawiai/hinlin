<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * max98926.c -- ALSA SoC MAX98926 driver
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
#समावेश "max98926.h"

अटल स्थिर अक्षर * स्थिर max98926_boost_voltage_txt[] = अणु
	"8.5V", "8.25V", "8.0V", "7.75V", "7.5V", "7.25V", "7.0V", "6.75V",
	"6.5V", "6.5V", "6.5V", "6.5V", "6.5V", "6.5V", "6.5V", "6.5V"
पूर्ण;

अटल स्थिर अक्षर *स्थिर max98926_pdm_ch_text[] = अणु
	"Current", "Voltage",
पूर्ण;

अटल स्थिर अक्षर *स्थिर max98926_hpf_cutoff_txt[] = अणु
	"Disable", "DC Block", "100Hz",
	"200Hz", "400Hz", "800Hz",
पूर्ण;

अटल स्थिर काष्ठा reg_शेष max98926_reg[] = अणु
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
	अणु 0x1A, 0x04 पूर्ण, /* DAI Clock Mode 1 */
	अणु 0x1B, 0x00 पूर्ण, /* DAI Clock Mode 2 */
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

अटल स्थिर काष्ठा soc_क्रमागत max98926_voltage_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(MAX98926_DAI_CLK_DIV_N_LSBS, 0,
		ARRAY_SIZE(max98926_pdm_ch_text),
		max98926_pdm_ch_text),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new max98926_voltage_control =
	SOC_DAPM_ENUM("Route", max98926_voltage_क्रमागत);

अटल स्थिर काष्ठा soc_क्रमागत max98926_current_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(MAX98926_DAI_CLK_DIV_N_LSBS,
		MAX98926_PDM_SOURCE_1_SHIFT,
		ARRAY_SIZE(max98926_pdm_ch_text),
		max98926_pdm_ch_text),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new max98926_current_control =
	SOC_DAPM_ENUM("Route", max98926_current_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new max98926_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("PCM Single Switch", MAX98926_SPK_AMP,
		MAX98926_INSELECT_MODE_SHIFT, 0, 0),
	SOC_DAPM_SINGLE("PDM Single Switch", MAX98926_SPK_AMP,
		MAX98926_INSELECT_MODE_SHIFT, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new max98926_dai_controls[] = अणु
	SOC_DAPM_SINGLE("Left", MAX98926_GAIN,
		MAX98926_DAC_IN_SEL_SHIFT, 0, 0),
	SOC_DAPM_SINGLE("Right", MAX98926_GAIN,
		MAX98926_DAC_IN_SEL_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("LeftRight", MAX98926_GAIN,
		MAX98926_DAC_IN_SEL_SHIFT, 2, 0),
	SOC_DAPM_SINGLE("(Left+Right)/2 Switch", MAX98926_GAIN,
		MAX98926_DAC_IN_SEL_SHIFT, 3, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget max98926_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("DAI_OUT", "HiFi Playback", 0,
		SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("Amp Enable", शून्य, MAX98926_BLOCK_ENABLE,
		MAX98926_SPK_EN_SHIFT, 0),
	SND_SOC_DAPM_SUPPLY("Global Enable", MAX98926_GLOBAL_ENABLE,
		MAX98926_EN_SHIFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("VI Enable", MAX98926_BLOCK_ENABLE,
		MAX98926_ADC_IMON_EN_WIDTH |
		MAX98926_ADC_VMON_EN_SHIFT,
		0, शून्य, 0),
	SND_SOC_DAPM_PGA("BST Enable", MAX98926_BLOCK_ENABLE,
		MAX98926_BST_EN_SHIFT, 0, शून्य, 0),
	SND_SOC_DAPM_OUTPUT("BE_OUT"),
	SND_SOC_DAPM_MIXER("PCM Sel", MAX98926_SPK_AMP,
		MAX98926_INSELECT_MODE_SHIFT, 0,
		&max98926_mixer_controls[0],
		ARRAY_SIZE(max98926_mixer_controls)),
	SND_SOC_DAPM_MIXER("DAI Sel",
		MAX98926_GAIN, MAX98926_DAC_IN_SEL_SHIFT, 0,
		&max98926_dai_controls[0],
		ARRAY_SIZE(max98926_dai_controls)),
	SND_SOC_DAPM_MUX("PDM CH1 Source",
		MAX98926_DAI_CLK_DIV_N_LSBS,
		MAX98926_PDM_CURRENT_SHIFT,
		0, &max98926_current_control),
	SND_SOC_DAPM_MUX("PDM CH0 Source",
		MAX98926_DAI_CLK_DIV_N_LSBS,
		MAX98926_PDM_VOLTAGE_SHIFT,
		0, &max98926_voltage_control),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route max98926_audio_map[] = अणु
	अणु"VI Enable", शून्य, "DAI_OUT"पूर्ण,
	अणु"DAI Sel", "Left", "VI Enable"पूर्ण,
	अणु"DAI Sel", "Right", "VI Enable"पूर्ण,
	अणु"DAI Sel", "LeftRight", "VI Enable"पूर्ण,
	अणु"DAI Sel", "LeftRightDiv2", "VI Enable"पूर्ण,
	अणु"PCM Sel", "PCM", "DAI Sel"पूर्ण,

	अणु"PDM CH1 Source", "Current", "DAI_OUT"पूर्ण,
	अणु"PDM CH1 Source", "Voltage", "DAI_OUT"पूर्ण,
	अणु"PDM CH0 Source", "Current", "DAI_OUT"पूर्ण,
	अणु"PDM CH0 Source", "Voltage", "DAI_OUT"पूर्ण,
	अणु"PCM Sel", "Analog", "PDM CH1 Source"पूर्ण,
	अणु"PCM Sel", "Analog", "PDM CH0 Source"पूर्ण,
	अणु"Amp Enable", शून्य, "PCM Sel"पूर्ण,

	अणु"BST Enable", शून्य, "Amp Enable"पूर्ण,
	अणु"BE_OUT", शून्य, "BST Enable"पूर्ण,
पूर्ण;

अटल bool max98926_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX98926_VBAT_DATA:
	हाल MAX98926_VBST_DATA:
	हाल MAX98926_LIVE_STATUS0:
	हाल MAX98926_LIVE_STATUS1:
	हाल MAX98926_LIVE_STATUS2:
	हाल MAX98926_STATE0:
	हाल MAX98926_STATE1:
	हाल MAX98926_STATE2:
	हाल MAX98926_FLAG0:
	हाल MAX98926_FLAG1:
	हाल MAX98926_FLAG2:
	हाल MAX98926_VERSION:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool max98926_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX98926_IRQ_CLEAR0:
	हाल MAX98926_IRQ_CLEAR1:
	हाल MAX98926_IRQ_CLEAR2:
	हाल MAX98926_ALC_HOLD_RLS:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण;

अटल DECLARE_TLV_DB_SCALE(max98926_spk_tlv, -600, 100, 0);
अटल DECLARE_TLV_DB_RANGE(max98926_current_tlv,
	0, 11, TLV_DB_SCALE_ITEM(20, 20, 0),
	12, 15, TLV_DB_SCALE_ITEM(320, 40, 0),
);

अटल SOC_ENUM_SINGLE_DECL(max98926_dac_hpf_cutoff,
		MAX98926_FILTERS, MAX98926_DAC_HPF_SHIFT,
		max98926_hpf_cutoff_txt);

अटल SOC_ENUM_SINGLE_DECL(max98926_boost_voltage,
		MAX98926_CONFIGURATION, MAX98926_BST_VOUT_SHIFT,
		max98926_boost_voltage_txt);

अटल स्थिर काष्ठा snd_kcontrol_new max98926_snd_controls[] = अणु
	SOC_SINGLE_TLV("Speaker Volume", MAX98926_GAIN,
		MAX98926_SPK_GAIN_SHIFT,
		(1<<MAX98926_SPK_GAIN_WIDTH)-1, 0,
		max98926_spk_tlv),
	SOC_SINGLE("Ramp Switch", MAX98926_GAIN_RAMPING,
		MAX98926_SPK_RMP_EN_SHIFT, 1, 0),
	SOC_SINGLE("ZCD Switch", MAX98926_GAIN_RAMPING,
		MAX98926_SPK_ZCD_EN_SHIFT, 1, 0),
	SOC_SINGLE("ALC Switch", MAX98926_THRESHOLD,
		MAX98926_ALC_EN_SHIFT, 1, 0),
	SOC_SINGLE("ALC Threshold", MAX98926_THRESHOLD,
		MAX98926_ALC_TH_SHIFT,
		(1<<MAX98926_ALC_TH_WIDTH)-1, 0),
	SOC_ENUM("Boost Output Voltage", max98926_boost_voltage),
	SOC_SINGLE_TLV("Boost Current Limit", MAX98926_BOOST_LIMITER,
		MAX98926_BST_ILIM_SHIFT,
		(1<<MAX98926_BST_ILIM_SHIFT)-1, 0,
		max98926_current_tlv),
	SOC_ENUM("DAC HPF Cutoff", max98926_dac_hpf_cutoff),
	SOC_DOUBLE("PDM Channel One", MAX98926_DAI_CLK_DIV_N_LSBS,
		MAX98926_PDM_CHANNEL_1_SHIFT,
		MAX98926_PDM_CHANNEL_1_HIZ, 1, 0),
	SOC_DOUBLE("PDM Channel Zero", MAX98926_DAI_CLK_DIV_N_LSBS,
		MAX98926_PDM_CHANNEL_0_SHIFT,
		MAX98926_PDM_CHANNEL_0_HIZ, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक rate;
	पूर्णांक  sr;
पूर्ण rate_table[] = अणु
	अणु
		.rate = 8000,
		.sr = 0,
	पूर्ण,
	अणु
		.rate = 11025,
		.sr = 1,
	पूर्ण,
	अणु
		.rate = 12000,
		.sr = 2,
	पूर्ण,
	अणु
		.rate = 16000,
		.sr = 3,
	पूर्ण,
	अणु
		.rate = 22050,
		.sr = 4,
	पूर्ण,
	अणु
		.rate = 24000,
		.sr = 5,
	पूर्ण,
	अणु
		.rate = 32000,
		.sr = 6,
	पूर्ण,
	अणु
		.rate = 44100,
		.sr = 7,
	पूर्ण,
	अणु
		.rate = 48000,
		.sr = 8,
	पूर्ण,
पूर्ण;

अटल व्योम max98926_set_sense_data(काष्ठा max98926_priv *max98926)
अणु
	regmap_update_bits(max98926->regmap,
		MAX98926_DOUT_CFG_VMON,
		MAX98926_DAI_VMON_EN_MASK,
		MAX98926_DAI_VMON_EN_MASK);
	regmap_update_bits(max98926->regmap,
		MAX98926_DOUT_CFG_IMON,
		MAX98926_DAI_IMON_EN_MASK,
		MAX98926_DAI_IMON_EN_MASK);

	अगर (!max98926->पूर्णांकerleave_mode) अणु
		/* set VMON slots */
		regmap_update_bits(max98926->regmap,
			MAX98926_DOUT_CFG_VMON,
			MAX98926_DAI_VMON_SLOT_MASK,
			max98926->v_slot);
		/* set IMON slots */
		regmap_update_bits(max98926->regmap,
			MAX98926_DOUT_CFG_IMON,
			MAX98926_DAI_IMON_SLOT_MASK,
			max98926->i_slot);
	पूर्ण अन्यथा अणु
		/* enable पूर्णांकerleave mode */
		regmap_update_bits(max98926->regmap,
			MAX98926_FORMAT,
			MAX98926_DAI_INTERLEAVE_MASK,
			MAX98926_DAI_INTERLEAVE_MASK);
		/* set पूर्णांकerleave slots */
		regmap_update_bits(max98926->regmap,
			MAX98926_DOUT_CFG_VBAT,
			MAX98926_DAI_INTERLEAVE_SLOT_MASK,
			max98926->v_slot);
	पूर्ण
पूर्ण

अटल पूर्णांक max98926_dai_set_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा max98926_priv *max98926 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक invert = 0;

	dev_dbg(component->dev, "%s: fmt 0x%08X\n", __func__, fmt);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		max98926_set_sense_data(max98926);
		अवरोध;
	शेष:
		dev_err(component->dev, "DAI clock mode unsupported\n");
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		invert = MAX98926_DAI_WCI_MASK;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		invert = MAX98926_DAI_BCI_MASK;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		invert = MAX98926_DAI_BCI_MASK | MAX98926_DAI_WCI_MASK;
		अवरोध;
	शेष:
		dev_err(component->dev, "DAI invert mode unsupported\n");
		वापस -EINVAL;
	पूर्ण

	regmap_ग_लिखो(max98926->regmap,
			MAX98926_FORMAT, MAX98926_DAI_DLY_MASK);
	regmap_update_bits(max98926->regmap, MAX98926_FORMAT,
			MAX98926_DAI_BCI_MASK, invert);
	वापस 0;
पूर्ण

अटल पूर्णांक max98926_dai_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params,
		काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक dai_sr = -EINVAL;
	पूर्णांक rate = params_rate(params), i;
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max98926_priv *max98926 = snd_soc_component_get_drvdata(component);
	पूर्णांक blr_clk_ratio;

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		regmap_update_bits(max98926->regmap,
			MAX98926_FORMAT,
			MAX98926_DAI_CHANSZ_MASK,
			MAX98926_DAI_CHANSZ_16);
		max98926->ch_size = 16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		regmap_update_bits(max98926->regmap,
			MAX98926_FORMAT,
			MAX98926_DAI_CHANSZ_MASK,
			MAX98926_DAI_CHANSZ_24);
		max98926->ch_size = 24;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		regmap_update_bits(max98926->regmap,
			MAX98926_FORMAT,
			MAX98926_DAI_CHANSZ_MASK,
			MAX98926_DAI_CHANSZ_32);
		max98926->ch_size = 32;
		अवरोध;
	शेष:
		dev_dbg(component->dev, "format unsupported %d\n",
			params_क्रमmat(params));
		वापस -EINVAL;
	पूर्ण

	/* BCLK/LRCLK ratio calculation */
	blr_clk_ratio = params_channels(params) * max98926->ch_size;

	चयन (blr_clk_ratio) अणु
	हाल 32:
		regmap_update_bits(max98926->regmap,
			MAX98926_DAI_CLK_MODE2,
			MAX98926_DAI_BSEL_MASK,
			MAX98926_DAI_BSEL_32);
		अवरोध;
	हाल 48:
		regmap_update_bits(max98926->regmap,
			MAX98926_DAI_CLK_MODE2,
			MAX98926_DAI_BSEL_MASK,
			MAX98926_DAI_BSEL_48);
		अवरोध;
	हाल 64:
		regmap_update_bits(max98926->regmap,
			MAX98926_DAI_CLK_MODE2,
			MAX98926_DAI_BSEL_MASK,
			MAX98926_DAI_BSEL_64);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* find the बंदst rate */
	क्रम (i = 0; i < ARRAY_SIZE(rate_table); i++) अणु
		अगर (rate_table[i].rate >= rate) अणु
			dai_sr = rate_table[i].sr;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (dai_sr < 0)
		वापस -EINVAL;

	/* set DAI_SR to correct LRCLK frequency */
	regmap_update_bits(max98926->regmap,
		MAX98926_DAI_CLK_MODE2,
		MAX98926_DAI_SR_MASK, dai_sr << MAX98926_DAI_SR_SHIFT);
	वापस 0;
पूर्ण

#घोषणा MAX98926_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | \
		SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops max98926_dai_ops = अणु
	.set_fmt = max98926_dai_set_fmt,
	.hw_params = max98926_dai_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver max98926_dai[] = अणु
अणु
	.name = "max98926-aif1",
	.playback = अणु
		.stream_name = "HiFi Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = MAX98926_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "HiFi Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = MAX98926_FORMATS,
	पूर्ण,
	.ops = &max98926_dai_ops,
पूर्ण
पूर्ण;

अटल पूर्णांक max98926_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा max98926_priv *max98926 = snd_soc_component_get_drvdata(component);

	max98926->component = component;

	/* Hi-Z all the slots */
	regmap_ग_लिखो(max98926->regmap, MAX98926_DOUT_HIZ_CFG4, 0xF0);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_max98926 = अणु
	.probe			= max98926_probe,
	.controls		= max98926_snd_controls,
	.num_controls		= ARRAY_SIZE(max98926_snd_controls),
	.dapm_routes		= max98926_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(max98926_audio_map),
	.dapm_widमाला_लो		= max98926_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(max98926_dapm_widमाला_लो),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config max98926_regmap = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.max_रेजिस्टर	= MAX98926_VERSION,
	.reg_शेषs	= max98926_reg,
	.num_reg_शेषs = ARRAY_SIZE(max98926_reg),
	.अस्थिर_reg	= max98926_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg	= max98926_पढ़ोable_रेजिस्टर,
	.cache_type		= REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक max98926_i2c_probe(काष्ठा i2c_client *i2c,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret, reg;
	u32 value;
	काष्ठा max98926_priv *max98926;

	max98926 = devm_kzalloc(&i2c->dev,
			माप(*max98926), GFP_KERNEL);
	अगर (!max98926)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, max98926);
	max98926->regmap = devm_regmap_init_i2c(i2c, &max98926_regmap);
	अगर (IS_ERR(max98926->regmap)) अणु
		ret = PTR_ERR(max98926->regmap);
		dev_err(&i2c->dev,
				"Failed to allocate regmap: %d\n", ret);
		जाओ err_out;
	पूर्ण
	अगर (of_property_पढ़ो_bool(i2c->dev.of_node, "interleave-mode"))
		max98926->पूर्णांकerleave_mode = true;

	अगर (!of_property_पढ़ो_u32(i2c->dev.of_node, "vmon-slot-no", &value)) अणु
		अगर (value > MAX98926_DAI_VMON_SLOT_1E_1F) अणु
			dev_err(&i2c->dev, "vmon slot number is wrong:\n");
			वापस -EINVAL;
		पूर्ण
		max98926->v_slot = value;
	पूर्ण
	अगर (!of_property_पढ़ो_u32(i2c->dev.of_node, "imon-slot-no", &value)) अणु
		अगर (value > MAX98926_DAI_IMON_SLOT_1E_1F) अणु
			dev_err(&i2c->dev, "imon slot number is wrong:\n");
			वापस -EINVAL;
		पूर्ण
		max98926->i_slot = value;
	पूर्ण
	ret = regmap_पढ़ो(max98926->regmap,
			MAX98926_VERSION, &reg);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to read: %x\n", reg);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_max98926,
			max98926_dai, ARRAY_SIZE(max98926_dai));
	अगर (ret < 0)
		dev_err(&i2c->dev,
				"Failed to register component: %d\n", ret);
	dev_info(&i2c->dev, "device version: %x\n", reg);
err_out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max98926_i2c_id[] = अणु
	अणु "max98926", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max98926_i2c_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id max98926_of_match[] = अणु
	अणु .compatible = "maxim,max98926", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max98926_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver max98926_i2c_driver = अणु
	.driver = अणु
		.name = "max98926",
		.of_match_table = of_match_ptr(max98926_of_match),
	पूर्ण,
	.probe	= max98926_i2c_probe,
	.id_table = max98926_i2c_id,
पूर्ण;

module_i2c_driver(max98926_i2c_driver)
MODULE_DESCRIPTION("ALSA SoC MAX98926 driver");
MODULE_AUTHOR("Anish kumar <anish.kumar@maximintegrated.com>");
MODULE_LICENSE("GPL");
