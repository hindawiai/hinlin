<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ADAU1977/ADAU1978/ADAU1979 driver
 *
 * Copyright 2014 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#समावेश <dt-bindings/sound/adi,adau1977.h>

#समावेश "adau1977.h"

#घोषणा ADAU1977_REG_POWER		0x00
#घोषणा ADAU1977_REG_PLL		0x01
#घोषणा ADAU1977_REG_BOOST		0x02
#घोषणा ADAU1977_REG_MICBIAS		0x03
#घोषणा ADAU1977_REG_BLOCK_POWER_SAI	0x04
#घोषणा ADAU1977_REG_SAI_CTRL0		0x05
#घोषणा ADAU1977_REG_SAI_CTRL1		0x06
#घोषणा ADAU1977_REG_CMAP12		0x07
#घोषणा ADAU1977_REG_CMAP34		0x08
#घोषणा ADAU1977_REG_SAI_OVERTEMP	0x09
#घोषणा ADAU1977_REG_POST_ADC_GAIN(x)	(0x0a + (x))
#घोषणा ADAU1977_REG_MISC_CONTROL	0x0e
#घोषणा ADAU1977_REG_DIAG_CONTROL	0x10
#घोषणा ADAU1977_REG_STATUS(x)		(0x11 + (x))
#घोषणा ADAU1977_REG_DIAG_IRQ1		0x15
#घोषणा ADAU1977_REG_DIAG_IRQ2		0x16
#घोषणा ADAU1977_REG_ADJUST1		0x17
#घोषणा ADAU1977_REG_ADJUST2		0x18
#घोषणा ADAU1977_REG_ADC_CLIP		0x19
#घोषणा ADAU1977_REG_DC_HPF_CAL		0x1a

#घोषणा ADAU1977_POWER_RESET			BIT(7)
#घोषणा ADAU1977_POWER_PWUP			BIT(0)

#घोषणा ADAU1977_PLL_CLK_S			BIT(4)
#घोषणा ADAU1977_PLL_MCS_MASK			0x7

#घोषणा ADAU1977_MICBIAS_MB_VOLTS_MASK		0xf0
#घोषणा ADAU1977_MICBIAS_MB_VOLTS_OFFSET	4

#घोषणा ADAU1977_BLOCK_POWER_SAI_LR_POL		BIT(7)
#घोषणा ADAU1977_BLOCK_POWER_SAI_BCLK_EDGE	BIT(6)
#घोषणा ADAU1977_BLOCK_POWER_SAI_LDO_EN		BIT(5)

#घोषणा ADAU1977_SAI_CTRL0_FMT_MASK		(0x3 << 6)
#घोषणा ADAU1977_SAI_CTRL0_FMT_I2S		(0x0 << 6)
#घोषणा ADAU1977_SAI_CTRL0_FMT_LJ		(0x1 << 6)
#घोषणा ADAU1977_SAI_CTRL0_FMT_RJ_24BIT		(0x2 << 6)
#घोषणा ADAU1977_SAI_CTRL0_FMT_RJ_16BIT		(0x3 << 6)

#घोषणा ADAU1977_SAI_CTRL0_SAI_MASK		(0x7 << 3)
#घोषणा ADAU1977_SAI_CTRL0_SAI_I2S		(0x0 << 3)
#घोषणा ADAU1977_SAI_CTRL0_SAI_TDM_2		(0x1 << 3)
#घोषणा ADAU1977_SAI_CTRL0_SAI_TDM_4		(0x2 << 3)
#घोषणा ADAU1977_SAI_CTRL0_SAI_TDM_8		(0x3 << 3)
#घोषणा ADAU1977_SAI_CTRL0_SAI_TDM_16		(0x4 << 3)

#घोषणा ADAU1977_SAI_CTRL0_FS_MASK		(0x7)
#घोषणा ADAU1977_SAI_CTRL0_FS_8000_12000	(0x0)
#घोषणा ADAU1977_SAI_CTRL0_FS_16000_24000	(0x1)
#घोषणा ADAU1977_SAI_CTRL0_FS_32000_48000	(0x2)
#घोषणा ADAU1977_SAI_CTRL0_FS_64000_96000	(0x3)
#घोषणा ADAU1977_SAI_CTRL0_FS_128000_192000	(0x4)

#घोषणा ADAU1977_SAI_CTRL1_SLOT_WIDTH_MASK	(0x3 << 5)
#घोषणा ADAU1977_SAI_CTRL1_SLOT_WIDTH_32	(0x0 << 5)
#घोषणा ADAU1977_SAI_CTRL1_SLOT_WIDTH_24	(0x1 << 5)
#घोषणा ADAU1977_SAI_CTRL1_SLOT_WIDTH_16	(0x2 << 5)
#घोषणा ADAU1977_SAI_CTRL1_DATA_WIDTH_MASK	(0x1 << 4)
#घोषणा ADAU1977_SAI_CTRL1_DATA_WIDTH_16BIT	(0x1 << 4)
#घोषणा ADAU1977_SAI_CTRL1_DATA_WIDTH_24BIT	(0x0 << 4)
#घोषणा ADAU1977_SAI_CTRL1_LRCLK_PULSE		BIT(3)
#घोषणा ADAU1977_SAI_CTRL1_MSB			BIT(2)
#घोषणा ADAU1977_SAI_CTRL1_BCLKRATE_16		(0x1 << 1)
#घोषणा ADAU1977_SAI_CTRL1_BCLKRATE_32		(0x0 << 1)
#घोषणा ADAU1977_SAI_CTRL1_BCLKRATE_MASK	(0x1 << 1)
#घोषणा ADAU1977_SAI_CTRL1_MASTER		BIT(0)

#घोषणा ADAU1977_SAI_OVERTEMP_DRV_C(x)		BIT(4 + (x))
#घोषणा ADAU1977_SAI_OVERTEMP_DRV_HIZ		BIT(3)

#घोषणा ADAU1977_MISC_CONTROL_SUM_MODE_MASK	(0x3 << 6)
#घोषणा ADAU1977_MISC_CONTROL_SUM_MODE_1CH	(0x2 << 6)
#घोषणा ADAU1977_MISC_CONTROL_SUM_MODE_2CH	(0x1 << 6)
#घोषणा ADAU1977_MISC_CONTROL_SUM_MODE_4CH	(0x0 << 6)
#घोषणा ADAU1977_MISC_CONTROL_MMUTE		BIT(4)
#घोषणा ADAU1977_MISC_CONTROL_DC_CAL		BIT(0)

#घोषणा ADAU1977_CHAN_MAP_SECOND_SLOT_OFFSET	4
#घोषणा ADAU1977_CHAN_MAP_FIRST_SLOT_OFFSET	0

काष्ठा adau1977 अणु
	काष्ठा regmap *regmap;
	bool right_j;
	अचिन्हित पूर्णांक sysclk;
	क्रमागत adau1977_sysclk_src sysclk_src;
	काष्ठा gpio_desc *reset_gpio;
	क्रमागत adau1977_type type;

	काष्ठा regulator *avdd_reg;
	काष्ठा regulator *dvdd_reg;

	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs;

	काष्ठा device *dev;
	व्योम (*चयन_mode)(काष्ठा device *dev);

	अचिन्हित पूर्णांक max_master_fs;
	अचिन्हित पूर्णांक slot_width;
	bool enabled;
	bool master;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष adau1977_reg_शेषs[] = अणु
	अणु 0x00, 0x00 पूर्ण,
	अणु 0x01, 0x41 पूर्ण,
	अणु 0x02, 0x4a पूर्ण,
	अणु 0x03, 0x7d पूर्ण,
	अणु 0x04, 0x3d पूर्ण,
	अणु 0x05, 0x02 पूर्ण,
	अणु 0x06, 0x00 पूर्ण,
	अणु 0x07, 0x10 पूर्ण,
	अणु 0x08, 0x32 पूर्ण,
	अणु 0x09, 0xf0 पूर्ण,
	अणु 0x0a, 0xa0 पूर्ण,
	अणु 0x0b, 0xa0 पूर्ण,
	अणु 0x0c, 0xa0 पूर्ण,
	अणु 0x0d, 0xa0 पूर्ण,
	अणु 0x0e, 0x02 पूर्ण,
	अणु 0x10, 0x0f पूर्ण,
	अणु 0x15, 0x20 पूर्ण,
	अणु 0x16, 0x00 पूर्ण,
	अणु 0x17, 0x00 पूर्ण,
	अणु 0x18, 0x00 पूर्ण,
	अणु 0x1a, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_MINMAX_MUTE(adau1977_adc_gain, -3562, 6000);

अटल स्थिर काष्ठा snd_soc_dapm_widget adau1977_micbias_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("MICBIAS", ADAU1977_REG_MICBIAS,
		3, 0, शून्य, 0)
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget adau1977_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("Vref", ADAU1977_REG_BLOCK_POWER_SAI,
		4, 0, शून्य, 0),

	SND_SOC_DAPM_ADC("ADC1", "Capture", ADAU1977_REG_BLOCK_POWER_SAI, 0, 0),
	SND_SOC_DAPM_ADC("ADC2", "Capture", ADAU1977_REG_BLOCK_POWER_SAI, 1, 0),
	SND_SOC_DAPM_ADC("ADC3", "Capture", ADAU1977_REG_BLOCK_POWER_SAI, 2, 0),
	SND_SOC_DAPM_ADC("ADC4", "Capture", ADAU1977_REG_BLOCK_POWER_SAI, 3, 0),

	SND_SOC_DAPM_INPUT("AIN1"),
	SND_SOC_DAPM_INPUT("AIN2"),
	SND_SOC_DAPM_INPUT("AIN3"),
	SND_SOC_DAPM_INPUT("AIN4"),

	SND_SOC_DAPM_OUTPUT("VREF"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route adau1977_dapm_routes[] = अणु
	अणु "ADC1", शून्य, "AIN1" पूर्ण,
	अणु "ADC2", शून्य, "AIN2" पूर्ण,
	अणु "ADC3", शून्य, "AIN3" पूर्ण,
	अणु "ADC4", शून्य, "AIN4" पूर्ण,

	अणु "ADC1", शून्य, "Vref" पूर्ण,
	अणु "ADC2", शून्य, "Vref" पूर्ण,
	अणु "ADC3", शून्य, "Vref" पूर्ण,
	अणु "ADC4", शून्य, "Vref" पूर्ण,

	अणु "VREF", शून्य, "Vref" पूर्ण,
पूर्ण;

#घोषणा ADAU1977_VOLUME(x) \
	SOC_SINGLE_TLV("ADC" #x " Capture Volume", \
		ADAU1977_REG_POST_ADC_GAIN((x) - 1), \
		0, 255, 1, adau1977_adc_gain)

#घोषणा ADAU1977_HPF_SWITCH(x) \
	SOC_SINGLE("ADC" #x " Highpass-Filter Capture Switch", \
		ADAU1977_REG_DC_HPF_CAL, (x) - 1, 1, 0)

#घोषणा ADAU1977_DC_SUB_SWITCH(x) \
	SOC_SINGLE("ADC" #x " DC Subtraction Capture Switch", \
		ADAU1977_REG_DC_HPF_CAL, (x) + 3, 1, 0)

अटल स्थिर काष्ठा snd_kcontrol_new adau1977_snd_controls[] = अणु
	ADAU1977_VOLUME(1),
	ADAU1977_VOLUME(2),
	ADAU1977_VOLUME(3),
	ADAU1977_VOLUME(4),

	ADAU1977_HPF_SWITCH(1),
	ADAU1977_HPF_SWITCH(2),
	ADAU1977_HPF_SWITCH(3),
	ADAU1977_HPF_SWITCH(4),

	ADAU1977_DC_SUB_SWITCH(1),
	ADAU1977_DC_SUB_SWITCH(2),
	ADAU1977_DC_SUB_SWITCH(3),
	ADAU1977_DC_SUB_SWITCH(4),
पूर्ण;

अटल पूर्णांक adau1977_reset(काष्ठा adau1977 *adau1977)
अणु
	पूर्णांक ret;

	/*
	 * The reset bit is obviously अस्थिर, but we need to be able to cache
	 * the other bits in the रेजिस्टर, so we can't just mark the whole
	 * रेजिस्टर as अस्थिर. Since this is the only place where we'll ever
	 * touch the reset bit just bypass the cache क्रम this operation.
	 */
	regcache_cache_bypass(adau1977->regmap, true);
	ret = regmap_ग_लिखो(adau1977->regmap, ADAU1977_REG_POWER,
			ADAU1977_POWER_RESET);
	regcache_cache_bypass(adau1977->regmap, false);

	वापस ret;
पूर्ण

/*
 * Returns the appropriate setting क्रम ths FS field in the CTRL0 रेजिस्टर
 * depending on the rate.
 */
अटल पूर्णांक adau1977_lookup_fs(अचिन्हित पूर्णांक rate)
अणु
	अगर (rate >= 8000 && rate <= 12000)
		वापस ADAU1977_SAI_CTRL0_FS_8000_12000;
	अन्यथा अगर (rate >= 16000 && rate <= 24000)
		वापस ADAU1977_SAI_CTRL0_FS_16000_24000;
	अन्यथा अगर (rate >= 32000 && rate <= 48000)
		वापस ADAU1977_SAI_CTRL0_FS_32000_48000;
	अन्यथा अगर (rate >= 64000 && rate <= 96000)
		वापस ADAU1977_SAI_CTRL0_FS_64000_96000;
	अन्यथा अगर (rate >= 128000 && rate <= 192000)
		वापस ADAU1977_SAI_CTRL0_FS_128000_192000;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक adau1977_lookup_mcs(काष्ठा adau1977 *adau1977, अचिन्हित पूर्णांक rate,
	अचिन्हित पूर्णांक fs)
अणु
	अचिन्हित पूर्णांक mcs;

	/*
	 * rate = sysclk / (512 * mcs_lut[mcs]) * 2**fs
	 * => mcs_lut[mcs] = sysclk / (512 * rate) * 2**fs
	 * => mcs_lut[mcs] = sysclk / ((512 / 2**fs) * rate)
	 */

	rate *= 512 >> fs;

	अगर (adau1977->sysclk % rate != 0)
		वापस -EINVAL;

	mcs = adau1977->sysclk / rate;

	/* The factors configured by MCS are 1, 2, 3, 4, 6 */
	अगर (mcs < 1 || mcs > 6 || mcs == 5)
		वापस -EINVAL;

	mcs = mcs - 1;
	अगर (mcs == 5)
		mcs = 4;

	वापस mcs;
पूर्ण

अटल पूर्णांक adau1977_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा adau1977 *adau1977 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक slot_width;
	अचिन्हित पूर्णांक ctrl0, ctrl0_mask;
	अचिन्हित पूर्णांक ctrl1;
	पूर्णांक mcs, fs;
	पूर्णांक ret;

	fs = adau1977_lookup_fs(rate);
	अगर (fs < 0)
		वापस fs;

	अगर (adau1977->sysclk_src == ADAU1977_SYSCLK_SRC_MCLK) अणु
		mcs = adau1977_lookup_mcs(adau1977, rate, fs);
		अगर (mcs < 0)
			वापस mcs;
	पूर्ण अन्यथा अणु
		mcs = 0;
	पूर्ण

	ctrl0_mask = ADAU1977_SAI_CTRL0_FS_MASK;
	ctrl0 = fs;

	अगर (adau1977->right_j) अणु
		चयन (params_width(params)) अणु
		हाल 16:
			ctrl0 |= ADAU1977_SAI_CTRL0_FMT_RJ_16BIT;
			अवरोध;
		हाल 24:
			ctrl0 |= ADAU1977_SAI_CTRL0_FMT_RJ_24BIT;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		ctrl0_mask |= ADAU1977_SAI_CTRL0_FMT_MASK;
	पूर्ण

	अगर (adau1977->master) अणु
		चयन (params_width(params)) अणु
		हाल 16:
			ctrl1 = ADAU1977_SAI_CTRL1_DATA_WIDTH_16BIT;
			slot_width = 16;
			अवरोध;
		हाल 24:
		हाल 32:
			ctrl1 = ADAU1977_SAI_CTRL1_DATA_WIDTH_24BIT;
			slot_width = 32;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		/* In TDM mode there is a fixed slot width */
		अगर (adau1977->slot_width)
			slot_width = adau1977->slot_width;

		अगर (slot_width == 16)
			ctrl1 |= ADAU1977_SAI_CTRL1_BCLKRATE_16;
		अन्यथा
			ctrl1 |= ADAU1977_SAI_CTRL1_BCLKRATE_32;

		ret = regmap_update_bits(adau1977->regmap,
			ADAU1977_REG_SAI_CTRL1,
			ADAU1977_SAI_CTRL1_DATA_WIDTH_MASK |
			ADAU1977_SAI_CTRL1_BCLKRATE_MASK,
			ctrl1);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = regmap_update_bits(adau1977->regmap, ADAU1977_REG_SAI_CTRL0,
				ctrl0_mask, ctrl0);
	अगर (ret < 0)
		वापस ret;

	वापस regmap_update_bits(adau1977->regmap, ADAU1977_REG_PLL,
				ADAU1977_PLL_MCS_MASK, mcs);
पूर्ण

अटल पूर्णांक adau1977_घातer_disable(काष्ठा adau1977 *adau1977)
अणु
	पूर्णांक ret = 0;

	अगर (!adau1977->enabled)
		वापस 0;

	ret = regmap_update_bits(adau1977->regmap, ADAU1977_REG_POWER,
		ADAU1977_POWER_PWUP, 0);
	अगर (ret)
		वापस ret;

	regcache_mark_dirty(adau1977->regmap);

	gpiod_set_value_cansleep(adau1977->reset_gpio, 0);

	regcache_cache_only(adau1977->regmap, true);

	regulator_disable(adau1977->avdd_reg);
	अगर (adau1977->dvdd_reg)
		regulator_disable(adau1977->dvdd_reg);

	adau1977->enabled = false;

	वापस 0;
पूर्ण

अटल पूर्णांक adau1977_घातer_enable(काष्ठा adau1977 *adau1977)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret = 0;

	अगर (adau1977->enabled)
		वापस 0;

	ret = regulator_enable(adau1977->avdd_reg);
	अगर (ret)
		वापस ret;

	अगर (adau1977->dvdd_reg) अणु
		ret = regulator_enable(adau1977->dvdd_reg);
		अगर (ret)
			जाओ err_disable_avdd;
	पूर्ण

	gpiod_set_value_cansleep(adau1977->reset_gpio, 1);

	regcache_cache_only(adau1977->regmap, false);

	अगर (adau1977->चयन_mode)
		adau1977->चयन_mode(adau1977->dev);

	ret = adau1977_reset(adau1977);
	अगर (ret)
		जाओ err_disable_dvdd;

	ret = regmap_update_bits(adau1977->regmap, ADAU1977_REG_POWER,
		ADAU1977_POWER_PWUP, ADAU1977_POWER_PWUP);
	अगर (ret)
		जाओ err_disable_dvdd;

	ret = regcache_sync(adau1977->regmap);
	अगर (ret)
		जाओ err_disable_dvdd;

	/*
	 * The PLL रेजिस्टर is not affected by the software reset. It is
	 * possible that the value of the रेजिस्टर was changed to the
	 * शेष value जबतक we were in cache only mode. In this हाल
	 * regcache_sync will skip over it and we have to manually sync
	 * it.
	 */
	ret = regmap_पढ़ो(adau1977->regmap, ADAU1977_REG_PLL, &val);
	अगर (ret)
		जाओ err_disable_dvdd;

	अगर (val == 0x41) अणु
		regcache_cache_bypass(adau1977->regmap, true);
		ret = regmap_ग_लिखो(adau1977->regmap, ADAU1977_REG_PLL,
			0x41);
		अगर (ret)
			जाओ err_disable_dvdd;
		regcache_cache_bypass(adau1977->regmap, false);
	पूर्ण

	adau1977->enabled = true;

	वापस ret;

err_disable_dvdd:
	अगर (adau1977->dvdd_reg)
		regulator_disable(adau1977->dvdd_reg);
err_disable_avdd:
		regulator_disable(adau1977->avdd_reg);
	वापस ret;
पूर्ण

अटल पूर्णांक adau1977_set_bias_level(काष्ठा snd_soc_component *component,
	क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा adau1977 *adau1977 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			ret = adau1977_घातer_enable(adau1977);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		ret = adau1977_घातer_disable(adau1977);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक adau1977_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
	अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक width)
अणु
	काष्ठा adau1977 *adau1977 = snd_soc_component_get_drvdata(dai->component);
	अचिन्हित पूर्णांक ctrl0, ctrl1, drv;
	अचिन्हित पूर्णांक slot[4];
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (slots == 0) अणु
		/* 0 = No fixed slot width */
		adau1977->slot_width = 0;
		adau1977->max_master_fs = 192000;
		वापस regmap_update_bits(adau1977->regmap,
			ADAU1977_REG_SAI_CTRL0, ADAU1977_SAI_CTRL0_SAI_MASK,
			ADAU1977_SAI_CTRL0_SAI_I2S);
	पूर्ण

	अगर (rx_mask == 0 || tx_mask != 0)
		वापस -EINVAL;

	drv = 0;
	क्रम (i = 0; i < 4; i++) अणु
		slot[i] = __ffs(rx_mask);
		drv |= ADAU1977_SAI_OVERTEMP_DRV_C(i);
		rx_mask &= ~(1 << slot[i]);
		अगर (slot[i] >= slots)
			वापस -EINVAL;
		अगर (rx_mask == 0)
			अवरोध;
	पूर्ण

	अगर (rx_mask != 0)
		वापस -EINVAL;

	चयन (width) अणु
	हाल 16:
		ctrl1 = ADAU1977_SAI_CTRL1_SLOT_WIDTH_16;
		अवरोध;
	हाल 24:
		/* We can only generate 16 bit or 32 bit wide slots */
		अगर (adau1977->master)
			वापस -EINVAL;
		ctrl1 = ADAU1977_SAI_CTRL1_SLOT_WIDTH_24;
		अवरोध;
	हाल 32:
		ctrl1 = ADAU1977_SAI_CTRL1_SLOT_WIDTH_32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (slots) अणु
	हाल 2:
		ctrl0 = ADAU1977_SAI_CTRL0_SAI_TDM_2;
		अवरोध;
	हाल 4:
		ctrl0 = ADAU1977_SAI_CTRL0_SAI_TDM_4;
		अवरोध;
	हाल 8:
		ctrl0 = ADAU1977_SAI_CTRL0_SAI_TDM_8;
		अवरोध;
	हाल 16:
		ctrl0 = ADAU1977_SAI_CTRL0_SAI_TDM_16;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(adau1977->regmap, ADAU1977_REG_SAI_OVERTEMP,
		ADAU1977_SAI_OVERTEMP_DRV_C(0) |
		ADAU1977_SAI_OVERTEMP_DRV_C(1) |
		ADAU1977_SAI_OVERTEMP_DRV_C(2) |
		ADAU1977_SAI_OVERTEMP_DRV_C(3), drv);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(adau1977->regmap, ADAU1977_REG_CMAP12,
		(slot[1] << ADAU1977_CHAN_MAP_SECOND_SLOT_OFFSET) |
		(slot[0] << ADAU1977_CHAN_MAP_FIRST_SLOT_OFFSET));
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(adau1977->regmap, ADAU1977_REG_CMAP34,
		(slot[3] << ADAU1977_CHAN_MAP_SECOND_SLOT_OFFSET) |
		(slot[2] << ADAU1977_CHAN_MAP_FIRST_SLOT_OFFSET));
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(adau1977->regmap, ADAU1977_REG_SAI_CTRL0,
		ADAU1977_SAI_CTRL0_SAI_MASK, ctrl0);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(adau1977->regmap, ADAU1977_REG_SAI_CTRL1,
		ADAU1977_SAI_CTRL1_SLOT_WIDTH_MASK, ctrl1);
	अगर (ret)
		वापस ret;

	adau1977->slot_width = width;

	/* In master mode the maximum bitघड़ी is 24.576 MHz */
	adau1977->max_master_fs = min(192000, 24576000 / width / slots);

	वापस 0;
पूर्ण

अटल पूर्णांक adau1977_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक stream)
अणु
	काष्ठा adau1977 *adau1977 = snd_soc_component_get_drvdata(dai->component);
	अचिन्हित पूर्णांक val;

	अगर (mute)
		val = ADAU1977_MISC_CONTROL_MMUTE;
	अन्यथा
		val = 0;

	वापस regmap_update_bits(adau1977->regmap, ADAU1977_REG_MISC_CONTROL,
			ADAU1977_MISC_CONTROL_MMUTE, val);
पूर्ण

अटल पूर्णांक adau1977_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा adau1977 *adau1977 = snd_soc_component_get_drvdata(dai->component);
	अचिन्हित पूर्णांक ctrl0 = 0, ctrl1 = 0, block_घातer = 0;
	bool invert_lrclk;
	पूर्णांक ret;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		adau1977->master = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		ctrl1 |= ADAU1977_SAI_CTRL1_MASTER;
		adau1977->master = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		invert_lrclk = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		block_घातer |= ADAU1977_BLOCK_POWER_SAI_BCLK_EDGE;
		invert_lrclk = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		invert_lrclk = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		block_घातer |= ADAU1977_BLOCK_POWER_SAI_BCLK_EDGE;
		invert_lrclk = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	adau1977->right_j = false;
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		ctrl0 |= ADAU1977_SAI_CTRL0_FMT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		ctrl0 |= ADAU1977_SAI_CTRL0_FMT_LJ;
		invert_lrclk = !invert_lrclk;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		ctrl0 |= ADAU1977_SAI_CTRL0_FMT_RJ_24BIT;
		adau1977->right_j = true;
		invert_lrclk = !invert_lrclk;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		ctrl1 |= ADAU1977_SAI_CTRL1_LRCLK_PULSE;
		ctrl0 |= ADAU1977_SAI_CTRL0_FMT_I2S;
		invert_lrclk = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		ctrl1 |= ADAU1977_SAI_CTRL1_LRCLK_PULSE;
		ctrl0 |= ADAU1977_SAI_CTRL0_FMT_LJ;
		invert_lrclk = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (invert_lrclk)
		block_घातer |= ADAU1977_BLOCK_POWER_SAI_LR_POL;

	ret = regmap_update_bits(adau1977->regmap, ADAU1977_REG_BLOCK_POWER_SAI,
		ADAU1977_BLOCK_POWER_SAI_LR_POL |
		ADAU1977_BLOCK_POWER_SAI_BCLK_EDGE, block_घातer);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(adau1977->regmap, ADAU1977_REG_SAI_CTRL0,
		ADAU1977_SAI_CTRL0_FMT_MASK,
		ctrl0);
	अगर (ret)
		वापस ret;

	वापस regmap_update_bits(adau1977->regmap, ADAU1977_REG_SAI_CTRL1,
		ADAU1977_SAI_CTRL1_MASTER | ADAU1977_SAI_CTRL1_LRCLK_PULSE,
		ctrl1);
पूर्ण

अटल पूर्णांक adau1977_startup(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा adau1977 *adau1977 = snd_soc_component_get_drvdata(dai->component);
	u64 क्रमmats = 0;

	अगर (adau1977->slot_width == 16)
		क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE;
	अन्यथा अगर (adau1977->right_j || adau1977->slot_width == 24)
		क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE |
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S24_BE;

	snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
		SNDRV_PCM_HW_PARAM_RATE, &adau1977->स्थिरraपूर्णांकs);

	अगर (adau1977->master)
		snd_pcm_hw_स्थिरraपूर्णांक_minmax(substream->runसमय,
			SNDRV_PCM_HW_PARAM_RATE, 8000, adau1977->max_master_fs);

	अगर (क्रमmats != 0)
		snd_pcm_hw_स्थिरraपूर्णांक_mask64(substream->runसमय,
			SNDRV_PCM_HW_PARAM_FORMAT, क्रमmats);

	वापस 0;
पूर्ण

अटल पूर्णांक adau1977_set_tristate(काष्ठा snd_soc_dai *dai, पूर्णांक tristate)
अणु
	काष्ठा adau1977 *adau1977 = snd_soc_component_get_drvdata(dai->component);
	अचिन्हित पूर्णांक val;

	अगर (tristate)
		val = ADAU1977_SAI_OVERTEMP_DRV_HIZ;
	अन्यथा
		val = 0;

	वापस regmap_update_bits(adau1977->regmap, ADAU1977_REG_SAI_OVERTEMP,
		ADAU1977_SAI_OVERTEMP_DRV_HIZ, val);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops adau1977_dai_ops = अणु
	.startup	= adau1977_startup,
	.hw_params	= adau1977_hw_params,
	.mute_stream	= adau1977_mute,
	.set_fmt	= adau1977_set_dai_fmt,
	.set_tdm_slot	= adau1977_set_tdm_slot,
	.set_tristate	= adau1977_set_tristate,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver adau1977_dai = अणु
	.name = "adau1977-hifi",
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 4,
		.rates = SNDRV_PCM_RATE_KNOT,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE |
		    SNDRV_PCM_FMTBIT_S32_LE,
		.sig_bits = 24,
	पूर्ण,
	.ops = &adau1977_dai_ops,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक adau1977_rates[] = अणु
	8000, 16000, 32000, 64000, 128000,
	11025, 22050, 44100, 88200, 172400,
	12000, 24000, 48000, 96000, 192000,
पूर्ण;

#घोषणा ADAU1977_RATE_CONSTRAINT_MASK_32000 0x001f
#घोषणा ADAU1977_RATE_CONSTRAINT_MASK_44100 0x03e0
#घोषणा ADAU1977_RATE_CONSTRAINT_MASK_48000 0x7c00
/* All rates >= 32000 */
#घोषणा ADAU1977_RATE_CONSTRAINT_MASK_LRCLK 0x739c

अटल bool adau1977_check_sysclk(अचिन्हित पूर्णांक mclk, अचिन्हित पूर्णांक base_freq)
अणु
	अचिन्हित पूर्णांक mcs;

	अगर (mclk % (base_freq * 128) != 0)
		वापस false;

	mcs = mclk / (128 * base_freq);
	अगर (mcs < 1 || mcs > 6 || mcs == 5)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक adau1977_set_sysclk(काष्ठा snd_soc_component *component,
	पूर्णांक clk_id, पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा adau1977 *adau1977 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक mask = 0;
	अचिन्हित पूर्णांक clk_src;
	अचिन्हित पूर्णांक ret;

	अगर (dir != SND_SOC_CLOCK_IN)
		वापस -EINVAL;

	अगर (clk_id != ADAU1977_SYSCLK)
		वापस -EINVAL;

	चयन (source) अणु
	हाल ADAU1977_SYSCLK_SRC_MCLK:
		clk_src = 0;
		अवरोध;
	हाल ADAU1977_SYSCLK_SRC_LRCLK:
		clk_src = ADAU1977_PLL_CLK_S;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (freq != 0 && source == ADAU1977_SYSCLK_SRC_MCLK) अणु
		अगर (freq < 4000000 || freq > 36864000)
			वापस -EINVAL;

		अगर (adau1977_check_sysclk(freq, 32000))
			mask |= ADAU1977_RATE_CONSTRAINT_MASK_32000;
		अगर (adau1977_check_sysclk(freq, 44100))
			mask |= ADAU1977_RATE_CONSTRAINT_MASK_44100;
		अगर (adau1977_check_sysclk(freq, 48000))
			mask |= ADAU1977_RATE_CONSTRAINT_MASK_48000;

		अगर (mask == 0)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (source == ADAU1977_SYSCLK_SRC_LRCLK) अणु
		mask = ADAU1977_RATE_CONSTRAINT_MASK_LRCLK;
	पूर्ण

	ret = regmap_update_bits(adau1977->regmap, ADAU1977_REG_PLL,
		ADAU1977_PLL_CLK_S, clk_src);
	अगर (ret)
		वापस ret;

	adau1977->स्थिरraपूर्णांकs.mask = mask;
	adau1977->sysclk_src = source;
	adau1977->sysclk = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक adau1977_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा adau1977 *adau1977 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (adau1977->type) अणु
	हाल ADAU1977:
		ret = snd_soc_dapm_new_controls(dapm,
			adau1977_micbias_dapm_widमाला_लो,
			ARRAY_SIZE(adau1977_micbias_dapm_widमाला_लो));
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver adau1977_component_driver = अणु
	.probe			= adau1977_component_probe,
	.set_bias_level		= adau1977_set_bias_level,
	.set_sysclk		= adau1977_set_sysclk,
	.controls		= adau1977_snd_controls,
	.num_controls		= ARRAY_SIZE(adau1977_snd_controls),
	.dapm_widमाला_लो		= adau1977_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(adau1977_dapm_widमाला_लो),
	.dapm_routes		= adau1977_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(adau1977_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक adau1977_setup_micbias(काष्ठा adau1977 *adau1977)
अणु
	अचिन्हित पूर्णांक micbias;

	अगर (device_property_पढ़ो_u32(adau1977->dev, "adi,micbias", &micbias))
		micbias = ADAU1977_MICBIAS_8V5;

	अगर (micbias > ADAU1977_MICBIAS_9V0) अणु
		dev_err(adau1977->dev, "Invalid value for 'adi,micbias'\n");
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(adau1977->regmap, ADAU1977_REG_MICBIAS,
		ADAU1977_MICBIAS_MB_VOLTS_MASK,
		micbias << ADAU1977_MICBIAS_MB_VOLTS_OFFSET);
पूर्ण

पूर्णांक adau1977_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
	क्रमागत adau1977_type type, व्योम (*चयन_mode)(काष्ठा device *dev))
अणु
	अचिन्हित पूर्णांक घातer_off_mask;
	काष्ठा adau1977 *adau1977;
	पूर्णांक ret;

	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	adau1977 = devm_kzalloc(dev, माप(*adau1977), GFP_KERNEL);
	अगर (adau1977 == शून्य)
		वापस -ENOMEM;

	adau1977->dev = dev;
	adau1977->type = type;
	adau1977->regmap = regmap;
	adau1977->चयन_mode = चयन_mode;
	adau1977->max_master_fs = 192000;

	adau1977->स्थिरraपूर्णांकs.list = adau1977_rates;
	adau1977->स्थिरraपूर्णांकs.count = ARRAY_SIZE(adau1977_rates);

	adau1977->avdd_reg = devm_regulator_get(dev, "AVDD");
	अगर (IS_ERR(adau1977->avdd_reg))
		वापस PTR_ERR(adau1977->avdd_reg);

	adau1977->dvdd_reg = devm_regulator_get_optional(dev, "DVDD");
	अगर (IS_ERR(adau1977->dvdd_reg)) अणु
		अगर (PTR_ERR(adau1977->dvdd_reg) != -ENODEV)
			वापस PTR_ERR(adau1977->dvdd_reg);
		adau1977->dvdd_reg = शून्य;
	पूर्ण

	adau1977->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						       GPIOD_OUT_LOW);
	अगर (IS_ERR(adau1977->reset_gpio))
		वापस PTR_ERR(adau1977->reset_gpio);

	dev_set_drvdata(dev, adau1977);

	अगर (adau1977->reset_gpio)
		ndelay(100);

	ret = adau1977_घातer_enable(adau1977);
	अगर (ret)
		वापस ret;

	अगर (type == ADAU1977) अणु
		ret = adau1977_setup_micbias(adau1977);
		अगर (ret)
			जाओ err_घातeroff;
	पूर्ण

	अगर (adau1977->dvdd_reg)
		घातer_off_mask = ~0;
	अन्यथा
		घातer_off_mask = (अचिन्हित पूर्णांक)~ADAU1977_BLOCK_POWER_SAI_LDO_EN;

	ret = regmap_update_bits(adau1977->regmap, ADAU1977_REG_BLOCK_POWER_SAI,
				घातer_off_mask, 0x00);
	अगर (ret)
		जाओ err_घातeroff;

	ret = adau1977_घातer_disable(adau1977);
	अगर (ret)
		वापस ret;

	वापस devm_snd_soc_रेजिस्टर_component(dev, &adau1977_component_driver,
			&adau1977_dai, 1);

err_घातeroff:
	adau1977_घातer_disable(adau1977);
	वापस ret;

पूर्ण
EXPORT_SYMBOL_GPL(adau1977_probe);

अटल bool adau1977_रेजिस्टर_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ADAU1977_REG_STATUS(0):
	हाल ADAU1977_REG_STATUS(1):
	हाल ADAU1977_REG_STATUS(2):
	हाल ADAU1977_REG_STATUS(3):
	हाल ADAU1977_REG_ADC_CLIP:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

स्थिर काष्ठा regmap_config adau1977_regmap_config = अणु
	.max_रेजिस्टर = ADAU1977_REG_DC_HPF_CAL,
	.अस्थिर_reg = adau1977_रेजिस्टर_अस्थिर,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = adau1977_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(adau1977_reg_शेषs),
पूर्ण;
EXPORT_SYMBOL_GPL(adau1977_regmap_config);

MODULE_DESCRIPTION("ASoC ADAU1977/ADAU1978/ADAU1979 driver");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_LICENSE("GPL");
