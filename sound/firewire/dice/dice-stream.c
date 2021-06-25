<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * dice_stream.c - a part of driver क्रम DICE based devices
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 * Copyright (c) 2014 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#समावेश "dice.h"

#घोषणा	CALLBACK_TIMEOUT	200
#घोषणा NOTIFICATION_TIMEOUT_MS	(2 * MSEC_PER_SEC)

काष्ठा reg_params अणु
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक size;
पूर्ण;

स्थिर अचिन्हित पूर्णांक snd_dice_rates[SND_DICE_RATES_COUNT] = अणु
	/* mode 0 */
	[0] =  32000,
	[1] =  44100,
	[2] =  48000,
	/* mode 1 */
	[3] =  88200,
	[4] =  96000,
	/* mode 2 */
	[5] = 176400,
	[6] = 192000,
पूर्ण;

पूर्णांक snd_dice_stream_get_rate_mode(काष्ठा snd_dice *dice, अचिन्हित पूर्णांक rate,
				  क्रमागत snd_dice_rate_mode *mode)
अणु
	/* Corresponding to each entry in snd_dice_rates. */
	अटल स्थिर क्रमागत snd_dice_rate_mode modes[] = अणु
		[0] = SND_DICE_RATE_MODE_LOW,
		[1] = SND_DICE_RATE_MODE_LOW,
		[2] = SND_DICE_RATE_MODE_LOW,
		[3] = SND_DICE_RATE_MODE_MIDDLE,
		[4] = SND_DICE_RATE_MODE_MIDDLE,
		[5] = SND_DICE_RATE_MODE_HIGH,
		[6] = SND_DICE_RATE_MODE_HIGH,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(snd_dice_rates); i++) अणु
		अगर (!(dice->घड़ी_caps & BIT(i)))
			जारी;
		अगर (snd_dice_rates[i] != rate)
			जारी;

		*mode = modes[i];
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * This operation has an effect to synchronize GLOBAL_STATUS/GLOBAL_SAMPLE_RATE
 * to GLOBAL_STATUS. Especially, just after घातering on, these are dअगरferent.
 */
अटल पूर्णांक ensure_phase_lock(काष्ठा snd_dice *dice, अचिन्हित पूर्णांक rate)
अणु
	__be32 reg, nominal;
	u32 data;
	पूर्णांक i;
	पूर्णांक err;

	err = snd_dice_transaction_पढ़ो_global(dice, GLOBAL_CLOCK_SELECT,
					       &reg, माप(reg));
	अगर (err < 0)
		वापस err;

	data = be32_to_cpu(reg);

	data &= ~CLOCK_RATE_MASK;
	क्रम (i = 0; i < ARRAY_SIZE(snd_dice_rates); ++i) अणु
		अगर (snd_dice_rates[i] == rate)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(snd_dice_rates))
		वापस -EINVAL;
	data |= i << CLOCK_RATE_SHIFT;

	अगर (completion_करोne(&dice->घड़ी_accepted))
		reinit_completion(&dice->घड़ी_accepted);

	reg = cpu_to_be32(data);
	err = snd_dice_transaction_ग_लिखो_global(dice, GLOBAL_CLOCK_SELECT,
						&reg, माप(reg));
	अगर (err < 0)
		वापस err;

	अगर (रुको_क्रम_completion_समयout(&dice->घड़ी_accepted,
			msecs_to_jअगरfies(NOTIFICATION_TIMEOUT_MS)) == 0) अणु
		/*
		 * Old versions of Dice firmware transfer no notअगरication when
		 * the same घड़ी status as current one is set. In this हाल,
		 * just check current घड़ी status.
		 */
		err = snd_dice_transaction_पढ़ो_global(dice, GLOBAL_STATUS,
						&nominal, माप(nominal));
		अगर (err < 0)
			वापस err;
		अगर (!(be32_to_cpu(nominal) & STATUS_SOURCE_LOCKED))
			वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_रेजिस्टर_params(काष्ठा snd_dice *dice,
			       काष्ठा reg_params *tx_params,
			       काष्ठा reg_params *rx_params)
अणु
	__be32 reg[2];
	पूर्णांक err;

	err = snd_dice_transaction_पढ़ो_tx(dice, TX_NUMBER, reg, माप(reg));
	अगर (err < 0)
		वापस err;
	tx_params->count =
			min_t(अचिन्हित पूर्णांक, be32_to_cpu(reg[0]), MAX_STREAMS);
	tx_params->size = be32_to_cpu(reg[1]) * 4;

	err = snd_dice_transaction_पढ़ो_rx(dice, RX_NUMBER, reg, माप(reg));
	अगर (err < 0)
		वापस err;
	rx_params->count =
			min_t(अचिन्हित पूर्णांक, be32_to_cpu(reg[0]), MAX_STREAMS);
	rx_params->size = be32_to_cpu(reg[1]) * 4;

	वापस 0;
पूर्ण

अटल व्योम release_resources(काष्ठा snd_dice *dice)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_STREAMS; ++i) अणु
		fw_iso_resources_मुक्त(&dice->tx_resources[i]);
		fw_iso_resources_मुक्त(&dice->rx_resources[i]);
	पूर्ण
पूर्ण

अटल व्योम stop_streams(काष्ठा snd_dice *dice, क्रमागत amdtp_stream_direction dir,
			 काष्ठा reg_params *params)
अणु
	__be32 reg;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < params->count; i++) अणु
		reg = cpu_to_be32((u32)-1);
		अगर (dir == AMDTP_IN_STREAM) अणु
			snd_dice_transaction_ग_लिखो_tx(dice,
					params->size * i + TX_ISOCHRONOUS,
					&reg, माप(reg));
		पूर्ण अन्यथा अणु
			snd_dice_transaction_ग_लिखो_rx(dice,
					params->size * i + RX_ISOCHRONOUS,
					&reg, माप(reg));
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक keep_resources(काष्ठा snd_dice *dice, काष्ठा amdtp_stream *stream,
			  काष्ठा fw_iso_resources *resources, अचिन्हित पूर्णांक rate,
			  अचिन्हित पूर्णांक pcm_chs, अचिन्हित पूर्णांक midi_ports)
अणु
	bool द्विगुन_pcm_frames;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	// At 176.4/192.0 kHz, Dice has a quirk to transfer two PCM frames in
	// one data block of AMDTP packet. Thus sampling transfer frequency is
	// a half of PCM sampling frequency, i.e. PCM frames at 192.0 kHz are
	// transferred on AMDTP packets at 96 kHz. Two successive samples of a
	// channel are stored consecutively in the packet. This quirk is called
	// as 'Dual Wire'.
	// For this quirk, blocking mode is required and PCM buffer size should
	// be aligned to SYT_INTERVAL.
	द्विगुन_pcm_frames = (rate > 96000 && !dice->disable_द्विगुन_pcm_frames);
	अगर (द्विगुन_pcm_frames) अणु
		rate /= 2;
		pcm_chs *= 2;
	पूर्ण

	err = amdtp_am824_set_parameters(stream, rate, pcm_chs, midi_ports,
					 द्विगुन_pcm_frames);
	अगर (err < 0)
		वापस err;

	अगर (द्विगुन_pcm_frames) अणु
		pcm_chs /= 2;

		क्रम (i = 0; i < pcm_chs; i++) अणु
			amdtp_am824_set_pcm_position(stream, i, i * 2);
			amdtp_am824_set_pcm_position(stream, i + pcm_chs,
						     i * 2 + 1);
		पूर्ण
	पूर्ण

	वापस fw_iso_resources_allocate(resources,
				amdtp_stream_get_max_payload(stream),
				fw_parent_device(dice->unit)->max_speed);
पूर्ण

अटल पूर्णांक keep_dual_resources(काष्ठा snd_dice *dice, अचिन्हित पूर्णांक rate,
			       क्रमागत amdtp_stream_direction dir,
			       काष्ठा reg_params *params)
अणु
	क्रमागत snd_dice_rate_mode mode;
	पूर्णांक i;
	पूर्णांक err;

	err = snd_dice_stream_get_rate_mode(dice, rate, &mode);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i < params->count; ++i) अणु
		__be32 reg[2];
		काष्ठा amdtp_stream *stream;
		काष्ठा fw_iso_resources *resources;
		अचिन्हित पूर्णांक pcm_cache;
		अचिन्हित पूर्णांक pcm_chs;
		अचिन्हित पूर्णांक midi_ports;

		अगर (dir == AMDTP_IN_STREAM) अणु
			stream = &dice->tx_stream[i];
			resources = &dice->tx_resources[i];

			pcm_cache = dice->tx_pcm_chs[i][mode];
			err = snd_dice_transaction_पढ़ो_tx(dice,
					params->size * i + TX_NUMBER_AUDIO,
					reg, माप(reg));
		पूर्ण अन्यथा अणु
			stream = &dice->rx_stream[i];
			resources = &dice->rx_resources[i];

			pcm_cache = dice->rx_pcm_chs[i][mode];
			err = snd_dice_transaction_पढ़ो_rx(dice,
					params->size * i + RX_NUMBER_AUDIO,
					reg, माप(reg));
		पूर्ण
		अगर (err < 0)
			वापस err;
		pcm_chs = be32_to_cpu(reg[0]);
		midi_ports = be32_to_cpu(reg[1]);

		// These are important क्रम developer of this driver.
		अगर (pcm_chs != pcm_cache) अणु
			dev_info(&dice->unit->device,
				 "cache mismatch: pcm: %u:%u, midi: %u\n",
				 pcm_chs, pcm_cache, midi_ports);
			वापस -EPROTO;
		पूर्ण

		err = keep_resources(dice, stream, resources, rate, pcm_chs,
				     midi_ports);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम finish_session(काष्ठा snd_dice *dice, काष्ठा reg_params *tx_params,
			   काष्ठा reg_params *rx_params)
अणु
	stop_streams(dice, AMDTP_IN_STREAM, tx_params);
	stop_streams(dice, AMDTP_OUT_STREAM, rx_params);

	snd_dice_transaction_clear_enable(dice);
पूर्ण

पूर्णांक snd_dice_stream_reserve_duplex(काष्ठा snd_dice *dice, अचिन्हित पूर्णांक rate,
				   अचिन्हित पूर्णांक events_per_period,
				   अचिन्हित पूर्णांक events_per_buffer)
अणु
	अचिन्हित पूर्णांक curr_rate;
	पूर्णांक err;

	// Check sampling transmission frequency.
	err = snd_dice_transaction_get_rate(dice, &curr_rate);
	अगर (err < 0)
		वापस err;
	अगर (rate == 0)
		rate = curr_rate;

	अगर (dice->substreams_counter == 0 || curr_rate != rate) अणु
		काष्ठा reg_params tx_params, rx_params;

		amdtp_करोमुख्य_stop(&dice->करोमुख्य);

		err = get_रेजिस्टर_params(dice, &tx_params, &rx_params);
		अगर (err < 0)
			वापस err;
		finish_session(dice, &tx_params, &rx_params);

		release_resources(dice);

		// Just after owning the unit (GLOBAL_OWNER), the unit can
		// वापस invalid stream क्रमmats. Selecting घड़ी parameters
		// have an effect क्रम the unit to refine it.
		err = ensure_phase_lock(dice, rate);
		अगर (err < 0)
			वापस err;

		// After changing sampling transfer frequency, the value of
		// रेजिस्टर can be changed.
		err = get_रेजिस्टर_params(dice, &tx_params, &rx_params);
		अगर (err < 0)
			वापस err;

		err = keep_dual_resources(dice, rate, AMDTP_IN_STREAM,
					  &tx_params);
		अगर (err < 0)
			जाओ error;

		err = keep_dual_resources(dice, rate, AMDTP_OUT_STREAM,
					  &rx_params);
		अगर (err < 0)
			जाओ error;

		err = amdtp_करोमुख्य_set_events_per_period(&dice->करोमुख्य,
					events_per_period, events_per_buffer);
		अगर (err < 0)
			जाओ error;
	पूर्ण

	वापस 0;
error:
	release_resources(dice);
	वापस err;
पूर्ण

अटल पूर्णांक start_streams(काष्ठा snd_dice *dice, क्रमागत amdtp_stream_direction dir,
			 अचिन्हित पूर्णांक rate, काष्ठा reg_params *params)
अणु
	अचिन्हित पूर्णांक max_speed = fw_parent_device(dice->unit)->max_speed;
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < params->count; i++) अणु
		काष्ठा amdtp_stream *stream;
		काष्ठा fw_iso_resources *resources;
		__be32 reg;

		अगर (dir == AMDTP_IN_STREAM) अणु
			stream = dice->tx_stream + i;
			resources = dice->tx_resources + i;
		पूर्ण अन्यथा अणु
			stream = dice->rx_stream + i;
			resources = dice->rx_resources + i;
		पूर्ण

		reg = cpu_to_be32(resources->channel);
		अगर (dir == AMDTP_IN_STREAM) अणु
			err = snd_dice_transaction_ग_लिखो_tx(dice,
					params->size * i + TX_ISOCHRONOUS,
					&reg, माप(reg));
		पूर्ण अन्यथा अणु
			err = snd_dice_transaction_ग_लिखो_rx(dice,
					params->size * i + RX_ISOCHRONOUS,
					&reg, माप(reg));
		पूर्ण
		अगर (err < 0)
			वापस err;

		अगर (dir == AMDTP_IN_STREAM) अणु
			reg = cpu_to_be32(max_speed);
			err = snd_dice_transaction_ग_लिखो_tx(dice,
					params->size * i + TX_SPEED,
					&reg, माप(reg));
			अगर (err < 0)
				वापस err;
		पूर्ण

		err = amdtp_करोमुख्य_add_stream(&dice->करोमुख्य, stream,
					      resources->channel, max_speed);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * MEMO: After this function, there're two states of streams:
 *  - None streams are running.
 *  - All streams are running.
 */
पूर्णांक snd_dice_stream_start_duplex(काष्ठा snd_dice *dice)
अणु
	अचिन्हित पूर्णांक generation = dice->rx_resources[0].generation;
	काष्ठा reg_params tx_params, rx_params;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक rate;
	क्रमागत snd_dice_rate_mode mode;
	पूर्णांक err;

	अगर (dice->substreams_counter == 0)
		वापस -EIO;

	err = get_रेजिस्टर_params(dice, &tx_params, &rx_params);
	अगर (err < 0)
		वापस err;

	// Check error of packet streaming.
	क्रम (i = 0; i < MAX_STREAMS; ++i) अणु
		अगर (amdtp_streaming_error(&dice->tx_stream[i]) ||
		    amdtp_streaming_error(&dice->rx_stream[i])) अणु
			amdtp_करोमुख्य_stop(&dice->करोमुख्य);
			finish_session(dice, &tx_params, &rx_params);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (generation != fw_parent_device(dice->unit)->card->generation) अणु
		क्रम (i = 0; i < MAX_STREAMS; ++i) अणु
			अगर (i < tx_params.count)
				fw_iso_resources_update(dice->tx_resources + i);
			अगर (i < rx_params.count)
				fw_iso_resources_update(dice->rx_resources + i);
		पूर्ण
	पूर्ण

	// Check required streams are running or not.
	err = snd_dice_transaction_get_rate(dice, &rate);
	अगर (err < 0)
		वापस err;
	err = snd_dice_stream_get_rate_mode(dice, rate, &mode);
	अगर (err < 0)
		वापस err;
	क्रम (i = 0; i < MAX_STREAMS; ++i) अणु
		अगर (dice->tx_pcm_chs[i][mode] > 0 &&
		    !amdtp_stream_running(&dice->tx_stream[i]))
			अवरोध;
		अगर (dice->rx_pcm_chs[i][mode] > 0 &&
		    !amdtp_stream_running(&dice->rx_stream[i]))
			अवरोध;
	पूर्ण
	अगर (i < MAX_STREAMS) अणु
		// Start both streams.
		err = start_streams(dice, AMDTP_IN_STREAM, rate, &tx_params);
		अगर (err < 0)
			जाओ error;

		err = start_streams(dice, AMDTP_OUT_STREAM, rate, &rx_params);
		अगर (err < 0)
			जाओ error;

		err = snd_dice_transaction_set_enable(dice);
		अगर (err < 0) अणु
			dev_err(&dice->unit->device,
				"fail to enable interface\n");
			जाओ error;
		पूर्ण

		err = amdtp_करोमुख्य_start(&dice->करोमुख्य, 0);
		अगर (err < 0)
			जाओ error;

		क्रम (i = 0; i < MAX_STREAMS; i++) अणु
			अगर ((i < tx_params.count &&
			    !amdtp_stream_रुको_callback(&dice->tx_stream[i],
							CALLBACK_TIMEOUT)) ||
			    (i < rx_params.count &&
			     !amdtp_stream_रुको_callback(&dice->rx_stream[i],
							 CALLBACK_TIMEOUT))) अणु
				err = -ETIMEDOUT;
				जाओ error;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
error:
	amdtp_करोमुख्य_stop(&dice->करोमुख्य);
	finish_session(dice, &tx_params, &rx_params);
	वापस err;
पूर्ण

/*
 * MEMO: After this function, there're two states of streams:
 *  - None streams are running.
 *  - All streams are running.
 */
व्योम snd_dice_stream_stop_duplex(काष्ठा snd_dice *dice)
अणु
	काष्ठा reg_params tx_params, rx_params;

	अगर (dice->substreams_counter == 0) अणु
		अगर (get_रेजिस्टर_params(dice, &tx_params, &rx_params) >= 0)
			finish_session(dice, &tx_params, &rx_params);

		amdtp_करोमुख्य_stop(&dice->करोमुख्य);
		release_resources(dice);
	पूर्ण
पूर्ण

अटल पूर्णांक init_stream(काष्ठा snd_dice *dice, क्रमागत amdtp_stream_direction dir,
		       अचिन्हित पूर्णांक index)
अणु
	काष्ठा amdtp_stream *stream;
	काष्ठा fw_iso_resources *resources;
	पूर्णांक err;

	अगर (dir == AMDTP_IN_STREAM) अणु
		stream = &dice->tx_stream[index];
		resources = &dice->tx_resources[index];
	पूर्ण अन्यथा अणु
		stream = &dice->rx_stream[index];
		resources = &dice->rx_resources[index];
	पूर्ण

	err = fw_iso_resources_init(resources, dice->unit);
	अगर (err < 0)
		जाओ end;
	resources->channels_mask = 0x00000000ffffffffuLL;

	err = amdtp_am824_init(stream, dice->unit, dir, CIP_BLOCKING);
	अगर (err < 0) अणु
		amdtp_stream_destroy(stream);
		fw_iso_resources_destroy(resources);
	पूर्ण
end:
	वापस err;
पूर्ण

/*
 * This function should be called beक्रमe starting streams or after stopping
 * streams.
 */
अटल व्योम destroy_stream(काष्ठा snd_dice *dice,
			   क्रमागत amdtp_stream_direction dir,
			   अचिन्हित पूर्णांक index)
अणु
	काष्ठा amdtp_stream *stream;
	काष्ठा fw_iso_resources *resources;

	अगर (dir == AMDTP_IN_STREAM) अणु
		stream = &dice->tx_stream[index];
		resources = &dice->tx_resources[index];
	पूर्ण अन्यथा अणु
		stream = &dice->rx_stream[index];
		resources = &dice->rx_resources[index];
	पूर्ण

	amdtp_stream_destroy(stream);
	fw_iso_resources_destroy(resources);
पूर्ण

पूर्णांक snd_dice_stream_init_duplex(काष्ठा snd_dice *dice)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < MAX_STREAMS; i++) अणु
		err = init_stream(dice, AMDTP_IN_STREAM, i);
		अगर (err < 0) अणु
			क्रम (; i >= 0; i--)
				destroy_stream(dice, AMDTP_IN_STREAM, i);
			जाओ end;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < MAX_STREAMS; i++) अणु
		err = init_stream(dice, AMDTP_OUT_STREAM, i);
		अगर (err < 0) अणु
			क्रम (; i >= 0; i--)
				destroy_stream(dice, AMDTP_OUT_STREAM, i);
			क्रम (i = 0; i < MAX_STREAMS; i++)
				destroy_stream(dice, AMDTP_IN_STREAM, i);
			जाओ end;
		पूर्ण
	पूर्ण

	err = amdtp_करोमुख्य_init(&dice->करोमुख्य);
	अगर (err < 0) अणु
		क्रम (i = 0; i < MAX_STREAMS; ++i) अणु
			destroy_stream(dice, AMDTP_OUT_STREAM, i);
			destroy_stream(dice, AMDTP_IN_STREAM, i);
		पूर्ण
	पूर्ण
end:
	वापस err;
पूर्ण

व्योम snd_dice_stream_destroy_duplex(काष्ठा snd_dice *dice)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < MAX_STREAMS; i++) अणु
		destroy_stream(dice, AMDTP_IN_STREAM, i);
		destroy_stream(dice, AMDTP_OUT_STREAM, i);
	पूर्ण

	amdtp_करोमुख्य_destroy(&dice->करोमुख्य);
पूर्ण

व्योम snd_dice_stream_update_duplex(काष्ठा snd_dice *dice)
अणु
	काष्ठा reg_params tx_params, rx_params;

	/*
	 * On a bus reset, the DICE firmware disables streaming and then goes
	 * off contemplating its own navel क्रम hundreds of milliseconds beक्रमe
	 * it can react to any of our attempts to reenable streaming.  This
	 * means that we lose synchronization anyway, so we क्रमce our streams
	 * to stop so that the application can restart them in an orderly
	 * manner.
	 */
	dice->global_enabled = false;

	अगर (get_रेजिस्टर_params(dice, &tx_params, &rx_params) == 0) अणु
		amdtp_करोमुख्य_stop(&dice->करोमुख्य);

		stop_streams(dice, AMDTP_IN_STREAM, &tx_params);
		stop_streams(dice, AMDTP_OUT_STREAM, &rx_params);
	पूर्ण
पूर्ण

पूर्णांक snd_dice_stream_detect_current_क्रमmats(काष्ठा snd_dice *dice)
अणु
	अचिन्हित पूर्णांक rate;
	क्रमागत snd_dice_rate_mode mode;
	__be32 reg[2];
	काष्ठा reg_params tx_params, rx_params;
	पूर्णांक i;
	पूर्णांक err;

	/* If extended protocol is available, detect detail spec. */
	err = snd_dice_detect_extension_क्रमmats(dice);
	अगर (err >= 0)
		वापस err;

	/*
	 * Available stream क्रमmat is restricted at current mode of sampling
	 * घड़ी.
	 */
	err = snd_dice_transaction_get_rate(dice, &rate);
	अगर (err < 0)
		वापस err;

	err = snd_dice_stream_get_rate_mode(dice, rate, &mode);
	अगर (err < 0)
		वापस err;

	/*
	 * Just after owning the unit (GLOBAL_OWNER), the unit can वापस
	 * invalid stream क्रमmats. Selecting घड़ी parameters have an effect
	 * क्रम the unit to refine it.
	 */
	err = ensure_phase_lock(dice, rate);
	अगर (err < 0)
		वापस err;

	err = get_रेजिस्टर_params(dice, &tx_params, &rx_params);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i < tx_params.count; ++i) अणु
		err = snd_dice_transaction_पढ़ो_tx(dice,
				tx_params.size * i + TX_NUMBER_AUDIO,
				reg, माप(reg));
		अगर (err < 0)
			वापस err;
		dice->tx_pcm_chs[i][mode] = be32_to_cpu(reg[0]);
		dice->tx_midi_ports[i] = max_t(अचिन्हित पूर्णांक,
				be32_to_cpu(reg[1]), dice->tx_midi_ports[i]);
	पूर्ण
	क्रम (i = 0; i < rx_params.count; ++i) अणु
		err = snd_dice_transaction_पढ़ो_rx(dice,
				rx_params.size * i + RX_NUMBER_AUDIO,
				reg, माप(reg));
		अगर (err < 0)
			वापस err;
		dice->rx_pcm_chs[i][mode] = be32_to_cpu(reg[0]);
		dice->rx_midi_ports[i] = max_t(अचिन्हित पूर्णांक,
				be32_to_cpu(reg[1]), dice->rx_midi_ports[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dice_lock_changed(काष्ठा snd_dice *dice)
अणु
	dice->dev_lock_changed = true;
	wake_up(&dice->hwdep_रुको);
पूर्ण

पूर्णांक snd_dice_stream_lock_try(काष्ठा snd_dice *dice)
अणु
	पूर्णांक err;

	spin_lock_irq(&dice->lock);

	अगर (dice->dev_lock_count < 0) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (dice->dev_lock_count++ == 0)
		dice_lock_changed(dice);
	err = 0;
out:
	spin_unlock_irq(&dice->lock);
	वापस err;
पूर्ण

व्योम snd_dice_stream_lock_release(काष्ठा snd_dice *dice)
अणु
	spin_lock_irq(&dice->lock);

	अगर (WARN_ON(dice->dev_lock_count <= 0))
		जाओ out;

	अगर (--dice->dev_lock_count == 0)
		dice_lock_changed(dice);
out:
	spin_unlock_irq(&dice->lock);
पूर्ण
