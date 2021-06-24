<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rt5670.c  --  RT5670 ALSA SoC audio codec driver
 *
 * Copyright 2014 Realtek Semiconductor Corp.
 * Author: Bard Liao <bardliao@realtek.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/acpi.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/dmi.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/jack.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "rl6231.h"
#समावेश "rt5670.h"
#समावेश "rt5670-dsp.h"

#घोषणा RT5670_GPIO1_IS_IRQ			BIT(0)
#घोषणा RT5670_IN2_DIFF			BIT(1)
#घोषणा RT5670_DMIC_EN			BIT(2)
#घोषणा RT5670_DMIC1_IN2P		BIT(3)
#घोषणा RT5670_DMIC1_GPIO6		BIT(4)
#घोषणा RT5670_DMIC1_GPIO7		BIT(5)
#घोषणा RT5670_DMIC2_INR		BIT(6)
#घोषणा RT5670_DMIC2_GPIO8		BIT(7)
#घोषणा RT5670_DMIC3_GPIO5		BIT(8)
#घोषणा RT5670_JD_MODE1			BIT(9)
#घोषणा RT5670_JD_MODE2			BIT(10)
#घोषणा RT5670_JD_MODE3			BIT(11)
#घोषणा RT5670_GPIO1_IS_EXT_SPK_EN	BIT(12)

अटल अचिन्हित दीर्घ rt5670_quirk;
अटल अचिन्हित पूर्णांक quirk_override;
module_param_named(quirk, quirk_override, uपूर्णांक, 0444);
MODULE_PARM_DESC(quirk, "Board-specific quirk override");

#घोषणा RT5670_DEVICE_ID 0x6271

#घोषणा RT5670_PR_RANGE_BASE (0xff + 1)
#घोषणा RT5670_PR_SPACING 0x100

#घोषणा RT5670_PR_BASE (RT5670_PR_RANGE_BASE + (0 * RT5670_PR_SPACING))

अटल स्थिर काष्ठा regmap_range_cfg rt5670_ranges[] = अणु
	अणु .name = "PR", .range_min = RT5670_PR_BASE,
	  .range_max = RT5670_PR_BASE + 0xf8,
	  .selector_reg = RT5670_PRIV_INDEX,
	  .selector_mask = 0xff,
	  .selector_shअगरt = 0x0,
	  .winकरोw_start = RT5670_PRIV_DATA,
	  .winकरोw_len = 0x1, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence init_list[] = अणु
	अणु RT5670_PR_BASE + 0x14, 0x9a8a पूर्ण,
	अणु RT5670_PR_BASE + 0x38, 0x1fe1 पूर्ण,
	अणु RT5670_PR_BASE + 0x3d, 0x3640 पूर्ण,
	अणु 0x8a, 0x0123 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष rt5670_reg[] = अणु
	अणु 0x00, 0x0000 पूर्ण,
	अणु 0x02, 0x8888 पूर्ण,
	अणु 0x03, 0x8888 पूर्ण,
	अणु 0x0a, 0x0001 पूर्ण,
	अणु 0x0b, 0x0827 पूर्ण,
	अणु 0x0c, 0x0000 पूर्ण,
	अणु 0x0d, 0x0008 पूर्ण,
	अणु 0x0e, 0x0000 पूर्ण,
	अणु 0x0f, 0x0808 पूर्ण,
	अणु 0x19, 0xafaf पूर्ण,
	अणु 0x1a, 0xafaf पूर्ण,
	अणु 0x1b, 0x0011 पूर्ण,
	अणु 0x1c, 0x2f2f पूर्ण,
	अणु 0x1d, 0x2f2f पूर्ण,
	अणु 0x1e, 0x0000 पूर्ण,
	अणु 0x1f, 0x2f2f पूर्ण,
	अणु 0x20, 0x0000 पूर्ण,
	अणु 0x26, 0x7860 पूर्ण,
	अणु 0x27, 0x7860 पूर्ण,
	अणु 0x28, 0x7871 पूर्ण,
	अणु 0x29, 0x8080 पूर्ण,
	अणु 0x2a, 0x5656 पूर्ण,
	अणु 0x2b, 0x5454 पूर्ण,
	अणु 0x2c, 0xaaa0 पूर्ण,
	अणु 0x2d, 0x0000 पूर्ण,
	अणु 0x2e, 0x2f2f पूर्ण,
	अणु 0x2f, 0x1002 पूर्ण,
	अणु 0x30, 0x0000 पूर्ण,
	अणु 0x31, 0x5f00 पूर्ण,
	अणु 0x32, 0x0000 पूर्ण,
	अणु 0x33, 0x0000 पूर्ण,
	अणु 0x34, 0x0000 पूर्ण,
	अणु 0x35, 0x0000 पूर्ण,
	अणु 0x36, 0x0000 पूर्ण,
	अणु 0x37, 0x0000 पूर्ण,
	अणु 0x38, 0x0000 पूर्ण,
	अणु 0x3b, 0x0000 पूर्ण,
	अणु 0x3c, 0x007f पूर्ण,
	अणु 0x3d, 0x0000 पूर्ण,
	अणु 0x3e, 0x007f पूर्ण,
	अणु 0x45, 0xe00f पूर्ण,
	अणु 0x4c, 0x5380 पूर्ण,
	अणु 0x4f, 0x0073 पूर्ण,
	अणु 0x52, 0x00d3 पूर्ण,
	अणु 0x53, 0xf000 पूर्ण,
	अणु 0x61, 0x0000 पूर्ण,
	अणु 0x62, 0x0001 पूर्ण,
	अणु 0x63, 0x00c3 पूर्ण,
	अणु 0x64, 0x0000 पूर्ण,
	अणु 0x65, 0x0001 पूर्ण,
	अणु 0x66, 0x0000 पूर्ण,
	अणु 0x6f, 0x8000 पूर्ण,
	अणु 0x70, 0x8000 पूर्ण,
	अणु 0x71, 0x8000 पूर्ण,
	अणु 0x72, 0x8000 पूर्ण,
	अणु 0x73, 0x7770 पूर्ण,
	अणु 0x74, 0x0e00 पूर्ण,
	अणु 0x75, 0x1505 पूर्ण,
	अणु 0x76, 0x0015 पूर्ण,
	अणु 0x77, 0x0c00 पूर्ण,
	अणु 0x78, 0x4000 पूर्ण,
	अणु 0x79, 0x0123 पूर्ण,
	अणु 0x7f, 0x1100 पूर्ण,
	अणु 0x80, 0x0000 पूर्ण,
	अणु 0x81, 0x0000 पूर्ण,
	अणु 0x82, 0x0000 पूर्ण,
	अणु 0x83, 0x0000 पूर्ण,
	अणु 0x84, 0x0000 पूर्ण,
	अणु 0x85, 0x0000 पूर्ण,
	अणु 0x86, 0x0004 पूर्ण,
	अणु 0x87, 0x0000 पूर्ण,
	अणु 0x88, 0x0000 पूर्ण,
	अणु 0x89, 0x0000 पूर्ण,
	अणु 0x8a, 0x0123 पूर्ण,
	अणु 0x8b, 0x0000 पूर्ण,
	अणु 0x8c, 0x0003 पूर्ण,
	अणु 0x8d, 0x0000 पूर्ण,
	अणु 0x8e, 0x0004 पूर्ण,
	अणु 0x8f, 0x1100 पूर्ण,
	अणु 0x90, 0x0646 पूर्ण,
	अणु 0x91, 0x0c06 पूर्ण,
	अणु 0x93, 0x0000 पूर्ण,
	अणु 0x94, 0x1270 पूर्ण,
	अणु 0x95, 0x1000 पूर्ण,
	अणु 0x97, 0x0000 पूर्ण,
	अणु 0x98, 0x0000 पूर्ण,
	अणु 0x99, 0x0000 पूर्ण,
	अणु 0x9a, 0x2184 पूर्ण,
	अणु 0x9b, 0x010a पूर्ण,
	अणु 0x9c, 0x0aea पूर्ण,
	अणु 0x9d, 0x000c पूर्ण,
	अणु 0x9e, 0x0400 पूर्ण,
	अणु 0xae, 0x7000 पूर्ण,
	अणु 0xaf, 0x0000 पूर्ण,
	अणु 0xb0, 0x7000 पूर्ण,
	अणु 0xb1, 0x0000 पूर्ण,
	अणु 0xb2, 0x0000 पूर्ण,
	अणु 0xb3, 0x001f पूर्ण,
	अणु 0xb4, 0x220c पूर्ण,
	अणु 0xb5, 0x1f00 पूर्ण,
	अणु 0xb6, 0x0000 पूर्ण,
	अणु 0xb7, 0x0000 पूर्ण,
	अणु 0xbb, 0x0000 पूर्ण,
	अणु 0xbc, 0x0000 पूर्ण,
	अणु 0xbd, 0x0000 पूर्ण,
	अणु 0xbe, 0x0000 पूर्ण,
	अणु 0xbf, 0x0000 पूर्ण,
	अणु 0xc0, 0x0000 पूर्ण,
	अणु 0xc1, 0x0000 पूर्ण,
	अणु 0xc2, 0x0000 पूर्ण,
	अणु 0xcd, 0x0000 पूर्ण,
	अणु 0xce, 0x0000 पूर्ण,
	अणु 0xcf, 0x1813 पूर्ण,
	अणु 0xd0, 0x0690 पूर्ण,
	अणु 0xd1, 0x1c17 पूर्ण,
	अणु 0xd3, 0xa220 पूर्ण,
	अणु 0xd4, 0x0000 पूर्ण,
	अणु 0xd6, 0x0400 पूर्ण,
	अणु 0xd9, 0x0809 पूर्ण,
	अणु 0xda, 0x0000 पूर्ण,
	अणु 0xdb, 0x0001 पूर्ण,
	अणु 0xdc, 0x0049 पूर्ण,
	अणु 0xdd, 0x0024 पूर्ण,
	अणु 0xe6, 0x8000 पूर्ण,
	अणु 0xe7, 0x0000 पूर्ण,
	अणु 0xec, 0xa200 पूर्ण,
	अणु 0xed, 0x0000 पूर्ण,
	अणु 0xee, 0xa200 पूर्ण,
	अणु 0xef, 0x0000 पूर्ण,
	अणु 0xf8, 0x0000 पूर्ण,
	अणु 0xf9, 0x0000 पूर्ण,
	अणु 0xfa, 0x8010 पूर्ण,
	अणु 0xfb, 0x0033 पूर्ण,
	अणु 0xfc, 0x0100 पूर्ण,
पूर्ण;

अटल bool rt5670_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rt5670_ranges); i++) अणु
		अगर ((reg >= rt5670_ranges[i].winकरोw_start &&
		     reg <= rt5670_ranges[i].winकरोw_start +
		     rt5670_ranges[i].winकरोw_len) ||
		    (reg >= rt5670_ranges[i].range_min &&
		     reg <= rt5670_ranges[i].range_max)) अणु
			वापस true;
		पूर्ण
	पूर्ण

	चयन (reg) अणु
	हाल RT5670_RESET:
	हाल RT5670_PDM_DATA_CTRL1:
	हाल RT5670_PDM1_DATA_CTRL4:
	हाल RT5670_PDM2_DATA_CTRL4:
	हाल RT5670_PRIV_DATA:
	हाल RT5670_ASRC_5:
	हाल RT5670_CJ_CTRL1:
	हाल RT5670_CJ_CTRL2:
	हाल RT5670_CJ_CTRL3:
	हाल RT5670_A_JD_CTRL1:
	हाल RT5670_A_JD_CTRL2:
	हाल RT5670_VAD_CTRL5:
	हाल RT5670_ADC_EQ_CTRL1:
	हाल RT5670_EQ_CTRL1:
	हाल RT5670_ALC_CTRL_1:
	हाल RT5670_IRQ_CTRL2:
	हाल RT5670_INT_IRQ_ST:
	हाल RT5670_IL_CMD:
	हाल RT5670_DSP_CTRL1:
	हाल RT5670_DSP_CTRL2:
	हाल RT5670_DSP_CTRL3:
	हाल RT5670_DSP_CTRL4:
	हाल RT5670_DSP_CTRL5:
	हाल RT5670_VENDOR_ID:
	हाल RT5670_VENDOR_ID1:
	हाल RT5670_VENDOR_ID2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt5670_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rt5670_ranges); i++) अणु
		अगर ((reg >= rt5670_ranges[i].winकरोw_start &&
		     reg <= rt5670_ranges[i].winकरोw_start +
		     rt5670_ranges[i].winकरोw_len) ||
		    (reg >= rt5670_ranges[i].range_min &&
		     reg <= rt5670_ranges[i].range_max)) अणु
			वापस true;
		पूर्ण
	पूर्ण

	चयन (reg) अणु
	हाल RT5670_RESET:
	हाल RT5670_HP_VOL:
	हाल RT5670_LOUT1:
	हाल RT5670_CJ_CTRL1:
	हाल RT5670_CJ_CTRL2:
	हाल RT5670_CJ_CTRL3:
	हाल RT5670_IN2:
	हाल RT5670_INL1_INR1_VOL:
	हाल RT5670_DAC1_DIG_VOL:
	हाल RT5670_DAC2_DIG_VOL:
	हाल RT5670_DAC_CTRL:
	हाल RT5670_STO1_ADC_DIG_VOL:
	हाल RT5670_MONO_ADC_DIG_VOL:
	हाल RT5670_STO2_ADC_DIG_VOL:
	हाल RT5670_ADC_BST_VOL1:
	हाल RT5670_ADC_BST_VOL2:
	हाल RT5670_STO2_ADC_MIXER:
	हाल RT5670_STO1_ADC_MIXER:
	हाल RT5670_MONO_ADC_MIXER:
	हाल RT5670_AD_DA_MIXER:
	हाल RT5670_STO_DAC_MIXER:
	हाल RT5670_DD_MIXER:
	हाल RT5670_DIG_MIXER:
	हाल RT5670_DSP_PATH1:
	हाल RT5670_DSP_PATH2:
	हाल RT5670_DIG_INF1_DATA:
	हाल RT5670_DIG_INF2_DATA:
	हाल RT5670_PDM_OUT_CTRL:
	हाल RT5670_PDM_DATA_CTRL1:
	हाल RT5670_PDM1_DATA_CTRL2:
	हाल RT5670_PDM1_DATA_CTRL3:
	हाल RT5670_PDM1_DATA_CTRL4:
	हाल RT5670_PDM2_DATA_CTRL2:
	हाल RT5670_PDM2_DATA_CTRL3:
	हाल RT5670_PDM2_DATA_CTRL4:
	हाल RT5670_REC_L1_MIXER:
	हाल RT5670_REC_L2_MIXER:
	हाल RT5670_REC_R1_MIXER:
	हाल RT5670_REC_R2_MIXER:
	हाल RT5670_HPO_MIXER:
	हाल RT5670_MONO_MIXER:
	हाल RT5670_OUT_L1_MIXER:
	हाल RT5670_OUT_R1_MIXER:
	हाल RT5670_LOUT_MIXER:
	हाल RT5670_PWR_DIG1:
	हाल RT5670_PWR_DIG2:
	हाल RT5670_PWR_ANLG1:
	हाल RT5670_PWR_ANLG2:
	हाल RT5670_PWR_MIXER:
	हाल RT5670_PWR_VOL:
	हाल RT5670_PRIV_INDEX:
	हाल RT5670_PRIV_DATA:
	हाल RT5670_I2S4_SDP:
	हाल RT5670_I2S1_SDP:
	हाल RT5670_I2S2_SDP:
	हाल RT5670_I2S3_SDP:
	हाल RT5670_ADDA_CLK1:
	हाल RT5670_ADDA_CLK2:
	हाल RT5670_DMIC_CTRL1:
	हाल RT5670_DMIC_CTRL2:
	हाल RT5670_TDM_CTRL_1:
	हाल RT5670_TDM_CTRL_2:
	हाल RT5670_TDM_CTRL_3:
	हाल RT5670_DSP_CLK:
	हाल RT5670_GLB_CLK:
	हाल RT5670_PLL_CTRL1:
	हाल RT5670_PLL_CTRL2:
	हाल RT5670_ASRC_1:
	हाल RT5670_ASRC_2:
	हाल RT5670_ASRC_3:
	हाल RT5670_ASRC_4:
	हाल RT5670_ASRC_5:
	हाल RT5670_ASRC_7:
	हाल RT5670_ASRC_8:
	हाल RT5670_ASRC_9:
	हाल RT5670_ASRC_10:
	हाल RT5670_ASRC_11:
	हाल RT5670_ASRC_12:
	हाल RT5670_ASRC_13:
	हाल RT5670_ASRC_14:
	हाल RT5670_DEPOP_M1:
	हाल RT5670_DEPOP_M2:
	हाल RT5670_DEPOP_M3:
	हाल RT5670_CHARGE_PUMP:
	हाल RT5670_MICBIAS:
	हाल RT5670_A_JD_CTRL1:
	हाल RT5670_A_JD_CTRL2:
	हाल RT5670_VAD_CTRL1:
	हाल RT5670_VAD_CTRL2:
	हाल RT5670_VAD_CTRL3:
	हाल RT5670_VAD_CTRL4:
	हाल RT5670_VAD_CTRL5:
	हाल RT5670_ADC_EQ_CTRL1:
	हाल RT5670_ADC_EQ_CTRL2:
	हाल RT5670_EQ_CTRL1:
	हाल RT5670_EQ_CTRL2:
	हाल RT5670_ALC_DRC_CTRL1:
	हाल RT5670_ALC_DRC_CTRL2:
	हाल RT5670_ALC_CTRL_1:
	हाल RT5670_ALC_CTRL_2:
	हाल RT5670_ALC_CTRL_3:
	हाल RT5670_JD_CTRL:
	हाल RT5670_IRQ_CTRL1:
	हाल RT5670_IRQ_CTRL2:
	हाल RT5670_INT_IRQ_ST:
	हाल RT5670_GPIO_CTRL1:
	हाल RT5670_GPIO_CTRL2:
	हाल RT5670_GPIO_CTRL3:
	हाल RT5670_SCRABBLE_FUN:
	हाल RT5670_SCRABBLE_CTRL:
	हाल RT5670_BASE_BACK:
	हाल RT5670_MP3_PLUS1:
	हाल RT5670_MP3_PLUS2:
	हाल RT5670_ADJ_HPF1:
	हाल RT5670_ADJ_HPF2:
	हाल RT5670_HP_CALIB_AMP_DET:
	हाल RT5670_SV_ZCD1:
	हाल RT5670_SV_ZCD2:
	हाल RT5670_IL_CMD:
	हाल RT5670_IL_CMD2:
	हाल RT5670_IL_CMD3:
	हाल RT5670_DRC_HL_CTRL1:
	हाल RT5670_DRC_HL_CTRL2:
	हाल RT5670_ADC_MONO_HP_CTRL1:
	हाल RT5670_ADC_MONO_HP_CTRL2:
	हाल RT5670_ADC_STO2_HP_CTRL1:
	हाल RT5670_ADC_STO2_HP_CTRL2:
	हाल RT5670_JD_CTRL3:
	हाल RT5670_JD_CTRL4:
	हाल RT5670_DIG_MISC:
	हाल RT5670_DSP_CTRL1:
	हाल RT5670_DSP_CTRL2:
	हाल RT5670_DSP_CTRL3:
	हाल RT5670_DSP_CTRL4:
	हाल RT5670_DSP_CTRL5:
	हाल RT5670_GEN_CTRL2:
	हाल RT5670_GEN_CTRL3:
	हाल RT5670_VENDOR_ID:
	हाल RT5670_VENDOR_ID1:
	हाल RT5670_VENDOR_ID2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/**
 * rt5670_headset_detect - Detect headset.
 * @component: SoC audio component device.
 * @jack_insert: Jack insert or not.
 *
 * Detect whether is headset or not when jack inserted.
 *
 * Returns detect status.
 */

अटल पूर्णांक rt5670_headset_detect(काष्ठा snd_soc_component *component, पूर्णांक jack_insert)
अणु
	पूर्णांक val;
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);

	अगर (jack_insert) अणु
		snd_soc_dapm_क्रमce_enable_pin(dapm, "Mic Det Power");
		snd_soc_dapm_sync(dapm);
		snd_soc_component_update_bits(component, RT5670_GEN_CTRL3, 0x4, 0x0);
		snd_soc_component_update_bits(component, RT5670_CJ_CTRL2,
			RT5670_CBJ_DET_MODE | RT5670_CBJ_MN_JD,
			RT5670_CBJ_MN_JD);
		snd_soc_component_ग_लिखो(component, RT5670_GPIO_CTRL2, 0x0004);
		snd_soc_component_update_bits(component, RT5670_GPIO_CTRL1,
			RT5670_GP1_PIN_MASK, RT5670_GP1_PIN_IRQ);
		snd_soc_component_update_bits(component, RT5670_CJ_CTRL1,
			RT5670_CBJ_BST1_EN, RT5670_CBJ_BST1_EN);
		snd_soc_component_ग_लिखो(component, RT5670_JD_CTRL3, 0x00f0);
		snd_soc_component_update_bits(component, RT5670_CJ_CTRL2,
			RT5670_CBJ_MN_JD, RT5670_CBJ_MN_JD);
		snd_soc_component_update_bits(component, RT5670_CJ_CTRL2,
			RT5670_CBJ_MN_JD, 0);
		msleep(300);
		val = snd_soc_component_पढ़ो(component, RT5670_CJ_CTRL3) & 0x7;
		अगर (val == 0x1 || val == 0x2) अणु
			rt5670->jack_type = SND_JACK_HEADSET;
			/* क्रम push button */
			snd_soc_component_update_bits(component, RT5670_INT_IRQ_ST, 0x8, 0x8);
			snd_soc_component_update_bits(component, RT5670_IL_CMD, 0x40, 0x40);
			snd_soc_component_पढ़ो(component, RT5670_IL_CMD);
		पूर्ण अन्यथा अणु
			snd_soc_component_update_bits(component, RT5670_GEN_CTRL3, 0x4, 0x4);
			rt5670->jack_type = SND_JACK_HEADPHONE;
			snd_soc_dapm_disable_pin(dapm, "Mic Det Power");
			snd_soc_dapm_sync(dapm);
		पूर्ण
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component, RT5670_INT_IRQ_ST, 0x8, 0x0);
		snd_soc_component_update_bits(component, RT5670_GEN_CTRL3, 0x4, 0x4);
		rt5670->jack_type = 0;
		snd_soc_dapm_disable_pin(dapm, "Mic Det Power");
		snd_soc_dapm_sync(dapm);
	पूर्ण

	वापस rt5670->jack_type;
पूर्ण

व्योम rt5670_jack_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);

	rt5670->jack_type_saved = rt5670->jack_type;
	rt5670_headset_detect(component, 0);
पूर्ण
EXPORT_SYMBOL_GPL(rt5670_jack_suspend);

व्योम rt5670_jack_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);

	अगर (rt5670->jack_type_saved)
		rt5670_headset_detect(component, 1);
पूर्ण
EXPORT_SYMBOL_GPL(rt5670_jack_resume);

अटल पूर्णांक rt5670_button_detect(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक btn_type, val;

	val = snd_soc_component_पढ़ो(component, RT5670_IL_CMD);
	btn_type = val & 0xff80;
	snd_soc_component_ग_लिखो(component, RT5670_IL_CMD, val);
	अगर (btn_type != 0) अणु
		msleep(20);
		val = snd_soc_component_पढ़ो(component, RT5670_IL_CMD);
		snd_soc_component_ग_लिखो(component, RT5670_IL_CMD, val);
	पूर्ण

	वापस btn_type;
पूर्ण

अटल पूर्णांक rt5670_irq_detection(व्योम *data)
अणु
	काष्ठा rt5670_priv *rt5670 = (काष्ठा rt5670_priv *)data;
	काष्ठा snd_soc_jack_gpio *gpio = &rt5670->hp_gpio;
	काष्ठा snd_soc_jack *jack = rt5670->jack;
	पूर्णांक val, btn_type, report = jack->status;

	अगर (rt5670->jd_mode == 1) /* 2 port */
		val = snd_soc_component_पढ़ो(rt5670->component, RT5670_A_JD_CTRL1) & 0x0070;
	अन्यथा
		val = snd_soc_component_पढ़ो(rt5670->component, RT5670_A_JD_CTRL1) & 0x0020;

	चयन (val) अणु
	/* jack in */
	हाल 0x30: /* 2 port */
	हाल 0x0: /* 1 port or 2 port */
		अगर (rt5670->jack_type == 0) अणु
			report = rt5670_headset_detect(rt5670->component, 1);
			/* क्रम push button and jack out */
			gpio->debounce_समय = 25;
			अवरोध;
		पूर्ण
		btn_type = 0;
		अगर (snd_soc_component_पढ़ो(rt5670->component, RT5670_INT_IRQ_ST) & 0x4) अणु
			/* button pressed */
			report = SND_JACK_HEADSET;
			btn_type = rt5670_button_detect(rt5670->component);
			चयन (btn_type) अणु
			हाल 0x2000: /* up */
				report |= SND_JACK_BTN_1;
				अवरोध;
			हाल 0x0400: /* center */
				report |= SND_JACK_BTN_0;
				अवरोध;
			हाल 0x0080: /* करोwn */
				report |= SND_JACK_BTN_2;
				अवरोध;
			शेष:
				dev_err(rt5670->component->dev,
					"Unexpected button code 0x%04x\n",
					btn_type);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (btn_type == 0)/* button release */
			report =  rt5670->jack_type;

		अवरोध;
	/* jack out */
	हाल 0x70: /* 2 port */
	हाल 0x10: /* 2 port */
	हाल 0x20: /* 1 port */
		report = 0;
		snd_soc_component_update_bits(rt5670->component, RT5670_INT_IRQ_ST, 0x1, 0x0);
		rt5670_headset_detect(rt5670->component, 0);
		gpio->debounce_समय = 150; /* क्रम jack in */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस report;
पूर्ण

पूर्णांक rt5670_set_jack_detect(काष्ठा snd_soc_component *component,
	काष्ठा snd_soc_jack *jack)
अणु
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	rt5670->jack = jack;
	rt5670->hp_gpio.gpiod_dev = component->dev;
	rt5670->hp_gpio.name = "headset";
	rt5670->hp_gpio.report = SND_JACK_HEADSET |
		SND_JACK_BTN_0 | SND_JACK_BTN_1 | SND_JACK_BTN_2;
	rt5670->hp_gpio.debounce_समय = 150;
	rt5670->hp_gpio.wake = true;
	rt5670->hp_gpio.data = (काष्ठा rt5670_priv *)rt5670;
	rt5670->hp_gpio.jack_status_check = rt5670_irq_detection;

	ret = snd_soc_jack_add_gpios(rt5670->jack, 1,
			&rt5670->hp_gpio);
	अगर (ret) अणु
		dev_err(component->dev, "Adding jack GPIO failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt5670_set_jack_detect);

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
अटल स्थिर अक्षर * स्थिर rt5670_data_select[] = अणु
	"Normal", "Swap", "left copy to right", "right copy to left"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_अगर2_dac_क्रमागत, RT5670_DIG_INF1_DATA,
				RT5670_IF2_DAC_SEL_SFT, rt5670_data_select);

अटल SOC_ENUM_SINGLE_DECL(rt5670_अगर2_adc_क्रमागत, RT5670_DIG_INF1_DATA,
				RT5670_IF2_ADC_SEL_SFT, rt5670_data_select);

/*
 * For reliable output-mute LED control we need a "DAC1 Playback Switch" control.
 * We emulate this by only clearing the RT5670_M_DAC1_L/_R AD_DA_MIXER रेजिस्टर
 * bits when both our emulated DAC1 Playback Switch control and the DAC1 MIXL/R
 * DAPM-mixer DAC1 input are enabled.
 */
अटल व्योम rt5670_update_ad_da_mixer_dac1_m_bits(काष्ठा rt5670_priv *rt5670)
अणु
	पूर्णांक val = RT5670_M_DAC1_L | RT5670_M_DAC1_R;

	अगर (rt5670->dac1_mixl_dac1_चयन && rt5670->dac1_playback_चयन_l)
		val &= ~RT5670_M_DAC1_L;

	अगर (rt5670->dac1_mixr_dac1_चयन && rt5670->dac1_playback_चयन_r)
		val &= ~RT5670_M_DAC1_R;

	regmap_update_bits(rt5670->regmap, RT5670_AD_DA_MIXER,
			   RT5670_M_DAC1_L | RT5670_M_DAC1_R, val);
पूर्ण

अटल पूर्णांक rt5670_dac1_playback_चयन_get(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = rt5670->dac1_playback_चयन_l;
	ucontrol->value.पूर्णांकeger.value[1] = rt5670->dac1_playback_चयन_r;

	वापस 0;
पूर्ण

अटल पूर्णांक rt5670_dac1_playback_चयन_put(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);

	अगर (rt5670->dac1_playback_चयन_l == ucontrol->value.पूर्णांकeger.value[0] &&
	    rt5670->dac1_playback_चयन_r == ucontrol->value.पूर्णांकeger.value[1])
		वापस 0;

	rt5670->dac1_playback_चयन_l = ucontrol->value.पूर्णांकeger.value[0];
	rt5670->dac1_playback_चयन_r = ucontrol->value.पूर्णांकeger.value[1];

	rt5670_update_ad_da_mixer_dac1_m_bits(rt5670);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_snd_controls[] = अणु
	/* Headphone Output Volume */
	SOC_DOUBLE_TLV("HP Playback Volume", RT5670_HP_VOL,
		RT5670_L_VOL_SFT, RT5670_R_VOL_SFT,
		39, 1, out_vol_tlv),
	/* OUTPUT Control */
	SOC_DOUBLE_TLV("OUT Playback Volume", RT5670_LOUT1,
		RT5670_L_VOL_SFT, RT5670_R_VOL_SFT, 39, 1, out_vol_tlv),
	/* DAC Digital Volume */
	SOC_DOUBLE("DAC2 Playback Switch", RT5670_DAC_CTRL,
		RT5670_M_DAC_L2_VOL_SFT, RT5670_M_DAC_R2_VOL_SFT, 1, 1),
	SOC_DOUBLE_EXT("DAC1 Playback Switch", SND_SOC_NOPM, 0, 1, 1, 0,
			rt5670_dac1_playback_चयन_get, rt5670_dac1_playback_चयन_put),
	SOC_DOUBLE_TLV("DAC1 Playback Volume", RT5670_DAC1_DIG_VOL,
			RT5670_L_VOL_SFT, RT5670_R_VOL_SFT,
			175, 0, dac_vol_tlv),
	SOC_DOUBLE_TLV("Mono DAC Playback Volume", RT5670_DAC2_DIG_VOL,
			RT5670_L_VOL_SFT, RT5670_R_VOL_SFT,
			175, 0, dac_vol_tlv),
	/* IN1/IN2 Control */
	SOC_SINGLE_TLV("IN1 Boost Volume", RT5670_CJ_CTRL1,
		RT5670_BST_SFT1, 8, 0, bst_tlv),
	SOC_SINGLE_TLV("IN2 Boost Volume", RT5670_IN2,
		RT5670_BST_SFT1, 8, 0, bst_tlv),
	/* INL/INR Volume Control */
	SOC_DOUBLE_TLV("IN Capture Volume", RT5670_INL1_INR1_VOL,
			RT5670_INL_VOL_SFT, RT5670_INR_VOL_SFT,
			31, 1, in_vol_tlv),
	/* ADC Digital Volume Control */
	SOC_DOUBLE("ADC Capture Switch", RT5670_STO1_ADC_DIG_VOL,
		RT5670_L_MUTE_SFT, RT5670_R_MUTE_SFT, 1, 1),
	SOC_DOUBLE_TLV("ADC Capture Volume", RT5670_STO1_ADC_DIG_VOL,
			RT5670_L_VOL_SFT, RT5670_R_VOL_SFT,
			127, 0, adc_vol_tlv),

	SOC_DOUBLE_TLV("Mono ADC Capture Volume", RT5670_MONO_ADC_DIG_VOL,
			RT5670_L_VOL_SFT, RT5670_R_VOL_SFT,
			127, 0, adc_vol_tlv),

	/* ADC Boost Volume Control */
	SOC_DOUBLE_TLV("STO1 ADC Boost Gain Volume", RT5670_ADC_BST_VOL1,
			RT5670_STO1_ADC_L_BST_SFT, RT5670_STO1_ADC_R_BST_SFT,
			3, 0, adc_bst_tlv),

	SOC_DOUBLE_TLV("STO2 ADC Boost Gain Volume", RT5670_ADC_BST_VOL1,
			RT5670_STO2_ADC_L_BST_SFT, RT5670_STO2_ADC_R_BST_SFT,
			3, 0, adc_bst_tlv),

	SOC_ENUM("ADC IF2 Data Switch", rt5670_अगर2_adc_क्रमागत),
	SOC_ENUM("DAC IF2 Data Switch", rt5670_अगर2_dac_क्रमागत),
पूर्ण;

/**
 * set_dmic_clk - Set parameter of dmic.
 *
 * @w: DAPM widget.
 * @kcontrol: The kcontrol of this widget.
 * @event: Event id.
 *
 * Choose dmic घड़ी between 1MHz and 3MHz.
 * It is better क्रम घड़ी to approximate 3MHz.
 */
अटल पूर्णांक set_dmic_clk(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);
	पूर्णांक idx, rate;

	rate = rt5670->sysclk / rl6231_get_pre_भाग(rt5670->regmap,
		RT5670_ADDA_CLK1, RT5670_I2S_PD1_SFT);
	idx = rl6231_calc_dmic_clk(rate);
	अगर (idx < 0)
		dev_err(component->dev, "Failed to set DMIC clock\n");
	अन्यथा
		snd_soc_component_update_bits(component, RT5670_DMIC_CTRL1,
			RT5670_DMIC_CLK_MASK, idx << RT5670_DMIC_CLK_SFT);
	वापस idx;
पूर्ण

अटल पूर्णांक is_sys_clk_from_pll(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);

	अगर (rt5670->sysclk_src == RT5670_SCLK_S_PLL1)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक is_using_asrc(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	अचिन्हित पूर्णांक reg, shअगरt, val;

	चयन (source->shअगरt) अणु
	हाल 0:
		reg = RT5670_ASRC_3;
		shअगरt = 0;
		अवरोध;
	हाल 1:
		reg = RT5670_ASRC_3;
		shअगरt = 4;
		अवरोध;
	हाल 2:
		reg = RT5670_ASRC_5;
		shअगरt = 12;
		अवरोध;
	हाल 3:
		reg = RT5670_ASRC_2;
		shअगरt = 0;
		अवरोध;
	हाल 8:
		reg = RT5670_ASRC_2;
		shअगरt = 4;
		अवरोध;
	हाल 9:
		reg = RT5670_ASRC_2;
		shअगरt = 8;
		अवरोध;
	हाल 10:
		reg = RT5670_ASRC_2;
		shअगरt = 12;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	val = (snd_soc_component_पढ़ो(component, reg) >> shअगरt) & 0xf;
	चयन (val) अणु
	हाल 1:
	हाल 2:
	हाल 3:
	हाल 4:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण

पूर्ण

अटल पूर्णांक can_use_asrc(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);

	अगर (rt5670->sysclk > rt5670->lrck[RT5670_AIF1] * 384)
		वापस 1;

	वापस 0;
पूर्ण


/**
 * rt5670_sel_asrc_clk_src - select ASRC घड़ी source क्रम a set of filters
 * @component: SoC audio component device.
 * @filter_mask: mask of filters.
 * @clk_src: घड़ी source
 *
 * The ASRC function is क्रम asynchronous MCLK and LRCK. Also, since RT5670 can
 * only support standard 32fs or 64fs i2s क्रमmat, ASRC should be enabled to
 * support special i2s घड़ी क्रमmat such as Intel's 100fs(100 * sampling rate).
 * ASRC function will track i2s घड़ी and generate a corresponding प्रणाली घड़ी
 * क्रम codec. This function provides an API to select the घड़ी source क्रम a
 * set of filters specअगरied by the mask. And the codec driver will turn on ASRC
 * क्रम these filters अगर ASRC is selected as their घड़ी source.
 */
पूर्णांक rt5670_sel_asrc_clk_src(काष्ठा snd_soc_component *component,
			    अचिन्हित पूर्णांक filter_mask, अचिन्हित पूर्णांक clk_src)
अणु
	अचिन्हित पूर्णांक asrc2_mask = 0, asrc2_value = 0;
	अचिन्हित पूर्णांक asrc3_mask = 0, asrc3_value = 0;

	अगर (clk_src > RT5670_CLK_SEL_SYS3)
		वापस -EINVAL;

	अगर (filter_mask & RT5670_DA_STEREO_FILTER) अणु
		asrc2_mask |= RT5670_DA_STO_CLK_SEL_MASK;
		asrc2_value = (asrc2_value & ~RT5670_DA_STO_CLK_SEL_MASK)
				| (clk_src <<  RT5670_DA_STO_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5670_DA_MONO_L_FILTER) अणु
		asrc2_mask |= RT5670_DA_MONOL_CLK_SEL_MASK;
		asrc2_value = (asrc2_value & ~RT5670_DA_MONOL_CLK_SEL_MASK)
				| (clk_src <<  RT5670_DA_MONOL_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5670_DA_MONO_R_FILTER) अणु
		asrc2_mask |= RT5670_DA_MONOR_CLK_SEL_MASK;
		asrc2_value = (asrc2_value & ~RT5670_DA_MONOR_CLK_SEL_MASK)
				| (clk_src <<  RT5670_DA_MONOR_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5670_AD_STEREO_FILTER) अणु
		asrc2_mask |= RT5670_AD_STO1_CLK_SEL_MASK;
		asrc2_value = (asrc2_value & ~RT5670_AD_STO1_CLK_SEL_MASK)
				| (clk_src <<  RT5670_AD_STO1_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5670_AD_MONO_L_FILTER) अणु
		asrc3_mask |= RT5670_AD_MONOL_CLK_SEL_MASK;
		asrc3_value = (asrc3_value & ~RT5670_AD_MONOL_CLK_SEL_MASK)
				| (clk_src <<  RT5670_AD_MONOL_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5670_AD_MONO_R_FILTER)  अणु
		asrc3_mask |= RT5670_AD_MONOR_CLK_SEL_MASK;
		asrc3_value = (asrc3_value & ~RT5670_AD_MONOR_CLK_SEL_MASK)
				| (clk_src <<  RT5670_AD_MONOR_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5670_UP_RATE_FILTER) अणु
		asrc3_mask |= RT5670_UP_CLK_SEL_MASK;
		asrc3_value = (asrc3_value & ~RT5670_UP_CLK_SEL_MASK)
				| (clk_src <<  RT5670_UP_CLK_SEL_SFT);
	पूर्ण

	अगर (filter_mask & RT5670_DOWN_RATE_FILTER) अणु
		asrc3_mask |= RT5670_DOWN_CLK_SEL_MASK;
		asrc3_value = (asrc3_value & ~RT5670_DOWN_CLK_SEL_MASK)
				| (clk_src <<  RT5670_DOWN_CLK_SEL_SFT);
	पूर्ण

	अगर (asrc2_mask)
		snd_soc_component_update_bits(component, RT5670_ASRC_2,
				    asrc2_mask, asrc2_value);

	अगर (asrc3_mask)
		snd_soc_component_update_bits(component, RT5670_ASRC_3,
				    asrc3_mask, asrc3_value);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt5670_sel_asrc_clk_src);

/* Digital Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt5670_sto1_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5670_STO1_ADC_MIXER,
			RT5670_M_ADC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5670_STO1_ADC_MIXER,
			RT5670_M_ADC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_sto1_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5670_STO1_ADC_MIXER,
			RT5670_M_ADC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5670_STO1_ADC_MIXER,
			RT5670_M_ADC_R2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_sto2_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5670_STO2_ADC_MIXER,
			RT5670_M_ADC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5670_STO2_ADC_MIXER,
			RT5670_M_ADC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_sto2_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5670_STO2_ADC_MIXER,
			RT5670_M_ADC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5670_STO2_ADC_MIXER,
			RT5670_M_ADC_R2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_mono_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5670_MONO_ADC_MIXER,
			RT5670_M_MONO_ADC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5670_MONO_ADC_MIXER,
			RT5670_M_MONO_ADC_L2_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_mono_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("ADC1 Switch", RT5670_MONO_ADC_MIXER,
			RT5670_M_MONO_ADC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("ADC2 Switch", RT5670_MONO_ADC_MIXER,
			RT5670_M_MONO_ADC_R2_SFT, 1, 1),
पूर्ण;

/* See comment above rt5670_update_ad_da_mixer_dac1_m_bits() */
अटल पूर्णांक rt5670_put_dac1_mix_dac1_चयन(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_mixer_control *mc = (काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	अगर (mc->shअगरt == 0)
		rt5670->dac1_mixl_dac1_चयन = ucontrol->value.पूर्णांकeger.value[0];
	अन्यथा
		rt5670->dac1_mixr_dac1_चयन = ucontrol->value.पूर्णांकeger.value[0];

	/* Apply the update (अगर any) */
	ret = snd_soc_dapm_put_volsw(kcontrol, ucontrol);
	अगर (ret == 0)
		वापस 0;

	rt5670_update_ad_da_mixer_dac1_m_bits(rt5670);

	वापस 1;
पूर्ण

#घोषणा SOC_DAPM_SINGLE_RT5670_DAC1_SW(name, shअगरt) \
	SOC_SINGLE_EXT(name, SND_SOC_NOPM, shअगरt, 1, 0, \
		       snd_soc_dapm_get_volsw, rt5670_put_dac1_mix_dac1_चयन)

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("Stereo ADC Switch", RT5670_AD_DA_MIXER,
			RT5670_M_ADCMIX_L_SFT, 1, 1),
	SOC_DAPM_SINGLE_RT5670_DAC1_SW("DAC1 Switch", 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("Stereo ADC Switch", RT5670_AD_DA_MIXER,
			RT5670_M_ADCMIX_R_SFT, 1, 1),
	SOC_DAPM_SINGLE_RT5670_DAC1_SW("DAC1 Switch", 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_sto_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5670_STO_DAC_MIXER,
			RT5670_M_DAC_L1_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5670_STO_DAC_MIXER,
			RT5670_M_DAC_L2_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5670_STO_DAC_MIXER,
			RT5670_M_DAC_R1_STO_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_sto_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5670_STO_DAC_MIXER,
			RT5670_M_DAC_R1_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5670_STO_DAC_MIXER,
			RT5670_M_DAC_R2_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5670_STO_DAC_MIXER,
			RT5670_M_DAC_L1_STO_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_mono_dac_l_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5670_DD_MIXER,
			RT5670_M_DAC_L1_MONO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5670_DD_MIXER,
			RT5670_M_DAC_L2_MONO_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5670_DD_MIXER,
			RT5670_M_DAC_R2_MONO_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_mono_dac_r_mix[] = अणु
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5670_DD_MIXER,
			RT5670_M_DAC_R1_MONO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5670_DD_MIXER,
			RT5670_M_DAC_R2_MONO_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5670_DD_MIXER,
			RT5670_M_DAC_L2_MONO_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_dig_l_mix[] = अणु
	SOC_DAPM_SINGLE("Sto DAC Mix L Switch", RT5670_DIG_MIXER,
			RT5670_M_STO_L_DAC_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5670_DIG_MIXER,
			RT5670_M_DAC_L2_DAC_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5670_DIG_MIXER,
			RT5670_M_DAC_R2_DAC_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_dig_r_mix[] = अणु
	SOC_DAPM_SINGLE("Sto DAC Mix R Switch", RT5670_DIG_MIXER,
			RT5670_M_STO_R_DAC_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5670_DIG_MIXER,
			RT5670_M_DAC_R2_DAC_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5670_DIG_MIXER,
			RT5670_M_DAC_L2_DAC_R_SFT, 1, 1),
पूर्ण;

/* Analog Input Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt5670_rec_l_mix[] = अणु
	SOC_DAPM_SINGLE("INL Switch", RT5670_REC_L2_MIXER,
			RT5670_M_IN_L_RM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5670_REC_L2_MIXER,
			RT5670_M_BST2_RM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5670_REC_L2_MIXER,
			RT5670_M_BST1_RM_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_rec_r_mix[] = अणु
	SOC_DAPM_SINGLE("INR Switch", RT5670_REC_R2_MIXER,
			RT5670_M_IN_R_RM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST2 Switch", RT5670_REC_R2_MIXER,
			RT5670_M_BST2_RM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("BST1 Switch", RT5670_REC_R2_MIXER,
			RT5670_M_BST1_RM_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_out_l_mix[] = अणु
	SOC_DAPM_SINGLE("BST1 Switch", RT5670_OUT_L1_MIXER,
			RT5670_M_BST1_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("INL Switch", RT5670_OUT_L1_MIXER,
			RT5670_M_IN_L_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L2 Switch", RT5670_OUT_L1_MIXER,
			RT5670_M_DAC_L2_OM_L_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5670_OUT_L1_MIXER,
			RT5670_M_DAC_L1_OM_L_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_out_r_mix[] = अणु
	SOC_DAPM_SINGLE("BST2 Switch", RT5670_OUT_R1_MIXER,
			RT5670_M_BST2_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("INR Switch", RT5670_OUT_R1_MIXER,
			RT5670_M_IN_R_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R2 Switch", RT5670_OUT_R1_MIXER,
			RT5670_M_DAC_R2_OM_R_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5670_OUT_R1_MIXER,
			RT5670_M_DAC_R1_OM_R_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_hpo_mix[] = अणु
	SOC_DAPM_SINGLE("DAC1 Switch", RT5670_HPO_MIXER,
			RT5670_M_DAC1_HM_SFT, 1, 1),
	SOC_DAPM_SINGLE("HPVOL Switch", RT5670_HPO_MIXER,
			RT5670_M_HPVOL_HM_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_hpvoll_mix[] = अणु
	SOC_DAPM_SINGLE("DAC1 Switch", RT5670_HPO_MIXER,
			RT5670_M_DACL1_HML_SFT, 1, 1),
	SOC_DAPM_SINGLE("INL Switch", RT5670_HPO_MIXER,
			RT5670_M_INL1_HML_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_hpvolr_mix[] = अणु
	SOC_DAPM_SINGLE("DAC1 Switch", RT5670_HPO_MIXER,
			RT5670_M_DACR1_HMR_SFT, 1, 1),
	SOC_DAPM_SINGLE("INR Switch", RT5670_HPO_MIXER,
			RT5670_M_INR1_HMR_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_lout_mix[] = अणु
	SOC_DAPM_SINGLE("DAC L1 Switch", RT5670_LOUT_MIXER,
			RT5670_M_DAC_L1_LM_SFT, 1, 1),
	SOC_DAPM_SINGLE("DAC R1 Switch", RT5670_LOUT_MIXER,
			RT5670_M_DAC_R1_LM_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUTMIX L Switch", RT5670_LOUT_MIXER,
			RT5670_M_OV_L_LM_SFT, 1, 1),
	SOC_DAPM_SINGLE("OUTMIX R Switch", RT5670_LOUT_MIXER,
			RT5670_M_OV_R_LM_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lout_l_enable_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT5670_LOUT1,
		RT5670_L_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new lout_r_enable_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT5670_LOUT1,
		RT5670_R_MUTE_SFT, 1, 1);

/* DAC1 L/R source */ /* MX-29 [9:8] [11:10] */
अटल स्थिर अक्षर * स्थिर rt5670_dac1_src[] = अणु
	"IF1 DAC", "IF2 DAC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_dac1l_क्रमागत, RT5670_AD_DA_MIXER,
	RT5670_DAC1_L_SEL_SFT, rt5670_dac1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_dac1l_mux =
	SOC_DAPM_ENUM("DAC1 L source", rt5670_dac1l_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(rt5670_dac1r_क्रमागत, RT5670_AD_DA_MIXER,
	RT5670_DAC1_R_SEL_SFT, rt5670_dac1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_dac1r_mux =
	SOC_DAPM_ENUM("DAC1 R source", rt5670_dac1r_क्रमागत);

/*DAC2 L/R source*/ /* MX-1B [6:4] [2:0] */
/* TODO Use SOC_VALUE_ENUM_SINGLE_DECL */
अटल स्थिर अक्षर * स्थिर rt5670_dac12_src[] = अणु
	"IF1 DAC", "IF2 DAC", "IF3 DAC", "TxDC DAC",
	"Bass", "VAD_ADC", "IF4 DAC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_dac2l_क्रमागत, RT5670_DAC_CTRL,
	RT5670_DAC2_L_SEL_SFT, rt5670_dac12_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_dac_l2_mux =
	SOC_DAPM_ENUM("DAC2 L source", rt5670_dac2l_क्रमागत);

अटल स्थिर अक्षर * स्थिर rt5670_dacr2_src[] = अणु
	"IF1 DAC", "IF2 DAC", "IF3 DAC", "TxDC DAC", "TxDP ADC", "IF4 DAC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_dac2r_क्रमागत, RT5670_DAC_CTRL,
	RT5670_DAC2_R_SEL_SFT, rt5670_dacr2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_dac_r2_mux =
	SOC_DAPM_ENUM("DAC2 R source", rt5670_dac2r_क्रमागत);

/*RxDP source*/ /* MX-2D [15:13] */
अटल स्थिर अक्षर * स्थिर rt5670_rxdp_src[] = अणु
	"IF2 DAC", "IF1 DAC", "STO1 ADC Mixer", "STO2 ADC Mixer",
	"Mono ADC Mixer L", "Mono ADC Mixer R", "DAC1"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_rxdp_क्रमागत, RT5670_DSP_PATH1,
	RT5670_RXDP_SEL_SFT, rt5670_rxdp_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_rxdp_mux =
	SOC_DAPM_ENUM("DAC2 L source", rt5670_rxdp_क्रमागत);

/* MX-2D [1] [0] */
अटल स्थिर अक्षर * स्थिर rt5670_dsp_bypass_src[] = अणु
	"DSP", "Bypass"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_dsp_ul_क्रमागत, RT5670_DSP_PATH1,
	RT5670_DSP_UL_SFT, rt5670_dsp_bypass_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_dsp_ul_mux =
	SOC_DAPM_ENUM("DSP UL source", rt5670_dsp_ul_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(rt5670_dsp_dl_क्रमागत, RT5670_DSP_PATH1,
	RT5670_DSP_DL_SFT, rt5670_dsp_bypass_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_dsp_dl_mux =
	SOC_DAPM_ENUM("DSP DL source", rt5670_dsp_dl_क्रमागत);

/* Stereo2 ADC source */
/* MX-26 [15] */
अटल स्थिर अक्षर * स्थिर rt5670_stereo2_adc_lr_src[] = अणु
	"L", "LR"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_stereo2_adc_lr_क्रमागत, RT5670_STO2_ADC_MIXER,
	RT5670_STO2_ADC_SRC_SFT, rt5670_stereo2_adc_lr_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_sto2_adc_lr_mux =
	SOC_DAPM_ENUM("Stereo2 ADC LR source", rt5670_stereo2_adc_lr_क्रमागत);

/* Stereo1 ADC source */
/* MX-27 MX-26 [12] */
अटल स्थिर अक्षर * स्थिर rt5670_stereo_adc1_src[] = अणु
	"DAC MIX", "ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_stereo1_adc1_क्रमागत, RT5670_STO1_ADC_MIXER,
	RT5670_ADC_1_SRC_SFT, rt5670_stereo_adc1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_sto_adc_1_mux =
	SOC_DAPM_ENUM("Stereo1 ADC 1 Mux", rt5670_stereo1_adc1_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(rt5670_stereo2_adc1_क्रमागत, RT5670_STO2_ADC_MIXER,
	RT5670_ADC_1_SRC_SFT, rt5670_stereo_adc1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_sto2_adc_1_mux =
	SOC_DAPM_ENUM("Stereo2 ADC 1 Mux", rt5670_stereo2_adc1_क्रमागत);


/* MX-27 MX-26 [11] */
अटल स्थिर अक्षर * स्थिर rt5670_stereo_adc2_src[] = अणु
	"DAC MIX", "DMIC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_stereo1_adc2_क्रमागत, RT5670_STO1_ADC_MIXER,
	RT5670_ADC_2_SRC_SFT, rt5670_stereo_adc2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_sto_adc_2_mux =
	SOC_DAPM_ENUM("Stereo1 ADC 2 Mux", rt5670_stereo1_adc2_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(rt5670_stereo2_adc2_क्रमागत, RT5670_STO2_ADC_MIXER,
	RT5670_ADC_2_SRC_SFT, rt5670_stereo_adc2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_sto2_adc_2_mux =
	SOC_DAPM_ENUM("Stereo2 ADC 2 Mux", rt5670_stereo2_adc2_क्रमागत);

/* MX-27 MX-26 [9:8] */
अटल स्थिर अक्षर * स्थिर rt5670_stereo_dmic_src[] = अणु
	"DMIC1", "DMIC2", "DMIC3"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_stereo1_dmic_क्रमागत, RT5670_STO1_ADC_MIXER,
	RT5670_DMIC_SRC_SFT, rt5670_stereo_dmic_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_sto1_dmic_mux =
	SOC_DAPM_ENUM("Stereo1 DMIC source", rt5670_stereo1_dmic_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(rt5670_stereo2_dmic_क्रमागत, RT5670_STO2_ADC_MIXER,
	RT5670_DMIC_SRC_SFT, rt5670_stereo_dmic_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_sto2_dmic_mux =
	SOC_DAPM_ENUM("Stereo2 DMIC source", rt5670_stereo2_dmic_क्रमागत);

/* Mono ADC source */
/* MX-28 [12] */
अटल स्थिर अक्षर * स्थिर rt5670_mono_adc_l1_src[] = अणु
	"Mono DAC MIXL", "ADC1"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_mono_adc_l1_क्रमागत, RT5670_MONO_ADC_MIXER,
	RT5670_MONO_ADC_L1_SRC_SFT, rt5670_mono_adc_l1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_mono_adc_l1_mux =
	SOC_DAPM_ENUM("Mono ADC1 left source", rt5670_mono_adc_l1_क्रमागत);
/* MX-28 [11] */
अटल स्थिर अक्षर * स्थिर rt5670_mono_adc_l2_src[] = अणु
	"Mono DAC MIXL", "DMIC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_mono_adc_l2_क्रमागत, RT5670_MONO_ADC_MIXER,
	RT5670_MONO_ADC_L2_SRC_SFT, rt5670_mono_adc_l2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_mono_adc_l2_mux =
	SOC_DAPM_ENUM("Mono ADC2 left source", rt5670_mono_adc_l2_क्रमागत);

/* MX-28 [9:8] */
अटल स्थिर अक्षर * स्थिर rt5670_mono_dmic_src[] = अणु
	"DMIC1", "DMIC2", "DMIC3"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_mono_dmic_l_क्रमागत, RT5670_MONO_ADC_MIXER,
	RT5670_MONO_DMIC_L_SRC_SFT, rt5670_mono_dmic_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_mono_dmic_l_mux =
	SOC_DAPM_ENUM("Mono DMIC left source", rt5670_mono_dmic_l_क्रमागत);
/* MX-28 [1:0] */
अटल SOC_ENUM_SINGLE_DECL(rt5670_mono_dmic_r_क्रमागत, RT5670_MONO_ADC_MIXER,
	RT5670_MONO_DMIC_R_SRC_SFT, rt5670_mono_dmic_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_mono_dmic_r_mux =
	SOC_DAPM_ENUM("Mono DMIC Right source", rt5670_mono_dmic_r_क्रमागत);
/* MX-28 [4] */
अटल स्थिर अक्षर * स्थिर rt5670_mono_adc_r1_src[] = अणु
	"Mono DAC MIXR", "ADC2"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_mono_adc_r1_क्रमागत, RT5670_MONO_ADC_MIXER,
	RT5670_MONO_ADC_R1_SRC_SFT, rt5670_mono_adc_r1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_mono_adc_r1_mux =
	SOC_DAPM_ENUM("Mono ADC1 right source", rt5670_mono_adc_r1_क्रमागत);
/* MX-28 [3] */
अटल स्थिर अक्षर * स्थिर rt5670_mono_adc_r2_src[] = अणु
	"Mono DAC MIXR", "DMIC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_mono_adc_r2_क्रमागत, RT5670_MONO_ADC_MIXER,
	RT5670_MONO_ADC_R2_SRC_SFT, rt5670_mono_adc_r2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_mono_adc_r2_mux =
	SOC_DAPM_ENUM("Mono ADC2 right source", rt5670_mono_adc_r2_क्रमागत);

/* MX-2D [3:2] */
अटल स्थिर अक्षर * स्थिर rt5670_txdp_slot_src[] = अणु
	"Slot 0-1", "Slot 2-3", "Slot 4-5", "Slot 6-7"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_txdp_slot_क्रमागत, RT5670_DSP_PATH1,
	RT5670_TXDP_SLOT_SEL_SFT, rt5670_txdp_slot_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_txdp_slot_mux =
	SOC_DAPM_ENUM("TxDP Slot source", rt5670_txdp_slot_क्रमागत);

/* MX-2F [15] */
अटल स्थिर अक्षर * स्थिर rt5670_अगर1_adc2_in_src[] = अणु
	"IF_ADC2", "VAD_ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_अगर1_adc2_in_क्रमागत, RT5670_DIG_INF1_DATA,
	RT5670_IF1_ADC2_IN_SFT, rt5670_अगर1_adc2_in_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_अगर1_adc2_in_mux =
	SOC_DAPM_ENUM("IF1 ADC2 IN source", rt5670_अगर1_adc2_in_क्रमागत);

/* MX-2F [14:12] */
अटल स्थिर अक्षर * स्थिर rt5670_अगर2_adc_in_src[] = अणु
	"IF_ADC1", "IF_ADC2", "IF_ADC3", "TxDC_DAC", "TxDP_ADC", "VAD_ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_अगर2_adc_in_क्रमागत, RT5670_DIG_INF1_DATA,
	RT5670_IF2_ADC_IN_SFT, rt5670_अगर2_adc_in_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_अगर2_adc_in_mux =
	SOC_DAPM_ENUM("IF2 ADC IN source", rt5670_अगर2_adc_in_क्रमागत);

/* MX-31 [15] [13] [11] [9] */
अटल स्थिर अक्षर * स्थिर rt5670_pdm_src[] = अणु
	"Mono DAC", "Stereo DAC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_pdm1_l_क्रमागत, RT5670_PDM_OUT_CTRL,
	RT5670_PDM1_L_SFT, rt5670_pdm_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_pdm1_l_mux =
	SOC_DAPM_ENUM("PDM1 L source", rt5670_pdm1_l_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(rt5670_pdm1_r_क्रमागत, RT5670_PDM_OUT_CTRL,
	RT5670_PDM1_R_SFT, rt5670_pdm_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_pdm1_r_mux =
	SOC_DAPM_ENUM("PDM1 R source", rt5670_pdm1_r_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(rt5670_pdm2_l_क्रमागत, RT5670_PDM_OUT_CTRL,
	RT5670_PDM2_L_SFT, rt5670_pdm_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_pdm2_l_mux =
	SOC_DAPM_ENUM("PDM2 L source", rt5670_pdm2_l_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(rt5670_pdm2_r_क्रमागत, RT5670_PDM_OUT_CTRL,
	RT5670_PDM2_R_SFT, rt5670_pdm_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_pdm2_r_mux =
	SOC_DAPM_ENUM("PDM2 R source", rt5670_pdm2_r_क्रमागत);

/* MX-FA [12] */
अटल स्थिर अक्षर * स्थिर rt5670_अगर1_adc1_in1_src[] = अणु
	"IF_ADC1", "IF1_ADC3"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_अगर1_adc1_in1_क्रमागत, RT5670_DIG_MISC,
	RT5670_IF1_ADC1_IN1_SFT, rt5670_अगर1_adc1_in1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_अगर1_adc1_in1_mux =
	SOC_DAPM_ENUM("IF1 ADC1 IN1 source", rt5670_अगर1_adc1_in1_क्रमागत);

/* MX-FA [11] */
अटल स्थिर अक्षर * स्थिर rt5670_अगर1_adc1_in2_src[] = अणु
	"IF1_ADC1_IN1", "IF1_ADC4"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_अगर1_adc1_in2_क्रमागत, RT5670_DIG_MISC,
	RT5670_IF1_ADC1_IN2_SFT, rt5670_अगर1_adc1_in2_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_अगर1_adc1_in2_mux =
	SOC_DAPM_ENUM("IF1 ADC1 IN2 source", rt5670_अगर1_adc1_in2_क्रमागत);

/* MX-FA [10] */
अटल स्थिर अक्षर * स्थिर rt5670_अगर1_adc2_in1_src[] = अणु
	"IF1_ADC2_IN", "IF1_ADC4"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_अगर1_adc2_in1_क्रमागत, RT5670_DIG_MISC,
	RT5670_IF1_ADC2_IN1_SFT, rt5670_अगर1_adc2_in1_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_अगर1_adc2_in1_mux =
	SOC_DAPM_ENUM("IF1 ADC2 IN1 source", rt5670_अगर1_adc2_in1_क्रमागत);

/* MX-9D [9:8] */
अटल स्थिर अक्षर * स्थिर rt5670_vad_adc_src[] = अणु
	"Sto1 ADC L", "Mono ADC L", "Mono ADC R", "Sto2 ADC L"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt5670_vad_adc_क्रमागत, RT5670_VAD_CTRL4,
	RT5670_VAD_SEL_SFT, rt5670_vad_adc_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5670_vad_adc_mux =
	SOC_DAPM_ENUM("VAD ADC source", rt5670_vad_adc_क्रमागत);

अटल पूर्णांक rt5670_hp_घातer_event(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_update_bits(rt5670->regmap, RT5670_CHARGE_PUMP,
			RT5670_PM_HP_MASK, RT5670_PM_HP_HV);
		regmap_update_bits(rt5670->regmap, RT5670_GEN_CTRL2,
			0x0400, 0x0400);
		/* headphone amp घातer on */
		regmap_update_bits(rt5670->regmap, RT5670_PWR_ANLG1,
			RT5670_PWR_HA |	RT5670_PWR_FV1 |
			RT5670_PWR_FV2,	RT5670_PWR_HA |
			RT5670_PWR_FV1 | RT5670_PWR_FV2);
		/* depop parameters */
		regmap_ग_लिखो(rt5670->regmap, RT5670_DEPOP_M2, 0x3100);
		regmap_ग_लिखो(rt5670->regmap, RT5670_DEPOP_M1, 0x8009);
		regmap_ग_लिखो(rt5670->regmap, RT5670_PR_BASE +
			RT5670_HP_DCC_INT1, 0x9f00);
		mdelay(20);
		regmap_ग_लिखो(rt5670->regmap, RT5670_DEPOP_M1, 0x8019);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_ग_लिखो(rt5670->regmap, RT5670_DEPOP_M1, 0x0004);
		msleep(30);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5670_hp_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* headphone unmute sequence */
		regmap_ग_लिखो(rt5670->regmap, RT5670_PR_BASE +
				RT5670_MAMP_INT_REG2, 0xb400);
		regmap_ग_लिखो(rt5670->regmap, RT5670_DEPOP_M3, 0x0772);
		regmap_ग_लिखो(rt5670->regmap, RT5670_DEPOP_M1, 0x805d);
		regmap_ग_लिखो(rt5670->regmap, RT5670_DEPOP_M1, 0x831d);
		regmap_update_bits(rt5670->regmap, RT5670_GEN_CTRL2,
				0x0300, 0x0300);
		regmap_update_bits(rt5670->regmap, RT5670_HP_VOL,
			RT5670_L_MUTE | RT5670_R_MUTE, 0);
		msleep(80);
		regmap_ग_लिखो(rt5670->regmap, RT5670_DEPOP_M1, 0x8019);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		/* headphone mute sequence */
		regmap_ग_लिखो(rt5670->regmap, RT5670_PR_BASE +
				RT5670_MAMP_INT_REG2, 0xb400);
		regmap_ग_लिखो(rt5670->regmap, RT5670_DEPOP_M3, 0x0772);
		regmap_ग_लिखो(rt5670->regmap, RT5670_DEPOP_M1, 0x803d);
		mdelay(10);
		regmap_ग_लिखो(rt5670->regmap, RT5670_DEPOP_M1, 0x831d);
		mdelay(10);
		regmap_update_bits(rt5670->regmap, RT5670_HP_VOL,
				   RT5670_L_MUTE | RT5670_R_MUTE,
				   RT5670_L_MUTE | RT5670_R_MUTE);
		msleep(20);
		regmap_update_bits(rt5670->regmap,
				   RT5670_GEN_CTRL2, 0x0300, 0x0);
		regmap_ग_लिखो(rt5670->regmap, RT5670_DEPOP_M1, 0x8019);
		regmap_ग_लिखो(rt5670->regmap, RT5670_DEPOP_M3, 0x0707);
		regmap_ग_लिखो(rt5670->regmap, RT5670_PR_BASE +
				RT5670_MAMP_INT_REG2, 0xfc00);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5670_spk_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);

	अगर (!rt5670->gpio1_is_ext_spk_en)
		वापस 0;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_update_bits(rt5670->regmap, RT5670_GPIO_CTRL2,
				   RT5670_GP1_OUT_MASK, RT5670_GP1_OUT_HI);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_update_bits(rt5670->regmap, RT5670_GPIO_CTRL2,
				   RT5670_GP1_OUT_MASK, RT5670_GP1_OUT_LO);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5670_bst1_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, RT5670_PWR_ANLG2,
				    RT5670_PWR_BST1_P, RT5670_PWR_BST1_P);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT5670_PWR_ANLG2,
				    RT5670_PWR_BST1_P, 0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5670_bst2_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, RT5670_PWR_ANLG2,
				    RT5670_PWR_BST2_P, RT5670_PWR_BST2_P);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT5670_PWR_ANLG2,
				    RT5670_PWR_BST2_P, 0);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget rt5670_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("PLL1", RT5670_PWR_ANLG2,
			    RT5670_PWR_PLL_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("I2S DSP", RT5670_PWR_DIG2,
			    RT5670_PWR_I2S_DSP_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Mic Det Power", RT5670_PWR_VOL,
			    RT5670_PWR_MIC_DET_BIT, 0, शून्य, 0),

	/* ASRC */
	SND_SOC_DAPM_SUPPLY_S("I2S1 ASRC", 1, RT5670_ASRC_1,
			      11, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("I2S2 ASRC", 1, RT5670_ASRC_1,
			      12, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DAC STO ASRC", 1, RT5670_ASRC_1,
			      10, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DAC MONO L ASRC", 1, RT5670_ASRC_1,
			      9, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DAC MONO R ASRC", 1, RT5670_ASRC_1,
			      8, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DMIC STO1 ASRC", 1, RT5670_ASRC_1,
			      7, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DMIC STO2 ASRC", 1, RT5670_ASRC_1,
			      6, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DMIC MONO L ASRC", 1, RT5670_ASRC_1,
			      5, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DMIC MONO R ASRC", 1, RT5670_ASRC_1,
			      4, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ADC STO1 ASRC", 1, RT5670_ASRC_1,
			      3, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ADC STO2 ASRC", 1, RT5670_ASRC_1,
			      2, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ADC MONO L ASRC", 1, RT5670_ASRC_1,
			      1, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ADC MONO R ASRC", 1, RT5670_ASRC_1,
			      0, 0, शून्य, 0),

	/* Input Side */
	/* micbias */
	SND_SOC_DAPM_SUPPLY("MICBIAS1", RT5670_PWR_ANLG2,
			     RT5670_PWR_MB1_BIT, 0, शून्य, 0),

	/* Input Lines */
	SND_SOC_DAPM_INPUT("DMIC L1"),
	SND_SOC_DAPM_INPUT("DMIC R1"),
	SND_SOC_DAPM_INPUT("DMIC L2"),
	SND_SOC_DAPM_INPUT("DMIC R2"),
	SND_SOC_DAPM_INPUT("DMIC L3"),
	SND_SOC_DAPM_INPUT("DMIC R3"),

	SND_SOC_DAPM_INPUT("IN1P"),
	SND_SOC_DAPM_INPUT("IN1N"),
	SND_SOC_DAPM_INPUT("IN2P"),
	SND_SOC_DAPM_INPUT("IN2N"),

	SND_SOC_DAPM_PGA("DMIC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DMIC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DMIC3", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("DMIC CLK", SND_SOC_NOPM, 0, 0,
			    set_dmic_clk, SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_SUPPLY("DMIC1 Power", RT5670_DMIC_CTRL1,
			    RT5670_DMIC_1_EN_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DMIC2 Power", RT5670_DMIC_CTRL1,
			    RT5670_DMIC_2_EN_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DMIC3 Power", RT5670_DMIC_CTRL1,
			    RT5670_DMIC_3_EN_SFT, 0, शून्य, 0),
	/* Boost */
	SND_SOC_DAPM_PGA_E("BST1", RT5670_PWR_ANLG2, RT5670_PWR_BST1_BIT,
			   0, शून्य, 0, rt5670_bst1_event,
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_E("BST2", RT5670_PWR_ANLG2, RT5670_PWR_BST2_BIT,
			   0, शून्य, 0, rt5670_bst2_event,
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	/* Input Volume */
	SND_SOC_DAPM_PGA("INL VOL", RT5670_PWR_VOL,
			 RT5670_PWR_IN_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("INR VOL", RT5670_PWR_VOL,
			 RT5670_PWR_IN_R_BIT, 0, शून्य, 0),

	/* REC Mixer */
	SND_SOC_DAPM_MIXER("RECMIXL", RT5670_PWR_MIXER, RT5670_PWR_RM_L_BIT, 0,
			   rt5670_rec_l_mix, ARRAY_SIZE(rt5670_rec_l_mix)),
	SND_SOC_DAPM_MIXER("RECMIXR", RT5670_PWR_MIXER, RT5670_PWR_RM_R_BIT, 0,
			   rt5670_rec_r_mix, ARRAY_SIZE(rt5670_rec_r_mix)),
	/* ADCs */
	SND_SOC_DAPM_ADC("ADC 1", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC 2", शून्य, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_PGA("ADC 1_2", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("ADC 1 power", RT5670_PWR_DIG1,
			    RT5670_PWR_ADC_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC 2 power", RT5670_PWR_DIG1,
			    RT5670_PWR_ADC_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC clock", RT5670_PR_BASE +
			    RT5670_CHOP_DAC_ADC, 12, 0, शून्य, 0),
	/* ADC Mux */
	SND_SOC_DAPM_MUX("Stereo1 DMIC Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_sto1_dmic_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC L2 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_sto_adc_2_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC R2 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_sto_adc_2_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC L1 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_sto_adc_1_mux),
	SND_SOC_DAPM_MUX("Stereo1 ADC R1 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_sto_adc_1_mux),
	SND_SOC_DAPM_MUX("Stereo2 DMIC Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_sto2_dmic_mux),
	SND_SOC_DAPM_MUX("Stereo2 ADC L2 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_sto2_adc_2_mux),
	SND_SOC_DAPM_MUX("Stereo2 ADC R2 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_sto2_adc_2_mux),
	SND_SOC_DAPM_MUX("Stereo2 ADC L1 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_sto2_adc_1_mux),
	SND_SOC_DAPM_MUX("Stereo2 ADC R1 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_sto2_adc_1_mux),
	SND_SOC_DAPM_MUX("Stereo2 ADC LR Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_sto2_adc_lr_mux),
	SND_SOC_DAPM_MUX("Mono DMIC L Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_mono_dmic_l_mux),
	SND_SOC_DAPM_MUX("Mono DMIC R Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_mono_dmic_r_mux),
	SND_SOC_DAPM_MUX("Mono ADC L2 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_mono_adc_l2_mux),
	SND_SOC_DAPM_MUX("Mono ADC L1 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_mono_adc_l1_mux),
	SND_SOC_DAPM_MUX("Mono ADC R1 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_mono_adc_r1_mux),
	SND_SOC_DAPM_MUX("Mono ADC R2 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_mono_adc_r2_mux),
	/* ADC Mixer */
	SND_SOC_DAPM_SUPPLY("ADC Stereo1 Filter", RT5670_PWR_DIG2,
			    RT5670_PWR_ADC_S1F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC Stereo2 Filter", RT5670_PWR_DIG2,
			    RT5670_PWR_ADC_S2F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Sto1 ADC MIXL", SND_SOC_NOPM, 0, 0,
			   rt5670_sto1_adc_l_mix, ARRAY_SIZE(rt5670_sto1_adc_l_mix)),
	SND_SOC_DAPM_MIXER("Sto1 ADC MIXR", SND_SOC_NOPM, 0, 0,
			   rt5670_sto1_adc_r_mix, ARRAY_SIZE(rt5670_sto1_adc_r_mix)),
	SND_SOC_DAPM_MIXER("Sto2 ADC MIXL", SND_SOC_NOPM, 0, 0,
			   rt5670_sto2_adc_l_mix,
			   ARRAY_SIZE(rt5670_sto2_adc_l_mix)),
	SND_SOC_DAPM_MIXER("Sto2 ADC MIXR", SND_SOC_NOPM, 0, 0,
			   rt5670_sto2_adc_r_mix,
			   ARRAY_SIZE(rt5670_sto2_adc_r_mix)),
	SND_SOC_DAPM_SUPPLY("ADC Mono Left Filter", RT5670_PWR_DIG2,
			    RT5670_PWR_ADC_MF_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Mono ADC MIXL", RT5670_MONO_ADC_DIG_VOL,
			   RT5670_L_MUTE_SFT, 1, rt5670_mono_adc_l_mix,
			   ARRAY_SIZE(rt5670_mono_adc_l_mix)),
	SND_SOC_DAPM_SUPPLY("ADC Mono Right Filter", RT5670_PWR_DIG2,
			    RT5670_PWR_ADC_MF_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Mono ADC MIXR", RT5670_MONO_ADC_DIG_VOL,
			   RT5670_R_MUTE_SFT, 1, rt5670_mono_adc_r_mix,
			   ARRAY_SIZE(rt5670_mono_adc_r_mix)),

	/* ADC PGA */
	SND_SOC_DAPM_PGA("Stereo1 ADC MIXL", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Stereo1 ADC MIXR", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Stereo2 ADC MIXL", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Stereo2 ADC MIXR", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Sto2 ADC LR MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Stereo1 ADC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Stereo2 ADC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Mono ADC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("VAD_ADC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF_ADC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF_ADC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF_ADC3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1_ADC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1_ADC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1_ADC3", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* DSP */
	SND_SOC_DAPM_PGA("TxDP_ADC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("TxDP_ADC_L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("TxDP_ADC_R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("TxDC_DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_MUX("TDM Data Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_txdp_slot_mux),

	SND_SOC_DAPM_MUX("DSP UL Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_dsp_ul_mux),
	SND_SOC_DAPM_MUX("DSP DL Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_dsp_dl_mux),

	SND_SOC_DAPM_MUX("RxDP Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_rxdp_mux),

	/* IF2 Mux */
	SND_SOC_DAPM_MUX("IF2 ADC Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_अगर2_adc_in_mux),

	/* Digital Interface */
	SND_SOC_DAPM_SUPPLY("I2S1", RT5670_PWR_DIG1,
			    RT5670_PWR_I2S1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1 L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1 R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC2 L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 DAC2 R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 ADC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 ADC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF1 ADC R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("I2S2", RT5670_PWR_DIG1,
			    RT5670_PWR_I2S2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 DAC R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 ADC", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 ADC L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IF2 ADC R", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* Digital Interface Select */
	SND_SOC_DAPM_MUX("IF1 ADC1 IN1 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_अगर1_adc1_in1_mux),
	SND_SOC_DAPM_MUX("IF1 ADC1 IN2 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_अगर1_adc1_in2_mux),
	SND_SOC_DAPM_MUX("IF1 ADC2 IN Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_अगर1_adc2_in_mux),
	SND_SOC_DAPM_MUX("IF1 ADC2 IN1 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_अगर1_adc2_in1_mux),
	SND_SOC_DAPM_MUX("VAD ADC Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_vad_adc_mux),

	/* Audio Interface */
	SND_SOC_DAPM_AIF_IN("AIF1RX", "AIF1 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX", "AIF1 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF2RX", "AIF2 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2TX", "AIF2 Capture", 0,
			     RT5670_GPIO_CTRL1, RT5670_I2S2_PIN_SFT, 1),

	/* Audio DSP */
	SND_SOC_DAPM_PGA("Audio DSP", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* Output Side */
	/* DAC mixer beक्रमe sound effect  */
	SND_SOC_DAPM_MIXER("DAC1 MIXL", SND_SOC_NOPM, 0, 0,
			   rt5670_dac_l_mix, ARRAY_SIZE(rt5670_dac_l_mix)),
	SND_SOC_DAPM_MIXER("DAC1 MIXR", SND_SOC_NOPM, 0, 0,
			   rt5670_dac_r_mix, ARRAY_SIZE(rt5670_dac_r_mix)),
	SND_SOC_DAPM_PGA("DAC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* DAC2 channel Mux */
	SND_SOC_DAPM_MUX("DAC L2 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_dac_l2_mux),
	SND_SOC_DAPM_MUX("DAC R2 Mux", SND_SOC_NOPM, 0, 0,
			 &rt5670_dac_r2_mux),
	SND_SOC_DAPM_PGA("DAC L2 Volume", RT5670_PWR_DIG1,
			 RT5670_PWR_DAC_L2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DAC R2 Volume", RT5670_PWR_DIG1,
			 RT5670_PWR_DAC_R2_BIT, 0, शून्य, 0),

	SND_SOC_DAPM_MUX("DAC1 L Mux", SND_SOC_NOPM, 0, 0, &rt5670_dac1l_mux),
	SND_SOC_DAPM_MUX("DAC1 R Mux", SND_SOC_NOPM, 0, 0, &rt5670_dac1r_mux),

	/* DAC Mixer */
	SND_SOC_DAPM_SUPPLY("DAC Stereo1 Filter", RT5670_PWR_DIG2,
			    RT5670_PWR_DAC_S1F_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC Mono Left Filter", RT5670_PWR_DIG2,
			    RT5670_PWR_DAC_MF_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC Mono Right Filter", RT5670_PWR_DIG2,
			    RT5670_PWR_DAC_MF_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Stereo DAC MIXL", SND_SOC_NOPM, 0, 0,
			   rt5670_sto_dac_l_mix,
			   ARRAY_SIZE(rt5670_sto_dac_l_mix)),
	SND_SOC_DAPM_MIXER("Stereo DAC MIXR", SND_SOC_NOPM, 0, 0,
			   rt5670_sto_dac_r_mix,
			   ARRAY_SIZE(rt5670_sto_dac_r_mix)),
	SND_SOC_DAPM_MIXER("Mono DAC MIXL", SND_SOC_NOPM, 0, 0,
			   rt5670_mono_dac_l_mix,
			   ARRAY_SIZE(rt5670_mono_dac_l_mix)),
	SND_SOC_DAPM_MIXER("Mono DAC MIXR", SND_SOC_NOPM, 0, 0,
			   rt5670_mono_dac_r_mix,
			   ARRAY_SIZE(rt5670_mono_dac_r_mix)),
	SND_SOC_DAPM_MIXER("DAC MIXL", SND_SOC_NOPM, 0, 0,
			   rt5670_dig_l_mix,
			   ARRAY_SIZE(rt5670_dig_l_mix)),
	SND_SOC_DAPM_MIXER("DAC MIXR", SND_SOC_NOPM, 0, 0,
			   rt5670_dig_r_mix,
			   ARRAY_SIZE(rt5670_dig_r_mix)),

	/* DACs */
	SND_SOC_DAPM_SUPPLY("DAC L1 Power", RT5670_PWR_DIG1,
			    RT5670_PWR_DAC_L1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC R1 Power", RT5670_PWR_DIG1,
			    RT5670_PWR_DAC_R1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_DAC("DAC L1", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC R1", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC L2", शून्य, RT5670_PWR_DIG1,
			 RT5670_PWR_DAC_L2_BIT, 0),

	SND_SOC_DAPM_DAC("DAC R2", शून्य, RT5670_PWR_DIG1,
			 RT5670_PWR_DAC_R2_BIT, 0),
	/* OUT Mixer */

	SND_SOC_DAPM_MIXER("OUT MIXL", RT5670_PWR_MIXER, RT5670_PWR_OM_L_BIT,
			   0, rt5670_out_l_mix, ARRAY_SIZE(rt5670_out_l_mix)),
	SND_SOC_DAPM_MIXER("OUT MIXR", RT5670_PWR_MIXER, RT5670_PWR_OM_R_BIT,
			   0, rt5670_out_r_mix, ARRAY_SIZE(rt5670_out_r_mix)),
	/* Ouput Volume */
	SND_SOC_DAPM_MIXER("HPOVOL MIXL", RT5670_PWR_VOL,
			   RT5670_PWR_HV_L_BIT, 0,
			   rt5670_hpvoll_mix, ARRAY_SIZE(rt5670_hpvoll_mix)),
	SND_SOC_DAPM_MIXER("HPOVOL MIXR", RT5670_PWR_VOL,
			   RT5670_PWR_HV_R_BIT, 0,
			   rt5670_hpvolr_mix, ARRAY_SIZE(rt5670_hpvolr_mix)),
	SND_SOC_DAPM_PGA("DAC 1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DAC 2", SND_SOC_NOPM,	0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("HPOVOL", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* HPO/LOUT/Mono Mixer */
	SND_SOC_DAPM_MIXER("HPO MIX", SND_SOC_NOPM, 0, 0,
			   rt5670_hpo_mix, ARRAY_SIZE(rt5670_hpo_mix)),
	SND_SOC_DAPM_MIXER("LOUT MIX", RT5670_PWR_ANLG1, RT5670_PWR_LM_BIT,
			   0, rt5670_lout_mix, ARRAY_SIZE(rt5670_lout_mix)),
	SND_SOC_DAPM_SUPPLY_S("Improve HP Amp Drv", 1, SND_SOC_NOPM, 0, 0,
			      rt5670_hp_घातer_event, SND_SOC_DAPM_POST_PMU |
			      SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_SUPPLY("HP L Amp", RT5670_PWR_ANLG1,
			    RT5670_PWR_HP_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("HP R Amp", RT5670_PWR_ANLG1,
			    RT5670_PWR_HP_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA_S("HP Amp", 1, SND_SOC_NOPM, 0, 0,
			   rt5670_hp_event, SND_SOC_DAPM_PRE_PMD |
			   SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SWITCH("LOUT L Playback", SND_SOC_NOPM, 0, 0,
			    &lout_l_enable_control),
	SND_SOC_DAPM_SWITCH("LOUT R Playback", SND_SOC_NOPM, 0, 0,
			    &lout_r_enable_control),
	SND_SOC_DAPM_PGA("LOUT Amp", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* PDM */
	SND_SOC_DAPM_SUPPLY("PDM1 Power", RT5670_PWR_DIG2,
		RT5670_PWR_PDM1_BIT, 0, शून्य, 0),

	SND_SOC_DAPM_MUX("PDM1 L Mux", RT5670_PDM_OUT_CTRL,
			 RT5670_M_PDM1_L_SFT, 1, &rt5670_pdm1_l_mux),
	SND_SOC_DAPM_MUX("PDM1 R Mux", RT5670_PDM_OUT_CTRL,
			 RT5670_M_PDM1_R_SFT, 1, &rt5670_pdm1_r_mux),

	/* Output Lines */
	SND_SOC_DAPM_OUTPUT("HPOL"),
	SND_SOC_DAPM_OUTPUT("HPOR"),
	SND_SOC_DAPM_OUTPUT("LOUTL"),
	SND_SOC_DAPM_OUTPUT("LOUTR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget rt5670_specअगरic_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("PDM2 Power", RT5670_PWR_DIG2,
		RT5670_PWR_PDM2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_MUX("PDM2 L Mux", RT5670_PDM_OUT_CTRL,
			 RT5670_M_PDM2_L_SFT, 1, &rt5670_pdm2_l_mux),
	SND_SOC_DAPM_MUX("PDM2 R Mux", RT5670_PDM_OUT_CTRL,
			 RT5670_M_PDM2_R_SFT, 1, &rt5670_pdm2_r_mux),
	SND_SOC_DAPM_OUTPUT("PDM1L"),
	SND_SOC_DAPM_OUTPUT("PDM1R"),
	SND_SOC_DAPM_OUTPUT("PDM2L"),
	SND_SOC_DAPM_OUTPUT("PDM2R"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget rt5672_specअगरic_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_PGA_E("SPO Amp", SND_SOC_NOPM, 0, 0, शून्य, 0,
			   rt5670_spk_event, SND_SOC_DAPM_PRE_PMD |
			   SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_OUTPUT("SPOLP"),
	SND_SOC_DAPM_OUTPUT("SPOLN"),
	SND_SOC_DAPM_OUTPUT("SPORP"),
	SND_SOC_DAPM_OUTPUT("SPORN"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5670_dapm_routes[] = अणु
	अणु "ADC Stereo1 Filter", शून्य, "ADC STO1 ASRC", is_using_asrc पूर्ण,
	अणु "ADC Stereo2 Filter", शून्य, "ADC STO2 ASRC", is_using_asrc पूर्ण,
	अणु "ADC Mono Left Filter", शून्य, "ADC MONO L ASRC", is_using_asrc पूर्ण,
	अणु "ADC Mono Right Filter", शून्य, "ADC MONO R ASRC", is_using_asrc पूर्ण,
	अणु "DAC Mono Left Filter", शून्य, "DAC MONO L ASRC", is_using_asrc पूर्ण,
	अणु "DAC Mono Right Filter", शून्य, "DAC MONO R ASRC", is_using_asrc पूर्ण,
	अणु "DAC Stereo1 Filter", शून्य, "DAC STO ASRC", is_using_asrc पूर्ण,
	अणु "Stereo1 DMIC Mux", शून्य, "DMIC STO1 ASRC", can_use_asrc पूर्ण,
	अणु "Stereo2 DMIC Mux", शून्य, "DMIC STO2 ASRC", can_use_asrc पूर्ण,
	अणु "Mono DMIC L Mux", शून्य, "DMIC MONO L ASRC", can_use_asrc पूर्ण,
	अणु "Mono DMIC R Mux", शून्य, "DMIC MONO R ASRC", can_use_asrc पूर्ण,

	अणु "I2S1", शून्य, "I2S1 ASRC", can_use_asrcपूर्ण,
	अणु "I2S2", शून्य, "I2S2 ASRC", can_use_asrcपूर्ण,

	अणु "DMIC1", शून्य, "DMIC L1" पूर्ण,
	अणु "DMIC1", शून्य, "DMIC R1" पूर्ण,
	अणु "DMIC2", शून्य, "DMIC L2" पूर्ण,
	अणु "DMIC2", शून्य, "DMIC R2" पूर्ण,
	अणु "DMIC3", शून्य, "DMIC L3" पूर्ण,
	अणु "DMIC3", शून्य, "DMIC R3" पूर्ण,

	अणु "BST1", शून्य, "IN1P" पूर्ण,
	अणु "BST1", शून्य, "IN1N" पूर्ण,
	अणु "BST1", शून्य, "Mic Det Power" पूर्ण,
	अणु "BST2", शून्य, "IN2P" पूर्ण,
	अणु "BST2", शून्य, "IN2N" पूर्ण,

	अणु "INL VOL", शून्य, "IN2P" पूर्ण,
	अणु "INR VOL", शून्य, "IN2N" पूर्ण,

	अणु "RECMIXL", "INL Switch", "INL VOL" पूर्ण,
	अणु "RECMIXL", "BST2 Switch", "BST2" पूर्ण,
	अणु "RECMIXL", "BST1 Switch", "BST1" पूर्ण,

	अणु "RECMIXR", "INR Switch", "INR VOL" पूर्ण,
	अणु "RECMIXR", "BST2 Switch", "BST2" पूर्ण,
	अणु "RECMIXR", "BST1 Switch", "BST1" पूर्ण,

	अणु "ADC 1", शून्य, "RECMIXL" पूर्ण,
	अणु "ADC 1", शून्य, "ADC 1 power" पूर्ण,
	अणु "ADC 1", शून्य, "ADC clock" पूर्ण,
	अणु "ADC 2", शून्य, "RECMIXR" पूर्ण,
	अणु "ADC 2", शून्य, "ADC 2 power" पूर्ण,
	अणु "ADC 2", शून्य, "ADC clock" पूर्ण,

	अणु "DMIC L1", शून्य, "DMIC CLK" पूर्ण,
	अणु "DMIC L1", शून्य, "DMIC1 Power" पूर्ण,
	अणु "DMIC R1", शून्य, "DMIC CLK" पूर्ण,
	अणु "DMIC R1", शून्य, "DMIC1 Power" पूर्ण,
	अणु "DMIC L2", शून्य, "DMIC CLK" पूर्ण,
	अणु "DMIC L2", शून्य, "DMIC2 Power" पूर्ण,
	अणु "DMIC R2", शून्य, "DMIC CLK" पूर्ण,
	अणु "DMIC R2", शून्य, "DMIC2 Power" पूर्ण,
	अणु "DMIC L3", शून्य, "DMIC CLK" पूर्ण,
	अणु "DMIC L3", शून्य, "DMIC3 Power" पूर्ण,
	अणु "DMIC R3", शून्य, "DMIC CLK" पूर्ण,
	अणु "DMIC R3", शून्य, "DMIC3 Power" पूर्ण,

	अणु "Stereo1 DMIC Mux", "DMIC1", "DMIC1" पूर्ण,
	अणु "Stereo1 DMIC Mux", "DMIC2", "DMIC2" पूर्ण,
	अणु "Stereo1 DMIC Mux", "DMIC3", "DMIC3" पूर्ण,

	अणु "Stereo2 DMIC Mux", "DMIC1", "DMIC1" पूर्ण,
	अणु "Stereo2 DMIC Mux", "DMIC2", "DMIC2" पूर्ण,
	अणु "Stereo2 DMIC Mux", "DMIC3", "DMIC3" पूर्ण,

	अणु "Mono DMIC L Mux", "DMIC1", "DMIC L1" पूर्ण,
	अणु "Mono DMIC L Mux", "DMIC2", "DMIC L2" पूर्ण,
	अणु "Mono DMIC L Mux", "DMIC3", "DMIC L3" पूर्ण,

	अणु "Mono DMIC R Mux", "DMIC1", "DMIC R1" पूर्ण,
	अणु "Mono DMIC R Mux", "DMIC2", "DMIC R2" पूर्ण,
	अणु "Mono DMIC R Mux", "DMIC3", "DMIC R3" पूर्ण,

	अणु "ADC 1_2", शून्य, "ADC 1" पूर्ण,
	अणु "ADC 1_2", शून्य, "ADC 2" पूर्ण,

	अणु "Stereo1 ADC L2 Mux", "DMIC", "Stereo1 DMIC Mux" पूर्ण,
	अणु "Stereo1 ADC L2 Mux", "DAC MIX", "DAC MIXL" पूर्ण,
	अणु "Stereo1 ADC L1 Mux", "ADC", "ADC 1_2" पूर्ण,
	अणु "Stereo1 ADC L1 Mux", "DAC MIX", "DAC MIXL" पूर्ण,

	अणु "Stereo1 ADC R1 Mux", "ADC", "ADC 1_2" पूर्ण,
	अणु "Stereo1 ADC R1 Mux", "DAC MIX", "DAC MIXR" पूर्ण,
	अणु "Stereo1 ADC R2 Mux", "DMIC", "Stereo1 DMIC Mux" पूर्ण,
	अणु "Stereo1 ADC R2 Mux", "DAC MIX", "DAC MIXR" पूर्ण,

	अणु "Mono ADC L2 Mux", "DMIC", "Mono DMIC L Mux" पूर्ण,
	अणु "Mono ADC L2 Mux", "Mono DAC MIXL", "Mono DAC MIXL" पूर्ण,
	अणु "Mono ADC L1 Mux", "Mono DAC MIXL", "Mono DAC MIXL" पूर्ण,
	अणु "Mono ADC L1 Mux", "ADC1",  "ADC 1" पूर्ण,

	अणु "Mono ADC R1 Mux", "Mono DAC MIXR", "Mono DAC MIXR" पूर्ण,
	अणु "Mono ADC R1 Mux", "ADC2", "ADC 2" पूर्ण,
	अणु "Mono ADC R2 Mux", "DMIC", "Mono DMIC R Mux" पूर्ण,
	अणु "Mono ADC R2 Mux", "Mono DAC MIXR", "Mono DAC MIXR" पूर्ण,

	अणु "Sto1 ADC MIXL", "ADC1 Switch", "Stereo1 ADC L1 Mux" पूर्ण,
	अणु "Sto1 ADC MIXL", "ADC2 Switch", "Stereo1 ADC L2 Mux" पूर्ण,
	अणु "Sto1 ADC MIXR", "ADC1 Switch", "Stereo1 ADC R1 Mux" पूर्ण,
	अणु "Sto1 ADC MIXR", "ADC2 Switch", "Stereo1 ADC R2 Mux" पूर्ण,

	अणु "Stereo1 ADC MIXL", शून्य, "Sto1 ADC MIXL" पूर्ण,
	अणु "Stereo1 ADC MIXL", शून्य, "ADC Stereo1 Filter" पूर्ण,

	अणु "Stereo1 ADC MIXR", शून्य, "Sto1 ADC MIXR" पूर्ण,
	अणु "Stereo1 ADC MIXR", शून्य, "ADC Stereo1 Filter" पूर्ण,
	अणु "ADC Stereo1 Filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,

	अणु "Mono ADC MIXL", "ADC1 Switch", "Mono ADC L1 Mux" पूर्ण,
	अणु "Mono ADC MIXL", "ADC2 Switch", "Mono ADC L2 Mux" पूर्ण,
	अणु "Mono ADC MIXL", शून्य, "ADC Mono Left Filter" पूर्ण,
	अणु "ADC Mono Left Filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,

	अणु "Mono ADC MIXR", "ADC1 Switch", "Mono ADC R1 Mux" पूर्ण,
	अणु "Mono ADC MIXR", "ADC2 Switch", "Mono ADC R2 Mux" पूर्ण,
	अणु "Mono ADC MIXR", शून्य, "ADC Mono Right Filter" पूर्ण,
	अणु "ADC Mono Right Filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,

	अणु "Stereo2 ADC L2 Mux", "DMIC", "Stereo2 DMIC Mux" पूर्ण,
	अणु "Stereo2 ADC L2 Mux", "DAC MIX", "DAC MIXL" पूर्ण,
	अणु "Stereo2 ADC L1 Mux", "ADC", "ADC 1_2" पूर्ण,
	अणु "Stereo2 ADC L1 Mux", "DAC MIX", "DAC MIXL" पूर्ण,

	अणु "Stereo2 ADC R1 Mux", "ADC", "ADC 1_2" पूर्ण,
	अणु "Stereo2 ADC R1 Mux", "DAC MIX", "DAC MIXR" पूर्ण,
	अणु "Stereo2 ADC R2 Mux", "DMIC", "Stereo2 DMIC Mux" पूर्ण,
	अणु "Stereo2 ADC R2 Mux", "DAC MIX", "DAC MIXR" पूर्ण,

	अणु "Sto2 ADC MIXL", "ADC1 Switch", "Stereo2 ADC L1 Mux" पूर्ण,
	अणु "Sto2 ADC MIXL", "ADC2 Switch", "Stereo2 ADC L2 Mux" पूर्ण,
	अणु "Sto2 ADC MIXR", "ADC1 Switch", "Stereo2 ADC R1 Mux" पूर्ण,
	अणु "Sto2 ADC MIXR", "ADC2 Switch", "Stereo2 ADC R2 Mux" पूर्ण,

	अणु "Sto2 ADC LR MIX", शून्य, "Sto2 ADC MIXL" पूर्ण,
	अणु "Sto2 ADC LR MIX", शून्य, "Sto2 ADC MIXR" पूर्ण,

	अणु "Stereo2 ADC LR Mux", "L", "Sto2 ADC MIXL" पूर्ण,
	अणु "Stereo2 ADC LR Mux", "LR", "Sto2 ADC LR MIX" पूर्ण,

	अणु "Stereo2 ADC MIXL", शून्य, "Stereo2 ADC LR Mux" पूर्ण,
	अणु "Stereo2 ADC MIXL", शून्य, "ADC Stereo2 Filter" पूर्ण,

	अणु "Stereo2 ADC MIXR", शून्य, "Sto2 ADC MIXR" पूर्ण,
	अणु "Stereo2 ADC MIXR", शून्य, "ADC Stereo2 Filter" पूर्ण,
	अणु "ADC Stereo2 Filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,

	अणु "VAD ADC Mux", "Sto1 ADC L", "Stereo1 ADC MIXL" पूर्ण,
	अणु "VAD ADC Mux", "Mono ADC L", "Mono ADC MIXL" पूर्ण,
	अणु "VAD ADC Mux", "Mono ADC R", "Mono ADC MIXR" पूर्ण,
	अणु "VAD ADC Mux", "Sto2 ADC L", "Sto2 ADC MIXL" पूर्ण,

	अणु "VAD_ADC", शून्य, "VAD ADC Mux" पूर्ण,

	अणु "IF_ADC1", शून्य, "Stereo1 ADC MIXL" पूर्ण,
	अणु "IF_ADC1", शून्य, "Stereo1 ADC MIXR" पूर्ण,
	अणु "IF_ADC2", शून्य, "Mono ADC MIXL" पूर्ण,
	अणु "IF_ADC2", शून्य, "Mono ADC MIXR" पूर्ण,
	अणु "IF_ADC3", शून्य, "Stereo2 ADC MIXL" पूर्ण,
	अणु "IF_ADC3", शून्य, "Stereo2 ADC MIXR" पूर्ण,

	अणु "IF1 ADC1 IN1 Mux", "IF_ADC1", "IF_ADC1" पूर्ण,
	अणु "IF1 ADC1 IN1 Mux", "IF1_ADC3", "IF1_ADC3" पूर्ण,

	अणु "IF1 ADC1 IN2 Mux", "IF1_ADC1_IN1", "IF1 ADC1 IN1 Mux" पूर्ण,
	अणु "IF1 ADC1 IN2 Mux", "IF1_ADC4", "TxDP_ADC" पूर्ण,

	अणु "IF1 ADC2 IN Mux", "IF_ADC2", "IF_ADC2" पूर्ण,
	अणु "IF1 ADC2 IN Mux", "VAD_ADC", "VAD_ADC" पूर्ण,

	अणु "IF1 ADC2 IN1 Mux", "IF1_ADC2_IN", "IF1 ADC2 IN Mux" पूर्ण,
	अणु "IF1 ADC2 IN1 Mux", "IF1_ADC4", "TxDP_ADC" पूर्ण,

	अणु "IF1_ADC1" , शून्य, "IF1 ADC1 IN2 Mux" पूर्ण,
	अणु "IF1_ADC2" , शून्य, "IF1 ADC2 IN1 Mux" पूर्ण,

	अणु "Stereo1 ADC MIX", शून्य, "Stereo1 ADC MIXL" पूर्ण,
	अणु "Stereo1 ADC MIX", शून्य, "Stereo1 ADC MIXR" पूर्ण,
	अणु "Stereo2 ADC MIX", शून्य, "Sto2 ADC MIXL" पूर्ण,
	अणु "Stereo2 ADC MIX", शून्य, "Sto2 ADC MIXR" पूर्ण,
	अणु "Mono ADC MIX", शून्य, "Mono ADC MIXL" पूर्ण,
	अणु "Mono ADC MIX", शून्य, "Mono ADC MIXR" पूर्ण,

	अणु "RxDP Mux", "IF2 DAC", "IF2 DAC" पूर्ण,
	अणु "RxDP Mux", "IF1 DAC", "IF1 DAC2" पूर्ण,
	अणु "RxDP Mux", "STO1 ADC Mixer", "Stereo1 ADC MIX" पूर्ण,
	अणु "RxDP Mux", "STO2 ADC Mixer", "Stereo2 ADC MIX" पूर्ण,
	अणु "RxDP Mux", "Mono ADC Mixer L", "Mono ADC MIXL" पूर्ण,
	अणु "RxDP Mux", "Mono ADC Mixer R", "Mono ADC MIXR" पूर्ण,
	अणु "RxDP Mux", "DAC1", "DAC MIX" पूर्ण,

	अणु "TDM Data Mux", "Slot 0-1", "Stereo1 ADC MIX" पूर्ण,
	अणु "TDM Data Mux", "Slot 2-3", "Mono ADC MIX" पूर्ण,
	अणु "TDM Data Mux", "Slot 4-5", "Stereo2 ADC MIX" पूर्ण,
	अणु "TDM Data Mux", "Slot 6-7", "IF2 DAC" पूर्ण,

	अणु "DSP UL Mux", "Bypass", "TDM Data Mux" पूर्ण,
	अणु "DSP UL Mux", शून्य, "I2S DSP" पूर्ण,
	अणु "DSP DL Mux", "Bypass", "RxDP Mux" पूर्ण,
	अणु "DSP DL Mux", शून्य, "I2S DSP" पूर्ण,

	अणु "TxDP_ADC_L", शून्य, "DSP UL Mux" पूर्ण,
	अणु "TxDP_ADC_R", शून्य, "DSP UL Mux" पूर्ण,
	अणु "TxDC_DAC", शून्य, "DSP DL Mux" पूर्ण,

	अणु "TxDP_ADC", शून्य, "TxDP_ADC_L" पूर्ण,
	अणु "TxDP_ADC", शून्य, "TxDP_ADC_R" पूर्ण,

	अणु "IF1 ADC", शून्य, "I2S1" पूर्ण,
	अणु "IF1 ADC", शून्य, "IF1_ADC1" पूर्ण,
	अणु "IF1 ADC", शून्य, "IF1_ADC2" पूर्ण,
	अणु "IF1 ADC", शून्य, "IF_ADC3" पूर्ण,
	अणु "IF1 ADC", शून्य, "TxDP_ADC" पूर्ण,

	अणु "IF2 ADC Mux", "IF_ADC1", "IF_ADC1" पूर्ण,
	अणु "IF2 ADC Mux", "IF_ADC2", "IF_ADC2" पूर्ण,
	अणु "IF2 ADC Mux", "IF_ADC3", "IF_ADC3" पूर्ण,
	अणु "IF2 ADC Mux", "TxDC_DAC", "TxDC_DAC" पूर्ण,
	अणु "IF2 ADC Mux", "TxDP_ADC", "TxDP_ADC" पूर्ण,
	अणु "IF2 ADC Mux", "VAD_ADC", "VAD_ADC" पूर्ण,

	अणु "IF2 ADC L", शून्य, "IF2 ADC Mux" पूर्ण,
	अणु "IF2 ADC R", शून्य, "IF2 ADC Mux" पूर्ण,

	अणु "IF2 ADC", शून्य, "I2S2" पूर्ण,
	अणु "IF2 ADC", शून्य, "IF2 ADC L" पूर्ण,
	अणु "IF2 ADC", शून्य, "IF2 ADC R" पूर्ण,

	अणु "AIF1TX", शून्य, "IF1 ADC" पूर्ण,
	अणु "AIF2TX", शून्य, "IF2 ADC" पूर्ण,

	अणु "IF1 DAC1", शून्य, "AIF1RX" पूर्ण,
	अणु "IF1 DAC2", शून्य, "AIF1RX" पूर्ण,
	अणु "IF2 DAC", शून्य, "AIF2RX" पूर्ण,

	अणु "IF1 DAC1", शून्य, "I2S1" पूर्ण,
	अणु "IF1 DAC2", शून्य, "I2S1" पूर्ण,
	अणु "IF2 DAC", शून्य, "I2S2" पूर्ण,

	अणु "IF1 DAC2 L", शून्य, "IF1 DAC2" पूर्ण,
	अणु "IF1 DAC2 R", शून्य, "IF1 DAC2" पूर्ण,
	अणु "IF1 DAC1 L", शून्य, "IF1 DAC1" पूर्ण,
	अणु "IF1 DAC1 R", शून्य, "IF1 DAC1" पूर्ण,
	अणु "IF2 DAC L", शून्य, "IF2 DAC" पूर्ण,
	अणु "IF2 DAC R", शून्य, "IF2 DAC" पूर्ण,

	अणु "DAC1 L Mux", "IF1 DAC", "IF1 DAC1 L" पूर्ण,
	अणु "DAC1 L Mux", "IF2 DAC", "IF2 DAC L" पूर्ण,

	अणु "DAC1 R Mux", "IF1 DAC", "IF1 DAC1 R" पूर्ण,
	अणु "DAC1 R Mux", "IF2 DAC", "IF2 DAC R" पूर्ण,

	अणु "DAC1 MIXL", "Stereo ADC Switch", "Stereo1 ADC MIXL" पूर्ण,
	अणु "DAC1 MIXL", "DAC1 Switch", "DAC1 L Mux" पूर्ण,
	अणु "DAC1 MIXL", शून्य, "DAC Stereo1 Filter" पूर्ण,
	अणु "DAC1 MIXR", "Stereo ADC Switch", "Stereo1 ADC MIXR" पूर्ण,
	अणु "DAC1 MIXR", "DAC1 Switch", "DAC1 R Mux" पूर्ण,
	अणु "DAC1 MIXR", शून्य, "DAC Stereo1 Filter" पूर्ण,

	अणु "DAC Stereo1 Filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,
	अणु "DAC Mono Left Filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,
	अणु "DAC Mono Right Filter", शून्य, "PLL1", is_sys_clk_from_pll पूर्ण,

	अणु "DAC MIX", शून्य, "DAC1 MIXL" पूर्ण,
	अणु "DAC MIX", शून्य, "DAC1 MIXR" पूर्ण,

	अणु "Audio DSP", शून्य, "DAC1 MIXL" पूर्ण,
	अणु "Audio DSP", शून्य, "DAC1 MIXR" पूर्ण,

	अणु "DAC L2 Mux", "IF1 DAC", "IF1 DAC2 L" पूर्ण,
	अणु "DAC L2 Mux", "IF2 DAC", "IF2 DAC L" पूर्ण,
	अणु "DAC L2 Mux", "TxDC DAC", "TxDC_DAC" पूर्ण,
	अणु "DAC L2 Mux", "VAD_ADC", "VAD_ADC" पूर्ण,
	अणु "DAC L2 Volume", शून्य, "DAC L2 Mux" पूर्ण,
	अणु "DAC L2 Volume", शून्य, "DAC Mono Left Filter" पूर्ण,

	अणु "DAC R2 Mux", "IF1 DAC", "IF1 DAC2 R" पूर्ण,
	अणु "DAC R2 Mux", "IF2 DAC", "IF2 DAC R" पूर्ण,
	अणु "DAC R2 Mux", "TxDC DAC", "TxDC_DAC" पूर्ण,
	अणु "DAC R2 Mux", "TxDP ADC", "TxDP_ADC" पूर्ण,
	अणु "DAC R2 Volume", शून्य, "DAC R2 Mux" पूर्ण,
	अणु "DAC R2 Volume", शून्य, "DAC Mono Right Filter" पूर्ण,

	अणु "Stereo DAC MIXL", "DAC L1 Switch", "DAC1 MIXL" पूर्ण,
	अणु "Stereo DAC MIXL", "DAC R1 Switch", "DAC1 MIXR" पूर्ण,
	अणु "Stereo DAC MIXL", "DAC L2 Switch", "DAC L2 Volume" पूर्ण,
	अणु "Stereo DAC MIXL", शून्य, "DAC Stereo1 Filter" पूर्ण,
	अणु "Stereo DAC MIXL", शून्य, "DAC L1 Power" पूर्ण,
	अणु "Stereo DAC MIXR", "DAC R1 Switch", "DAC1 MIXR" पूर्ण,
	अणु "Stereo DAC MIXR", "DAC L1 Switch", "DAC1 MIXL" पूर्ण,
	अणु "Stereo DAC MIXR", "DAC R2 Switch", "DAC R2 Volume" पूर्ण,
	अणु "Stereo DAC MIXR", शून्य, "DAC Stereo1 Filter" पूर्ण,
	अणु "Stereo DAC MIXR", शून्य, "DAC R1 Power" पूर्ण,

	अणु "Mono DAC MIXL", "DAC L1 Switch", "DAC1 MIXL" पूर्ण,
	अणु "Mono DAC MIXL", "DAC L2 Switch", "DAC L2 Volume" पूर्ण,
	अणु "Mono DAC MIXL", "DAC R2 Switch", "DAC R2 Volume" पूर्ण,
	अणु "Mono DAC MIXL", शून्य, "DAC Mono Left Filter" पूर्ण,
	अणु "Mono DAC MIXR", "DAC R1 Switch", "DAC1 MIXR" पूर्ण,
	अणु "Mono DAC MIXR", "DAC R2 Switch", "DAC R2 Volume" पूर्ण,
	अणु "Mono DAC MIXR", "DAC L2 Switch", "DAC L2 Volume" पूर्ण,
	अणु "Mono DAC MIXR", शून्य, "DAC Mono Right Filter" पूर्ण,

	अणु "DAC MIXL", "Sto DAC Mix L Switch", "Stereo DAC MIXL" पूर्ण,
	अणु "DAC MIXL", "DAC L2 Switch", "DAC L2 Volume" पूर्ण,
	अणु "DAC MIXL", "DAC R2 Switch", "DAC R2 Volume" पूर्ण,
	अणु "DAC MIXR", "Sto DAC Mix R Switch", "Stereo DAC MIXR" पूर्ण,
	अणु "DAC MIXR", "DAC R2 Switch", "DAC R2 Volume" पूर्ण,
	अणु "DAC MIXR", "DAC L2 Switch", "DAC L2 Volume" पूर्ण,

	अणु "DAC L1", शून्य, "DAC L1 Power" पूर्ण,
	अणु "DAC L1", शून्य, "Stereo DAC MIXL" पूर्ण,
	अणु "DAC R1", शून्य, "DAC R1 Power" पूर्ण,
	अणु "DAC R1", शून्य, "Stereo DAC MIXR" पूर्ण,
	अणु "DAC L2", शून्य, "Mono DAC MIXL" पूर्ण,
	अणु "DAC R2", शून्य, "Mono DAC MIXR" पूर्ण,

	अणु "OUT MIXL", "BST1 Switch", "BST1" पूर्ण,
	अणु "OUT MIXL", "INL Switch", "INL VOL" पूर्ण,
	अणु "OUT MIXL", "DAC L2 Switch", "DAC L2" पूर्ण,
	अणु "OUT MIXL", "DAC L1 Switch", "DAC L1" पूर्ण,

	अणु "OUT MIXR", "BST2 Switch", "BST2" पूर्ण,
	अणु "OUT MIXR", "INR Switch", "INR VOL" पूर्ण,
	अणु "OUT MIXR", "DAC R2 Switch", "DAC R2" पूर्ण,
	अणु "OUT MIXR", "DAC R1 Switch", "DAC R1" पूर्ण,

	अणु "HPOVOL MIXL", "DAC1 Switch", "DAC L1" पूर्ण,
	अणु "HPOVOL MIXL", "INL Switch", "INL VOL" पूर्ण,
	अणु "HPOVOL MIXR", "DAC1 Switch", "DAC R1" पूर्ण,
	अणु "HPOVOL MIXR", "INR Switch", "INR VOL" पूर्ण,

	अणु "DAC 2", शून्य, "DAC L2" पूर्ण,
	अणु "DAC 2", शून्य, "DAC R2" पूर्ण,
	अणु "DAC 1", शून्य, "DAC L1" पूर्ण,
	अणु "DAC 1", शून्य, "DAC R1" पूर्ण,
	अणु "HPOVOL", शून्य, "HPOVOL MIXL" पूर्ण,
	अणु "HPOVOL", शून्य, "HPOVOL MIXR" पूर्ण,
	अणु "HPO MIX", "DAC1 Switch", "DAC 1" पूर्ण,
	अणु "HPO MIX", "HPVOL Switch", "HPOVOL" पूर्ण,

	अणु "LOUT MIX", "DAC L1 Switch", "DAC L1" पूर्ण,
	अणु "LOUT MIX", "DAC R1 Switch", "DAC R1" पूर्ण,
	अणु "LOUT MIX", "OUTMIX L Switch", "OUT MIXL" पूर्ण,
	अणु "LOUT MIX", "OUTMIX R Switch", "OUT MIXR" पूर्ण,

	अणु "PDM1 L Mux", "Stereo DAC", "Stereo DAC MIXL" पूर्ण,
	अणु "PDM1 L Mux", "Mono DAC", "Mono DAC MIXL" पूर्ण,
	अणु "PDM1 L Mux", शून्य, "PDM1 Power" पूर्ण,
	अणु "PDM1 R Mux", "Stereo DAC", "Stereo DAC MIXR" पूर्ण,
	अणु "PDM1 R Mux", "Mono DAC", "Mono DAC MIXR" पूर्ण,
	अणु "PDM1 R Mux", शून्य, "PDM1 Power" पूर्ण,

	अणु "HP Amp", शून्य, "HPO MIX" पूर्ण,
	अणु "HP Amp", शून्य, "Mic Det Power" पूर्ण,
	अणु "HPOL", शून्य, "HP Amp" पूर्ण,
	अणु "HPOL", शून्य, "HP L Amp" पूर्ण,
	अणु "HPOL", शून्य, "Improve HP Amp Drv" पूर्ण,
	अणु "HPOR", शून्य, "HP Amp" पूर्ण,
	अणु "HPOR", शून्य, "HP R Amp" पूर्ण,
	अणु "HPOR", शून्य, "Improve HP Amp Drv" पूर्ण,

	अणु "LOUT Amp", शून्य, "LOUT MIX" पूर्ण,
	अणु "LOUT L Playback", "Switch", "LOUT Amp" पूर्ण,
	अणु "LOUT R Playback", "Switch", "LOUT Amp" पूर्ण,
	अणु "LOUTL", शून्य, "LOUT L Playback" पूर्ण,
	अणु "LOUTR", शून्य, "LOUT R Playback" पूर्ण,
	अणु "LOUTL", शून्य, "Improve HP Amp Drv" पूर्ण,
	अणु "LOUTR", शून्य, "Improve HP Amp Drv" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5670_specअगरic_dapm_routes[] = अणु
	अणु "PDM2 L Mux", "Stereo DAC", "Stereo DAC MIXL" पूर्ण,
	अणु "PDM2 L Mux", "Mono DAC", "Mono DAC MIXL" पूर्ण,
	अणु "PDM2 L Mux", शून्य, "PDM2 Power" पूर्ण,
	अणु "PDM2 R Mux", "Stereo DAC", "Stereo DAC MIXR" पूर्ण,
	अणु "PDM2 R Mux", "Mono DAC", "Mono DAC MIXR" पूर्ण,
	अणु "PDM2 R Mux", शून्य, "PDM2 Power" पूर्ण,
	अणु "PDM1L", शून्य, "PDM1 L Mux" पूर्ण,
	अणु "PDM1R", शून्य, "PDM1 R Mux" पूर्ण,
	अणु "PDM2L", शून्य, "PDM2 L Mux" पूर्ण,
	अणु "PDM2R", शून्य, "PDM2 R Mux" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5672_specअगरic_dapm_routes[] = अणु
	अणु "SPO Amp", शून्य, "PDM1 L Mux" पूर्ण,
	अणु "SPO Amp", शून्य, "PDM1 R Mux" पूर्ण,
	अणु "SPOLP", शून्य, "SPO Amp" पूर्ण,
	अणु "SPOLN", शून्य, "SPO Amp" पूर्ण,
	अणु "SPORP", शून्य, "SPO Amp" पूर्ण,
	अणु "SPORN", शून्य, "SPO Amp" पूर्ण,
पूर्ण;

अटल पूर्णांक rt5670_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val_len = 0, val_clk, mask_clk;
	पूर्णांक pre_भाग, bclk_ms, frame_size;

	rt5670->lrck[dai->id] = params_rate(params);
	pre_भाग = rl6231_get_clk_info(rt5670->sysclk, rt5670->lrck[dai->id]);
	अगर (pre_भाग < 0) अणु
		dev_err(component->dev, "Unsupported clock setting %d for DAI %d\n",
			rt5670->lrck[dai->id], dai->id);
		वापस -EINVAL;
	पूर्ण
	frame_size = snd_soc_params_to_frame_size(params);
	अगर (frame_size < 0) अणु
		dev_err(component->dev, "Unsupported frame size: %d\n", frame_size);
		वापस -EINVAL;
	पूर्ण
	bclk_ms = frame_size > 32;
	rt5670->bclk[dai->id] = rt5670->lrck[dai->id] * (32 << bclk_ms);

	dev_dbg(dai->dev, "bclk is %dHz and lrck is %dHz\n",
		rt5670->bclk[dai->id], rt5670->lrck[dai->id]);
	dev_dbg(dai->dev, "bclk_ms is %d and pre_div is %d for iis %d\n",
				bclk_ms, pre_भाग, dai->id);

	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		val_len |= RT5670_I2S_DL_20;
		अवरोध;
	हाल 24:
		val_len |= RT5670_I2S_DL_24;
		अवरोध;
	हाल 8:
		val_len |= RT5670_I2S_DL_8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT5670_AIF1:
		mask_clk = RT5670_I2S_BCLK_MS1_MASK | RT5670_I2S_PD1_MASK;
		val_clk = bclk_ms << RT5670_I2S_BCLK_MS1_SFT |
			pre_भाग << RT5670_I2S_PD1_SFT;
		snd_soc_component_update_bits(component, RT5670_I2S1_SDP,
			RT5670_I2S_DL_MASK, val_len);
		snd_soc_component_update_bits(component, RT5670_ADDA_CLK1, mask_clk, val_clk);
		अवरोध;
	हाल RT5670_AIF2:
		mask_clk = RT5670_I2S_BCLK_MS2_MASK | RT5670_I2S_PD2_MASK;
		val_clk = bclk_ms << RT5670_I2S_BCLK_MS2_SFT |
			pre_भाग << RT5670_I2S_PD2_SFT;
		snd_soc_component_update_bits(component, RT5670_I2S2_SDP,
			RT5670_I2S_DL_MASK, val_len);
		snd_soc_component_update_bits(component, RT5670_ADDA_CLK1, mask_clk, val_clk);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5670_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		rt5670->master[dai->id] = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		reg_val |= RT5670_I2S_MS_S;
		rt5670->master[dai->id] = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		reg_val |= RT5670_I2S_BP_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT5670_I2S_DF_LEFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT5670_I2S_DF_PCM_A;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		reg_val |= RT5670_I2S_DF_PCM_B;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT5670_AIF1:
		snd_soc_component_update_bits(component, RT5670_I2S1_SDP,
			RT5670_I2S_MS_MASK | RT5670_I2S_BP_MASK |
			RT5670_I2S_DF_MASK, reg_val);
		अवरोध;
	हाल RT5670_AIF2:
		snd_soc_component_update_bits(component, RT5670_I2S2_SDP,
			RT5670_I2S_MS_MASK | RT5670_I2S_BP_MASK |
			RT5670_I2S_DF_MASK, reg_val);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt5670_set_codec_sysclk(काष्ठा snd_soc_component *component, पूर्णांक clk_id,
				   पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;

	चयन (clk_id) अणु
	हाल RT5670_SCLK_S_MCLK:
		reg_val |= RT5670_SCLK_SRC_MCLK;
		अवरोध;
	हाल RT5670_SCLK_S_PLL1:
		reg_val |= RT5670_SCLK_SRC_PLL1;
		अवरोध;
	हाल RT5670_SCLK_S_RCCLK:
		reg_val |= RT5670_SCLK_SRC_RCCLK;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_update_bits(component, RT5670_GLB_CLK,
		RT5670_SCLK_SRC_MASK, reg_val);
	rt5670->sysclk = freq;
	अगर (clk_id != RT5670_SCLK_S_RCCLK)
		rt5670->sysclk_src = clk_id;

	dev_dbg(component->dev, "Sysclk : %dHz clock id : %d\n", freq, clk_id);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5670_set_dai_pll(काष्ठा snd_soc_dai *dai, पूर्णांक pll_id, पूर्णांक source,
			अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);
	काष्ठा rl6231_pll_code pll_code;
	पूर्णांक ret;

	अगर (source == rt5670->pll_src && freq_in == rt5670->pll_in &&
	    freq_out == rt5670->pll_out)
		वापस 0;

	अगर (!freq_in || !freq_out) अणु
		dev_dbg(component->dev, "PLL disabled\n");

		rt5670->pll_in = 0;
		rt5670->pll_out = 0;
		snd_soc_component_update_bits(component, RT5670_GLB_CLK,
			RT5670_SCLK_SRC_MASK, RT5670_SCLK_SRC_MCLK);
		वापस 0;
	पूर्ण

	चयन (source) अणु
	हाल RT5670_PLL1_S_MCLK:
		snd_soc_component_update_bits(component, RT5670_GLB_CLK,
			RT5670_PLL1_SRC_MASK, RT5670_PLL1_SRC_MCLK);
		अवरोध;
	हाल RT5670_PLL1_S_BCLK1:
	हाल RT5670_PLL1_S_BCLK2:
	हाल RT5670_PLL1_S_BCLK3:
	हाल RT5670_PLL1_S_BCLK4:
		चयन (dai->id) अणु
		हाल RT5670_AIF1:
			snd_soc_component_update_bits(component, RT5670_GLB_CLK,
				RT5670_PLL1_SRC_MASK, RT5670_PLL1_SRC_BCLK1);
			अवरोध;
		हाल RT5670_AIF2:
			snd_soc_component_update_bits(component, RT5670_GLB_CLK,
				RT5670_PLL1_SRC_MASK, RT5670_PLL1_SRC_BCLK2);
			अवरोध;
		शेष:
			dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
			वापस -EINVAL;
		पूर्ण
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

	snd_soc_component_ग_लिखो(component, RT5670_PLL_CTRL1,
		pll_code.n_code << RT5670_PLL_N_SFT | pll_code.k_code);
	snd_soc_component_ग_लिखो(component, RT5670_PLL_CTRL2,
		((pll_code.m_bp ? 0 : pll_code.m_code) << RT5670_PLL_M_SFT) |
		(pll_code.m_bp << RT5670_PLL_M_BP_SFT));

	rt5670->pll_in = freq_in;
	rt5670->pll_out = freq_out;
	rt5670->pll_src = source;

	वापस 0;
पूर्ण

अटल पूर्णांक rt5670_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
			अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक val = 0;

	अगर (rx_mask || tx_mask)
		val |= (1 << 14);

	चयन (slots) अणु
	हाल 4:
		val |= (1 << 12);
		अवरोध;
	हाल 6:
		val |= (2 << 12);
		अवरोध;
	हाल 8:
		val |= (3 << 12);
		अवरोध;
	हाल 2:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (slot_width) अणु
	हाल 20:
		val |= (1 << 10);
		अवरोध;
	हाल 24:
		val |= (2 << 10);
		अवरोध;
	हाल 32:
		val |= (3 << 10);
		अवरोध;
	हाल 16:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, RT5670_TDM_CTRL_1, 0x7c00, val);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5670_set_bclk_ratio(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक ratio)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	dev_dbg(component->dev, "%s ratio=%d\n", __func__, ratio);
	अगर (dai->id != RT5670_AIF1)
		वापस 0;

	अगर ((ratio % 50) == 0)
		snd_soc_component_update_bits(component, RT5670_GEN_CTRL3,
			RT5670_TDM_DATA_MODE_SEL, RT5670_TDM_DATA_MODE_50FS);
	अन्यथा
		snd_soc_component_update_bits(component, RT5670_GEN_CTRL3,
			RT5670_TDM_DATA_MODE_SEL, RT5670_TDM_DATA_MODE_NOR);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5670_set_bias_level(काष्ठा snd_soc_component *component,
			क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		अगर (SND_SOC_BIAS_STANDBY == snd_soc_component_get_bias_level(component)) अणु
			snd_soc_component_update_bits(component, RT5670_PWR_ANLG1,
				RT5670_PWR_VREF1 | RT5670_PWR_MB |
				RT5670_PWR_BG | RT5670_PWR_VREF2,
				RT5670_PWR_VREF1 | RT5670_PWR_MB |
				RT5670_PWR_BG | RT5670_PWR_VREF2);
			mdelay(10);
			snd_soc_component_update_bits(component, RT5670_PWR_ANLG1,
				RT5670_PWR_FV1 | RT5670_PWR_FV2,
				RT5670_PWR_FV1 | RT5670_PWR_FV2);
			snd_soc_component_update_bits(component, RT5670_CHARGE_PUMP,
				RT5670_OSW_L_MASK | RT5670_OSW_R_MASK,
				RT5670_OSW_L_DIS | RT5670_OSW_R_DIS);
			snd_soc_component_update_bits(component, RT5670_DIG_MISC, 0x1, 0x1);
			snd_soc_component_update_bits(component, RT5670_PWR_ANLG1,
				RT5670_LDO_SEL_MASK, 0x5);
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		snd_soc_component_update_bits(component, RT5670_PWR_ANLG1,
				RT5670_PWR_VREF1 | RT5670_PWR_VREF2 |
				RT5670_PWR_FV1 | RT5670_PWR_FV2, 0);
		snd_soc_component_update_bits(component, RT5670_PWR_ANLG1,
				RT5670_LDO_SEL_MASK, 0x3);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		अगर (rt5670->jd_mode)
			snd_soc_component_update_bits(component, RT5670_PWR_ANLG1,
				RT5670_PWR_VREF1 | RT5670_PWR_MB |
				RT5670_PWR_BG | RT5670_PWR_VREF2 |
				RT5670_PWR_FV1 | RT5670_PWR_FV2,
				RT5670_PWR_MB | RT5670_PWR_BG);
		अन्यथा
			snd_soc_component_update_bits(component, RT5670_PWR_ANLG1,
				RT5670_PWR_VREF1 | RT5670_PWR_MB |
				RT5670_PWR_BG | RT5670_PWR_VREF2 |
				RT5670_PWR_FV1 | RT5670_PWR_FV2, 0);

		snd_soc_component_update_bits(component, RT5670_DIG_MISC, 0x1, 0x0);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5670_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);

	चयन (snd_soc_component_पढ़ो(component, RT5670_RESET) & RT5670_ID_MASK) अणु
	हाल RT5670_ID_5670:
	हाल RT5670_ID_5671:
		snd_soc_dapm_new_controls(dapm,
			rt5670_specअगरic_dapm_widमाला_लो,
			ARRAY_SIZE(rt5670_specअगरic_dapm_widमाला_लो));
		snd_soc_dapm_add_routes(dapm,
			rt5670_specअगरic_dapm_routes,
			ARRAY_SIZE(rt5670_specअगरic_dapm_routes));
		अवरोध;
	हाल RT5670_ID_5672:
		snd_soc_dapm_new_controls(dapm,
			rt5672_specअगरic_dapm_widमाला_लो,
			ARRAY_SIZE(rt5672_specअगरic_dapm_widमाला_लो));
		snd_soc_dapm_add_routes(dapm,
			rt5672_specअगरic_dapm_routes,
			ARRAY_SIZE(rt5672_specअगरic_dapm_routes));
		अवरोध;
	शेष:
		dev_err(component->dev,
			"The driver is for RT5670 RT5671 or RT5672 only\n");
		वापस -ENODEV;
	पूर्ण
	rt5670->component = component;

	वापस 0;
पूर्ण

अटल व्योम rt5670_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);

	regmap_ग_लिखो(rt5670->regmap, RT5670_RESET, 0);
	snd_soc_jack_मुक्त_gpios(rt5670->jack, 1, &rt5670->hp_gpio);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rt5670_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt5670->regmap, true);
	regcache_mark_dirty(rt5670->regmap);
	वापस 0;
पूर्ण

अटल पूर्णांक rt5670_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt5670->regmap, false);
	regcache_sync(rt5670->regmap);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा rt5670_suspend शून्य
#घोषणा rt5670_resume शून्य
#पूर्ण_अगर

#घोषणा RT5670_STEREO_RATES SNDRV_PCM_RATE_8000_96000
#घोषणा RT5670_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S8)

अटल स्थिर काष्ठा snd_soc_dai_ops rt5670_aअगर_dai_ops = अणु
	.hw_params = rt5670_hw_params,
	.set_fmt = rt5670_set_dai_fmt,
	.set_tdm_slot = rt5670_set_tdm_slot,
	.set_pll = rt5670_set_dai_pll,
	.set_bclk_ratio = rt5670_set_bclk_ratio,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt5670_dai[] = अणु
	अणु
		.name = "rt5670-aif1",
		.id = RT5670_AIF1,
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5670_STEREO_RATES,
			.क्रमmats = RT5670_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5670_STEREO_RATES,
			.क्रमmats = RT5670_FORMATS,
		पूर्ण,
		.ops = &rt5670_aअगर_dai_ops,
		.symmetric_rate = 1,
	पूर्ण,
	अणु
		.name = "rt5670-aif2",
		.id = RT5670_AIF2,
		.playback = अणु
			.stream_name = "AIF2 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5670_STEREO_RATES,
			.क्रमmats = RT5670_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF2 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT5670_STEREO_RATES,
			.क्रमmats = RT5670_FORMATS,
		पूर्ण,
		.ops = &rt5670_aअगर_dai_ops,
		.symmetric_rate = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_rt5670 = अणु
	.probe			= rt5670_probe,
	.हटाओ			= rt5670_हटाओ,
	.suspend		= rt5670_suspend,
	.resume			= rt5670_resume,
	.set_bias_level		= rt5670_set_bias_level,
	.set_sysclk		= rt5670_set_codec_sysclk,
	.controls		= rt5670_snd_controls,
	.num_controls		= ARRAY_SIZE(rt5670_snd_controls),
	.dapm_widमाला_लो		= rt5670_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(rt5670_dapm_widमाला_लो),
	.dapm_routes		= rt5670_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(rt5670_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt5670_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
	.max_रेजिस्टर = RT5670_VENDOR_ID2 + 1 + (ARRAY_SIZE(rt5670_ranges) *
					       RT5670_PR_SPACING),
	.अस्थिर_reg = rt5670_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = rt5670_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = rt5670_reg,
	.num_reg_शेषs = ARRAY_SIZE(rt5670_reg),
	.ranges = rt5670_ranges,
	.num_ranges = ARRAY_SIZE(rt5670_ranges),
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id rt5670_i2c_id[] = अणु
	अणु "rt5670", 0 पूर्ण,
	अणु "rt5671", 0 पूर्ण,
	अणु "rt5672", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt5670_i2c_id);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id rt5670_acpi_match[] = अणु
	अणु "10EC5670", 0पूर्ण,
	अणु "10EC5672", 0पूर्ण,
	अणु "10EC5640", 0पूर्ण, /* quirk */
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rt5670_acpi_match);
#पूर्ण_अगर

अटल पूर्णांक rt5670_quirk_cb(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	rt5670_quirk = (अचिन्हित दीर्घ)id->driver_data;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id dmi_platक्रमm_पूर्णांकel_quirks[] = अणु
	अणु
		.callback = rt5670_quirk_cb,
		.ident = "Intel Braswell",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Intel Corporation"),
			DMI_MATCH(DMI_BOARD_NAME, "Braswell CRB"),
		पूर्ण,
		.driver_data = (अचिन्हित दीर्घ *)(RT5670_DMIC_EN |
						 RT5670_DMIC1_IN2P |
						 RT5670_GPIO1_IS_IRQ |
						 RT5670_JD_MODE1),
	पूर्ण,
	अणु
		.callback = rt5670_quirk_cb,
		.ident = "Dell Wyse 3040",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Wyse 3040"),
		पूर्ण,
		.driver_data = (अचिन्हित दीर्घ *)(RT5670_DMIC_EN |
						 RT5670_DMIC1_IN2P |
						 RT5670_GPIO1_IS_IRQ |
						 RT5670_JD_MODE1),
	पूर्ण,
	अणु
		.callback = rt5670_quirk_cb,
		.ident = "Lenovo Thinkpad Tablet 8",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad 8"),
		पूर्ण,
		.driver_data = (अचिन्हित दीर्घ *)(RT5670_DMIC_EN |
						 RT5670_DMIC2_INR |
						 RT5670_GPIO1_IS_IRQ |
						 RT5670_JD_MODE1),
	पूर्ण,
	अणु
		.callback = rt5670_quirk_cb,
		.ident = "Lenovo Thinkpad Tablet 10",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad 10"),
		पूर्ण,
		.driver_data = (अचिन्हित दीर्घ *)(RT5670_DMIC_EN |
						 RT5670_DMIC1_IN2P |
						 RT5670_GPIO1_IS_IRQ |
						 RT5670_JD_MODE1),
	पूर्ण,
	अणु
		.callback = rt5670_quirk_cb,
		.ident = "Lenovo Thinkpad Tablet 10",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad Tablet B"),
		पूर्ण,
		.driver_data = (अचिन्हित दीर्घ *)(RT5670_DMIC_EN |
						 RT5670_DMIC1_IN2P |
						 RT5670_GPIO1_IS_IRQ |
						 RT5670_JD_MODE1),
	पूर्ण,
	अणु
		.callback = rt5670_quirk_cb,
		.ident = "Lenovo Miix 2 10",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "Lenovo Miix 2 10"),
		पूर्ण,
		.driver_data = (अचिन्हित दीर्घ *)(RT5670_DMIC_EN |
						 RT5670_DMIC1_IN2P |
						 RT5670_GPIO1_IS_EXT_SPK_EN |
						 RT5670_JD_MODE2),
	पूर्ण,
	अणु
		.callback = rt5670_quirk_cb,
		.ident = "Dell Venue 8 Pro 5855",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Venue 8 Pro 5855"),
		पूर्ण,
		.driver_data = (अचिन्हित दीर्घ *)(RT5670_DMIC_EN |
						 RT5670_DMIC2_INR |
						 RT5670_GPIO1_IS_IRQ |
						 RT5670_JD_MODE3),
	पूर्ण,
	अणु
		.callback = rt5670_quirk_cb,
		.ident = "Dell Venue 10 Pro 5055",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Venue 10 Pro 5055"),
		पूर्ण,
		.driver_data = (अचिन्हित दीर्घ *)(RT5670_DMIC_EN |
						 RT5670_DMIC2_INR |
						 RT5670_GPIO1_IS_IRQ |
						 RT5670_JD_MODE1),
	पूर्ण,
	अणु
		.callback = rt5670_quirk_cb,
		.ident = "Aegex 10 tablet (RU2)",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "AEGEX"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "RU2"),
		पूर्ण,
		.driver_data = (अचिन्हित दीर्घ *)(RT5670_DMIC_EN |
						 RT5670_DMIC2_INR |
						 RT5670_GPIO1_IS_IRQ |
						 RT5670_JD_MODE3),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर अक्षर *rt5670_components(व्योम)
अणु
	अचिन्हित दीर्घ quirk;
	bool dmic1 = false;
	bool dmic2 = false;
	bool dmic3 = false;

	अगर (quirk_override) अणु
		quirk = quirk_override;
	पूर्ण अन्यथा अणु
		dmi_check_प्रणाली(dmi_platक्रमm_पूर्णांकel_quirks);
		quirk = rt5670_quirk;
	पूर्ण

	अगर ((quirk & RT5670_DMIC1_IN2P) ||
	    (quirk & RT5670_DMIC1_GPIO6) ||
	    (quirk & RT5670_DMIC1_GPIO7))
		dmic1 = true;

	अगर ((quirk & RT5670_DMIC2_INR) ||
	    (quirk & RT5670_DMIC2_GPIO8))
		dmic2 = true;

	अगर (quirk & RT5670_DMIC3_GPIO5)
		dmic3 = true;

	अगर (dmic1 && dmic2)
		वापस "cfg-spk:2 cfg-mic:dmics12";
	अन्यथा अगर (dmic1)
		वापस "cfg-spk:2 cfg-mic:dmic1";
	अन्यथा अगर (dmic2)
		वापस "cfg-spk:2 cfg-mic:dmic2";
	अन्यथा अगर (dmic3)
		वापस "cfg-spk:2 cfg-mic:dmic3";

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(rt5670_components);

अटल पूर्णांक rt5670_i2c_probe(काष्ठा i2c_client *i2c,
		    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rt5670_priv *rt5670;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	rt5670 = devm_kzalloc(&i2c->dev,
				माप(काष्ठा rt5670_priv),
				GFP_KERNEL);
	अगर (शून्य == rt5670)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, rt5670);

	dmi_check_प्रणाली(dmi_platक्रमm_पूर्णांकel_quirks);
	अगर (quirk_override) अणु
		dev_info(&i2c->dev, "Overriding quirk 0x%x => 0x%x\n",
			 (अचिन्हित पूर्णांक)rt5670_quirk, quirk_override);
		rt5670_quirk = quirk_override;
	पूर्ण

	अगर (rt5670_quirk & RT5670_GPIO1_IS_IRQ) अणु
		rt5670->gpio1_is_irq = true;
		dev_info(&i2c->dev, "quirk GPIO1 is IRQ\n");
	पूर्ण
	अगर (rt5670_quirk & RT5670_GPIO1_IS_EXT_SPK_EN) अणु
		rt5670->gpio1_is_ext_spk_en = true;
		dev_info(&i2c->dev, "quirk GPIO1 is external speaker enable\n");
	पूर्ण
	अगर (rt5670_quirk & RT5670_IN2_DIFF) अणु
		rt5670->in2_dअगरf = true;
		dev_info(&i2c->dev, "quirk IN2_DIFF\n");
	पूर्ण
	अगर (rt5670_quirk & RT5670_DMIC_EN) अणु
		rt5670->dmic_en = true;
		dev_info(&i2c->dev, "quirk DMIC enabled\n");
	पूर्ण
	अगर (rt5670_quirk & RT5670_DMIC1_IN2P) अणु
		rt5670->dmic1_data_pin = RT5670_DMIC_DATA_IN2P;
		dev_info(&i2c->dev, "quirk DMIC1 on IN2P pin\n");
	पूर्ण
	अगर (rt5670_quirk & RT5670_DMIC1_GPIO6) अणु
		rt5670->dmic1_data_pin = RT5670_DMIC_DATA_GPIO6;
		dev_info(&i2c->dev, "quirk DMIC1 on GPIO6 pin\n");
	पूर्ण
	अगर (rt5670_quirk & RT5670_DMIC1_GPIO7) अणु
		rt5670->dmic1_data_pin = RT5670_DMIC_DATA_GPIO7;
		dev_info(&i2c->dev, "quirk DMIC1 on GPIO7 pin\n");
	पूर्ण
	अगर (rt5670_quirk & RT5670_DMIC2_INR) अणु
		rt5670->dmic2_data_pin = RT5670_DMIC_DATA_IN3N;
		dev_info(&i2c->dev, "quirk DMIC2 on INR pin\n");
	पूर्ण
	अगर (rt5670_quirk & RT5670_DMIC2_GPIO8) अणु
		rt5670->dmic2_data_pin = RT5670_DMIC_DATA_GPIO8;
		dev_info(&i2c->dev, "quirk DMIC2 on GPIO8 pin\n");
	पूर्ण
	अगर (rt5670_quirk & RT5670_DMIC3_GPIO5) अणु
		rt5670->dmic3_data_pin = RT5670_DMIC_DATA_GPIO5;
		dev_info(&i2c->dev, "quirk DMIC3 on GPIO5 pin\n");
	पूर्ण

	अगर (rt5670_quirk & RT5670_JD_MODE1) अणु
		rt5670->jd_mode = 1;
		dev_info(&i2c->dev, "quirk JD mode 1\n");
	पूर्ण
	अगर (rt5670_quirk & RT5670_JD_MODE2) अणु
		rt5670->jd_mode = 2;
		dev_info(&i2c->dev, "quirk JD mode 2\n");
	पूर्ण
	अगर (rt5670_quirk & RT5670_JD_MODE3) अणु
		rt5670->jd_mode = 3;
		dev_info(&i2c->dev, "quirk JD mode 3\n");
	पूर्ण

	/*
	 * Enable the emulated "DAC1 Playback Switch" by शेष to aव्योम
	 * muting the output with older UCM profiles.
	 */
	rt5670->dac1_playback_चयन_l = true;
	rt5670->dac1_playback_चयन_r = true;
	/* The Power-On-Reset values क्रम the DAC1 mixer have the DAC1 input enabled. */
	rt5670->dac1_mixl_dac1_चयन = true;
	rt5670->dac1_mixr_dac1_चयन = true;

	rt5670->regmap = devm_regmap_init_i2c(i2c, &rt5670_regmap);
	अगर (IS_ERR(rt5670->regmap)) अणु
		ret = PTR_ERR(rt5670->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	regmap_पढ़ो(rt5670->regmap, RT5670_VENDOR_ID2, &val);
	अगर (val != RT5670_DEVICE_ID) अणु
		dev_err(&i2c->dev,
			"Device with ID register %#x is not rt5670/72\n", val);
		वापस -ENODEV;
	पूर्ण

	regmap_ग_लिखो(rt5670->regmap, RT5670_RESET, 0);
	regmap_update_bits(rt5670->regmap, RT5670_PWR_ANLG1,
		RT5670_PWR_HP_L | RT5670_PWR_HP_R |
		RT5670_PWR_VREF2, RT5670_PWR_VREF2);
	msleep(100);

	regmap_ग_लिखो(rt5670->regmap, RT5670_RESET, 0);

	regmap_पढ़ो(rt5670->regmap, RT5670_VENDOR_ID, &val);
	अगर (val >= 4)
		regmap_ग_लिखो(rt5670->regmap, RT5670_GPIO_CTRL3, 0x0980);
	अन्यथा
		regmap_ग_लिखो(rt5670->regmap, RT5670_GPIO_CTRL3, 0x0d00);

	ret = regmap_रेजिस्टर_patch(rt5670->regmap, init_list,
				    ARRAY_SIZE(init_list));
	अगर (ret != 0)
		dev_warn(&i2c->dev, "Failed to apply regmap patch: %d\n", ret);

	regmap_update_bits(rt5670->regmap, RT5670_DIG_MISC,
				 RT5670_MCLK_DET, RT5670_MCLK_DET);

	अगर (rt5670->in2_dअगरf)
		regmap_update_bits(rt5670->regmap, RT5670_IN2,
					RT5670_IN_DF2, RT5670_IN_DF2);

	अगर (rt5670->gpio1_is_irq) अणु
		/* क्रम push button */
		regmap_ग_लिखो(rt5670->regmap, RT5670_IL_CMD, 0x0000);
		regmap_ग_लिखो(rt5670->regmap, RT5670_IL_CMD2, 0x0010);
		regmap_ग_लिखो(rt5670->regmap, RT5670_IL_CMD3, 0x0014);
		/* क्रम irq */
		regmap_update_bits(rt5670->regmap, RT5670_GPIO_CTRL1,
				   RT5670_GP1_PIN_MASK, RT5670_GP1_PIN_IRQ);
		regmap_update_bits(rt5670->regmap, RT5670_GPIO_CTRL2,
				   RT5670_GP1_PF_MASK, RT5670_GP1_PF_OUT);
	पूर्ण

	अगर (rt5670->gpio1_is_ext_spk_en) अणु
		regmap_update_bits(rt5670->regmap, RT5670_GPIO_CTRL1,
				   RT5670_GP1_PIN_MASK, RT5670_GP1_PIN_GPIO1);
		regmap_update_bits(rt5670->regmap, RT5670_GPIO_CTRL2,
				   RT5670_GP1_PF_MASK, RT5670_GP1_PF_OUT);
	पूर्ण

	अगर (rt5670->jd_mode) अणु
		regmap_update_bits(rt5670->regmap, RT5670_GLB_CLK,
				   RT5670_SCLK_SRC_MASK, RT5670_SCLK_SRC_RCCLK);
		rt5670->sysclk = 0;
		rt5670->sysclk_src = RT5670_SCLK_S_RCCLK;
		regmap_update_bits(rt5670->regmap, RT5670_PWR_ANLG1,
				   RT5670_PWR_MB, RT5670_PWR_MB);
		regmap_update_bits(rt5670->regmap, RT5670_PWR_ANLG2,
				   RT5670_PWR_JD1, RT5670_PWR_JD1);
		regmap_update_bits(rt5670->regmap, RT5670_IRQ_CTRL1,
				   RT5670_JD1_1_EN_MASK, RT5670_JD1_1_EN);
		regmap_update_bits(rt5670->regmap, RT5670_JD_CTRL3,
				   RT5670_JD_TRI_CBJ_SEL_MASK |
				   RT5670_JD_TRI_HPO_SEL_MASK,
				   RT5670_JD_CBJ_JD1_1 | RT5670_JD_HPO_JD1_1);
		चयन (rt5670->jd_mode) अणु
		हाल 1:
			regmap_update_bits(rt5670->regmap, RT5670_A_JD_CTRL1,
					   RT5670_JD1_MODE_MASK,
					   RT5670_JD1_MODE_0);
			अवरोध;
		हाल 2:
			regmap_update_bits(rt5670->regmap, RT5670_A_JD_CTRL1,
					   RT5670_JD1_MODE_MASK,
					   RT5670_JD1_MODE_1);
			अवरोध;
		हाल 3:
			regmap_update_bits(rt5670->regmap, RT5670_A_JD_CTRL1,
					   RT5670_JD1_MODE_MASK,
					   RT5670_JD1_MODE_2);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (rt5670->dmic_en) अणु
		regmap_update_bits(rt5670->regmap, RT5670_GPIO_CTRL1,
				   RT5670_GP2_PIN_MASK,
				   RT5670_GP2_PIN_DMIC1_SCL);

		चयन (rt5670->dmic1_data_pin) अणु
		हाल RT5670_DMIC_DATA_IN2P:
			regmap_update_bits(rt5670->regmap, RT5670_DMIC_CTRL1,
					   RT5670_DMIC_1_DP_MASK,
					   RT5670_DMIC_1_DP_IN2P);
			अवरोध;

		हाल RT5670_DMIC_DATA_GPIO6:
			regmap_update_bits(rt5670->regmap, RT5670_DMIC_CTRL1,
					   RT5670_DMIC_1_DP_MASK,
					   RT5670_DMIC_1_DP_GPIO6);
			regmap_update_bits(rt5670->regmap, RT5670_GPIO_CTRL1,
					   RT5670_GP6_PIN_MASK,
					   RT5670_GP6_PIN_DMIC1_SDA);
			अवरोध;

		हाल RT5670_DMIC_DATA_GPIO7:
			regmap_update_bits(rt5670->regmap, RT5670_DMIC_CTRL1,
					   RT5670_DMIC_1_DP_MASK,
					   RT5670_DMIC_1_DP_GPIO7);
			regmap_update_bits(rt5670->regmap, RT5670_GPIO_CTRL1,
					   RT5670_GP7_PIN_MASK,
					   RT5670_GP7_PIN_DMIC1_SDA);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		चयन (rt5670->dmic2_data_pin) अणु
		हाल RT5670_DMIC_DATA_IN3N:
			regmap_update_bits(rt5670->regmap, RT5670_DMIC_CTRL1,
					   RT5670_DMIC_2_DP_MASK,
					   RT5670_DMIC_2_DP_IN3N);
			अवरोध;

		हाल RT5670_DMIC_DATA_GPIO8:
			regmap_update_bits(rt5670->regmap, RT5670_DMIC_CTRL1,
					   RT5670_DMIC_2_DP_MASK,
					   RT5670_DMIC_2_DP_GPIO8);
			regmap_update_bits(rt5670->regmap, RT5670_GPIO_CTRL1,
					   RT5670_GP8_PIN_MASK,
					   RT5670_GP8_PIN_DMIC2_SDA);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		चयन (rt5670->dmic3_data_pin) अणु
		हाल RT5670_DMIC_DATA_GPIO5:
			regmap_update_bits(rt5670->regmap, RT5670_DMIC_CTRL2,
					   RT5670_DMIC_3_DP_MASK,
					   RT5670_DMIC_3_DP_GPIO5);
			regmap_update_bits(rt5670->regmap, RT5670_GPIO_CTRL1,
					   RT5670_GP5_PIN_MASK,
					   RT5670_GP5_PIN_DMIC3_SDA);
			अवरोध;

		हाल RT5670_DMIC_DATA_GPIO9:
		हाल RT5670_DMIC_DATA_GPIO10:
			dev_err(&i2c->dev,
				"Always use GPIO5 as DMIC3 data pin\n");
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

	पूर्ण

	pm_runसमय_enable(&i2c->dev);
	pm_request_idle(&i2c->dev);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_rt5670,
			rt5670_dai, ARRAY_SIZE(rt5670_dai));
	अगर (ret < 0)
		जाओ err;

	pm_runसमय_put(&i2c->dev);

	वापस 0;
err:
	pm_runसमय_disable(&i2c->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक rt5670_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	pm_runसमय_disable(&i2c->dev);

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver rt5670_i2c_driver = अणु
	.driver = अणु
		.name = "rt5670",
		.acpi_match_table = ACPI_PTR(rt5670_acpi_match),
	पूर्ण,
	.probe = rt5670_i2c_probe,
	.हटाओ   = rt5670_i2c_हटाओ,
	.id_table = rt5670_i2c_id,
पूर्ण;

module_i2c_driver(rt5670_i2c_driver);

MODULE_DESCRIPTION("ASoC RT5670 driver");
MODULE_AUTHOR("Bard Liao <bardliao@realtek.com>");
MODULE_LICENSE("GPL v2");
