<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ff-pcm.c - a part of driver क्रम RME Fireface series
 *
 * Copyright (c) 2015-2017 Takashi Sakamoto
 */

#समावेश "ff.h"

अटल पूर्णांक hw_rule_rate(काष्ठा snd_pcm_hw_params *params,
			काष्ठा snd_pcm_hw_rule *rule)
अणु
	स्थिर अचिन्हित पूर्णांक *pcm_channels = rule->निजी;
	काष्ठा snd_पूर्णांकerval *r =
		hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	स्थिर काष्ठा snd_पूर्णांकerval *c =
		hw_param_पूर्णांकerval_c(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval t = अणु
		.min = अच_पूर्णांक_उच्च, .max = 0, .पूर्णांकeger = 1
	पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(amdtp_rate_table); i++) अणु
		क्रमागत snd_ff_stream_mode mode;
		पूर्णांक err;

		err = snd_ff_stream_get_multiplier_mode(i, &mode);
		अगर (err < 0)
			जारी;

		अगर (!snd_पूर्णांकerval_test(c, pcm_channels[mode]))
			जारी;

		t.min = min(t.min, amdtp_rate_table[i]);
		t.max = max(t.max, amdtp_rate_table[i]);
	पूर्ण

	वापस snd_पूर्णांकerval_refine(r, &t);
पूर्ण

अटल पूर्णांक hw_rule_channels(काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_pcm_hw_rule *rule)
अणु
	स्थिर अचिन्हित पूर्णांक *pcm_channels = rule->निजी;
	काष्ठा snd_पूर्णांकerval *c =
		hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	स्थिर काष्ठा snd_पूर्णांकerval *r =
		hw_param_पूर्णांकerval_c(params, SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval t = अणु
		.min = अच_पूर्णांक_उच्च, .max = 0, .पूर्णांकeger = 1
	पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(amdtp_rate_table); i++) अणु
		क्रमागत snd_ff_stream_mode mode;
		पूर्णांक err;

		err = snd_ff_stream_get_multiplier_mode(i, &mode);
		अगर (err < 0)
			जारी;

		अगर (!snd_पूर्णांकerval_test(r, amdtp_rate_table[i]))
			जारी;

		t.min = min(t.min, pcm_channels[mode]);
		t.max = max(t.max, pcm_channels[mode]);
	पूर्ण

	वापस snd_पूर्णांकerval_refine(c, &t);
पूर्ण

अटल व्योम limit_channels_and_rates(काष्ठा snd_pcm_hardware *hw,
				     स्थिर अचिन्हित पूर्णांक *pcm_channels)
अणु
	अचिन्हित पूर्णांक rate, channels;
	पूर्णांक i;

	hw->channels_min = अच_पूर्णांक_उच्च;
	hw->channels_max = 0;
	hw->rate_min = अच_पूर्णांक_उच्च;
	hw->rate_max = 0;

	क्रम (i = 0; i < ARRAY_SIZE(amdtp_rate_table); i++) अणु
		क्रमागत snd_ff_stream_mode mode;
		पूर्णांक err;

		err = snd_ff_stream_get_multiplier_mode(i, &mode);
		अगर (err < 0)
			जारी;

		channels = pcm_channels[mode];
		अगर (pcm_channels[mode] == 0)
			जारी;
		hw->channels_min = min(hw->channels_min, channels);
		hw->channels_max = max(hw->channels_max, channels);

		rate = amdtp_rate_table[i];
		hw->rates |= snd_pcm_rate_to_rate_bit(rate);
		hw->rate_min = min(hw->rate_min, rate);
		hw->rate_max = max(hw->rate_max, rate);
	पूर्ण
पूर्ण

अटल पूर्णांक pcm_init_hw_params(काष्ठा snd_ff *ff,
			      काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा amdtp_stream *s;
	स्थिर अचिन्हित पूर्णांक *pcm_channels;
	पूर्णांक err;

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S32;
		s = &ff->tx_stream;
		pcm_channels = ff->spec->pcm_capture_channels;
	पूर्ण अन्यथा अणु
		runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S32;
		s = &ff->rx_stream;
		pcm_channels = ff->spec->pcm_playback_channels;
	पूर्ण

	limit_channels_and_rates(&runसमय->hw, pcm_channels);

	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				  hw_rule_channels, (व्योम *)pcm_channels,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	अगर (err < 0)
		वापस err;

	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				  hw_rule_rate, (व्योम *)pcm_channels,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	अगर (err < 0)
		वापस err;

	वापस amdtp_ff_add_pcm_hw_स्थिरraपूर्णांकs(s, runसमय);
पूर्ण

अटल पूर्णांक pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ff *ff = substream->निजी_data;
	काष्ठा amdtp_करोमुख्य *d = &ff->करोमुख्य;
	अचिन्हित पूर्णांक rate;
	क्रमागत snd_ff_घड़ी_src src;
	पूर्णांक i, err;

	err = snd_ff_stream_lock_try(ff);
	अगर (err < 0)
		वापस err;

	err = pcm_init_hw_params(ff, substream);
	अगर (err < 0)
		जाओ release_lock;

	err = ff->spec->protocol->get_घड़ी(ff, &rate, &src);
	अगर (err < 0)
		जाओ release_lock;

	mutex_lock(&ff->mutex);

	// When source of घड़ी is not पूर्णांकernal or any stream is reserved क्रम
	// transmission of PCM frames, the available sampling rate is limited
	// at current one.
	अगर (src != SND_FF_CLOCK_SRC_INTERNAL) अणु
		क्रम (i = 0; i < CIP_SFC_COUNT; ++i) अणु
			अगर (amdtp_rate_table[i] == rate)
				अवरोध;
		पूर्ण

		// The unit is configured at sampling frequency which packet
		// streaming engine can't support.
		अगर (i >= CIP_SFC_COUNT) अणु
			mutex_unlock(&ff->mutex);
			err = -EIO;
			जाओ release_lock;
		पूर्ण

		substream->runसमय->hw.rate_min = rate;
		substream->runसमय->hw.rate_max = rate;
	पूर्ण अन्यथा अणु
		अगर (ff->substreams_counter > 0) अणु
			अचिन्हित पूर्णांक frames_per_period = d->events_per_period;
			अचिन्हित पूर्णांक frames_per_buffer = d->events_per_buffer;

			rate = amdtp_rate_table[ff->rx_stream.sfc];
			substream->runसमय->hw.rate_min = rate;
			substream->runसमय->hw.rate_max = rate;

			err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(substream->runसमय,
					SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
					frames_per_period, frames_per_period);
			अगर (err < 0) अणु
				mutex_unlock(&ff->mutex);
				जाओ release_lock;
			पूर्ण

			err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(substream->runसमय,
					SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
					frames_per_buffer, frames_per_buffer);
			अगर (err < 0) अणु
				mutex_unlock(&ff->mutex);
				जाओ release_lock;
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&ff->mutex);

	snd_pcm_set_sync(substream);

	वापस 0;

release_lock:
	snd_ff_stream_lock_release(ff);
	वापस err;
पूर्ण

अटल पूर्णांक pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ff *ff = substream->निजी_data;

	snd_ff_stream_lock_release(ff);

	वापस 0;
पूर्ण

अटल पूर्णांक pcm_hw_params(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_ff *ff = substream->निजी_data;
	पूर्णांक err = 0;

	अगर (substream->runसमय->status->state == SNDRV_PCM_STATE_OPEN) अणु
		अचिन्हित पूर्णांक rate = params_rate(hw_params);
		अचिन्हित पूर्णांक frames_per_period = params_period_size(hw_params);
		अचिन्हित पूर्णांक frames_per_buffer = params_buffer_size(hw_params);

		mutex_lock(&ff->mutex);
		err = snd_ff_stream_reserve_duplex(ff, rate, frames_per_period,
						   frames_per_buffer);
		अगर (err >= 0)
			++ff->substreams_counter;
		mutex_unlock(&ff->mutex);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ff *ff = substream->निजी_data;

	mutex_lock(&ff->mutex);

	अगर (substream->runसमय->status->state != SNDRV_PCM_STATE_OPEN)
		--ff->substreams_counter;

	snd_ff_stream_stop_duplex(ff);

	mutex_unlock(&ff->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक pcm_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ff *ff = substream->निजी_data;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	mutex_lock(&ff->mutex);

	err = snd_ff_stream_start_duplex(ff, runसमय->rate);
	अगर (err >= 0)
		amdtp_stream_pcm_prepare(&ff->tx_stream);

	mutex_unlock(&ff->mutex);

	वापस err;
पूर्ण

अटल पूर्णांक pcm_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ff *ff = substream->निजी_data;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	mutex_lock(&ff->mutex);

	err = snd_ff_stream_start_duplex(ff, runसमय->rate);
	अगर (err >= 0)
		amdtp_stream_pcm_prepare(&ff->rx_stream);

	mutex_unlock(&ff->mutex);

	वापस err;
पूर्ण

अटल पूर्णांक pcm_capture_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_ff *ff = substream->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		amdtp_stream_pcm_trigger(&ff->tx_stream, substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		amdtp_stream_pcm_trigger(&ff->tx_stream, शून्य);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcm_playback_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_ff *ff = substream->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		amdtp_stream_pcm_trigger(&ff->rx_stream, substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		amdtp_stream_pcm_trigger(&ff->rx_stream, शून्य);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t pcm_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *sbstrm)
अणु
	काष्ठा snd_ff *ff = sbstrm->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_poपूर्णांकer(&ff->करोमुख्य, &ff->tx_stream);
पूर्ण

अटल snd_pcm_uframes_t pcm_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *sbstrm)
अणु
	काष्ठा snd_ff *ff = sbstrm->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_poपूर्णांकer(&ff->करोमुख्य, &ff->rx_stream);
पूर्ण

अटल पूर्णांक pcm_capture_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ff *ff = substream->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_ack(&ff->करोमुख्य, &ff->tx_stream);
पूर्ण

अटल पूर्णांक pcm_playback_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ff *ff = substream->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_ack(&ff->करोमुख्य, &ff->rx_stream);
पूर्ण

पूर्णांक snd_ff_create_pcm_devices(काष्ठा snd_ff *ff)
अणु
	अटल स्थिर काष्ठा snd_pcm_ops pcm_capture_ops = अणु
		.खोलो		= pcm_खोलो,
		.बंद		= pcm_बंद,
		.hw_params	= pcm_hw_params,
		.hw_मुक्त	= pcm_hw_मुक्त,
		.prepare	= pcm_capture_prepare,
		.trigger	= pcm_capture_trigger,
		.poपूर्णांकer	= pcm_capture_poपूर्णांकer,
		.ack		= pcm_capture_ack,
	पूर्ण;
	अटल स्थिर काष्ठा snd_pcm_ops pcm_playback_ops = अणु
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

	err = snd_pcm_new(ff->card, ff->card->driver, 0, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;

	pcm->निजी_data = ff;
	snम_लिखो(pcm->name, माप(pcm->name),
		 "%s PCM", ff->card->लघुname);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &pcm_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &pcm_capture_ops);
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_VMALLOC, शून्य, 0, 0);

	वापस 0;
पूर्ण
