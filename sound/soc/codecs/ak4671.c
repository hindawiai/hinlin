<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ak4671.c  --  audio driver क्रम AK4671
 *
 * Copyright (C) 2009 Samsung Electronics Co.Ltd
 * Author: Joonyoung Shim <jy0922.shim@samsung.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "ak4671.h"


/* ak4671 रेजिस्टर cache & शेष रेजिस्टर settings */
अटल स्थिर काष्ठा reg_शेष ak4671_reg_शेषs[] = अणु
	अणु 0x00, 0x00 पूर्ण,	/* AK4671_AD_DA_POWER_MANAGEMENT	(0x00)	*/
	अणु 0x01, 0xf6 पूर्ण,	/* AK4671_PLL_MODE_SELECT0		(0x01)	*/
	अणु 0x02, 0x00 पूर्ण,	/* AK4671_PLL_MODE_SELECT1		(0x02)	*/
	अणु 0x03, 0x02 पूर्ण,	/* AK4671_FORMAT_SELECT			(0x03)	*/
	अणु 0x04, 0x00 पूर्ण,	/* AK4671_MIC_SIGNAL_SELECT		(0x04)	*/
	अणु 0x05, 0x55 पूर्ण,	/* AK4671_MIC_AMP_GAIN			(0x05)	*/
	अणु 0x06, 0x00 पूर्ण,	/* AK4671_MIXING_POWER_MANAGEMENT0	(0x06)	*/
	अणु 0x07, 0x00 पूर्ण,	/* AK4671_MIXING_POWER_MANAGEMENT1	(0x07)	*/
	अणु 0x08, 0xb5 पूर्ण,	/* AK4671_OUTPUT_VOLUME_CONTROL		(0x08)	*/
	अणु 0x09, 0x00 पूर्ण,	/* AK4671_LOUT1_SIGNAL_SELECT		(0x09)	*/
	अणु 0x0a, 0x00 पूर्ण,	/* AK4671_ROUT1_SIGNAL_SELECT		(0x0a)	*/
	अणु 0x0b, 0x00 पूर्ण,	/* AK4671_LOUT2_SIGNAL_SELECT		(0x0b)	*/
	अणु 0x0c, 0x00 पूर्ण,	/* AK4671_ROUT2_SIGNAL_SELECT		(0x0c)	*/
	अणु 0x0d, 0x00 पूर्ण,	/* AK4671_LOUT3_SIGNAL_SELECT		(0x0d)	*/
	अणु 0x0e, 0x00 पूर्ण,	/* AK4671_ROUT3_SIGNAL_SELECT		(0x0e)	*/
	अणु 0x0f, 0x00 पूर्ण,	/* AK4671_LOUT1_POWER_MANAGERMENT	(0x0f)	*/
	अणु 0x10, 0x00 पूर्ण,	/* AK4671_LOUT2_POWER_MANAGERMENT	(0x10)	*/
	अणु 0x11, 0x80 पूर्ण,	/* AK4671_LOUT3_POWER_MANAGERMENT	(0x11)	*/
	अणु 0x12, 0x91 पूर्ण,	/* AK4671_LCH_INPUT_VOLUME_CONTROL	(0x12)	*/
	अणु 0x13, 0x91 पूर्ण,	/* AK4671_RCH_INPUT_VOLUME_CONTROL	(0x13)	*/
	अणु 0x14, 0xe1 पूर्ण,	/* AK4671_ALC_REFERENCE_SELECT		(0x14)	*/
	अणु 0x15, 0x00 पूर्ण,	/* AK4671_DIGITAL_MIXING_CONTROL	(0x15)	*/
	अणु 0x16, 0x00 पूर्ण,	/* AK4671_ALC_TIMER_SELECT		(0x16)	*/
	अणु 0x17, 0x00 पूर्ण,	/* AK4671_ALC_MODE_CONTROL		(0x17)	*/
	अणु 0x18, 0x02 पूर्ण,	/* AK4671_MODE_CONTROL1			(0x18)	*/
	अणु 0x19, 0x01 पूर्ण,	/* AK4671_MODE_CONTROL2			(0x19)	*/
	अणु 0x1a, 0x18 पूर्ण,	/* AK4671_LCH_OUTPUT_VOLUME_CONTROL	(0x1a)	*/
	अणु 0x1b, 0x18 पूर्ण,	/* AK4671_RCH_OUTPUT_VOLUME_CONTROL	(0x1b)	*/
	अणु 0x1c, 0x00 पूर्ण,	/* AK4671_SIDETONE_A_CONTROL		(0x1c)	*/
	अणु 0x1d, 0x02 पूर्ण,	/* AK4671_DIGITAL_FILTER_SELECT		(0x1d)	*/
	अणु 0x1e, 0x00 पूर्ण,	/* AK4671_FIL3_COEFFICIENT0		(0x1e)	*/
	अणु 0x1f, 0x00 पूर्ण,	/* AK4671_FIL3_COEFFICIENT1		(0x1f)	*/
	अणु 0x20, 0x00 पूर्ण,	/* AK4671_FIL3_COEFFICIENT2		(0x20)	*/
	अणु 0x21, 0x00 पूर्ण,	/* AK4671_FIL3_COEFFICIENT3		(0x21)	*/
	अणु 0x22, 0x00 पूर्ण,	/* AK4671_EQ_COEFFICIENT0		(0x22)	*/
	अणु 0x23, 0x00 पूर्ण,	/* AK4671_EQ_COEFFICIENT1		(0x23)	*/
	अणु 0x24, 0x00 पूर्ण,	/* AK4671_EQ_COEFFICIENT2		(0x24)	*/
	अणु 0x25, 0x00 पूर्ण,	/* AK4671_EQ_COEFFICIENT3		(0x25)	*/
	अणु 0x26, 0x00 पूर्ण,	/* AK4671_EQ_COEFFICIENT4		(0x26)	*/
	अणु 0x27, 0x00 पूर्ण,	/* AK4671_EQ_COEFFICIENT5		(0x27)	*/
	अणु 0x28, 0xa9 पूर्ण,	/* AK4671_FIL1_COEFFICIENT0		(0x28)	*/
	अणु 0x29, 0x1f पूर्ण,	/* AK4671_FIL1_COEFFICIENT1		(0x29)	*/
	अणु 0x2a, 0xad पूर्ण,	/* AK4671_FIL1_COEFFICIENT2		(0x2a)	*/
	अणु 0x2b, 0x20 पूर्ण,	/* AK4671_FIL1_COEFFICIENT3		(0x2b)	*/
	अणु 0x2c, 0x00 पूर्ण,	/* AK4671_FIL2_COEFFICIENT0		(0x2c)	*/
	अणु 0x2d, 0x00 पूर्ण,	/* AK4671_FIL2_COEFFICIENT1		(0x2d)	*/
	अणु 0x2e, 0x00 पूर्ण,	/* AK4671_FIL2_COEFFICIENT2		(0x2e)	*/
	अणु 0x2f, 0x00 पूर्ण,	/* AK4671_FIL2_COEFFICIENT3		(0x2f)	*/
	अणु 0x30, 0x00 पूर्ण,	/* AK4671_DIGITAL_FILTER_SELECT2	(0x30)	*/

	अणु 0x32, 0x00 पूर्ण,	/* AK4671_E1_COEFFICIENT0		(0x32)	*/
	अणु 0x33, 0x00 पूर्ण,	/* AK4671_E1_COEFFICIENT1		(0x33)	*/
	अणु 0x34, 0x00 पूर्ण,	/* AK4671_E1_COEFFICIENT2		(0x34)	*/
	अणु 0x35, 0x00 पूर्ण,	/* AK4671_E1_COEFFICIENT3		(0x35)	*/
	अणु 0x36, 0x00 पूर्ण,	/* AK4671_E1_COEFFICIENT4		(0x36)	*/
	अणु 0x37, 0x00 पूर्ण,	/* AK4671_E1_COEFFICIENT5		(0x37)	*/
	अणु 0x38, 0x00 पूर्ण,	/* AK4671_E2_COEFFICIENT0		(0x38)	*/
	अणु 0x39, 0x00 पूर्ण,	/* AK4671_E2_COEFFICIENT1		(0x39)	*/
	अणु 0x3a, 0x00 पूर्ण,	/* AK4671_E2_COEFFICIENT2		(0x3a)	*/
	अणु 0x3b, 0x00 पूर्ण,	/* AK4671_E2_COEFFICIENT3		(0x3b)	*/
	अणु 0x3c, 0x00 पूर्ण,	/* AK4671_E2_COEFFICIENT4		(0x3c)	*/
	अणु 0x3d, 0x00 पूर्ण,	/* AK4671_E2_COEFFICIENT5		(0x3d)	*/
	अणु 0x3e, 0x00 पूर्ण,	/* AK4671_E3_COEFFICIENT0		(0x3e)	*/
	अणु 0x3f, 0x00 पूर्ण,	/* AK4671_E3_COEFFICIENT1		(0x3f)	*/
	अणु 0x40, 0x00 पूर्ण,	/* AK4671_E3_COEFFICIENT2		(0x40)	*/
	अणु 0x41, 0x00 पूर्ण,	/* AK4671_E3_COEFFICIENT3		(0x41)	*/
	अणु 0x42, 0x00 पूर्ण,	/* AK4671_E3_COEFFICIENT4		(0x42)	*/
	अणु 0x43, 0x00 पूर्ण,	/* AK4671_E3_COEFFICIENT5		(0x43)	*/
	अणु 0x44, 0x00 पूर्ण,	/* AK4671_E4_COEFFICIENT0		(0x44)	*/
	अणु 0x45, 0x00 पूर्ण,	/* AK4671_E4_COEFFICIENT1		(0x45)	*/
	अणु 0x46, 0x00 पूर्ण,	/* AK4671_E4_COEFFICIENT2		(0x46)	*/
	अणु 0x47, 0x00 पूर्ण,	/* AK4671_E4_COEFFICIENT3		(0x47)	*/
	अणु 0x48, 0x00 पूर्ण,	/* AK4671_E4_COEFFICIENT4		(0x48)	*/
	अणु 0x49, 0x00 पूर्ण,	/* AK4671_E4_COEFFICIENT5		(0x49)	*/
	अणु 0x4a, 0x00 पूर्ण,	/* AK4671_E5_COEFFICIENT0		(0x4a)	*/
	अणु 0x4b, 0x00 पूर्ण,	/* AK4671_E5_COEFFICIENT1		(0x4b)	*/
	अणु 0x4c, 0x00 पूर्ण,	/* AK4671_E5_COEFFICIENT2		(0x4c)	*/
	अणु 0x4d, 0x00 पूर्ण,	/* AK4671_E5_COEFFICIENT3		(0x4d)	*/
	अणु 0x4e, 0x00 पूर्ण,	/* AK4671_E5_COEFFICIENT4		(0x4e)	*/
	अणु 0x4f, 0x00 पूर्ण,	/* AK4671_E5_COEFFICIENT5		(0x4f)	*/
	अणु 0x50, 0x88 पूर्ण,	/* AK4671_EQ_CONTROL_250HZ_100HZ	(0x50)	*/
	अणु 0x51, 0x88 पूर्ण,	/* AK4671_EQ_CONTROL_3500HZ_1KHZ	(0x51)	*/
	अणु 0x52, 0x08 पूर्ण,	/* AK4671_EQ_CONTRO_10KHZ		(0x52)	*/
	अणु 0x53, 0x00 पूर्ण,	/* AK4671_PCM_IF_CONTROL0		(0x53)	*/
	अणु 0x54, 0x00 पूर्ण,	/* AK4671_PCM_IF_CONTROL1		(0x54)	*/
	अणु 0x55, 0x00 पूर्ण,	/* AK4671_PCM_IF_CONTROL2		(0x55)	*/
	अणु 0x56, 0x18 पूर्ण,	/* AK4671_DIGITAL_VOLUME_B_CONTROL	(0x56)	*/
	अणु 0x57, 0x18 पूर्ण,	/* AK4671_DIGITAL_VOLUME_C_CONTROL	(0x57)	*/
	अणु 0x58, 0x00 पूर्ण,	/* AK4671_SIDETONE_VOLUME_CONTROL	(0x58)	*/
	अणु 0x59, 0x00 पूर्ण,	/* AK4671_DIGITAL_MIXING_CONTROL2	(0x59)	*/
	अणु 0x5a, 0x00 पूर्ण,	/* AK4671_SAR_ADC_CONTROL		(0x5a)	*/
पूर्ण;

/*
 * LOUT1/ROUT1 output volume control:
 * from -24 to 6 dB in 6 dB steps (mute instead of -30 dB)
 */
अटल DECLARE_TLV_DB_SCALE(out1_tlv, -3000, 600, 1);

/*
 * LOUT2/ROUT2 output volume control:
 * from -33 to 6 dB in 3 dB steps (mute instead of -33 dB)
 */
अटल DECLARE_TLV_DB_SCALE(out2_tlv, -3300, 300, 1);

/*
 * LOUT3/ROUT3 output volume control:
 * from -6 to 3 dB in 3 dB steps
 */
अटल DECLARE_TLV_DB_SCALE(out3_tlv, -600, 300, 0);

/*
 * Mic amp gain control:
 * from -15 to 30 dB in 3 dB steps
 * REVISIT: The actual min value(0x01) is -12 dB and the reg value 0x00 is not
 * available
 */
अटल DECLARE_TLV_DB_SCALE(mic_amp_tlv, -1500, 300, 0);

अटल स्थिर काष्ठा snd_kcontrol_new ak4671_snd_controls[] = अणु
	/* Common playback gain controls */
	SOC_SINGLE_TLV("Line Output1 Playback Volume",
			AK4671_OUTPUT_VOLUME_CONTROL, 0, 0x6, 0, out1_tlv),
	SOC_SINGLE_TLV("Headphone Output2 Playback Volume",
			AK4671_OUTPUT_VOLUME_CONTROL, 4, 0xd, 0, out2_tlv),
	SOC_SINGLE_TLV("Line Output3 Playback Volume",
			AK4671_LOUT3_POWER_MANAGERMENT, 6, 0x3, 0, out3_tlv),

	/* Common capture gain controls */
	SOC_DOUBLE_TLV("Mic Amp Capture Volume",
			AK4671_MIC_AMP_GAIN, 0, 4, 0xf, 0, mic_amp_tlv),
पूर्ण;

/* event handlers */
अटल पूर्णांक ak4671_out2_event(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, AK4671_LOUT2_POWER_MANAGERMENT,
				    AK4671_MUTEN, AK4671_MUTEN);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, AK4671_LOUT2_POWER_MANAGERMENT,
				    AK4671_MUTEN, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* Output Mixers */
अटल स्थिर काष्ठा snd_kcontrol_new ak4671_lout1_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("DACL", AK4671_LOUT1_SIGNAL_SELECT, 0, 1, 0),
	SOC_DAPM_SINGLE("LINL1", AK4671_LOUT1_SIGNAL_SELECT, 1, 1, 0),
	SOC_DAPM_SINGLE("LINL2", AK4671_LOUT1_SIGNAL_SELECT, 2, 1, 0),
	SOC_DAPM_SINGLE("LINL3", AK4671_LOUT1_SIGNAL_SELECT, 3, 1, 0),
	SOC_DAPM_SINGLE("LINL4", AK4671_LOUT1_SIGNAL_SELECT, 4, 1, 0),
	SOC_DAPM_SINGLE("LOOPL", AK4671_LOUT1_SIGNAL_SELECT, 5, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ak4671_rout1_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("DACR", AK4671_ROUT1_SIGNAL_SELECT, 0, 1, 0),
	SOC_DAPM_SINGLE("RINR1", AK4671_ROUT1_SIGNAL_SELECT, 1, 1, 0),
	SOC_DAPM_SINGLE("RINR2", AK4671_ROUT1_SIGNAL_SELECT, 2, 1, 0),
	SOC_DAPM_SINGLE("RINR3", AK4671_ROUT1_SIGNAL_SELECT, 3, 1, 0),
	SOC_DAPM_SINGLE("RINR4", AK4671_ROUT1_SIGNAL_SELECT, 4, 1, 0),
	SOC_DAPM_SINGLE("LOOPR", AK4671_ROUT1_SIGNAL_SELECT, 5, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ak4671_lout2_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("DACHL", AK4671_LOUT2_SIGNAL_SELECT, 0, 1, 0),
	SOC_DAPM_SINGLE("LINH1", AK4671_LOUT2_SIGNAL_SELECT, 1, 1, 0),
	SOC_DAPM_SINGLE("LINH2", AK4671_LOUT2_SIGNAL_SELECT, 2, 1, 0),
	SOC_DAPM_SINGLE("LINH3", AK4671_LOUT2_SIGNAL_SELECT, 3, 1, 0),
	SOC_DAPM_SINGLE("LINH4", AK4671_LOUT2_SIGNAL_SELECT, 4, 1, 0),
	SOC_DAPM_SINGLE("LOOPHL", AK4671_LOUT2_SIGNAL_SELECT, 5, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ak4671_rout2_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("DACHR", AK4671_ROUT2_SIGNAL_SELECT, 0, 1, 0),
	SOC_DAPM_SINGLE("RINH1", AK4671_ROUT2_SIGNAL_SELECT, 1, 1, 0),
	SOC_DAPM_SINGLE("RINH2", AK4671_ROUT2_SIGNAL_SELECT, 2, 1, 0),
	SOC_DAPM_SINGLE("RINH3", AK4671_ROUT2_SIGNAL_SELECT, 3, 1, 0),
	SOC_DAPM_SINGLE("RINH4", AK4671_ROUT2_SIGNAL_SELECT, 4, 1, 0),
	SOC_DAPM_SINGLE("LOOPHR", AK4671_ROUT2_SIGNAL_SELECT, 5, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ak4671_lout3_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("DACSL", AK4671_LOUT3_SIGNAL_SELECT, 0, 1, 0),
	SOC_DAPM_SINGLE("LINS1", AK4671_LOUT3_SIGNAL_SELECT, 1, 1, 0),
	SOC_DAPM_SINGLE("LINS2", AK4671_LOUT3_SIGNAL_SELECT, 2, 1, 0),
	SOC_DAPM_SINGLE("LINS3", AK4671_LOUT3_SIGNAL_SELECT, 3, 1, 0),
	SOC_DAPM_SINGLE("LINS4", AK4671_LOUT3_SIGNAL_SELECT, 4, 1, 0),
	SOC_DAPM_SINGLE("LOOPSL", AK4671_LOUT3_SIGNAL_SELECT, 5, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ak4671_rout3_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("DACSR", AK4671_ROUT3_SIGNAL_SELECT, 0, 1, 0),
	SOC_DAPM_SINGLE("RINS1", AK4671_ROUT3_SIGNAL_SELECT, 1, 1, 0),
	SOC_DAPM_SINGLE("RINS2", AK4671_ROUT3_SIGNAL_SELECT, 2, 1, 0),
	SOC_DAPM_SINGLE("RINS3", AK4671_ROUT3_SIGNAL_SELECT, 3, 1, 0),
	SOC_DAPM_SINGLE("RINS4", AK4671_ROUT3_SIGNAL_SELECT, 4, 1, 0),
	SOC_DAPM_SINGLE("LOOPSR", AK4671_ROUT3_SIGNAL_SELECT, 5, 1, 0),
पूर्ण;

/* Input MUXs */
अटल स्थिर अक्षर *ak4671_lin_mux_texts[] =
		अणु"LIN1", "LIN2", "LIN3", "LIN4"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(ak4671_lin_mux_क्रमागत,
			    AK4671_MIC_SIGNAL_SELECT, 0,
			    ak4671_lin_mux_texts);
अटल स्थिर काष्ठा snd_kcontrol_new ak4671_lin_mux_control =
	SOC_DAPM_ENUM("Route", ak4671_lin_mux_क्रमागत);

अटल स्थिर अक्षर *ak4671_rin_mux_texts[] =
		अणु"RIN1", "RIN2", "RIN3", "RIN4"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(ak4671_rin_mux_क्रमागत,
			    AK4671_MIC_SIGNAL_SELECT, 2,
			    ak4671_rin_mux_texts);
अटल स्थिर काष्ठा snd_kcontrol_new ak4671_rin_mux_control =
	SOC_DAPM_ENUM("Route", ak4671_rin_mux_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget ak4671_dapm_widमाला_लो[] = अणु
	/* Inमाला_दो */
	SND_SOC_DAPM_INPUT("LIN1"),
	SND_SOC_DAPM_INPUT("RIN1"),
	SND_SOC_DAPM_INPUT("LIN2"),
	SND_SOC_DAPM_INPUT("RIN2"),
	SND_SOC_DAPM_INPUT("LIN3"),
	SND_SOC_DAPM_INPUT("RIN3"),
	SND_SOC_DAPM_INPUT("LIN4"),
	SND_SOC_DAPM_INPUT("RIN4"),

	/* Outमाला_दो */
	SND_SOC_DAPM_OUTPUT("LOUT1"),
	SND_SOC_DAPM_OUTPUT("ROUT1"),
	SND_SOC_DAPM_OUTPUT("LOUT2"),
	SND_SOC_DAPM_OUTPUT("ROUT2"),
	SND_SOC_DAPM_OUTPUT("LOUT3"),
	SND_SOC_DAPM_OUTPUT("ROUT3"),

	/* DAC */
	SND_SOC_DAPM_DAC("DAC Left", "Left HiFi Playback",
			AK4671_AD_DA_POWER_MANAGEMENT, 6, 0),
	SND_SOC_DAPM_DAC("DAC Right", "Right HiFi Playback",
			AK4671_AD_DA_POWER_MANAGEMENT, 7, 0),

	/* ADC */
	SND_SOC_DAPM_ADC("ADC Left", "Left HiFi Capture",
			AK4671_AD_DA_POWER_MANAGEMENT, 4, 0),
	SND_SOC_DAPM_ADC("ADC Right", "Right HiFi Capture",
			AK4671_AD_DA_POWER_MANAGEMENT, 5, 0),

	/* PGA */
	SND_SOC_DAPM_PGA("LOUT2 Mix Amp",
			AK4671_LOUT2_POWER_MANAGERMENT, 5, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("ROUT2 Mix Amp",
			AK4671_LOUT2_POWER_MANAGERMENT, 6, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("LIN1 Mixing Circuit",
			AK4671_MIXING_POWER_MANAGEMENT1, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("RIN1 Mixing Circuit",
			AK4671_MIXING_POWER_MANAGEMENT1, 1, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("LIN2 Mixing Circuit",
			AK4671_MIXING_POWER_MANAGEMENT1, 2, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("RIN2 Mixing Circuit",
			AK4671_MIXING_POWER_MANAGEMENT1, 3, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("LIN3 Mixing Circuit",
			AK4671_MIXING_POWER_MANAGEMENT1, 4, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("RIN3 Mixing Circuit",
			AK4671_MIXING_POWER_MANAGEMENT1, 5, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("LIN4 Mixing Circuit",
			AK4671_MIXING_POWER_MANAGEMENT1, 6, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("RIN4 Mixing Circuit",
			AK4671_MIXING_POWER_MANAGEMENT1, 7, 0, शून्य, 0),

	/* Output Mixers */
	SND_SOC_DAPM_MIXER("LOUT1 Mixer", AK4671_LOUT1_POWER_MANAGERMENT, 0, 0,
			&ak4671_lout1_mixer_controls[0],
			ARRAY_SIZE(ak4671_lout1_mixer_controls)),
	SND_SOC_DAPM_MIXER("ROUT1 Mixer", AK4671_LOUT1_POWER_MANAGERMENT, 1, 0,
			&ak4671_rout1_mixer_controls[0],
			ARRAY_SIZE(ak4671_rout1_mixer_controls)),
	SND_SOC_DAPM_MIXER_E("LOUT2 Mixer", AK4671_LOUT2_POWER_MANAGERMENT,
			0, 0, &ak4671_lout2_mixer_controls[0],
			ARRAY_SIZE(ak4671_lout2_mixer_controls),
			ak4671_out2_event,
			SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_MIXER_E("ROUT2 Mixer", AK4671_LOUT2_POWER_MANAGERMENT,
			1, 0, &ak4671_rout2_mixer_controls[0],
			ARRAY_SIZE(ak4671_rout2_mixer_controls),
			ak4671_out2_event,
			SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_MIXER("LOUT3 Mixer", AK4671_LOUT3_POWER_MANAGERMENT, 0, 0,
			&ak4671_lout3_mixer_controls[0],
			ARRAY_SIZE(ak4671_lout3_mixer_controls)),
	SND_SOC_DAPM_MIXER("ROUT3 Mixer", AK4671_LOUT3_POWER_MANAGERMENT, 1, 0,
			&ak4671_rout3_mixer_controls[0],
			ARRAY_SIZE(ak4671_rout3_mixer_controls)),

	/* Input MUXs */
	SND_SOC_DAPM_MUX("LIN MUX", AK4671_AD_DA_POWER_MANAGEMENT, 2, 0,
			&ak4671_lin_mux_control),
	SND_SOC_DAPM_MUX("RIN MUX", AK4671_AD_DA_POWER_MANAGEMENT, 3, 0,
			&ak4671_rin_mux_control),

	/* Mic Power */
	SND_SOC_DAPM_MICBIAS("Mic Bias", AK4671_AD_DA_POWER_MANAGEMENT, 1, 0),

	/* Supply */
	SND_SOC_DAPM_SUPPLY("PMPLL", AK4671_PLL_MODE_SELECT1, 0, 0, शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ak4671_पूर्णांकercon[] = अणु
	अणु"DAC Left", शून्य, "PMPLL"पूर्ण,
	अणु"DAC Right", शून्य, "PMPLL"पूर्ण,
	अणु"ADC Left", शून्य, "PMPLL"पूर्ण,
	अणु"ADC Right", शून्य, "PMPLL"पूर्ण,

	/* Outमाला_दो */
	अणु"LOUT1", शून्य, "LOUT1 Mixer"पूर्ण,
	अणु"ROUT1", शून्य, "ROUT1 Mixer"पूर्ण,
	अणु"LOUT2", शून्य, "LOUT2 Mix Amp"पूर्ण,
	अणु"ROUT2", शून्य, "ROUT2 Mix Amp"पूर्ण,
	अणु"LOUT3", शून्य, "LOUT3 Mixer"पूर्ण,
	अणु"ROUT3", शून्य, "ROUT3 Mixer"पूर्ण,

	अणु"LOUT1 Mixer", "DACL", "DAC Left"पूर्ण,
	अणु"ROUT1 Mixer", "DACR", "DAC Right"पूर्ण,
	अणु"LOUT2 Mixer", "DACHL", "DAC Left"पूर्ण,
	अणु"ROUT2 Mixer", "DACHR", "DAC Right"पूर्ण,
	अणु"LOUT2 Mix Amp", शून्य, "LOUT2 Mixer"पूर्ण,
	अणु"ROUT2 Mix Amp", शून्य, "ROUT2 Mixer"पूर्ण,
	अणु"LOUT3 Mixer", "DACSL", "DAC Left"पूर्ण,
	अणु"ROUT3 Mixer", "DACSR", "DAC Right"पूर्ण,

	/* Inमाला_दो */
	अणु"LIN MUX", "LIN1", "LIN1"पूर्ण,
	अणु"LIN MUX", "LIN2", "LIN2"पूर्ण,
	अणु"LIN MUX", "LIN3", "LIN3"पूर्ण,
	अणु"LIN MUX", "LIN4", "LIN4"पूर्ण,

	अणु"RIN MUX", "RIN1", "RIN1"पूर्ण,
	अणु"RIN MUX", "RIN2", "RIN2"पूर्ण,
	अणु"RIN MUX", "RIN3", "RIN3"पूर्ण,
	अणु"RIN MUX", "RIN4", "RIN4"पूर्ण,

	अणु"LIN1", शून्य, "Mic Bias"पूर्ण,
	अणु"RIN1", शून्य, "Mic Bias"पूर्ण,
	अणु"LIN2", शून्य, "Mic Bias"पूर्ण,
	अणु"RIN2", शून्य, "Mic Bias"पूर्ण,

	अणु"ADC Left", शून्य, "LIN MUX"पूर्ण,
	अणु"ADC Right", शून्य, "RIN MUX"पूर्ण,

	/* Analog Loops */
	अणु"LIN1 Mixing Circuit", शून्य, "LIN1"पूर्ण,
	अणु"RIN1 Mixing Circuit", शून्य, "RIN1"पूर्ण,
	अणु"LIN2 Mixing Circuit", शून्य, "LIN2"पूर्ण,
	अणु"RIN2 Mixing Circuit", शून्य, "RIN2"पूर्ण,
	अणु"LIN3 Mixing Circuit", शून्य, "LIN3"पूर्ण,
	अणु"RIN3 Mixing Circuit", शून्य, "RIN3"पूर्ण,
	अणु"LIN4 Mixing Circuit", शून्य, "LIN4"पूर्ण,
	अणु"RIN4 Mixing Circuit", शून्य, "RIN4"पूर्ण,

	अणु"LOUT1 Mixer", "LINL1", "LIN1 Mixing Circuit"पूर्ण,
	अणु"ROUT1 Mixer", "RINR1", "RIN1 Mixing Circuit"पूर्ण,
	अणु"LOUT2 Mixer", "LINH1", "LIN1 Mixing Circuit"पूर्ण,
	अणु"ROUT2 Mixer", "RINH1", "RIN1 Mixing Circuit"पूर्ण,
	अणु"LOUT3 Mixer", "LINS1", "LIN1 Mixing Circuit"पूर्ण,
	अणु"ROUT3 Mixer", "RINS1", "RIN1 Mixing Circuit"पूर्ण,

	अणु"LOUT1 Mixer", "LINL2", "LIN2 Mixing Circuit"पूर्ण,
	अणु"ROUT1 Mixer", "RINR2", "RIN2 Mixing Circuit"पूर्ण,
	अणु"LOUT2 Mixer", "LINH2", "LIN2 Mixing Circuit"पूर्ण,
	अणु"ROUT2 Mixer", "RINH2", "RIN2 Mixing Circuit"पूर्ण,
	अणु"LOUT3 Mixer", "LINS2", "LIN2 Mixing Circuit"पूर्ण,
	अणु"ROUT3 Mixer", "RINS2", "RIN2 Mixing Circuit"पूर्ण,

	अणु"LOUT1 Mixer", "LINL3", "LIN3 Mixing Circuit"पूर्ण,
	अणु"ROUT1 Mixer", "RINR3", "RIN3 Mixing Circuit"पूर्ण,
	अणु"LOUT2 Mixer", "LINH3", "LIN3 Mixing Circuit"पूर्ण,
	अणु"ROUT2 Mixer", "RINH3", "RIN3 Mixing Circuit"पूर्ण,
	अणु"LOUT3 Mixer", "LINS3", "LIN3 Mixing Circuit"पूर्ण,
	अणु"ROUT3 Mixer", "RINS3", "RIN3 Mixing Circuit"पूर्ण,

	अणु"LOUT1 Mixer", "LINL4", "LIN4 Mixing Circuit"पूर्ण,
	अणु"ROUT1 Mixer", "RINR4", "RIN4 Mixing Circuit"पूर्ण,
	अणु"LOUT2 Mixer", "LINH4", "LIN4 Mixing Circuit"पूर्ण,
	अणु"ROUT2 Mixer", "RINH4", "RIN4 Mixing Circuit"पूर्ण,
	अणु"LOUT3 Mixer", "LINS4", "LIN4 Mixing Circuit"पूर्ण,
	अणु"ROUT3 Mixer", "RINS4", "RIN4 Mixing Circuit"पूर्ण,
पूर्ण;

अटल पूर्णांक ak4671_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u8 fs;

	fs = snd_soc_component_पढ़ो(component, AK4671_PLL_MODE_SELECT0);
	fs &= ~AK4671_FS;

	चयन (params_rate(params)) अणु
	हाल 8000:
		fs |= AK4671_FS_8KHZ;
		अवरोध;
	हाल 12000:
		fs |= AK4671_FS_12KHZ;
		अवरोध;
	हाल 16000:
		fs |= AK4671_FS_16KHZ;
		अवरोध;
	हाल 24000:
		fs |= AK4671_FS_24KHZ;
		अवरोध;
	हाल 11025:
		fs |= AK4671_FS_11_025KHZ;
		अवरोध;
	हाल 22050:
		fs |= AK4671_FS_22_05KHZ;
		अवरोध;
	हाल 32000:
		fs |= AK4671_FS_32KHZ;
		अवरोध;
	हाल 44100:
		fs |= AK4671_FS_44_1KHZ;
		अवरोध;
	हाल 48000:
		fs |= AK4671_FS_48KHZ;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, AK4671_PLL_MODE_SELECT0, fs);

	वापस 0;
पूर्ण

अटल पूर्णांक ak4671_set_dai_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
		अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u8 pll;

	pll = snd_soc_component_पढ़ो(component, AK4671_PLL_MODE_SELECT0);
	pll &= ~AK4671_PLL;

	चयन (freq) अणु
	हाल 11289600:
		pll |= AK4671_PLL_11_2896MHZ;
		अवरोध;
	हाल 12000000:
		pll |= AK4671_PLL_12MHZ;
		अवरोध;
	हाल 12288000:
		pll |= AK4671_PLL_12_288MHZ;
		अवरोध;
	हाल 13000000:
		pll |= AK4671_PLL_13MHZ;
		अवरोध;
	हाल 13500000:
		pll |= AK4671_PLL_13_5MHZ;
		अवरोध;
	हाल 19200000:
		pll |= AK4671_PLL_19_2MHZ;
		अवरोध;
	हाल 24000000:
		pll |= AK4671_PLL_24MHZ;
		अवरोध;
	हाल 26000000:
		pll |= AK4671_PLL_26MHZ;
		अवरोध;
	हाल 27000000:
		pll |= AK4671_PLL_27MHZ;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, AK4671_PLL_MODE_SELECT0, pll);

	वापस 0;
पूर्ण

अटल पूर्णांक ak4671_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u8 mode;
	u8 क्रमmat;

	/* set master/slave audio पूर्णांकerface */
	mode = snd_soc_component_पढ़ो(component, AK4671_PLL_MODE_SELECT1);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		mode |= AK4671_M_S;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		mode &= ~(AK4671_M_S);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* पूर्णांकerface क्रमmat */
	क्रमmat = snd_soc_component_पढ़ो(component, AK4671_FORMAT_SELECT);
	क्रमmat &= ~AK4671_DIF;

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		क्रमmat |= AK4671_DIF_I2S_MODE;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		क्रमmat |= AK4671_DIF_MSB_MODE;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		क्रमmat |= AK4671_DIF_DSP_MODE;
		क्रमmat |= AK4671_BCKP;
		क्रमmat |= AK4671_MSBS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* set mode and क्रमmat */
	snd_soc_component_ग_लिखो(component, AK4671_PLL_MODE_SELECT1, mode);
	snd_soc_component_ग_लिखो(component, AK4671_FORMAT_SELECT, क्रमmat);

	वापस 0;
पूर्ण

अटल पूर्णांक ak4671_set_bias_level(काष्ठा snd_soc_component *component,
		क्रमागत snd_soc_bias_level level)
अणु
	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
	हाल SND_SOC_BIAS_STANDBY:
		snd_soc_component_update_bits(component, AK4671_AD_DA_POWER_MANAGEMENT,
				    AK4671_PMVCM, AK4671_PMVCM);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_ग_लिखो(component, AK4671_AD_DA_POWER_MANAGEMENT, 0x00);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा AK4671_RATES		(SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 |\
				SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_22050 |\
				SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |\
				SNDRV_PCM_RATE_48000)

#घोषणा AK4671_FORMATS		SNDRV_PCM_FMTBIT_S16_LE

अटल स्थिर काष्ठा snd_soc_dai_ops ak4671_dai_ops = अणु
	.hw_params	= ak4671_hw_params,
	.set_sysclk	= ak4671_set_dai_sysclk,
	.set_fmt	= ak4671_set_dai_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ak4671_dai = अणु
	.name = "ak4671-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = AK4671_RATES,
		.क्रमmats = AK4671_FORMATS,पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = AK4671_RATES,
		.क्रमmats = AK4671_FORMATS,पूर्ण,
	.ops = &ak4671_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_ak4671 = अणु
	.set_bias_level		= ak4671_set_bias_level,
	.controls		= ak4671_snd_controls,
	.num_controls		= ARRAY_SIZE(ak4671_snd_controls),
	.dapm_widमाला_लो		= ak4671_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ak4671_dapm_widमाला_लो),
	.dapm_routes		= ak4671_पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(ak4671_पूर्णांकercon),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ak4671_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = AK4671_SAR_ADC_CONTROL,
	.reg_शेषs = ak4671_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(ak4671_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक ak4671_i2c_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	regmap = devm_regmap_init_i2c(client, &ak4671_regmap);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		dev_err(&client->dev, "Failed to create regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&client->dev,
			&soc_component_dev_ak4671, &ak4671_dai, 1);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ak4671_i2c_id[] = अणु
	अणु "ak4671", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ak4671_i2c_id);

अटल काष्ठा i2c_driver ak4671_i2c_driver = अणु
	.driver = अणु
		.name = "ak4671-codec",
	पूर्ण,
	.probe = ak4671_i2c_probe,
	.id_table = ak4671_i2c_id,
पूर्ण;

module_i2c_driver(ak4671_i2c_driver);

MODULE_DESCRIPTION("ASoC AK4671 codec driver");
MODULE_AUTHOR("Joonyoung Shim <jy0922.shim@samsung.com>");
MODULE_LICENSE("GPL");
