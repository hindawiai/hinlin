<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * dice_pcm.c - a part of driver क्रम DICE based devices
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 * Copyright (c) 2014 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#समावेश "dice.h"

अटल पूर्णांक dice_rate_स्थिरraपूर्णांक(काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_pcm_substream *substream = rule->निजी;
	काष्ठा snd_dice *dice = substream->निजी_data;
	अचिन्हित पूर्णांक index = substream->pcm->device;

	स्थिर काष्ठा snd_पूर्णांकerval *c =
		hw_param_पूर्णांकerval_c(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval *r =
		hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval rates = अणु
		.min = अच_पूर्णांक_उच्च, .max = 0, .पूर्णांकeger = 1
	पूर्ण;
	अचिन्हित पूर्णांक *pcm_channels;
	क्रमागत snd_dice_rate_mode mode;
	अचिन्हित पूर्णांक i, rate;

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		pcm_channels = dice->tx_pcm_chs[index];
	अन्यथा
		pcm_channels = dice->rx_pcm_chs[index];

	क्रम (i = 0; i < ARRAY_SIZE(snd_dice_rates); ++i) अणु
		rate = snd_dice_rates[i];
		अगर (snd_dice_stream_get_rate_mode(dice, rate, &mode) < 0)
			जारी;

		अगर (!snd_पूर्णांकerval_test(c, pcm_channels[mode]))
			जारी;

		rates.min = min(rates.min, rate);
		rates.max = max(rates.max, rate);
	पूर्ण

	वापस snd_पूर्णांकerval_refine(r, &rates);
पूर्ण

अटल पूर्णांक dice_channels_स्थिरraपूर्णांक(काष्ठा snd_pcm_hw_params *params,
				    काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_pcm_substream *substream = rule->निजी;
	काष्ठा snd_dice *dice = substream->निजी_data;
	अचिन्हित पूर्णांक index = substream->pcm->device;

	स्थिर काष्ठा snd_पूर्णांकerval *r =
		hw_param_पूर्णांकerval_c(params, SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *c =
		hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval channels = अणु
		.min = अच_पूर्णांक_उच्च, .max = 0, .पूर्णांकeger = 1
	पूर्ण;
	अचिन्हित पूर्णांक *pcm_channels;
	क्रमागत snd_dice_rate_mode mode;
	अचिन्हित पूर्णांक i, rate;

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		pcm_channels = dice->tx_pcm_chs[index];
	अन्यथा
		pcm_channels = dice->rx_pcm_chs[index];

	क्रम (i = 0; i < ARRAY_SIZE(snd_dice_rates); ++i) अणु
		rate = snd_dice_rates[i];
		अगर (snd_dice_stream_get_rate_mode(dice, rate, &mode) < 0)
			जारी;

		अगर (!snd_पूर्णांकerval_test(r, rate))
			जारी;

		channels.min = min(channels.min, pcm_channels[mode]);
		channels.max = max(channels.max, pcm_channels[mode]);
	पूर्ण

	वापस snd_पूर्णांकerval_refine(c, &channels);
पूर्ण

अटल पूर्णांक limit_channels_and_rates(काष्ठा snd_dice *dice,
				    काष्ठा snd_pcm_runसमय *runसमय,
				    क्रमागत amdtp_stream_direction dir,
				    अचिन्हित पूर्णांक index)
अणु
	काष्ठा snd_pcm_hardware *hw = &runसमय->hw;
	अचिन्हित पूर्णांक *pcm_channels;
	अचिन्हित पूर्णांक i;

	अगर (dir == AMDTP_IN_STREAM)
		pcm_channels = dice->tx_pcm_chs[index];
	अन्यथा
		pcm_channels = dice->rx_pcm_chs[index];

	hw->channels_min = अच_पूर्णांक_उच्च;
	hw->channels_max = 0;

	क्रम (i = 0; i < ARRAY_SIZE(snd_dice_rates); ++i) अणु
		क्रमागत snd_dice_rate_mode mode;
		अचिन्हित पूर्णांक rate, channels;

		rate = snd_dice_rates[i];
		अगर (snd_dice_stream_get_rate_mode(dice, rate, &mode) < 0)
			जारी;
		hw->rates |= snd_pcm_rate_to_rate_bit(rate);

		channels = pcm_channels[mode];
		अगर (channels == 0)
			जारी;
		hw->channels_min = min(hw->channels_min, channels);
		hw->channels_max = max(hw->channels_max, channels);
	पूर्ण

	snd_pcm_limit_hw_rates(runसमय);

	वापस 0;
पूर्ण

अटल पूर्णांक init_hw_info(काष्ठा snd_dice *dice,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_pcm_hardware *hw = &runसमय->hw;
	अचिन्हित पूर्णांक index = substream->pcm->device;
	क्रमागत amdtp_stream_direction dir;
	काष्ठा amdtp_stream *stream;
	पूर्णांक err;

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		hw->क्रमmats = AM824_IN_PCM_FORMAT_BITS;
		dir = AMDTP_IN_STREAM;
		stream = &dice->tx_stream[index];
	पूर्ण अन्यथा अणु
		hw->क्रमmats = AM824_OUT_PCM_FORMAT_BITS;
		dir = AMDTP_OUT_STREAM;
		stream = &dice->rx_stream[index];
	पूर्ण

	err = limit_channels_and_rates(dice, substream->runसमय, dir,
				       index);
	अगर (err < 0)
		वापस err;

	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				  dice_rate_स्थिरraपूर्णांक, substream,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				  dice_channels_स्थिरraपूर्णांक, substream,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	अगर (err < 0)
		वापस err;

	वापस amdtp_am824_add_pcm_hw_स्थिरraपूर्णांकs(stream, runसमय);
पूर्ण

अटल पूर्णांक pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dice *dice = substream->निजी_data;
	काष्ठा amdtp_करोमुख्य *d = &dice->करोमुख्य;
	अचिन्हित पूर्णांक source;
	bool पूर्णांकernal;
	पूर्णांक err;

	err = snd_dice_stream_lock_try(dice);
	अगर (err < 0)
		वापस err;

	err = init_hw_info(dice, substream);
	अगर (err < 0)
		जाओ err_locked;

	err = snd_dice_transaction_get_घड़ी_source(dice, &source);
	अगर (err < 0)
		जाओ err_locked;
	चयन (source) अणु
	हाल CLOCK_SOURCE_AES1:
	हाल CLOCK_SOURCE_AES2:
	हाल CLOCK_SOURCE_AES3:
	हाल CLOCK_SOURCE_AES4:
	हाल CLOCK_SOURCE_AES_ANY:
	हाल CLOCK_SOURCE_ADAT:
	हाल CLOCK_SOURCE_TDIF:
	हाल CLOCK_SOURCE_WC:
		पूर्णांकernal = false;
		अवरोध;
	शेष:
		पूर्णांकernal = true;
		अवरोध;
	पूर्ण

	mutex_lock(&dice->mutex);

	// When source of घड़ी is not पूर्णांकernal or any stream is reserved क्रम
	// transmission of PCM frames, the available sampling rate is limited
	// at current one.
	अगर (!पूर्णांकernal ||
	    (dice->substreams_counter > 0 && d->events_per_period > 0)) अणु
		अचिन्हित पूर्णांक frames_per_period = d->events_per_period;
		अचिन्हित पूर्णांक frames_per_buffer = d->events_per_buffer;
		अचिन्हित पूर्णांक rate;

		err = snd_dice_transaction_get_rate(dice, &rate);
		अगर (err < 0) अणु
			mutex_unlock(&dice->mutex);
			जाओ err_locked;
		पूर्ण

		substream->runसमय->hw.rate_min = rate;
		substream->runसमय->hw.rate_max = rate;

		अगर (frames_per_period > 0) अणु
			// For द्विगुन_pcm_frame quirk.
			अगर (rate > 96000 && !dice->disable_द्विगुन_pcm_frames) अणु
				frames_per_period *= 2;
				frames_per_buffer *= 2;
			पूर्ण

			err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(substream->runसमय,
					SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
					frames_per_period, frames_per_period);
			अगर (err < 0) अणु
				mutex_unlock(&dice->mutex);
				जाओ err_locked;
			पूर्ण

			err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(substream->runसमय,
					SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
					frames_per_buffer, frames_per_buffer);
			अगर (err < 0) अणु
				mutex_unlock(&dice->mutex);
				जाओ err_locked;
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&dice->mutex);

	snd_pcm_set_sync(substream);

	वापस 0;
err_locked:
	snd_dice_stream_lock_release(dice);
	वापस err;
पूर्ण

अटल पूर्णांक pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dice *dice = substream->निजी_data;

	snd_dice_stream_lock_release(dice);

	वापस 0;
पूर्ण

अटल पूर्णांक pcm_hw_params(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_dice *dice = substream->निजी_data;
	पूर्णांक err = 0;

	अगर (substream->runसमय->status->state == SNDRV_PCM_STATE_OPEN) अणु
		अचिन्हित पूर्णांक rate = params_rate(hw_params);
		अचिन्हित पूर्णांक events_per_period = params_period_size(hw_params);
		अचिन्हित पूर्णांक events_per_buffer = params_buffer_size(hw_params);

		mutex_lock(&dice->mutex);
		// For द्विगुन_pcm_frame quirk.
		अगर (rate > 96000 && !dice->disable_द्विगुन_pcm_frames) अणु
			events_per_period /= 2;
			events_per_buffer /= 2;
		पूर्ण
		err = snd_dice_stream_reserve_duplex(dice, rate,
					events_per_period, events_per_buffer);
		अगर (err >= 0)
			++dice->substreams_counter;
		mutex_unlock(&dice->mutex);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dice *dice = substream->निजी_data;

	mutex_lock(&dice->mutex);

	अगर (substream->runसमय->status->state != SNDRV_PCM_STATE_OPEN)
		--dice->substreams_counter;

	snd_dice_stream_stop_duplex(dice);

	mutex_unlock(&dice->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dice *dice = substream->निजी_data;
	काष्ठा amdtp_stream *stream = &dice->tx_stream[substream->pcm->device];
	पूर्णांक err;

	mutex_lock(&dice->mutex);
	err = snd_dice_stream_start_duplex(dice);
	mutex_unlock(&dice->mutex);
	अगर (err >= 0)
		amdtp_stream_pcm_prepare(stream);

	वापस 0;
पूर्ण
अटल पूर्णांक playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dice *dice = substream->निजी_data;
	काष्ठा amdtp_stream *stream = &dice->rx_stream[substream->pcm->device];
	पूर्णांक err;

	mutex_lock(&dice->mutex);
	err = snd_dice_stream_start_duplex(dice);
	mutex_unlock(&dice->mutex);
	अगर (err >= 0)
		amdtp_stream_pcm_prepare(stream);

	वापस err;
पूर्ण

अटल पूर्णांक capture_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_dice *dice = substream->निजी_data;
	काष्ठा amdtp_stream *stream = &dice->tx_stream[substream->pcm->device];

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		amdtp_stream_pcm_trigger(stream, substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		amdtp_stream_pcm_trigger(stream, शून्य);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
अटल पूर्णांक playback_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_dice *dice = substream->निजी_data;
	काष्ठा amdtp_stream *stream = &dice->rx_stream[substream->pcm->device];

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		amdtp_stream_pcm_trigger(stream, substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		amdtp_stream_pcm_trigger(stream, शून्य);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dice *dice = substream->निजी_data;
	काष्ठा amdtp_stream *stream = &dice->tx_stream[substream->pcm->device];

	वापस amdtp_करोमुख्य_stream_pcm_poपूर्णांकer(&dice->करोमुख्य, stream);
पूर्ण
अटल snd_pcm_uframes_t playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dice *dice = substream->निजी_data;
	काष्ठा amdtp_stream *stream = &dice->rx_stream[substream->pcm->device];

	वापस amdtp_करोमुख्य_stream_pcm_poपूर्णांकer(&dice->करोमुख्य, stream);
पूर्ण

अटल पूर्णांक capture_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dice *dice = substream->निजी_data;
	काष्ठा amdtp_stream *stream = &dice->tx_stream[substream->pcm->device];

	वापस amdtp_करोमुख्य_stream_pcm_ack(&dice->करोमुख्य, stream);
पूर्ण

अटल पूर्णांक playback_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dice *dice = substream->निजी_data;
	काष्ठा amdtp_stream *stream = &dice->rx_stream[substream->pcm->device];

	वापस amdtp_करोमुख्य_stream_pcm_ack(&dice->करोमुख्य, stream);
पूर्ण

पूर्णांक snd_dice_create_pcm(काष्ठा snd_dice *dice)
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
	अचिन्हित पूर्णांक capture, playback;
	पूर्णांक i, j;
	पूर्णांक err;

	क्रम (i = 0; i < MAX_STREAMS; i++) अणु
		capture = playback = 0;
		क्रम (j = 0; j < SND_DICE_RATE_MODE_COUNT; ++j) अणु
			अगर (dice->tx_pcm_chs[i][j] > 0)
				capture = 1;
			अगर (dice->rx_pcm_chs[i][j] > 0)
				playback = 1;
		पूर्ण

		err = snd_pcm_new(dice->card, "DICE", i, playback, capture,
				  &pcm);
		अगर (err < 0)
			वापस err;
		pcm->निजी_data = dice;
		म_नकल(pcm->name, dice->card->लघुname);

		अगर (capture > 0)
			snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
					&capture_ops);

		अगर (playback > 0)
			snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
					&playback_ops);

		snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_VMALLOC,
					       शून्य, 0, 0);
	पूर्ण

	वापस 0;
पूर्ण
