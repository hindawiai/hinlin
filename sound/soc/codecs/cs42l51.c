<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cs42l51.c
 *
 * ASoC Driver क्रम Cirrus Logic CS42L51 codecs
 *
 * Copyright (c) 2010 Arnaud Patard <apatard@mandriva.com>
 *
 * Based on cs4270.c - Copyright (c) Freescale Semiconductor
 *
 * For now:
 *  - Only I2C is support. Not SPI
 *  - master mode *NOT* supported
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/pcm.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "cs42l51.h"

क्रमागत master_slave_mode अणु
	MODE_SLAVE,
	MODE_SLAVE_AUTO,
	MODE_MASTER,
पूर्ण;

अटल स्थिर अक्षर * स्थिर cs42l51_supply_names[] = अणु
	"VL",
	"VD",
	"VA",
	"VAHP",
पूर्ण;

काष्ठा cs42l51_निजी अणु
	अचिन्हित पूर्णांक mclk;
	काष्ठा clk *mclk_handle;
	अचिन्हित पूर्णांक audio_mode;	/* The mode (I2S or left-justअगरied) */
	क्रमागत master_slave_mode func;
	काष्ठा regulator_bulk_data supplies[ARRAY_SIZE(cs42l51_supply_names)];
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा regmap *regmap;
पूर्ण;

#घोषणा CS42L51_FORMATS ( \
		SNDRV_PCM_FMTBIT_S16_LE  | SNDRV_PCM_FMTBIT_S16_BE  | \
		SNDRV_PCM_FMTBIT_S18_3LE | SNDRV_PCM_FMTBIT_S18_3BE | \
		SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S20_3BE | \
		SNDRV_PCM_FMTBIT_S24_LE  | SNDRV_PCM_FMTBIT_S24_BE)

अटल पूर्णांक cs42l51_get_chan_mix(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	अचिन्हित दीर्घ value = snd_soc_component_पढ़ो(component, CS42L51_PCM_MIXER)&3;

	चयन (value) अणु
	शेष:
	हाल 0:
		ucontrol->value.क्रमागतerated.item[0] = 0;
		अवरोध;
	/* same value : (L+R)/2 and (R+L)/2 */
	हाल 1:
	हाल 2:
		ucontrol->value.क्रमागतerated.item[0] = 1;
		अवरोध;
	हाल 3:
		ucontrol->value.क्रमागतerated.item[0] = 2;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा CHAN_MIX_NORMAL	0x00
#घोषणा CHAN_MIX_BOTH	0x55
#घोषणा CHAN_MIX_SWAP	0xFF

अटल पूर्णांक cs42l51_set_chan_mix(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	अचिन्हित अक्षर val;

	चयन (ucontrol->value.क्रमागतerated.item[0]) अणु
	शेष:
	हाल 0:
		val = CHAN_MIX_NORMAL;
		अवरोध;
	हाल 1:
		val = CHAN_MIX_BOTH;
		अवरोध;
	हाल 2:
		val = CHAN_MIX_SWAP;
		अवरोध;
	पूर्ण

	snd_soc_component_ग_लिखो(component, CS42L51_PCM_MIXER, val);

	वापस 1;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(adc_pcm_tlv, -5150, 50, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(tone_tlv, -1050, 150, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(aout_tlv, -10200, 50, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(boost_tlv, 1600, 1600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_boost_tlv, 2000, 2000, 0);
अटल स्थिर अक्षर *chan_mix[] = अणु
	"L R",
	"L+R",
	"R L",
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(pga_tlv, -300, 50, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_att_tlv, -9600, 100, 0);

अटल SOC_ENUM_SINGLE_EXT_DECL(cs42l51_chan_mix, chan_mix);

अटल स्थिर काष्ठा snd_kcontrol_new cs42l51_snd_controls[] = अणु
	SOC_DOUBLE_R_SX_TLV("PCM Playback Volume",
			CS42L51_PCMA_VOL, CS42L51_PCMB_VOL,
			0, 0x19, 0x7F, adc_pcm_tlv),
	SOC_DOUBLE_R("PCM Playback Switch",
			CS42L51_PCMA_VOL, CS42L51_PCMB_VOL, 7, 1, 1),
	SOC_DOUBLE_R_SX_TLV("Analog Playback Volume",
			CS42L51_AOUTA_VOL, CS42L51_AOUTB_VOL,
			0, 0x34, 0xE4, aout_tlv),
	SOC_DOUBLE_R_SX_TLV("ADC Mixer Volume",
			CS42L51_ADCA_VOL, CS42L51_ADCB_VOL,
			0, 0x19, 0x7F, adc_pcm_tlv),
	SOC_DOUBLE_R("ADC Mixer Switch",
			CS42L51_ADCA_VOL, CS42L51_ADCB_VOL, 7, 1, 1),
	SOC_DOUBLE_R_SX_TLV("ADC Attenuator Volume",
			CS42L51_ADCA_ATT, CS42L51_ADCB_ATT,
			0, 0xA0, 96, adc_att_tlv),
	SOC_DOUBLE_R_SX_TLV("PGA Volume",
			CS42L51_ALC_PGA_CTL, CS42L51_ALC_PGB_CTL,
			0, 0x1A, 30, pga_tlv),
	SOC_SINGLE("Playback Deemphasis Switch", CS42L51_DAC_CTL, 3, 1, 0),
	SOC_SINGLE("Auto-Mute Switch", CS42L51_DAC_CTL, 2, 1, 0),
	SOC_SINGLE("Soft Ramp Switch", CS42L51_DAC_CTL, 1, 1, 0),
	SOC_SINGLE("Zero Cross Switch", CS42L51_DAC_CTL, 0, 0, 0),
	SOC_DOUBLE_TLV("Mic Boost Volume",
			CS42L51_MIC_CTL, 0, 1, 1, 0, boost_tlv),
	SOC_DOUBLE_TLV("ADC Boost Volume",
		       CS42L51_MIC_CTL, 5, 6, 1, 0, adc_boost_tlv),
	SOC_SINGLE_TLV("Bass Volume", CS42L51_TONE_CTL, 0, 0xf, 1, tone_tlv),
	SOC_SINGLE_TLV("Treble Volume", CS42L51_TONE_CTL, 4, 0xf, 1, tone_tlv),
	SOC_ENUM_EXT("PCM channel mixer",
			cs42l51_chan_mix,
			cs42l51_get_chan_mix, cs42l51_set_chan_mix),
पूर्ण;

/*
 * to घातer करोwn, one must:
 * 1.) Enable the PDN bit
 * 2.) enable घातer-करोwn क्रम the select channels
 * 3.) disable the PDN bit.
 */
अटल पूर्णांक cs42l51_pdn_event(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, CS42L51_POWER_CTL1,
				    CS42L51_POWER_CTL1_PDN,
				    CS42L51_POWER_CTL1_PDN);
		अवरोध;
	शेष:
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, CS42L51_POWER_CTL1,
				    CS42L51_POWER_CTL1_PDN, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *cs42l51_dac_names[] = अणु"Direct PCM",
	"DSP PCM", "ADC"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(cs42l51_dac_mux_क्रमागत,
			    CS42L51_DAC_CTL, 6, cs42l51_dac_names);
अटल स्थिर काष्ठा snd_kcontrol_new cs42l51_dac_mux_controls =
	SOC_DAPM_ENUM("Route", cs42l51_dac_mux_क्रमागत);

अटल स्थिर अक्षर *cs42l51_adcl_names[] = अणु"AIN1 Left", "AIN2 Left",
	"MIC Left", "MIC+preamp Left"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(cs42l51_adcl_mux_क्रमागत,
			    CS42L51_ADC_INPUT, 4, cs42l51_adcl_names);
अटल स्थिर काष्ठा snd_kcontrol_new cs42l51_adcl_mux_controls =
	SOC_DAPM_ENUM("Route", cs42l51_adcl_mux_क्रमागत);

अटल स्थिर अक्षर *cs42l51_adcr_names[] = अणु"AIN1 Right", "AIN2 Right",
	"MIC Right", "MIC+preamp Right"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(cs42l51_adcr_mux_क्रमागत,
			    CS42L51_ADC_INPUT, 6, cs42l51_adcr_names);
अटल स्थिर काष्ठा snd_kcontrol_new cs42l51_adcr_mux_controls =
	SOC_DAPM_ENUM("Route", cs42l51_adcr_mux_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget cs42l51_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("Mic Bias", CS42L51_MIC_POWER_CTL, 1, 1, शून्य,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("Left PGA", CS42L51_POWER_CTL1, 3, 1, शून्य, 0,
		cs42l51_pdn_event, SND_SOC_DAPM_PRE_POST_PMD),
	SND_SOC_DAPM_PGA_E("Right PGA", CS42L51_POWER_CTL1, 4, 1, शून्य, 0,
		cs42l51_pdn_event, SND_SOC_DAPM_PRE_POST_PMD),
	SND_SOC_DAPM_ADC_E("Left ADC", "Left HiFi Capture",
		CS42L51_POWER_CTL1, 1, 1,
		cs42l51_pdn_event, SND_SOC_DAPM_PRE_POST_PMD),
	SND_SOC_DAPM_ADC_E("Right ADC", "Right HiFi Capture",
		CS42L51_POWER_CTL1, 2, 1,
		cs42l51_pdn_event, SND_SOC_DAPM_PRE_POST_PMD),
	SND_SOC_DAPM_DAC_E("Left DAC", शून्य, CS42L51_POWER_CTL1, 5, 1,
			   cs42l51_pdn_event, SND_SOC_DAPM_PRE_POST_PMD),
	SND_SOC_DAPM_DAC_E("Right DAC", शून्य, CS42L51_POWER_CTL1, 6, 1,
			   cs42l51_pdn_event, SND_SOC_DAPM_PRE_POST_PMD),

	/* analog/mic */
	SND_SOC_DAPM_INPUT("AIN1L"),
	SND_SOC_DAPM_INPUT("AIN1R"),
	SND_SOC_DAPM_INPUT("AIN2L"),
	SND_SOC_DAPM_INPUT("AIN2R"),
	SND_SOC_DAPM_INPUT("MICL"),
	SND_SOC_DAPM_INPUT("MICR"),

	SND_SOC_DAPM_MIXER("Mic Preamp Left",
		CS42L51_MIC_POWER_CTL, 2, 1, शून्य, 0),
	SND_SOC_DAPM_MIXER("Mic Preamp Right",
		CS42L51_MIC_POWER_CTL, 3, 1, शून्य, 0),

	/* HP */
	SND_SOC_DAPM_OUTPUT("HPL"),
	SND_SOC_DAPM_OUTPUT("HPR"),

	/* mux */
	SND_SOC_DAPM_MUX("DAC Mux", SND_SOC_NOPM, 0, 0,
		&cs42l51_dac_mux_controls),
	SND_SOC_DAPM_MUX("PGA-ADC Mux Left", SND_SOC_NOPM, 0, 0,
		&cs42l51_adcl_mux_controls),
	SND_SOC_DAPM_MUX("PGA-ADC Mux Right", SND_SOC_NOPM, 0, 0,
		&cs42l51_adcr_mux_controls),
पूर्ण;

अटल पूर्णांक mclk_event(काष्ठा snd_soc_dapm_widget *w,
		      काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	काष्ठा cs42l51_निजी *cs42l51 = snd_soc_component_get_drvdata(comp);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		वापस clk_prepare_enable(cs42l51->mclk_handle);
	हाल SND_SOC_DAPM_POST_PMD:
		/* Delay mclk shutकरोwn to fulfill घातer-करोwn sequence requirements */
		msleep(20);
		clk_disable_unprepare(cs42l51->mclk_handle);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget cs42l51_dapm_mclk_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("MCLK", SND_SOC_NOPM, 0, 0, mclk_event,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs42l51_routes[] = अणु
	अणु"HPL", शून्य, "Left DAC"पूर्ण,
	अणु"HPR", शून्य, "Right DAC"पूर्ण,

	अणु"Right DAC", शून्य, "DAC Mux"पूर्ण,
	अणु"Left DAC", शून्य, "DAC Mux"पूर्ण,

	अणु"DAC Mux", "Direct PCM", "Playback"पूर्ण,
	अणु"DAC Mux", "DSP PCM", "Playback"पूर्ण,

	अणु"Left ADC", शून्य, "Left PGA"पूर्ण,
	अणु"Right ADC", शून्य, "Right PGA"पूर्ण,

	अणु"Mic Preamp Left",  शून्य,  "MICL"पूर्ण,
	अणु"Mic Preamp Right", शून्य,  "MICR"पूर्ण,

	अणु"PGA-ADC Mux Left",  "AIN1 Left",        "AIN1L" पूर्ण,
	अणु"PGA-ADC Mux Left",  "AIN2 Left",        "AIN2L" पूर्ण,
	अणु"PGA-ADC Mux Left",  "MIC Left",         "MICL"  पूर्ण,
	अणु"PGA-ADC Mux Left",  "MIC+preamp Left",  "Mic Preamp Left" पूर्ण,
	अणु"PGA-ADC Mux Right", "AIN1 Right",       "AIN1R" पूर्ण,
	अणु"PGA-ADC Mux Right", "AIN2 Right",       "AIN2R" पूर्ण,
	अणु"PGA-ADC Mux Right", "MIC Right",        "MICR" पूर्ण,
	अणु"PGA-ADC Mux Right", "MIC+preamp Right", "Mic Preamp Right" पूर्ण,

	अणु"Left PGA", शून्य, "PGA-ADC Mux Left"पूर्ण,
	अणु"Right PGA", शून्य, "PGA-ADC Mux Right"पूर्ण,
पूर्ण;

अटल पूर्णांक cs42l51_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक क्रमmat)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cs42l51_निजी *cs42l51 = snd_soc_component_get_drvdata(component);

	चयन (क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_LEFT_J:
	हाल SND_SOC_DAIFMT_RIGHT_J:
		cs42l51->audio_mode = क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK;
		अवरोध;
	शेष:
		dev_err(component->dev, "invalid DAI format\n");
		वापस -EINVAL;
	पूर्ण

	चयन (क्रमmat & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		cs42l51->func = MODE_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		cs42l51->func = MODE_SLAVE_AUTO;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unknown master/slave configuration\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा cs42l51_ratios अणु
	अचिन्हित पूर्णांक ratio;
	अचिन्हित अक्षर speed_mode;
	अचिन्हित अक्षर mclk;
पूर्ण;

अटल काष्ठा cs42l51_ratios slave_ratios[] = अणु
	अणु  512, CS42L51_QSM_MODE, 0 पूर्ण, अणु  768, CS42L51_QSM_MODE, 0 पूर्ण,
	अणु 1024, CS42L51_QSM_MODE, 0 पूर्ण, अणु 1536, CS42L51_QSM_MODE, 0 पूर्ण,
	अणु 2048, CS42L51_QSM_MODE, 0 पूर्ण, अणु 3072, CS42L51_QSM_MODE, 0 पूर्ण,
	अणु  256, CS42L51_HSM_MODE, 0 पूर्ण, अणु  384, CS42L51_HSM_MODE, 0 पूर्ण,
	अणु  512, CS42L51_HSM_MODE, 0 पूर्ण, अणु  768, CS42L51_HSM_MODE, 0 पूर्ण,
	अणु 1024, CS42L51_HSM_MODE, 0 पूर्ण, अणु 1536, CS42L51_HSM_MODE, 0 पूर्ण,
	अणु  128, CS42L51_SSM_MODE, 0 पूर्ण, अणु  192, CS42L51_SSM_MODE, 0 पूर्ण,
	अणु  256, CS42L51_SSM_MODE, 0 पूर्ण, अणु  384, CS42L51_SSM_MODE, 0 पूर्ण,
	अणु  512, CS42L51_SSM_MODE, 0 पूर्ण, अणु  768, CS42L51_SSM_MODE, 0 पूर्ण,
	अणु  128, CS42L51_DSM_MODE, 0 पूर्ण, अणु  192, CS42L51_DSM_MODE, 0 पूर्ण,
	अणु  256, CS42L51_DSM_MODE, 0 पूर्ण, अणु  384, CS42L51_DSM_MODE, 0 पूर्ण,
पूर्ण;

अटल काष्ठा cs42l51_ratios slave_स्वतः_ratios[] = अणु
	अणु 1024, CS42L51_QSM_MODE, 0 पूर्ण, अणु 1536, CS42L51_QSM_MODE, 0 पूर्ण,
	अणु 2048, CS42L51_QSM_MODE, 1 पूर्ण, अणु 3072, CS42L51_QSM_MODE, 1 पूर्ण,
	अणु  512, CS42L51_HSM_MODE, 0 पूर्ण, अणु  768, CS42L51_HSM_MODE, 0 पूर्ण,
	अणु 1024, CS42L51_HSM_MODE, 1 पूर्ण, अणु 1536, CS42L51_HSM_MODE, 1 पूर्ण,
	अणु  256, CS42L51_SSM_MODE, 0 पूर्ण, अणु  384, CS42L51_SSM_MODE, 0 पूर्ण,
	अणु  512, CS42L51_SSM_MODE, 1 पूर्ण, अणु  768, CS42L51_SSM_MODE, 1 पूर्ण,
	अणु  128, CS42L51_DSM_MODE, 0 पूर्ण, अणु  192, CS42L51_DSM_MODE, 0 पूर्ण,
	अणु  256, CS42L51_DSM_MODE, 1 पूर्ण, अणु  384, CS42L51_DSM_MODE, 1 पूर्ण,
पूर्ण;

/*
 * Master mode mclk/fs ratios.
 * Recommended configurations are SSM क्रम 4-50khz and DSM क्रम 50-100kHz ranges
 * The table below provides support of following ratios:
 * 128: SSM (%128) with भाग2 disabled
 * 256: SSM (%128) with भाग2 enabled
 * In both हालs, अगर sampling rate is above 50kHz, SSM is overridden
 * with DSM (%128) configuration
 */
अटल काष्ठा cs42l51_ratios master_ratios[] = अणु
	अणु 128, CS42L51_SSM_MODE, 0 पूर्ण, अणु 256, CS42L51_SSM_MODE, 1 पूर्ण,
पूर्ण;

अटल पूर्णांक cs42l51_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cs42l51_निजी *cs42l51 = snd_soc_component_get_drvdata(component);

	cs42l51->mclk = freq;
	वापस 0;
पूर्ण

अटल पूर्णांक cs42l51_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs42l51_निजी *cs42l51 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक ratio;
	काष्ठा cs42l51_ratios *ratios = शून्य;
	पूर्णांक nr_ratios = 0;
	पूर्णांक पूर्णांकf_ctl, घातer_ctl, fmt, mode;

	चयन (cs42l51->func) अणु
	हाल MODE_MASTER:
		ratios = master_ratios;
		nr_ratios = ARRAY_SIZE(master_ratios);
		अवरोध;
	हाल MODE_SLAVE:
		ratios = slave_ratios;
		nr_ratios = ARRAY_SIZE(slave_ratios);
		अवरोध;
	हाल MODE_SLAVE_AUTO:
		ratios = slave_स्वतः_ratios;
		nr_ratios = ARRAY_SIZE(slave_स्वतः_ratios);
		अवरोध;
	पूर्ण

	/* Figure out which MCLK/LRCK ratio to use */
	rate = params_rate(params);     /* Sampling rate, in Hz */
	ratio = cs42l51->mclk / rate;    /* MCLK/LRCK ratio */
	क्रम (i = 0; i < nr_ratios; i++) अणु
		अगर (ratios[i].ratio == ratio)
			अवरोध;
	पूर्ण

	अगर (i == nr_ratios) अणु
		/* We did not find a matching ratio */
		dev_err(component->dev, "could not find matching ratio\n");
		वापस -EINVAL;
	पूर्ण

	पूर्णांकf_ctl = snd_soc_component_पढ़ो(component, CS42L51_INTF_CTL);
	घातer_ctl = snd_soc_component_पढ़ो(component, CS42L51_MIC_POWER_CTL);

	पूर्णांकf_ctl &= ~(CS42L51_INTF_CTL_MASTER | CS42L51_INTF_CTL_ADC_I2S
			| CS42L51_INTF_CTL_DAC_FORMAT(7));
	घातer_ctl &= ~(CS42L51_MIC_POWER_CTL_SPEED(3)
			| CS42L51_MIC_POWER_CTL_MCLK_DIV2);

	चयन (cs42l51->func) अणु
	हाल MODE_MASTER:
		पूर्णांकf_ctl |= CS42L51_INTF_CTL_MASTER;
		mode = ratios[i].speed_mode;
		/* Force DSM mode अगर sampling rate is above 50kHz */
		अगर (rate > 50000)
			mode = CS42L51_DSM_MODE;
		घातer_ctl |= CS42L51_MIC_POWER_CTL_SPEED(mode);
		/*
		 * Auto detect mode is not applicable क्रम master mode and has to
		 * be disabled. Otherwise SPEED[1:0] bits will be ignored.
		 */
		घातer_ctl &= ~CS42L51_MIC_POWER_CTL_AUTO;
		अवरोध;
	हाल MODE_SLAVE:
		घातer_ctl |= CS42L51_MIC_POWER_CTL_SPEED(ratios[i].speed_mode);
		अवरोध;
	हाल MODE_SLAVE_AUTO:
		घातer_ctl |= CS42L51_MIC_POWER_CTL_AUTO;
		अवरोध;
	पूर्ण

	चयन (cs42l51->audio_mode) अणु
	हाल SND_SOC_DAIFMT_I2S:
		पूर्णांकf_ctl |= CS42L51_INTF_CTL_ADC_I2S;
		पूर्णांकf_ctl |= CS42L51_INTF_CTL_DAC_FORMAT(CS42L51_DAC_DIF_I2S);
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		पूर्णांकf_ctl |= CS42L51_INTF_CTL_DAC_FORMAT(CS42L51_DAC_DIF_LJ24);
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		चयन (params_width(params)) अणु
		हाल 16:
			fmt = CS42L51_DAC_DIF_RJ16;
			अवरोध;
		हाल 18:
			fmt = CS42L51_DAC_DIF_RJ18;
			अवरोध;
		हाल 20:
			fmt = CS42L51_DAC_DIF_RJ20;
			अवरोध;
		हाल 24:
			fmt = CS42L51_DAC_DIF_RJ24;
			अवरोध;
		शेष:
			dev_err(component->dev, "unknown format\n");
			वापस -EINVAL;
		पूर्ण
		पूर्णांकf_ctl |= CS42L51_INTF_CTL_DAC_FORMAT(fmt);
		अवरोध;
	शेष:
		dev_err(component->dev, "unknown format\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ratios[i].mclk)
		घातer_ctl |= CS42L51_MIC_POWER_CTL_MCLK_DIV2;

	ret = snd_soc_component_ग_लिखो(component, CS42L51_INTF_CTL, पूर्णांकf_ctl);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_component_ग_लिखो(component, CS42L51_MIC_POWER_CTL, घातer_ctl);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक cs42l51_dai_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक reg;
	पूर्णांक mask = CS42L51_DAC_OUT_CTL_DACA_MUTE|CS42L51_DAC_OUT_CTL_DACB_MUTE;

	reg = snd_soc_component_पढ़ो(component, CS42L51_DAC_OUT_CTL);

	अगर (mute)
		reg |= mask;
	अन्यथा
		reg &= ~mask;

	वापस snd_soc_component_ग_लिखो(component, CS42L51_DAC_OUT_CTL, reg);
पूर्ण

अटल पूर्णांक cs42l51_of_xlate_dai_id(काष्ठा snd_soc_component *component,
				   काष्ठा device_node *endpoपूर्णांक)
अणु
	/* वापस dai id 0, whatever the endpoपूर्णांक index */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops cs42l51_dai_ops = अणु
	.hw_params      = cs42l51_hw_params,
	.set_sysclk     = cs42l51_set_dai_sysclk,
	.set_fmt        = cs42l51_set_dai_fmt,
	.mute_stream    = cs42l51_dai_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver cs42l51_dai = अणु
	.name = "cs42l51-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = CS42L51_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = CS42L51_FORMATS,
	पूर्ण,
	.ops = &cs42l51_dai_ops,
पूर्ण;

अटल पूर्णांक cs42l51_component_probe(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret, reg;
	काष्ठा snd_soc_dapm_context *dapm;
	काष्ठा cs42l51_निजी *cs42l51;

	cs42l51 = snd_soc_component_get_drvdata(component);
	dapm = snd_soc_component_get_dapm(component);

	अगर (cs42l51->mclk_handle)
		snd_soc_dapm_new_controls(dapm, cs42l51_dapm_mclk_widमाला_लो, 1);

	/*
	 * DAC configuration
	 * - Use संकेत processor
	 * - स्वतः mute
	 * - vol changes immediate
	 * - no de-emphasize
	 */
	reg = CS42L51_DAC_CTL_DATA_SEL(1)
		| CS42L51_DAC_CTL_AMUTE | CS42L51_DAC_CTL_DACSZ(0);
	ret = snd_soc_component_ग_लिखो(component, CS42L51_DAC_CTL, reg);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_device_cs42l51 = अणु
	.probe			= cs42l51_component_probe,
	.controls		= cs42l51_snd_controls,
	.num_controls		= ARRAY_SIZE(cs42l51_snd_controls),
	.dapm_widमाला_लो		= cs42l51_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(cs42l51_dapm_widमाला_लो),
	.dapm_routes		= cs42l51_routes,
	.num_dapm_routes	= ARRAY_SIZE(cs42l51_routes),
	.of_xlate_dai_id	= cs42l51_of_xlate_dai_id,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल bool cs42l51_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS42L51_POWER_CTL1:
	हाल CS42L51_MIC_POWER_CTL:
	हाल CS42L51_INTF_CTL:
	हाल CS42L51_MIC_CTL:
	हाल CS42L51_ADC_CTL:
	हाल CS42L51_ADC_INPUT:
	हाल CS42L51_DAC_OUT_CTL:
	हाल CS42L51_DAC_CTL:
	हाल CS42L51_ALC_PGA_CTL:
	हाल CS42L51_ALC_PGB_CTL:
	हाल CS42L51_ADCA_ATT:
	हाल CS42L51_ADCB_ATT:
	हाल CS42L51_ADCA_VOL:
	हाल CS42L51_ADCB_VOL:
	हाल CS42L51_PCMA_VOL:
	हाल CS42L51_PCMB_VOL:
	हाल CS42L51_BEEP_FREQ:
	हाल CS42L51_BEEP_VOL:
	हाल CS42L51_BEEP_CONF:
	हाल CS42L51_TONE_CTL:
	हाल CS42L51_AOUTA_VOL:
	हाल CS42L51_AOUTB_VOL:
	हाल CS42L51_PCM_MIXER:
	हाल CS42L51_LIMIT_THRES_DIS:
	हाल CS42L51_LIMIT_REL:
	हाल CS42L51_LIMIT_ATT:
	हाल CS42L51_ALC_EN:
	हाल CS42L51_ALC_REL:
	हाल CS42L51_ALC_THRES:
	हाल CS42L51_NOISE_CONF:
	हाल CS42L51_CHARGE_FREQ:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs42l51_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS42L51_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs42l51_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS42L51_CHIP_REV_ID:
	हाल CS42L51_POWER_CTL1:
	हाल CS42L51_MIC_POWER_CTL:
	हाल CS42L51_INTF_CTL:
	हाल CS42L51_MIC_CTL:
	हाल CS42L51_ADC_CTL:
	हाल CS42L51_ADC_INPUT:
	हाल CS42L51_DAC_OUT_CTL:
	हाल CS42L51_DAC_CTL:
	हाल CS42L51_ALC_PGA_CTL:
	हाल CS42L51_ALC_PGB_CTL:
	हाल CS42L51_ADCA_ATT:
	हाल CS42L51_ADCB_ATT:
	हाल CS42L51_ADCA_VOL:
	हाल CS42L51_ADCB_VOL:
	हाल CS42L51_PCMA_VOL:
	हाल CS42L51_PCMB_VOL:
	हाल CS42L51_BEEP_FREQ:
	हाल CS42L51_BEEP_VOL:
	हाल CS42L51_BEEP_CONF:
	हाल CS42L51_TONE_CTL:
	हाल CS42L51_AOUTA_VOL:
	हाल CS42L51_AOUTB_VOL:
	हाल CS42L51_PCM_MIXER:
	हाल CS42L51_LIMIT_THRES_DIS:
	हाल CS42L51_LIMIT_REL:
	हाल CS42L51_LIMIT_ATT:
	हाल CS42L51_ALC_EN:
	हाल CS42L51_ALC_REL:
	हाल CS42L51_ALC_THRES:
	हाल CS42L51_NOISE_CONF:
	हाल CS42L51_STATUS:
	हाल CS42L51_CHARGE_FREQ:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

स्थिर काष्ठा regmap_config cs42l51_regmap = अणु
	.reg_bits = 8,
	.reg_stride = 1,
	.val_bits = 8,
	.use_single_ग_लिखो = true,
	.पढ़ोable_reg = cs42l51_पढ़ोable_reg,
	.अस्थिर_reg = cs42l51_अस्थिर_reg,
	.ग_लिखोable_reg = cs42l51_ग_लिखोable_reg,
	.max_रेजिस्टर = CS42L51_CHARGE_FREQ,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;
EXPORT_SYMBOL_GPL(cs42l51_regmap);

पूर्णांक cs42l51_probe(काष्ठा device *dev, काष्ठा regmap *regmap)
अणु
	काष्ठा cs42l51_निजी *cs42l51;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret, i;

	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	cs42l51 = devm_kzalloc(dev, माप(काष्ठा cs42l51_निजी),
			       GFP_KERNEL);
	अगर (!cs42l51)
		वापस -ENOMEM;

	dev_set_drvdata(dev, cs42l51);
	cs42l51->regmap = regmap;

	cs42l51->mclk_handle = devm_clk_get(dev, "MCLK");
	अगर (IS_ERR(cs42l51->mclk_handle)) अणु
		अगर (PTR_ERR(cs42l51->mclk_handle) != -ENOENT)
			वापस PTR_ERR(cs42l51->mclk_handle);
		cs42l51->mclk_handle = शून्य;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(cs42l51->supplies); i++)
		cs42l51->supplies[i].supply = cs42l51_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(cs42l51->supplies),
				      cs42l51->supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(cs42l51->supplies),
				    cs42l51->supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	cs42l51->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						      GPIOD_OUT_LOW);
	अगर (IS_ERR(cs42l51->reset_gpio))
		वापस PTR_ERR(cs42l51->reset_gpio);

	अगर (cs42l51->reset_gpio) अणु
		dev_dbg(dev, "Release reset gpio\n");
		gpiod_set_value_cansleep(cs42l51->reset_gpio, 0);
		mdelay(2);
	पूर्ण

	/* Verअगरy that we have a CS42L51 */
	ret = regmap_पढ़ो(regmap, CS42L51_CHIP_REV_ID, &val);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read I2C\n");
		जाओ error;
	पूर्ण

	अगर ((val != CS42L51_MK_CHIP_REV(CS42L51_CHIP_ID, CS42L51_CHIP_REV_A)) &&
	    (val != CS42L51_MK_CHIP_REV(CS42L51_CHIP_ID, CS42L51_CHIP_REV_B))) अणु
		dev_err(dev, "Invalid chip id: %x\n", val);
		ret = -ENODEV;
		जाओ error;
	पूर्ण
	dev_info(dev, "Cirrus Logic CS42L51, Revision: %02X\n",
		 val & CS42L51_CHIP_REV_MASK);

	ret = devm_snd_soc_रेजिस्टर_component(dev,
			&soc_component_device_cs42l51, &cs42l51_dai, 1);
	अगर (ret < 0)
		जाओ error;

	वापस 0;

error:
	regulator_bulk_disable(ARRAY_SIZE(cs42l51->supplies),
			       cs42l51->supplies);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cs42l51_probe);

पूर्णांक cs42l51_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा cs42l51_निजी *cs42l51 = dev_get_drvdata(dev);

	gpiod_set_value_cansleep(cs42l51->reset_gpio, 1);

	वापस regulator_bulk_disable(ARRAY_SIZE(cs42l51->supplies),
				      cs42l51->supplies);
पूर्ण
EXPORT_SYMBOL_GPL(cs42l51_हटाओ);

पूर्णांक __maybe_unused cs42l51_suspend(काष्ठा device *dev)
अणु
	काष्ठा cs42l51_निजी *cs42l51 = dev_get_drvdata(dev);

	regcache_cache_only(cs42l51->regmap, true);
	regcache_mark_dirty(cs42l51->regmap);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cs42l51_suspend);

पूर्णांक __maybe_unused cs42l51_resume(काष्ठा device *dev)
अणु
	काष्ठा cs42l51_निजी *cs42l51 = dev_get_drvdata(dev);

	regcache_cache_only(cs42l51->regmap, false);

	वापस regcache_sync(cs42l51->regmap);
पूर्ण
EXPORT_SYMBOL_GPL(cs42l51_resume);

स्थिर काष्ठा of_device_id cs42l51_of_match[] = अणु
	अणु .compatible = "cirrus,cs42l51", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cs42l51_of_match);
EXPORT_SYMBOL_GPL(cs42l51_of_match);

MODULE_AUTHOR("Arnaud Patard <arnaud.patard@rtp-net.org>");
MODULE_DESCRIPTION("Cirrus Logic CS42L51 ALSA SoC Codec Driver");
MODULE_LICENSE("GPL");
