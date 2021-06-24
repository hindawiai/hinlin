<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Cirrus Logic Madera class codecs common support
//
// Copyright (C) 2015-2019 Cirrus Logic, Inc. and
//                         Cirrus Logic International Semiconductor Ltd.
//

#समावेश <linux/delay.h>
#समावेश <linux/gcd.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>

#समावेश <linux/irqchip/irq-madera.h>
#समावेश <linux/mfd/madera/core.h>
#समावेश <linux/mfd/madera/रेजिस्टरs.h>
#समावेश <linux/mfd/madera/pdata.h>
#समावेश <sound/madera-pdata.h>

#समावेश <dt-bindings/sound/madera.h>

#समावेश "madera.h"

#घोषणा MADERA_AIF_BCLK_CTRL			0x00
#घोषणा MADERA_AIF_TX_PIN_CTRL			0x01
#घोषणा MADERA_AIF_RX_PIN_CTRL			0x02
#घोषणा MADERA_AIF_RATE_CTRL			0x03
#घोषणा MADERA_AIF_FORMAT			0x04
#घोषणा MADERA_AIF_RX_BCLK_RATE			0x06
#घोषणा MADERA_AIF_FRAME_CTRL_1			0x07
#घोषणा MADERA_AIF_FRAME_CTRL_2			0x08
#घोषणा MADERA_AIF_FRAME_CTRL_3			0x09
#घोषणा MADERA_AIF_FRAME_CTRL_4			0x0A
#घोषणा MADERA_AIF_FRAME_CTRL_5			0x0B
#घोषणा MADERA_AIF_FRAME_CTRL_6			0x0C
#घोषणा MADERA_AIF_FRAME_CTRL_7			0x0D
#घोषणा MADERA_AIF_FRAME_CTRL_8			0x0E
#घोषणा MADERA_AIF_FRAME_CTRL_9			0x0F
#घोषणा MADERA_AIF_FRAME_CTRL_10		0x10
#घोषणा MADERA_AIF_FRAME_CTRL_11		0x11
#घोषणा MADERA_AIF_FRAME_CTRL_12		0x12
#घोषणा MADERA_AIF_FRAME_CTRL_13		0x13
#घोषणा MADERA_AIF_FRAME_CTRL_14		0x14
#घोषणा MADERA_AIF_FRAME_CTRL_15		0x15
#घोषणा MADERA_AIF_FRAME_CTRL_16		0x16
#घोषणा MADERA_AIF_FRAME_CTRL_17		0x17
#घोषणा MADERA_AIF_FRAME_CTRL_18		0x18
#घोषणा MADERA_AIF_TX_ENABLES			0x19
#घोषणा MADERA_AIF_RX_ENABLES			0x1A
#घोषणा MADERA_AIF_FORCE_WRITE			0x1B

#घोषणा MADERA_DSP_CONFIG_1_OFFS		0x00
#घोषणा MADERA_DSP_CONFIG_2_OFFS		0x02

#घोषणा MADERA_DSP_CLK_SEL_MASK			0x70000
#घोषणा MADERA_DSP_CLK_SEL_SHIFT		16

#घोषणा MADERA_DSP_RATE_MASK			0x7800
#घोषणा MADERA_DSP_RATE_SHIFT			11

#घोषणा MADERA_SYSCLK_6MHZ			0
#घोषणा MADERA_SYSCLK_12MHZ			1
#घोषणा MADERA_SYSCLK_24MHZ			2
#घोषणा MADERA_SYSCLK_49MHZ			3
#घोषणा MADERA_SYSCLK_98MHZ			4

#घोषणा MADERA_DSPCLK_9MHZ			0
#घोषणा MADERA_DSPCLK_18MHZ			1
#घोषणा MADERA_DSPCLK_36MHZ			2
#घोषणा MADERA_DSPCLK_73MHZ			3
#घोषणा MADERA_DSPCLK_147MHZ			4

#घोषणा MADERA_FLL_VCO_CORNER			141900000
#घोषणा MADERA_FLL_MAX_FREF			13500000
#घोषणा MADERA_FLL_MAX_N			1023
#घोषणा MADERA_FLL_MIN_FOUT			90000000
#घोषणा MADERA_FLL_MAX_FOUT			100000000
#घोषणा MADERA_FLL_MAX_FRATIO			16
#घोषणा MADERA_FLL_MAX_REFDIV			8
#घोषणा MADERA_FLL_OUTDIV			3
#घोषणा MADERA_FLL_VCO_MULT			3
#घोषणा MADERA_FLLAO_MAX_FREF			12288000
#घोषणा MADERA_FLLAO_MIN_N			4
#घोषणा MADERA_FLLAO_MAX_N			1023
#घोषणा MADERA_FLLAO_MAX_FBDIV			254
#घोषणा MADERA_FLLHJ_पूर्णांक_उच्च_N			1023
#घोषणा MADERA_FLLHJ_पूर्णांक_न्यून_N			1
#घोषणा MADERA_FLLHJ_FRAC_MAX_N			255
#घोषणा MADERA_FLLHJ_FRAC_MIN_N			4
#घोषणा MADERA_FLLHJ_LOW_THRESH			192000
#घोषणा MADERA_FLLHJ_MID_THRESH			1152000
#घोषणा MADERA_FLLHJ_MAX_THRESH			13000000
#घोषणा MADERA_FLLHJ_LOW_GAINS			0x23f0
#घोषणा MADERA_FLLHJ_MID_GAINS			0x22f2
#घोषणा MADERA_FLLHJ_HIGH_GAINS			0x21f0

#घोषणा MADERA_FLL_SYNCHRONISER_OFFS		0x10
#घोषणा CS47L35_FLL_SYNCHRONISER_OFFS		0xE
#घोषणा MADERA_FLL_CONTROL_1_OFFS		0x1
#घोषणा MADERA_FLL_CONTROL_2_OFFS		0x2
#घोषणा MADERA_FLL_CONTROL_3_OFFS		0x3
#घोषणा MADERA_FLL_CONTROL_4_OFFS		0x4
#घोषणा MADERA_FLL_CONTROL_5_OFFS		0x5
#घोषणा MADERA_FLL_CONTROL_6_OFFS		0x6
#घोषणा MADERA_FLL_GAIN_OFFS			0x8
#घोषणा MADERA_FLL_CONTROL_7_OFFS		0x9
#घोषणा MADERA_FLL_EFS_2_OFFS			0xA
#घोषणा MADERA_FLL_SYNCHRONISER_1_OFFS		0x1
#घोषणा MADERA_FLL_SYNCHRONISER_2_OFFS		0x2
#घोषणा MADERA_FLL_SYNCHRONISER_3_OFFS		0x3
#घोषणा MADERA_FLL_SYNCHRONISER_4_OFFS		0x4
#घोषणा MADERA_FLL_SYNCHRONISER_5_OFFS		0x5
#घोषणा MADERA_FLL_SYNCHRONISER_6_OFFS		0x6
#घोषणा MADERA_FLL_SYNCHRONISER_7_OFFS		0x7
#घोषणा MADERA_FLL_SPREAD_SPECTRUM_OFFS		0x9
#घोषणा MADERA_FLL_GPIO_CLOCK_OFFS		0xA
#घोषणा MADERA_FLL_CONTROL_10_OFFS		0xA
#घोषणा MADERA_FLL_CONTROL_11_OFFS		0xB
#घोषणा MADERA_FLL1_DIGITAL_TEST_1_OFFS		0xD

#घोषणा MADERA_FLLAO_CONTROL_1_OFFS		0x1
#घोषणा MADERA_FLLAO_CONTROL_2_OFFS		0x2
#घोषणा MADERA_FLLAO_CONTROL_3_OFFS		0x3
#घोषणा MADERA_FLLAO_CONTROL_4_OFFS		0x4
#घोषणा MADERA_FLLAO_CONTROL_5_OFFS		0x5
#घोषणा MADERA_FLLAO_CONTROL_6_OFFS		0x6
#घोषणा MADERA_FLLAO_CONTROL_7_OFFS		0x8
#घोषणा MADERA_FLLAO_CONTROL_8_OFFS		0xA
#घोषणा MADERA_FLLAO_CONTROL_9_OFFS		0xB
#घोषणा MADERA_FLLAO_CONTROL_10_OFFS		0xC
#घोषणा MADERA_FLLAO_CONTROL_11_OFFS		0xD

#घोषणा MADERA_FMT_DSP_MODE_A			0
#घोषणा MADERA_FMT_DSP_MODE_B			1
#घोषणा MADERA_FMT_I2S_MODE			2
#घोषणा MADERA_FMT_LEFT_JUSTIFIED_MODE		3

#घोषणा madera_fll_err(_fll, fmt, ...) \
	dev_err(_fll->madera->dev, "FLL%d: " fmt, _fll->id, ##__VA_ARGS__)
#घोषणा madera_fll_warn(_fll, fmt, ...) \
	dev_warn(_fll->madera->dev, "FLL%d: " fmt, _fll->id, ##__VA_ARGS__)
#घोषणा madera_fll_dbg(_fll, fmt, ...) \
	dev_dbg(_fll->madera->dev, "FLL%d: " fmt, _fll->id, ##__VA_ARGS__)

#घोषणा madera_aअगर_err(_dai, fmt, ...) \
	dev_err(_dai->dev, "AIF%d: " fmt, _dai->id, ##__VA_ARGS__)
#घोषणा madera_aअगर_warn(_dai, fmt, ...) \
	dev_warn(_dai->dev, "AIF%d: " fmt, _dai->id, ##__VA_ARGS__)
#घोषणा madera_aअगर_dbg(_dai, fmt, ...) \
	dev_dbg(_dai->dev, "AIF%d: " fmt, _dai->id, ##__VA_ARGS__)

अटल स्थिर पूर्णांक madera_dsp_bus_error_irqs[MADERA_MAX_ADSP] = अणु
	MADERA_IRQ_DSP1_BUS_ERR,
	MADERA_IRQ_DSP2_BUS_ERR,
	MADERA_IRQ_DSP3_BUS_ERR,
	MADERA_IRQ_DSP4_BUS_ERR,
	MADERA_IRQ_DSP5_BUS_ERR,
	MADERA_IRQ_DSP6_BUS_ERR,
	MADERA_IRQ_DSP7_BUS_ERR,
पूर्ण;

पूर्णांक madera_clk_ev(काष्ठा snd_soc_dapm_widget *w,
		  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा madera *madera = priv->madera;
	अचिन्हित पूर्णांक val;
	पूर्णांक clk_idx;
	पूर्णांक ret;

	ret = regmap_पढ़ो(madera->regmap, w->reg, &val);
	अगर (ret) अणु
		dev_err(madera->dev, "Failed to check clock source: %d\n", ret);
		वापस ret;
	पूर्ण

	चयन ((val & MADERA_SYSCLK_SRC_MASK) >> MADERA_SYSCLK_SRC_SHIFT) अणु
	हाल MADERA_CLK_SRC_MCLK1:
		clk_idx = MADERA_MCLK1;
		अवरोध;
	हाल MADERA_CLK_SRC_MCLK2:
		clk_idx = MADERA_MCLK2;
		अवरोध;
	हाल MADERA_CLK_SRC_MCLK3:
		clk_idx = MADERA_MCLK3;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		वापस clk_prepare_enable(madera->mclk[clk_idx].clk);
	हाल SND_SOC_DAPM_POST_PMD:
		clk_disable_unprepare(madera->mclk[clk_idx].clk);
		वापस 0;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(madera_clk_ev);

अटल व्योम madera_spin_sysclk(काष्ठा madera_priv *priv)
अणु
	काष्ठा madera *madera = priv->madera;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret, i;

	/* Skip this अगर the chip is करोwn */
	अगर (pm_runसमय_suspended(madera->dev))
		वापस;

	/*
	 * Just पढ़ो a रेजिस्टर a few बार to ensure the पूर्णांकernal
	 * oscillator sends out a few घड़ीs.
	 */
	क्रम (i = 0; i < 4; i++) अणु
		ret = regmap_पढ़ो(madera->regmap, MADERA_SOFTWARE_RESET, &val);
		अगर (ret)
			dev_err(madera->dev,
				"Failed to read sysclk spin %d: %d\n", i, ret);
	पूर्ण

	udelay(300);
पूर्ण

पूर्णांक madera_sysclk_ev(काष्ठा snd_soc_dapm_widget *w,
		     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
	हाल SND_SOC_DAPM_PRE_PMD:
		madera_spin_sysclk(priv);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस madera_clk_ev(w, kcontrol, event);
पूर्ण
EXPORT_SYMBOL_GPL(madera_sysclk_ev);

अटल पूर्णांक madera_check_speaker_overheat(काष्ठा madera *madera,
					 bool *warn, bool *shutकरोwn)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(madera->regmap, MADERA_IRQ1_RAW_STATUS_15, &val);
	अगर (ret) अणु
		dev_err(madera->dev, "Failed to read thermal status: %d\n",
			ret);
		वापस ret;
	पूर्ण

	*warn = val & MADERA_SPK_OVERHEAT_WARN_STS1;
	*shutकरोwn = val & MADERA_SPK_OVERHEAT_STS1;

	वापस 0;
पूर्ण

पूर्णांक madera_spk_ev(काष्ठा snd_soc_dapm_widget *w,
		  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा madera *madera = priv->madera;
	bool warn, shutकरोwn;
	पूर्णांक ret;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		ret = madera_check_speaker_overheat(madera, &warn, &shutकरोwn);
		अगर (ret)
			वापस ret;

		अगर (shutकरोwn) अणु
			dev_crit(madera->dev,
				 "Speaker not enabled due to temperature\n");
			वापस -EBUSY;
		पूर्ण

		regmap_update_bits(madera->regmap, MADERA_OUTPUT_ENABLES_1,
				   1 << w->shअगरt, 1 << w->shअगरt);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_update_bits(madera->regmap, MADERA_OUTPUT_ENABLES_1,
				   1 << w->shअगरt, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(madera_spk_ev);

अटल irqवापस_t madera_thermal_warn(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा madera *madera = data;
	bool warn, shutकरोwn;
	पूर्णांक ret;

	ret = madera_check_speaker_overheat(madera, &warn, &shutकरोwn);
	अगर (ret || shutकरोwn) अणु /* क्रम safety attempt to shutकरोwn on error */
		dev_crit(madera->dev, "Thermal shutdown\n");
		ret = regmap_update_bits(madera->regmap,
					 MADERA_OUTPUT_ENABLES_1,
					 MADERA_OUT4L_ENA |
					 MADERA_OUT4R_ENA, 0);
		अगर (ret != 0)
			dev_crit(madera->dev,
				 "Failed to disable speaker outputs: %d\n",
				 ret);
	पूर्ण अन्यथा अगर (warn) अणु
		dev_alert(madera->dev, "Thermal warning\n");
	पूर्ण अन्यथा अणु
		dev_info(madera->dev, "Spurious thermal warning\n");
		वापस IRQ_NONE;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक madera_init_overheat(काष्ठा madera_priv *priv)
अणु
	काष्ठा madera *madera = priv->madera;
	काष्ठा device *dev = madera->dev;
	पूर्णांक ret;

	ret = madera_request_irq(madera, MADERA_IRQ_SPK_OVERHEAT_WARN,
				 "Thermal warning", madera_thermal_warn,
				 madera);
	अगर (ret)
		dev_err(dev, "Failed to get thermal warning IRQ: %d\n", ret);

	ret = madera_request_irq(madera, MADERA_IRQ_SPK_OVERHEAT,
				 "Thermal shutdown", madera_thermal_warn,
				 madera);
	अगर (ret)
		dev_err(dev, "Failed to get thermal shutdown IRQ: %d\n", ret);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(madera_init_overheat);

पूर्णांक madera_मुक्त_overheat(काष्ठा madera_priv *priv)
अणु
	काष्ठा madera *madera = priv->madera;

	madera_मुक्त_irq(madera, MADERA_IRQ_SPK_OVERHEAT_WARN, madera);
	madera_मुक्त_irq(madera, MADERA_IRQ_SPK_OVERHEAT, madera);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(madera_मुक्त_overheat);

अटल पूर्णांक madera_get_variable_u32_array(काष्ठा device *dev,
					 स्थिर अक्षर *propname,
					 u32 *dest, पूर्णांक n_max,
					 पूर्णांक multiple)
अणु
	पूर्णांक n, ret;

	n = device_property_count_u32(dev, propname);
	अगर (n < 0) अणु
		अगर (n == -EINVAL)
			वापस 0;	/* missing, ignore */

		dev_warn(dev, "%s malformed (%d)\n", propname, n);

		वापस n;
	पूर्ण अन्यथा अगर ((n % multiple) != 0) अणु
		dev_warn(dev, "%s not a multiple of %d entries\n",
			 propname, multiple);

		वापस -EINVAL;
	पूर्ण

	अगर (n > n_max)
		n = n_max;

	ret = device_property_पढ़ो_u32_array(dev, propname, dest, n);
	अगर (ret < 0)
		वापस ret;

	वापस n;
पूर्ण

अटल व्योम madera_prop_get_inmode(काष्ठा madera_priv *priv)
अणु
	काष्ठा madera *madera = priv->madera;
	काष्ठा madera_codec_pdata *pdata = &madera->pdata.codec;
	u32 पंचांगp[MADERA_MAX_INPUT * MADERA_MAX_MUXED_CHANNELS];
	पूर्णांक n, i, in_idx, ch_idx;

	BUILD_BUG_ON(ARRAY_SIZE(pdata->inmode) != MADERA_MAX_INPUT);
	BUILD_BUG_ON(ARRAY_SIZE(pdata->inmode[0]) != MADERA_MAX_MUXED_CHANNELS);

	n = madera_get_variable_u32_array(madera->dev, "cirrus,inmode",
					  पंचांगp, ARRAY_SIZE(पंचांगp),
					  MADERA_MAX_MUXED_CHANNELS);
	अगर (n < 0)
		वापस;

	in_idx = 0;
	ch_idx = 0;
	क्रम (i = 0; i < n; ++i) अणु
		pdata->inmode[in_idx][ch_idx] = पंचांगp[i];

		अगर (++ch_idx == MADERA_MAX_MUXED_CHANNELS) अणु
			ch_idx = 0;
			++in_idx;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम madera_prop_get_pdata(काष्ठा madera_priv *priv)
अणु
	काष्ठा madera *madera = priv->madera;
	काष्ठा madera_codec_pdata *pdata = &madera->pdata.codec;
	u32 out_mono[ARRAY_SIZE(pdata->out_mono)];
	पूर्णांक i, n;

	madera_prop_get_inmode(priv);

	n = madera_get_variable_u32_array(madera->dev, "cirrus,out-mono",
					  out_mono, ARRAY_SIZE(out_mono), 1);
	अगर (n > 0)
		क्रम (i = 0; i < n; ++i)
			pdata->out_mono[i] = !!out_mono[i];

	madera_get_variable_u32_array(madera->dev,
				      "cirrus,max-channels-clocked",
				      pdata->max_channels_घड़ीed,
				      ARRAY_SIZE(pdata->max_channels_घड़ीed),
				      1);

	madera_get_variable_u32_array(madera->dev, "cirrus,pdm-fmt",
				      pdata->pdm_fmt,
				      ARRAY_SIZE(pdata->pdm_fmt), 1);

	madera_get_variable_u32_array(madera->dev, "cirrus,pdm-mute",
				      pdata->pdm_mute,
				      ARRAY_SIZE(pdata->pdm_mute), 1);

	madera_get_variable_u32_array(madera->dev, "cirrus,dmic-ref",
				      pdata->dmic_ref,
				      ARRAY_SIZE(pdata->dmic_ref), 1);
पूर्ण

पूर्णांक madera_core_init(काष्ठा madera_priv *priv)
अणु
	पूर्णांक i;

	/* trap undersized array initializers */
	BUILD_BUG_ON(!madera_mixer_texts[MADERA_NUM_MIXER_INPUTS - 1]);
	BUILD_BUG_ON(!madera_mixer_values[MADERA_NUM_MIXER_INPUTS - 1]);

	अगर (!dev_get_platdata(priv->madera->dev))
		madera_prop_get_pdata(priv);

	mutex_init(&priv->rate_lock);

	क्रम (i = 0; i < MADERA_MAX_HP_OUTPUT; i++)
		priv->madera->out_clamp[i] = true;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(madera_core_init);

पूर्णांक madera_core_मुक्त(काष्ठा madera_priv *priv)
अणु
	mutex_destroy(&priv->rate_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(madera_core_मुक्त);

अटल व्योम madera_debug_dump_करोमुख्य_groups(स्थिर काष्ठा madera_priv *priv)
अणु
	काष्ठा madera *madera = priv->madera;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(priv->करोमुख्य_group_ref); ++i)
		dev_dbg(madera->dev, "domain_grp_ref[%d]=%d\n", i,
			priv->करोमुख्य_group_ref[i]);
पूर्ण

पूर्णांक madera_करोमुख्य_clk_ev(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *kcontrol,
			 पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक करोm_grp = w->shअगरt;

	अगर (करोm_grp >= ARRAY_SIZE(priv->करोमुख्य_group_ref)) अणु
		WARN(true, "%s dom_grp exceeds array size\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/*
	 * We can't rely on the DAPM mutex क्रम locking because we need a lock
	 * that can safely be called in hw_params
	 */
	mutex_lock(&priv->rate_lock);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		dev_dbg(priv->madera->dev, "Inc ref on domain group %d\n",
			करोm_grp);
		++priv->करोमुख्य_group_ref[करोm_grp];
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		dev_dbg(priv->madera->dev, "Dec ref on domain group %d\n",
			करोm_grp);
		--priv->करोमुख्य_group_ref[करोm_grp];
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	madera_debug_dump_करोमुख्य_groups(priv);

	mutex_unlock(&priv->rate_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(madera_करोमुख्य_clk_ev);

पूर्णांक madera_out1_demux_put(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा madera *madera = priv->madera;
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक ep_sel, mux, change;
	bool out_mono;
	पूर्णांक ret;

	अगर (ucontrol->value.क्रमागतerated.item[0] > e->items - 1)
		वापस -EINVAL;

	mux = ucontrol->value.क्रमागतerated.item[0];

	snd_soc_dapm_mutex_lock(dapm);

	ep_sel = mux << MADERA_EP_SEL_SHIFT;

	change = snd_soc_component_test_bits(component, MADERA_OUTPUT_ENABLES_1,
					     MADERA_EP_SEL_MASK,
					     ep_sel);
	अगर (!change)
		जाओ end;

	/* EP_SEL should not be modअगरied जबतक HP or EP driver is enabled */
	ret = regmap_update_bits(madera->regmap, MADERA_OUTPUT_ENABLES_1,
				 MADERA_OUT1L_ENA | MADERA_OUT1R_ENA, 0);
	अगर (ret)
		dev_warn(madera->dev, "Failed to disable outputs: %d\n", ret);

	usleep_range(2000, 3000); /* रुको क्रम wseq to complete */

	/* change demux setting */
	ret = 0;
	अगर (madera->out_clamp[0])
		ret = regmap_update_bits(madera->regmap,
					 MADERA_OUTPUT_ENABLES_1,
					 MADERA_EP_SEL_MASK, ep_sel);
	अगर (ret) अणु
		dev_err(madera->dev, "Failed to set OUT1 demux: %d\n", ret);
	पूर्ण अन्यथा अणु
		/* apply correct setting क्रम mono mode */
		अगर (!ep_sel && !madera->pdata.codec.out_mono[0])
			out_mono = false; /* stereo HP */
		अन्यथा
			out_mono = true; /* EP or mono HP */

		ret = madera_set_output_mode(component, 1, out_mono);
		अगर (ret)
			dev_warn(madera->dev,
				 "Failed to set output mode: %d\n", ret);
	पूर्ण

	/*
	 * अगर HPDET has disabled the clamp जबतक चयनing to HPOUT
	 * OUT1 should reमुख्य disabled
	 */
	अगर (ep_sel ||
	    (madera->out_clamp[0] && !madera->out_लघुed[0])) अणु
		ret = regmap_update_bits(madera->regmap,
					 MADERA_OUTPUT_ENABLES_1,
					 MADERA_OUT1L_ENA | MADERA_OUT1R_ENA,
					 madera->hp_ena);
		अगर (ret)
			dev_warn(madera->dev,
				 "Failed to restore earpiece outputs: %d\n",
				 ret);
		अन्यथा अगर (madera->hp_ena)
			msleep(34); /* रुको क्रम enable wseq */
		अन्यथा
			usleep_range(2000, 3000); /* रुको क्रम disable wseq */
	पूर्ण

end:
	snd_soc_dapm_mutex_unlock(dapm);

	वापस snd_soc_dapm_mux_update_घातer(dapm, kcontrol, mux, e, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(madera_out1_demux_put);

पूर्णांक madera_out1_demux_get(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_kcontrol_component(kcontrol);
	अचिन्हित पूर्णांक val;

	val = snd_soc_component_पढ़ो(component, MADERA_OUTPUT_ENABLES_1);
	val &= MADERA_EP_SEL_MASK;
	val >>= MADERA_EP_SEL_SHIFT;
	ucontrol->value.क्रमागतerated.item[0] = val;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(madera_out1_demux_get);

अटल पूर्णांक madera_inmux_put(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा madera *madera = priv->madera;
	काष्ठा regmap *regmap = madera->regmap;
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक mux, val, mask;
	अचिन्हित पूर्णांक inmode;
	bool changed;
	पूर्णांक ret;

	mux = ucontrol->value.क्रमागतerated.item[0];
	अगर (mux > 1)
		वापस -EINVAL;

	val = mux << e->shअगरt_l;
	mask = (e->mask << e->shअगरt_l) | MADERA_IN1L_SRC_SE_MASK;

	चयन (e->reg) अणु
	हाल MADERA_ADC_DIGITAL_VOLUME_1L:
		inmode = madera->pdata.codec.inmode[0][2 * mux];
		अवरोध;
	हाल MADERA_ADC_DIGITAL_VOLUME_1R:
		inmode = madera->pdata.codec.inmode[0][1 + (2 * mux)];
		अवरोध;
	हाल MADERA_ADC_DIGITAL_VOLUME_2L:
		inmode = madera->pdata.codec.inmode[1][2 * mux];
		अवरोध;
	हाल MADERA_ADC_DIGITAL_VOLUME_2R:
		inmode = madera->pdata.codec.inmode[1][1 + (2 * mux)];
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (inmode & MADERA_INMODE_SE)
		val |= 1 << MADERA_IN1L_SRC_SE_SHIFT;

	dev_dbg(madera->dev, "mux=%u reg=0x%x inmode=0x%x mask=0x%x val=0x%x\n",
		mux, e->reg, inmode, mask, val);

	ret = regmap_update_bits_check(regmap, e->reg, mask, val, &changed);
	अगर (ret < 0)
		वापस ret;

	अगर (changed)
		वापस snd_soc_dapm_mux_update_घातer(dapm, kcontrol,
						     mux, e, शून्य);
	अन्यथा
		वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर madera_inmux_texts[] = अणु
	"A",
	"B",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(madera_in1muxl_क्रमागत,
			    MADERA_ADC_DIGITAL_VOLUME_1L,
			    MADERA_IN1L_SRC_SHIFT,
			    madera_inmux_texts);

अटल SOC_ENUM_SINGLE_DECL(madera_in1muxr_क्रमागत,
			    MADERA_ADC_DIGITAL_VOLUME_1R,
			    MADERA_IN1R_SRC_SHIFT,
			    madera_inmux_texts);

अटल SOC_ENUM_SINGLE_DECL(madera_in2muxl_क्रमागत,
			    MADERA_ADC_DIGITAL_VOLUME_2L,
			    MADERA_IN2L_SRC_SHIFT,
			    madera_inmux_texts);

अटल SOC_ENUM_SINGLE_DECL(madera_in2muxr_क्रमागत,
			    MADERA_ADC_DIGITAL_VOLUME_2R,
			    MADERA_IN2R_SRC_SHIFT,
			    madera_inmux_texts);

स्थिर काष्ठा snd_kcontrol_new madera_inmux[] = अणु
	SOC_DAPM_ENUM_EXT("IN1L Mux", madera_in1muxl_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन, madera_inmux_put),
	SOC_DAPM_ENUM_EXT("IN1R Mux", madera_in1muxr_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन, madera_inmux_put),
	SOC_DAPM_ENUM_EXT("IN2L Mux", madera_in2muxl_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन, madera_inmux_put),
	SOC_DAPM_ENUM_EXT("IN2R Mux", madera_in2muxr_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन, madera_inmux_put),
पूर्ण;
EXPORT_SYMBOL_GPL(madera_inmux);

अटल स्थिर अक्षर * स्थिर madera_dmode_texts[] = अणु
	"Analog",
	"Digital",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(madera_in1dmode_क्रमागत,
			    MADERA_IN1L_CONTROL,
			    MADERA_IN1_MODE_SHIFT,
			    madera_dmode_texts);

अटल SOC_ENUM_SINGLE_DECL(madera_in2dmode_क्रमागत,
			    MADERA_IN2L_CONTROL,
			    MADERA_IN2_MODE_SHIFT,
			    madera_dmode_texts);

अटल SOC_ENUM_SINGLE_DECL(madera_in3dmode_क्रमागत,
			    MADERA_IN3L_CONTROL,
			    MADERA_IN3_MODE_SHIFT,
			    madera_dmode_texts);

स्थिर काष्ठा snd_kcontrol_new madera_inmode[] = अणु
	SOC_DAPM_ENUM("IN1 Mode", madera_in1dmode_क्रमागत),
	SOC_DAPM_ENUM("IN2 Mode", madera_in2dmode_क्रमागत),
	SOC_DAPM_ENUM("IN3 Mode", madera_in3dmode_क्रमागत),
पूर्ण;
EXPORT_SYMBOL_GPL(madera_inmode);

अटल bool madera_can_change_grp_rate(स्थिर काष्ठा madera_priv *priv,
				       अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक count;

	चयन (reg) अणु
	हाल MADERA_FX_CTRL1:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_FX];
		अवरोध;
	हाल MADERA_ASRC1_RATE1:
	हाल MADERA_ASRC1_RATE2:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_ASRC1];
		अवरोध;
	हाल MADERA_ASRC2_RATE1:
	हाल MADERA_ASRC2_RATE2:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_ASRC2];
		अवरोध;
	हाल MADERA_ISRC_1_CTRL_1:
	हाल MADERA_ISRC_1_CTRL_2:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_ISRC1];
		अवरोध;
	हाल MADERA_ISRC_2_CTRL_1:
	हाल MADERA_ISRC_2_CTRL_2:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_ISRC2];
		अवरोध;
	हाल MADERA_ISRC_3_CTRL_1:
	हाल MADERA_ISRC_3_CTRL_2:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_ISRC3];
		अवरोध;
	हाल MADERA_ISRC_4_CTRL_1:
	हाल MADERA_ISRC_4_CTRL_2:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_ISRC4];
		अवरोध;
	हाल MADERA_OUTPUT_RATE_1:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_OUT];
		अवरोध;
	हाल MADERA_SPD1_TX_CONTROL:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_SPD];
		अवरोध;
	हाल MADERA_DSP1_CONFIG_1:
	हाल MADERA_DSP1_CONFIG_2:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_DSP1];
		अवरोध;
	हाल MADERA_DSP2_CONFIG_1:
	हाल MADERA_DSP2_CONFIG_2:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_DSP2];
		अवरोध;
	हाल MADERA_DSP3_CONFIG_1:
	हाल MADERA_DSP3_CONFIG_2:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_DSP3];
		अवरोध;
	हाल MADERA_DSP4_CONFIG_1:
	हाल MADERA_DSP4_CONFIG_2:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_DSP4];
		अवरोध;
	हाल MADERA_DSP5_CONFIG_1:
	हाल MADERA_DSP5_CONFIG_2:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_DSP5];
		अवरोध;
	हाल MADERA_DSP6_CONFIG_1:
	हाल MADERA_DSP6_CONFIG_2:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_DSP6];
		अवरोध;
	हाल MADERA_DSP7_CONFIG_1:
	हाल MADERA_DSP7_CONFIG_2:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_DSP7];
		अवरोध;
	हाल MADERA_AIF1_RATE_CTRL:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_AIF1];
		अवरोध;
	हाल MADERA_AIF2_RATE_CTRL:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_AIF2];
		अवरोध;
	हाल MADERA_AIF3_RATE_CTRL:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_AIF3];
		अवरोध;
	हाल MADERA_AIF4_RATE_CTRL:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_AIF4];
		अवरोध;
	हाल MADERA_SLIMBUS_RATES_1:
	हाल MADERA_SLIMBUS_RATES_2:
	हाल MADERA_SLIMBUS_RATES_3:
	हाल MADERA_SLIMBUS_RATES_4:
	हाल MADERA_SLIMBUS_RATES_5:
	हाल MADERA_SLIMBUS_RATES_6:
	हाल MADERA_SLIMBUS_RATES_7:
	हाल MADERA_SLIMBUS_RATES_8:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_SLIMBUS];
		अवरोध;
	हाल MADERA_PWM_DRIVE_1:
		count = priv->करोमुख्य_group_ref[MADERA_DOM_GRP_PWM];
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	dev_dbg(priv->madera->dev, "Rate reg 0x%x group ref %d\n", reg, count);

	अगर (count)
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

अटल पूर्णांक madera_adsp_rate_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक cached_rate;
	स्थिर पूर्णांक adsp_num = e->shअगरt_l;
	पूर्णांक item;

	mutex_lock(&priv->rate_lock);
	cached_rate = priv->adsp_rate_cache[adsp_num];
	mutex_unlock(&priv->rate_lock);

	item = snd_soc_क्रमागत_val_to_item(e, cached_rate);
	ucontrol->value.क्रमागतerated.item[0] = item;

	वापस 0;
पूर्ण

अटल पूर्णांक madera_adsp_rate_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	स्थिर पूर्णांक adsp_num = e->shअगरt_l;
	स्थिर अचिन्हित पूर्णांक item = ucontrol->value.क्रमागतerated.item[0];
	पूर्णांक ret;

	अगर (item >= e->items)
		वापस -EINVAL;

	/*
	 * We करोn't directly ग_लिखो the rate रेजिस्टर here but we want to
	 * मुख्यtain consistent behaviour that rate करोमुख्यs cannot be changed
	 * जबतक in use since this is a hardware requirement
	 */
	mutex_lock(&priv->rate_lock);

	अगर (!madera_can_change_grp_rate(priv, priv->adsp[adsp_num].base)) अणु
		dev_warn(priv->madera->dev,
			 "Cannot change '%s' while in use by active audio paths\n",
			 kcontrol->id.name);
		ret = -EBUSY;
	पूर्ण अन्यथा अणु
		/* Volatile रेजिस्टर so defer until the codec is घातered up */
		priv->adsp_rate_cache[adsp_num] = e->values[item];
		ret = 0;
	पूर्ण

	mutex_unlock(&priv->rate_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा soc_क्रमागत madera_adsp_rate_क्रमागत[] = अणु
	SOC_VALUE_ENUM_SINGLE(SND_SOC_NOPM, 0, 0xf, MADERA_RATE_ENUM_SIZE,
			      madera_rate_text, madera_rate_val),
	SOC_VALUE_ENUM_SINGLE(SND_SOC_NOPM, 1, 0xf, MADERA_RATE_ENUM_SIZE,
			      madera_rate_text, madera_rate_val),
	SOC_VALUE_ENUM_SINGLE(SND_SOC_NOPM, 2, 0xf, MADERA_RATE_ENUM_SIZE,
			      madera_rate_text, madera_rate_val),
	SOC_VALUE_ENUM_SINGLE(SND_SOC_NOPM, 3, 0xf, MADERA_RATE_ENUM_SIZE,
			      madera_rate_text, madera_rate_val),
	SOC_VALUE_ENUM_SINGLE(SND_SOC_NOPM, 4, 0xf, MADERA_RATE_ENUM_SIZE,
			      madera_rate_text, madera_rate_val),
	SOC_VALUE_ENUM_SINGLE(SND_SOC_NOPM, 5, 0xf, MADERA_RATE_ENUM_SIZE,
			      madera_rate_text, madera_rate_val),
	SOC_VALUE_ENUM_SINGLE(SND_SOC_NOPM, 6, 0xf, MADERA_RATE_ENUM_SIZE,
			      madera_rate_text, madera_rate_val),
पूर्ण;

स्थिर काष्ठा snd_kcontrol_new madera_adsp_rate_controls[] = अणु
	SOC_ENUM_EXT("DSP1 Rate", madera_adsp_rate_क्रमागत[0],
		     madera_adsp_rate_get, madera_adsp_rate_put),
	SOC_ENUM_EXT("DSP2 Rate", madera_adsp_rate_क्रमागत[1],
		     madera_adsp_rate_get, madera_adsp_rate_put),
	SOC_ENUM_EXT("DSP3 Rate", madera_adsp_rate_क्रमागत[2],
		     madera_adsp_rate_get, madera_adsp_rate_put),
	SOC_ENUM_EXT("DSP4 Rate", madera_adsp_rate_क्रमागत[3],
		     madera_adsp_rate_get, madera_adsp_rate_put),
	SOC_ENUM_EXT("DSP5 Rate", madera_adsp_rate_क्रमागत[4],
		     madera_adsp_rate_get, madera_adsp_rate_put),
	SOC_ENUM_EXT("DSP6 Rate", madera_adsp_rate_क्रमागत[5],
		     madera_adsp_rate_get, madera_adsp_rate_put),
	SOC_ENUM_EXT("DSP7 Rate", madera_adsp_rate_क्रमागत[6],
		     madera_adsp_rate_get, madera_adsp_rate_put),
पूर्ण;
EXPORT_SYMBOL_GPL(madera_adsp_rate_controls);

अटल पूर्णांक madera_ग_लिखो_adsp_clk_setting(काष्ठा madera_priv *priv,
					 काष्ठा wm_adsp *dsp,
					 अचिन्हित पूर्णांक freq)
अणु
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक mask = MADERA_DSP_RATE_MASK;
	पूर्णांक ret;

	val = priv->adsp_rate_cache[dsp->num - 1] << MADERA_DSP_RATE_SHIFT;

	चयन (priv->madera->type) अणु
	हाल CS47L35:
	हाल CS47L85:
	हाल WM1840:
		/* use legacy frequency रेजिस्टरs */
		mask |= MADERA_DSP_CLK_SEL_MASK;
		val |= (freq << MADERA_DSP_CLK_SEL_SHIFT);
		अवरोध;
	शेष:
		/* Configure exact dsp frequency */
		dev_dbg(priv->madera->dev, "Set DSP frequency to 0x%x\n", freq);

		ret = regmap_ग_लिखो(dsp->regmap,
				   dsp->base + MADERA_DSP_CONFIG_2_OFFS, freq);
		अगर (ret)
			जाओ err;
		अवरोध;
	पूर्ण

	ret = regmap_update_bits(dsp->regmap,
				 dsp->base + MADERA_DSP_CONFIG_1_OFFS,
				 mask, val);
	अगर (ret)
		जाओ err;

	dev_dbg(priv->madera->dev, "Set DSP clocking to 0x%x\n", val);

	वापस 0;

err:
	dev_err(dsp->dev, "Failed to set DSP%d clock: %d\n", dsp->num, ret);

	वापस ret;
पूर्ण

पूर्णांक madera_set_adsp_clk(काष्ठा madera_priv *priv, पूर्णांक dsp_num,
			अचिन्हित पूर्णांक freq)
अणु
	काष्ठा wm_adsp *dsp = &priv->adsp[dsp_num];
	काष्ठा madera *madera = priv->madera;
	अचिन्हित पूर्णांक cur, new;
	पूर्णांक ret;

	/*
	 * This is called at a higher DAPM priority than the mux widमाला_लो so
	 * the muxes are still off at this poपूर्णांक and it's safe to change
	 * the rate करोमुख्य control.
	 * Also called at a lower DAPM priority than the करोमुख्य group widमाला_लो
	 * so locking the पढ़ोs of adsp_rate_cache is not necessary as we know
	 * changes are locked out by the करोमुख्य_group_ref reference count.
	 */

	ret = regmap_पढ़ो(dsp->regmap,  dsp->base, &cur);
	अगर (ret) अणु
		dev_err(madera->dev,
			"Failed to read current DSP rate: %d\n", ret);
		वापस ret;
	पूर्ण

	cur &= MADERA_DSP_RATE_MASK;

	new = priv->adsp_rate_cache[dsp->num - 1] << MADERA_DSP_RATE_SHIFT;

	अगर (new == cur) अणु
		dev_dbg(madera->dev, "DSP rate not changed\n");
		वापस madera_ग_लिखो_adsp_clk_setting(priv, dsp, freq);
	पूर्ण अन्यथा अणु
		dev_dbg(madera->dev, "DSP rate changed\n");

		/* The ग_लिखो must be guarded by a number of SYSCLK cycles */
		madera_spin_sysclk(priv);
		ret = madera_ग_लिखो_adsp_clk_setting(priv, dsp, freq);
		madera_spin_sysclk(priv);
		वापस ret;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(madera_set_adsp_clk);

पूर्णांक madera_rate_put(काष्ठा snd_kcontrol *kcontrol,
		    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक item = ucontrol->value.क्रमागतerated.item[0];
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (item >= e->items)
		वापस -EINVAL;

	/*
	 * Prevent the करोमुख्य घातering up जबतक we're checking whether it's
	 * safe to change rate करोमुख्य
	 */
	mutex_lock(&priv->rate_lock);

	val = snd_soc_component_पढ़ो(component, e->reg);
	val >>= e->shअगरt_l;
	val &= e->mask;
	अगर (snd_soc_क्रमागत_item_to_val(e, item) == val) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	अगर (!madera_can_change_grp_rate(priv, e->reg)) अणु
		dev_warn(priv->madera->dev,
			 "Cannot change '%s' while in use by active audio paths\n",
			 kcontrol->id.name);
		ret = -EBUSY;
	पूर्ण अन्यथा अणु
		/* The ग_लिखो must be guarded by a number of SYSCLK cycles */
		madera_spin_sysclk(priv);
		ret = snd_soc_put_क्रमागत_द्विगुन(kcontrol, ucontrol);
		madera_spin_sysclk(priv);
	पूर्ण
out:
	mutex_unlock(&priv->rate_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(madera_rate_put);

अटल व्योम madera_configure_input_mode(काष्ठा madera *madera)
अणु
	अचिन्हित पूर्णांक dig_mode, ana_mode_l, ana_mode_r;
	पूर्णांक max_analogue_inमाला_दो, max_dmic_sup, i;

	चयन (madera->type) अणु
	हाल CS47L15:
		max_analogue_inमाला_दो = 1;
		max_dmic_sup = 2;
		अवरोध;
	हाल CS47L35:
		max_analogue_inमाला_दो = 2;
		max_dmic_sup = 2;
		अवरोध;
	हाल CS47L85:
	हाल WM1840:
		max_analogue_inमाला_दो = 3;
		max_dmic_sup = 3;
		अवरोध;
	हाल CS47L90:
	हाल CS47L91:
		max_analogue_inमाला_दो = 2;
		max_dmic_sup = 2;
		अवरोध;
	शेष:
		max_analogue_inमाला_दो = 2;
		max_dmic_sup = 4;
		अवरोध;
	पूर्ण

	/*
	 * Initialize input modes from the A settings. For muxed inमाला_दो the
	 * B settings will be applied अगर the mux is changed
	 */
	क्रम (i = 0; i < max_dmic_sup; i++) अणु
		dev_dbg(madera->dev, "IN%d mode %u:%u:%u:%u\n", i + 1,
			madera->pdata.codec.inmode[i][0],
			madera->pdata.codec.inmode[i][1],
			madera->pdata.codec.inmode[i][2],
			madera->pdata.codec.inmode[i][3]);

		dig_mode = madera->pdata.codec.dmic_ref[i] <<
			   MADERA_IN1_DMIC_SUP_SHIFT;

		चयन (madera->pdata.codec.inmode[i][0]) अणु
		हाल MADERA_INMODE_DIFF:
			ana_mode_l = 0;
			अवरोध;
		हाल MADERA_INMODE_SE:
			ana_mode_l = 1 << MADERA_IN1L_SRC_SE_SHIFT;
			अवरोध;
		शेष:
			dev_warn(madera->dev,
				 "IN%dAL Illegal inmode %u ignored\n",
				 i + 1, madera->pdata.codec.inmode[i][0]);
			जारी;
		पूर्ण

		चयन (madera->pdata.codec.inmode[i][1]) अणु
		हाल MADERA_INMODE_DIFF:
			ana_mode_r = 0;
			अवरोध;
		हाल MADERA_INMODE_SE:
			ana_mode_r = 1 << MADERA_IN1R_SRC_SE_SHIFT;
			अवरोध;
		शेष:
			dev_warn(madera->dev,
				 "IN%dAR Illegal inmode %u ignored\n",
				 i + 1, madera->pdata.codec.inmode[i][1]);
			जारी;
		पूर्ण

		dev_dbg(madera->dev,
			"IN%dA DMIC mode=0x%x Analogue mode=0x%x,0x%x\n",
			i + 1, dig_mode, ana_mode_l, ana_mode_r);

		regmap_update_bits(madera->regmap,
				   MADERA_IN1L_CONTROL + (i * 8),
				   MADERA_IN1_DMIC_SUP_MASK, dig_mode);

		अगर (i >= max_analogue_inमाला_दो)
			जारी;

		regmap_update_bits(madera->regmap,
				   MADERA_ADC_DIGITAL_VOLUME_1L + (i * 8),
				   MADERA_IN1L_SRC_SE_MASK, ana_mode_l);

		regmap_update_bits(madera->regmap,
				   MADERA_ADC_DIGITAL_VOLUME_1R + (i * 8),
				   MADERA_IN1R_SRC_SE_MASK, ana_mode_r);
	पूर्ण
पूर्ण

पूर्णांक madera_init_inमाला_दो(काष्ठा snd_soc_component *component)
अणु
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा madera *madera = priv->madera;

	madera_configure_input_mode(madera);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(madera_init_inमाला_दो);

अटल स्थिर काष्ठा snd_soc_dapm_route madera_mono_routes[] = अणु
	अणु "OUT1R", शून्य, "OUT1L" पूर्ण,
	अणु "OUT2R", शून्य, "OUT2L" पूर्ण,
	अणु "OUT3R", शून्य, "OUT3L" पूर्ण,
	अणु "OUT4R", शून्य, "OUT4L" पूर्ण,
	अणु "OUT5R", शून्य, "OUT5L" पूर्ण,
	अणु "OUT6R", शून्य, "OUT6L" पूर्ण,
पूर्ण;

पूर्णांक madera_init_outमाला_दो(काष्ठा snd_soc_component *component,
			स्थिर काष्ठा snd_soc_dapm_route *routes,
			पूर्णांक n_mono_routes, पूर्णांक n_real)
अणु
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा madera *madera = priv->madera;
	स्थिर काष्ठा madera_codec_pdata *pdata = &madera->pdata.codec;
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	अगर (n_mono_routes > MADERA_MAX_OUTPUT) अणु
		dev_warn(madera->dev,
			 "Requested %d mono outputs, using maximum allowed %d\n",
			 n_mono_routes, MADERA_MAX_OUTPUT);
		n_mono_routes = MADERA_MAX_OUTPUT;
	पूर्ण

	अगर (!routes)
		routes = madera_mono_routes;

	क्रम (i = 0; i < n_mono_routes; i++) अणु
		/* Default is 0 so noop with शेषs */
		अगर (pdata->out_mono[i]) अणु
			val = MADERA_OUT1_MONO;
			snd_soc_dapm_add_routes(dapm, &routes[i], 1);
		पूर्ण अन्यथा अणु
			val = 0;
		पूर्ण

		अगर (i >= n_real)
			जारी;

		regmap_update_bits(madera->regmap,
				   MADERA_OUTPUT_PATH_CONFIG_1L + (i * 8),
				   MADERA_OUT1_MONO, val);

		dev_dbg(madera->dev, "OUT%d mono=0x%x\n", i + 1, val);
	पूर्ण

	क्रम (i = 0; i < MADERA_MAX_PDM_SPK; i++) अणु
		dev_dbg(madera->dev, "PDM%d fmt=0x%x mute=0x%x\n", i + 1,
			pdata->pdm_fmt[i], pdata->pdm_mute[i]);

		अगर (pdata->pdm_mute[i])
			regmap_update_bits(madera->regmap,
					   MADERA_PDM_SPK1_CTRL_1 + (i * 2),
					   MADERA_SPK1_MUTE_ENDIAN_MASK |
					   MADERA_SPK1_MUTE_SEQ1_MASK,
					   pdata->pdm_mute[i]);

		अगर (pdata->pdm_fmt[i])
			regmap_update_bits(madera->regmap,
					   MADERA_PDM_SPK1_CTRL_2 + (i * 2),
					   MADERA_SPK1_FMT_MASK,
					   pdata->pdm_fmt[i]);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(madera_init_outमाला_दो);

पूर्णांक madera_init_bus_error_irq(काष्ठा madera_priv *priv, पूर्णांक dsp_num,
			      irq_handler_t handler)
अणु
	काष्ठा madera *madera = priv->madera;
	पूर्णांक ret;

	ret = madera_request_irq(madera,
				 madera_dsp_bus_error_irqs[dsp_num],
				 "ADSP2 bus error",
				 handler,
				 &priv->adsp[dsp_num]);
	अगर (ret)
		dev_err(madera->dev,
			"Failed to request DSP Lock region IRQ: %d\n", ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(madera_init_bus_error_irq);

व्योम madera_मुक्त_bus_error_irq(काष्ठा madera_priv *priv, पूर्णांक dsp_num)
अणु
	काष्ठा madera *madera = priv->madera;

	madera_मुक्त_irq(madera,
			madera_dsp_bus_error_irqs[dsp_num],
			&priv->adsp[dsp_num]);
पूर्ण
EXPORT_SYMBOL_GPL(madera_मुक्त_bus_error_irq);

स्थिर अक्षर * स्थिर madera_mixer_texts[] = अणु
	"None",
	"Tone Generator 1",
	"Tone Generator 2",
	"Haptics",
	"AEC1",
	"AEC2",
	"Mic Mute Mixer",
	"Noise Generator",
	"IN1L",
	"IN1R",
	"IN2L",
	"IN2R",
	"IN3L",
	"IN3R",
	"IN4L",
	"IN4R",
	"IN5L",
	"IN5R",
	"IN6L",
	"IN6R",
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
	"AIF2RX3",
	"AIF2RX4",
	"AIF2RX5",
	"AIF2RX6",
	"AIF2RX7",
	"AIF2RX8",
	"AIF3RX1",
	"AIF3RX2",
	"AIF3RX3",
	"AIF3RX4",
	"AIF4RX1",
	"AIF4RX2",
	"SLIMRX1",
	"SLIMRX2",
	"SLIMRX3",
	"SLIMRX4",
	"SLIMRX5",
	"SLIMRX6",
	"SLIMRX7",
	"SLIMRX8",
	"EQ1",
	"EQ2",
	"EQ3",
	"EQ4",
	"DRC1L",
	"DRC1R",
	"DRC2L",
	"DRC2R",
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
	"DSP4.1",
	"DSP4.2",
	"DSP4.3",
	"DSP4.4",
	"DSP4.5",
	"DSP4.6",
	"DSP5.1",
	"DSP5.2",
	"DSP5.3",
	"DSP5.4",
	"DSP5.5",
	"DSP5.6",
	"DSP6.1",
	"DSP6.2",
	"DSP6.3",
	"DSP6.4",
	"DSP6.5",
	"DSP6.6",
	"DSP7.1",
	"DSP7.2",
	"DSP7.3",
	"DSP7.4",
	"DSP7.5",
	"DSP7.6",
	"ASRC1IN1L",
	"ASRC1IN1R",
	"ASRC1IN2L",
	"ASRC1IN2R",
	"ASRC2IN1L",
	"ASRC2IN1R",
	"ASRC2IN2L",
	"ASRC2IN2R",
	"ISRC1INT1",
	"ISRC1INT2",
	"ISRC1INT3",
	"ISRC1INT4",
	"ISRC1DEC1",
	"ISRC1DEC2",
	"ISRC1DEC3",
	"ISRC1DEC4",
	"ISRC2INT1",
	"ISRC2INT2",
	"ISRC2INT3",
	"ISRC2INT4",
	"ISRC2DEC1",
	"ISRC2DEC2",
	"ISRC2DEC3",
	"ISRC2DEC4",
	"ISRC3INT1",
	"ISRC3INT2",
	"ISRC3INT3",
	"ISRC3INT4",
	"ISRC3DEC1",
	"ISRC3DEC2",
	"ISRC3DEC3",
	"ISRC3DEC4",
	"ISRC4INT1",
	"ISRC4INT2",
	"ISRC4DEC1",
	"ISRC4DEC2",
	"DFC1",
	"DFC2",
	"DFC3",
	"DFC4",
	"DFC5",
	"DFC6",
	"DFC7",
	"DFC8",
पूर्ण;
EXPORT_SYMBOL_GPL(madera_mixer_texts);

स्थिर अचिन्हित पूर्णांक madera_mixer_values[] = अणु
	0x00,	/* None */
	0x04,	/* Tone Generator 1 */
	0x05,	/* Tone Generator 2 */
	0x06,	/* Haptics */
	0x08,	/* AEC */
	0x09,	/* AEC2 */
	0x0c,	/* Noise mixer */
	0x0d,	/* Comक्रमt noise */
	0x10,	/* IN1L */
	0x11,
	0x12,
	0x13,
	0x14,
	0x15,
	0x16,
	0x17,
	0x18,
	0x19,
	0x1A,
	0x1B,
	0x20,	/* AIF1RX1 */
	0x21,
	0x22,
	0x23,
	0x24,
	0x25,
	0x26,
	0x27,
	0x28,	/* AIF2RX1 */
	0x29,
	0x2a,
	0x2b,
	0x2c,
	0x2d,
	0x2e,
	0x2f,
	0x30,	/* AIF3RX1 */
	0x31,
	0x32,
	0x33,
	0x34,	/* AIF4RX1 */
	0x35,
	0x38,	/* SLIMRX1 */
	0x39,
	0x3a,
	0x3b,
	0x3c,
	0x3d,
	0x3e,
	0x3f,
	0x50,	/* EQ1 */
	0x51,
	0x52,
	0x53,
	0x58,	/* DRC1L */
	0x59,
	0x5a,
	0x5b,
	0x60,	/* LHPF1 */
	0x61,
	0x62,
	0x63,
	0x68,	/* DSP1.1 */
	0x69,
	0x6a,
	0x6b,
	0x6c,
	0x6d,
	0x70,	/* DSP2.1 */
	0x71,
	0x72,
	0x73,
	0x74,
	0x75,
	0x78,	/* DSP3.1 */
	0x79,
	0x7a,
	0x7b,
	0x7c,
	0x7d,
	0x80,	/* DSP4.1 */
	0x81,
	0x82,
	0x83,
	0x84,
	0x85,
	0x88,	/* DSP5.1 */
	0x89,
	0x8a,
	0x8b,
	0x8c,
	0x8d,
	0xc0,	/* DSP6.1 */
	0xc1,
	0xc2,
	0xc3,
	0xc4,
	0xc5,
	0xc8,	/* DSP7.1 */
	0xc9,
	0xca,
	0xcb,
	0xcc,
	0xcd,
	0x90,	/* ASRC1IN1L */
	0x91,
	0x92,
	0x93,
	0x94,	/* ASRC2IN1L */
	0x95,
	0x96,
	0x97,
	0xa0,	/* ISRC1INT1 */
	0xa1,
	0xa2,
	0xa3,
	0xa4,	/* ISRC1DEC1 */
	0xa5,
	0xa6,
	0xa7,
	0xa8,	/* ISRC2DEC1 */
	0xa9,
	0xaa,
	0xab,
	0xac,	/* ISRC2INT1 */
	0xad,
	0xae,
	0xaf,
	0xb0,	/* ISRC3DEC1 */
	0xb1,
	0xb2,
	0xb3,
	0xb4,	/* ISRC3INT1 */
	0xb5,
	0xb6,
	0xb7,
	0xb8,	/* ISRC4INT1 */
	0xb9,
	0xbc,	/* ISRC4DEC1 */
	0xbd,
	0xf8,	/* DFC1 */
	0xf9,
	0xfa,
	0xfb,
	0xfc,
	0xfd,
	0xfe,
	0xff,	/* DFC8 */
पूर्ण;
EXPORT_SYMBOL_GPL(madera_mixer_values);

स्थिर DECLARE_TLV_DB_SCALE(madera_ana_tlv, 0, 100, 0);
EXPORT_SYMBOL_GPL(madera_ana_tlv);

स्थिर DECLARE_TLV_DB_SCALE(madera_eq_tlv, -1200, 100, 0);
EXPORT_SYMBOL_GPL(madera_eq_tlv);

स्थिर DECLARE_TLV_DB_SCALE(madera_digital_tlv, -6400, 50, 0);
EXPORT_SYMBOL_GPL(madera_digital_tlv);

स्थिर DECLARE_TLV_DB_SCALE(madera_noise_tlv, -13200, 600, 0);
EXPORT_SYMBOL_GPL(madera_noise_tlv);

स्थिर DECLARE_TLV_DB_SCALE(madera_ng_tlv, -12000, 600, 0);
EXPORT_SYMBOL_GPL(madera_ng_tlv);

स्थिर DECLARE_TLV_DB_SCALE(madera_mixer_tlv, -3200, 100, 0);
EXPORT_SYMBOL_GPL(madera_mixer_tlv);

स्थिर अक्षर * स्थिर madera_rate_text[MADERA_RATE_ENUM_SIZE] = अणु
	"SYNCCLK rate 1", "SYNCCLK rate 2", "SYNCCLK rate 3",
	"ASYNCCLK rate 1", "ASYNCCLK rate 2",
पूर्ण;
EXPORT_SYMBOL_GPL(madera_rate_text);

स्थिर अचिन्हित पूर्णांक madera_rate_val[MADERA_RATE_ENUM_SIZE] = अणु
	0x0, 0x1, 0x2, 0x8, 0x9,
पूर्ण;
EXPORT_SYMBOL_GPL(madera_rate_val);

अटल स्थिर अक्षर * स्थिर madera_dfc_width_text[MADERA_DFC_WIDTH_ENUM_SIZE] = अणु
	"8 bit", "16 bit", "20 bit", "24 bit", "32 bit",
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक madera_dfc_width_val[MADERA_DFC_WIDTH_ENUM_SIZE] = अणु
	7, 15, 19, 23, 31,
पूर्ण;

अटल स्थिर अक्षर * स्थिर madera_dfc_type_text[MADERA_DFC_TYPE_ENUM_SIZE] = अणु
	"Fixed", "Unsigned Fixed", "Single Precision Floating",
	"Half Precision Floating", "Arm Alternative Floating",
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक madera_dfc_type_val[MADERA_DFC_TYPE_ENUM_SIZE] = अणु
	0, 1, 2, 4, 5,
पूर्ण;

स्थिर काष्ठा soc_क्रमागत madera_dfc_width[] = अणु
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC1_RX,
			      MADERA_DFC1_RX_DATA_WIDTH_SHIFT,
			      MADERA_DFC1_RX_DATA_WIDTH_MASK >>
			      MADERA_DFC1_RX_DATA_WIDTH_SHIFT,
			      ARRAY_SIZE(madera_dfc_width_text),
			      madera_dfc_width_text,
			      madera_dfc_width_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC1_TX,
			      MADERA_DFC1_TX_DATA_WIDTH_SHIFT,
			      MADERA_DFC1_TX_DATA_WIDTH_MASK >>
			      MADERA_DFC1_TX_DATA_WIDTH_SHIFT,
			      ARRAY_SIZE(madera_dfc_width_text),
			      madera_dfc_width_text,
			      madera_dfc_width_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC2_RX,
			      MADERA_DFC1_RX_DATA_WIDTH_SHIFT,
			      MADERA_DFC1_RX_DATA_WIDTH_MASK >>
			      MADERA_DFC1_RX_DATA_WIDTH_SHIFT,
			      ARRAY_SIZE(madera_dfc_width_text),
			      madera_dfc_width_text,
			      madera_dfc_width_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC2_TX,
			      MADERA_DFC1_TX_DATA_WIDTH_SHIFT,
			      MADERA_DFC1_TX_DATA_WIDTH_MASK >>
			      MADERA_DFC1_TX_DATA_WIDTH_SHIFT,
			      ARRAY_SIZE(madera_dfc_width_text),
			      madera_dfc_width_text,
			      madera_dfc_width_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC3_RX,
			      MADERA_DFC1_RX_DATA_WIDTH_SHIFT,
			      MADERA_DFC1_RX_DATA_WIDTH_MASK >>
			      MADERA_DFC1_RX_DATA_WIDTH_SHIFT,
			      ARRAY_SIZE(madera_dfc_width_text),
			      madera_dfc_width_text,
			      madera_dfc_width_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC3_TX,
			      MADERA_DFC1_TX_DATA_WIDTH_SHIFT,
			      MADERA_DFC1_TX_DATA_WIDTH_MASK >>
			      MADERA_DFC1_TX_DATA_WIDTH_SHIFT,
			      ARRAY_SIZE(madera_dfc_width_text),
			      madera_dfc_width_text,
			      madera_dfc_width_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC4_RX,
			      MADERA_DFC1_RX_DATA_WIDTH_SHIFT,
			      MADERA_DFC1_RX_DATA_WIDTH_MASK >>
			      MADERA_DFC1_RX_DATA_WIDTH_SHIFT,
			      ARRAY_SIZE(madera_dfc_width_text),
			      madera_dfc_width_text,
			      madera_dfc_width_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC4_TX,
			      MADERA_DFC1_TX_DATA_WIDTH_SHIFT,
			      MADERA_DFC1_TX_DATA_WIDTH_MASK >>
			      MADERA_DFC1_TX_DATA_WIDTH_SHIFT,
			      ARRAY_SIZE(madera_dfc_width_text),
			      madera_dfc_width_text,
			      madera_dfc_width_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC5_RX,
			      MADERA_DFC1_RX_DATA_WIDTH_SHIFT,
			      MADERA_DFC1_RX_DATA_WIDTH_MASK >>
			      MADERA_DFC1_RX_DATA_WIDTH_SHIFT,
			      ARRAY_SIZE(madera_dfc_width_text),
			      madera_dfc_width_text,
			      madera_dfc_width_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC5_TX,
			      MADERA_DFC1_TX_DATA_WIDTH_SHIFT,
			      MADERA_DFC1_TX_DATA_WIDTH_MASK >>
			      MADERA_DFC1_TX_DATA_WIDTH_SHIFT,
			      ARRAY_SIZE(madera_dfc_width_text),
			      madera_dfc_width_text,
			      madera_dfc_width_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC6_RX,
			      MADERA_DFC1_RX_DATA_WIDTH_SHIFT,
			      MADERA_DFC1_RX_DATA_WIDTH_MASK >>
			      MADERA_DFC1_RX_DATA_WIDTH_SHIFT,
			      ARRAY_SIZE(madera_dfc_width_text),
			      madera_dfc_width_text,
			      madera_dfc_width_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC6_TX,
			      MADERA_DFC1_TX_DATA_WIDTH_SHIFT,
			      MADERA_DFC1_TX_DATA_WIDTH_MASK >>
			      MADERA_DFC1_TX_DATA_WIDTH_SHIFT,
			      ARRAY_SIZE(madera_dfc_width_text),
			      madera_dfc_width_text,
			      madera_dfc_width_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC7_RX,
			      MADERA_DFC1_RX_DATA_WIDTH_SHIFT,
			      MADERA_DFC1_RX_DATA_WIDTH_MASK >>
			      MADERA_DFC1_RX_DATA_WIDTH_SHIFT,
			      ARRAY_SIZE(madera_dfc_width_text),
			      madera_dfc_width_text,
			      madera_dfc_width_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC7_TX,
			      MADERA_DFC1_TX_DATA_WIDTH_SHIFT,
			      MADERA_DFC1_TX_DATA_WIDTH_MASK >>
			      MADERA_DFC1_TX_DATA_WIDTH_SHIFT,
			      ARRAY_SIZE(madera_dfc_width_text),
			      madera_dfc_width_text,
			      madera_dfc_width_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC8_RX,
			      MADERA_DFC1_RX_DATA_WIDTH_SHIFT,
			      MADERA_DFC1_RX_DATA_WIDTH_MASK >>
			      MADERA_DFC1_RX_DATA_WIDTH_SHIFT,
			      ARRAY_SIZE(madera_dfc_width_text),
			      madera_dfc_width_text,
			      madera_dfc_width_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC8_TX,
			      MADERA_DFC1_TX_DATA_WIDTH_SHIFT,
			      MADERA_DFC1_TX_DATA_WIDTH_MASK >>
			      MADERA_DFC1_TX_DATA_WIDTH_SHIFT,
			      ARRAY_SIZE(madera_dfc_width_text),
			      madera_dfc_width_text,
			      madera_dfc_width_val),
पूर्ण;
EXPORT_SYMBOL_GPL(madera_dfc_width);

स्थिर काष्ठा soc_क्रमागत madera_dfc_type[] = अणु
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC1_RX,
			      MADERA_DFC1_RX_DATA_TYPE_SHIFT,
			      MADERA_DFC1_RX_DATA_TYPE_MASK >>
			      MADERA_DFC1_RX_DATA_TYPE_SHIFT,
			      ARRAY_SIZE(madera_dfc_type_text),
			      madera_dfc_type_text,
			      madera_dfc_type_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC1_TX,
			      MADERA_DFC1_TX_DATA_TYPE_SHIFT,
			      MADERA_DFC1_TX_DATA_TYPE_MASK >>
			      MADERA_DFC1_TX_DATA_TYPE_SHIFT,
			      ARRAY_SIZE(madera_dfc_type_text),
			      madera_dfc_type_text,
			      madera_dfc_type_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC2_RX,
			      MADERA_DFC1_RX_DATA_TYPE_SHIFT,
			      MADERA_DFC1_RX_DATA_TYPE_MASK >>
			      MADERA_DFC1_RX_DATA_TYPE_SHIFT,
			      ARRAY_SIZE(madera_dfc_type_text),
			      madera_dfc_type_text,
			      madera_dfc_type_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC2_TX,
			      MADERA_DFC1_TX_DATA_TYPE_SHIFT,
			      MADERA_DFC1_TX_DATA_TYPE_MASK >>
			      MADERA_DFC1_TX_DATA_TYPE_SHIFT,
			      ARRAY_SIZE(madera_dfc_type_text),
			      madera_dfc_type_text,
			      madera_dfc_type_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC3_RX,
			      MADERA_DFC1_RX_DATA_TYPE_SHIFT,
			      MADERA_DFC1_RX_DATA_TYPE_MASK >>
			      MADERA_DFC1_RX_DATA_TYPE_SHIFT,
			      ARRAY_SIZE(madera_dfc_type_text),
			      madera_dfc_type_text,
			      madera_dfc_type_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC3_TX,
			      MADERA_DFC1_TX_DATA_TYPE_SHIFT,
			      MADERA_DFC1_TX_DATA_TYPE_MASK >>
			      MADERA_DFC1_TX_DATA_TYPE_SHIFT,
			      ARRAY_SIZE(madera_dfc_type_text),
			      madera_dfc_type_text,
			      madera_dfc_type_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC4_RX,
			      MADERA_DFC1_RX_DATA_TYPE_SHIFT,
			      MADERA_DFC1_RX_DATA_TYPE_MASK >>
			      MADERA_DFC1_RX_DATA_TYPE_SHIFT,
			      ARRAY_SIZE(madera_dfc_type_text),
			      madera_dfc_type_text,
			      madera_dfc_type_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC4_TX,
			      MADERA_DFC1_TX_DATA_TYPE_SHIFT,
			      MADERA_DFC1_TX_DATA_TYPE_MASK >>
			      MADERA_DFC1_TX_DATA_TYPE_SHIFT,
			      ARRAY_SIZE(madera_dfc_type_text),
			      madera_dfc_type_text,
			      madera_dfc_type_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC5_RX,
			      MADERA_DFC1_RX_DATA_TYPE_SHIFT,
			      MADERA_DFC1_RX_DATA_TYPE_MASK >>
			      MADERA_DFC1_RX_DATA_TYPE_SHIFT,
			      ARRAY_SIZE(madera_dfc_type_text),
			      madera_dfc_type_text,
			      madera_dfc_type_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC5_TX,
			      MADERA_DFC1_TX_DATA_TYPE_SHIFT,
			      MADERA_DFC1_TX_DATA_TYPE_MASK >>
			      MADERA_DFC1_TX_DATA_TYPE_SHIFT,
			      ARRAY_SIZE(madera_dfc_type_text),
			      madera_dfc_type_text,
			      madera_dfc_type_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC6_RX,
			      MADERA_DFC1_RX_DATA_TYPE_SHIFT,
			      MADERA_DFC1_RX_DATA_TYPE_MASK >>
			      MADERA_DFC1_RX_DATA_TYPE_SHIFT,
			      ARRAY_SIZE(madera_dfc_type_text),
			      madera_dfc_type_text,
			      madera_dfc_type_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC6_TX,
			      MADERA_DFC1_TX_DATA_TYPE_SHIFT,
			      MADERA_DFC1_TX_DATA_TYPE_MASK >>
			      MADERA_DFC1_TX_DATA_TYPE_SHIFT,
			      ARRAY_SIZE(madera_dfc_type_text),
			      madera_dfc_type_text,
			      madera_dfc_type_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC7_RX,
			      MADERA_DFC1_RX_DATA_TYPE_SHIFT,
			      MADERA_DFC1_RX_DATA_TYPE_MASK >>
			      MADERA_DFC1_RX_DATA_TYPE_SHIFT,
			      ARRAY_SIZE(madera_dfc_type_text),
			      madera_dfc_type_text,
			      madera_dfc_type_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC7_TX,
			      MADERA_DFC1_TX_DATA_TYPE_SHIFT,
			      MADERA_DFC1_TX_DATA_TYPE_MASK >>
			      MADERA_DFC1_TX_DATA_TYPE_SHIFT,
			      ARRAY_SIZE(madera_dfc_type_text),
			      madera_dfc_type_text,
			      madera_dfc_type_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC8_RX,
			      MADERA_DFC1_RX_DATA_TYPE_SHIFT,
			      MADERA_DFC1_RX_DATA_TYPE_MASK >>
			      MADERA_DFC1_RX_DATA_TYPE_SHIFT,
			      ARRAY_SIZE(madera_dfc_type_text),
			      madera_dfc_type_text,
			      madera_dfc_type_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DFC8_TX,
			      MADERA_DFC1_TX_DATA_TYPE_SHIFT,
			      MADERA_DFC1_TX_DATA_TYPE_MASK >>
			      MADERA_DFC1_TX_DATA_TYPE_SHIFT,
			      ARRAY_SIZE(madera_dfc_type_text),
			      madera_dfc_type_text,
			      madera_dfc_type_val),
पूर्ण;
EXPORT_SYMBOL_GPL(madera_dfc_type);

स्थिर काष्ठा soc_क्रमागत madera_isrc_fsh[] = अणु
	SOC_VALUE_ENUM_SINGLE(MADERA_ISRC_1_CTRL_1,
			      MADERA_ISRC1_FSH_SHIFT, 0xf,
			      MADERA_RATE_ENUM_SIZE,
			      madera_rate_text, madera_rate_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_ISRC_2_CTRL_1,
			      MADERA_ISRC2_FSH_SHIFT, 0xf,
			      MADERA_RATE_ENUM_SIZE,
			      madera_rate_text, madera_rate_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_ISRC_3_CTRL_1,
			      MADERA_ISRC3_FSH_SHIFT, 0xf,
			      MADERA_RATE_ENUM_SIZE,
			      madera_rate_text, madera_rate_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_ISRC_4_CTRL_1,
			      MADERA_ISRC4_FSH_SHIFT, 0xf,
			      MADERA_RATE_ENUM_SIZE,
			      madera_rate_text, madera_rate_val),
पूर्ण;
EXPORT_SYMBOL_GPL(madera_isrc_fsh);

स्थिर काष्ठा soc_क्रमागत madera_isrc_fsl[] = अणु
	SOC_VALUE_ENUM_SINGLE(MADERA_ISRC_1_CTRL_2,
			      MADERA_ISRC1_FSL_SHIFT, 0xf,
			      MADERA_RATE_ENUM_SIZE,
			      madera_rate_text, madera_rate_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_ISRC_2_CTRL_2,
			      MADERA_ISRC2_FSL_SHIFT, 0xf,
			      MADERA_RATE_ENUM_SIZE,
			      madera_rate_text, madera_rate_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_ISRC_3_CTRL_2,
			      MADERA_ISRC3_FSL_SHIFT, 0xf,
			      MADERA_RATE_ENUM_SIZE,
			      madera_rate_text, madera_rate_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_ISRC_4_CTRL_2,
			      MADERA_ISRC4_FSL_SHIFT, 0xf,
			      MADERA_RATE_ENUM_SIZE,
			      madera_rate_text, madera_rate_val),
पूर्ण;
EXPORT_SYMBOL_GPL(madera_isrc_fsl);

स्थिर काष्ठा soc_क्रमागत madera_asrc1_rate[] = अणु
	SOC_VALUE_ENUM_SINGLE(MADERA_ASRC1_RATE1,
			      MADERA_ASRC1_RATE1_SHIFT, 0xf,
			      MADERA_SYNC_RATE_ENUM_SIZE,
			      madera_rate_text, madera_rate_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_ASRC1_RATE2,
			      MADERA_ASRC1_RATE1_SHIFT, 0xf,
			      MADERA_ASYNC_RATE_ENUM_SIZE,
			      madera_rate_text + MADERA_SYNC_RATE_ENUM_SIZE,
			      madera_rate_val + MADERA_SYNC_RATE_ENUM_SIZE),
पूर्ण;
EXPORT_SYMBOL_GPL(madera_asrc1_rate);

स्थिर काष्ठा soc_क्रमागत madera_asrc1_bidir_rate[] = अणु
	SOC_VALUE_ENUM_SINGLE(MADERA_ASRC1_RATE1,
			      MADERA_ASRC1_RATE1_SHIFT, 0xf,
			      MADERA_RATE_ENUM_SIZE,
			      madera_rate_text, madera_rate_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_ASRC1_RATE2,
			      MADERA_ASRC1_RATE2_SHIFT, 0xf,
			      MADERA_RATE_ENUM_SIZE,
			      madera_rate_text, madera_rate_val),
पूर्ण;
EXPORT_SYMBOL_GPL(madera_asrc1_bidir_rate);

स्थिर काष्ठा soc_क्रमागत madera_asrc2_rate[] = अणु
	SOC_VALUE_ENUM_SINGLE(MADERA_ASRC2_RATE1,
			      MADERA_ASRC2_RATE1_SHIFT, 0xf,
			      MADERA_SYNC_RATE_ENUM_SIZE,
			      madera_rate_text, madera_rate_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_ASRC2_RATE2,
			      MADERA_ASRC2_RATE2_SHIFT, 0xf,
			      MADERA_ASYNC_RATE_ENUM_SIZE,
			      madera_rate_text + MADERA_SYNC_RATE_ENUM_SIZE,
			      madera_rate_val + MADERA_SYNC_RATE_ENUM_SIZE),
पूर्ण;
EXPORT_SYMBOL_GPL(madera_asrc2_rate);

अटल स्थिर अक्षर * स्थिर madera_vol_ramp_text[] = अणु
	"0ms/6dB", "0.5ms/6dB", "1ms/6dB", "2ms/6dB", "4ms/6dB", "8ms/6dB",
	"15ms/6dB", "30ms/6dB",
पूर्ण;

SOC_ENUM_SINGLE_DECL(madera_in_vd_ramp,
		     MADERA_INPUT_VOLUME_RAMP,
		     MADERA_IN_VD_RAMP_SHIFT,
		     madera_vol_ramp_text);
EXPORT_SYMBOL_GPL(madera_in_vd_ramp);

SOC_ENUM_SINGLE_DECL(madera_in_vi_ramp,
		     MADERA_INPUT_VOLUME_RAMP,
		     MADERA_IN_VI_RAMP_SHIFT,
		     madera_vol_ramp_text);
EXPORT_SYMBOL_GPL(madera_in_vi_ramp);

SOC_ENUM_SINGLE_DECL(madera_out_vd_ramp,
		     MADERA_OUTPUT_VOLUME_RAMP,
		     MADERA_OUT_VD_RAMP_SHIFT,
		     madera_vol_ramp_text);
EXPORT_SYMBOL_GPL(madera_out_vd_ramp);

SOC_ENUM_SINGLE_DECL(madera_out_vi_ramp,
		     MADERA_OUTPUT_VOLUME_RAMP,
		     MADERA_OUT_VI_RAMP_SHIFT,
		     madera_vol_ramp_text);
EXPORT_SYMBOL_GPL(madera_out_vi_ramp);

अटल स्थिर अक्षर * स्थिर madera_lhpf_mode_text[] = अणु
	"Low-pass", "High-pass"
पूर्ण;

SOC_ENUM_SINGLE_DECL(madera_lhpf1_mode,
		     MADERA_HPLPF1_1,
		     MADERA_LHPF1_MODE_SHIFT,
		     madera_lhpf_mode_text);
EXPORT_SYMBOL_GPL(madera_lhpf1_mode);

SOC_ENUM_SINGLE_DECL(madera_lhpf2_mode,
		     MADERA_HPLPF2_1,
		     MADERA_LHPF2_MODE_SHIFT,
		     madera_lhpf_mode_text);
EXPORT_SYMBOL_GPL(madera_lhpf2_mode);

SOC_ENUM_SINGLE_DECL(madera_lhpf3_mode,
		     MADERA_HPLPF3_1,
		     MADERA_LHPF3_MODE_SHIFT,
		     madera_lhpf_mode_text);
EXPORT_SYMBOL_GPL(madera_lhpf3_mode);

SOC_ENUM_SINGLE_DECL(madera_lhpf4_mode,
		     MADERA_HPLPF4_1,
		     MADERA_LHPF4_MODE_SHIFT,
		     madera_lhpf_mode_text);
EXPORT_SYMBOL_GPL(madera_lhpf4_mode);

अटल स्थिर अक्षर * स्थिर madera_ng_hold_text[] = अणु
	"30ms", "120ms", "250ms", "500ms",
पूर्ण;

SOC_ENUM_SINGLE_DECL(madera_ng_hold,
		     MADERA_NOISE_GATE_CONTROL,
		     MADERA_NGATE_HOLD_SHIFT,
		     madera_ng_hold_text);
EXPORT_SYMBOL_GPL(madera_ng_hold);

अटल स्थिर अक्षर * स्थिर madera_in_hpf_cut_text[] = अणु
	"2.5Hz", "5Hz", "10Hz", "20Hz", "40Hz"
पूर्ण;

SOC_ENUM_SINGLE_DECL(madera_in_hpf_cut_क्रमागत,
		     MADERA_HPF_CONTROL,
		     MADERA_IN_HPF_CUT_SHIFT,
		     madera_in_hpf_cut_text);
EXPORT_SYMBOL_GPL(madera_in_hpf_cut_क्रमागत);

अटल स्थिर अक्षर * स्थिर madera_in_dmic_osr_text[MADERA_OSR_ENUM_SIZE] = अणु
	"384kHz", "768kHz", "1.536MHz", "3.072MHz", "6.144MHz",
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक madera_in_dmic_osr_val[MADERA_OSR_ENUM_SIZE] = अणु
	2, 3, 4, 5, 6,
पूर्ण;

स्थिर काष्ठा soc_क्रमागत madera_in_dmic_osr[] = अणु
	SOC_VALUE_ENUM_SINGLE(MADERA_DMIC1L_CONTROL, MADERA_IN1_OSR_SHIFT,
			      0x7, MADERA_OSR_ENUM_SIZE,
			      madera_in_dmic_osr_text, madera_in_dmic_osr_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DMIC2L_CONTROL, MADERA_IN2_OSR_SHIFT,
			      0x7, MADERA_OSR_ENUM_SIZE,
			      madera_in_dmic_osr_text, madera_in_dmic_osr_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DMIC3L_CONTROL, MADERA_IN3_OSR_SHIFT,
			      0x7, MADERA_OSR_ENUM_SIZE,
			      madera_in_dmic_osr_text, madera_in_dmic_osr_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DMIC4L_CONTROL, MADERA_IN4_OSR_SHIFT,
			      0x7, MADERA_OSR_ENUM_SIZE,
			      madera_in_dmic_osr_text, madera_in_dmic_osr_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DMIC5L_CONTROL, MADERA_IN5_OSR_SHIFT,
			      0x7, MADERA_OSR_ENUM_SIZE,
			      madera_in_dmic_osr_text, madera_in_dmic_osr_val),
	SOC_VALUE_ENUM_SINGLE(MADERA_DMIC6L_CONTROL, MADERA_IN6_OSR_SHIFT,
			      0x7, MADERA_OSR_ENUM_SIZE,
			      madera_in_dmic_osr_text, madera_in_dmic_osr_val),
पूर्ण;
EXPORT_SYMBOL_GPL(madera_in_dmic_osr);

अटल स्थिर अक्षर * स्थिर madera_anc_input_src_text[] = अणु
	"None", "IN1", "IN2", "IN3", "IN4", "IN5", "IN6",
पूर्ण;

अटल स्थिर अक्षर * स्थिर madera_anc_channel_src_text[] = अणु
	"None", "Left", "Right", "Combine",
पूर्ण;

स्थिर काष्ठा soc_क्रमागत madera_anc_input_src[] = अणु
	SOC_ENUM_SINGLE(MADERA_ANC_SRC,
			MADERA_IN_RXANCL_SEL_SHIFT,
			ARRAY_SIZE(madera_anc_input_src_text),
			madera_anc_input_src_text),
	SOC_ENUM_SINGLE(MADERA_FCL_ADC_REFORMATTER_CONTROL,
			MADERA_FCL_MIC_MODE_SEL_SHIFT,
			ARRAY_SIZE(madera_anc_channel_src_text),
			madera_anc_channel_src_text),
	SOC_ENUM_SINGLE(MADERA_ANC_SRC,
			MADERA_IN_RXANCR_SEL_SHIFT,
			ARRAY_SIZE(madera_anc_input_src_text),
			madera_anc_input_src_text),
	SOC_ENUM_SINGLE(MADERA_FCR_ADC_REFORMATTER_CONTROL,
			MADERA_FCR_MIC_MODE_SEL_SHIFT,
			ARRAY_SIZE(madera_anc_channel_src_text),
			madera_anc_channel_src_text),
पूर्ण;
EXPORT_SYMBOL_GPL(madera_anc_input_src);

अटल स्थिर अक्षर * स्थिर madera_anc_ng_texts[] = अणु
	"None", "Internal", "External",
पूर्ण;

SOC_ENUM_SINGLE_DECL(madera_anc_ng_क्रमागत, SND_SOC_NOPM, 0, madera_anc_ng_texts);
EXPORT_SYMBOL_GPL(madera_anc_ng_क्रमागत);

अटल स्थिर अक्षर * स्थिर madera_out_anc_src_text[] = अणु
	"None", "RXANCL", "RXANCR",
पूर्ण;

स्थिर काष्ठा soc_क्रमागत madera_output_anc_src[] = अणु
	SOC_ENUM_SINGLE(MADERA_OUTPUT_PATH_CONFIG_1L,
			MADERA_OUT1L_ANC_SRC_SHIFT,
			ARRAY_SIZE(madera_out_anc_src_text),
			madera_out_anc_src_text),
	SOC_ENUM_SINGLE(MADERA_OUTPUT_PATH_CONFIG_1R,
			MADERA_OUT1R_ANC_SRC_SHIFT,
			ARRAY_SIZE(madera_out_anc_src_text),
			madera_out_anc_src_text),
	SOC_ENUM_SINGLE(MADERA_OUTPUT_PATH_CONFIG_2L,
			MADERA_OUT2L_ANC_SRC_SHIFT,
			ARRAY_SIZE(madera_out_anc_src_text),
			madera_out_anc_src_text),
	SOC_ENUM_SINGLE(MADERA_OUTPUT_PATH_CONFIG_2R,
			MADERA_OUT2R_ANC_SRC_SHIFT,
			ARRAY_SIZE(madera_out_anc_src_text),
			madera_out_anc_src_text),
	SOC_ENUM_SINGLE(MADERA_OUTPUT_PATH_CONFIG_3L,
			MADERA_OUT3L_ANC_SRC_SHIFT,
			ARRAY_SIZE(madera_out_anc_src_text),
			madera_out_anc_src_text),
	SOC_ENUM_SINGLE(MADERA_OUTPUT_PATH_CONFIG_3R,
			MADERA_OUT3R_ANC_SRC_SHIFT,
			ARRAY_SIZE(madera_out_anc_src_text),
			madera_out_anc_src_text),
	SOC_ENUM_SINGLE(MADERA_OUTPUT_PATH_CONFIG_4L,
			MADERA_OUT4L_ANC_SRC_SHIFT,
			ARRAY_SIZE(madera_out_anc_src_text),
			madera_out_anc_src_text),
	SOC_ENUM_SINGLE(MADERA_OUTPUT_PATH_CONFIG_4R,
			MADERA_OUT4R_ANC_SRC_SHIFT,
			ARRAY_SIZE(madera_out_anc_src_text),
			madera_out_anc_src_text),
	SOC_ENUM_SINGLE(MADERA_OUTPUT_PATH_CONFIG_5L,
			MADERA_OUT5L_ANC_SRC_SHIFT,
			ARRAY_SIZE(madera_out_anc_src_text),
			madera_out_anc_src_text),
	SOC_ENUM_SINGLE(MADERA_OUTPUT_PATH_CONFIG_5R,
			MADERA_OUT5R_ANC_SRC_SHIFT,
			ARRAY_SIZE(madera_out_anc_src_text),
			madera_out_anc_src_text),
	SOC_ENUM_SINGLE(MADERA_OUTPUT_PATH_CONFIG_6L,
			MADERA_OUT6L_ANC_SRC_SHIFT,
			ARRAY_SIZE(madera_out_anc_src_text),
			madera_out_anc_src_text),
	SOC_ENUM_SINGLE(MADERA_OUTPUT_PATH_CONFIG_6R,
			MADERA_OUT6R_ANC_SRC_SHIFT,
			ARRAY_SIZE(madera_out_anc_src_text),
			madera_out_anc_src_text),
पूर्ण;
EXPORT_SYMBOL_GPL(madera_output_anc_src);

पूर्णांक madera_dfc_put(काष्ठा snd_kcontrol *kcontrol,
		   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg = e->reg;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret = 0;

	reg = ((reg / 6) * 6) - 2;

	snd_soc_dapm_mutex_lock(dapm);

	val = snd_soc_component_पढ़ो(component, reg);
	अगर (val & MADERA_DFC1_ENA) अणु
		ret = -EBUSY;
		dev_err(component->dev, "Can't change mode on an active DFC\n");
		जाओ निकास;
	पूर्ण

	ret = snd_soc_put_क्रमागत_द्विगुन(kcontrol, ucontrol);
निकास:
	snd_soc_dapm_mutex_unlock(dapm);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(madera_dfc_put);

पूर्णांक madera_lp_mode_put(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	अचिन्हित पूर्णांक val, mask;
	पूर्णांक ret;

	snd_soc_dapm_mutex_lock(dapm);

	/* Cannot change lp mode on an active input */
	val = snd_soc_component_पढ़ो(component, MADERA_INPUT_ENABLES);
	mask = (mc->reg - MADERA_ADC_DIGITAL_VOLUME_1L) / 4;
	mask ^= 0x1; /* Flip bottom bit क्रम channel order */

	अगर (val & (1 << mask)) अणु
		ret = -EBUSY;
		dev_err(component->dev,
			"Can't change lp mode on an active input\n");
		जाओ निकास;
	पूर्ण

	ret = snd_soc_put_volsw(kcontrol, ucontrol);

निकास:
	snd_soc_dapm_mutex_unlock(dapm);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(madera_lp_mode_put);

स्थिर काष्ठा snd_kcontrol_new madera_dsp_trigger_output_mux[] = अणु
	SOC_DAPM_SINGLE("Switch", SND_SOC_NOPM, 0, 1, 0),
	SOC_DAPM_SINGLE("Switch", SND_SOC_NOPM, 0, 1, 0),
	SOC_DAPM_SINGLE("Switch", SND_SOC_NOPM, 0, 1, 0),
	SOC_DAPM_SINGLE("Switch", SND_SOC_NOPM, 0, 1, 0),
	SOC_DAPM_SINGLE("Switch", SND_SOC_NOPM, 0, 1, 0),
	SOC_DAPM_SINGLE("Switch", SND_SOC_NOPM, 0, 1, 0),
	SOC_DAPM_SINGLE("Switch", SND_SOC_NOPM, 0, 1, 0),
पूर्ण;
EXPORT_SYMBOL_GPL(madera_dsp_trigger_output_mux);

स्थिर काष्ठा snd_kcontrol_new madera_drc_activity_output_mux[] = अणु
	SOC_DAPM_SINGLE("Switch", SND_SOC_NOPM, 0, 1, 0),
	SOC_DAPM_SINGLE("Switch", SND_SOC_NOPM, 0, 1, 0),
पूर्ण;
EXPORT_SYMBOL_GPL(madera_drc_activity_output_mux);

अटल व्योम madera_in_set_vu(काष्ठा madera_priv *priv, bool enable)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक i, ret;

	अगर (enable)
		val = MADERA_IN_VU;
	अन्यथा
		val = 0;

	क्रम (i = 0; i < priv->num_inमाला_दो; i++) अणु
		ret = regmap_update_bits(priv->madera->regmap,
					 MADERA_ADC_DIGITAL_VOLUME_1L + (i * 4),
					 MADERA_IN_VU, val);
		अगर (ret)
			dev_warn(priv->madera->dev,
				 "Failed to modify VU bits: %d\n", ret);
	पूर्ण
पूर्ण

पूर्णांक madera_in_ev(काष्ठा snd_soc_dapm_widget *w, काष्ठा snd_kcontrol *kcontrol,
		 पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg, val;

	अगर (w->shअगरt % 2)
		reg = MADERA_ADC_DIGITAL_VOLUME_1L + ((w->shअगरt / 2) * 8);
	अन्यथा
		reg = MADERA_ADC_DIGITAL_VOLUME_1R + ((w->shअगरt / 2) * 8);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		priv->in_pending++;
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		priv->in_pending--;
		snd_soc_component_update_bits(component, reg,
					      MADERA_IN1L_MUTE, 0);

		/* If this is the last input pending then allow VU */
		अगर (priv->in_pending == 0) अणु
			usleep_range(1000, 3000);
			madera_in_set_vu(priv, true);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, reg,
					      MADERA_IN1L_MUTE | MADERA_IN_VU,
					      MADERA_IN1L_MUTE | MADERA_IN_VU);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* Disable volume updates अगर no inमाला_दो are enabled */
		val = snd_soc_component_पढ़ो(component, MADERA_INPUT_ENABLES);
		अगर (!val)
			madera_in_set_vu(priv, false);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(madera_in_ev);

पूर्णांक madera_out_ev(काष्ठा snd_soc_dapm_widget *w,
		  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा madera *madera = priv->madera;
	पूर्णांक out_up_delay;

	चयन (madera->type) अणु
	हाल CS47L90:
	हाल CS47L91:
	हाल CS42L92:
	हाल CS47L92:
	हाल CS47L93:
		out_up_delay = 6;
		अवरोध;
	शेष:
		out_up_delay = 17;
		अवरोध;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		चयन (w->shअगरt) अणु
		हाल MADERA_OUT1L_ENA_SHIFT:
		हाल MADERA_OUT1R_ENA_SHIFT:
		हाल MADERA_OUT2L_ENA_SHIFT:
		हाल MADERA_OUT2R_ENA_SHIFT:
		हाल MADERA_OUT3L_ENA_SHIFT:
		हाल MADERA_OUT3R_ENA_SHIFT:
			priv->out_up_pending++;
			priv->out_up_delay += out_up_delay;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMU:
		चयन (w->shअगरt) अणु
		हाल MADERA_OUT1L_ENA_SHIFT:
		हाल MADERA_OUT1R_ENA_SHIFT:
		हाल MADERA_OUT2L_ENA_SHIFT:
		हाल MADERA_OUT2R_ENA_SHIFT:
		हाल MADERA_OUT3L_ENA_SHIFT:
		हाल MADERA_OUT3R_ENA_SHIFT:
			priv->out_up_pending--;
			अगर (!priv->out_up_pending) अणु
				msleep(priv->out_up_delay);
				priv->out_up_delay = 0;
			पूर्ण
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		चयन (w->shअगरt) अणु
		हाल MADERA_OUT1L_ENA_SHIFT:
		हाल MADERA_OUT1R_ENA_SHIFT:
		हाल MADERA_OUT2L_ENA_SHIFT:
		हाल MADERA_OUT2R_ENA_SHIFT:
		हाल MADERA_OUT3L_ENA_SHIFT:
		हाल MADERA_OUT3R_ENA_SHIFT:
			priv->out_करोwn_pending++;
			priv->out_करोwn_delay++;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		चयन (w->shअगरt) अणु
		हाल MADERA_OUT1L_ENA_SHIFT:
		हाल MADERA_OUT1R_ENA_SHIFT:
		हाल MADERA_OUT2L_ENA_SHIFT:
		हाल MADERA_OUT2R_ENA_SHIFT:
		हाल MADERA_OUT3L_ENA_SHIFT:
		हाल MADERA_OUT3R_ENA_SHIFT:
			priv->out_करोwn_pending--;
			अगर (!priv->out_करोwn_pending) अणु
				msleep(priv->out_करोwn_delay);
				priv->out_करोwn_delay = 0;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(madera_out_ev);

पूर्णांक madera_hp_ev(काष्ठा snd_soc_dapm_widget *w,
		 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा madera *madera = priv->madera;
	अचिन्हित पूर्णांक mask = 1 << w->shअगरt;
	अचिन्हित पूर्णांक out_num = w->shअगरt / 2;
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक ep_sel = 0;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		val = mask;
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		val = 0;
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMU:
	हाल SND_SOC_DAPM_POST_PMD:
		वापस madera_out_ev(w, kcontrol, event);
	शेष:
		वापस 0;
	पूर्ण

	/* Store the desired state क्रम the HP outमाला_दो */
	madera->hp_ena &= ~mask;
	madera->hp_ena |= val;

	चयन (madera->type) अणु
	हाल CS42L92:
	हाल CS47L92:
	हाल CS47L93:
		अवरोध;
	शेष:
		/* अगर OUT1 is routed to EPOUT, ignore HP clamp and impedance */
		regmap_पढ़ो(madera->regmap, MADERA_OUTPUT_ENABLES_1, &ep_sel);
		ep_sel &= MADERA_EP_SEL_MASK;
		अवरोध;
	पूर्ण

	/* Force off अगर HPDET has disabled the clamp क्रम this output */
	अगर (!ep_sel &&
	    (!madera->out_clamp[out_num] || madera->out_लघुed[out_num]))
		val = 0;

	regmap_update_bits(madera->regmap, MADERA_OUTPUT_ENABLES_1, mask, val);

	वापस madera_out_ev(w, kcontrol, event);
पूर्ण
EXPORT_SYMBOL_GPL(madera_hp_ev);

पूर्णांक madera_anc_ev(काष्ठा snd_soc_dapm_widget *w, काष्ठा snd_kcontrol *kcontrol,
		  पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	अचिन्हित पूर्णांक val;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		val = 1 << w->shअगरt;
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		val = 1 << (w->shअगरt + 1);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	snd_soc_component_ग_लिखो(component, MADERA_CLOCK_CONTROL, val);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(madera_anc_ev);

अटल स्थिर अचिन्हित पूर्णांक madera_opclk_ref_48k_rates[] = अणु
	6144000,
	12288000,
	24576000,
	49152000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक madera_opclk_ref_44k1_rates[] = अणु
	5644800,
	11289600,
	22579200,
	45158400,
पूर्ण;

अटल पूर्णांक madera_set_opclk(काष्ठा snd_soc_component *component,
			    अचिन्हित पूर्णांक clk, अचिन्हित पूर्णांक freq)
अणु
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक mask = MADERA_OPCLK_DIV_MASK | MADERA_OPCLK_SEL_MASK;
	अचिन्हित पूर्णांक reg, val;
	स्थिर अचिन्हित पूर्णांक *rates;
	पूर्णांक ref, भाग, refclk;

	BUILD_BUG_ON(ARRAY_SIZE(madera_opclk_ref_48k_rates) !=
		     ARRAY_SIZE(madera_opclk_ref_44k1_rates));

	चयन (clk) अणु
	हाल MADERA_CLK_OPCLK:
		reg = MADERA_OUTPUT_SYSTEM_CLOCK;
		refclk = priv->sysclk;
		अवरोध;
	हाल MADERA_CLK_ASYNC_OPCLK:
		reg = MADERA_OUTPUT_ASYNC_CLOCK;
		refclk = priv->asyncclk;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (refclk % 4000)
		rates = madera_opclk_ref_44k1_rates;
	अन्यथा
		rates = madera_opclk_ref_48k_rates;

	क्रम (ref = 0; ref < ARRAY_SIZE(madera_opclk_ref_48k_rates); ++ref) अणु
		अगर (rates[ref] > refclk)
			जारी;

		भाग = 2;
		जबतक ((rates[ref] / भाग >= freq) && (भाग <= 30)) अणु
			अगर (rates[ref] / भाग == freq) अणु
				dev_dbg(component->dev, "Configured %dHz OPCLK\n",
					freq);

				val = (भाग << MADERA_OPCLK_DIV_SHIFT) | ref;

				snd_soc_component_update_bits(component, reg,
							      mask, val);
				वापस 0;
			पूर्ण
			भाग += 2;
		पूर्ण
	पूर्ण

	dev_err(component->dev, "Unable to generate %dHz OPCLK\n", freq);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक madera_get_sysclk_setting(अचिन्हित पूर्णांक freq)
अणु
	चयन (freq) अणु
	हाल 0:
	हाल 5644800:
	हाल 6144000:
		वापस 0;
	हाल 11289600:
	हाल 12288000:
		वापस MADERA_SYSCLK_12MHZ << MADERA_SYSCLK_FREQ_SHIFT;
	हाल 22579200:
	हाल 24576000:
		वापस MADERA_SYSCLK_24MHZ << MADERA_SYSCLK_FREQ_SHIFT;
	हाल 45158400:
	हाल 49152000:
		वापस MADERA_SYSCLK_49MHZ << MADERA_SYSCLK_FREQ_SHIFT;
	हाल 90316800:
	हाल 98304000:
		वापस MADERA_SYSCLK_98MHZ << MADERA_SYSCLK_FREQ_SHIFT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक madera_get_legacy_dspclk_setting(काष्ठा madera *madera,
					    अचिन्हित पूर्णांक freq)
अणु
	चयन (freq) अणु
	हाल 0:
		वापस 0;
	हाल 45158400:
	हाल 49152000:
		चयन (madera->type) अणु
		हाल CS47L85:
		हाल WM1840:
			अगर (madera->rev < 3)
				वापस -EINVAL;
			अन्यथा
				वापस MADERA_SYSCLK_49MHZ <<
				       MADERA_SYSCLK_FREQ_SHIFT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल 135475200:
	हाल 147456000:
		वापस MADERA_DSPCLK_147MHZ << MADERA_DSP_CLK_FREQ_LEGACY_SHIFT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक madera_get_dspclk_setting(काष्ठा madera *madera,
				     अचिन्हित पूर्णांक freq,
				     अचिन्हित पूर्णांक *घड़ी_2_val)
अणु
	चयन (madera->type) अणु
	हाल CS47L35:
	हाल CS47L85:
	हाल WM1840:
		*घड़ी_2_val = 0; /* करोn't use MADERA_DSP_CLOCK_2 */
		वापस madera_get_legacy_dspclk_setting(madera, freq);
	शेष:
		अगर (freq > 150000000)
			वापस -EINVAL;

		/* Use new exact frequency control */
		*घड़ी_2_val = freq / 15625; /* freq * (2^6) / (10^6) */
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक madera_set_outclk(काष्ठा snd_soc_component *component,
			     अचिन्हित पूर्णांक source, अचिन्हित पूर्णांक freq)
अणु
	पूर्णांक भाग, भाग_inc, rate;

	चयन (source) अणु
	हाल MADERA_OUTCLK_SYSCLK:
		dev_dbg(component->dev, "Configured OUTCLK to SYSCLK\n");
		snd_soc_component_update_bits(component, MADERA_OUTPUT_RATE_1,
					      MADERA_OUT_CLK_SRC_MASK, source);
		वापस 0;
	हाल MADERA_OUTCLK_ASYNCCLK:
		dev_dbg(component->dev, "Configured OUTCLK to ASYNCCLK\n");
		snd_soc_component_update_bits(component, MADERA_OUTPUT_RATE_1,
					      MADERA_OUT_CLK_SRC_MASK, source);
		वापस 0;
	हाल MADERA_OUTCLK_MCLK1:
	हाल MADERA_OUTCLK_MCLK2:
	हाल MADERA_OUTCLK_MCLK3:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (freq % 4000)
		rate = 5644800;
	अन्यथा
		rate = 6144000;

	भाग = 1;
	भाग_inc = 0;
	जबतक (भाग <= 8) अणु
		अगर (freq / भाग == rate && !(freq % भाग)) अणु
			dev_dbg(component->dev, "Configured %dHz OUTCLK\n", rate);
			snd_soc_component_update_bits(component,
				MADERA_OUTPUT_RATE_1,
				MADERA_OUT_EXT_CLK_DIV_MASK |
				MADERA_OUT_CLK_SRC_MASK,
				(भाग_inc << MADERA_OUT_EXT_CLK_DIV_SHIFT) |
				source);
			वापस 0;
		पूर्ण
		भाग_inc++;
		भाग *= 2;
	पूर्ण

	dev_err(component->dev,
		"Unable to generate %dHz OUTCLK from %dHz MCLK\n",
		rate, freq);
	वापस -EINVAL;
पूर्ण

पूर्णांक madera_set_sysclk(काष्ठा snd_soc_component *component, पूर्णांक clk_id,
		      पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा madera *madera = priv->madera;
	अक्षर *name;
	अचिन्हित पूर्णांक reg, घड़ी_2_val = 0;
	अचिन्हित पूर्णांक mask = MADERA_SYSCLK_FREQ_MASK | MADERA_SYSCLK_SRC_MASK;
	अचिन्हित पूर्णांक val = source << MADERA_SYSCLK_SRC_SHIFT;
	पूर्णांक clk_freq_sel, *clk;
	पूर्णांक ret = 0;

	चयन (clk_id) अणु
	हाल MADERA_CLK_SYSCLK_1:
		name = "SYSCLK";
		reg = MADERA_SYSTEM_CLOCK_1;
		clk = &priv->sysclk;
		clk_freq_sel = madera_get_sysclk_setting(freq);
		mask |= MADERA_SYSCLK_FRAC;
		अवरोध;
	हाल MADERA_CLK_ASYNCCLK_1:
		name = "ASYNCCLK";
		reg = MADERA_ASYNC_CLOCK_1;
		clk = &priv->asyncclk;
		clk_freq_sel = madera_get_sysclk_setting(freq);
		अवरोध;
	हाल MADERA_CLK_DSPCLK:
		name = "DSPCLK";
		reg = MADERA_DSP_CLOCK_1;
		clk = &priv->dspclk;
		clk_freq_sel = madera_get_dspclk_setting(madera, freq,
							 &घड़ी_2_val);
		अवरोध;
	हाल MADERA_CLK_OPCLK:
	हाल MADERA_CLK_ASYNC_OPCLK:
		वापस madera_set_opclk(component, clk_id, freq);
	हाल MADERA_CLK_OUTCLK:
		वापस madera_set_outclk(component, source, freq);
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (clk_freq_sel < 0) अणु
		dev_err(madera->dev,
			"Failed to get clk setting for %dHZ\n", freq);
		वापस clk_freq_sel;
	पूर्ण

	*clk = freq;

	अगर (freq == 0) अणु
		dev_dbg(madera->dev, "%s cleared\n", name);
		वापस 0;
	पूर्ण

	val |= clk_freq_sel;

	अगर (घड़ी_2_val) अणु
		ret = regmap_ग_लिखो(madera->regmap, MADERA_DSP_CLOCK_2,
				   घड़ी_2_val);
		अगर (ret) अणु
			dev_err(madera->dev,
				"Failed to write DSP_CONFIG2: %d\n", ret);
			वापस ret;
		पूर्ण

		/*
		 * We're using the frequency setting in MADERA_DSP_CLOCK_2 so
		 * करोn't change the frequency select bits in MADERA_DSP_CLOCK_1
		 */
		mask = MADERA_SYSCLK_SRC_MASK;
	पूर्ण

	अगर (freq % 6144000)
		val |= MADERA_SYSCLK_FRAC;

	dev_dbg(madera->dev, "%s set to %uHz\n", name, freq);

	वापस regmap_update_bits(madera->regmap, reg, mask, val);
पूर्ण
EXPORT_SYMBOL_GPL(madera_set_sysclk);

अटल पूर्णांक madera_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा madera *madera = priv->madera;
	पूर्णांक lrclk, bclk, mode, base;

	base = dai->driver->base;

	lrclk = 0;
	bclk = 0;

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
		mode = MADERA_FMT_DSP_MODE_A;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		अगर ((fmt & SND_SOC_DAIFMT_MASTER_MASK) !=
		    SND_SOC_DAIFMT_CBM_CFM) अणु
			madera_aअगर_err(dai, "DSP_B not valid in slave mode\n");
			वापस -EINVAL;
		पूर्ण
		mode = MADERA_FMT_DSP_MODE_B;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		mode = MADERA_FMT_I2S_MODE;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगर ((fmt & SND_SOC_DAIFMT_MASTER_MASK) !=
		    SND_SOC_DAIFMT_CBM_CFM) अणु
			madera_aअगर_err(dai, "LEFT_J not valid in slave mode\n");
			वापस -EINVAL;
		पूर्ण
		mode = MADERA_FMT_LEFT_JUSTIFIED_MODE;
		अवरोध;
	शेष:
		madera_aअगर_err(dai, "Unsupported DAI format %d\n",
			       fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		lrclk |= MADERA_AIF1TX_LRCLK_MSTR;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		bclk |= MADERA_AIF1_BCLK_MSTR;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		bclk |= MADERA_AIF1_BCLK_MSTR;
		lrclk |= MADERA_AIF1TX_LRCLK_MSTR;
		अवरोध;
	शेष:
		madera_aअगर_err(dai, "Unsupported master mode %d\n",
			       fmt & SND_SOC_DAIFMT_MASTER_MASK);
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		bclk |= MADERA_AIF1_BCLK_INV;
		lrclk |= MADERA_AIF1TX_LRCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		bclk |= MADERA_AIF1_BCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		lrclk |= MADERA_AIF1TX_LRCLK_INV;
		अवरोध;
	शेष:
		madera_aअगर_err(dai, "Unsupported invert mode %d\n",
			       fmt & SND_SOC_DAIFMT_INV_MASK);
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(madera->regmap, base + MADERA_AIF_BCLK_CTRL,
			   MADERA_AIF1_BCLK_INV | MADERA_AIF1_BCLK_MSTR,
			   bclk);
	regmap_update_bits(madera->regmap, base + MADERA_AIF_TX_PIN_CTRL,
			   MADERA_AIF1TX_LRCLK_INV | MADERA_AIF1TX_LRCLK_MSTR,
			   lrclk);
	regmap_update_bits(madera->regmap, base + MADERA_AIF_RX_PIN_CTRL,
			   MADERA_AIF1RX_LRCLK_INV | MADERA_AIF1RX_LRCLK_MSTR,
			   lrclk);
	regmap_update_bits(madera->regmap, base + MADERA_AIF_FORMAT,
			   MADERA_AIF1_FMT_MASK, mode);

	वापस 0;
पूर्ण

अटल स्थिर पूर्णांक madera_48k_bclk_rates[] = अणु
	-1,
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

अटल स्थिर पूर्णांक madera_44k1_bclk_rates[] = अणु
	-1,
	44100,
	58800,
	88200,
	117600,
	177640,
	235200,
	352800,
	470400,
	705600,
	940800,
	1411200,
	1881600,
	2822400,
	3763200,
	5644800,
	7526400,
	11289600,
	22579200,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक madera_sr_vals[] = अणु
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

#घोषणा MADERA_192K_48K_RATE_MASK	0x0F003E
#घोषणा MADERA_192K_44K1_RATE_MASK	0x003E00
#घोषणा MADERA_192K_RATE_MASK		(MADERA_192K_48K_RATE_MASK | \
					 MADERA_192K_44K1_RATE_MASK)
#घोषणा MADERA_384K_48K_RATE_MASK	0x0F007E
#घोषणा MADERA_384K_44K1_RATE_MASK	0x007E00
#घोषणा MADERA_384K_RATE_MASK		(MADERA_384K_48K_RATE_MASK | \
					 MADERA_384K_44K1_RATE_MASK)

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list madera_स्थिरraपूर्णांक = अणु
	.count	= ARRAY_SIZE(madera_sr_vals),
	.list	= madera_sr_vals,
पूर्ण;

अटल पूर्णांक madera_startup(काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा madera_dai_priv *dai_priv = &priv->dai[dai->id - 1];
	काष्ठा madera *madera = priv->madera;
	अचिन्हित पूर्णांक base_rate;

	अगर (!substream->runसमय)
		वापस 0;

	चयन (dai_priv->clk) अणु
	हाल MADERA_CLK_SYSCLK_1:
	हाल MADERA_CLK_SYSCLK_2:
	हाल MADERA_CLK_SYSCLK_3:
		base_rate = priv->sysclk;
		अवरोध;
	हाल MADERA_CLK_ASYNCCLK_1:
	हाल MADERA_CLK_ASYNCCLK_2:
		base_rate = priv->asyncclk;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	चयन (madera->type) अणु
	हाल CS42L92:
	हाल CS47L92:
	हाल CS47L93:
		अगर (base_rate == 0)
			dai_priv->स्थिरraपूर्णांक.mask = MADERA_384K_RATE_MASK;
		अन्यथा अगर (base_rate % 4000)
			dai_priv->स्थिरraपूर्णांक.mask = MADERA_384K_44K1_RATE_MASK;
		अन्यथा
			dai_priv->स्थिरraपूर्णांक.mask = MADERA_384K_48K_RATE_MASK;
		अवरोध;
	शेष:
		अगर (base_rate == 0)
			dai_priv->स्थिरraपूर्णांक.mask = MADERA_192K_RATE_MASK;
		अन्यथा अगर (base_rate % 4000)
			dai_priv->स्थिरraपूर्णांक.mask = MADERA_192K_44K1_RATE_MASK;
		अन्यथा
			dai_priv->स्थिरraपूर्णांक.mask = MADERA_192K_48K_RATE_MASK;
		अवरोध;
	पूर्ण

	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
					  SNDRV_PCM_HW_PARAM_RATE,
					  &dai_priv->स्थिरraपूर्णांक);
पूर्ण

अटल पूर्णांक madera_hw_params_rate(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा madera_dai_priv *dai_priv = &priv->dai[dai->id - 1];
	पूर्णांक base = dai->driver->base;
	पूर्णांक i, sr_val;
	अचिन्हित पूर्णांक reg, cur, tar;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(madera_sr_vals); i++)
		अगर (madera_sr_vals[i] == params_rate(params))
			अवरोध;

	अगर (i == ARRAY_SIZE(madera_sr_vals)) अणु
		madera_aअगर_err(dai, "Unsupported sample rate %dHz\n",
			       params_rate(params));
		वापस -EINVAL;
	पूर्ण
	sr_val = i;

	चयन (dai_priv->clk) अणु
	हाल MADERA_CLK_SYSCLK_1:
		reg = MADERA_SAMPLE_RATE_1;
		tar = 0 << MADERA_AIF1_RATE_SHIFT;
		अवरोध;
	हाल MADERA_CLK_SYSCLK_2:
		reg = MADERA_SAMPLE_RATE_2;
		tar = 1 << MADERA_AIF1_RATE_SHIFT;
		अवरोध;
	हाल MADERA_CLK_SYSCLK_3:
		reg = MADERA_SAMPLE_RATE_3;
		tar = 2 << MADERA_AIF1_RATE_SHIFT;
		अवरोध;
	हाल MADERA_CLK_ASYNCCLK_1:
		reg = MADERA_ASYNC_SAMPLE_RATE_1;
		tar = 8 << MADERA_AIF1_RATE_SHIFT;
		अवरोध;
	हाल MADERA_CLK_ASYNCCLK_2:
		reg = MADERA_ASYNC_SAMPLE_RATE_2;
		tar = 9 << MADERA_AIF1_RATE_SHIFT;
		अवरोध;
	शेष:
		madera_aअगर_err(dai, "Invalid clock %d\n", dai_priv->clk);
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, reg, MADERA_SAMPLE_RATE_1_MASK,
				      sr_val);

	अगर (!base)
		वापस 0;

	ret = regmap_पढ़ो(priv->madera->regmap,
			  base + MADERA_AIF_RATE_CTRL, &cur);
	अगर (ret != 0) अणु
		madera_aअगर_err(dai, "Failed to check rate: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर ((cur & MADERA_AIF1_RATE_MASK) == (tar & MADERA_AIF1_RATE_MASK))
		वापस 0;

	mutex_lock(&priv->rate_lock);

	अगर (!madera_can_change_grp_rate(priv, base + MADERA_AIF_RATE_CTRL)) अणु
		madera_aअगर_warn(dai, "Cannot change rate while active\n");
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/* Guard the rate change with SYSCLK cycles */
	madera_spin_sysclk(priv);
	snd_soc_component_update_bits(component, base + MADERA_AIF_RATE_CTRL,
				      MADERA_AIF1_RATE_MASK, tar);
	madera_spin_sysclk(priv);

out:
	mutex_unlock(&priv->rate_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक madera_aअगर_cfg_changed(काष्ठा snd_soc_component *component,
				  पूर्णांक base, पूर्णांक bclk, पूर्णांक lrclk, पूर्णांक frame)
अणु
	अचिन्हित पूर्णांक val;

	val = snd_soc_component_पढ़ो(component, base + MADERA_AIF_BCLK_CTRL);
	अगर (bclk != (val & MADERA_AIF1_BCLK_FREQ_MASK))
		वापस 1;

	val = snd_soc_component_पढ़ो(component, base + MADERA_AIF_RX_BCLK_RATE);
	अगर (lrclk != (val & MADERA_AIF1RX_BCPF_MASK))
		वापस 1;

	val = snd_soc_component_पढ़ो(component, base + MADERA_AIF_FRAME_CTRL_1);
	अगर (frame != (val & (MADERA_AIF1TX_WL_MASK |
			     MADERA_AIF1TX_SLOT_LEN_MASK)))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक madera_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा madera *madera = priv->madera;
	पूर्णांक base = dai->driver->base;
	स्थिर पूर्णांक *rates;
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक channels = params_channels(params);
	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक chan_limit =
			madera->pdata.codec.max_channels_घड़ीed[dai->id - 1];
	पूर्णांक tdm_width = priv->tdm_width[dai->id - 1];
	पूर्णांक tdm_slots = priv->tdm_slots[dai->id - 1];
	पूर्णांक bclk, lrclk, wl, frame, bclk_target, num_rates;
	पूर्णांक reconfig;
	अचिन्हित पूर्णांक aअगर_tx_state = 0, aअगर_rx_state = 0;

	अगर (rate % 4000) अणु
		rates = &madera_44k1_bclk_rates[0];
		num_rates = ARRAY_SIZE(madera_44k1_bclk_rates);
	पूर्ण अन्यथा अणु
		rates = &madera_48k_bclk_rates[0];
		num_rates = ARRAY_SIZE(madera_48k_bclk_rates);
	पूर्ण

	wl = snd_pcm_क्रमmat_width(params_क्रमmat(params));

	अगर (tdm_slots) अणु
		madera_aअगर_dbg(dai, "Configuring for %d %d bit TDM slots\n",
			       tdm_slots, tdm_width);
		bclk_target = tdm_slots * tdm_width * rate;
		channels = tdm_slots;
	पूर्ण अन्यथा अणु
		bclk_target = snd_soc_params_to_bclk(params);
		tdm_width = wl;
	पूर्ण

	अगर (chan_limit && chan_limit < channels) अणु
		madera_aअगर_dbg(dai, "Limiting to %d channels\n", chan_limit);
		bclk_target /= channels;
		bclk_target *= chan_limit;
	पूर्ण

	/* Force multiple of 2 channels क्रम I2S mode */
	val = snd_soc_component_पढ़ो(component, base + MADERA_AIF_FORMAT);
	val &= MADERA_AIF1_FMT_MASK;
	अगर ((channels & 1) && val == MADERA_FMT_I2S_MODE) अणु
		madera_aअगर_dbg(dai, "Forcing stereo mode\n");
		bclk_target /= channels;
		bclk_target *= channels + 1;
	पूर्ण

	क्रम (i = 0; i < num_rates; i++) अणु
		अगर (rates[i] >= bclk_target && rates[i] % rate == 0) अणु
			bclk = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == num_rates) अणु
		madera_aअगर_err(dai, "Unsupported sample rate %dHz\n", rate);
		वापस -EINVAL;
	पूर्ण

	lrclk = rates[bclk] / rate;

	madera_aअगर_dbg(dai, "BCLK %dHz LRCLK %dHz\n",
		       rates[bclk], rates[bclk] / lrclk);

	frame = wl << MADERA_AIF1TX_WL_SHIFT | tdm_width;

	reconfig = madera_aअगर_cfg_changed(component, base, bclk, lrclk, frame);
	अगर (reconfig < 0)
		वापस reconfig;

	अगर (reconfig) अणु
		/* Save AIF TX/RX state */
		regmap_पढ़ो(madera->regmap, base + MADERA_AIF_TX_ENABLES,
			    &aअगर_tx_state);
		regmap_पढ़ो(madera->regmap, base + MADERA_AIF_RX_ENABLES,
			    &aअगर_rx_state);
		/* Disable AIF TX/RX beक्रमe reconfiguring it */
		regmap_update_bits(madera->regmap,
				   base + MADERA_AIF_TX_ENABLES, 0xff, 0x0);
		regmap_update_bits(madera->regmap,
				   base + MADERA_AIF_RX_ENABLES, 0xff, 0x0);
	पूर्ण

	ret = madera_hw_params_rate(substream, params, dai);
	अगर (ret != 0)
		जाओ restore_aअगर;

	अगर (reconfig) अणु
		regmap_update_bits(madera->regmap,
				   base + MADERA_AIF_BCLK_CTRL,
				   MADERA_AIF1_BCLK_FREQ_MASK, bclk);
		regmap_update_bits(madera->regmap,
				   base + MADERA_AIF_RX_BCLK_RATE,
				   MADERA_AIF1RX_BCPF_MASK, lrclk);
		regmap_update_bits(madera->regmap,
				   base + MADERA_AIF_FRAME_CTRL_1,
				   MADERA_AIF1TX_WL_MASK |
				   MADERA_AIF1TX_SLOT_LEN_MASK, frame);
		regmap_update_bits(madera->regmap,
				   base + MADERA_AIF_FRAME_CTRL_2,
				   MADERA_AIF1RX_WL_MASK |
				   MADERA_AIF1RX_SLOT_LEN_MASK, frame);
	पूर्ण

restore_aअगर:
	अगर (reconfig) अणु
		/* Restore AIF TX/RX state */
		regmap_update_bits(madera->regmap,
				   base + MADERA_AIF_TX_ENABLES,
				   0xff, aअगर_tx_state);
		regmap_update_bits(madera->regmap,
				   base + MADERA_AIF_RX_ENABLES,
				   0xff, aअगर_rx_state);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक madera_is_syncclk(पूर्णांक clk_id)
अणु
	चयन (clk_id) अणु
	हाल MADERA_CLK_SYSCLK_1:
	हाल MADERA_CLK_SYSCLK_2:
	हाल MADERA_CLK_SYSCLK_3:
		वापस 1;
	हाल MADERA_CLK_ASYNCCLK_1:
	हाल MADERA_CLK_ASYNCCLK_2:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक madera_dai_set_sysclk(काष्ठा snd_soc_dai *dai,
				 पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा madera_dai_priv *dai_priv = &priv->dai[dai->id - 1];
	काष्ठा snd_soc_dapm_route routes[2];
	पूर्णांक is_sync;

	is_sync = madera_is_syncclk(clk_id);
	अगर (is_sync < 0) अणु
		dev_err(component->dev, "Illegal DAI clock id %d\n", clk_id);
		वापस is_sync;
	पूर्ण

	अगर (is_sync == madera_is_syncclk(dai_priv->clk))
		वापस 0;

	अगर (snd_soc_dai_active(dai)) अणु
		dev_err(component->dev, "Can't change clock on active DAI %d\n",
			dai->id);
		वापस -EBUSY;
	पूर्ण

	dev_dbg(component->dev, "Setting AIF%d to %s\n", dai->id,
		is_sync ? "SYSCLK" : "ASYNCCLK");

	/*
	 * A connection to SYSCLK is always required, we only add and हटाओ
	 * a connection to ASYNCCLK
	 */
	स_रखो(&routes, 0, माप(routes));
	routes[0].sink = dai->driver->capture.stream_name;
	routes[1].sink = dai->driver->playback.stream_name;
	routes[0].source = "ASYNCCLK";
	routes[1].source = "ASYNCCLK";

	अगर (is_sync)
		snd_soc_dapm_del_routes(dapm, routes, ARRAY_SIZE(routes));
	अन्यथा
		snd_soc_dapm_add_routes(dapm, routes, ARRAY_SIZE(routes));

	dai_priv->clk = clk_id;

	वापस snd_soc_dapm_sync(dapm);
पूर्ण

अटल पूर्णांक madera_set_tristate(काष्ठा snd_soc_dai *dai, पूर्णांक tristate)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक base = dai->driver->base;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	अगर (tristate)
		reg = MADERA_AIF1_TRI;
	अन्यथा
		reg = 0;

	ret = snd_soc_component_update_bits(component,
					    base + MADERA_AIF_RATE_CTRL,
					    MADERA_AIF1_TRI, reg);
	अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम madera_set_channels_to_mask(काष्ठा snd_soc_dai *dai,
					अचिन्हित पूर्णांक base,
					पूर्णांक channels, अचिन्हित पूर्णांक mask)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा madera *madera = priv->madera;
	पूर्णांक slot, i;

	क्रम (i = 0; i < channels; ++i) अणु
		slot = ffs(mask) - 1;
		अगर (slot < 0)
			वापस;

		regmap_ग_लिखो(madera->regmap, base + i, slot);

		mask &= ~(1 << slot);
	पूर्ण

	अगर (mask)
		madera_aअगर_warn(dai, "Too many channels in TDM mask\n");
पूर्ण

अटल पूर्णांक madera_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
			       अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक base = dai->driver->base;
	पूर्णांक rx_max_chan = dai->driver->playback.channels_max;
	पूर्णांक tx_max_chan = dai->driver->capture.channels_max;

	/* Only support TDM क्रम the physical AIFs */
	अगर (dai->id > MADERA_MAX_AIF)
		वापस -ENOTSUPP;

	अगर (slots == 0) अणु
		tx_mask = (1 << tx_max_chan) - 1;
		rx_mask = (1 << rx_max_chan) - 1;
	पूर्ण

	madera_set_channels_to_mask(dai, base + MADERA_AIF_FRAME_CTRL_3,
				    tx_max_chan, tx_mask);
	madera_set_channels_to_mask(dai, base + MADERA_AIF_FRAME_CTRL_11,
				    rx_max_chan, rx_mask);

	priv->tdm_width[dai->id - 1] = slot_width;
	priv->tdm_slots[dai->id - 1] = slots;

	वापस 0;
पूर्ण

स्थिर काष्ठा snd_soc_dai_ops madera_dai_ops = अणु
	.startup = &madera_startup,
	.set_fmt = &madera_set_fmt,
	.set_tdm_slot = &madera_set_tdm_slot,
	.hw_params = &madera_hw_params,
	.set_sysclk = &madera_dai_set_sysclk,
	.set_tristate = &madera_set_tristate,
पूर्ण;
EXPORT_SYMBOL_GPL(madera_dai_ops);

स्थिर काष्ठा snd_soc_dai_ops madera_simple_dai_ops = अणु
	.startup = &madera_startup,
	.hw_params = &madera_hw_params_rate,
	.set_sysclk = &madera_dai_set_sysclk,
पूर्ण;
EXPORT_SYMBOL_GPL(madera_simple_dai_ops);

पूर्णांक madera_init_dai(काष्ठा madera_priv *priv, पूर्णांक id)
अणु
	काष्ठा madera_dai_priv *dai_priv = &priv->dai[id];

	dai_priv->clk = MADERA_CLK_SYSCLK_1;
	dai_priv->स्थिरraपूर्णांक = madera_स्थिरraपूर्णांक;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(madera_init_dai);

अटल स्थिर काष्ठा अणु
	अचिन्हित पूर्णांक min;
	अचिन्हित पूर्णांक max;
	u16 fratio;
	पूर्णांक ratio;
पूर्ण fll_sync_fratios[] = अणु
	अणु       0,    64000, 4, 16 पूर्ण,
	अणु   64000,   128000, 3,  8 पूर्ण,
	अणु  128000,   256000, 2,  4 पूर्ण,
	अणु  256000,  1000000, 1,  2 पूर्ण,
	अणु 1000000, 13500000, 0,  1 पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pseuकरो_fref_max[MADERA_FLL_MAX_FRATIO] = अणु
	13500000,
	 6144000,
	 6144000,
	 3072000,
	 3072000,
	 2822400,
	 2822400,
	 1536000,
	 1536000,
	 1536000,
	 1536000,
	 1536000,
	 1536000,
	 1536000,
	 1536000,
	  768000,
पूर्ण;

काष्ठा madera_fll_gains अणु
	अचिन्हित पूर्णांक min;
	अचिन्हित पूर्णांक max;
	पूर्णांक gain;		/* मुख्य gain */
	पूर्णांक alt_gain;		/* alternate पूर्णांकeger gain */
पूर्ण;

अटल स्थिर काष्ठा madera_fll_gains madera_fll_sync_gains[] = अणु
	अणु       0,   256000, 0, -1 पूर्ण,
	अणु  256000,  1000000, 2, -1 पूर्ण,
	अणु 1000000, 13500000, 4, -1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा madera_fll_gains madera_fll_मुख्य_gains[] = अणु
	अणु       0,   100000, 0, 2 पूर्ण,
	अणु  100000,   375000, 2, 2 पूर्ण,
	अणु  375000,   768000, 3, 2 पूर्ण,
	अणु  768001,  1500000, 3, 3 पूर्ण,
	अणु 1500000,  6000000, 4, 3 पूर्ण,
	अणु 6000000, 13500000, 5, 3 पूर्ण,
पूर्ण;

अटल पूर्णांक madera_find_sync_fratio(अचिन्हित पूर्णांक fref, पूर्णांक *fratio)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fll_sync_fratios); i++) अणु
		अगर (fll_sync_fratios[i].min <= fref &&
		    fref <= fll_sync_fratios[i].max) अणु
			अगर (fratio)
				*fratio = fll_sync_fratios[i].fratio;

			वापस fll_sync_fratios[i].ratio;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक madera_find_मुख्य_fratio(अचिन्हित पूर्णांक fref, अचिन्हित पूर्णांक fout,
				   पूर्णांक *fratio)
अणु
	पूर्णांक ratio = 1;

	जबतक ((fout / (ratio * fref)) > MADERA_FLL_MAX_N)
		ratio++;

	अगर (fratio)
		*fratio = ratio - 1;

	वापस ratio;
पूर्ण

अटल पूर्णांक madera_find_fratio(काष्ठा madera_fll *fll, अचिन्हित पूर्णांक fref,
			      bool sync, पूर्णांक *fratio)
अणु
	चयन (fll->madera->type) अणु
	हाल CS47L35:
		चयन (fll->madera->rev) अणु
		हाल 0:
			/* rev A0 uses sync calculation क्रम both loops */
			वापस madera_find_sync_fratio(fref, fratio);
		शेष:
			अगर (sync)
				वापस madera_find_sync_fratio(fref, fratio);
			अन्यथा
				वापस madera_find_मुख्य_fratio(fref,
							       fll->fout,
							       fratio);
		पूर्ण
		अवरोध;
	हाल CS47L85:
	हाल WM1840:
		/* these use the same calculation क्रम मुख्य and sync loops */
		वापस madera_find_sync_fratio(fref, fratio);
	शेष:
		अगर (sync)
			वापस madera_find_sync_fratio(fref, fratio);
		अन्यथा
			वापस madera_find_मुख्य_fratio(fref, fll->fout, fratio);
	पूर्ण
पूर्ण

अटल पूर्णांक madera_calc_fratio(काष्ठा madera_fll *fll,
			      काष्ठा madera_fll_cfg *cfg,
			      अचिन्हित पूर्णांक fref, bool sync)
अणु
	पूर्णांक init_ratio, ratio;
	पूर्णांक refभाग, भाग;

	/* fref must be <=13.5MHz, find initial refभाग */
	भाग = 1;
	cfg->refभाग = 0;
	जबतक (fref > MADERA_FLL_MAX_FREF) अणु
		भाग *= 2;
		fref /= 2;
		cfg->refभाग++;

		अगर (भाग > MADERA_FLL_MAX_REFDIV)
			वापस -EINVAL;
	पूर्ण

	/* Find an appropriate FLL_FRATIO */
	init_ratio = madera_find_fratio(fll, fref, sync, &cfg->fratio);
	अगर (init_ratio < 0) अणु
		madera_fll_err(fll, "Unable to find FRATIO for fref=%uHz\n",
			       fref);
		वापस init_ratio;
	पूर्ण

	अगर (!sync)
		cfg->fratio = init_ratio - 1;

	चयन (fll->madera->type) अणु
	हाल CS47L35:
		चयन (fll->madera->rev) अणु
		हाल 0:
			अगर (sync)
				वापस init_ratio;
			अवरोध;
		शेष:
			वापस init_ratio;
		पूर्ण
		अवरोध;
	हाल CS47L85:
	हाल WM1840:
		अगर (sync)
			वापस init_ratio;
		अवरोध;
	शेष:
		वापस init_ratio;
	पूर्ण

	/*
	 * For CS47L35 rev A0, CS47L85 and WM1840 adjust FRATIO/refभाग to aव्योम
	 * पूर्णांकeger mode अगर possible
	 */
	refभाग = cfg->refभाग;

	जबतक (भाग <= MADERA_FLL_MAX_REFDIV) अणु
		/*
		 * start from init_ratio because this may alपढ़ोy give a
		 * fractional N.K
		 */
		क्रम (ratio = init_ratio; ratio > 0; ratio--) अणु
			अगर (fll->fout % (ratio * fref)) अणु
				cfg->refभाग = refभाग;
				cfg->fratio = ratio - 1;
				वापस ratio;
			पूर्ण
		पूर्ण

		क्रम (ratio = init_ratio + 1; ratio <= MADERA_FLL_MAX_FRATIO;
		     ratio++) अणु
			अगर ((MADERA_FLL_VCO_CORNER / 2) /
			    (MADERA_FLL_VCO_MULT * ratio) < fref)
				अवरोध;

			अगर (fref > pseuकरो_fref_max[ratio - 1])
				अवरोध;

			अगर (fll->fout % (ratio * fref)) अणु
				cfg->refभाग = refभाग;
				cfg->fratio = ratio - 1;
				वापस ratio;
			पूर्ण
		पूर्ण

		भाग *= 2;
		fref /= 2;
		refभाग++;
		init_ratio = madera_find_fratio(fll, fref, sync, शून्य);
	पूर्ण

	madera_fll_warn(fll, "Falling back to integer mode operation\n");

	वापस cfg->fratio + 1;
पूर्ण

अटल पूर्णांक madera_find_fll_gain(काष्ठा madera_fll *fll,
				काष्ठा madera_fll_cfg *cfg,
				अचिन्हित पूर्णांक fref,
				स्थिर काष्ठा madera_fll_gains *gains,
				पूर्णांक n_gains)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n_gains; i++) अणु
		अगर (gains[i].min <= fref && fref <= gains[i].max) अणु
			cfg->gain = gains[i].gain;
			cfg->alt_gain = gains[i].alt_gain;
			वापस 0;
		पूर्ण
	पूर्ण

	madera_fll_err(fll, "Unable to find gain for fref=%uHz\n", fref);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक madera_calc_fll(काष्ठा madera_fll *fll,
			   काष्ठा madera_fll_cfg *cfg,
			   अचिन्हित पूर्णांक fref, bool sync)
अणु
	अचिन्हित पूर्णांक gcd_fll;
	स्थिर काष्ठा madera_fll_gains *gains;
	पूर्णांक n_gains;
	पूर्णांक ratio, ret;

	madera_fll_dbg(fll, "fref=%u Fout=%u fvco=%u\n",
		       fref, fll->fout, fll->fout * MADERA_FLL_VCO_MULT);

	/* Find an appropriate FLL_FRATIO and refभाग */
	ratio = madera_calc_fratio(fll, cfg, fref, sync);
	अगर (ratio < 0)
		वापस ratio;

	/* Apply the भागision क्रम our reमुख्यing calculations */
	fref = fref / (1 << cfg->refभाग);

	cfg->n = fll->fout / (ratio * fref);

	अगर (fll->fout % (ratio * fref)) अणु
		gcd_fll = gcd(fll->fout, ratio * fref);
		madera_fll_dbg(fll, "GCD=%u\n", gcd_fll);

		cfg->theta = (fll->fout - (cfg->n * ratio * fref))
			/ gcd_fll;
		cfg->lambda = (ratio * fref) / gcd_fll;
	पूर्ण अन्यथा अणु
		cfg->theta = 0;
		cfg->lambda = 0;
	पूर्ण

	/*
	 * Round करोwn to 16bit range with cost of accuracy lost.
	 * Denominator must be bigger than numerator so we only
	 * take care of it.
	 */
	जबतक (cfg->lambda >= (1 << 16)) अणु
		cfg->theta >>= 1;
		cfg->lambda >>= 1;
	पूर्ण

	चयन (fll->madera->type) अणु
	हाल CS47L35:
		चयन (fll->madera->rev) अणु
		हाल 0:
			/* Rev A0 uses the sync gains क्रम both loops */
			gains = madera_fll_sync_gains;
			n_gains = ARRAY_SIZE(madera_fll_sync_gains);
			अवरोध;
		शेष:
			अगर (sync) अणु
				gains = madera_fll_sync_gains;
				n_gains = ARRAY_SIZE(madera_fll_sync_gains);
			पूर्ण अन्यथा अणु
				gains = madera_fll_मुख्य_gains;
				n_gains = ARRAY_SIZE(madera_fll_मुख्य_gains);
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;
	हाल CS47L85:
	हाल WM1840:
		/* These use the sync gains क्रम both loops */
		gains = madera_fll_sync_gains;
		n_gains = ARRAY_SIZE(madera_fll_sync_gains);
		अवरोध;
	शेष:
		अगर (sync) अणु
			gains = madera_fll_sync_gains;
			n_gains = ARRAY_SIZE(madera_fll_sync_gains);
		पूर्ण अन्यथा अणु
			gains = madera_fll_मुख्य_gains;
			n_gains = ARRAY_SIZE(madera_fll_मुख्य_gains);
		पूर्ण
		अवरोध;
	पूर्ण

	ret = madera_find_fll_gain(fll, cfg, fref, gains, n_gains);
	अगर (ret)
		वापस ret;

	madera_fll_dbg(fll, "N=%d THETA=%d LAMBDA=%d\n",
		       cfg->n, cfg->theta, cfg->lambda);
	madera_fll_dbg(fll, "FRATIO=0x%x(%d) REFCLK_DIV=0x%x(%d)\n",
		       cfg->fratio, ratio, cfg->refभाग, 1 << cfg->refभाग);
	madera_fll_dbg(fll, "GAIN=0x%x(%d)\n", cfg->gain, 1 << cfg->gain);

	वापस 0;
पूर्ण

अटल bool madera_ग_लिखो_fll(काष्ठा madera *madera, अचिन्हित पूर्णांक base,
			     काष्ठा madera_fll_cfg *cfg, पूर्णांक source,
			     bool sync, पूर्णांक gain)
अणु
	bool change, fll_change;

	fll_change = false;
	regmap_update_bits_check(madera->regmap,
				 base + MADERA_FLL_CONTROL_3_OFFS,
				 MADERA_FLL1_THETA_MASK,
				 cfg->theta, &change);
	fll_change |= change;
	regmap_update_bits_check(madera->regmap,
				 base + MADERA_FLL_CONTROL_4_OFFS,
				 MADERA_FLL1_LAMBDA_MASK,
				 cfg->lambda, &change);
	fll_change |= change;
	regmap_update_bits_check(madera->regmap,
				 base + MADERA_FLL_CONTROL_5_OFFS,
				 MADERA_FLL1_FRATIO_MASK,
				 cfg->fratio << MADERA_FLL1_FRATIO_SHIFT,
				 &change);
	fll_change |= change;
	regmap_update_bits_check(madera->regmap,
				 base + MADERA_FLL_CONTROL_6_OFFS,
				 MADERA_FLL1_REFCLK_DIV_MASK |
				 MADERA_FLL1_REFCLK_SRC_MASK,
				 cfg->refभाग << MADERA_FLL1_REFCLK_DIV_SHIFT |
				 source << MADERA_FLL1_REFCLK_SRC_SHIFT,
				 &change);
	fll_change |= change;

	अगर (sync) अणु
		regmap_update_bits_check(madera->regmap,
					 base + MADERA_FLL_SYNCHRONISER_7_OFFS,
					 MADERA_FLL1_GAIN_MASK,
					 gain << MADERA_FLL1_GAIN_SHIFT,
					 &change);
		fll_change |= change;
	पूर्ण अन्यथा अणु
		regmap_update_bits_check(madera->regmap,
					 base + MADERA_FLL_CONTROL_7_OFFS,
					 MADERA_FLL1_GAIN_MASK,
					 gain << MADERA_FLL1_GAIN_SHIFT,
					 &change);
		fll_change |= change;
	पूर्ण

	regmap_update_bits_check(madera->regmap,
				 base + MADERA_FLL_CONTROL_2_OFFS,
				 MADERA_FLL1_CTRL_UPD | MADERA_FLL1_N_MASK,
				 MADERA_FLL1_CTRL_UPD | cfg->n, &change);
	fll_change |= change;

	वापस fll_change;
पूर्ण

अटल पूर्णांक madera_is_enabled_fll(काष्ठा madera_fll *fll, पूर्णांक base)
अणु
	काष्ठा madera *madera = fll->madera;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	ret = regmap_पढ़ो(madera->regmap,
			  base + MADERA_FLL_CONTROL_1_OFFS, &reg);
	अगर (ret != 0) अणु
		madera_fll_err(fll, "Failed to read current state: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस reg & MADERA_FLL1_ENA;
पूर्ण

अटल पूर्णांक madera_रुको_क्रम_fll(काष्ठा madera_fll *fll, bool requested)
अणु
	काष्ठा madera *madera = fll->madera;
	अचिन्हित पूर्णांक val = 0;
	bool status;
	पूर्णांक i;

	madera_fll_dbg(fll, "Waiting for FLL...\n");

	क्रम (i = 0; i < 30; i++) अणु
		regmap_पढ़ो(madera->regmap, MADERA_IRQ1_RAW_STATUS_2, &val);
		status = val & (MADERA_FLL1_LOCK_STS1 << (fll->id - 1));
		अगर (status == requested)
			वापस 0;

		चयन (i) अणु
		हाल 0 ... 5:
			usleep_range(75, 125);
			अवरोध;
		हाल 11 ... 20:
			usleep_range(750, 1250);
			अवरोध;
		शेष:
			msleep(20);
			अवरोध;
		पूर्ण
	पूर्ण

	madera_fll_warn(fll, "Timed out waiting for lock\n");

	वापस -ETIMEDOUT;
पूर्ण

अटल bool madera_set_fll_phase_पूर्णांकegrator(काष्ठा madera_fll *fll,
					    काष्ठा madera_fll_cfg *ref_cfg,
					    bool sync)
अणु
	अचिन्हित पूर्णांक val;
	bool reg_change;

	अगर (!sync && ref_cfg->theta == 0)
		val = (1 << MADERA_FLL1_PHASE_ENA_SHIFT) |
		      (2 << MADERA_FLL1_PHASE_GAIN_SHIFT);
	अन्यथा
		val = 2 << MADERA_FLL1_PHASE_GAIN_SHIFT;

	regmap_update_bits_check(fll->madera->regmap,
				 fll->base + MADERA_FLL_EFS_2_OFFS,
				 MADERA_FLL1_PHASE_ENA_MASK |
				 MADERA_FLL1_PHASE_GAIN_MASK,
				 val, &reg_change);

	वापस reg_change;
पूर्ण

अटल पूर्णांक madera_set_fll_clks_reg(काष्ठा madera_fll *fll, bool ena,
				   अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mask,
				   अचिन्हित पूर्णांक shअगरt)
अणु
	काष्ठा madera *madera = fll->madera;
	अचिन्हित पूर्णांक src;
	काष्ठा clk *clk;
	पूर्णांक ret;

	ret = regmap_पढ़ो(madera->regmap, reg, &src);
	अगर (ret != 0) अणु
		madera_fll_err(fll, "Failed to read current source: %d\n",
			       ret);
		वापस ret;
	पूर्ण

	src = (src & mask) >> shअगरt;

	चयन (src) अणु
	हाल MADERA_FLL_SRC_MCLK1:
		clk = madera->mclk[MADERA_MCLK1].clk;
		अवरोध;
	हाल MADERA_FLL_SRC_MCLK2:
		clk = madera->mclk[MADERA_MCLK2].clk;
		अवरोध;
	हाल MADERA_FLL_SRC_MCLK3:
		clk = madera->mclk[MADERA_MCLK3].clk;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (ena) अणु
		वापस clk_prepare_enable(clk);
	पूर्ण अन्यथा अणु
		clk_disable_unprepare(clk);
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक madera_set_fll_clks(काष्ठा madera_fll *fll, पूर्णांक base, bool ena)
अणु
	वापस madera_set_fll_clks_reg(fll, ena,
				       base + MADERA_FLL_CONTROL_6_OFFS,
				       MADERA_FLL1_REFCLK_SRC_MASK,
				       MADERA_FLL1_REFCLK_DIV_SHIFT);
पूर्ण

अटल अंतरभूत पूर्णांक madera_set_fllao_clks(काष्ठा madera_fll *fll, पूर्णांक base, bool ena)
अणु
	वापस madera_set_fll_clks_reg(fll, ena,
				       base + MADERA_FLLAO_CONTROL_6_OFFS,
				       MADERA_FLL_AO_REFCLK_SRC_MASK,
				       MADERA_FLL_AO_REFCLK_SRC_SHIFT);
पूर्ण

अटल अंतरभूत पूर्णांक madera_set_fllhj_clks(काष्ठा madera_fll *fll, पूर्णांक base, bool ena)
अणु
	वापस madera_set_fll_clks_reg(fll, ena,
				       base + MADERA_FLL_CONTROL_1_OFFS,
				       CS47L92_FLL1_REFCLK_SRC_MASK,
				       CS47L92_FLL1_REFCLK_SRC_SHIFT);
पूर्ण

अटल व्योम madera_disable_fll(काष्ठा madera_fll *fll)
अणु
	काष्ठा madera *madera = fll->madera;
	अचिन्हित पूर्णांक sync_base;
	bool ref_change, sync_change;

	चयन (madera->type) अणु
	हाल CS47L35:
		sync_base = fll->base + CS47L35_FLL_SYNCHRONISER_OFFS;
		अवरोध;
	शेष:
		sync_base = fll->base + MADERA_FLL_SYNCHRONISER_OFFS;
		अवरोध;
	पूर्ण

	madera_fll_dbg(fll, "Disabling FLL\n");

	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_1_OFFS,
			   MADERA_FLL1_FREERUN, MADERA_FLL1_FREERUN);
	regmap_update_bits_check(madera->regmap,
				 fll->base + MADERA_FLL_CONTROL_1_OFFS,
				 MADERA_FLL1_ENA, 0, &ref_change);
	regmap_update_bits_check(madera->regmap,
				 sync_base + MADERA_FLL_SYNCHRONISER_1_OFFS,
				 MADERA_FLL1_SYNC_ENA, 0, &sync_change);
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_1_OFFS,
			   MADERA_FLL1_FREERUN, 0);

	madera_रुको_क्रम_fll(fll, false);

	अगर (sync_change)
		madera_set_fll_clks(fll, sync_base, false);

	अगर (ref_change) अणु
		madera_set_fll_clks(fll, fll->base, false);
		pm_runसमय_put_स्वतःsuspend(madera->dev);
	पूर्ण
पूर्ण

अटल पूर्णांक madera_enable_fll(काष्ठा madera_fll *fll)
अणु
	काष्ठा madera *madera = fll->madera;
	bool have_sync = false;
	पूर्णांक alपढ़ोy_enabled = madera_is_enabled_fll(fll, fll->base);
	पूर्णांक sync_enabled;
	काष्ठा madera_fll_cfg cfg;
	अचिन्हित पूर्णांक sync_base;
	पूर्णांक gain, ret;
	bool fll_change = false;

	अगर (alपढ़ोy_enabled < 0)
		वापस alपढ़ोy_enabled;	/* error getting current state */

	अगर (fll->ref_src < 0 || fll->ref_freq == 0) अणु
		madera_fll_err(fll, "No REFCLK\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	madera_fll_dbg(fll, "Enabling FLL, initially %s\n",
		       alपढ़ोy_enabled ? "enabled" : "disabled");

	अगर (fll->fout < MADERA_FLL_MIN_FOUT ||
	    fll->fout > MADERA_FLL_MAX_FOUT) अणु
		madera_fll_err(fll, "invalid fout %uHz\n", fll->fout);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	चयन (madera->type) अणु
	हाल CS47L35:
		sync_base = fll->base + CS47L35_FLL_SYNCHRONISER_OFFS;
		अवरोध;
	शेष:
		sync_base = fll->base + MADERA_FLL_SYNCHRONISER_OFFS;
		अवरोध;
	पूर्ण

	sync_enabled = madera_is_enabled_fll(fll, sync_base);
	अगर (sync_enabled < 0)
		वापस sync_enabled;

	अगर (alपढ़ोy_enabled) अणु
		/* Facilitate smooth refclk across the transition */
		regmap_update_bits(fll->madera->regmap,
				   fll->base + MADERA_FLL_CONTROL_1_OFFS,
				   MADERA_FLL1_FREERUN,
				   MADERA_FLL1_FREERUN);
		udelay(32);
		regmap_update_bits(fll->madera->regmap,
				   fll->base + MADERA_FLL_CONTROL_7_OFFS,
				   MADERA_FLL1_GAIN_MASK, 0);

		अगर (sync_enabled > 0)
			madera_set_fll_clks(fll, sync_base, false);
		madera_set_fll_clks(fll, fll->base, false);
	पूर्ण

	/* Apply SYNCCLK setting */
	अगर (fll->sync_src >= 0) अणु
		ret = madera_calc_fll(fll, &cfg, fll->sync_freq, true);
		अगर (ret < 0)
			जाओ err;

		fll_change |= madera_ग_लिखो_fll(madera, sync_base,
					       &cfg, fll->sync_src,
					       true, cfg.gain);
		have_sync = true;
	पूर्ण

	अगर (alपढ़ोy_enabled && !!sync_enabled != have_sync)
		madera_fll_warn(fll, "Synchroniser changed on active FLL\n");

	/* Apply REFCLK setting */
	ret = madera_calc_fll(fll, &cfg, fll->ref_freq, false);
	अगर (ret < 0)
		जाओ err;

	/* Ref path hardcodes lambda to 65536 when sync is on */
	अगर (have_sync && cfg.lambda)
		cfg.theta = (cfg.theta * (1 << 16)) / cfg.lambda;

	चयन (fll->madera->type) अणु
	हाल CS47L35:
		चयन (fll->madera->rev) अणु
		हाल 0:
			gain = cfg.gain;
			अवरोध;
		शेष:
			fll_change |=
				madera_set_fll_phase_पूर्णांकegrator(fll, &cfg,
								have_sync);
			अगर (!have_sync && cfg.theta == 0)
				gain = cfg.alt_gain;
			अन्यथा
				gain = cfg.gain;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल CS47L85:
	हाल WM1840:
		gain = cfg.gain;
		अवरोध;
	शेष:
		fll_change |= madera_set_fll_phase_पूर्णांकegrator(fll, &cfg,
							      have_sync);
		अगर (!have_sync && cfg.theta == 0)
			gain = cfg.alt_gain;
		अन्यथा
			gain = cfg.gain;
		अवरोध;
	पूर्ण

	fll_change |= madera_ग_लिखो_fll(madera, fll->base,
				       &cfg, fll->ref_src,
				       false, gain);

	/*
	 * Increase the bandwidth अगर we're not using a low frequency
	 * sync source.
	 */
	अगर (have_sync && fll->sync_freq > 100000)
		regmap_update_bits(madera->regmap,
				   sync_base + MADERA_FLL_SYNCHRONISER_7_OFFS,
				   MADERA_FLL1_SYNC_DFSAT_MASK, 0);
	अन्यथा
		regmap_update_bits(madera->regmap,
				   sync_base + MADERA_FLL_SYNCHRONISER_7_OFFS,
				   MADERA_FLL1_SYNC_DFSAT_MASK,
				   MADERA_FLL1_SYNC_DFSAT);

	अगर (!alपढ़ोy_enabled)
		pm_runसमय_get_sync(madera->dev);

	अगर (have_sync) अणु
		madera_set_fll_clks(fll, sync_base, true);
		regmap_update_bits(madera->regmap,
				   sync_base + MADERA_FLL_SYNCHRONISER_1_OFFS,
				   MADERA_FLL1_SYNC_ENA,
				   MADERA_FLL1_SYNC_ENA);
	पूर्ण

	madera_set_fll_clks(fll, fll->base, true);
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_1_OFFS,
			   MADERA_FLL1_ENA, MADERA_FLL1_ENA);

	अगर (alपढ़ोy_enabled)
		regmap_update_bits(madera->regmap,
				   fll->base + MADERA_FLL_CONTROL_1_OFFS,
				   MADERA_FLL1_FREERUN, 0);

	अगर (fll_change || !alपढ़ोy_enabled)
		madera_रुको_क्रम_fll(fll, true);

	वापस 0;

err:
	 /* In हाल of error करोn't leave the FLL running with an old config */
	madera_disable_fll(fll);

	वापस ret;
पूर्ण

अटल पूर्णांक madera_apply_fll(काष्ठा madera_fll *fll)
अणु
	अगर (fll->fout) अणु
		वापस madera_enable_fll(fll);
	पूर्ण अन्यथा अणु
		madera_disable_fll(fll);
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक madera_set_fll_syncclk(काष्ठा madera_fll *fll, पूर्णांक source,
			   अचिन्हित पूर्णांक fref, अचिन्हित पूर्णांक fout)
अणु
	/*
	 * fout is ignored, since the synchronizer is an optional extra
	 * स्थिरraपूर्णांक on the Fout generated from REFCLK, so the Fout is
	 * set when configuring REFCLK
	 */

	अगर (fll->sync_src == source && fll->sync_freq == fref)
		वापस 0;

	fll->sync_src = source;
	fll->sync_freq = fref;

	वापस madera_apply_fll(fll);
पूर्ण
EXPORT_SYMBOL_GPL(madera_set_fll_syncclk);

पूर्णांक madera_set_fll_refclk(काष्ठा madera_fll *fll, पूर्णांक source,
			  अचिन्हित पूर्णांक fref, अचिन्हित पूर्णांक fout)
अणु
	पूर्णांक ret;

	अगर (fll->ref_src == source &&
	    fll->ref_freq == fref && fll->fout == fout)
		वापस 0;

	/*
	 * Changes of fout on an enabled FLL aren't allowed except when
	 * setting fout==0 to disable the FLL
	 */
	अगर (fout && fout != fll->fout) अणु
		ret = madera_is_enabled_fll(fll, fll->base);
		अगर (ret < 0)
			वापस ret;

		अगर (ret) अणु
			madera_fll_err(fll, "Can't change Fout on active FLL\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	fll->ref_src = source;
	fll->ref_freq = fref;
	fll->fout = fout;

	वापस madera_apply_fll(fll);
पूर्ण
EXPORT_SYMBOL_GPL(madera_set_fll_refclk);

पूर्णांक madera_init_fll(काष्ठा madera *madera, पूर्णांक id, पूर्णांक base,
		    काष्ठा madera_fll *fll)
अणु
	fll->id = id;
	fll->base = base;
	fll->madera = madera;
	fll->ref_src = MADERA_FLL_SRC_NONE;
	fll->sync_src = MADERA_FLL_SRC_NONE;

	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_1_OFFS,
			   MADERA_FLL1_FREERUN, 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(madera_init_fll);

अटल स्थिर काष्ठा reg_sequence madera_fll_ao_32K_49M_patch[] = अणु
	अणु MADERA_FLLAO_CONTROL_2,  0x02EE पूर्ण,
	अणु MADERA_FLLAO_CONTROL_3,  0x0000 पूर्ण,
	अणु MADERA_FLLAO_CONTROL_4,  0x0001 पूर्ण,
	अणु MADERA_FLLAO_CONTROL_5,  0x0002 पूर्ण,
	अणु MADERA_FLLAO_CONTROL_6,  0x8001 पूर्ण,
	अणु MADERA_FLLAO_CONTROL_7,  0x0004 पूर्ण,
	अणु MADERA_FLLAO_CONTROL_8,  0x0077 पूर्ण,
	अणु MADERA_FLLAO_CONTROL_10, 0x06D8 पूर्ण,
	अणु MADERA_FLLAO_CONTROL_11, 0x0085 पूर्ण,
	अणु MADERA_FLLAO_CONTROL_2,  0x82EE पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence madera_fll_ao_32K_45M_patch[] = अणु
	अणु MADERA_FLLAO_CONTROL_2,  0x02B1 पूर्ण,
	अणु MADERA_FLLAO_CONTROL_3,  0x0001 पूर्ण,
	अणु MADERA_FLLAO_CONTROL_4,  0x0010 पूर्ण,
	अणु MADERA_FLLAO_CONTROL_5,  0x0002 पूर्ण,
	अणु MADERA_FLLAO_CONTROL_6,  0x8001 पूर्ण,
	अणु MADERA_FLLAO_CONTROL_7,  0x0004 पूर्ण,
	अणु MADERA_FLLAO_CONTROL_8,  0x0077 पूर्ण,
	अणु MADERA_FLLAO_CONTROL_10, 0x06D8 पूर्ण,
	अणु MADERA_FLLAO_CONTROL_11, 0x0005 पूर्ण,
	अणु MADERA_FLLAO_CONTROL_2,  0x82B1 पूर्ण,
पूर्ण;

काष्ठा madera_fllao_patch अणु
	अचिन्हित पूर्णांक fin;
	अचिन्हित पूर्णांक fout;
	स्थिर काष्ठा reg_sequence *patch;
	अचिन्हित पूर्णांक patch_size;
पूर्ण;

अटल स्थिर काष्ठा madera_fllao_patch madera_fllao_settings[] = अणु
	अणु
		.fin = 32768,
		.fout = 49152000,
		.patch = madera_fll_ao_32K_49M_patch,
		.patch_size = ARRAY_SIZE(madera_fll_ao_32K_49M_patch),

	पूर्ण,
	अणु
		.fin = 32768,
		.fout = 45158400,
		.patch = madera_fll_ao_32K_45M_patch,
		.patch_size = ARRAY_SIZE(madera_fll_ao_32K_45M_patch),
	पूर्ण,
पूर्ण;

अटल पूर्णांक madera_enable_fll_ao(काष्ठा madera_fll *fll,
				स्थिर काष्ठा reg_sequence *patch,
				अचिन्हित पूर्णांक patch_size)
अणु
	काष्ठा madera *madera = fll->madera;
	पूर्णांक alपढ़ोy_enabled = madera_is_enabled_fll(fll, fll->base);
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	अगर (alपढ़ोy_enabled < 0)
		वापस alपढ़ोy_enabled;

	अगर (!alपढ़ोy_enabled)
		pm_runसमय_get_sync(madera->dev);

	madera_fll_dbg(fll, "Enabling FLL_AO, initially %s\n",
		       alपढ़ोy_enabled ? "enabled" : "disabled");

	/* FLL_AO_HOLD must be set beक्रमe configuring any रेजिस्टरs */
	regmap_update_bits(fll->madera->regmap,
			   fll->base + MADERA_FLLAO_CONTROL_1_OFFS,
			   MADERA_FLL_AO_HOLD, MADERA_FLL_AO_HOLD);

	अगर (alपढ़ोy_enabled)
		madera_set_fllao_clks(fll, fll->base, false);

	क्रम (i = 0; i < patch_size; i++) अणु
		val = patch[i].def;

		/* modअगरy the patch to apply fll->ref_src as input घड़ी */
		अगर (patch[i].reg == MADERA_FLLAO_CONTROL_6) अणु
			val &= ~MADERA_FLL_AO_REFCLK_SRC_MASK;
			val |= (fll->ref_src << MADERA_FLL_AO_REFCLK_SRC_SHIFT)
				& MADERA_FLL_AO_REFCLK_SRC_MASK;
		पूर्ण

		regmap_ग_लिखो(madera->regmap, patch[i].reg, val);
	पूर्ण

	madera_set_fllao_clks(fll, fll->base, true);

	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLLAO_CONTROL_1_OFFS,
			   MADERA_FLL_AO_ENA, MADERA_FLL_AO_ENA);

	/* Release the hold so that fll_ao locks to बाह्यal frequency */
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLLAO_CONTROL_1_OFFS,
			   MADERA_FLL_AO_HOLD, 0);

	अगर (!alपढ़ोy_enabled)
		madera_रुको_क्रम_fll(fll, true);

	वापस 0;
पूर्ण

अटल पूर्णांक madera_disable_fll_ao(काष्ठा madera_fll *fll)
अणु
	काष्ठा madera *madera = fll->madera;
	bool change;

	madera_fll_dbg(fll, "Disabling FLL_AO\n");

	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLLAO_CONTROL_1_OFFS,
			   MADERA_FLL_AO_HOLD, MADERA_FLL_AO_HOLD);
	regmap_update_bits_check(madera->regmap,
				 fll->base + MADERA_FLLAO_CONTROL_1_OFFS,
				 MADERA_FLL_AO_ENA, 0, &change);

	madera_रुको_क्रम_fll(fll, false);

	/*
	 * ctrl_up gates the ग_लिखोs to all fll_ao रेजिस्टर, setting it to 0
	 * here ensures that after a runसमय suspend/resume cycle when one
	 * enables the fllao then ctrl_up is the last bit that is configured
	 * by the fllao enable code rather than the cache sync operation which
	 * would have updated it much earlier beक्रमe writing out all fllao
	 * रेजिस्टरs
	 */
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLLAO_CONTROL_2_OFFS,
			   MADERA_FLL_AO_CTRL_UPD_MASK, 0);

	अगर (change) अणु
		madera_set_fllao_clks(fll, fll->base, false);
		pm_runसमय_put_स्वतःsuspend(madera->dev);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक madera_set_fll_ao_refclk(काष्ठा madera_fll *fll, पूर्णांक source,
			     अचिन्हित पूर्णांक fin, अचिन्हित पूर्णांक fout)
अणु
	पूर्णांक ret = 0;
	स्थिर काष्ठा reg_sequence *patch = शून्य;
	पूर्णांक patch_size = 0;
	अचिन्हित पूर्णांक i;

	अगर (fll->ref_src == source &&
	    fll->ref_freq == fin && fll->fout == fout)
		वापस 0;

	madera_fll_dbg(fll, "Change FLL_AO refclk to fin=%u fout=%u source=%d\n",
		       fin, fout, source);

	अगर (fout && (fll->ref_freq != fin || fll->fout != fout)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(madera_fllao_settings); i++) अणु
			अगर (madera_fllao_settings[i].fin == fin &&
			    madera_fllao_settings[i].fout == fout)
				अवरोध;
		पूर्ण

		अगर (i == ARRAY_SIZE(madera_fllao_settings)) अणु
			madera_fll_err(fll,
				       "No matching configuration for FLL_AO\n");
			वापस -EINVAL;
		पूर्ण

		patch = madera_fllao_settings[i].patch;
		patch_size = madera_fllao_settings[i].patch_size;
	पूर्ण

	fll->ref_src = source;
	fll->ref_freq = fin;
	fll->fout = fout;

	अगर (fout)
		ret = madera_enable_fll_ao(fll, patch, patch_size);
	अन्यथा
		madera_disable_fll_ao(fll);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(madera_set_fll_ao_refclk);

अटल पूर्णांक madera_fllhj_disable(काष्ठा madera_fll *fll)
अणु
	काष्ठा madera *madera = fll->madera;
	bool change;

	madera_fll_dbg(fll, "Disabling FLL\n");

	/* Disable lockdet, but करोn't set ctrl_upd update but.  This allows the
	 * lock status bit to clear as normal, but should the FLL be enabled
	 * again due to a control घड़ी being required, the lock won't re-निश्चित
	 * as the FLL config रेजिस्टरs are स्वतःmatically applied when the FLL
	 * enables.
	 */
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_11_OFFS,
			   MADERA_FLL1_LOCKDET_MASK, 0);
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_1_OFFS,
			   MADERA_FLL1_HOLD_MASK, MADERA_FLL1_HOLD_MASK);
	regmap_update_bits_check(madera->regmap,
				 fll->base + MADERA_FLL_CONTROL_1_OFFS,
				 MADERA_FLL1_ENA_MASK, 0, &change);

	madera_रुको_क्रम_fll(fll, false);

	/* ctrl_up gates the ग_लिखोs to all the fll's रेजिस्टरs, setting it to 0
	 * here ensures that after a runसमय suspend/resume cycle when one
	 * enables the fll then ctrl_up is the last bit that is configured
	 * by the fll enable code rather than the cache sync operation which
	 * would have updated it much earlier beक्रमe writing out all fll
	 * रेजिस्टरs
	 */
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_2_OFFS,
			   MADERA_FLL1_CTRL_UPD_MASK, 0);

	अगर (change) अणु
		madera_set_fllhj_clks(fll, fll->base, false);
		pm_runसमय_put_स्वतःsuspend(madera->dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक madera_fllhj_apply(काष्ठा madera_fll *fll, पूर्णांक fin)
अणु
	काष्ठा madera *madera = fll->madera;
	पूर्णांक refभाग, fref, fout, lockdet_thr, fbभाग, hp, fast_clk, fllgcd;
	bool frac = false;
	अचिन्हित पूर्णांक fll_n, min_n, max_n, ratio, theta, lambda;
	अचिन्हित पूर्णांक gains, val, num;

	madera_fll_dbg(fll, "fin=%d, fout=%d\n", fin, fll->fout);

	क्रम (refभाग = 0; refभाग < 4; refभाग++)
		अगर ((fin / (1 << refभाग)) <= MADERA_FLLHJ_MAX_THRESH)
			अवरोध;

	fref = fin / (1 << refभाग);

	/* Use simple heuristic approach to find a configuration that
	 * should work क्रम most input घड़ीs.
	 */
	fast_clk = 0;
	fout = fll->fout;
	frac = fout % fref;

	अगर (fref < MADERA_FLLHJ_LOW_THRESH) अणु
		lockdet_thr = 2;
		gains = MADERA_FLLHJ_LOW_GAINS;
		अगर (frac)
			fbभाग = 256;
		अन्यथा
			fbभाग = 4;
	पूर्ण अन्यथा अगर (fref < MADERA_FLLHJ_MID_THRESH) अणु
		lockdet_thr = 8;
		gains = MADERA_FLLHJ_MID_GAINS;
		fbभाग = 1;
	पूर्ण अन्यथा अणु
		lockdet_thr = 8;
		gains = MADERA_FLLHJ_HIGH_GAINS;
		fbभाग = 1;
		/* For high speed input घड़ीs, enable 300MHz fast oscillator
		 * when we're in fractional भागider mode.
		 */
		अगर (frac) अणु
			fast_clk = 0x3;
			fout = fll->fout * 6;
		पूर्ण
	पूर्ण
	/* Use high perक्रमmance mode क्रम fractional configurations. */
	अगर (frac) अणु
		hp = 0x3;
		min_n = MADERA_FLLHJ_FRAC_MIN_N;
		max_n = MADERA_FLLHJ_FRAC_MAX_N;
	पूर्ण अन्यथा अणु
		hp = 0x0;
		min_n = MADERA_FLLHJ_पूर्णांक_न्यून_N;
		max_n = MADERA_FLLHJ_पूर्णांक_उच्च_N;
	पूर्ण

	ratio = fout / fref;

	madera_fll_dbg(fll, "refdiv=%d, fref=%d, frac:%d\n",
		       refभाग, fref, frac);

	जबतक (ratio / fbभाग < min_n) अणु
		fbभाग /= 2;
		अगर (fbभाग < 1) अणु
			madera_fll_err(fll, "FBDIV (%d) must be >= 1\n", fbभाग);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	जबतक (frac && (ratio / fbभाग > max_n)) अणु
		fbभाग *= 2;
		अगर (fbभाग >= 1024) अणु
			madera_fll_err(fll, "FBDIV (%u) >= 1024\n", fbभाग);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	madera_fll_dbg(fll, "lockdet=%d, hp=0x%x, fbdiv:%d\n",
		       lockdet_thr, hp, fbभाग);

	/* Calculate N.K values */
	fllgcd = gcd(fout, fbभाग * fref);
	num = fout / fllgcd;
	lambda = (fref * fbभाग) / fllgcd;
	fll_n = num / lambda;
	theta = num % lambda;

	madera_fll_dbg(fll, "fll_n=%d, gcd=%d, theta=%d, lambda=%d\n",
		       fll_n, fllgcd, theta, lambda);

	/* Some sanity checks beक्रमe any रेजिस्टरs are written. */
	अगर (fll_n < min_n || fll_n > max_n) अणु
		madera_fll_err(fll, "N not in valid %s mode range %d-%d: %d\n",
			       frac ? "fractional" : "integer", min_n, max_n,
			       fll_n);
		वापस -EINVAL;
	पूर्ण
	अगर (fbभाग < 1 || (frac && fbभाग >= 1024) || (!frac && fbभाग >= 256)) अणु
		madera_fll_err(fll, "Invalid fbdiv for %s mode (%u)\n",
			       frac ? "fractional" : "integer", fbभाग);
		वापस -EINVAL;
	पूर्ण

	/* clear the ctrl_upd bit to guarantee we ग_लिखो to it later. */
	regmap_ग_लिखो(madera->regmap,
		     fll->base + MADERA_FLL_CONTROL_2_OFFS,
		     fll_n << MADERA_FLL1_N_SHIFT);
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_3_OFFS,
			   MADERA_FLL1_THETA_MASK,
			   theta << MADERA_FLL1_THETA_SHIFT);
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_4_OFFS,
			   MADERA_FLL1_LAMBDA_MASK,
			   lambda << MADERA_FLL1_LAMBDA_SHIFT);
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_5_OFFS,
			   MADERA_FLL1_FB_DIV_MASK,
			   fbभाग << MADERA_FLL1_FB_DIV_SHIFT);
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_6_OFFS,
			   MADERA_FLL1_REFCLK_DIV_MASK,
			   refभाग << MADERA_FLL1_REFCLK_DIV_SHIFT);
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_GAIN_OFFS,
			   0xffff,
			   gains);
	val = hp << MADERA_FLL1_HP_SHIFT;
	val |= 1 << MADERA_FLL1_PHASEDET_ENA_SHIFT;
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_10_OFFS,
			   MADERA_FLL1_HP_MASK | MADERA_FLL1_PHASEDET_ENA_MASK,
			   val);
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_11_OFFS,
			   MADERA_FLL1_LOCKDET_THR_MASK,
			   lockdet_thr << MADERA_FLL1_LOCKDET_THR_SHIFT);
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL1_DIGITAL_TEST_1_OFFS,
			   MADERA_FLL1_SYNC_EFS_ENA_MASK |
			   MADERA_FLL1_CLK_VCO_FAST_SRC_MASK,
			   fast_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक madera_fllhj_enable(काष्ठा madera_fll *fll)
अणु
	काष्ठा madera *madera = fll->madera;
	पूर्णांक alपढ़ोy_enabled = madera_is_enabled_fll(fll, fll->base);
	पूर्णांक ret;

	अगर (alपढ़ोy_enabled < 0)
		वापस alपढ़ोy_enabled;

	अगर (!alपढ़ोy_enabled)
		pm_runसमय_get_sync(madera->dev);

	madera_fll_dbg(fll, "Enabling FLL, initially %s\n",
		       alपढ़ोy_enabled ? "enabled" : "disabled");

	/* FLLn_HOLD must be set beक्रमe configuring any रेजिस्टरs */
	regmap_update_bits(fll->madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_1_OFFS,
			   MADERA_FLL1_HOLD_MASK,
			   MADERA_FLL1_HOLD_MASK);

	अगर (alपढ़ोy_enabled)
		madera_set_fllhj_clks(fll, fll->base, false);

	/* Apply refclk */
	ret = madera_fllhj_apply(fll, fll->ref_freq);
	अगर (ret) अणु
		madera_fll_err(fll, "Failed to set FLL: %d\n", ret);
		जाओ out;
	पूर्ण
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_1_OFFS,
			   CS47L92_FLL1_REFCLK_SRC_MASK,
			   fll->ref_src << CS47L92_FLL1_REFCLK_SRC_SHIFT);

	madera_set_fllhj_clks(fll, fll->base, true);

	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_1_OFFS,
			   MADERA_FLL1_ENA_MASK,
			   MADERA_FLL1_ENA_MASK);

out:
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_11_OFFS,
			   MADERA_FLL1_LOCKDET_MASK,
			   MADERA_FLL1_LOCKDET_MASK);

	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_2_OFFS,
			   MADERA_FLL1_CTRL_UPD_MASK,
			   MADERA_FLL1_CTRL_UPD_MASK);

	/* Release the hold so that flln locks to बाह्यal frequency */
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_1_OFFS,
			   MADERA_FLL1_HOLD_MASK,
			   0);

	अगर (!alपढ़ोy_enabled)
		madera_रुको_क्रम_fll(fll, true);

	वापस 0;
पूर्ण

अटल पूर्णांक madera_fllhj_validate(काष्ठा madera_fll *fll,
				 अचिन्हित पूर्णांक ref_in,
				 अचिन्हित पूर्णांक fout)
अणु
	अगर (fout && !ref_in) अणु
		madera_fll_err(fll, "fllout set without valid input clk\n");
		वापस -EINVAL;
	पूर्ण

	अगर (fll->fout && fout != fll->fout) अणु
		madera_fll_err(fll, "Can't change output on active FLL\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ref_in / MADERA_FLL_MAX_REFDIV > MADERA_FLLHJ_MAX_THRESH) अणु
		madera_fll_err(fll, "Can't scale %dMHz to <=13MHz\n", ref_in);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक madera_fllhj_set_refclk(काष्ठा madera_fll *fll, पूर्णांक source,
			    अचिन्हित पूर्णांक fin, अचिन्हित पूर्णांक fout)
अणु
	पूर्णांक ret = 0;

	/* To reमुख्य consistent with previous FLLs, we expect fout to be
	 * provided in the क्रमm of the required sysclk rate, which is
	 * 2x the calculated fll out.
	 */
	अगर (fout)
		fout /= 2;

	अगर (fll->ref_src == source && fll->ref_freq == fin &&
	    fll->fout == fout)
		वापस 0;

	अगर (fin && fout && madera_fllhj_validate(fll, fin, fout))
		वापस -EINVAL;

	fll->ref_src = source;
	fll->ref_freq = fin;
	fll->fout = fout;

	अगर (fout)
		ret = madera_fllhj_enable(fll);
	अन्यथा
		madera_fllhj_disable(fll);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(madera_fllhj_set_refclk);

/**
 * madera_set_output_mode - Set the mode of the specअगरied output
 *
 * @component: Device to configure
 * @output: Output number
 * @dअगरferential: True to set the output to dअगरferential mode
 *
 * Some प्रणालीs use बाह्यal analogue चयनes to connect more
 * analogue devices to the CODEC than are supported by the device.  In
 * some प्रणालीs this requires changing the चयनed output from single
 * ended to dअगरferential mode dynamically at runसमय, an operation
 * supported using this function.
 *
 * Most प्रणालीs have a single अटल configuration and should use
 * platक्रमm data instead.
 */
पूर्णांक madera_set_output_mode(काष्ठा snd_soc_component *component, पूर्णांक output,
			   bool dअगरferential)
अणु
	अचिन्हित पूर्णांक reg, val;
	पूर्णांक ret;

	अगर (output < 1 || output > MADERA_MAX_OUTPUT)
		वापस -EINVAL;

	reg = MADERA_OUTPUT_PATH_CONFIG_1L + (output - 1) * 8;

	अगर (dअगरferential)
		val = MADERA_OUT1_MONO;
	अन्यथा
		val = 0;

	ret = snd_soc_component_update_bits(component, reg, MADERA_OUT1_MONO,
					    val);
	अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(madera_set_output_mode);

अटल bool madera_eq_filter_unstable(bool mode, __be16 _a, __be16 _b)
अणु
	s16 a = be16_to_cpu(_a);
	s16 b = be16_to_cpu(_b);

	अगर (!mode) अणु
		वापस असल(a) >= 4096;
	पूर्ण अन्यथा अणु
		अगर (असल(b) >= 4096)
			वापस true;

		वापस (असल((a << 16) / (4096 - b)) >= 4096 << 4);
	पूर्ण
पूर्ण

पूर्णांक madera_eq_coeff_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा madera *madera = priv->madera;
	काष्ठा soc_bytes *params = (व्योम *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक val;
	__be16 *data;
	पूर्णांक len;
	पूर्णांक ret;

	len = params->num_regs * regmap_get_val_bytes(madera->regmap);

	data = kmemdup(ucontrol->value.bytes.data, len, GFP_KERNEL | GFP_DMA);
	अगर (!data)
		वापस -ENOMEM;

	data[0] &= cpu_to_be16(MADERA_EQ1_B1_MODE);

	अगर (madera_eq_filter_unstable(!!data[0], data[1], data[2]) ||
	    madera_eq_filter_unstable(true, data[4], data[5]) ||
	    madera_eq_filter_unstable(true, data[8], data[9]) ||
	    madera_eq_filter_unstable(true, data[12], data[13]) ||
	    madera_eq_filter_unstable(false, data[16], data[17])) अणु
		dev_err(madera->dev, "Rejecting unstable EQ coefficients\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = regmap_पढ़ो(madera->regmap, params->base, &val);
	अगर (ret != 0)
		जाओ out;

	val &= ~MADERA_EQ1_B1_MODE;
	data[0] |= cpu_to_be16(val);

	ret = regmap_raw_ग_लिखो(madera->regmap, params->base, data, len);

out:
	kमुक्त(data);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(madera_eq_coeff_put);

पूर्णांक madera_lhpf_coeff_put(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा madera_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा madera *madera = priv->madera;
	__be16 *data = (__be16 *)ucontrol->value.bytes.data;
	s16 val = be16_to_cpu(*data);

	अगर (असल(val) >= 4096) अणु
		dev_err(madera->dev, "Rejecting unstable LHPF coefficients\n");
		वापस -EINVAL;
	पूर्ण

	वापस snd_soc_bytes_put(kcontrol, ucontrol);
पूर्ण
EXPORT_SYMBOL_GPL(madera_lhpf_coeff_put);

MODULE_SOFTDEP("pre: madera");
MODULE_DESCRIPTION("ASoC Cirrus Logic Madera codec support");
MODULE_AUTHOR("Charles Keepax <ckeepax@opensource.cirrus.com>");
MODULE_AUTHOR("Richard Fitzgerald <rf@opensource.cirrus.com>");
MODULE_LICENSE("GPL v2");
