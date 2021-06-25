<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// ALSA SoC Audio driver क्रम CS47L92 codec
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

#घोषणा CS47L92_NUM_ADSP	1
#घोषणा CS47L92_MONO_OUTPUTS	3

#घोषणा DRV_NAME "cs47l92-codec"

काष्ठा cs47l92 अणु
	काष्ठा madera_priv core;
	काष्ठा madera_fll fll[2];
पूर्ण;

अटल स्थिर काष्ठा wm_adsp_region cs47l92_dsp1_regions[] = अणु
	अणु .type = WMFW_ADSP2_PM, .base = 0x080000 पूर्ण,
	अणु .type = WMFW_ADSP2_ZM, .base = 0x0e0000 पूर्ण,
	अणु .type = WMFW_ADSP2_XM, .base = 0x0a0000 पूर्ण,
	अणु .type = WMFW_ADSP2_YM, .base = 0x0c0000 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर cs47l92_outdemux_texts[] = अणु
	"HPOUT3",
	"HPOUT4",
पूर्ण;

अटल पूर्णांक cs47l92_put_demux(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	काष्ठा cs47l92 *cs47l92 = snd_soc_component_get_drvdata(component);
	काष्ठा madera_priv *priv = &cs47l92->core;
	काष्ठा madera *madera = priv->madera;
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक ep_sel, mux, change, cur;
	bool out_mono;
	पूर्णांक ret;

	अगर (ucontrol->value.क्रमागतerated.item[0] > e->items - 1)
		वापस -EINVAL;

	mux = ucontrol->value.क्रमागतerated.item[0];

	snd_soc_dapm_mutex_lock(dapm);

	ep_sel = mux << e->shअगरt_l;

	change = snd_soc_component_test_bits(component, MADERA_OUTPUT_ENABLES_1,
					     MADERA_EP_SEL_MASK,
					     ep_sel);
	अगर (!change)
		जाओ end;

	ret = regmap_पढ़ो(madera->regmap, MADERA_OUTPUT_ENABLES_1, &cur);
	अगर (ret != 0)
		dev_warn(madera->dev, "Failed to read outputs: %d\n", ret);

	/* EP_SEL should not be modअगरied जबतक HPOUT3 or 4 is enabled */
	ret = regmap_update_bits(madera->regmap, MADERA_OUTPUT_ENABLES_1,
				 MADERA_OUT3L_ENA | MADERA_OUT3R_ENA, 0);
	अगर (ret)
		dev_warn(madera->dev, "Failed to disable outputs: %d\n", ret);

	usleep_range(2000, 3000); /* रुको क्रम wseq to complete */

	ret = regmap_update_bits(madera->regmap, MADERA_OUTPUT_ENABLES_1,
				 MADERA_EP_SEL, ep_sel);
	अगर (ret) अणु
		dev_err(madera->dev, "Failed to set OUT3 demux: %d\n", ret);
	पूर्ण अन्यथा अणु
		out_mono = madera->pdata.codec.out_mono[2 + mux];

		ret = madera_set_output_mode(component, 3, out_mono);
		अगर (ret < 0)
			dev_warn(madera->dev,
				 "Failed to set output mode: %d\n", ret);
	पूर्ण

	ret = regmap_update_bits(madera->regmap, MADERA_OUTPUT_ENABLES_1,
				 MADERA_OUT3L_ENA | MADERA_OUT3R_ENA, cur);
	अगर (ret) अणु
		dev_warn(madera->dev, "Failed to restore outputs: %d\n", ret);
	पूर्ण अन्यथा अणु
		/* रुको क्रम wseq */
		अगर (cur & (MADERA_OUT3L_ENA | MADERA_OUT3R_ENA))
			msleep(34); /* enable delay */
		अन्यथा
			usleep_range(2000, 3000); /* disable delay */
	पूर्ण

end:
	snd_soc_dapm_mutex_unlock(dapm);

	वापस snd_soc_dapm_mux_update_घातer(dapm, kcontrol, mux, e, शून्य);
पूर्ण

अटल SOC_ENUM_SINGLE_DECL(cs47l92_outdemux_क्रमागत,
			    MADERA_OUTPUT_ENABLES_1,
			    MADERA_EP_SEL_SHIFT,
			    cs47l92_outdemux_texts);

अटल स्थिर काष्ठा snd_kcontrol_new cs47l92_outdemux =
	SOC_DAPM_ENUM_EXT("OUT3 Demux", cs47l92_outdemux_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन, cs47l92_put_demux);

अटल पूर्णांक cs47l92_adsp_घातer_ev(काष्ठा snd_soc_dapm_widget *w,
				 काष्ठा snd_kcontrol *kcontrol,
				 पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा cs47l92 *cs47l92 = snd_soc_component_get_drvdata(component);
	काष्ठा madera_priv *priv = &cs47l92->core;
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
		ret = madera_set_adsp_clk(&cs47l92->core, w->shअगरt, freq);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस wm_adsp_early_event(w, kcontrol, event);
पूर्ण

अटल पूर्णांक cs47l92_outclk_ev(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol,
			     पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा cs47l92 *cs47l92 = snd_soc_component_get_drvdata(component);
	काष्ठा madera_priv *priv = &cs47l92->core;
	काष्ठा madera *madera = priv->madera;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(madera->regmap, MADERA_OUTPUT_RATE_1, &val);
	अगर (ret) अणु
		dev_err(madera->dev, "Failed to read OUTCLK source: %d\n", ret);
		वापस ret;
	पूर्ण

	val &= MADERA_OUT_CLK_SRC_MASK;

	चयन (val) अणु
	हाल MADERA_OUTCLK_MCLK1:
	हाल MADERA_OUTCLK_MCLK2:
	हाल MADERA_OUTCLK_MCLK3:
		val -= (MADERA_OUTCLK_MCLK1 - MADERA_MCLK1);

		चयन (event) अणु
		हाल SND_SOC_DAPM_PRE_PMU:
			ret = clk_prepare_enable(madera->mclk[val].clk);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल SND_SOC_DAPM_POST_PMD:
			clk_disable_unprepare(madera->mclk[val].clk);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस madera_करोमुख्य_clk_ev(w, kcontrol, event);
पूर्ण

#घोषणा CS47L92_NG_SRC(name, base) \
	SOC_SINGLE(name " NG HPOUT1L Switch",  base,  0, 1, 0), \
	SOC_SINGLE(name " NG HPOUT1R Switch",  base,  1, 1, 0), \
	SOC_SINGLE(name " NG HPOUT2L Switch",  base,  2, 1, 0), \
	SOC_SINGLE(name " NG HPOUT2R Switch",  base,  3, 1, 0), \
	SOC_SINGLE(name " NG HPOUT3L Switch",  base,  4, 1, 0), \
	SOC_SINGLE(name " NG HPOUT3R Switch",  base,  5, 1, 0), \
	SOC_SINGLE(name " NG SPKDAT1L Switch", base,  8, 1, 0), \
	SOC_SINGLE(name " NG SPKDAT1R Switch", base,  9, 1, 0)

अटल स्थिर काष्ठा snd_kcontrol_new cs47l92_snd_controls[] = अणु
SOC_ENUM("IN1 OSR", madera_in_dmic_osr[0]),
SOC_ENUM("IN2 OSR", madera_in_dmic_osr[1]),
SOC_ENUM("IN3 OSR", madera_in_dmic_osr[2]),
SOC_ENUM("IN4 OSR", madera_in_dmic_osr[3]),

SOC_SINGLE_RANGE_TLV("IN1L Volume", MADERA_IN1L_CONTROL,
		     MADERA_IN1L_PGA_VOL_SHIFT, 0x40, 0x5f, 0, madera_ana_tlv),
SOC_SINGLE_RANGE_TLV("IN1R Volume", MADERA_IN1R_CONTROL,
		     MADERA_IN1R_PGA_VOL_SHIFT, 0x40, 0x5f, 0, madera_ana_tlv),
SOC_SINGLE_RANGE_TLV("IN2L Volume", MADERA_IN2L_CONTROL,
		     MADERA_IN2L_PGA_VOL_SHIFT, 0x40, 0x5f, 0, madera_ana_tlv),
SOC_SINGLE_RANGE_TLV("IN2R Volume", MADERA_IN2R_CONTROL,
		     MADERA_IN2R_PGA_VOL_SHIFT, 0x40, 0x5f, 0, madera_ana_tlv),

SOC_ENUM("IN HPF Cutoff Frequency", madera_in_hpf_cut_क्रमागत),

SOC_SINGLE_EXT("IN1L LP Switch", MADERA_ADC_DIGITAL_VOLUME_1L,
	       MADERA_IN1L_LP_MODE_SHIFT, 1, 0,
	       snd_soc_get_volsw, madera_lp_mode_put),
SOC_SINGLE_EXT("IN1R LP Switch", MADERA_ADC_DIGITAL_VOLUME_1R,
	       MADERA_IN1L_LP_MODE_SHIFT, 1, 0,
	       snd_soc_get_volsw, madera_lp_mode_put),
SOC_SINGLE_EXT("IN2L LP Switch", MADERA_ADC_DIGITAL_VOLUME_2L,
	       MADERA_IN1L_LP_MODE_SHIFT, 1, 0,
	       snd_soc_get_volsw, madera_lp_mode_put),
SOC_SINGLE_EXT("IN2R LP Switch", MADERA_ADC_DIGITAL_VOLUME_2R,
	       MADERA_IN1L_LP_MODE_SHIFT, 1, 0,
	       snd_soc_get_volsw, madera_lp_mode_put),

SOC_SINGLE("IN1L HPF Switch", MADERA_IN1L_CONTROL,
	   MADERA_IN1L_HPF_SHIFT, 1, 0),
SOC_SINGLE("IN1R HPF Switch", MADERA_IN1R_CONTROL,
	   MADERA_IN1R_HPF_SHIFT, 1, 0),
SOC_SINGLE("IN2L HPF Switch", MADERA_IN2L_CONTROL,
	   MADERA_IN2L_HPF_SHIFT, 1, 0),
SOC_SINGLE("IN2R HPF Switch", MADERA_IN2R_CONTROL,
	   MADERA_IN2R_HPF_SHIFT, 1, 0),
SOC_SINGLE("IN3L HPF Switch", MADERA_IN3L_CONTROL,
	   MADERA_IN3L_HPF_SHIFT, 1, 0),
SOC_SINGLE("IN3R HPF Switch", MADERA_IN3R_CONTROL,
	   MADERA_IN3R_HPF_SHIFT, 1, 0),
SOC_SINGLE("IN4L HPF Switch", MADERA_IN4L_CONTROL,
	   MADERA_IN4L_HPF_SHIFT, 1, 0),
SOC_SINGLE("IN4R HPF Switch", MADERA_IN4R_CONTROL,
	   MADERA_IN4R_HPF_SHIFT, 1, 0),

SOC_SINGLE_TLV("IN1L Digital Volume", MADERA_ADC_DIGITAL_VOLUME_1L,
	       MADERA_IN1L_DIG_VOL_SHIFT, 0xbf, 0, madera_digital_tlv),
SOC_SINGLE_TLV("IN1R Digital Volume", MADERA_ADC_DIGITAL_VOLUME_1R,
	       MADERA_IN1R_DIG_VOL_SHIFT, 0xbf, 0, madera_digital_tlv),
SOC_SINGLE_TLV("IN2L Digital Volume", MADERA_ADC_DIGITAL_VOLUME_2L,
	       MADERA_IN2L_DIG_VOL_SHIFT, 0xbf, 0, madera_digital_tlv),
SOC_SINGLE_TLV("IN2R Digital Volume", MADERA_ADC_DIGITAL_VOLUME_2R,
	       MADERA_IN2R_DIG_VOL_SHIFT, 0xbf, 0, madera_digital_tlv),
SOC_SINGLE_TLV("IN3L Digital Volume", MADERA_ADC_DIGITAL_VOLUME_3L,
	       MADERA_IN3L_DIG_VOL_SHIFT, 0xbf, 0, madera_digital_tlv),
SOC_SINGLE_TLV("IN3R Digital Volume", MADERA_ADC_DIGITAL_VOLUME_3R,
	       MADERA_IN3R_DIG_VOL_SHIFT, 0xbf, 0, madera_digital_tlv),
SOC_SINGLE_TLV("IN4L Digital Volume", MADERA_ADC_DIGITAL_VOLUME_4L,
	       MADERA_IN4L_DIG_VOL_SHIFT, 0xbf, 0, madera_digital_tlv),
SOC_SINGLE_TLV("IN4R Digital Volume", MADERA_ADC_DIGITAL_VOLUME_4R,
	       MADERA_IN4R_DIG_VOL_SHIFT, 0xbf, 0, madera_digital_tlv),

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

SOC_SINGLE("DAC High Performance Mode Switch", MADERA_OUTPUT_RATE_1,
	   MADERA_CP_DAC_MODE_SHIFT, 1, 0),

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
MADERA_RATE_ENUM("ASRC1 Rate 1", madera_asrc1_bidir_rate[0]),
MADERA_RATE_ENUM("ASRC1 Rate 2", madera_asrc1_bidir_rate[1]),

WM_ADSP2_PRELOAD_SWITCH("DSP1", 1),

MADERA_MIXER_CONTROLS("DSP1L", MADERA_DSP1LMIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("DSP1R", MADERA_DSP1RMIX_INPUT_1_SOURCE),

SOC_SINGLE_TLV("Noise Generator Volume", MADERA_COMFORT_NOISE_GENERATOR,
	       MADERA_NOISE_GEN_GAIN_SHIFT, 0x16, 0, madera_noise_tlv),

MADERA_MIXER_CONTROLS("HPOUT1L", MADERA_OUT1LMIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("HPOUT1R", MADERA_OUT1RMIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("HPOUT2L", MADERA_OUT2LMIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("HPOUT2R", MADERA_OUT2RMIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("HPOUT3L", MADERA_OUT3LMIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("HPOUT3R", MADERA_OUT3RMIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("SPKDAT1L", MADERA_OUT5LMIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("SPKDAT1R", MADERA_OUT5RMIX_INPUT_1_SOURCE),

SOC_SINGLE("HPOUT1 SC Protect Switch", MADERA_HP1_SHORT_CIRCUIT_CTRL,
	   MADERA_HP1_SC_ENA_SHIFT, 1, 0),
SOC_SINGLE("HPOUT2 SC Protect Switch", MADERA_HP2_SHORT_CIRCUIT_CTRL,
	   MADERA_HP2_SC_ENA_SHIFT, 1, 0),
SOC_SINGLE("HPOUT3 SC Protect Switch", MADERA_HP3_SHORT_CIRCUIT_CTRL,
	   MADERA_HP3_SC_ENA_SHIFT, 1, 0),

SOC_SINGLE("SPKDAT1 High Performance Switch", MADERA_OUTPUT_PATH_CONFIG_5L,
	   MADERA_OUT5_OSR_SHIFT, 1, 0),

SOC_DOUBLE_R("HPOUT1 Digital Switch", MADERA_DAC_DIGITAL_VOLUME_1L,
	     MADERA_DAC_DIGITAL_VOLUME_1R, MADERA_OUT1L_MUTE_SHIFT, 1, 1),
SOC_DOUBLE_R("HPOUT2 Digital Switch", MADERA_DAC_DIGITAL_VOLUME_2L,
	     MADERA_DAC_DIGITAL_VOLUME_2R, MADERA_OUT2L_MUTE_SHIFT, 1, 1),
SOC_DOUBLE_R("HPOUT3 Digital Switch", MADERA_DAC_DIGITAL_VOLUME_3L,
	     MADERA_DAC_DIGITAL_VOLUME_3R, MADERA_OUT3L_MUTE_SHIFT, 1, 1),
SOC_DOUBLE_R("SPKDAT1 Digital Switch", MADERA_DAC_DIGITAL_VOLUME_5L,
	     MADERA_DAC_DIGITAL_VOLUME_5R, MADERA_OUT5L_MUTE_SHIFT, 1, 1),

SOC_DOUBLE_R_TLV("HPOUT1 Digital Volume", MADERA_DAC_DIGITAL_VOLUME_1L,
		 MADERA_DAC_DIGITAL_VOLUME_1R, MADERA_OUT1L_VOL_SHIFT,
		 0xbf, 0, madera_digital_tlv),
SOC_DOUBLE_R_TLV("HPOUT2 Digital Volume", MADERA_DAC_DIGITAL_VOLUME_2L,
		 MADERA_DAC_DIGITAL_VOLUME_2R, MADERA_OUT2L_VOL_SHIFT,
		 0xbf, 0, madera_digital_tlv),
SOC_DOUBLE_R_TLV("HPOUT3 Digital Volume", MADERA_DAC_DIGITAL_VOLUME_3L,
		 MADERA_DAC_DIGITAL_VOLUME_3R, MADERA_OUT3L_VOL_SHIFT,
		 0xbf, 0, madera_digital_tlv),
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

SOC_ENUM_EXT("DFC1RX Width", madera_dfc_width[0],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC1RX Type", madera_dfc_type[0],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC1TX Width", madera_dfc_width[1],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC1TX Type", madera_dfc_type[1],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC2RX Width", madera_dfc_width[2],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC2RX Type", madera_dfc_type[2],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC2TX Width", madera_dfc_width[3],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC2TX Type", madera_dfc_type[3],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC3RX Width", madera_dfc_width[4],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC3RX Type", madera_dfc_type[4],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC3TX Width", madera_dfc_width[5],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC3TX Type", madera_dfc_type[5],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC4RX Width", madera_dfc_width[6],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC4RX Type", madera_dfc_type[6],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC4TX Width", madera_dfc_width[7],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC4TX Type", madera_dfc_type[7],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC5RX Width", madera_dfc_width[8],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC5RX Type", madera_dfc_type[8],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC5TX Width", madera_dfc_width[9],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC5TX Type", madera_dfc_type[9],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC6RX Width", madera_dfc_width[10],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC6RX Type", madera_dfc_type[10],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC6TX Width", madera_dfc_width[11],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC6TX Type", madera_dfc_type[11],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC7RX Width", madera_dfc_width[12],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC7RX Type", madera_dfc_type[12],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC7TX Width", madera_dfc_width[13],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC7TX Type", madera_dfc_type[13],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC8RX Width", madera_dfc_width[14],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC8RX Type", madera_dfc_type[14],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC8TX Width", madera_dfc_width[15],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),
SOC_ENUM_EXT("DFC8TX Type", madera_dfc_type[15],
	     snd_soc_get_क्रमागत_द्विगुन, madera_dfc_put),

CS47L92_NG_SRC("HPOUT1L", MADERA_NOISE_GATE_SELECT_1L),
CS47L92_NG_SRC("HPOUT1R", MADERA_NOISE_GATE_SELECT_1R),
CS47L92_NG_SRC("HPOUT2L", MADERA_NOISE_GATE_SELECT_2L),
CS47L92_NG_SRC("HPOUT2R", MADERA_NOISE_GATE_SELECT_2R),
CS47L92_NG_SRC("HPOUT3L", MADERA_NOISE_GATE_SELECT_3L),
CS47L92_NG_SRC("HPOUT3R", MADERA_NOISE_GATE_SELECT_3R),
CS47L92_NG_SRC("SPKDAT1L", MADERA_NOISE_GATE_SELECT_5L),
CS47L92_NG_SRC("SPKDAT1R", MADERA_NOISE_GATE_SELECT_5R),

MADERA_MIXER_CONTROLS("AIF1TX1", MADERA_AIF1TX1MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF1TX2", MADERA_AIF1TX2MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF1TX3", MADERA_AIF1TX3MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF1TX4", MADERA_AIF1TX4MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF1TX5", MADERA_AIF1TX5MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF1TX6", MADERA_AIF1TX6MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF1TX7", MADERA_AIF1TX7MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF1TX8", MADERA_AIF1TX8MIX_INPUT_1_SOURCE),

MADERA_MIXER_CONTROLS("AIF2TX1", MADERA_AIF2TX1MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF2TX2", MADERA_AIF2TX2MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF2TX3", MADERA_AIF2TX3MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF2TX4", MADERA_AIF2TX4MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF2TX5", MADERA_AIF2TX5MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF2TX6", MADERA_AIF2TX6MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF2TX7", MADERA_AIF2TX7MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF2TX8", MADERA_AIF2TX8MIX_INPUT_1_SOURCE),

MADERA_MIXER_CONTROLS("AIF3TX1", MADERA_AIF3TX1MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF3TX2", MADERA_AIF3TX2MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF3TX3", MADERA_AIF3TX3MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("AIF3TX4", MADERA_AIF3TX4MIX_INPUT_1_SOURCE),

MADERA_MIXER_CONTROLS("SLIMTX1", MADERA_SLIMTX1MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("SLIMTX2", MADERA_SLIMTX2MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("SLIMTX3", MADERA_SLIMTX3MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("SLIMTX4", MADERA_SLIMTX4MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("SLIMTX5", MADERA_SLIMTX5MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("SLIMTX6", MADERA_SLIMTX6MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("SLIMTX7", MADERA_SLIMTX7MIX_INPUT_1_SOURCE),
MADERA_MIXER_CONTROLS("SLIMTX8", MADERA_SLIMTX8MIX_INPUT_1_SOURCE),

MADERA_GAINMUX_CONTROLS("SPDIFTX1", MADERA_SPDIF1TX1MIX_INPUT_1_SOURCE),
MADERA_GAINMUX_CONTROLS("SPDIFTX2", MADERA_SPDIF1TX2MIX_INPUT_1_SOURCE),

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
MADERA_MIXER_ENUMS(OUT2L, MADERA_OUT2LMIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(OUT2R, MADERA_OUT2RMIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(OUT3L, MADERA_OUT3LMIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(OUT3R, MADERA_OUT3RMIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(SPKDAT1L, MADERA_OUT5LMIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(SPKDAT1R, MADERA_OUT5RMIX_INPUT_1_SOURCE);

MADERA_MIXER_ENUMS(AIF1TX1, MADERA_AIF1TX1MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF1TX2, MADERA_AIF1TX2MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF1TX3, MADERA_AIF1TX3MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF1TX4, MADERA_AIF1TX4MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF1TX5, MADERA_AIF1TX5MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF1TX6, MADERA_AIF1TX6MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF1TX7, MADERA_AIF1TX7MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF1TX8, MADERA_AIF1TX8MIX_INPUT_1_SOURCE);

MADERA_MIXER_ENUMS(AIF2TX1, MADERA_AIF2TX1MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF2TX2, MADERA_AIF2TX2MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF2TX3, MADERA_AIF2TX3MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF2TX4, MADERA_AIF2TX4MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF2TX5, MADERA_AIF2TX5MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF2TX6, MADERA_AIF2TX6MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF2TX7, MADERA_AIF2TX7MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF2TX8, MADERA_AIF2TX8MIX_INPUT_1_SOURCE);

MADERA_MIXER_ENUMS(AIF3TX1, MADERA_AIF3TX1MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF3TX2, MADERA_AIF3TX2MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF3TX3, MADERA_AIF3TX3MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(AIF3TX4, MADERA_AIF3TX4MIX_INPUT_1_SOURCE);

MADERA_MIXER_ENUMS(SLIMTX1, MADERA_SLIMTX1MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(SLIMTX2, MADERA_SLIMTX2MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(SLIMTX3, MADERA_SLIMTX3MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(SLIMTX4, MADERA_SLIMTX4MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(SLIMTX5, MADERA_SLIMTX5MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(SLIMTX6, MADERA_SLIMTX6MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(SLIMTX7, MADERA_SLIMTX7MIX_INPUT_1_SOURCE);
MADERA_MIXER_ENUMS(SLIMTX8, MADERA_SLIMTX8MIX_INPUT_1_SOURCE);

MADERA_MUX_ENUMS(SPD1TX1, MADERA_SPDIF1TX1MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(SPD1TX2, MADERA_SPDIF1TX2MIX_INPUT_1_SOURCE);

MADERA_MUX_ENUMS(ASRC1IN1L, MADERA_ASRC1_1LMIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(ASRC1IN1R, MADERA_ASRC1_1RMIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(ASRC1IN2L, MADERA_ASRC1_2LMIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(ASRC1IN2R, MADERA_ASRC1_2RMIX_INPUT_1_SOURCE);

MADERA_MUX_ENUMS(ISRC1INT1, MADERA_ISRC1INT1MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(ISRC1INT2, MADERA_ISRC1INT2MIX_INPUT_1_SOURCE);

MADERA_MUX_ENUMS(ISRC1DEC1, MADERA_ISRC1DEC1MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(ISRC1DEC2, MADERA_ISRC1DEC2MIX_INPUT_1_SOURCE);

MADERA_MUX_ENUMS(ISRC2INT1, MADERA_ISRC2INT1MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(ISRC2INT2, MADERA_ISRC2INT2MIX_INPUT_1_SOURCE);

MADERA_MUX_ENUMS(ISRC2DEC1, MADERA_ISRC2DEC1MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(ISRC2DEC2, MADERA_ISRC2DEC2MIX_INPUT_1_SOURCE);

MADERA_MUX_ENUMS(DFC1, MADERA_DFC1MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(DFC2, MADERA_DFC2MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(DFC3, MADERA_DFC3MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(DFC4, MADERA_DFC4MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(DFC5, MADERA_DFC5MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(DFC6, MADERA_DFC6MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(DFC7, MADERA_DFC7MIX_INPUT_1_SOURCE);
MADERA_MUX_ENUMS(DFC8, MADERA_DFC8MIX_INPUT_1_SOURCE);

अटल स्थिर अक्षर * स्थिर cs47l92_aec_loopback_texts[] = अणु
	"HPOUT1L", "HPOUT1R", "HPOUT2L", "HPOUT2R", "HPOUT3L", "HPOUT3R",
	"SPKDAT1L", "SPKDAT1R",
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक cs47l92_aec_loopback_values[] = अणु
	0, 1, 2, 3, 4, 5, 8, 9
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत cs47l92_aec_loopback =
	SOC_VALUE_ENUM_SINGLE(MADERA_DAC_AEC_CONTROL_1,
			      MADERA_AEC1_LOOPBACK_SRC_SHIFT, 0xf,
			      ARRAY_SIZE(cs47l92_aec_loopback_texts),
			      cs47l92_aec_loopback_texts,
			      cs47l92_aec_loopback_values);

अटल स्थिर काष्ठा snd_kcontrol_new cs47l92_aec_loopback_mux =
	SOC_DAPM_ENUM("AEC1 Loopback", cs47l92_aec_loopback);

अटल स्थिर काष्ठा snd_soc_dapm_widget cs47l92_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_SUPPLY("SYSCLK", MADERA_SYSTEM_CLOCK_1, MADERA_SYSCLK_ENA_SHIFT,
		    0, madera_sysclk_ev,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		    SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("ASYNCCLK", MADERA_ASYNC_CLOCK_1,
		    MADERA_ASYNC_CLK_ENA_SHIFT, 0, madera_clk_ev,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("OPCLK", MADERA_OUTPUT_SYSTEM_CLOCK,
		    MADERA_OPCLK_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("ASYNCOPCLK", MADERA_OUTPUT_ASYNC_CLOCK,
		    MADERA_OPCLK_ASYNC_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("DSPCLK", MADERA_DSP_CLOCK_1, MADERA_DSP_CLK_ENA_SHIFT,
		    0, madera_clk_ev,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

SND_SOC_DAPM_REGULATOR_SUPPLY("CPVDD1", 20, 0),
SND_SOC_DAPM_REGULATOR_SUPPLY("CPVDD2", 20, 0),
SND_SOC_DAPM_REGULATOR_SUPPLY("MICVDD", 0, SND_SOC_DAPM_REGULATOR_BYPASS),

SND_SOC_DAPM_SUPPLY("MICBIAS1", MADERA_MIC_BIAS_CTRL_1,
		    MADERA_MICB1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("MICBIAS2", MADERA_MIC_BIAS_CTRL_2,
		    MADERA_MICB1_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_SUPPLY("MICBIAS1A", MADERA_MIC_BIAS_CTRL_5,
		    MADERA_MICB1A_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("MICBIAS1B", MADERA_MIC_BIAS_CTRL_5,
		    MADERA_MICB1B_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("MICBIAS1C", MADERA_MIC_BIAS_CTRL_5,
		    MADERA_MICB1C_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("MICBIAS1D", MADERA_MIC_BIAS_CTRL_5,
		    MADERA_MICB1D_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_SUPPLY("MICBIAS2A", MADERA_MIC_BIAS_CTRL_6,
		    MADERA_MICB2A_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("MICBIAS2B", MADERA_MIC_BIAS_CTRL_6,
		    MADERA_MICB2B_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_SUPPLY("FXCLK", SND_SOC_NOPM,
		    MADERA_DOM_GRP_FX, 0,
		    madera_करोमुख्य_clk_ev,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("ASRC1CLK", SND_SOC_NOPM,
		    MADERA_DOM_GRP_ASRC1, 0,
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
		    cs47l92_outclk_ev,
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
SND_SOC_DAPM_SUPPLY("SLIMBUSCLK", SND_SOC_NOPM,
		    MADERA_DOM_GRP_SLIMBUS, 0,
		    madera_करोमुख्य_clk_ev,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("PWMCLK", SND_SOC_NOPM,
		    MADERA_DOM_GRP_PWM, 0,
		    madera_करोमुख्य_clk_ev,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("DFCCLK", SND_SOC_NOPM,
		    MADERA_DOM_GRP_DFC, 0,
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
SND_SOC_DAPM_INPUT("IN1BR"),
SND_SOC_DAPM_INPUT("IN2ALN"),
SND_SOC_DAPM_INPUT("IN2ALP"),
SND_SOC_DAPM_INPUT("IN2BL"),
SND_SOC_DAPM_INPUT("IN2ARN"),
SND_SOC_DAPM_INPUT("IN2ARP"),
SND_SOC_DAPM_INPUT("IN2BR"),

SND_SOC_DAPM_MUX("IN1L Analog Mux", SND_SOC_NOPM, 0, 0, &madera_inmux[0]),
SND_SOC_DAPM_MUX("IN1R Analog Mux", SND_SOC_NOPM, 0, 0, &madera_inmux[1]),
SND_SOC_DAPM_MUX("IN2L Analog Mux", SND_SOC_NOPM, 0, 0, &madera_inmux[2]),
SND_SOC_DAPM_MUX("IN2R Analog Mux", SND_SOC_NOPM, 0, 0, &madera_inmux[3]),

SND_SOC_DAPM_MUX("IN1L Mode", SND_SOC_NOPM, 0, 0, &madera_inmode[0]),
SND_SOC_DAPM_MUX("IN1R Mode", SND_SOC_NOPM, 0, 0, &madera_inmode[0]),

SND_SOC_DAPM_MUX("IN2L Mode", SND_SOC_NOPM, 0, 0, &madera_inmode[1]),
SND_SOC_DAPM_MUX("IN2R Mode", SND_SOC_NOPM, 0, 0, &madera_inmode[1]),

SND_SOC_DAPM_DEMUX("OUT3 Demux", SND_SOC_NOPM, 0, 0, &cs47l92_outdemux),
SND_SOC_DAPM_MUX("OUT3 Mono Mux", SND_SOC_NOPM, 0, 0, &cs47l92_outdemux),

SND_SOC_DAPM_OUTPUT("DRC1 Signal Activity"),
SND_SOC_DAPM_OUTPUT("DRC2 Signal Activity"),

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
SND_SOC_DAPM_AIF_OUT("AIF1TX7", शून्य, 6,
		     MADERA_AIF1_TX_ENABLES, MADERA_AIF1TX7_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX8", शून्य, 7,
		     MADERA_AIF1_TX_ENABLES, MADERA_AIF1TX8_ENA_SHIFT, 0),

SND_SOC_DAPM_AIF_OUT("AIF2TX1", शून्य, 0,
		     MADERA_AIF2_TX_ENABLES, MADERA_AIF2TX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF2TX2", शून्य, 1,
		     MADERA_AIF2_TX_ENABLES, MADERA_AIF2TX2_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF2TX3", शून्य, 2,
		     MADERA_AIF2_TX_ENABLES, MADERA_AIF2TX3_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF2TX4", शून्य, 3,
		     MADERA_AIF2_TX_ENABLES, MADERA_AIF2TX4_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF2TX5", शून्य, 4,
		     MADERA_AIF2_TX_ENABLES, MADERA_AIF2TX5_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF2TX6", शून्य, 5,
		     MADERA_AIF2_TX_ENABLES, MADERA_AIF2TX6_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF2TX7", शून्य, 6,
		     MADERA_AIF2_TX_ENABLES, MADERA_AIF2TX7_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF2TX8", शून्य, 7,
		     MADERA_AIF2_TX_ENABLES, MADERA_AIF2TX8_ENA_SHIFT, 0),

SND_SOC_DAPM_AIF_OUT("SLIMTX1", शून्य, 0,
		     MADERA_SLIMBUS_TX_CHANNEL_ENABLE,
		     MADERA_SLIMTX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("SLIMTX2", शून्य, 1,
		     MADERA_SLIMBUS_TX_CHANNEL_ENABLE,
		     MADERA_SLIMTX2_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("SLIMTX3", शून्य, 2,
		     MADERA_SLIMBUS_TX_CHANNEL_ENABLE,
		     MADERA_SLIMTX3_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("SLIMTX4", शून्य, 3,
		     MADERA_SLIMBUS_TX_CHANNEL_ENABLE,
		     MADERA_SLIMTX4_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("SLIMTX5", शून्य, 4,
		     MADERA_SLIMBUS_TX_CHANNEL_ENABLE,
		     MADERA_SLIMTX5_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("SLIMTX6", शून्य, 5,
		     MADERA_SLIMBUS_TX_CHANNEL_ENABLE,
		     MADERA_SLIMTX6_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("SLIMTX7", शून्य, 6,
		     MADERA_SLIMBUS_TX_CHANNEL_ENABLE,
		     MADERA_SLIMTX7_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("SLIMTX8", शून्य, 7,
		     MADERA_SLIMBUS_TX_CHANNEL_ENABLE,
		     MADERA_SLIMTX8_ENA_SHIFT, 0),

SND_SOC_DAPM_AIF_OUT("AIF3TX1", शून्य, 0,
		     MADERA_AIF3_TX_ENABLES, MADERA_AIF3TX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF3TX2", शून्य, 1,
		     MADERA_AIF3_TX_ENABLES, MADERA_AIF3TX2_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF3TX3", शून्य, 2,
		     MADERA_AIF3_TX_ENABLES, MADERA_AIF3TX3_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF3TX4", शून्य, 3,
		     MADERA_AIF3_TX_ENABLES, MADERA_AIF3TX4_ENA_SHIFT, 0),

SND_SOC_DAPM_PGA_E("OUT1L", SND_SOC_NOPM,
		   MADERA_OUT1L_ENA_SHIFT, 0, शून्य, 0, madera_hp_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT1R", SND_SOC_NOPM,
		   MADERA_OUT1R_ENA_SHIFT, 0, शून्य, 0, madera_hp_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT2L", SND_SOC_NOPM,
		   MADERA_OUT2L_ENA_SHIFT, 0, शून्य, 0, madera_hp_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT2R", SND_SOC_NOPM,
		   MADERA_OUT2R_ENA_SHIFT, 0, शून्य, 0, madera_hp_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT3L", MADERA_OUTPUT_ENABLES_1,
		   MADERA_OUT3L_ENA_SHIFT, 0, शून्य, 0, madera_out_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT3R", MADERA_OUTPUT_ENABLES_1,
		   MADERA_OUT3R_ENA_SHIFT, 0, शून्य, 0, madera_out_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
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
		 &cs47l92_aec_loopback_mux),

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
SND_SOC_DAPM_PGA_E("IN3L", MADERA_INPUT_ENABLES, MADERA_IN3L_ENA_SHIFT,
		   0, शून्य, 0, madera_in_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("IN3R", MADERA_INPUT_ENABLES, MADERA_IN3R_ENA_SHIFT,
		   0, शून्य, 0, madera_in_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("IN4L", MADERA_INPUT_ENABLES, MADERA_IN4L_ENA_SHIFT,
		   0, शून्य, 0, madera_in_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("IN4R", MADERA_INPUT_ENABLES, MADERA_IN4R_ENA_SHIFT,
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
SND_SOC_DAPM_AIF_IN("AIF1RX7", शून्य, 6,
		    MADERA_AIF1_RX_ENABLES, MADERA_AIF1RX7_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX8", शून्य, 7,
		    MADERA_AIF1_RX_ENABLES, MADERA_AIF1RX8_ENA_SHIFT, 0),

SND_SOC_DAPM_AIF_IN("AIF2RX1", शून्य, 0,
		    MADERA_AIF2_RX_ENABLES, MADERA_AIF2RX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF2RX2", शून्य, 1,
		    MADERA_AIF2_RX_ENABLES, MADERA_AIF2RX2_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF2RX3", शून्य, 2,
		    MADERA_AIF2_RX_ENABLES, MADERA_AIF2RX3_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF2RX4", शून्य, 3,
		    MADERA_AIF2_RX_ENABLES, MADERA_AIF2RX4_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF2RX5", शून्य, 4,
		    MADERA_AIF2_RX_ENABLES, MADERA_AIF2RX5_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF2RX6", शून्य, 5,
		    MADERA_AIF2_RX_ENABLES, MADERA_AIF2RX6_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF2RX7", शून्य, 6,
		    MADERA_AIF2_RX_ENABLES, MADERA_AIF2RX7_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF2RX8", शून्य, 7,
		    MADERA_AIF2_RX_ENABLES, MADERA_AIF2RX8_ENA_SHIFT, 0),

SND_SOC_DAPM_AIF_IN("AIF3RX1", शून्य, 0,
		    MADERA_AIF3_RX_ENABLES, MADERA_AIF3RX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF3RX2", शून्य, 1,
		    MADERA_AIF3_RX_ENABLES, MADERA_AIF3RX2_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF3RX3", शून्य, 2,
		    MADERA_AIF3_RX_ENABLES, MADERA_AIF3RX3_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF3RX4", शून्य, 3,
		    MADERA_AIF3_RX_ENABLES, MADERA_AIF3RX4_ENA_SHIFT, 0),

SND_SOC_DAPM_AIF_IN("SLIMRX1", शून्य, 0, MADERA_SLIMBUS_RX_CHANNEL_ENABLE,
		    MADERA_SLIMRX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("SLIMRX2", शून्य, 1, MADERA_SLIMBUS_RX_CHANNEL_ENABLE,
		    MADERA_SLIMRX2_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("SLIMRX3", शून्य, 2, MADERA_SLIMBUS_RX_CHANNEL_ENABLE,
		    MADERA_SLIMRX3_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("SLIMRX4", शून्य, 3, MADERA_SLIMBUS_RX_CHANNEL_ENABLE,
		    MADERA_SLIMRX4_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("SLIMRX5", शून्य, 4, MADERA_SLIMBUS_RX_CHANNEL_ENABLE,
		    MADERA_SLIMRX5_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("SLIMRX6", शून्य, 5, MADERA_SLIMBUS_RX_CHANNEL_ENABLE,
		    MADERA_SLIMRX6_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("SLIMRX7", शून्य, 6, MADERA_SLIMBUS_RX_CHANNEL_ENABLE,
		    MADERA_SLIMRX7_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("SLIMRX8", शून्य, 7, MADERA_SLIMBUS_RX_CHANNEL_ENABLE,
		    MADERA_SLIMRX8_ENA_SHIFT, 0),

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

SND_SOC_DAPM_PGA("LHPF1", MADERA_HPLPF1_1, MADERA_LHPF1_ENA_SHIFT, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("LHPF2", MADERA_HPLPF2_1, MADERA_LHPF2_ENA_SHIFT, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("LHPF3", MADERA_HPLPF3_1, MADERA_LHPF3_ENA_SHIFT, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("LHPF4", MADERA_HPLPF4_1, MADERA_LHPF4_ENA_SHIFT, 0,
		 शून्य, 0),

SND_SOC_DAPM_PGA("ASRC1IN1L", MADERA_ASRC1_ENABLE,
		 MADERA_ASRC1_IN1L_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ASRC1IN1R", MADERA_ASRC1_ENABLE,
		 MADERA_ASRC1_IN1R_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ASRC1IN2L", MADERA_ASRC1_ENABLE,
		 MADERA_ASRC1_IN2L_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ASRC1IN2R", MADERA_ASRC1_ENABLE,
		 MADERA_ASRC1_IN2R_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("ISRC1DEC1", MADERA_ISRC_1_CTRL_3,
		 MADERA_ISRC1_DEC1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ISRC1DEC2", MADERA_ISRC_1_CTRL_3,
		 MADERA_ISRC1_DEC2_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("ISRC1INT1", MADERA_ISRC_1_CTRL_3,
		 MADERA_ISRC1_INT1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ISRC1INT2", MADERA_ISRC_1_CTRL_3,
		 MADERA_ISRC1_INT2_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("ISRC2DEC1", MADERA_ISRC_2_CTRL_3,
		 MADERA_ISRC2_DEC1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ISRC2DEC2", MADERA_ISRC_2_CTRL_3,
		 MADERA_ISRC2_DEC2_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("ISRC2INT1", MADERA_ISRC_2_CTRL_3,
		 MADERA_ISRC2_INT1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ISRC2INT2", MADERA_ISRC_2_CTRL_3,
		 MADERA_ISRC2_INT2_ENA_SHIFT, 0, शून्य, 0),

WM_ADSP2("DSP1", 0, cs47l92_adsp_घातer_ev),

/* end of ordered widget list */

SND_SOC_DAPM_PGA("DFC1", MADERA_DFC1_CTRL, MADERA_DFC1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("DFC2", MADERA_DFC2_CTRL, MADERA_DFC1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("DFC3", MADERA_DFC3_CTRL, MADERA_DFC1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("DFC4", MADERA_DFC4_CTRL, MADERA_DFC1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("DFC5", MADERA_DFC5_CTRL, MADERA_DFC1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("DFC6", MADERA_DFC6_CTRL, MADERA_DFC1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("DFC7", MADERA_DFC7_CTRL, MADERA_DFC1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("DFC8", MADERA_DFC8_CTRL, MADERA_DFC1_ENA_SHIFT, 0, शून्य, 0),

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
MADERA_MIXER_WIDGETS(OUT2L, "HPOUT2L"),
MADERA_MIXER_WIDGETS(OUT2R, "HPOUT2R"),
MADERA_MIXER_WIDGETS(OUT3L, "HPOUT3L"),
MADERA_MIXER_WIDGETS(OUT3R, "HPOUT3R"),
MADERA_MIXER_WIDGETS(SPKDAT1L, "SPKDAT1L"),
MADERA_MIXER_WIDGETS(SPKDAT1R, "SPKDAT1R"),

MADERA_MIXER_WIDGETS(AIF1TX1, "AIF1TX1"),
MADERA_MIXER_WIDGETS(AIF1TX2, "AIF1TX2"),
MADERA_MIXER_WIDGETS(AIF1TX3, "AIF1TX3"),
MADERA_MIXER_WIDGETS(AIF1TX4, "AIF1TX4"),
MADERA_MIXER_WIDGETS(AIF1TX5, "AIF1TX5"),
MADERA_MIXER_WIDGETS(AIF1TX6, "AIF1TX6"),
MADERA_MIXER_WIDGETS(AIF1TX7, "AIF1TX7"),
MADERA_MIXER_WIDGETS(AIF1TX8, "AIF1TX8"),

MADERA_MIXER_WIDGETS(AIF2TX1, "AIF2TX1"),
MADERA_MIXER_WIDGETS(AIF2TX2, "AIF2TX2"),
MADERA_MIXER_WIDGETS(AIF2TX3, "AIF2TX3"),
MADERA_MIXER_WIDGETS(AIF2TX4, "AIF2TX4"),
MADERA_MIXER_WIDGETS(AIF2TX5, "AIF2TX5"),
MADERA_MIXER_WIDGETS(AIF2TX6, "AIF2TX6"),
MADERA_MIXER_WIDGETS(AIF2TX7, "AIF2TX7"),
MADERA_MIXER_WIDGETS(AIF2TX8, "AIF2TX8"),

MADERA_MIXER_WIDGETS(AIF3TX1, "AIF3TX1"),
MADERA_MIXER_WIDGETS(AIF3TX2, "AIF3TX2"),
MADERA_MIXER_WIDGETS(AIF3TX3, "AIF3TX3"),
MADERA_MIXER_WIDGETS(AIF3TX4, "AIF3TX4"),

MADERA_MIXER_WIDGETS(SLIMTX1, "SLIMTX1"),
MADERA_MIXER_WIDGETS(SLIMTX2, "SLIMTX2"),
MADERA_MIXER_WIDGETS(SLIMTX3, "SLIMTX3"),
MADERA_MIXER_WIDGETS(SLIMTX4, "SLIMTX4"),
MADERA_MIXER_WIDGETS(SLIMTX5, "SLIMTX5"),
MADERA_MIXER_WIDGETS(SLIMTX6, "SLIMTX6"),
MADERA_MIXER_WIDGETS(SLIMTX7, "SLIMTX7"),
MADERA_MIXER_WIDGETS(SLIMTX8, "SLIMTX8"),

MADERA_MUX_WIDGETS(SPD1TX1, "SPDIFTX1"),
MADERA_MUX_WIDGETS(SPD1TX2, "SPDIFTX2"),

MADERA_MUX_WIDGETS(ASRC1IN1L, "ASRC1IN1L"),
MADERA_MUX_WIDGETS(ASRC1IN1R, "ASRC1IN1R"),
MADERA_MUX_WIDGETS(ASRC1IN2L, "ASRC1IN2L"),
MADERA_MUX_WIDGETS(ASRC1IN2R, "ASRC1IN2R"),

MADERA_DSP_WIDGETS(DSP1, "DSP1"),

MADERA_MUX_WIDGETS(ISRC1DEC1, "ISRC1DEC1"),
MADERA_MUX_WIDGETS(ISRC1DEC2, "ISRC1DEC2"),

MADERA_MUX_WIDGETS(ISRC1INT1, "ISRC1INT1"),
MADERA_MUX_WIDGETS(ISRC1INT2, "ISRC1INT2"),

MADERA_MUX_WIDGETS(ISRC2DEC1, "ISRC2DEC1"),
MADERA_MUX_WIDGETS(ISRC2DEC2, "ISRC2DEC2"),

MADERA_MUX_WIDGETS(ISRC2INT1, "ISRC2INT1"),
MADERA_MUX_WIDGETS(ISRC2INT2, "ISRC2INT2"),

MADERA_MUX_WIDGETS(DFC1, "DFC1"),
MADERA_MUX_WIDGETS(DFC2, "DFC2"),
MADERA_MUX_WIDGETS(DFC3, "DFC3"),
MADERA_MUX_WIDGETS(DFC4, "DFC4"),
MADERA_MUX_WIDGETS(DFC5, "DFC5"),
MADERA_MUX_WIDGETS(DFC6, "DFC6"),
MADERA_MUX_WIDGETS(DFC7, "DFC7"),
MADERA_MUX_WIDGETS(DFC8, "DFC8"),

SND_SOC_DAPM_OUTPUT("HPOUT1L"),
SND_SOC_DAPM_OUTPUT("HPOUT1R"),
SND_SOC_DAPM_OUTPUT("HPOUT2L"),
SND_SOC_DAPM_OUTPUT("HPOUT2R"),
SND_SOC_DAPM_OUTPUT("HPOUT3L"),
SND_SOC_DAPM_OUTPUT("HPOUT3R"),
SND_SOC_DAPM_OUTPUT("HPOUT4L"),
SND_SOC_DAPM_OUTPUT("HPOUT4R"),
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
	अणु name, "IN1L", "IN1L" पूर्ण, \
	अणु name, "IN1R", "IN1R" पूर्ण, \
	अणु name, "IN2L", "IN2L" पूर्ण, \
	अणु name, "IN2R", "IN2R" पूर्ण, \
	अणु name, "IN3L", "IN3L" पूर्ण, \
	अणु name, "IN3R", "IN3R" पूर्ण, \
	अणु name, "IN4L", "IN4L" पूर्ण, \
	अणु name, "IN4R", "IN4R" पूर्ण, \
	अणु name, "AIF1RX1", "AIF1RX1" पूर्ण, \
	अणु name, "AIF1RX2", "AIF1RX2" पूर्ण, \
	अणु name, "AIF1RX3", "AIF1RX3" पूर्ण, \
	अणु name, "AIF1RX4", "AIF1RX4" पूर्ण, \
	अणु name, "AIF1RX5", "AIF1RX5" पूर्ण, \
	अणु name, "AIF1RX6", "AIF1RX6" पूर्ण, \
	अणु name, "AIF1RX7", "AIF1RX7" पूर्ण, \
	अणु name, "AIF1RX8", "AIF1RX8" पूर्ण, \
	अणु name, "AIF2RX1", "AIF2RX1" पूर्ण, \
	अणु name, "AIF2RX2", "AIF2RX2" पूर्ण, \
	अणु name, "AIF2RX3", "AIF2RX3" पूर्ण, \
	अणु name, "AIF2RX4", "AIF2RX4" पूर्ण, \
	अणु name, "AIF2RX5", "AIF2RX5" पूर्ण, \
	अणु name, "AIF2RX6", "AIF2RX6" पूर्ण, \
	अणु name, "AIF2RX7", "AIF2RX7" पूर्ण, \
	अणु name, "AIF2RX8", "AIF2RX8" पूर्ण, \
	अणु name, "AIF3RX1", "AIF3RX1" पूर्ण, \
	अणु name, "AIF3RX2", "AIF3RX2" पूर्ण, \
	अणु name, "AIF3RX3", "AIF3RX3" पूर्ण, \
	अणु name, "AIF3RX4", "AIF3RX4" पूर्ण, \
	अणु name, "SLIMRX1", "SLIMRX1" पूर्ण, \
	अणु name, "SLIMRX2", "SLIMRX2" पूर्ण, \
	अणु name, "SLIMRX3", "SLIMRX3" पूर्ण, \
	अणु name, "SLIMRX4", "SLIMRX4" पूर्ण, \
	अणु name, "SLIMRX5", "SLIMRX5" पूर्ण, \
	अणु name, "SLIMRX6", "SLIMRX6" पूर्ण, \
	अणु name, "SLIMRX7", "SLIMRX7" पूर्ण, \
	अणु name, "SLIMRX8", "SLIMRX8" पूर्ण, \
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
	अणु name, "ASRC1IN1L", "ASRC1IN1L" पूर्ण, \
	अणु name, "ASRC1IN1R", "ASRC1IN1R" पूर्ण, \
	अणु name, "ASRC1IN2L", "ASRC1IN2L" पूर्ण, \
	अणु name, "ASRC1IN2R", "ASRC1IN2R" पूर्ण, \
	अणु name, "ISRC1DEC1", "ISRC1DEC1" पूर्ण, \
	अणु name, "ISRC1DEC2", "ISRC1DEC2" पूर्ण, \
	अणु name, "ISRC1INT1", "ISRC1INT1" पूर्ण, \
	अणु name, "ISRC1INT2", "ISRC1INT2" पूर्ण, \
	अणु name, "ISRC2DEC1", "ISRC2DEC1" पूर्ण, \
	अणु name, "ISRC2DEC2", "ISRC2DEC2" पूर्ण, \
	अणु name, "ISRC2INT1", "ISRC2INT1" पूर्ण, \
	अणु name, "ISRC2INT2", "ISRC2INT2" पूर्ण, \
	अणु name, "DSP1.1", "DSP1" पूर्ण, \
	अणु name, "DSP1.2", "DSP1" पूर्ण, \
	अणु name, "DSP1.3", "DSP1" पूर्ण, \
	अणु name, "DSP1.4", "DSP1" पूर्ण, \
	अणु name, "DSP1.5", "DSP1" पूर्ण, \
	अणु name, "DSP1.6", "DSP1" पूर्ण, \
	अणु name, "DFC1", "DFC1" पूर्ण, \
	अणु name, "DFC2", "DFC2" पूर्ण, \
	अणु name, "DFC3", "DFC3" पूर्ण, \
	अणु name, "DFC4", "DFC4" पूर्ण, \
	अणु name, "DFC5", "DFC5" पूर्ण, \
	अणु name, "DFC6", "DFC6" पूर्ण, \
	अणु name, "DFC7", "DFC7" पूर्ण, \
	अणु name, "DFC8", "DFC8" पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_route cs47l92_dapm_routes[] = अणु
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
	अणु "OUT2L", शून्य, "OUTCLK" पूर्ण,
	अणु "OUT2R", शून्य, "OUTCLK" पूर्ण,
	अणु "OUT3L", शून्य, "OUTCLK" पूर्ण,
	अणु "OUT3R", शून्य, "OUTCLK" पूर्ण,
	अणु "OUT5L", शून्य, "OUTCLK" पूर्ण,
	अणु "OUT5R", शून्य, "OUTCLK" पूर्ण,
	अणु "AIF1TX1", शून्य, "AIF1TXCLK" पूर्ण,
	अणु "AIF1TX2", शून्य, "AIF1TXCLK" पूर्ण,
	अणु "AIF1TX3", शून्य, "AIF1TXCLK" पूर्ण,
	अणु "AIF1TX4", शून्य, "AIF1TXCLK" पूर्ण,
	अणु "AIF1TX5", शून्य, "AIF1TXCLK" पूर्ण,
	अणु "AIF1TX6", शून्य, "AIF1TXCLK" पूर्ण,
	अणु "AIF1TX7", शून्य, "AIF1TXCLK" पूर्ण,
	अणु "AIF1TX8", शून्य, "AIF1TXCLK" पूर्ण,
	अणु "AIF2TX1", शून्य, "AIF2TXCLK" पूर्ण,
	अणु "AIF2TX2", शून्य, "AIF2TXCLK" पूर्ण,
	अणु "AIF2TX3", शून्य, "AIF2TXCLK" पूर्ण,
	अणु "AIF2TX4", शून्य, "AIF2TXCLK" पूर्ण,
	अणु "AIF2TX5", शून्य, "AIF2TXCLK" पूर्ण,
	अणु "AIF2TX6", शून्य, "AIF2TXCLK" पूर्ण,
	अणु "AIF2TX7", शून्य, "AIF2TXCLK" पूर्ण,
	अणु "AIF2TX8", शून्य, "AIF2TXCLK" पूर्ण,
	अणु "AIF3TX1", शून्य, "AIF3TXCLK" पूर्ण,
	अणु "AIF3TX2", शून्य, "AIF3TXCLK" पूर्ण,
	अणु "AIF3TX3", शून्य, "AIF3TXCLK" पूर्ण,
	अणु "AIF3TX4", शून्य, "AIF3TXCLK" पूर्ण,
	अणु "SLIMTX1", शून्य, "SLIMBUSCLK" पूर्ण,
	अणु "SLIMTX2", शून्य, "SLIMBUSCLK" पूर्ण,
	अणु "SLIMTX3", शून्य, "SLIMBUSCLK" पूर्ण,
	अणु "SLIMTX4", शून्य, "SLIMBUSCLK" पूर्ण,
	अणु "SLIMTX5", शून्य, "SLIMBUSCLK" पूर्ण,
	अणु "SLIMTX6", शून्य, "SLIMBUSCLK" पूर्ण,
	अणु "SLIMTX7", शून्य, "SLIMBUSCLK" पूर्ण,
	अणु "SLIMTX8", शून्य, "SLIMBUSCLK" पूर्ण,
	अणु "SPD1TX1", शून्य, "SPDCLK" पूर्ण,
	अणु "SPD1TX2", शून्य, "SPDCLK" पूर्ण,
	अणु "DSP1", शून्य, "DSP1CLK" पूर्ण,
	अणु "ISRC1DEC1", शून्य, "ISRC1CLK" पूर्ण,
	अणु "ISRC1DEC2", शून्य, "ISRC1CLK" पूर्ण,
	अणु "ISRC1INT1", शून्य, "ISRC1CLK" पूर्ण,
	अणु "ISRC1INT2", शून्य, "ISRC1CLK" पूर्ण,
	अणु "ISRC2DEC1", शून्य, "ISRC2CLK" पूर्ण,
	अणु "ISRC2DEC2", शून्य, "ISRC2CLK" पूर्ण,
	अणु "ISRC2INT1", शून्य, "ISRC2CLK" पूर्ण,
	अणु "ISRC2INT2", शून्य, "ISRC2CLK" पूर्ण,
	अणु "ASRC1IN1L", शून्य, "ASRC1CLK" पूर्ण,
	अणु "ASRC1IN1R", शून्य, "ASRC1CLK" पूर्ण,
	अणु "ASRC1IN2L", शून्य, "ASRC1CLK" पूर्ण,
	अणु "ASRC1IN2R", शून्य, "ASRC1CLK" पूर्ण,
	अणु "DFC1", शून्य, "DFCCLK" पूर्ण,
	अणु "DFC2", शून्य, "DFCCLK" पूर्ण,
	अणु "DFC3", शून्य, "DFCCLK" पूर्ण,
	अणु "DFC4", शून्य, "DFCCLK" पूर्ण,
	अणु "DFC5", शून्य, "DFCCLK" पूर्ण,
	अणु "DFC6", शून्य, "DFCCLK" पूर्ण,
	अणु "DFC7", शून्य, "DFCCLK" पूर्ण,
	अणु "DFC8", शून्य, "DFCCLK" पूर्ण,

	अणु "OUT1L", शून्य, "CPVDD1" पूर्ण,
	अणु "OUT1L", शून्य, "CPVDD2" पूर्ण,
	अणु "OUT1R", शून्य, "CPVDD1" पूर्ण,
	अणु "OUT1R", शून्य, "CPVDD2" पूर्ण,
	अणु "OUT2L", शून्य, "CPVDD1" पूर्ण,
	अणु "OUT2L", शून्य, "CPVDD2" पूर्ण,
	अणु "OUT2R", शून्य, "CPVDD1" पूर्ण,
	अणु "OUT2R", शून्य, "CPVDD2" पूर्ण,
	अणु "OUT3L", शून्य, "CPVDD1" पूर्ण,
	अणु "OUT3L", शून्य, "CPVDD2" पूर्ण,
	अणु "OUT3R", शून्य, "CPVDD1" पूर्ण,
	अणु "OUT3R", शून्य, "CPVDD2" पूर्ण,

	अणु "OUT1L", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT1R", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT2L", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT2R", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT3L", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT3R", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT5L", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT5R", शून्य, "SYSCLK" पूर्ण,

	अणु "SPD1", शून्य, "SYSCLK" पूर्ण,
	अणु "SPD1", शून्य, "SPD1TX1" पूर्ण,
	अणु "SPD1", शून्य, "SPD1TX2" पूर्ण,

	अणु "IN1L", शून्य, "SYSCLK" पूर्ण,
	अणु "IN1R", शून्य, "SYSCLK" पूर्ण,
	अणु "IN2L", शून्य, "SYSCLK" पूर्ण,
	अणु "IN2R", शून्य, "SYSCLK" पूर्ण,
	अणु "IN3L", शून्य, "SYSCLK" पूर्ण,
	अणु "IN3R", शून्य, "SYSCLK" पूर्ण,
	अणु "IN4L", शून्य, "SYSCLK" पूर्ण,
	अणु "IN4R", शून्य, "SYSCLK" पूर्ण,

	अणु "ASRC1IN1L", शून्य, "SYSCLK" पूर्ण,
	अणु "ASRC1IN1R", शून्य, "SYSCLK" पूर्ण,
	अणु "ASRC1IN2L", शून्य, "SYSCLK" पूर्ण,
	अणु "ASRC1IN2R", शून्य, "SYSCLK" पूर्ण,

	अणु "ASRC1IN1L", शून्य, "ASYNCCLK" पूर्ण,
	अणु "ASRC1IN1R", शून्य, "ASYNCCLK" पूर्ण,
	अणु "ASRC1IN2L", शून्य, "ASYNCCLK" पूर्ण,
	अणु "ASRC1IN2R", शून्य, "ASYNCCLK" पूर्ण,

	अणु "MICBIAS1", शून्य, "MICVDD" पूर्ण,
	अणु "MICBIAS2", शून्य, "MICVDD" पूर्ण,

	अणु "MICBIAS1A", शून्य, "MICBIAS1" पूर्ण,
	अणु "MICBIAS1B", शून्य, "MICBIAS1" पूर्ण,
	अणु "MICBIAS1C", शून्य, "MICBIAS1" पूर्ण,
	अणु "MICBIAS1D", शून्य, "MICBIAS1" पूर्ण,

	अणु "MICBIAS2A", शून्य, "MICBIAS2" पूर्ण,
	अणु "MICBIAS2B", शून्य, "MICBIAS2" पूर्ण,

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
	अणु "AIF1 Capture", शून्य, "AIF1TX7" पूर्ण,
	अणु "AIF1 Capture", शून्य, "AIF1TX8" पूर्ण,

	अणु "AIF1RX1", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX2", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX3", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX4", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX5", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX6", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX7", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX8", शून्य, "AIF1 Playback" पूर्ण,

	अणु "AIF2 Capture", शून्य, "AIF2TX1" पूर्ण,
	अणु "AIF2 Capture", शून्य, "AIF2TX2" पूर्ण,
	अणु "AIF2 Capture", शून्य, "AIF2TX3" पूर्ण,
	अणु "AIF2 Capture", शून्य, "AIF2TX4" पूर्ण,
	अणु "AIF2 Capture", शून्य, "AIF2TX5" पूर्ण,
	अणु "AIF2 Capture", शून्य, "AIF2TX6" पूर्ण,
	अणु "AIF2 Capture", शून्य, "AIF2TX7" पूर्ण,
	अणु "AIF2 Capture", शून्य, "AIF2TX8" पूर्ण,

	अणु "AIF2RX1", शून्य, "AIF2 Playback" पूर्ण,
	अणु "AIF2RX2", शून्य, "AIF2 Playback" पूर्ण,
	अणु "AIF2RX3", शून्य, "AIF2 Playback" पूर्ण,
	अणु "AIF2RX4", शून्य, "AIF2 Playback" पूर्ण,
	अणु "AIF2RX5", शून्य, "AIF2 Playback" पूर्ण,
	अणु "AIF2RX6", शून्य, "AIF2 Playback" पूर्ण,
	अणु "AIF2RX7", शून्य, "AIF2 Playback" पूर्ण,
	अणु "AIF2RX8", शून्य, "AIF2 Playback" पूर्ण,

	अणु "AIF3 Capture", शून्य, "AIF3TX1" पूर्ण,
	अणु "AIF3 Capture", शून्य, "AIF3TX2" पूर्ण,
	अणु "AIF3 Capture", शून्य, "AIF3TX3" पूर्ण,
	अणु "AIF3 Capture", शून्य, "AIF3TX4" पूर्ण,

	अणु "AIF3RX1", शून्य, "AIF3 Playback" पूर्ण,
	अणु "AIF3RX2", शून्य, "AIF3 Playback" पूर्ण,
	अणु "AIF3RX3", शून्य, "AIF3 Playback" पूर्ण,
	अणु "AIF3RX4", शून्य, "AIF3 Playback" पूर्ण,

	अणु "Slim1 Capture", शून्य, "SLIMTX1" पूर्ण,
	अणु "Slim1 Capture", शून्य, "SLIMTX2" पूर्ण,
	अणु "Slim1 Capture", शून्य, "SLIMTX3" पूर्ण,
	अणु "Slim1 Capture", शून्य, "SLIMTX4" पूर्ण,

	अणु "SLIMRX1", शून्य, "Slim1 Playback" पूर्ण,
	अणु "SLIMRX2", शून्य, "Slim1 Playback" पूर्ण,
	अणु "SLIMRX3", शून्य, "Slim1 Playback" पूर्ण,
	अणु "SLIMRX4", शून्य, "Slim1 Playback" पूर्ण,

	अणु "Slim2 Capture", शून्य, "SLIMTX5" पूर्ण,
	अणु "Slim2 Capture", शून्य, "SLIMTX6" पूर्ण,

	अणु "SLIMRX5", शून्य, "Slim2 Playback" पूर्ण,
	अणु "SLIMRX6", शून्य, "Slim2 Playback" पूर्ण,

	अणु "Slim3 Capture", शून्य, "SLIMTX7" पूर्ण,
	अणु "Slim3 Capture", शून्य, "SLIMTX8" पूर्ण,

	अणु "SLIMRX7", शून्य, "Slim3 Playback" पूर्ण,
	अणु "SLIMRX8", शून्य, "Slim3 Playback" पूर्ण,

	अणु "AIF1 Playback", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF2 Playback", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF3 Playback", शून्य, "SYSCLK" पूर्ण,
	अणु "Slim1 Playback", शून्य, "SYSCLK" पूर्ण,
	अणु "Slim2 Playback", शून्य, "SYSCLK" पूर्ण,
	अणु "Slim3 Playback", शून्य, "SYSCLK" पूर्ण,

	अणु "AIF1 Capture", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF2 Capture", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF3 Capture", शून्य, "SYSCLK" पूर्ण,
	अणु "Slim1 Capture", शून्य, "SYSCLK" पूर्ण,
	अणु "Slim2 Capture", शून्य, "SYSCLK" पूर्ण,
	अणु "Slim3 Capture", शून्य, "SYSCLK" पूर्ण,

	अणु "Audio Trace DSP", शून्य, "DSP1" पूर्ण,

	अणु "IN1L Analog Mux", "A", "IN1ALN" पूर्ण,
	अणु "IN1L Analog Mux", "A", "IN1ALP" पूर्ण,
	अणु "IN1L Analog Mux", "B", "IN1BLN" पूर्ण,
	अणु "IN1L Analog Mux", "B", "IN1BLP" पूर्ण,
	अणु "IN1R Analog Mux", "A", "IN1ARN" पूर्ण,
	अणु "IN1R Analog Mux", "A", "IN1ARP" पूर्ण,
	अणु "IN1R Analog Mux", "B", "IN1BR" पूर्ण,
	अणु "IN1R Analog Mux", "B", "IN1ALN" पूर्ण,

	अणु "IN1L Mode", "Analog", "IN1L Analog Mux" पूर्ण,
	अणु "IN1R Mode", "Analog", "IN1R Analog Mux" पूर्ण,

	अणु "IN1L Mode", "Digital", "IN1ALN" पूर्ण,
	अणु "IN1L Mode", "Digital", "IN1ALP" पूर्ण,
	अणु "IN1R Mode", "Digital", "IN1ALN" पूर्ण,
	अणु "IN1R Mode", "Digital", "IN1ALP" पूर्ण,

	अणु "IN1L", शून्य, "IN1L Mode" पूर्ण,
	अणु "IN1R", शून्य, "IN1R Mode" पूर्ण,

	अणु "IN2L Analog Mux", "A", "IN2ALN" पूर्ण,
	अणु "IN2L Analog Mux", "A", "IN2ALP" पूर्ण,
	अणु "IN2L Analog Mux", "B", "IN2ALN" पूर्ण,
	अणु "IN2L Analog Mux", "B", "IN2BL" पूर्ण,
	अणु "IN2R Analog Mux", "A", "IN2ARN" पूर्ण,
	अणु "IN2R Analog Mux", "A", "IN2ARP" पूर्ण,
	अणु "IN2R Analog Mux", "B", "IN2ARN" पूर्ण,
	अणु "IN2R Analog Mux", "B", "IN2BR" पूर्ण,

	अणु "IN2L Mode", "Analog", "IN2L Analog Mux" पूर्ण,
	अणु "IN2R Mode", "Analog", "IN2R Analog Mux" पूर्ण,

	अणु "IN2L Mode", "Digital", "IN2ALN" पूर्ण,
	अणु "IN2L Mode", "Digital", "IN2ALP" पूर्ण,
	अणु "IN2R Mode", "Digital", "IN2ALN" पूर्ण,
	अणु "IN2R Mode", "Digital", "IN2ALP" पूर्ण,

	अणु "IN2L", शून्य, "IN2L Mode" पूर्ण,
	अणु "IN2R", शून्य, "IN2R Mode" पूर्ण,

	अणु "IN3L", शून्य, "IN1ARN" पूर्ण,
	अणु "IN3L", शून्य, "IN1ARP" पूर्ण,
	अणु "IN3R", शून्य, "IN1ARN" पूर्ण,
	अणु "IN3R", शून्य, "IN1ARP" पूर्ण,

	अणु "IN4L", शून्य, "IN2ARN" पूर्ण,
	अणु "IN4L", शून्य, "IN2ARP" पूर्ण,
	अणु "IN4R", शून्य, "IN2ARN" पूर्ण,
	अणु "IN4R", शून्य, "IN2ARP" पूर्ण,

	MADERA_MIXER_ROUTES("OUT1L", "HPOUT1L"),
	MADERA_MIXER_ROUTES("OUT1R", "HPOUT1R"),
	MADERA_MIXER_ROUTES("OUT2L", "HPOUT2L"),
	MADERA_MIXER_ROUTES("OUT2R", "HPOUT2R"),
	MADERA_MIXER_ROUTES("OUT3L", "HPOUT3L"),
	MADERA_MIXER_ROUTES("OUT3R", "HPOUT3R"),

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
	MADERA_MIXER_ROUTES("AIF1TX7", "AIF1TX7"),
	MADERA_MIXER_ROUTES("AIF1TX8", "AIF1TX8"),

	MADERA_MIXER_ROUTES("AIF2TX1", "AIF2TX1"),
	MADERA_MIXER_ROUTES("AIF2TX2", "AIF2TX2"),
	MADERA_MIXER_ROUTES("AIF2TX3", "AIF2TX3"),
	MADERA_MIXER_ROUTES("AIF2TX4", "AIF2TX4"),
	MADERA_MIXER_ROUTES("AIF2TX5", "AIF2TX5"),
	MADERA_MIXER_ROUTES("AIF2TX6", "AIF2TX6"),
	MADERA_MIXER_ROUTES("AIF2TX7", "AIF2TX7"),
	MADERA_MIXER_ROUTES("AIF2TX8", "AIF2TX8"),

	MADERA_MIXER_ROUTES("AIF3TX1", "AIF3TX1"),
	MADERA_MIXER_ROUTES("AIF3TX2", "AIF3TX2"),
	MADERA_MIXER_ROUTES("AIF3TX3", "AIF3TX3"),
	MADERA_MIXER_ROUTES("AIF3TX4", "AIF3TX4"),

	MADERA_MIXER_ROUTES("SLIMTX1", "SLIMTX1"),
	MADERA_MIXER_ROUTES("SLIMTX2", "SLIMTX2"),
	MADERA_MIXER_ROUTES("SLIMTX3", "SLIMTX3"),
	MADERA_MIXER_ROUTES("SLIMTX4", "SLIMTX4"),
	MADERA_MIXER_ROUTES("SLIMTX5", "SLIMTX5"),
	MADERA_MIXER_ROUTES("SLIMTX6", "SLIMTX6"),
	MADERA_MIXER_ROUTES("SLIMTX7", "SLIMTX7"),
	MADERA_MIXER_ROUTES("SLIMTX8", "SLIMTX8"),

	MADERA_MUX_ROUTES("SPD1TX1", "SPDIFTX1"),
	MADERA_MUX_ROUTES("SPD1TX2", "SPDIFTX2"),

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

	MADERA_MUX_ROUTES("ASRC1IN1L", "ASRC1IN1L"),
	MADERA_MUX_ROUTES("ASRC1IN1R", "ASRC1IN1R"),
	MADERA_MUX_ROUTES("ASRC1IN2L", "ASRC1IN2L"),
	MADERA_MUX_ROUTES("ASRC1IN2R", "ASRC1IN2R"),

	MADERA_DSP_ROUTES("DSP1"),

	MADERA_MUX_ROUTES("ISRC1INT1", "ISRC1INT1"),
	MADERA_MUX_ROUTES("ISRC1INT2", "ISRC1INT2"),

	MADERA_MUX_ROUTES("ISRC1DEC1", "ISRC1DEC1"),
	MADERA_MUX_ROUTES("ISRC1DEC2", "ISRC1DEC2"),

	MADERA_MUX_ROUTES("ISRC2INT1", "ISRC2INT1"),
	MADERA_MUX_ROUTES("ISRC2INT2", "ISRC2INT2"),

	MADERA_MUX_ROUTES("ISRC2DEC1", "ISRC2DEC1"),
	MADERA_MUX_ROUTES("ISRC2DEC2", "ISRC2DEC2"),

	अणु "AEC1 Loopback", "HPOUT1L", "OUT1L" पूर्ण,
	अणु "AEC1 Loopback", "HPOUT1R", "OUT1R" पूर्ण,
	अणु "HPOUT1L", शून्य, "OUT1L" पूर्ण,
	अणु "HPOUT1R", शून्य, "OUT1R" पूर्ण,

	अणु "AEC1 Loopback", "HPOUT2L", "OUT2L" पूर्ण,
	अणु "AEC1 Loopback", "HPOUT2R", "OUT2R" पूर्ण,
	अणु "HPOUT2L", शून्य, "OUT2L" पूर्ण,
	अणु "HPOUT2R", शून्य, "OUT2R" पूर्ण,

	अणु "AEC1 Loopback", "HPOUT3L", "OUT3L" पूर्ण,
	अणु "AEC1 Loopback", "HPOUT3R", "OUT3R" पूर्ण,
	अणु "OUT3 Demux", शून्य, "OUT3L" पूर्ण,
	अणु "OUT3 Demux", शून्य, "OUT3R" पूर्ण,

	अणु "OUT3R", शून्य, "OUT3 Mono Mux" पूर्ण,

	अणु "HPOUT3L", "HPOUT3", "OUT3 Demux" पूर्ण,
	अणु "HPOUT3R", "HPOUT3", "OUT3 Demux" पूर्ण,
	अणु "HPOUT4L", "HPOUT4", "OUT3 Demux" पूर्ण,
	अणु "HPOUT4R", "HPOUT4", "OUT3 Demux" पूर्ण,

	अणु "AEC1 Loopback", "SPKDAT1L", "OUT5L" पूर्ण,
	अणु "AEC1 Loopback", "SPKDAT1R", "OUT5R" पूर्ण,
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

	MADERA_MUX_ROUTES("DFC1", "DFC1"),
	MADERA_MUX_ROUTES("DFC2", "DFC2"),
	MADERA_MUX_ROUTES("DFC3", "DFC3"),
	MADERA_MUX_ROUTES("DFC4", "DFC4"),
	MADERA_MUX_ROUTES("DFC5", "DFC5"),
	MADERA_MUX_ROUTES("DFC6", "DFC6"),
	MADERA_MUX_ROUTES("DFC7", "DFC7"),
	MADERA_MUX_ROUTES("DFC8", "DFC8"),
पूर्ण;

अटल पूर्णांक cs47l92_set_fll(काष्ठा snd_soc_component *component, पूर्णांक fll_id,
			   पूर्णांक source, अचिन्हित पूर्णांक fref, अचिन्हित पूर्णांक fout)
अणु
	काष्ठा cs47l92 *cs47l92 = snd_soc_component_get_drvdata(component);

	चयन (fll_id) अणु
	हाल MADERA_FLL1_REFCLK:
		वापस madera_fllhj_set_refclk(&cs47l92->fll[0], source, fref,
					       fout);
	हाल MADERA_FLL2_REFCLK:
		वापस madera_fllhj_set_refclk(&cs47l92->fll[1], source, fref,
					       fout);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल काष्ठा snd_soc_dai_driver cs47l92_dai[] = अणु
	अणु
		.name = "cs47l92-aif1",
		.id = 1,
		.base = MADERA_AIF1_BCLK_CTRL,
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 8,
			.rates = MADERA_RATES,
			.क्रमmats = MADERA_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 1,
			.channels_max = 8,
			.rates = MADERA_RATES,
			.क्रमmats = MADERA_FORMATS,
		 पूर्ण,
		.ops = &madera_dai_ops,
		.symmetric_rate = 1,
		.symmetric_sample_bits = 1,
	पूर्ण,
	अणु
		.name = "cs47l92-aif2",
		.id = 2,
		.base = MADERA_AIF2_BCLK_CTRL,
		.playback = अणु
			.stream_name = "AIF2 Playback",
			.channels_min = 1,
			.channels_max = 8,
			.rates = MADERA_RATES,
			.क्रमmats = MADERA_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF2 Capture",
			.channels_min = 1,
			.channels_max = 8,
			.rates = MADERA_RATES,
			.क्रमmats = MADERA_FORMATS,
		 पूर्ण,
		.ops = &madera_dai_ops,
		.symmetric_rate = 1,
		.symmetric_sample_bits = 1,
	पूर्ण,
	अणु
		.name = "cs47l92-aif3",
		.id = 3,
		.base = MADERA_AIF3_BCLK_CTRL,
		.playback = अणु
			.stream_name = "AIF3 Playback",
			.channels_min = 1,
			.channels_max = 4,
			.rates = MADERA_RATES,
			.क्रमmats = MADERA_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF3 Capture",
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
		.name = "cs47l92-slim1",
		.id = 5,
		.playback = अणु
			.stream_name = "Slim1 Playback",
			.channels_min = 1,
			.channels_max = 4,
			.rates = MADERA_RATES,
			.क्रमmats = MADERA_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "Slim1 Capture",
			.channels_min = 1,
			.channels_max = 4,
			.rates = MADERA_RATES,
			.क्रमmats = MADERA_FORMATS,
		 पूर्ण,
		.ops = &madera_simple_dai_ops,
	पूर्ण,
	अणु
		.name = "cs47l92-slim2",
		.id = 6,
		.playback = अणु
			.stream_name = "Slim2 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MADERA_RATES,
			.क्रमmats = MADERA_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "Slim2 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MADERA_RATES,
			.क्रमmats = MADERA_FORMATS,
		 पूर्ण,
		.ops = &madera_simple_dai_ops,
	पूर्ण,
	अणु
		.name = "cs47l92-slim3",
		.id = 7,
		.playback = अणु
			.stream_name = "Slim3 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MADERA_RATES,
			.क्रमmats = MADERA_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "Slim3 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MADERA_RATES,
			.क्रमmats = MADERA_FORMATS,
		 पूर्ण,
		.ops = &madera_simple_dai_ops,
	पूर्ण,
	अणु
		.name = "cs47l92-cpu-trace",
		.capture = अणु
			.stream_name = "Audio Trace CPU",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MADERA_RATES,
			.क्रमmats = MADERA_FORMATS,
		पूर्ण,
		.compress_new = snd_soc_new_compress,
	पूर्ण,
	अणु
		.name = "cs47l92-dsp-trace",
		.capture = अणु
			.stream_name = "Audio Trace DSP",
			.channels_min = 1,
			.channels_max = 2,
			.rates = MADERA_RATES,
			.क्रमmats = MADERA_FORMATS,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक cs47l92_खोलो(काष्ठा snd_soc_component *component,
			काष्ठा snd_compr_stream *stream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = stream->निजी_data;
	काष्ठा cs47l92 *cs47l92 = snd_soc_component_get_drvdata(component);
	काष्ठा madera_priv *priv = &cs47l92->core;
	काष्ठा madera *madera = priv->madera;
	पूर्णांक n_adsp;

	अगर (म_भेद(asoc_rtd_to_codec(rtd, 0)->name, "cs47l92-dsp-trace") == 0) अणु
		n_adsp = 0;
	पूर्ण अन्यथा अणु
		dev_err(madera->dev,
			"No suitable compressed stream for DAI '%s'\n",
			asoc_rtd_to_codec(rtd, 0)->name);
		वापस -EINVAL;
	पूर्ण

	वापस wm_adsp_compr_खोलो(&priv->adsp[n_adsp], stream);
पूर्ण

अटल irqवापस_t cs47l92_adsp2_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cs47l92 *cs47l92 = data;
	काष्ठा madera_priv *priv = &cs47l92->core;
	काष्ठा madera *madera = priv->madera;
	पूर्णांक ret;

	ret = wm_adsp_compr_handle_irq(&priv->adsp[0]);
	अगर (ret == -ENODEV) अणु
		dev_err(madera->dev, "Spurious compressed data IRQ\n");
		वापस IRQ_NONE;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_route cs47l92_mono_routes[] = अणु
	अणु "OUT1R", शून्य, "OUT1L" पूर्ण,
	अणु "OUT2R", शून्य, "OUT2L" पूर्ण,
	अणु "OUT3 Mono Mux", "HPOUT3", "OUT3L" पूर्ण,
	अणु "OUT3 Mono Mux", "HPOUT4", "OUT3L" पूर्ण,
पूर्ण;

अटल पूर्णांक cs47l92_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs47l92 *cs47l92 = snd_soc_component_get_drvdata(component);
	काष्ठा madera *madera = cs47l92->core.madera;
	पूर्णांक ret;

	snd_soc_component_init_regmap(component, madera->regmap);

	mutex_lock(&madera->dapm_ptr_lock);
	madera->dapm = snd_soc_component_get_dapm(component);
	mutex_unlock(&madera->dapm_ptr_lock);

	ret = madera_init_inमाला_दो(component);
	अगर (ret)
		वापस ret;

	ret = madera_init_outमाला_दो(component, cs47l92_mono_routes,
				  ARRAY_SIZE(cs47l92_mono_routes),
				  CS47L92_MONO_OUTPUTS);
	अगर (ret)
		वापस ret;

	snd_soc_component_disable_pin(component, "HAPTICS");

	ret = snd_soc_add_component_controls(component,
					     madera_adsp_rate_controls,
					     CS47L92_NUM_ADSP);
	अगर (ret)
		वापस ret;

	वापस wm_adsp2_component_probe(&cs47l92->core.adsp[0], component);
पूर्ण

अटल व्योम cs47l92_component_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs47l92 *cs47l92 = snd_soc_component_get_drvdata(component);
	काष्ठा madera *madera = cs47l92->core.madera;

	mutex_lock(&madera->dapm_ptr_lock);
	madera->dapm = शून्य;
	mutex_unlock(&madera->dapm_ptr_lock);

	wm_adsp2_component_हटाओ(&cs47l92->core.adsp[0], component);
पूर्ण

#घोषणा CS47L92_DIG_VU 0x0200

अटल अचिन्हित पूर्णांक cs47l92_digital_vu[] = अणु
	MADERA_DAC_DIGITAL_VOLUME_1L,
	MADERA_DAC_DIGITAL_VOLUME_1R,
	MADERA_DAC_DIGITAL_VOLUME_2L,
	MADERA_DAC_DIGITAL_VOLUME_2R,
	MADERA_DAC_DIGITAL_VOLUME_3L,
	MADERA_DAC_DIGITAL_VOLUME_3R,
	MADERA_DAC_DIGITAL_VOLUME_5L,
	MADERA_DAC_DIGITAL_VOLUME_5R,
पूर्ण;

अटल स्थिर काष्ठा snd_compress_ops cs47l92_compress_ops = अणु
	.खोलो = &cs47l92_खोलो,
	.मुक्त = &wm_adsp_compr_मुक्त,
	.set_params = &wm_adsp_compr_set_params,
	.get_caps = &wm_adsp_compr_get_caps,
	.trigger = &wm_adsp_compr_trigger,
	.poपूर्णांकer = &wm_adsp_compr_poपूर्णांकer,
	.copy = &wm_adsp_compr_copy,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_cs47l92 = अणु
	.probe			= &cs47l92_component_probe,
	.हटाओ			= &cs47l92_component_हटाओ,
	.set_sysclk		= &madera_set_sysclk,
	.set_pll		= &cs47l92_set_fll,
	.name			= DRV_NAME,
	.compress_ops		= &cs47l92_compress_ops,
	.controls		= cs47l92_snd_controls,
	.num_controls		= ARRAY_SIZE(cs47l92_snd_controls),
	.dapm_widमाला_लो		= cs47l92_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(cs47l92_dapm_widमाला_लो),
	.dapm_routes		= cs47l92_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(cs47l92_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक cs47l92_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा madera *madera = dev_get_drvdata(pdev->dev.parent);
	काष्ठा cs47l92 *cs47l92;
	पूर्णांक i, ret;

	BUILD_BUG_ON(ARRAY_SIZE(cs47l92_dai) > MADERA_MAX_DAI);

	/* quick निकास अगर Madera irqchip driver hasn't completed probe */
	अगर (!madera->irq_dev) अणु
		dev_dbg(&pdev->dev, "irqchip driver not ready\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	cs47l92 = devm_kzalloc(&pdev->dev, माप(काष्ठा cs47l92), GFP_KERNEL);
	अगर (!cs47l92)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, cs47l92);

	cs47l92->core.madera = madera;
	cs47l92->core.dev = &pdev->dev;
	cs47l92->core.num_inमाला_दो = 8;

	ret = madera_core_init(&cs47l92->core);
	अगर (ret)
		वापस ret;

	ret = madera_request_irq(madera, MADERA_IRQ_DSP_IRQ1,
				 "ADSP2 Compressed IRQ", cs47l92_adsp2_irq,
				 cs47l92);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Failed to request DSP IRQ: %d\n", ret);
		जाओ error_core;
	पूर्ण

	ret = madera_set_irq_wake(madera, MADERA_IRQ_DSP_IRQ1, 1);
	अगर (ret)
		dev_warn(&pdev->dev, "Failed to set DSP IRQ wake: %d\n", ret);

	cs47l92->core.adsp[0].part = "cs47l92";
	cs47l92->core.adsp[0].num = 1;
	cs47l92->core.adsp[0].type = WMFW_ADSP2;
	cs47l92->core.adsp[0].rev = 2;
	cs47l92->core.adsp[0].dev = madera->dev;
	cs47l92->core.adsp[0].regmap = madera->regmap_32bit;

	cs47l92->core.adsp[0].base = MADERA_DSP1_CONFIG_1;
	cs47l92->core.adsp[0].mem = cs47l92_dsp1_regions;
	cs47l92->core.adsp[0].num_mems = ARRAY_SIZE(cs47l92_dsp1_regions);

	cs47l92->core.adsp[0].lock_regions = WM_ADSP2_REGION_1_9;

	ret = wm_adsp2_init(&cs47l92->core.adsp[0]);
	अगर (ret != 0)
		जाओ error_dsp_irq;

	ret = madera_init_bus_error_irq(&cs47l92->core, 0, wm_adsp2_bus_error);
	अगर (ret != 0)
		जाओ error_adsp;

	madera_init_fll(madera, 1, MADERA_FLL1_CONTROL_1 - 1,
			&cs47l92->fll[0]);
	madera_init_fll(madera, 2, MADERA_FLL2_CONTROL_1 - 1,
			&cs47l92->fll[1]);

	क्रम (i = 0; i < ARRAY_SIZE(cs47l92_dai); i++)
		madera_init_dai(&cs47l92->core, i);

	/* Latch volume update bits */
	क्रम (i = 0; i < ARRAY_SIZE(cs47l92_digital_vu); i++)
		regmap_update_bits(madera->regmap, cs47l92_digital_vu[i],
				   CS47L92_DIG_VU, CS47L92_DIG_VU);

	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_idle(&pdev->dev);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &soc_component_dev_cs47l92,
					      cs47l92_dai,
					      ARRAY_SIZE(cs47l92_dai));
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to register component: %d\n", ret);
		जाओ error_pm_runसमय;
	पूर्ण

	वापस ret;

error_pm_runसमय:
	pm_runसमय_disable(&pdev->dev);
	madera_मुक्त_bus_error_irq(&cs47l92->core, 0);
error_adsp:
	wm_adsp2_हटाओ(&cs47l92->core.adsp[0]);
error_dsp_irq:
	madera_set_irq_wake(madera, MADERA_IRQ_DSP_IRQ1, 0);
	madera_मुक्त_irq(madera, MADERA_IRQ_DSP_IRQ1, cs47l92);
error_core:
	madera_core_मुक्त(&cs47l92->core);

	वापस ret;
पूर्ण

अटल पूर्णांक cs47l92_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cs47l92 *cs47l92 = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);

	madera_मुक्त_bus_error_irq(&cs47l92->core, 0);
	wm_adsp2_हटाओ(&cs47l92->core.adsp[0]);

	madera_set_irq_wake(cs47l92->core.madera, MADERA_IRQ_DSP_IRQ1, 0);
	madera_मुक्त_irq(cs47l92->core.madera, MADERA_IRQ_DSP_IRQ1, cs47l92);

	madera_core_मुक्त(&cs47l92->core);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cs47l92_codec_driver = अणु
	.driver = अणु
		.name = "cs47l92-codec",
	पूर्ण,
	.probe = &cs47l92_probe,
	.हटाओ = &cs47l92_हटाओ,
पूर्ण;

module_platक्रमm_driver(cs47l92_codec_driver);

MODULE_SOFTDEP("pre: madera irq-madera arizona-micsupp");
MODULE_DESCRIPTION("ASoC CS47L92 driver");
MODULE_AUTHOR("Stuart Henderson <stuarth@opensource.cirrus.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:cs47l92-codec");
