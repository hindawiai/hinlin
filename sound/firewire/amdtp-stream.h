<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित SOUND_FIREWIRE_AMDTP_H_INCLUDED
#घोषणा SOUND_FIREWIRE_AMDTP_H_INCLUDED

#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>
#समावेश <sound/asound.h>
#समावेश "packets-buffer.h"

/**
 * क्रमागत cip_flags - describes details of the streaming protocol
 * @CIP_NONBLOCKING: In non-blocking mode, each packet contains
 *	sample_rate/8000 samples, with rounding up or करोwn to adjust
 *	क्रम घड़ी skew and left-over fractional samples.  This should
 *	be used अगर supported by the device.
 * @CIP_BLOCKING: In blocking mode, each packet contains either zero or
 *	SYT_INTERVAL samples, with these two types alternating so that
 *	the overall sample rate comes out right.
 * @CIP_EMPTY_WITH_TAG0: Only क्रम in-stream. Empty in-packets have TAG0.
 * @CIP_DBC_IS_END_EVENT: The value of dbc in an packet corresponds to the end
 * of event in the packet. Out of IEC 61883.
 * @CIP_WRONG_DBS: Only क्रम in-stream. The value of dbs is wrong in in-packets.
 *	The value of data_block_quadlets is used instead of reported value.
 * @CIP_SKIP_DBC_ZERO_CHECK: Only क्रम in-stream.  Packets with zero in dbc is
 *	skipped क्रम detecting discontinuity.
 * @CIP_EMPTY_HAS_WRONG_DBC: Only क्रम in-stream. The value of dbc in empty
 *	packet is wrong but the others are correct.
 * @CIP_JUMBO_PAYLOAD: Only क्रम in-stream. The number of data blocks in an
 *	packet is larger than IEC 61883-6 defines. Current implementation
 *	allows 5 बार as large as IEC 61883-6 defines.
 * @CIP_HEADER_WITHOUT_EOH: Only क्रम in-stream. CIP Header करोesn't include
 *	valid EOH.
 * @CIP_NO_HEADERS: a lack of headers in packets
 * @CIP_UNALIGHED_DBC: Only क्रम in-stream. The value of dbc is not alighed to
 *	the value of current SYT_INTERVAL; e.g. initial value is not zero.
 */
क्रमागत cip_flags अणु
	CIP_NONBLOCKING		= 0x00,
	CIP_BLOCKING		= 0x01,
	CIP_EMPTY_WITH_TAG0	= 0x02,
	CIP_DBC_IS_END_EVENT	= 0x04,
	CIP_WRONG_DBS		= 0x08,
	CIP_SKIP_DBC_ZERO_CHECK	= 0x10,
	CIP_EMPTY_HAS_WRONG_DBC	= 0x20,
	CIP_JUMBO_PAYLOAD	= 0x40,
	CIP_HEADER_WITHOUT_EOH	= 0x80,
	CIP_NO_HEADER		= 0x100,
	CIP_UNALIGHED_DBC	= 0x200,
पूर्ण;

/**
 * क्रमागत cip_sfc - supported Sampling Frequency Codes (SFCs)
 * @CIP_SFC_32000:   32,000 data blocks
 * @CIP_SFC_44100:   44,100 data blocks
 * @CIP_SFC_48000:   48,000 data blocks
 * @CIP_SFC_88200:   88,200 data blocks
 * @CIP_SFC_96000:   96,000 data blocks
 * @CIP_SFC_176400: 176,400 data blocks
 * @CIP_SFC_192000: 192,000 data blocks
 * @CIP_SFC_COUNT: the number of supported SFCs
 *
 * These values are used to show nominal Sampling Frequency Code in
 * Format Dependent Field (FDF) of AMDTP packet header. In IEC 61883-6:2002,
 * this code means the number of events per second. Actually the code
 * represents the number of data blocks transferred per second in an AMDTP
 * stream.
 *
 * In IEC 61883-6:2005, some extensions were added to support more types of
 * data such as 'One Bit LInear Audio', thereक्रमe the meaning of SFC became
 * dअगरferent depending on the types.
 *
 * Currently our implementation is compatible with IEC 61883-6:2002.
 */
क्रमागत cip_sfc अणु
	CIP_SFC_32000  = 0,
	CIP_SFC_44100  = 1,
	CIP_SFC_48000  = 2,
	CIP_SFC_88200  = 3,
	CIP_SFC_96000  = 4,
	CIP_SFC_176400 = 5,
	CIP_SFC_192000 = 6,
	CIP_SFC_COUNT
पूर्ण;

काष्ठा fw_unit;
काष्ठा fw_iso_context;
काष्ठा snd_pcm_substream;
काष्ठा snd_pcm_runसमय;

क्रमागत amdtp_stream_direction अणु
	AMDTP_OUT_STREAM = 0,
	AMDTP_IN_STREAM
पूर्ण;

काष्ठा pkt_desc अणु
	u32 cycle;
	u32 syt;
	अचिन्हित पूर्णांक data_blocks;
	अचिन्हित पूर्णांक data_block_counter;
	__be32 *ctx_payload;
पूर्ण;

काष्ठा amdtp_stream;
प्रकार अचिन्हित पूर्णांक (*amdtp_stream_process_ctx_payloads_t)(
						काष्ठा amdtp_stream *s,
						स्थिर काष्ठा pkt_desc *desc,
						अचिन्हित पूर्णांक packets,
						काष्ठा snd_pcm_substream *pcm);

काष्ठा amdtp_करोमुख्य;
काष्ठा amdtp_stream अणु
	काष्ठा fw_unit *unit;
	क्रमागत cip_flags flags;
	क्रमागत amdtp_stream_direction direction;
	काष्ठा mutex mutex;

	/* For packet processing. */
	काष्ठा fw_iso_context *context;
	काष्ठा iso_packets_buffer buffer;
	अचिन्हित पूर्णांक queue_size;
	पूर्णांक packet_index;
	काष्ठा pkt_desc *pkt_descs;
	पूर्णांक tag;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक ctx_header_size;

			// limit क्रम payload of iso packet.
			अचिन्हित पूर्णांक max_ctx_payload_length;

			// For quirks of CIP headers.
			// Fixed पूर्णांकerval of dbc between previos/current
			// packets.
			अचिन्हित पूर्णांक dbc_पूर्णांकerval;
		पूर्ण tx;
		काष्ठा अणु
			// To calculate CIP data blocks and tstamp.
			अचिन्हित पूर्णांक transfer_delay;
			अचिन्हित पूर्णांक seq_index;

			// To generate CIP header.
			अचिन्हित पूर्णांक fdf;
			पूर्णांक syt_override;

			// To generate स्थिरant hardware IRQ.
			अचिन्हित पूर्णांक event_count;
			अचिन्हित पूर्णांक events_per_period;
		पूर्ण rx;
	पूर्ण ctx_data;

	/* For CIP headers. */
	अचिन्हित पूर्णांक source_node_id_field;
	अचिन्हित पूर्णांक data_block_quadlets;
	अचिन्हित पूर्णांक data_block_counter;
	अचिन्हित पूर्णांक sph;
	अचिन्हित पूर्णांक fmt;

	/* Internal flags. */
	क्रमागत cip_sfc sfc;
	अचिन्हित पूर्णांक syt_पूर्णांकerval;

	/* For a PCM substream processing. */
	काष्ठा snd_pcm_substream *pcm;
	काष्ठा work_काष्ठा period_work;
	snd_pcm_uframes_t pcm_buffer_poपूर्णांकer;
	अचिन्हित पूर्णांक pcm_period_poपूर्णांकer;

	/* To रुको क्रम first packet. */
	bool callbacked;
	रुको_queue_head_t callback_रुको;
	u32 start_cycle;

	/* For backends to process data blocks. */
	व्योम *protocol;
	amdtp_stream_process_ctx_payloads_t process_ctx_payloads;

	// For करोमुख्य.
	पूर्णांक channel;
	पूर्णांक speed;
	काष्ठा list_head list;
	काष्ठा amdtp_करोमुख्य *करोमुख्य;
पूर्ण;

पूर्णांक amdtp_stream_init(काष्ठा amdtp_stream *s, काष्ठा fw_unit *unit,
		      क्रमागत amdtp_stream_direction dir, क्रमागत cip_flags flags,
		      अचिन्हित पूर्णांक fmt,
		      amdtp_stream_process_ctx_payloads_t process_ctx_payloads,
		      अचिन्हित पूर्णांक protocol_size);
व्योम amdtp_stream_destroy(काष्ठा amdtp_stream *s);

पूर्णांक amdtp_stream_set_parameters(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक rate,
				अचिन्हित पूर्णांक data_block_quadlets);
अचिन्हित पूर्णांक amdtp_stream_get_max_payload(काष्ठा amdtp_stream *s);

व्योम amdtp_stream_update(काष्ठा amdtp_stream *s);

पूर्णांक amdtp_stream_add_pcm_hw_स्थिरraपूर्णांकs(काष्ठा amdtp_stream *s,
					काष्ठा snd_pcm_runसमय *runसमय);

व्योम amdtp_stream_pcm_prepare(काष्ठा amdtp_stream *s);
व्योम amdtp_stream_pcm_पात(काष्ठा amdtp_stream *s);

बाह्य स्थिर अचिन्हित पूर्णांक amdtp_syt_पूर्णांकervals[CIP_SFC_COUNT];
बाह्य स्थिर अचिन्हित पूर्णांक amdtp_rate_table[CIP_SFC_COUNT];

/**
 * amdtp_stream_running - check stream is running or not
 * @s: the AMDTP stream
 *
 * If this function वापसs true, the stream is running.
 */
अटल अंतरभूत bool amdtp_stream_running(काष्ठा amdtp_stream *s)
अणु
	वापस !IS_ERR(s->context);
पूर्ण

/**
 * amdtp_streaming_error - check क्रम streaming error
 * @s: the AMDTP stream
 *
 * If this function वापसs true, the stream's packet queue has stopped due to
 * an asynchronous error.
 */
अटल अंतरभूत bool amdtp_streaming_error(काष्ठा amdtp_stream *s)
अणु
	वापस s->packet_index < 0;
पूर्ण

/**
 * amdtp_stream_pcm_running - check PCM substream is running or not
 * @s: the AMDTP stream
 *
 * If this function वापसs true, PCM substream in the AMDTP stream is running.
 */
अटल अंतरभूत bool amdtp_stream_pcm_running(काष्ठा amdtp_stream *s)
अणु
	वापस !!s->pcm;
पूर्ण

/**
 * amdtp_stream_pcm_trigger - start/stop playback from a PCM device
 * @s: the AMDTP stream
 * @pcm: the PCM device to be started, or %शून्य to stop the current device
 *
 * Call this function on a running isochronous stream to enable the actual
 * transmission of PCM data.  This function should be called from the PCM
 * device's .trigger callback.
 */
अटल अंतरभूत व्योम amdtp_stream_pcm_trigger(काष्ठा amdtp_stream *s,
					    काष्ठा snd_pcm_substream *pcm)
अणु
	WRITE_ONCE(s->pcm, pcm);
पूर्ण

अटल अंतरभूत bool cip_sfc_is_base_44100(क्रमागत cip_sfc sfc)
अणु
	वापस sfc & 1;
पूर्ण

/**
 * amdtp_stream_रुको_callback - sleep till callbacked or समयout
 * @s: the AMDTP stream
 * @समयout: msec till समयout
 *
 * If this function वापस false, the AMDTP stream should be stopped.
 */
अटल अंतरभूत bool amdtp_stream_रुको_callback(काष्ठा amdtp_stream *s,
					      अचिन्हित पूर्णांक समयout)
अणु
	वापस रुको_event_समयout(s->callback_रुको,
				  s->callbacked,
				  msecs_to_jअगरfies(समयout)) > 0;
पूर्ण

काष्ठा seq_desc अणु
	अचिन्हित पूर्णांक syt_offset;
	अचिन्हित पूर्णांक data_blocks;
पूर्ण;

काष्ठा amdtp_करोमुख्य अणु
	काष्ठा list_head streams;

	अचिन्हित पूर्णांक events_per_period;
	अचिन्हित पूर्णांक events_per_buffer;

	काष्ठा amdtp_stream *irq_target;

	काष्ठा seq_desc *seq_descs;
	अचिन्हित पूर्णांक seq_size;
	अचिन्हित पूर्णांक seq_tail;

	अचिन्हित पूर्णांक data_block_state;
	अचिन्हित पूर्णांक syt_offset_state;
	अचिन्हित पूर्णांक last_syt_offset;
पूर्ण;

पूर्णांक amdtp_करोमुख्य_init(काष्ठा amdtp_करोमुख्य *d);
व्योम amdtp_करोमुख्य_destroy(काष्ठा amdtp_करोमुख्य *d);

पूर्णांक amdtp_करोमुख्य_add_stream(काष्ठा amdtp_करोमुख्य *d, काष्ठा amdtp_stream *s,
			    पूर्णांक channel, पूर्णांक speed);

पूर्णांक amdtp_करोमुख्य_start(काष्ठा amdtp_करोमुख्य *d, अचिन्हित पूर्णांक ir_delay_cycle);
व्योम amdtp_करोमुख्य_stop(काष्ठा amdtp_करोमुख्य *d);

अटल अंतरभूत पूर्णांक amdtp_करोमुख्य_set_events_per_period(काष्ठा amdtp_करोमुख्य *d,
						अचिन्हित पूर्णांक events_per_period,
						अचिन्हित पूर्णांक events_per_buffer)
अणु
	d->events_per_period = events_per_period;
	d->events_per_buffer = events_per_buffer;

	वापस 0;
पूर्ण

अचिन्हित दीर्घ amdtp_करोमुख्य_stream_pcm_poपूर्णांकer(काष्ठा amdtp_करोमुख्य *d,
					      काष्ठा amdtp_stream *s);
पूर्णांक amdtp_करोमुख्य_stream_pcm_ack(काष्ठा amdtp_करोमुख्य *d, काष्ठा amdtp_stream *s);

#पूर्ण_अगर
