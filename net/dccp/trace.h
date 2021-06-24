<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM dccp

#अगर !defined(_TRACE_DCCP_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_DCCP_H

#समावेश <net/sock.h>
#समावेश "dccp.h"
#समावेश "ccids/ccid3.h"
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <trace/events/net_probe_common.h>

TRACE_EVENT(dccp_probe,

	TP_PROTO(काष्ठा sock *sk, माप_प्रकार size),

	TP_ARGS(sk, size),

	TP_STRUCT__entry(
		/* sockaddr_in6 is always bigger than sockaddr_in */
		__array(__u8, saddr, माप(काष्ठा sockaddr_in6))
		__array(__u8, daddr, माप(काष्ठा sockaddr_in6))
		__field(__u16, sport)
		__field(__u16, dport)
		__field(__u16, size)
		__field(__u16, tx_s)
		__field(__u32, tx_rtt)
		__field(__u32, tx_p)
		__field(__u32, tx_x_calc)
		__field(__u64, tx_x_recv)
		__field(__u64, tx_x)
		__field(__u32, tx_t_ipi)
	),

	TP_fast_assign(
		स्थिर काष्ठा inet_sock *inet = inet_sk(sk);
		काष्ठा ccid3_hc_tx_sock *hc = शून्य;

		अगर (ccid_get_current_tx_ccid(dccp_sk(sk)) == DCCPC_CCID3)
			hc = ccid3_hc_tx_sk(sk);

		स_रखो(__entry->saddr, 0, माप(काष्ठा sockaddr_in6));
		स_रखो(__entry->daddr, 0, माप(काष्ठा sockaddr_in6));

		TP_STORE_ADDR_PORTS(__entry, inet, sk);

		/* For filtering use */
		__entry->sport = ntohs(inet->inet_sport);
		__entry->dport = ntohs(inet->inet_dport);

		__entry->size = size;
		अगर (hc) अणु
			__entry->tx_s = hc->tx_s;
			__entry->tx_rtt = hc->tx_rtt;
			__entry->tx_p = hc->tx_p;
			__entry->tx_x_calc = hc->tx_x_calc;
			__entry->tx_x_recv = hc->tx_x_recv >> 6;
			__entry->tx_x = hc->tx_x >> 6;
			__entry->tx_t_ipi = hc->tx_t_ipi;
		पूर्ण अन्यथा अणु
			__entry->tx_s = 0;
			स_रखो(&__entry->tx_rtt, 0, (व्योम *)&__entry->tx_t_ipi -
			       (व्योम *)&__entry->tx_rtt +
			       माप(__entry->tx_t_ipi));
		पूर्ण
	),

	TP_prपूर्णांकk("src=%pISpc dest=%pISpc size=%d tx_s=%d tx_rtt=%d "
		  "tx_p=%d tx_x_calc=%u tx_x_recv=%llu tx_x=%llu tx_t_ipi=%d",
		  __entry->saddr, __entry->daddr, __entry->size,
		  __entry->tx_s, __entry->tx_rtt, __entry->tx_p,
		  __entry->tx_x_calc, __entry->tx_x_recv, __entry->tx_x,
		  __entry->tx_t_ipi)
);

#पूर्ण_अगर /* _TRACE_TCP_H */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace
#समावेश <trace/define_trace.h>
