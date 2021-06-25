<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Vidtv serves as a reference DVB driver and helps validate the existing APIs
 * in the media subप्रणाली. It can also aid developers working on userspace
 * applications.
 *
 * This file contains the multiplexer logic क्रम TS packets from dअगरferent
 * elementary streams
 *
 * Loosely based on libavcodec/mpegtsenc.c
 *
 * Copyright (C) 2020 Daniel W. S. Almeida
 */

#समावेश <linux/delay.h>
#समावेश <linux/dev_prपूर्णांकk.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/math64.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "vidtv_channel.h"
#समावेश "vidtv_common.h"
#समावेश "vidtv_encoder.h"
#समावेश "vidtv_mux.h"
#समावेश "vidtv_pes.h"
#समावेश "vidtv_psi.h"
#समावेश "vidtv_ts.h"

अटल काष्ठा vidtv_mux_pid_ctx
*vidtv_mux_get_pid_ctx(काष्ठा vidtv_mux *m, u16 pid)
अणु
	काष्ठा vidtv_mux_pid_ctx *ctx;

	hash_क्रम_each_possible(m->pid_ctx, ctx, h, pid)
		अगर (ctx->pid == pid)
			वापस ctx;
	वापस शून्य;
पूर्ण

अटल काष्ठा vidtv_mux_pid_ctx
*vidtv_mux_create_pid_ctx_once(काष्ठा vidtv_mux *m, u16 pid)
अणु
	काष्ठा vidtv_mux_pid_ctx *ctx;

	ctx = vidtv_mux_get_pid_ctx(m, pid);
	अगर (ctx)
		वापस ctx;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस शून्य;

	ctx->pid = pid;
	ctx->cc  = 0;
	hash_add(m->pid_ctx, &ctx->h, pid);

	वापस ctx;
पूर्ण

अटल व्योम vidtv_mux_pid_ctx_destroy(काष्ठा vidtv_mux *m)
अणु
	काष्ठा vidtv_mux_pid_ctx *ctx;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक bkt;

	hash_क्रम_each_safe(m->pid_ctx, bkt, पंचांगp, ctx, h) अणु
		hash_del(&ctx->h);
		kमुक्त(ctx);
	पूर्ण
पूर्ण

अटल पूर्णांक vidtv_mux_pid_ctx_init(काष्ठा vidtv_mux *m)
अणु
	काष्ठा vidtv_psi_table_pat_program *p = m->si.pat->program;
	u16 pid;

	hash_init(m->pid_ctx);
	/* push the pcr pid ctx */
	अगर (!vidtv_mux_create_pid_ctx_once(m, m->pcr_pid))
		वापस -ENOMEM;
	/* push the शून्य packet pid ctx */
	अगर (!vidtv_mux_create_pid_ctx_once(m, TS_शून्य_PACKET_PID))
		जाओ मुक्त;
	/* push the PAT pid ctx */
	अगर (!vidtv_mux_create_pid_ctx_once(m, VIDTV_PAT_PID))
		जाओ मुक्त;
	/* push the SDT pid ctx */
	अगर (!vidtv_mux_create_pid_ctx_once(m, VIDTV_SDT_PID))
		जाओ मुक्त;
	/* push the NIT pid ctx */
	अगर (!vidtv_mux_create_pid_ctx_once(m, VIDTV_NIT_PID))
		जाओ मुक्त;
	/* push the EIT pid ctx */
	अगर (!vidtv_mux_create_pid_ctx_once(m, VIDTV_EIT_PID))
		जाओ मुक्त;

	/* add a ctx क्रम all PMT sections */
	जबतक (p) अणु
		pid = vidtv_psi_get_pat_program_pid(p);
		vidtv_mux_create_pid_ctx_once(m, pid);
		p = p->next;
	पूर्ण

	वापस 0;

मुक्त:
	vidtv_mux_pid_ctx_destroy(m);
	वापस -ENOMEM;
पूर्ण

अटल व्योम vidtv_mux_update_clk(काष्ठा vidtv_mux *m)
अणु
	/* call this at every thपढ़ो iteration */
	u64 elapsed_समय;

	m->timing.past_jअगरfies = m->timing.current_jअगरfies;
	m->timing.current_jअगरfies = get_jअगरfies_64();

	elapsed_समय = jअगरfies_to_usecs(m->timing.current_jअगरfies -
					m->timing.past_jअगरfies);

	/* update the 27Mhz घड़ी proportionally to the elapsed समय */
	m->timing.clk += (CLOCK_UNIT_27MHZ / USEC_PER_SEC) * elapsed_समय;
पूर्ण

अटल u32 vidtv_mux_push_si(काष्ठा vidtv_mux *m)
अणु
	काष्ठा vidtv_psi_pat_ग_लिखो_args pat_args = अणु
		.buf                = m->mux_buf,
		.buf_sz             = m->mux_buf_sz,
		.pat                = m->si.pat,
	पूर्ण;
	काष्ठा vidtv_psi_pmt_ग_लिखो_args pmt_args = अणु
		.buf                = m->mux_buf,
		.buf_sz             = m->mux_buf_sz,
		.pcr_pid            = m->pcr_pid,
	पूर्ण;
	काष्ठा vidtv_psi_sdt_ग_लिखो_args sdt_args = अणु
		.buf                = m->mux_buf,
		.buf_sz             = m->mux_buf_sz,
		.sdt                = m->si.sdt,
	पूर्ण;
	काष्ठा vidtv_psi_nit_ग_लिखो_args nit_args = अणु
		.buf                = m->mux_buf,
		.buf_sz             = m->mux_buf_sz,
		.nit                = m->si.nit,

	पूर्ण;
	काष्ठा vidtv_psi_eit_ग_लिखो_args eit_args = अणु
		.buf                = m->mux_buf,
		.buf_sz             = m->mux_buf_sz,
		.eit                = m->si.eit,
	पूर्ण;
	u32 initial_offset = m->mux_buf_offset;
	काष्ठा vidtv_mux_pid_ctx *pat_ctx;
	काष्ठा vidtv_mux_pid_ctx *pmt_ctx;
	काष्ठा vidtv_mux_pid_ctx *sdt_ctx;
	काष्ठा vidtv_mux_pid_ctx *nit_ctx;
	काष्ठा vidtv_mux_pid_ctx *eit_ctx;
	u32 nbytes;
	u16 pmt_pid;
	u32 i;

	pat_ctx = vidtv_mux_get_pid_ctx(m, VIDTV_PAT_PID);
	sdt_ctx = vidtv_mux_get_pid_ctx(m, VIDTV_SDT_PID);
	nit_ctx = vidtv_mux_get_pid_ctx(m, VIDTV_NIT_PID);
	eit_ctx = vidtv_mux_get_pid_ctx(m, VIDTV_EIT_PID);

	pat_args.offset             = m->mux_buf_offset;
	pat_args.continuity_counter = &pat_ctx->cc;

	m->mux_buf_offset += vidtv_psi_pat_ग_लिखो_पूर्णांकo(&pat_args);

	क्रम (i = 0; i < m->si.pat->num_pmt; ++i) अणु
		pmt_pid = vidtv_psi_pmt_get_pid(m->si.pmt_secs[i],
						m->si.pat);

		अगर (pmt_pid > TS_LAST_VALID_PID) अणु
			dev_warn_ratelimited(m->dev,
					     "PID: %d not found\n", pmt_pid);
			जारी;
		पूर्ण

		pmt_ctx = vidtv_mux_get_pid_ctx(m, pmt_pid);

		pmt_args.offset             = m->mux_buf_offset;
		pmt_args.pmt                = m->si.pmt_secs[i];
		pmt_args.pid                = pmt_pid;
		pmt_args.continuity_counter = &pmt_ctx->cc;

		/* ग_लिखो each section पूर्णांकo buffer */
		m->mux_buf_offset += vidtv_psi_pmt_ग_लिखो_पूर्णांकo(&pmt_args);
	पूर्ण

	sdt_args.offset             = m->mux_buf_offset;
	sdt_args.continuity_counter = &sdt_ctx->cc;

	m->mux_buf_offset += vidtv_psi_sdt_ग_लिखो_पूर्णांकo(&sdt_args);

	nit_args.offset             = m->mux_buf_offset;
	nit_args.continuity_counter = &nit_ctx->cc;

	m->mux_buf_offset += vidtv_psi_nit_ग_लिखो_पूर्णांकo(&nit_args);

	eit_args.offset             = m->mux_buf_offset;
	eit_args.continuity_counter = &eit_ctx->cc;

	m->mux_buf_offset += vidtv_psi_eit_ग_लिखो_पूर्णांकo(&eit_args);

	nbytes = m->mux_buf_offset - initial_offset;

	m->num_streamed_si++;

	वापस nbytes;
पूर्ण

अटल u32 vidtv_mux_push_pcr(काष्ठा vidtv_mux *m)
अणु
	काष्ठा pcr_ग_लिखो_args args = अणुपूर्ण;
	काष्ठा vidtv_mux_pid_ctx *ctx;
	u32 nbytes = 0;

	ctx                     = vidtv_mux_get_pid_ctx(m, m->pcr_pid);
	args.dest_buf           = m->mux_buf;
	args.pid                = m->pcr_pid;
	args.buf_sz             = m->mux_buf_sz;
	args.continuity_counter = &ctx->cc;

	/* the 27Mhz घड़ी will feed both parts of the PCR bitfield */
	args.pcr = m->timing.clk;

	nbytes += vidtv_ts_pcr_ग_लिखो_पूर्णांकo(args);
	m->mux_buf_offset += nbytes;

	m->num_streamed_pcr++;

	वापस nbytes;
पूर्ण

अटल bool vidtv_mux_should_push_pcr(काष्ठा vidtv_mux *m)
अणु
	u64 next_pcr_at;

	अगर (m->num_streamed_pcr == 0)
		वापस true;

	next_pcr_at = m->timing.start_jअगरfies +
		      usecs_to_jअगरfies(m->num_streamed_pcr *
				       m->timing.pcr_period_usecs);

	वापस समय_after64(m->timing.current_jअगरfies, next_pcr_at);
पूर्ण

अटल bool vidtv_mux_should_push_si(काष्ठा vidtv_mux *m)
अणु
	u64 next_si_at;

	अगर (m->num_streamed_si == 0)
		वापस true;

	next_si_at = m->timing.start_jअगरfies +
		     usecs_to_jअगरfies(m->num_streamed_si *
				      m->timing.si_period_usecs);

	वापस समय_after64(m->timing.current_jअगरfies, next_si_at);
पूर्ण

अटल u32 vidtv_mux_packetize_access_units(काष्ठा vidtv_mux *m,
					    काष्ठा vidtv_encoder *e)
अणु
	काष्ठा pes_ग_लिखो_args args = अणु
		.dest_buf           = m->mux_buf,
		.dest_buf_sz        = m->mux_buf_sz,
		.pid                = be16_to_cpu(e->es_pid),
		.encoder_id         = e->id,
		.stream_id          = be16_to_cpu(e->stream_id),
		.send_pts           = true,  /* क्रमbidden value '01'... */
		.send_dts           = false, /* ...क्रम PTS_DTS flags    */
	पूर्ण;
	काष्ठा vidtv_access_unit *au = e->access_units;
	u32 initial_offset = m->mux_buf_offset;
	काष्ठा vidtv_mux_pid_ctx *pid_ctx;
	u32 nbytes = 0;
	u8 *buf = शून्य;

	/* see SMPTE 302M clause 6.4 */
	अगर (args.encoder_id == S302M) अणु
		args.send_dts = false;
		args.send_pts = true;
	पूर्ण

	pid_ctx = vidtv_mux_create_pid_ctx_once(m, be16_to_cpu(e->es_pid));
	args.continuity_counter = &pid_ctx->cc;

	जबतक (au) अणु
		buf                  = e->encoder_buf + au->offset;
		args.from            = buf;
		args.access_unit_len = au->nbytes;
		args.dest_offset     = m->mux_buf_offset;
		args.pts             = au->pts;
		args.pcr	     = m->timing.clk;

		m->mux_buf_offset += vidtv_pes_ग_लिखो_पूर्णांकo(&args);

		au = au->next;
	पूर्ण

	/*
	 * clear the encoder state once the ES data has been written to the mux
	 * buffer
	 */
	e->clear(e);

	nbytes = m->mux_buf_offset - initial_offset;
	वापस nbytes;
पूर्ण

अटल u32 vidtv_mux_poll_encoders(काष्ठा vidtv_mux *m)
अणु
	काष्ठा vidtv_channel *cur_chnl = m->channels;
	काष्ठा vidtv_encoder *e = शून्य;
	u32 nbytes = 0;
	u32 au_nbytes;

	जबतक (cur_chnl) अणु
		e = cur_chnl->encoders;

		जबतक (e) अणु
			e->encode(e);
			/* get the TS packets पूर्णांकo the mux buffer */
			au_nbytes = vidtv_mux_packetize_access_units(m, e);
			nbytes += au_nbytes;
			m->mux_buf_offset += au_nbytes;
			/* grab next encoder */
			e = e->next;
		पूर्ण

		/* grab the next channel */
		cur_chnl = cur_chnl->next;
	पूर्ण

	वापस nbytes;
पूर्ण

अटल u32 vidtv_mux_pad_with_nulls(काष्ठा vidtv_mux *m, u32 npkts)
अणु
	काष्ठा null_packet_ग_लिखो_args args = अणु
		.dest_buf           = m->mux_buf,
		.buf_sz             = m->mux_buf_sz,
		.dest_offset        = m->mux_buf_offset,
	पूर्ण;
	u32 initial_offset = m->mux_buf_offset;
	काष्ठा vidtv_mux_pid_ctx *ctx;
	u32 nbytes;
	u32 i;

	ctx = vidtv_mux_get_pid_ctx(m, TS_शून्य_PACKET_PID);

	args.continuity_counter = &ctx->cc;

	क्रम (i = 0; i < npkts; ++i) अणु
		m->mux_buf_offset += vidtv_ts_null_ग_लिखो_पूर्णांकo(args);
		args.dest_offset  = m->mux_buf_offset;
	पूर्ण

	nbytes = m->mux_buf_offset - initial_offset;

	/* sanity check */
	अगर (nbytes != npkts * TS_PACKET_LEN)
		dev_err_ratelimited(m->dev, "%d != %d\n",
				    nbytes, npkts * TS_PACKET_LEN);

	वापस nbytes;
पूर्ण

अटल व्योम vidtv_mux_clear(काष्ठा vidtv_mux *m)
अणु
	/* clear the packets currently in the mux */
	स_रखो(m->mux_buf, 0, m->mux_buf_sz * माप(*m->mux_buf));
	/* poपूर्णांक to the beginning of the buffer again */
	m->mux_buf_offset = 0;
पूर्ण

#घोषणा ERR_RATE 10000000
अटल व्योम vidtv_mux_tick(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vidtv_mux *m = container_of(work,
					   काष्ठा vidtv_mux,
					   mpeg_thपढ़ो);
	काष्ठा dtv_frontend_properties *c = &m->fe->dtv_property_cache;
	u32 tot_bits = 0;
	u32 nbytes;
	u32 npkts;

	जबतक (m->streaming) अणु
		nbytes = 0;

		vidtv_mux_update_clk(m);

		अगर (vidtv_mux_should_push_pcr(m))
			nbytes += vidtv_mux_push_pcr(m);

		अगर (vidtv_mux_should_push_si(m))
			nbytes += vidtv_mux_push_si(m);

		nbytes += vidtv_mux_poll_encoders(m);
		nbytes += vidtv_mux_pad_with_nulls(m, 256);

		npkts = nbytes / TS_PACKET_LEN;

		/* अगर the buffer is not aligned there is a bug somewhere */
		अगर (nbytes % TS_PACKET_LEN)
			dev_err_ratelimited(m->dev, "Misaligned buffer\n");

		अगर (m->on_new_packets_available_cb)
			m->on_new_packets_available_cb(m->priv,
						       m->mux_buf,
						       npkts);

		vidtv_mux_clear(m);

		/*
		 * Update bytes and packet counts at DVBv5 stats
		 *
		 * For now, both pre and post bit counts are identical,
		 * but post BER count can be lower than pre BER, अगर the error
		 * correction logic discards packages.
		 */
		c->pre_bit_count.stat[0].uvalue = nbytes * 8;
		c->post_bit_count.stat[0].uvalue = nbytes * 8;
		c->block_count.stat[0].uvalue += npkts;

		/*
		 * Even without any visible errors क्रम the user, the pre-BER
		 * stats usually have an error range up to 1E-6. So,
		 * add some अक्रमom error increment count to it.
		 *
		 * Please notice that this is a poor guy's implementation,
		 * as it will produce one corrected bit error every समय
		 * उच्चमान(total bytes / ERR_RATE) is incremented, without
		 * any sort of (pseuकरो-)अक्रमomness.
		 */
		tot_bits += nbytes * 8;
		अगर (tot_bits > ERR_RATE) अणु
			c->pre_bit_error.stat[0].uvalue++;
			tot_bits -= ERR_RATE;
		पूर्ण

		usleep_range(VIDTV_SLEEP_USECS, VIDTV_MAX_SLEEP_USECS);
	पूर्ण
पूर्ण

व्योम vidtv_mux_start_thपढ़ो(काष्ठा vidtv_mux *m)
अणु
	अगर (m->streaming) अणु
		dev_warn_ratelimited(m->dev, "Already streaming. Skipping.\n");
		वापस;
	पूर्ण

	m->streaming = true;
	m->timing.start_jअगरfies = get_jअगरfies_64();
	schedule_work(&m->mpeg_thपढ़ो);
पूर्ण

व्योम vidtv_mux_stop_thपढ़ो(काष्ठा vidtv_mux *m)
अणु
	अगर (m->streaming) अणु
		m->streaming = false; /* thपढ़ो will quit */
		cancel_work_sync(&m->mpeg_thपढ़ो);
	पूर्ण
पूर्ण

काष्ठा vidtv_mux *vidtv_mux_init(काष्ठा dvb_frontend *fe,
				 काष्ठा device *dev,
				 काष्ठा vidtv_mux_init_args *args)
अणु
	काष्ठा vidtv_mux *m;

	m = kzalloc(माप(*m), GFP_KERNEL);
	अगर (!m)
		वापस शून्य;

	m->dev = dev;
	m->fe = fe;
	m->timing.pcr_period_usecs = args->pcr_period_usecs;
	m->timing.si_period_usecs  = args->si_period_usecs;

	m->mux_rate_kbytes_sec = args->mux_rate_kbytes_sec;

	m->on_new_packets_available_cb = args->on_new_packets_available_cb;

	m->mux_buf = vzalloc(args->mux_buf_sz);
	अगर (!m->mux_buf)
		जाओ मुक्त_mux;

	m->mux_buf_sz = args->mux_buf_sz;

	m->pcr_pid = args->pcr_pid;
	m->transport_stream_id = args->transport_stream_id;
	m->priv = args->priv;
	m->network_id = args->network_id;
	m->network_name = kstrdup(args->network_name, GFP_KERNEL);
	m->timing.current_jअगरfies = get_jअगरfies_64();

	अगर (args->channels)
		m->channels = args->channels;
	अन्यथा
		अगर (vidtv_channels_init(m) < 0)
			जाओ मुक्त_mux_buf;

	/* will alloc data क्रम pmt_sections after initializing pat */
	अगर (vidtv_channel_si_init(m) < 0)
		जाओ मुक्त_channels;

	INIT_WORK(&m->mpeg_thपढ़ो, vidtv_mux_tick);

	अगर (vidtv_mux_pid_ctx_init(m) < 0)
		जाओ मुक्त_channel_si;

	वापस m;

मुक्त_channel_si:
	vidtv_channel_si_destroy(m);
मुक्त_channels:
	vidtv_channels_destroy(m);
मुक्त_mux_buf:
	vमुक्त(m->mux_buf);
मुक्त_mux:
	kमुक्त(m);
	वापस शून्य;
पूर्ण

व्योम vidtv_mux_destroy(काष्ठा vidtv_mux *m)
अणु
	vidtv_mux_stop_thपढ़ो(m);
	vidtv_mux_pid_ctx_destroy(m);
	vidtv_channel_si_destroy(m);
	vidtv_channels_destroy(m);
	kमुक्त(m->network_name);
	vमुक्त(m->mux_buf);
	kमुक्त(m);
पूर्ण
