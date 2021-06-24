<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * oxfw-scs1x.c - a part of driver क्रम OXFW970/971 based devices
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 * Copyright (c) 2015 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#समावेश "oxfw.h"

#घोषणा HSS1394_ADDRESS			0xc007dedadadaULL
#घोषणा HSS1394_MAX_PACKET_SIZE		64
#घोषणा HSS1394_TAG_USER_DATA		0x00
#घोषणा HSS1394_TAG_CHANGE_ADDRESS	0xf1

काष्ठा fw_scs1x अणु
	काष्ठा fw_address_handler hss_handler;
	u8 input_escape_count;
	काष्ठा snd_rawmidi_substream *input;

	/* For MIDI playback. */
	काष्ठा snd_rawmidi_substream *output;
	bool output_idle;
	u8 output_status;
	u8 output_bytes;
	bool output_escaped;
	bool output_escape_high_nibble;
	काष्ठा work_काष्ठा work;
	रुको_queue_head_t idle_रुको;
	u8 buffer[HSS1394_MAX_PACKET_SIZE];
	bool transaction_running;
	काष्ठा fw_transaction transaction;
	अचिन्हित पूर्णांक transaction_bytes;
	bool error;
	काष्ठा fw_device *fw_dev;
पूर्ण;

अटल स्थिर u8 sysex_escape_prefix[] = अणु
	0xf0,			/* SysEx begin */
	0x00, 0x01, 0x60,	/* Stanton DJ */
	0x48, 0x53, 0x53,	/* "HSS" */
पूर्ण;

अटल व्योम midi_input_escaped_byte(काष्ठा snd_rawmidi_substream *stream,
				    u8 byte)
अणु
	u8 nibbles[2];

	nibbles[0] = byte >> 4;
	nibbles[1] = byte & 0x0f;
	snd_rawmidi_receive(stream, nibbles, 2);
पूर्ण

अटल व्योम midi_input_byte(काष्ठा fw_scs1x *scs,
			    काष्ठा snd_rawmidi_substream *stream, u8 byte)
अणु
	स्थिर u8 eox = 0xf7;

	अगर (scs->input_escape_count > 0) अणु
		midi_input_escaped_byte(stream, byte);
		scs->input_escape_count--;
		अगर (scs->input_escape_count == 0)
			snd_rawmidi_receive(stream, &eox, माप(eox));
	पूर्ण अन्यथा अगर (byte == 0xf9) अणु
		snd_rawmidi_receive(stream, sysex_escape_prefix,
				    ARRAY_SIZE(sysex_escape_prefix));
		midi_input_escaped_byte(stream, 0x00);
		midi_input_escaped_byte(stream, 0xf9);
		scs->input_escape_count = 3;
	पूर्ण अन्यथा अणु
		snd_rawmidi_receive(stream, &byte, 1);
	पूर्ण
पूर्ण

अटल व्योम midi_input_packet(काष्ठा fw_scs1x *scs,
			      काष्ठा snd_rawmidi_substream *stream,
			      स्थिर u8 *data, अचिन्हित पूर्णांक bytes)
अणु
	अचिन्हित पूर्णांक i;
	स्थिर u8 eox = 0xf7;

	अगर (data[0] == HSS1394_TAG_USER_DATA) अणु
		क्रम (i = 1; i < bytes; ++i)
			midi_input_byte(scs, stream, data[i]);
	पूर्ण अन्यथा अणु
		snd_rawmidi_receive(stream, sysex_escape_prefix,
				    ARRAY_SIZE(sysex_escape_prefix));
		क्रम (i = 0; i < bytes; ++i)
			midi_input_escaped_byte(stream, data[i]);
		snd_rawmidi_receive(stream, &eox, माप(eox));
	पूर्ण
पूर्ण

अटल व्योम handle_hss(काष्ठा fw_card *card, काष्ठा fw_request *request,
		       पूर्णांक tcode, पूर्णांक destination, पूर्णांक source, पूर्णांक generation,
		       अचिन्हित दीर्घ दीर्घ offset, व्योम *data, माप_प्रकार length,
		       व्योम *callback_data)
अणु
	काष्ठा fw_scs1x *scs = callback_data;
	काष्ठा snd_rawmidi_substream *stream;
	पूर्णांक rcode;

	अगर (offset != scs->hss_handler.offset) अणु
		rcode = RCODE_ADDRESS_ERROR;
		जाओ end;
	पूर्ण
	अगर (tcode != TCODE_WRITE_QUADLET_REQUEST &&
	    tcode != TCODE_WRITE_BLOCK_REQUEST) अणु
		rcode = RCODE_TYPE_ERROR;
		जाओ end;
	पूर्ण

	अगर (length >= 1) अणु
		stream = READ_ONCE(scs->input);
		अगर (stream)
			midi_input_packet(scs, stream, data, length);
	पूर्ण

	rcode = RCODE_COMPLETE;
end:
	fw_send_response(card, request, rcode);
पूर्ण

अटल व्योम scs_ग_लिखो_callback(काष्ठा fw_card *card, पूर्णांक rcode,
			       व्योम *data, माप_प्रकार length, व्योम *callback_data)
अणु
	काष्ठा fw_scs1x *scs = callback_data;

	अगर (!rcode_is_permanent_error(rcode)) अणु
		/* Don't retry क्रम this data. */
		अगर (rcode == RCODE_COMPLETE)
			scs->transaction_bytes = 0;
	पूर्ण अन्यथा अणु
		scs->error = true;
	पूर्ण

	scs->transaction_running = false;
	schedule_work(&scs->work);
पूर्ण

अटल bool is_valid_running_status(u8 status)
अणु
	वापस status >= 0x80 && status <= 0xef;
पूर्ण

अटल bool is_one_byte_cmd(u8 status)
अणु
	वापस status == 0xf6 ||
	       status >= 0xf8;
पूर्ण

अटल bool is_two_bytes_cmd(u8 status)
अणु
	वापस (status >= 0xc0 && status <= 0xdf) ||
	       status == 0xf1 ||
	       status == 0xf3;
पूर्ण

अटल bool is_three_bytes_cmd(u8 status)
अणु
	वापस (status >= 0x80 && status <= 0xbf) ||
	       (status >= 0xe0 && status <= 0xef) ||
	       status == 0xf2;
पूर्ण

अटल bool is_invalid_cmd(u8 status)
अणु
	वापस status == 0xf4 ||
	       status == 0xf5 ||
	       status == 0xf9 ||
	       status == 0xfd;
पूर्ण

अटल व्योम scs_output_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fw_scs1x *scs = container_of(work, काष्ठा fw_scs1x, work);
	काष्ठा snd_rawmidi_substream *stream;
	अचिन्हित पूर्णांक i;
	u8 byte;
	पूर्णांक generation;

	अगर (scs->transaction_running)
		वापस;

	stream = READ_ONCE(scs->output);
	अगर (!stream || scs->error) अणु
		scs->output_idle = true;
		wake_up(&scs->idle_रुको);
		वापस;
	पूर्ण

	अगर (scs->transaction_bytes > 0)
		जाओ retry;

	i = scs->output_bytes;
	क्रम (;;) अणु
		अगर (snd_rawmidi_transmit(stream, &byte, 1) != 1) अणु
			scs->output_bytes = i;
			scs->output_idle = true;
			wake_up(&scs->idle_रुको);
			वापस;
		पूर्ण
		/*
		 * Convert from real MIDI to what I think the device expects (no
		 * running status, one command per packet, unescaped SysExs).
		 */
		अगर (scs->output_escaped && byte < 0x80) अणु
			अगर (scs->output_escape_high_nibble) अणु
				अगर (i < HSS1394_MAX_PACKET_SIZE) अणु
					scs->buffer[i] = byte << 4;
					scs->output_escape_high_nibble = false;
				पूर्ण
			पूर्ण अन्यथा अणु
				scs->buffer[i++] |= byte & 0x0f;
				scs->output_escape_high_nibble = true;
			पूर्ण
		पूर्ण अन्यथा अगर (byte < 0x80) अणु
			अगर (i == 1) अणु
				अगर (!is_valid_running_status(
							scs->output_status))
					जारी;
				scs->buffer[0] = HSS1394_TAG_USER_DATA;
				scs->buffer[i++] = scs->output_status;
			पूर्ण
			scs->buffer[i++] = byte;
			अगर ((i == 3 && is_two_bytes_cmd(scs->output_status)) ||
			    (i == 4 && is_three_bytes_cmd(scs->output_status)))
				अवरोध;
			अगर (i == 1 + ARRAY_SIZE(sysex_escape_prefix) &&
			    !स_भेद(scs->buffer + 1, sysex_escape_prefix,
				    ARRAY_SIZE(sysex_escape_prefix))) अणु
				scs->output_escaped = true;
				scs->output_escape_high_nibble = true;
				i = 0;
			पूर्ण
			अगर (i >= HSS1394_MAX_PACKET_SIZE)
				i = 1;
		पूर्ण अन्यथा अगर (byte == 0xf7) अणु
			अगर (scs->output_escaped) अणु
				अगर (i >= 1 && scs->output_escape_high_nibble &&
				    scs->buffer[0] !=
						HSS1394_TAG_CHANGE_ADDRESS)
					अवरोध;
			पूर्ण अन्यथा अणु
				अगर (i > 1 && scs->output_status == 0xf0) अणु
					scs->buffer[i++] = 0xf7;
					अवरोध;
				पूर्ण
			पूर्ण
			i = 1;
			scs->output_escaped = false;
		पूर्ण अन्यथा अगर (!is_invalid_cmd(byte) && byte < 0xf8) अणु
			i = 1;
			scs->buffer[0] = HSS1394_TAG_USER_DATA;
			scs->buffer[i++] = byte;
			scs->output_status = byte;
			scs->output_escaped = false;
			अगर (is_one_byte_cmd(byte))
				अवरोध;
		पूर्ण
	पूर्ण
	scs->output_bytes = 1;
	scs->output_escaped = false;

	scs->transaction_bytes = i;
retry:
	scs->transaction_running = true;
	generation = scs->fw_dev->generation;
	smp_rmb(); /* node_id vs. generation */
	fw_send_request(scs->fw_dev->card, &scs->transaction,
			TCODE_WRITE_BLOCK_REQUEST, scs->fw_dev->node_id,
			generation, scs->fw_dev->max_speed, HSS1394_ADDRESS,
			scs->buffer, scs->transaction_bytes,
			scs_ग_लिखो_callback, scs);
पूर्ण

अटल पूर्णांक midi_capture_खोलो(काष्ठा snd_rawmidi_substream *stream)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक midi_capture_बंद(काष्ठा snd_rawmidi_substream *stream)
अणु
	वापस 0;
पूर्ण

अटल व्योम midi_capture_trigger(काष्ठा snd_rawmidi_substream *stream, पूर्णांक up)
अणु
	काष्ठा fw_scs1x *scs = stream->rmidi->निजी_data;

	अगर (up) अणु
		scs->input_escape_count = 0;
		WRITE_ONCE(scs->input, stream);
	पूर्ण अन्यथा अणु
		WRITE_ONCE(scs->input, शून्य);
	पूर्ण
पूर्ण

अटल पूर्णांक midi_playback_खोलो(काष्ठा snd_rawmidi_substream *stream)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक midi_playback_बंद(काष्ठा snd_rawmidi_substream *stream)
अणु
	वापस 0;
पूर्ण

अटल व्योम midi_playback_trigger(काष्ठा snd_rawmidi_substream *stream, पूर्णांक up)
अणु
	काष्ठा fw_scs1x *scs = stream->rmidi->निजी_data;

	अगर (up) अणु
		scs->output_status = 0;
		scs->output_bytes = 1;
		scs->output_escaped = false;
		scs->output_idle = false;
		scs->transaction_bytes = 0;
		scs->error = false;

		WRITE_ONCE(scs->output, stream);
		schedule_work(&scs->work);
	पूर्ण अन्यथा अणु
		WRITE_ONCE(scs->output, शून्य);
	पूर्ण
पूर्ण
अटल व्योम midi_playback_drain(काष्ठा snd_rawmidi_substream *stream)
अणु
	काष्ठा fw_scs1x *scs = stream->rmidi->निजी_data;

	रुको_event(scs->idle_रुको, scs->output_idle);
पूर्ण

अटल पूर्णांक रेजिस्टर_address(काष्ठा snd_oxfw *oxfw)
अणु
	काष्ठा fw_scs1x *scs = oxfw->spec;
	__be64 data;

	data = cpu_to_be64(((u64)HSS1394_TAG_CHANGE_ADDRESS << 56) |
			    scs->hss_handler.offset);
	वापस snd_fw_transaction(oxfw->unit, TCODE_WRITE_BLOCK_REQUEST,
				  HSS1394_ADDRESS, &data, माप(data), 0);
पूर्ण

अटल व्योम हटाओ_scs1x(काष्ठा snd_rawmidi *rmidi)
अणु
	काष्ठा fw_scs1x *scs = rmidi->निजी_data;

	fw_core_हटाओ_address_handler(&scs->hss_handler);
पूर्ण

व्योम snd_oxfw_scs1x_update(काष्ठा snd_oxfw *oxfw)
अणु
	रेजिस्टर_address(oxfw);
पूर्ण

पूर्णांक snd_oxfw_scs1x_add(काष्ठा snd_oxfw *oxfw)
अणु
	अटल स्थिर काष्ठा snd_rawmidi_ops midi_capture_ops = अणु
		.खोलो    = midi_capture_खोलो,
		.बंद   = midi_capture_बंद,
		.trigger = midi_capture_trigger,
	पूर्ण;
	अटल स्थिर काष्ठा snd_rawmidi_ops midi_playback_ops = अणु
		.खोलो    = midi_playback_खोलो,
		.बंद   = midi_playback_बंद,
		.trigger = midi_playback_trigger,
		.drain   = midi_playback_drain,
	पूर्ण;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा fw_scs1x *scs;
	पूर्णांक err;

	scs = devm_kzalloc(&oxfw->card->card_dev, माप(काष्ठा fw_scs1x),
			   GFP_KERNEL);
	अगर (!scs)
		वापस -ENOMEM;
	scs->fw_dev = fw_parent_device(oxfw->unit);
	oxfw->spec = scs;

	/* Allocate own handler क्रम imcoming asynchronous transaction. */
	scs->hss_handler.length = HSS1394_MAX_PACKET_SIZE;
	scs->hss_handler.address_callback = handle_hss;
	scs->hss_handler.callback_data = scs;
	err = fw_core_add_address_handler(&scs->hss_handler,
					  &fw_high_memory_region);
	अगर (err < 0)
		वापस err;

	err = रेजिस्टर_address(oxfw);
	अगर (err < 0)
		जाओ err_allocated;

	/* Use unique name क्रम backward compatibility to scs1x module. */
	err = snd_rawmidi_new(oxfw->card, "SCS.1x", 0, 1, 1, &rmidi);
	अगर (err < 0)
		जाओ err_allocated;
	rmidi->निजी_data = scs;
	rmidi->निजी_मुक्त = हटाओ_scs1x;

	snम_लिखो(rmidi->name, माप(rmidi->name),
		 "%s MIDI", oxfw->card->लघुname);

	rmidi->info_flags = SNDRV_RAWMIDI_INFO_INPUT |
			    SNDRV_RAWMIDI_INFO_OUTPUT |
			    SNDRV_RAWMIDI_INFO_DUPLEX;
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT,
			    &midi_capture_ops);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
			    &midi_playback_ops);

	INIT_WORK(&scs->work, scs_output_work);
	init_रुकोqueue_head(&scs->idle_रुको);
	scs->output_idle = true;

	वापस 0;
err_allocated:
	fw_core_हटाओ_address_handler(&scs->hss_handler);
	वापस err;
पूर्ण
