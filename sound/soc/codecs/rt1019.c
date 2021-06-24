<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// rt1019.c  --  RT1019 ALSA SoC audio amplअगरier driver
// Author: Jack Yu <jack.yu@realtek.com>
//
// Copyright(c) 2021 Realtek Semiconductor Corp.
//
//

#समावेश <linux/acpi.h>
#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/gpपन.स>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "rl6231.h"
#समावेश "rt1019.h"

अटल स्थिर काष्ठा reg_शेष rt1019_reg[] = अणु
	अणु 0x0000, 0x00 पूर्ण,
	अणु 0x0011, 0x04 पूर्ण,
	अणु 0x0013, 0x00 पूर्ण,
	अणु 0x0019, 0x30 पूर्ण,
	अणु 0x001b, 0x01 पूर्ण,
	अणु 0x005c, 0x00 पूर्ण,
	अणु 0x005e, 0x10 पूर्ण,
	अणु 0x005f, 0xec पूर्ण,
	अणु 0x0061, 0x10 पूर्ण,
	अणु 0x0062, 0x19 पूर्ण,
	अणु 0x0066, 0x08 पूर्ण,
	अणु 0x0100, 0x80 पूर्ण,
	अणु 0x0100, 0x51 पूर्ण,
	अणु 0x0102, 0x23 पूर्ण,
	अणु 0x0311, 0x00 पूर्ण,
	अणु 0x0312, 0x3e पूर्ण,
	अणु 0x0313, 0x86 पूर्ण,
	अणु 0x0400, 0x03 पूर्ण,
	अणु 0x0401, 0x02 पूर्ण,
	अणु 0x0402, 0x01 पूर्ण,
	अणु 0x0504, 0xff पूर्ण,
	अणु 0x0505, 0x24 पूर्ण,
	अणु 0x0b00, 0x50 पूर्ण,
	अणु 0x0b01, 0xc3 पूर्ण,
पूर्ण;

अटल bool rt1019_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT1019_PWR_STRP_2:
	हाल RT1019_VER_ID:
	हाल RT1019_VEND_ID_1:
	हाल RT1019_VEND_ID_2:
	हाल RT1019_DEV_ID_1:
	हाल RT1019_DEV_ID_2:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt1019_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT1019_RESET:
	हाल RT1019_IDS_CTRL:
	हाल RT1019_ASEL_CTRL:
	हाल RT1019_PWR_STRP_2:
	हाल RT1019_BEEP_TONE:
	हाल RT1019_VER_ID:
	हाल RT1019_VEND_ID_1:
	हाल RT1019_VEND_ID_2:
	हाल RT1019_DEV_ID_1:
	हाल RT1019_DEV_ID_2:
	हाल RT1019_SDB_CTRL:
	हाल RT1019_CLK_TREE_1:
	हाल RT1019_CLK_TREE_2:
	हाल RT1019_CLK_TREE_3:
	हाल RT1019_PLL_1:
	हाल RT1019_PLL_2:
	हाल RT1019_PLL_3:
	हाल RT1019_TDM_1:
	हाल RT1019_TDM_2:
	हाल RT1019_TDM_3:
	हाल RT1019_DMIX_MONO_1:
	हाल RT1019_DMIX_MONO_2:
	हाल RT1019_BEEP_1:
	हाल RT1019_BEEP_2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(dac_vol_tlv, -9525, 75, 0);

अटल स्थिर अक्षर * स्थिर rt1019_din_source_select[] = अणु
	"Left",
	"Right",
	"Left + Right average",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt1019_mono_lr_sel, RT1019_IDS_CTRL, 0,
	rt1019_din_source_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt1019_snd_controls[] = अणु
	SOC_SINGLE_TLV("DAC Playback Volume", RT1019_DMIX_MONO_1, 0,
		127, 0, dac_vol_tlv),
	SOC_ENUM("Mono LR Select", rt1019_mono_lr_sel),
पूर्ण;

अटल पूर्णांक r1019_dac_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_ग_लिखो(component, RT1019_SDB_CTRL, 0xb);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_ग_लिखो(component, RT1019_SDB_CTRL, 0xa);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget rt1019_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("AIFRX", "AIF Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC_E("DAC", शून्य, SND_SOC_NOPM, 0, 0,
		r1019_dac_event, SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_OUTPUT("SPO"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt1019_dapm_routes[] = अणु
	अणु "DAC", शून्य, "AIFRX" पूर्ण,
	अणु "SPO", शून्य, "DAC" पूर्ण,
पूर्ण;

अटल पूर्णांक rt1019_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt1019_priv *rt1019 = snd_soc_component_get_drvdata(component);
	पूर्णांक pre_भाग, bclk_ms, frame_size;
	अचिन्हित पूर्णांक val_len = 0, sys_भाग_da_filter = 0;
	अचिन्हित पूर्णांक sys_dac_osr = 0, sys_fअगरo_clk = 0;
	अचिन्हित पूर्णांक sys_clk_cal = 0, sys_asrc_in = 0;

	rt1019->lrck = params_rate(params);
	pre_भाग = rl6231_get_clk_info(rt1019->sysclk, rt1019->lrck);
	अगर (pre_भाग < 0) अणु
		dev_err(component->dev, "Unsupported clock setting\n");
		वापस -EINVAL;
	पूर्ण

	frame_size = snd_soc_params_to_frame_size(params);
	अगर (frame_size < 0) अणु
		dev_err(component->dev, "Unsupported frame size: %d\n", frame_size);
		वापस -EINVAL;
	पूर्ण

	bclk_ms = frame_size > 32;
	rt1019->bclk = rt1019->lrck * (32 << bclk_ms);

	dev_dbg(dai->dev, "bclk is %dHz and lrck is %dHz\n",
		rt1019->bclk, rt1019->lrck);
	dev_dbg(dai->dev, "bclk_ms is %d and pre_div is %d for iis %d\n",
				bclk_ms, pre_भाग, dai->id);

	चयन (pre_भाग) अणु
	हाल 0:
		sys_भाग_da_filter = RT1019_SYS_DIV_DA_FIL_DIV1;
		sys_dac_osr = RT1019_SYS_DA_OSR_DIV1;
		sys_asrc_in = RT1019_ASRC_256FS_DIV1;
		sys_fअगरo_clk = RT1019_SEL_FIFO_DIV1;
		sys_clk_cal = RT1019_SEL_CLK_CAL_DIV1;
		अवरोध;
	हाल 1:
		sys_भाग_da_filter = RT1019_SYS_DIV_DA_FIL_DIV2;
		sys_dac_osr = RT1019_SYS_DA_OSR_DIV2;
		sys_asrc_in = RT1019_ASRC_256FS_DIV2;
		sys_fअगरo_clk = RT1019_SEL_FIFO_DIV2;
		sys_clk_cal = RT1019_SEL_CLK_CAL_DIV2;
		अवरोध;
	हाल 3:
		sys_भाग_da_filter = RT1019_SYS_DIV_DA_FIL_DIV4;
		sys_dac_osr = RT1019_SYS_DA_OSR_DIV4;
		sys_asrc_in = RT1019_ASRC_256FS_DIV4;
		sys_fअगरo_clk = RT1019_SEL_FIFO_DIV4;
		sys_clk_cal = RT1019_SEL_CLK_CAL_DIV4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		val_len = RT1019_I2S_DL_20;
		अवरोध;
	हाल 24:
		val_len = RT1019_I2S_DL_24;
		अवरोध;
	हाल 32:
		val_len = RT1019_I2S_DL_32;
		अवरोध;
	हाल 8:
		val_len = RT1019_I2S_DL_8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, RT1019_TDM_2, RT1019_I2S_DL_MASK,
			val_len);
	snd_soc_component_update_bits(component, RT1019_CLK_TREE_1,
			RT1019_SEL_FIFO_MASK, sys_fअगरo_clk);
	snd_soc_component_update_bits(component, RT1019_CLK_TREE_2,
			RT1019_SYS_DIV_DA_FIL_MASK | RT1019_SYS_DA_OSR_MASK |
			RT1019_ASRC_256FS_MASK, sys_भाग_da_filter | sys_dac_osr |
			sys_asrc_in);
	snd_soc_component_update_bits(component, RT1019_CLK_TREE_3,
			RT1019_SEL_CLK_CAL_MASK, sys_clk_cal);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1019_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक reg_val = 0, reg_val2 = 0;

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		reg_val2 |= RT1019_TDM_BCLK_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;

	हाल SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT1019_I2S_DF_LEFT;
		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT1019_I2S_DF_PCM_A_R;
		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_B:
		reg_val |= RT1019_I2S_DF_PCM_B_R;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, RT1019_TDM_2,
		RT1019_I2S_DF_MASK, reg_val);
	snd_soc_component_update_bits(component, RT1019_TDM_1,
		RT1019_TDM_BCLK_MASK, reg_val2);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1019_set_dai_sysclk(काष्ठा snd_soc_dai *dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt1019_priv *rt1019 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;

	अगर (freq == rt1019->sysclk && clk_id == rt1019->sysclk_src)
		वापस 0;

	चयन (clk_id) अणु
	हाल RT1019_SCLK_S_BCLK:
		reg_val |= RT1019_CLK_SYS_PRE_SEL_BCLK;
		अवरोध;

	हाल RT1019_SCLK_S_PLL:
		reg_val |= RT1019_CLK_SYS_PRE_SEL_PLL;
		अवरोध;

	शेष:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	rt1019->sysclk = freq;
	rt1019->sysclk_src = clk_id;

	dev_dbg(dai->dev, "Sysclk is %dHz and clock id is %d\n", freq, clk_id);

	snd_soc_component_update_bits(component, RT1019_CLK_TREE_1,
		RT1019_CLK_SYS_PRE_SEL_MASK, reg_val);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1019_set_dai_pll(काष्ठा snd_soc_dai *dai, पूर्णांक pll_id, पूर्णांक source,
			अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt1019_priv *rt1019 = snd_soc_component_get_drvdata(component);
	काष्ठा rl6231_pll_code pll_code;
	पूर्णांक ret;

	अगर (!freq_in || !freq_out) अणु
		dev_dbg(component->dev, "PLL disabled\n");
		rt1019->pll_in = 0;
		rt1019->pll_out = 0;
		वापस 0;
	पूर्ण

	अगर (source == rt1019->pll_src && freq_in == rt1019->pll_in &&
		freq_out == rt1019->pll_out)
		वापस 0;

	चयन (source) अणु
	हाल RT1019_PLL_S_BCLK:
		snd_soc_component_update_bits(component, RT1019_CLK_TREE_1,
			RT1019_PLL_SRC_MASK, RT1019_PLL_SRC_SEL_BCLK);
		अवरोध;

	हाल RT1019_PLL_S_RC25M:
		snd_soc_component_update_bits(component, RT1019_CLK_TREE_1,
			RT1019_PLL_SRC_MASK, RT1019_PLL_SRC_SEL_RC);
		अवरोध;

	शेष:
		dev_err(component->dev, "Unknown PLL source %d\n", source);
		वापस -EINVAL;
	पूर्ण

	ret = rl6231_pll_calc(freq_in, freq_out, &pll_code);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Unsupport input clock %d\n", freq_in);
		वापस ret;
	पूर्ण

	dev_dbg(component->dev, "bypass=%d m=%d n=%d k=%d\n",
		pll_code.m_bp, (pll_code.m_bp ? 0 : pll_code.m_code),
		pll_code.n_code, pll_code.k_code);

	snd_soc_component_update_bits(component, RT1019_PWR_STRP_2,
		RT1019_AUTO_BITS_SEL_MASK | RT1019_AUTO_CLK_SEL_MASK,
		RT1019_AUTO_BITS_SEL_MANU | RT1019_AUTO_CLK_SEL_MANU);
	snd_soc_component_update_bits(component, RT1019_PLL_1,
		RT1019_PLL_M_MASK | RT1019_PLL_M_BP_MASK | RT1019_PLL_Q_8_8_MASK,
		(pll_code.m_bp ? 0 : pll_code.m_code) << RT1019_PLL_M_SFT |
		pll_code.m_bp << RT1019_PLL_M_BP_SFT |
		((pll_code.n_code >> 8) & RT1019_PLL_Q_8_8_MASK));
	snd_soc_component_update_bits(component, RT1019_PLL_2,
		RT1019_PLL_Q_7_0_MASK, pll_code.n_code & RT1019_PLL_Q_7_0_MASK);
	snd_soc_component_update_bits(component, RT1019_PLL_3,
		RT1019_PLL_K_MASK, pll_code.k_code);

	rt1019->pll_in = freq_in;
	rt1019->pll_out = freq_out;
	rt1019->pll_src = source;

	वापस 0;
पूर्ण

अटल पूर्णांक rt1019_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
			अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक val = 0, rx_slotnum;
	पूर्णांक ret = 0, first_bit;

	चयन (slots) अणु
	हाल 4:
		val |= RT1019_I2S_TX_4CH;
		अवरोध;
	हाल 6:
		val |= RT1019_I2S_TX_6CH;
		अवरोध;
	हाल 8:
		val |= RT1019_I2S_TX_8CH;
		अवरोध;
	हाल 2:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (slot_width) अणु
	हाल 20:
		val |= RT1019_I2S_DL_20;
		अवरोध;
	हाल 24:
		val |= RT1019_I2S_DL_24;
		अवरोध;
	हाल 32:
		val |= RT1019_I2S_DL_32;
		अवरोध;
	हाल 8:
		val |= RT1019_I2S_DL_8;
		अवरोध;
	हाल 16:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Rx slot configuration */
	rx_slotnum = hweight_दीर्घ(rx_mask);
	अगर (rx_slotnum != 1) अणु
		ret = -EINVAL;
		dev_err(component->dev, "too many rx slots or zero slot\n");
		जाओ _set_tdm_err_;
	पूर्ण
	/* This is an assumption that the प्रणाली sends stereo audio to the
	 * amplअगरier typically. And the stereo audio is placed in slot 0/2/4/6
	 * as the starting slot. The users could select the channel from
	 * L/R/L+R by "Mono LR Select" control.
	 */
	first_bit = __ffs(rx_mask);
	चयन (first_bit) अणु
	हाल 0:
	हाल 2:
	हाल 4:
	हाल 6:
		snd_soc_component_update_bits(component,
			RT1019_TDM_3,
			RT1019_TDM_I2S_TX_L_DAC1_1_MASK |
			RT1019_TDM_I2S_TX_R_DAC1_1_MASK,
			(first_bit << RT1019_TDM_I2S_TX_L_DAC1_1_SFT) |
			((first_bit + 1) << RT1019_TDM_I2S_TX_R_DAC1_1_SFT));
		अवरोध;
	हाल 1:
	हाल 3:
	हाल 5:
	हाल 7:
		snd_soc_component_update_bits(component,
			RT1019_TDM_3,
			RT1019_TDM_I2S_TX_L_DAC1_1_MASK |
			RT1019_TDM_I2S_TX_R_DAC1_1_MASK,
			((first_bit - 1) << RT1019_TDM_I2S_TX_L_DAC1_1_SFT) |
			(first_bit << RT1019_TDM_I2S_TX_R_DAC1_1_SFT));
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ _set_tdm_err_;
	पूर्ण

	snd_soc_component_update_bits(component, RT1019_TDM_2,
		RT1019_I2S_CH_TX_MASK | RT1019_I2S_DF_MASK, val);

_set_tdm_err_:
	वापस ret;
पूर्ण

अटल पूर्णांक rt1019_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1019_priv *rt1019 = snd_soc_component_get_drvdata(component);

	rt1019->component = component;
	snd_soc_component_ग_लिखो(component, RT1019_SDB_CTRL, 0xa);

	वापस 0;
पूर्ण

#घोषणा RT1019_STEREO_RATES SNDRV_PCM_RATE_8000_192000
#घोषणा RT1019_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S8)

अटल स्थिर काष्ठा snd_soc_dai_ops rt1019_aअगर_dai_ops = अणु
	.hw_params = rt1019_hw_params,
	.set_fmt = rt1019_set_dai_fmt,
	.set_sysclk = rt1019_set_dai_sysclk,
	.set_pll = rt1019_set_dai_pll,
	.set_tdm_slot = rt1019_set_tdm_slot,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt1019_dai[] = अणु
	अणु
		.name = "rt1019-aif",
		.id = 0,
		.playback = अणु
			.stream_name = "AIF Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT1019_STEREO_RATES,
			.क्रमmats = RT1019_FORMATS,
		पूर्ण,
		.ops = &rt1019_aअगर_dai_ops,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_rt1019 = अणु
	.probe = rt1019_probe,
	.controls		= rt1019_snd_controls,
	.num_controls		= ARRAY_SIZE(rt1019_snd_controls),
	.dapm_widमाला_लो		= rt1019_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(rt1019_dapm_widमाला_लो),
	.dapm_routes		= rt1019_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(rt1019_dapm_routes),
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt1019_regmap = अणु
	.reg_bits = 16,
	.val_bits = 8,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
	.max_रेजिस्टर = RT1019_BEEP_2,
	.अस्थिर_reg = rt1019_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = rt1019_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = rt1019_reg,
	.num_reg_शेषs = ARRAY_SIZE(rt1019_reg),
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id rt1019_i2c_id[] = अणु
	अणु "rt1019", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt1019_i2c_id);

अटल स्थिर काष्ठा of_device_id rt1019_of_match[] = अणु
	अणु .compatible = "realtek,rt1019", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt1019_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id rt1019_acpi_match[] = अणु
	अणु "10EC1019", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rt1019_acpi_match);
#पूर्ण_अगर

अटल पूर्णांक rt1019_i2c_probe(काष्ठा i2c_client *i2c,
	स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rt1019_priv *rt1019;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val, val2, dev_id;

	rt1019 = devm_kzalloc(&i2c->dev, माप(काष्ठा rt1019_priv),
				GFP_KERNEL);
	अगर (!rt1019)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, rt1019);

	rt1019->regmap = devm_regmap_init_i2c(i2c, &rt1019_regmap);
	अगर (IS_ERR(rt1019->regmap)) अणु
		ret = PTR_ERR(rt1019->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	regmap_पढ़ो(rt1019->regmap, RT1019_DEV_ID_1, &val);
	regmap_पढ़ो(rt1019->regmap, RT1019_DEV_ID_2, &val2);
	dev_id = val << 8 | val2;
	अगर (dev_id != RT1019_DEVICE_ID_VAL && dev_id != RT1019_DEVICE_ID_VAL2) अणु
		dev_err(&i2c->dev,
			"Device with ID register 0x%x is not rt1019\n", dev_id);
		वापस -ENODEV;
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
		&soc_component_dev_rt1019, rt1019_dai, ARRAY_SIZE(rt1019_dai));
पूर्ण

अटल काष्ठा i2c_driver rt1019_i2c_driver = अणु
	.driver = अणु
		.name = "rt1019",
		.of_match_table = of_match_ptr(rt1019_of_match),
		.acpi_match_table = ACPI_PTR(rt1019_acpi_match),
	पूर्ण,
	.probe = rt1019_i2c_probe,
	.id_table = rt1019_i2c_id,
पूर्ण;
module_i2c_driver(rt1019_i2c_driver);

MODULE_DESCRIPTION("ASoC RT1019 driver");
MODULE_AUTHOR("Jack Yu <jack.yu@realtek.com>");
MODULE_LICENSE("GPL v2");
