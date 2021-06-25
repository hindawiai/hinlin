<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * amdtp-ff.c - a part of driver क्रम RME Fireface series
 *
 * Copyright (c) 2015-2017 Takashi Sakamoto
 */

#समावेश <sound/pcm.h>
#समावेश "ff.h"

काष्ठा amdtp_ff अणु
	अचिन्हित पूर्णांक pcm_channels;
पूर्ण;

पूर्णांक amdtp_ff_set_parameters(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक rate,
			    अचिन्हित पूर्णांक pcm_channels)
अणु
	काष्ठा amdtp_ff *p = s->protocol;
	अचिन्हित पूर्णांक data_channels;

	अगर (amdtp_stream_running(s))
		वापस -EBUSY;

	p->pcm_channels = pcm_channels;
	data_channels = pcm_channels;

	वापस amdtp_stream_set_parameters(s, rate, data_channels);
पूर्ण

अटल व्योम ग_लिखो_pcm_s32(काष्ठा amdtp_stream *s, काष्ठा snd_pcm_substream *pcm,
			  __le32 *buffer, अचिन्हित पूर्णांक frames,
			  अचिन्हित पूर्णांक pcm_frames)
अणु
	काष्ठा amdtp_ff *p = s->protocol;
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
			buffer[c] = cpu_to_le32(*src);
			src++;
		पूर्ण
		buffer += s->data_block_quadlets;
		अगर (--reमुख्यing_frames == 0)
			src = (व्योम *)runसमय->dma_area;
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_pcm_s32(काष्ठा amdtp_stream *s, काष्ठा snd_pcm_substream *pcm,
			 __le32 *buffer, अचिन्हित पूर्णांक frames,
			 अचिन्हित पूर्णांक pcm_frames)
अणु
	काष्ठा amdtp_ff *p = s->protocol;
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
			*dst = le32_to_cpu(buffer[c]) & 0xffffff00;
			dst++;
		पूर्ण
		buffer += s->data_block_quadlets;
		अगर (--reमुख्यing_frames == 0)
			dst = (व्योम *)runसमय->dma_area;
	पूर्ण
पूर्ण

अटल व्योम ग_लिखो_pcm_silence(काष्ठा amdtp_stream *s,
			      __le32 *buffer, अचिन्हित पूर्णांक frames)
अणु
	काष्ठा amdtp_ff *p = s->protocol;
	अचिन्हित पूर्णांक i, c, channels = p->pcm_channels;

	क्रम (i = 0; i < frames; ++i) अणु
		क्रम (c = 0; c < channels; ++c)
			buffer[c] = cpu_to_le32(0x00000000);
		buffer += s->data_block_quadlets;
	पूर्ण
पूर्ण

पूर्णांक amdtp_ff_add_pcm_hw_स्थिरraपूर्णांकs(काष्ठा amdtp_stream *s,
				    काष्ठा snd_pcm_runसमय *runसमय)
अणु
	पूर्णांक err;

	err = snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);
	अगर (err < 0)
		वापस err;

	वापस amdtp_stream_add_pcm_hw_स्थिरraपूर्णांकs(s, runसमय);
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
		__le32 *buf = (__le32 *)desc->ctx_payload;
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

अटल अचिन्हित पूर्णांक process_ir_ctx_payloads(काष्ठा amdtp_stream *s,
					    स्थिर काष्ठा pkt_desc *descs,
					    अचिन्हित पूर्णांक packets,
					    काष्ठा snd_pcm_substream *pcm)
अणु
	अचिन्हित पूर्णांक pcm_frames = 0;
	पूर्णांक i;

	क्रम (i = 0; i < packets; ++i) अणु
		स्थिर काष्ठा pkt_desc *desc = descs + i;
		__le32 *buf = (__le32 *)desc->ctx_payload;
		अचिन्हित पूर्णांक data_blocks = desc->data_blocks;

		अगर (pcm) अणु
			पढ़ो_pcm_s32(s, pcm, buf, data_blocks, pcm_frames);
			pcm_frames += data_blocks;
		पूर्ण
	पूर्ण

	वापस pcm_frames;
पूर्ण

पूर्णांक amdtp_ff_init(काष्ठा amdtp_stream *s, काष्ठा fw_unit *unit,
		  क्रमागत amdtp_stream_direction dir)
अणु
	amdtp_stream_process_ctx_payloads_t process_ctx_payloads;

	अगर (dir == AMDTP_IN_STREAM)
		process_ctx_payloads = process_ir_ctx_payloads;
	अन्यथा
		process_ctx_payloads = process_it_ctx_payloads;

	वापस amdtp_stream_init(s, unit, dir, CIP_NO_HEADER, 0,
				 process_ctx_payloads, माप(काष्ठा amdtp_ff));
पूर्ण
