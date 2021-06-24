<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_INCLUDE_PATH ../../drivers/dma-buf
#घोषणा TRACE_SYSTEM sync_trace

#अगर !defined(_TRACE_SYNC_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_SYNC_H

#समावेश "sync_debug.h"
#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(sync_समयline,
	TP_PROTO(काष्ठा sync_समयline *समयline),

	TP_ARGS(समयline),

	TP_STRUCT__entry(
			__string(name, समयline->name)
			__field(u32, value)
	),

	TP_fast_assign(
			__assign_str(name, समयline->name);
			__entry->value = समयline->value;
	),

	TP_prपूर्णांकk("name=%s value=%d", __get_str(name), __entry->value)
);

#पूर्ण_अगर /* अगर !defined(_TRACE_SYNC_H) || defined(TRACE_HEADER_MULTI_READ) */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
