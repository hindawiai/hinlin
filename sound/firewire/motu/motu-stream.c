<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * motu-stream.c - a part of driver क्रम MOTU FireWire series
 *
 * Copyright (c) 2015-2017 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#समावेश "motu.h"

#घोषणा	CALLBACK_TIMEOUT	200

#घोषणा ISOC_COMM_CONTROL_OFFSET		0x0b00
#घोषणा  ISOC_COMM_CONTROL_MASK			0xffff0000
#घोषणा  CHANGE_RX_ISOC_COMM_STATE		0x80000000
#घोषणा  RX_ISOC_COMM_IS_ACTIVATED		0x40000000
#घोषणा  RX_ISOC_COMM_CHANNEL_MASK		0x3f000000
#घोषणा  RX_ISOC_COMM_CHANNEL_SHIFT		24
#घोषणा  CHANGE_TX_ISOC_COMM_STATE		0x00800000
#घोषणा  TX_ISOC_COMM_IS_ACTIVATED		0x00400000
#घोषणा  TX_ISOC_COMM_CHANNEL_MASK		0x003f0000
#घोषणा  TX_ISOC_COMM_CHANNEL_SHIFT		16

#घोषणा PACKET_FORMAT_OFFSET			0x0b10
#घोषणा  TX_PACKET_EXCLUDE_DIFFERED_DATA_CHUNKS	0x00000080
#घोषणा  RX_PACKET_EXCLUDE_DIFFERED_DATA_CHUNKS	0x00000040
#घोषणा  TX_PACKET_TRANSMISSION_SPEED_MASK	0x0000000f

अटल पूर्णांक keep_resources(काष्ठा snd_motu *motu, अचिन्हित पूर्णांक rate,
			  काष्ठा amdtp_stream *stream)
अणु
	काष्ठा fw_iso_resources *resources;
	काष्ठा snd_motu_packet_क्रमmat *packet_क्रमmat;
	अचिन्हित पूर्णांक midi_ports = 0;
	पूर्णांक err;

	अगर (stream == &motu->rx_stream) अणु
		resources = &motu->rx_resources;
		packet_क्रमmat = &motu->rx_packet_क्रमmats;

		अगर ((motu->spec->flags & SND_MOTU_SPEC_RX_MIDI_2ND_Q) ||
		    (motu->spec->flags & SND_MOTU_SPEC_RX_MIDI_3RD_Q))
			midi_ports = 1;
	पूर्ण अन्यथा अणु
		resources = &motu->tx_resources;
		packet_क्रमmat = &motu->tx_packet_क्रमmats;

		अगर ((motu->spec->flags & SND_MOTU_SPEC_TX_MIDI_2ND_Q) ||
		    (motu->spec->flags & SND_MOTU_SPEC_TX_MIDI_3RD_Q))
			midi_ports = 1;
	पूर्ण

	err = amdtp_motu_set_parameters(stream, rate, midi_ports,
					packet_क्रमmat);
	अगर (err < 0)
		वापस err;

	वापस fw_iso_resources_allocate(resources,
				amdtp_stream_get_max_payload(stream),
				fw_parent_device(motu->unit)->max_speed);
पूर्ण

अटल पूर्णांक begin_session(काष्ठा snd_motu *motu)
अणु
	__be32 reg;
	u32 data;
	पूर्णांक err;

	// Configure the unit to start isochronous communication.
	err = snd_motu_transaction_पढ़ो(motu, ISOC_COMM_CONTROL_OFFSET, &reg,
					माप(reg));
	अगर (err < 0)
		वापस err;
	data = be32_to_cpu(reg) & ~ISOC_COMM_CONTROL_MASK;

	data |= CHANGE_RX_ISOC_COMM_STATE | RX_ISOC_COMM_IS_ACTIVATED |
		(motu->rx_resources.channel << RX_ISOC_COMM_CHANNEL_SHIFT) |
		CHANGE_TX_ISOC_COMM_STATE | TX_ISOC_COMM_IS_ACTIVATED |
		(motu->tx_resources.channel << TX_ISOC_COMM_CHANNEL_SHIFT);

	reg = cpu_to_be32(data);
	वापस snd_motu_transaction_ग_लिखो(motu, ISOC_COMM_CONTROL_OFFSET, &reg,
					  माप(reg));
पूर्ण

अटल व्योम finish_session(काष्ठा snd_motu *motu)
अणु
	__be32 reg;
	u32 data;
	पूर्णांक err;

	err = snd_motu_protocol_चयन_fetching_mode(motu, false);
	अगर (err < 0)
		वापस;

	err = snd_motu_transaction_पढ़ो(motu, ISOC_COMM_CONTROL_OFFSET, &reg,
					माप(reg));
	अगर (err < 0)
		वापस;
	data = be32_to_cpu(reg);

	data &= ~(RX_ISOC_COMM_IS_ACTIVATED | TX_ISOC_COMM_IS_ACTIVATED);
	data |= CHANGE_RX_ISOC_COMM_STATE | CHANGE_TX_ISOC_COMM_STATE;

	reg = cpu_to_be32(data);
	snd_motu_transaction_ग_लिखो(motu, ISOC_COMM_CONTROL_OFFSET, &reg,
				   माप(reg));
पूर्ण

पूर्णांक snd_motu_stream_cache_packet_क्रमmats(काष्ठा snd_motu *motu)
अणु
	पूर्णांक err;

	err = snd_motu_protocol_cache_packet_क्रमmats(motu);
	अगर (err < 0)
		वापस err;

	अगर (motu->spec->flags & SND_MOTU_SPEC_TX_MIDI_2ND_Q) अणु
		motu->tx_packet_क्रमmats.midi_flag_offset = 4;
		motu->tx_packet_क्रमmats.midi_byte_offset = 6;
	पूर्ण अन्यथा अगर (motu->spec->flags & SND_MOTU_SPEC_TX_MIDI_3RD_Q) अणु
		motu->tx_packet_क्रमmats.midi_flag_offset = 8;
		motu->tx_packet_क्रमmats.midi_byte_offset = 7;
	पूर्ण

	अगर (motu->spec->flags & SND_MOTU_SPEC_RX_MIDI_2ND_Q) अणु
		motu->rx_packet_क्रमmats.midi_flag_offset = 4;
		motu->rx_packet_क्रमmats.midi_byte_offset = 6;
	पूर्ण अन्यथा अगर (motu->spec->flags & SND_MOTU_SPEC_RX_MIDI_3RD_Q) अणु
		motu->rx_packet_क्रमmats.midi_flag_offset = 8;
		motu->rx_packet_क्रमmats.midi_byte_offset = 7;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_motu_stream_reserve_duplex(काष्ठा snd_motu *motu, अचिन्हित पूर्णांक rate,
				   अचिन्हित पूर्णांक frames_per_period,
				   अचिन्हित पूर्णांक frames_per_buffer)
अणु
	अचिन्हित पूर्णांक curr_rate;
	पूर्णांक err;

	err = snd_motu_protocol_get_घड़ी_rate(motu, &curr_rate);
	अगर (err < 0)
		वापस err;
	अगर (rate == 0)
		rate = curr_rate;

	अगर (motu->substreams_counter == 0 || curr_rate != rate) अणु
		amdtp_करोमुख्य_stop(&motu->करोमुख्य);
		finish_session(motu);

		fw_iso_resources_मुक्त(&motu->tx_resources);
		fw_iso_resources_मुक्त(&motu->rx_resources);

		err = snd_motu_protocol_set_घड़ी_rate(motu, rate);
		अगर (err < 0) अणु
			dev_err(&motu->unit->device,
				"fail to set sampling rate: %d\n", err);
			वापस err;
		पूर्ण

		err = snd_motu_stream_cache_packet_क्रमmats(motu);
		अगर (err < 0)
			वापस err;

		err = keep_resources(motu, rate, &motu->tx_stream);
		अगर (err < 0)
			वापस err;

		err = keep_resources(motu, rate, &motu->rx_stream);
		अगर (err < 0) अणु
			fw_iso_resources_मुक्त(&motu->tx_resources);
			वापस err;
		पूर्ण

		err = amdtp_करोमुख्य_set_events_per_period(&motu->करोमुख्य,
					frames_per_period, frames_per_buffer);
		अगर (err < 0) अणु
			fw_iso_resources_मुक्त(&motu->tx_resources);
			fw_iso_resources_मुक्त(&motu->rx_resources);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ensure_packet_क्रमmats(काष्ठा snd_motu *motu)
अणु
	__be32 reg;
	u32 data;
	पूर्णांक err;

	err = snd_motu_transaction_पढ़ो(motu, PACKET_FORMAT_OFFSET, &reg,
					माप(reg));
	अगर (err < 0)
		वापस err;
	data = be32_to_cpu(reg);

	data &= ~(TX_PACKET_EXCLUDE_DIFFERED_DATA_CHUNKS |
		  RX_PACKET_EXCLUDE_DIFFERED_DATA_CHUNKS|
		  TX_PACKET_TRANSMISSION_SPEED_MASK);
	अगर (motu->spec->tx_fixed_pcm_chunks[0] == motu->tx_packet_क्रमmats.pcm_chunks[0])
		data |= TX_PACKET_EXCLUDE_DIFFERED_DATA_CHUNKS;
	अगर (motu->spec->rx_fixed_pcm_chunks[0] == motu->rx_packet_क्रमmats.pcm_chunks[0])
		data |= RX_PACKET_EXCLUDE_DIFFERED_DATA_CHUNKS;
	data |= fw_parent_device(motu->unit)->max_speed;

	reg = cpu_to_be32(data);
	वापस snd_motu_transaction_ग_लिखो(motu, PACKET_FORMAT_OFFSET, &reg,
					  माप(reg));
पूर्ण

पूर्णांक snd_motu_stream_start_duplex(काष्ठा snd_motu *motu)
अणु
	अचिन्हित पूर्णांक generation = motu->rx_resources.generation;
	पूर्णांक err = 0;

	अगर (motu->substreams_counter == 0)
		वापस 0;

	अगर (amdtp_streaming_error(&motu->rx_stream) ||
	    amdtp_streaming_error(&motu->tx_stream)) अणु
		amdtp_करोमुख्य_stop(&motu->करोमुख्य);
		finish_session(motu);
	पूर्ण

	अगर (generation != fw_parent_device(motu->unit)->card->generation) अणु
		err = fw_iso_resources_update(&motu->rx_resources);
		अगर (err < 0)
			वापस err;

		err = fw_iso_resources_update(&motu->tx_resources);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (!amdtp_stream_running(&motu->rx_stream)) अणु
		पूर्णांक spd = fw_parent_device(motu->unit)->max_speed;

		err = ensure_packet_क्रमmats(motu);
		अगर (err < 0)
			वापस err;

		err = begin_session(motu);
		अगर (err < 0) अणु
			dev_err(&motu->unit->device,
				"fail to start isochronous comm: %d\n", err);
			जाओ stop_streams;
		पूर्ण

		err = amdtp_करोमुख्य_add_stream(&motu->करोमुख्य, &motu->tx_stream,
					      motu->tx_resources.channel, spd);
		अगर (err < 0)
			जाओ stop_streams;

		err = amdtp_करोमुख्य_add_stream(&motu->करोमुख्य, &motu->rx_stream,
					      motu->rx_resources.channel, spd);
		अगर (err < 0)
			जाओ stop_streams;

		err = amdtp_करोमुख्य_start(&motu->करोमुख्य, 0);
		अगर (err < 0)
			जाओ stop_streams;

		अगर (!amdtp_stream_रुको_callback(&motu->tx_stream,
						CALLBACK_TIMEOUT) ||
		    !amdtp_stream_रुको_callback(&motu->rx_stream,
						CALLBACK_TIMEOUT)) अणु
			err = -ETIMEDOUT;
			जाओ stop_streams;
		पूर्ण

		err = snd_motu_protocol_चयन_fetching_mode(motu, true);
		अगर (err < 0) अणु
			dev_err(&motu->unit->device,
				"fail to enable frame fetching: %d\n", err);
			जाओ stop_streams;
		पूर्ण
	पूर्ण

	वापस 0;

stop_streams:
	amdtp_करोमुख्य_stop(&motu->करोमुख्य);
	finish_session(motu);
	वापस err;
पूर्ण

व्योम snd_motu_stream_stop_duplex(काष्ठा snd_motu *motu)
अणु
	अगर (motu->substreams_counter == 0) अणु
		amdtp_करोमुख्य_stop(&motu->करोमुख्य);
		finish_session(motu);

		fw_iso_resources_मुक्त(&motu->tx_resources);
		fw_iso_resources_मुक्त(&motu->rx_resources);
	पूर्ण
पूर्ण

अटल पूर्णांक init_stream(काष्ठा snd_motu *motu, काष्ठा amdtp_stream *s)
अणु
	काष्ठा fw_iso_resources *resources;
	क्रमागत amdtp_stream_direction dir;
	पूर्णांक err;

	अगर (s == &motu->tx_stream) अणु
		resources = &motu->tx_resources;
		dir = AMDTP_IN_STREAM;
	पूर्ण अन्यथा अणु
		resources = &motu->rx_resources;
		dir = AMDTP_OUT_STREAM;
	पूर्ण

	err = fw_iso_resources_init(resources, motu->unit);
	अगर (err < 0)
		वापस err;

	err = amdtp_motu_init(s, motu->unit, dir, motu->spec);
	अगर (err < 0)
		fw_iso_resources_destroy(resources);

	वापस err;
पूर्ण

अटल व्योम destroy_stream(काष्ठा snd_motu *motu, काष्ठा amdtp_stream *s)
अणु
	amdtp_stream_destroy(s);

	अगर (s == &motu->tx_stream)
		fw_iso_resources_destroy(&motu->tx_resources);
	अन्यथा
		fw_iso_resources_destroy(&motu->rx_resources);
पूर्ण

पूर्णांक snd_motu_stream_init_duplex(काष्ठा snd_motu *motu)
अणु
	पूर्णांक err;

	err = init_stream(motu, &motu->tx_stream);
	अगर (err < 0)
		वापस err;

	err = init_stream(motu, &motu->rx_stream);
	अगर (err < 0) अणु
		destroy_stream(motu, &motu->tx_stream);
		वापस err;
	पूर्ण

	err = amdtp_करोमुख्य_init(&motu->करोमुख्य);
	अगर (err < 0) अणु
		destroy_stream(motu, &motu->tx_stream);
		destroy_stream(motu, &motu->rx_stream);
	पूर्ण

	वापस err;
पूर्ण

// This function should be called beक्रमe starting streams or after stopping
// streams.
व्योम snd_motu_stream_destroy_duplex(काष्ठा snd_motu *motu)
अणु
	amdtp_करोमुख्य_destroy(&motu->करोमुख्य);

	destroy_stream(motu, &motu->rx_stream);
	destroy_stream(motu, &motu->tx_stream);

	motu->substreams_counter = 0;
पूर्ण

अटल व्योम motu_lock_changed(काष्ठा snd_motu *motu)
अणु
	motu->dev_lock_changed = true;
	wake_up(&motu->hwdep_रुको);
पूर्ण

पूर्णांक snd_motu_stream_lock_try(काष्ठा snd_motu *motu)
अणु
	पूर्णांक err;

	spin_lock_irq(&motu->lock);

	अगर (motu->dev_lock_count < 0) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (motu->dev_lock_count++ == 0)
		motu_lock_changed(motu);
	err = 0;
out:
	spin_unlock_irq(&motu->lock);
	वापस err;
पूर्ण

व्योम snd_motu_stream_lock_release(काष्ठा snd_motu *motu)
अणु
	spin_lock_irq(&motu->lock);

	अगर (WARN_ON(motu->dev_lock_count <= 0))
		जाओ out;

	अगर (--motu->dev_lock_count == 0)
		motu_lock_changed(motu);
out:
	spin_unlock_irq(&motu->lock);
पूर्ण
