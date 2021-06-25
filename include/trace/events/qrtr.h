<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM qrtr

#अगर !defined(_TRACE_QRTR_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_QRTR_H

#समावेश <linux/qrtr.h>
#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(qrtr_ns_service_announce_new,

	TP_PROTO(__le32 service, __le32 instance, __le32 node, __le32 port),

	TP_ARGS(service, instance, node, port),

	TP_STRUCT__entry(
		__field(__le32, service)
		__field(__le32, instance)
		__field(__le32, node)
		__field(__le32, port)
	),

	TP_fast_assign(
		__entry->service = service;
		__entry->instance = instance;
		__entry->node = node;
		__entry->port = port;
	),

	TP_prपूर्णांकk("advertising new server [%d:%x]@[%d:%d]",
		  __entry->service, __entry->instance, __entry->node,
		  __entry->port
	)
);

TRACE_EVENT(qrtr_ns_service_announce_del,

	TP_PROTO(__le32 service, __le32 instance, __le32 node, __le32 port),

	TP_ARGS(service, instance, node, port),

	TP_STRUCT__entry(
		__field(__le32, service)
		__field(__le32, instance)
		__field(__le32, node)
		__field(__le32, port)
	),

	TP_fast_assign(
		__entry->service = service;
		__entry->instance = instance;
		__entry->node = node;
		__entry->port = port;
	),

	TP_prपूर्णांकk("advertising removal of server [%d:%x]@[%d:%d]",
		  __entry->service, __entry->instance, __entry->node,
		  __entry->port
	)
);

TRACE_EVENT(qrtr_ns_server_add,

	TP_PROTO(__le32 service, __le32 instance, __le32 node, __le32 port),

	TP_ARGS(service, instance, node, port),

	TP_STRUCT__entry(
		__field(__le32, service)
		__field(__le32, instance)
		__field(__le32, node)
		__field(__le32, port)
	),

	TP_fast_assign(
		__entry->service = service;
		__entry->instance = instance;
		__entry->node = node;
		__entry->port = port;
	),

	TP_prपूर्णांकk("add server [%d:%x]@[%d:%d]",
		  __entry->service, __entry->instance, __entry->node,
		  __entry->port
	)
);

TRACE_EVENT(qrtr_ns_message,

	TP_PROTO(स्थिर अक्षर * स्थिर ctrl_pkt_str, __u32 sq_node, __u32 sq_port),

	TP_ARGS(ctrl_pkt_str, sq_node, sq_port),

	TP_STRUCT__entry(
		__string(ctrl_pkt_str, ctrl_pkt_str)
		__field(__u32, sq_node)
		__field(__u32, sq_port)
	),

	TP_fast_assign(
		__assign_str(ctrl_pkt_str, ctrl_pkt_str);
		__entry->sq_node = sq_node;
		__entry->sq_port = sq_port;
	),

	TP_prपूर्णांकk("%s from %d:%d",
		  __get_str(ctrl_pkt_str), __entry->sq_node, __entry->sq_port
	)
);

#पूर्ण_अगर /* _TRACE_QRTR_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
