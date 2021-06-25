<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8903.c  --  WM8903 ALSA SoC Audio driver
 *
 * Copyright 2008-12 Wolfson Microelectronics
 * Copyright 2011-2012 NVIDIA, Inc.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 *
 * TODO:
 *  - TDM mode configuration.
 *  - Digital microphone support.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>
#समावेश <linux/mutex.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/wm8903.h>
#समावेश <trace/events/asoc.h>

#समावेश "wm8903.h"

/* Register शेषs at reset */
अटल स्थिर काष्ठा reg_शेष wm8903_reg_शेषs[] = अणु
	अणु 4,  0x0018 पूर्ण,     /* R4   - Bias Control 0 */
	अणु 5,  0x0000 पूर्ण,     /* R5   - VMID Control 0 */
	अणु 6,  0x0000 पूर्ण,     /* R6   - Mic Bias Control 0 */
	अणु 8,  0x0001 पूर्ण,     /* R8   - Analogue DAC 0 */
	अणु 10, 0x0001 पूर्ण,     /* R10  - Analogue ADC 0 */
	अणु 12, 0x0000 पूर्ण,     /* R12  - Power Management 0 */
	अणु 13, 0x0000 पूर्ण,     /* R13  - Power Management 1 */
	अणु 14, 0x0000 पूर्ण,     /* R14  - Power Management 2 */
	अणु 15, 0x0000 पूर्ण,     /* R15  - Power Management 3 */
	अणु 16, 0x0000 पूर्ण,     /* R16  - Power Management 4 */
	अणु 17, 0x0000 पूर्ण,     /* R17  - Power Management 5 */
	अणु 18, 0x0000 पूर्ण,     /* R18  - Power Management 6 */
	अणु 20, 0x0400 पूर्ण,     /* R20  - Clock Rates 0 */
	अणु 21, 0x0D07 पूर्ण,     /* R21  - Clock Rates 1 */
	अणु 22, 0x0000 पूर्ण,     /* R22  - Clock Rates 2 */
	अणु 24, 0x0050 पूर्ण,     /* R24  - Audio Interface 0 */
	अणु 25, 0x0242 पूर्ण,     /* R25  - Audio Interface 1 */
	अणु 26, 0x0008 पूर्ण,     /* R26  - Audio Interface 2 */
	अणु 27, 0x0022 पूर्ण,     /* R27  - Audio Interface 3 */
	अणु 30, 0x00C0 पूर्ण,     /* R30  - DAC Digital Volume Left */
	अणु 31, 0x00C0 पूर्ण,     /* R31  - DAC Digital Volume Right */
	अणु 32, 0x0000 पूर्ण,     /* R32  - DAC Digital 0 */
	अणु 33, 0x0000 पूर्ण,     /* R33  - DAC Digital 1 */
	अणु 36, 0x00C0 पूर्ण,     /* R36  - ADC Digital Volume Left */
	अणु 37, 0x00C0 पूर्ण,     /* R37  - ADC Digital Volume Right */
	अणु 38, 0x0000 पूर्ण,     /* R38  - ADC Digital 0 */
	अणु 39, 0x0073 पूर्ण,     /* R39  - Digital Microphone 0 */
	अणु 40, 0x09BF पूर्ण,     /* R40  - DRC 0 */
	अणु 41, 0x3241 पूर्ण,     /* R41  - DRC 1 */
	अणु 42, 0x0020 पूर्ण,     /* R42  - DRC 2 */
	अणु 43, 0x0000 पूर्ण,     /* R43  - DRC 3 */
	अणु 44, 0x0085 पूर्ण,     /* R44  - Analogue Left Input 0 */
	अणु 45, 0x0085 पूर्ण,     /* R45  - Analogue Right Input 0 */
	अणु 46, 0x0044 पूर्ण,     /* R46  - Analogue Left Input 1 */
	अणु 47, 0x0044 पूर्ण,     /* R47  - Analogue Right Input 1 */
	अणु 50, 0x0008 पूर्ण,     /* R50  - Analogue Left Mix 0 */
	अणु 51, 0x0004 पूर्ण,     /* R51  - Analogue Right Mix 0 */
	अणु 52, 0x0000 पूर्ण,     /* R52  - Analogue Spk Mix Left 0 */
	अणु 53, 0x0000 पूर्ण,     /* R53  - Analogue Spk Mix Left 1 */
	अणु 54, 0x0000 पूर्ण,     /* R54  - Analogue Spk Mix Right 0 */
	अणु 55, 0x0000 पूर्ण,     /* R55  - Analogue Spk Mix Right 1 */
	अणु 57, 0x002D पूर्ण,     /* R57  - Analogue OUT1 Left */
	अणु 58, 0x002D पूर्ण,     /* R58  - Analogue OUT1 Right */
	अणु 59, 0x0039 पूर्ण,     /* R59  - Analogue OUT2 Left */
	अणु 60, 0x0039 पूर्ण,     /* R60  - Analogue OUT2 Right */
	अणु 62, 0x0139 पूर्ण,     /* R62  - Analogue OUT3 Left */
	अणु 63, 0x0139 पूर्ण,     /* R63  - Analogue OUT3 Right */
	अणु 64, 0x0000 पूर्ण,     /* R65  - Analogue SPK Output Control 0 */
	अणु 67, 0x0010 पूर्ण,     /* R67  - DC Servo 0 */
	अणु 69, 0x00A4 पूर्ण,     /* R69  - DC Servo 2 */
	अणु 90, 0x0000 पूर्ण,     /* R90  - Analogue HP 0 */
	अणु 94, 0x0000 पूर्ण,     /* R94  - Analogue Lineout 0 */
	अणु 98, 0x0000 पूर्ण,     /* R98  - Charge Pump 0 */
	अणु 104, 0x0000 पूर्ण,    /* R104 - Class W 0 */
	अणु 108, 0x0000 पूर्ण,    /* R108 - Write Sequencer 0 */
	अणु 109, 0x0000 पूर्ण,    /* R109 - Write Sequencer 1 */
	अणु 110, 0x0000 पूर्ण,    /* R110 - Write Sequencer 2 */
	अणु 111, 0x0000 पूर्ण,    /* R111 - Write Sequencer 3 */
	अणु 112, 0x0000 पूर्ण,    /* R112 - Write Sequencer 4 */
	अणु 114, 0x0000 पूर्ण,    /* R114 - Control Interface */
	अणु 116, 0x00A8 पूर्ण,    /* R116 - GPIO Control 1 */
	अणु 117, 0x00A8 पूर्ण,    /* R117 - GPIO Control 2 */
	अणु 118, 0x00A8 पूर्ण,    /* R118 - GPIO Control 3 */
	अणु 119, 0x0220 पूर्ण,    /* R119 - GPIO Control 4 */
	अणु 120, 0x01A0 पूर्ण,    /* R120 - GPIO Control 5 */
	अणु 122, 0xFFFF पूर्ण,    /* R122 - Interrupt Status 1 Mask */
	अणु 123, 0x0000 पूर्ण,    /* R123 - Interrupt Polarity 1 */
	अणु 126, 0x0000 पूर्ण,    /* R126 - Interrupt Control */
	अणु 129, 0x0000 पूर्ण,    /* R129 - Control Interface Test 1 */
	अणु 149, 0x6810 पूर्ण,    /* R149 - Charge Pump Test 1 */
	अणु 164, 0x0028 पूर्ण,    /* R164 - Clock Rate Test 4 */
	अणु 172, 0x0000 पूर्ण,    /* R172 - Analogue Output Bias 0 */
पूर्ण;

#घोषणा WM8903_NUM_SUPPLIES 4
अटल स्थिर अक्षर *wm8903_supply_names[WM8903_NUM_SUPPLIES] = अणु
	"AVDD",
	"CPVDD",
	"DBVDD",
	"DCVDD",
पूर्ण;

काष्ठा wm8903_priv अणु
	काष्ठा wm8903_platक्रमm_data *pdata;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data supplies[WM8903_NUM_SUPPLIES];

	पूर्णांक sysclk;
	पूर्णांक irq;

	काष्ठा mutex lock;
	पूर्णांक fs;
	पूर्णांक deemph;

	पूर्णांक dcs_pending;
	पूर्णांक dcs_cache[4];

	/* Reference count */
	पूर्णांक class_w_users;

	काष्ठा snd_soc_jack *mic_jack;
	पूर्णांक mic_det;
	पूर्णांक mic_लघु;
	पूर्णांक mic_last_report;
	पूर्णांक mic_delay;

#अगर_घोषित CONFIG_GPIOLIB
	काष्ठा gpio_chip gpio_chip;
#पूर्ण_अगर
पूर्ण;

अटल bool wm8903_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8903_SW_RESET_AND_ID:
	हाल WM8903_REVISION_NUMBER:
	हाल WM8903_BIAS_CONTROL_0:
	हाल WM8903_VMID_CONTROL_0:
	हाल WM8903_MIC_BIAS_CONTROL_0:
	हाल WM8903_ANALOGUE_DAC_0:
	हाल WM8903_ANALOGUE_ADC_0:
	हाल WM8903_POWER_MANAGEMENT_0:
	हाल WM8903_POWER_MANAGEMENT_1:
	हाल WM8903_POWER_MANAGEMENT_2:
	हाल WM8903_POWER_MANAGEMENT_3:
	हाल WM8903_POWER_MANAGEMENT_4:
	हाल WM8903_POWER_MANAGEMENT_5:
	हाल WM8903_POWER_MANAGEMENT_6:
	हाल WM8903_CLOCK_RATES_0:
	हाल WM8903_CLOCK_RATES_1:
	हाल WM8903_CLOCK_RATES_2:
	हाल WM8903_AUDIO_INTERFACE_0:
	हाल WM8903_AUDIO_INTERFACE_1:
	हाल WM8903_AUDIO_INTERFACE_2:
	हाल WM8903_AUDIO_INTERFACE_3:
	हाल WM8903_DAC_DIGITAL_VOLUME_LEFT:
	हाल WM8903_DAC_DIGITAL_VOLUME_RIGHT:
	हाल WM8903_DAC_DIGITAL_0:
	हाल WM8903_DAC_DIGITAL_1:
	हाल WM8903_ADC_DIGITAL_VOLUME_LEFT:
	हाल WM8903_ADC_DIGITAL_VOLUME_RIGHT:
	हाल WM8903_ADC_DIGITAL_0:
	हाल WM8903_DIGITAL_MICROPHONE_0:
	हाल WM8903_DRC_0:
	हाल WM8903_DRC_1:
	हाल WM8903_DRC_2:
	हाल WM8903_DRC_3:
	हाल WM8903_ANALOGUE_LEFT_INPUT_0:
	हाल WM8903_ANALOGUE_RIGHT_INPUT_0:
	हाल WM8903_ANALOGUE_LEFT_INPUT_1:
	हाल WM8903_ANALOGUE_RIGHT_INPUT_1:
	हाल WM8903_ANALOGUE_LEFT_MIX_0:
	हाल WM8903_ANALOGUE_RIGHT_MIX_0:
	हाल WM8903_ANALOGUE_SPK_MIX_LEFT_0:
	हाल WM8903_ANALOGUE_SPK_MIX_LEFT_1:
	हाल WM8903_ANALOGUE_SPK_MIX_RIGHT_0:
	हाल WM8903_ANALOGUE_SPK_MIX_RIGHT_1:
	हाल WM8903_ANALOGUE_OUT1_LEFT:
	हाल WM8903_ANALOGUE_OUT1_RIGHT:
	हाल WM8903_ANALOGUE_OUT2_LEFT:
	हाल WM8903_ANALOGUE_OUT2_RIGHT:
	हाल WM8903_ANALOGUE_OUT3_LEFT:
	हाल WM8903_ANALOGUE_OUT3_RIGHT:
	हाल WM8903_ANALOGUE_SPK_OUTPUT_CONTROL_0:
	हाल WM8903_DC_SERVO_0:
	हाल WM8903_DC_SERVO_2:
	हाल WM8903_DC_SERVO_READBACK_1:
	हाल WM8903_DC_SERVO_READBACK_2:
	हाल WM8903_DC_SERVO_READBACK_3:
	हाल WM8903_DC_SERVO_READBACK_4:
	हाल WM8903_ANALOGUE_HP_0:
	हाल WM8903_ANALOGUE_LINEOUT_0:
	हाल WM8903_CHARGE_PUMP_0:
	हाल WM8903_CLASS_W_0:
	हाल WM8903_WRITE_SEQUENCER_0:
	हाल WM8903_WRITE_SEQUENCER_1:
	हाल WM8903_WRITE_SEQUENCER_2:
	हाल WM8903_WRITE_SEQUENCER_3:
	हाल WM8903_WRITE_SEQUENCER_4:
	हाल WM8903_CONTROL_INTERFACE:
	हाल WM8903_GPIO_CONTROL_1:
	हाल WM8903_GPIO_CONTROL_2:
	हाल WM8903_GPIO_CONTROL_3:
	हाल WM8903_GPIO_CONTROL_4:
	हाल WM8903_GPIO_CONTROL_5:
	हाल WM8903_INTERRUPT_STATUS_1:
	हाल WM8903_INTERRUPT_STATUS_1_MASK:
	हाल WM8903_INTERRUPT_POLARITY_1:
	हाल WM8903_INTERRUPT_CONTROL:
	हाल WM8903_CLOCK_RATE_TEST_4:
	हाल WM8903_ANALOGUE_OUTPUT_BIAS_0:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool wm8903_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8903_SW_RESET_AND_ID:
	हाल WM8903_REVISION_NUMBER:
	हाल WM8903_INTERRUPT_STATUS_1:
	हाल WM8903_WRITE_SEQUENCER_4:
	हाल WM8903_DC_SERVO_READBACK_1:
	हाल WM8903_DC_SERVO_READBACK_2:
	हाल WM8903_DC_SERVO_READBACK_3:
	हाल WM8903_DC_SERVO_READBACK_4:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक wm8903_cp_event(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	WARN_ON(event != SND_SOC_DAPM_POST_PMU);
	mdelay(4);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8903_dcs_event(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm8903_priv *wm8903 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		wm8903->dcs_pending |= 1 << w->shअगरt;
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, WM8903_DC_SERVO_0,
				    1 << w->shअगरt, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा WM8903_DCS_MODE_WRITE_STOP 0
#घोषणा WM8903_DCS_MODE_START_STOP 2

अटल व्योम wm8903_seq_notअगरier(काष्ठा snd_soc_component *component,
				क्रमागत snd_soc_dapm_type event, पूर्णांक subseq)
अणु
	काष्ठा wm8903_priv *wm8903 = snd_soc_component_get_drvdata(component);
	पूर्णांक dcs_mode = WM8903_DCS_MODE_WRITE_STOP;
	पूर्णांक i, val;

	/* Complete any pending DC servo starts */
	अगर (wm8903->dcs_pending) अणु
		dev_dbg(component->dev, "Starting DC servo for %x\n",
			wm8903->dcs_pending);

		/* If we've no cached values then we need to करो startup */
		क्रम (i = 0; i < ARRAY_SIZE(wm8903->dcs_cache); i++) अणु
			अगर (!(wm8903->dcs_pending & (1 << i)))
				जारी;

			अगर (wm8903->dcs_cache[i]) अणु
				dev_dbg(component->dev,
					"Restore DC servo %d value %x\n",
					3 - i, wm8903->dcs_cache[i]);

				snd_soc_component_ग_लिखो(component, WM8903_DC_SERVO_4 + i,
					      wm8903->dcs_cache[i] & 0xff);
			पूर्ण अन्यथा अणु
				dev_dbg(component->dev,
					"Calibrate DC servo %d\n", 3 - i);
				dcs_mode = WM8903_DCS_MODE_START_STOP;
			पूर्ण
		पूर्ण

		/* Don't trust the cache क्रम analogue */
		अगर (wm8903->class_w_users)
			dcs_mode = WM8903_DCS_MODE_START_STOP;

		snd_soc_component_update_bits(component, WM8903_DC_SERVO_2,
				    WM8903_DCS_MODE_MASK, dcs_mode);

		snd_soc_component_update_bits(component, WM8903_DC_SERVO_0,
				    WM8903_DCS_ENA_MASK, wm8903->dcs_pending);

		चयन (dcs_mode) अणु
		हाल WM8903_DCS_MODE_WRITE_STOP:
			अवरोध;

		हाल WM8903_DCS_MODE_START_STOP:
			msleep(270);

			/* Cache the measured offsets क्रम digital */
			अगर (wm8903->class_w_users)
				अवरोध;

			क्रम (i = 0; i < ARRAY_SIZE(wm8903->dcs_cache); i++) अणु
				अगर (!(wm8903->dcs_pending & (1 << i)))
					जारी;

				val = snd_soc_component_पढ़ो(component,
						   WM8903_DC_SERVO_READBACK_1 + i);
				dev_dbg(component->dev, "DC servo %d: %x\n",
					3 - i, val);
				wm8903->dcs_cache[i] = val;
			पूर्ण
			अवरोध;

		शेष:
			pr_warn("DCS mode %d delay not set\n", dcs_mode);
			अवरोध;
		पूर्ण

		wm8903->dcs_pending = 0;
	पूर्ण
पूर्ण

/*
 * When used with DAC outमाला_दो only the WM8903 अक्षरge pump supports
 * operation in class W mode, providing very low घातer consumption
 * when used with digital sources.  Enable and disable this mode
 * स्वतःmatically depending on the mixer configuration.
 *
 * All the relevant controls are simple चयनes.
 */
अटल पूर्णांक wm8903_class_w_put(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा wm8903_priv *wm8903 = snd_soc_component_get_drvdata(component);
	u16 reg;
	पूर्णांक ret;

	reg = snd_soc_component_पढ़ो(component, WM8903_CLASS_W_0);

	/* Turn it off अगर we're about to enable bypass */
	अगर (ucontrol->value.पूर्णांकeger.value[0]) अणु
		अगर (wm8903->class_w_users == 0) अणु
			dev_dbg(component->dev, "Disabling Class W\n");
			snd_soc_component_ग_लिखो(component, WM8903_CLASS_W_0, reg &
				     ~(WM8903_CP_DYN_FREQ | WM8903_CP_DYN_V));
		पूर्ण
		wm8903->class_w_users++;
	पूर्ण

	/* Implement the change */
	ret = snd_soc_dapm_put_volsw(kcontrol, ucontrol);

	/* If we've just disabled the last bypass path turn Class W on */
	अगर (!ucontrol->value.पूर्णांकeger.value[0]) अणु
		अगर (wm8903->class_w_users == 1) अणु
			dev_dbg(component->dev, "Enabling Class W\n");
			snd_soc_component_ग_लिखो(component, WM8903_CLASS_W_0, reg |
				     WM8903_CP_DYN_FREQ | WM8903_CP_DYN_V);
		पूर्ण
		wm8903->class_w_users--;
	पूर्ण

	dev_dbg(component->dev, "Bypass use count now %d\n",
		wm8903->class_w_users);

	वापस ret;
पूर्ण

#घोषणा SOC_DAPM_SINGLE_W(xname, reg, shअगरt, max, invert) \
	SOC_SINGLE_EXT(xname, reg, shअगरt, max, invert, \
		snd_soc_dapm_get_volsw, wm8903_class_w_put)


अटल पूर्णांक wm8903_deemph[] = अणु 0, 32000, 44100, 48000 पूर्ण;

अटल पूर्णांक wm8903_set_deemph(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8903_priv *wm8903 = snd_soc_component_get_drvdata(component);
	पूर्णांक val, i, best;

	/* If we're using deemphasis select the nearest available sample
	 * rate.
	 */
	अगर (wm8903->deemph) अणु
		best = 1;
		क्रम (i = 2; i < ARRAY_SIZE(wm8903_deemph); i++) अणु
			अगर (असल(wm8903_deemph[i] - wm8903->fs) <
			    असल(wm8903_deemph[best] - wm8903->fs))
				best = i;
		पूर्ण

		val = best << WM8903_DEEMPH_SHIFT;
	पूर्ण अन्यथा अणु
		best = 0;
		val = 0;
	पूर्ण

	dev_dbg(component->dev, "Set deemphasis %d (%dHz)\n",
		best, wm8903_deemph[best]);

	वापस snd_soc_component_update_bits(component, WM8903_DAC_DIGITAL_1,
				   WM8903_DEEMPH_MASK, val);
पूर्ण

अटल पूर्णांक wm8903_get_deemph(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8903_priv *wm8903 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = wm8903->deemph;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8903_put_deemph(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8903_priv *wm8903 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक deemph = ucontrol->value.पूर्णांकeger.value[0];
	पूर्णांक ret = 0;

	अगर (deemph > 1)
		वापस -EINVAL;

	mutex_lock(&wm8903->lock);
	अगर (wm8903->deemph != deemph) अणु
		wm8903->deemph = deemph;

		wm8903_set_deemph(component);

		ret = 1;
	पूर्ण
	mutex_unlock(&wm8903->lock);

	वापस ret;
पूर्ण

/* ALSA can only करो steps of .01dB */
अटल स्थिर DECLARE_TLV_DB_SCALE(digital_tlv, -7200, 75, 1);

अटल स्थिर DECLARE_TLV_DB_SCALE(dac_boost_tlv, 0, 600, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(digital_sidetone_tlv, -3600, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(out_tlv, -5700, 100, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(drc_tlv_thresh, 0, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(drc_tlv_amp, -2250, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(drc_tlv_min, 0, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(drc_tlv_max, 1200, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(drc_tlv_startup, -300, 50, 0);

अटल स्थिर अक्षर *hpf_mode_text[] = अणु
	"Hi-fi", "Voice 1", "Voice 2", "Voice 3"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(hpf_mode,
			    WM8903_ADC_DIGITAL_0, 5, hpf_mode_text);

अटल स्थिर अक्षर *osr_text[] = अणु
	"Low power", "High performance"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adc_osr,
			    WM8903_ANALOGUE_ADC_0, 0, osr_text);

अटल SOC_ENUM_SINGLE_DECL(dac_osr,
			    WM8903_DAC_DIGITAL_1, 0, osr_text);

अटल स्थिर अक्षर *drc_slope_text[] = अणु
	"1", "1/2", "1/4", "1/8", "1/16", "0"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(drc_slope_r0,
			    WM8903_DRC_2, 3, drc_slope_text);

अटल SOC_ENUM_SINGLE_DECL(drc_slope_r1,
			    WM8903_DRC_2, 0, drc_slope_text);

अटल स्थिर अक्षर *drc_attack_text[] = अणु
	"instantaneous",
	"363us", "762us", "1.45ms", "2.9ms", "5.8ms", "11.6ms", "23.2ms",
	"46.4ms", "92.8ms", "185.6ms"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(drc_attack,
			    WM8903_DRC_1, 12, drc_attack_text);

अटल स्थिर अक्षर *drc_decay_text[] = अणु
	"186ms", "372ms", "743ms", "1.49s", "2.97s", "5.94s", "11.89s",
	"23.87s", "47.56s"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(drc_decay,
			    WM8903_DRC_1, 8, drc_decay_text);

अटल स्थिर अक्षर *drc_ff_delay_text[] = अणु
	"5 samples", "9 samples"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(drc_ff_delay,
			    WM8903_DRC_0, 5, drc_ff_delay_text);

अटल स्थिर अक्षर *drc_qr_decay_text[] = अणु
	"0.725ms", "1.45ms", "5.8ms"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(drc_qr_decay,
			    WM8903_DRC_1, 4, drc_qr_decay_text);

अटल स्थिर अक्षर *drc_smoothing_text[] = अणु
	"Low", "Medium", "High"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(drc_smoothing,
			    WM8903_DRC_0, 11, drc_smoothing_text);

अटल स्थिर अक्षर *soft_mute_text[] = अणु
	"Fast (fs/2)", "Slow (fs/32)"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(soft_mute,
			    WM8903_DAC_DIGITAL_1, 10, soft_mute_text);

अटल स्थिर अक्षर *mute_mode_text[] = अणु
	"Hard", "Soft"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(mute_mode,
			    WM8903_DAC_DIGITAL_1, 9, mute_mode_text);

अटल स्थिर अक्षर *companding_text[] = अणु
	"ulaw", "alaw"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(dac_companding,
			    WM8903_AUDIO_INTERFACE_0, 0, companding_text);

अटल SOC_ENUM_SINGLE_DECL(adc_companding,
			    WM8903_AUDIO_INTERFACE_0, 2, companding_text);

अटल स्थिर अक्षर *input_mode_text[] = अणु
	"Single-Ended", "Differential Line", "Differential Mic"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(linput_mode_क्रमागत,
			    WM8903_ANALOGUE_LEFT_INPUT_1, 0, input_mode_text);

अटल SOC_ENUM_SINGLE_DECL(rinput_mode_क्रमागत,
			    WM8903_ANALOGUE_RIGHT_INPUT_1, 0, input_mode_text);

अटल स्थिर अक्षर *linput_mux_text[] = अणु
	"IN1L", "IN2L", "IN3L"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(linput_क्रमागत,
			    WM8903_ANALOGUE_LEFT_INPUT_1, 2, linput_mux_text);

अटल SOC_ENUM_SINGLE_DECL(linput_inv_क्रमागत,
			    WM8903_ANALOGUE_LEFT_INPUT_1, 4, linput_mux_text);

अटल स्थिर अक्षर *rinput_mux_text[] = अणु
	"IN1R", "IN2R", "IN3R"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rinput_क्रमागत,
			    WM8903_ANALOGUE_RIGHT_INPUT_1, 2, rinput_mux_text);

अटल SOC_ENUM_SINGLE_DECL(rinput_inv_क्रमागत,
			    WM8903_ANALOGUE_RIGHT_INPUT_1, 4, rinput_mux_text);


अटल स्थिर अक्षर *sidetone_text[] = अणु
	"None", "Left", "Right"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(lsidetone_क्रमागत,
			    WM8903_DAC_DIGITAL_0, 2, sidetone_text);

अटल SOC_ENUM_SINGLE_DECL(rsidetone_क्रमागत,
			    WM8903_DAC_DIGITAL_0, 0, sidetone_text);

अटल स्थिर अक्षर *adcinput_text[] = अणु
	"ADC", "DMIC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adcinput_क्रमागत,
			    WM8903_CLOCK_RATE_TEST_4, 9, adcinput_text);

अटल स्थिर अक्षर *aअगर_text[] = अणु
	"Left", "Right"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(lcapture_क्रमागत,
			    WM8903_AUDIO_INTERFACE_0, 7, aअगर_text);

अटल SOC_ENUM_SINGLE_DECL(rcapture_क्रमागत,
			    WM8903_AUDIO_INTERFACE_0, 6, aअगर_text);

अटल SOC_ENUM_SINGLE_DECL(lplay_क्रमागत,
			    WM8903_AUDIO_INTERFACE_0, 5, aअगर_text);

अटल SOC_ENUM_SINGLE_DECL(rplay_क्रमागत,
			    WM8903_AUDIO_INTERFACE_0, 4, aअगर_text);

अटल स्थिर काष्ठा snd_kcontrol_new wm8903_snd_controls[] = अणु

/* Input PGAs - No TLV since the scale depends on PGA mode */
SOC_SINGLE("Left Input PGA Switch", WM8903_ANALOGUE_LEFT_INPUT_0,
	   7, 1, 1),
SOC_SINGLE("Left Input PGA Volume", WM8903_ANALOGUE_LEFT_INPUT_0,
	   0, 31, 0),
SOC_SINGLE("Left Input PGA Common Mode Switch", WM8903_ANALOGUE_LEFT_INPUT_1,
	   6, 1, 0),

SOC_SINGLE("Right Input PGA Switch", WM8903_ANALOGUE_RIGHT_INPUT_0,
	   7, 1, 1),
SOC_SINGLE("Right Input PGA Volume", WM8903_ANALOGUE_RIGHT_INPUT_0,
	   0, 31, 0),
SOC_SINGLE("Right Input PGA Common Mode Switch", WM8903_ANALOGUE_RIGHT_INPUT_1,
	   6, 1, 0),

/* ADCs */
SOC_ENUM("ADC OSR", adc_osr),
SOC_SINGLE("HPF Switch", WM8903_ADC_DIGITAL_0, 4, 1, 0),
SOC_ENUM("HPF Mode", hpf_mode),
SOC_SINGLE("DRC Switch", WM8903_DRC_0, 15, 1, 0),
SOC_ENUM("DRC Compressor Slope R0", drc_slope_r0),
SOC_ENUM("DRC Compressor Slope R1", drc_slope_r1),
SOC_SINGLE_TLV("DRC Compressor Threshold Volume", WM8903_DRC_3, 5, 124, 1,
	       drc_tlv_thresh),
SOC_SINGLE_TLV("DRC Volume", WM8903_DRC_3, 0, 30, 1, drc_tlv_amp),
SOC_SINGLE_TLV("DRC Minimum Gain Volume", WM8903_DRC_1, 2, 3, 1, drc_tlv_min),
SOC_SINGLE_TLV("DRC Maximum Gain Volume", WM8903_DRC_1, 0, 3, 0, drc_tlv_max),
SOC_ENUM("DRC Attack Rate", drc_attack),
SOC_ENUM("DRC Decay Rate", drc_decay),
SOC_ENUM("DRC FF Delay", drc_ff_delay),
SOC_SINGLE("DRC Anticlip Switch", WM8903_DRC_0, 1, 1, 0),
SOC_SINGLE("DRC QR Switch", WM8903_DRC_0, 2, 1, 0),
SOC_SINGLE_TLV("DRC QR Threshold Volume", WM8903_DRC_0, 6, 3, 0, drc_tlv_max),
SOC_ENUM("DRC QR Decay Rate", drc_qr_decay),
SOC_SINGLE("DRC Smoothing Switch", WM8903_DRC_0, 3, 1, 0),
SOC_SINGLE("DRC Smoothing Hysteresis Switch", WM8903_DRC_0, 0, 1, 0),
SOC_ENUM("DRC Smoothing Threshold", drc_smoothing),
SOC_SINGLE_TLV("DRC Startup Volume", WM8903_DRC_0, 6, 18, 0, drc_tlv_startup),

SOC_DOUBLE_R_TLV("Digital Capture Volume", WM8903_ADC_DIGITAL_VOLUME_LEFT,
		 WM8903_ADC_DIGITAL_VOLUME_RIGHT, 1, 120, 0, digital_tlv),
SOC_ENUM("ADC Companding Mode", adc_companding),
SOC_SINGLE("ADC Companding Switch", WM8903_AUDIO_INTERFACE_0, 3, 1, 0),

SOC_DOUBLE_TLV("Digital Sidetone Volume", WM8903_DAC_DIGITAL_0, 4, 8,
	       12, 0, digital_sidetone_tlv),

/* DAC */
SOC_ENUM("DAC OSR", dac_osr),
SOC_DOUBLE_R_TLV("Digital Playback Volume", WM8903_DAC_DIGITAL_VOLUME_LEFT,
		 WM8903_DAC_DIGITAL_VOLUME_RIGHT, 1, 120, 0, digital_tlv),
SOC_ENUM("DAC Soft Mute Rate", soft_mute),
SOC_ENUM("DAC Mute Mode", mute_mode),
SOC_SINGLE("DAC Mono Switch", WM8903_DAC_DIGITAL_1, 12, 1, 0),
SOC_ENUM("DAC Companding Mode", dac_companding),
SOC_SINGLE("DAC Companding Switch", WM8903_AUDIO_INTERFACE_0, 1, 1, 0),
SOC_SINGLE_TLV("DAC Boost Volume", WM8903_AUDIO_INTERFACE_0, 9, 3, 0,
	       dac_boost_tlv),
SOC_SINGLE_BOOL_EXT("Playback Deemphasis Switch", 0,
		    wm8903_get_deemph, wm8903_put_deemph),

/* Headphones */
SOC_DOUBLE_R("Headphone Switch",
	     WM8903_ANALOGUE_OUT1_LEFT, WM8903_ANALOGUE_OUT1_RIGHT,
	     8, 1, 1),
SOC_DOUBLE_R("Headphone ZC Switch",
	     WM8903_ANALOGUE_OUT1_LEFT, WM8903_ANALOGUE_OUT1_RIGHT,
	     6, 1, 0),
SOC_DOUBLE_R_TLV("Headphone Volume",
		 WM8903_ANALOGUE_OUT1_LEFT, WM8903_ANALOGUE_OUT1_RIGHT,
		 0, 63, 0, out_tlv),

/* Line out */
SOC_DOUBLE_R("Line Out Switch",
	     WM8903_ANALOGUE_OUT2_LEFT, WM8903_ANALOGUE_OUT2_RIGHT,
	     8, 1, 1),
SOC_DOUBLE_R("Line Out ZC Switch",
	     WM8903_ANALOGUE_OUT2_LEFT, WM8903_ANALOGUE_OUT2_RIGHT,
	     6, 1, 0),
SOC_DOUBLE_R_TLV("Line Out Volume",
		 WM8903_ANALOGUE_OUT2_LEFT, WM8903_ANALOGUE_OUT2_RIGHT,
		 0, 63, 0, out_tlv),

/* Speaker */
SOC_DOUBLE_R("Speaker Switch",
	     WM8903_ANALOGUE_OUT3_LEFT, WM8903_ANALOGUE_OUT3_RIGHT, 8, 1, 1),
SOC_DOUBLE_R("Speaker ZC Switch",
	     WM8903_ANALOGUE_OUT3_LEFT, WM8903_ANALOGUE_OUT3_RIGHT, 6, 1, 0),
SOC_DOUBLE_R_TLV("Speaker Volume",
		 WM8903_ANALOGUE_OUT3_LEFT, WM8903_ANALOGUE_OUT3_RIGHT,
		 0, 63, 0, out_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new linput_mode_mux =
	SOC_DAPM_ENUM("Left Input Mode Mux", linput_mode_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rinput_mode_mux =
	SOC_DAPM_ENUM("Right Input Mode Mux", rinput_mode_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new linput_mux =
	SOC_DAPM_ENUM("Left Input Mux", linput_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new linput_inv_mux =
	SOC_DAPM_ENUM("Left Inverting Input Mux", linput_inv_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rinput_mux =
	SOC_DAPM_ENUM("Right Input Mux", rinput_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rinput_inv_mux =
	SOC_DAPM_ENUM("Right Inverting Input Mux", rinput_inv_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new lsidetone_mux =
	SOC_DAPM_ENUM("DACL Sidetone Mux", lsidetone_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rsidetone_mux =
	SOC_DAPM_ENUM("DACR Sidetone Mux", rsidetone_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new adcinput_mux =
	SOC_DAPM_ENUM("ADC Input", adcinput_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new lcapture_mux =
	SOC_DAPM_ENUM("Left Capture Mux", lcapture_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rcapture_mux =
	SOC_DAPM_ENUM("Right Capture Mux", rcapture_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new lplay_mux =
	SOC_DAPM_ENUM("Left Playback Mux", lplay_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rplay_mux =
	SOC_DAPM_ENUM("Right Playback Mux", rplay_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new left_output_mixer[] = अणु
SOC_DAPM_SINGLE("DACL Switch", WM8903_ANALOGUE_LEFT_MIX_0, 3, 1, 0),
SOC_DAPM_SINGLE("DACR Switch", WM8903_ANALOGUE_LEFT_MIX_0, 2, 1, 0),
SOC_DAPM_SINGLE_W("Left Bypass Switch", WM8903_ANALOGUE_LEFT_MIX_0, 1, 1, 0),
SOC_DAPM_SINGLE_W("Right Bypass Switch", WM8903_ANALOGUE_LEFT_MIX_0, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new right_output_mixer[] = अणु
SOC_DAPM_SINGLE("DACL Switch", WM8903_ANALOGUE_RIGHT_MIX_0, 3, 1, 0),
SOC_DAPM_SINGLE("DACR Switch", WM8903_ANALOGUE_RIGHT_MIX_0, 2, 1, 0),
SOC_DAPM_SINGLE_W("Left Bypass Switch", WM8903_ANALOGUE_RIGHT_MIX_0, 1, 1, 0),
SOC_DAPM_SINGLE_W("Right Bypass Switch", WM8903_ANALOGUE_RIGHT_MIX_0, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new left_speaker_mixer[] = अणु
SOC_DAPM_SINGLE("DACL Switch", WM8903_ANALOGUE_SPK_MIX_LEFT_0, 3, 1, 0),
SOC_DAPM_SINGLE("DACR Switch", WM8903_ANALOGUE_SPK_MIX_LEFT_0, 2, 1, 0),
SOC_DAPM_SINGLE("Left Bypass Switch", WM8903_ANALOGUE_SPK_MIX_LEFT_0, 1, 1, 0),
SOC_DAPM_SINGLE("Right Bypass Switch", WM8903_ANALOGUE_SPK_MIX_LEFT_0,
		0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new right_speaker_mixer[] = अणु
SOC_DAPM_SINGLE("DACL Switch", WM8903_ANALOGUE_SPK_MIX_RIGHT_0, 3, 1, 0),
SOC_DAPM_SINGLE("DACR Switch", WM8903_ANALOGUE_SPK_MIX_RIGHT_0, 2, 1, 0),
SOC_DAPM_SINGLE("Left Bypass Switch", WM8903_ANALOGUE_SPK_MIX_RIGHT_0,
		1, 1, 0),
SOC_DAPM_SINGLE("Right Bypass Switch", WM8903_ANALOGUE_SPK_MIX_RIGHT_0,
		0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8903_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("IN1L"),
SND_SOC_DAPM_INPUT("IN1R"),
SND_SOC_DAPM_INPUT("IN2L"),
SND_SOC_DAPM_INPUT("IN2R"),
SND_SOC_DAPM_INPUT("IN3L"),
SND_SOC_DAPM_INPUT("IN3R"),
SND_SOC_DAPM_INPUT("DMICDAT"),

SND_SOC_DAPM_OUTPUT("HPOUTL"),
SND_SOC_DAPM_OUTPUT("HPOUTR"),
SND_SOC_DAPM_OUTPUT("LINEOUTL"),
SND_SOC_DAPM_OUTPUT("LINEOUTR"),
SND_SOC_DAPM_OUTPUT("LOP"),
SND_SOC_DAPM_OUTPUT("LON"),
SND_SOC_DAPM_OUTPUT("ROP"),
SND_SOC_DAPM_OUTPUT("RON"),

SND_SOC_DAPM_SUPPLY("MICBIAS", WM8903_MIC_BIAS_CONTROL_0, 0, 0, शून्य, 0),

SND_SOC_DAPM_MUX("Left Input Mux", SND_SOC_NOPM, 0, 0, &linput_mux),
SND_SOC_DAPM_MUX("Left Input Inverting Mux", SND_SOC_NOPM, 0, 0,
		 &linput_inv_mux),
SND_SOC_DAPM_MUX("Left Input Mode Mux", SND_SOC_NOPM, 0, 0, &linput_mode_mux),

SND_SOC_DAPM_MUX("Right Input Mux", SND_SOC_NOPM, 0, 0, &rinput_mux),
SND_SOC_DAPM_MUX("Right Input Inverting Mux", SND_SOC_NOPM, 0, 0,
		 &rinput_inv_mux),
SND_SOC_DAPM_MUX("Right Input Mode Mux", SND_SOC_NOPM, 0, 0, &rinput_mode_mux),

SND_SOC_DAPM_PGA("Left Input PGA", WM8903_POWER_MANAGEMENT_0, 1, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Right Input PGA", WM8903_POWER_MANAGEMENT_0, 0, 0, शून्य, 0),

SND_SOC_DAPM_MUX("Left ADC Input", SND_SOC_NOPM, 0, 0, &adcinput_mux),
SND_SOC_DAPM_MUX("Right ADC Input", SND_SOC_NOPM, 0, 0, &adcinput_mux),

SND_SOC_DAPM_ADC("ADCL", शून्य, WM8903_POWER_MANAGEMENT_6, 1, 0),
SND_SOC_DAPM_ADC("ADCR", शून्य, WM8903_POWER_MANAGEMENT_6, 0, 0),

SND_SOC_DAPM_MUX("Left Capture Mux", SND_SOC_NOPM, 0, 0, &lcapture_mux),
SND_SOC_DAPM_MUX("Right Capture Mux", SND_SOC_NOPM, 0, 0, &rcapture_mux),

SND_SOC_DAPM_AIF_OUT("AIFTXL", "Left HiFi Capture", 0, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_AIF_OUT("AIFTXR", "Right HiFi Capture", 0, SND_SOC_NOPM, 0, 0),

SND_SOC_DAPM_MUX("DACL Sidetone", SND_SOC_NOPM, 0, 0, &lsidetone_mux),
SND_SOC_DAPM_MUX("DACR Sidetone", SND_SOC_NOPM, 0, 0, &rsidetone_mux),

SND_SOC_DAPM_AIF_IN("AIFRXL", "Left Playback", 0, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_AIF_IN("AIFRXR", "Right Playback", 0, SND_SOC_NOPM, 0, 0),

SND_SOC_DAPM_MUX("Left Playback Mux", SND_SOC_NOPM, 0, 0, &lplay_mux),
SND_SOC_DAPM_MUX("Right Playback Mux", SND_SOC_NOPM, 0, 0, &rplay_mux),

SND_SOC_DAPM_DAC("DACL", शून्य, WM8903_POWER_MANAGEMENT_6, 3, 0),
SND_SOC_DAPM_DAC("DACR", शून्य, WM8903_POWER_MANAGEMENT_6, 2, 0),

SND_SOC_DAPM_MIXER("Left Output Mixer", WM8903_POWER_MANAGEMENT_1, 1, 0,
		   left_output_mixer, ARRAY_SIZE(left_output_mixer)),
SND_SOC_DAPM_MIXER("Right Output Mixer", WM8903_POWER_MANAGEMENT_1, 0, 0,
		   right_output_mixer, ARRAY_SIZE(right_output_mixer)),

SND_SOC_DAPM_MIXER("Left Speaker Mixer", WM8903_POWER_MANAGEMENT_4, 1, 0,
		   left_speaker_mixer, ARRAY_SIZE(left_speaker_mixer)),
SND_SOC_DAPM_MIXER("Right Speaker Mixer", WM8903_POWER_MANAGEMENT_4, 0, 0,
		   right_speaker_mixer, ARRAY_SIZE(right_speaker_mixer)),

SND_SOC_DAPM_PGA_S("Left Headphone Output PGA", 0, WM8903_POWER_MANAGEMENT_2,
		   1, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("Right Headphone Output PGA", 0, WM8903_POWER_MANAGEMENT_2,
		   0, 0, शून्य, 0),

SND_SOC_DAPM_PGA_S("Left Line Output PGA", 0, WM8903_POWER_MANAGEMENT_3, 1, 0,
		   शून्य, 0),
SND_SOC_DAPM_PGA_S("Right Line Output PGA", 0, WM8903_POWER_MANAGEMENT_3, 0, 0,
		   शून्य, 0),

SND_SOC_DAPM_PGA_S("HPL_RMV_SHORT", 4, WM8903_ANALOGUE_HP_0, 7, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("HPL_ENA_OUTP", 3, WM8903_ANALOGUE_HP_0, 6, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("HPL_ENA_DLY", 2, WM8903_ANALOGUE_HP_0, 5, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("HPL_ENA", 1, WM8903_ANALOGUE_HP_0, 4, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("HPR_RMV_SHORT", 4, WM8903_ANALOGUE_HP_0, 3, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("HPR_ENA_OUTP", 3, WM8903_ANALOGUE_HP_0, 2, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("HPR_ENA_DLY", 2, WM8903_ANALOGUE_HP_0, 1, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("HPR_ENA", 1, WM8903_ANALOGUE_HP_0, 0, 0, शून्य, 0),

SND_SOC_DAPM_PGA_S("LINEOUTL_RMV_SHORT", 4, WM8903_ANALOGUE_LINEOUT_0, 7, 0,
		   शून्य, 0),
SND_SOC_DAPM_PGA_S("LINEOUTL_ENA_OUTP", 3, WM8903_ANALOGUE_LINEOUT_0, 6, 0,
		   शून्य, 0),
SND_SOC_DAPM_PGA_S("LINEOUTL_ENA_DLY", 2, WM8903_ANALOGUE_LINEOUT_0, 5, 0,
		   शून्य, 0),
SND_SOC_DAPM_PGA_S("LINEOUTL_ENA", 1, WM8903_ANALOGUE_LINEOUT_0, 4, 0,
		   शून्य, 0),
SND_SOC_DAPM_PGA_S("LINEOUTR_RMV_SHORT", 4, WM8903_ANALOGUE_LINEOUT_0, 3, 0,
		   शून्य, 0),
SND_SOC_DAPM_PGA_S("LINEOUTR_ENA_OUTP", 3, WM8903_ANALOGUE_LINEOUT_0, 2, 0,
		   शून्य, 0),
SND_SOC_DAPM_PGA_S("LINEOUTR_ENA_DLY", 2, WM8903_ANALOGUE_LINEOUT_0, 1, 0,
		   शून्य, 0),
SND_SOC_DAPM_PGA_S("LINEOUTR_ENA", 1, WM8903_ANALOGUE_LINEOUT_0, 0, 0,
		   शून्य, 0),

SND_SOC_DAPM_SUPPLY("DCS Master", WM8903_DC_SERVO_0, 4, 0, शून्य, 0),
SND_SOC_DAPM_PGA_S("HPL_DCS", 3, SND_SOC_NOPM, 3, 0, wm8903_dcs_event,
		   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
SND_SOC_DAPM_PGA_S("HPR_DCS", 3, SND_SOC_NOPM, 2, 0, wm8903_dcs_event,
		   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
SND_SOC_DAPM_PGA_S("LINEOUTL_DCS", 3, SND_SOC_NOPM, 1, 0, wm8903_dcs_event,
		   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
SND_SOC_DAPM_PGA_S("LINEOUTR_DCS", 3, SND_SOC_NOPM, 0, 0, wm8903_dcs_event,
		   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

SND_SOC_DAPM_PGA("Left Speaker PGA", WM8903_POWER_MANAGEMENT_5, 1, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("Right Speaker PGA", WM8903_POWER_MANAGEMENT_5, 0, 0,
		 शून्य, 0),

SND_SOC_DAPM_SUPPLY("Charge Pump", WM8903_CHARGE_PUMP_0, 0, 0,
		    wm8903_cp_event, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_SUPPLY("CLK_DSP", WM8903_CLOCK_RATES_2, 1, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("CLK_SYS", WM8903_CLOCK_RATES_2, 2, 0, शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8903_पूर्णांकercon[] = अणु

	अणु "CLK_DSP", शून्य, "CLK_SYS" पूर्ण,
	अणु "MICBIAS", शून्य, "CLK_SYS" पूर्ण,
	अणु "HPL_DCS", शून्य, "CLK_SYS" पूर्ण,
	अणु "HPR_DCS", शून्य, "CLK_SYS" पूर्ण,
	अणु "LINEOUTL_DCS", शून्य, "CLK_SYS" पूर्ण,
	अणु "LINEOUTR_DCS", शून्य, "CLK_SYS" पूर्ण,

	अणु "Left Input Mux", "IN1L", "IN1L" पूर्ण,
	अणु "Left Input Mux", "IN2L", "IN2L" पूर्ण,
	अणु "Left Input Mux", "IN3L", "IN3L" पूर्ण,

	अणु "Left Input Inverting Mux", "IN1L", "IN1L" पूर्ण,
	अणु "Left Input Inverting Mux", "IN2L", "IN2L" पूर्ण,
	अणु "Left Input Inverting Mux", "IN3L", "IN3L" पूर्ण,

	अणु "Right Input Mux", "IN1R", "IN1R" पूर्ण,
	अणु "Right Input Mux", "IN2R", "IN2R" पूर्ण,
	अणु "Right Input Mux", "IN3R", "IN3R" पूर्ण,

	अणु "Right Input Inverting Mux", "IN1R", "IN1R" पूर्ण,
	अणु "Right Input Inverting Mux", "IN2R", "IN2R" पूर्ण,
	अणु "Right Input Inverting Mux", "IN3R", "IN3R" पूर्ण,

	अणु "Left Input Mode Mux", "Single-Ended", "Left Input Inverting Mux" पूर्ण,
	अणु "Left Input Mode Mux", "Differential Line",
	  "Left Input Mux" पूर्ण,
	अणु "Left Input Mode Mux", "Differential Line",
	  "Left Input Inverting Mux" पूर्ण,
	अणु "Left Input Mode Mux", "Differential Mic",
	  "Left Input Mux" पूर्ण,
	अणु "Left Input Mode Mux", "Differential Mic",
	  "Left Input Inverting Mux" पूर्ण,

	अणु "Right Input Mode Mux", "Single-Ended",
	  "Right Input Inverting Mux" पूर्ण,
	अणु "Right Input Mode Mux", "Differential Line",
	  "Right Input Mux" पूर्ण,
	अणु "Right Input Mode Mux", "Differential Line",
	  "Right Input Inverting Mux" पूर्ण,
	अणु "Right Input Mode Mux", "Differential Mic",
	  "Right Input Mux" पूर्ण,
	अणु "Right Input Mode Mux", "Differential Mic",
	  "Right Input Inverting Mux" पूर्ण,

	अणु "Left Input PGA", शून्य, "Left Input Mode Mux" पूर्ण,
	अणु "Right Input PGA", शून्य, "Right Input Mode Mux" पूर्ण,

	अणु "Left ADC Input", "ADC", "Left Input PGA" पूर्ण,
	अणु "Left ADC Input", "DMIC", "DMICDAT" पूर्ण,
	अणु "Right ADC Input", "ADC", "Right Input PGA" पूर्ण,
	अणु "Right ADC Input", "DMIC", "DMICDAT" पूर्ण,

	अणु "Left Capture Mux", "Left", "ADCL" पूर्ण,
	अणु "Left Capture Mux", "Right", "ADCR" पूर्ण,

	अणु "Right Capture Mux", "Left", "ADCL" पूर्ण,
	अणु "Right Capture Mux", "Right", "ADCR" पूर्ण,

	अणु "AIFTXL", शून्य, "Left Capture Mux" पूर्ण,
	अणु "AIFTXR", शून्य, "Right Capture Mux" पूर्ण,

	अणु "ADCL", शून्य, "Left ADC Input" पूर्ण,
	अणु "ADCL", शून्य, "CLK_DSP" पूर्ण,
	अणु "ADCR", शून्य, "Right ADC Input" पूर्ण,
	अणु "ADCR", शून्य, "CLK_DSP" पूर्ण,

	अणु "Left Playback Mux", "Left", "AIFRXL" पूर्ण,
	अणु "Left Playback Mux", "Right", "AIFRXR" पूर्ण,

	अणु "Right Playback Mux", "Left", "AIFRXL" पूर्ण,
	अणु "Right Playback Mux", "Right", "AIFRXR" पूर्ण,

	अणु "DACL Sidetone", "Left", "ADCL" पूर्ण,
	अणु "DACL Sidetone", "Right", "ADCR" पूर्ण,
	अणु "DACR Sidetone", "Left", "ADCL" पूर्ण,
	अणु "DACR Sidetone", "Right", "ADCR" पूर्ण,

	अणु "DACL", शून्य, "Left Playback Mux" पूर्ण,
	अणु "DACL", शून्य, "DACL Sidetone" पूर्ण,
	अणु "DACL", शून्य, "CLK_DSP" पूर्ण,

	अणु "DACR", शून्य, "Right Playback Mux" पूर्ण,
	अणु "DACR", शून्य, "DACR Sidetone" पूर्ण,
	अणु "DACR", शून्य, "CLK_DSP" पूर्ण,

	अणु "Left Output Mixer", "Left Bypass Switch", "Left Input PGA" पूर्ण,
	अणु "Left Output Mixer", "Right Bypass Switch", "Right Input PGA" पूर्ण,
	अणु "Left Output Mixer", "DACL Switch", "DACL" पूर्ण,
	अणु "Left Output Mixer", "DACR Switch", "DACR" पूर्ण,

	अणु "Right Output Mixer", "Left Bypass Switch", "Left Input PGA" पूर्ण,
	अणु "Right Output Mixer", "Right Bypass Switch", "Right Input PGA" पूर्ण,
	अणु "Right Output Mixer", "DACL Switch", "DACL" पूर्ण,
	अणु "Right Output Mixer", "DACR Switch", "DACR" पूर्ण,

	अणु "Left Speaker Mixer", "Left Bypass Switch", "Left Input PGA" पूर्ण,
	अणु "Left Speaker Mixer", "Right Bypass Switch", "Right Input PGA" पूर्ण,
	अणु "Left Speaker Mixer", "DACL Switch", "DACL" पूर्ण,
	अणु "Left Speaker Mixer", "DACR Switch", "DACR" पूर्ण,

	अणु "Right Speaker Mixer", "Left Bypass Switch", "Left Input PGA" पूर्ण,
	अणु "Right Speaker Mixer", "Right Bypass Switch", "Right Input PGA" पूर्ण,
	अणु "Right Speaker Mixer", "DACL Switch", "DACL" पूर्ण,
	अणु "Right Speaker Mixer", "DACR Switch", "DACR" पूर्ण,

	अणु "Left Line Output PGA", शून्य, "Left Output Mixer" पूर्ण,
	अणु "Right Line Output PGA", शून्य, "Right Output Mixer" पूर्ण,

	अणु "Left Headphone Output PGA", शून्य, "Left Output Mixer" पूर्ण,
	अणु "Right Headphone Output PGA", शून्य, "Right Output Mixer" पूर्ण,

	अणु "Left Speaker PGA", शून्य, "Left Speaker Mixer" पूर्ण,
	अणु "Right Speaker PGA", शून्य, "Right Speaker Mixer" पूर्ण,

	अणु "HPL_ENA", शून्य, "Left Headphone Output PGA" पूर्ण,
	अणु "HPR_ENA", शून्य, "Right Headphone Output PGA" पूर्ण,
	अणु "HPL_ENA_DLY", शून्य, "HPL_ENA" पूर्ण,
	अणु "HPR_ENA_DLY", शून्य, "HPR_ENA" पूर्ण,
	अणु "LINEOUTL_ENA", शून्य, "Left Line Output PGA" पूर्ण,
	अणु "LINEOUTR_ENA", शून्य, "Right Line Output PGA" पूर्ण,
	अणु "LINEOUTL_ENA_DLY", शून्य, "LINEOUTL_ENA" पूर्ण,
	अणु "LINEOUTR_ENA_DLY", शून्य, "LINEOUTR_ENA" पूर्ण,

	अणु "HPL_DCS", शून्य, "DCS Master" पूर्ण,
	अणु "HPR_DCS", शून्य, "DCS Master" पूर्ण,
	अणु "LINEOUTL_DCS", शून्य, "DCS Master" पूर्ण,
	अणु "LINEOUTR_DCS", शून्य, "DCS Master" पूर्ण,

	अणु "HPL_DCS", शून्य, "HPL_ENA_DLY" पूर्ण,
	अणु "HPR_DCS", शून्य, "HPR_ENA_DLY" पूर्ण,
	अणु "LINEOUTL_DCS", शून्य, "LINEOUTL_ENA_DLY" पूर्ण,
	अणु "LINEOUTR_DCS", शून्य, "LINEOUTR_ENA_DLY" पूर्ण,

	अणु "HPL_ENA_OUTP", शून्य, "HPL_DCS" पूर्ण,
	अणु "HPR_ENA_OUTP", शून्य, "HPR_DCS" पूर्ण,
	अणु "LINEOUTL_ENA_OUTP", शून्य, "LINEOUTL_DCS" पूर्ण,
	अणु "LINEOUTR_ENA_OUTP", शून्य, "LINEOUTR_DCS" पूर्ण,

	अणु "HPL_RMV_SHORT", शून्य, "HPL_ENA_OUTP" पूर्ण,
	अणु "HPR_RMV_SHORT", शून्य, "HPR_ENA_OUTP" पूर्ण,
	अणु "LINEOUTL_RMV_SHORT", शून्य, "LINEOUTL_ENA_OUTP" पूर्ण,
	अणु "LINEOUTR_RMV_SHORT", शून्य, "LINEOUTR_ENA_OUTP" पूर्ण,

	अणु "HPOUTL", शून्य, "HPL_RMV_SHORT" पूर्ण,
	अणु "HPOUTR", शून्य, "HPR_RMV_SHORT" पूर्ण,
	अणु "LINEOUTL", शून्य, "LINEOUTL_RMV_SHORT" पूर्ण,
	अणु "LINEOUTR", शून्य, "LINEOUTR_RMV_SHORT" पूर्ण,

	अणु "LOP", शून्य, "Left Speaker PGA" पूर्ण,
	अणु "LON", शून्य, "Left Speaker PGA" पूर्ण,

	अणु "ROP", शून्य, "Right Speaker PGA" पूर्ण,
	अणु "RON", शून्य, "Right Speaker PGA" पूर्ण,

	अणु "Charge Pump", शून्य, "CLK_DSP" पूर्ण,

	अणु "Left Headphone Output PGA", शून्य, "Charge Pump" पूर्ण,
	अणु "Right Headphone Output PGA", शून्य, "Charge Pump" पूर्ण,
	अणु "Left Line Output PGA", शून्य, "Charge Pump" पूर्ण,
	अणु "Right Line Output PGA", शून्य, "Charge Pump" पूर्ण,
पूर्ण;

अटल पूर्णांक wm8903_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		snd_soc_component_update_bits(component, WM8903_VMID_CONTROL_0,
				    WM8903_VMID_RES_MASK,
				    WM8903_VMID_RES_50K);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			snd_soc_component_update_bits(component, WM8903_BIAS_CONTROL_0,
					    WM8903_POBCTRL | WM8903_ISEL_MASK |
					    WM8903_STARTUP_BIAS_ENA |
					    WM8903_BIAS_ENA,
					    WM8903_POBCTRL |
					    (2 << WM8903_ISEL_SHIFT) |
					    WM8903_STARTUP_BIAS_ENA);

			snd_soc_component_update_bits(component,
					    WM8903_ANALOGUE_SPK_OUTPUT_CONTROL_0,
					    WM8903_SPK_DISCHARGE,
					    WM8903_SPK_DISCHARGE);

			msleep(33);

			snd_soc_component_update_bits(component, WM8903_POWER_MANAGEMENT_5,
					    WM8903_SPKL_ENA | WM8903_SPKR_ENA,
					    WM8903_SPKL_ENA | WM8903_SPKR_ENA);

			snd_soc_component_update_bits(component,
					    WM8903_ANALOGUE_SPK_OUTPUT_CONTROL_0,
					    WM8903_SPK_DISCHARGE, 0);

			snd_soc_component_update_bits(component, WM8903_VMID_CONTROL_0,
					    WM8903_VMID_TIE_ENA |
					    WM8903_BUFIO_ENA |
					    WM8903_VMID_IO_ENA |
					    WM8903_VMID_SOFT_MASK |
					    WM8903_VMID_RES_MASK |
					    WM8903_VMID_BUF_ENA,
					    WM8903_VMID_TIE_ENA |
					    WM8903_BUFIO_ENA |
					    WM8903_VMID_IO_ENA |
					    (2 << WM8903_VMID_SOFT_SHIFT) |
					    WM8903_VMID_RES_250K |
					    WM8903_VMID_BUF_ENA);

			msleep(129);

			snd_soc_component_update_bits(component, WM8903_POWER_MANAGEMENT_5,
					    WM8903_SPKL_ENA | WM8903_SPKR_ENA,
					    0);

			snd_soc_component_update_bits(component, WM8903_VMID_CONTROL_0,
					    WM8903_VMID_SOFT_MASK, 0);

			snd_soc_component_update_bits(component, WM8903_VMID_CONTROL_0,
					    WM8903_VMID_RES_MASK,
					    WM8903_VMID_RES_50K);

			snd_soc_component_update_bits(component, WM8903_BIAS_CONTROL_0,
					    WM8903_BIAS_ENA | WM8903_POBCTRL,
					    WM8903_BIAS_ENA);

			/* By शेष no bypass paths are enabled so
			 * enable Class W support.
			 */
			dev_dbg(component->dev, "Enabling Class W\n");
			snd_soc_component_update_bits(component, WM8903_CLASS_W_0,
					    WM8903_CP_DYN_FREQ |
					    WM8903_CP_DYN_V,
					    WM8903_CP_DYN_FREQ |
					    WM8903_CP_DYN_V);
		पूर्ण

		snd_soc_component_update_bits(component, WM8903_VMID_CONTROL_0,
				    WM8903_VMID_RES_MASK,
				    WM8903_VMID_RES_250K);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, WM8903_BIAS_CONTROL_0,
				    WM8903_BIAS_ENA, 0);

		snd_soc_component_update_bits(component, WM8903_VMID_CONTROL_0,
				    WM8903_VMID_SOFT_MASK,
				    2 << WM8903_VMID_SOFT_SHIFT);

		snd_soc_component_update_bits(component, WM8903_VMID_CONTROL_0,
				    WM8903_VMID_BUF_ENA, 0);

		msleep(290);

		snd_soc_component_update_bits(component, WM8903_VMID_CONTROL_0,
				    WM8903_VMID_TIE_ENA | WM8903_BUFIO_ENA |
				    WM8903_VMID_IO_ENA | WM8903_VMID_RES_MASK |
				    WM8903_VMID_SOFT_MASK |
				    WM8903_VMID_BUF_ENA, 0);

		snd_soc_component_update_bits(component, WM8903_BIAS_CONTROL_0,
				    WM8903_STARTUP_BIAS_ENA, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8903_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				 पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8903_priv *wm8903 = snd_soc_component_get_drvdata(component);

	wm8903->sysclk = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8903_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
			      अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 aअगर1 = snd_soc_component_पढ़ो(component, WM8903_AUDIO_INTERFACE_1);

	aअगर1 &= ~(WM8903_LRCLK_सूची | WM8903_BCLK_सूची | WM8903_AIF_FMT_MASK |
		  WM8903_AIF_LRCLK_INV | WM8903_AIF_BCLK_INV);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		aअगर1 |= WM8903_LRCLK_सूची;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		aअगर1 |= WM8903_LRCLK_सूची | WM8903_BCLK_सूची;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		aअगर1 |= WM8903_BCLK_सूची;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
		aअगर1 |= 0x3;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		aअगर1 |= 0x3 | WM8903_AIF_LRCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		aअगर1 |= 0x2;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		aअगर1 |= 0x1;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Clock inversion */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
	हाल SND_SOC_DAIFMT_DSP_B:
		/* frame inversion not valid क्रम DSP modes */
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			aअगर1 |= WM8903_AIF_BCLK_INV;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_RIGHT_J:
	हाल SND_SOC_DAIFMT_LEFT_J:
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_IF:
			aअगर1 |= WM8903_AIF_BCLK_INV | WM8903_AIF_LRCLK_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			aअगर1 |= WM8903_AIF_BCLK_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_NB_IF:
			aअगर1 |= WM8903_AIF_LRCLK_INV;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8903_AUDIO_INTERFACE_1, aअगर1);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8903_mute(काष्ठा snd_soc_dai *codec_dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 reg;

	reg = snd_soc_component_पढ़ो(component, WM8903_DAC_DIGITAL_1);

	अगर (mute)
		reg |= WM8903_DAC_MUTE;
	अन्यथा
		reg &= ~WM8903_DAC_MUTE;

	snd_soc_component_ग_लिखो(component, WM8903_DAC_DIGITAL_1, reg);

	वापस 0;
पूर्ण

/* Lookup table क्रम CLK_SYS/fs ratio.  256fs or more is recommended
 * क्रम optimal perक्रमmance so we list the lower rates first and match
 * on the last match we find. */
अटल काष्ठा अणु
	पूर्णांक भाग;
	पूर्णांक rate;
	पूर्णांक mode;
	पूर्णांक mclk_भाग;
पूर्ण clk_sys_ratios[] = अणु
	अणु   64, 0x0, 0x0, 1 पूर्ण,
	अणु   68, 0x0, 0x1, 1 पूर्ण,
	अणु  125, 0x0, 0x2, 1 पूर्ण,
	अणु  128, 0x1, 0x0, 1 पूर्ण,
	अणु  136, 0x1, 0x1, 1 पूर्ण,
	अणु  192, 0x2, 0x0, 1 पूर्ण,
	अणु  204, 0x2, 0x1, 1 पूर्ण,

	अणु   64, 0x0, 0x0, 2 पूर्ण,
	अणु   68, 0x0, 0x1, 2 पूर्ण,
	अणु  125, 0x0, 0x2, 2 पूर्ण,
	अणु  128, 0x1, 0x0, 2 पूर्ण,
	अणु  136, 0x1, 0x1, 2 पूर्ण,
	अणु  192, 0x2, 0x0, 2 पूर्ण,
	अणु  204, 0x2, 0x1, 2 पूर्ण,

	अणु  250, 0x2, 0x2, 1 पूर्ण,
	अणु  256, 0x3, 0x0, 1 पूर्ण,
	अणु  272, 0x3, 0x1, 1 पूर्ण,
	अणु  384, 0x4, 0x0, 1 पूर्ण,
	अणु  408, 0x4, 0x1, 1 पूर्ण,
	अणु  375, 0x4, 0x2, 1 पूर्ण,
	अणु  512, 0x5, 0x0, 1 पूर्ण,
	अणु  544, 0x5, 0x1, 1 पूर्ण,
	अणु  500, 0x5, 0x2, 1 पूर्ण,
	अणु  768, 0x6, 0x0, 1 पूर्ण,
	अणु  816, 0x6, 0x1, 1 पूर्ण,
	अणु  750, 0x6, 0x2, 1 पूर्ण,
	अणु 1024, 0x7, 0x0, 1 पूर्ण,
	अणु 1088, 0x7, 0x1, 1 पूर्ण,
	अणु 1000, 0x7, 0x2, 1 पूर्ण,
	अणु 1408, 0x8, 0x0, 1 पूर्ण,
	अणु 1496, 0x8, 0x1, 1 पूर्ण,
	अणु 1536, 0x9, 0x0, 1 पूर्ण,
	अणु 1632, 0x9, 0x1, 1 पूर्ण,
	अणु 1500, 0x9, 0x2, 1 पूर्ण,

	अणु  250, 0x2, 0x2, 2 पूर्ण,
	अणु  256, 0x3, 0x0, 2 पूर्ण,
	अणु  272, 0x3, 0x1, 2 पूर्ण,
	अणु  384, 0x4, 0x0, 2 पूर्ण,
	अणु  408, 0x4, 0x1, 2 पूर्ण,
	अणु  375, 0x4, 0x2, 2 पूर्ण,
	अणु  512, 0x5, 0x0, 2 पूर्ण,
	अणु  544, 0x5, 0x1, 2 पूर्ण,
	अणु  500, 0x5, 0x2, 2 पूर्ण,
	अणु  768, 0x6, 0x0, 2 पूर्ण,
	अणु  816, 0x6, 0x1, 2 पूर्ण,
	अणु  750, 0x6, 0x2, 2 पूर्ण,
	अणु 1024, 0x7, 0x0, 2 पूर्ण,
	अणु 1088, 0x7, 0x1, 2 पूर्ण,
	अणु 1000, 0x7, 0x2, 2 पूर्ण,
	अणु 1408, 0x8, 0x0, 2 पूर्ण,
	अणु 1496, 0x8, 0x1, 2 पूर्ण,
	अणु 1536, 0x9, 0x0, 2 पूर्ण,
	अणु 1632, 0x9, 0x1, 2 पूर्ण,
	अणु 1500, 0x9, 0x2, 2 पूर्ण,
पूर्ण;

/* CLK_SYS/BCLK ratios - multiplied by 10 due to .5s */
अटल काष्ठा अणु
	पूर्णांक ratio;
	पूर्णांक भाग;
पूर्ण bclk_भागs[] = अणु
	अणु  10,  0 पूर्ण,
	अणु  20,  2 पूर्ण,
	अणु  30,  3 पूर्ण,
	अणु  40,  4 पूर्ण,
	अणु  50,  5 पूर्ण,
	अणु  60,  7 पूर्ण,
	अणु  80,  8 पूर्ण,
	अणु 100,  9 पूर्ण,
	अणु 120, 11 पूर्ण,
	अणु 160, 12 पूर्ण,
	अणु 200, 13 पूर्ण,
	अणु 220, 14 पूर्ण,
	अणु 240, 15 पूर्ण,
	अणु 300, 17 पूर्ण,
	अणु 320, 18 पूर्ण,
	अणु 440, 19 पूर्ण,
	अणु 480, 20 पूर्ण,
पूर्ण;

/* Sample rates क्रम DSP */
अटल काष्ठा अणु
	पूर्णांक rate;
	पूर्णांक value;
पूर्ण sample_rates[] = अणु
	अणु  8000,  0 पूर्ण,
	अणु 11025,  1 पूर्ण,
	अणु 12000,  2 पूर्ण,
	अणु 16000,  3 पूर्ण,
	अणु 22050,  4 पूर्ण,
	अणु 24000,  5 पूर्ण,
	अणु 32000,  6 पूर्ण,
	अणु 44100,  7 पूर्ण,
	अणु 48000,  8 पूर्ण,
	अणु 88200,  9 पूर्ण,
	अणु 96000, 10 पूर्ण,
	अणु 0,      0 पूर्ण,
पूर्ण;

अटल पूर्णांक wm8903_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8903_priv *wm8903 = snd_soc_component_get_drvdata(component);
	पूर्णांक fs = params_rate(params);
	पूर्णांक bclk;
	पूर्णांक bclk_भाग;
	पूर्णांक i;
	पूर्णांक dsp_config;
	पूर्णांक clk_config;
	पूर्णांक best_val;
	पूर्णांक cur_val;
	पूर्णांक clk_sys;

	u16 aअगर1 = snd_soc_component_पढ़ो(component, WM8903_AUDIO_INTERFACE_1);
	u16 aअगर2 = snd_soc_component_पढ़ो(component, WM8903_AUDIO_INTERFACE_2);
	u16 aअगर3 = snd_soc_component_पढ़ो(component, WM8903_AUDIO_INTERFACE_3);
	u16 घड़ी0 = snd_soc_component_पढ़ो(component, WM8903_CLOCK_RATES_0);
	u16 घड़ी1 = snd_soc_component_पढ़ो(component, WM8903_CLOCK_RATES_1);
	u16 dac_digital1 = snd_soc_component_पढ़ो(component, WM8903_DAC_DIGITAL_1);

	/* Enable sloping stopband filter क्रम low sample rates */
	अगर (fs <= 24000)
		dac_digital1 |= WM8903_DAC_SB_FILT;
	अन्यथा
		dac_digital1 &= ~WM8903_DAC_SB_FILT;

	/* Configure sample rate logic क्रम DSP - choose nearest rate */
	dsp_config = 0;
	best_val = असल(sample_rates[dsp_config].rate - fs);
	क्रम (i = 1; i < ARRAY_SIZE(sample_rates); i++) अणु
		cur_val = असल(sample_rates[i].rate - fs);
		अगर (cur_val <= best_val) अणु
			dsp_config = i;
			best_val = cur_val;
		पूर्ण
	पूर्ण

	dev_dbg(component->dev, "DSP fs = %dHz\n", sample_rates[dsp_config].rate);
	घड़ी1 &= ~WM8903_SAMPLE_RATE_MASK;
	घड़ी1 |= sample_rates[dsp_config].value;

	aअगर1 &= ~WM8903_AIF_WL_MASK;
	bclk = 2 * fs;
	चयन (params_width(params)) अणु
	हाल 16:
		bclk *= 16;
		अवरोध;
	हाल 20:
		bclk *= 20;
		aअगर1 |= 0x4;
		अवरोध;
	हाल 24:
		bclk *= 24;
		aअगर1 |= 0x8;
		अवरोध;
	हाल 32:
		bclk *= 32;
		aअगर1 |= 0xc;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(component->dev, "MCLK = %dHz, target sample rate = %dHz\n",
		wm8903->sysclk, fs);

	/* We may not have an MCLK which allows us to generate exactly
	 * the घड़ी we want, particularly with USB derived inमाला_दो, so
	 * approximate.
	 */
	clk_config = 0;
	best_val = असल((wm8903->sysclk /
			(clk_sys_ratios[0].mclk_भाग *
			 clk_sys_ratios[0].भाग)) - fs);
	क्रम (i = 1; i < ARRAY_SIZE(clk_sys_ratios); i++) अणु
		cur_val = असल((wm8903->sysclk /
			       (clk_sys_ratios[i].mclk_भाग *
				clk_sys_ratios[i].भाग)) - fs);

		अगर (cur_val <= best_val) अणु
			clk_config = i;
			best_val = cur_val;
		पूर्ण
	पूर्ण

	अगर (clk_sys_ratios[clk_config].mclk_भाग == 2) अणु
		घड़ी0 |= WM8903_MCLKDIV2;
		clk_sys = wm8903->sysclk / 2;
	पूर्ण अन्यथा अणु
		घड़ी0 &= ~WM8903_MCLKDIV2;
		clk_sys = wm8903->sysclk;
	पूर्ण

	घड़ी1 &= ~(WM8903_CLK_SYS_RATE_MASK |
		    WM8903_CLK_SYS_MODE_MASK);
	घड़ी1 |= clk_sys_ratios[clk_config].rate << WM8903_CLK_SYS_RATE_SHIFT;
	घड़ी1 |= clk_sys_ratios[clk_config].mode << WM8903_CLK_SYS_MODE_SHIFT;

	dev_dbg(component->dev, "CLK_SYS_RATE=%x, CLK_SYS_MODE=%x div=%d\n",
		clk_sys_ratios[clk_config].rate,
		clk_sys_ratios[clk_config].mode,
		clk_sys_ratios[clk_config].भाग);

	dev_dbg(component->dev, "Actual CLK_SYS = %dHz\n", clk_sys);

	/* We may not get quite the right frequency अगर using
	 * approximate घड़ीs so look क्रम the बंदst match that is
	 * higher than the target (we need to ensure that there enough
	 * BCLKs to घड़ी out the samples).
	 */
	bclk_भाग = 0;
	i = 1;
	जबतक (i < ARRAY_SIZE(bclk_भागs)) अणु
		cur_val = ((clk_sys * 10) / bclk_भागs[i].ratio) - bclk;
		अगर (cur_val < 0) /* BCLK table is sorted */
			अवरोध;
		bclk_भाग = i;
		i++;
	पूर्ण

	aअगर2 &= ~WM8903_BCLK_DIV_MASK;
	aअगर3 &= ~WM8903_LRCLK_RATE_MASK;

	dev_dbg(component->dev, "BCLK ratio %d for %dHz - actual BCLK = %dHz\n",
		bclk_भागs[bclk_भाग].ratio / 10, bclk,
		(clk_sys * 10) / bclk_भागs[bclk_भाग].ratio);

	aअगर2 |= bclk_भागs[bclk_भाग].भाग;
	aअगर3 |= bclk / fs;

	wm8903->fs = params_rate(params);
	wm8903_set_deemph(component);

	snd_soc_component_ग_लिखो(component, WM8903_CLOCK_RATES_0, घड़ी0);
	snd_soc_component_ग_लिखो(component, WM8903_CLOCK_RATES_1, घड़ी1);
	snd_soc_component_ग_लिखो(component, WM8903_AUDIO_INTERFACE_1, aअगर1);
	snd_soc_component_ग_लिखो(component, WM8903_AUDIO_INTERFACE_2, aअगर2);
	snd_soc_component_ग_लिखो(component, WM8903_AUDIO_INTERFACE_3, aअगर3);
	snd_soc_component_ग_लिखो(component, WM8903_DAC_DIGITAL_1, dac_digital1);

	वापस 0;
पूर्ण

/**
 * wm8903_mic_detect - Enable microphone detection via the WM8903 IRQ
 *
 * @component:  WM8903 component
 * @jack:   jack to report detection events on
 * @det:    value to report क्रम presence detection
 * @shrt:   value to report क्रम लघु detection
 *
 * Enable microphone detection via IRQ on the WM8903.  If GPIOs are
 * being used to bring out संकेतs to the processor then only platक्रमm
 * data configuration is needed क्रम WM8903 and processor GPIOs should
 * be configured using snd_soc_jack_add_gpios() instead.
 *
 * The current threasholds क्रम detection should be configured using
 * micdet_cfg in the platक्रमm data.  Using this function will क्रमce on
 * the microphone bias क्रम the device.
 */
पूर्णांक wm8903_mic_detect(काष्ठा snd_soc_component *component, काष्ठा snd_soc_jack *jack,
		      पूर्णांक det, पूर्णांक shrt)
अणु
	काष्ठा wm8903_priv *wm8903 = snd_soc_component_get_drvdata(component);
	पूर्णांक irq_mask = WM8903_MICDET_EINT | WM8903_MICSHRT_EINT;

	dev_dbg(component->dev, "Enabling microphone detection: %x %x\n",
		det, shrt);

	/* Store the configuration */
	wm8903->mic_jack = jack;
	wm8903->mic_det = det;
	wm8903->mic_लघु = shrt;

	/* Enable पूर्णांकerrupts we've got a report configured क्रम */
	अगर (det)
		irq_mask &= ~WM8903_MICDET_EINT;
	अगर (shrt)
		irq_mask &= ~WM8903_MICSHRT_EINT;

	snd_soc_component_update_bits(component, WM8903_INTERRUPT_STATUS_1_MASK,
			    WM8903_MICDET_EINT | WM8903_MICSHRT_EINT,
			    irq_mask);

	अगर (det || shrt) अणु
		/* Enable mic detection, this may not have been set through
		 * platक्रमm data (eg, अगर the शेषs are OK). */
		snd_soc_component_update_bits(component, WM8903_WRITE_SEQUENCER_0,
				    WM8903_WSEQ_ENA, WM8903_WSEQ_ENA);
		snd_soc_component_update_bits(component, WM8903_MIC_BIAS_CONTROL_0,
				    WM8903_MICDET_ENA, WM8903_MICDET_ENA);
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component, WM8903_MIC_BIAS_CONTROL_0,
				    WM8903_MICDET_ENA, 0);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm8903_mic_detect);

अटल irqवापस_t wm8903_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm8903_priv *wm8903 = data;
	पूर्णांक mic_report, ret;
	अचिन्हित पूर्णांक पूर्णांक_val, mask, पूर्णांक_pol;

	ret = regmap_पढ़ो(wm8903->regmap, WM8903_INTERRUPT_STATUS_1_MASK,
			  &mask);
	अगर (ret != 0) अणु
		dev_err(wm8903->dev, "Failed to read IRQ mask: %d\n", ret);
		वापस IRQ_NONE;
	पूर्ण

	ret = regmap_पढ़ो(wm8903->regmap, WM8903_INTERRUPT_STATUS_1, &पूर्णांक_val);
	अगर (ret != 0) अणु
		dev_err(wm8903->dev, "Failed to read IRQ status: %d\n", ret);
		वापस IRQ_NONE;
	पूर्ण

	पूर्णांक_val &= ~mask;

	अगर (पूर्णांक_val & WM8903_WSEQ_BUSY_EINT) अणु
		dev_warn(wm8903->dev, "Write sequencer done\n");
	पूर्ण

	/*
	 * The rest is microphone jack detection.  We need to manually
	 * invert the polarity of the पूर्णांकerrupt after each event - to
	 * simplअगरy the code keep track of the last state we reported
	 * and just invert the relevant bits in both the report and
	 * the polarity रेजिस्टर.
	 */
	mic_report = wm8903->mic_last_report;
	ret = regmap_पढ़ो(wm8903->regmap, WM8903_INTERRUPT_POLARITY_1,
			  &पूर्णांक_pol);
	अगर (ret != 0) अणु
		dev_err(wm8903->dev, "Failed to read interrupt polarity: %d\n",
			ret);
		वापस IRQ_HANDLED;
	पूर्ण

#अगर_अघोषित CONFIG_SND_SOC_WM8903_MODULE
	अगर (पूर्णांक_val & (WM8903_MICSHRT_EINT | WM8903_MICDET_EINT))
		trace_snd_soc_jack_irq(dev_name(wm8903->dev));
#पूर्ण_अगर

	अगर (पूर्णांक_val & WM8903_MICSHRT_EINT) अणु
		dev_dbg(wm8903->dev, "Microphone short (pol=%x)\n", पूर्णांक_pol);

		mic_report ^= wm8903->mic_लघु;
		पूर्णांक_pol ^= WM8903_MICSHRT_INV;
	पूर्ण

	अगर (पूर्णांक_val & WM8903_MICDET_EINT) अणु
		dev_dbg(wm8903->dev, "Microphone detect (pol=%x)\n", पूर्णांक_pol);

		mic_report ^= wm8903->mic_det;
		पूर्णांक_pol ^= WM8903_MICDET_INV;

		msleep(wm8903->mic_delay);
	पूर्ण

	regmap_update_bits(wm8903->regmap, WM8903_INTERRUPT_POLARITY_1,
			   WM8903_MICSHRT_INV | WM8903_MICDET_INV, पूर्णांक_pol);

	snd_soc_jack_report(wm8903->mic_jack, mic_report,
			    wm8903->mic_लघु | wm8903->mic_det);

	wm8903->mic_last_report = mic_report;

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा WM8903_PLAYBACK_RATES (SNDRV_PCM_RATE_8000 |\
			       SNDRV_PCM_RATE_11025 |	\
			       SNDRV_PCM_RATE_16000 |	\
			       SNDRV_PCM_RATE_22050 |	\
			       SNDRV_PCM_RATE_32000 |	\
			       SNDRV_PCM_RATE_44100 |	\
			       SNDRV_PCM_RATE_48000 |	\
			       SNDRV_PCM_RATE_88200 |	\
			       SNDRV_PCM_RATE_96000)

#घोषणा WM8903_CAPTURE_RATES (SNDRV_PCM_RATE_8000 |\
			      SNDRV_PCM_RATE_11025 |	\
			      SNDRV_PCM_RATE_16000 |	\
			      SNDRV_PCM_RATE_22050 |	\
			      SNDRV_PCM_RATE_32000 |	\
			      SNDRV_PCM_RATE_44100 |	\
			      SNDRV_PCM_RATE_48000)

#घोषणा WM8903_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
			SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8903_dai_ops = अणु
	.hw_params	= wm8903_hw_params,
	.mute_stream	= wm8903_mute,
	.set_fmt	= wm8903_set_dai_fmt,
	.set_sysclk	= wm8903_set_dai_sysclk,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8903_dai = अणु
	.name = "wm8903-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = WM8903_PLAYBACK_RATES,
		.क्रमmats = WM8903_FORMATS,
	पूर्ण,
	.capture = अणु
		 .stream_name = "Capture",
		 .channels_min = 2,
		 .channels_max = 2,
		 .rates = WM8903_CAPTURE_RATES,
		 .क्रमmats = WM8903_FORMATS,
	 पूर्ण,
	.ops = &wm8903_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक wm8903_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8903_priv *wm8903 = snd_soc_component_get_drvdata(component);

	regcache_sync(wm8903->regmap);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_GPIOLIB
अटल पूर्णांक wm8903_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	अगर (offset >= WM8903_NUM_GPIO)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8903_gpio_direction_in(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा wm8903_priv *wm8903 = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक mask, val;
	पूर्णांक ret;

	mask = WM8903_GP1_FN_MASK | WM8903_GP1_सूची_MASK;
	val = (WM8903_GPn_FN_GPIO_INPUT << WM8903_GP1_FN_SHIFT) |
		WM8903_GP1_सूची;

	ret = regmap_update_bits(wm8903->regmap,
				 WM8903_GPIO_CONTROL_1 + offset, mask, val);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8903_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा wm8903_priv *wm8903 = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक reg;

	regmap_पढ़ो(wm8903->regmap, WM8903_GPIO_CONTROL_1 + offset, &reg);

	वापस !!((reg & WM8903_GP1_LVL_MASK) >> WM8903_GP1_LVL_SHIFT);
पूर्ण

अटल पूर्णांक wm8903_gpio_direction_out(काष्ठा gpio_chip *chip,
				     अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा wm8903_priv *wm8903 = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक mask, val;
	पूर्णांक ret;

	mask = WM8903_GP1_FN_MASK | WM8903_GP1_सूची_MASK | WM8903_GP1_LVL_MASK;
	val = (WM8903_GPn_FN_GPIO_OUTPUT << WM8903_GP1_FN_SHIFT) |
		(value << WM8903_GP2_LVL_SHIFT);

	ret = regmap_update_bits(wm8903->regmap,
				 WM8903_GPIO_CONTROL_1 + offset, mask, val);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम wm8903_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा wm8903_priv *wm8903 = gpiochip_get_data(chip);

	regmap_update_bits(wm8903->regmap, WM8903_GPIO_CONTROL_1 + offset,
			   WM8903_GP1_LVL_MASK,
			   !!value << WM8903_GP1_LVL_SHIFT);
पूर्ण

अटल स्थिर काष्ठा gpio_chip wm8903_ढाँचा_chip = अणु
	.label			= "wm8903",
	.owner			= THIS_MODULE,
	.request		= wm8903_gpio_request,
	.direction_input	= wm8903_gpio_direction_in,
	.get			= wm8903_gpio_get,
	.direction_output	= wm8903_gpio_direction_out,
	.set			= wm8903_gpio_set,
	.can_sleep		= 1,
पूर्ण;

अटल व्योम wm8903_init_gpio(काष्ठा wm8903_priv *wm8903)
अणु
	काष्ठा wm8903_platक्रमm_data *pdata = wm8903->pdata;
	पूर्णांक ret;

	wm8903->gpio_chip = wm8903_ढाँचा_chip;
	wm8903->gpio_chip.ngpio = WM8903_NUM_GPIO;
	wm8903->gpio_chip.parent = wm8903->dev;

	अगर (pdata->gpio_base)
		wm8903->gpio_chip.base = pdata->gpio_base;
	अन्यथा
		wm8903->gpio_chip.base = -1;

	ret = gpiochip_add_data(&wm8903->gpio_chip, wm8903);
	अगर (ret != 0)
		dev_err(wm8903->dev, "Failed to add GPIOs: %d\n", ret);
पूर्ण

अटल व्योम wm8903_मुक्त_gpio(काष्ठा wm8903_priv *wm8903)
अणु
	gpiochip_हटाओ(&wm8903->gpio_chip);
पूर्ण
#अन्यथा
अटल व्योम wm8903_init_gpio(काष्ठा wm8903_priv *wm8903)
अणु
पूर्ण

अटल व्योम wm8903_मुक्त_gpio(काष्ठा wm8903_priv *wm8903)
अणु
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8903 = अणु
	.resume			= wm8903_resume,
	.set_bias_level		= wm8903_set_bias_level,
	.seq_notअगरier		= wm8903_seq_notअगरier,
	.controls		= wm8903_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8903_snd_controls),
	.dapm_widमाला_लो		= wm8903_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8903_dapm_widमाला_लो),
	.dapm_routes		= wm8903_पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(wm8903_पूर्णांकercon),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm8903_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,

	.max_रेजिस्टर = WM8903_MAX_REGISTER,
	.अस्थिर_reg = wm8903_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = wm8903_पढ़ोable_रेजिस्टर,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = wm8903_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8903_reg_शेषs),
पूर्ण;

अटल पूर्णांक wm8903_set_pdata_irq_trigger(काष्ठा i2c_client *i2c,
					काष्ठा wm8903_platक्रमm_data *pdata)
अणु
	काष्ठा irq_data *irq_data = irq_get_irq_data(i2c->irq);
	अगर (!irq_data) अणु
		dev_err(&i2c->dev, "Invalid IRQ: %d\n",
			i2c->irq);
		वापस -EINVAL;
	पूर्ण

	चयन (irqd_get_trigger_type(irq_data)) अणु
	हाल IRQ_TYPE_NONE:
	शेष:
		/*
		* We assume the controller imposes no restrictions,
		* so we are able to select active-high
		*/
		fallthrough;
	हाल IRQ_TYPE_LEVEL_HIGH:
		pdata->irq_active_low = false;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		pdata->irq_active_low = true;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8903_set_pdata_from_of(काष्ठा i2c_client *i2c,
				    काष्ठा wm8903_platक्रमm_data *pdata)
अणु
	स्थिर काष्ठा device_node *np = i2c->dev.of_node;
	u32 val32;
	पूर्णांक i;

	अगर (of_property_पढ़ो_u32(np, "micdet-cfg", &val32) >= 0)
		pdata->micdet_cfg = val32;

	अगर (of_property_पढ़ो_u32(np, "micdet-delay", &val32) >= 0)
		pdata->micdet_delay = val32;

	अगर (of_property_पढ़ो_u32_array(np, "gpio-cfg", pdata->gpio_cfg,
				       ARRAY_SIZE(pdata->gpio_cfg)) >= 0) अणु
		/*
		 * In device tree: 0 means "write 0",
		 * 0xffffffff means "don't touch".
		 *
		 * In platक्रमm data: 0 means "don't touch",
		 * 0x8000 means "write 0".
		 *
		 * Note: WM8903_GPIO_CONFIG_ZERO == 0x8000.
		 *
		 *  Convert from DT to pdata representation here,
		 * so no other code needs to change.
		 */
		क्रम (i = 0; i < ARRAY_SIZE(pdata->gpio_cfg); i++) अणु
			अगर (pdata->gpio_cfg[i] == 0) अणु
				pdata->gpio_cfg[i] = WM8903_GPIO_CONFIG_ZERO;
			पूर्ण अन्यथा अगर (pdata->gpio_cfg[i] == 0xffffffff) अणु
				pdata->gpio_cfg[i] = 0;
			पूर्ण अन्यथा अगर (pdata->gpio_cfg[i] > 0x7fff) अणु
				dev_err(&i2c->dev, "Invalid gpio-cfg[%d] %x\n",
					i, pdata->gpio_cfg[i]);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8903_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8903_platक्रमm_data *pdata = dev_get_platdata(&i2c->dev);
	काष्ठा wm8903_priv *wm8903;
	पूर्णांक trigger;
	bool mic_gpio = false;
	अचिन्हित पूर्णांक val, irq_pol;
	पूर्णांक ret, i;

	wm8903 = devm_kzalloc(&i2c->dev, माप(*wm8903), GFP_KERNEL);
	अगर (wm8903 == शून्य)
		वापस -ENOMEM;

	mutex_init(&wm8903->lock);
	wm8903->dev = &i2c->dev;

	wm8903->regmap = devm_regmap_init_i2c(i2c, &wm8903_regmap);
	अगर (IS_ERR(wm8903->regmap)) अणु
		ret = PTR_ERR(wm8903->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(i2c, wm8903);

	/* If no platक्रमm data was supplied, create storage क्रम शेषs */
	अगर (pdata) अणु
		wm8903->pdata = pdata;
	पूर्ण अन्यथा अणु
		wm8903->pdata = devm_kzalloc(&i2c->dev, माप(*wm8903->pdata),
					     GFP_KERNEL);
		अगर (!wm8903->pdata)
			वापस -ENOMEM;

		अगर (i2c->irq) अणु
			ret = wm8903_set_pdata_irq_trigger(i2c, wm8903->pdata);
			अगर (ret != 0)
				वापस ret;
		पूर्ण

		अगर (i2c->dev.of_node) अणु
			ret = wm8903_set_pdata_from_of(i2c, wm8903->pdata);
			अगर (ret != 0)
				वापस ret;
		पूर्ण
	पूर्ण

	pdata = wm8903->pdata;

	क्रम (i = 0; i < ARRAY_SIZE(wm8903->supplies); i++)
		wm8903->supplies[i].supply = wm8903_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev, ARRAY_SIZE(wm8903->supplies),
				      wm8903->supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8903->supplies),
				    wm8903->supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(wm8903->regmap, WM8903_SW_RESET_AND_ID, &val);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to read chip ID: %d\n", ret);
		जाओ err;
	पूर्ण
	अगर (val != 0x8903) अणु
		dev_err(&i2c->dev, "Device with ID %x is not a WM8903\n", val);
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	ret = regmap_पढ़ो(wm8903->regmap, WM8903_REVISION_NUMBER, &val);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to read chip revision: %d\n", ret);
		जाओ err;
	पूर्ण
	dev_info(&i2c->dev, "WM8903 revision %c\n",
		 (val & WM8903_CHIP_REV_MASK) + 'A');

	/* Reset the device */
	regmap_ग_लिखो(wm8903->regmap, WM8903_SW_RESET_AND_ID, 0x8903);

	wm8903_init_gpio(wm8903);

	/* Set up GPIO pin state, detect अगर any are MIC detect outमाला_दो */
	क्रम (i = 0; i < ARRAY_SIZE(pdata->gpio_cfg); i++) अणु
		अगर ((!pdata->gpio_cfg[i]) ||
		    (pdata->gpio_cfg[i] > WM8903_GPIO_CONFIG_ZERO))
			जारी;

		regmap_ग_लिखो(wm8903->regmap, WM8903_GPIO_CONTROL_1 + i,
				pdata->gpio_cfg[i] & 0x7fff);

		val = (pdata->gpio_cfg[i] & WM8903_GP1_FN_MASK)
			>> WM8903_GP1_FN_SHIFT;

		चयन (val) अणु
		हाल WM8903_GPn_FN_MICBIAS_CURRENT_DETECT:
		हाल WM8903_GPn_FN_MICBIAS_SHORT_DETECT:
			mic_gpio = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* Set up microphone detection */
	regmap_ग_लिखो(wm8903->regmap, WM8903_MIC_BIAS_CONTROL_0,
		     pdata->micdet_cfg);

	/* Microphone detection needs the WSEQ घड़ी */
	अगर (pdata->micdet_cfg)
		regmap_update_bits(wm8903->regmap, WM8903_WRITE_SEQUENCER_0,
				   WM8903_WSEQ_ENA, WM8903_WSEQ_ENA);

	/* If microphone detection is enabled by pdata but
	 * detected via IRQ then पूर्णांकerrupts can be lost beक्रमe
	 * the machine driver has set up microphone detection
	 * IRQs as the IRQs are clear on पढ़ो.  The detection
	 * will be enabled when the machine driver configures.
	 */
	WARN_ON(!mic_gpio && (pdata->micdet_cfg & WM8903_MICDET_ENA));

	wm8903->mic_delay = pdata->micdet_delay;

	अगर (i2c->irq) अणु
		अगर (pdata->irq_active_low) अणु
			trigger = IRQF_TRIGGER_LOW;
			irq_pol = WM8903_IRQ_POL;
		पूर्ण अन्यथा अणु
			trigger = IRQF_TRIGGER_HIGH;
			irq_pol = 0;
		पूर्ण

		regmap_update_bits(wm8903->regmap, WM8903_INTERRUPT_CONTROL,
				   WM8903_IRQ_POL, irq_pol);

		ret = request_thपढ़ोed_irq(i2c->irq, शून्य, wm8903_irq,
					   trigger | IRQF_ONESHOT,
					   "wm8903", wm8903);
		अगर (ret != 0) अणु
			dev_err(wm8903->dev, "Failed to request IRQ: %d\n",
				ret);
			वापस ret;
		पूर्ण

		/* Enable ग_लिखो sequencer पूर्णांकerrupts */
		regmap_update_bits(wm8903->regmap,
				   WM8903_INTERRUPT_STATUS_1_MASK,
				   WM8903_IM_WSEQ_BUSY_EINT, 0);
	पूर्ण

	/* Latch volume update bits */
	regmap_update_bits(wm8903->regmap, WM8903_ADC_DIGITAL_VOLUME_LEFT,
			   WM8903_ADCVU, WM8903_ADCVU);
	regmap_update_bits(wm8903->regmap, WM8903_ADC_DIGITAL_VOLUME_RIGHT,
			   WM8903_ADCVU, WM8903_ADCVU);

	regmap_update_bits(wm8903->regmap, WM8903_DAC_DIGITAL_VOLUME_LEFT,
			   WM8903_DACVU, WM8903_DACVU);
	regmap_update_bits(wm8903->regmap, WM8903_DAC_DIGITAL_VOLUME_RIGHT,
			   WM8903_DACVU, WM8903_DACVU);

	regmap_update_bits(wm8903->regmap, WM8903_ANALOGUE_OUT1_LEFT,
			   WM8903_HPOUTVU, WM8903_HPOUTVU);
	regmap_update_bits(wm8903->regmap, WM8903_ANALOGUE_OUT1_RIGHT,
			   WM8903_HPOUTVU, WM8903_HPOUTVU);

	regmap_update_bits(wm8903->regmap, WM8903_ANALOGUE_OUT2_LEFT,
			   WM8903_LINEOUTVU, WM8903_LINEOUTVU);
	regmap_update_bits(wm8903->regmap, WM8903_ANALOGUE_OUT2_RIGHT,
			   WM8903_LINEOUTVU, WM8903_LINEOUTVU);

	regmap_update_bits(wm8903->regmap, WM8903_ANALOGUE_OUT3_LEFT,
			   WM8903_SPKVU, WM8903_SPKVU);
	regmap_update_bits(wm8903->regmap, WM8903_ANALOGUE_OUT3_RIGHT,
			   WM8903_SPKVU, WM8903_SPKVU);

	/* Enable DAC soft mute by शेष */
	regmap_update_bits(wm8903->regmap, WM8903_DAC_DIGITAL_1,
			   WM8903_DAC_MUTEMODE | WM8903_DAC_MUTE,
			   WM8903_DAC_MUTEMODE | WM8903_DAC_MUTE);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_wm8903, &wm8903_dai, 1);
	अगर (ret != 0)
		जाओ err;

	वापस 0;
err:
	regulator_bulk_disable(ARRAY_SIZE(wm8903->supplies),
			       wm8903->supplies);
	वापस ret;
पूर्ण

अटल पूर्णांक wm8903_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा wm8903_priv *wm8903 = i2c_get_clientdata(client);

	regulator_bulk_disable(ARRAY_SIZE(wm8903->supplies),
			       wm8903->supplies);
	अगर (client->irq)
		मुक्त_irq(client->irq, wm8903);
	wm8903_मुक्त_gpio(wm8903);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id wm8903_of_match[] = अणु
	अणु .compatible = "wlf,wm8903", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, wm8903_of_match);

अटल स्थिर काष्ठा i2c_device_id wm8903_i2c_id[] = अणु
	अणु "wm8903", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8903_i2c_id);

अटल काष्ठा i2c_driver wm8903_i2c_driver = अणु
	.driver = अणु
		.name = "wm8903",
		.of_match_table = wm8903_of_match,
	पूर्ण,
	.probe =    wm8903_i2c_probe,
	.हटाओ =   wm8903_i2c_हटाओ,
	.id_table = wm8903_i2c_id,
पूर्ण;

module_i2c_driver(wm8903_i2c_driver);

MODULE_DESCRIPTION("ASoC WM8903 driver");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.cm>");
MODULE_LICENSE("GPL");
