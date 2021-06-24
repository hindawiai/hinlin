<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// soc-pcm.c  --  ALSA SoC PCM
//
// Copyright 2005 Wolfson Microelectronics PLC.
// Copyright 2005 Openedhand Ltd.
// Copyright (C) 2010 Slimlogic Ltd.
// Copyright (C) 2010 Texas Instruments Inc.
//
// Authors: Liam Girdwood <lrg@ti.com>
//          Mark Brown <broonie@खोलोsource.wolfsonmicro.com>

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/export.h>
#समावेश <linux/debugfs.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dpcm.h>
#समावेश <sound/soc-link.h>
#समावेश <sound/initval.h>

#घोषणा DPCM_MAX_BE_USERS	8

अटल अंतरभूत स्थिर अक्षर *soc_cpu_dai_name(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	वापस (rtd)->num_cpus == 1 ? asoc_rtd_to_cpu(rtd, 0)->name : "multicpu";
पूर्ण
अटल अंतरभूत स्थिर अक्षर *soc_codec_dai_name(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	वापस (rtd)->num_codecs == 1 ? asoc_rtd_to_codec(rtd, 0)->name : "multicodec";
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल स्थिर अक्षर *dpcm_state_string(क्रमागत snd_soc_dpcm_state state)
अणु
	चयन (state) अणु
	हाल SND_SOC_DPCM_STATE_NEW:
		वापस "new";
	हाल SND_SOC_DPCM_STATE_OPEN:
		वापस "open";
	हाल SND_SOC_DPCM_STATE_HW_PARAMS:
		वापस "hw_params";
	हाल SND_SOC_DPCM_STATE_PREPARE:
		वापस "prepare";
	हाल SND_SOC_DPCM_STATE_START:
		वापस "start";
	हाल SND_SOC_DPCM_STATE_STOP:
		वापस "stop";
	हाल SND_SOC_DPCM_STATE_SUSPEND:
		वापस "suspend";
	हाल SND_SOC_DPCM_STATE_PAUSED:
		वापस "paused";
	हाल SND_SOC_DPCM_STATE_HW_FREE:
		वापस "hw_free";
	हाल SND_SOC_DPCM_STATE_CLOSE:
		वापस "close";
	पूर्ण

	वापस "unknown";
पूर्ण

अटल sमाप_प्रकार dpcm_show_state(काष्ठा snd_soc_pcm_runसमय *fe,
			       पूर्णांक stream, अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा snd_pcm_hw_params *params = &fe->dpcm[stream].hw_params;
	काष्ठा snd_soc_dpcm *dpcm;
	sमाप_प्रकार offset = 0;
	अचिन्हित दीर्घ flags;

	/* FE state */
	offset += scnम_लिखो(buf + offset, size - offset,
			   "[%s - %s]\n", fe->dai_link->name,
			   stream ? "Capture" : "Playback");

	offset += scnम_लिखो(buf + offset, size - offset, "State: %s\n",
			   dpcm_state_string(fe->dpcm[stream].state));

	अगर ((fe->dpcm[stream].state >= SND_SOC_DPCM_STATE_HW_PARAMS) &&
	    (fe->dpcm[stream].state <= SND_SOC_DPCM_STATE_STOP))
		offset += scnम_लिखो(buf + offset, size - offset,
				   "Hardware Params: "
				   "Format = %s, Channels = %d, Rate = %d\n",
				   snd_pcm_क्रमmat_name(params_क्रमmat(params)),
				   params_channels(params),
				   params_rate(params));

	/* BEs state */
	offset += scnम_लिखो(buf + offset, size - offset, "Backends:\n");

	अगर (list_empty(&fe->dpcm[stream].be_clients)) अणु
		offset += scnम_लिखो(buf + offset, size - offset,
				   " No active DSP links\n");
		जाओ out;
	पूर्ण

	spin_lock_irqsave(&fe->card->dpcm_lock, flags);
	क्रम_each_dpcm_be(fe, stream, dpcm) अणु
		काष्ठा snd_soc_pcm_runसमय *be = dpcm->be;
		params = &dpcm->hw_params;

		offset += scnम_लिखो(buf + offset, size - offset,
				   "- %s\n", be->dai_link->name);

		offset += scnम_लिखो(buf + offset, size - offset,
				   "   State: %s\n",
				   dpcm_state_string(be->dpcm[stream].state));

		अगर ((be->dpcm[stream].state >= SND_SOC_DPCM_STATE_HW_PARAMS) &&
		    (be->dpcm[stream].state <= SND_SOC_DPCM_STATE_STOP))
			offset += scnम_लिखो(buf + offset, size - offset,
					   "   Hardware Params: "
					   "Format = %s, Channels = %d, Rate = %d\n",
					   snd_pcm_क्रमmat_name(params_क्रमmat(params)),
					   params_channels(params),
					   params_rate(params));
	पूर्ण
	spin_unlock_irqrestore(&fe->card->dpcm_lock, flags);
out:
	वापस offset;
पूर्ण

अटल sमाप_प्रकार dpcm_state_पढ़ो_file(काष्ठा file *file, अक्षर __user *user_buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा snd_soc_pcm_runसमय *fe = file->निजी_data;
	sमाप_प्रकार out_count = PAGE_SIZE, offset = 0, ret = 0;
	पूर्णांक stream;
	अक्षर *buf;

	अगर (fe->num_cpus > 1) अणु
		dev_err(fe->dev,
			"%s doesn't support Multi CPU yet\n", __func__);
		वापस -EINVAL;
	पूर्ण

	buf = kदो_स्मृति(out_count, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	क्रम_each_pcm_streams(stream)
		अगर (snd_soc_dai_stream_valid(asoc_rtd_to_cpu(fe, 0), stream))
			offset += dpcm_show_state(fe, stream,
						  buf + offset,
						  out_count - offset);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, offset);

	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations dpcm_state_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = dpcm_state_पढ़ो_file,
	.llseek = शेष_llseek,
पूर्ण;

व्योम soc_dpcm_debugfs_add(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	अगर (!rtd->dai_link->dynamic)
		वापस;

	अगर (!rtd->card->debugfs_card_root)
		वापस;

	rtd->debugfs_dpcm_root = debugfs_create_dir(rtd->dai_link->name,
						    rtd->card->debugfs_card_root);

	debugfs_create_file("state", 0444, rtd->debugfs_dpcm_root,
			    rtd, &dpcm_state_fops);
पूर्ण

अटल व्योम dpcm_create_debugfs_state(काष्ठा snd_soc_dpcm *dpcm, पूर्णांक stream)
अणु
	अक्षर *name;

	name = kaप्र_लिखो(GFP_KERNEL, "%s:%s", dpcm->be->dai_link->name,
			 stream ? "capture" : "playback");
	अगर (name) अणु
		dpcm->debugfs_state = debugfs_create_dir(
			name, dpcm->fe->debugfs_dpcm_root);
		debugfs_create_u32("state", 0644, dpcm->debugfs_state,
				   &dpcm->state);
		kमुक्त(name);
	पूर्ण
पूर्ण

अटल व्योम dpcm_हटाओ_debugfs_state(काष्ठा snd_soc_dpcm *dpcm)
अणु
	debugfs_हटाओ_recursive(dpcm->debugfs_state);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम dpcm_create_debugfs_state(काष्ठा snd_soc_dpcm *dpcm,
					     पूर्णांक stream)
अणु
पूर्ण

अटल अंतरभूत व्योम dpcm_हटाओ_debugfs_state(काष्ठा snd_soc_dpcm *dpcm)
अणु
पूर्ण
#पूर्ण_अगर

/* Set FE's runसमय_update state; the state is रक्षित via PCM stream lock
 * क्रम aव्योमing the race with trigger callback.
 * If the state is unset and a trigger is pending जबतक the previous operation,
 * process the pending trigger action here.
 */
अटल पूर्णांक dpcm_fe_dai_करो_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd);
अटल व्योम dpcm_set_fe_update_state(काष्ठा snd_soc_pcm_runसमय *fe,
				     पूर्णांक stream, क्रमागत snd_soc_dpcm_update state)
अणु
	काष्ठा snd_pcm_substream *substream =
		snd_soc_dpcm_get_substream(fe, stream);

	snd_pcm_stream_lock_irq(substream);
	अगर (state == SND_SOC_DPCM_UPDATE_NO && fe->dpcm[stream].trigger_pending) अणु
		dpcm_fe_dai_करो_trigger(substream,
				       fe->dpcm[stream].trigger_pending - 1);
		fe->dpcm[stream].trigger_pending = 0;
	पूर्ण
	fe->dpcm[stream].runसमय_update = state;
	snd_pcm_stream_unlock_irq(substream);
पूर्ण

अटल व्योम dpcm_set_be_update_state(काष्ठा snd_soc_pcm_runसमय *be,
				     पूर्णांक stream, क्रमागत snd_soc_dpcm_update state)
अणु
	be->dpcm[stream].runसमय_update = state;
पूर्ण

/**
 * snd_soc_runसमय_action() - Increment/Decrement active count क्रम
 * PCM runसमय components
 * @rtd: ASoC PCM runसमय that is activated
 * @stream: Direction of the PCM stream
 * @action: Activate stream अगर 1. Deactivate अगर -1.
 *
 * Increments/Decrements the active count क्रम all the DAIs and components
 * attached to a PCM runसमय.
 * Should typically be called when a stream is खोलोed.
 *
 * Must be called with the rtd->card->pcm_mutex being held
 */
व्योम snd_soc_runसमय_action(काष्ठा snd_soc_pcm_runसमय *rtd,
			    पूर्णांक stream, पूर्णांक action)
अणु
	काष्ठा snd_soc_dai *dai;
	पूर्णांक i;

	lockdep_निश्चित_held(&rtd->card->pcm_mutex);

	क्रम_each_rtd_dais(rtd, i, dai)
		snd_soc_dai_action(dai, stream, action);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_runसमय_action);

/**
 * snd_soc_runसमय_ignore_pmकरोwn_समय() - Check whether to ignore the घातer करोwn delay
 * @rtd: The ASoC PCM runसमय that should be checked.
 *
 * This function checks whether the घातer करोwn delay should be ignored क्रम a
 * specअगरic PCM runसमय. Returns true अगर the delay is 0, अगर it the DAI link has
 * been configured to ignore the delay, or अगर none of the components benefits
 * from having the delay.
 */
bool snd_soc_runसमय_ignore_pmकरोwn_समय(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *component;
	bool ignore = true;
	पूर्णांक i;

	अगर (!rtd->pmकरोwn_समय || rtd->dai_link->ignore_pmकरोwn_समय)
		वापस true;

	क्रम_each_rtd_components(rtd, i, component)
		ignore &= !component->driver->use_pmकरोwn_समय;

	वापस ignore;
पूर्ण

/**
 * snd_soc_set_runसमय_hwparams - set the runसमय hardware parameters
 * @substream: the pcm substream
 * @hw: the hardware parameters
 *
 * Sets the substream runसमय hardware parameters.
 */
पूर्णांक snd_soc_set_runसमय_hwparams(काष्ठा snd_pcm_substream *substream,
	स्थिर काष्ठा snd_pcm_hardware *hw)
अणु
	substream->runसमय->hw = *hw;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_set_runसमय_hwparams);

/* DPCM stream event, send event to FE and all active BEs. */
पूर्णांक dpcm_dapm_stream_event(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक dir,
	पूर्णांक event)
अणु
	काष्ठा snd_soc_dpcm *dpcm;

	क्रम_each_dpcm_be(fe, dir, dpcm) अणु

		काष्ठा snd_soc_pcm_runसमय *be = dpcm->be;

		dev_dbg(be->dev, "ASoC: BE %s event %d dir %d\n",
				be->dai_link->name, event, dir);

		अगर ((event == SND_SOC_DAPM_STREAM_STOP) &&
		    (be->dpcm[dir].users >= 1))
			जारी;

		snd_soc_dapm_stream_event(be, dir, event);
	पूर्ण

	snd_soc_dapm_stream_event(fe, dir, event);

	वापस 0;
पूर्ण

अटल व्योम soc_pcm_set_dai_params(काष्ठा snd_soc_dai *dai,
				   काष्ठा snd_pcm_hw_params *params)
अणु
	अगर (params) अणु
		dai->rate	 = params_rate(params);
		dai->channels	 = params_channels(params);
		dai->sample_bits = snd_pcm_क्रमmat_physical_width(params_क्रमmat(params));
	पूर्ण अन्यथा अणु
		dai->rate	 = 0;
		dai->channels	 = 0;
		dai->sample_bits = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक soc_pcm_apply_symmetry(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_soc_dai *soc_dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	पूर्णांक ret;

	अगर (!snd_soc_dai_active(soc_dai))
		वापस 0;

#घोषणा __soc_pcm_apply_symmetry(name, NAME)				\
	अगर (soc_dai->name && (soc_dai->driver->symmetric_##name ||	\
			      rtd->dai_link->symmetric_##name)) अणु	\
		dev_dbg(soc_dai->dev, "ASoC: Symmetry forces %s to %d\n",\
			#name, soc_dai->name);				\
									\
		ret = snd_pcm_hw_स्थिरraपूर्णांक_single(substream->runसमय,	\
						   SNDRV_PCM_HW_PARAM_##NAME,\
						   soc_dai->name);	\
		अगर (ret < 0) अणु						\
			dev_err(soc_dai->dev,				\
				"ASoC: Unable to apply %s constraint: %d\n",\
				#name, ret);				\
			वापस ret;					\
		पूर्ण							\
	पूर्ण

	__soc_pcm_apply_symmetry(rate,		RATE);
	__soc_pcm_apply_symmetry(channels,	CHANNELS);
	__soc_pcm_apply_symmetry(sample_bits,	SAMPLE_BITS);

	वापस 0;
पूर्ण

अटल पूर्णांक soc_pcm_params_symmetry(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai d;
	काष्ठा snd_soc_dai *dai;
	काष्ठा snd_soc_dai *cpu_dai;
	अचिन्हित पूर्णांक symmetry, i;

	d.name = __func__;
	soc_pcm_set_dai_params(&d, params);

#घोषणा __soc_pcm_params_symmetry(xxx)					\
	symmetry = rtd->dai_link->symmetric_##xxx;			\
	क्रम_each_rtd_dais(rtd, i, dai)					\
		symmetry |= dai->driver->symmetric_##xxx;		\
									\
	अगर (symmetry)							\
		क्रम_each_rtd_cpu_dais(rtd, i, cpu_dai)			\
			अगर (!snd_soc_dai_is_dummy(cpu_dai) &&		\
			    cpu_dai->xxx && cpu_dai->xxx != d.xxx) अणु	\
				dev_err(rtd->dev, "ASoC: unmatched %s symmetry: %s:%d - %s:%d\n", \
					#xxx, cpu_dai->name, cpu_dai->xxx, d.name, d.xxx); \
				वापस -EINVAL;				\
			पूर्ण

	/* reject unmatched parameters when applying symmetry */
	__soc_pcm_params_symmetry(rate);
	__soc_pcm_params_symmetry(channels);
	__soc_pcm_params_symmetry(sample_bits);

	वापस 0;
पूर्ण

अटल व्योम soc_pcm_update_symmetry(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai_link *link = rtd->dai_link;
	काष्ठा snd_soc_dai *dai;
	अचिन्हित पूर्णांक symmetry, i;

	symmetry = link->symmetric_rate ||
		link->symmetric_channels ||
		link->symmetric_sample_bits;

	क्रम_each_rtd_dais(rtd, i, dai)
		symmetry = symmetry ||
			dai->driver->symmetric_rate ||
			dai->driver->symmetric_channels ||
			dai->driver->symmetric_sample_bits;

	अगर (symmetry)
		substream->runसमय->hw.info |= SNDRV_PCM_INFO_JOINT_DUPLEX;
पूर्ण

अटल व्योम soc_pcm_set_msb(काष्ठा snd_pcm_substream *substream, पूर्णांक bits)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	पूर्णांक ret;

	अगर (!bits)
		वापस;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_msbits(substream->runसमय, 0, 0, bits);
	अगर (ret != 0)
		dev_warn(rtd->dev, "ASoC: Failed to set MSB %d: %d\n",
				 bits, ret);
पूर्ण

अटल व्योम soc_pcm_apply_msb(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai;
	काष्ठा snd_soc_dai *codec_dai;
	काष्ठा snd_soc_pcm_stream *pcm_codec, *pcm_cpu;
	पूर्णांक stream = substream->stream;
	पूर्णांक i;
	अचिन्हित पूर्णांक bits = 0, cpu_bits = 0;

	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
		pcm_codec = snd_soc_dai_get_pcm_stream(codec_dai, stream);

		अगर (pcm_codec->sig_bits == 0) अणु
			bits = 0;
			अवरोध;
		पूर्ण
		bits = max(pcm_codec->sig_bits, bits);
	पूर्ण

	क्रम_each_rtd_cpu_dais(rtd, i, cpu_dai) अणु
		pcm_cpu = snd_soc_dai_get_pcm_stream(cpu_dai, stream);

		अगर (pcm_cpu->sig_bits == 0) अणु
			cpu_bits = 0;
			अवरोध;
		पूर्ण
		cpu_bits = max(pcm_cpu->sig_bits, cpu_bits);
	पूर्ण

	soc_pcm_set_msb(substream, bits);
	soc_pcm_set_msb(substream, cpu_bits);
पूर्ण

अटल व्योम soc_pcm_hw_init(काष्ठा snd_pcm_hardware *hw)
अणु
	hw->rates		= अच_पूर्णांक_उच्च;
	hw->rate_min		= 0;
	hw->rate_max		= अच_पूर्णांक_उच्च;
	hw->channels_min	= 0;
	hw->channels_max	= अच_पूर्णांक_उच्च;
	hw->क्रमmats		= ULदीर्घ_उच्च;
पूर्ण

अटल व्योम soc_pcm_hw_update_rate(काष्ठा snd_pcm_hardware *hw,
				   काष्ठा snd_soc_pcm_stream *p)
अणु
	hw->rates = snd_pcm_rate_mask_पूर्णांकersect(hw->rates, p->rates);

	/* setup hw->rate_min/max via hw->rates first */
	snd_pcm_hw_limit_rates(hw);

	/* update hw->rate_min/max by snd_soc_pcm_stream */
	hw->rate_min = max(hw->rate_min, p->rate_min);
	hw->rate_max = min_not_zero(hw->rate_max, p->rate_max);
पूर्ण

अटल व्योम soc_pcm_hw_update_chan(काष्ठा snd_pcm_hardware *hw,
				   काष्ठा snd_soc_pcm_stream *p)
अणु
	hw->channels_min = max(hw->channels_min, p->channels_min);
	hw->channels_max = min(hw->channels_max, p->channels_max);
पूर्ण

अटल व्योम soc_pcm_hw_update_क्रमmat(काष्ठा snd_pcm_hardware *hw,
				     काष्ठा snd_soc_pcm_stream *p)
अणु
	hw->क्रमmats &= p->क्रमmats;
पूर्ण

/**
 * snd_soc_runसमय_calc_hw() - Calculate hw limits क्रम a PCM stream
 * @rtd: ASoC PCM runसमय
 * @hw: PCM hardware parameters (output)
 * @stream: Direction of the PCM stream
 *
 * Calculates the subset of stream parameters supported by all DAIs
 * associated with the PCM stream.
 */
पूर्णांक snd_soc_runसमय_calc_hw(काष्ठा snd_soc_pcm_runसमय *rtd,
			    काष्ठा snd_pcm_hardware *hw, पूर्णांक stream)
अणु
	काष्ठा snd_soc_dai *codec_dai;
	काष्ठा snd_soc_dai *cpu_dai;
	काष्ठा snd_soc_pcm_stream *codec_stream;
	काष्ठा snd_soc_pcm_stream *cpu_stream;
	अचिन्हित पूर्णांक cpu_chan_min = 0, cpu_chan_max = अच_पूर्णांक_उच्च;
	पूर्णांक i;

	soc_pcm_hw_init(hw);

	/* first calculate min/max only क्रम CPUs in the DAI link */
	क्रम_each_rtd_cpu_dais(rtd, i, cpu_dai) अणु

		/*
		 * Skip CPUs which करोn't support the current stream type.
		 * Otherwise, since the rate, channel, and क्रमmat values will
		 * zero in that हाल, we would have no usable settings left,
		 * causing the resulting setup to fail.
		 */
		अगर (!snd_soc_dai_stream_valid(cpu_dai, stream))
			जारी;

		cpu_stream = snd_soc_dai_get_pcm_stream(cpu_dai, stream);

		soc_pcm_hw_update_chan(hw, cpu_stream);
		soc_pcm_hw_update_rate(hw, cpu_stream);
		soc_pcm_hw_update_क्रमmat(hw, cpu_stream);
	पूर्ण
	cpu_chan_min = hw->channels_min;
	cpu_chan_max = hw->channels_max;

	/* second calculate min/max only क्रम CODECs in the DAI link */
	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु

		/*
		 * Skip CODECs which करोn't support the current stream type.
		 * Otherwise, since the rate, channel, and क्रमmat values will
		 * zero in that हाल, we would have no usable settings left,
		 * causing the resulting setup to fail.
		 */
		अगर (!snd_soc_dai_stream_valid(codec_dai, stream))
			जारी;

		codec_stream = snd_soc_dai_get_pcm_stream(codec_dai, stream);

		soc_pcm_hw_update_chan(hw, codec_stream);
		soc_pcm_hw_update_rate(hw, codec_stream);
		soc_pcm_hw_update_क्रमmat(hw, codec_stream);
	पूर्ण

	/* Verअगरy both a valid CPU DAI and a valid CODEC DAI were found */
	अगर (!hw->channels_min)
		वापस -EINVAL;

	/*
	 * chan min/max cannot be enक्रमced अगर there are multiple CODEC DAIs
	 * connected to CPU DAI(s), use CPU DAI's directly and let
	 * channel allocation be fixed up later
	 */
	अगर (rtd->num_codecs > 1) अणु
		hw->channels_min = cpu_chan_min;
		hw->channels_max = cpu_chan_max;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_runसमय_calc_hw);

अटल व्योम soc_pcm_init_runसमय_hw(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_hardware *hw = &substream->runसमय->hw;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	u64 क्रमmats = hw->क्रमmats;

	/*
	 * At least one CPU and one CODEC should match. Otherwise, we should
	 * have bailed out on a higher level, since there would be no CPU or
	 * CODEC to support the transfer direction in that हाल.
	 */
	snd_soc_runसमय_calc_hw(rtd, hw, substream->stream);

	अगर (क्रमmats)
		hw->क्रमmats &= क्रमmats;
पूर्ण

अटल पूर्णांक soc_pcm_components_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component;
	पूर्णांक i, ret = 0;

	क्रम_each_rtd_components(rtd, i, component) अणु
		ret = snd_soc_component_module_get_when_खोलो(component, substream);
		अगर (ret < 0)
			अवरोध;

		ret = snd_soc_component_खोलो(component, substream);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक soc_pcm_components_बंद(काष्ठा snd_pcm_substream *substream,
				    पूर्णांक rollback)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component;
	पूर्णांक i, r, ret = 0;

	क्रम_each_rtd_components(rtd, i, component) अणु
		r = snd_soc_component_बंद(component, substream, rollback);
		अगर (r < 0)
			ret = r; /* use last ret */

		snd_soc_component_module_put_when_बंद(component, substream, rollback);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक soc_pcm_clean(काष्ठा snd_pcm_substream *substream, पूर्णांक rollback)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component;
	काष्ठा snd_soc_dai *dai;
	पूर्णांक i;

	mutex_lock_nested(&rtd->card->pcm_mutex, rtd->card->pcm_subclass);

	अगर (!rollback)
		snd_soc_runसमय_deactivate(rtd, substream->stream);

	क्रम_each_rtd_dais(rtd, i, dai)
		snd_soc_dai_shutकरोwn(dai, substream, rollback);

	snd_soc_link_shutकरोwn(substream, rollback);

	soc_pcm_components_बंद(substream, rollback);


	mutex_unlock(&rtd->card->pcm_mutex);

	snd_soc_pcm_component_pm_runसमय_put(rtd, substream, rollback);

	क्रम_each_rtd_components(rtd, i, component)
		अगर (!snd_soc_component_active(component))
			pinctrl_pm_select_sleep_state(component->dev);

	वापस 0;
पूर्ण

/*
 * Called by ALSA when a PCM substream is बंदd. Private data can be
 * मुक्तd here. The cpu DAI, codec DAI, machine and components are also
 * shutकरोwn.
 */
अटल पूर्णांक soc_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	वापस soc_pcm_clean(substream, 0);
पूर्ण

अटल पूर्णांक soc_hw_sanity_check(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_pcm_hardware *hw = &substream->runसमय->hw;
	स्थिर अक्षर *name_cpu = soc_cpu_dai_name(rtd);
	स्थिर अक्षर *name_codec = soc_codec_dai_name(rtd);
	स्थिर अक्षर *err_msg;
	काष्ठा device *dev = rtd->dev;

	err_msg = "rates";
	अगर (!hw->rates)
		जाओ config_err;

	err_msg = "formats";
	अगर (!hw->क्रमmats)
		जाओ config_err;

	err_msg = "channels";
	अगर (!hw->channels_min || !hw->channels_max ||
	     hw->channels_min  >  hw->channels_max)
		जाओ config_err;

	dev_dbg(dev, "ASoC: %s <-> %s info:\n",		name_codec,
							name_cpu);
	dev_dbg(dev, "ASoC: rate mask 0x%x\n",		hw->rates);
	dev_dbg(dev, "ASoC: ch   min %d max %d\n",	hw->channels_min,
							hw->channels_max);
	dev_dbg(dev, "ASoC: rate min %d max %d\n",	hw->rate_min,
							hw->rate_max);

	वापस 0;

config_err:
	dev_err(dev, "ASoC: %s <-> %s No matching %s\n",
		name_codec, name_cpu, err_msg);
	वापस -EINVAL;
पूर्ण

/*
 * Called by ALSA when a PCM substream is खोलोed, the runसमय->hw record is
 * then initialized and any निजी data can be allocated. This also calls
 * startup क्रम the cpu DAI, component, machine and codec DAI.
 */
अटल पूर्णांक soc_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component;
	काष्ठा snd_soc_dai *dai;
	पूर्णांक i, ret = 0;

	क्रम_each_rtd_components(rtd, i, component)
		pinctrl_pm_select_शेष_state(component->dev);

	ret = snd_soc_pcm_component_pm_runसमय_get(rtd, substream);
	अगर (ret < 0)
		जाओ pm_err;

	mutex_lock_nested(&rtd->card->pcm_mutex, rtd->card->pcm_subclass);

	ret = soc_pcm_components_खोलो(substream);
	अगर (ret < 0)
		जाओ err;

	ret = snd_soc_link_startup(substream);
	अगर (ret < 0)
		जाओ err;

	/* startup the audio subप्रणाली */
	क्रम_each_rtd_dais(rtd, i, dai) अणु
		ret = snd_soc_dai_startup(dai, substream);
		अगर (ret < 0)
			जाओ err;

		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			dai->tx_mask = 0;
		अन्यथा
			dai->rx_mask = 0;
	पूर्ण

	/* Dynamic PCM DAI links compat checks use dynamic capabilities */
	अगर (rtd->dai_link->dynamic || rtd->dai_link->no_pcm)
		जाओ dynamic;

	/* Check that the codec and cpu DAIs are compatible */
	soc_pcm_init_runसमय_hw(substream);

	soc_pcm_update_symmetry(substream);

	ret = soc_hw_sanity_check(substream);
	अगर (ret < 0)
		जाओ err;

	soc_pcm_apply_msb(substream);

	/* Symmetry only applies अगर we've alपढ़ोy got an active stream. */
	क्रम_each_rtd_dais(rtd, i, dai) अणु
		ret = soc_pcm_apply_symmetry(substream, dai);
		अगर (ret != 0)
			जाओ err;
	पूर्ण
dynamic:
	snd_soc_runसमय_activate(rtd, substream->stream);
	ret = 0;
err:
	mutex_unlock(&rtd->card->pcm_mutex);
pm_err:
	अगर (ret < 0) अणु
		soc_pcm_clean(substream, 1);
		dev_err(rtd->dev, "%s() failed (%d)", __func__, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम codec2codec_बंद_delayed_work(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	/*
	 * Currently nothing to करो क्रम c2c links
	 * Since c2c links are पूर्णांकernal nodes in the DAPM graph and
	 * करोn't पूर्णांकerface with the outside world or application layer
	 * we करोn't have to करो any special handling on बंद.
	 */
पूर्ण

/*
 * Called by ALSA when the PCM substream is prepared, can set क्रमmat, sample
 * rate, etc.  This function is non atomic and can be called multiple बार,
 * it can refer to the runसमय info.
 */
अटल पूर्णांक soc_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *dai;
	पूर्णांक i, ret = 0;

	mutex_lock_nested(&rtd->card->pcm_mutex, rtd->card->pcm_subclass);

	ret = snd_soc_link_prepare(substream);
	अगर (ret < 0)
		जाओ out;

	ret = snd_soc_pcm_component_prepare(substream);
	अगर (ret < 0)
		जाओ out;

	ret = snd_soc_pcm_dai_prepare(substream);
	अगर (ret < 0)
		जाओ out;

	/* cancel any delayed stream shutकरोwn that is pending */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK &&
	    rtd->pop_रुको) अणु
		rtd->pop_रुको = 0;
		cancel_delayed_work(&rtd->delayed_work);
	पूर्ण

	snd_soc_dapm_stream_event(rtd, substream->stream,
			SND_SOC_DAPM_STREAM_START);

	क्रम_each_rtd_dais(rtd, i, dai)
		snd_soc_dai_digital_mute(dai, 0, substream->stream);

out:
	mutex_unlock(&rtd->card->pcm_mutex);

	अगर (ret < 0)
		dev_err(rtd->dev, "ASoC: %s() failed (%d)\n", __func__, ret);

	वापस ret;
पूर्ण

अटल व्योम soc_pcm_codec_params_fixup(काष्ठा snd_pcm_hw_params *params,
				       अचिन्हित पूर्णांक mask)
अणु
	काष्ठा snd_पूर्णांकerval *पूर्णांकerval;
	पूर्णांक channels = hweight_दीर्घ(mask);

	पूर्णांकerval = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	पूर्णांकerval->min = channels;
	पूर्णांकerval->max = channels;
पूर्ण

अटल पूर्णांक soc_pcm_hw_clean(काष्ठा snd_pcm_substream *substream, पूर्णांक rollback)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *dai;
	पूर्णांक i;

	mutex_lock_nested(&rtd->card->pcm_mutex, rtd->card->pcm_subclass);

	/* clear the corresponding DAIs parameters when going to be inactive */
	क्रम_each_rtd_dais(rtd, i, dai) अणु
		पूर्णांक active = snd_soc_dai_stream_active(dai, substream->stream);

		अगर (snd_soc_dai_active(dai) == 1)
			soc_pcm_set_dai_params(dai, शून्य);

		अगर (active == 1)
			snd_soc_dai_digital_mute(dai, 1, substream->stream);
	पूर्ण

	/* run the stream event */
	snd_soc_dapm_stream_stop(rtd, substream->stream);

	/* मुक्त any machine hw params */
	snd_soc_link_hw_मुक्त(substream, rollback);

	/* मुक्त any component resources */
	snd_soc_pcm_component_hw_मुक्त(substream, rollback);

	/* now मुक्त hw params क्रम the DAIs  */
	क्रम_each_rtd_dais(rtd, i, dai) अणु
		अगर (!snd_soc_dai_stream_valid(dai, substream->stream))
			जारी;

		snd_soc_dai_hw_मुक्त(dai, substream, rollback);
	पूर्ण

	mutex_unlock(&rtd->card->pcm_mutex);
	वापस 0;
पूर्ण

/*
 * Frees resources allocated by hw_params, can be called multiple बार
 */
अटल पूर्णांक soc_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	वापस soc_pcm_hw_clean(substream, 0);
पूर्ण

/*
 * Called by ALSA when the hardware params are set by application. This
 * function can also be called multiple बार and can allocate buffers
 * (using snd_pcm_lib_* ). It's non-atomic.
 */
अटल पूर्णांक soc_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक i, ret = 0;

	mutex_lock_nested(&rtd->card->pcm_mutex, rtd->card->pcm_subclass);

	ret = soc_pcm_params_symmetry(substream, params);
	अगर (ret)
		जाओ out;

	ret = snd_soc_link_hw_params(substream, params);
	अगर (ret < 0)
		जाओ out;

	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
		काष्ठा snd_pcm_hw_params codec_params;

		/*
		 * Skip CODECs which करोn't support the current stream type,
		 * the idea being that अगर a CODEC is not used क्रम the currently
		 * set up transfer direction, it should not need to be
		 * configured, especially since the configuration used might
		 * not even be supported by that CODEC. There may be हालs
		 * however where a CODEC needs to be set up although it is
		 * actually not being used क्रम the transfer, e.g. अगर a
		 * capture-only CODEC is acting as an LRCLK and/or BCLK master
		 * क्रम the DAI link including a playback-only CODEC.
		 * If this becomes necessary, we will have to augment the
		 * machine driver setup with inक्रमmation on how to act, so
		 * we can करो the right thing here.
		 */
		अगर (!snd_soc_dai_stream_valid(codec_dai, substream->stream))
			जारी;

		/* copy params क्रम each codec */
		codec_params = *params;

		/* fixup params based on TDM slot masks */
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK &&
		    codec_dai->tx_mask)
			soc_pcm_codec_params_fixup(&codec_params,
						   codec_dai->tx_mask);

		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE &&
		    codec_dai->rx_mask)
			soc_pcm_codec_params_fixup(&codec_params,
						   codec_dai->rx_mask);

		ret = snd_soc_dai_hw_params(codec_dai, substream,
					    &codec_params);
		अगर(ret < 0)
			जाओ out;

		soc_pcm_set_dai_params(codec_dai, &codec_params);
		snd_soc_dapm_update_dai(substream, &codec_params, codec_dai);
	पूर्ण

	क्रम_each_rtd_cpu_dais(rtd, i, cpu_dai) अणु
		/*
		 * Skip CPUs which करोn't support the current stream
		 * type. See soc_pcm_init_runसमय_hw() क्रम more details
		 */
		अगर (!snd_soc_dai_stream_valid(cpu_dai, substream->stream))
			जारी;

		ret = snd_soc_dai_hw_params(cpu_dai, substream, params);
		अगर (ret < 0)
			जाओ out;

		/* store the parameters क्रम each DAI */
		soc_pcm_set_dai_params(cpu_dai, params);
		snd_soc_dapm_update_dai(substream, params, cpu_dai);
	पूर्ण

	ret = snd_soc_pcm_component_hw_params(substream, params);
out:
	mutex_unlock(&rtd->card->pcm_mutex);

	अगर (ret < 0) अणु
		soc_pcm_hw_clean(substream, 1);
		dev_err(rtd->dev, "ASoC: %s() failed (%d)\n", __func__, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक soc_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	पूर्णांक ret = -EINVAL, _ret = 0;
	पूर्णांक rollback = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ret = snd_soc_link_trigger(substream, cmd, 0);
		अगर (ret < 0)
			जाओ start_err;

		ret = snd_soc_pcm_component_trigger(substream, cmd, 0);
		अगर (ret < 0)
			जाओ start_err;

		ret = snd_soc_pcm_dai_trigger(substream, cmd, 0);
start_err:
		अगर (ret < 0)
			rollback = 1;
	पूर्ण

	अगर (rollback) अणु
		_ret = ret;
		चयन (cmd) अणु
		हाल SNDRV_PCM_TRIGGER_START:
			cmd = SNDRV_PCM_TRIGGER_STOP;
			अवरोध;
		हाल SNDRV_PCM_TRIGGER_RESUME:
			cmd = SNDRV_PCM_TRIGGER_SUSPEND;
			अवरोध;
		हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
			cmd = SNDRV_PCM_TRIGGER_PAUSE_PUSH;
			अवरोध;
		पूर्ण
	पूर्ण

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ret = snd_soc_pcm_dai_trigger(substream, cmd, rollback);
		अगर (ret < 0)
			अवरोध;

		ret = snd_soc_pcm_component_trigger(substream, cmd, rollback);
		अगर (ret < 0)
			अवरोध;

		ret = snd_soc_link_trigger(substream, cmd, rollback);
		अवरोध;
	पूर्ण

	अगर (_ret)
		ret = _ret;

	वापस ret;
पूर्ण

/*
 * soc level wrapper क्रम poपूर्णांकer callback
 * If cpu_dai, codec_dai, component driver has the delay callback, then
 * the runसमय->delay will be updated accordingly.
 */
अटल snd_pcm_uframes_t soc_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai;
	काष्ठा snd_soc_dai *codec_dai;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_pcm_uframes_t offset = 0;
	snd_pcm_sframes_t delay = 0;
	snd_pcm_sframes_t codec_delay = 0;
	snd_pcm_sframes_t cpu_delay = 0;
	पूर्णांक i;

	/* clearing the previous total delay */
	runसमय->delay = 0;

	offset = snd_soc_pcm_component_poपूर्णांकer(substream);

	/* base delay अगर asचिन्हित in poपूर्णांकer callback */
	delay = runसमय->delay;

	क्रम_each_rtd_cpu_dais(rtd, i, cpu_dai) अणु
		cpu_delay = max(cpu_delay,
				snd_soc_dai_delay(cpu_dai, substream));
	पूर्ण
	delay += cpu_delay;

	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
		codec_delay = max(codec_delay,
				  snd_soc_dai_delay(codec_dai, substream));
	पूर्ण
	delay += codec_delay;

	runसमय->delay = delay;

	वापस offset;
पूर्ण

/* connect a FE and BE */
अटल पूर्णांक dpcm_be_connect(काष्ठा snd_soc_pcm_runसमय *fe,
		काष्ठा snd_soc_pcm_runसमय *be, पूर्णांक stream)
अणु
	काष्ठा snd_soc_dpcm *dpcm;
	अचिन्हित दीर्घ flags;

	/* only add new dpcms */
	क्रम_each_dpcm_be(fe, stream, dpcm) अणु
		अगर (dpcm->be == be && dpcm->fe == fe)
			वापस 0;
	पूर्ण

	dpcm = kzalloc(माप(काष्ठा snd_soc_dpcm), GFP_KERNEL);
	अगर (!dpcm)
		वापस -ENOMEM;

	dpcm->be = be;
	dpcm->fe = fe;
	be->dpcm[stream].runसमय = fe->dpcm[stream].runसमय;
	dpcm->state = SND_SOC_DPCM_LINK_STATE_NEW;
	spin_lock_irqsave(&fe->card->dpcm_lock, flags);
	list_add(&dpcm->list_be, &fe->dpcm[stream].be_clients);
	list_add(&dpcm->list_fe, &be->dpcm[stream].fe_clients);
	spin_unlock_irqrestore(&fe->card->dpcm_lock, flags);

	dev_dbg(fe->dev, "connected new DPCM %s path %s %s %s\n",
			stream ? "capture" : "playback",  fe->dai_link->name,
			stream ? "<-" : "->", be->dai_link->name);

	dpcm_create_debugfs_state(dpcm, stream);

	वापस 1;
पूर्ण

/* reparent a BE onto another FE */
अटल व्योम dpcm_be_reparent(काष्ठा snd_soc_pcm_runसमय *fe,
			काष्ठा snd_soc_pcm_runसमय *be, पूर्णांक stream)
अणु
	काष्ठा snd_soc_dpcm *dpcm;
	काष्ठा snd_pcm_substream *fe_substream, *be_substream;

	/* reparent अगर BE is connected to other FEs */
	अगर (!be->dpcm[stream].users)
		वापस;

	be_substream = snd_soc_dpcm_get_substream(be, stream);

	क्रम_each_dpcm_fe(be, stream, dpcm) अणु
		अगर (dpcm->fe == fe)
			जारी;

		dev_dbg(fe->dev, "reparent %s path %s %s %s\n",
			stream ? "capture" : "playback",
			dpcm->fe->dai_link->name,
			stream ? "<-" : "->", dpcm->be->dai_link->name);

		fe_substream = snd_soc_dpcm_get_substream(dpcm->fe, stream);
		be_substream->runसमय = fe_substream->runसमय;
		अवरोध;
	पूर्ण
पूर्ण

/* disconnect a BE and FE */
व्योम dpcm_be_disconnect(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक stream)
अणु
	काष्ठा snd_soc_dpcm *dpcm, *d;
	अचिन्हित दीर्घ flags;

	क्रम_each_dpcm_be_safe(fe, stream, dpcm, d) अणु
		dev_dbg(fe->dev, "ASoC: BE %s disconnect check for %s\n",
				stream ? "capture" : "playback",
				dpcm->be->dai_link->name);

		अगर (dpcm->state != SND_SOC_DPCM_LINK_STATE_FREE)
			जारी;

		dev_dbg(fe->dev, "freed DSP %s path %s %s %s\n",
			stream ? "capture" : "playback", fe->dai_link->name,
			stream ? "<-" : "->", dpcm->be->dai_link->name);

		/* BEs still alive need new FE */
		dpcm_be_reparent(fe, dpcm->be, stream);

		dpcm_हटाओ_debugfs_state(dpcm);

		spin_lock_irqsave(&fe->card->dpcm_lock, flags);
		list_del(&dpcm->list_be);
		list_del(&dpcm->list_fe);
		spin_unlock_irqrestore(&fe->card->dpcm_lock, flags);
		kमुक्त(dpcm);
	पूर्ण
पूर्ण

/* get BE क्रम DAI widget and stream */
अटल काष्ठा snd_soc_pcm_runसमय *dpcm_get_be(काष्ठा snd_soc_card *card,
		काष्ठा snd_soc_dapm_widget *widget, पूर्णांक stream)
अणु
	काष्ठा snd_soc_pcm_runसमय *be;
	काष्ठा snd_soc_dapm_widget *w;
	काष्ठा snd_soc_dai *dai;
	पूर्णांक i;

	dev_dbg(card->dev, "ASoC: find BE for widget %s\n", widget->name);

	क्रम_each_card_rtds(card, be) अणु

		अगर (!be->dai_link->no_pcm)
			जारी;

		क्रम_each_rtd_dais(be, i, dai) अणु
			w = snd_soc_dai_get_widget(dai, stream);

			dev_dbg(card->dev, "ASoC: try BE : %s\n",
				w ? w->name : "(not set)");

			अगर (w == widget)
				वापस be;
		पूर्ण
	पूर्ण

	/* Widget provided is not a BE */
	वापस शून्य;
पूर्ण

अटल पूर्णांक widget_in_list(काष्ठा snd_soc_dapm_widget_list *list,
		काष्ठा snd_soc_dapm_widget *widget)
अणु
	काष्ठा snd_soc_dapm_widget *w;
	पूर्णांक i;

	क्रम_each_dapm_widमाला_लो(list, i, w)
		अगर (widget == w)
			वापस 1;

	वापस 0;
पूर्ण

अटल bool dpcm_end_walk_at_be(काष्ठा snd_soc_dapm_widget *widget,
		क्रमागत snd_soc_dapm_direction dir)
अणु
	काष्ठा snd_soc_card *card = widget->dapm->card;
	काष्ठा snd_soc_pcm_runसमय *rtd;
	पूर्णांक stream;

	/* adjust dir to stream */
	अगर (dir == SND_SOC_DAPM_सूची_OUT)
		stream = SNDRV_PCM_STREAM_PLAYBACK;
	अन्यथा
		stream = SNDRV_PCM_STREAM_CAPTURE;

	rtd = dpcm_get_be(card, widget, stream);
	अगर (rtd)
		वापस true;

	वापस false;
पूर्ण

पूर्णांक dpcm_path_get(काष्ठा snd_soc_pcm_runसमय *fe,
	पूर्णांक stream, काष्ठा snd_soc_dapm_widget_list **list)
अणु
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(fe, 0);
	पूर्णांक paths;

	अगर (fe->num_cpus > 1) अणु
		dev_err(fe->dev,
			"%s doesn't support Multi CPU yet\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* get number of valid DAI paths and their widमाला_लो */
	paths = snd_soc_dapm_dai_get_connected_widमाला_लो(cpu_dai, stream, list,
			fe->card->component_chaining ?
				शून्य : dpcm_end_walk_at_be);

	अगर (paths > 0)
		dev_dbg(fe->dev, "ASoC: found %d audio %s paths\n", paths,
			stream ? "capture" : "playback");
	अन्यथा अगर (paths == 0)
		dev_dbg(fe->dev, "ASoC: %s no valid %s path\n", fe->dai_link->name,
			 stream ? "capture" : "playback");

	वापस paths;
पूर्ण

व्योम dpcm_path_put(काष्ठा snd_soc_dapm_widget_list **list)
अणु
	snd_soc_dapm_dai_मुक्त_widमाला_लो(list);
पूर्ण

अटल bool dpcm_be_is_active(काष्ठा snd_soc_dpcm *dpcm, पूर्णांक stream,
			      काष्ठा snd_soc_dapm_widget_list *list)
अणु
	काष्ठा snd_soc_dapm_widget *widget;
	काष्ठा snd_soc_dai *dai;
	अचिन्हित पूर्णांक i;

	/* is there a valid DAI widget क्रम this BE */
	क्रम_each_rtd_dais(dpcm->be, i, dai) अणु
		widget = snd_soc_dai_get_widget(dai, stream);

		/*
		 * The BE is pruned only अगर none of the dai
		 * widमाला_लो are in the active list.
		 */
		अगर (widget && widget_in_list(list, widget))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक dpcm_prune_paths(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक stream,
			    काष्ठा snd_soc_dapm_widget_list **list_)
अणु
	काष्ठा snd_soc_dpcm *dpcm;
	पूर्णांक prune = 0;

	/* Destroy any old FE <--> BE connections */
	क्रम_each_dpcm_be(fe, stream, dpcm) अणु
		अगर (dpcm_be_is_active(dpcm, stream, *list_))
			जारी;

		dev_dbg(fe->dev, "ASoC: pruning %s BE %s for %s\n",
			stream ? "capture" : "playback",
			dpcm->be->dai_link->name, fe->dai_link->name);
		dpcm->state = SND_SOC_DPCM_LINK_STATE_FREE;
		dpcm_set_be_update_state(dpcm->be, stream, SND_SOC_DPCM_UPDATE_BE);
		prune++;
	पूर्ण

	dev_dbg(fe->dev, "ASoC: found %d old BE paths for pruning\n", prune);
	वापस prune;
पूर्ण

अटल पूर्णांक dpcm_add_paths(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक stream,
	काष्ठा snd_soc_dapm_widget_list **list_)
अणु
	काष्ठा snd_soc_card *card = fe->card;
	काष्ठा snd_soc_dapm_widget_list *list = *list_;
	काष्ठा snd_soc_pcm_runसमय *be;
	काष्ठा snd_soc_dapm_widget *widget;
	पूर्णांक i, new = 0, err;

	/* Create any new FE <--> BE connections */
	क्रम_each_dapm_widमाला_लो(list, i, widget) अणु

		चयन (widget->id) अणु
		हाल snd_soc_dapm_dai_in:
			अगर (stream != SNDRV_PCM_STREAM_PLAYBACK)
				जारी;
			अवरोध;
		हाल snd_soc_dapm_dai_out:
			अगर (stream != SNDRV_PCM_STREAM_CAPTURE)
				जारी;
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		/* is there a valid BE rtd क्रम this widget */
		be = dpcm_get_be(card, widget, stream);
		अगर (!be) अणु
			dev_dbg(fe->dev, "ASoC: no BE found for %s\n",
				widget->name);
			जारी;
		पूर्ण

		/* करोn't connect अगर FE is not running */
		अगर (!fe->dpcm[stream].runसमय && !fe->fe_compr)
			जारी;

		/* newly connected FE and BE */
		err = dpcm_be_connect(fe, be, stream);
		अगर (err < 0) अणु
			dev_err(fe->dev, "ASoC: can't connect %s\n",
				widget->name);
			अवरोध;
		पूर्ण अन्यथा अगर (err == 0) /* alपढ़ोy connected */
			जारी;

		/* new */
		dpcm_set_be_update_state(be, stream, SND_SOC_DPCM_UPDATE_BE);
		new++;
	पूर्ण

	dev_dbg(fe->dev, "ASoC: found %d new BE paths\n", new);
	वापस new;
पूर्ण

/*
 * Find the corresponding BE DAIs that source or sink audio to this
 * FE substream.
 */
पूर्णांक dpcm_process_paths(काष्ठा snd_soc_pcm_runसमय *fe,
	पूर्णांक stream, काष्ठा snd_soc_dapm_widget_list **list, पूर्णांक new)
अणु
	अगर (new)
		वापस dpcm_add_paths(fe, stream, list);
	अन्यथा
		वापस dpcm_prune_paths(fe, stream, list);
पूर्ण

व्योम dpcm_clear_pending_state(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक stream)
अणु
	काष्ठा snd_soc_dpcm *dpcm;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fe->card->dpcm_lock, flags);
	क्रम_each_dpcm_be(fe, stream, dpcm)
		dpcm_set_be_update_state(dpcm->be, stream, SND_SOC_DPCM_UPDATE_NO);
	spin_unlock_irqrestore(&fe->card->dpcm_lock, flags);
पूर्ण

व्योम dpcm_be_dai_stop(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक stream,
		      पूर्णांक करो_hw_मुक्त, काष्ठा snd_soc_dpcm *last)
अणु
	काष्ठा snd_soc_dpcm *dpcm;

	/* disable any enabled and non active backends */
	क्रम_each_dpcm_be(fe, stream, dpcm) अणु
		काष्ठा snd_soc_pcm_runसमय *be = dpcm->be;
		काष्ठा snd_pcm_substream *be_substream =
			snd_soc_dpcm_get_substream(be, stream);

		अगर (dpcm == last)
			वापस;

		/* is this op क्रम this BE ? */
		अगर (!snd_soc_dpcm_be_can_update(fe, be, stream))
			जारी;

		अगर (be->dpcm[stream].users == 0) अणु
			dev_err(be->dev, "ASoC: no users %s at close - state %d\n",
				stream ? "capture" : "playback",
				be->dpcm[stream].state);
			जारी;
		पूर्ण

		अगर (--be->dpcm[stream].users != 0)
			जारी;

		अगर (be->dpcm[stream].state != SND_SOC_DPCM_STATE_OPEN) अणु
			अगर (!करो_hw_मुक्त)
				जारी;

			अगर (be->dpcm[stream].state != SND_SOC_DPCM_STATE_HW_FREE) अणु
				soc_pcm_hw_मुक्त(be_substream);
				be->dpcm[stream].state = SND_SOC_DPCM_STATE_HW_FREE;
			पूर्ण
		पूर्ण

		soc_pcm_बंद(be_substream);
		be_substream->runसमय = शून्य;
		be->dpcm[stream].state = SND_SOC_DPCM_STATE_CLOSE;
	पूर्ण
पूर्ण

पूर्णांक dpcm_be_dai_startup(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक stream)
अणु
	काष्ठा snd_soc_pcm_runसमय *be;
	काष्ठा snd_soc_dpcm *dpcm;
	पूर्णांक err, count = 0;

	/* only startup BE DAIs that are either sinks or sources to this FE DAI */
	क्रम_each_dpcm_be(fe, stream, dpcm) अणु
		काष्ठा snd_pcm_substream *be_substream;

		be = dpcm->be;
		be_substream = snd_soc_dpcm_get_substream(be, stream);

		अगर (!be_substream) अणु
			dev_err(be->dev, "ASoC: no backend %s stream\n",
				stream ? "capture" : "playback");
			जारी;
		पूर्ण

		/* is this op क्रम this BE ? */
		अगर (!snd_soc_dpcm_be_can_update(fe, be, stream))
			जारी;

		/* first समय the dpcm is खोलो ? */
		अगर (be->dpcm[stream].users == DPCM_MAX_BE_USERS) अणु
			dev_err(be->dev, "ASoC: too many users %s at open %d\n",
				stream ? "capture" : "playback",
				be->dpcm[stream].state);
			जारी;
		पूर्ण

		अगर (be->dpcm[stream].users++ != 0)
			जारी;

		अगर ((be->dpcm[stream].state != SND_SOC_DPCM_STATE_NEW) &&
		    (be->dpcm[stream].state != SND_SOC_DPCM_STATE_CLOSE))
			जारी;

		dev_dbg(be->dev, "ASoC: open %s BE %s\n",
			stream ? "capture" : "playback", be->dai_link->name);

		be_substream->runसमय = be->dpcm[stream].runसमय;
		err = soc_pcm_खोलो(be_substream);
		अगर (err < 0) अणु
			be->dpcm[stream].users--;
			अगर (be->dpcm[stream].users < 0)
				dev_err(be->dev, "ASoC: no users %s at unwind %d\n",
					stream ? "capture" : "playback",
					be->dpcm[stream].state);

			be->dpcm[stream].state = SND_SOC_DPCM_STATE_CLOSE;
			जाओ unwind;
		पूर्ण

		be->dpcm[stream].state = SND_SOC_DPCM_STATE_OPEN;
		count++;
	पूर्ण

	वापस count;

unwind:
	dpcm_be_dai_startup_rollback(fe, stream, dpcm);

	dev_err(fe->dev, "ASoC: %s() failed at %s (%d)\n",
		__func__, be->dai_link->name, err);

	वापस err;
पूर्ण

अटल व्योम dpcm_runसमय_setup_fe(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *fe = asoc_substream_to_rtd(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_pcm_hardware *hw = &runसमय->hw;
	काष्ठा snd_soc_dai *dai;
	पूर्णांक stream = substream->stream;
	पूर्णांक i;

	soc_pcm_hw_init(hw);

	क्रम_each_rtd_cpu_dais(fe, i, dai) अणु
		काष्ठा snd_soc_pcm_stream *cpu_stream;

		/*
		 * Skip CPUs which करोn't support the current stream
		 * type. See soc_pcm_init_runसमय_hw() क्रम more details
		 */
		अगर (!snd_soc_dai_stream_valid(dai, stream))
			जारी;

		cpu_stream = snd_soc_dai_get_pcm_stream(dai, stream);

		soc_pcm_hw_update_rate(hw, cpu_stream);
		soc_pcm_hw_update_chan(hw, cpu_stream);
		soc_pcm_hw_update_क्रमmat(hw, cpu_stream);
	पूर्ण

पूर्ण

अटल व्योम dpcm_runसमय_setup_be_क्रमmat(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *fe = asoc_substream_to_rtd(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_pcm_hardware *hw = &runसमय->hw;
	काष्ठा snd_soc_dpcm *dpcm;
	काष्ठा snd_soc_dai *dai;
	पूर्णांक stream = substream->stream;

	अगर (!fe->dai_link->dpcm_merged_क्रमmat)
		वापस;

	/*
	 * It वापसs merged BE codec क्रमmat
	 * अगर FE want to use it (= dpcm_merged_क्रमmat)
	 */

	क्रम_each_dpcm_be(fe, stream, dpcm) अणु
		काष्ठा snd_soc_pcm_runसमय *be = dpcm->be;
		काष्ठा snd_soc_pcm_stream *codec_stream;
		पूर्णांक i;

		क्रम_each_rtd_codec_dais(be, i, dai) अणु
			/*
			 * Skip CODECs which करोn't support the current stream
			 * type. See soc_pcm_init_runसमय_hw() क्रम more details
			 */
			अगर (!snd_soc_dai_stream_valid(dai, stream))
				जारी;

			codec_stream = snd_soc_dai_get_pcm_stream(dai, stream);

			soc_pcm_hw_update_क्रमmat(hw, codec_stream);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dpcm_runसमय_setup_be_chan(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *fe = asoc_substream_to_rtd(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_pcm_hardware *hw = &runसमय->hw;
	काष्ठा snd_soc_dpcm *dpcm;
	पूर्णांक stream = substream->stream;

	अगर (!fe->dai_link->dpcm_merged_chan)
		वापस;

	/*
	 * It वापसs merged BE codec channel;
	 * अगर FE want to use it (= dpcm_merged_chan)
	 */

	क्रम_each_dpcm_be(fe, stream, dpcm) अणु
		काष्ठा snd_soc_pcm_runसमय *be = dpcm->be;
		काष्ठा snd_soc_pcm_stream *codec_stream;
		काष्ठा snd_soc_pcm_stream *cpu_stream;
		काष्ठा snd_soc_dai *dai;
		पूर्णांक i;

		क्रम_each_rtd_cpu_dais(be, i, dai) अणु
			/*
			 * Skip CPUs which करोn't support the current stream
			 * type. See soc_pcm_init_runसमय_hw() क्रम more details
			 */
			अगर (!snd_soc_dai_stream_valid(dai, stream))
				जारी;

			cpu_stream = snd_soc_dai_get_pcm_stream(dai, stream);

			soc_pcm_hw_update_chan(hw, cpu_stream);
		पूर्ण

		/*
		 * chan min/max cannot be enक्रमced अगर there are multiple CODEC
		 * DAIs connected to a single CPU DAI, use CPU DAI's directly
		 */
		अगर (be->num_codecs == 1) अणु
			codec_stream = snd_soc_dai_get_pcm_stream(asoc_rtd_to_codec(be, 0), stream);

			soc_pcm_hw_update_chan(hw, codec_stream);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dpcm_runसमय_setup_be_rate(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *fe = asoc_substream_to_rtd(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_pcm_hardware *hw = &runसमय->hw;
	काष्ठा snd_soc_dpcm *dpcm;
	पूर्णांक stream = substream->stream;

	अगर (!fe->dai_link->dpcm_merged_rate)
		वापस;

	/*
	 * It वापसs merged BE codec channel;
	 * अगर FE want to use it (= dpcm_merged_chan)
	 */

	क्रम_each_dpcm_be(fe, stream, dpcm) अणु
		काष्ठा snd_soc_pcm_runसमय *be = dpcm->be;
		काष्ठा snd_soc_pcm_stream *pcm;
		काष्ठा snd_soc_dai *dai;
		पूर्णांक i;

		क्रम_each_rtd_dais(be, i, dai) अणु
			/*
			 * Skip DAIs which करोn't support the current stream
			 * type. See soc_pcm_init_runसमय_hw() क्रम more details
			 */
			अगर (!snd_soc_dai_stream_valid(dai, stream))
				जारी;

			pcm = snd_soc_dai_get_pcm_stream(dai, stream);

			soc_pcm_hw_update_rate(hw, pcm);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक dpcm_apply_symmetry(काष्ठा snd_pcm_substream *fe_substream,
			       पूर्णांक stream)
अणु
	काष्ठा snd_soc_dpcm *dpcm;
	काष्ठा snd_soc_pcm_runसमय *fe = asoc_substream_to_rtd(fe_substream);
	काष्ठा snd_soc_dai *fe_cpu_dai;
	पूर्णांक err;
	पूर्णांक i;

	/* apply symmetry क्रम FE */
	soc_pcm_update_symmetry(fe_substream);

	क्रम_each_rtd_cpu_dais (fe, i, fe_cpu_dai) अणु
		/* Symmetry only applies अगर we've got an active stream. */
		err = soc_pcm_apply_symmetry(fe_substream, fe_cpu_dai);
		अगर (err < 0)
			जाओ error;
	पूर्ण

	/* apply symmetry क्रम BE */
	क्रम_each_dpcm_be(fe, stream, dpcm) अणु
		काष्ठा snd_soc_pcm_runसमय *be = dpcm->be;
		काष्ठा snd_pcm_substream *be_substream =
			snd_soc_dpcm_get_substream(be, stream);
		काष्ठा snd_soc_pcm_runसमय *rtd;
		काष्ठा snd_soc_dai *dai;

		/* A backend may not have the requested substream */
		अगर (!be_substream)
			जारी;

		rtd = asoc_substream_to_rtd(be_substream);
		अगर (rtd->dai_link->be_hw_params_fixup)
			जारी;

		soc_pcm_update_symmetry(be_substream);

		/* Symmetry only applies अगर we've got an active stream. */
		क्रम_each_rtd_dais(rtd, i, dai) अणु
			err = soc_pcm_apply_symmetry(fe_substream, dai);
			अगर (err < 0)
				जाओ error;
		पूर्ण
	पूर्ण
error:
	अगर (err < 0)
		dev_err(fe->dev, "ASoC: %s failed (%d)\n", __func__, err);

	वापस err;
पूर्ण

अटल पूर्णांक dpcm_fe_dai_startup(काष्ठा snd_pcm_substream *fe_substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *fe = asoc_substream_to_rtd(fe_substream);
	पूर्णांक stream = fe_substream->stream, ret = 0;

	dpcm_set_fe_update_state(fe, stream, SND_SOC_DPCM_UPDATE_FE);

	ret = dpcm_be_dai_startup(fe, stream);
	अगर (ret < 0)
		जाओ be_err;

	dev_dbg(fe->dev, "ASoC: open FE %s\n", fe->dai_link->name);

	/* start the DAI frontend */
	ret = soc_pcm_खोलो(fe_substream);
	अगर (ret < 0)
		जाओ unwind;

	fe->dpcm[stream].state = SND_SOC_DPCM_STATE_OPEN;

	dpcm_runसमय_setup_fe(fe_substream);

	dpcm_runसमय_setup_be_क्रमmat(fe_substream);
	dpcm_runसमय_setup_be_chan(fe_substream);
	dpcm_runसमय_setup_be_rate(fe_substream);

	ret = dpcm_apply_symmetry(fe_substream, stream);

unwind:
	अगर (ret < 0)
		dpcm_be_dai_startup_unwind(fe, stream);
be_err:
	dpcm_set_fe_update_state(fe, stream, SND_SOC_DPCM_UPDATE_NO);

	अगर (ret < 0)
		dev_err(fe->dev, "%s() failed (%d)\n", __func__, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक dpcm_fe_dai_shutकरोwn(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *fe = asoc_substream_to_rtd(substream);
	पूर्णांक stream = substream->stream;

	dpcm_set_fe_update_state(fe, stream, SND_SOC_DPCM_UPDATE_FE);

	/* shutकरोwn the BEs */
	dpcm_be_dai_shutकरोwn(fe, stream);

	dev_dbg(fe->dev, "ASoC: close FE %s\n", fe->dai_link->name);

	/* now shutकरोwn the frontend */
	soc_pcm_बंद(substream);

	/* run the stream stop event */
	dpcm_dapm_stream_event(fe, stream, SND_SOC_DAPM_STREAM_STOP);

	fe->dpcm[stream].state = SND_SOC_DPCM_STATE_CLOSE;
	dpcm_set_fe_update_state(fe, stream, SND_SOC_DPCM_UPDATE_NO);
	वापस 0;
पूर्ण

व्योम dpcm_be_dai_hw_मुक्त(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक stream)
अणु
	काष्ठा snd_soc_dpcm *dpcm;

	/* only hw_params backends that are either sinks or sources
	 * to this frontend DAI */
	क्रम_each_dpcm_be(fe, stream, dpcm) अणु

		काष्ठा snd_soc_pcm_runसमय *be = dpcm->be;
		काष्ठा snd_pcm_substream *be_substream =
			snd_soc_dpcm_get_substream(be, stream);

		/* is this op क्रम this BE ? */
		अगर (!snd_soc_dpcm_be_can_update(fe, be, stream))
			जारी;

		/* only मुक्त hw when no दीर्घer used - check all FEs */
		अगर (!snd_soc_dpcm_can_be_मुक्त_stop(fe, be, stream))
				जारी;

		/* करो not मुक्त hw अगर this BE is used by other FE */
		अगर (be->dpcm[stream].users > 1)
			जारी;

		अगर ((be->dpcm[stream].state != SND_SOC_DPCM_STATE_HW_PARAMS) &&
		    (be->dpcm[stream].state != SND_SOC_DPCM_STATE_PREPARE) &&
		    (be->dpcm[stream].state != SND_SOC_DPCM_STATE_HW_FREE) &&
		    (be->dpcm[stream].state != SND_SOC_DPCM_STATE_PAUSED) &&
		    (be->dpcm[stream].state != SND_SOC_DPCM_STATE_STOP) &&
		    (be->dpcm[stream].state != SND_SOC_DPCM_STATE_SUSPEND))
			जारी;

		dev_dbg(be->dev, "ASoC: hw_free BE %s\n",
			be->dai_link->name);

		soc_pcm_hw_मुक्त(be_substream);

		be->dpcm[stream].state = SND_SOC_DPCM_STATE_HW_FREE;
	पूर्ण
पूर्ण

अटल पूर्णांक dpcm_fe_dai_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *fe = asoc_substream_to_rtd(substream);
	पूर्णांक stream = substream->stream;

	mutex_lock_nested(&fe->card->mutex, SND_SOC_CARD_CLASS_RUNTIME);
	dpcm_set_fe_update_state(fe, stream, SND_SOC_DPCM_UPDATE_FE);

	dev_dbg(fe->dev, "ASoC: hw_free FE %s\n", fe->dai_link->name);

	/* call hw_मुक्त on the frontend */
	soc_pcm_hw_मुक्त(substream);

	/* only hw_params backends that are either sinks or sources
	 * to this frontend DAI */
	dpcm_be_dai_hw_मुक्त(fe, stream);

	fe->dpcm[stream].state = SND_SOC_DPCM_STATE_HW_FREE;
	dpcm_set_fe_update_state(fe, stream, SND_SOC_DPCM_UPDATE_NO);

	mutex_unlock(&fe->card->mutex);
	वापस 0;
पूर्ण

पूर्णांक dpcm_be_dai_hw_params(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक stream)
अणु
	काष्ठा snd_soc_pcm_runसमय *be;
	काष्ठा snd_pcm_substream *be_substream;
	काष्ठा snd_soc_dpcm *dpcm;
	पूर्णांक ret;

	क्रम_each_dpcm_be(fe, stream, dpcm) अणु
		be = dpcm->be;
		be_substream = snd_soc_dpcm_get_substream(be, stream);

		/* is this op क्रम this BE ? */
		अगर (!snd_soc_dpcm_be_can_update(fe, be, stream))
			जारी;

		/* copy params क्रम each dpcm */
		स_नकल(&dpcm->hw_params, &fe->dpcm[stream].hw_params,
				माप(काष्ठा snd_pcm_hw_params));

		/* perक्रमm any hw_params fixups */
		ret = snd_soc_link_be_hw_params_fixup(be, &dpcm->hw_params);
		अगर (ret < 0)
			जाओ unwind;

		/* copy the fixed-up hw params क्रम BE dai */
		स_नकल(&be->dpcm[stream].hw_params, &dpcm->hw_params,
		       माप(काष्ठा snd_pcm_hw_params));

		/* only allow hw_params() अगर no connected FEs are running */
		अगर (!snd_soc_dpcm_can_be_params(fe, be, stream))
			जारी;

		अगर ((be->dpcm[stream].state != SND_SOC_DPCM_STATE_OPEN) &&
		    (be->dpcm[stream].state != SND_SOC_DPCM_STATE_HW_PARAMS) &&
		    (be->dpcm[stream].state != SND_SOC_DPCM_STATE_HW_FREE))
			जारी;

		dev_dbg(be->dev, "ASoC: hw_params BE %s\n",
			be->dai_link->name);

		ret = soc_pcm_hw_params(be_substream, &dpcm->hw_params);
		अगर (ret < 0)
			जाओ unwind;

		be->dpcm[stream].state = SND_SOC_DPCM_STATE_HW_PARAMS;
	पूर्ण
	वापस 0;

unwind:
	dev_dbg(fe->dev, "ASoC: %s() failed at %s (%d)\n",
		__func__, be->dai_link->name, ret);

	/* disable any enabled and non active backends */
	क्रम_each_dpcm_be_rollback(fe, stream, dpcm) अणु
		be = dpcm->be;
		be_substream = snd_soc_dpcm_get_substream(be, stream);

		अगर (!snd_soc_dpcm_be_can_update(fe, be, stream))
			जारी;

		/* only allow hw_मुक्त() अगर no connected FEs are running */
		अगर (!snd_soc_dpcm_can_be_मुक्त_stop(fe, be, stream))
			जारी;

		अगर ((be->dpcm[stream].state != SND_SOC_DPCM_STATE_OPEN) &&
		   (be->dpcm[stream].state != SND_SOC_DPCM_STATE_HW_PARAMS) &&
		   (be->dpcm[stream].state != SND_SOC_DPCM_STATE_HW_FREE) &&
		   (be->dpcm[stream].state != SND_SOC_DPCM_STATE_STOP))
			जारी;

		soc_pcm_hw_मुक्त(be_substream);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dpcm_fe_dai_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *fe = asoc_substream_to_rtd(substream);
	पूर्णांक ret, stream = substream->stream;

	mutex_lock_nested(&fe->card->mutex, SND_SOC_CARD_CLASS_RUNTIME);
	dpcm_set_fe_update_state(fe, stream, SND_SOC_DPCM_UPDATE_FE);

	स_नकल(&fe->dpcm[stream].hw_params, params,
			माप(काष्ठा snd_pcm_hw_params));
	ret = dpcm_be_dai_hw_params(fe, stream);
	अगर (ret < 0)
		जाओ out;

	dev_dbg(fe->dev, "ASoC: hw_params FE %s rate %d chan %x fmt %d\n",
			fe->dai_link->name, params_rate(params),
			params_channels(params), params_क्रमmat(params));

	/* call hw_params on the frontend */
	ret = soc_pcm_hw_params(substream, params);
	अगर (ret < 0)
		dpcm_be_dai_hw_मुक्त(fe, stream);
	अन्यथा
		fe->dpcm[stream].state = SND_SOC_DPCM_STATE_HW_PARAMS;

out:
	dpcm_set_fe_update_state(fe, stream, SND_SOC_DPCM_UPDATE_NO);
	mutex_unlock(&fe->card->mutex);

	अगर (ret < 0)
		dev_err(fe->dev, "ASoC: %s failed (%d)\n", __func__, ret);

	वापस ret;
पूर्ण

पूर्णांक dpcm_be_dai_trigger(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक stream,
			       पूर्णांक cmd)
अणु
	काष्ठा snd_soc_pcm_runसमय *be;
	काष्ठा snd_soc_dpcm *dpcm;
	पूर्णांक ret = 0;

	क्रम_each_dpcm_be(fe, stream, dpcm) अणु
		काष्ठा snd_pcm_substream *be_substream;

		be = dpcm->be;
		be_substream = snd_soc_dpcm_get_substream(be, stream);

		/* is this op क्रम this BE ? */
		अगर (!snd_soc_dpcm_be_can_update(fe, be, stream))
			जारी;

		dev_dbg(be->dev, "ASoC: trigger BE %s cmd %d\n",
			be->dai_link->name, cmd);

		चयन (cmd) अणु
		हाल SNDRV_PCM_TRIGGER_START:
			अगर ((be->dpcm[stream].state != SND_SOC_DPCM_STATE_PREPARE) &&
			    (be->dpcm[stream].state != SND_SOC_DPCM_STATE_STOP) &&
			    (be->dpcm[stream].state != SND_SOC_DPCM_STATE_PAUSED))
				जारी;

			ret = soc_pcm_trigger(be_substream, cmd);
			अगर (ret)
				जाओ end;

			be->dpcm[stream].state = SND_SOC_DPCM_STATE_START;
			अवरोध;
		हाल SNDRV_PCM_TRIGGER_RESUME:
			अगर ((be->dpcm[stream].state != SND_SOC_DPCM_STATE_SUSPEND))
				जारी;

			ret = soc_pcm_trigger(be_substream, cmd);
			अगर (ret)
				जाओ end;

			be->dpcm[stream].state = SND_SOC_DPCM_STATE_START;
			अवरोध;
		हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
			अगर ((be->dpcm[stream].state != SND_SOC_DPCM_STATE_PAUSED))
				जारी;

			ret = soc_pcm_trigger(be_substream, cmd);
			अगर (ret)
				जाओ end;

			be->dpcm[stream].state = SND_SOC_DPCM_STATE_START;
			अवरोध;
		हाल SNDRV_PCM_TRIGGER_STOP:
			अगर ((be->dpcm[stream].state != SND_SOC_DPCM_STATE_START) &&
			    (be->dpcm[stream].state != SND_SOC_DPCM_STATE_PAUSED))
				जारी;

			अगर (!snd_soc_dpcm_can_be_मुक्त_stop(fe, be, stream))
				जारी;

			ret = soc_pcm_trigger(be_substream, cmd);
			अगर (ret)
				जाओ end;

			be->dpcm[stream].state = SND_SOC_DPCM_STATE_STOP;
			अवरोध;
		हाल SNDRV_PCM_TRIGGER_SUSPEND:
			अगर (be->dpcm[stream].state != SND_SOC_DPCM_STATE_START)
				जारी;

			अगर (!snd_soc_dpcm_can_be_मुक्त_stop(fe, be, stream))
				जारी;

			ret = soc_pcm_trigger(be_substream, cmd);
			अगर (ret)
				जाओ end;

			be->dpcm[stream].state = SND_SOC_DPCM_STATE_SUSPEND;
			अवरोध;
		हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
			अगर (be->dpcm[stream].state != SND_SOC_DPCM_STATE_START)
				जारी;

			अगर (!snd_soc_dpcm_can_be_मुक्त_stop(fe, be, stream))
				जारी;

			ret = soc_pcm_trigger(be_substream, cmd);
			अगर (ret)
				जाओ end;

			be->dpcm[stream].state = SND_SOC_DPCM_STATE_PAUSED;
			अवरोध;
		पूर्ण
	पूर्ण
end:
	अगर (ret < 0)
		dev_err(fe->dev, "ASoC: %s() failed at %s (%d)\n",
			__func__, be->dai_link->name, ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dpcm_be_dai_trigger);

अटल पूर्णांक dpcm_dai_trigger_fe_be(काष्ठा snd_pcm_substream *substream,
				  पूर्णांक cmd, bool fe_first)
अणु
	काष्ठा snd_soc_pcm_runसमय *fe = asoc_substream_to_rtd(substream);
	पूर्णांक ret;

	/* call trigger on the frontend beक्रमe the backend. */
	अगर (fe_first) अणु
		dev_dbg(fe->dev, "ASoC: pre trigger FE %s cmd %d\n",
			fe->dai_link->name, cmd);

		ret = soc_pcm_trigger(substream, cmd);
		अगर (ret < 0)
			वापस ret;

		ret = dpcm_be_dai_trigger(fe, substream->stream, cmd);
		वापस ret;
	पूर्ण

	/* call trigger on the frontend after the backend. */
	ret = dpcm_be_dai_trigger(fe, substream->stream, cmd);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(fe->dev, "ASoC: post trigger FE %s cmd %d\n",
		fe->dai_link->name, cmd);

	ret = soc_pcm_trigger(substream, cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक dpcm_fe_dai_करो_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_soc_pcm_runसमय *fe = asoc_substream_to_rtd(substream);
	पूर्णांक stream = substream->stream;
	पूर्णांक ret = 0;
	क्रमागत snd_soc_dpcm_trigger trigger = fe->dai_link->trigger[stream];

	fe->dpcm[stream].runसमय_update = SND_SOC_DPCM_UPDATE_FE;

	चयन (trigger) अणु
	हाल SND_SOC_DPCM_TRIGGER_PRE:
		चयन (cmd) अणु
		हाल SNDRV_PCM_TRIGGER_START:
		हाल SNDRV_PCM_TRIGGER_RESUME:
		हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		हाल SNDRV_PCM_TRIGGER_DRAIN:
			ret = dpcm_dai_trigger_fe_be(substream, cmd, true);
			अवरोध;
		हाल SNDRV_PCM_TRIGGER_STOP:
		हाल SNDRV_PCM_TRIGGER_SUSPEND:
		हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
			ret = dpcm_dai_trigger_fe_be(substream, cmd, false);
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DPCM_TRIGGER_POST:
		चयन (cmd) अणु
		हाल SNDRV_PCM_TRIGGER_START:
		हाल SNDRV_PCM_TRIGGER_RESUME:
		हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		हाल SNDRV_PCM_TRIGGER_DRAIN:
			ret = dpcm_dai_trigger_fe_be(substream, cmd, false);
			अवरोध;
		हाल SNDRV_PCM_TRIGGER_STOP:
		हाल SNDRV_PCM_TRIGGER_SUSPEND:
		हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
			ret = dpcm_dai_trigger_fe_be(substream, cmd, true);
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DPCM_TRIGGER_BESPOKE:
		/* bespoke trigger() - handles both FE and BEs */

		dev_dbg(fe->dev, "ASoC: bespoke trigger FE %s cmd %d\n",
				fe->dai_link->name, cmd);

		ret = snd_soc_pcm_dai_bespoke_trigger(substream, cmd);
		अवरोध;
	शेष:
		dev_err(fe->dev, "ASoC: invalid trigger cmd %d for %s\n", cmd,
				fe->dai_link->name);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(fe->dev, "ASoC: trigger FE cmd: %d failed: %d\n",
			cmd, ret);
		जाओ out;
	पूर्ण

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		fe->dpcm[stream].state = SND_SOC_DPCM_STATE_START;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		fe->dpcm[stream].state = SND_SOC_DPCM_STATE_STOP;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		fe->dpcm[stream].state = SND_SOC_DPCM_STATE_PAUSED;
		अवरोध;
	पूर्ण

out:
	fe->dpcm[stream].runसमय_update = SND_SOC_DPCM_UPDATE_NO;
	वापस ret;
पूर्ण

अटल पूर्णांक dpcm_fe_dai_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_soc_pcm_runसमय *fe = asoc_substream_to_rtd(substream);
	पूर्णांक stream = substream->stream;

	/* अगर FE's runtime_update is already set, we're in race;
	 * process this trigger later at निकास
	 */
	अगर (fe->dpcm[stream].runसमय_update != SND_SOC_DPCM_UPDATE_NO) अणु
		fe->dpcm[stream].trigger_pending = cmd + 1;
		वापस 0; /* delayed, assuming it's successful */
	पूर्ण

	/* we're alone, let's trigger */
	वापस dpcm_fe_dai_करो_trigger(substream, cmd);
पूर्ण

पूर्णांक dpcm_be_dai_prepare(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक stream)
अणु
	काष्ठा snd_soc_dpcm *dpcm;
	पूर्णांक ret = 0;

	क्रम_each_dpcm_be(fe, stream, dpcm) अणु

		काष्ठा snd_soc_pcm_runसमय *be = dpcm->be;
		काष्ठा snd_pcm_substream *be_substream =
			snd_soc_dpcm_get_substream(be, stream);

		/* is this op क्रम this BE ? */
		अगर (!snd_soc_dpcm_be_can_update(fe, be, stream))
			जारी;

		अगर ((be->dpcm[stream].state != SND_SOC_DPCM_STATE_HW_PARAMS) &&
		    (be->dpcm[stream].state != SND_SOC_DPCM_STATE_STOP) &&
		    (be->dpcm[stream].state != SND_SOC_DPCM_STATE_SUSPEND) &&
		    (be->dpcm[stream].state != SND_SOC_DPCM_STATE_PAUSED))
			जारी;

		dev_dbg(be->dev, "ASoC: prepare BE %s\n",
			be->dai_link->name);

		ret = soc_pcm_prepare(be_substream);
		अगर (ret < 0)
			अवरोध;

		be->dpcm[stream].state = SND_SOC_DPCM_STATE_PREPARE;
	पूर्ण

	अगर (ret < 0)
		dev_err(fe->dev, "ASoC: %s() failed (%d)\n", __func__, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक dpcm_fe_dai_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *fe = asoc_substream_to_rtd(substream);
	पूर्णांक stream = substream->stream, ret = 0;

	mutex_lock_nested(&fe->card->mutex, SND_SOC_CARD_CLASS_RUNTIME);

	dev_dbg(fe->dev, "ASoC: prepare FE %s\n", fe->dai_link->name);

	dpcm_set_fe_update_state(fe, stream, SND_SOC_DPCM_UPDATE_FE);

	/* there is no poपूर्णांक preparing this FE अगर there are no BEs */
	अगर (list_empty(&fe->dpcm[stream].be_clients)) अणु
		dev_err(fe->dev, "ASoC: no backend DAIs enabled for %s\n",
				fe->dai_link->name);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = dpcm_be_dai_prepare(fe, stream);
	अगर (ret < 0)
		जाओ out;

	/* call prepare on the frontend */
	ret = soc_pcm_prepare(substream);
	अगर (ret < 0)
		जाओ out;

	fe->dpcm[stream].state = SND_SOC_DPCM_STATE_PREPARE;

out:
	dpcm_set_fe_update_state(fe, stream, SND_SOC_DPCM_UPDATE_NO);
	mutex_unlock(&fe->card->mutex);

	अगर (ret < 0)
		dev_err(fe->dev, "ASoC: %s() failed (%d)\n", __func__, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक dpcm_run_update_shutकरोwn(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक stream)
अणु
	काष्ठा snd_pcm_substream *substream =
		snd_soc_dpcm_get_substream(fe, stream);
	क्रमागत snd_soc_dpcm_trigger trigger = fe->dai_link->trigger[stream];
	पूर्णांक err;

	dev_dbg(fe->dev, "ASoC: runtime %s close on FE %s\n",
			stream ? "capture" : "playback", fe->dai_link->name);

	अगर (trigger == SND_SOC_DPCM_TRIGGER_BESPOKE) अणु
		/* call bespoke trigger - FE takes care of all BE triggers */
		dev_dbg(fe->dev, "ASoC: bespoke trigger FE %s cmd stop\n",
				fe->dai_link->name);

		err = snd_soc_pcm_dai_bespoke_trigger(substream, SNDRV_PCM_TRIGGER_STOP);
	पूर्ण अन्यथा अणु
		dev_dbg(fe->dev, "ASoC: trigger FE %s cmd stop\n",
			fe->dai_link->name);

		err = dpcm_be_dai_trigger(fe, stream, SNDRV_PCM_TRIGGER_STOP);
	पूर्ण

	dpcm_be_dai_hw_मुक्त(fe, stream);

	dpcm_be_dai_shutकरोwn(fe, stream);

	/* run the stream event क्रम each BE */
	dpcm_dapm_stream_event(fe, stream, SND_SOC_DAPM_STREAM_NOP);

	अगर (err < 0)
		dev_err(fe->dev, "ASoC: %s() failed (%d)\n", __func__, err);

	वापस err;
पूर्ण

अटल पूर्णांक dpcm_run_update_startup(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक stream)
अणु
	काष्ठा snd_pcm_substream *substream =
		snd_soc_dpcm_get_substream(fe, stream);
	काष्ठा snd_soc_dpcm *dpcm;
	क्रमागत snd_soc_dpcm_trigger trigger = fe->dai_link->trigger[stream];
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	dev_dbg(fe->dev, "ASoC: runtime %s open on FE %s\n",
			stream ? "capture" : "playback", fe->dai_link->name);

	/* Only start the BE अगर the FE is पढ़ोy */
	अगर (fe->dpcm[stream].state == SND_SOC_DPCM_STATE_HW_FREE ||
		fe->dpcm[stream].state == SND_SOC_DPCM_STATE_CLOSE) अणु
		dev_err(fe->dev, "ASoC: FE %s is not ready %d\n",
			fe->dai_link->name, fe->dpcm[stream].state);
		ret = -EINVAL;
		जाओ disconnect;
	पूर्ण

	/* startup must always be called क्रम new BEs */
	ret = dpcm_be_dai_startup(fe, stream);
	अगर (ret < 0)
		जाओ disconnect;

	/* keep going अगर FE state is > खोलो */
	अगर (fe->dpcm[stream].state == SND_SOC_DPCM_STATE_OPEN)
		वापस 0;

	ret = dpcm_be_dai_hw_params(fe, stream);
	अगर (ret < 0)
		जाओ बंद;

	/* keep going अगर FE state is > hw_params */
	अगर (fe->dpcm[stream].state == SND_SOC_DPCM_STATE_HW_PARAMS)
		वापस 0;

	ret = dpcm_be_dai_prepare(fe, stream);
	अगर (ret < 0)
		जाओ hw_मुक्त;

	/* run the stream event क्रम each BE */
	dpcm_dapm_stream_event(fe, stream, SND_SOC_DAPM_STREAM_NOP);

	/* keep going अगर FE state is > prepare */
	अगर (fe->dpcm[stream].state == SND_SOC_DPCM_STATE_PREPARE ||
		fe->dpcm[stream].state == SND_SOC_DPCM_STATE_STOP)
		वापस 0;

	अगर (trigger == SND_SOC_DPCM_TRIGGER_BESPOKE) अणु
		/* call trigger on the frontend - FE takes care of all BE triggers */
		dev_dbg(fe->dev, "ASoC: bespoke trigger FE %s cmd start\n",
				fe->dai_link->name);

		ret = snd_soc_pcm_dai_bespoke_trigger(substream, SNDRV_PCM_TRIGGER_START);
		अगर (ret < 0)
			जाओ hw_मुक्त;
	पूर्ण अन्यथा अणु
		dev_dbg(fe->dev, "ASoC: trigger FE %s cmd start\n",
			fe->dai_link->name);

		ret = dpcm_be_dai_trigger(fe, stream,
					SNDRV_PCM_TRIGGER_START);
		अगर (ret < 0)
			जाओ hw_मुक्त;
	पूर्ण

	वापस 0;

hw_मुक्त:
	dpcm_be_dai_hw_मुक्त(fe, stream);
बंद:
	dpcm_be_dai_shutकरोwn(fe, stream);
disconnect:
	/* disconnect any pending BEs */
	spin_lock_irqsave(&fe->card->dpcm_lock, flags);
	क्रम_each_dpcm_be(fe, stream, dpcm) अणु
		काष्ठा snd_soc_pcm_runसमय *be = dpcm->be;

		/* is this op क्रम this BE ? */
		अगर (!snd_soc_dpcm_be_can_update(fe, be, stream))
			जारी;

		अगर (be->dpcm[stream].state == SND_SOC_DPCM_STATE_CLOSE ||
			be->dpcm[stream].state == SND_SOC_DPCM_STATE_NEW)
				dpcm->state = SND_SOC_DPCM_LINK_STATE_FREE;
	पूर्ण
	spin_unlock_irqrestore(&fe->card->dpcm_lock, flags);

	अगर (ret < 0)
		dev_err(fe->dev, "ASoC: %s() failed (%d)\n", __func__, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक soc_dpcm_fe_runसमय_update(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक new)
अणु
	काष्ठा snd_soc_dapm_widget_list *list;
	पूर्णांक stream;
	पूर्णांक count, paths;

	अगर (!fe->dai_link->dynamic)
		वापस 0;

	अगर (fe->num_cpus > 1) अणु
		dev_err(fe->dev,
			"%s doesn't support Multi CPU yet\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* only check active links */
	अगर (!snd_soc_dai_active(asoc_rtd_to_cpu(fe, 0)))
		वापस 0;

	/* DAPM sync will call this to update DSP paths */
	dev_dbg(fe->dev, "ASoC: DPCM %s runtime update for FE %s\n",
		new ? "new" : "old", fe->dai_link->name);

	क्रम_each_pcm_streams(stream) अणु

		/* skip अगर FE करोesn't have playback/capture capability */
		अगर (!snd_soc_dai_stream_valid(asoc_rtd_to_cpu(fe, 0),   stream) ||
		    !snd_soc_dai_stream_valid(asoc_rtd_to_codec(fe, 0), stream))
			जारी;

		/* skip अगर FE isn't currently playing/capturing */
		अगर (!snd_soc_dai_stream_active(asoc_rtd_to_cpu(fe, 0), stream) ||
		    !snd_soc_dai_stream_active(asoc_rtd_to_codec(fe, 0), stream))
			जारी;

		paths = dpcm_path_get(fe, stream, &list);
		अगर (paths < 0)
			वापस paths;

		/* update any playback/capture paths */
		count = dpcm_process_paths(fe, stream, &list, new);
		अगर (count) अणु
			dpcm_set_fe_update_state(fe, stream, SND_SOC_DPCM_UPDATE_BE);
			अगर (new)
				dpcm_run_update_startup(fe, stream);
			अन्यथा
				dpcm_run_update_shutकरोwn(fe, stream);
			dpcm_set_fe_update_state(fe, stream, SND_SOC_DPCM_UPDATE_NO);

			dpcm_clear_pending_state(fe, stream);
			dpcm_be_disconnect(fe, stream);
		पूर्ण

		dpcm_path_put(&list);
	पूर्ण

	वापस 0;
पूर्ण

/* Called by DAPM mixer/mux changes to update audio routing between PCMs and
 * any DAI links.
 */
पूर्णांक snd_soc_dpcm_runसमय_update(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_pcm_runसमय *fe;
	पूर्णांक ret = 0;

	mutex_lock_nested(&card->mutex, SND_SOC_CARD_CLASS_RUNTIME);
	/* shutकरोwn all old paths first */
	क्रम_each_card_rtds(card, fe) अणु
		ret = soc_dpcm_fe_runसमय_update(fe, 0);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* bring new paths up */
	क्रम_each_card_rtds(card, fe) अणु
		ret = soc_dpcm_fe_runसमय_update(fe, 1);
		अगर (ret)
			जाओ out;
	पूर्ण

out:
	mutex_unlock(&card->mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dpcm_runसमय_update);

अटल व्योम dpcm_fe_dai_cleanup(काष्ठा snd_pcm_substream *fe_substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *fe = asoc_substream_to_rtd(fe_substream);
	काष्ठा snd_soc_dpcm *dpcm;
	पूर्णांक stream = fe_substream->stream;

	/* mark FE's links पढ़ोy to prune */
	क्रम_each_dpcm_be(fe, stream, dpcm)
		dpcm->state = SND_SOC_DPCM_LINK_STATE_FREE;

	dpcm_be_disconnect(fe, stream);

	fe->dpcm[stream].runसमय = शून्य;
पूर्ण

अटल पूर्णांक dpcm_fe_dai_बंद(काष्ठा snd_pcm_substream *fe_substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *fe = asoc_substream_to_rtd(fe_substream);
	पूर्णांक ret;

	mutex_lock_nested(&fe->card->mutex, SND_SOC_CARD_CLASS_RUNTIME);
	ret = dpcm_fe_dai_shutकरोwn(fe_substream);

	dpcm_fe_dai_cleanup(fe_substream);

	mutex_unlock(&fe->card->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dpcm_fe_dai_खोलो(काष्ठा snd_pcm_substream *fe_substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *fe = asoc_substream_to_rtd(fe_substream);
	काष्ठा snd_soc_dapm_widget_list *list;
	पूर्णांक ret;
	पूर्णांक stream = fe_substream->stream;

	mutex_lock_nested(&fe->card->mutex, SND_SOC_CARD_CLASS_RUNTIME);
	fe->dpcm[stream].runसमय = fe_substream->runसमय;

	ret = dpcm_path_get(fe, stream, &list);
	अगर (ret < 0)
		जाओ खोलो_end;

	/* calculate valid and active FE <-> BE dpcms */
	dpcm_process_paths(fe, stream, &list, 1);

	ret = dpcm_fe_dai_startup(fe_substream);
	अगर (ret < 0)
		dpcm_fe_dai_cleanup(fe_substream);

	dpcm_clear_pending_state(fe, stream);
	dpcm_path_put(&list);
खोलो_end:
	mutex_unlock(&fe->card->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक soc_get_playback_capture(काष्ठा snd_soc_pcm_runसमय *rtd,
				    पूर्णांक *playback, पूर्णांक *capture)
अणु
	काष्ठा snd_soc_dai *codec_dai;
	काष्ठा snd_soc_dai *cpu_dai;
	पूर्णांक stream;
	पूर्णांक i;

	अगर (rtd->dai_link->dynamic && rtd->num_cpus > 1) अणु
		dev_err(rtd->dev,
			"DPCM doesn't support Multi CPU for Front-Ends yet\n");
		वापस -EINVAL;
	पूर्ण

	अगर (rtd->dai_link->dynamic || rtd->dai_link->no_pcm) अणु
		अगर (rtd->dai_link->dpcm_playback) अणु
			stream = SNDRV_PCM_STREAM_PLAYBACK;

			क्रम_each_rtd_cpu_dais(rtd, i, cpu_dai) अणु
				अगर (snd_soc_dai_stream_valid(cpu_dai, stream)) अणु
					*playback = 1;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (!*playback) अणु
				dev_err(rtd->card->dev,
					"No CPU DAIs support playback for stream %s\n",
					rtd->dai_link->stream_name);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अगर (rtd->dai_link->dpcm_capture) अणु
			stream = SNDRV_PCM_STREAM_CAPTURE;

			क्रम_each_rtd_cpu_dais(rtd, i, cpu_dai) अणु
				अगर (snd_soc_dai_stream_valid(cpu_dai, stream)) अणु
					*capture = 1;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (!*capture) अणु
				dev_err(rtd->card->dev,
					"No CPU DAIs support capture for stream %s\n",
					rtd->dai_link->stream_name);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Adapt stream क्रम codec2codec links */
		पूर्णांक cpu_capture = rtd->dai_link->params ?
			SNDRV_PCM_STREAM_PLAYBACK : SNDRV_PCM_STREAM_CAPTURE;
		पूर्णांक cpu_playback = rtd->dai_link->params ?
			SNDRV_PCM_STREAM_CAPTURE : SNDRV_PCM_STREAM_PLAYBACK;

		क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
			अगर (rtd->num_cpus == 1) अणु
				cpu_dai = asoc_rtd_to_cpu(rtd, 0);
			पूर्ण अन्यथा अगर (rtd->num_cpus == rtd->num_codecs) अणु
				cpu_dai = asoc_rtd_to_cpu(rtd, i);
			पूर्ण अन्यथा अणु
				dev_err(rtd->card->dev,
					"N cpus to M codecs link is not supported yet\n");
				वापस -EINVAL;
			पूर्ण

			अगर (snd_soc_dai_stream_valid(codec_dai, SNDRV_PCM_STREAM_PLAYBACK) &&
			    snd_soc_dai_stream_valid(cpu_dai,   cpu_playback))
				*playback = 1;
			अगर (snd_soc_dai_stream_valid(codec_dai, SNDRV_PCM_STREAM_CAPTURE) &&
			    snd_soc_dai_stream_valid(cpu_dai,   cpu_capture))
				*capture = 1;
		पूर्ण
	पूर्ण

	अगर (rtd->dai_link->playback_only) अणु
		*playback = 1;
		*capture = 0;
	पूर्ण

	अगर (rtd->dai_link->capture_only) अणु
		*playback = 0;
		*capture = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक soc_create_pcm(काष्ठा snd_pcm **pcm,
			  काष्ठा snd_soc_pcm_runसमय *rtd,
			  पूर्णांक playback, पूर्णांक capture, पूर्णांक num)
अणु
	अक्षर new_name[64];
	पूर्णांक ret;

	/* create the PCM */
	अगर (rtd->dai_link->params) अणु
		snम_लिखो(new_name, माप(new_name), "codec2codec(%s)",
			 rtd->dai_link->stream_name);

		ret = snd_pcm_new_पूर्णांकernal(rtd->card->snd_card, new_name, num,
					   playback, capture, pcm);
	पूर्ण अन्यथा अगर (rtd->dai_link->no_pcm) अणु
		snम_लिखो(new_name, माप(new_name), "(%s)",
			rtd->dai_link->stream_name);

		ret = snd_pcm_new_पूर्णांकernal(rtd->card->snd_card, new_name, num,
				playback, capture, pcm);
	पूर्ण अन्यथा अणु
		अगर (rtd->dai_link->dynamic)
			snम_लिखो(new_name, माप(new_name), "%s (*)",
				rtd->dai_link->stream_name);
		अन्यथा
			snम_लिखो(new_name, माप(new_name), "%s %s-%d",
				rtd->dai_link->stream_name,
				soc_codec_dai_name(rtd), num);

		ret = snd_pcm_new(rtd->card->snd_card, new_name, num, playback,
			capture, pcm);
	पूर्ण
	अगर (ret < 0) अणु
		dev_err(rtd->card->dev, "ASoC: can't create pcm %s for dailink %s: %d\n",
			new_name, rtd->dai_link->name, ret);
		वापस ret;
	पूर्ण
	dev_dbg(rtd->card->dev, "ASoC: registered pcm #%d %s\n",num, new_name);

	वापस 0;
पूर्ण

/* create a new pcm */
पूर्णांक soc_new_pcm(काष्ठा snd_soc_pcm_runसमय *rtd, पूर्णांक num)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा snd_pcm *pcm;
	पूर्णांक ret = 0, playback = 0, capture = 0;
	पूर्णांक i;

	ret = soc_get_playback_capture(rtd, &playback, &capture);
	अगर (ret < 0)
		वापस ret;

	ret = soc_create_pcm(&pcm, rtd, playback, capture, num);
	अगर (ret < 0)
		वापस ret;

	/* DAPM dai link stream work */
	अगर (rtd->dai_link->params)
		rtd->बंद_delayed_work_func = codec2codec_बंद_delayed_work;
	अन्यथा
		rtd->बंद_delayed_work_func = snd_soc_बंद_delayed_work;

	rtd->pcm = pcm;
	pcm->nonatomic = rtd->dai_link->nonatomic;
	pcm->निजी_data = rtd;

	अगर (rtd->dai_link->no_pcm || rtd->dai_link->params) अणु
		अगर (playback)
			pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream->निजी_data = rtd;
		अगर (capture)
			pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream->निजी_data = rtd;
		जाओ out;
	पूर्ण

	/* ASoC PCM operations */
	अगर (rtd->dai_link->dynamic) अणु
		rtd->ops.खोलो		= dpcm_fe_dai_खोलो;
		rtd->ops.hw_params	= dpcm_fe_dai_hw_params;
		rtd->ops.prepare	= dpcm_fe_dai_prepare;
		rtd->ops.trigger	= dpcm_fe_dai_trigger;
		rtd->ops.hw_मुक्त	= dpcm_fe_dai_hw_मुक्त;
		rtd->ops.बंद		= dpcm_fe_dai_बंद;
		rtd->ops.poपूर्णांकer	= soc_pcm_poपूर्णांकer;
	पूर्ण अन्यथा अणु
		rtd->ops.खोलो		= soc_pcm_खोलो;
		rtd->ops.hw_params	= soc_pcm_hw_params;
		rtd->ops.prepare	= soc_pcm_prepare;
		rtd->ops.trigger	= soc_pcm_trigger;
		rtd->ops.hw_मुक्त	= soc_pcm_hw_मुक्त;
		rtd->ops.बंद		= soc_pcm_बंद;
		rtd->ops.poपूर्णांकer	= soc_pcm_poपूर्णांकer;
	पूर्ण

	क्रम_each_rtd_components(rtd, i, component) अणु
		स्थिर काष्ठा snd_soc_component_driver *drv = component->driver;

		अगर (drv->ioctl)
			rtd->ops.ioctl		= snd_soc_pcm_component_ioctl;
		अगर (drv->sync_stop)
			rtd->ops.sync_stop	= snd_soc_pcm_component_sync_stop;
		अगर (drv->copy_user)
			rtd->ops.copy_user	= snd_soc_pcm_component_copy_user;
		अगर (drv->page)
			rtd->ops.page		= snd_soc_pcm_component_page;
		अगर (drv->mmap)
			rtd->ops.mmap		= snd_soc_pcm_component_mmap;
		अगर (drv->ack)
			rtd->ops.ack            = snd_soc_pcm_component_ack;
	पूर्ण

	अगर (playback)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &rtd->ops);

	अगर (capture)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &rtd->ops);

	ret = snd_soc_pcm_component_new(rtd);
	अगर (ret < 0)
		वापस ret;

	pcm->no_device_suspend = true;
out:
	dev_dbg(rtd->card->dev, "%s <-> %s mapping ok\n",
		soc_codec_dai_name(rtd), soc_cpu_dai_name(rtd));
	वापस ret;
पूर्ण

/* is the current PCM operation क्रम this FE ? */
पूर्णांक snd_soc_dpcm_fe_can_update(काष्ठा snd_soc_pcm_runसमय *fe, पूर्णांक stream)
अणु
	अगर (fe->dpcm[stream].runसमय_update == SND_SOC_DPCM_UPDATE_FE)
		वापस 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dpcm_fe_can_update);

/* is the current PCM operation क्रम this BE ? */
पूर्णांक snd_soc_dpcm_be_can_update(काष्ठा snd_soc_pcm_runसमय *fe,
		काष्ठा snd_soc_pcm_runसमय *be, पूर्णांक stream)
अणु
	अगर ((fe->dpcm[stream].runसमय_update == SND_SOC_DPCM_UPDATE_FE) ||
	   ((fe->dpcm[stream].runसमय_update == SND_SOC_DPCM_UPDATE_BE) &&
		  be->dpcm[stream].runसमय_update))
		वापस 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dpcm_be_can_update);

/* get the substream क्रम this BE */
काष्ठा snd_pcm_substream *
	snd_soc_dpcm_get_substream(काष्ठा snd_soc_pcm_runसमय *be, पूर्णांक stream)
अणु
	वापस be->pcm->streams[stream].substream;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dpcm_get_substream);

अटल पूर्णांक snd_soc_dpcm_check_state(काष्ठा snd_soc_pcm_runसमय *fe,
				    काष्ठा snd_soc_pcm_runसमय *be,
				    पूर्णांक stream,
				    स्थिर क्रमागत snd_soc_dpcm_state *states,
				    पूर्णांक num_states)
अणु
	काष्ठा snd_soc_dpcm *dpcm;
	पूर्णांक state;
	पूर्णांक ret = 1;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&fe->card->dpcm_lock, flags);
	क्रम_each_dpcm_fe(be, stream, dpcm) अणु

		अगर (dpcm->fe == fe)
			जारी;

		state = dpcm->fe->dpcm[stream].state;
		क्रम (i = 0; i < num_states; i++) अणु
			अगर (state == states[i]) अणु
				ret = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&fe->card->dpcm_lock, flags);

	/* it's safe to करो this BE DAI */
	वापस ret;
पूर्ण

/*
 * We can only hw_मुक्त, stop, छोड़ो or suspend a BE DAI अगर any of it's FE
 * are not running, छोड़ोd or suspended क्रम the specअगरied stream direction.
 */
पूर्णांक snd_soc_dpcm_can_be_मुक्त_stop(काष्ठा snd_soc_pcm_runसमय *fe,
		काष्ठा snd_soc_pcm_runसमय *be, पूर्णांक stream)
अणु
	स्थिर क्रमागत snd_soc_dpcm_state state[] = अणु
		SND_SOC_DPCM_STATE_START,
		SND_SOC_DPCM_STATE_PAUSED,
		SND_SOC_DPCM_STATE_SUSPEND,
	पूर्ण;

	वापस snd_soc_dpcm_check_state(fe, be, stream, state, ARRAY_SIZE(state));
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dpcm_can_be_मुक्त_stop);

/*
 * We can only change hw params a BE DAI अगर any of it's FE are not prepared,
 * running, छोड़ोd or suspended क्रम the specअगरied stream direction.
 */
पूर्णांक snd_soc_dpcm_can_be_params(काष्ठा snd_soc_pcm_runसमय *fe,
		काष्ठा snd_soc_pcm_runसमय *be, पूर्णांक stream)
अणु
	स्थिर क्रमागत snd_soc_dpcm_state state[] = अणु
		SND_SOC_DPCM_STATE_START,
		SND_SOC_DPCM_STATE_PAUSED,
		SND_SOC_DPCM_STATE_SUSPEND,
		SND_SOC_DPCM_STATE_PREPARE,
	पूर्ण;

	वापस snd_soc_dpcm_check_state(fe, be, stream, state, ARRAY_SIZE(state));
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dpcm_can_be_params);
