<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * digi00x-pcm.c - a part of driver क्रम Digidesign Digi 002/003 family
 *
 * Copyright (c) 2014-2015 Takashi Sakamoto
 */

#समावेश "digi00x.h"

अटल पूर्णांक hw_rule_rate(काष्ठा snd_pcm_hw_params *params,
			काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *r =
		hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	स्थिर काष्ठा snd_पूर्णांकerval *c =
		hw_param_पूर्णांकerval_c(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval t = अणु
		.min = अच_पूर्णांक_उच्च, .max = 0, .पूर्णांकeger = 1,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < SND_DG00X_RATE_COUNT; i++) अणु
		अगर (!snd_पूर्णांकerval_test(c,
				       snd_dg00x_stream_pcm_channels[i]))
			जारी;

		t.min = min(t.min, snd_dg00x_stream_rates[i]);
		t.max = max(t.max, snd_dg00x_stream_rates[i]);
	पूर्ण

	वापस snd_पूर्णांकerval_refine(r, &t);
पूर्ण

अटल पूर्णांक hw_rule_channels(काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *c =
		hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	स्थिर काष्ठा snd_पूर्णांकerval *r =
		hw_param_पूर्णांकerval_c(params, SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval t = अणु
		.min = अच_पूर्णांक_उच्च, .max = 0, .पूर्णांकeger = 1,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < SND_DG00X_RATE_COUNT; i++) अणु
		अगर (!snd_पूर्णांकerval_test(r, snd_dg00x_stream_rates[i]))
			जारी;

		t.min = min(t.min, snd_dg00x_stream_pcm_channels[i]);
		t.max = max(t.max, snd_dg00x_stream_pcm_channels[i]);
	पूर्ण

	वापस snd_पूर्णांकerval_refine(c, &t);
पूर्ण

अटल पूर्णांक pcm_init_hw_params(काष्ठा snd_dg00x *dg00x,
			      काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_pcm_hardware *hw = &runसमय->hw;
	काष्ठा amdtp_stream *s;
	पूर्णांक err;


	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		substream->runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S32;
		s = &dg00x->tx_stream;
	पूर्ण अन्यथा अणु
		substream->runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S32;
		s = &dg00x->rx_stream;
	पूर्ण

	hw->channels_min = 10;
	hw->channels_max = 18;

	hw->rates = SNDRV_PCM_RATE_44100 |
		    SNDRV_PCM_RATE_48000 |
		    SNDRV_PCM_RATE_88200 |
		    SNDRV_PCM_RATE_96000;
	snd_pcm_limit_hw_rates(runसमय);

	err = snd_pcm_hw_rule_add(substream->runसमय, 0,
				  SNDRV_PCM_HW_PARAM_CHANNELS,
				  hw_rule_channels, शून्य,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	अगर (err < 0)
		वापस err;

	err = snd_pcm_hw_rule_add(substream->runसमय, 0,
				  SNDRV_PCM_HW_PARAM_RATE,
				  hw_rule_rate, शून्य,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	अगर (err < 0)
		वापस err;

	वापस amdtp_करोt_add_pcm_hw_स्थिरraपूर्णांकs(s, substream->runसमय);
पूर्ण

अटल पूर्णांक pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dg00x *dg00x = substream->निजी_data;
	काष्ठा amdtp_करोमुख्य *d = &dg00x->करोमुख्य;
	क्रमागत snd_dg00x_घड़ी घड़ी;
	bool detect;
	पूर्णांक err;

	err = snd_dg00x_stream_lock_try(dg00x);
	अगर (err < 0)
		वापस err;

	err = pcm_init_hw_params(dg00x, substream);
	अगर (err < 0)
		जाओ err_locked;

	/* Check current घड़ी source. */
	err = snd_dg00x_stream_get_घड़ी(dg00x, &घड़ी);
	अगर (err < 0)
		जाओ err_locked;
	अगर (घड़ी != SND_DG00X_CLOCK_INTERNAL) अणु
		err = snd_dg00x_stream_check_बाह्यal_घड़ी(dg00x, &detect);
		अगर (err < 0)
			जाओ err_locked;
		अगर (!detect) अणु
			err = -EBUSY;
			जाओ err_locked;
		पूर्ण
	पूर्ण

	mutex_lock(&dg00x->mutex);

	// When source of घड़ी is not पूर्णांकernal or any stream is reserved क्रम
	// transmission of PCM frames, the available sampling rate is limited
	// at current one.
	अगर ((घड़ी != SND_DG00X_CLOCK_INTERNAL) ||
	    (dg00x->substreams_counter > 0 && d->events_per_period > 0)) अणु
		अचिन्हित पूर्णांक frames_per_period = d->events_per_period;
		अचिन्हित पूर्णांक frames_per_buffer = d->events_per_buffer;
		अचिन्हित पूर्णांक rate;

		err = snd_dg00x_stream_get_बाह्यal_rate(dg00x, &rate);
		अगर (err < 0) अणु
			mutex_unlock(&dg00x->mutex);
			जाओ err_locked;
		पूर्ण
		substream->runसमय->hw.rate_min = rate;
		substream->runसमय->hw.rate_max = rate;

		अगर (frames_per_period > 0) अणु
			err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(substream->runसमय,
					SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
					frames_per_period, frames_per_period);
			अगर (err < 0) अणु
				mutex_unlock(&dg00x->mutex);
				जाओ err_locked;
			पूर्ण

			err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(substream->runसमय,
					SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
					frames_per_buffer, frames_per_buffer);
			अगर (err < 0) अणु
				mutex_unlock(&dg00x->mutex);
				जाओ err_locked;
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&dg00x->mutex);

	snd_pcm_set_sync(substream);

	वापस 0;
err_locked:
	snd_dg00x_stream_lock_release(dg00x);
	वापस err;
पूर्ण

अटल पूर्णांक pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dg00x *dg00x = substream->निजी_data;

	snd_dg00x_stream_lock_release(dg00x);

	वापस 0;
पूर्ण

अटल पूर्णांक pcm_hw_params(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_dg00x *dg00x = substream->निजी_data;
	पूर्णांक err = 0;

	अगर (substream->runसमय->status->state == SNDRV_PCM_STATE_OPEN) अणु
		अचिन्हित पूर्णांक rate = params_rate(hw_params);
		अचिन्हित पूर्णांक frames_per_period = params_period_size(hw_params);
		अचिन्हित पूर्णांक frames_per_buffer = params_buffer_size(hw_params);

		mutex_lock(&dg00x->mutex);
		err = snd_dg00x_stream_reserve_duplex(dg00x, rate,
					frames_per_period, frames_per_buffer);
		अगर (err >= 0)
			++dg00x->substreams_counter;
		mutex_unlock(&dg00x->mutex);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dg00x *dg00x = substream->निजी_data;

	mutex_lock(&dg00x->mutex);

	अगर (substream->runसमय->status->state != SNDRV_PCM_STATE_OPEN)
		--dg00x->substreams_counter;

	snd_dg00x_stream_stop_duplex(dg00x);

	mutex_unlock(&dg00x->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक pcm_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dg00x *dg00x = substream->निजी_data;
	पूर्णांक err;

	mutex_lock(&dg00x->mutex);

	err = snd_dg00x_stream_start_duplex(dg00x);
	अगर (err >= 0)
		amdtp_stream_pcm_prepare(&dg00x->tx_stream);

	mutex_unlock(&dg00x->mutex);

	वापस err;
पूर्ण

अटल पूर्णांक pcm_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dg00x *dg00x = substream->निजी_data;
	पूर्णांक err;

	mutex_lock(&dg00x->mutex);

	err = snd_dg00x_stream_start_duplex(dg00x);
	अगर (err >= 0) अणु
		amdtp_stream_pcm_prepare(&dg00x->rx_stream);
		amdtp_करोt_reset(&dg00x->rx_stream);
	पूर्ण

	mutex_unlock(&dg00x->mutex);

	वापस err;
पूर्ण

अटल पूर्णांक pcm_capture_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_dg00x *dg00x = substream->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		amdtp_stream_pcm_trigger(&dg00x->tx_stream, substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		amdtp_stream_pcm_trigger(&dg00x->tx_stream, शून्य);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcm_playback_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_dg00x *dg00x = substream->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		amdtp_stream_pcm_trigger(&dg00x->rx_stream, substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		amdtp_stream_pcm_trigger(&dg00x->rx_stream, शून्य);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t pcm_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *sbstrm)
अणु
	काष्ठा snd_dg00x *dg00x = sbstrm->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_poपूर्णांकer(&dg00x->करोमुख्य, &dg00x->tx_stream);
पूर्ण

अटल snd_pcm_uframes_t pcm_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *sbstrm)
अणु
	काष्ठा snd_dg00x *dg00x = sbstrm->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_poपूर्णांकer(&dg00x->करोमुख्य, &dg00x->rx_stream);
पूर्ण

अटल पूर्णांक pcm_capture_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dg00x *dg00x = substream->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_ack(&dg00x->करोमुख्य, &dg00x->tx_stream);
पूर्ण

अटल पूर्णांक pcm_playback_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dg00x *dg00x = substream->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_ack(&dg00x->करोमुख्य, &dg00x->rx_stream);
पूर्ण

पूर्णांक snd_dg00x_create_pcm_devices(काष्ठा snd_dg00x *dg00x)
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

	err = snd_pcm_new(dg00x->card, dg00x->card->driver, 0, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;

	pcm->निजी_data = dg00x;
	snम_लिखो(pcm->name, माप(pcm->name),
		 "%s PCM", dg00x->card->लघुname);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &capture_ops);
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_VMALLOC, शून्य, 0, 0);

	वापस 0;
पूर्ण
