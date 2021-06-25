<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// rt1308.c  --  RT1308 ALSA SoC amplअगरier component driver
//
// Copyright 2019 Realtek Semiconductor Corp.
// Author: Derek Fang <derek.fang@realtek.com>
//

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/acpi.h>
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
#समावेश "rt1308.h"

अटल स्थिर काष्ठा reg_sequence init_list[] = अणु

	अणु RT1308_I2C_I2S_SDW_SET,	0x01014005 पूर्ण,
	अणु RT1308_CLASS_D_SET_2,		0x227f5501 पूर्ण,
	अणु RT1308_PADS_1,		0x50150505 पूर्ण,
	अणु RT1308_VREF,			0x18100000 पूर्ण,
	अणु RT1308_IV_SENSE,		0x87010000 पूर्ण,
	अणु RT1308_DUMMY_REG,		0x00000200 पूर्ण,
	अणु RT1308_SIL_DET,		0xe1c30000 पूर्ण,
	अणु RT1308_DC_CAL_2,		0x00ffff00 पूर्ण,
	अणु RT1308_CLK_DET,		0x01000000 पूर्ण,
	अणु RT1308_POWER_STATUS,		0x08800000 पूर्ण,
	अणु RT1308_DAC_SET,		0xafaf0700 पूर्ण,

पूर्ण;
#घोषणा RT1308_INIT_REG_LEN ARRAY_SIZE(init_list)

काष्ठा rt1308_priv अणु
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

अटल स्थिर काष्ठा reg_शेष rt1308_reg[] = अणु

	अणु 0x01, 0x1f3f5f00 पूर्ण,
	अणु 0x02, 0x07000000 पूर्ण,
	अणु 0x03, 0x80003e00 पूर्ण,
	अणु 0x04, 0x80800600 पूर्ण,
	अणु 0x05, 0x0aaa1a0a पूर्ण,
	अणु 0x06, 0x52000000 पूर्ण,
	अणु 0x07, 0x00000000 पूर्ण,
	अणु 0x08, 0x00600000 पूर्ण,
	अणु 0x09, 0xe1030000 पूर्ण,
	अणु 0x0a, 0x00000000 पूर्ण,
	अणु 0x0b, 0x30000000 पूर्ण,
	अणु 0x0c, 0x7fff7000 पूर्ण,
	अणु 0x10, 0xffff0700 पूर्ण,
	अणु 0x11, 0x0a000000 पूर्ण,
	अणु 0x12, 0x60040000 पूर्ण,
	अणु 0x13, 0x00000000 पूर्ण,
	अणु 0x14, 0x0f300000 पूर्ण,
	अणु 0x15, 0x00000022 पूर्ण,
	अणु 0x16, 0x02000000 पूर्ण,
	अणु 0x17, 0x01004045 पूर्ण,
	अणु 0x18, 0x00000000 पूर्ण,
	अणु 0x19, 0x00000000 पूर्ण,
	अणु 0x1a, 0x80000000 पूर्ण,
	अणु 0x1b, 0x10325476 पूर्ण,
	अणु 0x1c, 0x1d1d0000 पूर्ण,
	अणु 0x20, 0xd2101300 पूर्ण,
	अणु 0x21, 0xf3ffff00 पूर्ण,
	अणु 0x22, 0x00000000 पूर्ण,
	अणु 0x23, 0x00000000 पूर्ण,
	अणु 0x24, 0x00000000 पूर्ण,
	अणु 0x25, 0x00000000 पूर्ण,
	अणु 0x26, 0x00000000 पूर्ण,
	अणु 0x27, 0x00000000 पूर्ण,
	अणु 0x28, 0x00000000 पूर्ण,
	अणु 0x29, 0x00000000 पूर्ण,
	अणु 0x2a, 0x00000000 पूर्ण,
	अणु 0x2b, 0x00000000 पूर्ण,
	अणु 0x2c, 0x00000000 पूर्ण,
	अणु 0x2d, 0x00000000 पूर्ण,
	अणु 0x2e, 0x00000000 पूर्ण,
	अणु 0x2f, 0x00000000 पूर्ण,
	अणु 0x30, 0x01000000 पूर्ण,
	अणु 0x31, 0x20025501 पूर्ण,
	अणु 0x32, 0x00000000 पूर्ण,
	अणु 0x33, 0x105a0000 पूर्ण,
	अणु 0x34, 0x10100000 पूर्ण,
	अणु 0x35, 0x2aaa52aa पूर्ण,
	अणु 0x36, 0x00c00000 पूर्ण,
	अणु 0x37, 0x20046100 पूर्ण,
	अणु 0x50, 0x10022f00 पूर्ण,
	अणु 0x51, 0x003c0000 पूर्ण,
	अणु 0x54, 0x04000000 पूर्ण,
	अणु 0x55, 0x01000000 पूर्ण,
	अणु 0x56, 0x02000000 पूर्ण,
	अणु 0x57, 0x02000000 पूर्ण,
	अणु 0x58, 0x02000000 पूर्ण,
	अणु 0x59, 0x02000000 पूर्ण,
	अणु 0x5b, 0x02000000 पूर्ण,
	अणु 0x5c, 0x00000000 पूर्ण,
	अणु 0x5d, 0x00000000 पूर्ण,
	अणु 0x5e, 0x00000000 पूर्ण,
	अणु 0x5f, 0x00000000 पूर्ण,
	अणु 0x60, 0x02000000 पूर्ण,
	अणु 0x61, 0x00000000 पूर्ण,
	अणु 0x62, 0x00000000 पूर्ण,
	अणु 0x63, 0x00000000 पूर्ण,
	अणु 0x64, 0x00000000 पूर्ण,
	अणु 0x65, 0x02000000 पूर्ण,
	अणु 0x66, 0x00000000 पूर्ण,
	अणु 0x67, 0x00000000 पूर्ण,
	अणु 0x68, 0x00000000 पूर्ण,
	अणु 0x69, 0x00000000 पूर्ण,
	अणु 0x6a, 0x02000000 पूर्ण,
	अणु 0x6c, 0x00000000 पूर्ण,
	अणु 0x6d, 0x00000000 पूर्ण,
	अणु 0x6e, 0x00000000 पूर्ण,
	अणु 0x70, 0x10EC1308 पूर्ण,
	अणु 0x71, 0x00000000 पूर्ण,
	अणु 0x72, 0x00000000 पूर्ण,
	अणु 0x73, 0x00000000 पूर्ण,
	अणु 0x74, 0x00000000 पूर्ण,
	अणु 0x75, 0x00000000 पूर्ण,
	अणु 0x76, 0x00000000 पूर्ण,
	अणु 0x77, 0x00000000 पूर्ण,
	अणु 0x78, 0x00000000 पूर्ण,
	अणु 0x79, 0x00000000 पूर्ण,
	अणु 0x7a, 0x00000000 पूर्ण,
	अणु 0x7b, 0x00000000 पूर्ण,
	अणु 0x7c, 0x00000000 पूर्ण,
	अणु 0x7d, 0x00000000 पूर्ण,
	अणु 0x7e, 0x00000000 पूर्ण,
	अणु 0x7f, 0x00020f00 पूर्ण,
	अणु 0x80, 0x00000000 पूर्ण,
	अणु 0x81, 0x00000000 पूर्ण,
	अणु 0x82, 0x00000000 पूर्ण,
	अणु 0x83, 0x00000000 पूर्ण,
	अणु 0x84, 0x00000000 पूर्ण,
	अणु 0x85, 0x00000000 पूर्ण,
	अणु 0x86, 0x00000000 पूर्ण,
	अणु 0x87, 0x00000000 पूर्ण,
	अणु 0x88, 0x00000000 पूर्ण,
	अणु 0x89, 0x00000000 पूर्ण,
	अणु 0x8a, 0x00000000 पूर्ण,
	अणु 0x8b, 0x00000000 पूर्ण,
	अणु 0x8c, 0x00000000 पूर्ण,
	अणु 0x8d, 0x00000000 पूर्ण,
	अणु 0x8e, 0x00000000 पूर्ण,
	अणु 0x90, 0x50250905 पूर्ण,
	अणु 0x91, 0x15050000 पूर्ण,
	अणु 0xa0, 0x00000000 पूर्ण,
	अणु 0xa1, 0x00000000 पूर्ण,
	अणु 0xa2, 0x00000000 पूर्ण,
	अणु 0xa3, 0x00000000 पूर्ण,
	अणु 0xa4, 0x00000000 पूर्ण,
	अणु 0xb0, 0x00000000 पूर्ण,
	अणु 0xb1, 0x00000000 पूर्ण,
	अणु 0xb2, 0x00000000 पूर्ण,
	अणु 0xb3, 0x00000000 पूर्ण,
	अणु 0xb4, 0x00000000 पूर्ण,
	अणु 0xb5, 0x00000000 पूर्ण,
	अणु 0xb6, 0x00000000 पूर्ण,
	अणु 0xb7, 0x00000000 पूर्ण,
	अणु 0xb8, 0x00000000 पूर्ण,
	अणु 0xb9, 0x00000000 पूर्ण,
	अणु 0xba, 0x00000000 पूर्ण,
	अणु 0xbb, 0x00000000 पूर्ण,
	अणु 0xc0, 0x01000000 पूर्ण,
	अणु 0xc1, 0x00000000 पूर्ण,
	अणु 0xf0, 0x00000000 पूर्ण,
पूर्ण;

अटल पूर्णांक rt1308_reg_init(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1308_priv *rt1308 = snd_soc_component_get_drvdata(component);

	वापस regmap_multi_reg_ग_लिखो(rt1308->regmap, init_list,
				RT1308_INIT_REG_LEN);
पूर्ण

अटल bool rt1308_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT1308_RESET:
	हाल RT1308_RESET_N:
	हाल RT1308_CLK_2:
	हाल RT1308_SIL_DET:
	हाल RT1308_CLK_DET:
	हाल RT1308_DC_DET:
	हाल RT1308_DAC_SET:
	हाल RT1308_DAC_BUF:
	हाल RT1308_SDW_REG_RDATA:
	हाल RT1308_DC_CAL_1:
	हाल RT1308_PVDD_OFFSET_CTL:
	हाल RT1308_CAL_OFFSET_DAC_PBTL:
	हाल RT1308_CAL_OFFSET_DAC_L:
	हाल RT1308_CAL_OFFSET_DAC_R:
	हाल RT1308_CAL_OFFSET_PWM_L:
	हाल RT1308_CAL_OFFSET_PWM_R:
	हाल RT1308_CAL_PWM_VOS_ADC_L:
	हाल RT1308_CAL_PWM_VOS_ADC_R:
	हाल RT1308_MBIAS:
	हाल RT1308_POWER_STATUS:
	हाल RT1308_POWER_INT:
	हाल RT1308_SINE_TONE_GEN_2:
	हाल RT1308_BQ_SET:
	हाल RT1308_BQ_PARA_UPDATE:
	हाल RT1308_VEN_DEV_ID:
	हाल RT1308_VERSION_ID:
	हाल RT1308_EFUSE_1:
	हाल RT1308_EFUSE_READ_PVDD_L:
	हाल RT1308_EFUSE_READ_PVDD_R:
	हाल RT1308_EFUSE_READ_PVDD_PTBL:
	हाल RT1308_EFUSE_READ_DEV:
	हाल RT1308_EFUSE_READ_R0:
	हाल RT1308_EFUSE_READ_ADC_L:
	हाल RT1308_EFUSE_READ_ADC_R:
	हाल RT1308_EFUSE_READ_ADC_PBTL:
	हाल RT1308_EFUSE_RESERVE:
	हाल RT1308_EFUSE_DATA_0_MSB:
	हाल RT1308_EFUSE_DATA_0_LSB:
	हाल RT1308_EFUSE_DATA_1_MSB:
	हाल RT1308_EFUSE_DATA_1_LSB:
	हाल RT1308_EFUSE_DATA_2_MSB:
	हाल RT1308_EFUSE_DATA_2_LSB:
	हाल RT1308_EFUSE_DATA_3_MSB:
	हाल RT1308_EFUSE_DATA_3_LSB:
	हाल RT1308_EFUSE_STATUS_1:
	हाल RT1308_EFUSE_STATUS_2:
	हाल RT1308_DUMMY_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt1308_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT1308_RESET:
	हाल RT1308_RESET_N:
	हाल RT1308_CLK_GATING ... RT1308_DC_DET_THRES:
	हाल RT1308_DAC_SET ... RT1308_AD_FILTER_SET:
	हाल RT1308_DC_CAL_1 ... RT1308_POWER_INT:
	हाल RT1308_SINE_TONE_GEN_1:
	हाल RT1308_SINE_TONE_GEN_2:
	हाल RT1308_BQ_SET:
	हाल RT1308_BQ_PARA_UPDATE:
	हाल RT1308_BQ_PRE_VOL_L ... RT1308_BQ_POST_VOL_R:
	हाल RT1308_BQ1_L_H0 ... RT1308_BQ2_R_A2:
	हाल RT1308_VEN_DEV_ID:
	हाल RT1308_VERSION_ID:
	हाल RT1308_SPK_BOUND:
	हाल RT1308_BQ1_EQ_L_1 ... RT1308_BQ2_EQ_R_3:
	हाल RT1308_EFUSE_1 ... RT1308_EFUSE_RESERVE:
	हाल RT1308_PADS_1:
	हाल RT1308_PADS_2:
	हाल RT1308_TEST_MODE:
	हाल RT1308_TEST_1:
	हाल RT1308_TEST_2:
	हाल RT1308_TEST_3:
	हाल RT1308_TEST_4:
	हाल RT1308_EFUSE_DATA_0_MSB ... RT1308_EFUSE_STATUS_2:
	हाल RT1308_TCON_1:
	हाल RT1308_TCON_2:
	हाल RT1308_DUMMY_REG:
	हाल RT1308_MAX_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक rt1308_classd_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		msleep(30);
		snd_soc_component_update_bits(component, RT1308_POWER_STATUS,
			RT1308_POW_PDB_REG_BIT | RT1308_POW_PDB_MN_BIT,
			RT1308_POW_PDB_REG_BIT | RT1308_POW_PDB_MN_BIT);
		msleep(40);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT1308_POWER_STATUS,
			RT1308_POW_PDB_REG_BIT | RT1308_POW_PDB_MN_BIT, 0);
		usleep_range(150000, 200000);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर rt1308_rx_data_ch_select[] = अणु
	"LR",
	"LL",
	"RL",
	"RR",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt1308_rx_data_ch_क्रमागत, RT1308_DATA_PATH, 24,
	rt1308_rx_data_ch_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt1308_snd_controls[] = अणु

	/* I2S Data Channel Selection */
	SOC_ENUM("RX Channel Select", rt1308_rx_data_ch_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt1308_sto_dac_l =
	SOC_DAPM_SINGLE("Switch", RT1308_DAC_SET,
		RT1308_DVOL_MUTE_L_EN_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new rt1308_sto_dac_r =
	SOC_DAPM_SINGLE("Switch", RT1308_DAC_SET,
		RT1308_DVOL_MUTE_R_EN_SFT, 1, 1);

अटल स्थिर काष्ठा snd_soc_dapm_widget rt1308_dapm_widमाला_लो[] = अणु
	/* Audio Interface */
	SND_SOC_DAPM_AIF_IN("AIF1RX", "AIF1 Playback", 0, SND_SOC_NOPM, 0, 0),

	/* Supply Widमाला_लो */
	SND_SOC_DAPM_SUPPLY("MBIAS20U", RT1308_POWER,
		RT1308_POW_MBIAS20U_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ALDO", RT1308_POWER,
		RT1308_POW_ALDO_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DBG", RT1308_POWER,
		RT1308_POW_DBG_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DACL", RT1308_POWER,
		RT1308_POW_DACL_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CLK25M", RT1308_POWER,
		RT1308_POW_CLK25M_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC_R", RT1308_POWER,
		RT1308_POW_ADC_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC_L", RT1308_POWER,
		RT1308_POW_ADC_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DLDO", RT1308_POWER,
		RT1308_POW_DLDO_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("VREF", RT1308_POWER,
		RT1308_POW_VREF_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MIXER_R", RT1308_POWER,
		RT1308_POW_MIXER_R_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MIXER_L", RT1308_POWER,
		RT1308_POW_MIXER_L_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MBIAS4U", RT1308_POWER,
		RT1308_POW_MBIAS4U_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL2_LDO", RT1308_POWER,
		RT1308_POW_PLL2_LDO_EN_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL2B", RT1308_POWER,
		RT1308_POW_PLL2B_EN_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL2F", RT1308_POWER,
		RT1308_POW_PLL2F_EN_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL2F2", RT1308_POWER,
		RT1308_POW_PLL2F2_EN_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL2B2", RT1308_POWER,
		RT1308_POW_PLL2B2_EN_BIT, 0, शून्य, 0),

	/* Digital Interface */
	SND_SOC_DAPM_SUPPLY("DAC Power", RT1308_POWER,
		RT1308_POW_DAC1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_DAC("DAC", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_SWITCH("DAC L", SND_SOC_NOPM, 0, 0, &rt1308_sto_dac_l),
	SND_SOC_DAPM_SWITCH("DAC R", SND_SOC_NOPM, 0, 0, &rt1308_sto_dac_r),

	/* Output Lines */
	SND_SOC_DAPM_PGA_E("CLASS D", SND_SOC_NOPM, 0, 0, शून्य, 0,
		rt1308_classd_event,
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_OUTPUT("SPOL"),
	SND_SOC_DAPM_OUTPUT("SPOR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt1308_dapm_routes[] = अणु

	अणु "DAC", शून्य, "AIF1RX" पूर्ण,

	अणु "DAC", शून्य, "MBIAS20U" पूर्ण,
	अणु "DAC", शून्य, "ALDO" पूर्ण,
	अणु "DAC", शून्य, "DBG" पूर्ण,
	अणु "DAC", शून्य, "DACL" पूर्ण,
	अणु "DAC", शून्य, "CLK25M" पूर्ण,
	अणु "DAC", शून्य, "ADC_R" पूर्ण,
	अणु "DAC", शून्य, "ADC_L" पूर्ण,
	अणु "DAC", शून्य, "DLDO" पूर्ण,
	अणु "DAC", शून्य, "VREF" पूर्ण,
	अणु "DAC", शून्य, "MIXER_R" पूर्ण,
	अणु "DAC", शून्य, "MIXER_L" पूर्ण,
	अणु "DAC", शून्य, "MBIAS4U" पूर्ण,
	अणु "DAC", शून्य, "PLL2_LDO" पूर्ण,
	अणु "DAC", शून्य, "PLL2B" पूर्ण,
	अणु "DAC", शून्य, "PLL2F" पूर्ण,
	अणु "DAC", शून्य, "PLL2F2" पूर्ण,
	अणु "DAC", शून्य, "PLL2B2" पूर्ण,

	अणु "DAC L", "Switch", "DAC" पूर्ण,
	अणु "DAC R", "Switch", "DAC" पूर्ण,
	अणु "DAC L", शून्य, "DAC Power" पूर्ण,
	अणु "DAC R", शून्य, "DAC Power" पूर्ण,

	अणु "CLASS D", शून्य, "DAC L" पूर्ण,
	अणु "CLASS D", शून्य, "DAC R" पूर्ण,
	अणु "SPOL", शून्य, "CLASS D" पूर्ण,
	अणु "SPOR", शून्य, "CLASS D" पूर्ण,
पूर्ण;

अटल पूर्णांक rt1308_get_clk_info(पूर्णांक sclk, पूर्णांक rate)
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

अटल पूर्णांक rt1308_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt1308_priv *rt1308 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val_len = 0, val_clk, mask_clk;
	पूर्णांक pre_भाग, bclk_ms, frame_size;

	rt1308->lrck = params_rate(params);
	pre_भाग = rt1308_get_clk_info(rt1308->sysclk, rt1308->lrck);
	अगर (pre_भाग < 0) अणु
		dev_err(component->dev,
			"Unsupported clock setting %d\n", rt1308->lrck);
		वापस -EINVAL;
	पूर्ण

	frame_size = snd_soc_params_to_frame_size(params);
	अगर (frame_size < 0) अणु
		dev_err(component->dev, "Unsupported frame size: %d\n",
			frame_size);
		वापस -EINVAL;
	पूर्ण

	bclk_ms = frame_size > 32;
	rt1308->bclk = rt1308->lrck * (32 << bclk_ms);

	dev_dbg(component->dev, "bclk_ms is %d and pre_div is %d for iis %d\n",
				bclk_ms, pre_भाग, dai->id);

	dev_dbg(component->dev, "lrck is %dHz and pre_div is %d for iis %d\n",
				rt1308->lrck, pre_भाग, dai->id);

	चयन (params_width(params)) अणु
	हाल 16:
		val_len |= RT1308_I2S_DL_SEL_16B;
		अवरोध;
	हाल 20:
		val_len |= RT1308_I2S_DL_SEL_20B;
		अवरोध;
	हाल 24:
		val_len |= RT1308_I2S_DL_SEL_24B;
		अवरोध;
	हाल 8:
		val_len |= RT1308_I2S_DL_SEL_8B;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT1308_AIF1:
		mask_clk = RT1308_DIV_FS_SYS_MASK;
		val_clk = pre_भाग << RT1308_DIV_FS_SYS_SFT;
		snd_soc_component_update_bits(component,
			RT1308_I2S_SET_2, RT1308_I2S_DL_SEL_MASK,
			val_len);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, RT1308_CLK_1,
		mask_clk, val_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1308_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt1308_priv *rt1308 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0, reg1_val = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		rt1308->master = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT1308_I2S_DF_SEL_LEFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT1308_I2S_DF_SEL_PCM_A;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		reg_val |= RT1308_I2S_DF_SEL_PCM_B;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		reg1_val |= RT1308_I2S_BCLK_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT1308_AIF1:
		snd_soc_component_update_bits(component,
			RT1308_I2S_SET_1, RT1308_I2S_DF_SEL_MASK,
			reg_val);
		snd_soc_component_update_bits(component,
			RT1308_I2S_SET_2, RT1308_I2S_BCLK_MASK,
			reg1_val);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt1308_set_component_sysclk(काष्ठा snd_soc_component *component,
		पूर्णांक clk_id, पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा rt1308_priv *rt1308 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;

	अगर (freq == rt1308->sysclk && clk_id == rt1308->sysclk_src)
		वापस 0;

	चयन (clk_id) अणु
	हाल RT1308_FS_SYS_S_MCLK:
		reg_val |= RT1308_SEL_FS_SYS_SRC_MCLK;
		snd_soc_component_update_bits(component,
			RT1308_CLK_DET, RT1308_MCLK_DET_EN_MASK,
			RT1308_MCLK_DET_EN);
		अवरोध;
	हाल RT1308_FS_SYS_S_BCLK:
		reg_val |= RT1308_SEL_FS_SYS_SRC_BCLK;
		अवरोध;
	हाल RT1308_FS_SYS_S_PLL:
		reg_val |= RT1308_SEL_FS_SYS_SRC_PLL;
		अवरोध;
	हाल RT1308_FS_SYS_S_RCCLK:
		reg_val |= RT1308_SEL_FS_SYS_SRC_RCCLK;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_update_bits(component, RT1308_CLK_1,
		RT1308_SEL_FS_SYS_MASK, reg_val);
	rt1308->sysclk = freq;
	rt1308->sysclk_src = clk_id;

	dev_dbg(component->dev, "Sysclk is %dHz and clock id is %d\n",
		freq, clk_id);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1308_set_component_pll(काष्ठा snd_soc_component *component,
		पूर्णांक pll_id, पूर्णांक source, अचिन्हित पूर्णांक freq_in,
		अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा rt1308_priv *rt1308 = snd_soc_component_get_drvdata(component);
	काष्ठा rl6231_pll_code pll_code;
	पूर्णांक ret;

	अगर (source == rt1308->pll_src && freq_in == rt1308->pll_in &&
	    freq_out == rt1308->pll_out)
		वापस 0;

	अगर (!freq_in || !freq_out) अणु
		dev_dbg(component->dev, "PLL disabled\n");

		rt1308->pll_in = 0;
		rt1308->pll_out = 0;
		snd_soc_component_update_bits(component,
			RT1308_CLK_1, RT1308_SEL_FS_SYS_MASK,
			RT1308_SEL_FS_SYS_SRC_MCLK);
		वापस 0;
	पूर्ण

	चयन (source) अणु
	हाल RT1308_PLL_S_MCLK:
		snd_soc_component_update_bits(component,
			RT1308_CLK_2, RT1308_SEL_PLL_SRC_MASK,
			RT1308_SEL_PLL_SRC_MCLK);
		snd_soc_component_update_bits(component,
			RT1308_CLK_DET, RT1308_MCLK_DET_EN_MASK,
			RT1308_MCLK_DET_EN);
		अवरोध;
	हाल RT1308_PLL_S_BCLK:
		snd_soc_component_update_bits(component,
			RT1308_CLK_2, RT1308_SEL_PLL_SRC_MASK,
			RT1308_SEL_PLL_SRC_BCLK);
		अवरोध;
	हाल RT1308_PLL_S_RCCLK:
		snd_soc_component_update_bits(component,
			RT1308_CLK_2, RT1308_SEL_PLL_SRC_MASK,
			RT1308_SEL_PLL_SRC_RCCLK);
		freq_in = 25000000;
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

	snd_soc_component_ग_लिखो(component, RT1308_PLL_1,
		(pll_code.k_code << RT1308_PLL1_K_SFT) |
		(pll_code.m_bp << RT1308_PLL1_M_BYPASS_SFT) |
		((pll_code.m_bp ? 0 : pll_code.m_code) << RT1308_PLL1_M_SFT) |
		(pll_code.n_code << RT1308_PLL1_N_SFT));

	rt1308->pll_in = freq_in;
	rt1308->pll_out = freq_out;
	rt1308->pll_src = source;

	वापस 0;
पूर्ण

अटल पूर्णांक rt1308_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1308_priv *rt1308 = snd_soc_component_get_drvdata(component);

	rt1308->component = component;

	वापस rt1308_reg_init(component);
पूर्ण

अटल व्योम rt1308_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1308_priv *rt1308 = snd_soc_component_get_drvdata(component);

	regmap_ग_लिखो(rt1308->regmap, RT1308_RESET, 0);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rt1308_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1308_priv *rt1308 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt1308->regmap, true);
	regcache_mark_dirty(rt1308->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1308_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1308_priv *rt1308 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt1308->regmap, false);
	regcache_sync(rt1308->regmap);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा rt1308_suspend शून्य
#घोषणा rt1308_resume शून्य
#पूर्ण_अगर

#घोषणा RT1308_STEREO_RATES SNDRV_PCM_RATE_48000
#घोषणा RT1308_FORMATS (SNDRV_PCM_FMTBIT_S8 | \
			SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S16_LE | \
			SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops rt1308_aअगर_dai_ops = अणु
	.hw_params = rt1308_hw_params,
	.set_fmt = rt1308_set_dai_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt1308_dai[] = अणु
	अणु
		.name = "rt1308-aif",
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT1308_STEREO_RATES,
			.क्रमmats = RT1308_FORMATS,
		पूर्ण,
		.ops = &rt1308_aअगर_dai_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_rt1308 = अणु
	.probe = rt1308_probe,
	.हटाओ = rt1308_हटाओ,
	.suspend = rt1308_suspend,
	.resume = rt1308_resume,
	.controls = rt1308_snd_controls,
	.num_controls = ARRAY_SIZE(rt1308_snd_controls),
	.dapm_widमाला_लो = rt1308_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(rt1308_dapm_widमाला_लो),
	.dapm_routes = rt1308_dapm_routes,
	.num_dapm_routes = ARRAY_SIZE(rt1308_dapm_routes),
	.set_sysclk = rt1308_set_component_sysclk,
	.set_pll = rt1308_set_component_pll,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt1308_regmap = अणु
	.reg_bits = 8,
	.val_bits = 32,
	.max_रेजिस्टर = RT1308_MAX_REG,
	.अस्थिर_reg = rt1308_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = rt1308_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = rt1308_reg,
	.num_reg_शेषs = ARRAY_SIZE(rt1308_reg),
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id rt1308_of_match[] = अणु
	अणु .compatible = "realtek,rt1308", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt1308_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id rt1308_acpi_match[] = अणु
	अणु "10EC1308", 0, पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rt1308_acpi_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id rt1308_i2c_id[] = अणु
	अणु "rt1308", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt1308_i2c_id);

अटल व्योम rt1308_efuse(काष्ठा rt1308_priv *rt1308)
अणु
	regmap_ग_लिखो(rt1308->regmap, RT1308_RESET, 0);

	regmap_ग_लिखो(rt1308->regmap, RT1308_POWER_STATUS, 0x01800000);
	msleep(100);
	regmap_ग_लिखो(rt1308->regmap, RT1308_EFUSE_1, 0x44fe0f00);
	msleep(20);
	regmap_ग_लिखो(rt1308->regmap, RT1308_PVDD_OFFSET_CTL, 0x10000000);
पूर्ण

अटल पूर्णांक rt1308_i2c_probe(काष्ठा i2c_client *i2c,
		    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rt1308_priv *rt1308;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	rt1308 = devm_kzalloc(&i2c->dev, माप(काष्ठा rt1308_priv),
				GFP_KERNEL);
	अगर (rt1308 == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, rt1308);

	rt1308->regmap = devm_regmap_init_i2c(i2c, &rt1308_regmap);
	अगर (IS_ERR(rt1308->regmap)) अणु
		ret = PTR_ERR(rt1308->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	regmap_पढ़ो(rt1308->regmap, RT1308_VEN_DEV_ID, &val);
	/* ignore last byte dअगरference */
	अगर ((val & 0xFFFFFF00) != RT1308_DEVICE_ID_NUM) अणु
		dev_err(&i2c->dev,
			"Device with ID register %x is not rt1308\n", val);
		वापस -ENODEV;
	पूर्ण

	rt1308_efuse(rt1308);

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_rt1308,
			rt1308_dai, ARRAY_SIZE(rt1308_dai));
पूर्ण

अटल व्योम rt1308_i2c_shutकरोwn(काष्ठा i2c_client *client)
अणु
	काष्ठा rt1308_priv *rt1308 = i2c_get_clientdata(client);

	regmap_ग_लिखो(rt1308->regmap, RT1308_RESET, 0);
पूर्ण

अटल काष्ठा i2c_driver rt1308_i2c_driver = अणु
	.driver = अणु
		.name = "rt1308",
		.of_match_table = of_match_ptr(rt1308_of_match),
		.acpi_match_table = ACPI_PTR(rt1308_acpi_match),
	पूर्ण,
	.probe = rt1308_i2c_probe,
	.shutकरोwn = rt1308_i2c_shutकरोwn,
	.id_table = rt1308_i2c_id,
पूर्ण;
module_i2c_driver(rt1308_i2c_driver);

MODULE_DESCRIPTION("ASoC RT1308 amplifier driver");
MODULE_AUTHOR("Derek Fang <derek.fang@realtek.com>");
MODULE_LICENSE("GPL v2");
