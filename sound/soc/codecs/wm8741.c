<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8741.c  --  WM8741 ALSA SoC Audio driver
 *
 * Copyright 2010-1 Wolfson Microelectronics plc
 *
 * Author: Ian Lartey <ian@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "wm8741.h"

#घोषणा WM8741_NUM_SUPPLIES 2
अटल स्थिर अक्षर *wm8741_supply_names[WM8741_NUM_SUPPLIES] = अणु
	"AVDD",
	"DVDD",
पूर्ण;

/* codec निजी data */
काष्ठा wm8741_priv अणु
	काष्ठा wm8741_platक्रमm_data pdata;
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data supplies[WM8741_NUM_SUPPLIES];
	अचिन्हित पूर्णांक sysclk;
	स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list *sysclk_स्थिरraपूर्णांकs;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष wm8741_reg_शेषs[] = अणु
	अणु  0, 0x0000 पूर्ण,     /* R0  - DACLLSB Attenuation */
	अणु  1, 0x0000 पूर्ण,     /* R1  - DACLMSB Attenuation */
	अणु  2, 0x0000 पूर्ण,     /* R2  - DACRLSB Attenuation */
	अणु  3, 0x0000 पूर्ण,     /* R3  - DACRMSB Attenuation */
	अणु  4, 0x0000 पूर्ण,     /* R4  - Volume Control */
	अणु  5, 0x000A पूर्ण,     /* R5  - Format Control */
	अणु  6, 0x0000 पूर्ण,     /* R6  - Filter Control */
	अणु  7, 0x0000 पूर्ण,     /* R7  - Mode Control 1 */
	अणु  8, 0x0002 पूर्ण,     /* R8  - Mode Control 2 */
	अणु 32, 0x0002 पूर्ण,     /* R32 - ADDITONAL_CONTROL_1 */
पूर्ण;

अटल पूर्णांक wm8741_reset(काष्ठा snd_soc_component *component)
अणु
	वापस snd_soc_component_ग_लिखो(component, WM8741_RESET, 0);
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(dac_tlv_fine, -12700, 13, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(dac_tlv, -12700, 400, 0);

अटल स्थिर काष्ठा snd_kcontrol_new wm8741_snd_controls_stereo[] = अणु
SOC_DOUBLE_R_TLV("Fine Playback Volume", WM8741_DACLLSB_ATTENUATION,
		 WM8741_DACRLSB_ATTENUATION, 1, 255, 1, dac_tlv_fine),
SOC_DOUBLE_R_TLV("Playback Volume", WM8741_DACLMSB_ATTENUATION,
		 WM8741_DACRMSB_ATTENUATION, 0, 511, 1, dac_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8741_snd_controls_mono_left[] = अणु
SOC_SINGLE_TLV("Fine Playback Volume", WM8741_DACLLSB_ATTENUATION,
		 1, 255, 1, dac_tlv_fine),
SOC_SINGLE_TLV("Playback Volume", WM8741_DACLMSB_ATTENUATION,
		 0, 511, 1, dac_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8741_snd_controls_mono_right[] = अणु
SOC_SINGLE_TLV("Fine Playback Volume", WM8741_DACRLSB_ATTENUATION,
		1, 255, 1, dac_tlv_fine),
SOC_SINGLE_TLV("Playback Volume", WM8741_DACRMSB_ATTENUATION,
		0, 511, 1, dac_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8741_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_DAC("DACL", "Playback", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_DAC("DACR", "Playback", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_OUTPUT("VOUTLP"),
SND_SOC_DAPM_OUTPUT("VOUTLN"),
SND_SOC_DAPM_OUTPUT("VOUTRP"),
SND_SOC_DAPM_OUTPUT("VOUTRN"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8741_dapm_routes[] = अणु
	अणु "VOUTLP", शून्य, "DACL" पूर्ण,
	अणु "VOUTLN", शून्य, "DACL" पूर्ण,
	अणु "VOUTRP", शून्य, "DACR" पूर्ण,
	अणु "VOUTRN", शून्य, "DACR" पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rates_11289[] = अणु
	44100, 88200,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_11289 = अणु
	.count	= ARRAY_SIZE(rates_11289),
	.list	= rates_11289,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rates_12288[] = अणु
	32000, 48000, 96000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_12288 = अणु
	.count	= ARRAY_SIZE(rates_12288),
	.list	= rates_12288,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rates_16384[] = अणु
	32000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_16384 = अणु
	.count	= ARRAY_SIZE(rates_16384),
	.list	= rates_16384,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rates_16934[] = अणु
	44100, 88200,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_16934 = अणु
	.count	= ARRAY_SIZE(rates_16934),
	.list	= rates_16934,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rates_18432[] = अणु
	48000, 96000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_18432 = अणु
	.count	= ARRAY_SIZE(rates_18432),
	.list	= rates_18432,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rates_22579[] = अणु
	44100, 88200, 176400
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_22579 = अणु
	.count	= ARRAY_SIZE(rates_22579),
	.list	= rates_22579,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rates_24576[] = अणु
	32000, 48000, 96000, 192000
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_24576 = अणु
	.count	= ARRAY_SIZE(rates_24576),
	.list	= rates_24576,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rates_36864[] = अणु
	48000, 96000, 192000
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_36864 = अणु
	.count	= ARRAY_SIZE(rates_36864),
	.list	= rates_36864,
पूर्ण;

अटल पूर्णांक wm8741_startup(काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8741_priv *wm8741 = snd_soc_component_get_drvdata(component);

	अगर (wm8741->sysclk)
		snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				SNDRV_PCM_HW_PARAM_RATE,
				wm8741->sysclk_स्थिरraपूर्णांकs);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8741_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8741_priv *wm8741 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक अगरace, mode;
	पूर्णांक i;

	/* The set of sample rates that can be supported depends on the
	 * MCLK supplied to the CODEC - enक्रमce this.
	 */
	अगर (!wm8741->sysclk) अणु
		dev_err(component->dev,
			"No MCLK configured, call set_sysclk() on init or in hw_params\n");
		वापस -EINVAL;
	पूर्ण

	/* Find a supported LRCLK rate */
	क्रम (i = 0; i < wm8741->sysclk_स्थिरraपूर्णांकs->count; i++) अणु
		अगर (wm8741->sysclk_स्थिरraपूर्णांकs->list[i] == params_rate(params))
			अवरोध;
	पूर्ण

	अगर (i == wm8741->sysclk_स्थिरraपूर्णांकs->count) अणु
		dev_err(component->dev, "LRCLK %d unsupported with MCLK %d\n",
			params_rate(params), wm8741->sysclk);
		वापस -EINVAL;
	पूर्ण

	/* bit size */
	चयन (params_width(params)) अणु
	हाल 16:
		अगरace = 0x0;
		अवरोध;
	हाल 20:
		अगरace = 0x1;
		अवरोध;
	हाल 24:
		अगरace = 0x2;
		अवरोध;
	हाल 32:
		अगरace = 0x3;
		अवरोध;
	शेष:
		dev_dbg(component->dev, "wm8741_hw_params:    Unsupported bit size param = %d",
			params_width(params));
		वापस -EINVAL;
	पूर्ण

	/* oversampling rate */
	अगर (params_rate(params) > 96000)
		mode = 0x40;
	अन्यथा अगर (params_rate(params) > 48000)
		mode = 0x20;
	अन्यथा
		mode = 0x00;

	dev_dbg(component->dev, "wm8741_hw_params:    bit size param = %d, rate param = %d",
		params_width(params), params_rate(params));

	snd_soc_component_update_bits(component, WM8741_FORMAT_CONTROL, WM8741_IWL_MASK,
			    अगरace);
	snd_soc_component_update_bits(component, WM8741_MODE_CONTROL_1, WM8741_OSR_MASK,
			    mode);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8741_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8741_priv *wm8741 = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "wm8741_set_dai_sysclk info: freq=%dHz\n", freq);

	चयन (freq) अणु
	हाल 0:
		wm8741->sysclk_स्थिरraपूर्णांकs = शून्य;
		अवरोध;
	हाल 11289600:
		wm8741->sysclk_स्थिरraपूर्णांकs = &स्थिरraपूर्णांकs_11289;
		अवरोध;
	हाल 12288000:
		wm8741->sysclk_स्थिरraपूर्णांकs = &स्थिरraपूर्णांकs_12288;
		अवरोध;
	हाल 16384000:
		wm8741->sysclk_स्थिरraपूर्णांकs = &स्थिरraपूर्णांकs_16384;
		अवरोध;
	हाल 16934400:
		wm8741->sysclk_स्थिरraपूर्णांकs = &स्थिरraपूर्णांकs_16934;
		अवरोध;
	हाल 18432000:
		wm8741->sysclk_स्थिरraपूर्णांकs = &स्थिरraपूर्णांकs_18432;
		अवरोध;
	हाल 22579200:
	हाल 33868800:
		wm8741->sysclk_स्थिरraपूर्णांकs = &स्थिरraपूर्णांकs_22579;
		अवरोध;
	हाल 24576000:
		wm8741->sysclk_स्थिरraपूर्णांकs = &स्थिरraपूर्णांकs_24576;
		अवरोध;
	हाल 36864000:
		wm8741->sysclk_स्थिरraपूर्णांकs = &स्थिरraपूर्णांकs_36864;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	wm8741->sysclk = freq;
	वापस 0;
पूर्ण

अटल पूर्णांक wm8741_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	अचिन्हित पूर्णांक अगरace;

	/* check master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरace = 0x08;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अगरace = 0x00;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरace = 0x04;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		अगरace = 0x0C;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		अगरace = 0x1C;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		अगरace |= 0x10;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अगरace |= 0x20;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		अगरace |= 0x30;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण


	dev_dbg(component->dev, "wm8741_set_dai_fmt:    Format=%x, Clock Inv=%x\n",
				fmt & SND_SOC_DAIFMT_FORMAT_MASK,
				((fmt & SND_SOC_DAIFMT_INV_MASK)));

	snd_soc_component_update_bits(component, WM8741_FORMAT_CONTROL,
			    WM8741_BCP_MASK | WM8741_LRP_MASK | WM8741_FMT_MASK,
			    अगरace);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8741_mute(काष्ठा snd_soc_dai *codec_dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;

	snd_soc_component_update_bits(component, WM8741_VOLUME_CONTROL,
			WM8741_SOFT_MASK, !!mute << WM8741_SOFT_SHIFT);
	वापस 0;
पूर्ण

#घोषणा WM8741_RATES (SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 | \
			SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_88200 | \
			SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_176400 | \
			SNDRV_PCM_RATE_192000)

#घोषणा WM8741_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8741_dai_ops = अणु
	.startup	= wm8741_startup,
	.hw_params	= wm8741_hw_params,
	.set_sysclk	= wm8741_set_dai_sysclk,
	.set_fmt	= wm8741_set_dai_fmt,
	.mute_stream	= wm8741_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8741_dai = अणु
	.name = "wm8741",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = WM8741_RATES,
		.क्रमmats = WM8741_FORMATS,
	पूर्ण,
	.ops = &wm8741_dai_ops,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक wm8741_resume(काष्ठा snd_soc_component *component)
अणु
	snd_soc_component_cache_sync(component);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा wm8741_resume शून्य
#पूर्ण_अगर

अटल पूर्णांक wm8741_configure(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8741_priv *wm8741 = snd_soc_component_get_drvdata(component);

	/* Configure dअगरferential mode */
	चयन (wm8741->pdata.dअगरf_mode) अणु
	हाल WM8741_DIFF_MODE_STEREO:
	हाल WM8741_DIFF_MODE_STEREO_REVERSED:
	हाल WM8741_DIFF_MODE_MONO_LEFT:
	हाल WM8741_DIFF_MODE_MONO_RIGHT:
		snd_soc_component_update_bits(component, WM8741_MODE_CONTROL_2,
				WM8741_DIFF_MASK,
				wm8741->pdata.dअगरf_mode << WM8741_DIFF_SHIFT);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Change some शेष settings - latch VU */
	snd_soc_component_update_bits(component, WM8741_DACLLSB_ATTENUATION,
			WM8741_UPDATELL, WM8741_UPDATELL);
	snd_soc_component_update_bits(component, WM8741_DACLMSB_ATTENUATION,
			WM8741_UPDATELM, WM8741_UPDATELM);
	snd_soc_component_update_bits(component, WM8741_DACRLSB_ATTENUATION,
			WM8741_UPDATERL, WM8741_UPDATERL);
	snd_soc_component_update_bits(component, WM8741_DACRMSB_ATTENUATION,
			WM8741_UPDATERM, WM8741_UPDATERM);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8741_add_controls(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8741_priv *wm8741 = snd_soc_component_get_drvdata(component);

	चयन (wm8741->pdata.dअगरf_mode) अणु
	हाल WM8741_DIFF_MODE_STEREO:
	हाल WM8741_DIFF_MODE_STEREO_REVERSED:
		snd_soc_add_component_controls(component,
				wm8741_snd_controls_stereo,
				ARRAY_SIZE(wm8741_snd_controls_stereo));
		अवरोध;
	हाल WM8741_DIFF_MODE_MONO_LEFT:
		snd_soc_add_component_controls(component,
				wm8741_snd_controls_mono_left,
				ARRAY_SIZE(wm8741_snd_controls_mono_left));
		अवरोध;
	हाल WM8741_DIFF_MODE_MONO_RIGHT:
		snd_soc_add_component_controls(component,
				wm8741_snd_controls_mono_right,
				ARRAY_SIZE(wm8741_snd_controls_mono_right));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8741_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8741_priv *wm8741 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8741->supplies),
				    wm8741->supplies);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to enable supplies: %d\n", ret);
		जाओ err_get;
	पूर्ण

	ret = wm8741_reset(component);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to issue reset\n");
		जाओ err_enable;
	पूर्ण

	ret = wm8741_configure(component);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to change default settings\n");
		जाओ err_enable;
	पूर्ण

	ret = wm8741_add_controls(component);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to add controls\n");
		जाओ err_enable;
	पूर्ण

	dev_dbg(component->dev, "Successful registration\n");
	वापस ret;

err_enable:
	regulator_bulk_disable(ARRAY_SIZE(wm8741->supplies), wm8741->supplies);
err_get:
	वापस ret;
पूर्ण

अटल व्योम wm8741_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8741_priv *wm8741 = snd_soc_component_get_drvdata(component);

	regulator_bulk_disable(ARRAY_SIZE(wm8741->supplies), wm8741->supplies);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8741 = अणु
	.probe			= wm8741_probe,
	.हटाओ			= wm8741_हटाओ,
	.resume			= wm8741_resume,
	.dapm_widमाला_लो		= wm8741_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8741_dapm_widमाला_लो),
	.dapm_routes		= wm8741_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8741_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id wm8741_of_match[] = अणु
	अणु .compatible = "wlf,wm8741", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wm8741_of_match);

अटल स्थिर काष्ठा regmap_config wm8741_regmap = अणु
	.reg_bits = 7,
	.val_bits = 9,
	.max_रेजिस्टर = WM8741_MAX_REGISTER,

	.reg_शेषs = wm8741_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8741_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक wm8741_set_pdata(काष्ठा device *dev, काष्ठा wm8741_priv *wm8741)
अणु
	स्थिर काष्ठा wm8741_platक्रमm_data *pdata = dev_get_platdata(dev);
	u32 dअगरf_mode;

	अगर (dev->of_node) अणु
		अगर (of_property_पढ़ो_u32(dev->of_node, "diff-mode", &dअगरf_mode)
				>= 0)
			wm8741->pdata.dअगरf_mode = dअगरf_mode;
	पूर्ण अन्यथा अणु
		अगर (pdata != शून्य)
			स_नकल(&wm8741->pdata, pdata, माप(wm8741->pdata));
	पूर्ण

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_I2C)
अटल पूर्णांक wm8741_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8741_priv *wm8741;
	पूर्णांक ret, i;

	wm8741 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8741_priv),
			      GFP_KERNEL);
	अगर (wm8741 == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(wm8741->supplies); i++)
		wm8741->supplies[i].supply = wm8741_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev, ARRAY_SIZE(wm8741->supplies),
				      wm8741->supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	wm8741->regmap = devm_regmap_init_i2c(i2c, &wm8741_regmap);
	अगर (IS_ERR(wm8741->regmap)) अणु
		ret = PTR_ERR(wm8741->regmap);
		dev_err(&i2c->dev, "Failed to init regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = wm8741_set_pdata(&i2c->dev, wm8741);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to set pdata: %d\n", ret);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(i2c, wm8741);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				     &soc_component_dev_wm8741, &wm8741_dai, 1);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8741_i2c_id[] = अणु
	अणु "wm8741", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8741_i2c_id);

अटल काष्ठा i2c_driver wm8741_i2c_driver = अणु
	.driver = अणु
		.name = "wm8741",
		.of_match_table = wm8741_of_match,
	पूर्ण,
	.probe =    wm8741_i2c_probe,
	.id_table = wm8741_i2c_id,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_SPI_MASTER)
अटल पूर्णांक wm8741_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा wm8741_priv *wm8741;
	पूर्णांक ret, i;

	wm8741 = devm_kzalloc(&spi->dev, माप(काष्ठा wm8741_priv),
			     GFP_KERNEL);
	अगर (wm8741 == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(wm8741->supplies); i++)
		wm8741->supplies[i].supply = wm8741_supply_names[i];

	ret = devm_regulator_bulk_get(&spi->dev, ARRAY_SIZE(wm8741->supplies),
				      wm8741->supplies);
	अगर (ret != 0) अणु
		dev_err(&spi->dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	wm8741->regmap = devm_regmap_init_spi(spi, &wm8741_regmap);
	अगर (IS_ERR(wm8741->regmap)) अणु
		ret = PTR_ERR(wm8741->regmap);
		dev_err(&spi->dev, "Failed to init regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = wm8741_set_pdata(&spi->dev, wm8741);
	अगर (ret != 0) अणु
		dev_err(&spi->dev, "Failed to set pdata: %d\n", ret);
		वापस ret;
	पूर्ण

	spi_set_drvdata(spi, wm8741);

	ret = devm_snd_soc_रेजिस्टर_component(&spi->dev,
			&soc_component_dev_wm8741, &wm8741_dai, 1);
	वापस ret;
पूर्ण

अटल काष्ठा spi_driver wm8741_spi_driver = अणु
	.driver = अणु
		.name	= "wm8741",
		.of_match_table = wm8741_of_match,
	पूर्ण,
	.probe		= wm8741_spi_probe,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SPI_MASTER */

अटल पूर्णांक __init wm8741_modinit(व्योम)
अणु
	पूर्णांक ret = 0;

#अगर IS_ENABLED(CONFIG_I2C)
	ret = i2c_add_driver(&wm8741_i2c_driver);
	अगर (ret != 0)
		pr_err("Failed to register WM8741 I2C driver: %d\n", ret);
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	ret = spi_रेजिस्टर_driver(&wm8741_spi_driver);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register wm8741 SPI driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर

	वापस ret;
पूर्ण
module_init(wm8741_modinit);

अटल व्योम __निकास wm8741_निकास(व्योम)
अणु
#अगर defined(CONFIG_SPI_MASTER)
	spi_unरेजिस्टर_driver(&wm8741_spi_driver);
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_I2C)
	i2c_del_driver(&wm8741_i2c_driver);
#पूर्ण_अगर
पूर्ण
module_निकास(wm8741_निकास);

MODULE_DESCRIPTION("ASoC WM8741 driver");
MODULE_AUTHOR("Ian Lartey <ian@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
