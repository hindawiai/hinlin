<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _RDS_RDS_H
#घोषणा _RDS_RDS_H

#समावेश <net/sock.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/highस्मृति.स>
#समावेश <rdma/rdma_cm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rds.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/refcount.h>
#समावेश <linux/in6.h>

#समावेश "info.h"

/*
 * RDS Network protocol version
 */
#घोषणा RDS_PROTOCOL_3_0	0x0300
#घोषणा RDS_PROTOCOL_3_1	0x0301
#घोषणा RDS_PROTOCOL_4_0	0x0400
#घोषणा RDS_PROTOCOL_4_1	0x0401
#घोषणा RDS_PROTOCOL_VERSION	RDS_PROTOCOL_3_1
#घोषणा RDS_PROTOCOL_MAJOR(v)	((v) >> 8)
#घोषणा RDS_PROTOCOL_MINOR(v)	((v) & 255)
#घोषणा RDS_PROTOCOL(maj, min)	(((maj) << 8) | min)
#घोषणा RDS_PROTOCOL_COMPAT_VERSION	RDS_PROTOCOL_3_1

/* The following ports, 16385, 18634, 18635, are रेजिस्टरed with IANA as
 * the ports to be used क्रम RDS over TCP and UDP.  Currently, only RDS over
 * TCP and RDS over IB/RDMA are implemented.  18634 is the historical value
 * used क्रम the RDMA_CM listener port.  RDS/TCP uses port 16385.  After
 * IPv6 work, RDMA_CM also uses 16385 as the listener port.  18634 is kept
 * to ensure compatibility with older RDS modules.  Those ports are defined
 * in each transport's header file.
 */
#घोषणा RDS_PORT	18634

#अगर_घोषित ATOMIC64_INIT
#घोषणा KERNEL_HAS_ATOMIC64
#पूर्ण_अगर
#अगर_घोषित RDS_DEBUG
#घोषणा rdsdebug(fmt, args...) pr_debug("%s(): " fmt, __func__ , ##args)
#अन्यथा
/* sigh, pr_debug() causes unused variable warnings */
अटल अंतरभूत __म_लिखो(1, 2)
व्योम rdsdebug(अक्षर *fmt, ...)
अणु
पूर्ण
#पूर्ण_अगर

#घोषणा RDS_FRAG_SHIFT	12
#घोषणा RDS_FRAG_SIZE	((अचिन्हित पूर्णांक)(1 << RDS_FRAG_SHIFT))

/* Used to limit both RDMA and non-RDMA RDS message to 1MB */
#घोषणा RDS_MAX_MSG_SIZE	((अचिन्हित पूर्णांक)(1 << 20))

#घोषणा RDS_CONG_MAP_BYTES	(65536 / 8)
#घोषणा RDS_CONG_MAP_PAGES	(PAGE_ALIGN(RDS_CONG_MAP_BYTES) / PAGE_SIZE)
#घोषणा RDS_CONG_MAP_PAGE_BITS	(PAGE_SIZE * 8)

काष्ठा rds_cong_map अणु
	काष्ठा rb_node		m_rb_node;
	काष्ठा in6_addr		m_addr;
	रुको_queue_head_t	m_रुकोq;
	काष्ठा list_head	m_conn_list;
	अचिन्हित दीर्घ		m_page_addrs[RDS_CONG_MAP_PAGES];
पूर्ण;


/*
 * This is how we will track the connection state:
 * A connection is always in one of the following
 * states. Updates to the state are atomic and imply
 * a memory barrier.
 */
क्रमागत अणु
	RDS_CONN_DOWN = 0,
	RDS_CONN_CONNECTING,
	RDS_CONN_DISCONNECTING,
	RDS_CONN_UP,
	RDS_CONN_RESETTING,
	RDS_CONN_ERROR,
पूर्ण;

/* Bits क्रम c_flags */
#घोषणा RDS_LL_SEND_FULL	0
#घोषणा RDS_RECONNECT_PENDING	1
#घोषणा RDS_IN_XMIT		2
#घोषणा RDS_RECV_REFILL		3
#घोषणा	RDS_DESTROY_PENDING	4

/* Max number of multipaths per RDS connection. Must be a घातer of 2 */
#घोषणा	RDS_MPATH_WORKERS	8
#घोषणा	RDS_MPATH_HASH(rs, n) (jhash_1word((rs)->rs_bound_port, \
			       (rs)->rs_hash_initval) & ((n) - 1))

#घोषणा IS_CANONICAL(laddr, faddr) (htonl(laddr) < htonl(faddr))

/* Per mpath connection state */
काष्ठा rds_conn_path अणु
	काष्ठा rds_connection	*cp_conn;
	काष्ठा rds_message	*cp_xmit_rm;
	अचिन्हित दीर्घ		cp_xmit_sg;
	अचिन्हित पूर्णांक		cp_xmit_hdr_off;
	अचिन्हित पूर्णांक		cp_xmit_data_off;
	अचिन्हित पूर्णांक		cp_xmit_atomic_sent;
	अचिन्हित पूर्णांक		cp_xmit_rdma_sent;
	अचिन्हित पूर्णांक		cp_xmit_data_sent;

	spinlock_t		cp_lock;		/* protect msg queues */
	u64			cp_next_tx_seq;
	काष्ठा list_head	cp_send_queue;
	काष्ठा list_head	cp_retrans;

	u64			cp_next_rx_seq;

	व्योम			*cp_transport_data;

	atomic_t		cp_state;
	अचिन्हित दीर्घ		cp_send_gen;
	अचिन्हित दीर्घ		cp_flags;
	अचिन्हित दीर्घ		cp_reconnect_jअगरfies;
	काष्ठा delayed_work	cp_send_w;
	काष्ठा delayed_work	cp_recv_w;
	काष्ठा delayed_work	cp_conn_w;
	काष्ठा work_काष्ठा	cp_करोwn_w;
	काष्ठा mutex		cp_cm_lock;	/* protect cp_state & cm */
	रुको_queue_head_t	cp_रुकोq;

	अचिन्हित पूर्णांक		cp_unacked_packets;
	अचिन्हित पूर्णांक		cp_unacked_bytes;
	अचिन्हित पूर्णांक		cp_index;
पूर्ण;

/* One rds_connection per RDS address pair */
काष्ठा rds_connection अणु
	काष्ठा hlist_node	c_hash_node;
	काष्ठा in6_addr		c_laddr;
	काष्ठा in6_addr		c_faddr;
	पूर्णांक			c_dev_अगर; /* अगरindex used क्रम this conn */
	पूर्णांक			c_bound_अगर; /* अगरindex of c_laddr */
	अचिन्हित पूर्णांक		c_loopback:1,
				c_isv6:1,
				c_ping_triggered:1,
				c_pad_to_32:29;
	पूर्णांक			c_npaths;
	काष्ठा rds_connection	*c_passive;
	काष्ठा rds_transport	*c_trans;

	काष्ठा rds_cong_map	*c_lcong;
	काष्ठा rds_cong_map	*c_fcong;

	/* Protocol version */
	अचिन्हित पूर्णांक		c_proposed_version;
	अचिन्हित पूर्णांक		c_version;
	possible_net_t		c_net;

	/* TOS */
	u8			c_tos;

	काष्ठा list_head	c_map_item;
	अचिन्हित दीर्घ		c_map_queued;

	काष्ठा rds_conn_path	*c_path;
	रुको_queue_head_t	c_hs_रुकोq; /* handshake रुकोq */

	u32			c_my_gen_num;
	u32			c_peer_gen_num;
पूर्ण;

अटल अंतरभूत
काष्ठा net *rds_conn_net(काष्ठा rds_connection *conn)
अणु
	वापस पढ़ो_pnet(&conn->c_net);
पूर्ण

अटल अंतरभूत
व्योम rds_conn_net_set(काष्ठा rds_connection *conn, काष्ठा net *net)
अणु
	ग_लिखो_pnet(&conn->c_net, net);
पूर्ण

#घोषणा RDS_FLAG_CONG_BITMAP	0x01
#घोषणा RDS_FLAG_ACK_REQUIRED	0x02
#घोषणा RDS_FLAG_RETRANSMITTED	0x04
#घोषणा RDS_MAX_ADV_CREDIT	255

/* RDS_FLAG_PROBE_PORT is the reserved sport used क्रम sending a ping
 * probe to exchange control inक्रमmation beक्रमe establishing a connection.
 * Currently the control inक्रमmation that is exchanged is the number of
 * supported paths. If the peer is a legacy (older kernel revision) peer,
 * it would वापस a pong message without additional control inक्रमmation
 * that would then alert the sender that the peer was an older rev.
 */
#घोषणा RDS_FLAG_PROBE_PORT	1
#घोषणा	RDS_HS_PROBE(sport, dport) \
		((sport == RDS_FLAG_PROBE_PORT && dport == 0) || \
		 (sport == 0 && dport == RDS_FLAG_PROBE_PORT))
/*
 * Maximum space available क्रम extension headers.
 */
#घोषणा RDS_HEADER_EXT_SPACE	16

काष्ठा rds_header अणु
	__be64	h_sequence;
	__be64	h_ack;
	__be32	h_len;
	__be16	h_sport;
	__be16	h_dport;
	u8	h_flags;
	u8	h_credit;
	u8	h_padding[4];
	__sum16	h_csum;

	u8	h_exthdr[RDS_HEADER_EXT_SPACE];
पूर्ण;

/*
 * Reserved - indicates end of extensions
 */
#घोषणा RDS_EXTHDR_NONE		0

/*
 * This extension header is included in the very
 * first message that is sent on a new connection,
 * and identअगरies the protocol level. This will help
 * rolling updates अगर a future change requires अवरोधing
 * the protocol.
 * NB: This is no दीर्घer true क्रम IB, where we करो a version
 * negotiation during the connection setup phase (protocol
 * version inक्रमmation is included in the RDMA CM निजी data).
 */
#घोषणा RDS_EXTHDR_VERSION	1
काष्ठा rds_ext_header_version अणु
	__be32			h_version;
पूर्ण;

/*
 * This extension header is included in the RDS message
 * chasing an RDMA operation.
 */
#घोषणा RDS_EXTHDR_RDMA		2
काष्ठा rds_ext_header_rdma अणु
	__be32			h_rdma_rkey;
पूर्ण;

/*
 * This extension header tells the peer about the
 * destination <R_Key,offset> of the requested RDMA
 * operation.
 */
#घोषणा RDS_EXTHDR_RDMA_DEST	3
काष्ठा rds_ext_header_rdma_dest अणु
	__be32			h_rdma_rkey;
	__be32			h_rdma_offset;
पूर्ण;

/* Extension header announcing number of paths.
 * Implicit length = 2 bytes.
 */
#घोषणा RDS_EXTHDR_NPATHS	5
#घोषणा RDS_EXTHDR_GEN_NUM	6

#घोषणा __RDS_EXTHDR_MAX	16 /* क्रम now */
#घोषणा RDS_RX_MAX_TRACES	(RDS_MSG_RX_DGRAM_TRACE_MAX + 1)
#घोषणा	RDS_MSG_RX_HDR		0
#घोषणा	RDS_MSG_RX_START	1
#घोषणा	RDS_MSG_RX_END		2
#घोषणा	RDS_MSG_RX_CMSG		3

/* The following values are whitelisted क्रम usercopy */
काष्ठा rds_inc_usercopy अणु
	rds_rdma_cookie_t	rdma_cookie;
	kसमय_प्रकार			rx_tstamp;
पूर्ण;

काष्ठा rds_incoming अणु
	refcount_t		i_refcount;
	काष्ठा list_head	i_item;
	काष्ठा rds_connection	*i_conn;
	काष्ठा rds_conn_path	*i_conn_path;
	काष्ठा rds_header	i_hdr;
	अचिन्हित दीर्घ		i_rx_jअगरfies;
	काष्ठा in6_addr		i_saddr;

	काष्ठा rds_inc_usercopy i_usercopy;
	u64			i_rx_lat_trace[RDS_RX_MAX_TRACES];
पूर्ण;

काष्ठा rds_mr अणु
	काष्ठा rb_node		r_rb_node;
	काष्ठा kref		r_kref;
	u32			r_key;

	/* A copy of the creation flags */
	अचिन्हित पूर्णांक		r_use_once:1;
	अचिन्हित पूर्णांक		r_invalidate:1;
	अचिन्हित पूर्णांक		r_ग_लिखो:1;

	काष्ठा rds_sock		*r_sock; /* back poपूर्णांकer to the socket that owns us */
	काष्ठा rds_transport	*r_trans;
	व्योम			*r_trans_निजी;
पूर्ण;

अटल अंतरभूत rds_rdma_cookie_t rds_rdma_make_cookie(u32 r_key, u32 offset)
अणु
	वापस r_key | (((u64) offset) << 32);
पूर्ण

अटल अंतरभूत u32 rds_rdma_cookie_key(rds_rdma_cookie_t cookie)
अणु
	वापस cookie;
पूर्ण

अटल अंतरभूत u32 rds_rdma_cookie_offset(rds_rdma_cookie_t cookie)
अणु
	वापस cookie >> 32;
पूर्ण

/* atomic operation types */
#घोषणा RDS_ATOMIC_TYPE_CSWP		0
#घोषणा RDS_ATOMIC_TYPE_FADD		1

/*
 * m_sock_item and m_conn_item are on lists that are serialized under
 * conn->c_lock.  m_sock_item has additional meaning in that once it is empty
 * the message will not be put back on the retransmit list after being sent.
 * messages that are canceled जबतक being sent rely on this.
 *
 * m_inc is used by loopback so that it can pass an incoming message straight
 * back up पूर्णांकo the rx path.  It embeds a wire header which is also used by
 * the send path, which is kind of awkward.
 *
 * m_sock_item indicates the message's presence on a socket's send or receive
 * queue.  m_rs will poपूर्णांक to that socket.
 *
 * m_daddr is used by cancellation to prune messages to a given destination.
 *
 * The RDS_MSG_ON_SOCK and RDS_MSG_ON_CONN flags are used to aव्योम lock
 * nesting.  As paths iterate over messages on a sock, or conn, they must
 * also lock the conn, or sock, to हटाओ the message from those lists too.
 * Testing the flag to determine अगर the message is still on the lists lets
 * us aव्योम testing the list_head directly.  That means each path can use
 * the message's list_head to keep it on a local list जबतक juggling locks
 * without confusing the other path.
 *
 * m_ack_seq is an optional field set by transports who need a dअगरferent
 * sequence number range to invalidate.  They can use this in a callback
 * that they pass to rds_send_drop_acked() to see अगर each message has been
 * acked.  The HAS_ACK_SEQ flag can be used to detect messages which haven't
 * had ack_seq set yet.
 */
#घोषणा RDS_MSG_ON_SOCK		1
#घोषणा RDS_MSG_ON_CONN		2
#घोषणा RDS_MSG_HAS_ACK_SEQ	3
#घोषणा RDS_MSG_ACK_REQUIRED	4
#घोषणा RDS_MSG_RETRANSMITTED	5
#घोषणा RDS_MSG_MAPPED		6
#घोषणा RDS_MSG_PAGEVEC		7
#घोषणा RDS_MSG_FLUSH		8

काष्ठा rds_znotअगरier अणु
	काष्ठा mmpin		z_mmp;
	u32			z_cookie;
पूर्ण;

काष्ठा rds_msg_zcopy_info अणु
	काष्ठा list_head rs_zcookie_next;
	जोड़ अणु
		काष्ठा rds_znotअगरier znotअगर;
		काष्ठा rds_zcopy_cookies zcookies;
	पूर्ण;
पूर्ण;

काष्ठा rds_msg_zcopy_queue अणु
	काष्ठा list_head zcookie_head;
	spinlock_t lock; /* protects zcookie_head queue */
पूर्ण;

अटल अंतरभूत व्योम rds_message_zcopy_queue_init(काष्ठा rds_msg_zcopy_queue *q)
अणु
	spin_lock_init(&q->lock);
	INIT_LIST_HEAD(&q->zcookie_head);
पूर्ण

काष्ठा rds_iov_vector अणु
	काष्ठा rds_iovec *iov;
	पूर्णांक               len;
पूर्ण;

काष्ठा rds_iov_vector_arr अणु
	काष्ठा rds_iov_vector *vec;
	पूर्णांक                    len;
	पूर्णांक                    indx;
	पूर्णांक                    incr;
पूर्ण;

काष्ठा rds_message अणु
	refcount_t		m_refcount;
	काष्ठा list_head	m_sock_item;
	काष्ठा list_head	m_conn_item;
	काष्ठा rds_incoming	m_inc;
	u64			m_ack_seq;
	काष्ठा in6_addr		m_daddr;
	अचिन्हित दीर्घ		m_flags;

	/* Never access m_rs without holding m_rs_lock.
	 * Lock nesting is
	 *  rm->m_rs_lock
	 *   -> rs->rs_lock
	 */
	spinlock_t		m_rs_lock;
	रुको_queue_head_t	m_flush_रुको;

	काष्ठा rds_sock		*m_rs;

	/* cookie to send to remote, in rds header */
	rds_rdma_cookie_t	m_rdma_cookie;

	अचिन्हित पूर्णांक		m_used_sgs;
	अचिन्हित पूर्णांक		m_total_sgs;

	व्योम			*m_final_op;

	काष्ठा अणु
		काष्ठा rm_atomic_op अणु
			पूर्णांक			op_type;
			जोड़ अणु
				काष्ठा अणु
					uपूर्णांक64_t	compare;
					uपूर्णांक64_t	swap;
					uपूर्णांक64_t	compare_mask;
					uपूर्णांक64_t	swap_mask;
				पूर्ण op_m_cswp;
				काष्ठा अणु
					uपूर्णांक64_t	add;
					uपूर्णांक64_t	nocarry_mask;
				पूर्ण op_m_fadd;
			पूर्ण;

			u32			op_rkey;
			u64			op_remote_addr;
			अचिन्हित पूर्णांक		op_notअगरy:1;
			अचिन्हित पूर्णांक		op_recverr:1;
			अचिन्हित पूर्णांक		op_mapped:1;
			अचिन्हित पूर्णांक		op_silent:1;
			अचिन्हित पूर्णांक		op_active:1;
			काष्ठा scatterlist	*op_sg;
			काष्ठा rds_notअगरier	*op_notअगरier;

			काष्ठा rds_mr		*op_rdma_mr;
		पूर्ण atomic;
		काष्ठा rm_rdma_op अणु
			u32			op_rkey;
			u64			op_remote_addr;
			अचिन्हित पूर्णांक		op_ग_लिखो:1;
			अचिन्हित पूर्णांक		op_fence:1;
			अचिन्हित पूर्णांक		op_notअगरy:1;
			अचिन्हित पूर्णांक		op_recverr:1;
			अचिन्हित पूर्णांक		op_mapped:1;
			अचिन्हित पूर्णांक		op_silent:1;
			अचिन्हित पूर्णांक		op_active:1;
			अचिन्हित पूर्णांक		op_bytes;
			अचिन्हित पूर्णांक		op_nents;
			अचिन्हित पूर्णांक		op_count;
			काष्ठा scatterlist	*op_sg;
			काष्ठा rds_notअगरier	*op_notअगरier;

			काष्ठा rds_mr		*op_rdma_mr;

			u64			op_odp_addr;
			काष्ठा rds_mr		*op_odp_mr;
		पूर्ण rdma;
		काष्ठा rm_data_op अणु
			अचिन्हित पूर्णांक		op_active:1;
			अचिन्हित पूर्णांक		op_nents;
			अचिन्हित पूर्णांक		op_count;
			अचिन्हित पूर्णांक		op_dmasg;
			अचिन्हित पूर्णांक		op_dmaoff;
			काष्ठा rds_znotअगरier	*op_mmp_znotअगरier;
			काष्ठा scatterlist	*op_sg;
		पूर्ण data;
	पूर्ण;

	काष्ठा rds_conn_path *m_conn_path;
पूर्ण;

/*
 * The RDS notअगरier is used (optionally) to tell the application about
 * completed RDMA operations. Rather than keeping the whole rds message
 * around on the queue, we allocate a small notअगरier that is put on the
 * socket's notअगरier_list. Notअगरications are delivered to the application
 * through control messages.
 */
काष्ठा rds_notअगरier अणु
	काष्ठा list_head	n_list;
	uपूर्णांक64_t		n_user_token;
	पूर्णांक			n_status;
पूर्ण;

/* Available as part of RDS core, so करोesn't need to participate
 * in get_preferred transport etc
 */
#घोषणा	RDS_TRANS_LOOP	3

/**
 * काष्ठा rds_transport -  transport specअगरic behavioural hooks
 *
 * @xmit: .xmit is called by rds_send_xmit() to tell the transport to send
 *        part of a message.  The caller serializes on the send_sem so this
 *        करोesn't need to be reentrant क्रम a given conn.  The header must be
 *        sent beक्रमe the data payload.  .xmit must be prepared to send a
 *        message with no data payload.  .xmit should वापस the number of
 *        bytes that were sent करोwn the connection, including header bytes.
 *        Returning 0 tells the caller that it करोesn't need to perक्रमm any
 *        additional work now.  This is usually the हाल when the transport has
 *        filled the sending queue क्रम its connection and will handle
 *        triggering the rds thपढ़ो to जारी the send when space becomes
 *        available.  Returning -EAGAIN tells the caller to retry the send
 *        immediately.  Returning -ENOMEM tells the caller to retry the send at
 *        some poपूर्णांक in the future.
 *
 * @conn_shutकरोwn: conn_shutकरोwn stops traffic on the given connection.  Once
 *                 it वापसs the connection can not call rds_recv_incoming().
 *                 This will only be called once after conn_connect वापसs
 *                 non-zero success and will The caller serializes this with
 *                 the send and connecting paths (xmit_* and conn_*).  The
 *                 transport is responsible क्रम other serialization, including
 *                 rds_recv_incoming().  This is called in process context but
 *                 should try hard not to block.
 */

काष्ठा rds_transport अणु
	अक्षर			t_name[TRANSNAMSIZ];
	काष्ठा list_head	t_item;
	काष्ठा module		*t_owner;
	अचिन्हित पूर्णांक		t_prefer_loopback:1,
				t_mp_capable:1;
	अचिन्हित पूर्णांक		t_type;

	पूर्णांक (*laddr_check)(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr,
			   __u32 scope_id);
	पूर्णांक (*conn_alloc)(काष्ठा rds_connection *conn, gfp_t gfp);
	व्योम (*conn_मुक्त)(व्योम *data);
	पूर्णांक (*conn_path_connect)(काष्ठा rds_conn_path *cp);
	व्योम (*conn_path_shutकरोwn)(काष्ठा rds_conn_path *conn);
	व्योम (*xmit_path_prepare)(काष्ठा rds_conn_path *cp);
	व्योम (*xmit_path_complete)(काष्ठा rds_conn_path *cp);
	पूर्णांक (*xmit)(काष्ठा rds_connection *conn, काष्ठा rds_message *rm,
		    अचिन्हित पूर्णांक hdr_off, अचिन्हित पूर्णांक sg, अचिन्हित पूर्णांक off);
	पूर्णांक (*xmit_rdma)(काष्ठा rds_connection *conn, काष्ठा rm_rdma_op *op);
	पूर्णांक (*xmit_atomic)(काष्ठा rds_connection *conn, काष्ठा rm_atomic_op *op);
	पूर्णांक (*recv_path)(काष्ठा rds_conn_path *cp);
	पूर्णांक (*inc_copy_to_user)(काष्ठा rds_incoming *inc, काष्ठा iov_iter *to);
	व्योम (*inc_मुक्त)(काष्ठा rds_incoming *inc);

	पूर्णांक (*cm_handle_connect)(काष्ठा rdma_cm_id *cm_id,
				 काष्ठा rdma_cm_event *event, bool isv6);
	पूर्णांक (*cm_initiate_connect)(काष्ठा rdma_cm_id *cm_id, bool isv6);
	व्योम (*cm_connect_complete)(काष्ठा rds_connection *conn,
				    काष्ठा rdma_cm_event *event);

	अचिन्हित पूर्णांक (*stats_info_copy)(काष्ठा rds_info_iterator *iter,
					अचिन्हित पूर्णांक avail);
	व्योम (*निकास)(व्योम);
	व्योम *(*get_mr)(काष्ठा scatterlist *sg, अचिन्हित दीर्घ nr_sg,
			काष्ठा rds_sock *rs, u32 *key_ret,
			काष्ठा rds_connection *conn,
			u64 start, u64 length, पूर्णांक need_odp);
	व्योम (*sync_mr)(व्योम *trans_निजी, पूर्णांक direction);
	व्योम (*मुक्त_mr)(व्योम *trans_निजी, पूर्णांक invalidate);
	व्योम (*flush_mrs)(व्योम);
	bool (*t_unloading)(काष्ठा rds_connection *conn);
	u8 (*get_tos_map)(u8 tos);
पूर्ण;

/* Bind hash table key length.  It is the sum of the size of a काष्ठा
 * in6_addr, a scope_id  and a port.
 */
#घोषणा RDS_BOUND_KEY_LEN \
	(माप(काष्ठा in6_addr) + माप(__u32) + माप(__be16))

काष्ठा rds_sock अणु
	काष्ठा sock		rs_sk;

	u64			rs_user_addr;
	u64			rs_user_bytes;

	/*
	 * bound_addr used क्रम both incoming and outgoing, no INADDR_ANY
	 * support.
	 */
	काष्ठा rhash_head	rs_bound_node;
	u8			rs_bound_key[RDS_BOUND_KEY_LEN];
	काष्ठा sockaddr_in6	rs_bound_sin6;
#घोषणा rs_bound_addr		rs_bound_sin6.sin6_addr
#घोषणा rs_bound_addr_v4	rs_bound_sin6.sin6_addr.s6_addr32[3]
#घोषणा rs_bound_port		rs_bound_sin6.sin6_port
#घोषणा rs_bound_scope_id	rs_bound_sin6.sin6_scope_id
	काष्ठा in6_addr		rs_conn_addr;
#घोषणा rs_conn_addr_v4		rs_conn_addr.s6_addr32[3]
	__be16			rs_conn_port;
	काष्ठा rds_transport    *rs_transport;

	/*
	 * rds_sendmsg caches the conn it used the last समय around.
	 * This helps aव्योम costly lookups.
	 */
	काष्ठा rds_connection	*rs_conn;

	/* flag indicating we were congested or not */
	पूर्णांक			rs_congested;
	/* seen congestion (ENOBUFS) when sending? */
	पूर्णांक			rs_seen_congestion;

	/* rs_lock protects all these adjacent members beक्रमe the newline */
	spinlock_t		rs_lock;
	काष्ठा list_head	rs_send_queue;
	u32			rs_snd_bytes;
	पूर्णांक			rs_rcv_bytes;
	काष्ठा list_head	rs_notअगरy_queue;	/* currently used क्रम failed RDMAs */

	/* Congestion wake_up. If rs_cong_monitor is set, we use cong_mask
	 * to decide whether the application should be woken up.
	 * If not set, we use rs_cong_track to find out whether a cong map
	 * update arrived.
	 */
	uपूर्णांक64_t		rs_cong_mask;
	uपूर्णांक64_t		rs_cong_notअगरy;
	काष्ठा list_head	rs_cong_list;
	अचिन्हित दीर्घ		rs_cong_track;

	/*
	 * rs_recv_lock protects the receive queue, and is
	 * used to serialize with rds_release.
	 */
	rwlock_t		rs_recv_lock;
	काष्ठा list_head	rs_recv_queue;

	/* just क्रम stats reporting */
	काष्ठा list_head	rs_item;

	/* these have their own lock */
	spinlock_t		rs_rdma_lock;
	काष्ठा rb_root		rs_rdma_keys;

	/* Socket options - in हाल there will be more */
	अचिन्हित अक्षर		rs_recverr,
				rs_cong_monitor;
	u32			rs_hash_initval;

	/* Socket receive path trace poपूर्णांकs*/
	u8			rs_rx_traces;
	u8			rs_rx_trace[RDS_MSG_RX_DGRAM_TRACE_MAX];
	काष्ठा rds_msg_zcopy_queue rs_zcookie_queue;
	u8			rs_tos;
पूर्ण;

अटल अंतरभूत काष्ठा rds_sock *rds_sk_to_rs(स्थिर काष्ठा sock *sk)
अणु
	वापस container_of(sk, काष्ठा rds_sock, rs_sk);
पूर्ण
अटल अंतरभूत काष्ठा sock *rds_rs_to_sk(काष्ठा rds_sock *rs)
अणु
	वापस &rs->rs_sk;
पूर्ण

/*
 * The stack assigns sk_sndbuf and sk_rcvbuf to twice the specअगरied value
 * to account क्रम overhead.  We करोn't account क्रम overhead, we just apply
 * the number of payload bytes to the specअगरied value.
 */
अटल अंतरभूत पूर्णांक rds_sk_sndbuf(काष्ठा rds_sock *rs)
अणु
	वापस rds_rs_to_sk(rs)->sk_sndbuf / 2;
पूर्ण
अटल अंतरभूत पूर्णांक rds_sk_rcvbuf(काष्ठा rds_sock *rs)
अणु
	वापस rds_rs_to_sk(rs)->sk_rcvbuf / 2;
पूर्ण

काष्ठा rds_statistics अणु
	uपूर्णांक64_t	s_conn_reset;
	uपूर्णांक64_t	s_recv_drop_bad_checksum;
	uपूर्णांक64_t	s_recv_drop_old_seq;
	uपूर्णांक64_t	s_recv_drop_no_sock;
	uपूर्णांक64_t	s_recv_drop_dead_sock;
	uपूर्णांक64_t	s_recv_deliver_raced;
	uपूर्णांक64_t	s_recv_delivered;
	uपूर्णांक64_t	s_recv_queued;
	uपूर्णांक64_t	s_recv_immediate_retry;
	uपूर्णांक64_t	s_recv_delayed_retry;
	uपूर्णांक64_t	s_recv_ack_required;
	uपूर्णांक64_t	s_recv_rdma_bytes;
	uपूर्णांक64_t	s_recv_ping;
	uपूर्णांक64_t	s_send_queue_empty;
	uपूर्णांक64_t	s_send_queue_full;
	uपूर्णांक64_t	s_send_lock_contention;
	uपूर्णांक64_t	s_send_lock_queue_raced;
	uपूर्णांक64_t	s_send_immediate_retry;
	uपूर्णांक64_t	s_send_delayed_retry;
	uपूर्णांक64_t	s_send_drop_acked;
	uपूर्णांक64_t	s_send_ack_required;
	uपूर्णांक64_t	s_send_queued;
	uपूर्णांक64_t	s_send_rdma;
	uपूर्णांक64_t	s_send_rdma_bytes;
	uपूर्णांक64_t	s_send_pong;
	uपूर्णांक64_t	s_page_reमुख्यder_hit;
	uपूर्णांक64_t	s_page_reमुख्यder_miss;
	uपूर्णांक64_t	s_copy_to_user;
	uपूर्णांक64_t	s_copy_from_user;
	uपूर्णांक64_t	s_cong_update_queued;
	uपूर्णांक64_t	s_cong_update_received;
	uपूर्णांक64_t	s_cong_send_error;
	uपूर्णांक64_t	s_cong_send_blocked;
	uपूर्णांक64_t	s_recv_bytes_added_to_socket;
	uपूर्णांक64_t	s_recv_bytes_हटाओd_from_socket;
	uपूर्णांक64_t	s_send_stuck_rm;
पूर्ण;

/* af_rds.c */
व्योम rds_sock_addref(काष्ठा rds_sock *rs);
व्योम rds_sock_put(काष्ठा rds_sock *rs);
व्योम rds_wake_sk_sleep(काष्ठा rds_sock *rs);
अटल अंतरभूत व्योम __rds_wake_sk_sleep(काष्ठा sock *sk)
अणु
	रुको_queue_head_t *रुकोq = sk_sleep(sk);

	अगर (!sock_flag(sk, SOCK_DEAD) && रुकोq)
		wake_up(रुकोq);
पूर्ण
बाह्य रुको_queue_head_t rds_poll_रुकोq;


/* bind.c */
पूर्णांक rds_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक addr_len);
व्योम rds_हटाओ_bound(काष्ठा rds_sock *rs);
काष्ठा rds_sock *rds_find_bound(स्थिर काष्ठा in6_addr *addr, __be16 port,
				__u32 scope_id);
पूर्णांक rds_bind_lock_init(व्योम);
व्योम rds_bind_lock_destroy(व्योम);

/* cong.c */
पूर्णांक rds_cong_get_maps(काष्ठा rds_connection *conn);
व्योम rds_cong_add_conn(काष्ठा rds_connection *conn);
व्योम rds_cong_हटाओ_conn(काष्ठा rds_connection *conn);
व्योम rds_cong_set_bit(काष्ठा rds_cong_map *map, __be16 port);
व्योम rds_cong_clear_bit(काष्ठा rds_cong_map *map, __be16 port);
पूर्णांक rds_cong_रुको(काष्ठा rds_cong_map *map, __be16 port, पूर्णांक nonblock, काष्ठा rds_sock *rs);
व्योम rds_cong_queue_updates(काष्ठा rds_cong_map *map);
व्योम rds_cong_map_updated(काष्ठा rds_cong_map *map, uपूर्णांक64_t);
पूर्णांक rds_cong_updated_since(अचिन्हित दीर्घ *recent);
व्योम rds_cong_add_socket(काष्ठा rds_sock *);
व्योम rds_cong_हटाओ_socket(काष्ठा rds_sock *);
व्योम rds_cong_निकास(व्योम);
काष्ठा rds_message *rds_cong_update_alloc(काष्ठा rds_connection *conn);

/* connection.c */
बाह्य u32 rds_gen_num;
पूर्णांक rds_conn_init(व्योम);
व्योम rds_conn_निकास(व्योम);
काष्ठा rds_connection *rds_conn_create(काष्ठा net *net,
				       स्थिर काष्ठा in6_addr *laddr,
				       स्थिर काष्ठा in6_addr *faddr,
				       काष्ठा rds_transport *trans,
				       u8 tos, gfp_t gfp,
				       पूर्णांक dev_अगर);
काष्ठा rds_connection *rds_conn_create_outgoing(काष्ठा net *net,
						स्थिर काष्ठा in6_addr *laddr,
						स्थिर काष्ठा in6_addr *faddr,
						काष्ठा rds_transport *trans,
						u8 tos, gfp_t gfp, पूर्णांक dev_अगर);
व्योम rds_conn_shutकरोwn(काष्ठा rds_conn_path *cpath);
व्योम rds_conn_destroy(काष्ठा rds_connection *conn);
व्योम rds_conn_drop(काष्ठा rds_connection *conn);
व्योम rds_conn_path_drop(काष्ठा rds_conn_path *cpath, bool destroy);
व्योम rds_conn_connect_अगर_करोwn(काष्ठा rds_connection *conn);
व्योम rds_conn_path_connect_अगर_करोwn(काष्ठा rds_conn_path *cp);
व्योम rds_check_all_paths(काष्ठा rds_connection *conn);
व्योम rds_क्रम_each_conn_info(काष्ठा socket *sock, अचिन्हित पूर्णांक len,
			  काष्ठा rds_info_iterator *iter,
			  काष्ठा rds_info_lengths *lens,
			  पूर्णांक (*visitor)(काष्ठा rds_connection *, व्योम *),
			  u64 *buffer,
			  माप_प्रकार item_len);

__म_लिखो(2, 3)
व्योम __rds_conn_path_error(काष्ठा rds_conn_path *cp, स्थिर अक्षर *, ...);
#घोषणा rds_conn_path_error(cp, fmt...) \
	__rds_conn_path_error(cp, KERN_WARNING "RDS: " fmt)

अटल अंतरभूत पूर्णांक
rds_conn_path_transition(काष्ठा rds_conn_path *cp, पूर्णांक old, पूर्णांक new)
अणु
	वापस atomic_cmpxchg(&cp->cp_state, old, new) == old;
पूर्ण

अटल अंतरभूत पूर्णांक
rds_conn_transition(काष्ठा rds_connection *conn, पूर्णांक old, पूर्णांक new)
अणु
	WARN_ON(conn->c_trans->t_mp_capable);
	वापस rds_conn_path_transition(&conn->c_path[0], old, new);
पूर्ण

अटल अंतरभूत पूर्णांक
rds_conn_path_state(काष्ठा rds_conn_path *cp)
अणु
	वापस atomic_पढ़ो(&cp->cp_state);
पूर्ण

अटल अंतरभूत पूर्णांक
rds_conn_state(काष्ठा rds_connection *conn)
अणु
	WARN_ON(conn->c_trans->t_mp_capable);
	वापस rds_conn_path_state(&conn->c_path[0]);
पूर्ण

अटल अंतरभूत पूर्णांक
rds_conn_path_up(काष्ठा rds_conn_path *cp)
अणु
	वापस atomic_पढ़ो(&cp->cp_state) == RDS_CONN_UP;
पूर्ण

अटल अंतरभूत पूर्णांक
rds_conn_path_करोwn(काष्ठा rds_conn_path *cp)
अणु
	वापस atomic_पढ़ो(&cp->cp_state) == RDS_CONN_DOWN;
पूर्ण

अटल अंतरभूत पूर्णांक
rds_conn_up(काष्ठा rds_connection *conn)
अणु
	WARN_ON(conn->c_trans->t_mp_capable);
	वापस rds_conn_path_up(&conn->c_path[0]);
पूर्ण

अटल अंतरभूत पूर्णांक
rds_conn_path_connecting(काष्ठा rds_conn_path *cp)
अणु
	वापस atomic_पढ़ो(&cp->cp_state) == RDS_CONN_CONNECTING;
पूर्ण

अटल अंतरभूत पूर्णांक
rds_conn_connecting(काष्ठा rds_connection *conn)
अणु
	WARN_ON(conn->c_trans->t_mp_capable);
	वापस rds_conn_path_connecting(&conn->c_path[0]);
पूर्ण

/* message.c */
काष्ठा rds_message *rds_message_alloc(अचिन्हित पूर्णांक nents, gfp_t gfp);
काष्ठा scatterlist *rds_message_alloc_sgs(काष्ठा rds_message *rm, पूर्णांक nents);
पूर्णांक rds_message_copy_from_user(काष्ठा rds_message *rm, काष्ठा iov_iter *from,
			       bool zcopy);
काष्ठा rds_message *rds_message_map_pages(अचिन्हित दीर्घ *page_addrs, अचिन्हित पूर्णांक total_len);
व्योम rds_message_populate_header(काष्ठा rds_header *hdr, __be16 sport,
				 __be16 dport, u64 seq);
पूर्णांक rds_message_add_extension(काष्ठा rds_header *hdr,
			      अचिन्हित पूर्णांक type, स्थिर व्योम *data, अचिन्हित पूर्णांक len);
पूर्णांक rds_message_next_extension(काष्ठा rds_header *hdr,
			       अचिन्हित पूर्णांक *pos, व्योम *buf, अचिन्हित पूर्णांक *buflen);
पूर्णांक rds_message_add_rdma_dest_extension(काष्ठा rds_header *hdr, u32 r_key, u32 offset);
पूर्णांक rds_message_inc_copy_to_user(काष्ठा rds_incoming *inc, काष्ठा iov_iter *to);
व्योम rds_message_inc_मुक्त(काष्ठा rds_incoming *inc);
व्योम rds_message_addref(काष्ठा rds_message *rm);
व्योम rds_message_put(काष्ठा rds_message *rm);
व्योम rds_message_रुको(काष्ठा rds_message *rm);
व्योम rds_message_unmapped(काष्ठा rds_message *rm);
व्योम rds_notअगरy_msg_zcopy_purge(काष्ठा rds_msg_zcopy_queue *info);

अटल अंतरभूत व्योम rds_message_make_checksum(काष्ठा rds_header *hdr)
अणु
	hdr->h_csum = 0;
	hdr->h_csum = ip_fast_csum((व्योम *) hdr, माप(*hdr) >> 2);
पूर्ण

अटल अंतरभूत पूर्णांक rds_message_verअगरy_checksum(स्थिर काष्ठा rds_header *hdr)
अणु
	वापस !hdr->h_csum || ip_fast_csum((व्योम *) hdr, माप(*hdr) >> 2) == 0;
पूर्ण


/* page.c */
पूर्णांक rds_page_reमुख्यder_alloc(काष्ठा scatterlist *scat, अचिन्हित दीर्घ bytes,
			     gfp_t gfp);
व्योम rds_page_निकास(व्योम);

/* recv.c */
व्योम rds_inc_init(काष्ठा rds_incoming *inc, काष्ठा rds_connection *conn,
		  काष्ठा in6_addr *saddr);
व्योम rds_inc_path_init(काष्ठा rds_incoming *inc, काष्ठा rds_conn_path *conn,
		       काष्ठा in6_addr *saddr);
व्योम rds_inc_put(काष्ठा rds_incoming *inc);
व्योम rds_recv_incoming(काष्ठा rds_connection *conn, काष्ठा in6_addr *saddr,
		       काष्ठा in6_addr *daddr,
		       काष्ठा rds_incoming *inc, gfp_t gfp);
पूर्णांक rds_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size,
		पूर्णांक msg_flags);
व्योम rds_clear_recv_queue(काष्ठा rds_sock *rs);
पूर्णांक rds_notअगरy_queue_get(काष्ठा rds_sock *rs, काष्ठा msghdr *msg);
व्योम rds_inc_info_copy(काष्ठा rds_incoming *inc,
		       काष्ठा rds_info_iterator *iter,
		       __be32 saddr, __be32 daddr, पूर्णांक flip);
व्योम rds6_inc_info_copy(काष्ठा rds_incoming *inc,
			काष्ठा rds_info_iterator *iter,
			काष्ठा in6_addr *saddr, काष्ठा in6_addr *daddr,
			पूर्णांक flip);

/* send.c */
पूर्णांक rds_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार payload_len);
व्योम rds_send_path_reset(काष्ठा rds_conn_path *conn);
पूर्णांक rds_send_xmit(काष्ठा rds_conn_path *cp);
काष्ठा sockaddr_in;
व्योम rds_send_drop_to(काष्ठा rds_sock *rs, काष्ठा sockaddr_in6 *dest);
प्रकार पूर्णांक (*is_acked_func)(काष्ठा rds_message *rm, uपूर्णांक64_t ack);
व्योम rds_send_drop_acked(काष्ठा rds_connection *conn, u64 ack,
			 is_acked_func is_acked);
व्योम rds_send_path_drop_acked(काष्ठा rds_conn_path *cp, u64 ack,
			      is_acked_func is_acked);
व्योम rds_send_ping(काष्ठा rds_connection *conn, पूर्णांक cp_index);
पूर्णांक rds_send_pong(काष्ठा rds_conn_path *cp, __be16 dport);

/* rdma.c */
व्योम rds_rdma_unuse(काष्ठा rds_sock *rs, u32 r_key, पूर्णांक क्रमce);
पूर्णांक rds_get_mr(काष्ठा rds_sock *rs, sockptr_t optval, पूर्णांक optlen);
पूर्णांक rds_get_mr_क्रम_dest(काष्ठा rds_sock *rs, sockptr_t optval, पूर्णांक optlen);
पूर्णांक rds_मुक्त_mr(काष्ठा rds_sock *rs, sockptr_t optval, पूर्णांक optlen);
व्योम rds_rdma_drop_keys(काष्ठा rds_sock *rs);
पूर्णांक rds_rdma_extra_size(काष्ठा rds_rdma_args *args,
			काष्ठा rds_iov_vector *iov);
पूर्णांक rds_cmsg_rdma_dest(काष्ठा rds_sock *rs, काष्ठा rds_message *rm,
			  काष्ठा cmsghdr *cmsg);
पूर्णांक rds_cmsg_rdma_args(काष्ठा rds_sock *rs, काष्ठा rds_message *rm,
			  काष्ठा cmsghdr *cmsg,
			  काष्ठा rds_iov_vector *vec);
पूर्णांक rds_cmsg_rdma_map(काष्ठा rds_sock *rs, काष्ठा rds_message *rm,
			  काष्ठा cmsghdr *cmsg);
व्योम rds_rdma_मुक्त_op(काष्ठा rm_rdma_op *ro);
व्योम rds_atomic_मुक्त_op(काष्ठा rm_atomic_op *ao);
व्योम rds_rdma_send_complete(काष्ठा rds_message *rm, पूर्णांक wc_status);
व्योम rds_atomic_send_complete(काष्ठा rds_message *rm, पूर्णांक wc_status);
पूर्णांक rds_cmsg_atomic(काष्ठा rds_sock *rs, काष्ठा rds_message *rm,
		    काष्ठा cmsghdr *cmsg);

व्योम __rds_put_mr_final(काष्ठा kref *kref);

अटल अंतरभूत bool rds_destroy_pending(काष्ठा rds_connection *conn)
अणु
	वापस !check_net(rds_conn_net(conn)) ||
	       (conn->c_trans->t_unloading && conn->c_trans->t_unloading(conn));
पूर्ण

क्रमागत अणु
	ODP_NOT_NEEDED,
	ODP_ZEROBASED,
	ODP_VIRTUAL
पूर्ण;

/* stats.c */
DECLARE_PER_CPU_SHARED_ALIGNED(काष्ठा rds_statistics, rds_stats);
#घोषणा rds_stats_inc_which(which, member) करो अणु		\
	per_cpu(which, get_cpu()).member++;		\
	put_cpu();					\
पूर्ण जबतक (0)
#घोषणा rds_stats_inc(member) rds_stats_inc_which(rds_stats, member)
#घोषणा rds_stats_add_which(which, member, count) करो अणु		\
	per_cpu(which, get_cpu()).member += count;	\
	put_cpu();					\
पूर्ण जबतक (0)
#घोषणा rds_stats_add(member, count) rds_stats_add_which(rds_stats, member, count)
पूर्णांक rds_stats_init(व्योम);
व्योम rds_stats_निकास(व्योम);
व्योम rds_stats_info_copy(काष्ठा rds_info_iterator *iter,
			 uपूर्णांक64_t *values, स्थिर अक्षर *स्थिर *names,
			 माप_प्रकार nr);

/* sysctl.c */
पूर्णांक rds_sysctl_init(व्योम);
व्योम rds_sysctl_निकास(व्योम);
बाह्य अचिन्हित दीर्घ rds_sysctl_sndbuf_min;
बाह्य अचिन्हित दीर्घ rds_sysctl_sndbuf_शेष;
बाह्य अचिन्हित दीर्घ rds_sysctl_sndbuf_max;
बाह्य अचिन्हित दीर्घ rds_sysctl_reconnect_min_jअगरfies;
बाह्य अचिन्हित दीर्घ rds_sysctl_reconnect_max_jअगरfies;
बाह्य अचिन्हित पूर्णांक  rds_sysctl_max_unacked_packets;
बाह्य अचिन्हित पूर्णांक  rds_sysctl_max_unacked_bytes;
बाह्य अचिन्हित पूर्णांक  rds_sysctl_ping_enable;
बाह्य अचिन्हित दीर्घ rds_sysctl_trace_flags;
बाह्य अचिन्हित पूर्णांक  rds_sysctl_trace_level;

/* thपढ़ोs.c */
पूर्णांक rds_thपढ़ोs_init(व्योम);
व्योम rds_thपढ़ोs_निकास(व्योम);
बाह्य काष्ठा workqueue_काष्ठा *rds_wq;
व्योम rds_queue_reconnect(काष्ठा rds_conn_path *cp);
व्योम rds_connect_worker(काष्ठा work_काष्ठा *);
व्योम rds_shutकरोwn_worker(काष्ठा work_काष्ठा *);
व्योम rds_send_worker(काष्ठा work_काष्ठा *);
व्योम rds_recv_worker(काष्ठा work_काष्ठा *);
व्योम rds_connect_path_complete(काष्ठा rds_conn_path *conn, पूर्णांक curr);
व्योम rds_connect_complete(काष्ठा rds_connection *conn);
पूर्णांक rds_addr_cmp(स्थिर काष्ठा in6_addr *a1, स्थिर काष्ठा in6_addr *a2);

/* transport.c */
व्योम rds_trans_रेजिस्टर(काष्ठा rds_transport *trans);
व्योम rds_trans_unरेजिस्टर(काष्ठा rds_transport *trans);
काष्ठा rds_transport *rds_trans_get_preferred(काष्ठा net *net,
					      स्थिर काष्ठा in6_addr *addr,
					      __u32 scope_id);
व्योम rds_trans_put(काष्ठा rds_transport *trans);
अचिन्हित पूर्णांक rds_trans_stats_info_copy(काष्ठा rds_info_iterator *iter,
				       अचिन्हित पूर्णांक avail);
काष्ठा rds_transport *rds_trans_get(पूर्णांक t_type);
पूर्णांक rds_trans_init(व्योम);
व्योम rds_trans_निकास(व्योम);

#पूर्ण_अगर
