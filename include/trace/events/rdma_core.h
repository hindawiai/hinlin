<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Trace poपूर्णांक definitions क्रम core RDMA functions.
 *
 * Author: Chuck Lever <chuck.lever@oracle.com>
 *
 * Copyright (c) 2019, Oracle and/or its affiliates. All rights reserved.
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM rdma_core

#अगर !defined(_TRACE_RDMA_CORE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_RDMA_CORE_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <rdma/ib_verbs.h>

/*
 * क्रमागत ib_poll_context, from include/rdma/ib_verbs.h
 */
#घोषणा IB_POLL_CTX_LIST			\
	ib_poll_ctx(सूचीECT)			\
	ib_poll_ctx(SOFTIRQ)			\
	ib_poll_ctx(WORKQUEUE)			\
	ib_poll_ctx_end(UNBOUND_WORKQUEUE)

#अघोषित ib_poll_ctx
#अघोषित ib_poll_ctx_end

#घोषणा ib_poll_ctx(x)		TRACE_DEFINE_ENUM(IB_POLL_##x);
#घोषणा ib_poll_ctx_end(x)	TRACE_DEFINE_ENUM(IB_POLL_##x);

IB_POLL_CTX_LIST

#अघोषित ib_poll_ctx
#अघोषित ib_poll_ctx_end

#घोषणा ib_poll_ctx(x)		अणु IB_POLL_##x, #x पूर्ण,
#घोषणा ib_poll_ctx_end(x)	अणु IB_POLL_##x, #x पूर्ण

#घोषणा rdma_show_ib_poll_ctx(x) \
		__prपूर्णांक_symbolic(x, IB_POLL_CTX_LIST)

/**
 ** Completion Queue events
 **/

TRACE_EVENT(cq_schedule,
	TP_PROTO(
		काष्ठा ib_cq *cq
	),

	TP_ARGS(cq),

	TP_STRUCT__entry(
		__field(u32, cq_id)
	),

	TP_fast_assign(
		cq->बारtamp = kसमय_get();
		cq->पूर्णांकerrupt = true;

		__entry->cq_id = cq->res.id;
	),

	TP_prपूर्णांकk("cq.id=%u", __entry->cq_id)
);

TRACE_EVENT(cq_reschedule,
	TP_PROTO(
		काष्ठा ib_cq *cq
	),

	TP_ARGS(cq),

	TP_STRUCT__entry(
		__field(u32, cq_id)
	),

	TP_fast_assign(
		cq->बारtamp = kसमय_get();
		cq->पूर्णांकerrupt = false;

		__entry->cq_id = cq->res.id;
	),

	TP_prपूर्णांकk("cq.id=%u", __entry->cq_id)
);

TRACE_EVENT(cq_process,
	TP_PROTO(
		स्थिर काष्ठा ib_cq *cq
	),

	TP_ARGS(cq),

	TP_STRUCT__entry(
		__field(u32, cq_id)
		__field(bool, पूर्णांकerrupt)
		__field(s64, latency)
	),

	TP_fast_assign(
		kसमय_प्रकार latency = kसमय_sub(kसमय_get(), cq->बारtamp);

		__entry->cq_id = cq->res.id;
		__entry->latency = kसमय_प्रकारo_us(latency);
		__entry->पूर्णांकerrupt = cq->पूर्णांकerrupt;
	),

	TP_prपूर्णांकk("cq.id=%u wake-up took %lld [us] from %s",
		__entry->cq_id, __entry->latency,
		__entry->पूर्णांकerrupt ? "interrupt" : "reschedule"
	)
);

TRACE_EVENT(cq_poll,
	TP_PROTO(
		स्थिर काष्ठा ib_cq *cq,
		पूर्णांक requested,
		पूर्णांक rc
	),

	TP_ARGS(cq, requested, rc),

	TP_STRUCT__entry(
		__field(u32, cq_id)
		__field(पूर्णांक, requested)
		__field(पूर्णांक, rc)
	),

	TP_fast_assign(
		__entry->cq_id = cq->res.id;
		__entry->requested = requested;
		__entry->rc = rc;
	),

	TP_prपूर्णांकk("cq.id=%u requested %d, returned %d",
		__entry->cq_id, __entry->requested, __entry->rc
	)
);

TRACE_EVENT(cq_drain_complete,
	TP_PROTO(
		स्थिर काष्ठा ib_cq *cq
	),

	TP_ARGS(cq),

	TP_STRUCT__entry(
		__field(u32, cq_id)
	),

	TP_fast_assign(
		__entry->cq_id = cq->res.id;
	),

	TP_prपूर्णांकk("cq.id=%u",
		__entry->cq_id
	)
);


TRACE_EVENT(cq_modअगरy,
	TP_PROTO(
		स्थिर काष्ठा ib_cq *cq,
		u16 comps,
		u16 usec
	),

	TP_ARGS(cq, comps, usec),

	TP_STRUCT__entry(
		__field(u32, cq_id)
		__field(अचिन्हित पूर्णांक, comps)
		__field(अचिन्हित पूर्णांक, usec)
	),

	TP_fast_assign(
		__entry->cq_id = cq->res.id;
		__entry->comps = comps;
		__entry->usec = usec;
	),

	TP_prपूर्णांकk("cq.id=%u comps=%u usec=%u",
		__entry->cq_id, __entry->comps, __entry->usec
	)
);

TRACE_EVENT(cq_alloc,
	TP_PROTO(
		स्थिर काष्ठा ib_cq *cq,
		पूर्णांक nr_cqe,
		पूर्णांक comp_vector,
		क्रमागत ib_poll_context poll_ctx
	),

	TP_ARGS(cq, nr_cqe, comp_vector, poll_ctx),

	TP_STRUCT__entry(
		__field(u32, cq_id)
		__field(पूर्णांक, nr_cqe)
		__field(पूर्णांक, comp_vector)
		__field(अचिन्हित दीर्घ, poll_ctx)
	),

	TP_fast_assign(
		__entry->cq_id = cq->res.id;
		__entry->nr_cqe = nr_cqe;
		__entry->comp_vector = comp_vector;
		__entry->poll_ctx = poll_ctx;
	),

	TP_prपूर्णांकk("cq.id=%u nr_cqe=%d comp_vector=%d poll_ctx=%s",
		__entry->cq_id, __entry->nr_cqe, __entry->comp_vector,
		rdma_show_ib_poll_ctx(__entry->poll_ctx)
	)
);

TRACE_EVENT(cq_alloc_error,
	TP_PROTO(
		पूर्णांक nr_cqe,
		पूर्णांक comp_vector,
		क्रमागत ib_poll_context poll_ctx,
		पूर्णांक rc
	),

	TP_ARGS(nr_cqe, comp_vector, poll_ctx, rc),

	TP_STRUCT__entry(
		__field(पूर्णांक, rc)
		__field(पूर्णांक, nr_cqe)
		__field(पूर्णांक, comp_vector)
		__field(अचिन्हित दीर्घ, poll_ctx)
	),

	TP_fast_assign(
		__entry->rc = rc;
		__entry->nr_cqe = nr_cqe;
		__entry->comp_vector = comp_vector;
		__entry->poll_ctx = poll_ctx;
	),

	TP_prपूर्णांकk("nr_cqe=%d comp_vector=%d poll_ctx=%s rc=%d",
		__entry->nr_cqe, __entry->comp_vector,
		rdma_show_ib_poll_ctx(__entry->poll_ctx), __entry->rc
	)
);

TRACE_EVENT(cq_मुक्त,
	TP_PROTO(
		स्थिर काष्ठा ib_cq *cq
	),

	TP_ARGS(cq),

	TP_STRUCT__entry(
		__field(u32, cq_id)
	),

	TP_fast_assign(
		__entry->cq_id = cq->res.id;
	),

	TP_prपूर्णांकk("cq.id=%u", __entry->cq_id)
);

/**
 ** Memory Region events
 **/

/*
 * क्रमागत ib_mr_type, from include/rdma/ib_verbs.h
 */
#घोषणा IB_MR_TYPE_LIST				\
	ib_mr_type_item(MEM_REG)		\
	ib_mr_type_item(SG_GAPS)		\
	ib_mr_type_item(DM)			\
	ib_mr_type_item(USER)			\
	ib_mr_type_item(DMA)			\
	ib_mr_type_end(INTEGRITY)

#अघोषित ib_mr_type_item
#अघोषित ib_mr_type_end

#घोषणा ib_mr_type_item(x)	TRACE_DEFINE_ENUM(IB_MR_TYPE_##x);
#घोषणा ib_mr_type_end(x)	TRACE_DEFINE_ENUM(IB_MR_TYPE_##x);

IB_MR_TYPE_LIST

#अघोषित ib_mr_type_item
#अघोषित ib_mr_type_end

#घोषणा ib_mr_type_item(x)	अणु IB_MR_TYPE_##x, #x पूर्ण,
#घोषणा ib_mr_type_end(x)	अणु IB_MR_TYPE_##x, #x पूर्ण

#घोषणा rdma_show_ib_mr_type(x) \
		__prपूर्णांक_symbolic(x, IB_MR_TYPE_LIST)

TRACE_EVENT(mr_alloc,
	TP_PROTO(
		स्थिर काष्ठा ib_pd *pd,
		क्रमागत ib_mr_type mr_type,
		u32 max_num_sg,
		स्थिर काष्ठा ib_mr *mr
	),

	TP_ARGS(pd, mr_type, max_num_sg, mr),

	TP_STRUCT__entry(
		__field(u32, pd_id)
		__field(u32, mr_id)
		__field(u32, max_num_sg)
		__field(पूर्णांक, rc)
		__field(अचिन्हित दीर्घ, mr_type)
	),

	TP_fast_assign(
		__entry->pd_id = pd->res.id;
		अगर (IS_ERR(mr)) अणु
			__entry->mr_id = 0;
			__entry->rc = PTR_ERR(mr);
		पूर्ण अन्यथा अणु
			__entry->mr_id = mr->res.id;
			__entry->rc = 0;
		पूर्ण
		__entry->max_num_sg = max_num_sg;
		__entry->mr_type = mr_type;
	),

	TP_prपूर्णांकk("pd.id=%u mr.id=%u type=%s max_num_sg=%u rc=%d",
		__entry->pd_id, __entry->mr_id,
		rdma_show_ib_mr_type(__entry->mr_type),
		__entry->max_num_sg, __entry->rc)
);

TRACE_EVENT(mr_पूर्णांकeg_alloc,
	TP_PROTO(
		स्थिर काष्ठा ib_pd *pd,
		u32 max_num_data_sg,
		u32 max_num_meta_sg,
		स्थिर काष्ठा ib_mr *mr
	),

	TP_ARGS(pd, max_num_data_sg, max_num_meta_sg, mr),

	TP_STRUCT__entry(
		__field(u32, pd_id)
		__field(u32, mr_id)
		__field(u32, max_num_data_sg)
		__field(u32, max_num_meta_sg)
		__field(पूर्णांक, rc)
	),

	TP_fast_assign(
		__entry->pd_id = pd->res.id;
		अगर (IS_ERR(mr)) अणु
			__entry->mr_id = 0;
			__entry->rc = PTR_ERR(mr);
		पूर्ण अन्यथा अणु
			__entry->mr_id = mr->res.id;
			__entry->rc = 0;
		पूर्ण
		__entry->max_num_data_sg = max_num_data_sg;
		__entry->max_num_meta_sg = max_num_meta_sg;
	),

	TP_prपूर्णांकk("pd.id=%u mr.id=%u max_num_data_sg=%u max_num_meta_sg=%u rc=%d",
		__entry->pd_id, __entry->mr_id, __entry->max_num_data_sg,
		__entry->max_num_meta_sg, __entry->rc)
);

TRACE_EVENT(mr_dereg,
	TP_PROTO(
		स्थिर काष्ठा ib_mr *mr
	),

	TP_ARGS(mr),

	TP_STRUCT__entry(
		__field(u32, id)
	),

	TP_fast_assign(
		__entry->id = mr->res.id;
	),

	TP_prपूर्णांकk("mr.id=%u", __entry->id)
);

#पूर्ण_अगर /* _TRACE_RDMA_CORE_H */

#समावेश <trace/define_trace.h>
