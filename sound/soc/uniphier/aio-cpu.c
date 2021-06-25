<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Socionext UniPhier AIO ALSA CPU DAI driver.
//
// Copyright (c) 2016-2018 Socionext Inc.

#समावेश <linux/clk.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश "aio.h"

अटल bool is_valid_pll(काष्ठा uniphier_aio_chip *chip, पूर्णांक pll_id)
अणु
	काष्ठा device *dev = &chip->pdev->dev;

	अगर (pll_id < 0 || chip->num_plls <= pll_id) अणु
		dev_err(dev, "PLL(%d) is not supported\n", pll_id);
		वापस false;
	पूर्ण

	वापस chip->plls[pll_id].enable;
पूर्ण

/**
 * find_volume - find volume supported HW port by HW port number
 * @chip: the AIO chip poपूर्णांकer
 * @oport_hw: HW port number, one of AUD_HW_XXXX
 *
 * Find AIO device from device list by HW port number. Volume feature is
 * available only in Output and PCM ports, this limitation comes from HW
 * specअगरications.
 *
 * Return: The poपूर्णांकer of AIO substream अगर successful, otherwise शून्य on error.
 */
अटल काष्ठा uniphier_aio_sub *find_volume(काष्ठा uniphier_aio_chip *chip,
					    पूर्णांक oport_hw)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < chip->num_aios; i++) अणु
		काष्ठा uniphier_aio_sub *sub = &chip->aios[i].sub[0];

		अगर (!sub->swm)
			जारी;

		अगर (sub->swm->oport.hw == oport_hw)
			वापस sub;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool match_spec(स्थिर काष्ठा uniphier_aio_spec *spec,
		       स्थिर अक्षर *name, पूर्णांक dir)
अणु
	अगर (dir == SNDRV_PCM_STREAM_PLAYBACK &&
	    spec->swm.dir != PORT_सूची_OUTPUT) अणु
		वापस false;
	पूर्ण

	अगर (dir == SNDRV_PCM_STREAM_CAPTURE &&
	    spec->swm.dir != PORT_सूची_INPUT) अणु
		वापस false;
	पूर्ण

	अगर (spec->name && म_भेद(spec->name, name) == 0)
		वापस true;

	अगर (spec->gname && म_भेद(spec->gname, name) == 0)
		वापस true;

	वापस false;
पूर्ण

/**
 * find_spec - find HW specअगरication info by name
 * @aio: the AIO device poपूर्णांकer
 * @name: name of device
 * @direction: the direction of substream, SNDRV_PCM_STREAM_*
 *
 * Find hardware specअगरication inक्रमmation from list by device name. This
 * inक्रमmation is used क्रम telling the dअगरference of SoCs to driver.
 *
 * Specअगरication list is array of 'struct uniphier_aio_spec' which is defined
 * in each drivers (see: aio-i2s.c).
 *
 * Return: The poपूर्णांकer of hardware specअगरication of AIO अगर successful,
 * otherwise शून्य on error.
 */
अटल स्थिर काष्ठा uniphier_aio_spec *find_spec(काष्ठा uniphier_aio *aio,
						 स्थिर अक्षर *name,
						 पूर्णांक direction)
अणु
	स्थिर काष्ठा uniphier_aio_chip_spec *chip_spec = aio->chip->chip_spec;
	पूर्णांक i;

	क्रम (i = 0; i < chip_spec->num_specs; i++) अणु
		स्थिर काष्ठा uniphier_aio_spec *spec = &chip_spec->specs[i];

		अगर (match_spec(spec, name, direction))
			वापस spec;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * find_भागider - find घड़ी भागider by frequency
 * @aio: the AIO device poपूर्णांकer
 * @pll_id: PLL ID, should be AUD_PLL_XX
 * @freq: required frequency
 *
 * Find suitable घड़ी भागider by frequency.
 *
 * Return: The ID of PLL अगर successful, otherwise negative error value.
 */
अटल पूर्णांक find_भागider(काष्ठा uniphier_aio *aio, पूर्णांक pll_id, अचिन्हित पूर्णांक freq)
अणु
	काष्ठा uniphier_aio_pll *pll;
	पूर्णांक mul[] = अणु 1, 1, 1, 2, पूर्ण;
	पूर्णांक भाग[] = अणु 2, 3, 1, 3, पूर्ण;
	पूर्णांक i;

	अगर (!is_valid_pll(aio->chip, pll_id))
		वापस -EINVAL;

	pll = &aio->chip->plls[pll_id];
	क्रम (i = 0; i < ARRAY_SIZE(mul); i++)
		अगर (pll->freq * mul[i] / भाग[i] == freq)
			वापस i;

	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक uniphier_aio_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
				   अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा uniphier_aio *aio = uniphier_priv(dai);
	काष्ठा device *dev = &aio->chip->pdev->dev;
	bool pll_स्वतः = false;
	पूर्णांक pll_id, भाग_id;

	चयन (clk_id) अणु
	हाल AUD_CLK_IO:
		वापस -ENOTSUPP;
	हाल AUD_CLK_A1:
		pll_id = AUD_PLL_A1;
		अवरोध;
	हाल AUD_CLK_F1:
		pll_id = AUD_PLL_F1;
		अवरोध;
	हाल AUD_CLK_A2:
		pll_id = AUD_PLL_A2;
		अवरोध;
	हाल AUD_CLK_F2:
		pll_id = AUD_PLL_F2;
		अवरोध;
	हाल AUD_CLK_A:
		pll_id = AUD_PLL_A1;
		pll_स्वतः = true;
		अवरोध;
	हाल AUD_CLK_F:
		pll_id = AUD_PLL_F1;
		pll_स्वतः = true;
		अवरोध;
	हाल AUD_CLK_APLL:
		pll_id = AUD_PLL_APLL;
		अवरोध;
	हाल AUD_CLK_RX0:
		pll_id = AUD_PLL_RX0;
		अवरोध;
	हाल AUD_CLK_USB0:
		pll_id = AUD_PLL_USB0;
		अवरोध;
	हाल AUD_CLK_HSC0:
		pll_id = AUD_PLL_HSC0;
		अवरोध;
	शेष:
		dev_err(dev, "Sysclk(%d) is not supported\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	अगर (pll_स्वतः) अणु
		क्रम (pll_id = 0; pll_id < aio->chip->num_plls; pll_id++) अणु
			भाग_id = find_भागider(aio, pll_id, freq);
			अगर (भाग_id >= 0) अणु
				aio->plद_भाग = भाग_id;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (pll_id == aio->chip->num_plls) अणु
			dev_err(dev, "Sysclk frequency is not supported(%d)\n",
				freq);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (dir == SND_SOC_CLOCK_OUT)
		aio->pll_out = pll_id;
	अन्यथा
		aio->pll_in = pll_id;

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_aio_set_pll(काष्ठा snd_soc_dai *dai, पूर्णांक pll_id,
				पूर्णांक source, अचिन्हित पूर्णांक freq_in,
				अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा uniphier_aio *aio = uniphier_priv(dai);
	पूर्णांक ret;

	अगर (!is_valid_pll(aio->chip, pll_id))
		वापस -EINVAL;

	ret = aio_chip_set_pll(aio->chip, pll_id, freq_out);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_aio_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा uniphier_aio *aio = uniphier_priv(dai);
	काष्ठा device *dev = &aio->chip->pdev->dev;

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_LEFT_J:
	हाल SND_SOC_DAIFMT_RIGHT_J:
	हाल SND_SOC_DAIFMT_I2S:
		aio->fmt = fmt & SND_SOC_DAIFMT_FORMAT_MASK;
		अवरोध;
	शेष:
		dev_err(dev, "Format is not supported(%d)\n",
			fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_aio_startup(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा uniphier_aio *aio = uniphier_priv(dai);
	काष्ठा uniphier_aio_sub *sub = &aio->sub[substream->stream];

	sub->substream = substream;
	sub->pass_through = 0;
	sub->use_mmap = true;

	वापस aio_init(sub);
पूर्ण

अटल व्योम uniphier_aio_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा uniphier_aio *aio = uniphier_priv(dai);
	काष्ठा uniphier_aio_sub *sub = &aio->sub[substream->stream];

	sub->substream = शून्य;
पूर्ण

अटल पूर्णांक uniphier_aio_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा uniphier_aio *aio = uniphier_priv(dai);
	काष्ठा uniphier_aio_sub *sub = &aio->sub[substream->stream];
	काष्ठा device *dev = &aio->chip->pdev->dev;
	पूर्णांक freq, ret;

	चयन (params_rate(params)) अणु
	हाल 48000:
	हाल 32000:
	हाल 24000:
		freq = 12288000;
		अवरोध;
	हाल 44100:
	हाल 22050:
		freq = 11289600;
		अवरोध;
	शेष:
		dev_err(dev, "Rate is not supported(%d)\n",
			params_rate(params));
		वापस -EINVAL;
	पूर्ण
	ret = snd_soc_dai_set_sysclk(dai, AUD_CLK_A,
				     freq, SND_SOC_CLOCK_OUT);
	अगर (ret)
		वापस ret;

	sub->params = *params;
	sub->setting = 1;

	aio_port_reset(sub);
	aio_port_set_volume(sub, sub->vol);
	aio_src_reset(sub);

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_aio_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा uniphier_aio *aio = uniphier_priv(dai);
	काष्ठा uniphier_aio_sub *sub = &aio->sub[substream->stream];

	sub->setting = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_aio_prepare(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा uniphier_aio *aio = uniphier_priv(dai);
	काष्ठा uniphier_aio_sub *sub = &aio->sub[substream->stream];
	पूर्णांक ret;

	ret = aio_port_set_param(sub, sub->pass_through, &sub->params);
	अगर (ret)
		वापस ret;
	ret = aio_src_set_param(sub, &sub->params);
	अगर (ret)
		वापस ret;
	aio_port_set_enable(sub, 1);

	ret = aio_अगर_set_param(sub, sub->pass_through);
	अगर (ret)
		वापस ret;

	अगर (sub->swm->type == PORT_TYPE_CONV) अणु
		ret = aio_srcअगर_set_param(sub);
		अगर (ret)
			वापस ret;
		ret = aio_srcch_set_param(sub);
		अगर (ret)
			वापस ret;
		aio_srcch_set_enable(sub, 1);
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा snd_soc_dai_ops uniphier_aio_i2s_ops = अणु
	.set_sysclk  = uniphier_aio_set_sysclk,
	.set_pll     = uniphier_aio_set_pll,
	.set_fmt     = uniphier_aio_set_fmt,
	.startup     = uniphier_aio_startup,
	.shutकरोwn    = uniphier_aio_shutकरोwn,
	.hw_params   = uniphier_aio_hw_params,
	.hw_मुक्त     = uniphier_aio_hw_मुक्त,
	.prepare     = uniphier_aio_prepare,
पूर्ण;
EXPORT_SYMBOL_GPL(uniphier_aio_i2s_ops);

स्थिर काष्ठा snd_soc_dai_ops uniphier_aio_spdअगर_ops = अणु
	.set_sysclk  = uniphier_aio_set_sysclk,
	.set_pll     = uniphier_aio_set_pll,
	.startup     = uniphier_aio_startup,
	.shutकरोwn    = uniphier_aio_shutकरोwn,
	.hw_params   = uniphier_aio_hw_params,
	.hw_मुक्त     = uniphier_aio_hw_मुक्त,
	.prepare     = uniphier_aio_prepare,
पूर्ण;
EXPORT_SYMBOL_GPL(uniphier_aio_spdअगर_ops);

पूर्णांक uniphier_aio_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा uniphier_aio *aio = uniphier_priv(dai);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(aio->sub); i++) अणु
		काष्ठा uniphier_aio_sub *sub = &aio->sub[i];
		स्थिर काष्ठा uniphier_aio_spec *spec;

		spec = find_spec(aio, dai->name, i);
		अगर (!spec)
			जारी;

		sub->swm = &spec->swm;
		sub->spec = spec;

		sub->vol = AUD_VOL_INIT;
	पूर्ण

	aio_iecout_set_enable(aio->chip, true);
	aio_chip_init(aio->chip);
	aio->chip->active = 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(uniphier_aio_dai_probe);

पूर्णांक uniphier_aio_dai_हटाओ(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा uniphier_aio *aio = uniphier_priv(dai);

	aio->chip->active = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(uniphier_aio_dai_हटाओ);

अटल व्योम uniphier_aio_dai_suspend(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा uniphier_aio *aio = uniphier_priv(dai);

	अगर (!snd_soc_dai_active(dai))
		वापस;

	aio->chip->num_wup_aios--;
	अगर (!aio->chip->num_wup_aios) अणु
		reset_control_निश्चित(aio->chip->rst);
		clk_disable_unprepare(aio->chip->clk);
	पूर्ण
पूर्ण

अटल पूर्णांक uniphier_aio_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dai *dai;

	क्रम_each_component_dais(component, dai)
		uniphier_aio_dai_suspend(dai);
	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_aio_dai_resume(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा uniphier_aio *aio = uniphier_priv(dai);
	पूर्णांक ret, i;

	अगर (!snd_soc_dai_active(dai))
		वापस 0;

	अगर (!aio->chip->active)
		वापस 0;

	अगर (!aio->chip->num_wup_aios) अणु
		ret = clk_prepare_enable(aio->chip->clk);
		अगर (ret)
			वापस ret;

		ret = reset_control_deनिश्चित(aio->chip->rst);
		अगर (ret)
			जाओ err_out_घड़ी;
	पूर्ण

	aio_iecout_set_enable(aio->chip, true);
	aio_chip_init(aio->chip);

	क्रम (i = 0; i < ARRAY_SIZE(aio->sub); i++) अणु
		काष्ठा uniphier_aio_sub *sub = &aio->sub[i];

		अगर (!sub->spec || !sub->substream)
			जारी;

		ret = aio_init(sub);
		अगर (ret)
			जाओ err_out_reset;

		अगर (!sub->setting)
			जारी;

		aio_port_reset(sub);
		aio_src_reset(sub);
	पूर्ण
	aio->chip->num_wup_aios++;

	वापस 0;

err_out_reset:
	अगर (!aio->chip->num_wup_aios)
		reset_control_निश्चित(aio->chip->rst);
err_out_घड़ी:
	अगर (!aio->chip->num_wup_aios)
		clk_disable_unprepare(aio->chip->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_aio_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dai *dai;
	पूर्णांक ret = 0;

	क्रम_each_component_dais(component, dai)
		ret |= uniphier_aio_dai_resume(dai);
	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_aio_vol_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = AUD_VOL_MAX;

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_aio_vol_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_kcontrol_component(kcontrol);
	काष्ठा uniphier_aio_chip *chip = snd_soc_component_get_drvdata(comp);
	काष्ठा uniphier_aio_sub *sub;
	पूर्णांक oport_hw = kcontrol->निजी_value;

	sub = find_volume(chip, oport_hw);
	अगर (!sub)
		वापस 0;

	ucontrol->value.पूर्णांकeger.value[0] = sub->vol;

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_aio_vol_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_kcontrol_component(kcontrol);
	काष्ठा uniphier_aio_chip *chip = snd_soc_component_get_drvdata(comp);
	काष्ठा uniphier_aio_sub *sub;
	पूर्णांक oport_hw = kcontrol->निजी_value;

	sub = find_volume(chip, oport_hw);
	अगर (!sub)
		वापस 0;

	अगर (sub->vol == ucontrol->value.पूर्णांकeger.value[0])
		वापस 0;
	sub->vol = ucontrol->value.पूर्णांकeger.value[0];

	aio_port_set_volume(sub, sub->vol);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new uniphier_aio_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.name = "HPCMOUT1 Volume",
		.info = uniphier_aio_vol_info,
		.get = uniphier_aio_vol_get,
		.put = uniphier_aio_vol_put,
		.निजी_value = AUD_HW_HPCMOUT1,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.name = "PCMOUT1 Volume",
		.info = uniphier_aio_vol_info,
		.get = uniphier_aio_vol_get,
		.put = uniphier_aio_vol_put,
		.निजी_value = AUD_HW_PCMOUT1,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.name = "PCMOUT2 Volume",
		.info = uniphier_aio_vol_info,
		.get = uniphier_aio_vol_get,
		.put = uniphier_aio_vol_put,
		.निजी_value = AUD_HW_PCMOUT2,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.name = "PCMOUT3 Volume",
		.info = uniphier_aio_vol_info,
		.get = uniphier_aio_vol_get,
		.put = uniphier_aio_vol_put,
		.निजी_value = AUD_HW_PCMOUT3,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.name = "HIECOUT1 Volume",
		.info = uniphier_aio_vol_info,
		.get = uniphier_aio_vol_get,
		.put = uniphier_aio_vol_put,
		.निजी_value = AUD_HW_HIECOUT1,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.name = "IECOUT1 Volume",
		.info = uniphier_aio_vol_info,
		.get = uniphier_aio_vol_get,
		.put = uniphier_aio_vol_put,
		.निजी_value = AUD_HW_IECOUT1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver uniphier_aio_component = अणु
	.name = "uniphier-aio",
	.controls = uniphier_aio_controls,
	.num_controls = ARRAY_SIZE(uniphier_aio_controls),
	.suspend = uniphier_aio_suspend,
	.resume  = uniphier_aio_resume,
पूर्ण;

पूर्णांक uniphier_aio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uniphier_aio_chip *chip;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret, i, j;

	chip = devm_kzalloc(dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->chip_spec = of_device_get_match_data(dev);
	अगर (!chip->chip_spec)
		वापस -EINVAL;

	chip->regmap_sg = syscon_regmap_lookup_by_phandle(dev->of_node,
							  "socionext,syscon");
	अगर (IS_ERR(chip->regmap_sg)) अणु
		अगर (PTR_ERR(chip->regmap_sg) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		chip->regmap_sg = शून्य;
	पूर्ण

	chip->clk = devm_clk_get(dev, "aio");
	अगर (IS_ERR(chip->clk))
		वापस PTR_ERR(chip->clk);

	chip->rst = devm_reset_control_get_shared(dev, "aio");
	अगर (IS_ERR(chip->rst))
		वापस PTR_ERR(chip->rst);

	chip->num_aios = chip->chip_spec->num_dais;
	chip->num_wup_aios = chip->num_aios;
	chip->aios = devm_kसुस्मृति(dev,
				  chip->num_aios, माप(काष्ठा uniphier_aio),
				  GFP_KERNEL);
	अगर (!chip->aios)
		वापस -ENOMEM;

	chip->num_plls = chip->chip_spec->num_plls;
	chip->plls = devm_kसुस्मृति(dev,
				  chip->num_plls,
				  माप(काष्ठा uniphier_aio_pll),
				  GFP_KERNEL);
	अगर (!chip->plls)
		वापस -ENOMEM;
	स_नकल(chip->plls, chip->chip_spec->plls,
	       माप(काष्ठा uniphier_aio_pll) * chip->num_plls);

	क्रम (i = 0; i < chip->num_aios; i++) अणु
		काष्ठा uniphier_aio *aio = &chip->aios[i];

		aio->chip = chip;
		aio->fmt = SND_SOC_DAIFMT_I2S;

		क्रम (j = 0; j < ARRAY_SIZE(aio->sub); j++) अणु
			काष्ठा uniphier_aio_sub *sub = &aio->sub[j];

			sub->aio = aio;
			spin_lock_init(&sub->lock);
		पूर्ण
	पूर्ण

	chip->pdev = pdev;
	platक्रमm_set_drvdata(pdev, chip);

	ret = clk_prepare_enable(chip->clk);
	अगर (ret)
		वापस ret;

	ret = reset_control_deनिश्चित(chip->rst);
	अगर (ret)
		जाओ err_out_घड़ी;

	ret = devm_snd_soc_रेजिस्टर_component(dev, &uniphier_aio_component,
					      chip->chip_spec->dais,
					      chip->chip_spec->num_dais);
	अगर (ret) अणु
		dev_err(dev, "Register component failed.\n");
		जाओ err_out_reset;
	पूर्ण

	ret = uniphier_aiodma_soc_रेजिस्टर_platक्रमm(pdev);
	अगर (ret) अणु
		dev_err(dev, "Register platform failed.\n");
		जाओ err_out_reset;
	पूर्ण

	वापस 0;

err_out_reset:
	reset_control_निश्चित(chip->rst);

err_out_घड़ी:
	clk_disable_unprepare(chip->clk);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(uniphier_aio_probe);

पूर्णांक uniphier_aio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uniphier_aio_chip *chip = platक्रमm_get_drvdata(pdev);

	reset_control_निश्चित(chip->rst);
	clk_disable_unprepare(chip->clk);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(uniphier_aio_हटाओ);

MODULE_AUTHOR("Katsuhiro Suzuki <suzuki.katsuhiro@socionext.com>");
MODULE_DESCRIPTION("UniPhier AIO CPU DAI driver.");
MODULE_LICENSE("GPL v2");
