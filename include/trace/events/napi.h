<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM napi

#अगर !defined(_TRACE_NAPI_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_NAPI_H

#समावेश <linux/netdevice.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/ftrace.h>

#घोषणा NO_DEV "(no_device)"

TRACE_EVENT(napi_poll,

	TP_PROTO(काष्ठा napi_काष्ठा *napi, पूर्णांक work, पूर्णांक budget),

	TP_ARGS(napi, work, budget),

	TP_STRUCT__entry(
		__field(	काष्ठा napi_काष्ठा *,	napi)
		__string(	dev_name, napi->dev ? napi->dev->name : NO_DEV)
		__field(	पूर्णांक,			work)
		__field(	पूर्णांक,			budget)
	),

	TP_fast_assign(
		__entry->napi = napi;
		__assign_str(dev_name, napi->dev ? napi->dev->name : NO_DEV);
		__entry->work = work;
		__entry->budget = budget;
	),

	TP_prपूर्णांकk("napi poll on napi struct %p for device %s work %d budget %d",
		  __entry->napi, __get_str(dev_name),
		  __entry->work, __entry->budget)
);

#अघोषित NO_DEV

#पूर्ण_अगर /* _TRACE_NAPI_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
