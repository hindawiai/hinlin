<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM vb2

#अगर !defined(_TRACE_VB2_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_VB2_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <media/videobuf2-core.h>

DECLARE_EVENT_CLASS(vb2_event_class,
	TP_PROTO(काष्ठा vb2_queue *q, काष्ठा vb2_buffer *vb),
	TP_ARGS(q, vb),

	TP_STRUCT__entry(
		__field(व्योम *, owner)
		__field(u32, queued_count)
		__field(पूर्णांक, owned_by_drv_count)
		__field(u32, index)
		__field(u32, type)
		__field(u32, bytesused)
		__field(u64, बारtamp)
	),

	TP_fast_assign(
		__entry->owner = q->owner;
		__entry->queued_count = q->queued_count;
		__entry->owned_by_drv_count =
			atomic_पढ़ो(&q->owned_by_drv_count);
		__entry->index = vb->index;
		__entry->type = vb->type;
		__entry->bytesused = vb->planes[0].bytesused;
		__entry->बारtamp = vb->बारtamp;
	),

	TP_prपूर्णांकk("owner = %p, queued = %u, owned_by_drv = %d, index = %u, "
		  "type = %u, bytesused = %u, timestamp = %llu", __entry->owner,
		  __entry->queued_count,
		  __entry->owned_by_drv_count,
		  __entry->index, __entry->type,
		  __entry->bytesused,
		  __entry->बारtamp
	)
)

DEFINE_EVENT(vb2_event_class, vb2_buf_करोne,
	TP_PROTO(काष्ठा vb2_queue *q, काष्ठा vb2_buffer *vb),
	TP_ARGS(q, vb)
);

DEFINE_EVENT(vb2_event_class, vb2_buf_queue,
	TP_PROTO(काष्ठा vb2_queue *q, काष्ठा vb2_buffer *vb),
	TP_ARGS(q, vb)
);

DEFINE_EVENT(vb2_event_class, vb2_dqbuf,
	TP_PROTO(काष्ठा vb2_queue *q, काष्ठा vb2_buffer *vb),
	TP_ARGS(q, vb)
);

DEFINE_EVENT(vb2_event_class, vb2_qbuf,
	TP_PROTO(काष्ठा vb2_queue *q, काष्ठा vb2_buffer *vb),
	TP_ARGS(q, vb)
);

#पूर्ण_अगर /* अगर !defined(_TRACE_VB2_H) || defined(TRACE_HEADER_MULTI_READ) */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
