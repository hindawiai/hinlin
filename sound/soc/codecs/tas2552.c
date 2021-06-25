<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tas2552.c - ALSA SoC Texas Instruments TAS2552 Mono Audio Amplअगरier
 *
 * Copyright (C) 2014 Texas Instruments Incorporated -  https://www.ti.com
 *
 * Author: Dan Murphy <dmurphy@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/tlv.h>
#समावेश <sound/tas2552-plat.h>
#समावेश <dt-bindings/sound/tas2552.h>

#समावेश "tas2552.h"

अटल स्थिर काष्ठा reg_शेष tas2552_reg_defs[] = अणु
	अणुTAS2552_CFG_1, 0x22पूर्ण,
	अणुTAS2552_CFG_3, 0x80पूर्ण,
	अणुTAS2552_DOUT, 0x00पूर्ण,
	अणुTAS2552_OUTPUT_DATA, 0xc0पूर्ण,
	अणुTAS2552_PDM_CFG, 0x01पूर्ण,
	अणुTAS2552_PGA_GAIN, 0x00पूर्ण,
	अणुTAS2552_BOOST_APT_CTRL, 0x0fपूर्ण,
	अणुTAS2552_RESERVED_0D, 0xbeपूर्ण,
	अणुTAS2552_LIMIT_RATE_HYS, 0x08पूर्ण,
	अणुTAS2552_CFG_2, 0xefपूर्ण,
	अणुTAS2552_SER_CTRL_1, 0x00पूर्ण,
	अणुTAS2552_SER_CTRL_2, 0x00पूर्ण,
	अणुTAS2552_PLL_CTRL_1, 0x10पूर्ण,
	अणुTAS2552_PLL_CTRL_2, 0x00पूर्ण,
	अणुTAS2552_PLL_CTRL_3, 0x00पूर्ण,
	अणुTAS2552_BTIP, 0x8fपूर्ण,
	अणुTAS2552_BTS_CTRL, 0x80पूर्ण,
	अणुTAS2552_LIMIT_RELEASE, 0x04पूर्ण,
	अणुTAS2552_LIMIT_INT_COUNT, 0x00पूर्ण,
	अणुTAS2552_EDGE_RATE_CTRL, 0x40पूर्ण,
	अणुTAS2552_VBAT_DATA, 0x00पूर्ण,
पूर्ण;

#घोषणा TAS2552_NUM_SUPPLIES	3
अटल स्थिर अक्षर *tas2552_supply_names[TAS2552_NUM_SUPPLIES] = अणु
	"vbat",		/* vbat voltage */
	"iovdd",	/* I/O Voltage */
	"avdd",		/* Analog DAC Voltage */
पूर्ण;

काष्ठा tas2552_data अणु
	काष्ठा snd_soc_component *component;
	काष्ठा regmap *regmap;
	काष्ठा i2c_client *tas2552_client;
	काष्ठा regulator_bulk_data supplies[TAS2552_NUM_SUPPLIES];
	काष्ठा gpio_desc *enable_gpio;
	अचिन्हित अक्षर regs[TAS2552_VBAT_DATA];
	अचिन्हित पूर्णांक pll_clkin;
	पूर्णांक pll_clk_id;
	अचिन्हित पूर्णांक pdm_clk;
	पूर्णांक pdm_clk_id;

	अचिन्हित पूर्णांक dai_fmt;
	अचिन्हित पूर्णांक tdm_delay;
पूर्ण;

अटल पूर्णांक tas2552_post_event(काष्ठा snd_soc_dapm_widget *w,
			      काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_ग_लिखो(component, TAS2552_RESERVED_0D, 0xc0);
		snd_soc_component_update_bits(component, TAS2552_LIMIT_RATE_HYS, (1 << 5),
				    (1 << 5));
		snd_soc_component_update_bits(component, TAS2552_CFG_2, 1, 0);
		snd_soc_component_update_bits(component, TAS2552_CFG_1, TAS2552_SWS, 0);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, TAS2552_CFG_1, TAS2552_SWS,
				    TAS2552_SWS);
		snd_soc_component_update_bits(component, TAS2552_CFG_2, 1, 1);
		snd_soc_component_update_bits(component, TAS2552_LIMIT_RATE_HYS, (1 << 5), 0);
		snd_soc_component_ग_लिखो(component, TAS2552_RESERVED_0D, 0xbe);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* Input mux controls */
अटल स्थिर अक्षर * स्थिर tas2552_input_texts[] = अणु
	"Digital", "Analog" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(tas2552_input_mux_क्रमागत, TAS2552_CFG_3, 7,
			    tas2552_input_texts);

अटल स्थिर काष्ठा snd_kcontrol_new tas2552_input_mux_control =
	SOC_DAPM_ENUM("Route", tas2552_input_mux_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget tas2552_dapm_widमाला_लो[] =
अणु
	SND_SOC_DAPM_INPUT("IN"),

	/* MUX Controls */
	SND_SOC_DAPM_MUX("Input selection", SND_SOC_NOPM, 0, 0,
			 &tas2552_input_mux_control),

	SND_SOC_DAPM_AIF_IN("DAC IN", "DAC Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_OUT_DRV("ClassD", TAS2552_CFG_2, 7, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL", TAS2552_CFG_2, 3, 0, शून्य, 0),
	SND_SOC_DAPM_POST("Post Event", tas2552_post_event),

	SND_SOC_DAPM_OUTPUT("OUT")
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route tas2552_audio_map[] = अणु
	अणु"DAC", शून्य, "DAC IN"पूर्ण,
	अणु"Input selection", "Digital", "DAC"पूर्ण,
	अणु"Input selection", "Analog", "IN"पूर्ण,
	अणु"ClassD", शून्य, "Input selection"पूर्ण,
	अणु"OUT", शून्य, "ClassD"पूर्ण,
	अणु"ClassD", शून्य, "PLL"पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल व्योम tas2552_sw_shutकरोwn(काष्ठा tas2552_data *tas2552, पूर्णांक sw_shutकरोwn)
अणु
	u8 cfg1_reg = 0;

	अगर (!tas2552->component)
		वापस;

	अगर (sw_shutकरोwn)
		cfg1_reg = TAS2552_SWS;

	snd_soc_component_update_bits(tas2552->component, TAS2552_CFG_1, TAS2552_SWS,
			    cfg1_reg);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tas2552_setup_pll(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा tas2552_data *tas2552 = dev_get_drvdata(component->dev);
	bool bypass_pll = false;
	अचिन्हित पूर्णांक pll_clk = params_rate(params) * 512;
	अचिन्हित पूर्णांक pll_clkin = tas2552->pll_clkin;
	u8 pll_enable;

	अगर (!pll_clkin) अणु
		अगर (tas2552->pll_clk_id != TAS2552_PLL_CLKIN_BCLK)
			वापस -EINVAL;

		pll_clkin = snd_soc_params_to_bclk(params);
		pll_clkin += tas2552->tdm_delay;
	पूर्ण

	pll_enable = snd_soc_component_पढ़ो(component, TAS2552_CFG_2) & TAS2552_PLL_ENABLE;
	snd_soc_component_update_bits(component, TAS2552_CFG_2, TAS2552_PLL_ENABLE, 0);

	अगर (pll_clkin == pll_clk)
		bypass_pll = true;

	अगर (bypass_pll) अणु
		/* By pass the PLL configuration */
		snd_soc_component_update_bits(component, TAS2552_PLL_CTRL_2,
				    TAS2552_PLL_BYPASS, TAS2552_PLL_BYPASS);
	पूर्ण अन्यथा अणु
		/* Fill in the PLL control रेजिस्टरs क्रम J & D
		 * pll_clk = (.5 * pll_clkin * J.D) / 2^p
		 * Need to fill in J and D here based on incoming freq
		 */
		अचिन्हित पूर्णांक d, q, t;
		u8 j;
		u8 pll_sel = (tas2552->pll_clk_id << 3) & TAS2552_PLL_SRC_MASK;
		u8 p = snd_soc_component_पढ़ो(component, TAS2552_PLL_CTRL_1);

		p = (p >> 7);

recalc:
		t = (pll_clk * 2) << p;
		j = t / pll_clkin;
		d = t % pll_clkin;
		t = pll_clkin / 10000;
		q = d / (t + 1);
		d = q + ((9999 - pll_clkin % 10000) * (d / t - q)) / 10000;

		अगर (d && (pll_clkin < 512000 || pll_clkin > 9200000)) अणु
			अगर (tas2552->pll_clk_id == TAS2552_PLL_CLKIN_BCLK) अणु
				pll_clkin = 1800000;
				pll_sel = (TAS2552_PLL_CLKIN_1_8_FIXED << 3) &
							TAS2552_PLL_SRC_MASK;
			पूर्ण अन्यथा अणु
				pll_clkin = snd_soc_params_to_bclk(params);
				pll_clkin += tas2552->tdm_delay;
				pll_sel = (TAS2552_PLL_CLKIN_BCLK << 3) &
							TAS2552_PLL_SRC_MASK;
			पूर्ण
			जाओ recalc;
		पूर्ण

		snd_soc_component_update_bits(component, TAS2552_CFG_1, TAS2552_PLL_SRC_MASK,
				    pll_sel);

		snd_soc_component_update_bits(component, TAS2552_PLL_CTRL_1,
				    TAS2552_PLL_J_MASK, j);
		/* Will clear the PLL_BYPASS bit */
		snd_soc_component_ग_लिखो(component, TAS2552_PLL_CTRL_2,
			      TAS2552_PLL_D_UPPER(d));
		snd_soc_component_ग_लिखो(component, TAS2552_PLL_CTRL_3,
			      TAS2552_PLL_D_LOWER(d));
	पूर्ण

	/* Restore PLL status */
	snd_soc_component_update_bits(component, TAS2552_CFG_2, TAS2552_PLL_ENABLE,
			    pll_enable);

	वापस 0;
पूर्ण

अटल पूर्णांक tas2552_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tas2552_data *tas2552 = dev_get_drvdata(component->dev);
	पूर्णांक cpf;
	u8 ser_ctrl1_reg, wclk_rate;

	चयन (params_width(params)) अणु
	हाल 16:
		ser_ctrl1_reg = TAS2552_WORDLENGTH_16BIT;
		cpf = 32 + tas2552->tdm_delay;
		अवरोध;
	हाल 20:
		ser_ctrl1_reg = TAS2552_WORDLENGTH_20BIT;
		cpf = 64 + tas2552->tdm_delay;
		अवरोध;
	हाल 24:
		ser_ctrl1_reg = TAS2552_WORDLENGTH_24BIT;
		cpf = 64 + tas2552->tdm_delay;
		अवरोध;
	हाल 32:
		ser_ctrl1_reg = TAS2552_WORDLENGTH_32BIT;
		cpf = 64 + tas2552->tdm_delay;
		अवरोध;
	शेष:
		dev_err(component->dev, "Not supported sample size: %d\n",
			params_width(params));
		वापस -EINVAL;
	पूर्ण

	अगर (cpf <= 32)
		ser_ctrl1_reg |= TAS2552_CLKSPERFRAME_32;
	अन्यथा अगर (cpf <= 64)
		ser_ctrl1_reg |= TAS2552_CLKSPERFRAME_64;
	अन्यथा अगर (cpf <= 128)
		ser_ctrl1_reg |= TAS2552_CLKSPERFRAME_128;
	अन्यथा
		ser_ctrl1_reg |= TAS2552_CLKSPERFRAME_256;

	snd_soc_component_update_bits(component, TAS2552_SER_CTRL_1,
			    TAS2552_WORDLENGTH_MASK | TAS2552_CLKSPERFRAME_MASK,
			    ser_ctrl1_reg);

	चयन (params_rate(params)) अणु
	हाल 8000:
		wclk_rate = TAS2552_WCLK_FREQ_8KHZ;
		अवरोध;
	हाल 11025:
	हाल 12000:
		wclk_rate = TAS2552_WCLK_FREQ_11_12KHZ;
		अवरोध;
	हाल 16000:
		wclk_rate = TAS2552_WCLK_FREQ_16KHZ;
		अवरोध;
	हाल 22050:
	हाल 24000:
		wclk_rate = TAS2552_WCLK_FREQ_22_24KHZ;
		अवरोध;
	हाल 32000:
		wclk_rate = TAS2552_WCLK_FREQ_32KHZ;
		अवरोध;
	हाल 44100:
	हाल 48000:
		wclk_rate = TAS2552_WCLK_FREQ_44_48KHZ;
		अवरोध;
	हाल 88200:
	हाल 96000:
		wclk_rate = TAS2552_WCLK_FREQ_88_96KHZ;
		अवरोध;
	हाल 176400:
	हाल 192000:
		wclk_rate = TAS2552_WCLK_FREQ_176_192KHZ;
		अवरोध;
	शेष:
		dev_err(component->dev, "Not supported sample rate: %d\n",
			params_rate(params));
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, TAS2552_CFG_3, TAS2552_WCLK_FREQ_MASK,
			    wclk_rate);

	वापस tas2552_setup_pll(component, params);
पूर्ण

#घोषणा TAS2552_DAI_FMT_MASK	(TAS2552_BCLKसूची | \
				 TAS2552_WCLKसूची | \
				 TAS2552_DATAFORMAT_MASK)
अटल पूर्णांक tas2552_prepare(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tas2552_data *tas2552 = snd_soc_component_get_drvdata(component);
	पूर्णांक delay = 0;

	/* TDM slot selection only valid in DSP_A/_B mode */
	अगर (tas2552->dai_fmt == SND_SOC_DAIFMT_DSP_A)
		delay += (tas2552->tdm_delay + 1);
	अन्यथा अगर (tas2552->dai_fmt == SND_SOC_DAIFMT_DSP_B)
		delay += tas2552->tdm_delay;

	/* Configure data delay */
	snd_soc_component_ग_लिखो(component, TAS2552_SER_CTRL_2, delay);

	वापस 0;
पूर्ण

अटल पूर्णांक tas2552_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tas2552_data *tas2552 = dev_get_drvdata(component->dev);
	u8 serial_क्रमmat;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		serial_क्रमmat = 0x00;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		serial_क्रमmat = TAS2552_WCLKसूची;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		serial_क्रमmat = TAS2552_BCLKसूची;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		serial_क्रमmat = (TAS2552_BCLKसूची | TAS2552_WCLKसूची);
		अवरोध;
	शेष:
		dev_vdbg(component->dev, "DAI Format master is not found\n");
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & (SND_SOC_DAIFMT_FORMAT_MASK |
		       SND_SOC_DAIFMT_INV_MASK)) अणु
	हाल (SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF):
		अवरोध;
	हाल (SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_IB_NF):
	हाल (SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_IB_NF):
		serial_क्रमmat |= TAS2552_DATAFORMAT_DSP;
		अवरोध;
	हाल (SND_SOC_DAIFMT_RIGHT_J | SND_SOC_DAIFMT_NB_NF):
		serial_क्रमmat |= TAS2552_DATAFORMAT_RIGHT_J;
		अवरोध;
	हाल (SND_SOC_DAIFMT_LEFT_J | SND_SOC_DAIFMT_NB_NF):
		serial_क्रमmat |= TAS2552_DATAFORMAT_LEFT_J;
		अवरोध;
	शेष:
		dev_vdbg(component->dev, "DAI Format is not found\n");
		वापस -EINVAL;
	पूर्ण
	tas2552->dai_fmt = fmt & SND_SOC_DAIFMT_FORMAT_MASK;

	snd_soc_component_update_bits(component, TAS2552_SER_CTRL_1, TAS2552_DAI_FMT_MASK,
			    serial_क्रमmat);
	वापस 0;
पूर्ण

अटल पूर्णांक tas2552_set_dai_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
				  अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tas2552_data *tas2552 = dev_get_drvdata(component->dev);
	u8 reg, mask, val;

	चयन (clk_id) अणु
	हाल TAS2552_PLL_CLKIN_MCLK:
	हाल TAS2552_PLL_CLKIN_IVCLKIN:
		अगर (freq < 512000 || freq > 24576000) अणु
			/* out of range PLL_CLKIN, fall back to use BCLK */
			dev_warn(component->dev, "Out of range PLL_CLKIN: %u\n",
				 freq);
			clk_id = TAS2552_PLL_CLKIN_BCLK;
			freq = 0;
		पूर्ण
		fallthrough;
	हाल TAS2552_PLL_CLKIN_BCLK:
	हाल TAS2552_PLL_CLKIN_1_8_FIXED:
		mask = TAS2552_PLL_SRC_MASK;
		val = (clk_id << 3) & mask; /* bit 4:5 in the रेजिस्टर */
		reg = TAS2552_CFG_1;
		tas2552->pll_clk_id = clk_id;
		tas2552->pll_clkin = freq;
		अवरोध;
	हाल TAS2552_PDM_CLK_PLL:
	हाल TAS2552_PDM_CLK_IVCLKIN:
	हाल TAS2552_PDM_CLK_BCLK:
	हाल TAS2552_PDM_CLK_MCLK:
		mask = TAS2552_PDM_CLK_SEL_MASK;
		val = (clk_id >> 1) & mask; /* bit 0:1 in the रेजिस्टर */
		reg = TAS2552_PDM_CFG;
		tas2552->pdm_clk_id = clk_id;
		tas2552->pdm_clk = freq;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid clk id: %d\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, reg, mask, val);

	वापस 0;
पूर्ण

अटल पूर्णांक tas2552_set_dai_tdm_slot(काष्ठा snd_soc_dai *dai,
				    अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
				    पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tas2552_data *tas2552 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक lsb;

	अगर (unlikely(!tx_mask)) अणु
		dev_err(component->dev, "tx masks need to be non 0\n");
		वापस -EINVAL;
	पूर्ण

	/* TDM based on DSP mode requires slots to be adjacent */
	lsb = __ffs(tx_mask);
	अगर ((lsb + 1) != __fls(tx_mask)) अणु
		dev_err(component->dev, "Invalid mask, slots must be adjacent\n");
		वापस -EINVAL;
	पूर्ण

	tas2552->tdm_delay = lsb * slot_width;

	/* DOUT in high-impedance on inactive bit घड़ीs */
	snd_soc_component_update_bits(component, TAS2552_DOUT,
			    TAS2552_SDOUT_TRISTATE, TAS2552_SDOUT_TRISTATE);

	वापस 0;
पूर्ण

अटल पूर्णांक tas2552_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	u8 cfg1_reg = 0;
	काष्ठा snd_soc_component *component = dai->component;

	अगर (mute)
		cfg1_reg |= TAS2552_MUTE;

	snd_soc_component_update_bits(component, TAS2552_CFG_1, TAS2552_MUTE, cfg1_reg);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक tas2552_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tas2552_data *tas2552 = dev_get_drvdata(dev);

	tas2552_sw_shutकरोwn(tas2552, 1);

	regcache_cache_only(tas2552->regmap, true);
	regcache_mark_dirty(tas2552->regmap);

	gpiod_set_value(tas2552->enable_gpio, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक tas2552_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tas2552_data *tas2552 = dev_get_drvdata(dev);

	gpiod_set_value(tas2552->enable_gpio, 1);

	tas2552_sw_shutकरोwn(tas2552, 0);

	regcache_cache_only(tas2552->regmap, false);
	regcache_sync(tas2552->regmap);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops tas2552_pm = अणु
	SET_RUNTIME_PM_OPS(tas2552_runसमय_suspend, tas2552_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops tas2552_speaker_dai_ops = अणु
	.hw_params	= tas2552_hw_params,
	.prepare	= tas2552_prepare,
	.set_sysclk	= tas2552_set_dai_sysclk,
	.set_fmt	= tas2552_set_dai_fmt,
	.set_tdm_slot	= tas2552_set_dai_tdm_slot,
	.mute_stream	= tas2552_mute,
	.no_capture_mute = 1,
पूर्ण;

/* Formats supported by TAS2552 driver. */
#घोषणा TAS2552_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
			 SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

/* TAS2552 dai काष्ठाure. */
अटल काष्ठा snd_soc_dai_driver tas2552_dai[] = अणु
	अणु
		.name = "tas2552-amplifier",
		.playback = अणु
			.stream_name = "Playback",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = TAS2552_FORMATS,
		पूर्ण,
		.ops = &tas2552_speaker_dai_ops,
	पूर्ण,
पूर्ण;

/*
 * DAC digital volumes. From -7 to 24 dB in 1 dB steps
 */
अटल DECLARE_TLV_DB_SCALE(dac_tlv, -700, 100, 0);

अटल स्थिर अक्षर * स्थिर tas2552_din_source_select[] = अणु
	"Muted",
	"Left",
	"Right",
	"Left + Right average",
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(tas2552_din_source_क्रमागत,
			    TAS2552_CFG_3, 3,
			    tas2552_din_source_select);

अटल स्थिर काष्ठा snd_kcontrol_new tas2552_snd_controls[] = अणु
	SOC_SINGLE_TLV("Speaker Driver Playback Volume",
			 TAS2552_PGA_GAIN, 0, 0x1f, 0, dac_tlv),
	SOC_ENUM("DIN source", tas2552_din_source_क्रमागत),
पूर्ण;

अटल पूर्णांक tas2552_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas2552_data *tas2552 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	tas2552->component = component;

	ret = regulator_bulk_enable(ARRAY_SIZE(tas2552->supplies),
				    tas2552->supplies);

	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to enable supplies: %d\n",
			ret);
		वापस ret;
	पूर्ण

	gpiod_set_value(tas2552->enable_gpio, 1);

	ret = pm_runसमय_get_sync(component->dev);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Enabling device failed: %d\n",
			ret);
		जाओ probe_fail;
	पूर्ण

	snd_soc_component_update_bits(component, TAS2552_CFG_1, TAS2552_MUTE, TAS2552_MUTE);
	snd_soc_component_ग_लिखो(component, TAS2552_CFG_3, TAS2552_I2S_OUT_SEL |
					    TAS2552_DIN_SRC_SEL_AVG_L_R);
	snd_soc_component_ग_लिखो(component, TAS2552_OUTPUT_DATA,
		      TAS2552_PDM_DATA_SEL_V_I |
		      TAS2552_R_DATA_OUT(TAS2552_DATA_OUT_V_DATA));
	snd_soc_component_ग_लिखो(component, TAS2552_BOOST_APT_CTRL, TAS2552_APT_DELAY_200 |
						     TAS2552_APT_THRESH_20_17);

	snd_soc_component_ग_लिखो(component, TAS2552_CFG_2, TAS2552_BOOST_EN | TAS2552_APT_EN |
					    TAS2552_LIM_EN);

	वापस 0;

probe_fail:
	pm_runसमय_put_noidle(component->dev);
	gpiod_set_value(tas2552->enable_gpio, 0);

	regulator_bulk_disable(ARRAY_SIZE(tas2552->supplies),
					tas2552->supplies);
	वापस ret;
पूर्ण

अटल व्योम tas2552_component_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas2552_data *tas2552 = snd_soc_component_get_drvdata(component);

	pm_runसमय_put(component->dev);

	gpiod_set_value(tas2552->enable_gpio, 0);
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक tas2552_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas2552_data *tas2552 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = regulator_bulk_disable(ARRAY_SIZE(tas2552->supplies),
					tas2552->supplies);

	अगर (ret != 0)
		dev_err(component->dev, "Failed to disable supplies: %d\n",
			ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tas2552_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas2552_data *tas2552 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(tas2552->supplies),
				    tas2552->supplies);

	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to enable supplies: %d\n",
			ret);
	पूर्ण

	वापस ret;
पूर्ण
#अन्यथा
#घोषणा tas2552_suspend शून्य
#घोषणा tas2552_resume शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_tas2552 = अणु
	.probe			= tas2552_component_probe,
	.हटाओ			= tas2552_component_हटाओ,
	.suspend		= tas2552_suspend,
	.resume			= tas2552_resume,
	.controls		= tas2552_snd_controls,
	.num_controls		= ARRAY_SIZE(tas2552_snd_controls),
	.dapm_widमाला_लो		= tas2552_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(tas2552_dapm_widमाला_लो),
	.dapm_routes		= tas2552_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(tas2552_audio_map),
	.idle_bias_on		= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config tas2552_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = TAS2552_MAX_REG,
	.reg_शेषs = tas2552_reg_defs,
	.num_reg_शेषs = ARRAY_SIZE(tas2552_reg_defs),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक tas2552_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev;
	काष्ठा tas2552_data *data;
	पूर्णांक ret;
	पूर्णांक i;

	dev = &client->dev;
	data = devm_kzalloc(&client->dev, माप(*data), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	data->enable_gpio = devm_gpiod_get_optional(dev, "enable",
						    GPIOD_OUT_LOW);
	अगर (IS_ERR(data->enable_gpio))
		वापस PTR_ERR(data->enable_gpio);

	data->tas2552_client = client;
	data->regmap = devm_regmap_init_i2c(client, &tas2552_regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		ret = PTR_ERR(data->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(data->supplies); i++)
		data->supplies[i].supply = tas2552_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(data->supplies),
				      data->supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	pm_runसमय_set_active(&client->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&client->dev, 1000);
	pm_runसमय_use_स्वतःsuspend(&client->dev);
	pm_runसमय_enable(&client->dev);
	pm_runसमय_mark_last_busy(&client->dev);
	pm_runसमय_put_sync_स्वतःsuspend(&client->dev);

	dev_set_drvdata(&client->dev, data);

	ret = devm_snd_soc_रेजिस्टर_component(&client->dev,
				      &soc_component_dev_tas2552,
				      tas2552_dai, ARRAY_SIZE(tas2552_dai));
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to register component: %d\n", ret);
		pm_runसमय_get_noresume(&client->dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tas2552_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	pm_runसमय_disable(&client->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tas2552_id[] = अणु
	अणु "tas2552", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tas2552_id);

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id tas2552_of_match[] = अणु
	अणु .compatible = "ti,tas2552", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tas2552_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver tas2552_i2c_driver = अणु
	.driver = अणु
		.name = "tas2552",
		.of_match_table = of_match_ptr(tas2552_of_match),
		.pm = &tas2552_pm,
	पूर्ण,
	.probe = tas2552_probe,
	.हटाओ = tas2552_i2c_हटाओ,
	.id_table = tas2552_id,
पूर्ण;

module_i2c_driver(tas2552_i2c_driver);

MODULE_AUTHOR("Dan Muprhy <dmurphy@ti.com>");
MODULE_DESCRIPTION("TAS2552 Audio amplifier driver");
MODULE_LICENSE("GPL");
