<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rt5660.c  --  RT5660 ALSA SoC audio codec driver
 *
 * Copyright 2016 Realtek Semiconductor Corp.
 * Author: Oder Chiou <oder_chiou@realtek.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
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

#समावेश "rl6231.h"
#समावेश "rt5660.h"

#घोषणा RT5660_DEVICE_ID 0x6338

#घोषणा RT5660_PR_RANGE_BASE (0xff + 1)
#घोषणा RT5660_PR_SPACING 0x100

#घोषणा RT5660_PR_BASE (RT5660_PR_RANGE_BASE + (0 * RT5660_PR_SPACING))

अटल स्थिर काष्ठा regmap_range_cfg rt5660_ranges[] = अणु
	अणु .name = "PR", .range_min = RT5660_PR_BASE,
	  .range_max = RT5660_PR_BASE + 0xf3,
	  .selector_reg = RT5660_PRIV_INDEX,
	  .selector_mask = 0xff,
	  .selector_shअगरt = 0x0,
	  .winकरोw_start = RT5660_PRIV_DATA,
	  .winकरोw_len = 0x1, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence rt5660_patch[] = अणु
	अणु RT5660_ALC_PGA_CTRL2,		0x44c3 पूर्ण,
	अणु RT5660_PR_BASE + 0x3d,	0x2600 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष rt5660_reg[] = अणु
	अणु 0x00, 0x0000 पूर्ण,
	अणु 0x01, 0xc800 पूर्ण,
	अणु 0x02, 0xc8c8 पूर्ण,
	अणु 0x0d, 0x1010 पूर्ण,
	अणु 0x0e, 0x1010 पूर्ण,
	अणु 0x19, 0xafaf पूर्ण,
	अणु 0x1c, 0x2f2f पूर्ण,
	अणु 0x1e, 0x0000 पूर्ण,
	अणु 0x27, 0x6060 पूर्ण,
	अणु 0x29, 0x8080 पूर्ण,
	अणु 0x2a, 0x4242 पूर्ण,
	अणु 0x2f, 0x0000 पूर्ण,
	अणु 0x3b, 0x0000 पूर्ण,
	अणु 0x3c, 0x007f पूर्ण,
	अणु 0x3d, 0x0000 पूर्ण,
	अणु 0x3e, 0x007f पूर्ण,
	अणु 0x45, 0xe000 पूर्ण,
	अणु 0x46, 0x003e पूर्ण,
	अणु 0x48, 0xf800 पूर्ण,
	अणु 0x4a, 0x0004 पूर्ण,
	अणु 0x4d, 0x0000 पूर्ण,
	अणु 0x4e, 0x0000 पूर्ण,
	अणु 0x4f, 0x01ff पूर्ण,
	अणु 0x50, 0x0000 पूर्ण,
	अणु 0x51, 0x0000 पूर्ण,
	अणु 0x52, 0x01ff पूर्ण,
	अणु 0x61, 0x0000 पूर्ण,
	अणु 0x62, 0x0000 पूर्ण,
	अणु 0x63, 0x00c0 पूर्ण,
	अणु 0x64, 0x0000 पूर्ण,
	अणु 0x65, 0x0000 पूर्ण,
	अणु 0x66, 0x0000 पूर्ण,
	अणु 0x70, 0x8000 पूर्ण,
	अणु 0x73, 0x7000 पूर्ण,
	अणु 0x74, 0x3c00 पूर्ण,
	अणु 0x75, 0x2800 पूर्ण,
	अणु 0x80, 0x0000 पूर्ण,
	अणु 0x81, 0x0000 पूर्ण,
	अणु 0x82, 0x0000 पूर्ण,
	अणु 0x8c, 0x0228 पूर्ण,
	अणु 0x8d, 0xa000 पूर्ण,
	अणु 0x8e, 0x0000 पूर्ण,
	अणु 0x92, 0x0000 पूर्ण,
	अणु 0x93, 0x3000 पूर्ण,
	अणु 0xa1, 0x0059 पूर्ण,
	अणु 0xa2, 0x0001 पूर्ण,
	अणु 0xa3, 0x5c80 पूर्ण,
	अणु 0xa4, 0x0146 पूर्ण,
	अणु 0xa5, 0x1f1f पूर्ण,
	अणु 0xa6, 0x78c6 पूर्ण,
	अणु 0xa7, 0xe5ec पूर्ण,
	अणु 0xa8, 0xba61 पूर्ण,
	अणु 0xa9, 0x3c78 पूर्ण,
	अणु 0xaa, 0x8ae2 पूर्ण,
	अणु 0xab, 0xe5ec पूर्ण,
	अणु 0xac, 0xc600 पूर्ण,
	अणु 0xad, 0xba61 पूर्ण,
	अणु 0xae, 0x17ed पूर्ण,
	अणु 0xb0, 0x2080 पूर्ण,
	अणु 0xb1, 0x0000 पूर्ण,
	अणु 0xb3, 0x001f पूर्ण,
	अणु 0xb4, 0x020c पूर्ण,
	अणु 0xb5, 0x1f00 पूर्ण,
	अणु 0xb6, 0x0000 पूर्ण,
	अणु 0xb7, 0x4000 पूर्ण,
	अणु 0xbb, 0x0000 पूर्ण,
	अणु 0xbd, 0x0000 पूर्ण,
	अणु 0xbe, 0x0000 पूर्ण,
	अणु 0xbf, 0x0100 पूर्ण,
	अणु 0xc0, 0x0000 पूर्ण,
	अणु 0xc2, 0x0000 पूर्ण,
	अणु 0xd3, 0xa220 पूर्ण,
	अणु 0xd9, 0x0809 पूर्ण,
	अणु 0xda, 0x0000 पूर्ण,
	अणु 0xe0, 0x8000 पूर्ण,
	अणु 0xe1, 0x0200 पूर्ण,
	अणु 0xe2, 0x8000 पूर्ण,
	अणु 0xe3, 0x0200 पूर्ण,
	अणु 0xe4, 0x0f20 पूर्ण,
	अणु 0xe5, 0x001f पूर्ण,
	अणु 0xe6, 0x020c पूर्ण,
	अणु 0xe7, 0x1f00 पूर्ण,
	अणु 0xe8, 0x0000 पूर्ण,
	अणु 0xe9, 0x4000 पूर्ण,
	अणु 0xea, 0x00a6 पूर्ण,
	अणु 0xeb, 0x04c3 पूर्ण,
	अणु 0xec, 0x27c8 पूर्ण,
	अणु 0xed, 0x7418 पूर्ण,
	अणु 0xee, 0xbf50 पूर्ण,
	अणु 0xef, 0x0045 पूर्ण,
	अणु 0xf0, 0x0007 पूर्ण,
	अणु 0xfa, 0x0000 पूर्ण,
	अणु 0xfd, 0x0000 पूर्ण,
	अणु 0xfe, 0x10ec पूर्ण,
	अणु 0xff, 0x6338 पूर्ण,
पूर्ण;

अटल bool rt5660_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rt5660_ranges); i++)
		अगर ((reg >= rt5660_ranges[i].winकरोw_start &&
		     reg <= rt5660_ranges[i].winकरोw_start +
		     rt5660_ranges[i].winकरोw_len) ||
		    (reg >= rt5660_ranges[i].range_min &&
		     reg <= rt5660_ranges[i].range_max))
			वापस true;

	चयन (reg) अणु
	हाल RT5660_RESET:
	हाल RT5660_PRIV_DATA:
	हाल RT5660_EQ_CTRL1:
	हाल RT5660_IRQ_CTRL2:
	हाल RT5660_INT_IRQ_ST:
	हाल RT5660_VENDOR_ID:
	हाल RT5660_VENDOR_ID1:
	हाल RT5660_VENDOR_ID2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt5660_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rt5660_ranges); i++)
		अगर ((reg >= rt5660_ranges[i].winकरोw_start &&
		     reg <= rt5660_ranges[i].winकरोw_start +
		     rt5660_ranges[i].winकरोw_len) ||
		    (reg >= rt5660_ranges[i].range_min &&
		     reg <= rt5660_ranges[i].range_max))
			वापस true;

	चयन (reg) अणु
	हाल RT5660_RESET:
	हाल RT5660_SPK_VOL:
	हाल RT5660_LOUT_VOL:
	हाल RT5660_IN1_IN2:
	हाल RT5660_IN3_IN4:
	हाल RT5660_DAC1_DIG_VOL:
	हाल RT5660_STO1_ADC_DIG_VOL:
	हाल RT5660_ADC_BST_VOL1:
	हाल RT5660_STO1_ADC_MIXER:
	हाल RT5660_AD_DA_MIXER:
	हाल RT5660_STO_DAC_MIXER:
	हाल RT5660_DIG_INF1_DATA:
	हाल RT5660_REC_L1_MIXER:
	हाल RT5660_REC_L2_MIXER:
	हाल RT5660_REC_R1_MIXER:
	हाल RT5660_REC_R2_MIXER:
	हाल RT5660_LOUT_MIXER:
	हाल RT5660_SPK_MIXER:
	हाल RT5660_SPO_MIXER:
	हाल RT5660_SPO_CLSD_RATIO:
	हाल RT5660_OUT_L_GAIN1:
	हाल RT5660_OUT_L_GAIN2:
	हाल RT5660_OUT_L1_MIXER:
	हाल RT5660_OUT_R_GAIN1:
	हाल RT5660_OUT_R_GAIN2:
	हाल RT5660_OUT_R1_MIXER:
	हाल RT5660_PWR_DIG1:
	हाल RT5660_PWR_DIG2:
	हाल RT5660_PWR_ANLG1:
	हाल RT5660_PWR_ANLG2:
	हाल RT5660_PWR_MIXER:
	हाल RT5660_PWR_VOL:
	हाल RT5660_PRIV_INDEX:
	हाल RT5660_PRIV_DATA:
	हाल RT5660_I2S1_SDP:
	हाल RT5660_ADDA_CLK1:
	हाल RT5660_ADDA_CLK2:
	हाल RT5660_DMIC_CTRL1:
	हाल RT5660_GLB_CLK:
	हाल RT5660_PLL_CTRL1:
	हाल RT5660_PLL_CTRL2:
	हाल RT5660_CLSD_AMP_OC_CTRL:
	हाल RT5660_CLSD_AMP_CTRL:
	हाल RT5660_LOUT_AMP_CTRL:
	हाल RT5660_SPK_AMP_SPKVDD:
	हाल RT5660_MICBIAS:
	हाल RT5660_CLSD_OUT_CTRL1:
	हाल RT5660_CLSD_OUT_CTRL2:
	हाल RT5660_DIPOLE_MIC_CTRL1:
	हाल RT5660_DIPOLE_MIC_CTRL2:
	हाल RT5660_DIPOLE_MIC_CTRL3:
	हाल RT5660_DIPOLE_MIC_CTRL4:
	हाल RT5660_DIPOLE_MIC_CTRL5:
	हाल RT5660_DIPOLE_MIC_CTRL6:
	हाल RT5660_DIPOLE_MIC_CTRL7:
	हाल RT5660_DIPOLE_MIC_CTRL8:
	हाल RT5660_DIPOLE_MIC_CTRL9:
	हाल RT5660_DIPOLE_MIC_CTRL10:
	हाल RT5660_DIPOLE_MIC_CTRL11:
	हाल RT5660_DIPOLE_MIC_CTRL12:
	हाल RT5660_EQ_CTRL1:
	हाल RT5660_EQ_CTRL2:
	हाल RT5660_DRC_AGC_CTRL1:
	हाल RT5660_DRC_AGC_CTRL2:
	हाल RT5660_DRC_AGC_CTRL3:
	हाल RT5660_DRC_AGC_CTRL4:
	हाल RT5660_DRC_AGC_CTRL5:
	हाल RT5660_JD_CTRL:
	हाल RT5660_IRQ_CTRL1:
	हाल RT5660_IRQ_CTRL2:
	हाल RT5660_INT_IRQ_ST:
	हाल RT5660_GPIO_CTRL1:
	हाल RT5660_GPIO_CTRL2:
	हाल RT5660_WIND_FILTER_CTRL1:
	हाल RT5660_SV_ZCD1:
	हाल RT5660_SV_ZCD2:
	हाल RT5660_DRC1_LM_CTRL1:
	हाल RT5660_DRC1_LM_CTRL2:
	हाल RT5660_DRC2_LM_CTRL1:
	हाल RT5660_DRC2_LM_CTRL2:
	हाल RT5660_MULTI_DRC_CTRL:
	हाल RT5660_DRC2_CTRL1:
	हाल RT5660_DRC2_CTRL2:
	हाल RT5660_DRC2_CTRL3:
	हाल RT5660_DRC2_CTRL4:
	हाल RT5660_DRC2_CTRL5:
	हाल RT5660_ALC_PGA_CTRL1:
	हाल RT5660_ALC_PGA_CTRL2:
	हाल RT5660_ALC_PGA_CTRL3:
	हाल RT5660_ALC_PGA_CTRL4:
	हाल RT5660_ALC_PGA_CTRL5:
	हाल RT5660_ALC_PGA_CTRL6:
	हाल RT5660_ALC_PGA_CTRL7:
	हाल RT5660_GEN_CTRL1:
	हाल RT5660_GEN_CTRL2:
	हाल RT5660_GEN_CTRL3:
	हाल RT5660_VENDOR_ID:
	हाल RT5660_VENDOR_ID1:
	हाल RT5660_VENDOR_ID2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(rt5660_out_vol_tlv, -4650, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(rt5660_dac_vol_tlv, -6525, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(rt5660_adc_vol_tlv, -1725, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(rt5660_adc_bst_tlv, 0, 1200, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(rt5660_bst_tlv, -1200, 75, 0);

अटल स्थिर काष्ठा snd_kcontrol_new rt5660_snd_controls[] = अणु
	/* Speaker Output Volume */
	SOC_SINGLE("Speaker Playback Switch", RT5660_SPK_VOL, RT5660_L_MUTE_SFT,
		1, 1),
	SOC_SINGLE_TLV("Speaker Playback Volume", RT5660_SPK_VOL,
		RT5660_L_VOL_SFT, 39, 1, rt5660_out_vol_tlv),

	/* OUTPUT Control */
	SOC_DOUBLE("OUT Playback Switch", RT5660_LOUT_VOL, RT5660_L_MUTE_SFT,
		RT5660_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE_TLV("OUT Playback Volume", RT5660_LOUT_VOL, RT5660_L_VOL_SFT,
		RT5660_R_VOL_SFT, 39, 1, rt5660_out_vol_tlv),

	/* DAC Digital Volume */
	SOC_DOUBLE_TLV("DAC1 Playback Volume", RT5660_DAC1_DIG_VOL,
		RT5660_DAC_L1_VOL_SFT, RT5660_DAC_R1_VOL_SFT, 87, 0,
		rt5660_dac_vol_tlv),

	/* IN1/IN2/IN3 Control */
	SOC_SINGLE_TLV("IN1 Boost Volume", RT5660_IN1_IN2, RT5660_BST_SFT1, 69,
		0, rt5660_bst_tlv),
	SOC_SINGLE_TLV("IN2 Boost Volume", RT5660_IN1_IN2, RT5660_BST_SFT2, 69,
		0, rt5660_bst_tlv),
	SOC_SINGLE_TLV("IN3 Boost Volume", RT5660_IN3_IN4, RT5660_BST_SFT3, 69,
		0, rt5660_bst_tlv),

	/* ADC Digital Volume Control */
	SOC_DOUBLE("ADC Capture Switch", RT5660_STO1_ADC_DIG_VOL,
		RT5660_L_MUTE_SFT, RT5660_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE_TLV("ADC Capture Volume", RT5660_STO1_ADC_DIG_VOL,
		RT5660_ADC_L_VOL_SFT, RT5660_ADC_R_VOL_SFT, 63, 0,
		rt5660_adc_vol_tlv),

	/* ADC Boost Volume Control */
	SOC_DOUBLE_TLV("STO1 ADC Boost Gain Volume", RT5660_ADC_BST_VOL1,
		RT5660_STO1_ADC_L_BST_SFT, RT5660_STO1_ADC_R_BST_SFT, 3, 0,
		rt5660_adc_bst_tlv),
पूर्ण;

/**
 * rt5660_set_dmic_clk - Set parameter of dmic.
 *
 * @w: DAPM widget.
 * @kcontrol: The kcontrol of this widget.
 * @event: Event id.
 *
 */
अटल पूर्णांक rt5660_set_dmic_clk(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5660_priv *rt5660 = snd_soc_component_get_drvdata(component);
	पूर्णांक idx, rate;

	rate = rt5660->sysclk / rl6231_get_pre_भाग(rt5660->regmap,
		RT5660_ADDA_CLK1, RT5660_I2S_PD1_SFT);
	idx = rl6231_calc_dmic_clk(rate);
	अगर (idx < 0)
		dev_err(component->dev, "Failed to set DMIC clock\n");
	अन्यथा
		snd_soc_component_update_bits(component, RT5660_DMIC_CTRL1,
			RT5660_DMIC_CLK_MASK, idx << RT5660_DMIC_CLK_SFT);

	वापस idx;
पूर्ण

अटल पूर्णांक rt5660_is_sys_clk_from_pll(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	अचिन्हित पूर्णांक val;

	val = snd_soc_component_पढ़ो(component, RT5660_GLB_CLK);
	val &= RT5660_SCLK_SRC_MASK;
	अगर (val == RT5660_SCLK_SRC_PLL1)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/* Digital Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt5660_sto1_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5660_STO1_ADC_MIXER,
			RT5660_M_ADC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5660_STO1_ADC_MIXER,
			RT5660_M_ADC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5660_sto1_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5660_STO1_ADC_MIXER,
			RT5660_M_ADC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5660_STO1_ADC_MIXER,
			RT5660_M_ADC_R2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5660_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("Stereo ADC Switch", RT5660_AD_DA_MIXER,
			RT5660_M_ADCMIX_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC1 Switch", RT5660_AD_DA_MIXER,
			RT5660_M_DAC1_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5660_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("Stereo ADC Switch", RT5660_AD_DA_MIXER,
			RT5660_M_ADCMIX_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC1 Switch", RT5660_AD_DA_MIXER,
			RT5660_M_DAC1_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5660_sto_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5660_STO_DAC_MIXER,
			RT5660_M_DAC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5660_STO_DAC_MIXER,
			RT5660_M_DAC_R1_STO_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5660_sto_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5660_STO_DAC_MIXER,
			RT5660_M_DAC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5660_STO_DAC_MIXER,
			RT5660_M_DAC_L1_STO_R_SFT, 1, 1),
पूर्ण;

/* Analog Input Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt5660_rec_l_mix[] = अणु
	SOC_DAPM_SINGLE("BST3 Switch", RT5660_REC_L2_MIXER,
			RT5660_M_BST3_RM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5660_REC_L2_MIXER,
			RT5660_M_BST2_RM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5660_REC_L2_MIXER,
			RT5660_M_BST1_RM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUT MIXL Switch", RT5660_REC_L2_MIXER,
			RT5660_M_OM_L_RM_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5660_rec_r_mix[] = अणु
	SOC_DAPM_SINGLE("BST3 Switch", RT5660_REC_R2_MIXER,
			RT5660_M_BST3_RM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5660_REC_R2_MIXER,
			RT5660_M_BST2_RM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5660_REC_R2_MIXER,
			RT5660_M_BST1_RM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUT MIXR Switch", RT5660_REC_R2_MIXER,
			RT5660_M_OM_R_RM_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5660_spk_mix[] = अणु
	SOC_DAPM_SINGLE("BST3 Switch", RT5660_SPK_MIXER,
			RT5660_M_BST3_SM_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5660_SPK_MIXER,
			RT5660_M_BST1_SM_SFT, 1, 1),
	SOC_DAPM_SINGLE("DACL Switch", RT5660_SPK_MIXER,
			RT5660_M_DACL_SM_SFT, 1, 1),
	SOC_DAPM_SINGLE("DACR Switch", RT5660_SPK_MIXER,
			RT5660_M_DACR_SM_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUTMIXL Switch", RT5660_SPK_MIXER,
			RT5660_M_OM_L_SM_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5660_out_l_mix[] = अणु
	SOC_DAPM_SINGLE("BST3 Switch", RT5660_OUT_L1_MIXER,
			RT5660_M_BST3_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5660_OUT_L1_MIXER,
			RT5660_M_BST2_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5660_OUT_L1_MIXER,
			RT5660_M_BST1_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("RECMIXL Switch", RT5660_OUT_L1_MIXER,
			RT5660_M_RM_L_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DACR Switch", RT5660_OUT_L1_MIXER,
			RT5660_M_DAC_R_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DACL Switch", RT5660_OUT_L1_MIXER,
			RT5660_M_DAC_L_OM_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5660_out_r_mix[] = अणु
	SOC_DAPM_SINGLE("BST2 Switch", RT5660_OUT_R1_MIXER,
			RT5660_M_BST2_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5660_OUT_R1_MIXER,
			RT5660_M_BST1_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("RECMIXR Switch", RT5660_OUT_R1_MIXER,
			RT5660_M_RM_R_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DACR Switch", RT5660_OUT_R1_MIXER,
			RT5660_M_DAC_R_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DACL Switch", RT5660_OUT_R1_MIXER,
			RT5660_M_DAC_L_OM_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5660_spo_mix[] = अणु
	SOC_DAPM_SINGLE("DACR Switch", RT5660_SPO_MIXER,
			RT5660_M_DAC_R_SPM_SFT, 1, 1),
	SOC_DAPM_SINGLE("DACL Switch", RT5660_SPO_MIXER,
			RT5660_M_DAC_L_SPM_SFT, 1, 1),
	SOC_DAPM_SINGLE("SPKVOL Switch", RT5660_SPO_MIXER,
			RT5660_M_SV_SPM_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5660_SPO_MIXER,
			RT5660_M_BST1_SPM_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5660_lout_mix[] = अणु
	SOC_DAPM_SINGLE("DAC Switch", RT5660_LOUT_MIXER,
			RT5660_M_DAC1_LM_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUTMIX Switch", RT5660_LOUT_MIXER,
			RT5660_M_LOVOL_LM_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new spk_vol_control =
	SOC_DAPM_SINGLE("Switch", RT5660_SPK_VOL,
		RT5660_VOL_L_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new lout_l_vol_control =
	SOC_DAPM_SINGLE("Switch", RT5660_LOUT_VOL,
		RT5660_VOL_L_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new lout_r_vol_control =
	SOC_DAPM_SINGLE("Switch", RT5660_LOUT_VOL,
		RT5660_VOL_R_SFT, 1, 1);

/* Interface data select */
अटल स्थिर अक्षर * स्थिर rt5660_data_select[] = अणु
	"L/R", "R/L", "L/L", "R/R"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5660_अगर1_dac_क्रमागत,
	RT5660_DIG_INF1_DATA, RT5660_IF1_DAC_IN_SFT, rt5660_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5660_अगर1_adc_क्रमागत,
	RT5660_DIG_INF1_DATA, RT5660_IF1_ADC_IN_SFT, rt5660_data_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt5660_अगर1_dac_swap_mux =
	SOC_DAPM_ENUM("IF1 DAC Swap Source", rt5660_अगर1_dac_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rt5660_अगर1_adc_swap_mux =
	SOC_DAPM_ENUM("IF1 ADC Swap Source", rt5660_अगर1_adc_क्रमागत);

अटल पूर्णांक rt5660_lout_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, RT5660_LOUT_AMP_CTRL,
			RT5660_LOUT_CO_MASK | RT5660_LOUT_CB_MASK,
			RT5660_LOUT_CO_EN | RT5660_LOUT_CB_PU);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT5660_LOUT_AMP_CTRL,
			RT5660_LOUT_CO_MASK | RT5660_LOUT_CB_MASK,
			RT5660_LOUT_CO_DIS | RT5660_LOUT_CB_PD);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget rt5660_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("LDO2", RT5660_PWR_ANLG1,
		RT5660_PWR_LDO2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL1", RT5660_PWR_ANLG2,
		RT5660_PWR_PLL_BIT, 0, शून्य, 0),

	/* MICBIAS */
	SND_SOC_DAPM_SUPPLY("MICBIAS1", RT5660_PWR_ANLG2,
			RT5660_PWR_MB1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MICBIAS2", RT5660_PWR_ANLG2,
			RT5660_PWR_MB2_BIT, 0, शून्य, 0),

	/* Input Side */
	/* Input Lines */
	SND_SOC_DAPM_INPUT("DMIC L1"),
	SND_SOC_DAPM_INPUT("DMIC R1"),

	SND_SOC_DAPM_INPUT("IN1P"),
	SND_SOC_DAPM_INPUT("IN1N"),
	SND_SOC_DAPM_INPUT("IN2P"),
	SND_SOC_DAPM_INPUT("IN3P"),
	SND_SOC_DAPM_INPUT("IN3N"),

	SND_SOC_DAPM_SUPPLY("DMIC CLK", SND_SOC_NOPM, 0, 0,
		rt5660_set_dmic_clk, SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_SUPPLY("DMIC Power", RT5660_DMIC_CTRL1,
		RT5660_DMIC_1_EN_SFT, 0, शून्य, 0),

	/* Boost */
	SND_SOC_DAPM_PGA("BST1", RT5660_PWR_ANLG2, RT5660_PWR_BST1_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_PGA("BST2", RT5660_PWR_ANLG2, RT5660_PWR_BST2_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_PGA("BST3", RT5660_PWR_ANLG2, RT5660_PWR_BST3_BIT, 0,
		शून्य, 0),

	/* REC Mixer */
	SND_SOC_DAPM_MIXER("RECMIXL", RT5660_PWR_MIXER, RT5660_PWR_RM_L_BIT,
			0, rt5660_rec_l_mix, ARRAY_SIZE(rt5660_rec_l_mix)),
	SND_SOC_DAPM_MIXER("RECMIXR", RT5660_PWR_MIXER, RT5660_PWR_RM_R_BIT,
			0, rt5660_rec_r_mix, ARRAY_SIZE(rt5660_rec_r_mix)),

	/* ADCs */
	SND_SOC_DAPM_ADC("ADC L", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC R", शून्य, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_SUPPLY("ADC L power", RT5660_PWR_DIG1,
			RT5660_PWR_ADC_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC R power", RT5660_PWR_DIG1,
			RT5660_PWR_ADC_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC clock", RT5660_PR_BASE + RT5660_CHOP_DAC_ADC,
			12, 0, शून्य, 0),

	/* ADC Mixer */
	SND_SOC_DAPM_SUPPLY("adc stereo1 filter", RT5660_PWR_DIG2,
		RT5660_PWR_ADC_S1F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Sto1 ADC MIXL", SND_SOC_NOPM, 0, 0,
		rt5660_sto1_adc_l_mix, ARRAY_SIZE(rt5660_sto1_adc_l_mix)),
	SND_SOC_DAPM_MIXER("Sto1 ADC MIXR", SND_SOC_NOPM, 0, 0,
		rt5660_sto1_adc_r_mix, ARRAY_SIZE(rt5660_sto1_adc_r_mix)),

	/* ADC */
	SND_SOC_DAPM_ADC("Stereo1 ADC MIXL", शून्य, RT5660_STO1_ADC_DIG_VOL,
		RT5660_L_MUTE_SFT, 1),
	SND_SOC_DAPM_ADC("Stereo1 ADC MIXR", शून्य, RT5660_STO1_ADC_DIG_VOL,
		RT5660_R_MUTE_SFT, 1),

	/* Digital Interface */
	SND_SOC_DAPM_SUPPLY("I2S1", RT5660_PWR_DIG1, RT5660_PWR_I2S1_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MUX("IF1 DAC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5660_अगर1_dac_swap_mux),
	SND_SOC_DAPM_PGA("IF1 ADC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MUX("IF1 ADC Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt5660_अगर1_adc_swap_mux),

	/* Audio Interface */
	SND_SOC_DAPM_AIF_IN("AIF1RX", "AIF1 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX", "AIF1 Capture", 0, SND_SOC_NOPM, 0, 0),

	/* Output Side */
	/* DAC mixer beक्रमe sound effect  */
	SND_SOC_DAPM_MIXER("DAC1 MIXL", SND_SOC_NOPM, 0, 0, rt5660_dac_l_mix,
		ARRAY_SIZE(rt5660_dac_l_mix)),
	SND_SOC_DAPM_MIXER("DAC1 MIXR", SND_SOC_NOPM, 0, 0, rt5660_dac_r_mix,
		ARRAY_SIZE(rt5660_dac_r_mix)),

	/* DAC Mixer */
	SND_SOC_DAPM_SUPPLY("dac stereo1 filter", RT5660_PWR_DIG2,
		RT5660_PWR_DAC_S1F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Stereo DAC MIXL", SND_SOC_NOPM, 0, 0,
		rt5660_sto_dac_l_mix, ARRAY_SIZE(rt5660_sto_dac_l_mix)),
	SND_SOC_DAPM_MIXER("Stereo DAC MIXR", SND_SOC_NOPM, 0, 0,
		rt5660_sto_dac_r_mix, ARRAY_SIZE(rt5660_sto_dac_r_mix)),

	/* DACs */
	SND_SOC_DAPM_DAC("DAC L1", शून्य, RT5660_PWR_DIG1,
			RT5660_PWR_DAC_L1_BIT, 0),
	SND_SOC_DAPM_DAC("DAC R1", शून्य, RT5660_PWR_DIG1,
			RT5660_PWR_DAC_R1_BIT, 0),

	/* OUT Mixer */
	SND_SOC_DAPM_MIXER("SPK MIX", RT5660_PWR_MIXER, RT5660_PWR_SM_BIT,
		0, rt5660_spk_mix, ARRAY_SIZE(rt5660_spk_mix)),
	SND_SOC_DAPM_MIXER("OUT MIXL", RT5660_PWR_MIXER, RT5660_PWR_OM_L_BIT,
		0, rt5660_out_l_mix, ARRAY_SIZE(rt5660_out_l_mix)),
	SND_SOC_DAPM_MIXER("OUT MIXR", RT5660_PWR_MIXER, RT5660_PWR_OM_R_BIT,
		0, rt5660_out_r_mix, ARRAY_SIZE(rt5660_out_r_mix)),

	/* Output Volume */
	SND_SOC_DAPM_SWITCH("SPKVOL", RT5660_PWR_VOL,
		RT5660_PWR_SV_BIT, 0, &spk_vol_control),
	SND_SOC_DAPM_PGA("DAC 1", SND_SOC_NOPM,
		0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("LOUTVOL", SND_SOC_NOPM,
		0, 0, शून्य, 0),
	SND_SOC_DAPM_SWITCH("LOUTVOL L", SND_SOC_NOPM,
		RT5660_PWR_LV_L_BIT, 0, &lout_l_vol_control),
	SND_SOC_DAPM_SWITCH("LOUTVOL R", SND_SOC_NOPM,
		RT5660_PWR_LV_R_BIT, 0, &lout_r_vol_control),

	/* HPO/LOUT/Mono Mixer */
	SND_SOC_DAPM_MIXER("SPO MIX", SND_SOC_NOPM, 0,
		0, rt5660_spo_mix, ARRAY_SIZE(rt5660_spo_mix)),
	SND_SOC_DAPM_MIXER("LOUT MIX", SND_SOC_NOPM, 0, 0,
		rt5660_lout_mix, ARRAY_SIZE(rt5660_lout_mix)),
	SND_SOC_DAPM_SUPPLY("VREF HP", RT5660_GEN_CTRL1,
		RT5660_PWR_VREF_HP_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA_S("LOUT amp", 1, RT5660_PWR_ANLG1,
		RT5660_PWR_HA_BIT, 0, rt5660_lout_event,
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_S("SPK amp", 1, RT5660_PWR_DIG1,
		RT5660_PWR_CLS_D_BIT, 0, शून्य, 0),

	/* Output Lines */
	SND_SOC_DAPM_OUTPUT("LOUTL"),
	SND_SOC_DAPM_OUTPUT("LOUTR"),
	SND_SOC_DAPM_OUTPUT("SPO"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5660_dapm_routes[] = अणु
	अणु "MICBIAS1", शून्य, "LDO2" पूर्ण,
	अणु "MICBIAS2", शून्य, "LDO2" पूर्ण,

	अणु "BST1", शून्य, "IN1P" पूर्ण,
	अणु "BST1", शून्य, "IN1N" पूर्ण,
	अणु "BST2", शून्य, "IN2P" पूर्ण,
	अणु "BST3", शून्य, "IN3P" पूर्ण,
	अणु "BST3", शून्य, "IN3N" पूर्ण,

	अणु "RECMIXL", "BST3 Switch", "BST3" पूर्ण,
	अणु "RECMIXL", "BST2 Switch", "BST2" पूर्ण,
	अणु "RECMIXL", "BST1 Switch", "BST1" पूर्ण,
	अणु "RECMIXL", "OUT MIXL Switch", "OUT MIXL" पूर्ण,

	अणु "RECMIXR", "BST3 Switch", "BST3" पूर्ण,
	अणु "RECMIXR", "BST2 Switch", "BST2" पूर्ण,
	अणु "RECMIXR", "BST1 Switch", "BST1" पूर्ण,
	अणु "RECMIXR", "OUT MIXR Switch", "OUT MIXR" पूर्ण,

	अणु "ADC L", शून्य, "RECMIXL" पूर्ण,
	अणु "ADC L", शून्य, "ADC L power" पूर्ण,
	अणु "ADC L", शून्य, "ADC clock" पूर्ण,
	अणु "ADC R", शून्य, "RECMIXR" पूर्ण,
	अणु "ADC R", शून्य, "ADC R power" पूर्ण,
	अणु "ADC R", शून्य, "ADC clock" पूर्ण,

	अणु"DMIC L1", शून्य, "DMIC CLK"पूर्ण,
	अणु"DMIC L1", शून्य, "DMIC Power"पूर्ण,
	अणु"DMIC R1", शून्य, "DMIC CLK"पूर्ण,
	अणु"DMIC R1", शून्य, "DMIC Power"पूर्ण,

	अणु "Sto1 ADC MIXL", "ADC1 Switch", "ADC L" पूर्ण,
	अणु "Sto1 ADC MIXL", "ADC2 Switch", "DMIC L1" पूर्ण,
	अणु "Sto1 ADC MIXR", "ADC1 Switch", "ADC R" पूर्ण,
	अणु "Sto1 ADC MIXR", "ADC2 Switch", "DMIC R1" पूर्ण,

	अणु "Stereo1 ADC MIXL", शून्य, "Sto1 ADC MIXL" पूर्ण,
	अणु "Stereo1 ADC MIXL", शून्य, "adc stereo1 filter" पूर्ण,
	अणु "adc stereo1 filter", शून्य, "PLL1", rt5660_is_sys_clk_from_pll पूर्ण,

	अणु "Stereo1 ADC MIXR", शून्य, "Sto1 ADC MIXR" पूर्ण,
	अणु "Stereo1 ADC MIXR", शून्य, "adc stereo1 filter" पूर्ण,
	अणु "adc stereo1 filter", शून्य, "PLL1", rt5660_is_sys_clk_from_pll पूर्ण,

	अणु "IF1 ADC", शून्य, "Stereo1 ADC MIXL" पूर्ण,
	अणु "IF1 ADC", शून्य, "Stereo1 ADC MIXR" पूर्ण,
	अणु "IF1 ADC", शून्य, "I2S1" पूर्ण,

	अणु "IF1 ADC Swap Mux", "L/R", "IF1 ADC" पूर्ण,
	अणु "IF1 ADC Swap Mux", "R/L", "IF1 ADC" पूर्ण,
	अणु "IF1 ADC Swap Mux", "L/L", "IF1 ADC" पूर्ण,
	अणु "IF1 ADC Swap Mux", "R/R", "IF1 ADC" पूर्ण,
	अणु "AIF1TX", शून्य, "IF1 ADC Swap Mux" पूर्ण,

	अणु "IF1 DAC", शून्य, "AIF1RX" पूर्ण,
	अणु "IF1 DAC", शून्य, "I2S1" पूर्ण,

	अणु "IF1 DAC Swap Mux", "L/R", "IF1 DAC" पूर्ण,
	अणु "IF1 DAC Swap Mux", "R/L", "IF1 DAC" पूर्ण,
	अणु "IF1 DAC Swap Mux", "L/L", "IF1 DAC" पूर्ण,
	अणु "IF1 DAC Swap Mux", "R/R", "IF1 DAC" पूर्ण,

	अणु "IF1 DAC L", शून्य, "IF1 DAC Swap Mux" पूर्ण,
	अणु "IF1 DAC R", शून्य, "IF1 DAC Swap Mux" पूर्ण,

	अणु "DAC1 MIXL", "Stereo ADC Switch", "Stereo1 ADC MIXL" पूर्ण,
	अणु "DAC1 MIXL", "DAC1 Switch", "IF1 DAC L" पूर्ण,
	अणु "DAC1 MIXR", "Stereo ADC Switch", "Stereo1 ADC MIXR" पूर्ण,
	अणु "DAC1 MIXR", "DAC1 Switch", "IF1 DAC R" पूर्ण,

	अणु "Stereo DAC MIXL", "DAC L1 Switch", "DAC1 MIXL" पूर्ण,
	अणु "Stereo DAC MIXL", "DAC R1 Switch", "DAC1 MIXR" पूर्ण,
	अणु "Stereo DAC MIXL", शून्य, "dac stereo1 filter" पूर्ण,
	अणु "dac stereo1 filter", शून्य, "PLL1", rt5660_is_sys_clk_from_pll पूर्ण,
	अणु "Stereo DAC MIXR", "DAC R1 Switch", "DAC1 MIXR" पूर्ण,
	अणु "Stereo DAC MIXR", "DAC L1 Switch", "DAC1 MIXL" पूर्ण,
	अणु "Stereo DAC MIXR", शून्य, "dac stereo1 filter" पूर्ण,
	अणु "dac stereo1 filter", शून्य, "PLL1", rt5660_is_sys_clk_from_pll पूर्ण,

	अणु "DAC L1", शून्य, "Stereo DAC MIXL" पूर्ण,
	अणु "DAC R1", शून्य, "Stereo DAC MIXR" पूर्ण,

	अणु "SPK MIX", "BST3 Switch", "BST3" पूर्ण,
	अणु "SPK MIX", "BST1 Switch", "BST1" पूर्ण,
	अणु "SPK MIX", "DACL Switch", "DAC L1" पूर्ण,
	अणु "SPK MIX", "DACR Switch", "DAC R1" पूर्ण,
	अणु "SPK MIX", "OUTMIXL Switch", "OUT MIXL" पूर्ण,

	अणु "OUT MIXL", "BST3 Switch", "BST3" पूर्ण,
	अणु "OUT MIXL", "BST2 Switch", "BST2" पूर्ण,
	अणु "OUT MIXL", "BST1 Switch", "BST1" पूर्ण,
	अणु "OUT MIXL", "RECMIXL Switch", "RECMIXL" पूर्ण,
	अणु "OUT MIXL", "DACR Switch", "DAC R1" पूर्ण,
	अणु "OUT MIXL", "DACL Switch", "DAC L1" पूर्ण,

	अणु "OUT MIXR", "BST2 Switch", "BST2" पूर्ण,
	अणु "OUT MIXR", "BST1 Switch", "BST1" पूर्ण,
	अणु "OUT MIXR", "RECMIXR Switch", "RECMIXR" पूर्ण,
	अणु "OUT MIXR", "DACR Switch", "DAC R1" पूर्ण,
	अणु "OUT MIXR", "DACL Switch", "DAC L1" पूर्ण,

	अणु "SPO MIX", "DACR Switch", "DAC R1" पूर्ण,
	अणु "SPO MIX", "DACL Switch", "DAC L1" पूर्ण,
	अणु "SPO MIX", "SPKVOL Switch", "SPKVOL" पूर्ण,
	अणु "SPO MIX", "BST1 Switch", "BST1" पूर्ण,

	अणु "SPKVOL", "Switch", "SPK MIX" पूर्ण,
	अणु "LOUTVOL L", "Switch", "OUT MIXL" पूर्ण,
	अणु "LOUTVOL R", "Switch", "OUT MIXR" पूर्ण,

	अणु "LOUTVOL", शून्य, "LOUTVOL L" पूर्ण,
	अणु "LOUTVOL", शून्य, "LOUTVOL R" पूर्ण,

	अणु "DAC 1", शून्य, "DAC L1" पूर्ण,
	अणु "DAC 1", शून्य, "DAC R1" पूर्ण,

	अणु "LOUT MIX", "DAC Switch", "DAC 1" पूर्ण,
	अणु "LOUT MIX", "OUTMIX Switch", "LOUTVOL" पूर्ण,

	अणु "LOUT amp", शून्य, "LOUT MIX" पूर्ण,
	अणु "LOUT amp", शून्य, "VREF HP" पूर्ण,
	अणु "LOUTL", शून्य, "LOUT amp" पूर्ण,
	अणु "LOUTR", शून्य, "LOUT amp" पूर्ण,

	अणु "SPK amp", शून्य, "SPO MIX" पूर्ण,
	अणु "SPO", शून्य, "SPK amp" पूर्ण,
पूर्ण;

अटल पूर्णांक rt5660_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5660_priv *rt5660 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val_len = 0, val_clk, mask_clk;
	पूर्णांक pre_भाग, bclk_ms, frame_size;

	rt5660->lrck[dai->id] = params_rate(params);
	pre_भाग = rl6231_get_clk_info(rt5660->sysclk, rt5660->lrck[dai->id]);
	अगर (pre_भाग < 0) अणु
		dev_err(component->dev, "Unsupported clock setting %d for DAI %d\n",
			rt5660->lrck[dai->id], dai->id);
		वापस -EINVAL;
	पूर्ण

	frame_size = snd_soc_params_to_frame_size(params);
	अगर (frame_size < 0) अणु
		dev_err(component->dev, "Unsupported frame size: %d\n", frame_size);
		वापस frame_size;
	पूर्ण

	अगर (frame_size > 32)
		bclk_ms = 1;
	अन्यथा
		bclk_ms = 0;

	rt5660->bclk[dai->id] = rt5660->lrck[dai->id] * (32 << bclk_ms);

	dev_dbg(dai->dev, "bclk is %dHz and lrck is %dHz\n",
		rt5660->bclk[dai->id], rt5660->lrck[dai->id]);
	dev_dbg(dai->dev, "bclk_ms is %d and pre_div is %d for iis %d\n",
				bclk_ms, pre_भाग, dai->id);

	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		val_len |= RT5660_I2S_DL_20;
		अवरोध;
	हाल 24:
		val_len |= RT5660_I2S_DL_24;
		अवरोध;
	हाल 8:
		val_len |= RT5660_I2S_DL_8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT5660_AIF1:
		mask_clk = RT5660_I2S_BCLK_MS1_MASK | RT5660_I2S_PD1_MASK;
		val_clk = bclk_ms << RT5660_I2S_BCLK_MS1_SFT |
			pre_भाग << RT5660_I2S_PD1_SFT;
		snd_soc_component_update_bits(component, RT5660_I2S1_SDP, RT5660_I2S_DL_MASK,
			val_len);
		snd_soc_component_update_bits(component, RT5660_ADDA_CLK1, mask_clk, val_clk);
		अवरोध;

	शेष:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5660_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5660_priv *rt5660 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		rt5660->master[dai->id] = 1;
		अवरोध;

	हाल SND_SOC_DAIFMT_CBS_CFS:
		reg_val |= RT5660_I2S_MS_S;
		rt5660->master[dai->id] = 0;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;

	हाल SND_SOC_DAIFMT_IB_NF:
		reg_val |= RT5660_I2S_BP_INV;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;

	हाल SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT5660_I2S_DF_LEFT;
		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT5660_I2S_DF_PCM_A;
		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_B:
		reg_val  |= RT5660_I2S_DF_PCM_B;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT5660_AIF1:
		snd_soc_component_update_bits(component, RT5660_I2S1_SDP,
			RT5660_I2S_MS_MASK | RT5660_I2S_BP_MASK |
			RT5660_I2S_DF_MASK, reg_val);
		अवरोध;

	शेष:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5660_set_dai_sysclk(काष्ठा snd_soc_dai *dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5660_priv *rt5660 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;

	अगर (freq == rt5660->sysclk && clk_id == rt5660->sysclk_src)
		वापस 0;

	चयन (clk_id) अणु
	हाल RT5660_SCLK_S_MCLK:
		reg_val |= RT5660_SCLK_SRC_MCLK;
		अवरोध;

	हाल RT5660_SCLK_S_PLL1:
		reg_val |= RT5660_SCLK_SRC_PLL1;
		अवरोध;

	हाल RT5660_SCLK_S_RCCLK:
		reg_val |= RT5660_SCLK_SRC_RCCLK;
		अवरोध;

	शेष:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, RT5660_GLB_CLK, RT5660_SCLK_SRC_MASK,
		reg_val);

	rt5660->sysclk = freq;
	rt5660->sysclk_src = clk_id;

	dev_dbg(dai->dev, "Sysclk is %dHz and clock id is %d\n", freq, clk_id);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5660_set_dai_pll(काष्ठा snd_soc_dai *dai, पूर्णांक pll_id, पूर्णांक source,
			अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5660_priv *rt5660 = snd_soc_component_get_drvdata(component);
	काष्ठा rl6231_pll_code pll_code;
	पूर्णांक ret;

	अगर (source == rt5660->pll_src && freq_in == rt5660->pll_in &&
		freq_out == rt5660->pll_out)
		वापस 0;

	अगर (!freq_in || !freq_out) अणु
		dev_dbg(component->dev, "PLL disabled\n");

		rt5660->pll_in = 0;
		rt5660->pll_out = 0;
		snd_soc_component_update_bits(component, RT5660_GLB_CLK,
			RT5660_SCLK_SRC_MASK, RT5660_SCLK_SRC_MCLK);
		वापस 0;
	पूर्ण

	चयन (source) अणु
	हाल RT5660_PLL1_S_MCLK:
		snd_soc_component_update_bits(component, RT5660_GLB_CLK,
			RT5660_PLL1_SRC_MASK, RT5660_PLL1_SRC_MCLK);
		अवरोध;

	हाल RT5660_PLL1_S_BCLK:
		snd_soc_component_update_bits(component, RT5660_GLB_CLK,
			RT5660_PLL1_SRC_MASK, RT5660_PLL1_SRC_BCLK1);
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

	snd_soc_component_ग_लिखो(component, RT5660_PLL_CTRL1,
		pll_code.n_code << RT5660_PLL_N_SFT | pll_code.k_code);
	snd_soc_component_ग_लिखो(component, RT5660_PLL_CTRL2,
		((pll_code.m_bp ? 0 : pll_code.m_code) << RT5660_PLL_M_SFT) |
		(pll_code.m_bp << RT5660_PLL_M_BP_SFT));

	rt5660->pll_in = freq_in;
	rt5660->pll_out = freq_out;
	rt5660->pll_src = source;

	वापस 0;
पूर्ण

अटल पूर्णांक rt5660_set_bias_level(काष्ठा snd_soc_component *component,
			क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा rt5660_priv *rt5660 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		snd_soc_component_update_bits(component, RT5660_GEN_CTRL1,
			RT5660_DIG_GATE_CTRL, RT5660_DIG_GATE_CTRL);

		अगर (IS_ERR(rt5660->mclk))
			अवरोध;

		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_ON) अणु
			clk_disable_unprepare(rt5660->mclk);
		पूर्ण अन्यथा अणु
			ret = clk_prepare_enable(rt5660->mclk);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			snd_soc_component_update_bits(component, RT5660_PWR_ANLG1,
				RT5660_PWR_VREF1 | RT5660_PWR_MB |
				RT5660_PWR_BG | RT5660_PWR_VREF2,
				RT5660_PWR_VREF1 | RT5660_PWR_MB |
				RT5660_PWR_BG | RT5660_PWR_VREF2);
			usleep_range(10000, 15000);
			snd_soc_component_update_bits(component, RT5660_PWR_ANLG1,
				RT5660_PWR_FV1 | RT5660_PWR_FV2,
				RT5660_PWR_FV1 | RT5660_PWR_FV2);
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, RT5660_GEN_CTRL1,
			RT5660_DIG_GATE_CTRL, 0);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5660_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5660_priv *rt5660 = snd_soc_component_get_drvdata(component);

	rt5660->component = component;

	वापस 0;
पूर्ण

अटल व्योम rt5660_हटाओ(काष्ठा snd_soc_component *component)
अणु
	snd_soc_component_ग_लिखो(component, RT5660_RESET, 0);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rt5660_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5660_priv *rt5660 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt5660->regmap, true);
	regcache_mark_dirty(rt5660->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5660_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5660_priv *rt5660 = snd_soc_component_get_drvdata(component);

	अगर (rt5660->pdata.घातeroff_codec_in_suspend)
		msleep(350);

	regcache_cache_only(rt5660->regmap, false);
	regcache_sync(rt5660->regmap);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा rt5660_suspend शून्य
#घोषणा rt5660_resume शून्य
#पूर्ण_अगर

#घोषणा RT5660_STEREO_RATES SNDRV_PCM_RATE_8000_192000
#घोषणा RT5660_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S8)

अटल स्थिर काष्ठा snd_soc_dai_ops rt5660_aअगर_dai_ops = अणु
	.hw_params = rt5660_hw_params,
	.set_fmt = rt5660_set_dai_fmt,
	.set_sysclk = rt5660_set_dai_sysclk,
	.set_pll = rt5660_set_dai_pll,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt5660_dai[] = अणु
	अणु
		.name = "rt5660-aif1",
		.id = RT5660_AIF1,
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5660_STEREO_RATES,
			.क्रमmats = RT5660_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5660_STEREO_RATES,
			.क्रमmats = RT5660_FORMATS,
		पूर्ण,
		.ops = &rt5660_aअगर_dai_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_rt5660 = अणु
	.probe			= rt5660_probe,
	.हटाओ			= rt5660_हटाओ,
	.suspend		= rt5660_suspend,
	.resume			= rt5660_resume,
	.set_bias_level		= rt5660_set_bias_level,
	.controls		= rt5660_snd_controls,
	.num_controls		= ARRAY_SIZE(rt5660_snd_controls),
	.dapm_widमाला_लो		= rt5660_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(rt5660_dapm_widमाला_लो),
	.dapm_routes		= rt5660_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(rt5660_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt5660_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,

	.max_रेजिस्टर = RT5660_VENDOR_ID2 + 1 + (ARRAY_SIZE(rt5660_ranges) *
					       RT5660_PR_SPACING),
	.अस्थिर_reg = rt5660_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = rt5660_पढ़ोable_रेजिस्टर,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = rt5660_reg,
	.num_reg_शेषs = ARRAY_SIZE(rt5660_reg),
	.ranges = rt5660_ranges,
	.num_ranges = ARRAY_SIZE(rt5660_ranges),
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id rt5660_i2c_id[] = अणु
	अणु "rt5660", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt5660_i2c_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id rt5660_of_match[] = अणु
	अणु .compatible = "realtek,rt5660", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt5660_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id rt5660_acpi_match[] = अणु
	अणु "10EC5660", 0 पूर्ण,
	अणु "10EC3277", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rt5660_acpi_match);
#पूर्ण_अगर

अटल पूर्णांक rt5660_parse_dt(काष्ठा rt5660_priv *rt5660, काष्ठा device *dev)
अणु
	rt5660->pdata.in1_dअगरf = device_property_पढ़ो_bool(dev,
					"realtek,in1-differential");
	rt5660->pdata.in3_dअगरf = device_property_पढ़ो_bool(dev,
					"realtek,in3-differential");
	rt5660->pdata.घातeroff_codec_in_suspend = device_property_पढ़ो_bool(dev,
					"realtek,poweroff-in-suspend");
	device_property_पढ़ो_u32(dev, "realtek,dmic1-data-pin",
		&rt5660->pdata.dmic1_data_pin);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5660_i2c_probe(काष्ठा i2c_client *i2c,
		    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rt5660_platक्रमm_data *pdata = dev_get_platdata(&i2c->dev);
	काष्ठा rt5660_priv *rt5660;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	rt5660 = devm_kzalloc(&i2c->dev, माप(काष्ठा rt5660_priv),
		GFP_KERNEL);

	अगर (rt5660 == शून्य)
		वापस -ENOMEM;

	/* Check अगर MCLK provided */
	rt5660->mclk = devm_clk_get(&i2c->dev, "mclk");
	अगर (PTR_ERR(rt5660->mclk) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	i2c_set_clientdata(i2c, rt5660);

	अगर (pdata)
		rt5660->pdata = *pdata;
	अन्यथा अगर (i2c->dev.of_node)
		rt5660_parse_dt(rt5660, &i2c->dev);

	rt5660->regmap = devm_regmap_init_i2c(i2c, &rt5660_regmap);
	अगर (IS_ERR(rt5660->regmap)) अणु
		ret = PTR_ERR(rt5660->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	regmap_पढ़ो(rt5660->regmap, RT5660_VENDOR_ID2, &val);
	अगर (val != RT5660_DEVICE_ID) अणु
		dev_err(&i2c->dev,
			"Device with ID register %#x is not rt5660\n", val);
		वापस -ENODEV;
	पूर्ण

	regmap_ग_लिखो(rt5660->regmap, RT5660_RESET, 0);

	ret = regmap_रेजिस्टर_patch(rt5660->regmap, rt5660_patch,
				    ARRAY_SIZE(rt5660_patch));
	अगर (ret != 0)
		dev_warn(&i2c->dev, "Failed to apply regmap patch: %d\n", ret);

	regmap_update_bits(rt5660->regmap, RT5660_GEN_CTRL1,
		RT5660_AUTO_DIS_AMP | RT5660_MCLK_DET | RT5660_POW_CLKDET,
		RT5660_AUTO_DIS_AMP | RT5660_MCLK_DET | RT5660_POW_CLKDET);

	अगर (rt5660->pdata.dmic1_data_pin) अणु
		regmap_update_bits(rt5660->regmap, RT5660_GPIO_CTRL1,
			RT5660_GP1_PIN_MASK, RT5660_GP1_PIN_DMIC1_SCL);

		अगर (rt5660->pdata.dmic1_data_pin == RT5660_DMIC1_DATA_GPIO2)
			regmap_update_bits(rt5660->regmap, RT5660_DMIC_CTRL1,
				RT5660_SEL_DMIC_DATA_MASK,
				RT5660_SEL_DMIC_DATA_GPIO2);
		अन्यथा अगर (rt5660->pdata.dmic1_data_pin == RT5660_DMIC1_DATA_IN1P)
			regmap_update_bits(rt5660->regmap, RT5660_DMIC_CTRL1,
				RT5660_SEL_DMIC_DATA_MASK,
				RT5660_SEL_DMIC_DATA_IN1P);
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				      &soc_component_dev_rt5660,
				      rt5660_dai, ARRAY_SIZE(rt5660_dai));
पूर्ण

अटल काष्ठा i2c_driver rt5660_i2c_driver = अणु
	.driver = अणु
		.name = "rt5660",
		.acpi_match_table = ACPI_PTR(rt5660_acpi_match),
		.of_match_table = of_match_ptr(rt5660_of_match),
	पूर्ण,
	.probe = rt5660_i2c_probe,
	.id_table = rt5660_i2c_id,
पूर्ण;
module_i2c_driver(rt5660_i2c_driver);

MODULE_DESCRIPTION("ASoC RT5660 driver");
MODULE_AUTHOR("Oder Chiou <oder_chiou@realtek.com>");
MODULE_LICENSE("GPL v2");
