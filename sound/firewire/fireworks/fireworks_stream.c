<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fireworks_stream.c - a part of driver क्रम Fireworks based devices
 *
 * Copyright (c) 2013-2014 Takashi Sakamoto
 */
#समावेश "./fireworks.h"

#घोषणा CALLBACK_TIMEOUT	100

अटल पूर्णांक init_stream(काष्ठा snd_efw *efw, काष्ठा amdtp_stream *stream)
अणु
	काष्ठा cmp_connection *conn;
	क्रमागत cmp_direction c_dir;
	क्रमागत amdtp_stream_direction s_dir;
	पूर्णांक err;

	अगर (stream == &efw->tx_stream) अणु
		conn = &efw->out_conn;
		c_dir = CMP_OUTPUT;
		s_dir = AMDTP_IN_STREAM;
	पूर्ण अन्यथा अणु
		conn = &efw->in_conn;
		c_dir = CMP_INPUT;
		s_dir = AMDTP_OUT_STREAM;
	पूर्ण

	err = cmp_connection_init(conn, efw->unit, c_dir, 0);
	अगर (err < 0)
		वापस err;

	err = amdtp_am824_init(stream, efw->unit, s_dir, CIP_BLOCKING);
	अगर (err < 0) अणु
		amdtp_stream_destroy(stream);
		cmp_connection_destroy(conn);
		वापस err;
	पूर्ण

	अगर (stream == &efw->tx_stream) अणु
		// Fireworks transmits NODATA packets with TAG0.
		efw->tx_stream.flags |= CIP_EMPTY_WITH_TAG0;
		// Fireworks has its own meaning क्रम dbc.
		efw->tx_stream.flags |= CIP_DBC_IS_END_EVENT;
		// Fireworks reset dbc at bus reset.
		efw->tx_stream.flags |= CIP_SKIP_DBC_ZERO_CHECK;
		// But Recent firmwares starts packets with non-zero dbc.
		// Driver version 5.7.6 installs firmware version 5.7.3.
		अगर (efw->is_fireworks3 &&
		    (efw->firmware_version == 0x5070000 ||
		     efw->firmware_version == 0x5070300 ||
		     efw->firmware_version == 0x5080000))
			efw->tx_stream.flags |= CIP_UNALIGHED_DBC;
		// AudioFire9 always reports wrong dbs.
		अगर (efw->is_af9)
			efw->tx_stream.flags |= CIP_WRONG_DBS;
		// Firmware version 5.5 reports fixed पूर्णांकerval क्रम dbc.
		अगर (efw->firmware_version == 0x5050000)
			efw->tx_stream.ctx_data.tx.dbc_पूर्णांकerval = 8;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक start_stream(काष्ठा snd_efw *efw, काष्ठा amdtp_stream *stream,
			अचिन्हित पूर्णांक rate)
अणु
	काष्ठा cmp_connection *conn;
	पूर्णांक err;

	अगर (stream == &efw->tx_stream)
		conn = &efw->out_conn;
	अन्यथा
		conn = &efw->in_conn;

	// Establish connection via CMP.
	err = cmp_connection_establish(conn);
	अगर (err < 0)
		वापस err;

	// Start amdtp stream.
	err = amdtp_करोमुख्य_add_stream(&efw->करोमुख्य, stream,
				      conn->resources.channel, conn->speed);
	अगर (err < 0) अणु
		cmp_connection_अवरोध(conn);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

// This function should be called beक्रमe starting the stream or after stopping
// the streams.
अटल व्योम destroy_stream(काष्ठा snd_efw *efw, काष्ठा amdtp_stream *stream)
अणु
	amdtp_stream_destroy(stream);

	अगर (stream == &efw->tx_stream)
		cmp_connection_destroy(&efw->out_conn);
	अन्यथा
		cmp_connection_destroy(&efw->in_conn);
पूर्ण

अटल पूर्णांक
check_connection_used_by_others(काष्ठा snd_efw *efw, काष्ठा amdtp_stream *s)
अणु
	काष्ठा cmp_connection *conn;
	bool used;
	पूर्णांक err;

	अगर (s == &efw->tx_stream)
		conn = &efw->out_conn;
	अन्यथा
		conn = &efw->in_conn;

	err = cmp_connection_check_used(conn, &used);
	अगर ((err >= 0) && used && !amdtp_stream_running(s)) अणु
		dev_err(&efw->unit->device,
			"Connection established by others: %cPCR[%d]\n",
			(conn->direction == CMP_OUTPUT) ? 'o' : 'i',
			conn->pcr_index);
		err = -EBUSY;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक snd_efw_stream_init_duplex(काष्ठा snd_efw *efw)
अणु
	पूर्णांक err;

	err = init_stream(efw, &efw->tx_stream);
	अगर (err < 0)
		वापस err;

	err = init_stream(efw, &efw->rx_stream);
	अगर (err < 0) अणु
		destroy_stream(efw, &efw->tx_stream);
		वापस err;
	पूर्ण

	err = amdtp_करोमुख्य_init(&efw->करोमुख्य);
	अगर (err < 0) अणु
		destroy_stream(efw, &efw->tx_stream);
		destroy_stream(efw, &efw->rx_stream);
		वापस err;
	पूर्ण

	// set IEC61883 compliant mode (actually not fully compliant...).
	err = snd_efw_command_set_tx_mode(efw, SND_EFW_TRANSPORT_MODE_IEC61883);
	अगर (err < 0) अणु
		destroy_stream(efw, &efw->tx_stream);
		destroy_stream(efw, &efw->rx_stream);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक keep_resources(काष्ठा snd_efw *efw, काष्ठा amdtp_stream *stream,
			  अचिन्हित पूर्णांक rate, अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित पूर्णांक pcm_channels;
	अचिन्हित पूर्णांक midi_ports;
	काष्ठा cmp_connection *conn;
	पूर्णांक err;

	अगर (stream == &efw->tx_stream) अणु
		pcm_channels = efw->pcm_capture_channels[mode];
		midi_ports = efw->midi_out_ports;
		conn = &efw->out_conn;
	पूर्ण अन्यथा अणु
		pcm_channels = efw->pcm_playback_channels[mode];
		midi_ports = efw->midi_in_ports;
		conn = &efw->in_conn;
	पूर्ण

	err = amdtp_am824_set_parameters(stream, rate, pcm_channels,
					 midi_ports, false);
	अगर (err < 0)
		वापस err;

	वापस cmp_connection_reserve(conn, amdtp_stream_get_max_payload(stream));
पूर्ण

पूर्णांक snd_efw_stream_reserve_duplex(काष्ठा snd_efw *efw, अचिन्हित पूर्णांक rate,
				  अचिन्हित पूर्णांक frames_per_period,
				  अचिन्हित पूर्णांक frames_per_buffer)
अणु
	अचिन्हित पूर्णांक curr_rate;
	पूर्णांक err;

	// Considering JACK/FFADO streaming:
	// TODO: This can be हटाओd hwdep functionality becomes popular.
	err = check_connection_used_by_others(efw, &efw->rx_stream);
	अगर (err < 0)
		वापस err;

	// stop streams अगर rate is dअगरferent.
	err = snd_efw_command_get_sampling_rate(efw, &curr_rate);
	अगर (err < 0)
		वापस err;
	अगर (rate == 0)
		rate = curr_rate;
	अगर (rate != curr_rate) अणु
		amdtp_करोमुख्य_stop(&efw->करोमुख्य);

		cmp_connection_अवरोध(&efw->out_conn);
		cmp_connection_अवरोध(&efw->in_conn);

		cmp_connection_release(&efw->out_conn);
		cmp_connection_release(&efw->in_conn);
	पूर्ण

	अगर (efw->substreams_counter == 0 || rate != curr_rate) अणु
		अचिन्हित पूर्णांक mode;

		err = snd_efw_command_set_sampling_rate(efw, rate);
		अगर (err < 0)
			वापस err;

		err = snd_efw_get_multiplier_mode(rate, &mode);
		अगर (err < 0)
			वापस err;

		err = keep_resources(efw, &efw->tx_stream, rate, mode);
		अगर (err < 0)
			वापस err;

		err = keep_resources(efw, &efw->rx_stream, rate, mode);
		अगर (err < 0) अणु
			cmp_connection_release(&efw->in_conn);
			वापस err;
		पूर्ण

		err = amdtp_करोमुख्य_set_events_per_period(&efw->करोमुख्य,
					frames_per_period, frames_per_buffer);
		अगर (err < 0) अणु
			cmp_connection_release(&efw->in_conn);
			cmp_connection_release(&efw->out_conn);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_efw_stream_start_duplex(काष्ठा snd_efw *efw)
अणु
	अचिन्हित पूर्णांक rate;
	पूर्णांक err = 0;

	// Need no substreams.
	अगर (efw->substreams_counter == 0)
		वापस -EIO;

	अगर (amdtp_streaming_error(&efw->rx_stream) ||
	    amdtp_streaming_error(&efw->tx_stream)) अणु
		amdtp_करोमुख्य_stop(&efw->करोमुख्य);
		cmp_connection_अवरोध(&efw->out_conn);
		cmp_connection_अवरोध(&efw->in_conn);
	पूर्ण

	err = snd_efw_command_get_sampling_rate(efw, &rate);
	अगर (err < 0)
		वापस err;

	अगर (!amdtp_stream_running(&efw->rx_stream)) अणु
		err = start_stream(efw, &efw->rx_stream, rate);
		अगर (err < 0)
			जाओ error;

		err = start_stream(efw, &efw->tx_stream, rate);
		अगर (err < 0)
			जाओ error;

		err = amdtp_करोमुख्य_start(&efw->करोमुख्य, 0);
		अगर (err < 0)
			जाओ error;

		// Wait first callback.
		अगर (!amdtp_stream_रुको_callback(&efw->rx_stream,
						CALLBACK_TIMEOUT) ||
		    !amdtp_stream_रुको_callback(&efw->tx_stream,
						CALLBACK_TIMEOUT)) अणु
			err = -ETIMEDOUT;
			जाओ error;
		पूर्ण
	पूर्ण

	वापस 0;
error:
	amdtp_करोमुख्य_stop(&efw->करोमुख्य);

	cmp_connection_अवरोध(&efw->out_conn);
	cmp_connection_अवरोध(&efw->in_conn);

	वापस err;
पूर्ण

व्योम snd_efw_stream_stop_duplex(काष्ठा snd_efw *efw)
अणु
	अगर (efw->substreams_counter == 0) अणु
		amdtp_करोमुख्य_stop(&efw->करोमुख्य);

		cmp_connection_अवरोध(&efw->out_conn);
		cmp_connection_अवरोध(&efw->in_conn);

		cmp_connection_release(&efw->out_conn);
		cmp_connection_release(&efw->in_conn);
	पूर्ण
पूर्ण

व्योम snd_efw_stream_update_duplex(काष्ठा snd_efw *efw)
अणु
	amdtp_करोमुख्य_stop(&efw->करोमुख्य);

	cmp_connection_अवरोध(&efw->out_conn);
	cmp_connection_अवरोध(&efw->in_conn);

	amdtp_stream_pcm_पात(&efw->rx_stream);
	amdtp_stream_pcm_पात(&efw->tx_stream);
पूर्ण

व्योम snd_efw_stream_destroy_duplex(काष्ठा snd_efw *efw)
अणु
	amdtp_करोमुख्य_destroy(&efw->करोमुख्य);

	destroy_stream(efw, &efw->rx_stream);
	destroy_stream(efw, &efw->tx_stream);
पूर्ण

व्योम snd_efw_stream_lock_changed(काष्ठा snd_efw *efw)
अणु
	efw->dev_lock_changed = true;
	wake_up(&efw->hwdep_रुको);
पूर्ण

पूर्णांक snd_efw_stream_lock_try(काष्ठा snd_efw *efw)
अणु
	पूर्णांक err;

	spin_lock_irq(&efw->lock);

	/* user land lock this */
	अगर (efw->dev_lock_count < 0) अणु
		err = -EBUSY;
		जाओ end;
	पूर्ण

	/* this is the first समय */
	अगर (efw->dev_lock_count++ == 0)
		snd_efw_stream_lock_changed(efw);
	err = 0;
end:
	spin_unlock_irq(&efw->lock);
	वापस err;
पूर्ण

व्योम snd_efw_stream_lock_release(काष्ठा snd_efw *efw)
अणु
	spin_lock_irq(&efw->lock);

	अगर (WARN_ON(efw->dev_lock_count <= 0))
		जाओ end;
	अगर (--efw->dev_lock_count == 0)
		snd_efw_stream_lock_changed(efw);
end:
	spin_unlock_irq(&efw->lock);
पूर्ण
