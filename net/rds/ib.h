<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _RDS_IB_H
#घोषणा _RDS_IB_H

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/rdma_cm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश "rds.h"
#समावेश "rdma_transport.h"

#घोषणा RDS_IB_MAX_SGE			8
#घोषणा RDS_IB_RECV_SGE 		2

#घोषणा RDS_IB_DEFAULT_RECV_WR		1024
#घोषणा RDS_IB_DEFAULT_SEND_WR		256
#घोषणा RDS_IB_DEFAULT_FR_WR		512

#घोषणा RDS_IB_DEFAULT_RETRY_COUNT	1

#घोषणा RDS_IB_SUPPORTED_PROTOCOLS	0x00000003	/* minor versions supported */

#घोषणा RDS_IB_RECYCLE_BATCH_COUNT	32

#घोषणा RDS_IB_WC_MAX			32

बाह्य काष्ठा rw_semaphore rds_ib_devices_lock;
बाह्य काष्ठा list_head rds_ib_devices;

/*
 * IB posts RDS_FRAG_SIZE fragments of pages to the receive queues to
 * try and minimize the amount of memory tied up both the device and
 * socket receive queues.
 */
काष्ठा rds_page_frag अणु
	काष्ठा list_head	f_item;
	काष्ठा list_head	f_cache_entry;
	काष्ठा scatterlist	f_sg;
पूर्ण;

काष्ठा rds_ib_incoming अणु
	काष्ठा list_head	ii_frags;
	काष्ठा list_head	ii_cache_entry;
	काष्ठा rds_incoming	ii_inc;
पूर्ण;

काष्ठा rds_ib_cache_head अणु
	काष्ठा list_head *first;
	अचिन्हित दीर्घ count;
पूर्ण;

काष्ठा rds_ib_refill_cache अणु
	काष्ठा rds_ib_cache_head __percpu *percpu;
	काष्ठा list_head	 *xfer;
	काष्ठा list_head	 *पढ़ोy;
पूर्ण;

/* This is the common काष्ठाure क्रम the IB निजी data exchange in setting up
 * an RDS connection.  The exchange is dअगरferent क्रम IPv4 and IPv6 connections.
 * The reason is that the address size is dअगरferent and the addresses
 * exchanged are in the beginning of the काष्ठाure.  Hence it is not possible
 * क्रम पूर्णांकeroperability अगर same काष्ठाure is used.
 */
काष्ठा rds_ib_conn_priv_cmn अणु
	u8			ricpc_protocol_major;
	u8			ricpc_protocol_minor;
	__be16			ricpc_protocol_minor_mask;	/* biपंचांगask */
	u8			ricpc_dp_toss;
	u8			ripc_reserved1;
	__be16			ripc_reserved2;
	__be64			ricpc_ack_seq;
	__be32			ricpc_credit;	/* non-zero enables flow ctl */
पूर्ण;

काष्ठा rds_ib_connect_निजी अणु
	/* Add new fields at the end, and करोn't permute existing fields. */
	__be32				dp_saddr;
	__be32				dp_daddr;
	काष्ठा rds_ib_conn_priv_cmn	dp_cmn;
पूर्ण;

काष्ठा rds6_ib_connect_निजी अणु
	/* Add new fields at the end, and करोn't permute existing fields. */
	काष्ठा in6_addr			dp_saddr;
	काष्ठा in6_addr			dp_daddr;
	काष्ठा rds_ib_conn_priv_cmn	dp_cmn;
पूर्ण;

#घोषणा dp_protocol_major	dp_cmn.ricpc_protocol_major
#घोषणा dp_protocol_minor	dp_cmn.ricpc_protocol_minor
#घोषणा dp_protocol_minor_mask	dp_cmn.ricpc_protocol_minor_mask
#घोषणा dp_ack_seq		dp_cmn.ricpc_ack_seq
#घोषणा dp_credit		dp_cmn.ricpc_credit

जोड़ rds_ib_conn_priv अणु
	काष्ठा rds_ib_connect_निजी	ricp_v4;
	काष्ठा rds6_ib_connect_निजी	ricp_v6;
पूर्ण;

काष्ठा rds_ib_send_work अणु
	व्योम			*s_op;
	जोड़ अणु
		काष्ठा ib_send_wr	s_wr;
		काष्ठा ib_rdma_wr	s_rdma_wr;
		काष्ठा ib_atomic_wr	s_atomic_wr;
	पूर्ण;
	काष्ठा ib_sge		s_sge[RDS_IB_MAX_SGE];
	अचिन्हित दीर्घ		s_queued;
पूर्ण;

काष्ठा rds_ib_recv_work अणु
	काष्ठा rds_ib_incoming 	*r_ibinc;
	काष्ठा rds_page_frag	*r_frag;
	काष्ठा ib_recv_wr	r_wr;
	काष्ठा ib_sge		r_sge[2];
पूर्ण;

काष्ठा rds_ib_work_ring अणु
	u32		w_nr;
	u32		w_alloc_ptr;
	u32		w_alloc_ctr;
	u32		w_मुक्त_ptr;
	atomic_t	w_मुक्त_ctr;
पूर्ण;

/* Rings are posted with all the allocations they'll need to queue the
 * incoming message to the receiving socket so this can't fail.
 * All fragments start with a header, so we can make sure we're not receiving
 * garbage, and we can tell a small 8 byte fragment from an ACK frame.
 */
काष्ठा rds_ib_ack_state अणु
	u64		ack_next;
	u64		ack_recv;
	अचिन्हित पूर्णांक	ack_required:1;
	अचिन्हित पूर्णांक	ack_next_valid:1;
	अचिन्हित पूर्णांक	ack_recv_valid:1;
पूर्ण;


काष्ठा rds_ib_device;

काष्ठा rds_ib_connection अणु

	काष्ठा list_head	ib_node;
	काष्ठा rds_ib_device	*rds_ibdev;
	काष्ठा rds_connection	*conn;

	/* alphabet soup, IBTA style */
	काष्ठा rdma_cm_id	*i_cm_id;
	काष्ठा ib_pd		*i_pd;
	काष्ठा ib_cq		*i_send_cq;
	काष्ठा ib_cq		*i_recv_cq;
	काष्ठा ib_wc		i_send_wc[RDS_IB_WC_MAX];
	काष्ठा ib_wc		i_recv_wc[RDS_IB_WC_MAX];

	/* To control the number of wrs from fastreg */
	atomic_t		i_fastreg_wrs;
	atomic_t		i_fastreg_inuse_count;

	/* पूर्णांकerrupt handling */
	काष्ठा tasklet_काष्ठा	i_send_tasklet;
	काष्ठा tasklet_काष्ठा	i_recv_tasklet;

	/* tx */
	काष्ठा rds_ib_work_ring	i_send_ring;
	काष्ठा rm_data_op	*i_data_op;
	काष्ठा rds_header	**i_send_hdrs;
	dma_addr_t		*i_send_hdrs_dma;
	काष्ठा rds_ib_send_work *i_sends;
	atomic_t		i_संकेतed_sends;

	/* rx */
	काष्ठा mutex		i_recv_mutex;
	काष्ठा rds_ib_work_ring	i_recv_ring;
	काष्ठा rds_ib_incoming	*i_ibinc;
	u32			i_recv_data_rem;
	काष्ठा rds_header	**i_recv_hdrs;
	dma_addr_t		*i_recv_hdrs_dma;
	काष्ठा rds_ib_recv_work *i_recvs;
	u64			i_ack_recv;	/* last ACK received */
	काष्ठा rds_ib_refill_cache i_cache_incs;
	काष्ठा rds_ib_refill_cache i_cache_frags;
	atomic_t		i_cache_allocs;

	/* sending acks */
	अचिन्हित दीर्घ		i_ack_flags;
#अगर_घोषित KERNEL_HAS_ATOMIC64
	atomic64_t		i_ack_next;	/* next ACK to send */
#अन्यथा
	spinlock_t		i_ack_lock;	/* protect i_ack_next */
	u64			i_ack_next;	/* next ACK to send */
#पूर्ण_अगर
	काष्ठा rds_header	*i_ack;
	काष्ठा ib_send_wr	i_ack_wr;
	काष्ठा ib_sge		i_ack_sge;
	dma_addr_t		i_ack_dma;
	अचिन्हित दीर्घ		i_ack_queued;

	/* Flow control related inक्रमmation
	 *
	 * Our algorithm uses a pair variables that we need to access
	 * atomically - one क्रम the send credits, and one posted
	 * recv credits we need to transfer to remote.
	 * Rather than protect them using a slow spinlock, we put both पूर्णांकo
	 * a single atomic_t and update it using cmpxchg
	 */
	atomic_t		i_credits;

	/* Protocol version specअगरic inक्रमmation */
	अचिन्हित पूर्णांक		i_flowctl:1;	/* enable/disable flow ctl */

	/* Batched completions */
	अचिन्हित पूर्णांक		i_unसंकेतed_wrs;

	/* Endpoपूर्णांक role in connection */
	bool			i_active_side;
	atomic_t		i_cq_quiesce;

	/* Send/Recv vectors */
	पूर्णांक			i_scq_vector;
	पूर्णांक			i_rcq_vector;
	u8			i_sl;
पूर्ण;

/* This assumes that atomic_t is at least 32 bits */
#घोषणा IB_GET_SEND_CREDITS(v)	((v) & 0xffff)
#घोषणा IB_GET_POST_CREDITS(v)	((v) >> 16)
#घोषणा IB_SET_SEND_CREDITS(v)	((v) & 0xffff)
#घोषणा IB_SET_POST_CREDITS(v)	((v) << 16)

काष्ठा rds_ib_ipaddr अणु
	काष्ठा list_head	list;
	__be32			ipaddr;
	काष्ठा rcu_head		rcu;
पूर्ण;

क्रमागत अणु
	RDS_IB_MR_8K_POOL,
	RDS_IB_MR_1M_POOL,
पूर्ण;

काष्ठा rds_ib_device अणु
	काष्ठा list_head	list;
	काष्ठा list_head	ipaddr_list;
	काष्ठा list_head	conn_list;
	काष्ठा ib_device	*dev;
	काष्ठा ib_pd		*pd;
	u8			odp_capable:1;

	अचिन्हित पूर्णांक		max_mrs;
	काष्ठा rds_ib_mr_pool	*mr_1m_pool;
	काष्ठा rds_ib_mr_pool   *mr_8k_pool;
	अचिन्हित पूर्णांक		max_8k_mrs;
	अचिन्हित पूर्णांक		max_1m_mrs;
	पूर्णांक			max_sge;
	अचिन्हित पूर्णांक		max_wrs;
	अचिन्हित पूर्णांक		max_initiator_depth;
	अचिन्हित पूर्णांक		max_responder_resources;
	spinlock_t		spinlock;	/* protect the above */
	refcount_t		refcount;
	काष्ठा work_काष्ठा	मुक्त_work;
	पूर्णांक			*vector_load;
पूर्ण;

#घोषणा rdsibdev_to_node(rdsibdev) ibdev_to_node(rdsibdev->dev)

/* bits क्रम i_ack_flags */
#घोषणा IB_ACK_IN_FLIGHT	0
#घोषणा IB_ACK_REQUESTED	1

/* Magic WR_ID क्रम ACKs */
#घोषणा RDS_IB_ACK_WR_ID	(~(u64) 0)

काष्ठा rds_ib_statistics अणु
	uपूर्णांक64_t	s_ib_connect_raced;
	uपूर्णांक64_t	s_ib_listen_बंदd_stale;
	uपूर्णांक64_t	s_ib_evt_handler_call;
	uपूर्णांक64_t	s_ib_tasklet_call;
	uपूर्णांक64_t	s_ib_tx_cq_event;
	uपूर्णांक64_t	s_ib_tx_ring_full;
	uपूर्णांक64_t	s_ib_tx_throttle;
	uपूर्णांक64_t	s_ib_tx_sg_mapping_failure;
	uपूर्णांक64_t	s_ib_tx_stalled;
	uपूर्णांक64_t	s_ib_tx_credit_updates;
	uपूर्णांक64_t	s_ib_rx_cq_event;
	uपूर्णांक64_t	s_ib_rx_ring_empty;
	uपूर्णांक64_t	s_ib_rx_refill_from_cq;
	uपूर्णांक64_t	s_ib_rx_refill_from_thपढ़ो;
	uपूर्णांक64_t	s_ib_rx_alloc_limit;
	uपूर्णांक64_t	s_ib_rx_total_frags;
	uपूर्णांक64_t	s_ib_rx_total_incs;
	uपूर्णांक64_t	s_ib_rx_credit_updates;
	uपूर्णांक64_t	s_ib_ack_sent;
	uपूर्णांक64_t	s_ib_ack_send_failure;
	uपूर्णांक64_t	s_ib_ack_send_delayed;
	uपूर्णांक64_t	s_ib_ack_send_piggybacked;
	uपूर्णांक64_t	s_ib_ack_received;
	uपूर्णांक64_t	s_ib_rdma_mr_8k_alloc;
	uपूर्णांक64_t	s_ib_rdma_mr_8k_मुक्त;
	uपूर्णांक64_t	s_ib_rdma_mr_8k_used;
	uपूर्णांक64_t	s_ib_rdma_mr_8k_pool_flush;
	uपूर्णांक64_t	s_ib_rdma_mr_8k_pool_रुको;
	uपूर्णांक64_t	s_ib_rdma_mr_8k_pool_depleted;
	uपूर्णांक64_t	s_ib_rdma_mr_1m_alloc;
	uपूर्णांक64_t	s_ib_rdma_mr_1m_मुक्त;
	uपूर्णांक64_t	s_ib_rdma_mr_1m_used;
	uपूर्णांक64_t	s_ib_rdma_mr_1m_pool_flush;
	uपूर्णांक64_t	s_ib_rdma_mr_1m_pool_रुको;
	uपूर्णांक64_t	s_ib_rdma_mr_1m_pool_depleted;
	uपूर्णांक64_t	s_ib_rdma_mr_8k_reused;
	uपूर्णांक64_t	s_ib_rdma_mr_1m_reused;
	uपूर्णांक64_t	s_ib_atomic_cswp;
	uपूर्णांक64_t	s_ib_atomic_fadd;
	uपूर्णांक64_t	s_ib_recv_added_to_cache;
	uपूर्णांक64_t	s_ib_recv_हटाओd_from_cache;
पूर्ण;

बाह्य काष्ठा workqueue_काष्ठा *rds_ib_wq;

/*
 * Fake ib_dma_sync_sg_क्रम_अणुcpu,deviceपूर्ण as दीर्घ as ib_verbs.h
 * करोesn't define it.
 */
अटल अंतरभूत व्योम rds_ib_dma_sync_sg_क्रम_cpu(काष्ठा ib_device *dev,
					      काष्ठा scatterlist *sglist,
					      अचिन्हित पूर्णांक sg_dma_len,
					      पूर्णांक direction)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i;

	क्रम_each_sg(sglist, sg, sg_dma_len, i) अणु
		ib_dma_sync_single_क्रम_cpu(dev, sg_dma_address(sg),
					   sg_dma_len(sg), direction);
	पूर्ण
पूर्ण
#घोषणा ib_dma_sync_sg_क्रम_cpu	rds_ib_dma_sync_sg_क्रम_cpu

अटल अंतरभूत व्योम rds_ib_dma_sync_sg_क्रम_device(काष्ठा ib_device *dev,
						 काष्ठा scatterlist *sglist,
						 अचिन्हित पूर्णांक sg_dma_len,
						 पूर्णांक direction)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i;

	क्रम_each_sg(sglist, sg, sg_dma_len, i) अणु
		ib_dma_sync_single_क्रम_device(dev, sg_dma_address(sg),
					      sg_dma_len(sg), direction);
	पूर्ण
पूर्ण
#घोषणा ib_dma_sync_sg_क्रम_device	rds_ib_dma_sync_sg_क्रम_device


/* ib.c */
बाह्य काष्ठा rds_transport rds_ib_transport;
काष्ठा rds_ib_device *rds_ib_get_client_data(काष्ठा ib_device *device);
व्योम rds_ib_dev_put(काष्ठा rds_ib_device *rds_ibdev);
बाह्य काष्ठा ib_client rds_ib_client;

बाह्य अचिन्हित पूर्णांक rds_ib_retry_count;

बाह्य spinlock_t ib_nodev_conns_lock;
बाह्य काष्ठा list_head ib_nodev_conns;

/* ib_cm.c */
पूर्णांक rds_ib_conn_alloc(काष्ठा rds_connection *conn, gfp_t gfp);
व्योम rds_ib_conn_मुक्त(व्योम *arg);
पूर्णांक rds_ib_conn_path_connect(काष्ठा rds_conn_path *cp);
व्योम rds_ib_conn_path_shutकरोwn(काष्ठा rds_conn_path *cp);
व्योम rds_ib_state_change(काष्ठा sock *sk);
पूर्णांक rds_ib_listen_init(व्योम);
व्योम rds_ib_listen_stop(व्योम);
__म_लिखो(2, 3)
व्योम __rds_ib_conn_error(काष्ठा rds_connection *conn, स्थिर अक्षर *, ...);
पूर्णांक rds_ib_cm_handle_connect(काष्ठा rdma_cm_id *cm_id,
			     काष्ठा rdma_cm_event *event, bool isv6);
पूर्णांक rds_ib_cm_initiate_connect(काष्ठा rdma_cm_id *cm_id, bool isv6);
व्योम rds_ib_cm_connect_complete(काष्ठा rds_connection *conn,
				काष्ठा rdma_cm_event *event);

#घोषणा rds_ib_conn_error(conn, fmt...) \
	__rds_ib_conn_error(conn, KERN_WARNING "RDS/IB: " fmt)

/* ib_rdma.c */
पूर्णांक rds_ib_update_ipaddr(काष्ठा rds_ib_device *rds_ibdev,
			 काष्ठा in6_addr *ipaddr);
व्योम rds_ib_add_conn(काष्ठा rds_ib_device *rds_ibdev, काष्ठा rds_connection *conn);
व्योम rds_ib_हटाओ_conn(काष्ठा rds_ib_device *rds_ibdev, काष्ठा rds_connection *conn);
व्योम rds_ib_destroy_nodev_conns(व्योम);
व्योम rds_ib_mr_cqe_handler(काष्ठा rds_ib_connection *ic, काष्ठा ib_wc *wc);

/* ib_recv.c */
पूर्णांक rds_ib_recv_init(व्योम);
व्योम rds_ib_recv_निकास(व्योम);
पूर्णांक rds_ib_recv_path(काष्ठा rds_conn_path *conn);
पूर्णांक rds_ib_recv_alloc_caches(काष्ठा rds_ib_connection *ic, gfp_t gfp);
व्योम rds_ib_recv_मुक्त_caches(काष्ठा rds_ib_connection *ic);
व्योम rds_ib_recv_refill(काष्ठा rds_connection *conn, पूर्णांक prefill, gfp_t gfp);
व्योम rds_ib_inc_मुक्त(काष्ठा rds_incoming *inc);
पूर्णांक rds_ib_inc_copy_to_user(काष्ठा rds_incoming *inc, काष्ठा iov_iter *to);
व्योम rds_ib_recv_cqe_handler(काष्ठा rds_ib_connection *ic, काष्ठा ib_wc *wc,
			     काष्ठा rds_ib_ack_state *state);
व्योम rds_ib_recv_tasklet_fn(अचिन्हित दीर्घ data);
व्योम rds_ib_recv_init_ring(काष्ठा rds_ib_connection *ic);
व्योम rds_ib_recv_clear_ring(काष्ठा rds_ib_connection *ic);
व्योम rds_ib_recv_init_ack(काष्ठा rds_ib_connection *ic);
व्योम rds_ib_attempt_ack(काष्ठा rds_ib_connection *ic);
व्योम rds_ib_ack_send_complete(काष्ठा rds_ib_connection *ic);
u64 rds_ib_piggyb_ack(काष्ठा rds_ib_connection *ic);
व्योम rds_ib_set_ack(काष्ठा rds_ib_connection *ic, u64 seq, पूर्णांक ack_required);

/* ib_ring.c */
व्योम rds_ib_ring_init(काष्ठा rds_ib_work_ring *ring, u32 nr);
व्योम rds_ib_ring_resize(काष्ठा rds_ib_work_ring *ring, u32 nr);
u32 rds_ib_ring_alloc(काष्ठा rds_ib_work_ring *ring, u32 val, u32 *pos);
व्योम rds_ib_ring_मुक्त(काष्ठा rds_ib_work_ring *ring, u32 val);
व्योम rds_ib_ring_unalloc(काष्ठा rds_ib_work_ring *ring, u32 val);
पूर्णांक rds_ib_ring_empty(काष्ठा rds_ib_work_ring *ring);
पूर्णांक rds_ib_ring_low(काष्ठा rds_ib_work_ring *ring);
u32 rds_ib_ring_oldest(काष्ठा rds_ib_work_ring *ring);
u32 rds_ib_ring_completed(काष्ठा rds_ib_work_ring *ring, u32 wr_id, u32 oldest);
बाह्य रुको_queue_head_t rds_ib_ring_empty_रुको;

/* ib_send.c */
व्योम rds_ib_xmit_path_complete(काष्ठा rds_conn_path *cp);
पूर्णांक rds_ib_xmit(काष्ठा rds_connection *conn, काष्ठा rds_message *rm,
		अचिन्हित पूर्णांक hdr_off, अचिन्हित पूर्णांक sg, अचिन्हित पूर्णांक off);
व्योम rds_ib_send_cqe_handler(काष्ठा rds_ib_connection *ic, काष्ठा ib_wc *wc);
व्योम rds_ib_send_init_ring(काष्ठा rds_ib_connection *ic);
व्योम rds_ib_send_clear_ring(काष्ठा rds_ib_connection *ic);
पूर्णांक rds_ib_xmit_rdma(काष्ठा rds_connection *conn, काष्ठा rm_rdma_op *op);
व्योम rds_ib_send_add_credits(काष्ठा rds_connection *conn, अचिन्हित पूर्णांक credits);
व्योम rds_ib_advertise_credits(काष्ठा rds_connection *conn, अचिन्हित पूर्णांक posted);
पूर्णांक rds_ib_send_grab_credits(काष्ठा rds_ib_connection *ic, u32 wanted,
			     u32 *adv_credits, पूर्णांक need_posted, पूर्णांक max_posted);
पूर्णांक rds_ib_xmit_atomic(काष्ठा rds_connection *conn, काष्ठा rm_atomic_op *op);

/* ib_stats.c */
DECLARE_PER_CPU_SHARED_ALIGNED(काष्ठा rds_ib_statistics, rds_ib_stats);
#घोषणा rds_ib_stats_inc(member) rds_stats_inc_which(rds_ib_stats, member)
#घोषणा rds_ib_stats_add(member, count) \
		rds_stats_add_which(rds_ib_stats, member, count)
अचिन्हित पूर्णांक rds_ib_stats_info_copy(काष्ठा rds_info_iterator *iter,
				    अचिन्हित पूर्णांक avail);

/* ib_sysctl.c */
पूर्णांक rds_ib_sysctl_init(व्योम);
व्योम rds_ib_sysctl_निकास(व्योम);
बाह्य अचिन्हित दीर्घ rds_ib_sysctl_max_send_wr;
बाह्य अचिन्हित दीर्घ rds_ib_sysctl_max_recv_wr;
बाह्य अचिन्हित दीर्घ rds_ib_sysctl_max_unsig_wrs;
बाह्य अचिन्हित दीर्घ rds_ib_sysctl_max_unsig_bytes;
बाह्य अचिन्हित दीर्घ rds_ib_sysctl_max_recv_allocation;
बाह्य अचिन्हित पूर्णांक rds_ib_sysctl_flow_control;

#पूर्ण_अगर
