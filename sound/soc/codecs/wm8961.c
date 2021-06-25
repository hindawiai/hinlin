<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8961.c  --  WM8961 ALSA SoC Audio driver
 *
 * Copyright 2009-10 Wolfson Microelectronics, plc
 *
 * Author: Mark Brown
 *
 * Currently unimplemented features:
 *  - ALC
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
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

#समावेश "wm8961.h"

#घोषणा WM8961_MAX_REGISTER                     0xFC

अटल स्थिर काष्ठा reg_शेष wm8961_reg_शेषs[] = अणु
	अणु  0, 0x009F पूर्ण,     /* R0   - Left Input volume */
	अणु  1, 0x009F पूर्ण,     /* R1   - Right Input volume */
	अणु  2, 0x0000 पूर्ण,     /* R2   - LOUT1 volume */
	अणु  3, 0x0000 पूर्ण,     /* R3   - ROUT1 volume */
	अणु  4, 0x0020 पूर्ण,     /* R4   - Clocking1 */
	अणु  5, 0x0008 पूर्ण,     /* R5   - ADC & DAC Control 1 */
	अणु  6, 0x0000 पूर्ण,     /* R6   - ADC & DAC Control 2 */
	अणु  7, 0x000A पूर्ण,     /* R7   - Audio Interface 0 */
	अणु  8, 0x01F4 पूर्ण,     /* R8   - Clocking2 */
	अणु  9, 0x0000 पूर्ण,     /* R9   - Audio Interface 1 */
	अणु 10, 0x00FF पूर्ण,     /* R10  - Left DAC volume */
	अणु 11, 0x00FF पूर्ण,     /* R11  - Right DAC volume */

	अणु 14, 0x0040 पूर्ण,     /* R14  - Audio Interface 2 */

	अणु 17, 0x007B पूर्ण,     /* R17  - ALC1 */
	अणु 18, 0x0000 पूर्ण,     /* R18  - ALC2 */
	अणु 19, 0x0032 पूर्ण,     /* R19  - ALC3 */
	अणु 20, 0x0000 पूर्ण,     /* R20  - Noise Gate */
	अणु 21, 0x00C0 पूर्ण,     /* R21  - Left ADC volume */
	अणु 22, 0x00C0 पूर्ण,     /* R22  - Right ADC volume */
	अणु 23, 0x0120 पूर्ण,     /* R23  - Additional control(1) */
	अणु 24, 0x0000 पूर्ण,     /* R24  - Additional control(2) */
	अणु 25, 0x0000 पूर्ण,     /* R25  - Pwr Mgmt (1) */
	अणु 26, 0x0000 पूर्ण,     /* R26  - Pwr Mgmt (2) */
	अणु 27, 0x0000 पूर्ण,     /* R27  - Additional Control (3) */
	अणु 28, 0x0000 पूर्ण,     /* R28  - Anti-pop */

	अणु 30, 0x005F पूर्ण,     /* R30  - Clocking 3 */

	अणु 32, 0x0000 पूर्ण,     /* R32  - ADCL संकेत path */
	अणु 33, 0x0000 पूर्ण,     /* R33  - ADCR संकेत path */

	अणु 40, 0x0000 पूर्ण,     /* R40  - LOUT2 volume */
	अणु 41, 0x0000 पूर्ण,     /* R41  - ROUT2 volume */

	अणु 47, 0x0000 पूर्ण,     /* R47  - Pwr Mgmt (3) */
	अणु 48, 0x0023 पूर्ण,     /* R48  - Additional Control (4) */
	अणु 49, 0x0000 पूर्ण,     /* R49  - Class D Control 1 */

	अणु 51, 0x0003 पूर्ण,     /* R51  - Class D Control 2 */

	अणु 56, 0x0106 पूर्ण,     /* R56  - Clocking 4 */
	अणु 57, 0x0000 पूर्ण,     /* R57  - DSP Sidetone 0 */
	अणु 58, 0x0000 पूर्ण,     /* R58  - DSP Sidetone 1 */

	अणु 60, 0x0000 पूर्ण,     /* R60  - DC Servo 0 */
	अणु 61, 0x0000 पूर्ण,     /* R61  - DC Servo 1 */

	अणु 63, 0x015E पूर्ण,     /* R63  - DC Servo 3 */

	अणु 65, 0x0010 पूर्ण,     /* R65  - DC Servo 5 */

	अणु 68, 0x0003 पूर्ण,     /* R68  - Analogue PGA Bias */
	अणु 69, 0x0000 पूर्ण,     /* R69  - Analogue HP 0 */

	अणु 71, 0x01FB पूर्ण,     /* R71  - Analogue HP 2 */
	अणु 72, 0x0000 पूर्ण,     /* R72  - Charge Pump 1 */

	अणु 82, 0x0000 पूर्ण,     /* R82  - Charge Pump B */

	अणु 87, 0x0000 पूर्ण,     /* R87  - Write Sequencer 1 */
	अणु 88, 0x0000 पूर्ण,     /* R88  - Write Sequencer 2 */
	अणु 89, 0x0000 पूर्ण,     /* R89  - Write Sequencer 3 */
	अणु 90, 0x0000 पूर्ण,     /* R90  - Write Sequencer 4 */
	अणु 91, 0x0000 पूर्ण,     /* R91  - Write Sequencer 5 */
	अणु 92, 0x0000 पूर्ण,     /* R92  - Write Sequencer 6 */
	अणु 93, 0x0000 पूर्ण,     /* R93  - Write Sequencer 7 */

	अणु 252, 0x0001 पूर्ण,     /* R252 - General test 1 */
पूर्ण;

काष्ठा wm8961_priv अणु
	काष्ठा regmap *regmap;
	पूर्णांक sysclk;
पूर्ण;

अटल bool wm8961_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8961_SOFTWARE_RESET:
	हाल WM8961_WRITE_SEQUENCER_7:
	हाल WM8961_DC_SERVO_1:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool wm8961_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8961_LEFT_INPUT_VOLUME:
	हाल WM8961_RIGHT_INPUT_VOLUME:
	हाल WM8961_LOUT1_VOLUME:
	हाल WM8961_ROUT1_VOLUME:
	हाल WM8961_CLOCKING1:
	हाल WM8961_ADC_DAC_CONTROL_1:
	हाल WM8961_ADC_DAC_CONTROL_2:
	हाल WM8961_AUDIO_INTERFACE_0:
	हाल WM8961_CLOCKING2:
	हाल WM8961_AUDIO_INTERFACE_1:
	हाल WM8961_LEFT_DAC_VOLUME:
	हाल WM8961_RIGHT_DAC_VOLUME:
	हाल WM8961_AUDIO_INTERFACE_2:
	हाल WM8961_SOFTWARE_RESET:
	हाल WM8961_ALC1:
	हाल WM8961_ALC2:
	हाल WM8961_ALC3:
	हाल WM8961_NOISE_GATE:
	हाल WM8961_LEFT_ADC_VOLUME:
	हाल WM8961_RIGHT_ADC_VOLUME:
	हाल WM8961_ADDITIONAL_CONTROL_1:
	हाल WM8961_ADDITIONAL_CONTROL_2:
	हाल WM8961_PWR_MGMT_1:
	हाल WM8961_PWR_MGMT_2:
	हाल WM8961_ADDITIONAL_CONTROL_3:
	हाल WM8961_ANTI_POP:
	हाल WM8961_CLOCKING_3:
	हाल WM8961_ADCL_SIGNAL_PATH:
	हाल WM8961_ADCR_SIGNAL_PATH:
	हाल WM8961_LOUT2_VOLUME:
	हाल WM8961_ROUT2_VOLUME:
	हाल WM8961_PWR_MGMT_3:
	हाल WM8961_ADDITIONAL_CONTROL_4:
	हाल WM8961_CLASS_D_CONTROL_1:
	हाल WM8961_CLASS_D_CONTROL_2:
	हाल WM8961_CLOCKING_4:
	हाल WM8961_DSP_SIDETONE_0:
	हाल WM8961_DSP_SIDETONE_1:
	हाल WM8961_DC_SERVO_0:
	हाल WM8961_DC_SERVO_1:
	हाल WM8961_DC_SERVO_3:
	हाल WM8961_DC_SERVO_5:
	हाल WM8961_ANALOGUE_PGA_BIAS:
	हाल WM8961_ANALOGUE_HP_0:
	हाल WM8961_ANALOGUE_HP_2:
	हाल WM8961_CHARGE_PUMP_1:
	हाल WM8961_CHARGE_PUMP_B:
	हाल WM8961_WRITE_SEQUENCER_1:
	हाल WM8961_WRITE_SEQUENCER_2:
	हाल WM8961_WRITE_SEQUENCER_3:
	हाल WM8961_WRITE_SEQUENCER_4:
	हाल WM8961_WRITE_SEQUENCER_5:
	हाल WM8961_WRITE_SEQUENCER_6:
	हाल WM8961_WRITE_SEQUENCER_7:
	हाल WM8961_GENERAL_TEST_1:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * The headphone output supports special anti-pop sequences giving
 * silent घातer up and घातer करोwn.
 */
अटल पूर्णांक wm8961_hp_event(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u16 hp_reg = snd_soc_component_पढ़ो(component, WM8961_ANALOGUE_HP_0);
	u16 cp_reg = snd_soc_component_पढ़ो(component, WM8961_CHARGE_PUMP_1);
	u16 pwr_reg = snd_soc_component_पढ़ो(component, WM8961_PWR_MGMT_2);
	u16 dcs_reg = snd_soc_component_पढ़ो(component, WM8961_DC_SERVO_1);
	पूर्णांक समयout = 500;

	अगर (event & SND_SOC_DAPM_POST_PMU) अणु
		/* Make sure the output is लघुed */
		hp_reg &= ~(WM8961_HPR_RMV_SHORT | WM8961_HPL_RMV_SHORT);
		snd_soc_component_ग_लिखो(component, WM8961_ANALOGUE_HP_0, hp_reg);

		/* Enable the अक्षरge pump */
		cp_reg |= WM8961_CP_ENA;
		snd_soc_component_ग_लिखो(component, WM8961_CHARGE_PUMP_1, cp_reg);
		mdelay(5);

		/* Enable the PGA */
		pwr_reg |= WM8961_LOUT1_PGA | WM8961_ROUT1_PGA;
		snd_soc_component_ग_लिखो(component, WM8961_PWR_MGMT_2, pwr_reg);

		/* Enable the amplअगरier */
		hp_reg |= WM8961_HPR_ENA | WM8961_HPL_ENA;
		snd_soc_component_ग_लिखो(component, WM8961_ANALOGUE_HP_0, hp_reg);

		/* Second stage enable */
		hp_reg |= WM8961_HPR_ENA_DLY | WM8961_HPL_ENA_DLY;
		snd_soc_component_ग_लिखो(component, WM8961_ANALOGUE_HP_0, hp_reg);

		/* Enable the DC servo & trigger startup */
		dcs_reg |=
			WM8961_DCS_ENA_CHAN_HPR | WM8961_DCS_TRIG_STARTUP_HPR |
			WM8961_DCS_ENA_CHAN_HPL | WM8961_DCS_TRIG_STARTUP_HPL;
		dev_dbg(component->dev, "Enabling DC servo\n");

		snd_soc_component_ग_लिखो(component, WM8961_DC_SERVO_1, dcs_reg);
		करो अणु
			msleep(1);
			dcs_reg = snd_soc_component_पढ़ो(component, WM8961_DC_SERVO_1);
		पूर्ण जबतक (--समयout &&
			 dcs_reg & (WM8961_DCS_TRIG_STARTUP_HPR |
				WM8961_DCS_TRIG_STARTUP_HPL));
		अगर (dcs_reg & (WM8961_DCS_TRIG_STARTUP_HPR |
			       WM8961_DCS_TRIG_STARTUP_HPL))
			dev_err(component->dev, "DC servo timed out\n");
		अन्यथा
			dev_dbg(component->dev, "DC servo startup complete\n");

		/* Enable the output stage */
		hp_reg |= WM8961_HPR_ENA_OUTP | WM8961_HPL_ENA_OUTP;
		snd_soc_component_ग_लिखो(component, WM8961_ANALOGUE_HP_0, hp_reg);

		/* Remove the लघु on the output stage */
		hp_reg |= WM8961_HPR_RMV_SHORT | WM8961_HPL_RMV_SHORT;
		snd_soc_component_ग_लिखो(component, WM8961_ANALOGUE_HP_0, hp_reg);
	पूर्ण

	अगर (event & SND_SOC_DAPM_PRE_PMD) अणु
		/* Short the output */
		hp_reg &= ~(WM8961_HPR_RMV_SHORT | WM8961_HPL_RMV_SHORT);
		snd_soc_component_ग_लिखो(component, WM8961_ANALOGUE_HP_0, hp_reg);

		/* Disable the output stage */
		hp_reg &= ~(WM8961_HPR_ENA_OUTP | WM8961_HPL_ENA_OUTP);
		snd_soc_component_ग_लिखो(component, WM8961_ANALOGUE_HP_0, hp_reg);

		/* Disable DC offset cancellation */
		dcs_reg &= ~(WM8961_DCS_ENA_CHAN_HPR |
			     WM8961_DCS_ENA_CHAN_HPL);
		snd_soc_component_ग_लिखो(component, WM8961_DC_SERVO_1, dcs_reg);

		/* Finish up */
		hp_reg &= ~(WM8961_HPR_ENA_DLY | WM8961_HPR_ENA |
			    WM8961_HPL_ENA_DLY | WM8961_HPL_ENA);
		snd_soc_component_ग_लिखो(component, WM8961_ANALOGUE_HP_0, hp_reg);

		/* Disable the PGA */
		pwr_reg &= ~(WM8961_LOUT1_PGA | WM8961_ROUT1_PGA);
		snd_soc_component_ग_लिखो(component, WM8961_PWR_MGMT_2, pwr_reg);

		/* Disable the अक्षरge pump */
		dev_dbg(component->dev, "Disabling charge pump\n");
		snd_soc_component_ग_लिखो(component, WM8961_CHARGE_PUMP_1,
			     cp_reg & ~WM8961_CP_ENA);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8961_spk_event(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u16 pwr_reg = snd_soc_component_पढ़ो(component, WM8961_PWR_MGMT_2);
	u16 spk_reg = snd_soc_component_पढ़ो(component, WM8961_CLASS_D_CONTROL_1);

	अगर (event & SND_SOC_DAPM_POST_PMU) अणु
		/* Enable the PGA */
		pwr_reg |= WM8961_SPKL_PGA | WM8961_SPKR_PGA;
		snd_soc_component_ग_लिखो(component, WM8961_PWR_MGMT_2, pwr_reg);

		/* Enable the amplअगरier */
		spk_reg |= WM8961_SPKL_ENA | WM8961_SPKR_ENA;
		snd_soc_component_ग_लिखो(component, WM8961_CLASS_D_CONTROL_1, spk_reg);
	पूर्ण

	अगर (event & SND_SOC_DAPM_PRE_PMD) अणु
		/* Disable the amplअगरier */
		spk_reg &= ~(WM8961_SPKL_ENA | WM8961_SPKR_ENA);
		snd_soc_component_ग_लिखो(component, WM8961_CLASS_D_CONTROL_1, spk_reg);

		/* Disable the PGA */
		pwr_reg &= ~(WM8961_SPKL_PGA | WM8961_SPKR_PGA);
		snd_soc_component_ग_लिखो(component, WM8961_PWR_MGMT_2, pwr_reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *adc_hpf_text[] = अणु
	"Hi-fi", "Voice 1", "Voice 2", "Voice 3",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adc_hpf,
			    WM8961_ADC_DAC_CONTROL_2, 7, adc_hpf_text);

अटल स्थिर अक्षर *dac_deemph_text[] = अणु
	"None", "32kHz", "44.1kHz", "48kHz",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(dac_deemph,
			    WM8961_ADC_DAC_CONTROL_1, 1, dac_deemph_text);

अटल स्थिर DECLARE_TLV_DB_SCALE(out_tlv, -12100, 100, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(hp_sec_tlv, -700, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_tlv, -7200, 75, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(sidetone_tlv, -3600, 300, 0);
अटल स्थिर DECLARE_TLV_DB_RANGE(boost_tlv,
	0, 0, TLV_DB_SCALE_ITEM(0,  0, 0),
	1, 1, TLV_DB_SCALE_ITEM(13, 0, 0),
	2, 2, TLV_DB_SCALE_ITEM(20, 0, 0),
	3, 3, TLV_DB_SCALE_ITEM(29, 0, 0)
);
अटल स्थिर DECLARE_TLV_DB_SCALE(pga_tlv, -2325, 75, 0);

अटल स्थिर काष्ठा snd_kcontrol_new wm8961_snd_controls[] = अणु
SOC_DOUBLE_R_TLV("Headphone Volume", WM8961_LOUT1_VOLUME, WM8961_ROUT1_VOLUME,
		 0, 127, 0, out_tlv),
SOC_DOUBLE_TLV("Headphone Secondary Volume", WM8961_ANALOGUE_HP_2,
	       6, 3, 7, 0, hp_sec_tlv),
SOC_DOUBLE_R("Headphone ZC Switch", WM8961_LOUT1_VOLUME, WM8961_ROUT1_VOLUME,
	     7, 1, 0),

SOC_DOUBLE_R_TLV("Speaker Volume", WM8961_LOUT2_VOLUME, WM8961_ROUT2_VOLUME,
		 0, 127, 0, out_tlv),
SOC_DOUBLE_R("Speaker ZC Switch", WM8961_LOUT2_VOLUME, WM8961_ROUT2_VOLUME,
	   7, 1, 0),
SOC_SINGLE("Speaker AC Gain", WM8961_CLASS_D_CONTROL_2, 0, 7, 0),

SOC_SINGLE("DAC x128 OSR Switch", WM8961_ADC_DAC_CONTROL_2, 0, 1, 0),
SOC_ENUM("DAC Deemphasis", dac_deemph),
SOC_SINGLE("DAC Soft Mute Switch", WM8961_ADC_DAC_CONTROL_2, 3, 1, 0),

SOC_DOUBLE_R_TLV("Sidetone Volume", WM8961_DSP_SIDETONE_0,
		 WM8961_DSP_SIDETONE_1, 4, 12, 0, sidetone_tlv),

SOC_SINGLE("ADC High Pass Filter Switch", WM8961_ADC_DAC_CONTROL_1, 0, 1, 0),
SOC_ENUM("ADC High Pass Filter Mode", adc_hpf),

SOC_DOUBLE_R_TLV("Capture Volume",
		 WM8961_LEFT_ADC_VOLUME, WM8961_RIGHT_ADC_VOLUME,
		 1, 119, 0, adc_tlv),
SOC_DOUBLE_R_TLV("Capture Boost Volume",
		 WM8961_ADCL_SIGNAL_PATH, WM8961_ADCR_SIGNAL_PATH,
		 4, 3, 0, boost_tlv),
SOC_DOUBLE_R_TLV("Capture PGA Volume",
		 WM8961_LEFT_INPUT_VOLUME, WM8961_RIGHT_INPUT_VOLUME,
		 0, 62, 0, pga_tlv),
SOC_DOUBLE_R("Capture PGA ZC Switch",
	     WM8961_LEFT_INPUT_VOLUME, WM8961_RIGHT_INPUT_VOLUME,
	     6, 1, 1),
SOC_DOUBLE_R("Capture PGA Switch",
	     WM8961_LEFT_INPUT_VOLUME, WM8961_RIGHT_INPUT_VOLUME,
	     7, 1, 1),
पूर्ण;

अटल स्थिर अक्षर *sidetone_text[] = अणु
	"None", "Left", "Right"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(dacl_sidetone,
			    WM8961_DSP_SIDETONE_0, 2, sidetone_text);

अटल SOC_ENUM_SINGLE_DECL(dacr_sidetone,
			    WM8961_DSP_SIDETONE_1, 2, sidetone_text);

अटल स्थिर काष्ठा snd_kcontrol_new dacl_mux =
	SOC_DAPM_ENUM("DACL Sidetone", dacl_sidetone);

अटल स्थिर काष्ठा snd_kcontrol_new dacr_mux =
	SOC_DAPM_ENUM("DACR Sidetone", dacr_sidetone);

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8961_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("LINPUT"),
SND_SOC_DAPM_INPUT("RINPUT"),

SND_SOC_DAPM_SUPPLY("CLK_DSP", WM8961_CLOCKING2, 4, 0, शून्य, 0),

SND_SOC_DAPM_PGA("Left Input", WM8961_PWR_MGMT_1, 5, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Right Input", WM8961_PWR_MGMT_1, 4, 0, शून्य, 0),

SND_SOC_DAPM_ADC("ADCL", "HiFi Capture", WM8961_PWR_MGMT_1, 3, 0),
SND_SOC_DAPM_ADC("ADCR", "HiFi Capture", WM8961_PWR_MGMT_1, 2, 0),

SND_SOC_DAPM_SUPPLY("MICBIAS", WM8961_PWR_MGMT_1, 1, 0, शून्य, 0),

SND_SOC_DAPM_MUX("DACL Sidetone", SND_SOC_NOPM, 0, 0, &dacl_mux),
SND_SOC_DAPM_MUX("DACR Sidetone", SND_SOC_NOPM, 0, 0, &dacr_mux),

SND_SOC_DAPM_DAC("DACL", "HiFi Playback", WM8961_PWR_MGMT_2, 8, 0),
SND_SOC_DAPM_DAC("DACR", "HiFi Playback", WM8961_PWR_MGMT_2, 7, 0),

/* Handle as a mono path क्रम DCS */
SND_SOC_DAPM_PGA_E("Headphone Output", SND_SOC_NOPM,
		   4, 0, शून्य, 0, wm8961_hp_event,
		   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
SND_SOC_DAPM_PGA_E("Speaker Output", SND_SOC_NOPM,
		   4, 0, शून्य, 0, wm8961_spk_event,
		   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

SND_SOC_DAPM_OUTPUT("HP_L"),
SND_SOC_DAPM_OUTPUT("HP_R"),
SND_SOC_DAPM_OUTPUT("SPK_LN"),
SND_SOC_DAPM_OUTPUT("SPK_LP"),
SND_SOC_DAPM_OUTPUT("SPK_RN"),
SND_SOC_DAPM_OUTPUT("SPK_RP"),
पूर्ण;


अटल स्थिर काष्ठा snd_soc_dapm_route audio_paths[] = अणु
	अणु "DACL", शून्य, "CLK_DSP" पूर्ण,
	अणु "DACL", शून्य, "DACL Sidetone" पूर्ण,
	अणु "DACR", शून्य, "CLK_DSP" पूर्ण,
	अणु "DACR", शून्य, "DACR Sidetone" पूर्ण,

	अणु "DACL Sidetone", "Left", "ADCL" पूर्ण,
	अणु "DACL Sidetone", "Right", "ADCR" पूर्ण,

	अणु "DACR Sidetone", "Left", "ADCL" पूर्ण,
	अणु "DACR Sidetone", "Right", "ADCR" पूर्ण,

	अणु "HP_L", शून्य, "Headphone Output" पूर्ण,
	अणु "HP_R", शून्य, "Headphone Output" पूर्ण,
	अणु "Headphone Output", शून्य, "DACL" पूर्ण,
	अणु "Headphone Output", शून्य, "DACR" पूर्ण,

	अणु "SPK_LN", शून्य, "Speaker Output" पूर्ण,
	अणु "SPK_LP", शून्य, "Speaker Output" पूर्ण,
	अणु "SPK_RN", शून्य, "Speaker Output" पूर्ण,
	अणु "SPK_RP", शून्य, "Speaker Output" पूर्ण,

	अणु "Speaker Output", शून्य, "DACL" पूर्ण,
	अणु "Speaker Output", शून्य, "DACR" पूर्ण,

	अणु "ADCL", शून्य, "Left Input" पूर्ण,
	अणु "ADCL", शून्य, "CLK_DSP" पूर्ण,
	अणु "ADCR", शून्य, "Right Input" पूर्ण,
	अणु "ADCR", शून्य, "CLK_DSP" पूर्ण,

	अणु "Left Input", शून्य, "LINPUT" पूर्ण,
	अणु "Right Input", शून्य, "RINPUT" पूर्ण,

पूर्ण;

/* Values क्रम CLK_SYS_RATE */
अटल काष्ठा अणु
	पूर्णांक ratio;
	u16 val;
पूर्ण wm8961_clk_sys_ratio[] = अणु
	अणु  64,  0 पूर्ण,
	अणु  128, 1 पूर्ण,
	अणु  192, 2 पूर्ण,
	अणु  256, 3 पूर्ण,
	अणु  384, 4 पूर्ण,
	अणु  512, 5 पूर्ण,
	अणु  768, 6 पूर्ण,
	अणु 1024, 7 पूर्ण,
	अणु 1408, 8 पूर्ण,
	अणु 1536, 9 पूर्ण,
पूर्ण;

/* Values क्रम SAMPLE_RATE */
अटल काष्ठा अणु
	पूर्णांक rate;
	u16 val;
पूर्ण wm8961_srate[] = अणु
	अणु 48000, 0 पूर्ण,
	अणु 44100, 0 पूर्ण,
	अणु 32000, 1 पूर्ण,
	अणु 22050, 2 पूर्ण,
	अणु 24000, 2 पूर्ण,
	अणु 16000, 3 पूर्ण,
	अणु 11250, 4 पूर्ण,
	अणु 12000, 4 पूर्ण,
	अणु  8000, 5 पूर्ण,
पूर्ण;

अटल पूर्णांक wm8961_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8961_priv *wm8961 = snd_soc_component_get_drvdata(component);
	पूर्णांक i, best, target, fs;
	u16 reg;

	fs = params_rate(params);

	अगर (!wm8961->sysclk) अणु
		dev_err(component->dev, "MCLK has not been specified\n");
		वापस -EINVAL;
	पूर्ण

	/* Find the बंदst sample rate क्रम the filters */
	best = 0;
	क्रम (i = 0; i < ARRAY_SIZE(wm8961_srate); i++) अणु
		अगर (असल(wm8961_srate[i].rate - fs) <
		    असल(wm8961_srate[best].rate - fs))
			best = i;
	पूर्ण
	reg = snd_soc_component_पढ़ो(component, WM8961_ADDITIONAL_CONTROL_3);
	reg &= ~WM8961_SAMPLE_RATE_MASK;
	reg |= wm8961_srate[best].val;
	snd_soc_component_ग_लिखो(component, WM8961_ADDITIONAL_CONTROL_3, reg);
	dev_dbg(component->dev, "Selected SRATE %dHz for %dHz\n",
		wm8961_srate[best].rate, fs);

	/* Select a CLK_SYS/fs ratio equal to or higher than required */
	target = wm8961->sysclk / fs;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK && target < 64) अणु
		dev_err(component->dev,
			"SYSCLK must be at least 64*fs for DAC\n");
		वापस -EINVAL;
	पूर्ण
	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE && target < 256) अणु
		dev_err(component->dev,
			"SYSCLK must be at least 256*fs for ADC\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(wm8961_clk_sys_ratio); i++) अणु
		अगर (wm8961_clk_sys_ratio[i].ratio >= target)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(wm8961_clk_sys_ratio)) अणु
		dev_err(component->dev, "Unable to generate CLK_SYS_RATE\n");
		वापस -EINVAL;
	पूर्ण
	dev_dbg(component->dev, "Selected CLK_SYS_RATE of %d for %d/%d=%d\n",
		wm8961_clk_sys_ratio[i].ratio, wm8961->sysclk, fs,
		wm8961->sysclk / fs);

	reg = snd_soc_component_पढ़ो(component, WM8961_CLOCKING_4);
	reg &= ~WM8961_CLK_SYS_RATE_MASK;
	reg |= wm8961_clk_sys_ratio[i].val << WM8961_CLK_SYS_RATE_SHIFT;
	snd_soc_component_ग_लिखो(component, WM8961_CLOCKING_4, reg);

	reg = snd_soc_component_पढ़ो(component, WM8961_AUDIO_INTERFACE_0);
	reg &= ~WM8961_WL_MASK;
	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		reg |= 1 << WM8961_WL_SHIFT;
		अवरोध;
	हाल 24:
		reg |= 2 << WM8961_WL_SHIFT;
		अवरोध;
	हाल 32:
		reg |= 3 << WM8961_WL_SHIFT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_ग_लिखो(component, WM8961_AUDIO_INTERFACE_0, reg);

	/* Sloping stop-band filter is recommended क्रम <= 24kHz */
	reg = snd_soc_component_पढ़ो(component, WM8961_ADC_DAC_CONTROL_2);
	अगर (fs <= 24000)
		reg |= WM8961_DACSLOPE;
	अन्यथा
		reg &= ~WM8961_DACSLOPE;
	snd_soc_component_ग_लिखो(component, WM8961_ADC_DAC_CONTROL_2, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8961_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
			     अचिन्हित पूर्णांक freq,
			     पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8961_priv *wm8961 = snd_soc_component_get_drvdata(component);
	u16 reg = snd_soc_component_पढ़ो(component, WM8961_CLOCKING1);

	अगर (freq > 33000000) अणु
		dev_err(component->dev, "MCLK must be <33MHz\n");
		वापस -EINVAL;
	पूर्ण

	अगर (freq > 16500000) अणु
		dev_dbg(component->dev, "Using MCLK/2 for %dHz MCLK\n", freq);
		reg |= WM8961_MCLKDIV;
		freq /= 2;
	पूर्ण अन्यथा अणु
		dev_dbg(component->dev, "Using MCLK/1 for %dHz MCLK\n", freq);
		reg &= ~WM8961_MCLKDIV;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8961_CLOCKING1, reg);

	wm8961->sysclk = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8961_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 aअगर = snd_soc_component_पढ़ो(component, WM8961_AUDIO_INTERFACE_0);

	aअगर &= ~(WM8961_BCLKINV | WM8961_LRP |
		 WM8961_MS | WM8961_FORMAT_MASK);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		aअगर |= WM8961_MS;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;

	हाल SND_SOC_DAIFMT_LEFT_J:
		aअगर |= 1;
		अवरोध;

	हाल SND_SOC_DAIFMT_I2S:
		aअगर |= 2;
		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_B:
		aअगर |= WM8961_LRP;
		fallthrough;
	हाल SND_SOC_DAIFMT_DSP_A:
		aअगर |= 3;
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
		हाल SND_SOC_DAIFMT_IB_NF:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		aअगर |= WM8961_LRP;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		aअगर |= WM8961_BCLKINV;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		aअगर |= WM8961_BCLKINV | WM8961_LRP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस snd_soc_component_ग_लिखो(component, WM8961_AUDIO_INTERFACE_0, aअगर);
पूर्ण

अटल पूर्णांक wm8961_set_tristate(काष्ठा snd_soc_dai *dai, पूर्णांक tristate)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 reg = snd_soc_component_पढ़ो(component, WM8961_ADDITIONAL_CONTROL_2);

	अगर (tristate)
		reg |= WM8961_TRIS;
	अन्यथा
		reg &= ~WM8961_TRIS;

	वापस snd_soc_component_ग_लिखो(component, WM8961_ADDITIONAL_CONTROL_2, reg);
पूर्ण

अटल पूर्णांक wm8961_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 reg = snd_soc_component_पढ़ो(component, WM8961_ADC_DAC_CONTROL_1);

	अगर (mute)
		reg |= WM8961_DACMU;
	अन्यथा
		reg &= ~WM8961_DACMU;

	msleep(17);

	वापस snd_soc_component_ग_लिखो(component, WM8961_ADC_DAC_CONTROL_1, reg);
पूर्ण

अटल पूर्णांक wm8961_set_clkभाग(काष्ठा snd_soc_dai *dai, पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 reg;

	चयन (भाग_id) अणु
	हाल WM8961_BCLK:
		reg = snd_soc_component_पढ़ो(component, WM8961_CLOCKING2);
		reg &= ~WM8961_BCLKDIV_MASK;
		reg |= भाग;
		snd_soc_component_ग_लिखो(component, WM8961_CLOCKING2, reg);
		अवरोध;

	हाल WM8961_LRCLK:
		reg = snd_soc_component_पढ़ो(component, WM8961_AUDIO_INTERFACE_2);
		reg &= ~WM8961_LRCLK_RATE_MASK;
		reg |= भाग;
		snd_soc_component_ग_लिखो(component, WM8961_AUDIO_INTERFACE_2, reg);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8961_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	u16 reg;

	/* This is all slightly unusual since we have no bypass paths
	 * and the output amplअगरier काष्ठाure means we can just slam
	 * the biases straight up rather than having to ramp them
	 * slowly.
	 */
	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_STANDBY) अणु
			/* Enable bias generation */
			reg = snd_soc_component_पढ़ो(component, WM8961_ANTI_POP);
			reg |= WM8961_BUFIOEN | WM8961_BUFDCOPEN;
			snd_soc_component_ग_लिखो(component, WM8961_ANTI_POP, reg);

			/* VMID=2*50k, VREF */
			reg = snd_soc_component_पढ़ो(component, WM8961_PWR_MGMT_1);
			reg &= ~WM8961_VMIDSEL_MASK;
			reg |= (1 << WM8961_VMIDSEL_SHIFT) | WM8961_VREF;
			snd_soc_component_ग_लिखो(component, WM8961_PWR_MGMT_1, reg);
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_PREPARE) अणु
			/* VREF off */
			reg = snd_soc_component_पढ़ो(component, WM8961_PWR_MGMT_1);
			reg &= ~WM8961_VREF;
			snd_soc_component_ग_लिखो(component, WM8961_PWR_MGMT_1, reg);

			/* Bias generation off */
			reg = snd_soc_component_पढ़ो(component, WM8961_ANTI_POP);
			reg &= ~(WM8961_BUFIOEN | WM8961_BUFDCOPEN);
			snd_soc_component_ग_लिखो(component, WM8961_ANTI_POP, reg);

			/* VMID off */
			reg = snd_soc_component_पढ़ो(component, WM8961_PWR_MGMT_1);
			reg &= ~WM8961_VMIDSEL_MASK;
			snd_soc_component_ग_लिखो(component, WM8961_PWR_MGMT_1, reg);
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण


#घोषणा WM8961_RATES SNDRV_PCM_RATE_8000_48000

#घोषणा WM8961_FORMATS \
	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
	SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8961_dai_ops = अणु
	.hw_params = wm8961_hw_params,
	.set_sysclk = wm8961_set_sysclk,
	.set_fmt = wm8961_set_fmt,
	.mute_stream = wm8961_mute,
	.set_tristate = wm8961_set_tristate,
	.set_clkभाग = wm8961_set_clkभाग,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8961_dai = अणु
	.name = "wm8961-hifi",
	.playback = अणु
		.stream_name = "HiFi Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8961_RATES,
		.क्रमmats = WM8961_FORMATS,पूर्ण,
	.capture = अणु
		.stream_name = "HiFi Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8961_RATES,
		.क्रमmats = WM8961_FORMATS,पूर्ण,
	.ops = &wm8961_dai_ops,
पूर्ण;

अटल पूर्णांक wm8961_probe(काष्ठा snd_soc_component *component)
अणु
	u16 reg;

	/* Enable class W */
	reg = snd_soc_component_पढ़ो(component, WM8961_CHARGE_PUMP_B);
	reg |= WM8961_CP_DYN_PWR_MASK;
	snd_soc_component_ग_लिखो(component, WM8961_CHARGE_PUMP_B, reg);

	/* Latch volume update bits (right channel only, we always
	 * ग_लिखो both out) and शेष ZC on. */
	reg = snd_soc_component_पढ़ो(component, WM8961_ROUT1_VOLUME);
	snd_soc_component_ग_लिखो(component, WM8961_ROUT1_VOLUME,
		     reg | WM8961_LO1ZC | WM8961_OUT1VU);
	snd_soc_component_ग_लिखो(component, WM8961_LOUT1_VOLUME, reg | WM8961_LO1ZC);
	reg = snd_soc_component_पढ़ो(component, WM8961_ROUT2_VOLUME);
	snd_soc_component_ग_लिखो(component, WM8961_ROUT2_VOLUME,
		     reg | WM8961_SPKRZC | WM8961_SPKVU);
	snd_soc_component_ग_लिखो(component, WM8961_LOUT2_VOLUME, reg | WM8961_SPKLZC);

	reg = snd_soc_component_पढ़ो(component, WM8961_RIGHT_ADC_VOLUME);
	snd_soc_component_ग_लिखो(component, WM8961_RIGHT_ADC_VOLUME, reg | WM8961_ADCVU);
	reg = snd_soc_component_पढ़ो(component, WM8961_RIGHT_INPUT_VOLUME);
	snd_soc_component_ग_लिखो(component, WM8961_RIGHT_INPUT_VOLUME, reg | WM8961_IPVU);

	/* Use soft mute by शेष */
	reg = snd_soc_component_पढ़ो(component, WM8961_ADC_DAC_CONTROL_2);
	reg |= WM8961_DACSMM;
	snd_soc_component_ग_लिखो(component, WM8961_ADC_DAC_CONTROL_2, reg);

	/* Use स्वतःmatic घड़ीing mode by शेष; क्रम now this is all
	 * we support.
	 */
	reg = snd_soc_component_पढ़ो(component, WM8961_CLOCKING_3);
	reg &= ~WM8961_MANUAL_MODE;
	snd_soc_component_ग_लिखो(component, WM8961_CLOCKING_3, reg);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक wm8961_resume(काष्ठा snd_soc_component *component)
अणु
	snd_soc_component_cache_sync(component);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा wm8961_resume शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8961 = अणु
	.probe			= wm8961_probe,
	.resume			= wm8961_resume,
	.set_bias_level		= wm8961_set_bias_level,
	.controls		= wm8961_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8961_snd_controls),
	.dapm_widमाला_लो		= wm8961_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8961_dapm_widमाला_लो),
	.dapm_routes		= audio_paths,
	.num_dapm_routes	= ARRAY_SIZE(audio_paths),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm8961_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = WM8961_MAX_REGISTER,

	.reg_शेषs = wm8961_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8961_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,

	.अस्थिर_reg = wm8961_अस्थिर,
	.पढ़ोable_reg = wm8961_पढ़ोable,
पूर्ण;

अटल पूर्णांक wm8961_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8961_priv *wm8961;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	wm8961 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8961_priv),
			      GFP_KERNEL);
	अगर (wm8961 == शून्य)
		वापस -ENOMEM;

	wm8961->regmap = devm_regmap_init_i2c(i2c, &wm8961_regmap);
	अगर (IS_ERR(wm8961->regmap))
		वापस PTR_ERR(wm8961->regmap);

	ret = regmap_पढ़ो(wm8961->regmap, WM8961_SOFTWARE_RESET, &val);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to read chip ID: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (val != 0x1801) अणु
		dev_err(&i2c->dev, "Device is not a WM8961: ID=0x%x\n", val);
		वापस -EINVAL;
	पूर्ण

	/* This isn't volatile - readback doesn't correspond to ग_लिखो */
	regcache_cache_bypass(wm8961->regmap, true);
	ret = regmap_पढ़ो(wm8961->regmap, WM8961_RIGHT_INPUT_VOLUME, &val);
	regcache_cache_bypass(wm8961->regmap, false);

	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to read chip revision: %d\n", ret);
		वापस ret;
	पूर्ण

	dev_info(&i2c->dev, "WM8961 family %d revision %c\n",
		 (val & WM8961_DEVICE_ID_MASK) >> WM8961_DEVICE_ID_SHIFT,
		 ((val & WM8961_CHIP_REV_MASK) >> WM8961_CHIP_REV_SHIFT)
		 + 'A');

	ret = regmap_ग_लिखो(wm8961->regmap, WM8961_SOFTWARE_RESET, 0x1801);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to issue reset: %d\n", ret);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(i2c, wm8961);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_wm8961, &wm8961_dai, 1);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8961_i2c_id[] = अणु
	अणु "wm8961", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8961_i2c_id);

अटल काष्ठा i2c_driver wm8961_i2c_driver = अणु
	.driver = अणु
		.name = "wm8961",
	पूर्ण,
	.probe =    wm8961_i2c_probe,
	.id_table = wm8961_i2c_id,
पूर्ण;

module_i2c_driver(wm8961_i2c_driver);

MODULE_DESCRIPTION("ASoC WM8961 driver");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
