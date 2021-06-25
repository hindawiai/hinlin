<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * bebob_pcm.c - a part of driver क्रम BeBoB based devices
 *
 * Copyright (c) 2013-2014 Takashi Sakamoto
 */

#समावेश "./bebob.h"

अटल पूर्णांक
hw_rule_rate(काष्ठा snd_pcm_hw_params *params, काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_bebob_stream_क्रमmation *क्रमmations = rule->निजी;
	काष्ठा snd_पूर्णांकerval *r =
		hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	स्थिर काष्ठा snd_पूर्णांकerval *c =
		hw_param_पूर्णांकerval_c(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval t = अणु
		.min = अच_पूर्णांक_उच्च, .max = 0, .पूर्णांकeger = 1
	पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < SND_BEBOB_STRM_FMT_ENTRIES; i++) अणु
		/* entry is invalid */
		अगर (क्रमmations[i].pcm == 0)
			जारी;

		अगर (!snd_पूर्णांकerval_test(c, क्रमmations[i].pcm))
			जारी;

		t.min = min(t.min, snd_bebob_rate_table[i]);
		t.max = max(t.max, snd_bebob_rate_table[i]);

	पूर्ण
	वापस snd_पूर्णांकerval_refine(r, &t);
पूर्ण

अटल पूर्णांक
hw_rule_channels(काष्ठा snd_pcm_hw_params *params, काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_bebob_stream_क्रमmation *क्रमmations = rule->निजी;
	काष्ठा snd_पूर्णांकerval *c =
		hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	स्थिर काष्ठा snd_पूर्णांकerval *r =
		hw_param_पूर्णांकerval_c(params, SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval t = अणु
		.min = अच_पूर्णांक_उच्च, .max = 0, .पूर्णांकeger = 1
	पूर्ण;

	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < SND_BEBOB_STRM_FMT_ENTRIES; i++) अणु
		/* entry is invalid */
		अगर (क्रमmations[i].pcm == 0)
			जारी;

		अगर (!snd_पूर्णांकerval_test(r, snd_bebob_rate_table[i]))
			जारी;

		t.min = min(t.min, क्रमmations[i].pcm);
		t.max = max(t.max, क्रमmations[i].pcm);
	पूर्ण

	वापस snd_पूर्णांकerval_refine(c, &t);
पूर्ण

अटल व्योम
limit_channels_and_rates(काष्ठा snd_pcm_hardware *hw,
			 काष्ठा snd_bebob_stream_क्रमmation *क्रमmations)
अणु
	अचिन्हित पूर्णांक i;

	hw->channels_min = अच_पूर्णांक_उच्च;
	hw->channels_max = 0;

	hw->rate_min = अच_पूर्णांक_उच्च;
	hw->rate_max = 0;
	hw->rates = 0;

	क्रम (i = 0; i < SND_BEBOB_STRM_FMT_ENTRIES; i++) अणु
		/* entry has no PCM channels */
		अगर (क्रमmations[i].pcm == 0)
			जारी;

		hw->channels_min = min(hw->channels_min, क्रमmations[i].pcm);
		hw->channels_max = max(hw->channels_max, क्रमmations[i].pcm);

		hw->rate_min = min(hw->rate_min, snd_bebob_rate_table[i]);
		hw->rate_max = max(hw->rate_max, snd_bebob_rate_table[i]);
		hw->rates |= snd_pcm_rate_to_rate_bit(snd_bebob_rate_table[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक
pcm_init_hw_params(काष्ठा snd_bebob *bebob,
		   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा amdtp_stream *s;
	काष्ठा snd_bebob_stream_क्रमmation *क्रमmations;
	पूर्णांक err;

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		runसमय->hw.क्रमmats = AM824_IN_PCM_FORMAT_BITS;
		s = &bebob->tx_stream;
		क्रमmations = bebob->tx_stream_क्रमmations;
	पूर्ण अन्यथा अणु
		runसमय->hw.क्रमmats = AM824_OUT_PCM_FORMAT_BITS;
		s = &bebob->rx_stream;
		क्रमmations = bebob->rx_stream_क्रमmations;
	पूर्ण

	limit_channels_and_rates(&runसमय->hw, क्रमmations);

	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				  hw_rule_channels, क्रमmations,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	अगर (err < 0)
		जाओ end;

	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				  hw_rule_rate, क्रमmations,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	अगर (err < 0)
		जाओ end;

	err = amdtp_am824_add_pcm_hw_स्थिरraपूर्णांकs(s, runसमय);
end:
	वापस err;
पूर्ण

अटल पूर्णांक pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_bebob *bebob = substream->निजी_data;
	स्थिर काष्ठा snd_bebob_rate_spec *spec = bebob->spec->rate;
	काष्ठा amdtp_करोमुख्य *d = &bebob->करोमुख्य;
	क्रमागत snd_bebob_घड़ी_प्रकारype src;
	पूर्णांक err;

	err = snd_bebob_stream_lock_try(bebob);
	अगर (err < 0)
		वापस err;

	err = pcm_init_hw_params(bebob, substream);
	अगर (err < 0)
		जाओ err_locked;

	err = snd_bebob_stream_get_घड़ी_src(bebob, &src);
	अगर (err < 0)
		जाओ err_locked;

	mutex_lock(&bebob->mutex);

	// When source of घड़ी is not पूर्णांकernal or any stream is reserved क्रम
	// transmission of PCM frames, the available sampling rate is limited
	// at current one.
	अगर (src == SND_BEBOB_CLOCK_TYPE_EXTERNAL ||
	    (bebob->substreams_counter > 0 && d->events_per_period > 0)) अणु
		अचिन्हित पूर्णांक frames_per_period = d->events_per_period;
		अचिन्हित पूर्णांक frames_per_buffer = d->events_per_buffer;
		अचिन्हित पूर्णांक sampling_rate;

		err = spec->get(bebob, &sampling_rate);
		अगर (err < 0) अणु
			mutex_unlock(&bebob->mutex);
			dev_err(&bebob->unit->device,
				"fail to get sampling rate: %d\n", err);
			जाओ err_locked;
		पूर्ण

		substream->runसमय->hw.rate_min = sampling_rate;
		substream->runसमय->hw.rate_max = sampling_rate;

		अगर (frames_per_period > 0) अणु
			err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(substream->runसमय,
					SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
					frames_per_period, frames_per_period);
			अगर (err < 0) अणु
				mutex_unlock(&bebob->mutex);
				जाओ err_locked;
			पूर्ण

			err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(substream->runसमय,
					SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
					frames_per_buffer, frames_per_buffer);
			अगर (err < 0) अणु
				mutex_unlock(&bebob->mutex);
				जाओ err_locked;
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&bebob->mutex);

	snd_pcm_set_sync(substream);

	वापस 0;
err_locked:
	snd_bebob_stream_lock_release(bebob);
	वापस err;
पूर्ण

अटल पूर्णांक
pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_bebob *bebob = substream->निजी_data;
	snd_bebob_stream_lock_release(bebob);
	वापस 0;
पूर्ण

अटल पूर्णांक pcm_hw_params(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_bebob *bebob = substream->निजी_data;
	पूर्णांक err = 0;

	अगर (substream->runसमय->status->state == SNDRV_PCM_STATE_OPEN) अणु
		अचिन्हित पूर्णांक rate = params_rate(hw_params);
		अचिन्हित पूर्णांक frames_per_period = params_period_size(hw_params);
		अचिन्हित पूर्णांक frames_per_buffer = params_buffer_size(hw_params);

		mutex_lock(&bebob->mutex);
		err = snd_bebob_stream_reserve_duplex(bebob, rate,
					frames_per_period, frames_per_buffer);
		अगर (err >= 0)
			++bebob->substreams_counter;
		mutex_unlock(&bebob->mutex);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_bebob *bebob = substream->निजी_data;

	mutex_lock(&bebob->mutex);

	अगर (substream->runसमय->status->state != SNDRV_PCM_STATE_OPEN)
		bebob->substreams_counter--;

	snd_bebob_stream_stop_duplex(bebob);

	mutex_unlock(&bebob->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक
pcm_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_bebob *bebob = substream->निजी_data;
	पूर्णांक err;

	err = snd_bebob_stream_start_duplex(bebob);
	अगर (err >= 0)
		amdtp_stream_pcm_prepare(&bebob->tx_stream);

	वापस err;
पूर्ण
अटल पूर्णांक
pcm_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_bebob *bebob = substream->निजी_data;
	पूर्णांक err;

	err = snd_bebob_stream_start_duplex(bebob);
	अगर (err >= 0)
		amdtp_stream_pcm_prepare(&bebob->rx_stream);

	वापस err;
पूर्ण

अटल पूर्णांक
pcm_capture_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_bebob *bebob = substream->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		amdtp_stream_pcm_trigger(&bebob->tx_stream, substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		amdtp_stream_pcm_trigger(&bebob->tx_stream, शून्य);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
अटल पूर्णांक
pcm_playback_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_bebob *bebob = substream->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		amdtp_stream_pcm_trigger(&bebob->rx_stream, substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		amdtp_stream_pcm_trigger(&bebob->rx_stream, शून्य);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t pcm_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *sbstrm)
अणु
	काष्ठा snd_bebob *bebob = sbstrm->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_poपूर्णांकer(&bebob->करोमुख्य,
					       &bebob->tx_stream);
पूर्ण
अटल snd_pcm_uframes_t pcm_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *sbstrm)
अणु
	काष्ठा snd_bebob *bebob = sbstrm->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_poपूर्णांकer(&bebob->करोमुख्य,
					       &bebob->rx_stream);
पूर्ण

अटल पूर्णांक pcm_capture_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_bebob *bebob = substream->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_ack(&bebob->करोमुख्य, &bebob->tx_stream);
पूर्ण

अटल पूर्णांक pcm_playback_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_bebob *bebob = substream->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_ack(&bebob->करोमुख्य, &bebob->rx_stream);
पूर्ण

पूर्णांक snd_bebob_create_pcm_devices(काष्ठा snd_bebob *bebob)
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

	err = snd_pcm_new(bebob->card, bebob->card->driver, 0, 1, 1, &pcm);
	अगर (err < 0)
		जाओ end;

	pcm->निजी_data = bebob;
	snम_लिखो(pcm->name, माप(pcm->name),
		 "%s PCM", bebob->card->लघुname);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &capture_ops);
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_VMALLOC, शून्य, 0, 0);
end:
	वापस err;
पूर्ण
