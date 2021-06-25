<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* ALSA SoC TLV320AIC3X codec driver
 *
 * Author:      Vladimir Barinov, <vbarinov@embeddedalley.com>
 * Copyright:   (C) 2007 MontaVista Software, Inc., <source@mvista.com>
 *
 * Based on sound/soc/codecs/wm8753.c by Liam Girdwood
 *
 * Notes:
 *  The AIC3X is a driver क्रम a low घातer stereo audio
 *  codecs aic31, aic32, aic33, aic3007.
 *
 *  It supports full aic33 codec functionality.
 *  The compatibility with aic32, aic31 and aic3007 is as follows:
 *    aic32/aic3007    |        aic31
 *  ---------------------------------------
 *   MONO_LOUT -> N/A  |  MONO_LOUT -> N/A
 *                     |  IN1L -> LINE1L
 *                     |  IN1R -> LINE1R
 *                     |  IN2L -> LINE2L
 *                     |  IN2R -> LINE2R
 *                     |  MIC3L/R -> N/A
 *   truncated पूर्णांकernal functionality in
 *   accordance with करोcumentation
 *  ---------------------------------------
 *
 *  Hence the machine layer should disable unsupported inमाला_दो/outमाला_दो by
 *  snd_soc_dapm_disable_pin(codec, "MONO_LOUT"), etc.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/tlv320aic3x.h>

#समावेश "tlv320aic3x.h"

#घोषणा AIC3X_NUM_SUPPLIES	4
अटल स्थिर अक्षर *aic3x_supply_names[AIC3X_NUM_SUPPLIES] = अणु
	"IOVDD",	/* I/O Voltage */
	"DVDD",		/* Digital Core Voltage */
	"AVDD",		/* Analog DAC Voltage */
	"DRVDD",	/* ADC Analog and Output Driver Voltage */
पूर्ण;

अटल LIST_HEAD(reset_list);

काष्ठा aic3x_priv;

काष्ठा aic3x_disable_nb अणु
	काष्ठा notअगरier_block nb;
	काष्ठा aic3x_priv *aic3x;
पूर्ण;

/* codec निजी data */
काष्ठा aic3x_priv अणु
	काष्ठा snd_soc_component *component;
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data supplies[AIC3X_NUM_SUPPLIES];
	काष्ठा aic3x_disable_nb disable_nb[AIC3X_NUM_SUPPLIES];
	काष्ठा aic3x_setup_data *setup;
	अचिन्हित पूर्णांक sysclk;
	अचिन्हित पूर्णांक dai_fmt;
	अचिन्हित पूर्णांक tdm_delay;
	अचिन्हित पूर्णांक slot_width;
	काष्ठा list_head list;
	पूर्णांक master;
	पूर्णांक gpio_reset;
	पूर्णांक घातer;
	u16 model;

	/* Selects the micbias voltage */
	क्रमागत aic3x_micbias_voltage micbias_vg;
	/* Output Common-Mode Voltage */
	u8 ocmv;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष aic3x_reg[] = अणु
	अणु   0, 0x00 पूर्ण, अणु   1, 0x00 पूर्ण, अणु   2, 0x00 पूर्ण, अणु   3, 0x10 पूर्ण,
	अणु   4, 0x04 पूर्ण, अणु   5, 0x00 पूर्ण, अणु   6, 0x00 पूर्ण, अणु   7, 0x00 पूर्ण,
	अणु   8, 0x00 पूर्ण, अणु   9, 0x00 पूर्ण, अणु  10, 0x00 पूर्ण, अणु  11, 0x01 पूर्ण,
	अणु  12, 0x00 पूर्ण, अणु  13, 0x00 पूर्ण, अणु  14, 0x00 पूर्ण, अणु  15, 0x80 पूर्ण,
	अणु  16, 0x80 पूर्ण, अणु  17, 0xff पूर्ण, अणु  18, 0xff पूर्ण, अणु  19, 0x78 पूर्ण,
	अणु  20, 0x78 पूर्ण, अणु  21, 0x78 पूर्ण, अणु  22, 0x78 पूर्ण, अणु  23, 0x78 पूर्ण,
	अणु  24, 0x78 पूर्ण, अणु  25, 0x00 पूर्ण, अणु  26, 0x00 पूर्ण, अणु  27, 0xfe पूर्ण,
	अणु  28, 0x00 पूर्ण, अणु  29, 0x00 पूर्ण, अणु  30, 0xfe पूर्ण, अणु  31, 0x00 पूर्ण,
	अणु  32, 0x18 पूर्ण, अणु  33, 0x18 पूर्ण, अणु  34, 0x00 पूर्ण, अणु  35, 0x00 पूर्ण,
	अणु  36, 0x00 पूर्ण, अणु  37, 0x00 पूर्ण, अणु  38, 0x00 पूर्ण, अणु  39, 0x00 पूर्ण,
	अणु  40, 0x00 पूर्ण, अणु  41, 0x00 पूर्ण, अणु  42, 0x00 पूर्ण, अणु  43, 0x80 पूर्ण,
	अणु  44, 0x80 पूर्ण, अणु  45, 0x00 पूर्ण, अणु  46, 0x00 पूर्ण, अणु  47, 0x00 पूर्ण,
	अणु  48, 0x00 पूर्ण, अणु  49, 0x00 पूर्ण, अणु  50, 0x00 पूर्ण, अणु  51, 0x04 पूर्ण,
	अणु  52, 0x00 पूर्ण, अणु  53, 0x00 पूर्ण, अणु  54, 0x00 पूर्ण, अणु  55, 0x00 पूर्ण,
	अणु  56, 0x00 पूर्ण, अणु  57, 0x00 पूर्ण, अणु  58, 0x04 पूर्ण, अणु  59, 0x00 पूर्ण,
	अणु  60, 0x00 पूर्ण, अणु  61, 0x00 पूर्ण, अणु  62, 0x00 पूर्ण, अणु  63, 0x00 पूर्ण,
	अणु  64, 0x00 पूर्ण, अणु  65, 0x04 पूर्ण, अणु  66, 0x00 पूर्ण, अणु  67, 0x00 पूर्ण,
	अणु  68, 0x00 पूर्ण, अणु  69, 0x00 पूर्ण, अणु  70, 0x00 पूर्ण, अणु  71, 0x00 पूर्ण,
	अणु  72, 0x04 पूर्ण, अणु  73, 0x00 पूर्ण, अणु  74, 0x00 पूर्ण, अणु  75, 0x00 पूर्ण,
	अणु  76, 0x00 पूर्ण, अणु  77, 0x00 पूर्ण, अणु  78, 0x00 पूर्ण, अणु  79, 0x00 पूर्ण,
	अणु  80, 0x00 पूर्ण, अणु  81, 0x00 पूर्ण, अणु  82, 0x00 पूर्ण, अणु  83, 0x00 पूर्ण,
	अणु  84, 0x00 पूर्ण, अणु  85, 0x00 पूर्ण, अणु  86, 0x00 पूर्ण, अणु  87, 0x00 पूर्ण,
	अणु  88, 0x00 पूर्ण, अणु  89, 0x00 पूर्ण, अणु  90, 0x00 पूर्ण, अणु  91, 0x00 पूर्ण,
	अणु  92, 0x00 पूर्ण, अणु  93, 0x00 पूर्ण, अणु  94, 0x00 पूर्ण, अणु  95, 0x00 पूर्ण,
	अणु  96, 0x00 पूर्ण, अणु  97, 0x00 पूर्ण, अणु  98, 0x00 पूर्ण, अणु  99, 0x00 पूर्ण,
	अणु 100, 0x00 पूर्ण, अणु 101, 0x00 पूर्ण, अणु 102, 0x02 पूर्ण, अणु 103, 0x00 पूर्ण,
	अणु 104, 0x00 पूर्ण, अणु 105, 0x00 पूर्ण, अणु 106, 0x00 पूर्ण, अणु 107, 0x00 पूर्ण,
	अणु 108, 0x00 पूर्ण, अणु 109, 0x00 पूर्ण,
पूर्ण;

अटल bool aic3x_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AIC3X_RESET:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

स्थिर काष्ठा regmap_config aic3x_regmap = अणु
	.max_रेजिस्टर = DAC_ICC_ADJ,
	.reg_शेषs = aic3x_reg,
	.num_reg_शेषs = ARRAY_SIZE(aic3x_reg),

	.अस्थिर_reg = aic3x_अस्थिर_reg,

	.cache_type = REGCACHE_RBTREE,
पूर्ण;
EXPORT_SYMBOL_GPL(aic3x_regmap);

#घोषणा SOC_DAPM_SINGLE_AIC3X(xname, reg, shअगरt, mask, invert) \
	SOC_SINGLE_EXT(xname, reg, shअगरt, mask, invert, \
		snd_soc_dapm_get_volsw, snd_soc_dapm_put_volsw_aic3x)

/*
 * All input lines are connected when !0xf and disconnected with 0xf bit field,
 * so we have to use specअगरic dapm_put call क्रम input mixer
 */
अटल पूर्णांक snd_soc_dapm_put_volsw_aic3x(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg = mc->reg;
	अचिन्हित पूर्णांक shअगरt = mc->shअगरt;
	पूर्णांक max = mc->max;
	अचिन्हित पूर्णांक mask = (1 << fls(max)) - 1;
	अचिन्हित पूर्णांक invert = mc->invert;
	अचिन्हित लघु val;
	काष्ठा snd_soc_dapm_update update = अणुपूर्ण;
	पूर्णांक connect, change;

	val = (ucontrol->value.पूर्णांकeger.value[0] & mask);

	mask = 0xf;
	अगर (val)
		val = mask;

	connect = !!val;

	अगर (invert)
		val = mask - val;

	mask <<= shअगरt;
	val <<= shअगरt;

	change = snd_soc_component_test_bits(component, reg, mask, val);
	अगर (change) अणु
		update.kcontrol = kcontrol;
		update.reg = reg;
		update.mask = mask;
		update.val = val;

		snd_soc_dapm_mixer_update_घातer(dapm, kcontrol, connect,
			&update);
	पूर्ण

	वापस change;
पूर्ण

/*
 * mic bias घातer on/off share the same रेजिस्टर bits with
 * output voltage of mic bias. when घातer on mic bias, we
 * need reclaim it to voltage value.
 * 0x0 = Powered off
 * 0x1 = MICBIAS output is घातered to 2.0V,
 * 0x2 = MICBIAS output is घातered to 2.5V
 * 0x3 = MICBIAS output is connected to AVDD
 */
अटल पूर्णांक mic_bias_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा aic3x_priv *aic3x = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* change mic bias voltage to user defined */
		snd_soc_component_update_bits(component, MICBIAS_CTRL,
				MICBIAS_LEVEL_MASK,
				aic3x->micbias_vg << MICBIAS_LEVEL_SHIFT);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, MICBIAS_CTRL,
				MICBIAS_LEVEL_MASK, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर aic3x_left_dac_mux[] = अणु
	"DAC_L1", "DAC_L3", "DAC_L2" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(aic3x_left_dac_क्रमागत, DAC_LINE_MUX, 6,
			    aic3x_left_dac_mux);

अटल स्थिर अक्षर * स्थिर aic3x_right_dac_mux[] = अणु
	"DAC_R1", "DAC_R3", "DAC_R2" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(aic3x_right_dac_क्रमागत, DAC_LINE_MUX, 4,
			    aic3x_right_dac_mux);

अटल स्थिर अक्षर * स्थिर aic3x_left_hpcom_mux[] = अणु
	"differential of HPLOUT", "constant VCM", "single-ended" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(aic3x_left_hpcom_क्रमागत, HPLCOM_CFG, 4,
			    aic3x_left_hpcom_mux);

अटल स्थिर अक्षर * स्थिर aic3x_right_hpcom_mux[] = अणु
	"differential of HPROUT", "constant VCM", "single-ended",
	"differential of HPLCOM", "external feedback" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(aic3x_right_hpcom_क्रमागत, HPRCOM_CFG, 3,
			    aic3x_right_hpcom_mux);

अटल स्थिर अक्षर * स्थिर aic3x_linein_mode_mux[] = अणु
	"single-ended", "differential" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(aic3x_line1l_2_l_क्रमागत, LINE1L_2_LADC_CTRL, 7,
			    aic3x_linein_mode_mux);
अटल SOC_ENUM_SINGLE_DECL(aic3x_line1l_2_r_क्रमागत, LINE1L_2_RADC_CTRL, 7,
			    aic3x_linein_mode_mux);
अटल SOC_ENUM_SINGLE_DECL(aic3x_line1r_2_l_क्रमागत, LINE1R_2_LADC_CTRL, 7,
			    aic3x_linein_mode_mux);
अटल SOC_ENUM_SINGLE_DECL(aic3x_line1r_2_r_क्रमागत, LINE1R_2_RADC_CTRL, 7,
			    aic3x_linein_mode_mux);
अटल SOC_ENUM_SINGLE_DECL(aic3x_line2l_2_ldac_क्रमागत, LINE2L_2_LADC_CTRL, 7,
			    aic3x_linein_mode_mux);
अटल SOC_ENUM_SINGLE_DECL(aic3x_line2r_2_rdac_क्रमागत, LINE2R_2_RADC_CTRL, 7,
			    aic3x_linein_mode_mux);

अटल स्थिर अक्षर * स्थिर aic3x_adc_hpf[] = अणु
	"Disabled", "0.0045xFs", "0.0125xFs", "0.025xFs" पूर्ण;
अटल SOC_ENUM_DOUBLE_DECL(aic3x_adc_hpf_क्रमागत, AIC3X_CODEC_DFILT_CTRL, 6, 4,
			    aic3x_adc_hpf);

अटल स्थिर अक्षर * स्थिर aic3x_agc_level[] = अणु
	"-5.5dB", "-8dB", "-10dB", "-12dB",
	"-14dB", "-17dB", "-20dB", "-24dB" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(aic3x_lagc_level_क्रमागत, LAGC_CTRL_A, 4,
			    aic3x_agc_level);
अटल SOC_ENUM_SINGLE_DECL(aic3x_ragc_level_क्रमागत, RAGC_CTRL_A, 4,
			    aic3x_agc_level);

अटल स्थिर अक्षर * स्थिर aic3x_agc_attack[] = अणु
	"8ms", "11ms", "16ms", "20ms" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(aic3x_lagc_attack_क्रमागत, LAGC_CTRL_A, 2,
			    aic3x_agc_attack);
अटल SOC_ENUM_SINGLE_DECL(aic3x_ragc_attack_क्रमागत, RAGC_CTRL_A, 2,
			    aic3x_agc_attack);

अटल स्थिर अक्षर * स्थिर aic3x_agc_decay[] = अणु
	"100ms", "200ms", "400ms", "500ms" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(aic3x_lagc_decay_क्रमागत, LAGC_CTRL_A, 0,
			    aic3x_agc_decay);
अटल SOC_ENUM_SINGLE_DECL(aic3x_ragc_decay_क्रमागत, RAGC_CTRL_A, 0,
			    aic3x_agc_decay);

अटल स्थिर अक्षर * स्थिर aic3x_घातeron_समय[] = अणु
	"0us", "10us", "100us", "1ms", "10ms", "50ms",
	"100ms", "200ms", "400ms", "800ms", "2s", "4s" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(aic3x_घातeron_समय_क्रमागत, HPOUT_POP_REDUCTION, 4,
			    aic3x_घातeron_समय);

अटल स्थिर अक्षर * स्थिर aic3x_rampup_step[] = अणु "0ms", "1ms", "2ms", "4ms" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(aic3x_rampup_step_क्रमागत, HPOUT_POP_REDUCTION, 2,
			    aic3x_rampup_step);

/*
 * DAC digital volumes. From -63.5 to 0 dB in 0.5 dB steps
 */
अटल DECLARE_TLV_DB_SCALE(dac_tlv, -6350, 50, 0);
/* ADC PGA gain volumes. From 0 to 59.5 dB in 0.5 dB steps */
अटल DECLARE_TLV_DB_SCALE(adc_tlv, 0, 50, 0);
/*
 * Output stage volumes. From -78.3 to 0 dB. Muted below -78.3 dB.
 * Step size is approximately 0.5 dB over most of the scale but increasing
 * near the very low levels.
 * Define dB scale so that it is mostly correct क्रम range about -55 to 0 dB
 * but having increasing dB dअगरference below that (and where it करोesn't count
 * so much). This setting shows -50 dB (actual is -50.3 dB) क्रम रेजिस्टर
 * value 100 and -58.5 dB (actual is -78.3 dB) क्रम रेजिस्टर value 117.
 */
अटल DECLARE_TLV_DB_SCALE(output_stage_tlv, -5900, 50, 1);

/* Output volumes. From 0 to 9 dB in 1 dB steps */
अटल स्थिर DECLARE_TLV_DB_SCALE(out_tlv, 0, 100, 0);

अटल स्थिर काष्ठा snd_kcontrol_new aic3x_snd_controls[] = अणु
	/* Output */
	SOC_DOUBLE_R_TLV("PCM Playback Volume",
			 LDAC_VOL, RDAC_VOL, 0, 0x7f, 1, dac_tlv),

	/*
	 * Output controls that map to output mixer चयनes. Note these are
	 * only क्रम swapped L-to-R and R-to-L routes. See below stereo controls
	 * क्रम direct L-to-L and R-to-R routes.
	 */
	SOC_SINGLE_TLV("Left Line Mixer PGAR Bypass Volume",
		       PGAR_2_LLOPM_VOL, 0, 118, 1, output_stage_tlv),
	SOC_SINGLE_TLV("Left Line Mixer DACR1 Playback Volume",
		       DACR1_2_LLOPM_VOL, 0, 118, 1, output_stage_tlv),

	SOC_SINGLE_TLV("Right Line Mixer PGAL Bypass Volume",
		       PGAL_2_RLOPM_VOL, 0, 118, 1, output_stage_tlv),
	SOC_SINGLE_TLV("Right Line Mixer DACL1 Playback Volume",
		       DACL1_2_RLOPM_VOL, 0, 118, 1, output_stage_tlv),

	SOC_SINGLE_TLV("Left HP Mixer PGAR Bypass Volume",
		       PGAR_2_HPLOUT_VOL, 0, 118, 1, output_stage_tlv),
	SOC_SINGLE_TLV("Left HP Mixer DACR1 Playback Volume",
		       DACR1_2_HPLOUT_VOL, 0, 118, 1, output_stage_tlv),

	SOC_SINGLE_TLV("Right HP Mixer PGAL Bypass Volume",
		       PGAL_2_HPROUT_VOL, 0, 118, 1, output_stage_tlv),
	SOC_SINGLE_TLV("Right HP Mixer DACL1 Playback Volume",
		       DACL1_2_HPROUT_VOL, 0, 118, 1, output_stage_tlv),

	SOC_SINGLE_TLV("Left HPCOM Mixer PGAR Bypass Volume",
		       PGAR_2_HPLCOM_VOL, 0, 118, 1, output_stage_tlv),
	SOC_SINGLE_TLV("Left HPCOM Mixer DACR1 Playback Volume",
		       DACR1_2_HPLCOM_VOL, 0, 118, 1, output_stage_tlv),

	SOC_SINGLE_TLV("Right HPCOM Mixer PGAL Bypass Volume",
		       PGAL_2_HPRCOM_VOL, 0, 118, 1, output_stage_tlv),
	SOC_SINGLE_TLV("Right HPCOM Mixer DACL1 Playback Volume",
		       DACL1_2_HPRCOM_VOL, 0, 118, 1, output_stage_tlv),

	/* Stereo output controls क्रम direct L-to-L and R-to-R routes */
	SOC_DOUBLE_R_TLV("Line PGA Bypass Volume",
			 PGAL_2_LLOPM_VOL, PGAR_2_RLOPM_VOL,
			 0, 118, 1, output_stage_tlv),
	SOC_DOUBLE_R_TLV("Line DAC Playback Volume",
			 DACL1_2_LLOPM_VOL, DACR1_2_RLOPM_VOL,
			 0, 118, 1, output_stage_tlv),

	SOC_DOUBLE_R_TLV("HP PGA Bypass Volume",
			 PGAL_2_HPLOUT_VOL, PGAR_2_HPROUT_VOL,
			 0, 118, 1, output_stage_tlv),
	SOC_DOUBLE_R_TLV("HP DAC Playback Volume",
			 DACL1_2_HPLOUT_VOL, DACR1_2_HPROUT_VOL,
			 0, 118, 1, output_stage_tlv),

	SOC_DOUBLE_R_TLV("HPCOM PGA Bypass Volume",
			 PGAL_2_HPLCOM_VOL, PGAR_2_HPRCOM_VOL,
			 0, 118, 1, output_stage_tlv),
	SOC_DOUBLE_R_TLV("HPCOM DAC Playback Volume",
			 DACL1_2_HPLCOM_VOL, DACR1_2_HPRCOM_VOL,
			 0, 118, 1, output_stage_tlv),

	/* Output pin controls */
	SOC_DOUBLE_R_TLV("Line Playback Volume", LLOPM_CTRL, RLOPM_CTRL, 4,
			 9, 0, out_tlv),
	SOC_DOUBLE_R("Line Playback Switch", LLOPM_CTRL, RLOPM_CTRL, 3,
		     0x01, 0),
	SOC_DOUBLE_R_TLV("HP Playback Volume", HPLOUT_CTRL, HPROUT_CTRL, 4,
			 9, 0, out_tlv),
	SOC_DOUBLE_R("HP Playback Switch", HPLOUT_CTRL, HPROUT_CTRL, 3,
		     0x01, 0),
	SOC_DOUBLE_R_TLV("HPCOM Playback Volume", HPLCOM_CTRL, HPRCOM_CTRL,
			 4, 9, 0, out_tlv),
	SOC_DOUBLE_R("HPCOM Playback Switch", HPLCOM_CTRL, HPRCOM_CTRL, 3,
		     0x01, 0),

	/*
	 * Note: enable Automatic input Gain Controller with care. It can
	 * adjust PGA to max value when ADC is on and will never go back.
	*/
	SOC_DOUBLE_R("AGC Switch", LAGC_CTRL_A, RAGC_CTRL_A, 7, 0x01, 0),
	SOC_ENUM("Left AGC Target level", aic3x_lagc_level_क्रमागत),
	SOC_ENUM("Right AGC Target level", aic3x_ragc_level_क्रमागत),
	SOC_ENUM("Left AGC Attack time", aic3x_lagc_attack_क्रमागत),
	SOC_ENUM("Right AGC Attack time", aic3x_ragc_attack_क्रमागत),
	SOC_ENUM("Left AGC Decay time", aic3x_lagc_decay_क्रमागत),
	SOC_ENUM("Right AGC Decay time", aic3x_ragc_decay_क्रमागत),

	/* De-emphasis */
	SOC_DOUBLE("De-emphasis Switch", AIC3X_CODEC_DFILT_CTRL, 2, 0, 0x01, 0),

	/* Input */
	SOC_DOUBLE_R_TLV("PGA Capture Volume", LADC_VOL, RADC_VOL,
			 0, 119, 0, adc_tlv),
	SOC_DOUBLE_R("PGA Capture Switch", LADC_VOL, RADC_VOL, 7, 0x01, 1),

	SOC_ENUM("ADC HPF Cut-off", aic3x_adc_hpf_क्रमागत),

	/* Pop reduction */
	SOC_ENUM("Output Driver Power-On time", aic3x_घातeron_समय_क्रमागत),
	SOC_ENUM("Output Driver Ramp-up step", aic3x_rampup_step_क्रमागत),
पूर्ण;

/* For other than tlv320aic3104 */
अटल स्थिर काष्ठा snd_kcontrol_new aic3x_extra_snd_controls[] = अणु
	/*
	 * Output controls that map to output mixer चयनes. Note these are
	 * only क्रम swapped L-to-R and R-to-L routes. See below stereo controls
	 * क्रम direct L-to-L and R-to-R routes.
	 */
	SOC_SINGLE_TLV("Left Line Mixer Line2R Bypass Volume",
		       LINE2R_2_LLOPM_VOL, 0, 118, 1, output_stage_tlv),

	SOC_SINGLE_TLV("Right Line Mixer Line2L Bypass Volume",
		       LINE2L_2_RLOPM_VOL, 0, 118, 1, output_stage_tlv),

	SOC_SINGLE_TLV("Left HP Mixer Line2R Bypass Volume",
		       LINE2R_2_HPLOUT_VOL, 0, 118, 1, output_stage_tlv),

	SOC_SINGLE_TLV("Right HP Mixer Line2L Bypass Volume",
		       LINE2L_2_HPROUT_VOL, 0, 118, 1, output_stage_tlv),

	SOC_SINGLE_TLV("Left HPCOM Mixer Line2R Bypass Volume",
		       LINE2R_2_HPLCOM_VOL, 0, 118, 1, output_stage_tlv),

	SOC_SINGLE_TLV("Right HPCOM Mixer Line2L Bypass Volume",
		       LINE2L_2_HPRCOM_VOL, 0, 118, 1, output_stage_tlv),

	/* Stereo output controls क्रम direct L-to-L and R-to-R routes */
	SOC_DOUBLE_R_TLV("Line Line2 Bypass Volume",
			 LINE2L_2_LLOPM_VOL, LINE2R_2_RLOPM_VOL,
			 0, 118, 1, output_stage_tlv),

	SOC_DOUBLE_R_TLV("HP Line2 Bypass Volume",
			 LINE2L_2_HPLOUT_VOL, LINE2R_2_HPROUT_VOL,
			 0, 118, 1, output_stage_tlv),

	SOC_DOUBLE_R_TLV("HPCOM Line2 Bypass Volume",
			 LINE2L_2_HPLCOM_VOL, LINE2R_2_HPRCOM_VOL,
			 0, 118, 1, output_stage_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aic3x_mono_controls[] = अणु
	SOC_DOUBLE_R_TLV("Mono Line2 Bypass Volume",
			 LINE2L_2_MONOLOPM_VOL, LINE2R_2_MONOLOPM_VOL,
			 0, 118, 1, output_stage_tlv),
	SOC_DOUBLE_R_TLV("Mono PGA Bypass Volume",
			 PGAL_2_MONOLOPM_VOL, PGAR_2_MONOLOPM_VOL,
			 0, 118, 1, output_stage_tlv),
	SOC_DOUBLE_R_TLV("Mono DAC Playback Volume",
			 DACL1_2_MONOLOPM_VOL, DACR1_2_MONOLOPM_VOL,
			 0, 118, 1, output_stage_tlv),

	SOC_SINGLE("Mono Playback Switch", MONOLOPM_CTRL, 3, 0x01, 0),
	SOC_SINGLE_TLV("Mono Playback Volume", MONOLOPM_CTRL, 4, 9, 0,
			out_tlv),

पूर्ण;

/*
 * Class-D amplअगरier gain. From 0 to 18 dB in 6 dB steps
 */
अटल DECLARE_TLV_DB_SCALE(classd_amp_tlv, 0, 600, 0);

अटल स्थिर काष्ठा snd_kcontrol_new aic3x_classd_amp_gain_ctrl =
	SOC_DOUBLE_TLV("Class-D Playback Volume", CLASSD_CTRL, 6, 4, 3, 0, classd_amp_tlv);

/* Left DAC Mux */
अटल स्थिर काष्ठा snd_kcontrol_new aic3x_left_dac_mux_controls =
SOC_DAPM_ENUM("Route", aic3x_left_dac_क्रमागत);

/* Right DAC Mux */
अटल स्थिर काष्ठा snd_kcontrol_new aic3x_right_dac_mux_controls =
SOC_DAPM_ENUM("Route", aic3x_right_dac_क्रमागत);

/* Left HPCOM Mux */
अटल स्थिर काष्ठा snd_kcontrol_new aic3x_left_hpcom_mux_controls =
SOC_DAPM_ENUM("Route", aic3x_left_hpcom_क्रमागत);

/* Right HPCOM Mux */
अटल स्थिर काष्ठा snd_kcontrol_new aic3x_right_hpcom_mux_controls =
SOC_DAPM_ENUM("Route", aic3x_right_hpcom_क्रमागत);

/* Left Line Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new aic3x_left_line_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("PGAL Bypass Switch", PGAL_2_LLOPM_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("DACL1 Switch", DACL1_2_LLOPM_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("PGAR Bypass Switch", PGAR_2_LLOPM_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("DACR1 Switch", DACR1_2_LLOPM_VOL, 7, 1, 0),
	/* Not on tlv320aic3104 */
	SOC_DAPM_SINGLE("Line2L Bypass Switch", LINE2L_2_LLOPM_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("Line2R Bypass Switch", LINE2R_2_LLOPM_VOL, 7, 1, 0),
पूर्ण;

/* Right Line Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new aic3x_right_line_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("PGAL Bypass Switch", PGAL_2_RLOPM_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("DACL1 Switch", DACL1_2_RLOPM_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("PGAR Bypass Switch", PGAR_2_RLOPM_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("DACR1 Switch", DACR1_2_RLOPM_VOL, 7, 1, 0),
	/* Not on tlv320aic3104 */
	SOC_DAPM_SINGLE("Line2L Bypass Switch", LINE2L_2_RLOPM_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("Line2R Bypass Switch", LINE2R_2_RLOPM_VOL, 7, 1, 0),
पूर्ण;

/* Mono Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new aic3x_mono_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Line2L Bypass Switch", LINE2L_2_MONOLOPM_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("PGAL Bypass Switch", PGAL_2_MONOLOPM_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("DACL1 Switch", DACL1_2_MONOLOPM_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("Line2R Bypass Switch", LINE2R_2_MONOLOPM_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("PGAR Bypass Switch", PGAR_2_MONOLOPM_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("DACR1 Switch", DACR1_2_MONOLOPM_VOL, 7, 1, 0),
पूर्ण;

/* Left HP Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new aic3x_left_hp_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("PGAL Bypass Switch", PGAL_2_HPLOUT_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("DACL1 Switch", DACL1_2_HPLOUT_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("PGAR Bypass Switch", PGAR_2_HPLOUT_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("DACR1 Switch", DACR1_2_HPLOUT_VOL, 7, 1, 0),
	/* Not on tlv320aic3104 */
	SOC_DAPM_SINGLE("Line2L Bypass Switch", LINE2L_2_HPLOUT_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("Line2R Bypass Switch", LINE2R_2_HPLOUT_VOL, 7, 1, 0),
पूर्ण;

/* Right HP Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new aic3x_right_hp_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("PGAL Bypass Switch", PGAL_2_HPROUT_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("DACL1 Switch", DACL1_2_HPROUT_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("PGAR Bypass Switch", PGAR_2_HPROUT_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("DACR1 Switch", DACR1_2_HPROUT_VOL, 7, 1, 0),
	/* Not on tlv320aic3104 */
	SOC_DAPM_SINGLE("Line2L Bypass Switch", LINE2L_2_HPROUT_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("Line2R Bypass Switch", LINE2R_2_HPROUT_VOL, 7, 1, 0),
पूर्ण;

/* Left HPCOM Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new aic3x_left_hpcom_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("PGAL Bypass Switch", PGAL_2_HPLCOM_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("DACL1 Switch", DACL1_2_HPLCOM_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("PGAR Bypass Switch", PGAR_2_HPLCOM_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("DACR1 Switch", DACR1_2_HPLCOM_VOL, 7, 1, 0),
	/* Not on tlv320aic3104 */
	SOC_DAPM_SINGLE("Line2L Bypass Switch", LINE2L_2_HPLCOM_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("Line2R Bypass Switch", LINE2R_2_HPLCOM_VOL, 7, 1, 0),
पूर्ण;

/* Right HPCOM Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new aic3x_right_hpcom_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("PGAL Bypass Switch", PGAL_2_HPRCOM_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("DACL1 Switch", DACL1_2_HPRCOM_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("PGAR Bypass Switch", PGAR_2_HPRCOM_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("DACR1 Switch", DACR1_2_HPRCOM_VOL, 7, 1, 0),
	/* Not on tlv320aic3104 */
	SOC_DAPM_SINGLE("Line2L Bypass Switch", LINE2L_2_HPRCOM_VOL, 7, 1, 0),
	SOC_DAPM_SINGLE("Line2R Bypass Switch", LINE2R_2_HPRCOM_VOL, 7, 1, 0),
पूर्ण;

/* Left PGA Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new aic3x_left_pga_mixer_controls[] = अणु
	SOC_DAPM_SINGLE_AIC3X("Line1L Switch", LINE1L_2_LADC_CTRL, 3, 1, 1),
	SOC_DAPM_SINGLE_AIC3X("Line1R Switch", LINE1R_2_LADC_CTRL, 3, 1, 1),
	SOC_DAPM_SINGLE_AIC3X("Line2L Switch", LINE2L_2_LADC_CTRL, 3, 1, 1),
	SOC_DAPM_SINGLE_AIC3X("Mic3L Switch", MIC3LR_2_LADC_CTRL, 4, 1, 1),
	SOC_DAPM_SINGLE_AIC3X("Mic3R Switch", MIC3LR_2_LADC_CTRL, 0, 1, 1),
पूर्ण;

/* Right PGA Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new aic3x_right_pga_mixer_controls[] = अणु
	SOC_DAPM_SINGLE_AIC3X("Line1R Switch", LINE1R_2_RADC_CTRL, 3, 1, 1),
	SOC_DAPM_SINGLE_AIC3X("Line1L Switch", LINE1L_2_RADC_CTRL, 3, 1, 1),
	SOC_DAPM_SINGLE_AIC3X("Line2R Switch", LINE2R_2_RADC_CTRL, 3, 1, 1),
	SOC_DAPM_SINGLE_AIC3X("Mic3L Switch", MIC3LR_2_RADC_CTRL, 4, 1, 1),
	SOC_DAPM_SINGLE_AIC3X("Mic3R Switch", MIC3LR_2_RADC_CTRL, 0, 1, 1),
पूर्ण;

/* Left PGA Mixer क्रम tlv320aic3104 */
अटल स्थिर काष्ठा snd_kcontrol_new aic3104_left_pga_mixer_controls[] = अणु
	SOC_DAPM_SINGLE_AIC3X("Line1L Switch", LINE1L_2_LADC_CTRL, 3, 1, 1),
	SOC_DAPM_SINGLE_AIC3X("Line1R Switch", LINE1R_2_LADC_CTRL, 3, 1, 1),
	SOC_DAPM_SINGLE_AIC3X("Mic2L Switch", MIC3LR_2_LADC_CTRL, 4, 1, 1),
	SOC_DAPM_SINGLE_AIC3X("Mic2R Switch", MIC3LR_2_LADC_CTRL, 0, 1, 1),
पूर्ण;

/* Right PGA Mixer क्रम tlv320aic3104 */
अटल स्थिर काष्ठा snd_kcontrol_new aic3104_right_pga_mixer_controls[] = अणु
	SOC_DAPM_SINGLE_AIC3X("Line1R Switch", LINE1R_2_RADC_CTRL, 3, 1, 1),
	SOC_DAPM_SINGLE_AIC3X("Line1L Switch", LINE1L_2_RADC_CTRL, 3, 1, 1),
	SOC_DAPM_SINGLE_AIC3X("Mic2L Switch", MIC3LR_2_RADC_CTRL, 4, 1, 1),
	SOC_DAPM_SINGLE_AIC3X("Mic2R Switch", MIC3LR_2_RADC_CTRL, 0, 1, 1),
पूर्ण;

/* Left Line1 Mux */
अटल स्थिर काष्ठा snd_kcontrol_new aic3x_left_line1l_mux_controls =
SOC_DAPM_ENUM("Route", aic3x_line1l_2_l_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new aic3x_right_line1l_mux_controls =
SOC_DAPM_ENUM("Route", aic3x_line1l_2_r_क्रमागत);

/* Right Line1 Mux */
अटल स्थिर काष्ठा snd_kcontrol_new aic3x_right_line1r_mux_controls =
SOC_DAPM_ENUM("Route", aic3x_line1r_2_r_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new aic3x_left_line1r_mux_controls =
SOC_DAPM_ENUM("Route", aic3x_line1r_2_l_क्रमागत);

/* Left Line2 Mux */
अटल स्थिर काष्ठा snd_kcontrol_new aic3x_left_line2_mux_controls =
SOC_DAPM_ENUM("Route", aic3x_line2l_2_ldac_क्रमागत);

/* Right Line2 Mux */
अटल स्थिर काष्ठा snd_kcontrol_new aic3x_right_line2_mux_controls =
SOC_DAPM_ENUM("Route", aic3x_line2r_2_rdac_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget aic3x_dapm_widमाला_लो[] = अणु
	/* Left DAC to Left Outमाला_दो */
	SND_SOC_DAPM_DAC("Left DAC", "Left Playback", DAC_PWR, 7, 0),
	SND_SOC_DAPM_MUX("Left DAC Mux", SND_SOC_NOPM, 0, 0,
			 &aic3x_left_dac_mux_controls),
	SND_SOC_DAPM_MUX("Left HPCOM Mux", SND_SOC_NOPM, 0, 0,
			 &aic3x_left_hpcom_mux_controls),
	SND_SOC_DAPM_PGA("Left Line Out", LLOPM_CTRL, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Left HP Out", HPLOUT_CTRL, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Left HP Com", HPLCOM_CTRL, 0, 0, शून्य, 0),

	/* Right DAC to Right Outमाला_दो */
	SND_SOC_DAPM_DAC("Right DAC", "Right Playback", DAC_PWR, 6, 0),
	SND_SOC_DAPM_MUX("Right DAC Mux", SND_SOC_NOPM, 0, 0,
			 &aic3x_right_dac_mux_controls),
	SND_SOC_DAPM_MUX("Right HPCOM Mux", SND_SOC_NOPM, 0, 0,
			 &aic3x_right_hpcom_mux_controls),
	SND_SOC_DAPM_PGA("Right Line Out", RLOPM_CTRL, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Right HP Out", HPROUT_CTRL, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Right HP Com", HPRCOM_CTRL, 0, 0, शून्य, 0),

	/* Inमाला_दो to Left ADC */
	SND_SOC_DAPM_ADC("Left ADC", "Left Capture", LINE1L_2_LADC_CTRL, 2, 0),
	SND_SOC_DAPM_MUX("Left Line1L Mux", SND_SOC_NOPM, 0, 0,
			 &aic3x_left_line1l_mux_controls),
	SND_SOC_DAPM_MUX("Left Line1R Mux", SND_SOC_NOPM, 0, 0,
			 &aic3x_left_line1r_mux_controls),

	/* Inमाला_दो to Right ADC */
	SND_SOC_DAPM_ADC("Right ADC", "Right Capture",
			 LINE1R_2_RADC_CTRL, 2, 0),
	SND_SOC_DAPM_MUX("Right Line1L Mux", SND_SOC_NOPM, 0, 0,
			 &aic3x_right_line1l_mux_controls),
	SND_SOC_DAPM_MUX("Right Line1R Mux", SND_SOC_NOPM, 0, 0,
			 &aic3x_right_line1r_mux_controls),

	/* Mic Bias */
	SND_SOC_DAPM_SUPPLY("Mic Bias", MICBIAS_CTRL, 6, 0,
			 mic_bias_event,
			 SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_OUTPUT("LLOUT"),
	SND_SOC_DAPM_OUTPUT("RLOUT"),
	SND_SOC_DAPM_OUTPUT("HPLOUT"),
	SND_SOC_DAPM_OUTPUT("HPROUT"),
	SND_SOC_DAPM_OUTPUT("HPLCOM"),
	SND_SOC_DAPM_OUTPUT("HPRCOM"),

	SND_SOC_DAPM_INPUT("LINE1L"),
	SND_SOC_DAPM_INPUT("LINE1R"),

	/*
	 * Virtual output pin to detection block inside codec. This can be
	 * used to keep codec bias on अगर gpio or detection features are needed.
	 * Force pin on or स्थिरruct a path with an input jack and mic bias
	 * widमाला_लो.
	 */
	SND_SOC_DAPM_OUTPUT("Detection"),
पूर्ण;

/* For other than tlv320aic3104 */
अटल स्थिर काष्ठा snd_soc_dapm_widget aic3x_extra_dapm_widमाला_लो[] = अणु
	/* Inमाला_दो to Left ADC */
	SND_SOC_DAPM_MIXER("Left PGA Mixer", SND_SOC_NOPM, 0, 0,
			   &aic3x_left_pga_mixer_controls[0],
			   ARRAY_SIZE(aic3x_left_pga_mixer_controls)),
	SND_SOC_DAPM_MUX("Left Line2L Mux", SND_SOC_NOPM, 0, 0,
			 &aic3x_left_line2_mux_controls),

	/* Inमाला_दो to Right ADC */
	SND_SOC_DAPM_MIXER("Right PGA Mixer", SND_SOC_NOPM, 0, 0,
			   &aic3x_right_pga_mixer_controls[0],
			   ARRAY_SIZE(aic3x_right_pga_mixer_controls)),
	SND_SOC_DAPM_MUX("Right Line2R Mux", SND_SOC_NOPM, 0, 0,
			 &aic3x_right_line2_mux_controls),

	/*
	 * Not a real mic bias widget but similar function. This is क्रम dynamic
	 * control of GPIO1 digital mic modulator घड़ी output function when
	 * using digital mic.
	 */
	SND_SOC_DAPM_REG(snd_soc_dapm_micbias, "GPIO1 dmic modclk",
			 AIC3X_GPIO1_REG, 4, 0xf,
			 AIC3X_GPIO1_FUNC_DIGITAL_MIC_MODCLK,
			 AIC3X_GPIO1_FUNC_DISABLED),

	/*
	 * Also similar function like mic bias. Selects digital mic with
	 * configurable oversampling rate instead of ADC converter.
	 */
	SND_SOC_DAPM_REG(snd_soc_dapm_micbias, "DMic Rate 128",
			 AIC3X_ASD_INTF_CTRLA, 0, 3, 1, 0),
	SND_SOC_DAPM_REG(snd_soc_dapm_micbias, "DMic Rate 64",
			 AIC3X_ASD_INTF_CTRLA, 0, 3, 2, 0),
	SND_SOC_DAPM_REG(snd_soc_dapm_micbias, "DMic Rate 32",
			 AIC3X_ASD_INTF_CTRLA, 0, 3, 3, 0),

	/* Output mixers */
	SND_SOC_DAPM_MIXER("Left Line Mixer", SND_SOC_NOPM, 0, 0,
			   &aic3x_left_line_mixer_controls[0],
			   ARRAY_SIZE(aic3x_left_line_mixer_controls)),
	SND_SOC_DAPM_MIXER("Right Line Mixer", SND_SOC_NOPM, 0, 0,
			   &aic3x_right_line_mixer_controls[0],
			   ARRAY_SIZE(aic3x_right_line_mixer_controls)),
	SND_SOC_DAPM_MIXER("Left HP Mixer", SND_SOC_NOPM, 0, 0,
			   &aic3x_left_hp_mixer_controls[0],
			   ARRAY_SIZE(aic3x_left_hp_mixer_controls)),
	SND_SOC_DAPM_MIXER("Right HP Mixer", SND_SOC_NOPM, 0, 0,
			   &aic3x_right_hp_mixer_controls[0],
			   ARRAY_SIZE(aic3x_right_hp_mixer_controls)),
	SND_SOC_DAPM_MIXER("Left HPCOM Mixer", SND_SOC_NOPM, 0, 0,
			   &aic3x_left_hpcom_mixer_controls[0],
			   ARRAY_SIZE(aic3x_left_hpcom_mixer_controls)),
	SND_SOC_DAPM_MIXER("Right HPCOM Mixer", SND_SOC_NOPM, 0, 0,
			   &aic3x_right_hpcom_mixer_controls[0],
			   ARRAY_SIZE(aic3x_right_hpcom_mixer_controls)),

	SND_SOC_DAPM_INPUT("MIC3L"),
	SND_SOC_DAPM_INPUT("MIC3R"),
	SND_SOC_DAPM_INPUT("LINE2L"),
	SND_SOC_DAPM_INPUT("LINE2R"),
पूर्ण;

/* For tlv320aic3104 */
अटल स्थिर काष्ठा snd_soc_dapm_widget aic3104_extra_dapm_widमाला_लो[] = अणु
	/* Inमाला_दो to Left ADC */
	SND_SOC_DAPM_MIXER("Left PGA Mixer", SND_SOC_NOPM, 0, 0,
			   &aic3104_left_pga_mixer_controls[0],
			   ARRAY_SIZE(aic3104_left_pga_mixer_controls)),

	/* Inमाला_दो to Right ADC */
	SND_SOC_DAPM_MIXER("Right PGA Mixer", SND_SOC_NOPM, 0, 0,
			   &aic3104_right_pga_mixer_controls[0],
			   ARRAY_SIZE(aic3104_right_pga_mixer_controls)),

	/* Output mixers */
	SND_SOC_DAPM_MIXER("Left Line Mixer", SND_SOC_NOPM, 0, 0,
			   &aic3x_left_line_mixer_controls[0],
			   ARRAY_SIZE(aic3x_left_line_mixer_controls) - 2),
	SND_SOC_DAPM_MIXER("Right Line Mixer", SND_SOC_NOPM, 0, 0,
			   &aic3x_right_line_mixer_controls[0],
			   ARRAY_SIZE(aic3x_right_line_mixer_controls) - 2),
	SND_SOC_DAPM_MIXER("Left HP Mixer", SND_SOC_NOPM, 0, 0,
			   &aic3x_left_hp_mixer_controls[0],
			   ARRAY_SIZE(aic3x_left_hp_mixer_controls) - 2),
	SND_SOC_DAPM_MIXER("Right HP Mixer", SND_SOC_NOPM, 0, 0,
			   &aic3x_right_hp_mixer_controls[0],
			   ARRAY_SIZE(aic3x_right_hp_mixer_controls) - 2),
	SND_SOC_DAPM_MIXER("Left HPCOM Mixer", SND_SOC_NOPM, 0, 0,
			   &aic3x_left_hpcom_mixer_controls[0],
			   ARRAY_SIZE(aic3x_left_hpcom_mixer_controls) - 2),
	SND_SOC_DAPM_MIXER("Right HPCOM Mixer", SND_SOC_NOPM, 0, 0,
			   &aic3x_right_hpcom_mixer_controls[0],
			   ARRAY_SIZE(aic3x_right_hpcom_mixer_controls) - 2),

	SND_SOC_DAPM_INPUT("MIC2L"),
	SND_SOC_DAPM_INPUT("MIC2R"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget aic3x_dapm_mono_widमाला_लो[] = अणु
	/* Mono Output */
	SND_SOC_DAPM_PGA("Mono Out", MONOLOPM_CTRL, 0, 0, शून्य, 0),

	SND_SOC_DAPM_MIXER("Mono Mixer", SND_SOC_NOPM, 0, 0,
			   &aic3x_mono_mixer_controls[0],
			   ARRAY_SIZE(aic3x_mono_mixer_controls)),

	SND_SOC_DAPM_OUTPUT("MONO_LOUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget aic3007_dapm_widमाला_लो[] = अणु
	/* Class-D outमाला_दो */
	SND_SOC_DAPM_PGA("Left Class-D Out", CLASSD_CTRL, 3, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Class-D Out", CLASSD_CTRL, 2, 0, शून्य, 0),

	SND_SOC_DAPM_OUTPUT("SPOP"),
	SND_SOC_DAPM_OUTPUT("SPOM"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route पूर्णांकercon[] = अणु
	/* Left Input */
	अणु"Left Line1L Mux", "single-ended", "LINE1L"पूर्ण,
	अणु"Left Line1L Mux", "differential", "LINE1L"पूर्ण,
	अणु"Left Line1R Mux", "single-ended", "LINE1R"पूर्ण,
	अणु"Left Line1R Mux", "differential", "LINE1R"पूर्ण,

	अणु"Left PGA Mixer", "Line1L Switch", "Left Line1L Mux"पूर्ण,
	अणु"Left PGA Mixer", "Line1R Switch", "Left Line1R Mux"पूर्ण,

	अणु"Left ADC", शून्य, "Left PGA Mixer"पूर्ण,

	/* Right Input */
	अणु"Right Line1R Mux", "single-ended", "LINE1R"पूर्ण,
	अणु"Right Line1R Mux", "differential", "LINE1R"पूर्ण,
	अणु"Right Line1L Mux", "single-ended", "LINE1L"पूर्ण,
	अणु"Right Line1L Mux", "differential", "LINE1L"पूर्ण,

	अणु"Right PGA Mixer", "Line1L Switch", "Right Line1L Mux"पूर्ण,
	अणु"Right PGA Mixer", "Line1R Switch", "Right Line1R Mux"पूर्ण,

	अणु"Right ADC", शून्य, "Right PGA Mixer"पूर्ण,

	/* Left DAC Output */
	अणु"Left DAC Mux", "DAC_L1", "Left DAC"पूर्ण,
	अणु"Left DAC Mux", "DAC_L2", "Left DAC"पूर्ण,
	अणु"Left DAC Mux", "DAC_L3", "Left DAC"पूर्ण,

	/* Right DAC Output */
	अणु"Right DAC Mux", "DAC_R1", "Right DAC"पूर्ण,
	अणु"Right DAC Mux", "DAC_R2", "Right DAC"पूर्ण,
	अणु"Right DAC Mux", "DAC_R3", "Right DAC"पूर्ण,

	/* Left Line Output */
	अणु"Left Line Mixer", "PGAL Bypass Switch", "Left PGA Mixer"पूर्ण,
	अणु"Left Line Mixer", "DACL1 Switch", "Left DAC Mux"पूर्ण,
	अणु"Left Line Mixer", "PGAR Bypass Switch", "Right PGA Mixer"पूर्ण,
	अणु"Left Line Mixer", "DACR1 Switch", "Right DAC Mux"पूर्ण,

	अणु"Left Line Out", शून्य, "Left Line Mixer"पूर्ण,
	अणु"Left Line Out", शून्य, "Left DAC Mux"पूर्ण,
	अणु"LLOUT", शून्य, "Left Line Out"पूर्ण,

	/* Right Line Output */
	अणु"Right Line Mixer", "PGAL Bypass Switch", "Left PGA Mixer"पूर्ण,
	अणु"Right Line Mixer", "DACL1 Switch", "Left DAC Mux"पूर्ण,
	अणु"Right Line Mixer", "PGAR Bypass Switch", "Right PGA Mixer"पूर्ण,
	अणु"Right Line Mixer", "DACR1 Switch", "Right DAC Mux"पूर्ण,

	अणु"Right Line Out", शून्य, "Right Line Mixer"पूर्ण,
	अणु"Right Line Out", शून्य, "Right DAC Mux"पूर्ण,
	अणु"RLOUT", शून्य, "Right Line Out"पूर्ण,

	/* Left HP Output */
	अणु"Left HP Mixer", "PGAL Bypass Switch", "Left PGA Mixer"पूर्ण,
	अणु"Left HP Mixer", "DACL1 Switch", "Left DAC Mux"पूर्ण,
	अणु"Left HP Mixer", "PGAR Bypass Switch", "Right PGA Mixer"पूर्ण,
	अणु"Left HP Mixer", "DACR1 Switch", "Right DAC Mux"पूर्ण,

	अणु"Left HP Out", शून्य, "Left HP Mixer"पूर्ण,
	अणु"Left HP Out", शून्य, "Left DAC Mux"पूर्ण,
	अणु"HPLOUT", शून्य, "Left HP Out"पूर्ण,

	/* Right HP Output */
	अणु"Right HP Mixer", "PGAL Bypass Switch", "Left PGA Mixer"पूर्ण,
	अणु"Right HP Mixer", "DACL1 Switch", "Left DAC Mux"पूर्ण,
	अणु"Right HP Mixer", "PGAR Bypass Switch", "Right PGA Mixer"पूर्ण,
	अणु"Right HP Mixer", "DACR1 Switch", "Right DAC Mux"पूर्ण,

	अणु"Right HP Out", शून्य, "Right HP Mixer"पूर्ण,
	अणु"Right HP Out", शून्य, "Right DAC Mux"पूर्ण,
	अणु"HPROUT", शून्य, "Right HP Out"पूर्ण,

	/* Left HPCOM Output */
	अणु"Left HPCOM Mixer", "PGAL Bypass Switch", "Left PGA Mixer"पूर्ण,
	अणु"Left HPCOM Mixer", "DACL1 Switch", "Left DAC Mux"पूर्ण,
	अणु"Left HPCOM Mixer", "PGAR Bypass Switch", "Right PGA Mixer"पूर्ण,
	अणु"Left HPCOM Mixer", "DACR1 Switch", "Right DAC Mux"पूर्ण,

	अणु"Left HPCOM Mux", "differential of HPLOUT", "Left HP Mixer"पूर्ण,
	अणु"Left HPCOM Mux", "constant VCM", "Left HPCOM Mixer"पूर्ण,
	अणु"Left HPCOM Mux", "single-ended", "Left HPCOM Mixer"पूर्ण,
	अणु"Left HP Com", शून्य, "Left HPCOM Mux"पूर्ण,
	अणु"HPLCOM", शून्य, "Left HP Com"पूर्ण,

	/* Right HPCOM Output */
	अणु"Right HPCOM Mixer", "PGAL Bypass Switch", "Left PGA Mixer"पूर्ण,
	अणु"Right HPCOM Mixer", "DACL1 Switch", "Left DAC Mux"पूर्ण,
	अणु"Right HPCOM Mixer", "PGAR Bypass Switch", "Right PGA Mixer"पूर्ण,
	अणु"Right HPCOM Mixer", "DACR1 Switch", "Right DAC Mux"पूर्ण,

	अणु"Right HPCOM Mux", "differential of HPROUT", "Right HP Mixer"पूर्ण,
	अणु"Right HPCOM Mux", "constant VCM", "Right HPCOM Mixer"पूर्ण,
	अणु"Right HPCOM Mux", "single-ended", "Right HPCOM Mixer"पूर्ण,
	अणु"Right HPCOM Mux", "differential of HPLCOM", "Left HPCOM Mixer"पूर्ण,
	अणु"Right HPCOM Mux", "external feedback", "Right HPCOM Mixer"पूर्ण,
	अणु"Right HP Com", शून्य, "Right HPCOM Mux"पूर्ण,
	अणु"HPRCOM", शून्य, "Right HP Com"पूर्ण,
पूर्ण;

/* For other than tlv320aic3104 */
अटल स्थिर काष्ठा snd_soc_dapm_route पूर्णांकercon_extra[] = अणु
	/* Left Input */
	अणु"Left Line2L Mux", "single-ended", "LINE2L"पूर्ण,
	अणु"Left Line2L Mux", "differential", "LINE2L"पूर्ण,

	अणु"Left PGA Mixer", "Line2L Switch", "Left Line2L Mux"पूर्ण,
	अणु"Left PGA Mixer", "Mic3L Switch", "MIC3L"पूर्ण,
	अणु"Left PGA Mixer", "Mic3R Switch", "MIC3R"पूर्ण,

	अणु"Left ADC", शून्य, "GPIO1 dmic modclk"पूर्ण,

	/* Right Input */
	अणु"Right Line2R Mux", "single-ended", "LINE2R"पूर्ण,
	अणु"Right Line2R Mux", "differential", "LINE2R"पूर्ण,

	अणु"Right PGA Mixer", "Line2R Switch", "Right Line2R Mux"पूर्ण,
	अणु"Right PGA Mixer", "Mic3L Switch", "MIC3L"पूर्ण,
	अणु"Right PGA Mixer", "Mic3R Switch", "MIC3R"पूर्ण,

	अणु"Right ADC", शून्य, "GPIO1 dmic modclk"पूर्ण,

	/*
	 * Logical path between digital mic enable and GPIO1 modulator घड़ी
	 * output function
	 */
	अणु"GPIO1 dmic modclk", शून्य, "DMic Rate 128"पूर्ण,
	अणु"GPIO1 dmic modclk", शून्य, "DMic Rate 64"पूर्ण,
	अणु"GPIO1 dmic modclk", शून्य, "DMic Rate 32"पूर्ण,

	/* Left Line Output */
	अणु"Left Line Mixer", "Line2L Bypass Switch", "Left Line2L Mux"पूर्ण,
	अणु"Left Line Mixer", "Line2R Bypass Switch", "Right Line2R Mux"पूर्ण,

	/* Right Line Output */
	अणु"Right Line Mixer", "Line2L Bypass Switch", "Left Line2L Mux"पूर्ण,
	अणु"Right Line Mixer", "Line2R Bypass Switch", "Right Line2R Mux"पूर्ण,

	/* Left HP Output */
	अणु"Left HP Mixer", "Line2L Bypass Switch", "Left Line2L Mux"पूर्ण,
	अणु"Left HP Mixer", "Line2R Bypass Switch", "Right Line2R Mux"पूर्ण,

	/* Right HP Output */
	अणु"Right HP Mixer", "Line2L Bypass Switch", "Left Line2L Mux"पूर्ण,
	अणु"Right HP Mixer", "Line2R Bypass Switch", "Right Line2R Mux"पूर्ण,

	/* Left HPCOM Output */
	अणु"Left HPCOM Mixer", "Line2L Bypass Switch", "Left Line2L Mux"पूर्ण,
	अणु"Left HPCOM Mixer", "Line2R Bypass Switch", "Right Line2R Mux"पूर्ण,

	/* Right HPCOM Output */
	अणु"Right HPCOM Mixer", "Line2L Bypass Switch", "Left Line2L Mux"पूर्ण,
	अणु"Right HPCOM Mixer", "Line2R Bypass Switch", "Right Line2R Mux"पूर्ण,
पूर्ण;

/* For tlv320aic3104 */
अटल स्थिर काष्ठा snd_soc_dapm_route पूर्णांकercon_extra_3104[] = अणु
	/* Left Input */
	अणु"Left PGA Mixer", "Mic2L Switch", "MIC2L"पूर्ण,
	अणु"Left PGA Mixer", "Mic2R Switch", "MIC2R"पूर्ण,

	/* Right Input */
	अणु"Right PGA Mixer", "Mic2L Switch", "MIC2L"पूर्ण,
	अणु"Right PGA Mixer", "Mic2R Switch", "MIC2R"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route पूर्णांकercon_mono[] = अणु
	/* Mono Output */
	अणु"Mono Mixer", "Line2L Bypass Switch", "Left Line2L Mux"पूर्ण,
	अणु"Mono Mixer", "PGAL Bypass Switch", "Left PGA Mixer"पूर्ण,
	अणु"Mono Mixer", "DACL1 Switch", "Left DAC Mux"पूर्ण,
	अणु"Mono Mixer", "Line2R Bypass Switch", "Right Line2R Mux"पूर्ण,
	अणु"Mono Mixer", "PGAR Bypass Switch", "Right PGA Mixer"पूर्ण,
	अणु"Mono Mixer", "DACR1 Switch", "Right DAC Mux"पूर्ण,
	अणु"Mono Out", शून्य, "Mono Mixer"पूर्ण,
	अणु"MONO_LOUT", शून्य, "Mono Out"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route पूर्णांकercon_3007[] = अणु
	/* Class-D outमाला_दो */
	अणु"Left Class-D Out", शून्य, "Left Line Out"पूर्ण,
	अणु"Right Class-D Out", शून्य, "Left Line Out"पूर्ण,
	अणु"SPOP", शून्य, "Left Class-D Out"पूर्ण,
	अणु"SPOM", शून्य, "Right Class-D Out"पूर्ण,
पूर्ण;

अटल पूर्णांक aic3x_add_widमाला_लो(काष्ठा snd_soc_component *component)
अणु
	काष्ठा aic3x_priv *aic3x = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	चयन (aic3x->model) अणु
	हाल AIC3X_MODEL_3X:
	हाल AIC3X_MODEL_33:
	हाल AIC3X_MODEL_3106:
		snd_soc_dapm_new_controls(dapm, aic3x_extra_dapm_widमाला_लो,
					  ARRAY_SIZE(aic3x_extra_dapm_widमाला_लो));
		snd_soc_dapm_add_routes(dapm, पूर्णांकercon_extra,
					ARRAY_SIZE(पूर्णांकercon_extra));
		snd_soc_dapm_new_controls(dapm, aic3x_dapm_mono_widमाला_लो,
			ARRAY_SIZE(aic3x_dapm_mono_widमाला_लो));
		snd_soc_dapm_add_routes(dapm, पूर्णांकercon_mono,
					ARRAY_SIZE(पूर्णांकercon_mono));
		अवरोध;
	हाल AIC3X_MODEL_3007:
		snd_soc_dapm_new_controls(dapm, aic3x_extra_dapm_widमाला_लो,
					  ARRAY_SIZE(aic3x_extra_dapm_widमाला_लो));
		snd_soc_dapm_add_routes(dapm, पूर्णांकercon_extra,
					ARRAY_SIZE(पूर्णांकercon_extra));
		snd_soc_dapm_new_controls(dapm, aic3007_dapm_widमाला_लो,
			ARRAY_SIZE(aic3007_dapm_widमाला_लो));
		snd_soc_dapm_add_routes(dapm, पूर्णांकercon_3007,
					ARRAY_SIZE(पूर्णांकercon_3007));
		अवरोध;
	हाल AIC3X_MODEL_3104:
		snd_soc_dapm_new_controls(dapm, aic3104_extra_dapm_widमाला_लो,
				ARRAY_SIZE(aic3104_extra_dapm_widमाला_लो));
		snd_soc_dapm_add_routes(dapm, पूर्णांकercon_extra_3104,
				ARRAY_SIZE(पूर्णांकercon_extra_3104));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aic3x_hw_params(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_pcm_hw_params *params,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा aic3x_priv *aic3x = snd_soc_component_get_drvdata(component);
	पूर्णांक codec_clk = 0, bypass_pll = 0, fsref, last_clk = 0;
	u8 data, j, r, p, pll_q, pll_p = 1, pll_r = 1, pll_j = 1;
	u16 d, pll_d = 1;
	पूर्णांक clk;
	पूर्णांक width = aic3x->slot_width;

	अगर (!width)
		width = params_width(params);

	/* select data word length */
	data = snd_soc_component_पढ़ो(component, AIC3X_ASD_INTF_CTRLB) & (~(0x3 << 4));
	चयन (width) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		data |= (0x01 << 4);
		अवरोध;
	हाल 24:
		data |= (0x02 << 4);
		अवरोध;
	हाल 32:
		data |= (0x03 << 4);
		अवरोध;
	पूर्ण
	snd_soc_component_ग_लिखो(component, AIC3X_ASD_INTF_CTRLB, data);

	/* Fsref can be 44100 or 48000 */
	fsref = (params_rate(params) % 11025 == 0) ? 44100 : 48000;

	/* Try to find a value क्रम Q which allows us to bypass the PLL and
	 * generate CODEC_CLK directly. */
	क्रम (pll_q = 2; pll_q < 18; pll_q++)
		अगर (aic3x->sysclk / (128 * pll_q) == fsref) अणु
			bypass_pll = 1;
			अवरोध;
		पूर्ण

	अगर (bypass_pll) अणु
		pll_q &= 0xf;
		snd_soc_component_ग_लिखो(component, AIC3X_PLL_PROGA_REG, pll_q << PLLQ_SHIFT);
		snd_soc_component_ग_लिखो(component, AIC3X_GPIOB_REG, CODEC_CLKIN_CLKDIV);
		/* disable PLL अगर it is bypassed */
		snd_soc_component_update_bits(component, AIC3X_PLL_PROGA_REG, PLL_ENABLE, 0);

	पूर्ण अन्यथा अणु
		snd_soc_component_ग_लिखो(component, AIC3X_GPIOB_REG, CODEC_CLKIN_PLLDIV);
		/* enable PLL when it is used */
		snd_soc_component_update_bits(component, AIC3X_PLL_PROGA_REG,
				    PLL_ENABLE, PLL_ENABLE);
	पूर्ण

	/* Route Left DAC to left channel input and
	 * right DAC to right channel input */
	data = (LDAC2LCH | RDAC2RCH);
	data |= (fsref == 44100) ? FSREF_44100 : FSREF_48000;
	अगर (params_rate(params) >= 64000)
		data |= DUAL_RATE_MODE;
	snd_soc_component_ग_लिखो(component, AIC3X_CODEC_DATAPATH_REG, data);

	/* codec sample rate select */
	data = (fsref * 20) / params_rate(params);
	अगर (params_rate(params) < 64000)
		data /= 2;
	data /= 5;
	data -= 2;
	data |= (data << 4);
	snd_soc_component_ग_लिखो(component, AIC3X_SAMPLE_RATE_SEL_REG, data);

	अगर (bypass_pll)
		वापस 0;

	/* Use PLL, compute appropriate setup क्रम j, d, r and p, the बंदst
	 * one wins the game. Try with d==0 first, next with d!=0.
	 * Constraपूर्णांकs क्रम j are according to the datasheet.
	 * The sysclk is भागided by 1000 to prevent पूर्णांकeger overflows.
	 */

	codec_clk = (2048 * fsref) / (aic3x->sysclk / 1000);

	क्रम (r = 1; r <= 16; r++)
		क्रम (p = 1; p <= 8; p++) अणु
			क्रम (j = 4; j <= 55; j++) अणु
				/* This is actually 1000*((j+(d/10000))*r)/p
				 * The term had to be converted to get
				 * rid of the भागision by 10000; d = 0 here
				 */
				पूर्णांक पंचांगp_clk = (1000 * j * r) / p;

				/* Check whether this values get बंदr than
				 * the best ones we had beक्रमe
				 */
				अगर (असल(codec_clk - पंचांगp_clk) <
					असल(codec_clk - last_clk)) अणु
					pll_j = j; pll_d = 0;
					pll_r = r; pll_p = p;
					last_clk = पंचांगp_clk;
				पूर्ण

				/* Early निकास क्रम exact matches */
				अगर (पंचांगp_clk == codec_clk)
					जाओ found;
			पूर्ण
		पूर्ण

	/* try with d != 0 */
	क्रम (p = 1; p <= 8; p++) अणु
		j = codec_clk * p / 1000;

		अगर (j < 4 || j > 11)
			जारी;

		/* करो not use codec_clk here since we'd loose precision */
		d = ((2048 * p * fsref) - j * aic3x->sysclk)
			* 100 / (aic3x->sysclk/100);

		clk = (10000 * j + d) / (10 * p);

		/* check whether this values get बंदr than the best
		 * ones we had beक्रमe */
		अगर (असल(codec_clk - clk) < असल(codec_clk - last_clk)) अणु
			pll_j = j; pll_d = d; pll_r = 1; pll_p = p;
			last_clk = clk;
		पूर्ण

		/* Early निकास क्रम exact matches */
		अगर (clk == codec_clk)
			जाओ found;
	पूर्ण

	अगर (last_clk == 0) अणु
		prपूर्णांकk(KERN_ERR "%s(): unable to setup PLL\n", __func__);
		वापस -EINVAL;
	पूर्ण

found:
	snd_soc_component_update_bits(component, AIC3X_PLL_PROGA_REG, PLLP_MASK, pll_p);
	snd_soc_component_ग_लिखो(component, AIC3X_OVRF_STATUS_AND_PLLR_REG,
		      pll_r << PLLR_SHIFT);
	snd_soc_component_ग_लिखो(component, AIC3X_PLL_PROGB_REG, pll_j << PLLJ_SHIFT);
	snd_soc_component_ग_लिखो(component, AIC3X_PLL_PROGC_REG,
		      (pll_d >> 6) << PLLD_MSB_SHIFT);
	snd_soc_component_ग_लिखो(component, AIC3X_PLL_PROGD_REG,
		      (pll_d & 0x3F) << PLLD_LSB_SHIFT);

	वापस 0;
पूर्ण

अटल पूर्णांक aic3x_prepare(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा aic3x_priv *aic3x = snd_soc_component_get_drvdata(component);
	पूर्णांक delay = 0;
	पूर्णांक width = aic3x->slot_width;

	अगर (!width)
		width = substream->runसमय->sample_bits;

	/* TDM slot selection only valid in DSP_A/_B mode */
	अगर (aic3x->dai_fmt == SND_SOC_DAIFMT_DSP_A)
		delay += (aic3x->tdm_delay*width + 1);
	अन्यथा अगर (aic3x->dai_fmt == SND_SOC_DAIFMT_DSP_B)
		delay += aic3x->tdm_delay*width;

	/* Configure data delay */
	snd_soc_component_ग_लिखो(component, AIC3X_ASD_INTF_CTRLC, delay);

	वापस 0;
पूर्ण

अटल पूर्णांक aic3x_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u8 ldac_reg = snd_soc_component_पढ़ो(component, LDAC_VOL) & ~MUTE_ON;
	u8 rdac_reg = snd_soc_component_पढ़ो(component, RDAC_VOL) & ~MUTE_ON;

	अगर (mute) अणु
		snd_soc_component_ग_लिखो(component, LDAC_VOL, ldac_reg | MUTE_ON);
		snd_soc_component_ग_लिखो(component, RDAC_VOL, rdac_reg | MUTE_ON);
	पूर्ण अन्यथा अणु
		snd_soc_component_ग_लिखो(component, LDAC_VOL, ldac_reg);
		snd_soc_component_ग_लिखो(component, RDAC_VOL, rdac_reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aic3x_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा aic3x_priv *aic3x = snd_soc_component_get_drvdata(component);

	/* set घड़ी on MCLK or GPIO2 or BCLK */
	snd_soc_component_update_bits(component, AIC3X_CLKGEN_CTRL_REG, PLLCLK_IN_MASK,
				clk_id << PLLCLK_IN_SHIFT);
	snd_soc_component_update_bits(component, AIC3X_CLKGEN_CTRL_REG, CLKDIV_IN_MASK,
				clk_id << CLKDIV_IN_SHIFT);

	aic3x->sysclk = freq;
	वापस 0;
पूर्ण

अटल पूर्णांक aic3x_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
			     अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा aic3x_priv *aic3x = snd_soc_component_get_drvdata(component);
	u8 अगरace_areg, अगरace_breg;

	अगरace_areg = snd_soc_component_पढ़ो(component, AIC3X_ASD_INTF_CTRLA) & 0x3f;
	अगरace_breg = snd_soc_component_पढ़ो(component, AIC3X_ASD_INTF_CTRLB) & 0x3f;

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		aic3x->master = 1;
		अगरace_areg |= BIT_CLK_MASTER | WORD_CLK_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		aic3x->master = 0;
		अगरace_areg &= ~(BIT_CLK_MASTER | WORD_CLK_MASTER);
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		aic3x->master = 1;
		अगरace_areg |= BIT_CLK_MASTER;
		अगरace_areg &= ~WORD_CLK_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		aic3x->master = 1;
		अगरace_areg |= WORD_CLK_MASTER;
		अगरace_areg &= ~BIT_CLK_MASTER;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * match both पूर्णांकerface क्रमmat and संकेत polarities since they
	 * are fixed
	 */
	चयन (fmt & (SND_SOC_DAIFMT_FORMAT_MASK |
		       SND_SOC_DAIFMT_INV_MASK)) अणु
	हाल (SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF):
		अवरोध;
	हाल (SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_IB_NF):
	हाल (SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_IB_NF):
		अगरace_breg |= (0x01 << 6);
		अवरोध;
	हाल (SND_SOC_DAIFMT_RIGHT_J | SND_SOC_DAIFMT_NB_NF):
		अगरace_breg |= (0x02 << 6);
		अवरोध;
	हाल (SND_SOC_DAIFMT_LEFT_J | SND_SOC_DAIFMT_NB_NF):
		अगरace_breg |= (0x03 << 6);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	aic3x->dai_fmt = fmt & SND_SOC_DAIFMT_FORMAT_MASK;

	/* set अगरace */
	snd_soc_component_ग_लिखो(component, AIC3X_ASD_INTF_CTRLA, अगरace_areg);
	snd_soc_component_ग_लिखो(component, AIC3X_ASD_INTF_CTRLB, अगरace_breg);

	वापस 0;
पूर्ण

अटल पूर्णांक aic3x_set_dai_tdm_slot(काष्ठा snd_soc_dai *codec_dai,
				  अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
				  पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा aic3x_priv *aic3x = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक lsb;

	अगर (tx_mask != rx_mask) अणु
		dev_err(component->dev, "tx and rx masks must be symmetric\n");
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(!tx_mask)) अणु
		dev_err(component->dev, "tx and rx masks need to be non 0\n");
		वापस -EINVAL;
	पूर्ण

	/* TDM based on DSP mode requires slots to be adjacent */
	lsb = __ffs(tx_mask);
	अगर ((lsb + 1) != __fls(tx_mask)) अणु
		dev_err(component->dev, "Invalid mask, slots must be adjacent\n");
		वापस -EINVAL;
	पूर्ण

	चयन (slot_width) अणु
	हाल 16:
	हाल 20:
	हाल 24:
	हाल 32:
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported slot width %d\n", slot_width);
		वापस -EINVAL;
	पूर्ण


	aic3x->tdm_delay = lsb;
	aic3x->slot_width = slot_width;

	/* DOUT in high-impedance on inactive bit घड़ीs */
	snd_soc_component_update_bits(component, AIC3X_ASD_INTF_CTRLA,
			    DOUT_TRISTATE, DOUT_TRISTATE);

	वापस 0;
पूर्ण

अटल पूर्णांक aic3x_regulator_event(काष्ठा notअगरier_block *nb,
				 अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा aic3x_disable_nb *disable_nb =
		container_of(nb, काष्ठा aic3x_disable_nb, nb);
	काष्ठा aic3x_priv *aic3x = disable_nb->aic3x;

	अगर (event & REGULATOR_EVENT_DISABLE) अणु
		/*
		 * Put codec to reset and require cache sync as at least one
		 * of the supplies was disabled
		 */
		अगर (gpio_is_valid(aic3x->gpio_reset))
			gpio_set_value(aic3x->gpio_reset, 0);
		regcache_mark_dirty(aic3x->regmap);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aic3x_set_घातer(काष्ठा snd_soc_component *component, पूर्णांक घातer)
अणु
	काष्ठा aic3x_priv *aic3x = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक pll_c, pll_d;
	पूर्णांक ret;

	अगर (घातer) अणु
		ret = regulator_bulk_enable(ARRAY_SIZE(aic3x->supplies),
					    aic3x->supplies);
		अगर (ret)
			जाओ out;
		aic3x->घातer = 1;

		अगर (gpio_is_valid(aic3x->gpio_reset)) अणु
			udelay(1);
			gpio_set_value(aic3x->gpio_reset, 1);
		पूर्ण

		/* Sync reg_cache with the hardware */
		regcache_cache_only(aic3x->regmap, false);
		regcache_sync(aic3x->regmap);

		/* Reग_लिखो paired PLL D रेजिस्टरs in हाल cached sync skipped
		 * writing one of them and thus caused other one also not
		 * being written
		 */
		pll_c = snd_soc_component_पढ़ो(component, AIC3X_PLL_PROGC_REG);
		pll_d = snd_soc_component_पढ़ो(component, AIC3X_PLL_PROGD_REG);
		अगर (pll_c == aic3x_reg[AIC3X_PLL_PROGC_REG].def ||
			pll_d == aic3x_reg[AIC3X_PLL_PROGD_REG].def) अणु
			snd_soc_component_ग_लिखो(component, AIC3X_PLL_PROGC_REG, pll_c);
			snd_soc_component_ग_लिखो(component, AIC3X_PLL_PROGD_REG, pll_d);
		पूर्ण

		/*
		 * Delay is needed to reduce pop-noise after syncing back the
		 * रेजिस्टरs
		 */
		mdelay(50);
	पूर्ण अन्यथा अणु
		/*
		 * Do soft reset to this codec instance in order to clear
		 * possible VDD leakage currents in हाल the supply regulators
		 * reमुख्य on
		 */
		snd_soc_component_ग_लिखो(component, AIC3X_RESET, SOFT_RESET);
		regcache_mark_dirty(aic3x->regmap);
		aic3x->घातer = 0;
		/* HW ग_लिखोs are needless when bias is off */
		regcache_cache_only(aic3x->regmap, true);
		ret = regulator_bulk_disable(ARRAY_SIZE(aic3x->supplies),
					     aic3x->supplies);
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक aic3x_set_bias_level(काष्ठा snd_soc_component *component,
				क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा aic3x_priv *aic3x = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_STANDBY &&
		    aic3x->master) अणु
			/* enable pll */
			snd_soc_component_update_bits(component, AIC3X_PLL_PROGA_REG,
					    PLL_ENABLE, PLL_ENABLE);
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (!aic3x->घातer)
			aic3x_set_घातer(component, 1);
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_PREPARE &&
		    aic3x->master) अणु
			/* disable pll */
			snd_soc_component_update_bits(component, AIC3X_PLL_PROGA_REG,
					    PLL_ENABLE, 0);
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		अगर (aic3x->घातer)
			aic3x_set_घातer(component, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा AIC3X_RATES	SNDRV_PCM_RATE_8000_96000
#घोषणा AIC3X_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			 SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S24_LE | \
			 SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops aic3x_dai_ops = अणु
	.hw_params	= aic3x_hw_params,
	.prepare	= aic3x_prepare,
	.mute_stream	= aic3x_mute,
	.set_sysclk	= aic3x_set_dai_sysclk,
	.set_fmt	= aic3x_set_dai_fmt,
	.set_tdm_slot	= aic3x_set_dai_tdm_slot,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver aic3x_dai = अणु
	.name = "tlv320aic3x-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = AIC3X_RATES,
		.क्रमmats = AIC3X_FORMATS,पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = AIC3X_RATES,
		.क्रमmats = AIC3X_FORMATS,पूर्ण,
	.ops = &aic3x_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल व्योम aic3x_mono_init(काष्ठा snd_soc_component *component)
अणु
	/* DAC to Mono Line Out शेष volume and route to Output mixer */
	snd_soc_component_ग_लिखो(component, DACL1_2_MONOLOPM_VOL, DEFAULT_VOL | ROUTE_ON);
	snd_soc_component_ग_लिखो(component, DACR1_2_MONOLOPM_VOL, DEFAULT_VOL | ROUTE_ON);

	/* unmute all outमाला_दो */
	snd_soc_component_update_bits(component, MONOLOPM_CTRL, UNMUTE, UNMUTE);

	/* PGA to Mono Line Out शेष volume, disconnect from Output Mixer */
	snd_soc_component_ग_लिखो(component, PGAL_2_MONOLOPM_VOL, DEFAULT_VOL);
	snd_soc_component_ग_लिखो(component, PGAR_2_MONOLOPM_VOL, DEFAULT_VOL);

	/* Line2 to Mono Out शेष volume, disconnect from Output Mixer */
	snd_soc_component_ग_लिखो(component, LINE2L_2_MONOLOPM_VOL, DEFAULT_VOL);
	snd_soc_component_ग_लिखो(component, LINE2R_2_MONOLOPM_VOL, DEFAULT_VOL);
पूर्ण

/*
 * initialise the AIC3X driver
 * रेजिस्टर the mixer and dsp पूर्णांकerfaces with the kernel
 */
अटल पूर्णांक aic3x_init(काष्ठा snd_soc_component *component)
अणु
	काष्ठा aic3x_priv *aic3x = snd_soc_component_get_drvdata(component);

	snd_soc_component_ग_लिखो(component, AIC3X_PAGE_SELECT, PAGE0_SELECT);
	snd_soc_component_ग_लिखो(component, AIC3X_RESET, SOFT_RESET);

	/* DAC शेष volume and mute */
	snd_soc_component_ग_लिखो(component, LDAC_VOL, DEFAULT_VOL | MUTE_ON);
	snd_soc_component_ग_लिखो(component, RDAC_VOL, DEFAULT_VOL | MUTE_ON);

	/* DAC to HP शेष volume and route to Output mixer */
	snd_soc_component_ग_लिखो(component, DACL1_2_HPLOUT_VOL, DEFAULT_VOL | ROUTE_ON);
	snd_soc_component_ग_लिखो(component, DACR1_2_HPROUT_VOL, DEFAULT_VOL | ROUTE_ON);
	snd_soc_component_ग_लिखो(component, DACL1_2_HPLCOM_VOL, DEFAULT_VOL | ROUTE_ON);
	snd_soc_component_ग_लिखो(component, DACR1_2_HPRCOM_VOL, DEFAULT_VOL | ROUTE_ON);
	/* DAC to Line Out शेष volume and route to Output mixer */
	snd_soc_component_ग_लिखो(component, DACL1_2_LLOPM_VOL, DEFAULT_VOL | ROUTE_ON);
	snd_soc_component_ग_लिखो(component, DACR1_2_RLOPM_VOL, DEFAULT_VOL | ROUTE_ON);

	/* unmute all outमाला_दो */
	snd_soc_component_update_bits(component, LLOPM_CTRL, UNMUTE, UNMUTE);
	snd_soc_component_update_bits(component, RLOPM_CTRL, UNMUTE, UNMUTE);
	snd_soc_component_update_bits(component, HPLOUT_CTRL, UNMUTE, UNMUTE);
	snd_soc_component_update_bits(component, HPROUT_CTRL, UNMUTE, UNMUTE);
	snd_soc_component_update_bits(component, HPLCOM_CTRL, UNMUTE, UNMUTE);
	snd_soc_component_update_bits(component, HPRCOM_CTRL, UNMUTE, UNMUTE);

	/* ADC शेष volume and unmute */
	snd_soc_component_ग_लिखो(component, LADC_VOL, DEFAULT_GAIN);
	snd_soc_component_ग_लिखो(component, RADC_VOL, DEFAULT_GAIN);
	/* By शेष route Line1 to ADC PGA mixer */
	snd_soc_component_ग_लिखो(component, LINE1L_2_LADC_CTRL, 0x0);
	snd_soc_component_ग_लिखो(component, LINE1R_2_RADC_CTRL, 0x0);

	/* PGA to HP Bypass शेष volume, disconnect from Output Mixer */
	snd_soc_component_ग_लिखो(component, PGAL_2_HPLOUT_VOL, DEFAULT_VOL);
	snd_soc_component_ग_लिखो(component, PGAR_2_HPROUT_VOL, DEFAULT_VOL);
	snd_soc_component_ग_लिखो(component, PGAL_2_HPLCOM_VOL, DEFAULT_VOL);
	snd_soc_component_ग_लिखो(component, PGAR_2_HPRCOM_VOL, DEFAULT_VOL);
	/* PGA to Line Out शेष volume, disconnect from Output Mixer */
	snd_soc_component_ग_लिखो(component, PGAL_2_LLOPM_VOL, DEFAULT_VOL);
	snd_soc_component_ग_लिखो(component, PGAR_2_RLOPM_VOL, DEFAULT_VOL);

	/* On tlv320aic3104, these रेजिस्टरs are reserved and must not be written */
	अगर (aic3x->model != AIC3X_MODEL_3104) अणु
		/* Line2 to HP Bypass शेष volume, disconnect from Output Mixer */
		snd_soc_component_ग_लिखो(component, LINE2L_2_HPLOUT_VOL, DEFAULT_VOL);
		snd_soc_component_ग_लिखो(component, LINE2R_2_HPROUT_VOL, DEFAULT_VOL);
		snd_soc_component_ग_लिखो(component, LINE2L_2_HPLCOM_VOL, DEFAULT_VOL);
		snd_soc_component_ग_लिखो(component, LINE2R_2_HPRCOM_VOL, DEFAULT_VOL);
		/* Line2 Line Out शेष volume, disconnect from Output Mixer */
		snd_soc_component_ग_लिखो(component, LINE2L_2_LLOPM_VOL, DEFAULT_VOL);
		snd_soc_component_ग_लिखो(component, LINE2R_2_RLOPM_VOL, DEFAULT_VOL);
	पूर्ण

	चयन (aic3x->model) अणु
	हाल AIC3X_MODEL_3X:
	हाल AIC3X_MODEL_33:
	हाल AIC3X_MODEL_3106:
		aic3x_mono_init(component);
		अवरोध;
	हाल AIC3X_MODEL_3007:
		snd_soc_component_ग_लिखो(component, CLASSD_CTRL, 0);
		अवरोध;
	पूर्ण

	/*  Output common-mode voltage = 1.5 V */
	snd_soc_component_update_bits(component, HPOUT_SC, HPOUT_SC_OCMV_MASK,
			    aic3x->ocmv << HPOUT_SC_OCMV_SHIFT);

	वापस 0;
पूर्ण

अटल bool aic3x_is_shared_reset(काष्ठा aic3x_priv *aic3x)
अणु
	काष्ठा aic3x_priv *a;

	list_क्रम_each_entry(a, &reset_list, list) अणु
		अगर (gpio_is_valid(aic3x->gpio_reset) &&
		    aic3x->gpio_reset == a->gpio_reset)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक aic3x_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा aic3x_priv *aic3x = snd_soc_component_get_drvdata(component);
	पूर्णांक ret, i;

	aic3x->component = component;

	क्रम (i = 0; i < ARRAY_SIZE(aic3x->supplies); i++) अणु
		aic3x->disable_nb[i].nb.notअगरier_call = aic3x_regulator_event;
		aic3x->disable_nb[i].aic3x = aic3x;
		ret = devm_regulator_रेजिस्टर_notअगरier(
						aic3x->supplies[i].consumer,
						&aic3x->disable_nb[i].nb);
		अगर (ret) अणु
			dev_err(component->dev,
				"Failed to request regulator notifier: %d\n",
				 ret);
			वापस ret;
		पूर्ण
	पूर्ण

	regcache_mark_dirty(aic3x->regmap);
	aic3x_init(component);

	अगर (aic3x->setup) अणु
		अगर (aic3x->model != AIC3X_MODEL_3104) अणु
			/* setup GPIO functions */
			snd_soc_component_ग_लिखो(component, AIC3X_GPIO1_REG,
				      (aic3x->setup->gpio_func[0] & 0xf) << 4);
			snd_soc_component_ग_लिखो(component, AIC3X_GPIO2_REG,
				      (aic3x->setup->gpio_func[1] & 0xf) << 4);
		पूर्ण अन्यथा अणु
			dev_warn(component->dev, "GPIO functionality is not supported on tlv320aic3104\n");
		पूर्ण
	पूर्ण

	चयन (aic3x->model) अणु
	हाल AIC3X_MODEL_3X:
	हाल AIC3X_MODEL_33:
	हाल AIC3X_MODEL_3106:
		snd_soc_add_component_controls(component, aic3x_extra_snd_controls,
				ARRAY_SIZE(aic3x_extra_snd_controls));
		snd_soc_add_component_controls(component, aic3x_mono_controls,
				ARRAY_SIZE(aic3x_mono_controls));
		अवरोध;
	हाल AIC3X_MODEL_3007:
		snd_soc_add_component_controls(component, aic3x_extra_snd_controls,
				ARRAY_SIZE(aic3x_extra_snd_controls));
		snd_soc_add_component_controls(component,
				&aic3x_classd_amp_gain_ctrl, 1);
		अवरोध;
	हाल AIC3X_MODEL_3104:
		अवरोध;
	पूर्ण

	/* set mic bias voltage */
	चयन (aic3x->micbias_vg) अणु
	हाल AIC3X_MICBIAS_2_0V:
	हाल AIC3X_MICBIAS_2_5V:
	हाल AIC3X_MICBIAS_AVDDV:
		snd_soc_component_update_bits(component, MICBIAS_CTRL,
				    MICBIAS_LEVEL_MASK,
				    (aic3x->micbias_vg) << MICBIAS_LEVEL_SHIFT);
		अवरोध;
	हाल AIC3X_MICBIAS_OFF:
		/*
		 * noting to करो. target won't enter here. This is just to aव्योम
		 * compile समय warning "warning: क्रमागतeration value
		 * 'AIC3X_MICBIAS_OFF' not handled in चयन"
		 */
		अवरोध;
	पूर्ण

	aic3x_add_widमाला_लो(component);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_aic3x = अणु
	.set_bias_level		= aic3x_set_bias_level,
	.probe			= aic3x_component_probe,
	.controls		= aic3x_snd_controls,
	.num_controls		= ARRAY_SIZE(aic3x_snd_controls),
	.dapm_widमाला_लो		= aic3x_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(aic3x_dapm_widमाला_लो),
	.dapm_routes		= पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(पूर्णांकercon),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल व्योम aic3x_configure_ocmv(काष्ठा device *dev, काष्ठा aic3x_priv *aic3x)
अणु
	काष्ठा device_node *np = dev->of_node;
	u32 value;
	पूर्णांक dvdd, avdd;

	अगर (np && !of_property_पढ़ो_u32(np, "ai3x-ocmv", &value)) अणु
		/* OCMV setting is क्रमced by DT */
		अगर (value <= 3) अणु
			aic3x->ocmv = value;
			वापस;
		पूर्ण
	पूर्ण

	dvdd = regulator_get_voltage(aic3x->supplies[1].consumer);
	avdd = regulator_get_voltage(aic3x->supplies[2].consumer);

	अगर (avdd > 3600000 || dvdd > 1950000) अणु
		dev_warn(dev,
			 "Too high supply voltage(s) AVDD: %d, DVDD: %d\n",
			 avdd, dvdd);
	पूर्ण अन्यथा अगर (avdd == 3600000 && dvdd == 1950000) अणु
		aic3x->ocmv = HPOUT_SC_OCMV_1_8V;
	पूर्ण अन्यथा अगर (avdd > 3300000 && dvdd > 1800000) अणु
		aic3x->ocmv = HPOUT_SC_OCMV_1_65V;
	पूर्ण अन्यथा अगर (avdd > 3000000 && dvdd > 1650000) अणु
		aic3x->ocmv = HPOUT_SC_OCMV_1_5V;
	पूर्ण अन्यथा अगर (avdd >= 2700000 && dvdd >= 1525000) अणु
		aic3x->ocmv = HPOUT_SC_OCMV_1_35V;
	पूर्ण अन्यथा अणु
		dev_warn(dev,
			 "Invalid supply voltage(s) AVDD: %d, DVDD: %d\n",
			 avdd, dvdd);
	पूर्ण
पूर्ण


अटल स्थिर काष्ठा reg_sequence aic3007_class_d[] = अणु
	/* Class-D speaker driver init; datasheet p. 46 */
	अणु AIC3X_PAGE_SELECT, 0x0D पूर्ण,
	अणु 0xD, 0x0D पूर्ण,
	अणु 0x8, 0x5C पूर्ण,
	अणु 0x8, 0x5D पूर्ण,
	अणु 0x8, 0x5C पूर्ण,
	अणु AIC3X_PAGE_SELECT, 0x00 पूर्ण,
पूर्ण;

पूर्णांक aic3x_probe(काष्ठा device *dev, काष्ठा regmap *regmap, kernel_uदीर्घ_t driver_data)
अणु
	काष्ठा aic3x_pdata *pdata = dev->platक्रमm_data;
	काष्ठा aic3x_priv *aic3x;
	काष्ठा aic3x_setup_data *ai3x_setup;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret, i;
	u32 value;

	aic3x = devm_kzalloc(dev, माप(काष्ठा aic3x_priv), GFP_KERNEL);
	अगर (!aic3x)
		वापस -ENOMEM;

	aic3x->regmap = regmap;
	अगर (IS_ERR(aic3x->regmap)) अणु
		ret = PTR_ERR(aic3x->regmap);
		वापस ret;
	पूर्ण

	regcache_cache_only(aic3x->regmap, true);

	dev_set_drvdata(dev, aic3x);
	अगर (pdata) अणु
		aic3x->gpio_reset = pdata->gpio_reset;
		aic3x->setup = pdata->setup;
		aic3x->micbias_vg = pdata->micbias_vg;
	पूर्ण अन्यथा अगर (np) अणु
		ai3x_setup = devm_kzalloc(dev, माप(*ai3x_setup), GFP_KERNEL);
		अगर (!ai3x_setup)
			वापस -ENOMEM;

		ret = of_get_named_gpio(np, "reset-gpios", 0);
		अगर (ret >= 0) अणु
			aic3x->gpio_reset = ret;
		पूर्ण अन्यथा अणु
			ret = of_get_named_gpio(np, "gpio-reset", 0);
			अगर (ret > 0) अणु
				dev_warn(dev, "Using deprecated property \"gpio-reset\", please update your DT");
				aic3x->gpio_reset = ret;
			पूर्ण अन्यथा अणु
				aic3x->gpio_reset = -1;
			पूर्ण
		पूर्ण

		अगर (of_property_पढ़ो_u32_array(np, "ai3x-gpio-func",
					ai3x_setup->gpio_func, 2) >= 0) अणु
			aic3x->setup = ai3x_setup;
		पूर्ण

		अगर (!of_property_पढ़ो_u32(np, "ai3x-micbias-vg", &value)) अणु
			चयन (value) अणु
			हाल 1 :
				aic3x->micbias_vg = AIC3X_MICBIAS_2_0V;
				अवरोध;
			हाल 2 :
				aic3x->micbias_vg = AIC3X_MICBIAS_2_5V;
				अवरोध;
			हाल 3 :
				aic3x->micbias_vg = AIC3X_MICBIAS_AVDDV;
				अवरोध;
			शेष :
				aic3x->micbias_vg = AIC3X_MICBIAS_OFF;
				dev_err(dev, "Unsuitable MicBias voltage "
							"found in DT\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			aic3x->micbias_vg = AIC3X_MICBIAS_OFF;
		पूर्ण

	पूर्ण अन्यथा अणु
		aic3x->gpio_reset = -1;
	पूर्ण

	aic3x->model = driver_data;

	अगर (gpio_is_valid(aic3x->gpio_reset) &&
	    !aic3x_is_shared_reset(aic3x)) अणु
		ret = gpio_request(aic3x->gpio_reset, "tlv320aic3x reset");
		अगर (ret != 0)
			जाओ err;
		gpio_direction_output(aic3x->gpio_reset, 0);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(aic3x->supplies); i++)
		aic3x->supplies[i].supply = aic3x_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(aic3x->supplies),
				      aic3x->supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to request supplies: %d\n", ret);
		जाओ err_gpio;
	पूर्ण

	aic3x_configure_ocmv(dev, aic3x);

	अगर (aic3x->model == AIC3X_MODEL_3007) अणु
		ret = regmap_रेजिस्टर_patch(aic3x->regmap, aic3007_class_d,
					    ARRAY_SIZE(aic3007_class_d));
		अगर (ret != 0)
			dev_err(dev, "Failed to init class D: %d\n",
				ret);
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(dev, &soc_component_dev_aic3x, &aic3x_dai, 1);

	अगर (ret != 0)
		जाओ err_gpio;

	INIT_LIST_HEAD(&aic3x->list);
	list_add(&aic3x->list, &reset_list);

	वापस 0;

err_gpio:
	अगर (gpio_is_valid(aic3x->gpio_reset) &&
	    !aic3x_is_shared_reset(aic3x))
		gpio_मुक्त(aic3x->gpio_reset);
err:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(aic3x_probe);

पूर्णांक aic3x_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा aic3x_priv *aic3x = dev_get_drvdata(dev);

	list_del(&aic3x->list);

	अगर (gpio_is_valid(aic3x->gpio_reset) &&
	    !aic3x_is_shared_reset(aic3x)) अणु
		gpio_set_value(aic3x->gpio_reset, 0);
		gpio_मुक्त(aic3x->gpio_reset);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(aic3x_हटाओ);

MODULE_DESCRIPTION("ASoC TLV320AIC3X codec driver");
MODULE_AUTHOR("Vladimir Barinov");
MODULE_LICENSE("GPL");
