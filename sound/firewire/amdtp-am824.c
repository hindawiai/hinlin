<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AM824 क्रमmat in Audio and Music Data Transmission Protocol (IEC 61883-6)
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 * Copyright (c) 2015 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#समावेश <linux/slab.h>

#समावेश "amdtp-am824.h"

#घोषणा CIP_FMT_AM		0x10

/* "Clock-based rate control mode" is just supported. */
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

काष्ठा amdtp_am824 अणु
	काष्ठा snd_rawmidi_substream *midi[AM824_MAX_CHANNELS_FOR_MIDI * 8];
	पूर्णांक midi_fअगरo_limit;
	पूर्णांक midi_fअगरo_used[AM824_MAX_CHANNELS_FOR_MIDI * 8];
	अचिन्हित पूर्णांक pcm_channels;
	अचिन्हित पूर्णांक midi_ports;

	u8 pcm_positions[AM824_MAX_CHANNELS_FOR_PCM];
	u8 midi_position;

	अचिन्हित पूर्णांक frame_multiplier;
पूर्ण;

/**
 * amdtp_am824_set_parameters - set stream parameters
 * @s: the AMDTP stream to configure
 * @rate: the sample rate
 * @pcm_channels: the number of PCM samples in each data block, to be encoded
 *                as AM824 multi-bit linear audio
 * @midi_ports: the number of MIDI ports (i.e., MPX-MIDI Data Channels)
 * @द्विगुन_pcm_frames: one data block transfers two PCM frames
 *
 * The parameters must be set beक्रमe the stream is started, and must not be
 * changed जबतक the stream is running.
 */
पूर्णांक amdtp_am824_set_parameters(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक rate,
			       अचिन्हित पूर्णांक pcm_channels,
			       अचिन्हित पूर्णांक midi_ports,
			       bool द्विगुन_pcm_frames)
अणु
	काष्ठा amdtp_am824 *p = s->protocol;
	अचिन्हित पूर्णांक midi_channels;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (amdtp_stream_running(s))
		वापस -EINVAL;

	अगर (pcm_channels > AM824_MAX_CHANNELS_FOR_PCM)
		वापस -EINVAL;

	midi_channels = DIV_ROUND_UP(midi_ports, 8);
	अगर (midi_channels > AM824_MAX_CHANNELS_FOR_MIDI)
		वापस -EINVAL;

	अगर (WARN_ON(amdtp_stream_running(s)) ||
	    WARN_ON(pcm_channels > AM824_MAX_CHANNELS_FOR_PCM) ||
	    WARN_ON(midi_channels > AM824_MAX_CHANNELS_FOR_MIDI))
		वापस -EINVAL;

	err = amdtp_stream_set_parameters(s, rate,
					  pcm_channels + midi_channels);
	अगर (err < 0)
		वापस err;

	अगर (s->direction == AMDTP_OUT_STREAM)
		s->ctx_data.rx.fdf = AMDTP_FDF_AM824 | s->sfc;

	p->pcm_channels = pcm_channels;
	p->midi_ports = midi_ports;

	/*
	 * In IEC 61883-6, one data block represents one event. In ALSA, one
	 * event equals to one PCM frame. But Dice has a quirk at higher
	 * sampling rate to transfer two PCM frames in one data block.
	 */
	अगर (द्विगुन_pcm_frames)
		p->frame_multiplier = 2;
	अन्यथा
		p->frame_multiplier = 1;

	/* init the position map क्रम PCM and MIDI channels */
	क्रम (i = 0; i < pcm_channels; i++)
		p->pcm_positions[i] = i;
	p->midi_position = p->pcm_channels;

	/*
	 * We करो not know the actual MIDI FIFO size of most devices.  Just
	 * assume two bytes, i.e., one byte can be received over the bus जबतक
	 * the previous one is transmitted over MIDI.
	 * (The value here is adjusted क्रम midi_ratelimit_per_packet().)
	 */
	p->midi_fअगरo_limit = rate - MIDI_BYTES_PER_SECOND * s->syt_पूर्णांकerval + 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(amdtp_am824_set_parameters);

/**
 * amdtp_am824_set_pcm_position - set an index of data channel क्रम a channel
 *				  of PCM frame
 * @s: the AMDTP stream
 * @index: the index of data channel in an data block
 * @position: the channel of PCM frame
 */
व्योम amdtp_am824_set_pcm_position(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक index,
				 अचिन्हित पूर्णांक position)
अणु
	काष्ठा amdtp_am824 *p = s->protocol;

	अगर (index < p->pcm_channels)
		p->pcm_positions[index] = position;
पूर्ण
EXPORT_SYMBOL_GPL(amdtp_am824_set_pcm_position);

/**
 * amdtp_am824_set_midi_position - set a index of data channel क्रम MIDI
 *				   conक्रमmant data channel
 * @s: the AMDTP stream
 * @position: the index of data channel in an data block
 */
व्योम amdtp_am824_set_midi_position(काष्ठा amdtp_stream *s,
				   अचिन्हित पूर्णांक position)
अणु
	काष्ठा amdtp_am824 *p = s->protocol;

	p->midi_position = position;
पूर्ण
EXPORT_SYMBOL_GPL(amdtp_am824_set_midi_position);

अटल व्योम ग_लिखो_pcm_s32(काष्ठा amdtp_stream *s, काष्ठा snd_pcm_substream *pcm,
			  __be32 *buffer, अचिन्हित पूर्णांक frames,
			  अचिन्हित पूर्णांक pcm_frames)
अणु
	काष्ठा amdtp_am824 *p = s->protocol;
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

	क्रम (i = 0; i < frames; ++i) अणु
		क्रम (c = 0; c < channels; ++c) अणु
			buffer[p->pcm_positions[c]] =
					cpu_to_be32((*src >> 8) | 0x40000000);
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
	काष्ठा amdtp_am824 *p = s->protocol;
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

	क्रम (i = 0; i < frames; ++i) अणु
		क्रम (c = 0; c < channels; ++c) अणु
			*dst = be32_to_cpu(buffer[p->pcm_positions[c]]) << 8;
			dst++;
		पूर्ण
		buffer += s->data_block_quadlets;
		अगर (--reमुख्यing_frames == 0)
			dst = (व्योम *)runसमय->dma_area;
	पूर्ण
पूर्ण

अटल व्योम ग_लिखो_pcm_silence(काष्ठा amdtp_stream *s,
			      __be32 *buffer, अचिन्हित पूर्णांक frames)
अणु
	काष्ठा amdtp_am824 *p = s->protocol;
	अचिन्हित पूर्णांक i, c, channels = p->pcm_channels;

	क्रम (i = 0; i < frames; ++i) अणु
		क्रम (c = 0; c < channels; ++c)
			buffer[p->pcm_positions[c]] = cpu_to_be32(0x40000000);
		buffer += s->data_block_quadlets;
	पूर्ण
पूर्ण

/**
 * amdtp_am824_add_pcm_hw_स्थिरraपूर्णांकs - add hw स्थिरraपूर्णांकs क्रम PCM substream
 * @s:		the AMDTP stream क्रम AM824 data block, must be initialized.
 * @runसमय:	the PCM substream runसमय
 *
 */
पूर्णांक amdtp_am824_add_pcm_hw_स्थिरraपूर्णांकs(काष्ठा amdtp_stream *s,
				       काष्ठा snd_pcm_runसमय *runसमय)
अणु
	पूर्णांक err;

	err = amdtp_stream_add_pcm_hw_स्थिरraपूर्णांकs(s, runसमय);
	अगर (err < 0)
		वापस err;

	/* AM824 in IEC 61883-6 can deliver 24bit data. */
	वापस snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);
पूर्ण
EXPORT_SYMBOL_GPL(amdtp_am824_add_pcm_hw_स्थिरraपूर्णांकs);

/**
 * amdtp_am824_midi_trigger - start/stop playback/capture with a MIDI device
 * @s: the AMDTP stream
 * @port: index of MIDI port
 * @midi: the MIDI device to be started, or %शून्य to stop the current device
 *
 * Call this function on a running isochronous stream to enable the actual
 * transmission of MIDI data.  This function should be called from the MIDI
 * device's .trigger callback.
 */
व्योम amdtp_am824_midi_trigger(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक port,
			      काष्ठा snd_rawmidi_substream *midi)
अणु
	काष्ठा amdtp_am824 *p = s->protocol;

	अगर (port < p->midi_ports)
		WRITE_ONCE(p->midi[port], midi);
पूर्ण
EXPORT_SYMBOL_GPL(amdtp_am824_midi_trigger);

/*
 * To aव्योम sending MIDI bytes at too high a rate, assume that the receiving
 * device has a FIFO, and track how much it is filled.  This values increases
 * by one whenever we send one byte in a packet, but the FIFO empties at
 * a स्थिरant rate independent of our packet rate.  One packet has syt_पूर्णांकerval
 * samples, so the number of bytes that empty out of the FIFO, per packet(!),
 * is MIDI_BYTES_PER_SECOND * syt_पूर्णांकerval / sample_rate.  To aव्योम storing
 * fractional values, the values in midi_fअगरo_used[] are measured in bytes
 * multiplied by the sample rate.
 */
अटल bool midi_ratelimit_per_packet(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक port)
अणु
	काष्ठा amdtp_am824 *p = s->protocol;
	पूर्णांक used;

	used = p->midi_fअगरo_used[port];
	अगर (used == 0) /* common लघुcut */
		वापस true;

	used -= MIDI_BYTES_PER_SECOND * s->syt_पूर्णांकerval;
	used = max(used, 0);
	p->midi_fअगरo_used[port] = used;

	वापस used < p->midi_fअगरo_limit;
पूर्ण

अटल व्योम midi_rate_use_one_byte(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक port)
अणु
	काष्ठा amdtp_am824 *p = s->protocol;

	p->midi_fअगरo_used[port] += amdtp_rate_table[s->sfc];
पूर्ण

अटल व्योम ग_लिखो_midi_messages(काष्ठा amdtp_stream *s, __be32 *buffer,
			अचिन्हित पूर्णांक frames, अचिन्हित पूर्णांक data_block_counter)
अणु
	काष्ठा amdtp_am824 *p = s->protocol;
	अचिन्हित पूर्णांक f, port;
	u8 *b;

	क्रम (f = 0; f < frames; f++) अणु
		b = (u8 *)&buffer[p->midi_position];

		port = (data_block_counter + f) % 8;
		अगर (f < MAX_MIDI_RX_BLOCKS &&
		    midi_ratelimit_per_packet(s, port) &&
		    p->midi[port] != शून्य &&
		    snd_rawmidi_transmit(p->midi[port], &b[1], 1) == 1) अणु
			midi_rate_use_one_byte(s, port);
			b[0] = 0x81;
		पूर्ण अन्यथा अणु
			b[0] = 0x80;
			b[1] = 0;
		पूर्ण
		b[2] = 0;
		b[3] = 0;

		buffer += s->data_block_quadlets;
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_midi_messages(काष्ठा amdtp_stream *s, __be32 *buffer,
			अचिन्हित पूर्णांक frames, अचिन्हित पूर्णांक data_block_counter)
अणु
	काष्ठा amdtp_am824 *p = s->protocol;
	पूर्णांक len;
	u8 *b;
	पूर्णांक f;

	क्रम (f = 0; f < frames; f++) अणु
		अचिन्हित पूर्णांक port = f;

		अगर (!(s->flags & CIP_UNALIGHED_DBC))
			port += data_block_counter;
		port %= 8;
		b = (u8 *)&buffer[p->midi_position];

		len = b[0] - 0x80;
		अगर ((1 <= len) &&  (len <= 3) && (p->midi[port]))
			snd_rawmidi_receive(p->midi[port], b + 1, len);

		buffer += s->data_block_quadlets;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक process_it_ctx_payloads(काष्ठा amdtp_stream *s,
					    स्थिर काष्ठा pkt_desc *descs,
					    अचिन्हित पूर्णांक packets,
					    काष्ठा snd_pcm_substream *pcm)
अणु
	काष्ठा amdtp_am824 *p = s->protocol;
	अचिन्हित पूर्णांक pcm_frames = 0;
	पूर्णांक i;

	क्रम (i = 0; i < packets; ++i) अणु
		स्थिर काष्ठा pkt_desc *desc = descs + i;
		__be32 *buf = desc->ctx_payload;
		अचिन्हित पूर्णांक data_blocks = desc->data_blocks;

		अगर (pcm) अणु
			ग_लिखो_pcm_s32(s, pcm, buf, data_blocks, pcm_frames);
			pcm_frames += data_blocks * p->frame_multiplier;
		पूर्ण अन्यथा अणु
			ग_लिखो_pcm_silence(s, buf, data_blocks);
		पूर्ण

		अगर (p->midi_ports) अणु
			ग_लिखो_midi_messages(s, buf, data_blocks,
					    desc->data_block_counter);
		पूर्ण
	पूर्ण

	वापस pcm_frames;
पूर्ण

अटल अचिन्हित पूर्णांक process_ir_ctx_payloads(काष्ठा amdtp_stream *s,
					    स्थिर काष्ठा pkt_desc *descs,
					    अचिन्हित पूर्णांक packets,
					    काष्ठा snd_pcm_substream *pcm)
अणु
	काष्ठा amdtp_am824 *p = s->protocol;
	अचिन्हित पूर्णांक pcm_frames = 0;
	पूर्णांक i;

	क्रम (i = 0; i < packets; ++i) अणु
		स्थिर काष्ठा pkt_desc *desc = descs + i;
		__be32 *buf = desc->ctx_payload;
		अचिन्हित पूर्णांक data_blocks = desc->data_blocks;

		अगर (pcm) अणु
			पढ़ो_pcm_s32(s, pcm, buf, data_blocks, pcm_frames);
			pcm_frames += data_blocks * p->frame_multiplier;
		पूर्ण

		अगर (p->midi_ports) अणु
			पढ़ो_midi_messages(s, buf, data_blocks,
					   desc->data_block_counter);
		पूर्ण
	पूर्ण

	वापस pcm_frames;
पूर्ण

/**
 * amdtp_am824_init - initialize an AMDTP stream काष्ठाure to handle AM824
 *		      data block
 * @s: the AMDTP stream to initialize
 * @unit: the target of the stream
 * @dir: the direction of stream
 * @flags: the packet transmission method to use
 */
पूर्णांक amdtp_am824_init(काष्ठा amdtp_stream *s, काष्ठा fw_unit *unit,
		     क्रमागत amdtp_stream_direction dir, क्रमागत cip_flags flags)
अणु
	amdtp_stream_process_ctx_payloads_t process_ctx_payloads;

	अगर (dir == AMDTP_IN_STREAM)
		process_ctx_payloads = process_ir_ctx_payloads;
	अन्यथा
		process_ctx_payloads = process_it_ctx_payloads;

	वापस amdtp_stream_init(s, unit, dir, flags, CIP_FMT_AM,
			process_ctx_payloads, माप(काष्ठा amdtp_am824));
पूर्ण
EXPORT_SYMBOL_GPL(amdtp_am824_init);
