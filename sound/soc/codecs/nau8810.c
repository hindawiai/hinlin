<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * nau8810.c  --  NAU8810 ALSA Soc Audio driver
 *
 * Copyright 2016 Nuvoton Technology Corp.
 *
 * Author: David Lin <ctlin0@nuvoton.com>
 *
 * Based on WM8974.c
 */

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

#समावेश "nau8810.h"

#घोषणा NAU_PLL_FREQ_MAX 100000000
#घोषणा NAU_PLL_FREQ_MIN 90000000
#घोषणा NAU_PLL_REF_MAX 33000000
#घोषणा NAU_PLL_REF_MIN 8000000
#घोषणा NAU_PLL_OPTOP_MIN 6


अटल स्थिर पूर्णांक nau8810_mclk_scaler[] = अणु 10, 15, 20, 30, 40, 60, 80, 120 पूर्ण;

अटल स्थिर काष्ठा reg_शेष nau8810_reg_शेषs[] = अणु
	अणु NAU8810_REG_POWER1, 0x0000 पूर्ण,
	अणु NAU8810_REG_POWER2, 0x0000 पूर्ण,
	अणु NAU8810_REG_POWER3, 0x0000 पूर्ण,
	अणु NAU8810_REG_IFACE, 0x0050 पूर्ण,
	अणु NAU8810_REG_COMP, 0x0000 पूर्ण,
	अणु NAU8810_REG_CLOCK, 0x0140 पूर्ण,
	अणु NAU8810_REG_SMPLR, 0x0000 पूर्ण,
	अणु NAU8810_REG_DAC, 0x0000 पूर्ण,
	अणु NAU8810_REG_DACGAIN, 0x00FF पूर्ण,
	अणु NAU8810_REG_ADC, 0x0100 पूर्ण,
	अणु NAU8810_REG_ADCGAIN, 0x00FF पूर्ण,
	अणु NAU8810_REG_EQ1, 0x012C पूर्ण,
	अणु NAU8810_REG_EQ2, 0x002C पूर्ण,
	अणु NAU8810_REG_EQ3, 0x002C पूर्ण,
	अणु NAU8810_REG_EQ4, 0x002C पूर्ण,
	अणु NAU8810_REG_EQ5, 0x002C पूर्ण,
	अणु NAU8810_REG_DACLIM1, 0x0032 पूर्ण,
	अणु NAU8810_REG_DACLIM2, 0x0000 पूर्ण,
	अणु NAU8810_REG_NOTCH1, 0x0000 पूर्ण,
	अणु NAU8810_REG_NOTCH2, 0x0000 पूर्ण,
	अणु NAU8810_REG_NOTCH3, 0x0000 पूर्ण,
	अणु NAU8810_REG_NOTCH4, 0x0000 पूर्ण,
	अणु NAU8810_REG_ALC1, 0x0038 पूर्ण,
	अणु NAU8810_REG_ALC2, 0x000B पूर्ण,
	अणु NAU8810_REG_ALC3, 0x0032 पूर्ण,
	अणु NAU8810_REG_NOISEGATE, 0x0000 पूर्ण,
	अणु NAU8810_REG_PLLN, 0x0008 पूर्ण,
	अणु NAU8810_REG_PLLK1, 0x000C पूर्ण,
	अणु NAU8810_REG_PLLK2, 0x0093 पूर्ण,
	अणु NAU8810_REG_PLLK3, 0x00E9 पूर्ण,
	अणु NAU8810_REG_ATTEN, 0x0000 पूर्ण,
	अणु NAU8810_REG_INPUT_SIGNAL, 0x0003 पूर्ण,
	अणु NAU8810_REG_PGAGAIN, 0x0010 पूर्ण,
	अणु NAU8810_REG_ADCBOOST, 0x0100 पूर्ण,
	अणु NAU8810_REG_OUTPUT, 0x0002 पूर्ण,
	अणु NAU8810_REG_SPKMIX, 0x0001 पूर्ण,
	अणु NAU8810_REG_SPKGAIN, 0x0039 पूर्ण,
	अणु NAU8810_REG_MONOMIX, 0x0001 पूर्ण,
	अणु NAU8810_REG_POWER4, 0x0000 पूर्ण,
	अणु NAU8810_REG_TSLOTCTL1, 0x0000 पूर्ण,
	अणु NAU8810_REG_TSLOTCTL2, 0x0020 पूर्ण,
	अणु NAU8810_REG_DEVICE_REVID, 0x0000 पूर्ण,
	अणु NAU8810_REG_I2C_DEVICEID, 0x001A पूर्ण,
	अणु NAU8810_REG_ADDITIONID, 0x00CA पूर्ण,
	अणु NAU8810_REG_RESERVE, 0x0124 पूर्ण,
	अणु NAU8810_REG_OUTCTL, 0x0001 पूर्ण,
	अणु NAU8810_REG_ALC1ENHAN1, 0x0010 पूर्ण,
	अणु NAU8810_REG_ALC1ENHAN2, 0x0000 पूर्ण,
	अणु NAU8810_REG_MISCCTL, 0x0000 पूर्ण,
	अणु NAU8810_REG_OUTTIखातापूर्णF, 0x0000 पूर्ण,
	अणु NAU8810_REG_AGCP2POUT, 0x0000 पूर्ण,
	अणु NAU8810_REG_AGCPOUT, 0x0000 पूर्ण,
	अणु NAU8810_REG_AMTCTL, 0x0000 पूर्ण,
	अणु NAU8810_REG_OUTTIखातापूर्णFMAN, 0x0000 पूर्ण,
पूर्ण;

अटल bool nau8810_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल NAU8810_REG_RESET ... NAU8810_REG_SMPLR:
	हाल NAU8810_REG_DAC ... NAU8810_REG_DACGAIN:
	हाल NAU8810_REG_ADC ... NAU8810_REG_ADCGAIN:
	हाल NAU8810_REG_EQ1 ... NAU8810_REG_EQ5:
	हाल NAU8810_REG_DACLIM1 ... NAU8810_REG_DACLIM2:
	हाल NAU8810_REG_NOTCH1 ... NAU8810_REG_NOTCH4:
	हाल NAU8810_REG_ALC1 ... NAU8810_REG_ATTEN:
	हाल NAU8810_REG_INPUT_SIGNAL ... NAU8810_REG_PGAGAIN:
	हाल NAU8810_REG_ADCBOOST:
	हाल NAU8810_REG_OUTPUT ... NAU8810_REG_SPKMIX:
	हाल NAU8810_REG_SPKGAIN:
	हाल NAU8810_REG_MONOMIX:
	हाल NAU8810_REG_POWER4 ... NAU8810_REG_TSLOTCTL2:
	हाल NAU8810_REG_DEVICE_REVID ... NAU8810_REG_RESERVE:
	हाल NAU8810_REG_OUTCTL ... NAU8810_REG_ALC1ENHAN2:
	हाल NAU8810_REG_MISCCTL:
	हाल NAU8810_REG_OUTTIखातापूर्णF ... NAU8810_REG_OUTTIखातापूर्णFMAN:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool nau8810_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल NAU8810_REG_RESET ... NAU8810_REG_SMPLR:
	हाल NAU8810_REG_DAC ... NAU8810_REG_DACGAIN:
	हाल NAU8810_REG_ADC ... NAU8810_REG_ADCGAIN:
	हाल NAU8810_REG_EQ1 ... NAU8810_REG_EQ5:
	हाल NAU8810_REG_DACLIM1 ... NAU8810_REG_DACLIM2:
	हाल NAU8810_REG_NOTCH1 ... NAU8810_REG_NOTCH4:
	हाल NAU8810_REG_ALC1 ... NAU8810_REG_ATTEN:
	हाल NAU8810_REG_INPUT_SIGNAL ... NAU8810_REG_PGAGAIN:
	हाल NAU8810_REG_ADCBOOST:
	हाल NAU8810_REG_OUTPUT ... NAU8810_REG_SPKMIX:
	हाल NAU8810_REG_SPKGAIN:
	हाल NAU8810_REG_MONOMIX:
	हाल NAU8810_REG_POWER4 ... NAU8810_REG_TSLOTCTL2:
	हाल NAU8810_REG_OUTCTL ... NAU8810_REG_ALC1ENHAN2:
	हाल NAU8810_REG_MISCCTL:
	हाल NAU8810_REG_OUTTIखातापूर्णF ... NAU8810_REG_OUTTIखातापूर्णFMAN:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool nau8810_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल NAU8810_REG_RESET:
	हाल NAU8810_REG_DEVICE_REVID ... NAU8810_REG_RESERVE:
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
अटल पूर्णांक nau8810_eq_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा nau8810 *nau8810 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_bytes_ext *params = (व्योम *)kcontrol->निजी_value;
	पूर्णांक i, reg, reg_val;
	u16 *val;

	val = (u16 *)ucontrol->value.bytes.data;
	reg = NAU8810_REG_EQ1;
	क्रम (i = 0; i < params->max / माप(u16); i++) अणु
		regmap_पढ़ो(nau8810->regmap, reg + i, &reg_val);
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
अटल पूर्णांक nau8810_eq_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा nau8810 *nau8810 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_bytes_ext *params = (व्योम *)kcontrol->निजी_value;
	व्योम *data;
	u16 *val, value;
	पूर्णांक i, reg, ret;

	data = kmemdup(ucontrol->value.bytes.data,
		params->max, GFP_KERNEL | GFP_DMA);
	अगर (!data)
		वापस -ENOMEM;

	val = (u16 *)data;
	reg = NAU8810_REG_EQ1;
	क्रम (i = 0; i < params->max / माप(u16); i++) अणु
		/* conversion of 16-bit पूर्णांकegers between native CPU क्रमmat
		 * and big endian क्रमmat
		 */
		value = be16_to_cpu(*(val + i));
		ret = regmap_ग_लिखो(nau8810->regmap, reg + i, value);
		अगर (ret) अणु
			dev_err(component->dev, "EQ configuration fail, register: %x ret: %d\n",
				reg + i, ret);
			kमुक्त(data);
			वापस ret;
		पूर्ण
	पूर्ण
	kमुक्त(data);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर nau8810_companding[] = अणु
	"Off", "NC", "u-law", "A-law" पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत nau8810_companding_adc_क्रमागत =
	SOC_ENUM_SINGLE(NAU8810_REG_COMP, NAU8810_ADCCM_SFT,
		ARRAY_SIZE(nau8810_companding), nau8810_companding);

अटल स्थिर काष्ठा soc_क्रमागत nau8810_companding_dac_क्रमागत =
	SOC_ENUM_SINGLE(NAU8810_REG_COMP, NAU8810_DACCM_SFT,
		ARRAY_SIZE(nau8810_companding), nau8810_companding);

अटल स्थिर अक्षर * स्थिर nau8810_deemp[] = अणु
	"None", "32kHz", "44.1kHz", "48kHz" पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत nau8810_deemp_क्रमागत =
	SOC_ENUM_SINGLE(NAU8810_REG_DAC, NAU8810_DEEMP_SFT,
		ARRAY_SIZE(nau8810_deemp), nau8810_deemp);

अटल स्थिर अक्षर * स्थिर nau8810_eqmode[] = अणु"Capture", "Playback" पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत nau8810_eqmode_क्रमागत =
	SOC_ENUM_SINGLE(NAU8810_REG_EQ1, NAU8810_EQM_SFT,
		ARRAY_SIZE(nau8810_eqmode), nau8810_eqmode);

अटल स्थिर अक्षर * स्थिर nau8810_alc[] = अणु"Normal", "Limiter" पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत nau8810_alc_क्रमागत =
	SOC_ENUM_SINGLE(NAU8810_REG_ALC3, NAU8810_ALCM_SFT,
		ARRAY_SIZE(nau8810_alc), nau8810_alc);

अटल स्थिर DECLARE_TLV_DB_SCALE(digital_tlv, -12750, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(eq_tlv, -1200, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(inpga_tlv, -1200, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(spk_tlv, -5700, 100, 0);

अटल स्थिर काष्ठा snd_kcontrol_new nau8810_snd_controls[] = अणु
	SOC_ENUM("ADC Companding", nau8810_companding_adc_क्रमागत),
	SOC_ENUM("DAC Companding", nau8810_companding_dac_क्रमागत),
	SOC_ENUM("DAC De-emphasis", nau8810_deemp_क्रमागत),

	SOC_ENUM("EQ Function", nau8810_eqmode_क्रमागत),
	SND_SOC_BYTES_EXT("EQ Parameters", 10,
		  nau8810_eq_get, nau8810_eq_put),

	SOC_SINGLE("DAC Inversion Switch", NAU8810_REG_DAC,
		NAU8810_DACPL_SFT, 1, 0),
	SOC_SINGLE_TLV("Playback Volume", NAU8810_REG_DACGAIN,
		NAU8810_DACGAIN_SFT, 0xff, 0, digital_tlv),

	SOC_SINGLE("High Pass Filter Switch", NAU8810_REG_ADC,
		NAU8810_HPFEN_SFT, 1, 0),
	SOC_SINGLE("High Pass Cut Off", NAU8810_REG_ADC,
		NAU8810_HPF_SFT, 0x7, 0),

	SOC_SINGLE("ADC Inversion Switch", NAU8810_REG_ADC,
		NAU8810_ADCPL_SFT, 1, 0),
	SOC_SINGLE_TLV("Capture Volume", NAU8810_REG_ADCGAIN,
		NAU8810_ADCGAIN_SFT, 0xff, 0, digital_tlv),

	SOC_SINGLE_TLV("EQ1 Volume", NAU8810_REG_EQ1,
		NAU8810_EQ1GC_SFT, 0x18, 1, eq_tlv),
	SOC_SINGLE_TLV("EQ2 Volume", NAU8810_REG_EQ2,
		NAU8810_EQ2GC_SFT, 0x18, 1, eq_tlv),
	SOC_SINGLE_TLV("EQ3 Volume", NAU8810_REG_EQ3,
		NAU8810_EQ3GC_SFT, 0x18, 1, eq_tlv),
	SOC_SINGLE_TLV("EQ4 Volume", NAU8810_REG_EQ4,
		NAU8810_EQ4GC_SFT, 0x18, 1, eq_tlv),
	SOC_SINGLE_TLV("EQ5 Volume", NAU8810_REG_EQ5,
		NAU8810_EQ5GC_SFT, 0x18, 1, eq_tlv),

	SOC_SINGLE("DAC Limiter Switch", NAU8810_REG_DACLIM1,
		NAU8810_DACLIMEN_SFT, 1, 0),
	SOC_SINGLE("DAC Limiter Decay", NAU8810_REG_DACLIM1,
		NAU8810_DACLIMDCY_SFT, 0xf, 0),
	SOC_SINGLE("DAC Limiter Attack", NAU8810_REG_DACLIM1,
		NAU8810_DACLIMATK_SFT, 0xf, 0),
	SOC_SINGLE("DAC Limiter Threshold", NAU8810_REG_DACLIM2,
		NAU8810_DACLIMTHL_SFT, 0x7, 0),
	SOC_SINGLE("DAC Limiter Boost", NAU8810_REG_DACLIM2,
		NAU8810_DACLIMBST_SFT, 0xf, 0),

	SOC_ENUM("ALC Mode", nau8810_alc_क्रमागत),
	SOC_SINGLE("ALC Enable Switch", NAU8810_REG_ALC1,
		NAU8810_ALCEN_SFT, 1, 0),
	SOC_SINGLE("ALC Max Volume", NAU8810_REG_ALC1,
		NAU8810_ALCMXGAIN_SFT, 0x7, 0),
	SOC_SINGLE("ALC Min Volume", NAU8810_REG_ALC1,
		NAU8810_ALCMINGAIN_SFT, 0x7, 0),
	SOC_SINGLE("ALC ZC Switch", NAU8810_REG_ALC2,
		NAU8810_ALCZC_SFT, 1, 0),
	SOC_SINGLE("ALC Hold", NAU8810_REG_ALC2,
		NAU8810_ALCHT_SFT, 0xf, 0),
	SOC_SINGLE("ALC Target", NAU8810_REG_ALC2,
		NAU8810_ALCSL_SFT, 0xf, 0),
	SOC_SINGLE("ALC Decay", NAU8810_REG_ALC3,
		NAU8810_ALCDCY_SFT, 0xf, 0),
	SOC_SINGLE("ALC Attack", NAU8810_REG_ALC3,
		NAU8810_ALCATK_SFT, 0xf, 0),
	SOC_SINGLE("ALC Noise Gate Switch", NAU8810_REG_NOISEGATE,
		NAU8810_ALCNEN_SFT, 1, 0),
	SOC_SINGLE("ALC Noise Gate Threshold", NAU8810_REG_NOISEGATE,
		NAU8810_ALCNTH_SFT, 0x7, 0),

	SOC_SINGLE("PGA ZC Switch", NAU8810_REG_PGAGAIN,
		NAU8810_PGAZC_SFT, 1, 0),
	SOC_SINGLE_TLV("PGA Volume", NAU8810_REG_PGAGAIN,
		NAU8810_PGAGAIN_SFT, 0x3f, 0, inpga_tlv),

	SOC_SINGLE("Speaker ZC Switch", NAU8810_REG_SPKGAIN,
		NAU8810_SPKZC_SFT, 1, 0),
	SOC_SINGLE("Speaker Mute Switch", NAU8810_REG_SPKGAIN,
		NAU8810_SPKMT_SFT, 1, 0),
	SOC_SINGLE_TLV("Speaker Volume", NAU8810_REG_SPKGAIN,
		NAU8810_SPKGAIN_SFT, 0x3f, 0, spk_tlv),

	SOC_SINGLE("Capture Boost(+20dB)", NAU8810_REG_ADCBOOST,
		NAU8810_PGABST_SFT, 1, 0),
	SOC_SINGLE("Mono Mute Switch", NAU8810_REG_MONOMIX,
		NAU8810_MOUTMXMT_SFT, 1, 0),

	SOC_SINGLE("DAC Oversampling Rate(128x) Switch", NAU8810_REG_DAC,
		NAU8810_DACOS_SFT, 1, 0),
	SOC_SINGLE("ADC Oversampling Rate(128x) Switch", NAU8810_REG_ADC,
		NAU8810_ADCOS_SFT, 1, 0),
पूर्ण;

/* Speaker Output Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new nau8810_speaker_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("AUX Bypass Switch", NAU8810_REG_SPKMIX,
		NAU8810_AUXSPK_SFT, 1, 0),
	SOC_DAPM_SINGLE("Line Bypass Switch", NAU8810_REG_SPKMIX,
		NAU8810_BYPSPK_SFT, 1, 0),
	SOC_DAPM_SINGLE("PCM Playback Switch", NAU8810_REG_SPKMIX,
		NAU8810_DACSPK_SFT, 1, 0),
पूर्ण;

/* Mono Output Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new nau8810_mono_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("AUX Bypass Switch", NAU8810_REG_MONOMIX,
		NAU8810_AUXMOUT_SFT, 1, 0),
	SOC_DAPM_SINGLE("Line Bypass Switch", NAU8810_REG_MONOMIX,
		NAU8810_BYPMOUT_SFT, 1, 0),
	SOC_DAPM_SINGLE("PCM Playback Switch", NAU8810_REG_MONOMIX,
		NAU8810_DACMOUT_SFT, 1, 0),
पूर्ण;

/* PGA Mute */
अटल स्थिर काष्ठा snd_kcontrol_new nau8810_pgaboost_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("AUX PGA Switch", NAU8810_REG_ADCBOOST,
		NAU8810_AUXBSTGAIN_SFT, 0x7, 0),
	SOC_DAPM_SINGLE("PGA Mute Switch", NAU8810_REG_PGAGAIN,
		NAU8810_PGAMT_SFT, 1, 1),
	SOC_DAPM_SINGLE("PMIC PGA Switch", NAU8810_REG_ADCBOOST,
		NAU8810_PMICBSTGAIN_SFT, 0x7, 0),
पूर्ण;

/* Input PGA */
अटल स्थिर काष्ठा snd_kcontrol_new nau8810_inpga[] = अणु
	SOC_DAPM_SINGLE("AUX Switch", NAU8810_REG_INPUT_SIGNAL,
		NAU8810_AUXPGA_SFT, 1, 0),
	SOC_DAPM_SINGLE("MicN Switch", NAU8810_REG_INPUT_SIGNAL,
		NAU8810_NMICPGA_SFT, 1, 0),
	SOC_DAPM_SINGLE("MicP Switch", NAU8810_REG_INPUT_SIGNAL,
		NAU8810_PMICPGA_SFT, 1, 0),
पूर्ण;

/* Loopback Switch */
अटल स्थिर काष्ठा snd_kcontrol_new nau8810_loopback =
	SOC_DAPM_SINGLE("Switch", NAU8810_REG_COMP,
		NAU8810_ADDAP_SFT, 1, 0);

अटल पूर्णांक check_mclk_select_pll(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	काष्ठा nau8810 *nau8810 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक value;

	regmap_पढ़ो(nau8810->regmap, NAU8810_REG_CLOCK, &value);
	वापस (value & NAU8810_CLKM_MASK);
पूर्ण

अटल पूर्णांक check_mic_enabled(काष्ठा snd_soc_dapm_widget *source,
	काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(source->dapm);
	काष्ठा nau8810 *nau8810 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक value;

	regmap_पढ़ो(nau8810->regmap, NAU8810_REG_INPUT_SIGNAL, &value);
	अगर (value & NAU8810_PMICPGA_EN || value & NAU8810_NMICPGA_EN)
		वापस 1;
	regmap_पढ़ो(nau8810->regmap, NAU8810_REG_ADCBOOST, &value);
	अगर (value & NAU8810_PMICBSTGAIN_MASK)
		वापस 1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget nau8810_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIXER("Speaker Mixer", NAU8810_REG_POWER3,
		NAU8810_SPKMX_EN_SFT, 0, &nau8810_speaker_mixer_controls[0],
		ARRAY_SIZE(nau8810_speaker_mixer_controls)),
	SND_SOC_DAPM_MIXER("Mono Mixer", NAU8810_REG_POWER3,
		NAU8810_MOUTMX_EN_SFT, 0, &nau8810_mono_mixer_controls[0],
		ARRAY_SIZE(nau8810_mono_mixer_controls)),
	SND_SOC_DAPM_DAC("DAC", "Playback", NAU8810_REG_POWER3,
		NAU8810_DAC_EN_SFT, 0),
	SND_SOC_DAPM_ADC("ADC", "Capture", NAU8810_REG_POWER2,
		NAU8810_ADC_EN_SFT, 0),
	SND_SOC_DAPM_PGA("SpkN Out", NAU8810_REG_POWER3,
		NAU8810_NSPK_EN_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SpkP Out", NAU8810_REG_POWER3,
		NAU8810_PSPK_EN_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Mono Out", NAU8810_REG_POWER3,
		NAU8810_MOUT_EN_SFT, 0, शून्य, 0),

	SND_SOC_DAPM_MIXER("Input PGA", NAU8810_REG_POWER2,
		NAU8810_PGA_EN_SFT, 0, nau8810_inpga,
		ARRAY_SIZE(nau8810_inpga)),
	SND_SOC_DAPM_MIXER("Input Boost Stage", NAU8810_REG_POWER2,
		NAU8810_BST_EN_SFT, 0, nau8810_pgaboost_mixer_controls,
		ARRAY_SIZE(nau8810_pgaboost_mixer_controls)),
	SND_SOC_DAPM_PGA("AUX Input", NAU8810_REG_POWER1,
		NAU8810_AUX_EN_SFT, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("Mic Bias", NAU8810_REG_POWER1,
		NAU8810_MICBIAS_EN_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL", NAU8810_REG_POWER1,
		NAU8810_PLL_EN_SFT, 0, शून्य, 0),

	SND_SOC_DAPM_SWITCH("Digital Loopback", SND_SOC_NOPM, 0, 0,
		&nau8810_loopback),

	SND_SOC_DAPM_INPUT("AUX"),
	SND_SOC_DAPM_INPUT("MICN"),
	SND_SOC_DAPM_INPUT("MICP"),
	SND_SOC_DAPM_OUTPUT("MONOOUT"),
	SND_SOC_DAPM_OUTPUT("SPKOUTP"),
	SND_SOC_DAPM_OUTPUT("SPKOUTN"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route nau8810_dapm_routes[] = अणु
	अणु"DAC", शून्य, "PLL", check_mclk_select_pllपूर्ण,

	/* Mono output mixer */
	अणु"Mono Mixer", "AUX Bypass Switch", "AUX Input"पूर्ण,
	अणु"Mono Mixer", "PCM Playback Switch", "DAC"पूर्ण,
	अणु"Mono Mixer", "Line Bypass Switch", "Input Boost Stage"पूर्ण,

	/* Speaker output mixer */
	अणु"Speaker Mixer", "AUX Bypass Switch", "AUX Input"पूर्ण,
	अणु"Speaker Mixer", "PCM Playback Switch", "DAC"पूर्ण,
	अणु"Speaker Mixer", "Line Bypass Switch", "Input Boost Stage"पूर्ण,

	/* Outमाला_दो */
	अणु"Mono Out", शून्य, "Mono Mixer"पूर्ण,
	अणु"MONOOUT", शून्य, "Mono Out"पूर्ण,
	अणु"SpkN Out", शून्य, "Speaker Mixer"पूर्ण,
	अणु"SpkP Out", शून्य, "Speaker Mixer"पूर्ण,
	अणु"SPKOUTN", शून्य, "SpkN Out"पूर्ण,
	अणु"SPKOUTP", शून्य, "SpkP Out"पूर्ण,

	/* Input Boost Stage */
	अणु"ADC", शून्य, "Input Boost Stage"पूर्ण,
	अणु"ADC", शून्य, "PLL", check_mclk_select_pllपूर्ण,
	अणु"Input Boost Stage", "AUX PGA Switch", "AUX Input"पूर्ण,
	अणु"Input Boost Stage", "PGA Mute Switch", "Input PGA"पूर्ण,
	अणु"Input Boost Stage", "PMIC PGA Switch", "MICP"पूर्ण,

	/* Input PGA */
	अणु"Input PGA", शून्य, "Mic Bias", check_mic_enabledपूर्ण,
	अणु"Input PGA", "AUX Switch", "AUX Input"पूर्ण,
	अणु"Input PGA", "MicN Switch", "MICN"पूर्ण,
	अणु"Input PGA", "MicP Switch", "MICP"पूर्ण,
	अणु"AUX Input", शून्य, "AUX"पूर्ण,

	/* Digital Looptack */
	अणु"Digital Loopback", "Switch", "ADC"पूर्ण,
	अणु"DAC", शून्य, "Digital Loopback"पूर्ण,
पूर्ण;

अटल पूर्णांक nau8810_set_sysclk(काष्ठा snd_soc_dai *dai,
				 पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा nau8810 *nau8810 = snd_soc_component_get_drvdata(component);

	nau8810->clk_id = clk_id;
	nau8810->sysclk = freq;
	dev_dbg(nau8810->dev, "master sysclk %dHz, source %s\n",
		freq, clk_id == NAU8810_SCLK_PLL ? "PLL" : "MCLK");

	वापस 0;
पूर्ण

अटल पूर्णांक nau8810_calc_pll(अचिन्हित पूर्णांक pll_in,
	अचिन्हित पूर्णांक fs, काष्ठा nau8810_pll *pll_param)
अणु
	u64 f2, f2_max, pll_ratio;
	पूर्णांक i, scal_sel;

	अगर (pll_in > NAU_PLL_REF_MAX || pll_in < NAU_PLL_REF_MIN)
		वापस -EINVAL;

	f2_max = 0;
	scal_sel = ARRAY_SIZE(nau8810_mclk_scaler);
	क्रम (i = 0; i < ARRAY_SIZE(nau8810_mclk_scaler); i++) अणु
		f2 = 256ULL * fs * 4 * nau8810_mclk_scaler[i];
		f2 = भाग_u64(f2, 10);
		अगर (f2 > NAU_PLL_FREQ_MIN && f2 < NAU_PLL_FREQ_MAX &&
			f2_max < f2) अणु
			f2_max = f2;
			scal_sel = i;
		पूर्ण
	पूर्ण
	अगर (ARRAY_SIZE(nau8810_mclk_scaler) == scal_sel)
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

अटल पूर्णांक nau8810_set_pll(काष्ठा snd_soc_dai *codec_dai, पूर्णांक pll_id,
	पूर्णांक source, अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा nau8810 *nau8810 = snd_soc_component_get_drvdata(component);
	काष्ठा regmap *map = nau8810->regmap;
	काष्ठा nau8810_pll *pll_param = &nau8810->pll;
	पूर्णांक ret, fs;

	fs = freq_out / 256;
	ret = nau8810_calc_pll(freq_in, fs, pll_param);
	अगर (ret < 0) अणु
		dev_err(nau8810->dev, "Unsupported input clock %d\n", freq_in);
		वापस ret;
	पूर्ण
	dev_info(nau8810->dev, "pll_int=%x pll_frac=%x mclk_scaler=%x pre_factor=%x\n",
		pll_param->pll_पूर्णांक, pll_param->pll_frac, pll_param->mclk_scaler,
		pll_param->pre_factor);

	regmap_update_bits(map, NAU8810_REG_PLLN,
		NAU8810_PLLMCLK_DIV2 | NAU8810_PLLN_MASK,
		(pll_param->pre_factor ? NAU8810_PLLMCLK_DIV2 : 0) |
		pll_param->pll_पूर्णांक);
	regmap_ग_लिखो(map, NAU8810_REG_PLLK1,
		(pll_param->pll_frac >> NAU8810_PLLK1_SFT) &
		NAU8810_PLLK1_MASK);
	regmap_ग_लिखो(map, NAU8810_REG_PLLK2,
		(pll_param->pll_frac >> NAU8810_PLLK2_SFT) &
		NAU8810_PLLK2_MASK);
	regmap_ग_लिखो(map, NAU8810_REG_PLLK3,
		pll_param->pll_frac & NAU8810_PLLK3_MASK);
	regmap_update_bits(map, NAU8810_REG_CLOCK, NAU8810_MCLKSEL_MASK,
		pll_param->mclk_scaler << NAU8810_MCLKSEL_SFT);
	regmap_update_bits(map, NAU8810_REG_CLOCK,
		NAU8810_CLKM_MASK, NAU8810_CLKM_PLL);

	वापस 0;
पूर्ण

अटल पूर्णांक nau8810_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा nau8810 *nau8810 = snd_soc_component_get_drvdata(component);
	u16 ctrl1_val = 0, ctrl2_val = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		ctrl2_val |= NAU8810_CLKIO_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		ctrl1_val |= NAU8810_AIFMT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		ctrl1_val |= NAU8810_AIFMT_LEFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		ctrl1_val |= NAU8810_AIFMT_PCM_A;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		ctrl1_val |= NAU8810_BCLKP_IB | NAU8810_FSP_IF;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		ctrl1_val |= NAU8810_BCLKP_IB;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		ctrl1_val |= NAU8810_FSP_IF;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(nau8810->regmap, NAU8810_REG_IFACE,
		NAU8810_AIFMT_MASK | NAU8810_FSP_IF |
		NAU8810_BCLKP_IB, ctrl1_val);
	regmap_update_bits(nau8810->regmap, NAU8810_REG_CLOCK,
		NAU8810_CLKIO_MASK, ctrl2_val);

	वापस 0;
पूर्ण

अटल पूर्णांक nau8810_mclk_clkभाग(काष्ठा nau8810 *nau8810, पूर्णांक rate)
अणु
	पूर्णांक i, sclk, imclk = rate * 256, भाग = 0;

	अगर (!nau8810->sysclk) अणु
		dev_err(nau8810->dev, "Make mclk div configuration fail because of invalid system clock\n");
		वापस -EINVAL;
	पूर्ण

	/* Configure the master घड़ी prescaler भाग to make प्रणाली
	 * घड़ी to approximate the पूर्णांकernal master घड़ी (IMCLK);
	 * and large or equal to IMCLK.
	 */
	क्रम (i = 1; i < ARRAY_SIZE(nau8810_mclk_scaler); i++) अणु
		sclk = (nau8810->sysclk * 10) /
			nau8810_mclk_scaler[i];
		अगर (sclk < imclk)
			अवरोध;
		भाग = i;
	पूर्ण
	dev_dbg(nau8810->dev,
		"master clock prescaler %x for fs %d\n", भाग, rate);

	/* master घड़ी from MCLK and disable PLL */
	regmap_update_bits(nau8810->regmap, NAU8810_REG_CLOCK,
		NAU8810_MCLKSEL_MASK, (भाग << NAU8810_MCLKSEL_SFT));
	regmap_update_bits(nau8810->regmap, NAU8810_REG_CLOCK,
		NAU8810_CLKM_MASK, NAU8810_CLKM_MCLK);

	वापस 0;
पूर्ण

अटल पूर्णांक nau8810_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा nau8810 *nau8810 = snd_soc_component_get_drvdata(component);
	पूर्णांक val_len = 0, val_rate = 0, ret = 0;
	अचिन्हित पूर्णांक ctrl_val, bclk_fs, bclk_भाग;

	/* Select BCLK configuration अगर the codec as master. */
	regmap_पढ़ो(nau8810->regmap, NAU8810_REG_CLOCK, &ctrl_val);
	अगर (ctrl_val & NAU8810_CLKIO_MASTER) अणु
		/* get the bclk and fs ratio */
		bclk_fs = snd_soc_params_to_bclk(params) / params_rate(params);
		अगर (bclk_fs <= 32)
			bclk_भाग = NAU8810_BCLKDIV_8;
		अन्यथा अगर (bclk_fs <= 64)
			bclk_भाग = NAU8810_BCLKDIV_4;
		अन्यथा अगर (bclk_fs <= 128)
			bclk_भाग = NAU8810_BCLKDIV_2;
		अन्यथा
			वापस -EINVAL;
		regmap_update_bits(nau8810->regmap, NAU8810_REG_CLOCK,
			NAU8810_BCLKSEL_MASK, bclk_भाग);
	पूर्ण

	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		val_len |= NAU8810_WLEN_20;
		अवरोध;
	हाल 24:
		val_len |= NAU8810_WLEN_24;
		अवरोध;
	हाल 32:
		val_len |= NAU8810_WLEN_32;
		अवरोध;
	पूर्ण

	चयन (params_rate(params)) अणु
	हाल 8000:
		val_rate |= NAU8810_SMPLR_8K;
		अवरोध;
	हाल 11025:
		val_rate |= NAU8810_SMPLR_12K;
		अवरोध;
	हाल 16000:
		val_rate |= NAU8810_SMPLR_16K;
		अवरोध;
	हाल 22050:
		val_rate |= NAU8810_SMPLR_24K;
		अवरोध;
	हाल 32000:
		val_rate |= NAU8810_SMPLR_32K;
		अवरोध;
	हाल 44100:
	हाल 48000:
		अवरोध;
	पूर्ण

	regmap_update_bits(nau8810->regmap, NAU8810_REG_IFACE,
		NAU8810_WLEN_MASK, val_len);
	regmap_update_bits(nau8810->regmap, NAU8810_REG_SMPLR,
		NAU8810_SMPLR_MASK, val_rate);

	/* If the master घड़ी is from MCLK, provide the runसमय FS क्रम driver
	 * to get the master घड़ी prescaler configuration.
	 */
	अगर (nau8810->clk_id == NAU8810_SCLK_MCLK) अणु
		ret = nau8810_mclk_clkभाग(nau8810, params_rate(params));
		अगर (ret < 0)
			dev_err(nau8810->dev, "MCLK div configuration fail\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक nau8810_set_bias_level(काष्ठा snd_soc_component *component,
	क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा nau8810 *nau8810 = snd_soc_component_get_drvdata(component);
	काष्ठा regmap *map = nau8810->regmap;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
		regmap_update_bits(map, NAU8810_REG_POWER1,
			NAU8810_REFIMP_MASK, NAU8810_REFIMP_80K);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		regmap_update_bits(map, NAU8810_REG_POWER1,
			NAU8810_IOBUF_EN | NAU8810_ABIAS_EN,
			NAU8810_IOBUF_EN | NAU8810_ABIAS_EN);

		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			regcache_sync(map);
			regmap_update_bits(map, NAU8810_REG_POWER1,
				NAU8810_REFIMP_MASK, NAU8810_REFIMP_3K);
			mdelay(100);
		पूर्ण
		regmap_update_bits(map, NAU8810_REG_POWER1,
			NAU8810_REFIMP_MASK, NAU8810_REFIMP_300K);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		regmap_ग_लिखो(map, NAU8810_REG_POWER1, 0);
		regmap_ग_लिखो(map, NAU8810_REG_POWER2, 0);
		regmap_ग_लिखो(map, NAU8810_REG_POWER3, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण


#घोषणा NAU8810_RATES (SNDRV_PCM_RATE_8000_48000)

#घोषणा NAU8810_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
	SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops nau8810_ops = अणु
	.hw_params = nau8810_pcm_hw_params,
	.set_fmt = nau8810_set_dai_fmt,
	.set_sysclk = nau8810_set_sysclk,
	.set_pll = nau8810_set_pll,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver nau8810_dai = अणु
	.name = "nau8810-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,   /* Only 1 channel of data */
		.rates = NAU8810_RATES,
		.क्रमmats = NAU8810_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,   /* Only 1 channel of data */
		.rates = NAU8810_RATES,
		.क्रमmats = NAU8810_FORMATS,
	पूर्ण,
	.ops = &nau8810_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config nau8810_regmap_config = अणु
	.reg_bits = 7,
	.val_bits = 9,

	.max_रेजिस्टर = NAU8810_REG_MAX,
	.पढ़ोable_reg = nau8810_पढ़ोable_reg,
	.ग_लिखोable_reg = nau8810_ग_लिखोable_reg,
	.अस्थिर_reg = nau8810_अस्थिर_reg,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = nau8810_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(nau8810_reg_शेषs),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver nau8810_component_driver = अणु
	.set_bias_level		= nau8810_set_bias_level,
	.controls		= nau8810_snd_controls,
	.num_controls		= ARRAY_SIZE(nau8810_snd_controls),
	.dapm_widमाला_लो		= nau8810_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(nau8810_dapm_widमाला_लो),
	.dapm_routes		= nau8810_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(nau8810_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक nau8810_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &i2c->dev;
	काष्ठा nau8810 *nau8810 = dev_get_platdata(dev);

	अगर (!nau8810) अणु
		nau8810 = devm_kzalloc(dev, माप(*nau8810), GFP_KERNEL);
		अगर (!nau8810)
			वापस -ENOMEM;
	पूर्ण
	i2c_set_clientdata(i2c, nau8810);

	nau8810->regmap = devm_regmap_init_i2c(i2c, &nau8810_regmap_config);
	अगर (IS_ERR(nau8810->regmap))
		वापस PTR_ERR(nau8810->regmap);
	nau8810->dev = dev;

	regmap_ग_लिखो(nau8810->regmap, NAU8810_REG_RESET, 0x00);

	वापस devm_snd_soc_रेजिस्टर_component(dev,
		&nau8810_component_driver, &nau8810_dai, 1);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id nau8810_i2c_id[] = अणु
	अणु "nau8810", 0 पूर्ण,
	अणु "nau8812", 0 पूर्ण,
	अणु "nau8814", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, nau8810_i2c_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id nau8810_of_match[] = अणु
	अणु .compatible = "nuvoton,nau8810", पूर्ण,
	अणु .compatible = "nuvoton,nau8812", पूर्ण,
	अणु .compatible = "nuvoton,nau8814", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, nau8810_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver nau8810_i2c_driver = अणु
	.driver = अणु
		.name = "nau8810",
		.of_match_table = of_match_ptr(nau8810_of_match),
	पूर्ण,
	.probe =    nau8810_i2c_probe,
	.id_table = nau8810_i2c_id,
पूर्ण;

module_i2c_driver(nau8810_i2c_driver);

MODULE_DESCRIPTION("ASoC NAU8810 driver");
MODULE_AUTHOR("David Lin <ctlin0@nuvoton.com>");
MODULE_LICENSE("GPL v2");
