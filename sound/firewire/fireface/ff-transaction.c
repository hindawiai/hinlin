<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ff-transaction.c - a part of driver क्रम RME Fireface series
 *
 * Copyright (c) 2015-2017 Takashi Sakamoto
 */

#समावेश "ff.h"

अटल व्योम finish_transmit_midi_msg(काष्ठा snd_ff *ff, अचिन्हित पूर्णांक port,
				     पूर्णांक rcode)
अणु
	काष्ठा snd_rawmidi_substream *substream =
				READ_ONCE(ff->rx_midi_substreams[port]);

	अगर (rcode_is_permanent_error(rcode)) अणु
		ff->rx_midi_error[port] = true;
		वापस;
	पूर्ण

	अगर (rcode != RCODE_COMPLETE) अणु
		/* Transfer the message again, immediately. */
		ff->next_kसमय[port] = 0;
		schedule_work(&ff->rx_midi_work[port]);
		वापस;
	पूर्ण

	snd_rawmidi_transmit_ack(substream, ff->rx_bytes[port]);
	ff->rx_bytes[port] = 0;

	अगर (!snd_rawmidi_transmit_empty(substream))
		schedule_work(&ff->rx_midi_work[port]);
पूर्ण

अटल व्योम finish_transmit_midi0_msg(काष्ठा fw_card *card, पूर्णांक rcode,
				      व्योम *data, माप_प्रकार length,
				      व्योम *callback_data)
अणु
	काष्ठा snd_ff *ff =
		container_of(callback_data, काष्ठा snd_ff, transactions[0]);
	finish_transmit_midi_msg(ff, 0, rcode);
पूर्ण

अटल व्योम finish_transmit_midi1_msg(काष्ठा fw_card *card, पूर्णांक rcode,
				      व्योम *data, माप_प्रकार length,
				      व्योम *callback_data)
अणु
	काष्ठा snd_ff *ff =
		container_of(callback_data, काष्ठा snd_ff, transactions[1]);
	finish_transmit_midi_msg(ff, 1, rcode);
पूर्ण

अटल व्योम transmit_midi_msg(काष्ठा snd_ff *ff, अचिन्हित पूर्णांक port)
अणु
	काष्ठा snd_rawmidi_substream *substream =
			READ_ONCE(ff->rx_midi_substreams[port]);
	पूर्णांक quad_count;

	काष्ठा fw_device *fw_dev = fw_parent_device(ff->unit);
	अचिन्हित दीर्घ दीर्घ addr;
	पूर्णांक generation;
	fw_transaction_callback_t callback;
	पूर्णांक tcode;

	अगर (substream == शून्य || snd_rawmidi_transmit_empty(substream))
		वापस;

	अगर (ff->rx_bytes[port] > 0 || ff->rx_midi_error[port])
		वापस;

	/* Do it in next chance. */
	अगर (kसमय_after(ff->next_kसमय[port], kसमय_get())) अणु
		schedule_work(&ff->rx_midi_work[port]);
		वापस;
	पूर्ण

	quad_count = ff->spec->protocol->fill_midi_msg(ff, substream, port);
	अगर (quad_count <= 0)
		वापस;

	अगर (port == 0) अणु
		addr = ff->spec->midi_rx_addrs[0];
		callback = finish_transmit_midi0_msg;
	पूर्ण अन्यथा अणु
		addr = ff->spec->midi_rx_addrs[1];
		callback = finish_transmit_midi1_msg;
	पूर्ण

	/* Set पूर्णांकerval to next transaction. */
	ff->next_kसमय[port] = kसमय_add_ns(kसमय_get(),
			ff->rx_bytes[port] * 8 * (NSEC_PER_SEC / 31250));

	अगर (quad_count == 1)
		tcode = TCODE_WRITE_QUADLET_REQUEST;
	अन्यथा
		tcode = TCODE_WRITE_BLOCK_REQUEST;

	/*
	 * In Linux FireWire core, when generation is updated with memory
	 * barrier, node id has alपढ़ोy been updated. In this module, After
	 * this smp_rmb(), load/store inकाष्ठाions to memory are completed.
	 * Thus, both of generation and node id are available with recent
	 * values. This is a light-serialization solution to handle bus reset
	 * events on IEEE 1394 bus.
	 */
	generation = fw_dev->generation;
	smp_rmb();
	fw_send_request(fw_dev->card, &ff->transactions[port], tcode,
			fw_dev->node_id, generation, fw_dev->max_speed,
			addr, &ff->msg_buf[port], quad_count * 4,
			callback, &ff->transactions[port]);
पूर्ण

अटल व्योम transmit_midi0_msg(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_ff *ff = container_of(work, काष्ठा snd_ff, rx_midi_work[0]);

	transmit_midi_msg(ff, 0);
पूर्ण

अटल व्योम transmit_midi1_msg(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_ff *ff = container_of(work, काष्ठा snd_ff, rx_midi_work[1]);

	transmit_midi_msg(ff, 1);
पूर्ण

अटल व्योम handle_midi_msg(काष्ठा fw_card *card, काष्ठा fw_request *request,
			    पूर्णांक tcode, पूर्णांक destination, पूर्णांक source,
			    पूर्णांक generation, अचिन्हित दीर्घ दीर्घ offset,
			    व्योम *data, माप_प्रकार length, व्योम *callback_data)
अणु
	काष्ठा snd_ff *ff = callback_data;
	__le32 *buf = data;

	fw_send_response(card, request, RCODE_COMPLETE);

	offset -= ff->async_handler.offset;
	ff->spec->protocol->handle_midi_msg(ff, (अचिन्हित पूर्णांक)offset, buf,
					    length);
पूर्ण

अटल पूर्णांक allocate_own_address(काष्ठा snd_ff *ff, पूर्णांक i)
अणु
	काष्ठा fw_address_region midi_msg_region;
	पूर्णांक err;

	ff->async_handler.length = ff->spec->midi_addr_range;
	ff->async_handler.address_callback = handle_midi_msg;
	ff->async_handler.callback_data = ff;

	midi_msg_region.start = 0x000100000000ull * i;
	midi_msg_region.end = midi_msg_region.start + ff->async_handler.length;

	err = fw_core_add_address_handler(&ff->async_handler, &midi_msg_region);
	अगर (err >= 0) अणु
		/* Controllers are allowed to रेजिस्टर this region. */
		अगर (ff->async_handler.offset & 0x0000ffffffff) अणु
			fw_core_हटाओ_address_handler(&ff->async_handler);
			err = -EAGAIN;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

// Controllers are allowed to रेजिस्टर higher 4 bytes of destination address to
// receive asynchronous transactions क्रम MIDI messages, जबतक the way to
// रेजिस्टर lower 4 bytes of address is dअगरferent depending on protocols. For
// details, please refer to comments in protocol implementations.
//
// This driver expects userspace applications to configure रेजिस्टरs क्रम the
// lower address because in most हालs such रेजिस्टरs has the other settings.
पूर्णांक snd_ff_transaction_reरेजिस्टर(काष्ठा snd_ff *ff)
अणु
	काष्ठा fw_card *fw_card = fw_parent_device(ff->unit)->card;
	u32 addr;
	__le32 reg;

	/*
	 * Controllers are allowed to रेजिस्टर its node ID and upper 2 byte of
	 * local address to listen asynchronous transactions.
	 */
	addr = (fw_card->node_id << 16) | (ff->async_handler.offset >> 32);
	reg = cpu_to_le32(addr);
	वापस snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				  ff->spec->midi_high_addr,
				  &reg, माप(reg), 0);
पूर्ण

पूर्णांक snd_ff_transaction_रेजिस्टर(काष्ठा snd_ff *ff)
अणु
	पूर्णांक i, err;

	/*
	 * Allocate in Memory Space of IEC 13213, but lower 4 byte in LSB should
	 * be zero due to device specअगरication.
	 */
	क्रम (i = 0; i < 0xffff; i++) अणु
		err = allocate_own_address(ff, i);
		अगर (err != -EBUSY && err != -EAGAIN)
			अवरोध;
	पूर्ण
	अगर (err < 0)
		वापस err;

	err = snd_ff_transaction_reरेजिस्टर(ff);
	अगर (err < 0)
		वापस err;

	INIT_WORK(&ff->rx_midi_work[0], transmit_midi0_msg);
	INIT_WORK(&ff->rx_midi_work[1], transmit_midi1_msg);

	वापस 0;
पूर्ण

व्योम snd_ff_transaction_unरेजिस्टर(काष्ठा snd_ff *ff)
अणु
	__le32 reg;

	अगर (ff->async_handler.callback_data == शून्य)
		वापस;
	ff->async_handler.callback_data = शून्य;

	/* Release higher 4 bytes of address. */
	reg = cpu_to_le32(0x00000000);
	snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
			   ff->spec->midi_high_addr,
			   &reg, माप(reg), 0);

	fw_core_हटाओ_address_handler(&ff->async_handler);
पूर्ण
