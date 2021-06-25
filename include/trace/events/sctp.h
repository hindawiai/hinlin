<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM sctp

#अगर !defined(_TRACE_SCTP_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_SCTP_H

#समावेश <net/sctp/काष्ठाs.h>
#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(sctp_probe_path,

	TP_PROTO(काष्ठा sctp_transport *sp,
		 स्थिर काष्ठा sctp_association *asoc),

	TP_ARGS(sp, asoc),

	TP_STRUCT__entry(
		__field(__u64, asoc)
		__field(__u32, primary)
		__array(__u8, ipaddr, माप(जोड़ sctp_addr))
		__field(__u32, state)
		__field(__u32, cwnd)
		__field(__u32, ssthresh)
		__field(__u32, flight_size)
		__field(__u32, partial_bytes_acked)
		__field(__u32, pathmtu)
	),

	TP_fast_assign(
		__entry->asoc = (अचिन्हित दीर्घ)asoc;
		__entry->primary = (sp == asoc->peer.primary_path);
		स_नकल(__entry->ipaddr, &sp->ipaddr, माप(जोड़ sctp_addr));
		__entry->state = sp->state;
		__entry->cwnd = sp->cwnd;
		__entry->ssthresh = sp->ssthresh;
		__entry->flight_size = sp->flight_size;
		__entry->partial_bytes_acked = sp->partial_bytes_acked;
		__entry->pathmtu = sp->pathmtu;
	),

	TP_prपूर्णांकk("asoc=%#llx%s ipaddr=%pISpc state=%u cwnd=%u ssthresh=%u "
		  "flight_size=%u partial_bytes_acked=%u pathmtu=%u",
		  __entry->asoc, __entry->primary ? "(*)" : "",
		  __entry->ipaddr, __entry->state, __entry->cwnd,
		  __entry->ssthresh, __entry->flight_size,
		  __entry->partial_bytes_acked, __entry->pathmtu)
);

TRACE_EVENT(sctp_probe,

	TP_PROTO(स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
		 स्थिर काष्ठा sctp_association *asoc,
		 काष्ठा sctp_chunk *chunk),

	TP_ARGS(ep, asoc, chunk),

	TP_STRUCT__entry(
		__field(__u64, asoc)
		__field(__u32, mark)
		__field(__u16, bind_port)
		__field(__u16, peer_port)
		__field(__u32, pathmtu)
		__field(__u32, rwnd)
		__field(__u16, unack_data)
	),

	TP_fast_assign(
		काष्ठा sk_buff *skb = chunk->skb;

		__entry->asoc = (अचिन्हित दीर्घ)asoc;
		__entry->mark = skb->mark;
		__entry->bind_port = ep->base.bind_addr.port;
		__entry->peer_port = asoc->peer.port;
		__entry->pathmtu = asoc->pathmtu;
		__entry->rwnd = asoc->peer.rwnd;
		__entry->unack_data = asoc->unack_data;
	),

	TP_prपूर्णांकk("asoc=%#llx mark=%#x bind_port=%d peer_port=%d pathmtu=%d "
		  "rwnd=%u unack_data=%d",
		  __entry->asoc, __entry->mark, __entry->bind_port,
		  __entry->peer_port, __entry->pathmtu, __entry->rwnd,
		  __entry->unack_data)
);

#पूर्ण_अगर /* _TRACE_SCTP_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
