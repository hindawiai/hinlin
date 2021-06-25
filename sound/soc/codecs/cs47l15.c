<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// ALSA SoC Audio driver क्रम CS47L15 codec
//
// Copyright (C) 2016-2019 Cirrus Logic, Inc. and
//                         Cirrus Logic International Semiconductor Ltd.
//

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#समावेश <linux/irqchip/irq-madera.h>
#समावेश <linux/mfd/madera/core.h>
#समावेश <linux/mfd/madera/रेजिस्टरs.h>

#समावेश "madera.h"
#समावेश "wm_adsp.h"

#घोषणा CS47L15_NUM_ADSP 1
#घोषणा CS47L15_MONO_OUTPUTS 1

/* Mid-mode रेजिस्टरs */
#घोषणा CS47L15_ADC_INT_BIAS_MASK	0x3800
#घोषणा CS47L15_ADC_INT_BIAS_SHIFT	11
#घोषणा CS47L15_PGA_BIAS_SEL_MASK	0x03
#घोषणा CS47L15_PGA_BIAS_SEL_SHIFT	0

#घोषणा DRV_NAME "cs47l15-codec"

काष्ठा cs47l15 अणु
	काष्ठा madera_priv core;
	काष्ठा madera_fll fll[2];

	bool in1_lp_mode;
पूर्ण;

अटल स्थिर काष्ठा wm_adsp_region cs47l15_dsp1_regions[] = अणु
	अणु .type = WMFW_ADSP2_PM, .base = 0x080000 पूर्ण,
	अणु .type = WMFW_ADSP2_ZM, .base = 0x0e0000 पूर्ण,
	अणु .type = WMFW_ADSP2_XM, .base = 0x0a0000 पूर्ण,
	अणु .type = WMFW_ADSP2_YM, .base = 0x0c0000 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर cs47l15_outdemux_texts[] = अणु
	"HPOUT",
	"EPOUT",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(cs47l15_outdemux_क्रमागत, SND_SOC_NOPM, 0,
			    cs47l15_outdemux_texts);

अटल स्थिर काष्ठा snd_kcontrol_new cs47l15_outdemux =
	SOC_DAPM_ENUM_EXT("HPOUT1 Demux", cs47l15_outdemux_क्रमागत,
			  madera_out1_demux_get, madera_out1_demux_put);

अटल पूर्णांक cs47l15_adsp_घातer_ev(काष्ठा snd_soc_dapm_widget *w,
				 काष्ठा snd_kcontrol *kcontrol,
				 पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा cs47l15 *cs47l15 = snd_soc_component_get_drvdata(component);
	काष्ठा madera_priv *priv = &cs47l15->core;
	काष्ठा madera *madera = priv->madera;
	अचिन्हित पूर्णांक freq;
	पूर्णांक ret;

	ret = regmap_पढ़ो(madera->regmap, MADERA_DSP_CLOCK_2, &freq);
	अगर (ret != 0) अणु
		dev_err(madera->dev,
			"Failed to read MADERA_DSP_CLOCK_2: %d\n", ret);
		वापस ret;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		ret = madera_set_adsp_clk(&cs47l15->core, w->shअगरt, freq);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस wm_adsp_early_event(w, kcontrol, event);
पूर्ण

#घोषणा CS47L15_NG_SRC(name, base) \
	SOC_SINGLE(name " NG HPOUT1L Switch",  base,  0, 1, 0), \
	SOC_SINGLE(name " NG HPOUT1R Switch",  base,  1, 1, 0), \
	SOC_SINGLE(name " NG SPKOUTL Switch",  base,  6, 1, 0), \
	SOC_SINGLE(name " NG SPKDAT1L Switch", base,  8, 1, 0), \
	SOC_SINGLE(name " NG SPKDAT1R Switch", base,  9, 1, 0)

अटल पूर्णांक cs47l15_in1_adc_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा cs47l15 *cs47l15 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = !!cs47l15->in1_lp_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक cs47l15_in1_adc_put(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा cs47l15 *cs47l15 = snd_soc_component_get_drvdata(component);

	चयन (ucontrol->value.पूर्णांकeger.value[0]) अणु
	हाल 0:
		/* Set IN1 to normal mode */
		snd_soc_component_update_bits(component, MADERA_DMIC1L_CONTROL,
					      MADERA_IN1_OSR_MASK,
					      5 << MADERA_IN1_OSR_SHIFT);
		snd_soc_component_update_bits(component, CS47L15_ADC_INT_BIAS,
					      CS47L15_ADC_INT_BIAS_MASK,
					      4 << CS47L15_ADC_INT_BIAS_SHIFT);
		snd_soc_component_update_bits(component, CS47L15_PGA_BIAS_SEL,
					      CS47L15_PGA_BIAS_SEL_MASK, 0);
		cs47l15->in1_lp_mode = false;
		अवरोध;
	शेष:
		/* Set IN1 to LP mode */
		snd_soc_component_update_bits(component, MADERA_DMIC1L_CONTROL,
					      MADERA_IN1_OSR_MASK,
					      4 << MADERA_IN1_OSR_SHIFT);
		snd_soc_component_update_bits(component, CS47L15_ADC_INT_BIAS,
					      CS47L15_ADC_INT_BIAS_MASK,
					      1 << CS47L15_ADC_INT_BIAS_SHIFT);
		snd_soc_component_update_bits(component, CS47L15_PGA_BIAS_SEL,
					      CS47L15_PGA_BIAS_SEL_MASK,
					      3 << CS47L15_PGA_BIAS_SEL_SHIFT);
		cs47l15->in1_lp_mode = true;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new cs47l15_snd_controls[] = अणु
SOC_ENUM("IN1 OSR", madera_in_dmic_osr[0]),
SOC_ENUM("IN2 OSR", madera_in_dmic_osr[1]),

SOC_SINGLE_RANGE_TLV("IN1L Volume", MADERA_IN1L_CONTROL,
		     MADERA_IN1L_PGA_VOL_SHIFT, 0x40, 0x5f, 0, madera_ana_tlv),
SOC_SINGLE_RANGE_TLV("IN1R Volume", MADERA_IN1R_CONTROL,
		     MADERA_IN1R_PGA_VOL_SHIFT, 0x40, 0x5f, 0, madera_ana_tlv),

SOC_ENUM("IN HPF Cutoff Frequency", madera_in_hpf_cut_क्रमागत),

SOC_SINGLE("IN1L HPF Switch", MADERA_IN1L_CONTROL, MADERA_IN1L_HPF_SHIFT, 1, 0),
SOC_SINGLE("IN1R HPF Switch", MADERA_IN1R_CONTROL, MADERA_IN1R_HPF_SHIFT, 1, 0),
SOC_SINGLE("IN2L HPF Switch", MADERA_IN2L_CONTROL, MADERA_IN2L_HPF_SHIFT, 1, 0),
SOC_SINGLE("IN2R HPF Switch", MADERA_IN2R_CONTROL, MADERA_IN2R_HPF_SHIFT, 1, 0),

SOC_SINGLE_TLV("IN1L Digital Volume", MADERA_ADC_DIGITAL_VOLUME_1L,
	       MADERA_IN1L_DIG_VOL_SHIFT, 0xbf, 0, madera_digital_tlv),
SOC_SINGLE_TLV("IN1R Digital Volume", MADERA_ADC_DIGITAL_VOLUME_1R,
	       MADERA_IN1R_DIG_VOL_SHIFT, 0xbf, 0, madera_digital_tlv),
SOC_SINGLE_TLV("IN2L Digital Volume", MADERA_ADC_DIGITAL_VOLUME_2L,
	       MADERA_IN2L_DIG_VOL_SHIFT, 0xbf, 0, madera_digital_tlv),
SOC_SINGLE_TLV("IN2R Digital Volume", MADERA_ADC_DIGITAL_VOLUME_2R,
	       MADERA_IN2R_DIG_VOL_SHIFT, 0xbf, 0, madera_digital_tlv),

SOC_ENUM("Input Ramp Up", madera_in_vi_ramp),
SOC_ENUM("Input Ramp Down", madera_in_vd_ramp),

MADERA_MIXER_CONTROLS("EQ1", MADERA_EQ1MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("EQ2", MADERA_EQ2MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("EQ3", MADERA_EQ3MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("EQ4", MADERA_EQ4MIX_INPUT_1_SOURCE),

MADERA_EQ_CONTROL("EQ1 Coefficients", MADERA_EQ1_2),
SOC_SINGLE_TLV("EQ1 B1 Volume", MADERA_EQ1_1, MADERA_EQ1_B1_GAIN_SHIFT,
	       24, 0, madera_eq_tlv),
SOC_SINGLE_TLV("EQ1 B2 Volume", MADERA_EQ1_1, MADERA_EQ1_B2_GAIN_SHIFT,
	       24, 0, madera_eq_tlv),
SOC_SINGLE_TLV("EQ1 B3 Volume", MADERA_EQ1_1, MADERA_EQ1_B3_GAIN_SHIFT,
	       24, 0, madera_eq_tlv),
SOC_SINGLE_TLV("EQ1 B4 Volume", MADERA_EQ1_2, MADERA_EQ1_B4_GAIN_SHIFT,
	       24, 0, madera_eq_tlv),
SOC_SINGLE_TLV("EQ1 B5 Volume", MADERA_EQ1_2, MADERA_EQ1_B5_GAIN_SHIFT,
	       24, 0, madera_eq_tlv),

MADERA_EQ_CONTROL("EQ2 Coefficients", MADERA_EQ2_2),
SOC_SINGLE_TLV("EQ2 B1 Volume", MADERA_EQ2_1, MADERA_EQ2_B1_GAIN_SHIFT,
	       24, 0, madera_eq_tlv),
SOC_SINGLE_TLV("EQ2 B2 Volume", MADERA_EQ2_1, MADERA_EQ2_B2_GAIN_SHIFT,
	       24, 0, madera_eq_tlv),
SOC_SINGLE_TLV("EQ2 B3 Volume", MADERA_EQ2_1, MADERA_EQ2_B3_GAIN_SHIFT,
	       24, 0, madera_eq_tlv),
SOC_SINGLE_TLV("EQ2 B4 Volume", MADERA_EQ2_2, MADERA_EQ2_B4_GAIN_SHIFT,
	       24, 0, madera_eq_tlv),
SOC_SINGLE_TLV("EQ2 B5 Volume", MADERA_EQ2_2, MADERA_EQ2_B5_GAIN_SHIFT,
	       24, 0, madera_eq_tlv),

MADERA_EQ_CONTROL("EQ3 Coefficients", MADERA_EQ3_2),
SOC_SINGLE_TLV("EQ3 B1 Volume", MADERA_EQ3_1, MADERA_EQ3_B1_GAIN_SHIFT,
	       24, 0, madera_eq_tlv),
SOC_SINGLE_TLV("EQ3 B2 Volume", MADERA_EQ3_1, MADERA_EQ3_B2_GAIN_SHIFT,
	       24, 0, madera_eq_tlv),
SOC_SINGLE_TLV("EQ3 B3 Volume", MADERA_EQ3_1, MADERA_EQ3_B3_GAIN_SHIFT,
	       24, 0, madera_eq_tlv),
SOC_SINGLE_TLV("EQ3 B4 Volume", MADERA_EQ3_2, MADERA_EQ3_B4_GAIN_SHIFT,
	       24, 0, madera_eq_tlv),
SOC_SINGLE_TLV("EQ3 B5 Volume", MADERA_EQ3_2, MADERA_EQ3_B5_GAIN_SHIFT,
	       24, 0, madera_eq_tlv),

MADERA_EQ_CONTROL("EQ4 Coefficients", MADERA_EQ4_2),
SOC_SINGLE_TLV("EQ4 B1 Volume", MADERA_EQ4_1, MADERA_EQ4_B1_GAIN_SHIFT,
	       24, 0, madera_eq_tlv),
SOC_SINGLE_TLV("EQ4 B2 Volume", MADERA_EQ4_1, MADERA_EQ4_B2_GAIN_SHIFT,
	       24, 0, madera_eq_tlv),
SOC_SINGLE_TLV("EQ4 B3 Volume", MADERA_EQ4_1, MADERA_EQ4_B3_GAIN_SHIFT,
	       24, 0, madera_eq_tlv),
SOC_SINGLE_TLV("EQ4 B4 Volume", MADERA_EQ4_2, MADERA_EQ4_B4_GAIN_SHIFT,
	       24, 0, madera_eq_tlv),
SOC_SINGLE_TLV("EQ4 B5 Volume", MADERA_EQ4_2, MADERA_EQ4_B5_GAIN_SHIFT,
	       24, 0, madera_eq_tlv),

MADERA_MIXER_CONTROLS("DRC1L", MADERA_DRC1LMIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("DRC1R", MADERA_DRC1RMIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("DRC2L", MADERA_DRC2LMIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("DRC2R", MADERA_DRC2RMIX_INPUT_1_SOURCE),

SND_SOC_BYTES_MASK("DRC1", MADERA_DRC1_CTRL1, 5,
		   MADERA_DRC1R_ENA | MADERA_DRC1L_ENA),
SND_SOC_BYTES_MASK("DRC2", MADERA_DRC2_CTRL1, 5,
		   MADERA_DRC2R_ENA | MADERA_DRC2L_ENA),

MADERA_MIXER_CONTROLS("LHPF1", MADERA_HPLP1MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("LHPF2", MADERA_HPLP2MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("LHPF3", MADERA_HPLP3MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("LHPF4", MADERA_HPLP4MIX_INPUT_1_SOURCE),

MADERA_LHPF_CONTROL("LHPF1 Coefficients", MADERA_HPLPF1_2),
MADERA_LHPF_CONTROL("LHPF2 Coefficients", MADERA_HPLPF2_2),
MADERA_LHPF_CONTROL("LHPF3 Coefficients", MADERA_HPLPF3_2),
MADERA_LHPF_CONTROL("LHPF4 Coefficients", MADERA_HPLPF4_2),

SOC_ENUM("LHPF1 Mode", madera_lhpf1_mode),
SOC_ENUM("LHPF2 Mode", madera_lhpf2_mode),
SOC_ENUM("LHPF3 Mode", madera_lhpf3_mode),
SOC_ENUM("LHPF4 Mode", madera_lhpf4_mode),

MADERA_RATE_ENUM("ISRC1 FSL", madera_isrc_fsl[0]),
MADERA_RATE_ENUM("ISRC2 FSL", madera_isrc_fsl[1]),
MADERA_RATE_ENUM("ISRC1 FSH", madera_isrc_fsh[0]),
MADERA_RATE_ENUM("ISRC2 FSH", madera_isrc_fsh[1]),

WM_ADSP2_PRELOAD_SWITCH("DSP1", 1),

MADERA_MIXER_CONTROLS("DSP1L", MADERA_DSP1LMIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("DSP1R", MADERA_DSP1RMIX_INPUT_1_SOURCE),

SOC_SINGLE_TLV("Noise Generator Volume", MADERA_COMFORT_NOISE_GENERATOR,
	       MADERA_NOISE_GEN_GAIN_SHIFT, 0x16, 0, madera_noise_tlv),

MADERA_MIXER_CONTROLS("HPOUT1L", MADERA_OUT1LMIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("HPOUT1R", MADERA_OUT1RMIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("SPKOUTL", MADERA_OUT4LMIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("SPKDAT1L", MADERA_OUT5LMIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("SPKDAT1R", MADERA_OUT5RMIX_INPUT_1_SOURCE),

SOC_SINGLE("HPOUT1 SC Protect Switch", MADERA_HP1_SHORT_CIRCUIT_CTRL,
	   MADERA_HP1_SC_ENA_SHIFT, 1, 0),

SOC_SINGLE("SPKDAT1 High Performance Switch", MADERA_OUTPUT_PATH_CONFIG_5L,
	   MADERA_OUT5_OSR_SHIFT, 1, 0),

SOC_DOUBLE_R("HPOUT1 Digital Switch", MADERA_DAC_DIGITAL_VOLUME_1L,
	     MADERA_DAC_DIGITAL_VOLUME_1R, MADERA_OUT1L_MUTE_SHIFT, 1, 1),
SOC_SINGLE("Speaker Digital Switch", MADERA_DAC_DIGITAL_VOLUME_4L,
	   MADERA_OUT4L_MUTE_SHIFT, 1, 1),
SOC_DOUBLE_R("SPKDAT1 Digital Switch", MADERA_DAC_DIGITAL_VOLUME_5L,
	     MADERA_DAC_DIGITAL_VOLUME_5R, MADERA_OUT5L_MUTE_SHIFT, 1, 1),

SOC_DOUBLE_R_TLV("HPOUT1 Digital Volume", MADERA_DAC_DIGITAL_VOLUME_1L,
		 MADERA_DAC_DIGITAL_VOLUME_1R, MADERA_OUT1L_VOL_SHIFT,
		 0xbf, 0, madera_digital_tlv),
SOC_SINGLE_TLV("Speaker Digital Volume", MADERA_DAC_DIGITAL_VOLUME_4L,
	       MADERA_OUT4L_VOL_SHIFT, 0xbf, 0, madera_digital_tlv),
SOC_DOUBLE_R_TLV("SPKDAT1 Digital Volume", MADERA_DAC_DIGITAL_VOLUME_5L,
		 MADERA_DAC_DIGITAL_VOLUME_5R, MADERA_OUT5L_VOL_SHIFT,
		 0xbf, 0, madera_digital_tlv),

SOC_DOUBLE("SPKDAT1 Switch", MADERA_PDM_SPK1_CTRL_1, MADERA_SPK1L_MUTE_SHIFT,
	   MADERA_SPK1R_MUTE_SHIFT, 1, 1),

SOC_ENUM("Output Ramp Up", madera_out_vi_ramp),
SOC_ENUM("Output Ramp Down", madera_out_vd_ramp),

SOC_SINGLE("Noise Gate Switch", MADERA_NOISE_GATE_CONTROL,
	   MADERA_NGATE_ENA_SHIFT, 1, 0),
SOC_SINGLE_TLV("Noise Gate Threshold Volume", MADERA_NOISE_GATE_CONTROL,
	       MADERA_NGATE_THR_SHIFT, 7, 1, madera_ng_tlv),
SOC_ENUM("Noise Gate Hold", madera_ng_hold),

SOC_SINGLE_BOOL_EXT("IN1 LP Mode Switch", 0,
		    cs47l15_in1_adc_get, cs47l15_in1_adc_put),

CS47L15_NG_SRC("HPOUT1L", MADERA_NOISE_GATE_SELECT_1L),
CS47L15_NG_SRC("HPOUT1R", MADERA_NOISE_GATE_SELECT_1R),
CS47L15_NG_SRC("SPKOUTL", MADERA_NOISE_GATE_SELECT_4L),
CS47L15_NG_SRC("SPKDAT1L", MADERA_NOISE_GATE_SELECT_5L),
CS47L15_NG_SRC("SPKDAT1R", MADERA_NOISE_GATE_SELECT_5R),

MADERA_MIXER_CONTROLS("AIF1TX1", MADERA_AIF1TX1MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF1TX2", MADERA_AIF1TX2MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF1TX3", MADERA_AIF1TX3MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF1TX4", MADERA_AIF1TX4MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF1TX5", MADERA_AIF1TX5MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF1TX6", MADERA_AIF1TX6MIX_INPUT_1_SOURCE),

MADERA_MIXER_CONTROLS("AIF2TX1", MADERA_AIF2TX1MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF2TX2", MADERA_AIF2TX2MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF2TX3", MADERA_AIF2TX3MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF2TX4", MADERA_AIF2TX4MIX_INPUT_1_SOURCE),

MADERA_MIXER_CONTROLS("AIF3TX1", MADERA_AIF3TX1MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF3TX2", MADERA_AIF3TX2MIX_INPUT_1_SOURCE),

MADERA_GAINMUX_CONTROLS("SPDIF1TX1", MADERA_SPDIF1TX1MIX_INPUT_1_SOURCE),
MADERA_GAINMUX_CONTROLS("SPDIF1TX2", MADERA_SPDIF1TX2MIX_INPUT_1_SOURCE),

WM_ADSP_FW_CONTROL("DSP1", 0),
पूर्ण;

MADERA_MIXER_ENUMS(EQ1, MADERA_EQ1MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(EQ2, MADERA_EQ2MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(EQ3, MADERA_EQ3MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(EQ4, MADERA_EQ4MIX_INPUT_1_SOURCE);

MADERA_MIXER_ENUMS(DRC1L, MADERA_DRC1LMIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(DRC1R, MADERA_DRC1RMIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(DRC2L, MADERA_DRC2LMIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(DRC2R, MADERA_DRC2RMIX_INPUT_1_SOURCE);

MADERA_MIXER_ENUMS(LHPF1, MADERA_HPLP1MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(LHPF2, MADERA_HPLP2MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(LHPF3, MADERA_HPLP3MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(LHPF4, MADERA_HPLP4MIX_INPUT_1_SOURCE);

MADERA_MIXER_ENUMS(DSP1L, MADERA_DSP1LMIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(DSP1R, MADERA_DSP1RMIX_INPUT_1_SOURCE);
MADERA_DSP_AUX_ENUMS(DSP1, MADERA_DSP1AUX1MIX_INPUT_1_SOURCE);

MADERA_MIXER_ENUMS(PWM1, MADERA_PWM1MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(PWM2, MADERA_PWM2MIX_INPUT_1_SOURCE);

MADERA_MIXER_ENUMS(OUT1L, MADERA_OUT1LMIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(OUT1R, MADERA_OUT1RMIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(SPKOUTL, MADERA_OUT4LMIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(SPKDAT1L, MADERA_OUT5LMIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(SPKDAT1R, MADERA_OUT5RMIX_INPUT_1_SOURCE);

MADERA_MIXER_ENUMS(AIF1TX1, MADERA_AIF1TX1MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF1TX2, MADERA_AIF1TX2MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF1TX3, MADERA_AIF1TX3MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF1TX4, MADERA_AIF1TX4MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF1TX5, MADERA_AIF1TX5MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF1TX6, MADERA_AIF1TX6MIX_INPUT_1_SOURCE);

MADERA_MIXER_ENUMS(AIF2TX1, MADERA_AIF2TX1MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF2TX2, MADERA_AIF2TX2MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF2TX3, MADERA_AIF2TX3MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF2TX4, MADERA_AIF2TX4MIX_INPUT_1_SOURCE);

MADERA_MIXER_ENUMS(AIF3TX1, MADERA_AIF3TX1MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF3TX2, MADERA_AIF3TX2MIX_INPUT_1_SOURCE);

MADERA_MUX_ENUMS(SPD1TX1, MADERA_SPDIF1TX1MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(SPD1TX2, MADERA_SPDIF1TX2MIX_INPUT_1_SOURCE);

MADERA_MUX_ENUMS(ISRC1INT1, MADERA_ISRC1INT1MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(ISRC1INT2, MADERA_ISRC1INT2MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(ISRC1INT3, MADERA_ISRC1INT3MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(ISRC1INT4, MADERA_ISRC1INT4MIX_INPUT_1_SOURCE);

MADERA_MUX_ENUMS(ISRC1DEC1, MADERA_ISRC1DEC1MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(ISRC1DEC2, MADERA_ISRC1DEC2MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(ISRC1DEC3, MADERA_ISRC1DEC3MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(ISRC1DEC4, MADERA_ISRC1DEC4MIX_INPUT_1_SOURCE);

MADERA_MUX_ENUMS(ISRC2INT1, MADERA_ISRC2INT1MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(ISRC2INT2, MADERA_ISRC2INT2MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(ISRC2INT3, MADERA_ISRC2INT3MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(ISRC2INT4, MADERA_ISRC2INT4MIX_INPUT_1_SOURCE);

MADERA_MUX_ENUMS(ISRC2DEC1, MADERA_ISRC2DEC1MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(ISRC2DEC2, MADERA_ISRC2DEC2MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(ISRC2DEC3, MADERA_ISRC2DEC3MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(ISRC2DEC4, MADERA_ISRC2DEC4MIX_INPUT_1_SOURCE);

अटल स्थिर अक्षर * स्थिर cs47l15_aec_loopback_texts[] = अणु
	"HPOUT1L", "HPOUT1R", "SPKOUTL", "SPKDAT1L", "SPKDAT1R",
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक cs47l15_aec_loopback_values[] = अणु
	0, 1, 6, 8, 9,
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत cs47l15_aec1_loopback =
	SOC_VALUE_ENUM_SINGLE(MADERA_DAC_AEC_CONTROL_1,
			      MADERA_AEC1_LOOPBACK_SRC_SHIFT, 0xf,
			      ARRAY_SIZE(cs47l15_aec_loopback_texts),
			      cs47l15_aec_loopback_texts,
			      cs47l15_aec_loopback_values);

अटल स्थिर काष्ठा soc_क्रमागत cs47l15_aec2_loopback =
	SOC_VALUE_ENUM_SINGLE(MADERA_DAC_AEC_CONTROL_2,
			      MADERA_AEC2_LOOPBACK_SRC_SHIFT, 0xf,
			      ARRAY_SIZE(cs47l15_aec_loopback_texts),
			      cs47l15_aec_loopback_texts,
			      cs47l15_aec_loopback_values);

अटल स्थिर काष्ठा snd_kcontrol_new cs47l15_aec_loopback_mux[] = अणु
	SOC_DAPM_ENUM("AEC1 Loopback", cs47l15_aec1_loopback),
	SOC_DAPM_ENUM("AEC2 Loopback", cs47l15_aec2_loopback),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget cs47l15_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_SUPPLY("SYSCLK", MADERA_SYSTEM_CLOCK_1, MADERA_SYSCLK_ENA_SHIFT,
		    0, madera_sysclk_ev,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		    SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("OPCLK", MADERA_OUTPUT_SYSTEM_CLOCK,
		    MADERA_OPCLK_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("DSPCLK", MADERA_DSP_CLOCK_1, MADERA_DSP_CLK_ENA_SHIFT,
		    0, madera_clk_ev,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

SND_SOC_DAPM_REGULATOR_SUPPLY("CPVDD1", 20, 0),
SND_SOC_DAPM_REGULATOR_SUPPLY("MICVDD", 0, SND_SOC_DAPM_REGULATOR_BYPASS),
SND_SOC_DAPM_REGULATOR_SUPPLY("SPKVDD", 0, 0),

SND_SOC_DAPM_SUPPLY("MICBIAS1", MADERA_MIC_BIAS_CTRL_1,
		    MADERA_MICB1_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_SUPPLY("MICBIAS1A", MADERA_MIC_BIAS_CTRL_5,
		    MADERA_MICB1A_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("MICBIAS1B", MADERA_MIC_BIAS_CTRL_5,
		    MADERA_MICB1B_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("MICBIAS1C", MADERA_MIC_BIAS_CTRL_5,
		    MADERA_MICB1C_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_SUPPLY("FXCLK", SND_SOC_NOPM,
		    MADERA_DOM_GRP_FX, 0,
		    madera_करोमुख्य_clk_ev,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("ISRC1CLK", SND_SOC_NOPM,
		    MADERA_DOM_GRP_ISRC1, 0,
		    madera_करोमुख्य_clk_ev,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("ISRC2CLK", SND_SOC_NOPM,
		    MADERA_DOM_GRP_ISRC2, 0,
		    madera_करोमुख्य_clk_ev,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("OUTCLK", SND_SOC_NOPM,
		    MADERA_DOM_GRP_OUT, 0,
		    madera_करोमुख्य_clk_ev,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("SPDCLK", SND_SOC_NOPM,
		    MADERA_DOM_GRP_SPD, 0,
		    madera_करोमुख्य_clk_ev,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("DSP1CLK", SND_SOC_NOPM,
		    MADERA_DOM_GRP_DSP1, 0,
		    madera_करोमुख्य_clk_ev,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("AIF1TXCLK", SND_SOC_NOPM,
		    MADERA_DOM_GRP_AIF1, 0,
		    madera_करोमुख्य_clk_ev,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("AIF2TXCLK", SND_SOC_NOPM,
		    MADERA_DOM_GRP_AIF2, 0,
		    madera_करोमुख्य_clk_ev,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("AIF3TXCLK", SND_SOC_NOPM,
		    MADERA_DOM_GRP_AIF3, 0,
		    madera_करोमुख्य_clk_ev,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("PWMCLK", SND_SOC_NOPM,
		    MADERA_DOM_GRP_PWM, 0,
		    madera_करोमुख्य_clk_ev,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

SND_SOC_DAPM_SIGGEN("TONE"),
SND_SOC_DAPM_SIGGEN("NOISE"),

SND_SOC_DAPM_INPUT("IN1ALN"),
SND_SOC_DAPM_INPUT("IN1ALP"),
SND_SOC_DAPM_INPUT("IN1BLN"),
SND_SOC_DAPM_INPUT("IN1BLP"),
SND_SOC_DAPM_INPUT("IN1ARN"),
SND_SOC_DAPM_INPUT("IN1ARP"),
SND_SOC_DAPM_INPUT("IN1BRN"),
SND_SOC_DAPM_INPUT("IN1BRP"),
SND_SOC_DAPM_INPUT("IN2N"),
SND_SOC_DAPM_INPUT("IN2P"),
SND_SOC_DAPM_INPUT("SPKRXDAT"),

SND_SOC_DAPM_MUX("IN1L Analog Mux", SND_SOC_NOPM, 0, 0, &madera_inmux[0]),
SND_SOC_DAPM_MUX("IN1R Analog Mux", SND_SOC_NOPM, 0, 0, &madera_inmux[1]),

SND_SOC_DAPM_MUX("IN1L Mode", SND_SOC_NOPM, 0, 0, &madera_inmode[0]),
SND_SOC_DAPM_MUX("IN1R Mode", SND_SOC_NOPM, 0, 0, &madera_inmode[0]),

SND_SOC_DAPM_MUX("IN2L Mode", SND_SOC_NOPM, 0, 0, &madera_inmode[1]),
SND_SOC_DAPM_MUX("IN2R Mode", SND_SOC_NOPM, 0, 0, &madera_inmode[1]),

SND_SOC_DAPM_OUTPUT("DRC1 Signal Activity"),
SND_SOC_DAPM_OUTPUT("DRC2 Signal Activity"),

SND_SOC_DAPM_OUTPUT("DSP Trigger Out"),

SND_SOC_DAPM_DEMUX("HPOUT1 Demux", SND_SOC_NOPM, 0, 0, &cs47l15_outdemux),
SND_SOC_DAPM_MUX("HPOUT1 Mono Mux", SND_SOC_NOPM, 0, 0, &cs47l15_outdemux),

SND_SOC_DAPM_PGA("PWM1 Driver", MADERA_PWM_DRIVE_1, MADERA_PWM1_ENA_SHIFT,
		 0, शून्य, 0),
SND_SOC_DAPM_PGA("PWM2 Driver", MADERA_PWM_DRIVE_1, MADERA_PWM2_ENA_SHIFT,
		 0, शून्य, 0),

SND_SOC_DAPM_AIF_OUT("AIF1TX1", शून्य, 0,
		     MADERA_AIF1_TX_ENABLES, MADERA_AIF1TX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX2", शून्य, 1,
		     MADERA_AIF1_TX_ENABLES, MADERA_AIF1TX2_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX3", शून्य, 2,
		     MADERA_AIF1_TX_ENABLES, MADERA_AIF1TX3_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX4", शून्य, 3,
		     MADERA_AIF1_TX_ENABLES, MADERA_AIF1TX4_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX5", शून्य, 4,
		     MADERA_AIF1_TX_ENABLES, MADERA_AIF1TX5_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX6", शून्य, 5,
		     MADERA_AIF1_TX_ENABLES, MADERA_AIF1TX6_ENA_SHIFT, 0),

SND_SOC_DAPM_AIF_OUT("AIF2TX1", शून्य, 0,
		     MADERA_AIF2_TX_ENABLES, MADERA_AIF2TX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF2TX2", शून्य, 1,
		     MADERA_AIF2_TX_ENABLES, MADERA_AIF2TX2_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF2TX3", शून्य, 2,
		     MADERA_AIF2_TX_ENABLES, MADERA_AIF2TX3_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF2TX4", शून्य, 3,
		     MADERA_AIF2_TX_ENABLES, MADERA_AIF2TX4_ENA_SHIFT, 0),

SND_SOC_DAPM_AIF_OUT("AIF3TX1", शून्य, 0,
		     MADERA_AIF3_TX_ENABLES, MADERA_AIF3TX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF3TX2", शून्य, 1,
		     MADERA_AIF3_TX_ENABLES, MADERA_AIF3TX2_ENA_SHIFT, 0),

SND_SOC_DAPM_PGA_E("OUT1L", SND_SOC_NOPM,
		   MADERA_OUT1L_ENA_SHIFT, 0, शून्य, 0, madera_hp_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT1R", SND_SOC_NOPM,
		   MADERA_OUT1R_ENA_SHIFT, 0, शून्य, 0, madera_hp_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT4L", SND_SOC_NOPM,
		   MADERA_OUT4L_ENA_SHIFT, 0, शून्य, 0, madera_spk_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT5L", MADERA_OUTPUT_ENABLES_1,
		   MADERA_OUT5L_ENA_SHIFT, 0, शून्य, 0, madera_out_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT5R", MADERA_OUTPUT_ENABLES_1,
		   MADERA_OUT5R_ENA_SHIFT, 0, शून्य, 0, madera_out_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),

SND_SOC_DAPM_PGA("SPD1TX1", MADERA_SPD1_TX_CONTROL,
		 MADERA_SPD1_VAL1_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("SPD1TX2", MADERA_SPD1_TX_CONTROL,
		 MADERA_SPD1_VAL2_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_OUT_DRV("SPD1", MADERA_SPD1_TX_CONTROL,
		     MADERA_SPD1_ENA_SHIFT, 0, शून्य, 0),

/*
 * mux_in widमाला_लो : arranged in the order of sources
 * specअगरied in MADERA_MIXER_INPUT_ROUTES
 */

SND_SOC_DAPM_PGA("Noise Generator", MADERA_COMFORT_NOISE_GENERATOR,
		 MADERA_NOISE_GEN_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("Tone Generator 1", MADERA_TONE_GENERATOR_1,
		 MADERA_TONE1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Tone Generator 2", MADERA_TONE_GENERATOR_1,
		 MADERA_TONE2_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_SIGGEN("HAPTICS"),

SND_SOC_DAPM_MUX("AEC1 Loopback", MADERA_DAC_AEC_CONTROL_1,
		 MADERA_AEC1_LOOPBACK_ENA_SHIFT, 0,
		 &cs47l15_aec_loopback_mux[0]),
SND_SOC_DAPM_MUX("AEC2 Loopback", MADERA_DAC_AEC_CONTROL_2,
		 MADERA_AEC2_LOOPBACK_ENA_SHIFT, 0,
		 &cs47l15_aec_loopback_mux[1]),

SND_SOC_DAPM_PGA_E("IN1L", MADERA_INPUT_ENABLES, MADERA_IN1L_ENA_SHIFT,
		   0, शून्य, 0, madera_in_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("IN1R", MADERA_INPUT_ENABLES, MADERA_IN1R_ENA_SHIFT,
		   0, शून्य, 0, madera_in_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("IN2L", MADERA_INPUT_ENABLES, MADERA_IN2L_ENA_SHIFT,
		   0, शून्य, 0, madera_in_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("IN2R", MADERA_INPUT_ENABLES, MADERA_IN2R_ENA_SHIFT,
		   0, शून्य, 0, madera_in_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),

SND_SOC_DAPM_AIF_IN("AIF1RX1", शून्य, 0,
		    MADERA_AIF1_RX_ENABLES, MADERA_AIF1RX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX2", शून्य, 1,
		    MADERA_AIF1_RX_ENABLES, MADERA_AIF1RX2_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX3", शून्य, 2,
		    MADERA_AIF1_RX_ENABLES, MADERA_AIF1RX3_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX4", शून्य, 3,
		    MADERA_AIF1_RX_ENABLES, MADERA_AIF1RX4_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX5", शून्य, 4,
		    MADERA_AIF1_RX_ENABLES, MADERA_AIF1RX5_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX6", शून्य, 5,
		    MADERA_AIF1_RX_ENABLES, MADERA_AIF1RX6_ENA_SHIFT, 0),

SND_SOC_DAPM_AIF_IN("AIF2RX1", शून्य, 0,
		    MADERA_AIF2_RX_ENABLES, MADERA_AIF2RX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF2RX2", शून्य, 1,
		    MADERA_AIF2_RX_ENABLES, MADERA_AIF2RX2_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF2RX3", शून्य, 2,
		    MADERA_AIF2_RX_ENABLES, MADERA_AIF2RX3_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF2RX4", शून्य, 3,
		    MADERA_AIF2_RX_ENABLES, MADERA_AIF2RX4_ENA_SHIFT, 0),

SND_SOC_DAPM_AIF_IN("AIF3RX1", शून्य, 0,
		    MADERA_AIF3_RX_ENABLES, MADERA_AIF3RX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF3RX2", शून्य, 1,
		    MADERA_AIF3_RX_ENABLES, MADERA_AIF3RX2_ENA_SHIFT, 0),

SND_SOC_DAPM_PGA("EQ1", MADERA_EQ1_1, MADERA_EQ1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("EQ2", MADERA_EQ2_1, MADERA_EQ2_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("EQ3", MADERA_EQ3_1, MADERA_EQ3_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("EQ4", MADERA_EQ4_1, MADERA_EQ4_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("DRC1L", MADERA_DRC1_CTRL1, MADERA_DRC1L_ENA_SHIFT, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("DRC1R", MADERA_DRC1_CTRL1, MADERA_DRC1R_ENA_SHIFT, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("DRC2L", MADERA_DRC2_CTRL1, MADERA_DRC2L_ENA_SHIFT, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("DRC2R", MADERA_DRC2_CTRL1, MADERA_DRC2R_ENA_SHIFT, 0,
		 शून्य, 0),

SND_SOC_DAPM_PGA("LHPF1", MADERA_HPLPF1_1, MADERA_LHPF1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("LHPF2", MADERA_HPLPF2_1, MADERA_LHPF2_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("LHPF3", MADERA_HPLPF3_1, MADERA_LHPF3_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("LHPF4", MADERA_HPLPF4_1, MADERA_LHPF4_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("ISRC1DEC1", MADERA_ISRC_1_CTRL_3,
		 MADERA_ISRC1_DEC1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ISRC1DEC2", MADERA_ISRC_1_CTRL_3,
		 MADERA_ISRC1_DEC2_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ISRC1DEC3", MADERA_ISRC_1_CTRL_3,
		 MADERA_ISRC1_DEC3_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ISRC1DEC4", MADERA_ISRC_1_CTRL_3,
		 MADERA_ISRC1_DEC4_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("ISRC1INT1", MADERA_ISRC_1_CTRL_3,
		 MADERA_ISRC1_INT1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ISRC1INT2", MADERA_ISRC_1_CTRL_3,
		 MADERA_ISRC1_INT2_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ISRC1INT3", MADERA_ISRC_1_CTRL_3,
		 MADERA_ISRC1_INT3_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ISRC1INT4", MADERA_ISRC_1_CTRL_3,
		 MADERA_ISRC1_INT4_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("ISRC2DEC1", MADERA_ISRC_2_CTRL_3,
		 MADERA_ISRC2_DEC1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ISRC2DEC2", MADERA_ISRC_2_CTRL_3,
		 MADERA_ISRC2_DEC2_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ISRC2DEC3", MADERA_ISRC_2_CTRL_3,
		 MADERA_ISRC2_DEC3_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ISRC2DEC4", MADERA_ISRC_2_CTRL_3,
		 MADERA_ISRC2_DEC4_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("ISRC2INT1", MADERA_ISRC_2_CTRL_3,
		 MADERA_ISRC2_INT1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ISRC2INT2", MADERA_ISRC_2_CTRL_3,
		 MADERA_ISRC2_INT2_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ISRC2INT3", MADERA_ISRC_2_CTRL_3,
		 MADERA_ISRC2_INT3_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ISRC2INT4", MADERA_ISRC_2_CTRL_3,
		 MADERA_ISRC2_INT4_ENA_SHIFT, 0, शून्य, 0),

WM_ADSP2("DSP1", 0, cs47l15_adsp_घातer_ev),

/* end of ordered widget list */

MADERA_MIXER_WIDGETS(EQ1, "EQ1"),
MADERA_MIXER_WIDGETS(EQ2, "EQ2"),
MADERA_MIXER_WIDGETS(EQ3, "EQ3"),
MADERA_MIXER_WIDGETS(EQ4, "EQ4"),

MADERA_MIXER_WIDGETS(DRC1L, "DRC1L"),
MADERA_MIXER_WIDGETS(DRC1R, "DRC1R"),
MADERA_MIXER_WIDGETS(DRC2L, "DRC2L"),
MADERA_MIXER_WIDGETS(DRC2R, "DRC2R"),

SND_SOC_DAPM_SWITCH("DRC1 Activity Output", SND_SOC_NOPM, 0, 0,
		    &madera_drc_activity_output_mux[0]),
SND_SOC_DAPM_SWITCH("DRC2 Activity Output", SND_SOC_NOPM, 0, 0,
		    &madera_drc_activity_output_mux[1]),

MADERA_MIXER_WIDGETS(LHPF1, "LHPF1"),
MADERA_MIXER_WIDGETS(LHPF2, "LHPF2"),
MADERA_MIXER_WIDGETS(LHPF3, "LHPF3"),
MADERA_MIXER_WIDGETS(LHPF4, "LHPF4"),

MADERA_MIXER_WIDGETS(PWM1, "PWM1"),
MADERA_MIXER_WIDGETS(PWM2, "PWM2"),

MADERA_MIXER_WIDGETS(OUT1L, "HPOUT1L"),
MADERA_MIXER_WIDGETS(OUT1R, "HPOUT1R"),
MADERA_MIXER_WIDGETS(SPKOUTL, "SPKOUTL"),
MADERA_MIXER_WIDGETS(SPKDAT1L, "SPKDAT1L"),
MADERA_MIXER_WIDGETS(SPKDAT1R, "SPKDAT1R"),

MADERA_MIXER_WIDGETS(AIF1TX1, "AIF1TX1"),
MADERA_MIXER_WIDGETS(AIF1TX2, "AIF1TX2"),
MADERA_MIXER_WIDGETS(AIF1TX3, "AIF1TX3"),
MADERA_MIXER_WIDGETS(AIF1TX4, "AIF1TX4"),
MADERA_MIXER_WIDGETS(AIF1TX5, "AIF1TX5"),
MADERA_MIXER_WIDGETS(AIF1TX6, "AIF1TX6"),

MADERA_MIXER_WIDGETS(AIF2TX1, "AIF2TX1"),
MADERA_MIXER_WIDGETS(AIF2TX2, "AIF2TX2"),
MADERA_MIXER_WIDGETS(AIF2TX3, "AIF2TX3"),
MADERA_MIXER_WIDGETS(AIF2TX4, "AIF2TX4"),

MADERA_MIXER_WIDGETS(AIF3TX1, "AIF3TX1"),
MADERA_MIXER_WIDGETS(AIF3TX2, "AIF3TX2"),

MADERA_MUX_WIDGETS(SPD1TX1, "SPDIF1TX1"),
MADERA_MUX_WIDGETS(SPD1TX2, "SPDIF1TX2"),

MADERA_DSP_WIDGETS(DSP1, "DSP1"),

SND_SOC_DAPM_SWITCH("DSP1 Trigger Output", SND_SOC_NOPM, 0, 0,
		    &madera_dsp_trigger_output_mux[0]),

MADERA_MUX_WIDGETS(ISRC1DEC1, "ISRC1DEC1"),
MADERA_MUX_WIDGETS(ISRC1DEC2, "ISRC1DEC2"),
MADERA_MUX_WIDGETS(ISRC1DEC3, "ISRC1DEC3"),
MADERA_MUX_WIDGETS(ISRC1DEC4, "ISRC1DEC4"),

MADERA_MUX_WIDGETS(ISRC1INT1, "ISRC1INT1"),
MADERA_MUX_WIDGETS(ISRC1INT2, "ISRC1INT2"),
MADERA_MUX_WIDGETS(ISRC1INT3, "ISRC1INT3"),
MADERA_MUX_WIDGETS(ISRC1INT4, "ISRC1INT4"),

MADERA_MUX_WIDGETS(ISRC2DEC1, "ISRC2DEC1"),
MADERA_MUX_WIDGETS(ISRC2DEC2, "ISRC2DEC2"),
MADERA_MUX_WIDGETS(ISRC2DEC3, "ISRC2DEC3"),
MADERA_MUX_WIDGETS(ISRC2DEC4, "ISRC2DEC4"),

MADERA_MUX_WIDGETS(ISRC2INT1, "ISRC2INT1"),
MADERA_MUX_WIDGETS(ISRC2INT2, "ISRC2INT2"),
MADERA_MUX_WIDGETS(ISRC2INT3, "ISRC2INT3"),
MADERA_MUX_WIDGETS(ISRC2INT4, "ISRC2INT4"),

SND_SOC_DAPM_OUTPUT("HPOUTL"),
SND_SOC_DAPM_OUTPUT("HPOUTR"),
SND_SOC_DAPM_OUTPUT("EPOUTP"),
SND_SOC_DAPM_OUTPUT("EPOUTN"),
SND_SOC_DAPM_OUTPUT("SPKOUTN"),
SND_SOC_DAPM_OUTPUT("SPKOUTP"),
SND_SOC_DAPM_OUTPUT("SPKDAT1L"),
SND_SOC_DAPM_OUTPUT("SPKDAT1R"),
SND_SOC_DAPM_OUTPUT("SPDIF1"),

SND_SOC_DAPM_OUTPUT("MICSUPP"),
पूर्ण;

#घोषणा MADERA_MIXER_INPUT_ROUTES(name)	\
	अणु name, "Noise Generator", "Noise Generator" पूर्ण, \
	अणु name, "Tone Generator 1", "Tone Generator 1" पूर्ण, \
	अणु name, "Tone Generator 2", "Tone Generator 2" पूर्ण, \
	अणु name, "Haptics", "HAPTICS" पूर्ण, \
	अणु name, "AEC1", "AEC1 Loopback" पूर्ण, \
	अणु name, "AEC2", "AEC2 Loopback" पूर्ण, \
	अणु name, "IN1L", "IN1L" पूर्ण, \
	अणु name, "IN1R", "IN1R" पूर्ण, \
	अणु name, "IN2L", "IN2L" पूर्ण, \
	अणु name, "IN2R", "IN2R" पूर्ण, \
	अणु name, "AIF1RX1", "AIF1RX1" पूर्ण, \
	अणु name, "AIF1RX2", "AIF1RX2" पूर्ण, \
	अणु name, "AIF1RX3", "AIF1RX3" पूर्ण, \
	अणु name, "AIF1RX4", "AIF1RX4" पूर्ण, \
	अणु name, "AIF1RX5", "AIF1RX5" पूर्ण, \
	अणु name, "AIF1RX6", "AIF1RX6" पूर्ण, \
	अणु name, "AIF2RX1", "AIF2RX1" पूर्ण, \
	अणु name, "AIF2RX2", "AIF2RX2" पूर्ण, \
	अणु name, "AIF2RX3", "AIF2RX3" पूर्ण, \
	अणु name, "AIF2RX4", "AIF2RX4" पूर्ण, \
	अणु name, "AIF3RX1", "AIF3RX1" पूर्ण, \
	अणु name, "AIF3RX2", "AIF3RX2" पूर्ण, \
	अणु name, "EQ1", "EQ1" पूर्ण, \
	अणु name, "EQ2", "EQ2" पूर्ण, \
	अणु name, "EQ3", "EQ3" पूर्ण, \
	अणु name, "EQ4", "EQ4" पूर्ण, \
	अणु name, "DRC1L", "DRC1L" पूर्ण, \
	अणु name, "DRC1R", "DRC1R" पूर्ण, \
	अणु name, "DRC2L", "DRC2L" पूर्ण, \
	अणु name, "DRC2R", "DRC2R" पूर्ण, \
	अणु name, "LHPF1", "LHPF1" पूर्ण, \
	अणु name, "LHPF2", "LHPF2" पूर्ण, \
	अणु name, "LHPF3", "LHPF3" पूर्ण, \
	अणु name, "LHPF4", "LHPF4" पूर्ण, \
	अणु name, "ISRC1DEC1", "ISRC1DEC1" पूर्ण, \
	अणु name, "ISRC1DEC2", "ISRC1DEC2" पूर्ण, \
	अणु name, "ISRC1DEC3", "ISRC1DEC3" पूर्ण, \
	अणु name, "ISRC1DEC4", "ISRC1DEC4" पूर्ण, \
	अणु name, "ISRC1INT1", "ISRC1INT1" पूर्ण, \
	अणु name, "ISRC1INT2", "ISRC1INT2" पूर्ण, \
	अणु name, "ISRC1INT3", "ISRC1INT3" पूर्ण, \
	अणु name, "ISRC1INT4", "ISRC1INT4" पूर्ण, \
	अणु name, "ISRC2DEC1", "ISRC2DEC1" पूर्ण, \
	अणु name, "ISRC2DEC2", "ISRC2DEC2" पूर्ण, \
	अणु name, "ISRC2DEC3", "ISRC2DEC3" पूर्ण, \
	अणु name, "ISRC2DEC4", "ISRC2DEC4" पूर्ण, \
	अणु name, "ISRC2INT1", "ISRC2INT1" पूर्ण, \
	अणु name, "ISRC2INT2", "ISRC2INT2" पूर्ण, \
	अणु name, "ISRC2INT3", "ISRC2INT3" पूर्ण, \
	अणु name, "ISRC2INT4", "ISRC2INT4" पूर्ण, \
	अणु name, "DSP1.1", "DSP1" पूर्ण, \
	अणु name, "DSP1.2", "DSP1" पूर्ण, \
	अणु name, "DSP1.3", "DSP1" पूर्ण, \
	अणु name, "DSP1.4", "DSP1" पूर्ण, \
	अणु name, "DSP1.5", "DSP1" पूर्ण, \
	अणु name, "DSP1.6", "DSP1" पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_route cs47l15_dapm_routes[] = अणु
	/* Internal घड़ी करोमुख्यs */
	अणु "EQ1", शून्य, "FXCLK" पूर्ण,
	अणु "EQ2", शून्य, "FXCLK" पूर्ण,
	अणु "EQ3", शून्य, "FXCLK" पूर्ण,
	अणु "EQ4", शून्य, "FXCLK" पूर्ण,
	अणु "DRC1L", शून्य, "FXCLK" पूर्ण,
	अणु "DRC1R", शून्य, "FXCLK" पूर्ण,
	अणु "DRC2L", शून्य, "FXCLK" पूर्ण,
	अणु "DRC2R", शून्य, "FXCLK" पूर्ण,
	अणु "LHPF1", शून्य, "FXCLK" पूर्ण,
	अणु "LHPF2", शून्य, "FXCLK" पूर्ण,
	अणु "LHPF3", शून्य, "FXCLK" पूर्ण,
	अणु "LHPF4", शून्य, "FXCLK" पूर्ण,
	अणु "PWM1 Mixer", शून्य, "PWMCLK" पूर्ण,
	अणु "PWM2 Mixer", शून्य, "PWMCLK" पूर्ण,
	अणु "OUT1L", शून्य, "OUTCLK" पूर्ण,
	अणु "OUT1R", शून्य, "OUTCLK" पूर्ण,
	अणु "OUT4L", शून्य, "OUTCLK" पूर्ण,
	अणु "OUT5L", शून्य, "OUTCLK" पूर्ण,
	अणु "OUT5R", शून्य, "OUTCLK" पूर्ण,
	अणु "AIF1TX1", शून्य, "AIF1TXCLK" पूर्ण,
	अणु "AIF1TX2", शून्य, "AIF1TXCLK" पूर्ण,
	अणु "AIF1TX3", शून्य, "AIF1TXCLK" पूर्ण,
	अणु "AIF1TX4", शून्य, "AIF1TXCLK" पूर्ण,
	अणु "AIF1TX5", शून्य, "AIF1TXCLK" पूर्ण,
	अणु "AIF1TX6", शून्य, "AIF1TXCLK" पूर्ण,
	अणु "AIF2TX1", शून्य, "AIF2TXCLK" पूर्ण,
	अणु "AIF2TX2", शून्य, "AIF2TXCLK" पूर्ण,
	अणु "AIF2TX3", शून्य, "AIF2TXCLK" पूर्ण,
	अणु "AIF2TX4", शून्य, "AIF2TXCLK" पूर्ण,
	अणु "AIF3TX1", शून्य, "AIF3TXCLK" पूर्ण,
	अणु "AIF3TX2", शून्य, "AIF3TXCLK" पूर्ण,
	अणु "SPD1TX1", शून्य, "SPDCLK" पूर्ण,
	अणु "SPD1TX2", शून्य, "SPDCLK" पूर्ण,
	अणु "DSP1", शून्य, "DSP1CLK" पूर्ण,
	अणु "ISRC1DEC1", शून्य, "ISRC1CLK" पूर्ण,
	अणु "ISRC1DEC2", शून्य, "ISRC1CLK" पूर्ण,
	अणु "ISRC1DEC3", शून्य, "ISRC1CLK" पूर्ण,
	अणु "ISRC1DEC4", शून्य, "ISRC1CLK" पूर्ण,
	अणु "ISRC1INT1", शून्य, "ISRC1CLK" पूर्ण,
	अणु "ISRC1INT2", शून्य, "ISRC1CLK" पूर्ण,
	अणु "ISRC1INT3", शून्य, "ISRC1CLK" पूर्ण,
	अणु "ISRC1INT4", शून्य, "ISRC1CLK" पूर्ण,
	अणु "ISRC2DEC1", शून्य, "ISRC2CLK" पूर्ण,
	अणु "ISRC2DEC2", शून्य, "ISRC2CLK" पूर्ण,
	अणु "ISRC2DEC3", शून्य, "ISRC2CLK" पूर्ण,
	अणु "ISRC2DEC4", शून्य, "ISRC2CLK" पूर्ण,
	अणु "ISRC2INT1", शून्य, "ISRC2CLK" पूर्ण,
	अणु "ISRC2INT2", शून्य, "ISRC2CLK" पूर्ण,
	अणु "ISRC2INT3", शून्य, "ISRC2CLK" पूर्ण,
	अणु "ISRC2INT4", शून्य, "ISRC2CLK" पूर्ण,

	अणु "OUT1L", शून्य, "CPVDD1" पूर्ण,
	अणु "OUT1R", शून्य, "CPVDD1" पूर्ण,
	अणु "OUT4L", शून्य, "SPKVDD" पूर्ण,

	अणु "OUT1L", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT1R", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT4L", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT5L", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT5R", शून्य, "SYSCLK" पूर्ण,

	अणु "SPD1", शून्य, "SYSCLK" पूर्ण,
	अणु "SPD1", शून्य, "SPD1TX1" पूर्ण,
	अणु "SPD1", शून्य, "SPD1TX2" पूर्ण,

	अणु "IN1L", शून्य, "SYSCLK" पूर्ण,
	अणु "IN1R", शून्य, "SYSCLK" पूर्ण,
	अणु "IN2L", शून्य, "SYSCLK" पूर्ण,
	अणु "IN2R", शून्य, "SYSCLK" पूर्ण,

	अणु "MICBIAS1", शून्य, "MICVDD" पूर्ण,

	अणु "MICBIAS1A", शून्य, "MICBIAS1" पूर्ण,
	अणु "MICBIAS1B", शून्य, "MICBIAS1" पूर्ण,
	अणु "MICBIAS1C", शून्य, "MICBIAS1" पूर्ण,

	अणु "Noise Generator", शून्य, "SYSCLK" पूर्ण,
	अणु "Tone Generator 1", शून्य, "SYSCLK" पूर्ण,
	अणु "Tone Generator 2", शून्य, "SYSCLK" पूर्ण,

	अणु "Noise Generator", शून्य, "NOISE" पूर्ण,
	अणु "Tone Generator 1", शून्य, "TONE" पूर्ण,
	अणु "Tone Generator 2", शून्य, "TONE" पूर्ण,

	अणु "AIF1 Capture", शून्य, "AIF1TX1" पूर्ण,
	अणु "AIF1 Capture", शून्य, "AIF1TX2" पूर्ण,
	अणु "AIF1 Capture", शून्य, "AIF1TX3" पूर्ण,
	अणु "AIF1 Capture", शून्य, "AIF1TX4" पूर्ण,
	अणु "AIF1 Capture", शून्य, "AIF1TX5" पूर्ण,
	अणु "AIF1 Capture", शून्य, "AIF1TX6" पूर्ण,

	अणु "AIF1RX1", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX2", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX3", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX4", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX5", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX6", शून्य, "AIF1 Playback" पूर्ण,

	अणु "AIF2 Capture", शून्य, "AIF2TX1" पूर्ण,
	अणु "AIF2 Capture", शून्य, "AIF2TX2" पूर्ण,
	अणु "AIF2 Capture", शून्य, "AIF2TX3" पूर्ण,
	अणु "AIF2 Capture", शून्य, "AIF2TX4" पूर्ण,

	अणु "AIF2RX1", शून्य, "AIF2 Playback" पूर्ण,
	अणु "AIF2RX2", शून्य, "AIF2 Playback" पूर्ण,
	अणु "AIF2RX3", शून्य, "AIF2 Playback" पूर्ण,
	अणु "AIF2RX4", शून्य, "AIF2 Playback" पूर्ण,

	अणु "AIF3 Capture", शून्य, "AIF3TX1" पूर्ण,
	अणु "AIF3 Capture", शून्य, "AIF3TX2" पूर्ण,

	अणु "AIF3RX1", शून्य, "AIF3 Playback" पूर्ण,
	अणु "AIF3RX2", शून्य, "AIF3 Playback" पूर्ण,

	अणु "AIF1 Playback", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF2 Playback", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF3 Playback", शून्य, "SYSCLK" पूर्ण,

	अणु "AIF1 Capture", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF2 Capture", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF3 Capture", शून्य, "SYSCLK" पूर्ण,

	अणु "Audio Trace DSP", शून्य, "DSP1" पूर्ण,

	अणु "IN1L Analog Mux", "A", "IN1ALN" पूर्ण,
	अणु "IN1L Analog Mux", "A", "IN1ALP" पूर्ण,
	अणु "IN1L Analog Mux", "B", "IN1BLN" पूर्ण,
	अणु "IN1L Analog Mux", "B", "IN1BLP" पूर्ण,
	अणु "IN1R Analog Mux", "A", "IN1ARN" पूर्ण,
	अणु "IN1R Analog Mux", "A", "IN1ARP" पूर्ण,
	अणु "IN1R Analog Mux", "B", "IN1BRN" पूर्ण,
	अणु "IN1R Analog Mux", "B", "IN1BRP" पूर्ण,

	अणु "IN1L Mode", "Analog", "IN1L Analog Mux" पूर्ण,
	अणु "IN1R Mode", "Analog", "IN1R Analog Mux" पूर्ण,

	अणु "IN1L Mode", "Digital", "IN1ALN" पूर्ण,
	अणु "IN1L Mode", "Digital", "IN1ALP" पूर्ण,
	अणु "IN1R Mode", "Digital", "IN1ALN" पूर्ण,
	अणु "IN1R Mode", "Digital", "IN1ALP" पूर्ण,

	अणु "IN1L", शून्य, "IN1L Mode" पूर्ण,
	अणु "IN1R", शून्य, "IN1R Mode" पूर्ण,

	अणु "IN2L Mode", "Analog", "IN2N" पूर्ण,
	अणु "IN2L Mode", "Analog", "IN2P" पूर्ण,

	अणु "IN2L Mode", "Digital", "SPKRXDAT" पूर्ण,
	अणु "IN2R Mode", "Digital", "SPKRXDAT" पूर्ण,

	अणु "IN2L", शून्य, "IN2L Mode" पूर्ण,
	अणु "IN2R", शून्य, "IN2R Mode" पूर्ण,

	MADERA_MIXER_ROUTES("OUT1L", "HPOUT1L"),
	MADERA_MIXER_ROUTES("OUT1R", "HPOUT1R"),
	MADERA_MIXER_ROUTES("OUT4L", "SPKOUTL"),
	MADERA_MIXER_ROUTES("OUT5L", "SPKDAT1L"),
	MADERA_MIXER_ROUTES("OUT5R", "SPKDAT1R"),

	MADERA_MIXER_ROUTES("PWM1 Driver", "PWM1"),
	MADERA_MIXER_ROUTES("PWM2 Driver", "PWM2"),

	MADERA_MIXER_ROUTES("AIF1TX1", "AIF1TX1"),
	MADERA_MIXER_ROUTES("AIF1TX2", "AIF1TX2"),
	MADERA_MIXER_ROUTES("AIF1TX3", "AIF1TX3"),
	MADERA_MIXER_ROUTES("AIF1TX4", "AIF1TX4"),
	MADERA_MIXER_ROUTES("AIF1TX5", "AIF1TX5"),
	MADERA_MIXER_ROUTES("AIF1TX6", "AIF1TX6"),

	MADERA_MIXER_ROUTES("AIF2TX1", "AIF2TX1"),
	MADERA_MIXER_ROUTES("AIF2TX2", "AIF2TX2"),
	MADERA_MIXER_ROUTES("AIF2TX3", "AIF2TX3"),
	MADERA_MIXER_ROUTES("AIF2TX4", "AIF2TX4"),

	MADERA_MIXER_ROUTES("AIF3TX1", "AIF3TX1"),
	MADERA_MIXER_ROUTES("AIF3TX2", "AIF3TX2"),

	MADERA_MUX_ROUTES("SPD1TX1", "SPDIF1TX1"),
	MADERA_MUX_ROUTES("SPD1TX2", "SPDIF1TX2"),

	MADERA_MIXER_ROUTES("EQ1", "EQ1"),
	MADERA_MIXER_ROUTES("EQ2", "EQ2"),
	MADERA_MIXER_ROUTES("EQ3", "EQ3"),
	MADERA_MIXER_ROUTES("EQ4", "EQ4"),

	MADERA_MIXER_ROUTES("DRC1L", "DRC1L"),
	MADERA_MIXER_ROUTES("DRC1R", "DRC1R"),
	MADERA_MIXER_ROUTES("DRC2L", "DRC2L"),
	MADERA_MIXER_ROUTES("DRC2R", "DRC2R"),

	MADERA_MIXER_ROUTES("LHPF1", "LHPF1"),
	MADERA_MIXER_ROUTES("LHPF2", "LHPF2"),
	MADERA_MIXER_ROUTES("LHPF3", "LHPF3"),
	MADERA_MIXER_ROUTES("LHPF4", "LHPF4"),

	MADERA_DSP_ROUTES("DSP1"),

	अणु "DSP Trigger Out", शून्य, "DSP1 Trigger Output" पूर्ण,

	अणु "DSP1 Trigger Output", "Switch", "DSP1" पूर्ण,

	MADERA_MUX_ROUTES("ISRC1INT1", "ISRC1INT1"),
	MADERA_MUX_ROUTES("ISRC1INT2", "ISRC1INT2"),
	MADERA_MUX_ROUTES("ISRC1INT3", "ISRC1INT3"),
	MADERA_MUX_ROUTES("ISRC1INT4", "ISRC1INT4"),

	MADERA_MUX_ROUTES("ISRC1DEC1", "ISRC1DEC1"),
	MADERA_MUX_ROUTES("ISRC1DEC2", "ISRC1DEC2"),
	MADERA_MUX_ROUTES("ISRC1DEC3", "ISRC1DEC3"),
	MADERA_MUX_ROUTES("ISRC1DEC4", "ISRC1DEC4"),

	MADERA_MUX_ROUTES("ISRC2INT1", "ISRC2INT1"),
	MADERA_MUX_ROUTES("ISRC2INT2", "ISRC2INT2"),
	MADERA_MUX_ROUTES("ISRC2INT3", "ISRC2INT3"),
	MADERA_MUX_ROUTES("ISRC2INT4", "ISRC2INT4"),

	MADERA_MUX_ROUTES("ISRC2DEC1", "ISRC2DEC1"),
	MADERA_MUX_ROUTES("ISRC2DEC2", "ISRC2DEC2"),
	MADERA_MUX_ROUTES("ISRC2DEC3", "ISRC2DEC3"),
	MADERA_MUX_ROUTES("ISRC2DEC4", "ISRC2DEC4"),

	अणु "AEC1 Loopback", "HPOUT1L", "OUT1L" पूर्ण,
	अणु "AEC1 Loopback", "HPOUT1R", "OUT1R" पूर्ण,
	अणु "AEC2 Loopback", "HPOUT1L", "OUT1L" पूर्ण,
	अणु "AEC2 Loopback", "HPOUT1R", "OUT1R" पूर्ण,
	अणु "HPOUT1 Demux", शून्य, "OUT1L" पूर्ण,
	अणु "HPOUT1 Demux", शून्य, "OUT1R" पूर्ण,

	अणु "OUT1R", शून्य, "HPOUT1 Mono Mux" पूर्ण,
	अणु "HPOUT1 Mono Mux", "EPOUT", "OUT1L" पूर्ण,

	अणु "HPOUTL", "HPOUT", "HPOUT1 Demux" पूर्ण,
	अणु "HPOUTR", "HPOUT", "HPOUT1 Demux" पूर्ण,
	अणु "EPOUTP", "EPOUT", "HPOUT1 Demux" पूर्ण,
	अणु "EPOUTN", "EPOUT", "HPOUT1 Demux" पूर्ण,

	अणु "AEC1 Loopback", "SPKOUTL", "OUT4L" पूर्ण,
	अणु "AEC2 Loopback", "SPKOUTL", "OUT4L" पूर्ण,
	अणु "SPKOUTN", शून्य, "OUT4L" पूर्ण,
	अणु "SPKOUTP", शून्य, "OUT4L" पूर्ण,

	अणु "AEC1 Loopback", "SPKDAT1L", "OUT5L" पूर्ण,
	अणु "AEC1 Loopback", "SPKDAT1R", "OUT5R" पूर्ण,
	अणु "AEC2 Loopback", "SPKDAT1L", "OUT5L" पूर्ण,
	अणु "AEC2 Loopback", "SPKDAT1R", "OUT5R" पूर्ण,
	अणु "SPKDAT1L", शून्य, "OUT5L" पूर्ण,
	अणु "SPKDAT1R", शून्य, "OUT5R" पूर्ण,

	अणु "SPDIF1", शून्य, "SPD1" पूर्ण,

	अणु "MICSUPP", शून्य, "SYSCLK" पूर्ण,

	अणु "DRC1 Signal Activity", शून्य, "DRC1 Activity Output" पूर्ण,
	अणु "DRC2 Signal Activity", शून्य, "DRC2 Activity Output" पूर्ण,
	अणु "DRC1 Activity Output", "Switch", "DRC1L" पूर्ण,
	अणु "DRC1 Activity Output", "Switch", "DRC1R" पूर्ण,
	अणु "DRC2 Activity Output", "Switch", "DRC2L" पूर्ण,
	अणु "DRC2 Activity Output", "Switch", "DRC2R" पूर्ण,
पूर्ण;

अटल पूर्णांक cs47l15_set_fll(काष्ठा snd_soc_component *component, पूर्णांक fll_id,
			   पूर्णांक source, अचिन्हित पूर्णांक fref, अचिन्हित पूर्णांक fout)
अणु
	काष्ठा cs47l15 *cs47l15 = snd_soc_component_get_drvdata(component);

	चयन (fll_id) अणु
	हाल MADERA_FLL1_REFCLK:
		वापस madera_set_fll_refclk(&cs47l15->fll[0], source, fref,
					     fout);
	हाल MADERA_FLLAO_REFCLK:
		वापस madera_set_fll_ao_refclk(&cs47l15->fll[1], source, fref,
						fout);
	हाल MADERA_FLL1_SYNCCLK:
		वापस madera_set_fll_syncclk(&cs47l15->fll[0], source, fref,
					      fout);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल काष्ठा snd_soc_dai_driver cs47l15_dai[] = अणु
	अणु
		.name = "cs47l15-aif1",
		.id = 1,
		.base = MADERA_AIF1_BCLK_CTRL,
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 6,
			.rates = MADERA_RATES,
			.क्रमmats = MADERA_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 1,
			.channels_max = 6,
			.rates = MADERA_RATES,
			.क्रमmats = MADERA_FORMATS,
		 पूर्ण,
		.ops = &madera_dai_ops,
		.symmetric_rate = 1,
		.symmetric_sample_bits = 1,
	पूर्ण,
	अणु
		.name = "cs47l15-aif2",
		.id = 2,
		.base = MADERA_AIF2_BCLK_CTRL,
		.playback = अणु
			.stream_name = "AIF2 Playback",
			.channels_min = 1,
			.channels_max = 4,
			.rates = MADERA_RATES,
			.क्रमmats = MADERA_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF2 Capture",
			.channels_min = 1,
			.channels_max = 4,
			.rates = MADERA_RATES,
			.क्रमmats = MADERA_FORMATS,
		 पूर्ण,
		.ops = &madera_dai_ops,
		.symmetric_rate = 1,
		.symmetric_sample_bits = 1,
	पूर्ण,
	अणु
		.name = "cs47l15-aif3",
		.id = 3,
		.base = MADERA_AIF3_BCLK_CTRL,
		.playback = अणु
			.stream_name = "AIF3 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MADERA_RATES,
			.क्रमmats = MADERA_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF3 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MADERA_RATES,
			.क्रमmats = MADERA_FORMATS,
		 पूर्ण,
		.ops = &madera_dai_ops,
		.symmetric_rate = 1,
		.symmetric_sample_bits = 1,
	पूर्ण,
	अणु
		.name = "cs47l15-cpu-trace",
		.capture = अणु
			.stream_name = "Audio Trace CPU",
			.channels_min = 1,
			.channels_max = 6,
			.rates = MADERA_RATES,
			.क्रमmats = MADERA_FORMATS,
		पूर्ण,
		.compress_new = snd_soc_new_compress,
	पूर्ण,
	अणु
		.name = "cs47l15-dsp-trace",
		.capture = अणु
			.stream_name = "Audio Trace DSP",
			.channels_min = 1,
			.channels_max = 6,
			.rates = MADERA_RATES,
			.क्रमmats = MADERA_FORMATS,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक cs47l15_खोलो(काष्ठा snd_soc_component *component,
			काष्ठा snd_compr_stream *stream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = stream->निजी_data;
	काष्ठा cs47l15 *cs47l15 = snd_soc_component_get_drvdata(component);
	काष्ठा madera_priv *priv = &cs47l15->core;
	काष्ठा madera *madera = priv->madera;
	पूर्णांक n_adsp;

	अगर (म_भेद(asoc_rtd_to_codec(rtd, 0)->name, "cs47l15-dsp-trace") == 0) अणु
		n_adsp = 0;
	पूर्ण अन्यथा अणु
		dev_err(madera->dev,
			"No suitable compressed stream for DAI '%s'\n",
			asoc_rtd_to_codec(rtd, 0)->name);
		वापस -EINVAL;
	पूर्ण

	वापस wm_adsp_compr_खोलो(&priv->adsp[n_adsp], stream);
पूर्ण

अटल irqवापस_t cs47l15_adsp2_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cs47l15 *cs47l15 = data;
	काष्ठा madera_priv *priv = &cs47l15->core;
	काष्ठा madera *madera = priv->madera;
	पूर्णांक ret;

	ret = wm_adsp_compr_handle_irq(&priv->adsp[0]);
	अगर (ret == -ENODEV) अणु
		dev_err(madera->dev, "Spurious compressed data IRQ\n");
		वापस IRQ_NONE;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_route cs47l15_mono_routes[] = अणु
	अणु "HPOUT1 Mono Mux", "HPOUT", "OUT1L" पूर्ण,
पूर्ण;

अटल पूर्णांक cs47l15_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs47l15 *cs47l15 = snd_soc_component_get_drvdata(component);
	काष्ठा madera *madera = cs47l15->core.madera;
	पूर्णांक ret;

	snd_soc_component_init_regmap(component, madera->regmap);

	mutex_lock(&madera->dapm_ptr_lock);
	madera->dapm = snd_soc_component_get_dapm(component);
	mutex_unlock(&madera->dapm_ptr_lock);

	ret = madera_init_inमाला_दो(component);
	अगर (ret)
		वापस ret;

	ret = madera_init_outमाला_दो(component, cs47l15_mono_routes,
				  ARRAY_SIZE(cs47l15_mono_routes),
				  CS47L15_MONO_OUTPUTS);
	अगर (ret)
		वापस ret;

	snd_soc_component_disable_pin(component, "HAPTICS");

	ret = snd_soc_add_component_controls(component,
					     madera_adsp_rate_controls,
					     CS47L15_NUM_ADSP);
	अगर (ret)
		वापस ret;

	wm_adsp2_component_probe(&cs47l15->core.adsp[0], component);

	वापस 0;
पूर्ण

अटल व्योम cs47l15_component_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs47l15 *cs47l15 = snd_soc_component_get_drvdata(component);
	काष्ठा madera *madera = cs47l15->core.madera;

	mutex_lock(&madera->dapm_ptr_lock);
	madera->dapm = शून्य;
	mutex_unlock(&madera->dapm_ptr_lock);

	wm_adsp2_component_हटाओ(&cs47l15->core.adsp[0], component);
पूर्ण

#घोषणा CS47L15_DIG_VU 0x0200

अटल अचिन्हित पूर्णांक cs47l15_digital_vu[] = अणु
	MADERA_DAC_DIGITAL_VOLUME_1L,
	MADERA_DAC_DIGITAL_VOLUME_1R,
	MADERA_DAC_DIGITAL_VOLUME_4L,
	MADERA_DAC_DIGITAL_VOLUME_5L,
	MADERA_DAC_DIGITAL_VOLUME_5R,
पूर्ण;

अटल स्थिर काष्ठा snd_compress_ops cs47l15_compress_ops = अणु
	.खोलो = &cs47l15_खोलो,
	.मुक्त = &wm_adsp_compr_मुक्त,
	.set_params = &wm_adsp_compr_set_params,
	.get_caps = &wm_adsp_compr_get_caps,
	.trigger = &wm_adsp_compr_trigger,
	.poपूर्णांकer = &wm_adsp_compr_poपूर्णांकer,
	.copy = &wm_adsp_compr_copy,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_cs47l15 = अणु
	.probe			= &cs47l15_component_probe,
	.हटाओ			= &cs47l15_component_हटाओ,
	.set_sysclk		= &madera_set_sysclk,
	.set_pll		= &cs47l15_set_fll,
	.name			= DRV_NAME,
	.compress_ops		= &cs47l15_compress_ops,
	.controls		= cs47l15_snd_controls,
	.num_controls		= ARRAY_SIZE(cs47l15_snd_controls),
	.dapm_widमाला_लो		= cs47l15_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(cs47l15_dapm_widमाला_लो),
	.dapm_routes		= cs47l15_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(cs47l15_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक cs47l15_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा madera *madera = dev_get_drvdata(pdev->dev.parent);
	काष्ठा cs47l15 *cs47l15;
	पूर्णांक i, ret;

	BUILD_BUG_ON(ARRAY_SIZE(cs47l15_dai) > MADERA_MAX_DAI);

	/* quick निकास अगर Madera irqchip driver hasn't completed probe */
	अगर (!madera->irq_dev) अणु
		dev_dbg(&pdev->dev, "irqchip driver not ready\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	cs47l15 = devm_kzalloc(&pdev->dev, माप(काष्ठा cs47l15),
			       GFP_KERNEL);
	अगर (!cs47l15)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, cs47l15);

	cs47l15->core.madera = madera;
	cs47l15->core.dev = &pdev->dev;
	cs47l15->core.num_inमाला_दो = 4;

	ret = madera_core_init(&cs47l15->core);
	अगर (ret)
		वापस ret;

	ret = madera_init_overheat(&cs47l15->core);
	अगर (ret)
		जाओ error_core;

	ret = madera_request_irq(madera, MADERA_IRQ_DSP_IRQ1,
				 "ADSP2 Compressed IRQ", cs47l15_adsp2_irq,
				 cs47l15);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Failed to request DSP IRQ: %d\n", ret);
		जाओ error_overheat;
	पूर्ण

	ret = madera_set_irq_wake(madera, MADERA_IRQ_DSP_IRQ1, 1);
	अगर (ret)
		dev_warn(&pdev->dev, "Failed to set DSP IRQ wake: %d\n", ret);

	cs47l15->core.adsp[0].part = "cs47l15";
	cs47l15->core.adsp[0].num = 1;
	cs47l15->core.adsp[0].type = WMFW_ADSP2;
	cs47l15->core.adsp[0].rev = 2;
	cs47l15->core.adsp[0].dev = madera->dev;
	cs47l15->core.adsp[0].regmap = madera->regmap_32bit;

	cs47l15->core.adsp[0].base = MADERA_DSP1_CONFIG_1;
	cs47l15->core.adsp[0].mem = cs47l15_dsp1_regions;
	cs47l15->core.adsp[0].num_mems = ARRAY_SIZE(cs47l15_dsp1_regions);

	cs47l15->core.adsp[0].lock_regions =
		WM_ADSP2_REGION_1 | WM_ADSP2_REGION_2 | WM_ADSP2_REGION_3;

	ret = wm_adsp2_init(&cs47l15->core.adsp[0]);
	अगर (ret != 0)
		जाओ error_dsp_irq;

	ret = madera_init_bus_error_irq(&cs47l15->core, 0, wm_adsp2_bus_error);
	अगर (ret)
		जाओ error_adsp;

	madera_init_fll(madera, 1, MADERA_FLL1_CONTROL_1 - 1,
			&cs47l15->fll[0]);
	madera_init_fll(madera, 4, MADERA_FLLAO_CONTROL_1 - 1,
			&cs47l15->fll[1]);

	क्रम (i = 0; i < ARRAY_SIZE(cs47l15_dai); i++)
		madera_init_dai(&cs47l15->core, i);

	/* Latch volume update bits */
	क्रम (i = 0; i < ARRAY_SIZE(cs47l15_digital_vu); i++)
		regmap_update_bits(madera->regmap, cs47l15_digital_vu[i],
				   CS47L15_DIG_VU, CS47L15_DIG_VU);

	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_idle(&pdev->dev);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &soc_component_dev_cs47l15,
					      cs47l15_dai,
					      ARRAY_SIZE(cs47l15_dai));
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to register component: %d\n", ret);
		जाओ error_pm_runसमय;
	पूर्ण

	वापस ret;

error_pm_runसमय:
	pm_runसमय_disable(&pdev->dev);
	madera_मुक्त_bus_error_irq(&cs47l15->core, 0);
error_adsp:
	wm_adsp2_हटाओ(&cs47l15->core.adsp[0]);
error_dsp_irq:
	madera_set_irq_wake(madera, MADERA_IRQ_DSP_IRQ1, 0);
	madera_मुक्त_irq(madera, MADERA_IRQ_DSP_IRQ1, cs47l15);
error_overheat:
	madera_मुक्त_overheat(&cs47l15->core);
error_core:
	madera_core_मुक्त(&cs47l15->core);

	वापस ret;
पूर्ण

अटल पूर्णांक cs47l15_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cs47l15 *cs47l15 = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);

	madera_मुक्त_bus_error_irq(&cs47l15->core, 0);

	wm_adsp2_हटाओ(&cs47l15->core.adsp[0]);

	madera_set_irq_wake(cs47l15->core.madera, MADERA_IRQ_DSP_IRQ1, 0);
	madera_मुक्त_irq(cs47l15->core.madera, MADERA_IRQ_DSP_IRQ1, cs47l15);
	madera_मुक्त_overheat(&cs47l15->core);
	madera_core_मुक्त(&cs47l15->core);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cs47l15_codec_driver = अणु
	.driver = अणु
		.name = "cs47l15-codec",
	पूर्ण,
	.probe = &cs47l15_probe,
	.हटाओ = &cs47l15_हटाओ,
पूर्ण;

module_platक्रमm_driver(cs47l15_codec_driver);

MODULE_SOFTDEP("pre: madera irq-madera arizona-micsupp");
MODULE_DESCRIPTION("ASoC CS47L15 driver");
MODULE_AUTHOR("Richard Fitzgerald <rf@opensource.cirrus.com>");
MODULE_AUTHOR("Jaswinder Jassal <jjassal@opensource.cirrus.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:cs47l15-codec");
