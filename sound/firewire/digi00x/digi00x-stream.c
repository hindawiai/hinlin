<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * digi00x-stream.c - a part of driver क्रम Digidesign Digi 002/003 family
 *
 * Copyright (c) 2014-2015 Takashi Sakamoto
 */

#समावेश "digi00x.h"

#घोषणा CALLBACK_TIMEOUT 500

स्थिर अचिन्हित पूर्णांक snd_dg00x_stream_rates[SND_DG00X_RATE_COUNT] = अणु
	[SND_DG00X_RATE_44100] = 44100,
	[SND_DG00X_RATE_48000] = 48000,
	[SND_DG00X_RATE_88200] = 88200,
	[SND_DG00X_RATE_96000] = 96000,
पूर्ण;

/* Multi Bit Linear Audio data channels क्रम each sampling transfer frequency. */
स्थिर अचिन्हित पूर्णांक
snd_dg00x_stream_pcm_channels[SND_DG00X_RATE_COUNT] = अणु
	/* Analog/ADAT/SPDIF */
	[SND_DG00X_RATE_44100] = (8 + 8 + 2),
	[SND_DG00X_RATE_48000] = (8 + 8 + 2),
	/* Analog/SPDIF */
	[SND_DG00X_RATE_88200] = (8 + 2),
	[SND_DG00X_RATE_96000] = (8 + 2),
पूर्ण;

पूर्णांक snd_dg00x_stream_get_local_rate(काष्ठा snd_dg00x *dg00x, अचिन्हित पूर्णांक *rate)
अणु
	u32 data;
	__be32 reg;
	पूर्णांक err;

	err = snd_fw_transaction(dg00x->unit, TCODE_READ_QUADLET_REQUEST,
				 DG00X_ADDR_BASE + DG00X_OFFSET_LOCAL_RATE,
				 &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	data = be32_to_cpu(reg) & 0x0f;
	अगर (data < ARRAY_SIZE(snd_dg00x_stream_rates))
		*rate = snd_dg00x_stream_rates[data];
	अन्यथा
		err = -EIO;

	वापस err;
पूर्ण

पूर्णांक snd_dg00x_stream_set_local_rate(काष्ठा snd_dg00x *dg00x, अचिन्हित पूर्णांक rate)
अणु
	__be32 reg;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(snd_dg00x_stream_rates); i++) अणु
		अगर (rate == snd_dg00x_stream_rates[i])
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(snd_dg00x_stream_rates))
		वापस -EINVAL;

	reg = cpu_to_be32(i);
	वापस snd_fw_transaction(dg00x->unit, TCODE_WRITE_QUADLET_REQUEST,
				  DG00X_ADDR_BASE + DG00X_OFFSET_LOCAL_RATE,
				  &reg, माप(reg), 0);
पूर्ण

पूर्णांक snd_dg00x_stream_get_घड़ी(काष्ठा snd_dg00x *dg00x,
			       क्रमागत snd_dg00x_घड़ी *घड़ी)
अणु
	__be32 reg;
	पूर्णांक err;

	err = snd_fw_transaction(dg00x->unit, TCODE_READ_QUADLET_REQUEST,
				 DG00X_ADDR_BASE + DG00X_OFFSET_CLOCK_SOURCE,
				 &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	*घड़ी = be32_to_cpu(reg) & 0x0f;
	अगर (*घड़ी >= SND_DG00X_CLOCK_COUNT)
		err = -EIO;

	वापस err;
पूर्ण

पूर्णांक snd_dg00x_stream_check_बाह्यal_घड़ी(काष्ठा snd_dg00x *dg00x, bool *detect)
अणु
	__be32 reg;
	पूर्णांक err;

	err = snd_fw_transaction(dg00x->unit, TCODE_READ_QUADLET_REQUEST,
				 DG00X_ADDR_BASE + DG00X_OFFSET_DETECT_EXTERNAL,
				 &reg, माप(reg), 0);
	अगर (err >= 0)
		*detect = be32_to_cpu(reg) > 0;

	वापस err;
पूर्ण

पूर्णांक snd_dg00x_stream_get_बाह्यal_rate(काष्ठा snd_dg00x *dg00x,
				       अचिन्हित पूर्णांक *rate)
अणु
	u32 data;
	__be32 reg;
	पूर्णांक err;

	err = snd_fw_transaction(dg00x->unit, TCODE_READ_QUADLET_REQUEST,
				 DG00X_ADDR_BASE + DG00X_OFFSET_EXTERNAL_RATE,
				 &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	data = be32_to_cpu(reg) & 0x0f;
	अगर (data < ARRAY_SIZE(snd_dg00x_stream_rates))
		*rate = snd_dg00x_stream_rates[data];
	/* This means desync. */
	अन्यथा
		err = -EBUSY;

	वापस err;
पूर्ण

अटल व्योम finish_session(काष्ठा snd_dg00x *dg00x)
अणु
	__be32 data;

	data = cpu_to_be32(0x00000003);
	snd_fw_transaction(dg00x->unit, TCODE_WRITE_QUADLET_REQUEST,
			   DG00X_ADDR_BASE + DG00X_OFFSET_STREAMING_SET,
			   &data, माप(data), 0);

	// Unरेजिस्टर isochronous channels क्रम both direction.
	data = 0;
	snd_fw_transaction(dg00x->unit, TCODE_WRITE_QUADLET_REQUEST,
			   DG00X_ADDR_BASE + DG00X_OFFSET_ISOC_CHANNELS,
			   &data, माप(data), 0);

	// Just after finishing the session, the device may lost transmitting
	// functionality क्रम a लघु समय.
	msleep(50);
पूर्ण

अटल पूर्णांक begin_session(काष्ठा snd_dg00x *dg00x)
अणु
	__be32 data;
	u32 curr;
	पूर्णांक err;

	// Register isochronous channels क्रम both direction.
	data = cpu_to_be32((dg00x->tx_resources.channel << 16) |
			   dg00x->rx_resources.channel);
	err = snd_fw_transaction(dg00x->unit, TCODE_WRITE_QUADLET_REQUEST,
				 DG00X_ADDR_BASE + DG00X_OFFSET_ISOC_CHANNELS,
				 &data, माप(data), 0);
	अगर (err < 0)
		वापस err;

	err = snd_fw_transaction(dg00x->unit, TCODE_READ_QUADLET_REQUEST,
				 DG00X_ADDR_BASE + DG00X_OFFSET_STREAMING_STATE,
				 &data, माप(data), 0);
	अगर (err < 0)
		वापस err;
	curr = be32_to_cpu(data);

	अगर (curr == 0)
		curr = 2;

	curr--;
	जबतक (curr > 0) अणु
		data = cpu_to_be32(curr);
		err = snd_fw_transaction(dg00x->unit,
					 TCODE_WRITE_QUADLET_REQUEST,
					 DG00X_ADDR_BASE +
					 DG00X_OFFSET_STREAMING_SET,
					 &data, माप(data), 0);
		अगर (err < 0)
			अवरोध;

		msleep(20);
		curr--;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक keep_resources(काष्ठा snd_dg00x *dg00x, काष्ठा amdtp_stream *stream,
			  अचिन्हित पूर्णांक rate)
अणु
	काष्ठा fw_iso_resources *resources;
	पूर्णांक i;
	पूर्णांक err;

	// Check sampling rate.
	क्रम (i = 0; i < SND_DG00X_RATE_COUNT; i++) अणु
		अगर (snd_dg00x_stream_rates[i] == rate)
			अवरोध;
	पूर्ण
	अगर (i == SND_DG00X_RATE_COUNT)
		वापस -EINVAL;

	अगर (stream == &dg00x->tx_stream)
		resources = &dg00x->tx_resources;
	अन्यथा
		resources = &dg00x->rx_resources;

	err = amdtp_करोt_set_parameters(stream, rate,
				       snd_dg00x_stream_pcm_channels[i]);
	अगर (err < 0)
		वापस err;

	वापस fw_iso_resources_allocate(resources,
				amdtp_stream_get_max_payload(stream),
				fw_parent_device(dg00x->unit)->max_speed);
पूर्ण

अटल पूर्णांक init_stream(काष्ठा snd_dg00x *dg00x, काष्ठा amdtp_stream *s)
अणु
	काष्ठा fw_iso_resources *resources;
	क्रमागत amdtp_stream_direction dir;
	पूर्णांक err;

	अगर (s == &dg00x->tx_stream) अणु
		resources = &dg00x->tx_resources;
		dir = AMDTP_IN_STREAM;
	पूर्ण अन्यथा अणु
		resources = &dg00x->rx_resources;
		dir = AMDTP_OUT_STREAM;
	पूर्ण

	err = fw_iso_resources_init(resources, dg00x->unit);
	अगर (err < 0)
		वापस err;

	err = amdtp_करोt_init(s, dg00x->unit, dir);
	अगर (err < 0)
		fw_iso_resources_destroy(resources);

	वापस err;
पूर्ण

अटल व्योम destroy_stream(काष्ठा snd_dg00x *dg00x, काष्ठा amdtp_stream *s)
अणु
	amdtp_stream_destroy(s);

	अगर (s == &dg00x->tx_stream)
		fw_iso_resources_destroy(&dg00x->tx_resources);
	अन्यथा
		fw_iso_resources_destroy(&dg00x->rx_resources);
पूर्ण

पूर्णांक snd_dg00x_stream_init_duplex(काष्ठा snd_dg00x *dg00x)
अणु
	पूर्णांक err;

	err = init_stream(dg00x, &dg00x->rx_stream);
	अगर (err < 0)
		वापस err;

	err = init_stream(dg00x, &dg00x->tx_stream);
	अगर (err < 0)
		destroy_stream(dg00x, &dg00x->rx_stream);

	err = amdtp_करोमुख्य_init(&dg00x->करोमुख्य);
	अगर (err < 0) अणु
		destroy_stream(dg00x, &dg00x->rx_stream);
		destroy_stream(dg00x, &dg00x->tx_stream);
	पूर्ण

	वापस err;
पूर्ण

/*
 * This function should be called beक्रमe starting streams or after stopping
 * streams.
 */
व्योम snd_dg00x_stream_destroy_duplex(काष्ठा snd_dg00x *dg00x)
अणु
	amdtp_करोमुख्य_destroy(&dg00x->करोमुख्य);

	destroy_stream(dg00x, &dg00x->rx_stream);
	destroy_stream(dg00x, &dg00x->tx_stream);
पूर्ण

पूर्णांक snd_dg00x_stream_reserve_duplex(काष्ठा snd_dg00x *dg00x, अचिन्हित पूर्णांक rate,
				    अचिन्हित पूर्णांक frames_per_period,
				    अचिन्हित पूर्णांक frames_per_buffer)
अणु
	अचिन्हित पूर्णांक curr_rate;
	पूर्णांक err;

	err = snd_dg00x_stream_get_local_rate(dg00x, &curr_rate);
	अगर (err < 0)
		वापस err;
	अगर (rate == 0)
		rate = curr_rate;

	अगर (dg00x->substreams_counter == 0 || curr_rate != rate) अणु
		amdtp_करोमुख्य_stop(&dg00x->करोमुख्य);

		finish_session(dg00x);

		fw_iso_resources_मुक्त(&dg00x->tx_resources);
		fw_iso_resources_मुक्त(&dg00x->rx_resources);

		err = snd_dg00x_stream_set_local_rate(dg00x, rate);
		अगर (err < 0)
			वापस err;

		err = keep_resources(dg00x, &dg00x->rx_stream, rate);
		अगर (err < 0)
			वापस err;

		err = keep_resources(dg00x, &dg00x->tx_stream, rate);
		अगर (err < 0) अणु
			fw_iso_resources_मुक्त(&dg00x->rx_resources);
			वापस err;
		पूर्ण

		err = amdtp_करोमुख्य_set_events_per_period(&dg00x->करोमुख्य,
					frames_per_period, frames_per_buffer);
		अगर (err < 0) अणु
			fw_iso_resources_मुक्त(&dg00x->rx_resources);
			fw_iso_resources_मुक्त(&dg00x->tx_resources);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_dg00x_stream_start_duplex(काष्ठा snd_dg00x *dg00x)
अणु
	अचिन्हित पूर्णांक generation = dg00x->rx_resources.generation;
	पूर्णांक err = 0;

	अगर (dg00x->substreams_counter == 0)
		वापस 0;

	अगर (amdtp_streaming_error(&dg00x->tx_stream) ||
	    amdtp_streaming_error(&dg00x->rx_stream)) अणु
		amdtp_करोमुख्य_stop(&dg00x->करोमुख्य);
		finish_session(dg00x);
	पूर्ण

	अगर (generation != fw_parent_device(dg00x->unit)->card->generation) अणु
		err = fw_iso_resources_update(&dg00x->tx_resources);
		अगर (err < 0)
			जाओ error;

		err = fw_iso_resources_update(&dg00x->rx_resources);
		अगर (err < 0)
			जाओ error;
	पूर्ण

	/*
	 * No packets are transmitted without receiving packets, reagardless of
	 * which source of घड़ी is used.
	 */
	अगर (!amdtp_stream_running(&dg00x->rx_stream)) अणु
		पूर्णांक spd = fw_parent_device(dg00x->unit)->max_speed;

		err = begin_session(dg00x);
		अगर (err < 0)
			जाओ error;

		err = amdtp_करोमुख्य_add_stream(&dg00x->करोमुख्य, &dg00x->rx_stream,
					      dg00x->rx_resources.channel, spd);
		अगर (err < 0)
			जाओ error;

		err = amdtp_करोमुख्य_add_stream(&dg00x->करोमुख्य, &dg00x->tx_stream,
					      dg00x->tx_resources.channel, spd);
		अगर (err < 0)
			जाओ error;

		err = amdtp_करोमुख्य_start(&dg00x->करोमुख्य, 0);
		अगर (err < 0)
			जाओ error;

		अगर (!amdtp_stream_रुको_callback(&dg00x->rx_stream,
						CALLBACK_TIMEOUT) ||
		    !amdtp_stream_रुको_callback(&dg00x->tx_stream,
						CALLBACK_TIMEOUT)) अणु
			err = -ETIMEDOUT;
			जाओ error;
		पूर्ण
	पूर्ण

	वापस 0;
error:
	amdtp_करोमुख्य_stop(&dg00x->करोमुख्य);
	finish_session(dg00x);

	वापस err;
पूर्ण

व्योम snd_dg00x_stream_stop_duplex(काष्ठा snd_dg00x *dg00x)
अणु
	अगर (dg00x->substreams_counter == 0) अणु
		amdtp_करोमुख्य_stop(&dg00x->करोमुख्य);
		finish_session(dg00x);

		fw_iso_resources_मुक्त(&dg00x->tx_resources);
		fw_iso_resources_मुक्त(&dg00x->rx_resources);
	पूर्ण
पूर्ण

व्योम snd_dg00x_stream_update_duplex(काष्ठा snd_dg00x *dg00x)
अणु
	fw_iso_resources_update(&dg00x->tx_resources);
	fw_iso_resources_update(&dg00x->rx_resources);

	amdtp_stream_update(&dg00x->tx_stream);
	amdtp_stream_update(&dg00x->rx_stream);
पूर्ण

व्योम snd_dg00x_stream_lock_changed(काष्ठा snd_dg00x *dg00x)
अणु
	dg00x->dev_lock_changed = true;
	wake_up(&dg00x->hwdep_रुको);
पूर्ण

पूर्णांक snd_dg00x_stream_lock_try(काष्ठा snd_dg00x *dg00x)
अणु
	पूर्णांक err;

	spin_lock_irq(&dg00x->lock);

	/* user land lock this */
	अगर (dg00x->dev_lock_count < 0) अणु
		err = -EBUSY;
		जाओ end;
	पूर्ण

	/* this is the first समय */
	अगर (dg00x->dev_lock_count++ == 0)
		snd_dg00x_stream_lock_changed(dg00x);
	err = 0;
end:
	spin_unlock_irq(&dg00x->lock);
	वापस err;
पूर्ण

व्योम snd_dg00x_stream_lock_release(काष्ठा snd_dg00x *dg00x)
अणु
	spin_lock_irq(&dg00x->lock);

	अगर (WARN_ON(dg00x->dev_lock_count <= 0))
		जाओ end;
	अगर (--dg00x->dev_lock_count == 0)
		snd_dg00x_stream_lock_changed(dg00x);
end:
	spin_unlock_irq(&dg00x->lock);
पूर्ण
