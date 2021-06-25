<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * amdtp-करोt.c - a part of driver क्रम Digidesign Digi 002/003 family
 *
 * Copyright (c) 2014-2015 Takashi Sakamoto
 * Copyright (C) 2012 Robin Gareus <robin@gareus.org>
 * Copyright (C) 2012 Damien Zammit <damien@zamaudio.com>
 */

#समावेश <sound/pcm.h>
#समावेश "digi00x.h"

#घोषणा CIP_FMT_AM		0x10

/* 'Clock-based rate control mode' is just supported. */
#घोषणा AMDTP_FDF_AM824		0x00

/*
 * Nominally 3125 bytes/second, but the MIDI port's घड़ी might be
 * 1% too slow, and the bus घड़ी 100 ppm too fast.
 */
#घोषणा MIDI_BYTES_PER_SECOND	3093

/*
 * Several devices look only at the first eight data blocks.
 * In any हाल, this is more than enough क्रम the MIDI data rate.
 */
#घोषणा MAX_MIDI_RX_BLOCKS	8

/* 3 = MAX(DOT_MIDI_IN_PORTS, DOT_MIDI_OUT_PORTS) + 1. */
#घोषणा MAX_MIDI_PORTS		3

/*
 * The द्विगुन-oh-three algorithm was discovered by Robin Gareus and Damien
 * Zammit in 2012, with reverse-engineering क्रम Digi 003 Rack.
 */
काष्ठा करोt_state अणु
	u8 carry;
	u8 idx;
	अचिन्हित पूर्णांक off;
पूर्ण;

काष्ठा amdtp_करोt अणु
	अचिन्हित पूर्णांक pcm_channels;
	काष्ठा करोt_state state;

	काष्ठा snd_rawmidi_substream *midi[MAX_MIDI_PORTS];
	पूर्णांक midi_fअगरo_used[MAX_MIDI_PORTS];
	पूर्णांक midi_fअगरo_limit;
पूर्ण;

/*
 * द्विगुन-oh-three look up table
 *
 * @param idx index byte (audio-sample data) 0x00..0xff
 * @param off channel offset shअगरt
 * @वापस salt to XOR with given data
 */
#घोषणा BYTE_PER_SAMPLE (4)
#घोषणा MAGIC_DOT_BYTE (2)
#घोषणा MAGIC_BYTE_OFF(x) (((x) * BYTE_PER_SAMPLE) + MAGIC_DOT_BYTE)
अटल u8 करोt_scrt(स्थिर u8 idx, स्थिर अचिन्हित पूर्णांक off)
अणु
	/*
	 * the length of the added pattern only depends on the lower nibble
	 * of the last non-zero data
	 */
	अटल स्थिर u8 len[16] = अणु0, 1, 3, 5, 7, 9, 11, 13, 14,
				   12, 10, 8, 6, 4, 2, 0पूर्ण;

	/*
	 * the lower nibble of the salt. Interleaved sequence.
	 * this is walked backwards according to len[]
	 */
	अटल स्थिर u8 nib[15] = अणु0x8, 0x7, 0x9, 0x6, 0xa, 0x5, 0xb, 0x4,
				   0xc, 0x3, 0xd, 0x2, 0xe, 0x1, 0xfपूर्ण;

	/* circular list क्रम the salt's hi nibble. */
	अटल स्थिर u8 hir[15] = अणु0x0, 0x6, 0xf, 0x8, 0x7, 0x5, 0x3, 0x4,
				   0xc, 0xd, 0xe, 0x1, 0x2, 0xb, 0xaपूर्ण;

	/*
	 * start offset क्रम upper nibble mapping.
	 * note: 9 is /special/. In the हाल where the high nibble == 0x9,
	 * hir[] is not used and - coincidentally - the salt's hi nibble is
	 * 0x09 regardless of the offset.
	 */
	अटल स्थिर u8 hio[16] = अणु0, 11, 12, 6, 7, 5, 1, 4,
				   3, 0x00, 14, 13, 8, 9, 10, 2पूर्ण;

	स्थिर u8 ln = idx & 0xf;
	स्थिर u8 hn = (idx >> 4) & 0xf;
	स्थिर u8 hr = (hn == 0x9) ? 0x9 : hir[(hio[hn] + off) % 15];

	अगर (len[ln] < off)
		वापस 0x00;

	वापस ((nib[14 + off - len[ln]]) | (hr << 4));
पूर्ण

अटल व्योम करोt_encode_step(काष्ठा करोt_state *state, __be32 *स्थिर buffer)
अणु
	u8 * स्थिर data = (u8 *) buffer;

	अगर (data[MAGIC_DOT_BYTE] != 0x00) अणु
		state->off = 0;
		state->idx = data[MAGIC_DOT_BYTE] ^ state->carry;
	पूर्ण
	data[MAGIC_DOT_BYTE] ^= state->carry;
	state->carry = करोt_scrt(state->idx, ++(state->off));
पूर्ण

पूर्णांक amdtp_करोt_set_parameters(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक rate,
			     अचिन्हित पूर्णांक pcm_channels)
अणु
	काष्ठा amdtp_करोt *p = s->protocol;
	पूर्णांक err;

	अगर (amdtp_stream_running(s))
		वापस -EBUSY;

	/*
	 * A first data channel is क्रम MIDI messages, the rest is Multi Bit
	 * Linear Audio data channel.
	 */
	err = amdtp_stream_set_parameters(s, rate, pcm_channels + 1);
	अगर (err < 0)
		वापस err;

	s->ctx_data.rx.fdf = AMDTP_FDF_AM824 | s->sfc;

	p->pcm_channels = pcm_channels;

	/*
	 * We करो not know the actual MIDI FIFO size of most devices.  Just
	 * assume two bytes, i.e., one byte can be received over the bus जबतक
	 * the previous one is transmitted over MIDI.
	 * (The value here is adjusted क्रम midi_ratelimit_per_packet().)
	 */
	p->midi_fअगरo_limit = rate - MIDI_BYTES_PER_SECOND * s->syt_पूर्णांकerval + 1;

	वापस 0;
पूर्ण

अटल व्योम ग_लिखो_pcm_s32(काष्ठा amdtp_stream *s, काष्ठा snd_pcm_substream *pcm,
			  __be32 *buffer, अचिन्हित पूर्णांक frames,
			  अचिन्हित पूर्णांक pcm_frames)
अणु
	काष्ठा amdtp_करोt *p = s->protocol;
	अचिन्हित पूर्णांक channels = p->pcm_channels;
	काष्ठा snd_pcm_runसमय *runसमय = pcm->runसमय;
	अचिन्हित पूर्णांक pcm_buffer_poपूर्णांकer;
	पूर्णांक reमुख्यing_frames;
	स्थिर u32 *src;
	पूर्णांक i, c;

	pcm_buffer_poपूर्णांकer = s->pcm_buffer_poपूर्णांकer + pcm_frames;
	pcm_buffer_poपूर्णांकer %= runसमय->buffer_size;

	src = (व्योम *)runसमय->dma_area +
				frames_to_bytes(runसमय, pcm_buffer_poपूर्णांकer);
	reमुख्यing_frames = runसमय->buffer_size - pcm_buffer_poपूर्णांकer;

	buffer++;
	क्रम (i = 0; i < frames; ++i) अणु
		क्रम (c = 0; c < channels; ++c) अणु
			buffer[c] = cpu_to_be32((*src >> 8) | 0x40000000);
			करोt_encode_step(&p->state, &buffer[c]);
			src++;
		पूर्ण
		buffer += s->data_block_quadlets;
		अगर (--reमुख्यing_frames == 0)
			src = (व्योम *)runसमय->dma_area;
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_pcm_s32(काष्ठा amdtp_stream *s, काष्ठा snd_pcm_substream *pcm,
			 __be32 *buffer, अचिन्हित पूर्णांक frames,
			 अचिन्हित पूर्णांक pcm_frames)
अणु
	काष्ठा amdtp_करोt *p = s->protocol;
	अचिन्हित पूर्णांक channels = p->pcm_channels;
	काष्ठा snd_pcm_runसमय *runसमय = pcm->runसमय;
	अचिन्हित पूर्णांक pcm_buffer_poपूर्णांकer;
	पूर्णांक reमुख्यing_frames;
	u32 *dst;
	पूर्णांक i, c;

	pcm_buffer_poपूर्णांकer = s->pcm_buffer_poपूर्णांकer + pcm_frames;
	pcm_buffer_poपूर्णांकer %= runसमय->buffer_size;

	dst  = (व्योम *)runसमय->dma_area +
				frames_to_bytes(runसमय, pcm_buffer_poपूर्णांकer);
	reमुख्यing_frames = runसमय->buffer_size - pcm_buffer_poपूर्णांकer;

	buffer++;
	क्रम (i = 0; i < frames; ++i) अणु
		क्रम (c = 0; c < channels; ++c) अणु
			*dst = be32_to_cpu(buffer[c]) << 8;
			dst++;
		पूर्ण
		buffer += s->data_block_quadlets;
		अगर (--reमुख्यing_frames == 0)
			dst = (व्योम *)runसमय->dma_area;
	पूर्ण
पूर्ण

अटल व्योम ग_लिखो_pcm_silence(काष्ठा amdtp_stream *s, __be32 *buffer,
			      अचिन्हित पूर्णांक data_blocks)
अणु
	काष्ठा amdtp_करोt *p = s->protocol;
	अचिन्हित पूर्णांक channels, i, c;

	channels = p->pcm_channels;

	buffer++;
	क्रम (i = 0; i < data_blocks; ++i) अणु
		क्रम (c = 0; c < channels; ++c)
			buffer[c] = cpu_to_be32(0x40000000);
		buffer += s->data_block_quadlets;
	पूर्ण
पूर्ण

अटल bool midi_ratelimit_per_packet(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक port)
अणु
	काष्ठा amdtp_करोt *p = s->protocol;
	पूर्णांक used;

	used = p->midi_fअगरo_used[port];
	अगर (used == 0)
		वापस true;

	used -= MIDI_BYTES_PER_SECOND * s->syt_पूर्णांकerval;
	used = max(used, 0);
	p->midi_fअगरo_used[port] = used;

	वापस used < p->midi_fअगरo_limit;
पूर्ण

अटल अंतरभूत व्योम midi_use_bytes(काष्ठा amdtp_stream *s,
				  अचिन्हित पूर्णांक port, अचिन्हित पूर्णांक count)
अणु
	काष्ठा amdtp_करोt *p = s->protocol;

	p->midi_fअगरo_used[port] += amdtp_rate_table[s->sfc] * count;
पूर्ण

अटल व्योम ग_लिखो_midi_messages(काष्ठा amdtp_stream *s, __be32 *buffer,
		अचिन्हित पूर्णांक data_blocks, अचिन्हित पूर्णांक data_block_counter)
अणु
	काष्ठा amdtp_करोt *p = s->protocol;
	अचिन्हित पूर्णांक f, port;
	पूर्णांक len;
	u8 *b;

	क्रम (f = 0; f < data_blocks; f++) अणु
		port = (data_block_counter + f) % 8;
		b = (u8 *)&buffer[0];

		len = 0;
		अगर (port < MAX_MIDI_PORTS &&
		    midi_ratelimit_per_packet(s, port) &&
		    p->midi[port] != शून्य)
			len = snd_rawmidi_transmit(p->midi[port], b + 1, 2);

		अगर (len > 0) अणु
			/*
			 * Upper 4 bits of LSB represent port number.
			 * - 0000b: physical MIDI port 1.
			 * - 0010b: physical MIDI port 2.
			 * - 1110b: console MIDI port.
			 */
			अगर (port == 2)
				b[3] = 0xe0;
			अन्यथा अगर (port == 1)
				b[3] = 0x20;
			अन्यथा
				b[3] = 0x00;
			b[3] |= len;
			midi_use_bytes(s, port, len);
		पूर्ण अन्यथा अणु
			b[1] = 0;
			b[2] = 0;
			b[3] = 0;
		पूर्ण
		b[0] = 0x80;

		buffer += s->data_block_quadlets;
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_midi_messages(काष्ठा amdtp_stream *s, __be32 *buffer,
			       अचिन्हित पूर्णांक data_blocks)
अणु
	काष्ठा amdtp_करोt *p = s->protocol;
	अचिन्हित पूर्णांक f, port, len;
	u8 *b;

	क्रम (f = 0; f < data_blocks; f++) अणु
		b = (u8 *)&buffer[0];

		len = b[3] & 0x0f;
		अगर (len > 0) अणु
			/*
			 * Upper 4 bits of LSB represent port number.
			 * - 0000b: physical MIDI port 1. Use port 0.
			 * - 1110b: console MIDI port. Use port 2.
			 */
			अगर (b[3] >> 4 > 0)
				port = 2;
			अन्यथा
				port = 0;

			अगर (port < MAX_MIDI_PORTS && p->midi[port])
				snd_rawmidi_receive(p->midi[port], b + 1, len);
		पूर्ण

		buffer += s->data_block_quadlets;
	पूर्ण
पूर्ण

पूर्णांक amdtp_करोt_add_pcm_hw_स्थिरraपूर्णांकs(काष्ठा amdtp_stream *s,
				     काष्ठा snd_pcm_runसमय *runसमय)
अणु
	पूर्णांक err;

	/* This protocol delivers 24 bit data in 32bit data channel. */
	err = snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);
	अगर (err < 0)
		वापस err;

	वापस amdtp_stream_add_pcm_hw_स्थिरraपूर्णांकs(s, runसमय);
पूर्ण

व्योम amdtp_करोt_midi_trigger(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक port,
			  काष्ठा snd_rawmidi_substream *midi)
अणु
	काष्ठा amdtp_करोt *p = s->protocol;

	अगर (port < MAX_MIDI_PORTS)
		WRITE_ONCE(p->midi[port], midi);
पूर्ण

अटल अचिन्हित पूर्णांक process_ir_ctx_payloads(काष्ठा amdtp_stream *s,
					    स्थिर काष्ठा pkt_desc *descs,
					    अचिन्हित पूर्णांक packets,
					    काष्ठा snd_pcm_substream *pcm)
अणु
	अचिन्हित पूर्णांक pcm_frames = 0;
	पूर्णांक i;

	क्रम (i = 0; i < packets; ++i) अणु
		स्थिर काष्ठा pkt_desc *desc = descs + i;
		__be32 *buf = desc->ctx_payload;
		अचिन्हित पूर्णांक data_blocks = desc->data_blocks;

		अगर (pcm) अणु
			पढ़ो_pcm_s32(s, pcm, buf, data_blocks, pcm_frames);
			pcm_frames += data_blocks;
		पूर्ण

		पढ़ो_midi_messages(s, buf, data_blocks);
	पूर्ण

	वापस pcm_frames;
पूर्ण

अटल अचिन्हित पूर्णांक process_it_ctx_payloads(काष्ठा amdtp_stream *s,
					    स्थिर काष्ठा pkt_desc *descs,
					    अचिन्हित पूर्णांक packets,
					    काष्ठा snd_pcm_substream *pcm)
अणु
	अचिन्हित पूर्णांक pcm_frames = 0;
	पूर्णांक i;

	क्रम (i = 0; i < packets; ++i) अणु
		स्थिर काष्ठा pkt_desc *desc = descs + i;
		__be32 *buf = desc->ctx_payload;
		अचिन्हित पूर्णांक data_blocks = desc->data_blocks;

		अगर (pcm) अणु
			ग_लिखो_pcm_s32(s, pcm, buf, data_blocks, pcm_frames);
			pcm_frames += data_blocks;
		पूर्ण अन्यथा अणु
			ग_लिखो_pcm_silence(s, buf, data_blocks);
		पूर्ण

		ग_लिखो_midi_messages(s, buf, data_blocks,
				    desc->data_block_counter);
	पूर्ण

	वापस pcm_frames;
पूर्ण

पूर्णांक amdtp_करोt_init(काष्ठा amdtp_stream *s, काष्ठा fw_unit *unit,
		 क्रमागत amdtp_stream_direction dir)
अणु
	amdtp_stream_process_ctx_payloads_t process_ctx_payloads;
	क्रमागत cip_flags flags;

	// Use dअगरferent mode between incoming/outgoing.
	अगर (dir == AMDTP_IN_STREAM) अणु
		flags = CIP_NONBLOCKING;
		process_ctx_payloads = process_ir_ctx_payloads;
	पूर्ण अन्यथा अणु
		flags = CIP_BLOCKING;
		process_ctx_payloads = process_it_ctx_payloads;
	पूर्ण

	वापस amdtp_stream_init(s, unit, dir, flags, CIP_FMT_AM,
				process_ctx_payloads, माप(काष्ठा amdtp_करोt));
पूर्ण

व्योम amdtp_करोt_reset(काष्ठा amdtp_stream *s)
अणु
	काष्ठा amdtp_करोt *p = s->protocol;

	p->state.carry = 0x00;
	p->state.idx = 0x00;
	p->state.off = 0;
पूर्ण
