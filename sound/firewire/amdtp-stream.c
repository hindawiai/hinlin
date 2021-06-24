<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Audio and Music Data Transmission Protocol (IEC 61883-6) streams
 * with Common Isochronous Packet (IEC 61883-1) headers
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश "amdtp-stream.h"

#घोषणा TICKS_PER_CYCLE		3072
#घोषणा CYCLES_PER_SECOND	8000
#घोषणा TICKS_PER_SECOND	(TICKS_PER_CYCLE * CYCLES_PER_SECOND)

#घोषणा OHCI_MAX_SECOND		8

/* Always support Linux tracing subप्रणाली. */
#घोषणा CREATE_TRACE_POINTS
#समावेश "amdtp-stream-trace.h"

#घोषणा TRANSFER_DELAY_TICKS	0x2e00 /* 479.17 microseconds */

/* isochronous header parameters */
#घोषणा ISO_DATA_LENGTH_SHIFT	16
#घोषणा TAG_NO_CIP_HEADER	0
#घोषणा TAG_CIP			1

/* common isochronous packet header parameters */
#घोषणा CIP_EOH_SHIFT		31
#घोषणा CIP_EOH			(1u << CIP_EOH_SHIFT)
#घोषणा CIP_EOH_MASK		0x80000000
#घोषणा CIP_SID_SHIFT		24
#घोषणा CIP_SID_MASK		0x3f000000
#घोषणा CIP_DBS_MASK		0x00ff0000
#घोषणा CIP_DBS_SHIFT		16
#घोषणा CIP_SPH_MASK		0x00000400
#घोषणा CIP_SPH_SHIFT		10
#घोषणा CIP_DBC_MASK		0x000000ff
#घोषणा CIP_FMT_SHIFT		24
#घोषणा CIP_FMT_MASK		0x3f000000
#घोषणा CIP_FDF_MASK		0x00ff0000
#घोषणा CIP_FDF_SHIFT		16
#घोषणा CIP_SYT_MASK		0x0000ffff
#घोषणा CIP_SYT_NO_INFO		0xffff

/* Audio and Music transfer protocol specअगरic parameters */
#घोषणा CIP_FMT_AM		0x10
#घोषणा AMDTP_FDF_NO_DATA	0xff

// For iso header, tstamp and 2 CIP header.
#घोषणा IR_CTX_HEADER_SIZE_CIP		16
// For iso header and tstamp.
#घोषणा IR_CTX_HEADER_SIZE_NO_CIP	8
#घोषणा HEADER_TSTAMP_MASK	0x0000ffff

#घोषणा IT_PKT_HEADER_SIZE_CIP		8 // For 2 CIP header.
#घोषणा IT_PKT_HEADER_SIZE_NO_CIP	0 // Nothing.

अटल व्योम pcm_period_work(काष्ठा work_काष्ठा *work);

/**
 * amdtp_stream_init - initialize an AMDTP stream काष्ठाure
 * @s: the AMDTP stream to initialize
 * @unit: the target of the stream
 * @dir: the direction of stream
 * @flags: the packet transmission method to use
 * @fmt: the value of fmt field in CIP header
 * @process_ctx_payloads: callback handler to process payloads of isoc context
 * @protocol_size: the size to allocate newly क्रम protocol
 */
पूर्णांक amdtp_stream_init(काष्ठा amdtp_stream *s, काष्ठा fw_unit *unit,
		      क्रमागत amdtp_stream_direction dir, क्रमागत cip_flags flags,
		      अचिन्हित पूर्णांक fmt,
		      amdtp_stream_process_ctx_payloads_t process_ctx_payloads,
		      अचिन्हित पूर्णांक protocol_size)
अणु
	अगर (process_ctx_payloads == शून्य)
		वापस -EINVAL;

	s->protocol = kzalloc(protocol_size, GFP_KERNEL);
	अगर (!s->protocol)
		वापस -ENOMEM;

	s->unit = unit;
	s->direction = dir;
	s->flags = flags;
	s->context = ERR_PTR(-1);
	mutex_init(&s->mutex);
	INIT_WORK(&s->period_work, pcm_period_work);
	s->packet_index = 0;

	init_रुकोqueue_head(&s->callback_रुको);
	s->callbacked = false;

	s->fmt = fmt;
	s->process_ctx_payloads = process_ctx_payloads;

	अगर (dir == AMDTP_OUT_STREAM)
		s->ctx_data.rx.syt_override = -1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(amdtp_stream_init);

/**
 * amdtp_stream_destroy - मुक्त stream resources
 * @s: the AMDTP stream to destroy
 */
व्योम amdtp_stream_destroy(काष्ठा amdtp_stream *s)
अणु
	/* Not initialized. */
	अगर (s->protocol == शून्य)
		वापस;

	WARN_ON(amdtp_stream_running(s));
	kमुक्त(s->protocol);
	mutex_destroy(&s->mutex);
पूर्ण
EXPORT_SYMBOL(amdtp_stream_destroy);

स्थिर अचिन्हित पूर्णांक amdtp_syt_पूर्णांकervals[CIP_SFC_COUNT] = अणु
	[CIP_SFC_32000]  =  8,
	[CIP_SFC_44100]  =  8,
	[CIP_SFC_48000]  =  8,
	[CIP_SFC_88200]  = 16,
	[CIP_SFC_96000]  = 16,
	[CIP_SFC_176400] = 32,
	[CIP_SFC_192000] = 32,
पूर्ण;
EXPORT_SYMBOL(amdtp_syt_पूर्णांकervals);

स्थिर अचिन्हित पूर्णांक amdtp_rate_table[CIP_SFC_COUNT] = अणु
	[CIP_SFC_32000]  =  32000,
	[CIP_SFC_44100]  =  44100,
	[CIP_SFC_48000]  =  48000,
	[CIP_SFC_88200]  =  88200,
	[CIP_SFC_96000]  =  96000,
	[CIP_SFC_176400] = 176400,
	[CIP_SFC_192000] = 192000,
पूर्ण;
EXPORT_SYMBOL(amdtp_rate_table);

अटल पूर्णांक apply_स्थिरraपूर्णांक_to_size(काष्ठा snd_pcm_hw_params *params,
				    काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *s = hw_param_पूर्णांकerval(params, rule->var);
	स्थिर काष्ठा snd_पूर्णांकerval *r =
		hw_param_पूर्णांकerval_c(params, SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval t = अणु0पूर्ण;
	अचिन्हित पूर्णांक step = 0;
	पूर्णांक i;

	क्रम (i = 0; i < CIP_SFC_COUNT; ++i) अणु
		अगर (snd_पूर्णांकerval_test(r, amdtp_rate_table[i]))
			step = max(step, amdtp_syt_पूर्णांकervals[i]);
	पूर्ण

	t.min = roundup(s->min, step);
	t.max = roundकरोwn(s->max, step);
	t.पूर्णांकeger = 1;

	वापस snd_पूर्णांकerval_refine(s, &t);
पूर्ण

/**
 * amdtp_stream_add_pcm_hw_स्थिरraपूर्णांकs - add hw स्थिरraपूर्णांकs क्रम PCM substream
 * @s:		the AMDTP stream, which must be initialized.
 * @runसमय:	the PCM substream runसमय
 */
पूर्णांक amdtp_stream_add_pcm_hw_स्थिरraपूर्णांकs(काष्ठा amdtp_stream *s,
					काष्ठा snd_pcm_runसमय *runसमय)
अणु
	काष्ठा snd_pcm_hardware *hw = &runसमय->hw;
	अचिन्हित पूर्णांक ctx_header_size;
	अचिन्हित पूर्णांक maximum_usec_per_period;
	पूर्णांक err;

	hw->info = SNDRV_PCM_INFO_BATCH |
		   SNDRV_PCM_INFO_BLOCK_TRANSFER |
		   SNDRV_PCM_INFO_INTERLEAVED |
		   SNDRV_PCM_INFO_JOINT_DUPLEX |
		   SNDRV_PCM_INFO_MMAP |
		   SNDRV_PCM_INFO_MMAP_VALID;

	/* SNDRV_PCM_INFO_BATCH */
	hw->periods_min = 2;
	hw->periods_max = अच_पूर्णांक_उच्च;

	/* bytes क्रम a frame */
	hw->period_bytes_min = 4 * hw->channels_max;

	/* Just to prevent from allocating much pages. */
	hw->period_bytes_max = hw->period_bytes_min * 2048;
	hw->buffer_bytes_max = hw->period_bytes_max * hw->periods_min;

	// Linux driver क्रम 1394 OHCI controller voluntarily flushes isoc
	// context when total size of accumulated context header reaches
	// PAGE_SIZE. This kicks work क्रम the isoc context and brings
	// callback in the middle of scheduled पूर्णांकerrupts.
	// Although AMDTP streams in the same करोमुख्य use the same events per
	// IRQ, use the largest size of context header between IT/IR contexts.
	// Here, use the value of context header in IR context is क्रम both
	// contexts.
	अगर (!(s->flags & CIP_NO_HEADER))
		ctx_header_size = IR_CTX_HEADER_SIZE_CIP;
	अन्यथा
		ctx_header_size = IR_CTX_HEADER_SIZE_NO_CIP;
	maximum_usec_per_period = USEC_PER_SEC * PAGE_SIZE /
				  CYCLES_PER_SECOND / ctx_header_size;

	// In IEC 61883-6, one isoc packet can transfer events up to the value
	// of syt पूर्णांकerval. This comes from the पूर्णांकerval of isoc cycle. As 1394
	// OHCI controller can generate hardware IRQ per isoc packet, the
	// पूर्णांकerval is 125 usec.
	// However, there are two ways of transmission in IEC 61883-6; blocking
	// and non-blocking modes. In blocking mode, the sequence of isoc packet
	// includes 'empty' or 'NODATA' packets which include no event. In
	// non-blocking mode, the number of events per packet is variable up to
	// the syt पूर्णांकerval.
	// Due to the above protocol design, the minimum PCM frames per
	// पूर्णांकerrupt should be द्विगुन of the value of syt पूर्णांकerval, thus it is
	// 250 usec.
	err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय,
					   SNDRV_PCM_HW_PARAM_PERIOD_TIME,
					   250, maximum_usec_per_period);
	अगर (err < 0)
		जाओ end;

	/* Non-Blocking stream has no more स्थिरraपूर्णांकs */
	अगर (!(s->flags & CIP_BLOCKING))
		जाओ end;

	/*
	 * One AMDTP packet can include some frames. In blocking mode, the
	 * number equals to SYT_INTERVAL. So the number is 8, 16 or 32,
	 * depending on its sampling rate. For accurate period पूर्णांकerrupt, it's
	 * preferrable to align period/buffer sizes to current SYT_INTERVAL.
	 */
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
				  apply_स्थिरraपूर्णांक_to_size, शून्य,
				  SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	अगर (err < 0)
		जाओ end;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
				  apply_स्थिरraपूर्णांक_to_size, शून्य,
				  SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	अगर (err < 0)
		जाओ end;
end:
	वापस err;
पूर्ण
EXPORT_SYMBOL(amdtp_stream_add_pcm_hw_स्थिरraपूर्णांकs);

/**
 * amdtp_stream_set_parameters - set stream parameters
 * @s: the AMDTP stream to configure
 * @rate: the sample rate
 * @data_block_quadlets: the size of a data block in quadlet unit
 *
 * The parameters must be set beक्रमe the stream is started, and must not be
 * changed जबतक the stream is running.
 */
पूर्णांक amdtp_stream_set_parameters(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक rate,
				अचिन्हित पूर्णांक data_block_quadlets)
अणु
	अचिन्हित पूर्णांक sfc;

	क्रम (sfc = 0; sfc < ARRAY_SIZE(amdtp_rate_table); ++sfc) अणु
		अगर (amdtp_rate_table[sfc] == rate)
			अवरोध;
	पूर्ण
	अगर (sfc == ARRAY_SIZE(amdtp_rate_table))
		वापस -EINVAL;

	s->sfc = sfc;
	s->data_block_quadlets = data_block_quadlets;
	s->syt_पूर्णांकerval = amdtp_syt_पूर्णांकervals[sfc];

	// शेष buffering in the device.
	अगर (s->direction == AMDTP_OUT_STREAM) अणु
		s->ctx_data.rx.transfer_delay =
					TRANSFER_DELAY_TICKS - TICKS_PER_CYCLE;

		अगर (s->flags & CIP_BLOCKING) अणु
			// additional buffering needed to adjust क्रम no-data
			// packets.
			s->ctx_data.rx.transfer_delay +=
				TICKS_PER_SECOND * s->syt_पूर्णांकerval / rate;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(amdtp_stream_set_parameters);

/**
 * amdtp_stream_get_max_payload - get the stream's packet size
 * @s: the AMDTP stream
 *
 * This function must not be called beक्रमe the stream has been configured
 * with amdtp_stream_set_parameters().
 */
अचिन्हित पूर्णांक amdtp_stream_get_max_payload(काष्ठा amdtp_stream *s)
अणु
	अचिन्हित पूर्णांक multiplier = 1;
	अचिन्हित पूर्णांक cip_header_size = 0;

	अगर (s->flags & CIP_JUMBO_PAYLOAD)
		multiplier = 5;
	अगर (!(s->flags & CIP_NO_HEADER))
		cip_header_size = माप(__be32) * 2;

	वापस cip_header_size +
		s->syt_पूर्णांकerval * s->data_block_quadlets * माप(__be32) * multiplier;
पूर्ण
EXPORT_SYMBOL(amdtp_stream_get_max_payload);

/**
 * amdtp_stream_pcm_prepare - prepare PCM device क्रम running
 * @s: the AMDTP stream
 *
 * This function should be called from the PCM device's .prepare callback.
 */
व्योम amdtp_stream_pcm_prepare(काष्ठा amdtp_stream *s)
अणु
	cancel_work_sync(&s->period_work);
	s->pcm_buffer_poपूर्णांकer = 0;
	s->pcm_period_poपूर्णांकer = 0;
पूर्ण
EXPORT_SYMBOL(amdtp_stream_pcm_prepare);

अटल अचिन्हित पूर्णांक calculate_data_blocks(अचिन्हित पूर्णांक *data_block_state,
				bool is_blocking, bool is_no_info,
				अचिन्हित पूर्णांक syt_पूर्णांकerval, क्रमागत cip_sfc sfc)
अणु
	अचिन्हित पूर्णांक data_blocks;

	/* Blocking mode. */
	अगर (is_blocking) अणु
		/* This module generate empty packet क्रम 'no data'. */
		अगर (is_no_info)
			data_blocks = 0;
		अन्यथा
			data_blocks = syt_पूर्णांकerval;
	/* Non-blocking mode. */
	पूर्ण अन्यथा अणु
		अगर (!cip_sfc_is_base_44100(sfc)) अणु
			// Sample_rate / 8000 is an पूर्णांकeger, and precomputed.
			data_blocks = *data_block_state;
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक phase = *data_block_state;

		/*
		 * This calculates the number of data blocks per packet so that
		 * 1) the overall rate is correct and exactly synchronized to
		 *    the bus घड़ी, and
		 * 2) packets with a rounded-up number of blocks occur as early
		 *    as possible in the sequence (to prevent underruns of the
		 *    device's buffer).
		 */
			अगर (sfc == CIP_SFC_44100)
				/* 6 6 5 6 5 6 5 ... */
				data_blocks = 5 + ((phase & 1) ^
						   (phase == 0 || phase >= 40));
			अन्यथा
				/* 12 11 11 11 11 ... or 23 22 22 22 22 ... */
				data_blocks = 11 * (sfc >> 1) + (phase == 0);
			अगर (++phase >= (80 >> (sfc >> 1)))
				phase = 0;
			*data_block_state = phase;
		पूर्ण
	पूर्ण

	वापस data_blocks;
पूर्ण

अटल अचिन्हित पूर्णांक calculate_syt_offset(अचिन्हित पूर्णांक *last_syt_offset,
			अचिन्हित पूर्णांक *syt_offset_state, क्रमागत cip_sfc sfc)
अणु
	अचिन्हित पूर्णांक syt_offset;

	अगर (*last_syt_offset < TICKS_PER_CYCLE) अणु
		अगर (!cip_sfc_is_base_44100(sfc))
			syt_offset = *last_syt_offset + *syt_offset_state;
		अन्यथा अणु
		/*
		 * The समय, in ticks, of the n'th SYT_INTERVAL sample is:
		 *   n * SYT_INTERVAL * 24576000 / sample_rate
		 * Modulo TICKS_PER_CYCLE, the dअगरference between successive
		 * elements is about 1386.23.  Rounding the results of this
		 * क्रमmula to the SYT precision results in a sequence of
		 * dअगरferences that begins with:
		 *   1386 1386 1387 1386 1386 1386 1387 1386 1386 1386 1387 ...
		 * This code generates _exactly_ the same sequence.
		 */
			अचिन्हित पूर्णांक phase = *syt_offset_state;
			अचिन्हित पूर्णांक index = phase % 13;

			syt_offset = *last_syt_offset;
			syt_offset += 1386 + ((index && !(index & 3)) ||
					      phase == 146);
			अगर (++phase >= 147)
				phase = 0;
			*syt_offset_state = phase;
		पूर्ण
	पूर्ण अन्यथा
		syt_offset = *last_syt_offset - TICKS_PER_CYCLE;
	*last_syt_offset = syt_offset;

	अगर (syt_offset >= TICKS_PER_CYCLE)
		syt_offset = CIP_SYT_NO_INFO;

	वापस syt_offset;
पूर्ण

अटल व्योम update_pcm_poपूर्णांकers(काष्ठा amdtp_stream *s,
				काष्ठा snd_pcm_substream *pcm,
				अचिन्हित पूर्णांक frames)
अणु
	अचिन्हित पूर्णांक ptr;

	ptr = s->pcm_buffer_poपूर्णांकer + frames;
	अगर (ptr >= pcm->runसमय->buffer_size)
		ptr -= pcm->runसमय->buffer_size;
	WRITE_ONCE(s->pcm_buffer_poपूर्णांकer, ptr);

	s->pcm_period_poपूर्णांकer += frames;
	अगर (s->pcm_period_poपूर्णांकer >= pcm->runसमय->period_size) अणु
		s->pcm_period_poपूर्णांकer -= pcm->runसमय->period_size;
		queue_work(प्रणाली_highpri_wq, &s->period_work);
	पूर्ण
पूर्ण

अटल व्योम pcm_period_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा amdtp_stream *s = container_of(work, काष्ठा amdtp_stream,
					      period_work);
	काष्ठा snd_pcm_substream *pcm = READ_ONCE(s->pcm);

	अगर (pcm)
		snd_pcm_period_elapsed(pcm);
पूर्ण

अटल पूर्णांक queue_packet(काष्ठा amdtp_stream *s, काष्ठा fw_iso_packet *params,
			bool sched_irq)
अणु
	पूर्णांक err;

	params->पूर्णांकerrupt = sched_irq;
	params->tag = s->tag;
	params->sy = 0;

	err = fw_iso_context_queue(s->context, params, &s->buffer.iso_buffer,
				   s->buffer.packets[s->packet_index].offset);
	अगर (err < 0) अणु
		dev_err(&s->unit->device, "queueing error: %d\n", err);
		जाओ end;
	पूर्ण

	अगर (++s->packet_index >= s->queue_size)
		s->packet_index = 0;
end:
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक queue_out_packet(काष्ठा amdtp_stream *s,
				   काष्ठा fw_iso_packet *params, bool sched_irq)
अणु
	params->skip =
		!!(params->header_length == 0 && params->payload_length == 0);
	वापस queue_packet(s, params, sched_irq);
पूर्ण

अटल अंतरभूत पूर्णांक queue_in_packet(काष्ठा amdtp_stream *s,
				  काष्ठा fw_iso_packet *params)
अणु
	// Queue one packet क्रम IR context.
	params->header_length = s->ctx_data.tx.ctx_header_size;
	params->payload_length = s->ctx_data.tx.max_ctx_payload_length;
	params->skip = false;
	वापस queue_packet(s, params, false);
पूर्ण

अटल व्योम generate_cip_header(काष्ठा amdtp_stream *s, __be32 cip_header[2],
			अचिन्हित पूर्णांक data_block_counter, अचिन्हित पूर्णांक syt)
अणु
	cip_header[0] = cpu_to_be32(READ_ONCE(s->source_node_id_field) |
				(s->data_block_quadlets << CIP_DBS_SHIFT) |
				((s->sph << CIP_SPH_SHIFT) & CIP_SPH_MASK) |
				data_block_counter);
	cip_header[1] = cpu_to_be32(CIP_EOH |
			((s->fmt << CIP_FMT_SHIFT) & CIP_FMT_MASK) |
			((s->ctx_data.rx.fdf << CIP_FDF_SHIFT) & CIP_FDF_MASK) |
			(syt & CIP_SYT_MASK));
पूर्ण

अटल व्योम build_it_pkt_header(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक cycle,
				काष्ठा fw_iso_packet *params,
				अचिन्हित पूर्णांक data_blocks,
				अचिन्हित पूर्णांक data_block_counter,
				अचिन्हित पूर्णांक syt, अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक payload_length;
	__be32 *cip_header;

	payload_length = data_blocks * माप(__be32) * s->data_block_quadlets;
	params->payload_length = payload_length;

	अगर (!(s->flags & CIP_NO_HEADER)) अणु
		cip_header = (__be32 *)params->header;
		generate_cip_header(s, cip_header, data_block_counter, syt);
		params->header_length = 2 * माप(__be32);
		payload_length += params->header_length;
	पूर्ण अन्यथा अणु
		cip_header = शून्य;
	पूर्ण

	trace_amdtp_packet(s, cycle, cip_header, payload_length, data_blocks,
			   data_block_counter, s->packet_index, index);
पूर्ण

अटल पूर्णांक check_cip_header(काष्ठा amdtp_stream *s, स्थिर __be32 *buf,
			    अचिन्हित पूर्णांक payload_length,
			    अचिन्हित पूर्णांक *data_blocks,
			    अचिन्हित पूर्णांक *data_block_counter, अचिन्हित पूर्णांक *syt)
अणु
	u32 cip_header[2];
	अचिन्हित पूर्णांक sph;
	अचिन्हित पूर्णांक fmt;
	अचिन्हित पूर्णांक fdf;
	अचिन्हित पूर्णांक dbc;
	bool lost;

	cip_header[0] = be32_to_cpu(buf[0]);
	cip_header[1] = be32_to_cpu(buf[1]);

	/*
	 * This module supports 'Two-quadlet CIP header with SYT field'.
	 * For convenience, also check FMT field is AM824 or not.
	 */
	अगर ((((cip_header[0] & CIP_EOH_MASK) == CIP_EOH) ||
	     ((cip_header[1] & CIP_EOH_MASK) != CIP_EOH)) &&
	    (!(s->flags & CIP_HEADER_WITHOUT_EOH))) अणु
		dev_info_ratelimited(&s->unit->device,
				"Invalid CIP header for AMDTP: %08X:%08X\n",
				cip_header[0], cip_header[1]);
		वापस -EAGAIN;
	पूर्ण

	/* Check valid protocol or not. */
	sph = (cip_header[0] & CIP_SPH_MASK) >> CIP_SPH_SHIFT;
	fmt = (cip_header[1] & CIP_FMT_MASK) >> CIP_FMT_SHIFT;
	अगर (sph != s->sph || fmt != s->fmt) अणु
		dev_info_ratelimited(&s->unit->device,
				     "Detect unexpected protocol: %08x %08x\n",
				     cip_header[0], cip_header[1]);
		वापस -EAGAIN;
	पूर्ण

	/* Calculate data blocks */
	fdf = (cip_header[1] & CIP_FDF_MASK) >> CIP_FDF_SHIFT;
	अगर (payload_length < माप(__be32) * 2 ||
	    (fmt == CIP_FMT_AM && fdf == AMDTP_FDF_NO_DATA)) अणु
		*data_blocks = 0;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक data_block_quadlets =
				(cip_header[0] & CIP_DBS_MASK) >> CIP_DBS_SHIFT;
		/* aव्योम भागision by zero */
		अगर (data_block_quadlets == 0) अणु
			dev_err(&s->unit->device,
				"Detect invalid value in dbs field: %08X\n",
				cip_header[0]);
			वापस -EPROTO;
		पूर्ण
		अगर (s->flags & CIP_WRONG_DBS)
			data_block_quadlets = s->data_block_quadlets;

		*data_blocks = (payload_length / माप(__be32) - 2) /
							data_block_quadlets;
	पूर्ण

	/* Check data block counter continuity */
	dbc = cip_header[0] & CIP_DBC_MASK;
	अगर (*data_blocks == 0 && (s->flags & CIP_EMPTY_HAS_WRONG_DBC) &&
	    *data_block_counter != अच_पूर्णांक_उच्च)
		dbc = *data_block_counter;

	अगर ((dbc == 0x00 && (s->flags & CIP_SKIP_DBC_ZERO_CHECK)) ||
	    *data_block_counter == अच_पूर्णांक_उच्च) अणु
		lost = false;
	पूर्ण अन्यथा अगर (!(s->flags & CIP_DBC_IS_END_EVENT)) अणु
		lost = dbc != *data_block_counter;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक dbc_पूर्णांकerval;

		अगर (*data_blocks > 0 && s->ctx_data.tx.dbc_पूर्णांकerval > 0)
			dbc_पूर्णांकerval = s->ctx_data.tx.dbc_पूर्णांकerval;
		अन्यथा
			dbc_पूर्णांकerval = *data_blocks;

		lost = dbc != ((*data_block_counter + dbc_पूर्णांकerval) & 0xff);
	पूर्ण

	अगर (lost) अणु
		dev_err(&s->unit->device,
			"Detect discontinuity of CIP: %02X %02X\n",
			*data_block_counter, dbc);
		वापस -EIO;
	पूर्ण

	*data_block_counter = dbc;

	*syt = cip_header[1] & CIP_SYT_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक parse_ir_ctx_header(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक cycle,
			       स्थिर __be32 *ctx_header,
			       अचिन्हित पूर्णांक *payload_length,
			       अचिन्हित पूर्णांक *data_blocks,
			       अचिन्हित पूर्णांक *data_block_counter,
			       अचिन्हित पूर्णांक *syt, अचिन्हित पूर्णांक packet_index, अचिन्हित पूर्णांक index)
अणु
	स्थिर __be32 *cip_header;
	अचिन्हित पूर्णांक cip_header_size;
	पूर्णांक err;

	*payload_length = be32_to_cpu(ctx_header[0]) >> ISO_DATA_LENGTH_SHIFT;

	अगर (!(s->flags & CIP_NO_HEADER))
		cip_header_size = 8;
	अन्यथा
		cip_header_size = 0;

	अगर (*payload_length > cip_header_size + s->ctx_data.tx.max_ctx_payload_length) अणु
		dev_err(&s->unit->device,
			"Detect jumbo payload: %04x %04x\n",
			*payload_length, cip_header_size + s->ctx_data.tx.max_ctx_payload_length);
		वापस -EIO;
	पूर्ण

	अगर (cip_header_size > 0) अणु
		cip_header = ctx_header + 2;
		err = check_cip_header(s, cip_header, *payload_length,
				       data_blocks, data_block_counter, syt);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अणु
		cip_header = शून्य;
		err = 0;
		*data_blocks = *payload_length / माप(__be32) /
			       s->data_block_quadlets;
		*syt = 0;

		अगर (*data_block_counter == अच_पूर्णांक_उच्च)
			*data_block_counter = 0;
	पूर्ण

	trace_amdtp_packet(s, cycle, cip_header, *payload_length, *data_blocks,
			   *data_block_counter, packet_index, index);

	वापस err;
पूर्ण

// In CYCLE_TIMER रेजिस्टर of IEEE 1394, 7 bits are used to represent second. On
// the other hand, in DMA descriptors of 1394 OHCI, 3 bits are used to represent
// it. Thus, via Linux firewire subप्रणाली, we can get the 3 bits क्रम second.
अटल अंतरभूत u32 compute_cycle_count(__be32 ctx_header_tstamp)
अणु
	u32 tstamp = be32_to_cpu(ctx_header_tstamp) & HEADER_TSTAMP_MASK;
	वापस (((tstamp >> 13) & 0x07) * 8000) + (tstamp & 0x1fff);
पूर्ण

अटल अंतरभूत u32 increment_cycle_count(u32 cycle, अचिन्हित पूर्णांक addend)
अणु
	cycle += addend;
	अगर (cycle >= OHCI_MAX_SECOND * CYCLES_PER_SECOND)
		cycle -= OHCI_MAX_SECOND * CYCLES_PER_SECOND;
	वापस cycle;
पूर्ण

// Align to actual cycle count क्रम the packet which is going to be scheduled.
// This module queued the same number of isochronous cycle as the size of queue
// to kip isochronous cycle, thereक्रमe it's OK to just increment the cycle by
// the size of queue क्रम scheduled cycle.
अटल अंतरभूत u32 compute_it_cycle(स्थिर __be32 ctx_header_tstamp,
				   अचिन्हित पूर्णांक queue_size)
अणु
	u32 cycle = compute_cycle_count(ctx_header_tstamp);
	वापस increment_cycle_count(cycle, queue_size);
पूर्ण

अटल पूर्णांक generate_device_pkt_descs(काष्ठा amdtp_stream *s,
				     काष्ठा pkt_desc *descs,
				     स्थिर __be32 *ctx_header,
				     अचिन्हित पूर्णांक packets)
अणु
	अचिन्हित पूर्णांक dbc = s->data_block_counter;
	अचिन्हित पूर्णांक packet_index = s->packet_index;
	अचिन्हित पूर्णांक queue_size = s->queue_size;
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < packets; ++i) अणु
		काष्ठा pkt_desc *desc = descs + i;
		अचिन्हित पूर्णांक cycle;
		अचिन्हित पूर्णांक payload_length;
		अचिन्हित पूर्णांक data_blocks;
		अचिन्हित पूर्णांक syt;

		cycle = compute_cycle_count(ctx_header[1]);

		err = parse_ir_ctx_header(s, cycle, ctx_header, &payload_length,
					  &data_blocks, &dbc, &syt, packet_index, i);
		अगर (err < 0)
			वापस err;

		desc->cycle = cycle;
		desc->syt = syt;
		desc->data_blocks = data_blocks;
		desc->data_block_counter = dbc;
		desc->ctx_payload = s->buffer.packets[packet_index].buffer;

		अगर (!(s->flags & CIP_DBC_IS_END_EVENT))
			dbc = (dbc + desc->data_blocks) & 0xff;

		ctx_header +=
			s->ctx_data.tx.ctx_header_size / माप(*ctx_header);

		packet_index = (packet_index + 1) % queue_size;
	पूर्ण

	s->data_block_counter = dbc;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक compute_syt(अचिन्हित पूर्णांक syt_offset, अचिन्हित पूर्णांक cycle,
				अचिन्हित पूर्णांक transfer_delay)
अणु
	अचिन्हित पूर्णांक syt;

	syt_offset += transfer_delay;
	syt = ((cycle + syt_offset / TICKS_PER_CYCLE) << 12) |
	      (syt_offset % TICKS_PER_CYCLE);
	वापस syt & CIP_SYT_MASK;
पूर्ण

अटल व्योम generate_pkt_descs(काष्ठा amdtp_stream *s, काष्ठा pkt_desc *descs,
			       स्थिर __be32 *ctx_header, अचिन्हित पूर्णांक packets,
			       स्थिर काष्ठा seq_desc *seq_descs,
			       अचिन्हित पूर्णांक seq_size)
अणु
	अचिन्हित पूर्णांक dbc = s->data_block_counter;
	अचिन्हित पूर्णांक seq_index = s->ctx_data.rx.seq_index;
	पूर्णांक i;

	क्रम (i = 0; i < packets; ++i) अणु
		काष्ठा pkt_desc *desc = descs + i;
		अचिन्हित पूर्णांक index = (s->packet_index + i) % s->queue_size;
		स्थिर काष्ठा seq_desc *seq = seq_descs + seq_index;
		अचिन्हित पूर्णांक syt;

		desc->cycle = compute_it_cycle(*ctx_header, s->queue_size);

		syt = seq->syt_offset;
		अगर (syt != CIP_SYT_NO_INFO) अणु
			syt = compute_syt(syt, desc->cycle,
					  s->ctx_data.rx.transfer_delay);
		पूर्ण
		desc->syt = syt;
		desc->data_blocks = seq->data_blocks;

		अगर (s->flags & CIP_DBC_IS_END_EVENT)
			dbc = (dbc + desc->data_blocks) & 0xff;

		desc->data_block_counter = dbc;

		अगर (!(s->flags & CIP_DBC_IS_END_EVENT))
			dbc = (dbc + desc->data_blocks) & 0xff;

		desc->ctx_payload = s->buffer.packets[index].buffer;

		seq_index = (seq_index + 1) % seq_size;

		++ctx_header;
	पूर्ण

	s->data_block_counter = dbc;
	s->ctx_data.rx.seq_index = seq_index;
पूर्ण

अटल अंतरभूत व्योम cancel_stream(काष्ठा amdtp_stream *s)
अणु
	s->packet_index = -1;
	अगर (in_पूर्णांकerrupt())
		amdtp_stream_pcm_पात(s);
	WRITE_ONCE(s->pcm_buffer_poपूर्णांकer, SNDRV_PCM_POS_XRUN);
पूर्ण

अटल व्योम process_ctx_payloads(काष्ठा amdtp_stream *s,
				 स्थिर काष्ठा pkt_desc *descs,
				 अचिन्हित पूर्णांक packets)
अणु
	काष्ठा snd_pcm_substream *pcm;
	अचिन्हित पूर्णांक pcm_frames;

	pcm = READ_ONCE(s->pcm);
	pcm_frames = s->process_ctx_payloads(s, descs, packets, pcm);
	अगर (pcm)
		update_pcm_poपूर्णांकers(s, pcm, pcm_frames);
पूर्ण

अटल व्योम out_stream_callback(काष्ठा fw_iso_context *context, u32 tstamp,
				माप_प्रकार header_length, व्योम *header,
				व्योम *निजी_data)
अणु
	काष्ठा amdtp_stream *s = निजी_data;
	स्थिर काष्ठा amdtp_करोमुख्य *d = s->करोमुख्य;
	स्थिर __be32 *ctx_header = header;
	अचिन्हित पूर्णांक events_per_period = s->ctx_data.rx.events_per_period;
	अचिन्हित पूर्णांक event_count = s->ctx_data.rx.event_count;
	अचिन्हित पूर्णांक packets;
	पूर्णांक i;

	अगर (s->packet_index < 0)
		वापस;

	// Calculate the number of packets in buffer and check XRUN.
	packets = header_length / माप(*ctx_header);

	generate_pkt_descs(s, s->pkt_descs, ctx_header, packets, d->seq_descs,
			   d->seq_size);

	process_ctx_payloads(s, s->pkt_descs, packets);

	क्रम (i = 0; i < packets; ++i) अणु
		स्थिर काष्ठा pkt_desc *desc = s->pkt_descs + i;
		अचिन्हित पूर्णांक syt;
		काष्ठा अणु
			काष्ठा fw_iso_packet params;
			__be32 header[IT_PKT_HEADER_SIZE_CIP / माप(__be32)];
		पूर्ण ढाँचा = अणु अणु0पूर्ण, अणु0पूर्ण पूर्ण;
		bool sched_irq = false;

		अगर (s->ctx_data.rx.syt_override < 0)
			syt = desc->syt;
		अन्यथा
			syt = s->ctx_data.rx.syt_override;

		build_it_pkt_header(s, desc->cycle, &ढाँचा.params,
				    desc->data_blocks, desc->data_block_counter,
				    syt, i);

		अगर (s == s->करोमुख्य->irq_target) अणु
			event_count += desc->data_blocks;
			अगर (event_count >= events_per_period) अणु
				event_count -= events_per_period;
				sched_irq = true;
			पूर्ण
		पूर्ण

		अगर (queue_out_packet(s, &ढाँचा.params, sched_irq) < 0) अणु
			cancel_stream(s);
			वापस;
		पूर्ण
	पूर्ण

	s->ctx_data.rx.event_count = event_count;
पूर्ण

अटल व्योम in_stream_callback(काष्ठा fw_iso_context *context, u32 tstamp,
			       माप_प्रकार header_length, व्योम *header,
			       व्योम *निजी_data)
अणु
	काष्ठा amdtp_stream *s = निजी_data;
	__be32 *ctx_header = header;
	अचिन्हित पूर्णांक packets;
	पूर्णांक i;
	पूर्णांक err;

	अगर (s->packet_index < 0)
		वापस;

	// Calculate the number of packets in buffer and check XRUN.
	packets = header_length / s->ctx_data.tx.ctx_header_size;

	err = generate_device_pkt_descs(s, s->pkt_descs, ctx_header, packets);
	अगर (err < 0) अणु
		अगर (err != -EAGAIN) अणु
			cancel_stream(s);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		process_ctx_payloads(s, s->pkt_descs, packets);
	पूर्ण

	क्रम (i = 0; i < packets; ++i) अणु
		काष्ठा fw_iso_packet params = अणु0पूर्ण;

		अगर (queue_in_packet(s, &params) < 0) अणु
			cancel_stream(s);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pool_ideal_seq_descs(काष्ठा amdtp_करोमुख्य *d, अचिन्हित पूर्णांक packets)
अणु
	काष्ठा amdtp_stream *irq_target = d->irq_target;
	अचिन्हित पूर्णांक seq_tail = d->seq_tail;
	अचिन्हित पूर्णांक seq_size = d->seq_size;
	अचिन्हित पूर्णांक min_avail;
	काष्ठा amdtp_stream *s;

	min_avail = d->seq_size;
	list_क्रम_each_entry(s, &d->streams, list) अणु
		अचिन्हित पूर्णांक seq_index;
		अचिन्हित पूर्णांक avail;

		अगर (s->direction == AMDTP_IN_STREAM)
			जारी;

		seq_index = s->ctx_data.rx.seq_index;
		avail = d->seq_tail;
		अगर (seq_index > avail)
			avail += d->seq_size;
		avail -= seq_index;

		अगर (avail < min_avail)
			min_avail = avail;
	पूर्ण

	जबतक (min_avail < packets) अणु
		काष्ठा seq_desc *desc = d->seq_descs + seq_tail;

		desc->syt_offset = calculate_syt_offset(&d->last_syt_offset,
					&d->syt_offset_state, irq_target->sfc);
		desc->data_blocks = calculate_data_blocks(&d->data_block_state,
				!!(irq_target->flags & CIP_BLOCKING),
				desc->syt_offset == CIP_SYT_NO_INFO,
				irq_target->syt_पूर्णांकerval, irq_target->sfc);

		++seq_tail;
		seq_tail %= seq_size;

		++min_avail;
	पूर्ण

	d->seq_tail = seq_tail;
पूर्ण

अटल व्योम irq_target_callback(काष्ठा fw_iso_context *context, u32 tstamp,
				माप_प्रकार header_length, व्योम *header,
				व्योम *निजी_data)
अणु
	काष्ठा amdtp_stream *irq_target = निजी_data;
	काष्ठा amdtp_करोमुख्य *d = irq_target->करोमुख्य;
	अचिन्हित पूर्णांक packets = header_length / माप(__be32);
	काष्ठा amdtp_stream *s;

	// Record enough entries with extra 3 cycles at least.
	pool_ideal_seq_descs(d, packets + 3);

	out_stream_callback(context, tstamp, header_length, header, irq_target);
	अगर (amdtp_streaming_error(irq_target))
		जाओ error;

	list_क्रम_each_entry(s, &d->streams, list) अणु
		अगर (s != irq_target && amdtp_stream_running(s)) अणु
			fw_iso_context_flush_completions(s->context);
			अगर (amdtp_streaming_error(s))
				जाओ error;
		पूर्ण
	पूर्ण

	वापस;
error:
	अगर (amdtp_stream_running(irq_target))
		cancel_stream(irq_target);

	list_क्रम_each_entry(s, &d->streams, list) अणु
		अगर (amdtp_stream_running(s))
			cancel_stream(s);
	पूर्ण
पूर्ण

// this is executed one समय.
अटल व्योम amdtp_stream_first_callback(काष्ठा fw_iso_context *context,
					u32 tstamp, माप_प्रकार header_length,
					व्योम *header, व्योम *निजी_data)
अणु
	काष्ठा amdtp_stream *s = निजी_data;
	स्थिर __be32 *ctx_header = header;
	u32 cycle;

	/*
	 * For in-stream, first packet has come.
	 * For out-stream, prepared to transmit first packet
	 */
	s->callbacked = true;
	wake_up(&s->callback_रुको);

	अगर (s->direction == AMDTP_IN_STREAM) अणु
		cycle = compute_cycle_count(ctx_header[1]);

		context->callback.sc = in_stream_callback;
	पूर्ण अन्यथा अणु
		cycle = compute_it_cycle(*ctx_header, s->queue_size);

		अगर (s == s->करोमुख्य->irq_target)
			context->callback.sc = irq_target_callback;
		अन्यथा
			context->callback.sc = out_stream_callback;
	पूर्ण

	s->start_cycle = cycle;

	context->callback.sc(context, tstamp, header_length, header, s);
पूर्ण

/**
 * amdtp_stream_start - start transferring packets
 * @s: the AMDTP stream to start
 * @channel: the isochronous channel on the bus
 * @speed: firewire speed code
 * @start_cycle: the isochronous cycle to start the context. Start immediately
 *		 अगर negative value is given.
 * @queue_size: The number of packets in the queue.
 * @idle_irq_पूर्णांकerval: the पूर्णांकerval to queue packet during initial state.
 *
 * The stream cannot be started until it has been configured with
 * amdtp_stream_set_parameters() and it must be started beक्रमe any PCM or MIDI
 * device can be started.
 */
अटल पूर्णांक amdtp_stream_start(काष्ठा amdtp_stream *s, पूर्णांक channel, पूर्णांक speed,
			      पूर्णांक start_cycle, अचिन्हित पूर्णांक queue_size,
			      अचिन्हित पूर्णांक idle_irq_पूर्णांकerval)
अणु
	bool is_irq_target = (s == s->करोमुख्य->irq_target);
	अचिन्हित पूर्णांक ctx_header_size;
	अचिन्हित पूर्णांक max_ctx_payload_size;
	क्रमागत dma_data_direction dir;
	पूर्णांक type, tag, err;

	mutex_lock(&s->mutex);

	अगर (WARN_ON(amdtp_stream_running(s) ||
		    (s->data_block_quadlets < 1))) अणु
		err = -EBADFD;
		जाओ err_unlock;
	पूर्ण

	अगर (s->direction == AMDTP_IN_STREAM) अणु
		// NOTE: IT context should be used क्रम स्थिरant IRQ.
		अगर (is_irq_target) अणु
			err = -EINVAL;
			जाओ err_unlock;
		पूर्ण

		s->data_block_counter = अच_पूर्णांक_उच्च;
	पूर्ण अन्यथा अणु
		s->data_block_counter = 0;
	पूर्ण

	// initialize packet buffer.
	max_ctx_payload_size = amdtp_stream_get_max_payload(s);
	अगर (s->direction == AMDTP_IN_STREAM) अणु
		dir = DMA_FROM_DEVICE;
		type = FW_ISO_CONTEXT_RECEIVE;
		अगर (!(s->flags & CIP_NO_HEADER)) अणु
			max_ctx_payload_size -= 8;
			ctx_header_size = IR_CTX_HEADER_SIZE_CIP;
		पूर्ण अन्यथा अणु
			ctx_header_size = IR_CTX_HEADER_SIZE_NO_CIP;
		पूर्ण
	पूर्ण अन्यथा अणु
		dir = DMA_TO_DEVICE;
		type = FW_ISO_CONTEXT_TRANSMIT;
		ctx_header_size = 0;	// No effect क्रम IT context.

		अगर (!(s->flags & CIP_NO_HEADER))
			max_ctx_payload_size -= IT_PKT_HEADER_SIZE_CIP;
	पूर्ण

	err = iso_packets_buffer_init(&s->buffer, s->unit, queue_size,
				      max_ctx_payload_size, dir);
	अगर (err < 0)
		जाओ err_unlock;
	s->queue_size = queue_size;

	s->context = fw_iso_context_create(fw_parent_device(s->unit)->card,
					  type, channel, speed, ctx_header_size,
					  amdtp_stream_first_callback, s);
	अगर (IS_ERR(s->context)) अणु
		err = PTR_ERR(s->context);
		अगर (err == -EBUSY)
			dev_err(&s->unit->device,
				"no free stream on this controller\n");
		जाओ err_buffer;
	पूर्ण

	amdtp_stream_update(s);

	अगर (s->direction == AMDTP_IN_STREAM) अणु
		s->ctx_data.tx.max_ctx_payload_length = max_ctx_payload_size;
		s->ctx_data.tx.ctx_header_size = ctx_header_size;
	पूर्ण

	अगर (s->flags & CIP_NO_HEADER)
		s->tag = TAG_NO_CIP_HEADER;
	अन्यथा
		s->tag = TAG_CIP;

	s->pkt_descs = kसुस्मृति(s->queue_size, माप(*s->pkt_descs),
			       GFP_KERNEL);
	अगर (!s->pkt_descs) अणु
		err = -ENOMEM;
		जाओ err_context;
	पूर्ण

	s->packet_index = 0;
	करो अणु
		काष्ठा fw_iso_packet params;

		अगर (s->direction == AMDTP_IN_STREAM) अणु
			err = queue_in_packet(s, &params);
		पूर्ण अन्यथा अणु
			bool sched_irq = false;

			params.header_length = 0;
			params.payload_length = 0;

			अगर (is_irq_target) अणु
				sched_irq = !((s->packet_index + 1) %
					      idle_irq_पूर्णांकerval);
			पूर्ण

			err = queue_out_packet(s, &params, sched_irq);
		पूर्ण
		अगर (err < 0)
			जाओ err_pkt_descs;
	पूर्ण जबतक (s->packet_index > 0);

	/* NOTE: TAG1 matches CIP. This just affects in stream. */
	tag = FW_ISO_CONTEXT_MATCH_TAG1;
	अगर ((s->flags & CIP_EMPTY_WITH_TAG0) || (s->flags & CIP_NO_HEADER))
		tag |= FW_ISO_CONTEXT_MATCH_TAG0;

	s->callbacked = false;
	err = fw_iso_context_start(s->context, start_cycle, 0, tag);
	अगर (err < 0)
		जाओ err_pkt_descs;

	mutex_unlock(&s->mutex);

	वापस 0;
err_pkt_descs:
	kमुक्त(s->pkt_descs);
err_context:
	fw_iso_context_destroy(s->context);
	s->context = ERR_PTR(-1);
err_buffer:
	iso_packets_buffer_destroy(&s->buffer, s->unit);
err_unlock:
	mutex_unlock(&s->mutex);

	वापस err;
पूर्ण

/**
 * amdtp_करोमुख्य_stream_pcm_poपूर्णांकer - get the PCM buffer position
 * @d: the AMDTP करोमुख्य.
 * @s: the AMDTP stream that transports the PCM data
 *
 * Returns the current buffer position, in frames.
 */
अचिन्हित दीर्घ amdtp_करोमुख्य_stream_pcm_poपूर्णांकer(काष्ठा amdtp_करोमुख्य *d,
					      काष्ठा amdtp_stream *s)
अणु
	काष्ठा amdtp_stream *irq_target = d->irq_target;

	अगर (irq_target && amdtp_stream_running(irq_target)) अणु
		// This function is called in software IRQ context of
		// period_work or process context.
		//
		// When the software IRQ context was scheduled by software IRQ
		// context of IT contexts, queued packets were alपढ़ोy handled.
		// Thereक्रमe, no need to flush the queue in buffer furthermore.
		//
		// When the process context reach here, some packets will be
		// alपढ़ोy queued in the buffer. These packets should be handled
		// immediately to keep better granularity of PCM poपूर्णांकer.
		//
		// Later, the process context will someबार schedules software
		// IRQ context of the period_work. Then, no need to flush the
		// queue by the same reason as described in the above
		अगर (current_work() != &s->period_work) अणु
			// Queued packet should be processed without any kernel
			// preemption to keep latency against bus cycle.
			preempt_disable();
			fw_iso_context_flush_completions(irq_target->context);
			preempt_enable();
		पूर्ण
	पूर्ण

	वापस READ_ONCE(s->pcm_buffer_poपूर्णांकer);
पूर्ण
EXPORT_SYMBOL_GPL(amdtp_करोमुख्य_stream_pcm_poपूर्णांकer);

/**
 * amdtp_करोमुख्य_stream_pcm_ack - acknowledge queued PCM frames
 * @d: the AMDTP करोमुख्य.
 * @s: the AMDTP stream that transfers the PCM frames
 *
 * Returns zero always.
 */
पूर्णांक amdtp_करोमुख्य_stream_pcm_ack(काष्ठा amdtp_करोमुख्य *d, काष्ठा amdtp_stream *s)
अणु
	काष्ठा amdtp_stream *irq_target = d->irq_target;

	// Process isochronous packets क्रम recent isochronous cycle to handle
	// queued PCM frames.
	अगर (irq_target && amdtp_stream_running(irq_target)) अणु
		// Queued packet should be processed without any kernel
		// preemption to keep latency against bus cycle.
		preempt_disable();
		fw_iso_context_flush_completions(irq_target->context);
		preempt_enable();
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(amdtp_करोमुख्य_stream_pcm_ack);

/**
 * amdtp_stream_update - update the stream after a bus reset
 * @s: the AMDTP stream
 */
व्योम amdtp_stream_update(काष्ठा amdtp_stream *s)
अणु
	/* Precomputing. */
	WRITE_ONCE(s->source_node_id_field,
                   (fw_parent_device(s->unit)->card->node_id << CIP_SID_SHIFT) & CIP_SID_MASK);
पूर्ण
EXPORT_SYMBOL(amdtp_stream_update);

/**
 * amdtp_stream_stop - stop sending packets
 * @s: the AMDTP stream to stop
 *
 * All PCM and MIDI devices of the stream must be stopped beक्रमe the stream
 * itself can be stopped.
 */
अटल व्योम amdtp_stream_stop(काष्ठा amdtp_stream *s)
अणु
	mutex_lock(&s->mutex);

	अगर (!amdtp_stream_running(s)) अणु
		mutex_unlock(&s->mutex);
		वापस;
	पूर्ण

	cancel_work_sync(&s->period_work);
	fw_iso_context_stop(s->context);
	fw_iso_context_destroy(s->context);
	s->context = ERR_PTR(-1);
	iso_packets_buffer_destroy(&s->buffer, s->unit);
	kमुक्त(s->pkt_descs);

	s->callbacked = false;

	mutex_unlock(&s->mutex);
पूर्ण

/**
 * amdtp_stream_pcm_पात - पात the running PCM device
 * @s: the AMDTP stream about to be stopped
 *
 * If the isochronous stream needs to be stopped asynchronously, call this
 * function first to stop the PCM device.
 */
व्योम amdtp_stream_pcm_पात(काष्ठा amdtp_stream *s)
अणु
	काष्ठा snd_pcm_substream *pcm;

	pcm = READ_ONCE(s->pcm);
	अगर (pcm)
		snd_pcm_stop_xrun(pcm);
पूर्ण
EXPORT_SYMBOL(amdtp_stream_pcm_पात);

/**
 * amdtp_करोमुख्य_init - initialize an AMDTP करोमुख्य काष्ठाure
 * @d: the AMDTP करोमुख्य to initialize.
 */
पूर्णांक amdtp_करोमुख्य_init(काष्ठा amdtp_करोमुख्य *d)
अणु
	INIT_LIST_HEAD(&d->streams);

	d->events_per_period = 0;

	d->seq_descs = शून्य;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(amdtp_करोमुख्य_init);

/**
 * amdtp_करोमुख्य_destroy - destroy an AMDTP करोमुख्य काष्ठाure
 * @d: the AMDTP करोमुख्य to destroy.
 */
व्योम amdtp_करोमुख्य_destroy(काष्ठा amdtp_करोमुख्य *d)
अणु
	// At present nothing to करो.
	वापस;
पूर्ण
EXPORT_SYMBOL_GPL(amdtp_करोमुख्य_destroy);

/**
 * amdtp_करोमुख्य_add_stream - रेजिस्टर isoc context पूर्णांकo the करोमुख्य.
 * @d: the AMDTP करोमुख्य.
 * @s: the AMDTP stream.
 * @channel: the isochronous channel on the bus.
 * @speed: firewire speed code.
 */
पूर्णांक amdtp_करोमुख्य_add_stream(काष्ठा amdtp_करोमुख्य *d, काष्ठा amdtp_stream *s,
			    पूर्णांक channel, पूर्णांक speed)
अणु
	काष्ठा amdtp_stream *पंचांगp;

	list_क्रम_each_entry(पंचांगp, &d->streams, list) अणु
		अगर (s == पंचांगp)
			वापस -EBUSY;
	पूर्ण

	list_add(&s->list, &d->streams);

	s->channel = channel;
	s->speed = speed;
	s->करोमुख्य = d;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(amdtp_करोमुख्य_add_stream);

अटल पूर्णांक get_current_cycle_समय(काष्ठा fw_card *fw_card, पूर्णांक *cur_cycle)
अणु
	पूर्णांक generation;
	पूर्णांक rcode;
	__be32 reg;
	u32 data;

	// This is a request to local 1394 OHCI controller and expected to
	// complete without any event रुकोing.
	generation = fw_card->generation;
	smp_rmb();	// node_id vs. generation.
	rcode = fw_run_transaction(fw_card, TCODE_READ_QUADLET_REQUEST,
				   fw_card->node_id, generation, SCODE_100,
				   CSR_REGISTER_BASE + CSR_CYCLE_TIME,
				   &reg, माप(reg));
	अगर (rcode != RCODE_COMPLETE)
		वापस -EIO;

	data = be32_to_cpu(reg);
	*cur_cycle = data >> 12;

	वापस 0;
पूर्ण

/**
 * amdtp_करोमुख्य_start - start sending packets क्रम isoc context in the करोमुख्य.
 * @d: the AMDTP करोमुख्य.
 * @ir_delay_cycle: the cycle delay to start all IR contexts.
 */
पूर्णांक amdtp_करोमुख्य_start(काष्ठा amdtp_करोमुख्य *d, अचिन्हित पूर्णांक ir_delay_cycle)
अणु
	अटल स्थिर काष्ठा अणु
		अचिन्हित पूर्णांक data_block;
		अचिन्हित पूर्णांक syt_offset;
	पूर्ण *entry, initial_state[] = अणु
		[CIP_SFC_32000]  = अणु  4, 3072 पूर्ण,
		[CIP_SFC_48000]  = अणु  6, 1024 पूर्ण,
		[CIP_SFC_96000]  = अणु 12, 1024 पूर्ण,
		[CIP_SFC_192000] = अणु 24, 1024 पूर्ण,
		[CIP_SFC_44100]  = अणु  0,   67 पूर्ण,
		[CIP_SFC_88200]  = अणु  0,   67 पूर्ण,
		[CIP_SFC_176400] = अणु  0,   67 पूर्ण,
	पूर्ण;
	अचिन्हित पूर्णांक events_per_buffer = d->events_per_buffer;
	अचिन्हित पूर्णांक events_per_period = d->events_per_period;
	अचिन्हित पूर्णांक idle_irq_पूर्णांकerval;
	अचिन्हित पूर्णांक queue_size;
	काष्ठा amdtp_stream *s;
	पूर्णांक cycle;
	पूर्णांक err;

	// Select an IT context as IRQ target.
	list_क्रम_each_entry(s, &d->streams, list) अणु
		अगर (s->direction == AMDTP_OUT_STREAM)
			अवरोध;
	पूर्ण
	अगर (!s)
		वापस -ENXIO;
	d->irq_target = s;

	// This is a हाल that AMDTP streams in करोमुख्य run just क्रम MIDI
	// substream. Use the number of events equivalent to 10 msec as
	// पूर्णांकerval of hardware IRQ.
	अगर (events_per_period == 0)
		events_per_period = amdtp_rate_table[d->irq_target->sfc] / 100;
	अगर (events_per_buffer == 0)
		events_per_buffer = events_per_period * 3;

	queue_size = DIV_ROUND_UP(CYCLES_PER_SECOND * events_per_buffer,
				  amdtp_rate_table[d->irq_target->sfc]);

	d->seq_descs = kसुस्मृति(queue_size, माप(*d->seq_descs), GFP_KERNEL);
	अगर (!d->seq_descs)
		वापस -ENOMEM;
	d->seq_size = queue_size;
	d->seq_tail = 0;

	entry = &initial_state[s->sfc];
	d->data_block_state = entry->data_block;
	d->syt_offset_state = entry->syt_offset;
	d->last_syt_offset = TICKS_PER_CYCLE;

	अगर (ir_delay_cycle > 0) अणु
		काष्ठा fw_card *fw_card = fw_parent_device(s->unit)->card;

		err = get_current_cycle_समय(fw_card, &cycle);
		अगर (err < 0)
			जाओ error;

		// No need to care overflow in cycle field because of enough
		// width.
		cycle += ir_delay_cycle;

		// Round up to sec field.
		अगर ((cycle & 0x00001fff) >= CYCLES_PER_SECOND) अणु
			अचिन्हित पूर्णांक sec;

			// The sec field can overflow.
			sec = (cycle & 0xffffe000) >> 13;
			cycle = (++sec << 13) |
				((cycle & 0x00001fff) / CYCLES_PER_SECOND);
		पूर्ण

		// In OHCI 1394 specअगरication, lower 2 bits are available क्रम
		// sec field.
		cycle &= 0x00007fff;
	पूर्ण अन्यथा अणु
		cycle = -1;
	पूर्ण

	list_क्रम_each_entry(s, &d->streams, list) अणु
		पूर्णांक cycle_match;

		अगर (s->direction == AMDTP_IN_STREAM) अणु
			cycle_match = cycle;
		पूर्ण अन्यथा अणु
			// IT context starts immediately.
			cycle_match = -1;
			s->ctx_data.rx.seq_index = 0;
		पूर्ण

		अगर (s != d->irq_target) अणु
			err = amdtp_stream_start(s, s->channel, s->speed,
						 cycle_match, queue_size, 0);
			अगर (err < 0)
				जाओ error;
		पूर्ण
	पूर्ण

	s = d->irq_target;
	s->ctx_data.rx.events_per_period = events_per_period;
	s->ctx_data.rx.event_count = 0;
	s->ctx_data.rx.seq_index = 0;

	idle_irq_पूर्णांकerval = DIV_ROUND_UP(CYCLES_PER_SECOND * events_per_period,
					 amdtp_rate_table[d->irq_target->sfc]);
	err = amdtp_stream_start(s, s->channel, s->speed, -1, queue_size,
				 idle_irq_पूर्णांकerval);
	अगर (err < 0)
		जाओ error;

	वापस 0;
error:
	list_क्रम_each_entry(s, &d->streams, list)
		amdtp_stream_stop(s);
	kमुक्त(d->seq_descs);
	d->seq_descs = शून्य;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(amdtp_करोमुख्य_start);

/**
 * amdtp_करोमुख्य_stop - stop sending packets क्रम isoc context in the same करोमुख्य.
 * @d: the AMDTP करोमुख्य to which the isoc contexts beदीर्घ.
 */
व्योम amdtp_करोमुख्य_stop(काष्ठा amdtp_करोमुख्य *d)
अणु
	काष्ठा amdtp_stream *s, *next;

	अगर (d->irq_target)
		amdtp_stream_stop(d->irq_target);

	list_क्रम_each_entry_safe(s, next, &d->streams, list) अणु
		list_del(&s->list);

		अगर (s != d->irq_target)
			amdtp_stream_stop(s);
	पूर्ण

	d->events_per_period = 0;
	d->irq_target = शून्य;

	kमुक्त(d->seq_descs);
	d->seq_descs = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(amdtp_करोमुख्य_stop);
