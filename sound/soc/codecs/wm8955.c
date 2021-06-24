<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8955.c  --  WM8955 ALSA SoC Audio driver
 *
 * Copyright 2009 Wolfson Microelectronics plc
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
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/wm8955.h>

#समावेश "wm8955.h"

#घोषणा WM8955_NUM_SUPPLIES 4
अटल स्थिर अक्षर *wm8955_supply_names[WM8955_NUM_SUPPLIES] = अणु
	"DCVDD",
	"DBVDD",
	"HPVDD",
	"AVDD",
पूर्ण;

/* codec निजी data */
काष्ठा wm8955_priv अणु
	काष्ठा regmap *regmap;

	अचिन्हित पूर्णांक mclk_rate;

	पूर्णांक deemph;
	पूर्णांक fs;

	काष्ठा regulator_bulk_data supplies[WM8955_NUM_SUPPLIES];
पूर्ण;

अटल स्थिर काष्ठा reg_शेष wm8955_reg_शेषs[] = अणु
	अणु 2,  0x0079 पूर्ण,     /* R2  - LOUT1 volume */
	अणु 3,  0x0079 पूर्ण,     /* R3  - ROUT1 volume */
	अणु 5,  0x0008 पूर्ण,     /* R5  - DAC Control */
	अणु 7,  0x000A पूर्ण,     /* R7  - Audio Interface */
	अणु 8,  0x0000 पूर्ण,     /* R8  - Sample Rate */
	अणु 10, 0x00FF पूर्ण,     /* R10 - Left DAC volume */
	अणु 11, 0x00FF पूर्ण,     /* R11 - Right DAC volume */
	अणु 12, 0x000F पूर्ण,     /* R12 - Bass control */
	अणु 13, 0x000F पूर्ण,     /* R13 - Treble control */
	अणु 23, 0x00C1 पूर्ण,     /* R23 - Additional control (1) */
	अणु 24, 0x0000 पूर्ण,     /* R24 - Additional control (2) */
	अणु 25, 0x0000 पूर्ण,     /* R25 - Power Management (1) */
	अणु 26, 0x0000 पूर्ण,     /* R26 - Power Management (2) */
	अणु 27, 0x0000 पूर्ण,     /* R27 - Additional Control (3) */
	अणु 34, 0x0050 पूर्ण,     /* R34 - Left out Mix (1) */
	अणु 35, 0x0050 पूर्ण,     /* R35 - Left out Mix (2) */
	अणु 36, 0x0050 पूर्ण,     /* R36 - Right out Mix (1) */
	अणु 37, 0x0050 पूर्ण,     /* R37 - Right Out Mix (2) */
	अणु 38, 0x0050 पूर्ण,     /* R38 - Mono out Mix (1) */
	अणु 39, 0x0050 पूर्ण,     /* R39 - Mono out Mix (2) */
	अणु 40, 0x0079 पूर्ण,     /* R40 - LOUT2 volume */
	अणु 41, 0x0079 पूर्ण,     /* R41 - ROUT2 volume */
	अणु 42, 0x0079 पूर्ण,     /* R42 - MONOOUT volume */
	अणु 43, 0x0000 पूर्ण,     /* R43 - Clocking / PLL */
	अणु 44, 0x0103 पूर्ण,     /* R44 - PLL Control 1 */
	अणु 45, 0x0024 पूर्ण,     /* R45 - PLL Control 2 */
	अणु 46, 0x01BA पूर्ण,     /* R46 - PLL Control 3 */
	अणु 59, 0x0000 पूर्ण,     /* R59 - PLL Control 4 */
पूर्ण;

अटल bool wm8955_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8955_LOUT1_VOLUME:
	हाल WM8955_ROUT1_VOLUME:
	हाल WM8955_DAC_CONTROL:
	हाल WM8955_AUDIO_INTERFACE:
	हाल WM8955_SAMPLE_RATE:
	हाल WM8955_LEFT_DAC_VOLUME:
	हाल WM8955_RIGHT_DAC_VOLUME:
	हाल WM8955_BASS_CONTROL:
	हाल WM8955_TREBLE_CONTROL:
	हाल WM8955_RESET:
	हाल WM8955_ADDITIONAL_CONTROL_1:
	हाल WM8955_ADDITIONAL_CONTROL_2:
	हाल WM8955_POWER_MANAGEMENT_1:
	हाल WM8955_POWER_MANAGEMENT_2:
	हाल WM8955_ADDITIONAL_CONTROL_3:
	हाल WM8955_LEFT_OUT_MIX_1:
	हाल WM8955_LEFT_OUT_MIX_2:
	हाल WM8955_RIGHT_OUT_MIX_1:
	हाल WM8955_RIGHT_OUT_MIX_2:
	हाल WM8955_MONO_OUT_MIX_1:
	हाल WM8955_MONO_OUT_MIX_2:
	हाल WM8955_LOUT2_VOLUME:
	हाल WM8955_ROUT2_VOLUME:
	हाल WM8955_MONOOUT_VOLUME:
	हाल WM8955_CLOCKING_PLL:
	हाल WM8955_PLL_CONTROL_1:
	हाल WM8955_PLL_CONTROL_2:
	हाल WM8955_PLL_CONTROL_3:
	हाल WM8955_PLL_CONTROL_4:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool wm8955_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8955_RESET:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक wm8955_reset(काष्ठा snd_soc_component *component)
अणु
	वापस snd_soc_component_ग_लिखो(component, WM8955_RESET, 0);
पूर्ण

काष्ठा pll_factors अणु
	पूर्णांक n;
	पूर्णांक k;
	पूर्णांक outभाग;
पूर्ण;

/* The size in bits of the FLL भागide multiplied by 10
 * to allow rounding later */
#घोषणा FIXED_FLL_SIZE ((1 << 22) * 10)

अटल पूर्णांक wm8955_pll_factors(काष्ठा device *dev,
			      पूर्णांक Fref, पूर्णांक Fout, काष्ठा pll_factors *pll)
अणु
	u64 Kpart;
	अचिन्हित पूर्णांक K, Nभाग, Nmod, target;

	dev_dbg(dev, "Fref=%u Fout=%u\n", Fref, Fout);

	/* The oscilator should run at should be 90-100MHz, and
	 * there's a भागide by 4 plus an optional भागide by 2 in the
	 * output path to generate the प्रणाली घड़ी.  The घड़ी table
	 * is sortd so we should always generate a suitable target. */
	target = Fout * 4;
	अगर (target < 90000000) अणु
		pll->outभाग = 1;
		target *= 2;
	पूर्ण अन्यथा अणु
		pll->outभाग = 0;
	पूर्ण

	WARN_ON(target < 90000000 || target > 100000000);

	dev_dbg(dev, "Fvco=%dHz\n", target);

	/* Now, calculate N.K */
	Nभाग = target / Fref;

	pll->n = Nभाग;
	Nmod = target % Fref;
	dev_dbg(dev, "Nmod=%d\n", Nmod);

	/* Calculate fractional part - scale up so we can round. */
	Kpart = FIXED_FLL_SIZE * (दीर्घ दीर्घ)Nmod;

	करो_भाग(Kpart, Fref);

	K = Kpart & 0xFFFFFFFF;

	अगर ((K % 10) >= 5)
		K += 5;

	/* Move करोwn to proper range now rounding is करोne */
	pll->k = K / 10;

	dev_dbg(dev, "N=%x K=%x OUTDIV=%x\n", pll->n, pll->k, pll->outभाग);

	वापस 0;
पूर्ण

/* Lookup table specअगरying SRATE (table 25 in datasheet); some of the
 * output frequencies have been rounded to the standard frequencies
 * they are पूर्णांकended to match where the error is slight. */
अटल काष्ठा अणु
	पूर्णांक mclk;
	पूर्णांक fs;
	पूर्णांक usb;
	पूर्णांक sr;
पूर्ण घड़ी_cfgs[] = अणु
	अणु 18432000,  8000, 0,  3, पूर्ण,
	अणु 18432000, 12000, 0,  9, पूर्ण,
	अणु 18432000, 16000, 0, 11, पूर्ण,
	अणु 18432000, 24000, 0, 29, पूर्ण,
	अणु 18432000, 32000, 0, 13, पूर्ण,
	अणु 18432000, 48000, 0,  1, पूर्ण,
	अणु 18432000, 96000, 0, 15, पूर्ण,

	अणु 16934400,  8018, 0, 19, पूर्ण,
	अणु 16934400, 11025, 0, 25, पूर्ण,
	अणु 16934400, 22050, 0, 27, पूर्ण,
	अणु 16934400, 44100, 0, 17, पूर्ण,
	अणु 16934400, 88200, 0, 31, पूर्ण,

	अणु 12000000,  8000, 1,  2, पूर्ण,
	अणु 12000000, 11025, 1, 25, पूर्ण,
	अणु 12000000, 12000, 1,  8, पूर्ण,
	अणु 12000000, 16000, 1, 10, पूर्ण,
	अणु 12000000, 22050, 1, 27, पूर्ण,
	अणु 12000000, 24000, 1, 28, पूर्ण,
	अणु 12000000, 32000, 1, 12, पूर्ण,
	अणु 12000000, 44100, 1, 17, पूर्ण,
	अणु 12000000, 48000, 1,  0, पूर्ण,
	अणु 12000000, 88200, 1, 31, पूर्ण,
	अणु 12000000, 96000, 1, 14, पूर्ण,

	अणु 12288000,  8000, 0,  2, पूर्ण,
	अणु 12288000, 12000, 0,  8, पूर्ण,
	अणु 12288000, 16000, 0, 10, पूर्ण,
	अणु 12288000, 24000, 0, 28, पूर्ण,
	अणु 12288000, 32000, 0, 12, पूर्ण,
	अणु 12288000, 48000, 0,  0, पूर्ण,
	अणु 12288000, 96000, 0, 14, पूर्ण,

	अणु 12289600,  8018, 0, 18, पूर्ण,
	अणु 12289600, 11025, 0, 24, पूर्ण,
	अणु 12289600, 22050, 0, 26, पूर्ण,
	अणु 11289600, 44100, 0, 16, पूर्ण,
	अणु 11289600, 88200, 0, 31, पूर्ण,
पूर्ण;

अटल पूर्णांक wm8955_configure_घड़ीing(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8955_priv *wm8955 = snd_soc_component_get_drvdata(component);
	पूर्णांक i, ret, val;
	पूर्णांक घड़ीing = 0;
	पूर्णांक srate = 0;
	पूर्णांक sr = -1;
	काष्ठा pll_factors pll;

	/* If we're not running a sample rate currently just pick one */
	अगर (wm8955->fs == 0)
		wm8955->fs = 8000;

	/* Can we generate an exact output? */
	क्रम (i = 0; i < ARRAY_SIZE(घड़ी_cfgs); i++) अणु
		अगर (wm8955->fs != घड़ी_cfgs[i].fs)
			जारी;
		sr = i;

		अगर (wm8955->mclk_rate == घड़ी_cfgs[i].mclk)
			अवरोध;
	पूर्ण

	/* We should never get here with an unsupported sample rate */
	अगर (sr == -1) अणु
		dev_err(component->dev, "Sample rate %dHz unsupported\n",
			wm8955->fs);
		WARN_ON(sr == -1);
		वापस -EINVAL;
	पूर्ण

	अगर (i == ARRAY_SIZE(घड़ी_cfgs)) अणु
		/* If we can't generate the right घड़ी from MCLK then
		 * we should configure the PLL to supply us with an
		 * appropriate घड़ी.
		 */
		घड़ीing |= WM8955_MCLKSEL;

		/* Use the last भागider configuration we saw क्रम the
		 * sample rate. */
		ret = wm8955_pll_factors(component->dev, wm8955->mclk_rate,
					 घड़ी_cfgs[sr].mclk, &pll);
		अगर (ret != 0) अणु
			dev_err(component->dev,
				"Unable to generate %dHz from %dHz MCLK\n",
				wm8955->fs, wm8955->mclk_rate);
			वापस -EINVAL;
		पूर्ण

		snd_soc_component_update_bits(component, WM8955_PLL_CONTROL_1,
				    WM8955_N_MASK | WM8955_K_21_18_MASK,
				    (pll.n << WM8955_N_SHIFT) |
				    pll.k >> 18);
		snd_soc_component_update_bits(component, WM8955_PLL_CONTROL_2,
				    WM8955_K_17_9_MASK,
				    (pll.k >> 9) & WM8955_K_17_9_MASK);
		snd_soc_component_update_bits(component, WM8955_PLL_CONTROL_3,
				    WM8955_K_8_0_MASK,
				    pll.k & WM8955_K_8_0_MASK);
		अगर (pll.k)
			snd_soc_component_update_bits(component, WM8955_PLL_CONTROL_4,
					    WM8955_KEN, WM8955_KEN);
		अन्यथा
			snd_soc_component_update_bits(component, WM8955_PLL_CONTROL_4,
					    WM8955_KEN, 0);

		अगर (pll.outभाग)
			val = WM8955_PLL_RB | WM8955_PLLOUTDIV2;
		अन्यथा
			val = WM8955_PLL_RB;

		/* Now start the PLL running */
		snd_soc_component_update_bits(component, WM8955_CLOCKING_PLL,
				    WM8955_PLL_RB | WM8955_PLLOUTDIV2, val);
		snd_soc_component_update_bits(component, WM8955_CLOCKING_PLL,
				    WM8955_PLLEN, WM8955_PLLEN);
	पूर्ण

	srate = घड़ी_cfgs[sr].usb | (घड़ी_cfgs[sr].sr << WM8955_SR_SHIFT);

	snd_soc_component_update_bits(component, WM8955_SAMPLE_RATE,
			    WM8955_USB | WM8955_SR_MASK, srate);
	snd_soc_component_update_bits(component, WM8955_CLOCKING_PLL,
			    WM8955_MCLKSEL, घड़ीing);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8955_sysclk(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	पूर्णांक ret = 0;

	/* Always disable the घड़ीs - अगर we're करोing reconfiguration this
	 * aव्योमs misघड़ीing.
	 */
	snd_soc_component_update_bits(component, WM8955_POWER_MANAGEMENT_1,
			    WM8955_DIGENB, 0);
	snd_soc_component_update_bits(component, WM8955_CLOCKING_PLL,
			    WM8955_PLL_RB | WM8955_PLLEN, 0);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMD:
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMU:
		ret = wm8955_configure_घड़ीing(component);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक deemph_settings[] = अणु 0, 32000, 44100, 48000 पूर्ण;

अटल पूर्णांक wm8955_set_deemph(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8955_priv *wm8955 = snd_soc_component_get_drvdata(component);
	पूर्णांक val, i, best;

	/* If we're using deemphasis select the nearest available sample
	 * rate.
	 */
	अगर (wm8955->deemph) अणु
		best = 1;
		क्रम (i = 2; i < ARRAY_SIZE(deemph_settings); i++) अणु
			अगर (असल(deemph_settings[i] - wm8955->fs) <
			    असल(deemph_settings[best] - wm8955->fs))
				best = i;
		पूर्ण

		val = best << WM8955_DEEMPH_SHIFT;
	पूर्ण अन्यथा अणु
		val = 0;
	पूर्ण

	dev_dbg(component->dev, "Set deemphasis %d\n", val);

	वापस snd_soc_component_update_bits(component, WM8955_DAC_CONTROL,
				   WM8955_DEEMPH_MASK, val);
पूर्ण

अटल पूर्णांक wm8955_get_deemph(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8955_priv *wm8955 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = wm8955->deemph;
	वापस 0;
पूर्ण

अटल पूर्णांक wm8955_put_deemph(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8955_priv *wm8955 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक deemph = ucontrol->value.पूर्णांकeger.value[0];

	अगर (deemph > 1)
		वापस -EINVAL;

	wm8955->deemph = deemph;

	वापस wm8955_set_deemph(component);
पूर्ण

अटल स्थिर अक्षर *bass_mode_text[] = अणु
	"Linear", "Adaptive",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(bass_mode, WM8955_BASS_CONTROL, 7, bass_mode_text);

अटल स्थिर अक्षर *bass_cutoff_text[] = अणु
	"Low", "High"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(bass_cutoff, WM8955_BASS_CONTROL, 6,
			    bass_cutoff_text);

अटल स्थिर अक्षर *treble_cutoff_text[] = अणु
	"High", "Low"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(treble_cutoff, WM8955_TREBLE_CONTROL, 2,
			    treble_cutoff_text);

अटल स्थिर DECLARE_TLV_DB_SCALE(digital_tlv, -12750, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(atten_tlv, -600, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(bypass_tlv, -1500, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(mono_tlv, -2100, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(out_tlv, -12100, 100, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(treble_tlv, -1200, 150, 1);

अटल स्थिर काष्ठा snd_kcontrol_new wm8955_snd_controls[] = अणु
SOC_DOUBLE_R_TLV("Digital Playback Volume", WM8955_LEFT_DAC_VOLUME,
		 WM8955_RIGHT_DAC_VOLUME, 0, 255, 0, digital_tlv),
SOC_SINGLE_TLV("Playback Attenuation Volume", WM8955_DAC_CONTROL, 7, 1, 1,
	       atten_tlv),
SOC_SINGLE_BOOL_EXT("DAC Deemphasis Switch", 0,
		    wm8955_get_deemph, wm8955_put_deemph),

SOC_ENUM("Bass Mode", bass_mode),
SOC_ENUM("Bass Cutoff", bass_cutoff),
SOC_SINGLE("Bass Volume", WM8955_BASS_CONTROL, 0, 15, 1),

SOC_ENUM("Treble Cutoff", treble_cutoff),
SOC_SINGLE_TLV("Treble Volume", WM8955_TREBLE_CONTROL, 0, 14, 1, treble_tlv),

SOC_SINGLE_TLV("Left Bypass Volume", WM8955_LEFT_OUT_MIX_1, 4, 7, 1,
	       bypass_tlv),
SOC_SINGLE_TLV("Left Mono Volume", WM8955_LEFT_OUT_MIX_2, 4, 7, 1,
	       bypass_tlv),

SOC_SINGLE_TLV("Right Mono Volume", WM8955_RIGHT_OUT_MIX_1, 4, 7, 1,
	       bypass_tlv),
SOC_SINGLE_TLV("Right Bypass Volume", WM8955_RIGHT_OUT_MIX_2, 4, 7, 1,
	       bypass_tlv),

/* Not a stereo pair so they line up with the DAPM चयनes */
SOC_SINGLE_TLV("Mono Left Bypass Volume", WM8955_MONO_OUT_MIX_1, 4, 7, 1,
	       mono_tlv),
SOC_SINGLE_TLV("Mono Right Bypass Volume", WM8955_MONO_OUT_MIX_2, 4, 7, 1,
	       mono_tlv),

SOC_DOUBLE_R_TLV("Headphone Volume", WM8955_LOUT1_VOLUME,
		 WM8955_ROUT1_VOLUME, 0, 127, 0, out_tlv),
SOC_DOUBLE_R("Headphone ZC Switch", WM8955_LOUT1_VOLUME,
	     WM8955_ROUT1_VOLUME, 7, 1, 0),

SOC_DOUBLE_R_TLV("Speaker Volume", WM8955_LOUT2_VOLUME,
		 WM8955_ROUT2_VOLUME, 0, 127, 0, out_tlv),
SOC_DOUBLE_R("Speaker ZC Switch", WM8955_LOUT2_VOLUME,
	     WM8955_ROUT2_VOLUME, 7, 1, 0),

SOC_SINGLE_TLV("Mono Volume", WM8955_MONOOUT_VOLUME, 0, 127, 0, out_tlv),
SOC_SINGLE("Mono ZC Switch", WM8955_MONOOUT_VOLUME, 7, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lmixer[] = अणु
SOC_DAPM_SINGLE("Playback Switch", WM8955_LEFT_OUT_MIX_1, 8, 1, 0),
SOC_DAPM_SINGLE("Bypass Switch", WM8955_LEFT_OUT_MIX_1, 7, 1, 0),
SOC_DAPM_SINGLE("Right Playback Switch", WM8955_LEFT_OUT_MIX_2, 8, 1, 0),
SOC_DAPM_SINGLE("Mono Switch", WM8955_LEFT_OUT_MIX_2, 7, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rmixer[] = अणु
SOC_DAPM_SINGLE("Left Playback Switch", WM8955_RIGHT_OUT_MIX_1, 8, 1, 0),
SOC_DAPM_SINGLE("Mono Switch", WM8955_RIGHT_OUT_MIX_1, 7, 1, 0),
SOC_DAPM_SINGLE("Playback Switch", WM8955_RIGHT_OUT_MIX_2, 8, 1, 0),
SOC_DAPM_SINGLE("Bypass Switch", WM8955_RIGHT_OUT_MIX_2, 7, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mmixer[] = अणु
SOC_DAPM_SINGLE("Left Playback Switch", WM8955_MONO_OUT_MIX_1, 8, 1, 0),
SOC_DAPM_SINGLE("Left Bypass Switch", WM8955_MONO_OUT_MIX_1, 7, 1, 0),
SOC_DAPM_SINGLE("Right Playback Switch", WM8955_MONO_OUT_MIX_2, 8, 1, 0),
SOC_DAPM_SINGLE("Right Bypass Switch", WM8955_MONO_OUT_MIX_2, 7, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8955_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("MONOIN-"),
SND_SOC_DAPM_INPUT("MONOIN+"),
SND_SOC_DAPM_INPUT("LINEINR"),
SND_SOC_DAPM_INPUT("LINEINL"),

SND_SOC_DAPM_PGA("Mono Input", SND_SOC_NOPM, 0, 0, शून्य, 0),

SND_SOC_DAPM_SUPPLY("SYSCLK", WM8955_POWER_MANAGEMENT_1, 0, 1, wm8955_sysclk,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("TSDEN", WM8955_ADDITIONAL_CONTROL_1, 8, 0, शून्य, 0),

SND_SOC_DAPM_DAC("DACL", "Playback", WM8955_POWER_MANAGEMENT_2, 8, 0),
SND_SOC_DAPM_DAC("DACR", "Playback", WM8955_POWER_MANAGEMENT_2, 7, 0),

SND_SOC_DAPM_PGA("LOUT1 PGA", WM8955_POWER_MANAGEMENT_2, 6, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ROUT1 PGA", WM8955_POWER_MANAGEMENT_2, 5, 0, शून्य, 0),
SND_SOC_DAPM_PGA("LOUT2 PGA", WM8955_POWER_MANAGEMENT_2, 4, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ROUT2 PGA", WM8955_POWER_MANAGEMENT_2, 3, 0, शून्य, 0),
SND_SOC_DAPM_PGA("MOUT PGA", WM8955_POWER_MANAGEMENT_2, 2, 0, शून्य, 0),
SND_SOC_DAPM_PGA("OUT3 PGA", WM8955_POWER_MANAGEMENT_2, 1, 0, शून्य, 0),

/* The names are chosen to make the control names nice */
SND_SOC_DAPM_MIXER("Left", SND_SOC_NOPM, 0, 0,
		   lmixer, ARRAY_SIZE(lmixer)),
SND_SOC_DAPM_MIXER("Right", SND_SOC_NOPM, 0, 0,
		   rmixer, ARRAY_SIZE(rmixer)),
SND_SOC_DAPM_MIXER("Mono", SND_SOC_NOPM, 0, 0,
		   mmixer, ARRAY_SIZE(mmixer)),

SND_SOC_DAPM_OUTPUT("LOUT1"),
SND_SOC_DAPM_OUTPUT("ROUT1"),
SND_SOC_DAPM_OUTPUT("LOUT2"),
SND_SOC_DAPM_OUTPUT("ROUT2"),
SND_SOC_DAPM_OUTPUT("MONOOUT"),
SND_SOC_DAPM_OUTPUT("OUT3"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8955_dapm_routes[] = अणु
	अणु "DACL", शून्य, "SYSCLK" पूर्ण,
	अणु "DACR", शून्य, "SYSCLK" पूर्ण,

	अणु "Mono Input", शून्य, "MONOIN-" पूर्ण,
	अणु "Mono Input", शून्य, "MONOIN+" पूर्ण,

	अणु "Left", "Playback Switch", "DACL" पूर्ण,
	अणु "Left", "Right Playback Switch", "DACR" पूर्ण,
	अणु "Left", "Bypass Switch", "LINEINL" पूर्ण,
	अणु "Left", "Mono Switch", "Mono Input" पूर्ण,

	अणु "Right", "Playback Switch", "DACR" पूर्ण,
	अणु "Right", "Left Playback Switch", "DACL" पूर्ण,
	अणु "Right", "Bypass Switch", "LINEINR" पूर्ण,
	अणु "Right", "Mono Switch", "Mono Input" पूर्ण,

	अणु "Mono", "Left Playback Switch", "DACL" पूर्ण,
	अणु "Mono", "Right Playback Switch", "DACR" पूर्ण,
	अणु "Mono", "Left Bypass Switch", "LINEINL" पूर्ण,
	अणु "Mono", "Right Bypass Switch", "LINEINR" पूर्ण,

	अणु "LOUT1 PGA", शून्य, "Left" पूर्ण,
	अणु "LOUT1", शून्य, "TSDEN" पूर्ण,
	अणु "LOUT1", शून्य, "LOUT1 PGA" पूर्ण,

	अणु "ROUT1 PGA", शून्य, "Right" पूर्ण,
	अणु "ROUT1", शून्य, "TSDEN" पूर्ण,
	अणु "ROUT1", शून्य, "ROUT1 PGA" पूर्ण,

	अणु "LOUT2 PGA", शून्य, "Left" पूर्ण,
	अणु "LOUT2", शून्य, "TSDEN" पूर्ण,
	अणु "LOUT2", शून्य, "LOUT2 PGA" पूर्ण,

	अणु "ROUT2 PGA", शून्य, "Right" पूर्ण,
	अणु "ROUT2", शून्य, "TSDEN" पूर्ण,
	अणु "ROUT2", शून्य, "ROUT2 PGA" पूर्ण,

	अणु "MOUT PGA", शून्य, "Mono" पूर्ण,
	अणु "MONOOUT", शून्य, "MOUT PGA" पूर्ण,

	/* OUT3 not currently implemented */
	अणु "OUT3", शून्य, "OUT3 PGA" पूर्ण,
पूर्ण;

अटल पूर्णांक wm8955_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8955_priv *wm8955 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;
	पूर्णांक wl;

	चयन (params_width(params)) अणु
	हाल 16:
		wl = 0;
		अवरोध;
	हाल 20:
		wl = 0x4;
		अवरोध;
	हाल 24:
		wl = 0x8;
		अवरोध;
	हाल 32:
		wl = 0xc;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_update_bits(component, WM8955_AUDIO_INTERFACE,
			    WM8955_WL_MASK, wl);

	wm8955->fs = params_rate(params);
	wm8955_set_deemph(component);

	/* If the chip is घड़ीed then disable the घड़ीs and क्रमce a
	 * reconfiguration, otherwise DAPM will घातer up the
	 * घड़ीs क्रम us later. */
	ret = snd_soc_component_पढ़ो(component, WM8955_POWER_MANAGEMENT_1);
	अगर (ret < 0)
		वापस ret;
	अगर (ret & WM8955_DIGENB) अणु
		snd_soc_component_update_bits(component, WM8955_POWER_MANAGEMENT_1,
				    WM8955_DIGENB, 0);
		snd_soc_component_update_bits(component, WM8955_CLOCKING_PLL,
				    WM8955_PLL_RB | WM8955_PLLEN, 0);

		wm8955_configure_घड़ीing(component);
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक wm8955_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
			     अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8955_priv *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक भाग;

	चयन (clk_id) अणु
	हाल WM8955_CLK_MCLK:
		अगर (freq > 15000000) अणु
			priv->mclk_rate = freq /= 2;
			भाग = WM8955_MCLKDIV2;
		पूर्ण अन्यथा अणु
			priv->mclk_rate = freq;
			भाग = 0;
		पूर्ण

		snd_soc_component_update_bits(component, WM8955_SAMPLE_RATE,
				    WM8955_MCLKDIV2, भाग);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dai->dev, "Clock source is %d at %uHz\n", clk_id, freq);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8955_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 aअगर = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		aअगर |= WM8955_MS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_B:
		aअगर |= WM8955_LRP;
		fallthrough;
	हाल SND_SOC_DAIFMT_DSP_A:
		aअगर |= 0x3;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		aअगर |= 0x2;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		aअगर |= 0x1;
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
			aअगर |= WM8955_BCLKINV;
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
			aअगर |= WM8955_BCLKINV | WM8955_LRP;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			aअगर |= WM8955_BCLKINV;
			अवरोध;
		हाल SND_SOC_DAIFMT_NB_IF:
			aअगर |= WM8955_LRP;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, WM8955_AUDIO_INTERFACE,
			    WM8955_MS | WM8955_FORMAT_MASK | WM8955_BCLKINV |
			    WM8955_LRP, aअगर);

	वापस 0;
पूर्ण


अटल पूर्णांक wm8955_mute(काष्ठा snd_soc_dai *codec_dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	पूर्णांक val;

	अगर (mute)
		val = WM8955_DACMU;
	अन्यथा
		val = 0;

	snd_soc_component_update_bits(component, WM8955_DAC_CONTROL, WM8955_DACMU, val);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8955_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8955_priv *wm8955 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		/* VMID resistance 2*50k */
		snd_soc_component_update_bits(component, WM8955_POWER_MANAGEMENT_1,
				    WM8955_VMIDSEL_MASK,
				    0x1 << WM8955_VMIDSEL_SHIFT);

		/* Default bias current */
		snd_soc_component_update_bits(component, WM8955_ADDITIONAL_CONTROL_1,
				    WM8955_VSEL_MASK,
				    0x2 << WM8955_VSEL_SHIFT);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			ret = regulator_bulk_enable(ARRAY_SIZE(wm8955->supplies),
						    wm8955->supplies);
			अगर (ret != 0) अणु
				dev_err(component->dev,
					"Failed to enable supplies: %d\n",
					ret);
				वापस ret;
			पूर्ण

			regcache_sync(wm8955->regmap);

			/* Enable VREF and VMID */
			snd_soc_component_update_bits(component, WM8955_POWER_MANAGEMENT_1,
					    WM8955_VREF |
					    WM8955_VMIDSEL_MASK,
					    WM8955_VREF |
					    0x3 << WM8955_VREF_SHIFT);

			/* Let VMID ramp */
			msleep(500);

			/* High resistance VROI to मुख्यtain outमाला_दो */
			snd_soc_component_update_bits(component,
					    WM8955_ADDITIONAL_CONTROL_3,
					    WM8955_VROI, WM8955_VROI);
		पूर्ण

		/* Maपूर्णांकain VMID with 2*250k */
		snd_soc_component_update_bits(component, WM8955_POWER_MANAGEMENT_1,
				    WM8955_VMIDSEL_MASK,
				    0x2 << WM8955_VMIDSEL_SHIFT);

		/* Minimum bias current */
		snd_soc_component_update_bits(component, WM8955_ADDITIONAL_CONTROL_1,
				    WM8955_VSEL_MASK, 0);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		/* Low resistance VROI to help disअक्षरge */
		snd_soc_component_update_bits(component,
				    WM8955_ADDITIONAL_CONTROL_3,
				    WM8955_VROI, 0);

		/* Turn off VMID and VREF */
		snd_soc_component_update_bits(component, WM8955_POWER_MANAGEMENT_1,
				    WM8955_VREF |
				    WM8955_VMIDSEL_MASK, 0);

		regulator_bulk_disable(ARRAY_SIZE(wm8955->supplies),
				       wm8955->supplies);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा WM8955_RATES SNDRV_PCM_RATE_8000_96000

#घोषणा WM8955_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8955_dai_ops = अणु
	.set_sysclk = wm8955_set_sysclk,
	.set_fmt = wm8955_set_fmt,
	.hw_params = wm8955_hw_params,
	.mute_stream = wm8955_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8955_dai = अणु
	.name = "wm8955-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = WM8955_RATES,
		.क्रमmats = WM8955_FORMATS,
	पूर्ण,
	.ops = &wm8955_dai_ops,
पूर्ण;

अटल पूर्णांक wm8955_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8955_priv *wm8955 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8955_pdata *pdata = dev_get_platdata(component->dev);
	पूर्णांक ret, i;

	क्रम (i = 0; i < ARRAY_SIZE(wm8955->supplies); i++)
		wm8955->supplies[i].supply = wm8955_supply_names[i];

	ret = devm_regulator_bulk_get(component->dev, ARRAY_SIZE(wm8955->supplies),
				 wm8955->supplies);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8955->supplies),
				    wm8955->supplies);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = wm8955_reset(component);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to issue reset: %d\n", ret);
		जाओ err_enable;
	पूर्ण

	/* Change some शेष settings - latch VU and enable ZC */
	snd_soc_component_update_bits(component, WM8955_LEFT_DAC_VOLUME,
			    WM8955_LDVU, WM8955_LDVU);
	snd_soc_component_update_bits(component, WM8955_RIGHT_DAC_VOLUME,
			    WM8955_RDVU, WM8955_RDVU);
	snd_soc_component_update_bits(component, WM8955_LOUT1_VOLUME,
			    WM8955_LO1VU | WM8955_LO1ZC,
			    WM8955_LO1VU | WM8955_LO1ZC);
	snd_soc_component_update_bits(component, WM8955_ROUT1_VOLUME,
			    WM8955_RO1VU | WM8955_RO1ZC,
			    WM8955_RO1VU | WM8955_RO1ZC);
	snd_soc_component_update_bits(component, WM8955_LOUT2_VOLUME,
			    WM8955_LO2VU | WM8955_LO2ZC,
			    WM8955_LO2VU | WM8955_LO2ZC);
	snd_soc_component_update_bits(component, WM8955_ROUT2_VOLUME,
			    WM8955_RO2VU | WM8955_RO2ZC,
			    WM8955_RO2VU | WM8955_RO2ZC);
	snd_soc_component_update_bits(component, WM8955_MONOOUT_VOLUME,
			    WM8955_MOZC, WM8955_MOZC);

	/* Also enable adaptive bass boost by शेष */
	snd_soc_component_update_bits(component, WM8955_BASS_CONTROL, WM8955_BB, WM8955_BB);

	/* Set platक्रमm data values */
	अगर (pdata) अणु
		अगर (pdata->out2_speaker)
			snd_soc_component_update_bits(component, WM8955_ADDITIONAL_CONTROL_2,
					    WM8955_ROUT2INV, WM8955_ROUT2INV);

		अगर (pdata->monoin_dअगरf)
			snd_soc_component_update_bits(component, WM8955_MONO_OUT_MIX_1,
					    WM8955_DMEN, WM8955_DMEN);
	पूर्ण

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_STANDBY);

	/* Bias level configuration will have करोne an extra enable */
	regulator_bulk_disable(ARRAY_SIZE(wm8955->supplies), wm8955->supplies);

	वापस 0;

err_enable:
	regulator_bulk_disable(ARRAY_SIZE(wm8955->supplies), wm8955->supplies);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8955 = अणु
	.probe			= wm8955_probe,
	.set_bias_level		= wm8955_set_bias_level,
	.controls		= wm8955_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8955_snd_controls),
	.dapm_widमाला_लो		= wm8955_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8955_dapm_widमाला_लो),
	.dapm_routes		= wm8955_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8955_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm8955_regmap = अणु
	.reg_bits = 7,
	.val_bits = 9,

	.max_रेजिस्टर = WM8955_MAX_REGISTER,
	.अस्थिर_reg = wm8955_अस्थिर,
	.ग_लिखोable_reg = wm8955_ग_लिखोable,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = wm8955_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8955_reg_शेषs),
पूर्ण;

अटल पूर्णांक wm8955_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8955_priv *wm8955;
	पूर्णांक ret;

	wm8955 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8955_priv),
			      GFP_KERNEL);
	अगर (wm8955 == शून्य)
		वापस -ENOMEM;

	wm8955->regmap = devm_regmap_init_i2c(i2c, &wm8955_regmap);
	अगर (IS_ERR(wm8955->regmap)) अणु
		ret = PTR_ERR(wm8955->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(i2c, wm8955);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_wm8955, &wm8955_dai, 1);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8955_i2c_id[] = अणु
	अणु "wm8955", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8955_i2c_id);

अटल काष्ठा i2c_driver wm8955_i2c_driver = अणु
	.driver = अणु
		.name = "wm8955",
	पूर्ण,
	.probe =    wm8955_i2c_probe,
	.id_table = wm8955_i2c_id,
पूर्ण;

module_i2c_driver(wm8955_i2c_driver);

MODULE_DESCRIPTION("ASoC WM8955 driver");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
