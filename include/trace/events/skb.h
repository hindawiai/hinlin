<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM skb

#अगर !defined(_TRACE_SKB_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_SKB_H

#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/tracepoपूर्णांक.h>

/*
 * Tracepoपूर्णांक क्रम मुक्त an sk_buff:
 */
TRACE_EVENT(kमुक्त_skb,

	TP_PROTO(काष्ठा sk_buff *skb, व्योम *location),

	TP_ARGS(skb, location),

	TP_STRUCT__entry(
		__field(	व्योम *,		skbaddr		)
		__field(	व्योम *,		location	)
		__field(	अचिन्हित लघु,	protocol	)
	),

	TP_fast_assign(
		__entry->skbaddr = skb;
		__entry->location = location;
		__entry->protocol = ntohs(skb->protocol);
	),

	TP_prपूर्णांकk("skbaddr=%p protocol=%u location=%p",
		__entry->skbaddr, __entry->protocol, __entry->location)
);

TRACE_EVENT(consume_skb,

	TP_PROTO(काष्ठा sk_buff *skb),

	TP_ARGS(skb),

	TP_STRUCT__entry(
		__field(	व्योम *,	skbaddr	)
	),

	TP_fast_assign(
		__entry->skbaddr = skb;
	),

	TP_prपूर्णांकk("skbaddr=%p", __entry->skbaddr)
);

TRACE_EVENT(skb_copy_datagram_iovec,

	TP_PROTO(स्थिर काष्ठा sk_buff *skb, पूर्णांक len),

	TP_ARGS(skb, len),

	TP_STRUCT__entry(
		__field(	स्थिर व्योम *,		skbaddr		)
		__field(	पूर्णांक,			len		)
	),

	TP_fast_assign(
		__entry->skbaddr = skb;
		__entry->len = len;
	),

	TP_prपूर्णांकk("skbaddr=%p len=%d", __entry->skbaddr, __entry->len)
);

#पूर्ण_अगर /* _TRACE_SKB_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
