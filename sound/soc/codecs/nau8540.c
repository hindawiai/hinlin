<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * NAU85L40 ALSA SoC audio driver
 *
 * Copyright 2016 Nuvoton Technology Corp.
 * Author: John Hsu <KCHSU0@nuvoton.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश "nau8540.h"


#घोषणा NAU_FREF_MAX 13500000
#घोषणा NAU_FVCO_MAX 100000000
#घोषणा NAU_FVCO_MIN 90000000

/* the maximum frequency of CLK_ADC */
#घोषणा CLK_ADC_MAX 6144000

/* scaling क्रम mclk from sysclk_src output */
अटल स्थिर काष्ठा nau8540_fll_attr mclk_src_scaling[] = अणु
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
अटल स्थिर काष्ठा nau8540_fll_attr fll_ratio[] = अणु
	अणु 512000, 0x01 पूर्ण,
	अणु 256000, 0x02 पूर्ण,
	अणु 128000, 0x04 पूर्ण,
	अणु 64000, 0x08 पूर्ण,
	अणु 32000, 0x10 पूर्ण,
	अणु 8000, 0x20 पूर्ण,
	अणु 4000, 0x40 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nau8540_fll_attr fll_pre_scalar[] = अणु
	अणु 1, 0x0 पूर्ण,
	अणु 2, 0x1 पूर्ण,
	अणु 4, 0x2 पूर्ण,
	अणु 8, 0x3 पूर्ण,
पूर्ण;

/* over sampling rate */
अटल स्थिर काष्ठा nau8540_osr_attr osr_adc_sel[] = अणु
	अणु 32, 3 पूर्ण,	/* OSR 32, SRC 1/8 */
	अणु 64, 2 पूर्ण,	/* OSR 64, SRC 1/4 */
	अणु 128, 1 पूर्ण,	/* OSR 128, SRC 1/2 */
	अणु 256, 0 पूर्ण,	/* OSR 256, SRC 1 */
पूर्ण;

अटल स्थिर काष्ठा reg_शेष nau8540_reg_शेषs[] = अणु
	अणुNAU8540_REG_POWER_MANAGEMENT, 0x0000पूर्ण,
	अणुNAU8540_REG_CLOCK_CTRL, 0x0000पूर्ण,
	अणुNAU8540_REG_CLOCK_SRC, 0x0000पूर्ण,
	अणुNAU8540_REG_FLL1, 0x0001पूर्ण,
	अणुNAU8540_REG_FLL2, 0x3126पूर्ण,
	अणुNAU8540_REG_FLL3, 0x0008पूर्ण,
	अणुNAU8540_REG_FLL4, 0x0010पूर्ण,
	अणुNAU8540_REG_FLL5, 0xC000पूर्ण,
	अणुNAU8540_REG_FLL6, 0x6000पूर्ण,
	अणुNAU8540_REG_FLL_VCO_RSV, 0xF13Cपूर्ण,
	अणुNAU8540_REG_PCM_CTRL0, 0x000Bपूर्ण,
	अणुNAU8540_REG_PCM_CTRL1, 0x3010पूर्ण,
	अणुNAU8540_REG_PCM_CTRL2, 0x0800पूर्ण,
	अणुNAU8540_REG_PCM_CTRL3, 0x0000पूर्ण,
	अणुNAU8540_REG_PCM_CTRL4, 0x000Fपूर्ण,
	अणुNAU8540_REG_ALC_CONTROL_1, 0x0000पूर्ण,
	अणुNAU8540_REG_ALC_CONTROL_2, 0x700Bपूर्ण,
	अणुNAU8540_REG_ALC_CONTROL_3, 0x0022पूर्ण,
	अणुNAU8540_REG_ALC_CONTROL_4, 0x1010पूर्ण,
	अणुNAU8540_REG_ALC_CONTROL_5, 0x1010पूर्ण,
	अणुNAU8540_REG_NOTCH_FIL1_CH1, 0x0000पूर्ण,
	अणुNAU8540_REG_NOTCH_FIL2_CH1, 0x0000पूर्ण,
	अणुNAU8540_REG_NOTCH_FIL1_CH2, 0x0000पूर्ण,
	अणुNAU8540_REG_NOTCH_FIL2_CH2, 0x0000पूर्ण,
	अणुNAU8540_REG_NOTCH_FIL1_CH3, 0x0000पूर्ण,
	अणुNAU8540_REG_NOTCH_FIL2_CH3, 0x0000पूर्ण,
	अणुNAU8540_REG_NOTCH_FIL1_CH4, 0x0000पूर्ण,
	अणुNAU8540_REG_NOTCH_FIL2_CH4, 0x0000पूर्ण,
	अणुNAU8540_REG_HPF_FILTER_CH12, 0x0000पूर्ण,
	अणुNAU8540_REG_HPF_FILTER_CH34, 0x0000पूर्ण,
	अणुNAU8540_REG_ADC_SAMPLE_RATE, 0x0002पूर्ण,
	अणुNAU8540_REG_DIGITAL_GAIN_CH1, 0x0400पूर्ण,
	अणुNAU8540_REG_DIGITAL_GAIN_CH2, 0x0400पूर्ण,
	अणुNAU8540_REG_DIGITAL_GAIN_CH3, 0x0400पूर्ण,
	अणुNAU8540_REG_DIGITAL_GAIN_CH4, 0x0400पूर्ण,
	अणुNAU8540_REG_DIGITAL_MUX, 0x00E4पूर्ण,
	अणुNAU8540_REG_GPIO_CTRL, 0x0000पूर्ण,
	अणुNAU8540_REG_MISC_CTRL, 0x0000पूर्ण,
	अणुNAU8540_REG_I2C_CTRL, 0xEFFFपूर्ण,
	अणुNAU8540_REG_VMID_CTRL, 0x0000पूर्ण,
	अणुNAU8540_REG_MUTE, 0x0000पूर्ण,
	अणुNAU8540_REG_ANALOG_ADC1, 0x0011पूर्ण,
	अणुNAU8540_REG_ANALOG_ADC2, 0x0020पूर्ण,
	अणुNAU8540_REG_ANALOG_PWR, 0x0000पूर्ण,
	अणुNAU8540_REG_MIC_BIAS, 0x0004पूर्ण,
	अणुNAU8540_REG_REFERENCE, 0x0000पूर्ण,
	अणुNAU8540_REG_FEPGA1, 0x0000पूर्ण,
	अणुNAU8540_REG_FEPGA2, 0x0000पूर्ण,
	अणुNAU8540_REG_FEPGA3, 0x0101पूर्ण,
	अणुNAU8540_REG_FEPGA4, 0x0101पूर्ण,
	अणुNAU8540_REG_PWR, 0x0000पूर्ण,
पूर्ण;

अटल bool nau8540_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल NAU8540_REG_POWER_MANAGEMENT ... NAU8540_REG_FLL_VCO_RSV:
	हाल NAU8540_REG_PCM_CTRL0 ... NAU8540_REG_PCM_CTRL4:
	हाल NAU8540_REG_ALC_CONTROL_1 ... NAU8540_REG_ALC_CONTROL_5:
	हाल NAU8540_REG_ALC_GAIN_CH12 ... NAU8540_REG_ADC_SAMPLE_RATE:
	हाल NAU8540_REG_DIGITAL_GAIN_CH1 ... NAU8540_REG_DIGITAL_MUX:
	हाल NAU8540_REG_P2P_CH1 ... NAU8540_REG_I2C_CTRL:
	हाल NAU8540_REG_I2C_DEVICE_ID:
	हाल NAU8540_REG_VMID_CTRL ... NAU8540_REG_MUTE:
	हाल NAU8540_REG_ANALOG_ADC1 ... NAU8540_REG_PWR:
		वापस true;
	शेष:
		वापस false;
	पूर्ण

पूर्ण

अटल bool nau8540_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल NAU8540_REG_SW_RESET ... NAU8540_REG_FLL_VCO_RSV:
	हाल NAU8540_REG_PCM_CTRL0 ... NAU8540_REG_PCM_CTRL4:
	हाल NAU8540_REG_ALC_CONTROL_1 ... NAU8540_REG_ALC_CONTROL_5:
	हाल NAU8540_REG_NOTCH_FIL1_CH1 ... NAU8540_REG_ADC_SAMPLE_RATE:
	हाल NAU8540_REG_DIGITAL_GAIN_CH1 ... NAU8540_REG_DIGITAL_MUX:
	हाल NAU8540_REG_GPIO_CTRL ... NAU8540_REG_I2C_CTRL:
	हाल NAU8540_REG_RST:
	हाल NAU8540_REG_VMID_CTRL ... NAU8540_REG_MUTE:
	हाल NAU8540_REG_ANALOG_ADC1 ... NAU8540_REG_PWR:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool nau8540_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल NAU8540_REG_SW_RESET:
	हाल NAU8540_REG_ALC_GAIN_CH12 ... NAU8540_REG_ALC_STATUS:
	हाल NAU8540_REG_P2P_CH1 ... NAU8540_REG_PEAK_CH4:
	हाल NAU8540_REG_I2C_DEVICE_ID:
	हाल NAU8540_REG_RST:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण


अटल स्थिर DECLARE_TLV_DB_MINMAX(adc_vol_tlv, -12800, 3600);
अटल स्थिर DECLARE_TLV_DB_MINMAX(fepga_gain_tlv, -100, 3600);

अटल स्थिर काष्ठा snd_kcontrol_new nau8540_snd_controls[] = अणु
	SOC_SINGLE_TLV("Mic1 Volume", NAU8540_REG_DIGITAL_GAIN_CH1,
		0, 0x520, 0, adc_vol_tlv),
	SOC_SINGLE_TLV("Mic2 Volume", NAU8540_REG_DIGITAL_GAIN_CH2,
		0, 0x520, 0, adc_vol_tlv),
	SOC_SINGLE_TLV("Mic3 Volume", NAU8540_REG_DIGITAL_GAIN_CH3,
		0, 0x520, 0, adc_vol_tlv),
	SOC_SINGLE_TLV("Mic4 Volume", NAU8540_REG_DIGITAL_GAIN_CH4,
		0, 0x520, 0, adc_vol_tlv),

	SOC_SINGLE_TLV("Frontend PGA1 Volume", NAU8540_REG_FEPGA3,
		0, 0x25, 0, fepga_gain_tlv),
	SOC_SINGLE_TLV("Frontend PGA2 Volume", NAU8540_REG_FEPGA3,
		8, 0x25, 0, fepga_gain_tlv),
	SOC_SINGLE_TLV("Frontend PGA3 Volume", NAU8540_REG_FEPGA4,
		0, 0x25, 0, fepga_gain_tlv),
	SOC_SINGLE_TLV("Frontend PGA4 Volume", NAU8540_REG_FEPGA4,
		8, 0x25, 0, fepga_gain_tlv),
पूर्ण;

अटल स्थिर अक्षर * स्थिर adc_channel[] = अणु
	"ADC channel 1", "ADC channel 2", "ADC channel 3", "ADC channel 4"
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(
	digital_ch4_क्रमागत, NAU8540_REG_DIGITAL_MUX, 6, adc_channel);

अटल स्थिर काष्ठा snd_kcontrol_new digital_ch4_mux =
	SOC_DAPM_ENUM("Digital CH4 Select", digital_ch4_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	digital_ch3_क्रमागत, NAU8540_REG_DIGITAL_MUX, 4, adc_channel);

अटल स्थिर काष्ठा snd_kcontrol_new digital_ch3_mux =
	SOC_DAPM_ENUM("Digital CH3 Select", digital_ch3_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	digital_ch2_क्रमागत, NAU8540_REG_DIGITAL_MUX, 2, adc_channel);

अटल स्थिर काष्ठा snd_kcontrol_new digital_ch2_mux =
	SOC_DAPM_ENUM("Digital CH2 Select", digital_ch2_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	digital_ch1_क्रमागत, NAU8540_REG_DIGITAL_MUX, 0, adc_channel);

अटल स्थिर काष्ठा snd_kcontrol_new digital_ch1_mux =
	SOC_DAPM_ENUM("Digital CH1 Select", digital_ch1_क्रमागत);

अटल पूर्णांक adc_घातer_control(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *k, पूर्णांक  event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा nau8540 *nau8540 = snd_soc_component_get_drvdata(component);

	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		msleep(300);
		/* DO12 and DO34 pad output enable */
		regmap_update_bits(nau8540->regmap, NAU8540_REG_PCM_CTRL1,
			NAU8540_I2S_DO12_TRI, 0);
		regmap_update_bits(nau8540->regmap, NAU8540_REG_PCM_CTRL2,
			NAU8540_I2S_DO34_TRI, 0);
	पूर्ण अन्यथा अगर (SND_SOC_DAPM_EVENT_OFF(event)) अणु
		regmap_update_bits(nau8540->regmap, NAU8540_REG_PCM_CTRL1,
			NAU8540_I2S_DO12_TRI, NAU8540_I2S_DO12_TRI);
		regmap_update_bits(nau8540->regmap, NAU8540_REG_PCM_CTRL2,
			NAU8540_I2S_DO34_TRI, NAU8540_I2S_DO34_TRI);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक aअगरtx_घातer_control(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *k, पूर्णांक  event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा nau8540 *nau8540 = snd_soc_component_get_drvdata(component);

	अगर (SND_SOC_DAPM_EVENT_OFF(event)) अणु
		regmap_ग_लिखो(nau8540->regmap, NAU8540_REG_RST, 0x0001);
		regmap_ग_लिखो(nau8540->regmap, NAU8540_REG_RST, 0x0000);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget nau8540_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("MICBIAS2", NAU8540_REG_MIC_BIAS, 11, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MICBIAS1", NAU8540_REG_MIC_BIAS, 10, 0, शून्य, 0),

	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("MIC3"),
	SND_SOC_DAPM_INPUT("MIC4"),

	SND_SOC_DAPM_PGA("Frontend PGA1", NAU8540_REG_PWR, 12, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Frontend PGA2", NAU8540_REG_PWR, 13, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Frontend PGA3", NAU8540_REG_PWR, 14, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Frontend PGA4", NAU8540_REG_PWR, 15, 0, शून्य, 0),

	SND_SOC_DAPM_ADC_E("ADC1", शून्य,
		NAU8540_REG_POWER_MANAGEMENT, 0, 0, adc_घातer_control,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_ADC_E("ADC2", शून्य,
		NAU8540_REG_POWER_MANAGEMENT, 1, 0, adc_घातer_control,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_ADC_E("ADC3", शून्य,
		NAU8540_REG_POWER_MANAGEMENT, 2, 0, adc_घातer_control,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_ADC_E("ADC4", शून्य,
		NAU8540_REG_POWER_MANAGEMENT, 3, 0, adc_घातer_control,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_PGA("ADC CH1", NAU8540_REG_ANALOG_PWR, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("ADC CH2", NAU8540_REG_ANALOG_PWR, 1, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("ADC CH3", NAU8540_REG_ANALOG_PWR, 2, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("ADC CH4", NAU8540_REG_ANALOG_PWR, 3, 0, शून्य, 0),

	SND_SOC_DAPM_MUX("Digital CH4 Mux",
		SND_SOC_NOPM, 0, 0, &digital_ch4_mux),
	SND_SOC_DAPM_MUX("Digital CH3 Mux",
		SND_SOC_NOPM, 0, 0, &digital_ch3_mux),
	SND_SOC_DAPM_MUX("Digital CH2 Mux",
		SND_SOC_NOPM, 0, 0, &digital_ch2_mux),
	SND_SOC_DAPM_MUX("Digital CH1 Mux",
		SND_SOC_NOPM, 0, 0, &digital_ch1_mux),

	SND_SOC_DAPM_AIF_OUT_E("AIFTX", "Capture", 0, SND_SOC_NOPM, 0, 0,
		aअगरtx_घातer_control, SND_SOC_DAPM_POST_PMD),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route nau8540_dapm_routes[] = अणु
	अणु"Frontend PGA1", शून्य, "MIC1"पूर्ण,
	अणु"Frontend PGA2", शून्य, "MIC2"पूर्ण,
	अणु"Frontend PGA3", शून्य, "MIC3"पूर्ण,
	अणु"Frontend PGA4", शून्य, "MIC4"पूर्ण,

	अणु"ADC1", शून्य, "Frontend PGA1"पूर्ण,
	अणु"ADC2", शून्य, "Frontend PGA2"पूर्ण,
	अणु"ADC3", शून्य, "Frontend PGA3"पूर्ण,
	अणु"ADC4", शून्य, "Frontend PGA4"पूर्ण,

	अणु"ADC CH1", शून्य, "ADC1"पूर्ण,
	अणु"ADC CH2", शून्य, "ADC2"पूर्ण,
	अणु"ADC CH3", शून्य, "ADC3"पूर्ण,
	अणु"ADC CH4", शून्य, "ADC4"पूर्ण,

	अणु"ADC1", शून्य, "MICBIAS1"पूर्ण,
	अणु"ADC2", शून्य, "MICBIAS1"पूर्ण,
	अणु"ADC3", शून्य, "MICBIAS2"पूर्ण,
	अणु"ADC4", शून्य, "MICBIAS2"पूर्ण,

	अणु"Digital CH1 Mux", "ADC channel 1", "ADC CH1"पूर्ण,
	अणु"Digital CH1 Mux", "ADC channel 2", "ADC CH2"पूर्ण,
	अणु"Digital CH1 Mux", "ADC channel 3", "ADC CH3"पूर्ण,
	अणु"Digital CH1 Mux", "ADC channel 4", "ADC CH4"पूर्ण,

	अणु"Digital CH2 Mux", "ADC channel 1", "ADC CH1"पूर्ण,
	अणु"Digital CH2 Mux", "ADC channel 2", "ADC CH2"पूर्ण,
	अणु"Digital CH2 Mux", "ADC channel 3", "ADC CH3"पूर्ण,
	अणु"Digital CH2 Mux", "ADC channel 4", "ADC CH4"पूर्ण,

	अणु"Digital CH3 Mux", "ADC channel 1", "ADC CH1"पूर्ण,
	अणु"Digital CH3 Mux", "ADC channel 2", "ADC CH2"पूर्ण,
	अणु"Digital CH3 Mux", "ADC channel 3", "ADC CH3"पूर्ण,
	अणु"Digital CH3 Mux", "ADC channel 4", "ADC CH4"पूर्ण,

	अणु"Digital CH4 Mux", "ADC channel 1", "ADC CH1"पूर्ण,
	अणु"Digital CH4 Mux", "ADC channel 2", "ADC CH2"पूर्ण,
	अणु"Digital CH4 Mux", "ADC channel 3", "ADC CH3"पूर्ण,
	अणु"Digital CH4 Mux", "ADC channel 4", "ADC CH4"पूर्ण,

	अणु"AIFTX", शून्य, "Digital CH1 Mux"पूर्ण,
	अणु"AIFTX", शून्य, "Digital CH2 Mux"पूर्ण,
	अणु"AIFTX", शून्य, "Digital CH3 Mux"पूर्ण,
	अणु"AIFTX", शून्य, "Digital CH4 Mux"पूर्ण,
पूर्ण;

अटल पूर्णांक nau8540_घड़ी_check(काष्ठा nau8540 *nau8540, पूर्णांक rate, पूर्णांक osr)
अणु
	अगर (osr >= ARRAY_SIZE(osr_adc_sel))
		वापस -EINVAL;

	अगर (rate * osr > CLK_ADC_MAX) अणु
		dev_err(nau8540->dev, "exceed the maximum frequency of CLK_ADC\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nau8540_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा nau8540 *nau8540 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val_len = 0, osr;

	/* CLK_ADC = OSR * FS
	 * ADC घड़ी frequency is defined as Over Sampling Rate (OSR)
	 * multiplied by the audio sample rate (Fs). Note that the OSR and Fs
	 * values must be selected such that the maximum frequency is less
	 * than 6.144 MHz.
	 */
	regmap_पढ़ो(nau8540->regmap, NAU8540_REG_ADC_SAMPLE_RATE, &osr);
	osr &= NAU8540_ADC_OSR_MASK;
	अगर (nau8540_घड़ी_check(nau8540, params_rate(params), osr))
		वापस -EINVAL;
	regmap_update_bits(nau8540->regmap, NAU8540_REG_CLOCK_SRC,
		NAU8540_CLK_ADC_SRC_MASK,
		osr_adc_sel[osr].clk_src << NAU8540_CLK_ADC_SRC_SFT);

	चयन (params_width(params)) अणु
	हाल 16:
		val_len |= NAU8540_I2S_DL_16;
		अवरोध;
	हाल 20:
		val_len |= NAU8540_I2S_DL_20;
		अवरोध;
	हाल 24:
		val_len |= NAU8540_I2S_DL_24;
		अवरोध;
	हाल 32:
		val_len |= NAU8540_I2S_DL_32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(nau8540->regmap, NAU8540_REG_PCM_CTRL0,
		NAU8540_I2S_DL_MASK, val_len);

	वापस 0;
पूर्ण

अटल पूर्णांक nau8540_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा nau8540 *nau8540 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक ctrl1_val = 0, ctrl2_val = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		ctrl2_val |= NAU8540_I2S_MS_MASTER;
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
		ctrl1_val |= NAU8540_I2S_BP_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		ctrl1_val |= NAU8540_I2S_DF_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		ctrl1_val |= NAU8540_I2S_DF_LEFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		ctrl1_val |= NAU8540_I2S_DF_RIGTH;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		ctrl1_val |= NAU8540_I2S_DF_PCM_AB;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		ctrl1_val |= NAU8540_I2S_DF_PCM_AB;
		ctrl1_val |= NAU8540_I2S_PCMB_EN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(nau8540->regmap, NAU8540_REG_PCM_CTRL0,
		NAU8540_I2S_DL_MASK | NAU8540_I2S_DF_MASK |
		NAU8540_I2S_BP_INV | NAU8540_I2S_PCMB_EN, ctrl1_val);
	regmap_update_bits(nau8540->regmap, NAU8540_REG_PCM_CTRL1,
		NAU8540_I2S_MS_MASK | NAU8540_I2S_DO12_OE, ctrl2_val);
	regmap_update_bits(nau8540->regmap, NAU8540_REG_PCM_CTRL2,
		NAU8540_I2S_DO34_OE, 0);

	वापस 0;
पूर्ण

/**
 * nau8540_set_tdm_slot - configure DAI TX TDM.
 * @dai: DAI
 * @tx_mask: biपंचांगask representing active TX slots. Ex.
 *                 0xf क्रम normal 4 channel TDM.
 *                 0xf0 क्रम shअगरted 4 channel TDM
 * @rx_mask: no used.
 * @slots: Number of slots in use.
 * @slot_width: Width in bits क्रम each slot.
 *
 * Configures a DAI क्रम TDM operation. Only support 4 slots TDM.
 */
अटल पूर्णांक nau8540_set_tdm_slot(काष्ठा snd_soc_dai *dai,
	अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा nau8540 *nau8540 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक ctrl2_val = 0, ctrl4_val = 0;

	अगर (slots > 4 || ((tx_mask & 0xf0) && (tx_mask & 0xf)))
		वापस -EINVAL;

	ctrl4_val |= (NAU8540_TDM_MODE | NAU8540_TDM_OFFSET_EN);
	अगर (tx_mask & 0xf0) अणु
		ctrl2_val = 4 * slot_width;
		ctrl4_val |= (tx_mask >> 4);
	पूर्ण अन्यथा अणु
		ctrl4_val |= tx_mask;
	पूर्ण
	regmap_update_bits(nau8540->regmap, NAU8540_REG_PCM_CTRL4,
		NAU8540_TDM_MODE | NAU8540_TDM_OFFSET_EN |
		NAU8540_TDM_TX_MASK, ctrl4_val);
	regmap_update_bits(nau8540->regmap, NAU8540_REG_PCM_CTRL1,
		NAU8540_I2S_DO12_OE, NAU8540_I2S_DO12_OE);
	regmap_update_bits(nau8540->regmap, NAU8540_REG_PCM_CTRL2,
		NAU8540_I2S_DO34_OE | NAU8540_I2S_TSLOT_L_MASK,
		NAU8540_I2S_DO34_OE | ctrl2_val);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा snd_soc_dai_ops nau8540_dai_ops = अणु
	.hw_params = nau8540_hw_params,
	.set_fmt = nau8540_set_fmt,
	.set_tdm_slot = nau8540_set_tdm_slot,
पूर्ण;

#घोषणा NAU8540_RATES SNDRV_PCM_RATE_8000_48000
#घोषणा NAU8540_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE \
	 | SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver nau8540_dai = अणु
	.name = "nau8540-hifi",
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 4,
		.rates = NAU8540_RATES,
		.क्रमmats = NAU8540_FORMATS,
	पूर्ण,
	.ops = &nau8540_dai_ops,
पूर्ण;

/**
 * nau8540_calc_fll_param - Calculate FLL parameters.
 * @fll_in: बाह्यal घड़ी provided to codec.
 * @fs: sampling rate.
 * @fll_param: Poपूर्णांकer to काष्ठाure of FLL parameters.
 *
 * Calculate FLL parameters to configure codec.
 *
 * Returns 0 क्रम success or negative error code.
 */
अटल पूर्णांक nau8540_calc_fll_param(अचिन्हित पूर्णांक fll_in,
	अचिन्हित पूर्णांक fs, काष्ठा nau8540_fll *fll_param)
अणु
	u64 fvco, fvco_max;
	अचिन्हित पूर्णांक fref, i, fvco_sel;

	/* Ensure the reference घड़ी frequency (FREF) is <= 13.5MHz by भागiding
	 * freq_in by 1, 2, 4, or 8 using FLL pre-scalar.
	 * FREF = freq_in / NAU8540_FLL_REF_DIV_MASK
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

अटल व्योम nau8540_fll_apply(काष्ठा regmap *regmap,
	काष्ठा nau8540_fll *fll_param)
अणु
	regmap_update_bits(regmap, NAU8540_REG_CLOCK_SRC,
		NAU8540_CLK_SRC_MASK | NAU8540_CLK_MCLK_SRC_MASK,
		NAU8540_CLK_SRC_MCLK | fll_param->mclk_src);
	regmap_update_bits(regmap, NAU8540_REG_FLL1,
		NAU8540_FLL_RATIO_MASK | NAU8540_ICTRL_LATCH_MASK,
		fll_param->ratio | (0x6 << NAU8540_ICTRL_LATCH_SFT));
	/* FLL 16-bit fractional input */
	regmap_ग_लिखो(regmap, NAU8540_REG_FLL2, fll_param->fll_frac);
	/* FLL 10-bit पूर्णांकeger input */
	regmap_update_bits(regmap, NAU8540_REG_FLL3,
		NAU8540_FLL_INTEGER_MASK, fll_param->fll_पूर्णांक);
	/* FLL pre-scaler */
	regmap_update_bits(regmap, NAU8540_REG_FLL4,
		NAU8540_FLL_REF_DIV_MASK,
		fll_param->clk_ref_भाग << NAU8540_FLL_REF_DIV_SFT);
	regmap_update_bits(regmap, NAU8540_REG_FLL5,
		NAU8540_FLL_CLK_SW_MASK, NAU8540_FLL_CLK_SW_REF);
	regmap_update_bits(regmap,
		NAU8540_REG_FLL6, NAU8540_DCO_EN, 0);
	अगर (fll_param->fll_frac) अणु
		regmap_update_bits(regmap, NAU8540_REG_FLL5,
			NAU8540_FLL_PDB_DAC_EN | NAU8540_FLL_LOOP_FTR_EN |
			NAU8540_FLL_FTR_SW_MASK,
			NAU8540_FLL_PDB_DAC_EN | NAU8540_FLL_LOOP_FTR_EN |
			NAU8540_FLL_FTR_SW_FILTER);
		regmap_update_bits(regmap, NAU8540_REG_FLL6,
			NAU8540_SDM_EN | NAU8540_CUTOFF500,
			NAU8540_SDM_EN | NAU8540_CUTOFF500);
	पूर्ण अन्यथा अणु
		regmap_update_bits(regmap, NAU8540_REG_FLL5,
			NAU8540_FLL_PDB_DAC_EN | NAU8540_FLL_LOOP_FTR_EN |
			NAU8540_FLL_FTR_SW_MASK, NAU8540_FLL_FTR_SW_ACCU);
		regmap_update_bits(regmap, NAU8540_REG_FLL6,
			NAU8540_SDM_EN | NAU8540_CUTOFF500, 0);
	पूर्ण
पूर्ण

/* freq_out must be 256*Fs in order to achieve the best perक्रमmance */
अटल पूर्णांक nau8540_set_pll(काष्ठा snd_soc_component *component, पूर्णांक pll_id, पूर्णांक source,
		अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा nau8540 *nau8540 = snd_soc_component_get_drvdata(component);
	काष्ठा nau8540_fll fll_param;
	पूर्णांक ret, fs;

	चयन (pll_id) अणु
	हाल NAU8540_CLK_FLL_MCLK:
		regmap_update_bits(nau8540->regmap, NAU8540_REG_FLL3,
			NAU8540_FLL_CLK_SRC_MASK | NAU8540_GAIN_ERR_MASK,
			NAU8540_FLL_CLK_SRC_MCLK | 0);
		अवरोध;

	हाल NAU8540_CLK_FLL_BLK:
		regmap_update_bits(nau8540->regmap, NAU8540_REG_FLL3,
			NAU8540_FLL_CLK_SRC_MASK | NAU8540_GAIN_ERR_MASK,
			NAU8540_FLL_CLK_SRC_BLK |
			(0xf << NAU8540_GAIN_ERR_SFT));
		अवरोध;

	हाल NAU8540_CLK_FLL_FS:
		regmap_update_bits(nau8540->regmap, NAU8540_REG_FLL3,
			NAU8540_FLL_CLK_SRC_MASK | NAU8540_GAIN_ERR_MASK,
			NAU8540_FLL_CLK_SRC_FS |
			(0xf << NAU8540_GAIN_ERR_SFT));
		अवरोध;

	शेष:
		dev_err(nau8540->dev, "Invalid clock id (%d)\n", pll_id);
		वापस -EINVAL;
	पूर्ण
	dev_dbg(nau8540->dev, "Sysclk is %dHz and clock id is %d\n",
		freq_out, pll_id);

	fs = freq_out / 256;
	ret = nau8540_calc_fll_param(freq_in, fs, &fll_param);
	अगर (ret < 0) अणु
		dev_err(nau8540->dev, "Unsupported input clock %d\n", freq_in);
		वापस ret;
	पूर्ण
	dev_dbg(nau8540->dev, "mclk_src=%x ratio=%x fll_frac=%x fll_int=%x clk_ref_div=%x\n",
		fll_param.mclk_src, fll_param.ratio, fll_param.fll_frac,
		fll_param.fll_पूर्णांक, fll_param.clk_ref_भाग);

	nau8540_fll_apply(nau8540->regmap, &fll_param);
	mdelay(2);
	regmap_update_bits(nau8540->regmap, NAU8540_REG_CLOCK_SRC,
		NAU8540_CLK_SRC_MASK, NAU8540_CLK_SRC_VCO);

	वापस 0;
पूर्ण

अटल पूर्णांक nau8540_set_sysclk(काष्ठा snd_soc_component *component,
	पूर्णांक clk_id, पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा nau8540 *nau8540 = snd_soc_component_get_drvdata(component);

	चयन (clk_id) अणु
	हाल NAU8540_CLK_DIS:
	हाल NAU8540_CLK_MCLK:
		regmap_update_bits(nau8540->regmap, NAU8540_REG_CLOCK_SRC,
			NAU8540_CLK_SRC_MASK, NAU8540_CLK_SRC_MCLK);
		regmap_update_bits(nau8540->regmap, NAU8540_REG_FLL6,
			NAU8540_DCO_EN, 0);
		अवरोध;

	हाल NAU8540_CLK_INTERNAL:
		regmap_update_bits(nau8540->regmap, NAU8540_REG_FLL6,
			NAU8540_DCO_EN, NAU8540_DCO_EN);
		regmap_update_bits(nau8540->regmap, NAU8540_REG_CLOCK_SRC,
			NAU8540_CLK_SRC_MASK, NAU8540_CLK_SRC_VCO);
		अवरोध;

	शेष:
		dev_err(nau8540->dev, "Invalid clock id (%d)\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(nau8540->dev, "Sysclk is %dHz and clock id is %d\n",
		freq, clk_id);

	वापस 0;
पूर्ण

अटल व्योम nau8540_reset_chip(काष्ठा regmap *regmap)
अणु
	regmap_ग_लिखो(regmap, NAU8540_REG_SW_RESET, 0x00);
	regmap_ग_लिखो(regmap, NAU8540_REG_SW_RESET, 0x00);
पूर्ण

अटल व्योम nau8540_init_regs(काष्ठा nau8540 *nau8540)
अणु
	काष्ठा regmap *regmap = nau8540->regmap;

	/* Enable Bias/VMID/VMID Tieoff */
	regmap_update_bits(regmap, NAU8540_REG_VMID_CTRL,
		NAU8540_VMID_EN | NAU8540_VMID_SEL_MASK,
		NAU8540_VMID_EN | (0x2 << NAU8540_VMID_SEL_SFT));
	regmap_update_bits(regmap, NAU8540_REG_REFERENCE,
		NAU8540_PRECHARGE_DIS | NAU8540_GLOBAL_BIAS_EN,
		NAU8540_PRECHARGE_DIS | NAU8540_GLOBAL_BIAS_EN);
	mdelay(2);
	regmap_update_bits(regmap, NAU8540_REG_MIC_BIAS,
		NAU8540_PU_PRE, NAU8540_PU_PRE);
	regmap_update_bits(regmap, NAU8540_REG_CLOCK_CTRL,
		NAU8540_CLK_ADC_EN | NAU8540_CLK_I2S_EN,
		NAU8540_CLK_ADC_EN | NAU8540_CLK_I2S_EN);
	/* ADC OSR selection, CLK_ADC = Fs * OSR;
	 * Channel समय alignment enable.
	 */
	regmap_update_bits(regmap, NAU8540_REG_ADC_SAMPLE_RATE,
		NAU8540_CH_SYNC | NAU8540_ADC_OSR_MASK,
		NAU8540_CH_SYNC | NAU8540_ADC_OSR_64);
	/* PGA input mode selection */
	regmap_update_bits(regmap, NAU8540_REG_FEPGA1,
		NAU8540_FEPGA1_MODCH2_SHT | NAU8540_FEPGA1_MODCH1_SHT,
		NAU8540_FEPGA1_MODCH2_SHT | NAU8540_FEPGA1_MODCH1_SHT);
	regmap_update_bits(regmap, NAU8540_REG_FEPGA2,
		NAU8540_FEPGA2_MODCH4_SHT | NAU8540_FEPGA2_MODCH3_SHT,
		NAU8540_FEPGA2_MODCH4_SHT | NAU8540_FEPGA2_MODCH3_SHT);
	/* DO12 and DO34 pad output disable */
	regmap_update_bits(regmap, NAU8540_REG_PCM_CTRL1,
		NAU8540_I2S_DO12_TRI, NAU8540_I2S_DO12_TRI);
	regmap_update_bits(regmap, NAU8540_REG_PCM_CTRL2,
		NAU8540_I2S_DO34_TRI, NAU8540_I2S_DO34_TRI);
पूर्ण

अटल पूर्णांक __maybe_unused nau8540_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा nau8540 *nau8540 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(nau8540->regmap, true);
	regcache_mark_dirty(nau8540->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused nau8540_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा nau8540 *nau8540 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(nau8540->regmap, false);
	regcache_sync(nau8540->regmap);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver nau8540_component_driver = अणु
	.set_sysclk		= nau8540_set_sysclk,
	.set_pll		= nau8540_set_pll,
	.suspend		= nau8540_suspend,
	.resume			= nau8540_resume,
	.controls		= nau8540_snd_controls,
	.num_controls		= ARRAY_SIZE(nau8540_snd_controls),
	.dapm_widमाला_लो		= nau8540_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(nau8540_dapm_widमाला_लो),
	.dapm_routes		= nau8540_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(nau8540_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config nau8540_regmap_config = अणु
	.val_bits = 16,
	.reg_bits = 16,

	.max_रेजिस्टर = NAU8540_REG_MAX,
	.पढ़ोable_reg = nau8540_पढ़ोable_reg,
	.ग_लिखोable_reg = nau8540_ग_लिखोable_reg,
	.अस्थिर_reg = nau8540_अस्थिर_reg,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = nau8540_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(nau8540_reg_शेषs),
पूर्ण;

अटल पूर्णांक nau8540_i2c_probe(काष्ठा i2c_client *i2c,
	स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &i2c->dev;
	काष्ठा nau8540 *nau8540 = dev_get_platdata(dev);
	पूर्णांक ret, value;

	अगर (!nau8540) अणु
		nau8540 = devm_kzalloc(dev, माप(*nau8540), GFP_KERNEL);
		अगर (!nau8540)
			वापस -ENOMEM;
	पूर्ण
	i2c_set_clientdata(i2c, nau8540);

	nau8540->regmap = devm_regmap_init_i2c(i2c, &nau8540_regmap_config);
	अगर (IS_ERR(nau8540->regmap))
		वापस PTR_ERR(nau8540->regmap);
	ret = regmap_पढ़ो(nau8540->regmap, NAU8540_REG_I2C_DEVICE_ID, &value);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read device id from the NAU85L40: %d\n",
			ret);
		वापस ret;
	पूर्ण

	nau8540->dev = dev;
	nau8540_reset_chip(nau8540->regmap);
	nau8540_init_regs(nau8540);

	वापस devm_snd_soc_रेजिस्टर_component(dev,
		&nau8540_component_driver, &nau8540_dai, 1);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id nau8540_i2c_ids[] = अणु
	अणु "nau8540", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, nau8540_i2c_ids);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id nau8540_of_ids[] = अणु
	अणु .compatible = "nuvoton,nau8540", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, nau8540_of_ids);
#पूर्ण_अगर

अटल काष्ठा i2c_driver nau8540_i2c_driver = अणु
	.driver = अणु
		.name = "nau8540",
		.of_match_table = of_match_ptr(nau8540_of_ids),
	पूर्ण,
	.probe = nau8540_i2c_probe,
	.id_table = nau8540_i2c_ids,
पूर्ण;
module_i2c_driver(nau8540_i2c_driver);

MODULE_DESCRIPTION("ASoC NAU85L40 driver");
MODULE_AUTHOR("John Hsu <KCHSU0@nuvoton.com>");
MODULE_LICENSE("GPL v2");
