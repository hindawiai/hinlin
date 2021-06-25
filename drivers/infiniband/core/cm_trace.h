<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Trace poपूर्णांक definitions क्रम the RDMA Connect Manager.
 *
 * Author: Chuck Lever <chuck.lever@oracle.com>
 *
 * Copyright (c) 2020 Oracle and/or its affiliates.
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM ib_cma

#अगर !defined(_TRACE_IB_CMA_H) || defined(TRACE_HEADER_MULTI_READ)

#घोषणा _TRACE_IB_CMA_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <rdma/ib_cm.h>
#समावेश <trace/events/rdma.h>

/*
 * क्रमागत ib_cm_state, from include/rdma/ib_cm.h
 */
#घोषणा IB_CM_STATE_LIST					\
	ib_cm_state(IDLE)					\
	ib_cm_state(LISTEN)					\
	ib_cm_state(REQ_SENT)					\
	ib_cm_state(REQ_RCVD)					\
	ib_cm_state(MRA_REQ_SENT)				\
	ib_cm_state(MRA_REQ_RCVD)				\
	ib_cm_state(REP_SENT)					\
	ib_cm_state(REP_RCVD)					\
	ib_cm_state(MRA_REP_SENT)				\
	ib_cm_state(MRA_REP_RCVD)				\
	ib_cm_state(ESTABLISHED)				\
	ib_cm_state(DREQ_SENT)					\
	ib_cm_state(DREQ_RCVD)					\
	ib_cm_state(TIMEWAIT)					\
	ib_cm_state(SIDR_REQ_SENT)				\
	ib_cm_state_end(SIDR_REQ_RCVD)

#अघोषित  ib_cm_state
#अघोषित  ib_cm_state_end
#घोषणा ib_cm_state(x)		TRACE_DEFINE_ENUM(IB_CM_##x);
#घोषणा ib_cm_state_end(x)	TRACE_DEFINE_ENUM(IB_CM_##x);

IB_CM_STATE_LIST

#अघोषित  ib_cm_state
#अघोषित  ib_cm_state_end
#घोषणा ib_cm_state(x)		अणु IB_CM_##x, #x पूर्ण,
#घोषणा ib_cm_state_end(x)	अणु IB_CM_##x, #x पूर्ण

#घोषणा show_ib_cm_state(x) \
		__prपूर्णांक_symbolic(x, IB_CM_STATE_LIST)

/*
 * क्रमागत ib_cm_lap_state, from include/rdma/ib_cm.h
 */
#घोषणा IB_CM_LAP_STATE_LIST					\
	ib_cm_lap_state(LAP_UNINIT)				\
	ib_cm_lap_state(LAP_IDLE)				\
	ib_cm_lap_state(LAP_SENT)				\
	ib_cm_lap_state(LAP_RCVD)				\
	ib_cm_lap_state(MRA_LAP_SENT)				\
	ib_cm_lap_state_end(MRA_LAP_RCVD)

#अघोषित  ib_cm_lap_state
#अघोषित  ib_cm_lap_state_end
#घोषणा ib_cm_lap_state(x)	TRACE_DEFINE_ENUM(IB_CM_##x);
#घोषणा ib_cm_lap_state_end(x)	TRACE_DEFINE_ENUM(IB_CM_##x);

IB_CM_LAP_STATE_LIST

#अघोषित  ib_cm_lap_state
#अघोषित  ib_cm_lap_state_end
#घोषणा ib_cm_lap_state(x)	अणु IB_CM_##x, #x पूर्ण,
#घोषणा ib_cm_lap_state_end(x)	अणु IB_CM_##x, #x पूर्ण

#घोषणा show_ib_cm_lap_state(x) \
		__prपूर्णांक_symbolic(x, IB_CM_LAP_STATE_LIST)

/*
 * क्रमागत ib_cm_rej_reason, from include/rdma/ib_cm.h
 */
#घोषणा IB_CM_REJ_REASON_LIST					\
	ib_cm_rej_reason(REJ_NO_QP)				\
	ib_cm_rej_reason(REJ_NO_EEC)				\
	ib_cm_rej_reason(REJ_NO_RESOURCES)			\
	ib_cm_rej_reason(REJ_TIMEOUT)				\
	ib_cm_rej_reason(REJ_UNSUPPORTED)			\
	ib_cm_rej_reason(REJ_INVALID_COMM_ID)			\
	ib_cm_rej_reason(REJ_INVALID_COMM_INSTANCE)		\
	ib_cm_rej_reason(REJ_INVALID_SERVICE_ID)		\
	ib_cm_rej_reason(REJ_INVALID_TRANSPORT_TYPE)		\
	ib_cm_rej_reason(REJ_STALE_CONN)			\
	ib_cm_rej_reason(REJ_RDC_NOT_EXIST)			\
	ib_cm_rej_reason(REJ_INVALID_GID)			\
	ib_cm_rej_reason(REJ_INVALID_LID)			\
	ib_cm_rej_reason(REJ_INVALID_SL)			\
	ib_cm_rej_reason(REJ_INVALID_TRAFFIC_CLASS)		\
	ib_cm_rej_reason(REJ_INVALID_HOP_LIMIT)			\
	ib_cm_rej_reason(REJ_INVALID_PACKET_RATE)		\
	ib_cm_rej_reason(REJ_INVALID_ALT_GID)			\
	ib_cm_rej_reason(REJ_INVALID_ALT_LID)			\
	ib_cm_rej_reason(REJ_INVALID_ALT_SL)			\
	ib_cm_rej_reason(REJ_INVALID_ALT_TRAFFIC_CLASS)		\
	ib_cm_rej_reason(REJ_INVALID_ALT_HOP_LIMIT)		\
	ib_cm_rej_reason(REJ_INVALID_ALT_PACKET_RATE)		\
	ib_cm_rej_reason(REJ_PORT_CM_REसूचीECT)			\
	ib_cm_rej_reason(REJ_PORT_REसूचीECT)			\
	ib_cm_rej_reason(REJ_INVALID_MTU)			\
	ib_cm_rej_reason(REJ_INSUFFICIENT_RESP_RESOURCES)	\
	ib_cm_rej_reason(REJ_CONSUMER_DEFINED)			\
	ib_cm_rej_reason(REJ_INVALID_RNR_RETRY)			\
	ib_cm_rej_reason(REJ_DUPLICATE_LOCAL_COMM_ID)		\
	ib_cm_rej_reason(REJ_INVALID_CLASS_VERSION)		\
	ib_cm_rej_reason(REJ_INVALID_FLOW_LABEL)		\
	ib_cm_rej_reason(REJ_INVALID_ALT_FLOW_LABEL)		\
	ib_cm_rej_reason_end(REJ_VENDOR_OPTION_NOT_SUPPORTED)

#अघोषित  ib_cm_rej_reason
#अघोषित  ib_cm_rej_reason_end
#घोषणा ib_cm_rej_reason(x)	TRACE_DEFINE_ENUM(IB_CM_##x);
#घोषणा ib_cm_rej_reason_end(x)	TRACE_DEFINE_ENUM(IB_CM_##x);

IB_CM_REJ_REASON_LIST

#अघोषित  ib_cm_rej_reason
#अघोषित  ib_cm_rej_reason_end
#घोषणा ib_cm_rej_reason(x)	अणु IB_CM_##x, #x पूर्ण,
#घोषणा ib_cm_rej_reason_end(x)	अणु IB_CM_##x, #x पूर्ण

#घोषणा show_ib_cm_rej_reason(x) \
		__prपूर्णांक_symbolic(x, IB_CM_REJ_REASON_LIST)

DECLARE_EVENT_CLASS(icm_id_class,
	TP_PROTO(
		स्थिर काष्ठा ib_cm_id *cm_id
	),

	TP_ARGS(cm_id),

	TP_STRUCT__entry(
		__field(स्थिर व्योम *, cm_id)	/* क्रम eBPF scripts */
		__field(अचिन्हित पूर्णांक, local_id)
		__field(अचिन्हित पूर्णांक, remote_id)
		__field(अचिन्हित दीर्घ, state)
		__field(अचिन्हित दीर्घ, lap_state)
	),

	TP_fast_assign(
		__entry->cm_id = cm_id;
		__entry->local_id = be32_to_cpu(cm_id->local_id);
		__entry->remote_id = be32_to_cpu(cm_id->remote_id);
		__entry->state = cm_id->state;
		__entry->lap_state = cm_id->lap_state;
	),

	TP_prपूर्णांकk("local_id=%u remote_id=%u state=%s lap_state=%s",
		__entry->local_id, __entry->remote_id,
		show_ib_cm_state(__entry->state),
		show_ib_cm_lap_state(__entry->lap_state)
	)
);

#घोषणा DEFINE_CM_SEND_EVENT(name)					\
		DEFINE_EVENT(icm_id_class,				\
				icm_send_##name,				\
				TP_PROTO(				\
					स्थिर काष्ठा ib_cm_id *cm_id	\
				),					\
				TP_ARGS(cm_id))

DEFINE_CM_SEND_EVENT(req);
DEFINE_CM_SEND_EVENT(rep);
DEFINE_CM_SEND_EVENT(dup_req);
DEFINE_CM_SEND_EVENT(dup_rep);
DEFINE_CM_SEND_EVENT(rtu);
DEFINE_CM_SEND_EVENT(mra);
DEFINE_CM_SEND_EVENT(sidr_req);
DEFINE_CM_SEND_EVENT(sidr_rep);
DEFINE_CM_SEND_EVENT(dreq);
DEFINE_CM_SEND_EVENT(drep);

TRACE_EVENT(icm_send_rej,
	TP_PROTO(
		स्थिर काष्ठा ib_cm_id *cm_id,
		क्रमागत ib_cm_rej_reason reason
	),

	TP_ARGS(cm_id, reason),

	TP_STRUCT__entry(
		__field(स्थिर व्योम *, cm_id)
		__field(u32, local_id)
		__field(u32, remote_id)
		__field(अचिन्हित दीर्घ, state)
		__field(अचिन्हित दीर्घ, reason)
	),

	TP_fast_assign(
		__entry->cm_id = cm_id;
		__entry->local_id = be32_to_cpu(cm_id->local_id);
		__entry->remote_id = be32_to_cpu(cm_id->remote_id);
		__entry->state = cm_id->state;
		__entry->reason = reason;
	),

	TP_prपूर्णांकk("local_id=%u remote_id=%u state=%s reason=%s",
		__entry->local_id, __entry->remote_id,
		show_ib_cm_state(__entry->state),
		show_ib_cm_rej_reason(__entry->reason)
	)
);

#घोषणा DEFINE_CM_ERR_EVENT(name)					\
		DEFINE_EVENT(icm_id_class,				\
				icm_##name##_err,			\
				TP_PROTO(				\
					स्थिर काष्ठा ib_cm_id *cm_id	\
				),					\
				TP_ARGS(cm_id))

DEFINE_CM_ERR_EVENT(send_cm_rtu);
DEFINE_CM_ERR_EVENT(establish);
DEFINE_CM_ERR_EVENT(no_listener);
DEFINE_CM_ERR_EVENT(send_drep);
DEFINE_CM_ERR_EVENT(dreq_unknown);
DEFINE_CM_ERR_EVENT(send_unknown_rej);
DEFINE_CM_ERR_EVENT(rej_unknown);
DEFINE_CM_ERR_EVENT(send_mra_unknown);
DEFINE_CM_ERR_EVENT(mra_unknown);
DEFINE_CM_ERR_EVENT(qp_init);
DEFINE_CM_ERR_EVENT(qp_rtr);
DEFINE_CM_ERR_EVENT(qp_rts);

DEFINE_EVENT(icm_id_class,						\
	icm_dreq_skipped,						\
	TP_PROTO(							\
		स्थिर काष्ठा ib_cm_id *cm_id				\
	),								\
	TP_ARGS(cm_id)							\
);

DECLARE_EVENT_CLASS(icm_local_class,
	TP_PROTO(
		अचिन्हित पूर्णांक local_id,
		अचिन्हित पूर्णांक remote_id
	),

	TP_ARGS(local_id, remote_id),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, local_id)
		__field(अचिन्हित पूर्णांक, remote_id)
	),

	TP_fast_assign(
		__entry->local_id = local_id;
		__entry->remote_id = remote_id;
	),

	TP_prपूर्णांकk("local_id=%u remote_id=%u",
		__entry->local_id, __entry->remote_id
	)
);

#घोषणा DEFINE_CM_LOCAL_EVENT(name)					\
		DEFINE_EVENT(icm_local_class,				\
				icm_##name,				\
				TP_PROTO(				\
					अचिन्हित पूर्णांक local_id,			\
					अचिन्हित पूर्णांक remote_id			\
				),					\
				TP_ARGS(local_id, remote_id))

DEFINE_CM_LOCAL_EVENT(issue_rej);
DEFINE_CM_LOCAL_EVENT(issue_drep);
DEFINE_CM_LOCAL_EVENT(staleconn_err);
DEFINE_CM_LOCAL_EVENT(no_priv_err);

DECLARE_EVENT_CLASS(icm_remote_class,
	TP_PROTO(
		u32 remote_id
	),

	TP_ARGS(remote_id),

	TP_STRUCT__entry(
		__field(u32, remote_id)
	),

	TP_fast_assign(
		__entry->remote_id = remote_id;
	),

	TP_prपूर्णांकk("remote_id=%u",
		__entry->remote_id
	)
);

#घोषणा DEFINE_CM_REMOTE_EVENT(name)					\
		DEFINE_EVENT(icm_remote_class,				\
				icm_##name,				\
				TP_PROTO(				\
					u32 remote_id			\
				),					\
				TP_ARGS(remote_id))

DEFINE_CM_REMOTE_EVENT(remote_no_priv_err);
DEFINE_CM_REMOTE_EVENT(insert_failed_err);

TRACE_EVENT(icm_send_rep_err,
	TP_PROTO(
		__be32 local_id,
		क्रमागत ib_cm_state state
	),

	TP_ARGS(local_id, state),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, local_id)
		__field(अचिन्हित दीर्घ, state)
	),

	TP_fast_assign(
		__entry->local_id = be32_to_cpu(local_id);
		__entry->state = state;
	),

	TP_prपूर्णांकk("local_id=%u state=%s",
		__entry->local_id, show_ib_cm_state(__entry->state)
	)
);

TRACE_EVENT(icm_rep_unknown_err,
	TP_PROTO(
		अचिन्हित पूर्णांक local_id,
		अचिन्हित पूर्णांक remote_id,
		क्रमागत ib_cm_state state
	),

	TP_ARGS(local_id, remote_id, state),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, local_id)
		__field(अचिन्हित पूर्णांक, remote_id)
		__field(अचिन्हित दीर्घ, state)
	),

	TP_fast_assign(
		__entry->local_id = local_id;
		__entry->remote_id = remote_id;
		__entry->state = state;
	),

	TP_prपूर्णांकk("local_id=%u remote_id=%u state=%s",
		__entry->local_id, __entry->remote_id,
		show_ib_cm_state(__entry->state)
	)
);

TRACE_EVENT(icm_handler_err,
	TP_PROTO(
		क्रमागत ib_cm_event_type event
	),

	TP_ARGS(event),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, event)
	),

	TP_fast_assign(
		__entry->event = event;
	),

	TP_prपूर्णांकk("unhandled event=%s",
		rdma_show_ib_cm_event(__entry->event)
	)
);

TRACE_EVENT(icm_mad_send_err,
	TP_PROTO(
		क्रमागत ib_cm_state state,
		क्रमागत ib_wc_status wc_status
	),

	TP_ARGS(state, wc_status),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, state)
		__field(अचिन्हित दीर्घ, wc_status)
	),

	TP_fast_assign(
		__entry->state = state;
		__entry->wc_status = wc_status;
	),

	TP_prपूर्णांकk("state=%s completion status=%s",
		show_ib_cm_state(__entry->state),
		rdma_show_wc_status(__entry->wc_status)
	)
);

#पूर्ण_अगर /* _TRACE_IB_CMA_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ../../drivers/infiniband/core
#घोषणा TRACE_INCLUDE_खाता cm_trace

#समावेश <trace/define_trace.h>
