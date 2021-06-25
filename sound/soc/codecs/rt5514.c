<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rt5514.c  --  RT5514 ALSA SoC audio codec driver
 *
 * Copyright 2015 Realtek Semiconductor Corp.
 * Author: Oder Chiou <oder_chiou@realtek.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/gpपन.स>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "rl6231.h"
#समावेश "rt5514.h"
#अगर IS_ENABLED(CONFIG_SND_SOC_RT5514_SPI)
#समावेश "rt5514-spi.h"
#पूर्ण_अगर

अटल स्थिर काष्ठा reg_sequence rt5514_i2c_patch[] = अणु
	अणु0x1800101c, 0x00000000पूर्ण,
	अणु0x18001100, 0x0000031fपूर्ण,
	अणु0x18001104, 0x00000007पूर्ण,
	अणु0x18001108, 0x00000000पूर्ण,
	अणु0x1800110c, 0x00000000पूर्ण,
	अणु0x18001110, 0x00000000पूर्ण,
	अणु0x18001114, 0x00000001पूर्ण,
	अणु0x18001118, 0x00000000पूर्ण,
	अणु0x18002f08, 0x00000006पूर्ण,
	अणु0x18002f00, 0x00055149पूर्ण,
	अणु0x18002f00, 0x0005514bपूर्ण,
	अणु0x18002f00, 0x00055149पूर्ण,
	अणु0xfafafafa, 0x00000001पूर्ण,
	अणु0x18002f10, 0x00000001पूर्ण,
	अणु0x18002f10, 0x00000000पूर्ण,
	अणु0x18002f10, 0x00000001पूर्ण,
	अणु0xfafafafa, 0x00000001पूर्ण,
	अणु0x18002000, 0x000010ecपूर्ण,
	अणु0xfafafafa, 0x00000000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence rt5514_patch[] = अणु
	अणुRT5514_DIG_IO_CTRL,		0x00000040पूर्ण,
	अणुRT5514_CLK_CTRL1,		0x38020041पूर्ण,
	अणुRT5514_SRC_CTRL,		0x44000eeeपूर्ण,
	अणुRT5514_ANA_CTRL_LDO10,		0x00028604पूर्ण,
	अणुRT5514_ANA_CTRL_ADCFED,	0x00000800पूर्ण,
	अणुRT5514_ASRC_IN_CTRL1,		0x00000003पूर्ण,
	अणुRT5514_DOWNFILTER0_CTRL3,	0x10000342पूर्ण,
	अणुRT5514_DOWNFILTER1_CTRL3,	0x10000342पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष rt5514_reg[] = अणु
	अणुRT5514_RESET,			0x00000000पूर्ण,
	अणुRT5514_PWR_ANA1,		0x00808880पूर्ण,
	अणुRT5514_PWR_ANA2,		0x00220000पूर्ण,
	अणुRT5514_I2S_CTRL1,		0x00000330पूर्ण,
	अणुRT5514_I2S_CTRL2,		0x20000000पूर्ण,
	अणुRT5514_VAD_CTRL6,		0xc00007d2पूर्ण,
	अणुRT5514_EXT_VAD_CTRL,		0x80000080पूर्ण,
	अणुRT5514_DIG_IO_CTRL,		0x00000040पूर्ण,
	अणुRT5514_PAD_CTRL1,		0x00804000पूर्ण,
	अणुRT5514_DMIC_DATA_CTRL,		0x00000005पूर्ण,
	अणुRT5514_DIG_SOURCE_CTRL,	0x00000002पूर्ण,
	अणुRT5514_SRC_CTRL,		0x44000eeeपूर्ण,
	अणुRT5514_DOWNFILTER2_CTRL1,	0x0000882fपूर्ण,
	अणुRT5514_PLL_SOURCE_CTRL,	0x00000004पूर्ण,
	अणुRT5514_CLK_CTRL1,		0x38020041पूर्ण,
	अणुRT5514_CLK_CTRL2,		0x00000000पूर्ण,
	अणुRT5514_PLL3_CALIB_CTRL1,	0x00400200पूर्ण,
	अणुRT5514_PLL3_CALIB_CTRL5,	0x40220012पूर्ण,
	अणुRT5514_DELAY_BUF_CTRL1,	0x7fff006aपूर्ण,
	अणुRT5514_DELAY_BUF_CTRL3,	0x00000000पूर्ण,
	अणुRT5514_ASRC_IN_CTRL1,		0x00000003पूर्ण,
	अणुRT5514_DOWNFILTER0_CTRL1,	0x00020c2fपूर्ण,
	अणुRT5514_DOWNFILTER0_CTRL2,	0x00020c2fपूर्ण,
	अणुRT5514_DOWNFILTER0_CTRL3,	0x10000342पूर्ण,
	अणुRT5514_DOWNFILTER1_CTRL1,	0x00020c2fपूर्ण,
	अणुRT5514_DOWNFILTER1_CTRL2,	0x00020c2fपूर्ण,
	अणुRT5514_DOWNFILTER1_CTRL3,	0x10000342पूर्ण,
	अणुRT5514_ANA_CTRL_LDO10,		0x00028604पूर्ण,
	अणुRT5514_ANA_CTRL_LDO18_16,	0x02000345पूर्ण,
	अणुRT5514_ANA_CTRL_ADC12,		0x0000a2a8पूर्ण,
	अणुRT5514_ANA_CTRL_ADC21,		0x00001180पूर्ण,
	अणुRT5514_ANA_CTRL_ADC22,		0x0000aaa8पूर्ण,
	अणुRT5514_ANA_CTRL_ADC23,		0x00151427पूर्ण,
	अणुRT5514_ANA_CTRL_MICBST,	0x00002000पूर्ण,
	अणुRT5514_ANA_CTRL_ADCFED,	0x00000800पूर्ण,
	अणुRT5514_ANA_CTRL_INBUF,		0x00000143पूर्ण,
	अणुRT5514_ANA_CTRL_VREF,		0x00008d50पूर्ण,
	अणुRT5514_ANA_CTRL_PLL3,		0x0000000eपूर्ण,
	अणुRT5514_ANA_CTRL_PLL1_1,	0x00000000पूर्ण,
	अणुRT5514_ANA_CTRL_PLL1_2,	0x00030220पूर्ण,
	अणुRT5514_DMIC_LP_CTRL,		0x00000000पूर्ण,
	अणुRT5514_MISC_CTRL_DSP,		0x00000000पूर्ण,
	अणुRT5514_DSP_CTRL1,		0x00055149पूर्ण,
	अणुRT5514_DSP_CTRL3,		0x00000006पूर्ण,
	अणुRT5514_DSP_CTRL4,		0x00000001पूर्ण,
	अणुRT5514_VENDOR_ID1,		0x00000001पूर्ण,
	अणुRT5514_VENDOR_ID2,		0x10ec5514पूर्ण,
पूर्ण;

अटल व्योम rt5514_enable_dsp_prepare(काष्ठा rt5514_priv *rt5514)
अणु
	/* Reset */
	regmap_ग_लिखो(rt5514->i2c_regmap, 0x18002000, 0x000010ec);
	/* LDO_I_limit */
	regmap_ग_लिखो(rt5514->i2c_regmap, 0x18002200, 0x00028604);
	/* I2C bypass enable */
	regmap_ग_लिखो(rt5514->i2c_regmap, 0xfafafafa, 0x00000001);
	/* mini-core reset */
	regmap_ग_लिखो(rt5514->i2c_regmap, 0x18002f00, 0x0005514b);
	regmap_ग_लिखो(rt5514->i2c_regmap, 0x18002f00, 0x00055149);
	/* I2C bypass disable */
	regmap_ग_लिखो(rt5514->i2c_regmap, 0xfafafafa, 0x00000000);
	/* PIN config */
	regmap_ग_लिखो(rt5514->i2c_regmap, 0x18002070, 0x00000040);
	/* PLL3(QN)=RCOSC*(10+2) */
	regmap_ग_लिखो(rt5514->i2c_regmap, 0x18002240, 0x0000000a);
	/* PLL3 source=RCOSC, fsi=rt_clk */
	regmap_ग_लिखो(rt5514->i2c_regmap, 0x18002100, 0x0000000b);
	/* Power on RCOSC, pll3 */
	regmap_ग_लिखो(rt5514->i2c_regmap, 0x18002004, 0x00808b81);
	/* DSP clk source = pll3, ENABLE DSP clk */
	regmap_ग_लिखो(rt5514->i2c_regmap, 0x18002f08, 0x00000005);
	/* Enable DSP clk स्वतः चयन */
	regmap_ग_लिखो(rt5514->i2c_regmap, 0x18001114, 0x00000001);
	/* Reduce DSP घातer */
	regmap_ग_लिखो(rt5514->i2c_regmap, 0x18001118, 0x00000001);
पूर्ण

अटल bool rt5514_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT5514_VENDOR_ID1:
	हाल RT5514_VENDOR_ID2:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt5514_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT5514_RESET:
	हाल RT5514_PWR_ANA1:
	हाल RT5514_PWR_ANA2:
	हाल RT5514_I2S_CTRL1:
	हाल RT5514_I2S_CTRL2:
	हाल RT5514_VAD_CTRL6:
	हाल RT5514_EXT_VAD_CTRL:
	हाल RT5514_DIG_IO_CTRL:
	हाल RT5514_PAD_CTRL1:
	हाल RT5514_DMIC_DATA_CTRL:
	हाल RT5514_DIG_SOURCE_CTRL:
	हाल RT5514_SRC_CTRL:
	हाल RT5514_DOWNFILTER2_CTRL1:
	हाल RT5514_PLL_SOURCE_CTRL:
	हाल RT5514_CLK_CTRL1:
	हाल RT5514_CLK_CTRL2:
	हाल RT5514_PLL3_CALIB_CTRL1:
	हाल RT5514_PLL3_CALIB_CTRL5:
	हाल RT5514_DELAY_BUF_CTRL1:
	हाल RT5514_DELAY_BUF_CTRL3:
	हाल RT5514_ASRC_IN_CTRL1:
	हाल RT5514_DOWNFILTER0_CTRL1:
	हाल RT5514_DOWNFILTER0_CTRL2:
	हाल RT5514_DOWNFILTER0_CTRL3:
	हाल RT5514_DOWNFILTER1_CTRL1:
	हाल RT5514_DOWNFILTER1_CTRL2:
	हाल RT5514_DOWNFILTER1_CTRL3:
	हाल RT5514_ANA_CTRL_LDO10:
	हाल RT5514_ANA_CTRL_LDO18_16:
	हाल RT5514_ANA_CTRL_ADC12:
	हाल RT5514_ANA_CTRL_ADC21:
	हाल RT5514_ANA_CTRL_ADC22:
	हाल RT5514_ANA_CTRL_ADC23:
	हाल RT5514_ANA_CTRL_MICBST:
	हाल RT5514_ANA_CTRL_ADCFED:
	हाल RT5514_ANA_CTRL_INBUF:
	हाल RT5514_ANA_CTRL_VREF:
	हाल RT5514_ANA_CTRL_PLL3:
	हाल RT5514_ANA_CTRL_PLL1_1:
	हाल RT5514_ANA_CTRL_PLL1_2:
	हाल RT5514_DMIC_LP_CTRL:
	हाल RT5514_MISC_CTRL_DSP:
	हाल RT5514_DSP_CTRL1:
	हाल RT5514_DSP_CTRL3:
	हाल RT5514_DSP_CTRL4:
	हाल RT5514_VENDOR_ID1:
	हाल RT5514_VENDOR_ID2:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt5514_i2c_पढ़ोable_रेजिस्टर(काष्ठा device *dev,
	अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT5514_DSP_MAPPING | RT5514_RESET:
	हाल RT5514_DSP_MAPPING | RT5514_PWR_ANA1:
	हाल RT5514_DSP_MAPPING | RT5514_PWR_ANA2:
	हाल RT5514_DSP_MAPPING | RT5514_I2S_CTRL1:
	हाल RT5514_DSP_MAPPING | RT5514_I2S_CTRL2:
	हाल RT5514_DSP_MAPPING | RT5514_VAD_CTRL6:
	हाल RT5514_DSP_MAPPING | RT5514_EXT_VAD_CTRL:
	हाल RT5514_DSP_MAPPING | RT5514_DIG_IO_CTRL:
	हाल RT5514_DSP_MAPPING | RT5514_PAD_CTRL1:
	हाल RT5514_DSP_MAPPING | RT5514_DMIC_DATA_CTRL:
	हाल RT5514_DSP_MAPPING | RT5514_DIG_SOURCE_CTRL:
	हाल RT5514_DSP_MAPPING | RT5514_SRC_CTRL:
	हाल RT5514_DSP_MAPPING | RT5514_DOWNFILTER2_CTRL1:
	हाल RT5514_DSP_MAPPING | RT5514_PLL_SOURCE_CTRL:
	हाल RT5514_DSP_MAPPING | RT5514_CLK_CTRL1:
	हाल RT5514_DSP_MAPPING | RT5514_CLK_CTRL2:
	हाल RT5514_DSP_MAPPING | RT5514_PLL3_CALIB_CTRL1:
	हाल RT5514_DSP_MAPPING | RT5514_PLL3_CALIB_CTRL5:
	हाल RT5514_DSP_MAPPING | RT5514_DELAY_BUF_CTRL1:
	हाल RT5514_DSP_MAPPING | RT5514_DELAY_BUF_CTRL3:
	हाल RT5514_DSP_MAPPING | RT5514_ASRC_IN_CTRL1:
	हाल RT5514_DSP_MAPPING | RT5514_DOWNFILTER0_CTRL1:
	हाल RT5514_DSP_MAPPING | RT5514_DOWNFILTER0_CTRL2:
	हाल RT5514_DSP_MAPPING | RT5514_DOWNFILTER0_CTRL3:
	हाल RT5514_DSP_MAPPING | RT5514_DOWNFILTER1_CTRL1:
	हाल RT5514_DSP_MAPPING | RT5514_DOWNFILTER1_CTRL2:
	हाल RT5514_DSP_MAPPING | RT5514_DOWNFILTER1_CTRL3:
	हाल RT5514_DSP_MAPPING | RT5514_ANA_CTRL_LDO10:
	हाल RT5514_DSP_MAPPING | RT5514_ANA_CTRL_LDO18_16:
	हाल RT5514_DSP_MAPPING | RT5514_ANA_CTRL_ADC12:
	हाल RT5514_DSP_MAPPING | RT5514_ANA_CTRL_ADC21:
	हाल RT5514_DSP_MAPPING | RT5514_ANA_CTRL_ADC22:
	हाल RT5514_DSP_MAPPING | RT5514_ANA_CTRL_ADC23:
	हाल RT5514_DSP_MAPPING | RT5514_ANA_CTRL_MICBST:
	हाल RT5514_DSP_MAPPING | RT5514_ANA_CTRL_ADCFED:
	हाल RT5514_DSP_MAPPING | RT5514_ANA_CTRL_INBUF:
	हाल RT5514_DSP_MAPPING | RT5514_ANA_CTRL_VREF:
	हाल RT5514_DSP_MAPPING | RT5514_ANA_CTRL_PLL3:
	हाल RT5514_DSP_MAPPING | RT5514_ANA_CTRL_PLL1_1:
	हाल RT5514_DSP_MAPPING | RT5514_ANA_CTRL_PLL1_2:
	हाल RT5514_DSP_MAPPING | RT5514_DMIC_LP_CTRL:
	हाल RT5514_DSP_MAPPING | RT5514_MISC_CTRL_DSP:
	हाल RT5514_DSP_MAPPING | RT5514_DSP_CTRL1:
	हाल RT5514_DSP_MAPPING | RT5514_DSP_CTRL3:
	हाल RT5514_DSP_MAPPING | RT5514_DSP_CTRL4:
	हाल RT5514_DSP_MAPPING | RT5514_VENDOR_ID1:
	हाल RT5514_DSP_MAPPING | RT5514_VENDOR_ID2:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

/* अणु-3, 0, +3, +4.5, +7.5, +9.5, +12, +14, +17पूर्ण dB */
अटल स्थिर DECLARE_TLV_DB_RANGE(bst_tlv,
	0, 2, TLV_DB_SCALE_ITEM(-300, 300, 0),
	3, 3, TLV_DB_SCALE_ITEM(450, 0, 0),
	4, 4, TLV_DB_SCALE_ITEM(750, 0, 0),
	5, 5, TLV_DB_SCALE_ITEM(950, 0, 0),
	6, 6, TLV_DB_SCALE_ITEM(1200, 0, 0),
	7, 7, TLV_DB_SCALE_ITEM(1400, 0, 0),
	8, 8, TLV_DB_SCALE_ITEM(1700, 0, 0)
);

अटल स्थिर DECLARE_TLV_DB_SCALE(adc_vol_tlv, -1725, 75, 0);

अटल पूर्णांक rt5514_dsp_voice_wake_up_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt5514_priv *rt5514 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = rt5514->dsp_enabled;

	वापस 0;
पूर्ण

अटल पूर्णांक rt5514_calibration(काष्ठा rt5514_priv *rt5514, bool on)
अणु
	अगर (on) अणु
		regmap_ग_लिखो(rt5514->regmap, RT5514_ANA_CTRL_PLL3, 0x0000000a);
		regmap_update_bits(rt5514->regmap, RT5514_PLL_SOURCE_CTRL, 0xf,
			0xa);
		regmap_update_bits(rt5514->regmap, RT5514_PWR_ANA1, 0x301,
			0x301);
		regmap_ग_लिखो(rt5514->regmap, RT5514_PLL3_CALIB_CTRL4,
			0x80000000 | rt5514->pll3_cal_value);
		regmap_ग_लिखो(rt5514->regmap, RT5514_PLL3_CALIB_CTRL1,
			0x8bb80800);
		regmap_update_bits(rt5514->regmap, RT5514_PLL3_CALIB_CTRL5,
			0xc0000000, 0x80000000);
		regmap_update_bits(rt5514->regmap, RT5514_PLL3_CALIB_CTRL5,
			0xc0000000, 0xc0000000);
	पूर्ण अन्यथा अणु
		regmap_update_bits(rt5514->regmap, RT5514_PLL3_CALIB_CTRL5,
			0xc0000000, 0x40000000);
		regmap_update_bits(rt5514->regmap, RT5514_PWR_ANA1, 0x301, 0);
		regmap_update_bits(rt5514->regmap, RT5514_PLL_SOURCE_CTRL, 0xf,
			0x4);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5514_dsp_voice_wake_up_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt5514_priv *rt5514 = snd_soc_component_get_drvdata(component);
	स्थिर काष्ठा firmware *fw = शून्य;
	u8 buf[8];

	अगर (ucontrol->value.पूर्णांकeger.value[0] == rt5514->dsp_enabled)
		वापस 0;

	अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
		rt5514->dsp_enabled = ucontrol->value.पूर्णांकeger.value[0];

		अगर (rt5514->dsp_enabled) अणु
			अगर (rt5514->pdata.dsp_calib_clk_name &&
				!IS_ERR(rt5514->dsp_calib_clk)) अणु
				अगर (clk_set_rate(rt5514->dsp_calib_clk,
					rt5514->pdata.dsp_calib_clk_rate))
					dev_err(component->dev,
						"Can't set rate for mclk");

				अगर (clk_prepare_enable(rt5514->dsp_calib_clk))
					dev_err(component->dev,
						"Can't enable dsp_calib_clk");

				rt5514_calibration(rt5514, true);

				msleep(20);
#अगर IS_ENABLED(CONFIG_SND_SOC_RT5514_SPI)
				rt5514_spi_burst_पढ़ो(RT5514_PLL3_CALIB_CTRL6 |
					RT5514_DSP_MAPPING, buf, माप(buf));
#अन्यथा
				dev_err(component->dev, "There is no SPI driver for"
					" loading the firmware\n");
				स_रखो(buf, 0, माप(buf));
#पूर्ण_अगर
				rt5514->pll3_cal_value = buf[0] | buf[1] << 8 |
					buf[2] << 16 | buf[3] << 24;

				rt5514_calibration(rt5514, false);
				clk_disable_unprepare(rt5514->dsp_calib_clk);
			पूर्ण

			rt5514_enable_dsp_prepare(rt5514);

			request_firmware(&fw, RT5514_FIRMWARE1, component->dev);
			अगर (fw) अणु
#अगर IS_ENABLED(CONFIG_SND_SOC_RT5514_SPI)
				rt5514_spi_burst_ग_लिखो(0x4ff60000, fw->data,
					((fw->size/8)+1)*8);
#अन्यथा
				dev_err(component->dev, "There is no SPI driver for"
					" loading the firmware\n");
#पूर्ण_अगर
				release_firmware(fw);
				fw = शून्य;
			पूर्ण

			request_firmware(&fw, RT5514_FIRMWARE2, component->dev);
			अगर (fw) अणु
#अगर IS_ENABLED(CONFIG_SND_SOC_RT5514_SPI)
				rt5514_spi_burst_ग_लिखो(0x4ffc0000, fw->data,
					((fw->size/8)+1)*8);
#अन्यथा
				dev_err(component->dev, "There is no SPI driver for"
					" loading the firmware\n");
#पूर्ण_अगर
				release_firmware(fw);
				fw = शून्य;
			पूर्ण

			/* DSP run */
			regmap_ग_लिखो(rt5514->i2c_regmap, 0x18002f00,
				0x00055148);

			अगर (rt5514->pdata.dsp_calib_clk_name &&
				!IS_ERR(rt5514->dsp_calib_clk)) अणु
				msleep(20);

				regmap_ग_लिखो(rt5514->i2c_regmap, 0x1800211c,
					rt5514->pll3_cal_value);
				regmap_ग_लिखो(rt5514->i2c_regmap, 0x18002124,
					0x00220012);
				regmap_ग_लिखो(rt5514->i2c_regmap, 0x18002124,
					0x80220042);
				regmap_ग_लिखो(rt5514->i2c_regmap, 0x18002124,
					0xe0220042);
			पूर्ण
		पूर्ण अन्यथा अणु
			regmap_multi_reg_ग_लिखो(rt5514->i2c_regmap,
				rt5514_i2c_patch, ARRAY_SIZE(rt5514_i2c_patch));
			regcache_mark_dirty(rt5514->regmap);
			regcache_sync(rt5514->regmap);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new rt5514_snd_controls[] = अणु
	SOC_DOUBLE_TLV("MIC Boost Volume", RT5514_ANA_CTRL_MICBST,
		RT5514_SEL_BSTL_SFT, RT5514_SEL_BSTR_SFT, 8, 0, bst_tlv),
	SOC_DOUBLE_R_TLV("ADC1 Capture Volume", RT5514_DOWNFILTER0_CTRL1,
		RT5514_DOWNFILTER0_CTRL2, RT5514_AD_GAIN_SFT, 63, 0,
		adc_vol_tlv),
	SOC_DOUBLE_R_TLV("ADC2 Capture Volume", RT5514_DOWNFILTER1_CTRL1,
		RT5514_DOWNFILTER1_CTRL2, RT5514_AD_GAIN_SFT, 63, 0,
		adc_vol_tlv),
	SOC_SINGLE_EXT("DSP Voice Wake Up", SND_SOC_NOPM, 0, 1, 0,
		rt5514_dsp_voice_wake_up_get, rt5514_dsp_voice_wake_up_put),
पूर्ण;

/* ADC Mixer*/
अटल स्थिर काष्ठा snd_kcontrol_new rt5514_sto1_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("DMIC Switch", RT5514_DOWNFILTER0_CTRL1,
		RT5514_AD_DMIC_MIX_BIT, 1, 1),
	SOC_DAPM_SINGLE("ADC Switch", RT5514_DOWNFILTER0_CTRL1,
		RT5514_AD_AD_MIX_BIT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5514_sto1_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("DMIC Switch", RT5514_DOWNFILTER0_CTRL2,
		RT5514_AD_DMIC_MIX_BIT, 1, 1),
	SOC_DAPM_SINGLE("ADC Switch", RT5514_DOWNFILTER0_CTRL2,
		RT5514_AD_AD_MIX_BIT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5514_sto2_adc_l_mix[] = अणु
	SOC_DAPM_SINGLE("DMIC Switch", RT5514_DOWNFILTER1_CTRL1,
		RT5514_AD_DMIC_MIX_BIT, 1, 1),
	SOC_DAPM_SINGLE("ADC Switch", RT5514_DOWNFILTER1_CTRL1,
		RT5514_AD_AD_MIX_BIT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt5514_sto2_adc_r_mix[] = अणु
	SOC_DAPM_SINGLE("DMIC Switch", RT5514_DOWNFILTER1_CTRL2,
		RT5514_AD_DMIC_MIX_BIT, 1, 1),
	SOC_DAPM_SINGLE("ADC Switch", RT5514_DOWNFILTER1_CTRL2,
		RT5514_AD_AD_MIX_BIT, 1, 1),
पूर्ण;

/* DMIC Source */
अटल स्थिर अक्षर * स्थिर rt5514_dmic_src[] = अणु
	"DMIC1", "DMIC2"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt5514_stereo1_dmic_क्रमागत, RT5514_DIG_SOURCE_CTRL,
	RT5514_AD0_DMIC_INPUT_SEL_SFT, rt5514_dmic_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5514_sto1_dmic_mux =
	SOC_DAPM_ENUM("Stereo1 DMIC Source", rt5514_stereo1_dmic_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt5514_stereo2_dmic_क्रमागत, RT5514_DIG_SOURCE_CTRL,
	RT5514_AD1_DMIC_INPUT_SEL_SFT, rt5514_dmic_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt5514_sto2_dmic_mux =
	SOC_DAPM_ENUM("Stereo2 DMIC Source", rt5514_stereo2_dmic_क्रमागत);

/**
 * rt5514_calc_dmic_clk - Calculate the frequency भागider parameter of dmic.
 *
 * @component: only used क्रम dev_warn
 * @rate: base घड़ी rate.
 *
 * Choose भागider parameter that gives the highest possible DMIC frequency in
 * 1MHz - 3MHz range.
 */
अटल पूर्णांक rt5514_calc_dmic_clk(काष्ठा snd_soc_component *component, पूर्णांक rate)
अणु
	पूर्णांक भाग[] = अणु2, 3, 4, 8, 12, 16, 24, 32पूर्ण;
	पूर्णांक i;

	अगर (rate < 1000000 * भाग[0]) अणु
		pr_warn("Base clock rate %d is too low\n", rate);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(भाग); i++) अणु
		/* find भागider that gives DMIC frequency below 3.072MHz */
		अगर (3072000 * भाग[i] >= rate)
			वापस i;
	पूर्ण

	dev_warn(component->dev, "Base clock rate %d is too high\n", rate);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक rt5514_set_dmic_clk(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt5514_priv *rt5514 = snd_soc_component_get_drvdata(component);
	पूर्णांक idx;

	idx = rt5514_calc_dmic_clk(component, rt5514->sysclk);
	अगर (idx < 0)
		dev_err(component->dev, "Failed to set DMIC clock\n");
	अन्यथा
		regmap_update_bits(rt5514->regmap, RT5514_CLK_CTRL1,
			RT5514_CLK_DMIC_OUT_SEL_MASK,
			idx << RT5514_CLK_DMIC_OUT_SEL_SFT);

	अगर (rt5514->pdata.dmic_init_delay)
		msleep(rt5514->pdata.dmic_init_delay);

	वापस idx;
पूर्ण

अटल पूर्णांक rt5514_is_sys_clk_from_pll(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	काष्ठा rt5514_priv *rt5514 = snd_soc_component_get_drvdata(component);

	अगर (rt5514->sysclk_src == RT5514_SCLK_S_PLL1)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक rt5514_i2s_use_asrc(काष्ठा snd_soc_dapm_widget *source,
	काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	काष्ठा rt5514_priv *rt5514 = snd_soc_component_get_drvdata(component);

	वापस (rt5514->sysclk > rt5514->lrck * 384);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget rt5514_dapm_widमाला_लो[] = अणु
	/* Input Lines */
	SND_SOC_DAPM_INPUT("DMIC1L"),
	SND_SOC_DAPM_INPUT("DMIC1R"),
	SND_SOC_DAPM_INPUT("DMIC2L"),
	SND_SOC_DAPM_INPUT("DMIC2R"),

	SND_SOC_DAPM_INPUT("AMICL"),
	SND_SOC_DAPM_INPUT("AMICR"),

	SND_SOC_DAPM_PGA("DMIC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DMIC2", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY_S("DMIC CLK", 1, SND_SOC_NOPM, 0, 0,
		rt5514_set_dmic_clk, SND_SOC_DAPM_PRE_PMU),

	SND_SOC_DAPM_SUPPLY("ADC CLK", RT5514_CLK_CTRL1,
		RT5514_CLK_AD_ANA1_EN_BIT, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("LDO18 IN", RT5514_PWR_ANA1,
		RT5514_POW_LDO18_IN_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("LDO18 ADC", RT5514_PWR_ANA1,
		RT5514_POW_LDO18_ADC_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("LDO21", RT5514_PWR_ANA1, RT5514_POW_LDO21_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BG LDO18 IN", RT5514_PWR_ANA1,
		RT5514_POW_BG_LDO18_IN_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BG LDO21", RT5514_PWR_ANA1,
		RT5514_POW_BG_LDO21_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BG MBIAS", RT5514_PWR_ANA2,
		RT5514_POW_BG_MBIAS_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MBIAS", RT5514_PWR_ANA2, RT5514_POW_MBIAS_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("VREF2", RT5514_PWR_ANA2, RT5514_POW_VREF2_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("VREF1", RT5514_PWR_ANA2, RT5514_POW_VREF1_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC Power", SND_SOC_NOPM, 0, 0, शून्य, 0),


	SND_SOC_DAPM_SUPPLY("LDO16L", RT5514_PWR_ANA2, RT5514_POWL_LDO16_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC1L", RT5514_PWR_ANA2, RT5514_POW_ADC1_L_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BSTL2", RT5514_PWR_ANA2, RT5514_POW2_BSTL_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BSTL", RT5514_PWR_ANA2, RT5514_POW_BSTL_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADCFEDL", RT5514_PWR_ANA2, RT5514_POW_ADCFEDL_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADCL Power", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("LDO16R", RT5514_PWR_ANA2, RT5514_POWR_LDO16_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADC1R", RT5514_PWR_ANA2, RT5514_POW_ADC1_R_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BSTR2", RT5514_PWR_ANA2, RT5514_POW2_BSTR_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BSTR", RT5514_PWR_ANA2, RT5514_POW_BSTR_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADCFEDR", RT5514_PWR_ANA2, RT5514_POW_ADCFEDR_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ADCR Power", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("PLL1 LDO ENABLE", RT5514_ANA_CTRL_PLL1_2,
		RT5514_EN_LDO_PLL1_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL1 LDO", RT5514_PWR_ANA2,
		RT5514_POW_PLL1_LDO_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL1", RT5514_PWR_ANA2, RT5514_POW_PLL1_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ASRC AD1", 1, RT5514_CLK_CTRL2,
		RT5514_CLK_AD0_ASRC_EN_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("ASRC AD2", 1, RT5514_CLK_CTRL2,
		RT5514_CLK_AD1_ASRC_EN_BIT, 0, शून्य, 0),

	/* ADC Mux */
	SND_SOC_DAPM_MUX("Stereo1 DMIC Mux", SND_SOC_NOPM, 0, 0,
				&rt5514_sto1_dmic_mux),
	SND_SOC_DAPM_MUX("Stereo2 DMIC Mux", SND_SOC_NOPM, 0, 0,
				&rt5514_sto2_dmic_mux),

	/* ADC Mixer */
	SND_SOC_DAPM_SUPPLY("adc stereo1 filter", RT5514_CLK_CTRL1,
		RT5514_CLK_AD0_EN_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("adc stereo2 filter", RT5514_CLK_CTRL1,
		RT5514_CLK_AD1_EN_BIT, 0, शून्य, 0),

	SND_SOC_DAPM_MIXER("Sto1 ADC MIXL", SND_SOC_NOPM, 0, 0,
		rt5514_sto1_adc_l_mix, ARRAY_SIZE(rt5514_sto1_adc_l_mix)),
	SND_SOC_DAPM_MIXER("Sto1 ADC MIXR", SND_SOC_NOPM, 0, 0,
		rt5514_sto1_adc_r_mix, ARRAY_SIZE(rt5514_sto1_adc_r_mix)),
	SND_SOC_DAPM_MIXER("Sto2 ADC MIXL", SND_SOC_NOPM, 0, 0,
		rt5514_sto2_adc_l_mix, ARRAY_SIZE(rt5514_sto2_adc_l_mix)),
	SND_SOC_DAPM_MIXER("Sto2 ADC MIXR", SND_SOC_NOPM, 0, 0,
		rt5514_sto2_adc_r_mix, ARRAY_SIZE(rt5514_sto2_adc_r_mix)),

	SND_SOC_DAPM_ADC("Stereo1 ADC MIXL", शून्य, RT5514_DOWNFILTER0_CTRL1,
		RT5514_AD_AD_MUTE_BIT, 1),
	SND_SOC_DAPM_ADC("Stereo1 ADC MIXR", शून्य, RT5514_DOWNFILTER0_CTRL2,
		RT5514_AD_AD_MUTE_BIT, 1),
	SND_SOC_DAPM_ADC("Stereo2 ADC MIXL", शून्य, RT5514_DOWNFILTER1_CTRL1,
		RT5514_AD_AD_MUTE_BIT, 1),
	SND_SOC_DAPM_ADC("Stereo2 ADC MIXR", शून्य, RT5514_DOWNFILTER1_CTRL2,
		RT5514_AD_AD_MUTE_BIT, 1),

	/* ADC PGA */
	SND_SOC_DAPM_PGA("Stereo1 ADC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Stereo2 ADC MIX", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* Audio Interface */
	SND_SOC_DAPM_AIF_OUT("AIF1TX", "AIF1 Capture", 0, SND_SOC_NOPM, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt5514_dapm_routes[] = अणु
	अणु "DMIC1", शून्य, "DMIC1L" पूर्ण,
	अणु "DMIC1", शून्य, "DMIC1R" पूर्ण,
	अणु "DMIC2", शून्य, "DMIC2L" पूर्ण,
	अणु "DMIC2", शून्य, "DMIC2R" पूर्ण,

	अणु "DMIC1L", शून्य, "DMIC CLK" पूर्ण,
	अणु "DMIC1R", शून्य, "DMIC CLK" पूर्ण,
	अणु "DMIC2L", शून्य, "DMIC CLK" पूर्ण,
	अणु "DMIC2R", शून्य, "DMIC CLK" पूर्ण,

	अणु "Stereo1 DMIC Mux", "DMIC1", "DMIC1" पूर्ण,
	अणु "Stereo1 DMIC Mux", "DMIC2", "DMIC2" पूर्ण,

	अणु "Sto1 ADC MIXL", "DMIC Switch", "Stereo1 DMIC Mux" पूर्ण,
	अणु "Sto1 ADC MIXL", "ADC Switch", "AMICL" पूर्ण,
	अणु "Sto1 ADC MIXR", "DMIC Switch", "Stereo1 DMIC Mux" पूर्ण,
	अणु "Sto1 ADC MIXR", "ADC Switch", "AMICR" पूर्ण,

	अणु "ADC Power", शून्य, "LDO18 IN" पूर्ण,
	अणु "ADC Power", शून्य, "LDO18 ADC" पूर्ण,
	अणु "ADC Power", शून्य, "LDO21" पूर्ण,
	अणु "ADC Power", शून्य, "BG LDO18 IN" पूर्ण,
	अणु "ADC Power", शून्य, "BG LDO21" पूर्ण,
	अणु "ADC Power", शून्य, "BG MBIAS" पूर्ण,
	अणु "ADC Power", शून्य, "MBIAS" पूर्ण,
	अणु "ADC Power", शून्य, "VREF2" पूर्ण,
	अणु "ADC Power", शून्य, "VREF1" पूर्ण,

	अणु "ADCL Power", शून्य, "LDO16L" पूर्ण,
	अणु "ADCL Power", शून्य, "ADC1L" पूर्ण,
	अणु "ADCL Power", शून्य, "BSTL2" पूर्ण,
	अणु "ADCL Power", शून्य, "BSTL" पूर्ण,
	अणु "ADCL Power", शून्य, "ADCFEDL" पूर्ण,

	अणु "ADCR Power", शून्य, "LDO16R" पूर्ण,
	अणु "ADCR Power", शून्य, "ADC1R" पूर्ण,
	अणु "ADCR Power", शून्य, "BSTR2" पूर्ण,
	अणु "ADCR Power", शून्य, "BSTR" पूर्ण,
	अणु "ADCR Power", शून्य, "ADCFEDR" पूर्ण,

	अणु "AMICL", शून्य, "ADC CLK" पूर्ण,
	अणु "AMICL", शून्य, "ADC Power" पूर्ण,
	अणु "AMICL", शून्य, "ADCL Power" पूर्ण,
	अणु "AMICR", शून्य, "ADC CLK" पूर्ण,
	अणु "AMICR", शून्य, "ADC Power" पूर्ण,
	अणु "AMICR", शून्य, "ADCR Power" पूर्ण,

	अणु "PLL1 LDO", शून्य, "PLL1 LDO ENABLE" पूर्ण,
	अणु "PLL1", शून्य, "PLL1 LDO" पूर्ण,

	अणु "Stereo1 ADC MIXL", शून्य, "Sto1 ADC MIXL" पूर्ण,
	अणु "Stereo1 ADC MIXR", शून्य, "Sto1 ADC MIXR" पूर्ण,

	अणु "Stereo1 ADC MIX", शून्य, "Stereo1 ADC MIXL" पूर्ण,
	अणु "Stereo1 ADC MIX", शून्य, "Stereo1 ADC MIXR" पूर्ण,
	अणु "Stereo1 ADC MIX", शून्य, "adc stereo1 filter" पूर्ण,
	अणु "adc stereo1 filter", शून्य, "PLL1", rt5514_is_sys_clk_from_pll पूर्ण,
	अणु "adc stereo1 filter", शून्य, "ASRC AD1", rt5514_i2s_use_asrc पूर्ण,

	अणु "Stereo2 DMIC Mux", "DMIC1", "DMIC1" पूर्ण,
	अणु "Stereo2 DMIC Mux", "DMIC2", "DMIC2" पूर्ण,

	अणु "Sto2 ADC MIXL", "DMIC Switch", "Stereo2 DMIC Mux" पूर्ण,
	अणु "Sto2 ADC MIXL", "ADC Switch", "AMICL" पूर्ण,
	अणु "Sto2 ADC MIXR", "DMIC Switch", "Stereo2 DMIC Mux" पूर्ण,
	अणु "Sto2 ADC MIXR", "ADC Switch", "AMICR" पूर्ण,

	अणु "Stereo2 ADC MIXL", शून्य, "Sto2 ADC MIXL" पूर्ण,
	अणु "Stereo2 ADC MIXR", शून्य, "Sto2 ADC MIXR" पूर्ण,

	अणु "Stereo2 ADC MIX", शून्य, "Stereo2 ADC MIXL" पूर्ण,
	अणु "Stereo2 ADC MIX", शून्य, "Stereo2 ADC MIXR" पूर्ण,
	अणु "Stereo2 ADC MIX", शून्य, "adc stereo2 filter" पूर्ण,
	अणु "adc stereo2 filter", शून्य, "PLL1", rt5514_is_sys_clk_from_pll पूर्ण,
	अणु "adc stereo2 filter", शून्य, "ASRC AD2", rt5514_i2s_use_asrc पूर्ण,

	अणु "AIF1TX", शून्य, "Stereo1 ADC MIX"पूर्ण,
	अणु "AIF1TX", शून्य, "Stereo2 ADC MIX"पूर्ण,
पूर्ण;

अटल पूर्णांक rt5514_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5514_priv *rt5514 = snd_soc_component_get_drvdata(component);
	पूर्णांक pre_भाग, bclk_ms, frame_size;
	अचिन्हित पूर्णांक val_len = 0;

	rt5514->lrck = params_rate(params);
	pre_भाग = rl6231_get_clk_info(rt5514->sysclk, rt5514->lrck);
	अगर (pre_भाग < 0) अणु
		dev_err(component->dev, "Unsupported clock setting\n");
		वापस -EINVAL;
	पूर्ण

	frame_size = snd_soc_params_to_frame_size(params);
	अगर (frame_size < 0) अणु
		dev_err(component->dev, "Unsupported frame size: %d\n", frame_size);
		वापस -EINVAL;
	पूर्ण

	bclk_ms = frame_size > 32;
	rt5514->bclk = rt5514->lrck * (32 << bclk_ms);

	dev_dbg(dai->dev, "bclk is %dHz and lrck is %dHz\n",
		rt5514->bclk, rt5514->lrck);
	dev_dbg(dai->dev, "bclk_ms is %d and pre_div is %d for iis %d\n",
				bclk_ms, pre_भाग, dai->id);

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S20_3LE:
		val_len = RT5514_I2S_DL_20;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		val_len = RT5514_I2S_DL_24;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S8:
		val_len = RT5514_I2S_DL_8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(rt5514->regmap, RT5514_I2S_CTRL1, RT5514_I2S_DL_MASK,
		val_len);
	regmap_update_bits(rt5514->regmap, RT5514_CLK_CTRL1,
		RT5514_CLK_AD_ANA1_SEL_MASK,
		(pre_भाग + 1) << RT5514_CLK_AD_ANA1_SEL_SFT);
	regmap_update_bits(rt5514->regmap, RT5514_CLK_CTRL2,
		RT5514_CLK_SYS_DIV_OUT_MASK | RT5514_SEL_ADC_OSR_MASK,
		pre_भाग << RT5514_CLK_SYS_DIV_OUT_SFT |
		pre_भाग << RT5514_SEL_ADC_OSR_SFT);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5514_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5514_priv *rt5514 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;

	हाल SND_SOC_DAIFMT_NB_IF:
		reg_val |= RT5514_I2S_LR_INV;
		अवरोध;

	हाल SND_SOC_DAIFMT_IB_NF:
		reg_val |= RT5514_I2S_BP_INV;
		अवरोध;

	हाल SND_SOC_DAIFMT_IB_IF:
		reg_val |= RT5514_I2S_BP_INV | RT5514_I2S_LR_INV;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;

	हाल SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT5514_I2S_DF_LEFT;
		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT5514_I2S_DF_PCM_A;
		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_B:
		reg_val |= RT5514_I2S_DF_PCM_B;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(rt5514->regmap, RT5514_I2S_CTRL1,
		RT5514_I2S_DF_MASK | RT5514_I2S_BP_MASK | RT5514_I2S_LR_MASK,
		reg_val);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5514_set_dai_sysclk(काष्ठा snd_soc_dai *dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5514_priv *rt5514 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;

	अगर (freq == rt5514->sysclk && clk_id == rt5514->sysclk_src)
		वापस 0;

	चयन (clk_id) अणु
	हाल RT5514_SCLK_S_MCLK:
		reg_val |= RT5514_CLK_SYS_PRE_SEL_MCLK;
		अवरोध;

	हाल RT5514_SCLK_S_PLL1:
		reg_val |= RT5514_CLK_SYS_PRE_SEL_PLL;
		अवरोध;

	शेष:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(rt5514->regmap, RT5514_CLK_CTRL2,
		RT5514_CLK_SYS_PRE_SEL_MASK, reg_val);

	rt5514->sysclk = freq;
	rt5514->sysclk_src = clk_id;

	dev_dbg(dai->dev, "Sysclk is %dHz and clock id is %d\n", freq, clk_id);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5514_set_dai_pll(काष्ठा snd_soc_dai *dai, पूर्णांक pll_id, पूर्णांक source,
			अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5514_priv *rt5514 = snd_soc_component_get_drvdata(component);
	काष्ठा rl6231_pll_code pll_code;
	पूर्णांक ret;

	अगर (!freq_in || !freq_out) अणु
		dev_dbg(component->dev, "PLL disabled\n");

		rt5514->pll_in = 0;
		rt5514->pll_out = 0;
		regmap_update_bits(rt5514->regmap, RT5514_CLK_CTRL2,
			RT5514_CLK_SYS_PRE_SEL_MASK,
			RT5514_CLK_SYS_PRE_SEL_MCLK);

		वापस 0;
	पूर्ण

	अगर (source == rt5514->pll_src && freq_in == rt5514->pll_in &&
	    freq_out == rt5514->pll_out)
		वापस 0;

	चयन (source) अणु
	हाल RT5514_PLL1_S_MCLK:
		regmap_update_bits(rt5514->regmap, RT5514_PLL_SOURCE_CTRL,
			RT5514_PLL_1_SEL_MASK, RT5514_PLL_1_SEL_MCLK);
		अवरोध;

	हाल RT5514_PLL1_S_BCLK:
		regmap_update_bits(rt5514->regmap, RT5514_PLL_SOURCE_CTRL,
			RT5514_PLL_1_SEL_MASK, RT5514_PLL_1_SEL_SCLK);
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

	regmap_ग_लिखो(rt5514->regmap, RT5514_ANA_CTRL_PLL1_1,
		pll_code.k_code << RT5514_PLL_K_SFT |
		pll_code.n_code << RT5514_PLL_N_SFT |
		(pll_code.m_bp ? 0 : pll_code.m_code) << RT5514_PLL_M_SFT);
	regmap_update_bits(rt5514->regmap, RT5514_ANA_CTRL_PLL1_2,
		RT5514_PLL_M_BP, pll_code.m_bp << RT5514_PLL_M_BP_SFT);

	rt5514->pll_in = freq_in;
	rt5514->pll_out = freq_out;
	rt5514->pll_src = source;

	वापस 0;
पूर्ण

अटल पूर्णांक rt5514_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
			अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt5514_priv *rt5514 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val = 0, val2 = 0;

	अगर (rx_mask || tx_mask)
		val |= RT5514_TDM_MODE;

	चयन (tx_mask) अणु
	हाल 0x3:
		val2 |= RT5514_TDM_DOCKING_MODE | RT5514_TDM_DOCKING_VALID_CH2 |
			RT5514_TDM_DOCKING_START_SLOT0;
		अवरोध;

	हाल 0x30:
		val2 |= RT5514_TDM_DOCKING_MODE | RT5514_TDM_DOCKING_VALID_CH2 |
			RT5514_TDM_DOCKING_START_SLOT4;
		अवरोध;

	हाल 0xf:
		val2 |= RT5514_TDM_DOCKING_MODE | RT5514_TDM_DOCKING_VALID_CH4 |
			RT5514_TDM_DOCKING_START_SLOT0;
		अवरोध;

	हाल 0xf0:
		val2 |= RT5514_TDM_DOCKING_MODE | RT5514_TDM_DOCKING_VALID_CH4 |
			RT5514_TDM_DOCKING_START_SLOT4;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण



	चयन (slots) अणु
	हाल 4:
		val |= RT5514_TDMSLOT_SEL_RX_4CH | RT5514_TDMSLOT_SEL_TX_4CH;
		अवरोध;

	हाल 6:
		val |= RT5514_TDMSLOT_SEL_RX_6CH | RT5514_TDMSLOT_SEL_TX_6CH;
		अवरोध;

	हाल 8:
		val |= RT5514_TDMSLOT_SEL_RX_8CH | RT5514_TDMSLOT_SEL_TX_8CH;
		अवरोध;

	हाल 2:
	शेष:
		अवरोध;
	पूर्ण

	चयन (slot_width) अणु
	हाल 20:
		val |= RT5514_CH_LEN_RX_20 | RT5514_CH_LEN_TX_20;
		अवरोध;

	हाल 24:
		val |= RT5514_CH_LEN_RX_24 | RT5514_CH_LEN_TX_24;
		अवरोध;

	हाल 25:
		val |= RT5514_TDM_MODE2;
		अवरोध;

	हाल 32:
		val |= RT5514_CH_LEN_RX_32 | RT5514_CH_LEN_TX_32;
		अवरोध;

	हाल 16:
	शेष:
		अवरोध;
	पूर्ण

	regmap_update_bits(rt5514->regmap, RT5514_I2S_CTRL1, RT5514_TDM_MODE |
		RT5514_TDMSLOT_SEL_RX_MASK | RT5514_TDMSLOT_SEL_TX_MASK |
		RT5514_CH_LEN_RX_MASK | RT5514_CH_LEN_TX_MASK |
		RT5514_TDM_MODE2, val);

	regmap_update_bits(rt5514->regmap, RT5514_I2S_CTRL2,
		RT5514_TDM_DOCKING_MODE | RT5514_TDM_DOCKING_VALID_CH_MASK |
		RT5514_TDM_DOCKING_START_MASK, val2);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5514_set_bias_level(काष्ठा snd_soc_component *component,
			क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा rt5514_priv *rt5514 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		अगर (IS_ERR(rt5514->mclk))
			अवरोध;

		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_ON) अणु
			clk_disable_unprepare(rt5514->mclk);
		पूर्ण अन्यथा अणु
			ret = clk_prepare_enable(rt5514->mclk);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			/*
			 * If the DSP is enabled in start of recording, the DSP
			 * should be disabled, and sync back to normal recording
			 * settings to make sure recording properly.
			 */
			अगर (rt5514->dsp_enabled) अणु
				rt5514->dsp_enabled = 0;
				regmap_multi_reg_ग_लिखो(rt5514->i2c_regmap,
					rt5514_i2c_patch,
					ARRAY_SIZE(rt5514_i2c_patch));
				regcache_mark_dirty(rt5514->regmap);
				regcache_sync(rt5514->regmap);
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5514_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5514_priv *rt5514 = snd_soc_component_get_drvdata(component);
	काष्ठा platक्रमm_device *pdev = container_of(component->dev,
						   काष्ठा platक्रमm_device, dev);

	rt5514->mclk = devm_clk_get(component->dev, "mclk");
	अगर (PTR_ERR(rt5514->mclk) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	अगर (rt5514->pdata.dsp_calib_clk_name) अणु
		rt5514->dsp_calib_clk = devm_clk_get(&pdev->dev,
				rt5514->pdata.dsp_calib_clk_name);
		अगर (PTR_ERR(rt5514->dsp_calib_clk) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
	पूर्ण

	rt5514->component = component;
	rt5514->pll3_cal_value = 0x0078b000;

	वापस 0;
पूर्ण

अटल पूर्णांक rt5514_i2c_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा i2c_client *client = context;
	काष्ठा rt5514_priv *rt5514 = i2c_get_clientdata(client);

	regmap_पढ़ो(rt5514->i2c_regmap, reg | RT5514_DSP_MAPPING, val);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5514_i2c_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा i2c_client *client = context;
	काष्ठा rt5514_priv *rt5514 = i2c_get_clientdata(client);

	regmap_ग_लिखो(rt5514->i2c_regmap, reg | RT5514_DSP_MAPPING, val);

	वापस 0;
पूर्ण

#घोषणा RT5514_STEREO_RATES SNDRV_PCM_RATE_8000_192000
#घोषणा RT5514_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S8)

अटल स्थिर काष्ठा snd_soc_dai_ops rt5514_aअगर_dai_ops = अणु
	.hw_params = rt5514_hw_params,
	.set_fmt = rt5514_set_dai_fmt,
	.set_sysclk = rt5514_set_dai_sysclk,
	.set_pll = rt5514_set_dai_pll,
	.set_tdm_slot = rt5514_set_tdm_slot,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt5514_dai[] = अणु
	अणु
		.name = "rt5514-aif1",
		.id = 0,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 1,
			.channels_max = 4,
			.rates = RT5514_STEREO_RATES,
			.क्रमmats = RT5514_FORMATS,
		पूर्ण,
		.ops = &rt5514_aअगर_dai_ops,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_rt5514 = अणु
	.probe			= rt5514_probe,
	.set_bias_level		= rt5514_set_bias_level,
	.controls		= rt5514_snd_controls,
	.num_controls		= ARRAY_SIZE(rt5514_snd_controls),
	.dapm_widमाला_लो		= rt5514_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(rt5514_dapm_widमाला_लो),
	.dapm_routes		= rt5514_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(rt5514_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt5514_i2c_regmap = अणु
	.name = "i2c",
	.reg_bits = 32,
	.val_bits = 32,

	.पढ़ोable_reg = rt5514_i2c_पढ़ोable_रेजिस्टर,

	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt5514_regmap = अणु
	.reg_bits = 16,
	.val_bits = 32,

	.max_रेजिस्टर = RT5514_VENDOR_ID2,
	.अस्थिर_reg = rt5514_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = rt5514_पढ़ोable_रेजिस्टर,
	.reg_पढ़ो = rt5514_i2c_पढ़ो,
	.reg_ग_लिखो = rt5514_i2c_ग_लिखो,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = rt5514_reg,
	.num_reg_शेषs = ARRAY_SIZE(rt5514_reg),
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id rt5514_i2c_id[] = अणु
	अणु "rt5514", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt5514_i2c_id);

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id rt5514_of_match[] = अणु
	अणु .compatible = "realtek,rt5514", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt5514_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id rt5514_acpi_match[] = अणु
	अणु "10EC5514", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rt5514_acpi_match);
#पूर्ण_अगर

अटल पूर्णांक rt5514_parse_dp(काष्ठा rt5514_priv *rt5514, काष्ठा device *dev)
अणु
	device_property_पढ़ो_u32(dev, "realtek,dmic-init-delay-ms",
		&rt5514->pdata.dmic_init_delay);
	device_property_पढ़ो_string(dev, "realtek,dsp-calib-clk-name",
		&rt5514->pdata.dsp_calib_clk_name);
	device_property_पढ़ो_u32(dev, "realtek,dsp-calib-clk-rate",
		&rt5514->pdata.dsp_calib_clk_rate);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक rt5514_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा rt5514_priv *rt5514 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;

	/*
	 * Add a bogus पढ़ो to aव्योम rt5514's confusion after s2r in हाल it
	 * saw glitches on the i2c lines and thought the other side sent a
	 * start bit.
	 */
	regmap_पढ़ो(rt5514->regmap, RT5514_VENDOR_ID2, &val);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5514_i2c_probe(काष्ठा i2c_client *i2c,
		    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rt5514_platक्रमm_data *pdata = dev_get_platdata(&i2c->dev);
	काष्ठा rt5514_priv *rt5514;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val = ~0;

	rt5514 = devm_kzalloc(&i2c->dev, माप(काष्ठा rt5514_priv),
				GFP_KERNEL);
	अगर (rt5514 == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, rt5514);

	अगर (pdata)
		rt5514->pdata = *pdata;
	अन्यथा
		rt5514_parse_dp(rt5514, &i2c->dev);

	rt5514->i2c_regmap = devm_regmap_init_i2c(i2c, &rt5514_i2c_regmap);
	अगर (IS_ERR(rt5514->i2c_regmap)) अणु
		ret = PTR_ERR(rt5514->i2c_regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	rt5514->regmap = devm_regmap_init(&i2c->dev, शून्य, i2c, &rt5514_regmap);
	अगर (IS_ERR(rt5514->regmap)) अणु
		ret = PTR_ERR(rt5514->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	/*
	 * The rt5514 can get confused अगर the i2c lines glitch together, as
	 * can happen at bootup as regulators are turned off and on.  If it's
	 * in this glitched state the first i2c पढ़ो will fail, so we'll give
	 * it one change to retry.
	 */
	ret = regmap_पढ़ो(rt5514->regmap, RT5514_VENDOR_ID2, &val);
	अगर (ret || val != RT5514_DEVICE_ID)
		ret = regmap_पढ़ो(rt5514->regmap, RT5514_VENDOR_ID2, &val);
	अगर (ret || val != RT5514_DEVICE_ID) अणु
		dev_err(&i2c->dev,
			"Device with ID register %x is not rt5514\n", val);
		वापस -ENODEV;
	पूर्ण

	ret = regmap_multi_reg_ग_लिखो(rt5514->i2c_regmap, rt5514_i2c_patch,
				    ARRAY_SIZE(rt5514_i2c_patch));
	अगर (ret != 0)
		dev_warn(&i2c->dev, "Failed to apply i2c_regmap patch: %d\n",
			ret);

	ret = regmap_रेजिस्टर_patch(rt5514->regmap, rt5514_patch,
				    ARRAY_SIZE(rt5514_patch));
	अगर (ret != 0)
		dev_warn(&i2c->dev, "Failed to apply regmap patch: %d\n", ret);

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_rt5514,
			rt5514_dai, ARRAY_SIZE(rt5514_dai));
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rt5514_i2_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(शून्य, rt5514_i2c_resume)
पूर्ण;

अटल काष्ठा i2c_driver rt5514_i2c_driver = अणु
	.driver = अणु
		.name = "rt5514",
		.acpi_match_table = ACPI_PTR(rt5514_acpi_match),
		.of_match_table = of_match_ptr(rt5514_of_match),
		.pm = &rt5514_i2_pm_ops,
	पूर्ण,
	.probe = rt5514_i2c_probe,
	.id_table = rt5514_i2c_id,
पूर्ण;
module_i2c_driver(rt5514_i2c_driver);

MODULE_DESCRIPTION("ASoC RT5514 driver");
MODULE_AUTHOR("Oder Chiou <oder_chiou@realtek.com>");
MODULE_LICENSE("GPL v2");
