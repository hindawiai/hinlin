<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// soc-compress.c  --  ALSA SoC Compress
//
// Copyright (C) 2012 Intel Corp.
//
// Authors: Namarta Kohli <namartax.kohli@पूर्णांकel.com>
//          Ramesh Babu K V <ramesh.babu@linux.पूर्णांकel.com>
//          Vinod Koul <vinod.koul@linux.पूर्णांकel.com>

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <sound/core.h>
#समावेश <sound/compress_params.h>
#समावेश <sound/compress_driver.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc-dpcm.h>
#समावेश <sound/soc-link.h>
#समावेश <linux/pm_runसमय.स>

अटल पूर्णांक soc_compr_clean(काष्ठा snd_compr_stream *cstream, पूर्णांक rollback)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक stream = cstream->direction; /* SND_COMPRESS_xxx is same as SNDRV_PCM_STREAM_xxx */

	mutex_lock_nested(&rtd->card->pcm_mutex, rtd->card->pcm_subclass);

	अगर (!rollback)
		snd_soc_runसमय_deactivate(rtd, stream);

	snd_soc_dai_digital_mute(codec_dai, 1, stream);

	अगर (!snd_soc_dai_active(cpu_dai))
		cpu_dai->rate = 0;

	अगर (!snd_soc_dai_active(codec_dai))
		codec_dai->rate = 0;

	snd_soc_link_compr_shutकरोwn(cstream, rollback);

	snd_soc_component_compr_मुक्त(cstream, rollback);

	snd_soc_dai_compr_shutकरोwn(cpu_dai, cstream, rollback);

	अगर (!rollback)
		snd_soc_dapm_stream_stop(rtd, stream);

	mutex_unlock(&rtd->card->pcm_mutex);

	snd_soc_pcm_component_pm_runसमय_put(rtd, cstream, rollback);

	वापस 0;
पूर्ण

अटल पूर्णांक soc_compr_मुक्त(काष्ठा snd_compr_stream *cstream)
अणु
	वापस soc_compr_clean(cstream, 0);
पूर्ण

अटल पूर्णांक soc_compr_खोलो(काष्ठा snd_compr_stream *cstream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक stream = cstream->direction; /* SND_COMPRESS_xxx is same as SNDRV_PCM_STREAM_xxx */
	पूर्णांक ret;

	ret = snd_soc_pcm_component_pm_runसमय_get(rtd, cstream);
	अगर (ret < 0)
		जाओ err_no_lock;

	mutex_lock_nested(&rtd->card->pcm_mutex, rtd->card->pcm_subclass);

	ret = snd_soc_dai_compr_startup(cpu_dai, cstream);
	अगर (ret < 0)
		जाओ err;

	ret = snd_soc_component_compr_खोलो(cstream);
	अगर (ret < 0)
		जाओ err;

	ret = snd_soc_link_compr_startup(cstream);
	अगर (ret < 0)
		जाओ err;

	snd_soc_runसमय_activate(rtd, stream);
err:
	mutex_unlock(&rtd->card->pcm_mutex);
err_no_lock:
	अगर (ret < 0)
		soc_compr_clean(cstream, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक soc_compr_खोलो_fe(काष्ठा snd_compr_stream *cstream)
अणु
	काष्ठा snd_soc_pcm_runसमय *fe = cstream->निजी_data;
	काष्ठा snd_pcm_substream *fe_substream =
		 fe->pcm->streams[cstream->direction].substream;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(fe, 0);
	काष्ठा snd_soc_dpcm *dpcm;
	काष्ठा snd_soc_dapm_widget_list *list;
	पूर्णांक stream = cstream->direction; /* SND_COMPRESS_xxx is same as SNDRV_PCM_STREAM_xxx */
	पूर्णांक ret;

	mutex_lock_nested(&fe->card->mutex, SND_SOC_CARD_CLASS_RUNTIME);
	fe->dpcm[stream].runसमय = fe_substream->runसमय;

	ret = dpcm_path_get(fe, stream, &list);
	अगर (ret < 0)
		जाओ be_err;

	/* calculate valid and active FE <-> BE dpcms */
	dpcm_process_paths(fe, stream, &list, 1);
	fe->dpcm[stream].runसमय = fe_substream->runसमय;

	fe->dpcm[stream].runसमय_update = SND_SOC_DPCM_UPDATE_FE;

	ret = dpcm_be_dai_startup(fe, stream);
	अगर (ret < 0) अणु
		/* clean up all links */
		क्रम_each_dpcm_be(fe, stream, dpcm)
			dpcm->state = SND_SOC_DPCM_LINK_STATE_FREE;

		dpcm_be_disconnect(fe, stream);
		fe->dpcm[stream].runसमय = शून्य;
		जाओ out;
	पूर्ण

	ret = snd_soc_dai_compr_startup(cpu_dai, cstream);
	अगर (ret < 0)
		जाओ out;

	ret = snd_soc_component_compr_खोलो(cstream);
	अगर (ret < 0)
		जाओ खोलो_err;

	ret = snd_soc_link_compr_startup(cstream);
	अगर (ret < 0)
		जाओ machine_err;

	dpcm_clear_pending_state(fe, stream);
	dpcm_path_put(&list);

	fe->dpcm[stream].state = SND_SOC_DPCM_STATE_OPEN;
	fe->dpcm[stream].runसमय_update = SND_SOC_DPCM_UPDATE_NO;

	mutex_lock_nested(&fe->card->pcm_mutex, fe->card->pcm_subclass);
	snd_soc_runसमय_activate(fe, stream);
	mutex_unlock(&fe->card->pcm_mutex);

	mutex_unlock(&fe->card->mutex);

	वापस 0;

machine_err:
	snd_soc_component_compr_मुक्त(cstream, 1);
खोलो_err:
	snd_soc_dai_compr_shutकरोwn(cpu_dai, cstream, 1);
out:
	dpcm_path_put(&list);
be_err:
	fe->dpcm[stream].runसमय_update = SND_SOC_DPCM_UPDATE_NO;
	mutex_unlock(&fe->card->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक soc_compr_मुक्त_fe(काष्ठा snd_compr_stream *cstream)
अणु
	काष्ठा snd_soc_pcm_runसमय *fe = cstream->निजी_data;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(fe, 0);
	काष्ठा snd_soc_dpcm *dpcm;
	पूर्णांक stream = cstream->direction; /* SND_COMPRESS_xxx is same as SNDRV_PCM_STREAM_xxx */

	mutex_lock_nested(&fe->card->mutex, SND_SOC_CARD_CLASS_RUNTIME);

	mutex_lock_nested(&fe->card->pcm_mutex, fe->card->pcm_subclass);
	snd_soc_runसमय_deactivate(fe, stream);
	mutex_unlock(&fe->card->pcm_mutex);

	fe->dpcm[stream].runसमय_update = SND_SOC_DPCM_UPDATE_FE;

	dpcm_be_dai_hw_मुक्त(fe, stream);

	dpcm_be_dai_shutकरोwn(fe, stream);

	/* mark FE's links पढ़ोy to prune */
	क्रम_each_dpcm_be(fe, stream, dpcm)
		dpcm->state = SND_SOC_DPCM_LINK_STATE_FREE;

	dpcm_dapm_stream_event(fe, stream, SND_SOC_DAPM_STREAM_STOP);

	fe->dpcm[stream].state = SND_SOC_DPCM_STATE_CLOSE;
	fe->dpcm[stream].runसमय_update = SND_SOC_DPCM_UPDATE_NO;

	dpcm_be_disconnect(fe, stream);

	fe->dpcm[stream].runसमय = शून्य;

	snd_soc_link_compr_shutकरोwn(cstream, 0);

	snd_soc_component_compr_मुक्त(cstream, 0);

	snd_soc_dai_compr_shutकरोwn(cpu_dai, cstream, 0);

	mutex_unlock(&fe->card->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक soc_compr_trigger(काष्ठा snd_compr_stream *cstream, पूर्णांक cmd)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक stream = cstream->direction; /* SND_COMPRESS_xxx is same as SNDRV_PCM_STREAM_xxx */
	पूर्णांक ret;

	mutex_lock_nested(&rtd->card->pcm_mutex, rtd->card->pcm_subclass);

	ret = snd_soc_component_compr_trigger(cstream, cmd);
	अगर (ret < 0)
		जाओ out;

	ret = snd_soc_dai_compr_trigger(cpu_dai, cstream, cmd);
	अगर (ret < 0)
		जाओ out;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		snd_soc_dai_digital_mute(codec_dai, 0, stream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		snd_soc_dai_digital_mute(codec_dai, 1, stream);
		अवरोध;
	पूर्ण

out:
	mutex_unlock(&rtd->card->pcm_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक soc_compr_trigger_fe(काष्ठा snd_compr_stream *cstream, पूर्णांक cmd)
अणु
	काष्ठा snd_soc_pcm_runसमय *fe = cstream->निजी_data;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(fe, 0);
	पूर्णांक stream = cstream->direction; /* SND_COMPRESS_xxx is same as SNDRV_PCM_STREAM_xxx */
	पूर्णांक ret;

	अगर (cmd == SND_COMPR_TRIGGER_PARTIAL_DRAIN ||
	    cmd == SND_COMPR_TRIGGER_DRAIN)
		वापस snd_soc_component_compr_trigger(cstream, cmd);

	mutex_lock_nested(&fe->card->mutex, SND_SOC_CARD_CLASS_RUNTIME);

	ret = snd_soc_dai_compr_trigger(cpu_dai, cstream, cmd);
	अगर (ret < 0)
		जाओ out;

	ret = snd_soc_component_compr_trigger(cstream, cmd);
	अगर (ret < 0)
		जाओ out;

	fe->dpcm[stream].runसमय_update = SND_SOC_DPCM_UPDATE_FE;

	ret = dpcm_be_dai_trigger(fe, stream, cmd);

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
	mutex_unlock(&fe->card->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक soc_compr_set_params(काष्ठा snd_compr_stream *cstream,
				काष्ठा snd_compr_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक stream = cstream->direction; /* SND_COMPRESS_xxx is same as SNDRV_PCM_STREAM_xxx */
	पूर्णांक ret;

	mutex_lock_nested(&rtd->card->pcm_mutex, rtd->card->pcm_subclass);

	/*
	 * First we call set_params क्रम the CPU DAI, then the component
	 * driver this should configure the SoC side. If the machine has
	 * compressed ops then we call that as well. The expectation is
	 * that these callbacks will configure everything क्रम this compress
	 * path, like configuring a PCM port क्रम a CODEC.
	 */
	ret = snd_soc_dai_compr_set_params(cpu_dai, cstream, params);
	अगर (ret < 0)
		जाओ err;

	ret = snd_soc_component_compr_set_params(cstream, params);
	अगर (ret < 0)
		जाओ err;

	ret = snd_soc_link_compr_set_params(cstream);
	अगर (ret < 0)
		जाओ err;

	snd_soc_dapm_stream_event(rtd, stream, SND_SOC_DAPM_STREAM_START);

	/* cancel any delayed stream shutकरोwn that is pending */
	rtd->pop_रुको = 0;
	mutex_unlock(&rtd->card->pcm_mutex);

	cancel_delayed_work_sync(&rtd->delayed_work);

	वापस 0;

err:
	mutex_unlock(&rtd->card->pcm_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक soc_compr_set_params_fe(काष्ठा snd_compr_stream *cstream,
				   काष्ठा snd_compr_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *fe = cstream->निजी_data;
	काष्ठा snd_pcm_substream *fe_substream =
		 fe->pcm->streams[cstream->direction].substream;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(fe, 0);
	पूर्णांक stream = cstream->direction; /* SND_COMPRESS_xxx is same as SNDRV_PCM_STREAM_xxx */
	पूर्णांक ret;

	mutex_lock_nested(&fe->card->mutex, SND_SOC_CARD_CLASS_RUNTIME);

	/*
	 * Create an empty hw_params क्रम the BE as the machine driver must
	 * fix this up to match DSP decoder and ASRC configuration.
	 * I.e. machine driver fixup क्रम compressed BE is mandatory.
	 */
	स_रखो(&fe->dpcm[fe_substream->stream].hw_params, 0,
		माप(काष्ठा snd_pcm_hw_params));

	fe->dpcm[stream].runसमय_update = SND_SOC_DPCM_UPDATE_FE;

	ret = dpcm_be_dai_hw_params(fe, stream);
	अगर (ret < 0)
		जाओ out;

	ret = dpcm_be_dai_prepare(fe, stream);
	अगर (ret < 0)
		जाओ out;

	ret = snd_soc_dai_compr_set_params(cpu_dai, cstream, params);
	अगर (ret < 0)
		जाओ out;

	ret = snd_soc_component_compr_set_params(cstream, params);
	अगर (ret < 0)
		जाओ out;

	ret = snd_soc_link_compr_set_params(cstream);
	अगर (ret < 0)
		जाओ out;

	dpcm_dapm_stream_event(fe, stream, SND_SOC_DAPM_STREAM_START);
	fe->dpcm[stream].state = SND_SOC_DPCM_STATE_PREPARE;

out:
	fe->dpcm[stream].runसमय_update = SND_SOC_DPCM_UPDATE_NO;
	mutex_unlock(&fe->card->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक soc_compr_get_params(काष्ठा snd_compr_stream *cstream,
				काष्ठा snd_codec *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक ret = 0;

	mutex_lock_nested(&rtd->card->pcm_mutex, rtd->card->pcm_subclass);

	ret = snd_soc_dai_compr_get_params(cpu_dai, cstream, params);
	अगर (ret < 0)
		जाओ err;

	ret = snd_soc_component_compr_get_params(cstream, params);
err:
	mutex_unlock(&rtd->card->pcm_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक soc_compr_ack(काष्ठा snd_compr_stream *cstream, माप_प्रकार bytes)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक ret;

	mutex_lock_nested(&rtd->card->pcm_mutex, rtd->card->pcm_subclass);

	ret = snd_soc_dai_compr_ack(cpu_dai, cstream, bytes);
	अगर (ret < 0)
		जाओ err;

	ret = snd_soc_component_compr_ack(cstream, bytes);
err:
	mutex_unlock(&rtd->card->pcm_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक soc_compr_poपूर्णांकer(काष्ठा snd_compr_stream *cstream,
			     काष्ठा snd_compr_tstamp *tstamp)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	पूर्णांक ret;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);

	mutex_lock_nested(&rtd->card->pcm_mutex, rtd->card->pcm_subclass);

	ret = snd_soc_dai_compr_poपूर्णांकer(cpu_dai, cstream, tstamp);
	अगर (ret < 0)
		जाओ out;

	ret = snd_soc_component_compr_poपूर्णांकer(cstream, tstamp);
out:
	mutex_unlock(&rtd->card->pcm_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक soc_compr_set_metadata(काष्ठा snd_compr_stream *cstream,
				  काष्ठा snd_compr_metadata *metadata)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक ret;

	ret = snd_soc_dai_compr_set_metadata(cpu_dai, cstream, metadata);
	अगर (ret < 0)
		वापस ret;

	वापस snd_soc_component_compr_set_metadata(cstream, metadata);
पूर्ण

अटल पूर्णांक soc_compr_get_metadata(काष्ठा snd_compr_stream *cstream,
				  काष्ठा snd_compr_metadata *metadata)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक ret;

	ret = snd_soc_dai_compr_get_metadata(cpu_dai, cstream, metadata);
	अगर (ret < 0)
		वापस ret;

	वापस snd_soc_component_compr_get_metadata(cstream, metadata);
पूर्ण

/* ASoC Compress operations */
अटल काष्ठा snd_compr_ops soc_compr_ops = अणु
	.खोलो		= soc_compr_खोलो,
	.मुक्त		= soc_compr_मुक्त,
	.set_params	= soc_compr_set_params,
	.set_metadata   = soc_compr_set_metadata,
	.get_metadata	= soc_compr_get_metadata,
	.get_params	= soc_compr_get_params,
	.trigger	= soc_compr_trigger,
	.poपूर्णांकer	= soc_compr_poपूर्णांकer,
	.ack		= soc_compr_ack,
	.get_caps	= snd_soc_component_compr_get_caps,
	.get_codec_caps = snd_soc_component_compr_get_codec_caps,
पूर्ण;

/* ASoC Dynamic Compress operations */
अटल काष्ठा snd_compr_ops soc_compr_dyn_ops = अणु
	.खोलो		= soc_compr_खोलो_fe,
	.मुक्त		= soc_compr_मुक्त_fe,
	.set_params	= soc_compr_set_params_fe,
	.get_params	= soc_compr_get_params,
	.set_metadata   = soc_compr_set_metadata,
	.get_metadata	= soc_compr_get_metadata,
	.trigger	= soc_compr_trigger_fe,
	.poपूर्णांकer	= soc_compr_poपूर्णांकer,
	.ack		= soc_compr_ack,
	.get_caps	= snd_soc_component_compr_get_caps,
	.get_codec_caps = snd_soc_component_compr_get_codec_caps,
पूर्ण;

/**
 * snd_soc_new_compress - create a new compress.
 *
 * @rtd: The runसमय क्रम which we will create compress
 * @num: the device index number (zero based - shared with normal PCMs)
 *
 * Return: 0 क्रम success, अन्यथा error.
 */
पूर्णांक snd_soc_new_compress(काष्ठा snd_soc_pcm_runसमय *rtd, पूर्णांक num)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_compr *compr;
	काष्ठा snd_pcm *be_pcm;
	अक्षर new_name[64];
	पूर्णांक ret = 0, direction = 0;
	पूर्णांक playback = 0, capture = 0;
	पूर्णांक i;

	/*
	 * make sure these are same value,
	 * and then use these as equally
	 */
	BUILD_BUG_ON((पूर्णांक)SNDRV_PCM_STREAM_PLAYBACK != (पूर्णांक)SND_COMPRESS_PLAYBACK);
	BUILD_BUG_ON((पूर्णांक)SNDRV_PCM_STREAM_CAPTURE  != (पूर्णांक)SND_COMPRESS_CAPTURE);

	अगर (rtd->num_cpus > 1 ||
	    rtd->num_codecs > 1) अणु
		dev_err(rtd->card->dev,
			"Compress ASoC: Multi CPU/Codec not supported\n");
		वापस -EINVAL;
	पूर्ण

	/* check client and पूर्णांकerface hw capabilities */
	अगर (snd_soc_dai_stream_valid(codec_dai, SNDRV_PCM_STREAM_PLAYBACK) &&
	    snd_soc_dai_stream_valid(cpu_dai,   SNDRV_PCM_STREAM_PLAYBACK))
		playback = 1;
	अगर (snd_soc_dai_stream_valid(codec_dai, SNDRV_PCM_STREAM_CAPTURE) &&
	    snd_soc_dai_stream_valid(cpu_dai,   SNDRV_PCM_STREAM_CAPTURE))
		capture = 1;

	/*
	 * Compress devices are unidirectional so only one of the directions
	 * should be set, check क्रम that (xor)
	 */
	अगर (playback + capture != 1) अणु
		dev_err(rtd->card->dev,
			"Compress ASoC: Invalid direction for P %d, C %d\n",
			playback, capture);
		वापस -EINVAL;
	पूर्ण

	अगर (playback)
		direction = SND_COMPRESS_PLAYBACK;
	अन्यथा
		direction = SND_COMPRESS_CAPTURE;

	compr = devm_kzalloc(rtd->card->dev, माप(*compr), GFP_KERNEL);
	अगर (!compr)
		वापस -ENOMEM;

	compr->ops = devm_kzalloc(rtd->card->dev, माप(soc_compr_ops),
				  GFP_KERNEL);
	अगर (!compr->ops)
		वापस -ENOMEM;

	अगर (rtd->dai_link->dynamic) अणु
		snम_लिखो(new_name, माप(new_name), "(%s)",
			rtd->dai_link->stream_name);

		ret = snd_pcm_new_पूर्णांकernal(rtd->card->snd_card, new_name, num,
				rtd->dai_link->dpcm_playback,
				rtd->dai_link->dpcm_capture, &be_pcm);
		अगर (ret < 0) अणु
			dev_err(rtd->card->dev,
				"Compress ASoC: can't create compressed for %s: %d\n",
				rtd->dai_link->name, ret);
			वापस ret;
		पूर्ण

		rtd->pcm = be_pcm;
		rtd->fe_compr = 1;
		अगर (rtd->dai_link->dpcm_playback)
			be_pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream->निजी_data = rtd;
		अन्यथा अगर (rtd->dai_link->dpcm_capture)
			be_pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream->निजी_data = rtd;
		स_नकल(compr->ops, &soc_compr_dyn_ops, माप(soc_compr_dyn_ops));
	पूर्ण अन्यथा अणु
		snम_लिखो(new_name, माप(new_name), "%s %s-%d",
			rtd->dai_link->stream_name, codec_dai->name, num);

		स_नकल(compr->ops, &soc_compr_ops, माप(soc_compr_ops));
	पूर्ण

	क्रम_each_rtd_components(rtd, i, component) अणु
		अगर (!component->driver->compress_ops ||
		    !component->driver->compress_ops->copy)
			जारी;

		compr->ops->copy = snd_soc_component_compr_copy;
		अवरोध;
	पूर्ण

	mutex_init(&compr->lock);
	ret = snd_compress_new(rtd->card->snd_card, num, direction,
				new_name, compr);
	अगर (ret < 0) अणु
		component = asoc_rtd_to_codec(rtd, 0)->component;
		dev_err(component->dev,
			"Compress ASoC: can't create compress for codec %s: %d\n",
			component->name, ret);
		वापस ret;
	पूर्ण

	/* DAPM dai link stream work */
	rtd->बंद_delayed_work_func = snd_soc_बंद_delayed_work;

	rtd->compr = compr;
	compr->निजी_data = rtd;

	dev_dbg(rtd->card->dev, "Compress ASoC: %s <-> %s mapping ok\n",
		codec_dai->name, cpu_dai->name);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_new_compress);
