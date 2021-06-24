<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SSM2518 amplअगरier audio driver
 *
 * Copyright 2013 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/platक्रमm_data/ssm2518.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "ssm2518.h"

#घोषणा SSM2518_REG_POWER1		0x00
#घोषणा SSM2518_REG_CLOCK		0x01
#घोषणा SSM2518_REG_SAI_CTRL1		0x02
#घोषणा SSM2518_REG_SAI_CTRL2		0x03
#घोषणा SSM2518_REG_CHAN_MAP		0x04
#घोषणा SSM2518_REG_LEFT_VOL		0x05
#घोषणा SSM2518_REG_RIGHT_VOL		0x06
#घोषणा SSM2518_REG_MUTE_CTRL		0x07
#घोषणा SSM2518_REG_FAULT_CTRL		0x08
#घोषणा SSM2518_REG_POWER2		0x09
#घोषणा SSM2518_REG_DRC_1		0x0a
#घोषणा SSM2518_REG_DRC_2		0x0b
#घोषणा SSM2518_REG_DRC_3		0x0c
#घोषणा SSM2518_REG_DRC_4		0x0d
#घोषणा SSM2518_REG_DRC_5		0x0e
#घोषणा SSM2518_REG_DRC_6		0x0f
#घोषणा SSM2518_REG_DRC_7		0x10
#घोषणा SSM2518_REG_DRC_8		0x11
#घोषणा SSM2518_REG_DRC_9		0x12

#घोषणा SSM2518_POWER1_RESET			BIT(7)
#घोषणा SSM2518_POWER1_NO_BCLK			BIT(5)
#घोषणा SSM2518_POWER1_MCS_MASK			(0xf << 1)
#घोषणा SSM2518_POWER1_MCS_64FS			(0x0 << 1)
#घोषणा SSM2518_POWER1_MCS_128FS		(0x1 << 1)
#घोषणा SSM2518_POWER1_MCS_256FS		(0x2 << 1)
#घोषणा SSM2518_POWER1_MCS_384FS		(0x3 << 1)
#घोषणा SSM2518_POWER1_MCS_512FS		(0x4 << 1)
#घोषणा SSM2518_POWER1_MCS_768FS		(0x5 << 1)
#घोषणा SSM2518_POWER1_MCS_100FS		(0x6 << 1)
#घोषणा SSM2518_POWER1_MCS_200FS		(0x7 << 1)
#घोषणा SSM2518_POWER1_MCS_400FS		(0x8 << 1)
#घोषणा SSM2518_POWER1_SPWDN			BIT(0)

#घोषणा SSM2518_CLOCK_ASR			BIT(0)

#घोषणा SSM2518_SAI_CTRL1_FMT_MASK		(0x3 << 5)
#घोषणा SSM2518_SAI_CTRL1_FMT_I2S		(0x0 << 5)
#घोषणा SSM2518_SAI_CTRL1_FMT_LJ		(0x1 << 5)
#घोषणा SSM2518_SAI_CTRL1_FMT_RJ_24BIT		(0x2 << 5)
#घोषणा SSM2518_SAI_CTRL1_FMT_RJ_16BIT		(0x3 << 5)

#घोषणा SSM2518_SAI_CTRL1_SAI_MASK		(0x7 << 2)
#घोषणा SSM2518_SAI_CTRL1_SAI_I2S		(0x0 << 2)
#घोषणा SSM2518_SAI_CTRL1_SAI_TDM_2		(0x1 << 2)
#घोषणा SSM2518_SAI_CTRL1_SAI_TDM_4		(0x2 << 2)
#घोषणा SSM2518_SAI_CTRL1_SAI_TDM_8		(0x3 << 2)
#घोषणा SSM2518_SAI_CTRL1_SAI_TDM_16		(0x4 << 2)
#घोषणा SSM2518_SAI_CTRL1_SAI_MONO		(0x5 << 2)

#घोषणा SSM2518_SAI_CTRL1_FS_MASK		(0x3)
#घोषणा SSM2518_SAI_CTRL1_FS_8000_12000		(0x0)
#घोषणा SSM2518_SAI_CTRL1_FS_16000_24000	(0x1)
#घोषणा SSM2518_SAI_CTRL1_FS_32000_48000	(0x2)
#घोषणा SSM2518_SAI_CTRL1_FS_64000_96000	(0x3)

#घोषणा SSM2518_SAI_CTRL2_BCLK_INTERAL		BIT(7)
#घोषणा SSM2518_SAI_CTRL2_LRCLK_PULSE		BIT(6)
#घोषणा SSM2518_SAI_CTRL2_LRCLK_INVERT		BIT(5)
#घोषणा SSM2518_SAI_CTRL2_MSB			BIT(4)
#घोषणा SSM2518_SAI_CTRL2_SLOT_WIDTH_MASK	(0x3 << 2)
#घोषणा SSM2518_SAI_CTRL2_SLOT_WIDTH_32		(0x0 << 2)
#घोषणा SSM2518_SAI_CTRL2_SLOT_WIDTH_24		(0x1 << 2)
#घोषणा SSM2518_SAI_CTRL2_SLOT_WIDTH_16		(0x2 << 2)
#घोषणा SSM2518_SAI_CTRL2_BCLK_INVERT		BIT(1)

#घोषणा SSM2518_CHAN_MAP_RIGHT_SLOT_OFFSET	4
#घोषणा SSM2518_CHAN_MAP_RIGHT_SLOT_MASK	0xf0
#घोषणा SSM2518_CHAN_MAP_LEFT_SLOT_OFFSET	0
#घोषणा SSM2518_CHAN_MAP_LEFT_SLOT_MASK		0x0f

#घोषणा SSM2518_MUTE_CTRL_ANA_GAIN		BIT(5)
#घोषणा SSM2518_MUTE_CTRL_MUTE_MASTER		BIT(0)

#घोषणा SSM2518_POWER2_APWDN			BIT(0)

#घोषणा SSM2518_DAC_MUTE			BIT(6)
#घोषणा SSM2518_DAC_FS_MASK			0x07
#घोषणा SSM2518_DAC_FS_8000			0x00
#घोषणा SSM2518_DAC_FS_16000			0x01
#घोषणा SSM2518_DAC_FS_32000			0x02
#घोषणा SSM2518_DAC_FS_64000			0x03
#घोषणा SSM2518_DAC_FS_128000			0x04

काष्ठा ssm2518 अणु
	काष्ठा regmap *regmap;
	bool right_j;

	अचिन्हित पूर्णांक sysclk;
	स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list *स्थिरraपूर्णांकs;

	पूर्णांक enable_gpio;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष ssm2518_reg_शेषs[] = अणु
	अणु 0x00, 0x05 पूर्ण,
	अणु 0x01, 0x00 पूर्ण,
	अणु 0x02, 0x02 पूर्ण,
	अणु 0x03, 0x00 पूर्ण,
	अणु 0x04, 0x10 पूर्ण,
	अणु 0x05, 0x40 पूर्ण,
	अणु 0x06, 0x40 पूर्ण,
	अणु 0x07, 0x81 पूर्ण,
	अणु 0x08, 0x0c पूर्ण,
	अणु 0x09, 0x99 पूर्ण,
	अणु 0x0a, 0x7c पूर्ण,
	अणु 0x0b, 0x5b पूर्ण,
	अणु 0x0c, 0x57 पूर्ण,
	अणु 0x0d, 0x89 पूर्ण,
	अणु 0x0e, 0x8c पूर्ण,
	अणु 0x0f, 0x77 पूर्ण,
	अणु 0x10, 0x26 पूर्ण,
	अणु 0x11, 0x1c पूर्ण,
	अणु 0x12, 0x97 पूर्ण,
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_MINMAX_MUTE(ssm2518_vol_tlv, -7125, 2400);
अटल स्थिर DECLARE_TLV_DB_SCALE(ssm2518_compressor_tlv, -3400, 200, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(ssm2518_expander_tlv, -8100, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(ssm2518_noise_gate_tlv, -9600, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(ssm2518_post_drc_tlv, -2400, 300, 0);

अटल स्थिर DECLARE_TLV_DB_RANGE(ssm2518_limiter_tlv,
	0, 7, TLV_DB_SCALE_ITEM(-2200, 200, 0),
	7, 15, TLV_DB_SCALE_ITEM(-800, 100, 0),
);

अटल स्थिर अक्षर * स्थिर ssm2518_drc_peak_detector_attack_समय_प्रकारext[] = अणु
	"0 ms", "0.1 ms", "0.19 ms", "0.37 ms", "0.75 ms", "1.5 ms", "3 ms",
	"6 ms", "12 ms", "24 ms", "48 ms", "96 ms", "192 ms", "384 ms",
	"768 ms", "1536 ms",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ssm2518_drc_peak_detector_release_समय_प्रकारext[] = अणु
	"0 ms", "1.5 ms", "3 ms", "6 ms", "12 ms", "24 ms", "48 ms", "96 ms",
	"192 ms", "384 ms", "768 ms", "1536 ms", "3072 ms", "6144 ms",
	"12288 ms", "24576 ms"
पूर्ण;

अटल स्थिर अक्षर * स्थिर ssm2518_drc_hold_समय_प्रकारext[] = अणु
	"0 ms", "0.67 ms", "1.33 ms", "2.67 ms", "5.33 ms", "10.66 ms",
	"21.32 ms", "42.64 ms", "85.28 ms", "170.56 ms", "341.12 ms",
	"682.24 ms", "1364 ms",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(ssm2518_drc_peak_detector_attack_समय_क्रमागत,
	SSM2518_REG_DRC_2, 4, ssm2518_drc_peak_detector_attack_समय_प्रकारext);
अटल SOC_ENUM_SINGLE_DECL(ssm2518_drc_peak_detector_release_समय_क्रमागत,
	SSM2518_REG_DRC_2, 0, ssm2518_drc_peak_detector_release_समय_प्रकारext);
अटल SOC_ENUM_SINGLE_DECL(ssm2518_drc_attack_समय_क्रमागत,
	SSM2518_REG_DRC_6, 4, ssm2518_drc_peak_detector_attack_समय_प्रकारext);
अटल SOC_ENUM_SINGLE_DECL(ssm2518_drc_decay_समय_क्रमागत,
	SSM2518_REG_DRC_6, 0, ssm2518_drc_peak_detector_release_समय_प्रकारext);
अटल SOC_ENUM_SINGLE_DECL(ssm2518_drc_hold_समय_क्रमागत,
	SSM2518_REG_DRC_7, 4, ssm2518_drc_hold_समय_प्रकारext);
अटल SOC_ENUM_SINGLE_DECL(ssm2518_drc_noise_gate_hold_समय_क्रमागत,
	SSM2518_REG_DRC_7, 0, ssm2518_drc_hold_समय_प्रकारext);
अटल SOC_ENUM_SINGLE_DECL(ssm2518_drc_rms_averaging_समय_क्रमागत,
	SSM2518_REG_DRC_9, 0, ssm2518_drc_peak_detector_release_समय_प्रकारext);

अटल स्थिर काष्ठा snd_kcontrol_new ssm2518_snd_controls[] = अणु
	SOC_SINGLE("Playback De-emphasis Switch", SSM2518_REG_MUTE_CTRL,
			4, 1, 0),
	SOC_DOUBLE_R_TLV("Master Playback Volume", SSM2518_REG_LEFT_VOL,
			SSM2518_REG_RIGHT_VOL, 0, 0xff, 1, ssm2518_vol_tlv),
	SOC_DOUBLE("Master Playback Switch", SSM2518_REG_MUTE_CTRL, 2, 1, 1, 1),

	SOC_SINGLE("Amp Low Power Mode Switch", SSM2518_REG_POWER2, 4, 1, 0),
	SOC_SINGLE("DAC Low Power Mode Switch", SSM2518_REG_POWER2, 3, 1, 0),

	SOC_SINGLE("DRC Limiter Switch", SSM2518_REG_DRC_1, 5, 1, 0),
	SOC_SINGLE("DRC Compressor Switch", SSM2518_REG_DRC_1, 4, 1, 0),
	SOC_SINGLE("DRC Expander Switch", SSM2518_REG_DRC_1, 3, 1, 0),
	SOC_SINGLE("DRC Noise Gate Switch", SSM2518_REG_DRC_1, 2, 1, 0),
	SOC_DOUBLE("DRC Switch", SSM2518_REG_DRC_1, 0, 1, 1, 0),

	SOC_SINGLE_TLV("DRC Limiter Threshold Volume",
			SSM2518_REG_DRC_3, 4, 15, 1, ssm2518_limiter_tlv),
	SOC_SINGLE_TLV("DRC Compressor Lower Threshold Volume",
			SSM2518_REG_DRC_3, 0, 15, 1, ssm2518_compressor_tlv),
	SOC_SINGLE_TLV("DRC Expander Upper Threshold Volume", SSM2518_REG_DRC_4,
			4, 15, 1, ssm2518_expander_tlv),
	SOC_SINGLE_TLV("DRC Noise Gate Threshold Volume",
			SSM2518_REG_DRC_4, 0, 15, 1, ssm2518_noise_gate_tlv),
	SOC_SINGLE_TLV("DRC Upper Output Threshold Volume",
			SSM2518_REG_DRC_5, 4, 15, 1, ssm2518_limiter_tlv),
	SOC_SINGLE_TLV("DRC Lower Output Threshold Volume",
			SSM2518_REG_DRC_5, 0, 15, 1, ssm2518_noise_gate_tlv),
	SOC_SINGLE_TLV("DRC Post Volume", SSM2518_REG_DRC_8,
			2, 15, 1, ssm2518_post_drc_tlv),

	SOC_ENUM("DRC Peak Detector Attack Time",
		ssm2518_drc_peak_detector_attack_समय_क्रमागत),
	SOC_ENUM("DRC Peak Detector Release Time",
		ssm2518_drc_peak_detector_release_समय_क्रमागत),
	SOC_ENUM("DRC Attack Time", ssm2518_drc_attack_समय_क्रमागत),
	SOC_ENUM("DRC Decay Time", ssm2518_drc_decay_समय_क्रमागत),
	SOC_ENUM("DRC Hold Time", ssm2518_drc_hold_समय_क्रमागत),
	SOC_ENUM("DRC Noise Gate Hold Time",
		ssm2518_drc_noise_gate_hold_समय_क्रमागत),
	SOC_ENUM("DRC RMS Averaging Time", ssm2518_drc_rms_averaging_समय_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget ssm2518_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("DACL", "HiFi Playback", SSM2518_REG_POWER2, 1, 1),
	SND_SOC_DAPM_DAC("DACR", "HiFi Playback", SSM2518_REG_POWER2, 2, 1),

	SND_SOC_DAPM_OUTPUT("OUTL"),
	SND_SOC_DAPM_OUTPUT("OUTR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ssm2518_routes[] = अणु
	अणु "OUTL", शून्य, "DACL" पूर्ण,
	अणु "OUTR", शून्य, "DACR" पूर्ण,
पूर्ण;

काष्ठा ssm2518_mcs_lut अणु
	अचिन्हित पूर्णांक rate;
	स्थिर अचिन्हित पूर्णांक *sysclks;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ssm2518_sysclks_2048000[] = अणु
	2048000, 4096000, 8192000, 12288000, 16384000, 24576000,
	3200000, 6400000, 12800000, 0
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ssm2518_sysclks_2822000[] = अणु
	2822000, 5644800, 11289600, 16934400, 22579200, 33868800,
	4410000, 8820000, 17640000, 0
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ssm2518_sysclks_3072000[] = अणु
	3072000, 6144000, 12288000, 16384000, 24576000, 38864000,
	4800000, 9600000, 19200000, 0
पूर्ण;

अटल स्थिर काष्ठा ssm2518_mcs_lut ssm2518_mcs_lut[] = अणु
	अणु 8000,  ssm2518_sysclks_2048000, पूर्ण,
	अणु 11025, ssm2518_sysclks_2822000, पूर्ण,
	अणु 12000, ssm2518_sysclks_3072000, पूर्ण,
	अणु 16000, ssm2518_sysclks_2048000, पूर्ण,
	अणु 24000, ssm2518_sysclks_3072000, पूर्ण,
	अणु 22050, ssm2518_sysclks_2822000, पूर्ण,
	अणु 32000, ssm2518_sysclks_2048000, पूर्ण,
	अणु 44100, ssm2518_sysclks_2822000, पूर्ण,
	अणु 48000, ssm2518_sysclks_3072000, पूर्ण,
	अणु 96000, ssm2518_sysclks_3072000, पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ssm2518_rates_2048000[] = अणु
	8000, 16000, 32000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list ssm2518_स्थिरraपूर्णांकs_2048000 = अणु
	.list = ssm2518_rates_2048000,
	.count = ARRAY_SIZE(ssm2518_rates_2048000),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ssm2518_rates_2822000[] = अणु
	11025, 22050, 44100,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list ssm2518_स्थिरraपूर्णांकs_2822000 = अणु
	.list = ssm2518_rates_2822000,
	.count = ARRAY_SIZE(ssm2518_rates_2822000),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ssm2518_rates_3072000[] = अणु
	12000, 24000, 48000, 96000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list ssm2518_स्थिरraपूर्णांकs_3072000 = अणु
	.list = ssm2518_rates_3072000,
	.count = ARRAY_SIZE(ssm2518_rates_3072000),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ssm2518_rates_12288000[] = अणु
	8000, 12000, 16000, 24000, 32000, 48000, 96000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list ssm2518_स्थिरraपूर्णांकs_12288000 = अणु
	.list = ssm2518_rates_12288000,
	.count = ARRAY_SIZE(ssm2518_rates_12288000),
पूर्ण;

अटल पूर्णांक ssm2518_lookup_mcs(काष्ठा ssm2518 *ssm2518,
	अचिन्हित पूर्णांक rate)
अणु
	स्थिर अचिन्हित पूर्णांक *sysclks = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ssm2518_mcs_lut); i++) अणु
		अगर (ssm2518_mcs_lut[i].rate == rate) अणु
			sysclks = ssm2518_mcs_lut[i].sysclks;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!sysclks)
		वापस -EINVAL;

	क्रम (i = 0; sysclks[i]; i++) अणु
		अगर (sysclks[i] == ssm2518->sysclk)
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ssm2518_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ssm2518 *ssm2518 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक ctrl1, ctrl1_mask;
	पूर्णांक mcs;
	पूर्णांक ret;

	mcs = ssm2518_lookup_mcs(ssm2518, rate);
	अगर (mcs < 0)
		वापस mcs;

	ctrl1_mask = SSM2518_SAI_CTRL1_FS_MASK;

	अगर (rate >= 8000 && rate <= 12000)
		ctrl1 = SSM2518_SAI_CTRL1_FS_8000_12000;
	अन्यथा अगर (rate >= 16000 && rate <= 24000)
		ctrl1 = SSM2518_SAI_CTRL1_FS_16000_24000;
	अन्यथा अगर (rate >= 32000 && rate <= 48000)
		ctrl1 = SSM2518_SAI_CTRL1_FS_32000_48000;
	अन्यथा अगर (rate >= 64000 && rate <= 96000)
		ctrl1 = SSM2518_SAI_CTRL1_FS_64000_96000;
	अन्यथा
		वापस -EINVAL;

	अगर (ssm2518->right_j) अणु
		चयन (params_width(params)) अणु
		हाल 16:
			ctrl1 |= SSM2518_SAI_CTRL1_FMT_RJ_16BIT;
			अवरोध;
		हाल 24:
			ctrl1 |= SSM2518_SAI_CTRL1_FMT_RJ_24BIT;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		ctrl1_mask |= SSM2518_SAI_CTRL1_FMT_MASK;
	पूर्ण

	/* Disable स्वतः samplerate detection */
	ret = regmap_update_bits(ssm2518->regmap, SSM2518_REG_CLOCK,
				SSM2518_CLOCK_ASR, SSM2518_CLOCK_ASR);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_update_bits(ssm2518->regmap, SSM2518_REG_SAI_CTRL1,
				ctrl1_mask, ctrl1);
	अगर (ret < 0)
		वापस ret;

	वापस regmap_update_bits(ssm2518->regmap, SSM2518_REG_POWER1,
				SSM2518_POWER1_MCS_MASK, mcs << 1);
पूर्ण

अटल पूर्णांक ssm2518_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा ssm2518 *ssm2518 = snd_soc_component_get_drvdata(dai->component);
	अचिन्हित पूर्णांक val;

	अगर (mute)
		val = SSM2518_MUTE_CTRL_MUTE_MASTER;
	अन्यथा
		val = 0;

	वापस regmap_update_bits(ssm2518->regmap, SSM2518_REG_MUTE_CTRL,
			SSM2518_MUTE_CTRL_MUTE_MASTER, val);
पूर्ण

अटल पूर्णांक ssm2518_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा ssm2518 *ssm2518 = snd_soc_component_get_drvdata(dai->component);
	अचिन्हित पूर्णांक ctrl1 = 0, ctrl2 = 0;
	bool invert_fclk;
	पूर्णांक ret;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		invert_fclk = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		ctrl2 |= SSM2518_SAI_CTRL2_BCLK_INVERT;
		invert_fclk = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		invert_fclk = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		ctrl2 |= SSM2518_SAI_CTRL2_BCLK_INVERT;
		invert_fclk = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ssm2518->right_j = false;
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		ctrl1 |= SSM2518_SAI_CTRL1_FMT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		ctrl1 |= SSM2518_SAI_CTRL1_FMT_LJ;
		invert_fclk = !invert_fclk;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		ctrl1 |= SSM2518_SAI_CTRL1_FMT_RJ_24BIT;
		ssm2518->right_j = true;
		invert_fclk = !invert_fclk;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		ctrl2 |= SSM2518_SAI_CTRL2_LRCLK_PULSE;
		ctrl1 |= SSM2518_SAI_CTRL1_FMT_I2S;
		invert_fclk = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		ctrl2 |= SSM2518_SAI_CTRL2_LRCLK_PULSE;
		ctrl1 |= SSM2518_SAI_CTRL1_FMT_LJ;
		invert_fclk = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (invert_fclk)
		ctrl2 |= SSM2518_SAI_CTRL2_LRCLK_INVERT;

	ret = regmap_ग_लिखो(ssm2518->regmap, SSM2518_REG_SAI_CTRL1, ctrl1);
	अगर (ret)
		वापस ret;

	वापस regmap_ग_लिखो(ssm2518->regmap, SSM2518_REG_SAI_CTRL2, ctrl2);
पूर्ण

अटल पूर्णांक ssm2518_set_घातer(काष्ठा ssm2518 *ssm2518, bool enable)
अणु
	पूर्णांक ret = 0;

	अगर (!enable) अणु
		ret = regmap_update_bits(ssm2518->regmap, SSM2518_REG_POWER1,
			SSM2518_POWER1_SPWDN, SSM2518_POWER1_SPWDN);
		regcache_mark_dirty(ssm2518->regmap);
	पूर्ण

	अगर (gpio_is_valid(ssm2518->enable_gpio))
		gpio_set_value(ssm2518->enable_gpio, enable);

	regcache_cache_only(ssm2518->regmap, !enable);

	अगर (enable) अणु
		ret = regmap_update_bits(ssm2518->regmap, SSM2518_REG_POWER1,
			SSM2518_POWER1_SPWDN | SSM2518_POWER1_RESET, 0x00);
		regcache_sync(ssm2518->regmap);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ssm2518_set_bias_level(काष्ठा snd_soc_component *component,
	क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा ssm2518 *ssm2518 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			ret = ssm2518_set_घातer(ssm2518, true);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		ret = ssm2518_set_घातer(ssm2518, false);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ssm2518_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
	अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक width)
अणु
	काष्ठा ssm2518 *ssm2518 = snd_soc_component_get_drvdata(dai->component);
	अचिन्हित पूर्णांक ctrl1, ctrl2;
	पूर्णांक left_slot, right_slot;
	पूर्णांक ret;

	अगर (slots == 0)
		वापस regmap_update_bits(ssm2518->regmap,
			SSM2518_REG_SAI_CTRL1, SSM2518_SAI_CTRL1_SAI_MASK,
			SSM2518_SAI_CTRL1_SAI_I2S);

	अगर (tx_mask == 0 || rx_mask != 0)
		वापस -EINVAL;

	अगर (slots == 1) अणु
		अगर (tx_mask != 1)
			वापस -EINVAL;
		left_slot = 0;
		right_slot = 0;
	पूर्ण अन्यथा अणु
		/* We assume the left channel < right channel */
		left_slot = __ffs(tx_mask);
		tx_mask &= ~(1 << left_slot);
		अगर (tx_mask == 0) अणु
			right_slot = left_slot;
		पूर्ण अन्यथा अणु
			right_slot = __ffs(tx_mask);
			tx_mask &= ~(1 << right_slot);
		पूर्ण
	पूर्ण

	अगर (tx_mask != 0 || left_slot >= slots || right_slot >= slots)
		वापस -EINVAL;

	चयन (width) अणु
	हाल 16:
		ctrl2 = SSM2518_SAI_CTRL2_SLOT_WIDTH_16;
		अवरोध;
	हाल 24:
		ctrl2 = SSM2518_SAI_CTRL2_SLOT_WIDTH_24;
		अवरोध;
	हाल 32:
		ctrl2 = SSM2518_SAI_CTRL2_SLOT_WIDTH_32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (slots) अणु
	हाल 1:
		ctrl1 = SSM2518_SAI_CTRL1_SAI_MONO;
		अवरोध;
	हाल 2:
		ctrl1 = SSM2518_SAI_CTRL1_SAI_TDM_2;
		अवरोध;
	हाल 4:
		ctrl1 = SSM2518_SAI_CTRL1_SAI_TDM_4;
		अवरोध;
	हाल 8:
		ctrl1 = SSM2518_SAI_CTRL1_SAI_TDM_8;
		अवरोध;
	हाल 16:
		ctrl1 = SSM2518_SAI_CTRL1_SAI_TDM_16;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = regmap_ग_लिखो(ssm2518->regmap, SSM2518_REG_CHAN_MAP,
		(left_slot << SSM2518_CHAN_MAP_LEFT_SLOT_OFFSET) |
		(right_slot << SSM2518_CHAN_MAP_RIGHT_SLOT_OFFSET));
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(ssm2518->regmap, SSM2518_REG_SAI_CTRL1,
		SSM2518_SAI_CTRL1_SAI_MASK, ctrl1);
	अगर (ret)
		वापस ret;

	वापस regmap_update_bits(ssm2518->regmap, SSM2518_REG_SAI_CTRL2,
		SSM2518_SAI_CTRL2_SLOT_WIDTH_MASK, ctrl2);
पूर्ण

अटल पूर्णांक ssm2518_startup(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा ssm2518 *ssm2518 = snd_soc_component_get_drvdata(dai->component);

	अगर (ssm2518->स्थिरraपूर्णांकs)
		snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				SNDRV_PCM_HW_PARAM_RATE, ssm2518->स्थिरraपूर्णांकs);

	वापस 0;
पूर्ण

#घोषणा SSM2518_FORMATS (SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_S16_LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32)

अटल स्थिर काष्ठा snd_soc_dai_ops ssm2518_dai_ops = अणु
	.startup = ssm2518_startup,
	.hw_params	= ssm2518_hw_params,
	.mute_stream	= ssm2518_mute,
	.set_fmt	= ssm2518_set_dai_fmt,
	.set_tdm_slot	= ssm2518_set_tdm_slot,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ssm2518_dai = अणु
	.name = "ssm2518-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = SSM2518_FORMATS,
	पूर्ण,
	.ops = &ssm2518_dai_ops,
पूर्ण;

अटल पूर्णांक ssm2518_set_sysclk(काष्ठा snd_soc_component *component, पूर्णांक clk_id,
	पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा ssm2518 *ssm2518 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val;

	अगर (clk_id != SSM2518_SYSCLK)
		वापस -EINVAL;

	चयन (source) अणु
	हाल SSM2518_SYSCLK_SRC_MCLK:
		val = 0;
		अवरोध;
	हाल SSM2518_SYSCLK_SRC_BCLK:
		/* In this हाल the bitघड़ी is used as the प्रणाली घड़ी, and
		 * the bitघड़ी संकेत needs to be connected to the MCLK pin and
		 * the BCLK pin is left unconnected */
		val = SSM2518_POWER1_NO_BCLK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (freq) अणु
	हाल 0:
		ssm2518->स्थिरraपूर्णांकs = शून्य;
		अवरोध;
	हाल 2048000:
	हाल 4096000:
	हाल 8192000:
	हाल 3200000:
	हाल 6400000:
	हाल 12800000:
		ssm2518->स्थिरraपूर्णांकs = &ssm2518_स्थिरraपूर्णांकs_2048000;
		अवरोध;
	हाल 2822000:
	हाल 5644800:
	हाल 11289600:
	हाल 16934400:
	हाल 22579200:
	हाल 33868800:
	हाल 4410000:
	हाल 8820000:
	हाल 17640000:
		ssm2518->स्थिरraपूर्णांकs = &ssm2518_स्थिरraपूर्णांकs_2822000;
		अवरोध;
	हाल 3072000:
	हाल 6144000:
	हाल 38864000:
	हाल 4800000:
	हाल 9600000:
	हाल 19200000:
		ssm2518->स्थिरraपूर्णांकs = &ssm2518_स्थिरraपूर्णांकs_3072000;
		अवरोध;
	हाल 12288000:
	हाल 16384000:
	हाल 24576000:
		ssm2518->स्थिरraपूर्णांकs = &ssm2518_स्थिरraपूर्णांकs_12288000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ssm2518->sysclk = freq;

	वापस regmap_update_bits(ssm2518->regmap, SSM2518_REG_POWER1,
			SSM2518_POWER1_NO_BCLK, val);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver ssm2518_component_driver = अणु
	.set_bias_level		= ssm2518_set_bias_level,
	.set_sysclk		= ssm2518_set_sysclk,
	.controls		= ssm2518_snd_controls,
	.num_controls		= ARRAY_SIZE(ssm2518_snd_controls),
	.dapm_widमाला_लो		= ssm2518_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ssm2518_dapm_widमाला_लो),
	.dapm_routes		= ssm2518_routes,
	.num_dapm_routes	= ARRAY_SIZE(ssm2518_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ssm2518_regmap_config = अणु
	.val_bits = 8,
	.reg_bits = 8,

	.max_रेजिस्टर = SSM2518_REG_DRC_9,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = ssm2518_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(ssm2518_reg_शेषs),
पूर्ण;

अटल पूर्णांक ssm2518_i2c_probe(काष्ठा i2c_client *i2c,
	स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ssm2518_platक्रमm_data *pdata = i2c->dev.platक्रमm_data;
	काष्ठा ssm2518 *ssm2518;
	पूर्णांक ret;

	ssm2518 = devm_kzalloc(&i2c->dev, माप(*ssm2518), GFP_KERNEL);
	अगर (ssm2518 == शून्य)
		वापस -ENOMEM;

	अगर (pdata) अणु
		ssm2518->enable_gpio = pdata->enable_gpio;
	पूर्ण अन्यथा अगर (i2c->dev.of_node) अणु
		ssm2518->enable_gpio = of_get_gpio(i2c->dev.of_node, 0);
		अगर (ssm2518->enable_gpio < 0 && ssm2518->enable_gpio != -ENOENT)
			वापस ssm2518->enable_gpio;
	पूर्ण अन्यथा अणु
		ssm2518->enable_gpio = -1;
	पूर्ण

	अगर (gpio_is_valid(ssm2518->enable_gpio)) अणु
		ret = devm_gpio_request_one(&i2c->dev, ssm2518->enable_gpio,
				GPIOF_OUT_INIT_HIGH, "SSM2518 nSD");
		अगर (ret)
			वापस ret;
	पूर्ण

	i2c_set_clientdata(i2c, ssm2518);

	ssm2518->regmap = devm_regmap_init_i2c(i2c, &ssm2518_regmap_config);
	अगर (IS_ERR(ssm2518->regmap))
		वापस PTR_ERR(ssm2518->regmap);

	/*
	 * The reset bit is obviously अस्थिर, but we need to be able to cache
	 * the other bits in the रेजिस्टर, so we can't just mark the whole
	 * रेजिस्टर as अस्थिर. Since this is the only place where we'll ever
	 * touch the reset bit just bypass the cache क्रम this operation.
	 */
	regcache_cache_bypass(ssm2518->regmap, true);
	ret = regmap_ग_लिखो(ssm2518->regmap, SSM2518_REG_POWER1,
			SSM2518_POWER1_RESET);
	regcache_cache_bypass(ssm2518->regmap, false);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(ssm2518->regmap, SSM2518_REG_POWER2,
				SSM2518_POWER2_APWDN, 0x00);
	अगर (ret)
		वापस ret;

	ret = ssm2518_set_घातer(ssm2518, false);
	अगर (ret)
		वापस ret;

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&ssm2518_component_driver,
			&ssm2518_dai, 1);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ssm2518_dt_ids[] = अणु
	अणु .compatible = "adi,ssm2518", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ssm2518_dt_ids);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id ssm2518_i2c_ids[] = अणु
	अणु "ssm2518", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ssm2518_i2c_ids);

अटल काष्ठा i2c_driver ssm2518_driver = अणु
	.driver = अणु
		.name = "ssm2518",
		.of_match_table = of_match_ptr(ssm2518_dt_ids),
	पूर्ण,
	.probe = ssm2518_i2c_probe,
	.id_table = ssm2518_i2c_ids,
पूर्ण;
module_i2c_driver(ssm2518_driver);

MODULE_DESCRIPTION("ASoC SSM2518 driver");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_LICENSE("GPL");
