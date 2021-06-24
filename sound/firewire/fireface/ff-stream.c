<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ff-stream.c - a part of driver क्रम RME Fireface series
 *
 * Copyright (c) 2015-2017 Takashi Sakamoto
 */

#समावेश "ff.h"

#घोषणा CALLBACK_TIMEOUT_MS	200

पूर्णांक snd_ff_stream_get_multiplier_mode(क्रमागत cip_sfc sfc,
				      क्रमागत snd_ff_stream_mode *mode)
अणु
	अटल स्थिर क्रमागत snd_ff_stream_mode modes[] = अणु
		[CIP_SFC_32000] = SND_FF_STREAM_MODE_LOW,
		[CIP_SFC_44100] = SND_FF_STREAM_MODE_LOW,
		[CIP_SFC_48000] = SND_FF_STREAM_MODE_LOW,
		[CIP_SFC_88200] = SND_FF_STREAM_MODE_MID,
		[CIP_SFC_96000] = SND_FF_STREAM_MODE_MID,
		[CIP_SFC_176400] = SND_FF_STREAM_MODE_HIGH,
		[CIP_SFC_192000] = SND_FF_STREAM_MODE_HIGH,
	पूर्ण;

	अगर (sfc >= CIP_SFC_COUNT)
		वापस -EINVAL;

	*mode = modes[sfc];

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम finish_session(काष्ठा snd_ff *ff)
अणु
	ff->spec->protocol->finish_session(ff);
	ff->spec->protocol->चयन_fetching_mode(ff, false);
पूर्ण

अटल पूर्णांक init_stream(काष्ठा snd_ff *ff, काष्ठा amdtp_stream *s)
अणु
	काष्ठा fw_iso_resources *resources;
	क्रमागत amdtp_stream_direction dir;
	पूर्णांक err;

	अगर (s == &ff->tx_stream) अणु
		resources = &ff->tx_resources;
		dir = AMDTP_IN_STREAM;
	पूर्ण अन्यथा अणु
		resources = &ff->rx_resources;
		dir = AMDTP_OUT_STREAM;
	पूर्ण

	err = fw_iso_resources_init(resources, ff->unit);
	अगर (err < 0)
		वापस err;

	err = amdtp_ff_init(s, ff->unit, dir);
	अगर (err < 0)
		fw_iso_resources_destroy(resources);

	वापस err;
पूर्ण

अटल व्योम destroy_stream(काष्ठा snd_ff *ff, काष्ठा amdtp_stream *s)
अणु
	amdtp_stream_destroy(s);

	अगर (s == &ff->tx_stream)
		fw_iso_resources_destroy(&ff->tx_resources);
	अन्यथा
		fw_iso_resources_destroy(&ff->rx_resources);
पूर्ण

पूर्णांक snd_ff_stream_init_duplex(काष्ठा snd_ff *ff)
अणु
	पूर्णांक err;

	err = init_stream(ff, &ff->rx_stream);
	अगर (err < 0)
		वापस err;

	err = init_stream(ff, &ff->tx_stream);
	अगर (err < 0) अणु
		destroy_stream(ff, &ff->rx_stream);
		वापस err;
	पूर्ण

	err = amdtp_करोमुख्य_init(&ff->करोमुख्य);
	अगर (err < 0) अणु
		destroy_stream(ff, &ff->rx_stream);
		destroy_stream(ff, &ff->tx_stream);
	पूर्ण

	वापस err;
पूर्ण

/*
 * This function should be called beक्रमe starting streams or after stopping
 * streams.
 */
व्योम snd_ff_stream_destroy_duplex(काष्ठा snd_ff *ff)
अणु
	amdtp_करोमुख्य_destroy(&ff->करोमुख्य);

	destroy_stream(ff, &ff->rx_stream);
	destroy_stream(ff, &ff->tx_stream);
पूर्ण

पूर्णांक snd_ff_stream_reserve_duplex(काष्ठा snd_ff *ff, अचिन्हित पूर्णांक rate,
				 अचिन्हित पूर्णांक frames_per_period,
				 अचिन्हित पूर्णांक frames_per_buffer)
अणु
	अचिन्हित पूर्णांक curr_rate;
	क्रमागत snd_ff_घड़ी_src src;
	पूर्णांक err;

	err = ff->spec->protocol->get_घड़ी(ff, &curr_rate, &src);
	अगर (err < 0)
		वापस err;

	अगर (ff->substreams_counter == 0 || curr_rate != rate) अणु
		क्रमागत snd_ff_stream_mode mode;
		पूर्णांक i;

		amdtp_करोमुख्य_stop(&ff->करोमुख्य);
		finish_session(ff);

		fw_iso_resources_मुक्त(&ff->tx_resources);
		fw_iso_resources_मुक्त(&ff->rx_resources);

		क्रम (i = 0; i < CIP_SFC_COUNT; ++i) अणु
			अगर (amdtp_rate_table[i] == rate)
				अवरोध;
		पूर्ण
		अगर (i >= CIP_SFC_COUNT)
			वापस -EINVAL;

		err = snd_ff_stream_get_multiplier_mode(i, &mode);
		अगर (err < 0)
			वापस err;

		err = amdtp_ff_set_parameters(&ff->tx_stream, rate,
					ff->spec->pcm_capture_channels[mode]);
		अगर (err < 0)
			वापस err;

		err = amdtp_ff_set_parameters(&ff->rx_stream, rate,
					ff->spec->pcm_playback_channels[mode]);
		अगर (err < 0)
			वापस err;

		err = ff->spec->protocol->allocate_resources(ff, rate);
		अगर (err < 0)
			वापस err;

		err = amdtp_करोमुख्य_set_events_per_period(&ff->करोमुख्य,
					frames_per_period, frames_per_buffer);
		अगर (err < 0) अणु
			fw_iso_resources_मुक्त(&ff->tx_resources);
			fw_iso_resources_मुक्त(&ff->rx_resources);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_ff_stream_start_duplex(काष्ठा snd_ff *ff, अचिन्हित पूर्णांक rate)
अणु
	पूर्णांक err;

	अगर (ff->substreams_counter == 0)
		वापस 0;

	अगर (amdtp_streaming_error(&ff->tx_stream) ||
	    amdtp_streaming_error(&ff->rx_stream)) अणु
		amdtp_करोमुख्य_stop(&ff->करोमुख्य);
		finish_session(ff);
	पूर्ण

	/*
	 * Regardless of current source of घड़ी संकेत, drivers transfer some
	 * packets. Then, the device transfers packets.
	 */
	अगर (!amdtp_stream_running(&ff->rx_stream)) अणु
		पूर्णांक spd = fw_parent_device(ff->unit)->max_speed;

		err = ff->spec->protocol->begin_session(ff, rate);
		अगर (err < 0)
			जाओ error;

		err = amdtp_करोमुख्य_add_stream(&ff->करोमुख्य, &ff->rx_stream,
					      ff->rx_resources.channel, spd);
		अगर (err < 0)
			जाओ error;

		err = amdtp_करोमुख्य_add_stream(&ff->करोमुख्य, &ff->tx_stream,
					      ff->tx_resources.channel, spd);
		अगर (err < 0)
			जाओ error;

		err = amdtp_करोमुख्य_start(&ff->करोमुख्य, 0);
		अगर (err < 0)
			जाओ error;

		अगर (!amdtp_stream_रुको_callback(&ff->rx_stream,
						CALLBACK_TIMEOUT_MS) ||
		    !amdtp_stream_रुको_callback(&ff->tx_stream,
						CALLBACK_TIMEOUT_MS)) अणु
			err = -ETIMEDOUT;
			जाओ error;
		पूर्ण

		err = ff->spec->protocol->चयन_fetching_mode(ff, true);
		अगर (err < 0)
			जाओ error;
	पूर्ण

	वापस 0;
error:
	amdtp_करोमुख्य_stop(&ff->करोमुख्य);
	finish_session(ff);

	वापस err;
पूर्ण

व्योम snd_ff_stream_stop_duplex(काष्ठा snd_ff *ff)
अणु
	अगर (ff->substreams_counter == 0) अणु
		amdtp_करोमुख्य_stop(&ff->करोमुख्य);
		finish_session(ff);

		fw_iso_resources_मुक्त(&ff->tx_resources);
		fw_iso_resources_मुक्त(&ff->rx_resources);
	पूर्ण
पूर्ण

व्योम snd_ff_stream_update_duplex(काष्ठा snd_ff *ff)
अणु
	amdtp_करोमुख्य_stop(&ff->करोमुख्य);

	// The device disजारी to transfer packets.
	amdtp_stream_pcm_पात(&ff->tx_stream);
	amdtp_stream_pcm_पात(&ff->rx_stream);
पूर्ण

व्योम snd_ff_stream_lock_changed(काष्ठा snd_ff *ff)
अणु
	ff->dev_lock_changed = true;
	wake_up(&ff->hwdep_रुको);
पूर्ण

पूर्णांक snd_ff_stream_lock_try(काष्ठा snd_ff *ff)
अणु
	पूर्णांक err;

	spin_lock_irq(&ff->lock);

	/* user land lock this */
	अगर (ff->dev_lock_count < 0) अणु
		err = -EBUSY;
		जाओ end;
	पूर्ण

	/* this is the first समय */
	अगर (ff->dev_lock_count++ == 0)
		snd_ff_stream_lock_changed(ff);
	err = 0;
end:
	spin_unlock_irq(&ff->lock);
	वापस err;
पूर्ण

व्योम snd_ff_stream_lock_release(काष्ठा snd_ff *ff)
अणु
	spin_lock_irq(&ff->lock);

	अगर (WARN_ON(ff->dev_lock_count <= 0))
		जाओ end;
	अगर (--ff->dev_lock_count == 0)
		snd_ff_stream_lock_changed(ff);
end:
	spin_unlock_irq(&ff->lock);
पूर्ण
