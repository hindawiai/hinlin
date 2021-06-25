<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rt5631.c  --  RT5631 ALSA Soc Audio driver
 *
 * Copyright 2011 Realtek Microelectronics
 *
 * Author: flove <flove@realtek.com>
 *
 * Based on WM8753.c
 */
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "rt5631.h"

काष्ठा rt5631_priv अणु
	काष्ठा regmap *regmap;
	पूर्णांक codec_version;
	पूर्णांक master;
	पूर्णांक sysclk;
	पूर्णांक rx_rate;
	पूर्णांक bclk_rate;
	पूर्णांक dmic_used_flag;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष rt5631_reg[] = अणु
	अणु RT5631_SPK_OUT_VOL, 0x8888 पूर्ण,
	अणु RT5631_HP_OUT_VOL, 0x8080 पूर्ण,
	अणु RT5631_MONO_AXO_1_2_VOL, 0xa080 पूर्ण,
	अणु RT5631_AUX_IN_VOL, 0x0808 पूर्ण,
	अणु RT5631_ADC_REC_MIXER, 0xf0f0 पूर्ण,
	अणु RT5631_VDAC_DIG_VOL, 0x0010 पूर्ण,
	अणु RT5631_OUTMIXER_L_CTRL, 0xffc0 पूर्ण,
	अणु RT5631_OUTMIXER_R_CTRL, 0xffc0 पूर्ण,
	अणु RT5631_AXO1MIXER_CTRL, 0x88c0 पूर्ण,
	अणु RT5631_AXO2MIXER_CTRL, 0x88c0 पूर्ण,
	अणु RT5631_DIG_MIC_CTRL, 0x3000 पूर्ण,
	अणु RT5631_MONO_INPUT_VOL, 0x8808 पूर्ण,
	अणु RT5631_SPK_MIXER_CTRL, 0xf8f8 पूर्ण,
	अणु RT5631_SPK_MONO_OUT_CTRL, 0xfc00 पूर्ण,
	अणु RT5631_SPK_MONO_HP_OUT_CTRL, 0x4440 पूर्ण,
	अणु RT5631_SDP_CTRL, 0x8000 पूर्ण,
	अणु RT5631_MONO_SDP_CTRL, 0x8000 पूर्ण,
	अणु RT5631_STEREO_AD_DA_CLK_CTRL, 0x2010 पूर्ण,
	अणु RT5631_GEN_PUR_CTRL_REG, 0x0e00 पूर्ण,
	अणु RT5631_INT_ST_IRQ_CTRL_2, 0x071a पूर्ण,
	अणु RT5631_MISC_CTRL, 0x2040 पूर्ण,
	अणु RT5631_DEPOP_FUN_CTRL_2, 0x8000 पूर्ण,
	अणु RT5631_SOFT_VOL_CTRL, 0x07e0 पूर्ण,
	अणु RT5631_ALC_CTRL_1, 0x0206 पूर्ण,
	अणु RT5631_ALC_CTRL_3, 0x2000 पूर्ण,
	अणु RT5631_PSEUDO_SPATL_CTRL, 0x0553 पूर्ण,
पूर्ण;

/*
 * rt5631_ग_लिखो_index - ग_लिखो index रेजिस्टर of 2nd layer
 */
अटल व्योम rt5631_ग_लिखो_index(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
	snd_soc_component_ग_लिखो(component, RT5631_INDEX_ADD, reg);
	snd_soc_component_ग_लिखो(component, RT5631_INDEX_DATA, value);
पूर्ण

/*
 * rt5631_पढ़ो_index - पढ़ो index रेजिस्टर of 2nd layer
 */
अटल अचिन्हित पूर्णांक rt5631_पढ़ो_index(काष्ठा snd_soc_component *component,
				अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक value;

	snd_soc_component_ग_लिखो(component, RT5631_INDEX_ADD, reg);
	value = snd_soc_component_पढ़ो(component, RT5631_INDEX_DATA);

	वापस value;
पूर्ण

अटल पूर्णांक rt5631_reset(काष्ठा snd_soc_component *component)
अणु
	वापस snd_soc_component_ग_लिखो(component, RT5631_RESET, 0);
पूर्ण

अटल bool rt5631_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT5631_RESET:
	हाल RT5631_INT_ST_IRQ_CTRL_2:
	हाल RT5631_INDEX_ADD:
	हाल RT5631_INDEX_DATA:
	हाल RT5631_EQ_CTRL:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt5631_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT5631_RESET:
	हाल RT5631_SPK_OUT_VOL:
	हाल RT5631_HP_OUT_VOL:
	हाल RT5631_MONO_AXO_1_2_VOL:
	हाल RT5631_AUX_IN_VOL:
	हाल RT5631_STEREO_DAC_VOL_1:
	हाल RT5631_MIC_CTRL_1:
	हाल RT5631_STEREO_DAC_VOL_2:
	हाल RT5631_ADC_CTRL_1:
	हाल RT5631_ADC_REC_MIXER:
	हाल RT5631_ADC_CTRL_2:
	हाल RT5631_VDAC_DIG_VOL:
	हाल RT5631_OUTMIXER_L_CTRL:
	हाल RT5631_OUTMIXER_R_CTRL:
	हाल RT5631_AXO1MIXER_CTRL:
	हाल RT5631_AXO2MIXER_CTRL:
	हाल RT5631_MIC_CTRL_2:
	हाल RT5631_DIG_MIC_CTRL:
	हाल RT5631_MONO_INPUT_VOL:
	हाल RT5631_SPK_MIXER_CTRL:
	हाल RT5631_SPK_MONO_OUT_CTRL:
	हाल RT5631_SPK_MONO_HP_OUT_CTRL:
	हाल RT5631_SDP_CTRL:
	हाल RT5631_MONO_SDP_CTRL:
	हाल RT5631_STEREO_AD_DA_CLK_CTRL:
	हाल RT5631_PWR_MANAG_ADD1:
	हाल RT5631_PWR_MANAG_ADD2:
	हाल RT5631_PWR_MANAG_ADD3:
	हाल RT5631_PWR_MANAG_ADD4:
	हाल RT5631_GEN_PUR_CTRL_REG:
	हाल RT5631_GLOBAL_CLK_CTRL:
	हाल RT5631_PLL_CTRL:
	हाल RT5631_INT_ST_IRQ_CTRL_1:
	हाल RT5631_INT_ST_IRQ_CTRL_2:
	हाल RT5631_GPIO_CTRL:
	हाल RT5631_MISC_CTRL:
	हाल RT5631_DEPOP_FUN_CTRL_1:
	हाल RT5631_DEPOP_FUN_CTRL_2:
	हाल RT5631_JACK_DET_CTRL:
	हाल RT5631_SOFT_VOL_CTRL:
	हाल RT5631_ALC_CTRL_1:
	हाल RT5631_ALC_CTRL_2:
	हाल RT5631_ALC_CTRL_3:
	हाल RT5631_PSEUDO_SPATL_CTRL:
	हाल RT5631_INDEX_ADD:
	हाल RT5631_INDEX_DATA:
	हाल RT5631_EQ_CTRL:
	हाल RT5631_VENDOR_ID:
	हाल RT5631_VENDOR_ID1:
	हाल RT5631_VENDOR_ID2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(out_vol_tlv, -4650, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(dac_vol_tlv, -95625, 375, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(in_vol_tlv, -3450, 150, 0);
/* अणु0, +20, +24, +30, +35, +40, +44, +50, +52पूर्णdB */
अटल स्थिर DECLARE_TLV_DB_RANGE(mic_bst_tlv,
	0, 0, TLV_DB_SCALE_ITEM(0, 0, 0),
	1, 1, TLV_DB_SCALE_ITEM(2000, 0, 0),
	2, 2, TLV_DB_SCALE_ITEM(2400, 0, 0),
	3, 5, TLV_DB_SCALE_ITEM(3000, 500, 0),
	6, 6, TLV_DB_SCALE_ITEM(4400, 0, 0),
	7, 7, TLV_DB_SCALE_ITEM(5000, 0, 0),
	8, 8, TLV_DB_SCALE_ITEM(5200, 0, 0)
);

अटल पूर्णांक rt5631_dmic_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा rt5631_priv *rt5631 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = rt5631->dmic_used_flag;

	वापस 0;
पूर्ण

अटल पूर्णांक rt5631_dmic_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा rt5631_priv *rt5631 = snd_soc_component_get_drvdata(component);

	rt5631->dmic_used_flag = ucontrol->value.पूर्णांकeger.value[0];
	वापस 0;
पूर्ण

/* MIC Input Type */
अटल स्थिर अक्षर *rt5631_input_mode[] = अणु
	"Single ended", "Differential"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5631_mic1_mode_क्रमागत, RT5631_MIC_CTRL_1,
			    RT5631_MIC1_DIFF_INPUT_SHIFT, rt5631_input_mode);

अटल SOC_ENUM_SINGLE_DECL(rt5631_mic2_mode_क्रमागत, RT5631_MIC_CTRL_1,
			    RT5631_MIC2_DIFF_INPUT_SHIFT, rt5631_input_mode);

/* MONO Input Type */
अटल SOC_ENUM_SINGLE_DECL(rt5631_monoin_mode_क्रमागत, RT5631_MONO_INPUT_VOL,
			    RT5631_MONO_DIFF_INPUT_SHIFT, rt5631_input_mode);

/* SPK Ratio Gain Control */
अटल स्थिर अक्षर *rt5631_spk_ratio[] = अणु"1.00x", "1.09x", "1.27x", "1.44x",
			"1.56x", "1.68x", "1.99x", "2.34x"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5631_spk_ratio_क्रमागत, RT5631_GEN_PUR_CTRL_REG,
			    RT5631_SPK_AMP_RATIO_CTRL_SHIFT, rt5631_spk_ratio);

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_snd_controls[] = अणु
	/* MIC */
	SOC_ENUM("MIC1 Mode Control",  rt5631_mic1_mode_क्रमागत),
	SOC_SINGLE_TLV("MIC1 Boost Volume", RT5631_MIC_CTRL_2,
		RT5631_MIC1_BOOST_SHIFT, 8, 0, mic_bst_tlv),
	SOC_ENUM("MIC2 Mode Control", rt5631_mic2_mode_क्रमागत),
	SOC_SINGLE_TLV("MIC2 Boost Volume", RT5631_MIC_CTRL_2,
		RT5631_MIC2_BOOST_SHIFT, 8, 0, mic_bst_tlv),
	/* MONO IN */
	SOC_ENUM("MONOIN Mode Control", rt5631_monoin_mode_क्रमागत),
	SOC_DOUBLE_TLV("MONOIN_RX Capture Volume", RT5631_MONO_INPUT_VOL,
			RT5631_L_VOL_SHIFT, RT5631_R_VOL_SHIFT,
			RT5631_VOL_MASK, 1, in_vol_tlv),
	/* AXI */
	SOC_DOUBLE_TLV("AXI Capture Volume", RT5631_AUX_IN_VOL,
			RT5631_L_VOL_SHIFT, RT5631_R_VOL_SHIFT,
			RT5631_VOL_MASK, 1, in_vol_tlv),
	/* DAC */
	SOC_DOUBLE_TLV("PCM Playback Volume", RT5631_STEREO_DAC_VOL_2,
			RT5631_L_VOL_SHIFT, RT5631_R_VOL_SHIFT,
			RT5631_DAC_VOL_MASK, 1, dac_vol_tlv),
	SOC_DOUBLE("PCM Playback Switch", RT5631_STEREO_DAC_VOL_1,
			RT5631_L_MUTE_SHIFT, RT5631_R_MUTE_SHIFT, 1, 1),
	/* AXO */
	SOC_SINGLE("AXO1 Playback Switch", RT5631_MONO_AXO_1_2_VOL,
				RT5631_L_MUTE_SHIFT, 1, 1),
	SOC_SINGLE("AXO2 Playback Switch", RT5631_MONO_AXO_1_2_VOL,
				RT5631_R_VOL_SHIFT, 1, 1),
	/* OUTVOL */
	SOC_DOUBLE("OUTVOL Channel Switch", RT5631_SPK_OUT_VOL,
		RT5631_L_EN_SHIFT, RT5631_R_EN_SHIFT, 1, 0),

	/* SPK */
	SOC_DOUBLE("Speaker Playback Switch", RT5631_SPK_OUT_VOL,
		RT5631_L_MUTE_SHIFT, RT5631_R_MUTE_SHIFT, 1, 1),
	SOC_DOUBLE_TLV("Speaker Playback Volume", RT5631_SPK_OUT_VOL,
		RT5631_L_VOL_SHIFT, RT5631_R_VOL_SHIFT, 39, 1, out_vol_tlv),
	/* MONO OUT */
	SOC_SINGLE("MONO Playback Switch", RT5631_MONO_AXO_1_2_VOL,
				RT5631_MUTE_MONO_SHIFT, 1, 1),
	/* HP */
	SOC_DOUBLE("HP Playback Switch", RT5631_HP_OUT_VOL,
		RT5631_L_MUTE_SHIFT, RT5631_R_MUTE_SHIFT, 1, 1),
	SOC_DOUBLE_TLV("HP Playback Volume", RT5631_HP_OUT_VOL,
		RT5631_L_VOL_SHIFT, RT5631_R_VOL_SHIFT,
		RT5631_VOL_MASK, 1, out_vol_tlv),
	/* DMIC */
	SOC_SINGLE_EXT("DMIC Switch", 0, 0, 1, 0,
		rt5631_dmic_get, rt5631_dmic_put),
	SOC_DOUBLE("DMIC Capture Switch", RT5631_DIG_MIC_CTRL,
		RT5631_DMIC_L_CH_MUTE_SHIFT,
		RT5631_DMIC_R_CH_MUTE_SHIFT, 1, 1),

	/* SPK Ratio Gain Control */
	SOC_ENUM("SPK Ratio Control", rt5631_spk_ratio_क्रमागत),
पूर्ण;

अटल पूर्णांक check_sysclk1_source(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	अचिन्हित पूर्णांक reg;

	reg = snd_soc_component_पढ़ो(component, RT5631_GLOBAL_CLK_CTRL);
	वापस reg & RT5631_SYSCLK_SOUR_SEL_PLL;
पूर्ण

अटल पूर्णांक check_dmic_used(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	काष्ठा rt5631_priv *rt5631 = snd_soc_component_get_drvdata(component);
	वापस rt5631->dmic_used_flag;
पूर्ण

अटल पूर्णांक check_dacl_to_ouपंचांगixl(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	अचिन्हित पूर्णांक reg;

	reg = snd_soc_component_पढ़ो(component, RT5631_OUTMIXER_L_CTRL);
	वापस !(reg & RT5631_M_DAC_L_TO_OUTMIXER_L);
पूर्ण

अटल पूर्णांक check_dacr_to_ouपंचांगixr(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	अचिन्हित पूर्णांक reg;

	reg = snd_soc_component_पढ़ो(component, RT5631_OUTMIXER_R_CTRL);
	वापस !(reg & RT5631_M_DAC_R_TO_OUTMIXER_R);
पूर्ण

अटल पूर्णांक check_dacl_to_spkmixl(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	अचिन्हित पूर्णांक reg;

	reg = snd_soc_component_पढ़ो(component, RT5631_SPK_MIXER_CTRL);
	वापस !(reg & RT5631_M_DAC_L_TO_SPKMIXER_L);
पूर्ण

अटल पूर्णांक check_dacr_to_spkmixr(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	अचिन्हित पूर्णांक reg;

	reg = snd_soc_component_पढ़ो(component, RT5631_SPK_MIXER_CTRL);
	वापस !(reg & RT5631_M_DAC_R_TO_SPKMIXER_R);
पूर्ण

अटल पूर्णांक check_adcl_select(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	अचिन्हित पूर्णांक reg;

	reg = snd_soc_component_पढ़ो(component, RT5631_ADC_REC_MIXER);
	वापस !(reg & RT5631_M_MIC1_TO_RECMIXER_L);
पूर्ण

अटल पूर्णांक check_adcr_select(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	अचिन्हित पूर्णांक reg;

	reg = snd_soc_component_पढ़ो(component, RT5631_ADC_REC_MIXER);
	वापस !(reg & RT5631_M_MIC2_TO_RECMIXER_R);
पूर्ण

/**
 * onebit_depop_घातer_stage - स्वतः depop in घातer stage.
 * @component: ASoC component
 * @enable: घातer on/off
 *
 * When घातer on/off headphone, the depop sequence is करोne by hardware.
 */
अटल व्योम onebit_depop_घातer_stage(काष्ठा snd_soc_component *component, पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक soft_vol, hp_zc;

	/* enable one-bit depop function */
	snd_soc_component_update_bits(component, RT5631_DEPOP_FUN_CTRL_2,
				RT5631_EN_ONE_BIT_DEPOP, 0);

	/* keep soft volume and zero crossing setting */
	soft_vol = snd_soc_component_पढ़ो(component, RT5631_SOFT_VOL_CTRL);
	snd_soc_component_ग_लिखो(component, RT5631_SOFT_VOL_CTRL, 0);
	hp_zc = snd_soc_component_पढ़ो(component, RT5631_INT_ST_IRQ_CTRL_2);
	snd_soc_component_ग_लिखो(component, RT5631_INT_ST_IRQ_CTRL_2, hp_zc & 0xf7ff);
	अगर (enable) अणु
		/* config one-bit depop parameter */
		rt5631_ग_लिखो_index(component, RT5631_TEST_MODE_CTRL, 0x84c0);
		rt5631_ग_लिखो_index(component, RT5631_SPK_INTL_CTRL, 0x309f);
		rt5631_ग_लिखो_index(component, RT5631_CP_INTL_REG2, 0x6530);
		/* घातer on capless block */
		snd_soc_component_ग_लिखो(component, RT5631_DEPOP_FUN_CTRL_2,
				RT5631_EN_CAP_FREE_DEPOP);
	पूर्ण अन्यथा अणु
		/* घातer off capless block */
		snd_soc_component_ग_लिखो(component, RT5631_DEPOP_FUN_CTRL_2, 0);
		msleep(100);
	पूर्ण

	/* recover soft volume and zero crossing setting */
	snd_soc_component_ग_लिखो(component, RT5631_SOFT_VOL_CTRL, soft_vol);
	snd_soc_component_ग_लिखो(component, RT5631_INT_ST_IRQ_CTRL_2, hp_zc);
पूर्ण

/**
 * onebit_depop_mute_stage - स्वतः depop in mute stage.
 * @component: ASoC component
 * @enable: mute/unmute
 *
 * When mute/unmute headphone, the depop sequence is करोne by hardware.
 */
अटल व्योम onebit_depop_mute_stage(काष्ठा snd_soc_component *component, पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक soft_vol, hp_zc;

	/* enable one-bit depop function */
	snd_soc_component_update_bits(component, RT5631_DEPOP_FUN_CTRL_2,
				RT5631_EN_ONE_BIT_DEPOP, 0);

	/* keep soft volume and zero crossing setting */
	soft_vol = snd_soc_component_पढ़ो(component, RT5631_SOFT_VOL_CTRL);
	snd_soc_component_ग_लिखो(component, RT5631_SOFT_VOL_CTRL, 0);
	hp_zc = snd_soc_component_पढ़ो(component, RT5631_INT_ST_IRQ_CTRL_2);
	snd_soc_component_ग_लिखो(component, RT5631_INT_ST_IRQ_CTRL_2, hp_zc & 0xf7ff);
	अगर (enable) अणु
		schedule_समयout_unपूर्णांकerruptible(msecs_to_jअगरfies(10));
		/* config one-bit depop parameter */
		rt5631_ग_लिखो_index(component, RT5631_SPK_INTL_CTRL, 0x307f);
		snd_soc_component_update_bits(component, RT5631_HP_OUT_VOL,
				RT5631_L_MUTE | RT5631_R_MUTE, 0);
		msleep(300);
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component, RT5631_HP_OUT_VOL,
			RT5631_L_MUTE | RT5631_R_MUTE,
			RT5631_L_MUTE | RT5631_R_MUTE);
		msleep(100);
	पूर्ण

	/* recover soft volume and zero crossing setting */
	snd_soc_component_ग_लिखो(component, RT5631_SOFT_VOL_CTRL, soft_vol);
	snd_soc_component_ग_लिखो(component, RT5631_INT_ST_IRQ_CTRL_2, hp_zc);
पूर्ण

/**
 * depop_seq_घातer_stage - step by step depop sequence in घातer stage.
 * @component: ASoC component
 * @enable: घातer on/off
 *
 * When घातer on/off headphone, the depop sequence is करोne in step by step.
 */
अटल व्योम depop_seq_घातer_stage(काष्ठा snd_soc_component *component, पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक soft_vol, hp_zc;

	/* depop control by रेजिस्टर */
	snd_soc_component_update_bits(component, RT5631_DEPOP_FUN_CTRL_2,
		RT5631_EN_ONE_BIT_DEPOP, RT5631_EN_ONE_BIT_DEPOP);

	/* keep soft volume and zero crossing setting */
	soft_vol = snd_soc_component_पढ़ो(component, RT5631_SOFT_VOL_CTRL);
	snd_soc_component_ग_लिखो(component, RT5631_SOFT_VOL_CTRL, 0);
	hp_zc = snd_soc_component_पढ़ो(component, RT5631_INT_ST_IRQ_CTRL_2);
	snd_soc_component_ग_लिखो(component, RT5631_INT_ST_IRQ_CTRL_2, hp_zc & 0xf7ff);
	अगर (enable) अणु
		/* config depop sequence parameter */
		rt5631_ग_लिखो_index(component, RT5631_SPK_INTL_CTRL, 0x303e);

		/* घातer on headphone and अक्षरge pump */
		snd_soc_component_update_bits(component, RT5631_PWR_MANAG_ADD3,
			RT5631_PWR_CHARGE_PUMP | RT5631_PWR_HP_L_AMP |
			RT5631_PWR_HP_R_AMP,
			RT5631_PWR_CHARGE_PUMP | RT5631_PWR_HP_L_AMP |
			RT5631_PWR_HP_R_AMP);

		/* घातer on soft generator and depop mode2 */
		snd_soc_component_ग_लिखो(component, RT5631_DEPOP_FUN_CTRL_1,
			RT5631_POW_ON_SOFT_GEN | RT5631_EN_DEPOP2_FOR_HP);
		msleep(100);

		/* stop depop mode */
		snd_soc_component_update_bits(component, RT5631_PWR_MANAG_ADD3,
			RT5631_PWR_HP_DEPOP_DIS, RT5631_PWR_HP_DEPOP_DIS);
	पूर्ण अन्यथा अणु
		/* config depop sequence parameter */
		rt5631_ग_लिखो_index(component, RT5631_SPK_INTL_CTRL, 0x303F);
		snd_soc_component_ग_लिखो(component, RT5631_DEPOP_FUN_CTRL_1,
			RT5631_POW_ON_SOFT_GEN | RT5631_EN_MUTE_UNMUTE_DEPOP |
			RT5631_PD_HPAMP_L_ST_UP | RT5631_PD_HPAMP_R_ST_UP);
		msleep(75);
		snd_soc_component_ग_लिखो(component, RT5631_DEPOP_FUN_CTRL_1,
			RT5631_POW_ON_SOFT_GEN | RT5631_PD_HPAMP_L_ST_UP |
			RT5631_PD_HPAMP_R_ST_UP);

		/* start depop mode */
		snd_soc_component_update_bits(component, RT5631_PWR_MANAG_ADD3,
				RT5631_PWR_HP_DEPOP_DIS, 0);

		/* config depop sequence parameter */
		snd_soc_component_ग_लिखो(component, RT5631_DEPOP_FUN_CTRL_1,
			RT5631_POW_ON_SOFT_GEN | RT5631_EN_DEPOP2_FOR_HP |
			RT5631_PD_HPAMP_L_ST_UP | RT5631_PD_HPAMP_R_ST_UP);
		msleep(80);
		snd_soc_component_ग_लिखो(component, RT5631_DEPOP_FUN_CTRL_1,
			RT5631_POW_ON_SOFT_GEN);

		/* घातer करोwn headphone and अक्षरge pump */
		snd_soc_component_update_bits(component, RT5631_PWR_MANAG_ADD3,
			RT5631_PWR_CHARGE_PUMP | RT5631_PWR_HP_L_AMP |
			RT5631_PWR_HP_R_AMP, 0);
	पूर्ण

	/* recover soft volume and zero crossing setting */
	snd_soc_component_ग_लिखो(component, RT5631_SOFT_VOL_CTRL, soft_vol);
	snd_soc_component_ग_लिखो(component, RT5631_INT_ST_IRQ_CTRL_2, hp_zc);
पूर्ण

/**
 * depop_seq_mute_stage - step by step depop sequence in mute stage.
 * @component: ASoC component
 * @enable: mute/unmute
 *
 * When mute/unmute headphone, the depop sequence is करोne in step by step.
 */
अटल व्योम depop_seq_mute_stage(काष्ठा snd_soc_component *component, पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक soft_vol, hp_zc;

	/* depop control by रेजिस्टर */
	snd_soc_component_update_bits(component, RT5631_DEPOP_FUN_CTRL_2,
		RT5631_EN_ONE_BIT_DEPOP, RT5631_EN_ONE_BIT_DEPOP);

	/* keep soft volume and zero crossing setting */
	soft_vol = snd_soc_component_पढ़ो(component, RT5631_SOFT_VOL_CTRL);
	snd_soc_component_ग_लिखो(component, RT5631_SOFT_VOL_CTRL, 0);
	hp_zc = snd_soc_component_पढ़ो(component, RT5631_INT_ST_IRQ_CTRL_2);
	snd_soc_component_ग_लिखो(component, RT5631_INT_ST_IRQ_CTRL_2, hp_zc & 0xf7ff);
	अगर (enable) अणु
		schedule_समयout_unपूर्णांकerruptible(msecs_to_jअगरfies(10));

		/* config depop sequence parameter */
		rt5631_ग_लिखो_index(component, RT5631_SPK_INTL_CTRL, 0x302f);
		snd_soc_component_ग_लिखो(component, RT5631_DEPOP_FUN_CTRL_1,
			RT5631_POW_ON_SOFT_GEN | RT5631_EN_MUTE_UNMUTE_DEPOP |
			RT5631_EN_HP_R_M_UN_MUTE_DEPOP |
			RT5631_EN_HP_L_M_UN_MUTE_DEPOP);

		snd_soc_component_update_bits(component, RT5631_HP_OUT_VOL,
				RT5631_L_MUTE | RT5631_R_MUTE, 0);
		msleep(160);
	पूर्ण अन्यथा अणु
		/* config depop sequence parameter */
		rt5631_ग_लिखो_index(component, RT5631_SPK_INTL_CTRL, 0x302f);
		snd_soc_component_ग_लिखो(component, RT5631_DEPOP_FUN_CTRL_1,
			RT5631_POW_ON_SOFT_GEN | RT5631_EN_MUTE_UNMUTE_DEPOP |
			RT5631_EN_HP_R_M_UN_MUTE_DEPOP |
			RT5631_EN_HP_L_M_UN_MUTE_DEPOP);

		snd_soc_component_update_bits(component, RT5631_HP_OUT_VOL,
			RT5631_L_MUTE | RT5631_R_MUTE,
			RT5631_L_MUTE | RT5631_R_MUTE);
		msleep(150);
	पूर्ण

	/* recover soft volume and zero crossing setting */
	snd_soc_component_ग_लिखो(component, RT5631_SOFT_VOL_CTRL, soft_vol);
	snd_soc_component_ग_लिखो(component, RT5631_INT_ST_IRQ_CTRL_2, hp_zc);
पूर्ण

अटल पूर्णांक hp_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5631_priv *rt5631 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMD:
		अगर (rt5631->codec_version) अणु
			onebit_depop_mute_stage(component, 0);
			onebit_depop_घातer_stage(component, 0);
		पूर्ण अन्यथा अणु
			depop_seq_mute_stage(component, 0);
			depop_seq_घातer_stage(component, 0);
		पूर्ण
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMU:
		अगर (rt5631->codec_version) अणु
			onebit_depop_घातer_stage(component, 1);
			onebit_depop_mute_stage(component, 1);
		पूर्ण अन्यथा अणु
			depop_seq_घातer_stage(component, 1);
			depop_seq_mute_stage(component, 1);
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_dmic_params(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5631_priv *rt5631 = snd_soc_component_get_drvdata(component);

	चयन (rt5631->rx_rate) अणु
	हाल 44100:
	हाल 48000:
		snd_soc_component_update_bits(component, RT5631_DIG_MIC_CTRL,
			RT5631_DMIC_CLK_CTRL_MASK,
			RT5631_DMIC_CLK_CTRL_TO_32FS);
		अवरोध;

	हाल 32000:
	हाल 22050:
		snd_soc_component_update_bits(component, RT5631_DIG_MIC_CTRL,
			RT5631_DMIC_CLK_CTRL_MASK,
			RT5631_DMIC_CLK_CTRL_TO_64FS);
		अवरोध;

	हाल 16000:
	हाल 11025:
	हाल 8000:
		snd_soc_component_update_bits(component, RT5631_DIG_MIC_CTRL,
			RT5631_DMIC_CLK_CTRL_MASK,
			RT5631_DMIC_CLK_CTRL_TO_128FS);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_recmixl_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("OUTMIXL Capture Switch", RT5631_ADC_REC_MIXER,
			RT5631_M_OUTMIXL_RECMIXL_BIT, 1, 1),
	SOC_DAPM_SINGLE("MIC1_BST1 Capture Switch", RT5631_ADC_REC_MIXER,
			RT5631_M_MIC1_RECMIXL_BIT, 1, 1),
	SOC_DAPM_SINGLE("AXILVOL Capture Switch", RT5631_ADC_REC_MIXER,
			RT5631_M_AXIL_RECMIXL_BIT, 1, 1),
	SOC_DAPM_SINGLE("MONOIN_RX Capture Switch", RT5631_ADC_REC_MIXER,
			RT5631_M_MONO_IN_RECMIXL_BIT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_recmixr_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("MONOIN_RX Capture Switch", RT5631_ADC_REC_MIXER,
			RT5631_M_MONO_IN_RECMIXR_BIT, 1, 1),
	SOC_DAPM_SINGLE("AXIRVOL Capture Switch", RT5631_ADC_REC_MIXER,
			RT5631_M_AXIR_RECMIXR_BIT, 1, 1),
	SOC_DAPM_SINGLE("MIC2_BST2 Capture Switch", RT5631_ADC_REC_MIXER,
			RT5631_M_MIC2_RECMIXR_BIT, 1, 1),
	SOC_DAPM_SINGLE("OUTMIXR Capture Switch", RT5631_ADC_REC_MIXER,
			RT5631_M_OUTMIXR_RECMIXR_BIT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_spkmixl_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("RECMIXL Playback Switch", RT5631_SPK_MIXER_CTRL,
			RT5631_M_RECMIXL_SPKMIXL_BIT, 1, 1),
	SOC_DAPM_SINGLE("MIC1_P Playback Switch", RT5631_SPK_MIXER_CTRL,
			RT5631_M_MIC1P_SPKMIXL_BIT, 1, 1),
	SOC_DAPM_SINGLE("DACL Playback Switch", RT5631_SPK_MIXER_CTRL,
			RT5631_M_DACL_SPKMIXL_BIT, 1, 1),
	SOC_DAPM_SINGLE("OUTMIXL Playback Switch", RT5631_SPK_MIXER_CTRL,
			RT5631_M_OUTMIXL_SPKMIXL_BIT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_spkmixr_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("OUTMIXR Playback Switch", RT5631_SPK_MIXER_CTRL,
			RT5631_M_OUTMIXR_SPKMIXR_BIT, 1, 1),
	SOC_DAPM_SINGLE("DACR Playback Switch", RT5631_SPK_MIXER_CTRL,
			RT5631_M_DACR_SPKMIXR_BIT, 1, 1),
	SOC_DAPM_SINGLE("MIC2_P Playback Switch", RT5631_SPK_MIXER_CTRL,
			RT5631_M_MIC2P_SPKMIXR_BIT, 1, 1),
	SOC_DAPM_SINGLE("RECMIXR Playback Switch", RT5631_SPK_MIXER_CTRL,
			RT5631_M_RECMIXR_SPKMIXR_BIT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_ouपंचांगixl_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("RECMIXL Playback Switch", RT5631_OUTMIXER_L_CTRL,
				RT5631_M_RECMIXL_OUTMIXL_BIT, 1, 1),
	SOC_DAPM_SINGLE("RECMIXR Playback Switch", RT5631_OUTMIXER_L_CTRL,
				RT5631_M_RECMIXR_OUTMIXL_BIT, 1, 1),
	SOC_DAPM_SINGLE("DACL Playback Switch", RT5631_OUTMIXER_L_CTRL,
				RT5631_M_DACL_OUTMIXL_BIT, 1, 1),
	SOC_DAPM_SINGLE("MIC1_BST1 Playback Switch", RT5631_OUTMIXER_L_CTRL,
				RT5631_M_MIC1_OUTMIXL_BIT, 1, 1),
	SOC_DAPM_SINGLE("MIC2_BST2 Playback Switch", RT5631_OUTMIXER_L_CTRL,
				RT5631_M_MIC2_OUTMIXL_BIT, 1, 1),
	SOC_DAPM_SINGLE("MONOIN_RXP Playback Switch", RT5631_OUTMIXER_L_CTRL,
				RT5631_M_MONO_INP_OUTMIXL_BIT, 1, 1),
	SOC_DAPM_SINGLE("AXILVOL Playback Switch", RT5631_OUTMIXER_L_CTRL,
				RT5631_M_AXIL_OUTMIXL_BIT, 1, 1),
	SOC_DAPM_SINGLE("AXIRVOL Playback Switch", RT5631_OUTMIXER_L_CTRL,
				RT5631_M_AXIR_OUTMIXL_BIT, 1, 1),
	SOC_DAPM_SINGLE("VDAC Playback Switch", RT5631_OUTMIXER_L_CTRL,
				RT5631_M_VDAC_OUTMIXL_BIT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_ouपंचांगixr_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("VDAC Playback Switch", RT5631_OUTMIXER_R_CTRL,
				RT5631_M_VDAC_OUTMIXR_BIT, 1, 1),
	SOC_DAPM_SINGLE("AXIRVOL Playback Switch", RT5631_OUTMIXER_R_CTRL,
				RT5631_M_AXIR_OUTMIXR_BIT, 1, 1),
	SOC_DAPM_SINGLE("AXILVOL Playback Switch", RT5631_OUTMIXER_R_CTRL,
				RT5631_M_AXIL_OUTMIXR_BIT, 1, 1),
	SOC_DAPM_SINGLE("MONOIN_RXN Playback Switch", RT5631_OUTMIXER_R_CTRL,
				RT5631_M_MONO_INN_OUTMIXR_BIT, 1, 1),
	SOC_DAPM_SINGLE("MIC2_BST2 Playback Switch", RT5631_OUTMIXER_R_CTRL,
				RT5631_M_MIC2_OUTMIXR_BIT, 1, 1),
	SOC_DAPM_SINGLE("MIC1_BST1 Playback Switch", RT5631_OUTMIXER_R_CTRL,
				RT5631_M_MIC1_OUTMIXR_BIT, 1, 1),
	SOC_DAPM_SINGLE("DACR Playback Switch", RT5631_OUTMIXER_R_CTRL,
				RT5631_M_DACR_OUTMIXR_BIT, 1, 1),
	SOC_DAPM_SINGLE("RECMIXR Playback Switch", RT5631_OUTMIXER_R_CTRL,
				RT5631_M_RECMIXR_OUTMIXR_BIT, 1, 1),
	SOC_DAPM_SINGLE("RECMIXL Playback Switch", RT5631_OUTMIXER_R_CTRL,
				RT5631_M_RECMIXL_OUTMIXR_BIT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_AXO1MIX_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("MIC1_BST1 Playback Switch", RT5631_AXO1MIXER_CTRL,
				RT5631_M_MIC1_AXO1MIX_BIT , 1, 1),
	SOC_DAPM_SINGLE("MIC2_BST2 Playback Switch", RT5631_AXO1MIXER_CTRL,
				RT5631_M_MIC2_AXO1MIX_BIT, 1, 1),
	SOC_DAPM_SINGLE("OUTVOLL Playback Switch", RT5631_AXO1MIXER_CTRL,
				RT5631_M_OUTMIXL_AXO1MIX_BIT , 1 , 1),
	SOC_DAPM_SINGLE("OUTVOLR Playback Switch", RT5631_AXO1MIXER_CTRL,
				RT5631_M_OUTMIXR_AXO1MIX_BIT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_AXO2MIX_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("MIC1_BST1 Playback Switch", RT5631_AXO2MIXER_CTRL,
				RT5631_M_MIC1_AXO2MIX_BIT, 1, 1),
	SOC_DAPM_SINGLE("MIC2_BST2 Playback Switch", RT5631_AXO2MIXER_CTRL,
				RT5631_M_MIC2_AXO2MIX_BIT, 1, 1),
	SOC_DAPM_SINGLE("OUTVOLL Playback Switch", RT5631_AXO2MIXER_CTRL,
				RT5631_M_OUTMIXL_AXO2MIX_BIT, 1, 1),
	SOC_DAPM_SINGLE("OUTVOLR Playback Switch", RT5631_AXO2MIXER_CTRL,
				RT5631_M_OUTMIXR_AXO2MIX_BIT, 1 , 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_spolmix_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("SPKVOLL Playback Switch", RT5631_SPK_MONO_OUT_CTRL,
				RT5631_M_SPKVOLL_SPOLMIX_BIT, 1, 1),
	SOC_DAPM_SINGLE("SPKVOLR Playback Switch", RT5631_SPK_MONO_OUT_CTRL,
				RT5631_M_SPKVOLR_SPOLMIX_BIT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_spormix_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("SPKVOLL Playback Switch", RT5631_SPK_MONO_OUT_CTRL,
				RT5631_M_SPKVOLL_SPORMIX_BIT, 1, 1),
	SOC_DAPM_SINGLE("SPKVOLR Playback Switch", RT5631_SPK_MONO_OUT_CTRL,
				RT5631_M_SPKVOLR_SPORMIX_BIT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_monomix_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("OUTVOLL Playback Switch", RT5631_SPK_MONO_OUT_CTRL,
				RT5631_M_OUTVOLL_MONOMIX_BIT, 1, 1),
	SOC_DAPM_SINGLE("OUTVOLR Playback Switch", RT5631_SPK_MONO_OUT_CTRL,
				RT5631_M_OUTVOLR_MONOMIX_BIT, 1, 1),
पूर्ण;

/* Left SPK Volume Input */
अटल स्थिर अक्षर *rt5631_spkvoll_sel[] = अणु"Vmid", "SPKMIXL"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5631_spkvoll_क्रमागत, RT5631_SPK_OUT_VOL,
			    RT5631_L_EN_SHIFT, rt5631_spkvoll_sel);

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_spkvoll_mux_control =
	SOC_DAPM_ENUM("Left SPKVOL SRC", rt5631_spkvoll_क्रमागत);

/* Left HP Volume Input */
अटल स्थिर अक्षर *rt5631_hpvoll_sel[] = अणु"Vmid", "OUTMIXL"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5631_hpvoll_क्रमागत, RT5631_HP_OUT_VOL,
			    RT5631_L_EN_SHIFT, rt5631_hpvoll_sel);

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_hpvoll_mux_control =
	SOC_DAPM_ENUM("Left HPVOL SRC", rt5631_hpvoll_क्रमागत);

/* Left Out Volume Input */
अटल स्थिर अक्षर *rt5631_outvoll_sel[] = अणु"Vmid", "OUTMIXL"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5631_outvoll_क्रमागत, RT5631_MONO_AXO_1_2_VOL,
			    RT5631_L_EN_SHIFT, rt5631_outvoll_sel);

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_outvoll_mux_control =
	SOC_DAPM_ENUM("Left OUTVOL SRC", rt5631_outvoll_क्रमागत);

/* Right Out Volume Input */
अटल स्थिर अक्षर *rt5631_outvolr_sel[] = अणु"Vmid", "OUTMIXR"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5631_outvolr_क्रमागत, RT5631_MONO_AXO_1_2_VOL,
			    RT5631_R_EN_SHIFT, rt5631_outvolr_sel);

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_outvolr_mux_control =
	SOC_DAPM_ENUM("Right OUTVOL SRC", rt5631_outvolr_क्रमागत);

/* Right HP Volume Input */
अटल स्थिर अक्षर *rt5631_hpvolr_sel[] = अणु"Vmid", "OUTMIXR"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5631_hpvolr_क्रमागत, RT5631_HP_OUT_VOL,
			    RT5631_R_EN_SHIFT, rt5631_hpvolr_sel);

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_hpvolr_mux_control =
	SOC_DAPM_ENUM("Right HPVOL SRC", rt5631_hpvolr_क्रमागत);

/* Right SPK Volume Input */
अटल स्थिर अक्षर *rt5631_spkvolr_sel[] = अणु"Vmid", "SPKMIXR"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5631_spkvolr_क्रमागत, RT5631_SPK_OUT_VOL,
			    RT5631_R_EN_SHIFT, rt5631_spkvolr_sel);

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_spkvolr_mux_control =
	SOC_DAPM_ENUM("Right SPKVOL SRC", rt5631_spkvolr_क्रमागत);

/* SPO Left Channel Input */
अटल स्थिर अक्षर *rt5631_spol_src_sel[] = अणु
	"SPOLMIX", "MONOIN_RX", "VDAC", "DACL"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5631_spol_src_क्रमागत, RT5631_SPK_MONO_HP_OUT_CTRL,
			    RT5631_SPK_L_MUX_SEL_SHIFT, rt5631_spol_src_sel);

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_spol_mux_control =
	SOC_DAPM_ENUM("SPOL SRC", rt5631_spol_src_क्रमागत);

/* SPO Right Channel Input */
अटल स्थिर अक्षर *rt5631_spor_src_sel[] = अणु
	"SPORMIX", "MONOIN_RX", "VDAC", "DACR"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5631_spor_src_क्रमागत, RT5631_SPK_MONO_HP_OUT_CTRL,
			    RT5631_SPK_R_MUX_SEL_SHIFT, rt5631_spor_src_sel);

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_spor_mux_control =
	SOC_DAPM_ENUM("SPOR SRC", rt5631_spor_src_क्रमागत);

/* MONO Input */
अटल स्थिर अक्षर *rt5631_mono_src_sel[] = अणु"MONOMIX", "MONOIN_RX", "VDAC"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5631_mono_src_क्रमागत, RT5631_SPK_MONO_HP_OUT_CTRL,
			    RT5631_MONO_MUX_SEL_SHIFT, rt5631_mono_src_sel);

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_mono_mux_control =
	SOC_DAPM_ENUM("MONO SRC", rt5631_mono_src_क्रमागत);

/* Left HPO Input */
अटल स्थिर अक्षर *rt5631_hpl_src_sel[] = अणु"Left HPVOL", "Left DAC"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5631_hpl_src_क्रमागत, RT5631_SPK_MONO_HP_OUT_CTRL,
			    RT5631_HP_L_MUX_SEL_SHIFT, rt5631_hpl_src_sel);

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_hpl_mux_control =
	SOC_DAPM_ENUM("HPL SRC", rt5631_hpl_src_क्रमागत);

/* Right HPO Input */
अटल स्थिर अक्षर *rt5631_hpr_src_sel[] = अणु"Right HPVOL", "Right DAC"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5631_hpr_src_क्रमागत, RT5631_SPK_MONO_HP_OUT_CTRL,
			    RT5631_HP_R_MUX_SEL_SHIFT, rt5631_hpr_src_sel);

अटल स्थिर काष्ठा snd_kcontrol_new rt5631_hpr_mux_control =
	SOC_DAPM_ENUM("HPR SRC", rt5631_hpr_src_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget rt5631_dapm_widमाला_लो[] = अणु
	/* Vmid */
	SND_SOC_DAPM_VMID("Vmid"),
	/* PLL1 */
	SND_SOC_DAPM_SUPPLY("PLL1", RT5631_PWR_MANAG_ADD2,
			RT5631_PWR_PLL1_BIT, 0, शून्य, 0),

	/* Input Side */
	/* Input Lines */
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("AXIL"),
	SND_SOC_DAPM_INPUT("AXIR"),
	SND_SOC_DAPM_INPUT("MONOIN_RXN"),
	SND_SOC_DAPM_INPUT("MONOIN_RXP"),
	SND_SOC_DAPM_INPUT("DMIC"),

	/* MICBIAS */
	SND_SOC_DAPM_MICBIAS("MIC Bias1", RT5631_PWR_MANAG_ADD2,
			RT5631_PWR_MICBIAS1_VOL_BIT, 0),
	SND_SOC_DAPM_MICBIAS("MIC Bias2", RT5631_PWR_MANAG_ADD2,
			RT5631_PWR_MICBIAS2_VOL_BIT, 0),

	/* Boost */
	SND_SOC_DAPM_PGA("MIC1 Boost", RT5631_PWR_MANAG_ADD2,
			RT5631_PWR_MIC1_BOOT_GAIN_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("MIC2 Boost", RT5631_PWR_MANAG_ADD2,
			RT5631_PWR_MIC2_BOOT_GAIN_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("MONOIN_RXP Boost", RT5631_PWR_MANAG_ADD4,
			RT5631_PWR_MONO_IN_P_VOL_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("MONOIN_RXN Boost", RT5631_PWR_MANAG_ADD4,
			RT5631_PWR_MONO_IN_N_VOL_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("AXIL Boost", RT5631_PWR_MANAG_ADD4,
			RT5631_PWR_AXIL_IN_VOL_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("AXIR Boost", RT5631_PWR_MANAG_ADD4,
			RT5631_PWR_AXIR_IN_VOL_BIT, 0, शून्य, 0),

	/* MONO In */
	SND_SOC_DAPM_MIXER("MONO_IN", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* REC Mixer */
	SND_SOC_DAPM_MIXER("RECMIXL Mixer", RT5631_PWR_MANAG_ADD2,
		RT5631_PWR_RECMIXER_L_BIT, 0,
		&rt5631_recmixl_mixer_controls[0],
		ARRAY_SIZE(rt5631_recmixl_mixer_controls)),
	SND_SOC_DAPM_MIXER("RECMIXR Mixer", RT5631_PWR_MANAG_ADD2,
		RT5631_PWR_RECMIXER_R_BIT, 0,
		&rt5631_recmixr_mixer_controls[0],
		ARRAY_SIZE(rt5631_recmixr_mixer_controls)),
	/* Because of record duplication क्रम L/R channel,
	 * L/R ADCs need घातer up at the same समय */
	SND_SOC_DAPM_MIXER("ADC Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* DMIC */
	SND_SOC_DAPM_SUPPLY("DMIC Supply", RT5631_DIG_MIC_CTRL,
		RT5631_DMIC_ENA_SHIFT, 0,
		set_dmic_params, SND_SOC_DAPM_PRE_PMU),
	/* ADC Data Srouce */
	SND_SOC_DAPM_SUPPLY("Left ADC Select", RT5631_INT_ST_IRQ_CTRL_2,
			RT5631_ADC_DATA_SEL_MIC1_SHIFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Right ADC Select", RT5631_INT_ST_IRQ_CTRL_2,
			RT5631_ADC_DATA_SEL_MIC2_SHIFT, 0, शून्य, 0),

	/* ADCs */
	SND_SOC_DAPM_ADC("Left ADC", "HIFI Capture",
		RT5631_PWR_MANAG_ADD1, RT5631_PWR_ADC_L_CLK_BIT, 0),
	SND_SOC_DAPM_ADC("Right ADC", "HIFI Capture",
		RT5631_PWR_MANAG_ADD1, RT5631_PWR_ADC_R_CLK_BIT, 0),

	/* DAC and ADC supply घातer */
	SND_SOC_DAPM_SUPPLY("I2S", RT5631_PWR_MANAG_ADD1,
			RT5631_PWR_MAIN_I2S_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC REF", RT5631_PWR_MANAG_ADD1,
			RT5631_PWR_DAC_REF_BIT, 0, शून्य, 0),

	/* Output Side */
	/* DACs */
	SND_SOC_DAPM_DAC("Left DAC", "HIFI Playback",
		RT5631_PWR_MANAG_ADD1, RT5631_PWR_DAC_L_CLK_BIT, 0),
	SND_SOC_DAPM_DAC("Right DAC", "HIFI Playback",
		RT5631_PWR_MANAG_ADD1, RT5631_PWR_DAC_R_CLK_BIT, 0),
	SND_SOC_DAPM_DAC("Voice DAC", "Voice DAC Mono Playback",
				SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_PGA("Voice DAC Boost", SND_SOC_NOPM, 0, 0, शून्य, 0),
	/* DAC supply घातer */
	SND_SOC_DAPM_SUPPLY("Left DAC To Mixer", RT5631_PWR_MANAG_ADD1,
			RT5631_PWR_DAC_L_TO_MIXER_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Right DAC To Mixer", RT5631_PWR_MANAG_ADD1,
			RT5631_PWR_DAC_R_TO_MIXER_BIT, 0, शून्य, 0),

	/* Left SPK Mixer */
	SND_SOC_DAPM_MIXER("SPKMIXL Mixer", RT5631_PWR_MANAG_ADD2,
			RT5631_PWR_SPKMIXER_L_BIT, 0,
			&rt5631_spkmixl_mixer_controls[0],
			ARRAY_SIZE(rt5631_spkmixl_mixer_controls)),
	/* Left Out Mixer */
	SND_SOC_DAPM_MIXER("OUTMIXL Mixer", RT5631_PWR_MANAG_ADD2,
			RT5631_PWR_OUTMIXER_L_BIT, 0,
			&rt5631_ouपंचांगixl_mixer_controls[0],
			ARRAY_SIZE(rt5631_ouपंचांगixl_mixer_controls)),
	/* Right Out Mixer */
	SND_SOC_DAPM_MIXER("OUTMIXR Mixer", RT5631_PWR_MANAG_ADD2,
			RT5631_PWR_OUTMIXER_R_BIT, 0,
			&rt5631_ouपंचांगixr_mixer_controls[0],
			ARRAY_SIZE(rt5631_ouपंचांगixr_mixer_controls)),
	/* Right SPK Mixer */
	SND_SOC_DAPM_MIXER("SPKMIXR Mixer", RT5631_PWR_MANAG_ADD2,
			RT5631_PWR_SPKMIXER_R_BIT, 0,
			&rt5631_spkmixr_mixer_controls[0],
			ARRAY_SIZE(rt5631_spkmixr_mixer_controls)),

	/* Volume Mux */
	SND_SOC_DAPM_MUX("Left SPKVOL Mux", RT5631_PWR_MANAG_ADD4,
			RT5631_PWR_SPK_L_VOL_BIT, 0,
			&rt5631_spkvoll_mux_control),
	SND_SOC_DAPM_MUX("Left HPVOL Mux", RT5631_PWR_MANAG_ADD4,
			RT5631_PWR_HP_L_OUT_VOL_BIT, 0,
			&rt5631_hpvoll_mux_control),
	SND_SOC_DAPM_MUX("Left OUTVOL Mux", RT5631_PWR_MANAG_ADD4,
			RT5631_PWR_LOUT_VOL_BIT, 0,
			&rt5631_outvoll_mux_control),
	SND_SOC_DAPM_MUX("Right OUTVOL Mux", RT5631_PWR_MANAG_ADD4,
			RT5631_PWR_ROUT_VOL_BIT, 0,
			&rt5631_outvolr_mux_control),
	SND_SOC_DAPM_MUX("Right HPVOL Mux", RT5631_PWR_MANAG_ADD4,
			RT5631_PWR_HP_R_OUT_VOL_BIT, 0,
			&rt5631_hpvolr_mux_control),
	SND_SOC_DAPM_MUX("Right SPKVOL Mux", RT5631_PWR_MANAG_ADD4,
			RT5631_PWR_SPK_R_VOL_BIT, 0,
			&rt5631_spkvolr_mux_control),

	/* DAC To HP */
	SND_SOC_DAPM_PGA_S("Left DAC_HP", 0, SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA_S("Right DAC_HP", 0, SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* HP Depop */
	SND_SOC_DAPM_PGA_S("HP Depop", 1, SND_SOC_NOPM, 0, 0,
		hp_event, SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),

	/* AXO1 Mixer */
	SND_SOC_DAPM_MIXER("AXO1MIX Mixer", RT5631_PWR_MANAG_ADD3,
			RT5631_PWR_AXO1MIXER_BIT, 0,
			&rt5631_AXO1MIX_mixer_controls[0],
			ARRAY_SIZE(rt5631_AXO1MIX_mixer_controls)),
	/* SPOL Mixer */
	SND_SOC_DAPM_MIXER("SPOLMIX Mixer", SND_SOC_NOPM, 0, 0,
			&rt5631_spolmix_mixer_controls[0],
			ARRAY_SIZE(rt5631_spolmix_mixer_controls)),
	/* MONO Mixer */
	SND_SOC_DAPM_MIXER("MONOMIX Mixer", RT5631_PWR_MANAG_ADD3,
			RT5631_PWR_MONOMIXER_BIT, 0,
			&rt5631_monomix_mixer_controls[0],
			ARRAY_SIZE(rt5631_monomix_mixer_controls)),
	/* SPOR Mixer */
	SND_SOC_DAPM_MIXER("SPORMIX Mixer", SND_SOC_NOPM, 0, 0,
			&rt5631_spormix_mixer_controls[0],
			ARRAY_SIZE(rt5631_spormix_mixer_controls)),
	/* AXO2 Mixer */
	SND_SOC_DAPM_MIXER("AXO2MIX Mixer", RT5631_PWR_MANAG_ADD3,
			RT5631_PWR_AXO2MIXER_BIT, 0,
			&rt5631_AXO2MIX_mixer_controls[0],
			ARRAY_SIZE(rt5631_AXO2MIX_mixer_controls)),

	/* Mux */
	SND_SOC_DAPM_MUX("SPOL Mux", SND_SOC_NOPM, 0, 0,
			&rt5631_spol_mux_control),
	SND_SOC_DAPM_MUX("SPOR Mux", SND_SOC_NOPM, 0, 0,
			&rt5631_spor_mux_control),
	SND_SOC_DAPM_MUX("MONO Mux", SND_SOC_NOPM, 0, 0,
			&rt5631_mono_mux_control),
	SND_SOC_DAPM_MUX("HPL Mux", SND_SOC_NOPM, 0, 0,
			&rt5631_hpl_mux_control),
	SND_SOC_DAPM_MUX("HPR Mux", SND_SOC_NOPM, 0, 0,
			&rt5631_hpr_mux_control),

	/* AMP supply */
	SND_SOC_DAPM_SUPPLY("MONO Depop", RT5631_PWR_MANAG_ADD3,
			RT5631_PWR_MONO_DEPOP_DIS_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Class D", RT5631_PWR_MANAG_ADD1,
			RT5631_PWR_CLASS_D_BIT, 0, शून्य, 0),

	/* Output Lines */
	SND_SOC_DAPM_OUTPUT("AUXO1"),
	SND_SOC_DAPM_OUTPUT("AUXO2"),
	SND_SOC_DAPM_OUTPUT("SPOL"),
	SND_SOC_DAPM_OUTPUT("SPOR"),
	SND_SOC_DAPM_OUTPUT("HPOL"),
	SND_SOC_DAPM_OUTPUT("HPOR"),
	SND_SOC_DAPM_OUTPUT("MONO"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5631_dapm_routes[] = अणु
	अणु"MIC1 Boost", शून्य, "MIC1"पूर्ण,
	अणु"MIC2 Boost", शून्य, "MIC2"पूर्ण,
	अणु"MONOIN_RXP Boost", शून्य, "MONOIN_RXP"पूर्ण,
	अणु"MONOIN_RXN Boost", शून्य, "MONOIN_RXN"पूर्ण,
	अणु"AXIL Boost", शून्य, "AXIL"पूर्ण,
	अणु"AXIR Boost", शून्य, "AXIR"पूर्ण,

	अणु"MONO_IN", शून्य, "MONOIN_RXP Boost"पूर्ण,
	अणु"MONO_IN", शून्य, "MONOIN_RXN Boost"पूर्ण,

	अणु"RECMIXL Mixer", "OUTMIXL Capture Switch", "OUTMIXL Mixer"पूर्ण,
	अणु"RECMIXL Mixer", "MIC1_BST1 Capture Switch", "MIC1 Boost"पूर्ण,
	अणु"RECMIXL Mixer", "AXILVOL Capture Switch", "AXIL Boost"पूर्ण,
	अणु"RECMIXL Mixer", "MONOIN_RX Capture Switch", "MONO_IN"पूर्ण,

	अणु"RECMIXR Mixer", "OUTMIXR Capture Switch", "OUTMIXR Mixer"पूर्ण,
	अणु"RECMIXR Mixer", "MIC2_BST2 Capture Switch", "MIC2 Boost"पूर्ण,
	अणु"RECMIXR Mixer", "AXIRVOL Capture Switch", "AXIR Boost"पूर्ण,
	अणु"RECMIXR Mixer", "MONOIN_RX Capture Switch", "MONO_IN"पूर्ण,

	अणु"ADC Mixer", शून्य, "RECMIXL Mixer"पूर्ण,
	अणु"ADC Mixer", शून्य, "RECMIXR Mixer"पूर्ण,

	अणु"Left ADC", शून्य, "ADC Mixer"पूर्ण,
	अणु"Left ADC", शून्य, "Left ADC Select", check_adcl_selectपूर्ण,
	अणु"Left ADC", शून्य, "PLL1", check_sysclk1_sourceपूर्ण,
	अणु"Left ADC", शून्य, "I2S"पूर्ण,
	अणु"Left ADC", शून्य, "DAC REF"पूर्ण,

	अणु"Right ADC", शून्य, "ADC Mixer"पूर्ण,
	अणु"Right ADC", शून्य, "Right ADC Select", check_adcr_selectपूर्ण,
	अणु"Right ADC", शून्य, "PLL1", check_sysclk1_sourceपूर्ण,
	अणु"Right ADC", शून्य, "I2S"पूर्ण,
	अणु"Right ADC", शून्य, "DAC REF"पूर्ण,

	अणु"DMIC", शून्य, "DMIC Supply", check_dmic_usedपूर्ण,
	अणु"Left ADC", शून्य, "DMIC"पूर्ण,
	अणु"Right ADC", शून्य, "DMIC"पूर्ण,

	अणु"Left DAC", शून्य, "PLL1", check_sysclk1_sourceपूर्ण,
	अणु"Left DAC", शून्य, "I2S"पूर्ण,
	अणु"Left DAC", शून्य, "DAC REF"पूर्ण,
	अणु"Right DAC", शून्य, "PLL1", check_sysclk1_sourceपूर्ण,
	अणु"Right DAC", शून्य, "I2S"पूर्ण,
	अणु"Right DAC", शून्य, "DAC REF"पूर्ण,

	अणु"Voice DAC Boost", शून्य, "Voice DAC"पूर्ण,

	अणु"SPKMIXL Mixer", शून्य, "Left DAC To Mixer", check_dacl_to_spkmixlपूर्ण,
	अणु"SPKMIXL Mixer", "RECMIXL Playback Switch", "RECMIXL Mixer"पूर्ण,
	अणु"SPKMIXL Mixer", "MIC1_P Playback Switch", "MIC1"पूर्ण,
	अणु"SPKMIXL Mixer", "DACL Playback Switch", "Left DAC"पूर्ण,
	अणु"SPKMIXL Mixer", "OUTMIXL Playback Switch", "OUTMIXL Mixer"पूर्ण,

	अणु"SPKMIXR Mixer", शून्य, "Right DAC To Mixer", check_dacr_to_spkmixrपूर्ण,
	अणु"SPKMIXR Mixer", "OUTMIXR Playback Switch", "OUTMIXR Mixer"पूर्ण,
	अणु"SPKMIXR Mixer", "DACR Playback Switch", "Right DAC"पूर्ण,
	अणु"SPKMIXR Mixer", "MIC2_P Playback Switch", "MIC2"पूर्ण,
	अणु"SPKMIXR Mixer", "RECMIXR Playback Switch", "RECMIXR Mixer"पूर्ण,

	अणु"OUTMIXL Mixer", शून्य, "Left DAC To Mixer", check_dacl_to_ouपंचांगixlपूर्ण,
	अणु"OUTMIXL Mixer", "RECMIXL Playback Switch", "RECMIXL Mixer"पूर्ण,
	अणु"OUTMIXL Mixer", "RECMIXR Playback Switch", "RECMIXR Mixer"पूर्ण,
	अणु"OUTMIXL Mixer", "DACL Playback Switch", "Left DAC"पूर्ण,
	अणु"OUTMIXL Mixer", "MIC1_BST1 Playback Switch", "MIC1 Boost"पूर्ण,
	अणु"OUTMIXL Mixer", "MIC2_BST2 Playback Switch", "MIC2 Boost"पूर्ण,
	अणु"OUTMIXL Mixer", "MONOIN_RXP Playback Switch", "MONOIN_RXP Boost"पूर्ण,
	अणु"OUTMIXL Mixer", "AXILVOL Playback Switch", "AXIL Boost"पूर्ण,
	अणु"OUTMIXL Mixer", "AXIRVOL Playback Switch", "AXIR Boost"पूर्ण,
	अणु"OUTMIXL Mixer", "VDAC Playback Switch", "Voice DAC Boost"पूर्ण,

	अणु"OUTMIXR Mixer", शून्य, "Right DAC To Mixer", check_dacr_to_ouपंचांगixrपूर्ण,
	अणु"OUTMIXR Mixer", "RECMIXL Playback Switch", "RECMIXL Mixer"पूर्ण,
	अणु"OUTMIXR Mixer", "RECMIXR Playback Switch", "RECMIXR Mixer"पूर्ण,
	अणु"OUTMIXR Mixer", "DACR Playback Switch", "Right DAC"पूर्ण,
	अणु"OUTMIXR Mixer", "MIC1_BST1 Playback Switch", "MIC1 Boost"पूर्ण,
	अणु"OUTMIXR Mixer", "MIC2_BST2 Playback Switch", "MIC2 Boost"पूर्ण,
	अणु"OUTMIXR Mixer", "MONOIN_RXN Playback Switch", "MONOIN_RXN Boost"पूर्ण,
	अणु"OUTMIXR Mixer", "AXILVOL Playback Switch", "AXIL Boost"पूर्ण,
	अणु"OUTMIXR Mixer", "AXIRVOL Playback Switch", "AXIR Boost"पूर्ण,
	अणु"OUTMIXR Mixer", "VDAC Playback Switch", "Voice DAC Boost"पूर्ण,

	अणु"Left SPKVOL Mux",  "SPKMIXL", "SPKMIXL Mixer"पूर्ण,
	अणु"Left SPKVOL Mux",  "Vmid", "Vmid"पूर्ण,
	अणु"Left HPVOL Mux",  "OUTMIXL", "OUTMIXL Mixer"पूर्ण,
	अणु"Left HPVOL Mux",  "Vmid", "Vmid"पूर्ण,
	अणु"Left OUTVOL Mux",  "OUTMIXL", "OUTMIXL Mixer"पूर्ण,
	अणु"Left OUTVOL Mux",  "Vmid", "Vmid"पूर्ण,
	अणु"Right OUTVOL Mux",  "OUTMIXR", "OUTMIXR Mixer"पूर्ण,
	अणु"Right OUTVOL Mux",  "Vmid", "Vmid"पूर्ण,
	अणु"Right HPVOL Mux",  "OUTMIXR", "OUTMIXR Mixer"पूर्ण,
	अणु"Right HPVOL Mux",  "Vmid", "Vmid"पूर्ण,
	अणु"Right SPKVOL Mux",  "SPKMIXR", "SPKMIXR Mixer"पूर्ण,
	अणु"Right SPKVOL Mux",  "Vmid", "Vmid"पूर्ण,

	अणु"AXO1MIX Mixer", "MIC1_BST1 Playback Switch", "MIC1 Boost"पूर्ण,
	अणु"AXO1MIX Mixer", "OUTVOLL Playback Switch", "Left OUTVOL Mux"पूर्ण,
	अणु"AXO1MIX Mixer", "OUTVOLR Playback Switch", "Right OUTVOL Mux"पूर्ण,
	अणु"AXO1MIX Mixer", "MIC2_BST2 Playback Switch", "MIC2 Boost"पूर्ण,

	अणु"AXO2MIX Mixer", "MIC1_BST1 Playback Switch", "MIC1 Boost"पूर्ण,
	अणु"AXO2MIX Mixer", "OUTVOLL Playback Switch", "Left OUTVOL Mux"पूर्ण,
	अणु"AXO2MIX Mixer", "OUTVOLR Playback Switch", "Right OUTVOL Mux"पूर्ण,
	अणु"AXO2MIX Mixer", "MIC2_BST2 Playback Switch", "MIC2 Boost"पूर्ण,

	अणु"SPOLMIX Mixer", "SPKVOLL Playback Switch", "Left SPKVOL Mux"पूर्ण,
	अणु"SPOLMIX Mixer", "SPKVOLR Playback Switch", "Right SPKVOL Mux"पूर्ण,

	अणु"SPORMIX Mixer", "SPKVOLL Playback Switch", "Left SPKVOL Mux"पूर्ण,
	अणु"SPORMIX Mixer", "SPKVOLR Playback Switch", "Right SPKVOL Mux"पूर्ण,

	अणु"MONOMIX Mixer", "OUTVOLL Playback Switch", "Left OUTVOL Mux"पूर्ण,
	अणु"MONOMIX Mixer", "OUTVOLR Playback Switch", "Right OUTVOL Mux"पूर्ण,

	अणु"SPOL Mux", "SPOLMIX", "SPOLMIX Mixer"पूर्ण,
	अणु"SPOL Mux", "MONOIN_RX", "MONO_IN"पूर्ण,
	अणु"SPOL Mux", "VDAC", "Voice DAC Boost"पूर्ण,
	अणु"SPOL Mux", "DACL", "Left DAC"पूर्ण,

	अणु"SPOR Mux", "SPORMIX", "SPORMIX Mixer"पूर्ण,
	अणु"SPOR Mux", "MONOIN_RX", "MONO_IN"पूर्ण,
	अणु"SPOR Mux", "VDAC", "Voice DAC Boost"पूर्ण,
	अणु"SPOR Mux", "DACR", "Right DAC"पूर्ण,

	अणु"MONO Mux", "MONOMIX", "MONOMIX Mixer"पूर्ण,
	अणु"MONO Mux", "MONOIN_RX", "MONO_IN"पूर्ण,
	अणु"MONO Mux", "VDAC", "Voice DAC Boost"पूर्ण,

	अणु"Right DAC_HP", शून्य, "Right DAC"पूर्ण,
	अणु"Left DAC_HP", शून्य, "Left DAC"पूर्ण,

	अणु"HPL Mux", "Left HPVOL", "Left HPVOL Mux"पूर्ण,
	अणु"HPL Mux", "Left DAC", "Left DAC_HP"पूर्ण,
	अणु"HPR Mux", "Right HPVOL", "Right HPVOL Mux"पूर्ण,
	अणु"HPR Mux", "Right DAC", "Right DAC_HP"पूर्ण,

	अणु"HP Depop", शून्य, "HPL Mux"पूर्ण,
	अणु"HP Depop", शून्य, "HPR Mux"पूर्ण,

	अणु"AUXO1", शून्य, "AXO1MIX Mixer"पूर्ण,
	अणु"AUXO2", शून्य, "AXO2MIX Mixer"पूर्ण,

	अणु"SPOL", शून्य, "Class D"पूर्ण,
	अणु"SPOL", शून्य, "SPOL Mux"पूर्ण,
	अणु"SPOR", शून्य, "Class D"पूर्ण,
	अणु"SPOR", शून्य, "SPOR Mux"पूर्ण,

	अणु"HPOL", शून्य, "HP Depop"पूर्ण,
	अणु"HPOR", शून्य, "HP Depop"पूर्ण,

	अणु"MONO", शून्य, "MONO Depop"पूर्ण,
	अणु"MONO", शून्य, "MONO Mux"पूर्ण,
पूर्ण;

काष्ठा coeff_clk_भाग अणु
	u32 mclk;
	u32 bclk;
	u32 rate;
	u16 reg_val;
पूर्ण;

/* PLL भागisors */
काष्ठा pll_भाग अणु
	u32 pll_in;
	u32 pll_out;
	u16 reg_val;
पूर्ण;

अटल स्थिर काष्ठा pll_भाग codec_master_pll_भाग[] = अणु
	अणु2048000,  8192000,  0x0ea0पूर्ण,
	अणु3686400,  8192000,  0x4e27पूर्ण,
	अणु12000000,  8192000,  0x456bपूर्ण,
	अणु13000000,  8192000,  0x495fपूर्ण,
	अणु13100000,  8192000,  0x0320पूर्ण,
	अणु2048000,  11289600,  0xf637पूर्ण,
	अणु3686400,  11289600,  0x2f22पूर्ण,
	अणु12000000,  11289600,  0x3e2fपूर्ण,
	अणु13000000,  11289600,  0x4d5bपूर्ण,
	अणु13100000,  11289600,  0x363bपूर्ण,
	अणु2048000,  16384000,  0x1ea0पूर्ण,
	अणु3686400,  16384000,  0x9e27पूर्ण,
	अणु12000000,  16384000,  0x452bपूर्ण,
	अणु13000000,  16384000,  0x542fपूर्ण,
	अणु13100000,  16384000,  0x03a0पूर्ण,
	अणु2048000,  16934400,  0xe625पूर्ण,
	अणु3686400,  16934400,  0x9126पूर्ण,
	अणु12000000,  16934400,  0x4d2cपूर्ण,
	अणु13000000,  16934400,  0x742fपूर्ण,
	अणु13100000,  16934400,  0x3c27पूर्ण,
	अणु2048000,  22579200,  0x2aa0पूर्ण,
	अणु3686400,  22579200,  0x2f20पूर्ण,
	अणु12000000,  22579200,  0x7e2fपूर्ण,
	अणु13000000,  22579200,  0x742fपूर्ण,
	अणु13100000,  22579200,  0x3c27पूर्ण,
	अणु2048000,  24576000,  0x2ea0पूर्ण,
	अणु3686400,  24576000,  0xee27पूर्ण,
	अणु12000000,  24576000,  0x2915पूर्ण,
	अणु13000000,  24576000,  0x772eपूर्ण,
	अणु13100000,  24576000,  0x0d20पूर्ण,
	अणु26000000,  24576000,  0x2027पूर्ण,
	अणु26000000,  22579200,  0x392fपूर्ण,
	अणु24576000,  22579200,  0x0921पूर्ण,
	अणु24576000,  24576000,  0x02a0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pll_भाग codec_slave_pll_भाग[] = अणु
	अणु256000,  2048000,  0x46f0पूर्ण,
	अणु256000,  4096000,  0x3ea0पूर्ण,
	अणु352800,  5644800,  0x3ea0पूर्ण,
	अणु512000,  8192000,  0x3ea0पूर्ण,
	अणु1024000,  8192000,  0x46f0पूर्ण,
	अणु705600,  11289600,  0x3ea0पूर्ण,
	अणु1024000,  16384000,  0x3ea0पूर्ण,
	अणु1411200,  22579200,  0x3ea0पूर्ण,
	अणु1536000,  24576000,  0x3ea0पूर्ण,
	अणु2048000,  16384000,  0x1ea0पूर्ण,
	अणु2822400,  22579200,  0x1ea0पूर्ण,
	अणु2822400,  45158400,  0x5ec0पूर्ण,
	अणु5644800,  45158400,  0x46f0पूर्ण,
	अणु3072000,  24576000,  0x1ea0पूर्ण,
	अणु3072000,  49152000,  0x5ec0पूर्ण,
	अणु6144000,  49152000,  0x46f0पूर्ण,
	अणु705600,  11289600,  0x3ea0पूर्ण,
	अणु705600,  8467200,  0x3ab0पूर्ण,
	अणु24576000,  24576000,  0x02a0पूर्ण,
	अणु1411200,  11289600,  0x1690पूर्ण,
	अणु2822400,  11289600,  0x0a90पूर्ण,
	अणु1536000,  12288000,  0x1690पूर्ण,
	अणु3072000,  12288000,  0x0a90पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा coeff_clk_भाग coeff_भाग[] = अणु
	/* sysclk is 256fs */
	अणु2048000,  8000 * 32,  8000, 0x1000पूर्ण,
	अणु2048000,  8000 * 64,  8000, 0x0000पूर्ण,
	अणु2822400,  11025 * 32,  11025,  0x1000पूर्ण,
	अणु2822400,  11025 * 64,  11025,  0x0000पूर्ण,
	अणु4096000,  16000 * 32,  16000,  0x1000पूर्ण,
	अणु4096000,  16000 * 64,  16000,  0x0000पूर्ण,
	अणु5644800,  22050 * 32,  22050,  0x1000पूर्ण,
	अणु5644800,  22050 * 64,  22050,  0x0000पूर्ण,
	अणु8192000,  32000 * 32,  32000,  0x1000पूर्ण,
	अणु8192000,  32000 * 64,  32000,  0x0000पूर्ण,
	अणु11289600,  44100 * 32,  44100,  0x1000पूर्ण,
	अणु11289600,  44100 * 64,  44100,  0x0000पूर्ण,
	अणु12288000,  48000 * 32,  48000,  0x1000पूर्ण,
	अणु12288000,  48000 * 64,  48000,  0x0000पूर्ण,
	अणु22579200,  88200 * 32,  88200,  0x1000पूर्ण,
	अणु22579200,  88200 * 64,  88200,  0x0000पूर्ण,
	अणु24576000,  96000 * 32,  96000,  0x1000पूर्ण,
	अणु24576000,  96000 * 64,  96000,  0x0000पूर्ण,
	/* sysclk is 512fs */
	अणु4096000,  8000 * 32,  8000, 0x3000पूर्ण,
	अणु4096000,  8000 * 64,  8000, 0x2000पूर्ण,
	अणु5644800,  11025 * 32,  11025, 0x3000पूर्ण,
	अणु5644800,  11025 * 64,  11025, 0x2000पूर्ण,
	अणु8192000,  16000 * 32,  16000, 0x3000पूर्ण,
	अणु8192000,  16000 * 64,  16000, 0x2000पूर्ण,
	अणु11289600,  22050 * 32,  22050, 0x3000पूर्ण,
	अणु11289600,  22050 * 64,  22050, 0x2000पूर्ण,
	अणु16384000,  32000 * 32,  32000, 0x3000पूर्ण,
	अणु16384000,  32000 * 64,  32000, 0x2000पूर्ण,
	अणु22579200,  44100 * 32,  44100, 0x3000पूर्ण,
	अणु22579200,  44100 * 64,  44100, 0x2000पूर्ण,
	अणु24576000,  48000 * 32,  48000, 0x3000पूर्ण,
	अणु24576000,  48000 * 64,  48000, 0x2000पूर्ण,
	अणु45158400,  88200 * 32,  88200, 0x3000पूर्ण,
	अणु45158400,  88200 * 64,  88200, 0x2000पूर्ण,
	अणु49152000,  96000 * 32,  96000, 0x3000पूर्ण,
	अणु49152000,  96000 * 64,  96000, 0x2000पूर्ण,
	/* sysclk is 24.576Mhz or 22.5792Mhz */
	अणु24576000,  8000 * 32,  8000,  0x7080पूर्ण,
	अणु24576000,  8000 * 64,  8000,  0x6080पूर्ण,
	अणु24576000,  16000 * 32,  16000,  0x5080पूर्ण,
	अणु24576000,  16000 * 64,  16000,  0x4080पूर्ण,
	अणु24576000,  24000 * 32,  24000,  0x5000पूर्ण,
	अणु24576000,  24000 * 64,  24000,  0x4000पूर्ण,
	अणु24576000,  32000 * 32,  32000,  0x3080पूर्ण,
	अणु24576000,  32000 * 64,  32000,  0x2080पूर्ण,
	अणु22579200,  11025 * 32,  11025,  0x7000पूर्ण,
	अणु22579200,  11025 * 64,  11025,  0x6000पूर्ण,
	अणु22579200,  22050 * 32,  22050,  0x5000पूर्ण,
	अणु22579200,  22050 * 64,  22050,  0x4000पूर्ण,
पूर्ण;

अटल पूर्णांक get_coeff(पूर्णांक mclk, पूर्णांक rate, पूर्णांक बारofbclk)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(coeff_भाग); i++) अणु
		अगर (coeff_भाग[i].mclk == mclk && coeff_भाग[i].rate == rate &&
			(coeff_भाग[i].bclk / coeff_भाग[i].rate) == बारofbclk)
			वापस i;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक rt5631_hअगरi_pcm_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5631_priv *rt5631 = snd_soc_component_get_drvdata(component);
	पूर्णांक बारofbclk = 32, coeff;
	अचिन्हित पूर्णांक अगरace = 0;

	dev_dbg(component->dev, "enter %s\n", __func__);

	rt5631->bclk_rate = snd_soc_params_to_bclk(params);
	अगर (rt5631->bclk_rate < 0) अणु
		dev_err(component->dev, "Fail to get BCLK rate\n");
		वापस rt5631->bclk_rate;
	पूर्ण
	rt5631->rx_rate = params_rate(params);

	अगर (rt5631->master)
		coeff = get_coeff(rt5631->sysclk, rt5631->rx_rate,
			rt5631->bclk_rate / rt5631->rx_rate);
	अन्यथा
		coeff = get_coeff(rt5631->sysclk, rt5631->rx_rate,
					बारofbclk);
	अगर (coeff < 0) अणु
		dev_err(component->dev, "Fail to get coeff\n");
		वापस coeff;
	पूर्ण

	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		अगरace |= RT5631_SDP_I2S_DL_20;
		अवरोध;
	हाल 24:
		अगरace |= RT5631_SDP_I2S_DL_24;
		अवरोध;
	हाल 8:
		अगरace |= RT5631_SDP_I2S_DL_8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, RT5631_SDP_CTRL,
		RT5631_SDP_I2S_DL_MASK, अगरace);
	snd_soc_component_ग_लिखो(component, RT5631_STEREO_AD_DA_CLK_CTRL,
					coeff_भाग[coeff].reg_val);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5631_hअगरi_codec_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
						अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा rt5631_priv *rt5631 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक अगरace = 0;

	dev_dbg(component->dev, "enter %s\n", __func__);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		rt5631->master = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अगरace |= RT5631_SDP_MODE_SEL_SLAVE;
		rt5631->master = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरace |= RT5631_SDP_I2S_DF_LEFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		अगरace |= RT5631_SDP_I2S_DF_PCM_A;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		अगरace  |= RT5631_SDP_I2S_DF_PCM_B;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अगरace |= RT5631_SDP_I2S_BCLK_POL_CTRL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, RT5631_SDP_CTRL, अगरace);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5631_hअगरi_codec_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा rt5631_priv *rt5631 = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "enter %s, syclk=%d\n", __func__, freq);

	अगर ((freq >= (256 * 8000)) && (freq <= (512 * 96000))) अणु
		rt5631->sysclk = freq;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक rt5631_codec_set_dai_pll(काष्ठा snd_soc_dai *codec_dai, पूर्णांक pll_id,
		पूर्णांक source, अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा rt5631_priv *rt5631 = snd_soc_component_get_drvdata(component);
	पूर्णांक i, ret = -EINVAL;

	dev_dbg(component->dev, "enter %s\n", __func__);

	अगर (!freq_in || !freq_out) अणु
		dev_dbg(component->dev, "PLL disabled\n");

		snd_soc_component_update_bits(component, RT5631_GLOBAL_CLK_CTRL,
			RT5631_SYSCLK_SOUR_SEL_MASK,
			RT5631_SYSCLK_SOUR_SEL_MCLK);

		वापस 0;
	पूर्ण

	अगर (rt5631->master) अणु
		क्रम (i = 0; i < ARRAY_SIZE(codec_master_pll_भाग); i++)
			अगर (freq_in == codec_master_pll_भाग[i].pll_in &&
			freq_out == codec_master_pll_भाग[i].pll_out) अणु
				dev_info(component->dev,
					"change PLL in master mode\n");
				snd_soc_component_ग_लिखो(component, RT5631_PLL_CTRL,
					codec_master_pll_भाग[i].reg_val);
				schedule_समयout_unपूर्णांकerruptible(
					msecs_to_jअगरfies(20));
				snd_soc_component_update_bits(component,
					RT5631_GLOBAL_CLK_CTRL,
					RT5631_SYSCLK_SOUR_SEL_MASK |
					RT5631_PLLCLK_SOUR_SEL_MASK,
					RT5631_SYSCLK_SOUR_SEL_PLL |
					RT5631_PLLCLK_SOUR_SEL_MCLK);
				ret = 0;
				अवरोध;
			पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ARRAY_SIZE(codec_slave_pll_भाग); i++)
			अगर (freq_in == codec_slave_pll_भाग[i].pll_in &&
			freq_out == codec_slave_pll_भाग[i].pll_out) अणु
				dev_info(component->dev,
					"change PLL in slave mode\n");
				snd_soc_component_ग_लिखो(component, RT5631_PLL_CTRL,
					codec_slave_pll_भाग[i].reg_val);
				schedule_समयout_unपूर्णांकerruptible(
					msecs_to_jअगरfies(20));
				snd_soc_component_update_bits(component,
					RT5631_GLOBAL_CLK_CTRL,
					RT5631_SYSCLK_SOUR_SEL_MASK |
					RT5631_PLLCLK_SOUR_SEL_MASK,
					RT5631_SYSCLK_SOUR_SEL_PLL |
					RT5631_PLLCLK_SOUR_SEL_BCLK);
				ret = 0;
				अवरोध;
			पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rt5631_set_bias_level(काष्ठा snd_soc_component *component,
			क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा rt5631_priv *rt5631 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
		snd_soc_component_update_bits(component, RT5631_PWR_MANAG_ADD2,
			RT5631_PWR_MICBIAS1_VOL | RT5631_PWR_MICBIAS2_VOL,
			RT5631_PWR_MICBIAS1_VOL | RT5631_PWR_MICBIAS2_VOL);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			snd_soc_component_update_bits(component, RT5631_PWR_MANAG_ADD3,
				RT5631_PWR_VREF | RT5631_PWR_MAIN_BIAS,
				RT5631_PWR_VREF | RT5631_PWR_MAIN_BIAS);
			msleep(80);
			snd_soc_component_update_bits(component, RT5631_PWR_MANAG_ADD3,
				RT5631_PWR_FAST_VREF_CTRL,
				RT5631_PWR_FAST_VREF_CTRL);
			regcache_cache_only(rt5631->regmap, false);
			regcache_sync(rt5631->regmap);
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_ग_लिखो(component, RT5631_PWR_MANAG_ADD1, 0x0000);
		snd_soc_component_ग_लिखो(component, RT5631_PWR_MANAG_ADD2, 0x0000);
		snd_soc_component_ग_लिखो(component, RT5631_PWR_MANAG_ADD3, 0x0000);
		snd_soc_component_ग_लिखो(component, RT5631_PWR_MANAG_ADD4, 0x0000);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5631_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5631_priv *rt5631 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val;

	val = rt5631_पढ़ो_index(component, RT5631_ADDA_MIXER_INTL_REG3);
	अगर (val & 0x0002)
		rt5631->codec_version = 1;
	अन्यथा
		rt5631->codec_version = 0;

	rt5631_reset(component);
	snd_soc_component_update_bits(component, RT5631_PWR_MANAG_ADD3,
		RT5631_PWR_VREF | RT5631_PWR_MAIN_BIAS,
		RT5631_PWR_VREF | RT5631_PWR_MAIN_BIAS);
	msleep(80);
	snd_soc_component_update_bits(component, RT5631_PWR_MANAG_ADD3,
		RT5631_PWR_FAST_VREF_CTRL, RT5631_PWR_FAST_VREF_CTRL);
	/* enable HP zero cross */
	snd_soc_component_ग_लिखो(component, RT5631_INT_ST_IRQ_CTRL_2, 0x0f18);
	/* घातer off ClassD स्वतः Recovery */
	अगर (rt5631->codec_version)
		snd_soc_component_update_bits(component, RT5631_INT_ST_IRQ_CTRL_2,
					0x2000, 0x2000);
	अन्यथा
		snd_soc_component_update_bits(component, RT5631_INT_ST_IRQ_CTRL_2,
					0x2000, 0);
	/* DMIC */
	अगर (rt5631->dmic_used_flag) अणु
		snd_soc_component_update_bits(component, RT5631_GPIO_CTRL,
			RT5631_GPIO_PIN_FUN_SEL_MASK |
			RT5631_GPIO_DMIC_FUN_SEL_MASK,
			RT5631_GPIO_PIN_FUN_SEL_GPIO_DIMC |
			RT5631_GPIO_DMIC_FUN_SEL_DIMC);
		snd_soc_component_update_bits(component, RT5631_DIG_MIC_CTRL,
			RT5631_DMIC_L_CH_LATCH_MASK |
			RT5631_DMIC_R_CH_LATCH_MASK,
			RT5631_DMIC_L_CH_LATCH_FALLING |
			RT5631_DMIC_R_CH_LATCH_RISING);
	पूर्ण

	snd_soc_component_init_bias_level(component, SND_SOC_BIAS_STANDBY);

	वापस 0;
पूर्ण

#घोषणा RT5631_STEREO_RATES SNDRV_PCM_RATE_8000_96000
#घोषणा RT5631_FORMAT	(SNDRV_PCM_FMTBIT_S16_LE | \
			SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | \
			SNDRV_PCM_FMTBIT_S8)

अटल स्थिर काष्ठा snd_soc_dai_ops rt5631_ops = अणु
	.hw_params = rt5631_hअगरi_pcm_params,
	.set_fmt = rt5631_hअगरi_codec_set_dai_fmt,
	.set_sysclk = rt5631_hअगरi_codec_set_dai_sysclk,
	.set_pll = rt5631_codec_set_dai_pll,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt5631_dai[] = अणु
	अणु
		.name = "rt5631-hifi",
		.id = 1,
		.playback = अणु
			.stream_name = "HIFI Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5631_STEREO_RATES,
			.क्रमmats = RT5631_FORMAT,
		पूर्ण,
		.capture = अणु
			.stream_name = "HIFI Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5631_STEREO_RATES,
			.क्रमmats = RT5631_FORMAT,
		पूर्ण,
		.ops = &rt5631_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_rt5631 = अणु
	.probe			= rt5631_probe,
	.set_bias_level		= rt5631_set_bias_level,
	.controls		= rt5631_snd_controls,
	.num_controls		= ARRAY_SIZE(rt5631_snd_controls),
	.dapm_widमाला_लो		= rt5631_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(rt5631_dapm_widमाला_लो),
	.dapm_routes		= rt5631_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(rt5631_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id rt5631_i2c_id[] = अणु
	अणु "rt5631", 0 पूर्ण,
	अणु "alc5631", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt5631_i2c_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id rt5631_i2c_dt_ids[] = अणु
	अणु .compatible = "realtek,rt5631"पूर्ण,
	अणु .compatible = "realtek,alc5631"पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rt5631_i2c_dt_ids);
#पूर्ण_अगर

अटल स्थिर काष्ठा regmap_config rt5631_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,

	.पढ़ोable_reg = rt5631_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = rt5631_अस्थिर_रेजिस्टर,
	.max_रेजिस्टर = RT5631_VENDOR_ID2,
	.reg_शेषs = rt5631_reg,
	.num_reg_शेषs = ARRAY_SIZE(rt5631_reg),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक rt5631_i2c_probe(काष्ठा i2c_client *i2c,
		    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rt5631_priv *rt5631;
	पूर्णांक ret;

	rt5631 = devm_kzalloc(&i2c->dev, माप(काष्ठा rt5631_priv),
			      GFP_KERNEL);
	अगर (शून्य == rt5631)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, rt5631);

	rt5631->regmap = devm_regmap_init_i2c(i2c, &rt5631_regmap_config);
	अगर (IS_ERR(rt5631->regmap))
		वापस PTR_ERR(rt5631->regmap);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_rt5631,
			rt5631_dai, ARRAY_SIZE(rt5631_dai));
	वापस ret;
पूर्ण

अटल पूर्णांक rt5631_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver rt5631_i2c_driver = अणु
	.driver = अणु
		.name = "rt5631",
		.of_match_table = of_match_ptr(rt5631_i2c_dt_ids),
	पूर्ण,
	.probe = rt5631_i2c_probe,
	.हटाओ   = rt5631_i2c_हटाओ,
	.id_table = rt5631_i2c_id,
पूर्ण;

module_i2c_driver(rt5631_i2c_driver);

MODULE_DESCRIPTION("ASoC RT5631 driver");
MODULE_AUTHOR("flove <flove@realtek.com>");
MODULE_LICENSE("GPL");
