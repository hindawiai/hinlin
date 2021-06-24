<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * uda134x.c  --  UDA134X ALSA SoC Codec driver
 *
 * Modअगरications by Christian Pellegrin <chripell@evolware.org>
 *
 * Copyright 2007 Dension Audio Systems Ltd.
 * Author: Zoltan Devai
 *
 * Based on the WM87xx drivers by Liam Girdwood and Riअक्षरd Purdie
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>

#समावेश <sound/uda134x.h>
#समावेश <sound/l3.h>

#समावेश "uda134x.h"


#घोषणा UDA134X_RATES SNDRV_PCM_RATE_8000_48000
#घोषणा UDA134X_FORMATS (SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_S16_LE | \
		SNDRV_PCM_FMTBIT_S18_3LE | SNDRV_PCM_FMTBIT_S20_3LE)

काष्ठा uda134x_priv अणु
	पूर्णांक sysclk;
	पूर्णांक dai_fmt;

	काष्ठा snd_pcm_substream *master_substream;
	काष्ठा snd_pcm_substream *slave_substream;

	काष्ठा regmap *regmap;
	काष्ठा uda134x_platक्रमm_data *pd;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष uda134x_reg_शेषs[] = अणु
	अणु UDA134X_EA000, 0x04 पूर्ण,
	अणु UDA134X_EA001, 0x04 पूर्ण,
	अणु UDA134X_EA010, 0x04 पूर्ण,
	अणु UDA134X_EA011, 0x00 पूर्ण,
	अणु UDA134X_EA100, 0x00 पूर्ण,
	अणु UDA134X_EA101, 0x00 पूर्ण,
	अणु UDA134X_EA110, 0x00 पूर्ण,
	अणु UDA134X_EA111, 0x00 पूर्ण,
	अणु UDA134X_STATUS0, 0x00 पूर्ण,
	अणु UDA134X_STATUS1, 0x03 पूर्ण,
	अणु UDA134X_DATA000, 0x00 पूर्ण,
	अणु UDA134X_DATA001, 0x00 पूर्ण,
	अणु UDA134X_DATA010, 0x00 पूर्ण,
	अणु UDA134X_DATA011, 0x00 पूर्ण,
	अणु UDA134X_DATA1, 0x00 पूर्ण,
पूर्ण;

/*
 * Write to the uda134x रेजिस्टरs
 *
 */
अटल पूर्णांक uda134x_regmap_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक value)
अणु
	काष्ठा uda134x_platक्रमm_data *pd = context;
	पूर्णांक ret;
	u8 addr;
	u8 data = value;

	चयन (reg) अणु
	हाल UDA134X_STATUS0:
	हाल UDA134X_STATUS1:
		addr = UDA134X_STATUS_ADDR;
		data |= (reg - UDA134X_STATUS0) << 7;
		अवरोध;
	हाल UDA134X_DATA000:
	हाल UDA134X_DATA001:
	हाल UDA134X_DATA010:
	हाल UDA134X_DATA011:
		addr = UDA134X_DATA0_ADDR;
		data |= (reg - UDA134X_DATA000) << 6;
		अवरोध;
	हाल UDA134X_DATA1:
		addr = UDA134X_DATA1_ADDR;
		अवरोध;
	शेष:
		/* It's an extended address रेजिस्टर */
		addr =  (reg | UDA134X_EXTADDR_PREFIX);

		ret = l3_ग_लिखो(&pd->l3,
			       UDA134X_DATA0_ADDR, &addr, 1);
		अगर (ret != 1)
			वापस -EIO;

		addr = UDA134X_DATA0_ADDR;
		data = (value | UDA134X_EXTDATA_PREFIX);
		अवरोध;
	पूर्ण

	ret = l3_ग_लिखो(&pd->l3,
		       addr, &data, 1);
	अगर (ret != 1)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम uda134x_reset(काष्ठा snd_soc_component *component)
अणु
	काष्ठा uda134x_priv *uda134x = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक mask = 1<<6;

	regmap_update_bits(uda134x->regmap, UDA134X_STATUS0, mask, mask);
	msleep(1);
	regmap_update_bits(uda134x->regmap, UDA134X_STATUS0, mask, 0);
पूर्ण

अटल पूर्णांक uda134x_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा uda134x_priv *uda134x = snd_soc_component_get_drvdata(dai->component);
	अचिन्हित पूर्णांक mask = 1<<2;
	अचिन्हित पूर्णांक val;

	pr_debug("%s mute: %d\n", __func__, mute);

	अगर (mute)
		val = mask;
	अन्यथा
		val = 0;

	वापस regmap_update_bits(uda134x->regmap, UDA134X_DATA010, mask, val);
पूर्ण

अटल पूर्णांक uda134x_startup(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा uda134x_priv *uda134x = snd_soc_component_get_drvdata(component);
	काष्ठा snd_pcm_runसमय *master_runसमय;

	अगर (uda134x->master_substream) अणु
		master_runसमय = uda134x->master_substream->runसमय;

		pr_debug("%s constraining to %d bits at %d\n", __func__,
			 master_runसमय->sample_bits,
			 master_runसमय->rate);

		snd_pcm_hw_स्थिरraपूर्णांक_single(substream->runसमय,
					     SNDRV_PCM_HW_PARAM_RATE,
					     master_runसमय->rate);

		snd_pcm_hw_स्थिरraपूर्णांक_single(substream->runसमय,
					     SNDRV_PCM_HW_PARAM_SAMPLE_BITS,
					     master_runसमय->sample_bits);

		uda134x->slave_substream = substream;
	पूर्ण अन्यथा
		uda134x->master_substream = substream;

	वापस 0;
पूर्ण

अटल व्योम uda134x_shutकरोwn(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा uda134x_priv *uda134x = snd_soc_component_get_drvdata(component);

	अगर (uda134x->master_substream == substream)
		uda134x->master_substream = uda134x->slave_substream;

	uda134x->slave_substream = शून्य;
पूर्ण

अटल पूर्णांक uda134x_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा uda134x_priv *uda134x = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक hw_params = 0;

	अगर (substream == uda134x->slave_substream) अणु
		pr_debug("%s ignoring hw_params for slave substream\n",
			 __func__);
		वापस 0;
	पूर्ण

	pr_debug("%s sysclk: %d, rate:%d\n", __func__,
		 uda134x->sysclk, params_rate(params));

	/* set SYSCLK / fs ratio */
	चयन (uda134x->sysclk / params_rate(params)) अणु
	हाल 512:
		अवरोध;
	हाल 384:
		hw_params |= (1<<4);
		अवरोध;
	हाल 256:
		hw_params |= (1<<5);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "%s unsupported fs\n", __func__);
		वापस -EINVAL;
	पूर्ण

	pr_debug("%s dai_fmt: %d, params_format:%d\n", __func__,
		 uda134x->dai_fmt, params_क्रमmat(params));

	/* set DAI क्रमmat and word length */
	चयन (uda134x->dai_fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		चयन (params_width(params)) अणु
		हाल 16:
			hw_params |= (1<<1);
			अवरोध;
		हाल 18:
			hw_params |= (1<<2);
			अवरोध;
		हाल 20:
			hw_params |= ((1<<2) | (1<<1));
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_ERR "%s unsupported format (right)\n",
			       __func__);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		hw_params |= (1<<3);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "%s unsupported format\n", __func__);
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(uda134x->regmap, UDA134X_STATUS0,
		STATUS0_SYSCLK_MASK | STATUS0_DAIFMT_MASK, hw_params);
पूर्ण

अटल पूर्णांक uda134x_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				  पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा uda134x_priv *uda134x = snd_soc_component_get_drvdata(component);

	pr_debug("%s clk_id: %d, freq: %u, dir: %d\n", __func__,
		 clk_id, freq, dir);

	/* Anything between 256fs*8Khz and 512fs*48Khz should be acceptable
	   because the codec is slave. Of course limitations of the घड़ी
	   master (the IIS controller) apply.
	   We'll error out on set_hw_params if it's not OK */
	अगर ((freq >= (256 * 8000)) && (freq <= (512 * 48000))) अणु
		uda134x->sysclk = freq;
		वापस 0;
	पूर्ण

	prपूर्णांकk(KERN_ERR "%s unsupported sysclk\n", __func__);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक uda134x_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
			       अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा uda134x_priv *uda134x = snd_soc_component_get_drvdata(component);

	pr_debug("%s fmt: %08X\n", __func__, fmt);

	/* codec supports only full slave mode */
	अगर ((fmt & SND_SOC_DAIFMT_MASTER_MASK) != SND_SOC_DAIFMT_CBS_CFS) अणु
		prपूर्णांकk(KERN_ERR "%s unsupported slave mode\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* no support क्रम घड़ी inversion */
	अगर ((fmt & SND_SOC_DAIFMT_INV_MASK) != SND_SOC_DAIFMT_NB_NF) अणु
		prपूर्णांकk(KERN_ERR "%s unsupported clock inversion\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* We can't setup DAI क्रमmat here as it depends on the word bit num */
	/* so let's just store the value क्रम later */
	uda134x->dai_fmt = fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक uda134x_set_bias_level(काष्ठा snd_soc_component *component,
				  क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा uda134x_priv *uda134x = snd_soc_component_get_drvdata(component);
	काष्ठा uda134x_platक्रमm_data *pd = uda134x->pd;
	pr_debug("%s bias level %d\n", __func__, level);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		/* घातer on */
		अगर (pd->घातer) अणु
			pd->घातer(1);
			regcache_sync(uda134x->regmap);
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		/* घातer off */
		अगर (pd->घातer) अणु
			pd->घातer(0);
			regcache_mark_dirty(uda134x->regmap);
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *uda134x_dsp_setting[] = अणु"Flat", "Minimum1",
					    "Minimum2", "Maximum"पूर्ण;
अटल स्थिर अक्षर *uda134x_deemph[] = अणु"None", "32Khz", "44.1Khz", "48Khz"पूर्ण;
अटल स्थिर अक्षर *uda134x_mixmode[] = अणु"Differential", "Analog1",
					"Analog2", "Both"पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत uda134x_mixer_क्रमागत[] = अणु
SOC_ENUM_SINGLE(UDA134X_DATA010, 0, 0x04, uda134x_dsp_setting),
SOC_ENUM_SINGLE(UDA134X_DATA010, 3, 0x04, uda134x_deemph),
SOC_ENUM_SINGLE(UDA134X_EA010, 0, 0x04, uda134x_mixmode),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new uda1341_snd_controls[] = अणु
SOC_SINGLE("Master Playback Volume", UDA134X_DATA000, 0, 0x3F, 1),
SOC_SINGLE("Capture Volume", UDA134X_EA010, 2, 0x07, 0),
SOC_SINGLE("Analog1 Volume", UDA134X_EA000, 0, 0x1F, 1),
SOC_SINGLE("Analog2 Volume", UDA134X_EA001, 0, 0x1F, 1),

SOC_SINGLE("Mic Sensitivity", UDA134X_EA010, 2, 7, 0),
SOC_SINGLE("Mic Volume", UDA134X_EA101, 0, 0x1F, 0),

SOC_SINGLE("Tone Control - Bass", UDA134X_DATA001, 2, 0xF, 0),
SOC_SINGLE("Tone Control - Treble", UDA134X_DATA001, 0, 3, 0),

SOC_ENUM("Sound Processing Filter", uda134x_mixer_क्रमागत[0]),
SOC_ENUM("PCM Playback De-emphasis", uda134x_mixer_क्रमागत[1]),
SOC_ENUM("Input Mux", uda134x_mixer_क्रमागत[2]),

SOC_SINGLE("AGC Switch", UDA134X_EA100, 4, 1, 0),
SOC_SINGLE("AGC Target Volume", UDA134X_EA110, 0, 0x03, 1),
SOC_SINGLE("AGC Timing", UDA134X_EA110, 2, 0x07, 0),

SOC_SINGLE("DAC +6dB Switch", UDA134X_STATUS1, 6, 1, 0),
SOC_SINGLE("ADC +6dB Switch", UDA134X_STATUS1, 5, 1, 0),
SOC_SINGLE("ADC Polarity Switch", UDA134X_STATUS1, 4, 1, 0),
SOC_SINGLE("DAC Polarity Switch", UDA134X_STATUS1, 3, 1, 0),
SOC_SINGLE("Double Speed Playback Switch", UDA134X_STATUS1, 2, 1, 0),
SOC_SINGLE("DC Filter Enable Switch", UDA134X_STATUS0, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new uda1340_snd_controls[] = अणु
SOC_SINGLE("Master Playback Volume", UDA134X_DATA000, 0, 0x3F, 1),

SOC_SINGLE("Tone Control - Bass", UDA134X_DATA001, 2, 0xF, 0),
SOC_SINGLE("Tone Control - Treble", UDA134X_DATA001, 0, 3, 0),

SOC_ENUM("Sound Processing Filter", uda134x_mixer_क्रमागत[0]),
SOC_ENUM("PCM Playback De-emphasis", uda134x_mixer_क्रमागत[1]),

SOC_SINGLE("DC Filter Enable Switch", UDA134X_STATUS0, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new uda1345_snd_controls[] = अणु
SOC_SINGLE("Master Playback Volume", UDA134X_DATA000, 0, 0x3F, 1),

SOC_ENUM("PCM Playback De-emphasis", uda134x_mixer_क्रमागत[1]),

SOC_SINGLE("DC Filter Enable Switch", UDA134X_STATUS0, 0, 1, 0),
पूर्ण;

/* UDA1341 has the DAC/ADC घातer करोwn in STATUS1 */
अटल स्थिर काष्ठा snd_soc_dapm_widget uda1341_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("DAC", "Playback", UDA134X_STATUS1, 0, 0),
	SND_SOC_DAPM_ADC("ADC", "Capture", UDA134X_STATUS1, 1, 0),
पूर्ण;

/* UDA1340/4/5 has the DAC/ADC pwoer करोwn in DATA0 11 */
अटल स्थिर काष्ठा snd_soc_dapm_widget uda1340_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("DAC", "Playback", UDA134X_DATA011, 0, 0),
	SND_SOC_DAPM_ADC("ADC", "Capture", UDA134X_DATA011, 1, 0),
पूर्ण;

/* Common DAPM widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget uda134x_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("VINL1"),
	SND_SOC_DAPM_INPUT("VINR1"),
	SND_SOC_DAPM_INPUT("VINL2"),
	SND_SOC_DAPM_INPUT("VINR2"),
	SND_SOC_DAPM_OUTPUT("VOUTL"),
	SND_SOC_DAPM_OUTPUT("VOUTR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route uda134x_dapm_routes[] = अणु
	अणु "ADC", शून्य, "VINL1" पूर्ण,
	अणु "ADC", शून्य, "VINR1" पूर्ण,
	अणु "ADC", शून्य, "VINL2" पूर्ण,
	अणु "ADC", शून्य, "VINR2" पूर्ण,
	अणु "VOUTL", शून्य, "DAC" पूर्ण,
	अणु "VOUTR", शून्य, "DAC" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops uda134x_dai_ops = अणु
	.startup	= uda134x_startup,
	.shutकरोwn	= uda134x_shutकरोwn,
	.hw_params	= uda134x_hw_params,
	.mute_stream	= uda134x_mute,
	.set_sysclk	= uda134x_set_dai_sysclk,
	.set_fmt	= uda134x_set_dai_fmt,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver uda134x_dai = अणु
	.name = "uda134x-hifi",
	/* playback capabilities */
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = UDA134X_RATES,
		.क्रमmats = UDA134X_FORMATS,
	पूर्ण,
	/* capture capabilities */
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = UDA134X_RATES,
		.क्रमmats = UDA134X_FORMATS,
	पूर्ण,
	/* pcm operations */
	.ops = &uda134x_dai_ops,
पूर्ण;

अटल पूर्णांक uda134x_soc_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा uda134x_priv *uda134x = snd_soc_component_get_drvdata(component);
	काष्ठा uda134x_platक्रमm_data *pd = uda134x->pd;
	स्थिर काष्ठा snd_soc_dapm_widget *widमाला_लो;
	अचिन्हित num_widमाला_लो;
	पूर्णांक ret;

	prपूर्णांकk(KERN_INFO "UDA134X SoC Audio Codec\n");

	चयन (pd->model) अणु
	हाल UDA134X_UDA1340:
	हाल UDA134X_UDA1341:
	हाल UDA134X_UDA1344:
	हाल UDA134X_UDA1345:
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "UDA134X SoC codec: "
		       "unsupported model %d\n",
			pd->model);
		वापस -EINVAL;
	पूर्ण

	अगर (pd->घातer)
		pd->घातer(1);

	uda134x_reset(component);

	अगर (pd->model == UDA134X_UDA1341) अणु
		widमाला_लो = uda1341_dapm_widमाला_लो;
		num_widमाला_लो = ARRAY_SIZE(uda1341_dapm_widमाला_लो);
	पूर्ण अन्यथा अणु
		widमाला_लो = uda1340_dapm_widमाला_लो;
		num_widमाला_लो = ARRAY_SIZE(uda1340_dapm_widमाला_लो);
	पूर्ण

	ret = snd_soc_dapm_new_controls(dapm, widमाला_लो, num_widमाला_लो);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s failed to register dapm controls: %d",
			__func__, ret);
		वापस ret;
	पूर्ण

	चयन (pd->model) अणु
	हाल UDA134X_UDA1340:
	हाल UDA134X_UDA1344:
		ret = snd_soc_add_component_controls(component, uda1340_snd_controls,
					ARRAY_SIZE(uda1340_snd_controls));
	अवरोध;
	हाल UDA134X_UDA1341:
		ret = snd_soc_add_component_controls(component, uda1341_snd_controls,
					ARRAY_SIZE(uda1341_snd_controls));
	अवरोध;
	हाल UDA134X_UDA1345:
		ret = snd_soc_add_component_controls(component, uda1345_snd_controls,
					ARRAY_SIZE(uda1345_snd_controls));
	अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "%s unknown codec type: %d",
			__func__, pd->model);
		वापस -EINVAL;
	पूर्ण

	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "UDA134X: failed to register controls\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_uda134x = अणु
	.probe			= uda134x_soc_probe,
	.set_bias_level		= uda134x_set_bias_level,
	.dapm_widमाला_लो		= uda134x_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(uda134x_dapm_widमाला_लो),
	.dapm_routes		= uda134x_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(uda134x_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config uda134x_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = UDA134X_DATA1,
	.reg_शेषs = uda134x_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(uda134x_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,

	.reg_ग_लिखो = uda134x_regmap_ग_लिखो,
पूर्ण;

अटल पूर्णांक uda134x_codec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uda134x_platक्रमm_data *pd = pdev->dev.platक्रमm_data;
	काष्ठा uda134x_priv *uda134x;
	पूर्णांक ret;

	अगर (!pd) अणु
		dev_err(&pdev->dev, "Missing L3 bitbang function\n");
		वापस -ENODEV;
	पूर्ण

	uda134x = devm_kzalloc(&pdev->dev, माप(*uda134x), GFP_KERNEL);
	अगर (!uda134x)
		वापस -ENOMEM;

	uda134x->pd = pd;
	platक्रमm_set_drvdata(pdev, uda134x);

	अगर (pd->l3.use_gpios) अणु
		ret = l3_set_gpio_ops(&pdev->dev, &uda134x->pd->l3);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	uda134x->regmap = devm_regmap_init(&pdev->dev, शून्य, pd,
		&uda134x_regmap_config);
	अगर (IS_ERR(uda134x->regmap))
		वापस PTR_ERR(uda134x->regmap);

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_component_dev_uda134x, &uda134x_dai, 1);
पूर्ण

अटल काष्ठा platक्रमm_driver uda134x_codec_driver = अणु
	.driver = अणु
		.name = "uda134x-codec",
	पूर्ण,
	.probe = uda134x_codec_probe,
पूर्ण;

module_platक्रमm_driver(uda134x_codec_driver);

MODULE_DESCRIPTION("UDA134X ALSA soc codec driver");
MODULE_AUTHOR("Zoltan Devai, Christian Pellegrin <chripell@evolware.org>");
MODULE_LICENSE("GPL");
