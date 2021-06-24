<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * motu-pcm.c - a part of driver क्रम MOTU FireWire series
 *
 * Copyright (c) 2015-2017 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#समावेश <sound/pcm_params.h>
#समावेश "motu.h"

अटल पूर्णांक motu_rate_स्थिरraपूर्णांक(काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_motu_packet_क्रमmat *क्रमmats = rule->निजी;

	स्थिर काष्ठा snd_पूर्णांकerval *c =
		hw_param_पूर्णांकerval_c(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval *r =
		hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval rates = अणु
		.min = अच_पूर्णांक_उच्च, .max = 0, .पूर्णांकeger = 1
	पूर्ण;
	अचिन्हित पूर्णांक i, pcm_channels, rate, mode;

	क्रम (i = 0; i < ARRAY_SIZE(snd_motu_घड़ी_rates); ++i) अणु
		rate = snd_motu_घड़ी_rates[i];
		mode = i / 2;

		pcm_channels = क्रमmats->pcm_chunks[mode];
		अगर (!snd_पूर्णांकerval_test(c, pcm_channels))
			जारी;

		rates.min = min(rates.min, rate);
		rates.max = max(rates.max, rate);
	पूर्ण

	वापस snd_पूर्णांकerval_refine(r, &rates);
पूर्ण

अटल पूर्णांक motu_channels_स्थिरraपूर्णांक(काष्ठा snd_pcm_hw_params *params,
				    काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_motu_packet_क्रमmat *क्रमmats = rule->निजी;

	स्थिर काष्ठा snd_पूर्णांकerval *r =
		hw_param_पूर्णांकerval_c(params, SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *c =
		hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval channels = अणु
		.min = अच_पूर्णांक_उच्च, .max = 0, .पूर्णांकeger = 1
	पूर्ण;
	अचिन्हित पूर्णांक i, pcm_channels, rate, mode;

	क्रम (i = 0; i < ARRAY_SIZE(snd_motu_घड़ी_rates); ++i) अणु
		rate = snd_motu_घड़ी_rates[i];
		mode = i / 2;

		अगर (!snd_पूर्णांकerval_test(r, rate))
			जारी;

		pcm_channels = क्रमmats->pcm_chunks[mode];
		channels.min = min(channels.min, pcm_channels);
		channels.max = max(channels.max, pcm_channels);
	पूर्ण

	वापस snd_पूर्णांकerval_refine(c, &channels);
पूर्ण

अटल व्योम limit_channels_and_rates(काष्ठा snd_motu *motu,
				     काष्ठा snd_pcm_runसमय *runसमय,
				     काष्ठा snd_motu_packet_क्रमmat *क्रमmats)
अणु
	काष्ठा snd_pcm_hardware *hw = &runसमय->hw;
	अचिन्हित पूर्णांक i, pcm_channels, rate, mode;

	hw->channels_min = अच_पूर्णांक_उच्च;
	hw->channels_max = 0;

	क्रम (i = 0; i < ARRAY_SIZE(snd_motu_घड़ी_rates); ++i) अणु
		rate = snd_motu_घड़ी_rates[i];
		mode = i / 2;

		pcm_channels = क्रमmats->pcm_chunks[mode];
		अगर (pcm_channels == 0)
			जारी;

		hw->rates |= snd_pcm_rate_to_rate_bit(rate);
		hw->channels_min = min(hw->channels_min, pcm_channels);
		hw->channels_max = max(hw->channels_max, pcm_channels);
	पूर्ण

	snd_pcm_limit_hw_rates(runसमय);
पूर्ण

अटल पूर्णांक init_hw_info(काष्ठा snd_motu *motu,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_pcm_hardware *hw = &runसमय->hw;
	काष्ठा amdtp_stream *stream;
	काष्ठा snd_motu_packet_क्रमmat *क्रमmats;
	पूर्णांक err;

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		hw->क्रमmats = SNDRV_PCM_FMTBIT_S32;
		stream = &motu->tx_stream;
		क्रमmats = &motu->tx_packet_क्रमmats;
	पूर्ण अन्यथा अणु
		hw->क्रमmats = SNDRV_PCM_FMTBIT_S32;
		stream = &motu->rx_stream;
		क्रमmats = &motu->rx_packet_क्रमmats;
	पूर्ण

	limit_channels_and_rates(motu, runसमय, क्रमmats);

	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				  motu_rate_स्थिरraपूर्णांक, क्रमmats,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				  motu_channels_स्थिरraपूर्णांक, क्रमmats,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	अगर (err < 0)
		वापस err;

	वापस amdtp_motu_add_pcm_hw_स्थिरraपूर्णांकs(stream, runसमय);
पूर्ण

अटल पूर्णांक pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_motu *motu = substream->निजी_data;
	काष्ठा amdtp_करोमुख्य *d = &motu->करोमुख्य;
	क्रमागत snd_motu_घड़ी_source src;
	पूर्णांक err;

	err = snd_motu_stream_lock_try(motu);
	अगर (err < 0)
		वापस err;

	mutex_lock(&motu->mutex);

	err = snd_motu_stream_cache_packet_क्रमmats(motu);
	अगर (err < 0)
		जाओ err_locked;

	err = init_hw_info(motu, substream);
	अगर (err < 0)
		जाओ err_locked;

	err = snd_motu_protocol_get_घड़ी_source(motu, &src);
	अगर (err < 0)
		जाओ err_locked;

	// When source of घड़ी is not पूर्णांकernal or any stream is reserved क्रम
	// transmission of PCM frames, the available sampling rate is limited
	// at current one.
	अगर ((src != SND_MOTU_CLOCK_SOURCE_INTERNAL &&
	     src != SND_MOTU_CLOCK_SOURCE_SPH) ||
	    (motu->substreams_counter > 0 && d->events_per_period > 0)) अणु
		अचिन्हित पूर्णांक frames_per_period = d->events_per_period;
		अचिन्हित पूर्णांक frames_per_buffer = d->events_per_buffer;
		अचिन्हित पूर्णांक rate;

		err = snd_motu_protocol_get_घड़ी_rate(motu, &rate);
		अगर (err < 0)
			जाओ err_locked;

		substream->runसमय->hw.rate_min = rate;
		substream->runसमय->hw.rate_max = rate;

		अगर (frames_per_period > 0) अणु
			err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(substream->runसमय,
					SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
					frames_per_period, frames_per_period);
			अगर (err < 0)
				जाओ err_locked;

			err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(substream->runसमय,
					SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
					frames_per_buffer, frames_per_buffer);
			अगर (err < 0)
				जाओ err_locked;
		पूर्ण
	पूर्ण

	snd_pcm_set_sync(substream);

	mutex_unlock(&motu->mutex);

	वापस 0;
err_locked:
	mutex_unlock(&motu->mutex);
	snd_motu_stream_lock_release(motu);
	वापस err;
पूर्ण

अटल पूर्णांक pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_motu *motu = substream->निजी_data;

	snd_motu_stream_lock_release(motu);

	वापस 0;
पूर्ण

अटल पूर्णांक pcm_hw_params(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_motu *motu = substream->निजी_data;
	पूर्णांक err = 0;

	अगर (substream->runसमय->status->state == SNDRV_PCM_STATE_OPEN) अणु
		अचिन्हित पूर्णांक rate = params_rate(hw_params);
		अचिन्हित पूर्णांक frames_per_period = params_period_size(hw_params);
		अचिन्हित पूर्णांक frames_per_buffer = params_buffer_size(hw_params);

		mutex_lock(&motu->mutex);
		err = snd_motu_stream_reserve_duplex(motu, rate,
					frames_per_period, frames_per_buffer);
		अगर (err >= 0)
			++motu->substreams_counter;
		mutex_unlock(&motu->mutex);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_motu *motu = substream->निजी_data;

	mutex_lock(&motu->mutex);

	अगर (substream->runसमय->status->state != SNDRV_PCM_STATE_OPEN)
		--motu->substreams_counter;

	snd_motu_stream_stop_duplex(motu);

	mutex_unlock(&motu->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_motu *motu = substream->निजी_data;
	पूर्णांक err;

	mutex_lock(&motu->mutex);
	err = snd_motu_stream_start_duplex(motu);
	mutex_unlock(&motu->mutex);
	अगर (err >= 0)
		amdtp_stream_pcm_prepare(&motu->tx_stream);

	वापस 0;
पूर्ण
अटल पूर्णांक playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_motu *motu = substream->निजी_data;
	पूर्णांक err;

	mutex_lock(&motu->mutex);
	err = snd_motu_stream_start_duplex(motu);
	mutex_unlock(&motu->mutex);
	अगर (err >= 0)
		amdtp_stream_pcm_prepare(&motu->rx_stream);

	वापस err;
पूर्ण

अटल पूर्णांक capture_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_motu *motu = substream->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		amdtp_stream_pcm_trigger(&motu->tx_stream, substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		amdtp_stream_pcm_trigger(&motu->tx_stream, शून्य);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
अटल पूर्णांक playback_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_motu *motu = substream->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		amdtp_stream_pcm_trigger(&motu->rx_stream, substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		amdtp_stream_pcm_trigger(&motu->rx_stream, शून्य);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_motu *motu = substream->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_poपूर्णांकer(&motu->करोमुख्य, &motu->tx_stream);
पूर्ण
अटल snd_pcm_uframes_t playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_motu *motu = substream->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_poपूर्णांकer(&motu->करोमुख्य, &motu->rx_stream);
पूर्ण

अटल पूर्णांक capture_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_motu *motu = substream->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_ack(&motu->करोमुख्य, &motu->tx_stream);
पूर्ण

अटल पूर्णांक playback_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_motu *motu = substream->निजी_data;

	वापस amdtp_करोमुख्य_stream_pcm_ack(&motu->करोमुख्य, &motu->rx_stream);
पूर्ण

पूर्णांक snd_motu_create_pcm_devices(काष्ठा snd_motu *motu)
अणु
	अटल स्थिर काष्ठा snd_pcm_ops capture_ops = अणु
		.खोलो      = pcm_खोलो,
		.बंद     = pcm_बंद,
		.hw_params = pcm_hw_params,
		.hw_मुक्त   = pcm_hw_मुक्त,
		.prepare   = capture_prepare,
		.trigger   = capture_trigger,
		.poपूर्णांकer   = capture_poपूर्णांकer,
		.ack       = capture_ack,
	पूर्ण;
	अटल स्थिर काष्ठा snd_pcm_ops playback_ops = अणु
		.खोलो      = pcm_खोलो,
		.बंद     = pcm_बंद,
		.hw_params = pcm_hw_params,
		.hw_मुक्त   = pcm_hw_मुक्त,
		.prepare   = playback_prepare,
		.trigger   = playback_trigger,
		.poपूर्णांकer   = playback_poपूर्णांकer,
		.ack       = playback_ack,
	पूर्ण;
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(motu->card, motu->card->driver, 0, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;
	pcm->निजी_data = motu;
	म_नकल(pcm->name, motu->card->लघुname);

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &capture_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &playback_ops);
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_VMALLOC, शून्य, 0, 0);

	वापस 0;
पूर्ण
