<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (c) 2014-2017 Oracle.  All rights reserved.
 * Copyright (c) 2003-2007 Network Appliance, Inc. All rights reserved.
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
 */

#अगर_अघोषित _LINUX_SUNRPC_XPRT_RDMA_H
#घोषणा _LINUX_SUNRPC_XPRT_RDMA_H

#समावेश <linux/रुको.h> 		/* रुको_queue_head_t, etc */
#समावेश <linux/spinlock.h> 		/* spinlock_t, etc */
#समावेश <linux/atomic.h>		/* atomic_t, etc */
#समावेश <linux/kref.h>			/* काष्ठा kref */
#समावेश <linux/workqueue.h>		/* काष्ठा work_काष्ठा */
#समावेश <linux/llist.h>

#समावेश <rdma/rdma_cm.h>		/* RDMA connection api */
#समावेश <rdma/ib_verbs.h>		/* RDMA verbs api */

#समावेश <linux/sunrpc/clnt.h> 		/* rpc_xprt */
#समावेश <linux/sunrpc/rpc_rdma_cid.h> 	/* completion IDs */
#समावेश <linux/sunrpc/rpc_rdma.h> 	/* RPC/RDMA protocol */
#समावेश <linux/sunrpc/xprtrdma.h> 	/* xprt parameters */

#घोषणा RDMA_RESOLVE_TIMEOUT	(5000)	/* 5 seconds */
#घोषणा RDMA_CONNECT_RETRY_MAX	(2)	/* retries अगर no listener backlog */

#घोषणा RPCRDMA_BIND_TO		(60U * HZ)
#घोषणा RPCRDMA_INIT_REEST_TO	(5U * HZ)
#घोषणा RPCRDMA_MAX_REEST_TO	(30U * HZ)
#घोषणा RPCRDMA_IDLE_DISC_TO	(5U * 60 * HZ)

/*
 * RDMA Endpoपूर्णांक -- connection endpoपूर्णांक details
 */
काष्ठा rpcrdma_ep अणु
	काष्ठा kref		re_kref;
	काष्ठा rdma_cm_id 	*re_id;
	काष्ठा ib_pd		*re_pd;
	अचिन्हित पूर्णांक		re_max_rdma_segs;
	अचिन्हित पूर्णांक		re_max_fr_depth;
	bool			re_implicit_roundup;
	क्रमागत ib_mr_type		re_mrtype;
	काष्ठा completion	re_करोne;
	अचिन्हित पूर्णांक		re_send_count;
	अचिन्हित पूर्णांक		re_send_batch;
	अचिन्हित पूर्णांक		re_max_अंतरभूत_send;
	अचिन्हित पूर्णांक		re_max_अंतरभूत_recv;
	पूर्णांक			re_async_rc;
	पूर्णांक			re_connect_status;
	atomic_t		re_receiving;
	atomic_t		re_क्रमce_disconnect;
	काष्ठा ib_qp_init_attr	re_attr;
	रुको_queue_head_t       re_connect_रुको;
	काष्ठा rpc_xprt		*re_xprt;
	काष्ठा rpcrdma_connect_निजी
				re_cm_निजी;
	काष्ठा rdma_conn_param	re_remote_cma;
	पूर्णांक			re_receive_count;
	अचिन्हित पूर्णांक		re_max_requests; /* depends on device */
	अचिन्हित पूर्णांक		re_अंतरभूत_send;	/* negotiated */
	अचिन्हित पूर्णांक		re_अंतरभूत_recv;	/* negotiated */

	atomic_t		re_completion_ids;
पूर्ण;

/* Pre-allocate extra Work Requests क्रम handling reverse-direction
 * Receives and Sends. This is a fixed value because the Work Queues
 * are allocated when the क्रमward channel is set up, दीर्घ beक्रमe the
 * backchannel is provisioned. This value is two बार
 * NFS4_DEF_CB_SLOT_TABLE_SIZE.
 */
#अगर defined(CONFIG_SUNRPC_BACKCHANNEL)
#घोषणा RPCRDMA_BACKWARD_WRS (32)
#अन्यथा
#घोषणा RPCRDMA_BACKWARD_WRS (0)
#पूर्ण_अगर

/* Registered buffer -- रेजिस्टरed kदो_स्मृति'd memory क्रम RDMA SEND/RECV
 */

काष्ठा rpcrdma_regbuf अणु
	काष्ठा ib_sge		rg_iov;
	काष्ठा ib_device	*rg_device;
	क्रमागत dma_data_direction	rg_direction;
	व्योम			*rg_data;
पूर्ण;

अटल अंतरभूत u64 rdmab_addr(काष्ठा rpcrdma_regbuf *rb)
अणु
	वापस rb->rg_iov.addr;
पूर्ण

अटल अंतरभूत u32 rdmab_length(काष्ठा rpcrdma_regbuf *rb)
अणु
	वापस rb->rg_iov.length;
पूर्ण

अटल अंतरभूत u32 rdmab_lkey(काष्ठा rpcrdma_regbuf *rb)
अणु
	वापस rb->rg_iov.lkey;
पूर्ण

अटल अंतरभूत काष्ठा ib_device *rdmab_device(काष्ठा rpcrdma_regbuf *rb)
अणु
	वापस rb->rg_device;
पूर्ण

अटल अंतरभूत व्योम *rdmab_data(स्थिर काष्ठा rpcrdma_regbuf *rb)
अणु
	वापस rb->rg_data;
पूर्ण

#घोषणा RPCRDMA_DEF_GFP		(GFP_NOIO | __GFP_NOWARN)

/* To ensure a transport can always make क्रमward progress,
 * the number of RDMA segments allowed in header chunk lists
 * is capped at 16. This prevents less-capable devices from
 * overrunning the Send buffer जबतक building chunk lists.
 *
 * Elements of the Read list take up more room than the
 * Write list or Reply chunk. 16 पढ़ो segments means the
 * chunk lists cannot consume more than
 *
 * ((16 + 2) * पढ़ो segment size) + 1 XDR words,
 *
 * or about 400 bytes. The fixed part of the header is
 * another 24 bytes. Thus when the अंतरभूत threshold is
 * 1024 bytes, at least 600 bytes are available क्रम RPC
 * message bodies.
 */
क्रमागत अणु
	RPCRDMA_MAX_HDR_SEGS = 16,
पूर्ण;

/*
 * काष्ठा rpcrdma_rep -- this काष्ठाure encapsulates state required
 * to receive and complete an RPC Reply, asychronously. It needs
 * several pieces of state:
 *
 *   o receive buffer and ib_sge (करोnated to provider)
 *   o status of receive (success or not, length, inv rkey)
 *   o bookkeeping state to get run by reply handler (XDR stream)
 *
 * These काष्ठाures are allocated during transport initialization.
 * N of these are associated with a transport instance, managed by
 * काष्ठा rpcrdma_buffer. N is the max number of outstanding RPCs.
 */

काष्ठा rpcrdma_rep अणु
	काष्ठा ib_cqe		rr_cqe;
	काष्ठा rpc_rdma_cid	rr_cid;

	__be32			rr_xid;
	__be32			rr_vers;
	__be32			rr_proc;
	पूर्णांक			rr_wc_flags;
	u32			rr_inv_rkey;
	bool			rr_temp;
	काष्ठा rpcrdma_regbuf	*rr_rdmabuf;
	काष्ठा rpcrdma_xprt	*rr_rxprt;
	काष्ठा rpc_rqst		*rr_rqst;
	काष्ठा xdr_buf		rr_hdrbuf;
	काष्ठा xdr_stream	rr_stream;
	काष्ठा llist_node	rr_node;
	काष्ठा ib_recv_wr	rr_recv_wr;
	काष्ठा list_head	rr_all;
पूर्ण;

/* To reduce the rate at which a transport invokes ib_post_recv
 * (and thus the hardware करोorbell rate), xprtrdma posts Receive
 * WRs in batches.
 *
 * Setting this to zero disables Receive post batching.
 */
क्रमागत अणु
	RPCRDMA_MAX_RECV_BATCH = 7,
पूर्ण;

/* काष्ठा rpcrdma_sendctx - DMA mapped SGEs to unmap after Send completes
 */
काष्ठा rpcrdma_req;
काष्ठा rpcrdma_sendctx अणु
	काष्ठा ib_cqe		sc_cqe;
	काष्ठा rpc_rdma_cid	sc_cid;
	काष्ठा rpcrdma_req	*sc_req;
	अचिन्हित पूर्णांक		sc_unmap_count;
	काष्ठा ib_sge		sc_sges[];
पूर्ण;

/*
 * काष्ठा rpcrdma_mr - बाह्यal memory region metadata
 *
 * An बाह्यal memory region is any buffer or page that is रेजिस्टरed
 * on the fly (ie, not pre-रेजिस्टरed).
 */
काष्ठा rpcrdma_req;
काष्ठा rpcrdma_mr अणु
	काष्ठा list_head	mr_list;
	काष्ठा rpcrdma_req	*mr_req;

	काष्ठा ib_mr		*mr_ibmr;
	काष्ठा ib_device	*mr_device;
	काष्ठा scatterlist	*mr_sg;
	पूर्णांक			mr_nents;
	क्रमागत dma_data_direction	mr_dir;
	काष्ठा ib_cqe		mr_cqe;
	काष्ठा completion	mr_linv_करोne;
	जोड़ अणु
		काष्ठा ib_reg_wr	mr_regwr;
		काष्ठा ib_send_wr	mr_invwr;
	पूर्ण;
	काष्ठा rpcrdma_xprt	*mr_xprt;
	u32			mr_handle;
	u32			mr_length;
	u64			mr_offset;
	काष्ठा list_head	mr_all;
	काष्ठा rpc_rdma_cid	mr_cid;
पूर्ण;

/*
 * काष्ठा rpcrdma_req -- काष्ठाure central to the request/reply sequence.
 *
 * N of these are associated with a transport instance, and stored in
 * काष्ठा rpcrdma_buffer. N is the max number of outstanding requests.
 *
 * It includes pre-रेजिस्टरed buffer memory क्रम send AND recv.
 * The recv buffer, however, is not owned by this काष्ठाure, and
 * is "donated" to the hardware when a recv is posted. When a
 * reply is handled, the recv buffer used is given back to the
 * काष्ठा rpcrdma_req associated with the request.
 *
 * In addition to the basic memory, this काष्ठाure includes an array
 * of iovs क्रम send operations. The reason is that the iovs passed to
 * ib_post_अणुsend,recvपूर्ण must not be modअगरied until the work request
 * completes.
 */

/* Maximum number of page-sized "segments" per chunk list to be
 * रेजिस्टरed or invalidated. Must handle a Reply chunk:
 */
क्रमागत अणु
	RPCRDMA_MAX_IOV_SEGS	= 3,
	RPCRDMA_MAX_DATA_SEGS	= ((1 * 1024 * 1024) / PAGE_SIZE) + 1,
	RPCRDMA_MAX_SEGS	= RPCRDMA_MAX_DATA_SEGS +
				  RPCRDMA_MAX_IOV_SEGS,
पूर्ण;

/* Arguments क्रम DMA mapping and registration */
काष्ठा rpcrdma_mr_seg अणु
	u32		mr_len;		/* length of segment */
	काष्ठा page	*mr_page;	/* underlying काष्ठा page */
	u64		mr_offset;	/* IN: page offset, OUT: iova */
पूर्ण;

/* The Send SGE array is provisioned to send a maximum size
 * अंतरभूत request:
 * - RPC-over-RDMA header
 * - xdr_buf head iovec
 * - RPCRDMA_MAX_INLINE bytes, in pages
 * - xdr_buf tail iovec
 *
 * The actual number of array elements consumed by each RPC
 * depends on the device's max_sge limit.
 */
क्रमागत अणु
	RPCRDMA_MIN_SEND_SGES = 3,
	RPCRDMA_MAX_PAGE_SGES = RPCRDMA_MAX_INLINE >> PAGE_SHIFT,
	RPCRDMA_MAX_SEND_SGES = 1 + 1 + RPCRDMA_MAX_PAGE_SGES + 1,
पूर्ण;

काष्ठा rpcrdma_buffer;
काष्ठा rpcrdma_req अणु
	काष्ठा list_head	rl_list;
	काष्ठा rpc_rqst		rl_slot;
	काष्ठा rpcrdma_rep	*rl_reply;
	काष्ठा xdr_stream	rl_stream;
	काष्ठा xdr_buf		rl_hdrbuf;
	काष्ठा ib_send_wr	rl_wr;
	काष्ठा rpcrdma_sendctx	*rl_sendctx;
	काष्ठा rpcrdma_regbuf	*rl_rdmabuf;	/* xprt header */
	काष्ठा rpcrdma_regbuf	*rl_sendbuf;	/* rq_snd_buf */
	काष्ठा rpcrdma_regbuf	*rl_recvbuf;	/* rq_rcv_buf */

	काष्ठा list_head	rl_all;
	काष्ठा kref		rl_kref;

	काष्ठा list_head	rl_मुक्त_mrs;
	काष्ठा list_head	rl_रेजिस्टरed;
	काष्ठा rpcrdma_mr_seg	rl_segments[RPCRDMA_MAX_SEGS];
पूर्ण;

अटल अंतरभूत काष्ठा rpcrdma_req *
rpcr_to_rdmar(स्थिर काष्ठा rpc_rqst *rqst)
अणु
	वापस container_of(rqst, काष्ठा rpcrdma_req, rl_slot);
पूर्ण

अटल अंतरभूत व्योम
rpcrdma_mr_push(काष्ठा rpcrdma_mr *mr, काष्ठा list_head *list)
अणु
	list_add(&mr->mr_list, list);
पूर्ण

अटल अंतरभूत काष्ठा rpcrdma_mr *
rpcrdma_mr_pop(काष्ठा list_head *list)
अणु
	काष्ठा rpcrdma_mr *mr;

	mr = list_first_entry_or_null(list, काष्ठा rpcrdma_mr, mr_list);
	अगर (mr)
		list_del_init(&mr->mr_list);
	वापस mr;
पूर्ण

/*
 * काष्ठा rpcrdma_buffer -- holds list/queue of pre-रेजिस्टरed memory क्रम
 * अंतरभूत requests/replies, and client/server credits.
 *
 * One of these is associated with a transport instance
 */
काष्ठा rpcrdma_buffer अणु
	spinlock_t		rb_lock;
	काष्ठा list_head	rb_send_bufs;
	काष्ठा list_head	rb_mrs;

	अचिन्हित दीर्घ		rb_sc_head;
	अचिन्हित दीर्घ		rb_sc_tail;
	अचिन्हित दीर्घ		rb_sc_last;
	काष्ठा rpcrdma_sendctx	**rb_sc_ctxs;

	काष्ठा list_head	rb_allreqs;
	काष्ठा list_head	rb_all_mrs;
	काष्ठा list_head	rb_all_reps;

	काष्ठा llist_head	rb_मुक्त_reps;

	__be32			rb_max_requests;
	u32			rb_credits;	/* most recent credit grant */

	u32			rb_bc_srv_max_requests;
	u32			rb_bc_max_requests;

	काष्ठा work_काष्ठा	rb_refresh_worker;
पूर्ण;

/*
 * Statistics क्रम RPCRDMA
 */
काष्ठा rpcrdma_stats अणु
	/* accessed when sending a call */
	अचिन्हित दीर्घ		पढ़ो_chunk_count;
	अचिन्हित दीर्घ		ग_लिखो_chunk_count;
	अचिन्हित दीर्घ		reply_chunk_count;
	अचिन्हित दीर्घ दीर्घ	total_rdma_request;

	/* rarely accessed error counters */
	अचिन्हित दीर्घ दीर्घ	pullup_copy_count;
	अचिन्हित दीर्घ		hardway_रेजिस्टर_count;
	अचिन्हित दीर्घ		failed_marshal_count;
	अचिन्हित दीर्घ		bad_reply_count;
	अचिन्हित दीर्घ		mrs_recycled;
	अचिन्हित दीर्घ		mrs_orphaned;
	अचिन्हित दीर्घ		mrs_allocated;
	अचिन्हित दीर्घ		empty_sendctx_q;

	/* accessed when receiving a reply */
	अचिन्हित दीर्घ दीर्घ	total_rdma_reply;
	अचिन्हित दीर्घ दीर्घ	fixup_copy_count;
	अचिन्हित दीर्घ		reply_रुकोs_क्रम_send;
	अचिन्हित दीर्घ		local_inv_needed;
	अचिन्हित दीर्घ		nomsg_call_count;
	अचिन्हित दीर्घ		bcall_count;
पूर्ण;

/*
 * RPCRDMA transport -- encapsulates the काष्ठाures above क्रम
 * पूर्णांकegration with RPC.
 *
 * The contained काष्ठाures are embedded, not poपूर्णांकers,
 * क्रम convenience. This काष्ठाure need not be visible बाह्यally.
 *
 * It is allocated and initialized during mount, and released
 * during unmount.
 */
काष्ठा rpcrdma_xprt अणु
	काष्ठा rpc_xprt		rx_xprt;
	काष्ठा rpcrdma_ep	*rx_ep;
	काष्ठा rpcrdma_buffer	rx_buf;
	काष्ठा delayed_work	rx_connect_worker;
	काष्ठा rpc_समयout	rx_समयout;
	काष्ठा rpcrdma_stats	rx_stats;
पूर्ण;

#घोषणा rpcx_to_rdmax(x) container_of(x, काष्ठा rpcrdma_xprt, rx_xprt)

अटल अंतरभूत स्थिर अक्षर *
rpcrdma_addrstr(स्थिर काष्ठा rpcrdma_xprt *r_xprt)
अणु
	वापस r_xprt->rx_xprt.address_strings[RPC_DISPLAY_ADDR];
पूर्ण

अटल अंतरभूत स्थिर अक्षर *
rpcrdma_portstr(स्थिर काष्ठा rpcrdma_xprt *r_xprt)
अणु
	वापस r_xprt->rx_xprt.address_strings[RPC_DISPLAY_PORT];
पूर्ण

/* Setting this to 0 ensures पूर्णांकeroperability with early servers.
 * Setting this to 1 enhances certain unaligned पढ़ो/ग_लिखो perक्रमmance.
 * Default is 0, see sysctl entry and rpc_rdma.c rpcrdma_convert_iovs() */
बाह्य पूर्णांक xprt_rdma_pad_optimize;

/* This setting controls the hunt क्रम a supported memory
 * registration strategy.
 */
बाह्य अचिन्हित पूर्णांक xprt_rdma_memreg_strategy;

/*
 * Endpoपूर्णांक calls - xprtrdma/verbs.c
 */
व्योम rpcrdma_flush_disconnect(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा ib_wc *wc);
पूर्णांक rpcrdma_xprt_connect(काष्ठा rpcrdma_xprt *r_xprt);
व्योम rpcrdma_xprt_disconnect(काष्ठा rpcrdma_xprt *r_xprt);

पूर्णांक rpcrdma_post_sends(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा rpcrdma_req *req);
व्योम rpcrdma_post_recvs(काष्ठा rpcrdma_xprt *r_xprt, पूर्णांक needed, bool temp);

/*
 * Buffer calls - xprtrdma/verbs.c
 */
काष्ठा rpcrdma_req *rpcrdma_req_create(काष्ठा rpcrdma_xprt *r_xprt, माप_प्रकार size,
				       gfp_t flags);
पूर्णांक rpcrdma_req_setup(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा rpcrdma_req *req);
व्योम rpcrdma_req_destroy(काष्ठा rpcrdma_req *req);
पूर्णांक rpcrdma_buffer_create(काष्ठा rpcrdma_xprt *);
व्योम rpcrdma_buffer_destroy(काष्ठा rpcrdma_buffer *);
काष्ठा rpcrdma_sendctx *rpcrdma_sendctx_get_locked(काष्ठा rpcrdma_xprt *r_xprt);

काष्ठा rpcrdma_mr *rpcrdma_mr_get(काष्ठा rpcrdma_xprt *r_xprt);
व्योम rpcrdma_mrs_refresh(काष्ठा rpcrdma_xprt *r_xprt);

काष्ठा rpcrdma_req *rpcrdma_buffer_get(काष्ठा rpcrdma_buffer *);
व्योम rpcrdma_buffer_put(काष्ठा rpcrdma_buffer *buffers,
			काष्ठा rpcrdma_req *req);
व्योम rpcrdma_rep_put(काष्ठा rpcrdma_buffer *buf, काष्ठा rpcrdma_rep *rep);
व्योम rpcrdma_reply_put(काष्ठा rpcrdma_buffer *buffers, काष्ठा rpcrdma_req *req);

bool rpcrdma_regbuf_पुनः_स्मृति(काष्ठा rpcrdma_regbuf *rb, माप_प्रकार size,
			    gfp_t flags);
bool __rpcrdma_regbuf_dma_map(काष्ठा rpcrdma_xprt *r_xprt,
			      काष्ठा rpcrdma_regbuf *rb);

/**
 * rpcrdma_regbuf_is_mapped - check अगर buffer is DMA mapped
 *
 * Returns true अगर the buffer is now mapped to rb->rg_device.
 */
अटल अंतरभूत bool rpcrdma_regbuf_is_mapped(काष्ठा rpcrdma_regbuf *rb)
अणु
	वापस rb->rg_device != शून्य;
पूर्ण

/**
 * rpcrdma_regbuf_dma_map - DMA-map a regbuf
 * @r_xprt: controlling transport instance
 * @rb: regbuf to be mapped
 *
 * Returns true अगर the buffer is currently DMA mapped.
 */
अटल अंतरभूत bool rpcrdma_regbuf_dma_map(काष्ठा rpcrdma_xprt *r_xprt,
					  काष्ठा rpcrdma_regbuf *rb)
अणु
	अगर (likely(rpcrdma_regbuf_is_mapped(rb)))
		वापस true;
	वापस __rpcrdma_regbuf_dma_map(r_xprt, rb);
पूर्ण

/*
 * Wrappers क्रम chunk registration, shared by पढ़ो/ग_लिखो chunk code.
 */

अटल अंतरभूत क्रमागत dma_data_direction
rpcrdma_data_dir(bool writing)
अणु
	वापस writing ? DMA_FROM_DEVICE : DMA_TO_DEVICE;
पूर्ण

/* Memory registration calls xprtrdma/frwr_ops.c
 */
व्योम frwr_reset(काष्ठा rpcrdma_req *req);
पूर्णांक frwr_query_device(काष्ठा rpcrdma_ep *ep, स्थिर काष्ठा ib_device *device);
पूर्णांक frwr_mr_init(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा rpcrdma_mr *mr);
व्योम frwr_mr_release(काष्ठा rpcrdma_mr *mr);
काष्ठा rpcrdma_mr_seg *frwr_map(काष्ठा rpcrdma_xprt *r_xprt,
				काष्ठा rpcrdma_mr_seg *seg,
				पूर्णांक nsegs, bool writing, __be32 xid,
				काष्ठा rpcrdma_mr *mr);
पूर्णांक frwr_send(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा rpcrdma_req *req);
व्योम frwr_reminv(काष्ठा rpcrdma_rep *rep, काष्ठा list_head *mrs);
व्योम frwr_unmap_sync(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा rpcrdma_req *req);
व्योम frwr_unmap_async(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा rpcrdma_req *req);

/*
 * RPC/RDMA protocol calls - xprtrdma/rpc_rdma.c
 */

क्रमागत rpcrdma_chunktype अणु
	rpcrdma_noch = 0,
	rpcrdma_noch_pullup,
	rpcrdma_noch_mapped,
	rpcrdma_पढ़ोch,
	rpcrdma_aपढ़ोch,
	rpcrdma_ग_लिखोch,
	rpcrdma_replych
पूर्ण;

पूर्णांक rpcrdma_prepare_send_sges(काष्ठा rpcrdma_xprt *r_xprt,
			      काष्ठा rpcrdma_req *req, u32 hdrlen,
			      काष्ठा xdr_buf *xdr,
			      क्रमागत rpcrdma_chunktype rtype);
व्योम rpcrdma_sendctx_unmap(काष्ठा rpcrdma_sendctx *sc);
पूर्णांक rpcrdma_marshal_req(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा rpc_rqst *rqst);
व्योम rpcrdma_set_max_header_sizes(काष्ठा rpcrdma_ep *ep);
व्योम rpcrdma_reset_cwnd(काष्ठा rpcrdma_xprt *r_xprt);
व्योम rpcrdma_complete_rqst(काष्ठा rpcrdma_rep *rep);
व्योम rpcrdma_unpin_rqst(काष्ठा rpcrdma_rep *rep);
व्योम rpcrdma_reply_handler(काष्ठा rpcrdma_rep *rep);

अटल अंतरभूत व्योम rpcrdma_set_xdrlen(काष्ठा xdr_buf *xdr, माप_प्रकार len)
अणु
	xdr->head[0].iov_len = len;
	xdr->len = len;
पूर्ण

/* RPC/RDMA module init - xprtrdma/transport.c
 */
बाह्य अचिन्हित पूर्णांक xprt_rdma_max_अंतरभूत_पढ़ो;
बाह्य अचिन्हित पूर्णांक xprt_rdma_max_अंतरभूत_ग_लिखो;
व्योम xprt_rdma_क्रमmat_addresses(काष्ठा rpc_xprt *xprt, काष्ठा sockaddr *sap);
व्योम xprt_rdma_मुक्त_addresses(काष्ठा rpc_xprt *xprt);
व्योम xprt_rdma_बंद(काष्ठा rpc_xprt *xprt);
व्योम xprt_rdma_prपूर्णांक_stats(काष्ठा rpc_xprt *xprt, काष्ठा seq_file *seq);
पूर्णांक xprt_rdma_init(व्योम);
व्योम xprt_rdma_cleanup(व्योम);

/* Backchannel calls - xprtrdma/backchannel.c
 */
#अगर defined(CONFIG_SUNRPC_BACKCHANNEL)
पूर्णांक xprt_rdma_bc_setup(काष्ठा rpc_xprt *, अचिन्हित पूर्णांक);
माप_प्रकार xprt_rdma_bc_maxpayload(काष्ठा rpc_xprt *);
अचिन्हित पूर्णांक xprt_rdma_bc_max_slots(काष्ठा rpc_xprt *);
पूर्णांक rpcrdma_bc_post_recv(काष्ठा rpcrdma_xprt *, अचिन्हित पूर्णांक);
व्योम rpcrdma_bc_receive_call(काष्ठा rpcrdma_xprt *, काष्ठा rpcrdma_rep *);
पूर्णांक xprt_rdma_bc_send_reply(काष्ठा rpc_rqst *rqst);
व्योम xprt_rdma_bc_मुक्त_rqst(काष्ठा rpc_rqst *);
व्योम xprt_rdma_bc_destroy(काष्ठा rpc_xprt *, अचिन्हित पूर्णांक);
#पूर्ण_अगर	/* CONFIG_SUNRPC_BACKCHANNEL */

बाह्य काष्ठा xprt_class xprt_rdma_bc;

#पूर्ण_अगर				/* _LINUX_SUNRPC_XPRT_RDMA_H */
