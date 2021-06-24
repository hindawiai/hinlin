<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * NAU88L24 ALSA SoC audio driver
 *
 * Copyright 2016 Nuvoton Technology Corp.
 * Author: John Hsu <KCHSU0@nuvoton.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/acpi.h>
#समावेश <linux/math64.h>
#समावेश <linux/semaphore.h>

#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>

#समावेश "nau8824.h"


अटल पूर्णांक nau8824_config_sysclk(काष्ठा nau8824 *nau8824,
	पूर्णांक clk_id, अचिन्हित पूर्णांक freq);
अटल bool nau8824_is_jack_inserted(काष्ठा nau8824 *nau8824);

/* the ADC threshold of headset */
#घोषणा DMIC_CLK 3072000

/* the ADC threshold of headset */
#घोषणा HEADSET_SARADC_THD 0x80

/* the parameter threshold of FLL */
#घोषणा NAU_FREF_MAX 13500000
#घोषणा NAU_FVCO_MAX 100000000
#घोषणा NAU_FVCO_MIN 90000000

/* scaling क्रम mclk from sysclk_src output */
अटल स्थिर काष्ठा nau8824_fll_attr mclk_src_scaling[] = अणु
	अणु 1, 0x0 पूर्ण,
	अणु 2, 0x2 पूर्ण,
	अणु 4, 0x3 पूर्ण,
	अणु 8, 0x4 पूर्ण,
	अणु 16, 0x5 पूर्ण,
	अणु 32, 0x6 पूर्ण,
	अणु 3, 0x7 पूर्ण,
	अणु 6, 0xa पूर्ण,
	अणु 12, 0xb पूर्ण,
	अणु 24, 0xc पूर्ण,
पूर्ण;

/* ratio क्रम input clk freq */
अटल स्थिर काष्ठा nau8824_fll_attr fll_ratio[] = अणु
	अणु 512000, 0x01 पूर्ण,
	अणु 256000, 0x02 पूर्ण,
	अणु 128000, 0x04 पूर्ण,
	अणु 64000, 0x08 पूर्ण,
	अणु 32000, 0x10 पूर्ण,
	अणु 8000, 0x20 पूर्ण,
	अणु 4000, 0x40 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nau8824_fll_attr fll_pre_scalar[] = अणु
	अणु 1, 0x0 पूर्ण,
	अणु 2, 0x1 पूर्ण,
	अणु 4, 0x2 पूर्ण,
	अणु 8, 0x3 पूर्ण,
पूर्ण;

/* the maximum frequency of CLK_ADC and CLK_DAC */
#घोषणा CLK_DA_AD_MAX 6144000

/* over sampling rate */
अटल स्थिर काष्ठा nau8824_osr_attr osr_dac_sel[] = अणु
	अणु 64, 2 पूर्ण,	/* OSR 64, SRC 1/4 */
	अणु 256, 0 पूर्ण,	/* OSR 256, SRC 1 */
	अणु 128, 1 पूर्ण,	/* OSR 128, SRC 1/2 */
	अणु 0, 0 पूर्ण,
	अणु 32, 3 पूर्ण,	/* OSR 32, SRC 1/8 */
पूर्ण;

अटल स्थिर काष्ठा nau8824_osr_attr osr_adc_sel[] = अणु
	अणु 32, 3 पूर्ण,	/* OSR 32, SRC 1/8 */
	अणु 64, 2 पूर्ण,	/* OSR 64, SRC 1/4 */
	अणु 128, 1 पूर्ण,	/* OSR 128, SRC 1/2 */
	अणु 256, 0 पूर्ण,	/* OSR 256, SRC 1 */
पूर्ण;

अटल स्थिर काष्ठा reg_शेष nau8824_reg_शेषs[] = अणु
	अणु NAU8824_REG_ENA_CTRL, 0x0000 पूर्ण,
	अणु NAU8824_REG_CLK_GATING_ENA, 0x0000 पूर्ण,
	अणु NAU8824_REG_CLK_DIVIDER, 0x0000 पूर्ण,
	अणु NAU8824_REG_FLL1, 0x0000 पूर्ण,
	अणु NAU8824_REG_FLL2, 0x3126 पूर्ण,
	अणु NAU8824_REG_FLL3, 0x0008 पूर्ण,
	अणु NAU8824_REG_FLL4, 0x0010 पूर्ण,
	अणु NAU8824_REG_FLL5, 0xC000 पूर्ण,
	अणु NAU8824_REG_FLL6, 0x6000 पूर्ण,
	अणु NAU8824_REG_FLL_VCO_RSV, 0xF13C पूर्ण,
	अणु NAU8824_REG_JACK_DET_CTRL, 0x0000 पूर्ण,
	अणु NAU8824_REG_INTERRUPT_SETTING_1, 0x0000 पूर्ण,
	अणु NAU8824_REG_IRQ, 0x0000 पूर्ण,
	अणु NAU8824_REG_CLEAR_INT_REG, 0x0000 पूर्ण,
	अणु NAU8824_REG_INTERRUPT_SETTING, 0x1000 पूर्ण,
	अणु NAU8824_REG_SAR_ADC, 0x0015 पूर्ण,
	अणु NAU8824_REG_VDET_COEFFICIENT, 0x0110 पूर्ण,
	अणु NAU8824_REG_VDET_THRESHOLD_1, 0x0000 पूर्ण,
	अणु NAU8824_REG_VDET_THRESHOLD_2, 0x0000 पूर्ण,
	अणु NAU8824_REG_VDET_THRESHOLD_3, 0x0000 पूर्ण,
	अणु NAU8824_REG_VDET_THRESHOLD_4, 0x0000 पूर्ण,
	अणु NAU8824_REG_GPIO_SEL, 0x0000 पूर्ण,
	अणु NAU8824_REG_PORT0_I2S_PCM_CTRL_1, 0x000B पूर्ण,
	अणु NAU8824_REG_PORT0_I2S_PCM_CTRL_2, 0x0010 पूर्ण,
	अणु NAU8824_REG_PORT0_LEFT_TIME_SLOT, 0x0000 पूर्ण,
	अणु NAU8824_REG_PORT0_RIGHT_TIME_SLOT, 0x0000 पूर्ण,
	अणु NAU8824_REG_TDM_CTRL, 0x0000 पूर्ण,
	अणु NAU8824_REG_ADC_HPF_FILTER, 0x0000 पूर्ण,
	अणु NAU8824_REG_ADC_FILTER_CTRL, 0x0002 पूर्ण,
	अणु NAU8824_REG_DAC_FILTER_CTRL_1, 0x0000 पूर्ण,
	अणु NAU8824_REG_DAC_FILTER_CTRL_2, 0x0000 पूर्ण,
	अणु NAU8824_REG_NOTCH_FILTER_1, 0x0000 पूर्ण,
	अणु NAU8824_REG_NOTCH_FILTER_2, 0x0000 पूर्ण,
	अणु NAU8824_REG_EQ1_LOW, 0x112C पूर्ण,
	अणु NAU8824_REG_EQ2_EQ3, 0x2C2C पूर्ण,
	अणु NAU8824_REG_EQ4_EQ5, 0x2C2C पूर्ण,
	अणु NAU8824_REG_ADC_CH0_DGAIN_CTRL, 0x0100 पूर्ण,
	अणु NAU8824_REG_ADC_CH1_DGAIN_CTRL, 0x0100 पूर्ण,
	अणु NAU8824_REG_ADC_CH2_DGAIN_CTRL, 0x0100 पूर्ण,
	अणु NAU8824_REG_ADC_CH3_DGAIN_CTRL, 0x0100 पूर्ण,
	अणु NAU8824_REG_DAC_MUTE_CTRL, 0x0000 पूर्ण,
	अणु NAU8824_REG_DAC_CH0_DGAIN_CTRL, 0x0100 पूर्ण,
	अणु NAU8824_REG_DAC_CH1_DGAIN_CTRL, 0x0100 पूर्ण,
	अणु NAU8824_REG_ADC_TO_DAC_ST, 0x0000 पूर्ण,
	अणु NAU8824_REG_DRC_KNEE_IP12_ADC_CH01, 0x1486 पूर्ण,
	अणु NAU8824_REG_DRC_KNEE_IP34_ADC_CH01, 0x0F12 पूर्ण,
	अणु NAU8824_REG_DRC_SLOPE_ADC_CH01, 0x25FF पूर्ण,
	अणु NAU8824_REG_DRC_ATKDCY_ADC_CH01, 0x3457 पूर्ण,
	अणु NAU8824_REG_DRC_KNEE_IP12_ADC_CH23, 0x1486 पूर्ण,
	अणु NAU8824_REG_DRC_KNEE_IP34_ADC_CH23, 0x0F12 पूर्ण,
	अणु NAU8824_REG_DRC_SLOPE_ADC_CH23, 0x25FF पूर्ण,
	अणु NAU8824_REG_DRC_ATKDCY_ADC_CH23, 0x3457 पूर्ण,
	अणु NAU8824_REG_DRC_GAINL_ADC0, 0x0200 पूर्ण,
	अणु NAU8824_REG_DRC_GAINL_ADC1, 0x0200 पूर्ण,
	अणु NAU8824_REG_DRC_GAINL_ADC2, 0x0200 पूर्ण,
	अणु NAU8824_REG_DRC_GAINL_ADC3, 0x0200 पूर्ण,
	अणु NAU8824_REG_DRC_KNEE_IP12_DAC, 0x1486 पूर्ण,
	अणु NAU8824_REG_DRC_KNEE_IP34_DAC, 0x0F12 पूर्ण,
	अणु NAU8824_REG_DRC_SLOPE_DAC, 0x25F9 पूर्ण,
	अणु NAU8824_REG_DRC_ATKDCY_DAC, 0x3457 पूर्ण,
	अणु NAU8824_REG_DRC_GAIN_DAC_CH0, 0x0200 पूर्ण,
	अणु NAU8824_REG_DRC_GAIN_DAC_CH1, 0x0200 पूर्ण,
	अणु NAU8824_REG_MODE, 0x0000 पूर्ण,
	अणु NAU8824_REG_MODE1, 0x0000 पूर्ण,
	अणु NAU8824_REG_MODE2, 0x0000 पूर्ण,
	अणु NAU8824_REG_CLASSG, 0x0000 पूर्ण,
	अणु NAU8824_REG_OTP_EFUSE, 0x0000 पूर्ण,
	अणु NAU8824_REG_OTPDOUT_1, 0x0000 पूर्ण,
	अणु NAU8824_REG_OTPDOUT_2, 0x0000 पूर्ण,
	अणु NAU8824_REG_MISC_CTRL, 0x0000 पूर्ण,
	अणु NAU8824_REG_I2C_TIMEOUT, 0xEFFF पूर्ण,
	अणु NAU8824_REG_TEST_MODE, 0x0000 पूर्ण,
	अणु NAU8824_REG_I2C_DEVICE_ID, 0x1AF1 पूर्ण,
	अणु NAU8824_REG_SAR_ADC_DATA_OUT, 0x00FF पूर्ण,
	अणु NAU8824_REG_BIAS_ADJ, 0x0000 पूर्ण,
	अणु NAU8824_REG_PGA_GAIN, 0x0000 पूर्ण,
	अणु NAU8824_REG_TRIM_SETTINGS, 0x0000 पूर्ण,
	अणु NAU8824_REG_ANALOG_CONTROL_1, 0x0000 पूर्ण,
	अणु NAU8824_REG_ANALOG_CONTROL_2, 0x0000 पूर्ण,
	अणु NAU8824_REG_ENABLE_LO, 0x0000 पूर्ण,
	अणु NAU8824_REG_GAIN_LO, 0x0000 पूर्ण,
	अणु NAU8824_REG_CLASSD_GAIN_1, 0x0000 पूर्ण,
	अणु NAU8824_REG_CLASSD_GAIN_2, 0x0000 पूर्ण,
	अणु NAU8824_REG_ANALOG_ADC_1, 0x0011 पूर्ण,
	अणु NAU8824_REG_ANALOG_ADC_2, 0x0020 पूर्ण,
	अणु NAU8824_REG_RDAC, 0x0008 पूर्ण,
	अणु NAU8824_REG_MIC_BIAS, 0x0006 पूर्ण,
	अणु NAU8824_REG_HS_VOLUME_CONTROL, 0x0000 पूर्ण,
	अणु NAU8824_REG_BOOST, 0x0000 पूर्ण,
	अणु NAU8824_REG_FEPGA, 0x0000 पूर्ण,
	अणु NAU8824_REG_FEPGA_II, 0x0000 पूर्ण,
	अणु NAU8824_REG_FEPGA_SE, 0x0000 पूर्ण,
	अणु NAU8824_REG_FEPGA_ATTENUATION, 0x0000 पूर्ण,
	अणु NAU8824_REG_ATT_PORT0, 0x0000 पूर्ण,
	अणु NAU8824_REG_ATT_PORT1, 0x0000 पूर्ण,
	अणु NAU8824_REG_POWER_UP_CONTROL, 0x0000 पूर्ण,
	अणु NAU8824_REG_CHARGE_PUMP_CONTROL, 0x0300 पूर्ण,
	अणु NAU8824_REG_CHARGE_PUMP_INPUT, 0x0013 पूर्ण,
पूर्ण;

अटल पूर्णांक nau8824_sema_acquire(काष्ठा nau8824 *nau8824, दीर्घ समयout)
अणु
	पूर्णांक ret;

	अगर (समयout) अणु
		ret = करोwn_समयout(&nau8824->jd_sem, समयout);
		अगर (ret < 0)
			dev_warn(nau8824->dev, "Acquire semaphore timeout\n");
	पूर्ण अन्यथा अणु
		ret = करोwn_पूर्णांकerruptible(&nau8824->jd_sem);
		अगर (ret < 0)
			dev_warn(nau8824->dev, "Acquire semaphore fail\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम nau8824_sema_release(काष्ठा nau8824 *nau8824)
अणु
	up(&nau8824->jd_sem);
पूर्ण

अटल bool nau8824_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल NAU8824_REG_ENA_CTRL ... NAU8824_REG_FLL_VCO_RSV:
	हाल NAU8824_REG_JACK_DET_CTRL:
	हाल NAU8824_REG_INTERRUPT_SETTING_1:
	हाल NAU8824_REG_IRQ:
	हाल NAU8824_REG_CLEAR_INT_REG ... NAU8824_REG_VDET_THRESHOLD_4:
	हाल NAU8824_REG_GPIO_SEL:
	हाल NAU8824_REG_PORT0_I2S_PCM_CTRL_1 ... NAU8824_REG_TDM_CTRL:
	हाल NAU8824_REG_ADC_HPF_FILTER ... NAU8824_REG_EQ4_EQ5:
	हाल NAU8824_REG_ADC_CH0_DGAIN_CTRL ... NAU8824_REG_ADC_TO_DAC_ST:
	हाल NAU8824_REG_DRC_KNEE_IP12_ADC_CH01 ... NAU8824_REG_DRC_GAINL_ADC3:
	हाल NAU8824_REG_DRC_KNEE_IP12_DAC ... NAU8824_REG_DRC_GAIN_DAC_CH1:
	हाल NAU8824_REG_CLASSG ... NAU8824_REG_OTP_EFUSE:
	हाल NAU8824_REG_OTPDOUT_1 ... NAU8824_REG_OTPDOUT_2:
	हाल NAU8824_REG_I2C_TIMEOUT:
	हाल NAU8824_REG_I2C_DEVICE_ID ... NAU8824_REG_SAR_ADC_DATA_OUT:
	हाल NAU8824_REG_BIAS_ADJ ... NAU8824_REG_CLASSD_GAIN_2:
	हाल NAU8824_REG_ANALOG_ADC_1 ... NAU8824_REG_ATT_PORT1:
	हाल NAU8824_REG_POWER_UP_CONTROL ... NAU8824_REG_CHARGE_PUMP_INPUT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण

पूर्ण

अटल bool nau8824_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल NAU8824_REG_RESET ... NAU8824_REG_FLL_VCO_RSV:
	हाल NAU8824_REG_JACK_DET_CTRL:
	हाल NAU8824_REG_INTERRUPT_SETTING_1:
	हाल NAU8824_REG_CLEAR_INT_REG ... NAU8824_REG_VDET_THRESHOLD_4:
	हाल NAU8824_REG_GPIO_SEL:
	हाल NAU8824_REG_PORT0_I2S_PCM_CTRL_1 ... NAU8824_REG_TDM_CTRL:
	हाल NAU8824_REG_ADC_HPF_FILTER ... NAU8824_REG_EQ4_EQ5:
	हाल NAU8824_REG_ADC_CH0_DGAIN_CTRL ... NAU8824_REG_ADC_TO_DAC_ST:
	हाल NAU8824_REG_DRC_KNEE_IP12_ADC_CH01:
	हाल NAU8824_REG_DRC_KNEE_IP34_ADC_CH01:
	हाल NAU8824_REG_DRC_SLOPE_ADC_CH01:
	हाल NAU8824_REG_DRC_ATKDCY_ADC_CH01:
	हाल NAU8824_REG_DRC_KNEE_IP12_ADC_CH23:
	हाल NAU8824_REG_DRC_KNEE_IP34_ADC_CH23:
	हाल NAU8824_REG_DRC_SLOPE_ADC_CH23:
	हाल NAU8824_REG_DRC_ATKDCY_ADC_CH23:
	हाल NAU8824_REG_DRC_KNEE_IP12_DAC ... NAU8824_REG_DRC_ATKDCY_DAC:
	हाल NAU8824_REG_CLASSG ... NAU8824_REG_OTP_EFUSE:
	हाल NAU8824_REG_I2C_TIMEOUT:
	हाल NAU8824_REG_BIAS_ADJ ... NAU8824_REG_CLASSD_GAIN_2:
	हाल NAU8824_REG_ANALOG_ADC_1 ... NAU8824_REG_ATT_PORT1:
	हाल NAU8824_REG_POWER_UP_CONTROL ... NAU8824_REG_CHARGE_PUMP_CONTROL:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool nau8824_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल NAU8824_REG_RESET:
	हाल NAU8824_REG_IRQ ... NAU8824_REG_CLEAR_INT_REG:
	हाल NAU8824_REG_DRC_GAINL_ADC0 ... NAU8824_REG_DRC_GAINL_ADC3:
	हाल NAU8824_REG_DRC_GAIN_DAC_CH0 ... NAU8824_REG_DRC_GAIN_DAC_CH1:
	हाल NAU8824_REG_OTPDOUT_1 ... NAU8824_REG_OTPDOUT_2:
	हाल NAU8824_REG_I2C_DEVICE_ID ... NAU8824_REG_SAR_ADC_DATA_OUT:
	हाल NAU8824_REG_CHARGE_PUMP_INPUT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर * स्थिर nau8824_companding[] = अणु
	"Off", "NC", "u-law", "A-law" पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत nau8824_companding_adc_क्रमागत =
	SOC_ENUM_SINGLE(NAU8824_REG_PORT0_I2S_PCM_CTRL_1, 12,
		ARRAY_SIZE(nau8824_companding), nau8824_companding);

अटल स्थिर काष्ठा soc_क्रमागत nau8824_companding_dac_क्रमागत =
	SOC_ENUM_SINGLE(NAU8824_REG_PORT0_I2S_PCM_CTRL_1, 14,
		ARRAY_SIZE(nau8824_companding), nau8824_companding);

अटल स्थिर अक्षर * स्थिर nau8824_adc_decimation[] = अणु
	"32", "64", "128", "256" पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत nau8824_adc_decimation_क्रमागत =
	SOC_ENUM_SINGLE(NAU8824_REG_ADC_FILTER_CTRL, 0,
		ARRAY_SIZE(nau8824_adc_decimation), nau8824_adc_decimation);

अटल स्थिर अक्षर * स्थिर nau8824_dac_oversampl[] = अणु
	"64", "256", "128", "", "32" पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत nau8824_dac_oversampl_क्रमागत =
	SOC_ENUM_SINGLE(NAU8824_REG_DAC_FILTER_CTRL_1, 0,
		ARRAY_SIZE(nau8824_dac_oversampl), nau8824_dac_oversampl);

अटल स्थिर अक्षर * स्थिर nau8824_input_channel[] = अणु
	"Input CH0", "Input CH1", "Input CH2", "Input CH3" पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत nau8824_adc_ch0_क्रमागत =
	SOC_ENUM_SINGLE(NAU8824_REG_ADC_CH0_DGAIN_CTRL, 9,
		ARRAY_SIZE(nau8824_input_channel), nau8824_input_channel);

अटल स्थिर काष्ठा soc_क्रमागत nau8824_adc_ch1_क्रमागत =
	SOC_ENUM_SINGLE(NAU8824_REG_ADC_CH1_DGAIN_CTRL, 9,
		ARRAY_SIZE(nau8824_input_channel), nau8824_input_channel);

अटल स्थिर काष्ठा soc_क्रमागत nau8824_adc_ch2_क्रमागत =
	SOC_ENUM_SINGLE(NAU8824_REG_ADC_CH2_DGAIN_CTRL, 9,
		ARRAY_SIZE(nau8824_input_channel), nau8824_input_channel);

अटल स्थिर काष्ठा soc_क्रमागत nau8824_adc_ch3_क्रमागत =
	SOC_ENUM_SINGLE(NAU8824_REG_ADC_CH3_DGAIN_CTRL, 9,
		ARRAY_SIZE(nau8824_input_channel), nau8824_input_channel);

अटल स्थिर अक्षर * स्थिर nau8824_tdm_slot[] = अणु
	"Slot 0", "Slot 1", "Slot 2", "Slot 3" पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत nau8824_dac_left_sel_क्रमागत =
	SOC_ENUM_SINGLE(NAU8824_REG_TDM_CTRL, 6,
		ARRAY_SIZE(nau8824_tdm_slot), nau8824_tdm_slot);

अटल स्थिर काष्ठा soc_क्रमागत nau8824_dac_right_sel_क्रमागत =
	SOC_ENUM_SINGLE(NAU8824_REG_TDM_CTRL, 4,
		ARRAY_SIZE(nau8824_tdm_slot), nau8824_tdm_slot);

अटल स्थिर DECLARE_TLV_DB_MINMAX_MUTE(spk_vol_tlv, 0, 2400);
अटल स्थिर DECLARE_TLV_DB_MINMAX(hp_vol_tlv, -3000, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(mic_vol_tlv, 0, 200, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(dmic_vol_tlv, -12800, 50, 0);

अटल स्थिर काष्ठा snd_kcontrol_new nau8824_snd_controls[] = अणु
	SOC_ENUM("ADC Companding", nau8824_companding_adc_क्रमागत),
	SOC_ENUM("DAC Companding", nau8824_companding_dac_क्रमागत),

	SOC_ENUM("ADC Decimation Rate", nau8824_adc_decimation_क्रमागत),
	SOC_ENUM("DAC Oversampling Rate", nau8824_dac_oversampl_क्रमागत),

	SOC_SINGLE_TLV("Speaker Right DACR Volume",
		NAU8824_REG_CLASSD_GAIN_1, 8, 0x1f, 0, spk_vol_tlv),
	SOC_SINGLE_TLV("Speaker Left DACL Volume",
		NAU8824_REG_CLASSD_GAIN_2, 0, 0x1f, 0, spk_vol_tlv),
	SOC_SINGLE_TLV("Speaker Left DACR Volume",
		NAU8824_REG_CLASSD_GAIN_1, 0, 0x1f, 0, spk_vol_tlv),
	SOC_SINGLE_TLV("Speaker Right DACL Volume",
		NAU8824_REG_CLASSD_GAIN_2, 8, 0x1f, 0, spk_vol_tlv),

	SOC_SINGLE_TLV("Headphone Right DACR Volume",
		NAU8824_REG_ATT_PORT0, 8, 0x1f, 0, hp_vol_tlv),
	SOC_SINGLE_TLV("Headphone Left DACL Volume",
		NAU8824_REG_ATT_PORT0, 0, 0x1f, 0, hp_vol_tlv),
	SOC_SINGLE_TLV("Headphone Right DACL Volume",
		NAU8824_REG_ATT_PORT1, 8, 0x1f, 0, hp_vol_tlv),
	SOC_SINGLE_TLV("Headphone Left DACR Volume",
		NAU8824_REG_ATT_PORT1, 0, 0x1f, 0, hp_vol_tlv),

	SOC_SINGLE_TLV("MIC1 Volume", NAU8824_REG_FEPGA_II,
		NAU8824_FEPGA_GAINL_SFT, 0x12, 0, mic_vol_tlv),
	SOC_SINGLE_TLV("MIC2 Volume", NAU8824_REG_FEPGA_II,
		NAU8824_FEPGA_GAINR_SFT, 0x12, 0, mic_vol_tlv),

	SOC_SINGLE_TLV("DMIC1 Volume", NAU8824_REG_ADC_CH0_DGAIN_CTRL,
		0, 0x164, 0, dmic_vol_tlv),
	SOC_SINGLE_TLV("DMIC2 Volume", NAU8824_REG_ADC_CH1_DGAIN_CTRL,
		0, 0x164, 0, dmic_vol_tlv),
	SOC_SINGLE_TLV("DMIC3 Volume", NAU8824_REG_ADC_CH2_DGAIN_CTRL,
		0, 0x164, 0, dmic_vol_tlv),
	SOC_SINGLE_TLV("DMIC4 Volume", NAU8824_REG_ADC_CH3_DGAIN_CTRL,
		0, 0x164, 0, dmic_vol_tlv),

	SOC_ENUM("ADC CH0 Select", nau8824_adc_ch0_क्रमागत),
	SOC_ENUM("ADC CH1 Select", nau8824_adc_ch1_क्रमागत),
	SOC_ENUM("ADC CH2 Select", nau8824_adc_ch2_क्रमागत),
	SOC_ENUM("ADC CH3 Select", nau8824_adc_ch3_क्रमागत),

	SOC_SINGLE("ADC CH0 TX Switch", NAU8824_REG_TDM_CTRL, 0, 1, 0),
	SOC_SINGLE("ADC CH1 TX Switch", NAU8824_REG_TDM_CTRL, 1, 1, 0),
	SOC_SINGLE("ADC CH2 TX Switch", NAU8824_REG_TDM_CTRL, 2, 1, 0),
	SOC_SINGLE("ADC CH3 TX Switch", NAU8824_REG_TDM_CTRL, 3, 1, 0),

	SOC_ENUM("DACL Channel Source", nau8824_dac_left_sel_क्रमागत),
	SOC_ENUM("DACR Channel Source", nau8824_dac_right_sel_क्रमागत),

	SOC_SINGLE("DACL LR Mix", NAU8824_REG_DAC_MUTE_CTRL, 0, 1, 0),
	SOC_SINGLE("DACR LR Mix", NAU8824_REG_DAC_MUTE_CTRL, 1, 1, 0),

	SOC_SINGLE("THD for key media",
		NAU8824_REG_VDET_THRESHOLD_1, 8, 0xff, 0),
	SOC_SINGLE("THD for key voice command",
		NAU8824_REG_VDET_THRESHOLD_1, 0, 0xff, 0),
	SOC_SINGLE("THD for key volume up",
		NAU8824_REG_VDET_THRESHOLD_2, 8, 0xff, 0),
	SOC_SINGLE("THD for key volume down",
		NAU8824_REG_VDET_THRESHOLD_2, 0, 0xff, 0),
पूर्ण;

अटल पूर्णांक nau8824_output_dac_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा nau8824 *nau8824 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Disables the TESTDAC to let DAC संकेत pass through. */
		regmap_update_bits(nau8824->regmap, NAU8824_REG_ENABLE_LO,
			NAU8824_TEST_DAC_EN, 0);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		regmap_update_bits(nau8824->regmap, NAU8824_REG_ENABLE_LO,
			NAU8824_TEST_DAC_EN, NAU8824_TEST_DAC_EN);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nau8824_spk_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा nau8824 *nau8824 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		regmap_update_bits(nau8824->regmap,
			NAU8824_REG_ANALOG_CONTROL_2,
			NAU8824_CLASSD_CLAMP_DIS, NAU8824_CLASSD_CLAMP_DIS);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		regmap_update_bits(nau8824->regmap,
			NAU8824_REG_ANALOG_CONTROL_2,
			NAU8824_CLASSD_CLAMP_DIS, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nau8824_pump_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा nau8824 *nau8824 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* Prevent startup click by letting अक्षरge pump to ramp up */
		msleep(10);
		regmap_update_bits(nau8824->regmap,
			NAU8824_REG_CHARGE_PUMP_CONTROL,
			NAU8824_JAMNODCLOW, NAU8824_JAMNODCLOW);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_update_bits(nau8824->regmap,
			NAU8824_REG_CHARGE_PUMP_CONTROL,
			NAU8824_JAMNODCLOW, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक प्रणाली_घड़ी_control(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *k, पूर्णांक  event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा nau8824 *nau8824 = snd_soc_component_get_drvdata(component);
	काष्ठा regmap *regmap = nau8824->regmap;
	अचिन्हित पूर्णांक value;
	bool clk_fll, error;

	अगर (SND_SOC_DAPM_EVENT_OFF(event)) अणु
		dev_dbg(nau8824->dev, "system clock control : POWER OFF\n");
		/* Set घड़ी source to disable or पूर्णांकernal घड़ी beक्रमe the
		 * playback or capture end. Codec needs घड़ी क्रम Jack
		 * detection and button press अगर jack inserted; otherwise,
		 * the घड़ी should be बंदd.
		 */
		अगर (nau8824_is_jack_inserted(nau8824)) अणु
			nau8824_config_sysclk(nau8824,
				NAU8824_CLK_INTERNAL, 0);
		पूर्ण अन्यथा अणु
			nau8824_config_sysclk(nau8824, NAU8824_CLK_DIS, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(nau8824->dev, "system clock control : POWER ON\n");
		/* Check the घड़ी source setting is proper or not
		 * no matter the source is from FLL or MCLK.
		 */
		regmap_पढ़ो(regmap, NAU8824_REG_FLL1, &value);
		clk_fll = value & NAU8824_FLL_RATIO_MASK;
		/* It's error to use पूर्णांकernal घड़ी when playback */
		regmap_पढ़ो(regmap, NAU8824_REG_FLL6, &value);
		error = value & NAU8824_DCO_EN;
		अगर (!error) अणु
			/* Check error depending on source is FLL or MCLK. */
			regmap_पढ़ो(regmap, NAU8824_REG_CLK_DIVIDER, &value);
			अगर (clk_fll)
				error = !(value & NAU8824_CLK_SRC_VCO);
			अन्यथा
				error = value & NAU8824_CLK_SRC_VCO;
		पूर्ण
		/* Recover the घड़ी source setting अगर error. */
		अगर (error) अणु
			अगर (clk_fll) अणु
				regmap_update_bits(regmap,
					NAU8824_REG_FLL6, NAU8824_DCO_EN, 0);
				regmap_update_bits(regmap,
					NAU8824_REG_CLK_DIVIDER,
					NAU8824_CLK_SRC_MASK,
					NAU8824_CLK_SRC_VCO);
			पूर्ण अन्यथा अणु
				nau8824_config_sysclk(nau8824,
					NAU8824_CLK_MCLK, 0);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dmic_घड़ी_control(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *k, पूर्णांक  event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा nau8824 *nau8824 = snd_soc_component_get_drvdata(component);
	पूर्णांक src;

	/* The DMIC घड़ी is gotten from प्रणाली घड़ी (256fs) भागided by
	 * DMIC_SRC (1, 2, 4, 8, 16, 32). The घड़ी has to be equal or
	 * less than 3.072 MHz.
	 */
	क्रम (src = 0; src < 5; src++) अणु
		अगर ((0x1 << (8 - src)) * nau8824->fs <= DMIC_CLK)
			अवरोध;
	पूर्ण
	dev_dbg(nau8824->dev, "dmic src %d for mclk %d\n", src, nau8824->fs * 256);
	regmap_update_bits(nau8824->regmap, NAU8824_REG_CLK_DIVIDER,
		NAU8824_CLK_DMIC_SRC_MASK, (src << NAU8824_CLK_DMIC_SRC_SFT));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new nau8824_adc_ch0_dmic =
	SOC_DAPM_SINGLE("Switch", NAU8824_REG_ENA_CTRL,
		NAU8824_ADC_CH0_DMIC_SFT, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new nau8824_adc_ch1_dmic =
	SOC_DAPM_SINGLE("Switch", NAU8824_REG_ENA_CTRL,
		NAU8824_ADC_CH1_DMIC_SFT, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new nau8824_adc_ch2_dmic =
	SOC_DAPM_SINGLE("Switch", NAU8824_REG_ENA_CTRL,
		NAU8824_ADC_CH2_DMIC_SFT, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new nau8824_adc_ch3_dmic =
	SOC_DAPM_SINGLE("Switch", NAU8824_REG_ENA_CTRL,
		NAU8824_ADC_CH3_DMIC_SFT, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new nau8824_adc_left_mixer[] = अणु
	SOC_DAPM_SINGLE("MIC Switch", NAU8824_REG_FEPGA,
		NAU8824_FEPGA_MODEL_MIC1_SFT, 1, 0),
	SOC_DAPM_SINGLE("HSMIC Switch", NAU8824_REG_FEPGA,
		NAU8824_FEPGA_MODEL_HSMIC_SFT, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new nau8824_adc_right_mixer[] = अणु
	SOC_DAPM_SINGLE("MIC Switch", NAU8824_REG_FEPGA,
		NAU8824_FEPGA_MODER_MIC2_SFT, 1, 0),
	SOC_DAPM_SINGLE("HSMIC Switch", NAU8824_REG_FEPGA,
		NAU8824_FEPGA_MODER_HSMIC_SFT, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new nau8824_hp_left_mixer[] = अणु
	SOC_DAPM_SINGLE("DAC Right Switch", NAU8824_REG_ENABLE_LO,
		NAU8824_DACR_HPL_EN_SFT, 1, 0),
	SOC_DAPM_SINGLE("DAC Left Switch", NAU8824_REG_ENABLE_LO,
		NAU8824_DACL_HPL_EN_SFT, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new nau8824_hp_right_mixer[] = अणु
	SOC_DAPM_SINGLE("DAC Left Switch", NAU8824_REG_ENABLE_LO,
		NAU8824_DACL_HPR_EN_SFT, 1, 0),
	SOC_DAPM_SINGLE("DAC Right Switch", NAU8824_REG_ENABLE_LO,
		NAU8824_DACR_HPR_EN_SFT, 1, 0),
पूर्ण;

अटल स्थिर अक्षर * स्थिर nau8824_dac_src[] = अणु "DACL", "DACR" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	nau8824_dacl_क्रमागत, NAU8824_REG_DAC_CH0_DGAIN_CTRL,
	NAU8824_DAC_CH0_SEL_SFT, nau8824_dac_src);

अटल SOC_ENUM_SINGLE_DECL(
	nau8824_dacr_क्रमागत, NAU8824_REG_DAC_CH1_DGAIN_CTRL,
	NAU8824_DAC_CH1_SEL_SFT, nau8824_dac_src);

अटल स्थिर काष्ठा snd_kcontrol_new nau8824_dacl_mux =
	SOC_DAPM_ENUM("DACL Source", nau8824_dacl_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new nau8824_dacr_mux =
	SOC_DAPM_ENUM("DACR Source", nau8824_dacr_क्रमागत);


अटल स्थिर काष्ठा snd_soc_dapm_widget nau8824_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("System Clock", SND_SOC_NOPM, 0, 0,
		प्रणाली_घड़ी_control, SND_SOC_DAPM_POST_PMD |
		SND_SOC_DAPM_POST_PMU),

	SND_SOC_DAPM_INPUT("HSMIC1"),
	SND_SOC_DAPM_INPUT("HSMIC2"),
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("DMIC1"),
	SND_SOC_DAPM_INPUT("DMIC2"),
	SND_SOC_DAPM_INPUT("DMIC3"),
	SND_SOC_DAPM_INPUT("DMIC4"),

	SND_SOC_DAPM_SUPPLY("SAR", NAU8824_REG_SAR_ADC,
		NAU8824_SAR_ADC_EN_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MICBIAS", NAU8824_REG_MIC_BIAS,
		NAU8824_MICBIAS_POWERUP_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DMIC12 Power", NAU8824_REG_BIAS_ADJ,
		NAU8824_DMIC1_EN_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DMIC34 Power", NAU8824_REG_BIAS_ADJ,
		NAU8824_DMIC2_EN_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DMIC Clock", SND_SOC_NOPM, 0, 0,
		dmic_घड़ी_control, SND_SOC_DAPM_POST_PMU),

	SND_SOC_DAPM_SWITCH("DMIC1 Enable", SND_SOC_NOPM,
		0, 0, &nau8824_adc_ch0_dmic),
	SND_SOC_DAPM_SWITCH("DMIC2 Enable", SND_SOC_NOPM,
		0, 0, &nau8824_adc_ch1_dmic),
	SND_SOC_DAPM_SWITCH("DMIC3 Enable", SND_SOC_NOPM,
		0, 0, &nau8824_adc_ch2_dmic),
	SND_SOC_DAPM_SWITCH("DMIC4 Enable", SND_SOC_NOPM,
		0, 0, &nau8824_adc_ch3_dmic),

	SND_SOC_DAPM_MIXER("Left ADC", NAU8824_REG_POWER_UP_CONTROL,
		12, 0, nau8824_adc_left_mixer,
		ARRAY_SIZE(nau8824_adc_left_mixer)),
	SND_SOC_DAPM_MIXER("Right ADC", NAU8824_REG_POWER_UP_CONTROL,
		13, 0, nau8824_adc_right_mixer,
		ARRAY_SIZE(nau8824_adc_right_mixer)),

	SND_SOC_DAPM_ADC("ADCL", शून्य, NAU8824_REG_ANALOG_ADC_2,
		NAU8824_ADCL_EN_SFT, 0),
	SND_SOC_DAPM_ADC("ADCR", शून्य, NAU8824_REG_ANALOG_ADC_2,
		NAU8824_ADCR_EN_SFT, 0),

	SND_SOC_DAPM_AIF_OUT("AIFTX", "Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIFRX", "Playback", 0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_DAC("DACL", शून्य, NAU8824_REG_RDAC,
		NAU8824_DACL_EN_SFT, 0),
	SND_SOC_DAPM_SUPPLY("DACL Clock", NAU8824_REG_RDAC,
		NAU8824_DACL_CLK_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_DAC("DACR", शून्य, NAU8824_REG_RDAC,
		NAU8824_DACR_EN_SFT, 0),
	SND_SOC_DAPM_SUPPLY("DACR Clock", NAU8824_REG_RDAC,
		NAU8824_DACR_CLK_SFT, 0, शून्य, 0),

	SND_SOC_DAPM_MUX("DACL Mux", SND_SOC_NOPM, 0, 0, &nau8824_dacl_mux),
	SND_SOC_DAPM_MUX("DACR Mux", SND_SOC_NOPM, 0, 0, &nau8824_dacr_mux),

	SND_SOC_DAPM_PGA_S("Output DACL", 0, NAU8824_REG_CHARGE_PUMP_CONTROL,
		8, 1, nau8824_output_dac_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_S("Output DACR", 0, NAU8824_REG_CHARGE_PUMP_CONTROL,
		9, 1, nau8824_output_dac_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_PGA_S("ClassD", 0, NAU8824_REG_CLASSD_GAIN_1,
		NAU8824_CLASSD_EN_SFT, 0, nau8824_spk_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MIXER("Left Headphone", NAU8824_REG_CLASSG,
		NAU8824_CLASSG_LDAC_EN_SFT, 0, nau8824_hp_left_mixer,
		ARRAY_SIZE(nau8824_hp_left_mixer)),
	SND_SOC_DAPM_MIXER("Right Headphone", NAU8824_REG_CLASSG,
		NAU8824_CLASSG_RDAC_EN_SFT, 0, nau8824_hp_right_mixer,
		ARRAY_SIZE(nau8824_hp_right_mixer)),
	SND_SOC_DAPM_PGA_S("Charge Pump", 1, NAU8824_REG_CHARGE_PUMP_CONTROL,
		NAU8824_CHARGE_PUMP_EN_SFT, 0, nau8824_pump_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_PGA("Output Driver L",
		NAU8824_REG_POWER_UP_CONTROL, 3, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Output Driver R",
		NAU8824_REG_POWER_UP_CONTROL, 2, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Main Driver L",
		NAU8824_REG_POWER_UP_CONTROL, 1, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Main Driver R",
		NAU8824_REG_POWER_UP_CONTROL, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("HP Boost Driver", NAU8824_REG_BOOST,
		NAU8824_HP_BOOST_DIS_SFT, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("Class G", NAU8824_REG_CLASSG,
		NAU8824_CLASSG_EN_SFT, 0, शून्य, 0),

	SND_SOC_DAPM_OUTPUT("SPKOUTL"),
	SND_SOC_DAPM_OUTPUT("SPKOUTR"),
	SND_SOC_DAPM_OUTPUT("HPOL"),
	SND_SOC_DAPM_OUTPUT("HPOR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route nau8824_dapm_routes[] = अणु
	अणु"DMIC1 Enable", "Switch", "DMIC1"पूर्ण,
	अणु"DMIC2 Enable", "Switch", "DMIC2"पूर्ण,
	अणु"DMIC3 Enable", "Switch", "DMIC3"पूर्ण,
	अणु"DMIC4 Enable", "Switch", "DMIC4"पूर्ण,

	अणु"DMIC1", शून्य, "DMIC12 Power"पूर्ण,
	अणु"DMIC2", शून्य, "DMIC12 Power"पूर्ण,
	अणु"DMIC3", शून्य, "DMIC34 Power"पूर्ण,
	अणु"DMIC4", शून्य, "DMIC34 Power"पूर्ण,
	अणु"DMIC12 Power", शून्य, "DMIC Clock"पूर्ण,
	अणु"DMIC34 Power", शून्य, "DMIC Clock"पूर्ण,

	अणु"Left ADC", "MIC Switch", "MIC1"पूर्ण,
	अणु"Left ADC", "HSMIC Switch", "HSMIC1"पूर्ण,
	अणु"Right ADC", "MIC Switch", "MIC2"पूर्ण,
	अणु"Right ADC", "HSMIC Switch", "HSMIC2"पूर्ण,

	अणु"ADCL", शून्य, "Left ADC"पूर्ण,
	अणु"ADCR", शून्य, "Right ADC"पूर्ण,

	अणु"AIFTX", शून्य, "MICBIAS"पूर्ण,
	अणु"AIFTX", शून्य, "ADCL"पूर्ण,
	अणु"AIFTX", शून्य, "ADCR"पूर्ण,
	अणु"AIFTX", शून्य, "DMIC1 Enable"पूर्ण,
	अणु"AIFTX", शून्य, "DMIC2 Enable"पूर्ण,
	अणु"AIFTX", शून्य, "DMIC3 Enable"पूर्ण,
	अणु"AIFTX", शून्य, "DMIC4 Enable"पूर्ण,

	अणु"AIFTX", शून्य, "System Clock"पूर्ण,
	अणु"AIFRX", शून्य, "System Clock"पूर्ण,

	अणु"DACL", शून्य, "AIFRX"पूर्ण,
	अणु"DACL", शून्य, "DACL Clock"पूर्ण,
	अणु"DACR", शून्य, "AIFRX"पूर्ण,
	अणु"DACR", शून्य, "DACR Clock"पूर्ण,

	अणु"DACL Mux", "DACL", "DACL"पूर्ण,
	अणु"DACL Mux", "DACR", "DACR"पूर्ण,
	अणु"DACR Mux", "DACL", "DACL"पूर्ण,
	अणु"DACR Mux", "DACR", "DACR"पूर्ण,

	अणु"Output DACL", शून्य, "DACL Mux"पूर्ण,
	अणु"Output DACR", शून्य, "DACR Mux"पूर्ण,

	अणु"ClassD", शून्य, "Output DACL"पूर्ण,
	अणु"ClassD", शून्य, "Output DACR"पूर्ण,

	अणु"Left Headphone", "DAC Left Switch", "Output DACL"पूर्ण,
	अणु"Left Headphone", "DAC Right Switch", "Output DACR"पूर्ण,
	अणु"Right Headphone", "DAC Left Switch", "Output DACL"पूर्ण,
	अणु"Right Headphone", "DAC Right Switch", "Output DACR"पूर्ण,

	अणु"Charge Pump", शून्य, "Left Headphone"पूर्ण,
	अणु"Charge Pump", शून्य, "Right Headphone"पूर्ण,
	अणु"Output Driver L", शून्य, "Charge Pump"पूर्ण,
	अणु"Output Driver R", शून्य, "Charge Pump"पूर्ण,
	अणु"Main Driver L", शून्य, "Output Driver L"पूर्ण,
	अणु"Main Driver R", शून्य, "Output Driver R"पूर्ण,
	अणु"Class G", शून्य, "Main Driver L"पूर्ण,
	अणु"Class G", शून्य, "Main Driver R"पूर्ण,
	अणु"HP Boost Driver", शून्य, "Class G"पूर्ण,

	अणु"SPKOUTL", शून्य, "ClassD"पूर्ण,
	अणु"SPKOUTR", शून्य, "ClassD"पूर्ण,
	अणु"HPOL", शून्य, "HP Boost Driver"पूर्ण,
	अणु"HPOR", शून्य, "HP Boost Driver"पूर्ण,
पूर्ण;

अटल bool nau8824_is_jack_inserted(काष्ठा nau8824 *nau8824)
अणु
	काष्ठा snd_soc_jack *jack = nau8824->jack;
	bool insert = false;

	अगर (nau8824->irq && jack)
		insert = jack->status & SND_JACK_HEADPHONE;

	वापस insert;
पूर्ण

अटल व्योम nau8824_पूर्णांक_status_clear_all(काष्ठा regmap *regmap)
अणु
	पूर्णांक active_irq, clear_irq, i;

	/* Reset the पूर्णांकrruption status from righपंचांगost bit अगर the corres-
	 * ponding irq event occurs.
	 */
	regmap_पढ़ो(regmap, NAU8824_REG_IRQ, &active_irq);
	क्रम (i = 0; i < NAU8824_REG_DATA_LEN; i++) अणु
		clear_irq = (0x1 << i);
		अगर (active_irq & clear_irq)
			regmap_ग_लिखो(regmap,
				NAU8824_REG_CLEAR_INT_REG, clear_irq);
	पूर्ण
पूर्ण

अटल व्योम nau8824_dapm_disable_pin(काष्ठा nau8824 *nau8824, स्थिर अक्षर *pin)
अणु
	काष्ठा snd_soc_dapm_context *dapm = nau8824->dapm;
	स्थिर अक्षर *prefix = dapm->component->name_prefix;
	अक्षर prefixed_pin[80];

	अगर (prefix) अणु
		snम_लिखो(prefixed_pin, माप(prefixed_pin), "%s %s",
			 prefix, pin);
		snd_soc_dapm_disable_pin(dapm, prefixed_pin);
	पूर्ण अन्यथा अणु
		snd_soc_dapm_disable_pin(dapm, pin);
	पूर्ण
पूर्ण

अटल व्योम nau8824_dapm_enable_pin(काष्ठा nau8824 *nau8824, स्थिर अक्षर *pin)
अणु
	काष्ठा snd_soc_dapm_context *dapm = nau8824->dapm;
	स्थिर अक्षर *prefix = dapm->component->name_prefix;
	अक्षर prefixed_pin[80];

	अगर (prefix) अणु
		snम_लिखो(prefixed_pin, माप(prefixed_pin), "%s %s",
			 prefix, pin);
		snd_soc_dapm_क्रमce_enable_pin(dapm, prefixed_pin);
	पूर्ण अन्यथा अणु
		snd_soc_dapm_क्रमce_enable_pin(dapm, pin);
	पूर्ण
पूर्ण

अटल व्योम nau8824_eject_jack(काष्ठा nau8824 *nau8824)
अणु
	काष्ठा snd_soc_dapm_context *dapm = nau8824->dapm;
	काष्ठा regmap *regmap = nau8824->regmap;

	/* Clear all पूर्णांकerruption status */
	nau8824_पूर्णांक_status_clear_all(regmap);

	nau8824_dapm_disable_pin(nau8824, "SAR");
	nau8824_dapm_disable_pin(nau8824, "MICBIAS");
	snd_soc_dapm_sync(dapm);

	/* Enable the insertion पूर्णांकerruption, disable the ejection
	 * पूर्णांकerruption, and then bypass de-bounce circuit.
	 */
	regmap_update_bits(regmap, NAU8824_REG_INTERRUPT_SETTING,
		NAU8824_IRQ_KEY_RELEASE_DIS | NAU8824_IRQ_KEY_SHORT_PRESS_DIS |
		NAU8824_IRQ_EJECT_DIS | NAU8824_IRQ_INSERT_DIS,
		NAU8824_IRQ_KEY_RELEASE_DIS | NAU8824_IRQ_KEY_SHORT_PRESS_DIS |
		NAU8824_IRQ_EJECT_DIS);
	regmap_update_bits(regmap, NAU8824_REG_INTERRUPT_SETTING_1,
		NAU8824_IRQ_INSERT_EN | NAU8824_IRQ_EJECT_EN,
		NAU8824_IRQ_INSERT_EN);
	regmap_update_bits(regmap, NAU8824_REG_ENA_CTRL,
		NAU8824_JD_SLEEP_MODE, NAU8824_JD_SLEEP_MODE);

	/* Close घड़ी क्रम jack type detection at manual mode */
	अगर (dapm->bias_level < SND_SOC_BIAS_PREPARE)
		nau8824_config_sysclk(nau8824, NAU8824_CLK_DIS, 0);
पूर्ण

अटल व्योम nau8824_jdet_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nau8824 *nau8824 = container_of(
		work, काष्ठा nau8824, jdet_work);
	काष्ठा snd_soc_dapm_context *dapm = nau8824->dapm;
	काष्ठा regmap *regmap = nau8824->regmap;
	पूर्णांक adc_value, event = 0, event_mask = 0;

	nau8824_dapm_enable_pin(nau8824, "MICBIAS");
	nau8824_dapm_enable_pin(nau8824, "SAR");
	snd_soc_dapm_sync(dapm);

	msleep(100);

	regmap_पढ़ो(regmap, NAU8824_REG_SAR_ADC_DATA_OUT, &adc_value);
	adc_value = adc_value & NAU8824_SAR_ADC_DATA_MASK;
	dev_dbg(nau8824->dev, "SAR ADC data 0x%02x\n", adc_value);
	अगर (adc_value < HEADSET_SARADC_THD) अणु
		event |= SND_JACK_HEADPHONE;

		nau8824_dapm_disable_pin(nau8824, "SAR");
		nau8824_dapm_disable_pin(nau8824, "MICBIAS");
		snd_soc_dapm_sync(dapm);
	पूर्ण अन्यथा अणु
		event |= SND_JACK_HEADSET;
	पूर्ण
	event_mask |= SND_JACK_HEADSET;
	snd_soc_jack_report(nau8824->jack, event, event_mask);

	/* Enable लघु key press and release पूर्णांकerruption. */
	regmap_update_bits(regmap, NAU8824_REG_INTERRUPT_SETTING,
		NAU8824_IRQ_KEY_RELEASE_DIS |
		NAU8824_IRQ_KEY_SHORT_PRESS_DIS, 0);

	nau8824_sema_release(nau8824);
पूर्ण

अटल व्योम nau8824_setup_स्वतः_irq(काष्ठा nau8824 *nau8824)
अणु
	काष्ठा regmap *regmap = nau8824->regmap;

	/* Enable jack ejection पूर्णांकerruption. */
	regmap_update_bits(regmap, NAU8824_REG_INTERRUPT_SETTING_1,
		NAU8824_IRQ_INSERT_EN | NAU8824_IRQ_EJECT_EN,
		NAU8824_IRQ_EJECT_EN);
	regmap_update_bits(regmap, NAU8824_REG_INTERRUPT_SETTING,
		NAU8824_IRQ_EJECT_DIS, 0);
	/* Enable पूर्णांकernal VCO needed क्रम पूर्णांकerruptions */
	अगर (nau8824->dapm->bias_level < SND_SOC_BIAS_PREPARE)
		nau8824_config_sysclk(nau8824, NAU8824_CLK_INTERNAL, 0);
	regmap_update_bits(regmap, NAU8824_REG_ENA_CTRL,
		NAU8824_JD_SLEEP_MODE, 0);
पूर्ण

अटल पूर्णांक nau8824_button_decode(पूर्णांक value)
अणु
	पूर्णांक buttons = 0;

	/* The chip supports up to 8 buttons, but ALSA defines
	 * only 6 buttons.
	 */
	अगर (value & BIT(0))
		buttons |= SND_JACK_BTN_0;
	अगर (value & BIT(1))
		buttons |= SND_JACK_BTN_1;
	अगर (value & BIT(2))
		buttons |= SND_JACK_BTN_2;
	अगर (value & BIT(3))
		buttons |= SND_JACK_BTN_3;
	अगर (value & BIT(4))
		buttons |= SND_JACK_BTN_4;
	अगर (value & BIT(5))
		buttons |= SND_JACK_BTN_5;

	वापस buttons;
पूर्ण

#घोषणा NAU8824_BUTTONS (SND_JACK_BTN_0 | SND_JACK_BTN_1 | \
		SND_JACK_BTN_2 | SND_JACK_BTN_3)

अटल irqवापस_t nau8824_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा nau8824 *nau8824 = (काष्ठा nau8824 *)data;
	काष्ठा regmap *regmap = nau8824->regmap;
	पूर्णांक active_irq, clear_irq = 0, event = 0, event_mask = 0;

	अगर (regmap_पढ़ो(regmap, NAU8824_REG_IRQ, &active_irq)) अणु
		dev_err(nau8824->dev, "failed to read irq status\n");
		वापस IRQ_NONE;
	पूर्ण
	dev_dbg(nau8824->dev, "IRQ %x\n", active_irq);

	अगर (active_irq & NAU8824_JACK_EJECTION_DETECTED) अणु
		nau8824_eject_jack(nau8824);
		event_mask |= SND_JACK_HEADSET;
		clear_irq = NAU8824_JACK_EJECTION_DETECTED;
		/* release semaphore held after resume,
		 * and cancel jack detection
		 */
		nau8824_sema_release(nau8824);
		cancel_work_sync(&nau8824->jdet_work);
	पूर्ण अन्यथा अगर (active_irq & NAU8824_KEY_SHORT_PRESS_IRQ) अणु
		पूर्णांक key_status, button_pressed;

		regmap_पढ़ो(regmap, NAU8824_REG_CLEAR_INT_REG,
			&key_status);

		/* lower 8 bits of the रेजिस्टर are क्रम pressed keys */
		button_pressed = nau8824_button_decode(key_status);

		event |= button_pressed;
		dev_dbg(nau8824->dev, "button %x pressed\n", event);
		event_mask |= NAU8824_BUTTONS;
		clear_irq = NAU8824_KEY_SHORT_PRESS_IRQ;
	पूर्ण अन्यथा अगर (active_irq & NAU8824_KEY_RELEASE_IRQ) अणु
		event_mask = NAU8824_BUTTONS;
		clear_irq = NAU8824_KEY_RELEASE_IRQ;
	पूर्ण अन्यथा अगर (active_irq & NAU8824_JACK_INSERTION_DETECTED) अणु
		/* Turn off insertion पूर्णांकerruption at manual mode */
		regmap_update_bits(regmap,
			NAU8824_REG_INTERRUPT_SETTING,
			NAU8824_IRQ_INSERT_DIS,
			NAU8824_IRQ_INSERT_DIS);
		regmap_update_bits(regmap,
			NAU8824_REG_INTERRUPT_SETTING_1,
			NAU8824_IRQ_INSERT_EN, 0);
		/* detect microphone and jack type */
		cancel_work_sync(&nau8824->jdet_work);
		schedule_work(&nau8824->jdet_work);

		/* Enable पूर्णांकerruption क्रम jack type detection at auकरो
		 * mode which can detect microphone and jack type.
		 */
		nau8824_setup_स्वतः_irq(nau8824);
	पूर्ण

	अगर (!clear_irq)
		clear_irq = active_irq;
	/* clears the righपंचांगost पूर्णांकerruption */
	regmap_ग_लिखो(regmap, NAU8824_REG_CLEAR_INT_REG, clear_irq);

	अगर (event_mask)
		snd_soc_jack_report(nau8824->jack, event, event_mask);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक nau8824_घड़ी_check(काष्ठा nau8824 *nau8824,
	पूर्णांक stream, पूर्णांक rate, पूर्णांक osr)
अणु
	पूर्णांक osrate;

	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		अगर (osr >= ARRAY_SIZE(osr_dac_sel))
			वापस -EINVAL;
		osrate = osr_dac_sel[osr].osr;
	पूर्ण अन्यथा अणु
		अगर (osr >= ARRAY_SIZE(osr_adc_sel))
			वापस -EINVAL;
		osrate = osr_adc_sel[osr].osr;
	पूर्ण

	अगर (!osrate || rate * osr > CLK_DA_AD_MAX) अणु
		dev_err(nau8824->dev, "exceed the maximum frequency of CLK_ADC or CLK_DAC\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nau8824_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा nau8824 *nau8824 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val_len = 0, osr, ctrl_val, bclk_fs, bclk_भाग;

	nau8824_sema_acquire(nau8824, HZ);

	/* CLK_DAC or CLK_ADC = OSR * FS
	 * DAC or ADC घड़ी frequency is defined as Over Sampling Rate (OSR)
	 * multiplied by the audio sample rate (Fs). Note that the OSR and Fs
	 * values must be selected such that the maximum frequency is less
	 * than 6.144 MHz.
	 */
	nau8824->fs = params_rate(params);
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		regmap_पढ़ो(nau8824->regmap,
			NAU8824_REG_DAC_FILTER_CTRL_1, &osr);
		osr &= NAU8824_DAC_OVERSAMPLE_MASK;
		अगर (nau8824_घड़ी_check(nau8824, substream->stream,
			nau8824->fs, osr))
			वापस -EINVAL;
		regmap_update_bits(nau8824->regmap, NAU8824_REG_CLK_DIVIDER,
			NAU8824_CLK_DAC_SRC_MASK,
			osr_dac_sel[osr].clk_src << NAU8824_CLK_DAC_SRC_SFT);
	पूर्ण अन्यथा अणु
		regmap_पढ़ो(nau8824->regmap,
			NAU8824_REG_ADC_FILTER_CTRL, &osr);
		osr &= NAU8824_ADC_SYNC_DOWN_MASK;
		अगर (nau8824_घड़ी_check(nau8824, substream->stream,
			nau8824->fs, osr))
			वापस -EINVAL;
		regmap_update_bits(nau8824->regmap, NAU8824_REG_CLK_DIVIDER,
			NAU8824_CLK_ADC_SRC_MASK,
			osr_adc_sel[osr].clk_src << NAU8824_CLK_ADC_SRC_SFT);
	पूर्ण

	/* make BCLK and LRC भागde configuration अगर the codec as master. */
	regmap_पढ़ो(nau8824->regmap,
		NAU8824_REG_PORT0_I2S_PCM_CTRL_2, &ctrl_val);
	अगर (ctrl_val & NAU8824_I2S_MS_MASTER) अणु
		/* get the bclk and fs ratio */
		bclk_fs = snd_soc_params_to_bclk(params) / nau8824->fs;
		अगर (bclk_fs <= 32)
			bclk_भाग = 0x3;
		अन्यथा अगर (bclk_fs <= 64)
			bclk_भाग = 0x2;
		अन्यथा अगर (bclk_fs <= 128)
			bclk_भाग = 0x1;
		अन्यथा अगर (bclk_fs <= 256)
			bclk_भाग = 0;
		अन्यथा
			वापस -EINVAL;
		regmap_update_bits(nau8824->regmap,
			NAU8824_REG_PORT0_I2S_PCM_CTRL_2,
			NAU8824_I2S_LRC_DIV_MASK | NAU8824_I2S_BLK_DIV_MASK,
			(bclk_भाग << NAU8824_I2S_LRC_DIV_SFT) | bclk_भाग);
	पूर्ण

	चयन (params_width(params)) अणु
	हाल 16:
		val_len |= NAU8824_I2S_DL_16;
		अवरोध;
	हाल 20:
		val_len |= NAU8824_I2S_DL_20;
		अवरोध;
	हाल 24:
		val_len |= NAU8824_I2S_DL_24;
		अवरोध;
	हाल 32:
		val_len |= NAU8824_I2S_DL_32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(nau8824->regmap, NAU8824_REG_PORT0_I2S_PCM_CTRL_1,
		NAU8824_I2S_DL_MASK, val_len);

	nau8824_sema_release(nau8824);

	वापस 0;
पूर्ण

अटल पूर्णांक nau8824_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा nau8824 *nau8824 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक ctrl1_val = 0, ctrl2_val = 0;

	nau8824_sema_acquire(nau8824, HZ);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		ctrl2_val |= NAU8824_I2S_MS_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		ctrl1_val |= NAU8824_I2S_BP_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		ctrl1_val |= NAU8824_I2S_DF_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		ctrl1_val |= NAU8824_I2S_DF_LEFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		ctrl1_val |= NAU8824_I2S_DF_RIGTH;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		ctrl1_val |= NAU8824_I2S_DF_PCM_AB;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		ctrl1_val |= NAU8824_I2S_DF_PCM_AB;
		ctrl1_val |= NAU8824_I2S_PCMB_EN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(nau8824->regmap, NAU8824_REG_PORT0_I2S_PCM_CTRL_1,
		NAU8824_I2S_DF_MASK | NAU8824_I2S_BP_MASK |
		NAU8824_I2S_PCMB_EN, ctrl1_val);
	regmap_update_bits(nau8824->regmap, NAU8824_REG_PORT0_I2S_PCM_CTRL_2,
		NAU8824_I2S_MS_MASK, ctrl2_val);

	nau8824_sema_release(nau8824);

	वापस 0;
पूर्ण

/**
 * nau8824_set_tdm_slot - configure DAI TDM.
 * @dai: DAI
 * @tx_mask: Biपंचांगask representing active TX slots. Ex.
 *                 0xf क्रम normal 4 channel TDM.
 *                 0xf0 क्रम shअगरted 4 channel TDM
 * @rx_mask: Biपंचांगask [0:1] representing active DACR RX slots.
 *                 Biपंचांगask [2:3] representing active DACL RX slots.
 *                 00=CH0,01=CH1,10=CH2,11=CH3. Ex.
 *                 0xf क्रम DACL/R selecting TDM CH3.
 *                 0xf0 क्रम DACL/R selecting shअगरted TDM CH3.
 * @slots: Number of slots in use.
 * @slot_width: Width in bits क्रम each slot.
 *
 * Configures a DAI क्रम TDM operation. Only support 4 slots TDM.
 */
अटल पूर्णांक nau8824_set_tdm_slot(काष्ठा snd_soc_dai *dai,
	अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा nau8824 *nau8824 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक tslot_l = 0, ctrl_val = 0;

	अगर (slots > 4 || ((tx_mask & 0xf0) && (tx_mask & 0xf)) ||
		((rx_mask & 0xf0) && (rx_mask & 0xf)) ||
		((rx_mask & 0xf0) && (tx_mask & 0xf)) ||
		((rx_mask & 0xf) && (tx_mask & 0xf0)))
		वापस -EINVAL;

	ctrl_val |= (NAU8824_TDM_MODE | NAU8824_TDM_OFFSET_EN);
	अगर (tx_mask & 0xf0) अणु
		tslot_l = 4 * slot_width;
		ctrl_val |= (tx_mask >> 4);
	पूर्ण अन्यथा अणु
		ctrl_val |= tx_mask;
	पूर्ण
	अगर (rx_mask & 0xf0)
		ctrl_val |= ((rx_mask >> 4) << NAU8824_TDM_DACR_RX_SFT);
	अन्यथा
		ctrl_val |= (rx_mask << NAU8824_TDM_DACR_RX_SFT);

	regmap_update_bits(nau8824->regmap, NAU8824_REG_TDM_CTRL,
		NAU8824_TDM_MODE | NAU8824_TDM_OFFSET_EN |
		NAU8824_TDM_DACL_RX_MASK | NAU8824_TDM_DACR_RX_MASK |
		NAU8824_TDM_TX_MASK, ctrl_val);
	regmap_update_bits(nau8824->regmap, NAU8824_REG_PORT0_LEFT_TIME_SLOT,
		NAU8824_TSLOT_L_MASK, tslot_l);

	वापस 0;
पूर्ण

/**
 * nau8824_calc_fll_param - Calculate FLL parameters.
 * @fll_in: बाह्यal घड़ी provided to codec.
 * @fs: sampling rate.
 * @fll_param: Poपूर्णांकer to काष्ठाure of FLL parameters.
 *
 * Calculate FLL parameters to configure codec.
 *
 * Returns 0 क्रम success or negative error code.
 */
अटल पूर्णांक nau8824_calc_fll_param(अचिन्हित पूर्णांक fll_in,
	अचिन्हित पूर्णांक fs, काष्ठा nau8824_fll *fll_param)
अणु
	u64 fvco, fvco_max;
	अचिन्हित पूर्णांक fref, i, fvco_sel;

	/* Ensure the reference घड़ी frequency (FREF) is <= 13.5MHz by भागiding
	 * freq_in by 1, 2, 4, or 8 using FLL pre-scalar.
	 * FREF = freq_in / NAU8824_FLL_REF_DIV_MASK
	 */
	क्रम (i = 0; i < ARRAY_SIZE(fll_pre_scalar); i++) अणु
		fref = fll_in / fll_pre_scalar[i].param;
		अगर (fref <= NAU_FREF_MAX)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(fll_pre_scalar))
		वापस -EINVAL;
	fll_param->clk_ref_भाग = fll_pre_scalar[i].val;

	/* Choose the FLL ratio based on FREF */
	क्रम (i = 0; i < ARRAY_SIZE(fll_ratio); i++) अणु
		अगर (fref >= fll_ratio[i].param)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(fll_ratio))
		वापस -EINVAL;
	fll_param->ratio = fll_ratio[i].val;

	/* Calculate the frequency of DCO (FDCO) given freq_out = 256 * Fs.
	 * FDCO must be within the 90MHz - 124MHz or the FFL cannot be
	 * guaranteed across the full range of operation.
	 * FDCO = freq_out * 2 * mclk_src_scaling
	 */
	fvco_max = 0;
	fvco_sel = ARRAY_SIZE(mclk_src_scaling);
	क्रम (i = 0; i < ARRAY_SIZE(mclk_src_scaling); i++) अणु
		fvco = 256ULL * fs * 2 * mclk_src_scaling[i].param;
		अगर (fvco > NAU_FVCO_MIN && fvco < NAU_FVCO_MAX &&
			fvco_max < fvco) अणु
			fvco_max = fvco;
			fvco_sel = i;
		पूर्ण
	पूर्ण
	अगर (ARRAY_SIZE(mclk_src_scaling) == fvco_sel)
		वापस -EINVAL;
	fll_param->mclk_src = mclk_src_scaling[fvco_sel].val;

	/* Calculate the FLL 10-bit पूर्णांकeger input and the FLL 16-bit fractional
	 * input based on FDCO, FREF and FLL ratio.
	 */
	fvco = भाग_u64(fvco_max << 16, fref * fll_param->ratio);
	fll_param->fll_पूर्णांक = (fvco >> 16) & 0x3FF;
	fll_param->fll_frac = fvco & 0xFFFF;
	वापस 0;
पूर्ण

अटल व्योम nau8824_fll_apply(काष्ठा regmap *regmap,
	काष्ठा nau8824_fll *fll_param)
अणु
	regmap_update_bits(regmap, NAU8824_REG_CLK_DIVIDER,
		NAU8824_CLK_SRC_MASK | NAU8824_CLK_MCLK_SRC_MASK,
		NAU8824_CLK_SRC_MCLK | fll_param->mclk_src);
	regmap_update_bits(regmap, NAU8824_REG_FLL1,
		NAU8824_FLL_RATIO_MASK, fll_param->ratio);
	/* FLL 16-bit fractional input */
	regmap_ग_लिखो(regmap, NAU8824_REG_FLL2, fll_param->fll_frac);
	/* FLL 10-bit पूर्णांकeger input */
	regmap_update_bits(regmap, NAU8824_REG_FLL3,
		NAU8824_FLL_INTEGER_MASK, fll_param->fll_पूर्णांक);
	/* FLL pre-scaler */
	regmap_update_bits(regmap, NAU8824_REG_FLL4,
		NAU8824_FLL_REF_DIV_MASK,
		fll_param->clk_ref_भाग << NAU8824_FLL_REF_DIV_SFT);
	/* select भागided VCO input */
	regmap_update_bits(regmap, NAU8824_REG_FLL5,
		NAU8824_FLL_CLK_SW_MASK, NAU8824_FLL_CLK_SW_REF);
	/* Disable मुक्त-running mode */
	regmap_update_bits(regmap,
		NAU8824_REG_FLL6, NAU8824_DCO_EN, 0);
	अगर (fll_param->fll_frac) अणु
		regmap_update_bits(regmap, NAU8824_REG_FLL5,
			NAU8824_FLL_PDB_DAC_EN | NAU8824_FLL_LOOP_FTR_EN |
			NAU8824_FLL_FTR_SW_MASK,
			NAU8824_FLL_PDB_DAC_EN | NAU8824_FLL_LOOP_FTR_EN |
			NAU8824_FLL_FTR_SW_FILTER);
		regmap_update_bits(regmap, NAU8824_REG_FLL6,
			NAU8824_SDM_EN, NAU8824_SDM_EN);
	पूर्ण अन्यथा अणु
		regmap_update_bits(regmap, NAU8824_REG_FLL5,
			NAU8824_FLL_PDB_DAC_EN | NAU8824_FLL_LOOP_FTR_EN |
			NAU8824_FLL_FTR_SW_MASK, NAU8824_FLL_FTR_SW_ACCU);
		regmap_update_bits(regmap,
			NAU8824_REG_FLL6, NAU8824_SDM_EN, 0);
	पूर्ण
पूर्ण

/* freq_out must be 256*Fs in order to achieve the best perक्रमmance */
अटल पूर्णांक nau8824_set_pll(काष्ठा snd_soc_component *component, पूर्णांक pll_id, पूर्णांक source,
		अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा nau8824 *nau8824 = snd_soc_component_get_drvdata(component);
	काष्ठा nau8824_fll fll_param;
	पूर्णांक ret, fs;

	fs = freq_out / 256;
	ret = nau8824_calc_fll_param(freq_in, fs, &fll_param);
	अगर (ret < 0) अणु
		dev_err(nau8824->dev, "Unsupported input clock %d\n", freq_in);
		वापस ret;
	पूर्ण
	dev_dbg(nau8824->dev, "mclk_src=%x ratio=%x fll_frac=%x fll_int=%x clk_ref_div=%x\n",
		fll_param.mclk_src, fll_param.ratio, fll_param.fll_frac,
		fll_param.fll_पूर्णांक, fll_param.clk_ref_भाग);

	nau8824_fll_apply(nau8824->regmap, &fll_param);
	mdelay(2);
	regmap_update_bits(nau8824->regmap, NAU8824_REG_CLK_DIVIDER,
		NAU8824_CLK_SRC_MASK, NAU8824_CLK_SRC_VCO);

	वापस 0;
पूर्ण

अटल पूर्णांक nau8824_config_sysclk(काष्ठा nau8824 *nau8824,
	पूर्णांक clk_id, अचिन्हित पूर्णांक freq)
अणु
	काष्ठा regmap *regmap = nau8824->regmap;

	चयन (clk_id) अणु
	हाल NAU8824_CLK_DIS:
		regmap_update_bits(regmap, NAU8824_REG_CLK_DIVIDER,
			NAU8824_CLK_SRC_MASK, NAU8824_CLK_SRC_MCLK);
		regmap_update_bits(regmap, NAU8824_REG_FLL6,
			NAU8824_DCO_EN, 0);
		अवरोध;

	हाल NAU8824_CLK_MCLK:
		nau8824_sema_acquire(nau8824, HZ);
		regmap_update_bits(regmap, NAU8824_REG_CLK_DIVIDER,
			NAU8824_CLK_SRC_MASK, NAU8824_CLK_SRC_MCLK);
		regmap_update_bits(regmap, NAU8824_REG_FLL6,
			NAU8824_DCO_EN, 0);
		nau8824_sema_release(nau8824);
		अवरोध;

	हाल NAU8824_CLK_INTERNAL:
		regmap_update_bits(regmap, NAU8824_REG_FLL6,
			NAU8824_DCO_EN, NAU8824_DCO_EN);
		regmap_update_bits(regmap, NAU8824_REG_CLK_DIVIDER,
			NAU8824_CLK_SRC_MASK, NAU8824_CLK_SRC_VCO);
		अवरोध;

	हाल NAU8824_CLK_FLL_MCLK:
		nau8824_sema_acquire(nau8824, HZ);
		regmap_update_bits(regmap, NAU8824_REG_FLL3,
			NAU8824_FLL_CLK_SRC_MASK, NAU8824_FLL_CLK_SRC_MCLK);
		nau8824_sema_release(nau8824);
		अवरोध;

	हाल NAU8824_CLK_FLL_BLK:
		nau8824_sema_acquire(nau8824, HZ);
		regmap_update_bits(regmap, NAU8824_REG_FLL3,
			NAU8824_FLL_CLK_SRC_MASK, NAU8824_FLL_CLK_SRC_BLK);
		nau8824_sema_release(nau8824);
		अवरोध;

	हाल NAU8824_CLK_FLL_FS:
		nau8824_sema_acquire(nau8824, HZ);
		regmap_update_bits(regmap, NAU8824_REG_FLL3,
			NAU8824_FLL_CLK_SRC_MASK, NAU8824_FLL_CLK_SRC_FS);
		nau8824_sema_release(nau8824);
		अवरोध;

	शेष:
		dev_err(nau8824->dev, "Invalid clock id (%d)\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(nau8824->dev, "Sysclk is %dHz and clock id is %d\n", freq,
		clk_id);

	वापस 0;
पूर्ण

अटल पूर्णांक nau8824_set_sysclk(काष्ठा snd_soc_component *component,
	पूर्णांक clk_id, पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा nau8824 *nau8824 = snd_soc_component_get_drvdata(component);

	वापस nau8824_config_sysclk(nau8824, clk_id, freq);
पूर्ण

अटल व्योम nau8824_resume_setup(काष्ठा nau8824 *nau8824)
अणु
	nau8824_config_sysclk(nau8824, NAU8824_CLK_DIS, 0);
	अगर (nau8824->irq) अणु
		/* Clear all पूर्णांकerruption status */
		nau8824_पूर्णांक_status_clear_all(nau8824->regmap);
		/* Enable jack detection at sleep mode, insertion detection,
		 * and ejection detection.
		 */
		regmap_update_bits(nau8824->regmap, NAU8824_REG_ENA_CTRL,
			NAU8824_JD_SLEEP_MODE, NAU8824_JD_SLEEP_MODE);
		regmap_update_bits(nau8824->regmap,
			NAU8824_REG_INTERRUPT_SETTING_1,
			NAU8824_IRQ_EJECT_EN | NAU8824_IRQ_INSERT_EN,
			NAU8824_IRQ_EJECT_EN | NAU8824_IRQ_INSERT_EN);
		regmap_update_bits(nau8824->regmap,
			NAU8824_REG_INTERRUPT_SETTING,
			NAU8824_IRQ_EJECT_DIS | NAU8824_IRQ_INSERT_DIS, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक nau8824_set_bias_level(काष्ठा snd_soc_component *component,
	क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा nau8824 *nau8824 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			/* Setup codec configuration after resume */
			nau8824_resume_setup(nau8824);
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		regmap_update_bits(nau8824->regmap,
			NAU8824_REG_INTERRUPT_SETTING, 0x3ff, 0x3ff);
		regmap_update_bits(nau8824->regmap,
			NAU8824_REG_INTERRUPT_SETTING_1,
			NAU8824_IRQ_EJECT_EN | NAU8824_IRQ_INSERT_EN, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nau8824_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा nau8824 *nau8824 = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	nau8824->dapm = dapm;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused nau8824_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा nau8824 *nau8824 = snd_soc_component_get_drvdata(component);

	अगर (nau8824->irq) अणु
		disable_irq(nau8824->irq);
		snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_OFF);
	पूर्ण
	regcache_cache_only(nau8824->regmap, true);
	regcache_mark_dirty(nau8824->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused nau8824_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा nau8824 *nau8824 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(nau8824->regmap, false);
	regcache_sync(nau8824->regmap);
	अगर (nau8824->irq) अणु
		/* Hold semaphore to postpone playback happening
		 * until jack detection करोne.
		 */
		nau8824_sema_acquire(nau8824, 0);
		enable_irq(nau8824->irq);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver nau8824_component_driver = अणु
	.probe			= nau8824_component_probe,
	.set_sysclk		= nau8824_set_sysclk,
	.set_pll		= nau8824_set_pll,
	.set_bias_level		= nau8824_set_bias_level,
	.suspend		= nau8824_suspend,
	.resume			= nau8824_resume,
	.controls		= nau8824_snd_controls,
	.num_controls		= ARRAY_SIZE(nau8824_snd_controls),
	.dapm_widमाला_लो		= nau8824_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(nau8824_dapm_widमाला_लो),
	.dapm_routes		= nau8824_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(nau8824_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops nau8824_dai_ops = अणु
	.hw_params = nau8824_hw_params,
	.set_fmt = nau8824_set_fmt,
	.set_tdm_slot = nau8824_set_tdm_slot,
पूर्ण;

#घोषणा NAU8824_RATES SNDRV_PCM_RATE_8000_192000
#घोषणा NAU8824_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE \
	 | SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver nau8824_dai = अणु
	.name = NAU8824_CODEC_DAI,
	.playback = अणु
		.stream_name	 = "Playback",
		.channels_min	 = 1,
		.channels_max	 = 2,
		.rates		 = NAU8824_RATES,
		.क्रमmats	 = NAU8824_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name	 = "Capture",
		.channels_min	 = 1,
		.channels_max	 = 2,
		.rates		 = NAU8824_RATES,
		.क्रमmats	 = NAU8824_FORMATS,
	पूर्ण,
	.ops = &nau8824_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा regmap_config nau8824_regmap_config = अणु
	.val_bits = NAU8824_REG_ADDR_LEN,
	.reg_bits = NAU8824_REG_DATA_LEN,

	.max_रेजिस्टर = NAU8824_REG_MAX,
	.पढ़ोable_reg = nau8824_पढ़ोable_reg,
	.ग_लिखोable_reg = nau8824_ग_लिखोable_reg,
	.अस्थिर_reg = nau8824_अस्थिर_reg,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = nau8824_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(nau8824_reg_शेषs),
पूर्ण;

/**
 * nau8824_enable_jack_detect - Specअगरy a jack क्रम event reporting
 *
 * @component:  component to रेजिस्टर the jack with
 * @jack: jack to use to report headset and button events on
 *
 * After this function has been called the headset insert/हटाओ and button
 * events will be routed to the given jack.  Jack can be null to stop
 * reporting.
 */
पूर्णांक nau8824_enable_jack_detect(काष्ठा snd_soc_component *component,
	काष्ठा snd_soc_jack *jack)
अणु
	काष्ठा nau8824 *nau8824 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	nau8824->jack = jack;
	/* Initiate jack detection work queue */
	INIT_WORK(&nau8824->jdet_work, nau8824_jdet_work);
	ret = devm_request_thपढ़ोed_irq(nau8824->dev, nau8824->irq, शून्य,
		nau8824_पूर्णांकerrupt, IRQF_TRIGGER_LOW | IRQF_ONESHOT,
		"nau8824", nau8824);
	अगर (ret) अणु
		dev_err(nau8824->dev, "Cannot request irq %d (%d)\n",
			nau8824->irq, ret);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nau8824_enable_jack_detect);

अटल व्योम nau8824_reset_chip(काष्ठा regmap *regmap)
अणु
	regmap_ग_लिखो(regmap, NAU8824_REG_RESET, 0x00);
	regmap_ग_लिखो(regmap, NAU8824_REG_RESET, 0x00);
पूर्ण

अटल व्योम nau8824_setup_buttons(काष्ठा nau8824 *nau8824)
अणु
	काष्ठा regmap *regmap = nau8824->regmap;

	regmap_update_bits(regmap, NAU8824_REG_SAR_ADC,
		NAU8824_SAR_TRACKING_GAIN_MASK,
		nau8824->sar_voltage << NAU8824_SAR_TRACKING_GAIN_SFT);
	regmap_update_bits(regmap, NAU8824_REG_SAR_ADC,
		NAU8824_SAR_COMPARE_TIME_MASK,
		nau8824->sar_compare_समय << NAU8824_SAR_COMPARE_TIME_SFT);
	regmap_update_bits(regmap, NAU8824_REG_SAR_ADC,
		NAU8824_SAR_SAMPLING_TIME_MASK,
		nau8824->sar_sampling_समय << NAU8824_SAR_SAMPLING_TIME_SFT);

	regmap_update_bits(regmap, NAU8824_REG_VDET_COEFFICIENT,
		NAU8824_LEVELS_NR_MASK,
		(nau8824->sar_threshold_num - 1) << NAU8824_LEVELS_NR_SFT);
	regmap_update_bits(regmap, NAU8824_REG_VDET_COEFFICIENT,
		NAU8824_HYSTERESIS_MASK,
		nau8824->sar_hysteresis << NAU8824_HYSTERESIS_SFT);
	regmap_update_bits(regmap, NAU8824_REG_VDET_COEFFICIENT,
		NAU8824_SHORTKEY_DEBOUNCE_MASK,
		nau8824->key_debounce << NAU8824_SHORTKEY_DEBOUNCE_SFT);

	regmap_ग_लिखो(regmap, NAU8824_REG_VDET_THRESHOLD_1,
		(nau8824->sar_threshold[0] << 8) | nau8824->sar_threshold[1]);
	regmap_ग_लिखो(regmap, NAU8824_REG_VDET_THRESHOLD_2,
		(nau8824->sar_threshold[2] << 8) | nau8824->sar_threshold[3]);
	regmap_ग_लिखो(regmap, NAU8824_REG_VDET_THRESHOLD_3,
		(nau8824->sar_threshold[4] << 8) | nau8824->sar_threshold[5]);
	regmap_ग_लिखो(regmap, NAU8824_REG_VDET_THRESHOLD_4,
		(nau8824->sar_threshold[6] << 8) | nau8824->sar_threshold[7]);
पूर्ण

अटल व्योम nau8824_init_regs(काष्ठा nau8824 *nau8824)
अणु
	काष्ठा regmap *regmap = nau8824->regmap;

	/* Enable Bias/VMID/VMID Tieoff */
	regmap_update_bits(regmap, NAU8824_REG_BIAS_ADJ,
		NAU8824_VMID | NAU8824_VMID_SEL_MASK, NAU8824_VMID |
		(nau8824->vref_impedance << NAU8824_VMID_SEL_SFT));
	regmap_update_bits(regmap, NAU8824_REG_BOOST,
		NAU8824_GLOBAL_BIAS_EN, NAU8824_GLOBAL_BIAS_EN);
	mdelay(2);
	regmap_update_bits(regmap, NAU8824_REG_MIC_BIAS,
		NAU8824_MICBIAS_VOLTAGE_MASK, nau8824->micbias_voltage);
	/* Disable Boost Driver, Automatic Short circuit protection enable */
	regmap_update_bits(regmap, NAU8824_REG_BOOST,
		NAU8824_PRECHARGE_DIS | NAU8824_HP_BOOST_DIS |
		NAU8824_HP_BOOST_G_DIS | NAU8824_SHORT_SHUTDOWN_EN,
		NAU8824_PRECHARGE_DIS | NAU8824_HP_BOOST_DIS |
		NAU8824_HP_BOOST_G_DIS | NAU8824_SHORT_SHUTDOWN_EN);
	/* Scaling क्रम ADC and DAC घड़ी */
	regmap_update_bits(regmap, NAU8824_REG_CLK_DIVIDER,
		NAU8824_CLK_ADC_SRC_MASK | NAU8824_CLK_DAC_SRC_MASK,
		(0x1 << NAU8824_CLK_ADC_SRC_SFT) |
		(0x1 << NAU8824_CLK_DAC_SRC_SFT));
	regmap_update_bits(regmap, NAU8824_REG_DAC_MUTE_CTRL,
		NAU8824_DAC_ZC_EN, NAU8824_DAC_ZC_EN);
	regmap_update_bits(regmap, NAU8824_REG_ENA_CTRL,
		NAU8824_DAC_CH1_EN | NAU8824_DAC_CH0_EN |
		NAU8824_ADC_CH0_EN | NAU8824_ADC_CH1_EN |
		NAU8824_ADC_CH2_EN | NAU8824_ADC_CH3_EN,
		NAU8824_DAC_CH1_EN | NAU8824_DAC_CH0_EN |
		NAU8824_ADC_CH0_EN | NAU8824_ADC_CH1_EN |
		NAU8824_ADC_CH2_EN | NAU8824_ADC_CH3_EN);
	regmap_update_bits(regmap, NAU8824_REG_CLK_GATING_ENA,
		NAU8824_CLK_ADC_CH23_EN | NAU8824_CLK_ADC_CH01_EN |
		NAU8824_CLK_DAC_CH1_EN | NAU8824_CLK_DAC_CH0_EN |
		NAU8824_CLK_I2S_EN | NAU8824_CLK_GAIN_EN |
		NAU8824_CLK_SAR_EN | NAU8824_CLK_DMIC_CH23_EN,
		NAU8824_CLK_ADC_CH23_EN | NAU8824_CLK_ADC_CH01_EN |
		NAU8824_CLK_DAC_CH1_EN | NAU8824_CLK_DAC_CH0_EN |
		NAU8824_CLK_I2S_EN | NAU8824_CLK_GAIN_EN |
		NAU8824_CLK_SAR_EN | NAU8824_CLK_DMIC_CH23_EN);
	/* Class G समयr 64ms */
	regmap_update_bits(regmap, NAU8824_REG_CLASSG,
		NAU8824_CLASSG_TIMER_MASK,
		0x20 << NAU8824_CLASSG_TIMER_SFT);
	regmap_update_bits(regmap, NAU8824_REG_TRIM_SETTINGS,
		NAU8824_DRV_CURR_INC, NAU8824_DRV_CURR_INC);
	/* Disable DACR/L घातer */
	regmap_update_bits(regmap, NAU8824_REG_CHARGE_PUMP_CONTROL,
		NAU8824_SPKR_PULL_DOWN | NAU8824_SPKL_PULL_DOWN |
		NAU8824_POWER_DOWN_DACR | NAU8824_POWER_DOWN_DACL,
		NAU8824_SPKR_PULL_DOWN | NAU8824_SPKL_PULL_DOWN |
		NAU8824_POWER_DOWN_DACR | NAU8824_POWER_DOWN_DACL);
	/* Enable TESTDAC. This sets the analog DAC inमाला_दो to a '0' input
	 * संकेत to aव्योम any glitches due to घातer up transients in both
	 * the analog and digital DAC circuit.
	 */
	regmap_update_bits(regmap, NAU8824_REG_ENABLE_LO,
		NAU8824_TEST_DAC_EN, NAU8824_TEST_DAC_EN);
	/* Config L/R channel */
	regmap_update_bits(regmap, NAU8824_REG_DAC_CH0_DGAIN_CTRL,
		NAU8824_DAC_CH0_SEL_MASK, NAU8824_DAC_CH0_SEL_I2S0);
	regmap_update_bits(regmap, NAU8824_REG_DAC_CH1_DGAIN_CTRL,
		NAU8824_DAC_CH1_SEL_MASK, NAU8824_DAC_CH1_SEL_I2S1);
	regmap_update_bits(regmap, NAU8824_REG_ENABLE_LO,
		NAU8824_DACR_HPR_EN | NAU8824_DACL_HPL_EN,
		NAU8824_DACR_HPR_EN | NAU8824_DACL_HPL_EN);
	/* Default oversampling/decimations settings are unusable
	 * (audible hiss). Set it to something better.
	 */
	regmap_update_bits(regmap, NAU8824_REG_ADC_FILTER_CTRL,
		NAU8824_ADC_SYNC_DOWN_MASK, NAU8824_ADC_SYNC_DOWN_64);
	regmap_update_bits(regmap, NAU8824_REG_DAC_FILTER_CTRL_1,
		NAU8824_DAC_CICCLP_OFF | NAU8824_DAC_OVERSAMPLE_MASK,
		NAU8824_DAC_CICCLP_OFF | NAU8824_DAC_OVERSAMPLE_64);
	/* DAC घड़ी delay 2ns, VREF */
	regmap_update_bits(regmap, NAU8824_REG_RDAC,
		NAU8824_RDAC_CLK_DELAY_MASK | NAU8824_RDAC_VREF_MASK,
		(0x2 << NAU8824_RDAC_CLK_DELAY_SFT) |
		(0x3 << NAU8824_RDAC_VREF_SFT));
	/* PGA input mode selection */
	regmap_update_bits(regmap, NAU8824_REG_FEPGA,
		NAU8824_FEPGA_MODEL_SHORT_EN | NAU8824_FEPGA_MODER_SHORT_EN,
		NAU8824_FEPGA_MODEL_SHORT_EN | NAU8824_FEPGA_MODER_SHORT_EN);
	/* Digital microphone control */
	regmap_update_bits(regmap, NAU8824_REG_ANALOG_CONTROL_1,
		NAU8824_DMIC_CLK_DRV_STRG | NAU8824_DMIC_CLK_SLEW_FAST,
		NAU8824_DMIC_CLK_DRV_STRG | NAU8824_DMIC_CLK_SLEW_FAST);
	regmap_update_bits(regmap, NAU8824_REG_JACK_DET_CTRL,
		NAU8824_JACK_LOGIC,
		/* jkdet_polarity - 1  is क्रम active-low */
		nau8824->jkdet_polarity ? 0 : NAU8824_JACK_LOGIC);
	regmap_update_bits(regmap,
		NAU8824_REG_JACK_DET_CTRL, NAU8824_JACK_EJECT_DT_MASK,
		(nau8824->jack_eject_debounce << NAU8824_JACK_EJECT_DT_SFT));
	अगर (nau8824->sar_threshold_num)
		nau8824_setup_buttons(nau8824);
पूर्ण

अटल पूर्णांक nau8824_setup_irq(काष्ठा nau8824 *nau8824)
अणु
	/* Disable पूर्णांकerruption beक्रमe codec initiation करोne */
	regmap_update_bits(nau8824->regmap, NAU8824_REG_ENA_CTRL,
		NAU8824_JD_SLEEP_MODE, NAU8824_JD_SLEEP_MODE);
	regmap_update_bits(nau8824->regmap,
		NAU8824_REG_INTERRUPT_SETTING, 0x3ff, 0x3ff);
	regmap_update_bits(nau8824->regmap, NAU8824_REG_INTERRUPT_SETTING_1,
		NAU8824_IRQ_EJECT_EN | NAU8824_IRQ_INSERT_EN, 0);

	वापस 0;
पूर्ण

अटल व्योम nau8824_prपूर्णांक_device_properties(काष्ठा nau8824 *nau8824)
अणु
	काष्ठा device *dev = nau8824->dev;
	पूर्णांक i;

	dev_dbg(dev, "jkdet-polarity:       %d\n", nau8824->jkdet_polarity);
	dev_dbg(dev, "micbias-voltage:      %d\n", nau8824->micbias_voltage);
	dev_dbg(dev, "vref-impedance:       %d\n", nau8824->vref_impedance);

	dev_dbg(dev, "sar-threshold-num:    %d\n", nau8824->sar_threshold_num);
	क्रम (i = 0; i < nau8824->sar_threshold_num; i++)
		dev_dbg(dev, "sar-threshold[%d]=%x\n", i,
				nau8824->sar_threshold[i]);

	dev_dbg(dev, "sar-hysteresis:       %d\n", nau8824->sar_hysteresis);
	dev_dbg(dev, "sar-voltage:          %d\n", nau8824->sar_voltage);
	dev_dbg(dev, "sar-compare-time:     %d\n", nau8824->sar_compare_समय);
	dev_dbg(dev, "sar-sampling-time:    %d\n", nau8824->sar_sampling_समय);
	dev_dbg(dev, "short-key-debounce:   %d\n", nau8824->key_debounce);
	dev_dbg(dev, "jack-eject-debounce:  %d\n",
			nau8824->jack_eject_debounce);
पूर्ण

अटल पूर्णांक nau8824_पढ़ो_device_properties(काष्ठा device *dev,
	काष्ठा nau8824 *nau8824) अणु
	पूर्णांक ret;

	ret = device_property_पढ़ो_u32(dev, "nuvoton,jkdet-polarity",
		&nau8824->jkdet_polarity);
	अगर (ret)
		nau8824->jkdet_polarity = 1;
	ret = device_property_पढ़ो_u32(dev, "nuvoton,micbias-voltage",
		&nau8824->micbias_voltage);
	अगर (ret)
		nau8824->micbias_voltage = 6;
	ret = device_property_पढ़ो_u32(dev, "nuvoton,vref-impedance",
		&nau8824->vref_impedance);
	अगर (ret)
		nau8824->vref_impedance = 2;
	ret = device_property_पढ़ो_u32(dev, "nuvoton,sar-threshold-num",
		&nau8824->sar_threshold_num);
	अगर (ret)
		nau8824->sar_threshold_num = 4;
	ret = device_property_पढ़ो_u32_array(dev, "nuvoton,sar-threshold",
		nau8824->sar_threshold, nau8824->sar_threshold_num);
	अगर (ret) अणु
		nau8824->sar_threshold[0] = 0x0a;
		nau8824->sar_threshold[1] = 0x14;
		nau8824->sar_threshold[2] = 0x26;
		nau8824->sar_threshold[3] = 0x73;
	पूर्ण
	ret = device_property_पढ़ो_u32(dev, "nuvoton,sar-hysteresis",
		&nau8824->sar_hysteresis);
	अगर (ret)
		nau8824->sar_hysteresis = 0;
	ret = device_property_पढ़ो_u32(dev, "nuvoton,sar-voltage",
		&nau8824->sar_voltage);
	अगर (ret)
		nau8824->sar_voltage = 6;
	ret = device_property_पढ़ो_u32(dev, "nuvoton,sar-compare-time",
		&nau8824->sar_compare_समय);
	अगर (ret)
		nau8824->sar_compare_समय = 1;
	ret = device_property_पढ़ो_u32(dev, "nuvoton,sar-sampling-time",
		&nau8824->sar_sampling_समय);
	अगर (ret)
		nau8824->sar_sampling_समय = 1;
	ret = device_property_पढ़ो_u32(dev, "nuvoton,short-key-debounce",
		&nau8824->key_debounce);
	अगर (ret)
		nau8824->key_debounce = 0;
	ret = device_property_पढ़ो_u32(dev, "nuvoton,jack-eject-debounce",
		&nau8824->jack_eject_debounce);
	अगर (ret)
		nau8824->jack_eject_debounce = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक nau8824_i2c_probe(काष्ठा i2c_client *i2c,
	स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &i2c->dev;
	काष्ठा nau8824 *nau8824 = dev_get_platdata(dev);
	पूर्णांक ret, value;

	अगर (!nau8824) अणु
		nau8824 = devm_kzalloc(dev, माप(*nau8824), GFP_KERNEL);
		अगर (!nau8824)
			वापस -ENOMEM;
		ret = nau8824_पढ़ो_device_properties(dev, nau8824);
		अगर (ret)
			वापस ret;
	पूर्ण
	i2c_set_clientdata(i2c, nau8824);

	nau8824->regmap = devm_regmap_init_i2c(i2c, &nau8824_regmap_config);
	अगर (IS_ERR(nau8824->regmap))
		वापस PTR_ERR(nau8824->regmap);
	nau8824->dev = dev;
	nau8824->irq = i2c->irq;
	sema_init(&nau8824->jd_sem, 1);

	nau8824_prपूर्णांक_device_properties(nau8824);

	ret = regmap_पढ़ो(nau8824->regmap, NAU8824_REG_I2C_DEVICE_ID, &value);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read device id from the NAU8824: %d\n",
			ret);
		वापस ret;
	पूर्ण
	nau8824_reset_chip(nau8824->regmap);
	nau8824_init_regs(nau8824);

	अगर (i2c->irq)
		nau8824_setup_irq(nau8824);

	वापस devm_snd_soc_रेजिस्टर_component(dev,
		&nau8824_component_driver, &nau8824_dai, 1);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id nau8824_i2c_ids[] = अणु
	अणु "nau8824", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, nau8824_i2c_ids);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id nau8824_of_ids[] = अणु
	अणु .compatible = "nuvoton,nau8824", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, nau8824_of_ids);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id nau8824_acpi_match[] = अणु
	अणु "10508824", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, nau8824_acpi_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver nau8824_i2c_driver = अणु
	.driver = अणु
		.name = "nau8824",
		.of_match_table = of_match_ptr(nau8824_of_ids),
		.acpi_match_table = ACPI_PTR(nau8824_acpi_match),
	पूर्ण,
	.probe = nau8824_i2c_probe,
	.id_table = nau8824_i2c_ids,
पूर्ण;
module_i2c_driver(nau8824_i2c_driver);


MODULE_DESCRIPTION("ASoC NAU88L24 driver");
MODULE_AUTHOR("John Hsu <KCHSU0@nuvoton.com>");
MODULE_LICENSE("GPL v2");
