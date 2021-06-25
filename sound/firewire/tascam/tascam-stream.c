<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tascam-stream.c - a part of driver क्रम TASCAM FireWire series
 *
 * Copyright (c) 2015 Takashi Sakamoto
 */

#समावेश <linux/delay.h>
#समावेश "tascam.h"

#घोषणा CLOCK_STATUS_MASK      0xffff0000
#घोषणा CLOCK_CONFIG_MASK      0x0000ffff

#घोषणा CALLBACK_TIMEOUT 500

अटल पूर्णांक get_घड़ी(काष्ठा snd_tscm *tscm, u32 *data)
अणु
	पूर्णांक trial = 0;
	__be32 reg;
	पूर्णांक err;

	जबतक (trial++ < 5) अणु
		err = snd_fw_transaction(tscm->unit, TCODE_READ_QUADLET_REQUEST,
				TSCM_ADDR_BASE + TSCM_OFFSET_CLOCK_STATUS,
				&reg, माप(reg), 0);
		अगर (err < 0)
			वापस err;

		*data = be32_to_cpu(reg);
		अगर (*data & CLOCK_STATUS_MASK)
			अवरोध;

		// In पूर्णांकermediate state after changing घड़ी status.
		msleep(50);
	पूर्ण

	// Still in the पूर्णांकermediate state.
	अगर (trial >= 5)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल पूर्णांक set_घड़ी(काष्ठा snd_tscm *tscm, अचिन्हित पूर्णांक rate,
		     क्रमागत snd_tscm_घड़ी घड़ी)
अणु
	u32 data;
	__be32 reg;
	पूर्णांक err;

	err = get_घड़ी(tscm, &data);
	अगर (err < 0)
		वापस err;
	data &= CLOCK_CONFIG_MASK;

	अगर (rate > 0) अणु
		data &= 0x000000ff;
		/* Base rate. */
		अगर ((rate % 44100) == 0) अणु
			data |= 0x00000100;
			/* Multiplier. */
			अगर (rate / 44100 == 2)
				data |= 0x00008000;
		पूर्ण अन्यथा अगर ((rate % 48000) == 0) अणु
			data |= 0x00000200;
			/* Multiplier. */
			अगर (rate / 48000 == 2)
				data |= 0x00008000;
		पूर्ण अन्यथा अणु
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	अगर (घड़ी != पूर्णांक_उच्च) अणु
		data &= 0x0000ff00;
		data |= घड़ी + 1;
	पूर्ण

	reg = cpu_to_be32(data);

	err = snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				 TSCM_ADDR_BASE + TSCM_OFFSET_CLOCK_STATUS,
				 &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	अगर (data & 0x00008000)
		reg = cpu_to_be32(0x0000001a);
	अन्यथा
		reg = cpu_to_be32(0x0000000d);

	वापस snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				  TSCM_ADDR_BASE + TSCM_OFFSET_MULTIPLEX_MODE,
				  &reg, माप(reg), 0);
पूर्ण

पूर्णांक snd_tscm_stream_get_rate(काष्ठा snd_tscm *tscm, अचिन्हित पूर्णांक *rate)
अणु
	u32 data;
	पूर्णांक err;

	err = get_घड़ी(tscm, &data);
	अगर (err < 0)
		वापस err;

	data = (data & 0xff000000) >> 24;

	/* Check base rate. */
	अगर ((data & 0x0f) == 0x01)
		*rate = 44100;
	अन्यथा अगर ((data & 0x0f) == 0x02)
		*rate = 48000;
	अन्यथा
		वापस -EAGAIN;

	/* Check multiplier. */
	अगर ((data & 0xf0) == 0x80)
		*rate *= 2;
	अन्यथा अगर ((data & 0xf0) != 0x00)
		वापस -EAGAIN;

	वापस err;
पूर्ण

पूर्णांक snd_tscm_stream_get_घड़ी(काष्ठा snd_tscm *tscm, क्रमागत snd_tscm_घड़ी *घड़ी)
अणु
	u32 data;
	पूर्णांक err;

	err = get_घड़ी(tscm, &data);
	अगर (err < 0)
		वापस err;

	*घड़ी = ((data & 0x00ff0000) >> 16) - 1;
	अगर (*घड़ी < 0 || *घड़ी > SND_TSCM_CLOCK_ADAT)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक enable_data_channels(काष्ठा snd_tscm *tscm)
अणु
	__be32 reg;
	u32 data;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	data = 0;
	क्रम (i = 0; i < tscm->spec->pcm_capture_analog_channels; ++i)
		data |= BIT(i);
	अगर (tscm->spec->has_adat)
		data |= 0x0000ff00;
	अगर (tscm->spec->has_spdअगर)
		data |= 0x00030000;

	reg = cpu_to_be32(data);
	err = snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				 TSCM_ADDR_BASE + TSCM_OFFSET_TX_PCM_CHANNELS,
				 &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	data = 0;
	क्रम (i = 0; i < tscm->spec->pcm_playback_analog_channels; ++i)
		data |= BIT(i);
	अगर (tscm->spec->has_adat)
		data |= 0x0000ff00;
	अगर (tscm->spec->has_spdअगर)
		data |= 0x00030000;

	reg = cpu_to_be32(data);
	वापस snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				  TSCM_ADDR_BASE + TSCM_OFFSET_RX_PCM_CHANNELS,
				  &reg, माप(reg), 0);
पूर्ण

अटल पूर्णांक set_stream_क्रमmats(काष्ठा snd_tscm *tscm, अचिन्हित पूर्णांक rate)
अणु
	__be32 reg;
	पूर्णांक err;

	// Set an option क्रम unknown purpose.
	reg = cpu_to_be32(0x00200000);
	err = snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				 TSCM_ADDR_BASE + TSCM_OFFSET_SET_OPTION,
				 &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	वापस enable_data_channels(tscm);
पूर्ण

अटल व्योम finish_session(काष्ठा snd_tscm *tscm)
अणु
	__be32 reg;

	reg = 0;
	snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
			   TSCM_ADDR_BASE + TSCM_OFFSET_START_STREAMING,
			   &reg, माप(reg), 0);

	reg = 0;
	snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
			   TSCM_ADDR_BASE + TSCM_OFFSET_ISOC_RX_ON,
			   &reg, माप(reg), 0);

	// Unरेजिस्टर channels.
	reg = cpu_to_be32(0x00000000);
	snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
			   TSCM_ADDR_BASE + TSCM_OFFSET_ISOC_TX_CH,
			   &reg, माप(reg), 0);
	reg = cpu_to_be32(0x00000000);
	snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
			   TSCM_ADDR_BASE + TSCM_OFFSET_UNKNOWN,
			   &reg, माप(reg), 0);
	reg = cpu_to_be32(0x00000000);
	snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
			   TSCM_ADDR_BASE + TSCM_OFFSET_ISOC_RX_CH,
			   &reg, माप(reg), 0);
पूर्ण

अटल पूर्णांक begin_session(काष्ठा snd_tscm *tscm)
अणु
	__be32 reg;
	पूर्णांक err;

	// Register the isochronous channel क्रम transmitting stream.
	reg = cpu_to_be32(tscm->tx_resources.channel);
	err = snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				 TSCM_ADDR_BASE + TSCM_OFFSET_ISOC_TX_CH,
				 &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	// Unknown.
	reg = cpu_to_be32(0x00000002);
	err = snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				 TSCM_ADDR_BASE + TSCM_OFFSET_UNKNOWN,
				 &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	// Register the isochronous channel क्रम receiving stream.
	reg = cpu_to_be32(tscm->rx_resources.channel);
	err = snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				 TSCM_ADDR_BASE + TSCM_OFFSET_ISOC_RX_CH,
				 &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	reg = cpu_to_be32(0x00000001);
	err = snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				 TSCM_ADDR_BASE + TSCM_OFFSET_START_STREAMING,
				 &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	reg = cpu_to_be32(0x00000001);
	err = snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				 TSCM_ADDR_BASE + TSCM_OFFSET_ISOC_RX_ON,
				 &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	// Set an option क्रम unknown purpose.
	reg = cpu_to_be32(0x00002000);
	err = snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				 TSCM_ADDR_BASE + TSCM_OFFSET_SET_OPTION,
				 &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	// Start multiplexing PCM samples on packets.
	reg = cpu_to_be32(0x00000001);
	वापस snd_fw_transaction(tscm->unit,
				  TCODE_WRITE_QUADLET_REQUEST,
				  TSCM_ADDR_BASE + TSCM_OFFSET_ISOC_TX_ON,
				  &reg, माप(reg), 0);
पूर्ण

अटल पूर्णांक keep_resources(काष्ठा snd_tscm *tscm, अचिन्हित पूर्णांक rate,
			  काष्ठा amdtp_stream *stream)
अणु
	काष्ठा fw_iso_resources *resources;
	पूर्णांक err;

	अगर (stream == &tscm->tx_stream)
		resources = &tscm->tx_resources;
	अन्यथा
		resources = &tscm->rx_resources;

	err = amdtp_tscm_set_parameters(stream, rate);
	अगर (err < 0)
		वापस err;

	वापस fw_iso_resources_allocate(resources,
				amdtp_stream_get_max_payload(stream),
				fw_parent_device(tscm->unit)->max_speed);
पूर्ण

अटल पूर्णांक init_stream(काष्ठा snd_tscm *tscm, काष्ठा amdtp_stream *s)
अणु
	काष्ठा fw_iso_resources *resources;
	क्रमागत amdtp_stream_direction dir;
	अचिन्हित पूर्णांक pcm_channels;
	पूर्णांक err;

	अगर (s == &tscm->tx_stream) अणु
		resources = &tscm->tx_resources;
		dir = AMDTP_IN_STREAM;
		pcm_channels = tscm->spec->pcm_capture_analog_channels;
	पूर्ण अन्यथा अणु
		resources = &tscm->rx_resources;
		dir = AMDTP_OUT_STREAM;
		pcm_channels = tscm->spec->pcm_playback_analog_channels;
	पूर्ण

	अगर (tscm->spec->has_adat)
		pcm_channels += 8;
	अगर (tscm->spec->has_spdअगर)
		pcm_channels += 2;

	err = fw_iso_resources_init(resources, tscm->unit);
	अगर (err < 0)
		वापस err;

	err = amdtp_tscm_init(s, tscm->unit, dir, pcm_channels);
	अगर (err < 0)
		fw_iso_resources_मुक्त(resources);

	वापस err;
पूर्ण

अटल व्योम destroy_stream(काष्ठा snd_tscm *tscm, काष्ठा amdtp_stream *s)
अणु
	amdtp_stream_destroy(s);

	अगर (s == &tscm->tx_stream)
		fw_iso_resources_destroy(&tscm->tx_resources);
	अन्यथा
		fw_iso_resources_destroy(&tscm->rx_resources);
पूर्ण

पूर्णांक snd_tscm_stream_init_duplex(काष्ठा snd_tscm *tscm)
अणु
	पूर्णांक err;

	err = init_stream(tscm, &tscm->tx_stream);
	अगर (err < 0)
		वापस err;

	err = init_stream(tscm, &tscm->rx_stream);
	अगर (err < 0) अणु
		destroy_stream(tscm, &tscm->tx_stream);
		वापस err;
	पूर्ण

	err = amdtp_करोमुख्य_init(&tscm->करोमुख्य);
	अगर (err < 0) अणु
		destroy_stream(tscm, &tscm->tx_stream);
		destroy_stream(tscm, &tscm->rx_stream);
	पूर्ण

	वापस err;
पूर्ण

// At bus reset, streaming is stopped and some रेजिस्टरs are clear.
व्योम snd_tscm_stream_update_duplex(काष्ठा snd_tscm *tscm)
अणु
	amdtp_करोमुख्य_stop(&tscm->करोमुख्य);

	amdtp_stream_pcm_पात(&tscm->tx_stream);
	amdtp_stream_pcm_पात(&tscm->rx_stream);
पूर्ण

// This function should be called beक्रमe starting streams or after stopping
// streams.
व्योम snd_tscm_stream_destroy_duplex(काष्ठा snd_tscm *tscm)
अणु
	amdtp_करोमुख्य_destroy(&tscm->करोमुख्य);

	destroy_stream(tscm, &tscm->rx_stream);
	destroy_stream(tscm, &tscm->tx_stream);
पूर्ण

पूर्णांक snd_tscm_stream_reserve_duplex(काष्ठा snd_tscm *tscm, अचिन्हित पूर्णांक rate,
				   अचिन्हित पूर्णांक frames_per_period,
				   अचिन्हित पूर्णांक frames_per_buffer)
अणु
	अचिन्हित पूर्णांक curr_rate;
	पूर्णांक err;

	err = snd_tscm_stream_get_rate(tscm, &curr_rate);
	अगर (err < 0)
		वापस err;

	अगर (tscm->substreams_counter == 0 || rate != curr_rate) अणु
		amdtp_करोमुख्य_stop(&tscm->करोमुख्य);

		finish_session(tscm);

		fw_iso_resources_मुक्त(&tscm->tx_resources);
		fw_iso_resources_मुक्त(&tscm->rx_resources);

		err = set_घड़ी(tscm, rate, पूर्णांक_उच्च);
		अगर (err < 0)
			वापस err;

		err = keep_resources(tscm, rate, &tscm->tx_stream);
		अगर (err < 0)
			वापस err;

		err = keep_resources(tscm, rate, &tscm->rx_stream);
		अगर (err < 0) अणु
			fw_iso_resources_मुक्त(&tscm->tx_resources);
			वापस err;
		पूर्ण

		err = amdtp_करोमुख्य_set_events_per_period(&tscm->करोमुख्य,
					frames_per_period, frames_per_buffer);
		अगर (err < 0) अणु
			fw_iso_resources_मुक्त(&tscm->tx_resources);
			fw_iso_resources_मुक्त(&tscm->rx_resources);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_tscm_stream_start_duplex(काष्ठा snd_tscm *tscm, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक generation = tscm->rx_resources.generation;
	पूर्णांक err;

	अगर (tscm->substreams_counter == 0)
		वापस 0;

	अगर (amdtp_streaming_error(&tscm->rx_stream) ||
	    amdtp_streaming_error(&tscm->tx_stream)) अणु
		amdtp_करोमुख्य_stop(&tscm->करोमुख्य);
		finish_session(tscm);
	पूर्ण

	अगर (generation != fw_parent_device(tscm->unit)->card->generation) अणु
		err = fw_iso_resources_update(&tscm->tx_resources);
		अगर (err < 0)
			जाओ error;

		err = fw_iso_resources_update(&tscm->rx_resources);
		अगर (err < 0)
			जाओ error;
	पूर्ण

	अगर (!amdtp_stream_running(&tscm->rx_stream)) अणु
		पूर्णांक spd = fw_parent_device(tscm->unit)->max_speed;

		err = set_stream_क्रमmats(tscm, rate);
		अगर (err < 0)
			जाओ error;

		err = begin_session(tscm);
		अगर (err < 0)
			जाओ error;

		err = amdtp_करोमुख्य_add_stream(&tscm->करोमुख्य, &tscm->rx_stream,
					      tscm->rx_resources.channel, spd);
		अगर (err < 0)
			जाओ error;

		err = amdtp_करोमुख्य_add_stream(&tscm->करोमुख्य, &tscm->tx_stream,
					      tscm->tx_resources.channel, spd);
		अगर (err < 0)
			जाओ error;

		err = amdtp_करोमुख्य_start(&tscm->करोमुख्य, 0);
		अगर (err < 0)
			वापस err;

		अगर (!amdtp_stream_रुको_callback(&tscm->rx_stream,
						CALLBACK_TIMEOUT) ||
		    !amdtp_stream_रुको_callback(&tscm->tx_stream,
						CALLBACK_TIMEOUT)) अणु
			err = -ETIMEDOUT;
			जाओ error;
		पूर्ण
	पूर्ण

	वापस 0;
error:
	amdtp_करोमुख्य_stop(&tscm->करोमुख्य);
	finish_session(tscm);

	वापस err;
पूर्ण

व्योम snd_tscm_stream_stop_duplex(काष्ठा snd_tscm *tscm)
अणु
	अगर (tscm->substreams_counter == 0) अणु
		amdtp_करोमुख्य_stop(&tscm->करोमुख्य);
		finish_session(tscm);

		fw_iso_resources_मुक्त(&tscm->tx_resources);
		fw_iso_resources_मुक्त(&tscm->rx_resources);
	पूर्ण
पूर्ण

व्योम snd_tscm_stream_lock_changed(काष्ठा snd_tscm *tscm)
अणु
	tscm->dev_lock_changed = true;
	wake_up(&tscm->hwdep_रुको);
पूर्ण

पूर्णांक snd_tscm_stream_lock_try(काष्ठा snd_tscm *tscm)
अणु
	पूर्णांक err;

	spin_lock_irq(&tscm->lock);

	/* user land lock this */
	अगर (tscm->dev_lock_count < 0) अणु
		err = -EBUSY;
		जाओ end;
	पूर्ण

	/* this is the first समय */
	अगर (tscm->dev_lock_count++ == 0)
		snd_tscm_stream_lock_changed(tscm);
	err = 0;
end:
	spin_unlock_irq(&tscm->lock);
	वापस err;
पूर्ण

व्योम snd_tscm_stream_lock_release(काष्ठा snd_tscm *tscm)
अणु
	spin_lock_irq(&tscm->lock);

	अगर (WARN_ON(tscm->dev_lock_count <= 0))
		जाओ end;
	अगर (--tscm->dev_lock_count == 0)
		snd_tscm_stream_lock_changed(tscm);
end:
	spin_unlock_irq(&tscm->lock);
पूर्ण
