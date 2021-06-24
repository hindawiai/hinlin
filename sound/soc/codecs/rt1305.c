<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rt1305.c  --  RT1305 ALSA SoC amplअगरier component driver
 *
 * Copyright 2018 Realtek Semiconductor Corp.
 * Author: Shuming Fan <shumingf@realtek.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/acpi.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/firmware.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "rl6231.h"
#समावेश "rt1305.h"


#घोषणा RT1305_PR_RANGE_BASE (0xff + 1)
#घोषणा RT1305_PR_SPACING 0x100

#घोषणा RT1305_PR_BASE (RT1305_PR_RANGE_BASE + (0 * RT1305_PR_SPACING))


अटल स्थिर काष्ठा regmap_range_cfg rt1305_ranges[] = अणु
	अणु
		.name = "PR",
		.range_min = RT1305_PR_BASE,
		.range_max = RT1305_PR_BASE + 0xff,
		.selector_reg = RT1305_PRIV_INDEX,
		.selector_mask = 0xff,
		.selector_shअगरt = 0x0,
		.winकरोw_start = RT1305_PRIV_DATA,
		.winकरोw_len = 0x1,
	पूर्ण,
पूर्ण;


अटल स्थिर काष्ठा reg_sequence init_list[] = अणु

	अणु RT1305_PR_BASE + 0xcf, 0x5548 पूर्ण,
	अणु RT1305_PR_BASE + 0x5d, 0x0442 पूर्ण,
	अणु RT1305_PR_BASE + 0xc1, 0x0320 पूर्ण,

	अणु RT1305_POWER_STATUS, 0x0000 पूर्ण,

	अणु RT1305_SPK_TEMP_PROTECTION_1, 0xd6de पूर्ण,
	अणु RT1305_SPK_TEMP_PROTECTION_2, 0x0707 पूर्ण,
	अणु RT1305_SPK_TEMP_PROTECTION_3, 0x4090 पूर्ण,

	अणु RT1305_DAC_SET_1, 0xdfdf पूर्ण,	/* 4 ohm 2W  */
	अणु RT1305_ADC_SET_3, 0x0219 पूर्ण,
	अणु RT1305_ADC_SET_1, 0x170f पूर्ण,	/* 0.2 ohm RSense*/

पूर्ण;
#घोषणा RT1305_INIT_REG_LEN ARRAY_SIZE(init_list)

काष्ठा rt1305_priv अणु
	काष्ठा snd_soc_component *component;
	काष्ठा regmap *regmap;

	पूर्णांक sysclk;
	पूर्णांक sysclk_src;
	पूर्णांक lrck;
	पूर्णांक bclk;
	पूर्णांक master;

	पूर्णांक pll_src;
	पूर्णांक pll_in;
	पूर्णांक pll_out;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष rt1305_reg[] = अणु

	अणु 0x04, 0x0400 पूर्ण,
	अणु 0x05, 0x0880 पूर्ण,
	अणु 0x06, 0x0000 पूर्ण,
	अणु 0x07, 0x3100 पूर्ण,
	अणु 0x08, 0x8000 पूर्ण,
	अणु 0x09, 0x0000 पूर्ण,
	अणु 0x0a, 0x087e पूर्ण,
	अणु 0x0b, 0x0020 पूर्ण,
	अणु 0x0c, 0x0802 पूर्ण,
	अणु 0x0d, 0x0020 पूर्ण,
	अणु 0x10, 0x1d1d पूर्ण,
	अणु 0x11, 0x1d1d पूर्ण,
	अणु 0x12, 0xffff पूर्ण,
	अणु 0x14, 0x000c पूर्ण,
	अणु 0x16, 0x1717 पूर्ण,
	अणु 0x17, 0x4000 पूर्ण,
	अणु 0x18, 0x0019 पूर्ण,
	अणु 0x20, 0x0000 पूर्ण,
	अणु 0x22, 0x0000 पूर्ण,
	अणु 0x24, 0x0000 पूर्ण,
	अणु 0x26, 0x0000 पूर्ण,
	अणु 0x28, 0x0000 पूर्ण,
	अणु 0x2a, 0x4000 पूर्ण,
	अणु 0x2b, 0x3000 पूर्ण,
	अणु 0x2d, 0x6000 पूर्ण,
	अणु 0x2e, 0x0000 पूर्ण,
	अणु 0x2f, 0x8000 पूर्ण,
	अणु 0x32, 0x0000 पूर्ण,
	अणु 0x39, 0x0001 पूर्ण,
	अणु 0x3a, 0x0000 पूर्ण,
	अणु 0x3b, 0x1020 पूर्ण,
	अणु 0x3c, 0x0000 पूर्ण,
	अणु 0x3d, 0x0000 पूर्ण,
	अणु 0x3e, 0x4c00 पूर्ण,
	अणु 0x3f, 0x3000 पूर्ण,
	अणु 0x40, 0x000c पूर्ण,
	अणु 0x42, 0x0400 पूर्ण,
	अणु 0x46, 0xc22c पूर्ण,
	अणु 0x47, 0x0000 पूर्ण,
	अणु 0x4b, 0x0000 पूर्ण,
	अणु 0x4c, 0x0300 पूर्ण,
	अणु 0x4f, 0xf000 पूर्ण,
	अणु 0x50, 0xc200 पूर्ण,
	अणु 0x51, 0x1f1f पूर्ण,
	अणु 0x52, 0x01f0 पूर्ण,
	अणु 0x53, 0x407f पूर्ण,
	अणु 0x54, 0xffff पूर्ण,
	अणु 0x58, 0x4005 पूर्ण,
	अणु 0x5e, 0x0000 पूर्ण,
	अणु 0x5f, 0x0000 पूर्ण,
	अणु 0x60, 0xee13 पूर्ण,
	अणु 0x62, 0x0000 पूर्ण,
	अणु 0x63, 0x5f5f पूर्ण,
	अणु 0x64, 0x0040 पूर्ण,
	अणु 0x65, 0x4000 पूर्ण,
	अणु 0x66, 0x4004 पूर्ण,
	अणु 0x67, 0x0306 पूर्ण,
	अणु 0x68, 0x8c04 पूर्ण,
	अणु 0x69, 0xe021 पूर्ण,
	अणु 0x6a, 0x0000 पूर्ण,
	अणु 0x6c, 0xaaaa पूर्ण,
	अणु 0x70, 0x0333 पूर्ण,
	अणु 0x71, 0x3330 पूर्ण,
	अणु 0x72, 0x3333 पूर्ण,
	अणु 0x73, 0x3300 पूर्ण,
	अणु 0x74, 0x0000 पूर्ण,
	अणु 0x75, 0x0000 पूर्ण,
	अणु 0x76, 0x0000 पूर्ण,
	अणु 0x7a, 0x0003 पूर्ण,
	अणु 0x7c, 0x10ec पूर्ण,
	अणु 0x7e, 0x6251 पूर्ण,
	अणु 0x80, 0x0800 पूर्ण,
	अणु 0x81, 0x4000 पूर्ण,
	अणु 0x82, 0x0000 पूर्ण,
	अणु 0x90, 0x7a01 पूर्ण,
	अणु 0x91, 0x8431 पूर्ण,
	अणु 0x92, 0x0180 पूर्ण,
	अणु 0x93, 0x0000 पूर्ण,
	अणु 0x94, 0x0000 पूर्ण,
	अणु 0x95, 0x0000 पूर्ण,
	अणु 0x96, 0x0000 पूर्ण,
	अणु 0x97, 0x0000 पूर्ण,
	अणु 0x98, 0x0000 पूर्ण,
	अणु 0x99, 0x0000 पूर्ण,
	अणु 0x9a, 0x0000 पूर्ण,
	अणु 0x9b, 0x0000 पूर्ण,
	अणु 0x9c, 0x0000 पूर्ण,
	अणु 0x9d, 0x0000 पूर्ण,
	अणु 0x9e, 0x0000 पूर्ण,
	अणु 0x9f, 0x0000 पूर्ण,
	अणु 0xa0, 0x0000 पूर्ण,
	अणु 0xb0, 0x8200 पूर्ण,
	अणु 0xb1, 0x00ff पूर्ण,
	अणु 0xb2, 0x0008 पूर्ण,
	अणु 0xc0, 0x0200 पूर्ण,
	अणु 0xc1, 0x0000 पूर्ण,
	अणु 0xc2, 0x0000 पूर्ण,
	अणु 0xc3, 0x0000 पूर्ण,
	अणु 0xc4, 0x0000 पूर्ण,
	अणु 0xc5, 0x0000 पूर्ण,
	अणु 0xc6, 0x0000 पूर्ण,
	अणु 0xc7, 0x0000 पूर्ण,
	अणु 0xc8, 0x0000 पूर्ण,
	अणु 0xc9, 0x0000 पूर्ण,
	अणु 0xca, 0x0200 पूर्ण,
	अणु 0xcb, 0x0000 पूर्ण,
	अणु 0xcc, 0x0000 पूर्ण,
	अणु 0xcd, 0x0000 पूर्ण,
	अणु 0xce, 0x0000 पूर्ण,
	अणु 0xcf, 0x0000 पूर्ण,
	अणु 0xd0, 0x0000 पूर्ण,
	अणु 0xd1, 0x0000 पूर्ण,
	अणु 0xd2, 0x0000 पूर्ण,
	अणु 0xd3, 0x0000 पूर्ण,
	अणु 0xd4, 0x0200 पूर्ण,
	अणु 0xd5, 0x0000 पूर्ण,
	अणु 0xd6, 0x0000 पूर्ण,
	अणु 0xd7, 0x0000 पूर्ण,
	अणु 0xd8, 0x0000 पूर्ण,
	अणु 0xd9, 0x0000 पूर्ण,
	अणु 0xda, 0x0000 पूर्ण,
	अणु 0xdb, 0x0000 पूर्ण,
	अणु 0xdc, 0x0000 पूर्ण,
	अणु 0xdd, 0x0000 पूर्ण,
	अणु 0xde, 0x0200 पूर्ण,
	अणु 0xdf, 0x0000 पूर्ण,
	अणु 0xe0, 0x0000 पूर्ण,
	अणु 0xe1, 0x0000 पूर्ण,
	अणु 0xe2, 0x0000 पूर्ण,
	अणु 0xe3, 0x0000 पूर्ण,
	अणु 0xe4, 0x0000 पूर्ण,
	अणु 0xe5, 0x0000 पूर्ण,
	अणु 0xe6, 0x0000 पूर्ण,
	अणु 0xe7, 0x0000 पूर्ण,
	अणु 0xe8, 0x0200 पूर्ण,
	अणु 0xe9, 0x0000 पूर्ण,
	अणु 0xea, 0x0000 पूर्ण,
	अणु 0xeb, 0x0000 पूर्ण,
	अणु 0xec, 0x0000 पूर्ण,
	अणु 0xed, 0x0000 पूर्ण,
	अणु 0xee, 0x0000 पूर्ण,
	अणु 0xef, 0x0000 पूर्ण,
	अणु 0xf0, 0x0000 पूर्ण,
	अणु 0xf1, 0x0000 पूर्ण,
	अणु 0xf2, 0x0200 पूर्ण,
	अणु 0xf3, 0x0000 पूर्ण,
	अणु 0xf4, 0x0000 पूर्ण,
	अणु 0xf5, 0x0000 पूर्ण,
	अणु 0xf6, 0x0000 पूर्ण,
	अणु 0xf7, 0x0000 पूर्ण,
	अणु 0xf8, 0x0000 पूर्ण,
	अणु 0xf9, 0x0000 पूर्ण,
	अणु 0xfa, 0x0000 पूर्ण,
	अणु 0xfb, 0x0000 पूर्ण,
पूर्ण;

अटल पूर्णांक rt1305_reg_init(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1305_priv *rt1305 = snd_soc_component_get_drvdata(component);

	regmap_multi_reg_ग_लिखो(rt1305->regmap, init_list, RT1305_INIT_REG_LEN);
	वापस 0;
पूर्ण

अटल bool rt1305_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rt1305_ranges); i++) अणु
		अगर (reg >= rt1305_ranges[i].range_min &&
			reg <= rt1305_ranges[i].range_max) अणु
			वापस true;
		पूर्ण
	पूर्ण

	चयन (reg) अणु
	हाल RT1305_RESET:
	हाल RT1305_SPDIF_IN_SET_1:
	हाल RT1305_SPDIF_IN_SET_2:
	हाल RT1305_SPDIF_IN_SET_3:
	हाल RT1305_POWER_CTRL_2:
	हाल RT1305_CLOCK_DETECT:
	हाल RT1305_BIQUAD_SET_1:
	हाल RT1305_BIQUAD_SET_2:
	हाल RT1305_EQ_SET_2:
	हाल RT1305_SPK_TEMP_PROTECTION_0:
	हाल RT1305_SPK_TEMP_PROTECTION_2:
	हाल RT1305_SPK_DC_DETECT_1:
	हाल RT1305_SILENCE_DETECT:
	हाल RT1305_VERSION_ID:
	हाल RT1305_VENDOR_ID:
	हाल RT1305_DEVICE_ID:
	हाल RT1305_EFUSE_1:
	हाल RT1305_EFUSE_3:
	हाल RT1305_DC_CALIB_1:
	हाल RT1305_DC_CALIB_3:
	हाल RT1305_DAC_OFFSET_1:
	हाल RT1305_DAC_OFFSET_2:
	हाल RT1305_DAC_OFFSET_3:
	हाल RT1305_DAC_OFFSET_4:
	हाल RT1305_DAC_OFFSET_5:
	हाल RT1305_DAC_OFFSET_6:
	हाल RT1305_DAC_OFFSET_7:
	हाल RT1305_DAC_OFFSET_8:
	हाल RT1305_DAC_OFFSET_9:
	हाल RT1305_DAC_OFFSET_10:
	हाल RT1305_DAC_OFFSET_11:
	हाल RT1305_TRIM_1:
	हाल RT1305_TRIM_2:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt1305_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rt1305_ranges); i++) अणु
		अगर (reg >= rt1305_ranges[i].range_min &&
			reg <= rt1305_ranges[i].range_max) अणु
			वापस true;
		पूर्ण
	पूर्ण

	चयन (reg) अणु
	हाल RT1305_RESET:
	हाल RT1305_CLK_1 ... RT1305_CAL_EFUSE_CLOCK:
	हाल RT1305_PLL0_1 ... RT1305_PLL1_2:
	हाल RT1305_MIXER_CTRL_1:
	हाल RT1305_MIXER_CTRL_2:
	हाल RT1305_DAC_SET_1:
	हाल RT1305_DAC_SET_2:
	हाल RT1305_ADC_SET_1:
	हाल RT1305_ADC_SET_2:
	हाल RT1305_ADC_SET_3:
	हाल RT1305_PATH_SET:
	हाल RT1305_SPDIF_IN_SET_1:
	हाल RT1305_SPDIF_IN_SET_2:
	हाल RT1305_SPDIF_IN_SET_3:
	हाल RT1305_SPDIF_OUT_SET_1:
	हाल RT1305_SPDIF_OUT_SET_2:
	हाल RT1305_SPDIF_OUT_SET_3:
	हाल RT1305_I2S_SET_1:
	हाल RT1305_I2S_SET_2:
	हाल RT1305_PBTL_MONO_MODE_SRC:
	हाल RT1305_MANUALLY_I2C_DEVICE:
	हाल RT1305_POWER_STATUS:
	हाल RT1305_POWER_CTRL_1:
	हाल RT1305_POWER_CTRL_2:
	हाल RT1305_POWER_CTRL_3:
	हाल RT1305_POWER_CTRL_4:
	हाल RT1305_POWER_CTRL_5:
	हाल RT1305_CLOCK_DETECT:
	हाल RT1305_BIQUAD_SET_1:
	हाल RT1305_BIQUAD_SET_2:
	हाल RT1305_ADJUSTED_HPF_1:
	हाल RT1305_ADJUSTED_HPF_2:
	हाल RT1305_EQ_SET_1:
	हाल RT1305_EQ_SET_2:
	हाल RT1305_SPK_TEMP_PROTECTION_0:
	हाल RT1305_SPK_TEMP_PROTECTION_1:
	हाल RT1305_SPK_TEMP_PROTECTION_2:
	हाल RT1305_SPK_TEMP_PROTECTION_3:
	हाल RT1305_SPK_DC_DETECT_1:
	हाल RT1305_SPK_DC_DETECT_2:
	हाल RT1305_LOUDNESS:
	हाल RT1305_THERMAL_FOLD_BACK_1:
	हाल RT1305_THERMAL_FOLD_BACK_2:
	हाल RT1305_SILENCE_DETECT ... RT1305_SPK_EXCURSION_LIMITER_7:
	हाल RT1305_VERSION_ID:
	हाल RT1305_VENDOR_ID:
	हाल RT1305_DEVICE_ID:
	हाल RT1305_EFUSE_1:
	हाल RT1305_EFUSE_2:
	हाल RT1305_EFUSE_3:
	हाल RT1305_DC_CALIB_1:
	हाल RT1305_DC_CALIB_2:
	हाल RT1305_DC_CALIB_3:
	हाल RT1305_DAC_OFFSET_1 ... RT1305_DAC_OFFSET_14:
	हाल RT1305_TRIM_1:
	हाल RT1305_TRIM_2:
	हाल RT1305_TUNE_INTERNAL_OSC:
	हाल RT1305_BIQUAD1_H0_L_28_16 ... RT1305_BIQUAD3_A2_R_15_0:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(dac_vol_tlv, -9435, 37, 0);

अटल स्थिर अक्षर * स्थिर rt1305_rx_data_ch_select[] = अणु
	"LR",
	"RL",
	"Copy L",
	"Copy R",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt1305_rx_data_ch_क्रमागत, RT1305_I2S_SET_2, 2,
	rt1305_rx_data_ch_select);

अटल व्योम rt1305_reset(काष्ठा regmap *regmap)
अणु
	regmap_ग_लिखो(regmap, RT1305_RESET, 0);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new rt1305_snd_controls[] = अणु
	SOC_DOUBLE_TLV("DAC Playback Volume", RT1305_DAC_SET_1,
			8, 0, 0xff, 0, dac_vol_tlv),

	/* I2S Data Channel Selection */
	SOC_ENUM("RX Channel Select", rt1305_rx_data_ch_क्रमागत),
पूर्ण;

अटल पूर्णांक rt1305_is_rc_clk_from_pll(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(source->dapm);
	काष्ठा rt1305_priv *rt1305 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val;

	val = snd_soc_component_पढ़ो(component, RT1305_CLK_1);

	अगर (rt1305->sysclk_src == RT1305_FS_SYS_PRE_S_PLL1 &&
		(val & RT1305_SEL_PLL_SRC_2_RCCLK))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक rt1305_is_sys_clk_from_pll(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(source->dapm);
	काष्ठा rt1305_priv *rt1305 = snd_soc_component_get_drvdata(component);

	अगर (rt1305->sysclk_src == RT1305_FS_SYS_PRE_S_PLL1)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक rt1305_classd_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, RT1305_POWER_CTRL_1,
			RT1305_POW_PDB_JD_MASK, RT1305_POW_PDB_JD);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT1305_POWER_CTRL_1,
			RT1305_POW_PDB_JD_MASK, 0);
		usleep_range(150000, 200000);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new rt1305_sto_dac_l =
	SOC_DAPM_SINGLE("Switch", RT1305_DAC_SET_2,
		RT1305_DVOL_MUTE_L_EN_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new rt1305_sto_dac_r =
	SOC_DAPM_SINGLE("Switch", RT1305_DAC_SET_2,
		RT1305_DVOL_MUTE_R_EN_SFT, 1, 1);

अटल स्थिर काष्ठा snd_soc_dapm_widget rt1305_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("PLL0", RT1305_POWER_CTRL_1,
		RT1305_POW_PLL0_EN_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL1", RT1305_POWER_CTRL_1,
		RT1305_POW_PLL1_EN_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MBIAS", RT1305_POWER_CTRL_1,
		RT1305_POW_MBIAS_LV_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BG MBIAS", RT1305_POWER_CTRL_1,
		RT1305_POW_BG_MBIAS_LV_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("LDO2", RT1305_POWER_CTRL_1,
		RT1305_POW_LDO2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BG2", RT1305_POWER_CTRL_1,
		RT1305_POW_BG2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("LDO2 IB2", RT1305_POWER_CTRL_1,
		RT1305_POW_LDO2_IB2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("VREF", RT1305_POWER_CTRL_1,
		RT1305_POW_VREF_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("VREF1", RT1305_POWER_CTRL_1,
		RT1305_POW_VREF1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("VREF2", RT1305_POWER_CTRL_1,
		RT1305_POW_VREF2_BIT, 0, शून्य, 0),


	SND_SOC_DAPM_SUPPLY("DISC VREF", RT1305_POWER_CTRL_2,
		RT1305_POW_DISC_VREF_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("FASTB VREF", RT1305_POWER_CTRL_2,
		RT1305_POW_FASTB_VREF_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ULTRA FAST VREF", RT1305_POWER_CTRL_2,
		RT1305_POW_ULTRA_FAST_VREF_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CHOP DAC", RT1305_POWER_CTRL_2,
		RT1305_POW_CKXEN_DAC_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CKGEN DAC", RT1305_POWER_CTRL_2,
		RT1305_POW_EN_CKGEN_DAC_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CLAMP", RT1305_POWER_CTRL_2,
		RT1305_POW_CLAMP_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BUFL", RT1305_POWER_CTRL_2,
		RT1305_POW_BUFL_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BUFR", RT1305_POWER_CTRL_2,
		RT1305_POW_BUFR_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CKGEN ADC", RT1305_POWER_CTRL_2,
		RT1305_POW_EN_CKGEN_ADC_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC3 L", RT1305_POWER_CTRL_2,
		RT1305_POW_ADC3_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC3 R", RT1305_POWER_CTRL_2,
		RT1305_POW_ADC3_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("TRIOSC", RT1305_POWER_CTRL_2,
		RT1305_POW_TRIOSC_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("AVDD1", RT1305_POWER_CTRL_2,
		RT1305_POR_AVDD1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("AVDD2", RT1305_POWER_CTRL_2,
		RT1305_POR_AVDD2_BIT, 0, शून्य, 0),


	SND_SOC_DAPM_SUPPLY("VSENSE R", RT1305_POWER_CTRL_3,
		RT1305_POW_VSENSE_RCH_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("VSENSE L", RT1305_POWER_CTRL_3,
		RT1305_POW_VSENSE_LCH_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ISENSE R", RT1305_POWER_CTRL_3,
		RT1305_POW_ISENSE_RCH_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ISENSE L", RT1305_POWER_CTRL_3,
		RT1305_POW_ISENSE_LCH_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("POR AVDD1", RT1305_POWER_CTRL_3,
		RT1305_POW_POR_AVDD1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("POR AVDD2", RT1305_POWER_CTRL_3,
		RT1305_POW_POR_AVDD2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("VCM 6172", RT1305_POWER_CTRL_3,
		RT1305_EN_VCM_6172_BIT, 0, शून्य, 0),


	/* Audio Interface */
	SND_SOC_DAPM_AIF_IN("AIF1RX", "AIF1 Playback", 0, SND_SOC_NOPM, 0, 0),

	/* Digital Interface */
	SND_SOC_DAPM_SUPPLY("DAC L Power", RT1305_POWER_CTRL_2,
		RT1305_POW_DAC1_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC R Power", RT1305_POWER_CTRL_2,
		RT1305_POW_DAC1_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_DAC("DAC", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_SWITCH("DAC L", SND_SOC_NOPM, 0, 0, &rt1305_sto_dac_l),
	SND_SOC_DAPM_SWITCH("DAC R", SND_SOC_NOPM, 0, 0, &rt1305_sto_dac_r),

	/* Output Lines */
	SND_SOC_DAPM_PGA_E("CLASS D", SND_SOC_NOPM, 0, 0, शून्य, 0,
		rt1305_classd_event,
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_OUTPUT("SPOL"),
	SND_SOC_DAPM_OUTPUT("SPOR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt1305_dapm_routes[] = अणु

	अणु "DAC", शून्य, "AIF1RX" पूर्ण,

	अणु "DAC", शून्य, "PLL0", rt1305_is_rc_clk_from_pll पूर्ण,
	अणु "DAC", शून्य, "PLL1", rt1305_is_sys_clk_from_pll पूर्ण,

	अणु "DAC", शून्य, "MBIAS" पूर्ण,
	अणु "DAC", शून्य, "BG MBIAS" पूर्ण,
	अणु "DAC", शून्य, "LDO2" पूर्ण,
	अणु "DAC", शून्य, "BG2" पूर्ण,
	अणु "DAC", शून्य, "LDO2 IB2" पूर्ण,
	अणु "DAC", शून्य, "VREF" पूर्ण,
	अणु "DAC", शून्य, "VREF1" पूर्ण,
	अणु "DAC", शून्य, "VREF2" पूर्ण,

	अणु "DAC", शून्य, "DISC VREF" पूर्ण,
	अणु "DAC", शून्य, "FASTB VREF" पूर्ण,
	अणु "DAC", शून्य, "ULTRA FAST VREF" पूर्ण,
	अणु "DAC", शून्य, "CHOP DAC" पूर्ण,
	अणु "DAC", शून्य, "CKGEN DAC" पूर्ण,
	अणु "DAC", शून्य, "CLAMP" पूर्ण,
	अणु "DAC", शून्य, "CKGEN ADC" पूर्ण,
	अणु "DAC", शून्य, "TRIOSC" पूर्ण,
	अणु "DAC", शून्य, "AVDD1" पूर्ण,
	अणु "DAC", शून्य, "AVDD2" पूर्ण,

	अणु "DAC", शून्य, "POR AVDD1" पूर्ण,
	अणु "DAC", शून्य, "POR AVDD2" पूर्ण,
	अणु "DAC", शून्य, "VCM 6172" पूर्ण,

	अणु "DAC L", "Switch", "DAC" पूर्ण,
	अणु "DAC R", "Switch", "DAC" पूर्ण,

	अणु "DAC R", शून्य, "VSENSE R" पूर्ण,
	अणु "DAC L", शून्य, "VSENSE L" पूर्ण,
	अणु "DAC R", शून्य, "ISENSE R" पूर्ण,
	अणु "DAC L", शून्य, "ISENSE L" पूर्ण,
	अणु "DAC L", शून्य, "ADC3 L" पूर्ण,
	अणु "DAC R", शून्य, "ADC3 R" पूर्ण,
	अणु "DAC L", शून्य, "BUFL" पूर्ण,
	अणु "DAC R", शून्य, "BUFR" पूर्ण,
	अणु "DAC L", शून्य, "DAC L Power" पूर्ण,
	अणु "DAC R", शून्य, "DAC R Power" पूर्ण,

	अणु "CLASS D", शून्य, "DAC L" पूर्ण,
	अणु "CLASS D", शून्य, "DAC R" पूर्ण,

	अणु "SPOL", शून्य, "CLASS D" पूर्ण,
	अणु "SPOR", शून्य, "CLASS D" पूर्ण,
पूर्ण;

अटल पूर्णांक rt1305_get_clk_info(पूर्णांक sclk, पूर्णांक rate)
अणु
	पूर्णांक i;
	अटल स्थिर पूर्णांक pd[] = अणु1, 2, 3, 4, 6, 8, 12, 16पूर्ण;

	अगर (sclk <= 0 || rate <= 0)
		वापस -EINVAL;

	rate = rate << 8;
	क्रम (i = 0; i < ARRAY_SIZE(pd); i++)
		अगर (sclk == rate * pd[i])
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक rt1305_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt1305_priv *rt1305 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val_len = 0, val_clk, mask_clk;
	पूर्णांक pre_भाग, bclk_ms, frame_size;

	rt1305->lrck = params_rate(params);
	pre_भाग = rt1305_get_clk_info(rt1305->sysclk, rt1305->lrck);
	अगर (pre_भाग < 0) अणु
		dev_warn(component->dev, "Force using PLL ");
		snd_soc_dai_set_pll(dai, 0, RT1305_PLL1_S_BCLK,
			rt1305->lrck * 64, rt1305->lrck * 256);
		snd_soc_dai_set_sysclk(dai, RT1305_FS_SYS_PRE_S_PLL1,
			rt1305->lrck * 256, SND_SOC_CLOCK_IN);
		pre_भाग = 0;
	पूर्ण
	frame_size = snd_soc_params_to_frame_size(params);
	अगर (frame_size < 0) अणु
		dev_err(component->dev, "Unsupported frame size: %d\n",
			frame_size);
		वापस -EINVAL;
	पूर्ण

	bclk_ms = frame_size > 32;
	rt1305->bclk = rt1305->lrck * (32 << bclk_ms);

	dev_dbg(component->dev, "bclk_ms is %d and pre_div is %d for iis %d\n",
				bclk_ms, pre_भाग, dai->id);

	dev_dbg(component->dev, "lrck is %dHz and pre_div is %d for iis %d\n",
				rt1305->lrck, pre_भाग, dai->id);

	चयन (params_width(params)) अणु
	हाल 16:
		val_len |= RT1305_I2S_DL_SEL_16B;
		अवरोध;
	हाल 20:
		val_len |= RT1305_I2S_DL_SEL_20B;
		अवरोध;
	हाल 24:
		val_len |= RT1305_I2S_DL_SEL_24B;
		अवरोध;
	हाल 8:
		val_len |= RT1305_I2S_DL_SEL_8B;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT1305_AIF1:
		mask_clk = RT1305_DIV_FS_SYS_MASK;
		val_clk = pre_भाग << RT1305_DIV_FS_SYS_SFT;
		snd_soc_component_update_bits(component, RT1305_I2S_SET_2,
			RT1305_I2S_DL_SEL_MASK,
			val_len);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, RT1305_CLK_2,
		mask_clk, val_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1305_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt1305_priv *rt1305 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0, reg1_val = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		reg_val |= RT1305_SEL_I2S_OUT_MODE_M;
		rt1305->master = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		reg_val |= RT1305_SEL_I2S_OUT_MODE_S;
		rt1305->master = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		reg1_val |= RT1305_I2S_BCLK_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		reg1_val |= RT1305_I2S_DF_SEL_LEFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		reg1_val |= RT1305_I2S_DF_SEL_PCM_A;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		reg1_val |= RT1305_I2S_DF_SEL_PCM_B;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT1305_AIF1:
		snd_soc_component_update_bits(component, RT1305_I2S_SET_1,
			RT1305_SEL_I2S_OUT_MODE_MASK, reg_val);
		snd_soc_component_update_bits(component, RT1305_I2S_SET_2,
			RT1305_I2S_DF_SEL_MASK | RT1305_I2S_BCLK_MASK,
			reg1_val);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt1305_set_component_sysclk(काष्ठा snd_soc_component *component,
		पूर्णांक clk_id, पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा rt1305_priv *rt1305 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;

	अगर (freq == rt1305->sysclk && clk_id == rt1305->sysclk_src)
		वापस 0;

	चयन (clk_id) अणु
	हाल RT1305_FS_SYS_PRE_S_MCLK:
		reg_val |= RT1305_SEL_FS_SYS_PRE_MCLK;
		snd_soc_component_update_bits(component,
			RT1305_CLOCK_DETECT, RT1305_SEL_CLK_DET_SRC_MASK,
			RT1305_SEL_CLK_DET_SRC_MCLK);
		अवरोध;
	हाल RT1305_FS_SYS_PRE_S_PLL1:
		reg_val |= RT1305_SEL_FS_SYS_PRE_PLL;
		अवरोध;
	हाल RT1305_FS_SYS_PRE_S_RCCLK:
		reg_val |= RT1305_SEL_FS_SYS_PRE_RCCLK;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_update_bits(component, RT1305_CLK_1,
		RT1305_SEL_FS_SYS_PRE_MASK, reg_val);
	rt1305->sysclk = freq;
	rt1305->sysclk_src = clk_id;

	dev_dbg(component->dev, "Sysclk is %dHz and clock id is %d\n",
		freq, clk_id);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1305_set_component_pll(काष्ठा snd_soc_component *component,
		पूर्णांक pll_id, पूर्णांक source, अचिन्हित पूर्णांक freq_in,
		अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा rt1305_priv *rt1305 = snd_soc_component_get_drvdata(component);
	काष्ठा rl6231_pll_code pll_code;
	पूर्णांक ret;

	अगर (source == rt1305->pll_src && freq_in == rt1305->pll_in &&
	    freq_out == rt1305->pll_out)
		वापस 0;

	अगर (!freq_in || !freq_out) अणु
		dev_dbg(component->dev, "PLL disabled\n");

		rt1305->pll_in = 0;
		rt1305->pll_out = 0;
		snd_soc_component_update_bits(component, RT1305_CLK_1,
			RT1305_SEL_FS_SYS_PRE_MASK | RT1305_SEL_PLL_SRC_1_MASK,
			RT1305_SEL_FS_SYS_PRE_PLL | RT1305_SEL_PLL_SRC_1_BCLK);
		वापस 0;
	पूर्ण

	चयन (source) अणु
	हाल RT1305_PLL2_S_MCLK:
		snd_soc_component_update_bits(component, RT1305_CLK_1,
			RT1305_SEL_PLL_SRC_2_MASK | RT1305_SEL_PLL_SRC_1_MASK |
			RT1305_DIV_PLL_SRC_2_MASK,
			RT1305_SEL_PLL_SRC_2_MCLK | RT1305_SEL_PLL_SRC_1_PLL2);
		snd_soc_component_update_bits(component,
			RT1305_CLOCK_DETECT, RT1305_SEL_CLK_DET_SRC_MASK,
			RT1305_SEL_CLK_DET_SRC_MCLK);
		अवरोध;
	हाल RT1305_PLL1_S_BCLK:
		snd_soc_component_update_bits(component,
			RT1305_CLK_1, RT1305_SEL_PLL_SRC_1_MASK,
			RT1305_SEL_PLL_SRC_1_BCLK);
		अवरोध;
	हाल RT1305_PLL2_S_RCCLK:
		snd_soc_component_update_bits(component, RT1305_CLK_1,
			RT1305_SEL_PLL_SRC_2_MASK | RT1305_SEL_PLL_SRC_1_MASK |
			RT1305_DIV_PLL_SRC_2_MASK,
			RT1305_SEL_PLL_SRC_2_RCCLK | RT1305_SEL_PLL_SRC_1_PLL2);
		freq_in = 98304000;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unknown PLL Source %d\n", source);
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

	snd_soc_component_ग_लिखो(component, RT1305_PLL1_1,
		((pll_code.m_bp ? 0 : pll_code.m_code) << RT1305_PLL_1_M_SFT) |
		(pll_code.m_bp << RT1305_PLL_1_M_BYPASS_SFT) |
		pll_code.n_code);
	snd_soc_component_ग_लिखो(component, RT1305_PLL1_2,
		pll_code.k_code);

	rt1305->pll_in = freq_in;
	rt1305->pll_out = freq_out;
	rt1305->pll_src = source;

	वापस 0;
पूर्ण

अटल पूर्णांक rt1305_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1305_priv *rt1305 = snd_soc_component_get_drvdata(component);

	rt1305->component = component;

	/* initial settings */
	rt1305_reg_init(component);

	वापस 0;
पूर्ण

अटल व्योम rt1305_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1305_priv *rt1305 = snd_soc_component_get_drvdata(component);

	rt1305_reset(rt1305->regmap);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rt1305_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1305_priv *rt1305 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt1305->regmap, true);
	regcache_mark_dirty(rt1305->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1305_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1305_priv *rt1305 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt1305->regmap, false);
	regcache_sync(rt1305->regmap);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा rt1305_suspend शून्य
#घोषणा rt1305_resume शून्य
#पूर्ण_अगर

#घोषणा RT1305_STEREO_RATES SNDRV_PCM_RATE_8000_192000
#घोषणा RT1305_FORMATS (SNDRV_PCM_FMTBIT_S8 | \
			SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S16_LE | \
			SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops rt1305_aअगर_dai_ops = अणु
	.hw_params = rt1305_hw_params,
	.set_fmt = rt1305_set_dai_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt1305_dai[] = अणु
	अणु
		.name = "rt1305-aif",
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT1305_STEREO_RATES,
			.क्रमmats = RT1305_FORMATS,
		पूर्ण,
		.ops = &rt1305_aअगर_dai_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_rt1305 = अणु
	.probe = rt1305_probe,
	.हटाओ = rt1305_हटाओ,
	.suspend = rt1305_suspend,
	.resume = rt1305_resume,
	.controls = rt1305_snd_controls,
	.num_controls = ARRAY_SIZE(rt1305_snd_controls),
	.dapm_widमाला_लो = rt1305_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(rt1305_dapm_widमाला_लो),
	.dapm_routes = rt1305_dapm_routes,
	.num_dapm_routes = ARRAY_SIZE(rt1305_dapm_routes),
	.set_sysclk = rt1305_set_component_sysclk,
	.set_pll = rt1305_set_component_pll,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt1305_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = RT1305_MAX_REG + 1 + (ARRAY_SIZE(rt1305_ranges) *
					       RT1305_PR_SPACING),
	.अस्थिर_reg = rt1305_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = rt1305_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = rt1305_reg,
	.num_reg_शेषs = ARRAY_SIZE(rt1305_reg),
	.ranges = rt1305_ranges,
	.num_ranges = ARRAY_SIZE(rt1305_ranges),
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id rt1305_of_match[] = अणु
	अणु .compatible = "realtek,rt1305", पूर्ण,
	अणु .compatible = "realtek,rt1306", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt1305_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id rt1305_acpi_match[] = अणु
	अणु"10EC1305", 0,पूर्ण,
	अणु"10EC1306", 0,पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rt1305_acpi_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id rt1305_i2c_id[] = अणु
	अणु "rt1305", 0 पूर्ण,
	अणु "rt1306", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt1305_i2c_id);

अटल व्योम rt1305_calibrate(काष्ठा rt1305_priv *rt1305)
अणु
	अचिन्हित पूर्णांक valmsb, vallsb, offsetl, offsetr;
	अचिन्हित पूर्णांक rh, rl, rhl, r0ohm;
	u64 r0l, r0r;

	regcache_cache_bypass(rt1305->regmap, true);

	rt1305_reset(rt1305->regmap);
	regmap_ग_लिखो(rt1305->regmap, RT1305_ADC_SET_3, 0x0219);
	regmap_ग_लिखो(rt1305->regmap, RT1305_PR_BASE + 0xcf, 0x5548);
	regmap_ग_लिखो(rt1305->regmap, RT1305_PR_BASE + 0xc1, 0x0320);
	regmap_ग_लिखो(rt1305->regmap, RT1305_CLOCK_DETECT, 0x1000);
	regmap_ग_लिखो(rt1305->regmap, RT1305_CLK_1, 0x0600);
	regmap_ग_लिखो(rt1305->regmap, RT1305_POWER_CTRL_3, 0xffd0);
	regmap_ग_लिखो(rt1305->regmap, RT1305_EFUSE_1, 0x0080);
	regmap_ग_लिखो(rt1305->regmap, RT1305_EFUSE_1, 0x0880);
	regmap_ग_लिखो(rt1305->regmap, RT1305_POWER_CTRL_1, 0x0dfe);

	/* Sin Gen */
	regmap_ग_लिखो(rt1305->regmap, RT1305_PR_BASE + 0x5d, 0x0442);

	regmap_ग_लिखो(rt1305->regmap, RT1305_CAL_EFUSE_CLOCK, 0xb000);
	regmap_ग_लिखो(rt1305->regmap, RT1305_PR_BASE + 0xc3, 0xd4a0);
	regmap_ग_लिखो(rt1305->regmap, RT1305_PR_BASE + 0xcc, 0x00cc);
	regmap_ग_लिखो(rt1305->regmap, RT1305_PR_BASE + 0xc1, 0x0320);
	regmap_ग_लिखो(rt1305->regmap, RT1305_POWER_STATUS, 0x0000);
	regmap_ग_लिखो(rt1305->regmap, RT1305_POWER_CTRL_2, 0xffff);
	regmap_ग_लिखो(rt1305->regmap, RT1305_POWER_CTRL_3, 0xfc20);
	regmap_ग_लिखो(rt1305->regmap, RT1305_PR_BASE + 0x06, 0x00c0);
	regmap_ग_लिखो(rt1305->regmap, RT1305_POWER_CTRL_3, 0xfca0);
	regmap_ग_लिखो(rt1305->regmap, RT1305_POWER_CTRL_3, 0xfce0);
	regmap_ग_लिखो(rt1305->regmap, RT1305_POWER_CTRL_3, 0xfcf0);

	/* EFUSE पढ़ो */
	regmap_ग_लिखो(rt1305->regmap, RT1305_EFUSE_1, 0x0080);
	regmap_ग_लिखो(rt1305->regmap, RT1305_EFUSE_1, 0x0880);
	regmap_ग_लिखो(rt1305->regmap, RT1305_EFUSE_1, 0x0880);
	regmap_ग_लिखो(rt1305->regmap, RT1305_POWER_CTRL_3, 0xfce0);
	regmap_ग_लिखो(rt1305->regmap, RT1305_POWER_CTRL_3, 0xfca0);
	regmap_ग_लिखो(rt1305->regmap, RT1305_POWER_CTRL_3, 0xfc20);
	regmap_ग_लिखो(rt1305->regmap, RT1305_PR_BASE + 0x06, 0x0000);
	regmap_ग_लिखो(rt1305->regmap, RT1305_EFUSE_1, 0x0000);

	regmap_पढ़ो(rt1305->regmap, RT1305_DAC_OFFSET_5, &valmsb);
	regmap_पढ़ो(rt1305->regmap, RT1305_DAC_OFFSET_6, &vallsb);
	offsetl = valmsb << 16 | vallsb;
	regmap_पढ़ो(rt1305->regmap, RT1305_DAC_OFFSET_7, &valmsb);
	regmap_पढ़ो(rt1305->regmap, RT1305_DAC_OFFSET_8, &vallsb);
	offsetr = valmsb << 16 | vallsb;
	pr_info("DC offsetl=0x%x, offsetr=0x%x\n", offsetl, offsetr);

	/* R0 calibration */
	regmap_ग_लिखो(rt1305->regmap, RT1305_PR_BASE + 0x5d, 0x9542);
	regmap_ग_लिखो(rt1305->regmap, RT1305_POWER_CTRL_3, 0xfcf0);
	regmap_ग_लिखो(rt1305->regmap, RT1305_POWER_CTRL_2, 0xffff);
	regmap_ग_लिखो(rt1305->regmap, RT1305_POWER_CTRL_1, 0x1dfe);
	regmap_ग_लिखो(rt1305->regmap, RT1305_SILENCE_DETECT, 0x0e13);
	regmap_ग_लिखो(rt1305->regmap, RT1305_CLK_1, 0x0650);

	regmap_ग_लिखो(rt1305->regmap, RT1305_PR_BASE + 0x50, 0x0064);
	regmap_ग_लिखो(rt1305->regmap, RT1305_PR_BASE + 0x51, 0x0770);
	regmap_ग_लिखो(rt1305->regmap, RT1305_PR_BASE + 0x52, 0xc30c);
	regmap_ग_लिखो(rt1305->regmap, RT1305_SPK_TEMP_PROTECTION_1, 0x8200);
	regmap_ग_लिखो(rt1305->regmap, RT1305_PR_BASE + 0xd4, 0xfb00);
	regmap_ग_लिखो(rt1305->regmap, RT1305_PR_BASE + 0xd4, 0xff80);
	msleep(2000);
	regmap_पढ़ो(rt1305->regmap, RT1305_PR_BASE + 0x55, &rh);
	regmap_पढ़ो(rt1305->regmap, RT1305_PR_BASE + 0x56, &rl);
	rhl = (rh << 16) | rl;
	r0ohm = (rhl*10) / 33554432;

	pr_debug("Left_rhl = 0x%x rh=0x%x rl=0x%x\n", rhl, rh, rl);
	pr_info("Left channel %d.%dohm\n", (r0ohm/10), (r0ohm%10));

	r0l = 562949953421312ULL;
	अगर (rhl != 0)
		करो_भाग(r0l, rhl);
	pr_debug("Left_r0 = 0x%llx\n", r0l);

	regmap_ग_लिखो(rt1305->regmap, RT1305_SPK_TEMP_PROTECTION_1, 0x9200);
	regmap_ग_लिखो(rt1305->regmap, RT1305_PR_BASE + 0xd4, 0xfb00);
	regmap_ग_लिखो(rt1305->regmap, RT1305_PR_BASE + 0xd4, 0xff80);
	msleep(2000);
	regmap_पढ़ो(rt1305->regmap, RT1305_PR_BASE + 0x55, &rh);
	regmap_पढ़ो(rt1305->regmap, RT1305_PR_BASE + 0x56, &rl);
	rhl = (rh << 16) | rl;
	r0ohm = (rhl*10) / 33554432;

	pr_debug("Right_rhl = 0x%x rh=0x%x rl=0x%x\n", rhl, rh, rl);
	pr_info("Right channel %d.%dohm\n", (r0ohm/10), (r0ohm%10));

	r0r = 562949953421312ULL;
	अगर (rhl != 0)
		करो_भाग(r0r, rhl);
	pr_debug("Right_r0 = 0x%llx\n", r0r);

	regmap_ग_लिखो(rt1305->regmap, RT1305_SPK_TEMP_PROTECTION_1, 0xc2ec);

	अगर ((r0l > R0_UPPER) && (r0l < R0_LOWER) &&
		(r0r > R0_UPPER) && (r0r < R0_LOWER)) अणु
		regmap_ग_लिखो(rt1305->regmap, RT1305_PR_BASE + 0x4e,
			(r0l >> 16) & 0xffff);
		regmap_ग_लिखो(rt1305->regmap, RT1305_PR_BASE + 0x4f,
			r0l & 0xffff);
		regmap_ग_लिखो(rt1305->regmap, RT1305_PR_BASE + 0xfe,
			((r0r >> 16) & 0xffff) | 0xf800);
		regmap_ग_लिखो(rt1305->regmap, RT1305_PR_BASE + 0xfd,
			r0r & 0xffff);
	पूर्ण अन्यथा अणु
		pr_err("R0 calibration failed\n");
	पूर्ण

	/* restore some रेजिस्टरs */
	regmap_ग_लिखो(rt1305->regmap, RT1305_POWER_CTRL_1, 0x0dfe);
	usleep_range(200000, 400000);
	regmap_ग_लिखो(rt1305->regmap, RT1305_PR_BASE + 0x5d, 0x0442);
	regmap_ग_लिखो(rt1305->regmap, RT1305_CLOCK_DETECT, 0x3000);
	regmap_ग_लिखो(rt1305->regmap, RT1305_CLK_1, 0x0400);
	regmap_ग_लिखो(rt1305->regmap, RT1305_POWER_CTRL_1, 0x0000);
	regmap_ग_लिखो(rt1305->regmap, RT1305_CAL_EFUSE_CLOCK, 0x8000);
	regmap_ग_लिखो(rt1305->regmap, RT1305_POWER_CTRL_2, 0x1020);
	regmap_ग_लिखो(rt1305->regmap, RT1305_POWER_CTRL_3, 0x0000);

	regcache_cache_bypass(rt1305->regmap, false);
पूर्ण

अटल पूर्णांक rt1305_i2c_probe(काष्ठा i2c_client *i2c,
		    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rt1305_priv *rt1305;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	rt1305 = devm_kzalloc(&i2c->dev, माप(काष्ठा rt1305_priv),
				GFP_KERNEL);
	अगर (rt1305 == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, rt1305);

	rt1305->regmap = devm_regmap_init_i2c(i2c, &rt1305_regmap);
	अगर (IS_ERR(rt1305->regmap)) अणु
		ret = PTR_ERR(rt1305->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	regmap_पढ़ो(rt1305->regmap, RT1305_DEVICE_ID, &val);
	अगर (val != RT1305_DEVICE_ID_NUM) अणु
		dev_err(&i2c->dev,
			"Device with ID register %x is not rt1305\n", val);
		वापस -ENODEV;
	पूर्ण

	rt1305_reset(rt1305->regmap);
	rt1305_calibrate(rt1305);

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_rt1305,
			rt1305_dai, ARRAY_SIZE(rt1305_dai));
पूर्ण

अटल व्योम rt1305_i2c_shutकरोwn(काष्ठा i2c_client *client)
अणु
	काष्ठा rt1305_priv *rt1305 = i2c_get_clientdata(client);

	rt1305_reset(rt1305->regmap);
पूर्ण


अटल काष्ठा i2c_driver rt1305_i2c_driver = अणु
	.driver = अणु
		.name = "rt1305",
#अगर defined(CONFIG_OF)
		.of_match_table = rt1305_of_match,
#पूर्ण_अगर
#अगर defined(CONFIG_ACPI)
		.acpi_match_table = ACPI_PTR(rt1305_acpi_match)
#पूर्ण_अगर
	पूर्ण,
	.probe = rt1305_i2c_probe,
	.shutकरोwn = rt1305_i2c_shutकरोwn,
	.id_table = rt1305_i2c_id,
पूर्ण;
module_i2c_driver(rt1305_i2c_driver);

MODULE_DESCRIPTION("ASoC RT1305 amplifier driver");
MODULE_AUTHOR("Shuming Fan <shumingf@realtek.com>");
MODULE_LICENSE("GPL v2");
