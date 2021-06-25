<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर !defined(__TRACE_ATH5K_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __TRACE_ATH5K_H

#समावेश <linux/tracepoपूर्णांक.h>


#अगर !defined(CONFIG_ATH5K_TRACER) || defined(__CHECKER__)
#अघोषित TRACE_EVENT
#घोषणा TRACE_EVENT(name, proto, ...) \
अटल अंतरभूत व्योम trace_ ## name(proto) अणुपूर्ण
#पूर्ण_अगर

काष्ठा sk_buff;
काष्ठा ath5k_txq;
काष्ठा ath5k_tx_status;

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM ath5k

TRACE_EVENT(ath5k_rx,
	TP_PROTO(काष्ठा ath5k_hw *priv, काष्ठा sk_buff *skb),
	TP_ARGS(priv, skb),
	TP_STRUCT__entry(
		__field(काष्ठा ath5k_hw *, priv)
		__field(अचिन्हित दीर्घ, skbaddr)
		__dynamic_array(u8, frame, skb->len)
	),
	TP_fast_assign(
		__entry->priv = priv;
		__entry->skbaddr = (अचिन्हित दीर्घ) skb;
		स_नकल(__get_dynamic_array(frame), skb->data, skb->len);
	),
	TP_prपूर्णांकk(
		"[%p] RX skb=%lx", __entry->priv, __entry->skbaddr
	)
);

TRACE_EVENT(ath5k_tx,
	TP_PROTO(काष्ठा ath5k_hw *priv, काष्ठा sk_buff *skb,
		 काष्ठा ath5k_txq *q),

	TP_ARGS(priv, skb, q),

	TP_STRUCT__entry(
		__field(काष्ठा ath5k_hw *, priv)
		__field(अचिन्हित दीर्घ, skbaddr)
		__field(u8, qnum)
		__dynamic_array(u8, frame, skb->len)
	),

	TP_fast_assign(
		__entry->priv = priv;
		__entry->skbaddr = (अचिन्हित दीर्घ) skb;
		__entry->qnum = (u8) q->qnum;
		स_नकल(__get_dynamic_array(frame), skb->data, skb->len);
	),

	TP_prपूर्णांकk(
		"[%p] TX skb=%lx q=%d", __entry->priv, __entry->skbaddr,
		__entry->qnum
	)
);

TRACE_EVENT(ath5k_tx_complete,
	TP_PROTO(काष्ठा ath5k_hw *priv, काष्ठा sk_buff *skb,
		 काष्ठा ath5k_txq *q, काष्ठा ath5k_tx_status *ts),

	TP_ARGS(priv, skb, q, ts),

	TP_STRUCT__entry(
		__field(काष्ठा ath5k_hw *, priv)
		__field(अचिन्हित दीर्घ, skbaddr)
		__field(u8, qnum)
		__field(u8, ts_status)
		__field(s8, ts_rssi)
		__field(u8, ts_antenna)
	),

	TP_fast_assign(
		__entry->priv = priv;
		__entry->skbaddr = (अचिन्हित दीर्घ) skb;
		__entry->qnum = (u8) q->qnum;
		__entry->ts_status = ts->ts_status;
		__entry->ts_rssi =  ts->ts_rssi;
		__entry->ts_antenna = ts->ts_antenna;
	),

	TP_prपूर्णांकk(
		"[%p] TX end skb=%lx q=%d stat=%x rssi=%d ant=%x",
		__entry->priv, __entry->skbaddr, __entry->qnum,
		__entry->ts_status, __entry->ts_rssi, __entry->ts_antenna
	)
);

#पूर्ण_अगर /* __TRACE_ATH5K_H */

#अगर defined(CONFIG_ATH5K_TRACER) && !defined(__CHECKER__)

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

#समावेश <trace/define_trace.h>

#पूर्ण_अगर
