<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8993.c -- WM8993 ALSA SoC audio driver
 *
 * Copyright 2009-12 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
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
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/wm8993.h>

#समावेश "wm8993.h"
#समावेश "wm_hubs.h"

#घोषणा WM8993_NUM_SUPPLIES 6
अटल स्थिर अक्षर *wm8993_supply_names[WM8993_NUM_SUPPLIES] = अणु
	"DCVDD",
	"DBVDD",
	"AVDD1",
	"AVDD2",
	"CPVDD",
	"SPKVDD",
पूर्ण;

अटल स्थिर काष्ठा reg_शेष wm8993_reg_शेषs[] = अणु
	अणु 1,   0x0000 पूर्ण,     /* R1   - Power Management (1) */
	अणु 2,   0x6000 पूर्ण,     /* R2   - Power Management (2) */
	अणु 3,   0x0000 पूर्ण,     /* R3   - Power Management (3) */
	अणु 4,   0x4050 पूर्ण,     /* R4   - Audio Interface (1) */
	अणु 5,   0x4000 पूर्ण,     /* R5   - Audio Interface (2) */
	अणु 6,   0x01C8 पूर्ण,     /* R6   - Clocking 1 */
	अणु 7,   0x0000 पूर्ण,     /* R7   - Clocking 2 */
	अणु 8,   0x0000 पूर्ण,     /* R8   - Audio Interface (3) */
	अणु 9,   0x0040 पूर्ण,     /* R9   - Audio Interface (4) */
	अणु 10,  0x0004 पूर्ण,     /* R10  - DAC CTRL */
	अणु 11,  0x00C0 पूर्ण,     /* R11  - Left DAC Digital Volume */
	अणु 12,  0x00C0 पूर्ण,     /* R12  - Right DAC Digital Volume */
	अणु 13,  0x0000 पूर्ण,     /* R13  - Digital Side Tone */
	अणु 14,  0x0300 पूर्ण,     /* R14  - ADC CTRL */
	अणु 15,  0x00C0 पूर्ण,     /* R15  - Left ADC Digital Volume */
	अणु 16,  0x00C0 पूर्ण,     /* R16  - Right ADC Digital Volume */
	अणु 18,  0x0000 पूर्ण,     /* R18  - GPIO CTRL 1 */
	अणु 19,  0x0010 पूर्ण,     /* R19  - GPIO1 */
	अणु 20,  0x0000 पूर्ण,     /* R20  - IRQ_DEBOUNCE */
	अणु 21,  0x0000 पूर्ण,     /* R21  - Inमाला_दो Clamp */
	अणु 22,  0x8000 पूर्ण,     /* R22  - GPIOCTRL 2 */
	अणु 23,  0x0800 पूर्ण,     /* R23  - GPIO_POL */
	अणु 24,  0x008B पूर्ण,     /* R24  - Left Line Input 1&2 Volume */
	अणु 25,  0x008B पूर्ण,     /* R25  - Left Line Input 3&4 Volume */
	अणु 26,  0x008B पूर्ण,     /* R26  - Right Line Input 1&2 Volume */
	अणु 27,  0x008B पूर्ण,     /* R27  - Right Line Input 3&4 Volume */
	अणु 28,  0x006D पूर्ण,     /* R28  - Left Output Volume */
	अणु 29,  0x006D पूर्ण,     /* R29  - Right Output Volume */
	अणु 30,  0x0066 पूर्ण,     /* R30  - Line Outमाला_दो Volume */
	अणु 31,  0x0020 पूर्ण,     /* R31  - HPOUT2 Volume */
	अणु 32,  0x0079 पूर्ण,     /* R32  - Left OPGA Volume */
	अणु 33,  0x0079 पूर्ण,     /* R33  - Right OPGA Volume */
	अणु 34,  0x0003 पूर्ण,     /* R34  - SPKMIXL Attenuation */
	अणु 35,  0x0003 पूर्ण,     /* R35  - SPKMIXR Attenuation */
	अणु 36,  0x0011 पूर्ण,     /* R36  - SPKOUT Mixers */
	अणु 37,  0x0100 पूर्ण,     /* R37  - SPKOUT Boost */
	अणु 38,  0x0079 पूर्ण,     /* R38  - Speaker Volume Left */
	अणु 39,  0x0079 पूर्ण,     /* R39  - Speaker Volume Right */
	अणु 40,  0x0000 पूर्ण,     /* R40  - Input Mixer2 */
	अणु 41,  0x0000 पूर्ण,     /* R41  - Input Mixer3 */
	अणु 42,  0x0000 पूर्ण,     /* R42  - Input Mixer4 */
	अणु 43,  0x0000 पूर्ण,     /* R43  - Input Mixer5 */
	अणु 44,  0x0000 पूर्ण,     /* R44  - Input Mixer6 */
	अणु 45,  0x0000 पूर्ण,     /* R45  - Output Mixer1 */
	अणु 46,  0x0000 पूर्ण,     /* R46  - Output Mixer2 */
	अणु 47,  0x0000 पूर्ण,     /* R47  - Output Mixer3 */
	अणु 48,  0x0000 पूर्ण,     /* R48  - Output Mixer4 */
	अणु 49,  0x0000 पूर्ण,     /* R49  - Output Mixer5 */
	अणु 50,  0x0000 पूर्ण,     /* R50  - Output Mixer6 */
	अणु 51,  0x0000 पूर्ण,     /* R51  - HPOUT2 Mixer */
	अणु 52,  0x0000 पूर्ण,     /* R52  - Line Mixer1 */
	अणु 53,  0x0000 पूर्ण,     /* R53  - Line Mixer2 */
	अणु 54,  0x0000 पूर्ण,     /* R54  - Speaker Mixer */
	अणु 55,  0x0000 पूर्ण,     /* R55  - Additional Control */
	अणु 56,  0x0000 पूर्ण,     /* R56  - AntiPOP1 */
	अणु 57,  0x0000 पूर्ण,     /* R57  - AntiPOP2 */
	अणु 58,  0x0000 पूर्ण,     /* R58  - MICBIAS */
	अणु 60,  0x0000 पूर्ण,     /* R60  - FLL Control 1 */
	अणु 61,  0x0000 पूर्ण,     /* R61  - FLL Control 2 */
	अणु 62,  0x0000 पूर्ण,     /* R62  - FLL Control 3 */
	अणु 63,  0x2EE0 पूर्ण,     /* R63  - FLL Control 4 */
	अणु 64,  0x0002 पूर्ण,     /* R64  - FLL Control 5 */
	अणु 65,  0x2287 पूर्ण,     /* R65  - Clocking 3 */
	अणु 66,  0x025F पूर्ण,     /* R66  - Clocking 4 */
	अणु 67,  0x0000 पूर्ण,     /* R67  - MW Slave Control */
	अणु 69,  0x0002 पूर्ण,     /* R69  - Bus Control 1 */
	अणु 70,  0x0000 पूर्ण,     /* R70  - Write Sequencer 0 */
	अणु 71,  0x0000 पूर्ण,     /* R71  - Write Sequencer 1 */
	अणु 72,  0x0000 पूर्ण,     /* R72  - Write Sequencer 2 */
	अणु 73,  0x0000 पूर्ण,     /* R73  - Write Sequencer 3 */
	अणु 74,  0x0000 पूर्ण,     /* R74  - Write Sequencer 4 */
	अणु 75,  0x0000 पूर्ण,     /* R75  - Write Sequencer 5 */
	अणु 76,  0x1F25 पूर्ण,     /* R76  - Charge Pump 1 */
	अणु 81,  0x0000 पूर्ण,     /* R81  - Class W 0 */
	अणु 85,  0x054A पूर्ण,     /* R85  - DC Servo 1 */
	अणु 87,  0x0000 पूर्ण,     /* R87  - DC Servo 3 */
	अणु 96,  0x0100 पूर्ण,     /* R96  - Analogue HP 0 */
	अणु 98,  0x0000 पूर्ण,     /* R98  - EQ1 */
	अणु 99,  0x000C पूर्ण,     /* R99  - EQ2 */
	अणु 100, 0x000C पूर्ण,     /* R100 - EQ3 */
	अणु 101, 0x000C पूर्ण,     /* R101 - EQ4 */
	अणु 102, 0x000C पूर्ण,     /* R102 - EQ5 */
	अणु 103, 0x000C पूर्ण,     /* R103 - EQ6 */
	अणु 104, 0x0FCA पूर्ण,     /* R104 - EQ7 */
	अणु 105, 0x0400 पूर्ण,     /* R105 - EQ8 */
	अणु 106, 0x00D8 पूर्ण,     /* R106 - EQ9 */
	अणु 107, 0x1EB5 पूर्ण,     /* R107 - EQ10 */
	अणु 108, 0xF145 पूर्ण,     /* R108 - EQ11 */
	अणु 109, 0x0B75 पूर्ण,     /* R109 - EQ12 */
	अणु 110, 0x01C5 पूर्ण,     /* R110 - EQ13 */
	अणु 111, 0x1C58 पूर्ण,     /* R111 - EQ14 */
	अणु 112, 0xF373 पूर्ण,     /* R112 - EQ15 */
	अणु 113, 0x0A54 पूर्ण,     /* R113 - EQ16 */
	अणु 114, 0x0558 पूर्ण,     /* R114 - EQ17 */
	अणु 115, 0x168E पूर्ण,     /* R115 - EQ18 */
	अणु 116, 0xF829 पूर्ण,     /* R116 - EQ19 */
	अणु 117, 0x07AD पूर्ण,     /* R117 - EQ20 */
	अणु 118, 0x1103 पूर्ण,     /* R118 - EQ21 */
	अणु 119, 0x0564 पूर्ण,     /* R119 - EQ22 */
	अणु 120, 0x0559 पूर्ण,     /* R120 - EQ23 */
	अणु 121, 0x4000 पूर्ण,     /* R121 - EQ24 */
	अणु 122, 0x0000 पूर्ण,     /* R122 - Digital Pulls */
	अणु 123, 0x0F08 पूर्ण,     /* R123 - DRC Control 1 */
	अणु 124, 0x0000 पूर्ण,     /* R124 - DRC Control 2 */
	अणु 125, 0x0080 पूर्ण,     /* R125 - DRC Control 3 */
	अणु 126, 0x0000 पूर्ण,     /* R126 - DRC Control 4 */
पूर्ण;

अटल काष्ठा अणु
	पूर्णांक ratio;
	पूर्णांक clk_sys_rate;
पूर्ण clk_sys_rates[] = अणु
	अणु 64,   0 पूर्ण,
	अणु 128,  1 पूर्ण,
	अणु 192,  2 पूर्ण,
	अणु 256,  3 पूर्ण,
	अणु 384,  4 पूर्ण,
	अणु 512,  5 पूर्ण,
	अणु 768,  6 पूर्ण,
	अणु 1024, 7 पूर्ण,
	अणु 1408, 8 पूर्ण,
	अणु 1536, 9 पूर्ण,
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
	अणु 55,  5  पूर्ण,
	अणु 60,  6  पूर्ण,
	अणु 80,  7  पूर्ण,
	अणु 110, 8  पूर्ण,
	अणु 120, 9  पूर्ण,
	अणु 160, 10 पूर्ण,
	अणु 220, 11 पूर्ण,
	अणु 240, 12 पूर्ण,
	अणु 320, 13 पूर्ण,
	अणु 440, 14 पूर्ण,
	अणु 480, 15 पूर्ण,
पूर्ण;

काष्ठा wm8993_priv अणु
	काष्ठा wm_hubs_data hubs_data;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data supplies[WM8993_NUM_SUPPLIES];
	काष्ठा wm8993_platक्रमm_data pdata;
	काष्ठा completion fll_lock;
	पूर्णांक master;
	पूर्णांक sysclk_source;
	पूर्णांक tdm_slots;
	पूर्णांक tdm_width;
	अचिन्हित पूर्णांक mclk_rate;
	अचिन्हित पूर्णांक sysclk_rate;
	अचिन्हित पूर्णांक fs;
	अचिन्हित पूर्णांक bclk;
	अचिन्हित पूर्णांक fll_fref;
	अचिन्हित पूर्णांक fll_fout;
	पूर्णांक fll_src;
पूर्ण;

अटल bool wm8993_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8993_SOFTWARE_RESET:
	हाल WM8993_GPIO_CTRL_1:
	हाल WM8993_DC_SERVO_0:
	हाल WM8993_DC_SERVO_READBACK_0:
	हाल WM8993_DC_SERVO_READBACK_1:
	हाल WM8993_DC_SERVO_READBACK_2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool wm8993_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8993_SOFTWARE_RESET:
	हाल WM8993_POWER_MANAGEMENT_1:
	हाल WM8993_POWER_MANAGEMENT_2:
	हाल WM8993_POWER_MANAGEMENT_3:
	हाल WM8993_AUDIO_INTERFACE_1:
	हाल WM8993_AUDIO_INTERFACE_2:
	हाल WM8993_CLOCKING_1:
	हाल WM8993_CLOCKING_2:
	हाल WM8993_AUDIO_INTERFACE_3:
	हाल WM8993_AUDIO_INTERFACE_4:
	हाल WM8993_DAC_CTRL:
	हाल WM8993_LEFT_DAC_DIGITAL_VOLUME:
	हाल WM8993_RIGHT_DAC_DIGITAL_VOLUME:
	हाल WM8993_DIGITAL_SIDE_TONE:
	हाल WM8993_ADC_CTRL:
	हाल WM8993_LEFT_ADC_DIGITAL_VOLUME:
	हाल WM8993_RIGHT_ADC_DIGITAL_VOLUME:
	हाल WM8993_GPIO_CTRL_1:
	हाल WM8993_GPIO1:
	हाल WM8993_IRQ_DEBOUNCE:
	हाल WM8993_GPIOCTRL_2:
	हाल WM8993_GPIO_POL:
	हाल WM8993_LEFT_LINE_INPUT_1_2_VOLUME:
	हाल WM8993_LEFT_LINE_INPUT_3_4_VOLUME:
	हाल WM8993_RIGHT_LINE_INPUT_1_2_VOLUME:
	हाल WM8993_RIGHT_LINE_INPUT_3_4_VOLUME:
	हाल WM8993_LEFT_OUTPUT_VOLUME:
	हाल WM8993_RIGHT_OUTPUT_VOLUME:
	हाल WM8993_LINE_OUTPUTS_VOLUME:
	हाल WM8993_HPOUT2_VOLUME:
	हाल WM8993_LEFT_OPGA_VOLUME:
	हाल WM8993_RIGHT_OPGA_VOLUME:
	हाल WM8993_SPKMIXL_ATTENUATION:
	हाल WM8993_SPKMIXR_ATTENUATION:
	हाल WM8993_SPKOUT_MIXERS:
	हाल WM8993_SPKOUT_BOOST:
	हाल WM8993_SPEAKER_VOLUME_LEFT:
	हाल WM8993_SPEAKER_VOLUME_RIGHT:
	हाल WM8993_INPUT_MIXER2:
	हाल WM8993_INPUT_MIXER3:
	हाल WM8993_INPUT_MIXER4:
	हाल WM8993_INPUT_MIXER5:
	हाल WM8993_INPUT_MIXER6:
	हाल WM8993_OUTPUT_MIXER1:
	हाल WM8993_OUTPUT_MIXER2:
	हाल WM8993_OUTPUT_MIXER3:
	हाल WM8993_OUTPUT_MIXER4:
	हाल WM8993_OUTPUT_MIXER5:
	हाल WM8993_OUTPUT_MIXER6:
	हाल WM8993_HPOUT2_MIXER:
	हाल WM8993_LINE_MIXER1:
	हाल WM8993_LINE_MIXER2:
	हाल WM8993_SPEAKER_MIXER:
	हाल WM8993_ADDITIONAL_CONTROL:
	हाल WM8993_ANTIPOP1:
	हाल WM8993_ANTIPOP2:
	हाल WM8993_MICBIAS:
	हाल WM8993_FLL_CONTROL_1:
	हाल WM8993_FLL_CONTROL_2:
	हाल WM8993_FLL_CONTROL_3:
	हाल WM8993_FLL_CONTROL_4:
	हाल WM8993_FLL_CONTROL_5:
	हाल WM8993_CLOCKING_3:
	हाल WM8993_CLOCKING_4:
	हाल WM8993_MW_SLAVE_CONTROL:
	हाल WM8993_BUS_CONTROL_1:
	हाल WM8993_WRITE_SEQUENCER_0:
	हाल WM8993_WRITE_SEQUENCER_1:
	हाल WM8993_WRITE_SEQUENCER_2:
	हाल WM8993_WRITE_SEQUENCER_3:
	हाल WM8993_WRITE_SEQUENCER_4:
	हाल WM8993_WRITE_SEQUENCER_5:
	हाल WM8993_CHARGE_PUMP_1:
	हाल WM8993_CLASS_W_0:
	हाल WM8993_DC_SERVO_0:
	हाल WM8993_DC_SERVO_1:
	हाल WM8993_DC_SERVO_3:
	हाल WM8993_DC_SERVO_READBACK_0:
	हाल WM8993_DC_SERVO_READBACK_1:
	हाल WM8993_DC_SERVO_READBACK_2:
	हाल WM8993_ANALOGUE_HP_0:
	हाल WM8993_EQ1:
	हाल WM8993_EQ2:
	हाल WM8993_EQ3:
	हाल WM8993_EQ4:
	हाल WM8993_EQ5:
	हाल WM8993_EQ6:
	हाल WM8993_EQ7:
	हाल WM8993_EQ8:
	हाल WM8993_EQ9:
	हाल WM8993_EQ10:
	हाल WM8993_EQ11:
	हाल WM8993_EQ12:
	हाल WM8993_EQ13:
	हाल WM8993_EQ14:
	हाल WM8993_EQ15:
	हाल WM8993_EQ16:
	हाल WM8993_EQ17:
	हाल WM8993_EQ18:
	हाल WM8993_EQ19:
	हाल WM8993_EQ20:
	हाल WM8993_EQ21:
	हाल WM8993_EQ22:
	हाल WM8993_EQ23:
	हाल WM8993_EQ24:
	हाल WM8993_DIGITAL_PULLS:
	हाल WM8993_DRC_CONTROL_1:
	हाल WM8993_DRC_CONTROL_2:
	हाल WM8993_DRC_CONTROL_3:
	हाल WM8993_DRC_CONTROL_4:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
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
	भाग = 0;
	target = Fout * 2;
	जबतक (target < 90000000) अणु
		भाग++;
		target *= 2;
		अगर (भाग > 7) अणु
			pr_err("Unable to find FLL_OUTDIV for Fout=%uHz\n",
			       Fout);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	fll_भाग->fll_outभाग = भाग;

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

अटल पूर्णांक _wm8993_set_fll(काष्ठा snd_soc_component *component, पूर्णांक fll_id, पूर्णांक source,
			  अचिन्हित पूर्णांक Fref, अचिन्हित पूर्णांक Fout)
अणु
	काष्ठा wm8993_priv *wm8993 = snd_soc_component_get_drvdata(component);
	काष्ठा i2c_client *i2c = to_i2c_client(component->dev);
	u16 reg1, reg4, reg5;
	काष्ठा _fll_भाग fll_भाग;
	अचिन्हित पूर्णांक समयout;
	पूर्णांक ret;

	/* Any change? */
	अगर (Fref == wm8993->fll_fref && Fout == wm8993->fll_fout)
		वापस 0;

	/* Disable the FLL */
	अगर (Fout == 0) अणु
		dev_dbg(component->dev, "FLL disabled\n");
		wm8993->fll_fref = 0;
		wm8993->fll_fout = 0;

		reg1 = snd_soc_component_पढ़ो(component, WM8993_FLL_CONTROL_1);
		reg1 &= ~WM8993_FLL_ENA;
		snd_soc_component_ग_लिखो(component, WM8993_FLL_CONTROL_1, reg1);

		वापस 0;
	पूर्ण

	ret = fll_factors(&fll_भाग, Fref, Fout);
	अगर (ret != 0)
		वापस ret;

	reg5 = snd_soc_component_पढ़ो(component, WM8993_FLL_CONTROL_5);
	reg5 &= ~WM8993_FLL_CLK_SRC_MASK;

	चयन (fll_id) अणु
	हाल WM8993_FLL_MCLK:
		अवरोध;

	हाल WM8993_FLL_LRCLK:
		reg5 |= 1;
		अवरोध;

	हाल WM8993_FLL_BCLK:
		reg5 |= 2;
		अवरोध;

	शेष:
		dev_err(component->dev, "Unknown FLL ID %d\n", fll_id);
		वापस -EINVAL;
	पूर्ण

	/* Any FLL configuration change requires that the FLL be
	 * disabled first. */
	reg1 = snd_soc_component_पढ़ो(component, WM8993_FLL_CONTROL_1);
	reg1 &= ~WM8993_FLL_ENA;
	snd_soc_component_ग_लिखो(component, WM8993_FLL_CONTROL_1, reg1);

	/* Apply the configuration */
	अगर (fll_भाग.k)
		reg1 |= WM8993_FLL_FRAC_MASK;
	अन्यथा
		reg1 &= ~WM8993_FLL_FRAC_MASK;
	snd_soc_component_ग_लिखो(component, WM8993_FLL_CONTROL_1, reg1);

	snd_soc_component_ग_लिखो(component, WM8993_FLL_CONTROL_2,
		      (fll_भाग.fll_outभाग << WM8993_FLL_OUTDIV_SHIFT) |
		      (fll_भाग.fll_fratio << WM8993_FLL_FRATIO_SHIFT));
	snd_soc_component_ग_लिखो(component, WM8993_FLL_CONTROL_3, fll_भाग.k);

	reg4 = snd_soc_component_पढ़ो(component, WM8993_FLL_CONTROL_4);
	reg4 &= ~WM8993_FLL_N_MASK;
	reg4 |= fll_भाग.n << WM8993_FLL_N_SHIFT;
	snd_soc_component_ग_लिखो(component, WM8993_FLL_CONTROL_4, reg4);

	reg5 &= ~WM8993_FLL_CLK_REF_DIV_MASK;
	reg5 |= fll_भाग.fll_clk_ref_भाग << WM8993_FLL_CLK_REF_DIV_SHIFT;
	snd_soc_component_ग_लिखो(component, WM8993_FLL_CONTROL_5, reg5);

	/* If we've got an पूर्णांकerrupt wired up make sure we get it */
	अगर (i2c->irq)
		समयout = msecs_to_jअगरfies(20);
	अन्यथा अगर (Fref < 1000000)
		समयout = msecs_to_jअगरfies(3);
	अन्यथा
		समयout = msecs_to_jअगरfies(1);

	try_रुको_क्रम_completion(&wm8993->fll_lock);

	/* Enable the FLL */
	snd_soc_component_ग_लिखो(component, WM8993_FLL_CONTROL_1, reg1 | WM8993_FLL_ENA);

	समयout = रुको_क्रम_completion_समयout(&wm8993->fll_lock, समयout);
	अगर (i2c->irq && !समयout)
		dev_warn(component->dev, "Timed out waiting for FLL\n");

	dev_dbg(component->dev, "FLL enabled at %dHz->%dHz\n", Fref, Fout);

	wm8993->fll_fref = Fref;
	wm8993->fll_fout = Fout;
	wm8993->fll_src = source;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8993_set_fll(काष्ठा snd_soc_dai *dai, पूर्णांक fll_id, पूर्णांक source,
			  अचिन्हित पूर्णांक Fref, अचिन्हित पूर्णांक Fout)
अणु
	वापस _wm8993_set_fll(dai->component, fll_id, source, Fref, Fout);
पूर्ण

अटल पूर्णांक configure_घड़ी(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8993_priv *wm8993 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg;

	/* This should be करोne on init() क्रम bypass paths */
	चयन (wm8993->sysclk_source) अणु
	हाल WM8993_SYSCLK_MCLK:
		dev_dbg(component->dev, "Using %dHz MCLK\n", wm8993->mclk_rate);

		reg = snd_soc_component_पढ़ो(component, WM8993_CLOCKING_2);
		reg &= ~(WM8993_MCLK_DIV | WM8993_SYSCLK_SRC);
		अगर (wm8993->mclk_rate > 13500000) अणु
			reg |= WM8993_MCLK_DIV;
			wm8993->sysclk_rate = wm8993->mclk_rate / 2;
		पूर्ण अन्यथा अणु
			reg &= ~WM8993_MCLK_DIV;
			wm8993->sysclk_rate = wm8993->mclk_rate;
		पूर्ण
		snd_soc_component_ग_लिखो(component, WM8993_CLOCKING_2, reg);
		अवरोध;

	हाल WM8993_SYSCLK_FLL:
		dev_dbg(component->dev, "Using %dHz FLL clock\n",
			wm8993->fll_fout);

		reg = snd_soc_component_पढ़ो(component, WM8993_CLOCKING_2);
		reg |= WM8993_SYSCLK_SRC;
		अगर (wm8993->fll_fout > 13500000) अणु
			reg |= WM8993_MCLK_DIV;
			wm8993->sysclk_rate = wm8993->fll_fout / 2;
		पूर्ण अन्यथा अणु
			reg &= ~WM8993_MCLK_DIV;
			wm8993->sysclk_rate = wm8993->fll_fout;
		पूर्ण
		snd_soc_component_ग_लिखो(component, WM8993_CLOCKING_2, reg);
		अवरोध;

	शेष:
		dev_err(component->dev, "System clock not configured\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(component->dev, "CLK_SYS is %dHz\n", wm8993->sysclk_rate);

	वापस 0;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(sidetone_tlv, -3600, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(drc_comp_threash, -4500, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(drc_comp_amp, -2250, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(drc_min_tlv, -1800, 600, 0);
अटल स्थिर DECLARE_TLV_DB_RANGE(drc_max_tlv,
	0, 2, TLV_DB_SCALE_ITEM(1200, 600, 0),
	3, 3, TLV_DB_SCALE_ITEM(3600, 0, 0)
);
अटल स्थिर DECLARE_TLV_DB_SCALE(drc_qr_tlv, 1200, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(drc_startup_tlv, -1800, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(eq_tlv, -1200, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(digital_tlv, -7200, 75, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(dac_boost_tlv, 0, 600, 0);

अटल स्थिर अक्षर *dac_deemph_text[] = अणु
	"None",
	"32kHz",
	"44.1kHz",
	"48kHz",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(dac_deemph,
			    WM8993_DAC_CTRL, 4, dac_deemph_text);

अटल स्थिर अक्षर *adc_hpf_text[] = अणु
	"Hi-Fi",
	"Voice 1",
	"Voice 2",
	"Voice 3",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adc_hpf,
			    WM8993_ADC_CTRL, 5, adc_hpf_text);

अटल स्थिर अक्षर *drc_path_text[] = अणु
	"ADC",
	"DAC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(drc_path,
			    WM8993_DRC_CONTROL_1, 14, drc_path_text);

अटल स्थिर अक्षर *drc_r0_text[] = अणु
	"1",
	"1/2",
	"1/4",
	"1/8",
	"1/16",
	"0",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(drc_r0,
			    WM8993_DRC_CONTROL_3, 8, drc_r0_text);

अटल स्थिर अक्षर *drc_r1_text[] = अणु
	"1",
	"1/2",
	"1/4",
	"1/8",
	"0",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(drc_r1,
			    WM8993_DRC_CONTROL_4, 13, drc_r1_text);

अटल स्थिर अक्षर *drc_attack_text[] = अणु
	"Reserved",
	"181us",
	"363us",
	"726us",
	"1.45ms",
	"2.9ms",
	"5.8ms",
	"11.6ms",
	"23.2ms",
	"46.4ms",
	"92.8ms",
	"185.6ms",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(drc_attack,
			    WM8993_DRC_CONTROL_2, 12, drc_attack_text);

अटल स्थिर अक्षर *drc_decay_text[] = अणु
	"186ms",
	"372ms",
	"743ms",
	"1.49s",
	"2.97ms",
	"5.94ms",
	"11.89ms",
	"23.78ms",
	"47.56ms",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(drc_decay,
			    WM8993_DRC_CONTROL_2, 8, drc_decay_text);

अटल स्थिर अक्षर *drc_ff_text[] = अणु
	"5 samples",
	"9 samples",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(drc_ff,
			    WM8993_DRC_CONTROL_3, 7, drc_ff_text);

अटल स्थिर अक्षर *drc_qr_rate_text[] = अणु
	"0.725ms",
	"1.45ms",
	"5.8ms",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(drc_qr_rate,
			    WM8993_DRC_CONTROL_3, 0, drc_qr_rate_text);

अटल स्थिर अक्षर *drc_smooth_text[] = अणु
	"Low",
	"Medium",
	"High",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(drc_smooth,
			    WM8993_DRC_CONTROL_1, 4, drc_smooth_text);

अटल स्थिर काष्ठा snd_kcontrol_new wm8993_snd_controls[] = अणु
SOC_DOUBLE_TLV("Digital Sidetone Volume", WM8993_DIGITAL_SIDE_TONE,
	       5, 9, 12, 0, sidetone_tlv),

SOC_SINGLE("DRC Switch", WM8993_DRC_CONTROL_1, 15, 1, 0),
SOC_ENUM("DRC Path", drc_path),
SOC_SINGLE_TLV("DRC Compressor Threshold Volume", WM8993_DRC_CONTROL_2,
	       2, 60, 1, drc_comp_threash),
SOC_SINGLE_TLV("DRC Compressor Amplitude Volume", WM8993_DRC_CONTROL_3,
	       11, 30, 1, drc_comp_amp),
SOC_ENUM("DRC R0", drc_r0),
SOC_ENUM("DRC R1", drc_r1),
SOC_SINGLE_TLV("DRC Minimum Volume", WM8993_DRC_CONTROL_1, 2, 3, 1,
	       drc_min_tlv),
SOC_SINGLE_TLV("DRC Maximum Volume", WM8993_DRC_CONTROL_1, 0, 3, 0,
	       drc_max_tlv),
SOC_ENUM("DRC Attack Rate", drc_attack),
SOC_ENUM("DRC Decay Rate", drc_decay),
SOC_ENUM("DRC FF Delay", drc_ff),
SOC_SINGLE("DRC Anti-clip Switch", WM8993_DRC_CONTROL_1, 9, 1, 0),
SOC_SINGLE("DRC Quick Release Switch", WM8993_DRC_CONTROL_1, 10, 1, 0),
SOC_SINGLE_TLV("DRC Quick Release Volume", WM8993_DRC_CONTROL_3, 2, 3, 0,
	       drc_qr_tlv),
SOC_ENUM("DRC Quick Release Rate", drc_qr_rate),
SOC_SINGLE("DRC Smoothing Switch", WM8993_DRC_CONTROL_1, 11, 1, 0),
SOC_SINGLE("DRC Smoothing Hysteresis Switch", WM8993_DRC_CONTROL_1, 8, 1, 0),
SOC_ENUM("DRC Smoothing Hysteresis Threshold", drc_smooth),
SOC_SINGLE_TLV("DRC Startup Volume", WM8993_DRC_CONTROL_4, 8, 18, 0,
	       drc_startup_tlv),

SOC_SINGLE("EQ Switch", WM8993_EQ1, 0, 1, 0),

SOC_DOUBLE_R_TLV("Capture Volume", WM8993_LEFT_ADC_DIGITAL_VOLUME,
		 WM8993_RIGHT_ADC_DIGITAL_VOLUME, 1, 96, 0, digital_tlv),
SOC_SINGLE("ADC High Pass Filter Switch", WM8993_ADC_CTRL, 8, 1, 0),
SOC_ENUM("ADC High Pass Filter Mode", adc_hpf),

SOC_DOUBLE_R_TLV("Playback Volume", WM8993_LEFT_DAC_DIGITAL_VOLUME,
		 WM8993_RIGHT_DAC_DIGITAL_VOLUME, 1, 96, 0, digital_tlv),
SOC_SINGLE_TLV("Playback Boost Volume", WM8993_AUDIO_INTERFACE_2, 10, 3, 0,
	       dac_boost_tlv),
SOC_ENUM("DAC Deemphasis", dac_deemph),

SOC_SINGLE_TLV("SPKL DAC Volume", WM8993_SPKMIXL_ATTENUATION,
	       2, 1, 1, wm_hubs_spkmix_tlv),

SOC_SINGLE_TLV("SPKR DAC Volume", WM8993_SPKMIXR_ATTENUATION,
	       2, 1, 1, wm_hubs_spkmix_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8993_eq_controls[] = अणु
SOC_SINGLE_TLV("EQ1 Volume", WM8993_EQ2, 0, 24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ2 Volume", WM8993_EQ3, 0, 24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ3 Volume", WM8993_EQ4, 0, 24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ4 Volume", WM8993_EQ5, 0, 24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ5 Volume", WM8993_EQ6, 0, 24, 0, eq_tlv),
पूर्ण;

अटल पूर्णांक clk_sys_event(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		वापस configure_घड़ी(component);

	हाल SND_SOC_DAPM_POST_PMD:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new left_speaker_mixer[] = अणु
SOC_DAPM_SINGLE("Input Switch", WM8993_SPEAKER_MIXER, 7, 1, 0),
SOC_DAPM_SINGLE("IN1LP Switch", WM8993_SPEAKER_MIXER, 5, 1, 0),
SOC_DAPM_SINGLE("Output Switch", WM8993_SPEAKER_MIXER, 3, 1, 0),
SOC_DAPM_SINGLE("DAC Switch", WM8993_SPEAKER_MIXER, 6, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new right_speaker_mixer[] = अणु
SOC_DAPM_SINGLE("Input Switch", WM8993_SPEAKER_MIXER, 6, 1, 0),
SOC_DAPM_SINGLE("IN1RP Switch", WM8993_SPEAKER_MIXER, 4, 1, 0),
SOC_DAPM_SINGLE("Output Switch", WM8993_SPEAKER_MIXER, 2, 1, 0),
SOC_DAPM_SINGLE("DAC Switch", WM8993_SPEAKER_MIXER, 0, 1, 0),
पूर्ण;

अटल स्थिर अक्षर *aअगर_text[] = अणु
	"Left", "Right"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(aअगरoutl_क्रमागत,
			    WM8993_AUDIO_INTERFACE_1, 15, aअगर_text);

अटल स्थिर काष्ठा snd_kcontrol_new aअगरoutl_mux =
	SOC_DAPM_ENUM("AIFOUTL Mux", aअगरoutl_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(aअगरoutr_क्रमागत,
			    WM8993_AUDIO_INTERFACE_1, 14, aअगर_text);

अटल स्थिर काष्ठा snd_kcontrol_new aअगरoutr_mux =
	SOC_DAPM_ENUM("AIFOUTR Mux", aअगरoutr_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(aअगरinl_क्रमागत,
			    WM8993_AUDIO_INTERFACE_2, 15, aअगर_text);

अटल स्थिर काष्ठा snd_kcontrol_new aअगरinl_mux =
	SOC_DAPM_ENUM("AIFINL Mux", aअगरinl_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(aअगरinr_क्रमागत,
			    WM8993_AUDIO_INTERFACE_2, 14, aअगर_text);

अटल स्थिर काष्ठा snd_kcontrol_new aअगरinr_mux =
	SOC_DAPM_ENUM("AIFINR Mux", aअगरinr_क्रमागत);

अटल स्थिर अक्षर *sidetone_text[] = अणु
	"None", "Left", "Right"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(sidetonel_क्रमागत,
			    WM8993_DIGITAL_SIDE_TONE, 2, sidetone_text);

अटल स्थिर काष्ठा snd_kcontrol_new sidetonel_mux =
	SOC_DAPM_ENUM("Left Sidetone", sidetonel_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(sidetoner_क्रमागत,
			    WM8993_DIGITAL_SIDE_TONE, 0, sidetone_text);

अटल स्थिर काष्ठा snd_kcontrol_new sidetoner_mux =
	SOC_DAPM_ENUM("Right Sidetone", sidetoner_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8993_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_SUPPLY("CLK_SYS", WM8993_BUS_CONTROL_1, 1, 0, clk_sys_event,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("TOCLK", WM8993_CLOCKING_1, 14, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("CLK_DSP", WM8993_CLOCKING_3, 0, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("VMID", SND_SOC_NOPM, 0, 0, शून्य, 0),

SND_SOC_DAPM_ADC("ADCL", शून्य, WM8993_POWER_MANAGEMENT_2, 1, 0),
SND_SOC_DAPM_ADC("ADCR", शून्य, WM8993_POWER_MANAGEMENT_2, 0, 0),

SND_SOC_DAPM_MUX("AIFOUTL Mux", SND_SOC_NOPM, 0, 0, &aअगरoutl_mux),
SND_SOC_DAPM_MUX("AIFOUTR Mux", SND_SOC_NOPM, 0, 0, &aअगरoutr_mux),

SND_SOC_DAPM_AIF_OUT("AIFOUTL", "Capture", 0, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_AIF_OUT("AIFOUTR", "Capture", 1, SND_SOC_NOPM, 0, 0),

SND_SOC_DAPM_AIF_IN("AIFINL", "Playback", 0, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_AIF_IN("AIFINR", "Playback", 1, SND_SOC_NOPM, 0, 0),

SND_SOC_DAPM_MUX("DACL Mux", SND_SOC_NOPM, 0, 0, &aअगरinl_mux),
SND_SOC_DAPM_MUX("DACR Mux", SND_SOC_NOPM, 0, 0, &aअगरinr_mux),

SND_SOC_DAPM_MUX("DACL Sidetone", SND_SOC_NOPM, 0, 0, &sidetonel_mux),
SND_SOC_DAPM_MUX("DACR Sidetone", SND_SOC_NOPM, 0, 0, &sidetoner_mux),

SND_SOC_DAPM_DAC("DACL", शून्य, WM8993_POWER_MANAGEMENT_3, 1, 0),
SND_SOC_DAPM_DAC("DACR", शून्य, WM8993_POWER_MANAGEMENT_3, 0, 0),

SND_SOC_DAPM_MUX("Left Headphone Mux", SND_SOC_NOPM, 0, 0, &wm_hubs_hpl_mux),
SND_SOC_DAPM_MUX("Right Headphone Mux", SND_SOC_NOPM, 0, 0, &wm_hubs_hpr_mux),

SND_SOC_DAPM_MIXER("SPKL", WM8993_POWER_MANAGEMENT_3, 8, 0,
		   left_speaker_mixer, ARRAY_SIZE(left_speaker_mixer)),
SND_SOC_DAPM_MIXER("SPKR", WM8993_POWER_MANAGEMENT_3, 9, 0,
		   right_speaker_mixer, ARRAY_SIZE(right_speaker_mixer)),
SND_SOC_DAPM_PGA("Direct Voice", SND_SOC_NOPM, 0, 0, शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route routes[] = अणु
	अणु "MICBIAS1", शून्य, "VMID" पूर्ण,
	अणु "MICBIAS2", शून्य, "VMID" पूर्ण,

	अणु "ADCL", शून्य, "CLK_SYS" पूर्ण,
	अणु "ADCL", शून्य, "CLK_DSP" पूर्ण,
	अणु "ADCR", शून्य, "CLK_SYS" पूर्ण,
	अणु "ADCR", शून्य, "CLK_DSP" पूर्ण,

	अणु "AIFOUTL Mux", "Left", "ADCL" पूर्ण,
	अणु "AIFOUTL Mux", "Right", "ADCR" पूर्ण,
	अणु "AIFOUTR Mux", "Left", "ADCL" पूर्ण,
	अणु "AIFOUTR Mux", "Right", "ADCR" पूर्ण,

	अणु "AIFOUTL", शून्य, "AIFOUTL Mux" पूर्ण,
	अणु "AIFOUTR", शून्य, "AIFOUTR Mux" पूर्ण,

	अणु "DACL Mux", "Left", "AIFINL" पूर्ण,
	अणु "DACL Mux", "Right", "AIFINR" पूर्ण,
	अणु "DACR Mux", "Left", "AIFINL" पूर्ण,
	अणु "DACR Mux", "Right", "AIFINR" पूर्ण,

	अणु "DACL Sidetone", "Left", "ADCL" पूर्ण,
	अणु "DACL Sidetone", "Right", "ADCR" पूर्ण,
	अणु "DACR Sidetone", "Left", "ADCL" पूर्ण,
	अणु "DACR Sidetone", "Right", "ADCR" पूर्ण,

	अणु "DACL", शून्य, "CLK_SYS" पूर्ण,
	अणु "DACL", शून्य, "CLK_DSP" पूर्ण,
	अणु "DACL", शून्य, "DACL Mux" पूर्ण,
	अणु "DACL", शून्य, "DACL Sidetone" पूर्ण,
	अणु "DACR", शून्य, "CLK_SYS" पूर्ण,
	अणु "DACR", शून्य, "CLK_DSP" पूर्ण,
	अणु "DACR", शून्य, "DACR Mux" पूर्ण,
	अणु "DACR", शून्य, "DACR Sidetone" पूर्ण,

	अणु "Left Output Mixer", "DAC Switch", "DACL" पूर्ण,

	अणु "Right Output Mixer", "DAC Switch", "DACR" पूर्ण,

	अणु "Left Output PGA", शून्य, "CLK_SYS" पूर्ण,

	अणु "Right Output PGA", शून्य, "CLK_SYS" पूर्ण,

	अणु "SPKL", "DAC Switch", "DACL" पूर्ण,
	अणु "SPKL", शून्य, "CLK_SYS" पूर्ण,

	अणु "SPKR", "DAC Switch", "DACR" पूर्ण,
	अणु "SPKR", शून्य, "CLK_SYS" पूर्ण,

	अणु "Left Headphone Mux", "DAC", "DACL" पूर्ण,
	अणु "Right Headphone Mux", "DAC", "DACR" पूर्ण,
पूर्ण;

अटल पूर्णांक wm8993_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8993_priv *wm8993 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	wm_hubs_set_bias_level(component, level);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
		/* VMID=2*40k */
		snd_soc_component_update_bits(component, WM8993_POWER_MANAGEMENT_1,
				    WM8993_VMID_SEL_MASK, 0x2);
		snd_soc_component_update_bits(component, WM8993_POWER_MANAGEMENT_2,
				    WM8993_TSHUT_ENA, WM8993_TSHUT_ENA);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			ret = regulator_bulk_enable(ARRAY_SIZE(wm8993->supplies),
						    wm8993->supplies);
			अगर (ret != 0)
				वापस ret;

			regcache_cache_only(wm8993->regmap, false);
			regcache_sync(wm8993->regmap);

			wm_hubs_vmid_ena(component);

			/* Bring up VMID with fast soft start */
			snd_soc_component_update_bits(component, WM8993_ANTIPOP2,
					    WM8993_STARTUP_BIAS_ENA |
					    WM8993_VMID_BUF_ENA |
					    WM8993_VMID_RAMP_MASK |
					    WM8993_BIAS_SRC,
					    WM8993_STARTUP_BIAS_ENA |
					    WM8993_VMID_BUF_ENA |
					    WM8993_VMID_RAMP_MASK |
					    WM8993_BIAS_SRC);

			/* If either line output is single ended we
			 * need the VMID buffer */
			अगर (!wm8993->pdata.lineout1_dअगरf ||
			    !wm8993->pdata.lineout2_dअगरf)
				snd_soc_component_update_bits(component, WM8993_ANTIPOP1,
						 WM8993_LINEOUT_VMID_BUF_ENA,
						 WM8993_LINEOUT_VMID_BUF_ENA);

			/* VMID=2*40k */
			snd_soc_component_update_bits(component, WM8993_POWER_MANAGEMENT_1,
					    WM8993_VMID_SEL_MASK |
					    WM8993_BIAS_ENA,
					    WM8993_BIAS_ENA | 0x2);
			msleep(32);

			/* Switch to normal bias */
			snd_soc_component_update_bits(component, WM8993_ANTIPOP2,
					    WM8993_BIAS_SRC |
					    WM8993_STARTUP_BIAS_ENA, 0);
		पूर्ण

		/* VMID=2*240k */
		snd_soc_component_update_bits(component, WM8993_POWER_MANAGEMENT_1,
				    WM8993_VMID_SEL_MASK, 0x4);

		snd_soc_component_update_bits(component, WM8993_POWER_MANAGEMENT_2,
				    WM8993_TSHUT_ENA, 0);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, WM8993_ANTIPOP1,
				    WM8993_LINEOUT_VMID_BUF_ENA, 0);

		snd_soc_component_update_bits(component, WM8993_POWER_MANAGEMENT_1,
				    WM8993_VMID_SEL_MASK | WM8993_BIAS_ENA,
				    0);

		snd_soc_component_update_bits(component, WM8993_ANTIPOP2,
				    WM8993_STARTUP_BIAS_ENA |
				    WM8993_VMID_BUF_ENA |
				    WM8993_VMID_RAMP_MASK |
				    WM8993_BIAS_SRC, 0);

		regcache_cache_only(wm8993->regmap, true);
		regcache_mark_dirty(wm8993->regmap);

		regulator_bulk_disable(ARRAY_SIZE(wm8993->supplies),
				       wm8993->supplies);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8993_set_sysclk(काष्ठा snd_soc_dai *codec_dai,
			     पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8993_priv *wm8993 = snd_soc_component_get_drvdata(component);

	चयन (clk_id) अणु
	हाल WM8993_SYSCLK_MCLK:
		wm8993->mclk_rate = freq;
		fallthrough;
	हाल WM8993_SYSCLK_FLL:
		wm8993->sysclk_source = clk_id;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8993_set_dai_fmt(काष्ठा snd_soc_dai *dai,
			      अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8993_priv *wm8993 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक aअगर1 = snd_soc_component_पढ़ो(component, WM8993_AUDIO_INTERFACE_1);
	अचिन्हित पूर्णांक aअगर4 = snd_soc_component_पढ़ो(component, WM8993_AUDIO_INTERFACE_4);

	aअगर1 &= ~(WM8993_BCLK_सूची | WM8993_AIF_BCLK_INV |
		  WM8993_AIF_LRCLK_INV | WM8993_AIF_FMT_MASK);
	aअगर4 &= ~WM8993_LRCLK_सूची;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		wm8993->master = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		aअगर4 |= WM8993_LRCLK_सूची;
		wm8993->master = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		aअगर1 |= WM8993_BCLK_सूची;
		wm8993->master = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		aअगर1 |= WM8993_BCLK_सूची;
		aअगर4 |= WM8993_LRCLK_सूची;
		wm8993->master = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_B:
		aअगर1 |= WM8993_AIF_LRCLK_INV;
		fallthrough;
	हाल SND_SOC_DAIFMT_DSP_A:
		aअगर1 |= 0x18;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		aअगर1 |= 0x10;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		aअगर1 |= 0x8;
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
			aअगर1 |= WM8993_AIF_BCLK_INV;
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
			aअगर1 |= WM8993_AIF_BCLK_INV | WM8993_AIF_LRCLK_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			aअगर1 |= WM8993_AIF_BCLK_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_NB_IF:
			aअगर1 |= WM8993_AIF_LRCLK_INV;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8993_AUDIO_INTERFACE_1, aअगर1);
	snd_soc_component_ग_लिखो(component, WM8993_AUDIO_INTERFACE_4, aअगर4);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8993_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8993_priv *wm8993 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret, i, best, best_val, cur_val;
	अचिन्हित पूर्णांक घड़ीing1, घड़ीing3, aअगर1, aअगर4;

	घड़ीing1 = snd_soc_component_पढ़ो(component, WM8993_CLOCKING_1);
	घड़ीing1 &= ~WM8993_BCLK_DIV_MASK;

	घड़ीing3 = snd_soc_component_पढ़ो(component, WM8993_CLOCKING_3);
	घड़ीing3 &= ~(WM8993_CLK_SYS_RATE_MASK | WM8993_SAMPLE_RATE_MASK);

	aअगर1 = snd_soc_component_पढ़ो(component, WM8993_AUDIO_INTERFACE_1);
	aअगर1 &= ~WM8993_AIF_WL_MASK;

	aअगर4 = snd_soc_component_पढ़ो(component, WM8993_AUDIO_INTERFACE_4);
	aअगर4 &= ~WM8993_LRCLK_RATE_MASK;

	/* What BCLK करो we need? */
	wm8993->fs = params_rate(params);
	wm8993->bclk = 2 * wm8993->fs;
	अगर (wm8993->tdm_slots) अणु
		dev_dbg(component->dev, "Configuring for %d %d bit TDM slots\n",
			wm8993->tdm_slots, wm8993->tdm_width);
		wm8993->bclk *= wm8993->tdm_width * wm8993->tdm_slots;
	पूर्ण अन्यथा अणु
		चयन (params_width(params)) अणु
		हाल 16:
			wm8993->bclk *= 16;
			अवरोध;
		हाल 20:
			wm8993->bclk *= 20;
			aअगर1 |= 0x8;
			अवरोध;
		हाल 24:
			wm8993->bclk *= 24;
			aअगर1 |= 0x10;
			अवरोध;
		हाल 32:
			wm8993->bclk *= 32;
			aअगर1 |= 0x18;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	dev_dbg(component->dev, "Target BCLK is %dHz\n", wm8993->bclk);

	ret = configure_घड़ी(component);
	अगर (ret != 0)
		वापस ret;

	/* Select nearest CLK_SYS_RATE */
	best = 0;
	best_val = असल((wm8993->sysclk_rate / clk_sys_rates[0].ratio)
		       - wm8993->fs);
	क्रम (i = 1; i < ARRAY_SIZE(clk_sys_rates); i++) अणु
		cur_val = असल((wm8993->sysclk_rate /
			       clk_sys_rates[i].ratio) - wm8993->fs);
		अगर (cur_val < best_val) अणु
			best = i;
			best_val = cur_val;
		पूर्ण
	पूर्ण
	dev_dbg(component->dev, "Selected CLK_SYS_RATIO of %d\n",
		clk_sys_rates[best].ratio);
	घड़ीing3 |= (clk_sys_rates[best].clk_sys_rate
		      << WM8993_CLK_SYS_RATE_SHIFT);

	/* SAMPLE_RATE */
	best = 0;
	best_val = असल(wm8993->fs - sample_rates[0].rate);
	क्रम (i = 1; i < ARRAY_SIZE(sample_rates); i++) अणु
		/* Closest match */
		cur_val = असल(wm8993->fs - sample_rates[i].rate);
		अगर (cur_val < best_val) अणु
			best = i;
			best_val = cur_val;
		पूर्ण
	पूर्ण
	dev_dbg(component->dev, "Selected SAMPLE_RATE of %dHz\n",
		sample_rates[best].rate);
	घड़ीing3 |= (sample_rates[best].sample_rate
		      << WM8993_SAMPLE_RATE_SHIFT);

	/* BCLK_DIV */
	best = 0;
	best_val = पूर्णांक_उच्च;
	क्रम (i = 0; i < ARRAY_SIZE(bclk_भागs); i++) अणु
		cur_val = ((wm8993->sysclk_rate * 10) / bclk_भागs[i].भाग)
			- wm8993->bclk;
		अगर (cur_val < 0) /* Table is sorted */
			अवरोध;
		अगर (cur_val < best_val) अणु
			best = i;
			best_val = cur_val;
		पूर्ण
	पूर्ण
	wm8993->bclk = (wm8993->sysclk_rate * 10) / bclk_भागs[best].भाग;
	dev_dbg(component->dev, "Selected BCLK_DIV of %d for %dHz BCLK\n",
		bclk_भागs[best].भाग, wm8993->bclk);
	घड़ीing1 |= bclk_भागs[best].bclk_भाग << WM8993_BCLK_DIV_SHIFT;

	/* LRCLK is a simple fraction of BCLK */
	dev_dbg(component->dev, "LRCLK_RATE is %d\n", wm8993->bclk / wm8993->fs);
	aअगर4 |= wm8993->bclk / wm8993->fs;

	snd_soc_component_ग_लिखो(component, WM8993_CLOCKING_1, घड़ीing1);
	snd_soc_component_ग_लिखो(component, WM8993_CLOCKING_3, घड़ीing3);
	snd_soc_component_ग_लिखो(component, WM8993_AUDIO_INTERFACE_1, aअगर1);
	snd_soc_component_ग_लिखो(component, WM8993_AUDIO_INTERFACE_4, aअगर4);

	/* ReTune Mobile? */
	अगर (wm8993->pdata.num_retune_configs) अणु
		u16 eq1 = snd_soc_component_पढ़ो(component, WM8993_EQ1);
		काष्ठा wm8993_retune_mobile_setting *s;

		best = 0;
		best_val = असल(wm8993->pdata.retune_configs[0].rate
			       - wm8993->fs);
		क्रम (i = 0; i < wm8993->pdata.num_retune_configs; i++) अणु
			cur_val = असल(wm8993->pdata.retune_configs[i].rate
				      - wm8993->fs);
			अगर (cur_val < best_val) अणु
				best_val = cur_val;
				best = i;
			पूर्ण
		पूर्ण
		s = &wm8993->pdata.retune_configs[best];

		dev_dbg(component->dev, "ReTune Mobile %s tuned for %dHz\n",
			s->name, s->rate);

		/* Disable EQ जबतक we reconfigure */
		snd_soc_component_update_bits(component, WM8993_EQ1, WM8993_EQ_ENA, 0);

		क्रम (i = 1; i < ARRAY_SIZE(s->config); i++)
			snd_soc_component_ग_लिखो(component, WM8993_EQ1 + i, s->config[i]);

		snd_soc_component_update_bits(component, WM8993_EQ1, WM8993_EQ_ENA, eq1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8993_mute(काष्ठा snd_soc_dai *codec_dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	अचिन्हित पूर्णांक reg;

	reg = snd_soc_component_पढ़ो(component, WM8993_DAC_CTRL);

	अगर (mute)
		reg |= WM8993_DAC_MUTE;
	अन्यथा
		reg &= ~WM8993_DAC_MUTE;

	snd_soc_component_ग_लिखो(component, WM8993_DAC_CTRL, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8993_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
			       अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8993_priv *wm8993 = snd_soc_component_get_drvdata(component);
	पूर्णांक aअगर1 = 0;
	पूर्णांक aअगर2 = 0;

	/* Don't need to validate anything if we're turning off TDM */
	अगर (slots == 0) अणु
		wm8993->tdm_slots = 0;
		जाओ out;
	पूर्ण

	/* Note that we allow configurations we can't handle ourselves - 
	 * क्रम example, we can generate घड़ीs क्रम slots 2 and up even अगर
	 * we can't use those slots ourselves.
	 */
	aअगर1 |= WM8993_AIFADC_TDM;
	aअगर2 |= WM8993_AIFDAC_TDM;

	चयन (rx_mask) अणु
	हाल 3:
		अवरोध;
	हाल 0xc:
		aअगर1 |= WM8993_AIFADC_TDM_CHAN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण


	चयन (tx_mask) अणु
	हाल 3:
		अवरोध;
	हाल 0xc:
		aअगर2 |= WM8993_AIFDAC_TDM_CHAN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

out:
	wm8993->tdm_width = slot_width;
	wm8993->tdm_slots = slots / 2;

	snd_soc_component_update_bits(component, WM8993_AUDIO_INTERFACE_1,
			    WM8993_AIFADC_TDM | WM8993_AIFADC_TDM_CHAN, aअगर1);
	snd_soc_component_update_bits(component, WM8993_AUDIO_INTERFACE_2,
			    WM8993_AIFDAC_TDM | WM8993_AIFDAC_TDM_CHAN, aअगर2);

	वापस 0;
पूर्ण

अटल irqवापस_t wm8993_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm8993_priv *wm8993 = data;
	पूर्णांक mask, val, ret;

	ret = regmap_पढ़ो(wm8993->regmap, WM8993_GPIO_CTRL_1, &val);
	अगर (ret != 0) अणु
		dev_err(wm8993->dev, "Failed to read interrupt status: %d\n",
			ret);
		वापस IRQ_NONE;
	पूर्ण

	ret = regmap_पढ़ो(wm8993->regmap, WM8993_GPIOCTRL_2, &mask);
	अगर (ret != 0) अणु
		dev_err(wm8993->dev, "Failed to read interrupt mask: %d\n",
			ret);
		वापस IRQ_NONE;
	पूर्ण

	/* The IRQ pin status is visible in the रेजिस्टर too */
	val &= ~(mask | WM8993_IRQ);
	अगर (!val)
		वापस IRQ_NONE;

	अगर (val & WM8993_TEMPOK_EINT)
		dev_crit(wm8993->dev, "Thermal warning\n");

	अगर (val & WM8993_FLL_LOCK_EINT) अणु
		dev_dbg(wm8993->dev, "FLL locked\n");
		complete(&wm8993->fll_lock);
	पूर्ण

	ret = regmap_ग_लिखो(wm8993->regmap, WM8993_GPIO_CTRL_1, val);
	अगर (ret != 0)
		dev_err(wm8993->dev, "Failed to ack interrupt: %d\n", ret);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops wm8993_ops = अणु
	.set_sysclk = wm8993_set_sysclk,
	.set_fmt = wm8993_set_dai_fmt,
	.hw_params = wm8993_hw_params,
	.mute_stream = wm8993_mute,
	.set_pll = wm8993_set_fll,
	.set_tdm_slot = wm8993_set_tdm_slot,
	.no_capture_mute = 1,
पूर्ण;

#घोषणा WM8993_RATES SNDRV_PCM_RATE_8000_48000

#घोषणा WM8993_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
			SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE |\
			SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver wm8993_dai = अणु
	.name = "wm8993-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8993_RATES,
		.क्रमmats = WM8993_FORMATS,
		.sig_bits = 24,
	पूर्ण,
	.capture = अणु
		 .stream_name = "Capture",
		 .channels_min = 1,
		 .channels_max = 2,
		 .rates = WM8993_RATES,
		 .क्रमmats = WM8993_FORMATS,
		 .sig_bits = 24,
	 पूर्ण,
	.ops = &wm8993_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक wm8993_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8993_priv *wm8993 = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	wm8993->hubs_data.hp_startup_mode = 1;
	wm8993->hubs_data.dcs_codes_l = -2;
	wm8993->hubs_data.dcs_codes_r = -2;
	wm8993->hubs_data.series_startup = 1;

	/* Latch volume update bits and शेष ZC on */
	snd_soc_component_update_bits(component, WM8993_RIGHT_DAC_DIGITAL_VOLUME,
			    WM8993_DAC_VU, WM8993_DAC_VU);
	snd_soc_component_update_bits(component, WM8993_RIGHT_ADC_DIGITAL_VOLUME,
			    WM8993_ADC_VU, WM8993_ADC_VU);

	/* Manualy manage the HPOUT sequencing क्रम independent stereo
	 * control. */
	snd_soc_component_update_bits(component, WM8993_ANALOGUE_HP_0,
			    WM8993_HPOUT1_AUTO_PU, 0);

	/* Use स्वतःmatic घड़ी configuration */
	snd_soc_component_update_bits(component, WM8993_CLOCKING_4, WM8993_SR_MODE, 0);

	wm_hubs_handle_analogue_pdata(component, wm8993->pdata.lineout1_dअगरf,
				      wm8993->pdata.lineout2_dअगरf,
				      wm8993->pdata.lineout1fb,
				      wm8993->pdata.lineout2fb,
				      wm8993->pdata.jd_scthr,
				      wm8993->pdata.jd_thr,
				      wm8993->pdata.micbias1_delay,
				      wm8993->pdata.micbias2_delay,
				      wm8993->pdata.micbias1_lvl,
				      wm8993->pdata.micbias2_lvl);

	snd_soc_add_component_controls(component, wm8993_snd_controls,
			     ARRAY_SIZE(wm8993_snd_controls));
	अगर (wm8993->pdata.num_retune_configs != 0) अणु
		dev_dbg(component->dev, "Using ReTune Mobile\n");
	पूर्ण अन्यथा अणु
		dev_dbg(component->dev, "No ReTune Mobile, using normal EQ\n");
		snd_soc_add_component_controls(component, wm8993_eq_controls,
				     ARRAY_SIZE(wm8993_eq_controls));
	पूर्ण

	snd_soc_dapm_new_controls(dapm, wm8993_dapm_widमाला_लो,
				  ARRAY_SIZE(wm8993_dapm_widमाला_लो));
	wm_hubs_add_analogue_controls(component);

	snd_soc_dapm_add_routes(dapm, routes, ARRAY_SIZE(routes));
	wm_hubs_add_analogue_routes(component, wm8993->pdata.lineout1_dअगरf,
				    wm8993->pdata.lineout2_dअगरf);

	/* If the line outमाला_दो are dअगरferential then we aren't presenting
	 * VMID as an output and can disable it.
	 */
	अगर (wm8993->pdata.lineout1_dअगरf && wm8993->pdata.lineout2_dअगरf)
		dapm->idle_bias_off = 1;

	वापस 0;

पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक wm8993_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8993_priv *wm8993 = snd_soc_component_get_drvdata(component);
	पूर्णांक fll_fout = wm8993->fll_fout;
	पूर्णांक fll_fref  = wm8993->fll_fref;
	पूर्णांक ret;

	/* Stop the FLL in an orderly fashion */
	ret = _wm8993_set_fll(component, 0, 0, 0, 0);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to stop FLL\n");
		वापस ret;
	पूर्ण

	wm8993->fll_fout = fll_fout;
	wm8993->fll_fref = fll_fref;

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_OFF);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8993_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8993_priv *wm8993 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_STANDBY);

	/* Restart the FLL? */
	अगर (wm8993->fll_fout) अणु
		पूर्णांक fll_fout = wm8993->fll_fout;
		पूर्णांक fll_fref  = wm8993->fll_fref;

		wm8993->fll_fref = 0;
		wm8993->fll_fout = 0;

		ret = _wm8993_set_fll(component, 0, wm8993->fll_src,
				     fll_fref, fll_fout);
		अगर (ret != 0)
			dev_err(component->dev, "Failed to restart FLL\n");
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा wm8993_suspend शून्य
#घोषणा wm8993_resume शून्य
#पूर्ण_अगर

/* Tune DC servo configuration */
अटल स्थिर काष्ठा reg_sequence wm8993_regmap_patch[] = अणु
	अणु 0x44, 3 पूर्ण,
	अणु 0x56, 3 पूर्ण,
	अणु 0x44, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm8993_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,

	.max_रेजिस्टर = WM8993_MAX_REGISTER,
	.अस्थिर_reg = wm8993_अस्थिर,
	.पढ़ोable_reg = wm8993_पढ़ोable,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = wm8993_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8993_reg_शेषs),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8993 = अणु
	.probe			= wm8993_probe,
	.suspend		= wm8993_suspend,
	.resume			= wm8993_resume,
	.set_bias_level		= wm8993_set_bias_level,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक wm8993_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8993_priv *wm8993;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret, i;

	wm8993 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8993_priv),
			      GFP_KERNEL);
	अगर (wm8993 == शून्य)
		वापस -ENOMEM;

	wm8993->dev = &i2c->dev;
	init_completion(&wm8993->fll_lock);

	wm8993->regmap = devm_regmap_init_i2c(i2c, &wm8993_regmap);
	अगर (IS_ERR(wm8993->regmap)) अणु
		ret = PTR_ERR(wm8993->regmap);
		dev_err(&i2c->dev, "Failed to allocate regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(i2c, wm8993);

	क्रम (i = 0; i < ARRAY_SIZE(wm8993->supplies); i++)
		wm8993->supplies[i].supply = wm8993_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev, ARRAY_SIZE(wm8993->supplies),
				 wm8993->supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8993->supplies),
				    wm8993->supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(wm8993->regmap, WM8993_SOFTWARE_RESET, &reg);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to read chip ID: %d\n", ret);
		जाओ err_enable;
	पूर्ण

	अगर (reg != 0x8993) अणु
		dev_err(&i2c->dev, "Invalid ID register value %x\n", reg);
		ret = -EINVAL;
		जाओ err_enable;
	पूर्ण

	ret = regmap_ग_लिखो(wm8993->regmap, WM8993_SOFTWARE_RESET, 0xffff);
	अगर (ret != 0)
		जाओ err_enable;

	ret = regmap_रेजिस्टर_patch(wm8993->regmap, wm8993_regmap_patch,
				    ARRAY_SIZE(wm8993_regmap_patch));
	अगर (ret != 0)
		dev_warn(wm8993->dev, "Failed to apply regmap patch: %d\n",
			 ret);

	अगर (i2c->irq) अणु
		/* Put GPIO1 पूर्णांकo पूर्णांकerrupt mode (only GPIO1 can output IRQ) */
		ret = regmap_update_bits(wm8993->regmap, WM8993_GPIO1,
					 WM8993_GPIO1_PD |
					 WM8993_GPIO1_SEL_MASK, 7);
		अगर (ret != 0)
			जाओ err_enable;

		ret = request_thपढ़ोed_irq(i2c->irq, शून्य, wm8993_irq,
					   IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					   "wm8993", wm8993);
		अगर (ret != 0)
			जाओ err_enable;

	पूर्ण

	regulator_bulk_disable(ARRAY_SIZE(wm8993->supplies), wm8993->supplies);

	regcache_cache_only(wm8993->regmap, true);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_wm8993, &wm8993_dai, 1);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to register CODEC: %d\n", ret);
		जाओ err_irq;
	पूर्ण

	वापस 0;

err_irq:
	अगर (i2c->irq)
		मुक्त_irq(i2c->irq, wm8993);
err_enable:
	regulator_bulk_disable(ARRAY_SIZE(wm8993->supplies), wm8993->supplies);
	वापस ret;
पूर्ण

अटल पूर्णांक wm8993_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा wm8993_priv *wm8993 = i2c_get_clientdata(i2c);

	अगर (i2c->irq)
		मुक्त_irq(i2c->irq, wm8993);
	regulator_bulk_disable(ARRAY_SIZE(wm8993->supplies), wm8993->supplies);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8993_i2c_id[] = अणु
	अणु "wm8993", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8993_i2c_id);

अटल काष्ठा i2c_driver wm8993_i2c_driver = अणु
	.driver = अणु
		.name = "wm8993",
	पूर्ण,
	.probe =    wm8993_i2c_probe,
	.हटाओ =   wm8993_i2c_हटाओ,
	.id_table = wm8993_i2c_id,
पूर्ण;

module_i2c_driver(wm8993_i2c_driver);

MODULE_DESCRIPTION("ASoC WM8993 driver");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
