<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// soc-component.c
//
// Copyright 2009-2011 Wolfson Microelectronics PLC.
// Copyright (C) 2019 Renesas Electronics Corp.
//
// Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
// Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
//
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/soc.h>
#समावेश <linux/bitops.h>

#घोषणा soc_component_ret(dai, ret) _soc_component_ret(dai, __func__, ret)
अटल अंतरभूत पूर्णांक _soc_component_ret(काष्ठा snd_soc_component *component,
				     स्थिर अक्षर *func, पूर्णांक ret)
अणु
	/* Positive/Zero values are not errors */
	अगर (ret >= 0)
		वापस ret;

	/* Negative values might be errors */
	चयन (ret) अणु
	हाल -EPROBE_DEFER:
	हाल -ENOTSUPP:
		अवरोध;
	शेष:
		dev_err(component->dev,
			"ASoC: error at %s on %s: %d\n",
			func, component->name, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक soc_component_field_shअगरt(काष्ठा snd_soc_component *component,
					    अचिन्हित पूर्णांक mask)
अणु
	अगर (!mask) अणु
		dev_err(component->dev,	"ASoC: error field mask is zero for %s\n",
			component->name);
		वापस 0;
	पूर्ण

	वापस (ffs(mask) - 1);
पूर्ण

/*
 * We might want to check substream by using list.
 * In such हाल, we can update these macros.
 */
#घोषणा soc_component_mark_push(component, substream, tgt)	((component)->mark_##tgt = substream)
#घोषणा soc_component_mark_pop(component, substream, tgt)	((component)->mark_##tgt = शून्य)
#घोषणा soc_component_mark_match(component, substream, tgt)	((component)->mark_##tgt == substream)

व्योम snd_soc_component_set_aux(काष्ठा snd_soc_component *component,
			       काष्ठा snd_soc_aux_dev *aux)
अणु
	component->init = (aux) ? aux->init : शून्य;
पूर्ण

पूर्णांक snd_soc_component_init(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret = 0;

	अगर (component->init)
		ret = component->init(component);

	वापस soc_component_ret(component, ret);
पूर्ण

/**
 * snd_soc_component_set_sysclk - configure COMPONENT प्रणाली or master घड़ी.
 * @component: COMPONENT
 * @clk_id: DAI specअगरic घड़ी ID
 * @source: Source क्रम the घड़ी
 * @freq: new घड़ी frequency in Hz
 * @dir: new घड़ी direction - input/output.
 *
 * Configures the CODEC master (MCLK) or प्रणाली (SYSCLK) घड़ीing.
 */
पूर्णांक snd_soc_component_set_sysclk(काष्ठा snd_soc_component *component,
				 पूर्णांक clk_id, पूर्णांक source, अचिन्हित पूर्णांक freq,
				 पूर्णांक dir)
अणु
	पूर्णांक ret = -ENOTSUPP;

	अगर (component->driver->set_sysclk)
		ret = component->driver->set_sysclk(component, clk_id, source,
						     freq, dir);

	वापस soc_component_ret(component, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_set_sysclk);

/*
 * snd_soc_component_set_pll - configure component PLL.
 * @component: COMPONENT
 * @pll_id: DAI specअगरic PLL ID
 * @source: DAI specअगरic source क्रम the PLL
 * @freq_in: PLL input घड़ी frequency in Hz
 * @freq_out: requested PLL output घड़ी frequency in Hz
 *
 * Configures and enables PLL to generate output घड़ी based on input घड़ी.
 */
पूर्णांक snd_soc_component_set_pll(काष्ठा snd_soc_component *component, पूर्णांक pll_id,
			      पूर्णांक source, अचिन्हित पूर्णांक freq_in,
			      अचिन्हित पूर्णांक freq_out)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (component->driver->set_pll)
		ret = component->driver->set_pll(component, pll_id, source,
						  freq_in, freq_out);

	वापस soc_component_ret(component, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_set_pll);

व्योम snd_soc_component_seq_notअगरier(काष्ठा snd_soc_component *component,
				    क्रमागत snd_soc_dapm_type type, पूर्णांक subseq)
अणु
	अगर (component->driver->seq_notअगरier)
		component->driver->seq_notअगरier(component, type, subseq);
पूर्ण

पूर्णांक snd_soc_component_stream_event(काष्ठा snd_soc_component *component,
				   पूर्णांक event)
अणु
	पूर्णांक ret = 0;

	अगर (component->driver->stream_event)
		ret = component->driver->stream_event(component, event);

	वापस soc_component_ret(component, ret);
पूर्ण

पूर्णांक snd_soc_component_set_bias_level(काष्ठा snd_soc_component *component,
				     क्रमागत snd_soc_bias_level level)
अणु
	पूर्णांक ret = 0;

	अगर (component->driver->set_bias_level)
		ret = component->driver->set_bias_level(component, level);

	वापस soc_component_ret(component, ret);
पूर्ण

अटल पूर्णांक soc_component_pin(काष्ठा snd_soc_component *component,
			     स्थिर अक्षर *pin,
			     पूर्णांक (*pin_func)(काष्ठा snd_soc_dapm_context *dapm,
					     स्थिर अक्षर *pin))
अणु
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	अक्षर *full_name;
	पूर्णांक ret;

	अगर (!component->name_prefix) अणु
		ret = pin_func(dapm, pin);
		जाओ end;
	पूर्ण

	full_name = kaप्र_लिखो(GFP_KERNEL, "%s %s", component->name_prefix, pin);
	अगर (!full_name) अणु
		ret = -ENOMEM;
		जाओ end;
	पूर्ण

	ret = pin_func(dapm, full_name);
	kमुक्त(full_name);
end:
	वापस soc_component_ret(component, ret);
पूर्ण

पूर्णांक snd_soc_component_enable_pin(काष्ठा snd_soc_component *component,
				 स्थिर अक्षर *pin)
अणु
	वापस soc_component_pin(component, pin, snd_soc_dapm_enable_pin);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_enable_pin);

पूर्णांक snd_soc_component_enable_pin_unlocked(काष्ठा snd_soc_component *component,
					  स्थिर अक्षर *pin)
अणु
	वापस soc_component_pin(component, pin, snd_soc_dapm_enable_pin_unlocked);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_enable_pin_unlocked);

पूर्णांक snd_soc_component_disable_pin(काष्ठा snd_soc_component *component,
				  स्थिर अक्षर *pin)
अणु
	वापस soc_component_pin(component, pin, snd_soc_dapm_disable_pin);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_disable_pin);

पूर्णांक snd_soc_component_disable_pin_unlocked(काष्ठा snd_soc_component *component,
					   स्थिर अक्षर *pin)
अणु
	वापस soc_component_pin(component, pin, snd_soc_dapm_disable_pin_unlocked);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_disable_pin_unlocked);

पूर्णांक snd_soc_component_nc_pin(काष्ठा snd_soc_component *component,
			     स्थिर अक्षर *pin)
अणु
	वापस soc_component_pin(component, pin, snd_soc_dapm_nc_pin);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_nc_pin);

पूर्णांक snd_soc_component_nc_pin_unlocked(काष्ठा snd_soc_component *component,
				      स्थिर अक्षर *pin)
अणु
	वापस soc_component_pin(component, pin, snd_soc_dapm_nc_pin_unlocked);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_nc_pin_unlocked);

पूर्णांक snd_soc_component_get_pin_status(काष्ठा snd_soc_component *component,
				     स्थिर अक्षर *pin)
अणु
	वापस soc_component_pin(component, pin, snd_soc_dapm_get_pin_status);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_get_pin_status);

पूर्णांक snd_soc_component_क्रमce_enable_pin(काष्ठा snd_soc_component *component,
				       स्थिर अक्षर *pin)
अणु
	वापस soc_component_pin(component, pin, snd_soc_dapm_क्रमce_enable_pin);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_क्रमce_enable_pin);

पूर्णांक snd_soc_component_क्रमce_enable_pin_unlocked(
	काष्ठा snd_soc_component *component,
	स्थिर अक्षर *pin)
अणु
	वापस soc_component_pin(component, pin, snd_soc_dapm_क्रमce_enable_pin_unlocked);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_क्रमce_enable_pin_unlocked);

/**
 * snd_soc_component_set_jack - configure component jack.
 * @component: COMPONENTs
 * @jack: काष्ठाure to use क्रम the jack
 * @data: can be used अगर codec driver need extra data क्रम configuring jack
 *
 * Configures and enables jack detection function.
 */
पूर्णांक snd_soc_component_set_jack(काष्ठा snd_soc_component *component,
			       काष्ठा snd_soc_jack *jack, व्योम *data)
अणु
	पूर्णांक ret = -ENOTSUPP;

	अगर (component->driver->set_jack)
		ret = component->driver->set_jack(component, jack, data);

	वापस soc_component_ret(component, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_set_jack);

पूर्णांक snd_soc_component_module_get(काष्ठा snd_soc_component *component,
				 काष्ठा snd_pcm_substream *substream,
				 पूर्णांक upon_खोलो)
अणु
	पूर्णांक ret = 0;

	अगर (component->driver->module_get_upon_खोलो == !!upon_खोलो &&
	    !try_module_get(component->dev->driver->owner))
		ret = -ENODEV;

	/* mark substream अगर succeeded */
	अगर (ret == 0)
		soc_component_mark_push(component, substream, module);

	वापस soc_component_ret(component, ret);
पूर्ण

व्योम snd_soc_component_module_put(काष्ठा snd_soc_component *component,
				  काष्ठा snd_pcm_substream *substream,
				  पूर्णांक upon_खोलो, पूर्णांक rollback)
अणु
	अगर (rollback && !soc_component_mark_match(component, substream, module))
		वापस;

	अगर (component->driver->module_get_upon_खोलो == !!upon_खोलो)
		module_put(component->dev->driver->owner);

	/* हटाओ marked substream */
	soc_component_mark_pop(component, substream, module);
पूर्ण

पूर्णांक snd_soc_component_खोलो(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक ret = 0;

	अगर (component->driver->खोलो)
		ret = component->driver->खोलो(component, substream);

	/* mark substream अगर succeeded */
	अगर (ret == 0)
		soc_component_mark_push(component, substream, खोलो);

	वापस soc_component_ret(component, ret);
पूर्ण

पूर्णांक snd_soc_component_बंद(काष्ठा snd_soc_component *component,
			    काष्ठा snd_pcm_substream *substream,
			    पूर्णांक rollback)
अणु
	पूर्णांक ret = 0;

	अगर (rollback && !soc_component_mark_match(component, substream, खोलो))
		वापस 0;

	अगर (component->driver->बंद)
		ret = component->driver->बंद(component, substream);

	/* हटाओ marked substream */
	soc_component_mark_pop(component, substream, खोलो);

	वापस soc_component_ret(component, ret);
पूर्ण

व्योम snd_soc_component_suspend(काष्ठा snd_soc_component *component)
अणु
	अगर (component->driver->suspend)
		component->driver->suspend(component);
	component->suspended = 1;
पूर्ण

व्योम snd_soc_component_resume(काष्ठा snd_soc_component *component)
अणु
	अगर (component->driver->resume)
		component->driver->resume(component);
	component->suspended = 0;
पूर्ण

पूर्णांक snd_soc_component_is_suspended(काष्ठा snd_soc_component *component)
अणु
	वापस component->suspended;
पूर्ण

पूर्णांक snd_soc_component_probe(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret = 0;

	अगर (component->driver->probe)
		ret = component->driver->probe(component);

	वापस soc_component_ret(component, ret);
पूर्ण

व्योम snd_soc_component_हटाओ(काष्ठा snd_soc_component *component)
अणु
	अगर (component->driver->हटाओ)
		component->driver->हटाओ(component);
पूर्ण

पूर्णांक snd_soc_component_of_xlate_dai_id(काष्ठा snd_soc_component *component,
				      काष्ठा device_node *ep)
अणु
	पूर्णांक ret = -ENOTSUPP;

	अगर (component->driver->of_xlate_dai_id)
		ret = component->driver->of_xlate_dai_id(component, ep);

	वापस soc_component_ret(component, ret);
पूर्ण

पूर्णांक snd_soc_component_of_xlate_dai_name(काष्ठा snd_soc_component *component,
					स्थिर काष्ठा of_phandle_args *args,
					स्थिर अक्षर **dai_name)
अणु
	अगर (component->driver->of_xlate_dai_name)
		वापस component->driver->of_xlate_dai_name(component,
							    args, dai_name);
	/*
	 * Don't use soc_component_ret here because we may not want to report
	 * the error just yet. If a device has more than one component, the
	 * first may not match and we करोn't want spam the log with this.
	 */
	वापस -ENOTSUPP;
पूर्ण

व्योम snd_soc_component_setup_regmap(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक val_bytes = regmap_get_val_bytes(component->regmap);

	/* Errors are legitimate क्रम non-पूर्णांकeger byte multiples */
	अगर (val_bytes > 0)
		component->val_bytes = val_bytes;
पूर्ण

#अगर_घोषित CONFIG_REGMAP

/**
 * snd_soc_component_init_regmap() - Initialize regmap instance क्रम the
 *                                   component
 * @component: The component क्रम which to initialize the regmap instance
 * @regmap: The regmap instance that should be used by the component
 *
 * This function allows deferred assignment of the regmap instance that is
 * associated with the component. Only use this अगर the regmap instance is not
 * yet पढ़ोy when the component is रेजिस्टरed. The function must also be called
 * beक्रमe the first IO attempt of the component.
 */
व्योम snd_soc_component_init_regmap(काष्ठा snd_soc_component *component,
				   काष्ठा regmap *regmap)
अणु
	component->regmap = regmap;
	snd_soc_component_setup_regmap(component);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_init_regmap);

/**
 * snd_soc_component_निकास_regmap() - De-initialize regmap instance क्रम the
 *                                   component
 * @component: The component क्रम which to de-initialize the regmap instance
 *
 * Calls regmap_निकास() on the regmap instance associated to the component and
 * हटाओs the regmap instance from the component.
 *
 * This function should only be used अगर snd_soc_component_init_regmap() was used
 * to initialize the regmap instance.
 */
व्योम snd_soc_component_निकास_regmap(काष्ठा snd_soc_component *component)
अणु
	regmap_निकास(component->regmap);
	component->regmap = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_निकास_regmap);

#पूर्ण_अगर

पूर्णांक snd_soc_component_compr_खोलो(काष्ठा snd_compr_stream *cstream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_soc_component *component;
	पूर्णांक i, ret;

	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (component->driver->compress_ops &&
		    component->driver->compress_ops->खोलो) अणु
			ret = component->driver->compress_ops->खोलो(component, cstream);
			अगर (ret < 0)
				वापस soc_component_ret(component, ret);
		पूर्ण
		soc_component_mark_push(component, cstream, compr_खोलो);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_compr_खोलो);

व्योम snd_soc_component_compr_मुक्त(काष्ठा snd_compr_stream *cstream,
				  पूर्णांक rollback)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_soc_component *component;
	पूर्णांक i;

	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (rollback && !soc_component_mark_match(component, cstream, compr_खोलो))
			जारी;

		अगर (component->driver->compress_ops &&
		    component->driver->compress_ops->मुक्त)
			component->driver->compress_ops->मुक्त(component, cstream);

		soc_component_mark_pop(component, cstream, compr_खोलो);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_compr_मुक्त);

पूर्णांक snd_soc_component_compr_trigger(काष्ठा snd_compr_stream *cstream, पूर्णांक cmd)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_soc_component *component;
	पूर्णांक i, ret;

	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (component->driver->compress_ops &&
		    component->driver->compress_ops->trigger) अणु
			ret = component->driver->compress_ops->trigger(
				component, cstream, cmd);
			अगर (ret < 0)
				वापस soc_component_ret(component, ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_compr_trigger);

पूर्णांक snd_soc_component_compr_set_params(काष्ठा snd_compr_stream *cstream,
				       काष्ठा snd_compr_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_soc_component *component;
	पूर्णांक i, ret;

	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (component->driver->compress_ops &&
		    component->driver->compress_ops->set_params) अणु
			ret = component->driver->compress_ops->set_params(
				component, cstream, params);
			अगर (ret < 0)
				वापस soc_component_ret(component, ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_compr_set_params);

पूर्णांक snd_soc_component_compr_get_params(काष्ठा snd_compr_stream *cstream,
				       काष्ठा snd_codec *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_soc_component *component;
	पूर्णांक i, ret;

	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (component->driver->compress_ops &&
		    component->driver->compress_ops->get_params) अणु
			ret = component->driver->compress_ops->get_params(
				component, cstream, params);
			वापस soc_component_ret(component, ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_compr_get_params);

पूर्णांक snd_soc_component_compr_get_caps(काष्ठा snd_compr_stream *cstream,
				     काष्ठा snd_compr_caps *caps)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_soc_component *component;
	पूर्णांक i, ret = 0;

	mutex_lock_nested(&rtd->card->pcm_mutex, rtd->card->pcm_subclass);

	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (component->driver->compress_ops &&
		    component->driver->compress_ops->get_caps) अणु
			ret = component->driver->compress_ops->get_caps(
				component, cstream, caps);
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&rtd->card->pcm_mutex);

	वापस soc_component_ret(component, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_compr_get_caps);

पूर्णांक snd_soc_component_compr_get_codec_caps(काष्ठा snd_compr_stream *cstream,
					   काष्ठा snd_compr_codec_caps *codec)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_soc_component *component;
	पूर्णांक i, ret = 0;

	mutex_lock_nested(&rtd->card->pcm_mutex, rtd->card->pcm_subclass);

	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (component->driver->compress_ops &&
		    component->driver->compress_ops->get_codec_caps) अणु
			ret = component->driver->compress_ops->get_codec_caps(
				component, cstream, codec);
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&rtd->card->pcm_mutex);

	वापस soc_component_ret(component, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_compr_get_codec_caps);

पूर्णांक snd_soc_component_compr_ack(काष्ठा snd_compr_stream *cstream, माप_प्रकार bytes)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_soc_component *component;
	पूर्णांक i, ret;

	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (component->driver->compress_ops &&
		    component->driver->compress_ops->ack) अणु
			ret = component->driver->compress_ops->ack(
				component, cstream, bytes);
			अगर (ret < 0)
				वापस soc_component_ret(component, ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_compr_ack);

पूर्णांक snd_soc_component_compr_poपूर्णांकer(काष्ठा snd_compr_stream *cstream,
				    काष्ठा snd_compr_tstamp *tstamp)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_soc_component *component;
	पूर्णांक i, ret;

	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (component->driver->compress_ops &&
		    component->driver->compress_ops->poपूर्णांकer) अणु
			ret = component->driver->compress_ops->poपूर्णांकer(
				component, cstream, tstamp);
			वापस soc_component_ret(component, ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_compr_poपूर्णांकer);

पूर्णांक snd_soc_component_compr_copy(काष्ठा snd_compr_stream *cstream,
				 अक्षर __user *buf, माप_प्रकार count)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_soc_component *component;
	पूर्णांक i, ret = 0;

	mutex_lock_nested(&rtd->card->pcm_mutex, rtd->card->pcm_subclass);

	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (component->driver->compress_ops &&
		    component->driver->compress_ops->copy) अणु
			ret = component->driver->compress_ops->copy(
				component, cstream, buf, count);
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&rtd->card->pcm_mutex);

	वापस soc_component_ret(component, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_compr_copy);

पूर्णांक snd_soc_component_compr_set_metadata(काष्ठा snd_compr_stream *cstream,
					 काष्ठा snd_compr_metadata *metadata)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_soc_component *component;
	पूर्णांक i, ret;

	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (component->driver->compress_ops &&
		    component->driver->compress_ops->set_metadata) अणु
			ret = component->driver->compress_ops->set_metadata(
				component, cstream, metadata);
			अगर (ret < 0)
				वापस soc_component_ret(component, ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_compr_set_metadata);

पूर्णांक snd_soc_component_compr_get_metadata(काष्ठा snd_compr_stream *cstream,
					 काष्ठा snd_compr_metadata *metadata)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_soc_component *component;
	पूर्णांक i, ret;

	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (component->driver->compress_ops &&
		    component->driver->compress_ops->get_metadata) अणु
			ret = component->driver->compress_ops->get_metadata(
				component, cstream, metadata);
			वापस soc_component_ret(component, ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_compr_get_metadata);

अटल अचिन्हित पूर्णांक soc_component_पढ़ो_no_lock(
	काष्ठा snd_soc_component *component,
	अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val = 0;

	अगर (component->regmap)
		ret = regmap_पढ़ो(component->regmap, reg, &val);
	अन्यथा अगर (component->driver->पढ़ो) अणु
		ret = 0;
		val = component->driver->पढ़ो(component, reg);
	पूर्ण
	अन्यथा
		ret = -EIO;

	अगर (ret < 0)
		वापस soc_component_ret(component, ret);

	वापस val;
पूर्ण

/**
 * snd_soc_component_पढ़ो() - Read रेजिस्टर value
 * @component: Component to पढ़ो from
 * @reg: Register to पढ़ो
 *
 * Return: पढ़ो value
 */
अचिन्हित पूर्णांक snd_soc_component_पढ़ो(काष्ठा snd_soc_component *component,
				    अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक val;

	mutex_lock(&component->io_mutex);
	val = soc_component_पढ़ो_no_lock(component, reg);
	mutex_unlock(&component->io_mutex);

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_पढ़ो);

अटल पूर्णांक soc_component_ग_लिखो_no_lock(
	काष्ठा snd_soc_component *component,
	अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	पूर्णांक ret = -EIO;

	अगर (component->regmap)
		ret = regmap_ग_लिखो(component->regmap, reg, val);
	अन्यथा अगर (component->driver->ग_लिखो)
		ret = component->driver->ग_लिखो(component, reg, val);

	वापस soc_component_ret(component, ret);
पूर्ण

/**
 * snd_soc_component_ग_लिखो() - Write रेजिस्टर value
 * @component: Component to ग_लिखो to
 * @reg: Register to ग_लिखो
 * @val: Value to ग_लिखो to the रेजिस्टर
 *
 * Return: 0 on success, a negative error code otherwise.
 */
पूर्णांक snd_soc_component_ग_लिखो(काष्ठा snd_soc_component *component,
			    अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	पूर्णांक ret;

	mutex_lock(&component->io_mutex);
	ret = soc_component_ग_लिखो_no_lock(component, reg, val);
	mutex_unlock(&component->io_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_ग_लिखो);

अटल पूर्णांक snd_soc_component_update_bits_legacy(
	काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val, bool *change)
अणु
	अचिन्हित पूर्णांक old, new;
	पूर्णांक ret = 0;

	mutex_lock(&component->io_mutex);

	old = soc_component_पढ़ो_no_lock(component, reg);

	new = (old & ~mask) | (val & mask);
	*change = old != new;
	अगर (*change)
		ret = soc_component_ग_लिखो_no_lock(component, reg, new);

	mutex_unlock(&component->io_mutex);

	वापस soc_component_ret(component, ret);
पूर्ण

/**
 * snd_soc_component_update_bits() - Perक्रमm पढ़ो/modअगरy/ग_लिखो cycle
 * @component: Component to update
 * @reg: Register to update
 * @mask: Mask that specअगरies which bits to update
 * @val: New value क्रम the bits specअगरied by mask
 *
 * Return: 1 अगर the operation was successful and the value of the रेजिस्टर
 * changed, 0 अगर the operation was successful, but the value did not change.
 * Returns a negative error code otherwise.
 */
पूर्णांक snd_soc_component_update_bits(काष्ठा snd_soc_component *component,
				  अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	bool change;
	पूर्णांक ret;

	अगर (component->regmap)
		ret = regmap_update_bits_check(component->regmap, reg, mask,
					       val, &change);
	अन्यथा
		ret = snd_soc_component_update_bits_legacy(component, reg,
							   mask, val, &change);

	अगर (ret < 0)
		वापस soc_component_ret(component, ret);
	वापस change;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_update_bits);

/**
 * snd_soc_component_update_bits_async() - Perक्रमm asynchronous
 *  पढ़ो/modअगरy/ग_लिखो cycle
 * @component: Component to update
 * @reg: Register to update
 * @mask: Mask that specअगरies which bits to update
 * @val: New value क्रम the bits specअगरied by mask
 *
 * This function is similar to snd_soc_component_update_bits(), but the update
 * operation is scheduled asynchronously. This means it may not be completed
 * when the function वापसs. To make sure that all scheduled updates have been
 * completed snd_soc_component_async_complete() must be called.
 *
 * Return: 1 अगर the operation was successful and the value of the रेजिस्टर
 * changed, 0 अगर the operation was successful, but the value did not change.
 * Returns a negative error code otherwise.
 */
पूर्णांक snd_soc_component_update_bits_async(काष्ठा snd_soc_component *component,
					अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	bool change;
	पूर्णांक ret;

	अगर (component->regmap)
		ret = regmap_update_bits_check_async(component->regmap, reg,
						     mask, val, &change);
	अन्यथा
		ret = snd_soc_component_update_bits_legacy(component, reg,
							   mask, val, &change);

	अगर (ret < 0)
		वापस soc_component_ret(component, ret);
	वापस change;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_update_bits_async);

/**
 * snd_soc_component_पढ़ो_field() - Read रेजिस्टर field value
 * @component: Component to पढ़ो from
 * @reg: Register to पढ़ो
 * @mask: mask of the रेजिस्टर field
 *
 * Return: पढ़ो value of रेजिस्टर field.
 */
अचिन्हित पूर्णांक snd_soc_component_पढ़ो_field(काष्ठा snd_soc_component *component,
					  अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक val;

	val = snd_soc_component_पढ़ो(component, reg);

	val = (val & mask) >> soc_component_field_shअगरt(component, mask);

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_पढ़ो_field);

/**
 * snd_soc_component_ग_लिखो_field() - ग_लिखो to रेजिस्टर field
 * @component: Component to ग_लिखो to
 * @reg: Register to ग_लिखो
 * @mask: mask of the रेजिस्टर field to update
 * @val: value of the field to ग_लिखो
 *
 * Return: 1 क्रम change, otherwise 0.
 */
पूर्णांक snd_soc_component_ग_लिखो_field(काष्ठा snd_soc_component *component,
				  अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mask,
				  अचिन्हित पूर्णांक val)
अणु

	val = (val << soc_component_field_shअगरt(component, mask)) & mask;

	वापस snd_soc_component_update_bits(component, reg, mask, val);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_ग_लिखो_field);

/**
 * snd_soc_component_async_complete() - Ensure asynchronous I/O has completed
 * @component: Component क्रम which to रुको
 *
 * This function blocks until all asynchronous I/O which has previously been
 * scheduled using snd_soc_component_update_bits_async() has completed.
 */
व्योम snd_soc_component_async_complete(काष्ठा snd_soc_component *component)
अणु
	अगर (component->regmap)
		regmap_async_complete(component->regmap);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_async_complete);

/**
 * snd_soc_component_test_bits - Test रेजिस्टर क्रम change
 * @component: component
 * @reg: Register to test
 * @mask: Mask that specअगरies which bits to test
 * @value: Value to test against
 *
 * Tests a रेजिस्टर with a new value and checks अगर the new value is
 * dअगरferent from the old value.
 *
 * Return: 1 क्रम change, otherwise 0.
 */
पूर्णांक snd_soc_component_test_bits(काष्ठा snd_soc_component *component,
				अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक value)
अणु
	अचिन्हित पूर्णांक old, new;

	old = snd_soc_component_पढ़ो(component, reg);
	new = (old & ~mask) | value;
	वापस old != new;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_component_test_bits);

पूर्णांक snd_soc_pcm_component_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component;
	पूर्णांक i;

	/* FIXME: use 1st poपूर्णांकer */
	क्रम_each_rtd_components(rtd, i, component)
		अगर (component->driver->poपूर्णांकer)
			वापस component->driver->poपूर्णांकer(component, substream);

	वापस 0;
पूर्ण

पूर्णांक snd_soc_pcm_component_ioctl(काष्ठा snd_pcm_substream *substream,
				अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component;
	पूर्णांक i;

	/* FIXME: use 1st ioctl */
	क्रम_each_rtd_components(rtd, i, component)
		अगर (component->driver->ioctl)
			वापस soc_component_ret(
				component,
				component->driver->ioctl(component,
							 substream, cmd, arg));

	वापस snd_pcm_lib_ioctl(substream, cmd, arg);
पूर्ण

पूर्णांक snd_soc_pcm_component_sync_stop(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component;
	पूर्णांक i, ret;

	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (component->driver->sync_stop) अणु
			ret = component->driver->sync_stop(component,
							   substream);
			अगर (ret < 0)
				वापस soc_component_ret(component, ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_soc_pcm_component_copy_user(काष्ठा snd_pcm_substream *substream,
				    पूर्णांक channel, अचिन्हित दीर्घ pos,
				    व्योम __user *buf, अचिन्हित दीर्घ bytes)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component;
	पूर्णांक i;

	/* FIXME. it वापसs 1st copy now */
	क्रम_each_rtd_components(rtd, i, component)
		अगर (component->driver->copy_user)
			वापस soc_component_ret(
				component,
				component->driver->copy_user(
					component, substream, channel,
					pos, buf, bytes));

	वापस -EINVAL;
पूर्ण

काष्ठा page *snd_soc_pcm_component_page(काष्ठा snd_pcm_substream *substream,
					अचिन्हित दीर्घ offset)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component;
	काष्ठा page *page;
	पूर्णांक i;

	/* FIXME. it वापसs 1st page now */
	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (component->driver->page) अणु
			page = component->driver->page(component,
						       substream, offset);
			अगर (page)
				वापस page;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक snd_soc_pcm_component_mmap(काष्ठा snd_pcm_substream *substream,
			       काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component;
	पूर्णांक i;

	/* FIXME. it वापसs 1st mmap now */
	क्रम_each_rtd_components(rtd, i, component)
		अगर (component->driver->mmap)
			वापस soc_component_ret(
				component,
				component->driver->mmap(component,
							substream, vma));

	वापस -EINVAL;
पूर्ण

पूर्णांक snd_soc_pcm_component_new(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *component;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (component->driver->pcm_स्थिरruct) अणु
			ret = component->driver->pcm_स्थिरruct(component, rtd);
			अगर (ret < 0)
				वापस soc_component_ret(component, ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम snd_soc_pcm_component_मुक्त(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *component;
	पूर्णांक i;

	अगर (!rtd->pcm)
		वापस;

	क्रम_each_rtd_components(rtd, i, component)
		अगर (component->driver->pcm_deकाष्ठा)
			component->driver->pcm_deकाष्ठा(component, rtd->pcm);
पूर्ण

पूर्णांक snd_soc_pcm_component_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component;
	पूर्णांक i, ret;

	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (component->driver->prepare) अणु
			ret = component->driver->prepare(component, substream);
			अगर (ret < 0)
				वापस soc_component_ret(component, ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_soc_pcm_component_hw_params(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component;
	पूर्णांक i, ret;

	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (component->driver->hw_params) अणु
			ret = component->driver->hw_params(component,
							   substream, params);
			अगर (ret < 0)
				वापस soc_component_ret(component, ret);
		पूर्ण
		/* mark substream अगर succeeded */
		soc_component_mark_push(component, substream, hw_params);
	पूर्ण

	वापस 0;
पूर्ण

व्योम snd_soc_pcm_component_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
				   पूर्णांक rollback)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component;
	पूर्णांक i, ret;

	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (rollback && !soc_component_mark_match(component, substream, hw_params))
			जारी;

		अगर (component->driver->hw_मुक्त) अणु
			ret = component->driver->hw_मुक्त(component, substream);
			अगर (ret < 0)
				soc_component_ret(component, ret);
		पूर्ण

		/* हटाओ marked substream */
		soc_component_mark_pop(component, substream, hw_params);
	पूर्ण
पूर्ण

अटल पूर्णांक soc_component_trigger(काष्ठा snd_soc_component *component,
				 काष्ठा snd_pcm_substream *substream,
				 पूर्णांक cmd)
अणु
	पूर्णांक ret = 0;

	अगर (component->driver->trigger)
		ret = component->driver->trigger(component, substream, cmd);

	वापस soc_component_ret(component, ret);
पूर्ण

पूर्णांक snd_soc_pcm_component_trigger(काष्ठा snd_pcm_substream *substream,
				  पूर्णांक cmd, पूर्णांक rollback)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component;
	पूर्णांक i, r, ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		क्रम_each_rtd_components(rtd, i, component) अणु
			ret = soc_component_trigger(component, substream, cmd);
			अगर (ret < 0)
				अवरोध;
			soc_component_mark_push(component, substream, trigger);
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		क्रम_each_rtd_components(rtd, i, component) अणु
			अगर (rollback && !soc_component_mark_match(component, substream, trigger))
				जारी;

			r = soc_component_trigger(component, substream, cmd);
			अगर (r < 0)
				ret = r; /* use last ret */
			soc_component_mark_pop(component, substream, trigger);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक snd_soc_pcm_component_pm_runसमय_get(काष्ठा snd_soc_pcm_runसमय *rtd,
					 व्योम *stream)
अणु
	काष्ठा snd_soc_component *component;
	पूर्णांक i, ret;

	क्रम_each_rtd_components(rtd, i, component) अणु
		ret = pm_runसमय_get_sync(component->dev);
		अगर (ret < 0 && ret != -EACCES) अणु
			pm_runसमय_put_noidle(component->dev);
			वापस soc_component_ret(component, ret);
		पूर्ण
		/* mark stream अगर succeeded */
		soc_component_mark_push(component, stream, pm);
	पूर्ण

	वापस 0;
पूर्ण

व्योम snd_soc_pcm_component_pm_runसमय_put(काष्ठा snd_soc_pcm_runसमय *rtd,
					  व्योम *stream, पूर्णांक rollback)
अणु
	काष्ठा snd_soc_component *component;
	पूर्णांक i;

	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (rollback && !soc_component_mark_match(component, stream, pm))
			जारी;

		pm_runसमय_mark_last_busy(component->dev);
		pm_runसमय_put_स्वतःsuspend(component->dev);

		/* हटाओ marked stream */
		soc_component_mark_pop(component, stream, pm);
	पूर्ण
पूर्ण

पूर्णांक snd_soc_pcm_component_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component;
	पूर्णांक i;

	/* FIXME: use 1st poपूर्णांकer */
	क्रम_each_rtd_components(rtd, i, component)
		अगर (component->driver->ack)
			वापस component->driver->ack(component, substream);

	वापस 0;
पूर्ण
