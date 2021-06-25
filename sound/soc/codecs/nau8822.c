<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// nau8822.c  --  NAU8822 ALSA Soc Audio driver
//
// Copyright 2017 Nuvoton Technology Crop.
//
// Author: David Lin <ctlin0@nuvoton.com>
// Co-author: John Hsu <kchsu0@nuvoton.com>
// Co-author: Seven Li <wtli@nuvoton.com>
//
// Based on WM8974.c

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <यंत्र/भाग64.h>
#समावेश "nau8822.h"

#घोषणा NAU_PLL_FREQ_MAX 100000000
#घोषणा NAU_PLL_FREQ_MIN 90000000
#घोषणा NAU_PLL_REF_MAX 33000000
#घोषणा NAU_PLL_REF_MIN 8000000
#घोषणा NAU_PLL_OPTOP_MIN 6

अटल स्थिर पूर्णांक nau8822_mclk_scaler[] = अणु 10, 15, 20, 30, 40, 60, 80, 120 पूर्ण;

अटल स्थिर काष्ठा reg_शेष nau8822_reg_शेषs[] = अणु
	अणु NAU8822_REG_POWER_MANAGEMENT_1, 0x0000 पूर्ण,
	अणु NAU8822_REG_POWER_MANAGEMENT_2, 0x0000 पूर्ण,
	अणु NAU8822_REG_POWER_MANAGEMENT_3, 0x0000 पूर्ण,
	अणु NAU8822_REG_AUDIO_INTERFACE, 0x0050 पूर्ण,
	अणु NAU8822_REG_COMPANDING_CONTROL, 0x0000 पूर्ण,
	अणु NAU8822_REG_CLOCKING, 0x0140 पूर्ण,
	अणु NAU8822_REG_ADDITIONAL_CONTROL, 0x0000 पूर्ण,
	अणु NAU8822_REG_GPIO_CONTROL, 0x0000 पूर्ण,
	अणु NAU8822_REG_JACK_DETECT_CONTROL_1, 0x0000 पूर्ण,
	अणु NAU8822_REG_DAC_CONTROL, 0x0000 पूर्ण,
	अणु NAU8822_REG_LEFT_DAC_DIGITAL_VOLUME, 0x00ff पूर्ण,
	अणु NAU8822_REG_RIGHT_DAC_DIGITAL_VOLUME, 0x00ff पूर्ण,
	अणु NAU8822_REG_JACK_DETECT_CONTROL_2, 0x0000 पूर्ण,
	अणु NAU8822_REG_ADC_CONTROL, 0x0100 पूर्ण,
	अणु NAU8822_REG_LEFT_ADC_DIGITAL_VOLUME, 0x00ff पूर्ण,
	अणु NAU8822_REG_RIGHT_ADC_DIGITAL_VOLUME, 0x00ff पूर्ण,
	अणु NAU8822_REG_EQ1, 0x012c पूर्ण,
	अणु NAU8822_REG_EQ2, 0x002c पूर्ण,
	अणु NAU8822_REG_EQ3, 0x002c पूर्ण,
	अणु NAU8822_REG_EQ4, 0x002c पूर्ण,
	अणु NAU8822_REG_EQ5, 0x002c पूर्ण,
	अणु NAU8822_REG_DAC_LIMITER_1, 0x0032 पूर्ण,
	अणु NAU8822_REG_DAC_LIMITER_2, 0x0000 पूर्ण,
	अणु NAU8822_REG_NOTCH_FILTER_1, 0x0000 पूर्ण,
	अणु NAU8822_REG_NOTCH_FILTER_2, 0x0000 पूर्ण,
	अणु NAU8822_REG_NOTCH_FILTER_3, 0x0000 पूर्ण,
	अणु NAU8822_REG_NOTCH_FILTER_4, 0x0000 पूर्ण,
	अणु NAU8822_REG_ALC_CONTROL_1, 0x0038 पूर्ण,
	अणु NAU8822_REG_ALC_CONTROL_2, 0x000b पूर्ण,
	अणु NAU8822_REG_ALC_CONTROL_3, 0x0032 पूर्ण,
	अणु NAU8822_REG_NOISE_GATE, 0x0010 पूर्ण,
	अणु NAU8822_REG_PLL_N, 0x0008 पूर्ण,
	अणु NAU8822_REG_PLL_K1, 0x000c पूर्ण,
	अणु NAU8822_REG_PLL_K2, 0x0093 पूर्ण,
	अणु NAU8822_REG_PLL_K3, 0x00e9 पूर्ण,
	अणु NAU8822_REG_3D_CONTROL, 0x0000 पूर्ण,
	अणु NAU8822_REG_RIGHT_SPEAKER_CONTROL, 0x0000 पूर्ण,
	अणु NAU8822_REG_INPUT_CONTROL, 0x0033 पूर्ण,
	अणु NAU8822_REG_LEFT_INP_PGA_CONTROL, 0x0010 पूर्ण,
	अणु NAU8822_REG_RIGHT_INP_PGA_CONTROL, 0x0010 पूर्ण,
	अणु NAU8822_REG_LEFT_ADC_BOOST_CONTROL, 0x0100 पूर्ण,
	अणु NAU8822_REG_RIGHT_ADC_BOOST_CONTROL, 0x0100 पूर्ण,
	अणु NAU8822_REG_OUTPUT_CONTROL, 0x0002 पूर्ण,
	अणु NAU8822_REG_LEFT_MIXER_CONTROL, 0x0001 पूर्ण,
	अणु NAU8822_REG_RIGHT_MIXER_CONTROL, 0x0001 पूर्ण,
	अणु NAU8822_REG_LHP_VOLUME, 0x0039 पूर्ण,
	अणु NAU8822_REG_RHP_VOLUME, 0x0039 पूर्ण,
	अणु NAU8822_REG_LSPKOUT_VOLUME, 0x0039 पूर्ण,
	अणु NAU8822_REG_RSPKOUT_VOLUME, 0x0039 पूर्ण,
	अणु NAU8822_REG_AUX2_MIXER, 0x0001 पूर्ण,
	अणु NAU8822_REG_AUX1_MIXER, 0x0001 पूर्ण,
	अणु NAU8822_REG_POWER_MANAGEMENT_4, 0x0000 पूर्ण,
	अणु NAU8822_REG_LEFT_TIME_SLOT, 0x0000 पूर्ण,
	अणु NAU8822_REG_MISC, 0x0020 पूर्ण,
	अणु NAU8822_REG_RIGHT_TIME_SLOT, 0x0000 पूर्ण,
	अणु NAU8822_REG_DEVICE_REVISION, 0x007f पूर्ण,
	अणु NAU8822_REG_DEVICE_ID, 0x001a पूर्ण,
	अणु NAU8822_REG_DAC_DITHER, 0x0114 पूर्ण,
	अणु NAU8822_REG_ALC_ENHANCE_1, 0x0000 पूर्ण,
	अणु NAU8822_REG_ALC_ENHANCE_2, 0x0000 पूर्ण,
	अणु NAU8822_REG_192KHZ_SAMPLING, 0x0008 पूर्ण,
	अणु NAU8822_REG_MISC_CONTROL, 0x0000 पूर्ण,
	अणु NAU8822_REG_INPUT_TIखातापूर्णF, 0x0000 पूर्ण,
	अणु NAU8822_REG_POWER_REDUCTION, 0x0000 पूर्ण,
	अणु NAU8822_REG_AGC_PEAK2PEAK, 0x0000 पूर्ण,
	अणु NAU8822_REG_AGC_PEAK_DETECT, 0x0000 पूर्ण,
	अणु NAU8822_REG_AUTOMUTE_CONTROL, 0x0000 पूर्ण,
	अणु NAU8822_REG_OUTPUT_TIखातापूर्णF, 0x0000 पूर्ण,
पूर्ण;

अटल bool nau8822_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल NAU8822_REG_RESET ... NAU8822_REG_JACK_DETECT_CONTROL_1:
	हाल NAU8822_REG_DAC_CONTROL ... NAU8822_REG_LEFT_ADC_DIGITAL_VOLUME:
	हाल NAU8822_REG_RIGHT_ADC_DIGITAL_VOLUME:
	हाल NAU8822_REG_EQ1 ... NAU8822_REG_EQ5:
	हाल NAU8822_REG_DAC_LIMITER_1 ... NAU8822_REG_DAC_LIMITER_2:
	हाल NAU8822_REG_NOTCH_FILTER_1 ... NAU8822_REG_NOTCH_FILTER_4:
	हाल NAU8822_REG_ALC_CONTROL_1 ...NAU8822_REG_PLL_K3:
	हाल NAU8822_REG_3D_CONTROL:
	हाल NAU8822_REG_RIGHT_SPEAKER_CONTROL:
	हाल NAU8822_REG_INPUT_CONTROL ... NAU8822_REG_LEFT_ADC_BOOST_CONTROL:
	हाल NAU8822_REG_RIGHT_ADC_BOOST_CONTROL ... NAU8822_REG_AUX1_MIXER:
	हाल NAU8822_REG_POWER_MANAGEMENT_4 ... NAU8822_REG_DEVICE_ID:
	हाल NAU8822_REG_DAC_DITHER:
	हाल NAU8822_REG_ALC_ENHANCE_1 ... NAU8822_REG_MISC_CONTROL:
	हाल NAU8822_REG_INPUT_TIखातापूर्णF ... NAU8822_REG_OUTPUT_TIखातापूर्णF:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool nau8822_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल NAU8822_REG_RESET ... NAU8822_REG_JACK_DETECT_CONTROL_1:
	हाल NAU8822_REG_DAC_CONTROL ... NAU8822_REG_LEFT_ADC_DIGITAL_VOLUME:
	हाल NAU8822_REG_RIGHT_ADC_DIGITAL_VOLUME:
	हाल NAU8822_REG_EQ1 ... NAU8822_REG_EQ5:
	हाल NAU8822_REG_DAC_LIMITER_1 ... NAU8822_REG_DAC_LIMITER_2:
	हाल NAU8822_REG_NOTCH_FILTER_1 ... NAU8822_REG_NOTCH_FILTER_4:
	हाल NAU8822_REG_ALC_CONTROL_1 ...NAU8822_REG_PLL_K3:
	हाल NAU8822_REG_3D_CONTROL:
	हाल NAU8822_REG_RIGHT_SPEAKER_CONTROL:
	हाल NAU8822_REG_INPUT_CONTROL ... NAU8822_REG_LEFT_ADC_BOOST_CONTROL:
	हाल NAU8822_REG_RIGHT_ADC_BOOST_CONTROL ... NAU8822_REG_AUX1_MIXER:
	हाल NAU8822_REG_POWER_MANAGEMENT_4 ... NAU8822_REG_DEVICE_ID:
	हाल NAU8822_REG_DAC_DITHER:
	हाल NAU8822_REG_ALC_ENHANCE_1 ... NAU8822_REG_MISC_CONTROL:
	हाल NAU8822_REG_INPUT_TIखातापूर्णF ... NAU8822_REG_OUTPUT_TIखातापूर्णF:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool nau8822_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल NAU8822_REG_RESET:
	हाल NAU8822_REG_DEVICE_REVISION:
	हाल NAU8822_REG_DEVICE_ID:
	हाल NAU8822_REG_AGC_PEAK2PEAK:
	हाल NAU8822_REG_AGC_PEAK_DETECT:
	हाल NAU8822_REG_AUTOMUTE_CONTROL:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/* The EQ parameters get function is to get the 5 band equalizer control.
 * The regmap raw पढ़ो can't work here because regmap doesn't provide
 * value क्रमmat क्रम value width of 9 bits. Thereक्रमe, the driver पढ़ोs data
 * from cache and makes value क्रमmat according to the endianness of
 * bytes type control element.
 */
अटल पूर्णांक nau8822_eq_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
			snd_soc_kcontrol_component(kcontrol);
	काष्ठा soc_bytes_ext *params = (व्योम *)kcontrol->निजी_value;
	पूर्णांक i, reg;
	u16 reg_val, *val;

	val = (u16 *)ucontrol->value.bytes.data;
	reg = NAU8822_REG_EQ1;
	क्रम (i = 0; i < params->max / माप(u16); i++) अणु
		reg_val = snd_soc_component_पढ़ो(component, reg + i);
		/* conversion of 16-bit पूर्णांकegers between native CPU क्रमmat
		 * and big endian क्रमmat
		 */
		reg_val = cpu_to_be16(reg_val);
		स_नकल(val + i, &reg_val, माप(reg_val));
	पूर्ण

	वापस 0;
पूर्ण

/* The EQ parameters put function is to make configuration of 5 band equalizer
 * control. These configuration includes central frequency, equalizer gain,
 * cut-off frequency, bandwidth control, and equalizer path.
 * The regmap raw ग_लिखो can't work here because regmap doesn't provide
 * रेजिस्टर and value क्रमmat क्रम रेजिस्टर with address 7 bits and value 9 bits.
 * Thereक्रमe, the driver makes value क्रमmat according to the endianness of
 * bytes type control element and ग_लिखोs data to codec.
 */
अटल पूर्णांक nau8822_eq_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
			snd_soc_kcontrol_component(kcontrol);
	काष्ठा soc_bytes_ext *params = (व्योम *)kcontrol->निजी_value;
	व्योम *data;
	u16 *val, value;
	पूर्णांक i, reg, ret;

	data = kmemdup(ucontrol->value.bytes.data,
		params->max, GFP_KERNEL | GFP_DMA);
	अगर (!data)
		वापस -ENOMEM;

	val = (u16 *)data;
	reg = NAU8822_REG_EQ1;
	क्रम (i = 0; i < params->max / माप(u16); i++) अणु
		/* conversion of 16-bit पूर्णांकegers between native CPU क्रमmat
		 * and big endian क्रमmat
		 */
		value = be16_to_cpu(*(val + i));
		ret = snd_soc_component_ग_लिखो(component, reg + i, value);
		अगर (ret) अणु
			dev_err(component->dev,
			    "EQ configuration fail, register: %x ret: %d\n",
			    reg + i, ret);
			kमुक्त(data);
			वापस ret;
		पूर्ण
	पूर्ण
	kमुक्त(data);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर nau8822_companding[] = अणु
	"Off", "NC", "u-law", "A-law"पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत nau8822_companding_adc_क्रमागत =
	SOC_ENUM_SINGLE(NAU8822_REG_COMPANDING_CONTROL, NAU8822_ADCCM_SFT,
		ARRAY_SIZE(nau8822_companding), nau8822_companding);

अटल स्थिर काष्ठा soc_क्रमागत nau8822_companding_dac_क्रमागत =
	SOC_ENUM_SINGLE(NAU8822_REG_COMPANDING_CONTROL, NAU8822_DACCM_SFT,
		ARRAY_SIZE(nau8822_companding), nau8822_companding);

अटल स्थिर अक्षर * स्थिर nau8822_eqmode[] = अणु"Capture", "Playback"पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत nau8822_eqmode_क्रमागत =
	SOC_ENUM_SINGLE(NAU8822_REG_EQ1, NAU8822_EQM_SFT,
		ARRAY_SIZE(nau8822_eqmode), nau8822_eqmode);

अटल स्थिर अक्षर * स्थिर nau8822_alc1[] = अणु"Off", "Right", "Left", "Both"पूर्ण;
अटल स्थिर अक्षर * स्थिर nau8822_alc3[] = अणु"Normal", "Limiter"पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत nau8822_alc_enable_क्रमागत =
	SOC_ENUM_SINGLE(NAU8822_REG_ALC_CONTROL_1, NAU8822_ALCEN_SFT,
		ARRAY_SIZE(nau8822_alc1), nau8822_alc1);

अटल स्थिर काष्ठा soc_क्रमागत nau8822_alc_mode_क्रमागत =
	SOC_ENUM_SINGLE(NAU8822_REG_ALC_CONTROL_3, NAU8822_ALCM_SFT,
		ARRAY_SIZE(nau8822_alc3), nau8822_alc3);

अटल स्थिर DECLARE_TLV_DB_SCALE(digital_tlv, -12750, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(inpga_tlv, -1200, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(spk_tlv, -5700, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(pga_boost_tlv, 0, 2000, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(boost_tlv, -1500, 300, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(limiter_tlv, 0, 100, 0);

अटल स्थिर काष्ठा snd_kcontrol_new nau8822_snd_controls[] = अणु
	SOC_ENUM("ADC Companding", nau8822_companding_adc_क्रमागत),
	SOC_ENUM("DAC Companding", nau8822_companding_dac_क्रमागत),

	SOC_ENUM("EQ Function", nau8822_eqmode_क्रमागत),
	SND_SOC_BYTES_EXT("EQ Parameters", 10,
		  nau8822_eq_get, nau8822_eq_put),

	SOC_DOUBLE("DAC Inversion Switch",
		NAU8822_REG_DAC_CONTROL, 0, 1, 1, 0),
	SOC_DOUBLE_R_TLV("PCM Volume",
		NAU8822_REG_LEFT_DAC_DIGITAL_VOLUME,
		NAU8822_REG_RIGHT_DAC_DIGITAL_VOLUME, 0, 255, 0, digital_tlv),

	SOC_SINGLE("High Pass Filter Switch",
		NAU8822_REG_ADC_CONTROL, 8, 1, 0),
	SOC_SINGLE("High Pass Cut Off",
		NAU8822_REG_ADC_CONTROL, 4, 7, 0),

	SOC_DOUBLE("ADC Inversion Switch",
		NAU8822_REG_ADC_CONTROL, 0, 1, 1, 0),
	SOC_DOUBLE_R_TLV("ADC Volume",
		NAU8822_REG_LEFT_ADC_DIGITAL_VOLUME,
		NAU8822_REG_RIGHT_ADC_DIGITAL_VOLUME, 0, 255, 0, digital_tlv),

	SOC_SINGLE("DAC Limiter Switch",
		NAU8822_REG_DAC_LIMITER_1, 8, 1, 0),
	SOC_SINGLE("DAC Limiter Decay",
		NAU8822_REG_DAC_LIMITER_1, 4, 15, 0),
	SOC_SINGLE("DAC Limiter Attack",
		NAU8822_REG_DAC_LIMITER_1, 0, 15, 0),
	SOC_SINGLE("DAC Limiter Threshold",
		NAU8822_REG_DAC_LIMITER_2, 4, 7, 0),
	SOC_SINGLE_TLV("DAC Limiter Volume",
		NAU8822_REG_DAC_LIMITER_2, 0, 12, 0, limiter_tlv),

	SOC_ENUM("ALC Mode", nau8822_alc_mode_क्रमागत),
	SOC_ENUM("ALC Enable Switch", nau8822_alc_enable_क्रमागत),
	SOC_SINGLE("ALC Min Gain",
		NAU8822_REG_ALC_CONTROL_1, 0, 7, 0),
	SOC_SINGLE("ALC Max Gain",
		NAU8822_REG_ALC_CONTROL_1, 3, 7, 0),
	SOC_SINGLE("ALC Hold",
		NAU8822_REG_ALC_CONTROL_2, 4, 10, 0),
	SOC_SINGLE("ALC Target",
		NAU8822_REG_ALC_CONTROL_2, 0, 15, 0),
	SOC_SINGLE("ALC Decay",
		NAU8822_REG_ALC_CONTROL_3, 4, 10, 0),
	SOC_SINGLE("ALC Attack",
		NAU8822_REG_ALC_CONTROL_3, 0, 10, 0),
	SOC_SINGLE("ALC Noise Gate Switch",
		NAU8822_REG_NOISE_GATE, 3, 1, 0),
	SOC_SINGLE("ALC Noise Gate Threshold",
		NAU8822_REG_NOISE_GATE, 0, 7, 0),

	SOC_DOUBLE_R("PGA ZC Switch",
		NAU8822_REG_LEFT_INP_PGA_CONTROL,
		NAU8822_REG_RIGHT_INP_PGA_CONTROL,
		7, 1, 0),
	SOC_DOUBLE_R_TLV("PGA Volume",
		NAU8822_REG_LEFT_INP_PGA_CONTROL,
		NAU8822_REG_RIGHT_INP_PGA_CONTROL, 0, 63, 0, inpga_tlv),

	SOC_DOUBLE_R("Headphone ZC Switch",
		NAU8822_REG_LHP_VOLUME,
		NAU8822_REG_RHP_VOLUME, 7, 1, 0),
	SOC_DOUBLE_R("Headphone Playback Switch",
		NAU8822_REG_LHP_VOLUME,
		NAU8822_REG_RHP_VOLUME, 6, 1, 1),
	SOC_DOUBLE_R_TLV("Headphone Volume",
		NAU8822_REG_LHP_VOLUME,
		NAU8822_REG_RHP_VOLUME,	0, 63, 0, spk_tlv),

	SOC_DOUBLE_R("Speaker ZC Switch",
		NAU8822_REG_LSPKOUT_VOLUME,
		NAU8822_REG_RSPKOUT_VOLUME, 7, 1, 0),
	SOC_DOUBLE_R("Speaker Playback Switch",
		NAU8822_REG_LSPKOUT_VOLUME,
		NAU8822_REG_RSPKOUT_VOLUME, 6, 1, 1),
	SOC_DOUBLE_R_TLV("Speaker Volume",
		NAU8822_REG_LSPKOUT_VOLUME,
		NAU8822_REG_RSPKOUT_VOLUME, 0, 63, 0, spk_tlv),

	SOC_DOUBLE_R("AUXOUT Playback Switch",
		NAU8822_REG_AUX2_MIXER,
		NAU8822_REG_AUX1_MIXER, 6, 1, 1),

	SOC_DOUBLE_R_TLV("PGA Boost Volume",
		NAU8822_REG_LEFT_ADC_BOOST_CONTROL,
		NAU8822_REG_RIGHT_ADC_BOOST_CONTROL, 8, 1, 0, pga_boost_tlv),
	SOC_DOUBLE_R_TLV("L2/R2 Boost Volume",
		NAU8822_REG_LEFT_ADC_BOOST_CONTROL,
		NAU8822_REG_RIGHT_ADC_BOOST_CONTROL, 4, 7, 0, boost_tlv),
	SOC_DOUBLE_R_TLV("Aux Boost Volume",
		NAU8822_REG_LEFT_ADC_BOOST_CONTROL,
		NAU8822_REG_RIGHT_ADC_BOOST_CONTROL, 0, 7, 0, boost_tlv),

	SOC_SINGLE("DAC 128x Oversampling Switch",
		NAU8822_REG_DAC_CONTROL, 5, 1, 0),
	SOC_SINGLE("ADC 128x Oversampling Switch",
		NAU8822_REG_ADC_CONTROL, 5, 1, 0),
पूर्ण;

/* LMAIN and RMAIN Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new nau8822_left_out_mixer[] = अणु
	SOC_DAPM_SINGLE("LINMIX Switch",
		NAU8822_REG_LEFT_MIXER_CONTROL, 1, 1, 0),
	SOC_DAPM_SINGLE("LAUX Switch",
		NAU8822_REG_LEFT_MIXER_CONTROL, 5, 1, 0),
	SOC_DAPM_SINGLE("LDAC Switch",
		NAU8822_REG_LEFT_MIXER_CONTROL, 0, 1, 0),
	SOC_DAPM_SINGLE("RDAC Switch",
		NAU8822_REG_OUTPUT_CONTROL, 5, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new nau8822_right_out_mixer[] = अणु
	SOC_DAPM_SINGLE("RINMIX Switch",
		NAU8822_REG_RIGHT_MIXER_CONTROL, 1, 1, 0),
	SOC_DAPM_SINGLE("RAUX Switch",
		NAU8822_REG_RIGHT_MIXER_CONTROL, 5, 1, 0),
	SOC_DAPM_SINGLE("RDAC Switch",
		NAU8822_REG_RIGHT_MIXER_CONTROL, 0, 1, 0),
	SOC_DAPM_SINGLE("LDAC Switch",
		NAU8822_REG_OUTPUT_CONTROL, 6, 1, 0),
पूर्ण;

/* AUX1 and AUX2 Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new nau8822_auxout1_mixer[] = अणु
	SOC_DAPM_SINGLE("RDAC Switch", NAU8822_REG_AUX1_MIXER, 0, 1, 0),
	SOC_DAPM_SINGLE("RMIX Switch", NAU8822_REG_AUX1_MIXER, 1, 1, 0),
	SOC_DAPM_SINGLE("RINMIX Switch", NAU8822_REG_AUX1_MIXER, 2, 1, 0),
	SOC_DAPM_SINGLE("LDAC Switch", NAU8822_REG_AUX1_MIXER, 3, 1, 0),
	SOC_DAPM_SINGLE("LMIX Switch", NAU8822_REG_AUX1_MIXER, 4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new nau8822_auxout2_mixer[] = अणु
	SOC_DAPM_SINGLE("LDAC Switch", NAU8822_REG_AUX2_MIXER, 0, 1, 0),
	SOC_DAPM_SINGLE("LMIX Switch", NAU8822_REG_AUX2_MIXER, 1, 1, 0),
	SOC_DAPM_SINGLE("LINMIX Switch", NAU8822_REG_AUX2_MIXER, 2, 1, 0),
	SOC_DAPM_SINGLE("AUX1MIX Output Switch",
		NAU8822_REG_AUX2_MIXER, 3, 1, 0),
पूर्ण;

/* Input PGA */
अटल स्थिर काष्ठा snd_kcontrol_new nau8822_left_input_mixer[] = अणु
	SOC_DAPM_SINGLE("L2 Switch", NAU8822_REG_INPUT_CONTROL, 2, 1, 0),
	SOC_DAPM_SINGLE("MicN Switch", NAU8822_REG_INPUT_CONTROL, 1, 1, 0),
	SOC_DAPM_SINGLE("MicP Switch", NAU8822_REG_INPUT_CONTROL, 0, 1, 0),
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new nau8822_right_input_mixer[] = अणु
	SOC_DAPM_SINGLE("R2 Switch", NAU8822_REG_INPUT_CONTROL, 6, 1, 0),
	SOC_DAPM_SINGLE("MicN Switch", NAU8822_REG_INPUT_CONTROL, 5, 1, 0),
	SOC_DAPM_SINGLE("MicP Switch", NAU8822_REG_INPUT_CONTROL, 4, 1, 0),
पूर्ण;

/* Loopback Switch */
अटल स्थिर काष्ठा snd_kcontrol_new nau8822_loopback =
	SOC_DAPM_SINGLE("Switch", NAU8822_REG_COMPANDING_CONTROL,
		NAU8822_ADDAP_SFT, 1, 0);

अटल पूर्णांक check_mclk_select_pll(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(source->dapm);
	अचिन्हित पूर्णांक value;

	value = snd_soc_component_पढ़ो(component, NAU8822_REG_CLOCKING);

	वापस (value & NAU8822_CLKM_MASK);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget nau8822_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("Left DAC", "Left HiFi Playback",
		NAU8822_REG_POWER_MANAGEMENT_3, 0, 0),
	SND_SOC_DAPM_DAC("Right DAC", "Right HiFi Playback",
		NAU8822_REG_POWER_MANAGEMENT_3, 1, 0),
	SND_SOC_DAPM_ADC("Left ADC", "Left HiFi Capture",
		NAU8822_REG_POWER_MANAGEMENT_2, 0, 0),
	SND_SOC_DAPM_ADC("Right ADC", "Right HiFi Capture",
		NAU8822_REG_POWER_MANAGEMENT_2, 1, 0),

	SOC_MIXER_ARRAY("Left Output Mixer",
		NAU8822_REG_POWER_MANAGEMENT_3, 2, 0, nau8822_left_out_mixer),
	SOC_MIXER_ARRAY("Right Output Mixer",
		NAU8822_REG_POWER_MANAGEMENT_3,	3, 0, nau8822_right_out_mixer),
	SOC_MIXER_ARRAY("AUX1 Output Mixer",
		NAU8822_REG_POWER_MANAGEMENT_1, 7, 0, nau8822_auxout1_mixer),
	SOC_MIXER_ARRAY("AUX2 Output Mixer",
		NAU8822_REG_POWER_MANAGEMENT_1,	6, 0, nau8822_auxout2_mixer),

	SOC_MIXER_ARRAY("Left Input Mixer",
		NAU8822_REG_POWER_MANAGEMENT_2,
		2, 0, nau8822_left_input_mixer),
	SOC_MIXER_ARRAY("Right Input Mixer",
		NAU8822_REG_POWER_MANAGEMENT_2,
		3, 0, nau8822_right_input_mixer),

	SND_SOC_DAPM_PGA("Left Boost Mixer",
		NAU8822_REG_POWER_MANAGEMENT_2, 4, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Boost Mixer",
		NAU8822_REG_POWER_MANAGEMENT_2, 5, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("Left Capture PGA",
		NAU8822_REG_LEFT_INP_PGA_CONTROL, 6, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Capture PGA",
		NAU8822_REG_RIGHT_INP_PGA_CONTROL, 6, 1, शून्य, 0),

	SND_SOC_DAPM_PGA("Left Headphone Out",
		NAU8822_REG_POWER_MANAGEMENT_2, 7, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Headphone Out",
		NAU8822_REG_POWER_MANAGEMENT_2, 8, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("Left Speaker Out",
		 NAU8822_REG_POWER_MANAGEMENT_3, 6, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Speaker Out",
		NAU8822_REG_POWER_MANAGEMENT_3,	5, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("AUX1 Out",
		NAU8822_REG_POWER_MANAGEMENT_3,	8, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("AUX2 Out",
		NAU8822_REG_POWER_MANAGEMENT_3,	7, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("Mic Bias",
		NAU8822_REG_POWER_MANAGEMENT_1,	4, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL",
		NAU8822_REG_POWER_MANAGEMENT_1,	5, 0, शून्य, 0),

	SND_SOC_DAPM_SWITCH("Digital Loopback", SND_SOC_NOPM, 0, 0,
		&nau8822_loopback),

	SND_SOC_DAPM_INPUT("LMICN"),
	SND_SOC_DAPM_INPUT("LMICP"),
	SND_SOC_DAPM_INPUT("RMICN"),
	SND_SOC_DAPM_INPUT("RMICP"),
	SND_SOC_DAPM_INPUT("LAUX"),
	SND_SOC_DAPM_INPUT("RAUX"),
	SND_SOC_DAPM_INPUT("L2"),
	SND_SOC_DAPM_INPUT("R2"),
	SND_SOC_DAPM_OUTPUT("LHP"),
	SND_SOC_DAPM_OUTPUT("RHP"),
	SND_SOC_DAPM_OUTPUT("LSPK"),
	SND_SOC_DAPM_OUTPUT("RSPK"),
	SND_SOC_DAPM_OUTPUT("AUXOUT1"),
	SND_SOC_DAPM_OUTPUT("AUXOUT2"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route nau8822_dapm_routes[] = अणु
	अणु"Right DAC", शून्य, "PLL", check_mclk_select_pllपूर्ण,
	अणु"Left DAC", शून्य, "PLL", check_mclk_select_pllपूर्ण,

	/* LMAIN and RMAIN Mixer */
	अणु"Right Output Mixer", "LDAC Switch", "Left DAC"पूर्ण,
	अणु"Right Output Mixer", "RDAC Switch", "Right DAC"पूर्ण,
	अणु"Right Output Mixer", "RAUX Switch", "RAUX"पूर्ण,
	अणु"Right Output Mixer", "RINMIX Switch", "Right Boost Mixer"पूर्ण,

	अणु"Left Output Mixer", "LDAC Switch", "Left DAC"पूर्ण,
	अणु"Left Output Mixer", "RDAC Switch", "Right DAC"पूर्ण,
	अणु"Left Output Mixer", "LAUX Switch", "LAUX"पूर्ण,
	अणु"Left Output Mixer", "LINMIX Switch", "Left Boost Mixer"पूर्ण,

	/* AUX1 and AUX2 Mixer */
	अणु"AUX1 Output Mixer", "RDAC Switch", "Right DAC"पूर्ण,
	अणु"AUX1 Output Mixer", "RMIX Switch", "Right Output Mixer"पूर्ण,
	अणु"AUX1 Output Mixer", "RINMIX Switch", "Right Boost Mixer"पूर्ण,
	अणु"AUX1 Output Mixer", "LDAC Switch", "Left DAC"पूर्ण,
	अणु"AUX1 Output Mixer", "LMIX Switch", "Left Output Mixer"पूर्ण,

	अणु"AUX2 Output Mixer", "LDAC Switch", "Left DAC"पूर्ण,
	अणु"AUX2 Output Mixer", "LMIX Switch", "Left Output Mixer"पूर्ण,
	अणु"AUX2 Output Mixer", "LINMIX Switch", "Left Boost Mixer"पूर्ण,
	अणु"AUX2 Output Mixer", "AUX1MIX Output Switch", "AUX1 Output Mixer"पूर्ण,

	/* Outमाला_दो */
	अणु"Right Headphone Out", शून्य, "Right Output Mixer"पूर्ण,
	अणु"RHP", शून्य, "Right Headphone Out"पूर्ण,

	अणु"Left Headphone Out", शून्य, "Left Output Mixer"पूर्ण,
	अणु"LHP", शून्य, "Left Headphone Out"पूर्ण,

	अणु"Right Speaker Out", शून्य, "Right Output Mixer"पूर्ण,
	अणु"RSPK", शून्य, "Right Speaker Out"पूर्ण,

	अणु"Left Speaker Out", शून्य, "Left Output Mixer"पूर्ण,
	अणु"LSPK", शून्य, "Left Speaker Out"पूर्ण,

	अणु"AUX1 Out", शून्य, "AUX1 Output Mixer"पूर्ण,
	अणु"AUX2 Out", शून्य, "AUX2 Output Mixer"पूर्ण,
	अणु"AUXOUT1", शून्य, "AUX1 Out"पूर्ण,
	अणु"AUXOUT2", शून्य, "AUX2 Out"पूर्ण,

	/* Boost Mixer */
	अणु"Right ADC", शून्य, "PLL", check_mclk_select_pllपूर्ण,
	अणु"Left ADC", शून्य, "PLL", check_mclk_select_pllपूर्ण,

	अणु"Right ADC", शून्य, "Right Boost Mixer"पूर्ण,

	अणु"Right Boost Mixer", शून्य, "RAUX"पूर्ण,
	अणु"Right Boost Mixer", शून्य, "Right Capture PGA"पूर्ण,
	अणु"Right Boost Mixer", शून्य, "R2"पूर्ण,

	अणु"Left ADC", शून्य, "Left Boost Mixer"पूर्ण,

	अणु"Left Boost Mixer", शून्य, "LAUX"पूर्ण,
	अणु"Left Boost Mixer", शून्य, "Left Capture PGA"पूर्ण,
	अणु"Left Boost Mixer", शून्य, "L2"पूर्ण,

	/* Input PGA */
	अणु"Right Capture PGA", शून्य, "Right Input Mixer"पूर्ण,
	अणु"Left Capture PGA", शून्य, "Left Input Mixer"पूर्ण,

	/* Enable Microphone Power */
	अणु"Right Capture PGA", शून्य, "Mic Bias"पूर्ण,
	अणु"Left Capture PGA", शून्य, "Mic Bias"पूर्ण,

	अणु"Right Input Mixer", "R2 Switch", "R2"पूर्ण,
	अणु"Right Input Mixer", "MicN Switch", "RMICN"पूर्ण,
	अणु"Right Input Mixer", "MicP Switch", "RMICP"पूर्ण,

	अणु"Left Input Mixer", "L2 Switch", "L2"पूर्ण,
	अणु"Left Input Mixer", "MicN Switch", "LMICN"पूर्ण,
	अणु"Left Input Mixer", "MicP Switch", "LMICP"पूर्ण,

	/* Digital Loopback */
	अणु"Digital Loopback", "Switch", "Left ADC"पूर्ण,
	अणु"Digital Loopback", "Switch", "Right ADC"पूर्ण,
	अणु"Left DAC", शून्य, "Digital Loopback"पूर्ण,
	अणु"Right DAC", शून्य, "Digital Loopback"पूर्ण,
पूर्ण;

अटल पूर्णांक nau8822_set_dai_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
				 अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा nau8822 *nau8822 = snd_soc_component_get_drvdata(component);

	nau8822->भाग_id = clk_id;
	nau8822->sysclk = freq;
	dev_dbg(component->dev, "master sysclk %dHz, source %s\n", freq,
		clk_id == NAU8822_CLK_PLL ? "PLL" : "MCLK");

	वापस 0;
पूर्ण

अटल पूर्णांक nau8822_calc_pll(अचिन्हित पूर्णांक pll_in, अचिन्हित पूर्णांक fs,
				काष्ठा nau8822_pll *pll_param)
अणु
	u64 f2, f2_max, pll_ratio;
	पूर्णांक i, scal_sel;

	अगर (pll_in > NAU_PLL_REF_MAX || pll_in < NAU_PLL_REF_MIN)
		वापस -EINVAL;
	f2_max = 0;
	scal_sel = ARRAY_SIZE(nau8822_mclk_scaler);

	क्रम (i = 0; i < scal_sel; i++) अणु
		f2 = 256 * fs * 4 * nau8822_mclk_scaler[i] / 10;
		अगर (f2 > NAU_PLL_FREQ_MIN && f2 < NAU_PLL_FREQ_MAX &&
			f2_max < f2) अणु
			f2_max = f2;
			scal_sel = i;
		पूर्ण
	पूर्ण

	अगर (ARRAY_SIZE(nau8822_mclk_scaler) == scal_sel)
		वापस -EINVAL;
	pll_param->mclk_scaler = scal_sel;
	f2 = f2_max;

	/* Calculate the PLL 4-bit पूर्णांकeger input and the PLL 24-bit fractional
	 * input; round up the 24+4bit.
	 */
	pll_ratio = भाग_u64(f2 << 28, pll_in);
	pll_param->pre_factor = 0;
	अगर (((pll_ratio >> 28) & 0xF) < NAU_PLL_OPTOP_MIN) अणु
		pll_ratio <<= 1;
		pll_param->pre_factor = 1;
	पूर्ण
	pll_param->pll_पूर्णांक = (pll_ratio >> 28) & 0xF;
	pll_param->pll_frac = ((pll_ratio & 0xFFFFFFF) >> 4);

	वापस 0;
पूर्ण

अटल पूर्णांक nau8822_config_clkभाग(काष्ठा snd_soc_dai *dai, पूर्णांक भाग, पूर्णांक rate)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा nau8822 *nau8822 = snd_soc_component_get_drvdata(component);
	काष्ठा nau8822_pll *pll = &nau8822->pll;
	पूर्णांक i, sclk, imclk;

	चयन (nau8822->भाग_id) अणु
	हाल NAU8822_CLK_MCLK:
		/* Configure the master घड़ी prescaler भाग to make प्रणाली
		 * घड़ी to approximate the पूर्णांकernal master घड़ी (IMCLK);
		 * and large or equal to IMCLK.
		 */
		भाग = 0;
		imclk = rate * 256;
		क्रम (i = 1; i < ARRAY_SIZE(nau8822_mclk_scaler); i++) अणु
			sclk = (nau8822->sysclk * 10) /	nau8822_mclk_scaler[i];
			अगर (sclk < imclk)
				अवरोध;
			भाग = i;
		पूर्ण
		dev_dbg(component->dev, "master clock prescaler %x for fs %d\n",
			भाग, rate);

		/* master घड़ी from MCLK and disable PLL */
		snd_soc_component_update_bits(component,
			NAU8822_REG_CLOCKING, NAU8822_MCLKSEL_MASK,
			(भाग << NAU8822_MCLKSEL_SFT));
		snd_soc_component_update_bits(component,
			NAU8822_REG_CLOCKING, NAU8822_CLKM_MASK,
			NAU8822_CLKM_MCLK);
		अवरोध;

	हाल NAU8822_CLK_PLL:
		/* master घड़ी from PLL and enable PLL */
		अगर (pll->mclk_scaler != भाग) अणु
			dev_err(component->dev,
			"master clock prescaler not meet PLL parameters\n");
			वापस -EINVAL;
		पूर्ण
		snd_soc_component_update_bits(component,
			NAU8822_REG_CLOCKING, NAU8822_MCLKSEL_MASK,
			(भाग << NAU8822_MCLKSEL_SFT));
		snd_soc_component_update_bits(component,
			NAU8822_REG_CLOCKING, NAU8822_CLKM_MASK,
			NAU8822_CLKM_PLL);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nau8822_set_pll(काष्ठा snd_soc_dai *dai, पूर्णांक pll_id, पूर्णांक source,
				अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा nau8822 *nau8822 = snd_soc_component_get_drvdata(component);
	काष्ठा nau8822_pll *pll_param = &nau8822->pll;
	पूर्णांक ret, fs;

	fs = freq_out / 256;

	ret = nau8822_calc_pll(freq_in, fs, pll_param);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Unsupported input clock %d\n",
			freq_in);
		वापस ret;
	पूर्ण

	dev_info(component->dev,
		"pll_int=%x pll_frac=%x mclk_scaler=%x pre_factor=%x\n",
		pll_param->pll_पूर्णांक, pll_param->pll_frac,
		pll_param->mclk_scaler, pll_param->pre_factor);

	snd_soc_component_update_bits(component,
		NAU8822_REG_PLL_N, NAU8822_PLLMCLK_DIV2 | NAU8822_PLLN_MASK,
		(pll_param->pre_factor ? NAU8822_PLLMCLK_DIV2 : 0) |
		pll_param->pll_पूर्णांक);
	snd_soc_component_ग_लिखो(component,
		NAU8822_REG_PLL_K1, (pll_param->pll_frac >> NAU8822_PLLK1_SFT) &
		NAU8822_PLLK1_MASK);
	snd_soc_component_ग_लिखो(component,
		NAU8822_REG_PLL_K2, (pll_param->pll_frac >> NAU8822_PLLK2_SFT) &
		NAU8822_PLLK2_MASK);
	snd_soc_component_ग_लिखो(component,
		NAU8822_REG_PLL_K3, pll_param->pll_frac & NAU8822_PLLK3_MASK);
	snd_soc_component_update_bits(component,
		NAU8822_REG_CLOCKING, NAU8822_MCLKSEL_MASK,
		pll_param->mclk_scaler << NAU8822_MCLKSEL_SFT);
	snd_soc_component_update_bits(component,
		NAU8822_REG_CLOCKING, NAU8822_CLKM_MASK, NAU8822_CLKM_PLL);

	वापस 0;
पूर्ण

अटल पूर्णांक nau8822_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 ctrl1_val = 0, ctrl2_val = 0;

	dev_dbg(component->dev, "%s\n", __func__);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		ctrl2_val |= 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		ctrl2_val &= ~1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		ctrl1_val |= 0x10;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		ctrl1_val |= 0x8;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		ctrl1_val |= 0x18;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		ctrl1_val |= 0x180;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		ctrl1_val |= 0x100;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		ctrl1_val |= 0x80;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component,
		NAU8822_REG_AUDIO_INTERFACE,
		NAU8822_AIFMT_MASK | NAU8822_LRP_MASK | NAU8822_BCLKP_MASK,
		ctrl1_val);
	snd_soc_component_update_bits(component,
		NAU8822_REG_CLOCKING, NAU8822_CLKIOEN_MASK, ctrl2_val);

	वापस 0;
पूर्ण

अटल पूर्णांक nau8822_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा nau8822 *nau8822 = snd_soc_component_get_drvdata(component);
	पूर्णांक val_len = 0, val_rate = 0;
	अचिन्हित पूर्णांक ctrl_val, bclk_fs, bclk_भाग;

	/* make BCLK and LRC भागide configuration अगर the codec as master. */
	ctrl_val = snd_soc_component_पढ़ो(component, NAU8822_REG_CLOCKING);
	अगर (ctrl_val & NAU8822_CLK_MASTER) अणु
		/* get the bclk and fs ratio */
		bclk_fs = snd_soc_params_to_bclk(params) / params_rate(params);
		अगर (bclk_fs <= 32)
			bclk_भाग = NAU8822_BCLKDIV_8;
		अन्यथा अगर (bclk_fs <= 64)
			bclk_भाग = NAU8822_BCLKDIV_4;
		अन्यथा अगर (bclk_fs <= 128)
			bclk_भाग = NAU8822_BCLKDIV_2;
		अन्यथा
			वापस -EINVAL;
		snd_soc_component_update_bits(component, NAU8822_REG_CLOCKING,
				NAU8822_BCLKSEL_MASK, bclk_भाग);
	पूर्ण

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S20_3LE:
		val_len |= NAU8822_WLEN_20;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		val_len |= NAU8822_WLEN_24;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		val_len |= NAU8822_WLEN_32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (params_rate(params)) अणु
	हाल 8000:
		val_rate |= NAU8822_SMPLR_8K;
		अवरोध;
	हाल 11025:
		val_rate |= NAU8822_SMPLR_12K;
		अवरोध;
	हाल 16000:
		val_rate |= NAU8822_SMPLR_16K;
		अवरोध;
	हाल 22050:
		val_rate |= NAU8822_SMPLR_24K;
		अवरोध;
	हाल 32000:
		val_rate |= NAU8822_SMPLR_32K;
		अवरोध;
	हाल 44100:
	हाल 48000:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component,
		NAU8822_REG_AUDIO_INTERFACE, NAU8822_WLEN_MASK, val_len);
	snd_soc_component_update_bits(component,
		NAU8822_REG_ADDITIONAL_CONTROL, NAU8822_SMPLR_MASK, val_rate);

	/* If the master घड़ी is from MCLK, provide the runसमय FS क्रम driver
	 * to get the master घड़ी prescaler configuration.
	 */
	अगर (nau8822->भाग_id == NAU8822_CLK_MCLK)
		nau8822_config_clkभाग(dai, 0, params_rate(params));

	वापस 0;
पूर्ण

अटल पूर्णांक nau8822_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	dev_dbg(component->dev, "%s: %d\n", __func__, mute);

	अगर (mute)
		snd_soc_component_update_bits(component,
			NAU8822_REG_DAC_CONTROL, 0x40, 0x40);
	अन्यथा
		snd_soc_component_update_bits(component,
			NAU8822_REG_DAC_CONTROL, 0x40, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक nau8822_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
		snd_soc_component_update_bits(component,
			NAU8822_REG_POWER_MANAGEMENT_1,
			NAU8822_REFIMP_MASK, NAU8822_REFIMP_80K);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		snd_soc_component_update_bits(component,
			NAU8822_REG_POWER_MANAGEMENT_1,
			NAU8822_IOBUF_EN | NAU8822_ABIAS_EN,
			NAU8822_IOBUF_EN | NAU8822_ABIAS_EN);

		अगर (snd_soc_component_get_bias_level(component) ==
			SND_SOC_BIAS_OFF) अणु
			snd_soc_component_update_bits(component,
				NAU8822_REG_POWER_MANAGEMENT_1,
				NAU8822_REFIMP_MASK, NAU8822_REFIMP_3K);
			mdelay(100);
		पूर्ण
		snd_soc_component_update_bits(component,
			NAU8822_REG_POWER_MANAGEMENT_1,
			NAU8822_REFIMP_MASK, NAU8822_REFIMP_300K);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_ग_लिखो(component,
			NAU8822_REG_POWER_MANAGEMENT_1, 0);
		snd_soc_component_ग_लिखो(component,
			NAU8822_REG_POWER_MANAGEMENT_2, 0);
		snd_soc_component_ग_लिखो(component,
			NAU8822_REG_POWER_MANAGEMENT_3, 0);
		अवरोध;
	पूर्ण

	dev_dbg(component->dev, "%s: %d\n", __func__, level);

	वापस 0;
पूर्ण

#घोषणा NAU8822_RATES (SNDRV_PCM_RATE_8000_48000)

#घोषणा NAU8822_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
	SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops nau8822_dai_ops = अणु
	.hw_params	= nau8822_hw_params,
	.mute_stream	= nau8822_mute,
	.set_fmt	= nau8822_set_dai_fmt,
	.set_sysclk	= nau8822_set_dai_sysclk,
	.set_pll	= nau8822_set_pll,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver nau8822_dai = अणु
	.name = "nau8822-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = NAU8822_RATES,
		.क्रमmats = NAU8822_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = NAU8822_RATES,
		.क्रमmats = NAU8822_FORMATS,
	पूर्ण,
	.ops = &nau8822_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक nau8822_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा nau8822 *nau8822 = snd_soc_component_get_drvdata(component);

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_OFF);

	regcache_mark_dirty(nau8822->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक nau8822_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा nau8822 *nau8822 = snd_soc_component_get_drvdata(component);

	regcache_sync(nau8822->regmap);

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_STANDBY);

	वापस 0;
पूर्ण

/*
 * These रेजिस्टरs contain an "update" bit - bit 8. This means, क्रम example,
 * that one can ग_लिखो new DAC digital volume क्रम both channels, but only when
 * the update bit is set, will also the volume be updated - simultaneously क्रम
 * both channels.
 */
अटल स्थिर पूर्णांक update_reg[] = अणु
	NAU8822_REG_LEFT_DAC_DIGITAL_VOLUME,
	NAU8822_REG_RIGHT_DAC_DIGITAL_VOLUME,
	NAU8822_REG_LEFT_ADC_DIGITAL_VOLUME,
	NAU8822_REG_RIGHT_ADC_DIGITAL_VOLUME,
	NAU8822_REG_LEFT_INP_PGA_CONTROL,
	NAU8822_REG_RIGHT_INP_PGA_CONTROL,
	NAU8822_REG_LHP_VOLUME,
	NAU8822_REG_RHP_VOLUME,
	NAU8822_REG_LSPKOUT_VOLUME,
	NAU8822_REG_RSPKOUT_VOLUME,
पूर्ण;

अटल पूर्णांक nau8822_probe(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक i;

	/*
	 * Set the update bit in all रेजिस्टरs, that have one. This way all
	 * ग_लिखोs to those रेजिस्टरs will also cause the update bit to be
	 * written.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(update_reg); i++)
		snd_soc_component_update_bits(component,
			update_reg[i], 0x100, 0x100);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_nau8822 = अणु
	.probe				= nau8822_probe,
	.suspend			= nau8822_suspend,
	.resume				= nau8822_resume,
	.set_bias_level			= nau8822_set_bias_level,
	.controls			= nau8822_snd_controls,
	.num_controls			= ARRAY_SIZE(nau8822_snd_controls),
	.dapm_widमाला_लो			= nau8822_dapm_widमाला_लो,
	.num_dapm_widमाला_लो		= ARRAY_SIZE(nau8822_dapm_widमाला_लो),
	.dapm_routes			= nau8822_dapm_routes,
	.num_dapm_routes		= ARRAY_SIZE(nau8822_dapm_routes),
	.idle_bias_on			= 1,
	.use_pmकरोwn_समय		= 1,
	.endianness			= 1,
	.non_legacy_dai_naming		= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config nau8822_regmap_config = अणु
	.reg_bits = 7,
	.val_bits = 9,

	.max_रेजिस्टर = NAU8822_REG_MAX_REGISTER,
	.अस्थिर_reg = nau8822_अस्थिर,

	.पढ़ोable_reg = nau8822_पढ़ोable_reg,
	.ग_लिखोable_reg = nau8822_ग_लिखोable_reg,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = nau8822_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(nau8822_reg_शेषs),
पूर्ण;

अटल पूर्णांक nau8822_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &i2c->dev;
	काष्ठा nau8822 *nau8822 = dev_get_platdata(dev);
	पूर्णांक ret;

	अगर (!nau8822) अणु
		nau8822 = devm_kzalloc(dev, माप(*nau8822), GFP_KERNEL);
		अगर (nau8822 == शून्य)
			वापस -ENOMEM;
	पूर्ण
	i2c_set_clientdata(i2c, nau8822);

	nau8822->regmap = devm_regmap_init_i2c(i2c, &nau8822_regmap_config);
	अगर (IS_ERR(nau8822->regmap)) अणु
		ret = PTR_ERR(nau8822->regmap);
		dev_err(&i2c->dev, "Failed to allocate regmap: %d\n", ret);
		वापस ret;
	पूर्ण
	nau8822->dev = dev;

	/* Reset the codec */
	ret = regmap_ग_लिखो(nau8822->regmap, NAU8822_REG_RESET, 0x00);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to issue reset: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(dev, &soc_component_dev_nau8822,
						&nau8822_dai, 1);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to register CODEC: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id nau8822_i2c_id[] = अणु
	अणु "nau8822", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, nau8822_i2c_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id nau8822_of_match[] = अणु
	अणु .compatible = "nuvoton,nau8822", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, nau8822_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver nau8822_i2c_driver = अणु
	.driver = अणु
		.name = "nau8822",
		.of_match_table = of_match_ptr(nau8822_of_match),
	पूर्ण,
	.probe =    nau8822_i2c_probe,
	.id_table = nau8822_i2c_id,
पूर्ण;
module_i2c_driver(nau8822_i2c_driver);

MODULE_DESCRIPTION("ASoC NAU8822 codec driver");
MODULE_AUTHOR("David Lin <ctlin0@nuvoton.com>");
MODULE_LICENSE("GPL v2");
