<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * oxfw_pcm.c - a part of driver क्रम OXFW970/971 based devices
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश "oxfw.h"

अटल पूर्णांक hw_rule_rate(काष्ठा snd_pcm_hw_params *params,
			काष्ठा snd_pcm_hw_rule *rule)
अणु
	u8 **क्रमmats = rule->निजी;
	काष्ठा snd_पूर्णांकerval *r =
		hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	स्थिर काष्ठा snd_पूर्णांकerval *c =
		hw_param_पूर्णांकerval_c(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval t = अणु
		.min = अच_पूर्णांक_उच्च, .max = 0, .पूर्णांकeger = 1
	पूर्ण;
	काष्ठा snd_oxfw_stream_क्रमmation क्रमmation;
	पूर्णांक i, err;

	क्रम (i = 0; i < SND_OXFW_STREAM_FORMAT_ENTRIES; i++) अणु
		अगर (क्रमmats[i] == शून्य)
			जारी;

		err = snd_oxfw_stream_parse_क्रमmat(क्रमmats[i], &क्रमmation);
		अगर (err < 0)
			जारी;
		अगर (!snd_पूर्णांकerval_test(c, क्रमmation.pcm))
			जारी;

		t.min = min(t.min, क्रमmation.rate);
		t.max = max(t.max, क्रमmation.rate);

	पूर्ण
	वापस snd_पूर्णांकerval_refine(r, &t);
पूर्ण

अटल पूर्णांक hw_rule_channels(काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_pcm_hw_rule *rule)
अणु
	u8 **क्रमmats = rule->निजी;
	काष्ठा snd_पूर्णांकerval *c =
		hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	स्थिर काष्ठा snd_पूर्णांकerval *r =
		hw_param_पूर्णांकerval_c(params, SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_oxfw_stream_क्रमmation क्रमmation;
	पूर्णांक i, j, err;
	अचिन्हित पूर्णांक count, list[SND_OXFW_STREAM_FORMAT_ENTRIES] = अणु0पूर्ण;

	count = 0;
	क्रम (i = 0; i < SND_OXFW_STREAM_FORMAT_ENTRIES; i++) अणु
		अगर (क्रमmats[i] == शून्य)
			अवरोध;

		err = snd_oxfw_stream_parse_क्रमmat(क्रमmats[i], &क्रमmation);
		अगर (err < 0)
			जारी;
		अगर (!snd_पूर्णांकerval_test(r, क्रमmation.rate))
			जारी;
		अगर (list[count] == क्रमmation.pcm)
			जारी;

		क्रम (j = 0; j < ARRAY_SIZE(list); j++) अणु
			अगर (list[j] == क्रमmation.pcm)
				अवरोध;
		पूर्ण
		अगर (j == ARRAY_SIZE(list)) अणु
			list[count] = क्रमmation.pcm;
			अगर (++count == ARRAY_SIZE(list))
				अवरोध;
		पूर्ण
	पूर्ण

	वापस snd_पूर्णांकerval_list(c, count, list, 0);
पूर्ण

अटल व्योम limit_channels_and_rates(काष्ठा snd_pcm_hardware *hw, u8 **क्रमmats)
अणु
	काष्ठा snd_oxfw_stream_क्रमmation क्रमmation;
	पूर्णांक i, err;

	hw->channels_min = अच_पूर्णांक_उच्च;
	hw->channels_max = 0;

	hw->rate_min = अच_पूर्णांक_उच्च;
	hw->rate_max = 0;
	hw->rates = 0;

	क्रम (i = 0; i < SND_OXFW_STREAM_FORMAT_ENTRIES; i++) अणु
		अगर (क्रमmats[i] == शून्य)
			अवरोध;

		err = snd_oxfw_stream_parse_क्रमmat(क्रमmats[i], &क्रमmation);
		अगर (err < 0)
			जारी;

		hw->channels_min = min(hw->channels_min, क्रमmation.pcm);
		hw->channels_max = max(hw->channels_max, क्रमmation.pcm);

		hw->rate_min = min(hw->rate_min, क्रमmation.rate);
		hw->rate_max = max(hw->rate_max, क्रमmation.rate);
		hw->rates |= snd_pcm_rate_to_rate_bit(क्रमmation.rate);
	पूर्ण
पूर्ण

अटल पूर्णांक init_hw_params(काष्ठा snd_oxfw *oxfw,
			  काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	u8 **क्रमmats;
	काष्ठा amdtp_stream *stream;
	पूर्णांक err;

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		runसमय->hw.क्रमmats = AM824_IN_PCM_FORMAT_BITS;
		stream = &oxfw->tx_stream;
		क्रमmats = oxfw->tx_stream_क्रमmats;
	पूर्ण अन्यथा अणु
		runसमय->hw.क्रमmats = AM824_OUT_PCM_FORMAT_BITS;
		stream = &oxfw->rx_stream;
		क्रमmats = oxfw->rx_stream_क्रमmats;
	पूर्ण

	limit_channels_and_rates(&runसमय->hw, क्रमmats);

	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				  hw_rule_channels, क्रमmats,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	अगर (err < 0)
		जाओ end;

	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				  hw_rule_rate, क्रमmats,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	अगर (err < 0)
		जाओ end;

	err = amdtp_am824_add_pcm_hw_स्थिरraपूर्णांकs(stream, runसमय);
end:
	वापस err;
पूर्ण

अटल पूर्णांक limit_to_current_params(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_oxfw *oxfw = substream->निजी_data;
	काष्ठा snd_oxfw_stream_क्रमmation क्रमmation;
	क्रमागत avc_general_plug_dir dir;
	पूर्णांक err;

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		dir = AVC_GENERAL_PLUG_सूची_OUT;
	अन्यथा
		dir = AVC_GENERAL_PLUG_सूची_IN;

	err = snd_oxfw_stream_get_current_क्रमmation(oxfw, dir, &क्रमmation);
	अगर (err < 0)
		जाओ end;

	substream->runसमय->hw.channels_min = क्रमmation.pcm;
	substream->runसमय->hw.channels_max = क्रमmation.pcm;
	substream->runसमय->hw.rate_min = क्रमmation.rate;
	substream->runसमय->hw.rate_max = क्रमmation.rate;
end:
	वापस err;
पूर्ण

अटल पूर्णांक pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_oxfw *oxfw = substream->निजी_data;
	काष्ठा amdtp_करोमुख्य *d = &oxfw->करोमुख्य;
	पूर्णांक err;

	err = snd_oxfw_stream_lock_try(oxfw);
	अगर (err < 0)
		वापस err;

	err = init_hw_params(oxfw, substream);
	अगर (err < 0)
		जाओ err_locked;

	mutex_lock(&oxfw->mutex);

	// When source of घड़ी is not पूर्णांकernal or any stream is reserved क्रम
	// transmission of PCM frames, the available sampling rate is limited
	// at current one.
	अगर (oxfw->substreams_count > 0 && d->events_per_period > 0) अणु
		अचिन्हित पूर्णांक frames_per_period = d->events_per_period;
		अचिन्हित पूर्णांक frames_per_buffer = d->events_per_buffer;

		err = limit_to_current_params(substream);
		अगर (err < 0) अणु
			mutex_unlock(&oxfw->mutex);
			जाओ err_locked;
		पूर्ण

		अगर (frames_per_period > 0) अणु
			err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(substream->runसमय,
					SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
					frames_per_period, frames_per_period);
			अगर (err < 0) अणु
				mutex_unlock(&oxfw->mutex);
				जाओ err_locked;
			पूर्ण

			err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(substream->runसमय,
					SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
					frames_per_buffer, frames_per_buffer);
			अगर (err < 0) अणु
				mutex_unlock(&oxfw->mutex);
				जाओ err_locked;
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&oxfw->mutex);

	snd_pcm_set_sync(substream);

	वापस 0;
err_locked:
	snd_oxfw_stream_lock_release(oxfw);
	वापस err;
पूर्ण

अटल पूर्णांक pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_oxfw *oxfw = substream->निजी_data;

	snd_oxfw_stream_lock_release(oxfw);
	वापस 0;
पूर्ण

अटल पूर्णांक pcm_capture_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_oxfw *oxfw = substream->निजी_data;
	पूर्णांक err = 0;

	अगर (substream->runसमय->status->state == SNDRV_PCM_STATE_OPEN) अणु
		अचिन्हित पूर्णांक rate = params_rate(hw_params);
		अचिन्हित पूर्णांक channels = params_channels(hw_params);
		अचिन्हित पूर्णांक frames_per_period = params_period_size(hw_params);
		अचिन्हित पूर्णांक frames_per_buffer = params_buffer_size(hw_params);

		mutex_lock(&oxfw->mutex);
		err = snd_oxfw_stream_reserve_duplex(oxfw, &oxfw->tx_stream,
					rate, channels, frames_per_period,
					frames_per_buffer);
		अगर (err >= 0)
			++oxfw->substreams_count;
		mutex_unlock(&oxfw->mutex);
	पूर्ण

	वापस err;
पूर्ण
अटल पूर्णांक pcm_playback_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_oxfw *oxfw = substream->निजी_data;
	पूर्णांक err = 0;

	अगर (substream->runसमय->status->state == SNDRV_PCM_STATE_OPEN) अणु
		अचिन्हित पूर्णांक rate = params_rate(hw_params);
		अचिन्हित पूर्णांक channels = params_channels(hw_params);
		अचिन्हित पूर्णांक frames_per_period = params_period_size(hw_params);
		अचिन्हित पूर्णांक frames_per_buffer = params_buffer_size(hw_params);

		mutex_lock(&oxfw->mutex);
		err = snd_oxfw_stream_reserve_duplex(oxfw, &oxfw->rx_stream,
					rate, channels, frames_per_period,
					frames_per_buffer);
		अगर (err >= 0)
			++oxfw->substreams_count;
		mutex_unlock(&oxfw->mutex);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक pcm_capture_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_oxfw *oxfw = substream->निजी_data;

	mutex_lock(&oxfw->mutex);

	अगर (substream->runसमय->status->state != SNDRV_PCM_STATE_OPEN)
		--oxfw->substreams_count;

	snd_oxfw_stream_stop_duplex(oxfw);

	mutex_unlock(&oxfw->mutex);

	वापस 0;
पूर्ण
अटल पूर्णांक pcm_playback_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_oxfw *oxfw = substream->निजी_data;

	mutex_lock(&oxfw->mutex);

	अगर (substream->runसमय->status->state != SNDRV_PCM_STATE_OPEN)
		--oxfw->substreams_count;

	snd_oxfw_stream_stop_duplex(oxfw);

	mutex_unlock(&oxfw->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक pcm_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_oxfw *oxfw = substream->निजी_data;
	पूर्णांक err;

	mutex_lock(&oxfw->mutex);
	err = snd_oxfw_stream_start_duplex(oxfw);
	mutex_unlock(&oxfw->mutex);
	अगर (err < 0)
		जाओ end;

	amdtp_stream_pcm_prepare(&oxfw->tx_stream);
end:
	वापस err;
पूर्ण
अटल पूर्णांक pcm_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_oxfw *oxfw = substream->निजी_data;
	पूर्णांक err;

	mutex_lock(&oxfw->mutex);
	err = snd_oxfw_stream_start_duplex(oxfw);
	mutex_unlock(&oxfw->mutex);
	अगर (err < 0)
		जाओ end;

	amdtp_stream_pcm_prepare(&oxfw->rx_stream);
end:
	वापस err;
पूर्ण

अटल पूर्णांक pcm_capture_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_oxfw *oxfw = substream->निजी_data;
	काष्ठा snd_pcm_substream *pcm;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		pcm = substream;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		pcm = शून्य;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	amdtp_stream_pcm_trigger(&oxfw->tx_stream, pcm);
	वापस 0;
पूर्ण
अटल पूर्णांक pcm_playback_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_oxfw *oxfw = substream->निजी_data;
	काष्ठा snd_pcm_substream *pcm;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		pcm = substream;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		pcm = शून्य;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	amdtp_stream_pcm_trigger(&oxfw->rx_stream, pcm);
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t pcm_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *sbsपंचांग)
अणु
	काष्ठा snd_oxfw *oxfw = sbsपंचांग->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_poपूर्णांकer(&oxfw->करोमुख्य, &oxfw->tx_stream);
पूर्ण
अटल snd_pcm_uframes_t pcm_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *sbsपंचांग)
अणु
	काष्ठा snd_oxfw *oxfw = sbsपंचांग->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_poपूर्णांकer(&oxfw->करोमुख्य, &oxfw->rx_stream);
पूर्ण

अटल पूर्णांक pcm_capture_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_oxfw *oxfw = substream->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_ack(&oxfw->करोमुख्य, &oxfw->tx_stream);
पूर्ण

अटल पूर्णांक pcm_playback_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_oxfw *oxfw = substream->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_ack(&oxfw->करोमुख्य, &oxfw->rx_stream);
पूर्ण

पूर्णांक snd_oxfw_create_pcm(काष्ठा snd_oxfw *oxfw)
अणु
	अटल स्थिर काष्ठा snd_pcm_ops capture_ops = अणु
		.खोलो      = pcm_खोलो,
		.बंद     = pcm_बंद,
		.hw_params = pcm_capture_hw_params,
		.hw_मुक्त   = pcm_capture_hw_मुक्त,
		.prepare   = pcm_capture_prepare,
		.trigger   = pcm_capture_trigger,
		.poपूर्णांकer   = pcm_capture_poपूर्णांकer,
		.ack       = pcm_capture_ack,
	पूर्ण;
	अटल स्थिर काष्ठा snd_pcm_ops playback_ops = अणु
		.खोलो      = pcm_खोलो,
		.बंद     = pcm_बंद,
		.hw_params = pcm_playback_hw_params,
		.hw_मुक्त   = pcm_playback_hw_मुक्त,
		.prepare   = pcm_playback_prepare,
		.trigger   = pcm_playback_trigger,
		.poपूर्णांकer   = pcm_playback_poपूर्णांकer,
		.ack       = pcm_playback_ack,
	पूर्ण;
	काष्ठा snd_pcm *pcm;
	अचिन्हित पूर्णांक cap = 0;
	पूर्णांक err;

	अगर (oxfw->has_output)
		cap = 1;

	err = snd_pcm_new(oxfw->card, oxfw->card->driver, 0, 1, cap, &pcm);
	अगर (err < 0)
		वापस err;

	pcm->निजी_data = oxfw;
	म_नकल(pcm->name, oxfw->card->लघुname);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &playback_ops);
	अगर (cap > 0)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &capture_ops);
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_VMALLOC, शून्य, 0, 0);

	वापस 0;
पूर्ण
