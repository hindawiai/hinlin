<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm5100.c  --  WM5100 ALSA SoC Audio driver
 *
 * Copyright 2011-2 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/pm.h>
#समावेश <linux/gcd.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/wm5100.h>

#समावेश "wm5100.h"

#घोषणा WM5100_NUM_CORE_SUPPLIES 2
अटल स्थिर अक्षर *wm5100_core_supply_names[WM5100_NUM_CORE_SUPPLIES] = अणु
	"DBVDD1",
	"LDOVDD", /* If DCVDD is supplied बाह्यally specअगरy as LDOVDD */
पूर्ण;

#घोषणा WM5100_AIFS     3
#घोषणा WM5100_SYNC_SRS 3

काष्ठा wm5100_fll अणु
	पूर्णांक fref;
	पूर्णांक fout;
	पूर्णांक src;
	काष्ठा completion lock;
पूर्ण;

/* codec निजी data */
काष्ठा wm5100_priv अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा snd_soc_component *component;

	काष्ठा regulator_bulk_data core_supplies[WM5100_NUM_CORE_SUPPLIES];

	पूर्णांक rev;

	पूर्णांक sysclk;
	पूर्णांक asyncclk;

	bool aअगर_async[WM5100_AIFS];
	bool aअगर_symmetric[WM5100_AIFS];
	पूर्णांक sr_ref[WM5100_SYNC_SRS];

	bool out_ena[2];

	काष्ठा snd_soc_jack *jack;
	bool jack_detecting;
	bool jack_mic;
	पूर्णांक jack_mode;
	पूर्णांक jack_flips;

	काष्ठा wm5100_fll fll[2];

	काष्ठा wm5100_pdata pdata;

#अगर_घोषित CONFIG_GPIOLIB
	काष्ठा gpio_chip gpio_chip;
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक wm5100_sr_code[] = अणु
	0,
	12000,
	24000,
	48000,
	96000,
	192000,
	384000,
	768000,
	0,
	11025,
	22050,
	44100,
	88200,
	176400,
	352800,
	705600,
	4000,
	8000,
	16000,
	32000,
	64000,
	128000,
	256000,
	512000,
पूर्ण;

अटल पूर्णांक wm5100_sr_regs[WM5100_SYNC_SRS] = अणु
	WM5100_CLOCKING_4,
	WM5100_CLOCKING_5,
	WM5100_CLOCKING_6,
पूर्ण;

अटल पूर्णांक wm5100_alloc_sr(काष्ठा snd_soc_component *component, पूर्णांक rate)
अणु
	काष्ठा wm5100_priv *wm5100 = snd_soc_component_get_drvdata(component);
	पूर्णांक sr_code, sr_मुक्त, i;

	क्रम (i = 0; i < ARRAY_SIZE(wm5100_sr_code); i++)
		अगर (wm5100_sr_code[i] == rate)
			अवरोध;
	अगर (i == ARRAY_SIZE(wm5100_sr_code)) अणु
		dev_err(component->dev, "Unsupported sample rate: %dHz\n", rate);
		वापस -EINVAL;
	पूर्ण
	sr_code = i;

	अगर ((wm5100->sysclk % rate) == 0) अणु
		/* Is this rate alपढ़ोy in use? */
		sr_मुक्त = -1;
		क्रम (i = 0; i < ARRAY_SIZE(wm5100_sr_regs); i++) अणु
			अगर (!wm5100->sr_ref[i] && sr_मुक्त == -1) अणु
				sr_मुक्त = i;
				जारी;
			पूर्ण
			अगर ((snd_soc_component_पढ़ो(component, wm5100_sr_regs[i]) &
			     WM5100_SAMPLE_RATE_1_MASK) == sr_code)
				अवरोध;
		पूर्ण

		अगर (i < ARRAY_SIZE(wm5100_sr_regs)) अणु
			wm5100->sr_ref[i]++;
			dev_dbg(component->dev, "SR %dHz, slot %d, ref %d\n",
				rate, i, wm5100->sr_ref[i]);
			वापस i;
		पूर्ण

		अगर (sr_मुक्त == -1) अणु
			dev_err(component->dev, "All SR slots already in use\n");
			वापस -EBUSY;
		पूर्ण

		dev_dbg(component->dev, "Allocating SR slot %d for %dHz\n",
			sr_मुक्त, rate);
		wm5100->sr_ref[sr_मुक्त]++;
		snd_soc_component_update_bits(component, wm5100_sr_regs[sr_मुक्त],
				    WM5100_SAMPLE_RATE_1_MASK,
				    sr_code);

		वापस sr_मुक्त;

	पूर्ण अन्यथा अणु
		dev_err(component->dev,
			"SR %dHz incompatible with %dHz SYSCLK and %dHz ASYNCCLK\n",
			rate, wm5100->sysclk, wm5100->asyncclk);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम wm5100_मुक्त_sr(काष्ठा snd_soc_component *component, पूर्णांक rate)
अणु
	काष्ठा wm5100_priv *wm5100 = snd_soc_component_get_drvdata(component);
	पूर्णांक i, sr_code;

	क्रम (i = 0; i < ARRAY_SIZE(wm5100_sr_code); i++)
		अगर (wm5100_sr_code[i] == rate)
			अवरोध;
	अगर (i == ARRAY_SIZE(wm5100_sr_code)) अणु
		dev_err(component->dev, "Unsupported sample rate: %dHz\n", rate);
		वापस;
	पूर्ण
	sr_code = wm5100_sr_code[i];

	क्रम (i = 0; i < ARRAY_SIZE(wm5100_sr_regs); i++) अणु
		अगर (!wm5100->sr_ref[i])
			जारी;

		अगर ((snd_soc_component_पढ़ो(component, wm5100_sr_regs[i]) &
		     WM5100_SAMPLE_RATE_1_MASK) == sr_code)
			अवरोध;
	पूर्ण
	अगर (i < ARRAY_SIZE(wm5100_sr_regs)) अणु
		wm5100->sr_ref[i]--;
		dev_dbg(component->dev, "Dereference SR %dHz, count now %d\n",
			rate, wm5100->sr_ref[i]);
	पूर्ण अन्यथा अणु
		dev_warn(component->dev, "Freeing unreferenced sample rate %dHz\n",
			 rate);
	पूर्ण
पूर्ण

अटल पूर्णांक wm5100_reset(काष्ठा wm5100_priv *wm5100)
अणु
	अगर (wm5100->pdata.reset) अणु
		gpio_set_value_cansleep(wm5100->pdata.reset, 0);
		gpio_set_value_cansleep(wm5100->pdata.reset, 1);

		वापस 0;
	पूर्ण अन्यथा अणु
		वापस regmap_ग_लिखो(wm5100->regmap, WM5100_SOFTWARE_RESET, 0);
	पूर्ण
पूर्ण

अटल DECLARE_TLV_DB_SCALE(in_tlv, -6300, 100, 0);
अटल DECLARE_TLV_DB_SCALE(eq_tlv, -1200, 100, 0);
अटल DECLARE_TLV_DB_SCALE(mixer_tlv, -3200, 100, 0);
अटल DECLARE_TLV_DB_SCALE(out_tlv, -6400, 100, 0);
अटल DECLARE_TLV_DB_SCALE(digital_tlv, -6400, 50, 0);

अटल स्थिर अक्षर *wm5100_mixer_texts[] = अणु
	"None",
	"Tone Generator 1",
	"Tone Generator 2",
	"AEC loopback",
	"IN1L",
	"IN1R",
	"IN2L",
	"IN2R",
	"IN3L",
	"IN3R",
	"IN4L",
	"IN4R",
	"AIF1RX1",
	"AIF1RX2",
	"AIF1RX3",
	"AIF1RX4",
	"AIF1RX5",
	"AIF1RX6",
	"AIF1RX7",
	"AIF1RX8",
	"AIF2RX1",
	"AIF2RX2",
	"AIF3RX1",
	"AIF3RX2",
	"EQ1",
	"EQ2",
	"EQ3",
	"EQ4",
	"DRC1L",
	"DRC1R",
	"LHPF1",
	"LHPF2",
	"LHPF3",
	"LHPF4",
	"DSP1.1",
	"DSP1.2",
	"DSP1.3",
	"DSP1.4",
	"DSP1.5",
	"DSP1.6",
	"DSP2.1",
	"DSP2.2",
	"DSP2.3",
	"DSP2.4",
	"DSP2.5",
	"DSP2.6",
	"DSP3.1",
	"DSP3.2",
	"DSP3.3",
	"DSP3.4",
	"DSP3.5",
	"DSP3.6",
	"ASRC1L",
	"ASRC1R",
	"ASRC2L",
	"ASRC2R",
	"ISRC1INT1",
	"ISRC1INT2",
	"ISRC1INT3",
	"ISRC1INT4",
	"ISRC2INT1",
	"ISRC2INT2",
	"ISRC2INT3",
	"ISRC2INT4",
	"ISRC1DEC1",
	"ISRC1DEC2",
	"ISRC1DEC3",
	"ISRC1DEC4",
	"ISRC2DEC1",
	"ISRC2DEC2",
	"ISRC2DEC3",
	"ISRC2DEC4",
पूर्ण;

अटल पूर्णांक wm5100_mixer_values[] = अणु
	0x00,
	0x04,   /* Tone */
	0x05,
	0x08,   /* AEC */
	0x10,   /* Input */
	0x11,
	0x12,
	0x13,
	0x14,
	0x15,
	0x16,
	0x17,
	0x20,   /* AIF */
	0x21,
	0x22,
	0x23,
	0x24,
	0x25,
	0x26,
	0x27,
	0x28,
	0x29,
	0x30,   /* AIF3 - check */
	0x31,
	0x50,   /* EQ */
	0x51,
	0x52,
	0x53,
	0x54,
	0x58,   /* DRC */
	0x59,
	0x60,   /* LHPF1 */
	0x61,   /* LHPF2 */
	0x62,   /* LHPF3 */
	0x63,   /* LHPF4 */
	0x68,   /* DSP1 */
	0x69,
	0x6a,
	0x6b,
	0x6c,
	0x6d,
	0x70,   /* DSP2 */
	0x71,
	0x72,
	0x73,
	0x74,
	0x75,
	0x78,   /* DSP3 */
	0x79,
	0x7a,
	0x7b,
	0x7c,
	0x7d,
	0x90,   /* ASRC1 */
	0x91,
	0x92,   /* ASRC2 */
	0x93,
	0xa0,   /* ISRC1DEC1 */
	0xa1,
	0xa2,
	0xa3,
	0xa4,   /* ISRC1INT1 */
	0xa5,
	0xa6,
	0xa7,
	0xa8,   /* ISRC2DEC1 */
	0xa9,
	0xaa,
	0xab,
	0xac,   /* ISRC2INT1 */
	0xad,
	0xae,
	0xaf,
पूर्ण;

#घोषणा WM5100_MIXER_CONTROLS(name, base) \
	SOC_SINGLE_TLV(name " Input 1 Volume", base + 1 , \
		       WM5100_MIXER_VOL_SHIFT, 80, 0, mixer_tlv), \
	SOC_SINGLE_TLV(name " Input 2 Volume", base + 3 , \
		       WM5100_MIXER_VOL_SHIFT, 80, 0, mixer_tlv), \
	SOC_SINGLE_TLV(name " Input 3 Volume", base + 5 , \
		       WM5100_MIXER_VOL_SHIFT, 80, 0, mixer_tlv), \
	SOC_SINGLE_TLV(name " Input 4 Volume", base + 7 , \
		       WM5100_MIXER_VOL_SHIFT, 80, 0, mixer_tlv)

#घोषणा WM5100_MUX_ENUM_DECL(name, reg) \
	SOC_VALUE_ENUM_SINGLE_DECL(name, reg, 0, 0xff, 			\
				   wm5100_mixer_texts, wm5100_mixer_values)

#घोषणा WM5100_MUX_CTL_DECL(name) \
	स्थिर काष्ठा snd_kcontrol_new name##_mux =	\
		SOC_DAPM_ENUM("Route", name##_क्रमागत)

#घोषणा WM5100_MIXER_ENUMS(name, base_reg) \
	अटल WM5100_MUX_ENUM_DECL(name##_in1_क्रमागत, base_reg);	     \
	अटल WM5100_MUX_ENUM_DECL(name##_in2_क्रमागत, base_reg + 2);  \
	अटल WM5100_MUX_ENUM_DECL(name##_in3_क्रमागत, base_reg + 4);  \
	अटल WM5100_MUX_ENUM_DECL(name##_in4_क्रमागत, base_reg + 6);  \
	अटल WM5100_MUX_CTL_DECL(name##_in1); \
	अटल WM5100_MUX_CTL_DECL(name##_in2); \
	अटल WM5100_MUX_CTL_DECL(name##_in3); \
	अटल WM5100_MUX_CTL_DECL(name##_in4) 

WM5100_MIXER_ENUMS(HPOUT1L, WM5100_OUT1LMIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(HPOUT1R, WM5100_OUT1RMIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(HPOUT2L, WM5100_OUT2LMIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(HPOUT2R, WM5100_OUT2RMIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(HPOUT3L, WM5100_OUT3LMIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(HPOUT3R, WM5100_OUT3RMIX_INPUT_1_SOURCE);

WM5100_MIXER_ENUMS(SPKOUTL, WM5100_OUT4LMIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(SPKOUTR, WM5100_OUT4RMIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(SPKDAT1L, WM5100_OUT5LMIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(SPKDAT1R, WM5100_OUT5RMIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(SPKDAT2L, WM5100_OUT6LMIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(SPKDAT2R, WM5100_OUT6RMIX_INPUT_1_SOURCE);

WM5100_MIXER_ENUMS(PWM1, WM5100_PWM1MIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(PWM2, WM5100_PWM1MIX_INPUT_1_SOURCE);

WM5100_MIXER_ENUMS(AIF1TX1, WM5100_AIF1TX1MIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(AIF1TX2, WM5100_AIF1TX2MIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(AIF1TX3, WM5100_AIF1TX3MIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(AIF1TX4, WM5100_AIF1TX4MIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(AIF1TX5, WM5100_AIF1TX5MIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(AIF1TX6, WM5100_AIF1TX6MIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(AIF1TX7, WM5100_AIF1TX7MIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(AIF1TX8, WM5100_AIF1TX8MIX_INPUT_1_SOURCE);

WM5100_MIXER_ENUMS(AIF2TX1, WM5100_AIF2TX1MIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(AIF2TX2, WM5100_AIF2TX2MIX_INPUT_1_SOURCE);

WM5100_MIXER_ENUMS(AIF3TX1, WM5100_AIF1TX1MIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(AIF3TX2, WM5100_AIF1TX2MIX_INPUT_1_SOURCE);

WM5100_MIXER_ENUMS(EQ1, WM5100_EQ1MIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(EQ2, WM5100_EQ2MIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(EQ3, WM5100_EQ3MIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(EQ4, WM5100_EQ4MIX_INPUT_1_SOURCE);

WM5100_MIXER_ENUMS(DRC1L, WM5100_DRC1LMIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(DRC1R, WM5100_DRC1RMIX_INPUT_1_SOURCE);

WM5100_MIXER_ENUMS(LHPF1, WM5100_HPLP1MIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(LHPF2, WM5100_HPLP2MIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(LHPF3, WM5100_HPLP3MIX_INPUT_1_SOURCE);
WM5100_MIXER_ENUMS(LHPF4, WM5100_HPLP4MIX_INPUT_1_SOURCE);

#घोषणा WM5100_MUX(name, ctrl) \
	SND_SOC_DAPM_MUX(name, SND_SOC_NOPM, 0, 0, ctrl)

#घोषणा WM5100_MIXER_WIDGETS(name, name_str)	\
	WM5100_MUX(name_str " Input 1", &name##_in1_mux), \
	WM5100_MUX(name_str " Input 2", &name##_in2_mux), \
	WM5100_MUX(name_str " Input 3", &name##_in3_mux), \
	WM5100_MUX(name_str " Input 4", &name##_in4_mux), \
	SND_SOC_DAPM_MIXER(name_str " Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0)

#घोषणा WM5100_MIXER_INPUT_ROUTES(name)	\
	अणु name, "Tone Generator 1", "Tone Generator 1" पूर्ण, \
        अणु name, "Tone Generator 2", "Tone Generator 2" पूर्ण, \
        अणु name, "IN1L", "IN1L PGA" पूर्ण, \
        अणु name, "IN1R", "IN1R PGA" पूर्ण, \
        अणु name, "IN2L", "IN2L PGA" पूर्ण, \
        अणु name, "IN2R", "IN2R PGA" पूर्ण, \
        अणु name, "IN3L", "IN3L PGA" पूर्ण, \
        अणु name, "IN3R", "IN3R PGA" पूर्ण, \
        अणु name, "IN4L", "IN4L PGA" पूर्ण, \
        अणु name, "IN4R", "IN4R PGA" पूर्ण, \
        अणु name, "AIF1RX1", "AIF1RX1" पूर्ण, \
        अणु name, "AIF1RX2", "AIF1RX2" पूर्ण, \
        अणु name, "AIF1RX3", "AIF1RX3" पूर्ण, \
        अणु name, "AIF1RX4", "AIF1RX4" पूर्ण, \
        अणु name, "AIF1RX5", "AIF1RX5" पूर्ण, \
        अणु name, "AIF1RX6", "AIF1RX6" पूर्ण, \
        अणु name, "AIF1RX7", "AIF1RX7" पूर्ण, \
        अणु name, "AIF1RX8", "AIF1RX8" पूर्ण, \
        अणु name, "AIF2RX1", "AIF2RX1" पूर्ण, \
        अणु name, "AIF2RX2", "AIF2RX2" पूर्ण, \
        अणु name, "AIF3RX1", "AIF3RX1" पूर्ण, \
        अणु name, "AIF3RX2", "AIF3RX2" पूर्ण, \
        अणु name, "EQ1", "EQ1" पूर्ण, \
        अणु name, "EQ2", "EQ2" पूर्ण, \
        अणु name, "EQ3", "EQ3" पूर्ण, \
        अणु name, "EQ4", "EQ4" पूर्ण, \
        अणु name, "DRC1L", "DRC1L" पूर्ण, \
        अणु name, "DRC1R", "DRC1R" पूर्ण, \
        अणु name, "LHPF1", "LHPF1" पूर्ण, \
        अणु name, "LHPF2", "LHPF2" पूर्ण, \
        अणु name, "LHPF3", "LHPF3" पूर्ण, \
        अणु name, "LHPF4", "LHPF4" पूर्ण

#घोषणा WM5100_MIXER_ROUTES(widget, name) \
	अणु widget, शून्य, name " Mixer" पूर्ण,         \
	अणु name " Mixer", शून्य, name " Input 1" पूर्ण, \
	अणु name " Mixer", शून्य, name " Input 2" पूर्ण, \
	अणु name " Mixer", शून्य, name " Input 3" पूर्ण, \
	अणु name " Mixer", शून्य, name " Input 4" पूर्ण, \
	WM5100_MIXER_INPUT_ROUTES(name " Input 1"), \
	WM5100_MIXER_INPUT_ROUTES(name " Input 2"), \
	WM5100_MIXER_INPUT_ROUTES(name " Input 3"), \
	WM5100_MIXER_INPUT_ROUTES(name " Input 4")

अटल स्थिर अक्षर *wm5100_lhpf_mode_text[] = अणु
	"Low-pass", "High-pass"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(wm5100_lhpf1_mode,
			    WM5100_HPLPF1_1, WM5100_LHPF1_MODE_SHIFT,
			    wm5100_lhpf_mode_text);

अटल SOC_ENUM_SINGLE_DECL(wm5100_lhpf2_mode,
			    WM5100_HPLPF2_1, WM5100_LHPF2_MODE_SHIFT,
			    wm5100_lhpf_mode_text);

अटल SOC_ENUM_SINGLE_DECL(wm5100_lhpf3_mode,
			    WM5100_HPLPF3_1, WM5100_LHPF3_MODE_SHIFT,
			    wm5100_lhpf_mode_text);

अटल SOC_ENUM_SINGLE_DECL(wm5100_lhpf4_mode,
			    WM5100_HPLPF4_1, WM5100_LHPF4_MODE_SHIFT,
			    wm5100_lhpf_mode_text);

अटल स्थिर काष्ठा snd_kcontrol_new wm5100_snd_controls[] = अणु
SOC_SINGLE("IN1 High Performance Switch", WM5100_IN1L_CONTROL,
	   WM5100_IN1_OSR_SHIFT, 1, 0),
SOC_SINGLE("IN2 High Performance Switch", WM5100_IN2L_CONTROL,
	   WM5100_IN2_OSR_SHIFT, 1, 0),
SOC_SINGLE("IN3 High Performance Switch", WM5100_IN3L_CONTROL,
	   WM5100_IN3_OSR_SHIFT, 1, 0),
SOC_SINGLE("IN4 High Performance Switch", WM5100_IN4L_CONTROL,
	   WM5100_IN4_OSR_SHIFT, 1, 0),

/* Only applicable क्रम analogue inमाला_दो */
SOC_DOUBLE_R_TLV("IN1 Volume", WM5100_IN1L_CONTROL, WM5100_IN1R_CONTROL,
		 WM5100_IN1L_PGA_VOL_SHIFT, 94, 0, in_tlv),
SOC_DOUBLE_R_TLV("IN2 Volume", WM5100_IN2L_CONTROL, WM5100_IN2R_CONTROL,
		 WM5100_IN2L_PGA_VOL_SHIFT, 94, 0, in_tlv),
SOC_DOUBLE_R_TLV("IN3 Volume", WM5100_IN3L_CONTROL, WM5100_IN3R_CONTROL,
		 WM5100_IN3L_PGA_VOL_SHIFT, 94, 0, in_tlv),
SOC_DOUBLE_R_TLV("IN4 Volume", WM5100_IN4L_CONTROL, WM5100_IN4R_CONTROL,
		 WM5100_IN4L_PGA_VOL_SHIFT, 94, 0, in_tlv),

SOC_DOUBLE_R_TLV("IN1 Digital Volume", WM5100_ADC_DIGITAL_VOLUME_1L,
		 WM5100_ADC_DIGITAL_VOLUME_1R, WM5100_IN1L_VOL_SHIFT, 191,
		 0, digital_tlv),
SOC_DOUBLE_R_TLV("IN2 Digital Volume", WM5100_ADC_DIGITAL_VOLUME_2L,
		 WM5100_ADC_DIGITAL_VOLUME_2R, WM5100_IN2L_VOL_SHIFT, 191,
		 0, digital_tlv),
SOC_DOUBLE_R_TLV("IN3 Digital Volume", WM5100_ADC_DIGITAL_VOLUME_3L,
		 WM5100_ADC_DIGITAL_VOLUME_3R, WM5100_IN3L_VOL_SHIFT, 191,
		 0, digital_tlv),
SOC_DOUBLE_R_TLV("IN4 Digital Volume", WM5100_ADC_DIGITAL_VOLUME_4L,
		 WM5100_ADC_DIGITAL_VOLUME_4R, WM5100_IN4L_VOL_SHIFT, 191,
		 0, digital_tlv),

SOC_DOUBLE_R("IN1 Switch", WM5100_ADC_DIGITAL_VOLUME_1L,
	     WM5100_ADC_DIGITAL_VOLUME_1R, WM5100_IN1L_MUTE_SHIFT, 1, 1),
SOC_DOUBLE_R("IN2 Switch", WM5100_ADC_DIGITAL_VOLUME_2L,
	     WM5100_ADC_DIGITAL_VOLUME_2R, WM5100_IN2L_MUTE_SHIFT, 1, 1),
SOC_DOUBLE_R("IN3 Switch", WM5100_ADC_DIGITAL_VOLUME_3L,
	     WM5100_ADC_DIGITAL_VOLUME_3R, WM5100_IN3L_MUTE_SHIFT, 1, 1),
SOC_DOUBLE_R("IN4 Switch", WM5100_ADC_DIGITAL_VOLUME_4L,
	     WM5100_ADC_DIGITAL_VOLUME_4R, WM5100_IN4L_MUTE_SHIFT, 1, 1),

SND_SOC_BYTES_MASK("EQ1 Coefficients", WM5100_EQ1_1, 20, WM5100_EQ1_ENA),
SND_SOC_BYTES_MASK("EQ2 Coefficients", WM5100_EQ2_1, 20, WM5100_EQ2_ENA),
SND_SOC_BYTES_MASK("EQ3 Coefficients", WM5100_EQ3_1, 20, WM5100_EQ3_ENA),
SND_SOC_BYTES_MASK("EQ4 Coefficients", WM5100_EQ4_1, 20, WM5100_EQ4_ENA),

SND_SOC_BYTES_MASK("DRC Coefficients", WM5100_DRC1_CTRL1, 5,
		   WM5100_DRCL_ENA | WM5100_DRCR_ENA),

SND_SOC_BYTES("LHPF1 Coefficients", WM5100_HPLPF1_2, 1),
SND_SOC_BYTES("LHPF2 Coefficients", WM5100_HPLPF2_2, 1),
SND_SOC_BYTES("LHPF3 Coefficients", WM5100_HPLPF3_2, 1),
SND_SOC_BYTES("LHPF4 Coefficients", WM5100_HPLPF4_2, 1),

SOC_SINGLE("HPOUT1 High Performance Switch", WM5100_OUT_VOLUME_1L,
	   WM5100_OUT1_OSR_SHIFT, 1, 0),
SOC_SINGLE("HPOUT2 High Performance Switch", WM5100_OUT_VOLUME_2L,
	   WM5100_OUT2_OSR_SHIFT, 1, 0),
SOC_SINGLE("HPOUT3 High Performance Switch", WM5100_OUT_VOLUME_3L,
	   WM5100_OUT3_OSR_SHIFT, 1, 0),
SOC_SINGLE("SPKOUT High Performance Switch", WM5100_OUT_VOLUME_4L,
	   WM5100_OUT4_OSR_SHIFT, 1, 0),
SOC_SINGLE("SPKDAT1 High Performance Switch", WM5100_DAC_VOLUME_LIMIT_5L,
	   WM5100_OUT5_OSR_SHIFT, 1, 0),
SOC_SINGLE("SPKDAT2 High Performance Switch", WM5100_DAC_VOLUME_LIMIT_6L,
	   WM5100_OUT6_OSR_SHIFT, 1, 0),

SOC_DOUBLE_R_TLV("HPOUT1 Digital Volume", WM5100_DAC_DIGITAL_VOLUME_1L,
		 WM5100_DAC_DIGITAL_VOLUME_1R, WM5100_OUT1L_VOL_SHIFT, 159, 0,
		 digital_tlv),
SOC_DOUBLE_R_TLV("HPOUT2 Digital Volume", WM5100_DAC_DIGITAL_VOLUME_2L,
		 WM5100_DAC_DIGITAL_VOLUME_2R, WM5100_OUT2L_VOL_SHIFT, 159, 0,
		 digital_tlv),
SOC_DOUBLE_R_TLV("HPOUT3 Digital Volume", WM5100_DAC_DIGITAL_VOLUME_3L,
		 WM5100_DAC_DIGITAL_VOLUME_3R, WM5100_OUT3L_VOL_SHIFT, 159, 0,
		 digital_tlv),
SOC_DOUBLE_R_TLV("SPKOUT Digital Volume", WM5100_DAC_DIGITAL_VOLUME_4L,
		 WM5100_DAC_DIGITAL_VOLUME_4R, WM5100_OUT4L_VOL_SHIFT, 159, 0,
		 digital_tlv),
SOC_DOUBLE_R_TLV("SPKDAT1 Digital Volume", WM5100_DAC_DIGITAL_VOLUME_5L,
		 WM5100_DAC_DIGITAL_VOLUME_5R, WM5100_OUT5L_VOL_SHIFT, 159, 0,
		 digital_tlv),
SOC_DOUBLE_R_TLV("SPKDAT2 Digital Volume", WM5100_DAC_DIGITAL_VOLUME_6L,
		 WM5100_DAC_DIGITAL_VOLUME_6R, WM5100_OUT6L_VOL_SHIFT, 159, 0,
		 digital_tlv),

SOC_DOUBLE_R("HPOUT1 Digital Switch", WM5100_DAC_DIGITAL_VOLUME_1L,
	     WM5100_DAC_DIGITAL_VOLUME_1R, WM5100_OUT1L_MUTE_SHIFT, 1, 1),
SOC_DOUBLE_R("HPOUT2 Digital Switch", WM5100_DAC_DIGITAL_VOLUME_2L,
	     WM5100_DAC_DIGITAL_VOLUME_2R, WM5100_OUT2L_MUTE_SHIFT, 1, 1),
SOC_DOUBLE_R("HPOUT3 Digital Switch", WM5100_DAC_DIGITAL_VOLUME_3L,
	     WM5100_DAC_DIGITAL_VOLUME_3R, WM5100_OUT3L_MUTE_SHIFT, 1, 1),
SOC_DOUBLE_R("SPKOUT Digital Switch", WM5100_DAC_DIGITAL_VOLUME_4L,
	     WM5100_DAC_DIGITAL_VOLUME_4R, WM5100_OUT4L_MUTE_SHIFT, 1, 1),
SOC_DOUBLE_R("SPKDAT1 Digital Switch", WM5100_DAC_DIGITAL_VOLUME_5L,
	     WM5100_DAC_DIGITAL_VOLUME_5R, WM5100_OUT5L_MUTE_SHIFT, 1, 1),
SOC_DOUBLE_R("SPKDAT2 Digital Switch", WM5100_DAC_DIGITAL_VOLUME_6L,
	     WM5100_DAC_DIGITAL_VOLUME_6R, WM5100_OUT6L_MUTE_SHIFT, 1, 1),

/* FIXME: Only valid from -12dB to 0dB (52-64) */
SOC_DOUBLE_R_TLV("HPOUT1 Volume", WM5100_OUT_VOLUME_1L, WM5100_OUT_VOLUME_1R,
		 WM5100_OUT1L_PGA_VOL_SHIFT, 64, 0, out_tlv),
SOC_DOUBLE_R_TLV("HPOUT2 Volume", WM5100_OUT_VOLUME_2L, WM5100_OUT_VOLUME_2R,
		 WM5100_OUT2L_PGA_VOL_SHIFT, 64, 0, out_tlv),
SOC_DOUBLE_R_TLV("HPOUT3 Volume", WM5100_OUT_VOLUME_3L, WM5100_OUT_VOLUME_3R,
		 WM5100_OUT2L_PGA_VOL_SHIFT, 64, 0, out_tlv),

SOC_DOUBLE("SPKDAT1 Switch", WM5100_PDM_SPK1_CTRL_1, WM5100_SPK1L_MUTE_SHIFT,
	   WM5100_SPK1R_MUTE_SHIFT, 1, 1),
SOC_DOUBLE("SPKDAT2 Switch", WM5100_PDM_SPK2_CTRL_1, WM5100_SPK2L_MUTE_SHIFT,
	   WM5100_SPK2R_MUTE_SHIFT, 1, 1),

SOC_SINGLE_TLV("EQ1 Band 1 Volume", WM5100_EQ1_1, WM5100_EQ1_B1_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ1 Band 2 Volume", WM5100_EQ1_1, WM5100_EQ1_B2_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ1 Band 3 Volume", WM5100_EQ1_1, WM5100_EQ1_B3_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ1 Band 4 Volume", WM5100_EQ1_2, WM5100_EQ1_B4_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ1 Band 5 Volume", WM5100_EQ1_2, WM5100_EQ1_B5_GAIN_SHIFT,
	       24, 0, eq_tlv),

SOC_SINGLE_TLV("EQ2 Band 1 Volume", WM5100_EQ2_1, WM5100_EQ2_B1_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ2 Band 2 Volume", WM5100_EQ2_1, WM5100_EQ2_B2_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ2 Band 3 Volume", WM5100_EQ2_1, WM5100_EQ2_B3_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ2 Band 4 Volume", WM5100_EQ2_2, WM5100_EQ2_B4_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ2 Band 5 Volume", WM5100_EQ2_2, WM5100_EQ2_B5_GAIN_SHIFT,
	       24, 0, eq_tlv),

SOC_SINGLE_TLV("EQ3 Band 1 Volume", WM5100_EQ1_1, WM5100_EQ3_B1_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ3 Band 2 Volume", WM5100_EQ3_1, WM5100_EQ3_B2_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ3 Band 3 Volume", WM5100_EQ3_1, WM5100_EQ3_B3_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ3 Band 4 Volume", WM5100_EQ3_2, WM5100_EQ3_B4_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ3 Band 5 Volume", WM5100_EQ3_2, WM5100_EQ3_B5_GAIN_SHIFT,
	       24, 0, eq_tlv),

SOC_SINGLE_TLV("EQ4 Band 1 Volume", WM5100_EQ4_1, WM5100_EQ4_B1_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ4 Band 2 Volume", WM5100_EQ4_1, WM5100_EQ4_B2_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ4 Band 3 Volume", WM5100_EQ4_1, WM5100_EQ4_B3_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ4 Band 4 Volume", WM5100_EQ4_2, WM5100_EQ4_B4_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ4 Band 5 Volume", WM5100_EQ4_2, WM5100_EQ4_B5_GAIN_SHIFT,
	       24, 0, eq_tlv),

SOC_ENUM("LHPF1 Mode", wm5100_lhpf1_mode),
SOC_ENUM("LHPF2 Mode", wm5100_lhpf2_mode),
SOC_ENUM("LHPF3 Mode", wm5100_lhpf3_mode),
SOC_ENUM("LHPF4 Mode", wm5100_lhpf4_mode),

WM5100_MIXER_CONTROLS("HPOUT1L", WM5100_OUT1LMIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("HPOUT1R", WM5100_OUT1RMIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("HPOUT2L", WM5100_OUT2LMIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("HPOUT2R", WM5100_OUT2RMIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("HPOUT3L", WM5100_OUT3LMIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("HPOUT3R", WM5100_OUT3RMIX_INPUT_1_SOURCE),

WM5100_MIXER_CONTROLS("SPKOUTL", WM5100_OUT4LMIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("SPKOUTR", WM5100_OUT4RMIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("SPKDAT1L", WM5100_OUT5LMIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("SPKDAT1R", WM5100_OUT5RMIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("SPKDAT2L", WM5100_OUT6LMIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("SPKDAT2R", WM5100_OUT6RMIX_INPUT_1_SOURCE),

WM5100_MIXER_CONTROLS("PWM1", WM5100_PWM1MIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("PWM2", WM5100_PWM2MIX_INPUT_1_SOURCE),

WM5100_MIXER_CONTROLS("AIF1TX1", WM5100_AIF1TX1MIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("AIF1TX2", WM5100_AIF1TX2MIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("AIF1TX3", WM5100_AIF1TX3MIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("AIF1TX4", WM5100_AIF1TX4MIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("AIF1TX5", WM5100_AIF1TX5MIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("AIF1TX6", WM5100_AIF1TX6MIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("AIF1TX7", WM5100_AIF1TX7MIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("AIF1TX8", WM5100_AIF1TX8MIX_INPUT_1_SOURCE),

WM5100_MIXER_CONTROLS("AIF2TX1", WM5100_AIF2TX1MIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("AIF2TX2", WM5100_AIF2TX2MIX_INPUT_1_SOURCE),

WM5100_MIXER_CONTROLS("AIF3TX1", WM5100_AIF3TX1MIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("AIF3TX2", WM5100_AIF3TX2MIX_INPUT_1_SOURCE),

WM5100_MIXER_CONTROLS("EQ1", WM5100_EQ1MIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("EQ2", WM5100_EQ2MIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("EQ3", WM5100_EQ3MIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("EQ4", WM5100_EQ4MIX_INPUT_1_SOURCE),

WM5100_MIXER_CONTROLS("DRC1L", WM5100_DRC1LMIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("DRC1R", WM5100_DRC1RMIX_INPUT_1_SOURCE),
SND_SOC_BYTES_MASK("DRC", WM5100_DRC1_CTRL1, 5,
		   WM5100_DRCL_ENA | WM5100_DRCR_ENA),

WM5100_MIXER_CONTROLS("LHPF1", WM5100_HPLP1MIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("LHPF2", WM5100_HPLP2MIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("LHPF3", WM5100_HPLP3MIX_INPUT_1_SOURCE),
WM5100_MIXER_CONTROLS("LHPF4", WM5100_HPLP4MIX_INPUT_1_SOURCE),
पूर्ण;

अटल व्योम wm5100_seq_notअगरier(काष्ठा snd_soc_component *component,
				क्रमागत snd_soc_dapm_type event, पूर्णांक subseq)
अणु
	काष्ठा wm5100_priv *wm5100 = snd_soc_component_get_drvdata(component);
	u16 val, expect, i;

	/* Wait क्रम the outमाला_दो to flag themselves as enabled */
	अगर (wm5100->out_ena[0]) अणु
		expect = snd_soc_component_पढ़ो(component, WM5100_CHANNEL_ENABLES_1);
		क्रम (i = 0; i < 200; i++) अणु
			val = snd_soc_component_पढ़ो(component, WM5100_OUTPUT_STATUS_1);
			अगर (val == expect) अणु
				wm5100->out_ena[0] = false;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == 200) अणु
			dev_err(component->dev, "Timeout waiting for OUTPUT1 %x\n",
				expect);
		पूर्ण
	पूर्ण

	अगर (wm5100->out_ena[1]) अणु
		expect = snd_soc_component_पढ़ो(component, WM5100_OUTPUT_ENABLES_2);
		क्रम (i = 0; i < 200; i++) अणु
			val = snd_soc_component_पढ़ो(component, WM5100_OUTPUT_STATUS_2);
			अगर (val == expect) अणु
				wm5100->out_ena[1] = false;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == 200) अणु
			dev_err(component->dev, "Timeout waiting for OUTPUT2 %x\n",
				expect);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक wm5100_out_ev(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *kcontrol,
			 पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm5100_priv *wm5100 = snd_soc_component_get_drvdata(component);

	चयन (w->reg) अणु
	हाल WM5100_CHANNEL_ENABLES_1:
		wm5100->out_ena[0] = true;
		अवरोध;
	हाल WM5100_OUTPUT_ENABLES_2:
		wm5100->out_ena[0] = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wm5100_log_status3(काष्ठा wm5100_priv *wm5100, पूर्णांक val)
अणु
	अगर (val & WM5100_SPK_SHUTDOWN_WARN_EINT)
		dev_crit(wm5100->dev, "Speaker shutdown warning\n");
	अगर (val & WM5100_SPK_SHUTDOWN_EINT)
		dev_crit(wm5100->dev, "Speaker shutdown\n");
	अगर (val & WM5100_CLKGEN_ERR_EINT)
		dev_crit(wm5100->dev, "SYSCLK underclocked\n");
	अगर (val & WM5100_CLKGEN_ERR_ASYNC_EINT)
		dev_crit(wm5100->dev, "ASYNCCLK underclocked\n");
पूर्ण

अटल व्योम wm5100_log_status4(काष्ठा wm5100_priv *wm5100, पूर्णांक val)
अणु
	अगर (val & WM5100_AIF3_ERR_EINT)
		dev_err(wm5100->dev, "AIF3 configuration error\n");
	अगर (val & WM5100_AIF2_ERR_EINT)
		dev_err(wm5100->dev, "AIF2 configuration error\n");
	अगर (val & WM5100_AIF1_ERR_EINT)
		dev_err(wm5100->dev, "AIF1 configuration error\n");
	अगर (val & WM5100_CTRLIF_ERR_EINT)
		dev_err(wm5100->dev, "Control interface error\n");
	अगर (val & WM5100_ISRC2_UNDERCLOCKED_EINT)
		dev_err(wm5100->dev, "ISRC2 underclocked\n");
	अगर (val & WM5100_ISRC1_UNDERCLOCKED_EINT)
		dev_err(wm5100->dev, "ISRC1 underclocked\n");
	अगर (val & WM5100_FX_UNDERCLOCKED_EINT)
		dev_err(wm5100->dev, "FX underclocked\n");
	अगर (val & WM5100_AIF3_UNDERCLOCKED_EINT)
		dev_err(wm5100->dev, "AIF3 underclocked\n");
	अगर (val & WM5100_AIF2_UNDERCLOCKED_EINT)
		dev_err(wm5100->dev, "AIF2 underclocked\n");
	अगर (val & WM5100_AIF1_UNDERCLOCKED_EINT)
		dev_err(wm5100->dev, "AIF1 underclocked\n");
	अगर (val & WM5100_ASRC_UNDERCLOCKED_EINT)
		dev_err(wm5100->dev, "ASRC underclocked\n");
	अगर (val & WM5100_DAC_UNDERCLOCKED_EINT)
		dev_err(wm5100->dev, "DAC underclocked\n");
	अगर (val & WM5100_ADC_UNDERCLOCKED_EINT)
		dev_err(wm5100->dev, "ADC underclocked\n");
	अगर (val & WM5100_MIXER_UNDERCLOCKED_EINT)
		dev_err(wm5100->dev, "Mixer underclocked\n");
पूर्ण

अटल पूर्णांक wm5100_post_ev(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *kcontrol,
			  पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm5100_priv *wm5100 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = snd_soc_component_पढ़ो(component, WM5100_INTERRUPT_RAW_STATUS_3);
	ret &= WM5100_SPK_SHUTDOWN_WARN_STS |
		WM5100_SPK_SHUTDOWN_STS | WM5100_CLKGEN_ERR_STS |
		WM5100_CLKGEN_ERR_ASYNC_STS;
	wm5100_log_status3(wm5100, ret);

	ret = snd_soc_component_पढ़ो(component, WM5100_INTERRUPT_RAW_STATUS_4);
	wm5100_log_status4(wm5100, ret);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget wm5100_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_SUPPLY("SYSCLK", WM5100_CLOCKING_3, WM5100_SYSCLK_ENA_SHIFT, 0,
		    शून्य, 0),
SND_SOC_DAPM_SUPPLY("ASYNCCLK", WM5100_CLOCKING_6, WM5100_ASYNC_CLK_ENA_SHIFT,
		    0, शून्य, 0),

SND_SOC_DAPM_REGULATOR_SUPPLY("CPVDD", 20, 0),
SND_SOC_DAPM_REGULATOR_SUPPLY("DBVDD2", 0, 0),
SND_SOC_DAPM_REGULATOR_SUPPLY("DBVDD3", 0, 0),

SND_SOC_DAPM_SUPPLY("CP1", WM5100_HP_CHARGE_PUMP_1, WM5100_CP1_ENA_SHIFT, 0,
		    शून्य, 0),
SND_SOC_DAPM_SUPPLY("CP2", WM5100_MIC_CHARGE_PUMP_1, WM5100_CP2_ENA_SHIFT, 0,
		    शून्य, 0),
SND_SOC_DAPM_SUPPLY("CP2 Active", WM5100_MIC_CHARGE_PUMP_1,
		    WM5100_CP2_BYPASS_SHIFT, 1, शून्य, 0),

SND_SOC_DAPM_SUPPLY("MICBIAS1", WM5100_MIC_BIAS_CTRL_1, WM5100_MICB1_ENA_SHIFT,
		    0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("MICBIAS2", WM5100_MIC_BIAS_CTRL_2, WM5100_MICB2_ENA_SHIFT,
		    0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("MICBIAS3", WM5100_MIC_BIAS_CTRL_3, WM5100_MICB3_ENA_SHIFT,
		    0, शून्य, 0),

SND_SOC_DAPM_INPUT("IN1L"),
SND_SOC_DAPM_INPUT("IN1R"),
SND_SOC_DAPM_INPUT("IN2L"),
SND_SOC_DAPM_INPUT("IN2R"),
SND_SOC_DAPM_INPUT("IN3L"),
SND_SOC_DAPM_INPUT("IN3R"),
SND_SOC_DAPM_INPUT("IN4L"),
SND_SOC_DAPM_INPUT("IN4R"),
SND_SOC_DAPM_SIGGEN("TONE"),

SND_SOC_DAPM_PGA_E("IN1L PGA", WM5100_INPUT_ENABLES, WM5100_IN1L_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("IN1R PGA", WM5100_INPUT_ENABLES, WM5100_IN1R_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("IN2L PGA", WM5100_INPUT_ENABLES, WM5100_IN2L_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("IN2R PGA", WM5100_INPUT_ENABLES, WM5100_IN2R_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("IN3L PGA", WM5100_INPUT_ENABLES, WM5100_IN3L_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("IN3R PGA", WM5100_INPUT_ENABLES, WM5100_IN3R_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("IN4L PGA", WM5100_INPUT_ENABLES, WM5100_IN4L_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("IN4R PGA", WM5100_INPUT_ENABLES, WM5100_IN4R_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),

SND_SOC_DAPM_PGA("Tone Generator 1", WM5100_TONE_GENERATOR_1,
		 WM5100_TONE1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Tone Generator 2", WM5100_TONE_GENERATOR_1,
		 WM5100_TONE2_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_AIF_IN("AIF1RX1", "AIF1 Playback", 0,
		    WM5100_AUDIO_IF_1_27, WM5100_AIF1RX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX2", "AIF1 Playback", 1,
		    WM5100_AUDIO_IF_1_27, WM5100_AIF1RX2_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX3", "AIF1 Playback", 2,
		    WM5100_AUDIO_IF_1_27, WM5100_AIF1RX3_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX4", "AIF1 Playback", 3,
		    WM5100_AUDIO_IF_1_27, WM5100_AIF1RX4_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX5", "AIF1 Playback", 4,
		    WM5100_AUDIO_IF_1_27, WM5100_AIF1RX5_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX6", "AIF1 Playback", 5,
		    WM5100_AUDIO_IF_1_27, WM5100_AIF1RX6_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX7", "AIF1 Playback", 6,
		    WM5100_AUDIO_IF_1_27, WM5100_AIF1RX7_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX8", "AIF1 Playback", 7,
		    WM5100_AUDIO_IF_1_27, WM5100_AIF1RX8_ENA_SHIFT, 0),

SND_SOC_DAPM_AIF_IN("AIF2RX1", "AIF2 Playback", 0,
		    WM5100_AUDIO_IF_2_27, WM5100_AIF2RX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF2RX2", "AIF2 Playback", 1,
		    WM5100_AUDIO_IF_2_27, WM5100_AIF2RX2_ENA_SHIFT, 0),

SND_SOC_DAPM_AIF_IN("AIF3RX1", "AIF3 Playback", 0,
		    WM5100_AUDIO_IF_3_27, WM5100_AIF3RX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF3RX2", "AIF3 Playback", 1,
		    WM5100_AUDIO_IF_3_27, WM5100_AIF3RX2_ENA_SHIFT, 0),

SND_SOC_DAPM_AIF_OUT("AIF1TX1", "AIF1 Capture", 0,
		    WM5100_AUDIO_IF_1_26, WM5100_AIF1TX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX2", "AIF1 Capture", 1,
		    WM5100_AUDIO_IF_1_26, WM5100_AIF1TX2_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX3", "AIF1 Capture", 2,
		    WM5100_AUDIO_IF_1_26, WM5100_AIF1TX3_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX4", "AIF1 Capture", 3,
		    WM5100_AUDIO_IF_1_26, WM5100_AIF1TX4_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX5", "AIF1 Capture", 4,
		    WM5100_AUDIO_IF_1_26, WM5100_AIF1TX5_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX6", "AIF1 Capture", 5,
		    WM5100_AUDIO_IF_1_26, WM5100_AIF1TX6_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX7", "AIF1 Capture", 6,
		    WM5100_AUDIO_IF_1_26, WM5100_AIF1TX7_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX8", "AIF1 Capture", 7,
		    WM5100_AUDIO_IF_1_26, WM5100_AIF1TX8_ENA_SHIFT, 0),

SND_SOC_DAPM_AIF_OUT("AIF2TX1", "AIF2 Capture", 0,
		    WM5100_AUDIO_IF_2_26, WM5100_AIF2TX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF2TX2", "AIF2 Capture", 1,
		    WM5100_AUDIO_IF_2_26, WM5100_AIF2TX2_ENA_SHIFT, 0),

SND_SOC_DAPM_AIF_OUT("AIF3TX1", "AIF3 Capture", 0,
		    WM5100_AUDIO_IF_3_26, WM5100_AIF3TX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF3TX2", "AIF3 Capture", 1,
		    WM5100_AUDIO_IF_3_26, WM5100_AIF3TX2_ENA_SHIFT, 0),

SND_SOC_DAPM_PGA_E("OUT6L", WM5100_OUTPUT_ENABLES_2, WM5100_OUT6L_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT6R", WM5100_OUTPUT_ENABLES_2, WM5100_OUT6R_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT5L", WM5100_OUTPUT_ENABLES_2, WM5100_OUT5L_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT5R", WM5100_OUTPUT_ENABLES_2, WM5100_OUT5R_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT4L", WM5100_OUTPUT_ENABLES_2, WM5100_OUT4L_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT4R", WM5100_OUTPUT_ENABLES_2, WM5100_OUT4R_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT3L", WM5100_CHANNEL_ENABLES_1, WM5100_HP3L_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT3R", WM5100_CHANNEL_ENABLES_1, WM5100_HP3R_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT2L", WM5100_CHANNEL_ENABLES_1, WM5100_HP2L_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT2R", WM5100_CHANNEL_ENABLES_1, WM5100_HP2R_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT1L", WM5100_CHANNEL_ENABLES_1, WM5100_HP1L_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT1R", WM5100_CHANNEL_ENABLES_1, WM5100_HP1R_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("PWM1 Driver", WM5100_PWM_DRIVE_1, WM5100_PWM1_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("PWM2 Driver", WM5100_PWM_DRIVE_1, WM5100_PWM2_ENA_SHIFT, 0,
		   शून्य, 0, wm5100_out_ev, SND_SOC_DAPM_POST_PMU),

SND_SOC_DAPM_PGA("EQ1", WM5100_EQ1_1, WM5100_EQ1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("EQ2", WM5100_EQ2_1, WM5100_EQ2_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("EQ3", WM5100_EQ3_1, WM5100_EQ3_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("EQ4", WM5100_EQ4_1, WM5100_EQ4_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("DRC1L", WM5100_DRC1_CTRL1, WM5100_DRCL_ENA_SHIFT, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("DRC1R", WM5100_DRC1_CTRL1, WM5100_DRCR_ENA_SHIFT, 0,
		 शून्य, 0),

SND_SOC_DAPM_PGA("LHPF1", WM5100_HPLPF1_1, WM5100_LHPF1_ENA_SHIFT, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("LHPF2", WM5100_HPLPF2_1, WM5100_LHPF2_ENA_SHIFT, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("LHPF3", WM5100_HPLPF3_1, WM5100_LHPF3_ENA_SHIFT, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("LHPF4", WM5100_HPLPF4_1, WM5100_LHPF4_ENA_SHIFT, 0,
		 शून्य, 0),

WM5100_MIXER_WIDGETS(EQ1, "EQ1"),
WM5100_MIXER_WIDGETS(EQ2, "EQ2"),
WM5100_MIXER_WIDGETS(EQ3, "EQ3"),
WM5100_MIXER_WIDGETS(EQ4, "EQ4"),

WM5100_MIXER_WIDGETS(DRC1L, "DRC1L"),
WM5100_MIXER_WIDGETS(DRC1R, "DRC1R"),

WM5100_MIXER_WIDGETS(LHPF1, "LHPF1"),
WM5100_MIXER_WIDGETS(LHPF2, "LHPF2"),
WM5100_MIXER_WIDGETS(LHPF3, "LHPF3"),
WM5100_MIXER_WIDGETS(LHPF4, "LHPF4"),

WM5100_MIXER_WIDGETS(AIF1TX1, "AIF1TX1"),
WM5100_MIXER_WIDGETS(AIF1TX2, "AIF1TX2"),
WM5100_MIXER_WIDGETS(AIF1TX3, "AIF1TX3"),
WM5100_MIXER_WIDGETS(AIF1TX4, "AIF1TX4"),
WM5100_MIXER_WIDGETS(AIF1TX5, "AIF1TX5"),
WM5100_MIXER_WIDGETS(AIF1TX6, "AIF1TX6"),
WM5100_MIXER_WIDGETS(AIF1TX7, "AIF1TX7"),
WM5100_MIXER_WIDGETS(AIF1TX8, "AIF1TX8"),

WM5100_MIXER_WIDGETS(AIF2TX1, "AIF2TX1"),
WM5100_MIXER_WIDGETS(AIF2TX2, "AIF2TX2"),

WM5100_MIXER_WIDGETS(AIF3TX1, "AIF3TX1"),
WM5100_MIXER_WIDGETS(AIF3TX2, "AIF3TX2"),

WM5100_MIXER_WIDGETS(HPOUT1L, "HPOUT1L"),
WM5100_MIXER_WIDGETS(HPOUT1R, "HPOUT1R"),
WM5100_MIXER_WIDGETS(HPOUT2L, "HPOUT2L"),
WM5100_MIXER_WIDGETS(HPOUT2R, "HPOUT2R"),
WM5100_MIXER_WIDGETS(HPOUT3L, "HPOUT3L"),
WM5100_MIXER_WIDGETS(HPOUT3R, "HPOUT3R"),

WM5100_MIXER_WIDGETS(SPKOUTL, "SPKOUTL"),
WM5100_MIXER_WIDGETS(SPKOUTR, "SPKOUTR"),
WM5100_MIXER_WIDGETS(SPKDAT1L, "SPKDAT1L"),
WM5100_MIXER_WIDGETS(SPKDAT1R, "SPKDAT1R"),
WM5100_MIXER_WIDGETS(SPKDAT2L, "SPKDAT2L"),
WM5100_MIXER_WIDGETS(SPKDAT2R, "SPKDAT2R"),

WM5100_MIXER_WIDGETS(PWM1, "PWM1"),
WM5100_MIXER_WIDGETS(PWM2, "PWM2"),

SND_SOC_DAPM_OUTPUT("HPOUT1L"),
SND_SOC_DAPM_OUTPUT("HPOUT1R"),
SND_SOC_DAPM_OUTPUT("HPOUT2L"),
SND_SOC_DAPM_OUTPUT("HPOUT2R"),
SND_SOC_DAPM_OUTPUT("HPOUT3L"),
SND_SOC_DAPM_OUTPUT("HPOUT3R"),
SND_SOC_DAPM_OUTPUT("SPKOUTL"),
SND_SOC_DAPM_OUTPUT("SPKOUTR"),
SND_SOC_DAPM_OUTPUT("SPKDAT1"),
SND_SOC_DAPM_OUTPUT("SPKDAT2"),
SND_SOC_DAPM_OUTPUT("PWM1"),
SND_SOC_DAPM_OUTPUT("PWM2"),
पूर्ण;

/* We रेजिस्टर a _POST event अगर we करोn't have IRQ support so we can
 * look at the error status from the CODEC - अगर we've got the IRQ
 * hooked up then we will get prompted to look by an पूर्णांकerrupt.
 */
अटल स्थिर काष्ठा snd_soc_dapm_widget wm5100_dapm_widमाला_लो_noirq[] = अणु
SND_SOC_DAPM_POST("Post", wm5100_post_ev),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm5100_dapm_routes[] = अणु
	अणु "CP1", शून्य, "CPVDD" पूर्ण,
	अणु "CP2 Active", शून्य, "CPVDD" पूर्ण,

	अणु "IN1L", शून्य, "SYSCLK" पूर्ण,
	अणु "IN1R", शून्य, "SYSCLK" पूर्ण,
	अणु "IN2L", शून्य, "SYSCLK" पूर्ण,
	अणु "IN2R", शून्य, "SYSCLK" पूर्ण,
	अणु "IN3L", शून्य, "SYSCLK" पूर्ण,
	अणु "IN3R", शून्य, "SYSCLK" पूर्ण,
	अणु "IN4L", शून्य, "SYSCLK" पूर्ण,
	अणु "IN4R", शून्य, "SYSCLK" पूर्ण,

	अणु "OUT1L", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT1R", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT2L", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT2R", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT3L", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT3R", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT4L", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT4R", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT5L", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT5R", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT6L", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT6R", शून्य, "SYSCLK" पूर्ण,

	अणु "AIF1RX1", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1RX2", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1RX3", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1RX4", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1RX5", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1RX6", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1RX7", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1RX8", शून्य, "SYSCLK" पूर्ण,

	अणु "AIF2RX1", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF2RX1", शून्य, "DBVDD2" पूर्ण,
	अणु "AIF2RX2", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF2RX2", शून्य, "DBVDD2" पूर्ण,

	अणु "AIF3RX1", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF3RX1", शून्य, "DBVDD3" पूर्ण,
	अणु "AIF3RX2", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF3RX2", शून्य, "DBVDD3" पूर्ण,

	अणु "AIF1TX1", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1TX2", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1TX3", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1TX4", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1TX5", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1TX6", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1TX7", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF1TX8", शून्य, "SYSCLK" पूर्ण,

	अणु "AIF2TX1", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF2TX1", शून्य, "DBVDD2" पूर्ण,
	अणु "AIF2TX2", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF2TX2", शून्य, "DBVDD2" पूर्ण,

	अणु "AIF3TX1", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF3TX1", शून्य, "DBVDD3" पूर्ण,
	अणु "AIF3TX2", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF3TX2", शून्य, "DBVDD3" पूर्ण,

	अणु "MICBIAS1", शून्य, "CP2" पूर्ण,
	अणु "MICBIAS2", शून्य, "CP2" पूर्ण,
	अणु "MICBIAS3", शून्य, "CP2" पूर्ण,

	अणु "IN1L PGA", शून्य, "CP2" पूर्ण,
	अणु "IN1R PGA", शून्य, "CP2" पूर्ण,
	अणु "IN2L PGA", शून्य, "CP2" पूर्ण,
	अणु "IN2R PGA", शून्य, "CP2" पूर्ण,
	अणु "IN3L PGA", शून्य, "CP2" पूर्ण,
	अणु "IN3R PGA", शून्य, "CP2" पूर्ण,
	अणु "IN4L PGA", शून्य, "CP2" पूर्ण,
	अणु "IN4R PGA", शून्य, "CP2" पूर्ण,

	अणु "IN1L PGA", शून्य, "CP2 Active" पूर्ण,
	अणु "IN1R PGA", शून्य, "CP2 Active" पूर्ण,
	अणु "IN2L PGA", शून्य, "CP2 Active" पूर्ण,
	अणु "IN2R PGA", शून्य, "CP2 Active" पूर्ण,
	अणु "IN3L PGA", शून्य, "CP2 Active" पूर्ण,
	अणु "IN3R PGA", शून्य, "CP2 Active" पूर्ण,
	अणु "IN4L PGA", शून्य, "CP2 Active" पूर्ण,
	अणु "IN4R PGA", शून्य, "CP2 Active" पूर्ण,

	अणु "OUT1L", शून्य, "CP1" पूर्ण,
	अणु "OUT1R", शून्य, "CP1" पूर्ण,
	अणु "OUT2L", शून्य, "CP1" पूर्ण,
	अणु "OUT2R", शून्य, "CP1" पूर्ण,
	अणु "OUT3L", शून्य, "CP1" पूर्ण,
	अणु "OUT3R", शून्य, "CP1" पूर्ण,

	अणु "Tone Generator 1", शून्य, "TONE" पूर्ण,
	अणु "Tone Generator 2", शून्य, "TONE" पूर्ण,

	अणु "IN1L PGA", शून्य, "IN1L" पूर्ण,
	अणु "IN1R PGA", शून्य, "IN1R" पूर्ण,
	अणु "IN2L PGA", शून्य, "IN2L" पूर्ण,
	अणु "IN2R PGA", शून्य, "IN2R" पूर्ण,
	अणु "IN3L PGA", शून्य, "IN3L" पूर्ण,
	अणु "IN3R PGA", शून्य, "IN3R" पूर्ण,
	अणु "IN4L PGA", शून्य, "IN4L" पूर्ण,
	अणु "IN4R PGA", शून्य, "IN4R" पूर्ण,

	WM5100_MIXER_ROUTES("OUT1L", "HPOUT1L"),
	WM5100_MIXER_ROUTES("OUT1R", "HPOUT1R"),
	WM5100_MIXER_ROUTES("OUT2L", "HPOUT2L"),
	WM5100_MIXER_ROUTES("OUT2R", "HPOUT2R"),
	WM5100_MIXER_ROUTES("OUT3L", "HPOUT3L"),
	WM5100_MIXER_ROUTES("OUT3R", "HPOUT3R"),

	WM5100_MIXER_ROUTES("OUT4L", "SPKOUTL"),
	WM5100_MIXER_ROUTES("OUT4R", "SPKOUTR"),
	WM5100_MIXER_ROUTES("OUT5L", "SPKDAT1L"),
	WM5100_MIXER_ROUTES("OUT5R", "SPKDAT1R"),
	WM5100_MIXER_ROUTES("OUT6L", "SPKDAT2L"),
	WM5100_MIXER_ROUTES("OUT6R", "SPKDAT2R"),

	WM5100_MIXER_ROUTES("PWM1 Driver", "PWM1"),
	WM5100_MIXER_ROUTES("PWM2 Driver", "PWM2"),

	WM5100_MIXER_ROUTES("AIF1TX1", "AIF1TX1"),
	WM5100_MIXER_ROUTES("AIF1TX2", "AIF1TX2"),
	WM5100_MIXER_ROUTES("AIF1TX3", "AIF1TX3"),
	WM5100_MIXER_ROUTES("AIF1TX4", "AIF1TX4"),
	WM5100_MIXER_ROUTES("AIF1TX5", "AIF1TX5"),
	WM5100_MIXER_ROUTES("AIF1TX6", "AIF1TX6"),
	WM5100_MIXER_ROUTES("AIF1TX7", "AIF1TX7"),
	WM5100_MIXER_ROUTES("AIF1TX8", "AIF1TX8"),

	WM5100_MIXER_ROUTES("AIF2TX1", "AIF2TX1"),
	WM5100_MIXER_ROUTES("AIF2TX2", "AIF2TX2"),

	WM5100_MIXER_ROUTES("AIF3TX1", "AIF3TX1"),
	WM5100_MIXER_ROUTES("AIF3TX2", "AIF3TX2"),

	WM5100_MIXER_ROUTES("EQ1", "EQ1"),
	WM5100_MIXER_ROUTES("EQ2", "EQ2"),
	WM5100_MIXER_ROUTES("EQ3", "EQ3"),
	WM5100_MIXER_ROUTES("EQ4", "EQ4"),

	WM5100_MIXER_ROUTES("DRC1L", "DRC1L"),
	WM5100_MIXER_ROUTES("DRC1R", "DRC1R"),

	WM5100_MIXER_ROUTES("LHPF1", "LHPF1"),
	WM5100_MIXER_ROUTES("LHPF2", "LHPF2"),
	WM5100_MIXER_ROUTES("LHPF3", "LHPF3"),
	WM5100_MIXER_ROUTES("LHPF4", "LHPF4"),

	अणु "HPOUT1L", शून्य, "OUT1L" पूर्ण,
	अणु "HPOUT1R", शून्य, "OUT1R" पूर्ण,
	अणु "HPOUT2L", शून्य, "OUT2L" पूर्ण,
	अणु "HPOUT2R", शून्य, "OUT2R" पूर्ण,
	अणु "HPOUT3L", शून्य, "OUT3L" पूर्ण,
	अणु "HPOUT3R", शून्य, "OUT3R" पूर्ण,
	अणु "SPKOUTL", शून्य, "OUT4L" पूर्ण,
	अणु "SPKOUTR", शून्य, "OUT4R" पूर्ण,
	अणु "SPKDAT1", शून्य, "OUT5L" पूर्ण,
	अणु "SPKDAT1", शून्य, "OUT5R" पूर्ण,
	अणु "SPKDAT2", शून्य, "OUT6L" पूर्ण,
	अणु "SPKDAT2", शून्य, "OUT6R" पूर्ण,
	अणु "PWM1", शून्य, "PWM1 Driver" पूर्ण,
	अणु "PWM2", शून्य, "PWM2 Driver" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence wm5100_reva_patches[] = अणु
	अणु WM5100_AUDIO_IF_1_10, 0 पूर्ण,
	अणु WM5100_AUDIO_IF_1_11, 1 पूर्ण,
	अणु WM5100_AUDIO_IF_1_12, 2 पूर्ण,
	अणु WM5100_AUDIO_IF_1_13, 3 पूर्ण,
	अणु WM5100_AUDIO_IF_1_14, 4 पूर्ण,
	अणु WM5100_AUDIO_IF_1_15, 5 पूर्ण,
	अणु WM5100_AUDIO_IF_1_16, 6 पूर्ण,
	अणु WM5100_AUDIO_IF_1_17, 7 पूर्ण,

	अणु WM5100_AUDIO_IF_1_18, 0 पूर्ण,
	अणु WM5100_AUDIO_IF_1_19, 1 पूर्ण,
	अणु WM5100_AUDIO_IF_1_20, 2 पूर्ण,
	अणु WM5100_AUDIO_IF_1_21, 3 पूर्ण,
	अणु WM5100_AUDIO_IF_1_22, 4 पूर्ण,
	अणु WM5100_AUDIO_IF_1_23, 5 पूर्ण,
	अणु WM5100_AUDIO_IF_1_24, 6 पूर्ण,
	अणु WM5100_AUDIO_IF_1_25, 7 पूर्ण,

	अणु WM5100_AUDIO_IF_2_10, 0 पूर्ण,
	अणु WM5100_AUDIO_IF_2_11, 1 पूर्ण,

	अणु WM5100_AUDIO_IF_2_18, 0 पूर्ण,
	अणु WM5100_AUDIO_IF_2_19, 1 पूर्ण,

	अणु WM5100_AUDIO_IF_3_10, 0 पूर्ण,
	अणु WM5100_AUDIO_IF_3_11, 1 पूर्ण,

	अणु WM5100_AUDIO_IF_3_18, 0 पूर्ण,
	अणु WM5100_AUDIO_IF_3_19, 1 पूर्ण,
पूर्ण;

अटल पूर्णांक wm5100_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक lrclk, bclk, mask, base;

	base = dai->driver->base;

	lrclk = 0;
	bclk = 0;

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
		mask = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		mask = 2;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported DAI format %d\n",
			fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		lrclk |= WM5100_AIF1TX_LRCLK_MSTR;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		bclk |= WM5100_AIF1_BCLK_MSTR;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		lrclk |= WM5100_AIF1TX_LRCLK_MSTR;
		bclk |= WM5100_AIF1_BCLK_MSTR;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported master mode %d\n",
			fmt & SND_SOC_DAIFMT_MASTER_MASK);
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		bclk |= WM5100_AIF1_BCLK_INV;
		lrclk |= WM5100_AIF1TX_LRCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		bclk |= WM5100_AIF1_BCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		lrclk |= WM5100_AIF1TX_LRCLK_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, base + 1, WM5100_AIF1_BCLK_MSTR |
			    WM5100_AIF1_BCLK_INV, bclk);
	snd_soc_component_update_bits(component, base + 2, WM5100_AIF1TX_LRCLK_MSTR |
			    WM5100_AIF1TX_LRCLK_INV, lrclk);
	snd_soc_component_update_bits(component, base + 3, WM5100_AIF1TX_LRCLK_MSTR |
			    WM5100_AIF1TX_LRCLK_INV, lrclk);
	snd_soc_component_update_bits(component, base + 5, WM5100_AIF1_FMT_MASK, mask);

	वापस 0;
पूर्ण

#घोषणा WM5100_NUM_BCLK_RATES 19

अटल पूर्णांक wm5100_bclk_rates_dat[WM5100_NUM_BCLK_RATES] = अणु
	32000,
	48000,
	64000,
	96000,
	128000,
	192000,
	256000,
	384000,
	512000,
	768000,
	1024000,
	1536000,
	2048000,
	3072000,
	4096000,
	6144000,
	8192000,
	12288000,
	24576000,
पूर्ण;

अटल पूर्णांक wm5100_bclk_rates_cd[WM5100_NUM_BCLK_RATES] = अणु
	29400,
	44100,
	58800,
	88200,
	117600,
	176400,
	235200,
	352800,
	470400,
	705600,
	940800,
	1411200,
	1881600,
	2882400,
	3763200,
	5644800,
	7526400,
	11289600,
	22579600,
पूर्ण;

अटल पूर्णांक wm5100_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm5100_priv *wm5100 = snd_soc_component_get_drvdata(component);
	bool async = wm5100->aअगर_async[dai->id];
	पूर्णांक i, base, bclk, aअगर_rate, lrclk, wl, fl, sr;
	पूर्णांक *bclk_rates;

	base = dai->driver->base;

	/* Data sizes अगर not using TDM */
	wl = params_width(params);
	अगर (wl < 0)
		वापस wl;
	fl = snd_soc_params_to_frame_size(params);
	अगर (fl < 0)
		वापस fl;

	dev_dbg(component->dev, "Word length %d bits, frame length %d bits\n",
		wl, fl);

	/* Target BCLK rate */
	bclk = snd_soc_params_to_bclk(params);
	अगर (bclk < 0)
		वापस bclk;

	/* Root क्रम BCLK depends on SYS/ASYNCCLK */
	अगर (!async) अणु
		aअगर_rate = wm5100->sysclk;
		sr = wm5100_alloc_sr(component, params_rate(params));
		अगर (sr < 0)
			वापस sr;
	पूर्ण अन्यथा अणु
		/* If we're in ASYNCCLK set the ASYNC sample rate */
		aअगर_rate = wm5100->asyncclk;
		sr = 3;

		क्रम (i = 0; i < ARRAY_SIZE(wm5100_sr_code); i++)
			अगर (params_rate(params) == wm5100_sr_code[i])
				अवरोध;
		अगर (i == ARRAY_SIZE(wm5100_sr_code)) अणु
			dev_err(component->dev, "Invalid rate %dHzn",
				params_rate(params));
			वापस -EINVAL;
		पूर्ण

		/* TODO: We should really check क्रम symmetry */
		snd_soc_component_update_bits(component, WM5100_CLOCKING_8,
				    WM5100_ASYNC_SAMPLE_RATE_MASK, i);
	पूर्ण

	अगर (!aअगर_rate) अणु
		dev_err(component->dev, "%s has no rate set\n",
			async ? "ASYNCCLK" : "SYSCLK");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(component->dev, "Target BCLK is %dHz, using %dHz %s\n",
		bclk, aअगर_rate, async ? "ASYNCCLK" : "SYSCLK");

	अगर (aअगर_rate % 4000)
		bclk_rates = wm5100_bclk_rates_cd;
	अन्यथा
		bclk_rates = wm5100_bclk_rates_dat;

	क्रम (i = 0; i < WM5100_NUM_BCLK_RATES; i++)
		अगर (bclk_rates[i] >= bclk && (bclk_rates[i] % bclk == 0))
			अवरोध;
	अगर (i == WM5100_NUM_BCLK_RATES) अणु
		dev_err(component->dev,
			"No valid BCLK for %dHz found from %dHz %s\n",
			bclk, aअगर_rate, async ? "ASYNCCLK" : "SYSCLK");
		वापस -EINVAL;
	पूर्ण

	bclk = i;
	dev_dbg(component->dev, "Setting %dHz BCLK\n", bclk_rates[bclk]);
	snd_soc_component_update_bits(component, base + 1, WM5100_AIF1_BCLK_FREQ_MASK, bclk);

	lrclk = bclk_rates[bclk] / params_rate(params);
	dev_dbg(component->dev, "Setting %dHz LRCLK\n", bclk_rates[bclk] / lrclk);
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK ||
	    wm5100->aअगर_symmetric[dai->id])
		snd_soc_component_update_bits(component, base + 7,
				    WM5100_AIF1RX_BCPF_MASK, lrclk);
	अन्यथा
		snd_soc_component_update_bits(component, base + 6,
				    WM5100_AIF1TX_BCPF_MASK, lrclk);

	i = (wl << WM5100_AIF1TX_WL_SHIFT) | fl;
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		snd_soc_component_update_bits(component, base + 9,
				    WM5100_AIF1RX_WL_MASK |
				    WM5100_AIF1RX_SLOT_LEN_MASK, i);
	अन्यथा
		snd_soc_component_update_bits(component, base + 8,
				    WM5100_AIF1TX_WL_MASK |
				    WM5100_AIF1TX_SLOT_LEN_MASK, i);

	snd_soc_component_update_bits(component, base + 4, WM5100_AIF1_RATE_MASK, sr);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops wm5100_dai_ops = अणु
	.set_fmt = wm5100_set_fmt,
	.hw_params = wm5100_hw_params,
पूर्ण;

अटल पूर्णांक wm5100_set_sysclk(काष्ठा snd_soc_component *component, पूर्णांक clk_id,
			     पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा wm5100_priv *wm5100 = snd_soc_component_get_drvdata(component);
	पूर्णांक *rate_store;
	पूर्णांक fval, audio_rate, ret, reg;

	चयन (clk_id) अणु
	हाल WM5100_CLK_SYSCLK:
		reg = WM5100_CLOCKING_3;
		rate_store = &wm5100->sysclk;
		अवरोध;
	हाल WM5100_CLK_ASYNCCLK:
		reg = WM5100_CLOCKING_7;
		rate_store = &wm5100->asyncclk;
		अवरोध;
	हाल WM5100_CLK_32KHZ:
		/* The 32kHz घड़ी is slightly dअगरferent to the others */
		चयन (source) अणु
		हाल WM5100_CLKSRC_MCLK1:
		हाल WM5100_CLKSRC_MCLK2:
		हाल WM5100_CLKSRC_SYSCLK:
			snd_soc_component_update_bits(component, WM5100_CLOCKING_1,
					    WM5100_CLK_32K_SRC_MASK,
					    source);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		वापस 0;

	हाल WM5100_CLK_AIF1:
	हाल WM5100_CLK_AIF2:
	हाल WM5100_CLK_AIF3:
		/* Not real घड़ीs, record which घड़ी करोमुख्य they're in */
		चयन (source) अणु
		हाल WM5100_CLKSRC_SYSCLK:
			wm5100->aअगर_async[clk_id - 1] = false;
			अवरोध;
		हाल WM5100_CLKSRC_ASYNCCLK:
			wm5100->aअगर_async[clk_id - 1] = true;
			अवरोध;
		शेष:
			dev_err(component->dev, "Invalid source %d\n", source);
			वापस -EINVAL;
		पूर्ण	
		वापस 0;

	हाल WM5100_CLK_OPCLK:
		चयन (freq) अणु
		हाल 5644800:
		हाल 6144000:
			snd_soc_component_update_bits(component, WM5100_MISC_GPIO_1,
					    WM5100_OPCLK_SEL_MASK, 0);
			अवरोध;
		हाल 11289600:
		हाल 12288000:
			snd_soc_component_update_bits(component, WM5100_MISC_GPIO_1,
					    WM5100_OPCLK_SEL_MASK, 0);
			अवरोध;
		हाल 22579200:
		हाल 24576000:
			snd_soc_component_update_bits(component, WM5100_MISC_GPIO_1,
					    WM5100_OPCLK_SEL_MASK, 0);
			अवरोध;
		शेष:
			dev_err(component->dev, "Unsupported OPCLK %dHz\n",
				freq);
			वापस -EINVAL;
		पूर्ण
		वापस 0;

	शेष:
		dev_err(component->dev, "Unknown clock %d\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	चयन (source) अणु
	हाल WM5100_CLKSRC_SYSCLK:
	हाल WM5100_CLKSRC_ASYNCCLK:
		dev_err(component->dev, "Invalid source %d\n", source);
		वापस -EINVAL;
	पूर्ण

	चयन (freq) अणु
	हाल 5644800:
	हाल 6144000:
		fval = 0;
		अवरोध;
	हाल 11289600:
	हाल 12288000:
		fval = 1;
		अवरोध;
	हाल 22579200:
	हाल 24576000:
		fval = 2;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid clock rate: %d\n", freq);
		वापस -EINVAL;
	पूर्ण

	चयन (freq) अणु
	हाल 5644800:
	हाल 11289600:
	हाल 22579200:
		audio_rate = 44100;
		अवरोध;

	हाल 6144000:
	हाल 12288000:
	हाल 24576000:
		audio_rate = 48000;
		अवरोध;

	शेष:
		BUG();
		audio_rate = 0;
		अवरोध;
	पूर्ण

	/* TODO: Check अगर MCLKs are in use and enable/disable pulls to
	 * match.
	 */

	snd_soc_component_update_bits(component, reg, WM5100_SYSCLK_FREQ_MASK |
			    WM5100_SYSCLK_SRC_MASK,
			    fval << WM5100_SYSCLK_FREQ_SHIFT | source);

	/* If this is SYSCLK then configure the घड़ी rate क्रम the
	 * पूर्णांकernal audio functions to the natural sample rate क्रम
	 * this घड़ी rate.
	 */
	अगर (clk_id == WM5100_CLK_SYSCLK) अणु
		dev_dbg(component->dev, "Setting primary audio rate to %dHz",
			audio_rate);
		अगर (0 && *rate_store)
			wm5100_मुक्त_sr(component, audio_rate);
		ret = wm5100_alloc_sr(component, audio_rate);
		अगर (ret != 0)
			dev_warn(component->dev, "Primary audio slot is %d\n",
				 ret);
	पूर्ण

	*rate_store = freq;

	वापस 0;
पूर्ण

काष्ठा _fll_भाग अणु
	u16 fll_fratio;
	u16 fll_outभाग;
	u16 fll_refclk_भाग;
	u16 n;
	u16 theta;
	u16 lambda;
पूर्ण;

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
	अचिन्हित पूर्णांक target;
	अचिन्हित पूर्णांक भाग;
	अचिन्हित पूर्णांक fratio, gcd_fll;
	पूर्णांक i;

	/* Fref must be <=13.5MHz */
	भाग = 1;
	fll_भाग->fll_refclk_भाग = 0;
	जबतक ((Fref / भाग) > 13500000) अणु
		भाग *= 2;
		fll_भाग->fll_refclk_भाग++;

		अगर (भाग > 8) अणु
			pr_err("Can't scale %dMHz input down to <=13.5MHz\n",
			       Fref);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	pr_debug("FLL Fref=%u Fout=%u\n", Fref, Fout);

	/* Apply the भागision क्रम our reमुख्यing calculations */
	Fref /= भाग;

	/* Fvco should be 90-100MHz; करोn't check the upper bound */
	भाग = 2;
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

	pr_debug("FLL Fvco=%dHz\n", target);

	/* Find an appropraite FLL_FRATIO and factor it out of the target */
	क्रम (i = 0; i < ARRAY_SIZE(fll_fratios); i++) अणु
		अगर (fll_fratios[i].min <= Fref && Fref <= fll_fratios[i].max) अणु
			fll_भाग->fll_fratio = fll_fratios[i].fll_fratio;
			fratio = fll_fratios[i].ratio;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(fll_fratios)) अणु
		pr_err("Unable to find FLL_FRATIO for Fref=%uHz\n", Fref);
		वापस -EINVAL;
	पूर्ण

	fll_भाग->n = target / (fratio * Fref);

	अगर (target % Fref == 0) अणु
		fll_भाग->theta = 0;
		fll_भाग->lambda = 0;
	पूर्ण अन्यथा अणु
		gcd_fll = gcd(target, fratio * Fref);

		fll_भाग->theta = (target - (fll_भाग->n * fratio * Fref))
			/ gcd_fll;
		fll_भाग->lambda = (fratio * Fref) / gcd_fll;
	पूर्ण

	pr_debug("FLL N=%x THETA=%x LAMBDA=%x\n",
		 fll_भाग->n, fll_भाग->theta, fll_भाग->lambda);
	pr_debug("FLL_FRATIO=%x(%d) FLL_OUTDIV=%x FLL_REFCLK_DIV=%x\n",
		 fll_भाग->fll_fratio, fratio, fll_भाग->fll_outभाग,
		 fll_भाग->fll_refclk_भाग);

	वापस 0;
पूर्ण

अटल पूर्णांक wm5100_set_fll(काष्ठा snd_soc_component *component, पूर्णांक fll_id, पूर्णांक source,
			  अचिन्हित पूर्णांक Fref, अचिन्हित पूर्णांक Fout)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(component->dev);
	काष्ठा wm5100_priv *wm5100 = snd_soc_component_get_drvdata(component);
	काष्ठा _fll_भाग factors;
	काष्ठा wm5100_fll *fll;
	पूर्णांक ret, base, lock, i, समयout;
	अचिन्हित दीर्घ समय_left;

	चयन (fll_id) अणु
	हाल WM5100_FLL1:
		fll = &wm5100->fll[0];
		base = WM5100_FLL1_CONTROL_1 - 1;
		lock = WM5100_FLL1_LOCK_STS;
		अवरोध;
	हाल WM5100_FLL2:
		fll = &wm5100->fll[1];
		base = WM5100_FLL2_CONTROL_2 - 1;
		lock = WM5100_FLL2_LOCK_STS;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unknown FLL %d\n",fll_id);
		वापस -EINVAL;
	पूर्ण

	अगर (!Fout) अणु
		dev_dbg(component->dev, "FLL%d disabled", fll_id);
		अगर (fll->fout)
			pm_runसमय_put(component->dev);
		fll->fout = 0;
		snd_soc_component_update_bits(component, base + 1, WM5100_FLL1_ENA, 0);
		वापस 0;
	पूर्ण

	चयन (source) अणु
	हाल WM5100_FLL_SRC_MCLK1:
	हाल WM5100_FLL_SRC_MCLK2:
	हाल WM5100_FLL_SRC_FLL1:
	हाल WM5100_FLL_SRC_FLL2:
	हाल WM5100_FLL_SRC_AIF1BCLK:
	हाल WM5100_FLL_SRC_AIF2BCLK:
	हाल WM5100_FLL_SRC_AIF3BCLK:
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid FLL source %d\n", source);
		वापस -EINVAL;
	पूर्ण

	ret = fll_factors(&factors, Fref, Fout);
	अगर (ret < 0)
		वापस ret;

	/* Disable the FLL जबतक we reconfigure */
	snd_soc_component_update_bits(component, base + 1, WM5100_FLL1_ENA, 0);

	snd_soc_component_update_bits(component, base + 2,
			    WM5100_FLL1_OUTDIV_MASK | WM5100_FLL1_FRATIO_MASK,
			    (factors.fll_outभाग << WM5100_FLL1_OUTDIV_SHIFT) |
			    factors.fll_fratio);
	snd_soc_component_update_bits(component, base + 3, WM5100_FLL1_THETA_MASK,
			    factors.theta);
	snd_soc_component_update_bits(component, base + 5, WM5100_FLL1_N_MASK, factors.n);
	snd_soc_component_update_bits(component, base + 6,
			    WM5100_FLL1_REFCLK_DIV_MASK |
			    WM5100_FLL1_REFCLK_SRC_MASK,
			    (factors.fll_refclk_भाग
			     << WM5100_FLL1_REFCLK_DIV_SHIFT) | source);
	snd_soc_component_update_bits(component, base + 7, WM5100_FLL1_LAMBDA_MASK,
			    factors.lambda);

	/* Clear any pending completions */
	try_रुको_क्रम_completion(&fll->lock);

	pm_runसमय_get_sync(component->dev);

	snd_soc_component_update_bits(component, base + 1, WM5100_FLL1_ENA, WM5100_FLL1_ENA);

	अगर (i2c->irq)
		समयout = 2;
	अन्यथा
		समयout = 50;

	snd_soc_component_update_bits(component, WM5100_CLOCKING_3, WM5100_SYSCLK_ENA,
			    WM5100_SYSCLK_ENA);

	/* Poll क्रम the lock; will use पूर्णांकerrupt when we can test */
	क्रम (i = 0; i < समयout; i++) अणु
		अगर (i2c->irq) अणु
			समय_left = रुको_क्रम_completion_समयout(&fll->lock,
							msecs_to_jअगरfies(25));
			अगर (समय_left > 0)
				अवरोध;
		पूर्ण अन्यथा अणु
			msleep(1);
		पूर्ण

		ret = snd_soc_component_पढ़ो(component,
				   WM5100_INTERRUPT_RAW_STATUS_3);
		अगर (ret < 0) अणु
			dev_err(component->dev,
				"Failed to read FLL status: %d\n",
				ret);
			जारी;
		पूर्ण
		अगर (ret & lock)
			अवरोध;
	पूर्ण
	अगर (i == समयout) अणु
		dev_err(component->dev, "FLL%d lock timed out\n", fll_id);
		pm_runसमय_put(component->dev);
		वापस -ETIMEDOUT;
	पूर्ण

	fll->src = source;
	fll->fref = Fref;
	fll->fout = Fout;

	dev_dbg(component->dev, "FLL%d running %dHz->%dHz\n", fll_id,
		Fref, Fout);

	वापस 0;
पूर्ण

/* Actually go much higher */
#घोषणा WM5100_RATES SNDRV_PCM_RATE_8000_192000

#घोषणा WM5100_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver wm5100_dai[] = अणु
	अणु
		.name = "wm5100-aif1",
		.base = WM5100_AUDIO_IF_1_1 - 1,
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 2,
			.channels_max = 2,
			.rates = WM5100_RATES,
			.क्रमmats = WM5100_FORMATS,
		पूर्ण,
		.capture = अणु
			 .stream_name = "AIF1 Capture",
			 .channels_min = 2,
			 .channels_max = 2,
			 .rates = WM5100_RATES,
			 .क्रमmats = WM5100_FORMATS,
		 पूर्ण,
		.ops = &wm5100_dai_ops,
	पूर्ण,
	अणु
		.name = "wm5100-aif2",
		.id = 1,
		.base = WM5100_AUDIO_IF_2_1 - 1,
		.playback = अणु
			.stream_name = "AIF2 Playback",
			.channels_min = 2,
			.channels_max = 2,
			.rates = WM5100_RATES,
			.क्रमmats = WM5100_FORMATS,
		पूर्ण,
		.capture = अणु
			 .stream_name = "AIF2 Capture",
			 .channels_min = 2,
			 .channels_max = 2,
			 .rates = WM5100_RATES,
			 .क्रमmats = WM5100_FORMATS,
		 पूर्ण,
		.ops = &wm5100_dai_ops,
	पूर्ण,
	अणु
		.name = "wm5100-aif3",
		.id = 2,
		.base = WM5100_AUDIO_IF_3_1 - 1,
		.playback = अणु
			.stream_name = "AIF3 Playback",
			.channels_min = 2,
			.channels_max = 2,
			.rates = WM5100_RATES,
			.क्रमmats = WM5100_FORMATS,
		पूर्ण,
		.capture = अणु
			 .stream_name = "AIF3 Capture",
			 .channels_min = 2,
			 .channels_max = 2,
			 .rates = WM5100_RATES,
			 .क्रमmats = WM5100_FORMATS,
		 पूर्ण,
		.ops = &wm5100_dai_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक wm5100_dig_vu[] = अणु
	WM5100_ADC_DIGITAL_VOLUME_1L,
	WM5100_ADC_DIGITAL_VOLUME_1R,
	WM5100_ADC_DIGITAL_VOLUME_2L,
	WM5100_ADC_DIGITAL_VOLUME_2R,
	WM5100_ADC_DIGITAL_VOLUME_3L,
	WM5100_ADC_DIGITAL_VOLUME_3R,
	WM5100_ADC_DIGITAL_VOLUME_4L,
	WM5100_ADC_DIGITAL_VOLUME_4R,

	WM5100_DAC_DIGITAL_VOLUME_1L,
	WM5100_DAC_DIGITAL_VOLUME_1R,
	WM5100_DAC_DIGITAL_VOLUME_2L,
	WM5100_DAC_DIGITAL_VOLUME_2R,
	WM5100_DAC_DIGITAL_VOLUME_3L,
	WM5100_DAC_DIGITAL_VOLUME_3R,
	WM5100_DAC_DIGITAL_VOLUME_4L,
	WM5100_DAC_DIGITAL_VOLUME_4R,
	WM5100_DAC_DIGITAL_VOLUME_5L,
	WM5100_DAC_DIGITAL_VOLUME_5R,
	WM5100_DAC_DIGITAL_VOLUME_6L,
	WM5100_DAC_DIGITAL_VOLUME_6R,
पूर्ण;

अटल व्योम wm5100_set_detect_mode(काष्ठा wm5100_priv *wm5100, पूर्णांक the_mode)
अणु
	काष्ठा wm5100_jack_mode *mode = &wm5100->pdata.jack_modes[the_mode];

	अगर (WARN_ON(the_mode >= ARRAY_SIZE(wm5100->pdata.jack_modes)))
		वापस;

	gpio_set_value_cansleep(wm5100->pdata.hp_pol, mode->hp_pol);
	regmap_update_bits(wm5100->regmap, WM5100_ACCESSORY_DETECT_MODE_1,
			   WM5100_ACCDET_BIAS_SRC_MASK |
			   WM5100_ACCDET_SRC,
			   (mode->bias << WM5100_ACCDET_BIAS_SRC_SHIFT) |
			   mode->micd_src << WM5100_ACCDET_SRC_SHIFT);
	regmap_update_bits(wm5100->regmap, WM5100_MISC_CONTROL,
			   WM5100_HPCOM_SRC,
			   mode->micd_src << WM5100_HPCOM_SRC_SHIFT);

	wm5100->jack_mode = the_mode;

	dev_dbg(wm5100->dev, "Set microphone polarity to %d\n",
		wm5100->jack_mode);
पूर्ण

अटल व्योम wm5100_report_headphone(काष्ठा wm5100_priv *wm5100)
अणु
	dev_dbg(wm5100->dev, "Headphone detected\n");
	wm5100->jack_detecting = false;
	snd_soc_jack_report(wm5100->jack, SND_JACK_HEADPHONE,
			    SND_JACK_HEADPHONE);

	/* Increase the detection rate a bit क्रम responsiveness. */
	regmap_update_bits(wm5100->regmap, WM5100_MIC_DETECT_1,
			   WM5100_ACCDET_RATE_MASK,
			   7 << WM5100_ACCDET_RATE_SHIFT);
पूर्ण

अटल व्योम wm5100_micd_irq(काष्ठा wm5100_priv *wm5100)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(wm5100->regmap, WM5100_MIC_DETECT_3, &val);
	अगर (ret != 0) अणु
		dev_err(wm5100->dev, "Failed to read microphone status: %d\n",
			ret);
		वापस;
	पूर्ण

	dev_dbg(wm5100->dev, "Microphone event: %x\n", val);

	अगर (!(val & WM5100_ACCDET_VALID)) अणु
		dev_warn(wm5100->dev, "Microphone detection state invalid\n");
		वापस;
	पूर्ण

	/* No accessory, reset everything and report removal */
	अगर (!(val & WM5100_ACCDET_STS)) अणु
		dev_dbg(wm5100->dev, "Jack removal detected\n");
		wm5100->jack_mic = false;
		wm5100->jack_detecting = true;
		wm5100->jack_flips = 0;
		snd_soc_jack_report(wm5100->jack, 0,
				    SND_JACK_LINEOUT | SND_JACK_HEADSET |
				    SND_JACK_BTN_0);

		regmap_update_bits(wm5100->regmap, WM5100_MIC_DETECT_1,
				   WM5100_ACCDET_RATE_MASK,
				   WM5100_ACCDET_RATE_MASK);
		वापस;
	पूर्ण

	/* If the measurement is very high we've got a microphone,
	 * either we just detected one or अगर we alपढ़ोy reported then
	 * we've got a button release event.
	 */
	अगर (val & 0x400) अणु
		अगर (wm5100->jack_detecting) अणु
			dev_dbg(wm5100->dev, "Microphone detected\n");
			wm5100->jack_mic = true;
			wm5100->jack_detecting = false;
			snd_soc_jack_report(wm5100->jack,
					    SND_JACK_HEADSET,
					    SND_JACK_HEADSET | SND_JACK_BTN_0);

			/* Increase poll rate to give better responsiveness
			 * क्रम buttons */
			regmap_update_bits(wm5100->regmap, WM5100_MIC_DETECT_1,
					   WM5100_ACCDET_RATE_MASK,
					   5 << WM5100_ACCDET_RATE_SHIFT);
		पूर्ण अन्यथा अणु
			dev_dbg(wm5100->dev, "Mic button up\n");
			snd_soc_jack_report(wm5100->jack, 0, SND_JACK_BTN_0);
		पूर्ण

		वापस;
	पूर्ण

	/* If we detected a lower impedence during initial startup
	 * then we probably have the wrong polarity, flip it.  Don't
	 * करो this क्रम the lowest impedences to speed up detection of
	 * plain headphones and give up अगर neither polarity looks
	 * sensible.
	 */
	अगर (wm5100->jack_detecting && (val & 0x3f8)) अणु
		wm5100->jack_flips++;

		अगर (wm5100->jack_flips > 1)
			wm5100_report_headphone(wm5100);
		अन्यथा
			wm5100_set_detect_mode(wm5100, !wm5100->jack_mode);

		वापस;
	पूर्ण

	/* Don't distinguish between buttons, just report any low
	 * impedence as BTN_0.
	 */
	अगर (val & 0x3fc) अणु
		अगर (wm5100->jack_mic) अणु
			dev_dbg(wm5100->dev, "Mic button detected\n");
			snd_soc_jack_report(wm5100->jack, SND_JACK_BTN_0,
					    SND_JACK_BTN_0);
		पूर्ण अन्यथा अगर (wm5100->jack_detecting) अणु
			wm5100_report_headphone(wm5100);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक wm5100_detect(काष्ठा snd_soc_component *component, काष्ठा snd_soc_jack *jack)
अणु
	काष्ठा wm5100_priv *wm5100 = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	अगर (jack) अणु
		wm5100->jack = jack;
		wm5100->jack_detecting = true;
		wm5100->jack_flips = 0;

		wm5100_set_detect_mode(wm5100, 0);

		/* Slowest detection rate, gives debounce क्रम initial
		 * detection */
		snd_soc_component_update_bits(component, WM5100_MIC_DETECT_1,
				    WM5100_ACCDET_BIAS_STARTTIME_MASK |
				    WM5100_ACCDET_RATE_MASK,
				    (7 << WM5100_ACCDET_BIAS_STARTTIME_SHIFT) |
				    WM5100_ACCDET_RATE_MASK);

		/* We need the अक्षरge pump to घातer MICBIAS */
		snd_soc_dapm_mutex_lock(dapm);

		snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "CP2");
		snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, "SYSCLK");

		snd_soc_dapm_sync_unlocked(dapm);

		snd_soc_dapm_mutex_unlock(dapm);

		/* We start off just enabling microphone detection - even a
		 * plain headphone will trigger detection.
		 */
		snd_soc_component_update_bits(component, WM5100_MIC_DETECT_1,
				    WM5100_ACCDET_ENA, WM5100_ACCDET_ENA);

		snd_soc_component_update_bits(component, WM5100_INTERRUPT_STATUS_3_MASK,
				    WM5100_IM_ACCDET_EINT, 0);
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component, WM5100_INTERRUPT_STATUS_3_MASK,
				    WM5100_IM_HPDET_EINT |
				    WM5100_IM_ACCDET_EINT,
				    WM5100_IM_HPDET_EINT |
				    WM5100_IM_ACCDET_EINT);
		snd_soc_component_update_bits(component, WM5100_MIC_DETECT_1,
				    WM5100_ACCDET_ENA, 0);
		wm5100->jack = शून्य;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm5100_detect);

अटल irqवापस_t wm5100_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm5100_priv *wm5100 = data;
	irqवापस_t status = IRQ_NONE;
	अचिन्हित पूर्णांक irq_val, mask_val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(wm5100->regmap, WM5100_INTERRUPT_STATUS_3, &irq_val);
	अगर (ret < 0) अणु
		dev_err(wm5100->dev, "Failed to read IRQ status 3: %d\n",
			ret);
		irq_val = 0;
	पूर्ण

	ret = regmap_पढ़ो(wm5100->regmap, WM5100_INTERRUPT_STATUS_3_MASK,
			  &mask_val);
	अगर (ret < 0) अणु
		dev_err(wm5100->dev, "Failed to read IRQ mask 3: %d\n",
			ret);
		mask_val = 0xffff;
	पूर्ण

	irq_val &= ~mask_val;

	regmap_ग_लिखो(wm5100->regmap, WM5100_INTERRUPT_STATUS_3, irq_val);

	अगर (irq_val)
		status = IRQ_HANDLED;

	wm5100_log_status3(wm5100, irq_val);

	अगर (irq_val & WM5100_FLL1_LOCK_EINT) अणु
		dev_dbg(wm5100->dev, "FLL1 locked\n");
		complete(&wm5100->fll[0].lock);
	पूर्ण
	अगर (irq_val & WM5100_FLL2_LOCK_EINT) अणु
		dev_dbg(wm5100->dev, "FLL2 locked\n");
		complete(&wm5100->fll[1].lock);
	पूर्ण

	अगर (irq_val & WM5100_ACCDET_EINT)
		wm5100_micd_irq(wm5100);

	ret = regmap_पढ़ो(wm5100->regmap, WM5100_INTERRUPT_STATUS_4, &irq_val);
	अगर (ret < 0) अणु
		dev_err(wm5100->dev, "Failed to read IRQ status 4: %d\n",
			ret);
		irq_val = 0;
	पूर्ण

	ret = regmap_पढ़ो(wm5100->regmap, WM5100_INTERRUPT_STATUS_4_MASK,
			  &mask_val);
	अगर (ret < 0) अणु
		dev_err(wm5100->dev, "Failed to read IRQ mask 4: %d\n",
			ret);
		mask_val = 0xffff;
	पूर्ण

	irq_val &= ~mask_val;

	अगर (irq_val)
		status = IRQ_HANDLED;

	regmap_ग_लिखो(wm5100->regmap, WM5100_INTERRUPT_STATUS_4, irq_val);

	wm5100_log_status4(wm5100, irq_val);

	वापस status;
पूर्ण

अटल irqवापस_t wm5100_edge_irq(पूर्णांक irq, व्योम *data)
अणु
	irqवापस_t ret = IRQ_NONE;
	irqवापस_t val;

	करो अणु
		val = wm5100_irq(irq, data);
		अगर (val != IRQ_NONE)
			ret = val;
	पूर्ण जबतक (val != IRQ_NONE);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_GPIOLIB
अटल व्योम wm5100_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा wm5100_priv *wm5100 = gpiochip_get_data(chip);

	regmap_update_bits(wm5100->regmap, WM5100_GPIO_CTRL_1 + offset,
			   WM5100_GP1_LVL, !!value << WM5100_GP1_LVL_SHIFT);
पूर्ण

अटल पूर्णांक wm5100_gpio_direction_out(काष्ठा gpio_chip *chip,
				     अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा wm5100_priv *wm5100 = gpiochip_get_data(chip);
	पूर्णांक val, ret;

	val = (1 << WM5100_GP1_FN_SHIFT) | (!!value << WM5100_GP1_LVL_SHIFT);

	ret = regmap_update_bits(wm5100->regmap, WM5100_GPIO_CTRL_1 + offset,
				 WM5100_GP1_FN_MASK | WM5100_GP1_सूची |
				 WM5100_GP1_LVL, val);
	अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक wm5100_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा wm5100_priv *wm5100 = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	ret = regmap_पढ़ो(wm5100->regmap, WM5100_GPIO_CTRL_1 + offset, &reg);
	अगर (ret < 0)
		वापस ret;

	वापस (reg & WM5100_GP1_LVL) != 0;
पूर्ण

अटल पूर्णांक wm5100_gpio_direction_in(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा wm5100_priv *wm5100 = gpiochip_get_data(chip);

	वापस regmap_update_bits(wm5100->regmap, WM5100_GPIO_CTRL_1 + offset,
				  WM5100_GP1_FN_MASK | WM5100_GP1_सूची,
				  (1 << WM5100_GP1_FN_SHIFT) |
				  (1 << WM5100_GP1_सूची_SHIFT));
पूर्ण

अटल स्थिर काष्ठा gpio_chip wm5100_ढाँचा_chip = अणु
	.label			= "wm5100",
	.owner			= THIS_MODULE,
	.direction_output	= wm5100_gpio_direction_out,
	.set			= wm5100_gpio_set,
	.direction_input	= wm5100_gpio_direction_in,
	.get			= wm5100_gpio_get,
	.can_sleep		= 1,
पूर्ण;

अटल व्योम wm5100_init_gpio(काष्ठा i2c_client *i2c)
अणु
	काष्ठा wm5100_priv *wm5100 = i2c_get_clientdata(i2c);
	पूर्णांक ret;

	wm5100->gpio_chip = wm5100_ढाँचा_chip;
	wm5100->gpio_chip.ngpio = 6;
	wm5100->gpio_chip.parent = &i2c->dev;

	अगर (wm5100->pdata.gpio_base)
		wm5100->gpio_chip.base = wm5100->pdata.gpio_base;
	अन्यथा
		wm5100->gpio_chip.base = -1;

	ret = gpiochip_add_data(&wm5100->gpio_chip, wm5100);
	अगर (ret != 0)
		dev_err(&i2c->dev, "Failed to add GPIOs: %d\n", ret);
पूर्ण

अटल व्योम wm5100_मुक्त_gpio(काष्ठा i2c_client *i2c)
अणु
	काष्ठा wm5100_priv *wm5100 = i2c_get_clientdata(i2c);

	gpiochip_हटाओ(&wm5100->gpio_chip);
पूर्ण
#अन्यथा
अटल व्योम wm5100_init_gpio(काष्ठा i2c_client *i2c)
अणु
पूर्ण

अटल व्योम wm5100_मुक्त_gpio(काष्ठा i2c_client *i2c)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक wm5100_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा i2c_client *i2c = to_i2c_client(component->dev);
	काष्ठा wm5100_priv *wm5100 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret, i;

	wm5100->component = component;

	क्रम (i = 0; i < ARRAY_SIZE(wm5100_dig_vu); i++)
		snd_soc_component_update_bits(component, wm5100_dig_vu[i], WM5100_OUT_VU,
				    WM5100_OUT_VU);

	/* Don't debounce पूर्णांकerrupts to support use of SYSCLK only */
	snd_soc_component_ग_लिखो(component, WM5100_IRQ_DEBOUNCE_1, 0);
	snd_soc_component_ग_लिखो(component, WM5100_IRQ_DEBOUNCE_2, 0);

	/* TODO: check अगर we're symmetric */

	अगर (i2c->irq)
		snd_soc_dapm_new_controls(dapm, wm5100_dapm_widमाला_लो_noirq,
					  ARRAY_SIZE(wm5100_dapm_widमाला_लो_noirq));

	अगर (wm5100->pdata.hp_pol) अणु
		ret = gpio_request_one(wm5100->pdata.hp_pol,
				       GPIOF_OUT_INIT_HIGH, "WM5100 HP_POL");
		अगर (ret < 0) अणु
			dev_err(&i2c->dev, "Failed to request HP_POL %d: %d\n",
				wm5100->pdata.hp_pol, ret);
			जाओ err_gpio;
		पूर्ण
	पूर्ण

	वापस 0;

err_gpio:

	वापस ret;
पूर्ण

अटल व्योम wm5100_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm5100_priv *wm5100 = snd_soc_component_get_drvdata(component);

	अगर (wm5100->pdata.hp_pol) अणु
		gpio_मुक्त(wm5100->pdata.hp_pol);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm5100 = अणु
	.probe			= wm5100_probe,
	.हटाओ			= wm5100_हटाओ,
	.set_sysclk		= wm5100_set_sysclk,
	.set_pll		= wm5100_set_fll,
	.seq_notअगरier		= wm5100_seq_notअगरier,
	.controls		= wm5100_snd_controls,
	.num_controls		= ARRAY_SIZE(wm5100_snd_controls),
	.dapm_widमाला_लो		= wm5100_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm5100_dapm_widमाला_लो),
	.dapm_routes		= wm5100_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm5100_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm5100_regmap = अणु
	.reg_bits = 16,
	.val_bits = 16,

	.max_रेजिस्टर = WM5100_MAX_REGISTER,
	.reg_शेषs = wm5100_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm5100_reg_शेषs),
	.अस्थिर_reg = wm5100_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = wm5100_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक wm5100_mic_ctrl_reg[] = अणु
	WM5100_IN1L_CONTROL,
	WM5100_IN2L_CONTROL,
	WM5100_IN3L_CONTROL,
	WM5100_IN4L_CONTROL,
पूर्ण;

अटल पूर्णांक wm5100_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm5100_pdata *pdata = dev_get_platdata(&i2c->dev);
	काष्ठा wm5100_priv *wm5100;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret, i, irq_flags;

	wm5100 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm5100_priv),
			      GFP_KERNEL);
	अगर (wm5100 == शून्य)
		वापस -ENOMEM;

	wm5100->dev = &i2c->dev;

	wm5100->regmap = devm_regmap_init_i2c(i2c, &wm5100_regmap);
	अगर (IS_ERR(wm5100->regmap)) अणु
		ret = PTR_ERR(wm5100->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(wm5100->fll); i++)
		init_completion(&wm5100->fll[i].lock);

	अगर (pdata)
		wm5100->pdata = *pdata;

	i2c_set_clientdata(i2c, wm5100);

	क्रम (i = 0; i < ARRAY_SIZE(wm5100->core_supplies); i++)
		wm5100->core_supplies[i].supply = wm5100_core_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev,
				      ARRAY_SIZE(wm5100->core_supplies),
				      wm5100->core_supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to request core supplies: %d\n",
			ret);
		जाओ err;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(wm5100->core_supplies),
				    wm5100->core_supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to enable core supplies: %d\n",
			ret);
		जाओ err;
	पूर्ण

	अगर (wm5100->pdata.lकरो_ena) अणु
		ret = gpio_request_one(wm5100->pdata.lकरो_ena,
				       GPIOF_OUT_INIT_HIGH, "WM5100 LDOENA");
		अगर (ret < 0) अणु
			dev_err(&i2c->dev, "Failed to request LDOENA %d: %d\n",
				wm5100->pdata.lकरो_ena, ret);
			जाओ err_enable;
		पूर्ण
		msleep(2);
	पूर्ण

	अगर (wm5100->pdata.reset) अणु
		ret = gpio_request_one(wm5100->pdata.reset,
				       GPIOF_OUT_INIT_HIGH, "WM5100 /RESET");
		अगर (ret < 0) अणु
			dev_err(&i2c->dev, "Failed to request /RESET %d: %d\n",
				wm5100->pdata.reset, ret);
			जाओ err_lकरो;
		पूर्ण
	पूर्ण

	ret = regmap_पढ़ो(wm5100->regmap, WM5100_SOFTWARE_RESET, &reg);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to read ID register: %d\n", ret);
		जाओ err_reset;
	पूर्ण
	चयन (reg) अणु
	हाल 0x8997:
	हाल 0x5100:
		अवरोध;

	शेष:
		dev_err(&i2c->dev, "Device is not a WM5100, ID is %x\n", reg);
		ret = -EINVAL;
		जाओ err_reset;
	पूर्ण

	ret = regmap_पढ़ो(wm5100->regmap, WM5100_DEVICE_REVISION, &reg);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to read revision register\n");
		जाओ err_reset;
	पूर्ण
	wm5100->rev = reg & WM5100_DEVICE_REVISION_MASK;

	dev_info(&i2c->dev, "revision %c\n", wm5100->rev + 'A');

	ret = wm5100_reset(wm5100);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to issue reset\n");
		जाओ err_reset;
	पूर्ण

	चयन (wm5100->rev) अणु
	हाल 0:
		ret = regmap_रेजिस्टर_patch(wm5100->regmap,
					    wm5100_reva_patches,
					    ARRAY_SIZE(wm5100_reva_patches));
		अगर (ret != 0) अणु
			dev_err(&i2c->dev, "Failed to register patches: %d\n",
				ret);
			जाओ err_reset;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण


	wm5100_init_gpio(i2c);

	क्रम (i = 0; i < ARRAY_SIZE(wm5100->pdata.gpio_शेषs); i++) अणु
		अगर (!wm5100->pdata.gpio_शेषs[i])
			जारी;

		regmap_ग_लिखो(wm5100->regmap, WM5100_GPIO_CTRL_1 + i,
			     wm5100->pdata.gpio_शेषs[i]);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(wm5100->pdata.in_mode); i++) अणु
		regmap_update_bits(wm5100->regmap, wm5100_mic_ctrl_reg[i],
				   WM5100_IN1_MODE_MASK |
				   WM5100_IN1_DMIC_SUP_MASK,
				   (wm5100->pdata.in_mode[i] <<
				    WM5100_IN1_MODE_SHIFT) |
				   (wm5100->pdata.dmic_sup[i] <<
				    WM5100_IN1_DMIC_SUP_SHIFT));
	पूर्ण

	अगर (i2c->irq) अणु
		अगर (wm5100->pdata.irq_flags)
			irq_flags = wm5100->pdata.irq_flags;
		अन्यथा
			irq_flags = IRQF_TRIGGER_LOW;

		irq_flags |= IRQF_ONESHOT;

		अगर (irq_flags & (IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING))
			ret = request_thपढ़ोed_irq(i2c->irq, शून्य,
						   wm5100_edge_irq, irq_flags,
						   "wm5100", wm5100);
		अन्यथा
			ret = request_thपढ़ोed_irq(i2c->irq, शून्य, wm5100_irq,
						   irq_flags, "wm5100",
						   wm5100);

		अगर (ret != 0) अणु
			dev_err(&i2c->dev, "Failed to request IRQ %d: %d\n",
				i2c->irq, ret);
		पूर्ण अन्यथा अणु
			/* Enable शेष पूर्णांकerrupts */
			regmap_update_bits(wm5100->regmap,
					   WM5100_INTERRUPT_STATUS_3_MASK,
					   WM5100_IM_SPK_SHUTDOWN_WARN_EINT |
					   WM5100_IM_SPK_SHUTDOWN_EINT |
					   WM5100_IM_ASRC2_LOCK_EINT |
					   WM5100_IM_ASRC1_LOCK_EINT |
					   WM5100_IM_FLL2_LOCK_EINT |
					   WM5100_IM_FLL1_LOCK_EINT |
					   WM5100_CLKGEN_ERR_EINT |
					   WM5100_CLKGEN_ERR_ASYNC_EINT, 0);

			regmap_update_bits(wm5100->regmap,
					   WM5100_INTERRUPT_STATUS_4_MASK,
					   WM5100_AIF3_ERR_EINT |
					   WM5100_AIF2_ERR_EINT |
					   WM5100_AIF1_ERR_EINT |
					   WM5100_CTRLIF_ERR_EINT |
					   WM5100_ISRC2_UNDERCLOCKED_EINT |
					   WM5100_ISRC1_UNDERCLOCKED_EINT |
					   WM5100_FX_UNDERCLOCKED_EINT |
					   WM5100_AIF3_UNDERCLOCKED_EINT |
					   WM5100_AIF2_UNDERCLOCKED_EINT |
					   WM5100_AIF1_UNDERCLOCKED_EINT |
					   WM5100_ASRC_UNDERCLOCKED_EINT |
					   WM5100_DAC_UNDERCLOCKED_EINT |
					   WM5100_ADC_UNDERCLOCKED_EINT |
					   WM5100_MIXER_UNDERCLOCKED_EINT, 0);
		पूर्ण
	पूर्ण

	pm_runसमय_set_active(&i2c->dev);
	pm_runसमय_enable(&i2c->dev);
	pm_request_idle(&i2c->dev);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				     &soc_component_dev_wm5100, wm5100_dai,
				     ARRAY_SIZE(wm5100_dai));
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to register WM5100: %d\n", ret);
		जाओ err_reset;
	पूर्ण

	वापस ret;

err_reset:
	pm_runसमय_disable(&i2c->dev);
	अगर (i2c->irq)
		मुक्त_irq(i2c->irq, wm5100);
	wm5100_मुक्त_gpio(i2c);
	अगर (wm5100->pdata.reset) अणु
		gpio_set_value_cansleep(wm5100->pdata.reset, 0);
		gpio_मुक्त(wm5100->pdata.reset);
	पूर्ण
err_lकरो:
	अगर (wm5100->pdata.lकरो_ena) अणु
		gpio_set_value_cansleep(wm5100->pdata.lकरो_ena, 0);
		gpio_मुक्त(wm5100->pdata.lकरो_ena);
	पूर्ण
err_enable:
	regulator_bulk_disable(ARRAY_SIZE(wm5100->core_supplies),
			       wm5100->core_supplies);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक wm5100_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा wm5100_priv *wm5100 = i2c_get_clientdata(i2c);

	pm_runसमय_disable(&i2c->dev);
	अगर (i2c->irq)
		मुक्त_irq(i2c->irq, wm5100);
	wm5100_मुक्त_gpio(i2c);
	अगर (wm5100->pdata.reset) अणु
		gpio_set_value_cansleep(wm5100->pdata.reset, 0);
		gpio_मुक्त(wm5100->pdata.reset);
	पूर्ण
	अगर (wm5100->pdata.lकरो_ena) अणु
		gpio_set_value_cansleep(wm5100->pdata.lकरो_ena, 0);
		gpio_मुक्त(wm5100->pdata.lकरो_ena);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक wm5100_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा wm5100_priv *wm5100 = dev_get_drvdata(dev);

	regcache_cache_only(wm5100->regmap, true);
	regcache_mark_dirty(wm5100->regmap);
	अगर (wm5100->pdata.lकरो_ena)
		gpio_set_value_cansleep(wm5100->pdata.lकरो_ena, 0);
	regulator_bulk_disable(ARRAY_SIZE(wm5100->core_supplies),
			       wm5100->core_supplies);

	वापस 0;
पूर्ण

अटल पूर्णांक wm5100_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा wm5100_priv *wm5100 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(wm5100->core_supplies),
				    wm5100->core_supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to enable supplies: %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (wm5100->pdata.lकरो_ena) अणु
		gpio_set_value_cansleep(wm5100->pdata.lकरो_ena, 1);
		msleep(2);
	पूर्ण

	regcache_cache_only(wm5100->regmap, false);
	regcache_sync(wm5100->regmap);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops wm5100_pm = अणु
	SET_RUNTIME_PM_OPS(wm5100_runसमय_suspend, wm5100_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id wm5100_i2c_id[] = अणु
	अणु "wm5100", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm5100_i2c_id);

अटल काष्ठा i2c_driver wm5100_i2c_driver = अणु
	.driver = अणु
		.name = "wm5100",
		.pm = &wm5100_pm,
	पूर्ण,
	.probe =    wm5100_i2c_probe,
	.हटाओ =   wm5100_i2c_हटाओ,
	.id_table = wm5100_i2c_id,
पूर्ण;

module_i2c_driver(wm5100_i2c_driver);

MODULE_DESCRIPTION("ASoC WM5100 driver");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
