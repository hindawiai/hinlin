<शैली गुरु>
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM qdisc

#अगर !defined(_TRACE_QDISC_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_QDISC_H

#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/pkt_sched.h>
#समावेश <net/sch_generic.h>

TRACE_EVENT(qdisc_dequeue,

	TP_PROTO(काष्ठा Qdisc *qdisc, स्थिर काष्ठा netdev_queue *txq,
		 पूर्णांक packets, काष्ठा sk_buff *skb),

	TP_ARGS(qdisc, txq, packets, skb),

	TP_STRUCT__entry(
		__field(	काष्ठा Qdisc *,		qdisc	)
		__field(स्थिर	काष्ठा netdev_queue *,	txq	)
		__field(	पूर्णांक,			packets	)
		__field(	व्योम *,			skbaddr	)
		__field(	पूर्णांक,			अगरindex	)
		__field(	u32,			handle	)
		__field(	u32,			parent	)
		__field(	अचिन्हित दीर्घ,		txq_state)
	),

	/* skb==शून्य indicate packets dequeued was 0, even when packets==1 */
	TP_fast_assign(
		__entry->qdisc		= qdisc;
		__entry->txq		= txq;
		__entry->packets	= skb ? packets : 0;
		__entry->skbaddr	= skb;
		__entry->अगरindex	= txq->dev ? txq->dev->अगरindex : 0;
		__entry->handle		= qdisc->handle;
		__entry->parent		= qdisc->parent;
		__entry->txq_state	= txq->state;
	),

	TP_prपूर्णांकk("dequeue ifindex=%d qdisc handle=0x%X parent=0x%X txq_state=0x%lX packets=%d skbaddr=%p",
		  __entry->अगरindex, __entry->handle, __entry->parent,
		  __entry->txq_state, __entry->packets, __entry->skbaddr )
);

TRACE_EVENT(qdisc_reset,

	TP_PROTO(काष्ठा Qdisc *q),

	TP_ARGS(q),

	TP_STRUCT__entry(
		__string(	dev,		qdisc_dev(q)	)
		__string(	kind,		q->ops->id	)
		__field(	u32,		parent		)
		__field(	u32,		handle		)
	),

	TP_fast_assign(
		__assign_str(dev, qdisc_dev(q));
		__assign_str(kind, q->ops->id);
		__entry->parent = q->parent;
		__entry->handle = q->handle;
	),

	TP_prपूर्णांकk("dev=%s kind=%s parent=%x:%x handle=%x:%x", __get_str(dev),
		  __get_str(kind), TC_H_MAJ(__entry->parent) >> 16, TC_H_MIN(__entry->parent),
		  TC_H_MAJ(__entry->handle) >> 16, TC_H_MIN(__entry->handle))
);

TRACE_EVENT(qdisc_destroy,

	TP_PROTO(काष्ठा Qdisc *q),

	TP_ARGS(q),

	TP_STRUCT__entry(
		__string(	dev,		qdisc_dev(q)	)
		__string(	kind,		q->ops->id	)
		__field(	u32,		parent		)
		__field(	u32,		handle		)
	),

	TP_fast_assign(
		__assign_str(dev, qdisc_dev(q));
		__assign_str(kind, q->ops->id);
		__entry->parent = q->parent;
		__entry->handle = q->handle;
	),

	TP_prपूर्णांकk("dev=%s kind=%s parent=%x:%x handle=%x:%x", __get_str(dev),
		  __get_str(kind), TC_H_MAJ(__entry->parent) >> 16, TC_H_MIN(__entry->parent),
		  TC_H_MAJ(__entry->handle) >> 16, TC_H_MIN(__entry->handle))
);

TRACE_EVENT(qdisc_create,

	TP_PROTO(स्थिर काष्ठा Qdisc_ops *ops, काष्ठा net_device *dev, u32 parent),

	TP_ARGS(ops, dev, parent),

	TP_STRUCT__entry(
		__string(	dev,		dev->name	)
		__string(	kind,		ops->id		)
		__field(	u32,		parent		)
	),

	TP_fast_assign(
		__assign_str(dev, dev->name);
		__assign_str(kind, ops->id);
		__entry->parent = parent;
	),

	TP_prपूर्णांकk("dev=%s kind=%s parent=%x:%x",
		  __get_str(dev), __get_str(kind),
		  TC_H_MAJ(__entry->parent) >> 16, TC_H_MIN(__entry->parent))
);

#पूर्ण_अगर /* _TRACE_QDISC_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
