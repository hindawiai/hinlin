<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * amdtp-tascam.c - a part of driver क्रम TASCAM FireWire series
 *
 * Copyright (c) 2015 Takashi Sakamoto
 */

#समावेश <sound/pcm.h>
#समावेश "tascam.h"

#घोषणा AMDTP_FMT_TSCM_TX	0x1e
#घोषणा AMDTP_FMT_TSCM_RX	0x3e

काष्ठा amdtp_tscm अणु
	अचिन्हित पूर्णांक pcm_channels;
पूर्ण;

पूर्णांक amdtp_tscm_set_parameters(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक rate)
अणु
	काष्ठा amdtp_tscm *p = s->protocol;
	अचिन्हित पूर्णांक data_channels;

	अगर (amdtp_stream_running(s))
		वापस -EBUSY;

	data_channels = p->pcm_channels;

	/* Packets in in-stream have extra 2 data channels. */
	अगर (s->direction == AMDTP_IN_STREAM)
		data_channels += 2;

	वापस amdtp_stream_set_parameters(s, rate, data_channels);
पूर्ण

अटल व्योम ग_लिखो_pcm_s32(काष्ठा amdtp_stream *s, काष्ठा snd_pcm_substream *pcm,
			  __be32 *buffer, अचिन्हित पूर्णांक frames,
			  अचिन्हित पूर्णांक pcm_frames)
अणु
	काष्ठा amdtp_tscm *p = s->protocol;
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
			buffer[c] = cpu_to_be32(*src);
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
	काष्ठा amdtp_tscm *p = s->protocol;
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

	/* The first data channel is क्रम event counter. */
	buffer += 1;

	क्रम (i = 0; i < frames; ++i) अणु
		क्रम (c = 0; c < channels; ++c) अणु
			*dst = be32_to_cpu(buffer[c]);
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
	काष्ठा amdtp_tscm *p = s->protocol;
	अचिन्हित पूर्णांक channels, i, c;

	channels = p->pcm_channels;

	क्रम (i = 0; i < data_blocks; ++i) अणु
		क्रम (c = 0; c < channels; ++c)
			buffer[c] = 0x00000000;
		buffer += s->data_block_quadlets;
	पूर्ण
पूर्ण

पूर्णांक amdtp_tscm_add_pcm_hw_स्थिरraपूर्णांकs(काष्ठा amdtp_stream *s,
				      काष्ठा snd_pcm_runसमय *runसमय)
अणु
	पूर्णांक err;

	/*
	 * Our implementation allows this protocol to deliver 24 bit sample in
	 * 32bit data channel.
	 */
	err = snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);
	अगर (err < 0)
		वापस err;

	वापस amdtp_stream_add_pcm_hw_स्थिरraपूर्णांकs(s, runसमय);
पूर्ण

अटल व्योम पढ़ो_status_messages(काष्ठा amdtp_stream *s,
				 __be32 *buffer, अचिन्हित पूर्णांक data_blocks)
अणु
	काष्ठा snd_tscm *tscm = container_of(s, काष्ठा snd_tscm, tx_stream);
	bool used = READ_ONCE(tscm->hwdep->used);
	पूर्णांक i;

	क्रम (i = 0; i < data_blocks; i++) अणु
		अचिन्हित पूर्णांक index;
		__be32 beक्रमe;
		__be32 after;

		index = be32_to_cpu(buffer[0]) % SNDRV_FIREWIRE_TASCAM_STATE_COUNT;
		beक्रमe = tscm->state[index];
		after = buffer[s->data_block_quadlets - 1];

		अगर (used && index > 4 && index < 16) अणु
			__be32 mask;

			अगर (index == 5)
				mask = cpu_to_be32(~0x0000ffff);
			अन्यथा अगर (index == 6)
				mask = cpu_to_be32(~0x0000ffff);
			अन्यथा अगर (index == 8)
				mask = cpu_to_be32(~0x000f0f00);
			अन्यथा
				mask = cpu_to_be32(~0x00000000);

			अगर ((beक्रमe ^ after) & mask) अणु
				काष्ठा snd_firewire_tascam_change *entry =
						&tscm->queue[tscm->push_pos];
				अचिन्हित दीर्घ flag;

				spin_lock_irqsave(&tscm->lock, flag);
				entry->index = index;
				entry->beक्रमe = beक्रमe;
				entry->after = after;
				अगर (++tscm->push_pos >= SND_TSCM_QUEUE_COUNT)
					tscm->push_pos = 0;
				spin_unlock_irqrestore(&tscm->lock, flag);

				wake_up(&tscm->hwdep_रुको);
			पूर्ण
		पूर्ण

		tscm->state[index] = after;
		buffer += s->data_block_quadlets;
	पूर्ण
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

		पढ़ो_status_messages(s, buf, data_blocks);
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
	पूर्ण

	वापस pcm_frames;
पूर्ण

पूर्णांक amdtp_tscm_init(काष्ठा amdtp_stream *s, काष्ठा fw_unit *unit,
		    क्रमागत amdtp_stream_direction dir, अचिन्हित पूर्णांक pcm_channels)
अणु
	amdtp_stream_process_ctx_payloads_t process_ctx_payloads;
	काष्ठा amdtp_tscm *p;
	अचिन्हित पूर्णांक fmt;
	पूर्णांक err;

	अगर (dir == AMDTP_IN_STREAM) अणु
		fmt = AMDTP_FMT_TSCM_TX;
		process_ctx_payloads = process_ir_ctx_payloads;
	पूर्ण अन्यथा अणु
		fmt = AMDTP_FMT_TSCM_RX;
		process_ctx_payloads = process_it_ctx_payloads;
	पूर्ण

	err = amdtp_stream_init(s, unit, dir,
			CIP_NONBLOCKING | CIP_SKIP_DBC_ZERO_CHECK, fmt,
			process_ctx_payloads, माप(काष्ठा amdtp_tscm));
	अगर (err < 0)
		वापस 0;

	अगर (dir == AMDTP_OUT_STREAM) अणु
		// Use fixed value क्रम FDF field.
		s->ctx_data.rx.fdf = 0x00;
		// Not used.
		s->ctx_data.rx.syt_override = 0x0000;
	पूर्ण

	/* This protocol uses fixed number of data channels क्रम PCM samples. */
	p = s->protocol;
	p->pcm_channels = pcm_channels;

	वापस 0;
पूर्ण
