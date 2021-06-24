<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8994.c  --  WM8994 ALSA SoC Audio driver
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
#समावेश <linux/gcd.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <trace/events/asoc.h>

#समावेश <linux/mfd/wm8994/core.h>
#समावेश <linux/mfd/wm8994/रेजिस्टरs.h>
#समावेश <linux/mfd/wm8994/pdata.h>
#समावेश <linux/mfd/wm8994/gpपन.स>

#समावेश "wm8994.h"
#समावेश "wm_hubs.h"

#घोषणा WM1811_JACKDET_MODE_NONE  0x0000
#घोषणा WM1811_JACKDET_MODE_JACK  0x0100
#घोषणा WM1811_JACKDET_MODE_MIC   0x0080
#घोषणा WM1811_JACKDET_MODE_AUDIO 0x0180

#घोषणा WM8994_NUM_DRC 3
#घोषणा WM8994_NUM_EQ  3

काष्ठा wm8994_reg_mask अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक mask;
पूर्ण;

अटल काष्ठा wm8994_reg_mask wm8994_vu_bits[] = अणु
	अणु WM8994_LEFT_LINE_INPUT_1_2_VOLUME, WM8994_IN1_VU पूर्ण,
	अणु WM8994_RIGHT_LINE_INPUT_1_2_VOLUME, WM8994_IN1_VU पूर्ण,
	अणु WM8994_LEFT_LINE_INPUT_3_4_VOLUME, WM8994_IN2_VU पूर्ण,
	अणु WM8994_RIGHT_LINE_INPUT_3_4_VOLUME, WM8994_IN2_VU पूर्ण,
	अणु WM8994_SPEAKER_VOLUME_LEFT, WM8994_SPKOUT_VU पूर्ण,
	अणु WM8994_SPEAKER_VOLUME_RIGHT, WM8994_SPKOUT_VU पूर्ण,
	अणु WM8994_LEFT_OUTPUT_VOLUME, WM8994_HPOUT1_VU पूर्ण,
	अणु WM8994_RIGHT_OUTPUT_VOLUME, WM8994_HPOUT1_VU पूर्ण,
	अणु WM8994_LEFT_OPGA_VOLUME, WM8994_MIXOUT_VU पूर्ण,
	अणु WM8994_RIGHT_OPGA_VOLUME, WM8994_MIXOUT_VU पूर्ण,

	अणु WM8994_AIF1_DAC1_LEFT_VOLUME, WM8994_AIF1DAC1_VU पूर्ण,
	अणु WM8994_AIF1_DAC1_RIGHT_VOLUME, WM8994_AIF1DAC1_VU पूर्ण,
	अणु WM8994_AIF2_DAC_LEFT_VOLUME, WM8994_AIF2DAC_VU पूर्ण,
	अणु WM8994_AIF2_DAC_RIGHT_VOLUME, WM8994_AIF2DAC_VU पूर्ण,
	अणु WM8994_AIF1_ADC1_LEFT_VOLUME, WM8994_AIF1ADC1_VU पूर्ण,
	अणु WM8994_AIF1_ADC1_RIGHT_VOLUME, WM8994_AIF1ADC1_VU पूर्ण,
	अणु WM8994_AIF2_ADC_LEFT_VOLUME, WM8994_AIF2ADC_VU पूर्ण,
	अणु WM8994_AIF2_ADC_RIGHT_VOLUME, WM8994_AIF1ADC2_VU पूर्ण,
	अणु WM8994_DAC1_LEFT_VOLUME, WM8994_DAC1_VU पूर्ण,
	अणु WM8994_DAC1_RIGHT_VOLUME, WM8994_DAC1_VU पूर्ण,
	अणु WM8994_DAC2_LEFT_VOLUME, WM8994_DAC2_VU पूर्ण,
	अणु WM8994_DAC2_RIGHT_VOLUME, WM8994_DAC2_VU पूर्ण,
पूर्ण;

/* VU bitfields क्रम ADC2, DAC2 not available on WM1811 */
अटल काष्ठा wm8994_reg_mask wm8994_adc2_dac2_vu_bits[] = अणु
	अणु WM8994_AIF1_DAC2_LEFT_VOLUME, WM8994_AIF1DAC2_VU पूर्ण,
	अणु WM8994_AIF1_DAC2_RIGHT_VOLUME, WM8994_AIF1DAC2_VU पूर्ण,
	अणु WM8994_AIF1_ADC2_LEFT_VOLUME, WM8994_AIF1ADC2_VU पूर्ण,
	अणु WM8994_AIF1_ADC2_RIGHT_VOLUME, WM8994_AIF1ADC2_VU पूर्ण,
पूर्ण;

अटल पूर्णांक wm8994_drc_base[] = अणु
	WM8994_AIF1_DRC1_1,
	WM8994_AIF1_DRC2_1,
	WM8994_AIF2_DRC_1,
पूर्ण;

अटल पूर्णांक wm8994_retune_mobile_base[] = अणु
	WM8994_AIF1_DAC1_EQ_GAINS_1,
	WM8994_AIF1_DAC2_EQ_GAINS_1,
	WM8994_AIF2_EQ_GAINS_1,
पूर्ण;

अटल स्थिर काष्ठा wm8958_micd_rate micdet_rates[] = अणु
	अणु 32768,       true,  1, 4 पूर्ण,
	अणु 32768,       false, 1, 1 पूर्ण,
	अणु 44100 * 256, true,  7, 10 पूर्ण,
	अणु 44100 * 256, false, 7, 10 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा wm8958_micd_rate jackdet_rates[] = अणु
	अणु 32768,       true,  0, 1 पूर्ण,
	अणु 32768,       false, 0, 1 पूर्ण,
	अणु 44100 * 256, true,  10, 10 पूर्ण,
	अणु 44100 * 256, false, 7, 8 पूर्ण,
पूर्ण;

अटल व्योम wm8958_micd_set_rate(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;
	पूर्णांक best, i, sysclk, val;
	bool idle;
	स्थिर काष्ठा wm8958_micd_rate *rates;
	पूर्णांक num_rates;

	idle = !wm8994->jack_mic;

	sysclk = snd_soc_component_पढ़ो(component, WM8994_CLOCKING_1);
	अगर (sysclk & WM8994_SYSCLK_SRC)
		sysclk = wm8994->aअगरclk[1];
	अन्यथा
		sysclk = wm8994->aअगरclk[0];

	अगर (control->pdata.micd_rates) अणु
		rates = control->pdata.micd_rates;
		num_rates = control->pdata.num_micd_rates;
	पूर्ण अन्यथा अगर (wm8994->jackdet) अणु
		rates = jackdet_rates;
		num_rates = ARRAY_SIZE(jackdet_rates);
	पूर्ण अन्यथा अणु
		rates = micdet_rates;
		num_rates = ARRAY_SIZE(micdet_rates);
	पूर्ण

	best = 0;
	क्रम (i = 0; i < num_rates; i++) अणु
		अगर (rates[i].idle != idle)
			जारी;
		अगर (असल(rates[i].sysclk - sysclk) <
		    असल(rates[best].sysclk - sysclk))
			best = i;
		अन्यथा अगर (rates[best].idle != idle)
			best = i;
	पूर्ण

	val = rates[best].start << WM8958_MICD_BIAS_STARTTIME_SHIFT
		| rates[best].rate << WM8958_MICD_RATE_SHIFT;

	dev_dbg(component->dev, "MICD rate %d,%d for %dHz %s\n",
		rates[best].start, rates[best].rate, sysclk,
		idle ? "idle" : "active");

	snd_soc_component_update_bits(component, WM8958_MIC_DETECT_1,
			    WM8958_MICD_BIAS_STARTTIME_MASK |
			    WM8958_MICD_RATE_MASK, val);
पूर्ण

अटल पूर्णांक configure_aअगर_घड़ी(काष्ठा snd_soc_component *component, पूर्णांक aअगर)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	पूर्णांक rate;
	पूर्णांक reg1 = 0;
	पूर्णांक offset;

	अगर (aअगर)
		offset = 4;
	अन्यथा
		offset = 0;

	चयन (wm8994->sysclk[aअगर]) अणु
	हाल WM8994_SYSCLK_MCLK1:
		rate = wm8994->mclk_rate[0];
		अवरोध;

	हाल WM8994_SYSCLK_MCLK2:
		reg1 |= 0x8;
		rate = wm8994->mclk_rate[1];
		अवरोध;

	हाल WM8994_SYSCLK_FLL1:
		reg1 |= 0x10;
		rate = wm8994->fll[0].out;
		अवरोध;

	हाल WM8994_SYSCLK_FLL2:
		reg1 |= 0x18;
		rate = wm8994->fll[1].out;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (rate >= 13500000) अणु
		rate /= 2;
		reg1 |= WM8994_AIF1CLK_DIV;

		dev_dbg(component->dev, "Dividing AIF%d clock to %dHz\n",
			aअगर + 1, rate);
	पूर्ण

	wm8994->aअगरclk[aअगर] = rate;

	snd_soc_component_update_bits(component, WM8994_AIF1_CLOCKING_1 + offset,
			    WM8994_AIF1CLK_SRC_MASK | WM8994_AIF1CLK_DIV,
			    reg1);

	वापस 0;
पूर्ण

अटल पूर्णांक configure_घड़ी(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	पूर्णांक change, new;

	/* Bring up the AIF घड़ीs first */
	configure_aअगर_घड़ी(component, 0);
	configure_aअगर_घड़ी(component, 1);

	/* Then चयन CLK_SYS over to the higher of them; a change
	 * can only happen as a result of a घड़ीing change which can
	 * only be made outside of DAPM so we can safely reकरो the
	 * घड़ीing.
	 */

	/* If they're equal it doesn't matter which is used */
	अगर (wm8994->aअगरclk[0] == wm8994->aअगरclk[1]) अणु
		wm8958_micd_set_rate(component);
		वापस 0;
	पूर्ण

	अगर (wm8994->aअगरclk[0] < wm8994->aअगरclk[1])
		new = WM8994_SYSCLK_SRC;
	अन्यथा
		new = 0;

	change = snd_soc_component_update_bits(component, WM8994_CLOCKING_1,
				     WM8994_SYSCLK_SRC, new);
	अगर (change)
		snd_soc_dapm_sync(dapm);

	wm8958_micd_set_rate(component);

	वापस 0;
पूर्ण

अटल पूर्णांक check_clk_sys(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	पूर्णांक reg = snd_soc_component_पढ़ो(component, WM8994_CLOCKING_1);
	स्थिर अक्षर *clk;

	/* Check what we're currently using क्रम CLK_SYS */
	अगर (reg & WM8994_SYSCLK_SRC)
		clk = "AIF2CLK";
	अन्यथा
		clk = "AIF1CLK";

	वापस म_भेद(source->name, clk) == 0;
पूर्ण

अटल स्थिर अक्षर *sidetone_hpf_text[] = अणु
	"2.7kHz", "1.35kHz", "675Hz", "370Hz", "180Hz", "90Hz", "45Hz"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(sidetone_hpf,
			    WM8994_SIDETONE, 7, sidetone_hpf_text);

अटल स्थिर अक्षर *adc_hpf_text[] = अणु
	"HiFi", "Voice 1", "Voice 2", "Voice 3"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(aअगर1adc1_hpf,
			    WM8994_AIF1_ADC1_FILTERS, 13, adc_hpf_text);

अटल SOC_ENUM_SINGLE_DECL(aअगर1adc2_hpf,
			    WM8994_AIF1_ADC2_FILTERS, 13, adc_hpf_text);

अटल SOC_ENUM_SINGLE_DECL(aअगर2adc_hpf,
			    WM8994_AIF2_ADC_FILTERS, 13, adc_hpf_text);

अटल स्थिर DECLARE_TLV_DB_SCALE(aअगर_tlv, 0, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(digital_tlv, -7200, 75, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(st_tlv, -3600, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(wm8994_3d_tlv, -1600, 183, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(eq_tlv, -1200, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(ng_tlv, -10200, 600, 0);

#घोषणा WM8994_DRC_SWITCH(xname, reg, shअगरt) \
	SOC_SINGLE_EXT(xname, reg, shअगरt, 1, 0, \
		snd_soc_get_volsw, wm8994_put_drc_sw)

अटल पूर्णांक wm8994_put_drc_sw(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	पूर्णांक mask, ret;

	/* Can't enable both ADC and DAC paths simultaneously */
	अगर (mc->shअगरt == WM8994_AIF1DAC1_DRC_ENA_SHIFT)
		mask = WM8994_AIF1ADC1L_DRC_ENA_MASK |
			WM8994_AIF1ADC1R_DRC_ENA_MASK;
	अन्यथा
		mask = WM8994_AIF1DAC1_DRC_ENA_MASK;

	ret = snd_soc_component_पढ़ो(component, mc->reg);
	अगर (ret < 0)
		वापस ret;
	अगर (ret & mask)
		वापस -EINVAL;

	वापस snd_soc_put_volsw(kcontrol, ucontrol);
पूर्ण

अटल व्योम wm8994_set_drc(काष्ठा snd_soc_component *component, पूर्णांक drc)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;
	काष्ठा wm8994_pdata *pdata = &control->pdata;
	पूर्णांक base = wm8994_drc_base[drc];
	पूर्णांक cfg = wm8994->drc_cfg[drc];
	पूर्णांक save, i;

	/* Save any enables; the configuration should clear them. */
	save = snd_soc_component_पढ़ो(component, base);
	save &= WM8994_AIF1DAC1_DRC_ENA | WM8994_AIF1ADC1L_DRC_ENA |
		WM8994_AIF1ADC1R_DRC_ENA;

	क्रम (i = 0; i < WM8994_DRC_REGS; i++)
		snd_soc_component_update_bits(component, base + i, 0xffff,
				    pdata->drc_cfgs[cfg].regs[i]);

	snd_soc_component_update_bits(component, base, WM8994_AIF1DAC1_DRC_ENA |
			     WM8994_AIF1ADC1L_DRC_ENA |
			     WM8994_AIF1ADC1R_DRC_ENA, save);
पूर्ण

/* Icky as hell but saves code duplication */
अटल पूर्णांक wm8994_get_drc(स्थिर अक्षर *name)
अणु
	अगर (म_भेद(name, "AIF1DRC1 Mode") == 0)
		वापस 0;
	अगर (म_भेद(name, "AIF1DRC2 Mode") == 0)
		वापस 1;
	अगर (म_भेद(name, "AIF2DRC Mode") == 0)
		वापस 2;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wm8994_put_drc_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;
	काष्ठा wm8994_pdata *pdata = &control->pdata;
	पूर्णांक drc = wm8994_get_drc(kcontrol->id.name);
	पूर्णांक value = ucontrol->value.क्रमागतerated.item[0];

	अगर (drc < 0)
		वापस drc;

	अगर (value >= pdata->num_drc_cfgs)
		वापस -EINVAL;

	wm8994->drc_cfg[drc] = value;

	wm8994_set_drc(component, drc);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8994_get_drc_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	पूर्णांक drc = wm8994_get_drc(kcontrol->id.name);

	अगर (drc < 0)
		वापस drc;
	ucontrol->value.क्रमागतerated.item[0] = wm8994->drc_cfg[drc];

	वापस 0;
पूर्ण

अटल व्योम wm8994_set_retune_mobile(काष्ठा snd_soc_component *component, पूर्णांक block)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;
	काष्ठा wm8994_pdata *pdata = &control->pdata;
	पूर्णांक base = wm8994_retune_mobile_base[block];
	पूर्णांक अगरace, best, best_val, save, i, cfg;

	अगर (!pdata || !wm8994->num_retune_mobile_texts)
		वापस;

	चयन (block) अणु
	हाल 0:
	हाल 1:
		अगरace = 0;
		अवरोध;
	हाल 2:
		अगरace = 1;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	/* Find the version of the currently selected configuration
	 * with the nearest sample rate. */
	cfg = wm8994->retune_mobile_cfg[block];
	best = 0;
	best_val = पूर्णांक_उच्च;
	क्रम (i = 0; i < pdata->num_retune_mobile_cfgs; i++) अणु
		अगर (म_भेद(pdata->retune_mobile_cfgs[i].name,
			   wm8994->retune_mobile_texts[cfg]) == 0 &&
		    असल(pdata->retune_mobile_cfgs[i].rate
			- wm8994->dac_rates[अगरace]) < best_val) अणु
			best = i;
			best_val = असल(pdata->retune_mobile_cfgs[i].rate
				       - wm8994->dac_rates[अगरace]);
		पूर्ण
	पूर्ण

	dev_dbg(component->dev, "ReTune Mobile %d %s/%dHz for %dHz sample rate\n",
		block,
		pdata->retune_mobile_cfgs[best].name,
		pdata->retune_mobile_cfgs[best].rate,
		wm8994->dac_rates[अगरace]);

	/* The EQ will be disabled जबतक reconfiguring it, remember the
	 * current configuration.
	 */
	save = snd_soc_component_पढ़ो(component, base);
	save &= WM8994_AIF1DAC1_EQ_ENA;

	क्रम (i = 0; i < WM8994_EQ_REGS; i++)
		snd_soc_component_update_bits(component, base + i, 0xffff,
				pdata->retune_mobile_cfgs[best].regs[i]);

	snd_soc_component_update_bits(component, base, WM8994_AIF1DAC1_EQ_ENA, save);
पूर्ण

/* Icky as hell but saves code duplication */
अटल पूर्णांक wm8994_get_retune_mobile_block(स्थिर अक्षर *name)
अणु
	अगर (म_भेद(name, "AIF1.1 EQ Mode") == 0)
		वापस 0;
	अगर (म_भेद(name, "AIF1.2 EQ Mode") == 0)
		वापस 1;
	अगर (म_भेद(name, "AIF2 EQ Mode") == 0)
		वापस 2;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wm8994_put_retune_mobile_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;
	काष्ठा wm8994_pdata *pdata = &control->pdata;
	पूर्णांक block = wm8994_get_retune_mobile_block(kcontrol->id.name);
	पूर्णांक value = ucontrol->value.क्रमागतerated.item[0];

	अगर (block < 0)
		वापस block;

	अगर (value >= pdata->num_retune_mobile_cfgs)
		वापस -EINVAL;

	wm8994->retune_mobile_cfg[block] = value;

	wm8994_set_retune_mobile(component, block);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8994_get_retune_mobile_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	पूर्णांक block = wm8994_get_retune_mobile_block(kcontrol->id.name);

	अगर (block < 0)
		वापस block;

	ucontrol->value.क्रमागतerated.item[0] = wm8994->retune_mobile_cfg[block];

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *aअगर_chan_src_text[] = अणु
	"Left", "Right"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(aअगर1adcl_src,
			    WM8994_AIF1_CONTROL_1, 15, aअगर_chan_src_text);

अटल SOC_ENUM_SINGLE_DECL(aअगर1adcr_src,
			    WM8994_AIF1_CONTROL_1, 14, aअगर_chan_src_text);

अटल SOC_ENUM_SINGLE_DECL(aअगर2adcl_src,
			    WM8994_AIF2_CONTROL_1, 15, aअगर_chan_src_text);

अटल SOC_ENUM_SINGLE_DECL(aअगर2adcr_src,
			    WM8994_AIF2_CONTROL_1, 14, aअगर_chan_src_text);

अटल SOC_ENUM_SINGLE_DECL(aअगर1dacl_src,
			    WM8994_AIF1_CONTROL_2, 15, aअगर_chan_src_text);

अटल SOC_ENUM_SINGLE_DECL(aअगर1dacr_src,
			    WM8994_AIF1_CONTROL_2, 14, aअगर_chan_src_text);

अटल SOC_ENUM_SINGLE_DECL(aअगर2dacl_src,
			    WM8994_AIF2_CONTROL_2, 15, aअगर_chan_src_text);

अटल SOC_ENUM_SINGLE_DECL(aअगर2dacr_src,
			    WM8994_AIF2_CONTROL_2, 14, aअगर_chan_src_text);

अटल स्थिर अक्षर *osr_text[] = अणु
	"Low Power", "High Performance",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(dac_osr,
			    WM8994_OVERSAMPLING, 0, osr_text);

अटल SOC_ENUM_SINGLE_DECL(adc_osr,
			    WM8994_OVERSAMPLING, 1, osr_text);

अटल स्थिर काष्ठा snd_kcontrol_new wm8994_common_snd_controls[] = अणु
SOC_DOUBLE_R_TLV("AIF1ADC1 Volume", WM8994_AIF1_ADC1_LEFT_VOLUME,
		 WM8994_AIF1_ADC1_RIGHT_VOLUME,
		 1, 119, 0, digital_tlv),
SOC_DOUBLE_R_TLV("AIF2ADC Volume", WM8994_AIF2_ADC_LEFT_VOLUME,
		 WM8994_AIF2_ADC_RIGHT_VOLUME,
		 1, 119, 0, digital_tlv),

SOC_ENUM("AIF1ADCL Source", aअगर1adcl_src),
SOC_ENUM("AIF1ADCR Source", aअगर1adcr_src),
SOC_ENUM("AIF2ADCL Source", aअगर2adcl_src),
SOC_ENUM("AIF2ADCR Source", aअगर2adcr_src),

SOC_ENUM("AIF1DACL Source", aअगर1dacl_src),
SOC_ENUM("AIF1DACR Source", aअगर1dacr_src),
SOC_ENUM("AIF2DACL Source", aअगर2dacl_src),
SOC_ENUM("AIF2DACR Source", aअगर2dacr_src),

SOC_DOUBLE_R_TLV("AIF1DAC1 Volume", WM8994_AIF1_DAC1_LEFT_VOLUME,
		 WM8994_AIF1_DAC1_RIGHT_VOLUME, 1, 96, 0, digital_tlv),
SOC_DOUBLE_R_TLV("AIF2DAC Volume", WM8994_AIF2_DAC_LEFT_VOLUME,
		 WM8994_AIF2_DAC_RIGHT_VOLUME, 1, 96, 0, digital_tlv),

SOC_SINGLE_TLV("AIF1 Boost Volume", WM8994_AIF1_CONTROL_2, 10, 3, 0, aअगर_tlv),
SOC_SINGLE_TLV("AIF2 Boost Volume", WM8994_AIF2_CONTROL_2, 10, 3, 0, aअगर_tlv),

SOC_SINGLE("AIF1DAC1 EQ Switch", WM8994_AIF1_DAC1_EQ_GAINS_1, 0, 1, 0),
SOC_SINGLE("AIF2 EQ Switch", WM8994_AIF2_EQ_GAINS_1, 0, 1, 0),

WM8994_DRC_SWITCH("AIF1DAC1 DRC Switch", WM8994_AIF1_DRC1_1, 2),
WM8994_DRC_SWITCH("AIF1ADC1L DRC Switch", WM8994_AIF1_DRC1_1, 1),
WM8994_DRC_SWITCH("AIF1ADC1R DRC Switch", WM8994_AIF1_DRC1_1, 0),

WM8994_DRC_SWITCH("AIF2DAC DRC Switch", WM8994_AIF2_DRC_1, 2),
WM8994_DRC_SWITCH("AIF2ADCL DRC Switch", WM8994_AIF2_DRC_1, 1),
WM8994_DRC_SWITCH("AIF2ADCR DRC Switch", WM8994_AIF2_DRC_1, 0),

SOC_SINGLE_TLV("DAC1 Right Sidetone Volume", WM8994_DAC1_MIXER_VOLUMES,
	       5, 12, 0, st_tlv),
SOC_SINGLE_TLV("DAC1 Left Sidetone Volume", WM8994_DAC1_MIXER_VOLUMES,
	       0, 12, 0, st_tlv),
SOC_SINGLE_TLV("DAC2 Right Sidetone Volume", WM8994_DAC2_MIXER_VOLUMES,
	       5, 12, 0, st_tlv),
SOC_SINGLE_TLV("DAC2 Left Sidetone Volume", WM8994_DAC2_MIXER_VOLUMES,
	       0, 12, 0, st_tlv),
SOC_ENUM("Sidetone HPF Mux", sidetone_hpf),
SOC_SINGLE("Sidetone HPF Switch", WM8994_SIDETONE, 6, 1, 0),

SOC_ENUM("AIF1ADC1 HPF Mode", aअगर1adc1_hpf),
SOC_DOUBLE("AIF1ADC1 HPF Switch", WM8994_AIF1_ADC1_FILTERS, 12, 11, 1, 0),

SOC_ENUM("AIF2ADC HPF Mode", aअगर2adc_hpf),
SOC_DOUBLE("AIF2ADC HPF Switch", WM8994_AIF2_ADC_FILTERS, 12, 11, 1, 0),

SOC_ENUM("ADC OSR", adc_osr),
SOC_ENUM("DAC OSR", dac_osr),

SOC_DOUBLE_R_TLV("DAC1 Volume", WM8994_DAC1_LEFT_VOLUME,
		 WM8994_DAC1_RIGHT_VOLUME, 1, 96, 0, digital_tlv),
SOC_DOUBLE_R("DAC1 Switch", WM8994_DAC1_LEFT_VOLUME,
	     WM8994_DAC1_RIGHT_VOLUME, 9, 1, 1),

SOC_DOUBLE_R_TLV("DAC2 Volume", WM8994_DAC2_LEFT_VOLUME,
		 WM8994_DAC2_RIGHT_VOLUME, 1, 96, 0, digital_tlv),
SOC_DOUBLE_R("DAC2 Switch", WM8994_DAC2_LEFT_VOLUME,
	     WM8994_DAC2_RIGHT_VOLUME, 9, 1, 1),

SOC_SINGLE_TLV("SPKL DAC2 Volume", WM8994_SPKMIXL_ATTENUATION,
	       6, 1, 1, wm_hubs_spkmix_tlv),
SOC_SINGLE_TLV("SPKL DAC1 Volume", WM8994_SPKMIXL_ATTENUATION,
	       2, 1, 1, wm_hubs_spkmix_tlv),

SOC_SINGLE_TLV("SPKR DAC2 Volume", WM8994_SPKMIXR_ATTENUATION,
	       6, 1, 1, wm_hubs_spkmix_tlv),
SOC_SINGLE_TLV("SPKR DAC1 Volume", WM8994_SPKMIXR_ATTENUATION,
	       2, 1, 1, wm_hubs_spkmix_tlv),

SOC_SINGLE_TLV("AIF1DAC1 3D Stereo Volume", WM8994_AIF1_DAC1_FILTERS_2,
	       10, 15, 0, wm8994_3d_tlv),
SOC_SINGLE("AIF1DAC1 3D Stereo Switch", WM8994_AIF1_DAC1_FILTERS_2,
	   8, 1, 0),
SOC_SINGLE_TLV("AIF1DAC2 3D Stereo Volume", WM8994_AIF1_DAC2_FILTERS_2,
	       10, 15, 0, wm8994_3d_tlv),
SOC_SINGLE("AIF1DAC2 3D Stereo Switch", WM8994_AIF1_DAC2_FILTERS_2,
	   8, 1, 0),
SOC_SINGLE_TLV("AIF2DAC 3D Stereo Volume", WM8994_AIF2_DAC_FILTERS_2,
	       10, 15, 0, wm8994_3d_tlv),
SOC_SINGLE("AIF2DAC 3D Stereo Switch", WM8994_AIF2_DAC_FILTERS_2,
	   8, 1, 0),
पूर्ण;

/* Controls not available on WM1811 */
अटल स्थिर काष्ठा snd_kcontrol_new wm8994_snd_controls[] = अणु
SOC_DOUBLE_R_TLV("AIF1ADC2 Volume", WM8994_AIF1_ADC2_LEFT_VOLUME,
		 WM8994_AIF1_ADC2_RIGHT_VOLUME,
		 1, 119, 0, digital_tlv),
SOC_DOUBLE_R_TLV("AIF1DAC2 Volume", WM8994_AIF1_DAC2_LEFT_VOLUME,
		 WM8994_AIF1_DAC2_RIGHT_VOLUME, 1, 96, 0, digital_tlv),

SOC_SINGLE("AIF1DAC2 EQ Switch", WM8994_AIF1_DAC2_EQ_GAINS_1, 0, 1, 0),

WM8994_DRC_SWITCH("AIF1DAC2 DRC Switch", WM8994_AIF1_DRC2_1, 2),
WM8994_DRC_SWITCH("AIF1ADC2L DRC Switch", WM8994_AIF1_DRC2_1, 1),
WM8994_DRC_SWITCH("AIF1ADC2R DRC Switch", WM8994_AIF1_DRC2_1, 0),

SOC_ENUM("AIF1ADC2 HPF Mode", aअगर1adc2_hpf),
SOC_DOUBLE("AIF1ADC2 HPF Switch", WM8994_AIF1_ADC2_FILTERS, 12, 11, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8994_eq_controls[] = अणु
SOC_SINGLE_TLV("AIF1DAC1 EQ1 Volume", WM8994_AIF1_DAC1_EQ_GAINS_1, 11, 31, 0,
	       eq_tlv),
SOC_SINGLE_TLV("AIF1DAC1 EQ2 Volume", WM8994_AIF1_DAC1_EQ_GAINS_1, 6, 31, 0,
	       eq_tlv),
SOC_SINGLE_TLV("AIF1DAC1 EQ3 Volume", WM8994_AIF1_DAC1_EQ_GAINS_1, 1, 31, 0,
	       eq_tlv),
SOC_SINGLE_TLV("AIF1DAC1 EQ4 Volume", WM8994_AIF1_DAC1_EQ_GAINS_2, 11, 31, 0,
	       eq_tlv),
SOC_SINGLE_TLV("AIF1DAC1 EQ5 Volume", WM8994_AIF1_DAC1_EQ_GAINS_2, 6, 31, 0,
	       eq_tlv),

SOC_SINGLE_TLV("AIF1DAC2 EQ1 Volume", WM8994_AIF1_DAC2_EQ_GAINS_1, 11, 31, 0,
	       eq_tlv),
SOC_SINGLE_TLV("AIF1DAC2 EQ2 Volume", WM8994_AIF1_DAC2_EQ_GAINS_1, 6, 31, 0,
	       eq_tlv),
SOC_SINGLE_TLV("AIF1DAC2 EQ3 Volume", WM8994_AIF1_DAC2_EQ_GAINS_1, 1, 31, 0,
	       eq_tlv),
SOC_SINGLE_TLV("AIF1DAC2 EQ4 Volume", WM8994_AIF1_DAC2_EQ_GAINS_2, 11, 31, 0,
	       eq_tlv),
SOC_SINGLE_TLV("AIF1DAC2 EQ5 Volume", WM8994_AIF1_DAC2_EQ_GAINS_2, 6, 31, 0,
	       eq_tlv),

SOC_SINGLE_TLV("AIF2 EQ1 Volume", WM8994_AIF2_EQ_GAINS_1, 11, 31, 0,
	       eq_tlv),
SOC_SINGLE_TLV("AIF2 EQ2 Volume", WM8994_AIF2_EQ_GAINS_1, 6, 31, 0,
	       eq_tlv),
SOC_SINGLE_TLV("AIF2 EQ3 Volume", WM8994_AIF2_EQ_GAINS_1, 1, 31, 0,
	       eq_tlv),
SOC_SINGLE_TLV("AIF2 EQ4 Volume", WM8994_AIF2_EQ_GAINS_2, 11, 31, 0,
	       eq_tlv),
SOC_SINGLE_TLV("AIF2 EQ5 Volume", WM8994_AIF2_EQ_GAINS_2, 6, 31, 0,
	       eq_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8994_drc_controls[] = अणु
SND_SOC_BYTES_MASK("AIF1.1 DRC", WM8994_AIF1_DRC1_1, 5,
		   WM8994_AIF1DAC1_DRC_ENA | WM8994_AIF1ADC1L_DRC_ENA |
		   WM8994_AIF1ADC1R_DRC_ENA),
SND_SOC_BYTES_MASK("AIF1.2 DRC", WM8994_AIF1_DRC2_1, 5,
		   WM8994_AIF1DAC2_DRC_ENA | WM8994_AIF1ADC2L_DRC_ENA |
		   WM8994_AIF1ADC2R_DRC_ENA),
SND_SOC_BYTES_MASK("AIF2 DRC", WM8994_AIF2_DRC_1, 5,
		   WM8994_AIF2DAC_DRC_ENA | WM8994_AIF2ADCL_DRC_ENA |
		   WM8994_AIF2ADCR_DRC_ENA),
पूर्ण;

अटल स्थिर अक्षर *wm8958_ng_text[] = अणु
	"30ms", "125ms", "250ms", "500ms",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(wm8958_aअगर1dac1_ng_hold,
			    WM8958_AIF1_DAC1_NOISE_GATE,
			    WM8958_AIF1DAC1_NG_THR_SHIFT,
			    wm8958_ng_text);

अटल SOC_ENUM_SINGLE_DECL(wm8958_aअगर1dac2_ng_hold,
			    WM8958_AIF1_DAC2_NOISE_GATE,
			    WM8958_AIF1DAC2_NG_THR_SHIFT,
			    wm8958_ng_text);

अटल SOC_ENUM_SINGLE_DECL(wm8958_aअगर2dac_ng_hold,
			    WM8958_AIF2_DAC_NOISE_GATE,
			    WM8958_AIF2DAC_NG_THR_SHIFT,
			    wm8958_ng_text);

अटल स्थिर काष्ठा snd_kcontrol_new wm8958_snd_controls[] = अणु
SOC_SINGLE_TLV("AIF3 Boost Volume", WM8958_AIF3_CONTROL_2, 10, 3, 0, aअगर_tlv),

SOC_SINGLE("AIF1DAC1 Noise Gate Switch", WM8958_AIF1_DAC1_NOISE_GATE,
	   WM8958_AIF1DAC1_NG_ENA_SHIFT, 1, 0),
SOC_ENUM("AIF1DAC1 Noise Gate Hold Time", wm8958_aअगर1dac1_ng_hold),
SOC_SINGLE_TLV("AIF1DAC1 Noise Gate Threshold Volume",
	       WM8958_AIF1_DAC1_NOISE_GATE, WM8958_AIF1DAC1_NG_THR_SHIFT,
	       7, 1, ng_tlv),

SOC_SINGLE("AIF1DAC2 Noise Gate Switch", WM8958_AIF1_DAC2_NOISE_GATE,
	   WM8958_AIF1DAC2_NG_ENA_SHIFT, 1, 0),
SOC_ENUM("AIF1DAC2 Noise Gate Hold Time", wm8958_aअगर1dac2_ng_hold),
SOC_SINGLE_TLV("AIF1DAC2 Noise Gate Threshold Volume",
	       WM8958_AIF1_DAC2_NOISE_GATE, WM8958_AIF1DAC2_NG_THR_SHIFT,
	       7, 1, ng_tlv),

SOC_SINGLE("AIF2DAC Noise Gate Switch", WM8958_AIF2_DAC_NOISE_GATE,
	   WM8958_AIF2DAC_NG_ENA_SHIFT, 1, 0),
SOC_ENUM("AIF2DAC Noise Gate Hold Time", wm8958_aअगर2dac_ng_hold),
SOC_SINGLE_TLV("AIF2DAC Noise Gate Threshold Volume",
	       WM8958_AIF2_DAC_NOISE_GATE, WM8958_AIF2DAC_NG_THR_SHIFT,
	       7, 1, ng_tlv),
पूर्ण;

/* We run all mode setting through a function to enक्रमce audio mode */
अटल व्योम wm1811_jackdet_set_mode(काष्ठा snd_soc_component *component, u16 mode)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	अगर (!wm8994->jackdet || !wm8994->micdet[0].jack)
		वापस;

	अगर (wm8994->active_refcount)
		mode = WM1811_JACKDET_MODE_AUDIO;

	अगर (mode == wm8994->jackdet_mode)
		वापस;

	wm8994->jackdet_mode = mode;

	/* Always use audio mode to detect जबतक the प्रणाली is active */
	अगर (mode != WM1811_JACKDET_MODE_NONE)
		mode = WM1811_JACKDET_MODE_AUDIO;

	snd_soc_component_update_bits(component, WM8994_ANTIPOP_2,
			    WM1811_JACKDET_MODE_MASK, mode);
पूर्ण

अटल व्योम active_reference(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	mutex_lock(&wm8994->accdet_lock);

	wm8994->active_refcount++;

	dev_dbg(component->dev, "Active refcount incremented, now %d\n",
		wm8994->active_refcount);

	/* If we're using jack detection go पूर्णांकo audio mode */
	wm1811_jackdet_set_mode(component, WM1811_JACKDET_MODE_AUDIO);

	mutex_unlock(&wm8994->accdet_lock);
पूर्ण

अटल व्योम active_dereference(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	u16 mode;

	mutex_lock(&wm8994->accdet_lock);

	wm8994->active_refcount--;

	dev_dbg(component->dev, "Active refcount decremented, now %d\n",
		wm8994->active_refcount);

	अगर (wm8994->active_refcount == 0) अणु
		/* Go पूर्णांकo appropriate detection only mode */
		अगर (wm8994->jack_mic || wm8994->mic_detecting)
			mode = WM1811_JACKDET_MODE_MIC;
		अन्यथा
			mode = WM1811_JACKDET_MODE_JACK;

		wm1811_jackdet_set_mode(component, mode);
	पूर्ण

	mutex_unlock(&wm8994->accdet_lock);
पूर्ण

अटल पूर्णांक clk_sys_event(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		वापस configure_घड़ी(component);

	हाल SND_SOC_DAPM_POST_PMU:
		/*
		 * JACKDET won't run until we start the घड़ी and it
		 * only reports deltas, make sure we notअगरy the state
		 * up the stack on startup.  Use a *very* generous
		 * समयout क्रम paranoia, there's no urgency and we
		 * करोn't want false reports.
		 */
		अगर (wm8994->jackdet && !wm8994->clk_has_run) अणु
			queue_delayed_work(प्रणाली_घातer_efficient_wq,
					   &wm8994->jackdet_bootstrap,
					   msecs_to_jअगरfies(1000));
			wm8994->clk_has_run = true;
		पूर्ण
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		configure_घड़ी(component);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vmid_reference(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	pm_runसमय_get_sync(component->dev);

	wm8994->vmid_refcount++;

	dev_dbg(component->dev, "Referencing VMID, refcount is now %d\n",
		wm8994->vmid_refcount);

	अगर (wm8994->vmid_refcount == 1) अणु
		snd_soc_component_update_bits(component, WM8994_ANTIPOP_1,
				    WM8994_LINEOUT1_DISCH |
				    WM8994_LINEOUT2_DISCH, 0);

		wm_hubs_vmid_ena(component);

		चयन (wm8994->vmid_mode) अणु
		शेष:
			WARN_ON(शून्य == "Invalid VMID mode");
			fallthrough;
		हाल WM8994_VMID_NORMAL:
			/* Startup bias, VMID ramp & buffer */
			snd_soc_component_update_bits(component, WM8994_ANTIPOP_2,
					    WM8994_BIAS_SRC |
					    WM8994_VMID_DISCH |
					    WM8994_STARTUP_BIAS_ENA |
					    WM8994_VMID_BUF_ENA |
					    WM8994_VMID_RAMP_MASK,
					    WM8994_BIAS_SRC |
					    WM8994_STARTUP_BIAS_ENA |
					    WM8994_VMID_BUF_ENA |
					    (0x2 << WM8994_VMID_RAMP_SHIFT));

			/* Main bias enable, VMID=2x40k */
			snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_1,
					    WM8994_BIAS_ENA |
					    WM8994_VMID_SEL_MASK,
					    WM8994_BIAS_ENA | 0x2);

			msleep(300);

			snd_soc_component_update_bits(component, WM8994_ANTIPOP_2,
					    WM8994_VMID_RAMP_MASK |
					    WM8994_BIAS_SRC,
					    0);
			अवरोध;

		हाल WM8994_VMID_FORCE:
			/* Startup bias, slow VMID ramp & buffer */
			snd_soc_component_update_bits(component, WM8994_ANTIPOP_2,
					    WM8994_BIAS_SRC |
					    WM8994_VMID_DISCH |
					    WM8994_STARTUP_BIAS_ENA |
					    WM8994_VMID_BUF_ENA |
					    WM8994_VMID_RAMP_MASK,
					    WM8994_BIAS_SRC |
					    WM8994_STARTUP_BIAS_ENA |
					    WM8994_VMID_BUF_ENA |
					    (0x2 << WM8994_VMID_RAMP_SHIFT));

			/* Main bias enable, VMID=2x40k */
			snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_1,
					    WM8994_BIAS_ENA |
					    WM8994_VMID_SEL_MASK,
					    WM8994_BIAS_ENA | 0x2);

			msleep(400);

			snd_soc_component_update_bits(component, WM8994_ANTIPOP_2,
					    WM8994_VMID_RAMP_MASK |
					    WM8994_BIAS_SRC,
					    0);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम vmid_dereference(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	wm8994->vmid_refcount--;

	dev_dbg(component->dev, "Dereferencing VMID, refcount is now %d\n",
		wm8994->vmid_refcount);

	अगर (wm8994->vmid_refcount == 0) अणु
		अगर (wm8994->hubs.lineout1_se)
			snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_3,
					    WM8994_LINEOUT1N_ENA |
					    WM8994_LINEOUT1P_ENA,
					    WM8994_LINEOUT1N_ENA |
					    WM8994_LINEOUT1P_ENA);

		अगर (wm8994->hubs.lineout2_se)
			snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_3,
					    WM8994_LINEOUT2N_ENA |
					    WM8994_LINEOUT2P_ENA,
					    WM8994_LINEOUT2N_ENA |
					    WM8994_LINEOUT2P_ENA);

		/* Start disअक्षरging VMID */
		snd_soc_component_update_bits(component, WM8994_ANTIPOP_2,
				    WM8994_BIAS_SRC |
				    WM8994_VMID_DISCH,
				    WM8994_BIAS_SRC |
				    WM8994_VMID_DISCH);

		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_1,
				    WM8994_VMID_SEL_MASK, 0);

		msleep(400);

		/* Active disअक्षरge */
		snd_soc_component_update_bits(component, WM8994_ANTIPOP_1,
				    WM8994_LINEOUT1_DISCH |
				    WM8994_LINEOUT2_DISCH,
				    WM8994_LINEOUT1_DISCH |
				    WM8994_LINEOUT2_DISCH);

		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_3,
				    WM8994_LINEOUT1N_ENA |
				    WM8994_LINEOUT1P_ENA |
				    WM8994_LINEOUT2N_ENA |
				    WM8994_LINEOUT2P_ENA, 0);

		/* Switch off startup biases */
		snd_soc_component_update_bits(component, WM8994_ANTIPOP_2,
				    WM8994_BIAS_SRC |
				    WM8994_STARTUP_BIAS_ENA |
				    WM8994_VMID_BUF_ENA |
				    WM8994_VMID_RAMP_MASK, 0);

		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_1,
				    WM8994_VMID_SEL_MASK, 0);
	पूर्ण

	pm_runसमय_put(component->dev);
पूर्ण

अटल पूर्णांक vmid_event(काष्ठा snd_soc_dapm_widget *w,
		      काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		vmid_reference(component);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		vmid_dereference(component);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool wm8994_check_class_w_digital(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक source = 0;  /* GCC flow analysis can't track enable */
	पूर्णांक reg, reg_r;

	/* We also need the same AIF source क्रम L/R and only one path */
	reg = snd_soc_component_पढ़ो(component, WM8994_DAC1_LEFT_MIXER_ROUTING);
	चयन (reg) अणु
	हाल WM8994_AIF2DACL_TO_DAC1L:
		dev_vdbg(component->dev, "Class W source AIF2DAC\n");
		source = 2 << WM8994_CP_DYN_SRC_SEL_SHIFT;
		अवरोध;
	हाल WM8994_AIF1DAC2L_TO_DAC1L:
		dev_vdbg(component->dev, "Class W source AIF1DAC2\n");
		source = 1 << WM8994_CP_DYN_SRC_SEL_SHIFT;
		अवरोध;
	हाल WM8994_AIF1DAC1L_TO_DAC1L:
		dev_vdbg(component->dev, "Class W source AIF1DAC1\n");
		source = 0 << WM8994_CP_DYN_SRC_SEL_SHIFT;
		अवरोध;
	शेष:
		dev_vdbg(component->dev, "DAC mixer setting: %x\n", reg);
		वापस false;
	पूर्ण

	reg_r = snd_soc_component_पढ़ो(component, WM8994_DAC1_RIGHT_MIXER_ROUTING);
	अगर (reg_r != reg) अणु
		dev_vdbg(component->dev, "Left and right DAC mixers different\n");
		वापस false;
	पूर्ण

	/* Set the source up */
	snd_soc_component_update_bits(component, WM8994_CLASS_W_1,
			    WM8994_CP_DYN_SRC_SEL_MASK, source);

	वापस true;
पूर्ण

अटल व्योम wm8994_update_vu_bits(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(wm8994_vu_bits); i++)
		snd_soc_component_ग_लिखो(component, wm8994_vu_bits[i].reg,
					snd_soc_component_पढ़ो(component,
						       wm8994_vu_bits[i].reg));
	अगर (control->type == WM1811)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(wm8994_adc2_dac2_vu_bits); i++)
		snd_soc_component_ग_लिखो(component,
				wm8994_adc2_dac2_vu_bits[i].reg,
				snd_soc_component_पढ़ो(component,
					wm8994_adc2_dac2_vu_bits[i].reg));
पूर्ण

अटल पूर्णांक aअगर_mclk_set(काष्ठा snd_soc_component *component, पूर्णांक aअगर, bool enable)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक offset, val, clk_idx;
	पूर्णांक ret;

	अगर (aअगर)
		offset = 4;
	अन्यथा
		offset = 0;

	val = snd_soc_component_पढ़ो(component, WM8994_AIF1_CLOCKING_1 + offset);
	val &= WM8994_AIF1CLK_SRC_MASK;

	चयन (val) अणु
	हाल 0:
		clk_idx = WM8994_MCLK1;
		अवरोध;
	हाल 1:
		clk_idx = WM8994_MCLK2;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (enable) अणु
		ret = clk_prepare_enable(wm8994->mclk[clk_idx].clk);
		अगर (ret < 0) अणु
			dev_err(component->dev,	"Failed to enable MCLK%d\n",
				clk_idx);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		clk_disable_unprepare(wm8994->mclk[clk_idx].clk);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aअगर1clk_ev(काष्ठा snd_soc_dapm_widget *w,
		      काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;
	पूर्णांक mask = WM8994_AIF1DAC1L_ENA | WM8994_AIF1DAC1R_ENA;
	पूर्णांक ret;
	पूर्णांक dac;
	पूर्णांक adc;
	पूर्णांक val;

	चयन (control->type) अणु
	हाल WM8994:
	हाल WM8958:
		mask |= WM8994_AIF1DAC2L_ENA | WM8994_AIF1DAC2R_ENA;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		ret = aअगर_mclk_set(component, 0, true);
		अगर (ret < 0)
			वापस ret;

		/* Don't enable बारlot 2 अगर not in use */
		अगर (wm8994->channels[0] <= 2)
			mask &= ~(WM8994_AIF1DAC2L_ENA | WM8994_AIF1DAC2R_ENA);

		val = snd_soc_component_पढ़ो(component, WM8994_AIF1_CONTROL_1);
		अगर ((val & WM8994_AIF1ADCL_SRC) &&
		    (val & WM8994_AIF1ADCR_SRC))
			adc = WM8994_AIF1ADC1R_ENA | WM8994_AIF1ADC2R_ENA;
		अन्यथा अगर (!(val & WM8994_AIF1ADCL_SRC) &&
			 !(val & WM8994_AIF1ADCR_SRC))
			adc = WM8994_AIF1ADC1L_ENA | WM8994_AIF1ADC2L_ENA;
		अन्यथा
			adc = WM8994_AIF1ADC1R_ENA | WM8994_AIF1ADC2R_ENA |
				WM8994_AIF1ADC1L_ENA | WM8994_AIF1ADC2L_ENA;

		val = snd_soc_component_पढ़ो(component, WM8994_AIF1_CONTROL_2);
		अगर ((val & WM8994_AIF1DACL_SRC) &&
		    (val & WM8994_AIF1DACR_SRC))
			dac = WM8994_AIF1DAC1R_ENA | WM8994_AIF1DAC2R_ENA;
		अन्यथा अगर (!(val & WM8994_AIF1DACL_SRC) &&
			 !(val & WM8994_AIF1DACR_SRC))
			dac = WM8994_AIF1DAC1L_ENA | WM8994_AIF1DAC2L_ENA;
		अन्यथा
			dac = WM8994_AIF1DAC1R_ENA | WM8994_AIF1DAC2R_ENA |
				WM8994_AIF1DAC1L_ENA | WM8994_AIF1DAC2L_ENA;

		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_4,
				    mask, adc);
		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_5,
				    mask, dac);
		snd_soc_component_update_bits(component, WM8994_CLOCKING_1,
				    WM8994_AIF1DSPCLK_ENA |
				    WM8994_SYSDSPCLK_ENA,
				    WM8994_AIF1DSPCLK_ENA |
				    WM8994_SYSDSPCLK_ENA);
		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_4, mask,
				    WM8994_AIF1ADC1R_ENA |
				    WM8994_AIF1ADC1L_ENA |
				    WM8994_AIF1ADC2R_ENA |
				    WM8994_AIF1ADC2L_ENA);
		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_5, mask,
				    WM8994_AIF1DAC1R_ENA |
				    WM8994_AIF1DAC1L_ENA |
				    WM8994_AIF1DAC2R_ENA |
				    WM8994_AIF1DAC2L_ENA);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMU:
		wm8994_update_vu_bits(component);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_5,
				    mask, 0);
		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_4,
				    mask, 0);

		val = snd_soc_component_पढ़ो(component, WM8994_CLOCKING_1);
		अगर (val & WM8994_AIF2DSPCLK_ENA)
			val = WM8994_SYSDSPCLK_ENA;
		अन्यथा
			val = 0;
		snd_soc_component_update_bits(component, WM8994_CLOCKING_1,
				    WM8994_SYSDSPCLK_ENA |
				    WM8994_AIF1DSPCLK_ENA, val);
		अवरोध;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMD:
		aअगर_mclk_set(component, 0, false);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aअगर2clk_ev(काष्ठा snd_soc_dapm_widget *w,
		      काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	पूर्णांक ret;
	पूर्णांक dac;
	पूर्णांक adc;
	पूर्णांक val;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		ret = aअगर_mclk_set(component, 1, true);
		अगर (ret < 0)
			वापस ret;

		val = snd_soc_component_पढ़ो(component, WM8994_AIF2_CONTROL_1);
		अगर ((val & WM8994_AIF2ADCL_SRC) &&
		    (val & WM8994_AIF2ADCR_SRC))
			adc = WM8994_AIF2ADCR_ENA;
		अन्यथा अगर (!(val & WM8994_AIF2ADCL_SRC) &&
			 !(val & WM8994_AIF2ADCR_SRC))
			adc = WM8994_AIF2ADCL_ENA;
		अन्यथा
			adc = WM8994_AIF2ADCL_ENA | WM8994_AIF2ADCR_ENA;


		val = snd_soc_component_पढ़ो(component, WM8994_AIF2_CONTROL_2);
		अगर ((val & WM8994_AIF2DACL_SRC) &&
		    (val & WM8994_AIF2DACR_SRC))
			dac = WM8994_AIF2DACR_ENA;
		अन्यथा अगर (!(val & WM8994_AIF2DACL_SRC) &&
			 !(val & WM8994_AIF2DACR_SRC))
			dac = WM8994_AIF2DACL_ENA;
		अन्यथा
			dac = WM8994_AIF2DACL_ENA | WM8994_AIF2DACR_ENA;

		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_4,
				    WM8994_AIF2ADCL_ENA |
				    WM8994_AIF2ADCR_ENA, adc);
		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_5,
				    WM8994_AIF2DACL_ENA |
				    WM8994_AIF2DACR_ENA, dac);
		snd_soc_component_update_bits(component, WM8994_CLOCKING_1,
				    WM8994_AIF2DSPCLK_ENA |
				    WM8994_SYSDSPCLK_ENA,
				    WM8994_AIF2DSPCLK_ENA |
				    WM8994_SYSDSPCLK_ENA);
		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_4,
				    WM8994_AIF2ADCL_ENA |
				    WM8994_AIF2ADCR_ENA,
				    WM8994_AIF2ADCL_ENA |
				    WM8994_AIF2ADCR_ENA);
		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_5,
				    WM8994_AIF2DACL_ENA |
				    WM8994_AIF2DACR_ENA,
				    WM8994_AIF2DACL_ENA |
				    WM8994_AIF2DACR_ENA);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMU:
		wm8994_update_vu_bits(component);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_5,
				    WM8994_AIF2DACL_ENA |
				    WM8994_AIF2DACR_ENA, 0);
		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_4,
				    WM8994_AIF2ADCL_ENA |
				    WM8994_AIF2ADCR_ENA, 0);

		val = snd_soc_component_पढ़ो(component, WM8994_CLOCKING_1);
		अगर (val & WM8994_AIF1DSPCLK_ENA)
			val = WM8994_SYSDSPCLK_ENA;
		अन्यथा
			val = 0;
		snd_soc_component_update_bits(component, WM8994_CLOCKING_1,
				    WM8994_SYSDSPCLK_ENA |
				    WM8994_AIF2DSPCLK_ENA, val);
		अवरोध;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMD:
		aअगर_mclk_set(component, 1, false);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aअगर1clk_late_ev(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		wm8994->aअगर1clk_enable = 1;
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		wm8994->aअगर1clk_disable = 1;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aअगर2clk_late_ev(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		wm8994->aअगर2clk_enable = 1;
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		wm8994->aअगर2clk_disable = 1;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक late_enable_ev(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		अगर (wm8994->aअगर1clk_enable) अणु
			aअगर1clk_ev(w, kcontrol, SND_SOC_DAPM_PRE_PMU);
			snd_soc_component_update_bits(component, WM8994_AIF1_CLOCKING_1,
					    WM8994_AIF1CLK_ENA_MASK,
					    WM8994_AIF1CLK_ENA);
			aअगर1clk_ev(w, kcontrol, SND_SOC_DAPM_POST_PMU);
			wm8994->aअगर1clk_enable = 0;
		पूर्ण
		अगर (wm8994->aअगर2clk_enable) अणु
			aअगर2clk_ev(w, kcontrol, SND_SOC_DAPM_PRE_PMU);
			snd_soc_component_update_bits(component, WM8994_AIF2_CLOCKING_1,
					    WM8994_AIF2CLK_ENA_MASK,
					    WM8994_AIF2CLK_ENA);
			aअगर2clk_ev(w, kcontrol, SND_SOC_DAPM_POST_PMU);
			wm8994->aअगर2clk_enable = 0;
		पूर्ण
		अवरोध;
	पूर्ण

	/* We may also have postponed startup of DSP, handle that. */
	wm8958_aअगर_ev(w, kcontrol, event);

	वापस 0;
पूर्ण

अटल पूर्णांक late_disable_ev(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMD:
		अगर (wm8994->aअगर1clk_disable) अणु
			aअगर1clk_ev(w, kcontrol, SND_SOC_DAPM_PRE_PMD);
			snd_soc_component_update_bits(component, WM8994_AIF1_CLOCKING_1,
					    WM8994_AIF1CLK_ENA_MASK, 0);
			aअगर1clk_ev(w, kcontrol, SND_SOC_DAPM_POST_PMD);
			wm8994->aअगर1clk_disable = 0;
		पूर्ण
		अगर (wm8994->aअगर2clk_disable) अणु
			aअगर2clk_ev(w, kcontrol, SND_SOC_DAPM_PRE_PMD);
			snd_soc_component_update_bits(component, WM8994_AIF2_CLOCKING_1,
					    WM8994_AIF2CLK_ENA_MASK, 0);
			aअगर2clk_ev(w, kcontrol, SND_SOC_DAPM_POST_PMD);
			wm8994->aअगर2clk_disable = 0;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adc_mux_ev(काष्ठा snd_soc_dapm_widget *w,
		      काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	late_enable_ev(w, kcontrol, event);
	वापस 0;
पूर्ण

अटल पूर्णांक micbias_ev(काष्ठा snd_soc_dapm_widget *w,
		      काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	late_enable_ev(w, kcontrol, event);
	वापस 0;
पूर्ण

अटल पूर्णांक dac_ev(काष्ठा snd_soc_dapm_widget *w,
		  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	अचिन्हित पूर्णांक mask = 1 << w->shअगरt;

	snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_5,
			    mask, mask);
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *adc_mux_text[] = अणु
	"ADC",
	"DMIC",
पूर्ण;

अटल SOC_ENUM_SINGLE_VIRT_DECL(adc_क्रमागत, adc_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new adcl_mux =
	SOC_DAPM_ENUM("ADCL Mux", adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new adcr_mux =
	SOC_DAPM_ENUM("ADCR Mux", adc_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new left_speaker_mixer[] = अणु
SOC_DAPM_SINGLE("DAC2 Switch", WM8994_SPEAKER_MIXER, 9, 1, 0),
SOC_DAPM_SINGLE("Input Switch", WM8994_SPEAKER_MIXER, 7, 1, 0),
SOC_DAPM_SINGLE("IN1LP Switch", WM8994_SPEAKER_MIXER, 5, 1, 0),
SOC_DAPM_SINGLE("Output Switch", WM8994_SPEAKER_MIXER, 3, 1, 0),
SOC_DAPM_SINGLE("DAC1 Switch", WM8994_SPEAKER_MIXER, 1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new right_speaker_mixer[] = अणु
SOC_DAPM_SINGLE("DAC2 Switch", WM8994_SPEAKER_MIXER, 8, 1, 0),
SOC_DAPM_SINGLE("Input Switch", WM8994_SPEAKER_MIXER, 6, 1, 0),
SOC_DAPM_SINGLE("IN1RP Switch", WM8994_SPEAKER_MIXER, 4, 1, 0),
SOC_DAPM_SINGLE("Output Switch", WM8994_SPEAKER_MIXER, 2, 1, 0),
SOC_DAPM_SINGLE("DAC1 Switch", WM8994_SPEAKER_MIXER, 0, 1, 0),
पूर्ण;

/* Debugging; dump chip status after DAPM transitions */
अटल पूर्णांक post_ev(काष्ठा snd_soc_dapm_widget *w,
	    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	dev_dbg(component->dev, "SRC status: %x\n",
		snd_soc_component_पढ़ो(component,
			     WM8994_RATE_STATUS));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new aअगर1adc1l_mix[] = अणु
SOC_DAPM_SINGLE("ADC/DMIC Switch", WM8994_AIF1_ADC1_LEFT_MIXER_ROUTING,
		1, 1, 0),
SOC_DAPM_SINGLE("AIF2 Switch", WM8994_AIF1_ADC1_LEFT_MIXER_ROUTING,
		0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aअगर1adc1r_mix[] = अणु
SOC_DAPM_SINGLE("ADC/DMIC Switch", WM8994_AIF1_ADC1_RIGHT_MIXER_ROUTING,
		1, 1, 0),
SOC_DAPM_SINGLE("AIF2 Switch", WM8994_AIF1_ADC1_RIGHT_MIXER_ROUTING,
		0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aअगर1adc2l_mix[] = अणु
SOC_DAPM_SINGLE("DMIC Switch", WM8994_AIF1_ADC2_LEFT_MIXER_ROUTING,
		1, 1, 0),
SOC_DAPM_SINGLE("AIF2 Switch", WM8994_AIF1_ADC2_LEFT_MIXER_ROUTING,
		0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aअगर1adc2r_mix[] = अणु
SOC_DAPM_SINGLE("DMIC Switch", WM8994_AIF1_ADC2_RIGHT_MIXER_ROUTING,
		1, 1, 0),
SOC_DAPM_SINGLE("AIF2 Switch", WM8994_AIF1_ADC2_RIGHT_MIXER_ROUTING,
		0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aअगर2dac2l_mix[] = अणु
SOC_DAPM_SINGLE("Right Sidetone Switch", WM8994_DAC2_LEFT_MIXER_ROUTING,
		5, 1, 0),
SOC_DAPM_SINGLE("Left Sidetone Switch", WM8994_DAC2_LEFT_MIXER_ROUTING,
		4, 1, 0),
SOC_DAPM_SINGLE("AIF2 Switch", WM8994_DAC2_LEFT_MIXER_ROUTING,
		2, 1, 0),
SOC_DAPM_SINGLE("AIF1.2 Switch", WM8994_DAC2_LEFT_MIXER_ROUTING,
		1, 1, 0),
SOC_DAPM_SINGLE("AIF1.1 Switch", WM8994_DAC2_LEFT_MIXER_ROUTING,
		0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aअगर2dac2r_mix[] = अणु
SOC_DAPM_SINGLE("Right Sidetone Switch", WM8994_DAC2_RIGHT_MIXER_ROUTING,
		5, 1, 0),
SOC_DAPM_SINGLE("Left Sidetone Switch", WM8994_DAC2_RIGHT_MIXER_ROUTING,
		4, 1, 0),
SOC_DAPM_SINGLE("AIF2 Switch", WM8994_DAC2_RIGHT_MIXER_ROUTING,
		2, 1, 0),
SOC_DAPM_SINGLE("AIF1.2 Switch", WM8994_DAC2_RIGHT_MIXER_ROUTING,
		1, 1, 0),
SOC_DAPM_SINGLE("AIF1.1 Switch", WM8994_DAC2_RIGHT_MIXER_ROUTING,
		0, 1, 0),
पूर्ण;

#घोषणा WM8994_CLASS_W_SWITCH(xname, reg, shअगरt, max, invert) \
	SOC_SINGLE_EXT(xname, reg, shअगरt, max, invert, \
		snd_soc_dapm_get_volsw, wm8994_put_class_w)

अटल पूर्णांक wm8994_put_class_w(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	पूर्णांक ret;

	ret = snd_soc_dapm_put_volsw(kcontrol, ucontrol);

	wm_hubs_update_class_w(component);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new dac1l_mix[] = अणु
WM8994_CLASS_W_SWITCH("Right Sidetone Switch", WM8994_DAC1_LEFT_MIXER_ROUTING,
		      5, 1, 0),
WM8994_CLASS_W_SWITCH("Left Sidetone Switch", WM8994_DAC1_LEFT_MIXER_ROUTING,
		      4, 1, 0),
WM8994_CLASS_W_SWITCH("AIF2 Switch", WM8994_DAC1_LEFT_MIXER_ROUTING,
		      2, 1, 0),
WM8994_CLASS_W_SWITCH("AIF1.2 Switch", WM8994_DAC1_LEFT_MIXER_ROUTING,
		      1, 1, 0),
WM8994_CLASS_W_SWITCH("AIF1.1 Switch", WM8994_DAC1_LEFT_MIXER_ROUTING,
		      0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new dac1r_mix[] = अणु
WM8994_CLASS_W_SWITCH("Right Sidetone Switch", WM8994_DAC1_RIGHT_MIXER_ROUTING,
		      5, 1, 0),
WM8994_CLASS_W_SWITCH("Left Sidetone Switch", WM8994_DAC1_RIGHT_MIXER_ROUTING,
		      4, 1, 0),
WM8994_CLASS_W_SWITCH("AIF2 Switch", WM8994_DAC1_RIGHT_MIXER_ROUTING,
		      2, 1, 0),
WM8994_CLASS_W_SWITCH("AIF1.2 Switch", WM8994_DAC1_RIGHT_MIXER_ROUTING,
		      1, 1, 0),
WM8994_CLASS_W_SWITCH("AIF1.1 Switch", WM8994_DAC1_RIGHT_MIXER_ROUTING,
		      0, 1, 0),
पूर्ण;

अटल स्थिर अक्षर *sidetone_text[] = अणु
	"ADC/DMIC1", "DMIC2",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(sidetone1_क्रमागत,
			    WM8994_SIDETONE, 0, sidetone_text);

अटल स्थिर काष्ठा snd_kcontrol_new sidetone1_mux =
	SOC_DAPM_ENUM("Left Sidetone Mux", sidetone1_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(sidetone2_क्रमागत,
			    WM8994_SIDETONE, 1, sidetone_text);

अटल स्थिर काष्ठा snd_kcontrol_new sidetone2_mux =
	SOC_DAPM_ENUM("Right Sidetone Mux", sidetone2_क्रमागत);

अटल स्थिर अक्षर *aअगर1dac_text[] = अणु
	"AIF1DACDAT", "AIF3DACDAT",
पूर्ण;

अटल स्थिर अक्षर *loopback_text[] = अणु
	"None", "ADCDAT",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(aअगर1_loopback_क्रमागत,
			    WM8994_AIF1_CONTROL_2,
			    WM8994_AIF1_LOOPBACK_SHIFT,
			    loopback_text);

अटल स्थिर काष्ठा snd_kcontrol_new aअगर1_loopback =
	SOC_DAPM_ENUM("AIF1 Loopback", aअगर1_loopback_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(aअगर2_loopback_क्रमागत,
			    WM8994_AIF2_CONTROL_2,
			    WM8994_AIF2_LOOPBACK_SHIFT,
			    loopback_text);

अटल स्थिर काष्ठा snd_kcontrol_new aअगर2_loopback =
	SOC_DAPM_ENUM("AIF2 Loopback", aअगर2_loopback_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(aअगर1dac_क्रमागत,
			    WM8994_POWER_MANAGEMENT_6, 0, aअगर1dac_text);

अटल स्थिर काष्ठा snd_kcontrol_new aअगर1dac_mux =
	SOC_DAPM_ENUM("AIF1DAC Mux", aअगर1dac_क्रमागत);

अटल स्थिर अक्षर *aअगर2dac_text[] = अणु
	"AIF2DACDAT", "AIF3DACDAT",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(aअगर2dac_क्रमागत,
			    WM8994_POWER_MANAGEMENT_6, 1, aअगर2dac_text);

अटल स्थिर काष्ठा snd_kcontrol_new aअगर2dac_mux =
	SOC_DAPM_ENUM("AIF2DAC Mux", aअगर2dac_क्रमागत);

अटल स्थिर अक्षर *aअगर2adc_text[] = अणु
	"AIF2ADCDAT", "AIF3DACDAT",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(aअगर2adc_क्रमागत,
			    WM8994_POWER_MANAGEMENT_6, 2, aअगर2adc_text);

अटल स्थिर काष्ठा snd_kcontrol_new aअगर2adc_mux =
	SOC_DAPM_ENUM("AIF2ADC Mux", aअगर2adc_क्रमागत);

अटल स्थिर अक्षर *aअगर3adc_text[] = अणु
	"AIF1ADCDAT", "AIF2ADCDAT", "AIF2DACDAT", "Mono PCM",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(wm8994_aअगर3adc_क्रमागत,
			    WM8994_POWER_MANAGEMENT_6, 3, aअगर3adc_text);

अटल स्थिर काष्ठा snd_kcontrol_new wm8994_aअगर3adc_mux =
	SOC_DAPM_ENUM("AIF3ADC Mux", wm8994_aअगर3adc_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(wm8958_aअगर3adc_क्रमागत,
			    WM8994_POWER_MANAGEMENT_6, 3, aअगर3adc_text);

अटल स्थिर काष्ठा snd_kcontrol_new wm8958_aअगर3adc_mux =
	SOC_DAPM_ENUM("AIF3ADC Mux", wm8958_aअगर3adc_क्रमागत);

अटल स्थिर अक्षर *mono_pcm_out_text[] = अणु
	"None", "AIF2ADCL", "AIF2ADCR",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(mono_pcm_out_क्रमागत,
			    WM8994_POWER_MANAGEMENT_6, 9, mono_pcm_out_text);

अटल स्थिर काष्ठा snd_kcontrol_new mono_pcm_out_mux =
	SOC_DAPM_ENUM("Mono PCM Out Mux", mono_pcm_out_क्रमागत);

अटल स्थिर अक्षर *aअगर2dac_src_text[] = अणु
	"AIF2", "AIF3",
पूर्ण;

/* Note that these two control shouldn't be simultaneously चयनed to AIF3 */
अटल SOC_ENUM_SINGLE_DECL(aअगर2dacl_src_क्रमागत,
			    WM8994_POWER_MANAGEMENT_6, 7, aअगर2dac_src_text);

अटल स्थिर काष्ठा snd_kcontrol_new aअगर2dacl_src_mux =
	SOC_DAPM_ENUM("AIF2DACL Mux", aअगर2dacl_src_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(aअगर2dacr_src_क्रमागत,
			    WM8994_POWER_MANAGEMENT_6, 8, aअगर2dac_src_text);

अटल स्थिर काष्ठा snd_kcontrol_new aअगर2dacr_src_mux =
	SOC_DAPM_ENUM("AIF2DACR Mux", aअगर2dacr_src_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8994_lateclk_revd_widमाला_लो[] = अणु
SND_SOC_DAPM_SUPPLY("AIF1CLK", SND_SOC_NOPM, 0, 0, aअगर1clk_late_ev,
	SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("AIF2CLK", SND_SOC_NOPM, 0, 0, aअगर2clk_late_ev,
	SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

SND_SOC_DAPM_PGA_E("Late DAC1L Enable PGA", SND_SOC_NOPM, 0, 0, शून्य, 0,
	late_enable_ev, SND_SOC_DAPM_PRE_PMU),
SND_SOC_DAPM_PGA_E("Late DAC1R Enable PGA", SND_SOC_NOPM, 0, 0, शून्य, 0,
	late_enable_ev, SND_SOC_DAPM_PRE_PMU),
SND_SOC_DAPM_PGA_E("Late DAC2L Enable PGA", SND_SOC_NOPM, 0, 0, शून्य, 0,
	late_enable_ev, SND_SOC_DAPM_PRE_PMU),
SND_SOC_DAPM_PGA_E("Late DAC2R Enable PGA", SND_SOC_NOPM, 0, 0, शून्य, 0,
	late_enable_ev, SND_SOC_DAPM_PRE_PMU),
SND_SOC_DAPM_PGA_E("Direct Voice", SND_SOC_NOPM, 0, 0, शून्य, 0,
	late_enable_ev, SND_SOC_DAPM_PRE_PMU),

SND_SOC_DAPM_MIXER_E("SPKL", WM8994_POWER_MANAGEMENT_3, 8, 0,
		     left_speaker_mixer, ARRAY_SIZE(left_speaker_mixer),
		     late_enable_ev, SND_SOC_DAPM_PRE_PMU),
SND_SOC_DAPM_MIXER_E("SPKR", WM8994_POWER_MANAGEMENT_3, 9, 0,
		     right_speaker_mixer, ARRAY_SIZE(right_speaker_mixer),
		     late_enable_ev, SND_SOC_DAPM_PRE_PMU),
SND_SOC_DAPM_MUX_E("Left Headphone Mux", SND_SOC_NOPM, 0, 0, &wm_hubs_hpl_mux,
		   late_enable_ev, SND_SOC_DAPM_PRE_PMU),
SND_SOC_DAPM_MUX_E("Right Headphone Mux", SND_SOC_NOPM, 0, 0, &wm_hubs_hpr_mux,
		   late_enable_ev, SND_SOC_DAPM_PRE_PMU),

SND_SOC_DAPM_POST("Late Disable PGA", late_disable_ev)
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8994_lateclk_widमाला_लो[] = अणु
SND_SOC_DAPM_SUPPLY("AIF1CLK", WM8994_AIF1_CLOCKING_1, 0, 0, aअगर1clk_ev,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		    SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("AIF2CLK", WM8994_AIF2_CLOCKING_1, 0, 0, aअगर2clk_ev,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		    SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_PGA("Direct Voice", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_MIXER("SPKL", WM8994_POWER_MANAGEMENT_3, 8, 0,
		   left_speaker_mixer, ARRAY_SIZE(left_speaker_mixer)),
SND_SOC_DAPM_MIXER("SPKR", WM8994_POWER_MANAGEMENT_3, 9, 0,
		   right_speaker_mixer, ARRAY_SIZE(right_speaker_mixer)),
SND_SOC_DAPM_MUX("Left Headphone Mux", SND_SOC_NOPM, 0, 0, &wm_hubs_hpl_mux),
SND_SOC_DAPM_MUX("Right Headphone Mux", SND_SOC_NOPM, 0, 0, &wm_hubs_hpr_mux),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8994_dac_revd_widमाला_लो[] = अणु
SND_SOC_DAPM_DAC_E("DAC2L", शून्य, SND_SOC_NOPM, 3, 0,
	dac_ev, SND_SOC_DAPM_PRE_PMU),
SND_SOC_DAPM_DAC_E("DAC2R", शून्य, SND_SOC_NOPM, 2, 0,
	dac_ev, SND_SOC_DAPM_PRE_PMU),
SND_SOC_DAPM_DAC_E("DAC1L", शून्य, SND_SOC_NOPM, 1, 0,
	dac_ev, SND_SOC_DAPM_PRE_PMU),
SND_SOC_DAPM_DAC_E("DAC1R", शून्य, SND_SOC_NOPM, 0, 0,
	dac_ev, SND_SOC_DAPM_PRE_PMU),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8994_dac_widमाला_लो[] = अणु
SND_SOC_DAPM_DAC("DAC2L", शून्य, WM8994_POWER_MANAGEMENT_5, 3, 0),
SND_SOC_DAPM_DAC("DAC2R", शून्य, WM8994_POWER_MANAGEMENT_5, 2, 0),
SND_SOC_DAPM_DAC("DAC1L", शून्य, WM8994_POWER_MANAGEMENT_5, 1, 0),
SND_SOC_DAPM_DAC("DAC1R", शून्य, WM8994_POWER_MANAGEMENT_5, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8994_adc_revd_widमाला_लो[] = अणु
SND_SOC_DAPM_MUX_E("ADCL Mux", WM8994_POWER_MANAGEMENT_4, 1, 0, &adcl_mux,
			adc_mux_ev, SND_SOC_DAPM_PRE_PMU),
SND_SOC_DAPM_MUX_E("ADCR Mux", WM8994_POWER_MANAGEMENT_4, 0, 0, &adcr_mux,
			adc_mux_ev, SND_SOC_DAPM_PRE_PMU),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8994_adc_widमाला_लो[] = अणु
SND_SOC_DAPM_MUX("ADCL Mux", WM8994_POWER_MANAGEMENT_4, 1, 0, &adcl_mux),
SND_SOC_DAPM_MUX("ADCR Mux", WM8994_POWER_MANAGEMENT_4, 0, 0, &adcr_mux),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8994_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("DMIC1DAT"),
SND_SOC_DAPM_INPUT("DMIC2DAT"),
SND_SOC_DAPM_INPUT("Clock"),

SND_SOC_DAPM_SUPPLY_S("MICBIAS Supply", 1, SND_SOC_NOPM, 0, 0, micbias_ev,
		      SND_SOC_DAPM_PRE_PMU),
SND_SOC_DAPM_SUPPLY("VMID", SND_SOC_NOPM, 0, 0, vmid_event,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

SND_SOC_DAPM_SUPPLY("CLK_SYS", SND_SOC_NOPM, 0, 0, clk_sys_event,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		    SND_SOC_DAPM_PRE_PMD),

SND_SOC_DAPM_SUPPLY("DSP1CLK", SND_SOC_NOPM, 3, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("DSP2CLK", SND_SOC_NOPM, 2, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("DSPINTCLK", SND_SOC_NOPM, 1, 0, शून्य, 0),

SND_SOC_DAPM_AIF_OUT("AIF1ADC1L", शून्य,
		     0, SND_SOC_NOPM, 9, 0),
SND_SOC_DAPM_AIF_OUT("AIF1ADC1R", शून्य,
		     0, SND_SOC_NOPM, 8, 0),
SND_SOC_DAPM_AIF_IN_E("AIF1DAC1L", शून्य, 0,
		      SND_SOC_NOPM, 9, 0, wm8958_aअगर_ev,
		      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_AIF_IN_E("AIF1DAC1R", शून्य, 0,
		      SND_SOC_NOPM, 8, 0, wm8958_aअगर_ev,
		      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

SND_SOC_DAPM_AIF_OUT("AIF1ADC2L", शून्य,
		     0, SND_SOC_NOPM, 11, 0),
SND_SOC_DAPM_AIF_OUT("AIF1ADC2R", शून्य,
		     0, SND_SOC_NOPM, 10, 0),
SND_SOC_DAPM_AIF_IN_E("AIF1DAC2L", शून्य, 0,
		      SND_SOC_NOPM, 11, 0, wm8958_aअगर_ev,
		      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_AIF_IN_E("AIF1DAC2R", शून्य, 0,
		      SND_SOC_NOPM, 10, 0, wm8958_aअगर_ev,
		      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

SND_SOC_DAPM_MIXER("AIF1ADC1L Mixer", SND_SOC_NOPM, 0, 0,
		   aअगर1adc1l_mix, ARRAY_SIZE(aअगर1adc1l_mix)),
SND_SOC_DAPM_MIXER("AIF1ADC1R Mixer", SND_SOC_NOPM, 0, 0,
		   aअगर1adc1r_mix, ARRAY_SIZE(aअगर1adc1r_mix)),

SND_SOC_DAPM_MIXER("AIF1ADC2L Mixer", SND_SOC_NOPM, 0, 0,
		   aअगर1adc2l_mix, ARRAY_SIZE(aअगर1adc2l_mix)),
SND_SOC_DAPM_MIXER("AIF1ADC2R Mixer", SND_SOC_NOPM, 0, 0,
		   aअगर1adc2r_mix, ARRAY_SIZE(aअगर1adc2r_mix)),

SND_SOC_DAPM_MIXER("AIF2DAC2L Mixer", SND_SOC_NOPM, 0, 0,
		   aअगर2dac2l_mix, ARRAY_SIZE(aअगर2dac2l_mix)),
SND_SOC_DAPM_MIXER("AIF2DAC2R Mixer", SND_SOC_NOPM, 0, 0,
		   aअगर2dac2r_mix, ARRAY_SIZE(aअगर2dac2r_mix)),

SND_SOC_DAPM_MUX("Left Sidetone", SND_SOC_NOPM, 0, 0, &sidetone1_mux),
SND_SOC_DAPM_MUX("Right Sidetone", SND_SOC_NOPM, 0, 0, &sidetone2_mux),

SND_SOC_DAPM_MIXER("DAC1L Mixer", SND_SOC_NOPM, 0, 0,
		   dac1l_mix, ARRAY_SIZE(dac1l_mix)),
SND_SOC_DAPM_MIXER("DAC1R Mixer", SND_SOC_NOPM, 0, 0,
		   dac1r_mix, ARRAY_SIZE(dac1r_mix)),

SND_SOC_DAPM_AIF_OUT("AIF2ADCL", शून्य, 0,
		     SND_SOC_NOPM, 13, 0),
SND_SOC_DAPM_AIF_OUT("AIF2ADCR", शून्य, 0,
		     SND_SOC_NOPM, 12, 0),
SND_SOC_DAPM_AIF_IN_E("AIF2DACL", शून्य, 0,
		      SND_SOC_NOPM, 13, 0, wm8958_aअगर_ev,
		      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
SND_SOC_DAPM_AIF_IN_E("AIF2DACR", शून्य, 0,
		      SND_SOC_NOPM, 12, 0, wm8958_aअगर_ev,
		      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

SND_SOC_DAPM_AIF_IN("AIF1DACDAT", शून्य, 0, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_AIF_IN("AIF2DACDAT", शून्य, 0, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_AIF_OUT("AIF1ADCDAT", शून्य, 0, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_AIF_OUT("AIF2ADCDAT",  शून्य, 0, SND_SOC_NOPM, 0, 0),

SND_SOC_DAPM_MUX("AIF1DAC Mux", SND_SOC_NOPM, 0, 0, &aअगर1dac_mux),
SND_SOC_DAPM_MUX("AIF2DAC Mux", SND_SOC_NOPM, 0, 0, &aअगर2dac_mux),
SND_SOC_DAPM_MUX("AIF2ADC Mux", SND_SOC_NOPM, 0, 0, &aअगर2adc_mux),

SND_SOC_DAPM_AIF_IN("AIF3DACDAT", शून्य, 0, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_AIF_OUT("AIF3ADCDAT", शून्य, 0, SND_SOC_NOPM, 0, 0),

SND_SOC_DAPM_SUPPLY("TOCLK", WM8994_CLOCKING_1, 4, 0, शून्य, 0),

SND_SOC_DAPM_ADC("DMIC2L", शून्य, WM8994_POWER_MANAGEMENT_4, 5, 0),
SND_SOC_DAPM_ADC("DMIC2R", शून्य, WM8994_POWER_MANAGEMENT_4, 4, 0),
SND_SOC_DAPM_ADC("DMIC1L", शून्य, WM8994_POWER_MANAGEMENT_4, 3, 0),
SND_SOC_DAPM_ADC("DMIC1R", शून्य, WM8994_POWER_MANAGEMENT_4, 2, 0),

/* Power is करोne with the muxes since the ADC घातer also controls the
 * करोwnsampling chain, the chip will स्वतःmatically manage the analogue
 * specअगरic portions.
 */
SND_SOC_DAPM_ADC("ADCL", शून्य, SND_SOC_NOPM, 1, 0),
SND_SOC_DAPM_ADC("ADCR", शून्य, SND_SOC_NOPM, 0, 0),

SND_SOC_DAPM_MUX("AIF1 Loopback", SND_SOC_NOPM, 0, 0, &aअगर1_loopback),
SND_SOC_DAPM_MUX("AIF2 Loopback", SND_SOC_NOPM, 0, 0, &aअगर2_loopback),

SND_SOC_DAPM_POST("Debug log", post_ev),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8994_specअगरic_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_MUX("AIF3ADC Mux", SND_SOC_NOPM, 0, 0, &wm8994_aअगर3adc_mux),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8958_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_SUPPLY("AIF3", WM8994_POWER_MANAGEMENT_6, 5, 1, शून्य, 0),
SND_SOC_DAPM_MUX("Mono PCM Out Mux", SND_SOC_NOPM, 0, 0, &mono_pcm_out_mux),
SND_SOC_DAPM_MUX("AIF2DACL Mux", SND_SOC_NOPM, 0, 0, &aअगर2dacl_src_mux),
SND_SOC_DAPM_MUX("AIF2DACR Mux", SND_SOC_NOPM, 0, 0, &aअगर2dacr_src_mux),
SND_SOC_DAPM_MUX("AIF3ADC Mux", SND_SOC_NOPM, 0, 0, &wm8958_aअगर3adc_mux),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route पूर्णांकercon[] = अणु
	अणु "CLK_SYS", शून्य, "AIF1CLK", check_clk_sys पूर्ण,
	अणु "CLK_SYS", शून्य, "AIF2CLK", check_clk_sys पूर्ण,

	अणु "DSP1CLK", शून्य, "CLK_SYS" पूर्ण,
	अणु "DSP2CLK", शून्य, "CLK_SYS" पूर्ण,
	अणु "DSPINTCLK", शून्य, "CLK_SYS" पूर्ण,

	अणु "AIF1ADC1L", शून्य, "AIF1CLK" पूर्ण,
	अणु "AIF1ADC1L", शून्य, "DSP1CLK" पूर्ण,
	अणु "AIF1ADC1R", शून्य, "AIF1CLK" पूर्ण,
	अणु "AIF1ADC1R", शून्य, "DSP1CLK" पूर्ण,
	अणु "AIF1ADC1R", शून्य, "DSPINTCLK" पूर्ण,

	अणु "AIF1DAC1L", शून्य, "AIF1CLK" पूर्ण,
	अणु "AIF1DAC1L", शून्य, "DSP1CLK" पूर्ण,
	अणु "AIF1DAC1R", शून्य, "AIF1CLK" पूर्ण,
	अणु "AIF1DAC1R", शून्य, "DSP1CLK" पूर्ण,
	अणु "AIF1DAC1R", शून्य, "DSPINTCLK" पूर्ण,

	अणु "AIF1ADC2L", शून्य, "AIF1CLK" पूर्ण,
	अणु "AIF1ADC2L", शून्य, "DSP1CLK" पूर्ण,
	अणु "AIF1ADC2R", शून्य, "AIF1CLK" पूर्ण,
	अणु "AIF1ADC2R", शून्य, "DSP1CLK" पूर्ण,
	अणु "AIF1ADC2R", शून्य, "DSPINTCLK" पूर्ण,

	अणु "AIF1DAC2L", शून्य, "AIF1CLK" पूर्ण,
	अणु "AIF1DAC2L", शून्य, "DSP1CLK" पूर्ण,
	अणु "AIF1DAC2R", शून्य, "AIF1CLK" पूर्ण,
	अणु "AIF1DAC2R", शून्य, "DSP1CLK" पूर्ण,
	अणु "AIF1DAC2R", शून्य, "DSPINTCLK" पूर्ण,

	अणु "AIF2ADCL", शून्य, "AIF2CLK" पूर्ण,
	अणु "AIF2ADCL", शून्य, "DSP2CLK" पूर्ण,
	अणु "AIF2ADCR", शून्य, "AIF2CLK" पूर्ण,
	अणु "AIF2ADCR", शून्य, "DSP2CLK" पूर्ण,
	अणु "AIF2ADCR", शून्य, "DSPINTCLK" पूर्ण,

	अणु "AIF2DACL", शून्य, "AIF2CLK" पूर्ण,
	अणु "AIF2DACL", शून्य, "DSP2CLK" पूर्ण,
	अणु "AIF2DACR", शून्य, "AIF2CLK" पूर्ण,
	अणु "AIF2DACR", शून्य, "DSP2CLK" पूर्ण,
	अणु "AIF2DACR", शून्य, "DSPINTCLK" पूर्ण,

	अणु "DMIC1L", शून्य, "DMIC1DAT" पूर्ण,
	अणु "DMIC1L", शून्य, "CLK_SYS" पूर्ण,
	अणु "DMIC1R", शून्य, "DMIC1DAT" पूर्ण,
	अणु "DMIC1R", शून्य, "CLK_SYS" पूर्ण,
	अणु "DMIC2L", शून्य, "DMIC2DAT" पूर्ण,
	अणु "DMIC2L", शून्य, "CLK_SYS" पूर्ण,
	अणु "DMIC2R", शून्य, "DMIC2DAT" पूर्ण,
	अणु "DMIC2R", शून्य, "CLK_SYS" पूर्ण,

	अणु "ADCL", शून्य, "AIF1CLK" पूर्ण,
	अणु "ADCL", शून्य, "DSP1CLK" पूर्ण,
	अणु "ADCL", शून्य, "DSPINTCLK" पूर्ण,

	अणु "ADCR", शून्य, "AIF1CLK" पूर्ण,
	अणु "ADCR", शून्य, "DSP1CLK" पूर्ण,
	अणु "ADCR", शून्य, "DSPINTCLK" पूर्ण,

	अणु "ADCL Mux", "ADC", "ADCL" पूर्ण,
	अणु "ADCL Mux", "DMIC", "DMIC1L" पूर्ण,
	अणु "ADCR Mux", "ADC", "ADCR" पूर्ण,
	अणु "ADCR Mux", "DMIC", "DMIC1R" पूर्ण,

	अणु "DAC1L", शून्य, "AIF1CLK" पूर्ण,
	अणु "DAC1L", शून्य, "DSP1CLK" पूर्ण,
	अणु "DAC1L", शून्य, "DSPINTCLK" पूर्ण,

	अणु "DAC1R", शून्य, "AIF1CLK" पूर्ण,
	अणु "DAC1R", शून्य, "DSP1CLK" पूर्ण,
	अणु "DAC1R", शून्य, "DSPINTCLK" पूर्ण,

	अणु "DAC2L", शून्य, "AIF2CLK" पूर्ण,
	अणु "DAC2L", शून्य, "DSP2CLK" पूर्ण,
	अणु "DAC2L", शून्य, "DSPINTCLK" पूर्ण,

	अणु "DAC2R", शून्य, "AIF2DACR" पूर्ण,
	अणु "DAC2R", शून्य, "AIF2CLK" पूर्ण,
	अणु "DAC2R", शून्य, "DSP2CLK" पूर्ण,
	अणु "DAC2R", शून्य, "DSPINTCLK" पूर्ण,

	अणु "TOCLK", शून्य, "CLK_SYS" पूर्ण,

	अणु "AIF1DACDAT", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF2DACDAT", शून्य, "AIF2 Playback" पूर्ण,
	अणु "AIF3DACDAT", शून्य, "AIF3 Playback" पूर्ण,

	अणु "AIF1 Capture", शून्य, "AIF1ADCDAT" पूर्ण,
	अणु "AIF2 Capture", शून्य, "AIF2ADCDAT" पूर्ण,
	अणु "AIF3 Capture", शून्य, "AIF3ADCDAT" पूर्ण,

	/* AIF1 outमाला_दो */
	अणु "AIF1ADC1L", शून्य, "AIF1ADC1L Mixer" पूर्ण,
	अणु "AIF1ADC1L Mixer", "ADC/DMIC Switch", "ADCL Mux" पूर्ण,
	अणु "AIF1ADC1L Mixer", "AIF2 Switch", "AIF2DACL" पूर्ण,

	अणु "AIF1ADC1R", शून्य, "AIF1ADC1R Mixer" पूर्ण,
	अणु "AIF1ADC1R Mixer", "ADC/DMIC Switch", "ADCR Mux" पूर्ण,
	अणु "AIF1ADC1R Mixer", "AIF2 Switch", "AIF2DACR" पूर्ण,

	अणु "AIF1ADC2L", शून्य, "AIF1ADC2L Mixer" पूर्ण,
	अणु "AIF1ADC2L Mixer", "DMIC Switch", "DMIC2L" पूर्ण,
	अणु "AIF1ADC2L Mixer", "AIF2 Switch", "AIF2DACL" पूर्ण,

	अणु "AIF1ADC2R", शून्य, "AIF1ADC2R Mixer" पूर्ण,
	अणु "AIF1ADC2R Mixer", "DMIC Switch", "DMIC2R" पूर्ण,
	अणु "AIF1ADC2R Mixer", "AIF2 Switch", "AIF2DACR" पूर्ण,

	/* Pin level routing क्रम AIF3 */
	अणु "AIF1DAC1L", शून्य, "AIF1DAC Mux" पूर्ण,
	अणु "AIF1DAC1R", शून्य, "AIF1DAC Mux" पूर्ण,
	अणु "AIF1DAC2L", शून्य, "AIF1DAC Mux" पूर्ण,
	अणु "AIF1DAC2R", शून्य, "AIF1DAC Mux" पूर्ण,

	अणु "AIF1DAC Mux", "AIF1DACDAT", "AIF1 Loopback" पूर्ण,
	अणु "AIF1DAC Mux", "AIF3DACDAT", "AIF3DACDAT" पूर्ण,
	अणु "AIF2DAC Mux", "AIF2DACDAT", "AIF2 Loopback" पूर्ण,
	अणु "AIF2DAC Mux", "AIF3DACDAT", "AIF3DACDAT" पूर्ण,
	अणु "AIF2ADC Mux", "AIF2ADCDAT", "AIF2ADCL" पूर्ण,
	अणु "AIF2ADC Mux", "AIF2ADCDAT", "AIF2ADCR" पूर्ण,
	अणु "AIF2ADC Mux", "AIF3DACDAT", "AIF3ADCDAT" पूर्ण,

	/* DAC1 inमाला_दो */
	अणु "DAC1L Mixer", "AIF2 Switch", "AIF2DACL" पूर्ण,
	अणु "DAC1L Mixer", "AIF1.2 Switch", "AIF1DAC2L" पूर्ण,
	अणु "DAC1L Mixer", "AIF1.1 Switch", "AIF1DAC1L" पूर्ण,
	अणु "DAC1L Mixer", "Left Sidetone Switch", "Left Sidetone" पूर्ण,
	अणु "DAC1L Mixer", "Right Sidetone Switch", "Right Sidetone" पूर्ण,

	अणु "DAC1R Mixer", "AIF2 Switch", "AIF2DACR" पूर्ण,
	अणु "DAC1R Mixer", "AIF1.2 Switch", "AIF1DAC2R" पूर्ण,
	अणु "DAC1R Mixer", "AIF1.1 Switch", "AIF1DAC1R" पूर्ण,
	अणु "DAC1R Mixer", "Left Sidetone Switch", "Left Sidetone" पूर्ण,
	अणु "DAC1R Mixer", "Right Sidetone Switch", "Right Sidetone" पूर्ण,

	/* DAC2/AIF2 outमाला_दो  */
	अणु "AIF2ADCL", शून्य, "AIF2DAC2L Mixer" पूर्ण,
	अणु "AIF2DAC2L Mixer", "AIF2 Switch", "AIF2DACL" पूर्ण,
	अणु "AIF2DAC2L Mixer", "AIF1.2 Switch", "AIF1DAC2L" पूर्ण,
	अणु "AIF2DAC2L Mixer", "AIF1.1 Switch", "AIF1DAC1L" पूर्ण,
	अणु "AIF2DAC2L Mixer", "Left Sidetone Switch", "Left Sidetone" पूर्ण,
	अणु "AIF2DAC2L Mixer", "Right Sidetone Switch", "Right Sidetone" पूर्ण,

	अणु "AIF2ADCR", शून्य, "AIF2DAC2R Mixer" पूर्ण,
	अणु "AIF2DAC2R Mixer", "AIF2 Switch", "AIF2DACR" पूर्ण,
	अणु "AIF2DAC2R Mixer", "AIF1.2 Switch", "AIF1DAC2R" पूर्ण,
	अणु "AIF2DAC2R Mixer", "AIF1.1 Switch", "AIF1DAC1R" पूर्ण,
	अणु "AIF2DAC2R Mixer", "Left Sidetone Switch", "Left Sidetone" पूर्ण,
	अणु "AIF2DAC2R Mixer", "Right Sidetone Switch", "Right Sidetone" पूर्ण,

	अणु "AIF1ADCDAT", शून्य, "AIF1ADC1L" पूर्ण,
	अणु "AIF1ADCDAT", शून्य, "AIF1ADC1R" पूर्ण,
	अणु "AIF1ADCDAT", शून्य, "AIF1ADC2L" पूर्ण,
	अणु "AIF1ADCDAT", शून्य, "AIF1ADC2R" पूर्ण,

	अणु "AIF2ADCDAT", शून्य, "AIF2ADC Mux" पूर्ण,

	/* AIF3 output */
	अणु "AIF3ADC Mux", "AIF1ADCDAT", "AIF1ADC1L" पूर्ण,
	अणु "AIF3ADC Mux", "AIF1ADCDAT", "AIF1ADC1R" पूर्ण,
	अणु "AIF3ADC Mux", "AIF1ADCDAT", "AIF1ADC2L" पूर्ण,
	अणु "AIF3ADC Mux", "AIF1ADCDAT", "AIF1ADC2R" पूर्ण,
	अणु "AIF3ADC Mux", "AIF2ADCDAT", "AIF2ADCL" पूर्ण,
	अणु "AIF3ADC Mux", "AIF2ADCDAT", "AIF2ADCR" पूर्ण,
	अणु "AIF3ADC Mux", "AIF2DACDAT", "AIF2DACL" पूर्ण,
	अणु "AIF3ADC Mux", "AIF2DACDAT", "AIF2DACR" पूर्ण,

	अणु "AIF3ADCDAT", शून्य, "AIF3ADC Mux" पूर्ण,

	/* Loopback */
	अणु "AIF1 Loopback", "ADCDAT", "AIF1ADCDAT" पूर्ण,
	अणु "AIF1 Loopback", "None", "AIF1DACDAT" पूर्ण,
	अणु "AIF2 Loopback", "ADCDAT", "AIF2ADCDAT" पूर्ण,
	अणु "AIF2 Loopback", "None", "AIF2DACDAT" पूर्ण,

	/* Sidetone */
	अणु "Left Sidetone", "ADC/DMIC1", "ADCL Mux" पूर्ण,
	अणु "Left Sidetone", "DMIC2", "DMIC2L" पूर्ण,
	अणु "Right Sidetone", "ADC/DMIC1", "ADCR Mux" पूर्ण,
	अणु "Right Sidetone", "DMIC2", "DMIC2R" पूर्ण,

	/* Output stages */
	अणु "Left Output Mixer", "DAC Switch", "DAC1L" पूर्ण,
	अणु "Right Output Mixer", "DAC Switch", "DAC1R" पूर्ण,

	अणु "SPKL", "DAC1 Switch", "DAC1L" पूर्ण,
	अणु "SPKL", "DAC2 Switch", "DAC2L" पूर्ण,

	अणु "SPKR", "DAC1 Switch", "DAC1R" पूर्ण,
	अणु "SPKR", "DAC2 Switch", "DAC2R" पूर्ण,

	अणु "Left Headphone Mux", "DAC", "DAC1L" पूर्ण,
	अणु "Right Headphone Mux", "DAC", "DAC1R" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8994_lateclk_revd_पूर्णांकercon[] = अणु
	अणु "DAC1L", शून्य, "Late DAC1L Enable PGA" पूर्ण,
	अणु "Late DAC1L Enable PGA", शून्य, "DAC1L Mixer" पूर्ण,
	अणु "DAC1R", शून्य, "Late DAC1R Enable PGA" पूर्ण,
	अणु "Late DAC1R Enable PGA", शून्य, "DAC1R Mixer" पूर्ण,
	अणु "DAC2L", शून्य, "Late DAC2L Enable PGA" पूर्ण,
	अणु "Late DAC2L Enable PGA", शून्य, "AIF2DAC2L Mixer" पूर्ण,
	अणु "DAC2R", शून्य, "Late DAC2R Enable PGA" पूर्ण,
	अणु "Late DAC2R Enable PGA", शून्य, "AIF2DAC2R Mixer" पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8994_lateclk_पूर्णांकercon[] = अणु
	अणु "DAC1L", शून्य, "DAC1L Mixer" पूर्ण,
	अणु "DAC1R", शून्य, "DAC1R Mixer" पूर्ण,
	अणु "DAC2L", शून्य, "AIF2DAC2L Mixer" पूर्ण,
	अणु "DAC2R", शून्य, "AIF2DAC2R Mixer" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8994_revd_पूर्णांकercon[] = अणु
	अणु "AIF1DACDAT", शून्य, "AIF2DACDAT" पूर्ण,
	अणु "AIF2DACDAT", शून्य, "AIF1DACDAT" पूर्ण,
	अणु "AIF1ADCDAT", शून्य, "AIF2ADCDAT" पूर्ण,
	अणु "AIF2ADCDAT", शून्य, "AIF1ADCDAT" पूर्ण,
	अणु "MICBIAS1", शून्य, "CLK_SYS" पूर्ण,
	अणु "MICBIAS1", शून्य, "MICBIAS Supply" पूर्ण,
	अणु "MICBIAS2", शून्य, "CLK_SYS" पूर्ण,
	अणु "MICBIAS2", शून्य, "MICBIAS Supply" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8994_पूर्णांकercon[] = अणु
	अणु "AIF2DACL", शून्य, "AIF2DAC Mux" पूर्ण,
	अणु "AIF2DACR", शून्य, "AIF2DAC Mux" पूर्ण,
	अणु "MICBIAS1", शून्य, "VMID" पूर्ण,
	अणु "MICBIAS2", शून्य, "VMID" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8958_पूर्णांकercon[] = अणु
	अणु "AIF2DACL", शून्य, "AIF2DACL Mux" पूर्ण,
	अणु "AIF2DACR", शून्य, "AIF2DACR Mux" पूर्ण,

	अणु "AIF2DACL Mux", "AIF2", "AIF2DAC Mux" पूर्ण,
	अणु "AIF2DACL Mux", "AIF3", "AIF3DACDAT" पूर्ण,
	अणु "AIF2DACR Mux", "AIF2", "AIF2DAC Mux" पूर्ण,
	अणु "AIF2DACR Mux", "AIF3", "AIF3DACDAT" पूर्ण,

	अणु "AIF3DACDAT", शून्य, "AIF3" पूर्ण,
	अणु "AIF3ADCDAT", शून्य, "AIF3" पूर्ण,

	अणु "Mono PCM Out Mux", "AIF2ADCL", "AIF2ADCL" पूर्ण,
	अणु "Mono PCM Out Mux", "AIF2ADCR", "AIF2ADCR" पूर्ण,

	अणु "AIF3ADC Mux", "Mono PCM", "Mono PCM Out Mux" पूर्ण,
पूर्ण;

/* The size in bits of the FLL भागide multiplied by 10
 * to allow rounding later */
#घोषणा FIXED_FLL_SIZE ((1 << 16) * 10)

काष्ठा fll_भाग अणु
	u16 outभाग;
	u16 n;
	u16 k;
	u16 lambda;
	u16 clk_ref_भाग;
	u16 fll_fratio;
पूर्ण;

अटल पूर्णांक wm8994_get_fll_config(काष्ठा wm8994 *control, काष्ठा fll_भाग *fll,
				 पूर्णांक freq_in, पूर्णांक freq_out)
अणु
	u64 Kpart;
	अचिन्हित पूर्णांक K, Nभाग, Nmod, gcd_fll;

	pr_debug("FLL input=%dHz, output=%dHz\n", freq_in, freq_out);

	/* Scale the input frequency करोwn to <= 13.5MHz */
	fll->clk_ref_भाग = 0;
	जबतक (freq_in > 13500000) अणु
		fll->clk_ref_भाग++;
		freq_in /= 2;

		अगर (fll->clk_ref_भाग > 3)
			वापस -EINVAL;
	पूर्ण
	pr_debug("CLK_REF_DIV=%d, Fref=%dHz\n", fll->clk_ref_भाग, freq_in);

	/* Scale the output to give 90MHz<=Fvco<=100MHz */
	fll->outभाग = 3;
	जबतक (freq_out * (fll->outभाग + 1) < 90000000) अणु
		fll->outभाग++;
		अगर (fll->outभाग > 63)
			वापस -EINVAL;
	पूर्ण
	freq_out *= fll->outभाग + 1;
	pr_debug("OUTDIV=%d, Fvco=%dHz\n", fll->outभाग, freq_out);

	अगर (freq_in > 1000000) अणु
		fll->fll_fratio = 0;
	पूर्ण अन्यथा अगर (freq_in > 256000) अणु
		fll->fll_fratio = 1;
		freq_in *= 2;
	पूर्ण अन्यथा अगर (freq_in > 128000) अणु
		fll->fll_fratio = 2;
		freq_in *= 4;
	पूर्ण अन्यथा अगर (freq_in > 64000) अणु
		fll->fll_fratio = 3;
		freq_in *= 8;
	पूर्ण अन्यथा अणु
		fll->fll_fratio = 4;
		freq_in *= 16;
	पूर्ण
	pr_debug("FLL_FRATIO=%d, Fref=%dHz\n", fll->fll_fratio, freq_in);

	/* Now, calculate N.K */
	Nभाग = freq_out / freq_in;

	fll->n = Nभाग;
	Nmod = freq_out % freq_in;
	pr_debug("Nmod=%d\n", Nmod);

	चयन (control->type) अणु
	हाल WM8994:
		/* Calculate fractional part - scale up so we can round. */
		Kpart = FIXED_FLL_SIZE * (दीर्घ दीर्घ)Nmod;

		करो_भाग(Kpart, freq_in);

		K = Kpart & 0xFFFFFFFF;

		अगर ((K % 10) >= 5)
			K += 5;

		/* Move करोwn to proper range now rounding is करोne */
		fll->k = K / 10;
		fll->lambda = 0;

		pr_debug("N=%x K=%x\n", fll->n, fll->k);
		अवरोध;

	शेष:
		gcd_fll = gcd(freq_out, freq_in);

		fll->k = (freq_out - (freq_in * fll->n)) / gcd_fll;
		fll->lambda = freq_in / gcd_fll;
		
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक _wm8994_set_fll(काष्ठा snd_soc_component *component, पूर्णांक id, पूर्णांक src,
			  अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;
	पूर्णांक reg_offset, ret;
	काष्ठा fll_भाग fll;
	u16 reg, clk1, aअगर_reg, aअगर_src;
	अचिन्हित दीर्घ समयout;
	bool was_enabled;
	काष्ठा clk *mclk;

	चयन (id) अणु
	हाल WM8994_FLL1:
		reg_offset = 0;
		id = 0;
		aअगर_src = 0x10;
		अवरोध;
	हाल WM8994_FLL2:
		reg_offset = 0x20;
		id = 1;
		aअगर_src = 0x18;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	reg = snd_soc_component_पढ़ो(component, WM8994_FLL1_CONTROL_1 + reg_offset);
	was_enabled = reg & WM8994_FLL1_ENA;

	चयन (src) अणु
	हाल 0:
		/* Allow no source specअगरication when stopping */
		अगर (freq_out)
			वापस -EINVAL;
		src = wm8994->fll[id].src;
		अवरोध;
	हाल WM8994_FLL_SRC_MCLK1:
	हाल WM8994_FLL_SRC_MCLK2:
	हाल WM8994_FLL_SRC_LRCLK:
	हाल WM8994_FLL_SRC_BCLK:
		अवरोध;
	हाल WM8994_FLL_SRC_INTERNAL:
		freq_in = 12000000;
		freq_out = 12000000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Are we changing anything? */
	अगर (wm8994->fll[id].src == src &&
	    wm8994->fll[id].in == freq_in && wm8994->fll[id].out == freq_out)
		वापस 0;

	/* If we're stopping the FLL reकरो the old config - no
	 * रेजिस्टरs will actually be written but we aव्योम GCC flow
	 * analysis bugs spewing warnings.
	 */
	अगर (freq_out)
		ret = wm8994_get_fll_config(control, &fll, freq_in, freq_out);
	अन्यथा
		ret = wm8994_get_fll_config(control, &fll, wm8994->fll[id].in,
					    wm8994->fll[id].out);
	अगर (ret < 0)
		वापस ret;

	/* Make sure that we're not providing SYSCLK right now */
	clk1 = snd_soc_component_पढ़ो(component, WM8994_CLOCKING_1);
	अगर (clk1 & WM8994_SYSCLK_SRC)
		aअगर_reg = WM8994_AIF2_CLOCKING_1;
	अन्यथा
		aअगर_reg = WM8994_AIF1_CLOCKING_1;
	reg = snd_soc_component_पढ़ो(component, aअगर_reg);

	अगर ((reg & WM8994_AIF1CLK_ENA) &&
	    (reg & WM8994_AIF1CLK_SRC_MASK) == aअगर_src) अणु
		dev_err(component->dev, "FLL%d is currently providing SYSCLK\n",
			id + 1);
		वापस -EBUSY;
	पूर्ण

	/* We always need to disable the FLL जबतक reconfiguring */
	snd_soc_component_update_bits(component, WM8994_FLL1_CONTROL_1 + reg_offset,
			    WM8994_FLL1_ENA, 0);

	/* Disable MCLK अगर needed beक्रमe we possibly change to new घड़ी parent */
	अगर (was_enabled) अणु
		reg = snd_soc_component_पढ़ो(component, WM8994_FLL1_CONTROL_5
							+ reg_offset);
		reg = ((reg & WM8994_FLL1_REFCLK_SRC_MASK)
			>> WM8994_FLL1_REFCLK_SRC_SHIFT) + 1;

		चयन (reg) अणु
		हाल WM8994_FLL_SRC_MCLK1:
			mclk = wm8994->mclk[WM8994_MCLK1].clk;
			अवरोध;
		हाल WM8994_FLL_SRC_MCLK2:
			mclk = wm8994->mclk[WM8994_MCLK2].clk;
			अवरोध;
		शेष:
			mclk = शून्य;
		पूर्ण

		clk_disable_unprepare(mclk);
	पूर्ण

	अगर (wm8994->fll_byp && src == WM8994_FLL_SRC_BCLK &&
	    freq_in == freq_out && freq_out) अणु
		dev_dbg(component->dev, "Bypassing FLL%d\n", id + 1);
		snd_soc_component_update_bits(component, WM8994_FLL1_CONTROL_5 + reg_offset,
				    WM8958_FLL1_BYP, WM8958_FLL1_BYP);
		जाओ out;
	पूर्ण

	reg = (fll.outभाग << WM8994_FLL1_OUTDIV_SHIFT) |
		(fll.fll_fratio << WM8994_FLL1_FRATIO_SHIFT);
	snd_soc_component_update_bits(component, WM8994_FLL1_CONTROL_2 + reg_offset,
			    WM8994_FLL1_OUTDIV_MASK |
			    WM8994_FLL1_FRATIO_MASK, reg);

	snd_soc_component_update_bits(component, WM8994_FLL1_CONTROL_3 + reg_offset,
			    WM8994_FLL1_K_MASK, fll.k);

	snd_soc_component_update_bits(component, WM8994_FLL1_CONTROL_4 + reg_offset,
			    WM8994_FLL1_N_MASK,
			    fll.n << WM8994_FLL1_N_SHIFT);

	अगर (fll.lambda) अणु
		snd_soc_component_update_bits(component, WM8958_FLL1_EFS_1 + reg_offset,
				    WM8958_FLL1_LAMBDA_MASK,
				    fll.lambda);
		snd_soc_component_update_bits(component, WM8958_FLL1_EFS_2 + reg_offset,
				    WM8958_FLL1_EFS_ENA, WM8958_FLL1_EFS_ENA);
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component, WM8958_FLL1_EFS_2 + reg_offset,
				    WM8958_FLL1_EFS_ENA, 0);
	पूर्ण

	snd_soc_component_update_bits(component, WM8994_FLL1_CONTROL_5 + reg_offset,
			    WM8994_FLL1_FRC_NCO | WM8958_FLL1_BYP |
			    WM8994_FLL1_REFCLK_DIV_MASK |
			    WM8994_FLL1_REFCLK_SRC_MASK,
			    ((src == WM8994_FLL_SRC_INTERNAL)
			     << WM8994_FLL1_FRC_NCO_SHIFT) |
			    (fll.clk_ref_भाग << WM8994_FLL1_REFCLK_DIV_SHIFT) |
			    (src - 1));

	/* Clear any pending completion from a previous failure */
	try_रुको_क्रम_completion(&wm8994->fll_locked[id]);

	चयन (src) अणु
	हाल WM8994_FLL_SRC_MCLK1:
		mclk = wm8994->mclk[WM8994_MCLK1].clk;
		अवरोध;
	हाल WM8994_FLL_SRC_MCLK2:
		mclk = wm8994->mclk[WM8994_MCLK2].clk;
		अवरोध;
	शेष:
		mclk = शून्य;
	पूर्ण

	/* Enable (with fractional mode अगर required) */
	अगर (freq_out) अणु
		ret = clk_prepare_enable(mclk);
		अगर (ret < 0) अणु
			dev_err(component->dev, "Failed to enable MCLK for FLL%d\n",
				id + 1);
			वापस ret;
		पूर्ण

		/* Enable VMID अगर we need it */
		अगर (!was_enabled) अणु

			active_reference(component);

			चयन (control->type) अणु
			हाल WM8994:
				vmid_reference(component);
				अवरोध;
			हाल WM8958:
				अगर (control->revision < 1)
					vmid_reference(component);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण

		reg = WM8994_FLL1_ENA;

		अगर (fll.k)
			reg |= WM8994_FLL1_FRAC;
		अगर (src == WM8994_FLL_SRC_INTERNAL)
			reg |= WM8994_FLL1_OSC_ENA;

		snd_soc_component_update_bits(component, WM8994_FLL1_CONTROL_1 + reg_offset,
				    WM8994_FLL1_ENA | WM8994_FLL1_OSC_ENA |
				    WM8994_FLL1_FRAC, reg);

		अगर (wm8994->fll_locked_irq) अणु
			समयout = रुको_क्रम_completion_समयout(&wm8994->fll_locked[id],
							      msecs_to_jअगरfies(10));
			अगर (समयout == 0)
				dev_warn(component->dev,
					 "Timed out waiting for FLL lock\n");
		पूर्ण अन्यथा अणु
			msleep(5);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (was_enabled) अणु
			चयन (control->type) अणु
			हाल WM8994:
				vmid_dereference(component);
				अवरोध;
			हाल WM8958:
				अगर (control->revision < 1)
					vmid_dereference(component);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

			active_dereference(component);
		पूर्ण
	पूर्ण

out:
	wm8994->fll[id].in = freq_in;
	wm8994->fll[id].out = freq_out;
	wm8994->fll[id].src = src;

	configure_घड़ी(component);

	/*
	 * If SYSCLK will be less than 50kHz adjust AIFnCLK भागiders
	 * क्रम detection.
	 */
	अगर (max(wm8994->aअगरclk[0], wm8994->aअगरclk[1]) < 50000) अणु
		dev_dbg(component->dev, "Configuring AIFs for 128fs\n");

		wm8994->aअगरभाग[0] = snd_soc_component_पढ़ो(component, WM8994_AIF1_RATE)
			& WM8994_AIF1CLK_RATE_MASK;
		wm8994->aअगरभाग[1] = snd_soc_component_पढ़ो(component, WM8994_AIF2_RATE)
			& WM8994_AIF1CLK_RATE_MASK;

		snd_soc_component_update_bits(component, WM8994_AIF1_RATE,
				    WM8994_AIF1CLK_RATE_MASK, 0x1);
		snd_soc_component_update_bits(component, WM8994_AIF2_RATE,
				    WM8994_AIF2CLK_RATE_MASK, 0x1);
	पूर्ण अन्यथा अगर (wm8994->aअगरभाग[0]) अणु
		snd_soc_component_update_bits(component, WM8994_AIF1_RATE,
				    WM8994_AIF1CLK_RATE_MASK,
				    wm8994->aअगरभाग[0]);
		snd_soc_component_update_bits(component, WM8994_AIF2_RATE,
				    WM8994_AIF2CLK_RATE_MASK,
				    wm8994->aअगरभाग[1]);

		wm8994->aअगरभाग[0] = 0;
		wm8994->aअगरभाग[1] = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t wm8994_fll_locked_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा completion *completion = data;

	complete(completion);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक opclk_भागs[] = अणु 10, 20, 30, 40, 55, 60, 80, 120, 160 पूर्ण;

अटल पूर्णांक wm8994_set_fll(काष्ठा snd_soc_dai *dai, पूर्णांक id, पूर्णांक src,
			  अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	वापस _wm8994_set_fll(dai->component, id, src, freq_in, freq_out);
पूर्ण

अटल पूर्णांक wm8994_set_mclk_rate(काष्ठा wm8994_priv *wm8994, अचिन्हित पूर्णांक id,
				अचिन्हित पूर्णांक *freq)
अणु
	पूर्णांक ret;

	अगर (!wm8994->mclk[id].clk || *freq == wm8994->mclk_rate[id])
		वापस 0;

	ret = clk_set_rate(wm8994->mclk[id].clk, *freq);
	अगर (ret < 0)
		वापस ret;

	*freq = clk_get_rate(wm8994->mclk[id].clk);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8994_set_dai_sysclk(काष्ठा snd_soc_dai *dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret, i;

	चयन (dai->id) अणु
	हाल 1:
	हाल 2:
		अवरोध;

	शेष:
		/* AIF3 shares घड़ीing with AIF1/2 */
		वापस -EINVAL;
	पूर्ण

	चयन (clk_id) अणु
	हाल WM8994_SYSCLK_MCLK1:
		wm8994->sysclk[dai->id - 1] = WM8994_SYSCLK_MCLK1;

		ret = wm8994_set_mclk_rate(wm8994, dai->id - 1, &freq);
		अगर (ret < 0)
			वापस ret;

		wm8994->mclk_rate[0] = freq;
		dev_dbg(dai->dev, "AIF%d using MCLK1 at %uHz\n",
			dai->id, freq);
		अवरोध;

	हाल WM8994_SYSCLK_MCLK2:
		/* TODO: Set GPIO AF */
		wm8994->sysclk[dai->id - 1] = WM8994_SYSCLK_MCLK2;

		ret = wm8994_set_mclk_rate(wm8994, dai->id - 1, &freq);
		अगर (ret < 0)
			वापस ret;

		wm8994->mclk_rate[1] = freq;
		dev_dbg(dai->dev, "AIF%d using MCLK2 at %uHz\n",
			dai->id, freq);
		अवरोध;

	हाल WM8994_SYSCLK_FLL1:
		wm8994->sysclk[dai->id - 1] = WM8994_SYSCLK_FLL1;
		dev_dbg(dai->dev, "AIF%d using FLL1\n", dai->id);
		अवरोध;

	हाल WM8994_SYSCLK_FLL2:
		wm8994->sysclk[dai->id - 1] = WM8994_SYSCLK_FLL2;
		dev_dbg(dai->dev, "AIF%d using FLL2\n", dai->id);
		अवरोध;

	हाल WM8994_SYSCLK_OPCLK:
		/* Special हाल - a भागision (बार 10) is given and
		 * no effect on मुख्य घड़ीing.
		 */
		अगर (freq) अणु
			क्रम (i = 0; i < ARRAY_SIZE(opclk_भागs); i++)
				अगर (opclk_भागs[i] == freq)
					अवरोध;
			अगर (i == ARRAY_SIZE(opclk_भागs))
				वापस -EINVAL;
			snd_soc_component_update_bits(component, WM8994_CLOCKING_2,
					    WM8994_OPCLK_DIV_MASK, i);
			snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_2,
					    WM8994_OPCLK_ENA, WM8994_OPCLK_ENA);
		पूर्ण अन्यथा अणु
			snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_2,
					    WM8994_OPCLK_ENA, 0);
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	configure_घड़ी(component);

	/*
	 * If SYSCLK will be less than 50kHz adjust AIFnCLK भागiders
	 * क्रम detection.
	 */
	अगर (max(wm8994->aअगरclk[0], wm8994->aअगरclk[1]) < 50000) अणु
		dev_dbg(component->dev, "Configuring AIFs for 128fs\n");

		wm8994->aअगरभाग[0] = snd_soc_component_पढ़ो(component, WM8994_AIF1_RATE)
			& WM8994_AIF1CLK_RATE_MASK;
		wm8994->aअगरभाग[1] = snd_soc_component_पढ़ो(component, WM8994_AIF2_RATE)
			& WM8994_AIF1CLK_RATE_MASK;

		snd_soc_component_update_bits(component, WM8994_AIF1_RATE,
				    WM8994_AIF1CLK_RATE_MASK, 0x1);
		snd_soc_component_update_bits(component, WM8994_AIF2_RATE,
				    WM8994_AIF2CLK_RATE_MASK, 0x1);
	पूर्ण अन्यथा अगर (wm8994->aअगरभाग[0]) अणु
		snd_soc_component_update_bits(component, WM8994_AIF1_RATE,
				    WM8994_AIF1CLK_RATE_MASK,
				    wm8994->aअगरभाग[0]);
		snd_soc_component_update_bits(component, WM8994_AIF2_RATE,
				    WM8994_AIF2CLK_RATE_MASK,
				    wm8994->aअगरभाग[1]);

		wm8994->aअगरभाग[0] = 0;
		wm8994->aअगरभाग[1] = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8994_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;

	wm_hubs_set_bias_level(component, level);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		/* MICBIAS पूर्णांकo regulating mode */
		चयन (control->type) अणु
		हाल WM8958:
		हाल WM1811:
			snd_soc_component_update_bits(component, WM8958_MICBIAS1,
					    WM8958_MICB1_MODE, 0);
			snd_soc_component_update_bits(component, WM8958_MICBIAS2,
					    WM8958_MICB2_MODE, 0);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_STANDBY)
			active_reference(component);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			चयन (control->type) अणु
			हाल WM8958:
				अगर (control->revision == 0) अणु
					/* Optimise perक्रमmance क्रम rev A */
					snd_soc_component_update_bits(component,
							    WM8958_CHARGE_PUMP_2,
							    WM8958_CP_DISCH,
							    WM8958_CP_DISCH);
				पूर्ण
				अवरोध;

			शेष:
				अवरोध;
			पूर्ण

			/* Disअक्षरge LINEOUT1 & 2 */
			snd_soc_component_update_bits(component, WM8994_ANTIPOP_1,
					    WM8994_LINEOUT1_DISCH |
					    WM8994_LINEOUT2_DISCH,
					    WM8994_LINEOUT1_DISCH |
					    WM8994_LINEOUT2_DISCH);
		पूर्ण

		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_PREPARE)
			active_dereference(component);

		/* MICBIAS पूर्णांकo bypass mode on newer devices */
		चयन (control->type) अणु
		हाल WM8958:
		हाल WM1811:
			snd_soc_component_update_bits(component, WM8958_MICBIAS1,
					    WM8958_MICB1_MODE,
					    WM8958_MICB1_MODE);
			snd_soc_component_update_bits(component, WM8958_MICBIAS2,
					    WM8958_MICB2_MODE,
					    WM8958_MICB2_MODE);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_STANDBY)
			wm8994->cur_fw = शून्य;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक wm8994_vmid_mode(काष्ठा snd_soc_component *component, क्रमागत wm8994_vmid_mode mode)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	चयन (mode) अणु
	हाल WM8994_VMID_NORMAL:
		snd_soc_dapm_mutex_lock(dapm);

		अगर (wm8994->hubs.lineout1_se) अणु
			snd_soc_dapm_disable_pin_unlocked(dapm,
							  "LINEOUT1N Driver");
			snd_soc_dapm_disable_pin_unlocked(dapm,
							  "LINEOUT1P Driver");
		पूर्ण
		अगर (wm8994->hubs.lineout2_se) अणु
			snd_soc_dapm_disable_pin_unlocked(dapm,
							  "LINEOUT2N Driver");
			snd_soc_dapm_disable_pin_unlocked(dapm,
							  "LINEOUT2P Driver");
		पूर्ण

		/* Do the sync with the old mode to allow it to clean up */
		snd_soc_dapm_sync_unlocked(dapm);
		wm8994->vmid_mode = mode;

		snd_soc_dapm_mutex_unlock(dapm);
		अवरोध;

	हाल WM8994_VMID_FORCE:
		snd_soc_dapm_mutex_lock(dapm);

		अगर (wm8994->hubs.lineout1_se) अणु
			snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm,
							       "LINEOUT1N Driver");
			snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm,
							       "LINEOUT1P Driver");
		पूर्ण
		अगर (wm8994->hubs.lineout2_se) अणु
			snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm,
							       "LINEOUT2N Driver");
			snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm,
							       "LINEOUT2P Driver");
		पूर्ण

		wm8994->vmid_mode = mode;
		snd_soc_dapm_sync_unlocked(dapm);

		snd_soc_dapm_mutex_unlock(dapm);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8994_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;
	पूर्णांक ms_reg;
	पूर्णांक aअगर1_reg;
	पूर्णांक dac_reg;
	पूर्णांक adc_reg;
	पूर्णांक ms = 0;
	पूर्णांक aअगर1 = 0;
	पूर्णांक lrclk = 0;

	चयन (dai->id) अणु
	हाल 1:
		ms_reg = WM8994_AIF1_MASTER_SLAVE;
		aअगर1_reg = WM8994_AIF1_CONTROL_1;
		dac_reg = WM8994_AIF1DAC_LRCLK;
		adc_reg = WM8994_AIF1ADC_LRCLK;
		अवरोध;
	हाल 2:
		ms_reg = WM8994_AIF2_MASTER_SLAVE;
		aअगर1_reg = WM8994_AIF2_CONTROL_1;
		dac_reg = WM8994_AIF1DAC_LRCLK;
		adc_reg = WM8994_AIF1ADC_LRCLK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		ms = WM8994_AIF1_MSTR;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_B:
		aअगर1 |= WM8994_AIF1_LRCLK_INV;
		lrclk |= WM8958_AIF1_LRCLK_INV;
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
			aअगर1 |= WM8994_AIF1_BCLK_INV;
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
			aअगर1 |= WM8994_AIF1_BCLK_INV | WM8994_AIF1_LRCLK_INV;
			lrclk |= WM8958_AIF1_LRCLK_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			aअगर1 |= WM8994_AIF1_BCLK_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_NB_IF:
			aअगर1 |= WM8994_AIF1_LRCLK_INV;
			lrclk |= WM8958_AIF1_LRCLK_INV;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* The AIF2 क्रमmat configuration needs to be mirrored to AIF3
	 * on WM8958 अगर it's in use so just करो it all the समय. */
	चयन (control->type) अणु
	हाल WM1811:
	हाल WM8958:
		अगर (dai->id == 2)
			snd_soc_component_update_bits(component, WM8958_AIF3_CONTROL_1,
					    WM8994_AIF1_LRCLK_INV |
					    WM8958_AIF3_FMT_MASK, aअगर1);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	snd_soc_component_update_bits(component, aअगर1_reg,
			    WM8994_AIF1_BCLK_INV | WM8994_AIF1_LRCLK_INV |
			    WM8994_AIF1_FMT_MASK,
			    aअगर1);
	snd_soc_component_update_bits(component, ms_reg, WM8994_AIF1_MSTR,
			    ms);
	snd_soc_component_update_bits(component, dac_reg,
			    WM8958_AIF1_LRCLK_INV, lrclk);
	snd_soc_component_update_bits(component, adc_reg,
			    WM8958_AIF1_LRCLK_INV, lrclk);

	वापस 0;
पूर्ण

अटल काष्ठा अणु
	पूर्णांक val, rate;
पूर्ण srs[] = अणु
	अणु 0,   8000 पूर्ण,
	अणु 1,  11025 पूर्ण,
	अणु 2,  12000 पूर्ण,
	अणु 3,  16000 पूर्ण,
	अणु 4,  22050 पूर्ण,
	अणु 5,  24000 पूर्ण,
	अणु 6,  32000 पूर्ण,
	अणु 7,  44100 पूर्ण,
	अणु 8,  48000 पूर्ण,
	अणु 9,  88200 पूर्ण,
	अणु 10, 96000 पूर्ण,
पूर्ण;

अटल पूर्णांक fs_ratios[] = अणु
	64, 128, 192, 256, 384, 512, 768, 1024, 1408, 1536
पूर्ण;

अटल पूर्णांक bclk_भागs[] = अणु
	10, 15, 20, 30, 40, 50, 60, 80, 110, 120, 160, 220, 240, 320, 440, 480,
	640, 880, 960, 1280, 1760, 1920
पूर्ण;

अटल पूर्णांक wm8994_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;
	काष्ठा wm8994_pdata *pdata = &control->pdata;
	पूर्णांक aअगर1_reg;
	पूर्णांक aअगर2_reg;
	पूर्णांक bclk_reg;
	पूर्णांक lrclk_reg;
	पूर्णांक rate_reg;
	पूर्णांक aअगर1 = 0;
	पूर्णांक aअगर2 = 0;
	पूर्णांक bclk = 0;
	पूर्णांक lrclk = 0;
	पूर्णांक rate_val = 0;
	पूर्णांक id = dai->id - 1;

	पूर्णांक i, cur_val, best_val, bclk_rate, best;

	चयन (dai->id) अणु
	हाल 1:
		aअगर1_reg = WM8994_AIF1_CONTROL_1;
		aअगर2_reg = WM8994_AIF1_CONTROL_2;
		bclk_reg = WM8994_AIF1_BCLK;
		rate_reg = WM8994_AIF1_RATE;
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK ||
		    wm8994->lrclk_shared[0]) अणु
			lrclk_reg = WM8994_AIF1DAC_LRCLK;
		पूर्ण अन्यथा अणु
			lrclk_reg = WM8994_AIF1ADC_LRCLK;
			dev_dbg(component->dev, "AIF1 using split LRCLK\n");
		पूर्ण
		अवरोध;
	हाल 2:
		aअगर1_reg = WM8994_AIF2_CONTROL_1;
		aअगर2_reg = WM8994_AIF2_CONTROL_2;
		bclk_reg = WM8994_AIF2_BCLK;
		rate_reg = WM8994_AIF2_RATE;
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK ||
		    wm8994->lrclk_shared[1]) अणु
			lrclk_reg = WM8994_AIF2DAC_LRCLK;
		पूर्ण अन्यथा अणु
			lrclk_reg = WM8994_AIF2ADC_LRCLK;
			dev_dbg(component->dev, "AIF2 using split LRCLK\n");
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	bclk_rate = params_rate(params);
	चयन (params_width(params)) अणु
	हाल 16:
		bclk_rate *= 16;
		अवरोध;
	हाल 20:
		bclk_rate *= 20;
		aअगर1 |= 0x20;
		अवरोध;
	हाल 24:
		bclk_rate *= 24;
		aअगर1 |= 0x40;
		अवरोध;
	हाल 32:
		bclk_rate *= 32;
		aअगर1 |= 0x60;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	wm8994->channels[id] = params_channels(params);
	अगर (pdata->max_channels_घड़ीed[id] &&
	    wm8994->channels[id] > pdata->max_channels_घड़ीed[id]) अणु
		dev_dbg(dai->dev, "Constraining channels to %d from %d\n",
			pdata->max_channels_घड़ीed[id], wm8994->channels[id]);
		wm8994->channels[id] = pdata->max_channels_घड़ीed[id];
	पूर्ण

	चयन (wm8994->channels[id]) अणु
	हाल 1:
	हाल 2:
		bclk_rate *= 2;
		अवरोध;
	शेष:
		bclk_rate *= 4;
		अवरोध;
	पूर्ण

	/* Try to find an appropriate sample rate; look क्रम an exact match. */
	क्रम (i = 0; i < ARRAY_SIZE(srs); i++)
		अगर (srs[i].rate == params_rate(params))
			अवरोध;
	अगर (i == ARRAY_SIZE(srs))
		वापस -EINVAL;
	rate_val |= srs[i].val << WM8994_AIF1_SR_SHIFT;

	dev_dbg(dai->dev, "Sample rate is %dHz\n", srs[i].rate);
	dev_dbg(dai->dev, "AIF%dCLK is %dHz, target BCLK %dHz\n",
		dai->id, wm8994->aअगरclk[id], bclk_rate);

	अगर (wm8994->channels[id] == 1 &&
	    (snd_soc_component_पढ़ो(component, aअगर1_reg) & 0x18) == 0x18)
		aअगर2 |= WM8994_AIF1_MONO;

	अगर (wm8994->aअगरclk[id] == 0) अणु
		dev_err(dai->dev, "AIF%dCLK not configured\n", dai->id);
		वापस -EINVAL;
	पूर्ण

	/* AIFCLK/fs ratio; look क्रम a बंद match in either direction */
	best = 0;
	best_val = असल((fs_ratios[0] * params_rate(params))
		       - wm8994->aअगरclk[id]);
	क्रम (i = 1; i < ARRAY_SIZE(fs_ratios); i++) अणु
		cur_val = असल((fs_ratios[i] * params_rate(params))
			      - wm8994->aअगरclk[id]);
		अगर (cur_val >= best_val)
			जारी;
		best = i;
		best_val = cur_val;
	पूर्ण
	dev_dbg(dai->dev, "Selected AIF%dCLK/fs = %d\n",
		dai->id, fs_ratios[best]);
	rate_val |= best;

	/* We may not get quite the right frequency अगर using
	 * approximate घड़ीs so look क्रम the बंदst match that is
	 * higher than the target (we need to ensure that there enough
	 * BCLKs to घड़ी out the samples).
	 */
	best = 0;
	क्रम (i = 0; i < ARRAY_SIZE(bclk_भागs); i++) अणु
		cur_val = (wm8994->aअगरclk[id] * 10 / bclk_भागs[i]) - bclk_rate;
		अगर (cur_val < 0) /* BCLK table is sorted */
			अवरोध;
		best = i;
	पूर्ण
	bclk_rate = wm8994->aअगरclk[id] * 10 / bclk_भागs[best];
	dev_dbg(dai->dev, "Using BCLK_DIV %d for actual BCLK %dHz\n",
		bclk_भागs[best], bclk_rate);
	bclk |= best << WM8994_AIF1_BCLK_DIV_SHIFT;

	lrclk = bclk_rate / params_rate(params);
	अगर (!lrclk) अणु
		dev_err(dai->dev, "Unable to generate LRCLK from %dHz BCLK\n",
			bclk_rate);
		वापस -EINVAL;
	पूर्ण
	dev_dbg(dai->dev, "Using LRCLK rate %d for actual LRCLK %dHz\n",
		lrclk, bclk_rate / lrclk);

	snd_soc_component_update_bits(component, aअगर1_reg, WM8994_AIF1_WL_MASK, aअगर1);
	snd_soc_component_update_bits(component, aअगर2_reg, WM8994_AIF1_MONO, aअगर2);
	snd_soc_component_update_bits(component, bclk_reg, WM8994_AIF1_BCLK_DIV_MASK, bclk);
	snd_soc_component_update_bits(component, lrclk_reg, WM8994_AIF1DAC_RATE_MASK,
			    lrclk);
	snd_soc_component_update_bits(component, rate_reg, WM8994_AIF1_SR_MASK |
			    WM8994_AIF1CLK_RATE_MASK, rate_val);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		चयन (dai->id) अणु
		हाल 1:
			wm8994->dac_rates[0] = params_rate(params);
			wm8994_set_retune_mobile(component, 0);
			wm8994_set_retune_mobile(component, 1);
			अवरोध;
		हाल 2:
			wm8994->dac_rates[1] = params_rate(params);
			wm8994_set_retune_mobile(component, 2);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8994_aअगर3_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;
	पूर्णांक aअगर1_reg;
	पूर्णांक aअगर1 = 0;

	चयन (dai->id) अणु
	हाल 3:
		चयन (control->type) अणु
		हाल WM1811:
		हाल WM8958:
			aअगर1_reg = WM8958_AIF3_CONTROL_1;
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		aअगर1 |= 0x20;
		अवरोध;
	हाल 24:
		aअगर1 |= 0x40;
		अवरोध;
	हाल 32:
		aअगर1 |= 0x60;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस snd_soc_component_update_bits(component, aअगर1_reg, WM8994_AIF1_WL_MASK, aअगर1);
पूर्ण

अटल पूर्णांक wm8994_aअगर_mute(काष्ठा snd_soc_dai *codec_dai, पूर्णांक mute,
			   पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	पूर्णांक mute_reg;
	पूर्णांक reg;

	चयन (codec_dai->id) अणु
	हाल 1:
		mute_reg = WM8994_AIF1_DAC1_FILTERS_1;
		अवरोध;
	हाल 2:
		mute_reg = WM8994_AIF2_DAC_FILTERS_1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (mute)
		reg = WM8994_AIF1DAC1_MUTE;
	अन्यथा
		reg = 0;

	snd_soc_component_update_bits(component, mute_reg, WM8994_AIF1DAC1_MUTE, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8994_set_tristate(काष्ठा snd_soc_dai *codec_dai, पूर्णांक tristate)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	पूर्णांक reg, val, mask;

	चयन (codec_dai->id) अणु
	हाल 1:
		reg = WM8994_AIF1_MASTER_SLAVE;
		mask = WM8994_AIF1_TRI;
		अवरोध;
	हाल 2:
		reg = WM8994_AIF2_MASTER_SLAVE;
		mask = WM8994_AIF2_TRI;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (tristate)
		val = mask;
	अन्यथा
		val = 0;

	वापस snd_soc_component_update_bits(component, reg, mask, val);
पूर्ण

अटल पूर्णांक wm8994_aअगर2_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	/* Disable the pulls on the AIF अगर we're using it to save घातer. */
	snd_soc_component_update_bits(component, WM8994_GPIO_3,
			    WM8994_GPN_PU | WM8994_GPN_PD, 0);
	snd_soc_component_update_bits(component, WM8994_GPIO_4,
			    WM8994_GPN_PU | WM8994_GPN_PD, 0);
	snd_soc_component_update_bits(component, WM8994_GPIO_5,
			    WM8994_GPN_PU | WM8994_GPN_PD, 0);

	वापस 0;
पूर्ण

#घोषणा WM8994_RATES SNDRV_PCM_RATE_8000_96000

#घोषणा WM8994_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8994_aअगर1_dai_ops = अणु
	.set_sysclk	= wm8994_set_dai_sysclk,
	.set_fmt	= wm8994_set_dai_fmt,
	.hw_params	= wm8994_hw_params,
	.mute_stream	= wm8994_aअगर_mute,
	.set_pll	= wm8994_set_fll,
	.set_tristate	= wm8994_set_tristate,
	.no_capture_mute = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops wm8994_aअगर2_dai_ops = अणु
	.set_sysclk	= wm8994_set_dai_sysclk,
	.set_fmt	= wm8994_set_dai_fmt,
	.hw_params	= wm8994_hw_params,
	.mute_stream	= wm8994_aअगर_mute,
	.set_pll	= wm8994_set_fll,
	.set_tristate	= wm8994_set_tristate,
	.no_capture_mute = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops wm8994_aअगर3_dai_ops = अणु
	.hw_params	= wm8994_aअगर3_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8994_dai[] = अणु
	अणु
		.name = "wm8994-aif1",
		.id = 1,
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = WM8994_RATES,
			.क्रमmats = WM8994_FORMATS,
			.sig_bits = 24,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = WM8994_RATES,
			.क्रमmats = WM8994_FORMATS,
			.sig_bits = 24,
		 पूर्ण,
		.ops = &wm8994_aअगर1_dai_ops,
	पूर्ण,
	अणु
		.name = "wm8994-aif2",
		.id = 2,
		.playback = अणु
			.stream_name = "AIF2 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = WM8994_RATES,
			.क्रमmats = WM8994_FORMATS,
			.sig_bits = 24,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF2 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = WM8994_RATES,
			.क्रमmats = WM8994_FORMATS,
			.sig_bits = 24,
		पूर्ण,
		.probe = wm8994_aअगर2_probe,
		.ops = &wm8994_aअगर2_dai_ops,
	पूर्ण,
	अणु
		.name = "wm8994-aif3",
		.id = 3,
		.playback = अणु
			.stream_name = "AIF3 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = WM8994_RATES,
			.क्रमmats = WM8994_FORMATS,
			.sig_bits = 24,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF3 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = WM8994_RATES,
			.क्रमmats = WM8994_FORMATS,
			.sig_bits = 24,
		 पूर्ण,
		.ops = &wm8994_aअगर3_dai_ops,
	पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक wm8994_component_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(wm8994->fll); i++) अणु
		स_नकल(&wm8994->fll_suspend[i], &wm8994->fll[i],
		       माप(काष्ठा wm8994_fll_config));
		ret = _wm8994_set_fll(component, i + 1, 0, 0, 0);
		अगर (ret < 0)
			dev_warn(component->dev, "Failed to stop FLL%d: %d\n",
				 i + 1, ret);
	पूर्ण

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_OFF);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8994_component_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(wm8994->fll); i++) अणु
		अगर (!wm8994->fll_suspend[i].out)
			जारी;

		ret = _wm8994_set_fll(component, i + 1,
				     wm8994->fll_suspend[i].src,
				     wm8994->fll_suspend[i].in,
				     wm8994->fll_suspend[i].out);
		अगर (ret < 0)
			dev_warn(component->dev, "Failed to restore FLL%d: %d\n",
				 i + 1, ret);
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा wm8994_component_suspend शून्य
#घोषणा wm8994_component_resume शून्य
#पूर्ण_अगर

अटल व्योम wm8994_handle_retune_mobile_pdata(काष्ठा wm8994_priv *wm8994)
अणु
	काष्ठा snd_soc_component *component = wm8994->hubs.component;
	काष्ठा wm8994 *control = wm8994->wm8994;
	काष्ठा wm8994_pdata *pdata = &control->pdata;
	काष्ठा snd_kcontrol_new controls[] = अणु
		SOC_ENUM_EXT("AIF1.1 EQ Mode",
			     wm8994->retune_mobile_क्रमागत,
			     wm8994_get_retune_mobile_क्रमागत,
			     wm8994_put_retune_mobile_क्रमागत),
		SOC_ENUM_EXT("AIF1.2 EQ Mode",
			     wm8994->retune_mobile_क्रमागत,
			     wm8994_get_retune_mobile_क्रमागत,
			     wm8994_put_retune_mobile_क्रमागत),
		SOC_ENUM_EXT("AIF2 EQ Mode",
			     wm8994->retune_mobile_क्रमागत,
			     wm8994_get_retune_mobile_क्रमागत,
			     wm8994_put_retune_mobile_क्रमागत),
	पूर्ण;
	पूर्णांक ret, i, j;
	स्थिर अक्षर **t;

	/* We need an array of texts क्रम the क्रमागत API but the number
	 * of texts is likely to be less than the number of
	 * configurations due to the sample rate dependency of the
	 * configurations. */
	wm8994->num_retune_mobile_texts = 0;
	wm8994->retune_mobile_texts = शून्य;
	क्रम (i = 0; i < pdata->num_retune_mobile_cfgs; i++) अणु
		क्रम (j = 0; j < wm8994->num_retune_mobile_texts; j++) अणु
			अगर (म_भेद(pdata->retune_mobile_cfgs[i].name,
				   wm8994->retune_mobile_texts[j]) == 0)
				अवरोध;
		पूर्ण

		अगर (j != wm8994->num_retune_mobile_texts)
			जारी;

		/* Expand the array... */
		t = kपुनः_स्मृति(wm8994->retune_mobile_texts,
			     माप(अक्षर *) *
			     (wm8994->num_retune_mobile_texts + 1),
			     GFP_KERNEL);
		अगर (t == शून्य)
			जारी;

		/* ...store the new entry... */
		t[wm8994->num_retune_mobile_texts] =
			pdata->retune_mobile_cfgs[i].name;

		/* ...and remember the new version. */
		wm8994->num_retune_mobile_texts++;
		wm8994->retune_mobile_texts = t;
	पूर्ण

	dev_dbg(component->dev, "Allocated %d unique ReTune Mobile names\n",
		wm8994->num_retune_mobile_texts);

	wm8994->retune_mobile_क्रमागत.items = wm8994->num_retune_mobile_texts;
	wm8994->retune_mobile_क्रमागत.texts = wm8994->retune_mobile_texts;

	ret = snd_soc_add_component_controls(wm8994->hubs.component, controls,
				   ARRAY_SIZE(controls));
	अगर (ret != 0)
		dev_err(wm8994->hubs.component->dev,
			"Failed to add ReTune Mobile controls: %d\n", ret);
पूर्ण

अटल व्योम wm8994_handle_pdata(काष्ठा wm8994_priv *wm8994)
अणु
	काष्ठा snd_soc_component *component = wm8994->hubs.component;
	काष्ठा wm8994 *control = wm8994->wm8994;
	काष्ठा wm8994_pdata *pdata = &control->pdata;
	पूर्णांक ret, i;

	अगर (!pdata)
		वापस;

	wm_hubs_handle_analogue_pdata(component, pdata->lineout1_dअगरf,
				      pdata->lineout2_dअगरf,
				      pdata->lineout1fb,
				      pdata->lineout2fb,
				      pdata->jd_scthr,
				      pdata->jd_thr,
				      pdata->micb1_delay,
				      pdata->micb2_delay,
				      pdata->micbias1_lvl,
				      pdata->micbias2_lvl);

	dev_dbg(component->dev, "%d DRC configurations\n", pdata->num_drc_cfgs);

	अगर (pdata->num_drc_cfgs) अणु
		काष्ठा snd_kcontrol_new controls[] = अणु
			SOC_ENUM_EXT("AIF1DRC1 Mode", wm8994->drc_क्रमागत,
				     wm8994_get_drc_क्रमागत, wm8994_put_drc_क्रमागत),
			SOC_ENUM_EXT("AIF1DRC2 Mode", wm8994->drc_क्रमागत,
				     wm8994_get_drc_क्रमागत, wm8994_put_drc_क्रमागत),
			SOC_ENUM_EXT("AIF2DRC Mode", wm8994->drc_क्रमागत,
				     wm8994_get_drc_क्रमागत, wm8994_put_drc_क्रमागत),
		पूर्ण;

		/* We need an array of texts क्रम the क्रमागत API */
		wm8994->drc_texts = devm_kसुस्मृति(wm8994->hubs.component->dev,
			    pdata->num_drc_cfgs, माप(अक्षर *), GFP_KERNEL);
		अगर (!wm8994->drc_texts)
			वापस;

		क्रम (i = 0; i < pdata->num_drc_cfgs; i++)
			wm8994->drc_texts[i] = pdata->drc_cfgs[i].name;

		wm8994->drc_क्रमागत.items = pdata->num_drc_cfgs;
		wm8994->drc_क्रमागत.texts = wm8994->drc_texts;

		ret = snd_soc_add_component_controls(wm8994->hubs.component, controls,
					   ARRAY_SIZE(controls));
		क्रम (i = 0; i < WM8994_NUM_DRC; i++)
			wm8994_set_drc(component, i);
	पूर्ण अन्यथा अणु
		ret = snd_soc_add_component_controls(wm8994->hubs.component,
						 wm8994_drc_controls,
						 ARRAY_SIZE(wm8994_drc_controls));
	पूर्ण

	अगर (ret != 0)
		dev_err(wm8994->hubs.component->dev,
			"Failed to add DRC mode controls: %d\n", ret);


	dev_dbg(component->dev, "%d ReTune Mobile configurations\n",
		pdata->num_retune_mobile_cfgs);

	अगर (pdata->num_retune_mobile_cfgs)
		wm8994_handle_retune_mobile_pdata(wm8994);
	अन्यथा
		snd_soc_add_component_controls(wm8994->hubs.component, wm8994_eq_controls,
				     ARRAY_SIZE(wm8994_eq_controls));

	क्रम (i = 0; i < ARRAY_SIZE(pdata->micbias); i++) अणु
		अगर (pdata->micbias[i]) अणु
			snd_soc_component_ग_लिखो(component, WM8958_MICBIAS1 + i,
				pdata->micbias[i] & 0xffff);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * wm8994_mic_detect - Enable microphone detection via the WM8994 IRQ
 *
 * @component:   WM8994 component
 * @jack:    jack to report detection events on
 * @micbias: microphone bias to detect on
 *
 * Enable microphone detection via IRQ on the WM8994.  If GPIOs are
 * being used to bring out संकेतs to the processor then only platक्रमm
 * data configuration is needed क्रम WM8994 and processor GPIOs should
 * be configured using snd_soc_jack_add_gpios() instead.
 *
 * Configuration of detection levels is available via the micbias1_lvl
 * and micbias2_lvl platक्रमm data members.
 */
पूर्णांक wm8994_mic_detect(काष्ठा snd_soc_component *component, काष्ठा snd_soc_jack *jack,
		      पूर्णांक micbias)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994_micdet *micdet;
	काष्ठा wm8994 *control = wm8994->wm8994;
	पूर्णांक reg, ret;

	अगर (control->type != WM8994) अणु
		dev_warn(component->dev, "Not a WM8994\n");
		वापस -EINVAL;
	पूर्ण

	pm_runसमय_get_sync(component->dev);

	चयन (micbias) अणु
	हाल 1:
		micdet = &wm8994->micdet[0];
		अगर (jack)
			ret = snd_soc_dapm_क्रमce_enable_pin(dapm, "MICBIAS1");
		अन्यथा
			ret = snd_soc_dapm_disable_pin(dapm, "MICBIAS1");
		अवरोध;
	हाल 2:
		micdet = &wm8994->micdet[1];
		अगर (jack)
			ret = snd_soc_dapm_क्रमce_enable_pin(dapm, "MICBIAS1");
		अन्यथा
			ret = snd_soc_dapm_disable_pin(dapm, "MICBIAS1");
		अवरोध;
	शेष:
		dev_warn(component->dev, "Invalid MICBIAS %d\n", micbias);
		वापस -EINVAL;
	पूर्ण

	अगर (ret != 0)
		dev_warn(component->dev, "Failed to configure MICBIAS%d: %d\n",
			 micbias, ret);

	dev_dbg(component->dev, "Configuring microphone detection on %d %p\n",
		micbias, jack);

	/* Store the configuration */
	micdet->jack = jack;
	micdet->detecting = true;

	/* If either of the jacks is set up then enable detection */
	अगर (wm8994->micdet[0].jack || wm8994->micdet[1].jack)
		reg = WM8994_MICD_ENA;
	अन्यथा
		reg = 0;

	snd_soc_component_update_bits(component, WM8994_MICBIAS, WM8994_MICD_ENA, reg);

	/* enable MICDET and MICSHRT deboune */
	snd_soc_component_update_bits(component, WM8994_IRQ_DEBOUNCE,
			    WM8994_MIC1_DET_DB_MASK | WM8994_MIC1_SHRT_DB_MASK |
			    WM8994_MIC2_DET_DB_MASK | WM8994_MIC2_SHRT_DB_MASK,
			    WM8994_MIC1_DET_DB | WM8994_MIC1_SHRT_DB);

	snd_soc_dapm_sync(dapm);

	pm_runसमय_put(component->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm8994_mic_detect);

अटल व्योम wm8994_mic_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wm8994_priv *priv = container_of(work,
						काष्ठा wm8994_priv,
						mic_work.work);
	काष्ठा regmap *regmap = priv->wm8994->regmap;
	काष्ठा device *dev = priv->wm8994->dev;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;
	पूर्णांक report;

	pm_runसमय_get_sync(dev);

	ret = regmap_पढ़ो(regmap, WM8994_INTERRUPT_RAW_STATUS_2, &reg);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read microphone status: %d\n",
			ret);
		pm_runसमय_put(dev);
		वापस;
	पूर्ण

	dev_dbg(dev, "Microphone status: %x\n", reg);

	report = 0;
	अगर (reg & WM8994_MIC1_DET_STS) अणु
		अगर (priv->micdet[0].detecting)
			report = SND_JACK_HEADSET;
	पूर्ण
	अगर (reg & WM8994_MIC1_SHRT_STS) अणु
		अगर (priv->micdet[0].detecting)
			report = SND_JACK_HEADPHONE;
		अन्यथा
			report |= SND_JACK_BTN_0;
	पूर्ण
	अगर (report)
		priv->micdet[0].detecting = false;
	अन्यथा
		priv->micdet[0].detecting = true;

	snd_soc_jack_report(priv->micdet[0].jack, report,
			    SND_JACK_HEADSET | SND_JACK_BTN_0);

	report = 0;
	अगर (reg & WM8994_MIC2_DET_STS) अणु
		अगर (priv->micdet[1].detecting)
			report = SND_JACK_HEADSET;
	पूर्ण
	अगर (reg & WM8994_MIC2_SHRT_STS) अणु
		अगर (priv->micdet[1].detecting)
			report = SND_JACK_HEADPHONE;
		अन्यथा
			report |= SND_JACK_BTN_0;
	पूर्ण
	अगर (report)
		priv->micdet[1].detecting = false;
	अन्यथा
		priv->micdet[1].detecting = true;

	snd_soc_jack_report(priv->micdet[1].jack, report,
			    SND_JACK_HEADSET | SND_JACK_BTN_0);

	pm_runसमय_put(dev);
पूर्ण

अटल irqवापस_t wm8994_mic_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm8994_priv *priv = data;
	काष्ठा snd_soc_component *component = priv->hubs.component;

#अगर_अघोषित CONFIG_SND_SOC_WM8994_MODULE
	trace_snd_soc_jack_irq(dev_name(component->dev));
#पूर्ण_अगर

	pm_wakeup_event(component->dev, 300);

	queue_delayed_work(प्रणाली_घातer_efficient_wq,
			   &priv->mic_work, msecs_to_jअगरfies(250));

	वापस IRQ_HANDLED;
पूर्ण

/* Should be called with accdet_lock held */
अटल व्योम wm1811_micd_stop(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	अगर (!wm8994->jackdet)
		वापस;

	snd_soc_component_update_bits(component, WM8958_MIC_DETECT_1, WM8958_MICD_ENA, 0);

	wm1811_jackdet_set_mode(component, WM1811_JACKDET_MODE_JACK);

	अगर (wm8994->wm8994->pdata.jd_ext_cap)
		snd_soc_dapm_disable_pin(dapm, "MICBIAS2");
पूर्ण

अटल व्योम wm8958_button_det(काष्ठा snd_soc_component *component, u16 status)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	पूर्णांक report;

	report = 0;
	अगर (status & 0x4)
		report |= SND_JACK_BTN_0;

	अगर (status & 0x8)
		report |= SND_JACK_BTN_1;

	अगर (status & 0x10)
		report |= SND_JACK_BTN_2;

	अगर (status & 0x20)
		report |= SND_JACK_BTN_3;

	अगर (status & 0x40)
		report |= SND_JACK_BTN_4;

	अगर (status & 0x80)
		report |= SND_JACK_BTN_5;

	snd_soc_jack_report(wm8994->micdet[0].jack, report,
			    wm8994->btn_mask);
पूर्ण

अटल व्योम wm8958_खोलो_circuit_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wm8994_priv *wm8994 = container_of(work,
						  काष्ठा wm8994_priv,
						  खोलो_circuit_work.work);
	काष्ठा device *dev = wm8994->wm8994->dev;

	mutex_lock(&wm8994->accdet_lock);

	wm1811_micd_stop(wm8994->hubs.component);

	dev_dbg(dev, "Reporting open circuit\n");

	wm8994->jack_mic = false;
	wm8994->mic_detecting = true;

	wm8958_micd_set_rate(wm8994->hubs.component);

	snd_soc_jack_report(wm8994->micdet[0].jack, 0,
			    wm8994->btn_mask |
			    SND_JACK_HEADSET);

	mutex_unlock(&wm8994->accdet_lock);
पूर्ण

अटल व्योम wm8958_mic_id(व्योम *data, u16 status)
अणु
	काष्ठा snd_soc_component *component = data;
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	/* Either nothing present or just starting detection */
	अगर (!(status & WM8958_MICD_STS)) अणु
		/* If nothing present then clear our statuses */
		dev_dbg(component->dev, "Detected open circuit\n");

		queue_delayed_work(प्रणाली_घातer_efficient_wq,
				   &wm8994->खोलो_circuit_work,
				   msecs_to_jअगरfies(2500));
		वापस;
	पूर्ण

	/* If the measurement is showing a high impedence we've got a
	 * microphone.
	 */
	अगर (status & 0x600) अणु
		dev_dbg(component->dev, "Detected microphone\n");

		wm8994->mic_detecting = false;
		wm8994->jack_mic = true;

		wm8958_micd_set_rate(component);

		snd_soc_jack_report(wm8994->micdet[0].jack, SND_JACK_HEADSET,
				    SND_JACK_HEADSET);
	पूर्ण


	अगर (status & 0xfc) अणु
		dev_dbg(component->dev, "Detected headphone\n");
		wm8994->mic_detecting = false;

		wm8958_micd_set_rate(component);

		/* If we have jackdet that will detect removal */
		wm1811_micd_stop(component);

		snd_soc_jack_report(wm8994->micdet[0].jack, SND_JACK_HEADPHONE,
				    SND_JACK_HEADSET);
	पूर्ण
पूर्ण

/* Deferred mic detection to allow क्रम extra settling समय */
अटल व्योम wm1811_mic_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wm8994_priv *wm8994 = container_of(work, काष्ठा wm8994_priv,
						  mic_work.work);
	काष्ठा wm8994 *control = wm8994->wm8994;
	काष्ठा snd_soc_component *component = wm8994->hubs.component;
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	pm_runसमय_get_sync(component->dev);

	/* If required क्रम an बाह्यal cap क्रमce MICBIAS on */
	अगर (control->pdata.jd_ext_cap) अणु
		snd_soc_dapm_क्रमce_enable_pin(dapm, "MICBIAS2");
		snd_soc_dapm_sync(dapm);
	पूर्ण

	mutex_lock(&wm8994->accdet_lock);

	dev_dbg(component->dev, "Starting mic detection\n");

	/* Use a user-supplied callback अगर we have one */
	अगर (wm8994->micd_cb) अणु
		wm8994->micd_cb(wm8994->micd_cb_data);
	पूर्ण अन्यथा अणु
		/*
		 * Start off measument of microphone impedence to find out
		 * what's actually there.
		 */
		wm8994->mic_detecting = true;
		wm1811_jackdet_set_mode(component, WM1811_JACKDET_MODE_MIC);

		snd_soc_component_update_bits(component, WM8958_MIC_DETECT_1,
				    WM8958_MICD_ENA, WM8958_MICD_ENA);
	पूर्ण

	mutex_unlock(&wm8994->accdet_lock);

	pm_runसमय_put(component->dev);
पूर्ण

अटल irqवापस_t wm1811_jackdet_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm8994_priv *wm8994 = data;
	काष्ठा wm8994 *control = wm8994->wm8994;
	काष्ठा snd_soc_component *component = wm8994->hubs.component;
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	पूर्णांक reg, delay;
	bool present;

	pm_runसमय_get_sync(component->dev);

	cancel_delayed_work_sync(&wm8994->mic_complete_work);

	mutex_lock(&wm8994->accdet_lock);

	reg = snd_soc_component_पढ़ो(component, WM1811_JACKDET_CTRL);
	अगर (reg < 0) अणु
		dev_err(component->dev, "Failed to read jack status: %d\n", reg);
		mutex_unlock(&wm8994->accdet_lock);
		pm_runसमय_put(component->dev);
		वापस IRQ_NONE;
	पूर्ण

	dev_dbg(component->dev, "JACKDET %x\n", reg);

	present = reg & WM1811_JACKDET_LVL;

	अगर (present) अणु
		dev_dbg(component->dev, "Jack detected\n");

		wm8958_micd_set_rate(component);

		snd_soc_component_update_bits(component, WM8958_MICBIAS2,
				    WM8958_MICB2_DISCH, 0);

		/* Disable debounce जबतक inserted */
		snd_soc_component_update_bits(component, WM1811_JACKDET_CTRL,
				    WM1811_JACKDET_DB, 0);

		delay = control->pdata.micdet_delay;
		queue_delayed_work(प्रणाली_घातer_efficient_wq,
				   &wm8994->mic_work,
				   msecs_to_jअगरfies(delay));
	पूर्ण अन्यथा अणु
		dev_dbg(component->dev, "Jack not detected\n");

		cancel_delayed_work_sync(&wm8994->mic_work);

		snd_soc_component_update_bits(component, WM8958_MICBIAS2,
				    WM8958_MICB2_DISCH, WM8958_MICB2_DISCH);

		/* Enable debounce जबतक हटाओd */
		snd_soc_component_update_bits(component, WM1811_JACKDET_CTRL,
				    WM1811_JACKDET_DB, WM1811_JACKDET_DB);

		wm8994->mic_detecting = false;
		wm8994->jack_mic = false;
		snd_soc_component_update_bits(component, WM8958_MIC_DETECT_1,
				    WM8958_MICD_ENA, 0);
		wm1811_jackdet_set_mode(component, WM1811_JACKDET_MODE_JACK);
	पूर्ण

	mutex_unlock(&wm8994->accdet_lock);

	/* Turn off MICBIAS अगर it was on क्रम an बाह्यal cap */
	अगर (control->pdata.jd_ext_cap && !present)
		snd_soc_dapm_disable_pin(dapm, "MICBIAS2");

	अगर (present)
		snd_soc_jack_report(wm8994->micdet[0].jack,
				    SND_JACK_MECHANICAL, SND_JACK_MECHANICAL);
	अन्यथा
		snd_soc_jack_report(wm8994->micdet[0].jack, 0,
				    SND_JACK_MECHANICAL | SND_JACK_HEADSET |
				    wm8994->btn_mask);

	/* Since we only report deltas क्रमce an update, ensures we
	 * aव्योम bootstrapping issues with the core. */
	snd_soc_jack_report(wm8994->micdet[0].jack, 0, 0);

	pm_runसमय_put(component->dev);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम wm1811_jackdet_bootstrap(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wm8994_priv *wm8994 = container_of(work,
						काष्ठा wm8994_priv,
						jackdet_bootstrap.work);
	wm1811_jackdet_irq(0, wm8994);
पूर्ण

/**
 * wm8958_mic_detect - Enable microphone detection via the WM8958 IRQ
 *
 * @component:   WM8958 component
 * @jack:    jack to report detection events on
 * @det_cb: detection callback
 * @det_cb_data: data क्रम detection callback
 * @id_cb: mic id callback
 * @id_cb_data: data क्रम mic id callback
 *
 * Enable microphone detection functionality क्रम the WM8958.  By
 * शेष simple detection which supports the detection of up to 6
 * buttons plus video and microphone functionality is supported.
 *
 * The WM8958 has an advanced jack detection facility which is able to
 * support complex accessory detection, especially when used in
 * conjunction with बाह्यal circuitry.  In order to provide maximum
 * flexiblity a callback is provided which allows a completely custom
 * detection algorithm.
 */
पूर्णांक wm8958_mic_detect(काष्ठा snd_soc_component *component, काष्ठा snd_soc_jack *jack,
		      wm1811_micdet_cb det_cb, व्योम *det_cb_data,
		      wm1811_mic_id_cb id_cb, व्योम *id_cb_data)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;
	u16 micd_lvl_sel;

	चयन (control->type) अणु
	हाल WM1811:
	हाल WM8958:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	pm_runसमय_get_sync(component->dev);

	अगर (jack) अणु
		snd_soc_dapm_क्रमce_enable_pin(dapm, "CLK_SYS");
		snd_soc_dapm_sync(dapm);

		wm8994->micdet[0].jack = jack;

		अगर (det_cb) अणु
			wm8994->micd_cb = det_cb;
			wm8994->micd_cb_data = det_cb_data;
		पूर्ण अन्यथा अणु
			wm8994->mic_detecting = true;
			wm8994->jack_mic = false;
		पूर्ण

		अगर (id_cb) अणु
			wm8994->mic_id_cb = id_cb;
			wm8994->mic_id_cb_data = id_cb_data;
		पूर्ण अन्यथा अणु
			wm8994->mic_id_cb = wm8958_mic_id;
			wm8994->mic_id_cb_data = component;
		पूर्ण

		wm8958_micd_set_rate(component);

		/* Detect microphones and लघु circuits by शेष */
		अगर (control->pdata.micd_lvl_sel)
			micd_lvl_sel = control->pdata.micd_lvl_sel;
		अन्यथा
			micd_lvl_sel = 0x41;

		wm8994->btn_mask = SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3 |
			SND_JACK_BTN_4 | SND_JACK_BTN_5;

		snd_soc_component_update_bits(component, WM8958_MIC_DETECT_2,
				    WM8958_MICD_LVL_SEL_MASK, micd_lvl_sel);

		WARN_ON(snd_soc_component_get_bias_level(component) > SND_SOC_BIAS_STANDBY);

		/*
		 * If we can use jack detection start off with that,
		 * otherwise jump straight to microphone detection.
		 */
		अगर (wm8994->jackdet) अणु
			/* Disable debounce क्रम the initial detect */
			snd_soc_component_update_bits(component, WM1811_JACKDET_CTRL,
					    WM1811_JACKDET_DB, 0);

			snd_soc_component_update_bits(component, WM8958_MICBIAS2,
					    WM8958_MICB2_DISCH,
					    WM8958_MICB2_DISCH);
			snd_soc_component_update_bits(component, WM8994_LDO_1,
					    WM8994_LDO1_DISCH, 0);
			wm1811_jackdet_set_mode(component,
						WM1811_JACKDET_MODE_JACK);
		पूर्ण अन्यथा अणु
			snd_soc_component_update_bits(component, WM8958_MIC_DETECT_1,
					    WM8958_MICD_ENA, WM8958_MICD_ENA);
		पूर्ण

	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component, WM8958_MIC_DETECT_1,
				    WM8958_MICD_ENA, 0);
		wm1811_jackdet_set_mode(component, WM1811_JACKDET_MODE_NONE);
		snd_soc_dapm_disable_pin(dapm, "CLK_SYS");
		snd_soc_dapm_sync(dapm);
	पूर्ण

	pm_runसमय_put(component->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm8958_mic_detect);

अटल व्योम wm8958_mic_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wm8994_priv *wm8994 = container_of(work,
						  काष्ठा wm8994_priv,
						  mic_complete_work.work);
	काष्ठा snd_soc_component *component = wm8994->hubs.component;

	pm_runसमय_get_sync(component->dev);

	mutex_lock(&wm8994->accdet_lock);

	wm8994->mic_id_cb(wm8994->mic_id_cb_data, wm8994->mic_status);

	mutex_unlock(&wm8994->accdet_lock);

	pm_runसमय_put(component->dev);
पूर्ण

अटल irqवापस_t wm8958_mic_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm8994_priv *wm8994 = data;
	काष्ठा snd_soc_component *component = wm8994->hubs.component;
	पूर्णांक reg, count, ret, id_delay;

	/*
	 * Jack detection may have detected a removal simulataneously
	 * with an update of the MICDET status; अगर so it will have
	 * stopped detection and we can ignore this पूर्णांकerrupt.
	 */
	अगर (!(snd_soc_component_पढ़ो(component, WM8958_MIC_DETECT_1) & WM8958_MICD_ENA))
		वापस IRQ_HANDLED;

	cancel_delayed_work_sync(&wm8994->mic_complete_work);
	cancel_delayed_work_sync(&wm8994->खोलो_circuit_work);

	pm_runसमय_get_sync(component->dev);

	/* We may occasionally पढ़ो a detection without an impedence
	 * range being provided - अगर that happens loop again.
	 */
	count = 10;
	करो अणु
		reg = snd_soc_component_पढ़ो(component, WM8958_MIC_DETECT_3);
		अगर (reg < 0) अणु
			dev_err(component->dev,
				"Failed to read mic detect status: %d\n",
				reg);
			pm_runसमय_put(component->dev);
			वापस IRQ_NONE;
		पूर्ण

		अगर (!(reg & WM8958_MICD_VALID)) अणु
			dev_dbg(component->dev, "Mic detect data not valid\n");
			जाओ out;
		पूर्ण

		अगर (!(reg & WM8958_MICD_STS) || (reg & WM8958_MICD_LVL_MASK))
			अवरोध;

		msleep(1);
	पूर्ण जबतक (count--);

	अगर (count == 0)
		dev_warn(component->dev, "No impedance range reported for jack\n");

#अगर_अघोषित CONFIG_SND_SOC_WM8994_MODULE
	trace_snd_soc_jack_irq(dev_name(component->dev));
#पूर्ण_अगर

	/* Aव्योम a transient report when the accessory is being हटाओd */
	अगर (wm8994->jackdet) अणु
		ret = snd_soc_component_पढ़ो(component, WM1811_JACKDET_CTRL);
		अगर (ret < 0) अणु
			dev_err(component->dev, "Failed to read jack status: %d\n",
				ret);
		पूर्ण अन्यथा अगर (!(ret & WM1811_JACKDET_LVL)) अणु
			dev_dbg(component->dev, "Ignoring removed jack\n");
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (!(reg & WM8958_MICD_STS)) अणु
		snd_soc_jack_report(wm8994->micdet[0].jack, 0,
				    SND_JACK_MECHANICAL | SND_JACK_HEADSET |
				    wm8994->btn_mask);
		wm8994->mic_detecting = true;
		जाओ out;
	पूर्ण

	wm8994->mic_status = reg;
	id_delay = wm8994->wm8994->pdata.mic_id_delay;

	अगर (wm8994->mic_detecting)
		queue_delayed_work(प्रणाली_घातer_efficient_wq,
				   &wm8994->mic_complete_work,
				   msecs_to_jअगरfies(id_delay));
	अन्यथा
		wm8958_button_det(component, reg);

out:
	pm_runसमय_put(component->dev);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t wm8994_fअगरo_error(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा snd_soc_component *component = data;

	dev_err(component->dev, "FIFO error\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t wm8994_temp_warn(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा snd_soc_component *component = data;

	dev_err(component->dev, "Thermal warning\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t wm8994_temp_shut(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा snd_soc_component *component = data;

	dev_crit(component->dev, "Thermal shutdown\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक wm8994_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा wm8994 *control = dev_get_drvdata(component->dev->parent);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret, i;

	snd_soc_component_init_regmap(component, control->regmap);

	wm8994->hubs.component = component;

	mutex_init(&wm8994->accdet_lock);
	INIT_DELAYED_WORK(&wm8994->jackdet_bootstrap,
			  wm1811_jackdet_bootstrap);
	INIT_DELAYED_WORK(&wm8994->खोलो_circuit_work,
			  wm8958_खोलो_circuit_work);

	चयन (control->type) अणु
	हाल WM8994:
		INIT_DELAYED_WORK(&wm8994->mic_work, wm8994_mic_work);
		अवरोध;
	हाल WM1811:
		INIT_DELAYED_WORK(&wm8994->mic_work, wm1811_mic_work);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	INIT_DELAYED_WORK(&wm8994->mic_complete_work, wm8958_mic_work);

	क्रम (i = 0; i < ARRAY_SIZE(wm8994->fll_locked); i++)
		init_completion(&wm8994->fll_locked[i]);

	wm8994->micdet_irq = control->pdata.micdet_irq;

	/* By शेष use idle_bias_off, will override क्रम WM8994 */
	dapm->idle_bias_off = 1;

	/* Set revision-specअगरic configuration */
	चयन (control->type) अणु
	हाल WM8994:
		/* Single ended line outमाला_दो should have VMID on. */
		अगर (!control->pdata.lineout1_dअगरf ||
		    !control->pdata.lineout2_dअगरf)
			dapm->idle_bias_off = 0;

		चयन (control->revision) अणु
		हाल 2:
		हाल 3:
			wm8994->hubs.dcs_codes_l = -5;
			wm8994->hubs.dcs_codes_r = -5;
			wm8994->hubs.hp_startup_mode = 1;
			wm8994->hubs.dcs_पढ़ोback_mode = 1;
			wm8994->hubs.series_startup = 1;
			अवरोध;
		शेष:
			wm8994->hubs.dcs_पढ़ोback_mode = 2;
			अवरोध;
		पूर्ण
		wm8994->hubs.micd_scthr = true;
		अवरोध;

	हाल WM8958:
		wm8994->hubs.dcs_पढ़ोback_mode = 1;
		wm8994->hubs.hp_startup_mode = 1;
		wm8994->hubs.micd_scthr = true;

		चयन (control->revision) अणु
		हाल 0:
			अवरोध;
		शेष:
			wm8994->fll_byp = true;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल WM1811:
		wm8994->hubs.dcs_पढ़ोback_mode = 2;
		wm8994->hubs.no_series_update = 1;
		wm8994->hubs.hp_startup_mode = 1;
		wm8994->hubs.no_cache_dac_hp_direct = true;
		wm8994->fll_byp = true;

		wm8994->hubs.dcs_codes_l = -9;
		wm8994->hubs.dcs_codes_r = -7;

		snd_soc_component_update_bits(component, WM8994_ANALOGUE_HP_1,
				    WM1811_HPOUT1_ATTN, WM1811_HPOUT1_ATTN);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	wm8994_request_irq(wm8994->wm8994, WM8994_IRQ_FIFOS_ERR,
			   wm8994_fअगरo_error, "FIFO error", component);
	wm8994_request_irq(wm8994->wm8994, WM8994_IRQ_TEMP_WARN,
			   wm8994_temp_warn, "Thermal warning", component);
	wm8994_request_irq(wm8994->wm8994, WM8994_IRQ_TEMP_SHUT,
			   wm8994_temp_shut, "Thermal shutdown", component);

	चयन (control->type) अणु
	हाल WM8994:
		अगर (wm8994->micdet_irq)
			ret = request_thपढ़ोed_irq(wm8994->micdet_irq, शून्य,
						   wm8994_mic_irq,
						   IRQF_TRIGGER_RISING |
						   IRQF_ONESHOT,
						   "Mic1 detect",
						   wm8994);
		 अन्यथा
			ret = wm8994_request_irq(wm8994->wm8994,
					WM8994_IRQ_MIC1_DET,
					wm8994_mic_irq, "Mic 1 detect",
					wm8994);

		अगर (ret != 0)
			dev_warn(component->dev,
				 "Failed to request Mic1 detect IRQ: %d\n",
				 ret);


		ret = wm8994_request_irq(wm8994->wm8994,
					 WM8994_IRQ_MIC1_SHRT,
					 wm8994_mic_irq, "Mic 1 short",
					 wm8994);
		अगर (ret != 0)
			dev_warn(component->dev,
				 "Failed to request Mic1 short IRQ: %d\n",
				 ret);

		ret = wm8994_request_irq(wm8994->wm8994,
					 WM8994_IRQ_MIC2_DET,
					 wm8994_mic_irq, "Mic 2 detect",
					 wm8994);
		अगर (ret != 0)
			dev_warn(component->dev,
				 "Failed to request Mic2 detect IRQ: %d\n",
				 ret);

		ret = wm8994_request_irq(wm8994->wm8994,
					 WM8994_IRQ_MIC2_SHRT,
					 wm8994_mic_irq, "Mic 2 short",
					 wm8994);
		अगर (ret != 0)
			dev_warn(component->dev,
				 "Failed to request Mic2 short IRQ: %d\n",
				 ret);
		अवरोध;

	हाल WM8958:
	हाल WM1811:
		अगर (wm8994->micdet_irq) अणु
			ret = request_thपढ़ोed_irq(wm8994->micdet_irq, शून्य,
						   wm8958_mic_irq,
						   IRQF_TRIGGER_RISING |
						   IRQF_ONESHOT,
						   "Mic detect",
						   wm8994);
			अगर (ret != 0)
				dev_warn(component->dev,
					 "Failed to request Mic detect IRQ: %d\n",
					 ret);
		पूर्ण अन्यथा अणु
			wm8994_request_irq(wm8994->wm8994, WM8994_IRQ_MIC1_DET,
					   wm8958_mic_irq, "Mic detect",
					   wm8994);
		पूर्ण
	पूर्ण

	चयन (control->type) अणु
	हाल WM1811:
		अगर (control->cust_id > 1 || control->revision > 1) अणु
			ret = wm8994_request_irq(wm8994->wm8994,
						 WM8994_IRQ_GPIO(6),
						 wm1811_jackdet_irq, "JACKDET",
						 wm8994);
			अगर (ret == 0)
				wm8994->jackdet = true;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	wm8994->fll_locked_irq = true;
	क्रम (i = 0; i < ARRAY_SIZE(wm8994->fll_locked); i++) अणु
		ret = wm8994_request_irq(wm8994->wm8994,
					 WM8994_IRQ_FLL1_LOCK + i,
					 wm8994_fll_locked_irq, "FLL lock",
					 &wm8994->fll_locked[i]);
		अगर (ret != 0)
			wm8994->fll_locked_irq = false;
	पूर्ण

	/* Make sure we can पढ़ो from the GPIOs अगर they're inमाला_दो */
	pm_runसमय_get_sync(component->dev);

	/* Remember अगर AIFnLRCLK is configured as a GPIO.  This should be
	 * configured on init - अगर a प्रणाली wants to करो this dynamically
	 * at runसमय we can deal with that then.
	 */
	ret = regmap_पढ़ो(control->regmap, WM8994_GPIO_1, &reg);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to read GPIO1 state: %d\n", ret);
		जाओ err_irq;
	पूर्ण
	अगर ((reg & WM8994_GPN_FN_MASK) != WM8994_GP_FN_PIN_SPECIFIC) अणु
		wm8994->lrclk_shared[0] = 1;
		wm8994_dai[0].symmetric_rate = 1;
	पूर्ण अन्यथा अणु
		wm8994->lrclk_shared[0] = 0;
	पूर्ण

	ret = regmap_पढ़ो(control->regmap, WM8994_GPIO_6, &reg);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to read GPIO6 state: %d\n", ret);
		जाओ err_irq;
	पूर्ण
	अगर ((reg & WM8994_GPN_FN_MASK) != WM8994_GP_FN_PIN_SPECIFIC) अणु
		wm8994->lrclk_shared[1] = 1;
		wm8994_dai[1].symmetric_rate = 1;
	पूर्ण अन्यथा अणु
		wm8994->lrclk_shared[1] = 0;
	पूर्ण

	pm_runसमय_put(component->dev);

	/* Latch volume update bits */
	क्रम (i = 0; i < ARRAY_SIZE(wm8994_vu_bits); i++)
		snd_soc_component_update_bits(component, wm8994_vu_bits[i].reg,
				    wm8994_vu_bits[i].mask,
				    wm8994_vu_bits[i].mask);

	अगर (control->type != WM1811) अणु
		क्रम (i = 0; i < ARRAY_SIZE(wm8994_adc2_dac2_vu_bits); i++)
			snd_soc_component_update_bits(component,
					wm8994_adc2_dac2_vu_bits[i].reg,
					wm8994_adc2_dac2_vu_bits[i].mask,
					wm8994_adc2_dac2_vu_bits[i].mask);
	पूर्ण

	/* Set the low bit of the 3D stereo depth so TLV matches */
	snd_soc_component_update_bits(component, WM8994_AIF1_DAC1_FILTERS_2,
			    1 << WM8994_AIF1DAC1_3D_GAIN_SHIFT,
			    1 << WM8994_AIF1DAC1_3D_GAIN_SHIFT);
	snd_soc_component_update_bits(component, WM8994_AIF1_DAC2_FILTERS_2,
			    1 << WM8994_AIF1DAC2_3D_GAIN_SHIFT,
			    1 << WM8994_AIF1DAC2_3D_GAIN_SHIFT);
	snd_soc_component_update_bits(component, WM8994_AIF2_DAC_FILTERS_2,
			    1 << WM8994_AIF2DAC_3D_GAIN_SHIFT,
			    1 << WM8994_AIF2DAC_3D_GAIN_SHIFT);

	/* Unconditionally enable AIF1 ADC TDM mode on chips which can
	 * use this; it only affects behaviour on idle TDM घड़ी
	 * cycles. */
	चयन (control->type) अणु
	हाल WM8994:
	हाल WM8958:
		snd_soc_component_update_bits(component, WM8994_AIF1_CONTROL_1,
				    WM8994_AIF1ADC_TDM, WM8994_AIF1ADC_TDM);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Put MICBIAS पूर्णांकo bypass mode by शेष on newer devices */
	चयन (control->type) अणु
	हाल WM8958:
	हाल WM1811:
		snd_soc_component_update_bits(component, WM8958_MICBIAS1,
				    WM8958_MICB1_MODE, WM8958_MICB1_MODE);
		snd_soc_component_update_bits(component, WM8958_MICBIAS2,
				    WM8958_MICB2_MODE, WM8958_MICB2_MODE);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	wm8994->hubs.check_class_w_digital = wm8994_check_class_w_digital;
	wm_hubs_update_class_w(component);

	wm8994_handle_pdata(wm8994);

	wm_hubs_add_analogue_controls(component);
	snd_soc_add_component_controls(component, wm8994_common_snd_controls,
				       ARRAY_SIZE(wm8994_common_snd_controls));
	snd_soc_dapm_new_controls(dapm, wm8994_dapm_widमाला_लो,
				  ARRAY_SIZE(wm8994_dapm_widमाला_लो));

	चयन (control->type) अणु
	हाल WM8994:
		snd_soc_add_component_controls(component, wm8994_snd_controls,
					       ARRAY_SIZE(wm8994_snd_controls));
		snd_soc_dapm_new_controls(dapm, wm8994_specअगरic_dapm_widमाला_लो,
					  ARRAY_SIZE(wm8994_specअगरic_dapm_widमाला_लो));
		अगर (control->revision < 4) अणु
			snd_soc_dapm_new_controls(dapm, wm8994_lateclk_revd_widमाला_लो,
						  ARRAY_SIZE(wm8994_lateclk_revd_widमाला_लो));
			snd_soc_dapm_new_controls(dapm, wm8994_adc_revd_widमाला_लो,
						  ARRAY_SIZE(wm8994_adc_revd_widमाला_लो));
			snd_soc_dapm_new_controls(dapm, wm8994_dac_revd_widमाला_लो,
						  ARRAY_SIZE(wm8994_dac_revd_widमाला_लो));
		पूर्ण अन्यथा अणु
			snd_soc_dapm_new_controls(dapm, wm8994_lateclk_widमाला_लो,
						  ARRAY_SIZE(wm8994_lateclk_widमाला_लो));
			snd_soc_dapm_new_controls(dapm, wm8994_adc_widमाला_लो,
						  ARRAY_SIZE(wm8994_adc_widमाला_लो));
			snd_soc_dapm_new_controls(dapm, wm8994_dac_widमाला_लो,
						  ARRAY_SIZE(wm8994_dac_widमाला_लो));
		पूर्ण
		अवरोध;
	हाल WM8958:
		snd_soc_add_component_controls(component, wm8994_snd_controls,
					       ARRAY_SIZE(wm8994_snd_controls));
		snd_soc_add_component_controls(component, wm8958_snd_controls,
					       ARRAY_SIZE(wm8958_snd_controls));
		snd_soc_dapm_new_controls(dapm, wm8958_dapm_widमाला_लो,
					  ARRAY_SIZE(wm8958_dapm_widमाला_लो));
		अगर (control->revision < 1) अणु
			snd_soc_dapm_new_controls(dapm, wm8994_lateclk_revd_widमाला_लो,
						  ARRAY_SIZE(wm8994_lateclk_revd_widमाला_लो));
			snd_soc_dapm_new_controls(dapm, wm8994_adc_revd_widमाला_लो,
						  ARRAY_SIZE(wm8994_adc_revd_widमाला_लो));
			snd_soc_dapm_new_controls(dapm, wm8994_dac_revd_widमाला_लो,
						  ARRAY_SIZE(wm8994_dac_revd_widमाला_लो));
		पूर्ण अन्यथा अणु
			snd_soc_dapm_new_controls(dapm, wm8994_lateclk_widमाला_लो,
						  ARRAY_SIZE(wm8994_lateclk_widमाला_लो));
			snd_soc_dapm_new_controls(dapm, wm8994_adc_widमाला_लो,
						  ARRAY_SIZE(wm8994_adc_widमाला_लो));
			snd_soc_dapm_new_controls(dapm, wm8994_dac_widमाला_लो,
						  ARRAY_SIZE(wm8994_dac_widमाला_लो));
		पूर्ण
		अवरोध;

	हाल WM1811:
		snd_soc_add_component_controls(component, wm8958_snd_controls,
				     ARRAY_SIZE(wm8958_snd_controls));
		snd_soc_dapm_new_controls(dapm, wm8958_dapm_widमाला_लो,
					  ARRAY_SIZE(wm8958_dapm_widमाला_लो));
		snd_soc_dapm_new_controls(dapm, wm8994_lateclk_widमाला_लो,
					  ARRAY_SIZE(wm8994_lateclk_widमाला_लो));
		snd_soc_dapm_new_controls(dapm, wm8994_adc_widमाला_लो,
					  ARRAY_SIZE(wm8994_adc_widमाला_लो));
		snd_soc_dapm_new_controls(dapm, wm8994_dac_widमाला_लो,
					  ARRAY_SIZE(wm8994_dac_widमाला_लो));
		अवरोध;
	पूर्ण

	wm_hubs_add_analogue_routes(component, 0, 0);
	ret = wm8994_request_irq(wm8994->wm8994, WM8994_IRQ_DCS_DONE,
				 wm_hubs_dcs_करोne, "DC servo done",
				 &wm8994->hubs);
	अगर (ret == 0)
		wm8994->hubs.dcs_करोne_irq = true;
	snd_soc_dapm_add_routes(dapm, पूर्णांकercon, ARRAY_SIZE(पूर्णांकercon));

	चयन (control->type) अणु
	हाल WM8994:
		snd_soc_dapm_add_routes(dapm, wm8994_पूर्णांकercon,
					ARRAY_SIZE(wm8994_पूर्णांकercon));

		अगर (control->revision < 4) अणु
			snd_soc_dapm_add_routes(dapm, wm8994_revd_पूर्णांकercon,
						ARRAY_SIZE(wm8994_revd_पूर्णांकercon));
			snd_soc_dapm_add_routes(dapm, wm8994_lateclk_revd_पूर्णांकercon,
						ARRAY_SIZE(wm8994_lateclk_revd_पूर्णांकercon));
		पूर्ण अन्यथा अणु
			snd_soc_dapm_add_routes(dapm, wm8994_lateclk_पूर्णांकercon,
						ARRAY_SIZE(wm8994_lateclk_पूर्णांकercon));
		पूर्ण
		अवरोध;
	हाल WM8958:
		अगर (control->revision < 1) अणु
			snd_soc_dapm_add_routes(dapm, wm8994_पूर्णांकercon,
						ARRAY_SIZE(wm8994_पूर्णांकercon));
			snd_soc_dapm_add_routes(dapm, wm8994_revd_पूर्णांकercon,
						ARRAY_SIZE(wm8994_revd_पूर्णांकercon));
			snd_soc_dapm_add_routes(dapm, wm8994_lateclk_revd_पूर्णांकercon,
						ARRAY_SIZE(wm8994_lateclk_revd_पूर्णांकercon));
		पूर्ण अन्यथा अणु
			snd_soc_dapm_add_routes(dapm, wm8994_lateclk_पूर्णांकercon,
						ARRAY_SIZE(wm8994_lateclk_पूर्णांकercon));
			snd_soc_dapm_add_routes(dapm, wm8958_पूर्णांकercon,
						ARRAY_SIZE(wm8958_पूर्णांकercon));
		पूर्ण

		wm8958_dsp2_init(component);
		अवरोध;
	हाल WM1811:
		snd_soc_dapm_add_routes(dapm, wm8994_lateclk_पूर्णांकercon,
					ARRAY_SIZE(wm8994_lateclk_पूर्णांकercon));
		snd_soc_dapm_add_routes(dapm, wm8958_पूर्णांकercon,
					ARRAY_SIZE(wm8958_पूर्णांकercon));
		अवरोध;
	पूर्ण

	वापस 0;

err_irq:
	अगर (wm8994->jackdet)
		wm8994_मुक्त_irq(wm8994->wm8994, WM8994_IRQ_GPIO(6), wm8994);
	wm8994_मुक्त_irq(wm8994->wm8994, WM8994_IRQ_MIC2_SHRT, wm8994);
	wm8994_मुक्त_irq(wm8994->wm8994, WM8994_IRQ_MIC2_DET, wm8994);
	wm8994_मुक्त_irq(wm8994->wm8994, WM8994_IRQ_MIC1_SHRT, wm8994);
	अगर (wm8994->micdet_irq)
		मुक्त_irq(wm8994->micdet_irq, wm8994);
	क्रम (i = 0; i < ARRAY_SIZE(wm8994->fll_locked); i++)
		wm8994_मुक्त_irq(wm8994->wm8994, WM8994_IRQ_FLL1_LOCK + i,
				&wm8994->fll_locked[i]);
	wm8994_मुक्त_irq(wm8994->wm8994, WM8994_IRQ_DCS_DONE,
			&wm8994->hubs);
	wm8994_मुक्त_irq(wm8994->wm8994, WM8994_IRQ_FIFOS_ERR, component);
	wm8994_मुक्त_irq(wm8994->wm8994, WM8994_IRQ_TEMP_SHUT, component);
	wm8994_मुक्त_irq(wm8994->wm8994, WM8994_IRQ_TEMP_WARN, component);

	वापस ret;
पूर्ण

अटल व्योम wm8994_component_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(wm8994->fll_locked); i++)
		wm8994_मुक्त_irq(wm8994->wm8994, WM8994_IRQ_FLL1_LOCK + i,
				&wm8994->fll_locked[i]);

	wm8994_मुक्त_irq(wm8994->wm8994, WM8994_IRQ_DCS_DONE,
			&wm8994->hubs);
	wm8994_मुक्त_irq(wm8994->wm8994, WM8994_IRQ_FIFOS_ERR, component);
	wm8994_मुक्त_irq(wm8994->wm8994, WM8994_IRQ_TEMP_SHUT, component);
	wm8994_मुक्त_irq(wm8994->wm8994, WM8994_IRQ_TEMP_WARN, component);

	अगर (wm8994->jackdet)
		wm8994_मुक्त_irq(wm8994->wm8994, WM8994_IRQ_GPIO(6), wm8994);

	चयन (control->type) अणु
	हाल WM8994:
		अगर (wm8994->micdet_irq)
			मुक्त_irq(wm8994->micdet_irq, wm8994);
		wm8994_मुक्त_irq(wm8994->wm8994, WM8994_IRQ_MIC2_DET,
				wm8994);
		wm8994_मुक्त_irq(wm8994->wm8994, WM8994_IRQ_MIC1_SHRT,
				wm8994);
		wm8994_मुक्त_irq(wm8994->wm8994, WM8994_IRQ_MIC1_DET,
				wm8994);
		अवरोध;

	हाल WM1811:
	हाल WM8958:
		अगर (wm8994->micdet_irq)
			मुक्त_irq(wm8994->micdet_irq, wm8994);
		अवरोध;
	पूर्ण
	release_firmware(wm8994->mbc);
	release_firmware(wm8994->mbc_vss);
	release_firmware(wm8994->enh_eq);
	kमुक्त(wm8994->retune_mobile_texts);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8994 = अणु
	.probe			= wm8994_component_probe,
	.हटाओ			= wm8994_component_हटाओ,
	.suspend		= wm8994_component_suspend,
	.resume			= wm8994_component_resume,
	.set_bias_level		= wm8994_set_bias_level,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक wm8994_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm8994_priv *wm8994;
	पूर्णांक ret;

	wm8994 = devm_kzalloc(&pdev->dev, माप(काष्ठा wm8994_priv),
			      GFP_KERNEL);
	अगर (wm8994 == शून्य)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, wm8994);

	mutex_init(&wm8994->fw_lock);

	wm8994->wm8994 = dev_get_drvdata(pdev->dev.parent);

	wm8994->mclk[WM8994_MCLK1].id = "MCLK1";
	wm8994->mclk[WM8994_MCLK2].id = "MCLK2";

	ret = devm_clk_bulk_get_optional(pdev->dev.parent, ARRAY_SIZE(wm8994->mclk),
					 wm8994->mclk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to get clocks: %d\n", ret);
		वापस ret;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_idle(&pdev->dev);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &soc_component_dev_wm8994,
			wm8994_dai, ARRAY_SIZE(wm8994_dai));
	अगर (ret < 0)
		pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक wm8994_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक wm8994_suspend(काष्ठा device *dev)
अणु
	काष्ठा wm8994_priv *wm8994 = dev_get_drvdata(dev);

	/* Drop करोwn to घातer saving mode when प्रणाली is suspended */
	अगर (wm8994->jackdet && !wm8994->active_refcount)
		regmap_update_bits(wm8994->wm8994->regmap, WM8994_ANTIPOP_2,
				   WM1811_JACKDET_MODE_MASK,
				   wm8994->jackdet_mode);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8994_resume(काष्ठा device *dev)
अणु
	काष्ठा wm8994_priv *wm8994 = dev_get_drvdata(dev);

	अगर (wm8994->jackdet && wm8994->jackdet_mode)
		regmap_update_bits(wm8994->wm8994->regmap, WM8994_ANTIPOP_2,
				   WM1811_JACKDET_MODE_MASK,
				   WM1811_JACKDET_MODE_AUDIO);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops wm8994_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(wm8994_suspend, wm8994_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver wm8994_codec_driver = अणु
	.driver = अणु
		.name = "wm8994-codec",
		.pm = &wm8994_pm_ops,
	पूर्ण,
	.probe = wm8994_probe,
	.हटाओ = wm8994_हटाओ,
पूर्ण;

module_platक्रमm_driver(wm8994_codec_driver);

MODULE_DESCRIPTION("ASoC WM8994 driver");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm8994-codec");
