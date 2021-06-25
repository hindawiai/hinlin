<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// rt1016.c  --  RT1016 ALSA SoC audio amplअगरier driver
//
// Copyright 2020 Realtek Semiconductor Corp.
// Author: Oder Chiou <oder_chiou@realtek.com>
//

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
#समावेश "rt1016.h"

अटल स्थिर काष्ठा reg_sequence rt1016_patch[] = अणु
	अणुRT1016_VOL_CTRL_3,	0x8900पूर्ण,
	अणुRT1016_ANA_CTRL_1,	0xa002पूर्ण,
	अणुRT1016_ANA_CTRL_2,	0x0002पूर्ण,
	अणुRT1016_CLOCK_4,	0x6700पूर्ण,
	अणुRT1016_CLASSD_3,	0xdc55पूर्ण,
	अणुRT1016_CLASSD_4,	0x376aपूर्ण,
	अणुRT1016_CLASSD_5,	0x009fपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष rt1016_reg[] = अणु
	अणु0x00, 0x0000पूर्ण,
	अणु0x01, 0x5400पूर्ण,
	अणु0x02, 0x5506पूर्ण,
	अणु0x03, 0xf800पूर्ण,
	अणु0x04, 0x0000पूर्ण,
	अणु0x05, 0xbfbfपूर्ण,
	अणु0x06, 0x8900पूर्ण,
	अणु0x07, 0xa002पूर्ण,
	अणु0x08, 0x0000पूर्ण,
	अणु0x09, 0x0000पूर्ण,
	अणु0x0a, 0x0000पूर्ण,
	अणु0x0c, 0x0000पूर्ण,
	अणु0x0d, 0x0000पूर्ण,
	अणु0x0e, 0x10ecपूर्ण,
	अणु0x0f, 0x6595पूर्ण,
	अणु0x11, 0x0002पूर्ण,
	अणु0x1c, 0x0000पूर्ण,
	अणु0x1d, 0x0000पूर्ण,
	अणु0x1e, 0x0000पूर्ण,
	अणु0x1f, 0xf000पूर्ण,
	अणु0x20, 0x0000पूर्ण,
	अणु0x21, 0x6000पूर्ण,
	अणु0x22, 0x0000पूर्ण,
	अणु0x23, 0x6700पूर्ण,
	अणु0x24, 0x0000पूर्ण,
	अणु0x25, 0x0000पूर्ण,
	अणु0x26, 0x0000पूर्ण,
	अणु0x40, 0x0018पूर्ण,
	अणु0x60, 0x00a5पूर्ण,
	अणु0x80, 0x0010पूर्ण,
	अणु0x81, 0x0009पूर्ण,
	अणु0x82, 0x0000पूर्ण,
	अणु0x83, 0x0000पूर्ण,
	अणु0xa0, 0x0700पूर्ण,
	अणु0xc0, 0x0080पूर्ण,
	अणु0xc1, 0x02a0पूर्ण,
	अणु0xc2, 0x1400पूर्ण,
	अणु0xc3, 0x0a4aपूर्ण,
	अणु0xc4, 0x552aपूर्ण,
	अणु0xc5, 0x087eपूर्ण,
	अणु0xc6, 0x0020पूर्ण,
	अणु0xc7, 0xa833पूर्ण,
	अणु0xc8, 0x0433पूर्ण,
	अणु0xc9, 0x8040पूर्ण,
	अणु0xca, 0xdc55पूर्ण,
	अणु0xcb, 0x376aपूर्ण,
	अणु0xcc, 0x009fपूर्ण,
	अणु0xcf, 0x0020पूर्ण,
पूर्ण;

अटल bool rt1016_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT1016_ANA_FLAG:
	हाल RT1016_VERSION2_ID:
	हाल RT1016_VERSION1_ID:
	हाल RT1016_VENDER_ID:
	हाल RT1016_DEVICE_ID:
	हाल RT1016_TEST_SIGNAL:
	हाल RT1016_SC_CTRL_1:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt1016_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT1016_RESET:
	हाल RT1016_PADS_CTRL_1:
	हाल RT1016_PADS_CTRL_2:
	हाल RT1016_I2C_CTRL:
	हाल RT1016_VOL_CTRL_1:
	हाल RT1016_VOL_CTRL_2:
	हाल RT1016_VOL_CTRL_3:
	हाल RT1016_ANA_CTRL_1:
	हाल RT1016_MUX_SEL:
	हाल RT1016_RX_I2S_CTRL:
	हाल RT1016_ANA_FLAG:
	हाल RT1016_VERSION2_ID:
	हाल RT1016_VERSION1_ID:
	हाल RT1016_VENDER_ID:
	हाल RT1016_DEVICE_ID:
	हाल RT1016_ANA_CTRL_2:
	हाल RT1016_TEST_SIGNAL:
	हाल RT1016_TEST_CTRL_1:
	हाल RT1016_TEST_CTRL_2:
	हाल RT1016_TEST_CTRL_3:
	हाल RT1016_CLOCK_1:
	हाल RT1016_CLOCK_2:
	हाल RT1016_CLOCK_3:
	हाल RT1016_CLOCK_4:
	हाल RT1016_CLOCK_5:
	हाल RT1016_CLOCK_6:
	हाल RT1016_CLOCK_7:
	हाल RT1016_I2S_CTRL:
	हाल RT1016_DAC_CTRL_1:
	हाल RT1016_SC_CTRL_1:
	हाल RT1016_SC_CTRL_2:
	हाल RT1016_SC_CTRL_3:
	हाल RT1016_SC_CTRL_4:
	हाल RT1016_SIL_DET:
	हाल RT1016_SYS_CLK:
	हाल RT1016_BIAS_CUR:
	हाल RT1016_DAC_CTRL_2:
	हाल RT1016_LDO_CTRL:
	हाल RT1016_CLASSD_1:
	हाल RT1016_PLL1:
	हाल RT1016_PLL2:
	हाल RT1016_PLL3:
	हाल RT1016_CLASSD_2:
	हाल RT1016_CLASSD_OUT:
	हाल RT1016_CLASSD_3:
	हाल RT1016_CLASSD_4:
	हाल RT1016_CLASSD_5:
	हाल RT1016_PWR_CTRL:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(dac_vol_tlv, -9550, 50, 0);

अटल स्थिर काष्ठा snd_kcontrol_new rt1016_snd_controls[] = अणु
	SOC_DOUBLE_TLV("DAC Playback Volume", RT1016_VOL_CTRL_2,
		RT1016_L_VOL_SFT, RT1016_R_VOL_SFT, 191, 0, dac_vol_tlv),
	SOC_DOUBLE("DAC Playback Switch", RT1016_VOL_CTRL_1,
		RT1016_DA_MUTE_L_SFT, RT1016_DA_MUTE_R_SFT, 1, 1),
पूर्ण;

अटल पूर्णांक rt1016_is_sys_clk_from_pll(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(source->dapm);
	काष्ठा rt1016_priv *rt1016 = snd_soc_component_get_drvdata(component);

	अगर (rt1016->sysclk_src == RT1016_SCLK_S_PLL)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/* Interface data select */
अटल स्थिर अक्षर * स्थिर rt1016_data_select[] = अणु
	"L/R", "R/L", "L/L", "R/R"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt1016_अगर_data_swap_क्रमागत,
	RT1016_I2S_CTRL, RT1016_I2S_DATA_SWAP_SFT, rt1016_data_select);

अटल स्थिर काष्ठा snd_kcontrol_new rt1016_अगर_data_swap_mux =
	SOC_DAPM_ENUM("Data Swap Mux", rt1016_अगर_data_swap_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget rt1016_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MUX("Data Swap Mux", SND_SOC_NOPM, 0, 0,
			&rt1016_अगर_data_swap_mux),

	SND_SOC_DAPM_SUPPLY("DAC Filter", RT1016_CLOCK_3,
		RT1016_PWR_DAC_FILTER_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAMOD", RT1016_CLOCK_3, RT1016_PWR_DACMOD_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("FIFO", RT1016_CLOCK_3, RT1016_PWR_CLK_FIFO_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Pure DC", RT1016_CLOCK_3,
		RT1016_PWR_CLK_PUREDC_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CLK Silence Det", RT1016_CLOCK_3,
		RT1016_PWR_SIL_DET_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("RC 25M", RT1016_CLOCK_3, RT1016_PWR_RC_25M_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL1", RT1016_CLOCK_3, RT1016_PWR_PLL1_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("ANA CTRL", RT1016_CLOCK_3, RT1016_PWR_ANA_CTRL_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CLK SYS", RT1016_CLOCK_3, RT1016_PWR_CLK_SYS_BIT,
		0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("LRCK Det", RT1016_CLOCK_4, RT1016_PWR_LRCK_DET_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("BCLK Det", RT1016_CLOCK_4, RT1016_PWR_BCLK_DET_BIT,
		0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("CKGEN DAC", RT1016_DAC_CTRL_2,
		RT1016_CKGEN_DAC_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("VCM SLOW", RT1016_CLASSD_1, RT1016_VCM_SLOW_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Silence Det", RT1016_SIL_DET,
		RT1016_SIL_DET_EN_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLL2", RT1016_PLL2, RT1016_PLL2_EN_BIT, 0, शून्य,
		0),

	SND_SOC_DAPM_SUPPLY_S("BG1 BG2", 1, RT1016_PWR_CTRL,
		RT1016_PWR_BG_1_2_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("MBIAS BG", 1, RT1016_PWR_CTRL,
		RT1016_PWR_MBIAS_BG_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("PLL", 1, RT1016_PWR_CTRL, RT1016_PWR_PLL_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("BASIC", 1, RT1016_PWR_CTRL, RT1016_PWR_BASIC_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("CLASS D", 1, RT1016_PWR_CTRL,
		RT1016_PWR_CLSD_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("25M", 1, RT1016_PWR_CTRL, RT1016_PWR_25M_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DACL", 1, RT1016_PWR_CTRL, RT1016_PWR_DACL_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("DACR", 1, RT1016_PWR_CTRL, RT1016_PWR_DACR_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("LDO2", 1, RT1016_PWR_CTRL, RT1016_PWR_LDO2_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("VREF", 1, RT1016_PWR_CTRL, RT1016_PWR_VREF_BIT,
		0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("MBIAS", 1, RT1016_PWR_CTRL, RT1016_PWR_MBIAS_BIT,
		0, शून्य, 0),

	SND_SOC_DAPM_AIF_IN("AIFRX", "AIF Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC", शून्य, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_OUTPUT("SPO"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt1016_dapm_routes[] = अणु
	अणु "Data Swap Mux", "L/R", "AIFRX" पूर्ण,
	अणु "Data Swap Mux", "R/L", "AIFRX" पूर्ण,
	अणु "Data Swap Mux", "L/L", "AIFRX" पूर्ण,
	अणु "Data Swap Mux", "R/R", "AIFRX" पूर्ण,

	अणु "DAC", शून्य, "DAC Filter" पूर्ण,
	अणु "DAC", शून्य, "DAMOD" पूर्ण,
	अणु "DAC", शून्य, "FIFO" पूर्ण,
	अणु "DAC", शून्य, "Pure DC" पूर्ण,
	अणु "DAC", शून्य, "Silence Det" पूर्ण,
	अणु "DAC", शून्य, "ANA CTRL" पूर्ण,
	अणु "DAC", शून्य, "CLK SYS" पूर्ण,
	अणु "DAC", शून्य, "LRCK Det" पूर्ण,
	अणु "DAC", शून्य, "BCLK Det" पूर्ण,
	अणु "DAC", शून्य, "CKGEN DAC" पूर्ण,
	अणु "DAC", शून्य, "VCM SLOW" पूर्ण,

	अणु "PLL", शून्य, "PLL1" पूर्ण,
	अणु "PLL", शून्य, "PLL2" पूर्ण,
	अणु "25M", शून्य, "RC 25M" पूर्ण,
	अणु "Silence Det", शून्य, "CLK Silence Det" पूर्ण,

	अणु "DAC", शून्य, "Data Swap Mux" पूर्ण,
	अणु "DAC", शून्य, "BG1 BG2" पूर्ण,
	अणु "DAC", शून्य, "MBIAS BG" पूर्ण,
	अणु "DAC", शून्य, "PLL", rt1016_is_sys_clk_from_pllपूर्ण,
	अणु "DAC", शून्य, "BASIC" पूर्ण,
	अणु "DAC", शून्य, "CLASS D" पूर्ण,
	अणु "DAC", शून्य, "25M" पूर्ण,
	अणु "DAC", शून्य, "DACL" पूर्ण,
	अणु "DAC", शून्य, "DACR" पूर्ण,
	अणु "DAC", शून्य, "LDO2" पूर्ण,
	अणु "DAC", शून्य, "VREF" पूर्ण,
	अणु "DAC", शून्य, "MBIAS" पूर्ण,

	अणु "SPO", शून्य, "DAC" पूर्ण,
पूर्ण;

अटल पूर्णांक rt1016_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt1016_priv *rt1016 = snd_soc_component_get_drvdata(component);
	पूर्णांक pre_भाग, bclk_ms, frame_size;
	अचिन्हित पूर्णांक val_len = 0;

	rt1016->lrck = params_rate(params);
	pre_भाग = rl6231_get_clk_info(rt1016->sysclk, rt1016->lrck);
	अगर (pre_भाग < 0) अणु
		dev_err(component->dev, "Unsupported clock rate\n");
		वापस -EINVAL;
	पूर्ण

	frame_size = snd_soc_params_to_frame_size(params);
	अगर (frame_size < 0) अणु
		dev_err(component->dev, "Unsupported frame size: %d\n",
			frame_size);
		वापस -EINVAL;
	पूर्ण

	bclk_ms = frame_size > 32;
	rt1016->bclk = rt1016->lrck * (32 << bclk_ms);

	अगर (bclk_ms && rt1016->master)
		snd_soc_component_update_bits(component, RT1016_I2S_CTRL,
			RT1016_I2S_BCLK_MS_MASK, RT1016_I2S_BCLK_MS_64);

	dev_dbg(component->dev, "lrck is %dHz and pre_div is %d for iis %d\n",
				rt1016->lrck, pre_भाग, dai->id);

	चयन (params_width(params)) अणु
	हाल 16:
		val_len = RT1016_I2S_DL_16;
		अवरोध;
	हाल 20:
		val_len = RT1016_I2S_DL_20;
		अवरोध;
	हाल 24:
		val_len = RT1016_I2S_DL_24;
		अवरोध;
	हाल 32:
		val_len = RT1016_I2S_DL_32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, RT1016_I2S_CTRL,
		RT1016_I2S_DL_MASK, val_len);
	snd_soc_component_update_bits(component, RT1016_CLOCK_2,
		RT1016_FS_PD_MASK | RT1016_OSR_PD_MASK,
		((pre_भाग + 3) << RT1016_FS_PD_SFT) |
		(pre_भाग << RT1016_OSR_PD_SFT));

	वापस 0;
पूर्ण

अटल पूर्णांक rt1016_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt1016_priv *rt1016 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		reg_val |= RT1016_I2S_MS_M;
		rt1016->master = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		reg_val |= RT1016_I2S_MS_S;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		reg_val |= RT1016_I2S_BCLK_POL_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;

	हाल SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT1016_I2S_DF_LEFT;
		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT1016_I2S_DF_PCM_A;
		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_B:
		reg_val |= RT1016_I2S_DF_PCM_B;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, RT1016_I2S_CTRL,
			RT1016_I2S_MS_MASK | RT1016_I2S_BCLK_POL_MASK |
			RT1016_I2S_DF_MASK, reg_val);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1016_set_component_sysclk(काष्ठा snd_soc_component *component,
		पूर्णांक clk_id, पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा rt1016_priv *rt1016 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;

	अगर (freq == rt1016->sysclk && clk_id == rt1016->sysclk_src)
		वापस 0;

	चयन (clk_id) अणु
	हाल RT1016_SCLK_S_MCLK:
		reg_val |= RT1016_CLK_SYS_SEL_MCLK;
		अवरोध;

	हाल RT1016_SCLK_S_PLL:
		reg_val |= RT1016_CLK_SYS_SEL_PLL;
		अवरोध;

	शेष:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	rt1016->sysclk = freq;
	rt1016->sysclk_src = clk_id;

	dev_dbg(component->dev, "Sysclk is %dHz and clock id is %d\n",
		freq, clk_id);

	snd_soc_component_update_bits(component, RT1016_CLOCK_1,
			RT1016_CLK_SYS_SEL_MASK, reg_val);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1016_set_component_pll(काष्ठा snd_soc_component *component,
		पूर्णांक pll_id, पूर्णांक source, अचिन्हित पूर्णांक freq_in,
		अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा rt1016_priv *rt1016 = snd_soc_component_get_drvdata(component);
	काष्ठा rl6231_pll_code pll_code;
	पूर्णांक ret;

	अगर (!freq_in || !freq_out) अणु
		dev_dbg(component->dev, "PLL disabled\n");

		rt1016->pll_in = 0;
		rt1016->pll_out = 0;

		वापस 0;
	पूर्ण

	अगर (source == rt1016->pll_src && freq_in == rt1016->pll_in &&
		freq_out == rt1016->pll_out)
		वापस 0;

	चयन (source) अणु
	हाल RT1016_PLL_S_MCLK:
		snd_soc_component_update_bits(component, RT1016_CLOCK_1,
			RT1016_PLL_SEL_MASK, RT1016_PLL_SEL_MCLK);
		अवरोध;

	हाल RT1016_PLL_S_BCLK:
		snd_soc_component_update_bits(component, RT1016_CLOCK_1,
			RT1016_PLL_SEL_MASK, RT1016_PLL_SEL_BCLK);
		अवरोध;

	शेष:
		dev_err(component->dev, "Unknown PLL Source %d\n", source);
		वापस -EINVAL;
	पूर्ण

	ret = rl6231_pll_calc(freq_in, freq_out * 4, &pll_code);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Unsupport input clock %d\n", freq_in);
		वापस ret;
	पूर्ण

	dev_dbg(component->dev, "mbypass=%d m=%d n=%d kbypass=%d k=%d\n",
		pll_code.m_bp, (pll_code.m_bp ? 0 : pll_code.m_code),
		pll_code.n_code, pll_code.k_bp,
		(pll_code.k_bp ? 0 : pll_code.k_code));

	snd_soc_component_ग_लिखो(component, RT1016_PLL1,
		((pll_code.m_bp ? 0 : pll_code.m_code) << RT1016_PLL_M_SFT) |
		(pll_code.m_bp << RT1016_PLL_M_BP_SFT) |
		pll_code.n_code);
	snd_soc_component_ग_लिखो(component, RT1016_PLL2,
		(pll_code.k_bp << RT1016_PLL_K_BP_SFT) |
		(pll_code.k_bp ? 0 : pll_code.k_code));

	rt1016->pll_in = freq_in;
	rt1016->pll_out = freq_out;
	rt1016->pll_src = source;

	वापस 0;
पूर्ण

अटल पूर्णांक rt1016_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1016_priv *rt1016 =
		snd_soc_component_get_drvdata(component);

	rt1016->component = component;

	वापस 0;
पूर्ण

अटल व्योम rt1016_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1016_priv *rt1016 = snd_soc_component_get_drvdata(component);

	regmap_ग_लिखो(rt1016->regmap, RT1016_RESET, 0);
पूर्ण

#घोषणा RT1016_STEREO_RATES SNDRV_PCM_RATE_8000_48000
#घोषणा RT1016_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S8)

अटल स्थिर काष्ठा snd_soc_dai_ops rt1016_aअगर_dai_ops = अणु
	.hw_params = rt1016_hw_params,
	.set_fmt = rt1016_set_dai_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt1016_dai[] = अणु
	अणु
		.name = "rt1016-aif",
		.id = 0,
		.playback = अणु
			.stream_name = "AIF Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT1016_STEREO_RATES,
			.क्रमmats = RT1016_FORMATS,
		पूर्ण,
		.ops = &rt1016_aअगर_dai_ops,
	पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rt1016_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1016_priv *rt1016 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt1016->regmap, true);
	regcache_mark_dirty(rt1016->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1016_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1016_priv *rt1016 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt1016->regmap, false);
	regcache_sync(rt1016->regmap);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा rt1016_suspend शून्य
#घोषणा rt1016_resume शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_rt1016 = अणु
	.probe = rt1016_probe,
	.हटाओ = rt1016_हटाओ,
	.suspend = rt1016_suspend,
	.resume = rt1016_resume,
	.controls = rt1016_snd_controls,
	.num_controls = ARRAY_SIZE(rt1016_snd_controls),
	.dapm_widमाला_लो = rt1016_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(rt1016_dapm_widमाला_लो),
	.dapm_routes = rt1016_dapm_routes,
	.num_dapm_routes = ARRAY_SIZE(rt1016_dapm_routes),
	.set_sysclk = rt1016_set_component_sysclk,
	.set_pll = rt1016_set_component_pll,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt1016_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = RT1016_PWR_CTRL,
	.अस्थिर_reg = rt1016_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = rt1016_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = rt1016_reg,
	.num_reg_शेषs = ARRAY_SIZE(rt1016_reg),
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id rt1016_i2c_id[] = अणु
	अणु "rt1016", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt1016_i2c_id);

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id rt1016_of_match[] = अणु
	अणु .compatible = "realtek,rt1016", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt1016_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id rt1016_acpi_match[] = अणु
	अणु"10EC1016", 0,पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rt1016_acpi_match);
#पूर्ण_अगर

अटल पूर्णांक rt1016_i2c_probe(काष्ठा i2c_client *i2c,
	स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rt1016_priv *rt1016;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	rt1016 = devm_kzalloc(&i2c->dev, माप(काष्ठा rt1016_priv),
				GFP_KERNEL);
	अगर (rt1016 == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, rt1016);

	rt1016->regmap = devm_regmap_init_i2c(i2c, &rt1016_regmap);
	अगर (IS_ERR(rt1016->regmap)) अणु
		ret = PTR_ERR(rt1016->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	regmap_पढ़ो(rt1016->regmap, RT1016_DEVICE_ID, &val);
	अगर (val != RT1016_DEVICE_ID_VAL) अणु
		dev_err(&i2c->dev,
			"Device with ID register %x is not rt1016\n", val);
		वापस -ENODEV;
	पूर्ण

	regmap_ग_लिखो(rt1016->regmap, RT1016_RESET, 0);

	ret = regmap_रेजिस्टर_patch(rt1016->regmap, rt1016_patch,
				    ARRAY_SIZE(rt1016_patch));
	अगर (ret != 0)
		dev_warn(&i2c->dev, "Failed to apply regmap patch: %d\n", ret);

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
		&soc_component_dev_rt1016,
		rt1016_dai, ARRAY_SIZE(rt1016_dai));
पूर्ण

अटल व्योम rt1016_i2c_shutकरोwn(काष्ठा i2c_client *client)
अणु
	काष्ठा rt1016_priv *rt1016 = i2c_get_clientdata(client);

	regmap_ग_लिखो(rt1016->regmap, RT1016_RESET, 0);
पूर्ण

अटल काष्ठा i2c_driver rt1016_i2c_driver = अणु
	.driver = अणु
		.name = "rt1016",
		.of_match_table = of_match_ptr(rt1016_of_match),
		.acpi_match_table = ACPI_PTR(rt1016_acpi_match),
	पूर्ण,
	.probe = rt1016_i2c_probe,
	.shutकरोwn = rt1016_i2c_shutकरोwn,
	.id_table = rt1016_i2c_id,
पूर्ण;
module_i2c_driver(rt1016_i2c_driver);

MODULE_DESCRIPTION("ASoC RT1016 driver");
MODULE_AUTHOR("Oder Chiou <oder_chiou@realtek.com>");
MODULE_LICENSE("GPL v2");
