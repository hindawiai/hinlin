<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM percpu

#अगर !defined(_TRACE_PERCPU_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_PERCPU_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(percpu_alloc_percpu,

	TP_PROTO(bool reserved, bool is_atomic, माप_प्रकार size,
		 माप_प्रकार align, व्योम *base_addr, पूर्णांक off, व्योम __percpu *ptr),

	TP_ARGS(reserved, is_atomic, size, align, base_addr, off, ptr),

	TP_STRUCT__entry(
		__field(	bool,			reserved	)
		__field(	bool,			is_atomic	)
		__field(	माप_प्रकार,			size		)
		__field(	माप_प्रकार,			align		)
		__field(	व्योम *,			base_addr	)
		__field(	पूर्णांक,			off		)
		__field(	व्योम __percpu *,	ptr		)
	),

	TP_fast_assign(
		__entry->reserved	= reserved;
		__entry->is_atomic	= is_atomic;
		__entry->size		= size;
		__entry->align		= align;
		__entry->base_addr	= base_addr;
		__entry->off		= off;
		__entry->ptr		= ptr;
	),

	TP_prपूर्णांकk("reserved=%d is_atomic=%d size=%zu align=%zu base_addr=%p off=%d ptr=%p",
		  __entry->reserved, __entry->is_atomic,
		  __entry->size, __entry->align,
		  __entry->base_addr, __entry->off, __entry->ptr)
);

TRACE_EVENT(percpu_मुक्त_percpu,

	TP_PROTO(व्योम *base_addr, पूर्णांक off, व्योम __percpu *ptr),

	TP_ARGS(base_addr, off, ptr),

	TP_STRUCT__entry(
		__field(	व्योम *,			base_addr	)
		__field(	पूर्णांक,			off		)
		__field(	व्योम __percpu *,	ptr		)
	),

	TP_fast_assign(
		__entry->base_addr	= base_addr;
		__entry->off		= off;
		__entry->ptr		= ptr;
	),

	TP_prपूर्णांकk("base_addr=%p off=%d ptr=%p",
		__entry->base_addr, __entry->off, __entry->ptr)
);

TRACE_EVENT(percpu_alloc_percpu_fail,

	TP_PROTO(bool reserved, bool is_atomic, माप_प्रकार size, माप_प्रकार align),

	TP_ARGS(reserved, is_atomic, size, align),

	TP_STRUCT__entry(
		__field(	bool,	reserved	)
		__field(	bool,	is_atomic	)
		__field(	माप_प्रकार,	size		)
		__field(	माप_प्रकार, align		)
	),

	TP_fast_assign(
		__entry->reserved	= reserved;
		__entry->is_atomic	= is_atomic;
		__entry->size		= size;
		__entry->align		= align;
	),

	TP_prपूर्णांकk("reserved=%d is_atomic=%d size=%zu align=%zu",
		  __entry->reserved, __entry->is_atomic,
		  __entry->size, __entry->align)
);

TRACE_EVENT(percpu_create_chunk,

	TP_PROTO(व्योम *base_addr),

	TP_ARGS(base_addr),

	TP_STRUCT__entry(
		__field(	व्योम *, base_addr	)
	),

	TP_fast_assign(
		__entry->base_addr	= base_addr;
	),

	TP_prपूर्णांकk("base_addr=%p", __entry->base_addr)
);

TRACE_EVENT(percpu_destroy_chunk,

	TP_PROTO(व्योम *base_addr),

	TP_ARGS(base_addr),

	TP_STRUCT__entry(
		__field(	व्योम *,	base_addr	)
	),

	TP_fast_assign(
		__entry->base_addr	= base_addr;
	),

	TP_prपूर्णांकk("base_addr=%p", __entry->base_addr)
);

#पूर्ण_अगर /* _TRACE_PERCPU_H */

#समावेश <trace/define_trace.h>
