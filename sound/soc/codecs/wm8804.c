<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8804.c  --  WM8804 S/PDIF transceiver driver
 *
 * Copyright 2010-11 Wolfson Microelectronics plc
 *
 * Author: Dimitris Papastamos <dp@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/soc-dapm.h>

#समावेश "wm8804.h"

#घोषणा WM8804_NUM_SUPPLIES 2
अटल स्थिर अक्षर *wm8804_supply_names[WM8804_NUM_SUPPLIES] = अणु
	"PVDD",
	"DVDD"
पूर्ण;

अटल स्थिर काष्ठा reg_शेष wm8804_reg_शेषs[] = अणु
	अणु 3,  0x21 पूर्ण,     /* R3  - PLL1 */
	अणु 4,  0xFD पूर्ण,     /* R4  - PLL2 */
	अणु 5,  0x36 पूर्ण,     /* R5  - PLL3 */
	अणु 6,  0x07 पूर्ण,     /* R6  - PLL4 */
	अणु 7,  0x16 पूर्ण,     /* R7  - PLL5 */
	अणु 8,  0x18 पूर्ण,     /* R8  - PLL6 */
	अणु 9,  0xFF पूर्ण,     /* R9  - SPDMODE */
	अणु 10, 0x00 पूर्ण,     /* R10 - INTMASK */
	अणु 18, 0x00 पूर्ण,     /* R18 - SPDTX1 */
	अणु 19, 0x00 पूर्ण,     /* R19 - SPDTX2 */
	अणु 20, 0x00 पूर्ण,     /* R20 - SPDTX3 */
	अणु 21, 0x71 पूर्ण,     /* R21 - SPDTX4 */
	अणु 22, 0x0B पूर्ण,     /* R22 - SPDTX5 */
	अणु 23, 0x70 पूर्ण,     /* R23 - GPO0 */
	अणु 24, 0x57 पूर्ण,     /* R24 - GPO1 */
	अणु 26, 0x42 पूर्ण,     /* R26 - GPO2 */
	अणु 27, 0x06 पूर्ण,     /* R27 - AIFTX */
	अणु 28, 0x06 पूर्ण,     /* R28 - AIFRX */
	अणु 29, 0x80 पूर्ण,     /* R29 - SPDRX1 */
	अणु 30, 0x07 पूर्ण,     /* R30 - PWRDN */
पूर्ण;

काष्ठा wm8804_priv अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data supplies[WM8804_NUM_SUPPLIES];
	काष्ठा notअगरier_block disable_nb[WM8804_NUM_SUPPLIES];
	पूर्णांक mclk_भाग;

	काष्ठा gpio_desc *reset;

	पूर्णांक aअगर_pwr;
पूर्ण;

अटल पूर्णांक txsrc_put(काष्ठा snd_kcontrol *kcontrol,
		     काष्ठा snd_ctl_elem_value *ucontrol);

अटल पूर्णांक wm8804_aअगर_event(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event);

/*
 * We can't use the same notअगरier block क्रम more than one supply and
 * there's no way I can see to get from a callback to the caller
 * except container_of().
 */
#घोषणा WM8804_REGULATOR_EVENT(n) \
अटल पूर्णांक wm8804_regulator_event_##n(काष्ठा notअगरier_block *nb, \
				      अचिन्हित दीर्घ event, व्योम *data)    \
अणु \
	काष्ठा wm8804_priv *wm8804 = container_of(nb, काष्ठा wm8804_priv, \
						  disable_nb[n]); \
	अगर (event & REGULATOR_EVENT_DISABLE) अणु \
		regcache_mark_dirty(wm8804->regmap);	\
	पूर्ण \
	वापस 0; \
पूर्ण

WM8804_REGULATOR_EVENT(0)
WM8804_REGULATOR_EVENT(1)

अटल स्थिर अक्षर *txsrc_text[] = अणु "S/PDIF RX", "AIF" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(txsrc, WM8804_SPDTX4, 6, txsrc_text);

अटल स्थिर काष्ठा snd_kcontrol_new wm8804_tx_source_mux[] = अणु
	SOC_DAPM_ENUM_EXT("Input Source", txsrc,
			  snd_soc_dapm_get_क्रमागत_द्विगुन, txsrc_put),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8804_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_OUTPUT("SPDIF Out"),
SND_SOC_DAPM_INPUT("SPDIF In"),

SND_SOC_DAPM_PGA("SPDIFTX", WM8804_PWRDN, 2, 1, शून्य, 0),
SND_SOC_DAPM_PGA("SPDIFRX", WM8804_PWRDN, 1, 1, शून्य, 0),

SND_SOC_DAPM_MUX("Tx Source", SND_SOC_NOPM, 6, 0, wm8804_tx_source_mux),

SND_SOC_DAPM_AIF_OUT_E("AIFTX", शून्य, 0, SND_SOC_NOPM, 0, 0, wm8804_aअगर_event,
		       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_AIF_IN_E("AIFRX", शून्य, 0, SND_SOC_NOPM, 0, 0, wm8804_aअगर_event,
		      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8804_dapm_routes[] = अणु
	अणु "AIFRX", शून्य, "Playback" पूर्ण,
	अणु "Tx Source", "AIF", "AIFRX" पूर्ण,

	अणु "SPDIFRX", शून्य, "SPDIF In" पूर्ण,
	अणु "Tx Source", "S/PDIF RX", "SPDIFRX" पूर्ण,

	अणु "SPDIFTX", शून्य, "Tx Source" पूर्ण,
	अणु "SPDIF Out", शून्य, "SPDIFTX" पूर्ण,

	अणु "AIFTX", शून्य, "SPDIFRX" पूर्ण,
	अणु "Capture", शून्य, "AIFTX" पूर्ण,
पूर्ण;

अटल पूर्णांक wm8804_aअगर_event(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm8804_priv *wm8804 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* घातer up the aअगर */
		अगर (!wm8804->aअगर_pwr)
			snd_soc_component_update_bits(component, WM8804_PWRDN, 0x10, 0x0);
		wm8804->aअगर_pwr++;
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* घातer करोwn only both paths are disabled */
		wm8804->aअगर_pwr--;
		अगर (!wm8804->aअगर_pwr)
			snd_soc_component_update_bits(component, WM8804_PWRDN, 0x10, 0x10);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक txsrc_put(काष्ठा snd_kcontrol *kcontrol,
		     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक val = ucontrol->value.क्रमागतerated.item[0] << e->shअगरt_l;
	अचिन्हित पूर्णांक mask = 1 << e->shअगरt_l;
	अचिन्हित पूर्णांक txpwr;

	अगर (val != 0 && val != mask)
		वापस -EINVAL;

	snd_soc_dapm_mutex_lock(dapm);

	अगर (snd_soc_component_test_bits(component, e->reg, mask, val)) अणु
		/* save the current घातer state of the transmitter */
		txpwr = snd_soc_component_पढ़ो(component, WM8804_PWRDN) & 0x4;

		/* घातer करोwn the transmitter */
		snd_soc_component_update_bits(component, WM8804_PWRDN, 0x4, 0x4);

		/* set the tx source */
		snd_soc_component_update_bits(component, e->reg, mask, val);

		/* restore the transmitter's configuration */
		snd_soc_component_update_bits(component, WM8804_PWRDN, 0x4, txpwr);
	पूर्ण

	snd_soc_dapm_mutex_unlock(dapm);

	वापस 0;
पूर्ण

अटल bool wm8804_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8804_RST_DEVID1:
	हाल WM8804_DEVID2:
	हाल WM8804_DEVREV:
	हाल WM8804_INTSTAT:
	हाल WM8804_SPDSTAT:
	हाल WM8804_RXCHAN1:
	हाल WM8804_RXCHAN2:
	हाल WM8804_RXCHAN3:
	हाल WM8804_RXCHAN4:
	हाल WM8804_RXCHAN5:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक wm8804_soft_reset(काष्ठा wm8804_priv *wm8804)
अणु
	वापस regmap_ग_लिखो(wm8804->regmap, WM8804_RST_DEVID1, 0x0);
पूर्ण

अटल पूर्णांक wm8804_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component;
	u16 क्रमmat, master, bcp, lrp;

	component = dai->component;

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		क्रमmat = 0x2;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		क्रमmat = 0x0;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		क्रमmat = 0x1;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
	हाल SND_SOC_DAIFMT_DSP_B:
		क्रमmat = 0x3;
		अवरोध;
	शेष:
		dev_err(dai->dev, "Unknown dai format\n");
		वापस -EINVAL;
	पूर्ण

	/* set data क्रमmat */
	snd_soc_component_update_bits(component, WM8804_AIFTX, 0x3, क्रमmat);
	snd_soc_component_update_bits(component, WM8804_AIFRX, 0x3, क्रमmat);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		master = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		master = 0;
		अवरोध;
	शेष:
		dev_err(dai->dev, "Unknown master/slave configuration\n");
		वापस -EINVAL;
	पूर्ण

	/* set master/slave mode */
	snd_soc_component_update_bits(component, WM8804_AIFRX, 0x40, master << 6);

	bcp = lrp = 0;
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		bcp = lrp = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		bcp = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		lrp = 1;
		अवरोध;
	शेष:
		dev_err(dai->dev, "Unknown polarity configuration\n");
		वापस -EINVAL;
	पूर्ण

	/* set frame inversion */
	snd_soc_component_update_bits(component, WM8804_AIFTX, 0x10 | 0x20,
			    (bcp << 4) | (lrp << 5));
	snd_soc_component_update_bits(component, WM8804_AIFRX, 0x10 | 0x20,
			    (bcp << 4) | (lrp << 5));
	वापस 0;
पूर्ण

अटल पूर्णांक wm8804_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component;
	u16 blen;

	component = dai->component;

	चयन (params_width(params)) अणु
	हाल 16:
		blen = 0x0;
		अवरोध;
	हाल 20:
		blen = 0x1;
		अवरोध;
	हाल 24:
		blen = 0x2;
		अवरोध;
	शेष:
		dev_err(dai->dev, "Unsupported word length: %u\n",
			params_width(params));
		वापस -EINVAL;
	पूर्ण

	/* set word length */
	snd_soc_component_update_bits(component, WM8804_AIFTX, 0xc, blen << 2);
	snd_soc_component_update_bits(component, WM8804_AIFRX, 0xc, blen << 2);

	वापस 0;
पूर्ण

काष्ठा pll_भाग अणु
	u32 prescale:1;
	u32 mclkभाग:1;
	u32 freqmode:2;
	u32 n:4;
	u32 k:22;
पूर्ण;

/* PLL rate to output rate भागisions */
अटल काष्ठा अणु
	अचिन्हित पूर्णांक भाग;
	अचिन्हित पूर्णांक freqmode;
	अचिन्हित पूर्णांक mclkभाग;
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

#घोषणा FIXED_PLL_SIZE ((1ULL << 22) * 10)
अटल पूर्णांक pll_factors(काष्ठा pll_भाग *pll_भाग, अचिन्हित पूर्णांक target,
		       अचिन्हित पूर्णांक source, अचिन्हित पूर्णांक mclk_भाग)
अणु
	u64 Kpart;
	अचिन्हित दीर्घ पूर्णांक K, Nभाग, Nmod, पंचांगp;
	पूर्णांक i;

	/*
	 * Scale the output frequency up; the PLL should run in the
	 * region of 90-100MHz.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(post_table); i++) अणु
		पंचांगp = target * post_table[i].भाग;
		अगर ((पंचांगp >= 90000000 && पंचांगp <= 100000000) &&
		    (mclk_भाग == post_table[i].mclkभाग)) अणु
			pll_भाग->freqmode = post_table[i].freqmode;
			pll_भाग->mclkभाग = post_table[i].mclkभाग;
			target *= post_table[i].भाग;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ARRAY_SIZE(post_table)) अणु
		pr_err("%s: Unable to scale output frequency: %uHz\n",
		       __func__, target);
		वापस -EINVAL;
	पूर्ण

	pll_भाग->prescale = 0;
	Nभाग = target / source;
	अगर (Nभाग < 5) अणु
		source >>= 1;
		pll_भाग->prescale = 1;
		Nभाग = target / source;
	पूर्ण

	अगर (Nभाग < 5 || Nभाग > 13) अणु
		pr_err("%s: WM8804 N value is not within the recommended range: %lu\n",
		       __func__, Nभाग);
		वापस -EINVAL;
	पूर्ण
	pll_भाग->n = Nभाग;

	Nmod = target % source;
	Kpart = FIXED_PLL_SIZE * (u64)Nmod;

	करो_भाग(Kpart, source);

	K = Kpart & 0xffffffff;
	अगर ((K % 10) >= 5)
		K += 5;
	K /= 10;
	pll_भाग->k = K;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8804_set_pll(काष्ठा snd_soc_dai *dai, पूर्णांक pll_id,
			  पूर्णांक source, अचिन्हित पूर्णांक freq_in,
			  अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8804_priv *wm8804 = snd_soc_component_get_drvdata(component);
	bool change;

	अगर (!freq_in || !freq_out) अणु
		/* disable the PLL */
		regmap_update_bits_check(wm8804->regmap, WM8804_PWRDN,
					 0x1, 0x1, &change);
		अगर (change)
			pm_runसमय_put(wm8804->dev);
	पूर्ण अन्यथा अणु
		पूर्णांक ret;
		काष्ठा pll_भाग pll_भाग;

		ret = pll_factors(&pll_भाग, freq_out, freq_in,
				  wm8804->mclk_भाग);
		अगर (ret)
			वापस ret;

		/* घातer करोwn the PLL beक्रमe reprogramming it */
		regmap_update_bits_check(wm8804->regmap, WM8804_PWRDN,
					 0x1, 0x1, &change);
		अगर (!change)
			pm_runसमय_get_sync(wm8804->dev);

		/* set PLLN and PRESCALE */
		snd_soc_component_update_bits(component, WM8804_PLL4, 0xf | 0x10,
				    pll_भाग.n | (pll_भाग.prescale << 4));
		/* set mclkभाग and freqmode */
		snd_soc_component_update_bits(component, WM8804_PLL5, 0x3 | 0x8,
				    pll_भाग.freqmode | (pll_भाग.mclkभाग << 3));
		/* set PLLK */
		snd_soc_component_ग_लिखो(component, WM8804_PLL1, pll_भाग.k & 0xff);
		snd_soc_component_ग_लिखो(component, WM8804_PLL2, (pll_भाग.k >> 8) & 0xff);
		snd_soc_component_ग_लिखो(component, WM8804_PLL3, pll_भाग.k >> 16);

		/* घातer up the PLL */
		snd_soc_component_update_bits(component, WM8804_PWRDN, 0x1, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8804_set_sysclk(काष्ठा snd_soc_dai *dai,
			     पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component;

	component = dai->component;

	चयन (clk_id) अणु
	हाल WM8804_TX_CLKSRC_MCLK:
		अगर ((freq >= 10000000 && freq <= 14400000)
				|| (freq >= 16280000 && freq <= 27000000))
			snd_soc_component_update_bits(component, WM8804_PLL6, 0x80, 0x80);
		अन्यथा अणु
			dev_err(dai->dev, "OSCCLOCK is not within the "
				"recommended range: %uHz\n", freq);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल WM8804_TX_CLKSRC_PLL:
		snd_soc_component_update_bits(component, WM8804_PLL6, 0x80, 0);
		अवरोध;
	हाल WM8804_CLKOUT_SRC_CLK1:
		snd_soc_component_update_bits(component, WM8804_PLL6, 0x8, 0);
		अवरोध;
	हाल WM8804_CLKOUT_SRC_OSCCLK:
		snd_soc_component_update_bits(component, WM8804_PLL6, 0x8, 0x8);
		अवरोध;
	शेष:
		dev_err(dai->dev, "Unknown clock source: %d\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8804_set_clkभाग(काष्ठा snd_soc_dai *dai,
			     पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा wm8804_priv *wm8804;

	component = dai->component;
	चयन (भाग_id) अणु
	हाल WM8804_CLKOUT_DIV:
		snd_soc_component_update_bits(component, WM8804_PLL5, 0x30,
				    (भाग & 0x3) << 4);
		अवरोध;
	हाल WM8804_MCLK_DIV:
		wm8804 = snd_soc_component_get_drvdata(component);
		wm8804->mclk_भाग = भाग;
		अवरोध;
	शेष:
		dev_err(dai->dev, "Unknown clock divider: %d\n", भाग_id);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops wm8804_dai_ops = अणु
	.hw_params = wm8804_hw_params,
	.set_fmt = wm8804_set_fmt,
	.set_sysclk = wm8804_set_sysclk,
	.set_clkभाग = wm8804_set_clkभाग,
	.set_pll = wm8804_set_pll
पूर्ण;

#घोषणा WM8804_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE)

#घोषणा WM8804_RATES (SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 | \
		      SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_64000 | \
		      SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000 | \
		      SNDRV_PCM_RATE_176400 | SNDRV_PCM_RATE_192000)

अटल काष्ठा snd_soc_dai_driver wm8804_dai = अणु
	.name = "wm8804-spdif",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = WM8804_RATES,
		.क्रमmats = WM8804_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = WM8804_RATES,
		.क्रमmats = WM8804_FORMATS,
	पूर्ण,
	.ops = &wm8804_dai_ops,
	.symmetric_rate = 1
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8804 = अणु
	.dapm_widमाला_लो		= wm8804_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8804_dapm_widमाला_लो),
	.dapm_routes		= wm8804_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8804_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

स्थिर काष्ठा regmap_config wm8804_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = WM8804_MAX_REGISTER,
	.अस्थिर_reg = wm8804_अस्थिर,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = wm8804_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8804_reg_शेषs),
पूर्ण;
EXPORT_SYMBOL_GPL(wm8804_regmap_config);

पूर्णांक wm8804_probe(काष्ठा device *dev, काष्ठा regmap *regmap)
अणु
	काष्ठा wm8804_priv *wm8804;
	अचिन्हित पूर्णांक id1, id2;
	पूर्णांक i, ret;

	wm8804 = devm_kzalloc(dev, माप(*wm8804), GFP_KERNEL);
	अगर (!wm8804)
		वापस -ENOMEM;

	dev_set_drvdata(dev, wm8804);

	wm8804->dev = dev;
	wm8804->regmap = regmap;

	wm8804->reset = devm_gpiod_get_optional(dev, "wlf,reset",
						GPIOD_OUT_LOW);
	अगर (IS_ERR(wm8804->reset)) अणु
		ret = PTR_ERR(wm8804->reset);
		dev_err(dev, "Failed to get reset line: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(wm8804->supplies); i++)
		wm8804->supplies[i].supply = wm8804_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(wm8804->supplies),
				      wm8804->supplies);
	अगर (ret) अणु
		dev_err(dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	wm8804->disable_nb[0].notअगरier_call = wm8804_regulator_event_0;
	wm8804->disable_nb[1].notअगरier_call = wm8804_regulator_event_1;

	/* This should really be moved पूर्णांकo the regulator core */
	क्रम (i = 0; i < ARRAY_SIZE(wm8804->supplies); i++) अणु
		काष्ठा regulator *regulator = wm8804->supplies[i].consumer;

		ret = devm_regulator_रेजिस्टर_notअगरier(regulator,
						       &wm8804->disable_nb[i]);
		अगर (ret != 0) अणु
			dev_err(dev,
				"Failed to register regulator notifier: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8804->supplies),
				    wm8804->supplies);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	gpiod_set_value_cansleep(wm8804->reset, 1);

	ret = regmap_पढ़ो(regmap, WM8804_RST_DEVID1, &id1);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read device ID: %d\n", ret);
		जाओ err_reg_enable;
	पूर्ण

	ret = regmap_पढ़ो(regmap, WM8804_DEVID2, &id2);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read device ID: %d\n", ret);
		जाओ err_reg_enable;
	पूर्ण

	id2 = (id2 << 8) | id1;

	अगर (id2 != 0x8805) अणु
		dev_err(dev, "Invalid device ID: %#x\n", id2);
		ret = -EINVAL;
		जाओ err_reg_enable;
	पूर्ण

	ret = regmap_पढ़ो(regmap, WM8804_DEVREV, &id1);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read device revision: %d\n",
			ret);
		जाओ err_reg_enable;
	पूर्ण
	dev_info(dev, "revision %c\n", id1 + 'A');

	अगर (!wm8804->reset) अणु
		ret = wm8804_soft_reset(wm8804);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to issue reset: %d\n", ret);
			जाओ err_reg_enable;
		पूर्ण
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(dev, &soc_component_dev_wm8804,
				     &wm8804_dai, 1);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to register CODEC: %d\n", ret);
		जाओ err_reg_enable;
	पूर्ण

	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_idle(dev);

	वापस 0;

err_reg_enable:
	regulator_bulk_disable(ARRAY_SIZE(wm8804->supplies), wm8804->supplies);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wm8804_probe);

व्योम wm8804_हटाओ(काष्ठा device *dev)
अणु
	pm_runसमय_disable(dev);
पूर्ण
EXPORT_SYMBOL_GPL(wm8804_हटाओ);

#अगर IS_ENABLED(CONFIG_PM)
अटल पूर्णांक wm8804_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा wm8804_priv *wm8804 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8804->supplies),
				    wm8804->supplies);
	अगर (ret) अणु
		dev_err(wm8804->dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	regcache_sync(wm8804->regmap);

	/* Power up OSCCLK */
	regmap_update_bits(wm8804->regmap, WM8804_PWRDN, 0x8, 0x0);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8804_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा wm8804_priv *wm8804 = dev_get_drvdata(dev);

	/* Power करोwn OSCCLK */
	regmap_update_bits(wm8804->regmap, WM8804_PWRDN, 0x8, 0x8);

	regulator_bulk_disable(ARRAY_SIZE(wm8804->supplies),
			       wm8804->supplies);

	वापस 0;
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा dev_pm_ops wm8804_pm = अणु
	SET_RUNTIME_PM_OPS(wm8804_runसमय_suspend, wm8804_runसमय_resume, शून्य)
पूर्ण;
EXPORT_SYMBOL_GPL(wm8804_pm);

MODULE_DESCRIPTION("ASoC WM8804 driver");
MODULE_AUTHOR("Dimitris Papastamos <dp@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
