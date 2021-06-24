<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tascam-pcm.c - a part of driver क्रम TASCAM FireWire series
 *
 * Copyright (c) 2015 Takashi Sakamoto
 */

#समावेश "tascam.h"

अटल पूर्णांक pcm_init_hw_params(काष्ठा snd_tscm *tscm,
			      काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_pcm_hardware *hw = &runसमय->hw;
	काष्ठा amdtp_stream *stream;
	अचिन्हित पूर्णांक pcm_channels;

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S32;
		stream = &tscm->tx_stream;
		pcm_channels = tscm->spec->pcm_capture_analog_channels;
	पूर्ण अन्यथा अणु
		runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S32;
		stream = &tscm->rx_stream;
		pcm_channels = tscm->spec->pcm_playback_analog_channels;
	पूर्ण

	अगर (tscm->spec->has_adat)
		pcm_channels += 8;
	अगर (tscm->spec->has_spdअगर)
		pcm_channels += 2;
	runसमय->hw.channels_min = runसमय->hw.channels_max = pcm_channels;

	hw->rates = SNDRV_PCM_RATE_44100 |
		    SNDRV_PCM_RATE_48000 |
		    SNDRV_PCM_RATE_88200 |
		    SNDRV_PCM_RATE_96000;
	snd_pcm_limit_hw_rates(runसमय);

	वापस amdtp_tscm_add_pcm_hw_स्थिरraपूर्णांकs(stream, runसमय);
पूर्ण

अटल पूर्णांक pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_tscm *tscm = substream->निजी_data;
	काष्ठा amdtp_करोमुख्य *d = &tscm->करोमुख्य;
	क्रमागत snd_tscm_घड़ी घड़ी;
	पूर्णांक err;

	err = snd_tscm_stream_lock_try(tscm);
	अगर (err < 0)
		वापस err;

	err = pcm_init_hw_params(tscm, substream);
	अगर (err < 0)
		जाओ err_locked;

	err = snd_tscm_stream_get_घड़ी(tscm, &घड़ी);
	अगर (err < 0)
		जाओ err_locked;

	mutex_lock(&tscm->mutex);

	// When source of घड़ी is not पूर्णांकernal or any stream is reserved क्रम
	// transmission of PCM frames, the available sampling rate is limited
	// at current one.
	अगर (घड़ी != SND_TSCM_CLOCK_INTERNAL || tscm->substreams_counter > 0) अणु
		अचिन्हित पूर्णांक frames_per_period = d->events_per_period;
		अचिन्हित पूर्णांक frames_per_buffer = d->events_per_buffer;
		अचिन्हित पूर्णांक rate;

		err = snd_tscm_stream_get_rate(tscm, &rate);
		अगर (err < 0) अणु
			mutex_unlock(&tscm->mutex);
			जाओ err_locked;
		पूर्ण
		substream->runसमय->hw.rate_min = rate;
		substream->runसमय->hw.rate_max = rate;

		err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(substream->runसमय,
					SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
					frames_per_period, frames_per_period);
		अगर (err < 0) अणु
			mutex_unlock(&tscm->mutex);
			जाओ err_locked;
		पूर्ण

		err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(substream->runसमय,
					SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
					frames_per_buffer, frames_per_buffer);
		अगर (err < 0) अणु
			mutex_unlock(&tscm->mutex);
			जाओ err_locked;
		पूर्ण
	पूर्ण

	mutex_unlock(&tscm->mutex);

	snd_pcm_set_sync(substream);

	वापस 0;
err_locked:
	snd_tscm_stream_lock_release(tscm);
	वापस err;
पूर्ण

अटल पूर्णांक pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_tscm *tscm = substream->निजी_data;

	snd_tscm_stream_lock_release(tscm);

	वापस 0;
पूर्ण

अटल पूर्णांक pcm_hw_params(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_tscm *tscm = substream->निजी_data;
	पूर्णांक err = 0;

	अगर (substream->runसमय->status->state == SNDRV_PCM_STATE_OPEN) अणु
		अचिन्हित पूर्णांक rate = params_rate(hw_params);
		अचिन्हित पूर्णांक frames_per_period = params_period_size(hw_params);
		अचिन्हित पूर्णांक frames_per_buffer = params_buffer_size(hw_params);

		mutex_lock(&tscm->mutex);
		err = snd_tscm_stream_reserve_duplex(tscm, rate,
					frames_per_period, frames_per_buffer);
		अगर (err >= 0)
			++tscm->substreams_counter;
		mutex_unlock(&tscm->mutex);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_tscm *tscm = substream->निजी_data;

	mutex_lock(&tscm->mutex);

	अगर (substream->runसमय->status->state != SNDRV_PCM_STATE_OPEN)
		--tscm->substreams_counter;

	snd_tscm_stream_stop_duplex(tscm);

	mutex_unlock(&tscm->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक pcm_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_tscm *tscm = substream->निजी_data;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	mutex_lock(&tscm->mutex);

	err = snd_tscm_stream_start_duplex(tscm, runसमय->rate);
	अगर (err >= 0)
		amdtp_stream_pcm_prepare(&tscm->tx_stream);

	mutex_unlock(&tscm->mutex);

	वापस err;
पूर्ण

अटल पूर्णांक pcm_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_tscm *tscm = substream->निजी_data;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	mutex_lock(&tscm->mutex);

	err = snd_tscm_stream_start_duplex(tscm, runसमय->rate);
	अगर (err >= 0)
		amdtp_stream_pcm_prepare(&tscm->rx_stream);

	mutex_unlock(&tscm->mutex);

	वापस err;
पूर्ण

अटल पूर्णांक pcm_capture_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_tscm *tscm = substream->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		amdtp_stream_pcm_trigger(&tscm->tx_stream, substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		amdtp_stream_pcm_trigger(&tscm->tx_stream, शून्य);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcm_playback_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_tscm *tscm = substream->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		amdtp_stream_pcm_trigger(&tscm->rx_stream, substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		amdtp_stream_pcm_trigger(&tscm->rx_stream, शून्य);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t pcm_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *sbstrm)
अणु
	काष्ठा snd_tscm *tscm = sbstrm->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_poपूर्णांकer(&tscm->करोमुख्य, &tscm->tx_stream);
पूर्ण

अटल snd_pcm_uframes_t pcm_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *sbstrm)
अणु
	काष्ठा snd_tscm *tscm = sbstrm->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_poपूर्णांकer(&tscm->करोमुख्य, &tscm->rx_stream);
पूर्ण

अटल पूर्णांक pcm_capture_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_tscm *tscm = substream->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_ack(&tscm->करोमुख्य, &tscm->tx_stream);
पूर्ण

अटल पूर्णांक pcm_playback_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_tscm *tscm = substream->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_ack(&tscm->करोमुख्य, &tscm->rx_stream);
पूर्ण

पूर्णांक snd_tscm_create_pcm_devices(काष्ठा snd_tscm *tscm)
अणु
	अटल स्थिर काष्ठा snd_pcm_ops capture_ops = अणु
		.खोलो		= pcm_खोलो,
		.बंद		= pcm_बंद,
		.hw_params	= pcm_hw_params,
		.hw_मुक्त	= pcm_hw_मुक्त,
		.prepare	= pcm_capture_prepare,
		.trigger	= pcm_capture_trigger,
		.poपूर्णांकer	= pcm_capture_poपूर्णांकer,
		.ack		= pcm_capture_ack,
	पूर्ण;
	अटल स्थिर काष्ठा snd_pcm_ops playback_ops = अणु
		.खोलो		= pcm_खोलो,
		.बंद		= pcm_बंद,
		.hw_params	= pcm_hw_params,
		.hw_मुक्त	= pcm_hw_मुक्त,
		.prepare	= pcm_playback_prepare,
		.trigger	= pcm_playback_trigger,
		.poपूर्णांकer	= pcm_playback_poपूर्णांकer,
		.ack		= pcm_playback_ack,
	पूर्ण;
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(tscm->card, tscm->card->driver, 0, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;

	pcm->निजी_data = tscm;
	snम_लिखो(pcm->name, माप(pcm->name),
		 "%s PCM", tscm->card->लघुname);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &capture_ops);
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_VMALLOC, शून्य, 0, 0);

	वापस 0;
पूर्ण
