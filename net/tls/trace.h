<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2019 Netronome Systems, Inc. */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM tls

#अगर !defined(_TLS_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TLS_TRACE_H_

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/tracepoपूर्णांक.h>

काष्ठा sock;

TRACE_EVENT(tls_device_offload_set,

	TP_PROTO(काष्ठा sock *sk, पूर्णांक dir, u32 tcp_seq, u8 *rec_no, पूर्णांक ret),

	TP_ARGS(sk, dir, tcp_seq, rec_no, ret),

	TP_STRUCT__entry(
		__field(	काष्ठा sock *,	sk		)
		__field(	u64,		rec_no		)
		__field(	पूर्णांक,		dir		)
		__field(	u32,		tcp_seq		)
		__field(	पूर्णांक,		ret		)
	),

	TP_fast_assign(
		__entry->sk = sk;
		__entry->rec_no = get_unaligned_be64(rec_no);
		__entry->dir = dir;
		__entry->tcp_seq = tcp_seq;
		__entry->ret = ret;
	),

	TP_prपूर्णांकk(
		"sk=%p direction=%d tcp_seq=%u rec_no=%llu ret=%d",
		__entry->sk, __entry->dir, __entry->tcp_seq, __entry->rec_no,
		__entry->ret
	)
);

TRACE_EVENT(tls_device_decrypted,

	TP_PROTO(काष्ठा sock *sk, u32 tcp_seq, u8 *rec_no, u32 rec_len,
		 bool encrypted, bool decrypted),

	TP_ARGS(sk, tcp_seq, rec_no, rec_len, encrypted, decrypted),

	TP_STRUCT__entry(
		__field(	काष्ठा sock *,	sk		)
		__field(	u64,		rec_no		)
		__field(	u32,		tcp_seq		)
		__field(	u32,		rec_len		)
		__field(	bool,		encrypted	)
		__field(	bool,		decrypted	)
	),

	TP_fast_assign(
		__entry->sk = sk;
		__entry->rec_no = get_unaligned_be64(rec_no);
		__entry->tcp_seq = tcp_seq;
		__entry->rec_len = rec_len;
		__entry->encrypted = encrypted;
		__entry->decrypted = decrypted;
	),

	TP_prपूर्णांकk(
		"sk=%p tcp_seq=%u rec_no=%llu len=%u encrypted=%d decrypted=%d",
		__entry->sk, __entry->tcp_seq,
		__entry->rec_no, __entry->rec_len,
		__entry->encrypted, __entry->decrypted
	)
);

TRACE_EVENT(tls_device_rx_resync_send,

	TP_PROTO(काष्ठा sock *sk, u32 tcp_seq, u8 *rec_no, पूर्णांक sync_type),

	TP_ARGS(sk, tcp_seq, rec_no, sync_type),

	TP_STRUCT__entry(
		__field(	काष्ठा sock *,	sk		)
		__field(	u64,		rec_no		)
		__field(	u32,		tcp_seq		)
		__field(	पूर्णांक,		sync_type	)
	),

	TP_fast_assign(
		__entry->sk = sk;
		__entry->rec_no = get_unaligned_be64(rec_no);
		__entry->tcp_seq = tcp_seq;
		__entry->sync_type = sync_type;
	),

	TP_prपूर्णांकk(
		"sk=%p tcp_seq=%u rec_no=%llu sync_type=%d",
		__entry->sk, __entry->tcp_seq, __entry->rec_no,
		__entry->sync_type
	)
);

TRACE_EVENT(tls_device_rx_resync_nh_schedule,

	TP_PROTO(काष्ठा sock *sk),

	TP_ARGS(sk),

	TP_STRUCT__entry(
		__field(	काष्ठा sock *,	sk		)
	),

	TP_fast_assign(
		__entry->sk = sk;
	),

	TP_prपूर्णांकk(
		"sk=%p", __entry->sk
	)
);

TRACE_EVENT(tls_device_rx_resync_nh_delay,

	TP_PROTO(काष्ठा sock *sk, u32 sock_data, u32 rec_len),

	TP_ARGS(sk, sock_data, rec_len),

	TP_STRUCT__entry(
		__field(	काष्ठा sock *,	sk		)
		__field(	u32,		sock_data	)
		__field(	u32,		rec_len		)
	),

	TP_fast_assign(
		__entry->sk = sk;
		__entry->sock_data = sock_data;
		__entry->rec_len = rec_len;
	),

	TP_prपूर्णांकk(
		"sk=%p sock_data=%u rec_len=%u",
		__entry->sk, __entry->sock_data, __entry->rec_len
	)
);

TRACE_EVENT(tls_device_tx_resync_req,

	TP_PROTO(काष्ठा sock *sk, u32 tcp_seq, u32 exp_tcp_seq),

	TP_ARGS(sk, tcp_seq, exp_tcp_seq),

	TP_STRUCT__entry(
		__field(	काष्ठा sock *,	sk		)
		__field(	u32,		tcp_seq		)
		__field(	u32,		exp_tcp_seq	)
	),

	TP_fast_assign(
		__entry->sk = sk;
		__entry->tcp_seq = tcp_seq;
		__entry->exp_tcp_seq = exp_tcp_seq;
	),

	TP_prपूर्णांकk(
		"sk=%p tcp_seq=%u exp_tcp_seq=%u",
		__entry->sk, __entry->tcp_seq, __entry->exp_tcp_seq
	)
);

TRACE_EVENT(tls_device_tx_resync_send,

	TP_PROTO(काष्ठा sock *sk, u32 tcp_seq, u8 *rec_no),

	TP_ARGS(sk, tcp_seq, rec_no),

	TP_STRUCT__entry(
		__field(	काष्ठा sock *,	sk		)
		__field(	u64,		rec_no		)
		__field(	u32,		tcp_seq		)
	),

	TP_fast_assign(
		__entry->sk = sk;
		__entry->rec_no = get_unaligned_be64(rec_no);
		__entry->tcp_seq = tcp_seq;
	),

	TP_prपूर्णांकk(
		"sk=%p tcp_seq=%u rec_no=%llu",
		__entry->sk, __entry->tcp_seq, __entry->rec_no
	)
);

#पूर्ण_अगर /* _TLS_TRACE_H_ */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

#समावेश <trace/define_trace.h>
