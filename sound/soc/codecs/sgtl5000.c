<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// sgtl5000.c  --  SGTL5000 ALSA SoC Audio driver
//
// Copyright 2010-2011 Freescale Semiconductor, Inc. All Rights Reserved.

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/clk.h>
#समावेश <linux/log2.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/of_device.h>
#समावेश <sound/core.h>
#समावेश <sound/tlv.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>

#समावेश "sgtl5000.h"

#घोषणा SGTL5000_DAP_REG_OFFSET	0x0100
#घोषणा SGTL5000_MAX_REG_OFFSET	0x013A

/* Delay क्रम the VAG ramp up */
#घोषणा SGTL5000_VAG_POWERUP_DELAY 500 /* ms */
/* Delay क्रम the VAG ramp करोwn */
#घोषणा SGTL5000_VAG_POWERDOWN_DELAY 500 /* ms */

#घोषणा SGTL5000_OUTPUTS_MUTE (SGTL5000_HP_MUTE | SGTL5000_LINE_OUT_MUTE)

/* शेष value of sgtl5000 रेजिस्टरs */
अटल स्थिर काष्ठा reg_शेष sgtl5000_reg_शेषs[] = अणु
	अणु SGTL5000_CHIP_DIG_POWER,		0x0000 पूर्ण,
	अणु SGTL5000_CHIP_I2S_CTRL,		0x0010 पूर्ण,
	अणु SGTL5000_CHIP_SSS_CTRL,		0x0010 पूर्ण,
	अणु SGTL5000_CHIP_ADCDAC_CTRL,		0x020c पूर्ण,
	अणु SGTL5000_CHIP_DAC_VOL,		0x3c3c पूर्ण,
	अणु SGTL5000_CHIP_PAD_STRENGTH,		0x015f पूर्ण,
	अणु SGTL5000_CHIP_ANA_ADC_CTRL,		0x0000 पूर्ण,
	अणु SGTL5000_CHIP_ANA_HP_CTRL,		0x1818 पूर्ण,
	अणु SGTL5000_CHIP_ANA_CTRL,		0x0111 पूर्ण,
	अणु SGTL5000_CHIP_REF_CTRL,		0x0000 पूर्ण,
	अणु SGTL5000_CHIP_MIC_CTRL,		0x0000 पूर्ण,
	अणु SGTL5000_CHIP_LINE_OUT_CTRL,		0x0000 पूर्ण,
	अणु SGTL5000_CHIP_LINE_OUT_VOL,		0x0404 पूर्ण,
	अणु SGTL5000_CHIP_PLL_CTRL,		0x5000 पूर्ण,
	अणु SGTL5000_CHIP_CLK_TOP_CTRL,		0x0000 पूर्ण,
	अणु SGTL5000_CHIP_ANA_STATUS,		0x0000 पूर्ण,
	अणु SGTL5000_CHIP_SHORT_CTRL,		0x0000 पूर्ण,
	अणु SGTL5000_CHIP_ANA_TEST2,		0x0000 पूर्ण,
	अणु SGTL5000_DAP_CTRL,			0x0000 पूर्ण,
	अणु SGTL5000_DAP_PEQ,			0x0000 पूर्ण,
	अणु SGTL5000_DAP_BASS_ENHANCE,		0x0040 पूर्ण,
	अणु SGTL5000_DAP_BASS_ENHANCE_CTRL,	0x051f पूर्ण,
	अणु SGTL5000_DAP_AUDIO_EQ,		0x0000 पूर्ण,
	अणु SGTL5000_DAP_SURROUND,		0x0040 पूर्ण,
	अणु SGTL5000_DAP_EQ_BASS_BAND0,		0x002f पूर्ण,
	अणु SGTL5000_DAP_EQ_BASS_BAND1,		0x002f पूर्ण,
	अणु SGTL5000_DAP_EQ_BASS_BAND2,		0x002f पूर्ण,
	अणु SGTL5000_DAP_EQ_BASS_BAND3,		0x002f पूर्ण,
	अणु SGTL5000_DAP_EQ_BASS_BAND4,		0x002f पूर्ण,
	अणु SGTL5000_DAP_MAIN_CHAN,		0x8000 पूर्ण,
	अणु SGTL5000_DAP_MIX_CHAN,		0x0000 पूर्ण,
	अणु SGTL5000_DAP_AVC_CTRL,		0x5100 पूर्ण,
	अणु SGTL5000_DAP_AVC_THRESHOLD,		0x1473 पूर्ण,
	अणु SGTL5000_DAP_AVC_ATTACK,		0x0028 पूर्ण,
	अणु SGTL5000_DAP_AVC_DECAY,		0x0050 पूर्ण,
पूर्ण;

/* AVC: Threshold dB -> रेजिस्टर: pre-calculated values */
अटल स्थिर u16 avc_thr_db2reg[97] = अणु
	0x5168, 0x488E, 0x40AA, 0x39A1, 0x335D, 0x2DC7, 0x28CC, 0x245D, 0x2068,
	0x1CE2, 0x19BE, 0x16F1, 0x1472, 0x1239, 0x103E, 0x0E7A, 0x0CE6, 0x0B7F,
	0x0A3F, 0x0922, 0x0824, 0x0741, 0x0677, 0x05C3, 0x0522, 0x0493, 0x0414,
	0x03A2, 0x033D, 0x02E3, 0x0293, 0x024B, 0x020B, 0x01D2, 0x019F, 0x0172,
	0x014A, 0x0126, 0x0106, 0x00E9, 0x00D0, 0x00B9, 0x00A5, 0x0093, 0x0083,
	0x0075, 0x0068, 0x005D, 0x0052, 0x0049, 0x0041, 0x003A, 0x0034, 0x002E,
	0x0029, 0x0025, 0x0021, 0x001D, 0x001A, 0x0017, 0x0014, 0x0012, 0x0010,
	0x000E, 0x000D, 0x000B, 0x000A, 0x0009, 0x0008, 0x0007, 0x0006, 0x0005,
	0x0005, 0x0004, 0x0004, 0x0003, 0x0003, 0x0002, 0x0002, 0x0002, 0x0002,
	0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000पूर्ण;

/* regulator supplies क्रम sgtl5000, VDDD is an optional बाह्यal supply */
क्रमागत sgtl5000_regulator_supplies अणु
	VDDA,
	VDDIO,
	VDDD,
	SGTL5000_SUPPLY_NUM
पूर्ण;

/* vddd is optional supply */
अटल स्थिर अक्षर *supply_names[SGTL5000_SUPPLY_NUM] = अणु
	"VDDA",
	"VDDIO",
	"VDDD"
पूर्ण;

#घोषणा LDO_VOLTAGE		1200000
#घोषणा LINREG_VDDD	((1600 - LDO_VOLTAGE / 1000) / 50)

क्रमागत sgtl5000_micbias_resistor अणु
	SGTL5000_MICBIAS_OFF = 0,
	SGTL5000_MICBIAS_2K = 2,
	SGTL5000_MICBIAS_4K = 4,
	SGTL5000_MICBIAS_8K = 8,
पूर्ण;

क्रमागत  अणु
	I2S_LRCLK_STRENGTH_DISABLE,
	I2S_LRCLK_STRENGTH_LOW,
	I2S_LRCLK_STRENGTH_MEDIUM,
	I2S_LRCLK_STRENGTH_HIGH,
पूर्ण;

क्रमागत  अणु
	I2S_SCLK_STRENGTH_DISABLE,
	I2S_SCLK_STRENGTH_LOW,
	I2S_SCLK_STRENGTH_MEDIUM,
	I2S_SCLK_STRENGTH_HIGH,
पूर्ण;

क्रमागत अणु
	HP_POWER_EVENT,
	DAC_POWER_EVENT,
	ADC_POWER_EVENT,
	LAST_POWER_EVENT = ADC_POWER_EVENT
पूर्ण;

/* sgtl5000 निजी काष्ठाure in codec */
काष्ठा sgtl5000_priv अणु
	पूर्णांक sysclk;	/* sysclk rate */
	पूर्णांक master;	/* i2s master or not */
	पूर्णांक fmt;	/* i2s data क्रमmat */
	काष्ठा regulator_bulk_data supplies[SGTL5000_SUPPLY_NUM];
	पूर्णांक num_supplies;
	काष्ठा regmap *regmap;
	काष्ठा clk *mclk;
	पूर्णांक revision;
	u8 micbias_resistor;
	u8 micbias_voltage;
	u8 lrclk_strength;
	u8 sclk_strength;
	u16 mute_state[LAST_POWER_EVENT + 1];
पूर्ण;

अटल अंतरभूत पूर्णांक hp_sel_input(काष्ठा snd_soc_component *component)
अणु
	वापस (snd_soc_component_पढ़ो(component, SGTL5000_CHIP_ANA_CTRL) &
		SGTL5000_HP_SEL_MASK) >> SGTL5000_HP_SEL_SHIFT;
पूर्ण

अटल अंतरभूत u16 mute_output(काष्ठा snd_soc_component *component,
			      u16 mute_mask)
अणु
	u16 mute_reg = snd_soc_component_पढ़ो(component,
					      SGTL5000_CHIP_ANA_CTRL);

	snd_soc_component_update_bits(component, SGTL5000_CHIP_ANA_CTRL,
			    mute_mask, mute_mask);
	वापस mute_reg;
पूर्ण

अटल अंतरभूत व्योम restore_output(काष्ठा snd_soc_component *component,
				  u16 mute_mask, u16 mute_reg)
अणु
	snd_soc_component_update_bits(component, SGTL5000_CHIP_ANA_CTRL,
		mute_mask, mute_reg);
पूर्ण

अटल व्योम vag_घातer_on(काष्ठा snd_soc_component *component, u32 source)
अणु
	अगर (snd_soc_component_पढ़ो(component, SGTL5000_CHIP_ANA_POWER) &
	    SGTL5000_VAG_POWERUP)
		वापस;

	snd_soc_component_update_bits(component, SGTL5000_CHIP_ANA_POWER,
			    SGTL5000_VAG_POWERUP, SGTL5000_VAG_POWERUP);

	/* When VAG घातering on to get local loop from Line-In, the sleep
	 * is required to aव्योम loud pop.
	 */
	अगर (hp_sel_input(component) == SGTL5000_HP_SEL_LINE_IN &&
	    source == HP_POWER_EVENT)
		msleep(SGTL5000_VAG_POWERUP_DELAY);
पूर्ण

अटल पूर्णांक vag_घातer_consumers(काष्ठा snd_soc_component *component,
			       u16 ana_pwr_reg, u32 source)
अणु
	पूर्णांक consumers = 0;

	/* count dac/adc consumers unconditional */
	अगर (ana_pwr_reg & SGTL5000_DAC_POWERUP)
		consumers++;
	अगर (ana_pwr_reg & SGTL5000_ADC_POWERUP)
		consumers++;

	/*
	 * If the event comes from HP and Line-In is selected,
	 * current action is 'DAC to be powered down'.
	 * As HP_POWERUP is not set when HP muxed to line-in,
	 * we need to keep VAG घातer ON.
	 */
	अगर (source == HP_POWER_EVENT) अणु
		अगर (hp_sel_input(component) == SGTL5000_HP_SEL_LINE_IN)
			consumers++;
	पूर्ण अन्यथा अणु
		अगर (ana_pwr_reg & SGTL5000_HP_POWERUP)
			consumers++;
	पूर्ण

	वापस consumers;
पूर्ण

अटल व्योम vag_घातer_off(काष्ठा snd_soc_component *component, u32 source)
अणु
	u16 ana_pwr = snd_soc_component_पढ़ो(component,
					     SGTL5000_CHIP_ANA_POWER);

	अगर (!(ana_pwr & SGTL5000_VAG_POWERUP))
		वापस;

	/*
	 * This function calls when any of VAG घातer consumers is disappearing.
	 * Thus, अगर there is more than one consumer at the moment, as minimum
	 * one consumer will definitely stay after the end of the current
	 * event.
	 * Don't clear VAG_POWERUP अगर 2 or more consumers of VAG present:
	 * - LINE_IN (क्रम HP events) / HP (क्रम DAC/ADC events)
	 * - DAC
	 * - ADC
	 * (the current consumer is disappearing right now)
	 */
	अगर (vag_घातer_consumers(component, ana_pwr, source) >= 2)
		वापस;

	snd_soc_component_update_bits(component, SGTL5000_CHIP_ANA_POWER,
		SGTL5000_VAG_POWERUP, 0);
	/* In घातer करोwn हाल, we need रुको 400-1000 ms
	 * when VAG fully ramped करोwn.
	 * As दीर्घer we रुको, as smaller pop we've got.
	 */
	msleep(SGTL5000_VAG_POWERDOWN_DELAY);
पूर्ण

/*
 * mic_bias घातer on/off share the same रेजिस्टर bits with
 * output impedance of mic bias, when घातer on mic bias, we
 * need reclaim it to impedance value.
 * 0x0 = Powered off
 * 0x1 = 2Kohm
 * 0x2 = 4Kohm
 * 0x3 = 8Kohm
 */
अटल पूर्णांक mic_bias_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा sgtl5000_priv *sgtl5000 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* change mic bias resistor */
		snd_soc_component_update_bits(component, SGTL5000_CHIP_MIC_CTRL,
			SGTL5000_BIAS_R_MASK,
			sgtl5000->micbias_resistor << SGTL5000_BIAS_R_SHIFT);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, SGTL5000_CHIP_MIC_CTRL,
				SGTL5000_BIAS_R_MASK, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vag_and_mute_control(काष्ठा snd_soc_component *component,
				 पूर्णांक event, पूर्णांक event_source)
अणु
	अटल स्थिर u16 mute_mask[] = अणु
		/*
		 * Mask क्रम HP_POWER_EVENT.
		 * Muxing Headphones have to be wrapped with mute/unmute
		 * headphones only.
		 */
		SGTL5000_HP_MUTE,
		/*
		 * Masks क्रम DAC_POWER_EVENT/ADC_POWER_EVENT.
		 * Muxing DAC or ADC block have to wrapped with mute/unmute
		 * both headphones and line-out.
		 */
		SGTL5000_OUTPUTS_MUTE,
		SGTL5000_OUTPUTS_MUTE
	पूर्ण;

	काष्ठा sgtl5000_priv *sgtl5000 =
		snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		sgtl5000->mute_state[event_source] =
			mute_output(component, mute_mask[event_source]);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		vag_घातer_on(component, event_source);
		restore_output(component, mute_mask[event_source],
			       sgtl5000->mute_state[event_source]);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		sgtl5000->mute_state[event_source] =
			mute_output(component, mute_mask[event_source]);
		vag_घातer_off(component, event_source);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		restore_output(component, mute_mask[event_source],
			       sgtl5000->mute_state[event_source]);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Mute Headphone when घातer it up/करोwn.
 * Control VAG घातer on HP घातer path.
 */
अटल पूर्णांक headphone_pga_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);

	वापस vag_and_mute_control(component, event, HP_POWER_EVENT);
पूर्ण

/* As manual describes, ADC/DAC घातering up/करोwn requires
 * to mute outमाला_दो to aव्योम pops.
 * Control VAG घातer on ADC/DAC घातer path.
 */
अटल पूर्णांक adc_upकरोwn_depop(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);

	वापस vag_and_mute_control(component, event, ADC_POWER_EVENT);
पूर्ण

अटल पूर्णांक dac_upकरोwn_depop(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);

	वापस vag_and_mute_control(component, event, DAC_POWER_EVENT);
पूर्ण

/* input sources क्रम ADC */
अटल स्थिर अक्षर *adc_mux_text[] = अणु
	"MIC_IN", "LINE_IN"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adc_क्रमागत,
			    SGTL5000_CHIP_ANA_CTRL, 2,
			    adc_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new adc_mux =
SOC_DAPM_ENUM("Capture Mux", adc_क्रमागत);

/* input sources क्रम headphone */
अटल स्थिर अक्षर *hp_mux_text[] = अणु
	"DAC", "LINE_IN"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(hp_क्रमागत,
			    SGTL5000_CHIP_ANA_CTRL, 6,
			    hp_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new hp_mux =
SOC_DAPM_ENUM("Headphone Mux", hp_क्रमागत);

/* input sources क्रम DAC */
अटल स्थिर अक्षर *dac_mux_text[] = अणु
	"ADC", "I2S", "Rsvrd", "DAP"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(dac_क्रमागत,
			    SGTL5000_CHIP_SSS_CTRL, SGTL5000_DAC_SEL_SHIFT,
			    dac_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new dac_mux =
SOC_DAPM_ENUM("Digital Input Mux", dac_क्रमागत);

/* input sources क्रम DAP */
अटल स्थिर अक्षर *dap_mux_text[] = अणु
	"ADC", "I2S"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(dap_क्रमागत,
			    SGTL5000_CHIP_SSS_CTRL, SGTL5000_DAP_SEL_SHIFT,
			    dap_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new dap_mux =
SOC_DAPM_ENUM("DAP Mux", dap_क्रमागत);

/* input sources क्रम DAP mix */
अटल स्थिर अक्षर *dapmix_mux_text[] = अणु
	"ADC", "I2S"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(dapmix_क्रमागत,
			    SGTL5000_CHIP_SSS_CTRL, SGTL5000_DAP_MIX_SEL_SHIFT,
			    dapmix_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new dapmix_mux =
SOC_DAPM_ENUM("DAP MIX Mux", dapmix_क्रमागत);


अटल स्थिर काष्ठा snd_soc_dapm_widget sgtl5000_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("LINE_IN"),
	SND_SOC_DAPM_INPUT("MIC_IN"),

	SND_SOC_DAPM_OUTPUT("HP_OUT"),
	SND_SOC_DAPM_OUTPUT("LINE_OUT"),

	SND_SOC_DAPM_SUPPLY("Mic Bias", SGTL5000_CHIP_MIC_CTRL, 8, 0,
			    mic_bias_event,
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_PGA_E("HP", SGTL5000_CHIP_ANA_POWER, 4, 0, शून्य, 0,
			   headphone_pga_event,
			   SND_SOC_DAPM_PRE_POST_PMU |
			   SND_SOC_DAPM_PRE_POST_PMD),
	SND_SOC_DAPM_PGA("LO", SGTL5000_CHIP_ANA_POWER, 0, 0, शून्य, 0),

	SND_SOC_DAPM_MUX("Capture Mux", SND_SOC_NOPM, 0, 0, &adc_mux),
	SND_SOC_DAPM_MUX("Headphone Mux", SND_SOC_NOPM, 0, 0, &hp_mux),
	SND_SOC_DAPM_MUX("Digital Input Mux", SND_SOC_NOPM, 0, 0, &dac_mux),
	SND_SOC_DAPM_MUX("DAP Mux", SGTL5000_DAP_CTRL, 0, 0, &dap_mux),
	SND_SOC_DAPM_MUX("DAP MIX Mux", SGTL5000_DAP_CTRL, 4, 0, &dapmix_mux),
	SND_SOC_DAPM_MIXER("DAP", SGTL5000_CHIP_DIG_POWER, 4, 0, शून्य, 0),


	/* aअगर क्रम i2s input */
	SND_SOC_DAPM_AIF_IN("AIFIN", "Playback",
				0, SGTL5000_CHIP_DIG_POWER,
				0, 0),

	/* aअगर क्रम i2s output */
	SND_SOC_DAPM_AIF_OUT("AIFOUT", "Capture",
				0, SGTL5000_CHIP_DIG_POWER,
				1, 0),

	SND_SOC_DAPM_ADC_E("ADC", "Capture", SGTL5000_CHIP_ANA_POWER, 1, 0,
			   adc_upकरोwn_depop, SND_SOC_DAPM_PRE_POST_PMU |
			   SND_SOC_DAPM_PRE_POST_PMD),
	SND_SOC_DAPM_DAC_E("DAC", "Playback", SGTL5000_CHIP_ANA_POWER, 3, 0,
			   dac_upकरोwn_depop, SND_SOC_DAPM_PRE_POST_PMU |
			   SND_SOC_DAPM_PRE_POST_PMD),
पूर्ण;

/* routes क्रम sgtl5000 */
अटल स्थिर काष्ठा snd_soc_dapm_route sgtl5000_dapm_routes[] = अणु
	अणु"Capture Mux", "LINE_IN", "LINE_IN"पूर्ण,	/* line_in --> adc_mux */
	अणु"Capture Mux", "MIC_IN", "MIC_IN"पूर्ण,	/* mic_in --> adc_mux */

	अणु"ADC", शून्य, "Capture Mux"पूर्ण,		/* adc_mux --> adc */
	अणु"AIFOUT", शून्य, "ADC"पूर्ण,		/* adc --> i2s_out */

	अणु"DAP Mux", "ADC", "ADC"पूर्ण,		/* adc --> DAP mux */
	अणु"DAP Mux", शून्य, "AIFIN"पूर्ण,		/* i2s --> DAP mux */
	अणु"DAP", शून्य, "DAP Mux"पूर्ण,		/* DAP mux --> dap */

	अणु"DAP MIX Mux", "ADC", "ADC"पूर्ण,		/* adc --> DAP MIX mux */
	अणु"DAP MIX Mux", शून्य, "AIFIN"पूर्ण,		/* i2s --> DAP MIX mux */
	अणु"DAP", शून्य, "DAP MIX Mux"पूर्ण,		/* DAP MIX mux --> dap */

	अणु"Digital Input Mux", "ADC", "ADC"पूर्ण,	/* adc --> audio mux */
	अणु"Digital Input Mux", शून्य, "AIFIN"पूर्ण,	/* i2s --> audio mux */
	अणु"Digital Input Mux", शून्य, "DAP"पूर्ण,	/* dap --> audio mux */
	अणु"DAC", शून्य, "Digital Input Mux"पूर्ण,	/* audio mux --> dac */

	अणु"Headphone Mux", "DAC", "DAC"पूर्ण,	/* dac --> hp_mux */
	अणु"LO", शून्य, "DAC"पूर्ण,			/* dac --> line_out */

	अणु"Headphone Mux", "LINE_IN", "LINE_IN"पूर्ण,/* line_in --> hp_mux */
	अणु"HP", शून्य, "Headphone Mux"पूर्ण,		/* hp_mux --> hp */

	अणु"LINE_OUT", शून्य, "LO"पूर्ण,
	अणु"HP_OUT", शून्य, "HP"पूर्ण,
पूर्ण;

/* custom function to fetch info of PCM playback volume */
अटल पूर्णांक dac_info_volsw(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 0xfc - 0x3c;
	वापस 0;
पूर्ण

/*
 * custom function to get of PCM playback volume
 *
 * dac volume रेजिस्टर
 * 15-------------8-7--------------0
 * | R channel vol | L channel vol |
 *  -------------------------------
 *
 * PCM volume with 0.5017 dB steps from 0 to -90 dB
 *
 * रेजिस्टर values map to dB
 * 0x3B and less = Reserved
 * 0x3C = 0 dB
 * 0x3D = -0.5 dB
 * 0xF0 = -90 dB
 * 0xFC and greater = Muted
 *
 * रेजिस्टर value map to userspace value
 *
 * रेजिस्टर value	0x3c(0dB)	  0xf0(-90dB)0xfc
 *			------------------------------
 * userspace value	0xc0			     0
 */
अटल पूर्णांक dac_get_volsw(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	पूर्णांक reg;
	पूर्णांक l;
	पूर्णांक r;

	reg = snd_soc_component_पढ़ो(component, SGTL5000_CHIP_DAC_VOL);

	/* get left channel volume */
	l = (reg & SGTL5000_DAC_VOL_LEFT_MASK) >> SGTL5000_DAC_VOL_LEFT_SHIFT;

	/* get right channel volume */
	r = (reg & SGTL5000_DAC_VOL_RIGHT_MASK) >> SGTL5000_DAC_VOL_RIGHT_SHIFT;

	/* make sure value fall in (0x3c,0xfc) */
	l = clamp(l, 0x3c, 0xfc);
	r = clamp(r, 0x3c, 0xfc);

	/* invert it and map to userspace value */
	l = 0xfc - l;
	r = 0xfc - r;

	ucontrol->value.पूर्णांकeger.value[0] = l;
	ucontrol->value.पूर्णांकeger.value[1] = r;

	वापस 0;
पूर्ण

/*
 * custom function to put of PCM playback volume
 *
 * dac volume रेजिस्टर
 * 15-------------8-7--------------0
 * | R channel vol | L channel vol |
 *  -------------------------------
 *
 * PCM volume with 0.5017 dB steps from 0 to -90 dB
 *
 * रेजिस्टर values map to dB
 * 0x3B and less = Reserved
 * 0x3C = 0 dB
 * 0x3D = -0.5 dB
 * 0xF0 = -90 dB
 * 0xFC and greater = Muted
 *
 * userspace value map to रेजिस्टर value
 *
 * userspace value	0xc0			     0
 *			------------------------------
 * रेजिस्टर value	0x3c(0dB)	0xf0(-90dB)0xfc
 */
अटल पूर्णांक dac_put_volsw(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	पूर्णांक reg;
	पूर्णांक l;
	पूर्णांक r;

	l = ucontrol->value.पूर्णांकeger.value[0];
	r = ucontrol->value.पूर्णांकeger.value[1];

	/* make sure userspace volume fall in (0, 0xfc-0x3c) */
	l = clamp(l, 0, 0xfc - 0x3c);
	r = clamp(r, 0, 0xfc - 0x3c);

	/* invert it, get the value can be set to रेजिस्टर */
	l = 0xfc - l;
	r = 0xfc - r;

	/* shअगरt to get the रेजिस्टर value */
	reg = l << SGTL5000_DAC_VOL_LEFT_SHIFT |
		r << SGTL5000_DAC_VOL_RIGHT_SHIFT;

	snd_soc_component_ग_लिखो(component, SGTL5000_CHIP_DAC_VOL, reg);

	वापस 0;
पूर्ण

/*
 * custom function to get AVC threshold
 *
 * The threshold dB is calculated by rearranging the calculation from the
 * avc_put_threshold function: रेजिस्टर_value = 10^(dB/20) * 0.636 * 2^15 ==>
 * dB = ( fls(रेजिस्टर_value) - 14.347 ) * 6.02
 *
 * As this calculation is expensive and the threshold dB values may not exceed
 * 0 to 96 we use pre-calculated values.
 */
अटल पूर्णांक avc_get_threshold(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	पूर्णांक db, i;
	u16 reg = snd_soc_component_पढ़ो(component, SGTL5000_DAP_AVC_THRESHOLD);

	/* रेजिस्टर value 0 => -96dB */
	अगर (!reg) अणु
		ucontrol->value.पूर्णांकeger.value[0] = 96;
		ucontrol->value.पूर्णांकeger.value[1] = 96;
		वापस 0;
	पूर्ण

	/* get dB from रेजिस्टर value (rounded करोwn) */
	क्रम (i = 0; avc_thr_db2reg[i] > reg; i++)
		;
	db = i;

	ucontrol->value.पूर्णांकeger.value[0] = db;
	ucontrol->value.पूर्णांकeger.value[1] = db;

	वापस 0;
पूर्ण

/*
 * custom function to put AVC threshold
 *
 * The रेजिस्टर value is calculated by following क्रमmula:
 *                                    रेजिस्टर_value = 10^(dB/20) * 0.636 * 2^15
 * As this calculation is expensive and the threshold dB values may not exceed
 * 0 to 96 we use pre-calculated values.
 */
अटल पूर्णांक avc_put_threshold(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	पूर्णांक db;
	u16 reg;

	db = (पूर्णांक)ucontrol->value.पूर्णांकeger.value[0];
	अगर (db < 0 || db > 96)
		वापस -EINVAL;
	reg = avc_thr_db2reg[db];
	snd_soc_component_ग_लिखो(component, SGTL5000_DAP_AVC_THRESHOLD, reg);

	वापस 0;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(capture_6db_attenuate, -600, 600, 0);

/* tlv क्रम mic gain, 0db 20db 30db 40db */
अटल स्थिर DECLARE_TLV_DB_RANGE(mic_gain_tlv,
	0, 0, TLV_DB_SCALE_ITEM(0, 0, 0),
	1, 3, TLV_DB_SCALE_ITEM(2000, 1000, 0)
);

/* tlv क्रम DAP channels, 0% - 100% - 200% */
अटल स्थिर DECLARE_TLV_DB_SCALE(dap_volume, 0, 1, 0);

/* tlv क्रम bass bands, -11.75db to 12.0db, step .25db */
अटल स्थिर DECLARE_TLV_DB_SCALE(bass_band, -1175, 25, 0);

/* tlv क्रम hp volume, -51.5db to 12.0db, step .5db */
अटल स्थिर DECLARE_TLV_DB_SCALE(headphone_volume, -5150, 50, 0);

/* tlv क्रम lineout volume, 31 steps of .5db each */
अटल स्थिर DECLARE_TLV_DB_SCALE(lineout_volume, -1550, 50, 0);

/* tlv क्रम dap avc max gain, 0db, 6db, 12db */
अटल स्थिर DECLARE_TLV_DB_SCALE(avc_max_gain, 0, 600, 0);

/* tlv क्रम dap avc threshold, */
अटल स्थिर DECLARE_TLV_DB_MINMAX(avc_threshold, 0, 9600);

अटल स्थिर काष्ठा snd_kcontrol_new sgtl5000_snd_controls[] = अणु
	/* SOC_DOUBLE_S8_TLV with invert */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "PCM Playback Volume",
		.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ |
			SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.info = dac_info_volsw,
		.get = dac_get_volsw,
		.put = dac_put_volsw,
	पूर्ण,

	SOC_DOUBLE("Capture Volume", SGTL5000_CHIP_ANA_ADC_CTRL, 0, 4, 0xf, 0),
	SOC_SINGLE_TLV("Capture Attenuate Switch (-6dB)",
			SGTL5000_CHIP_ANA_ADC_CTRL,
			8, 1, 0, capture_6db_attenuate),
	SOC_SINGLE("Capture ZC Switch", SGTL5000_CHIP_ANA_CTRL, 1, 1, 0),
	SOC_SINGLE("Capture Switch", SGTL5000_CHIP_ANA_CTRL, 0, 1, 1),

	SOC_DOUBLE_TLV("Headphone Playback Volume",
			SGTL5000_CHIP_ANA_HP_CTRL,
			0, 8,
			0x7f, 1,
			headphone_volume),
	SOC_SINGLE("Headphone Playback Switch", SGTL5000_CHIP_ANA_CTRL,
			4, 1, 1),
	SOC_SINGLE("Headphone Playback ZC Switch", SGTL5000_CHIP_ANA_CTRL,
			5, 1, 0),

	SOC_SINGLE_TLV("Mic Volume", SGTL5000_CHIP_MIC_CTRL,
			0, 3, 0, mic_gain_tlv),

	SOC_DOUBLE_TLV("Lineout Playback Volume",
			SGTL5000_CHIP_LINE_OUT_VOL,
			SGTL5000_LINE_OUT_VOL_LEFT_SHIFT,
			SGTL5000_LINE_OUT_VOL_RIGHT_SHIFT,
			0x1f, 1,
			lineout_volume),
	SOC_SINGLE("Lineout Playback Switch", SGTL5000_CHIP_ANA_CTRL, 8, 1, 1),

	SOC_SINGLE_TLV("DAP Main channel", SGTL5000_DAP_MAIN_CHAN,
	0, 0xffff, 0, dap_volume),

	SOC_SINGLE_TLV("DAP Mix channel", SGTL5000_DAP_MIX_CHAN,
	0, 0xffff, 0, dap_volume),
	/* Automatic Volume Control (DAP AVC) */
	SOC_SINGLE("AVC Switch", SGTL5000_DAP_AVC_CTRL, 0, 1, 0),
	SOC_SINGLE("AVC Hard Limiter Switch", SGTL5000_DAP_AVC_CTRL, 5, 1, 0),
	SOC_SINGLE_TLV("AVC Max Gain Volume", SGTL5000_DAP_AVC_CTRL, 12, 2, 0,
			avc_max_gain),
	SOC_SINGLE("AVC Integrator Response", SGTL5000_DAP_AVC_CTRL, 8, 3, 0),
	SOC_SINGLE_EXT_TLV("AVC Threshold Volume", SGTL5000_DAP_AVC_THRESHOLD,
			0, 96, 0, avc_get_threshold, avc_put_threshold,
			avc_threshold),

	SOC_SINGLE_TLV("BASS 0", SGTL5000_DAP_EQ_BASS_BAND0,
	0, 0x5F, 0, bass_band),

	SOC_SINGLE_TLV("BASS 1", SGTL5000_DAP_EQ_BASS_BAND1,
	0, 0x5F, 0, bass_band),

	SOC_SINGLE_TLV("BASS 2", SGTL5000_DAP_EQ_BASS_BAND2,
	0, 0x5F, 0, bass_band),

	SOC_SINGLE_TLV("BASS 3", SGTL5000_DAP_EQ_BASS_BAND3,
	0, 0x5F, 0, bass_band),

	SOC_SINGLE_TLV("BASS 4", SGTL5000_DAP_EQ_BASS_BAND4,
	0, 0x5F, 0, bass_band),
पूर्ण;

/* mute the codec used by alsa core */
अटल पूर्णांक sgtl5000_mute_stream(काष्ठा snd_soc_dai *codec_dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 i2s_pwr = SGTL5000_I2S_IN_POWERUP;

	/*
	 * During 'digital mute' करो not mute DAC
	 * because LINE_IN would be muted aswell. We want to mute
	 * only I2S block - this can be करोne by घातering it off
	 */
	snd_soc_component_update_bits(component, SGTL5000_CHIP_DIG_POWER,
			i2s_pwr, mute ? 0 : i2s_pwr);

	वापस 0;
पूर्ण

/* set codec क्रमmat */
अटल पूर्णांक sgtl5000_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा sgtl5000_priv *sgtl5000 = snd_soc_component_get_drvdata(component);
	u16 i2sctl = 0;

	sgtl5000->master = 0;
	/*
	 * i2s घड़ी and frame master setting.
	 * ONLY support:
	 *  - घड़ी and frame slave,
	 *  - घड़ी and frame master
	 */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		i2sctl |= SGTL5000_I2S_MASTER;
		sgtl5000->master = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* setting i2s data क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
		i2sctl |= SGTL5000_I2S_MODE_PCM << SGTL5000_I2S_MODE_SHIFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		i2sctl |= SGTL5000_I2S_MODE_PCM << SGTL5000_I2S_MODE_SHIFT;
		i2sctl |= SGTL5000_I2S_LRALIGN;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		i2sctl |= SGTL5000_I2S_MODE_I2S_LJ << SGTL5000_I2S_MODE_SHIFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		i2sctl |= SGTL5000_I2S_MODE_RJ << SGTL5000_I2S_MODE_SHIFT;
		i2sctl |= SGTL5000_I2S_LRPOL;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		i2sctl |= SGTL5000_I2S_MODE_I2S_LJ << SGTL5000_I2S_MODE_SHIFT;
		i2sctl |= SGTL5000_I2S_LRALIGN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	sgtl5000->fmt = fmt & SND_SOC_DAIFMT_FORMAT_MASK;

	/* Clock inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		i2sctl |= SGTL5000_I2S_SCLK_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, SGTL5000_CHIP_I2S_CTRL, i2sctl);

	वापस 0;
पूर्ण

/* set codec sysclk */
अटल पूर्णांक sgtl5000_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				   पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा sgtl5000_priv *sgtl5000 = snd_soc_component_get_drvdata(component);

	चयन (clk_id) अणु
	हाल SGTL5000_SYSCLK:
		sgtl5000->sysclk = freq;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * set घड़ी according to i2s frame घड़ी,
 * sgtl5000 provides 2 घड़ी sources:
 * 1. sys_mclk: sample freq can only be configured to
 *	1/256, 1/384, 1/512 of sys_mclk.
 * 2. pll: can derive any audio घड़ीs.
 *
 * घड़ी setting rules:
 * 1. in slave mode, only sys_mclk can be used
 * 2. as स्थिरraपूर्णांक by sys_mclk, sample freq should be set to 32 kHz, 44.1 kHz
 * and above.
 * 3. usage of sys_mclk is preferred over pll to save घातer.
 */
अटल पूर्णांक sgtl5000_set_घड़ी(काष्ठा snd_soc_component *component, पूर्णांक frame_rate)
अणु
	काष्ठा sgtl5000_priv *sgtl5000 = snd_soc_component_get_drvdata(component);
	पूर्णांक clk_ctl = 0;
	पूर्णांक sys_fs;	/* sample freq */

	/*
	 * sample freq should be भागided by frame घड़ी,
	 * अगर frame घड़ी is lower than 44.1 kHz, sample freq should be set to
	 * 32 kHz or 44.1 kHz.
	 */
	चयन (frame_rate) अणु
	हाल 8000:
	हाल 16000:
		sys_fs = 32000;
		अवरोध;
	हाल 11025:
	हाल 22050:
		sys_fs = 44100;
		अवरोध;
	शेष:
		sys_fs = frame_rate;
		अवरोध;
	पूर्ण

	/* set भागided factor of frame घड़ी */
	चयन (sys_fs / frame_rate) अणु
	हाल 4:
		clk_ctl |= SGTL5000_RATE_MODE_DIV_4 << SGTL5000_RATE_MODE_SHIFT;
		अवरोध;
	हाल 2:
		clk_ctl |= SGTL5000_RATE_MODE_DIV_2 << SGTL5000_RATE_MODE_SHIFT;
		अवरोध;
	हाल 1:
		clk_ctl |= SGTL5000_RATE_MODE_DIV_1 << SGTL5000_RATE_MODE_SHIFT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* set the sys_fs according to frame rate */
	चयन (sys_fs) अणु
	हाल 32000:
		clk_ctl |= SGTL5000_SYS_FS_32k << SGTL5000_SYS_FS_SHIFT;
		अवरोध;
	हाल 44100:
		clk_ctl |= SGTL5000_SYS_FS_44_1k << SGTL5000_SYS_FS_SHIFT;
		अवरोध;
	हाल 48000:
		clk_ctl |= SGTL5000_SYS_FS_48k << SGTL5000_SYS_FS_SHIFT;
		अवरोध;
	हाल 96000:
		clk_ctl |= SGTL5000_SYS_FS_96k << SGTL5000_SYS_FS_SHIFT;
		अवरोध;
	शेष:
		dev_err(component->dev, "frame rate %d not supported\n",
			frame_rate);
		वापस -EINVAL;
	पूर्ण

	/*
	 * calculate the भागider of mclk/sample_freq,
	 * factor of freq = 96 kHz can only be 256, since mclk is in the range
	 * of 8 MHz - 27 MHz
	 */
	चयन (sgtl5000->sysclk / frame_rate) अणु
	हाल 256:
		clk_ctl |= SGTL5000_MCLK_FREQ_256FS <<
			SGTL5000_MCLK_FREQ_SHIFT;
		अवरोध;
	हाल 384:
		clk_ctl |= SGTL5000_MCLK_FREQ_384FS <<
			SGTL5000_MCLK_FREQ_SHIFT;
		अवरोध;
	हाल 512:
		clk_ctl |= SGTL5000_MCLK_FREQ_512FS <<
			SGTL5000_MCLK_FREQ_SHIFT;
		अवरोध;
	शेष:
		/* अगर mclk करोes not satisfy the भागider, use pll */
		अगर (sgtl5000->master) अणु
			clk_ctl |= SGTL5000_MCLK_FREQ_PLL <<
				SGTL5000_MCLK_FREQ_SHIFT;
		पूर्ण अन्यथा अणु
			dev_err(component->dev,
				"PLL not supported in slave mode\n");
			dev_err(component->dev, "%d ratio is not supported. "
				"SYS_MCLK needs to be 256, 384 or 512 * fs\n",
				sgtl5000->sysclk / frame_rate);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* अगर using pll, please check manual 6.4.2 क्रम detail */
	अगर ((clk_ctl & SGTL5000_MCLK_FREQ_MASK) == SGTL5000_MCLK_FREQ_PLL) अणु
		u64 out, t;
		पूर्णांक भाग2;
		पूर्णांक pll_ctl;
		अचिन्हित पूर्णांक in, पूर्णांक_भाग, frac_भाग;

		अगर (sgtl5000->sysclk > 17000000) अणु
			भाग2 = 1;
			in = sgtl5000->sysclk / 2;
		पूर्ण अन्यथा अणु
			भाग2 = 0;
			in = sgtl5000->sysclk;
		पूर्ण
		अगर (sys_fs == 44100)
			out = 180633600;
		अन्यथा
			out = 196608000;
		t = करो_भाग(out, in);
		पूर्णांक_भाग = out;
		t *= 2048;
		करो_भाग(t, in);
		frac_भाग = t;
		pll_ctl = पूर्णांक_भाग << SGTL5000_PLL_INT_DIV_SHIFT |
		    frac_भाग << SGTL5000_PLL_FRAC_DIV_SHIFT;

		snd_soc_component_ग_लिखो(component, SGTL5000_CHIP_PLL_CTRL, pll_ctl);
		अगर (भाग2)
			snd_soc_component_update_bits(component,
				SGTL5000_CHIP_CLK_TOP_CTRL,
				SGTL5000_INPUT_FREQ_DIV2,
				SGTL5000_INPUT_FREQ_DIV2);
		अन्यथा
			snd_soc_component_update_bits(component,
				SGTL5000_CHIP_CLK_TOP_CTRL,
				SGTL5000_INPUT_FREQ_DIV2,
				0);

		/* घातer up pll */
		snd_soc_component_update_bits(component, SGTL5000_CHIP_ANA_POWER,
			SGTL5000_PLL_POWERUP | SGTL5000_VCOAMP_POWERUP,
			SGTL5000_PLL_POWERUP | SGTL5000_VCOAMP_POWERUP);

		/* अगर using pll, clk_ctrl must be set after pll घातer up */
		snd_soc_component_ग_लिखो(component, SGTL5000_CHIP_CLK_CTRL, clk_ctl);
	पूर्ण अन्यथा अणु
		/* otherwise, clk_ctrl must be set beक्रमe pll घातer करोwn */
		snd_soc_component_ग_लिखो(component, SGTL5000_CHIP_CLK_CTRL, clk_ctl);

		/* घातer करोwn pll */
		snd_soc_component_update_bits(component, SGTL5000_CHIP_ANA_POWER,
			SGTL5000_PLL_POWERUP | SGTL5000_VCOAMP_POWERUP,
			0);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Set PCM DAI bit size and sample rate.
 * input: params_rate, params_fmt
 */
अटल पूर्णांक sgtl5000_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा sgtl5000_priv *sgtl5000 = snd_soc_component_get_drvdata(component);
	पूर्णांक channels = params_channels(params);
	पूर्णांक i2s_ctl = 0;
	पूर्णांक stereo;
	पूर्णांक ret;

	/* sysclk should alपढ़ोy set */
	अगर (!sgtl5000->sysclk) अणु
		dev_err(component->dev, "%s: set sysclk first!\n", __func__);
		वापस -EFAULT;
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		stereo = SGTL5000_DAC_STEREO;
	अन्यथा
		stereo = SGTL5000_ADC_STEREO;

	/* set mono to save घातer */
	snd_soc_component_update_bits(component, SGTL5000_CHIP_ANA_POWER, stereo,
			channels == 1 ? 0 : stereo);

	/* set codec घड़ी base on lrclk */
	ret = sgtl5000_set_घड़ी(component, params_rate(params));
	अगर (ret)
		वापस ret;

	/* set i2s data क्रमmat */
	चयन (params_width(params)) अणु
	हाल 16:
		अगर (sgtl5000->fmt == SND_SOC_DAIFMT_RIGHT_J)
			वापस -EINVAL;
		i2s_ctl |= SGTL5000_I2S_DLEN_16 << SGTL5000_I2S_DLEN_SHIFT;
		i2s_ctl |= SGTL5000_I2S_SCLKFREQ_32FS <<
		    SGTL5000_I2S_SCLKFREQ_SHIFT;
		अवरोध;
	हाल 20:
		i2s_ctl |= SGTL5000_I2S_DLEN_20 << SGTL5000_I2S_DLEN_SHIFT;
		i2s_ctl |= SGTL5000_I2S_SCLKFREQ_64FS <<
		    SGTL5000_I2S_SCLKFREQ_SHIFT;
		अवरोध;
	हाल 24:
		i2s_ctl |= SGTL5000_I2S_DLEN_24 << SGTL5000_I2S_DLEN_SHIFT;
		i2s_ctl |= SGTL5000_I2S_SCLKFREQ_64FS <<
		    SGTL5000_I2S_SCLKFREQ_SHIFT;
		अवरोध;
	हाल 32:
		अगर (sgtl5000->fmt == SND_SOC_DAIFMT_RIGHT_J)
			वापस -EINVAL;
		i2s_ctl |= SGTL5000_I2S_DLEN_32 << SGTL5000_I2S_DLEN_SHIFT;
		i2s_ctl |= SGTL5000_I2S_SCLKFREQ_64FS <<
		    SGTL5000_I2S_SCLKFREQ_SHIFT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, SGTL5000_CHIP_I2S_CTRL,
			    SGTL5000_I2S_DLEN_MASK | SGTL5000_I2S_SCLKFREQ_MASK,
			    i2s_ctl);

	वापस 0;
पूर्ण

/*
 * set dac bias
 * common state changes:
 * startup:
 * off --> standby --> prepare --> on
 * standby --> prepare --> on
 *
 * stop:
 * on --> prepare --> standby
 */
अटल पूर्णांक sgtl5000_set_bias_level(काष्ठा snd_soc_component *component,
				   क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा sgtl5000_priv *sgtl = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
	हाल SND_SOC_BIAS_STANDBY:
		regcache_cache_only(sgtl->regmap, false);
		ret = regcache_sync(sgtl->regmap);
		अगर (ret) अणु
			regcache_cache_only(sgtl->regmap, true);
			वापस ret;
		पूर्ण

		snd_soc_component_update_bits(component, SGTL5000_CHIP_ANA_POWER,
				    SGTL5000_REFTOP_POWERUP,
				    SGTL5000_REFTOP_POWERUP);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		regcache_cache_only(sgtl->regmap, true);
		snd_soc_component_update_bits(component, SGTL5000_CHIP_ANA_POWER,
				    SGTL5000_REFTOP_POWERUP, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा SGTL5000_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
			SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE |\
			SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops sgtl5000_ops = अणु
	.hw_params = sgtl5000_pcm_hw_params,
	.mute_stream = sgtl5000_mute_stream,
	.set_fmt = sgtl5000_set_dai_fmt,
	.set_sysclk = sgtl5000_set_dai_sysclk,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver sgtl5000_dai = अणु
	.name = "sgtl5000",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		/*
		 * only support 8~48K + 96K,
		 * TODO modअगरy hw_param to support more
		 */
		.rates = SNDRV_PCM_RATE_8000_48000 | SNDRV_PCM_RATE_96000,
		.क्रमmats = SGTL5000_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000 | SNDRV_PCM_RATE_96000,
		.क्रमmats = SGTL5000_FORMATS,
	पूर्ण,
	.ops = &sgtl5000_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल bool sgtl5000_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SGTL5000_CHIP_ID:
	हाल SGTL5000_CHIP_ADCDAC_CTRL:
	हाल SGTL5000_CHIP_ANA_STATUS:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool sgtl5000_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SGTL5000_CHIP_ID:
	हाल SGTL5000_CHIP_DIG_POWER:
	हाल SGTL5000_CHIP_CLK_CTRL:
	हाल SGTL5000_CHIP_I2S_CTRL:
	हाल SGTL5000_CHIP_SSS_CTRL:
	हाल SGTL5000_CHIP_ADCDAC_CTRL:
	हाल SGTL5000_CHIP_DAC_VOL:
	हाल SGTL5000_CHIP_PAD_STRENGTH:
	हाल SGTL5000_CHIP_ANA_ADC_CTRL:
	हाल SGTL5000_CHIP_ANA_HP_CTRL:
	हाल SGTL5000_CHIP_ANA_CTRL:
	हाल SGTL5000_CHIP_LINREG_CTRL:
	हाल SGTL5000_CHIP_REF_CTRL:
	हाल SGTL5000_CHIP_MIC_CTRL:
	हाल SGTL5000_CHIP_LINE_OUT_CTRL:
	हाल SGTL5000_CHIP_LINE_OUT_VOL:
	हाल SGTL5000_CHIP_ANA_POWER:
	हाल SGTL5000_CHIP_PLL_CTRL:
	हाल SGTL5000_CHIP_CLK_TOP_CTRL:
	हाल SGTL5000_CHIP_ANA_STATUS:
	हाल SGTL5000_CHIP_SHORT_CTRL:
	हाल SGTL5000_CHIP_ANA_TEST2:
	हाल SGTL5000_DAP_CTRL:
	हाल SGTL5000_DAP_PEQ:
	हाल SGTL5000_DAP_BASS_ENHANCE:
	हाल SGTL5000_DAP_BASS_ENHANCE_CTRL:
	हाल SGTL5000_DAP_AUDIO_EQ:
	हाल SGTL5000_DAP_SURROUND:
	हाल SGTL5000_DAP_FLT_COEF_ACCESS:
	हाल SGTL5000_DAP_COEF_WR_B0_MSB:
	हाल SGTL5000_DAP_COEF_WR_B0_LSB:
	हाल SGTL5000_DAP_EQ_BASS_BAND0:
	हाल SGTL5000_DAP_EQ_BASS_BAND1:
	हाल SGTL5000_DAP_EQ_BASS_BAND2:
	हाल SGTL5000_DAP_EQ_BASS_BAND3:
	हाल SGTL5000_DAP_EQ_BASS_BAND4:
	हाल SGTL5000_DAP_MAIN_CHAN:
	हाल SGTL5000_DAP_MIX_CHAN:
	हाल SGTL5000_DAP_AVC_CTRL:
	हाल SGTL5000_DAP_AVC_THRESHOLD:
	हाल SGTL5000_DAP_AVC_ATTACK:
	हाल SGTL5000_DAP_AVC_DECAY:
	हाल SGTL5000_DAP_COEF_WR_B1_MSB:
	हाल SGTL5000_DAP_COEF_WR_B1_LSB:
	हाल SGTL5000_DAP_COEF_WR_B2_MSB:
	हाल SGTL5000_DAP_COEF_WR_B2_LSB:
	हाल SGTL5000_DAP_COEF_WR_A1_MSB:
	हाल SGTL5000_DAP_COEF_WR_A1_LSB:
	हाल SGTL5000_DAP_COEF_WR_A2_MSB:
	हाल SGTL5000_DAP_COEF_WR_A2_LSB:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * This precalculated table contains all (vag_val * 100 / lo_calcntrl) results
 * to select an appropriate lo_vol_* in SGTL5000_CHIP_LINE_OUT_VOL
 * The calculatation was करोne क्रम all possible रेजिस्टर values which
 * is the array index and the following क्रमmula: 10^((idxै15)/40) * 100
 */
अटल स्थिर u8 vol_quot_table[] = अणु
	42, 45, 47, 50, 53, 56, 60, 63,
	67, 71, 75, 79, 84, 89, 94, 100,
	106, 112, 119, 126, 133, 141, 150, 158,
	168, 178, 188, 200, 211, 224, 237, 251
पूर्ण;

/*
 * sgtl5000 has 3 पूर्णांकernal घातer supplies:
 * 1. VAG, normally set to vdda/2
 * 2. अक्षरge pump, set to dअगरferent value
 *	according to voltage of vdda and vddio
 * 3. line out VAG, normally set to vddio/2
 *
 * and should be set according to:
 * 1. vddd provided by बाह्यal or not
 * 2. vdda and vddio voltage value. > 3.1v or not
 */
अटल पूर्णांक sgtl5000_set_घातer_regs(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक vddd;
	पूर्णांक vdda;
	पूर्णांक vddio;
	u16 ana_pwr;
	u16 lreg_ctrl;
	पूर्णांक vag;
	पूर्णांक lo_vag;
	पूर्णांक vol_quot;
	पूर्णांक lo_vol;
	माप_प्रकार i;
	काष्ठा sgtl5000_priv *sgtl5000 = snd_soc_component_get_drvdata(component);

	vdda  = regulator_get_voltage(sgtl5000->supplies[VDDA].consumer);
	vddio = regulator_get_voltage(sgtl5000->supplies[VDDIO].consumer);
	vddd  = (sgtl5000->num_supplies > VDDD)
		? regulator_get_voltage(sgtl5000->supplies[VDDD].consumer)
		: LDO_VOLTAGE;

	vdda  = vdda / 1000;
	vddio = vddio / 1000;
	vddd  = vddd / 1000;

	अगर (vdda <= 0 || vddio <= 0 || vddd < 0) अणु
		dev_err(component->dev, "regulator voltage not set correctly\n");

		वापस -EINVAL;
	पूर्ण

	/* according to datasheet, maximum voltage of supplies */
	अगर (vdda > 3600 || vddio > 3600 || vddd > 1980) अणु
		dev_err(component->dev,
			"exceed max voltage vdda %dmV vddio %dmV vddd %dmV\n",
			vdda, vddio, vddd);

		वापस -EINVAL;
	पूर्ण

	/* reset value */
	ana_pwr = snd_soc_component_पढ़ो(component, SGTL5000_CHIP_ANA_POWER);
	ana_pwr |= SGTL5000_DAC_STEREO |
			SGTL5000_ADC_STEREO |
			SGTL5000_REFTOP_POWERUP;
	lreg_ctrl = snd_soc_component_पढ़ो(component, SGTL5000_CHIP_LINREG_CTRL);

	अगर (vddio < 3100 && vdda < 3100) अणु
		/* enable पूर्णांकernal oscillator used क्रम अक्षरge pump */
		snd_soc_component_update_bits(component, SGTL5000_CHIP_CLK_TOP_CTRL,
					SGTL5000_INT_OSC_EN,
					SGTL5000_INT_OSC_EN);
		/* Enable VDDC अक्षरge pump */
		ana_pwr |= SGTL5000_VDDC_CHRGPMP_POWERUP;
	पूर्ण अन्यथा अणु
		ana_pwr &= ~SGTL5000_VDDC_CHRGPMP_POWERUP;
		/*
		 * अगर vddio == vdda the source of अक्षरge pump should be
		 * asचिन्हित manually to VDDIO
		 */
		अगर (regulator_is_equal(sgtl5000->supplies[VDDA].consumer,
				       sgtl5000->supplies[VDDIO].consumer)) अणु
			lreg_ctrl |= SGTL5000_VDDC_ASSN_OVRD;
			lreg_ctrl |= SGTL5000_VDDC_MAN_ASSN_VDDIO <<
				    SGTL5000_VDDC_MAN_ASSN_SHIFT;
		पूर्ण
	पूर्ण

	snd_soc_component_ग_लिखो(component, SGTL5000_CHIP_LINREG_CTRL, lreg_ctrl);

	snd_soc_component_ग_लिखो(component, SGTL5000_CHIP_ANA_POWER, ana_pwr);

	/*
	 * set ADC/DAC VAG to vdda / 2,
	 * should stay in range (0.8v, 1.575v)
	 */
	vag = vdda / 2;
	अगर (vag <= SGTL5000_ANA_GND_BASE)
		vag = 0;
	अन्यथा अगर (vag >= SGTL5000_ANA_GND_BASE + SGTL5000_ANA_GND_STP *
		 (SGTL5000_ANA_GND_MASK >> SGTL5000_ANA_GND_SHIFT))
		vag = SGTL5000_ANA_GND_MASK >> SGTL5000_ANA_GND_SHIFT;
	अन्यथा
		vag = (vag - SGTL5000_ANA_GND_BASE) / SGTL5000_ANA_GND_STP;

	snd_soc_component_update_bits(component, SGTL5000_CHIP_REF_CTRL,
			SGTL5000_ANA_GND_MASK, vag << SGTL5000_ANA_GND_SHIFT);

	/* set line out VAG to vddio / 2, in range (0.8v, 1.675v) */
	lo_vag = vddio / 2;
	अगर (lo_vag <= SGTL5000_LINE_OUT_GND_BASE)
		lo_vag = 0;
	अन्यथा अगर (lo_vag >= SGTL5000_LINE_OUT_GND_BASE +
		SGTL5000_LINE_OUT_GND_STP * SGTL5000_LINE_OUT_GND_MAX)
		lo_vag = SGTL5000_LINE_OUT_GND_MAX;
	अन्यथा
		lo_vag = (lo_vag - SGTL5000_LINE_OUT_GND_BASE) /
		    SGTL5000_LINE_OUT_GND_STP;

	snd_soc_component_update_bits(component, SGTL5000_CHIP_LINE_OUT_CTRL,
			SGTL5000_LINE_OUT_CURRENT_MASK |
			SGTL5000_LINE_OUT_GND_MASK,
			lo_vag << SGTL5000_LINE_OUT_GND_SHIFT |
			SGTL5000_LINE_OUT_CURRENT_360u <<
				SGTL5000_LINE_OUT_CURRENT_SHIFT);

	/*
	 * Set lineout output level in range (0..31)
	 * the same value is used क्रम right and left channel
	 *
	 * Searching क्रम a suitable index solving this क्रमmula:
	 * idx = 40 * log10(vag_val / lo_cagcntrl) + 15
	 */
	vol_quot = lo_vag ? (vag * 100) / lo_vag : 0;
	lo_vol = 0;
	क्रम (i = 0; i < ARRAY_SIZE(vol_quot_table); i++) अणु
		अगर (vol_quot >= vol_quot_table[i])
			lo_vol = i;
		अन्यथा
			अवरोध;
	पूर्ण

	snd_soc_component_update_bits(component, SGTL5000_CHIP_LINE_OUT_VOL,
		SGTL5000_LINE_OUT_VOL_RIGHT_MASK |
		SGTL5000_LINE_OUT_VOL_LEFT_MASK,
		lo_vol << SGTL5000_LINE_OUT_VOL_RIGHT_SHIFT |
		lo_vol << SGTL5000_LINE_OUT_VOL_LEFT_SHIFT);

	वापस 0;
पूर्ण

अटल पूर्णांक sgtl5000_enable_regulators(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक बाह्यal_vddd = 0;
	काष्ठा regulator *vddd;
	काष्ठा sgtl5000_priv *sgtl5000 = i2c_get_clientdata(client);

	क्रम (i = 0; i < ARRAY_SIZE(sgtl5000->supplies); i++)
		sgtl5000->supplies[i].supply = supply_names[i];

	vddd = regulator_get_optional(&client->dev, "VDDD");
	अगर (IS_ERR(vddd)) अणु
		/* See अगर it's just not रेजिस्टरed yet */
		अगर (PTR_ERR(vddd) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
	पूर्ण अन्यथा अणु
		बाह्यal_vddd = 1;
		regulator_put(vddd);
	पूर्ण

	sgtl5000->num_supplies = ARRAY_SIZE(sgtl5000->supplies)
				 - 1 + बाह्यal_vddd;
	ret = regulator_bulk_get(&client->dev, sgtl5000->num_supplies,
				 sgtl5000->supplies);
	अगर (ret)
		वापस ret;

	ret = regulator_bulk_enable(sgtl5000->num_supplies,
				    sgtl5000->supplies);
	अगर (!ret)
		usleep_range(10, 20);
	अन्यथा
		regulator_bulk_मुक्त(sgtl5000->num_supplies,
				    sgtl5000->supplies);

	वापस ret;
पूर्ण

अटल पूर्णांक sgtl5000_probe(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret;
	u16 reg;
	काष्ठा sgtl5000_priv *sgtl5000 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक zcd_mask = SGTL5000_HP_ZCD_EN | SGTL5000_ADC_ZCD_EN;

	/* घातer up sgtl5000 */
	ret = sgtl5000_set_घातer_regs(component);
	अगर (ret)
		जाओ err;

	/* enable small pop, पूर्णांकroduce 400ms delay in turning off */
	snd_soc_component_update_bits(component, SGTL5000_CHIP_REF_CTRL,
				SGTL5000_SMALL_POP, SGTL5000_SMALL_POP);

	/* disable लघु cut detector */
	snd_soc_component_ग_लिखो(component, SGTL5000_CHIP_SHORT_CTRL, 0);

	snd_soc_component_ग_लिखो(component, SGTL5000_CHIP_DIG_POWER,
			SGTL5000_ADC_EN | SGTL5000_DAC_EN);

	/* enable dac volume ramp by शेष */
	snd_soc_component_ग_लिखो(component, SGTL5000_CHIP_ADCDAC_CTRL,
			SGTL5000_DAC_VOL_RAMP_EN |
			SGTL5000_DAC_MUTE_RIGHT |
			SGTL5000_DAC_MUTE_LEFT);

	reg = ((sgtl5000->lrclk_strength) << SGTL5000_PAD_I2S_LRCLK_SHIFT |
	       (sgtl5000->sclk_strength) << SGTL5000_PAD_I2S_SCLK_SHIFT |
	       0x1f);
	snd_soc_component_ग_लिखो(component, SGTL5000_CHIP_PAD_STRENGTH, reg);

	snd_soc_component_update_bits(component, SGTL5000_CHIP_ANA_CTRL,
		zcd_mask, zcd_mask);

	snd_soc_component_update_bits(component, SGTL5000_CHIP_MIC_CTRL,
			SGTL5000_BIAS_R_MASK,
			sgtl5000->micbias_resistor << SGTL5000_BIAS_R_SHIFT);

	snd_soc_component_update_bits(component, SGTL5000_CHIP_MIC_CTRL,
			SGTL5000_BIAS_VOLT_MASK,
			sgtl5000->micbias_voltage << SGTL5000_BIAS_VOLT_SHIFT);
	/*
	 * enable DAP Graphic EQ
	 * TODO:
	 * Add control क्रम changing between PEQ/Tone Control/GEQ
	 */
	snd_soc_component_ग_लिखो(component, SGTL5000_DAP_AUDIO_EQ, SGTL5000_DAP_SEL_GEQ);

	/* Unmute DAC after start */
	snd_soc_component_update_bits(component, SGTL5000_CHIP_ADCDAC_CTRL,
		SGTL5000_DAC_MUTE_LEFT | SGTL5000_DAC_MUTE_RIGHT, 0);

	वापस 0;

err:
	वापस ret;
पूर्ण

अटल पूर्णांक sgtl5000_of_xlate_dai_id(काष्ठा snd_soc_component *component,
				    काष्ठा device_node *endpoपूर्णांक)
अणु
	/* वापस dai id 0, whatever the endpoपूर्णांक index */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver sgtl5000_driver = अणु
	.probe			= sgtl5000_probe,
	.set_bias_level		= sgtl5000_set_bias_level,
	.controls		= sgtl5000_snd_controls,
	.num_controls		= ARRAY_SIZE(sgtl5000_snd_controls),
	.dapm_widमाला_लो		= sgtl5000_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(sgtl5000_dapm_widमाला_लो),
	.dapm_routes		= sgtl5000_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(sgtl5000_dapm_routes),
	.of_xlate_dai_id	= sgtl5000_of_xlate_dai_id,
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sgtl5000_regmap = अणु
	.reg_bits = 16,
	.val_bits = 16,
	.reg_stride = 2,

	.max_रेजिस्टर = SGTL5000_MAX_REG_OFFSET,
	.अस्थिर_reg = sgtl5000_अस्थिर,
	.पढ़ोable_reg = sgtl5000_पढ़ोable,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = sgtl5000_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(sgtl5000_reg_शेषs),
पूर्ण;

/*
 * Write all the शेष values from sgtl5000_reg_शेषs[] array पूर्णांकo the
 * sgtl5000 रेजिस्टरs, to make sure we always start with the sane रेजिस्टरs
 * values as stated in the datasheet.
 *
 * Since sgtl5000 करोes not have a reset line, nor a reset command in software,
 * we follow this approach to guarantee we always start from the शेष values
 * and aव्योम problems like, not being able to probe after an audio playback
 * followed by a प्रणाली reset or a 'reboot' command in Linux
 */
अटल व्योम sgtl5000_fill_शेषs(काष्ठा i2c_client *client)
अणु
	काष्ठा sgtl5000_priv *sgtl5000 = i2c_get_clientdata(client);
	पूर्णांक i, ret, val, index;

	क्रम (i = 0; i < ARRAY_SIZE(sgtl5000_reg_शेषs); i++) अणु
		val = sgtl5000_reg_शेषs[i].def;
		index = sgtl5000_reg_शेषs[i].reg;
		ret = regmap_ग_लिखो(sgtl5000->regmap, index, val);
		अगर (ret)
			dev_err(&client->dev,
				"%s: error %d setting reg 0x%02x to 0x%04x\n",
				__func__, ret, index, val);
	पूर्ण
पूर्ण

अटल पूर्णांक sgtl5000_i2c_probe(काष्ठा i2c_client *client,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा sgtl5000_priv *sgtl5000;
	पूर्णांक ret, reg, rev;
	काष्ठा device_node *np = client->dev.of_node;
	u32 value;
	u16 ana_pwr;

	sgtl5000 = devm_kzalloc(&client->dev, माप(*sgtl5000), GFP_KERNEL);
	अगर (!sgtl5000)
		वापस -ENOMEM;

	i2c_set_clientdata(client, sgtl5000);

	ret = sgtl5000_enable_regulators(client);
	अगर (ret)
		वापस ret;

	sgtl5000->regmap = devm_regmap_init_i2c(client, &sgtl5000_regmap);
	अगर (IS_ERR(sgtl5000->regmap)) अणु
		ret = PTR_ERR(sgtl5000->regmap);
		dev_err(&client->dev, "Failed to allocate regmap: %d\n", ret);
		जाओ disable_regs;
	पूर्ण

	sgtl5000->mclk = devm_clk_get(&client->dev, शून्य);
	अगर (IS_ERR(sgtl5000->mclk)) अणु
		ret = PTR_ERR(sgtl5000->mclk);
		/* Defer the probe to see अगर the clk will be provided later */
		अगर (ret == -ENOENT)
			ret = -EPROBE_DEFER;

		अगर (ret != -EPROBE_DEFER)
			dev_err(&client->dev, "Failed to get mclock: %d\n",
				ret);
		जाओ disable_regs;
	पूर्ण

	ret = clk_prepare_enable(sgtl5000->mclk);
	अगर (ret) अणु
		dev_err(&client->dev, "Error enabling clock %d\n", ret);
		जाओ disable_regs;
	पूर्ण

	/* Need 8 घड़ीs beक्रमe I2C accesses */
	udelay(1);

	/* पढ़ो chip inक्रमmation */
	ret = regmap_पढ़ो(sgtl5000->regmap, SGTL5000_CHIP_ID, &reg);
	अगर (ret) अणु
		dev_err(&client->dev, "Error reading chip id %d\n", ret);
		जाओ disable_clk;
	पूर्ण

	अगर (((reg & SGTL5000_PARTID_MASK) >> SGTL5000_PARTID_SHIFT) !=
	    SGTL5000_PARTID_PART_ID) अणु
		dev_err(&client->dev,
			"Device with ID register %x is not a sgtl5000\n", reg);
		ret = -ENODEV;
		जाओ disable_clk;
	पूर्ण

	rev = (reg & SGTL5000_REVID_MASK) >> SGTL5000_REVID_SHIFT;
	dev_info(&client->dev, "sgtl5000 revision 0x%x\n", rev);
	sgtl5000->revision = rev;

	/* reconfigure the घड़ीs in हाल we're using the PLL */
	ret = regmap_ग_लिखो(sgtl5000->regmap,
			   SGTL5000_CHIP_CLK_CTRL,
			   SGTL5000_CHIP_CLK_CTRL_DEFAULT);
	अगर (ret)
		dev_err(&client->dev,
			"Error %d initializing CHIP_CLK_CTRL\n", ret);

	/* Mute everything to aव्योम pop from the following घातer-up */
	ret = regmap_ग_लिखो(sgtl5000->regmap, SGTL5000_CHIP_ANA_CTRL,
			   SGTL5000_CHIP_ANA_CTRL_DEFAULT);
	अगर (ret) अणु
		dev_err(&client->dev,
			"Error %d muting outputs via CHIP_ANA_CTRL\n", ret);
		जाओ disable_clk;
	पूर्ण

	/*
	 * If VAG is घातered-on (e.g. from previous boot), it would be disabled
	 * by the ग_लिखो to ANA_POWER in later steps of the probe code. This
	 * may create a loud pop even with all outमाला_दो muted. The proper way
	 * to circumvent this is disabling the bit first and रुकोing the proper
	 * cool-करोwn समय.
	 */
	ret = regmap_पढ़ो(sgtl5000->regmap, SGTL5000_CHIP_ANA_POWER, &value);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to read ANA_POWER: %d\n", ret);
		जाओ disable_clk;
	पूर्ण
	अगर (value & SGTL5000_VAG_POWERUP) अणु
		ret = regmap_update_bits(sgtl5000->regmap,
					 SGTL5000_CHIP_ANA_POWER,
					 SGTL5000_VAG_POWERUP,
					 0);
		अगर (ret) अणु
			dev_err(&client->dev, "Error %d disabling VAG\n", ret);
			जाओ disable_clk;
		पूर्ण

		msleep(SGTL5000_VAG_POWERDOWN_DELAY);
	पूर्ण

	/* Follow section 2.2.1.1 of AN3663 */
	ana_pwr = SGTL5000_ANA_POWER_DEFAULT;
	अगर (sgtl5000->num_supplies <= VDDD) अणु
		/* पूर्णांकernal VDDD at 1.2V */
		ret = regmap_update_bits(sgtl5000->regmap,
					 SGTL5000_CHIP_LINREG_CTRL,
					 SGTL5000_LINREG_VDDD_MASK,
					 LINREG_VDDD);
		अगर (ret)
			dev_err(&client->dev,
				"Error %d setting LINREG_VDDD\n", ret);

		ana_pwr |= SGTL5000_LINEREG_D_POWERUP;
		dev_info(&client->dev,
			 "Using internal LDO instead of VDDD: check ER1 erratum\n");
	पूर्ण अन्यथा अणु
		/* using बाह्यal LDO क्रम VDDD
		 * Clear startup घातerup and simple घातerup
		 * bits to save घातer
		 */
		ana_pwr &= ~(SGTL5000_STARTUP_POWERUP
			     | SGTL5000_LINREG_SIMPLE_POWERUP);
		dev_dbg(&client->dev, "Using external VDDD\n");
	पूर्ण
	ret = regmap_ग_लिखो(sgtl5000->regmap, SGTL5000_CHIP_ANA_POWER, ana_pwr);
	अगर (ret)
		dev_err(&client->dev,
			"Error %d setting CHIP_ANA_POWER to %04x\n",
			ret, ana_pwr);

	अगर (np) अणु
		अगर (!of_property_पढ़ो_u32(np,
			"micbias-resistor-k-ohms", &value)) अणु
			चयन (value) अणु
			हाल SGTL5000_MICBIAS_OFF:
				sgtl5000->micbias_resistor = 0;
				अवरोध;
			हाल SGTL5000_MICBIAS_2K:
				sgtl5000->micbias_resistor = 1;
				अवरोध;
			हाल SGTL5000_MICBIAS_4K:
				sgtl5000->micbias_resistor = 2;
				अवरोध;
			हाल SGTL5000_MICBIAS_8K:
				sgtl5000->micbias_resistor = 3;
				अवरोध;
			शेष:
				sgtl5000->micbias_resistor = 2;
				dev_err(&client->dev,
					"Unsuitable MicBias resistor\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			/* शेष is 4Kohms */
			sgtl5000->micbias_resistor = 2;
		पूर्ण
		अगर (!of_property_पढ़ो_u32(np,
			"micbias-voltage-m-volts", &value)) अणु
			/* 1250mV => 0 */
			/* steps of 250mV */
			अगर ((value >= 1250) && (value <= 3000))
				sgtl5000->micbias_voltage = (value / 250) - 5;
			अन्यथा अणु
				sgtl5000->micbias_voltage = 0;
				dev_err(&client->dev,
					"Unsuitable MicBias voltage\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			sgtl5000->micbias_voltage = 0;
		पूर्ण
	पूर्ण

	sgtl5000->lrclk_strength = I2S_LRCLK_STRENGTH_LOW;
	अगर (!of_property_पढ़ो_u32(np, "lrclk-strength", &value)) अणु
		अगर (value > I2S_LRCLK_STRENGTH_HIGH)
			value = I2S_LRCLK_STRENGTH_LOW;
		sgtl5000->lrclk_strength = value;
	पूर्ण

	sgtl5000->sclk_strength = I2S_SCLK_STRENGTH_LOW;
	अगर (!of_property_पढ़ो_u32(np, "sclk-strength", &value)) अणु
		अगर (value > I2S_SCLK_STRENGTH_HIGH)
			value = I2S_SCLK_STRENGTH_LOW;
		sgtl5000->sclk_strength = value;
	पूर्ण

	/* Ensure sgtl5000 will start with sane रेजिस्टर values */
	sgtl5000_fill_शेषs(client);

	ret = devm_snd_soc_रेजिस्टर_component(&client->dev,
			&sgtl5000_driver, &sgtl5000_dai, 1);
	अगर (ret)
		जाओ disable_clk;

	वापस 0;

disable_clk:
	clk_disable_unprepare(sgtl5000->mclk);

disable_regs:
	regulator_bulk_disable(sgtl5000->num_supplies, sgtl5000->supplies);
	regulator_bulk_मुक्त(sgtl5000->num_supplies, sgtl5000->supplies);

	वापस ret;
पूर्ण

अटल पूर्णांक sgtl5000_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा sgtl5000_priv *sgtl5000 = i2c_get_clientdata(client);

	clk_disable_unprepare(sgtl5000->mclk);
	regulator_bulk_disable(sgtl5000->num_supplies, sgtl5000->supplies);
	regulator_bulk_मुक्त(sgtl5000->num_supplies, sgtl5000->supplies);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id sgtl5000_id[] = अणु
	अणु"sgtl5000", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, sgtl5000_id);

अटल स्थिर काष्ठा of_device_id sgtl5000_dt_ids[] = अणु
	अणु .compatible = "fsl,sgtl5000", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sgtl5000_dt_ids);

अटल काष्ठा i2c_driver sgtl5000_i2c_driver = अणु
	.driver = अणु
		.name = "sgtl5000",
		.of_match_table = sgtl5000_dt_ids,
	पूर्ण,
	.probe = sgtl5000_i2c_probe,
	.हटाओ = sgtl5000_i2c_हटाओ,
	.id_table = sgtl5000_id,
पूर्ण;

module_i2c_driver(sgtl5000_i2c_driver);

MODULE_DESCRIPTION("Freescale SGTL5000 ALSA SoC Codec Driver");
MODULE_AUTHOR("Zeng Zhaoming <zengzm.kernel@gmail.com>");
MODULE_LICENSE("GPL");
