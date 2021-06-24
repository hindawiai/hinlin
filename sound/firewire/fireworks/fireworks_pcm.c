<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fireworks_pcm.c - a part of driver क्रम Fireworks based devices
 *
 * Copyright (c) 2009-2010 Clemens Ladisch
 * Copyright (c) 2013-2014 Takashi Sakamoto
 */
#समावेश "./fireworks.h"

/*
 * NOTE:
 * Fireworks changes its AMDTP channels क्रम PCM data according to its sampling
 * rate. There are three modes. Here _XX is either _rx or _tx.
 *  0:  32.0- 48.0 kHz then snd_efw_hwinfo.amdtp_XX_pcm_channels applied
 *  1:  88.2- 96.0 kHz then snd_efw_hwinfo.amdtp_XX_pcm_channels_2x applied
 *  2: 176.4-192.0 kHz then snd_efw_hwinfo.amdtp_XX_pcm_channels_4x applied
 *
 * The number of PCM channels क्रम analog input and output are always fixed but
 * the number of PCM channels क्रम digital input and output are dअगरfered.
 *
 * Additionally, according to "AudioFire Owner's Manual Version 2.2", in some
 * model, the number of PCM channels क्रम digital input has more restriction
 * depending on which digital पूर्णांकerface is selected.
 *  - S/PDIF coaxial and optical	: use input 1-2
 *  - ADAT optical at 32.0-48.0 kHz	: use input 1-8
 *  - ADAT optical at 88.2-96.0 kHz	: use input 1-4 (S/MUX क्रमmat)
 *
 * The data in AMDTP channels क्रम blank PCM channels are zero.
 */
अटल स्थिर अचिन्हित पूर्णांक freq_table[] = अणु
	/* multiplier mode 0 */
	[0] = 32000,
	[1] = 44100,
	[2] = 48000,
	/* multiplier mode 1 */
	[3] = 88200,
	[4] = 96000,
	/* multiplier mode 2 */
	[5] = 176400,
	[6] = 192000,
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक
get_multiplier_mode_with_index(अचिन्हित पूर्णांक index)
अणु
	वापस ((पूर्णांक)index - 1) / 2;
पूर्ण

पूर्णांक snd_efw_get_multiplier_mode(अचिन्हित पूर्णांक sampling_rate, अचिन्हित पूर्णांक *mode)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(freq_table); i++) अणु
		अगर (freq_table[i] == sampling_rate) अणु
			*mode = get_multiplier_mode_with_index(i);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
hw_rule_rate(काष्ठा snd_pcm_hw_params *params, काष्ठा snd_pcm_hw_rule *rule)
अणु
	अचिन्हित पूर्णांक *pcm_channels = rule->निजी;
	काष्ठा snd_पूर्णांकerval *r =
		hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	स्थिर काष्ठा snd_पूर्णांकerval *c =
		hw_param_पूर्णांकerval_c(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval t = अणु
		.min = अच_पूर्णांक_उच्च, .max = 0, .पूर्णांकeger = 1
	पूर्ण;
	अचिन्हित पूर्णांक i, mode;

	क्रम (i = 0; i < ARRAY_SIZE(freq_table); i++) अणु
		mode = get_multiplier_mode_with_index(i);
		अगर (!snd_पूर्णांकerval_test(c, pcm_channels[mode]))
			जारी;

		t.min = min(t.min, freq_table[i]);
		t.max = max(t.max, freq_table[i]);
	पूर्ण

	वापस snd_पूर्णांकerval_refine(r, &t);
पूर्ण

अटल पूर्णांक
hw_rule_channels(काष्ठा snd_pcm_hw_params *params, काष्ठा snd_pcm_hw_rule *rule)
अणु
	अचिन्हित पूर्णांक *pcm_channels = rule->निजी;
	काष्ठा snd_पूर्णांकerval *c =
		hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	स्थिर काष्ठा snd_पूर्णांकerval *r =
		hw_param_पूर्णांकerval_c(params, SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval t = अणु
		.min = अच_पूर्णांक_उच्च, .max = 0, .पूर्णांकeger = 1
	पूर्ण;
	अचिन्हित पूर्णांक i, mode;

	क्रम (i = 0; i < ARRAY_SIZE(freq_table); i++) अणु
		mode = get_multiplier_mode_with_index(i);
		अगर (!snd_पूर्णांकerval_test(r, freq_table[i]))
			जारी;

		t.min = min(t.min, pcm_channels[mode]);
		t.max = max(t.max, pcm_channels[mode]);
	पूर्ण

	वापस snd_पूर्णांकerval_refine(c, &t);
पूर्ण

अटल व्योम
limit_channels(काष्ठा snd_pcm_hardware *hw, अचिन्हित पूर्णांक *pcm_channels)
अणु
	अचिन्हित पूर्णांक i, mode;

	hw->channels_min = अच_पूर्णांक_उच्च;
	hw->channels_max = 0;

	क्रम (i = 0; i < ARRAY_SIZE(freq_table); i++) अणु
		mode = get_multiplier_mode_with_index(i);
		अगर (pcm_channels[mode] == 0)
			जारी;

		hw->channels_min = min(hw->channels_min, pcm_channels[mode]);
		hw->channels_max = max(hw->channels_max, pcm_channels[mode]);
	पूर्ण
पूर्ण

अटल पूर्णांक
pcm_init_hw_params(काष्ठा snd_efw *efw,
		   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा amdtp_stream *s;
	अचिन्हित पूर्णांक *pcm_channels;
	पूर्णांक err;

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		runसमय->hw.क्रमmats = AM824_IN_PCM_FORMAT_BITS;
		s = &efw->tx_stream;
		pcm_channels = efw->pcm_capture_channels;
	पूर्ण अन्यथा अणु
		runसमय->hw.क्रमmats = AM824_OUT_PCM_FORMAT_BITS;
		s = &efw->rx_stream;
		pcm_channels = efw->pcm_playback_channels;
	पूर्ण

	/* limit rates */
	runसमय->hw.rates = efw->supported_sampling_rate;
	snd_pcm_limit_hw_rates(runसमय);

	limit_channels(&runसमय->hw, pcm_channels);

	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				  hw_rule_channels, pcm_channels,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	अगर (err < 0)
		जाओ end;

	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				  hw_rule_rate, pcm_channels,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	अगर (err < 0)
		जाओ end;

	err = amdtp_am824_add_pcm_hw_स्थिरraपूर्णांकs(s, runसमय);
end:
	वापस err;
पूर्ण

अटल पूर्णांक pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_efw *efw = substream->निजी_data;
	काष्ठा amdtp_करोमुख्य *d = &efw->करोमुख्य;
	क्रमागत snd_efw_घड़ी_source घड़ी_source;
	पूर्णांक err;

	err = snd_efw_stream_lock_try(efw);
	अगर (err < 0)
		वापस err;

	err = pcm_init_hw_params(efw, substream);
	अगर (err < 0)
		जाओ err_locked;

	err = snd_efw_command_get_घड़ी_source(efw, &घड़ी_source);
	अगर (err < 0)
		जाओ err_locked;

	mutex_lock(&efw->mutex);

	// When source of घड़ी is not पूर्णांकernal or any stream is reserved क्रम
	// transmission of PCM frames, the available sampling rate is limited
	// at current one.
	अगर ((घड़ी_source != SND_EFW_CLOCK_SOURCE_INTERNAL) ||
	    (efw->substreams_counter > 0 && d->events_per_period > 0)) अणु
		अचिन्हित पूर्णांक frames_per_period = d->events_per_period;
		अचिन्हित पूर्णांक frames_per_buffer = d->events_per_buffer;
		अचिन्हित पूर्णांक sampling_rate;

		err = snd_efw_command_get_sampling_rate(efw, &sampling_rate);
		अगर (err < 0) अणु
			mutex_unlock(&efw->mutex);
			जाओ err_locked;
		पूर्ण
		substream->runसमय->hw.rate_min = sampling_rate;
		substream->runसमय->hw.rate_max = sampling_rate;

		अगर (frames_per_period > 0) अणु
			err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(substream->runसमय,
					SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
					frames_per_period, frames_per_period);
			अगर (err < 0) अणु
				mutex_unlock(&efw->mutex);
				जाओ err_locked;
			पूर्ण

			err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(substream->runसमय,
					SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
					frames_per_buffer, frames_per_buffer);
			अगर (err < 0) अणु
				mutex_unlock(&efw->mutex);
				जाओ err_locked;
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&efw->mutex);

	snd_pcm_set_sync(substream);

	वापस 0;
err_locked:
	snd_efw_stream_lock_release(efw);
	वापस err;
पूर्ण

अटल पूर्णांक pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_efw *efw = substream->निजी_data;
	snd_efw_stream_lock_release(efw);
	वापस 0;
पूर्ण

अटल पूर्णांक pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_efw *efw = substream->निजी_data;
	पूर्णांक err = 0;

	अगर (substream->runसमय->status->state == SNDRV_PCM_STATE_OPEN) अणु
		अचिन्हित पूर्णांक rate = params_rate(hw_params);
		अचिन्हित पूर्णांक frames_per_period = params_period_size(hw_params);
		अचिन्हित पूर्णांक frames_per_buffer = params_buffer_size(hw_params);

		mutex_lock(&efw->mutex);
		err = snd_efw_stream_reserve_duplex(efw, rate,
					frames_per_period, frames_per_buffer);
		अगर (err >= 0)
			++efw->substreams_counter;
		mutex_unlock(&efw->mutex);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_efw *efw = substream->निजी_data;

	mutex_lock(&efw->mutex);

	अगर (substream->runसमय->status->state != SNDRV_PCM_STATE_OPEN)
		--efw->substreams_counter;

	snd_efw_stream_stop_duplex(efw);

	mutex_unlock(&efw->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक pcm_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_efw *efw = substream->निजी_data;
	पूर्णांक err;

	err = snd_efw_stream_start_duplex(efw);
	अगर (err >= 0)
		amdtp_stream_pcm_prepare(&efw->tx_stream);

	वापस err;
पूर्ण
अटल पूर्णांक pcm_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_efw *efw = substream->निजी_data;
	पूर्णांक err;

	err = snd_efw_stream_start_duplex(efw);
	अगर (err >= 0)
		amdtp_stream_pcm_prepare(&efw->rx_stream);

	वापस err;
पूर्ण

अटल पूर्णांक pcm_capture_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_efw *efw = substream->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		amdtp_stream_pcm_trigger(&efw->tx_stream, substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		amdtp_stream_pcm_trigger(&efw->tx_stream, शून्य);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
अटल पूर्णांक pcm_playback_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_efw *efw = substream->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		amdtp_stream_pcm_trigger(&efw->rx_stream, substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		amdtp_stream_pcm_trigger(&efw->rx_stream, शून्य);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t pcm_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *sbstrm)
अणु
	काष्ठा snd_efw *efw = sbstrm->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_poपूर्णांकer(&efw->करोमुख्य, &efw->tx_stream);
पूर्ण
अटल snd_pcm_uframes_t pcm_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *sbstrm)
अणु
	काष्ठा snd_efw *efw = sbstrm->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_poपूर्णांकer(&efw->करोमुख्य, &efw->rx_stream);
पूर्ण

अटल पूर्णांक pcm_capture_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_efw *efw = substream->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_ack(&efw->करोमुख्य, &efw->tx_stream);
पूर्ण

अटल पूर्णांक pcm_playback_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_efw *efw = substream->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_ack(&efw->करोमुख्य, &efw->rx_stream);
पूर्ण

पूर्णांक snd_efw_create_pcm_devices(काष्ठा snd_efw *efw)
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

	err = snd_pcm_new(efw->card, efw->card->driver, 0, 1, 1, &pcm);
	अगर (err < 0)
		जाओ end;

	pcm->निजी_data = efw;
	snम_लिखो(pcm->name, माप(pcm->name), "%s PCM", efw->card->लघुname);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &capture_ops);
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_VMALLOC, शून्य, 0, 0);
end:
	वापस err;
पूर्ण

