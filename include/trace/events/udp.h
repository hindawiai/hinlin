<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM udp

#अगर !defined(_TRACE_UDP_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_UDP_H

#समावेश <linux/udp.h>
#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(udp_fail_queue_rcv_skb,

	TP_PROTO(पूर्णांक rc, काष्ठा sock *sk),

	TP_ARGS(rc, sk),

	TP_STRUCT__entry(
		__field(पूर्णांक, rc)
		__field(__u16, lport)
	),

	TP_fast_assign(
		__entry->rc = rc;
		__entry->lport = inet_sk(sk)->inet_num;
	),

	TP_prपूर्णांकk("rc=%d port=%hu", __entry->rc, __entry->lport)
);

#पूर्ण_अगर /* _TRACE_UDP_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
