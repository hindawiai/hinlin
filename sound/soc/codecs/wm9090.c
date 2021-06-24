<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ALSA SoC WM9090 driver
 *
 * Copyright 2009-12 Wolfson Microelectronics
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <sound/wm9090.h>

#समावेश "wm9090.h"

अटल स्थिर काष्ठा reg_शेष wm9090_reg_शेषs[] = अणु
	अणु 1,  0x0006 पूर्ण,     /* R1   - Power Management (1) */
	अणु 2,  0x6000 पूर्ण,     /* R2   - Power Management (2) */
	अणु 3,  0x0000 पूर्ण,     /* R3   - Power Management (3) */
	अणु 6,  0x01C0 पूर्ण,     /* R6   - Clocking 1 */
	अणु 22, 0x0003 पूर्ण,     /* R22  - IN1 Line Control */
	अणु 23, 0x0003 पूर्ण,     /* R23  - IN2 Line Control */
	अणु 24, 0x0083 पूर्ण,     /* R24  - IN1 Line Input A Volume */
	अणु 25, 0x0083 पूर्ण,     /* R25  - IN1  Line Input B Volume */
	अणु 26, 0x0083 पूर्ण,     /* R26  - IN2 Line Input A Volume */
	अणु 27, 0x0083 पूर्ण,     /* R27  - IN2 Line Input B Volume */
	अणु 28, 0x002D पूर्ण,     /* R28  - Left Output Volume */
	अणु 29, 0x002D पूर्ण,     /* R29  - Right Output Volume */
	अणु 34, 0x0100 पूर्ण,     /* R34  - SPKMIXL Attenuation */
	अणु 35, 0x0010 पूर्ण,     /* R36  - SPKOUT Mixers */
	अणु 37, 0x0140 पूर्ण,     /* R37  - ClassD3 */
	अणु 38, 0x0039 पूर्ण,     /* R38  - Speaker Volume Left */
	अणु 45, 0x0000 पूर्ण,     /* R45  - Output Mixer1 */
	अणु 46, 0x0000 पूर्ण,     /* R46  - Output Mixer2 */
	अणु 47, 0x0100 पूर्ण,     /* R47  - Output Mixer3 */
	अणु 48, 0x0100 पूर्ण,     /* R48  - Output Mixer4 */
	अणु 54, 0x0000 पूर्ण,     /* R54  - Speaker Mixer */
	अणु 57, 0x000D पूर्ण,     /* R57  - AntiPOP2 */
	अणु 70, 0x0000 पूर्ण,     /* R70  - Write Sequencer 0 */
	अणु 71, 0x0000 पूर्ण,     /* R71  - Write Sequencer 1 */
	अणु 72, 0x0000 पूर्ण,     /* R72  - Write Sequencer 2 */
	अणु 73, 0x0000 पूर्ण,     /* R73  - Write Sequencer 3 */
	अणु 74, 0x0000 पूर्ण,     /* R74  - Write Sequencer 4 */
	अणु 75, 0x0000 पूर्ण,     /* R75  - Write Sequencer 5 */
	अणु 76, 0x1F25 पूर्ण,     /* R76  - Charge Pump 1 */
	अणु 85, 0x054A पूर्ण,     /* R85  - DC Servo 1 */
	अणु 87, 0x0000 पूर्ण,     /* R87  - DC Servo 3 */
	अणु 96, 0x0100 पूर्ण,     /* R96  - Analogue HP 0 */
	अणु 98, 0x8640 पूर्ण,     /* R98  - AGC Control 0 */
	अणु 99, 0xC000 पूर्ण,     /* R99  - AGC Control 1 */
	अणु 100, 0x0200 पूर्ण,     /* R100 - AGC Control 2 */
पूर्ण;

/* This काष्ठा is used to save the context */
काष्ठा wm9090_priv अणु
	काष्ठा wm9090_platक्रमm_data pdata;
	काष्ठा regmap *regmap;
पूर्ण;

अटल bool wm9090_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM9090_SOFTWARE_RESET:
	हाल WM9090_DC_SERVO_0:
	हाल WM9090_DC_SERVO_READBACK_0:
	हाल WM9090_DC_SERVO_READBACK_1:
	हाल WM9090_DC_SERVO_READBACK_2:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool wm9090_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM9090_SOFTWARE_RESET:
	हाल WM9090_POWER_MANAGEMENT_1:
	हाल WM9090_POWER_MANAGEMENT_2:
	हाल WM9090_POWER_MANAGEMENT_3:
	हाल WM9090_CLOCKING_1:
	हाल WM9090_IN1_LINE_CONTROL:
	हाल WM9090_IN2_LINE_CONTROL:
	हाल WM9090_IN1_LINE_INPUT_A_VOLUME:
	हाल WM9090_IN1_LINE_INPUT_B_VOLUME:
	हाल WM9090_IN2_LINE_INPUT_A_VOLUME:
	हाल WM9090_IN2_LINE_INPUT_B_VOLUME:
	हाल WM9090_LEFT_OUTPUT_VOLUME:
	हाल WM9090_RIGHT_OUTPUT_VOLUME:
	हाल WM9090_SPKMIXL_ATTENUATION:
	हाल WM9090_SPKOUT_MIXERS:
	हाल WM9090_CLASSD3:
	हाल WM9090_SPEAKER_VOLUME_LEFT:
	हाल WM9090_OUTPUT_MIXER1:
	हाल WM9090_OUTPUT_MIXER2:
	हाल WM9090_OUTPUT_MIXER3:
	हाल WM9090_OUTPUT_MIXER4:
	हाल WM9090_SPEAKER_MIXER:
	हाल WM9090_ANTIPOP2:
	हाल WM9090_WRITE_SEQUENCER_0:
	हाल WM9090_WRITE_SEQUENCER_1:
	हाल WM9090_WRITE_SEQUENCER_2:
	हाल WM9090_WRITE_SEQUENCER_3:
	हाल WM9090_WRITE_SEQUENCER_4:
	हाल WM9090_WRITE_SEQUENCER_5:
	हाल WM9090_CHARGE_PUMP_1:
	हाल WM9090_DC_SERVO_0:
	हाल WM9090_DC_SERVO_1:
	हाल WM9090_DC_SERVO_3:
	हाल WM9090_DC_SERVO_READBACK_0:
	हाल WM9090_DC_SERVO_READBACK_1:
	हाल WM9090_DC_SERVO_READBACK_2:
	हाल WM9090_ANALOGUE_HP_0:
	हाल WM9090_AGC_CONTROL_0:
	हाल WM9090_AGC_CONTROL_1:
	हाल WM9090_AGC_CONTROL_2:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम रुको_क्रम_dc_servo(काष्ठा snd_soc_component *component)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक count = 0;

	dev_dbg(component->dev, "Waiting for DC servo...\n");
	करो अणु
		count++;
		msleep(1);
		reg = snd_soc_component_पढ़ो(component, WM9090_DC_SERVO_READBACK_0);
		dev_dbg(component->dev, "DC servo status: %x\n", reg);
	पूर्ण जबतक ((reg & WM9090_DCS_CAL_COMPLETE_MASK)
		 != WM9090_DCS_CAL_COMPLETE_MASK && count < 1000);

	अगर ((reg & WM9090_DCS_CAL_COMPLETE_MASK)
	    != WM9090_DCS_CAL_COMPLETE_MASK)
		dev_err(component->dev, "Timed out waiting for DC Servo\n");
पूर्ण

अटल स्थिर DECLARE_TLV_DB_RANGE(in_tlv,
	0, 0, TLV_DB_SCALE_ITEM(-600, 0, 0),
	1, 3, TLV_DB_SCALE_ITEM(-350, 350, 0),
	4, 6, TLV_DB_SCALE_ITEM(600, 600, 0)
);
अटल स्थिर DECLARE_TLV_DB_RANGE(mix_tlv,
	0, 2, TLV_DB_SCALE_ITEM(-1200, 300, 0),
	3, 3, TLV_DB_SCALE_ITEM(0, 0, 0)
);
अटल स्थिर DECLARE_TLV_DB_SCALE(out_tlv, -5700, 100, 0);
अटल स्थिर DECLARE_TLV_DB_RANGE(spkboost_tlv,
	0, 6, TLV_DB_SCALE_ITEM(0, 150, 0),
	7, 7, TLV_DB_SCALE_ITEM(1200, 0, 0)
);

अटल स्थिर काष्ठा snd_kcontrol_new wm9090_controls[] = अणु
SOC_SINGLE_TLV("IN1A Volume", WM9090_IN1_LINE_INPUT_A_VOLUME, 0, 6, 0,
	       in_tlv),
SOC_SINGLE("IN1A Switch", WM9090_IN1_LINE_INPUT_A_VOLUME, 7, 1, 1),
SOC_SINGLE("IN1A ZC Switch", WM9090_IN1_LINE_INPUT_A_VOLUME, 6, 1, 0),

SOC_SINGLE_TLV("IN2A Volume", WM9090_IN2_LINE_INPUT_A_VOLUME, 0, 6, 0,
	       in_tlv),
SOC_SINGLE("IN2A Switch", WM9090_IN2_LINE_INPUT_A_VOLUME, 7, 1, 1),
SOC_SINGLE("IN2A ZC Switch", WM9090_IN2_LINE_INPUT_A_VOLUME, 6, 1, 0),

SOC_SINGLE("MIXOUTL Switch", WM9090_OUTPUT_MIXER3, 8, 1, 1),
SOC_SINGLE_TLV("MIXOUTL IN1A Volume", WM9090_OUTPUT_MIXER3, 6, 3, 1,
	       mix_tlv),
SOC_SINGLE_TLV("MIXOUTL IN2A Volume", WM9090_OUTPUT_MIXER3, 2, 3, 1,
	       mix_tlv),

SOC_SINGLE("MIXOUTR Switch", WM9090_OUTPUT_MIXER4, 8, 1, 1),
SOC_SINGLE_TLV("MIXOUTR IN1A Volume", WM9090_OUTPUT_MIXER4, 6, 3, 1,
	       mix_tlv),
SOC_SINGLE_TLV("MIXOUTR IN2A Volume", WM9090_OUTPUT_MIXER4, 2, 3, 1,
	       mix_tlv),

SOC_SINGLE("SPKMIX Switch", WM9090_SPKMIXL_ATTENUATION, 8, 1, 1),
SOC_SINGLE_TLV("SPKMIX IN1A Volume", WM9090_SPKMIXL_ATTENUATION, 6, 3, 1,
	       mix_tlv),
SOC_SINGLE_TLV("SPKMIX IN2A Volume", WM9090_SPKMIXL_ATTENUATION, 2, 3, 1,
	       mix_tlv),

SOC_DOUBLE_R_TLV("Headphone Volume", WM9090_LEFT_OUTPUT_VOLUME,
		 WM9090_RIGHT_OUTPUT_VOLUME, 0, 63, 0, out_tlv),
SOC_DOUBLE_R("Headphone Switch", WM9090_LEFT_OUTPUT_VOLUME,
	     WM9090_RIGHT_OUTPUT_VOLUME, 6, 1, 1),
SOC_DOUBLE_R("Headphone ZC Switch", WM9090_LEFT_OUTPUT_VOLUME,
	     WM9090_RIGHT_OUTPUT_VOLUME, 7, 1, 0),

SOC_SINGLE_TLV("Speaker Volume", WM9090_SPEAKER_VOLUME_LEFT, 0, 63, 0,
	       out_tlv),
SOC_SINGLE("Speaker Switch", WM9090_SPEAKER_VOLUME_LEFT, 6, 1, 1),
SOC_SINGLE("Speaker ZC Switch", WM9090_SPEAKER_VOLUME_LEFT, 7, 1, 0),
SOC_SINGLE_TLV("Speaker Boost Volume", WM9090_CLASSD3, 3, 7, 0, spkboost_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm9090_in1_se_controls[] = अणु
SOC_SINGLE_TLV("IN1B Volume", WM9090_IN1_LINE_INPUT_B_VOLUME, 0, 6, 0,
	       in_tlv),
SOC_SINGLE("IN1B Switch", WM9090_IN1_LINE_INPUT_B_VOLUME, 7, 1, 1),
SOC_SINGLE("IN1B ZC Switch", WM9090_IN1_LINE_INPUT_B_VOLUME, 6, 1, 0),

SOC_SINGLE_TLV("SPKMIX IN1B Volume", WM9090_SPKMIXL_ATTENUATION, 4, 3, 1,
	       mix_tlv),
SOC_SINGLE_TLV("MIXOUTL IN1B Volume", WM9090_OUTPUT_MIXER3, 4, 3, 1,
	       mix_tlv),
SOC_SINGLE_TLV("MIXOUTR IN1B Volume", WM9090_OUTPUT_MIXER4, 4, 3, 1,
	       mix_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm9090_in2_se_controls[] = अणु
SOC_SINGLE_TLV("IN2B Volume", WM9090_IN2_LINE_INPUT_B_VOLUME, 0, 6, 0,
	       in_tlv),
SOC_SINGLE("IN2B Switch", WM9090_IN2_LINE_INPUT_B_VOLUME, 7, 1, 1),
SOC_SINGLE("IN2B ZC Switch", WM9090_IN2_LINE_INPUT_B_VOLUME, 6, 1, 0),

SOC_SINGLE_TLV("SPKMIX IN2B Volume", WM9090_SPKMIXL_ATTENUATION, 0, 3, 1,
	       mix_tlv),
SOC_SINGLE_TLV("MIXOUTL IN2B Volume", WM9090_OUTPUT_MIXER3, 0, 3, 1,
	       mix_tlv),
SOC_SINGLE_TLV("MIXOUTR IN2B Volume", WM9090_OUTPUT_MIXER4, 0, 3, 1,
	       mix_tlv),
पूर्ण;

अटल पूर्णांक hp_ev(काष्ठा snd_soc_dapm_widget *w,
		 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	अचिन्हित पूर्णांक reg = snd_soc_component_पढ़ो(component, WM9090_ANALOGUE_HP_0);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, WM9090_CHARGE_PUMP_1,
				    WM9090_CP_ENA, WM9090_CP_ENA);

		msleep(5);

		snd_soc_component_update_bits(component, WM9090_POWER_MANAGEMENT_1,
				    WM9090_HPOUT1L_ENA | WM9090_HPOUT1R_ENA,
				    WM9090_HPOUT1L_ENA | WM9090_HPOUT1R_ENA);

		reg |= WM9090_HPOUT1L_DLY | WM9090_HPOUT1R_DLY;
		snd_soc_component_ग_लिखो(component, WM9090_ANALOGUE_HP_0, reg);

		/* Start the DC servo.  We करोn't currently use the
		 * ability to save the state since we करोn't have full
		 * control of the analogue paths and they can change
		 * DC offsets; see the WM8904 driver क्रम an example of
		 * करोing so.
		 */
		snd_soc_component_ग_लिखो(component, WM9090_DC_SERVO_0,
			      WM9090_DCS_ENA_CHAN_0 |
			      WM9090_DCS_ENA_CHAN_1 |
			      WM9090_DCS_TRIG_STARTUP_1 |
			      WM9090_DCS_TRIG_STARTUP_0);
		रुको_क्रम_dc_servo(component);

		reg |= WM9090_HPOUT1R_OUTP | WM9090_HPOUT1R_RMV_SHORT |
			WM9090_HPOUT1L_OUTP | WM9090_HPOUT1L_RMV_SHORT;
		snd_soc_component_ग_लिखो(component, WM9090_ANALOGUE_HP_0, reg);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		reg &= ~(WM9090_HPOUT1L_RMV_SHORT |
			 WM9090_HPOUT1L_DLY |
			 WM9090_HPOUT1L_OUTP |
			 WM9090_HPOUT1R_RMV_SHORT |
			 WM9090_HPOUT1R_DLY |
			 WM9090_HPOUT1R_OUTP);

		snd_soc_component_ग_लिखो(component, WM9090_ANALOGUE_HP_0, reg);

		snd_soc_component_ग_लिखो(component, WM9090_DC_SERVO_0, 0);

		snd_soc_component_update_bits(component, WM9090_POWER_MANAGEMENT_1,
				    WM9090_HPOUT1L_ENA | WM9090_HPOUT1R_ENA,
				    0);

		snd_soc_component_update_bits(component, WM9090_CHARGE_PUMP_1,
				    WM9090_CP_ENA, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new spkmix[] = अणु
SOC_DAPM_SINGLE("IN1A Switch", WM9090_SPEAKER_MIXER, 6, 1, 0),
SOC_DAPM_SINGLE("IN1B Switch", WM9090_SPEAKER_MIXER, 4, 1, 0),
SOC_DAPM_SINGLE("IN2A Switch", WM9090_SPEAKER_MIXER, 2, 1, 0),
SOC_DAPM_SINGLE("IN2B Switch", WM9090_SPEAKER_MIXER, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new spkout[] = अणु
SOC_DAPM_SINGLE("Mixer Switch", WM9090_SPKOUT_MIXERS, 4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mixoutl[] = अणु
SOC_DAPM_SINGLE("IN1A Switch", WM9090_OUTPUT_MIXER1, 6, 1, 0),
SOC_DAPM_SINGLE("IN1B Switch", WM9090_OUTPUT_MIXER1, 4, 1, 0),
SOC_DAPM_SINGLE("IN2A Switch", WM9090_OUTPUT_MIXER1, 2, 1, 0),
SOC_DAPM_SINGLE("IN2B Switch", WM9090_OUTPUT_MIXER1, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mixoutr[] = अणु
SOC_DAPM_SINGLE("IN1A Switch", WM9090_OUTPUT_MIXER2, 6, 1, 0),
SOC_DAPM_SINGLE("IN1B Switch", WM9090_OUTPUT_MIXER2, 4, 1, 0),
SOC_DAPM_SINGLE("IN2A Switch", WM9090_OUTPUT_MIXER2, 2, 1, 0),
SOC_DAPM_SINGLE("IN2B Switch", WM9090_OUTPUT_MIXER2, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm9090_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("IN1+"),
SND_SOC_DAPM_INPUT("IN1-"),
SND_SOC_DAPM_INPUT("IN2+"),
SND_SOC_DAPM_INPUT("IN2-"),

SND_SOC_DAPM_SUPPLY("OSC", WM9090_POWER_MANAGEMENT_1, 3, 0, शून्य, 0),

SND_SOC_DAPM_PGA("IN1A PGA", WM9090_POWER_MANAGEMENT_2, 7, 0, शून्य, 0),
SND_SOC_DAPM_PGA("IN1B PGA", WM9090_POWER_MANAGEMENT_2, 6, 0, शून्य, 0),
SND_SOC_DAPM_PGA("IN2A PGA", WM9090_POWER_MANAGEMENT_2, 5, 0, शून्य, 0),
SND_SOC_DAPM_PGA("IN2B PGA", WM9090_POWER_MANAGEMENT_2, 4, 0, शून्य, 0),

SND_SOC_DAPM_MIXER("SPKMIX", WM9090_POWER_MANAGEMENT_3, 3, 0,
		   spkmix, ARRAY_SIZE(spkmix)),
SND_SOC_DAPM_MIXER("MIXOUTL", WM9090_POWER_MANAGEMENT_3, 5, 0,
		   mixoutl, ARRAY_SIZE(mixoutl)),
SND_SOC_DAPM_MIXER("MIXOUTR", WM9090_POWER_MANAGEMENT_3, 4, 0,
		   mixoutr, ARRAY_SIZE(mixoutr)),

SND_SOC_DAPM_PGA_E("HP PGA", SND_SOC_NOPM, 0, 0, शून्य, 0,
		   hp_ev, SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

SND_SOC_DAPM_PGA("SPKPGA", WM9090_POWER_MANAGEMENT_3, 8, 0, शून्य, 0),
SND_SOC_DAPM_MIXER("SPKOUT", WM9090_POWER_MANAGEMENT_1, 12, 0,
		   spkout, ARRAY_SIZE(spkout)),

SND_SOC_DAPM_OUTPUT("HPR"),
SND_SOC_DAPM_OUTPUT("HPL"),
SND_SOC_DAPM_OUTPUT("Speaker"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	अणु "IN1A PGA", शून्य, "IN1+" पूर्ण,
	अणु "IN2A PGA", शून्य, "IN2+" पूर्ण,

	अणु "SPKMIX", "IN1A Switch", "IN1A PGA" पूर्ण,
	अणु "SPKMIX", "IN2A Switch", "IN2A PGA" पूर्ण,

	अणु "MIXOUTL", "IN1A Switch", "IN1A PGA" पूर्ण,
	अणु "MIXOUTL", "IN2A Switch", "IN2A PGA" पूर्ण,

	अणु "MIXOUTR", "IN1A Switch", "IN1A PGA" पूर्ण,
	अणु "MIXOUTR", "IN2A Switch", "IN2A PGA" पूर्ण,

	अणु "HP PGA", शून्य, "OSC" पूर्ण,
	अणु "HP PGA", शून्य, "MIXOUTL" पूर्ण,
	अणु "HP PGA", शून्य, "MIXOUTR" पूर्ण,

	अणु "HPL", शून्य, "HP PGA" पूर्ण,
	अणु "HPR", शून्य, "HP PGA" पूर्ण,

	अणु "SPKPGA", शून्य, "OSC" पूर्ण,
	अणु "SPKPGA", शून्य, "SPKMIX" पूर्ण,

	अणु "SPKOUT", "Mixer Switch", "SPKPGA" पूर्ण,

	अणु "Speaker", शून्य, "SPKOUT" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map_in1_se[] = अणु
	अणु "IN1B PGA", शून्य, "IN1-" पूर्ण,	

	अणु "SPKMIX", "IN1B Switch", "IN1B PGA" पूर्ण,
	अणु "MIXOUTL", "IN1B Switch", "IN1B PGA" पूर्ण,
	अणु "MIXOUTR", "IN1B Switch", "IN1B PGA" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map_in1_dअगरf[] = अणु
	अणु "IN1A PGA", शून्य, "IN1-" पूर्ण,	
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map_in2_se[] = अणु
	अणु "IN2B PGA", शून्य, "IN2-" पूर्ण,	

	अणु "SPKMIX", "IN2B Switch", "IN2B PGA" पूर्ण,
	अणु "MIXOUTL", "IN2B Switch", "IN2B PGA" पूर्ण,
	अणु "MIXOUTR", "IN2B Switch", "IN2B PGA" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map_in2_dअगरf[] = अणु
	अणु "IN2A PGA", शून्य, "IN2-" पूर्ण,	
पूर्ण;

अटल पूर्णांक wm9090_add_controls(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm9090_priv *wm9090 = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	पूर्णांक i;

	snd_soc_dapm_new_controls(dapm, wm9090_dapm_widमाला_लो,
				  ARRAY_SIZE(wm9090_dapm_widमाला_लो));

	snd_soc_dapm_add_routes(dapm, audio_map, ARRAY_SIZE(audio_map));

	snd_soc_add_component_controls(component, wm9090_controls,
			     ARRAY_SIZE(wm9090_controls));

	अगर (wm9090->pdata.lin1_dअगरf) अणु
		snd_soc_dapm_add_routes(dapm, audio_map_in1_dअगरf,
					ARRAY_SIZE(audio_map_in1_dअगरf));
	पूर्ण अन्यथा अणु
		snd_soc_dapm_add_routes(dapm, audio_map_in1_se,
					ARRAY_SIZE(audio_map_in1_se));
		snd_soc_add_component_controls(component, wm9090_in1_se_controls,
				     ARRAY_SIZE(wm9090_in1_se_controls));
	पूर्ण

	अगर (wm9090->pdata.lin2_dअगरf) अणु
		snd_soc_dapm_add_routes(dapm, audio_map_in2_dअगरf,
					ARRAY_SIZE(audio_map_in2_dअगरf));
	पूर्ण अन्यथा अणु
		snd_soc_dapm_add_routes(dapm, audio_map_in2_se,
					ARRAY_SIZE(audio_map_in2_se));
		snd_soc_add_component_controls(component, wm9090_in2_se_controls,
				     ARRAY_SIZE(wm9090_in2_se_controls));
	पूर्ण

	अगर (wm9090->pdata.agc_ena) अणु
		क्रम (i = 0; i < ARRAY_SIZE(wm9090->pdata.agc); i++)
			snd_soc_component_ग_लिखो(component, WM9090_AGC_CONTROL_0 + i,
				      wm9090->pdata.agc[i]);
		snd_soc_component_update_bits(component, WM9090_POWER_MANAGEMENT_3,
				    WM9090_AGC_ENA, WM9090_AGC_ENA);
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component, WM9090_POWER_MANAGEMENT_3,
				    WM9090_AGC_ENA, 0);
	पूर्ण

	वापस 0;

पूर्ण

/*
 * The machine driver should call this from their set_bias_level; अगर there
 * isn't one then this can just be set as the set_bias_level function.
 */
अटल पूर्णांक wm9090_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm9090_priv *wm9090 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		snd_soc_component_update_bits(component, WM9090_ANTIPOP2, WM9090_VMID_ENA,
				    WM9090_VMID_ENA);
		snd_soc_component_update_bits(component, WM9090_POWER_MANAGEMENT_1,
				    WM9090_BIAS_ENA |
				    WM9090_VMID_RES_MASK,
				    WM9090_BIAS_ENA |
				    1 << WM9090_VMID_RES_SHIFT);
		msleep(1);  /* Probably an overestimate */
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			/* Restore the रेजिस्टर cache */
			regcache_sync(wm9090->regmap);
		पूर्ण

		/* We keep VMID off during standby since the combination of
		 * ground referenced outमाला_दो and class D speaker mean that
		 * latency is not an issue.
		 */
		snd_soc_component_update_bits(component, WM9090_POWER_MANAGEMENT_1,
				    WM9090_BIAS_ENA | WM9090_VMID_RES_MASK, 0);
		snd_soc_component_update_bits(component, WM9090_ANTIPOP2,
				    WM9090_VMID_ENA, 0);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm9090_probe(काष्ठा snd_soc_component *component)
अणु
	/* Configure some शेषs; they will be written out when we
	 * bring the bias up.
	 */
	snd_soc_component_update_bits(component, WM9090_IN1_LINE_INPUT_A_VOLUME,
			    WM9090_IN1_VU | WM9090_IN1A_ZC,
			    WM9090_IN1_VU | WM9090_IN1A_ZC);
	snd_soc_component_update_bits(component, WM9090_IN1_LINE_INPUT_B_VOLUME,
			    WM9090_IN1_VU | WM9090_IN1B_ZC,
			    WM9090_IN1_VU | WM9090_IN1B_ZC);
	snd_soc_component_update_bits(component, WM9090_IN2_LINE_INPUT_A_VOLUME,
			    WM9090_IN2_VU | WM9090_IN2A_ZC,
			    WM9090_IN2_VU | WM9090_IN2A_ZC);
	snd_soc_component_update_bits(component, WM9090_IN2_LINE_INPUT_B_VOLUME,
			    WM9090_IN2_VU | WM9090_IN2B_ZC,
			    WM9090_IN2_VU | WM9090_IN2B_ZC);
	snd_soc_component_update_bits(component, WM9090_SPEAKER_VOLUME_LEFT,
			    WM9090_SPKOUT_VU | WM9090_SPKOUTL_ZC,
			    WM9090_SPKOUT_VU | WM9090_SPKOUTL_ZC);
	snd_soc_component_update_bits(component, WM9090_LEFT_OUTPUT_VOLUME,
			    WM9090_HPOUT1_VU | WM9090_HPOUT1L_ZC,
			    WM9090_HPOUT1_VU | WM9090_HPOUT1L_ZC);
	snd_soc_component_update_bits(component, WM9090_RIGHT_OUTPUT_VOLUME,
			    WM9090_HPOUT1_VU | WM9090_HPOUT1R_ZC,
			    WM9090_HPOUT1_VU | WM9090_HPOUT1R_ZC);

	snd_soc_component_update_bits(component, WM9090_CLOCKING_1,
			    WM9090_TOCLK_ENA, WM9090_TOCLK_ENA);

	wm9090_add_controls(component);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm9090 = अणु
	.probe			= wm9090_probe,
	.set_bias_level		= wm9090_set_bias_level,
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm9090_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,

	.max_रेजिस्टर = WM9090_MAX_REGISTER,
	.अस्थिर_reg = wm9090_अस्थिर,
	.पढ़ोable_reg = wm9090_पढ़ोable,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = wm9090_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm9090_reg_शेषs),
पूर्ण;


अटल पूर्णांक wm9090_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm9090_priv *wm9090;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	wm9090 = devm_kzalloc(&i2c->dev, माप(*wm9090), GFP_KERNEL);
	अगर (!wm9090)
		वापस -ENOMEM;

	wm9090->regmap = devm_regmap_init_i2c(i2c, &wm9090_regmap);
	अगर (IS_ERR(wm9090->regmap)) अणु
		ret = PTR_ERR(wm9090->regmap);
		dev_err(&i2c->dev, "Failed to allocate regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(wm9090->regmap, WM9090_SOFTWARE_RESET, &reg);
	अगर (ret < 0)
		वापस ret;

	अगर (reg != 0x9093) अणु
		dev_err(&i2c->dev, "Device is not a WM9090, ID=%x\n", reg);
		वापस -ENODEV;
	पूर्ण

	ret = regmap_ग_लिखो(wm9090->regmap, WM9090_SOFTWARE_RESET, 0);
	अगर (ret < 0)
		वापस ret;

	अगर (i2c->dev.platक्रमm_data)
		स_नकल(&wm9090->pdata, i2c->dev.platक्रमm_data,
		       माप(wm9090->pdata));

	i2c_set_clientdata(i2c, wm9090);

	ret =  devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_wm9090,  शून्य, 0);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to register CODEC: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm9090_id[] = अणु
	अणु "wm9090", 0 पूर्ण,
	अणु "wm9093", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm9090_id);

अटल काष्ठा i2c_driver wm9090_i2c_driver = अणु
	.driver = अणु
		.name = "wm9090",
	पूर्ण,
	.probe = wm9090_i2c_probe,
	.id_table = wm9090_id,
पूर्ण;

module_i2c_driver(wm9090_i2c_driver);

MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("WM9090 ASoC driver");
MODULE_LICENSE("GPL");
