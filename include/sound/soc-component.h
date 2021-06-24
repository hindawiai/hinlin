<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * soc-component.h
 *
 * Copyright (C) 2019 Renesas Electronics Corp.
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */
#अगर_अघोषित __SOC_COMPONENT_H
#घोषणा __SOC_COMPONENT_H

#समावेश <sound/soc.h>

/*
 * Component probe and हटाओ ordering levels क्रम components with runसमय
 * dependencies.
 */
#घोषणा SND_SOC_COMP_ORDER_FIRST	-2
#घोषणा SND_SOC_COMP_ORDER_EARLY	-1
#घोषणा SND_SOC_COMP_ORDER_NORMAL	 0
#घोषणा SND_SOC_COMP_ORDER_LATE		 1
#घोषणा SND_SOC_COMP_ORDER_LAST		 2

#घोषणा क्रम_each_comp_order(order)		\
	क्रम (order  = SND_SOC_COMP_ORDER_FIRST;	\
	     order <= SND_SOC_COMP_ORDER_LAST;	\
	     order++)

/* component पूर्णांकerface */
काष्ठा snd_compress_ops अणु
	पूर्णांक (*खोलो)(काष्ठा snd_soc_component *component,
		    काष्ठा snd_compr_stream *stream);
	पूर्णांक (*मुक्त)(काष्ठा snd_soc_component *component,
		    काष्ठा snd_compr_stream *stream);
	पूर्णांक (*set_params)(काष्ठा snd_soc_component *component,
			  काष्ठा snd_compr_stream *stream,
			  काष्ठा snd_compr_params *params);
	पूर्णांक (*get_params)(काष्ठा snd_soc_component *component,
			  काष्ठा snd_compr_stream *stream,
			  काष्ठा snd_codec *params);
	पूर्णांक (*set_metadata)(काष्ठा snd_soc_component *component,
			    काष्ठा snd_compr_stream *stream,
			    काष्ठा snd_compr_metadata *metadata);
	पूर्णांक (*get_metadata)(काष्ठा snd_soc_component *component,
			    काष्ठा snd_compr_stream *stream,
			    काष्ठा snd_compr_metadata *metadata);
	पूर्णांक (*trigger)(काष्ठा snd_soc_component *component,
		       काष्ठा snd_compr_stream *stream, पूर्णांक cmd);
	पूर्णांक (*poपूर्णांकer)(काष्ठा snd_soc_component *component,
		       काष्ठा snd_compr_stream *stream,
		       काष्ठा snd_compr_tstamp *tstamp);
	पूर्णांक (*copy)(काष्ठा snd_soc_component *component,
		    काष्ठा snd_compr_stream *stream, अक्षर __user *buf,
		    माप_प्रकार count);
	पूर्णांक (*mmap)(काष्ठा snd_soc_component *component,
		    काष्ठा snd_compr_stream *stream,
		    काष्ठा vm_area_काष्ठा *vma);
	पूर्णांक (*ack)(काष्ठा snd_soc_component *component,
		   काष्ठा snd_compr_stream *stream, माप_प्रकार bytes);
	पूर्णांक (*get_caps)(काष्ठा snd_soc_component *component,
			काष्ठा snd_compr_stream *stream,
			काष्ठा snd_compr_caps *caps);
	पूर्णांक (*get_codec_caps)(काष्ठा snd_soc_component *component,
			      काष्ठा snd_compr_stream *stream,
			      काष्ठा snd_compr_codec_caps *codec);
पूर्ण;

काष्ठा snd_soc_component_driver अणु
	स्थिर अक्षर *name;

	/* Default control and setup, added after probe() is run */
	स्थिर काष्ठा snd_kcontrol_new *controls;
	अचिन्हित पूर्णांक num_controls;
	स्थिर काष्ठा snd_soc_dapm_widget *dapm_widमाला_लो;
	अचिन्हित पूर्णांक num_dapm_widमाला_लो;
	स्थिर काष्ठा snd_soc_dapm_route *dapm_routes;
	अचिन्हित पूर्णांक num_dapm_routes;

	पूर्णांक (*probe)(काष्ठा snd_soc_component *component);
	व्योम (*हटाओ)(काष्ठा snd_soc_component *component);
	पूर्णांक (*suspend)(काष्ठा snd_soc_component *component);
	पूर्णांक (*resume)(काष्ठा snd_soc_component *component);

	अचिन्हित पूर्णांक (*पढ़ो)(काष्ठा snd_soc_component *component,
			     अचिन्हित पूर्णांक reg);
	पूर्णांक (*ग_लिखो)(काष्ठा snd_soc_component *component,
		     अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val);

	/* pcm creation and deकाष्ठाion */
	पूर्णांक (*pcm_स्थिरruct)(काष्ठा snd_soc_component *component,
			     काष्ठा snd_soc_pcm_runसमय *rtd);
	व्योम (*pcm_deकाष्ठा)(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm *pcm);

	/* component wide operations */
	पूर्णांक (*set_sysclk)(काष्ठा snd_soc_component *component,
			  पूर्णांक clk_id, पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir);
	पूर्णांक (*set_pll)(काष्ठा snd_soc_component *component, पूर्णांक pll_id,
		       पूर्णांक source, अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out);
	पूर्णांक (*set_jack)(काष्ठा snd_soc_component *component,
			काष्ठा snd_soc_jack *jack,  व्योम *data);

	/* DT */
	पूर्णांक (*of_xlate_dai_name)(काष्ठा snd_soc_component *component,
				 स्थिर काष्ठा of_phandle_args *args,
				 स्थिर अक्षर **dai_name);
	पूर्णांक (*of_xlate_dai_id)(काष्ठा snd_soc_component *comment,
			       काष्ठा device_node *endpoपूर्णांक);
	व्योम (*seq_notअगरier)(काष्ठा snd_soc_component *component,
			     क्रमागत snd_soc_dapm_type type, पूर्णांक subseq);
	पूर्णांक (*stream_event)(काष्ठा snd_soc_component *component, पूर्णांक event);
	पूर्णांक (*set_bias_level)(काष्ठा snd_soc_component *component,
			      क्रमागत snd_soc_bias_level level);

	पूर्णांक (*खोलो)(काष्ठा snd_soc_component *component,
		    काष्ठा snd_pcm_substream *substream);
	पूर्णांक (*बंद)(काष्ठा snd_soc_component *component,
		     काष्ठा snd_pcm_substream *substream);
	पूर्णांक (*ioctl)(काष्ठा snd_soc_component *component,
		     काष्ठा snd_pcm_substream *substream,
		     अचिन्हित पूर्णांक cmd, व्योम *arg);
	पूर्णांक (*hw_params)(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_pcm_hw_params *params);
	पूर्णांक (*hw_मुक्त)(काष्ठा snd_soc_component *component,
		       काष्ठा snd_pcm_substream *substream);
	पूर्णांक (*prepare)(काष्ठा snd_soc_component *component,
		       काष्ठा snd_pcm_substream *substream);
	पूर्णांक (*trigger)(काष्ठा snd_soc_component *component,
		       काष्ठा snd_pcm_substream *substream, पूर्णांक cmd);
	पूर्णांक (*sync_stop)(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm_substream *substream);
	snd_pcm_uframes_t (*poपूर्णांकer)(काष्ठा snd_soc_component *component,
				     काष्ठा snd_pcm_substream *substream);
	पूर्णांक (*get_समय_info)(काष्ठा snd_soc_component *component,
		काष्ठा snd_pcm_substream *substream, काष्ठा बारpec64 *प्रणाली_ts,
		काष्ठा बारpec64 *audio_ts,
		काष्ठा snd_pcm_audio_tstamp_config *audio_tstamp_config,
		काष्ठा snd_pcm_audio_tstamp_report *audio_tstamp_report);
	पूर्णांक (*copy_user)(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm_substream *substream, पूर्णांक channel,
			 अचिन्हित दीर्घ pos, व्योम __user *buf,
			 अचिन्हित दीर्घ bytes);
	काष्ठा page *(*page)(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream,
			     अचिन्हित दीर्घ offset);
	पूर्णांक (*mmap)(काष्ठा snd_soc_component *component,
		    काष्ठा snd_pcm_substream *substream,
		    काष्ठा vm_area_काष्ठा *vma);
	पूर्णांक (*ack)(काष्ठा snd_soc_component *component,
		   काष्ठा snd_pcm_substream *substream);

	स्थिर काष्ठा snd_compress_ops *compress_ops;

	/* probe ordering - क्रम components with runसमय dependencies */
	पूर्णांक probe_order;
	पूर्णांक हटाओ_order;

	/*
	 * संकेत अगर the module handling the component should not be हटाओd
	 * अगर a pcm is खोलो. Setting this would prevent the module
	 * refcount being incremented in probe() but allow it be incremented
	 * when a pcm is खोलोed and decremented when it is बंदd.
	 */
	अचिन्हित पूर्णांक module_get_upon_खोलो:1;

	/* bits */
	अचिन्हित पूर्णांक idle_bias_on:1;
	अचिन्हित पूर्णांक suspend_bias_off:1;
	अचिन्हित पूर्णांक use_pmकरोwn_समय:1; /* care pmकरोwn_समय at stop */
	अचिन्हित पूर्णांक endianness:1;
	अचिन्हित पूर्णांक non_legacy_dai_naming:1;

	/* this component uses topology and ignore machine driver FEs */
	स्थिर अक्षर *ignore_machine;
	स्थिर अक्षर *topology_name_prefix;
	पूर्णांक (*be_hw_params_fixup)(काष्ठा snd_soc_pcm_runसमय *rtd,
				  काष्ठा snd_pcm_hw_params *params);
	bool use_dai_pcm_id;	/* use DAI link PCM ID as PCM device number */
	पूर्णांक be_pcm_base;	/* base device ID क्रम all BE PCMs */
पूर्ण;

काष्ठा snd_soc_component अणु
	स्थिर अक्षर *name;
	पूर्णांक id;
	स्थिर अक्षर *name_prefix;
	काष्ठा device *dev;
	काष्ठा snd_soc_card *card;

	अचिन्हित पूर्णांक active;

	अचिन्हित पूर्णांक suspended:1; /* is in suspend PM state */

	काष्ठा list_head list;
	काष्ठा list_head card_aux_list; /* क्रम auxiliary bound components */
	काष्ठा list_head card_list;

	स्थिर काष्ठा snd_soc_component_driver *driver;

	काष्ठा list_head dai_list;
	पूर्णांक num_dai;

	काष्ठा regmap *regmap;
	पूर्णांक val_bytes;

	काष्ठा mutex io_mutex;

	/* attached dynamic objects */
	काष्ठा list_head करोbj_list;

	/*
	 * DO NOT use any of the fields below in drivers, they are temporary and
	 * are going to be हटाओd again soon. If you use them in driver code
	 * the driver will be marked as BROKEN when these fields are हटाओd.
	 */

	/* Don't use these, use snd_soc_component_get_dapm() */
	काष्ठा snd_soc_dapm_context dapm;

	/* machine specअगरic init */
	पूर्णांक (*init)(काष्ठा snd_soc_component *component);

	/* function mark */
	काष्ठा snd_pcm_substream *mark_module;
	काष्ठा snd_pcm_substream *mark_खोलो;
	काष्ठा snd_pcm_substream *mark_hw_params;
	काष्ठा snd_pcm_substream *mark_trigger;
	काष्ठा snd_compr_stream  *mark_compr_खोलो;
	व्योम *mark_pm;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs_root;
	स्थिर अक्षर *debugfs_prefix;
#पूर्ण_अगर
पूर्ण;

#घोषणा क्रम_each_component_dais(component, dai)\
	list_क्रम_each_entry(dai, &(component)->dai_list, list)
#घोषणा क्रम_each_component_dais_safe(component, dai, _dai)\
	list_क्रम_each_entry_safe(dai, _dai, &(component)->dai_list, list)

/**
 * snd_soc_dapm_to_component() - Casts a DAPM context to the component it is
 *  embedded in
 * @dapm: The DAPM context to cast to the component
 *
 * This function must only be used on DAPM contexts that are known to be part of
 * a component (e.g. in a component driver). Otherwise the behavior is
 * undefined.
 */
अटल अंतरभूत काष्ठा snd_soc_component *snd_soc_dapm_to_component(
	काष्ठा snd_soc_dapm_context *dapm)
अणु
	वापस container_of(dapm, काष्ठा snd_soc_component, dapm);
पूर्ण

/**
 * snd_soc_component_get_dapm() - Returns the DAPM context associated with a
 *  component
 * @component: The component क्रम which to get the DAPM context
 */
अटल अंतरभूत काष्ठा snd_soc_dapm_context *snd_soc_component_get_dapm(
	काष्ठा snd_soc_component *component)
अणु
	वापस &component->dapm;
पूर्ण

/**
 * snd_soc_component_init_bias_level() - Initialize COMPONENT DAPM bias level
 * @component: The COMPONENT क्रम which to initialize the DAPM bias level
 * @level: The DAPM level to initialize to
 *
 * Initializes the COMPONENT DAPM bias level. See snd_soc_dapm_init_bias_level()
 */
अटल अंतरभूत व्योम
snd_soc_component_init_bias_level(काष्ठा snd_soc_component *component,
				  क्रमागत snd_soc_bias_level level)
अणु
	snd_soc_dapm_init_bias_level(
		snd_soc_component_get_dapm(component), level);
पूर्ण

/**
 * snd_soc_component_get_bias_level() - Get current COMPONENT DAPM bias level
 * @component: The COMPONENT क्रम which to get the DAPM bias level
 *
 * Returns: The current DAPM bias level of the COMPONENT.
 */
अटल अंतरभूत क्रमागत snd_soc_bias_level
snd_soc_component_get_bias_level(काष्ठा snd_soc_component *component)
अणु
	वापस snd_soc_dapm_get_bias_level(
		snd_soc_component_get_dapm(component));
पूर्ण

/**
 * snd_soc_component_क्रमce_bias_level() - Set the COMPONENT DAPM bias level
 * @component: The COMPONENT क्रम which to set the level
 * @level: The level to set to
 *
 * Forces the COMPONENT bias level to a specअगरic state. See
 * snd_soc_dapm_क्रमce_bias_level().
 */
अटल अंतरभूत पूर्णांक
snd_soc_component_क्रमce_bias_level(काष्ठा snd_soc_component *component,
				   क्रमागत snd_soc_bias_level level)
अणु
	वापस snd_soc_dapm_क्रमce_bias_level(
		snd_soc_component_get_dapm(component),
		level);
पूर्ण

/**
 * snd_soc_dapm_kcontrol_component() - Returns the component associated to a
 * kcontrol
 * @kcontrol: The kcontrol
 *
 * This function must only be used on DAPM contexts that are known to be part of
 * a COMPONENT (e.g. in a COMPONENT driver). Otherwise the behavior is undefined
 */
अटल अंतरभूत काष्ठा snd_soc_component *snd_soc_dapm_kcontrol_component(
	काष्ठा snd_kcontrol *kcontrol)
अणु
	वापस snd_soc_dapm_to_component(snd_soc_dapm_kcontrol_dapm(kcontrol));
पूर्ण

/**
 * snd_soc_component_cache_sync() - Sync the रेजिस्टर cache with the hardware
 * @component: COMPONENT to sync
 *
 * Note: This function will call regcache_sync()
 */
अटल अंतरभूत पूर्णांक snd_soc_component_cache_sync(
	काष्ठा snd_soc_component *component)
अणु
	वापस regcache_sync(component->regmap);
पूर्ण

व्योम snd_soc_component_set_aux(काष्ठा snd_soc_component *component,
			       काष्ठा snd_soc_aux_dev *aux);
पूर्णांक snd_soc_component_init(काष्ठा snd_soc_component *component);
पूर्णांक snd_soc_component_is_dummy(काष्ठा snd_soc_component *component);

/* component IO */
अचिन्हित पूर्णांक snd_soc_component_पढ़ो(काष्ठा snd_soc_component *component,
				      अचिन्हित पूर्णांक reg);
पूर्णांक snd_soc_component_ग_लिखो(काष्ठा snd_soc_component *component,
			    अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val);
पूर्णांक snd_soc_component_update_bits(काष्ठा snd_soc_component *component,
				  अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mask,
				  अचिन्हित पूर्णांक val);
पूर्णांक snd_soc_component_update_bits_async(काष्ठा snd_soc_component *component,
					अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mask,
					अचिन्हित पूर्णांक val);
व्योम snd_soc_component_async_complete(काष्ठा snd_soc_component *component);
पूर्णांक snd_soc_component_test_bits(काष्ठा snd_soc_component *component,
				अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mask,
				अचिन्हित पूर्णांक value);

अचिन्हित पूर्णांक snd_soc_component_पढ़ो_field(काष्ठा snd_soc_component *component,
					  अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mask);
पूर्णांक snd_soc_component_ग_लिखो_field(काष्ठा snd_soc_component *component,
				  अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mask,
				  अचिन्हित पूर्णांक val);

/* component wide operations */
पूर्णांक snd_soc_component_set_sysclk(काष्ठा snd_soc_component *component,
				 पूर्णांक clk_id, पूर्णांक source,
				 अचिन्हित पूर्णांक freq, पूर्णांक dir);
पूर्णांक snd_soc_component_set_pll(काष्ठा snd_soc_component *component, पूर्णांक pll_id,
			      पूर्णांक source, अचिन्हित पूर्णांक freq_in,
			      अचिन्हित पूर्णांक freq_out);
पूर्णांक snd_soc_component_set_jack(काष्ठा snd_soc_component *component,
			       काष्ठा snd_soc_jack *jack, व्योम *data);

व्योम snd_soc_component_seq_notअगरier(काष्ठा snd_soc_component *component,
				    क्रमागत snd_soc_dapm_type type, पूर्णांक subseq);
पूर्णांक snd_soc_component_stream_event(काष्ठा snd_soc_component *component,
				   पूर्णांक event);
पूर्णांक snd_soc_component_set_bias_level(काष्ठा snd_soc_component *component,
				     क्रमागत snd_soc_bias_level level);

व्योम snd_soc_component_setup_regmap(काष्ठा snd_soc_component *component);
#अगर_घोषित CONFIG_REGMAP
व्योम snd_soc_component_init_regmap(काष्ठा snd_soc_component *component,
				   काष्ठा regmap *regmap);
व्योम snd_soc_component_निकास_regmap(काष्ठा snd_soc_component *component);
#पूर्ण_अगर

#घोषणा snd_soc_component_module_get_when_probe(component)\
	snd_soc_component_module_get(component, शून्य, 0)
#घोषणा snd_soc_component_module_get_when_खोलो(component, substream)	\
	snd_soc_component_module_get(component, substream, 1)
पूर्णांक snd_soc_component_module_get(काष्ठा snd_soc_component *component,
				 काष्ठा snd_pcm_substream *substream,
				 पूर्णांक upon_खोलो);
#घोषणा snd_soc_component_module_put_when_हटाओ(component)	\
	snd_soc_component_module_put(component, शून्य, 0, 0)
#घोषणा snd_soc_component_module_put_when_बंद(component, substream, rollback) \
	snd_soc_component_module_put(component, substream, 1, rollback)
व्योम snd_soc_component_module_put(काष्ठा snd_soc_component *component,
				  काष्ठा snd_pcm_substream *substream,
				  पूर्णांक upon_खोलो, पूर्णांक rollback);

अटल अंतरभूत व्योम snd_soc_component_set_drvdata(काष्ठा snd_soc_component *c,
						 व्योम *data)
अणु
	dev_set_drvdata(c->dev, data);
पूर्ण

अटल अंतरभूत व्योम *snd_soc_component_get_drvdata(काष्ठा snd_soc_component *c)
अणु
	वापस dev_get_drvdata(c->dev);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
snd_soc_component_active(काष्ठा snd_soc_component *component)
अणु
	वापस component->active;
पूर्ण

/* component pin */
पूर्णांक snd_soc_component_enable_pin(काष्ठा snd_soc_component *component,
				 स्थिर अक्षर *pin);
पूर्णांक snd_soc_component_enable_pin_unlocked(काष्ठा snd_soc_component *component,
					  स्थिर अक्षर *pin);
पूर्णांक snd_soc_component_disable_pin(काष्ठा snd_soc_component *component,
				  स्थिर अक्षर *pin);
पूर्णांक snd_soc_component_disable_pin_unlocked(काष्ठा snd_soc_component *component,
					   स्थिर अक्षर *pin);
पूर्णांक snd_soc_component_nc_pin(काष्ठा snd_soc_component *component,
			     स्थिर अक्षर *pin);
पूर्णांक snd_soc_component_nc_pin_unlocked(काष्ठा snd_soc_component *component,
				      स्थिर अक्षर *pin);
पूर्णांक snd_soc_component_get_pin_status(काष्ठा snd_soc_component *component,
				     स्थिर अक्षर *pin);
पूर्णांक snd_soc_component_क्रमce_enable_pin(काष्ठा snd_soc_component *component,
				       स्थिर अक्षर *pin);
पूर्णांक snd_soc_component_क्रमce_enable_pin_unlocked(
	काष्ठा snd_soc_component *component,
	स्थिर अक्षर *pin);

/* component driver ops */
पूर्णांक snd_soc_component_खोलो(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream);
पूर्णांक snd_soc_component_बंद(काष्ठा snd_soc_component *component,
			    काष्ठा snd_pcm_substream *substream,
			    पूर्णांक rollback);
व्योम snd_soc_component_suspend(काष्ठा snd_soc_component *component);
व्योम snd_soc_component_resume(काष्ठा snd_soc_component *component);
पूर्णांक snd_soc_component_is_suspended(काष्ठा snd_soc_component *component);
पूर्णांक snd_soc_component_probe(काष्ठा snd_soc_component *component);
व्योम snd_soc_component_हटाओ(काष्ठा snd_soc_component *component);
पूर्णांक snd_soc_component_of_xlate_dai_id(काष्ठा snd_soc_component *component,
				      काष्ठा device_node *ep);
पूर्णांक snd_soc_component_of_xlate_dai_name(काष्ठा snd_soc_component *component,
					स्थिर काष्ठा of_phandle_args *args,
					स्थिर अक्षर **dai_name);
पूर्णांक snd_soc_component_compr_खोलो(काष्ठा snd_compr_stream *cstream);
व्योम snd_soc_component_compr_मुक्त(काष्ठा snd_compr_stream *cstream,
				  पूर्णांक rollback);
पूर्णांक snd_soc_component_compr_trigger(काष्ठा snd_compr_stream *cstream, पूर्णांक cmd);
पूर्णांक snd_soc_component_compr_set_params(काष्ठा snd_compr_stream *cstream,
				       काष्ठा snd_compr_params *params);
पूर्णांक snd_soc_component_compr_get_params(काष्ठा snd_compr_stream *cstream,
				       काष्ठा snd_codec *params);
पूर्णांक snd_soc_component_compr_get_caps(काष्ठा snd_compr_stream *cstream,
				     काष्ठा snd_compr_caps *caps);
पूर्णांक snd_soc_component_compr_get_codec_caps(काष्ठा snd_compr_stream *cstream,
					   काष्ठा snd_compr_codec_caps *codec);
पूर्णांक snd_soc_component_compr_ack(काष्ठा snd_compr_stream *cstream, माप_प्रकार bytes);
पूर्णांक snd_soc_component_compr_poपूर्णांकer(काष्ठा snd_compr_stream *cstream,
				    काष्ठा snd_compr_tstamp *tstamp);
पूर्णांक snd_soc_component_compr_copy(काष्ठा snd_compr_stream *cstream,
				 अक्षर __user *buf, माप_प्रकार count);
पूर्णांक snd_soc_component_compr_set_metadata(काष्ठा snd_compr_stream *cstream,
					 काष्ठा snd_compr_metadata *metadata);
पूर्णांक snd_soc_component_compr_get_metadata(काष्ठा snd_compr_stream *cstream,
					 काष्ठा snd_compr_metadata *metadata);

पूर्णांक snd_soc_pcm_component_poपूर्णांकer(काष्ठा snd_pcm_substream *substream);
पूर्णांक snd_soc_pcm_component_ioctl(काष्ठा snd_pcm_substream *substream,
				अचिन्हित पूर्णांक cmd, व्योम *arg);
पूर्णांक snd_soc_pcm_component_sync_stop(काष्ठा snd_pcm_substream *substream);
पूर्णांक snd_soc_pcm_component_copy_user(काष्ठा snd_pcm_substream *substream,
				    पूर्णांक channel, अचिन्हित दीर्घ pos,
				    व्योम __user *buf, अचिन्हित दीर्घ bytes);
काष्ठा page *snd_soc_pcm_component_page(काष्ठा snd_pcm_substream *substream,
					अचिन्हित दीर्घ offset);
पूर्णांक snd_soc_pcm_component_mmap(काष्ठा snd_pcm_substream *substream,
			       काष्ठा vm_area_काष्ठा *vma);
पूर्णांक snd_soc_pcm_component_new(काष्ठा snd_soc_pcm_runसमय *rtd);
व्योम snd_soc_pcm_component_मुक्त(काष्ठा snd_soc_pcm_runसमय *rtd);
पूर्णांक snd_soc_pcm_component_prepare(काष्ठा snd_pcm_substream *substream);
पूर्णांक snd_soc_pcm_component_hw_params(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_hw_params *params);
व्योम snd_soc_pcm_component_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
				   पूर्णांक rollback);
पूर्णांक snd_soc_pcm_component_trigger(काष्ठा snd_pcm_substream *substream,
				  पूर्णांक cmd, पूर्णांक rollback);
पूर्णांक snd_soc_pcm_component_pm_runसमय_get(काष्ठा snd_soc_pcm_runसमय *rtd,
					 व्योम *stream);
व्योम snd_soc_pcm_component_pm_runसमय_put(काष्ठा snd_soc_pcm_runसमय *rtd,
					  व्योम *stream, पूर्णांक rollback);
पूर्णांक snd_soc_pcm_component_ack(काष्ठा snd_pcm_substream *substream);

#पूर्ण_अगर /* __SOC_COMPONENT_H */
