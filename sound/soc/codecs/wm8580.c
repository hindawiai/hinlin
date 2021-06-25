<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm8580.c  --  WM8580 and WM8581 ALSA Soc Audio driver
 *
 * Copyright 2008-12 Wolfson Microelectronics PLC.
 *
 * Notes:
 *  The WM8580 is a multichannel codec with S/PDIF support, featuring six
 *  DAC channels and two ADC channels.
 *
 *  The WM8581 is a multichannel codec with S/PDIF support, featuring eight
 *  DAC channels and two ADC channels.
 *
 *  Currently only the primary audio पूर्णांकerface is supported - S/PDIF and
 *  the secondary audio पूर्णांकerfaces are not.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_device.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <sound/initval.h>
#समावेश <यंत्र/भाग64.h>

#समावेश "wm8580.h"

/* WM8580 रेजिस्टर space */
#घोषणा WM8580_PLLA1                         0x00
#घोषणा WM8580_PLLA2                         0x01
#घोषणा WM8580_PLLA3                         0x02
#घोषणा WM8580_PLLA4                         0x03
#घोषणा WM8580_PLLB1                         0x04
#घोषणा WM8580_PLLB2                         0x05
#घोषणा WM8580_PLLB3                         0x06
#घोषणा WM8580_PLLB4                         0x07
#घोषणा WM8580_CLKSEL                        0x08
#घोषणा WM8580_PAIF1                         0x09
#घोषणा WM8580_PAIF2                         0x0A
#घोषणा WM8580_SAIF1                         0x0B
#घोषणा WM8580_PAIF3                         0x0C
#घोषणा WM8580_PAIF4                         0x0D
#घोषणा WM8580_SAIF2                         0x0E
#घोषणा WM8580_DAC_CONTROL1                  0x0F
#घोषणा WM8580_DAC_CONTROL2                  0x10
#घोषणा WM8580_DAC_CONTROL3                  0x11
#घोषणा WM8580_DAC_CONTROL4                  0x12
#घोषणा WM8580_DAC_CONTROL5                  0x13
#घोषणा WM8580_DIGITAL_ATTENUATION_DACL1     0x14
#घोषणा WM8580_DIGITAL_ATTENUATION_DACR1     0x15
#घोषणा WM8580_DIGITAL_ATTENUATION_DACL2     0x16
#घोषणा WM8580_DIGITAL_ATTENUATION_DACR2     0x17
#घोषणा WM8580_DIGITAL_ATTENUATION_DACL3     0x18
#घोषणा WM8580_DIGITAL_ATTENUATION_DACR3     0x19
#घोषणा WM8581_DIGITAL_ATTENUATION_DACL4     0x1A
#घोषणा WM8581_DIGITAL_ATTENUATION_DACR4     0x1B
#घोषणा WM8580_MASTER_DIGITAL_ATTENUATION    0x1C
#घोषणा WM8580_ADC_CONTROL1                  0x1D
#घोषणा WM8580_SPDTXCHAN0                    0x1E
#घोषणा WM8580_SPDTXCHAN1                    0x1F
#घोषणा WM8580_SPDTXCHAN2                    0x20
#घोषणा WM8580_SPDTXCHAN3                    0x21
#घोषणा WM8580_SPDTXCHAN4                    0x22
#घोषणा WM8580_SPDTXCHAN5                    0x23
#घोषणा WM8580_SPDMODE                       0x24
#घोषणा WM8580_INTMASK                       0x25
#घोषणा WM8580_GPO1                          0x26
#घोषणा WM8580_GPO2                          0x27
#घोषणा WM8580_GPO3                          0x28
#घोषणा WM8580_GPO4                          0x29
#घोषणा WM8580_GPO5                          0x2A
#घोषणा WM8580_INTSTAT                       0x2B
#घोषणा WM8580_SPDRXCHAN1                    0x2C
#घोषणा WM8580_SPDRXCHAN2                    0x2D
#घोषणा WM8580_SPDRXCHAN3                    0x2E
#घोषणा WM8580_SPDRXCHAN4                    0x2F
#घोषणा WM8580_SPDRXCHAN5                    0x30
#घोषणा WM8580_SPDSTAT                       0x31
#घोषणा WM8580_PWRDN1                        0x32
#घोषणा WM8580_PWRDN2                        0x33
#घोषणा WM8580_READBACK                      0x34
#घोषणा WM8580_RESET                         0x35

#घोषणा WM8580_MAX_REGISTER                  0x35

#घोषणा WM8580_DACOSR 0x40

/* PLLB4 (रेजिस्टर 7h) */
#घोषणा WM8580_PLLB4_MCLKOUTSRC_MASK   0x60
#घोषणा WM8580_PLLB4_MCLKOUTSRC_PLLA   0x20
#घोषणा WM8580_PLLB4_MCLKOUTSRC_PLLB   0x40
#घोषणा WM8580_PLLB4_MCLKOUTSRC_OSC    0x60

#घोषणा WM8580_PLLB4_CLKOUTSRC_MASK    0x180
#घोषणा WM8580_PLLB4_CLKOUTSRC_PLLACLK 0x080
#घोषणा WM8580_PLLB4_CLKOUTSRC_PLLBCLK 0x100
#घोषणा WM8580_PLLB4_CLKOUTSRC_OSCCLK  0x180

/* CLKSEL (रेजिस्टर 8h) */
#घोषणा WM8580_CLKSEL_DAC_CLKSEL_MASK 0x03
#घोषणा WM8580_CLKSEL_DAC_CLKSEL_PLLA 0x01
#घोषणा WM8580_CLKSEL_DAC_CLKSEL_PLLB 0x02

/* AIF control 1 (रेजिस्टरs 9h-bh) */
#घोषणा WM8580_AIF_RATE_MASK       0x7
#घोषणा WM8580_AIF_BCLKSEL_MASK   0x18

#घोषणा WM8580_AIF_MS             0x20

#घोषणा WM8580_AIF_CLKSRC_MASK    0xc0
#घोषणा WM8580_AIF_CLKSRC_PLLA    0x40
#घोषणा WM8580_AIF_CLKSRC_PLLB    0x40
#घोषणा WM8580_AIF_CLKSRC_MCLK    0xc0

/* AIF control 2 (रेजिस्टरs ch-eh) */
#घोषणा WM8580_AIF_FMT_MASK    0x03
#घोषणा WM8580_AIF_FMT_RIGHTJ  0x00
#घोषणा WM8580_AIF_FMT_LEFTJ   0x01
#घोषणा WM8580_AIF_FMT_I2S     0x02
#घोषणा WM8580_AIF_FMT_DSP     0x03

#घोषणा WM8580_AIF_LENGTH_MASK   0x0c
#घोषणा WM8580_AIF_LENGTH_16     0x00
#घोषणा WM8580_AIF_LENGTH_20     0x04
#घोषणा WM8580_AIF_LENGTH_24     0x08
#घोषणा WM8580_AIF_LENGTH_32     0x0c

#घोषणा WM8580_AIF_LRP         0x10
#घोषणा WM8580_AIF_BCP         0x20

/* Powerकरोwn Register 1 (रेजिस्टर 32h) */
#घोषणा WM8580_PWRDN1_PWDN     0x001
#घोषणा WM8580_PWRDN1_ALLDACPD 0x040

/* Powerकरोwn Register 2 (रेजिस्टर 33h) */
#घोषणा WM8580_PWRDN2_OSSCPD   0x001
#घोषणा WM8580_PWRDN2_PLLAPD   0x002
#घोषणा WM8580_PWRDN2_PLLBPD   0x004
#घोषणा WM8580_PWRDN2_SPDIFPD  0x008
#घोषणा WM8580_PWRDN2_SPDIFTXD 0x010
#घोषणा WM8580_PWRDN2_SPDIFRXD 0x020

#घोषणा WM8580_DAC_CONTROL5_MUTEALL 0x10

/*
 * wm8580 रेजिस्टर cache
 * We can't पढ़ो the WM8580 रेजिस्टर space when we
 * are using 2 wire क्रम device control, so we cache them instead.
 */
अटल स्थिर काष्ठा reg_शेष wm8580_reg_शेषs[] = अणु
	अणु  0, 0x0121 पूर्ण,
	अणु  1, 0x017e पूर्ण,
	अणु  2, 0x007d पूर्ण,
	अणु  3, 0x0014 पूर्ण,
	अणु  4, 0x0121 पूर्ण,
	अणु  5, 0x017e पूर्ण,
	अणु  6, 0x007d पूर्ण,
	अणु  7, 0x0194 पूर्ण,
	अणु  8, 0x0010 पूर्ण,
	अणु  9, 0x0002 पूर्ण,
	अणु 10, 0x0002 पूर्ण,
	अणु 11, 0x00c2 पूर्ण,
	अणु 12, 0x0182 पूर्ण,
	अणु 13, 0x0082 पूर्ण,
	अणु 14, 0x000a पूर्ण,
	अणु 15, 0x0024 पूर्ण,
	अणु 16, 0x0009 पूर्ण,
	अणु 17, 0x0000 पूर्ण,
	अणु 18, 0x00ff पूर्ण,
	अणु 19, 0x0000 पूर्ण,
	अणु 20, 0x00ff पूर्ण,
	अणु 21, 0x00ff पूर्ण,
	अणु 22, 0x00ff पूर्ण,
	अणु 23, 0x00ff पूर्ण,
	अणु 24, 0x00ff पूर्ण,
	अणु 25, 0x00ff पूर्ण,
	अणु 26, 0x00ff पूर्ण,
	अणु 27, 0x00ff पूर्ण,
	अणु 28, 0x01f0 पूर्ण,
	अणु 29, 0x0040 पूर्ण,
	अणु 30, 0x0000 पूर्ण,
	अणु 31, 0x0000 पूर्ण,
	अणु 32, 0x0000 पूर्ण,
	अणु 33, 0x0000 पूर्ण,
	अणु 34, 0x0031 पूर्ण,
	अणु 35, 0x000b पूर्ण,
	अणु 36, 0x0039 पूर्ण,
	अणु 37, 0x0000 पूर्ण,
	अणु 38, 0x0010 पूर्ण,
	अणु 39, 0x0032 पूर्ण,
	अणु 40, 0x0054 पूर्ण,
	अणु 41, 0x0076 पूर्ण,
	अणु 42, 0x0098 पूर्ण,
	अणु 43, 0x0000 पूर्ण,
	अणु 44, 0x0000 पूर्ण,
	अणु 45, 0x0000 पूर्ण,
	अणु 46, 0x0000 पूर्ण,
	अणु 47, 0x0000 पूर्ण,
	अणु 48, 0x0000 पूर्ण,
	अणु 49, 0x0000 पूर्ण,
	अणु 50, 0x005e पूर्ण,
	अणु 51, 0x003e पूर्ण,
	अणु 52, 0x0000 पूर्ण,
पूर्ण;

अटल bool wm8580_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8580_RESET:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

काष्ठा pll_state अणु
	अचिन्हित पूर्णांक in;
	अचिन्हित पूर्णांक out;
पूर्ण;

#घोषणा WM8580_NUM_SUPPLIES 3
अटल स्थिर अक्षर *wm8580_supply_names[WM8580_NUM_SUPPLIES] = अणु
	"AVDD",
	"DVDD",
	"PVDD",
पूर्ण;

काष्ठा wm8580_driver_data अणु
	पूर्णांक num_dacs;
पूर्ण;

/* codec निजी data */
काष्ठा wm8580_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data supplies[WM8580_NUM_SUPPLIES];
	काष्ठा pll_state a;
	काष्ठा pll_state b;
	स्थिर काष्ठा wm8580_driver_data *drvdata;
	पूर्णांक sysclk[2];
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(dac_tlv, -12750, 50, 1);

अटल पूर्णांक wm8580_out_vu(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8580_priv *wm8580 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg = mc->reg;
	अचिन्हित पूर्णांक reg2 = mc->rreg;
	पूर्णांक ret;

	/* Clear the रेजिस्टर cache VU so we ग_लिखो without VU set */
	regcache_cache_only(wm8580->regmap, true);
	regmap_update_bits(wm8580->regmap, reg, 0x100, 0x000);
	regmap_update_bits(wm8580->regmap, reg2, 0x100, 0x000);
	regcache_cache_only(wm8580->regmap, false);

	ret = snd_soc_put_volsw(kcontrol, ucontrol);
	अगर (ret < 0)
		वापस ret;

	/* Now ग_लिखो again with the volume update bit set */
	snd_soc_component_update_bits(component, reg, 0x100, 0x100);
	snd_soc_component_update_bits(component, reg2, 0x100, 0x100);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new wm8580_snd_controls[] = अणु
SOC_DOUBLE_R_EXT_TLV("DAC1 Playback Volume",
		     WM8580_DIGITAL_ATTENUATION_DACL1,
		     WM8580_DIGITAL_ATTENUATION_DACR1,
		     0, 0xff, 0, snd_soc_get_volsw, wm8580_out_vu, dac_tlv),
SOC_DOUBLE_R_EXT_TLV("DAC2 Playback Volume",
		     WM8580_DIGITAL_ATTENUATION_DACL2,
		     WM8580_DIGITAL_ATTENUATION_DACR2,
		     0, 0xff, 0, snd_soc_get_volsw, wm8580_out_vu, dac_tlv),
SOC_DOUBLE_R_EXT_TLV("DAC3 Playback Volume",
		     WM8580_DIGITAL_ATTENUATION_DACL3,
		     WM8580_DIGITAL_ATTENUATION_DACR3,
		     0, 0xff, 0, snd_soc_get_volsw, wm8580_out_vu, dac_tlv),

SOC_SINGLE("DAC1 Deemphasis Switch", WM8580_DAC_CONTROL3, 0, 1, 0),
SOC_SINGLE("DAC2 Deemphasis Switch", WM8580_DAC_CONTROL3, 1, 1, 0),
SOC_SINGLE("DAC3 Deemphasis Switch", WM8580_DAC_CONTROL3, 2, 1, 0),

SOC_DOUBLE("DAC1 Invert Switch", WM8580_DAC_CONTROL4,  0, 1, 1, 0),
SOC_DOUBLE("DAC2 Invert Switch", WM8580_DAC_CONTROL4,  2, 3, 1, 0),
SOC_DOUBLE("DAC3 Invert Switch", WM8580_DAC_CONTROL4,  4, 5, 1, 0),

SOC_SINGLE("DAC ZC Switch", WM8580_DAC_CONTROL5, 5, 1, 0),
SOC_SINGLE("DAC1 Switch", WM8580_DAC_CONTROL5, 0, 1, 1),
SOC_SINGLE("DAC2 Switch", WM8580_DAC_CONTROL5, 1, 1, 1),
SOC_SINGLE("DAC3 Switch", WM8580_DAC_CONTROL5, 2, 1, 1),

SOC_DOUBLE("Capture Switch", WM8580_ADC_CONTROL1, 0, 1, 1, 1),
SOC_SINGLE("Capture High-Pass Filter Switch", WM8580_ADC_CONTROL1, 4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8581_snd_controls[] = अणु
SOC_DOUBLE_R_EXT_TLV("DAC4 Playback Volume",
		     WM8581_DIGITAL_ATTENUATION_DACL4,
		     WM8581_DIGITAL_ATTENUATION_DACR4,
		     0, 0xff, 0, snd_soc_get_volsw, wm8580_out_vu, dac_tlv),

SOC_SINGLE("DAC4 Deemphasis Switch", WM8580_DAC_CONTROL3, 3, 1, 0),

SOC_DOUBLE("DAC4 Invert Switch", WM8580_DAC_CONTROL4,  8, 7, 1, 0),

SOC_SINGLE("DAC4 Switch", WM8580_DAC_CONTROL5, 3, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8580_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_DAC("DAC1", "Playback", WM8580_PWRDN1, 2, 1),
SND_SOC_DAPM_DAC("DAC2", "Playback", WM8580_PWRDN1, 3, 1),
SND_SOC_DAPM_DAC("DAC3", "Playback", WM8580_PWRDN1, 4, 1),

SND_SOC_DAPM_OUTPUT("VOUT1L"),
SND_SOC_DAPM_OUTPUT("VOUT1R"),
SND_SOC_DAPM_OUTPUT("VOUT2L"),
SND_SOC_DAPM_OUTPUT("VOUT2R"),
SND_SOC_DAPM_OUTPUT("VOUT3L"),
SND_SOC_DAPM_OUTPUT("VOUT3R"),

SND_SOC_DAPM_ADC("ADC", "Capture", WM8580_PWRDN1, 1, 1),

SND_SOC_DAPM_INPUT("AINL"),
SND_SOC_DAPM_INPUT("AINR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8581_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_DAC("DAC4", "Playback", WM8580_PWRDN1, 5, 1),

SND_SOC_DAPM_OUTPUT("VOUT4L"),
SND_SOC_DAPM_OUTPUT("VOUT4R"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8580_dapm_routes[] = अणु
	अणु "VOUT1L", शून्य, "DAC1" पूर्ण,
	अणु "VOUT1R", शून्य, "DAC1" पूर्ण,

	अणु "VOUT2L", शून्य, "DAC2" पूर्ण,
	अणु "VOUT2R", शून्य, "DAC2" पूर्ण,

	अणु "VOUT3L", शून्य, "DAC3" पूर्ण,
	अणु "VOUT3R", शून्य, "DAC3" पूर्ण,

	अणु "ADC", शून्य, "AINL" पूर्ण,
	अणु "ADC", शून्य, "AINR" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8581_dapm_routes[] = अणु
	अणु "VOUT4L", शून्य, "DAC4" पूर्ण,
	अणु "VOUT4R", शून्य, "DAC4" पूर्ण,
पूर्ण;

/* PLL भागisors */
काष्ठा _pll_भाग अणु
	u32 prescale:1;
	u32 postscale:1;
	u32 freqmode:2;
	u32 n:4;
	u32 k:24;
पूर्ण;

/* The size in bits of the pll भागide */
#घोषणा FIXED_PLL_SIZE (1 << 22)

/* PLL rate to output rate भागisions */
अटल काष्ठा अणु
	अचिन्हित पूर्णांक भाग;
	अचिन्हित पूर्णांक freqmode;
	अचिन्हित पूर्णांक postscale;
पूर्ण post_table[] = अणु
	अणु  2,  0, 0 पूर्ण,
	अणु  4,  0, 1 पूर्ण,
	अणु  4,  1, 0 पूर्ण,
	अणु  8,  1, 1 पूर्ण,
	अणु  8,  2, 0 पूर्ण,
	अणु 16,  2, 1 पूर्ण,
	अणु 12,  3, 0 पूर्ण,
	अणु 24,  3, 1 पूर्ण
पूर्ण;

अटल पूर्णांक pll_factors(काष्ठा _pll_भाग *pll_भाग, अचिन्हित पूर्णांक target,
		       अचिन्हित पूर्णांक source)
अणु
	u64 Kpart;
	अचिन्हित पूर्णांक K, Nभाग, Nmod;
	पूर्णांक i;

	pr_debug("wm8580: PLL %uHz->%uHz\n", source, target);

	/* Scale the output frequency up; the PLL should run in the
	 * region of 90-100MHz.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(post_table); i++) अणु
		अगर (target * post_table[i].भाग >=  90000000 &&
		    target * post_table[i].भाग <= 100000000) अणु
			pll_भाग->freqmode = post_table[i].freqmode;
			pll_भाग->postscale = post_table[i].postscale;
			target *= post_table[i].भाग;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ARRAY_SIZE(post_table)) अणु
		prपूर्णांकk(KERN_ERR "wm8580: Unable to scale output frequency "
		       "%u\n", target);
		वापस -EINVAL;
	पूर्ण

	Nभाग = target / source;

	अगर (Nभाग < 5) अणु
		source /= 2;
		pll_भाग->prescale = 1;
		Nभाग = target / source;
	पूर्ण अन्यथा
		pll_भाग->prescale = 0;

	अगर ((Nभाग < 5) || (Nभाग > 13)) अणु
		prपूर्णांकk(KERN_ERR
			"WM8580 N=%u outside supported range\n", Nभाग);
		वापस -EINVAL;
	पूर्ण

	pll_भाग->n = Nभाग;
	Nmod = target % source;
	Kpart = FIXED_PLL_SIZE * (दीर्घ दीर्घ)Nmod;

	करो_भाग(Kpart, source);

	K = Kpart & 0xFFFFFFFF;

	pll_भाग->k = K;

	pr_debug("PLL %x.%x prescale %d freqmode %d postscale %d\n",
		 pll_भाग->n, pll_भाग->k, pll_भाग->prescale, pll_भाग->freqmode,
		 pll_भाग->postscale);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8580_set_dai_pll(काष्ठा snd_soc_dai *codec_dai, पूर्णांक pll_id,
		पूर्णांक source, अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	पूर्णांक offset;
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8580_priv *wm8580 = snd_soc_component_get_drvdata(component);
	काष्ठा pll_state *state;
	काष्ठा _pll_भाग pll_भाग;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक pwr_mask;
	पूर्णांक ret;

	/* GCC isn't able to work out the अगरs below क्रम initialising/using
	 * pll_भाग so suppress warnings.
	 */
	स_रखो(&pll_भाग, 0, माप(pll_भाग));

	चयन (pll_id) अणु
	हाल WM8580_PLLA:
		state = &wm8580->a;
		offset = 0;
		pwr_mask = WM8580_PWRDN2_PLLAPD;
		अवरोध;
	हाल WM8580_PLLB:
		state = &wm8580->b;
		offset = 4;
		pwr_mask = WM8580_PWRDN2_PLLBPD;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	अगर (freq_in && freq_out) अणु
		ret = pll_factors(&pll_भाग, freq_out, freq_in);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	state->in = freq_in;
	state->out = freq_out;

	/* Always disable the PLL - it is not safe to leave it running
	 * जबतक reprogramming it.
	 */
	snd_soc_component_update_bits(component, WM8580_PWRDN2, pwr_mask, pwr_mask);

	अगर (!freq_in || !freq_out)
		वापस 0;

	snd_soc_component_ग_लिखो(component, WM8580_PLLA1 + offset, pll_भाग.k & 0x1ff);
	snd_soc_component_ग_लिखो(component, WM8580_PLLA2 + offset, (pll_भाग.k >> 9) & 0x1ff);
	snd_soc_component_ग_लिखो(component, WM8580_PLLA3 + offset,
		     (pll_भाग.k >> 18 & 0xf) | (pll_भाग.n << 4));

	reg = snd_soc_component_पढ़ो(component, WM8580_PLLA4 + offset);
	reg &= ~0x1b;
	reg |= pll_भाग.prescale | pll_भाग.postscale << 1 |
		pll_भाग.freqmode << 3;

	snd_soc_component_ग_लिखो(component, WM8580_PLLA4 + offset, reg);

	/* All करोne, turn it on */
	snd_soc_component_update_bits(component, WM8580_PWRDN2, pwr_mask, 0);

	वापस 0;
पूर्ण

अटल स्थिर पूर्णांक wm8580_sysclk_ratios[] = अणु
	128, 192, 256, 384, 512, 768, 1152,
पूर्ण;

/*
 * Set PCM DAI bit size and sample rate.
 */
अटल पूर्णांक wm8580_paअगर_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8580_priv *wm8580 = snd_soc_component_get_drvdata(component);
	u16 paअगरa = 0;
	u16 paअगरb = 0;
	पूर्णांक i, ratio, osr;

	/* bit size */
	चयन (params_width(params)) अणु
	हाल 16:
		paअगरa |= 0x8;
		अवरोध;
	हाल 20:
		paअगरa |= 0x0;
		paअगरb |= WM8580_AIF_LENGTH_20;
		अवरोध;
	हाल 24:
		paअगरa |= 0x0;
		paअगरb |= WM8580_AIF_LENGTH_24;
		अवरोध;
	हाल 32:
		paअगरa |= 0x0;
		paअगरb |= WM8580_AIF_LENGTH_32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Look up the SYSCLK ratio; accept only exact matches */
	ratio = wm8580->sysclk[dai->driver->id] / params_rate(params);
	क्रम (i = 0; i < ARRAY_SIZE(wm8580_sysclk_ratios); i++)
		अगर (ratio == wm8580_sysclk_ratios[i])
			अवरोध;
	अगर (i == ARRAY_SIZE(wm8580_sysclk_ratios)) अणु
		dev_err(component->dev, "Invalid clock ratio %d/%d\n",
			wm8580->sysclk[dai->driver->id], params_rate(params));
		वापस -EINVAL;
	पूर्ण
	paअगरa |= i;
	dev_dbg(component->dev, "Running at %dfs with %dHz clock\n",
		wm8580_sysclk_ratios[i], wm8580->sysclk[dai->driver->id]);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		चयन (ratio) अणु
		हाल 128:
		हाल 192:
			osr = WM8580_DACOSR;
			dev_dbg(component->dev, "Selecting 64x OSR\n");
			अवरोध;
		शेष:
			osr = 0;
			dev_dbg(component->dev, "Selecting 128x OSR\n");
			अवरोध;
		पूर्ण

		snd_soc_component_update_bits(component, WM8580_PAIF3, WM8580_DACOSR, osr);
	पूर्ण

	snd_soc_component_update_bits(component, WM8580_PAIF1 + dai->driver->id,
			    WM8580_AIF_RATE_MASK | WM8580_AIF_BCLKSEL_MASK,
			    paअगरa);
	snd_soc_component_update_bits(component, WM8580_PAIF3 + dai->driver->id,
			    WM8580_AIF_LENGTH_MASK, paअगरb);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8580_set_paअगर_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
				      अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	अचिन्हित पूर्णांक aअगरa;
	अचिन्हित पूर्णांक aअगरb;
	पूर्णांक can_invert_lrclk;

	aअगरa = snd_soc_component_पढ़ो(component, WM8580_PAIF1 + codec_dai->driver->id);
	aअगरb = snd_soc_component_पढ़ो(component, WM8580_PAIF3 + codec_dai->driver->id);

	aअगरb &= ~(WM8580_AIF_FMT_MASK | WM8580_AIF_LRP | WM8580_AIF_BCP);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		aअगरa &= ~WM8580_AIF_MS;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		aअगरa |= WM8580_AIF_MS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		can_invert_lrclk = 1;
		aअगरb |= WM8580_AIF_FMT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		can_invert_lrclk = 1;
		aअगरb |= WM8580_AIF_FMT_RIGHTJ;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		can_invert_lrclk = 1;
		aअगरb |= WM8580_AIF_FMT_LEFTJ;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		can_invert_lrclk = 0;
		aअगरb |= WM8580_AIF_FMT_DSP;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		can_invert_lrclk = 0;
		aअगरb |= WM8580_AIF_FMT_DSP;
		aअगरb |= WM8580_AIF_LRP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;

	हाल SND_SOC_DAIFMT_IB_IF:
		अगर (!can_invert_lrclk)
			वापस -EINVAL;
		aअगरb |= WM8580_AIF_BCP;
		aअगरb |= WM8580_AIF_LRP;
		अवरोध;

	हाल SND_SOC_DAIFMT_IB_NF:
		aअगरb |= WM8580_AIF_BCP;
		अवरोध;

	हाल SND_SOC_DAIFMT_NB_IF:
		अगर (!can_invert_lrclk)
			वापस -EINVAL;
		aअगरb |= WM8580_AIF_LRP;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8580_PAIF1 + codec_dai->driver->id, aअगरa);
	snd_soc_component_ग_लिखो(component, WM8580_PAIF3 + codec_dai->driver->id, aअगरb);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8580_set_dai_clkभाग(काष्ठा snd_soc_dai *codec_dai,
				 पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	अचिन्हित पूर्णांक reg;

	चयन (भाग_id) अणु
	हाल WM8580_MCLK:
		reg = snd_soc_component_पढ़ो(component, WM8580_PLLB4);
		reg &= ~WM8580_PLLB4_MCLKOUTSRC_MASK;

		चयन (भाग) अणु
		हाल WM8580_CLKSRC_MCLK:
			/* Input */
			अवरोध;

		हाल WM8580_CLKSRC_PLLA:
			reg |= WM8580_PLLB4_MCLKOUTSRC_PLLA;
			अवरोध;
		हाल WM8580_CLKSRC_PLLB:
			reg |= WM8580_PLLB4_MCLKOUTSRC_PLLB;
			अवरोध;

		हाल WM8580_CLKSRC_OSC:
			reg |= WM8580_PLLB4_MCLKOUTSRC_OSC;
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण
		snd_soc_component_ग_लिखो(component, WM8580_PLLB4, reg);
		अवरोध;

	हाल WM8580_CLKOUTSRC:
		reg = snd_soc_component_पढ़ो(component, WM8580_PLLB4);
		reg &= ~WM8580_PLLB4_CLKOUTSRC_MASK;

		चयन (भाग) अणु
		हाल WM8580_CLKSRC_NONE:
			अवरोध;

		हाल WM8580_CLKSRC_PLLA:
			reg |= WM8580_PLLB4_CLKOUTSRC_PLLACLK;
			अवरोध;

		हाल WM8580_CLKSRC_PLLB:
			reg |= WM8580_PLLB4_CLKOUTSRC_PLLBCLK;
			अवरोध;

		हाल WM8580_CLKSRC_OSC:
			reg |= WM8580_PLLB4_CLKOUTSRC_OSCCLK;
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण
		snd_soc_component_ग_लिखो(component, WM8580_PLLB4, reg);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8580_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
			     अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8580_priv *wm8580 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret, sel, sel_mask, sel_shअगरt;

	चयन (dai->driver->id) अणु
	हाल WM8580_DAI_PAIFRX:
		sel_mask = 0x3;
		sel_shअगरt = 0;
		अवरोध;

	हाल WM8580_DAI_PAIFTX:
		sel_mask = 0xc;
		sel_shअगरt = 2;
		अवरोध;

	शेष:
		WARN(1, "Unknown DAI driver ID\n");
		वापस -EINVAL;
	पूर्ण

	चयन (clk_id) अणु
	हाल WM8580_CLKSRC_ADCMCLK:
		अगर (dai->driver->id != WM8580_DAI_PAIFTX)
			वापस -EINVAL;
		sel = 0 << sel_shअगरt;
		अवरोध;
	हाल WM8580_CLKSRC_PLLA:
		sel = 1 << sel_shअगरt;
		अवरोध;
	हाल WM8580_CLKSRC_PLLB:
		sel = 2 << sel_shअगरt;
		अवरोध;
	हाल WM8580_CLKSRC_MCLK:
		sel = 3 << sel_shअगरt;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unknown clock %d\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	/* We really should validate PLL settings but not yet */
	wm8580->sysclk[dai->driver->id] = freq;

	ret = snd_soc_component_update_bits(component, WM8580_CLKSEL, sel_mask, sel);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8580_mute(काष्ठा snd_soc_dai *codec_dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	अचिन्हित पूर्णांक reg;

	reg = snd_soc_component_पढ़ो(component, WM8580_DAC_CONTROL5);

	अगर (mute)
		reg |= WM8580_DAC_CONTROL5_MUTEALL;
	अन्यथा
		reg &= ~WM8580_DAC_CONTROL5_MUTEALL;

	snd_soc_component_ग_लिखो(component, WM8580_DAC_CONTROL5, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8580_set_bias_level(काष्ठा snd_soc_component *component,
	क्रमागत snd_soc_bias_level level)
अणु
	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			/* Power up and get inभागidual control of the DACs */
			snd_soc_component_update_bits(component, WM8580_PWRDN1,
					    WM8580_PWRDN1_PWDN |
					    WM8580_PWRDN1_ALLDACPD, 0);

			/* Make VMID high impedance */
			snd_soc_component_update_bits(component, WM8580_ADC_CONTROL1,
					    0x100, 0);
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, WM8580_PWRDN1,
				    WM8580_PWRDN1_PWDN, WM8580_PWRDN1_PWDN);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wm8580_playback_startup(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8580_priv *wm8580 = snd_soc_component_get_drvdata(component);

	वापस snd_pcm_hw_स्थिरraपूर्णांक_minmax(substream->runसमय,
		SNDRV_PCM_HW_PARAM_CHANNELS, 1, wm8580->drvdata->num_dacs * 2);
पूर्ण

#घोषणा WM8580_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8580_dai_ops_playback = अणु
	.startup	= wm8580_playback_startup,
	.set_sysclk	= wm8580_set_sysclk,
	.hw_params	= wm8580_paअगर_hw_params,
	.set_fmt	= wm8580_set_paअगर_dai_fmt,
	.set_clkभाग	= wm8580_set_dai_clkभाग,
	.set_pll	= wm8580_set_dai_pll,
	.mute_stream	= wm8580_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops wm8580_dai_ops_capture = अणु
	.set_sysclk	= wm8580_set_sysclk,
	.hw_params	= wm8580_paअगर_hw_params,
	.set_fmt	= wm8580_set_paअगर_dai_fmt,
	.set_clkभाग	= wm8580_set_dai_clkभाग,
	.set_pll	= wm8580_set_dai_pll,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8580_dai[] = अणु
	अणु
		.name = "wm8580-hifi-playback",
		.id	= WM8580_DAI_PAIFRX,
		.playback = अणु
			.stream_name = "Playback",
			.channels_min = 1,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = WM8580_FORMATS,
		पूर्ण,
		.ops = &wm8580_dai_ops_playback,
	पूर्ण,
	अणु
		.name = "wm8580-hifi-capture",
		.id	=	WM8580_DAI_PAIFTX,
		.capture = अणु
			.stream_name = "Capture",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = WM8580_FORMATS,
		पूर्ण,
		.ops = &wm8580_dai_ops_capture,
	पूर्ण,
पूर्ण;

अटल पूर्णांक wm8580_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8580_priv *wm8580 = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	पूर्णांक ret = 0;

	चयन (wm8580->drvdata->num_dacs) अणु
	हाल 4:
		snd_soc_add_component_controls(component, wm8581_snd_controls,
					ARRAY_SIZE(wm8581_snd_controls));
		snd_soc_dapm_new_controls(dapm, wm8581_dapm_widमाला_लो,
					ARRAY_SIZE(wm8581_dapm_widमाला_लो));
		snd_soc_dapm_add_routes(dapm, wm8581_dapm_routes,
					ARRAY_SIZE(wm8581_dapm_routes));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8580->supplies),
				    wm8580->supplies);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to enable supplies: %d\n", ret);
		जाओ err_regulator_get;
	पूर्ण

	/* Get the codec पूर्णांकo a known state */
	ret = snd_soc_component_ग_लिखो(component, WM8580_RESET, 0);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to reset component: %d\n", ret);
		जाओ err_regulator_enable;
	पूर्ण

	वापस 0;

err_regulator_enable:
	regulator_bulk_disable(ARRAY_SIZE(wm8580->supplies), wm8580->supplies);
err_regulator_get:
	वापस ret;
पूर्ण

/* घातer करोwn chip */
अटल व्योम wm8580_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8580_priv *wm8580 = snd_soc_component_get_drvdata(component);

	regulator_bulk_disable(ARRAY_SIZE(wm8580->supplies), wm8580->supplies);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8580 = अणु
	.probe			= wm8580_probe,
	.हटाओ			= wm8580_हटाओ,
	.set_bias_level		= wm8580_set_bias_level,
	.controls		= wm8580_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8580_snd_controls),
	.dapm_widमाला_लो		= wm8580_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8580_dapm_widमाला_लो),
	.dapm_routes		= wm8580_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8580_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm8580_regmap = अणु
	.reg_bits = 7,
	.val_bits = 9,
	.max_रेजिस्टर = WM8580_MAX_REGISTER,

	.reg_शेषs = wm8580_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8580_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,

	.अस्थिर_reg = wm8580_अस्थिर,
पूर्ण;

अटल स्थिर काष्ठा wm8580_driver_data wm8580_data = अणु
	.num_dacs = 3,
पूर्ण;

अटल स्थिर काष्ठा wm8580_driver_data wm8581_data = अणु
	.num_dacs = 4,
पूर्ण;

अटल स्थिर काष्ठा of_device_id wm8580_of_match[] = अणु
	अणु .compatible = "wlf,wm8580", .data = &wm8580_data पूर्ण,
	अणु .compatible = "wlf,wm8581", .data = &wm8581_data पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, wm8580_of_match);

अटल पूर्णांक wm8580_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा wm8580_priv *wm8580;
	पूर्णांक ret, i;

	wm8580 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8580_priv),
			      GFP_KERNEL);
	अगर (wm8580 == शून्य)
		वापस -ENOMEM;

	wm8580->regmap = devm_regmap_init_i2c(i2c, &wm8580_regmap);
	अगर (IS_ERR(wm8580->regmap))
		वापस PTR_ERR(wm8580->regmap);

	क्रम (i = 0; i < ARRAY_SIZE(wm8580->supplies); i++)
		wm8580->supplies[i].supply = wm8580_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev, ARRAY_SIZE(wm8580->supplies),
				      wm8580->supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(i2c, wm8580);

	of_id = of_match_device(wm8580_of_match, &i2c->dev);
	अगर (of_id)
		wm8580->drvdata = of_id->data;

	अगर (!wm8580->drvdata) अणु
		dev_err(&i2c->dev, "failed to find driver data\n");
		वापस -EINVAL;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_wm8580, wm8580_dai, ARRAY_SIZE(wm8580_dai));

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8580_i2c_id[] = अणु
	अणु "wm8580", (kernel_uदीर्घ_t)&wm8580_data पूर्ण,
	अणु "wm8581", (kernel_uदीर्घ_t)&wm8581_data पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8580_i2c_id);

अटल काष्ठा i2c_driver wm8580_i2c_driver = अणु
	.driver = अणु
		.name = "wm8580",
		.of_match_table = wm8580_of_match,
	पूर्ण,
	.probe =    wm8580_i2c_probe,
	.id_table = wm8580_i2c_id,
पूर्ण;

module_i2c_driver(wm8580_i2c_driver);

MODULE_DESCRIPTION("ASoC WM8580 driver");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_AUTHOR("Matt Flax <flatmax@flatmax.org>");
MODULE_LICENSE("GPL");
