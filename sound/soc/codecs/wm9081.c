<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm9081.c  --  WM9081 ALSA SoC Audio driver
 *
 * Author: Mark Brown
 *
 * Copyright 2009-12 Wolfson Microelectronics plc
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
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

#समावेश <sound/wm9081.h>
#समावेश "wm9081.h"

अटल स्थिर काष्ठा reg_शेष wm9081_reg[] = अणु
	अणु  2, 0x00B9 पूर्ण,     /* R2  - Analogue Lineout */
	अणु  3, 0x00B9 पूर्ण,     /* R3  - Analogue Speaker PGA */
	अणु  4, 0x0001 पूर्ण,     /* R4  - VMID Control */
	अणु  5, 0x0068 पूर्ण,     /* R5  - Bias Control 1 */
	अणु  7, 0x0000 पूर्ण,     /* R7  - Analogue Mixer */
	अणु  8, 0x0000 पूर्ण,     /* R8  - Anti Pop Control */
	अणु  9, 0x01DB पूर्ण,     /* R9  - Analogue Speaker 1 */
	अणु 10, 0x0018 पूर्ण,     /* R10 - Analogue Speaker 2 */
	अणु 11, 0x0180 पूर्ण,     /* R11 - Power Management */
	अणु 12, 0x0000 पूर्ण,     /* R12 - Clock Control 1 */
	अणु 13, 0x0038 पूर्ण,     /* R13 - Clock Control 2 */
	अणु 14, 0x4000 पूर्ण,     /* R14 - Clock Control 3 */
	अणु 16, 0x0000 पूर्ण,     /* R16 - FLL Control 1 */
	अणु 17, 0x0200 पूर्ण,     /* R17 - FLL Control 2 */
	अणु 18, 0x0000 पूर्ण,     /* R18 - FLL Control 3 */
	अणु 19, 0x0204 पूर्ण,     /* R19 - FLL Control 4 */
	अणु 20, 0x0000 पूर्ण,     /* R20 - FLL Control 5 */
	अणु 22, 0x0000 पूर्ण,     /* R22 - Audio Interface 1 */
	अणु 23, 0x0002 पूर्ण,     /* R23 - Audio Interface 2 */
	अणु 24, 0x0008 पूर्ण,     /* R24 - Audio Interface 3 */
	अणु 25, 0x0022 पूर्ण,     /* R25 - Audio Interface 4 */
	अणु 27, 0x0006 पूर्ण,     /* R27 - Interrupt Status Mask */
	अणु 28, 0x0000 पूर्ण,     /* R28 - Interrupt Polarity */
	अणु 29, 0x0000 पूर्ण,     /* R29 - Interrupt Control */
	अणु 30, 0x00C0 पूर्ण,     /* R30 - DAC Digital 1 */
	अणु 31, 0x0008 पूर्ण,     /* R31 - DAC Digital 2 */
	अणु 32, 0x09AF पूर्ण,     /* R32 - DRC 1 */
	अणु 33, 0x4201 पूर्ण,     /* R33 - DRC 2 */
	अणु 34, 0x0000 पूर्ण,     /* R34 - DRC 3 */
	अणु 35, 0x0000 पूर्ण,     /* R35 - DRC 4 */
	अणु 38, 0x0000 पूर्ण,     /* R38 - Write Sequencer 1 */
	अणु 39, 0x0000 पूर्ण,     /* R39 - Write Sequencer 2 */
	अणु 40, 0x0002 पूर्ण,     /* R40 - MW Slave 1 */
	अणु 42, 0x0000 पूर्ण,     /* R42 - EQ 1 */
	अणु 43, 0x0000 पूर्ण,     /* R43 - EQ 2 */
	अणु 44, 0x0FCA पूर्ण,     /* R44 - EQ 3 */
	अणु 45, 0x0400 पूर्ण,     /* R45 - EQ 4 */
	अणु 46, 0x00B8 पूर्ण,     /* R46 - EQ 5 */
	अणु 47, 0x1EB5 पूर्ण,     /* R47 - EQ 6 */
	अणु 48, 0xF145 पूर्ण,     /* R48 - EQ 7 */
	अणु 49, 0x0B75 पूर्ण,     /* R49 - EQ 8 */
	अणु 50, 0x01C5 पूर्ण,     /* R50 - EQ 9 */
	अणु 51, 0x169E पूर्ण,     /* R51 - EQ 10 */
	अणु 52, 0xF829 पूर्ण,     /* R52 - EQ 11 */
	अणु 53, 0x07AD पूर्ण,     /* R53 - EQ 12 */
	अणु 54, 0x1103 पूर्ण,     /* R54 - EQ 13 */
	अणु 55, 0x1C58 पूर्ण,     /* R55 - EQ 14 */
	अणु 56, 0xF373 पूर्ण,     /* R56 - EQ 15 */
	अणु 57, 0x0A54 पूर्ण,     /* R57 - EQ 16 */
	अणु 58, 0x0558 पूर्ण,     /* R58 - EQ 17 */
	अणु 59, 0x0564 पूर्ण,     /* R59 - EQ 18 */
	अणु 60, 0x0559 पूर्ण,     /* R60 - EQ 19 */
	अणु 61, 0x4000 पूर्ण,     /* R61 - EQ 20 */
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
	अणु 12000, 2  पूर्ण,
	अणु 16000, 3  पूर्ण,
	अणु 22050, 4  पूर्ण,
	अणु 24000, 5  पूर्ण,
	अणु 32000, 6  पूर्ण,
	अणु 44100, 7  पूर्ण,
	अणु 48000, 8  पूर्ण,
	अणु 88200, 9  पूर्ण,
	अणु 96000, 10 पूर्ण,
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
	अणु 240, 15 पूर्ण,
	अणु 250, 16 पूर्ण,
	अणु 300, 17 पूर्ण,
	अणु 320, 18 पूर्ण,
	अणु 440, 19 पूर्ण,
	अणु 480, 20 पूर्ण,
पूर्ण;

काष्ठा wm9081_priv अणु
	काष्ठा regmap *regmap;
	पूर्णांक sysclk_source;
	पूर्णांक mclk_rate;
	पूर्णांक sysclk_rate;
	पूर्णांक fs;
	पूर्णांक bclk;
	पूर्णांक master;
	पूर्णांक fll_fref;
	पूर्णांक fll_fout;
	पूर्णांक tdm_width;
	काष्ठा wm9081_pdata pdata;
पूर्ण;

अटल bool wm9081_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM9081_SOFTWARE_RESET:
	हाल WM9081_INTERRUPT_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool wm9081_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM9081_SOFTWARE_RESET:
	हाल WM9081_ANALOGUE_LINEOUT:
	हाल WM9081_ANALOGUE_SPEAKER_PGA:
	हाल WM9081_VMID_CONTROL:
	हाल WM9081_BIAS_CONTROL_1:
	हाल WM9081_ANALOGUE_MIXER:
	हाल WM9081_ANTI_POP_CONTROL:
	हाल WM9081_ANALOGUE_SPEAKER_1:
	हाल WM9081_ANALOGUE_SPEAKER_2:
	हाल WM9081_POWER_MANAGEMENT:
	हाल WM9081_CLOCK_CONTROL_1:
	हाल WM9081_CLOCK_CONTROL_2:
	हाल WM9081_CLOCK_CONTROL_3:
	हाल WM9081_FLL_CONTROL_1:
	हाल WM9081_FLL_CONTROL_2:
	हाल WM9081_FLL_CONTROL_3:
	हाल WM9081_FLL_CONTROL_4:
	हाल WM9081_FLL_CONTROL_5:
	हाल WM9081_AUDIO_INTERFACE_1:
	हाल WM9081_AUDIO_INTERFACE_2:
	हाल WM9081_AUDIO_INTERFACE_3:
	हाल WM9081_AUDIO_INTERFACE_4:
	हाल WM9081_INTERRUPT_STATUS:
	हाल WM9081_INTERRUPT_STATUS_MASK:
	हाल WM9081_INTERRUPT_POLARITY:
	हाल WM9081_INTERRUPT_CONTROL:
	हाल WM9081_DAC_DIGITAL_1:
	हाल WM9081_DAC_DIGITAL_2:
	हाल WM9081_DRC_1:
	हाल WM9081_DRC_2:
	हाल WM9081_DRC_3:
	हाल WM9081_DRC_4:
	हाल WM9081_WRITE_SEQUENCER_1:
	हाल WM9081_WRITE_SEQUENCER_2:
	हाल WM9081_MW_SLAVE_1:
	हाल WM9081_EQ_1:
	हाल WM9081_EQ_2:
	हाल WM9081_EQ_3:
	हाल WM9081_EQ_4:
	हाल WM9081_EQ_5:
	हाल WM9081_EQ_6:
	हाल WM9081_EQ_7:
	हाल WM9081_EQ_8:
	हाल WM9081_EQ_9:
	हाल WM9081_EQ_10:
	हाल WM9081_EQ_11:
	हाल WM9081_EQ_12:
	हाल WM9081_EQ_13:
	हाल WM9081_EQ_14:
	हाल WM9081_EQ_15:
	हाल WM9081_EQ_16:
	हाल WM9081_EQ_17:
	हाल WM9081_EQ_18:
	हाल WM9081_EQ_19:
	हाल WM9081_EQ_20:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक wm9081_reset(काष्ठा regmap *map)
अणु
	वापस regmap_ग_लिखो(map, WM9081_SOFTWARE_RESET, 0x9081);
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(drc_in_tlv, -4500, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(drc_out_tlv, -2250, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(drc_min_tlv, -1800, 600, 0);
अटल स्थिर DECLARE_TLV_DB_RANGE(drc_max_tlv,
	0, 0, TLV_DB_SCALE_ITEM(1200, 0, 0),
	1, 1, TLV_DB_SCALE_ITEM(1800, 0, 0),
	2, 2, TLV_DB_SCALE_ITEM(2400, 0, 0),
	3, 3, TLV_DB_SCALE_ITEM(3600, 0, 0)
);
अटल स्थिर DECLARE_TLV_DB_SCALE(drc_qr_tlv, 1200, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(drc_startup_tlv, -300, 50, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(eq_tlv, -1200, 100, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(in_tlv, -600, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(dac_tlv, -7200, 75, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(out_tlv, -5700, 100, 0);

अटल स्थिर अक्षर *drc_high_text[] = अणु
	"1",
	"1/2",
	"1/4",
	"1/8",
	"1/16",
	"0",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(drc_high, WM9081_DRC_3, 3, drc_high_text);

अटल स्थिर अक्षर *drc_low_text[] = अणु
	"1",
	"1/2",
	"1/4",
	"1/8",
	"0",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(drc_low, WM9081_DRC_3, 0, drc_low_text);

अटल स्थिर अक्षर *drc_atk_text[] = अणु
	"181us",
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

अटल SOC_ENUM_SINGLE_DECL(drc_atk, WM9081_DRC_2, 12, drc_atk_text);

अटल स्थिर अक्षर *drc_dcy_text[] = अणु
	"186ms",
	"372ms",
	"743ms",
	"1.49s",
	"2.97s",
	"5.94s",
	"11.89s",
	"23.78s",
	"47.56s",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(drc_dcy, WM9081_DRC_2, 8, drc_dcy_text);

अटल स्थिर अक्षर *drc_qr_dcy_text[] = अणु
	"0.725ms",
	"1.45ms",
	"5.8ms",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(drc_qr_dcy, WM9081_DRC_2, 4, drc_qr_dcy_text);

अटल स्थिर अक्षर *dac_deemph_text[] = अणु
	"None",
	"32kHz",
	"44.1kHz",
	"48kHz",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(dac_deemph, WM9081_DAC_DIGITAL_2, 1,
			    dac_deemph_text);

अटल स्थिर अक्षर *speaker_mode_text[] = अणु
	"Class D",
	"Class AB",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(speaker_mode, WM9081_ANALOGUE_SPEAKER_2, 6,
			    speaker_mode_text);

अटल पूर्णांक speaker_mode_get(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	अचिन्हित पूर्णांक reg;

	reg = snd_soc_component_पढ़ो(component, WM9081_ANALOGUE_SPEAKER_2);
	अगर (reg & WM9081_SPK_MODE)
		ucontrol->value.क्रमागतerated.item[0] = 1;
	अन्यथा
		ucontrol->value.क्रमागतerated.item[0] = 0;

	वापस 0;
पूर्ण

/*
 * Stop any attempts to change speaker mode जबतक the speaker is enabled.
 *
 * We also have some special anti-pop controls dependent on speaker
 * mode which must be changed aदीर्घ with the mode.
 */
अटल पूर्णांक speaker_mode_put(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	अचिन्हित पूर्णांक reg_pwr = snd_soc_component_पढ़ो(component, WM9081_POWER_MANAGEMENT);
	अचिन्हित पूर्णांक reg2 = snd_soc_component_पढ़ो(component, WM9081_ANALOGUE_SPEAKER_2);

	/* Are we changing anything? */
	अगर (ucontrol->value.क्रमागतerated.item[0] ==
	    ((reg2 & WM9081_SPK_MODE) != 0))
		वापस 0;

	/* Don't try to change modes जबतक enabled */
	अगर (reg_pwr & WM9081_SPK_ENA)
		वापस -EINVAL;

	अगर (ucontrol->value.क्रमागतerated.item[0]) अणु
		/* Class AB */
		reg2 &= ~(WM9081_SPK_INV_MUTE | WM9081_OUT_SPK_CTRL);
		reg2 |= WM9081_SPK_MODE;
	पूर्ण अन्यथा अणु
		/* Class D */
		reg2 |= WM9081_SPK_INV_MUTE | WM9081_OUT_SPK_CTRL;
		reg2 &= ~WM9081_SPK_MODE;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM9081_ANALOGUE_SPEAKER_2, reg2);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new wm9081_snd_controls[] = अणु
SOC_SINGLE_TLV("IN1 Volume", WM9081_ANALOGUE_MIXER, 1, 1, 1, in_tlv),
SOC_SINGLE_TLV("IN2 Volume", WM9081_ANALOGUE_MIXER, 3, 1, 1, in_tlv),

SOC_SINGLE_TLV("Playback Volume", WM9081_DAC_DIGITAL_1, 1, 96, 0, dac_tlv),

SOC_SINGLE("LINEOUT Switch", WM9081_ANALOGUE_LINEOUT, 7, 1, 1),
SOC_SINGLE("LINEOUT ZC Switch", WM9081_ANALOGUE_LINEOUT, 6, 1, 0),
SOC_SINGLE_TLV("LINEOUT Volume", WM9081_ANALOGUE_LINEOUT, 0, 63, 0, out_tlv),

SOC_SINGLE("DRC Switch", WM9081_DRC_1, 15, 1, 0),
SOC_ENUM("DRC High Slope", drc_high),
SOC_ENUM("DRC Low Slope", drc_low),
SOC_SINGLE_TLV("DRC Input Volume", WM9081_DRC_4, 5, 60, 1, drc_in_tlv),
SOC_SINGLE_TLV("DRC Output Volume", WM9081_DRC_4, 0, 30, 1, drc_out_tlv),
SOC_SINGLE_TLV("DRC Minimum Volume", WM9081_DRC_2, 2, 3, 1, drc_min_tlv),
SOC_SINGLE_TLV("DRC Maximum Volume", WM9081_DRC_2, 0, 3, 0, drc_max_tlv),
SOC_ENUM("DRC Attack", drc_atk),
SOC_ENUM("DRC Decay", drc_dcy),
SOC_SINGLE("DRC Quick Release Switch", WM9081_DRC_1, 2, 1, 0),
SOC_SINGLE_TLV("DRC Quick Release Volume", WM9081_DRC_2, 6, 3, 0, drc_qr_tlv),
SOC_ENUM("DRC Quick Release Decay", drc_qr_dcy),
SOC_SINGLE_TLV("DRC Startup Volume", WM9081_DRC_1, 6, 18, 0, drc_startup_tlv),

SOC_SINGLE("EQ Switch", WM9081_EQ_1, 0, 1, 0),

SOC_SINGLE("Speaker DC Volume", WM9081_ANALOGUE_SPEAKER_1, 3, 5, 0),
SOC_SINGLE("Speaker AC Volume", WM9081_ANALOGUE_SPEAKER_1, 0, 5, 0),
SOC_SINGLE("Speaker Switch", WM9081_ANALOGUE_SPEAKER_PGA, 7, 1, 1),
SOC_SINGLE("Speaker ZC Switch", WM9081_ANALOGUE_SPEAKER_PGA, 6, 1, 0),
SOC_SINGLE_TLV("Speaker Volume", WM9081_ANALOGUE_SPEAKER_PGA, 0, 63, 0,
	       out_tlv),
SOC_ENUM("DAC Deemphasis", dac_deemph),
SOC_ENUM_EXT("Speaker Mode", speaker_mode, speaker_mode_get, speaker_mode_put),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm9081_eq_controls[] = अणु
SOC_SINGLE_TLV("EQ1 Volume", WM9081_EQ_1, 11, 24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ2 Volume", WM9081_EQ_1, 6, 24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ3 Volume", WM9081_EQ_1, 1, 24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ4 Volume", WM9081_EQ_2, 11, 24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ5 Volume", WM9081_EQ_2, 6, 24, 0, eq_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mixer[] = अणु
SOC_DAPM_SINGLE("IN1 Switch", WM9081_ANALOGUE_MIXER, 0, 1, 0),
SOC_DAPM_SINGLE("IN2 Switch", WM9081_ANALOGUE_MIXER, 2, 1, 0),
SOC_DAPM_SINGLE("Playback Switch", WM9081_ANALOGUE_MIXER, 4, 1, 0),
पूर्ण;

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
	जबतक ((Fref / भाग) > 13500000) अणु
		भाग *= 2;

		अगर (भाग > 8) अणु
			pr_err("Can't scale %dMHz input down to <=13.5MHz\n",
			       Fref);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	fll_भाग->fll_clk_ref_भाग = भाग / 2;

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

अटल पूर्णांक wm9081_set_fll(काष्ठा snd_soc_component *component, पूर्णांक fll_id,
			  अचिन्हित पूर्णांक Fref, अचिन्हित पूर्णांक Fout)
अणु
	काष्ठा wm9081_priv *wm9081 = snd_soc_component_get_drvdata(component);
	u16 reg1, reg4, reg5;
	काष्ठा _fll_भाग fll_भाग;
	पूर्णांक ret;
	पूर्णांक clk_sys_reg;

	/* Any change? */
	अगर (Fref == wm9081->fll_fref && Fout == wm9081->fll_fout)
		वापस 0;

	/* Disable the FLL */
	अगर (Fout == 0) अणु
		dev_dbg(component->dev, "FLL disabled\n");
		wm9081->fll_fref = 0;
		wm9081->fll_fout = 0;

		वापस 0;
	पूर्ण

	ret = fll_factors(&fll_भाग, Fref, Fout);
	अगर (ret != 0)
		वापस ret;

	reg5 = snd_soc_component_पढ़ो(component, WM9081_FLL_CONTROL_5);
	reg5 &= ~WM9081_FLL_CLK_SRC_MASK;

	चयन (fll_id) अणु
	हाल WM9081_SYSCLK_FLL_MCLK:
		reg5 |= 0x1;
		अवरोध;

	शेष:
		dev_err(component->dev, "Unknown FLL ID %d\n", fll_id);
		वापस -EINVAL;
	पूर्ण

	/* Disable CLK_SYS जबतक we reconfigure */
	clk_sys_reg = snd_soc_component_पढ़ो(component, WM9081_CLOCK_CONTROL_3);
	अगर (clk_sys_reg & WM9081_CLK_SYS_ENA)
		snd_soc_component_ग_लिखो(component, WM9081_CLOCK_CONTROL_3,
			     clk_sys_reg & ~WM9081_CLK_SYS_ENA);

	/* Any FLL configuration change requires that the FLL be
	 * disabled first. */
	reg1 = snd_soc_component_पढ़ो(component, WM9081_FLL_CONTROL_1);
	reg1 &= ~WM9081_FLL_ENA;
	snd_soc_component_ग_लिखो(component, WM9081_FLL_CONTROL_1, reg1);

	/* Apply the configuration */
	अगर (fll_भाग.k)
		reg1 |= WM9081_FLL_FRAC_MASK;
	अन्यथा
		reg1 &= ~WM9081_FLL_FRAC_MASK;
	snd_soc_component_ग_लिखो(component, WM9081_FLL_CONTROL_1, reg1);

	snd_soc_component_ग_लिखो(component, WM9081_FLL_CONTROL_2,
		     (fll_भाग.fll_outभाग << WM9081_FLL_OUTDIV_SHIFT) |
		     (fll_भाग.fll_fratio << WM9081_FLL_FRATIO_SHIFT));
	snd_soc_component_ग_लिखो(component, WM9081_FLL_CONTROL_3, fll_भाग.k);

	reg4 = snd_soc_component_पढ़ो(component, WM9081_FLL_CONTROL_4);
	reg4 &= ~WM9081_FLL_N_MASK;
	reg4 |= fll_भाग.n << WM9081_FLL_N_SHIFT;
	snd_soc_component_ग_लिखो(component, WM9081_FLL_CONTROL_4, reg4);

	reg5 &= ~WM9081_FLL_CLK_REF_DIV_MASK;
	reg5 |= fll_भाग.fll_clk_ref_भाग << WM9081_FLL_CLK_REF_DIV_SHIFT;
	snd_soc_component_ग_लिखो(component, WM9081_FLL_CONTROL_5, reg5);

	/* Set gain to the recommended value */
	snd_soc_component_update_bits(component, WM9081_FLL_CONTROL_4,
			    WM9081_FLL_GAIN_MASK, 0);

	/* Enable the FLL */
	snd_soc_component_ग_लिखो(component, WM9081_FLL_CONTROL_1, reg1 | WM9081_FLL_ENA);

	/* Then bring CLK_SYS up again अगर it was disabled */
	अगर (clk_sys_reg & WM9081_CLK_SYS_ENA)
		snd_soc_component_ग_लिखो(component, WM9081_CLOCK_CONTROL_3, clk_sys_reg);

	dev_dbg(component->dev, "FLL enabled at %dHz->%dHz\n", Fref, Fout);

	wm9081->fll_fref = Fref;
	wm9081->fll_fout = Fout;

	वापस 0;
पूर्ण

अटल पूर्णांक configure_घड़ी(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm9081_priv *wm9081 = snd_soc_component_get_drvdata(component);
	पूर्णांक new_sysclk, i, target;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret = 0;
	पूर्णांक mclkभाग = 0;
	पूर्णांक fll = 0;

	चयन (wm9081->sysclk_source) अणु
	हाल WM9081_SYSCLK_MCLK:
		अगर (wm9081->mclk_rate > 12225000) अणु
			mclkभाग = 1;
			wm9081->sysclk_rate = wm9081->mclk_rate / 2;
		पूर्ण अन्यथा अणु
			wm9081->sysclk_rate = wm9081->mclk_rate;
		पूर्ण
		wm9081_set_fll(component, WM9081_SYSCLK_FLL_MCLK, 0, 0);
		अवरोध;

	हाल WM9081_SYSCLK_FLL_MCLK:
		/* If we have a sample rate calculate a CLK_SYS that
		 * gives us a suitable DAC configuration, plus BCLK.
		 * Ideally we would check to see अगर we can घड़ी
		 * directly from MCLK and only use the FLL अगर this is
		 * not the हाल, though care must be taken with मुक्त
		 * running mode.
		 */
		अगर (wm9081->master && wm9081->bclk) अणु
			/* Make sure we can generate CLK_SYS and BCLK
			 * and that we've got 3MHz क्रम optimal
			 * perक्रमmance. */
			क्रम (i = 0; i < ARRAY_SIZE(clk_sys_rates); i++) अणु
				target = wm9081->fs * clk_sys_rates[i].ratio;
				new_sysclk = target;
				अगर (target >= wm9081->bclk &&
				    target > 3000000)
					अवरोध;
			पूर्ण

			अगर (i == ARRAY_SIZE(clk_sys_rates))
				वापस -EINVAL;

		पूर्ण अन्यथा अगर (wm9081->fs) अणु
			क्रम (i = 0; i < ARRAY_SIZE(clk_sys_rates); i++) अणु
				new_sysclk = clk_sys_rates[i].ratio
					* wm9081->fs;
				अगर (new_sysclk > 3000000)
					अवरोध;
			पूर्ण

			अगर (i == ARRAY_SIZE(clk_sys_rates))
				वापस -EINVAL;

		पूर्ण अन्यथा अणु
			new_sysclk = 12288000;
		पूर्ण

		ret = wm9081_set_fll(component, WM9081_SYSCLK_FLL_MCLK,
				     wm9081->mclk_rate, new_sysclk);
		अगर (ret == 0) अणु
			wm9081->sysclk_rate = new_sysclk;

			/* Switch SYSCLK over to FLL */
			fll = 1;
		पूर्ण अन्यथा अणु
			wm9081->sysclk_rate = wm9081->mclk_rate;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	reg = snd_soc_component_पढ़ो(component, WM9081_CLOCK_CONTROL_1);
	अगर (mclkभाग)
		reg |= WM9081_MCLKDIV2;
	अन्यथा
		reg &= ~WM9081_MCLKDIV2;
	snd_soc_component_ग_लिखो(component, WM9081_CLOCK_CONTROL_1, reg);

	reg = snd_soc_component_पढ़ो(component, WM9081_CLOCK_CONTROL_3);
	अगर (fll)
		reg |= WM9081_CLK_SRC_SEL;
	अन्यथा
		reg &= ~WM9081_CLK_SRC_SEL;
	snd_soc_component_ग_लिखो(component, WM9081_CLOCK_CONTROL_3, reg);

	dev_dbg(component->dev, "CLK_SYS is %dHz\n", wm9081->sysclk_rate);

	वापस ret;
पूर्ण

अटल पूर्णांक clk_sys_event(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm9081_priv *wm9081 = snd_soc_component_get_drvdata(component);

	/* This should be करोne on init() क्रम bypass paths */
	चयन (wm9081->sysclk_source) अणु
	हाल WM9081_SYSCLK_MCLK:
		dev_dbg(component->dev, "Using %dHz MCLK\n", wm9081->mclk_rate);
		अवरोध;
	हाल WM9081_SYSCLK_FLL_MCLK:
		dev_dbg(component->dev, "Using %dHz MCLK with FLL\n",
			wm9081->mclk_rate);
		अवरोध;
	शेष:
		dev_err(component->dev, "System clock not configured\n");
		वापस -EINVAL;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		configure_घड़ी(component);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		/* Disable the FLL अगर it's running */
		wm9081_set_fll(component, 0, 0, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget wm9081_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("IN1"),
SND_SOC_DAPM_INPUT("IN2"),

SND_SOC_DAPM_DAC("DAC", शून्य, WM9081_POWER_MANAGEMENT, 0, 0),

SND_SOC_DAPM_MIXER_NAMED_CTL("Mixer", SND_SOC_NOPM, 0, 0,
			     mixer, ARRAY_SIZE(mixer)),

SND_SOC_DAPM_PGA("LINEOUT PGA", WM9081_POWER_MANAGEMENT, 4, 0, शून्य, 0),

SND_SOC_DAPM_PGA("Speaker PGA", WM9081_POWER_MANAGEMENT, 2, 0, शून्य, 0),
SND_SOC_DAPM_OUT_DRV("Speaker", WM9081_POWER_MANAGEMENT, 1, 0, शून्य, 0),

SND_SOC_DAPM_OUTPUT("LINEOUT"),
SND_SOC_DAPM_OUTPUT("SPKN"),
SND_SOC_DAPM_OUTPUT("SPKP"),

SND_SOC_DAPM_SUPPLY("CLK_SYS", WM9081_CLOCK_CONTROL_3, 0, 0, clk_sys_event,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("CLK_DSP", WM9081_CLOCK_CONTROL_3, 1, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("TOCLK", WM9081_CLOCK_CONTROL_3, 2, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("TSENSE", WM9081_POWER_MANAGEMENT, 7, 0, शून्य, 0),
पूर्ण;


अटल स्थिर काष्ठा snd_soc_dapm_route wm9081_audio_paths[] = अणु
	अणु "DAC", शून्य, "CLK_SYS" पूर्ण,
	अणु "DAC", शून्य, "CLK_DSP" पूर्ण,
	अणु "DAC", शून्य, "AIF" पूर्ण,

	अणु "Mixer", "IN1 Switch", "IN1" पूर्ण,
	अणु "Mixer", "IN2 Switch", "IN2" पूर्ण,
	अणु "Mixer", "Playback Switch", "DAC" पूर्ण,

	अणु "LINEOUT PGA", शून्य, "Mixer" पूर्ण,
	अणु "LINEOUT PGA", शून्य, "TOCLK" पूर्ण,
	अणु "LINEOUT PGA", शून्य, "CLK_SYS" पूर्ण,

	अणु "LINEOUT", शून्य, "LINEOUT PGA" पूर्ण,

	अणु "Speaker PGA", शून्य, "Mixer" पूर्ण,
	अणु "Speaker PGA", शून्य, "TOCLK" पूर्ण,
	अणु "Speaker PGA", शून्य, "CLK_SYS" पूर्ण,

	अणु "Speaker", शून्य, "Speaker PGA" पूर्ण,
	अणु "Speaker", शून्य, "TSENSE" पूर्ण,

	अणु "SPKN", शून्य, "Speaker" पूर्ण,
	अणु "SPKP", शून्य, "Speaker" पूर्ण,
पूर्ण;

अटल पूर्णांक wm9081_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm9081_priv *wm9081 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		/* VMID=2*40k */
		snd_soc_component_update_bits(component, WM9081_VMID_CONTROL,
				    WM9081_VMID_SEL_MASK, 0x2);

		/* Normal bias current */
		snd_soc_component_update_bits(component, WM9081_BIAS_CONTROL_1,
				    WM9081_STBY_BIAS_ENA, 0);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		/* Initial cold start */
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			regcache_cache_only(wm9081->regmap, false);
			regcache_sync(wm9081->regmap);

			/* Disable LINEOUT disअक्षरge */
			snd_soc_component_update_bits(component, WM9081_ANTI_POP_CONTROL,
					    WM9081_LINEOUT_DISCH, 0);

			/* Select startup bias source */
			snd_soc_component_update_bits(component, WM9081_BIAS_CONTROL_1,
					    WM9081_BIAS_SRC | WM9081_BIAS_ENA,
					    WM9081_BIAS_SRC | WM9081_BIAS_ENA);

			/* VMID 2*4k; Soft VMID ramp enable */
			snd_soc_component_update_bits(component, WM9081_VMID_CONTROL,
					    WM9081_VMID_RAMP |
					    WM9081_VMID_SEL_MASK,
					    WM9081_VMID_RAMP | 0x6);

			mdelay(100);

			/* Normal bias enable & soft start off */
			snd_soc_component_update_bits(component, WM9081_VMID_CONTROL,
					    WM9081_VMID_RAMP, 0);

			/* Standard bias source */
			snd_soc_component_update_bits(component, WM9081_BIAS_CONTROL_1,
					    WM9081_BIAS_SRC, 0);
		पूर्ण

		/* VMID 2*240k */
		snd_soc_component_update_bits(component, WM9081_VMID_CONTROL,
				    WM9081_VMID_SEL_MASK, 0x04);

		/* Standby bias current on */
		snd_soc_component_update_bits(component, WM9081_BIAS_CONTROL_1,
				    WM9081_STBY_BIAS_ENA,
				    WM9081_STBY_BIAS_ENA);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		/* Startup bias source and disable bias */
		snd_soc_component_update_bits(component, WM9081_BIAS_CONTROL_1,
				    WM9081_BIAS_SRC | WM9081_BIAS_ENA,
				    WM9081_BIAS_SRC);

		/* Disable VMID with soft ramping */
		snd_soc_component_update_bits(component, WM9081_VMID_CONTROL,
				    WM9081_VMID_RAMP | WM9081_VMID_SEL_MASK,
				    WM9081_VMID_RAMP);

		/* Actively disअक्षरge LINEOUT */
		snd_soc_component_update_bits(component, WM9081_ANTI_POP_CONTROL,
				    WM9081_LINEOUT_DISCH,
				    WM9081_LINEOUT_DISCH);

		regcache_cache_only(wm9081->regmap, true);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm9081_set_dai_fmt(काष्ठा snd_soc_dai *dai,
			      अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm9081_priv *wm9081 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक aअगर2 = snd_soc_component_पढ़ो(component, WM9081_AUDIO_INTERFACE_2);

	aअगर2 &= ~(WM9081_AIF_BCLK_INV | WM9081_AIF_LRCLK_INV |
		  WM9081_BCLK_सूची | WM9081_LRCLK_सूची | WM9081_AIF_FMT_MASK);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		wm9081->master = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		aअगर2 |= WM9081_LRCLK_सूची;
		wm9081->master = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		aअगर2 |= WM9081_BCLK_सूची;
		wm9081->master = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		aअगर2 |= WM9081_LRCLK_सूची | WM9081_BCLK_सूची;
		wm9081->master = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_B:
		aअगर2 |= WM9081_AIF_LRCLK_INV;
		fallthrough;
	हाल SND_SOC_DAIFMT_DSP_A:
		aअगर2 |= 0x3;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		aअगर2 |= 0x2;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		aअगर2 |= 0x1;
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
			aअगर2 |= WM9081_AIF_BCLK_INV;
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
			aअगर2 |= WM9081_AIF_BCLK_INV | WM9081_AIF_LRCLK_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			aअगर2 |= WM9081_AIF_BCLK_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_NB_IF:
			aअगर2 |= WM9081_AIF_LRCLK_INV;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM9081_AUDIO_INTERFACE_2, aअगर2);

	वापस 0;
पूर्ण

अटल पूर्णांक wm9081_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm9081_priv *wm9081 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret, i, best, best_val, cur_val;
	अचिन्हित पूर्णांक clk_ctrl2, aअगर1, aअगर2, aअगर3, aअगर4;

	clk_ctrl2 = snd_soc_component_पढ़ो(component, WM9081_CLOCK_CONTROL_2);
	clk_ctrl2 &= ~(WM9081_CLK_SYS_RATE_MASK | WM9081_SAMPLE_RATE_MASK);

	aअगर1 = snd_soc_component_पढ़ो(component, WM9081_AUDIO_INTERFACE_1);

	aअगर2 = snd_soc_component_पढ़ो(component, WM9081_AUDIO_INTERFACE_2);
	aअगर2 &= ~WM9081_AIF_WL_MASK;

	aअगर3 = snd_soc_component_पढ़ो(component, WM9081_AUDIO_INTERFACE_3);
	aअगर3 &= ~WM9081_BCLK_DIV_MASK;

	aअगर4 = snd_soc_component_पढ़ो(component, WM9081_AUDIO_INTERFACE_4);
	aअगर4 &= ~WM9081_LRCLK_RATE_MASK;

	wm9081->fs = params_rate(params);

	अगर (wm9081->tdm_width) अणु
		/* If TDM is set up then that fixes our BCLK. */
		पूर्णांक slots = ((aअगर1 & WM9081_AIFDAC_TDM_MODE_MASK) >>
			     WM9081_AIFDAC_TDM_MODE_SHIFT) + 1;

		wm9081->bclk = wm9081->fs * wm9081->tdm_width * slots;
	पूर्ण अन्यथा अणु
		/* Otherwise work out a BCLK from the sample size */
		wm9081->bclk = 2 * wm9081->fs;

		चयन (params_width(params)) अणु
		हाल 16:
			wm9081->bclk *= 16;
			अवरोध;
		हाल 20:
			wm9081->bclk *= 20;
			aअगर2 |= 0x4;
			अवरोध;
		हाल 24:
			wm9081->bclk *= 24;
			aअगर2 |= 0x8;
			अवरोध;
		हाल 32:
			wm9081->bclk *= 32;
			aअगर2 |= 0xc;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	dev_dbg(component->dev, "Target BCLK is %dHz\n", wm9081->bclk);

	ret = configure_घड़ी(component);
	अगर (ret != 0)
		वापस ret;

	/* Select nearest CLK_SYS_RATE */
	best = 0;
	best_val = असल((wm9081->sysclk_rate / clk_sys_rates[0].ratio)
		       - wm9081->fs);
	क्रम (i = 1; i < ARRAY_SIZE(clk_sys_rates); i++) अणु
		cur_val = असल((wm9081->sysclk_rate /
			       clk_sys_rates[i].ratio) - wm9081->fs);
		अगर (cur_val < best_val) अणु
			best = i;
			best_val = cur_val;
		पूर्ण
	पूर्ण
	dev_dbg(component->dev, "Selected CLK_SYS_RATIO of %d\n",
		clk_sys_rates[best].ratio);
	clk_ctrl2 |= (clk_sys_rates[best].clk_sys_rate
		      << WM9081_CLK_SYS_RATE_SHIFT);

	/* SAMPLE_RATE */
	best = 0;
	best_val = असल(wm9081->fs - sample_rates[0].rate);
	क्रम (i = 1; i < ARRAY_SIZE(sample_rates); i++) अणु
		/* Closest match */
		cur_val = असल(wm9081->fs - sample_rates[i].rate);
		अगर (cur_val < best_val) अणु
			best = i;
			best_val = cur_val;
		पूर्ण
	पूर्ण
	dev_dbg(component->dev, "Selected SAMPLE_RATE of %dHz\n",
		sample_rates[best].rate);
	clk_ctrl2 |= (sample_rates[best].sample_rate
			<< WM9081_SAMPLE_RATE_SHIFT);

	/* BCLK_DIV */
	best = 0;
	best_val = पूर्णांक_उच्च;
	क्रम (i = 0; i < ARRAY_SIZE(bclk_भागs); i++) अणु
		cur_val = ((wm9081->sysclk_rate * 10) / bclk_भागs[i].भाग)
			- wm9081->bclk;
		अगर (cur_val < 0) /* Table is sorted */
			अवरोध;
		अगर (cur_val < best_val) अणु
			best = i;
			best_val = cur_val;
		पूर्ण
	पूर्ण
	wm9081->bclk = (wm9081->sysclk_rate * 10) / bclk_भागs[best].भाग;
	dev_dbg(component->dev, "Selected BCLK_DIV of %d for %dHz BCLK\n",
		bclk_भागs[best].भाग, wm9081->bclk);
	aअगर3 |= bclk_भागs[best].bclk_भाग;

	/* LRCLK is a simple fraction of BCLK */
	dev_dbg(component->dev, "LRCLK_RATE is %d\n", wm9081->bclk / wm9081->fs);
	aअगर4 |= wm9081->bclk / wm9081->fs;

	/* Apply a ReTune Mobile configuration अगर it's in use */
	अगर (wm9081->pdata.num_retune_configs) अणु
		काष्ठा wm9081_pdata *pdata = &wm9081->pdata;
		काष्ठा wm9081_retune_mobile_setting *s;
		पूर्णांक eq1;

		best = 0;
		best_val = असल(pdata->retune_configs[0].rate - wm9081->fs);
		क्रम (i = 0; i < pdata->num_retune_configs; i++) अणु
			cur_val = असल(pdata->retune_configs[i].rate -
				      wm9081->fs);
			अगर (cur_val < best_val) अणु
				best_val = cur_val;
				best = i;
			पूर्ण
		पूर्ण
		s = &pdata->retune_configs[best];

		dev_dbg(component->dev, "ReTune Mobile %s tuned for %dHz\n",
			s->name, s->rate);

		/* If the EQ is enabled then disable it जबतक we ग_लिखो out */
		eq1 = snd_soc_component_पढ़ो(component, WM9081_EQ_1) & WM9081_EQ_ENA;
		अगर (eq1 & WM9081_EQ_ENA)
			snd_soc_component_ग_लिखो(component, WM9081_EQ_1, 0);

		/* Write out the other values */
		क्रम (i = 1; i < ARRAY_SIZE(s->config); i++)
			snd_soc_component_ग_लिखो(component, WM9081_EQ_1 + i, s->config[i]);

		eq1 |= (s->config[0] & ~WM9081_EQ_ENA);
		snd_soc_component_ग_लिखो(component, WM9081_EQ_1, eq1);
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM9081_CLOCK_CONTROL_2, clk_ctrl2);
	snd_soc_component_ग_लिखो(component, WM9081_AUDIO_INTERFACE_2, aअगर2);
	snd_soc_component_ग_लिखो(component, WM9081_AUDIO_INTERFACE_3, aअगर3);
	snd_soc_component_ग_लिखो(component, WM9081_AUDIO_INTERFACE_4, aअगर4);

	वापस 0;
पूर्ण

अटल पूर्णांक wm9081_mute(काष्ठा snd_soc_dai *codec_dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	अचिन्हित पूर्णांक reg;

	reg = snd_soc_component_पढ़ो(component, WM9081_DAC_DIGITAL_2);

	अगर (mute)
		reg |= WM9081_DAC_MUTE;
	अन्यथा
		reg &= ~WM9081_DAC_MUTE;

	snd_soc_component_ग_लिखो(component, WM9081_DAC_DIGITAL_2, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक wm9081_set_sysclk(काष्ठा snd_soc_component *component, पूर्णांक clk_id,
			     पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा wm9081_priv *wm9081 = snd_soc_component_get_drvdata(component);

	चयन (clk_id) अणु
	हाल WM9081_SYSCLK_MCLK:
	हाल WM9081_SYSCLK_FLL_MCLK:
		wm9081->sysclk_source = clk_id;
		wm9081->mclk_rate = freq;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm9081_set_tdm_slot(काष्ठा snd_soc_dai *dai,
	अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm9081_priv *wm9081 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक aअगर1 = snd_soc_component_पढ़ो(component, WM9081_AUDIO_INTERFACE_1);

	aअगर1 &= ~(WM9081_AIFDAC_TDM_SLOT_MASK | WM9081_AIFDAC_TDM_MODE_MASK);

	अगर (slots < 0 || slots > 4)
		वापस -EINVAL;

	wm9081->tdm_width = slot_width;

	अगर (slots == 0)
		slots = 1;

	aअगर1 |= (slots - 1) << WM9081_AIFDAC_TDM_MODE_SHIFT;

	चयन (rx_mask) अणु
	हाल 1:
		अवरोध;
	हाल 2:
		aअगर1 |= 0x10;
		अवरोध;
	हाल 4:
		aअगर1 |= 0x20;
		अवरोध;
	हाल 8:
		aअगर1 |= 0x30;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM9081_AUDIO_INTERFACE_1, aअगर1);

	वापस 0;
पूर्ण

#घोषणा WM9081_RATES SNDRV_PCM_RATE_8000_96000

#घोषणा WM9081_FORMATS \
	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
	 SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm9081_dai_ops = अणु
	.hw_params = wm9081_hw_params,
	.set_fmt = wm9081_set_dai_fmt,
	.mute_stream = wm9081_mute,
	.set_tdm_slot = wm9081_set_tdm_slot,
	.no_capture_mute = 1,
पूर्ण;

/* We report two channels because the CODEC processes a stereo संकेत, even
 * though it is only capable of handling a mono output.
 */
अटल काष्ठा snd_soc_dai_driver wm9081_dai = अणु
	.name = "wm9081-hifi",
	.playback = अणु
		.stream_name = "AIF",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM9081_RATES,
		.क्रमmats = WM9081_FORMATS,
	पूर्ण,
	.ops = &wm9081_dai_ops,
पूर्ण;

अटल पूर्णांक wm9081_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm9081_priv *wm9081 = snd_soc_component_get_drvdata(component);

	/* Enable zero cross by शेष */
	snd_soc_component_update_bits(component, WM9081_ANALOGUE_LINEOUT,
			    WM9081_LINEOUTZC, WM9081_LINEOUTZC);
	snd_soc_component_update_bits(component, WM9081_ANALOGUE_SPEAKER_PGA,
			    WM9081_SPKPGAZC, WM9081_SPKPGAZC);

	अगर (!wm9081->pdata.num_retune_configs) अणु
		dev_dbg(component->dev,
			"No ReTune Mobile data, using normal EQ\n");
		snd_soc_add_component_controls(component, wm9081_eq_controls,
				     ARRAY_SIZE(wm9081_eq_controls));
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm9081 = अणु
	.probe			= wm9081_probe,
	.set_sysclk		= wm9081_set_sysclk,
	.set_bias_level		= wm9081_set_bias_level,
	.controls		= wm9081_snd_controls,
	.num_controls		= ARRAY_SIZE(wm9081_snd_controls),
	.dapm_widमाला_लो		= wm9081_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm9081_dapm_widमाला_लो),
	.dapm_routes		= wm9081_audio_paths,
	.num_dapm_routes	= ARRAY_SIZE(wm9081_audio_paths),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm9081_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,

	.max_रेजिस्टर = WM9081_MAX_REGISTER,
	.reg_शेषs = wm9081_reg,
	.num_reg_शेषs = ARRAY_SIZE(wm9081_reg),
	.अस्थिर_reg = wm9081_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = wm9081_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक wm9081_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm9081_priv *wm9081;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	wm9081 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm9081_priv),
			      GFP_KERNEL);
	अगर (wm9081 == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, wm9081);

	wm9081->regmap = devm_regmap_init_i2c(i2c, &wm9081_regmap);
	अगर (IS_ERR(wm9081->regmap)) अणु
		ret = PTR_ERR(wm9081->regmap);
		dev_err(&i2c->dev, "regmap_init() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(wm9081->regmap, WM9081_SOFTWARE_RESET, &reg);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to read chip ID: %d\n", ret);
		वापस ret;
	पूर्ण
	अगर (reg != 0x9081) अणु
		dev_err(&i2c->dev, "Device is not a WM9081: ID=0x%x\n", reg);
		वापस -EINVAL;
	पूर्ण

	ret = wm9081_reset(wm9081->regmap);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to issue reset\n");
		वापस ret;
	पूर्ण

	अगर (dev_get_platdata(&i2c->dev))
		स_नकल(&wm9081->pdata, dev_get_platdata(&i2c->dev),
		       माप(wm9081->pdata));

	reg = 0;
	अगर (wm9081->pdata.irq_high)
		reg |= WM9081_IRQ_POL;
	अगर (!wm9081->pdata.irq_cmos)
		reg |= WM9081_IRQ_OP_CTRL;
	regmap_update_bits(wm9081->regmap, WM9081_INTERRUPT_CONTROL,
			   WM9081_IRQ_POL | WM9081_IRQ_OP_CTRL, reg);

	regcache_cache_only(wm9081->regmap, true);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_wm9081, &wm9081_dai, 1);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक wm9081_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm9081_i2c_id[] = अणु
	अणु "wm9081", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm9081_i2c_id);

अटल काष्ठा i2c_driver wm9081_i2c_driver = अणु
	.driver = अणु
		.name = "wm9081",
	पूर्ण,
	.probe =    wm9081_i2c_probe,
	.हटाओ =   wm9081_i2c_हटाओ,
	.id_table = wm9081_i2c_id,
पूर्ण;

module_i2c_driver(wm9081_i2c_driver);

MODULE_DESCRIPTION("ASoC WM9081 driver");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
