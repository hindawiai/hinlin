<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Trace poपूर्णांक definitions क्रम the RDMA Connect Manager.
 *
 * Author: Chuck Lever <chuck.lever@oracle.com>
 *
 * Copyright (c) 2019, Oracle and/or its affiliates. All rights reserved.
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM rdma_cma

#अगर !defined(_TRACE_RDMA_CMA_H) || defined(TRACE_HEADER_MULTI_READ)

#घोषणा _TRACE_RDMA_CMA_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <trace/events/rdma.h>


DECLARE_EVENT_CLASS(cma_fsm_class,
	TP_PROTO(
		स्थिर काष्ठा rdma_id_निजी *id_priv
	),

	TP_ARGS(id_priv),

	TP_STRUCT__entry(
		__field(u32, cm_id)
		__field(u32, tos)
		__array(अचिन्हित अक्षर, srcaddr, माप(काष्ठा sockaddr_in6))
		__array(अचिन्हित अक्षर, dstaddr, माप(काष्ठा sockaddr_in6))
	),

	TP_fast_assign(
		__entry->cm_id = id_priv->res.id;
		__entry->tos = id_priv->tos;
		स_नकल(__entry->srcaddr, &id_priv->id.route.addr.src_addr,
		       माप(काष्ठा sockaddr_in6));
		स_नकल(__entry->dstaddr, &id_priv->id.route.addr.dst_addr,
		       माप(काष्ठा sockaddr_in6));
	),

	TP_prपूर्णांकk("cm.id=%u src=%pISpc dst=%pISpc tos=%u",
		__entry->cm_id, __entry->srcaddr, __entry->dstaddr, __entry->tos
	)
);

#घोषणा DEFINE_CMA_FSM_EVENT(name)						\
		DEFINE_EVENT(cma_fsm_class, cm_##name,				\
				TP_PROTO(					\
					स्थिर काष्ठा rdma_id_निजी *id_priv	\
				),						\
				TP_ARGS(id_priv))

DEFINE_CMA_FSM_EVENT(send_rtu);
DEFINE_CMA_FSM_EVENT(send_rej);
DEFINE_CMA_FSM_EVENT(send_mra);
DEFINE_CMA_FSM_EVENT(send_sidr_req);
DEFINE_CMA_FSM_EVENT(send_sidr_rep);
DEFINE_CMA_FSM_EVENT(disconnect);
DEFINE_CMA_FSM_EVENT(sent_drep);
DEFINE_CMA_FSM_EVENT(sent_dreq);
DEFINE_CMA_FSM_EVENT(id_destroy);

TRACE_EVENT(cm_id_attach,
	TP_PROTO(
		स्थिर काष्ठा rdma_id_निजी *id_priv,
		स्थिर काष्ठा ib_device *device
	),

	TP_ARGS(id_priv, device),

	TP_STRUCT__entry(
		__field(u32, cm_id)
		__array(अचिन्हित अक्षर, srcaddr, माप(काष्ठा sockaddr_in6))
		__array(अचिन्हित अक्षर, dstaddr, माप(काष्ठा sockaddr_in6))
		__string(devname, device->name)
	),

	TP_fast_assign(
		__entry->cm_id = id_priv->res.id;
		स_नकल(__entry->srcaddr, &id_priv->id.route.addr.src_addr,
		       माप(काष्ठा sockaddr_in6));
		स_नकल(__entry->dstaddr, &id_priv->id.route.addr.dst_addr,
		       माप(काष्ठा sockaddr_in6));
		__assign_str(devname, device->name);
	),

	TP_prपूर्णांकk("cm.id=%u src=%pISpc dst=%pISpc device=%s",
		__entry->cm_id, __entry->srcaddr, __entry->dstaddr,
		__get_str(devname)
	)
);

DECLARE_EVENT_CLASS(cma_qp_class,
	TP_PROTO(
		स्थिर काष्ठा rdma_id_निजी *id_priv
	),

	TP_ARGS(id_priv),

	TP_STRUCT__entry(
		__field(u32, cm_id)
		__field(u32, tos)
		__field(u32, qp_num)
		__array(अचिन्हित अक्षर, srcaddr, माप(काष्ठा sockaddr_in6))
		__array(अचिन्हित अक्षर, dstaddr, माप(काष्ठा sockaddr_in6))
	),

	TP_fast_assign(
		__entry->cm_id = id_priv->res.id;
		__entry->tos = id_priv->tos;
		__entry->qp_num = id_priv->qp_num;
		स_नकल(__entry->srcaddr, &id_priv->id.route.addr.src_addr,
		       माप(काष्ठा sockaddr_in6));
		स_नकल(__entry->dstaddr, &id_priv->id.route.addr.dst_addr,
		       माप(काष्ठा sockaddr_in6));
	),

	TP_prपूर्णांकk("cm.id=%u src=%pISpc dst=%pISpc tos=%u qp_num=%u",
		__entry->cm_id, __entry->srcaddr, __entry->dstaddr, __entry->tos,
		__entry->qp_num
	)
);

#घोषणा DEFINE_CMA_QP_EVENT(name)						\
		DEFINE_EVENT(cma_qp_class, cm_##name,				\
				TP_PROTO(					\
					स्थिर काष्ठा rdma_id_निजी *id_priv	\
				),						\
				TP_ARGS(id_priv))

DEFINE_CMA_QP_EVENT(send_req);
DEFINE_CMA_QP_EVENT(send_rep);
DEFINE_CMA_QP_EVENT(qp_destroy);

/*
 * क्रमागत ib_wp_type, from include/rdma/ib_verbs.h
 */
#घोषणा IB_QP_TYPE_LIST				\
	ib_qp_type(SMI)				\
	ib_qp_type(GSI)				\
	ib_qp_type(RC)				\
	ib_qp_type(UC)				\
	ib_qp_type(UD)				\
	ib_qp_type(RAW_IPV6)			\
	ib_qp_type(RAW_ETHERTYPE)		\
	ib_qp_type(RAW_PACKET)			\
	ib_qp_type(XRC_INI)			\
	ib_qp_type_end(XRC_TGT)

#अघोषित ib_qp_type
#अघोषित ib_qp_type_end

#घोषणा ib_qp_type(x)		TRACE_DEFINE_ENUM(IB_QPT_##x);
#घोषणा ib_qp_type_end(x)	TRACE_DEFINE_ENUM(IB_QPT_##x);

IB_QP_TYPE_LIST

#अघोषित ib_qp_type
#अघोषित ib_qp_type_end

#घोषणा ib_qp_type(x)		अणु IB_QPT_##x, #x पूर्ण,
#घोषणा ib_qp_type_end(x)	अणु IB_QPT_##x, #x पूर्ण

#घोषणा rdma_show_qp_type(x) \
		__prपूर्णांक_symbolic(x, IB_QP_TYPE_LIST)


TRACE_EVENT(cm_qp_create,
	TP_PROTO(
		स्थिर काष्ठा rdma_id_निजी *id_priv,
		स्थिर काष्ठा ib_pd *pd,
		स्थिर काष्ठा ib_qp_init_attr *qp_init_attr,
		पूर्णांक rc
	),

	TP_ARGS(id_priv, pd, qp_init_attr, rc),

	TP_STRUCT__entry(
		__field(u32, cm_id)
		__field(u32, pd_id)
		__field(u32, tos)
		__field(u32, qp_num)
		__field(u32, send_wr)
		__field(u32, recv_wr)
		__field(पूर्णांक, rc)
		__field(अचिन्हित दीर्घ, qp_type)
		__array(अचिन्हित अक्षर, srcaddr, माप(काष्ठा sockaddr_in6))
		__array(अचिन्हित अक्षर, dstaddr, माप(काष्ठा sockaddr_in6))
	),

	TP_fast_assign(
		__entry->cm_id = id_priv->res.id;
		__entry->pd_id = pd->res.id;
		__entry->tos = id_priv->tos;
		__entry->send_wr = qp_init_attr->cap.max_send_wr;
		__entry->recv_wr = qp_init_attr->cap.max_recv_wr;
		__entry->rc = rc;
		अगर (!rc) अणु
			__entry->qp_num = id_priv->qp_num;
			__entry->qp_type = id_priv->id.qp_type;
		पूर्ण अन्यथा अणु
			__entry->qp_num = 0;
			__entry->qp_type = 0;
		पूर्ण
		स_नकल(__entry->srcaddr, &id_priv->id.route.addr.src_addr,
		       माप(काष्ठा sockaddr_in6));
		स_नकल(__entry->dstaddr, &id_priv->id.route.addr.dst_addr,
		       माप(काष्ठा sockaddr_in6));
	),

	TP_prपूर्णांकk("cm.id=%u src=%pISpc dst=%pISpc tos=%u pd.id=%u qp_type=%s"
		" send_wr=%u recv_wr=%u qp_num=%u rc=%d",
		__entry->cm_id, __entry->srcaddr, __entry->dstaddr,
		__entry->tos, __entry->pd_id,
		rdma_show_qp_type(__entry->qp_type), __entry->send_wr,
		__entry->recv_wr, __entry->qp_num, __entry->rc
	)
);

TRACE_EVENT(cm_req_handler,
	TP_PROTO(
		स्थिर काष्ठा rdma_id_निजी *id_priv,
		पूर्णांक event
	),

	TP_ARGS(id_priv, event),

	TP_STRUCT__entry(
		__field(u32, cm_id)
		__field(u32, tos)
		__field(अचिन्हित दीर्घ, event)
		__array(अचिन्हित अक्षर, srcaddr, माप(काष्ठा sockaddr_in6))
		__array(अचिन्हित अक्षर, dstaddr, माप(काष्ठा sockaddr_in6))
	),

	TP_fast_assign(
		__entry->cm_id = id_priv->res.id;
		__entry->tos = id_priv->tos;
		__entry->event = event;
		स_नकल(__entry->srcaddr, &id_priv->id.route.addr.src_addr,
		       माप(काष्ठा sockaddr_in6));
		स_नकल(__entry->dstaddr, &id_priv->id.route.addr.dst_addr,
		       माप(काष्ठा sockaddr_in6));
	),

	TP_prपूर्णांकk("cm.id=%u src=%pISpc dst=%pISpc tos=%u %s (%lu)",
		__entry->cm_id, __entry->srcaddr, __entry->dstaddr, __entry->tos,
		rdma_show_ib_cm_event(__entry->event), __entry->event
	)
);

TRACE_EVENT(cm_event_handler,
	TP_PROTO(
		स्थिर काष्ठा rdma_id_निजी *id_priv,
		स्थिर काष्ठा rdma_cm_event *event
	),

	TP_ARGS(id_priv, event),

	TP_STRUCT__entry(
		__field(u32, cm_id)
		__field(u32, tos)
		__field(अचिन्हित दीर्घ, event)
		__field(पूर्णांक, status)
		__array(अचिन्हित अक्षर, srcaddr, माप(काष्ठा sockaddr_in6))
		__array(अचिन्हित अक्षर, dstaddr, माप(काष्ठा sockaddr_in6))
	),

	TP_fast_assign(
		__entry->cm_id = id_priv->res.id;
		__entry->tos = id_priv->tos;
		__entry->event = event->event;
		__entry->status = event->status;
		स_नकल(__entry->srcaddr, &id_priv->id.route.addr.src_addr,
		       माप(काष्ठा sockaddr_in6));
		स_नकल(__entry->dstaddr, &id_priv->id.route.addr.dst_addr,
		       माप(काष्ठा sockaddr_in6));
	),

	TP_prपूर्णांकk("cm.id=%u src=%pISpc dst=%pISpc tos=%u %s (%lu/%d)",
		__entry->cm_id, __entry->srcaddr, __entry->dstaddr, __entry->tos,
		rdma_show_cm_event(__entry->event), __entry->event,
		__entry->status
	)
);

TRACE_EVENT(cm_event_करोne,
	TP_PROTO(
		स्थिर काष्ठा rdma_id_निजी *id_priv,
		स्थिर काष्ठा rdma_cm_event *event,
		पूर्णांक result
	),

	TP_ARGS(id_priv, event, result),

	TP_STRUCT__entry(
		__field(u32, cm_id)
		__field(u32, tos)
		__field(अचिन्हित दीर्घ, event)
		__field(पूर्णांक, result)
		__array(अचिन्हित अक्षर, srcaddr, माप(काष्ठा sockaddr_in6))
		__array(अचिन्हित अक्षर, dstaddr, माप(काष्ठा sockaddr_in6))
	),

	TP_fast_assign(
		__entry->cm_id = id_priv->res.id;
		__entry->tos = id_priv->tos;
		__entry->event = event->event;
		__entry->result = result;
		स_नकल(__entry->srcaddr, &id_priv->id.route.addr.src_addr,
		       माप(काष्ठा sockaddr_in6));
		स_नकल(__entry->dstaddr, &id_priv->id.route.addr.dst_addr,
		       माप(काष्ठा sockaddr_in6));
	),

	TP_prपूर्णांकk("cm.id=%u src=%pISpc dst=%pISpc tos=%u %s consumer returns %d",
		__entry->cm_id, __entry->srcaddr, __entry->dstaddr, __entry->tos,
		rdma_show_cm_event(__entry->event), __entry->result
	)
);

DECLARE_EVENT_CLASS(cma_client_class,
	TP_PROTO(
		स्थिर काष्ठा ib_device *device
	),

	TP_ARGS(device),

	TP_STRUCT__entry(
		__string(name, device->name)
	),

	TP_fast_assign(
		__assign_str(name, device->name);
	),

	TP_prपूर्णांकk("device name=%s",
		__get_str(name)
	)
);

#घोषणा DEFINE_CMA_CLIENT_EVENT(name)						\
		DEFINE_EVENT(cma_client_class, cm_##name,			\
				TP_PROTO(					\
					स्थिर काष्ठा ib_device *device		\
				),						\
				TP_ARGS(device))

DEFINE_CMA_CLIENT_EVENT(add_one);
DEFINE_CMA_CLIENT_EVENT(हटाओ_one);

#पूर्ण_अगर /* _TRACE_RDMA_CMA_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता cma_trace

#समावेश <trace/define_trace.h>
