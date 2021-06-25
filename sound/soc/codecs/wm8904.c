<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8904.c  --  WM8904 ALSA SoC Audio driver
 *
 * Copyright 2009-12 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/wm8904.h>

#समावेश "wm8904.h"

क्रमागत wm8904_type अणु
	WM8904,
	WM8912,
पूर्ण;

#घोषणा WM8904_NUM_DCS_CHANNELS 4

#घोषणा WM8904_NUM_SUPPLIES 5
अटल स्थिर अक्षर *wm8904_supply_names[WM8904_NUM_SUPPLIES] = अणु
	"DCVDD",
	"DBVDD",
	"AVDD",
	"CPVDD",
	"MICVDD",
पूर्ण;

/* codec निजी data */
काष्ठा wm8904_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा clk *mclk;

	क्रमागत wm8904_type devtype;

	काष्ठा regulator_bulk_data supplies[WM8904_NUM_SUPPLIES];

	काष्ठा wm8904_pdata *pdata;

	पूर्णांक deemph;

	/* Platक्रमm provided DRC configuration */
	स्थिर अक्षर **drc_texts;
	पूर्णांक drc_cfg;
	काष्ठा soc_क्रमागत drc_क्रमागत;

	/* Platक्रमm provided ReTune mobile configuration */
	पूर्णांक num_retune_mobile_texts;
	स्थिर अक्षर **retune_mobile_texts;
	पूर्णांक retune_mobile_cfg;
	काष्ठा soc_क्रमागत retune_mobile_क्रमागत;

	/* FLL setup */
	पूर्णांक fll_src;
	पूर्णांक fll_fref;
	पूर्णांक fll_fout;

	/* Clocking configuration */
	अचिन्हित पूर्णांक mclk_rate;
	पूर्णांक sysclk_src;
	अचिन्हित पूर्णांक sysclk_rate;

	पूर्णांक tdm_width;
	पूर्णांक tdm_slots;
	पूर्णांक bclk;
	पूर्णांक fs;

	/* DC servo configuration - cached offset values */
	पूर्णांक dcs_state[WM8904_NUM_DCS_CHANNELS];
पूर्ण;

अटल स्थिर काष्ठा reg_शेष wm8904_reg_शेषs[] = अणु
	अणु 4,   0x0018 पूर्ण,     /* R4   - Bias Control 0 */
	अणु 5,   0x0000 पूर्ण,     /* R5   - VMID Control 0 */
	अणु 6,   0x0000 पूर्ण,     /* R6   - Mic Bias Control 0 */
	अणु 7,   0x0000 पूर्ण,     /* R7   - Mic Bias Control 1 */
	अणु 8,   0x0001 पूर्ण,     /* R8   - Analogue DAC 0 */
	अणु 9,   0x9696 पूर्ण,     /* R9   - mic Filter Control */
	अणु 10,  0x0001 पूर्ण,     /* R10  - Analogue ADC 0 */
	अणु 12,  0x0000 पूर्ण,     /* R12  - Power Management 0 */
	अणु 14,  0x0000 पूर्ण,     /* R14  - Power Management 2 */
	अणु 15,  0x0000 पूर्ण,     /* R15  - Power Management 3 */
	अणु 18,  0x0000 पूर्ण,     /* R18  - Power Management 6 */
	अणु 20,  0x945E पूर्ण,     /* R20  - Clock Rates 0 */
	अणु 21,  0x0C05 पूर्ण,     /* R21  - Clock Rates 1 */
	अणु 22,  0x0006 पूर्ण,     /* R22  - Clock Rates 2 */
	अणु 24,  0x0050 पूर्ण,     /* R24  - Audio Interface 0 */
	अणु 25,  0x000A पूर्ण,     /* R25  - Audio Interface 1 */
	अणु 26,  0x00E4 पूर्ण,     /* R26  - Audio Interface 2 */
	अणु 27,  0x0040 पूर्ण,     /* R27  - Audio Interface 3 */
	अणु 30,  0x00C0 पूर्ण,     /* R30  - DAC Digital Volume Left */
	अणु 31,  0x00C0 पूर्ण,     /* R31  - DAC Digital Volume Right */
	अणु 32,  0x0000 पूर्ण,     /* R32  - DAC Digital 0 */
	अणु 33,  0x0008 पूर्ण,     /* R33  - DAC Digital 1 */
	अणु 36,  0x00C0 पूर्ण,     /* R36  - ADC Digital Volume Left */
	अणु 37,  0x00C0 पूर्ण,     /* R37  - ADC Digital Volume Right */
	अणु 38,  0x0010 पूर्ण,     /* R38  - ADC Digital 0 */
	अणु 39,  0x0000 पूर्ण,     /* R39  - Digital Microphone 0 */
	अणु 40,  0x01AF पूर्ण,     /* R40  - DRC 0 */
	अणु 41,  0x3248 पूर्ण,     /* R41  - DRC 1 */
	अणु 42,  0x0000 पूर्ण,     /* R42  - DRC 2 */
	अणु 43,  0x0000 पूर्ण,     /* R43  - DRC 3 */
	अणु 44,  0x0085 पूर्ण,     /* R44  - Analogue Left Input 0 */
	अणु 45,  0x0085 पूर्ण,     /* R45  - Analogue Right Input 0 */
	अणु 46,  0x0044 पूर्ण,     /* R46  - Analogue Left Input 1 */
	अणु 47,  0x0044 पूर्ण,     /* R47  - Analogue Right Input 1 */
	अणु 57,  0x002D पूर्ण,     /* R57  - Analogue OUT1 Left */
	अणु 58,  0x002D पूर्ण,     /* R58  - Analogue OUT1 Right */
	अणु 59,  0x0039 पूर्ण,     /* R59  - Analogue OUT2 Left */
	अणु 60,  0x0039 पूर्ण,     /* R60  - Analogue OUT2 Right */
	अणु 61,  0x0000 पूर्ण,     /* R61  - Analogue OUT12 ZC */
	अणु 67,  0x0000 पूर्ण,     /* R67  - DC Servo 0 */
	अणु 69,  0xAAAA पूर्ण,     /* R69  - DC Servo 2 */
	अणु 71,  0xAAAA पूर्ण,     /* R71  - DC Servo 4 */
	अणु 72,  0xAAAA पूर्ण,     /* R72  - DC Servo 5 */
	अणु 90,  0x0000 पूर्ण,     /* R90  - Analogue HP 0 */
	अणु 94,  0x0000 पूर्ण,     /* R94  - Analogue Lineout 0 */
	अणु 98,  0x0000 पूर्ण,     /* R98  - Charge Pump 0 */
	अणु 104, 0x0004 पूर्ण,     /* R104 - Class W 0 */
	अणु 108, 0x0000 पूर्ण,     /* R108 - Write Sequencer 0 */
	अणु 109, 0x0000 पूर्ण,     /* R109 - Write Sequencer 1 */
	अणु 110, 0x0000 पूर्ण,     /* R110 - Write Sequencer 2 */
	अणु 111, 0x0000 पूर्ण,     /* R111 - Write Sequencer 3 */
	अणु 112, 0x0000 पूर्ण,     /* R112 - Write Sequencer 4 */
	अणु 116, 0x0000 पूर्ण,     /* R116 - FLL Control 1 */
	अणु 117, 0x0007 पूर्ण,     /* R117 - FLL Control 2 */
	अणु 118, 0x0000 पूर्ण,     /* R118 - FLL Control 3 */
	अणु 119, 0x2EE0 पूर्ण,     /* R119 - FLL Control 4 */
	अणु 120, 0x0004 पूर्ण,     /* R120 - FLL Control 5 */
	अणु 121, 0x0014 पूर्ण,     /* R121 - GPIO Control 1 */
	अणु 122, 0x0010 पूर्ण,     /* R122 - GPIO Control 2 */
	अणु 123, 0x0010 पूर्ण,     /* R123 - GPIO Control 3 */
	अणु 124, 0x0000 पूर्ण,     /* R124 - GPIO Control 4 */
	अणु 126, 0x0000 पूर्ण,     /* R126 - Digital Pulls */
	अणु 128, 0xFFFF पूर्ण,     /* R128 - Interrupt Status Mask */
	अणु 129, 0x0000 पूर्ण,     /* R129 - Interrupt Polarity */
	अणु 130, 0x0000 पूर्ण,     /* R130 - Interrupt Debounce */
	अणु 134, 0x0000 पूर्ण,     /* R134 - EQ1 */
	अणु 135, 0x000C पूर्ण,     /* R135 - EQ2 */
	अणु 136, 0x000C पूर्ण,     /* R136 - EQ3 */
	अणु 137, 0x000C पूर्ण,     /* R137 - EQ4 */
	अणु 138, 0x000C पूर्ण,     /* R138 - EQ5 */
	अणु 139, 0x000C पूर्ण,     /* R139 - EQ6 */
	अणु 140, 0x0FCA पूर्ण,     /* R140 - EQ7 */
	अणु 141, 0x0400 पूर्ण,     /* R141 - EQ8 */
	अणु 142, 0x00D8 पूर्ण,     /* R142 - EQ9 */
	अणु 143, 0x1EB5 पूर्ण,     /* R143 - EQ10 */
	अणु 144, 0xF145 पूर्ण,     /* R144 - EQ11 */
	अणु 145, 0x0B75 पूर्ण,     /* R145 - EQ12 */
	अणु 146, 0x01C5 पूर्ण,     /* R146 - EQ13 */
	अणु 147, 0x1C58 पूर्ण,     /* R147 - EQ14 */
	अणु 148, 0xF373 पूर्ण,     /* R148 - EQ15 */
	अणु 149, 0x0A54 पूर्ण,     /* R149 - EQ16 */
	अणु 150, 0x0558 पूर्ण,     /* R150 - EQ17 */
	अणु 151, 0x168E पूर्ण,     /* R151 - EQ18 */
	अणु 152, 0xF829 पूर्ण,     /* R152 - EQ19 */
	अणु 153, 0x07AD पूर्ण,     /* R153 - EQ20 */
	अणु 154, 0x1103 पूर्ण,     /* R154 - EQ21 */
	अणु 155, 0x0564 पूर्ण,     /* R155 - EQ22 */
	अणु 156, 0x0559 पूर्ण,     /* R156 - EQ23 */
	अणु 157, 0x4000 पूर्ण,     /* R157 - EQ24 */
	अणु 161, 0x0000 पूर्ण,     /* R161 - Control Interface Test 1 */
	अणु 204, 0x0000 पूर्ण,     /* R204 - Analogue Output Bias 0 */
	अणु 247, 0x0000 पूर्ण,     /* R247 - FLL NCO Test 0 */
	अणु 248, 0x0019 पूर्ण,     /* R248 - FLL NCO Test 1 */
पूर्ण;

अटल bool wm8904_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8904_SW_RESET_AND_ID:
	हाल WM8904_REVISION:
	हाल WM8904_DC_SERVO_1:
	हाल WM8904_DC_SERVO_6:
	हाल WM8904_DC_SERVO_7:
	हाल WM8904_DC_SERVO_8:
	हाल WM8904_DC_SERVO_9:
	हाल WM8904_DC_SERVO_READBACK_0:
	हाल WM8904_INTERRUPT_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool wm8904_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8904_SW_RESET_AND_ID:
	हाल WM8904_REVISION:
	हाल WM8904_BIAS_CONTROL_0:
	हाल WM8904_VMID_CONTROL_0:
	हाल WM8904_MIC_BIAS_CONTROL_0:
	हाल WM8904_MIC_BIAS_CONTROL_1:
	हाल WM8904_ANALOGUE_DAC_0:
	हाल WM8904_MIC_FILTER_CONTROL:
	हाल WM8904_ANALOGUE_ADC_0:
	हाल WM8904_POWER_MANAGEMENT_0:
	हाल WM8904_POWER_MANAGEMENT_2:
	हाल WM8904_POWER_MANAGEMENT_3:
	हाल WM8904_POWER_MANAGEMENT_6:
	हाल WM8904_CLOCK_RATES_0:
	हाल WM8904_CLOCK_RATES_1:
	हाल WM8904_CLOCK_RATES_2:
	हाल WM8904_AUDIO_INTERFACE_0:
	हाल WM8904_AUDIO_INTERFACE_1:
	हाल WM8904_AUDIO_INTERFACE_2:
	हाल WM8904_AUDIO_INTERFACE_3:
	हाल WM8904_DAC_DIGITAL_VOLUME_LEFT:
	हाल WM8904_DAC_DIGITAL_VOLUME_RIGHT:
	हाल WM8904_DAC_DIGITAL_0:
	हाल WM8904_DAC_DIGITAL_1:
	हाल WM8904_ADC_DIGITAL_VOLUME_LEFT:
	हाल WM8904_ADC_DIGITAL_VOLUME_RIGHT:
	हाल WM8904_ADC_DIGITAL_0:
	हाल WM8904_DIGITAL_MICROPHONE_0:
	हाल WM8904_DRC_0:
	हाल WM8904_DRC_1:
	हाल WM8904_DRC_2:
	हाल WM8904_DRC_3:
	हाल WM8904_ANALOGUE_LEFT_INPUT_0:
	हाल WM8904_ANALOGUE_RIGHT_INPUT_0:
	हाल WM8904_ANALOGUE_LEFT_INPUT_1:
	हाल WM8904_ANALOGUE_RIGHT_INPUT_1:
	हाल WM8904_ANALOGUE_OUT1_LEFT:
	हाल WM8904_ANALOGUE_OUT1_RIGHT:
	हाल WM8904_ANALOGUE_OUT2_LEFT:
	हाल WM8904_ANALOGUE_OUT2_RIGHT:
	हाल WM8904_ANALOGUE_OUT12_ZC:
	हाल WM8904_DC_SERVO_0:
	हाल WM8904_DC_SERVO_1:
	हाल WM8904_DC_SERVO_2:
	हाल WM8904_DC_SERVO_4:
	हाल WM8904_DC_SERVO_5:
	हाल WM8904_DC_SERVO_6:
	हाल WM8904_DC_SERVO_7:
	हाल WM8904_DC_SERVO_8:
	हाल WM8904_DC_SERVO_9:
	हाल WM8904_DC_SERVO_READBACK_0:
	हाल WM8904_ANALOGUE_HP_0:
	हाल WM8904_ANALOGUE_LINEOUT_0:
	हाल WM8904_CHARGE_PUMP_0:
	हाल WM8904_CLASS_W_0:
	हाल WM8904_WRITE_SEQUENCER_0:
	हाल WM8904_WRITE_SEQUENCER_1:
	हाल WM8904_WRITE_SEQUENCER_2:
	हाल WM8904_WRITE_SEQUENCER_3:
	हाल WM8904_WRITE_SEQUENCER_4:
	हाल WM8904_FLL_CONTROL_1:
	हाल WM8904_FLL_CONTROL_2:
	हाल WM8904_FLL_CONTROL_3:
	हाल WM8904_FLL_CONTROL_4:
	हाल WM8904_FLL_CONTROL_5:
	हाल WM8904_GPIO_CONTROL_1:
	हाल WM8904_GPIO_CONTROL_2:
	हाल WM8904_GPIO_CONTROL_3:
	हाल WM8904_GPIO_CONTROL_4:
	हाल WM8904_DIGITAL_PULLS:
	हाल WM8904_INTERRUPT_STATUS:
	हाल WM8904_INTERRUPT_STATUS_MASK:
	हाल WM8904_INTERRUPT_POLARITY:
	हाल WM8904_INTERRUPT_DEBOUNCE:
	हाल WM8904_EQ1:
	हाल WM8904_EQ2:
	हाल WM8904_EQ3:
	हाल WM8904_EQ4:
	हाल WM8904_EQ5:
	हाल WM8904_EQ6:
	हाल WM8904_EQ7:
	हाल WM8904_EQ8:
	हाल WM8904_EQ9:
	हाल WM8904_EQ10:
	हाल WM8904_EQ11:
	हाल WM8904_EQ12:
	हाल WM8904_EQ13:
	हाल WM8904_EQ14:
	हाल WM8904_EQ15:
	हाल WM8904_EQ16:
	हाल WM8904_EQ17:
	हाल WM8904_EQ18:
	हाल WM8904_EQ19:
	हाल WM8904_EQ20:
	हाल WM8904_EQ21:
	हाल WM8904_EQ22:
	हाल WM8904_EQ23:
	हाल WM8904_EQ24:
	हाल WM8904_CONTROL_INTERFACE_TEST_1:
	हाल WM8904_ADC_TEST_0:
	हाल WM8904_ANALOGUE_OUTPUT_BIAS_0:
	हाल WM8904_FLL_NCO_TEST_0:
	हाल WM8904_FLL_NCO_TEST_1:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक wm8904_configure_घड़ीing(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक घड़ी0, घड़ी2, rate;

	/* Gate the घड़ी जबतक we're updating to aव्योम misघड़ीing */
	घड़ी2 = snd_soc_component_पढ़ो(component, WM8904_CLOCK_RATES_2);
	snd_soc_component_update_bits(component, WM8904_CLOCK_RATES_2,
			    WM8904_SYSCLK_SRC, 0);

	/* This should be करोne on init() क्रम bypass paths */
	चयन (wm8904->sysclk_src) अणु
	हाल WM8904_CLK_MCLK:
		dev_dbg(component->dev, "Using %dHz MCLK\n", wm8904->mclk_rate);

		घड़ी2 &= ~WM8904_SYSCLK_SRC;
		rate = wm8904->mclk_rate;

		/* Ensure the FLL is stopped */
		snd_soc_component_update_bits(component, WM8904_FLL_CONTROL_1,
				    WM8904_FLL_OSC_ENA | WM8904_FLL_ENA, 0);
		अवरोध;

	हाल WM8904_CLK_FLL:
		dev_dbg(component->dev, "Using %dHz FLL clock\n",
			wm8904->fll_fout);

		घड़ी2 |= WM8904_SYSCLK_SRC;
		rate = wm8904->fll_fout;
		अवरोध;

	शेष:
		dev_err(component->dev, "System clock not configured\n");
		वापस -EINVAL;
	पूर्ण

	/* SYSCLK shouldn't be over 13.5MHz */
	अगर (rate > 13500000) अणु
		घड़ी0 = WM8904_MCLK_DIV;
		wm8904->sysclk_rate = rate / 2;
	पूर्ण अन्यथा अणु
		घड़ी0 = 0;
		wm8904->sysclk_rate = rate;
	पूर्ण

	snd_soc_component_update_bits(component, WM8904_CLOCK_RATES_0, WM8904_MCLK_DIV,
			    घड़ी0);

	snd_soc_component_update_bits(component, WM8904_CLOCK_RATES_2,
			    WM8904_CLK_SYS_ENA | WM8904_SYSCLK_SRC, घड़ी2);

	dev_dbg(component->dev, "CLK_SYS is %dHz\n", wm8904->sysclk_rate);

	वापस 0;
पूर्ण

अटल व्योम wm8904_set_drc(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8904_pdata *pdata = wm8904->pdata;
	पूर्णांक save, i;

	/* Save any enables; the configuration should clear them. */
	save = snd_soc_component_पढ़ो(component, WM8904_DRC_0);

	क्रम (i = 0; i < WM8904_DRC_REGS; i++)
		snd_soc_component_update_bits(component, WM8904_DRC_0 + i, 0xffff,
				    pdata->drc_cfgs[wm8904->drc_cfg].regs[i]);

	/* Reenable the DRC */
	snd_soc_component_update_bits(component, WM8904_DRC_0,
			    WM8904_DRC_ENA | WM8904_DRC_DAC_PATH, save);
पूर्ण

अटल पूर्णांक wm8904_put_drc_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8904_pdata *pdata = wm8904->pdata;
	पूर्णांक value = ucontrol->value.क्रमागतerated.item[0];

	अगर (value >= pdata->num_drc_cfgs)
		वापस -EINVAL;

	wm8904->drc_cfg = value;

	wm8904_set_drc(component);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8904_get_drc_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);

	ucontrol->value.क्रमागतerated.item[0] = wm8904->drc_cfg;

	वापस 0;
पूर्ण

अटल व्योम wm8904_set_retune_mobile(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8904_pdata *pdata = wm8904->pdata;
	पूर्णांक best, best_val, save, i, cfg;

	अगर (!pdata || !wm8904->num_retune_mobile_texts)
		वापस;

	/* Find the version of the currently selected configuration
	 * with the nearest sample rate. */
	cfg = wm8904->retune_mobile_cfg;
	best = 0;
	best_val = पूर्णांक_उच्च;
	क्रम (i = 0; i < pdata->num_retune_mobile_cfgs; i++) अणु
		अगर (म_भेद(pdata->retune_mobile_cfgs[i].name,
			   wm8904->retune_mobile_texts[cfg]) == 0 &&
		    असल(pdata->retune_mobile_cfgs[i].rate
			- wm8904->fs) < best_val) अणु
			best = i;
			best_val = असल(pdata->retune_mobile_cfgs[i].rate
				       - wm8904->fs);
		पूर्ण
	पूर्ण

	dev_dbg(component->dev, "ReTune Mobile %s/%dHz for %dHz sample rate\n",
		pdata->retune_mobile_cfgs[best].name,
		pdata->retune_mobile_cfgs[best].rate,
		wm8904->fs);

	/* The EQ will be disabled जबतक reconfiguring it, remember the
	 * current configuration. 
	 */
	save = snd_soc_component_पढ़ो(component, WM8904_EQ1);

	क्रम (i = 0; i < WM8904_EQ_REGS; i++)
		snd_soc_component_update_bits(component, WM8904_EQ1 + i, 0xffff,
				pdata->retune_mobile_cfgs[best].regs[i]);

	snd_soc_component_update_bits(component, WM8904_EQ1, WM8904_EQ_ENA, save);
पूर्ण

अटल पूर्णांक wm8904_put_retune_mobile_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8904_pdata *pdata = wm8904->pdata;
	पूर्णांक value = ucontrol->value.क्रमागतerated.item[0];

	अगर (value >= pdata->num_retune_mobile_cfgs)
		वापस -EINVAL;

	wm8904->retune_mobile_cfg = value;

	wm8904_set_retune_mobile(component);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8904_get_retune_mobile_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);

	ucontrol->value.क्रमागतerated.item[0] = wm8904->retune_mobile_cfg;

	वापस 0;
पूर्ण

अटल पूर्णांक deemph_settings[] = अणु 0, 32000, 44100, 48000 पूर्ण;

अटल पूर्णांक wm8904_set_deemph(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);
	पूर्णांक val, i, best;

	/* If we're using deemphasis select the nearest available sample 
	 * rate.
	 */
	अगर (wm8904->deemph) अणु
		best = 1;
		क्रम (i = 2; i < ARRAY_SIZE(deemph_settings); i++) अणु
			अगर (असल(deemph_settings[i] - wm8904->fs) <
			    असल(deemph_settings[best] - wm8904->fs))
				best = i;
		पूर्ण

		val = best << WM8904_DEEMPH_SHIFT;
	पूर्ण अन्यथा अणु
		val = 0;
	पूर्ण

	dev_dbg(component->dev, "Set deemphasis %d\n", val);

	वापस snd_soc_component_update_bits(component, WM8904_DAC_DIGITAL_1,
				   WM8904_DEEMPH_MASK, val);
पूर्ण

अटल पूर्णांक wm8904_get_deemph(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = wm8904->deemph;
	वापस 0;
पूर्ण

अटल पूर्णांक wm8904_put_deemph(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक deemph = ucontrol->value.पूर्णांकeger.value[0];

	अगर (deemph > 1)
		वापस -EINVAL;

	wm8904->deemph = deemph;

	वापस wm8904_set_deemph(component);
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(dac_boost_tlv, 0, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(digital_tlv, -7200, 75, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(out_tlv, -5700, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(sidetone_tlv, -3600, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(eq_tlv, -1200, 100, 0);

अटल स्थिर अक्षर *hpf_mode_text[] = अणु
	"Hi-fi", "Voice 1", "Voice 2", "Voice 3"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(hpf_mode, WM8904_ADC_DIGITAL_0, 5,
			    hpf_mode_text);

अटल पूर्णांक wm8904_adc_osr_put(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = snd_soc_put_volsw(kcontrol, ucontrol);
	अगर (ret < 0)
		वापस ret;

	अगर (ucontrol->value.पूर्णांकeger.value[0])
		val = 0;
	अन्यथा
		val = WM8904_ADC_128_OSR_TST_MODE | WM8904_ADC_BIASX1P5;

	snd_soc_component_update_bits(component, WM8904_ADC_TEST_0,
			    WM8904_ADC_128_OSR_TST_MODE | WM8904_ADC_BIASX1P5,
			    val);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new wm8904_adc_snd_controls[] = अणु
SOC_DOUBLE_R_TLV("Digital Capture Volume", WM8904_ADC_DIGITAL_VOLUME_LEFT,
		 WM8904_ADC_DIGITAL_VOLUME_RIGHT, 1, 119, 0, digital_tlv),

/* No TLV since it depends on mode */
SOC_DOUBLE_R("Capture Volume", WM8904_ANALOGUE_LEFT_INPUT_0,
	     WM8904_ANALOGUE_RIGHT_INPUT_0, 0, 31, 0),
SOC_DOUBLE_R("Capture Switch", WM8904_ANALOGUE_LEFT_INPUT_0,
	     WM8904_ANALOGUE_RIGHT_INPUT_0, 7, 1, 1),

SOC_SINGLE("High Pass Filter Switch", WM8904_ADC_DIGITAL_0, 4, 1, 0),
SOC_ENUM("High Pass Filter Mode", hpf_mode),
SOC_SINGLE_EXT("ADC 128x OSR Switch", WM8904_ANALOGUE_ADC_0, 0, 1, 0,
	snd_soc_get_volsw, wm8904_adc_osr_put),
पूर्ण;

अटल स्थिर अक्षर *drc_path_text[] = अणु
	"ADC", "DAC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(drc_path, WM8904_DRC_0, 14, drc_path_text);

अटल स्थिर काष्ठा snd_kcontrol_new wm8904_dac_snd_controls[] = अणु
SOC_SINGLE_TLV("Digital Playback Boost Volume", 
	       WM8904_AUDIO_INTERFACE_0, 9, 3, 0, dac_boost_tlv),
SOC_DOUBLE_R_TLV("Digital Playback Volume", WM8904_DAC_DIGITAL_VOLUME_LEFT,
		 WM8904_DAC_DIGITAL_VOLUME_RIGHT, 1, 96, 0, digital_tlv),

SOC_DOUBLE_R_TLV("Headphone Volume", WM8904_ANALOGUE_OUT1_LEFT,
		 WM8904_ANALOGUE_OUT1_RIGHT, 0, 63, 0, out_tlv),
SOC_DOUBLE_R("Headphone Switch", WM8904_ANALOGUE_OUT1_LEFT,
	     WM8904_ANALOGUE_OUT1_RIGHT, 8, 1, 1),
SOC_DOUBLE_R("Headphone ZC Switch", WM8904_ANALOGUE_OUT1_LEFT,
	     WM8904_ANALOGUE_OUT1_RIGHT, 6, 1, 0),

SOC_DOUBLE_R_TLV("Line Output Volume", WM8904_ANALOGUE_OUT2_LEFT,
		 WM8904_ANALOGUE_OUT2_RIGHT, 0, 63, 0, out_tlv),
SOC_DOUBLE_R("Line Output Switch", WM8904_ANALOGUE_OUT2_LEFT,
	     WM8904_ANALOGUE_OUT2_RIGHT, 8, 1, 1),
SOC_DOUBLE_R("Line Output ZC Switch", WM8904_ANALOGUE_OUT2_LEFT,
	     WM8904_ANALOGUE_OUT2_RIGHT, 6, 1, 0),

SOC_SINGLE("EQ Switch", WM8904_EQ1, 0, 1, 0),
SOC_SINGLE("DRC Switch", WM8904_DRC_0, 15, 1, 0),
SOC_ENUM("DRC Path", drc_path),
SOC_SINGLE("DAC OSRx2 Switch", WM8904_DAC_DIGITAL_1, 6, 1, 0),
SOC_SINGLE_BOOL_EXT("DAC Deemphasis Switch", 0,
		    wm8904_get_deemph, wm8904_put_deemph),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8904_snd_controls[] = अणु
SOC_DOUBLE_TLV("Digital Sidetone Volume", WM8904_DAC_DIGITAL_0, 4, 8, 15, 0,
	       sidetone_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8904_eq_controls[] = अणु
SOC_SINGLE_TLV("EQ1 Volume", WM8904_EQ2, 0, 24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ2 Volume", WM8904_EQ3, 0, 24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ3 Volume", WM8904_EQ4, 0, 24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ4 Volume", WM8904_EQ5, 0, 24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ5 Volume", WM8904_EQ6, 0, 24, 0, eq_tlv),
पूर्ण;

अटल पूर्णांक cp_event(काष्ठा snd_soc_dapm_widget *w,
		    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	अगर (WARN_ON(event != SND_SOC_DAPM_POST_PMU))
		वापस -EINVAL;

	/* Maximum startup समय */
	udelay(500);

	वापस 0;
पूर्ण

अटल पूर्णांक sysclk_event(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* If we're using the FLL then we only start it when
		 * required; we assume that the configuration has been
		 * करोne previously and all we need to करो is kick it
		 * off.
		 */
		चयन (wm8904->sysclk_src) अणु
		हाल WM8904_CLK_FLL:
			snd_soc_component_update_bits(component, WM8904_FLL_CONTROL_1,
					    WM8904_FLL_OSC_ENA,
					    WM8904_FLL_OSC_ENA);

			snd_soc_component_update_bits(component, WM8904_FLL_CONTROL_1,
					    WM8904_FLL_ENA,
					    WM8904_FLL_ENA);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, WM8904_FLL_CONTROL_1,
				    WM8904_FLL_OSC_ENA | WM8904_FLL_ENA, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक out_pga_event(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);
	पूर्णांक reg, val;
	पूर्णांक dcs_mask;
	पूर्णांक dcs_l, dcs_r;
	पूर्णांक dcs_l_reg, dcs_r_reg;
	पूर्णांक समयout;
	पूर्णांक pwr_reg;

	/* This code is shared between HP and LINEOUT; we करो all our
	 * घातer management in stereo pairs to aव्योम latency issues so
	 * we reuse shअगरt to identअगरy which rather than म_भेद() the
	 * name. */
	reg = w->shअगरt;

	चयन (reg) अणु
	हाल WM8904_ANALOGUE_HP_0:
		pwr_reg = WM8904_POWER_MANAGEMENT_2;
		dcs_mask = WM8904_DCS_ENA_CHAN_0 | WM8904_DCS_ENA_CHAN_1;
		dcs_r_reg = WM8904_DC_SERVO_8;
		dcs_l_reg = WM8904_DC_SERVO_9;
		dcs_l = 0;
		dcs_r = 1;
		अवरोध;
	हाल WM8904_ANALOGUE_LINEOUT_0:
		pwr_reg = WM8904_POWER_MANAGEMENT_3;
		dcs_mask = WM8904_DCS_ENA_CHAN_2 | WM8904_DCS_ENA_CHAN_3;
		dcs_r_reg = WM8904_DC_SERVO_6;
		dcs_l_reg = WM8904_DC_SERVO_7;
		dcs_l = 2;
		dcs_r = 3;
		अवरोध;
	शेष:
		WARN(1, "Invalid reg %d\n", reg);
		वापस -EINVAL;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Power on the PGAs */
		snd_soc_component_update_bits(component, pwr_reg,
				    WM8904_HPL_PGA_ENA | WM8904_HPR_PGA_ENA,
				    WM8904_HPL_PGA_ENA | WM8904_HPR_PGA_ENA);

		/* Power on the amplअगरier */
		snd_soc_component_update_bits(component, reg,
				    WM8904_HPL_ENA | WM8904_HPR_ENA,
				    WM8904_HPL_ENA | WM8904_HPR_ENA);


		/* Enable the first stage */
		snd_soc_component_update_bits(component, reg,
				    WM8904_HPL_ENA_DLY | WM8904_HPR_ENA_DLY,
				    WM8904_HPL_ENA_DLY | WM8904_HPR_ENA_DLY);

		/* Power up the DC servo */
		snd_soc_component_update_bits(component, WM8904_DC_SERVO_0,
				    dcs_mask, dcs_mask);

		/* Either calibrate the DC servo or restore cached state
		 * अगर we have that.
		 */
		अगर (wm8904->dcs_state[dcs_l] || wm8904->dcs_state[dcs_r]) अणु
			dev_dbg(component->dev, "Restoring DC servo state\n");

			snd_soc_component_ग_लिखो(component, dcs_l_reg,
				      wm8904->dcs_state[dcs_l]);
			snd_soc_component_ग_लिखो(component, dcs_r_reg,
				      wm8904->dcs_state[dcs_r]);

			snd_soc_component_ग_लिखो(component, WM8904_DC_SERVO_1, dcs_mask);

			समयout = 20;
		पूर्ण अन्यथा अणु
			dev_dbg(component->dev, "Calibrating DC servo\n");

			snd_soc_component_ग_लिखो(component, WM8904_DC_SERVO_1,
				dcs_mask << WM8904_DCS_TRIG_STARTUP_0_SHIFT);

			समयout = 500;
		पूर्ण

		/* Wait क्रम DC servo to complete */
		dcs_mask <<= WM8904_DCS_CAL_COMPLETE_SHIFT;
		करो अणु
			val = snd_soc_component_पढ़ो(component, WM8904_DC_SERVO_READBACK_0);
			अगर ((val & dcs_mask) == dcs_mask)
				अवरोध;

			msleep(1);
		पूर्ण जबतक (--समयout);

		अगर ((val & dcs_mask) != dcs_mask)
			dev_warn(component->dev, "DC servo timed out\n");
		अन्यथा
			dev_dbg(component->dev, "DC servo ready\n");

		/* Enable the output stage */
		snd_soc_component_update_bits(component, reg,
				    WM8904_HPL_ENA_OUTP | WM8904_HPR_ENA_OUTP,
				    WM8904_HPL_ENA_OUTP | WM8904_HPR_ENA_OUTP);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMU:
		/* Unलघु the output itself */
		snd_soc_component_update_bits(component, reg,
				    WM8904_HPL_RMV_SHORT |
				    WM8904_HPR_RMV_SHORT,
				    WM8904_HPL_RMV_SHORT |
				    WM8904_HPR_RMV_SHORT);

		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		/* Short the output */
		snd_soc_component_update_bits(component, reg,
				    WM8904_HPL_RMV_SHORT |
				    WM8904_HPR_RMV_SHORT, 0);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		/* Cache the DC servo configuration; this will be
		 * invalidated अगर we change the configuration. */
		wm8904->dcs_state[dcs_l] = snd_soc_component_पढ़ो(component, dcs_l_reg);
		wm8904->dcs_state[dcs_r] = snd_soc_component_पढ़ो(component, dcs_r_reg);

		snd_soc_component_update_bits(component, WM8904_DC_SERVO_0,
				    dcs_mask, 0);

		/* Disable the amplअगरier input and output stages */
		snd_soc_component_update_bits(component, reg,
				    WM8904_HPL_ENA | WM8904_HPR_ENA |
				    WM8904_HPL_ENA_DLY | WM8904_HPR_ENA_DLY |
				    WM8904_HPL_ENA_OUTP | WM8904_HPR_ENA_OUTP,
				    0);

		/* PGAs too */
		snd_soc_component_update_bits(component, pwr_reg,
				    WM8904_HPL_PGA_ENA | WM8904_HPR_PGA_ENA,
				    0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *input_mode_text[] = अणु
	"Single-Ended", "Differential Line", "Differential Mic"
पूर्ण;

अटल स्थिर अक्षर *lin_text[] = अणु
	"IN1L", "IN2L", "IN3L"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(lin_क्रमागत, WM8904_ANALOGUE_LEFT_INPUT_1, 2,
			    lin_text);

अटल स्थिर काष्ठा snd_kcontrol_new lin_mux =
	SOC_DAPM_ENUM("Left Capture Mux", lin_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(lin_inv_क्रमागत, WM8904_ANALOGUE_LEFT_INPUT_1, 4,
			    lin_text);

अटल स्थिर काष्ठा snd_kcontrol_new lin_inv_mux =
	SOC_DAPM_ENUM("Left Capture Inverting Mux", lin_inv_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(lin_mode_क्रमागत,
			    WM8904_ANALOGUE_LEFT_INPUT_1, 0,
			    input_mode_text);

अटल स्थिर काष्ठा snd_kcontrol_new lin_mode =
	SOC_DAPM_ENUM("Left Capture Mode", lin_mode_क्रमागत);

अटल स्थिर अक्षर *rin_text[] = अणु
	"IN1R", "IN2R", "IN3R"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rin_क्रमागत, WM8904_ANALOGUE_RIGHT_INPUT_1, 2,
			    rin_text);

अटल स्थिर काष्ठा snd_kcontrol_new rin_mux =
	SOC_DAPM_ENUM("Right Capture Mux", rin_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(rin_inv_क्रमागत, WM8904_ANALOGUE_RIGHT_INPUT_1, 4,
			    rin_text);

अटल स्थिर काष्ठा snd_kcontrol_new rin_inv_mux =
	SOC_DAPM_ENUM("Right Capture Inverting Mux", rin_inv_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(rin_mode_क्रमागत,
			    WM8904_ANALOGUE_RIGHT_INPUT_1, 0,
			    input_mode_text);

अटल स्थिर काष्ठा snd_kcontrol_new rin_mode =
	SOC_DAPM_ENUM("Right Capture Mode", rin_mode_क्रमागत);

अटल स्थिर अक्षर *aअगर_text[] = अणु
	"Left", "Right"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(aअगरoutl_क्रमागत, WM8904_AUDIO_INTERFACE_0, 7,
			    aअगर_text);

अटल स्थिर काष्ठा snd_kcontrol_new aअगरoutl_mux =
	SOC_DAPM_ENUM("AIFOUTL Mux", aअगरoutl_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(aअगरoutr_क्रमागत, WM8904_AUDIO_INTERFACE_0, 6,
			    aअगर_text);

अटल स्थिर काष्ठा snd_kcontrol_new aअगरoutr_mux =
	SOC_DAPM_ENUM("AIFOUTR Mux", aअगरoutr_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(aअगरinl_क्रमागत, WM8904_AUDIO_INTERFACE_0, 5,
			    aअगर_text);

अटल स्थिर काष्ठा snd_kcontrol_new aअगरinl_mux =
	SOC_DAPM_ENUM("AIFINL Mux", aअगरinl_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(aअगरinr_क्रमागत, WM8904_AUDIO_INTERFACE_0, 4,
			    aअगर_text);

अटल स्थिर काष्ठा snd_kcontrol_new aअगरinr_mux =
	SOC_DAPM_ENUM("AIFINR Mux", aअगरinr_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8904_core_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_SUPPLY("SYSCLK", WM8904_CLOCK_RATES_2, 2, 0, sysclk_event,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("CLK_DSP", WM8904_CLOCK_RATES_2, 1, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("TOCLK", WM8904_CLOCK_RATES_2, 0, 0, शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8904_adc_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("IN1L"),
SND_SOC_DAPM_INPUT("IN1R"),
SND_SOC_DAPM_INPUT("IN2L"),
SND_SOC_DAPM_INPUT("IN2R"),
SND_SOC_DAPM_INPUT("IN3L"),
SND_SOC_DAPM_INPUT("IN3R"),

SND_SOC_DAPM_SUPPLY("MICBIAS", WM8904_MIC_BIAS_CONTROL_0, 0, 0, शून्य, 0),

SND_SOC_DAPM_MUX("Left Capture Mux", SND_SOC_NOPM, 0, 0, &lin_mux),
SND_SOC_DAPM_MUX("Left Capture Inverting Mux", SND_SOC_NOPM, 0, 0,
		 &lin_inv_mux),
SND_SOC_DAPM_MUX("Left Capture Mode", SND_SOC_NOPM, 0, 0, &lin_mode),
SND_SOC_DAPM_MUX("Right Capture Mux", SND_SOC_NOPM, 0, 0, &rin_mux),
SND_SOC_DAPM_MUX("Right Capture Inverting Mux", SND_SOC_NOPM, 0, 0,
		 &rin_inv_mux),
SND_SOC_DAPM_MUX("Right Capture Mode", SND_SOC_NOPM, 0, 0, &rin_mode),

SND_SOC_DAPM_PGA("Left Capture PGA", WM8904_POWER_MANAGEMENT_0, 1, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("Right Capture PGA", WM8904_POWER_MANAGEMENT_0, 0, 0,
		 शून्य, 0),

SND_SOC_DAPM_ADC("ADCL", शून्य, WM8904_POWER_MANAGEMENT_6, 1, 0),
SND_SOC_DAPM_ADC("ADCR", शून्य, WM8904_POWER_MANAGEMENT_6, 0, 0),

SND_SOC_DAPM_MUX("AIFOUTL Mux", SND_SOC_NOPM, 0, 0, &aअगरoutl_mux),
SND_SOC_DAPM_MUX("AIFOUTR Mux", SND_SOC_NOPM, 0, 0, &aअगरoutr_mux),

SND_SOC_DAPM_AIF_OUT("AIFOUTL", "Capture", 0, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_AIF_OUT("AIFOUTR", "Capture", 1, SND_SOC_NOPM, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8904_dac_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_AIF_IN("AIFINL", "Playback", 0, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_AIF_IN("AIFINR", "Playback", 1, SND_SOC_NOPM, 0, 0),

SND_SOC_DAPM_MUX("DACL Mux", SND_SOC_NOPM, 0, 0, &aअगरinl_mux),
SND_SOC_DAPM_MUX("DACR Mux", SND_SOC_NOPM, 0, 0, &aअगरinr_mux),

SND_SOC_DAPM_DAC("DACL", शून्य, WM8904_POWER_MANAGEMENT_6, 3, 0),
SND_SOC_DAPM_DAC("DACR", शून्य, WM8904_POWER_MANAGEMENT_6, 2, 0),

SND_SOC_DAPM_SUPPLY("Charge pump", WM8904_CHARGE_PUMP_0, 0, 0, cp_event,
		    SND_SOC_DAPM_POST_PMU),

SND_SOC_DAPM_PGA("HPL PGA", SND_SOC_NOPM, 1, 0, शून्य, 0),
SND_SOC_DAPM_PGA("HPR PGA", SND_SOC_NOPM, 0, 0, शून्य, 0),

SND_SOC_DAPM_PGA("LINEL PGA", SND_SOC_NOPM, 1, 0, शून्य, 0),
SND_SOC_DAPM_PGA("LINER PGA", SND_SOC_NOPM, 0, 0, शून्य, 0),

SND_SOC_DAPM_PGA_E("Headphone Output", SND_SOC_NOPM, WM8904_ANALOGUE_HP_0,
		   0, शून्य, 0, out_pga_event,
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_PGA_E("Line Output", SND_SOC_NOPM, WM8904_ANALOGUE_LINEOUT_0,
		   0, शून्य, 0, out_pga_event,
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

SND_SOC_DAPM_OUTPUT("HPOUTL"),
SND_SOC_DAPM_OUTPUT("HPOUTR"),
SND_SOC_DAPM_OUTPUT("LINEOUTL"),
SND_SOC_DAPM_OUTPUT("LINEOUTR"),
पूर्ण;

अटल स्थिर अक्षर *out_mux_text[] = अणु
	"DAC", "Bypass"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(hpl_क्रमागत, WM8904_ANALOGUE_OUT12_ZC, 3,
			    out_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new hpl_mux =
	SOC_DAPM_ENUM("HPL Mux", hpl_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(hpr_क्रमागत, WM8904_ANALOGUE_OUT12_ZC, 2,
			    out_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new hpr_mux =
	SOC_DAPM_ENUM("HPR Mux", hpr_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(linel_क्रमागत, WM8904_ANALOGUE_OUT12_ZC, 1,
			    out_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new linel_mux =
	SOC_DAPM_ENUM("LINEL Mux", linel_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(liner_क्रमागत, WM8904_ANALOGUE_OUT12_ZC, 0,
			    out_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new liner_mux =
	SOC_DAPM_ENUM("LINER Mux", liner_क्रमागत);

अटल स्थिर अक्षर *sidetone_text[] = अणु
	"None", "Left", "Right"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(dacl_sidetone_क्रमागत, WM8904_DAC_DIGITAL_0, 2,
			    sidetone_text);

अटल स्थिर काष्ठा snd_kcontrol_new dacl_sidetone_mux =
	SOC_DAPM_ENUM("Left Sidetone Mux", dacl_sidetone_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(dacr_sidetone_क्रमागत, WM8904_DAC_DIGITAL_0, 0,
			    sidetone_text);

अटल स्थिर काष्ठा snd_kcontrol_new dacr_sidetone_mux =
	SOC_DAPM_ENUM("Right Sidetone Mux", dacr_sidetone_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8904_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_SUPPLY("Class G", WM8904_CLASS_W_0, 0, 1, शून्य, 0),
SND_SOC_DAPM_PGA("Left Bypass", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Right Bypass", SND_SOC_NOPM, 0, 0, शून्य, 0),

SND_SOC_DAPM_MUX("Left Sidetone", SND_SOC_NOPM, 0, 0, &dacl_sidetone_mux),
SND_SOC_DAPM_MUX("Right Sidetone", SND_SOC_NOPM, 0, 0, &dacr_sidetone_mux),

SND_SOC_DAPM_MUX("HPL Mux", SND_SOC_NOPM, 0, 0, &hpl_mux),
SND_SOC_DAPM_MUX("HPR Mux", SND_SOC_NOPM, 0, 0, &hpr_mux),
SND_SOC_DAPM_MUX("LINEL Mux", SND_SOC_NOPM, 0, 0, &linel_mux),
SND_SOC_DAPM_MUX("LINER Mux", SND_SOC_NOPM, 0, 0, &liner_mux),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route core_पूर्णांकercon[] = अणु
	अणु "CLK_DSP", शून्य, "SYSCLK" पूर्ण,
	अणु "TOCLK", शून्य, "SYSCLK" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route adc_पूर्णांकercon[] = अणु
	अणु "Left Capture Mux", "IN1L", "IN1L" पूर्ण,
	अणु "Left Capture Mux", "IN2L", "IN2L" पूर्ण,
	अणु "Left Capture Mux", "IN3L", "IN3L" पूर्ण,

	अणु "Left Capture Inverting Mux", "IN1L", "IN1L" पूर्ण,
	अणु "Left Capture Inverting Mux", "IN2L", "IN2L" पूर्ण,
	अणु "Left Capture Inverting Mux", "IN3L", "IN3L" पूर्ण,

	अणु "Left Capture Mode", "Single-Ended", "Left Capture Inverting Mux" पूर्ण,
	अणु "Left Capture Mode", "Differential Line", "Left Capture Mux" पूर्ण,
	अणु "Left Capture Mode", "Differential Line", "Left Capture Inverting Mux" पूर्ण,
	अणु "Left Capture Mode", "Differential Mic", "Left Capture Mux" पूर्ण,
	अणु "Left Capture Mode", "Differential Mic", "Left Capture Inverting Mux" पूर्ण,

	अणु "Right Capture Mux", "IN1R", "IN1R" पूर्ण,
	अणु "Right Capture Mux", "IN2R", "IN2R" पूर्ण,
	अणु "Right Capture Mux", "IN3R", "IN3R" पूर्ण,

	अणु "Right Capture Inverting Mux", "IN1R", "IN1R" पूर्ण,
	अणु "Right Capture Inverting Mux", "IN2R", "IN2R" पूर्ण,
	अणु "Right Capture Inverting Mux", "IN3R", "IN3R" पूर्ण,

	अणु "Right Capture Mode", "Single-Ended", "Right Capture Inverting Mux" पूर्ण,
	अणु "Right Capture Mode", "Differential Line", "Right Capture Mux" पूर्ण,
	अणु "Right Capture Mode", "Differential Line", "Right Capture Inverting Mux" पूर्ण,
	अणु "Right Capture Mode", "Differential Mic", "Right Capture Mux" पूर्ण,
	अणु "Right Capture Mode", "Differential Mic", "Right Capture Inverting Mux" पूर्ण,

	अणु "Left Capture PGA", शून्य, "Left Capture Mode" पूर्ण,
	अणु "Right Capture PGA", शून्य, "Right Capture Mode" पूर्ण,

	अणु "AIFOUTL Mux", "Left", "ADCL" पूर्ण,
	अणु "AIFOUTL Mux", "Right", "ADCR" पूर्ण,
	अणु "AIFOUTR Mux", "Left", "ADCL" पूर्ण,
	अणु "AIFOUTR Mux", "Right", "ADCR" पूर्ण,

	अणु "AIFOUTL", शून्य, "AIFOUTL Mux" पूर्ण,
	अणु "AIFOUTR", शून्य, "AIFOUTR Mux" पूर्ण,

	अणु "ADCL", शून्य, "CLK_DSP" पूर्ण,
	अणु "ADCL", शून्य, "Left Capture PGA" पूर्ण,

	अणु "ADCR", शून्य, "CLK_DSP" पूर्ण,
	अणु "ADCR", शून्य, "Right Capture PGA" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route dac_पूर्णांकercon[] = अणु
	अणु "DACL Mux", "Left", "AIFINL" पूर्ण,
	अणु "DACL Mux", "Right", "AIFINR" पूर्ण,

	अणु "DACR Mux", "Left", "AIFINL" पूर्ण,
	अणु "DACR Mux", "Right", "AIFINR" पूर्ण,

	अणु "DACL", शून्य, "DACL Mux" पूर्ण,
	अणु "DACL", शून्य, "CLK_DSP" पूर्ण,

	अणु "DACR", शून्य, "DACR Mux" पूर्ण,
	अणु "DACR", शून्य, "CLK_DSP" पूर्ण,

	अणु "Charge pump", शून्य, "SYSCLK" पूर्ण,

	अणु "Headphone Output", शून्य, "HPL PGA" पूर्ण,
	अणु "Headphone Output", शून्य, "HPR PGA" पूर्ण,
	अणु "Headphone Output", शून्य, "Charge pump" पूर्ण,
	अणु "Headphone Output", शून्य, "TOCLK" पूर्ण,

	अणु "Line Output", शून्य, "LINEL PGA" पूर्ण,
	अणु "Line Output", शून्य, "LINER PGA" पूर्ण,
	अणु "Line Output", शून्य, "Charge pump" पूर्ण,
	अणु "Line Output", शून्य, "TOCLK" पूर्ण,

	अणु "HPOUTL", शून्य, "Headphone Output" पूर्ण,
	अणु "HPOUTR", शून्य, "Headphone Output" पूर्ण,

	अणु "LINEOUTL", शून्य, "Line Output" पूर्ण,
	अणु "LINEOUTR", शून्य, "Line Output" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8904_पूर्णांकercon[] = अणु
	अणु "Left Sidetone", "Left", "ADCL" पूर्ण,
	अणु "Left Sidetone", "Right", "ADCR" पूर्ण,
	अणु "DACL", शून्य, "Left Sidetone" पूर्ण,
	
	अणु "Right Sidetone", "Left", "ADCL" पूर्ण,
	अणु "Right Sidetone", "Right", "ADCR" पूर्ण,
	अणु "DACR", शून्य, "Right Sidetone" पूर्ण,

	अणु "Left Bypass", शून्य, "Class G" पूर्ण,
	अणु "Left Bypass", शून्य, "Left Capture PGA" पूर्ण,

	अणु "Right Bypass", शून्य, "Class G" पूर्ण,
	अणु "Right Bypass", शून्य, "Right Capture PGA" पूर्ण,

	अणु "HPL Mux", "DAC", "DACL" पूर्ण,
	अणु "HPL Mux", "Bypass", "Left Bypass" पूर्ण,

	अणु "HPR Mux", "DAC", "DACR" पूर्ण,
	अणु "HPR Mux", "Bypass", "Right Bypass" पूर्ण,

	अणु "LINEL Mux", "DAC", "DACL" पूर्ण,
	अणु "LINEL Mux", "Bypass", "Left Bypass" पूर्ण,

	अणु "LINER Mux", "DAC", "DACR" पूर्ण,
	अणु "LINER Mux", "Bypass", "Right Bypass" पूर्ण,

	अणु "HPL PGA", शून्य, "HPL Mux" पूर्ण,
	अणु "HPR PGA", शून्य, "HPR Mux" पूर्ण,

	अणु "LINEL PGA", शून्य, "LINEL Mux" पूर्ण,
	अणु "LINER PGA", शून्य, "LINER Mux" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8912_पूर्णांकercon[] = अणु
	अणु "HPL PGA", शून्य, "DACL" पूर्ण,
	अणु "HPR PGA", शून्य, "DACR" पूर्ण,

	अणु "LINEL PGA", शून्य, "DACL" पूर्ण,
	अणु "LINER PGA", शून्य, "DACR" पूर्ण,
पूर्ण;

अटल पूर्णांक wm8904_add_widमाला_लो(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	snd_soc_dapm_new_controls(dapm, wm8904_core_dapm_widमाला_लो,
				  ARRAY_SIZE(wm8904_core_dapm_widमाला_लो));
	snd_soc_dapm_add_routes(dapm, core_पूर्णांकercon,
				ARRAY_SIZE(core_पूर्णांकercon));

	चयन (wm8904->devtype) अणु
	हाल WM8904:
		snd_soc_add_component_controls(component, wm8904_adc_snd_controls,
				     ARRAY_SIZE(wm8904_adc_snd_controls));
		snd_soc_add_component_controls(component, wm8904_dac_snd_controls,
				     ARRAY_SIZE(wm8904_dac_snd_controls));
		snd_soc_add_component_controls(component, wm8904_snd_controls,
				     ARRAY_SIZE(wm8904_snd_controls));

		snd_soc_dapm_new_controls(dapm, wm8904_adc_dapm_widमाला_लो,
					  ARRAY_SIZE(wm8904_adc_dapm_widमाला_लो));
		snd_soc_dapm_new_controls(dapm, wm8904_dac_dapm_widमाला_लो,
					  ARRAY_SIZE(wm8904_dac_dapm_widमाला_लो));
		snd_soc_dapm_new_controls(dapm, wm8904_dapm_widमाला_लो,
					  ARRAY_SIZE(wm8904_dapm_widमाला_लो));

		snd_soc_dapm_add_routes(dapm, adc_पूर्णांकercon,
					ARRAY_SIZE(adc_पूर्णांकercon));
		snd_soc_dapm_add_routes(dapm, dac_पूर्णांकercon,
					ARRAY_SIZE(dac_पूर्णांकercon));
		snd_soc_dapm_add_routes(dapm, wm8904_पूर्णांकercon,
					ARRAY_SIZE(wm8904_पूर्णांकercon));
		अवरोध;

	हाल WM8912:
		snd_soc_add_component_controls(component, wm8904_dac_snd_controls,
				     ARRAY_SIZE(wm8904_dac_snd_controls));

		snd_soc_dapm_new_controls(dapm, wm8904_dac_dapm_widमाला_लो,
					  ARRAY_SIZE(wm8904_dac_dapm_widमाला_लो));

		snd_soc_dapm_add_routes(dapm, dac_पूर्णांकercon,
					ARRAY_SIZE(dac_पूर्णांकercon));
		snd_soc_dapm_add_routes(dapm, wm8912_पूर्णांकercon,
					ARRAY_SIZE(wm8912_पूर्णांकercon));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा अणु
	पूर्णांक ratio;
	अचिन्हित पूर्णांक clk_sys_rate;
पूर्ण clk_sys_rates[] = अणु
	अणु   64,  0 पूर्ण,
	अणु  128,  1 पूर्ण,
	अणु  192,  2 पूर्ण,
	अणु  256,  3 पूर्ण,
	अणु  384,  4 पूर्ण,
	अणु  512,  5 पूर्ण,
	अणु  786,  6 पूर्ण,
	अणु 1024,  7 पूर्ण,
	अणु 1408,  8 पूर्ण,
	अणु 1536,  9 पूर्ण,
पूर्ण;

अटल काष्ठा अणु
	पूर्णांक rate;
	पूर्णांक sample_rate;
पूर्ण sample_rates[] = अणु
	अणु 8000,  0  पूर्ण,
	अणु 11025, 1  पूर्ण,
	अणु 12000, 1  पूर्ण,
	अणु 16000, 2  पूर्ण,
	अणु 22050, 3  पूर्ण,
	अणु 24000, 3  पूर्ण,
	अणु 32000, 4  पूर्ण,
	अणु 44100, 5  पूर्ण,
	अणु 48000, 5  पूर्ण,
पूर्ण;

अटल काष्ठा अणु
	पूर्णांक भाग; /* *10 due to .5s */
	पूर्णांक bclk_भाग;
पूर्ण bclk_भागs[] = अणु
	अणु 10,  0  पूर्ण,
	अणु 15,  1  पूर्ण,
	अणु 20,  2  पूर्ण,
	अणु 30,  3  पूर्ण,
	अणु 40,  4  पूर्ण,
	अणु 50,  5  पूर्ण,
	अणु 55,  6  पूर्ण,
	अणु 60,  7  पूर्ण,
	अणु 80,  8  पूर्ण,
	अणु 100, 9  पूर्ण,
	अणु 110, 10 पूर्ण,
	अणु 120, 11 पूर्ण,
	अणु 160, 12 पूर्ण,
	अणु 200, 13 पूर्ण,
	अणु 220, 14 पूर्ण,
	अणु 240, 16 पूर्ण,
	अणु 200, 17 पूर्ण,
	अणु 320, 18 पूर्ण,
	अणु 440, 19 पूर्ण,
	अणु 480, 20 पूर्ण,
पूर्ण;


अटल पूर्णांक wm8904_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret, i, best, best_val, cur_val;
	अचिन्हित पूर्णांक aअगर1 = 0;
	अचिन्हित पूर्णांक aअगर2 = 0;
	अचिन्हित पूर्णांक aअगर3 = 0;
	अचिन्हित पूर्णांक घड़ी1 = 0;
	अचिन्हित पूर्णांक dac_digital1 = 0;

	/* What BCLK करो we need? */
	wm8904->fs = params_rate(params);
	अगर (wm8904->tdm_slots) अणु
		dev_dbg(component->dev, "Configuring for %d %d bit TDM slots\n",
			wm8904->tdm_slots, wm8904->tdm_width);
		wm8904->bclk = snd_soc_calc_bclk(wm8904->fs,
						 wm8904->tdm_width, 2,
						 wm8904->tdm_slots);
	पूर्ण अन्यथा अणु
		wm8904->bclk = snd_soc_params_to_bclk(params);
	पूर्ण

	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		aअगर1 |= 0x40;
		अवरोध;
	हाल 24:
		aअगर1 |= 0x80;
		अवरोध;
	हाल 32:
		aअगर1 |= 0xc0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण


	dev_dbg(component->dev, "Target BCLK is %dHz\n", wm8904->bclk);

	ret = wm8904_configure_घड़ीing(component);
	अगर (ret != 0)
		वापस ret;

	/* Select nearest CLK_SYS_RATE */
	best = 0;
	best_val = असल((wm8904->sysclk_rate / clk_sys_rates[0].ratio)
		       - wm8904->fs);
	क्रम (i = 1; i < ARRAY_SIZE(clk_sys_rates); i++) अणु
		cur_val = असल((wm8904->sysclk_rate /
			       clk_sys_rates[i].ratio) - wm8904->fs);
		अगर (cur_val < best_val) अणु
			best = i;
			best_val = cur_val;
		पूर्ण
	पूर्ण
	dev_dbg(component->dev, "Selected CLK_SYS_RATIO of %d\n",
		clk_sys_rates[best].ratio);
	घड़ी1 |= (clk_sys_rates[best].clk_sys_rate
		   << WM8904_CLK_SYS_RATE_SHIFT);

	/* SAMPLE_RATE */
	best = 0;
	best_val = असल(wm8904->fs - sample_rates[0].rate);
	क्रम (i = 1; i < ARRAY_SIZE(sample_rates); i++) अणु
		/* Closest match */
		cur_val = असल(wm8904->fs - sample_rates[i].rate);
		अगर (cur_val < best_val) अणु
			best = i;
			best_val = cur_val;
		पूर्ण
	पूर्ण
	dev_dbg(component->dev, "Selected SAMPLE_RATE of %dHz\n",
		sample_rates[best].rate);
	घड़ी1 |= (sample_rates[best].sample_rate
		   << WM8904_SAMPLE_RATE_SHIFT);

	/* Enable sloping stopband filter क्रम low sample rates */
	अगर (wm8904->fs <= 24000)
		dac_digital1 |= WM8904_DAC_SB_FILT;

	/* BCLK_DIV */
	best = 0;
	best_val = पूर्णांक_उच्च;
	क्रम (i = 0; i < ARRAY_SIZE(bclk_भागs); i++) अणु
		cur_val = ((wm8904->sysclk_rate * 10) / bclk_भागs[i].भाग)
			- wm8904->bclk;
		अगर (cur_val < 0) /* Table is sorted */
			अवरोध;
		अगर (cur_val < best_val) अणु
			best = i;
			best_val = cur_val;
		पूर्ण
	पूर्ण
	wm8904->bclk = (wm8904->sysclk_rate * 10) / bclk_भागs[best].भाग;
	dev_dbg(component->dev, "Selected BCLK_DIV of %d for %dHz BCLK\n",
		bclk_भागs[best].भाग, wm8904->bclk);
	aअगर2 |= bclk_भागs[best].bclk_भाग;

	/* LRCLK is a simple fraction of BCLK */
	dev_dbg(component->dev, "LRCLK_RATE is %d\n", wm8904->bclk / wm8904->fs);
	aअगर3 |= wm8904->bclk / wm8904->fs;

	/* Apply the settings */
	snd_soc_component_update_bits(component, WM8904_DAC_DIGITAL_1,
			    WM8904_DAC_SB_FILT, dac_digital1);
	snd_soc_component_update_bits(component, WM8904_AUDIO_INTERFACE_1,
			    WM8904_AIF_WL_MASK, aअगर1);
	snd_soc_component_update_bits(component, WM8904_AUDIO_INTERFACE_2,
			    WM8904_BCLK_DIV_MASK, aअगर2);
	snd_soc_component_update_bits(component, WM8904_AUDIO_INTERFACE_3,
			    WM8904_LRCLK_RATE_MASK, aअगर3);
	snd_soc_component_update_bits(component, WM8904_CLOCK_RATES_1,
			    WM8904_SAMPLE_RATE_MASK |
			    WM8904_CLK_SYS_RATE_MASK, घड़ी1);

	/* Update filters क्रम the new settings */
	wm8904_set_retune_mobile(component);
	wm8904_set_deemph(component);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8904_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक aअगर1 = 0;
	अचिन्हित पूर्णांक aअगर3 = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		aअगर3 |= WM8904_LRCLK_सूची;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		aअगर1 |= WM8904_BCLK_सूची;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		aअगर1 |= WM8904_BCLK_सूची;
		aअगर3 |= WM8904_LRCLK_सूची;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_B:
		aअगर1 |= 0x3 | WM8904_AIF_LRCLK_INV;
		fallthrough;
	हाल SND_SOC_DAIFMT_DSP_A:
		aअगर1 |= 0x3;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		aअगर1 |= 0x2;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		aअगर1 |= 0x1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
	हाल SND_SOC_DAIFMT_DSP_B:
		/* frame inversion not valid क्रम DSP modes */
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			aअगर1 |= WM8904_AIF_BCLK_INV;
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
			aअगर1 |= WM8904_AIF_BCLK_INV | WM8904_AIF_LRCLK_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			aअगर1 |= WM8904_AIF_BCLK_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_NB_IF:
			aअगर1 |= WM8904_AIF_LRCLK_INV;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, WM8904_AUDIO_INTERFACE_1,
			    WM8904_AIF_BCLK_INV | WM8904_AIF_LRCLK_INV |
			    WM8904_AIF_FMT_MASK | WM8904_BCLK_सूची, aअगर1);
	snd_soc_component_update_bits(component, WM8904_AUDIO_INTERFACE_3,
			    WM8904_LRCLK_सूची, aअगर3);

	वापस 0;
पूर्ण


अटल पूर्णांक wm8904_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
			       अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);
	पूर्णांक aअगर1 = 0;

	/* Don't need to validate anything if we're turning off TDM */
	अगर (slots == 0)
		जाओ out;

	/* Note that we allow configurations we can't handle ourselves - 
	 * क्रम example, we can generate घड़ीs क्रम slots 2 and up even अगर
	 * we can't use those slots ourselves.
	 */
	aअगर1 |= WM8904_AIFADC_TDM | WM8904_AIFDAC_TDM;

	चयन (rx_mask) अणु
	हाल 3:
		अवरोध;
	हाल 0xc:
		aअगर1 |= WM8904_AIFADC_TDM_CHAN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण


	चयन (tx_mask) अणु
	हाल 3:
		अवरोध;
	हाल 0xc:
		aअगर1 |= WM8904_AIFDAC_TDM_CHAN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

out:
	wm8904->tdm_width = slot_width;
	wm8904->tdm_slots = slots / 2;

	snd_soc_component_update_bits(component, WM8904_AUDIO_INTERFACE_1,
			    WM8904_AIFADC_TDM | WM8904_AIFADC_TDM_CHAN |
			    WM8904_AIFDAC_TDM | WM8904_AIFDAC_TDM_CHAN, aअगर1);

	वापस 0;
पूर्ण

काष्ठा _fll_भाग अणु
	u16 fll_fratio;
	u16 fll_outभाग;
	u16 fll_clk_ref_भाग;
	u16 n;
	u16 k;
पूर्ण;

/* The size in bits of the FLL भागide multiplied by 10
 * to allow rounding later */
#घोषणा FIXED_FLL_SIZE ((1 << 16) * 10)

अटल काष्ठा अणु
	अचिन्हित पूर्णांक min;
	अचिन्हित पूर्णांक max;
	u16 fll_fratio;
	पूर्णांक ratio;
पूर्ण fll_fratios[] = अणु
	अणु       0,    64000, 4, 16 पूर्ण,
	अणु   64000,   128000, 3,  8 पूर्ण,
	अणु  128000,   256000, 2,  4 पूर्ण,
	अणु  256000,  1000000, 1,  2 पूर्ण,
	अणु 1000000, 13500000, 0,  1 पूर्ण,
पूर्ण;

अटल पूर्णांक fll_factors(काष्ठा _fll_भाग *fll_भाग, अचिन्हित पूर्णांक Fref,
		       अचिन्हित पूर्णांक Fout)
अणु
	u64 Kpart;
	अचिन्हित पूर्णांक K, Nभाग, Nmod, target;
	अचिन्हित पूर्णांक भाग;
	पूर्णांक i;

	/* Fref must be <=13.5MHz */
	भाग = 1;
	fll_भाग->fll_clk_ref_भाग = 0;
	जबतक ((Fref / भाग) > 13500000) अणु
		भाग *= 2;
		fll_भाग->fll_clk_ref_भाग++;

		अगर (भाग > 8) अणु
			pr_err("Can't scale %dMHz input down to <=13.5MHz\n",
			       Fref);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	pr_debug("Fref=%u Fout=%u\n", Fref, Fout);

	/* Apply the भागision क्रम our reमुख्यing calculations */
	Fref /= भाग;

	/* Fvco should be 90-100MHz; करोn't check the upper bound */
	भाग = 4;
	जबतक (Fout * भाग < 90000000) अणु
		भाग++;
		अगर (भाग > 64) अणु
			pr_err("Unable to find FLL_OUTDIV for Fout=%uHz\n",
			       Fout);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	target = Fout * भाग;
	fll_भाग->fll_outभाग = भाग - 1;

	pr_debug("Fvco=%dHz\n", target);

	/* Find an appropriate FLL_FRATIO and factor it out of the target */
	क्रम (i = 0; i < ARRAY_SIZE(fll_fratios); i++) अणु
		अगर (fll_fratios[i].min <= Fref && Fref <= fll_fratios[i].max) अणु
			fll_भाग->fll_fratio = fll_fratios[i].fll_fratio;
			target /= fll_fratios[i].ratio;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(fll_fratios)) अणु
		pr_err("Unable to find FLL_FRATIO for Fref=%uHz\n", Fref);
		वापस -EINVAL;
	पूर्ण

	/* Now, calculate N.K */
	Nभाग = target / Fref;

	fll_भाग->n = Nभाग;
	Nmod = target % Fref;
	pr_debug("Nmod=%d\n", Nmod);

	/* Calculate fractional part - scale up so we can round. */
	Kpart = FIXED_FLL_SIZE * (दीर्घ दीर्घ)Nmod;

	करो_भाग(Kpart, Fref);

	K = Kpart & 0xFFFFFFFF;

	अगर ((K % 10) >= 5)
		K += 5;

	/* Move करोwn to proper range now rounding is करोne */
	fll_भाग->k = K / 10;

	pr_debug("N=%x K=%x FLL_FRATIO=%x FLL_OUTDIV=%x FLL_CLK_REF_DIV=%x\n",
		 fll_भाग->n, fll_भाग->k,
		 fll_भाग->fll_fratio, fll_भाग->fll_outभाग,
		 fll_भाग->fll_clk_ref_भाग);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8904_set_fll(काष्ठा snd_soc_dai *dai, पूर्णांक fll_id, पूर्णांक source,
			  अचिन्हित पूर्णांक Fref, अचिन्हित पूर्णांक Fout)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);
	काष्ठा _fll_भाग fll_भाग;
	पूर्णांक ret, val;
	पूर्णांक घड़ी2, fll1;

	/* Any change? */
	अगर (source == wm8904->fll_src && Fref == wm8904->fll_fref &&
	    Fout == wm8904->fll_fout)
		वापस 0;

	घड़ी2 = snd_soc_component_पढ़ो(component, WM8904_CLOCK_RATES_2);

	अगर (Fout == 0) अणु
		dev_dbg(component->dev, "FLL disabled\n");

		wm8904->fll_fref = 0;
		wm8904->fll_fout = 0;

		/* Gate SYSCLK to aव्योम glitches */
		snd_soc_component_update_bits(component, WM8904_CLOCK_RATES_2,
				    WM8904_CLK_SYS_ENA, 0);

		snd_soc_component_update_bits(component, WM8904_FLL_CONTROL_1,
				    WM8904_FLL_OSC_ENA | WM8904_FLL_ENA, 0);

		जाओ out;
	पूर्ण

	/* Validate the FLL ID */
	चयन (source) अणु
	हाल WM8904_FLL_MCLK:
	हाल WM8904_FLL_LRCLK:
	हाल WM8904_FLL_BCLK:
		ret = fll_factors(&fll_भाग, Fref, Fout);
		अगर (ret != 0)
			वापस ret;
		अवरोध;

	हाल WM8904_FLL_FREE_RUNNING:
		dev_dbg(component->dev, "Using free running FLL\n");
		/* Force 12MHz and output/4 क्रम now */
		Fout = 12000000;
		Fref = 12000000;

		स_रखो(&fll_भाग, 0, माप(fll_भाग));
		fll_भाग.fll_outभाग = 3;
		अवरोध;

	शेष:
		dev_err(component->dev, "Unknown FLL ID %d\n", fll_id);
		वापस -EINVAL;
	पूर्ण

	/* Save current state then disable the FLL and SYSCLK to aव्योम
	 * misघड़ीing */
	fll1 = snd_soc_component_पढ़ो(component, WM8904_FLL_CONTROL_1);
	snd_soc_component_update_bits(component, WM8904_CLOCK_RATES_2,
			    WM8904_CLK_SYS_ENA, 0);
	snd_soc_component_update_bits(component, WM8904_FLL_CONTROL_1,
			    WM8904_FLL_OSC_ENA | WM8904_FLL_ENA, 0);

	/* Unlock क्रमced oscilator control to चयन it on/off */
	snd_soc_component_update_bits(component, WM8904_CONTROL_INTERFACE_TEST_1,
			    WM8904_USER_KEY, WM8904_USER_KEY);

	अगर (fll_id == WM8904_FLL_FREE_RUNNING) अणु
		val = WM8904_FLL_FRC_NCO;
	पूर्ण अन्यथा अणु
		val = 0;
	पूर्ण

	snd_soc_component_update_bits(component, WM8904_FLL_NCO_TEST_1, WM8904_FLL_FRC_NCO,
			    val);
	snd_soc_component_update_bits(component, WM8904_CONTROL_INTERFACE_TEST_1,
			    WM8904_USER_KEY, 0);

	चयन (fll_id) अणु
	हाल WM8904_FLL_MCLK:
		snd_soc_component_update_bits(component, WM8904_FLL_CONTROL_5,
				    WM8904_FLL_CLK_REF_SRC_MASK, 0);
		अवरोध;

	हाल WM8904_FLL_LRCLK:
		snd_soc_component_update_bits(component, WM8904_FLL_CONTROL_5,
				    WM8904_FLL_CLK_REF_SRC_MASK, 1);
		अवरोध;

	हाल WM8904_FLL_BCLK:
		snd_soc_component_update_bits(component, WM8904_FLL_CONTROL_5,
				    WM8904_FLL_CLK_REF_SRC_MASK, 2);
		अवरोध;
	पूर्ण

	अगर (fll_भाग.k)
		val = WM8904_FLL_FRACN_ENA;
	अन्यथा
		val = 0;
	snd_soc_component_update_bits(component, WM8904_FLL_CONTROL_1,
			    WM8904_FLL_FRACN_ENA, val);

	snd_soc_component_update_bits(component, WM8904_FLL_CONTROL_2,
			    WM8904_FLL_OUTDIV_MASK | WM8904_FLL_FRATIO_MASK,
			    (fll_भाग.fll_outभाग << WM8904_FLL_OUTDIV_SHIFT) |
			    (fll_भाग.fll_fratio << WM8904_FLL_FRATIO_SHIFT));

	snd_soc_component_ग_लिखो(component, WM8904_FLL_CONTROL_3, fll_भाग.k);

	snd_soc_component_update_bits(component, WM8904_FLL_CONTROL_4, WM8904_FLL_N_MASK,
			    fll_भाग.n << WM8904_FLL_N_SHIFT);

	snd_soc_component_update_bits(component, WM8904_FLL_CONTROL_5,
			    WM8904_FLL_CLK_REF_DIV_MASK,
			    fll_भाग.fll_clk_ref_भाग 
			    << WM8904_FLL_CLK_REF_DIV_SHIFT);

	dev_dbg(component->dev, "FLL configured for %dHz->%dHz\n", Fref, Fout);

	wm8904->fll_fref = Fref;
	wm8904->fll_fout = Fout;
	wm8904->fll_src = source;

	/* Enable the FLL अगर it was previously active */
	snd_soc_component_update_bits(component, WM8904_FLL_CONTROL_1,
			    WM8904_FLL_OSC_ENA, fll1);
	snd_soc_component_update_bits(component, WM8904_FLL_CONTROL_1,
			    WM8904_FLL_ENA, fll1);

out:
	/* Reenable SYSCLK अगर it was previously active */
	snd_soc_component_update_bits(component, WM8904_CLOCK_RATES_2,
			    WM8904_CLK_SYS_ENA, घड़ी2);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8904_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
			     अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8904_priv *priv = snd_soc_component_get_drvdata(component);
	अचिन्हित दीर्घ mclk_freq;
	पूर्णांक ret;

	चयन (clk_id) अणु
	हाल WM8904_CLK_AUTO:
		/* We करोn't have any rate स्थिरraपूर्णांकs, so just ignore the
		 * request to disable स्थिरraining.
		 */
		अगर (!freq)
			वापस 0;

		mclk_freq = clk_get_rate(priv->mclk);
		/* enable FLL अगर a dअगरferent sysclk is desired */
		अगर (mclk_freq != freq) अणु
			priv->sysclk_src = WM8904_CLK_FLL;
			ret = wm8904_set_fll(dai, WM8904_FLL_MCLK,
					     WM8904_FLL_MCLK,
					     mclk_freq, freq);
			अगर (ret)
				वापस ret;
			अवरोध;
		पूर्ण
		clk_id = WM8904_CLK_MCLK;
		fallthrough;

	हाल WM8904_CLK_MCLK:
		priv->sysclk_src = clk_id;
		priv->mclk_rate = freq;
		अवरोध;

	हाल WM8904_CLK_FLL:
		priv->sysclk_src = clk_id;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dai->dev, "Clock source is %d at %uHz\n", clk_id, freq);

	wm8904_configure_घड़ीing(component);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8904_mute(काष्ठा snd_soc_dai *codec_dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	पूर्णांक val;

	अगर (mute)
		val = WM8904_DAC_MUTE;
	अन्यथा
		val = 0;

	snd_soc_component_update_bits(component, WM8904_DAC_DIGITAL_1, WM8904_DAC_MUTE, val);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8904_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		/* VMID resistance 2*50k */
		snd_soc_component_update_bits(component, WM8904_VMID_CONTROL_0,
				    WM8904_VMID_RES_MASK,
				    0x1 << WM8904_VMID_RES_SHIFT);

		/* Normal bias current */
		snd_soc_component_update_bits(component, WM8904_BIAS_CONTROL_0,
				    WM8904_ISEL_MASK, 2 << WM8904_ISEL_SHIFT);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			ret = regulator_bulk_enable(ARRAY_SIZE(wm8904->supplies),
						    wm8904->supplies);
			अगर (ret != 0) अणु
				dev_err(component->dev,
					"Failed to enable supplies: %d\n",
					ret);
				वापस ret;
			पूर्ण

			ret = clk_prepare_enable(wm8904->mclk);
			अगर (ret) अणु
				dev_err(component->dev,
					"Failed to enable MCLK: %d\n", ret);
				regulator_bulk_disable(ARRAY_SIZE(wm8904->supplies),
						       wm8904->supplies);
				वापस ret;
			पूर्ण

			regcache_cache_only(wm8904->regmap, false);
			regcache_sync(wm8904->regmap);

			/* Enable bias */
			snd_soc_component_update_bits(component, WM8904_BIAS_CONTROL_0,
					    WM8904_BIAS_ENA, WM8904_BIAS_ENA);

			/* Enable VMID, VMID buffering, 2*5k resistance */
			snd_soc_component_update_bits(component, WM8904_VMID_CONTROL_0,
					    WM8904_VMID_ENA |
					    WM8904_VMID_RES_MASK,
					    WM8904_VMID_ENA |
					    0x3 << WM8904_VMID_RES_SHIFT);

			/* Let VMID ramp */
			msleep(1);
		पूर्ण

		/* Maपूर्णांकain VMID with 2*250k */
		snd_soc_component_update_bits(component, WM8904_VMID_CONTROL_0,
				    WM8904_VMID_RES_MASK,
				    0x2 << WM8904_VMID_RES_SHIFT);

		/* Bias current *0.5 */
		snd_soc_component_update_bits(component, WM8904_BIAS_CONTROL_0,
				    WM8904_ISEL_MASK, 0);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		/* Turn off VMID */
		snd_soc_component_update_bits(component, WM8904_VMID_CONTROL_0,
				    WM8904_VMID_RES_MASK | WM8904_VMID_ENA, 0);

		/* Stop bias generation */
		snd_soc_component_update_bits(component, WM8904_BIAS_CONTROL_0,
				    WM8904_BIAS_ENA, 0);

		snd_soc_component_ग_लिखो(component, WM8904_SW_RESET_AND_ID, 0);
		regcache_cache_only(wm8904->regmap, true);
		regcache_mark_dirty(wm8904->regmap);

		regulator_bulk_disable(ARRAY_SIZE(wm8904->supplies),
				       wm8904->supplies);
		clk_disable_unprepare(wm8904->mclk);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा WM8904_RATES SNDRV_PCM_RATE_8000_96000

#घोषणा WM8904_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8904_dai_ops = अणु
	.set_sysclk = wm8904_set_sysclk,
	.set_fmt = wm8904_set_fmt,
	.set_tdm_slot = wm8904_set_tdm_slot,
	.set_pll = wm8904_set_fll,
	.hw_params = wm8904_hw_params,
	.mute_stream = wm8904_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8904_dai = अणु
	.name = "wm8904-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = WM8904_RATES,
		.क्रमmats = WM8904_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = WM8904_RATES,
		.क्रमmats = WM8904_FORMATS,
	पूर्ण,
	.ops = &wm8904_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल व्योम wm8904_handle_retune_mobile_pdata(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8904_pdata *pdata = wm8904->pdata;
	काष्ठा snd_kcontrol_new control =
		SOC_ENUM_EXT("EQ Mode",
			     wm8904->retune_mobile_क्रमागत,
			     wm8904_get_retune_mobile_क्रमागत,
			     wm8904_put_retune_mobile_क्रमागत);
	पूर्णांक ret, i, j;
	स्थिर अक्षर **t;

	/* We need an array of texts क्रम the क्रमागत API but the number
	 * of texts is likely to be less than the number of
	 * configurations due to the sample rate dependency of the
	 * configurations. */
	wm8904->num_retune_mobile_texts = 0;
	wm8904->retune_mobile_texts = शून्य;
	क्रम (i = 0; i < pdata->num_retune_mobile_cfgs; i++) अणु
		क्रम (j = 0; j < wm8904->num_retune_mobile_texts; j++) अणु
			अगर (म_भेद(pdata->retune_mobile_cfgs[i].name,
				   wm8904->retune_mobile_texts[j]) == 0)
				अवरोध;
		पूर्ण

		अगर (j != wm8904->num_retune_mobile_texts)
			जारी;

		/* Expand the array... */
		t = kपुनः_स्मृति(wm8904->retune_mobile_texts,
			     माप(अक्षर *) * 
			     (wm8904->num_retune_mobile_texts + 1),
			     GFP_KERNEL);
		अगर (t == शून्य)
			जारी;

		/* ...store the new entry... */
		t[wm8904->num_retune_mobile_texts] = 
			pdata->retune_mobile_cfgs[i].name;

		/* ...and remember the new version. */
		wm8904->num_retune_mobile_texts++;
		wm8904->retune_mobile_texts = t;
	पूर्ण

	dev_dbg(component->dev, "Allocated %d unique ReTune Mobile names\n",
		wm8904->num_retune_mobile_texts);

	wm8904->retune_mobile_क्रमागत.items = wm8904->num_retune_mobile_texts;
	wm8904->retune_mobile_क्रमागत.texts = wm8904->retune_mobile_texts;

	ret = snd_soc_add_component_controls(component, &control, 1);
	अगर (ret != 0)
		dev_err(component->dev,
			"Failed to add ReTune Mobile control: %d\n", ret);
पूर्ण

अटल व्योम wm8904_handle_pdata(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8904_pdata *pdata = wm8904->pdata;
	पूर्णांक ret, i;

	अगर (!pdata) अणु
		snd_soc_add_component_controls(component, wm8904_eq_controls,
				     ARRAY_SIZE(wm8904_eq_controls));
		वापस;
	पूर्ण

	dev_dbg(component->dev, "%d DRC configurations\n", pdata->num_drc_cfgs);

	अगर (pdata->num_drc_cfgs) अणु
		काष्ठा snd_kcontrol_new control =
			SOC_ENUM_EXT("DRC Mode", wm8904->drc_क्रमागत,
				     wm8904_get_drc_क्रमागत, wm8904_put_drc_क्रमागत);

		/* We need an array of texts क्रम the क्रमागत API */
		wm8904->drc_texts = kदो_स्मृति_array(pdata->num_drc_cfgs,
						  माप(अक्षर *),
						  GFP_KERNEL);
		अगर (!wm8904->drc_texts)
			वापस;

		क्रम (i = 0; i < pdata->num_drc_cfgs; i++)
			wm8904->drc_texts[i] = pdata->drc_cfgs[i].name;

		wm8904->drc_क्रमागत.items = pdata->num_drc_cfgs;
		wm8904->drc_क्रमागत.texts = wm8904->drc_texts;

		ret = snd_soc_add_component_controls(component, &control, 1);
		अगर (ret != 0)
			dev_err(component->dev,
				"Failed to add DRC mode control: %d\n", ret);

		wm8904_set_drc(component);
	पूर्ण

	dev_dbg(component->dev, "%d ReTune Mobile configurations\n",
		pdata->num_retune_mobile_cfgs);

	अगर (pdata->num_retune_mobile_cfgs)
		wm8904_handle_retune_mobile_pdata(component);
	अन्यथा
		snd_soc_add_component_controls(component, wm8904_eq_controls,
				     ARRAY_SIZE(wm8904_eq_controls));
पूर्ण


अटल पूर्णांक wm8904_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);

	चयन (wm8904->devtype) अणु
	हाल WM8904:
		अवरोध;
	हाल WM8912:
		स_रखो(&wm8904_dai.capture, 0, माप(wm8904_dai.capture));
		अवरोध;
	शेष:
		dev_err(component->dev, "Unknown device type %d\n",
			wm8904->devtype);
		वापस -EINVAL;
	पूर्ण

	wm8904_handle_pdata(component);

	wm8904_add_widमाला_लो(component);

	वापस 0;
पूर्ण

अटल व्योम wm8904_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);

	kमुक्त(wm8904->retune_mobile_texts);
	kमुक्त(wm8904->drc_texts);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8904 = अणु
	.probe			= wm8904_probe,
	.हटाओ			= wm8904_हटाओ,
	.set_bias_level		= wm8904_set_bias_level,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm8904_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,

	.max_रेजिस्टर = WM8904_MAX_REGISTER,
	.अस्थिर_reg = wm8904_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = wm8904_पढ़ोable_रेजिस्टर,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = wm8904_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8904_reg_शेषs),
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id wm8904_of_match[] = अणु
	अणु
		.compatible = "wlf,wm8904",
		.data = (व्योम *)WM8904,
	पूर्ण, अणु
		.compatible = "wlf,wm8912",
		.data = (व्योम *)WM8912,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wm8904_of_match);
#पूर्ण_अगर

अटल पूर्णांक wm8904_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8904_priv *wm8904;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret, i;

	wm8904 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8904_priv),
			      GFP_KERNEL);
	अगर (wm8904 == शून्य)
		वापस -ENOMEM;

	wm8904->mclk = devm_clk_get(&i2c->dev, "mclk");
	अगर (IS_ERR(wm8904->mclk)) अणु
		ret = PTR_ERR(wm8904->mclk);
		dev_err(&i2c->dev, "Failed to get MCLK\n");
		वापस ret;
	पूर्ण

	wm8904->regmap = devm_regmap_init_i2c(i2c, &wm8904_regmap);
	अगर (IS_ERR(wm8904->regmap)) अणु
		ret = PTR_ERR(wm8904->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (i2c->dev.of_node) अणु
		स्थिर काष्ठा of_device_id *match;

		match = of_match_node(wm8904_of_match, i2c->dev.of_node);
		अगर (match == शून्य)
			वापस -EINVAL;
		wm8904->devtype = (क्रमागत wm8904_type)match->data;
	पूर्ण अन्यथा अणु
		wm8904->devtype = id->driver_data;
	पूर्ण

	i2c_set_clientdata(i2c, wm8904);
	wm8904->pdata = i2c->dev.platक्रमm_data;

	क्रम (i = 0; i < ARRAY_SIZE(wm8904->supplies); i++)
		wm8904->supplies[i].supply = wm8904_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev, ARRAY_SIZE(wm8904->supplies),
				      wm8904->supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8904->supplies),
				    wm8904->supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(wm8904->regmap, WM8904_SW_RESET_AND_ID, &val);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to read ID register: %d\n", ret);
		जाओ err_enable;
	पूर्ण
	अगर (val != 0x8904) अणु
		dev_err(&i2c->dev, "Device is not a WM8904, ID is %x\n", val);
		ret = -EINVAL;
		जाओ err_enable;
	पूर्ण

	ret = regmap_पढ़ो(wm8904->regmap, WM8904_REVISION, &val);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to read device revision: %d\n",
			ret);
		जाओ err_enable;
	पूर्ण
	dev_info(&i2c->dev, "revision %c\n", val + 'A');

	ret = regmap_ग_लिखो(wm8904->regmap, WM8904_SW_RESET_AND_ID, 0);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to issue reset: %d\n", ret);
		जाओ err_enable;
	पूर्ण

	/* Change some शेष settings - latch VU and enable ZC */
	regmap_update_bits(wm8904->regmap, WM8904_ADC_DIGITAL_VOLUME_LEFT,
			   WM8904_ADC_VU, WM8904_ADC_VU);
	regmap_update_bits(wm8904->regmap, WM8904_ADC_DIGITAL_VOLUME_RIGHT,
			   WM8904_ADC_VU, WM8904_ADC_VU);
	regmap_update_bits(wm8904->regmap, WM8904_DAC_DIGITAL_VOLUME_LEFT,
			   WM8904_DAC_VU, WM8904_DAC_VU);
	regmap_update_bits(wm8904->regmap, WM8904_DAC_DIGITAL_VOLUME_RIGHT,
			   WM8904_DAC_VU, WM8904_DAC_VU);
	regmap_update_bits(wm8904->regmap, WM8904_ANALOGUE_OUT1_LEFT,
			   WM8904_HPOUT_VU | WM8904_HPOUTLZC,
			   WM8904_HPOUT_VU | WM8904_HPOUTLZC);
	regmap_update_bits(wm8904->regmap, WM8904_ANALOGUE_OUT1_RIGHT,
			   WM8904_HPOUT_VU | WM8904_HPOUTRZC,
			   WM8904_HPOUT_VU | WM8904_HPOUTRZC);
	regmap_update_bits(wm8904->regmap, WM8904_ANALOGUE_OUT2_LEFT,
			   WM8904_LINEOUT_VU | WM8904_LINEOUTLZC,
			   WM8904_LINEOUT_VU | WM8904_LINEOUTLZC);
	regmap_update_bits(wm8904->regmap, WM8904_ANALOGUE_OUT2_RIGHT,
			   WM8904_LINEOUT_VU | WM8904_LINEOUTRZC,
			   WM8904_LINEOUT_VU | WM8904_LINEOUTRZC);
	regmap_update_bits(wm8904->regmap, WM8904_CLOCK_RATES_0,
			   WM8904_SR_MODE, 0);

	/* Apply configuration from the platक्रमm data. */
	अगर (wm8904->pdata) अणु
		क्रम (i = 0; i < WM8904_GPIO_REGS; i++) अणु
			अगर (!wm8904->pdata->gpio_cfg[i])
				जारी;

			regmap_update_bits(wm8904->regmap,
					   WM8904_GPIO_CONTROL_1 + i,
					   0xffff,
					   wm8904->pdata->gpio_cfg[i]);
		पूर्ण

		/* Zero is the शेष value क्रम these anyway */
		क्रम (i = 0; i < WM8904_MIC_REGS; i++)
			regmap_update_bits(wm8904->regmap,
					   WM8904_MIC_BIAS_CONTROL_0 + i,
					   0xffff,
					   wm8904->pdata->mic_cfg[i]);
	पूर्ण

	/* Set Class W by शेष - this will be managed by the Class
	 * G widget at runसमय where bypass paths are available.
	 */
	regmap_update_bits(wm8904->regmap, WM8904_CLASS_W_0,
			    WM8904_CP_DYN_PWR, WM8904_CP_DYN_PWR);

	/* Use normal bias source */
	regmap_update_bits(wm8904->regmap, WM8904_BIAS_CONTROL_0,
			    WM8904_POBCTRL, 0);

	/* Can leave the device घातered off until we need it */
	regcache_cache_only(wm8904->regmap, true);
	regulator_bulk_disable(ARRAY_SIZE(wm8904->supplies), wm8904->supplies);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_wm8904, &wm8904_dai, 1);
	अगर (ret != 0)
		वापस ret;

	वापस 0;

err_enable:
	regulator_bulk_disable(ARRAY_SIZE(wm8904->supplies), wm8904->supplies);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8904_i2c_id[] = अणु
	अणु "wm8904", WM8904 पूर्ण,
	अणु "wm8912", WM8912 पूर्ण,
	अणु "wm8918", WM8904 पूर्ण,   /* Actually a subset, updates to follow */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8904_i2c_id);

अटल काष्ठा i2c_driver wm8904_i2c_driver = अणु
	.driver = अणु
		.name = "wm8904",
		.of_match_table = of_match_ptr(wm8904_of_match),
	पूर्ण,
	.probe =    wm8904_i2c_probe,
	.id_table = wm8904_i2c_id,
पूर्ण;

module_i2c_driver(wm8904_i2c_driver);

MODULE_DESCRIPTION("ASoC WM8904 driver");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
