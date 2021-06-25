<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arizona.c - Wolfson Arizona class device shared support
 *
 * Copyright 2012 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gcd.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>

#समावेश <linux/mfd/arizona/core.h>
#समावेश <linux/mfd/arizona/रेजिस्टरs.h>

#समावेश "arizona.h"

#घोषणा ARIZONA_AIF_BCLK_CTRL                   0x00
#घोषणा ARIZONA_AIF_TX_PIN_CTRL                 0x01
#घोषणा ARIZONA_AIF_RX_PIN_CTRL                 0x02
#घोषणा ARIZONA_AIF_RATE_CTRL                   0x03
#घोषणा ARIZONA_AIF_FORMAT                      0x04
#घोषणा ARIZONA_AIF_TX_BCLK_RATE                0x05
#घोषणा ARIZONA_AIF_RX_BCLK_RATE                0x06
#घोषणा ARIZONA_AIF_FRAME_CTRL_1                0x07
#घोषणा ARIZONA_AIF_FRAME_CTRL_2                0x08
#घोषणा ARIZONA_AIF_FRAME_CTRL_3                0x09
#घोषणा ARIZONA_AIF_FRAME_CTRL_4                0x0A
#घोषणा ARIZONA_AIF_FRAME_CTRL_5                0x0B
#घोषणा ARIZONA_AIF_FRAME_CTRL_6                0x0C
#घोषणा ARIZONA_AIF_FRAME_CTRL_7                0x0D
#घोषणा ARIZONA_AIF_FRAME_CTRL_8                0x0E
#घोषणा ARIZONA_AIF_FRAME_CTRL_9                0x0F
#घोषणा ARIZONA_AIF_FRAME_CTRL_10               0x10
#घोषणा ARIZONA_AIF_FRAME_CTRL_11               0x11
#घोषणा ARIZONA_AIF_FRAME_CTRL_12               0x12
#घोषणा ARIZONA_AIF_FRAME_CTRL_13               0x13
#घोषणा ARIZONA_AIF_FRAME_CTRL_14               0x14
#घोषणा ARIZONA_AIF_FRAME_CTRL_15               0x15
#घोषणा ARIZONA_AIF_FRAME_CTRL_16               0x16
#घोषणा ARIZONA_AIF_FRAME_CTRL_17               0x17
#घोषणा ARIZONA_AIF_FRAME_CTRL_18               0x18
#घोषणा ARIZONA_AIF_TX_ENABLES                  0x19
#घोषणा ARIZONA_AIF_RX_ENABLES                  0x1A
#घोषणा ARIZONA_AIF_FORCE_WRITE                 0x1B

#घोषणा ARIZONA_FLL_VCO_CORNER 141900000
#घोषणा ARIZONA_FLL_MAX_FREF   13500000
#घोषणा ARIZONA_FLL_MIN_FVCO   90000000
#घोषणा ARIZONA_FLL_MAX_FRATIO 16
#घोषणा ARIZONA_FLL_MAX_REFDIV 8
#घोषणा ARIZONA_FLL_MIN_OUTDIV 2
#घोषणा ARIZONA_FLL_MAX_OUTDIV 7

#घोषणा ARIZONA_FMT_DSP_MODE_A          0
#घोषणा ARIZONA_FMT_DSP_MODE_B          1
#घोषणा ARIZONA_FMT_I2S_MODE            2
#घोषणा ARIZONA_FMT_LEFT_JUSTIFIED_MODE 3

#घोषणा arizona_fll_err(_fll, fmt, ...) \
	dev_err(_fll->arizona->dev, "FLL%d: " fmt, _fll->id, ##__VA_ARGS__)
#घोषणा arizona_fll_warn(_fll, fmt, ...) \
	dev_warn(_fll->arizona->dev, "FLL%d: " fmt, _fll->id, ##__VA_ARGS__)
#घोषणा arizona_fll_dbg(_fll, fmt, ...) \
	dev_dbg(_fll->arizona->dev, "FLL%d: " fmt, _fll->id, ##__VA_ARGS__)

#घोषणा arizona_aअगर_err(_dai, fmt, ...) \
	dev_err(_dai->dev, "AIF%d: " fmt, _dai->id, ##__VA_ARGS__)
#घोषणा arizona_aअगर_warn(_dai, fmt, ...) \
	dev_warn(_dai->dev, "AIF%d: " fmt, _dai->id, ##__VA_ARGS__)
#घोषणा arizona_aअगर_dbg(_dai, fmt, ...) \
	dev_dbg(_dai->dev, "AIF%d: " fmt, _dai->id, ##__VA_ARGS__)

अटल पूर्णांक arizona_spk_ev(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *kcontrol,
			  पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा arizona *arizona = dev_get_drvdata(component->dev->parent);
	पूर्णांक val;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		val = snd_soc_component_पढ़ो(component,
					       ARIZONA_INTERRUPT_RAW_STATUS_3);
		अगर (val & ARIZONA_SPK_OVERHEAT_STS) अणु
			dev_crit(arizona->dev,
				 "Speaker not enabled due to temperature\n");
			वापस -EBUSY;
		पूर्ण

		regmap_update_bits_async(arizona->regmap,
					 ARIZONA_OUTPUT_ENABLES_1,
					 1 << w->shअगरt, 1 << w->shअगरt);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_update_bits_async(arizona->regmap,
					 ARIZONA_OUTPUT_ENABLES_1,
					 1 << w->shअगरt, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस arizona_out_ev(w, kcontrol, event);
पूर्ण

अटल irqवापस_t arizona_thermal_warn(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा arizona *arizona = data;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(arizona->regmap, ARIZONA_INTERRUPT_RAW_STATUS_3,
			  &val);
	अगर (ret != 0) अणु
		dev_err(arizona->dev, "Failed to read thermal status: %d\n",
			ret);
	पूर्ण अन्यथा अगर (val & ARIZONA_SPK_OVERHEAT_WARN_STS) अणु
		dev_crit(arizona->dev, "Thermal warning\n");
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t arizona_thermal_shutकरोwn(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा arizona *arizona = data;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(arizona->regmap, ARIZONA_INTERRUPT_RAW_STATUS_3,
			  &val);
	अगर (ret != 0) अणु
		dev_err(arizona->dev, "Failed to read thermal status: %d\n",
			ret);
	पूर्ण अन्यथा अगर (val & ARIZONA_SPK_OVERHEAT_STS) अणु
		dev_crit(arizona->dev, "Thermal shutdown\n");
		ret = regmap_update_bits(arizona->regmap,
					 ARIZONA_OUTPUT_ENABLES_1,
					 ARIZONA_OUT4L_ENA |
					 ARIZONA_OUT4R_ENA, 0);
		अगर (ret != 0)
			dev_crit(arizona->dev,
				 "Failed to disable speaker outputs: %d\n",
				 ret);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget arizona_spkl =
	SND_SOC_DAPM_PGA_E("OUT4L", SND_SOC_NOPM,
			   ARIZONA_OUT4L_ENA_SHIFT, 0, शून्य, 0, arizona_spk_ev,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD);

अटल स्थिर काष्ठा snd_soc_dapm_widget arizona_spkr =
	SND_SOC_DAPM_PGA_E("OUT4R", SND_SOC_NOPM,
			   ARIZONA_OUT4R_ENA_SHIFT, 0, शून्य, 0, arizona_spk_ev,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD);

पूर्णांक arizona_init_spk(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा arizona *arizona = priv->arizona;
	पूर्णांक ret;

	ret = snd_soc_dapm_new_controls(dapm, &arizona_spkl, 1);
	अगर (ret != 0)
		वापस ret;

	चयन (arizona->type) अणु
	हाल WM8997:
	हाल CS47L24:
	हाल WM1831:
		अवरोध;
	शेष:
		ret = snd_soc_dapm_new_controls(dapm, &arizona_spkr, 1);
		अगर (ret != 0)
			वापस ret;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_init_spk);

पूर्णांक arizona_init_spk_irqs(काष्ठा arizona *arizona)
अणु
	पूर्णांक ret;

	ret = arizona_request_irq(arizona, ARIZONA_IRQ_SPK_OVERHEAT_WARN,
				  "Thermal warning", arizona_thermal_warn,
				  arizona);
	अगर (ret != 0)
		dev_err(arizona->dev,
			"Failed to get thermal warning IRQ: %d\n",
			ret);

	ret = arizona_request_irq(arizona, ARIZONA_IRQ_SPK_OVERHEAT,
				  "Thermal shutdown", arizona_thermal_shutकरोwn,
				  arizona);
	अगर (ret != 0)
		dev_err(arizona->dev,
			"Failed to get thermal shutdown IRQ: %d\n",
			ret);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_init_spk_irqs);

पूर्णांक arizona_मुक्त_spk_irqs(काष्ठा arizona *arizona)
अणु
	arizona_मुक्त_irq(arizona, ARIZONA_IRQ_SPK_OVERHEAT_WARN, arizona);
	arizona_मुक्त_irq(arizona, ARIZONA_IRQ_SPK_OVERHEAT, arizona);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_मुक्त_spk_irqs);

अटल स्थिर काष्ठा snd_soc_dapm_route arizona_mono_routes[] = अणु
	अणु "OUT1R", शून्य, "OUT1L" पूर्ण,
	अणु "OUT2R", शून्य, "OUT2L" पूर्ण,
	अणु "OUT3R", शून्य, "OUT3L" पूर्ण,
	अणु "OUT4R", शून्य, "OUT4L" पूर्ण,
	अणु "OUT5R", शून्य, "OUT5L" पूर्ण,
	अणु "OUT6R", शून्य, "OUT6L" पूर्ण,
पूर्ण;

पूर्णांक arizona_init_mono(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा arizona *arizona = priv->arizona;
	पूर्णांक i;

	क्रम (i = 0; i < ARIZONA_MAX_OUTPUT; ++i) अणु
		अगर (arizona->pdata.out_mono[i])
			snd_soc_dapm_add_routes(dapm,
						&arizona_mono_routes[i], 1);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_init_mono);

पूर्णांक arizona_init_gpio(काष्ठा snd_soc_component *component)
अणु
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा arizona *arizona = priv->arizona;
	पूर्णांक i;

	चयन (arizona->type) अणु
	हाल WM5110:
	हाल WM8280:
		snd_soc_component_disable_pin(component,
					      "DRC2 Signal Activity");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	snd_soc_component_disable_pin(component, "DRC1 Signal Activity");

	क्रम (i = 0; i < ARRAY_SIZE(arizona->pdata.gpio_शेषs); i++) अणु
		चयन (arizona->pdata.gpio_शेषs[i] & ARIZONA_GPN_FN_MASK) अणु
		हाल ARIZONA_GP_FN_DRC1_SIGNAL_DETECT:
			snd_soc_component_enable_pin(component,
						     "DRC1 Signal Activity");
			अवरोध;
		हाल ARIZONA_GP_FN_DRC2_SIGNAL_DETECT:
			snd_soc_component_enable_pin(component,
						     "DRC2 Signal Activity");
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_init_gpio);

पूर्णांक arizona_init_common(काष्ठा arizona *arizona)
अणु
	काष्ठा arizona_pdata *pdata = &arizona->pdata;
	अचिन्हित पूर्णांक val, mask;
	पूर्णांक i;

	BLOCKING_INIT_NOTIFIER_HEAD(&arizona->notअगरier);

	क्रम (i = 0; i < ARIZONA_MAX_OUTPUT; ++i) अणु
		/* Default is 0 so noop with शेषs */
		अगर (pdata->out_mono[i])
			val = ARIZONA_OUT1_MONO;
		अन्यथा
			val = 0;

		regmap_update_bits(arizona->regmap,
				   ARIZONA_OUTPUT_PATH_CONFIG_1L + (i * 8),
				   ARIZONA_OUT1_MONO, val);
	पूर्ण

	क्रम (i = 0; i < ARIZONA_MAX_PDM_SPK; i++) अणु
		अगर (pdata->spk_mute[i])
			regmap_update_bits(arizona->regmap,
					   ARIZONA_PDM_SPK1_CTRL_1 + (i * 2),
					   ARIZONA_SPK1_MUTE_ENDIAN_MASK |
					   ARIZONA_SPK1_MUTE_SEQ1_MASK,
					   pdata->spk_mute[i]);

		अगर (pdata->spk_fmt[i])
			regmap_update_bits(arizona->regmap,
					   ARIZONA_PDM_SPK1_CTRL_2 + (i * 2),
					   ARIZONA_SPK1_FMT_MASK,
					   pdata->spk_fmt[i]);
	पूर्ण

	क्रम (i = 0; i < ARIZONA_MAX_INPUT; i++) अणु
		/* Default क्रम both is 0 so noop with शेषs */
		val = pdata->dmic_ref[i] << ARIZONA_IN1_DMIC_SUP_SHIFT;
		अगर (pdata->inmode[i] & ARIZONA_INMODE_DMIC)
			val |= 1 << ARIZONA_IN1_MODE_SHIFT;

		चयन (arizona->type) अणु
		हाल WM8998:
		हाल WM1814:
			regmap_update_bits(arizona->regmap,
				ARIZONA_ADC_DIGITAL_VOLUME_1L + (i * 8),
				ARIZONA_IN1L_SRC_SE_MASK,
				(pdata->inmode[i] & ARIZONA_INMODE_SE)
					<< ARIZONA_IN1L_SRC_SE_SHIFT);

			regmap_update_bits(arizona->regmap,
				ARIZONA_ADC_DIGITAL_VOLUME_1R + (i * 8),
				ARIZONA_IN1R_SRC_SE_MASK,
				(pdata->inmode[i] & ARIZONA_INMODE_SE)
					<< ARIZONA_IN1R_SRC_SE_SHIFT);

			mask = ARIZONA_IN1_DMIC_SUP_MASK |
			       ARIZONA_IN1_MODE_MASK;
			अवरोध;
		शेष:
			अगर (pdata->inmode[i] & ARIZONA_INMODE_SE)
				val |= 1 << ARIZONA_IN1_SINGLE_ENDED_SHIFT;

			mask = ARIZONA_IN1_DMIC_SUP_MASK |
			       ARIZONA_IN1_MODE_MASK |
			       ARIZONA_IN1_SINGLE_ENDED_MASK;
			अवरोध;
		पूर्ण

		regmap_update_bits(arizona->regmap,
				   ARIZONA_IN1L_CONTROL + (i * 8),
				   mask, val);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_init_common);

पूर्णांक arizona_init_vol_limit(काष्ठा arizona *arizona)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(arizona->pdata.out_vol_limit); ++i) अणु
		अगर (arizona->pdata.out_vol_limit[i])
			regmap_update_bits(arizona->regmap,
					   ARIZONA_DAC_VOLUME_LIMIT_1L + i * 4,
					   ARIZONA_OUT1L_VOL_LIM_MASK,
					   arizona->pdata.out_vol_limit[i]);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_init_vol_limit);

स्थिर अक्षर * स्थिर arizona_mixer_texts[ARIZONA_NUM_MIXER_INPUTS] = अणु
	"None",
	"Tone Generator 1",
	"Tone Generator 2",
	"Haptics",
	"AEC",
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
	"AIF3RX1",
	"AIF3RX2",
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
	"ASRC1L",
	"ASRC1R",
	"ASRC2L",
	"ASRC2R",
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
पूर्ण;
EXPORT_SYMBOL_GPL(arizona_mixer_texts);

अचिन्हित पूर्णांक arizona_mixer_values[ARIZONA_NUM_MIXER_INPUTS] = अणु
	0x00,  /* None */
	0x04,  /* Tone */
	0x05,
	0x06,  /* Haptics */
	0x08,  /* AEC */
	0x09,  /* AEC2 */
	0x0c,  /* Noise mixer */
	0x0d,  /* Comक्रमt noise */
	0x10,  /* IN1L */
	0x11,
	0x12,
	0x13,
	0x14,
	0x15,
	0x16,
	0x17,
	0x20,  /* AIF1RX1 */
	0x21,
	0x22,
	0x23,
	0x24,
	0x25,
	0x26,
	0x27,
	0x28,  /* AIF2RX1 */
	0x29,
	0x2a,
	0x2b,
	0x2c,
	0x2d,
	0x30,  /* AIF3RX1 */
	0x31,
	0x38,  /* SLIMRX1 */
	0x39,
	0x3a,
	0x3b,
	0x3c,
	0x3d,
	0x3e,
	0x3f,
	0x50,  /* EQ1 */
	0x51,
	0x52,
	0x53,
	0x58,  /* DRC1L */
	0x59,
	0x5a,
	0x5b,
	0x60,  /* LHPF1 */
	0x61,
	0x62,
	0x63,
	0x68,  /* DSP1.1 */
	0x69,
	0x6a,
	0x6b,
	0x6c,
	0x6d,
	0x70,  /* DSP2.1 */
	0x71,
	0x72,
	0x73,
	0x74,
	0x75,
	0x78,  /* DSP3.1 */
	0x79,
	0x7a,
	0x7b,
	0x7c,
	0x7d,
	0x80,  /* DSP4.1 */
	0x81,
	0x82,
	0x83,
	0x84,
	0x85,
	0x90,  /* ASRC1L */
	0x91,
	0x92,
	0x93,
	0xa0,  /* ISRC1INT1 */
	0xa1,
	0xa2,
	0xa3,
	0xa4,  /* ISRC1DEC1 */
	0xa5,
	0xa6,
	0xa7,
	0xa8,  /* ISRC2DEC1 */
	0xa9,
	0xaa,
	0xab,
	0xac,  /* ISRC2INT1 */
	0xad,
	0xae,
	0xaf,
	0xb0,  /* ISRC3DEC1 */
	0xb1,
	0xb2,
	0xb3,
	0xb4,  /* ISRC3INT1 */
	0xb5,
	0xb6,
	0xb7,
पूर्ण;
EXPORT_SYMBOL_GPL(arizona_mixer_values);

स्थिर DECLARE_TLV_DB_SCALE(arizona_mixer_tlv, -3200, 100, 0);
EXPORT_SYMBOL_GPL(arizona_mixer_tlv);

स्थिर अक्षर * स्थिर arizona_sample_rate_text[ARIZONA_SAMPLE_RATE_ENUM_SIZE] = अणु
	"12kHz", "24kHz", "48kHz", "96kHz", "192kHz",
	"11.025kHz", "22.05kHz", "44.1kHz", "88.2kHz", "176.4kHz",
	"4kHz", "8kHz", "16kHz", "32kHz",
पूर्ण;
EXPORT_SYMBOL_GPL(arizona_sample_rate_text);

स्थिर अचिन्हित पूर्णांक arizona_sample_rate_val[ARIZONA_SAMPLE_RATE_ENUM_SIZE] = अणु
	0x01, 0x02, 0x03, 0x04, 0x05, 0x09, 0x0A, 0x0B, 0x0C, 0x0D,
	0x10, 0x11, 0x12, 0x13,
पूर्ण;
EXPORT_SYMBOL_GPL(arizona_sample_rate_val);

स्थिर अक्षर *arizona_sample_rate_val_to_name(अचिन्हित पूर्णांक rate_val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(arizona_sample_rate_val); ++i) अणु
		अगर (arizona_sample_rate_val[i] == rate_val)
			वापस arizona_sample_rate_text[i];
	पूर्ण

	वापस "Illegal";
पूर्ण
EXPORT_SYMBOL_GPL(arizona_sample_rate_val_to_name);

स्थिर अक्षर * स्थिर arizona_rate_text[ARIZONA_RATE_ENUM_SIZE] = अणु
	"SYNCCLK rate", "8kHz", "16kHz", "ASYNCCLK rate",
पूर्ण;
EXPORT_SYMBOL_GPL(arizona_rate_text);

स्थिर अचिन्हित पूर्णांक arizona_rate_val[ARIZONA_RATE_ENUM_SIZE] = अणु
	0, 1, 2, 8,
पूर्ण;
EXPORT_SYMBOL_GPL(arizona_rate_val);

स्थिर काष्ठा soc_क्रमागत arizona_isrc_fsh[] = अणु
	SOC_VALUE_ENUM_SINGLE(ARIZONA_ISRC_1_CTRL_1,
			      ARIZONA_ISRC1_FSH_SHIFT, 0xf,
			      ARIZONA_RATE_ENUM_SIZE,
			      arizona_rate_text, arizona_rate_val),
	SOC_VALUE_ENUM_SINGLE(ARIZONA_ISRC_2_CTRL_1,
			      ARIZONA_ISRC2_FSH_SHIFT, 0xf,
			      ARIZONA_RATE_ENUM_SIZE,
			      arizona_rate_text, arizona_rate_val),
	SOC_VALUE_ENUM_SINGLE(ARIZONA_ISRC_3_CTRL_1,
			      ARIZONA_ISRC3_FSH_SHIFT, 0xf,
			      ARIZONA_RATE_ENUM_SIZE,
			      arizona_rate_text, arizona_rate_val),
पूर्ण;
EXPORT_SYMBOL_GPL(arizona_isrc_fsh);

स्थिर काष्ठा soc_क्रमागत arizona_isrc_fsl[] = अणु
	SOC_VALUE_ENUM_SINGLE(ARIZONA_ISRC_1_CTRL_2,
			      ARIZONA_ISRC1_FSL_SHIFT, 0xf,
			      ARIZONA_RATE_ENUM_SIZE,
			      arizona_rate_text, arizona_rate_val),
	SOC_VALUE_ENUM_SINGLE(ARIZONA_ISRC_2_CTRL_2,
			      ARIZONA_ISRC2_FSL_SHIFT, 0xf,
			      ARIZONA_RATE_ENUM_SIZE,
			      arizona_rate_text, arizona_rate_val),
	SOC_VALUE_ENUM_SINGLE(ARIZONA_ISRC_3_CTRL_2,
			      ARIZONA_ISRC3_FSL_SHIFT, 0xf,
			      ARIZONA_RATE_ENUM_SIZE,
			      arizona_rate_text, arizona_rate_val),
पूर्ण;
EXPORT_SYMBOL_GPL(arizona_isrc_fsl);

स्थिर काष्ठा soc_क्रमागत arizona_asrc_rate1 =
	SOC_VALUE_ENUM_SINGLE(ARIZONA_ASRC_RATE1,
			      ARIZONA_ASRC_RATE1_SHIFT, 0xf,
			      ARIZONA_RATE_ENUM_SIZE - 1,
			      arizona_rate_text, arizona_rate_val);
EXPORT_SYMBOL_GPL(arizona_asrc_rate1);

अटल स्थिर अक्षर * स्थिर arizona_vol_ramp_text[] = अणु
	"0ms/6dB", "0.5ms/6dB", "1ms/6dB", "2ms/6dB", "4ms/6dB", "8ms/6dB",
	"15ms/6dB", "30ms/6dB",
पूर्ण;

SOC_ENUM_SINGLE_DECL(arizona_in_vd_ramp,
		     ARIZONA_INPUT_VOLUME_RAMP,
		     ARIZONA_IN_VD_RAMP_SHIFT,
		     arizona_vol_ramp_text);
EXPORT_SYMBOL_GPL(arizona_in_vd_ramp);

SOC_ENUM_SINGLE_DECL(arizona_in_vi_ramp,
		     ARIZONA_INPUT_VOLUME_RAMP,
		     ARIZONA_IN_VI_RAMP_SHIFT,
		     arizona_vol_ramp_text);
EXPORT_SYMBOL_GPL(arizona_in_vi_ramp);

SOC_ENUM_SINGLE_DECL(arizona_out_vd_ramp,
		     ARIZONA_OUTPUT_VOLUME_RAMP,
		     ARIZONA_OUT_VD_RAMP_SHIFT,
		     arizona_vol_ramp_text);
EXPORT_SYMBOL_GPL(arizona_out_vd_ramp);

SOC_ENUM_SINGLE_DECL(arizona_out_vi_ramp,
		     ARIZONA_OUTPUT_VOLUME_RAMP,
		     ARIZONA_OUT_VI_RAMP_SHIFT,
		     arizona_vol_ramp_text);
EXPORT_SYMBOL_GPL(arizona_out_vi_ramp);

अटल स्थिर अक्षर * स्थिर arizona_lhpf_mode_text[] = अणु
	"Low-pass", "High-pass"
पूर्ण;

SOC_ENUM_SINGLE_DECL(arizona_lhpf1_mode,
		     ARIZONA_HPLPF1_1,
		     ARIZONA_LHPF1_MODE_SHIFT,
		     arizona_lhpf_mode_text);
EXPORT_SYMBOL_GPL(arizona_lhpf1_mode);

SOC_ENUM_SINGLE_DECL(arizona_lhpf2_mode,
		     ARIZONA_HPLPF2_1,
		     ARIZONA_LHPF2_MODE_SHIFT,
		     arizona_lhpf_mode_text);
EXPORT_SYMBOL_GPL(arizona_lhpf2_mode);

SOC_ENUM_SINGLE_DECL(arizona_lhpf3_mode,
		     ARIZONA_HPLPF3_1,
		     ARIZONA_LHPF3_MODE_SHIFT,
		     arizona_lhpf_mode_text);
EXPORT_SYMBOL_GPL(arizona_lhpf3_mode);

SOC_ENUM_SINGLE_DECL(arizona_lhpf4_mode,
		     ARIZONA_HPLPF4_1,
		     ARIZONA_LHPF4_MODE_SHIFT,
		     arizona_lhpf_mode_text);
EXPORT_SYMBOL_GPL(arizona_lhpf4_mode);

अटल स्थिर अक्षर * स्थिर arizona_ng_hold_text[] = अणु
	"30ms", "120ms", "250ms", "500ms",
पूर्ण;

SOC_ENUM_SINGLE_DECL(arizona_ng_hold,
		     ARIZONA_NOISE_GATE_CONTROL,
		     ARIZONA_NGATE_HOLD_SHIFT,
		     arizona_ng_hold_text);
EXPORT_SYMBOL_GPL(arizona_ng_hold);

अटल स्थिर अक्षर * स्थिर arizona_in_hpf_cut_text[] = अणु
	"2.5Hz", "5Hz", "10Hz", "20Hz", "40Hz"
पूर्ण;

SOC_ENUM_SINGLE_DECL(arizona_in_hpf_cut_क्रमागत,
		     ARIZONA_HPF_CONTROL,
		     ARIZONA_IN_HPF_CUT_SHIFT,
		     arizona_in_hpf_cut_text);
EXPORT_SYMBOL_GPL(arizona_in_hpf_cut_क्रमागत);

अटल स्थिर अक्षर * स्थिर arizona_in_dmic_osr_text[] = अणु
	"1.536MHz", "3.072MHz", "6.144MHz", "768kHz",
पूर्ण;

स्थिर काष्ठा soc_क्रमागत arizona_in_dmic_osr[] = अणु
	SOC_ENUM_SINGLE(ARIZONA_IN1L_CONTROL, ARIZONA_IN1_OSR_SHIFT,
			ARRAY_SIZE(arizona_in_dmic_osr_text),
			arizona_in_dmic_osr_text),
	SOC_ENUM_SINGLE(ARIZONA_IN2L_CONTROL, ARIZONA_IN2_OSR_SHIFT,
			ARRAY_SIZE(arizona_in_dmic_osr_text),
			arizona_in_dmic_osr_text),
	SOC_ENUM_SINGLE(ARIZONA_IN3L_CONTROL, ARIZONA_IN3_OSR_SHIFT,
			ARRAY_SIZE(arizona_in_dmic_osr_text),
			arizona_in_dmic_osr_text),
	SOC_ENUM_SINGLE(ARIZONA_IN4L_CONTROL, ARIZONA_IN4_OSR_SHIFT,
			ARRAY_SIZE(arizona_in_dmic_osr_text),
			arizona_in_dmic_osr_text),
पूर्ण;
EXPORT_SYMBOL_GPL(arizona_in_dmic_osr);

अटल स्थिर अक्षर * स्थिर arizona_anc_input_src_text[] = अणु
	"None", "IN1", "IN2", "IN3", "IN4",
पूर्ण;

अटल स्थिर अक्षर * स्थिर arizona_anc_channel_src_text[] = अणु
	"None", "Left", "Right", "Combine",
पूर्ण;

स्थिर काष्ठा soc_क्रमागत arizona_anc_input_src[] = अणु
	SOC_ENUM_SINGLE(ARIZONA_ANC_SRC,
			ARIZONA_IN_RXANCL_SEL_SHIFT,
			ARRAY_SIZE(arizona_anc_input_src_text),
			arizona_anc_input_src_text),
	SOC_ENUM_SINGLE(ARIZONA_FCL_ADC_REFORMATTER_CONTROL,
			ARIZONA_FCL_MIC_MODE_SEL_SHIFT,
			ARRAY_SIZE(arizona_anc_channel_src_text),
			arizona_anc_channel_src_text),
	SOC_ENUM_SINGLE(ARIZONA_ANC_SRC,
			ARIZONA_IN_RXANCR_SEL_SHIFT,
			ARRAY_SIZE(arizona_anc_input_src_text),
			arizona_anc_input_src_text),
	SOC_ENUM_SINGLE(ARIZONA_FCR_ADC_REFORMATTER_CONTROL,
			ARIZONA_FCR_MIC_MODE_SEL_SHIFT,
			ARRAY_SIZE(arizona_anc_channel_src_text),
			arizona_anc_channel_src_text),
पूर्ण;
EXPORT_SYMBOL_GPL(arizona_anc_input_src);

अटल स्थिर अक्षर * स्थिर arizona_anc_ng_texts[] = अणु
	"None",
	"Internal",
	"External",
पूर्ण;

SOC_ENUM_SINGLE_DECL(arizona_anc_ng_क्रमागत, SND_SOC_NOPM, 0,
		     arizona_anc_ng_texts);
EXPORT_SYMBOL_GPL(arizona_anc_ng_क्रमागत);

अटल स्थिर अक्षर * स्थिर arizona_output_anc_src_text[] = अणु
	"None", "RXANCL", "RXANCR",
पूर्ण;

स्थिर काष्ठा soc_क्रमागत arizona_output_anc_src[] = अणु
	SOC_ENUM_SINGLE(ARIZONA_OUTPUT_PATH_CONFIG_1L,
			ARIZONA_OUT1L_ANC_SRC_SHIFT,
			ARRAY_SIZE(arizona_output_anc_src_text),
			arizona_output_anc_src_text),
	SOC_ENUM_SINGLE(ARIZONA_OUTPUT_PATH_CONFIG_1R,
			ARIZONA_OUT1R_ANC_SRC_SHIFT,
			ARRAY_SIZE(arizona_output_anc_src_text),
			arizona_output_anc_src_text),
	SOC_ENUM_SINGLE(ARIZONA_OUTPUT_PATH_CONFIG_2L,
			ARIZONA_OUT2L_ANC_SRC_SHIFT,
			ARRAY_SIZE(arizona_output_anc_src_text),
			arizona_output_anc_src_text),
	SOC_ENUM_SINGLE(ARIZONA_OUTPUT_PATH_CONFIG_2R,
			ARIZONA_OUT2R_ANC_SRC_SHIFT,
			ARRAY_SIZE(arizona_output_anc_src_text),
			arizona_output_anc_src_text),
	SOC_ENUM_SINGLE(ARIZONA_OUTPUT_PATH_CONFIG_3L,
			ARIZONA_OUT3L_ANC_SRC_SHIFT,
			ARRAY_SIZE(arizona_output_anc_src_text),
			arizona_output_anc_src_text),
	SOC_ENUM_SINGLE(ARIZONA_DAC_VOLUME_LIMIT_3R,
			ARIZONA_OUT3R_ANC_SRC_SHIFT,
			ARRAY_SIZE(arizona_output_anc_src_text),
			arizona_output_anc_src_text),
	SOC_ENUM_SINGLE(ARIZONA_OUTPUT_PATH_CONFIG_4L,
			ARIZONA_OUT4L_ANC_SRC_SHIFT,
			ARRAY_SIZE(arizona_output_anc_src_text),
			arizona_output_anc_src_text),
	SOC_ENUM_SINGLE(ARIZONA_OUTPUT_PATH_CONFIG_4R,
			ARIZONA_OUT4R_ANC_SRC_SHIFT,
			ARRAY_SIZE(arizona_output_anc_src_text),
			arizona_output_anc_src_text),
	SOC_ENUM_SINGLE(ARIZONA_OUTPUT_PATH_CONFIG_5L,
			ARIZONA_OUT5L_ANC_SRC_SHIFT,
			ARRAY_SIZE(arizona_output_anc_src_text),
			arizona_output_anc_src_text),
	SOC_ENUM_SINGLE(ARIZONA_OUTPUT_PATH_CONFIG_5R,
			ARIZONA_OUT5R_ANC_SRC_SHIFT,
			ARRAY_SIZE(arizona_output_anc_src_text),
			arizona_output_anc_src_text),
	SOC_ENUM_SINGLE(ARIZONA_OUTPUT_PATH_CONFIG_6L,
			ARIZONA_OUT6L_ANC_SRC_SHIFT,
			ARRAY_SIZE(arizona_output_anc_src_text),
			arizona_output_anc_src_text),
	SOC_ENUM_SINGLE(ARIZONA_OUTPUT_PATH_CONFIG_6R,
			ARIZONA_OUT6R_ANC_SRC_SHIFT,
			ARRAY_SIZE(arizona_output_anc_src_text),
			arizona_output_anc_src_text),
पूर्ण;
EXPORT_SYMBOL_GPL(arizona_output_anc_src);

स्थिर काष्ठा snd_kcontrol_new arizona_voice_trigger_चयन[] = अणु
	SOC_DAPM_SINGLE("Switch", SND_SOC_NOPM, 0, 1, 0),
	SOC_DAPM_SINGLE("Switch", SND_SOC_NOPM, 1, 1, 0),
	SOC_DAPM_SINGLE("Switch", SND_SOC_NOPM, 2, 1, 0),
	SOC_DAPM_SINGLE("Switch", SND_SOC_NOPM, 3, 1, 0),
पूर्ण;
EXPORT_SYMBOL_GPL(arizona_voice_trigger_चयन);

अटल व्योम arizona_in_set_vu(काष्ठा snd_soc_component *component, पूर्णांक ena)
अणु
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	अगर (ena)
		val = ARIZONA_IN_VU;
	अन्यथा
		val = 0;

	क्रम (i = 0; i < priv->num_inमाला_दो; i++)
		snd_soc_component_update_bits(component,
				    ARIZONA_ADC_DIGITAL_VOLUME_1L + (i * 4),
				    ARIZONA_IN_VU, val);
पूर्ण

bool arizona_input_analog(काष्ठा snd_soc_component *component, पूर्णांक shअगरt)
अणु
	अचिन्हित पूर्णांक reg = ARIZONA_IN1L_CONTROL + ((shअगरt / 2) * 8);
	अचिन्हित पूर्णांक val = snd_soc_component_पढ़ो(component, reg);

	वापस !(val & ARIZONA_IN1_MODE_MASK);
पूर्ण
EXPORT_SYMBOL_GPL(arizona_input_analog);

पूर्णांक arizona_in_ev(काष्ठा snd_soc_dapm_widget *w, काष्ठा snd_kcontrol *kcontrol,
		  पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg;

	अगर (w->shअगरt % 2)
		reg = ARIZONA_ADC_DIGITAL_VOLUME_1L + ((w->shअगरt / 2) * 8);
	अन्यथा
		reg = ARIZONA_ADC_DIGITAL_VOLUME_1R + ((w->shअगरt / 2) * 8);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		priv->in_pending++;
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, reg,
					      ARIZONA_IN1L_MUTE, 0);

		/* If this is the last input pending then allow VU */
		priv->in_pending--;
		अगर (priv->in_pending == 0) अणु
			msleep(1);
			arizona_in_set_vu(component, 1);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, reg,
				    ARIZONA_IN1L_MUTE | ARIZONA_IN_VU,
				    ARIZONA_IN1L_MUTE | ARIZONA_IN_VU);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* Disable volume updates अगर no inमाला_दो are enabled */
		reg = snd_soc_component_पढ़ो(component, ARIZONA_INPUT_ENABLES);
		अगर (reg == 0)
			arizona_in_set_vu(component, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_in_ev);

पूर्णांक arizona_out_ev(काष्ठा snd_soc_dapm_widget *w,
		   काष्ठा snd_kcontrol *kcontrol,
		   पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा arizona *arizona = priv->arizona;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		चयन (w->shअगरt) अणु
		हाल ARIZONA_OUT1L_ENA_SHIFT:
		हाल ARIZONA_OUT1R_ENA_SHIFT:
		हाल ARIZONA_OUT2L_ENA_SHIFT:
		हाल ARIZONA_OUT2R_ENA_SHIFT:
		हाल ARIZONA_OUT3L_ENA_SHIFT:
		हाल ARIZONA_OUT3R_ENA_SHIFT:
			priv->out_up_pending++;
			priv->out_up_delay += 17;
			अवरोध;
		हाल ARIZONA_OUT4L_ENA_SHIFT:
		हाल ARIZONA_OUT4R_ENA_SHIFT:
			priv->out_up_pending++;
			चयन (arizona->type) अणु
			हाल WM5102:
			हाल WM8997:
				अवरोध;
			शेष:
				priv->out_up_delay += 10;
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		चयन (w->shअगरt) अणु
		हाल ARIZONA_OUT1L_ENA_SHIFT:
		हाल ARIZONA_OUT1R_ENA_SHIFT:
		हाल ARIZONA_OUT2L_ENA_SHIFT:
		हाल ARIZONA_OUT2R_ENA_SHIFT:
		हाल ARIZONA_OUT3L_ENA_SHIFT:
		हाल ARIZONA_OUT3R_ENA_SHIFT:
		हाल ARIZONA_OUT4L_ENA_SHIFT:
		हाल ARIZONA_OUT4R_ENA_SHIFT:
			priv->out_up_pending--;
			अगर (!priv->out_up_pending && priv->out_up_delay) अणु
				dev_dbg(component->dev, "Power up delay: %d\n",
					priv->out_up_delay);
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
		हाल ARIZONA_OUT1L_ENA_SHIFT:
		हाल ARIZONA_OUT1R_ENA_SHIFT:
		हाल ARIZONA_OUT2L_ENA_SHIFT:
		हाल ARIZONA_OUT2R_ENA_SHIFT:
		हाल ARIZONA_OUT3L_ENA_SHIFT:
		हाल ARIZONA_OUT3R_ENA_SHIFT:
			priv->out_करोwn_pending++;
			priv->out_करोwn_delay++;
			अवरोध;
		हाल ARIZONA_OUT4L_ENA_SHIFT:
		हाल ARIZONA_OUT4R_ENA_SHIFT:
			priv->out_करोwn_pending++;
			चयन (arizona->type) अणु
			हाल WM5102:
			हाल WM8997:
				अवरोध;
			हाल WM8998:
			हाल WM1814:
				priv->out_करोwn_delay += 5;
				अवरोध;
			शेष:
				priv->out_करोwn_delay++;
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		चयन (w->shअगरt) अणु
		हाल ARIZONA_OUT1L_ENA_SHIFT:
		हाल ARIZONA_OUT1R_ENA_SHIFT:
		हाल ARIZONA_OUT2L_ENA_SHIFT:
		हाल ARIZONA_OUT2R_ENA_SHIFT:
		हाल ARIZONA_OUT3L_ENA_SHIFT:
		हाल ARIZONA_OUT3R_ENA_SHIFT:
		हाल ARIZONA_OUT4L_ENA_SHIFT:
		हाल ARIZONA_OUT4R_ENA_SHIFT:
			priv->out_करोwn_pending--;
			अगर (!priv->out_करोwn_pending && priv->out_करोwn_delay) अणु
				dev_dbg(component->dev, "Power down delay: %d\n",
					priv->out_करोwn_delay);
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
EXPORT_SYMBOL_GPL(arizona_out_ev);

पूर्णांक arizona_hp_ev(काष्ठा snd_soc_dapm_widget *w, काष्ठा snd_kcontrol *kcontrol,
		  पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा arizona *arizona = priv->arizona;
	अचिन्हित पूर्णांक mask = 1 << w->shअगरt;
	अचिन्हित पूर्णांक val;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		val = mask;
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		val = 0;
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMU:
	हाल SND_SOC_DAPM_POST_PMD:
		वापस arizona_out_ev(w, kcontrol, event);
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Store the desired state क्रम the HP outमाला_दो */
	priv->arizona->hp_ena &= ~mask;
	priv->arizona->hp_ena |= val;

	/* Force off अगर HPDET clamp is active */
	अगर (priv->arizona->hpdet_clamp)
		val = 0;

	regmap_update_bits_async(arizona->regmap, ARIZONA_OUTPUT_ENABLES_1,
				 mask, val);

	वापस arizona_out_ev(w, kcontrol, event);
पूर्ण
EXPORT_SYMBOL_GPL(arizona_hp_ev);

अटल पूर्णांक arizona_dvfs_enable(काष्ठा snd_soc_component *component)
अणु
	स्थिर काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा arizona *arizona = priv->arizona;
	पूर्णांक ret;

	ret = regulator_set_voltage(arizona->dcvdd, 1800000, 1800000);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to boost DCVDD: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(arizona->regmap,
				 ARIZONA_DYNAMIC_FREQUENCY_SCALING_1,
				 ARIZONA_SUBSYS_MAX_FREQ,
				 ARIZONA_SUBSYS_MAX_FREQ);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to enable subsys max: %d\n", ret);
		regulator_set_voltage(arizona->dcvdd, 1200000, 1800000);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक arizona_dvfs_disable(काष्ठा snd_soc_component *component)
अणु
	स्थिर काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा arizona *arizona = priv->arizona;
	पूर्णांक ret;

	ret = regmap_update_bits(arizona->regmap,
				 ARIZONA_DYNAMIC_FREQUENCY_SCALING_1,
				 ARIZONA_SUBSYS_MAX_FREQ, 0);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to disable subsys max: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_set_voltage(arizona->dcvdd, 1200000, 1800000);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to unboost DCVDD: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक arizona_dvfs_up(काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	mutex_lock(&priv->dvfs_lock);

	अगर (!priv->dvfs_cached && !priv->dvfs_reqs) अणु
		ret = arizona_dvfs_enable(component);
		अगर (ret)
			जाओ err;
	पूर्ण

	priv->dvfs_reqs |= flags;
err:
	mutex_unlock(&priv->dvfs_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_dvfs_up);

पूर्णांक arizona_dvfs_करोwn(काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक old_reqs;
	पूर्णांक ret = 0;

	mutex_lock(&priv->dvfs_lock);

	old_reqs = priv->dvfs_reqs;
	priv->dvfs_reqs &= ~flags;

	अगर (!priv->dvfs_cached && old_reqs && !priv->dvfs_reqs)
		ret = arizona_dvfs_disable(component);

	mutex_unlock(&priv->dvfs_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_dvfs_करोwn);

पूर्णांक arizona_dvfs_sysclk_ev(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	mutex_lock(&priv->dvfs_lock);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		अगर (priv->dvfs_reqs)
			ret = arizona_dvfs_enable(component);

		priv->dvfs_cached = false;
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		/* We must ensure DVFS is disabled beक्रमe the codec goes पूर्णांकo
		 * suspend so that we are never in an illegal state of DVFS
		 * enabled without enough DCVDD
		 */
		priv->dvfs_cached = true;

		अगर (priv->dvfs_reqs)
			ret = arizona_dvfs_disable(component);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	mutex_unlock(&priv->dvfs_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_dvfs_sysclk_ev);

व्योम arizona_init_dvfs(काष्ठा arizona_priv *priv)
अणु
	mutex_init(&priv->dvfs_lock);
पूर्ण
EXPORT_SYMBOL_GPL(arizona_init_dvfs);

पूर्णांक arizona_anc_ev(काष्ठा snd_soc_dapm_widget *w,
		   काष्ठा snd_kcontrol *kcontrol,
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

	snd_soc_component_ग_लिखो(component, ARIZONA_CLOCK_CONTROL, val);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_anc_ev);

अटल अचिन्हित पूर्णांक arizona_opclk_ref_48k_rates[] = अणु
	6144000,
	12288000,
	24576000,
	49152000,
पूर्ण;

अटल अचिन्हित पूर्णांक arizona_opclk_ref_44k1_rates[] = अणु
	5644800,
	11289600,
	22579200,
	45158400,
पूर्ण;

अटल पूर्णांक arizona_set_opclk(काष्ठा snd_soc_component *component,
			     अचिन्हित पूर्णांक clk, अचिन्हित पूर्णांक freq)
अणु
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक *rates;
	पूर्णांक ref, भाग, refclk;

	चयन (clk) अणु
	हाल ARIZONA_CLK_OPCLK:
		reg = ARIZONA_OUTPUT_SYSTEM_CLOCK;
		refclk = priv->sysclk;
		अवरोध;
	हाल ARIZONA_CLK_ASYNC_OPCLK:
		reg = ARIZONA_OUTPUT_ASYNC_CLOCK;
		refclk = priv->asyncclk;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (refclk % 8000)
		rates = arizona_opclk_ref_44k1_rates;
	अन्यथा
		rates = arizona_opclk_ref_48k_rates;

	क्रम (ref = 0; ref < ARRAY_SIZE(arizona_opclk_ref_48k_rates) &&
	     rates[ref] <= refclk; ref++) अणु
		भाग = 1;
		जबतक (rates[ref] / भाग >= freq && भाग < 32) अणु
			अगर (rates[ref] / भाग == freq) अणु
				dev_dbg(component->dev, "Configured %dHz OPCLK\n",
					freq);
				snd_soc_component_update_bits(component, reg,
						    ARIZONA_OPCLK_DIV_MASK |
						    ARIZONA_OPCLK_SEL_MASK,
						    (भाग <<
						     ARIZONA_OPCLK_DIV_SHIFT) |
						    ref);
				वापस 0;
			पूर्ण
			भाग++;
		पूर्ण
	पूर्ण

	dev_err(component->dev, "Unable to generate %dHz OPCLK\n", freq);
	वापस -EINVAL;
पूर्ण

पूर्णांक arizona_clk_ev(काष्ठा snd_soc_dapm_widget *w,
		   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा arizona *arizona = dev_get_drvdata(component->dev->parent);
	अचिन्हित पूर्णांक val;
	पूर्णांक clk_idx;
	पूर्णांक ret;

	ret = regmap_पढ़ो(arizona->regmap, w->reg, &val);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to check clock source: %d\n", ret);
		वापस ret;
	पूर्ण

	val = (val & ARIZONA_SYSCLK_SRC_MASK) >> ARIZONA_SYSCLK_SRC_SHIFT;

	चयन (val) अणु
	हाल ARIZONA_CLK_SRC_MCLK1:
		clk_idx = ARIZONA_MCLK1;
		अवरोध;
	हाल ARIZONA_CLK_SRC_MCLK2:
		clk_idx = ARIZONA_MCLK2;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		वापस clk_prepare_enable(arizona->mclk[clk_idx]);
	हाल SND_SOC_DAPM_POST_PMD:
		clk_disable_unprepare(arizona->mclk[clk_idx]);
		वापस 0;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(arizona_clk_ev);

पूर्णांक arizona_set_sysclk(काष्ठा snd_soc_component *component, पूर्णांक clk_id,
		       पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा arizona *arizona = priv->arizona;
	अक्षर *name;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक mask = ARIZONA_SYSCLK_FREQ_MASK | ARIZONA_SYSCLK_SRC_MASK;
	अचिन्हित पूर्णांक val = source << ARIZONA_SYSCLK_SRC_SHIFT;
	पूर्णांक *clk;

	चयन (clk_id) अणु
	हाल ARIZONA_CLK_SYSCLK:
		name = "SYSCLK";
		reg = ARIZONA_SYSTEM_CLOCK_1;
		clk = &priv->sysclk;
		mask |= ARIZONA_SYSCLK_FRAC;
		अवरोध;
	हाल ARIZONA_CLK_ASYNCCLK:
		name = "ASYNCCLK";
		reg = ARIZONA_ASYNC_CLOCK_1;
		clk = &priv->asyncclk;
		अवरोध;
	हाल ARIZONA_CLK_OPCLK:
	हाल ARIZONA_CLK_ASYNC_OPCLK:
		वापस arizona_set_opclk(component, clk_id, freq);
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (freq) अणु
	हाल  5644800:
	हाल  6144000:
		अवरोध;
	हाल 11289600:
	हाल 12288000:
		val |= ARIZONA_CLK_12MHZ << ARIZONA_SYSCLK_FREQ_SHIFT;
		अवरोध;
	हाल 22579200:
	हाल 24576000:
		val |= ARIZONA_CLK_24MHZ << ARIZONA_SYSCLK_FREQ_SHIFT;
		अवरोध;
	हाल 45158400:
	हाल 49152000:
		val |= ARIZONA_CLK_49MHZ << ARIZONA_SYSCLK_FREQ_SHIFT;
		अवरोध;
	हाल 67737600:
	हाल 73728000:
		val |= ARIZONA_CLK_73MHZ << ARIZONA_SYSCLK_FREQ_SHIFT;
		अवरोध;
	हाल 90316800:
	हाल 98304000:
		val |= ARIZONA_CLK_98MHZ << ARIZONA_SYSCLK_FREQ_SHIFT;
		अवरोध;
	हाल 135475200:
	हाल 147456000:
		val |= ARIZONA_CLK_147MHZ << ARIZONA_SYSCLK_FREQ_SHIFT;
		अवरोध;
	हाल 0:
		dev_dbg(arizona->dev, "%s cleared\n", name);
		*clk = freq;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*clk = freq;

	अगर (freq % 6144000)
		val |= ARIZONA_SYSCLK_FRAC;

	dev_dbg(arizona->dev, "%s set to %uHz", name, freq);

	वापस regmap_update_bits(arizona->regmap, reg, mask, val);
पूर्ण
EXPORT_SYMBOL_GPL(arizona_set_sysclk);

अटल पूर्णांक arizona_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा arizona *arizona = priv->arizona;
	पूर्णांक lrclk, bclk, mode, base;

	base = dai->driver->base;

	lrclk = 0;
	bclk = 0;

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
		mode = ARIZONA_FMT_DSP_MODE_A;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		अगर ((fmt & SND_SOC_DAIFMT_MASTER_MASK)
				!= SND_SOC_DAIFMT_CBM_CFM) अणु
			arizona_aअगर_err(dai, "DSP_B not valid in slave mode\n");
			वापस -EINVAL;
		पूर्ण
		mode = ARIZONA_FMT_DSP_MODE_B;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		mode = ARIZONA_FMT_I2S_MODE;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगर ((fmt & SND_SOC_DAIFMT_MASTER_MASK)
				!= SND_SOC_DAIFMT_CBM_CFM) अणु
			arizona_aअगर_err(dai, "LEFT_J not valid in slave mode\n");
			वापस -EINVAL;
		पूर्ण
		mode = ARIZONA_FMT_LEFT_JUSTIFIED_MODE;
		अवरोध;
	शेष:
		arizona_aअगर_err(dai, "Unsupported DAI format %d\n",
				fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		lrclk |= ARIZONA_AIF1TX_LRCLK_MSTR;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		bclk |= ARIZONA_AIF1_BCLK_MSTR;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		bclk |= ARIZONA_AIF1_BCLK_MSTR;
		lrclk |= ARIZONA_AIF1TX_LRCLK_MSTR;
		अवरोध;
	शेष:
		arizona_aअगर_err(dai, "Unsupported master mode %d\n",
				fmt & SND_SOC_DAIFMT_MASTER_MASK);
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		bclk |= ARIZONA_AIF1_BCLK_INV;
		lrclk |= ARIZONA_AIF1TX_LRCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		bclk |= ARIZONA_AIF1_BCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		lrclk |= ARIZONA_AIF1TX_LRCLK_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits_async(arizona->regmap, base + ARIZONA_AIF_BCLK_CTRL,
				 ARIZONA_AIF1_BCLK_INV |
				 ARIZONA_AIF1_BCLK_MSTR,
				 bclk);
	regmap_update_bits_async(arizona->regmap, base + ARIZONA_AIF_TX_PIN_CTRL,
				 ARIZONA_AIF1TX_LRCLK_INV |
				 ARIZONA_AIF1TX_LRCLK_MSTR, lrclk);
	regmap_update_bits_async(arizona->regmap,
				 base + ARIZONA_AIF_RX_PIN_CTRL,
				 ARIZONA_AIF1RX_LRCLK_INV |
				 ARIZONA_AIF1RX_LRCLK_MSTR, lrclk);
	regmap_update_bits(arizona->regmap, base + ARIZONA_AIF_FORMAT,
			   ARIZONA_AIF1_FMT_MASK, mode);

	वापस 0;
पूर्ण

अटल स्थिर पूर्णांक arizona_48k_bclk_rates[] = अणु
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

अटल स्थिर पूर्णांक arizona_44k1_bclk_rates[] = अणु
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

अटल स्थिर अचिन्हित पूर्णांक arizona_sr_vals[] = अणु
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

#घोषणा ARIZONA_48K_RATE_MASK	0x0F003E
#घोषणा ARIZONA_44K1_RATE_MASK	0x003E00
#घोषणा ARIZONA_RATE_MASK	(ARIZONA_48K_RATE_MASK | ARIZONA_44K1_RATE_MASK)

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list arizona_स्थिरraपूर्णांक = अणु
	.count	= ARRAY_SIZE(arizona_sr_vals),
	.list	= arizona_sr_vals,
पूर्ण;

अटल पूर्णांक arizona_startup(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा arizona_dai_priv *dai_priv = &priv->dai[dai->id - 1];
	अचिन्हित पूर्णांक base_rate;

	अगर (!substream->runसमय)
		वापस 0;

	चयन (dai_priv->clk) अणु
	हाल ARIZONA_CLK_SYSCLK:
		base_rate = priv->sysclk;
		अवरोध;
	हाल ARIZONA_CLK_ASYNCCLK:
		base_rate = priv->asyncclk;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (base_rate == 0)
		dai_priv->स्थिरraपूर्णांक.mask = ARIZONA_RATE_MASK;
	अन्यथा अगर (base_rate % 8000)
		dai_priv->स्थिरraपूर्णांक.mask = ARIZONA_44K1_RATE_MASK;
	अन्यथा
		dai_priv->स्थिरraपूर्णांक.mask = ARIZONA_48K_RATE_MASK;

	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
					  SNDRV_PCM_HW_PARAM_RATE,
					  &dai_priv->स्थिरraपूर्णांक);
पूर्ण

अटल व्योम arizona_wm5102_set_dac_comp(काष्ठा snd_soc_component *component,
					अचिन्हित पूर्णांक rate)
अणु
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा arizona *arizona = priv->arizona;
	काष्ठा reg_sequence dac_comp[] = अणु
		अणु 0x80, 0x3 पूर्ण,
		अणु ARIZONA_DAC_COMP_1, 0 पूर्ण,
		अणु ARIZONA_DAC_COMP_2, 0 पूर्ण,
		अणु 0x80, 0x0 पूर्ण,
	पूर्ण;

	mutex_lock(&arizona->dac_comp_lock);

	dac_comp[1].def = arizona->dac_comp_coeff;
	अगर (rate >= 176400)
		dac_comp[2].def = arizona->dac_comp_enabled;

	mutex_unlock(&arizona->dac_comp_lock);

	regmap_multi_reg_ग_लिखो(arizona->regmap,
			       dac_comp,
			       ARRAY_SIZE(dac_comp));
पूर्ण

अटल पूर्णांक arizona_hw_params_rate(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा arizona_dai_priv *dai_priv = &priv->dai[dai->id - 1];
	पूर्णांक base = dai->driver->base;
	पूर्णांक i, sr_val, ret;

	/*
	 * We will need to be more flexible than this in future,
	 * currently we use a single sample rate क्रम SYSCLK.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(arizona_sr_vals); i++)
		अगर (arizona_sr_vals[i] == params_rate(params))
			अवरोध;
	अगर (i == ARRAY_SIZE(arizona_sr_vals)) अणु
		arizona_aअगर_err(dai, "Unsupported sample rate %dHz\n",
				params_rate(params));
		वापस -EINVAL;
	पूर्ण
	sr_val = i;

	चयन (priv->arizona->type) अणु
	हाल WM5102:
	हाल WM8997:
		अगर (arizona_sr_vals[sr_val] >= 88200)
			ret = arizona_dvfs_up(component, ARIZONA_DVFS_SR1_RQ);
		अन्यथा
			ret = arizona_dvfs_करोwn(component, ARIZONA_DVFS_SR1_RQ);

		अगर (ret) अणु
			arizona_aअगर_err(dai, "Failed to change DVFS %d\n", ret);
			वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (dai_priv->clk) अणु
	हाल ARIZONA_CLK_SYSCLK:
		चयन (priv->arizona->type) अणु
		हाल WM5102:
			arizona_wm5102_set_dac_comp(component,
						    params_rate(params));
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		snd_soc_component_update_bits(component, ARIZONA_SAMPLE_RATE_1,
					      ARIZONA_SAMPLE_RATE_1_MASK,
					      sr_val);
		अगर (base)
			snd_soc_component_update_bits(component,
					base + ARIZONA_AIF_RATE_CTRL,
					ARIZONA_AIF1_RATE_MASK, 0);
		अवरोध;
	हाल ARIZONA_CLK_ASYNCCLK:
		snd_soc_component_update_bits(component,
					      ARIZONA_ASYNC_SAMPLE_RATE_1,
					      ARIZONA_ASYNC_SAMPLE_RATE_1_MASK,
					      sr_val);
		अगर (base)
			snd_soc_component_update_bits(component,
					base + ARIZONA_AIF_RATE_CTRL,
					ARIZONA_AIF1_RATE_MASK,
					8 << ARIZONA_AIF1_RATE_SHIFT);
		अवरोध;
	शेष:
		arizona_aअगर_err(dai, "Invalid clock %d\n", dai_priv->clk);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool arizona_aअगर_cfg_changed(काष्ठा snd_soc_component *component,
				    पूर्णांक base, पूर्णांक bclk, पूर्णांक lrclk, पूर्णांक frame)
अणु
	पूर्णांक val;

	val = snd_soc_component_पढ़ो(component, base + ARIZONA_AIF_BCLK_CTRL);
	अगर (bclk != (val & ARIZONA_AIF1_BCLK_FREQ_MASK))
		वापस true;

	val = snd_soc_component_पढ़ो(component, base + ARIZONA_AIF_TX_BCLK_RATE);
	अगर (lrclk != (val & ARIZONA_AIF1TX_BCPF_MASK))
		वापस true;

	val = snd_soc_component_पढ़ो(component, base + ARIZONA_AIF_FRAME_CTRL_1);
	अगर (frame != (val & (ARIZONA_AIF1TX_WL_MASK |
			     ARIZONA_AIF1TX_SLOT_LEN_MASK)))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक arizona_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा arizona *arizona = priv->arizona;
	पूर्णांक base = dai->driver->base;
	स्थिर पूर्णांक *rates;
	पूर्णांक i, ret, val;
	पूर्णांक channels = params_channels(params);
	पूर्णांक chan_limit = arizona->pdata.max_channels_घड़ीed[dai->id - 1];
	पूर्णांक tdm_width = arizona->tdm_width[dai->id - 1];
	पूर्णांक tdm_slots = arizona->tdm_slots[dai->id - 1];
	पूर्णांक bclk, lrclk, wl, frame, bclk_target;
	bool reconfig;
	अचिन्हित पूर्णांक aअगर_tx_state, aअगर_rx_state;

	अगर (params_rate(params) % 4000)
		rates = &arizona_44k1_bclk_rates[0];
	अन्यथा
		rates = &arizona_48k_bclk_rates[0];

	wl = params_width(params);

	अगर (tdm_slots) अणु
		arizona_aअगर_dbg(dai, "Configuring for %d %d bit TDM slots\n",
				tdm_slots, tdm_width);
		bclk_target = tdm_slots * tdm_width * params_rate(params);
		channels = tdm_slots;
	पूर्ण अन्यथा अणु
		bclk_target = snd_soc_params_to_bclk(params);
		tdm_width = wl;
	पूर्ण

	अगर (chan_limit && chan_limit < channels) अणु
		arizona_aअगर_dbg(dai, "Limiting to %d channels\n", chan_limit);
		bclk_target /= channels;
		bclk_target *= chan_limit;
	पूर्ण

	/* Force multiple of 2 channels क्रम I2S mode */
	val = snd_soc_component_पढ़ो(component, base + ARIZONA_AIF_FORMAT);
	val &= ARIZONA_AIF1_FMT_MASK;
	अगर ((channels & 1) && (val == ARIZONA_FMT_I2S_MODE)) अणु
		arizona_aअगर_dbg(dai, "Forcing stereo mode\n");
		bclk_target /= channels;
		bclk_target *= channels + 1;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(arizona_44k1_bclk_rates); i++) अणु
		अगर (rates[i] >= bclk_target &&
		    rates[i] % params_rate(params) == 0) अणु
			bclk = i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(arizona_44k1_bclk_rates)) अणु
		arizona_aअगर_err(dai, "Unsupported sample rate %dHz\n",
				params_rate(params));
		वापस -EINVAL;
	पूर्ण

	lrclk = rates[bclk] / params_rate(params);

	arizona_aअगर_dbg(dai, "BCLK %dHz LRCLK %dHz\n",
			rates[bclk], rates[bclk] / lrclk);

	frame = wl << ARIZONA_AIF1TX_WL_SHIFT | tdm_width;

	reconfig = arizona_aअगर_cfg_changed(component, base, bclk, lrclk, frame);

	अगर (reconfig) अणु
		/* Save AIF TX/RX state */
		aअगर_tx_state = snd_soc_component_पढ़ो(component,
					    base + ARIZONA_AIF_TX_ENABLES);
		aअगर_rx_state = snd_soc_component_पढ़ो(component,
					    base + ARIZONA_AIF_RX_ENABLES);
		/* Disable AIF TX/RX beक्रमe reconfiguring it */
		regmap_update_bits_async(arizona->regmap,
					 base + ARIZONA_AIF_TX_ENABLES,
					 0xff, 0x0);
		regmap_update_bits(arizona->regmap,
				   base + ARIZONA_AIF_RX_ENABLES, 0xff, 0x0);
	पूर्ण

	ret = arizona_hw_params_rate(substream, params, dai);
	अगर (ret != 0)
		जाओ restore_aअगर;

	अगर (reconfig) अणु
		regmap_update_bits_async(arizona->regmap,
					 base + ARIZONA_AIF_BCLK_CTRL,
					 ARIZONA_AIF1_BCLK_FREQ_MASK, bclk);
		regmap_update_bits_async(arizona->regmap,
					 base + ARIZONA_AIF_TX_BCLK_RATE,
					 ARIZONA_AIF1TX_BCPF_MASK, lrclk);
		regmap_update_bits_async(arizona->regmap,
					 base + ARIZONA_AIF_RX_BCLK_RATE,
					 ARIZONA_AIF1RX_BCPF_MASK, lrclk);
		regmap_update_bits_async(arizona->regmap,
					 base + ARIZONA_AIF_FRAME_CTRL_1,
					 ARIZONA_AIF1TX_WL_MASK |
					 ARIZONA_AIF1TX_SLOT_LEN_MASK, frame);
		regmap_update_bits(arizona->regmap,
				   base + ARIZONA_AIF_FRAME_CTRL_2,
				   ARIZONA_AIF1RX_WL_MASK |
				   ARIZONA_AIF1RX_SLOT_LEN_MASK, frame);
	पूर्ण

restore_aअगर:
	अगर (reconfig) अणु
		/* Restore AIF TX/RX state */
		regmap_update_bits_async(arizona->regmap,
					 base + ARIZONA_AIF_TX_ENABLES,
					 0xff, aअगर_tx_state);
		regmap_update_bits(arizona->regmap,
				   base + ARIZONA_AIF_RX_ENABLES,
				   0xff, aअगर_rx_state);
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर अक्षर *arizona_dai_clk_str(पूर्णांक clk_id)
अणु
	चयन (clk_id) अणु
	हाल ARIZONA_CLK_SYSCLK:
		वापस "SYSCLK";
	हाल ARIZONA_CLK_ASYNCCLK:
		वापस "ASYNCCLK";
	शेष:
		वापस "Unknown clock";
	पूर्ण
पूर्ण

अटल पूर्णांक arizona_dai_set_sysclk(काष्ठा snd_soc_dai *dai,
				  पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा arizona_dai_priv *dai_priv = &priv->dai[dai->id - 1];
	काष्ठा snd_soc_dapm_route routes[2];

	चयन (clk_id) अणु
	हाल ARIZONA_CLK_SYSCLK:
	हाल ARIZONA_CLK_ASYNCCLK:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (clk_id == dai_priv->clk)
		वापस 0;

	अगर (snd_soc_dai_active(dai)) अणु
		dev_err(component->dev, "Can't change clock on active DAI %d\n",
			dai->id);
		वापस -EBUSY;
	पूर्ण

	dev_dbg(component->dev, "Setting AIF%d to %s\n", dai->id + 1,
		arizona_dai_clk_str(clk_id));

	स_रखो(&routes, 0, माप(routes));
	routes[0].sink = dai->driver->capture.stream_name;
	routes[1].sink = dai->driver->playback.stream_name;

	routes[0].source = arizona_dai_clk_str(dai_priv->clk);
	routes[1].source = arizona_dai_clk_str(dai_priv->clk);
	snd_soc_dapm_del_routes(dapm, routes, ARRAY_SIZE(routes));

	routes[0].source = arizona_dai_clk_str(clk_id);
	routes[1].source = arizona_dai_clk_str(clk_id);
	snd_soc_dapm_add_routes(dapm, routes, ARRAY_SIZE(routes));

	dai_priv->clk = clk_id;

	वापस snd_soc_dapm_sync(dapm);
पूर्ण

अटल पूर्णांक arizona_set_tristate(काष्ठा snd_soc_dai *dai, पूर्णांक tristate)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक base = dai->driver->base;
	अचिन्हित पूर्णांक reg;

	अगर (tristate)
		reg = ARIZONA_AIF1_TRI;
	अन्यथा
		reg = 0;

	वापस snd_soc_component_update_bits(component,
					     base + ARIZONA_AIF_RATE_CTRL,
					     ARIZONA_AIF1_TRI, reg);
पूर्ण

अटल व्योम arizona_set_channels_to_mask(काष्ठा snd_soc_dai *dai,
					 अचिन्हित पूर्णांक base,
					 पूर्णांक channels, अचिन्हित पूर्णांक mask)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा arizona *arizona = priv->arizona;
	पूर्णांक slot, i;

	क्रम (i = 0; i < channels; ++i) अणु
		slot = ffs(mask) - 1;
		अगर (slot < 0)
			वापस;

		regmap_ग_लिखो(arizona->regmap, base + i, slot);

		mask &= ~(1 << slot);
	पूर्ण

	अगर (mask)
		arizona_aअगर_warn(dai, "Too many channels in TDM mask\n");
पूर्ण

अटल पूर्णांक arizona_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
				अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा arizona_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा arizona *arizona = priv->arizona;
	पूर्णांक base = dai->driver->base;
	पूर्णांक rx_max_chan = dai->driver->playback.channels_max;
	पूर्णांक tx_max_chan = dai->driver->capture.channels_max;

	/* Only support TDM क्रम the physical AIFs */
	अगर (dai->id > ARIZONA_MAX_AIF)
		वापस -ENOTSUPP;

	अगर (slots == 0) अणु
		tx_mask = (1 << tx_max_chan) - 1;
		rx_mask = (1 << rx_max_chan) - 1;
	पूर्ण

	arizona_set_channels_to_mask(dai, base + ARIZONA_AIF_FRAME_CTRL_3,
				     tx_max_chan, tx_mask);
	arizona_set_channels_to_mask(dai, base + ARIZONA_AIF_FRAME_CTRL_11,
				     rx_max_chan, rx_mask);

	arizona->tdm_width[dai->id - 1] = slot_width;
	arizona->tdm_slots[dai->id - 1] = slots;

	वापस 0;
पूर्ण

स्थिर काष्ठा snd_soc_dai_ops arizona_dai_ops = अणु
	.startup = arizona_startup,
	.set_fmt = arizona_set_fmt,
	.set_tdm_slot = arizona_set_tdm_slot,
	.hw_params = arizona_hw_params,
	.set_sysclk = arizona_dai_set_sysclk,
	.set_tristate = arizona_set_tristate,
पूर्ण;
EXPORT_SYMBOL_GPL(arizona_dai_ops);

स्थिर काष्ठा snd_soc_dai_ops arizona_simple_dai_ops = अणु
	.startup = arizona_startup,
	.hw_params = arizona_hw_params_rate,
	.set_sysclk = arizona_dai_set_sysclk,
पूर्ण;
EXPORT_SYMBOL_GPL(arizona_simple_dai_ops);

पूर्णांक arizona_init_dai(काष्ठा arizona_priv *priv, पूर्णांक id)
अणु
	काष्ठा arizona_dai_priv *dai_priv = &priv->dai[id];

	dai_priv->clk = ARIZONA_CLK_SYSCLK;
	dai_priv->स्थिरraपूर्णांक = arizona_स्थिरraपूर्णांक;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_init_dai);

अटल काष्ठा अणु
	अचिन्हित पूर्णांक min;
	अचिन्हित पूर्णांक max;
	u16 fratio;
	पूर्णांक ratio;
पूर्ण fll_fratios[] = अणु
	अणु       0,    64000, 4, 16 पूर्ण,
	अणु   64000,   128000, 3,  8 पूर्ण,
	अणु  128000,   256000, 2,  4 पूर्ण,
	अणु  256000,  1000000, 1,  2 पूर्ण,
	अणु 1000000, 13500000, 0,  1 पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pseuकरो_fref_max[ARIZONA_FLL_MAX_FRATIO] = अणु
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

अटल काष्ठा अणु
	अचिन्हित पूर्णांक min;
	अचिन्हित पूर्णांक max;
	u16 gain;
पूर्ण fll_gains[] = अणु
	अणु       0,   256000, 0 पूर्ण,
	अणु  256000,  1000000, 2 पूर्ण,
	अणु 1000000, 13500000, 4 पूर्ण,
पूर्ण;

काष्ठा arizona_fll_cfg अणु
	पूर्णांक n;
	अचिन्हित पूर्णांक theta;
	अचिन्हित पूर्णांक lambda;
	पूर्णांक refभाग;
	पूर्णांक outभाग;
	पूर्णांक fratio;
	पूर्णांक gain;
पूर्ण;

अटल पूर्णांक arizona_validate_fll(काष्ठा arizona_fll *fll,
				अचिन्हित पूर्णांक Fref,
				अचिन्हित पूर्णांक Fout)
अणु
	अचिन्हित पूर्णांक Fvco_min;

	अगर (fll->fout && Fout != fll->fout) अणु
		arizona_fll_err(fll,
				"Can't change output on active FLL\n");
		वापस -EINVAL;
	पूर्ण

	अगर (Fref / ARIZONA_FLL_MAX_REFDIV > ARIZONA_FLL_MAX_FREF) अणु
		arizona_fll_err(fll,
				"Can't scale %dMHz in to <=13.5MHz\n",
				Fref);
		वापस -EINVAL;
	पूर्ण

	Fvco_min = ARIZONA_FLL_MIN_FVCO * fll->vco_mult;
	अगर (Fout * ARIZONA_FLL_MAX_OUTDIV < Fvco_min) अणु
		arizona_fll_err(fll, "No FLL_OUTDIV for Fout=%uHz\n",
				Fout);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक arizona_find_fratio(अचिन्हित पूर्णांक Fref, पूर्णांक *fratio)
अणु
	पूर्णांक i;

	/* Find an appropriate FLL_FRATIO */
	क्रम (i = 0; i < ARRAY_SIZE(fll_fratios); i++) अणु
		अगर (fll_fratios[i].min <= Fref && Fref <= fll_fratios[i].max) अणु
			अगर (fratio)
				*fratio = fll_fratios[i].fratio;
			वापस fll_fratios[i].ratio;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक arizona_calc_fratio(काष्ठा arizona_fll *fll,
			       काष्ठा arizona_fll_cfg *cfg,
			       अचिन्हित पूर्णांक target,
			       अचिन्हित पूर्णांक Fref, bool sync)
अणु
	पूर्णांक init_ratio, ratio;
	पूर्णांक refभाग, भाग;

	/* Fref must be <=13.5MHz, find initial refभाग */
	भाग = 1;
	cfg->refभाग = 0;
	जबतक (Fref > ARIZONA_FLL_MAX_FREF) अणु
		भाग *= 2;
		Fref /= 2;
		cfg->refभाग++;

		अगर (भाग > ARIZONA_FLL_MAX_REFDIV)
			वापस -EINVAL;
	पूर्ण

	/* Find an appropriate FLL_FRATIO */
	init_ratio = arizona_find_fratio(Fref, &cfg->fratio);
	अगर (init_ratio < 0) अणु
		arizona_fll_err(fll, "Unable to find FRATIO for Fref=%uHz\n",
				Fref);
		वापस init_ratio;
	पूर्ण

	चयन (fll->arizona->type) अणु
	हाल WM5102:
	हाल WM8997:
		वापस init_ratio;
	हाल WM5110:
	हाल WM8280:
		अगर (fll->arizona->rev < 3 || sync)
			वापस init_ratio;
		अवरोध;
	शेष:
		अगर (sync)
			वापस init_ratio;
		अवरोध;
	पूर्ण

	cfg->fratio = init_ratio - 1;

	/* Adjust FRATIO/refभाग to aव्योम पूर्णांकeger mode अगर possible */
	refभाग = cfg->refभाग;

	arizona_fll_dbg(fll, "pseudo: initial ratio=%u fref=%u refdiv=%u\n",
			init_ratio, Fref, refभाग);

	जबतक (भाग <= ARIZONA_FLL_MAX_REFDIV) अणु
		/* start from init_ratio because this may alपढ़ोy give a
		 * fractional N.K
		 */
		क्रम (ratio = init_ratio; ratio > 0; ratio--) अणु
			अगर (target % (ratio * Fref)) अणु
				cfg->refभाग = refभाग;
				cfg->fratio = ratio - 1;
				arizona_fll_dbg(fll,
					"pseudo: found fref=%u refdiv=%d(%d) ratio=%d\n",
					Fref, refभाग, भाग, ratio);
				वापस ratio;
			पूर्ण
		पूर्ण

		क्रम (ratio = init_ratio + 1; ratio <= ARIZONA_FLL_MAX_FRATIO;
		     ratio++) अणु
			अगर ((ARIZONA_FLL_VCO_CORNER / 2) /
			    (fll->vco_mult * ratio) < Fref) अणु
				arizona_fll_dbg(fll, "pseudo: hit VCO corner\n");
				अवरोध;
			पूर्ण

			अगर (Fref > pseuकरो_fref_max[ratio - 1]) अणु
				arizona_fll_dbg(fll,
					"pseudo: exceeded max fref(%u) for ratio=%u\n",
					pseuकरो_fref_max[ratio - 1],
					ratio);
				अवरोध;
			पूर्ण

			अगर (target % (ratio * Fref)) अणु
				cfg->refभाग = refभाग;
				cfg->fratio = ratio - 1;
				arizona_fll_dbg(fll,
					"pseudo: found fref=%u refdiv=%d(%d) ratio=%d\n",
					Fref, refभाग, भाग, ratio);
				वापस ratio;
			पूर्ण
		पूर्ण

		भाग *= 2;
		Fref /= 2;
		refभाग++;
		init_ratio = arizona_find_fratio(Fref, शून्य);
		arizona_fll_dbg(fll,
				"pseudo: change fref=%u refdiv=%d(%d) ratio=%u\n",
				Fref, refभाग, भाग, init_ratio);
	पूर्ण

	arizona_fll_warn(fll, "Falling back to integer mode operation\n");
	वापस cfg->fratio + 1;
पूर्ण

अटल पूर्णांक arizona_calc_fll(काष्ठा arizona_fll *fll,
			    काष्ठा arizona_fll_cfg *cfg,
			    अचिन्हित पूर्णांक Fref, bool sync)
अणु
	अचिन्हित पूर्णांक target, भाग, gcd_fll;
	पूर्णांक i, ratio;

	arizona_fll_dbg(fll, "Fref=%u Fout=%u\n", Fref, fll->fout);

	/* Fvco should be over the targt; करोn't check the upper bound */
	भाग = ARIZONA_FLL_MIN_OUTDIV;
	जबतक (fll->fout * भाग < ARIZONA_FLL_MIN_FVCO * fll->vco_mult) अणु
		भाग++;
		अगर (भाग > ARIZONA_FLL_MAX_OUTDIV)
			वापस -EINVAL;
	पूर्ण
	target = fll->fout * भाग / fll->vco_mult;
	cfg->outभाग = भाग;

	arizona_fll_dbg(fll, "Fvco=%dHz\n", target);

	/* Find an appropriate FLL_FRATIO and refभाग */
	ratio = arizona_calc_fratio(fll, cfg, target, Fref, sync);
	अगर (ratio < 0)
		वापस ratio;

	/* Apply the भागision क्रम our reमुख्यing calculations */
	Fref = Fref / (1 << cfg->refभाग);

	cfg->n = target / (ratio * Fref);

	अगर (target % (ratio * Fref)) अणु
		gcd_fll = gcd(target, ratio * Fref);
		arizona_fll_dbg(fll, "GCD=%u\n", gcd_fll);

		cfg->theta = (target - (cfg->n * ratio * Fref))
			/ gcd_fll;
		cfg->lambda = (ratio * Fref) / gcd_fll;
	पूर्ण अन्यथा अणु
		cfg->theta = 0;
		cfg->lambda = 0;
	पूर्ण

	/* Round करोwn to 16bit range with cost of accuracy lost.
	 * Denominator must be bigger than numerator so we only
	 * take care of it.
	 */
	जबतक (cfg->lambda >= (1 << 16)) अणु
		cfg->theta >>= 1;
		cfg->lambda >>= 1;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(fll_gains); i++) अणु
		अगर (fll_gains[i].min <= Fref && Fref <= fll_gains[i].max) अणु
			cfg->gain = fll_gains[i].gain;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(fll_gains)) अणु
		arizona_fll_err(fll, "Unable to find gain for Fref=%uHz\n",
				Fref);
		वापस -EINVAL;
	पूर्ण

	arizona_fll_dbg(fll, "N=%d THETA=%d LAMBDA=%d\n",
			cfg->n, cfg->theta, cfg->lambda);
	arizona_fll_dbg(fll, "FRATIO=0x%x(%d) OUTDIV=%d REFCLK_DIV=0x%x(%d)\n",
			cfg->fratio, ratio, cfg->outभाग,
			cfg->refभाग, 1 << cfg->refभाग);
	arizona_fll_dbg(fll, "GAIN=0x%x(%d)\n", cfg->gain, 1 << cfg->gain);

	वापस 0;
पूर्ण

अटल व्योम arizona_apply_fll(काष्ठा arizona *arizona, अचिन्हित पूर्णांक base,
			      काष्ठा arizona_fll_cfg *cfg, पूर्णांक source,
			      bool sync)
अणु
	regmap_update_bits_async(arizona->regmap, base + 3,
				 ARIZONA_FLL1_THETA_MASK, cfg->theta);
	regmap_update_bits_async(arizona->regmap, base + 4,
				 ARIZONA_FLL1_LAMBDA_MASK, cfg->lambda);
	regmap_update_bits_async(arizona->regmap, base + 5,
				 ARIZONA_FLL1_FRATIO_MASK,
				 cfg->fratio << ARIZONA_FLL1_FRATIO_SHIFT);
	regmap_update_bits_async(arizona->regmap, base + 6,
				 ARIZONA_FLL1_CLK_REF_DIV_MASK |
				 ARIZONA_FLL1_CLK_REF_SRC_MASK,
				 cfg->refभाग << ARIZONA_FLL1_CLK_REF_DIV_SHIFT |
				 source << ARIZONA_FLL1_CLK_REF_SRC_SHIFT);

	अगर (sync) अणु
		regmap_update_bits(arizona->regmap, base + 0x7,
				   ARIZONA_FLL1_GAIN_MASK,
				   cfg->gain << ARIZONA_FLL1_GAIN_SHIFT);
	पूर्ण अन्यथा अणु
		regmap_update_bits(arizona->regmap, base + 0x5,
				   ARIZONA_FLL1_OUTDIV_MASK,
				   cfg->outभाग << ARIZONA_FLL1_OUTDIV_SHIFT);
		regmap_update_bits(arizona->regmap, base + 0x9,
				   ARIZONA_FLL1_GAIN_MASK,
				   cfg->gain << ARIZONA_FLL1_GAIN_SHIFT);
	पूर्ण

	regmap_update_bits_async(arizona->regmap, base + 2,
				 ARIZONA_FLL1_CTRL_UPD | ARIZONA_FLL1_N_MASK,
				 ARIZONA_FLL1_CTRL_UPD | cfg->n);
पूर्ण

अटल पूर्णांक arizona_is_enabled_fll(काष्ठा arizona_fll *fll, पूर्णांक base)
अणु
	काष्ठा arizona *arizona = fll->arizona;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	ret = regmap_पढ़ो(arizona->regmap, base + 1, &reg);
	अगर (ret != 0) अणु
		arizona_fll_err(fll, "Failed to read current state: %d\n",
				ret);
		वापस ret;
	पूर्ण

	वापस reg & ARIZONA_FLL1_ENA;
पूर्ण

अटल पूर्णांक arizona_set_fll_clks(काष्ठा arizona_fll *fll, पूर्णांक base, bool ena)
अणु
	काष्ठा arizona *arizona = fll->arizona;
	अचिन्हित पूर्णांक val;
	काष्ठा clk *clk;
	पूर्णांक ret;

	ret = regmap_पढ़ो(arizona->regmap, base + 6, &val);
	अगर (ret != 0) अणु
		arizona_fll_err(fll, "Failed to read current source: %d\n",
				ret);
		वापस ret;
	पूर्ण

	val &= ARIZONA_FLL1_CLK_REF_SRC_MASK;
	val >>= ARIZONA_FLL1_CLK_REF_SRC_SHIFT;

	चयन (val) अणु
	हाल ARIZONA_FLL_SRC_MCLK1:
		clk = arizona->mclk[ARIZONA_MCLK1];
		अवरोध;
	हाल ARIZONA_FLL_SRC_MCLK2:
		clk = arizona->mclk[ARIZONA_MCLK2];
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

अटल पूर्णांक arizona_enable_fll(काष्ठा arizona_fll *fll)
अणु
	काष्ठा arizona *arizona = fll->arizona;
	bool use_sync = false;
	पूर्णांक alपढ़ोy_enabled = arizona_is_enabled_fll(fll, fll->base);
	पूर्णांक sync_enabled = arizona_is_enabled_fll(fll, fll->base + 0x10);
	काष्ठा arizona_fll_cfg cfg;
	पूर्णांक i;
	अचिन्हित पूर्णांक val;

	अगर (alपढ़ोy_enabled < 0)
		वापस alपढ़ोy_enabled;
	अगर (sync_enabled < 0)
		वापस sync_enabled;

	अगर (alपढ़ोy_enabled) अणु
		/* Facilitate smooth refclk across the transition */
		regmap_update_bits(fll->arizona->regmap, fll->base + 1,
				   ARIZONA_FLL1_FREERUN, ARIZONA_FLL1_FREERUN);
		udelay(32);
		regmap_update_bits_async(fll->arizona->regmap, fll->base + 0x9,
					 ARIZONA_FLL1_GAIN_MASK, 0);

		अगर (arizona_is_enabled_fll(fll, fll->base + 0x10) > 0)
			arizona_set_fll_clks(fll, fll->base + 0x10, false);
		arizona_set_fll_clks(fll, fll->base, false);
	पूर्ण

	/*
	 * If we have both REFCLK and SYNCCLK then enable both,
	 * otherwise apply the SYNCCLK settings to REFCLK.
	 */
	अगर (fll->ref_src >= 0 && fll->ref_freq &&
	    fll->ref_src != fll->sync_src) अणु
		arizona_calc_fll(fll, &cfg, fll->ref_freq, false);

		/* Ref path hardcodes lambda to 65536 when sync is on */
		अगर (fll->sync_src >= 0 && cfg.lambda)
			cfg.theta = (cfg.theta * (1 << 16)) / cfg.lambda;

		arizona_apply_fll(arizona, fll->base, &cfg, fll->ref_src,
				  false);
		अगर (fll->sync_src >= 0) अणु
			arizona_calc_fll(fll, &cfg, fll->sync_freq, true);

			arizona_apply_fll(arizona, fll->base + 0x10, &cfg,
					  fll->sync_src, true);
			use_sync = true;
		पूर्ण
	पूर्ण अन्यथा अगर (fll->sync_src >= 0) अणु
		arizona_calc_fll(fll, &cfg, fll->sync_freq, false);

		arizona_apply_fll(arizona, fll->base, &cfg,
				  fll->sync_src, false);

		regmap_update_bits_async(arizona->regmap, fll->base + 0x11,
					 ARIZONA_FLL1_SYNC_ENA, 0);
	पूर्ण अन्यथा अणु
		arizona_fll_err(fll, "No clocks provided\n");
		वापस -EINVAL;
	पूर्ण

	अगर (alपढ़ोy_enabled && !!sync_enabled != use_sync)
		arizona_fll_warn(fll, "Synchroniser changed on active FLL\n");

	/*
	 * Increase the bandwidth अगर we're not using a low frequency
	 * sync source.
	 */
	अगर (use_sync && fll->sync_freq > 100000)
		regmap_update_bits_async(arizona->regmap, fll->base + 0x17,
					 ARIZONA_FLL1_SYNC_BW, 0);
	अन्यथा
		regmap_update_bits_async(arizona->regmap, fll->base + 0x17,
					 ARIZONA_FLL1_SYNC_BW,
					 ARIZONA_FLL1_SYNC_BW);

	अगर (!alपढ़ोy_enabled)
		pm_runसमय_get_sync(arizona->dev);

	अगर (use_sync) अणु
		arizona_set_fll_clks(fll, fll->base + 0x10, true);
		regmap_update_bits_async(arizona->regmap, fll->base + 0x11,
					 ARIZONA_FLL1_SYNC_ENA,
					 ARIZONA_FLL1_SYNC_ENA);
	पूर्ण
	arizona_set_fll_clks(fll, fll->base, true);
	regmap_update_bits_async(arizona->regmap, fll->base + 1,
				 ARIZONA_FLL1_ENA, ARIZONA_FLL1_ENA);

	अगर (alपढ़ोy_enabled)
		regmap_update_bits_async(arizona->regmap, fll->base + 1,
					 ARIZONA_FLL1_FREERUN, 0);

	arizona_fll_dbg(fll, "Waiting for FLL lock...\n");
	val = 0;
	क्रम (i = 0; i < 15; i++) अणु
		अगर (i < 5)
			usleep_range(200, 400);
		अन्यथा
			msleep(20);

		regmap_पढ़ो(arizona->regmap,
			    ARIZONA_INTERRUPT_RAW_STATUS_5,
			    &val);
		अगर (val & (ARIZONA_FLL1_CLOCK_OK_STS << (fll->id - 1)))
			अवरोध;
	पूर्ण
	अगर (i == 15)
		arizona_fll_warn(fll, "Timed out waiting for lock\n");
	अन्यथा
		arizona_fll_dbg(fll, "FLL locked (%d polls)\n", i);

	वापस 0;
पूर्ण

अटल व्योम arizona_disable_fll(काष्ठा arizona_fll *fll)
अणु
	काष्ठा arizona *arizona = fll->arizona;
	bool ref_change, sync_change;

	regmap_update_bits_async(arizona->regmap, fll->base + 1,
				 ARIZONA_FLL1_FREERUN, ARIZONA_FLL1_FREERUN);
	regmap_update_bits_check(arizona->regmap, fll->base + 1,
				 ARIZONA_FLL1_ENA, 0, &ref_change);
	regmap_update_bits_check(arizona->regmap, fll->base + 0x11,
				 ARIZONA_FLL1_SYNC_ENA, 0, &sync_change);
	regmap_update_bits_async(arizona->regmap, fll->base + 1,
				 ARIZONA_FLL1_FREERUN, 0);

	अगर (sync_change)
		arizona_set_fll_clks(fll, fll->base + 0x10, false);

	अगर (ref_change) अणु
		arizona_set_fll_clks(fll, fll->base, false);
		pm_runसमय_put_स्वतःsuspend(arizona->dev);
	पूर्ण
पूर्ण

पूर्णांक arizona_set_fll_refclk(काष्ठा arizona_fll *fll, पूर्णांक source,
			   अचिन्हित पूर्णांक Fref, अचिन्हित पूर्णांक Fout)
अणु
	पूर्णांक ret = 0;

	अगर (fll->ref_src == source && fll->ref_freq == Fref)
		वापस 0;

	अगर (fll->fout && Fref > 0) अणु
		ret = arizona_validate_fll(fll, Fref, fll->fout);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	fll->ref_src = source;
	fll->ref_freq = Fref;

	अगर (fll->fout && Fref > 0)
		ret = arizona_enable_fll(fll);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_set_fll_refclk);

पूर्णांक arizona_set_fll(काष्ठा arizona_fll *fll, पूर्णांक source,
		    अचिन्हित पूर्णांक Fref, अचिन्हित पूर्णांक Fout)
अणु
	पूर्णांक ret = 0;

	अगर (fll->sync_src == source &&
	    fll->sync_freq == Fref && fll->fout == Fout)
		वापस 0;

	अगर (Fout) अणु
		अगर (fll->ref_src >= 0) अणु
			ret = arizona_validate_fll(fll, fll->ref_freq, Fout);
			अगर (ret != 0)
				वापस ret;
		पूर्ण

		ret = arizona_validate_fll(fll, Fref, Fout);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	fll->sync_src = source;
	fll->sync_freq = Fref;
	fll->fout = Fout;

	अगर (Fout)
		ret = arizona_enable_fll(fll);
	अन्यथा
		arizona_disable_fll(fll);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_set_fll);

पूर्णांक arizona_init_fll(काष्ठा arizona *arizona, पूर्णांक id, पूर्णांक base, पूर्णांक lock_irq,
		     पूर्णांक ok_irq, काष्ठा arizona_fll *fll)
अणु
	अचिन्हित पूर्णांक val;

	fll->id = id;
	fll->base = base;
	fll->arizona = arizona;
	fll->sync_src = ARIZONA_FLL_SRC_NONE;

	/* Configure शेष refclk to 32kHz अगर we have one */
	regmap_पढ़ो(arizona->regmap, ARIZONA_CLOCK_32K_1, &val);
	चयन (val & ARIZONA_CLK_32K_SRC_MASK) अणु
	हाल ARIZONA_CLK_SRC_MCLK1:
	हाल ARIZONA_CLK_SRC_MCLK2:
		fll->ref_src = val & ARIZONA_CLK_32K_SRC_MASK;
		अवरोध;
	शेष:
		fll->ref_src = ARIZONA_FLL_SRC_NONE;
	पूर्ण
	fll->ref_freq = 32768;

	snम_लिखो(fll->lock_name, माप(fll->lock_name), "FLL%d lock", id);
	snम_लिखो(fll->घड़ी_ok_name, माप(fll->घड़ी_ok_name),
		 "FLL%d clock OK", id);

	regmap_update_bits(arizona->regmap, fll->base + 1,
			   ARIZONA_FLL1_FREERUN, 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_init_fll);

/**
 * arizona_set_output_mode - Set the mode of the specअगरied output
 *
 * @component: Device to configure
 * @output: Output number
 * @dअगरf: True to set the output to dअगरferential mode
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
पूर्णांक arizona_set_output_mode(काष्ठा snd_soc_component *component, पूर्णांक output,
			    bool dअगरf)
अणु
	अचिन्हित पूर्णांक reg, val;

	अगर (output < 1 || output > 6)
		वापस -EINVAL;

	reg = ARIZONA_OUTPUT_PATH_CONFIG_1L + (output - 1) * 8;

	अगर (dअगरf)
		val = ARIZONA_OUT1_MONO;
	अन्यथा
		val = 0;

	वापस snd_soc_component_update_bits(component, reg,
					     ARIZONA_OUT1_MONO, val);
पूर्ण
EXPORT_SYMBOL_GPL(arizona_set_output_mode);

अटल स्थिर काष्ठा soc_क्रमागत arizona_adsp2_rate_क्रमागत[] = अणु
	SOC_VALUE_ENUM_SINGLE(ARIZONA_DSP1_CONTROL_1,
			      ARIZONA_DSP1_RATE_SHIFT, 0xf,
			      ARIZONA_RATE_ENUM_SIZE,
			      arizona_rate_text, arizona_rate_val),
	SOC_VALUE_ENUM_SINGLE(ARIZONA_DSP2_CONTROL_1,
			      ARIZONA_DSP1_RATE_SHIFT, 0xf,
			      ARIZONA_RATE_ENUM_SIZE,
			      arizona_rate_text, arizona_rate_val),
	SOC_VALUE_ENUM_SINGLE(ARIZONA_DSP3_CONTROL_1,
			      ARIZONA_DSP1_RATE_SHIFT, 0xf,
			      ARIZONA_RATE_ENUM_SIZE,
			      arizona_rate_text, arizona_rate_val),
	SOC_VALUE_ENUM_SINGLE(ARIZONA_DSP4_CONTROL_1,
			      ARIZONA_DSP1_RATE_SHIFT, 0xf,
			      ARIZONA_RATE_ENUM_SIZE,
			      arizona_rate_text, arizona_rate_val),
पूर्ण;

स्थिर काष्ठा snd_kcontrol_new arizona_adsp2_rate_controls[] = अणु
	SOC_ENUM("DSP1 Rate", arizona_adsp2_rate_क्रमागत[0]),
	SOC_ENUM("DSP2 Rate", arizona_adsp2_rate_क्रमागत[1]),
	SOC_ENUM("DSP3 Rate", arizona_adsp2_rate_क्रमागत[2]),
	SOC_ENUM("DSP4 Rate", arizona_adsp2_rate_क्रमागत[3]),
पूर्ण;
EXPORT_SYMBOL_GPL(arizona_adsp2_rate_controls);

अटल bool arizona_eq_filter_unstable(bool mode, __be16 _a, __be16 _b)
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

पूर्णांक arizona_eq_coeff_put(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा arizona *arizona = dev_get_drvdata(component->dev->parent);
	काष्ठा soc_bytes *params = (व्योम *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक val;
	__be16 *data;
	पूर्णांक len;
	पूर्णांक ret;

	len = params->num_regs * regmap_get_val_bytes(arizona->regmap);

	data = kmemdup(ucontrol->value.bytes.data, len, GFP_KERNEL | GFP_DMA);
	अगर (!data)
		वापस -ENOMEM;

	data[0] &= cpu_to_be16(ARIZONA_EQ1_B1_MODE);

	अगर (arizona_eq_filter_unstable(!!data[0], data[1], data[2]) ||
	    arizona_eq_filter_unstable(true, data[4], data[5]) ||
	    arizona_eq_filter_unstable(true, data[8], data[9]) ||
	    arizona_eq_filter_unstable(true, data[12], data[13]) ||
	    arizona_eq_filter_unstable(false, data[16], data[17])) अणु
		dev_err(arizona->dev, "Rejecting unstable EQ coefficients\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = regmap_पढ़ो(arizona->regmap, params->base, &val);
	अगर (ret != 0)
		जाओ out;

	val &= ~ARIZONA_EQ1_B1_MODE;
	data[0] |= cpu_to_be16(val);

	ret = regmap_raw_ग_लिखो(arizona->regmap, params->base, data, len);

out:
	kमुक्त(data);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_eq_coeff_put);

पूर्णांक arizona_lhpf_coeff_put(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा arizona *arizona = dev_get_drvdata(component->dev->parent);
	__be16 *data = (__be16 *)ucontrol->value.bytes.data;
	s16 val = be16_to_cpu(*data);

	अगर (असल(val) >= 4096) अणु
		dev_err(arizona->dev, "Rejecting unstable LHPF coefficients\n");
		वापस -EINVAL;
	पूर्ण

	वापस snd_soc_bytes_put(kcontrol, ucontrol);
पूर्ण
EXPORT_SYMBOL_GPL(arizona_lhpf_coeff_put);

पूर्णांक arizona_of_get_audio_pdata(काष्ठा arizona *arizona)
अणु
	काष्ठा arizona_pdata *pdata = &arizona->pdata;
	काष्ठा device_node *np = arizona->dev->of_node;
	काष्ठा property *prop;
	स्थिर __be32 *cur;
	u32 val;
	u32 pdm_val[ARIZONA_MAX_PDM_SPK];
	पूर्णांक ret;
	पूर्णांक count = 0;

	count = 0;
	of_property_क्रम_each_u32(np, "wlf,inmode", prop, cur, val) अणु
		अगर (count == ARRAY_SIZE(pdata->inmode))
			अवरोध;

		pdata->inmode[count] = val;
		count++;
	पूर्ण

	count = 0;
	of_property_क्रम_each_u32(np, "wlf,dmic-ref", prop, cur, val) अणु
		अगर (count == ARRAY_SIZE(pdata->dmic_ref))
			अवरोध;

		pdata->dmic_ref[count] = val;
		count++;
	पूर्ण

	count = 0;
	of_property_क्रम_each_u32(np, "wlf,out-mono", prop, cur, val) अणु
		अगर (count == ARRAY_SIZE(pdata->out_mono))
			अवरोध;

		pdata->out_mono[count] = !!val;
		count++;
	पूर्ण

	count = 0;
	of_property_क्रम_each_u32(np, "wlf,max-channels-clocked", prop, cur, val) अणु
		अगर (count == ARRAY_SIZE(pdata->max_channels_घड़ीed))
			अवरोध;

		pdata->max_channels_घड़ीed[count] = val;
		count++;
	पूर्ण

	count = 0;
	of_property_क्रम_each_u32(np, "wlf,out-volume-limit", prop, cur, val) अणु
		अगर (count == ARRAY_SIZE(pdata->out_vol_limit))
			अवरोध;

		pdata->out_vol_limit[count] = val;
		count++;
	पूर्ण

	ret = of_property_पढ़ो_u32_array(np, "wlf,spk-fmt",
					 pdm_val, ARRAY_SIZE(pdm_val));

	अगर (ret >= 0)
		क्रम (count = 0; count < ARRAY_SIZE(pdata->spk_fmt); ++count)
			pdata->spk_fmt[count] = pdm_val[count];

	ret = of_property_पढ़ो_u32_array(np, "wlf,spk-mute",
					 pdm_val, ARRAY_SIZE(pdm_val));

	अगर (ret >= 0)
		क्रम (count = 0; count < ARRAY_SIZE(pdata->spk_mute); ++count)
			pdata->spk_mute[count] = pdm_val[count];

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_of_get_audio_pdata);

MODULE_DESCRIPTION("ASoC Wolfson Arizona class device support");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
