<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * amdtp-motu.c - a part of driver क्रम MOTU FireWire series
 *
 * Copyright (c) 2015-2017 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>
#समावेश "motu.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "amdtp-motu-trace.h"

#घोषणा CIP_FMT_MOTU		0x02
#घोषणा CIP_FMT_MOTU_TX_V3	0x22
#घोषणा MOTU_FDF_AM824		0x22

/*
 * Nominally 3125 bytes/second, but the MIDI port's घड़ी might be
 * 1% too slow, and the bus घड़ी 100 ppm too fast.
 */
#घोषणा MIDI_BYTES_PER_SECOND	3093

काष्ठा amdtp_motu अणु
	/* For बारtamp processing.  */
	अचिन्हित पूर्णांक quotient_ticks_per_event;
	अचिन्हित पूर्णांक reमुख्यder_ticks_per_event;
	अचिन्हित पूर्णांक next_ticks;
	अचिन्हित पूर्णांक next_accumulated;
	अचिन्हित पूर्णांक next_cycles;
	अचिन्हित पूर्णांक next_seconds;

	अचिन्हित पूर्णांक pcm_chunks;
	अचिन्हित पूर्णांक pcm_byte_offset;

	काष्ठा snd_rawmidi_substream *midi;
	अचिन्हित पूर्णांक midi_ports;
	अचिन्हित पूर्णांक midi_flag_offset;
	अचिन्हित पूर्णांक midi_byte_offset;

	पूर्णांक midi_db_count;
	अचिन्हित पूर्णांक midi_db_पूर्णांकerval;
पूर्ण;

पूर्णांक amdtp_motu_set_parameters(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक rate,
			      अचिन्हित पूर्णांक midi_ports,
			      काष्ठा snd_motu_packet_क्रमmat *क्रमmats)
अणु
	अटल स्थिर काष्ठा अणु
		अचिन्हित पूर्णांक quotient_ticks_per_event;
		अचिन्हित पूर्णांक reमुख्यder_ticks_per_event;
	पूर्ण params[] = अणु
		[CIP_SFC_44100]  = अणु 557, 123 पूर्ण,
		[CIP_SFC_48000]  = अणु 512,   0 पूर्ण,
		[CIP_SFC_88200]  = अणु 278, 282 पूर्ण,
		[CIP_SFC_96000]  = अणु 256,   0 पूर्ण,
		[CIP_SFC_176400] = अणु 139, 141 पूर्ण,
		[CIP_SFC_192000] = अणु 128,   0 पूर्ण,
	पूर्ण;
	काष्ठा amdtp_motu *p = s->protocol;
	अचिन्हित पूर्णांक pcm_chunks, data_chunks, data_block_quadlets;
	अचिन्हित पूर्णांक delay;
	अचिन्हित पूर्णांक mode;
	पूर्णांक i, err;

	अगर (amdtp_stream_running(s))
		वापस -EBUSY;

	क्रम (i = 0; i < ARRAY_SIZE(snd_motu_घड़ी_rates); ++i) अणु
		अगर (snd_motu_घड़ी_rates[i] == rate) अणु
			mode = i >> 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(snd_motu_घड़ी_rates))
		वापस -EINVAL;

	// Each data block includes SPH in its head. Data chunks follow with
	// 3 byte alignment. Padding follows with zero to conक्रमm to quadlet
	// alignment.
	pcm_chunks = क्रमmats->pcm_chunks[mode];
	data_chunks = क्रमmats->msg_chunks + pcm_chunks;
	data_block_quadlets = 1 + DIV_ROUND_UP(data_chunks * 3, 4);

	err = amdtp_stream_set_parameters(s, rate, data_block_quadlets);
	अगर (err < 0)
		वापस err;

	p->pcm_chunks = pcm_chunks;
	p->pcm_byte_offset = क्रमmats->pcm_byte_offset;

	p->midi_ports = midi_ports;
	p->midi_flag_offset = क्रमmats->midi_flag_offset;
	p->midi_byte_offset = क्रमmats->midi_byte_offset;

	p->midi_db_count = 0;
	p->midi_db_पूर्णांकerval = rate / MIDI_BYTES_PER_SECOND;

	/* IEEE 1394 bus requires. */
	delay = 0x2e00;

	/* For no-data or empty packets to adjust PCM sampling frequency. */
	delay += 8000 * 3072 * s->syt_पूर्णांकerval / rate;

	p->next_seconds = 0;
	p->next_cycles = delay / 3072;
	p->quotient_ticks_per_event = params[s->sfc].quotient_ticks_per_event;
	p->reमुख्यder_ticks_per_event = params[s->sfc].reमुख्यder_ticks_per_event;
	p->next_ticks = delay % 3072;
	p->next_accumulated = 0;

	वापस 0;
पूर्ण

अटल व्योम पढ़ो_pcm_s32(काष्ठा amdtp_stream *s, काष्ठा snd_pcm_substream *pcm,
			 __be32 *buffer, अचिन्हित पूर्णांक data_blocks,
			 अचिन्हित पूर्णांक pcm_frames)
अणु
	काष्ठा amdtp_motu *p = s->protocol;
	अचिन्हित पूर्णांक channels = p->pcm_chunks;
	काष्ठा snd_pcm_runसमय *runसमय = pcm->runसमय;
	अचिन्हित पूर्णांक pcm_buffer_poपूर्णांकer;
	पूर्णांक reमुख्यing_frames;
	u8 *byte;
	u32 *dst;
	पूर्णांक i, c;

	pcm_buffer_poपूर्णांकer = s->pcm_buffer_poपूर्णांकer + pcm_frames;
	pcm_buffer_poपूर्णांकer %= runसमय->buffer_size;

	dst = (व्योम *)runसमय->dma_area +
				frames_to_bytes(runसमय, pcm_buffer_poपूर्णांकer);
	reमुख्यing_frames = runसमय->buffer_size - pcm_buffer_poपूर्णांकer;

	क्रम (i = 0; i < data_blocks; ++i) अणु
		byte = (u8 *)buffer + p->pcm_byte_offset;

		क्रम (c = 0; c < channels; ++c) अणु
			*dst = (byte[0] << 24) |
			       (byte[1] << 16) |
			       (byte[2] << 8);
			byte += 3;
			dst++;
		पूर्ण
		buffer += s->data_block_quadlets;
		अगर (--reमुख्यing_frames == 0)
			dst = (व्योम *)runसमय->dma_area;
	पूर्ण
पूर्ण

अटल व्योम ग_लिखो_pcm_s32(काष्ठा amdtp_stream *s, काष्ठा snd_pcm_substream *pcm,
			  __be32 *buffer, अचिन्हित पूर्णांक data_blocks,
			  अचिन्हित पूर्णांक pcm_frames)
अणु
	काष्ठा amdtp_motu *p = s->protocol;
	अचिन्हित पूर्णांक channels = p->pcm_chunks;
	काष्ठा snd_pcm_runसमय *runसमय = pcm->runसमय;
	अचिन्हित पूर्णांक pcm_buffer_poपूर्णांकer;
	पूर्णांक reमुख्यing_frames;
	u8 *byte;
	स्थिर u32 *src;
	पूर्णांक i, c;

	pcm_buffer_poपूर्णांकer = s->pcm_buffer_poपूर्णांकer + pcm_frames;
	pcm_buffer_poपूर्णांकer %= runसमय->buffer_size;

	src = (व्योम *)runसमय->dma_area +
				frames_to_bytes(runसमय, pcm_buffer_poपूर्णांकer);
	reमुख्यing_frames = runसमय->buffer_size - pcm_buffer_poपूर्णांकer;

	क्रम (i = 0; i < data_blocks; ++i) अणु
		byte = (u8 *)buffer + p->pcm_byte_offset;

		क्रम (c = 0; c < channels; ++c) अणु
			byte[0] = (*src >> 24) & 0xff;
			byte[1] = (*src >> 16) & 0xff;
			byte[2] = (*src >>  8) & 0xff;
			byte += 3;
			src++;
		पूर्ण

		buffer += s->data_block_quadlets;
		अगर (--reमुख्यing_frames == 0)
			src = (व्योम *)runसमय->dma_area;
	पूर्ण
पूर्ण

अटल व्योम ग_लिखो_pcm_silence(काष्ठा amdtp_stream *s, __be32 *buffer,
			      अचिन्हित पूर्णांक data_blocks)
अणु
	काष्ठा amdtp_motu *p = s->protocol;
	अचिन्हित पूर्णांक channels, i, c;
	u8 *byte;

	channels = p->pcm_chunks;

	क्रम (i = 0; i < data_blocks; ++i) अणु
		byte = (u8 *)buffer + p->pcm_byte_offset;

		क्रम (c = 0; c < channels; ++c) अणु
			byte[0] = 0;
			byte[1] = 0;
			byte[2] = 0;
			byte += 3;
		पूर्ण

		buffer += s->data_block_quadlets;
	पूर्ण
पूर्ण

पूर्णांक amdtp_motu_add_pcm_hw_स्थिरraपूर्णांकs(काष्ठा amdtp_stream *s,
				      काष्ठा snd_pcm_runसमय *runसमय)
अणु
	पूर्णांक err;

	/* TODO: how to set an स्थिरraपूर्णांक क्रम exactly 24bit PCM sample? */
	err = snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);
	अगर (err < 0)
		वापस err;

	वापस amdtp_stream_add_pcm_hw_स्थिरraपूर्णांकs(s, runसमय);
पूर्ण

व्योम amdtp_motu_midi_trigger(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक port,
			     काष्ठा snd_rawmidi_substream *midi)
अणु
	काष्ठा amdtp_motu *p = s->protocol;

	अगर (port < p->midi_ports)
		WRITE_ONCE(p->midi, midi);
पूर्ण

अटल व्योम ग_लिखो_midi_messages(काष्ठा amdtp_stream *s, __be32 *buffer,
				अचिन्हित पूर्णांक data_blocks)
अणु
	काष्ठा amdtp_motu *p = s->protocol;
	काष्ठा snd_rawmidi_substream *midi = READ_ONCE(p->midi);
	u8 *b;
	पूर्णांक i;

	क्रम (i = 0; i < data_blocks; i++) अणु
		b = (u8 *)buffer;

		अगर (midi && p->midi_db_count == 0 &&
		    snd_rawmidi_transmit(midi, b + p->midi_byte_offset, 1) == 1) अणु
			b[p->midi_flag_offset] = 0x01;
		पूर्ण अन्यथा अणु
			b[p->midi_byte_offset] = 0x00;
			b[p->midi_flag_offset] = 0x00;
		पूर्ण

		buffer += s->data_block_quadlets;

		अगर (--p->midi_db_count < 0)
			p->midi_db_count = p->midi_db_पूर्णांकerval;
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_midi_messages(काष्ठा amdtp_stream *s, __be32 *buffer,
			       अचिन्हित पूर्णांक data_blocks)
अणु
	काष्ठा amdtp_motu *p = s->protocol;
	काष्ठा snd_rawmidi_substream *midi;
	u8 *b;
	पूर्णांक i;

	क्रम (i = 0; i < data_blocks; i++) अणु
		b = (u8 *)buffer;
		midi = READ_ONCE(p->midi);

		अगर (midi && (b[p->midi_flag_offset] & 0x01))
			snd_rawmidi_receive(midi, b + p->midi_byte_offset, 1);

		buffer += s->data_block_quadlets;
	पूर्ण
पूर्ण

/* For tracepoपूर्णांकs. */
अटल व्योम __maybe_unused copy_sph(u32 *frames, __be32 *buffer,
				    अचिन्हित पूर्णांक data_blocks,
				    अचिन्हित पूर्णांक data_block_quadlets)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < data_blocks; ++i) अणु
		*frames = be32_to_cpu(*buffer);
		buffer += data_block_quadlets;
		frames++;
	पूर्ण
पूर्ण

/* For tracepoपूर्णांकs. */
अटल व्योम __maybe_unused copy_message(u64 *frames, __be32 *buffer,
					अचिन्हित पूर्णांक data_blocks,
					अचिन्हित पूर्णांक data_block_quadlets)
अणु
	अचिन्हित पूर्णांक i;

	/* This is just क्रम v2/v3 protocol. */
	क्रम (i = 0; i < data_blocks; ++i) अणु
		*frames = (be32_to_cpu(buffer[1]) << 16) |
			  (be32_to_cpu(buffer[2]) >> 16);
		buffer += data_block_quadlets;
		frames++;
	पूर्ण
पूर्ण

अटल व्योम probe_tracepoपूर्णांकs_events(काष्ठा amdtp_stream *s,
				     स्थिर काष्ठा pkt_desc *descs,
				     अचिन्हित पूर्णांक packets)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < packets; ++i) अणु
		स्थिर काष्ठा pkt_desc *desc = descs + i;
		__be32 *buf = desc->ctx_payload;
		अचिन्हित पूर्णांक data_blocks = desc->data_blocks;

		trace_data_block_sph(s, data_blocks, buf);
		trace_data_block_message(s, data_blocks, buf);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक process_ir_ctx_payloads(काष्ठा amdtp_stream *s,
					    स्थिर काष्ठा pkt_desc *descs,
					    अचिन्हित पूर्णांक packets,
					    काष्ठा snd_pcm_substream *pcm)
अणु
	काष्ठा amdtp_motu *p = s->protocol;
	अचिन्हित पूर्णांक pcm_frames = 0;
	पूर्णांक i;

	// For data block processing.
	क्रम (i = 0; i < packets; ++i) अणु
		स्थिर काष्ठा pkt_desc *desc = descs + i;
		__be32 *buf = desc->ctx_payload;
		अचिन्हित पूर्णांक data_blocks = desc->data_blocks;

		अगर (pcm) अणु
			पढ़ो_pcm_s32(s, pcm, buf, data_blocks, pcm_frames);
			pcm_frames += data_blocks;
		पूर्ण

		अगर (p->midi_ports)
			पढ़ो_midi_messages(s, buf, data_blocks);
	पूर्ण

	// For tracepoपूर्णांकs.
	अगर (trace_data_block_sph_enabled() ||
	    trace_data_block_message_enabled())
		probe_tracepoपूर्णांकs_events(s, descs, packets);

	वापस pcm_frames;
पूर्ण

अटल अंतरभूत व्योम compute_next_elapse_from_start(काष्ठा amdtp_motu *p)
अणु
	p->next_accumulated += p->reमुख्यder_ticks_per_event;
	अगर (p->next_accumulated >= 441) अणु
		p->next_accumulated -= 441;
		p->next_ticks++;
	पूर्ण

	p->next_ticks += p->quotient_ticks_per_event;
	अगर (p->next_ticks >= 3072) अणु
		p->next_ticks -= 3072;
		p->next_cycles++;
	पूर्ण

	अगर (p->next_cycles >= 8000) अणु
		p->next_cycles -= 8000;
		p->next_seconds++;
	पूर्ण

	अगर (p->next_seconds >= 128)
		p->next_seconds -= 128;
पूर्ण

अटल व्योम ग_लिखो_sph(काष्ठा amdtp_stream *s, __be32 *buffer,
		      अचिन्हित पूर्णांक data_blocks)
अणु
	काष्ठा amdtp_motu *p = s->protocol;
	अचिन्हित पूर्णांक next_cycles;
	अचिन्हित पूर्णांक i;
	u32 sph;

	क्रम (i = 0; i < data_blocks; i++) अणु
		next_cycles = (s->start_cycle + p->next_cycles) % 8000;
		sph = ((next_cycles << 12) | p->next_ticks) & 0x01ffffff;
		*buffer = cpu_to_be32(sph);

		compute_next_elapse_from_start(p);

		buffer += s->data_block_quadlets;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक process_it_ctx_payloads(काष्ठा amdtp_stream *s,
					    स्थिर काष्ठा pkt_desc *descs,
					    अचिन्हित पूर्णांक packets,
					    काष्ठा snd_pcm_substream *pcm)
अणु
	काष्ठा amdtp_motu *p = s->protocol;
	अचिन्हित पूर्णांक pcm_frames = 0;
	पूर्णांक i;

	// For data block processing.
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

		अगर (p->midi_ports)
			ग_लिखो_midi_messages(s, buf, data_blocks);

		// TODO: how to पूर्णांकeract control messages between userspace?

		ग_लिखो_sph(s, buf, data_blocks);
	पूर्ण

	// For tracepoपूर्णांकs.
	अगर (trace_data_block_sph_enabled() ||
	    trace_data_block_message_enabled())
		probe_tracepoपूर्णांकs_events(s, descs, packets);

	वापस pcm_frames;
पूर्ण

पूर्णांक amdtp_motu_init(काष्ठा amdtp_stream *s, काष्ठा fw_unit *unit,
		    क्रमागत amdtp_stream_direction dir,
		    स्थिर काष्ठा snd_motu_spec *spec)
अणु
	amdtp_stream_process_ctx_payloads_t process_ctx_payloads;
	पूर्णांक fmt = CIP_FMT_MOTU;
	पूर्णांक flags = CIP_BLOCKING;
	पूर्णांक err;

	अगर (dir == AMDTP_IN_STREAM) अणु
		process_ctx_payloads = process_ir_ctx_payloads;

		/*
		 * Units of version 3 transmits packets with invalid CIP header
		 * against IEC 61883-1.
		 */
		अगर (spec->protocol_version == SND_MOTU_PROTOCOL_V3) अणु
			flags |= CIP_WRONG_DBS |
				 CIP_SKIP_DBC_ZERO_CHECK |
				 CIP_HEADER_WITHOUT_EOH;
			fmt = CIP_FMT_MOTU_TX_V3;
		पूर्ण

		अगर (spec == &snd_motu_spec_8pre ||
		    spec == &snd_motu_spec_ultralite) अणु
			// 8pre has some quirks.
			flags |= CIP_WRONG_DBS |
				 CIP_SKIP_DBC_ZERO_CHECK;
		पूर्ण
	पूर्ण अन्यथा अणु
		process_ctx_payloads = process_it_ctx_payloads;
		flags |= CIP_DBC_IS_END_EVENT;
	पूर्ण

	err = amdtp_stream_init(s, unit, dir, flags, fmt, process_ctx_payloads,
				माप(काष्ठा amdtp_motu));
	अगर (err < 0)
		वापस err;

	s->sph = 1;

	अगर (dir == AMDTP_OUT_STREAM) अणु
		// Use fixed value क्रम FDF field.
		s->ctx_data.rx.fdf = MOTU_FDF_AM824;
		// Not used.
		s->ctx_data.rx.syt_override = 0xffff;
	पूर्ण

	वापस 0;
पूर्ण
