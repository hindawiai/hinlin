<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tascam-transaction.c - a part of driver क्रम TASCAM FireWire series
 *
 * Copyright (c) 2015 Takashi Sakamoto
 */

#समावेश "tascam.h"

/*
 * When वापस minus value, given argument is not MIDI status.
 * When वापस 0, given argument is a beginning of प्रणाली exclusive.
 * When वापस the others, given argument is MIDI data.
 */
अटल अंतरभूत पूर्णांक calculate_message_bytes(u8 status)
अणु
	चयन (status) अणु
	हाल 0xf6:	/* Tune request. */
	हाल 0xf8:	/* Timing घड़ी. */
	हाल 0xfa:	/* Start. */
	हाल 0xfb:	/* Continue. */
	हाल 0xfc:	/* Stop. */
	हाल 0xfe:	/* Active sensing. */
	हाल 0xff:	/* System reset. */
		वापस 1;
	हाल 0xf1:	/* MIDI समय code quarter frame. */
	हाल 0xf3:	/* Song select. */
		वापस 2;
	हाल 0xf2:	/* Song position poपूर्णांकer. */
		वापस 3;
	हाल 0xf0:	/* Exclusive. */
		वापस 0;
	हाल 0xf7:	/* End of exclusive. */
		अवरोध;
	हाल 0xf4:	/* Undefined. */
	हाल 0xf5:	/* Undefined. */
	हाल 0xf9:	/* Undefined. */
	हाल 0xfd:	/* Undefined. */
		अवरोध;
	शेष:
		चयन (status & 0xf0) अणु
		हाल 0x80:	/* Note on. */
		हाल 0x90:	/* Note off. */
		हाल 0xa0:	/* Polyphonic key pressure. */
		हाल 0xb0:	/* Control change and Mode change. */
		हाल 0xe0:	/* Pitch bend change. */
			वापस 3;
		हाल 0xc0:	/* Program change. */
		हाल 0xd0:	/* Channel pressure. */
			वापस 2;
		शेष:
		अवरोध;
		पूर्ण
	अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक fill_message(काष्ठा snd_fw_async_midi_port *port,
			काष्ठा snd_rawmidi_substream *substream)
अणु
	पूर्णांक i, len, consume;
	u8 *label, *msg;
	u8 status;

	/* The first byte is used क्रम label, the rest क्रम MIDI bytes. */
	label = port->buf;
	msg = port->buf + 1;

	consume = snd_rawmidi_transmit_peek(substream, msg, 3);
	अगर (consume == 0)
		वापस 0;

	/* On exclusive message. */
	अगर (port->on_sysex) अणु
		/* Seek the end of exclusives. */
		क्रम (i = 0; i < consume; ++i) अणु
			अगर (msg[i] == 0xf7) अणु
				port->on_sysex = false;
				अवरोध;
			पूर्ण
		पूर्ण

		/* At the end of exclusive message, use label 0x07. */
		अगर (!port->on_sysex) अणु
			consume = i + 1;
			*label = (substream->number << 4) | 0x07;
		/* During exclusive message, use label 0x04. */
		पूर्ण अन्यथा अगर (consume == 3) अणु
			*label = (substream->number << 4) | 0x04;
		/* We need to fill whole 3 bytes. Go to next change. */
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण

		len = consume;
	पूर्ण अन्यथा अणु
		/* The beginning of exclusives. */
		अगर (msg[0] == 0xf0) अणु
			/* Transfer it in next chance in another condition. */
			port->on_sysex = true;
			वापस 0;
		पूर्ण अन्यथा अणु
			/* On running-status. */
			अगर ((msg[0] & 0x80) != 0x80)
				status = port->running_status;
			अन्यथा
				status = msg[0];

			/* Calculate consume bytes. */
			len = calculate_message_bytes(status);
			अगर (len <= 0)
				वापस 0;

			/* On running-status. */
			अगर ((msg[0] & 0x80) != 0x80) अणु
				/* Enough MIDI bytes were not retrieved. */
				अगर (consume < len - 1)
					वापस 0;
				consume = len - 1;

				msg[2] = msg[1];
				msg[1] = msg[0];
				msg[0] = port->running_status;
			पूर्ण अन्यथा अणु
				/* Enough MIDI bytes were not retrieved. */
				अगर (consume < len)
					वापस 0;
				consume = len;

				port->running_status = msg[0];
			पूर्ण
		पूर्ण

		*label = (substream->number << 4) | (msg[0] >> 4);
	पूर्ण

	अगर (len > 0 && len < 3)
		स_रखो(msg + len, 0, 3 - len);

	वापस consume;
पूर्ण

अटल व्योम async_midi_port_callback(काष्ठा fw_card *card, पूर्णांक rcode,
				     व्योम *data, माप_प्रकार length,
				     व्योम *callback_data)
अणु
	काष्ठा snd_fw_async_midi_port *port = callback_data;
	काष्ठा snd_rawmidi_substream *substream = READ_ONCE(port->substream);

	/* This port is बंदd. */
	अगर (substream == शून्य)
		वापस;

	अगर (rcode == RCODE_COMPLETE)
		snd_rawmidi_transmit_ack(substream, port->consume_bytes);
	अन्यथा अगर (!rcode_is_permanent_error(rcode))
		/* To start next transaction immediately क्रम recovery. */
		port->next_kसमय = 0;
	अन्यथा
		/* Don't जारी processing. */
		port->error = true;

	port->idling = true;

	अगर (!snd_rawmidi_transmit_empty(substream))
		schedule_work(&port->work);
पूर्ण

अटल व्योम midi_port_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_fw_async_midi_port *port =
			container_of(work, काष्ठा snd_fw_async_midi_port, work);
	काष्ठा snd_rawmidi_substream *substream = READ_ONCE(port->substream);
	पूर्णांक generation;

	/* Under transacting or error state. */
	अगर (!port->idling || port->error)
		वापस;

	/* Nothing to करो. */
	अगर (substream == शून्य || snd_rawmidi_transmit_empty(substream))
		वापस;

	/* Do it in next chance. */
	अगर (kसमय_after(port->next_kसमय, kसमय_get())) अणु
		schedule_work(&port->work);
		वापस;
	पूर्ण

	/*
	 * Fill the buffer. The callee must use snd_rawmidi_transmit_peek().
	 * Later, snd_rawmidi_transmit_ack() is called.
	 */
	स_रखो(port->buf, 0, 4);
	port->consume_bytes = fill_message(port, substream);
	अगर (port->consume_bytes <= 0) अणु
		/* Do it in next chance, immediately. */
		अगर (port->consume_bytes == 0) अणु
			port->next_kसमय = 0;
			schedule_work(&port->work);
		पूर्ण अन्यथा अणु
			/* Fatal error. */
			port->error = true;
		पूर्ण
		वापस;
	पूर्ण

	/* Set पूर्णांकerval to next transaction. */
	port->next_kसमय = kसमय_add_ns(kसमय_get(),
			port->consume_bytes * 8 * (NSEC_PER_SEC / 31250));

	/* Start this transaction. */
	port->idling = false;

	/*
	 * In Linux FireWire core, when generation is updated with memory
	 * barrier, node id has alपढ़ोy been updated. In this module, After
	 * this smp_rmb(), load/store inकाष्ठाions to memory are completed.
	 * Thus, both of generation and node id are available with recent
	 * values. This is a light-serialization solution to handle bus reset
	 * events on IEEE 1394 bus.
	 */
	generation = port->parent->generation;
	smp_rmb();

	fw_send_request(port->parent->card, &port->transaction,
			TCODE_WRITE_QUADLET_REQUEST,
			port->parent->node_id, generation,
			port->parent->max_speed,
			TSCM_ADDR_BASE + TSCM_OFFSET_MIDI_RX_QUAD,
			port->buf, 4, async_midi_port_callback,
			port);
पूर्ण

व्योम snd_fw_async_midi_port_init(काष्ठा snd_fw_async_midi_port *port)
अणु
	port->idling = true;
	port->error = false;
	port->running_status = 0;
	port->on_sysex = false;
पूर्ण

अटल व्योम handle_midi_tx(काष्ठा fw_card *card, काष्ठा fw_request *request,
			   पूर्णांक tcode, पूर्णांक destination, पूर्णांक source,
			   पूर्णांक generation, अचिन्हित दीर्घ दीर्घ offset,
			   व्योम *data, माप_प्रकार length, व्योम *callback_data)
अणु
	काष्ठा snd_tscm *tscm = callback_data;
	u32 *buf = (u32 *)data;
	अचिन्हित पूर्णांक messages;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक port;
	काष्ठा snd_rawmidi_substream *substream;
	u8 *b;
	पूर्णांक bytes;

	अगर (offset != tscm->async_handler.offset)
		जाओ end;

	messages = length / 8;
	क्रम (i = 0; i < messages; i++) अणु
		b = (u8 *)(buf + i * 2);

		port = b[0] >> 4;
		/* TODO: support भव MIDI ports. */
		अगर (port >= tscm->spec->midi_capture_ports)
			जाओ end;

		/* Assume the message length. */
		bytes = calculate_message_bytes(b[1]);
		/* On MIDI data or exclusives. */
		अगर (bytes <= 0) अणु
			/* Seek the end of exclusives. */
			क्रम (bytes = 1; bytes < 4; bytes++) अणु
				अगर (b[bytes] == 0xf7)
					अवरोध;
			पूर्ण
			अगर (bytes == 4)
				bytes = 3;
		पूर्ण

		substream = READ_ONCE(tscm->tx_midi_substreams[port]);
		अगर (substream != शून्य)
			snd_rawmidi_receive(substream, b + 1, bytes);
	पूर्ण
end:
	fw_send_response(card, request, RCODE_COMPLETE);
पूर्ण

पूर्णांक snd_tscm_transaction_रेजिस्टर(काष्ठा snd_tscm *tscm)
अणु
	अटल स्थिर काष्ठा fw_address_region resp_रेजिस्टर_region = अणु
		.start	= 0xffffe0000000ull,
		.end	= 0xffffe000ffffull,
	पूर्ण;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	/*
	 * Usually, two quadlets are transferred by one transaction. The first
	 * quadlet has MIDI messages, the rest includes बारtamp.
	 * Someबार, 8 set of the data is transferred by a block transaction.
	 */
	tscm->async_handler.length = 8 * 8;
	tscm->async_handler.address_callback = handle_midi_tx;
	tscm->async_handler.callback_data = tscm;

	err = fw_core_add_address_handler(&tscm->async_handler,
					  &resp_रेजिस्टर_region);
	अगर (err < 0)
		वापस err;

	err = snd_tscm_transaction_reरेजिस्टर(tscm);
	अगर (err < 0)
		जाओ error;

	क्रम (i = 0; i < TSCM_MIDI_OUT_PORT_MAX; i++) अणु
		tscm->out_ports[i].parent = fw_parent_device(tscm->unit);
		tscm->out_ports[i].next_kसमय = 0;
		INIT_WORK(&tscm->out_ports[i].work, midi_port_work);
	पूर्ण

	वापस err;
error:
	fw_core_हटाओ_address_handler(&tscm->async_handler);
	tscm->async_handler.callback_data = शून्य;
	वापस err;
पूर्ण

/* At bus reset, these रेजिस्टरs are cleared. */
पूर्णांक snd_tscm_transaction_reरेजिस्टर(काष्ठा snd_tscm *tscm)
अणु
	काष्ठा fw_device *device = fw_parent_device(tscm->unit);
	__be32 reg;
	पूर्णांक err;

	/* Register messaging address. Block transaction is not allowed. */
	reg = cpu_to_be32((device->card->node_id << 16) |
			  (tscm->async_handler.offset >> 32));
	err = snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				 TSCM_ADDR_BASE + TSCM_OFFSET_MIDI_TX_ADDR_HI,
				 &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	reg = cpu_to_be32(tscm->async_handler.offset);
	err = snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				 TSCM_ADDR_BASE + TSCM_OFFSET_MIDI_TX_ADDR_LO,
				 &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	/* Turn on messaging. */
	reg = cpu_to_be32(0x00000001);
	err = snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				  TSCM_ADDR_BASE + TSCM_OFFSET_MIDI_TX_ON,
				  &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	/* Turn on FireWire LED. */
	reg = cpu_to_be32(0x0001008e);
	वापस snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				  TSCM_ADDR_BASE + TSCM_OFFSET_LED_POWER,
				  &reg, माप(reg), 0);
पूर्ण

व्योम snd_tscm_transaction_unरेजिस्टर(काष्ठा snd_tscm *tscm)
अणु
	__be32 reg;

	अगर (tscm->async_handler.callback_data == शून्य)
		वापस;

	/* Turn off FireWire LED. */
	reg = cpu_to_be32(0x0000008e);
	snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
			   TSCM_ADDR_BASE + TSCM_OFFSET_LED_POWER,
			   &reg, माप(reg), 0);

	/* Turn off messaging. */
	reg = cpu_to_be32(0x00000000);
	snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
			   TSCM_ADDR_BASE + TSCM_OFFSET_MIDI_TX_ON,
			   &reg, माप(reg), 0);

	/* Unरेजिस्टर the address. */
	snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
			   TSCM_ADDR_BASE + TSCM_OFFSET_MIDI_TX_ADDR_HI,
			   &reg, माप(reg), 0);
	snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
			   TSCM_ADDR_BASE + TSCM_OFFSET_MIDI_TX_ADDR_LO,
			   &reg, माप(reg), 0);

	fw_core_हटाओ_address_handler(&tscm->async_handler);
	tscm->async_handler.callback_data = शून्य;
पूर्ण
