<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (c) 2005-2006 Network Appliance, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the BSD-type
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *      Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *      Redistributions in binary क्रमm must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the करोcumentation and/or other materials provided
 *      with the distribution.
 *
 *      Neither the name of the Network Appliance, Inc. nor the names of
 *      its contributors may be used to enकरोrse or promote products
 *      derived from this software without specअगरic prior written
 *      permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: Tom Tucker <tom@खोलोgridcomputing.com>
 */

#अगर_अघोषित SVC_RDMA_H
#घोषणा SVC_RDMA_H
#समावेश <linux/llist.h>
#समावेश <linux/sunrpc/xdr.h>
#समावेश <linux/sunrpc/svcsock.h>
#समावेश <linux/sunrpc/rpc_rdma.h>
#समावेश <linux/sunrpc/rpc_rdma_cid.h>
#समावेश <linux/sunrpc/svc_rdma_pcl.h>

#समावेश <linux/percpu_counter.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/rdma_cm.h>

/* Default and maximum अंतरभूत threshold sizes */
क्रमागत अणु
	RPCRDMA_PULLUP_THRESH = RPCRDMA_V1_DEF_INLINE_SIZE >> 1,
	RPCRDMA_DEF_INLINE_THRESH = 4096,
	RPCRDMA_MAX_INLINE_THRESH = 65536
पूर्ण;

/* RPC/RDMA parameters and stats */
बाह्य अचिन्हित पूर्णांक svcrdma_ord;
बाह्य अचिन्हित पूर्णांक svcrdma_max_requests;
बाह्य अचिन्हित पूर्णांक svcrdma_max_bc_requests;
बाह्य अचिन्हित पूर्णांक svcrdma_max_req_size;

बाह्य काष्ठा percpu_counter svcrdma_stat_पढ़ो;
बाह्य काष्ठा percpu_counter svcrdma_stat_recv;
बाह्य काष्ठा percpu_counter svcrdma_stat_sq_starve;
बाह्य काष्ठा percpu_counter svcrdma_stat_ग_लिखो;

काष्ठा svcxprt_rdma अणु
	काष्ठा svc_xprt      sc_xprt;		/* SVC transport काष्ठाure */
	काष्ठा rdma_cm_id    *sc_cm_id;		/* RDMA connection id */
	काष्ठा list_head     sc_accept_q;	/* Conn. रुकोing accept */
	पूर्णांक		     sc_ord;		/* RDMA पढ़ो limit */
	पूर्णांक                  sc_max_send_sges;
	bool		     sc_snd_w_inv;	/* OK to use Send With Invalidate */

	atomic_t             sc_sq_avail;	/* SQEs पढ़ोy to be consumed */
	अचिन्हित पूर्णांक	     sc_sq_depth;	/* Depth of SQ */
	__be32		     sc_fc_credits;	/* Forward credits */
	u32		     sc_max_requests;	/* Max requests */
	u32		     sc_max_bc_requests;/* Backward credits */
	पूर्णांक                  sc_max_req_size;	/* Size of each RQ WR buf */
	u8		     sc_port_num;

	काष्ठा ib_pd         *sc_pd;

	spinlock_t	     sc_send_lock;
	काष्ठा list_head     sc_send_ctxts;
	spinlock_t	     sc_rw_ctxt_lock;
	काष्ठा list_head     sc_rw_ctxts;

	u32		     sc_pending_recvs;
	u32		     sc_recv_batch;
	काष्ठा list_head     sc_rq_dto_q;
	spinlock_t	     sc_rq_dto_lock;
	काष्ठा ib_qp         *sc_qp;
	काष्ठा ib_cq         *sc_rq_cq;
	काष्ठा ib_cq         *sc_sq_cq;

	spinlock_t	     sc_lock;		/* transport lock */

	रुको_queue_head_t    sc_send_रुको;	/* SQ exhaustion रुकोlist */
	अचिन्हित दीर्घ	     sc_flags;
	काष्ठा work_काष्ठा   sc_work;

	काष्ठा llist_head    sc_recv_ctxts;

	atomic_t	     sc_completion_ids;
पूर्ण;
/* sc_flags */
#घोषणा RDMAXPRT_CONN_PENDING	3

/*
 * Default connection parameters
 */
क्रमागत अणु
	RPCRDMA_LISTEN_BACKLOG	= 10,
	RPCRDMA_MAX_REQUESTS	= 64,
	RPCRDMA_MAX_BC_REQUESTS	= 2,
पूर्ण;

#घोषणा RPCSVC_MAXPAYLOAD_RDMA	RPCSVC_MAXPAYLOAD

काष्ठा svc_rdma_recv_ctxt अणु
	काष्ठा llist_node	rc_node;
	काष्ठा list_head	rc_list;
	काष्ठा ib_recv_wr	rc_recv_wr;
	काष्ठा ib_cqe		rc_cqe;
	काष्ठा rpc_rdma_cid	rc_cid;
	काष्ठा ib_sge		rc_recv_sge;
	व्योम			*rc_recv_buf;
	काष्ठा xdr_stream	rc_stream;
	bool			rc_temp;
	u32			rc_byte_len;
	अचिन्हित पूर्णांक		rc_page_count;
	u32			rc_inv_rkey;
	__be32			rc_msgtype;

	काष्ठा svc_rdma_pcl	rc_call_pcl;

	काष्ठा svc_rdma_pcl	rc_पढ़ो_pcl;
	काष्ठा svc_rdma_chunk	*rc_cur_result_payload;
	काष्ठा svc_rdma_pcl	rc_ग_लिखो_pcl;
	काष्ठा svc_rdma_pcl	rc_reply_pcl;
पूर्ण;

काष्ठा svc_rdma_send_ctxt अणु
	काष्ठा list_head	sc_list;
	काष्ठा rpc_rdma_cid	sc_cid;

	काष्ठा ib_send_wr	sc_send_wr;
	काष्ठा ib_cqe		sc_cqe;
	काष्ठा completion	sc_करोne;
	काष्ठा xdr_buf		sc_hdrbuf;
	काष्ठा xdr_stream	sc_stream;
	व्योम			*sc_xprt_buf;
	पूर्णांक			sc_cur_sge_no;

	काष्ठा ib_sge		sc_sges[];
पूर्ण;

/* svc_rdma_backchannel.c */
बाह्य व्योम svc_rdma_handle_bc_reply(काष्ठा svc_rqst *rqstp,
				     काष्ठा svc_rdma_recv_ctxt *rctxt);

/* svc_rdma_recvfrom.c */
बाह्य व्योम svc_rdma_recv_ctxts_destroy(काष्ठा svcxprt_rdma *rdma);
बाह्य bool svc_rdma_post_recvs(काष्ठा svcxprt_rdma *rdma);
बाह्य काष्ठा svc_rdma_recv_ctxt *
		svc_rdma_recv_ctxt_get(काष्ठा svcxprt_rdma *rdma);
बाह्य व्योम svc_rdma_recv_ctxt_put(काष्ठा svcxprt_rdma *rdma,
				   काष्ठा svc_rdma_recv_ctxt *ctxt);
बाह्य व्योम svc_rdma_flush_recv_queues(काष्ठा svcxprt_rdma *rdma);
बाह्य व्योम svc_rdma_release_rqst(काष्ठा svc_rqst *rqstp);
बाह्य पूर्णांक svc_rdma_recvfrom(काष्ठा svc_rqst *);

/* svc_rdma_rw.c */
बाह्य व्योम svc_rdma_destroy_rw_ctxts(काष्ठा svcxprt_rdma *rdma);
बाह्य पूर्णांक svc_rdma_send_ग_लिखो_chunk(काष्ठा svcxprt_rdma *rdma,
				     स्थिर काष्ठा svc_rdma_chunk *chunk,
				     स्थिर काष्ठा xdr_buf *xdr);
बाह्य पूर्णांक svc_rdma_send_reply_chunk(काष्ठा svcxprt_rdma *rdma,
				     स्थिर काष्ठा svc_rdma_recv_ctxt *rctxt,
				     स्थिर काष्ठा xdr_buf *xdr);
बाह्य पूर्णांक svc_rdma_process_पढ़ो_list(काष्ठा svcxprt_rdma *rdma,
				      काष्ठा svc_rqst *rqstp,
				      काष्ठा svc_rdma_recv_ctxt *head);

/* svc_rdma_sendto.c */
बाह्य व्योम svc_rdma_send_ctxts_destroy(काष्ठा svcxprt_rdma *rdma);
बाह्य काष्ठा svc_rdma_send_ctxt *
		svc_rdma_send_ctxt_get(काष्ठा svcxprt_rdma *rdma);
बाह्य व्योम svc_rdma_send_ctxt_put(काष्ठा svcxprt_rdma *rdma,
				   काष्ठा svc_rdma_send_ctxt *ctxt);
बाह्य पूर्णांक svc_rdma_send(काष्ठा svcxprt_rdma *rdma,
			 काष्ठा svc_rdma_send_ctxt *ctxt);
बाह्य पूर्णांक svc_rdma_map_reply_msg(काष्ठा svcxprt_rdma *rdma,
				  काष्ठा svc_rdma_send_ctxt *sctxt,
				  स्थिर काष्ठा svc_rdma_recv_ctxt *rctxt,
				  स्थिर काष्ठा xdr_buf *xdr);
बाह्य व्योम svc_rdma_send_error_msg(काष्ठा svcxprt_rdma *rdma,
				    काष्ठा svc_rdma_send_ctxt *sctxt,
				    काष्ठा svc_rdma_recv_ctxt *rctxt,
				    पूर्णांक status);
बाह्य पूर्णांक svc_rdma_sendto(काष्ठा svc_rqst *);
बाह्य पूर्णांक svc_rdma_result_payload(काष्ठा svc_rqst *rqstp, अचिन्हित पूर्णांक offset,
				   अचिन्हित पूर्णांक length);

/* svc_rdma_transport.c */
बाह्य काष्ठा svc_xprt_class svc_rdma_class;
#अगर_घोषित CONFIG_SUNRPC_BACKCHANNEL
बाह्य काष्ठा svc_xprt_class svc_rdma_bc_class;
#पूर्ण_अगर

/* svc_rdma.c */
बाह्य पूर्णांक svc_rdma_init(व्योम);
बाह्य व्योम svc_rdma_cleanup(व्योम);

#पूर्ण_अगर
