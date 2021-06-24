<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rt5640.c  --  RT5640/RT5639 ALSA SoC audio codec driver
 *
 * Copyright 2011 Realtek Semiconductor Corp.
 * Author: Johnny Hsu <johnnyhsu@realtek.com>
 * Copyright (c) 2013, NVIDIA CORPORATION.  All rights reserved.
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
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "rl6231.h"
#समावेश "rt5640.h"

#घोषणा RT5640_DEVICE_ID 0x6231

#घोषणा RT5640_PR_RANGE_BASE (0xff + 1)
#घोषणा RT5640_PR_SPACING 0x100

#घोषणा RT5640_PR_BASE (RT5640_PR_RANGE_BASE + (0 * RT5640_PR_SPACING))

अटल स्थिर काष्ठा regmap_range_cfg rt5640_ranges[] = अणु
	अणु .name = "PR", .range_min = RT5640_PR_BASE,
	  .range_max = RT5640_PR_BASE + 0xb4,
	  .selector_reg = RT5640_PRIV_INDEX,
	  .selector_mask = 0xff,
	  .selector_shअगरt = 0x0,
	  .winकरोw_start = RT5640_PRIV_DATA,
	  .winकरोw_len = 0x1, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence init_list[] = अणु
	अणुRT5640_PR_BASE + 0x3d,	0x3600पूर्ण,
	अणुRT5640_PR_BASE + 0x12,	0x0aa8पूर्ण,
	अणुRT5640_PR_BASE + 0x14,	0x0aaaपूर्ण,
	अणुRT5640_PR_BASE + 0x20,	0x6110पूर्ण,
	अणुRT5640_PR_BASE + 0x21,	0xe0e0पूर्ण,
	अणुRT5640_PR_BASE + 0x23,	0x1804पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष rt5640_reg[] = अणु
	अणु 0x00, 0x000e पूर्ण,
	अणु 0x01, 0xc8c8 पूर्ण,
	अणु 0x02, 0xc8c8 पूर्ण,
	अणु 0x03, 0xc8c8 पूर्ण,
	अणु 0x04, 0x8000 पूर्ण,
	अणु 0x0d, 0x0000 पूर्ण,
	अणु 0x0e, 0x0000 पूर्ण,
	अणु 0x0f, 0x0808 पूर्ण,
	अणु 0x19, 0xafaf पूर्ण,
	अणु 0x1a, 0xafaf पूर्ण,
	अणु 0x1b, 0x0000 पूर्ण,
	अणु 0x1c, 0x2f2f पूर्ण,
	अणु 0x1d, 0x2f2f पूर्ण,
	अणु 0x1e, 0x0000 पूर्ण,
	अणु 0x27, 0x7060 पूर्ण,
	अणु 0x28, 0x7070 पूर्ण,
	अणु 0x29, 0x8080 पूर्ण,
	अणु 0x2a, 0x5454 पूर्ण,
	अणु 0x2b, 0x5454 पूर्ण,
	अणु 0x2c, 0xaa00 पूर्ण,
	अणु 0x2d, 0x0000 पूर्ण,
	अणु 0x2e, 0xa000 पूर्ण,
	अणु 0x2f, 0x0000 पूर्ण,
	अणु 0x3b, 0x0000 पूर्ण,
	अणु 0x3c, 0x007f पूर्ण,
	अणु 0x3d, 0x0000 पूर्ण,
	अणु 0x3e, 0x007f पूर्ण,
	अणु 0x45, 0xe000 पूर्ण,
	अणु 0x46, 0x003e पूर्ण,
	अणु 0x47, 0x003e पूर्ण,
	अणु 0x48, 0xf800 पूर्ण,
	अणु 0x49, 0x3800 पूर्ण,
	अणु 0x4a, 0x0004 पूर्ण,
	अणु 0x4c, 0xfc00 पूर्ण,
	अणु 0x4d, 0x0000 पूर्ण,
	अणु 0x4f, 0x01ff पूर्ण,
	अणु 0x50, 0x0000 पूर्ण,
	अणु 0x51, 0x0000 पूर्ण,
	अणु 0x52, 0x01ff पूर्ण,
	अणु 0x53, 0xf000 पूर्ण,
	अणु 0x61, 0x0000 पूर्ण,
	अणु 0x62, 0x0000 पूर्ण,
	अणु 0x63, 0x00c0 पूर्ण,
	अणु 0x64, 0x0000 पूर्ण,
	अणु 0x65, 0x0000 पूर्ण,
	अणु 0x66, 0x0000 पूर्ण,
	अणु 0x6a, 0x0000 पूर्ण,
	अणु 0x6c, 0x0000 पूर्ण,
	अणु 0x70, 0x8000 पूर्ण,
	अणु 0x71, 0x8000 पूर्ण,
	अणु 0x72, 0x8000 पूर्ण,
	अणु 0x73, 0x1114 पूर्ण,
	अणु 0x74, 0x0c00 पूर्ण,
	अणु 0x75, 0x1d00 पूर्ण,
	अणु 0x80, 0x0000 पूर्ण,
	अणु 0x81, 0x0000 पूर्ण,
	अणु 0x82, 0x0000 पूर्ण,
	अणु 0x83, 0x0000 पूर्ण,
	अणु 0x84, 0x0000 पूर्ण,
	अणु 0x85, 0x0008 पूर्ण,
	अणु 0x89, 0x0000 पूर्ण,
	अणु 0x8a, 0x0000 पूर्ण,
	अणु 0x8b, 0x0600 पूर्ण,
	अणु 0x8c, 0x0228 पूर्ण,
	अणु 0x8d, 0xa000 पूर्ण,
	अणु 0x8e, 0x0004 पूर्ण,
	अणु 0x8f, 0x1100 पूर्ण,
	अणु 0x90, 0x0646 पूर्ण,
	अणु 0x91, 0x0c00 पूर्ण,
	अणु 0x92, 0x0000 पूर्ण,
	अणु 0x93, 0x3000 पूर्ण,
	अणु 0xb0, 0x2080 पूर्ण,
	अणु 0xb1, 0x0000 पूर्ण,
	अणु 0xb4, 0x2206 पूर्ण,
	अणु 0xb5, 0x1f00 पूर्ण,
	अणु 0xb6, 0x0000 पूर्ण,
	अणु 0xb8, 0x034b पूर्ण,
	अणु 0xb9, 0x0066 पूर्ण,
	अणु 0xba, 0x000b पूर्ण,
	अणु 0xbb, 0x0000 पूर्ण,
	अणु 0xbc, 0x0000 पूर्ण,
	अणु 0xbd, 0x0000 पूर्ण,
	अणु 0xbe, 0x0000 पूर्ण,
	अणु 0xbf, 0x0000 पूर्ण,
	अणु 0xc0, 0x0400 पूर्ण,
	अणु 0xc2, 0x0000 पूर्ण,
	अणु 0xc4, 0x0000 पूर्ण,
	अणु 0xc5, 0x0000 पूर्ण,
	अणु 0xc6, 0x2000 पूर्ण,
	अणु 0xc8, 0x0000 पूर्ण,
	अणु 0xc9, 0x0000 पूर्ण,
	अणु 0xca, 0x0000 पूर्ण,
	अणु 0xcb, 0x0000 पूर्ण,
	अणु 0xcc, 0x0000 पूर्ण,
	अणु 0xcf, 0x0013 पूर्ण,
	अणु 0xd0, 0x0680 पूर्ण,
	अणु 0xd1, 0x1c17 पूर्ण,
	अणु 0xd2, 0x8c00 पूर्ण,
	अणु 0xd3, 0xaa20 पूर्ण,
	अणु 0xd6, 0x0400 पूर्ण,
	अणु 0xd9, 0x0809 पूर्ण,
	अणु 0xfe, 0x10ec पूर्ण,
	अणु 0xff, 0x6231 पूर्ण,
पूर्ण;

अटल पूर्णांक rt5640_reset(काष्ठा snd_soc_component *component)
अणु
	वापस snd_soc_component_ग_लिखो(component, RT5640_RESET, 0);
पूर्ण

अटल bool rt5640_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rt5640_ranges); i++)
		अगर ((reg >= rt5640_ranges[i].winकरोw_start &&
		     reg <= rt5640_ranges[i].winकरोw_start +
		     rt5640_ranges[i].winकरोw_len) ||
		    (reg >= rt5640_ranges[i].range_min &&
		     reg <= rt5640_ranges[i].range_max))
			वापस true;

	चयन (reg) अणु
	हाल RT5640_RESET:
	हाल RT5640_ASRC_5:
	हाल RT5640_EQ_CTRL1:
	हाल RT5640_DRC_AGC_1:
	हाल RT5640_ANC_CTRL1:
	हाल RT5640_IRQ_CTRL2:
	हाल RT5640_INT_IRQ_ST:
	हाल RT5640_DSP_CTRL2:
	हाल RT5640_DSP_CTRL3:
	हाल RT5640_PRIV_INDEX:
	हाल RT5640_PRIV_DATA:
	हाल RT5640_PGM_REG_ARR1:
	हाल RT5640_PGM_REG_ARR3:
	हाल RT5640_VENDOR_ID:
	हाल RT5640_VENDOR_ID1:
	हाल RT5640_VENDOR_ID2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt5640_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rt5640_ranges); i++)
		अगर ((reg >= rt5640_ranges[i].winकरोw_start &&
		     reg <= rt5640_ranges[i].winकरोw_start +
		     rt5640_ranges[i].winकरोw_len) ||
		    (reg >= rt5640_ranges[i].range_min &&
		     reg <= rt5640_ranges[i].range_max))
			वापस true;

	चयन (reg) अणु
	हाल RT5640_RESET:
	हाल RT5640_SPK_VOL:
	हाल RT5640_HP_VOL:
	हाल RT5640_OUTPUT:
	हाल RT5640_MONO_OUT:
	हाल RT5640_IN1_IN2:
	हाल RT5640_IN3_IN4:
	हाल RT5640_INL_INR_VOL:
	हाल RT5640_DAC1_DIG_VOL:
	हाल RT5640_DAC2_DIG_VOL:
	हाल RT5640_DAC2_CTRL:
	हाल RT5640_ADC_DIG_VOL:
	हाल RT5640_ADC_DATA:
	हाल RT5640_ADC_BST_VOL:
	हाल RT5640_STO_ADC_MIXER:
	हाल RT5640_MONO_ADC_MIXER:
	हाल RT5640_AD_DA_MIXER:
	हाल RT5640_STO_DAC_MIXER:
	हाल RT5640_MONO_DAC_MIXER:
	हाल RT5640_DIG_MIXER:
	हाल RT5640_DSP_PATH1:
	हाल RT5640_DSP_PATH2:
	हाल RT5640_DIG_INF_DATA:
	हाल RT5640_REC_L1_MIXER:
	हाल RT5640_REC_L2_MIXER:
	हाल RT5640_REC_R1_MIXER:
	हाल RT5640_REC_R2_MIXER:
	हाल RT5640_HPO_MIXER:
	हाल RT5640_SPK_L_MIXER:
	हाल RT5640_SPK_R_MIXER:
	हाल RT5640_SPO_L_MIXER:
	हाल RT5640_SPO_R_MIXER:
	हाल RT5640_SPO_CLSD_RATIO:
	हाल RT5640_MONO_MIXER:
	हाल RT5640_OUT_L1_MIXER:
	हाल RT5640_OUT_L2_MIXER:
	हाल RT5640_OUT_L3_MIXER:
	हाल RT5640_OUT_R1_MIXER:
	हाल RT5640_OUT_R2_MIXER:
	हाल RT5640_OUT_R3_MIXER:
	हाल RT5640_LOUT_MIXER:
	हाल RT5640_PWR_DIG1:
	हाल RT5640_PWR_DIG2:
	हाल RT5640_PWR_ANLG1:
	हाल RT5640_PWR_ANLG2:
	हाल RT5640_PWR_MIXER:
	हाल RT5640_PWR_VOL:
	हाल RT5640_PRIV_INDEX:
	हाल RT5640_PRIV_DATA:
	हाल RT5640_I2S1_SDP:
	हाल RT5640_I2S2_SDP:
	हाल RT5640_ADDA_CLK1:
	हाल RT5640_ADDA_CLK2:
	हाल RT5640_DMIC:
	हाल RT5640_GLB_CLK:
	हाल RT5640_PLL_CTRL1:
	हाल RT5640_PLL_CTRL2:
	हाल RT5640_ASRC_1:
	हाल RT5640_ASRC_2:
	हाल RT5640_ASRC_3:
	हाल RT5640_ASRC_4:
	हाल RT5640_ASRC_5:
	हाल RT5640_HP_OVCD:
	हाल RT5640_CLS_D_OVCD:
	हाल RT5640_CLS_D_OUT:
	हाल RT5640_DEPOP_M1:
	हाल RT5640_DEPOP_M2:
	हाल RT5640_DEPOP_M3:
	हाल RT5640_CHARGE_PUMP:
	हाल RT5640_PV_DET_SPK_G:
	हाल RT5640_MICBIAS:
	हाल RT5640_EQ_CTRL1:
	हाल RT5640_EQ_CTRL2:
	हाल RT5640_WIND_FILTER:
	हाल RT5640_DRC_AGC_1:
	हाल RT5640_DRC_AGC_2:
	हाल RT5640_DRC_AGC_3:
	हाल RT5640_SVOL_ZC:
	हाल RT5640_ANC_CTRL1:
	हाल RT5640_ANC_CTRL2:
	हाल RT5640_ANC_CTRL3:
	हाल RT5640_JD_CTRL:
	हाल RT5640_ANC_JD:
	हाल RT5640_IRQ_CTRL1:
	हाल RT5640_IRQ_CTRL2:
	हाल RT5640_INT_IRQ_ST:
	हाल RT5640_GPIO_CTRL1:
	हाल RT5640_GPIO_CTRL2:
	हाल RT5640_GPIO_CTRL3:
	हाल RT5640_DSP_CTRL1:
	हाल RT5640_DSP_CTRL2:
	हाल RT5640_DSP_CTRL3:
	हाल RT5640_DSP_CTRL4:
	हाल RT5640_PGM_REG_ARR1:
	हाल RT5640_PGM_REG_ARR2:
	हाल RT5640_PGM_REG_ARR3:
	हाल RT5640_PGM_REG_ARR4:
	हाल RT5640_PGM_REG_ARR5:
	हाल RT5640_SCB_FUNC:
	हाल RT5640_SCB_CTRL:
	हाल RT5640_BASE_BACK:
	हाल RT5640_MP3_PLUS1:
	हाल RT5640_MP3_PLUS2:
	हाल RT5640_3D_HP:
	हाल RT5640_ADJ_HPF:
	हाल RT5640_HP_CALIB_AMP_DET:
	हाल RT5640_HP_CALIB2:
	हाल RT5640_SV_ZCD1:
	हाल RT5640_SV_ZCD2:
	हाल RT5640_DUMMY1:
	हाल RT5640_DUMMY2:
	हाल RT5640_DUMMY3:
	हाल RT5640_VENDOR_ID:
	हाल RT5640_VENDOR_ID1:
	हाल RT5640_VENDOR_ID2:
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
अटल स्थिर अक्षर * स्थिर rt5640_data_select[] = अणु
	"Normal", "Swap", "left copy to right", "right copy to left"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5640_अगर1_dac_क्रमागत, RT5640_DIG_INF_DATA,
			    RT5640_IF1_DAC_SEL_SFT, rt5640_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5640_अगर1_adc_क्रमागत, RT5640_DIG_INF_DATA,
			    RT5640_IF1_ADC_SEL_SFT, rt5640_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5640_अगर2_dac_क्रमागत, RT5640_DIG_INF_DATA,
			    RT5640_IF2_DAC_SEL_SFT, rt5640_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5640_अगर2_adc_क्रमागत, RT5640_DIG_INF_DATA,
			    RT5640_IF2_ADC_SEL_SFT, rt5640_data_select);

/* Class D speaker gain ratio */
अटल स्थिर अक्षर * स्थिर rt5640_clsd_spk_ratio[] = अणु"1.66x", "1.83x", "1.94x",
	"2x", "2.11x", "2.22x", "2.33x", "2.44x", "2.55x", "2.66x", "2.77x"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5640_clsd_spk_ratio_क्रमागत, RT5640_CLS_D_OUT,
			    RT5640_CLSD_RATIO_SFT, rt5640_clsd_spk_ratio);

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_snd_controls[] = अणु
	/* Speaker Output Volume */
	SOC_DOUBLE("Speaker Channel Switch", RT5640_SPK_VOL,
		RT5640_VOL_L_SFT, RT5640_VOL_R_SFT, 1, 1),
	SOC_DOUBLE_TLV("Speaker Playback Volume", RT5640_SPK_VOL,
		RT5640_L_VOL_SFT, RT5640_R_VOL_SFT, 39, 1, out_vol_tlv),
	/* Headphone Output Volume */
	SOC_DOUBLE("HP Channel Switch", RT5640_HP_VOL,
		RT5640_VOL_L_SFT, RT5640_VOL_R_SFT, 1, 1),
	SOC_DOUBLE_TLV("HP Playback Volume", RT5640_HP_VOL,
		RT5640_L_VOL_SFT, RT5640_R_VOL_SFT, 39, 1, out_vol_tlv),
	/* OUTPUT Control */
	SOC_DOUBLE("OUT Playback Switch", RT5640_OUTPUT,
		RT5640_L_MUTE_SFT, RT5640_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE("OUT Channel Switch", RT5640_OUTPUT,
		RT5640_VOL_L_SFT, RT5640_VOL_R_SFT, 1, 1),
	SOC_DOUBLE_TLV("OUT Playback Volume", RT5640_OUTPUT,
		RT5640_L_VOL_SFT, RT5640_R_VOL_SFT, 39, 1, out_vol_tlv),

	/* DAC Digital Volume */
	SOC_DOUBLE("DAC2 Playback Switch", RT5640_DAC2_CTRL,
		RT5640_M_DAC_L2_VOL_SFT, RT5640_M_DAC_R2_VOL_SFT, 1, 1),
	SOC_DOUBLE_TLV("DAC2 Playback Volume", RT5640_DAC2_DIG_VOL,
			RT5640_L_VOL_SFT, RT5640_R_VOL_SFT,
			175, 0, dac_vol_tlv),
	SOC_DOUBLE_TLV("DAC1 Playback Volume", RT5640_DAC1_DIG_VOL,
			RT5640_L_VOL_SFT, RT5640_R_VOL_SFT,
			175, 0, dac_vol_tlv),
	/* IN1/IN2/IN3 Control */
	SOC_SINGLE_TLV("IN1 Boost", RT5640_IN1_IN2,
		RT5640_BST_SFT1, 8, 0, bst_tlv),
	SOC_SINGLE_TLV("IN2 Boost", RT5640_IN3_IN4,
		RT5640_BST_SFT2, 8, 0, bst_tlv),
	SOC_SINGLE_TLV("IN3 Boost", RT5640_IN1_IN2,
		RT5640_BST_SFT2, 8, 0, bst_tlv),

	/* INL/INR Volume Control */
	SOC_DOUBLE_TLV("IN Capture Volume", RT5640_INL_INR_VOL,
			RT5640_INL_VOL_SFT, RT5640_INR_VOL_SFT,
			31, 1, in_vol_tlv),
	/* ADC Digital Volume Control */
	SOC_DOUBLE("ADC Capture Switch", RT5640_ADC_DIG_VOL,
		RT5640_L_MUTE_SFT, RT5640_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE_TLV("ADC Capture Volume", RT5640_ADC_DIG_VOL,
			RT5640_L_VOL_SFT, RT5640_R_VOL_SFT,
			127, 0, adc_vol_tlv),
	SOC_DOUBLE("Mono ADC Capture Switch", RT5640_DUMMY1,
		RT5640_M_MONO_ADC_L_SFT, RT5640_M_MONO_ADC_R_SFT, 1, 1),
	SOC_DOUBLE_TLV("Mono ADC Capture Volume", RT5640_ADC_DATA,
			RT5640_L_VOL_SFT, RT5640_R_VOL_SFT,
			127, 0, adc_vol_tlv),
	/* ADC Boost Volume Control */
	SOC_DOUBLE_TLV("ADC Boost Gain", RT5640_ADC_BST_VOL,
			RT5640_ADC_L_BST_SFT, RT5640_ADC_R_BST_SFT,
			3, 0, adc_bst_tlv),
	/* Class D speaker gain ratio */
	SOC_ENUM("Class D SPK Ratio Control", rt5640_clsd_spk_ratio_क्रमागत),

	SOC_ENUM("ADC IF1 Data Switch", rt5640_अगर1_adc_क्रमागत),
	SOC_ENUM("DAC IF1 Data Switch", rt5640_अगर1_dac_क्रमागत),
	SOC_ENUM("ADC IF2 Data Switch", rt5640_अगर2_adc_क्रमागत),
	SOC_ENUM("DAC IF2 Data Switch", rt5640_अगर2_dac_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_specअगरic_snd_controls[] = अणु
	/* MONO Output Control */
	SOC_SINGLE("Mono Playback Switch", RT5640_MONO_OUT, RT5640_L_MUTE_SFT,
		1, 1),
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
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);
	पूर्णांक idx, rate;

	rate = rt5640->sysclk / rl6231_get_pre_भाग(rt5640->regmap,
		RT5640_ADDA_CLK1, RT5640_I2S_PD1_SFT);
	idx = rl6231_calc_dmic_clk(rate);
	अगर (idx < 0)
		dev_err(component->dev, "Failed to set DMIC clock\n");
	अन्यथा
		snd_soc_component_update_bits(component, RT5640_DMIC, RT5640_DMIC_CLK_MASK,
					idx << RT5640_DMIC_CLK_SFT);
	वापस idx;
पूर्ण

अटल पूर्णांक is_using_asrc(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);

	अगर (!rt5640->asrc_en)
		वापस 0;

	वापस 1;
पूर्ण

/* Digital Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt5640_sto_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5640_STO_ADC_MIXER,
			RT5640_M_ADC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5640_STO_ADC_MIXER,
			RT5640_M_ADC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_sto_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5640_STO_ADC_MIXER,
			RT5640_M_ADC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5640_STO_ADC_MIXER,
			RT5640_M_ADC_R2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_mono_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5640_MONO_ADC_MIXER,
			RT5640_M_MONO_ADC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5640_MONO_ADC_MIXER,
			RT5640_M_MONO_ADC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_mono_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5640_MONO_ADC_MIXER,
			RT5640_M_MONO_ADC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5640_MONO_ADC_MIXER,
			RT5640_M_MONO_ADC_R2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("Stereo ADC Switch", RT5640_AD_DA_MIXER,
			RT5640_M_ADCMIX_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("INF1 Switch", RT5640_AD_DA_MIXER,
			RT5640_M_IF1_DAC_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("Stereo ADC Switch", RT5640_AD_DA_MIXER,
			RT5640_M_ADCMIX_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("INF1 Switch", RT5640_AD_DA_MIXER,
			RT5640_M_IF1_DAC_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_sto_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5640_STO_DAC_MIXER,
			RT5640_M_DAC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5640_STO_DAC_MIXER,
			RT5640_M_DAC_L2_SFT, 1, 1),
	SOC_DAPM_SINGLE("ANC Switch", RT5640_STO_DAC_MIXER,
			RT5640_M_ANC_DAC_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_sto_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5640_STO_DAC_MIXER,
			RT5640_M_DAC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5640_STO_DAC_MIXER,
			RT5640_M_DAC_R2_SFT, 1, 1),
	SOC_DAPM_SINGLE("ANC Switch", RT5640_STO_DAC_MIXER,
			RT5640_M_ANC_DAC_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5639_sto_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5640_STO_DAC_MIXER,
			RT5640_M_DAC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5640_STO_DAC_MIXER,
			RT5640_M_DAC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5639_sto_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5640_STO_DAC_MIXER,
			RT5640_M_DAC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5640_STO_DAC_MIXER,
			RT5640_M_DAC_R2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_mono_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5640_MONO_DAC_MIXER,
			RT5640_M_DAC_L1_MONO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5640_MONO_DAC_MIXER,
			RT5640_M_DAC_L2_MONO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5640_MONO_DAC_MIXER,
			RT5640_M_DAC_R2_MONO_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_mono_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5640_MONO_DAC_MIXER,
			RT5640_M_DAC_R1_MONO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5640_MONO_DAC_MIXER,
			RT5640_M_DAC_R2_MONO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5640_MONO_DAC_MIXER,
			RT5640_M_DAC_L2_MONO_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_dig_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5640_DIG_MIXER,
			RT5640_M_STO_L_DAC_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5640_DIG_MIXER,
			RT5640_M_DAC_L2_DAC_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_dig_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5640_DIG_MIXER,
			RT5640_M_STO_R_DAC_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5640_DIG_MIXER,
			RT5640_M_DAC_R2_DAC_R_SFT, 1, 1),
पूर्ण;

/* Analog Input Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt5640_rec_l_mix[] = अणु
	SOC_DAPM_SINGLE("HPOL Switch", RT5640_REC_L2_MIXER,
			RT5640_M_HP_L_RM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("INL Switch", RT5640_REC_L2_MIXER,
			RT5640_M_IN_L_RM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST3 Switch", RT5640_REC_L2_MIXER,
			RT5640_M_BST2_RM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5640_REC_L2_MIXER,
			RT5640_M_BST4_RM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5640_REC_L2_MIXER,
			RT5640_M_BST1_RM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUT MIXL Switch", RT5640_REC_L2_MIXER,
			RT5640_M_OM_L_RM_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_rec_r_mix[] = अणु
	SOC_DAPM_SINGLE("HPOR Switch", RT5640_REC_R2_MIXER,
			RT5640_M_HP_R_RM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("INR Switch", RT5640_REC_R2_MIXER,
			RT5640_M_IN_R_RM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST3 Switch", RT5640_REC_R2_MIXER,
			RT5640_M_BST2_RM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5640_REC_R2_MIXER,
			RT5640_M_BST4_RM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5640_REC_R2_MIXER,
			RT5640_M_BST1_RM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUT MIXR Switch", RT5640_REC_R2_MIXER,
			RT5640_M_OM_R_RM_R_SFT, 1, 1),
पूर्ण;

/* Analog Output Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt5640_spk_l_mix[] = अणु
	SOC_DAPM_SINGLE("REC MIXL Switch", RT5640_SPK_L_MIXER,
			RT5640_M_RM_L_SM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("INL Switch", RT5640_SPK_L_MIXER,
			RT5640_M_IN_L_SM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5640_SPK_L_MIXER,
			RT5640_M_DAC_L1_SM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5640_SPK_L_MIXER,
			RT5640_M_DAC_L2_SM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUT MIXL Switch", RT5640_SPK_L_MIXER,
			RT5640_M_OM_L_SM_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_spk_r_mix[] = अणु
	SOC_DAPM_SINGLE("REC MIXR Switch", RT5640_SPK_R_MIXER,
			RT5640_M_RM_R_SM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("INR Switch", RT5640_SPK_R_MIXER,
			RT5640_M_IN_R_SM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5640_SPK_R_MIXER,
			RT5640_M_DAC_R1_SM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5640_SPK_R_MIXER,
			RT5640_M_DAC_R2_SM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUT MIXR Switch", RT5640_SPK_R_MIXER,
			RT5640_M_OM_R_SM_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_out_l_mix[] = अणु
	SOC_DAPM_SINGLE("SPK MIXL Switch", RT5640_OUT_L3_MIXER,
			RT5640_M_SM_L_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5640_OUT_L3_MIXER,
			RT5640_M_BST1_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("INL Switch", RT5640_OUT_L3_MIXER,
			RT5640_M_IN_L_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("REC MIXL Switch", RT5640_OUT_L3_MIXER,
			RT5640_M_RM_L_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5640_OUT_L3_MIXER,
			RT5640_M_DAC_R2_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5640_OUT_L3_MIXER,
			RT5640_M_DAC_L2_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5640_OUT_L3_MIXER,
			RT5640_M_DAC_L1_OM_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_out_r_mix[] = अणु
	SOC_DAPM_SINGLE("SPK MIXR Switch", RT5640_OUT_R3_MIXER,
			RT5640_M_SM_L_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5640_OUT_R3_MIXER,
			RT5640_M_BST4_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5640_OUT_R3_MIXER,
			RT5640_M_BST1_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("INR Switch", RT5640_OUT_R3_MIXER,
			RT5640_M_IN_R_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("REC MIXR Switch", RT5640_OUT_R3_MIXER,
			RT5640_M_RM_R_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5640_OUT_R3_MIXER,
			RT5640_M_DAC_L2_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5640_OUT_R3_MIXER,
			RT5640_M_DAC_R2_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5640_OUT_R3_MIXER,
			RT5640_M_DAC_R1_OM_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5639_out_l_mix[] = अणु
	SOC_DAPM_SINGLE("BST1 Switch", RT5640_OUT_L3_MIXER,
			RT5640_M_BST1_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("INL Switch", RT5640_OUT_L3_MIXER,
			RT5640_M_IN_L_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("REC MIXL Switch", RT5640_OUT_L3_MIXER,
			RT5640_M_RM_L_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5640_OUT_L3_MIXER,
			RT5640_M_DAC_L1_OM_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5639_out_r_mix[] = अणु
	SOC_DAPM_SINGLE("BST2 Switch", RT5640_OUT_R3_MIXER,
			RT5640_M_BST4_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5640_OUT_R3_MIXER,
			RT5640_M_BST1_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("INR Switch", RT5640_OUT_R3_MIXER,
			RT5640_M_IN_R_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("REC MIXR Switch", RT5640_OUT_R3_MIXER,
			RT5640_M_RM_R_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5640_OUT_R3_MIXER,
			RT5640_M_DAC_R1_OM_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_spo_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5640_SPO_L_MIXER,
			RT5640_M_DAC_R1_SPM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5640_SPO_L_MIXER,
			RT5640_M_DAC_L1_SPM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("SPKVOL R Switch", RT5640_SPO_L_MIXER,
			RT5640_M_SV_R_SPM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("SPKVOL L Switch", RT5640_SPO_L_MIXER,
			RT5640_M_SV_L_SPM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5640_SPO_L_MIXER,
			RT5640_M_BST1_SPM_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_spo_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5640_SPO_R_MIXER,
			RT5640_M_DAC_R1_SPM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("SPKVOL R Switch", RT5640_SPO_R_MIXER,
			RT5640_M_SV_R_SPM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5640_SPO_R_MIXER,
			RT5640_M_BST1_SPM_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_hpo_mix[] = अणु
	SOC_DAPM_SINGLE("HPO MIX DAC2 Switch", RT5640_HPO_MIXER,
			RT5640_M_DAC2_HM_SFT, 1, 1),
	SOC_DAPM_SINGLE("HPO MIX DAC1 Switch", RT5640_HPO_MIXER,
			RT5640_M_DAC1_HM_SFT, 1, 1),
	SOC_DAPM_SINGLE("HPO MIX HPVOL Switch", RT5640_HPO_MIXER,
			RT5640_M_HPVOL_HM_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5639_hpo_mix[] = अणु
	SOC_DAPM_SINGLE("HPO MIX DAC1 Switch", RT5640_HPO_MIXER,
			RT5640_M_DAC1_HM_SFT, 1, 1),
	SOC_DAPM_SINGLE("HPO MIX HPVOL Switch", RT5640_HPO_MIXER,
			RT5640_M_HPVOL_HM_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_lout_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5640_LOUT_MIXER,
			RT5640_M_DAC_L1_LM_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5640_LOUT_MIXER,
			RT5640_M_DAC_R1_LM_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUTVOL L Switch", RT5640_LOUT_MIXER,
			RT5640_M_OV_L_LM_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUTVOL R Switch", RT5640_LOUT_MIXER,
			RT5640_M_OV_R_LM_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_mono_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5640_MONO_MIXER,
			RT5640_M_DAC_R2_MM_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5640_MONO_MIXER,
			RT5640_M_DAC_L2_MM_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUTVOL R Switch", RT5640_MONO_MIXER,
			RT5640_M_OV_R_MM_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUTVOL L Switch", RT5640_MONO_MIXER,
			RT5640_M_OV_L_MM_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5640_MONO_MIXER,
			RT5640_M_BST1_MM_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new spk_l_enable_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT5640_SPK_VOL,
		RT5640_L_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new spk_r_enable_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT5640_SPK_VOL,
		RT5640_R_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new hp_l_enable_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT5640_HP_VOL,
		RT5640_L_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new hp_r_enable_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT5640_HP_VOL,
		RT5640_R_MUTE_SFT, 1, 1);

/* Stereo ADC source */
अटल स्थिर अक्षर * स्थिर rt5640_stereo_adc1_src[] = अणु
	"DIG MIX", "ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5640_stereo_adc1_क्रमागत, RT5640_STO_ADC_MIXER,
			    RT5640_ADC_1_SRC_SFT, rt5640_stereo_adc1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_sto_adc_1_mux =
	SOC_DAPM_ENUM("Stereo ADC1 Mux", rt5640_stereo_adc1_क्रमागत);

अटल स्थिर अक्षर * स्थिर rt5640_stereo_adc2_src[] = अणु
	"DMIC1", "DMIC2", "DIG MIX"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5640_stereo_adc2_क्रमागत, RT5640_STO_ADC_MIXER,
			    RT5640_ADC_2_SRC_SFT, rt5640_stereo_adc2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_sto_adc_2_mux =
	SOC_DAPM_ENUM("Stereo ADC2 Mux", rt5640_stereo_adc2_क्रमागत);

/* Mono ADC source */
अटल स्थिर अक्षर * स्थिर rt5640_mono_adc_l1_src[] = अणु
	"Mono DAC MIXL", "ADCL"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5640_mono_adc_l1_क्रमागत, RT5640_MONO_ADC_MIXER,
			    RT5640_MONO_ADC_L1_SRC_SFT, rt5640_mono_adc_l1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_mono_adc_l1_mux =
	SOC_DAPM_ENUM("Mono ADC1 left source", rt5640_mono_adc_l1_क्रमागत);

अटल स्थिर अक्षर * स्थिर rt5640_mono_adc_l2_src[] = अणु
	"DMIC L1", "DMIC L2", "Mono DAC MIXL"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5640_mono_adc_l2_क्रमागत, RT5640_MONO_ADC_MIXER,
			    RT5640_MONO_ADC_L2_SRC_SFT, rt5640_mono_adc_l2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_mono_adc_l2_mux =
	SOC_DAPM_ENUM("Mono ADC2 left source", rt5640_mono_adc_l2_क्रमागत);

अटल स्थिर अक्षर * स्थिर rt5640_mono_adc_r1_src[] = अणु
	"Mono DAC MIXR", "ADCR"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5640_mono_adc_r1_क्रमागत, RT5640_MONO_ADC_MIXER,
			    RT5640_MONO_ADC_R1_SRC_SFT, rt5640_mono_adc_r1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_mono_adc_r1_mux =
	SOC_DAPM_ENUM("Mono ADC1 right source", rt5640_mono_adc_r1_क्रमागत);

अटल स्थिर अक्षर * स्थिर rt5640_mono_adc_r2_src[] = अणु
	"DMIC R1", "DMIC R2", "Mono DAC MIXR"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5640_mono_adc_r2_क्रमागत, RT5640_MONO_ADC_MIXER,
			    RT5640_MONO_ADC_R2_SRC_SFT, rt5640_mono_adc_r2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_mono_adc_r2_mux =
	SOC_DAPM_ENUM("Mono ADC2 right source", rt5640_mono_adc_r2_क्रमागत);

/* DAC2 channel source */
अटल स्थिर अक्षर * स्थिर rt5640_dac_l2_src[] = अणु
	"IF2", "Base L/R"
पूर्ण;

अटल पूर्णांक rt5640_dac_l2_values[] = अणु
	0,
	3,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(rt5640_dac_l2_क्रमागत,
				  RT5640_DSP_PATH2, RT5640_DAC_L2_SEL_SFT,
				  0x3, rt5640_dac_l2_src, rt5640_dac_l2_values);

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_dac_l2_mux =
	SOC_DAPM_ENUM("DAC2 left channel source", rt5640_dac_l2_क्रमागत);

अटल स्थिर अक्षर * स्थिर rt5640_dac_r2_src[] = अणु
	"IF2",
पूर्ण;

अटल पूर्णांक rt5640_dac_r2_values[] = अणु
	0,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(rt5640_dac_r2_क्रमागत,
				  RT5640_DSP_PATH2, RT5640_DAC_R2_SEL_SFT,
				  0x3, rt5640_dac_r2_src, rt5640_dac_r2_values);

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_dac_r2_mux =
	SOC_DAPM_ENUM("DAC2 right channel source", rt5640_dac_r2_क्रमागत);

/* digital पूर्णांकerface and iis पूर्णांकerface map */
अटल स्थिर अक्षर * स्थिर rt5640_dai_iis_map[] = अणु
	"1:1|2:2", "1:2|2:1", "1:1|2:1", "1:2|2:2"
पूर्ण;

अटल पूर्णांक rt5640_dai_iis_map_values[] = अणु
	0,
	5,
	6,
	7,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(rt5640_dai_iis_map_क्रमागत,
				  RT5640_I2S1_SDP, RT5640_I2S_IF_SFT,
				  0x7, rt5640_dai_iis_map,
				  rt5640_dai_iis_map_values);

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_dai_mux =
	SOC_DAPM_ENUM("DAI select", rt5640_dai_iis_map_क्रमागत);

/* SDI select */
अटल स्थिर अक्षर * स्थिर rt5640_sdi_sel[] = अणु
	"IF1", "IF2"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5640_sdi_sel_क्रमागत, RT5640_I2S2_SDP,
			    RT5640_I2S2_SDI_SFT, rt5640_sdi_sel);

अटल स्थिर काष्ठा snd_kcontrol_new rt5640_sdi_mux =
	SOC_DAPM_ENUM("SDI select", rt5640_sdi_sel_क्रमागत);

अटल व्योम hp_amp_घातer_on(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);

	/* depop parameters */
	regmap_update_bits(rt5640->regmap, RT5640_PR_BASE +
		RT5640_CHPUMP_INT_REG1, 0x0700, 0x0200);
	regmap_update_bits(rt5640->regmap, RT5640_DEPOP_M2,
		RT5640_DEPOP_MASK, RT5640_DEPOP_MAN);
	regmap_update_bits(rt5640->regmap, RT5640_DEPOP_M1,
		RT5640_HP_CP_MASK | RT5640_HP_SG_MASK | RT5640_HP_CB_MASK,
		RT5640_HP_CP_PU | RT5640_HP_SG_DIS | RT5640_HP_CB_PU);
	regmap_ग_लिखो(rt5640->regmap, RT5640_PR_BASE + RT5640_HP_DCC_INT1,
			   0x9f00);
	/* headphone amp घातer on */
	regmap_update_bits(rt5640->regmap, RT5640_PWR_ANLG1,
		RT5640_PWR_FV1 | RT5640_PWR_FV2, 0);
	regmap_update_bits(rt5640->regmap, RT5640_PWR_ANLG1,
		RT5640_PWR_HA,
		RT5640_PWR_HA);
	usleep_range(10000, 15000);
	regmap_update_bits(rt5640->regmap, RT5640_PWR_ANLG1,
		RT5640_PWR_FV1 | RT5640_PWR_FV2 ,
		RT5640_PWR_FV1 | RT5640_PWR_FV2);
पूर्ण

अटल व्योम rt5640_pmu_depop(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);

	regmap_update_bits(rt5640->regmap, RT5640_DEPOP_M2,
		RT5640_DEPOP_MASK | RT5640_DIG_DP_MASK,
		RT5640_DEPOP_AUTO | RT5640_DIG_DP_EN);
	regmap_update_bits(rt5640->regmap, RT5640_CHARGE_PUMP,
		RT5640_PM_HP_MASK, RT5640_PM_HP_HV);

	regmap_update_bits(rt5640->regmap, RT5640_DEPOP_M3,
		RT5640_CP_FQ1_MASK | RT5640_CP_FQ2_MASK | RT5640_CP_FQ3_MASK,
		(RT5640_CP_FQ_192_KHZ << RT5640_CP_FQ1_SFT) |
		(RT5640_CP_FQ_12_KHZ << RT5640_CP_FQ2_SFT) |
		(RT5640_CP_FQ_192_KHZ << RT5640_CP_FQ3_SFT));

	regmap_ग_लिखो(rt5640->regmap, RT5640_PR_BASE +
		RT5640_MAMP_INT_REG2, 0x1c00);
	regmap_update_bits(rt5640->regmap, RT5640_DEPOP_M1,
		RT5640_HP_CP_MASK | RT5640_HP_SG_MASK,
		RT5640_HP_CP_PD | RT5640_HP_SG_EN);
	regmap_update_bits(rt5640->regmap, RT5640_PR_BASE +
		RT5640_CHPUMP_INT_REG1, 0x0700, 0x0400);
पूर्ण

अटल पूर्णांक rt5640_hp_event(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		rt5640_pmu_depop(component);
		rt5640->hp_mute = false;
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		rt5640->hp_mute = true;
		msleep(70);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5640_lout_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		hp_amp_घातer_on(component);
		snd_soc_component_update_bits(component, RT5640_PWR_ANLG1,
			RT5640_PWR_LM, RT5640_PWR_LM);
		snd_soc_component_update_bits(component, RT5640_OUTPUT,
			RT5640_L_MUTE | RT5640_R_MUTE, 0);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT5640_OUTPUT,
			RT5640_L_MUTE | RT5640_R_MUTE,
			RT5640_L_MUTE | RT5640_R_MUTE);
		snd_soc_component_update_bits(component, RT5640_PWR_ANLG1,
			RT5640_PWR_LM, 0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5640_hp_घातer_event(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		hp_amp_घातer_on(component);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5640_hp_post_event(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		अगर (!rt5640->hp_mute)
			msleep(80);

		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget rt5640_dapm_widमाला_लो[] = अणु
	/* ASRC */
	SND_SOC_DAPM_SUPPLY_S("Stereo Filter ASRC", 1, RT5640_ASRC_1,
			 15, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("I2S2 Filter ASRC", 1, RT5640_ASRC_1,
			 12, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("I2S2 ASRC", 1, RT5640_ASRC_1,
			 11, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DMIC1 ASRC", 1, RT5640_ASRC_1,
			 9, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DMIC2 ASRC", 1, RT5640_ASRC_1,
			 8, 0, शून्य, 0),


	/* Input Side */
	/* micbias */
	SND_SOC_DAPM_SUPPLY("LDO2", RT5640_PWR_ANLG1,
			RT5640_PWR_LDO2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MICBIAS1", RT5640_PWR_ANLG2,
			RT5640_PWR_MB1_BIT, 0, शून्य, 0),
	/* Input Lines */
	SND_SOC_DAPM_INPUT("DMIC1"),
	SND_SOC_DAPM_INPUT("DMIC2"),
	SND_SOC_DAPM_INPUT("IN1P"),
	SND_SOC_DAPM_INPUT("IN1N"),
	SND_SOC_DAPM_INPUT("IN2P"),
	SND_SOC_DAPM_INPUT("IN2N"),
	SND_SOC_DAPM_INPUT("IN3P"),
	SND_SOC_DAPM_INPUT("IN3N"),
	SND_SOC_DAPM_PGA("DMIC L1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DMIC R1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DMIC L2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DMIC R2", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("DMIC CLK", SND_SOC_NOPM, 0, 0,
		set_dmic_clk, SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_SUPPLY("DMIC1 Power", RT5640_DMIC, RT5640_DMIC_1_EN_SFT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DMIC2 Power", RT5640_DMIC, RT5640_DMIC_2_EN_SFT, 0,
		शून्य, 0),
	/* Boost */
	SND_SOC_DAPM_PGA("BST1", RT5640_PWR_ANLG2,
		RT5640_PWR_BST1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("BST2", RT5640_PWR_ANLG2,
		RT5640_PWR_BST4_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("BST3", RT5640_PWR_ANLG2,
		RT5640_PWR_BST2_BIT, 0, शून्य, 0),
	/* Input Volume */
	SND_SOC_DAPM_PGA("INL VOL", RT5640_PWR_VOL,
		RT5640_PWR_IN_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("INR VOL", RT5640_PWR_VOL,
		RT5640_PWR_IN_R_BIT, 0, शून्य, 0),
	/* REC Mixer */
	SND_SOC_DAPM_MIXER("RECMIXL", RT5640_PWR_MIXER, RT5640_PWR_RM_L_BIT, 0,
			rt5640_rec_l_mix, ARRAY_SIZE(rt5640_rec_l_mix)),
	SND_SOC_DAPM_MIXER("RECMIXR", RT5640_PWR_MIXER, RT5640_PWR_RM_R_BIT, 0,
			rt5640_rec_r_mix, ARRAY_SIZE(rt5640_rec_r_mix)),
	/* ADCs */
	SND_SOC_DAPM_ADC("ADC L", शून्य, RT5640_PWR_DIG1,
			RT5640_PWR_ADC_L_BIT, 0),
	SND_SOC_DAPM_ADC("ADC R", शून्य, RT5640_PWR_DIG1,
			RT5640_PWR_ADC_R_BIT, 0),
	/* ADC Mux */
	SND_SOC_DAPM_MUX("Stereo ADC L2 Mux", SND_SOC_NOPM, 0, 0,
				&rt5640_sto_adc_2_mux),
	SND_SOC_DAPM_MUX("Stereo ADC R2 Mux", SND_SOC_NOPM, 0, 0,
				&rt5640_sto_adc_2_mux),
	SND_SOC_DAPM_MUX("Stereo ADC L1 Mux", SND_SOC_NOPM, 0, 0,
				&rt5640_sto_adc_1_mux),
	SND_SOC_DAPM_MUX("Stereo ADC R1 Mux", SND_SOC_NOPM, 0, 0,
				&rt5640_sto_adc_1_mux),
	SND_SOC_DAPM_MUX("Mono ADC L2 Mux", SND_SOC_NOPM, 0, 0,
				&rt5640_mono_adc_l2_mux),
	SND_SOC_DAPM_MUX("Mono ADC L1 Mux", SND_SOC_NOPM, 0, 0,
				&rt5640_mono_adc_l1_mux),
	SND_SOC_DAPM_MUX("Mono ADC R1 Mux", SND_SOC_NOPM, 0, 0,
				&rt5640_mono_adc_r1_mux),
	SND_SOC_DAPM_MUX("Mono ADC R2 Mux", SND_SOC_NOPM, 0, 0,
				&rt5640_mono_adc_r2_mux),
	/* ADC Mixer */
	SND_SOC_DAPM_SUPPLY("Stereo Filter", RT5640_PWR_DIG2,
		RT5640_PWR_ADC_SF_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Stereo ADC MIXL", SND_SOC_NOPM, 0, 0,
		rt5640_sto_adc_l_mix, ARRAY_SIZE(rt5640_sto_adc_l_mix)),
	SND_SOC_DAPM_MIXER("Stereo ADC MIXR", SND_SOC_NOPM, 0, 0,
		rt5640_sto_adc_r_mix, ARRAY_SIZE(rt5640_sto_adc_r_mix)),
	SND_SOC_DAPM_SUPPLY("Mono Left Filter", RT5640_PWR_DIG2,
		RT5640_PWR_ADC_MF_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Mono ADC MIXL", SND_SOC_NOPM, 0, 0,
		rt5640_mono_adc_l_mix, ARRAY_SIZE(rt5640_mono_adc_l_mix)),
	SND_SOC_DAPM_SUPPLY("Mono Right Filter", RT5640_PWR_DIG2,
		RT5640_PWR_ADC_MF_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Mono ADC MIXR", SND_SOC_NOPM, 0, 0,
		rt5640_mono_adc_r_mix, ARRAY_SIZE(rt5640_mono_adc_r_mix)),

	/* Digital Interface */
	SND_SOC_DAPM_SUPPLY("I2S1", RT5640_PWR_DIG1,
		RT5640_PWR_I2S1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 ADC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 ADC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 ADC R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("I2S2", RT5640_PWR_DIG1,
		RT5640_PWR_I2S2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 ADC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 ADC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 ADC R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	/* Digital Interface Select */
	SND_SOC_DAPM_MUX("DAI1 RX Mux", SND_SOC_NOPM, 0, 0, &rt5640_dai_mux),
	SND_SOC_DAPM_MUX("DAI1 TX Mux", SND_SOC_NOPM, 0, 0, &rt5640_dai_mux),
	SND_SOC_DAPM_MUX("DAI1 IF1 Mux", SND_SOC_NOPM, 0, 0, &rt5640_dai_mux),
	SND_SOC_DAPM_MUX("DAI1 IF2 Mux", SND_SOC_NOPM, 0, 0, &rt5640_dai_mux),
	SND_SOC_DAPM_MUX("SDI1 TX Mux", SND_SOC_NOPM, 0, 0, &rt5640_sdi_mux),
	SND_SOC_DAPM_MUX("DAI2 RX Mux", SND_SOC_NOPM, 0, 0, &rt5640_dai_mux),
	SND_SOC_DAPM_MUX("DAI2 TX Mux", SND_SOC_NOPM, 0, 0, &rt5640_dai_mux),
	SND_SOC_DAPM_MUX("DAI2 IF1 Mux", SND_SOC_NOPM, 0, 0, &rt5640_dai_mux),
	SND_SOC_DAPM_MUX("DAI2 IF2 Mux", SND_SOC_NOPM, 0, 0, &rt5640_dai_mux),
	SND_SOC_DAPM_MUX("SDI2 TX Mux", SND_SOC_NOPM, 0, 0, &rt5640_sdi_mux),
	/* Audio Interface */
	SND_SOC_DAPM_AIF_IN("AIF1RX", "AIF1 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX", "AIF1 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF2RX", "AIF2 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2TX", "AIF2 Capture", 0, SND_SOC_NOPM, 0, 0),

	/* Output Side */
	/* DAC mixer beक्रमe sound effect  */
	SND_SOC_DAPM_MIXER("DAC MIXL", SND_SOC_NOPM, 0, 0,
		rt5640_dac_l_mix, ARRAY_SIZE(rt5640_dac_l_mix)),
	SND_SOC_DAPM_MIXER("DAC MIXR", SND_SOC_NOPM, 0, 0,
		rt5640_dac_r_mix, ARRAY_SIZE(rt5640_dac_r_mix)),

	/* DAC Mixer */
	SND_SOC_DAPM_MIXER("Mono DAC MIXL", SND_SOC_NOPM, 0, 0,
		rt5640_mono_dac_l_mix, ARRAY_SIZE(rt5640_mono_dac_l_mix)),
	SND_SOC_DAPM_MIXER("Mono DAC MIXR", SND_SOC_NOPM, 0, 0,
		rt5640_mono_dac_r_mix, ARRAY_SIZE(rt5640_mono_dac_r_mix)),
	SND_SOC_DAPM_MIXER("DIG MIXL", SND_SOC_NOPM, 0, 0,
		rt5640_dig_l_mix, ARRAY_SIZE(rt5640_dig_l_mix)),
	SND_SOC_DAPM_MIXER("DIG MIXR", SND_SOC_NOPM, 0, 0,
		rt5640_dig_r_mix, ARRAY_SIZE(rt5640_dig_r_mix)),
	/* DACs */
	SND_SOC_DAPM_DAC("DAC L1", शून्य, SND_SOC_NOPM,
			0, 0),
	SND_SOC_DAPM_DAC("DAC R1", शून्य, SND_SOC_NOPM,
			0, 0),
	SND_SOC_DAPM_SUPPLY("DAC L1 Power", RT5640_PWR_DIG1,
		RT5640_PWR_DAC_L1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC R1 Power", RT5640_PWR_DIG1,
		RT5640_PWR_DAC_R1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC L2 Power", RT5640_PWR_DIG1,
		RT5640_PWR_DAC_L2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC R2 Power", RT5640_PWR_DIG1,
		RT5640_PWR_DAC_R2_BIT, 0, शून्य, 0),
	/* SPK/OUT Mixer */
	SND_SOC_DAPM_MIXER("SPK MIXL", RT5640_PWR_MIXER, RT5640_PWR_SM_L_BIT,
		0, rt5640_spk_l_mix, ARRAY_SIZE(rt5640_spk_l_mix)),
	SND_SOC_DAPM_MIXER("SPK MIXR", RT5640_PWR_MIXER, RT5640_PWR_SM_R_BIT,
		0, rt5640_spk_r_mix, ARRAY_SIZE(rt5640_spk_r_mix)),
	/* Ouput Volume */
	SND_SOC_DAPM_PGA("SPKVOL L", RT5640_PWR_VOL,
		RT5640_PWR_SV_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SPKVOL R", RT5640_PWR_VOL,
		RT5640_PWR_SV_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("OUTVOL L", RT5640_PWR_VOL,
		RT5640_PWR_OV_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("OUTVOL R", RT5640_PWR_VOL,
		RT5640_PWR_OV_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("HPOVOL L", RT5640_PWR_VOL,
		RT5640_PWR_HV_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("HPOVOL R", RT5640_PWR_VOL,
		RT5640_PWR_HV_R_BIT, 0, शून्य, 0),
	/* SPO/HPO/LOUT/Mono Mixer */
	SND_SOC_DAPM_MIXER("SPOL MIX", SND_SOC_NOPM, 0,
		0, rt5640_spo_l_mix, ARRAY_SIZE(rt5640_spo_l_mix)),
	SND_SOC_DAPM_MIXER("SPOR MIX", SND_SOC_NOPM, 0,
		0, rt5640_spo_r_mix, ARRAY_SIZE(rt5640_spo_r_mix)),
	SND_SOC_DAPM_MIXER("LOUT MIX", SND_SOC_NOPM, 0, 0,
		rt5640_lout_mix, ARRAY_SIZE(rt5640_lout_mix)),
	SND_SOC_DAPM_SUPPLY_S("Improve HP Amp Drv", 1, SND_SOC_NOPM,
		0, 0, rt5640_hp_घातer_event, SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_S("HP Amp", 1, SND_SOC_NOPM, 0, 0,
		rt5640_hp_event,
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_S("LOUT amp", 1, SND_SOC_NOPM, 0, 0,
		rt5640_lout_event,
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SUPPLY("HP L Amp", RT5640_PWR_ANLG1,
		RT5640_PWR_HP_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("HP R Amp", RT5640_PWR_ANLG1,
		RT5640_PWR_HP_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Improve SPK Amp Drv", RT5640_PWR_DIG1,
		RT5640_PWR_CLS_D_BIT, 0, शून्य, 0),

	/* Output Switch */
	SND_SOC_DAPM_SWITCH("Speaker L Playback", SND_SOC_NOPM, 0, 0,
			&spk_l_enable_control),
	SND_SOC_DAPM_SWITCH("Speaker R Playback", SND_SOC_NOPM, 0, 0,
			&spk_r_enable_control),
	SND_SOC_DAPM_SWITCH("HP L Playback", SND_SOC_NOPM, 0, 0,
			&hp_l_enable_control),
	SND_SOC_DAPM_SWITCH("HP R Playback", SND_SOC_NOPM, 0, 0,
			&hp_r_enable_control),
	SND_SOC_DAPM_POST("HP Post", rt5640_hp_post_event),
	/* Output Lines */
	SND_SOC_DAPM_OUTPUT("SPOLP"),
	SND_SOC_DAPM_OUTPUT("SPOLN"),
	SND_SOC_DAPM_OUTPUT("SPORP"),
	SND_SOC_DAPM_OUTPUT("SPORN"),
	SND_SOC_DAPM_OUTPUT("HPOL"),
	SND_SOC_DAPM_OUTPUT("HPOR"),
	SND_SOC_DAPM_OUTPUT("LOUTL"),
	SND_SOC_DAPM_OUTPUT("LOUTR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget rt5640_specअगरic_dapm_widमाला_लो[] = अणु
	/* Audio DSP */
	SND_SOC_DAPM_PGA("Audio DSP", SND_SOC_NOPM, 0, 0, शून्य, 0),
	/* ANC */
	SND_SOC_DAPM_PGA("ANC", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* DAC2 channel Mux */
	SND_SOC_DAPM_MUX("DAC L2 Mux", SND_SOC_NOPM, 0, 0, &rt5640_dac_l2_mux),
	SND_SOC_DAPM_MUX("DAC R2 Mux", SND_SOC_NOPM, 0, 0, &rt5640_dac_r2_mux),

	SND_SOC_DAPM_MIXER("Stereo DAC MIXL", SND_SOC_NOPM, 0, 0,
		rt5640_sto_dac_l_mix, ARRAY_SIZE(rt5640_sto_dac_l_mix)),
	SND_SOC_DAPM_MIXER("Stereo DAC MIXR", SND_SOC_NOPM, 0, 0,
		rt5640_sto_dac_r_mix, ARRAY_SIZE(rt5640_sto_dac_r_mix)),

	SND_SOC_DAPM_DAC("DAC R2", शून्य, SND_SOC_NOPM, 0,
		0),
	SND_SOC_DAPM_DAC("DAC L2", शून्य, SND_SOC_NOPM, 0,
		0),

	SND_SOC_DAPM_MIXER("OUT MIXL", RT5640_PWR_MIXER, RT5640_PWR_OM_L_BIT,
		0, rt5640_out_l_mix, ARRAY_SIZE(rt5640_out_l_mix)),
	SND_SOC_DAPM_MIXER("OUT MIXR", RT5640_PWR_MIXER, RT5640_PWR_OM_R_BIT,
		0, rt5640_out_r_mix, ARRAY_SIZE(rt5640_out_r_mix)),

	SND_SOC_DAPM_MIXER("HPO MIX L", SND_SOC_NOPM, 0, 0,
		rt5640_hpo_mix, ARRAY_SIZE(rt5640_hpo_mix)),
	SND_SOC_DAPM_MIXER("HPO MIX R", SND_SOC_NOPM, 0, 0,
		rt5640_hpo_mix, ARRAY_SIZE(rt5640_hpo_mix)),

	SND_SOC_DAPM_MIXER("Mono MIX", RT5640_PWR_ANLG1, RT5640_PWR_MM_BIT, 0,
		rt5640_mono_mix, ARRAY_SIZE(rt5640_mono_mix)),
	SND_SOC_DAPM_SUPPLY("Improve MONO Amp Drv", RT5640_PWR_ANLG1,
		RT5640_PWR_MA_BIT, 0, शून्य, 0),

	SND_SOC_DAPM_OUTPUT("MONOP"),
	SND_SOC_DAPM_OUTPUT("MONON"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget rt5639_specअगरic_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIXER("Stereo DAC MIXL", SND_SOC_NOPM, 0, 0,
		rt5639_sto_dac_l_mix, ARRAY_SIZE(rt5639_sto_dac_l_mix)),
	SND_SOC_DAPM_MIXER("Stereo DAC MIXR", SND_SOC_NOPM, 0, 0,
		rt5639_sto_dac_r_mix, ARRAY_SIZE(rt5639_sto_dac_r_mix)),

	SND_SOC_DAPM_MIXER("OUT MIXL", RT5640_PWR_MIXER, RT5640_PWR_OM_L_BIT,
		0, rt5639_out_l_mix, ARRAY_SIZE(rt5639_out_l_mix)),
	SND_SOC_DAPM_MIXER("OUT MIXR", RT5640_PWR_MIXER, RT5640_PWR_OM_R_BIT,
		0, rt5639_out_r_mix, ARRAY_SIZE(rt5639_out_r_mix)),

	SND_SOC_DAPM_MIXER("HPO MIX L", SND_SOC_NOPM, 0, 0,
		rt5639_hpo_mix, ARRAY_SIZE(rt5639_hpo_mix)),
	SND_SOC_DAPM_MIXER("HPO MIX R", SND_SOC_NOPM, 0, 0,
		rt5639_hpo_mix, ARRAY_SIZE(rt5639_hpo_mix)),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5640_dapm_routes[] = अणु
	अणु "I2S1", शून्य, "Stereo Filter ASRC", is_using_asrc पूर्ण,
	अणु "I2S2", शून्य, "I2S2 ASRC", is_using_asrc पूर्ण,
	अणु "I2S2", शून्य, "I2S2 Filter ASRC", is_using_asrc पूर्ण,
	अणु "DMIC1", शून्य, "DMIC1 ASRC", is_using_asrc पूर्ण,
	अणु "DMIC2", शून्य, "DMIC2 ASRC", is_using_asrc पूर्ण,

	अणु"IN1P", शून्य, "LDO2"पूर्ण,
	अणु"IN2P", शून्य, "LDO2"पूर्ण,
	अणु"IN3P", शून्य, "LDO2"पूर्ण,

	अणु"DMIC L1", शून्य, "DMIC1"पूर्ण,
	अणु"DMIC R1", शून्य, "DMIC1"पूर्ण,
	अणु"DMIC L2", शून्य, "DMIC2"पूर्ण,
	अणु"DMIC R2", शून्य, "DMIC2"पूर्ण,

	अणु"BST1", शून्य, "IN1P"पूर्ण,
	अणु"BST1", शून्य, "IN1N"पूर्ण,
	अणु"BST2", शून्य, "IN2P"पूर्ण,
	अणु"BST2", शून्य, "IN2N"पूर्ण,
	अणु"BST3", शून्य, "IN3P"पूर्ण,
	अणु"BST3", शून्य, "IN3N"पूर्ण,

	अणु"INL VOL", शून्य, "IN2P"पूर्ण,
	अणु"INR VOL", शून्य, "IN2N"पूर्ण,

	अणु"RECMIXL", "HPOL Switch", "HPOL"पूर्ण,
	अणु"RECMIXL", "INL Switch", "INL VOL"पूर्ण,
	अणु"RECMIXL", "BST3 Switch", "BST3"पूर्ण,
	अणु"RECMIXL", "BST2 Switch", "BST2"पूर्ण,
	अणु"RECMIXL", "BST1 Switch", "BST1"पूर्ण,
	अणु"RECMIXL", "OUT MIXL Switch", "OUT MIXL"पूर्ण,

	अणु"RECMIXR", "HPOR Switch", "HPOR"पूर्ण,
	अणु"RECMIXR", "INR Switch", "INR VOL"पूर्ण,
	अणु"RECMIXR", "BST3 Switch", "BST3"पूर्ण,
	अणु"RECMIXR", "BST2 Switch", "BST2"पूर्ण,
	अणु"RECMIXR", "BST1 Switch", "BST1"पूर्ण,
	अणु"RECMIXR", "OUT MIXR Switch", "OUT MIXR"पूर्ण,

	अणु"ADC L", शून्य, "RECMIXL"पूर्ण,
	अणु"ADC R", शून्य, "RECMIXR"पूर्ण,

	अणु"DMIC L1", शून्य, "DMIC CLK"पूर्ण,
	अणु"DMIC L1", शून्य, "DMIC1 Power"पूर्ण,
	अणु"DMIC R1", शून्य, "DMIC CLK"पूर्ण,
	अणु"DMIC R1", शून्य, "DMIC1 Power"पूर्ण,
	अणु"DMIC L2", शून्य, "DMIC CLK"पूर्ण,
	अणु"DMIC L2", शून्य, "DMIC2 Power"पूर्ण,
	अणु"DMIC R2", शून्य, "DMIC CLK"पूर्ण,
	अणु"DMIC R2", शून्य, "DMIC2 Power"पूर्ण,

	अणु"Stereo ADC L2 Mux", "DMIC1", "DMIC L1"पूर्ण,
	अणु"Stereo ADC L2 Mux", "DMIC2", "DMIC L2"पूर्ण,
	अणु"Stereo ADC L2 Mux", "DIG MIX", "DIG MIXL"पूर्ण,
	अणु"Stereo ADC L1 Mux", "ADC", "ADC L"पूर्ण,
	अणु"Stereo ADC L1 Mux", "DIG MIX", "DIG MIXL"पूर्ण,

	अणु"Stereo ADC R1 Mux", "ADC", "ADC R"पूर्ण,
	अणु"Stereo ADC R1 Mux", "DIG MIX", "DIG MIXR"पूर्ण,
	अणु"Stereo ADC R2 Mux", "DMIC1", "DMIC R1"पूर्ण,
	अणु"Stereo ADC R2 Mux", "DMIC2", "DMIC R2"पूर्ण,
	अणु"Stereo ADC R2 Mux", "DIG MIX", "DIG MIXR"पूर्ण,

	अणु"Mono ADC L2 Mux", "DMIC L1", "DMIC L1"पूर्ण,
	अणु"Mono ADC L2 Mux", "DMIC L2", "DMIC L2"पूर्ण,
	अणु"Mono ADC L2 Mux", "Mono DAC MIXL", "Mono DAC MIXL"पूर्ण,
	अणु"Mono ADC L1 Mux", "Mono DAC MIXL", "Mono DAC MIXL"पूर्ण,
	अणु"Mono ADC L1 Mux", "ADCL", "ADC L"पूर्ण,

	अणु"Mono ADC R1 Mux", "Mono DAC MIXR", "Mono DAC MIXR"पूर्ण,
	अणु"Mono ADC R1 Mux", "ADCR", "ADC R"पूर्ण,
	अणु"Mono ADC R2 Mux", "DMIC R1", "DMIC R1"पूर्ण,
	अणु"Mono ADC R2 Mux", "DMIC R2", "DMIC R2"पूर्ण,
	अणु"Mono ADC R2 Mux", "Mono DAC MIXR", "Mono DAC MIXR"पूर्ण,

	अणु"Stereo ADC MIXL", "ADC1 Switch", "Stereo ADC L1 Mux"पूर्ण,
	अणु"Stereo ADC MIXL", "ADC2 Switch", "Stereo ADC L2 Mux"पूर्ण,
	अणु"Stereo ADC MIXL", शून्य, "Stereo Filter"पूर्ण,

	अणु"Stereo ADC MIXR", "ADC1 Switch", "Stereo ADC R1 Mux"पूर्ण,
	अणु"Stereo ADC MIXR", "ADC2 Switch", "Stereo ADC R2 Mux"पूर्ण,
	अणु"Stereo ADC MIXR", शून्य, "Stereo Filter"पूर्ण,

	अणु"Mono ADC MIXL", "ADC1 Switch", "Mono ADC L1 Mux"पूर्ण,
	अणु"Mono ADC MIXL", "ADC2 Switch", "Mono ADC L2 Mux"पूर्ण,
	अणु"Mono ADC MIXL", शून्य, "Mono Left Filter"पूर्ण,

	अणु"Mono ADC MIXR", "ADC1 Switch", "Mono ADC R1 Mux"पूर्ण,
	अणु"Mono ADC MIXR", "ADC2 Switch", "Mono ADC R2 Mux"पूर्ण,
	अणु"Mono ADC MIXR", शून्य, "Mono Right Filter"पूर्ण,

	अणु"IF2 ADC L", शून्य, "Mono ADC MIXL"पूर्ण,
	अणु"IF2 ADC R", शून्य, "Mono ADC MIXR"पूर्ण,
	अणु"IF1 ADC L", शून्य, "Stereo ADC MIXL"पूर्ण,
	अणु"IF1 ADC R", शून्य, "Stereo ADC MIXR"पूर्ण,

	अणु"IF1 ADC", शून्य, "I2S1"पूर्ण,
	अणु"IF1 ADC", शून्य, "IF1 ADC L"पूर्ण,
	अणु"IF1 ADC", शून्य, "IF1 ADC R"पूर्ण,
	अणु"IF2 ADC", शून्य, "I2S2"पूर्ण,
	अणु"IF2 ADC", शून्य, "IF2 ADC L"पूर्ण,
	अणु"IF2 ADC", शून्य, "IF2 ADC R"पूर्ण,

	अणु"DAI1 TX Mux", "1:1|2:2", "IF1 ADC"पूर्ण,
	अणु"DAI1 TX Mux", "1:2|2:1", "IF2 ADC"पूर्ण,
	अणु"DAI1 IF1 Mux", "1:1|2:1", "IF1 ADC"पूर्ण,
	अणु"DAI1 IF2 Mux", "1:1|2:1", "IF2 ADC"पूर्ण,
	अणु"SDI1 TX Mux", "IF1", "DAI1 IF1 Mux"पूर्ण,
	अणु"SDI1 TX Mux", "IF2", "DAI1 IF2 Mux"पूर्ण,

	अणु"DAI2 TX Mux", "1:2|2:1", "IF1 ADC"पूर्ण,
	अणु"DAI2 TX Mux", "1:1|2:2", "IF2 ADC"पूर्ण,
	अणु"DAI2 IF1 Mux", "1:2|2:2", "IF1 ADC"पूर्ण,
	अणु"DAI2 IF2 Mux", "1:2|2:2", "IF2 ADC"पूर्ण,
	अणु"SDI2 TX Mux", "IF1", "DAI2 IF1 Mux"पूर्ण,
	अणु"SDI2 TX Mux", "IF2", "DAI2 IF2 Mux"पूर्ण,

	अणु"AIF1TX", शून्य, "DAI1 TX Mux"पूर्ण,
	अणु"AIF1TX", शून्य, "SDI1 TX Mux"पूर्ण,
	अणु"AIF2TX", शून्य, "DAI2 TX Mux"पूर्ण,
	अणु"AIF2TX", शून्य, "SDI2 TX Mux"पूर्ण,

	अणु"DAI1 RX Mux", "1:1|2:2", "AIF1RX"पूर्ण,
	अणु"DAI1 RX Mux", "1:1|2:1", "AIF1RX"पूर्ण,
	अणु"DAI1 RX Mux", "1:2|2:1", "AIF2RX"पूर्ण,
	अणु"DAI1 RX Mux", "1:2|2:2", "AIF2RX"पूर्ण,

	अणु"DAI2 RX Mux", "1:2|2:1", "AIF1RX"पूर्ण,
	अणु"DAI2 RX Mux", "1:1|2:1", "AIF1RX"पूर्ण,
	अणु"DAI2 RX Mux", "1:1|2:2", "AIF2RX"पूर्ण,
	अणु"DAI2 RX Mux", "1:2|2:2", "AIF2RX"पूर्ण,

	अणु"IF1 DAC", शून्य, "I2S1"पूर्ण,
	अणु"IF1 DAC", शून्य, "DAI1 RX Mux"पूर्ण,
	अणु"IF2 DAC", शून्य, "I2S2"पूर्ण,
	अणु"IF2 DAC", शून्य, "DAI2 RX Mux"पूर्ण,

	अणु"IF1 DAC L", शून्य, "IF1 DAC"पूर्ण,
	अणु"IF1 DAC R", शून्य, "IF1 DAC"पूर्ण,
	अणु"IF2 DAC L", शून्य, "IF2 DAC"पूर्ण,
	अणु"IF2 DAC R", शून्य, "IF2 DAC"पूर्ण,

	अणु"DAC MIXL", "Stereo ADC Switch", "Stereo ADC MIXL"पूर्ण,
	अणु"DAC MIXL", "INF1 Switch", "IF1 DAC L"पूर्ण,
	अणु"DAC MIXL", शून्य, "DAC L1 Power"पूर्ण,
	अणु"DAC MIXR", "Stereo ADC Switch", "Stereo ADC MIXR"पूर्ण,
	अणु"DAC MIXR", "INF1 Switch", "IF1 DAC R"पूर्ण,
	अणु"DAC MIXR", शून्य, "DAC R1 Power"पूर्ण,

	अणु"Stereo DAC MIXL", "DAC L1 Switch", "DAC MIXL"पूर्ण,
	अणु"Stereo DAC MIXR", "DAC R1 Switch", "DAC MIXR"पूर्ण,

	अणु"Mono DAC MIXL", "DAC L1 Switch", "DAC MIXL"पूर्ण,
	अणु"Mono DAC MIXR", "DAC R1 Switch", "DAC MIXR"पूर्ण,

	अणु"DIG MIXL", "DAC L1 Switch", "DAC MIXL"पूर्ण,
	अणु"DIG MIXR", "DAC R1 Switch", "DAC MIXR"पूर्ण,

	अणु"DAC L1", शून्य, "Stereo DAC MIXL"पूर्ण,
	अणु"DAC L1", शून्य, "DAC L1 Power"पूर्ण,
	अणु"DAC R1", शून्य, "Stereo DAC MIXR"पूर्ण,
	अणु"DAC R1", शून्य, "DAC R1 Power"पूर्ण,

	अणु"SPK MIXL", "REC MIXL Switch", "RECMIXL"पूर्ण,
	अणु"SPK MIXL", "INL Switch", "INL VOL"पूर्ण,
	अणु"SPK MIXL", "DAC L1 Switch", "DAC L1"पूर्ण,
	अणु"SPK MIXL", "OUT MIXL Switch", "OUT MIXL"पूर्ण,
	अणु"SPK MIXR", "REC MIXR Switch", "RECMIXR"पूर्ण,
	अणु"SPK MIXR", "INR Switch", "INR VOL"पूर्ण,
	अणु"SPK MIXR", "DAC R1 Switch", "DAC R1"पूर्ण,
	अणु"SPK MIXR", "OUT MIXR Switch", "OUT MIXR"पूर्ण,

	अणु"OUT MIXL", "BST1 Switch", "BST1"पूर्ण,
	अणु"OUT MIXL", "INL Switch", "INL VOL"पूर्ण,
	अणु"OUT MIXL", "REC MIXL Switch", "RECMIXL"पूर्ण,
	अणु"OUT MIXL", "DAC L1 Switch", "DAC L1"पूर्ण,

	अणु"OUT MIXR", "BST2 Switch", "BST2"पूर्ण,
	अणु"OUT MIXR", "BST1 Switch", "BST1"पूर्ण,
	अणु"OUT MIXR", "INR Switch", "INR VOL"पूर्ण,
	अणु"OUT MIXR", "REC MIXR Switch", "RECMIXR"पूर्ण,
	अणु"OUT MIXR", "DAC R1 Switch", "DAC R1"पूर्ण,

	अणु"SPKVOL L", शून्य, "SPK MIXL"पूर्ण,
	अणु"SPKVOL R", शून्य, "SPK MIXR"पूर्ण,
	अणु"HPOVOL L", शून्य, "OUT MIXL"पूर्ण,
	अणु"HPOVOL R", शून्य, "OUT MIXR"पूर्ण,
	अणु"OUTVOL L", शून्य, "OUT MIXL"पूर्ण,
	अणु"OUTVOL R", शून्य, "OUT MIXR"पूर्ण,

	अणु"SPOL MIX", "DAC R1 Switch", "DAC R1"पूर्ण,
	अणु"SPOL MIX", "DAC L1 Switch", "DAC L1"पूर्ण,
	अणु"SPOL MIX", "SPKVOL R Switch", "SPKVOL R"पूर्ण,
	अणु"SPOL MIX", "SPKVOL L Switch", "SPKVOL L"पूर्ण,
	अणु"SPOL MIX", "BST1 Switch", "BST1"पूर्ण,
	अणु"SPOR MIX", "DAC R1 Switch", "DAC R1"पूर्ण,
	अणु"SPOR MIX", "SPKVOL R Switch", "SPKVOL R"पूर्ण,
	अणु"SPOR MIX", "BST1 Switch", "BST1"पूर्ण,

	अणु"HPO MIX L", "HPO MIX DAC1 Switch", "DAC L1"पूर्ण,
	अणु"HPO MIX L", "HPO MIX HPVOL Switch", "HPOVOL L"पूर्ण,
	अणु"HPO MIX L", शून्य, "HP L Amp"पूर्ण,
	अणु"HPO MIX R", "HPO MIX DAC1 Switch", "DAC R1"पूर्ण,
	अणु"HPO MIX R", "HPO MIX HPVOL Switch", "HPOVOL R"पूर्ण,
	अणु"HPO MIX R", शून्य, "HP R Amp"पूर्ण,

	अणु"LOUT MIX", "DAC L1 Switch", "DAC L1"पूर्ण,
	अणु"LOUT MIX", "DAC R1 Switch", "DAC R1"पूर्ण,
	अणु"LOUT MIX", "OUTVOL L Switch", "OUTVOL L"पूर्ण,
	अणु"LOUT MIX", "OUTVOL R Switch", "OUTVOL R"पूर्ण,

	अणु"HP Amp", शून्य, "HPO MIX L"पूर्ण,
	अणु"HP Amp", शून्य, "HPO MIX R"पूर्ण,

	अणु"Speaker L Playback", "Switch", "SPOL MIX"पूर्ण,
	अणु"Speaker R Playback", "Switch", "SPOR MIX"पूर्ण,
	अणु"SPOLP", शून्य, "Speaker L Playback"पूर्ण,
	अणु"SPOLN", शून्य, "Speaker L Playback"पूर्ण,
	अणु"SPORP", शून्य, "Speaker R Playback"पूर्ण,
	अणु"SPORN", शून्य, "Speaker R Playback"पूर्ण,

	अणु"SPOLP", शून्य, "Improve SPK Amp Drv"पूर्ण,
	अणु"SPOLN", शून्य, "Improve SPK Amp Drv"पूर्ण,
	अणु"SPORP", शून्य, "Improve SPK Amp Drv"पूर्ण,
	अणु"SPORN", शून्य, "Improve SPK Amp Drv"पूर्ण,

	अणु"HPOL", शून्य, "Improve HP Amp Drv"पूर्ण,
	अणु"HPOR", शून्य, "Improve HP Amp Drv"पूर्ण,

	अणु"HP L Playback", "Switch", "HP Amp"पूर्ण,
	अणु"HP R Playback", "Switch", "HP Amp"पूर्ण,
	अणु"HPOL", शून्य, "HP L Playback"पूर्ण,
	अणु"HPOR", शून्य, "HP R Playback"पूर्ण,

	अणु"LOUT amp", शून्य, "LOUT MIX"पूर्ण,
	अणु"LOUTL", शून्य, "LOUT amp"पूर्ण,
	अणु"LOUTR", शून्य, "LOUT amp"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5640_specअगरic_dapm_routes[] = अणु
	अणु"ANC", शून्य, "Stereo ADC MIXL"पूर्ण,
	अणु"ANC", शून्य, "Stereo ADC MIXR"पूर्ण,

	अणु"Audio DSP", शून्य, "DAC MIXL"पूर्ण,
	अणु"Audio DSP", शून्य, "DAC MIXR"पूर्ण,

	अणु"DAC L2 Mux", "IF2", "IF2 DAC L"पूर्ण,
	अणु"DAC L2 Mux", "Base L/R", "Audio DSP"पूर्ण,
	अणु"DAC L2 Mux", शून्य, "DAC L2 Power"पूर्ण,
	अणु"DAC R2 Mux", "IF2", "IF2 DAC R"पूर्ण,
	अणु"DAC R2 Mux", शून्य, "DAC R2 Power"पूर्ण,

	अणु"Stereo DAC MIXL", "DAC L2 Switch", "DAC L2 Mux"पूर्ण,
	अणु"Stereo DAC MIXL", "ANC Switch", "ANC"पूर्ण,
	अणु"Stereo DAC MIXR", "DAC R2 Switch", "DAC R2 Mux"पूर्ण,
	अणु"Stereo DAC MIXR", "ANC Switch", "ANC"पूर्ण,

	अणु"Mono DAC MIXL", "DAC L2 Switch", "DAC L2 Mux"पूर्ण,
	अणु"Mono DAC MIXL", "DAC R2 Switch", "DAC R2 Mux"पूर्ण,

	अणु"Mono DAC MIXR", "DAC R2 Switch", "DAC R2 Mux"पूर्ण,
	अणु"Mono DAC MIXR", "DAC L2 Switch", "DAC L2 Mux"पूर्ण,

	अणु"DIG MIXR", "DAC R2 Switch", "DAC R2 Mux"पूर्ण,
	अणु"DIG MIXL", "DAC L2 Switch", "DAC L2 Mux"पूर्ण,

	अणु"DAC L2", शून्य, "Mono DAC MIXL"पूर्ण,
	अणु"DAC L2", शून्य, "DAC L2 Power"पूर्ण,
	अणु"DAC R2", शून्य, "Mono DAC MIXR"पूर्ण,
	अणु"DAC R2", शून्य, "DAC R2 Power"पूर्ण,

	अणु"SPK MIXL", "DAC L2 Switch", "DAC L2"पूर्ण,
	अणु"SPK MIXR", "DAC R2 Switch", "DAC R2"पूर्ण,

	अणु"OUT MIXL", "SPK MIXL Switch", "SPK MIXL"पूर्ण,
	अणु"OUT MIXR", "SPK MIXR Switch", "SPK MIXR"पूर्ण,

	अणु"OUT MIXL", "DAC R2 Switch", "DAC R2"पूर्ण,
	अणु"OUT MIXL", "DAC L2 Switch", "DAC L2"पूर्ण,

	अणु"OUT MIXR", "DAC L2 Switch", "DAC L2"पूर्ण,
	अणु"OUT MIXR", "DAC R2 Switch", "DAC R2"पूर्ण,

	अणु"HPO MIX L", "HPO MIX DAC2 Switch", "DAC L2"पूर्ण,
	अणु"HPO MIX R", "HPO MIX DAC2 Switch", "DAC R2"पूर्ण,

	अणु"Mono MIX", "DAC R2 Switch", "DAC R2"पूर्ण,
	अणु"Mono MIX", "DAC L2 Switch", "DAC L2"पूर्ण,
	अणु"Mono MIX", "OUTVOL R Switch", "OUTVOL R"पूर्ण,
	अणु"Mono MIX", "OUTVOL L Switch", "OUTVOL L"पूर्ण,
	अणु"Mono MIX", "BST1 Switch", "BST1"पूर्ण,

	अणु"MONOP", शून्य, "Mono MIX"पूर्ण,
	अणु"MONON", शून्य, "Mono MIX"पूर्ण,
	अणु"MONOP", शून्य, "Improve MONO Amp Drv"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5639_specअगरic_dapm_routes[] = अणु
	अणु"Stereo DAC MIXL", "DAC L2 Switch", "IF2 DAC L"पूर्ण,
	अणु"Stereo DAC MIXR", "DAC R2 Switch", "IF2 DAC R"पूर्ण,

	अणु"Mono DAC MIXL", "DAC L2 Switch", "IF2 DAC L"पूर्ण,
	अणु"Mono DAC MIXL", "DAC R2 Switch", "IF2 DAC R"पूर्ण,

	अणु"Mono DAC MIXR", "DAC R2 Switch", "IF2 DAC R"पूर्ण,
	अणु"Mono DAC MIXR", "DAC L2 Switch", "IF2 DAC L"पूर्ण,

	अणु"DIG MIXL", "DAC L2 Switch", "IF2 DAC L"पूर्ण,
	अणु"DIG MIXR", "DAC R2 Switch", "IF2 DAC R"पूर्ण,

	अणु"IF2 DAC L", शून्य, "DAC L2 Power"पूर्ण,
	अणु"IF2 DAC R", शून्य, "DAC R2 Power"पूर्ण,
पूर्ण;

अटल पूर्णांक get_sdp_info(काष्ठा snd_soc_component *component, पूर्णांक dai_id)
अणु
	पूर्णांक ret = 0, val;

	अगर (component == शून्य)
		वापस -EINVAL;

	val = snd_soc_component_पढ़ो(component, RT5640_I2S1_SDP);
	val = (val & RT5640_I2S_IF_MASK) >> RT5640_I2S_IF_SFT;
	चयन (dai_id) अणु
	हाल RT5640_AIF1:
		चयन (val) अणु
		हाल RT5640_IF_123:
		हाल RT5640_IF_132:
			ret |= RT5640_U_IF1;
			अवरोध;
		हाल RT5640_IF_113:
			ret |= RT5640_U_IF1;
			fallthrough;
		हाल RT5640_IF_312:
		हाल RT5640_IF_213:
			ret |= RT5640_U_IF2;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल RT5640_AIF2:
		चयन (val) अणु
		हाल RT5640_IF_231:
		हाल RT5640_IF_213:
			ret |= RT5640_U_IF1;
			अवरोध;
		हाल RT5640_IF_223:
			ret |= RT5640_U_IF1;
			fallthrough;
		हाल RT5640_IF_123:
		हाल RT5640_IF_321:
			ret |= RT5640_U_IF2;
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rt5640_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val_len = 0, val_clk, mask_clk;
	पूर्णांक dai_sel, pre_भाग, bclk_ms, frame_size;

	rt5640->lrck[dai->id] = params_rate(params);
	pre_भाग = rl6231_get_clk_info(rt5640->sysclk, rt5640->lrck[dai->id]);
	अगर (pre_भाग < 0) अणु
		dev_err(component->dev, "Unsupported clock setting %d for DAI %d\n",
			rt5640->lrck[dai->id], dai->id);
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
	rt5640->bclk[dai->id] = rt5640->lrck[dai->id] * (32 << bclk_ms);

	dev_dbg(dai->dev, "bclk is %dHz and lrck is %dHz\n",
		rt5640->bclk[dai->id], rt5640->lrck[dai->id]);
	dev_dbg(dai->dev, "bclk_ms is %d and pre_div is %d for iis %d\n",
				bclk_ms, pre_भाग, dai->id);

	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		val_len |= RT5640_I2S_DL_20;
		अवरोध;
	हाल 24:
		val_len |= RT5640_I2S_DL_24;
		अवरोध;
	हाल 8:
		val_len |= RT5640_I2S_DL_8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dai_sel = get_sdp_info(component, dai->id);
	अगर (dai_sel < 0) अणु
		dev_err(component->dev, "Failed to get sdp info: %d\n", dai_sel);
		वापस -EINVAL;
	पूर्ण
	अगर (dai_sel & RT5640_U_IF1) अणु
		mask_clk = RT5640_I2S_BCLK_MS1_MASK | RT5640_I2S_PD1_MASK;
		val_clk = bclk_ms << RT5640_I2S_BCLK_MS1_SFT |
			pre_भाग << RT5640_I2S_PD1_SFT;
		snd_soc_component_update_bits(component, RT5640_I2S1_SDP,
			RT5640_I2S_DL_MASK, val_len);
		snd_soc_component_update_bits(component, RT5640_ADDA_CLK1, mask_clk, val_clk);
	पूर्ण
	अगर (dai_sel & RT5640_U_IF2) अणु
		mask_clk = RT5640_I2S_BCLK_MS2_MASK | RT5640_I2S_PD2_MASK;
		val_clk = bclk_ms << RT5640_I2S_BCLK_MS2_SFT |
			pre_भाग << RT5640_I2S_PD2_SFT;
		snd_soc_component_update_bits(component, RT5640_I2S2_SDP,
			RT5640_I2S_DL_MASK, val_len);
		snd_soc_component_update_bits(component, RT5640_ADDA_CLK1, mask_clk, val_clk);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5640_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;
	पूर्णांक dai_sel;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		rt5640->master[dai->id] = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		reg_val |= RT5640_I2S_MS_S;
		rt5640->master[dai->id] = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		reg_val |= RT5640_I2S_BP_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT5640_I2S_DF_LEFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT5640_I2S_DF_PCM_A;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		reg_val  |= RT5640_I2S_DF_PCM_B;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dai_sel = get_sdp_info(component, dai->id);
	अगर (dai_sel < 0) अणु
		dev_err(component->dev, "Failed to get sdp info: %d\n", dai_sel);
		वापस -EINVAL;
	पूर्ण
	अगर (dai_sel & RT5640_U_IF1) अणु
		snd_soc_component_update_bits(component, RT5640_I2S1_SDP,
			RT5640_I2S_MS_MASK | RT5640_I2S_BP_MASK |
			RT5640_I2S_DF_MASK, reg_val);
	पूर्ण
	अगर (dai_sel & RT5640_U_IF2) अणु
		snd_soc_component_update_bits(component, RT5640_I2S2_SDP,
			RT5640_I2S_MS_MASK | RT5640_I2S_BP_MASK |
			RT5640_I2S_DF_MASK, reg_val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5640_set_dai_sysclk(काष्ठा snd_soc_dai *dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;
	अचिन्हित पूर्णांक pll_bit = 0;

	अगर (freq == rt5640->sysclk && clk_id == rt5640->sysclk_src)
		वापस 0;

	चयन (clk_id) अणु
	हाल RT5640_SCLK_S_MCLK:
		reg_val |= RT5640_SCLK_SRC_MCLK;
		अवरोध;
	हाल RT5640_SCLK_S_PLL1:
		reg_val |= RT5640_SCLK_SRC_PLL1;
		pll_bit |= RT5640_PWR_PLL;
		अवरोध;
	हाल RT5640_SCLK_S_RCCLK:
		reg_val |= RT5640_SCLK_SRC_RCCLK;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_update_bits(component, RT5640_PWR_ANLG2,
		RT5640_PWR_PLL, pll_bit);
	snd_soc_component_update_bits(component, RT5640_GLB_CLK,
		RT5640_SCLK_SRC_MASK, reg_val);
	rt5640->sysclk = freq;
	rt5640->sysclk_src = clk_id;

	dev_dbg(dai->dev, "Sysclk is %dHz and clock id is %d\n", freq, clk_id);
	वापस 0;
पूर्ण

अटल पूर्णांक rt5640_set_dai_pll(काष्ठा snd_soc_dai *dai, पूर्णांक pll_id, पूर्णांक source,
			अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);
	काष्ठा rl6231_pll_code pll_code;
	पूर्णांक ret;

	अगर (source == rt5640->pll_src && freq_in == rt5640->pll_in &&
	    freq_out == rt5640->pll_out)
		वापस 0;

	अगर (!freq_in || !freq_out) अणु
		dev_dbg(component->dev, "PLL disabled\n");

		rt5640->pll_in = 0;
		rt5640->pll_out = 0;
		snd_soc_component_update_bits(component, RT5640_GLB_CLK,
			RT5640_SCLK_SRC_MASK, RT5640_SCLK_SRC_MCLK);
		वापस 0;
	पूर्ण

	चयन (source) अणु
	हाल RT5640_PLL1_S_MCLK:
		snd_soc_component_update_bits(component, RT5640_GLB_CLK,
			RT5640_PLL1_SRC_MASK, RT5640_PLL1_SRC_MCLK);
		अवरोध;
	हाल RT5640_PLL1_S_BCLK1:
		snd_soc_component_update_bits(component, RT5640_GLB_CLK,
			RT5640_PLL1_SRC_MASK, RT5640_PLL1_SRC_BCLK1);
		अवरोध;
	हाल RT5640_PLL1_S_BCLK2:
		snd_soc_component_update_bits(component, RT5640_GLB_CLK,
			RT5640_PLL1_SRC_MASK, RT5640_PLL1_SRC_BCLK2);
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

	snd_soc_component_ग_लिखो(component, RT5640_PLL_CTRL1,
		(pll_code.n_code << RT5640_PLL_N_SFT) | pll_code.k_code);
	snd_soc_component_ग_लिखो(component, RT5640_PLL_CTRL2,
		((pll_code.m_bp ? 0 : pll_code.m_code) << RT5640_PLL_M_SFT) |
		(pll_code.m_bp << RT5640_PLL_M_BP_SFT));

	rt5640->pll_in = freq_in;
	rt5640->pll_out = freq_out;
	rt5640->pll_src = source;

	वापस 0;
पूर्ण

अटल पूर्णांक rt5640_set_bias_level(काष्ठा snd_soc_component *component,
			क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);
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
		अगर (IS_ERR(rt5640->mclk))
			अवरोध;

		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_ON) अणु
			clk_disable_unprepare(rt5640->mclk);
		पूर्ण अन्यथा अणु
			ret = clk_prepare_enable(rt5640->mclk);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (SND_SOC_BIAS_OFF == snd_soc_component_get_bias_level(component)) अणु
			snd_soc_component_update_bits(component, RT5640_PWR_ANLG1,
				RT5640_PWR_VREF1 | RT5640_PWR_MB |
				RT5640_PWR_BG | RT5640_PWR_VREF2,
				RT5640_PWR_VREF1 | RT5640_PWR_MB |
				RT5640_PWR_BG | RT5640_PWR_VREF2);
			usleep_range(10000, 15000);
			snd_soc_component_update_bits(component, RT5640_PWR_ANLG1,
				RT5640_PWR_FV1 | RT5640_PWR_FV2,
				RT5640_PWR_FV1 | RT5640_PWR_FV2);
			snd_soc_component_update_bits(component, RT5640_DUMMY1,
						0x0301, 0x0301);
			snd_soc_component_update_bits(component, RT5640_MICBIAS,
						0x0030, 0x0030);
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_ग_लिखो(component, RT5640_DEPOP_M1, 0x0004);
		snd_soc_component_ग_लिखो(component, RT5640_DEPOP_M2, 0x1100);
		snd_soc_component_update_bits(component, RT5640_DUMMY1, 0x1, 0);
		snd_soc_component_ग_लिखो(component, RT5640_PWR_DIG1, 0x0000);
		snd_soc_component_ग_लिखो(component, RT5640_PWR_DIG2, 0x0000);
		snd_soc_component_ग_लिखो(component, RT5640_PWR_VOL, 0x0000);
		snd_soc_component_ग_लिखो(component, RT5640_PWR_MIXER, 0x0000);
		snd_soc_component_ग_लिखो(component, RT5640_PWR_ANLG1, 0x0000);
		snd_soc_component_ग_लिखो(component, RT5640_PWR_ANLG2, 0x0000);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rt5640_dmic_enable(काष्ठा snd_soc_component *component,
		       bool dmic1_data_pin, bool dmic2_data_pin)
अणु
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);

	regmap_update_bits(rt5640->regmap, RT5640_GPIO_CTRL1,
		RT5640_GP2_PIN_MASK, RT5640_GP2_PIN_DMIC1_SCL);

	अगर (dmic1_data_pin) अणु
		regmap_update_bits(rt5640->regmap, RT5640_DMIC,
			RT5640_DMIC_1_DP_MASK, RT5640_DMIC_1_DP_GPIO3);
		regmap_update_bits(rt5640->regmap, RT5640_GPIO_CTRL1,
			RT5640_GP3_PIN_MASK, RT5640_GP3_PIN_DMIC1_SDA);
	पूर्ण

	अगर (dmic2_data_pin) अणु
		regmap_update_bits(rt5640->regmap, RT5640_DMIC,
			RT5640_DMIC_2_DP_MASK, RT5640_DMIC_2_DP_GPIO4);
		regmap_update_bits(rt5640->regmap, RT5640_GPIO_CTRL1,
			RT5640_GP4_PIN_MASK, RT5640_GP4_PIN_DMIC2_SDA);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt5640_dmic_enable);

पूर्णांक rt5640_sel_asrc_clk_src(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक filter_mask, अचिन्हित पूर्णांक clk_src)
अणु
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक asrc2_mask = 0;
	अचिन्हित पूर्णांक asrc2_value = 0;

	चयन (clk_src) अणु
	हाल RT5640_CLK_SEL_SYS:
	हाल RT5640_CLK_SEL_ASRC:
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!filter_mask)
		वापस -EINVAL;

	अगर (filter_mask & RT5640_DA_STEREO_FILTER) अणु
		asrc2_mask |= RT5640_STO_DAC_M_MASK;
		asrc2_value = (asrc2_value & ~RT5640_STO_DAC_M_MASK)
			| (clk_src << RT5640_STO_DAC_M_SFT);
	पूर्ण

	अगर (filter_mask & RT5640_DA_MONO_L_FILTER) अणु
		asrc2_mask |= RT5640_MDA_L_M_MASK;
		asrc2_value = (asrc2_value & ~RT5640_MDA_L_M_MASK)
			| (clk_src << RT5640_MDA_L_M_SFT);
	पूर्ण

	अगर (filter_mask & RT5640_DA_MONO_R_FILTER) अणु
		asrc2_mask |= RT5640_MDA_R_M_MASK;
		asrc2_value = (asrc2_value & ~RT5640_MDA_R_M_MASK)
			| (clk_src << RT5640_MDA_R_M_SFT);
	पूर्ण

	अगर (filter_mask & RT5640_AD_STEREO_FILTER) अणु
		asrc2_mask |= RT5640_ADC_M_MASK;
		asrc2_value = (asrc2_value & ~RT5640_ADC_M_MASK)
			| (clk_src << RT5640_ADC_M_SFT);
	पूर्ण

	अगर (filter_mask & RT5640_AD_MONO_L_FILTER) अणु
		asrc2_mask |= RT5640_MAD_L_M_MASK;
		asrc2_value = (asrc2_value & ~RT5640_MAD_L_M_MASK)
			| (clk_src << RT5640_MAD_L_M_SFT);
	पूर्ण

	अगर (filter_mask & RT5640_AD_MONO_R_FILTER)  अणु
		asrc2_mask |= RT5640_MAD_R_M_MASK;
		asrc2_value = (asrc2_value & ~RT5640_MAD_R_M_MASK)
			| (clk_src << RT5640_MAD_R_M_SFT);
	पूर्ण

	snd_soc_component_update_bits(component, RT5640_ASRC_2,
		asrc2_mask, asrc2_value);

	अगर (snd_soc_component_पढ़ो(component, RT5640_ASRC_2)) अणु
		rt5640->asrc_en = true;
		snd_soc_component_update_bits(component, RT5640_JD_CTRL, 0x3, 0x3);
	पूर्ण अन्यथा अणु
		rt5640->asrc_en = false;
		snd_soc_component_update_bits(component, RT5640_JD_CTRL, 0x3, 0x0);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt5640_sel_asrc_clk_src);

अटल व्योम rt5640_enable_micbias1_क्रम_ovcd(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	snd_soc_dapm_mutex_lock(dapm);
	snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "LDO2");
	snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "MICBIAS1");
	/* OVCD is unreliable when used with RCCLK as sysclk-source */
	snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "Platform Clock");
	snd_soc_dapm_sync_unlocked(dapm);
	snd_soc_dapm_mutex_unlock(dapm);
पूर्ण

अटल व्योम rt5640_disable_micbias1_क्रम_ovcd(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	snd_soc_dapm_mutex_lock(dapm);
	snd_soc_dapm_disable_pin_unlocked(dapm, "Platform Clock");
	snd_soc_dapm_disable_pin_unlocked(dapm, "MICBIAS1");
	snd_soc_dapm_disable_pin_unlocked(dapm, "LDO2");
	snd_soc_dapm_sync_unlocked(dapm);
	snd_soc_dapm_mutex_unlock(dapm);
पूर्ण

अटल व्योम rt5640_enable_micbias1_ovcd_irq(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);

	snd_soc_component_update_bits(component, RT5640_IRQ_CTRL2,
		RT5640_IRQ_MB1_OC_MASK, RT5640_IRQ_MB1_OC_NOR);
	rt5640->ovcd_irq_enabled = true;
पूर्ण

अटल व्योम rt5640_disable_micbias1_ovcd_irq(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);

	snd_soc_component_update_bits(component, RT5640_IRQ_CTRL2,
		RT5640_IRQ_MB1_OC_MASK, RT5640_IRQ_MB1_OC_BP);
	rt5640->ovcd_irq_enabled = false;
पूर्ण

अटल व्योम rt5640_clear_micbias1_ovcd(काष्ठा snd_soc_component *component)
अणु
	snd_soc_component_update_bits(component, RT5640_IRQ_CTRL2,
		RT5640_MB1_OC_STATUS, 0);
पूर्ण

अटल bool rt5640_micbias1_ovcd(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक val;

	val = snd_soc_component_पढ़ो(component, RT5640_IRQ_CTRL2);
	dev_dbg(component->dev, "irq ctrl2 %#04x\n", val);

	वापस (val & RT5640_MB1_OC_STATUS);
पूर्ण

अटल bool rt5640_jack_inserted(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);
	पूर्णांक val;

	val = snd_soc_component_पढ़ो(component, RT5640_INT_IRQ_ST);
	dev_dbg(component->dev, "irq status %#04x\n", val);

	अगर (rt5640->jd_inverted)
		वापस !(val & RT5640_JD_STATUS);
	अन्यथा
		वापस (val & RT5640_JD_STATUS);
पूर्ण

/* Jack detect and button-press timings */
#घोषणा JACK_SETTLE_TIME	100 /* milli seconds */
#घोषणा JACK_DETECT_COUNT	5
#घोषणा JACK_DETECT_MAXCOUNT	20  /* Aprox. 2 seconds worth of tries */
#घोषणा JACK_UNPLUG_TIME	80  /* milli seconds */
#घोषणा BP_POLL_TIME		10  /* milli seconds */
#घोषणा BP_POLL_MAXCOUNT	200 /* assume something is wrong after this */
#घोषणा BP_THRESHOLD		3

अटल व्योम rt5640_start_button_press_work(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);

	rt5640->poll_count = 0;
	rt5640->press_count = 0;
	rt5640->release_count = 0;
	rt5640->pressed = false;
	rt5640->press_reported = false;
	rt5640_clear_micbias1_ovcd(component);
	schedule_delayed_work(&rt5640->bp_work, msecs_to_jअगरfies(BP_POLL_TIME));
पूर्ण

अटल व्योम rt5640_button_press_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt5640_priv *rt5640 =
		container_of(work, काष्ठा rt5640_priv, bp_work.work);
	काष्ठा snd_soc_component *component = rt5640->component;

	/* Check the jack was not हटाओd underneath us */
	अगर (!rt5640_jack_inserted(component))
		वापस;

	अगर (rt5640_micbias1_ovcd(component)) अणु
		rt5640->release_count = 0;
		rt5640->press_count++;
		/* Remember till after JACK_UNPLUG_TIME रुको */
		अगर (rt5640->press_count >= BP_THRESHOLD)
			rt5640->pressed = true;
		rt5640_clear_micbias1_ovcd(component);
	पूर्ण अन्यथा अणु
		rt5640->press_count = 0;
		rt5640->release_count++;
	पूर्ण

	/*
	 * The pins get temporarily लघुed on jack unplug, so we poll क्रम
	 * at least JACK_UNPLUG_TIME milli-seconds beक्रमe reporting a press.
	 */
	rt5640->poll_count++;
	अगर (rt5640->poll_count < (JACK_UNPLUG_TIME / BP_POLL_TIME)) अणु
		schedule_delayed_work(&rt5640->bp_work,
				      msecs_to_jअगरfies(BP_POLL_TIME));
		वापस;
	पूर्ण

	अगर (rt5640->pressed && !rt5640->press_reported) अणु
		dev_dbg(component->dev, "headset button press\n");
		snd_soc_jack_report(rt5640->jack, SND_JACK_BTN_0,
				    SND_JACK_BTN_0);
		rt5640->press_reported = true;
	पूर्ण

	अगर (rt5640->release_count >= BP_THRESHOLD) अणु
		अगर (rt5640->press_reported) अणु
			dev_dbg(component->dev, "headset button release\n");
			snd_soc_jack_report(rt5640->jack, 0, SND_JACK_BTN_0);
		पूर्ण
		/* Re-enable OVCD IRQ to detect next press */
		rt5640_enable_micbias1_ovcd_irq(component);
		वापस; /* Stop polling */
	पूर्ण

	schedule_delayed_work(&rt5640->bp_work, msecs_to_jअगरfies(BP_POLL_TIME));
पूर्ण

अटल पूर्णांक rt5640_detect_headset(काष्ठा snd_soc_component *component)
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
		rt5640_clear_micbias1_ovcd(component);

		msleep(JACK_SETTLE_TIME);

		/* Check the jack is still connected beक्रमe checking ovcd */
		अगर (!rt5640_jack_inserted(component))
			वापस 0;

		अगर (rt5640_micbias1_ovcd(component)) अणु
			/*
			 * Over current detected, there is a लघु between the
			 * 2nd ring contact and the ground, so a TRS connector
			 * without a mic contact and thus plain headphones.
			 */
			dev_dbg(component->dev, "jack mic-gnd shorted\n");
			headset_count = 0;
			headphone_count++;
			अगर (headphone_count == JACK_DETECT_COUNT)
				वापस SND_JACK_HEADPHONE;
		पूर्ण अन्यथा अणु
			dev_dbg(component->dev, "jack mic-gnd open\n");
			headphone_count = 0;
			headset_count++;
			अगर (headset_count == JACK_DETECT_COUNT)
				वापस SND_JACK_HEADSET;
		पूर्ण
	पूर्ण

	dev_err(component->dev, "Error detecting headset vs headphones, bad contact?, assuming headphones\n");
	वापस SND_JACK_HEADPHONE;
पूर्ण

अटल व्योम rt5640_jack_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt5640_priv *rt5640 =
		container_of(work, काष्ठा rt5640_priv, jack_work);
	काष्ठा snd_soc_component *component = rt5640->component;
	पूर्णांक status;

	अगर (!rt5640_jack_inserted(component)) अणु
		/* Jack हटाओd, or spurious IRQ? */
		अगर (rt5640->jack->status & SND_JACK_HEADPHONE) अणु
			अगर (rt5640->jack->status & SND_JACK_MICROPHONE) अणु
				cancel_delayed_work_sync(&rt5640->bp_work);
				rt5640_disable_micbias1_ovcd_irq(component);
				rt5640_disable_micbias1_क्रम_ovcd(component);
			पूर्ण
			snd_soc_jack_report(rt5640->jack, 0,
					    SND_JACK_HEADSET | SND_JACK_BTN_0);
			dev_dbg(component->dev, "jack unplugged\n");
		पूर्ण
	पूर्ण अन्यथा अगर (!(rt5640->jack->status & SND_JACK_HEADPHONE)) अणु
		/* Jack inserted */
		WARN_ON(rt5640->ovcd_irq_enabled);
		rt5640_enable_micbias1_क्रम_ovcd(component);
		status = rt5640_detect_headset(component);
		अगर (status == SND_JACK_HEADSET) अणु
			/* Enable ovcd IRQ क्रम button press detect. */
			rt5640_enable_micbias1_ovcd_irq(component);
		पूर्ण अन्यथा अणु
			/* No more need क्रम overcurrent detect. */
			rt5640_disable_micbias1_क्रम_ovcd(component);
		पूर्ण
		dev_dbg(component->dev, "detect status %#02x\n", status);
		snd_soc_jack_report(rt5640->jack, status, SND_JACK_HEADSET);
	पूर्ण अन्यथा अगर (rt5640->ovcd_irq_enabled && rt5640_micbias1_ovcd(component)) अणु
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
		rt5640_disable_micbias1_ovcd_irq(component);
		rt5640_start_button_press_work(component);

		/*
		 * If the jack-detect IRQ flag goes high (unplug) after our
		 * above rt5640_jack_inserted() check and beक्रमe we have
		 * disabled the OVCD IRQ, the IRQ pin will stay high and as
		 * we react to edges, we miss the unplug event -> recheck.
		 */
		queue_work(प्रणाली_दीर्घ_wq, &rt5640->jack_work);
	पूर्ण
पूर्ण

अटल irqवापस_t rt5640_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rt5640_priv *rt5640 = data;

	अगर (rt5640->jack)
		queue_work(प्रणाली_दीर्घ_wq, &rt5640->jack_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rt5640_cancel_work(व्योम *data)
अणु
	काष्ठा rt5640_priv *rt5640 = data;

	cancel_work_sync(&rt5640->jack_work);
	cancel_delayed_work_sync(&rt5640->bp_work);
पूर्ण

अटल व्योम rt5640_enable_jack_detect(काष्ठा snd_soc_component *component,
				      काष्ठा snd_soc_jack *jack)
अणु
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);

	/* Select JD-source */
	snd_soc_component_update_bits(component, RT5640_JD_CTRL,
		RT5640_JD_MASK, rt5640->jd_src);

	/* Selecting GPIO01 as an पूर्णांकerrupt */
	snd_soc_component_update_bits(component, RT5640_GPIO_CTRL1,
		RT5640_GP1_PIN_MASK, RT5640_GP1_PIN_IRQ);

	/* Set GPIO1 output */
	snd_soc_component_update_bits(component, RT5640_GPIO_CTRL3,
		RT5640_GP1_PF_MASK, RT5640_GP1_PF_OUT);

	/* Enabling jd2 in general control 1 */
	snd_soc_component_ग_लिखो(component, RT5640_DUMMY1, 0x3f41);

	/* Enabling jd2 in general control 2 */
	snd_soc_component_ग_लिखो(component, RT5640_DUMMY2, 0x4001);

	snd_soc_component_ग_लिखो(component, RT5640_PR_BASE + RT5640_BIAS_CUR4,
		0xa800 | rt5640->ovcd_sf);

	snd_soc_component_update_bits(component, RT5640_MICBIAS,
		RT5640_MIC1_OVTH_MASK | RT5640_MIC1_OVCD_MASK,
		rt5640->ovcd_th | RT5640_MIC1_OVCD_EN);

	/*
	 * The over-current-detect is only reliable in detecting the असलence
	 * of over-current, when the mic-contact in the jack is लघु-circuited,
	 * the hardware periodically retries अगर it can apply the bias-current
	 * leading to the ovcd status flip-flopping 1-0-1 with it being 0 about
	 * 10% of the समय, as we poll the ovcd status bit we might hit that
	 * 10%, so we enable sticky mode and when checking OVCD we clear the
	 * status, msleep() a bit and then check to get a reliable पढ़ोing.
	 */
	snd_soc_component_update_bits(component, RT5640_IRQ_CTRL2,
		RT5640_MB1_OC_STKY_MASK, RT5640_MB1_OC_STKY_EN);

	/*
	 * All IRQs get or-ed together, so we need the jack IRQ to report 0
	 * when a jack is inserted so that the OVCD IRQ then toggles the IRQ
	 * pin 0/1 instead of it being stuck to 1. So we invert the JD polarity
	 * on प्रणालीs where the hardware करोes not alपढ़ोy करो this.
	 */
	अगर (rt5640->jd_inverted)
		snd_soc_component_ग_लिखो(component, RT5640_IRQ_CTRL1,
					RT5640_IRQ_JD_NOR);
	अन्यथा
		snd_soc_component_ग_लिखो(component, RT5640_IRQ_CTRL1,
					RT5640_IRQ_JD_NOR | RT5640_JD_P_INV);

	rt5640->jack = jack;
	अगर (rt5640->jack->status & SND_JACK_MICROPHONE) अणु
		rt5640_enable_micbias1_क्रम_ovcd(component);
		rt5640_enable_micbias1_ovcd_irq(component);
	पूर्ण

	enable_irq(rt5640->irq);
	/* sync initial jack state */
	queue_work(प्रणाली_दीर्घ_wq, &rt5640->jack_work);
पूर्ण

अटल व्योम rt5640_disable_jack_detect(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);

	/*
	 * soc_हटाओ_component() क्रमce-disables jack and thus rt5640->jack
	 * could be शून्य at the समय of driver's module unloading.
	 */
	अगर (!rt5640->jack)
		वापस;

	disable_irq(rt5640->irq);
	rt5640_cancel_work(rt5640);

	अगर (rt5640->jack->status & SND_JACK_MICROPHONE) अणु
		rt5640_disable_micbias1_ovcd_irq(component);
		rt5640_disable_micbias1_क्रम_ovcd(component);
		snd_soc_jack_report(rt5640->jack, 0, SND_JACK_BTN_0);
	पूर्ण

	rt5640->jack = शून्य;
पूर्ण

अटल पूर्णांक rt5640_set_jack(काष्ठा snd_soc_component *component,
			   काष्ठा snd_soc_jack *jack, व्योम *data)
अणु
	अगर (jack)
		rt5640_enable_jack_detect(component, jack);
	अन्यथा
		rt5640_disable_jack_detect(component);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5640_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);
	u32 dmic1_data_pin = 0;
	u32 dmic2_data_pin = 0;
	bool dmic_en = false;
	u32 val;

	/* Check अगर MCLK provided */
	rt5640->mclk = devm_clk_get(component->dev, "mclk");
	अगर (PTR_ERR(rt5640->mclk) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	rt5640->component = component;

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_OFF);

	snd_soc_component_update_bits(component, RT5640_DUMMY1, 0x0301, 0x0301);
	snd_soc_component_update_bits(component, RT5640_MICBIAS, 0x0030, 0x0030);
	snd_soc_component_update_bits(component, RT5640_DSP_PATH2, 0xfc00, 0x0c00);

	चयन (snd_soc_component_पढ़ो(component, RT5640_RESET) & RT5640_ID_MASK) अणु
	हाल RT5640_ID_5640:
	हाल RT5640_ID_5642:
		snd_soc_add_component_controls(component,
			rt5640_specअगरic_snd_controls,
			ARRAY_SIZE(rt5640_specअगरic_snd_controls));
		snd_soc_dapm_new_controls(dapm,
			rt5640_specअगरic_dapm_widमाला_लो,
			ARRAY_SIZE(rt5640_specअगरic_dapm_widमाला_लो));
		snd_soc_dapm_add_routes(dapm,
			rt5640_specअगरic_dapm_routes,
			ARRAY_SIZE(rt5640_specअगरic_dapm_routes));
		अवरोध;
	हाल RT5640_ID_5639:
		snd_soc_dapm_new_controls(dapm,
			rt5639_specअगरic_dapm_widमाला_लो,
			ARRAY_SIZE(rt5639_specअगरic_dapm_widमाला_लो));
		snd_soc_dapm_add_routes(dapm,
			rt5639_specअगरic_dapm_routes,
			ARRAY_SIZE(rt5639_specअगरic_dapm_routes));
		अवरोध;
	शेष:
		dev_err(component->dev,
			"The driver is for RT5639 RT5640 or RT5642 only\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * Note on some platक्रमms the platक्रमm code may need to add device-props
	 * rather then relying only on properties set by the firmware.
	 * Thereक्रम the property parsing MUST be करोne here, rather then from
	 * rt5640_i2c_probe(), so that the platक्रमm-code can attach extra
	 * properties beक्रमe calling snd_soc_रेजिस्टर_card().
	 */
	अगर (device_property_पढ़ो_bool(component->dev, "realtek,in1-differential"))
		snd_soc_component_update_bits(component, RT5640_IN1_IN2,
					      RT5640_IN_DF1, RT5640_IN_DF1);

	अगर (device_property_पढ़ो_bool(component->dev, "realtek,in2-differential"))
		snd_soc_component_update_bits(component, RT5640_IN3_IN4,
					      RT5640_IN_DF2, RT5640_IN_DF2);

	अगर (device_property_पढ़ो_bool(component->dev, "realtek,in3-differential"))
		snd_soc_component_update_bits(component, RT5640_IN1_IN2,
					      RT5640_IN_DF2, RT5640_IN_DF2);

	अगर (device_property_पढ़ो_u32(component->dev, "realtek,dmic1-data-pin",
				     &val) == 0 && val) अणु
		dmic1_data_pin = val - 1;
		dmic_en = true;
	पूर्ण

	अगर (device_property_पढ़ो_u32(component->dev, "realtek,dmic2-data-pin",
				     &val) == 0 && val) अणु
		dmic2_data_pin = val - 1;
		dmic_en = true;
	पूर्ण

	अगर (dmic_en)
		rt5640_dmic_enable(component, dmic1_data_pin, dmic2_data_pin);

	अगर (device_property_पढ़ो_u32(component->dev,
				     "realtek,jack-detect-source", &val) == 0) अणु
		अगर (val <= RT5640_JD_SRC_GPIO4)
			rt5640->jd_src = val << RT5640_JD_SFT;
		अन्यथा
			dev_warn(component->dev, "Warning: Invalid jack-detect-source value: %d, leaving jack-detect disabled\n",
				 val);
	पूर्ण

	अगर (!device_property_पढ़ो_bool(component->dev, "realtek,jack-detect-not-inverted"))
		rt5640->jd_inverted = true;

	/*
	 * Testing on various boards has shown that good शेषs क्रम the OVCD
	 * threshold and scale-factor are 2000तगA and 0.75. For an effective
	 * limit of 1500तगA, this seems to be more reliable then 1500तगA and 1.0.
	 */
	rt5640->ovcd_th = RT5640_MIC1_OVTH_2000UA;
	rt5640->ovcd_sf = RT5640_MIC_OVCD_SF_0P75;

	अगर (device_property_पढ़ो_u32(component->dev,
			"realtek,over-current-threshold-microamp", &val) == 0) अणु
		चयन (val) अणु
		हाल 600:
			rt5640->ovcd_th = RT5640_MIC1_OVTH_600UA;
			अवरोध;
		हाल 1500:
			rt5640->ovcd_th = RT5640_MIC1_OVTH_1500UA;
			अवरोध;
		हाल 2000:
			rt5640->ovcd_th = RT5640_MIC1_OVTH_2000UA;
			अवरोध;
		शेष:
			dev_warn(component->dev, "Warning: Invalid over-current-threshold-microamp value: %d, defaulting to 2000uA\n",
				 val);
		पूर्ण
	पूर्ण

	अगर (device_property_पढ़ो_u32(component->dev,
			"realtek,over-current-scale-factor", &val) == 0) अणु
		अगर (val <= RT5640_OVCD_SF_1P5)
			rt5640->ovcd_sf = val << RT5640_MIC_OVCD_SF_SFT;
		अन्यथा
			dev_warn(component->dev, "Warning: Invalid over-current-scale-factor value: %d, defaulting to 0.75\n",
				 val);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rt5640_हटाओ(काष्ठा snd_soc_component *component)
अणु
	rt5640_reset(component);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rt5640_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_OFF);
	rt5640_reset(component);
	regcache_cache_only(rt5640->regmap, true);
	regcache_mark_dirty(rt5640->regmap);
	अगर (gpio_is_valid(rt5640->lकरो1_en))
		gpio_set_value_cansleep(rt5640->lकरो1_en, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5640_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);

	अगर (gpio_is_valid(rt5640->lकरो1_en)) अणु
		gpio_set_value_cansleep(rt5640->lकरो1_en, 1);
		msleep(400);
	पूर्ण

	regcache_cache_only(rt5640->regmap, false);
	regcache_sync(rt5640->regmap);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा rt5640_suspend शून्य
#घोषणा rt5640_resume शून्य
#पूर्ण_अगर

#घोषणा RT5640_STEREO_RATES SNDRV_PCM_RATE_8000_96000
#घोषणा RT5640_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S8)

अटल स्थिर काष्ठा snd_soc_dai_ops rt5640_aअगर_dai_ops = अणु
	.hw_params = rt5640_hw_params,
	.set_fmt = rt5640_set_dai_fmt,
	.set_sysclk = rt5640_set_dai_sysclk,
	.set_pll = rt5640_set_dai_pll,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt5640_dai[] = अणु
	अणु
		.name = "rt5640-aif1",
		.id = RT5640_AIF1,
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5640_STEREO_RATES,
			.क्रमmats = RT5640_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5640_STEREO_RATES,
			.क्रमmats = RT5640_FORMATS,
		पूर्ण,
		.ops = &rt5640_aअगर_dai_ops,
	पूर्ण,
	अणु
		.name = "rt5640-aif2",
		.id = RT5640_AIF2,
		.playback = अणु
			.stream_name = "AIF2 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5640_STEREO_RATES,
			.क्रमmats = RT5640_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF2 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5640_STEREO_RATES,
			.क्रमmats = RT5640_FORMATS,
		पूर्ण,
		.ops = &rt5640_aअगर_dai_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_rt5640 = अणु
	.probe			= rt5640_probe,
	.हटाओ			= rt5640_हटाओ,
	.suspend		= rt5640_suspend,
	.resume			= rt5640_resume,
	.set_bias_level		= rt5640_set_bias_level,
	.set_jack		= rt5640_set_jack,
	.controls		= rt5640_snd_controls,
	.num_controls		= ARRAY_SIZE(rt5640_snd_controls),
	.dapm_widमाला_लो		= rt5640_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(rt5640_dapm_widमाला_लो),
	.dapm_routes		= rt5640_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(rt5640_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,

पूर्ण;

अटल स्थिर काष्ठा regmap_config rt5640_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,

	.max_रेजिस्टर = RT5640_VENDOR_ID2 + 1 + (ARRAY_SIZE(rt5640_ranges) *
					       RT5640_PR_SPACING),
	.अस्थिर_reg = rt5640_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = rt5640_पढ़ोable_रेजिस्टर,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = rt5640_reg,
	.num_reg_शेषs = ARRAY_SIZE(rt5640_reg),
	.ranges = rt5640_ranges,
	.num_ranges = ARRAY_SIZE(rt5640_ranges),
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id rt5640_i2c_id[] = अणु
	अणु "rt5640", 0 पूर्ण,
	अणु "rt5639", 0 पूर्ण,
	अणु "rt5642", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt5640_i2c_id);

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id rt5640_of_match[] = अणु
	अणु .compatible = "realtek,rt5639", पूर्ण,
	अणु .compatible = "realtek,rt5640", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt5640_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id rt5640_acpi_match[] = अणु
	अणु "INT33CA", 0 पूर्ण,
	अणु "10EC3276", 0 पूर्ण,
	अणु "10EC5640", 0 पूर्ण,
	अणु "10EC5642", 0 पूर्ण,
	अणु "INTCCFFD", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rt5640_acpi_match);
#पूर्ण_अगर

अटल पूर्णांक rt5640_parse_dt(काष्ठा rt5640_priv *rt5640, काष्ठा device_node *np)
अणु
	rt5640->lकरो1_en = of_get_named_gpio(np, "realtek,ldo1-en-gpios", 0);
	/*
	 * LDO1_EN is optional (it may be अटलally tied on the board).
	 * -ENOENT means that the property करोesn't exist, i.e. there is no
	 * GPIO, so is not an error. Any other error code means the property
	 * exists, but could not be parsed.
	 */
	अगर (!gpio_is_valid(rt5640->lकरो1_en) &&
			(rt5640->lकरो1_en != -ENOENT))
		वापस rt5640->lकरो1_en;

	वापस 0;
पूर्ण

अटल पूर्णांक rt5640_i2c_probe(काष्ठा i2c_client *i2c,
		    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rt5640_priv *rt5640;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	rt5640 = devm_kzalloc(&i2c->dev,
				माप(काष्ठा rt5640_priv),
				GFP_KERNEL);
	अगर (शून्य == rt5640)
		वापस -ENOMEM;
	i2c_set_clientdata(i2c, rt5640);

	अगर (i2c->dev.of_node) अणु
		ret = rt5640_parse_dt(rt5640, i2c->dev.of_node);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा
		rt5640->lकरो1_en = -EINVAL;

	rt5640->regmap = devm_regmap_init_i2c(i2c, &rt5640_regmap);
	अगर (IS_ERR(rt5640->regmap)) अणु
		ret = PTR_ERR(rt5640->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (gpio_is_valid(rt5640->lकरो1_en)) अणु
		ret = devm_gpio_request_one(&i2c->dev, rt5640->lकरो1_en,
					    GPIOF_OUT_INIT_HIGH,
					    "RT5640 LDO1_EN");
		अगर (ret < 0) अणु
			dev_err(&i2c->dev, "Failed to request LDO1_EN %d: %d\n",
				rt5640->lकरो1_en, ret);
			वापस ret;
		पूर्ण
		msleep(400);
	पूर्ण

	regmap_पढ़ो(rt5640->regmap, RT5640_VENDOR_ID2, &val);
	अगर (val != RT5640_DEVICE_ID) अणु
		dev_err(&i2c->dev,
			"Device with ID register %#x is not rt5640/39\n", val);
		वापस -ENODEV;
	पूर्ण

	regmap_ग_लिखो(rt5640->regmap, RT5640_RESET, 0);

	ret = regmap_रेजिस्टर_patch(rt5640->regmap, init_list,
				    ARRAY_SIZE(init_list));
	अगर (ret != 0)
		dev_warn(&i2c->dev, "Failed to apply regmap patch: %d\n", ret);

	regmap_update_bits(rt5640->regmap, RT5640_DUMMY1,
				RT5640_MCLK_DET, RT5640_MCLK_DET);

	rt5640->hp_mute = true;
	rt5640->irq = i2c->irq;
	INIT_DELAYED_WORK(&rt5640->bp_work, rt5640_button_press_work);
	INIT_WORK(&rt5640->jack_work, rt5640_jack_work);

	/* Make sure work is stopped on probe-error / हटाओ */
	ret = devm_add_action_or_reset(&i2c->dev, rt5640_cancel_work, rt5640);
	अगर (ret)
		वापस ret;

	ret = devm_request_irq(&i2c->dev, rt5640->irq, rt5640_irq,
			       IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING
			       | IRQF_ONESHOT, "rt5640", rt5640);
	अगर (ret == 0) अणु
		/* Gets re-enabled by rt5640_set_jack() */
		disable_irq(rt5640->irq);
	पूर्ण अन्यथा अणु
		dev_warn(&i2c->dev, "Failed to reguest IRQ %d: %d\n",
			 rt5640->irq, ret);
		rt5640->irq = -ENXIO;
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				      &soc_component_dev_rt5640,
				      rt5640_dai, ARRAY_SIZE(rt5640_dai));
पूर्ण

अटल काष्ठा i2c_driver rt5640_i2c_driver = अणु
	.driver = अणु
		.name = "rt5640",
		.acpi_match_table = ACPI_PTR(rt5640_acpi_match),
		.of_match_table = of_match_ptr(rt5640_of_match),
	पूर्ण,
	.probe = rt5640_i2c_probe,
	.id_table = rt5640_i2c_id,
पूर्ण;
module_i2c_driver(rt5640_i2c_driver);

MODULE_DESCRIPTION("ASoC RT5640/RT5639 driver");
MODULE_AUTHOR("Johnny Hsu <johnnyhsu@realtek.com>");
MODULE_LICENSE("GPL v2");
