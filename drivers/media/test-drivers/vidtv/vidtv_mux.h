<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Vidtv serves as a reference DVB driver and helps validate the existing APIs
 * in the media subप्रणाली. It can also aid developers working on userspace
 * applications.
 *
 * This file contains the muxer logic क्रम TS packets from dअगरferent
 * elementary streams.
 *
 * Loosely based on libavcodec/mpegtsenc.c
 *
 * Copyright (C) 2020 Daniel W. S. Almeida
 */

#अगर_अघोषित VIDTV_MUX_H
#घोषणा VIDTV_MUX_H

#समावेश <linux/hashtable.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

#समावेश <media/dvb_frontend.h>

#समावेश "vidtv_psi.h"

/**
 * काष्ठा vidtv_mux_timing - Timing related inक्रमmation
 *
 * This is used to decide when PCR or PSI packets should be sent. This will also
 * provide storage क्रम the घड़ी, which is used to compute the value क्रम the PCR.
 *
 * @start_jअगरfies: The value of 'jiffies' when we started the mux thपढ़ो.
 * @current_jअगरfies: The value of 'jiffies' क्रम the current iteration.
 * @past_jअगरfies: The value of 'jiffies' क्रम the past iteration.
 * @clk: A 27Mhz घड़ी from which we will drive the PCR. Updated proportionally
 * on every iteration.
 * @pcr_period_usecs: How often we should send PCR packets.
 * @si_period_usecs: How often we should send PSI packets.
 */
काष्ठा vidtv_mux_timing अणु
	u64 start_jअगरfies;
	u64 current_jअगरfies;
	u64 past_jअगरfies;

	u64 clk;

	u64 pcr_period_usecs;
	u64 si_period_usecs;
पूर्ण;

/**
 * काष्ठा vidtv_mux_si - Store the PSI context.
 *
 * This is used to store the PAT, PMT sections and SDT in use by the muxer.
 *
 * The muxer acquire these by looking पूर्णांकo the hardcoded channels in
 * vidtv_channel and then periodically sends the TS packets क्रम them>
 *
 * @pat: The PAT in use by the muxer.
 * @pmt_secs: The PMT sections in use by the muxer. One क्रम each program in the PAT.
 * @sdt: The SDT in use by the muxer.
 * @nit: The NIT in use by the muxer.
 * @eit: the EIT in use by the muxer.
 */
काष्ठा vidtv_mux_si अणु
	/* the SI tables */
	काष्ठा vidtv_psi_table_pat *pat;
	काष्ठा vidtv_psi_table_pmt **pmt_secs; /* the PMT sections */
	काष्ठा vidtv_psi_table_sdt *sdt;
	काष्ठा vidtv_psi_table_nit *nit;
	काष्ठा vidtv_psi_table_eit *eit;
पूर्ण;

/**
 * काष्ठा vidtv_mux_pid_ctx - Store the context क्रम a given TS PID.
 * @pid: The TS PID.
 * @cc: The continuity counter क्रम this PID. It is incremented on every TS
 * pack and it will wrap around at 0xf0. If the decoder notices a sudden jump in
 * this counter this will trigger a discontinuity state.
 * @h: This is embedded in a hash table, mapping pid -> vidtv_mux_pid_ctx
 */
काष्ठा vidtv_mux_pid_ctx अणु
	u16 pid;
	u8 cc; /* continuity counter */
	काष्ठा hlist_node h;
पूर्ण;

/**
 * काष्ठा vidtv_mux - A muxer असलtraction loosely based in libavcodec/mpegtsenc.c
 * @fe: The frontend काष्ठाure allocated by the muxer.
 * @dev: poपूर्णांकer to काष्ठा device.
 * @timing: Keeps track of timing related inक्रमmation.
 * @mux_rate_kbytes_sec: The bit rate क्रम the TS, in kbytes.
 * @pid_ctx: A hash table to keep track of per-PID metadata.
 * @on_new_packets_available_cb: A callback to inक्रमm of new TS packets पढ़ोy.
 * @mux_buf: A poपूर्णांकer to a buffer क्रम this muxer. TS packets are stored there
 * and then passed on to the bridge driver.
 * @mux_buf_sz: The size क्रम 'mux_buf'.
 * @mux_buf_offset: The current offset पूर्णांकo 'mux_buf'.
 * @channels: The channels associated with this muxer.
 * @si: Keeps track of the PSI context.
 * @num_streamed_pcr: Number of PCR packets streamed.
 * @num_streamed_si: The number of PSI packets streamed.
 * @mpeg_thपढ़ो: Thपढ़ो responsible क्रम the muxer loop.
 * @streaming: whether 'mpeg_thread' is running.
 * @pcr_pid: The TS PID used क्रम the PSI packets. All channels will share the
 * same PCR.
 * @transport_stream_id: The transport stream ID
 * @network_id: The network ID
 * @network_name: The network name
 * @priv: Private data.
 */
काष्ठा vidtv_mux अणु
	काष्ठा dvb_frontend *fe;
	काष्ठा device *dev;

	काष्ठा vidtv_mux_timing timing;

	u32 mux_rate_kbytes_sec;

	DECLARE_HASHTABLE(pid_ctx, 3);

	व्योम (*on_new_packets_available_cb)(व्योम *priv, u8 *buf, u32 npackets);

	u8 *mux_buf;
	u32 mux_buf_sz;
	u32 mux_buf_offset;

	काष्ठा vidtv_channel  *channels;

	काष्ठा vidtv_mux_si si;
	u64 num_streamed_pcr;
	u64 num_streamed_si;

	काष्ठा work_काष्ठा mpeg_thपढ़ो;
	bool streaming;

	u16 pcr_pid;
	u16 transport_stream_id;
	u16 network_id;
	अक्षर *network_name;
	व्योम *priv;
पूर्ण;

/**
 * काष्ठा vidtv_mux_init_args - Arguments used to inix the muxer.
 * @mux_rate_kbytes_sec: The bit rate क्रम the TS, in kbytes.
 * @on_new_packets_available_cb: A callback to inक्रमm of new TS packets पढ़ोy.
 * @mux_buf_sz: The size क्रम 'mux_buf'.
 * @pcr_period_usecs: How often we should send PCR packets.
 * @si_period_usecs: How often we should send PSI packets.
 * @pcr_pid: The TS PID used क्रम the PSI packets. All channels will share the
 * same PCR.
 * @transport_stream_id: The transport stream ID
 * @channels: an optional list of channels to use
 * @network_id: The network ID
 * @network_name: The network name
 * @priv: Private data.
 */
काष्ठा vidtv_mux_init_args अणु
	u32 mux_rate_kbytes_sec;
	व्योम (*on_new_packets_available_cb)(व्योम *priv, u8 *buf, u32 npackets);
	u32 mux_buf_sz;
	u64 pcr_period_usecs;
	u64 si_period_usecs;
	u16 pcr_pid;
	u16 transport_stream_id;
	काष्ठा vidtv_channel *channels;
	u16 network_id;
	अक्षर *network_name;
	व्योम *priv;
पूर्ण;

काष्ठा vidtv_mux *vidtv_mux_init(काष्ठा dvb_frontend *fe,
				 काष्ठा device *dev,
				 काष्ठा vidtv_mux_init_args *args);
व्योम vidtv_mux_destroy(काष्ठा vidtv_mux *m);

व्योम vidtv_mux_start_thपढ़ो(काष्ठा vidtv_mux *m);
व्योम vidtv_mux_stop_thपढ़ो(काष्ठा vidtv_mux *m);

#पूर्ण_अगर //VIDTV_MUX_H
