<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rt5616.c  --  RT5616 ALSA SoC audio codec driver
 *
 * Copyright 2015 Realtek Semiconductor Corp.
 * Author: Bard Liao <bardliao@realtek.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "rl6231.h"
#समावेश "rt5616.h"

#घोषणा RT5616_PR_RANGE_BASE (0xff + 1)
#घोषणा RT5616_PR_SPACING 0x100

#घोषणा RT5616_PR_BASE (RT5616_PR_RANGE_BASE + (0 * RT5616_PR_SPACING))

अटल स्थिर काष्ठा regmap_range_cfg rt5616_ranges[] = अणु
	अणु
		.name = "PR",
		.range_min = RT5616_PR_BASE,
		.range_max = RT5616_PR_BASE + 0xf8,
		.selector_reg = RT5616_PRIV_INDEX,
		.selector_mask = 0xff,
		.selector_shअगरt = 0x0,
		.winकरोw_start = RT5616_PRIV_DATA,
		.winकरोw_len = 0x1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence init_list[] = अणु
	अणुRT5616_PR_BASE + 0x3d,	0x3e00पूर्ण,
	अणुRT5616_PR_BASE + 0x25,	0x6110पूर्ण,
	अणुRT5616_PR_BASE + 0x20,	0x611fपूर्ण,
	अणुRT5616_PR_BASE + 0x21,	0x4040पूर्ण,
	अणुRT5616_PR_BASE + 0x23,	0x0004पूर्ण,
पूर्ण;

#घोषणा RT5616_INIT_REG_LEN ARRAY_SIZE(init_list)

अटल स्थिर काष्ठा reg_शेष rt5616_reg[] = अणु
	अणु 0x00, 0x0021 पूर्ण,
	अणु 0x02, 0xc8c8 पूर्ण,
	अणु 0x03, 0xc8c8 पूर्ण,
	अणु 0x05, 0x0000 पूर्ण,
	अणु 0x0d, 0x0000 पूर्ण,
	अणु 0x0f, 0x0808 पूर्ण,
	अणु 0x19, 0xafaf पूर्ण,
	अणु 0x1c, 0x2f2f पूर्ण,
	अणु 0x1e, 0x0000 पूर्ण,
	अणु 0x27, 0x7860 पूर्ण,
	अणु 0x29, 0x8080 पूर्ण,
	अणु 0x2a, 0x5252 पूर्ण,
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
	अणु 0x73, 0x1104 पूर्ण,
	अणु 0x74, 0x0c00 पूर्ण,
	अणु 0x80, 0x0000 पूर्ण,
	अणु 0x81, 0x0000 पूर्ण,
	अणु 0x82, 0x0000 पूर्ण,
	अणु 0x8b, 0x0600 पूर्ण,
	अणु 0x8e, 0x0004 पूर्ण,
	अणु 0x8f, 0x1100 पूर्ण,
	अणु 0x90, 0x0000 पूर्ण,
	अणु 0x91, 0x0c00 पूर्ण,
	अणु 0x92, 0x0000 पूर्ण,
	अणु 0x93, 0x2000 पूर्ण,
	अणु 0x94, 0x0200 पूर्ण,
	अणु 0x95, 0x0000 पूर्ण,
	अणु 0xb0, 0x2080 पूर्ण,
	अणु 0xb1, 0x0000 पूर्ण,
	अणु 0xb2, 0x0000 पूर्ण,
	अणु 0xb4, 0x2206 पूर्ण,
	अणु 0xb5, 0x1f00 पूर्ण,
	अणु 0xb6, 0x0000 पूर्ण,
	अणु 0xb7, 0x0000 पूर्ण,
	अणु 0xbb, 0x0000 पूर्ण,
	अणु 0xbc, 0x0000 पूर्ण,
	अणु 0xbd, 0x0000 पूर्ण,
	अणु 0xbe, 0x0000 पूर्ण,
	अणु 0xbf, 0x0000 पूर्ण,
	अणु 0xc0, 0x0100 पूर्ण,
	अणु 0xc1, 0x0000 पूर्ण,
	अणु 0xc2, 0x0000 पूर्ण,
	अणु 0xc8, 0x0000 पूर्ण,
	अणु 0xc9, 0x0000 पूर्ण,
	अणु 0xca, 0x0000 पूर्ण,
	अणु 0xcb, 0x0000 पूर्ण,
	अणु 0xcc, 0x0000 पूर्ण,
	अणु 0xcd, 0x0000 पूर्ण,
	अणु 0xce, 0x0000 पूर्ण,
	अणु 0xcf, 0x0013 पूर्ण,
	अणु 0xd0, 0x0680 पूर्ण,
	अणु 0xd1, 0x1c17 पूर्ण,
	अणु 0xd3, 0xb320 पूर्ण,
	अणु 0xd4, 0x0000 पूर्ण,
	अणु 0xd6, 0x0000 पूर्ण,
	अणु 0xd7, 0x0000 पूर्ण,
	अणु 0xd9, 0x0809 पूर्ण,
	अणु 0xda, 0x0000 पूर्ण,
	अणु 0xfa, 0x0010 पूर्ण,
	अणु 0xfb, 0x0000 पूर्ण,
	अणु 0xfc, 0x0000 पूर्ण,
	अणु 0xfe, 0x10ec पूर्ण,
	अणु 0xff, 0x6281 पूर्ण,
पूर्ण;

काष्ठा rt5616_priv अणु
	काष्ठा snd_soc_component *component;
	काष्ठा delayed_work patch_work;
	काष्ठा regmap *regmap;
	काष्ठा clk *mclk;

	पूर्णांक sysclk;
	पूर्णांक sysclk_src;
	पूर्णांक lrck[RT5616_AIFS];
	पूर्णांक bclk[RT5616_AIFS];
	पूर्णांक master[RT5616_AIFS];

	पूर्णांक pll_src;
	पूर्णांक pll_in;
	पूर्णांक pll_out;

पूर्ण;

अटल bool rt5616_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rt5616_ranges); i++) अणु
		अगर (reg >= rt5616_ranges[i].range_min &&
		    reg <= rt5616_ranges[i].range_max)
			वापस true;
	पूर्ण

	चयन (reg) अणु
	हाल RT5616_RESET:
	हाल RT5616_PRIV_DATA:
	हाल RT5616_EQ_CTRL1:
	हाल RT5616_DRC_AGC_1:
	हाल RT5616_IRQ_CTRL2:
	हाल RT5616_INT_IRQ_ST:
	हाल RT5616_PGM_REG_ARR1:
	हाल RT5616_PGM_REG_ARR3:
	हाल RT5616_VENDOR_ID:
	हाल RT5616_DEVICE_ID:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt5616_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rt5616_ranges); i++) अणु
		अगर (reg >= rt5616_ranges[i].range_min &&
		    reg <= rt5616_ranges[i].range_max)
			वापस true;
	पूर्ण

	चयन (reg) अणु
	हाल RT5616_RESET:
	हाल RT5616_VERSION_ID:
	हाल RT5616_VENDOR_ID:
	हाल RT5616_DEVICE_ID:
	हाल RT5616_HP_VOL:
	हाल RT5616_LOUT_CTRL1:
	हाल RT5616_LOUT_CTRL2:
	हाल RT5616_IN1_IN2:
	हाल RT5616_INL1_INR1_VOL:
	हाल RT5616_DAC1_DIG_VOL:
	हाल RT5616_ADC_DIG_VOL:
	हाल RT5616_ADC_BST_VOL:
	हाल RT5616_STO1_ADC_MIXER:
	हाल RT5616_AD_DA_MIXER:
	हाल RT5616_STO_DAC_MIXER:
	हाल RT5616_REC_L1_MIXER:
	हाल RT5616_REC_L2_MIXER:
	हाल RT5616_REC_R1_MIXER:
	हाल RT5616_REC_R2_MIXER:
	हाल RT5616_HPO_MIXER:
	हाल RT5616_OUT_L1_MIXER:
	हाल RT5616_OUT_L2_MIXER:
	हाल RT5616_OUT_L3_MIXER:
	हाल RT5616_OUT_R1_MIXER:
	हाल RT5616_OUT_R2_MIXER:
	हाल RT5616_OUT_R3_MIXER:
	हाल RT5616_LOUT_MIXER:
	हाल RT5616_PWR_DIG1:
	हाल RT5616_PWR_DIG2:
	हाल RT5616_PWR_ANLG1:
	हाल RT5616_PWR_ANLG2:
	हाल RT5616_PWR_MIXER:
	हाल RT5616_PWR_VOL:
	हाल RT5616_PRIV_INDEX:
	हाल RT5616_PRIV_DATA:
	हाल RT5616_I2S1_SDP:
	हाल RT5616_ADDA_CLK1:
	हाल RT5616_ADDA_CLK2:
	हाल RT5616_GLB_CLK:
	हाल RT5616_PLL_CTRL1:
	हाल RT5616_PLL_CTRL2:
	हाल RT5616_HP_OVCD:
	हाल RT5616_DEPOP_M1:
	हाल RT5616_DEPOP_M2:
	हाल RT5616_DEPOP_M3:
	हाल RT5616_CHARGE_PUMP:
	हाल RT5616_PV_DET_SPK_G:
	हाल RT5616_MICBIAS:
	हाल RT5616_A_JD_CTL1:
	हाल RT5616_A_JD_CTL2:
	हाल RT5616_EQ_CTRL1:
	हाल RT5616_EQ_CTRL2:
	हाल RT5616_WIND_FILTER:
	हाल RT5616_DRC_AGC_1:
	हाल RT5616_DRC_AGC_2:
	हाल RT5616_DRC_AGC_3:
	हाल RT5616_SVOL_ZC:
	हाल RT5616_JD_CTRL1:
	हाल RT5616_JD_CTRL2:
	हाल RT5616_IRQ_CTRL1:
	हाल RT5616_IRQ_CTRL2:
	हाल RT5616_INT_IRQ_ST:
	हाल RT5616_GPIO_CTRL1:
	हाल RT5616_GPIO_CTRL2:
	हाल RT5616_GPIO_CTRL3:
	हाल RT5616_PGM_REG_ARR1:
	हाल RT5616_PGM_REG_ARR2:
	हाल RT5616_PGM_REG_ARR3:
	हाल RT5616_PGM_REG_ARR4:
	हाल RT5616_PGM_REG_ARR5:
	हाल RT5616_SCB_FUNC:
	हाल RT5616_SCB_CTRL:
	हाल RT5616_BASE_BACK:
	हाल RT5616_MP3_PLUS1:
	हाल RT5616_MP3_PLUS2:
	हाल RT5616_ADJ_HPF_CTRL1:
	हाल RT5616_ADJ_HPF_CTRL2:
	हाल RT5616_HP_CALIB_AMP_DET:
	हाल RT5616_HP_CALIB2:
	हाल RT5616_SV_ZCD1:
	हाल RT5616_SV_ZCD2:
	हाल RT5616_D_MISC:
	हाल RT5616_DUMMY2:
	हाल RT5616_DUMMY3:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(out_vol_tlv, -4650, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(dac_vol_tlv, -65625, 375, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(in_vol_tlv, -3450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_vol_tlv, -17625, 375, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_bst_tlv, 0, 1200, 0);

/* अणु0, +20, +24, +30, +35, +40, +44, +50, +52पूर्ण dB */
अटल स्थिर SNDRV_CTL_TLVD_DECLARE_DB_RANGE(bst_tlv,
	0, 0, TLV_DB_SCALE_ITEM(0, 0, 0),
	1, 1, TLV_DB_SCALE_ITEM(2000, 0, 0),
	2, 2, TLV_DB_SCALE_ITEM(2400, 0, 0),
	3, 5, TLV_DB_SCALE_ITEM(3000, 500, 0),
	6, 6, TLV_DB_SCALE_ITEM(4400, 0, 0),
	7, 7, TLV_DB_SCALE_ITEM(5000, 0, 0),
	8, 8, TLV_DB_SCALE_ITEM(5200, 0, 0),
);

अटल स्थिर काष्ठा snd_kcontrol_new rt5616_snd_controls[] = अणु
	/* Headphone Output Volume */
	SOC_DOUBLE("HP Playback Switch", RT5616_HP_VOL,
		   RT5616_L_MUTE_SFT, RT5616_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE("HPVOL Playback Switch", RT5616_HP_VOL,
		   RT5616_VOL_L_SFT, RT5616_VOL_R_SFT, 1, 1),
	SOC_DOUBLE_TLV("HP Playback Volume", RT5616_HP_VOL,
		       RT5616_L_VOL_SFT, RT5616_R_VOL_SFT, 39, 1, out_vol_tlv),
	/* OUTPUT Control */
	SOC_DOUBLE("OUT Playback Switch", RT5616_LOUT_CTRL1,
		   RT5616_L_MUTE_SFT, RT5616_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE("OUT Channel Switch", RT5616_LOUT_CTRL1,
		   RT5616_VOL_L_SFT, RT5616_VOL_R_SFT, 1, 1),
	SOC_DOUBLE_TLV("OUT Playback Volume", RT5616_LOUT_CTRL1,
		       RT5616_L_VOL_SFT, RT5616_R_VOL_SFT, 39, 1, out_vol_tlv),

	/* DAC Digital Volume */
	SOC_DOUBLE_TLV("DAC1 Playback Volume", RT5616_DAC1_DIG_VOL,
		       RT5616_L_VOL_SFT, RT5616_R_VOL_SFT,
		       175, 0, dac_vol_tlv),
	/* IN1/IN2 Control */
	SOC_SINGLE_TLV("IN1 Boost Volume", RT5616_IN1_IN2,
		       RT5616_BST_SFT1, 8, 0, bst_tlv),
	SOC_SINGLE_TLV("IN2 Boost Volume", RT5616_IN1_IN2,
		       RT5616_BST_SFT2, 8, 0, bst_tlv),
	/* INL/INR Volume Control */
	SOC_DOUBLE_TLV("IN Capture Volume", RT5616_INL1_INR1_VOL,
		       RT5616_INL_VOL_SFT, RT5616_INR_VOL_SFT,
		       31, 1, in_vol_tlv),
	/* ADC Digital Volume Control */
	SOC_DOUBLE("ADC Capture Switch", RT5616_ADC_DIG_VOL,
		   RT5616_L_MUTE_SFT, RT5616_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE_TLV("ADC Capture Volume", RT5616_ADC_DIG_VOL,
		       RT5616_L_VOL_SFT, RT5616_R_VOL_SFT,
		       127, 0, adc_vol_tlv),

	/* ADC Boost Volume Control */
	SOC_DOUBLE_TLV("ADC Boost Volume", RT5616_ADC_BST_VOL,
		       RT5616_ADC_L_BST_SFT, RT5616_ADC_R_BST_SFT,
		       3, 0, adc_bst_tlv),
पूर्ण;

अटल पूर्णांक is_sys_clk_from_pll(काष्ठा snd_soc_dapm_widget *source,
			       काष्ठा snd_soc_dapm_widget *sink)
अणु
	अचिन्हित पूर्णांक val;

	val = snd_soc_component_पढ़ो(snd_soc_dapm_to_component(source->dapm), RT5616_GLB_CLK);
	val &= RT5616_SCLK_SRC_MASK;
	अगर (val == RT5616_SCLK_SRC_PLL1)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/* Digital Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt5616_sto1_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5616_STO1_ADC_MIXER,
			RT5616_M_STO1_ADC_L1_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5616_sto1_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5616_STO1_ADC_MIXER,
			RT5616_M_STO1_ADC_R1_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5616_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("Stereo ADC Switch", RT5616_AD_DA_MIXER,
			RT5616_M_ADCMIX_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("INF1 Switch", RT5616_AD_DA_MIXER,
			RT5616_M_IF1_DAC_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5616_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("Stereo ADC Switch", RT5616_AD_DA_MIXER,
			RT5616_M_ADCMIX_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("INF1 Switch", RT5616_AD_DA_MIXER,
			RT5616_M_IF1_DAC_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5616_sto_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5616_STO_DAC_MIXER,
			RT5616_M_DAC_L1_MIXL_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5616_STO_DAC_MIXER,
			RT5616_M_DAC_R1_MIXL_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5616_sto_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5616_STO_DAC_MIXER,
			RT5616_M_DAC_R1_MIXR_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5616_STO_DAC_MIXER,
			RT5616_M_DAC_L1_MIXR_SFT, 1, 1),
पूर्ण;

/* Analog Input Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt5616_rec_l_mix[] = अणु
	SOC_DAPM_SINGLE("INL1 Switch", RT5616_REC_L2_MIXER,
			RT5616_M_IN1_L_RM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5616_REC_L2_MIXER,
			RT5616_M_BST2_RM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5616_REC_L2_MIXER,
			RT5616_M_BST1_RM_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5616_rec_r_mix[] = अणु
	SOC_DAPM_SINGLE("INR1 Switch", RT5616_REC_R2_MIXER,
			RT5616_M_IN1_R_RM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5616_REC_R2_MIXER,
			RT5616_M_BST2_RM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5616_REC_R2_MIXER,
			RT5616_M_BST1_RM_R_SFT, 1, 1),
पूर्ण;

/* Analog Output Mixer */

अटल स्थिर काष्ठा snd_kcontrol_new rt5616_out_l_mix[] = अणु
	SOC_DAPM_SINGLE("BST1 Switch", RT5616_OUT_L3_MIXER,
			RT5616_M_BST1_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5616_OUT_L3_MIXER,
			RT5616_M_BST2_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("INL1 Switch", RT5616_OUT_L3_MIXER,
			RT5616_M_IN1_L_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("REC MIXL Switch", RT5616_OUT_L3_MIXER,
			RT5616_M_RM_L_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5616_OUT_L3_MIXER,
			RT5616_M_DAC_L1_OM_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5616_out_r_mix[] = अणु
	SOC_DAPM_SINGLE("BST2 Switch", RT5616_OUT_R3_MIXER,
			RT5616_M_BST2_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5616_OUT_R3_MIXER,
			RT5616_M_BST1_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("INR1 Switch", RT5616_OUT_R3_MIXER,
			RT5616_M_IN1_R_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("REC MIXR Switch", RT5616_OUT_R3_MIXER,
			RT5616_M_RM_R_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5616_OUT_R3_MIXER,
			RT5616_M_DAC_R1_OM_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5616_hpo_mix[] = अणु
	SOC_DAPM_SINGLE("DAC1 Switch", RT5616_HPO_MIXER,
			RT5616_M_DAC1_HM_SFT, 1, 1),
	SOC_DAPM_SINGLE("HPVOL Switch", RT5616_HPO_MIXER,
			RT5616_M_HPVOL_HM_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5616_lout_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5616_LOUT_MIXER,
			RT5616_M_DAC_L1_LM_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5616_LOUT_MIXER,
			RT5616_M_DAC_R1_LM_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUTVOL L Switch", RT5616_LOUT_MIXER,
			RT5616_M_OV_L_LM_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUTVOL R Switch", RT5616_LOUT_MIXER,
			RT5616_M_OV_R_LM_SFT, 1, 1),
पूर्ण;

अटल पूर्णांक rt5616_adc_event(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, RT5616_ADC_DIG_VOL,
				    RT5616_L_MUTE | RT5616_R_MUTE, 0);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, RT5616_ADC_DIG_VOL,
				    RT5616_L_MUTE | RT5616_R_MUTE,
				    RT5616_L_MUTE | RT5616_R_MUTE);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5616_अक्षरge_pump_event(काष्ठा snd_soc_dapm_widget *w,
				    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* depop parameters */
		snd_soc_component_update_bits(component, RT5616_DEPOP_M2,
				    RT5616_DEPOP_MASK, RT5616_DEPOP_MAN);
		snd_soc_component_update_bits(component, RT5616_DEPOP_M1,
				    RT5616_HP_CP_MASK | RT5616_HP_SG_MASK |
				    RT5616_HP_CB_MASK, RT5616_HP_CP_PU |
				    RT5616_HP_SG_DIS | RT5616_HP_CB_PU);
		snd_soc_component_ग_लिखो(component, RT5616_PR_BASE +
			      RT5616_HP_DCC_INT1, 0x9f00);
		/* headphone amp घातer on */
		snd_soc_component_update_bits(component, RT5616_PWR_ANLG1,
				    RT5616_PWR_FV1 | RT5616_PWR_FV2, 0);
		snd_soc_component_update_bits(component, RT5616_PWR_VOL,
				    RT5616_PWR_HV_L | RT5616_PWR_HV_R,
				    RT5616_PWR_HV_L | RT5616_PWR_HV_R);
		snd_soc_component_update_bits(component, RT5616_PWR_ANLG1,
				    RT5616_PWR_HP_L | RT5616_PWR_HP_R |
				    RT5616_PWR_HA, RT5616_PWR_HP_L |
				    RT5616_PWR_HP_R | RT5616_PWR_HA);
		msleep(50);
		snd_soc_component_update_bits(component, RT5616_PWR_ANLG1,
				    RT5616_PWR_FV1 | RT5616_PWR_FV2,
				    RT5616_PWR_FV1 | RT5616_PWR_FV2);

		snd_soc_component_update_bits(component, RT5616_CHARGE_PUMP,
				    RT5616_PM_HP_MASK, RT5616_PM_HP_HV);
		snd_soc_component_update_bits(component, RT5616_PR_BASE +
				    RT5616_CHOP_DAC_ADC, 0x0200, 0x0200);
		snd_soc_component_update_bits(component, RT5616_DEPOP_M1,
				    RT5616_HP_CO_MASK | RT5616_HP_SG_MASK,
				    RT5616_HP_CO_EN | RT5616_HP_SG_EN);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT5616_PR_BASE +
				    RT5616_CHOP_DAC_ADC, 0x0200, 0x0);
		snd_soc_component_update_bits(component, RT5616_DEPOP_M1,
				    RT5616_HP_SG_MASK | RT5616_HP_L_SMT_MASK |
				    RT5616_HP_R_SMT_MASK, RT5616_HP_SG_DIS |
				    RT5616_HP_L_SMT_DIS | RT5616_HP_R_SMT_DIS);
		/* headphone amp घातer करोwn */
		snd_soc_component_update_bits(component, RT5616_DEPOP_M1,
				    RT5616_SMT_TRIG_MASK |
				    RT5616_HP_CD_PD_MASK | RT5616_HP_CO_MASK |
				    RT5616_HP_CP_MASK | RT5616_HP_SG_MASK |
				    RT5616_HP_CB_MASK,
				    RT5616_SMT_TRIG_DIS | RT5616_HP_CD_PD_EN |
				    RT5616_HP_CO_DIS | RT5616_HP_CP_PD |
				    RT5616_HP_SG_EN | RT5616_HP_CB_PD);
		snd_soc_component_update_bits(component, RT5616_PWR_ANLG1,
				    RT5616_PWR_HP_L | RT5616_PWR_HP_R |
				    RT5616_PWR_HA, 0);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5616_hp_event(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* headphone unmute sequence */
		snd_soc_component_update_bits(component, RT5616_DEPOP_M3,
				    RT5616_CP_FQ1_MASK | RT5616_CP_FQ2_MASK |
				    RT5616_CP_FQ3_MASK,
				    RT5616_CP_FQ_192_KHZ << RT5616_CP_FQ1_SFT |
				    RT5616_CP_FQ_12_KHZ << RT5616_CP_FQ2_SFT |
				    RT5616_CP_FQ_192_KHZ << RT5616_CP_FQ3_SFT);
		snd_soc_component_ग_लिखो(component, RT5616_PR_BASE +
			      RT5616_MAMP_INT_REG2, 0xfc00);
		snd_soc_component_update_bits(component, RT5616_DEPOP_M1,
				    RT5616_SMT_TRIG_MASK, RT5616_SMT_TRIG_EN);
		snd_soc_component_update_bits(component, RT5616_DEPOP_M1,
				    RT5616_RSTN_MASK, RT5616_RSTN_EN);
		snd_soc_component_update_bits(component, RT5616_DEPOP_M1,
				    RT5616_RSTN_MASK | RT5616_HP_L_SMT_MASK |
				    RT5616_HP_R_SMT_MASK, RT5616_RSTN_DIS |
				    RT5616_HP_L_SMT_EN | RT5616_HP_R_SMT_EN);
		snd_soc_component_update_bits(component, RT5616_HP_VOL,
				    RT5616_L_MUTE | RT5616_R_MUTE, 0);
		msleep(100);
		snd_soc_component_update_bits(component, RT5616_DEPOP_M1,
				    RT5616_HP_SG_MASK | RT5616_HP_L_SMT_MASK |
				    RT5616_HP_R_SMT_MASK, RT5616_HP_SG_DIS |
				    RT5616_HP_L_SMT_DIS | RT5616_HP_R_SMT_DIS);
		msleep(20);
		snd_soc_component_update_bits(component, RT5616_HP_CALIB_AMP_DET,
				    RT5616_HPD_PS_MASK, RT5616_HPD_PS_EN);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		/* headphone mute sequence */
		snd_soc_component_update_bits(component, RT5616_DEPOP_M3,
				    RT5616_CP_FQ1_MASK | RT5616_CP_FQ2_MASK |
				    RT5616_CP_FQ3_MASK,
				    RT5616_CP_FQ_96_KHZ << RT5616_CP_FQ1_SFT |
				    RT5616_CP_FQ_12_KHZ << RT5616_CP_FQ2_SFT |
				    RT5616_CP_FQ_96_KHZ << RT5616_CP_FQ3_SFT);
		snd_soc_component_ग_लिखो(component, RT5616_PR_BASE +
			      RT5616_MAMP_INT_REG2, 0xfc00);
		snd_soc_component_update_bits(component, RT5616_DEPOP_M1,
				    RT5616_HP_SG_MASK, RT5616_HP_SG_EN);
		snd_soc_component_update_bits(component, RT5616_DEPOP_M1,
				    RT5616_RSTP_MASK, RT5616_RSTP_EN);
		snd_soc_component_update_bits(component, RT5616_DEPOP_M1,
				    RT5616_RSTP_MASK | RT5616_HP_L_SMT_MASK |
				    RT5616_HP_R_SMT_MASK, RT5616_RSTP_DIS |
				    RT5616_HP_L_SMT_EN | RT5616_HP_R_SMT_EN);
		snd_soc_component_update_bits(component, RT5616_HP_CALIB_AMP_DET,
				    RT5616_HPD_PS_MASK, RT5616_HPD_PS_DIS);
		msleep(90);
		snd_soc_component_update_bits(component, RT5616_HP_VOL,
				    RT5616_L_MUTE | RT5616_R_MUTE,
				    RT5616_L_MUTE | RT5616_R_MUTE);
		msleep(30);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5616_lout_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, RT5616_PWR_ANLG1,
				    RT5616_PWR_LM, RT5616_PWR_LM);
		snd_soc_component_update_bits(component, RT5616_LOUT_CTRL1,
				    RT5616_L_MUTE | RT5616_R_MUTE, 0);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT5616_LOUT_CTRL1,
				    RT5616_L_MUTE | RT5616_R_MUTE,
				    RT5616_L_MUTE | RT5616_R_MUTE);
		snd_soc_component_update_bits(component, RT5616_PWR_ANLG1,
				    RT5616_PWR_LM, 0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5616_bst1_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, RT5616_PWR_ANLG2,
				    RT5616_PWR_BST1_OP2, RT5616_PWR_BST1_OP2);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT5616_PWR_ANLG2,
				    RT5616_PWR_BST1_OP2, 0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5616_bst2_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, RT5616_PWR_ANLG2,
				    RT5616_PWR_BST2_OP2, RT5616_PWR_BST2_OP2);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT5616_PWR_ANLG2,
				    RT5616_PWR_BST2_OP2, 0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget rt5616_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("PLL1", RT5616_PWR_ANLG2,
			    RT5616_PWR_PLL_BIT, 0, शून्य, 0),
	/* Input Side */
	/* micbias */
	SND_SOC_DAPM_SUPPLY("LDO", RT5616_PWR_ANLG1,
			    RT5616_PWR_LDO_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("micbias1", RT5616_PWR_ANLG2,
			    RT5616_PWR_MB1_BIT, 0, शून्य, 0),

	/* Input Lines */
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),

	SND_SOC_DAPM_INPUT("IN1P"),
	SND_SOC_DAPM_INPUT("IN2P"),
	SND_SOC_DAPM_INPUT("IN2N"),

	/* Boost */
	SND_SOC_DAPM_PGA_E("BST1", RT5616_PWR_ANLG2,
			   RT5616_PWR_BST1_BIT, 0, शून्य, 0, rt5616_bst1_event,
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_E("BST2", RT5616_PWR_ANLG2,
			   RT5616_PWR_BST2_BIT, 0, शून्य, 0, rt5616_bst2_event,
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	/* Input Volume */
	SND_SOC_DAPM_PGA("INL1 VOL", RT5616_PWR_VOL,
			 RT5616_PWR_IN1_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("INR1 VOL", RT5616_PWR_VOL,
			 RT5616_PWR_IN1_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("INL2 VOL", RT5616_PWR_VOL,
			 RT5616_PWR_IN2_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("INR2 VOL", RT5616_PWR_VOL,
			 RT5616_PWR_IN2_R_BIT, 0, शून्य, 0),

	/* REC Mixer */
	SND_SOC_DAPM_MIXER("RECMIXL", RT5616_PWR_MIXER, RT5616_PWR_RM_L_BIT, 0,
			   rt5616_rec_l_mix, ARRAY_SIZE(rt5616_rec_l_mix)),
	SND_SOC_DAPM_MIXER("RECMIXR", RT5616_PWR_MIXER, RT5616_PWR_RM_R_BIT, 0,
			   rt5616_rec_r_mix, ARRAY_SIZE(rt5616_rec_r_mix)),
	/* ADCs */
	SND_SOC_DAPM_ADC_E("ADC L", शून्य, RT5616_PWR_DIG1,
			   RT5616_PWR_ADC_L_BIT, 0, rt5616_adc_event,
			   SND_SOC_DAPM_POST_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_ADC_E("ADC R", शून्य, RT5616_PWR_DIG1,
			   RT5616_PWR_ADC_R_BIT, 0, rt5616_adc_event,
			   SND_SOC_DAPM_POST_PMD | SND_SOC_DAPM_POST_PMU),

	/* ADC Mixer */
	SND_SOC_DAPM_SUPPLY("stereo1 filter", RT5616_PWR_DIG2,
			    RT5616_PWR_ADC_STO1_F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Stereo1 ADC MIXL", SND_SOC_NOPM, 0, 0,
			   rt5616_sto1_adc_l_mix,
			   ARRAY_SIZE(rt5616_sto1_adc_l_mix)),
	SND_SOC_DAPM_MIXER("Stereo1 ADC MIXR", SND_SOC_NOPM, 0, 0,
			   rt5616_sto1_adc_r_mix,
			   ARRAY_SIZE(rt5616_sto1_adc_r_mix)),

	/* Digital Interface */
	SND_SOC_DAPM_SUPPLY("I2S1", RT5616_PWR_DIG1,
			    RT5616_PWR_I2S1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1 L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1 R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 ADC1", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* Digital Interface Select */

	/* Audio Interface */
	SND_SOC_DAPM_AIF_IN("AIF1RX", "AIF1 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX", "AIF1 Capture", 0, SND_SOC_NOPM, 0, 0),

	/* Audio DSP */
	SND_SOC_DAPM_PGA("Audio DSP", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* Output Side */
	/* DAC mixer beक्रमe sound effect  */
	SND_SOC_DAPM_MIXER("DAC MIXL", SND_SOC_NOPM, 0, 0,
			   rt5616_dac_l_mix, ARRAY_SIZE(rt5616_dac_l_mix)),
	SND_SOC_DAPM_MIXER("DAC MIXR", SND_SOC_NOPM, 0, 0,
			   rt5616_dac_r_mix, ARRAY_SIZE(rt5616_dac_r_mix)),

	SND_SOC_DAPM_SUPPLY("Stero1 DAC Power", RT5616_PWR_DIG2,
			    RT5616_PWR_DAC_STO1_F_BIT, 0, शून्य, 0),

	/* DAC Mixer */
	SND_SOC_DAPM_MIXER("Stereo DAC MIXL", SND_SOC_NOPM, 0, 0,
			   rt5616_sto_dac_l_mix,
			   ARRAY_SIZE(rt5616_sto_dac_l_mix)),
	SND_SOC_DAPM_MIXER("Stereo DAC MIXR", SND_SOC_NOPM, 0, 0,
			   rt5616_sto_dac_r_mix,
			   ARRAY_SIZE(rt5616_sto_dac_r_mix)),

	/* DACs */
	SND_SOC_DAPM_DAC("DAC L1", शून्य, RT5616_PWR_DIG1,
			 RT5616_PWR_DAC_L1_BIT, 0),
	SND_SOC_DAPM_DAC("DAC R1", शून्य, RT5616_PWR_DIG1,
			 RT5616_PWR_DAC_R1_BIT, 0),
	/* OUT Mixer */
	SND_SOC_DAPM_MIXER("OUT MIXL", RT5616_PWR_MIXER, RT5616_PWR_OM_L_BIT,
			   0, rt5616_out_l_mix, ARRAY_SIZE(rt5616_out_l_mix)),
	SND_SOC_DAPM_MIXER("OUT MIXR", RT5616_PWR_MIXER, RT5616_PWR_OM_R_BIT,
			   0, rt5616_out_r_mix, ARRAY_SIZE(rt5616_out_r_mix)),
	/* Output Volume */
	SND_SOC_DAPM_PGA("OUTVOL L", RT5616_PWR_VOL,
			 RT5616_PWR_OV_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("OUTVOL R", RT5616_PWR_VOL,
			 RT5616_PWR_OV_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("HPOVOL L", RT5616_PWR_VOL,
			 RT5616_PWR_HV_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("HPOVOL R", RT5616_PWR_VOL,
			 RT5616_PWR_HV_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DAC 1", SND_SOC_NOPM,
			 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DAC 2", SND_SOC_NOPM,
			 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("HPOVOL", SND_SOC_NOPM,
			 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("INL1", RT5616_PWR_VOL,
			 RT5616_PWR_IN1_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("INR1", RT5616_PWR_VOL,
			 RT5616_PWR_IN1_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("INL2", RT5616_PWR_VOL,
			 RT5616_PWR_IN2_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("INR2", RT5616_PWR_VOL,
			 RT5616_PWR_IN2_R_BIT, 0, शून्य, 0),
	/* HPO/LOUT/Mono Mixer */
	SND_SOC_DAPM_MIXER("HPO MIX", SND_SOC_NOPM, 0, 0,
			   rt5616_hpo_mix, ARRAY_SIZE(rt5616_hpo_mix)),
	SND_SOC_DAPM_MIXER("LOUT MIX", SND_SOC_NOPM, 0, 0,
			   rt5616_lout_mix, ARRAY_SIZE(rt5616_lout_mix)),

	SND_SOC_DAPM_PGA_S("HP amp", 1, SND_SOC_NOPM, 0, 0,
			   rt5616_hp_event, SND_SOC_DAPM_PRE_PMD |
			   SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_S("LOUT amp", 1, SND_SOC_NOPM, 0, 0,
			   rt5616_lout_event, SND_SOC_DAPM_PRE_PMD |
			   SND_SOC_DAPM_POST_PMU),

	SND_SOC_DAPM_SUPPLY_S("Charge Pump", 1, SND_SOC_NOPM, 0, 0,
			      rt5616_अक्षरge_pump_event, SND_SOC_DAPM_POST_PMU |
			      SND_SOC_DAPM_PRE_PMD),

	/* Output Lines */
	SND_SOC_DAPM_OUTPUT("HPOL"),
	SND_SOC_DAPM_OUTPUT("HPOR"),
	SND_SOC_DAPM_OUTPUT("LOUTL"),
	SND_SOC_DAPM_OUTPUT("LOUTR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5616_dapm_routes[] = अणु
	अणु"IN1P", शून्य, "LDO"पूर्ण,
	अणु"IN2P", शून्य, "LDO"पूर्ण,

	अणु"IN1P", शून्य, "MIC1"पूर्ण,
	अणु"IN2P", शून्य, "MIC2"पूर्ण,
	अणु"IN2N", शून्य, "MIC2"पूर्ण,

	अणु"BST1", शून्य, "IN1P"पूर्ण,
	अणु"BST2", शून्य, "IN2P"पूर्ण,
	अणु"BST2", शून्य, "IN2N"पूर्ण,
	अणु"BST1", शून्य, "micbias1"पूर्ण,
	अणु"BST2", शून्य, "micbias1"पूर्ण,

	अणु"INL1 VOL", शून्य, "IN2P"पूर्ण,
	अणु"INR1 VOL", शून्य, "IN2N"पूर्ण,

	अणु"RECMIXL", "INL1 Switch", "INL1 VOL"पूर्ण,
	अणु"RECMIXL", "BST2 Switch", "BST2"पूर्ण,
	अणु"RECMIXL", "BST1 Switch", "BST1"पूर्ण,

	अणु"RECMIXR", "INR1 Switch", "INR1 VOL"पूर्ण,
	अणु"RECMIXR", "BST2 Switch", "BST2"पूर्ण,
	अणु"RECMIXR", "BST1 Switch", "BST1"पूर्ण,

	अणु"ADC L", शून्य, "RECMIXL"पूर्ण,
	अणु"ADC R", शून्य, "RECMIXR"पूर्ण,

	अणु"Stereo1 ADC MIXL", "ADC1 Switch", "ADC L"पूर्ण,
	अणु"Stereo1 ADC MIXL", शून्य, "stereo1 filter"पूर्ण,
	अणु"stereo1 filter", शून्य, "PLL1", is_sys_clk_from_pllपूर्ण,

	अणु"Stereo1 ADC MIXR", "ADC1 Switch", "ADC R"पूर्ण,
	अणु"Stereo1 ADC MIXR", शून्य, "stereo1 filter"पूर्ण,
	अणु"stereo1 filter", शून्य, "PLL1", is_sys_clk_from_pllपूर्ण,

	अणु"IF1 ADC1", शून्य, "Stereo1 ADC MIXL"पूर्ण,
	अणु"IF1 ADC1", शून्य, "Stereo1 ADC MIXR"पूर्ण,
	अणु"IF1 ADC1", शून्य, "I2S1"पूर्ण,

	अणु"AIF1TX", शून्य, "IF1 ADC1"पूर्ण,

	अणु"IF1 DAC", शून्य, "AIF1RX"पूर्ण,
	अणु"IF1 DAC", शून्य, "I2S1"पूर्ण,

	अणु"IF1 DAC1 L", शून्य, "IF1 DAC"पूर्ण,
	अणु"IF1 DAC1 R", शून्य, "IF1 DAC"पूर्ण,

	अणु"DAC MIXL", "Stereo ADC Switch", "Stereo1 ADC MIXL"पूर्ण,
	अणु"DAC MIXL", "INF1 Switch", "IF1 DAC1 L"पूर्ण,
	अणु"DAC MIXR", "Stereo ADC Switch", "Stereo1 ADC MIXR"पूर्ण,
	अणु"DAC MIXR", "INF1 Switch", "IF1 DAC1 R"पूर्ण,

	अणु"Audio DSP", शून्य, "DAC MIXL"पूर्ण,
	अणु"Audio DSP", शून्य, "DAC MIXR"पूर्ण,

	अणु"Stereo DAC MIXL", "DAC L1 Switch", "Audio DSP"पूर्ण,
	अणु"Stereo DAC MIXL", "DAC R1 Switch", "DAC MIXR"पूर्ण,
	अणु"Stereo DAC MIXL", शून्य, "Stero1 DAC Power"पूर्ण,
	अणु"Stereo DAC MIXR", "DAC R1 Switch", "Audio DSP"पूर्ण,
	अणु"Stereo DAC MIXR", "DAC L1 Switch", "DAC MIXL"पूर्ण,
	अणु"Stereo DAC MIXR", शून्य, "Stero1 DAC Power"पूर्ण,

	अणु"DAC L1", शून्य, "Stereo DAC MIXL"पूर्ण,
	अणु"DAC L1", शून्य, "PLL1", is_sys_clk_from_pllपूर्ण,
	अणु"DAC R1", शून्य, "Stereo DAC MIXR"पूर्ण,
	अणु"DAC R1", शून्य, "PLL1", is_sys_clk_from_pllपूर्ण,

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

	अणु"HPOVOL L", शून्य, "OUT MIXL"पूर्ण,
	अणु"HPOVOL R", शून्य, "OUT MIXR"पूर्ण,
	अणु"OUTVOL L", शून्य, "OUT MIXL"पूर्ण,
	अणु"OUTVOL R", शून्य, "OUT MIXR"पूर्ण,

	अणु"DAC 1", शून्य, "DAC L1"पूर्ण,
	अणु"DAC 1", शून्य, "DAC R1"पूर्ण,
	अणु"HPOVOL", शून्य, "HPOVOL L"पूर्ण,
	अणु"HPOVOL", शून्य, "HPOVOL R"पूर्ण,
	अणु"HPO MIX", "DAC1 Switch", "DAC 1"पूर्ण,
	अणु"HPO MIX", "HPVOL Switch", "HPOVOL"पूर्ण,

	अणु"LOUT MIX", "DAC L1 Switch", "DAC L1"पूर्ण,
	अणु"LOUT MIX", "DAC R1 Switch", "DAC R1"पूर्ण,
	अणु"LOUT MIX", "OUTVOL L Switch", "OUTVOL L"पूर्ण,
	अणु"LOUT MIX", "OUTVOL R Switch", "OUTVOL R"पूर्ण,

	अणु"HP amp", शून्य, "HPO MIX"पूर्ण,
	अणु"HP amp", शून्य, "Charge Pump"पूर्ण,
	अणु"HPOL", शून्य, "HP amp"पूर्ण,
	अणु"HPOR", शून्य, "HP amp"पूर्ण,

	अणु"LOUT amp", शून्य, "LOUT MIX"पूर्ण,
	अणु"LOUT amp", शून्य, "Charge Pump"पूर्ण,
	अणु"LOUTL", शून्य, "LOUT amp"पूर्ण,
	अणु"LOUTR", शून्य, "LOUT amp"पूर्ण,

पूर्ण;

अटल पूर्णांक rt5616_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5616_priv *rt5616 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val_len = 0, val_clk, mask_clk;
	पूर्णांक pre_भाग, bclk_ms, frame_size;

	rt5616->lrck[dai->id] = params_rate(params);

	pre_भाग = rl6231_get_clk_info(rt5616->sysclk, rt5616->lrck[dai->id]);

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
	rt5616->bclk[dai->id] = rt5616->lrck[dai->id] * (32 << bclk_ms);

	dev_dbg(dai->dev, "bclk is %dHz and lrck is %dHz\n",
		rt5616->bclk[dai->id], rt5616->lrck[dai->id]);
	dev_dbg(dai->dev, "bclk_ms is %d and pre_div is %d for iis %d\n",
		bclk_ms, pre_भाग, dai->id);

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S20_3LE:
		val_len |= RT5616_I2S_DL_20;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		val_len |= RT5616_I2S_DL_24;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S8:
		val_len |= RT5616_I2S_DL_8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mask_clk = RT5616_I2S_PD1_MASK;
	val_clk = pre_भाग << RT5616_I2S_PD1_SFT;
	snd_soc_component_update_bits(component, RT5616_I2S1_SDP,
			    RT5616_I2S_DL_MASK, val_len);
	snd_soc_component_update_bits(component, RT5616_ADDA_CLK1, mask_clk, val_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5616_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5616_priv *rt5616 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		rt5616->master[dai->id] = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		reg_val |= RT5616_I2S_MS_S;
		rt5616->master[dai->id] = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		reg_val |= RT5616_I2S_BP_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT5616_I2S_DF_LEFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT5616_I2S_DF_PCM_A;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		reg_val |= RT5616_I2S_DF_PCM_B;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, RT5616_I2S1_SDP,
			    RT5616_I2S_MS_MASK | RT5616_I2S_BP_MASK |
			    RT5616_I2S_DF_MASK, reg_val);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5616_set_dai_sysclk(काष्ठा snd_soc_dai *dai,
				 पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5616_priv *rt5616 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;

	अगर (freq == rt5616->sysclk && clk_id == rt5616->sysclk_src)
		वापस 0;

	चयन (clk_id) अणु
	हाल RT5616_SCLK_S_MCLK:
		reg_val |= RT5616_SCLK_SRC_MCLK;
		अवरोध;
	हाल RT5616_SCLK_S_PLL1:
		reg_val |= RT5616_SCLK_SRC_PLL1;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, RT5616_GLB_CLK,
			    RT5616_SCLK_SRC_MASK, reg_val);
	rt5616->sysclk = freq;
	rt5616->sysclk_src = clk_id;

	dev_dbg(dai->dev, "Sysclk is %dHz and clock id is %d\n", freq, clk_id);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5616_set_dai_pll(काष्ठा snd_soc_dai *dai, पूर्णांक pll_id, पूर्णांक source,
			      अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5616_priv *rt5616 = snd_soc_component_get_drvdata(component);
	काष्ठा rl6231_pll_code pll_code;
	पूर्णांक ret;

	अगर (source == rt5616->pll_src && freq_in == rt5616->pll_in &&
	    freq_out == rt5616->pll_out)
		वापस 0;

	अगर (!freq_in || !freq_out) अणु
		dev_dbg(component->dev, "PLL disabled\n");

		rt5616->pll_in = 0;
		rt5616->pll_out = 0;
		snd_soc_component_update_bits(component, RT5616_GLB_CLK,
				    RT5616_SCLK_SRC_MASK,
				    RT5616_SCLK_SRC_MCLK);
		वापस 0;
	पूर्ण

	चयन (source) अणु
	हाल RT5616_PLL1_S_MCLK:
		snd_soc_component_update_bits(component, RT5616_GLB_CLK,
				    RT5616_PLL1_SRC_MASK,
				    RT5616_PLL1_SRC_MCLK);
		अवरोध;
	हाल RT5616_PLL1_S_BCLK1:
	हाल RT5616_PLL1_S_BCLK2:
		snd_soc_component_update_bits(component, RT5616_GLB_CLK,
				    RT5616_PLL1_SRC_MASK,
				    RT5616_PLL1_SRC_BCLK1);
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

	snd_soc_component_ग_लिखो(component, RT5616_PLL_CTRL1,
		      pll_code.n_code << RT5616_PLL_N_SFT | pll_code.k_code);
	snd_soc_component_ग_लिखो(component, RT5616_PLL_CTRL2,
		      (pll_code.m_bp ? 0 : pll_code.m_code) <<
		      RT5616_PLL_M_SFT |
		      pll_code.m_bp << RT5616_PLL_M_BP_SFT);

	rt5616->pll_in = freq_in;
	rt5616->pll_out = freq_out;
	rt5616->pll_src = source;

	वापस 0;
पूर्ण

अटल पूर्णांक rt5616_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा rt5616_priv *rt5616 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (level) अणु

	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		/*
		 * SND_SOC_BIAS_PREPARE is called जबतक preparing क्रम a
		 * transition to ON or away from ON. If current bias_level
		 * is SND_SOC_BIAS_ON, then it is preparing क्रम a transition
		 * away from ON. Disable the घड़ी in that हाल, otherwise
		 * enable it.
		 */
		अगर (IS_ERR(rt5616->mclk))
			अवरोध;

		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_ON) अणु
			clk_disable_unprepare(rt5616->mclk);
		पूर्ण अन्यथा अणु
			ret = clk_prepare_enable(rt5616->mclk);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			snd_soc_component_update_bits(component, RT5616_PWR_ANLG1,
					    RT5616_PWR_VREF1 | RT5616_PWR_MB |
					    RT5616_PWR_BG | RT5616_PWR_VREF2,
					    RT5616_PWR_VREF1 | RT5616_PWR_MB |
					    RT5616_PWR_BG | RT5616_PWR_VREF2);
			mdelay(10);
			snd_soc_component_update_bits(component, RT5616_PWR_ANLG1,
					    RT5616_PWR_FV1 | RT5616_PWR_FV2,
					    RT5616_PWR_FV1 | RT5616_PWR_FV2);
			snd_soc_component_update_bits(component, RT5616_D_MISC,
					    RT5616_D_GATE_EN,
					    RT5616_D_GATE_EN);
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, RT5616_D_MISC, RT5616_D_GATE_EN, 0);
		snd_soc_component_ग_लिखो(component, RT5616_PWR_DIG1, 0x0000);
		snd_soc_component_ग_लिखो(component, RT5616_PWR_DIG2, 0x0000);
		snd_soc_component_ग_लिखो(component, RT5616_PWR_VOL, 0x0000);
		snd_soc_component_ग_लिखो(component, RT5616_PWR_MIXER, 0x0000);
		snd_soc_component_ग_लिखो(component, RT5616_PWR_ANLG1, 0x0000);
		snd_soc_component_ग_लिखो(component, RT5616_PWR_ANLG2, 0x0000);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5616_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5616_priv *rt5616 = snd_soc_component_get_drvdata(component);

	/* Check अगर MCLK provided */
	rt5616->mclk = devm_clk_get(component->dev, "mclk");
	अगर (PTR_ERR(rt5616->mclk) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	rt5616->component = component;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rt5616_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5616_priv *rt5616 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt5616->regmap, true);
	regcache_mark_dirty(rt5616->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5616_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5616_priv *rt5616 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt5616->regmap, false);
	regcache_sync(rt5616->regmap);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा rt5616_suspend शून्य
#घोषणा rt5616_resume शून्य
#पूर्ण_अगर

#घोषणा RT5616_STEREO_RATES SNDRV_PCM_RATE_8000_192000
#घोषणा RT5616_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S8)

अटल स्थिर काष्ठा snd_soc_dai_ops rt5616_aअगर_dai_ops = अणु
	.hw_params = rt5616_hw_params,
	.set_fmt = rt5616_set_dai_fmt,
	.set_sysclk = rt5616_set_dai_sysclk,
	.set_pll = rt5616_set_dai_pll,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt5616_dai[] = अणु
	अणु
		.name = "rt5616-aif1",
		.id = RT5616_AIF1,
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5616_STEREO_RATES,
			.क्रमmats = RT5616_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5616_STEREO_RATES,
			.क्रमmats = RT5616_FORMATS,
		पूर्ण,
		.ops = &rt5616_aअगर_dai_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_rt5616 = अणु
	.probe			= rt5616_probe,
	.suspend		= rt5616_suspend,
	.resume			= rt5616_resume,
	.set_bias_level		= rt5616_set_bias_level,
	.controls		= rt5616_snd_controls,
	.num_controls		= ARRAY_SIZE(rt5616_snd_controls),
	.dapm_widमाला_लो		= rt5616_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(rt5616_dapm_widमाला_लो),
	.dapm_routes		= rt5616_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(rt5616_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt5616_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
	.max_रेजिस्टर = RT5616_DEVICE_ID + 1 + (ARRAY_SIZE(rt5616_ranges) *
					       RT5616_PR_SPACING),
	.अस्थिर_reg = rt5616_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = rt5616_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = rt5616_reg,
	.num_reg_शेषs = ARRAY_SIZE(rt5616_reg),
	.ranges = rt5616_ranges,
	.num_ranges = ARRAY_SIZE(rt5616_ranges),
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id rt5616_i2c_id[] = अणु
	अणु "rt5616", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt5616_i2c_id);

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id rt5616_of_match[] = अणु
	अणु .compatible = "realtek,rt5616", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt5616_of_match);
#पूर्ण_अगर

अटल पूर्णांक rt5616_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rt5616_priv *rt5616;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	rt5616 = devm_kzalloc(&i2c->dev, माप(काष्ठा rt5616_priv),
			      GFP_KERNEL);
	अगर (!rt5616)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, rt5616);

	rt5616->regmap = devm_regmap_init_i2c(i2c, &rt5616_regmap);
	अगर (IS_ERR(rt5616->regmap)) अणु
		ret = PTR_ERR(rt5616->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	regmap_पढ़ो(rt5616->regmap, RT5616_DEVICE_ID, &val);
	अगर (val != 0x6281) अणु
		dev_err(&i2c->dev,
			"Device with ID register %#x is not rt5616\n",
			val);
		वापस -ENODEV;
	पूर्ण
	regmap_ग_लिखो(rt5616->regmap, RT5616_RESET, 0);
	regmap_update_bits(rt5616->regmap, RT5616_PWR_ANLG1,
			   RT5616_PWR_VREF1 | RT5616_PWR_MB |
			   RT5616_PWR_BG | RT5616_PWR_VREF2,
			   RT5616_PWR_VREF1 | RT5616_PWR_MB |
			   RT5616_PWR_BG | RT5616_PWR_VREF2);
	mdelay(10);
	regmap_update_bits(rt5616->regmap, RT5616_PWR_ANLG1,
			   RT5616_PWR_FV1 | RT5616_PWR_FV2,
			   RT5616_PWR_FV1 | RT5616_PWR_FV2);

	ret = regmap_रेजिस्टर_patch(rt5616->regmap, init_list,
				    ARRAY_SIZE(init_list));
	अगर (ret != 0)
		dev_warn(&i2c->dev, "Failed to apply regmap patch: %d\n", ret);

	regmap_update_bits(rt5616->regmap, RT5616_PWR_ANLG1,
			   RT5616_PWR_LDO_DVO_MASK, RT5616_PWR_LDO_DVO_1_2V);

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				      &soc_component_dev_rt5616,
				      rt5616_dai, ARRAY_SIZE(rt5616_dai));
पूर्ण

अटल पूर्णांक rt5616_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	वापस 0;
पूर्ण

अटल व्योम rt5616_i2c_shutकरोwn(काष्ठा i2c_client *client)
अणु
	काष्ठा rt5616_priv *rt5616 = i2c_get_clientdata(client);

	regmap_ग_लिखो(rt5616->regmap, RT5616_HP_VOL, 0xc8c8);
	regmap_ग_लिखो(rt5616->regmap, RT5616_LOUT_CTRL1, 0xc8c8);
पूर्ण

अटल काष्ठा i2c_driver rt5616_i2c_driver = अणु
	.driver = अणु
		.name = "rt5616",
		.of_match_table = of_match_ptr(rt5616_of_match),
	पूर्ण,
	.probe = rt5616_i2c_probe,
	.हटाओ = rt5616_i2c_हटाओ,
	.shutकरोwn = rt5616_i2c_shutकरोwn,
	.id_table = rt5616_i2c_id,
पूर्ण;
module_i2c_driver(rt5616_i2c_driver);

MODULE_DESCRIPTION("ASoC RT5616 driver");
MODULE_AUTHOR("Bard Liao <bardliao@realtek.com>");
MODULE_LICENSE("GPL");
