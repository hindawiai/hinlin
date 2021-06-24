<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SSM4567 amplअगरier audio driver
 *
 * Copyright 2014 Google Chromium project.
 *  Author: Anम_से_द Pomozov <anम_से_द@chromium.org>
 *
 * Based on code copyright/by:
 *   Copyright 2013 Analog Devices Inc.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#घोषणा SSM4567_REG_POWER_CTRL		0x00
#घोषणा SSM4567_REG_AMP_SNS_CTRL		0x01
#घोषणा SSM4567_REG_DAC_CTRL		0x02
#घोषणा SSM4567_REG_DAC_VOLUME		0x03
#घोषणा SSM4567_REG_SAI_CTRL_1		0x04
#घोषणा SSM4567_REG_SAI_CTRL_2		0x05
#घोषणा SSM4567_REG_SAI_PLACEMENT_1		0x06
#घोषणा SSM4567_REG_SAI_PLACEMENT_2		0x07
#घोषणा SSM4567_REG_SAI_PLACEMENT_3		0x08
#घोषणा SSM4567_REG_SAI_PLACEMENT_4		0x09
#घोषणा SSM4567_REG_SAI_PLACEMENT_5		0x0a
#घोषणा SSM4567_REG_SAI_PLACEMENT_6		0x0b
#घोषणा SSM4567_REG_BATTERY_V_OUT		0x0c
#घोषणा SSM4567_REG_LIMITER_CTRL_1		0x0d
#घोषणा SSM4567_REG_LIMITER_CTRL_2		0x0e
#घोषणा SSM4567_REG_LIMITER_CTRL_3		0x0f
#घोषणा SSM4567_REG_STATUS_1		0x10
#घोषणा SSM4567_REG_STATUS_2		0x11
#घोषणा SSM4567_REG_FAULT_CTRL		0x12
#घोषणा SSM4567_REG_PDM_CTRL		0x13
#घोषणा SSM4567_REG_MCLK_RATIO		0x14
#घोषणा SSM4567_REG_BOOST_CTRL_1		0x15
#घोषणा SSM4567_REG_BOOST_CTRL_2		0x16
#घोषणा SSM4567_REG_SOFT_RESET		0xff

/* POWER_CTRL */
#घोषणा SSM4567_POWER_APWDN_EN		BIT(7)
#घोषणा SSM4567_POWER_BSNS_PWDN		BIT(6)
#घोषणा SSM4567_POWER_VSNS_PWDN		BIT(5)
#घोषणा SSM4567_POWER_ISNS_PWDN		BIT(4)
#घोषणा SSM4567_POWER_BOOST_PWDN		BIT(3)
#घोषणा SSM4567_POWER_AMP_PWDN		BIT(2)
#घोषणा SSM4567_POWER_VBAT_ONLY		BIT(1)
#घोषणा SSM4567_POWER_SPWDN			BIT(0)

/* DAC_CTRL */
#घोषणा SSM4567_DAC_HV			BIT(7)
#घोषणा SSM4567_DAC_MUTE		BIT(6)
#घोषणा SSM4567_DAC_HPF			BIT(5)
#घोषणा SSM4567_DAC_LPM			BIT(4)
#घोषणा SSM4567_DAC_FS_MASK	0x7
#घोषणा SSM4567_DAC_FS_8000_12000	0x0
#घोषणा SSM4567_DAC_FS_16000_24000	0x1
#घोषणा SSM4567_DAC_FS_32000_48000	0x2
#घोषणा SSM4567_DAC_FS_64000_96000	0x3
#घोषणा SSM4567_DAC_FS_128000_192000	0x4

/* SAI_CTRL_1 */
#घोषणा SSM4567_SAI_CTRL_1_BCLK			BIT(6)
#घोषणा SSM4567_SAI_CTRL_1_TDM_BLCKS_MASK	(0x3 << 4)
#घोषणा SSM4567_SAI_CTRL_1_TDM_BLCKS_32		(0x0 << 4)
#घोषणा SSM4567_SAI_CTRL_1_TDM_BLCKS_48		(0x1 << 4)
#घोषणा SSM4567_SAI_CTRL_1_TDM_BLCKS_64		(0x2 << 4)
#घोषणा SSM4567_SAI_CTRL_1_FSYNC		BIT(3)
#घोषणा SSM4567_SAI_CTRL_1_LJ			BIT(2)
#घोषणा SSM4567_SAI_CTRL_1_TDM			BIT(1)
#घोषणा SSM4567_SAI_CTRL_1_PDM			BIT(0)

/* SAI_CTRL_2 */
#घोषणा SSM4567_SAI_CTRL_2_AUTO_SLOT		BIT(3)
#घोषणा SSM4567_SAI_CTRL_2_TDM_SLOT_MASK	0x7
#घोषणा SSM4567_SAI_CTRL_2_TDM_SLOT(x)		(x)

काष्ठा ssm4567 अणु
	काष्ठा regmap *regmap;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष ssm4567_reg_शेषs[] = अणु
	अणु SSM4567_REG_POWER_CTRL,	0x81 पूर्ण,
	अणु SSM4567_REG_AMP_SNS_CTRL, 0x09 पूर्ण,
	अणु SSM4567_REG_DAC_CTRL, 0x32 पूर्ण,
	अणु SSM4567_REG_DAC_VOLUME, 0x40 पूर्ण,
	अणु SSM4567_REG_SAI_CTRL_1, 0x00 पूर्ण,
	अणु SSM4567_REG_SAI_CTRL_2, 0x08 पूर्ण,
	अणु SSM4567_REG_SAI_PLACEMENT_1, 0x01 पूर्ण,
	अणु SSM4567_REG_SAI_PLACEMENT_2, 0x20 पूर्ण,
	अणु SSM4567_REG_SAI_PLACEMENT_3, 0x32 पूर्ण,
	अणु SSM4567_REG_SAI_PLACEMENT_4, 0x07 पूर्ण,
	अणु SSM4567_REG_SAI_PLACEMENT_5, 0x07 पूर्ण,
	अणु SSM4567_REG_SAI_PLACEMENT_6, 0x07 पूर्ण,
	अणु SSM4567_REG_BATTERY_V_OUT, 0x00 पूर्ण,
	अणु SSM4567_REG_LIMITER_CTRL_1, 0xa4 पूर्ण,
	अणु SSM4567_REG_LIMITER_CTRL_2, 0x73 पूर्ण,
	अणु SSM4567_REG_LIMITER_CTRL_3, 0x00 पूर्ण,
	अणु SSM4567_REG_STATUS_1, 0x00 पूर्ण,
	अणु SSM4567_REG_STATUS_2, 0x00 पूर्ण,
	अणु SSM4567_REG_FAULT_CTRL, 0x30 पूर्ण,
	अणु SSM4567_REG_PDM_CTRL, 0x40 पूर्ण,
	अणु SSM4567_REG_MCLK_RATIO, 0x11 पूर्ण,
	अणु SSM4567_REG_BOOST_CTRL_1, 0x03 पूर्ण,
	अणु SSM4567_REG_BOOST_CTRL_2, 0x00 पूर्ण,
	अणु SSM4567_REG_SOFT_RESET, 0x00 पूर्ण,
पूर्ण;


अटल bool ssm4567_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SSM4567_REG_POWER_CTRL ... SSM4567_REG_BOOST_CTRL_2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण

पूर्ण

अटल bool ssm4567_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SSM4567_REG_POWER_CTRL ... SSM4567_REG_SAI_PLACEMENT_6:
	हाल SSM4567_REG_LIMITER_CTRL_1 ... SSM4567_REG_LIMITER_CTRL_3:
	हाल SSM4567_REG_FAULT_CTRL ... SSM4567_REG_BOOST_CTRL_2:
	/* The datasheet states that soft reset रेजिस्टर is पढ़ो-only,
	 * but logically it is ग_लिखो-only. */
	हाल SSM4567_REG_SOFT_RESET:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool ssm4567_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SSM4567_REG_BATTERY_V_OUT:
	हाल SSM4567_REG_STATUS_1 ... SSM4567_REG_STATUS_2:
	हाल SSM4567_REG_SOFT_RESET:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर DECLARE_TLV_DB_MINMAX_MUTE(ssm4567_vol_tlv, -7125, 2400);

अटल स्थिर काष्ठा snd_kcontrol_new ssm4567_snd_controls[] = अणु
	SOC_SINGLE_TLV("Master Playback Volume", SSM4567_REG_DAC_VOLUME, 0,
		0xff, 1, ssm4567_vol_tlv),
	SOC_SINGLE("DAC Low Power Mode Switch", SSM4567_REG_DAC_CTRL, 4, 1, 0),
	SOC_SINGLE("DAC High Pass Filter Switch", SSM4567_REG_DAC_CTRL,
		5, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ssm4567_amplअगरier_boost_control =
	SOC_DAPM_SINGLE("Switch", SSM4567_REG_POWER_CTRL, 1, 1, 1);

अटल स्थिर काष्ठा snd_soc_dapm_widget ssm4567_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("DAC", "HiFi Playback", SSM4567_REG_POWER_CTRL, 2, 1),
	SND_SOC_DAPM_SWITCH("Amplifier Boost", SSM4567_REG_POWER_CTRL, 3, 1,
		&ssm4567_amplअगरier_boost_control),

	SND_SOC_DAPM_SIGGEN("Sense"),

	SND_SOC_DAPM_PGA("Current Sense", SSM4567_REG_POWER_CTRL, 4, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("Voltage Sense", SSM4567_REG_POWER_CTRL, 5, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("VBAT Sense", SSM4567_REG_POWER_CTRL, 6, 1, शून्य, 0),

	SND_SOC_DAPM_OUTPUT("OUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ssm4567_routes[] = अणु
	अणु "OUT", शून्य, "Amplifier Boost" पूर्ण,
	अणु "Amplifier Boost", "Switch", "DAC" पूर्ण,
	अणु "OUT", शून्य, "DAC" पूर्ण,

	अणु "Current Sense", शून्य, "Sense" पूर्ण,
	अणु "Voltage Sense", शून्य, "Sense" पूर्ण,
	अणु "VBAT Sense", शून्य, "Sense" पूर्ण,
	अणु "Capture Sense", शून्य, "Current Sense" पूर्ण,
	अणु "Capture Sense", शून्य, "Voltage Sense" पूर्ण,
	अणु "Capture Sense", शून्य, "VBAT Sense" पूर्ण,
पूर्ण;

अटल पूर्णांक ssm4567_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ssm4567 *ssm4567 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक dacfs;

	अगर (rate >= 8000 && rate <= 12000)
		dacfs = SSM4567_DAC_FS_8000_12000;
	अन्यथा अगर (rate >= 16000 && rate <= 24000)
		dacfs = SSM4567_DAC_FS_16000_24000;
	अन्यथा अगर (rate >= 32000 && rate <= 48000)
		dacfs = SSM4567_DAC_FS_32000_48000;
	अन्यथा अगर (rate >= 64000 && rate <= 96000)
		dacfs = SSM4567_DAC_FS_64000_96000;
	अन्यथा अगर (rate >= 128000 && rate <= 192000)
		dacfs = SSM4567_DAC_FS_128000_192000;
	अन्यथा
		वापस -EINVAL;

	वापस regmap_update_bits(ssm4567->regmap, SSM4567_REG_DAC_CTRL,
				SSM4567_DAC_FS_MASK, dacfs);
पूर्ण

अटल पूर्णांक ssm4567_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा ssm4567 *ssm4567 = snd_soc_component_get_drvdata(dai->component);
	अचिन्हित पूर्णांक val;

	val = mute ? SSM4567_DAC_MUTE : 0;
	वापस regmap_update_bits(ssm4567->regmap, SSM4567_REG_DAC_CTRL,
			SSM4567_DAC_MUTE, val);
पूर्ण

अटल पूर्णांक ssm4567_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
	अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक width)
अणु
	काष्ठा ssm4567 *ssm4567 = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक blcks;
	पूर्णांक slot;
	पूर्णांक ret;

	अगर (tx_mask == 0)
		वापस -EINVAL;

	अगर (rx_mask && rx_mask != tx_mask)
		वापस -EINVAL;

	slot = __ffs(tx_mask);
	अगर (tx_mask != BIT(slot))
		वापस -EINVAL;

	चयन (width) अणु
	हाल 32:
		blcks = SSM4567_SAI_CTRL_1_TDM_BLCKS_32;
		अवरोध;
	हाल 48:
		blcks = SSM4567_SAI_CTRL_1_TDM_BLCKS_48;
		अवरोध;
	हाल 64:
		blcks = SSM4567_SAI_CTRL_1_TDM_BLCKS_64;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(ssm4567->regmap, SSM4567_REG_SAI_CTRL_2,
		SSM4567_SAI_CTRL_2_AUTO_SLOT | SSM4567_SAI_CTRL_2_TDM_SLOT_MASK,
		SSM4567_SAI_CTRL_2_TDM_SLOT(slot));
	अगर (ret)
		वापस ret;

	वापस regmap_update_bits(ssm4567->regmap, SSM4567_REG_SAI_CTRL_1,
		SSM4567_SAI_CTRL_1_TDM_BLCKS_MASK, blcks);
पूर्ण

अटल पूर्णांक ssm4567_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा ssm4567 *ssm4567 = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक ctrl1 = 0;
	bool invert_fclk;

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
		ctrl1 |= SSM4567_SAI_CTRL_1_BCLK;
		invert_fclk = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		ctrl1 |= SSM4567_SAI_CTRL_1_FSYNC;
		invert_fclk = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		ctrl1 |= SSM4567_SAI_CTRL_1_BCLK;
		invert_fclk = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		ctrl1 |= SSM4567_SAI_CTRL_1_LJ;
		invert_fclk = !invert_fclk;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		ctrl1 |= SSM4567_SAI_CTRL_1_TDM;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		ctrl1 |= SSM4567_SAI_CTRL_1_TDM | SSM4567_SAI_CTRL_1_LJ;
		अवरोध;
	हाल SND_SOC_DAIFMT_PDM:
		ctrl1 |= SSM4567_SAI_CTRL_1_PDM;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (invert_fclk)
		ctrl1 |= SSM4567_SAI_CTRL_1_FSYNC;

	वापस regmap_update_bits(ssm4567->regmap, SSM4567_REG_SAI_CTRL_1,
			SSM4567_SAI_CTRL_1_BCLK |
			SSM4567_SAI_CTRL_1_FSYNC |
			SSM4567_SAI_CTRL_1_LJ |
			SSM4567_SAI_CTRL_1_TDM |
			SSM4567_SAI_CTRL_1_PDM,
			ctrl1);
पूर्ण

अटल पूर्णांक ssm4567_set_घातer(काष्ठा ssm4567 *ssm4567, bool enable)
अणु
	पूर्णांक ret = 0;

	अगर (!enable) अणु
		ret = regmap_update_bits(ssm4567->regmap,
			SSM4567_REG_POWER_CTRL,
			SSM4567_POWER_SPWDN, SSM4567_POWER_SPWDN);
		regcache_mark_dirty(ssm4567->regmap);
	पूर्ण

	regcache_cache_only(ssm4567->regmap, !enable);

	अगर (enable) अणु
		ret = regmap_ग_लिखो(ssm4567->regmap, SSM4567_REG_SOFT_RESET,
			0x00);
		अगर (ret)
			वापस ret;

		ret = regmap_update_bits(ssm4567->regmap,
			SSM4567_REG_POWER_CTRL,
			SSM4567_POWER_SPWDN, 0x00);
		regcache_sync(ssm4567->regmap);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ssm4567_set_bias_level(काष्ठा snd_soc_component *component,
	क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा ssm4567 *ssm4567 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			ret = ssm4567_set_घातer(ssm4567, true);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		ret = ssm4567_set_घातer(ssm4567, false);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops ssm4567_dai_ops = अणु
	.hw_params	= ssm4567_hw_params,
	.mute_stream	= ssm4567_mute,
	.set_fmt	= ssm4567_set_dai_fmt,
	.set_tdm_slot	= ssm4567_set_tdm_slot,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ssm4567_dai = अणु
	.name = "ssm4567-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 1,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE |
			SNDRV_PCM_FMTBIT_S32,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture Sense",
		.channels_min = 1,
		.channels_max = 1,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE |
			SNDRV_PCM_FMTBIT_S32,
	पूर्ण,
	.ops = &ssm4567_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver ssm4567_component_driver = अणु
	.set_bias_level		= ssm4567_set_bias_level,
	.controls		= ssm4567_snd_controls,
	.num_controls		= ARRAY_SIZE(ssm4567_snd_controls),
	.dapm_widमाला_लो		= ssm4567_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ssm4567_dapm_widमाला_लो),
	.dapm_routes		= ssm4567_routes,
	.num_dapm_routes	= ARRAY_SIZE(ssm4567_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ssm4567_regmap_config = अणु
	.val_bits = 8,
	.reg_bits = 8,

	.max_रेजिस्टर = SSM4567_REG_SOFT_RESET,
	.पढ़ोable_reg = ssm4567_पढ़ोable_reg,
	.ग_लिखोable_reg = ssm4567_ग_लिखोable_reg,
	.अस्थिर_reg = ssm4567_अस्थिर_reg,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = ssm4567_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(ssm4567_reg_शेषs),
पूर्ण;

अटल पूर्णांक ssm4567_i2c_probe(काष्ठा i2c_client *i2c,
	स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ssm4567 *ssm4567;
	पूर्णांक ret;

	ssm4567 = devm_kzalloc(&i2c->dev, माप(*ssm4567), GFP_KERNEL);
	अगर (ssm4567 == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, ssm4567);

	ssm4567->regmap = devm_regmap_init_i2c(i2c, &ssm4567_regmap_config);
	अगर (IS_ERR(ssm4567->regmap))
		वापस PTR_ERR(ssm4567->regmap);

	ret = regmap_ग_लिखो(ssm4567->regmap, SSM4567_REG_SOFT_RESET, 0x00);
	अगर (ret)
		वापस ret;

	ret = ssm4567_set_घातer(ssm4567, false);
	अगर (ret)
		वापस ret;

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev, &ssm4567_component_driver,
			&ssm4567_dai, 1);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ssm4567_i2c_ids[] = अणु
	अणु "ssm4567", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ssm4567_i2c_ids);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ssm4567_of_match[] = अणु
	अणु .compatible = "adi,ssm4567", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ssm4567_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI

अटल स्थिर काष्ठा acpi_device_id ssm4567_acpi_match[] = अणु
	अणु "INT343B", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ssm4567_acpi_match);

#पूर्ण_अगर

अटल काष्ठा i2c_driver ssm4567_driver = अणु
	.driver = अणु
		.name = "ssm4567",
		.of_match_table = of_match_ptr(ssm4567_of_match),
		.acpi_match_table = ACPI_PTR(ssm4567_acpi_match),
	पूर्ण,
	.probe = ssm4567_i2c_probe,
	.id_table = ssm4567_i2c_ids,
पूर्ण;
module_i2c_driver(ssm4567_driver);

MODULE_DESCRIPTION("ASoC SSM4567 driver");
MODULE_AUTHOR("Anatol Pomozov <anatol@chromium.org>");
MODULE_LICENSE("GPL");
