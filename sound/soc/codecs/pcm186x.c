<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments PCM186x Universal Audio ADC
 *
 * Copyright (C) 2015-2017 Texas Instruments Incorporated - https://www.ti.com
 *	Andreas Dannenberg <dannenberg@ti.com>
 *	Andrew F. Davis <afd@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "pcm186x.h"

अटल स्थिर अक्षर * स्थिर pcm186x_supply_names[] = अणु
	"avdd",		/* Analog घातer supply. Connect to 3.3-V supply. */
	"dvdd",		/* Digital घातer supply. Connect to 3.3-V supply. */
	"iovdd",	/* I/O घातer supply. Connect to 3.3-V or 1.8-V. */
पूर्ण;
#घोषणा PCM186x_NUM_SUPPLIES ARRAY_SIZE(pcm186x_supply_names)

काष्ठा pcm186x_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data supplies[PCM186x_NUM_SUPPLIES];
	अचिन्हित पूर्णांक sysclk;
	अचिन्हित पूर्णांक tdm_offset;
	bool is_tdm_mode;
	bool is_master_mode;
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(pcm186x_pga_tlv, -1200, 50, 0);

अटल स्थिर काष्ठा snd_kcontrol_new pcm1863_snd_controls[] = अणु
	SOC_DOUBLE_R_S_TLV("ADC Capture Volume", PCM186X_PGA_VAL_CH1_L,
			   PCM186X_PGA_VAL_CH1_R, 0, -24, 80, 7, 0,
			   pcm186x_pga_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new pcm1865_snd_controls[] = अणु
	SOC_DOUBLE_R_S_TLV("ADC1 Capture Volume", PCM186X_PGA_VAL_CH1_L,
			   PCM186X_PGA_VAL_CH1_R, 0, -24, 80, 7, 0,
			   pcm186x_pga_tlv),
	SOC_DOUBLE_R_S_TLV("ADC2 Capture Volume", PCM186X_PGA_VAL_CH2_L,
			   PCM186X_PGA_VAL_CH2_R, 0, -24, 80, 7, 0,
			   pcm186x_pga_tlv),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pcm186x_adc_input_channel_sel_value[] = अणु
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
	0x10, 0x20, 0x30
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcm186x_adcl_input_channel_sel_text[] = अणु
	"No Select",
	"VINL1[SE]",					/* Default क्रम ADC1L */
	"VINL2[SE]",					/* Default क्रम ADC2L */
	"VINL2[SE] + VINL1[SE]",
	"VINL3[SE]",
	"VINL3[SE] + VINL1[SE]",
	"VINL3[SE] + VINL2[SE]",
	"VINL3[SE] + VINL2[SE] + VINL1[SE]",
	"VINL4[SE]",
	"VINL4[SE] + VINL1[SE]",
	"VINL4[SE] + VINL2[SE]",
	"VINL4[SE] + VINL2[SE] + VINL1[SE]",
	"VINL4[SE] + VINL3[SE]",
	"VINL4[SE] + VINL3[SE] + VINL1[SE]",
	"VINL4[SE] + VINL3[SE] + VINL2[SE]",
	"VINL4[SE] + VINL3[SE] + VINL2[SE] + VINL1[SE]",
	"{VIN1P, VIN1M}[DIFF]",
	"{VIN4P, VIN4M}[DIFF]",
	"{VIN1P, VIN1M}[DIFF] + {VIN4P, VIN4M}[DIFF]"
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcm186x_adcr_input_channel_sel_text[] = अणु
	"No Select",
	"VINR1[SE]",					/* Default क्रम ADC1R */
	"VINR2[SE]",					/* Default क्रम ADC2R */
	"VINR2[SE] + VINR1[SE]",
	"VINR3[SE]",
	"VINR3[SE] + VINR1[SE]",
	"VINR3[SE] + VINR2[SE]",
	"VINR3[SE] + VINR2[SE] + VINR1[SE]",
	"VINR4[SE]",
	"VINR4[SE] + VINR1[SE]",
	"VINR4[SE] + VINR2[SE]",
	"VINR4[SE] + VINR2[SE] + VINR1[SE]",
	"VINR4[SE] + VINR3[SE]",
	"VINR4[SE] + VINR3[SE] + VINR1[SE]",
	"VINR4[SE] + VINR3[SE] + VINR2[SE]",
	"VINR4[SE] + VINR3[SE] + VINR2[SE] + VINR1[SE]",
	"{VIN2P, VIN2M}[DIFF]",
	"{VIN3P, VIN3M}[DIFF]",
	"{VIN2P, VIN2M}[DIFF] + {VIN3P, VIN3M}[DIFF]"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत pcm186x_adc_input_channel_sel[] = अणु
	SOC_VALUE_ENUM_SINGLE(PCM186X_ADC1_INPUT_SEL_L, 0,
			      PCM186X_ADC_INPUT_SEL_MASK,
			      ARRAY_SIZE(pcm186x_adcl_input_channel_sel_text),
			      pcm186x_adcl_input_channel_sel_text,
			      pcm186x_adc_input_channel_sel_value),
	SOC_VALUE_ENUM_SINGLE(PCM186X_ADC1_INPUT_SEL_R, 0,
			      PCM186X_ADC_INPUT_SEL_MASK,
			      ARRAY_SIZE(pcm186x_adcr_input_channel_sel_text),
			      pcm186x_adcr_input_channel_sel_text,
			      pcm186x_adc_input_channel_sel_value),
	SOC_VALUE_ENUM_SINGLE(PCM186X_ADC2_INPUT_SEL_L, 0,
			      PCM186X_ADC_INPUT_SEL_MASK,
			      ARRAY_SIZE(pcm186x_adcl_input_channel_sel_text),
			      pcm186x_adcl_input_channel_sel_text,
			      pcm186x_adc_input_channel_sel_value),
	SOC_VALUE_ENUM_SINGLE(PCM186X_ADC2_INPUT_SEL_R, 0,
			      PCM186X_ADC_INPUT_SEL_MASK,
			      ARRAY_SIZE(pcm186x_adcr_input_channel_sel_text),
			      pcm186x_adcr_input_channel_sel_text,
			      pcm186x_adc_input_channel_sel_value),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new pcm186x_adc_mux_controls[] = अणु
	SOC_DAPM_ENUM("ADC1 Left Input", pcm186x_adc_input_channel_sel[0]),
	SOC_DAPM_ENUM("ADC1 Right Input", pcm186x_adc_input_channel_sel[1]),
	SOC_DAPM_ENUM("ADC2 Left Input", pcm186x_adc_input_channel_sel[2]),
	SOC_DAPM_ENUM("ADC2 Right Input", pcm186x_adc_input_channel_sel[3]),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget pcm1863_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("VINL1"),
	SND_SOC_DAPM_INPUT("VINR1"),
	SND_SOC_DAPM_INPUT("VINL2"),
	SND_SOC_DAPM_INPUT("VINR2"),
	SND_SOC_DAPM_INPUT("VINL3"),
	SND_SOC_DAPM_INPUT("VINR3"),
	SND_SOC_DAPM_INPUT("VINL4"),
	SND_SOC_DAPM_INPUT("VINR4"),

	SND_SOC_DAPM_MUX("ADC Left Capture Source", SND_SOC_NOPM, 0, 0,
			 &pcm186x_adc_mux_controls[0]),
	SND_SOC_DAPM_MUX("ADC Right Capture Source", SND_SOC_NOPM, 0, 0,
			 &pcm186x_adc_mux_controls[1]),

	/*
	 * Put the codec पूर्णांकo SLEEP mode when not in use, allowing the
	 * Energysense mechanism to operate.
	 */
	SND_SOC_DAPM_ADC("ADC", "HiFi Capture", PCM186X_POWER_CTRL, 1,  1),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget pcm1865_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("VINL1"),
	SND_SOC_DAPM_INPUT("VINR1"),
	SND_SOC_DAPM_INPUT("VINL2"),
	SND_SOC_DAPM_INPUT("VINR2"),
	SND_SOC_DAPM_INPUT("VINL3"),
	SND_SOC_DAPM_INPUT("VINR3"),
	SND_SOC_DAPM_INPUT("VINL4"),
	SND_SOC_DAPM_INPUT("VINR4"),

	SND_SOC_DAPM_MUX("ADC1 Left Capture Source", SND_SOC_NOPM, 0, 0,
			 &pcm186x_adc_mux_controls[0]),
	SND_SOC_DAPM_MUX("ADC1 Right Capture Source", SND_SOC_NOPM, 0, 0,
			 &pcm186x_adc_mux_controls[1]),
	SND_SOC_DAPM_MUX("ADC2 Left Capture Source", SND_SOC_NOPM, 0, 0,
			 &pcm186x_adc_mux_controls[2]),
	SND_SOC_DAPM_MUX("ADC2 Right Capture Source", SND_SOC_NOPM, 0, 0,
			 &pcm186x_adc_mux_controls[3]),

	/*
	 * Put the codec पूर्णांकo SLEEP mode when not in use, allowing the
	 * Energysense mechanism to operate.
	 */
	SND_SOC_DAPM_ADC("ADC1", "HiFi Capture 1", PCM186X_POWER_CTRL, 1,  1),
	SND_SOC_DAPM_ADC("ADC2", "HiFi Capture 2", PCM186X_POWER_CTRL, 1,  1),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route pcm1863_dapm_routes[] = अणु
	अणु "ADC Left Capture Source", शून्य, "VINL1" पूर्ण,
	अणु "ADC Left Capture Source", शून्य, "VINR1" पूर्ण,
	अणु "ADC Left Capture Source", शून्य, "VINL2" पूर्ण,
	अणु "ADC Left Capture Source", शून्य, "VINR2" पूर्ण,
	अणु "ADC Left Capture Source", शून्य, "VINL3" पूर्ण,
	अणु "ADC Left Capture Source", शून्य, "VINR3" पूर्ण,
	अणु "ADC Left Capture Source", शून्य, "VINL4" पूर्ण,
	अणु "ADC Left Capture Source", शून्य, "VINR4" पूर्ण,

	अणु "ADC", शून्य, "ADC Left Capture Source" पूर्ण,

	अणु "ADC Right Capture Source", शून्य, "VINL1" पूर्ण,
	अणु "ADC Right Capture Source", शून्य, "VINR1" पूर्ण,
	अणु "ADC Right Capture Source", शून्य, "VINL2" पूर्ण,
	अणु "ADC Right Capture Source", शून्य, "VINR2" पूर्ण,
	अणु "ADC Right Capture Source", शून्य, "VINL3" पूर्ण,
	अणु "ADC Right Capture Source", शून्य, "VINR3" पूर्ण,
	अणु "ADC Right Capture Source", शून्य, "VINL4" पूर्ण,
	अणु "ADC Right Capture Source", शून्य, "VINR4" पूर्ण,

	अणु "ADC", शून्य, "ADC Right Capture Source" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route pcm1865_dapm_routes[] = अणु
	अणु "ADC1 Left Capture Source", शून्य, "VINL1" पूर्ण,
	अणु "ADC1 Left Capture Source", शून्य, "VINR1" पूर्ण,
	अणु "ADC1 Left Capture Source", शून्य, "VINL2" पूर्ण,
	अणु "ADC1 Left Capture Source", शून्य, "VINR2" पूर्ण,
	अणु "ADC1 Left Capture Source", शून्य, "VINL3" पूर्ण,
	अणु "ADC1 Left Capture Source", शून्य, "VINR3" पूर्ण,
	अणु "ADC1 Left Capture Source", शून्य, "VINL4" पूर्ण,
	अणु "ADC1 Left Capture Source", शून्य, "VINR4" पूर्ण,

	अणु "ADC1", शून्य, "ADC1 Left Capture Source" पूर्ण,

	अणु "ADC1 Right Capture Source", शून्य, "VINL1" पूर्ण,
	अणु "ADC1 Right Capture Source", शून्य, "VINR1" पूर्ण,
	अणु "ADC1 Right Capture Source", शून्य, "VINL2" पूर्ण,
	अणु "ADC1 Right Capture Source", शून्य, "VINR2" पूर्ण,
	अणु "ADC1 Right Capture Source", शून्य, "VINL3" पूर्ण,
	अणु "ADC1 Right Capture Source", शून्य, "VINR3" पूर्ण,
	अणु "ADC1 Right Capture Source", शून्य, "VINL4" पूर्ण,
	अणु "ADC1 Right Capture Source", शून्य, "VINR4" पूर्ण,

	अणु "ADC1", शून्य, "ADC1 Right Capture Source" पूर्ण,

	अणु "ADC2 Left Capture Source", शून्य, "VINL1" पूर्ण,
	अणु "ADC2 Left Capture Source", शून्य, "VINR1" पूर्ण,
	अणु "ADC2 Left Capture Source", शून्य, "VINL2" पूर्ण,
	अणु "ADC2 Left Capture Source", शून्य, "VINR2" पूर्ण,
	अणु "ADC2 Left Capture Source", शून्य, "VINL3" पूर्ण,
	अणु "ADC2 Left Capture Source", शून्य, "VINR3" पूर्ण,
	अणु "ADC2 Left Capture Source", शून्य, "VINL4" पूर्ण,
	अणु "ADC2 Left Capture Source", शून्य, "VINR4" पूर्ण,

	अणु "ADC2", शून्य, "ADC2 Left Capture Source" पूर्ण,

	अणु "ADC2 Right Capture Source", शून्य, "VINL1" पूर्ण,
	अणु "ADC2 Right Capture Source", शून्य, "VINR1" पूर्ण,
	अणु "ADC2 Right Capture Source", शून्य, "VINL2" पूर्ण,
	अणु "ADC2 Right Capture Source", शून्य, "VINR2" पूर्ण,
	अणु "ADC2 Right Capture Source", शून्य, "VINL3" पूर्ण,
	अणु "ADC2 Right Capture Source", शून्य, "VINR3" पूर्ण,
	अणु "ADC2 Right Capture Source", शून्य, "VINL4" पूर्ण,
	अणु "ADC2 Right Capture Source", शून्य, "VINR4" पूर्ण,

	अणु "ADC2", शून्य, "ADC2 Right Capture Source" पूर्ण,
पूर्ण;

अटल पूर्णांक pcm186x_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm186x_priv *priv = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक rate = params_rate(params);
	snd_pcm_क्रमmat_t क्रमmat = params_क्रमmat(params);
	अचिन्हित पूर्णांक width = params_width(params);
	अचिन्हित पूर्णांक channels = params_channels(params);
	अचिन्हित पूर्णांक भाग_lrck;
	अचिन्हित पूर्णांक भाग_bck;
	u8 tdm_tx_sel = 0;
	u8 pcm_cfg = 0;

	dev_dbg(component->dev, "%s() rate=%u format=0x%x width=%u channels=%u\n",
		__func__, rate, क्रमmat, width, channels);

	चयन (width) अणु
	हाल 16:
		pcm_cfg = PCM186X_PCM_CFG_RX_WLEN_16 <<
			  PCM186X_PCM_CFG_RX_WLEN_SHIFT |
			  PCM186X_PCM_CFG_TX_WLEN_16 <<
			  PCM186X_PCM_CFG_TX_WLEN_SHIFT;
		अवरोध;
	हाल 20:
		pcm_cfg = PCM186X_PCM_CFG_RX_WLEN_20 <<
			  PCM186X_PCM_CFG_RX_WLEN_SHIFT |
			  PCM186X_PCM_CFG_TX_WLEN_20 <<
			  PCM186X_PCM_CFG_TX_WLEN_SHIFT;
		अवरोध;
	हाल 24:
		pcm_cfg = PCM186X_PCM_CFG_RX_WLEN_24 <<
			  PCM186X_PCM_CFG_RX_WLEN_SHIFT |
			  PCM186X_PCM_CFG_TX_WLEN_24 <<
			  PCM186X_PCM_CFG_TX_WLEN_SHIFT;
		अवरोध;
	हाल 32:
		pcm_cfg = PCM186X_PCM_CFG_RX_WLEN_32 <<
			  PCM186X_PCM_CFG_RX_WLEN_SHIFT |
			  PCM186X_PCM_CFG_TX_WLEN_32 <<
			  PCM186X_PCM_CFG_TX_WLEN_SHIFT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, PCM186X_PCM_CFG,
			    PCM186X_PCM_CFG_RX_WLEN_MASK |
			    PCM186X_PCM_CFG_TX_WLEN_MASK,
			    pcm_cfg);

	भाग_lrck = width * channels;

	अगर (priv->is_tdm_mode) अणु
		/* Select TDM transmission data */
		चयन (channels) अणु
		हाल 2:
			tdm_tx_sel = PCM186X_TDM_TX_SEL_2CH;
			अवरोध;
		हाल 4:
			tdm_tx_sel = PCM186X_TDM_TX_SEL_4CH;
			अवरोध;
		हाल 6:
			tdm_tx_sel = PCM186X_TDM_TX_SEL_6CH;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		snd_soc_component_update_bits(component, PCM186X_TDM_TX_SEL,
				    PCM186X_TDM_TX_SEL_MASK, tdm_tx_sel);

		/* In DSP/TDM mode, the LRCLK भागider must be 256 */
		भाग_lrck = 256;

		/* Configure 1/256 duty cycle क्रम LRCK */
		snd_soc_component_update_bits(component, PCM186X_PCM_CFG,
				    PCM186X_PCM_CFG_TDM_LRCK_MODE,
				    PCM186X_PCM_CFG_TDM_LRCK_MODE);
	पूर्ण

	/* Only configure घड़ी भागiders in master mode. */
	अगर (priv->is_master_mode) अणु
		भाग_bck = priv->sysclk / (भाग_lrck * rate);

		dev_dbg(component->dev,
			"%s() master_clk=%u div_bck=%u div_lrck=%u\n",
			__func__, priv->sysclk, भाग_bck, भाग_lrck);

		snd_soc_component_ग_लिखो(component, PCM186X_BCK_DIV, भाग_bck - 1);
		snd_soc_component_ग_लिखो(component, PCM186X_LRK_DIV, भाग_lrck - 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcm186x_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक क्रमmat)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm186x_priv *priv = snd_soc_component_get_drvdata(component);
	u8 clk_ctrl = 0;
	u8 pcm_cfg = 0;

	dev_dbg(component->dev, "%s() format=0x%x\n", __func__, क्रमmat);

	/* set master/slave audio पूर्णांकerface */
	चयन (क्रमmat & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अगर (!priv->sysclk) अणु
			dev_err(component->dev, "operating in master mode requires sysclock to be configured\n");
			वापस -EINVAL;
		पूर्ण
		clk_ctrl |= PCM186X_CLK_CTRL_MST_MODE;
		priv->is_master_mode = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		priv->is_master_mode = false;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid DAI master/slave interface\n");
		वापस -EINVAL;
	पूर्ण

	/* set पूर्णांकerface polarity */
	चयन (क्रमmat & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	शेष:
		dev_err(component->dev, "Inverted DAI clocks not supported\n");
		वापस -EINVAL;
	पूर्ण

	/* set पूर्णांकerface क्रमmat */
	चयन (क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		pcm_cfg = PCM186X_PCM_CFG_FMT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		pcm_cfg = PCM186X_PCM_CFG_FMT_LEFTJ;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		priv->tdm_offset += 1;
		fallthrough;
		/* DSP_A uses the same basic config as DSP_B
		 * except we need to shअगरt the TDM output by one BCK cycle
		 */
	हाल SND_SOC_DAIFMT_DSP_B:
		priv->is_tdm_mode = true;
		pcm_cfg = PCM186X_PCM_CFG_FMT_TDM;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid DAI format\n");
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, PCM186X_CLK_CTRL,
			    PCM186X_CLK_CTRL_MST_MODE, clk_ctrl);

	snd_soc_component_ग_लिखो(component, PCM186X_TDM_TX_OFFSET, priv->tdm_offset);

	snd_soc_component_update_bits(component, PCM186X_PCM_CFG,
			    PCM186X_PCM_CFG_FMT_MASK, pcm_cfg);

	वापस 0;
पूर्ण

अटल पूर्णांक pcm186x_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
				अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm186x_priv *priv = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक first_slot, last_slot, tdm_offset;

	dev_dbg(component->dev,
		"%s() tx_mask=0x%x rx_mask=0x%x slots=%d slot_width=%d\n",
		__func__, tx_mask, rx_mask, slots, slot_width);

	अगर (!tx_mask) अणु
		dev_err(component->dev, "tdm tx mask must not be 0\n");
		वापस -EINVAL;
	पूर्ण

	first_slot = __ffs(tx_mask);
	last_slot = __fls(tx_mask);

	अगर (last_slot - first_slot != hweight32(tx_mask) - 1) अणु
		dev_err(component->dev, "tdm tx mask must be contiguous\n");
		वापस -EINVAL;
	पूर्ण

	tdm_offset = first_slot * slot_width;

	अगर (tdm_offset > 255) अणु
		dev_err(component->dev, "tdm tx slot selection out of bounds\n");
		वापस -EINVAL;
	पूर्ण

	priv->tdm_offset = tdm_offset;

	वापस 0;
पूर्ण

अटल पूर्णांक pcm186x_set_dai_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
				  अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm186x_priv *priv = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "%s() clk_id=%d freq=%u dir=%d\n",
		__func__, clk_id, freq, dir);

	priv->sysclk = freq;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops pcm186x_dai_ops = अणु
	.set_sysclk = pcm186x_set_dai_sysclk,
	.set_tdm_slot = pcm186x_set_tdm_slot,
	.set_fmt = pcm186x_set_fmt,
	.hw_params = pcm186x_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver pcm1863_dai = अणु
	.name = "pcm1863-aif",
	.capture = अणु
		 .stream_name = "Capture",
		 .channels_min = 1,
		 .channels_max = 2,
		 .rates = PCM186X_RATES,
		 .क्रमmats = PCM186X_FORMATS,
	 पूर्ण,
	.ops = &pcm186x_dai_ops,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver pcm1865_dai = अणु
	.name = "pcm1865-aif",
	.capture = अणु
		 .stream_name = "Capture",
		 .channels_min = 1,
		 .channels_max = 4,
		 .rates = PCM186X_RATES,
		 .क्रमmats = PCM186X_FORMATS,
	 पूर्ण,
	.ops = &pcm186x_dai_ops,
पूर्ण;

अटल पूर्णांक pcm186x_घातer_on(काष्ठा snd_soc_component *component)
अणु
	काष्ठा pcm186x_priv *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	ret = regulator_bulk_enable(ARRAY_SIZE(priv->supplies),
				    priv->supplies);
	अगर (ret)
		वापस ret;

	regcache_cache_only(priv->regmap, false);
	ret = regcache_sync(priv->regmap);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to restore cache\n");
		regcache_cache_only(priv->regmap, true);
		regulator_bulk_disable(ARRAY_SIZE(priv->supplies),
				       priv->supplies);
		वापस ret;
	पूर्ण

	snd_soc_component_update_bits(component, PCM186X_POWER_CTRL,
			    PCM186X_PWR_CTRL_PWRDN, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक pcm186x_घातer_off(काष्ठा snd_soc_component *component)
अणु
	काष्ठा pcm186x_priv *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	snd_soc_component_update_bits(component, PCM186X_POWER_CTRL,
			    PCM186X_PWR_CTRL_PWRDN, PCM186X_PWR_CTRL_PWRDN);

	regcache_cache_only(priv->regmap, true);

	ret = regulator_bulk_disable(ARRAY_SIZE(priv->supplies),
				     priv->supplies);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक pcm186x_set_bias_level(काष्ठा snd_soc_component *component,
				  क्रमागत snd_soc_bias_level level)
अणु
	dev_dbg(component->dev, "## %s: %d -> %d\n", __func__,
		snd_soc_component_get_bias_level(component), level);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			pcm186x_घातer_on(component);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		pcm186x_घातer_off(component);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_component_driver soc_codec_dev_pcm1863 = अणु
	.set_bias_level		= pcm186x_set_bias_level,
	.controls		= pcm1863_snd_controls,
	.num_controls		= ARRAY_SIZE(pcm1863_snd_controls),
	.dapm_widमाला_लो		= pcm1863_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(pcm1863_dapm_widमाला_लो),
	.dapm_routes		= pcm1863_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(pcm1863_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल काष्ठा snd_soc_component_driver soc_codec_dev_pcm1865 = अणु
	.set_bias_level		= pcm186x_set_bias_level,
	.controls		= pcm1865_snd_controls,
	.num_controls		= ARRAY_SIZE(pcm1865_snd_controls),
	.dapm_widमाला_लो		= pcm1865_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(pcm1865_dapm_widमाला_लो),
	.dapm_routes		= pcm1865_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(pcm1865_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल bool pcm186x_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल PCM186X_PAGE:
	हाल PCM186X_DEVICE_STATUS:
	हाल PCM186X_FSAMPLE_STATUS:
	हाल PCM186X_DIV_STATUS:
	हाल PCM186X_CLK_STATUS:
	हाल PCM186X_SUPPLY_STATUS:
	हाल PCM186X_MMAP_STAT_CTRL:
	हाल PCM186X_MMAP_ADDRESS:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_range_cfg pcm186x_range = अणु
	.name = "Pages",
	.range_max = PCM186X_MAX_REGISTER,
	.selector_reg = PCM186X_PAGE,
	.selector_mask = 0xff,
	.winकरोw_len = PCM186X_PAGE_LEN,
पूर्ण;

स्थिर काष्ठा regmap_config pcm186x_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.अस्थिर_reg = pcm186x_अस्थिर,

	.ranges = &pcm186x_range,
	.num_ranges = 1,

	.max_रेजिस्टर = PCM186X_MAX_REGISTER,

	.cache_type = REGCACHE_RBTREE,
पूर्ण;
EXPORT_SYMBOL_GPL(pcm186x_regmap);

पूर्णांक pcm186x_probe(काष्ठा device *dev, क्रमागत pcm186x_type type, पूर्णांक irq,
		  काष्ठा regmap *regmap)
अणु
	काष्ठा pcm186x_priv *priv;
	पूर्णांक i, ret;

	priv = devm_kzalloc(dev, माप(काष्ठा pcm186x_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	dev_set_drvdata(dev, priv);
	priv->regmap = regmap;

	क्रम (i = 0; i < ARRAY_SIZE(priv->supplies); i++)
		priv->supplies[i].supply = pcm186x_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(priv->supplies),
				      priv->supplies);
	अगर (ret) अणु
		dev_err(dev, "failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(priv->supplies),
				    priv->supplies);
	अगर (ret) अणु
		dev_err(dev, "failed enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Reset device रेजिस्टरs क्रम a consistent घातer-on like state */
	ret = regmap_ग_लिखो(regmap, PCM186X_PAGE, PCM186X_RESET);
	अगर (ret) अणु
		dev_err(dev, "failed to write device: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_disable(ARRAY_SIZE(priv->supplies),
				     priv->supplies);
	अगर (ret) अणु
		dev_err(dev, "failed disable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	चयन (type) अणु
	हाल PCM1865:
	हाल PCM1864:
		ret = devm_snd_soc_रेजिस्टर_component(dev, &soc_codec_dev_pcm1865,
					     &pcm1865_dai, 1);
		अवरोध;
	हाल PCM1863:
	हाल PCM1862:
	शेष:
		ret = devm_snd_soc_रेजिस्टर_component(dev, &soc_codec_dev_pcm1863,
					     &pcm1863_dai, 1);
	पूर्ण
	अगर (ret) अणु
		dev_err(dev, "failed to register CODEC: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pcm186x_probe);

MODULE_AUTHOR("Andreas Dannenberg <dannenberg@ti.com>");
MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_DESCRIPTION("PCM186x Universal Audio ADC driver");
MODULE_LICENSE("GPL v2");
