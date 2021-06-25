<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rt5651.c  --  RT5651 ALSA SoC audio codec driver
 *
 * Copyright 2014 Realtek Semiconductor Corp.
 * Author: Bard Liao <bardliao@realtek.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/acpi.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/jack.h>

#समावेश "rl6231.h"
#समावेश "rt5651.h"

#घोषणा RT5651_DEVICE_ID_VALUE 0x6281

#घोषणा RT5651_PR_RANGE_BASE (0xff + 1)
#घोषणा RT5651_PR_SPACING 0x100

#घोषणा RT5651_PR_BASE (RT5651_PR_RANGE_BASE + (0 * RT5651_PR_SPACING))

अटल स्थिर काष्ठा regmap_range_cfg rt5651_ranges[] = अणु
	अणु .name = "PR", .range_min = RT5651_PR_BASE,
	  .range_max = RT5651_PR_BASE + 0xb4,
	  .selector_reg = RT5651_PRIV_INDEX,
	  .selector_mask = 0xff,
	  .selector_shअगरt = 0x0,
	  .winकरोw_start = RT5651_PRIV_DATA,
	  .winकरोw_len = 0x1, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence init_list[] = अणु
	अणुRT5651_PR_BASE + 0x3d,	0x3e00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष rt5651_reg[] = अणु
	अणु 0x00, 0x0000 पूर्ण,
	अणु 0x02, 0xc8c8 पूर्ण,
	अणु 0x03, 0xc8c8 पूर्ण,
	अणु 0x05, 0x0000 पूर्ण,
	अणु 0x0d, 0x0000 पूर्ण,
	अणु 0x0e, 0x0000 पूर्ण,
	अणु 0x0f, 0x0808 पूर्ण,
	अणु 0x10, 0x0808 पूर्ण,
	अणु 0x19, 0xafaf पूर्ण,
	अणु 0x1a, 0xafaf पूर्ण,
	अणु 0x1b, 0x0c00 पूर्ण,
	अणु 0x1c, 0x2f2f पूर्ण,
	अणु 0x1d, 0x2f2f पूर्ण,
	अणु 0x1e, 0x0000 पूर्ण,
	अणु 0x27, 0x7860 पूर्ण,
	अणु 0x28, 0x7070 पूर्ण,
	अणु 0x29, 0x8080 पूर्ण,
	अणु 0x2a, 0x5252 पूर्ण,
	अणु 0x2b, 0x5454 पूर्ण,
	अणु 0x2f, 0x0000 पूर्ण,
	अणु 0x30, 0x5000 पूर्ण,
	अणु 0x3b, 0x0000 पूर्ण,
	अणु 0x3c, 0x006f पूर्ण,
	अणु 0x3d, 0x0000 पूर्ण,
	अणु 0x3e, 0x006f पूर्ण,
	अणु 0x45, 0x6000 पूर्ण,
	अणु 0x4d, 0x0000 पूर्ण,
	अणु 0x4e, 0x0000 पूर्ण,
	अणु 0x4f, 0x0279 पूर्ण,
	अणु 0x50, 0x0000 पूर्ण,
	अणु 0x51, 0x0000 पूर्ण,
	अणु 0x52, 0x0279 पूर्ण,
	अणु 0x53, 0xf000 पूर्ण,
	अणु 0x61, 0x0000 पूर्ण,
	अणु 0x62, 0x0000 पूर्ण,
	अणु 0x63, 0x00c0 पूर्ण,
	अणु 0x64, 0x0000 पूर्ण,
	अणु 0x65, 0x0000 पूर्ण,
	अणु 0x66, 0x0000 पूर्ण,
	अणु 0x70, 0x8000 पूर्ण,
	अणु 0x71, 0x8000 पूर्ण,
	अणु 0x73, 0x1104 पूर्ण,
	अणु 0x74, 0x0c00 पूर्ण,
	अणु 0x75, 0x1400 पूर्ण,
	अणु 0x77, 0x0c00 पूर्ण,
	अणु 0x78, 0x4000 पूर्ण,
	अणु 0x79, 0x0123 पूर्ण,
	अणु 0x80, 0x0000 पूर्ण,
	अणु 0x81, 0x0000 पूर्ण,
	अणु 0x82, 0x0000 पूर्ण,
	अणु 0x83, 0x0800 पूर्ण,
	अणु 0x84, 0x0000 पूर्ण,
	अणु 0x85, 0x0008 पूर्ण,
	अणु 0x89, 0x0000 पूर्ण,
	अणु 0x8e, 0x0004 पूर्ण,
	अणु 0x8f, 0x1100 पूर्ण,
	अणु 0x90, 0x0000 पूर्ण,
	अणु 0x93, 0x2000 पूर्ण,
	अणु 0x94, 0x0200 पूर्ण,
	अणु 0xb0, 0x2080 पूर्ण,
	अणु 0xb1, 0x0000 पूर्ण,
	अणु 0xb4, 0x2206 पूर्ण,
	अणु 0xb5, 0x1f00 पूर्ण,
	अणु 0xb6, 0x0000 पूर्ण,
	अणु 0xbb, 0x0000 पूर्ण,
	अणु 0xbc, 0x0000 पूर्ण,
	अणु 0xbd, 0x0000 पूर्ण,
	अणु 0xbe, 0x0000 पूर्ण,
	अणु 0xbf, 0x0000 पूर्ण,
	अणु 0xc0, 0x0400 पूर्ण,
	अणु 0xc1, 0x0000 पूर्ण,
	अणु 0xc2, 0x0000 पूर्ण,
	अणु 0xcf, 0x0013 पूर्ण,
	अणु 0xd0, 0x0680 पूर्ण,
	अणु 0xd1, 0x1c17 पूर्ण,
	अणु 0xd3, 0xb320 पूर्ण,
	अणु 0xd9, 0x0809 पूर्ण,
	अणु 0xfa, 0x0010 पूर्ण,
	अणु 0xfe, 0x10ec पूर्ण,
	अणु 0xff, 0x6281 पूर्ण,
पूर्ण;

अटल bool rt5651_अस्थिर_रेजिस्टर(काष्ठा device *dev,  अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rt5651_ranges); i++) अणु
		अगर ((reg >= rt5651_ranges[i].winकरोw_start &&
		     reg <= rt5651_ranges[i].winकरोw_start +
		     rt5651_ranges[i].winकरोw_len) ||
		    (reg >= rt5651_ranges[i].range_min &&
		     reg <= rt5651_ranges[i].range_max)) अणु
			वापस true;
		पूर्ण
	पूर्ण

	चयन (reg) अणु
	हाल RT5651_RESET:
	हाल RT5651_PRIV_DATA:
	हाल RT5651_EQ_CTRL1:
	हाल RT5651_ALC_1:
	हाल RT5651_IRQ_CTRL2:
	हाल RT5651_INT_IRQ_ST:
	हाल RT5651_PGM_REG_ARR1:
	हाल RT5651_PGM_REG_ARR3:
	हाल RT5651_VENDOR_ID:
	हाल RT5651_DEVICE_ID:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt5651_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rt5651_ranges); i++) अणु
		अगर ((reg >= rt5651_ranges[i].winकरोw_start &&
		     reg <= rt5651_ranges[i].winकरोw_start +
		     rt5651_ranges[i].winकरोw_len) ||
		    (reg >= rt5651_ranges[i].range_min &&
		     reg <= rt5651_ranges[i].range_max)) अणु
			वापस true;
		पूर्ण
	पूर्ण

	चयन (reg) अणु
	हाल RT5651_RESET:
	हाल RT5651_VERSION_ID:
	हाल RT5651_VENDOR_ID:
	हाल RT5651_DEVICE_ID:
	हाल RT5651_HP_VOL:
	हाल RT5651_LOUT_CTRL1:
	हाल RT5651_LOUT_CTRL2:
	हाल RT5651_IN1_IN2:
	हाल RT5651_IN3:
	हाल RT5651_INL1_INR1_VOL:
	हाल RT5651_INL2_INR2_VOL:
	हाल RT5651_DAC1_DIG_VOL:
	हाल RT5651_DAC2_DIG_VOL:
	हाल RT5651_DAC2_CTRL:
	हाल RT5651_ADC_DIG_VOL:
	हाल RT5651_ADC_DATA:
	हाल RT5651_ADC_BST_VOL:
	हाल RT5651_STO1_ADC_MIXER:
	हाल RT5651_STO2_ADC_MIXER:
	हाल RT5651_AD_DA_MIXER:
	हाल RT5651_STO_DAC_MIXER:
	हाल RT5651_DD_MIXER:
	हाल RT5651_DIG_INF_DATA:
	हाल RT5651_PDM_CTL:
	हाल RT5651_REC_L1_MIXER:
	हाल RT5651_REC_L2_MIXER:
	हाल RT5651_REC_R1_MIXER:
	हाल RT5651_REC_R2_MIXER:
	हाल RT5651_HPO_MIXER:
	हाल RT5651_OUT_L1_MIXER:
	हाल RT5651_OUT_L2_MIXER:
	हाल RT5651_OUT_L3_MIXER:
	हाल RT5651_OUT_R1_MIXER:
	हाल RT5651_OUT_R2_MIXER:
	हाल RT5651_OUT_R3_MIXER:
	हाल RT5651_LOUT_MIXER:
	हाल RT5651_PWR_DIG1:
	हाल RT5651_PWR_DIG2:
	हाल RT5651_PWR_ANLG1:
	हाल RT5651_PWR_ANLG2:
	हाल RT5651_PWR_MIXER:
	हाल RT5651_PWR_VOL:
	हाल RT5651_PRIV_INDEX:
	हाल RT5651_PRIV_DATA:
	हाल RT5651_I2S1_SDP:
	हाल RT5651_I2S2_SDP:
	हाल RT5651_ADDA_CLK1:
	हाल RT5651_ADDA_CLK2:
	हाल RT5651_DMIC:
	हाल RT5651_TDM_CTL_1:
	हाल RT5651_TDM_CTL_2:
	हाल RT5651_TDM_CTL_3:
	हाल RT5651_GLB_CLK:
	हाल RT5651_PLL_CTRL1:
	हाल RT5651_PLL_CTRL2:
	हाल RT5651_PLL_MODE_1:
	हाल RT5651_PLL_MODE_2:
	हाल RT5651_PLL_MODE_3:
	हाल RT5651_PLL_MODE_4:
	हाल RT5651_PLL_MODE_5:
	हाल RT5651_PLL_MODE_6:
	हाल RT5651_PLL_MODE_7:
	हाल RT5651_DEPOP_M1:
	हाल RT5651_DEPOP_M2:
	हाल RT5651_DEPOP_M3:
	हाल RT5651_CHARGE_PUMP:
	हाल RT5651_MICBIAS:
	हाल RT5651_A_JD_CTL1:
	हाल RT5651_EQ_CTRL1:
	हाल RT5651_EQ_CTRL2:
	हाल RT5651_ALC_1:
	हाल RT5651_ALC_2:
	हाल RT5651_ALC_3:
	हाल RT5651_JD_CTRL1:
	हाल RT5651_JD_CTRL2:
	हाल RT5651_IRQ_CTRL1:
	हाल RT5651_IRQ_CTRL2:
	हाल RT5651_INT_IRQ_ST:
	हाल RT5651_GPIO_CTRL1:
	हाल RT5651_GPIO_CTRL2:
	हाल RT5651_GPIO_CTRL3:
	हाल RT5651_PGM_REG_ARR1:
	हाल RT5651_PGM_REG_ARR2:
	हाल RT5651_PGM_REG_ARR3:
	हाल RT5651_PGM_REG_ARR4:
	हाल RT5651_PGM_REG_ARR5:
	हाल RT5651_SCB_FUNC:
	हाल RT5651_SCB_CTRL:
	हाल RT5651_BASE_BACK:
	हाल RT5651_MP3_PLUS1:
	हाल RT5651_MP3_PLUS2:
	हाल RT5651_ADJ_HPF_CTRL1:
	हाल RT5651_ADJ_HPF_CTRL2:
	हाल RT5651_HP_CALIB_AMP_DET:
	हाल RT5651_HP_CALIB2:
	हाल RT5651_SV_ZCD1:
	हाल RT5651_SV_ZCD2:
	हाल RT5651_D_MISC:
	हाल RT5651_DUMMY2:
	हाल RT5651_DUMMY3:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(out_vol_tlv, -4650, 150, 0);
अटल स्थिर DECLARE_TLV_DB_MINMAX(dac_vol_tlv, -6562, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(in_vol_tlv, -3450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_MINMAX(adc_vol_tlv, -1762, 3000);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_bst_tlv, 0, 1200, 0);

/* अणु0, +20, +24, +30, +35, +40, +44, +50, +52पूर्ण dB */
अटल स्थिर DECLARE_TLV_DB_RANGE(bst_tlv,
	0, 0, TLV_DB_SCALE_ITEM(0, 0, 0),
	1, 1, TLV_DB_SCALE_ITEM(2000, 0, 0),
	2, 2, TLV_DB_SCALE_ITEM(2400, 0, 0),
	3, 5, TLV_DB_SCALE_ITEM(3000, 500, 0),
	6, 6, TLV_DB_SCALE_ITEM(4400, 0, 0),
	7, 7, TLV_DB_SCALE_ITEM(5000, 0, 0),
	8, 8, TLV_DB_SCALE_ITEM(5200, 0, 0)
);

/* Interface data select */
अटल स्थिर अक्षर * स्थिर rt5651_data_select[] = अणु
	"Normal", "Swap", "left copy to right", "right copy to left"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5651_अगर2_dac_क्रमागत, RT5651_DIG_INF_DATA,
				RT5651_IF2_DAC_SEL_SFT, rt5651_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5651_अगर2_adc_क्रमागत, RT5651_DIG_INF_DATA,
				RT5651_IF2_ADC_SEL_SFT, rt5651_data_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_snd_controls[] = अणु
	/* Headphone Output Volume */
	SOC_DOUBLE_TLV("HP Playback Volume", RT5651_HP_VOL,
		RT5651_L_VOL_SFT, RT5651_R_VOL_SFT, 39, 1, out_vol_tlv),
	/* OUTPUT Control */
	SOC_DOUBLE_TLV("OUT Playback Volume", RT5651_LOUT_CTRL1,
		RT5651_L_VOL_SFT, RT5651_R_VOL_SFT, 39, 1, out_vol_tlv),

	/* DAC Digital Volume */
	SOC_DOUBLE("DAC2 Playback Switch", RT5651_DAC2_CTRL,
		RT5651_M_DAC_L2_VOL_SFT, RT5651_M_DAC_R2_VOL_SFT, 1, 1),
	SOC_DOUBLE_TLV("DAC1 Playback Volume", RT5651_DAC1_DIG_VOL,
			RT5651_L_VOL_SFT, RT5651_R_VOL_SFT,
			175, 0, dac_vol_tlv),
	SOC_DOUBLE_TLV("Mono DAC Playback Volume", RT5651_DAC2_DIG_VOL,
			RT5651_L_VOL_SFT, RT5651_R_VOL_SFT,
			175, 0, dac_vol_tlv),
	/* IN1/IN2/IN3 Control */
	SOC_SINGLE_TLV("IN1 Boost", RT5651_IN1_IN2,
		RT5651_BST_SFT1, 8, 0, bst_tlv),
	SOC_SINGLE_TLV("IN2 Boost", RT5651_IN1_IN2,
		RT5651_BST_SFT2, 8, 0, bst_tlv),
	SOC_SINGLE_TLV("IN3 Boost", RT5651_IN3,
		RT5651_BST_SFT1, 8, 0, bst_tlv),
	/* INL/INR Volume Control */
	SOC_DOUBLE_TLV("IN Capture Volume", RT5651_INL1_INR1_VOL,
			RT5651_INL_VOL_SFT, RT5651_INR_VOL_SFT,
			31, 1, in_vol_tlv),
	/* ADC Digital Volume Control */
	SOC_DOUBLE("ADC Capture Switch", RT5651_ADC_DIG_VOL,
		RT5651_L_MUTE_SFT, RT5651_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE_TLV("ADC Capture Volume", RT5651_ADC_DIG_VOL,
			RT5651_L_VOL_SFT, RT5651_R_VOL_SFT,
			127, 0, adc_vol_tlv),
	SOC_DOUBLE_TLV("Mono ADC Capture Volume", RT5651_ADC_DATA,
			RT5651_L_VOL_SFT, RT5651_R_VOL_SFT,
			127, 0, adc_vol_tlv),
	/* ADC Boost Volume Control */
	SOC_DOUBLE_TLV("ADC Boost Gain", RT5651_ADC_BST_VOL,
			RT5651_ADC_L_BST_SFT, RT5651_ADC_R_BST_SFT,
			3, 0, adc_bst_tlv),

	/* ASRC */
	SOC_SINGLE("IF1 ASRC Switch", RT5651_PLL_MODE_1,
		RT5651_STO1_T_SFT, 1, 0),
	SOC_SINGLE("IF2 ASRC Switch", RT5651_PLL_MODE_1,
		RT5651_STO2_T_SFT, 1, 0),
	SOC_SINGLE("DMIC ASRC Switch", RT5651_PLL_MODE_1,
		RT5651_DMIC_1_M_SFT, 1, 0),

	SOC_ENUM("ADC IF2 Data Switch", rt5651_अगर2_adc_क्रमागत),
	SOC_ENUM("DAC IF2 Data Switch", rt5651_अगर2_dac_क्रमागत),
पूर्ण;

/**
 * set_dmic_clk - Set parameter of dmic.
 *
 * @w: DAPM widget.
 * @kcontrol: The kcontrol of this widget.
 * @event: Event id.
 *
 */
अटल पूर्णांक set_dmic_clk(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5651_priv *rt5651 = snd_soc_component_get_drvdata(component);
	पूर्णांक idx, rate;

	rate = rt5651->sysclk / rl6231_get_pre_भाग(rt5651->regmap,
		RT5651_ADDA_CLK1, RT5651_I2S_PD1_SFT);
	idx = rl6231_calc_dmic_clk(rate);
	अगर (idx < 0)
		dev_err(component->dev, "Failed to set DMIC clock\n");
	अन्यथा
		snd_soc_component_update_bits(component, RT5651_DMIC, RT5651_DMIC_CLK_MASK,
					idx << RT5651_DMIC_CLK_SFT);

	वापस idx;
पूर्ण

/* Digital Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt5651_sto1_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5651_STO1_ADC_MIXER,
			RT5651_M_STO1_ADC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5651_STO1_ADC_MIXER,
			RT5651_M_STO1_ADC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_sto1_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5651_STO1_ADC_MIXER,
			RT5651_M_STO1_ADC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5651_STO1_ADC_MIXER,
			RT5651_M_STO1_ADC_R2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_sto2_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5651_STO2_ADC_MIXER,
			RT5651_M_STO2_ADC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5651_STO2_ADC_MIXER,
			RT5651_M_STO2_ADC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_sto2_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5651_STO2_ADC_MIXER,
			RT5651_M_STO2_ADC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5651_STO2_ADC_MIXER,
			RT5651_M_STO2_ADC_R2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("Stereo ADC Switch", RT5651_AD_DA_MIXER,
			RT5651_M_ADCMIX_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("INF1 Switch", RT5651_AD_DA_MIXER,
			RT5651_M_IF1_DAC_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("Stereo ADC Switch", RT5651_AD_DA_MIXER,
			RT5651_M_ADCMIX_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("INF1 Switch", RT5651_AD_DA_MIXER,
			RT5651_M_IF1_DAC_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_sto_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5651_STO_DAC_MIXER,
			RT5651_M_DAC_L1_MIXL_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5651_STO_DAC_MIXER,
			RT5651_M_DAC_L2_MIXL_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5651_STO_DAC_MIXER,
			RT5651_M_DAC_R1_MIXL_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_sto_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5651_STO_DAC_MIXER,
			RT5651_M_DAC_R1_MIXR_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5651_STO_DAC_MIXER,
			RT5651_M_DAC_R2_MIXR_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5651_STO_DAC_MIXER,
			RT5651_M_DAC_L1_MIXR_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_dd_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5651_DD_MIXER,
			RT5651_M_STO_DD_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5651_DD_MIXER,
			RT5651_M_STO_DD_L2_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5651_DD_MIXER,
			RT5651_M_STO_DD_R2_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_dd_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5651_DD_MIXER,
			RT5651_M_STO_DD_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5651_DD_MIXER,
			RT5651_M_STO_DD_R2_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5651_DD_MIXER,
			RT5651_M_STO_DD_L2_R_SFT, 1, 1),
पूर्ण;

/* Analog Input Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt5651_rec_l_mix[] = अणु
	SOC_DAPM_SINGLE("INL1 Switch", RT5651_REC_L2_MIXER,
			RT5651_M_IN1_L_RM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST3 Switch", RT5651_REC_L2_MIXER,
			RT5651_M_BST3_RM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5651_REC_L2_MIXER,
			RT5651_M_BST2_RM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5651_REC_L2_MIXER,
			RT5651_M_BST1_RM_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_rec_r_mix[] = अणु
	SOC_DAPM_SINGLE("INR1 Switch", RT5651_REC_R2_MIXER,
			RT5651_M_IN1_R_RM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST3 Switch", RT5651_REC_R2_MIXER,
			RT5651_M_BST3_RM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5651_REC_R2_MIXER,
			RT5651_M_BST2_RM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5651_REC_R2_MIXER,
			RT5651_M_BST1_RM_R_SFT, 1, 1),
पूर्ण;

/* Analog Output Mixer */

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_out_l_mix[] = अणु
	SOC_DAPM_SINGLE("BST1 Switch", RT5651_OUT_L3_MIXER,
			RT5651_M_BST1_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5651_OUT_L3_MIXER,
			RT5651_M_BST2_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("INL1 Switch", RT5651_OUT_L3_MIXER,
			RT5651_M_IN1_L_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("REC MIXL Switch", RT5651_OUT_L3_MIXER,
			RT5651_M_RM_L_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5651_OUT_L3_MIXER,
			RT5651_M_DAC_L1_OM_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_out_r_mix[] = अणु
	SOC_DAPM_SINGLE("BST2 Switch", RT5651_OUT_R3_MIXER,
			RT5651_M_BST2_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5651_OUT_R3_MIXER,
			RT5651_M_BST1_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("INR1 Switch", RT5651_OUT_R3_MIXER,
			RT5651_M_IN1_R_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("REC MIXR Switch", RT5651_OUT_R3_MIXER,
			RT5651_M_RM_R_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5651_OUT_R3_MIXER,
			RT5651_M_DAC_R1_OM_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_hpo_mix[] = अणु
	SOC_DAPM_SINGLE("HPO MIX DAC1 Switch", RT5651_HPO_MIXER,
			RT5651_M_DAC1_HM_SFT, 1, 1),
	SOC_DAPM_SINGLE("HPO MIX HPVOL Switch", RT5651_HPO_MIXER,
			RT5651_M_HPVOL_HM_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_lout_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5651_LOUT_MIXER,
			RT5651_M_DAC_L1_LM_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5651_LOUT_MIXER,
			RT5651_M_DAC_R1_LM_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUTVOL L Switch", RT5651_LOUT_MIXER,
			RT5651_M_OV_L_LM_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUTVOL R Switch", RT5651_LOUT_MIXER,
			RT5651_M_OV_R_LM_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new outvol_l_control =
	SOC_DAPM_SINGLE("Switch", RT5651_LOUT_CTRL1,
			RT5651_VOL_L_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new outvol_r_control =
	SOC_DAPM_SINGLE("Switch", RT5651_LOUT_CTRL1,
			RT5651_VOL_R_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new lout_l_mute_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT5651_LOUT_CTRL1,
				    RT5651_L_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new lout_r_mute_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT5651_LOUT_CTRL1,
				    RT5651_R_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new hpovol_l_control =
	SOC_DAPM_SINGLE("Switch", RT5651_HP_VOL,
			RT5651_VOL_L_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new hpovol_r_control =
	SOC_DAPM_SINGLE("Switch", RT5651_HP_VOL,
			RT5651_VOL_R_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new hpo_l_mute_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT5651_HP_VOL,
				    RT5651_L_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new hpo_r_mute_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT5651_HP_VOL,
				    RT5651_R_MUTE_SFT, 1, 1);

/* Stereo ADC source */
अटल स्थिर अक्षर * स्थिर rt5651_stereo1_adc1_src[] = अणु"DD MIX", "ADC"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5651_stereo1_adc1_क्रमागत, RT5651_STO1_ADC_MIXER,
	RT5651_STO1_ADC_1_SRC_SFT, rt5651_stereo1_adc1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_sto1_adc_l1_mux =
	SOC_DAPM_ENUM("Stereo1 ADC L1 source", rt5651_stereo1_adc1_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_sto1_adc_r1_mux =
	SOC_DAPM_ENUM("Stereo1 ADC R1 source", rt5651_stereo1_adc1_क्रमागत);

अटल स्थिर अक्षर * स्थिर rt5651_stereo1_adc2_src[] = अणु"DMIC", "DD MIX"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5651_stereo1_adc2_क्रमागत, RT5651_STO1_ADC_MIXER,
	RT5651_STO1_ADC_2_SRC_SFT, rt5651_stereo1_adc2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_sto1_adc_l2_mux =
	SOC_DAPM_ENUM("Stereo1 ADC L2 source", rt5651_stereo1_adc2_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_sto1_adc_r2_mux =
	SOC_DAPM_ENUM("Stereo1 ADC R2 source", rt5651_stereo1_adc2_क्रमागत);

/* Mono ADC source */
अटल स्थिर अक्षर * स्थिर rt5651_sto2_adc_l1_src[] = अणु"DD MIXL", "ADCL"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5651_sto2_adc_l1_क्रमागत, RT5651_STO1_ADC_MIXER,
	RT5651_STO2_ADC_L1_SRC_SFT, rt5651_sto2_adc_l1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_sto2_adc_l1_mux =
	SOC_DAPM_ENUM("Stereo2 ADC1 left source", rt5651_sto2_adc_l1_क्रमागत);

अटल स्थिर अक्षर * स्थिर rt5651_sto2_adc_l2_src[] = अणु"DMIC L", "DD MIXL"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5651_sto2_adc_l2_क्रमागत, RT5651_STO1_ADC_MIXER,
	RT5651_STO2_ADC_L2_SRC_SFT, rt5651_sto2_adc_l2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_sto2_adc_l2_mux =
	SOC_DAPM_ENUM("Stereo2 ADC2 left source", rt5651_sto2_adc_l2_क्रमागत);

अटल स्थिर अक्षर * स्थिर rt5651_sto2_adc_r1_src[] = अणु"DD MIXR", "ADCR"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5651_sto2_adc_r1_क्रमागत, RT5651_STO1_ADC_MIXER,
	RT5651_STO2_ADC_R1_SRC_SFT, rt5651_sto2_adc_r1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_sto2_adc_r1_mux =
	SOC_DAPM_ENUM("Stereo2 ADC1 right source", rt5651_sto2_adc_r1_क्रमागत);

अटल स्थिर अक्षर * स्थिर rt5651_sto2_adc_r2_src[] = अणु"DMIC R", "DD MIXR"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5651_sto2_adc_r2_क्रमागत, RT5651_STO1_ADC_MIXER,
	RT5651_STO2_ADC_R2_SRC_SFT, rt5651_sto2_adc_r2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_sto2_adc_r2_mux =
	SOC_DAPM_ENUM("Stereo2 ADC2 right source", rt5651_sto2_adc_r2_क्रमागत);

/* DAC2 channel source */

अटल स्थिर अक्षर * स्थिर rt5651_dac_src[] = अणु"IF1", "IF2"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5651_dac_l2_क्रमागत, RT5651_DAC2_CTRL,
				RT5651_SEL_DAC_L2_SFT, rt5651_dac_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_dac_l2_mux =
	SOC_DAPM_ENUM("DAC2 left channel source", rt5651_dac_l2_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5651_dac_r2_क्रमागत, RT5651_DAC2_CTRL,
	RT5651_SEL_DAC_R2_SFT, rt5651_dac_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_dac_r2_mux =
	SOC_DAPM_ENUM("DAC2 right channel source", rt5651_dac_r2_क्रमागत);

/* IF2_ADC channel source */

अटल स्थिर अक्षर * स्थिर rt5651_adc_src[] = अणु"IF1 ADC1", "IF1 ADC2"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5651_अगर2_adc_src_क्रमागत, RT5651_DIG_INF_DATA,
				RT5651_IF2_ADC_SRC_SFT, rt5651_adc_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_अगर2_adc_src_mux =
	SOC_DAPM_ENUM("IF2 ADC channel source", rt5651_अगर2_adc_src_क्रमागत);

/* PDM select */
अटल स्थिर अक्षर * स्थिर rt5651_pdm_sel[] = अणु"DD MIX", "Stereo DAC MIX"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5651_pdm_l_sel_क्रमागत, RT5651_PDM_CTL,
	RT5651_PDM_L_SEL_SFT, rt5651_pdm_sel);

अटल SOC_ENUM_SINGLE_DECL(
	rt5651_pdm_r_sel_क्रमागत, RT5651_PDM_CTL,
	RT5651_PDM_R_SEL_SFT, rt5651_pdm_sel);

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_pdm_l_mux =
	SOC_DAPM_ENUM("PDM L select", rt5651_pdm_l_sel_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5651_pdm_r_mux =
	SOC_DAPM_ENUM("PDM R select", rt5651_pdm_r_sel_क्रमागत);

अटल पूर्णांक rt5651_amp_घातer_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5651_priv *rt5651 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* depop parameters */
		regmap_update_bits(rt5651->regmap, RT5651_PR_BASE +
			RT5651_CHPUMP_INT_REG1, 0x0700, 0x0200);
		regmap_update_bits(rt5651->regmap, RT5651_DEPOP_M2,
			RT5651_DEPOP_MASK, RT5651_DEPOP_MAN);
		regmap_update_bits(rt5651->regmap, RT5651_DEPOP_M1,
			RT5651_HP_CP_MASK | RT5651_HP_SG_MASK |
			RT5651_HP_CB_MASK, RT5651_HP_CP_PU |
			RT5651_HP_SG_DIS | RT5651_HP_CB_PU);
		regmap_ग_लिखो(rt5651->regmap, RT5651_PR_BASE +
				RT5651_HP_DCC_INT1, 0x9f00);
		/* headphone amp घातer on */
		regmap_update_bits(rt5651->regmap, RT5651_PWR_ANLG1,
			RT5651_PWR_FV1 | RT5651_PWR_FV2, 0);
		regmap_update_bits(rt5651->regmap, RT5651_PWR_ANLG1,
			RT5651_PWR_HA,
			RT5651_PWR_HA);
		usleep_range(10000, 15000);
		regmap_update_bits(rt5651->regmap, RT5651_PWR_ANLG1,
			RT5651_PWR_FV1 | RT5651_PWR_FV2 ,
			RT5651_PWR_FV1 | RT5651_PWR_FV2);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5651_hp_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5651_priv *rt5651 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* headphone unmute sequence */
		regmap_update_bits(rt5651->regmap, RT5651_DEPOP_M2,
			RT5651_DEPOP_MASK | RT5651_DIG_DP_MASK,
			RT5651_DEPOP_AUTO | RT5651_DIG_DP_EN);
		regmap_update_bits(rt5651->regmap, RT5651_CHARGE_PUMP,
			RT5651_PM_HP_MASK, RT5651_PM_HP_HV);

		regmap_update_bits(rt5651->regmap, RT5651_DEPOP_M3,
			RT5651_CP_FQ1_MASK | RT5651_CP_FQ2_MASK |
			RT5651_CP_FQ3_MASK,
			(RT5651_CP_FQ_192_KHZ << RT5651_CP_FQ1_SFT) |
			(RT5651_CP_FQ_12_KHZ << RT5651_CP_FQ2_SFT) |
			(RT5651_CP_FQ_192_KHZ << RT5651_CP_FQ3_SFT));

		regmap_ग_लिखो(rt5651->regmap, RT5651_PR_BASE +
			RT5651_MAMP_INT_REG2, 0x1c00);
		regmap_update_bits(rt5651->regmap, RT5651_DEPOP_M1,
			RT5651_HP_CP_MASK | RT5651_HP_SG_MASK,
			RT5651_HP_CP_PD | RT5651_HP_SG_EN);
		regmap_update_bits(rt5651->regmap, RT5651_PR_BASE +
			RT5651_CHPUMP_INT_REG1, 0x0700, 0x0400);
		rt5651->hp_mute = false;
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		rt5651->hp_mute = true;
		usleep_range(70000, 75000);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5651_hp_post_event(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु

	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5651_priv *rt5651 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		अगर (!rt5651->hp_mute)
			usleep_range(80000, 85000);

		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5651_bst1_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, RT5651_PWR_ANLG2,
			RT5651_PWR_BST1_OP2, RT5651_PWR_BST1_OP2);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT5651_PWR_ANLG2,
			RT5651_PWR_BST1_OP2, 0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5651_bst2_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, RT5651_PWR_ANLG2,
			RT5651_PWR_BST2_OP2, RT5651_PWR_BST2_OP2);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT5651_PWR_ANLG2,
			RT5651_PWR_BST2_OP2, 0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5651_bst3_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, RT5651_PWR_ANLG2,
			RT5651_PWR_BST3_OP2, RT5651_PWR_BST3_OP2);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT5651_PWR_ANLG2,
			RT5651_PWR_BST3_OP2, 0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget rt5651_dapm_widमाला_लो[] = अणु
	/* ASRC */
	SND_SOC_DAPM_SUPPLY_S("I2S1 ASRC", 1, RT5651_PLL_MODE_2,
			      15, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("I2S2 ASRC", 1, RT5651_PLL_MODE_2,
			      14, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("STO1 DAC ASRC", 1, RT5651_PLL_MODE_2,
			      13, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("STO2 DAC ASRC", 1, RT5651_PLL_MODE_2,
			      12, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ADC ASRC", 1, RT5651_PLL_MODE_2,
			      11, 0, शून्य, 0),

	/* micbias */
	SND_SOC_DAPM_SUPPLY("LDO", RT5651_PWR_ANLG1,
			RT5651_PWR_LDO_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("micbias1", RT5651_PWR_ANLG2,
			RT5651_PWR_MB1_BIT, 0, शून्य, 0),
	/* Input Lines */
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("MIC3"),

	SND_SOC_DAPM_INPUT("IN1P"),
	SND_SOC_DAPM_INPUT("IN2P"),
	SND_SOC_DAPM_INPUT("IN2N"),
	SND_SOC_DAPM_INPUT("IN3P"),
	SND_SOC_DAPM_INPUT("DMIC L1"),
	SND_SOC_DAPM_INPUT("DMIC R1"),
	SND_SOC_DAPM_SUPPLY("DMIC CLK", RT5651_DMIC, RT5651_DMIC_1_EN_SFT,
			    0, set_dmic_clk, SND_SOC_DAPM_PRE_PMU),
	/* Boost */
	SND_SOC_DAPM_PGA_E("BST1", RT5651_PWR_ANLG2,
		RT5651_PWR_BST1_BIT, 0, शून्य, 0, rt5651_bst1_event,
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_E("BST2", RT5651_PWR_ANLG2,
		RT5651_PWR_BST2_BIT, 0, शून्य, 0, rt5651_bst2_event,
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_E("BST3", RT5651_PWR_ANLG2,
		RT5651_PWR_BST3_BIT, 0, शून्य, 0, rt5651_bst3_event,
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	/* Input Volume */
	SND_SOC_DAPM_PGA("INL1 VOL", RT5651_PWR_VOL,
			 RT5651_PWR_IN1_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("INR1 VOL", RT5651_PWR_VOL,
			 RT5651_PWR_IN1_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("INL2 VOL", RT5651_PWR_VOL,
			 RT5651_PWR_IN2_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("INR2 VOL", RT5651_PWR_VOL,
			 RT5651_PWR_IN2_R_BIT, 0, शून्य, 0),

	/* REC Mixer */
	SND_SOC_DAPM_MIXER("RECMIXL", RT5651_PWR_MIXER, RT5651_PWR_RM_L_BIT, 0,
			   rt5651_rec_l_mix, ARRAY_SIZE(rt5651_rec_l_mix)),
	SND_SOC_DAPM_MIXER("RECMIXR", RT5651_PWR_MIXER, RT5651_PWR_RM_R_BIT, 0,
			   rt5651_rec_r_mix, ARRAY_SIZE(rt5651_rec_r_mix)),
	/* ADCs */
	SND_SOC_DAPM_ADC("ADC L", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC R", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_SUPPLY("ADC L Power", RT5651_PWR_DIG1,
			    RT5651_PWR_ADC_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC R Power", RT5651_PWR_DIG1,
			    RT5651_PWR_ADC_R_BIT, 0, शून्य, 0),
	/* ADC Mux */
	SND_SOC_DAPM_MUX("Stereo1 ADC L2 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5651_sto1_adc_l2_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC R2 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5651_sto1_adc_r2_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC L1 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5651_sto1_adc_l1_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC R1 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5651_sto1_adc_r1_mux),
	SND_SOC_DAPM_MUX("Stereo2 ADC L2 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5651_sto2_adc_l2_mux),
	SND_SOC_DAPM_MUX("Stereo2 ADC L1 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5651_sto2_adc_l1_mux),
	SND_SOC_DAPM_MUX("Stereo2 ADC R1 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5651_sto2_adc_r1_mux),
	SND_SOC_DAPM_MUX("Stereo2 ADC R2 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5651_sto2_adc_r2_mux),
	/* ADC Mixer */
	SND_SOC_DAPM_SUPPLY("Stereo1 Filter", RT5651_PWR_DIG2,
			    RT5651_PWR_ADC_STO1_F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Stereo2 Filter", RT5651_PWR_DIG2,
			    RT5651_PWR_ADC_STO2_F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Stereo1 ADC MIXL", SND_SOC_NOPM, 0, 0,
			   rt5651_sto1_adc_l_mix,
			   ARRAY_SIZE(rt5651_sto1_adc_l_mix)),
	SND_SOC_DAPM_MIXER("Stereo1 ADC MIXR", SND_SOC_NOPM, 0, 0,
			   rt5651_sto1_adc_r_mix,
			   ARRAY_SIZE(rt5651_sto1_adc_r_mix)),
	SND_SOC_DAPM_MIXER("Stereo2 ADC MIXL", SND_SOC_NOPM, 0, 0,
			   rt5651_sto2_adc_l_mix,
			   ARRAY_SIZE(rt5651_sto2_adc_l_mix)),
	SND_SOC_DAPM_MIXER("Stereo2 ADC MIXR", SND_SOC_NOPM, 0, 0,
			   rt5651_sto2_adc_r_mix,
			   ARRAY_SIZE(rt5651_sto2_adc_r_mix)),

	/* Digital Interface */
	SND_SOC_DAPM_SUPPLY("I2S1", RT5651_PWR_DIG1,
			    RT5651_PWR_I2S1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1 L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1 R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 ADC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC2 L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC2 R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 ADC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("I2S2", RT5651_PWR_DIG1,
			    RT5651_PWR_I2S2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MUX("IF2 ADC", SND_SOC_NOPM, 0, 0,
			 &rt5651_अगर2_adc_src_mux),

	/* Digital Interface Select */

	SND_SOC_DAPM_MUX("PDM L Mux", RT5651_PDM_CTL,
			 RT5651_M_PDM_L_SFT, 1, &rt5651_pdm_l_mux),
	SND_SOC_DAPM_MUX("PDM R Mux", RT5651_PDM_CTL,
			 RT5651_M_PDM_R_SFT, 1, &rt5651_pdm_r_mux),
	/* Audio Interface */
	SND_SOC_DAPM_AIF_IN("AIF1RX", "AIF1 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX", "AIF1 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF2RX", "AIF2 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2TX", "AIF2 Capture", 0, SND_SOC_NOPM, 0, 0),

	/* Audio DSP */
	SND_SOC_DAPM_PGA("Audio DSP", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* Output Side */
	/* DAC mixer beक्रमe sound effect  */
	SND_SOC_DAPM_MIXER("DAC MIXL", SND_SOC_NOPM, 0, 0,
			   rt5651_dac_l_mix, ARRAY_SIZE(rt5651_dac_l_mix)),
	SND_SOC_DAPM_MIXER("DAC MIXR", SND_SOC_NOPM, 0, 0,
			   rt5651_dac_r_mix, ARRAY_SIZE(rt5651_dac_r_mix)),

	/* DAC2 channel Mux */
	SND_SOC_DAPM_MUX("DAC L2 Mux", SND_SOC_NOPM, 0, 0, &rt5651_dac_l2_mux),
	SND_SOC_DAPM_MUX("DAC R2 Mux", SND_SOC_NOPM, 0, 0, &rt5651_dac_r2_mux),
	SND_SOC_DAPM_PGA("DAC L2 Volume", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DAC R2 Volume", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("Stero1 DAC Power", RT5651_PWR_DIG2,
			    RT5651_PWR_DAC_STO1_F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Stero2 DAC Power", RT5651_PWR_DIG2,
			    RT5651_PWR_DAC_STO2_F_BIT, 0, शून्य, 0),
	/* DAC Mixer */
	SND_SOC_DAPM_MIXER("Stereo DAC MIXL", SND_SOC_NOPM, 0, 0,
			   rt5651_sto_dac_l_mix,
			   ARRAY_SIZE(rt5651_sto_dac_l_mix)),
	SND_SOC_DAPM_MIXER("Stereo DAC MIXR", SND_SOC_NOPM, 0, 0,
			   rt5651_sto_dac_r_mix,
			   ARRAY_SIZE(rt5651_sto_dac_r_mix)),
	SND_SOC_DAPM_MIXER("DD MIXL", SND_SOC_NOPM, 0, 0,
			   rt5651_dd_dac_l_mix,
			   ARRAY_SIZE(rt5651_dd_dac_l_mix)),
	SND_SOC_DAPM_MIXER("DD MIXR", SND_SOC_NOPM, 0, 0,
			   rt5651_dd_dac_r_mix,
			   ARRAY_SIZE(rt5651_dd_dac_r_mix)),

	/* DACs */
	SND_SOC_DAPM_DAC("DAC L1", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC R1", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_SUPPLY("DAC L1 Power", RT5651_PWR_DIG1,
			    RT5651_PWR_DAC_L1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC R1 Power", RT5651_PWR_DIG1,
			    RT5651_PWR_DAC_R1_BIT, 0, शून्य, 0),
	/* OUT Mixer */
	SND_SOC_DAPM_MIXER("OUT MIXL", RT5651_PWR_MIXER, RT5651_PWR_OM_L_BIT,
			   0, rt5651_out_l_mix, ARRAY_SIZE(rt5651_out_l_mix)),
	SND_SOC_DAPM_MIXER("OUT MIXR", RT5651_PWR_MIXER, RT5651_PWR_OM_R_BIT,
			   0, rt5651_out_r_mix, ARRAY_SIZE(rt5651_out_r_mix)),
	/* Ouput Volume */
	SND_SOC_DAPM_SWITCH("OUTVOL L", RT5651_PWR_VOL,
			    RT5651_PWR_OV_L_BIT, 0, &outvol_l_control),
	SND_SOC_DAPM_SWITCH("OUTVOL R", RT5651_PWR_VOL,
			    RT5651_PWR_OV_R_BIT, 0, &outvol_r_control),
	SND_SOC_DAPM_SWITCH("HPOVOL L", RT5651_PWR_VOL,
			    RT5651_PWR_HV_L_BIT, 0, &hpovol_l_control),
	SND_SOC_DAPM_SWITCH("HPOVOL R", RT5651_PWR_VOL,
			    RT5651_PWR_HV_R_BIT, 0, &hpovol_r_control),
	SND_SOC_DAPM_PGA("INL1", RT5651_PWR_VOL,
			 RT5651_PWR_IN1_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("INR1", RT5651_PWR_VOL,
			 RT5651_PWR_IN1_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("INL2", RT5651_PWR_VOL,
			 RT5651_PWR_IN2_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("INR2", RT5651_PWR_VOL,
			 RT5651_PWR_IN2_R_BIT, 0, शून्य, 0),
	/* HPO/LOUT/Mono Mixer */
	SND_SOC_DAPM_MIXER("HPOL MIX", SND_SOC_NOPM, 0, 0,
			   rt5651_hpo_mix, ARRAY_SIZE(rt5651_hpo_mix)),
	SND_SOC_DAPM_MIXER("HPOR MIX", SND_SOC_NOPM, 0, 0,
			   rt5651_hpo_mix, ARRAY_SIZE(rt5651_hpo_mix)),
	SND_SOC_DAPM_SUPPLY("HP L Amp", RT5651_PWR_ANLG1,
			    RT5651_PWR_HP_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("HP R Amp", RT5651_PWR_ANLG1,
			    RT5651_PWR_HP_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("LOUT MIX", RT5651_PWR_ANLG1, RT5651_PWR_LM_BIT, 0,
			   rt5651_lout_mix, ARRAY_SIZE(rt5651_lout_mix)),

	SND_SOC_DAPM_SUPPLY("Amp Power", RT5651_PWR_ANLG1,
			    RT5651_PWR_HA_BIT, 0, rt5651_amp_घातer_event,
			    SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_S("HP Amp", 1, SND_SOC_NOPM, 0, 0, rt5651_hp_event,
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SWITCH("HPO L Playback", SND_SOC_NOPM, 0, 0,
			    &hpo_l_mute_control),
	SND_SOC_DAPM_SWITCH("HPO R Playback", SND_SOC_NOPM, 0, 0,
			    &hpo_r_mute_control),
	SND_SOC_DAPM_SWITCH("LOUT L Playback", SND_SOC_NOPM, 0, 0,
			    &lout_l_mute_control),
	SND_SOC_DAPM_SWITCH("LOUT R Playback", SND_SOC_NOPM, 0, 0,
			    &lout_r_mute_control),
	SND_SOC_DAPM_POST("HP Post", rt5651_hp_post_event),

	/* Output Lines */
	SND_SOC_DAPM_OUTPUT("HPOL"),
	SND_SOC_DAPM_OUTPUT("HPOR"),
	SND_SOC_DAPM_OUTPUT("LOUTL"),
	SND_SOC_DAPM_OUTPUT("LOUTR"),
	SND_SOC_DAPM_OUTPUT("PDML"),
	SND_SOC_DAPM_OUTPUT("PDMR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5651_dapm_routes[] = अणु
	अणु"Stero1 DAC Power", शून्य, "STO1 DAC ASRC"पूर्ण,
	अणु"Stero2 DAC Power", शून्य, "STO2 DAC ASRC"पूर्ण,
	अणु"I2S1", शून्य, "I2S1 ASRC"पूर्ण,
	अणु"I2S2", शून्य, "I2S2 ASRC"पूर्ण,

	अणु"IN1P", शून्य, "LDO"पूर्ण,
	अणु"IN2P", शून्य, "LDO"पूर्ण,
	अणु"IN3P", शून्य, "LDO"पूर्ण,

	अणु"IN1P", शून्य, "MIC1"पूर्ण,
	अणु"IN2P", शून्य, "MIC2"पूर्ण,
	अणु"IN2N", शून्य, "MIC2"पूर्ण,
	अणु"IN3P", शून्य, "MIC3"पूर्ण,

	अणु"BST1", शून्य, "IN1P"पूर्ण,
	अणु"BST2", शून्य, "IN2P"पूर्ण,
	अणु"BST2", शून्य, "IN2N"पूर्ण,
	अणु"BST3", शून्य, "IN3P"पूर्ण,

	अणु"INL1 VOL", शून्य, "IN2P"पूर्ण,
	अणु"INR1 VOL", शून्य, "IN2N"पूर्ण,

	अणु"RECMIXL", "INL1 Switch", "INL1 VOL"पूर्ण,
	अणु"RECMIXL", "BST3 Switch", "BST3"पूर्ण,
	अणु"RECMIXL", "BST2 Switch", "BST2"पूर्ण,
	अणु"RECMIXL", "BST1 Switch", "BST1"पूर्ण,

	अणु"RECMIXR", "INR1 Switch", "INR1 VOL"पूर्ण,
	अणु"RECMIXR", "BST3 Switch", "BST3"पूर्ण,
	अणु"RECMIXR", "BST2 Switch", "BST2"पूर्ण,
	अणु"RECMIXR", "BST1 Switch", "BST1"पूर्ण,

	अणु"ADC L", शून्य, "RECMIXL"पूर्ण,
	अणु"ADC L", शून्य, "ADC L Power"पूर्ण,
	अणु"ADC R", शून्य, "RECMIXR"पूर्ण,
	अणु"ADC R", शून्य, "ADC R Power"पूर्ण,

	अणु"DMIC L1", शून्य, "DMIC CLK"पूर्ण,
	अणु"DMIC R1", शून्य, "DMIC CLK"पूर्ण,

	अणु"Stereo1 ADC L2 Mux", "DMIC", "DMIC L1"पूर्ण,
	अणु"Stereo1 ADC L2 Mux", "DD MIX", "DD MIXL"पूर्ण,
	अणु"Stereo1 ADC L1 Mux", "ADC", "ADC L"पूर्ण,
	अणु"Stereo1 ADC L1 Mux", "DD MIX", "DD MIXL"पूर्ण,

	अणु"Stereo1 ADC R1 Mux", "ADC", "ADC R"पूर्ण,
	अणु"Stereo1 ADC R1 Mux", "DD MIX", "DD MIXR"पूर्ण,
	अणु"Stereo1 ADC R2 Mux", "DMIC", "DMIC R1"पूर्ण,
	अणु"Stereo1 ADC R2 Mux", "DD MIX", "DD MIXR"पूर्ण,

	अणु"Stereo2 ADC L2 Mux", "DMIC L", "DMIC L1"पूर्ण,
	अणु"Stereo2 ADC L2 Mux", "DD MIXL", "DD MIXL"पूर्ण,
	अणु"Stereo2 ADC L1 Mux", "DD MIXL", "DD MIXL"पूर्ण,
	अणु"Stereo2 ADC L1 Mux", "ADCL", "ADC L"पूर्ण,

	अणु"Stereo2 ADC R1 Mux", "DD MIXR", "DD MIXR"पूर्ण,
	अणु"Stereo2 ADC R1 Mux", "ADCR", "ADC R"पूर्ण,
	अणु"Stereo2 ADC R2 Mux", "DMIC R", "DMIC R1"पूर्ण,
	अणु"Stereo2 ADC R2 Mux", "DD MIXR", "DD MIXR"पूर्ण,

	अणु"Stereo1 ADC MIXL", "ADC1 Switch", "Stereo1 ADC L1 Mux"पूर्ण,
	अणु"Stereo1 ADC MIXL", "ADC2 Switch", "Stereo1 ADC L2 Mux"पूर्ण,
	अणु"Stereo1 ADC MIXL", शून्य, "Stereo1 Filter"पूर्ण,
	अणु"Stereo1 Filter", शून्य, "ADC ASRC"पूर्ण,

	अणु"Stereo1 ADC MIXR", "ADC1 Switch", "Stereo1 ADC R1 Mux"पूर्ण,
	अणु"Stereo1 ADC MIXR", "ADC2 Switch", "Stereo1 ADC R2 Mux"पूर्ण,
	अणु"Stereo1 ADC MIXR", शून्य, "Stereo1 Filter"पूर्ण,

	अणु"Stereo2 ADC MIXL", "ADC1 Switch", "Stereo2 ADC L1 Mux"पूर्ण,
	अणु"Stereo2 ADC MIXL", "ADC2 Switch", "Stereo2 ADC L2 Mux"पूर्ण,
	अणु"Stereo2 ADC MIXL", शून्य, "Stereo2 Filter"पूर्ण,
	अणु"Stereo2 Filter", शून्य, "ADC ASRC"पूर्ण,

	अणु"Stereo2 ADC MIXR", "ADC1 Switch", "Stereo2 ADC R1 Mux"पूर्ण,
	अणु"Stereo2 ADC MIXR", "ADC2 Switch", "Stereo2 ADC R2 Mux"पूर्ण,
	अणु"Stereo2 ADC MIXR", शून्य, "Stereo2 Filter"पूर्ण,

	अणु"IF1 ADC2", शून्य, "Stereo2 ADC MIXL"पूर्ण,
	अणु"IF1 ADC2", शून्य, "Stereo2 ADC MIXR"पूर्ण,
	अणु"IF1 ADC1", शून्य, "Stereo1 ADC MIXL"पूर्ण,
	अणु"IF1 ADC1", शून्य, "Stereo1 ADC MIXR"पूर्ण,

	अणु"IF1 ADC1", शून्य, "I2S1"पूर्ण,

	अणु"IF2 ADC", "IF1 ADC1", "IF1 ADC1"पूर्ण,
	अणु"IF2 ADC", "IF1 ADC2", "IF1 ADC2"पूर्ण,
	अणु"IF2 ADC", शून्य, "I2S2"पूर्ण,

	अणु"AIF1TX", शून्य, "IF1 ADC1"पूर्ण,
	अणु"AIF1TX", शून्य, "IF1 ADC2"पूर्ण,
	अणु"AIF2TX", शून्य, "IF2 ADC"पूर्ण,

	अणु"IF1 DAC", शून्य, "AIF1RX"पूर्ण,
	अणु"IF1 DAC", शून्य, "I2S1"पूर्ण,
	अणु"IF2 DAC", शून्य, "AIF2RX"पूर्ण,
	अणु"IF2 DAC", शून्य, "I2S2"पूर्ण,

	अणु"IF1 DAC1 L", शून्य, "IF1 DAC"पूर्ण,
	अणु"IF1 DAC1 R", शून्य, "IF1 DAC"पूर्ण,
	अणु"IF1 DAC2 L", शून्य, "IF1 DAC"पूर्ण,
	अणु"IF1 DAC2 R", शून्य, "IF1 DAC"पूर्ण,
	अणु"IF2 DAC L", शून्य, "IF2 DAC"पूर्ण,
	अणु"IF2 DAC R", शून्य, "IF2 DAC"पूर्ण,

	अणु"DAC MIXL", "Stereo ADC Switch", "Stereo1 ADC MIXL"पूर्ण,
	अणु"DAC MIXL", "INF1 Switch", "IF1 DAC1 L"पूर्ण,
	अणु"DAC MIXR", "Stereo ADC Switch", "Stereo1 ADC MIXR"पूर्ण,
	अणु"DAC MIXR", "INF1 Switch", "IF1 DAC1 R"पूर्ण,

	अणु"Audio DSP", शून्य, "DAC MIXL"पूर्ण,
	अणु"Audio DSP", शून्य, "DAC MIXR"पूर्ण,

	अणु"DAC L2 Mux", "IF1", "IF1 DAC2 L"पूर्ण,
	अणु"DAC L2 Mux", "IF2", "IF2 DAC L"पूर्ण,
	अणु"DAC L2 Volume", शून्य, "DAC L2 Mux"पूर्ण,

	अणु"DAC R2 Mux", "IF1", "IF1 DAC2 R"पूर्ण,
	अणु"DAC R2 Mux", "IF2", "IF2 DAC R"पूर्ण,
	अणु"DAC R2 Volume", शून्य, "DAC R2 Mux"पूर्ण,

	अणु"Stereo DAC MIXL", "DAC L1 Switch", "Audio DSP"पूर्ण,
	अणु"Stereo DAC MIXL", "DAC L2 Switch", "DAC L2 Volume"पूर्ण,
	अणु"Stereo DAC MIXL", "DAC R1 Switch", "DAC MIXR"पूर्ण,
	अणु"Stereo DAC MIXL", शून्य, "Stero1 DAC Power"पूर्ण,
	अणु"Stereo DAC MIXL", शून्य, "Stero2 DAC Power"पूर्ण,
	अणु"Stereo DAC MIXR", "DAC R1 Switch", "Audio DSP"पूर्ण,
	अणु"Stereo DAC MIXR", "DAC R2 Switch", "DAC R2 Volume"पूर्ण,
	अणु"Stereo DAC MIXR", "DAC L1 Switch", "DAC MIXL"पूर्ण,
	अणु"Stereo DAC MIXR", शून्य, "Stero1 DAC Power"पूर्ण,
	अणु"Stereo DAC MIXR", शून्य, "Stero2 DAC Power"पूर्ण,

	अणु"PDM L Mux", "Stereo DAC MIX", "Stereo DAC MIXL"पूर्ण,
	अणु"PDM L Mux", "DD MIX", "DAC MIXL"पूर्ण,
	अणु"PDM R Mux", "Stereo DAC MIX", "Stereo DAC MIXR"पूर्ण,
	अणु"PDM R Mux", "DD MIX", "DAC MIXR"पूर्ण,

	अणु"DAC L1", शून्य, "Stereo DAC MIXL"पूर्ण,
	अणु"DAC L1", शून्य, "DAC L1 Power"पूर्ण,
	अणु"DAC R1", शून्य, "Stereo DAC MIXR"पूर्ण,
	अणु"DAC R1", शून्य, "DAC R1 Power"पूर्ण,

	अणु"DD MIXL", "DAC L1 Switch", "DAC MIXL"पूर्ण,
	अणु"DD MIXL", "DAC L2 Switch", "DAC L2 Volume"पूर्ण,
	अणु"DD MIXL", "DAC R2 Switch", "DAC R2 Volume"पूर्ण,
	अणु"DD MIXL", शून्य, "Stero2 DAC Power"पूर्ण,

	अणु"DD MIXR", "DAC R1 Switch", "DAC MIXR"पूर्ण,
	अणु"DD MIXR", "DAC R2 Switch", "DAC R2 Volume"पूर्ण,
	अणु"DD MIXR", "DAC L2 Switch", "DAC L2 Volume"पूर्ण,
	अणु"DD MIXR", शून्य, "Stero2 DAC Power"पूर्ण,

	अणु"OUT MIXL", "BST1 Switch", "BST1"पूर्ण,
	अणु"OUT MIXL", "BST2 Switch", "BST2"पूर्ण,
	अणु"OUT MIXL", "INL1 Switch", "INL1 VOL"पूर्ण,
	अणु"OUT MIXL", "REC MIXL Switch", "RECMIXL"पूर्ण,
	अणु"OUT MIXL", "DAC L1 Switch", "DAC L1"पूर्ण,

	अणु"OUT MIXR", "BST2 Switch", "BST2"पूर्ण,
	अणु"OUT MIXR", "BST1 Switch", "BST1"पूर्ण,
	अणु"OUT MIXR", "INR1 Switch", "INR1 VOL"पूर्ण,
	अणु"OUT MIXR", "REC MIXR Switch", "RECMIXR"पूर्ण,
	अणु"OUT MIXR", "DAC R1 Switch", "DAC R1"पूर्ण,

	अणु"HPOVOL L", "Switch", "OUT MIXL"पूर्ण,
	अणु"HPOVOL R", "Switch", "OUT MIXR"पूर्ण,
	अणु"OUTVOL L", "Switch", "OUT MIXL"पूर्ण,
	अणु"OUTVOL R", "Switch", "OUT MIXR"पूर्ण,

	अणु"HPOL MIX", "HPO MIX DAC1 Switch", "DAC L1"पूर्ण,
	अणु"HPOL MIX", "HPO MIX HPVOL Switch", "HPOVOL L"पूर्ण,
	अणु"HPOL MIX", शून्य, "HP L Amp"पूर्ण,
	अणु"HPOR MIX", "HPO MIX DAC1 Switch", "DAC R1"पूर्ण,
	अणु"HPOR MIX", "HPO MIX HPVOL Switch", "HPOVOL R"पूर्ण,
	अणु"HPOR MIX", शून्य, "HP R Amp"पूर्ण,

	अणु"LOUT MIX", "DAC L1 Switch", "DAC L1"पूर्ण,
	अणु"LOUT MIX", "DAC R1 Switch", "DAC R1"पूर्ण,
	अणु"LOUT MIX", "OUTVOL L Switch", "OUTVOL L"पूर्ण,
	अणु"LOUT MIX", "OUTVOL R Switch", "OUTVOL R"पूर्ण,

	अणु"HP Amp", शून्य, "HPOL MIX"पूर्ण,
	अणु"HP Amp", शून्य, "HPOR MIX"पूर्ण,
	अणु"HP Amp", शून्य, "Amp Power"पूर्ण,
	अणु"HPO L Playback", "Switch", "HP Amp"पूर्ण,
	अणु"HPO R Playback", "Switch", "HP Amp"पूर्ण,
	अणु"HPOL", शून्य, "HPO L Playback"पूर्ण,
	अणु"HPOR", शून्य, "HPO R Playback"पूर्ण,

	अणु"LOUT L Playback", "Switch", "LOUT MIX"पूर्ण,
	अणु"LOUT R Playback", "Switch", "LOUT MIX"पूर्ण,
	अणु"LOUTL", शून्य, "LOUT L Playback"पूर्ण,
	अणु"LOUTL", शून्य, "Amp Power"पूर्ण,
	अणु"LOUTR", शून्य, "LOUT R Playback"पूर्ण,
	अणु"LOUTR", शून्य, "Amp Power"पूर्ण,

	अणु"PDML", शून्य, "PDM L Mux"पूर्ण,
	अणु"PDMR", शून्य, "PDM R Mux"पूर्ण,
पूर्ण;

अटल पूर्णांक rt5651_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5651_priv *rt5651 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val_len = 0, val_clk, mask_clk;
	पूर्णांक pre_भाग, bclk_ms, frame_size;

	rt5651->lrck[dai->id] = params_rate(params);
	pre_भाग = rl6231_get_clk_info(rt5651->sysclk, rt5651->lrck[dai->id]);

	अगर (pre_भाग < 0) अणु
		dev_err(component->dev, "Unsupported clock setting\n");
		वापस -EINVAL;
	पूर्ण
	frame_size = snd_soc_params_to_frame_size(params);
	अगर (frame_size < 0) अणु
		dev_err(component->dev, "Unsupported frame size: %d\n", frame_size);
		वापस -EINVAL;
	पूर्ण
	bclk_ms = frame_size > 32 ? 1 : 0;
	rt5651->bclk[dai->id] = rt5651->lrck[dai->id] * (32 << bclk_ms);

	dev_dbg(dai->dev, "bclk is %dHz and lrck is %dHz\n",
		rt5651->bclk[dai->id], rt5651->lrck[dai->id]);
	dev_dbg(dai->dev, "bclk_ms is %d and pre_div is %d for iis %d\n",
				bclk_ms, pre_भाग, dai->id);

	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		val_len |= RT5651_I2S_DL_20;
		अवरोध;
	हाल 24:
		val_len |= RT5651_I2S_DL_24;
		अवरोध;
	हाल 8:
		val_len |= RT5651_I2S_DL_8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT5651_AIF1:
		mask_clk = RT5651_I2S_PD1_MASK;
		val_clk = pre_भाग << RT5651_I2S_PD1_SFT;
		snd_soc_component_update_bits(component, RT5651_I2S1_SDP,
			RT5651_I2S_DL_MASK, val_len);
		snd_soc_component_update_bits(component, RT5651_ADDA_CLK1, mask_clk, val_clk);
		अवरोध;
	हाल RT5651_AIF2:
		mask_clk = RT5651_I2S_BCLK_MS2_MASK | RT5651_I2S_PD2_MASK;
		val_clk = pre_भाग << RT5651_I2S_PD2_SFT;
		snd_soc_component_update_bits(component, RT5651_I2S2_SDP,
			RT5651_I2S_DL_MASK, val_len);
		snd_soc_component_update_bits(component, RT5651_ADDA_CLK1, mask_clk, val_clk);
		अवरोध;
	शेष:
		dev_err(component->dev, "Wrong dai->id: %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5651_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5651_priv *rt5651 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		rt5651->master[dai->id] = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		reg_val |= RT5651_I2S_MS_S;
		rt5651->master[dai->id] = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		reg_val |= RT5651_I2S_BP_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT5651_I2S_DF_LEFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT5651_I2S_DF_PCM_A;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		reg_val |= RT5651_I2S_DF_PCM_B;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT5651_AIF1:
		snd_soc_component_update_bits(component, RT5651_I2S1_SDP,
			RT5651_I2S_MS_MASK | RT5651_I2S_BP_MASK |
			RT5651_I2S_DF_MASK, reg_val);
		अवरोध;
	हाल RT5651_AIF2:
		snd_soc_component_update_bits(component, RT5651_I2S2_SDP,
			RT5651_I2S_MS_MASK | RT5651_I2S_BP_MASK |
			RT5651_I2S_DF_MASK, reg_val);
		अवरोध;
	शेष:
		dev_err(component->dev, "Wrong dai->id: %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt5651_set_dai_sysclk(काष्ठा snd_soc_dai *dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5651_priv *rt5651 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;
	अचिन्हित पूर्णांक pll_bit = 0;

	अगर (freq == rt5651->sysclk && clk_id == rt5651->sysclk_src)
		वापस 0;

	चयन (clk_id) अणु
	हाल RT5651_SCLK_S_MCLK:
		reg_val |= RT5651_SCLK_SRC_MCLK;
		अवरोध;
	हाल RT5651_SCLK_S_PLL1:
		reg_val |= RT5651_SCLK_SRC_PLL1;
		pll_bit |= RT5651_PWR_PLL;
		अवरोध;
	हाल RT5651_SCLK_S_RCCLK:
		reg_val |= RT5651_SCLK_SRC_RCCLK;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_update_bits(component, RT5651_PWR_ANLG2,
		RT5651_PWR_PLL, pll_bit);
	snd_soc_component_update_bits(component, RT5651_GLB_CLK,
		RT5651_SCLK_SRC_MASK, reg_val);
	rt5651->sysclk = freq;
	rt5651->sysclk_src = clk_id;

	dev_dbg(dai->dev, "Sysclk is %dHz and clock id is %d\n", freq, clk_id);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5651_set_dai_pll(काष्ठा snd_soc_dai *dai, पूर्णांक pll_id, पूर्णांक source,
			अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5651_priv *rt5651 = snd_soc_component_get_drvdata(component);
	काष्ठा rl6231_pll_code pll_code;
	पूर्णांक ret;

	अगर (source == rt5651->pll_src && freq_in == rt5651->pll_in &&
	    freq_out == rt5651->pll_out)
		वापस 0;

	अगर (!freq_in || !freq_out) अणु
		dev_dbg(component->dev, "PLL disabled\n");

		rt5651->pll_in = 0;
		rt5651->pll_out = 0;
		snd_soc_component_update_bits(component, RT5651_GLB_CLK,
			RT5651_SCLK_SRC_MASK, RT5651_SCLK_SRC_MCLK);
		वापस 0;
	पूर्ण

	चयन (source) अणु
	हाल RT5651_PLL1_S_MCLK:
		snd_soc_component_update_bits(component, RT5651_GLB_CLK,
			RT5651_PLL1_SRC_MASK, RT5651_PLL1_SRC_MCLK);
		अवरोध;
	हाल RT5651_PLL1_S_BCLK1:
		snd_soc_component_update_bits(component, RT5651_GLB_CLK,
				RT5651_PLL1_SRC_MASK, RT5651_PLL1_SRC_BCLK1);
		अवरोध;
	हाल RT5651_PLL1_S_BCLK2:
			snd_soc_component_update_bits(component, RT5651_GLB_CLK,
				RT5651_PLL1_SRC_MASK, RT5651_PLL1_SRC_BCLK2);
		अवरोध;
	शेष:
		dev_err(component->dev, "Unknown PLL source %d\n", source);
		वापस -EINVAL;
	पूर्ण

	ret = rl6231_pll_calc(freq_in, freq_out, &pll_code);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Unsupport input clock %d\n", freq_in);
		वापस ret;
	पूर्ण

	dev_dbg(component->dev, "bypass=%d m=%d n=%d k=%d\n",
		pll_code.m_bp, (pll_code.m_bp ? 0 : pll_code.m_code),
		pll_code.n_code, pll_code.k_code);

	snd_soc_component_ग_लिखो(component, RT5651_PLL_CTRL1,
		pll_code.n_code << RT5651_PLL_N_SFT | pll_code.k_code);
	snd_soc_component_ग_लिखो(component, RT5651_PLL_CTRL2,
		((pll_code.m_bp ? 0 : pll_code.m_code) << RT5651_PLL_M_SFT) |
		(pll_code.m_bp << RT5651_PLL_M_BP_SFT));

	rt5651->pll_in = freq_in;
	rt5651->pll_out = freq_out;
	rt5651->pll_src = source;

	वापस 0;
पूर्ण

अटल पूर्णांक rt5651_set_bias_level(काष्ठा snd_soc_component *component,
			क्रमागत snd_soc_bias_level level)
अणु
	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		अगर (SND_SOC_BIAS_STANDBY == snd_soc_component_get_bias_level(component)) अणु
			अगर (snd_soc_component_पढ़ो(component, RT5651_PLL_MODE_1) & 0x9200)
				snd_soc_component_update_bits(component, RT5651_D_MISC,
						    0xc00, 0xc00);
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (SND_SOC_BIAS_OFF == snd_soc_component_get_bias_level(component)) अणु
			snd_soc_component_update_bits(component, RT5651_PWR_ANLG1,
				RT5651_PWR_VREF1 | RT5651_PWR_MB |
				RT5651_PWR_BG | RT5651_PWR_VREF2,
				RT5651_PWR_VREF1 | RT5651_PWR_MB |
				RT5651_PWR_BG | RT5651_PWR_VREF2);
			usleep_range(10000, 15000);
			snd_soc_component_update_bits(component, RT5651_PWR_ANLG1,
				RT5651_PWR_FV1 | RT5651_PWR_FV2,
				RT5651_PWR_FV1 | RT5651_PWR_FV2);
			snd_soc_component_update_bits(component, RT5651_D_MISC, 0x1, 0x1);
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_ग_लिखो(component, RT5651_D_MISC, 0x0010);
		snd_soc_component_ग_लिखो(component, RT5651_PWR_DIG1, 0x0000);
		snd_soc_component_ग_लिखो(component, RT5651_PWR_DIG2, 0x0000);
		snd_soc_component_ग_लिखो(component, RT5651_PWR_VOL, 0x0000);
		snd_soc_component_ग_लिखो(component, RT5651_PWR_MIXER, 0x0000);
		/* Do not touch the LDO voltage select bits on bias-off */
		snd_soc_component_update_bits(component, RT5651_PWR_ANLG1,
			~RT5651_PWR_LDO_DVO_MASK, 0);
		/* Leave PLL1 and jack-detect घातer as is, all others off */
		snd_soc_component_update_bits(component, RT5651_PWR_ANLG2,
				    ~(RT5651_PWR_PLL | RT5651_PWR_JD_M), 0);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rt5651_enable_micbias1_क्रम_ovcd(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	snd_soc_dapm_mutex_lock(dapm);
	snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "LDO");
	snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "micbias1");
	/* OVCD is unreliable when used with RCCLK as sysclk-source */
	snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "Platform Clock");
	snd_soc_dapm_sync_unlocked(dapm);
	snd_soc_dapm_mutex_unlock(dapm);
पूर्ण

अटल व्योम rt5651_disable_micbias1_क्रम_ovcd(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	snd_soc_dapm_mutex_lock(dapm);
	snd_soc_dapm_disable_pin_unlocked(dapm, "Platform Clock");
	snd_soc_dapm_disable_pin_unlocked(dapm, "micbias1");
	snd_soc_dapm_disable_pin_unlocked(dapm, "LDO");
	snd_soc_dapm_sync_unlocked(dapm);
	snd_soc_dapm_mutex_unlock(dapm);
पूर्ण

अटल व्योम rt5651_enable_micbias1_ovcd_irq(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5651_priv *rt5651 = snd_soc_component_get_drvdata(component);

	snd_soc_component_update_bits(component, RT5651_IRQ_CTRL2,
		RT5651_IRQ_MB1_OC_MASK, RT5651_IRQ_MB1_OC_NOR);
	rt5651->ovcd_irq_enabled = true;
पूर्ण

अटल व्योम rt5651_disable_micbias1_ovcd_irq(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5651_priv *rt5651 = snd_soc_component_get_drvdata(component);

	snd_soc_component_update_bits(component, RT5651_IRQ_CTRL2,
		RT5651_IRQ_MB1_OC_MASK, RT5651_IRQ_MB1_OC_BP);
	rt5651->ovcd_irq_enabled = false;
पूर्ण

अटल व्योम rt5651_clear_micbias1_ovcd(काष्ठा snd_soc_component *component)
अणु
	snd_soc_component_update_bits(component, RT5651_IRQ_CTRL2,
		RT5651_MB1_OC_CLR, 0);
पूर्ण

अटल bool rt5651_micbias1_ovcd(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक val;

	val = snd_soc_component_पढ़ो(component, RT5651_IRQ_CTRL2);
	dev_dbg(component->dev, "irq ctrl2 %#04x\n", val);

	वापस (val & RT5651_MB1_OC_CLR);
पूर्ण

अटल bool rt5651_jack_inserted(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5651_priv *rt5651 = snd_soc_component_get_drvdata(component);
	पूर्णांक val;

	अगर (rt5651->gpiod_hp_det) अणु
		val = gpiod_get_value_cansleep(rt5651->gpiod_hp_det);
		dev_dbg(component->dev, "jack-detect gpio %d\n", val);
		वापस val;
	पूर्ण

	val = snd_soc_component_पढ़ो(component, RT5651_INT_IRQ_ST);
	dev_dbg(component->dev, "irq status %#04x\n", val);

	चयन (rt5651->jd_src) अणु
	हाल RT5651_JD1_1:
		val &= 0x1000;
		अवरोध;
	हाल RT5651_JD1_2:
		val &= 0x2000;
		अवरोध;
	हाल RT5651_JD2:
		val &= 0x4000;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (rt5651->jd_active_high)
		वापस val != 0;
	अन्यथा
		वापस val == 0;
पूर्ण

/* Jack detect and button-press timings */
#घोषणा JACK_SETTLE_TIME	100 /* milli seconds */
#घोषणा JACK_DETECT_COUNT	5
#घोषणा JACK_DETECT_MAXCOUNT	20  /* Aprox. 2 seconds worth of tries */
#घोषणा JACK_UNPLUG_TIME	80  /* milli seconds */
#घोषणा BP_POLL_TIME		10  /* milli seconds */
#घोषणा BP_POLL_MAXCOUNT	200 /* assume something is wrong after this */
#घोषणा BP_THRESHOLD		3

अटल व्योम rt5651_start_button_press_work(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5651_priv *rt5651 = snd_soc_component_get_drvdata(component);

	rt5651->poll_count = 0;
	rt5651->press_count = 0;
	rt5651->release_count = 0;
	rt5651->pressed = false;
	rt5651->press_reported = false;
	rt5651_clear_micbias1_ovcd(component);
	schedule_delayed_work(&rt5651->bp_work, msecs_to_jअगरfies(BP_POLL_TIME));
पूर्ण

अटल व्योम rt5651_button_press_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt5651_priv *rt5651 =
		container_of(work, काष्ठा rt5651_priv, bp_work.work);
	काष्ठा snd_soc_component *component = rt5651->component;

	/* Check the jack was not हटाओd underneath us */
	अगर (!rt5651_jack_inserted(component))
		वापस;

	अगर (rt5651_micbias1_ovcd(component)) अणु
		rt5651->release_count = 0;
		rt5651->press_count++;
		/* Remember till after JACK_UNPLUG_TIME रुको */
		अगर (rt5651->press_count >= BP_THRESHOLD)
			rt5651->pressed = true;
		rt5651_clear_micbias1_ovcd(component);
	पूर्ण अन्यथा अणु
		rt5651->press_count = 0;
		rt5651->release_count++;
	पूर्ण

	/*
	 * The pins get temporarily लघुed on jack unplug, so we poll क्रम
	 * at least JACK_UNPLUG_TIME milli-seconds beक्रमe reporting a press.
	 */
	rt5651->poll_count++;
	अगर (rt5651->poll_count < (JACK_UNPLUG_TIME / BP_POLL_TIME)) अणु
		schedule_delayed_work(&rt5651->bp_work,
				      msecs_to_jअगरfies(BP_POLL_TIME));
		वापस;
	पूर्ण

	अगर (rt5651->pressed && !rt5651->press_reported) अणु
		dev_dbg(component->dev, "headset button press\n");
		snd_soc_jack_report(rt5651->hp_jack, SND_JACK_BTN_0,
				    SND_JACK_BTN_0);
		rt5651->press_reported = true;
	पूर्ण

	अगर (rt5651->release_count >= BP_THRESHOLD) अणु
		अगर (rt5651->press_reported) अणु
			dev_dbg(component->dev, "headset button release\n");
			snd_soc_jack_report(rt5651->hp_jack, 0, SND_JACK_BTN_0);
		पूर्ण
		/* Re-enable OVCD IRQ to detect next press */
		rt5651_enable_micbias1_ovcd_irq(component);
		वापस; /* Stop polling */
	पूर्ण

	schedule_delayed_work(&rt5651->bp_work, msecs_to_jअगरfies(BP_POLL_TIME));
पूर्ण

अटल पूर्णांक rt5651_detect_headset(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक i, headset_count = 0, headphone_count = 0;

	/*
	 * We get the insertion event beक्रमe the jack is fully inserted at which
	 * poपूर्णांक the second ring on a TRRS connector may लघु the 2nd ring and
	 * sleeve contacts, also the overcurrent detection is not entirely
	 * reliable. So we try several बार with a रुको in between until we
	 * detect the same type JACK_DETECT_COUNT बार in a row.
	 */
	क्रम (i = 0; i < JACK_DETECT_MAXCOUNT; i++) अणु
		/* Clear any previous over-current status flag */
		rt5651_clear_micbias1_ovcd(component);

		msleep(JACK_SETTLE_TIME);

		/* Check the jack is still connected beक्रमe checking ovcd */
		अगर (!rt5651_jack_inserted(component))
			वापस 0;

		अगर (rt5651_micbias1_ovcd(component)) अणु
			/*
			 * Over current detected, there is a लघु between the
			 * 2nd ring contact and the ground, so a TRS connector
			 * without a mic contact and thus plain headphones.
			 */
			dev_dbg(component->dev, "mic-gnd shorted\n");
			headset_count = 0;
			headphone_count++;
			अगर (headphone_count == JACK_DETECT_COUNT)
				वापस SND_JACK_HEADPHONE;
		पूर्ण अन्यथा अणु
			dev_dbg(component->dev, "mic-gnd open\n");
			headphone_count = 0;
			headset_count++;
			अगर (headset_count == JACK_DETECT_COUNT)
				वापस SND_JACK_HEADSET;
		पूर्ण
	पूर्ण

	dev_err(component->dev, "Error detecting headset vs headphones, bad contact?, assuming headphones\n");
	वापस SND_JACK_HEADPHONE;
पूर्ण

अटल bool rt5651_support_button_press(काष्ठा rt5651_priv *rt5651)
अणु
	अगर (!rt5651->hp_jack)
		वापस false;

	/* Button press support only works with पूर्णांकernal jack-detection */
	वापस (rt5651->hp_jack->status & SND_JACK_MICROPHONE) &&
		rt5651->gpiod_hp_det == शून्य;
पूर्ण

अटल व्योम rt5651_jack_detect_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt5651_priv *rt5651 =
		container_of(work, काष्ठा rt5651_priv, jack_detect_work);
	काष्ठा snd_soc_component *component = rt5651->component;
	पूर्णांक report;

	अगर (!rt5651_jack_inserted(component)) अणु
		/* Jack हटाओd, or spurious IRQ? */
		अगर (rt5651->hp_jack->status & SND_JACK_HEADPHONE) अणु
			अगर (rt5651->hp_jack->status & SND_JACK_MICROPHONE) अणु
				cancel_delayed_work_sync(&rt5651->bp_work);
				rt5651_disable_micbias1_ovcd_irq(component);
				rt5651_disable_micbias1_क्रम_ovcd(component);
			पूर्ण
			snd_soc_jack_report(rt5651->hp_jack, 0,
					    SND_JACK_HEADSET | SND_JACK_BTN_0);
			dev_dbg(component->dev, "jack unplugged\n");
		पूर्ण
	पूर्ण अन्यथा अगर (!(rt5651->hp_jack->status & SND_JACK_HEADPHONE)) अणु
		/* Jack inserted */
		WARN_ON(rt5651->ovcd_irq_enabled);
		rt5651_enable_micbias1_क्रम_ovcd(component);
		report = rt5651_detect_headset(component);
		dev_dbg(component->dev, "detect report %#02x\n", report);
		snd_soc_jack_report(rt5651->hp_jack, report, SND_JACK_HEADSET);
		अगर (rt5651_support_button_press(rt5651)) अणु
			/* Enable ovcd IRQ क्रम button press detect. */
			rt5651_enable_micbias1_ovcd_irq(component);
		पूर्ण अन्यथा अणु
			/* No more need क्रम overcurrent detect. */
			rt5651_disable_micbias1_क्रम_ovcd(component);
		पूर्ण
	पूर्ण अन्यथा अगर (rt5651->ovcd_irq_enabled && rt5651_micbias1_ovcd(component)) अणु
		dev_dbg(component->dev, "OVCD IRQ\n");

		/*
		 * The ovcd IRQ keeps firing जबतक the button is pressed, so
		 * we disable it and start polling the button until released.
		 *
		 * The disable will make the IRQ pin 0 again and since we get
		 * IRQs on both edges (so as to detect both jack plugin and
		 * unplug) this means we will immediately get another IRQ.
		 * The ovcd_irq_enabled check above makes the 2ND IRQ a NOP.
		 */
		rt5651_disable_micbias1_ovcd_irq(component);
		rt5651_start_button_press_work(component);

		/*
		 * If the jack-detect IRQ flag goes high (unplug) after our
		 * above rt5651_jack_inserted() check and beक्रमe we have
		 * disabled the OVCD IRQ, the IRQ pin will stay high and as
		 * we react to edges, we miss the unplug event -> recheck.
		 */
		queue_work(प्रणाली_दीर्घ_wq, &rt5651->jack_detect_work);
	पूर्ण
पूर्ण

अटल irqवापस_t rt5651_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rt5651_priv *rt5651 = data;

	queue_work(प्रणाली_घातer_efficient_wq, &rt5651->jack_detect_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rt5651_cancel_work(व्योम *data)
अणु
	काष्ठा rt5651_priv *rt5651 = data;

	cancel_work_sync(&rt5651->jack_detect_work);
	cancel_delayed_work_sync(&rt5651->bp_work);
पूर्ण

अटल व्योम rt5651_enable_jack_detect(काष्ठा snd_soc_component *component,
				      काष्ठा snd_soc_jack *hp_jack,
				      काष्ठा gpio_desc *gpiod_hp_det)
अणु
	काष्ठा rt5651_priv *rt5651 = snd_soc_component_get_drvdata(component);
	bool using_पूर्णांकernal_jack_detect = true;

	/* Select jack detect source */
	चयन (rt5651->jd_src) अणु
	हाल RT5651_JD_शून्य:
		rt5651->gpiod_hp_det = gpiod_hp_det;
		अगर (!rt5651->gpiod_hp_det)
			वापस; /* No jack detect */
		using_पूर्णांकernal_jack_detect = false;
		अवरोध;
	हाल RT5651_JD1_1:
		snd_soc_component_update_bits(component, RT5651_JD_CTRL2,
			RT5651_JD_TRG_SEL_MASK, RT5651_JD_TRG_SEL_JD1_1);
		/* active-low is normal, set inv flag क्रम active-high */
		अगर (rt5651->jd_active_high)
			snd_soc_component_update_bits(component,
				RT5651_IRQ_CTRL1,
				RT5651_JD1_1_IRQ_EN | RT5651_JD1_1_INV,
				RT5651_JD1_1_IRQ_EN | RT5651_JD1_1_INV);
		अन्यथा
			snd_soc_component_update_bits(component,
				RT5651_IRQ_CTRL1,
				RT5651_JD1_1_IRQ_EN | RT5651_JD1_1_INV,
				RT5651_JD1_1_IRQ_EN);
		अवरोध;
	हाल RT5651_JD1_2:
		snd_soc_component_update_bits(component, RT5651_JD_CTRL2,
			RT5651_JD_TRG_SEL_MASK, RT5651_JD_TRG_SEL_JD1_2);
		/* active-low is normal, set inv flag क्रम active-high */
		अगर (rt5651->jd_active_high)
			snd_soc_component_update_bits(component,
				RT5651_IRQ_CTRL1,
				RT5651_JD1_2_IRQ_EN | RT5651_JD1_2_INV,
				RT5651_JD1_2_IRQ_EN | RT5651_JD1_2_INV);
		अन्यथा
			snd_soc_component_update_bits(component,
				RT5651_IRQ_CTRL1,
				RT5651_JD1_2_IRQ_EN | RT5651_JD1_2_INV,
				RT5651_JD1_2_IRQ_EN);
		अवरोध;
	हाल RT5651_JD2:
		snd_soc_component_update_bits(component, RT5651_JD_CTRL2,
			RT5651_JD_TRG_SEL_MASK, RT5651_JD_TRG_SEL_JD2);
		/* active-low is normal, set inv flag क्रम active-high */
		अगर (rt5651->jd_active_high)
			snd_soc_component_update_bits(component,
				RT5651_IRQ_CTRL1,
				RT5651_JD2_IRQ_EN | RT5651_JD2_INV,
				RT5651_JD2_IRQ_EN | RT5651_JD2_INV);
		अन्यथा
			snd_soc_component_update_bits(component,
				RT5651_IRQ_CTRL1,
				RT5651_JD2_IRQ_EN | RT5651_JD2_INV,
				RT5651_JD2_IRQ_EN);
		अवरोध;
	शेष:
		dev_err(component->dev, "Currently only JD1_1 / JD1_2 / JD2 are supported\n");
		वापस;
	पूर्ण

	अगर (using_पूर्णांकernal_jack_detect) अणु
		/* IRQ output on GPIO1 */
		snd_soc_component_update_bits(component, RT5651_GPIO_CTRL1,
			RT5651_GP1_PIN_MASK, RT5651_GP1_PIN_IRQ);

		/* Enable jack detect घातer */
		snd_soc_component_update_bits(component, RT5651_PWR_ANLG2,
			RT5651_PWR_JD_M, RT5651_PWR_JD_M);
	पूर्ण

	/* Set OVCD threshold current and scale-factor */
	snd_soc_component_ग_लिखो(component, RT5651_PR_BASE + RT5651_BIAS_CUR4,
				0xa800 | rt5651->ovcd_sf);

	snd_soc_component_update_bits(component, RT5651_MICBIAS,
				      RT5651_MIC1_OVCD_MASK |
				      RT5651_MIC1_OVTH_MASK |
				      RT5651_PWR_CLK12M_MASK |
				      RT5651_PWR_MB_MASK,
				      RT5651_MIC1_OVCD_EN |
				      rt5651->ovcd_th |
				      RT5651_PWR_MB_PU |
				      RT5651_PWR_CLK12M_PU);

	/*
	 * The over-current-detect is only reliable in detecting the असलence
	 * of over-current, when the mic-contact in the jack is लघु-circuited,
	 * the hardware periodically retries अगर it can apply the bias-current
	 * leading to the ovcd status flip-flopping 1-0-1 with it being 0 about
	 * 10% of the समय, as we poll the ovcd status bit we might hit that
	 * 10%, so we enable sticky mode and when checking OVCD we clear the
	 * status, msleep() a bit and then check to get a reliable पढ़ोing.
	 */
	snd_soc_component_update_bits(component, RT5651_IRQ_CTRL2,
		RT5651_MB1_OC_STKY_MASK, RT5651_MB1_OC_STKY_EN);

	rt5651->hp_jack = hp_jack;
	अगर (rt5651_support_button_press(rt5651)) अणु
		rt5651_enable_micbias1_क्रम_ovcd(component);
		rt5651_enable_micbias1_ovcd_irq(component);
	पूर्ण

	enable_irq(rt5651->irq);
	/* sync initial jack state */
	queue_work(प्रणाली_घातer_efficient_wq, &rt5651->jack_detect_work);
पूर्ण

अटल व्योम rt5651_disable_jack_detect(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5651_priv *rt5651 = snd_soc_component_get_drvdata(component);

	disable_irq(rt5651->irq);
	rt5651_cancel_work(rt5651);

	अगर (rt5651_support_button_press(rt5651)) अणु
		rt5651_disable_micbias1_ovcd_irq(component);
		rt5651_disable_micbias1_क्रम_ovcd(component);
		snd_soc_jack_report(rt5651->hp_jack, 0, SND_JACK_BTN_0);
	पूर्ण

	rt5651->hp_jack = शून्य;
पूर्ण

अटल पूर्णांक rt5651_set_jack(काष्ठा snd_soc_component *component,
			   काष्ठा snd_soc_jack *jack, व्योम *data)
अणु
	अगर (jack)
		rt5651_enable_jack_detect(component, jack, data);
	अन्यथा
		rt5651_disable_jack_detect(component);

	वापस 0;
पूर्ण

/*
 * Note on some platक्रमms the platक्रमm code may need to add device-properties,
 * rather then relying only on properties set by the firmware. Thereक्रम the
 * property parsing MUST be करोne from the component driver's probe function,
 * rather then from the i2c driver's probe function, so that the platक्रमm-code
 * can attach extra properties beक्रमe calling snd_soc_रेजिस्टर_card().
 */
अटल व्योम rt5651_apply_properties(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5651_priv *rt5651 = snd_soc_component_get_drvdata(component);
	u32 val;

	अगर (device_property_पढ़ो_bool(component->dev, "realtek,in2-differential"))
		snd_soc_component_update_bits(component, RT5651_IN1_IN2,
				RT5651_IN_DF2, RT5651_IN_DF2);

	अगर (device_property_पढ़ो_bool(component->dev, "realtek,dmic-en"))
		snd_soc_component_update_bits(component, RT5651_GPIO_CTRL1,
				RT5651_GP2_PIN_MASK, RT5651_GP2_PIN_DMIC1_SCL);

	अगर (device_property_पढ़ो_u32(component->dev,
				     "realtek,jack-detect-source", &val) == 0)
		rt5651->jd_src = val;

	अगर (device_property_पढ़ो_bool(component->dev, "realtek,jack-detect-not-inverted"))
		rt5651->jd_active_high = true;

	/*
	 * Testing on various boards has shown that good शेषs क्रम the OVCD
	 * threshold and scale-factor are 2000तगA and 0.75. For an effective
	 * limit of 1500तगA, this seems to be more reliable then 1500तगA and 1.0.
	 */
	rt5651->ovcd_th = RT5651_MIC1_OVTH_2000UA;
	rt5651->ovcd_sf = RT5651_MIC_OVCD_SF_0P75;

	अगर (device_property_पढ़ो_u32(component->dev,
			"realtek,over-current-threshold-microamp", &val) == 0) अणु
		चयन (val) अणु
		हाल 600:
			rt5651->ovcd_th = RT5651_MIC1_OVTH_600UA;
			अवरोध;
		हाल 1500:
			rt5651->ovcd_th = RT5651_MIC1_OVTH_1500UA;
			अवरोध;
		हाल 2000:
			rt5651->ovcd_th = RT5651_MIC1_OVTH_2000UA;
			अवरोध;
		शेष:
			dev_warn(component->dev, "Warning: Invalid over-current-threshold-microamp value: %d, defaulting to 2000uA\n",
				 val);
		पूर्ण
	पूर्ण

	अगर (device_property_पढ़ो_u32(component->dev,
			"realtek,over-current-scale-factor", &val) == 0) अणु
		अगर (val <= RT5651_OVCD_SF_1P5)
			rt5651->ovcd_sf = val << RT5651_MIC_OVCD_SF_SFT;
		अन्यथा
			dev_warn(component->dev, "Warning: Invalid over-current-scale-factor value: %d, defaulting to 0.75\n",
				 val);
	पूर्ण
पूर्ण

अटल पूर्णांक rt5651_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5651_priv *rt5651 = snd_soc_component_get_drvdata(component);

	rt5651->component = component;

	snd_soc_component_update_bits(component, RT5651_PWR_ANLG1,
		RT5651_PWR_LDO_DVO_MASK, RT5651_PWR_LDO_DVO_1_2V);

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_OFF);

	rt5651_apply_properties(component);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rt5651_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5651_priv *rt5651 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt5651->regmap, true);
	regcache_mark_dirty(rt5651->regmap);
	वापस 0;
पूर्ण

अटल पूर्णांक rt5651_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5651_priv *rt5651 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt5651->regmap, false);
	snd_soc_component_cache_sync(component);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा rt5651_suspend शून्य
#घोषणा rt5651_resume शून्य
#पूर्ण_अगर

#घोषणा RT5651_STEREO_RATES SNDRV_PCM_RATE_8000_96000
#घोषणा RT5651_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S8)

अटल स्थिर काष्ठा snd_soc_dai_ops rt5651_aअगर_dai_ops = अणु
	.hw_params = rt5651_hw_params,
	.set_fmt = rt5651_set_dai_fmt,
	.set_sysclk = rt5651_set_dai_sysclk,
	.set_pll = rt5651_set_dai_pll,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt5651_dai[] = अणु
	अणु
		.name = "rt5651-aif1",
		.id = RT5651_AIF1,
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5651_STEREO_RATES,
			.क्रमmats = RT5651_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5651_STEREO_RATES,
			.क्रमmats = RT5651_FORMATS,
		पूर्ण,
		.ops = &rt5651_aअगर_dai_ops,
	पूर्ण,
	अणु
		.name = "rt5651-aif2",
		.id = RT5651_AIF2,
		.playback = अणु
			.stream_name = "AIF2 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5651_STEREO_RATES,
			.क्रमmats = RT5651_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF2 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5651_STEREO_RATES,
			.क्रमmats = RT5651_FORMATS,
		पूर्ण,
		.ops = &rt5651_aअगर_dai_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_rt5651 = अणु
	.probe			= rt5651_probe,
	.suspend		= rt5651_suspend,
	.resume			= rt5651_resume,
	.set_bias_level		= rt5651_set_bias_level,
	.set_jack		= rt5651_set_jack,
	.controls		= rt5651_snd_controls,
	.num_controls		= ARRAY_SIZE(rt5651_snd_controls),
	.dapm_widमाला_लो		= rt5651_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(rt5651_dapm_widमाला_लो),
	.dapm_routes		= rt5651_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(rt5651_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt5651_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,

	.max_रेजिस्टर = RT5651_DEVICE_ID + 1 + (ARRAY_SIZE(rt5651_ranges) *
					       RT5651_PR_SPACING),
	.अस्थिर_reg = rt5651_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = rt5651_पढ़ोable_रेजिस्टर,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = rt5651_reg,
	.num_reg_शेषs = ARRAY_SIZE(rt5651_reg),
	.ranges = rt5651_ranges,
	.num_ranges = ARRAY_SIZE(rt5651_ranges),
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id rt5651_of_match[] = अणु
	अणु .compatible = "realtek,rt5651", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt5651_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id rt5651_acpi_match[] = अणु
	अणु "10EC5651", 0 पूर्ण,
	अणु "10EC5640", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rt5651_acpi_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id rt5651_i2c_id[] = अणु
	अणु "rt5651", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt5651_i2c_id);

/*
 * Note this function MUST not look at device-properties, see the comment
 * above rt5651_apply_properties().
 */
अटल पूर्णांक rt5651_i2c_probe(काष्ठा i2c_client *i2c,
		    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rt5651_priv *rt5651;
	पूर्णांक ret;
	पूर्णांक err;

	rt5651 = devm_kzalloc(&i2c->dev, माप(*rt5651),
				GFP_KERNEL);
	अगर (शून्य == rt5651)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, rt5651);

	rt5651->regmap = devm_regmap_init_i2c(i2c, &rt5651_regmap);
	अगर (IS_ERR(rt5651->regmap)) अणु
		ret = PTR_ERR(rt5651->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	err = regmap_पढ़ो(rt5651->regmap, RT5651_DEVICE_ID, &ret);
	अगर (err)
		वापस err;

	अगर (ret != RT5651_DEVICE_ID_VALUE) अणु
		dev_err(&i2c->dev,
			"Device with ID register %#x is not rt5651\n", ret);
		वापस -ENODEV;
	पूर्ण

	regmap_ग_लिखो(rt5651->regmap, RT5651_RESET, 0);

	ret = regmap_रेजिस्टर_patch(rt5651->regmap, init_list,
				    ARRAY_SIZE(init_list));
	अगर (ret != 0)
		dev_warn(&i2c->dev, "Failed to apply regmap patch: %d\n", ret);

	rt5651->irq = i2c->irq;
	rt5651->hp_mute = true;

	INIT_DELAYED_WORK(&rt5651->bp_work, rt5651_button_press_work);
	INIT_WORK(&rt5651->jack_detect_work, rt5651_jack_detect_work);

	/* Make sure work is stopped on probe-error / हटाओ */
	ret = devm_add_action_or_reset(&i2c->dev, rt5651_cancel_work, rt5651);
	अगर (ret)
		वापस ret;

	ret = devm_request_irq(&i2c->dev, rt5651->irq, rt5651_irq,
			       IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING
			       | IRQF_ONESHOT, "rt5651", rt5651);
	अगर (ret == 0) अणु
		/* Gets re-enabled by rt5651_set_jack() */
		disable_irq(rt5651->irq);
	पूर्ण अन्यथा अणु
		dev_warn(&i2c->dev, "Failed to reguest IRQ %d: %d\n",
			 rt5651->irq, ret);
		rt5651->irq = -ENXIO;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				&soc_component_dev_rt5651,
				rt5651_dai, ARRAY_SIZE(rt5651_dai));

	वापस ret;
पूर्ण

अटल काष्ठा i2c_driver rt5651_i2c_driver = अणु
	.driver = अणु
		.name = "rt5651",
		.acpi_match_table = ACPI_PTR(rt5651_acpi_match),
		.of_match_table = of_match_ptr(rt5651_of_match),
	पूर्ण,
	.probe = rt5651_i2c_probe,
	.id_table = rt5651_i2c_id,
पूर्ण;
module_i2c_driver(rt5651_i2c_driver);

MODULE_DESCRIPTION("ASoC RT5651 driver");
MODULE_AUTHOR("Bard Liao <bardliao@realtek.com>");
MODULE_LICENSE("GPL v2");
