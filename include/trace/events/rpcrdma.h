<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2017, 2018 Oracle.  All rights reserved.
 *
 * Trace poपूर्णांक definitions क्रम the "rpcrdma" subप्रणाली.
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM rpcrdma

#अगर !defined(_TRACE_RPCRDMA_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_RPCRDMA_H

#समावेश <linux/scatterlist.h>
#समावेश <linux/sunrpc/rpc_rdma_cid.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <rdma/ib_cm.h>
#समावेश <trace/events/rdma.h>

/**
 ** Event classes
 **/

DECLARE_EVENT_CLASS(rpcrdma_completion_class,
	TP_PROTO(
		स्थिर काष्ठा ib_wc *wc,
		स्थिर काष्ठा rpc_rdma_cid *cid
	),

	TP_ARGS(wc, cid),

	TP_STRUCT__entry(
		__field(u32, cq_id)
		__field(पूर्णांक, completion_id)
		__field(अचिन्हित दीर्घ, status)
		__field(अचिन्हित पूर्णांक, venकरोr_err)
	),

	TP_fast_assign(
		__entry->cq_id = cid->ci_queue_id;
		__entry->completion_id = cid->ci_completion_id;
		__entry->status = wc->status;
		अगर (wc->status)
			__entry->venकरोr_err = wc->venकरोr_err;
		अन्यथा
			__entry->venकरोr_err = 0;
	),

	TP_prपूर्णांकk("cq.id=%u cid=%d status=%s (%lu/0x%x)",
		__entry->cq_id, __entry->completion_id,
		rdma_show_wc_status(__entry->status),
		__entry->status, __entry->venकरोr_err
	)
);

#घोषणा DEFINE_COMPLETION_EVENT(name)					\
		DEFINE_EVENT(rpcrdma_completion_class, name,		\
				TP_PROTO(				\
					स्थिर काष्ठा ib_wc *wc,		\
					स्थिर काष्ठा rpc_rdma_cid *cid	\
				),					\
				TP_ARGS(wc, cid))

DECLARE_EVENT_CLASS(rpcrdma_mr_completion_class,
	TP_PROTO(
		स्थिर काष्ठा ib_wc *wc,
		स्थिर काष्ठा rpc_rdma_cid *cid
	),

	TP_ARGS(wc, cid),

	TP_STRUCT__entry(
		__field(u32, cq_id)
		__field(पूर्णांक, completion_id)
		__field(अचिन्हित दीर्घ, status)
		__field(अचिन्हित पूर्णांक, venकरोr_err)
	),

	TP_fast_assign(
		__entry->cq_id = cid->ci_queue_id;
		__entry->completion_id = cid->ci_completion_id;
		__entry->status = wc->status;
		अगर (wc->status)
			__entry->venकरोr_err = wc->venकरोr_err;
		अन्यथा
			__entry->venकरोr_err = 0;
	),

	TP_prपूर्णांकk("cq.id=%u mr.id=%d status=%s (%lu/0x%x)",
		__entry->cq_id, __entry->completion_id,
		rdma_show_wc_status(__entry->status),
		__entry->status, __entry->venकरोr_err
	)
);

#घोषणा DEFINE_MR_COMPLETION_EVENT(name)				\
		DEFINE_EVENT(rpcrdma_mr_completion_class, name,		\
				TP_PROTO(				\
					स्थिर काष्ठा ib_wc *wc,		\
					स्थिर काष्ठा rpc_rdma_cid *cid	\
				),					\
				TP_ARGS(wc, cid))

DECLARE_EVENT_CLASS(rpcrdma_receive_completion_class,
	TP_PROTO(
		स्थिर काष्ठा ib_wc *wc,
		स्थिर काष्ठा rpc_rdma_cid *cid
	),

	TP_ARGS(wc, cid),

	TP_STRUCT__entry(
		__field(u32, cq_id)
		__field(पूर्णांक, completion_id)
		__field(u32, received)
		__field(अचिन्हित दीर्घ, status)
		__field(अचिन्हित पूर्णांक, venकरोr_err)
	),

	TP_fast_assign(
		__entry->cq_id = cid->ci_queue_id;
		__entry->completion_id = cid->ci_completion_id;
		__entry->status = wc->status;
		अगर (wc->status) अणु
			__entry->received = 0;
			__entry->venकरोr_err = wc->venकरोr_err;
		पूर्ण अन्यथा अणु
			__entry->received = wc->byte_len;
			__entry->venकरोr_err = 0;
		पूर्ण
	),

	TP_prपूर्णांकk("cq.id=%u cid=%d status=%s (%lu/0x%x) received=%u",
		__entry->cq_id, __entry->completion_id,
		rdma_show_wc_status(__entry->status),
		__entry->status, __entry->venकरोr_err,
		__entry->received
	)
);

#घोषणा DEFINE_RECEIVE_COMPLETION_EVENT(name)				\
		DEFINE_EVENT(rpcrdma_receive_completion_class, name,	\
				TP_PROTO(				\
					स्थिर काष्ठा ib_wc *wc,		\
					स्थिर काष्ठा rpc_rdma_cid *cid	\
				),					\
				TP_ARGS(wc, cid))

DECLARE_EVENT_CLASS(xprtrdma_reply_class,
	TP_PROTO(
		स्थिर काष्ठा rpcrdma_rep *rep
	),

	TP_ARGS(rep),

	TP_STRUCT__entry(
		__field(u32, xid)
		__field(u32, version)
		__field(u32, proc)
		__string(addr, rpcrdma_addrstr(rep->rr_rxprt))
		__string(port, rpcrdma_portstr(rep->rr_rxprt))
	),

	TP_fast_assign(
		__entry->xid = be32_to_cpu(rep->rr_xid);
		__entry->version = be32_to_cpu(rep->rr_vers);
		__entry->proc = be32_to_cpu(rep->rr_proc);
		__assign_str(addr, rpcrdma_addrstr(rep->rr_rxprt));
		__assign_str(port, rpcrdma_portstr(rep->rr_rxprt));
	),

	TP_prपूर्णांकk("peer=[%s]:%s xid=0x%08x version=%u proc=%u",
		__get_str(addr), __get_str(port),
		__entry->xid, __entry->version, __entry->proc
	)
);

#घोषणा DEFINE_REPLY_EVENT(name)					\
		DEFINE_EVENT(xprtrdma_reply_class,			\
				xprtrdma_reply_##name##_err,		\
				TP_PROTO(				\
					स्थिर काष्ठा rpcrdma_rep *rep	\
				),					\
				TP_ARGS(rep))

DECLARE_EVENT_CLASS(xprtrdma_rxprt,
	TP_PROTO(
		स्थिर काष्ठा rpcrdma_xprt *r_xprt
	),

	TP_ARGS(r_xprt),

	TP_STRUCT__entry(
		__string(addr, rpcrdma_addrstr(r_xprt))
		__string(port, rpcrdma_portstr(r_xprt))
	),

	TP_fast_assign(
		__assign_str(addr, rpcrdma_addrstr(r_xprt));
		__assign_str(port, rpcrdma_portstr(r_xprt));
	),

	TP_prपूर्णांकk("peer=[%s]:%s",
		__get_str(addr), __get_str(port)
	)
);

#घोषणा DEFINE_RXPRT_EVENT(name)					\
		DEFINE_EVENT(xprtrdma_rxprt, name,			\
				TP_PROTO(				\
					स्थिर काष्ठा rpcrdma_xprt *r_xprt \
				),					\
				TP_ARGS(r_xprt))

DECLARE_EVENT_CLASS(xprtrdma_connect_class,
	TP_PROTO(
		स्थिर काष्ठा rpcrdma_xprt *r_xprt,
		पूर्णांक rc
	),

	TP_ARGS(r_xprt, rc),

	TP_STRUCT__entry(
		__field(पूर्णांक, rc)
		__field(पूर्णांक, connect_status)
		__string(addr, rpcrdma_addrstr(r_xprt))
		__string(port, rpcrdma_portstr(r_xprt))
	),

	TP_fast_assign(
		__entry->rc = rc;
		__entry->connect_status = r_xprt->rx_ep->re_connect_status;
		__assign_str(addr, rpcrdma_addrstr(r_xprt));
		__assign_str(port, rpcrdma_portstr(r_xprt));
	),

	TP_prपूर्णांकk("peer=[%s]:%s rc=%d connection status=%d",
		__get_str(addr), __get_str(port),
		__entry->rc, __entry->connect_status
	)
);

#घोषणा DEFINE_CONN_EVENT(name)						\
		DEFINE_EVENT(xprtrdma_connect_class, xprtrdma_##name,	\
				TP_PROTO(				\
					स्थिर काष्ठा rpcrdma_xprt *r_xprt, \
					पूर्णांक rc				\
				),					\
				TP_ARGS(r_xprt, rc))

DECLARE_EVENT_CLASS(xprtrdma_rdch_event,
	TP_PROTO(
		स्थिर काष्ठा rpc_task *task,
		अचिन्हित पूर्णांक pos,
		काष्ठा rpcrdma_mr *mr,
		पूर्णांक nsegs
	),

	TP_ARGS(task, pos, mr, nsegs),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(अचिन्हित पूर्णांक, pos)
		__field(पूर्णांक, nents)
		__field(u32, handle)
		__field(u32, length)
		__field(u64, offset)
		__field(पूर्णांक, nsegs)
	),

	TP_fast_assign(
		__entry->task_id = task->tk_pid;
		__entry->client_id = task->tk_client->cl_clid;
		__entry->pos = pos;
		__entry->nents = mr->mr_nents;
		__entry->handle = mr->mr_handle;
		__entry->length = mr->mr_length;
		__entry->offset = mr->mr_offset;
		__entry->nsegs = nsegs;
	),

	TP_prपूर्णांकk("task:%u@%u pos=%u %u@0x%016llx:0x%08x (%s)",
		__entry->task_id, __entry->client_id,
		__entry->pos, __entry->length,
		(अचिन्हित दीर्घ दीर्घ)__entry->offset, __entry->handle,
		__entry->nents < __entry->nsegs ? "more" : "last"
	)
);

#घोषणा DEFINE_RDCH_EVENT(name)						\
		DEFINE_EVENT(xprtrdma_rdch_event, xprtrdma_chunk_##name,\
				TP_PROTO(				\
					स्थिर काष्ठा rpc_task *task,	\
					अचिन्हित पूर्णांक pos,		\
					काष्ठा rpcrdma_mr *mr,		\
					पूर्णांक nsegs			\
				),					\
				TP_ARGS(task, pos, mr, nsegs))

DECLARE_EVENT_CLASS(xprtrdma_wrch_event,
	TP_PROTO(
		स्थिर काष्ठा rpc_task *task,
		काष्ठा rpcrdma_mr *mr,
		पूर्णांक nsegs
	),

	TP_ARGS(task, mr, nsegs),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(पूर्णांक, nents)
		__field(u32, handle)
		__field(u32, length)
		__field(u64, offset)
		__field(पूर्णांक, nsegs)
	),

	TP_fast_assign(
		__entry->task_id = task->tk_pid;
		__entry->client_id = task->tk_client->cl_clid;
		__entry->nents = mr->mr_nents;
		__entry->handle = mr->mr_handle;
		__entry->length = mr->mr_length;
		__entry->offset = mr->mr_offset;
		__entry->nsegs = nsegs;
	),

	TP_prपूर्णांकk("task:%u@%u %u@0x%016llx:0x%08x (%s)",
		__entry->task_id, __entry->client_id,
		__entry->length, (अचिन्हित दीर्घ दीर्घ)__entry->offset,
		__entry->handle,
		__entry->nents < __entry->nsegs ? "more" : "last"
	)
);

#घोषणा DEFINE_WRCH_EVENT(name)						\
		DEFINE_EVENT(xprtrdma_wrch_event, xprtrdma_chunk_##name,\
				TP_PROTO(				\
					स्थिर काष्ठा rpc_task *task,	\
					काष्ठा rpcrdma_mr *mr,		\
					पूर्णांक nsegs			\
				),					\
				TP_ARGS(task, mr, nsegs))

TRACE_DEFINE_ENUM(DMA_BIसूचीECTIONAL);
TRACE_DEFINE_ENUM(DMA_TO_DEVICE);
TRACE_DEFINE_ENUM(DMA_FROM_DEVICE);
TRACE_DEFINE_ENUM(DMA_NONE);

#घोषणा xprtrdma_show_direction(x)					\
		__prपूर्णांक_symbolic(x,					\
				अणु DMA_BIसूचीECTIONAL, "BIDIR" पूर्ण,		\
				अणु DMA_TO_DEVICE, "TO_DEVICE" पूर्ण,		\
				अणु DMA_FROM_DEVICE, "FROM_DEVICE" पूर्ण,	\
				अणु DMA_NONE, "NONE" पूर्ण)

DECLARE_EVENT_CLASS(xprtrdma_mr_class,
	TP_PROTO(
		स्थिर काष्ठा rpcrdma_mr *mr
	),

	TP_ARGS(mr),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(u32, mr_id)
		__field(पूर्णांक, nents)
		__field(u32, handle)
		__field(u32, length)
		__field(u64, offset)
		__field(u32, dir)
	),

	TP_fast_assign(
		स्थिर काष्ठा rpcrdma_req *req = mr->mr_req;
		स्थिर काष्ठा rpc_task *task = req->rl_slot.rq_task;

		__entry->task_id = task->tk_pid;
		__entry->client_id = task->tk_client->cl_clid;
		__entry->mr_id  = mr->mr_ibmr->res.id;
		__entry->nents  = mr->mr_nents;
		__entry->handle = mr->mr_handle;
		__entry->length = mr->mr_length;
		__entry->offset = mr->mr_offset;
		__entry->dir    = mr->mr_dir;
	),

	TP_prपूर्णांकk("task:%u@%u mr.id=%u nents=%d %u@0x%016llx:0x%08x (%s)",
		__entry->task_id, __entry->client_id,
		__entry->mr_id, __entry->nents, __entry->length,
		(अचिन्हित दीर्घ दीर्घ)__entry->offset, __entry->handle,
		xprtrdma_show_direction(__entry->dir)
	)
);

#घोषणा DEFINE_MR_EVENT(name)						\
		DEFINE_EVENT(xprtrdma_mr_class,				\
				xprtrdma_mr_##name,			\
				TP_PROTO(				\
					स्थिर काष्ठा rpcrdma_mr *mr	\
				),					\
				TP_ARGS(mr))

DECLARE_EVENT_CLASS(xprtrdma_anonymous_mr_class,
	TP_PROTO(
		स्थिर काष्ठा rpcrdma_mr *mr
	),

	TP_ARGS(mr),

	TP_STRUCT__entry(
		__field(u32, mr_id)
		__field(पूर्णांक, nents)
		__field(u32, handle)
		__field(u32, length)
		__field(u64, offset)
		__field(u32, dir)
	),

	TP_fast_assign(
		__entry->mr_id  = mr->mr_ibmr->res.id;
		__entry->nents  = mr->mr_nents;
		__entry->handle = mr->mr_handle;
		__entry->length = mr->mr_length;
		__entry->offset = mr->mr_offset;
		__entry->dir    = mr->mr_dir;
	),

	TP_prपूर्णांकk("mr.id=%u nents=%d %u@0x%016llx:0x%08x (%s)",
		__entry->mr_id, __entry->nents, __entry->length,
		(अचिन्हित दीर्घ दीर्घ)__entry->offset, __entry->handle,
		xprtrdma_show_direction(__entry->dir)
	)
);

#घोषणा DEFINE_ANON_MR_EVENT(name)					\
		DEFINE_EVENT(xprtrdma_anonymous_mr_class,		\
				xprtrdma_mr_##name,			\
				TP_PROTO(				\
					स्थिर काष्ठा rpcrdma_mr *mr	\
				),					\
				TP_ARGS(mr))

DECLARE_EVENT_CLASS(xprtrdma_callback_class,
	TP_PROTO(
		स्थिर काष्ठा rpcrdma_xprt *r_xprt,
		स्थिर काष्ठा rpc_rqst *rqst
	),

	TP_ARGS(r_xprt, rqst),

	TP_STRUCT__entry(
		__field(u32, xid)
		__string(addr, rpcrdma_addrstr(r_xprt))
		__string(port, rpcrdma_portstr(r_xprt))
	),

	TP_fast_assign(
		__entry->xid = be32_to_cpu(rqst->rq_xid);
		__assign_str(addr, rpcrdma_addrstr(r_xprt));
		__assign_str(port, rpcrdma_portstr(r_xprt));
	),

	TP_prपूर्णांकk("peer=[%s]:%s xid=0x%08x",
		__get_str(addr), __get_str(port), __entry->xid
	)
);

#घोषणा DEFINE_CALLBACK_EVENT(name)					\
		DEFINE_EVENT(xprtrdma_callback_class,			\
				xprtrdma_cb_##name,			\
				TP_PROTO(				\
					स्थिर काष्ठा rpcrdma_xprt *r_xprt, \
					स्थिर काष्ठा rpc_rqst *rqst	\
				),					\
				TP_ARGS(r_xprt, rqst))

/**
 ** Connection events
 **/

TRACE_EVENT(xprtrdma_अंतरभूत_thresh,
	TP_PROTO(
		स्थिर काष्ठा rpcrdma_ep *ep
	),

	TP_ARGS(ep),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, अंतरभूत_send)
		__field(अचिन्हित पूर्णांक, अंतरभूत_recv)
		__field(अचिन्हित पूर्णांक, max_send)
		__field(अचिन्हित पूर्णांक, max_recv)
		__array(अचिन्हित अक्षर, srcaddr, माप(काष्ठा sockaddr_in6))
		__array(अचिन्हित अक्षर, dstaddr, माप(काष्ठा sockaddr_in6))
	),

	TP_fast_assign(
		स्थिर काष्ठा rdma_cm_id *id = ep->re_id;

		__entry->अंतरभूत_send = ep->re_अंतरभूत_send;
		__entry->अंतरभूत_recv = ep->re_अंतरभूत_recv;
		__entry->max_send = ep->re_max_अंतरभूत_send;
		__entry->max_recv = ep->re_max_अंतरभूत_recv;
		स_नकल(__entry->srcaddr, &id->route.addr.src_addr,
		       माप(काष्ठा sockaddr_in6));
		स_नकल(__entry->dstaddr, &id->route.addr.dst_addr,
		       माप(काष्ठा sockaddr_in6));
	),

	TP_prपूर्णांकk("%pISpc -> %pISpc neg send/recv=%u/%u, calc send/recv=%u/%u",
		__entry->srcaddr, __entry->dstaddr,
		__entry->अंतरभूत_send, __entry->अंतरभूत_recv,
		__entry->max_send, __entry->max_recv
	)
);

DEFINE_CONN_EVENT(connect);
DEFINE_CONN_EVENT(disconnect);

DEFINE_RXPRT_EVENT(xprtrdma_op_inject_dsc);

TRACE_EVENT(xprtrdma_op_connect,
	TP_PROTO(
		स्थिर काष्ठा rpcrdma_xprt *r_xprt,
		अचिन्हित दीर्घ delay
	),

	TP_ARGS(r_xprt, delay),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, delay)
		__string(addr, rpcrdma_addrstr(r_xprt))
		__string(port, rpcrdma_portstr(r_xprt))
	),

	TP_fast_assign(
		__entry->delay = delay;
		__assign_str(addr, rpcrdma_addrstr(r_xprt));
		__assign_str(port, rpcrdma_portstr(r_xprt));
	),

	TP_prपूर्णांकk("peer=[%s]:%s delay=%lu",
		__get_str(addr), __get_str(port), __entry->delay
	)
);


TRACE_EVENT(xprtrdma_op_set_cto,
	TP_PROTO(
		स्थिर काष्ठा rpcrdma_xprt *r_xprt,
		अचिन्हित दीर्घ connect,
		अचिन्हित दीर्घ reconnect
	),

	TP_ARGS(r_xprt, connect, reconnect),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, connect)
		__field(अचिन्हित दीर्घ, reconnect)
		__string(addr, rpcrdma_addrstr(r_xprt))
		__string(port, rpcrdma_portstr(r_xprt))
	),

	TP_fast_assign(
		__entry->connect = connect;
		__entry->reconnect = reconnect;
		__assign_str(addr, rpcrdma_addrstr(r_xprt));
		__assign_str(port, rpcrdma_portstr(r_xprt));
	),

	TP_prपूर्णांकk("peer=[%s]:%s connect=%lu reconnect=%lu",
		__get_str(addr), __get_str(port),
		__entry->connect / HZ, __entry->reconnect / HZ
	)
);

/**
 ** Call events
 **/

TRACE_EVENT(xprtrdma_createmrs,
	TP_PROTO(
		स्थिर काष्ठा rpcrdma_xprt *r_xprt,
		अचिन्हित पूर्णांक count
	),

	TP_ARGS(r_xprt, count),

	TP_STRUCT__entry(
		__string(addr, rpcrdma_addrstr(r_xprt))
		__string(port, rpcrdma_portstr(r_xprt))
		__field(अचिन्हित पूर्णांक, count)
	),

	TP_fast_assign(
		__entry->count = count;
		__assign_str(addr, rpcrdma_addrstr(r_xprt));
		__assign_str(port, rpcrdma_portstr(r_xprt));
	),

	TP_prपूर्णांकk("peer=[%s]:%s created %u MRs",
		__get_str(addr), __get_str(port), __entry->count
	)
);

TRACE_EVENT(xprtrdma_nomrs_err,
	TP_PROTO(
		स्थिर काष्ठा rpcrdma_xprt *r_xprt,
		स्थिर काष्ठा rpcrdma_req *req
	),

	TP_ARGS(r_xprt, req),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__string(addr, rpcrdma_addrstr(r_xprt))
		__string(port, rpcrdma_portstr(r_xprt))
	),

	TP_fast_assign(
		स्थिर काष्ठा rpc_rqst *rqst = &req->rl_slot;

		__entry->task_id = rqst->rq_task->tk_pid;
		__entry->client_id = rqst->rq_task->tk_client->cl_clid;
		__assign_str(addr, rpcrdma_addrstr(r_xprt));
		__assign_str(port, rpcrdma_portstr(r_xprt));
	),

	TP_prपूर्णांकk("peer=[%s]:%s task:%u@%u",
		__get_str(addr), __get_str(port),
		__entry->task_id, __entry->client_id
	)
);

DEFINE_RDCH_EVENT(पढ़ो);
DEFINE_WRCH_EVENT(ग_लिखो);
DEFINE_WRCH_EVENT(reply);

TRACE_DEFINE_ENUM(rpcrdma_noch);
TRACE_DEFINE_ENUM(rpcrdma_noch_pullup);
TRACE_DEFINE_ENUM(rpcrdma_noch_mapped);
TRACE_DEFINE_ENUM(rpcrdma_पढ़ोch);
TRACE_DEFINE_ENUM(rpcrdma_aपढ़ोch);
TRACE_DEFINE_ENUM(rpcrdma_ग_लिखोch);
TRACE_DEFINE_ENUM(rpcrdma_replych);

#घोषणा xprtrdma_show_chunktype(x)					\
		__prपूर्णांक_symbolic(x,					\
				अणु rpcrdma_noch, "inline" पूर्ण,		\
				अणु rpcrdma_noch_pullup, "pullup" पूर्ण,	\
				अणु rpcrdma_noch_mapped, "mapped" पूर्ण,	\
				अणु rpcrdma_पढ़ोch, "read list" पूर्ण,	\
				अणु rpcrdma_aपढ़ोch, "*read list" पूर्ण,	\
				अणु rpcrdma_ग_लिखोch, "write list" पूर्ण,	\
				अणु rpcrdma_replych, "reply chunk" पूर्ण)

TRACE_EVENT(xprtrdma_marshal,
	TP_PROTO(
		स्थिर काष्ठा rpcrdma_req *req,
		अचिन्हित पूर्णांक rtype,
		अचिन्हित पूर्णांक wtype
	),

	TP_ARGS(req, rtype, wtype),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(u32, xid)
		__field(अचिन्हित पूर्णांक, hdrlen)
		__field(अचिन्हित पूर्णांक, headlen)
		__field(अचिन्हित पूर्णांक, pagelen)
		__field(अचिन्हित पूर्णांक, taillen)
		__field(अचिन्हित पूर्णांक, rtype)
		__field(अचिन्हित पूर्णांक, wtype)
	),

	TP_fast_assign(
		स्थिर काष्ठा rpc_rqst *rqst = &req->rl_slot;

		__entry->task_id = rqst->rq_task->tk_pid;
		__entry->client_id = rqst->rq_task->tk_client->cl_clid;
		__entry->xid = be32_to_cpu(rqst->rq_xid);
		__entry->hdrlen = req->rl_hdrbuf.len;
		__entry->headlen = rqst->rq_snd_buf.head[0].iov_len;
		__entry->pagelen = rqst->rq_snd_buf.page_len;
		__entry->taillen = rqst->rq_snd_buf.tail[0].iov_len;
		__entry->rtype = rtype;
		__entry->wtype = wtype;
	),

	TP_prपूर्णांकk("task:%u@%u xid=0x%08x: hdr=%u xdr=%u/%u/%u %s/%s",
		__entry->task_id, __entry->client_id, __entry->xid,
		__entry->hdrlen,
		__entry->headlen, __entry->pagelen, __entry->taillen,
		xprtrdma_show_chunktype(__entry->rtype),
		xprtrdma_show_chunktype(__entry->wtype)
	)
);

TRACE_EVENT(xprtrdma_marshal_failed,
	TP_PROTO(स्थिर काष्ठा rpc_rqst *rqst,
		 पूर्णांक ret
	),

	TP_ARGS(rqst, ret),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(u32, xid)
		__field(पूर्णांक, ret)
	),

	TP_fast_assign(
		__entry->task_id = rqst->rq_task->tk_pid;
		__entry->client_id = rqst->rq_task->tk_client->cl_clid;
		__entry->xid = be32_to_cpu(rqst->rq_xid);
		__entry->ret = ret;
	),

	TP_prपूर्णांकk("task:%u@%u xid=0x%08x: ret=%d",
		__entry->task_id, __entry->client_id, __entry->xid,
		__entry->ret
	)
);

TRACE_EVENT(xprtrdma_prepsend_failed,
	TP_PROTO(स्थिर काष्ठा rpc_rqst *rqst,
		 पूर्णांक ret
	),

	TP_ARGS(rqst, ret),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(u32, xid)
		__field(पूर्णांक, ret)
	),

	TP_fast_assign(
		__entry->task_id = rqst->rq_task->tk_pid;
		__entry->client_id = rqst->rq_task->tk_client->cl_clid;
		__entry->xid = be32_to_cpu(rqst->rq_xid);
		__entry->ret = ret;
	),

	TP_prपूर्णांकk("task:%u@%u xid=0x%08x: ret=%d",
		__entry->task_id, __entry->client_id, __entry->xid,
		__entry->ret
	)
);

TRACE_EVENT(xprtrdma_post_send,
	TP_PROTO(
		स्थिर काष्ठा rpcrdma_req *req
	),

	TP_ARGS(req),

	TP_STRUCT__entry(
		__field(u32, cq_id)
		__field(पूर्णांक, completion_id)
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(पूर्णांक, num_sge)
		__field(पूर्णांक, संकेतed)
	),

	TP_fast_assign(
		स्थिर काष्ठा rpc_rqst *rqst = &req->rl_slot;
		स्थिर काष्ठा rpcrdma_sendctx *sc = req->rl_sendctx;

		__entry->cq_id = sc->sc_cid.ci_queue_id;
		__entry->completion_id = sc->sc_cid.ci_completion_id;
		__entry->task_id = rqst->rq_task->tk_pid;
		__entry->client_id = rqst->rq_task->tk_client ?
				     rqst->rq_task->tk_client->cl_clid : -1;
		__entry->num_sge = req->rl_wr.num_sge;
		__entry->संकेतed = req->rl_wr.send_flags & IB_SEND_SIGNALED;
	),

	TP_prपूर्णांकk("task:%u@%u cq.id=%u cid=%d (%d SGE%s) %s",
		__entry->task_id, __entry->client_id,
		__entry->cq_id, __entry->completion_id,
		__entry->num_sge, (__entry->num_sge == 1 ? "" : "s"),
		(__entry->संकेतed ? "signaled" : "")
	)
);

TRACE_EVENT(xprtrdma_post_recv,
	TP_PROTO(
		स्थिर काष्ठा rpcrdma_rep *rep
	),

	TP_ARGS(rep),

	TP_STRUCT__entry(
		__field(u32, cq_id)
		__field(पूर्णांक, completion_id)
	),

	TP_fast_assign(
		__entry->cq_id = rep->rr_cid.ci_queue_id;
		__entry->completion_id = rep->rr_cid.ci_completion_id;
	),

	TP_prपूर्णांकk("cq.id=%d cid=%d",
		__entry->cq_id, __entry->completion_id
	)
);

TRACE_EVENT(xprtrdma_post_recvs,
	TP_PROTO(
		स्थिर काष्ठा rpcrdma_xprt *r_xprt,
		अचिन्हित पूर्णांक count,
		पूर्णांक status
	),

	TP_ARGS(r_xprt, count, status),

	TP_STRUCT__entry(
		__field(u32, cq_id)
		__field(अचिन्हित पूर्णांक, count)
		__field(पूर्णांक, status)
		__field(पूर्णांक, posted)
		__string(addr, rpcrdma_addrstr(r_xprt))
		__string(port, rpcrdma_portstr(r_xprt))
	),

	TP_fast_assign(
		स्थिर काष्ठा rpcrdma_ep *ep = r_xprt->rx_ep;

		__entry->cq_id = ep->re_attr.recv_cq->res.id;
		__entry->count = count;
		__entry->status = status;
		__entry->posted = ep->re_receive_count;
		__assign_str(addr, rpcrdma_addrstr(r_xprt));
		__assign_str(port, rpcrdma_portstr(r_xprt));
	),

	TP_prपूर्णांकk("peer=[%s]:%s cq.id=%d %u new recvs, %d active (rc %d)",
		__get_str(addr), __get_str(port), __entry->cq_id,
		__entry->count, __entry->posted, __entry->status
	)
);

TRACE_EVENT(xprtrdma_post_linv_err,
	TP_PROTO(
		स्थिर काष्ठा rpcrdma_req *req,
		पूर्णांक status
	),

	TP_ARGS(req, status),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(पूर्णांक, status)
	),

	TP_fast_assign(
		स्थिर काष्ठा rpc_task *task = req->rl_slot.rq_task;

		__entry->task_id = task->tk_pid;
		__entry->client_id = task->tk_client->cl_clid;
		__entry->status = status;
	),

	TP_prपूर्णांकk("task:%u@%u status=%d",
		__entry->task_id, __entry->client_id, __entry->status
	)
);

/**
 ** Completion events
 **/

DEFINE_RECEIVE_COMPLETION_EVENT(xprtrdma_wc_receive);

DEFINE_COMPLETION_EVENT(xprtrdma_wc_send);
DEFINE_MR_COMPLETION_EVENT(xprtrdma_wc_fastreg);
DEFINE_MR_COMPLETION_EVENT(xprtrdma_wc_li);
DEFINE_MR_COMPLETION_EVENT(xprtrdma_wc_li_wake);
DEFINE_MR_COMPLETION_EVENT(xprtrdma_wc_li_करोne);

TRACE_EVENT(xprtrdma_frwr_alloc,
	TP_PROTO(
		स्थिर काष्ठा rpcrdma_mr *mr,
		पूर्णांक rc
	),

	TP_ARGS(mr, rc),

	TP_STRUCT__entry(
		__field(u32, mr_id)
		__field(पूर्णांक, rc)
	),

	TP_fast_assign(
		__entry->mr_id = mr->mr_ibmr->res.id;
		__entry->rc = rc;
	),

	TP_prपूर्णांकk("mr.id=%u: rc=%d",
		__entry->mr_id, __entry->rc
	)
);

TRACE_EVENT(xprtrdma_frwr_dereg,
	TP_PROTO(
		स्थिर काष्ठा rpcrdma_mr *mr,
		पूर्णांक rc
	),

	TP_ARGS(mr, rc),

	TP_STRUCT__entry(
		__field(u32, mr_id)
		__field(पूर्णांक, nents)
		__field(u32, handle)
		__field(u32, length)
		__field(u64, offset)
		__field(u32, dir)
		__field(पूर्णांक, rc)
	),

	TP_fast_assign(
		__entry->mr_id  = mr->mr_ibmr->res.id;
		__entry->nents  = mr->mr_nents;
		__entry->handle = mr->mr_handle;
		__entry->length = mr->mr_length;
		__entry->offset = mr->mr_offset;
		__entry->dir    = mr->mr_dir;
		__entry->rc	= rc;
	),

	TP_prपूर्णांकk("mr.id=%u nents=%d %u@0x%016llx:0x%08x (%s): rc=%d",
		__entry->mr_id, __entry->nents, __entry->length,
		(अचिन्हित दीर्घ दीर्घ)__entry->offset, __entry->handle,
		xprtrdma_show_direction(__entry->dir),
		__entry->rc
	)
);

TRACE_EVENT(xprtrdma_frwr_sgerr,
	TP_PROTO(
		स्थिर काष्ठा rpcrdma_mr *mr,
		पूर्णांक sg_nents
	),

	TP_ARGS(mr, sg_nents),

	TP_STRUCT__entry(
		__field(u32, mr_id)
		__field(u64, addr)
		__field(u32, dir)
		__field(पूर्णांक, nents)
	),

	TP_fast_assign(
		__entry->mr_id = mr->mr_ibmr->res.id;
		__entry->addr = mr->mr_sg->dma_address;
		__entry->dir = mr->mr_dir;
		__entry->nents = sg_nents;
	),

	TP_prपूर्णांकk("mr.id=%u DMA addr=0x%llx (%s) sg_nents=%d",
		__entry->mr_id, __entry->addr,
		xprtrdma_show_direction(__entry->dir),
		__entry->nents
	)
);

TRACE_EVENT(xprtrdma_frwr_maperr,
	TP_PROTO(
		स्थिर काष्ठा rpcrdma_mr *mr,
		पूर्णांक num_mapped
	),

	TP_ARGS(mr, num_mapped),

	TP_STRUCT__entry(
		__field(u32, mr_id)
		__field(u64, addr)
		__field(u32, dir)
		__field(पूर्णांक, num_mapped)
		__field(पूर्णांक, nents)
	),

	TP_fast_assign(
		__entry->mr_id = mr->mr_ibmr->res.id;
		__entry->addr = mr->mr_sg->dma_address;
		__entry->dir = mr->mr_dir;
		__entry->num_mapped = num_mapped;
		__entry->nents = mr->mr_nents;
	),

	TP_prपूर्णांकk("mr.id=%u DMA addr=0x%llx (%s) nents=%d of %d",
		__entry->mr_id, __entry->addr,
		xprtrdma_show_direction(__entry->dir),
		__entry->num_mapped, __entry->nents
	)
);

DEFINE_MR_EVENT(fastreg);
DEFINE_MR_EVENT(localinv);
DEFINE_MR_EVENT(reminv);
DEFINE_MR_EVENT(map);

DEFINE_ANON_MR_EVENT(unmap);

TRACE_EVENT(xprtrdma_dma_maperr,
	TP_PROTO(
		u64 addr
	),

	TP_ARGS(addr),

	TP_STRUCT__entry(
		__field(u64, addr)
	),

	TP_fast_assign(
		__entry->addr = addr;
	),

	TP_prपूर्णांकk("dma addr=0x%llx\n", __entry->addr)
);

/**
 ** Reply events
 **/

TRACE_EVENT(xprtrdma_reply,
	TP_PROTO(
		स्थिर काष्ठा rpc_task *task,
		स्थिर काष्ठा rpcrdma_rep *rep,
		अचिन्हित पूर्णांक credits
	),

	TP_ARGS(task, rep, credits),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(u32, xid)
		__field(अचिन्हित पूर्णांक, credits)
	),

	TP_fast_assign(
		__entry->task_id = task->tk_pid;
		__entry->client_id = task->tk_client->cl_clid;
		__entry->xid = be32_to_cpu(rep->rr_xid);
		__entry->credits = credits;
	),

	TP_prपूर्णांकk("task:%u@%u xid=0x%08x credits=%u",
		__entry->task_id, __entry->client_id, __entry->xid,
		__entry->credits
	)
);

DEFINE_REPLY_EVENT(vers);
DEFINE_REPLY_EVENT(rqst);
DEFINE_REPLY_EVENT(लघु);
DEFINE_REPLY_EVENT(hdr);

TRACE_EVENT(xprtrdma_err_vers,
	TP_PROTO(
		स्थिर काष्ठा rpc_rqst *rqst,
		__be32 *min,
		__be32 *max
	),

	TP_ARGS(rqst, min, max),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(u32, xid)
		__field(u32, min)
		__field(u32, max)
	),

	TP_fast_assign(
		__entry->task_id = rqst->rq_task->tk_pid;
		__entry->client_id = rqst->rq_task->tk_client->cl_clid;
		__entry->xid = be32_to_cpu(rqst->rq_xid);
		__entry->min = be32_to_cpup(min);
		__entry->max = be32_to_cpup(max);
	),

	TP_prपूर्णांकk("task:%u@%u xid=0x%08x versions=[%u, %u]",
		__entry->task_id, __entry->client_id, __entry->xid,
		__entry->min, __entry->max
	)
);

TRACE_EVENT(xprtrdma_err_chunk,
	TP_PROTO(
		स्थिर काष्ठा rpc_rqst *rqst
	),

	TP_ARGS(rqst),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(u32, xid)
	),

	TP_fast_assign(
		__entry->task_id = rqst->rq_task->tk_pid;
		__entry->client_id = rqst->rq_task->tk_client->cl_clid;
		__entry->xid = be32_to_cpu(rqst->rq_xid);
	),

	TP_prपूर्णांकk("task:%u@%u xid=0x%08x",
		__entry->task_id, __entry->client_id, __entry->xid
	)
);

TRACE_EVENT(xprtrdma_err_unrecognized,
	TP_PROTO(
		स्थिर काष्ठा rpc_rqst *rqst,
		__be32 *procedure
	),

	TP_ARGS(rqst, procedure),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(u32, xid)
		__field(u32, procedure)
	),

	TP_fast_assign(
		__entry->task_id = rqst->rq_task->tk_pid;
		__entry->client_id = rqst->rq_task->tk_client->cl_clid;
		__entry->procedure = be32_to_cpup(procedure);
	),

	TP_prपूर्णांकk("task:%u@%u xid=0x%08x procedure=%u",
		__entry->task_id, __entry->client_id, __entry->xid,
		__entry->procedure
	)
);

TRACE_EVENT(xprtrdma_fixup,
	TP_PROTO(
		स्थिर काष्ठा rpc_rqst *rqst,
		अचिन्हित दीर्घ fixup
	),

	TP_ARGS(rqst, fixup),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
		__field(अचिन्हित दीर्घ, fixup)
		__field(माप_प्रकार, headlen)
		__field(अचिन्हित पूर्णांक, pagelen)
		__field(माप_प्रकार, taillen)
	),

	TP_fast_assign(
		__entry->task_id = rqst->rq_task->tk_pid;
		__entry->client_id = rqst->rq_task->tk_client->cl_clid;
		__entry->fixup = fixup;
		__entry->headlen = rqst->rq_rcv_buf.head[0].iov_len;
		__entry->pagelen = rqst->rq_rcv_buf.page_len;
		__entry->taillen = rqst->rq_rcv_buf.tail[0].iov_len;
	),

	TP_prपूर्णांकk("task:%u@%u fixup=%lu xdr=%zu/%u/%zu",
		__entry->task_id, __entry->client_id, __entry->fixup,
		__entry->headlen, __entry->pagelen, __entry->taillen
	)
);

TRACE_EVENT(xprtrdma_decode_seg,
	TP_PROTO(
		u32 handle,
		u32 length,
		u64 offset
	),

	TP_ARGS(handle, length, offset),

	TP_STRUCT__entry(
		__field(u32, handle)
		__field(u32, length)
		__field(u64, offset)
	),

	TP_fast_assign(
		__entry->handle = handle;
		__entry->length = length;
		__entry->offset = offset;
	),

	TP_prपूर्णांकk("%u@0x%016llx:0x%08x",
		__entry->length, (अचिन्हित दीर्घ दीर्घ)__entry->offset,
		__entry->handle
	)
);

TRACE_EVENT(xprtrdma_mrs_zap,
	TP_PROTO(
		स्थिर काष्ठा rpc_task *task
	),

	TP_ARGS(task),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, task_id)
		__field(अचिन्हित पूर्णांक, client_id)
	),

	TP_fast_assign(
		__entry->task_id = task->tk_pid;
		__entry->client_id = task->tk_client->cl_clid;
	),

	TP_prपूर्णांकk("task:%u@%u",
		__entry->task_id, __entry->client_id
	)
);

/**
 ** Callback events
 **/

TRACE_EVENT(xprtrdma_cb_setup,
	TP_PROTO(
		स्थिर काष्ठा rpcrdma_xprt *r_xprt,
		अचिन्हित पूर्णांक reqs
	),

	TP_ARGS(r_xprt, reqs),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, reqs)
		__string(addr, rpcrdma_addrstr(r_xprt))
		__string(port, rpcrdma_portstr(r_xprt))
	),

	TP_fast_assign(
		__entry->reqs = reqs;
		__assign_str(addr, rpcrdma_addrstr(r_xprt));
		__assign_str(port, rpcrdma_portstr(r_xprt));
	),

	TP_prपूर्णांकk("peer=[%s]:%s %u reqs",
		__get_str(addr), __get_str(port), __entry->reqs
	)
);

DEFINE_CALLBACK_EVENT(call);
DEFINE_CALLBACK_EVENT(reply);

/**
 ** Server-side RPC/RDMA events
 **/

DECLARE_EVENT_CLASS(svcrdma_accept_class,
	TP_PROTO(
		स्थिर काष्ठा svcxprt_rdma *rdma,
		दीर्घ status
	),

	TP_ARGS(rdma, status),

	TP_STRUCT__entry(
		__field(दीर्घ, status)
		__string(addr, rdma->sc_xprt.xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->status = status;
		__assign_str(addr, rdma->sc_xprt.xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s status=%ld",
		__get_str(addr), __entry->status
	)
);

#घोषणा DEFINE_ACCEPT_EVENT(name) \
		DEFINE_EVENT(svcrdma_accept_class, svcrdma_##name##_err, \
				TP_PROTO( \
					स्थिर काष्ठा svcxprt_rdma *rdma, \
					दीर्घ status \
				), \
				TP_ARGS(rdma, status))

DEFINE_ACCEPT_EVENT(pd);
DEFINE_ACCEPT_EVENT(qp);
DEFINE_ACCEPT_EVENT(fabric);
DEFINE_ACCEPT_EVENT(initdepth);
DEFINE_ACCEPT_EVENT(accept);

TRACE_DEFINE_ENUM(RDMA_MSG);
TRACE_DEFINE_ENUM(RDMA_NOMSG);
TRACE_DEFINE_ENUM(RDMA_MSGP);
TRACE_DEFINE_ENUM(RDMA_DONE);
TRACE_DEFINE_ENUM(RDMA_ERROR);

#घोषणा show_rpcrdma_proc(x)						\
		__prपूर्णांक_symbolic(x,					\
				अणु RDMA_MSG, "RDMA_MSG" पूर्ण,		\
				अणु RDMA_NOMSG, "RDMA_NOMSG" पूर्ण,		\
				अणु RDMA_MSGP, "RDMA_MSGP" पूर्ण,		\
				अणु RDMA_DONE, "RDMA_DONE" पूर्ण,		\
				अणु RDMA_ERROR, "RDMA_ERROR" पूर्ण)

TRACE_EVENT(svcrdma_decode_rqst,
	TP_PROTO(
		स्थिर काष्ठा svc_rdma_recv_ctxt *ctxt,
		__be32 *p,
		अचिन्हित पूर्णांक hdrlen
	),

	TP_ARGS(ctxt, p, hdrlen),

	TP_STRUCT__entry(
		__field(u32, cq_id)
		__field(पूर्णांक, completion_id)
		__field(u32, xid)
		__field(u32, vers)
		__field(u32, proc)
		__field(u32, credits)
		__field(अचिन्हित पूर्णांक, hdrlen)
	),

	TP_fast_assign(
		__entry->cq_id = ctxt->rc_cid.ci_queue_id;
		__entry->completion_id = ctxt->rc_cid.ci_completion_id;
		__entry->xid = be32_to_cpup(p++);
		__entry->vers = be32_to_cpup(p++);
		__entry->credits = be32_to_cpup(p++);
		__entry->proc = be32_to_cpup(p);
		__entry->hdrlen = hdrlen;
	),

	TP_prपूर्णांकk("cq.id=%u cid=%d xid=0x%08x vers=%u credits=%u proc=%s hdrlen=%u",
		__entry->cq_id, __entry->completion_id,
		__entry->xid, __entry->vers, __entry->credits,
		show_rpcrdma_proc(__entry->proc), __entry->hdrlen)
);

TRACE_EVENT(svcrdma_decode_लघु_err,
	TP_PROTO(
		स्थिर काष्ठा svc_rdma_recv_ctxt *ctxt,
		अचिन्हित पूर्णांक hdrlen
	),

	TP_ARGS(ctxt, hdrlen),

	TP_STRUCT__entry(
		__field(u32, cq_id)
		__field(पूर्णांक, completion_id)
		__field(अचिन्हित पूर्णांक, hdrlen)
	),

	TP_fast_assign(
		__entry->cq_id = ctxt->rc_cid.ci_queue_id;
		__entry->completion_id = ctxt->rc_cid.ci_completion_id;
		__entry->hdrlen = hdrlen;
	),

	TP_prपूर्णांकk("cq.id=%u cid=%d hdrlen=%u",
		__entry->cq_id, __entry->completion_id,
		__entry->hdrlen)
);

DECLARE_EVENT_CLASS(svcrdma_badreq_event,
	TP_PROTO(
		स्थिर काष्ठा svc_rdma_recv_ctxt *ctxt,
		__be32 *p
	),

	TP_ARGS(ctxt, p),

	TP_STRUCT__entry(
		__field(u32, cq_id)
		__field(पूर्णांक, completion_id)
		__field(u32, xid)
		__field(u32, vers)
		__field(u32, proc)
		__field(u32, credits)
	),

	TP_fast_assign(
		__entry->cq_id = ctxt->rc_cid.ci_queue_id;
		__entry->completion_id = ctxt->rc_cid.ci_completion_id;
		__entry->xid = be32_to_cpup(p++);
		__entry->vers = be32_to_cpup(p++);
		__entry->credits = be32_to_cpup(p++);
		__entry->proc = be32_to_cpup(p);
	),

	TP_prपूर्णांकk("cq.id=%u cid=%d xid=0x%08x vers=%u credits=%u proc=%u",
		__entry->cq_id, __entry->completion_id,
		__entry->xid, __entry->vers, __entry->credits, __entry->proc)
);

#घोषणा DEFINE_BADREQ_EVENT(name)					\
		DEFINE_EVENT(svcrdma_badreq_event,			\
			     svcrdma_decode_##name##_err,		\
				TP_PROTO(				\
					स्थिर काष्ठा svc_rdma_recv_ctxt *ctxt,	\
					__be32 *p			\
				),					\
				TP_ARGS(ctxt, p))

DEFINE_BADREQ_EVENT(badvers);
DEFINE_BADREQ_EVENT(drop);
DEFINE_BADREQ_EVENT(badproc);
DEFINE_BADREQ_EVENT(parse);

TRACE_EVENT(svcrdma_encode_wseg,
	TP_PROTO(
		स्थिर काष्ठा svc_rdma_send_ctxt *ctxt,
		u32 segno,
		u32 handle,
		u32 length,
		u64 offset
	),

	TP_ARGS(ctxt, segno, handle, length, offset),

	TP_STRUCT__entry(
		__field(u32, cq_id)
		__field(पूर्णांक, completion_id)
		__field(u32, segno)
		__field(u32, handle)
		__field(u32, length)
		__field(u64, offset)
	),

	TP_fast_assign(
		__entry->cq_id = ctxt->sc_cid.ci_queue_id;
		__entry->completion_id = ctxt->sc_cid.ci_completion_id;
		__entry->segno = segno;
		__entry->handle = handle;
		__entry->length = length;
		__entry->offset = offset;
	),

	TP_prपूर्णांकk("cq_id=%u cid=%d segno=%u %u@0x%016llx:0x%08x",
		__entry->cq_id, __entry->completion_id,
		__entry->segno, __entry->length,
		(अचिन्हित दीर्घ दीर्घ)__entry->offset, __entry->handle
	)
);

TRACE_EVENT(svcrdma_decode_rseg,
	TP_PROTO(
		स्थिर काष्ठा rpc_rdma_cid *cid,
		स्थिर काष्ठा svc_rdma_chunk *chunk,
		स्थिर काष्ठा svc_rdma_segment *segment
	),

	TP_ARGS(cid, chunk, segment),

	TP_STRUCT__entry(
		__field(u32, cq_id)
		__field(पूर्णांक, completion_id)
		__field(u32, segno)
		__field(u32, position)
		__field(u32, handle)
		__field(u32, length)
		__field(u64, offset)
	),

	TP_fast_assign(
		__entry->cq_id = cid->ci_queue_id;
		__entry->completion_id = cid->ci_completion_id;
		__entry->segno = chunk->ch_segcount;
		__entry->position = chunk->ch_position;
		__entry->handle = segment->rs_handle;
		__entry->length = segment->rs_length;
		__entry->offset = segment->rs_offset;
	),

	TP_prपूर्णांकk("cq_id=%u cid=%d segno=%u position=%u %u@0x%016llx:0x%08x",
		__entry->cq_id, __entry->completion_id,
		__entry->segno, __entry->position, __entry->length,
		(अचिन्हित दीर्घ दीर्घ)__entry->offset, __entry->handle
	)
);

TRACE_EVENT(svcrdma_decode_wseg,
	TP_PROTO(
		स्थिर काष्ठा rpc_rdma_cid *cid,
		स्थिर काष्ठा svc_rdma_chunk *chunk,
		u32 segno
	),

	TP_ARGS(cid, chunk, segno),

	TP_STRUCT__entry(
		__field(u32, cq_id)
		__field(पूर्णांक, completion_id)
		__field(u32, segno)
		__field(u32, handle)
		__field(u32, length)
		__field(u64, offset)
	),

	TP_fast_assign(
		स्थिर काष्ठा svc_rdma_segment *segment =
			&chunk->ch_segments[segno];

		__entry->cq_id = cid->ci_queue_id;
		__entry->completion_id = cid->ci_completion_id;
		__entry->segno = segno;
		__entry->handle = segment->rs_handle;
		__entry->length = segment->rs_length;
		__entry->offset = segment->rs_offset;
	),

	TP_prपूर्णांकk("cq_id=%u cid=%d segno=%u %u@0x%016llx:0x%08x",
		__entry->cq_id, __entry->completion_id,
		__entry->segno, __entry->length,
		(अचिन्हित दीर्घ दीर्घ)__entry->offset, __entry->handle
	)
);

DECLARE_EVENT_CLASS(svcrdma_error_event,
	TP_PROTO(
		__be32 xid
	),

	TP_ARGS(xid),

	TP_STRUCT__entry(
		__field(u32, xid)
	),

	TP_fast_assign(
		__entry->xid = be32_to_cpu(xid);
	),

	TP_prपूर्णांकk("xid=0x%08x",
		__entry->xid
	)
);

#घोषणा DEFINE_ERROR_EVENT(name)					\
		DEFINE_EVENT(svcrdma_error_event, svcrdma_err_##name,	\
				TP_PROTO(				\
					__be32 xid			\
				),					\
				TP_ARGS(xid))

DEFINE_ERROR_EVENT(vers);
DEFINE_ERROR_EVENT(chunk);

/**
 ** Server-side RDMA API events
 **/

DECLARE_EVENT_CLASS(svcrdma_dma_map_class,
	TP_PROTO(
		स्थिर काष्ठा svcxprt_rdma *rdma,
		u64 dma_addr,
		u32 length
	),

	TP_ARGS(rdma, dma_addr, length),

	TP_STRUCT__entry(
		__field(u64, dma_addr)
		__field(u32, length)
		__string(device, rdma->sc_cm_id->device->name)
		__string(addr, rdma->sc_xprt.xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->dma_addr = dma_addr;
		__entry->length = length;
		__assign_str(device, rdma->sc_cm_id->device->name);
		__assign_str(addr, rdma->sc_xprt.xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s device=%s dma_addr=%llu length=%u",
		__get_str(addr), __get_str(device),
		__entry->dma_addr, __entry->length
	)
);

#घोषणा DEFINE_SVC_DMA_EVENT(name)					\
		DEFINE_EVENT(svcrdma_dma_map_class, svcrdma_##name,	\
				TP_PROTO(				\
					स्थिर काष्ठा svcxprt_rdma *rdma,\
					u64 dma_addr,			\
					u32 length			\
				),					\
				TP_ARGS(rdma, dma_addr, length))

DEFINE_SVC_DMA_EVENT(dma_map_page);
DEFINE_SVC_DMA_EVENT(dma_map_err);
DEFINE_SVC_DMA_EVENT(dma_unmap_page);

TRACE_EVENT(svcrdma_dma_map_rw_err,
	TP_PROTO(
		स्थिर काष्ठा svcxprt_rdma *rdma,
		अचिन्हित पूर्णांक nents,
		पूर्णांक status
	),

	TP_ARGS(rdma, nents, status),

	TP_STRUCT__entry(
		__field(पूर्णांक, status)
		__field(अचिन्हित पूर्णांक, nents)
		__string(device, rdma->sc_cm_id->device->name)
		__string(addr, rdma->sc_xprt.xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->status = status;
		__entry->nents = nents;
		__assign_str(device, rdma->sc_cm_id->device->name);
		__assign_str(addr, rdma->sc_xprt.xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s device=%s nents=%u status=%d",
		__get_str(addr), __get_str(device), __entry->nents,
		__entry->status
	)
);

TRACE_EVENT(svcrdma_no_rwctx_err,
	TP_PROTO(
		स्थिर काष्ठा svcxprt_rdma *rdma,
		अचिन्हित पूर्णांक num_sges
	),

	TP_ARGS(rdma, num_sges),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, num_sges)
		__string(device, rdma->sc_cm_id->device->name)
		__string(addr, rdma->sc_xprt.xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->num_sges = num_sges;
		__assign_str(device, rdma->sc_cm_id->device->name);
		__assign_str(addr, rdma->sc_xprt.xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s device=%s num_sges=%d",
		__get_str(addr), __get_str(device), __entry->num_sges
	)
);

TRACE_EVENT(svcrdma_page_overrun_err,
	TP_PROTO(
		स्थिर काष्ठा svcxprt_rdma *rdma,
		स्थिर काष्ठा svc_rqst *rqst,
		अचिन्हित पूर्णांक pageno
	),

	TP_ARGS(rdma, rqst, pageno),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, pageno)
		__field(u32, xid)
		__string(device, rdma->sc_cm_id->device->name)
		__string(addr, rdma->sc_xprt.xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->pageno = pageno;
		__entry->xid = __be32_to_cpu(rqst->rq_xid);
		__assign_str(device, rdma->sc_cm_id->device->name);
		__assign_str(addr, rdma->sc_xprt.xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s device=%s xid=0x%08x pageno=%u", __get_str(addr),
		__get_str(device), __entry->xid, __entry->pageno
	)
);

TRACE_EVENT(svcrdma_small_wrch_err,
	TP_PROTO(
		स्थिर काष्ठा svcxprt_rdma *rdma,
		अचिन्हित पूर्णांक reमुख्यing,
		अचिन्हित पूर्णांक seg_no,
		अचिन्हित पूर्णांक num_segs
	),

	TP_ARGS(rdma, reमुख्यing, seg_no, num_segs),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, reमुख्यing)
		__field(अचिन्हित पूर्णांक, seg_no)
		__field(अचिन्हित पूर्णांक, num_segs)
		__string(device, rdma->sc_cm_id->device->name)
		__string(addr, rdma->sc_xprt.xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->reमुख्यing = reमुख्यing;
		__entry->seg_no = seg_no;
		__entry->num_segs = num_segs;
		__assign_str(device, rdma->sc_cm_id->device->name);
		__assign_str(addr, rdma->sc_xprt.xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s device=%s remaining=%u seg_no=%u num_segs=%u",
		__get_str(addr), __get_str(device), __entry->reमुख्यing,
		__entry->seg_no, __entry->num_segs
	)
);

TRACE_EVENT(svcrdma_send_pullup,
	TP_PROTO(
		स्थिर काष्ठा svc_rdma_send_ctxt *ctxt,
		अचिन्हित पूर्णांक msglen
	),

	TP_ARGS(ctxt, msglen),

	TP_STRUCT__entry(
		__field(u32, cq_id)
		__field(पूर्णांक, completion_id)
		__field(अचिन्हित पूर्णांक, hdrlen)
		__field(अचिन्हित पूर्णांक, msglen)
	),

	TP_fast_assign(
		__entry->cq_id = ctxt->sc_cid.ci_queue_id;
		__entry->completion_id = ctxt->sc_cid.ci_completion_id;
		__entry->hdrlen = ctxt->sc_hdrbuf.len,
		__entry->msglen = msglen;
	),

	TP_prपूर्णांकk("cq_id=%u cid=%d hdr=%u msg=%u (total %u)",
		__entry->cq_id, __entry->completion_id,
		__entry->hdrlen, __entry->msglen,
		__entry->hdrlen + __entry->msglen)
);

TRACE_EVENT(svcrdma_send_err,
	TP_PROTO(
		स्थिर काष्ठा svc_rqst *rqst,
		पूर्णांक status
	),

	TP_ARGS(rqst, status),

	TP_STRUCT__entry(
		__field(पूर्णांक, status)
		__field(u32, xid)
		__string(addr, rqst->rq_xprt->xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->status = status;
		__entry->xid = __be32_to_cpu(rqst->rq_xid);
		__assign_str(addr, rqst->rq_xprt->xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s xid=0x%08x status=%d", __get_str(addr),
		__entry->xid, __entry->status
	)
);

TRACE_EVENT(svcrdma_post_send,
	TP_PROTO(
		स्थिर काष्ठा svc_rdma_send_ctxt *ctxt
	),

	TP_ARGS(ctxt),

	TP_STRUCT__entry(
		__field(u32, cq_id)
		__field(पूर्णांक, completion_id)
		__field(अचिन्हित पूर्णांक, num_sge)
		__field(u32, inv_rkey)
	),

	TP_fast_assign(
		स्थिर काष्ठा ib_send_wr *wr = &ctxt->sc_send_wr;

		__entry->cq_id = ctxt->sc_cid.ci_queue_id;
		__entry->completion_id = ctxt->sc_cid.ci_completion_id;
		__entry->num_sge = wr->num_sge;
		__entry->inv_rkey = (wr->opcode == IB_WR_SEND_WITH_INV) ?
					wr->ex.invalidate_rkey : 0;
	),

	TP_prपूर्णांकk("cq_id=%u cid=%d num_sge=%u inv_rkey=0x%08x",
		__entry->cq_id, __entry->completion_id,
		__entry->num_sge, __entry->inv_rkey
	)
);

DEFINE_COMPLETION_EVENT(svcrdma_wc_send);

TRACE_EVENT(svcrdma_post_recv,
	TP_PROTO(
		स्थिर काष्ठा svc_rdma_recv_ctxt *ctxt
	),

	TP_ARGS(ctxt),

	TP_STRUCT__entry(
		__field(u32, cq_id)
		__field(पूर्णांक, completion_id)
	),

	TP_fast_assign(
		__entry->cq_id = ctxt->rc_cid.ci_queue_id;
		__entry->completion_id = ctxt->rc_cid.ci_completion_id;
	),

	TP_prपूर्णांकk("cq.id=%d cid=%d",
		__entry->cq_id, __entry->completion_id
	)
);

DEFINE_RECEIVE_COMPLETION_EVENT(svcrdma_wc_receive);

TRACE_EVENT(svcrdma_rq_post_err,
	TP_PROTO(
		स्थिर काष्ठा svcxprt_rdma *rdma,
		पूर्णांक status
	),

	TP_ARGS(rdma, status),

	TP_STRUCT__entry(
		__field(पूर्णांक, status)
		__string(addr, rdma->sc_xprt.xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->status = status;
		__assign_str(addr, rdma->sc_xprt.xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s status=%d",
		__get_str(addr), __entry->status
	)
);

DECLARE_EVENT_CLASS(svcrdma_post_chunk_class,
	TP_PROTO(
		स्थिर काष्ठा rpc_rdma_cid *cid,
		पूर्णांक sqecount
	),

	TP_ARGS(cid, sqecount),

	TP_STRUCT__entry(
		__field(u32, cq_id)
		__field(पूर्णांक, completion_id)
		__field(पूर्णांक, sqecount)
	),

	TP_fast_assign(
		__entry->cq_id = cid->ci_queue_id;
		__entry->completion_id = cid->ci_completion_id;
		__entry->sqecount = sqecount;
	),

	TP_prपूर्णांकk("cq.id=%u cid=%d sqecount=%d",
		__entry->cq_id, __entry->completion_id,
		__entry->sqecount
	)
);

#घोषणा DEFINE_POST_CHUNK_EVENT(name)					\
		DEFINE_EVENT(svcrdma_post_chunk_class,			\
				svcrdma_post_##name##_chunk,		\
				TP_PROTO(				\
					स्थिर काष्ठा rpc_rdma_cid *cid,	\
					पूर्णांक sqecount			\
				),					\
				TP_ARGS(cid, sqecount))

DEFINE_POST_CHUNK_EVENT(पढ़ो);
DEFINE_POST_CHUNK_EVENT(ग_लिखो);
DEFINE_POST_CHUNK_EVENT(reply);

DEFINE_COMPLETION_EVENT(svcrdma_wc_पढ़ो);
DEFINE_COMPLETION_EVENT(svcrdma_wc_ग_लिखो);

TRACE_EVENT(svcrdma_qp_error,
	TP_PROTO(
		स्थिर काष्ठा ib_event *event,
		स्थिर काष्ठा sockaddr *sap
	),

	TP_ARGS(event, sap),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, event)
		__string(device, event->device->name)
		__array(__u8, addr, INET6_ADDRSTRLEN + 10)
	),

	TP_fast_assign(
		__entry->event = event->event;
		__assign_str(device, event->device->name);
		snम_लिखो(__entry->addr, माप(__entry->addr) - 1,
			 "%pISpc", sap);
	),

	TP_prपूर्णांकk("addr=%s dev=%s event=%s (%u)",
		__entry->addr, __get_str(device),
		rdma_show_ib_event(__entry->event), __entry->event
	)
);

DECLARE_EVENT_CLASS(svcrdma_sendqueue_event,
	TP_PROTO(
		स्थिर काष्ठा svcxprt_rdma *rdma
	),

	TP_ARGS(rdma),

	TP_STRUCT__entry(
		__field(पूर्णांक, avail)
		__field(पूर्णांक, depth)
		__string(addr, rdma->sc_xprt.xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->avail = atomic_पढ़ो(&rdma->sc_sq_avail);
		__entry->depth = rdma->sc_sq_depth;
		__assign_str(addr, rdma->sc_xprt.xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s sc_sq_avail=%d/%d",
		__get_str(addr), __entry->avail, __entry->depth
	)
);

#घोषणा DEFINE_SQ_EVENT(name)						\
		DEFINE_EVENT(svcrdma_sendqueue_event, svcrdma_sq_##name,\
				TP_PROTO(				\
					स्थिर काष्ठा svcxprt_rdma *rdma \
				),					\
				TP_ARGS(rdma))

DEFINE_SQ_EVENT(full);
DEFINE_SQ_EVENT(retry);

TRACE_EVENT(svcrdma_sq_post_err,
	TP_PROTO(
		स्थिर काष्ठा svcxprt_rdma *rdma,
		पूर्णांक status
	),

	TP_ARGS(rdma, status),

	TP_STRUCT__entry(
		__field(पूर्णांक, avail)
		__field(पूर्णांक, depth)
		__field(पूर्णांक, status)
		__string(addr, rdma->sc_xprt.xpt_remotebuf)
	),

	TP_fast_assign(
		__entry->avail = atomic_पढ़ो(&rdma->sc_sq_avail);
		__entry->depth = rdma->sc_sq_depth;
		__entry->status = status;
		__assign_str(addr, rdma->sc_xprt.xpt_remotebuf);
	),

	TP_prपूर्णांकk("addr=%s sc_sq_avail=%d/%d status=%d",
		__get_str(addr), __entry->avail, __entry->depth,
		__entry->status
	)
);

#पूर्ण_अगर /* _TRACE_RPCRDMA_H */

#समावेश <trace/define_trace.h>
