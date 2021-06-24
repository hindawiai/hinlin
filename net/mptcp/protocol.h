<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Multipath TCP
 *
 * Copyright (c) 2017 - 2019, Intel Corporation.
 */

#अगर_अघोषित __MPTCP_PROTOCOL_H
#घोषणा __MPTCP_PROTOCOL_H

#समावेश <linux/अक्रमom.h>
#समावेश <net/tcp.h>
#समावेश <net/inet_connection_sock.h>
#समावेश <uapi/linux/mptcp.h>

#घोषणा MPTCP_SUPPORTED_VERSION	1

/* MPTCP option bits */
#घोषणा OPTION_MPTCP_MPC_SYN	BIT(0)
#घोषणा OPTION_MPTCP_MPC_SYNACK	BIT(1)
#घोषणा OPTION_MPTCP_MPC_ACK	BIT(2)
#घोषणा OPTION_MPTCP_MPJ_SYN	BIT(3)
#घोषणा OPTION_MPTCP_MPJ_SYNACK	BIT(4)
#घोषणा OPTION_MPTCP_MPJ_ACK	BIT(5)
#घोषणा OPTION_MPTCP_ADD_ADDR	BIT(6)
#घोषणा OPTION_MPTCP_RM_ADDR	BIT(7)
#घोषणा OPTION_MPTCP_FASTCLOSE	BIT(8)
#घोषणा OPTION_MPTCP_PRIO	BIT(9)
#घोषणा OPTION_MPTCP_RST	BIT(10)

/* MPTCP option subtypes */
#घोषणा MPTCPOPT_MP_CAPABLE	0
#घोषणा MPTCPOPT_MP_JOIN	1
#घोषणा MPTCPOPT_DSS		2
#घोषणा MPTCPOPT_ADD_ADDR	3
#घोषणा MPTCPOPT_RM_ADDR	4
#घोषणा MPTCPOPT_MP_PRIO	5
#घोषणा MPTCPOPT_MP_FAIL	6
#घोषणा MPTCPOPT_MP_FASTCLOSE	7
#घोषणा MPTCPOPT_RST		8

/* MPTCP suboption lengths */
#घोषणा TCPOLEN_MPTCP_MPC_SYN		4
#घोषणा TCPOLEN_MPTCP_MPC_SYNACK	12
#घोषणा TCPOLEN_MPTCP_MPC_ACK		20
#घोषणा TCPOLEN_MPTCP_MPC_ACK_DATA	22
#घोषणा TCPOLEN_MPTCP_MPJ_SYN		12
#घोषणा TCPOLEN_MPTCP_MPJ_SYNACK	16
#घोषणा TCPOLEN_MPTCP_MPJ_ACK		24
#घोषणा TCPOLEN_MPTCP_DSS_BASE		4
#घोषणा TCPOLEN_MPTCP_DSS_ACK32		4
#घोषणा TCPOLEN_MPTCP_DSS_ACK64		8
#घोषणा TCPOLEN_MPTCP_DSS_MAP32		10
#घोषणा TCPOLEN_MPTCP_DSS_MAP64		14
#घोषणा TCPOLEN_MPTCP_DSS_CHECKSUM	2
#घोषणा TCPOLEN_MPTCP_ADD_ADDR		16
#घोषणा TCPOLEN_MPTCP_ADD_ADDR_PORT	18
#घोषणा TCPOLEN_MPTCP_ADD_ADDR_BASE	8
#घोषणा TCPOLEN_MPTCP_ADD_ADDR_BASE_PORT	10
#घोषणा TCPOLEN_MPTCP_ADD_ADDR6		28
#घोषणा TCPOLEN_MPTCP_ADD_ADDR6_PORT	30
#घोषणा TCPOLEN_MPTCP_ADD_ADDR6_BASE	20
#घोषणा TCPOLEN_MPTCP_ADD_ADDR6_BASE_PORT	22
#घोषणा TCPOLEN_MPTCP_PORT_LEN		2
#घोषणा TCPOLEN_MPTCP_PORT_ALIGN	2
#घोषणा TCPOLEN_MPTCP_RM_ADDR_BASE	3
#घोषणा TCPOLEN_MPTCP_PRIO		3
#घोषणा TCPOLEN_MPTCP_PRIO_ALIGN	4
#घोषणा TCPOLEN_MPTCP_FASTCLOSE		12
#घोषणा TCPOLEN_MPTCP_RST		4

/* MPTCP MP_JOIN flags */
#घोषणा MPTCPOPT_BACKUP		BIT(0)
#घोषणा MPTCPOPT_HMAC_LEN	20
#घोषणा MPTCPOPT_THMAC_LEN	8

/* MPTCP MP_CAPABLE flags */
#घोषणा MPTCP_VERSION_MASK	(0x0F)
#घोषणा MPTCP_CAP_CHECKSUM_REQD	BIT(7)
#घोषणा MPTCP_CAP_EXTENSIBILITY	BIT(6)
#घोषणा MPTCP_CAP_HMAC_SHA256	BIT(0)
#घोषणा MPTCP_CAP_FLAG_MASK	(0x3F)

/* MPTCP DSS flags */
#घोषणा MPTCP_DSS_DATA_FIN	BIT(4)
#घोषणा MPTCP_DSS_DSN64		BIT(3)
#घोषणा MPTCP_DSS_HAS_MAP	BIT(2)
#घोषणा MPTCP_DSS_ACK64		BIT(1)
#घोषणा MPTCP_DSS_HAS_ACK	BIT(0)
#घोषणा MPTCP_DSS_FLAG_MASK	(0x1F)

/* MPTCP ADD_ADDR flags */
#घोषणा MPTCP_ADDR_ECHO		BIT(0)

/* MPTCP MP_PRIO flags */
#घोषणा MPTCP_PRIO_BKUP		BIT(0)

/* MPTCP TCPRST flags */
#घोषणा MPTCP_RST_TRANSIENT	BIT(0)

/* MPTCP socket flags */
#घोषणा MPTCP_DATA_READY	0
#घोषणा MPTCP_NOSPACE		1
#घोषणा MPTCP_WORK_RTX		2
#घोषणा MPTCP_WORK_खातापूर्ण		3
#घोषणा MPTCP_FALLBACK_DONE	4
#घोषणा MPTCP_WORK_CLOSE_SUBFLOW 5
#घोषणा MPTCP_PUSH_PENDING	6
#घोषणा MPTCP_CLEAN_UNA		7
#घोषणा MPTCP_ERROR_REPORT	8
#घोषणा MPTCP_RETRANSMIT	9
#घोषणा MPTCP_WORK_SYNC_SETSOCKOPT 10

अटल अंतरभूत bool beक्रमe64(__u64 seq1, __u64 seq2)
अणु
	वापस (__s64)(seq1 - seq2) < 0;
पूर्ण

#घोषणा after64(seq2, seq1)	beक्रमe64(seq1, seq2)

काष्ठा mptcp_options_received अणु
	u64	sndr_key;
	u64	rcvr_key;
	u64	data_ack;
	u64	data_seq;
	u32	subflow_seq;
	u16	data_len;
	u16	mp_capable : 1,
		mp_join : 1,
		fastबंद : 1,
		reset : 1,
		dss : 1,
		add_addr : 1,
		rm_addr : 1,
		mp_prio : 1,
		echo : 1,
		backup : 1;
	u32	token;
	u32	nonce;
	u64	thmac;
	u8	hmac[MPTCPOPT_HMAC_LEN];
	u8	join_id;
	u8	use_map:1,
		dsn64:1,
		data_fin:1,
		use_ack:1,
		ack64:1,
		mpc_map:1,
		__unused:2;
	काष्ठा mptcp_addr_info addr;
	काष्ठा mptcp_rm_list rm_list;
	u64	ahmac;
	u8	reset_reason:4;
	u8	reset_transient:1;
पूर्ण;

अटल अंतरभूत __be32 mptcp_option(u8 subopt, u8 len, u8 nib, u8 field)
अणु
	वापस htonl((TCPOPT_MPTCP << 24) | (len << 16) | (subopt << 12) |
		     ((nib & 0xF) << 8) | field);
पूर्ण

क्रमागत mptcp_pm_status अणु
	MPTCP_PM_ADD_ADDR_RECEIVED,
	MPTCP_PM_ADD_ADDR_SEND_ACK,
	MPTCP_PM_RM_ADDR_RECEIVED,
	MPTCP_PM_ESTABLISHED,
	MPTCP_PM_ALREADY_ESTABLISHED,	/* persistent status, set after ESTABLISHED event */
	MPTCP_PM_SUBFLOW_ESTABLISHED,
पूर्ण;

क्रमागत mptcp_addr_संकेत_status अणु
	MPTCP_ADD_ADDR_SIGNAL,
	MPTCP_ADD_ADDR_ECHO,
	MPTCP_ADD_ADDR_IPV6,
	MPTCP_ADD_ADDR_PORT,
	MPTCP_RM_ADDR_SIGNAL,
पूर्ण;

काष्ठा mptcp_pm_data अणु
	काष्ठा mptcp_addr_info local;
	काष्ठा mptcp_addr_info remote;
	काष्ठा list_head anno_list;

	spinlock_t	lock;		/*protects the whole PM data */

	u8		addr_संकेत;
	bool		server_side;
	bool		work_pending;
	bool		accept_addr;
	bool		accept_subflow;
	u8		add_addr_संकेतed;
	u8		add_addr_accepted;
	u8		local_addr_used;
	u8		subflows;
	u8		status;
	काष्ठा mptcp_rm_list rm_list_tx;
	काष्ठा mptcp_rm_list rm_list_rx;
पूर्ण;

काष्ठा mptcp_data_frag अणु
	काष्ठा list_head list;
	u64 data_seq;
	u16 data_len;
	u16 offset;
	u16 overhead;
	u16 alपढ़ोy_sent;
	काष्ठा page *page;
पूर्ण;

/* MPTCP connection sock */
काष्ठा mptcp_sock अणु
	/* inet_connection_sock must be the first member */
	काष्ठा inet_connection_sock sk;
	u64		local_key;
	u64		remote_key;
	u64		ग_लिखो_seq;
	u64		snd_nxt;
	u64		ack_seq;
	u64		rcv_wnd_sent;
	u64		rcv_data_fin_seq;
	पूर्णांक		wmem_reserved;
	काष्ठा sock	*last_snd;
	पूर्णांक		snd_burst;
	पूर्णांक		old_wspace;
	u64		snd_una;
	u64		wnd_end;
	अचिन्हित दीर्घ	समयr_ival;
	u32		token;
	पूर्णांक		rmem_released;
	अचिन्हित दीर्घ	flags;
	bool		can_ack;
	bool		fully_established;
	bool		rcv_data_fin;
	bool		snd_data_fin_enable;
	bool		rcv_fastबंद;
	bool		use_64bit_ack; /* Set when we received a 64-bit DSN */
	spinlock_t	join_list_lock;
	काष्ठा sock	*ack_hपूर्णांक;
	काष्ठा work_काष्ठा work;
	काष्ठा sk_buff  *ooo_last_skb;
	काष्ठा rb_root  out_of_order_queue;
	काष्ठा sk_buff_head receive_queue;
	काष्ठा sk_buff_head skb_tx_cache;	/* this is wmem accounted */
	पूर्णांक		tx_pending_data;
	पूर्णांक		size_goal_cache;
	काष्ठा list_head conn_list;
	काष्ठा list_head rtx_queue;
	काष्ठा mptcp_data_frag *first_pending;
	काष्ठा list_head join_list;
	काष्ठा socket	*subflow; /* outgoing connect/listener/!mp_capable */
	काष्ठा sock	*first;
	काष्ठा mptcp_pm_data	pm;
	काष्ठा अणु
		u32	space;	/* bytes copied in last measurement winकरोw */
		u32	copied; /* bytes copied in this measurement winकरोw */
		u64	समय;	/* start समय of measurement winकरोw */
		u64	rtt_us; /* last maximum rtt of subflows */
	पूर्ण rcvq_space;

	u32 setsockopt_seq;
	अक्षर		ca_name[TCP_CA_NAME_MAX];
पूर्ण;

#घोषणा mptcp_lock_sock(___sk, cb) करो अणु					\
	काष्ठा sock *__sk = (___sk); /* silence macro reuse warning */	\
	might_sleep();							\
	spin_lock_bh(&__sk->sk_lock.slock);				\
	अगर (__sk->sk_lock.owned)					\
		__lock_sock(__sk);					\
	cb;								\
	__sk->sk_lock.owned = 1;					\
	spin_unlock(&__sk->sk_lock.slock);				\
	mutex_acquire(&__sk->sk_lock.dep_map, 0, 0, _RET_IP_);		\
	local_bh_enable();						\
पूर्ण जबतक (0)

#घोषणा mptcp_data_lock(sk) spin_lock_bh(&(sk)->sk_lock.slock)
#घोषणा mptcp_data_unlock(sk) spin_unlock_bh(&(sk)->sk_lock.slock)

#घोषणा mptcp_क्रम_each_subflow(__msk, __subflow)			\
	list_क्रम_each_entry(__subflow, &((__msk)->conn_list), node)

अटल अंतरभूत व्योम msk_owned_by_me(स्थिर काष्ठा mptcp_sock *msk)
अणु
	sock_owned_by_me((स्थिर काष्ठा sock *)msk);
पूर्ण

अटल अंतरभूत काष्ठा mptcp_sock *mptcp_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा mptcp_sock *)sk;
पूर्ण

अटल अंतरभूत पूर्णांक __mptcp_space(स्थिर काष्ठा sock *sk)
अणु
	वापस tcp_space(sk) + READ_ONCE(mptcp_sk(sk)->rmem_released);
पूर्ण

अटल अंतरभूत काष्ठा mptcp_data_frag *mptcp_send_head(स्थिर काष्ठा sock *sk)
अणु
	स्थिर काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	वापस READ_ONCE(msk->first_pending);
पूर्ण

अटल अंतरभूत काष्ठा mptcp_data_frag *mptcp_send_next(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	काष्ठा mptcp_data_frag *cur;

	cur = msk->first_pending;
	वापस list_is_last(&cur->list, &msk->rtx_queue) ? शून्य :
						     list_next_entry(cur, list);
पूर्ण

अटल अंतरभूत काष्ठा mptcp_data_frag *mptcp_pending_tail(स्थिर काष्ठा sock *sk)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	अगर (!msk->first_pending)
		वापस शून्य;

	अगर (WARN_ON_ONCE(list_empty(&msk->rtx_queue)))
		वापस शून्य;

	वापस list_last_entry(&msk->rtx_queue, काष्ठा mptcp_data_frag, list);
पूर्ण

अटल अंतरभूत काष्ठा mptcp_data_frag *mptcp_rtx_head(स्थिर काष्ठा sock *sk)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	अगर (msk->snd_una == READ_ONCE(msk->snd_nxt))
		वापस शून्य;

	वापस list_first_entry_or_null(&msk->rtx_queue, काष्ठा mptcp_data_frag, list);
पूर्ण

काष्ठा mptcp_subflow_request_sock अणु
	काष्ठा	tcp_request_sock sk;
	u16	mp_capable : 1,
		mp_join : 1,
		backup : 1;
	u8	local_id;
	u8	remote_id;
	u64	local_key;
	u64	idsn;
	u32	token;
	u32	ssn_offset;
	u64	thmac;
	u32	local_nonce;
	u32	remote_nonce;
	काष्ठा mptcp_sock	*msk;
	काष्ठा hlist_nulls_node token_node;
पूर्ण;

अटल अंतरभूत काष्ठा mptcp_subflow_request_sock *
mptcp_subflow_rsk(स्थिर काष्ठा request_sock *rsk)
अणु
	वापस (काष्ठा mptcp_subflow_request_sock *)rsk;
पूर्ण

क्रमागत mptcp_data_avail अणु
	MPTCP_SUBFLOW_NODATA,
	MPTCP_SUBFLOW_DATA_AVAIL,
पूर्ण;

काष्ठा mptcp_delegated_action अणु
	काष्ठा napi_काष्ठा napi;
	काष्ठा list_head head;
पूर्ण;

DECLARE_PER_CPU(काष्ठा mptcp_delegated_action, mptcp_delegated_actions);

#घोषणा MPTCP_DELEGATE_SEND		0

/* MPTCP subflow context */
काष्ठा mptcp_subflow_context अणु
	काष्ठा	list_head node;/* conn_list of subflows */
	u64	local_key;
	u64	remote_key;
	u64	idsn;
	u64	map_seq;
	u32	snd_isn;
	u32	token;
	u32	rel_ग_लिखो_seq;
	u32	map_subflow_seq;
	u32	ssn_offset;
	u32	map_data_len;
	u32	request_mptcp : 1,  /* send MP_CAPABLE */
		request_join : 1,   /* send MP_JOIN */
		request_bkup : 1,
		mp_capable : 1,	    /* remote is MPTCP capable */
		mp_join : 1,	    /* remote is JOINing */
		fully_established : 1,	    /* path validated */
		pm_notअगरied : 1,    /* PM hook called क्रम established status */
		conn_finished : 1,
		map_valid : 1,
		mpc_map : 1,
		backup : 1,
		send_mp_prio : 1,
		rx_eof : 1,
		can_ack : 1,        /* only after processing the remote a key */
		disposable : 1;	    /* ctx can be मुक्त at ulp release समय */
	क्रमागत mptcp_data_avail data_avail;
	u32	remote_nonce;
	u64	thmac;
	u32	local_nonce;
	u32	remote_token;
	u8	hmac[MPTCPOPT_HMAC_LEN];
	u8	local_id;
	u8	remote_id;
	u8	reset_seen:1;
	u8	reset_transient:1;
	u8	reset_reason:4;

	दीर्घ	delegated_status;
	काष्ठा	list_head delegated_node;   /* link पूर्णांकo delegated_action, रक्षित by local BH */

	u32 setsockopt_seq;

	काष्ठा	sock *tcp_sock;	    /* tcp sk backpoपूर्णांकer */
	काष्ठा	sock *conn;	    /* parent mptcp_sock */
	स्थिर	काष्ठा inet_connection_sock_af_ops *icsk_af_ops;
	व्योम	(*tcp_data_पढ़ोy)(काष्ठा sock *sk);
	व्योम	(*tcp_state_change)(काष्ठा sock *sk);
	व्योम	(*tcp_ग_लिखो_space)(काष्ठा sock *sk);
	व्योम	(*tcp_error_report)(काष्ठा sock *sk);

	काष्ठा	rcu_head rcu;
पूर्ण;

अटल अंतरभूत काष्ठा mptcp_subflow_context *
mptcp_subflow_ctx(स्थिर काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	/* Use RCU on icsk_ulp_data only क्रम sock diag code */
	वापस (__क्रमce काष्ठा mptcp_subflow_context *)icsk->icsk_ulp_data;
पूर्ण

अटल अंतरभूत काष्ठा sock *
mptcp_subflow_tcp_sock(स्थिर काष्ठा mptcp_subflow_context *subflow)
अणु
	वापस subflow->tcp_sock;
पूर्ण

अटल अंतरभूत u64
mptcp_subflow_get_map_offset(स्थिर काष्ठा mptcp_subflow_context *subflow)
अणु
	वापस tcp_sk(mptcp_subflow_tcp_sock(subflow))->copied_seq -
		      subflow->ssn_offset -
		      subflow->map_subflow_seq;
पूर्ण

अटल अंतरभूत u64
mptcp_subflow_get_mapped_dsn(स्थिर काष्ठा mptcp_subflow_context *subflow)
अणु
	वापस subflow->map_seq + mptcp_subflow_get_map_offset(subflow);
पूर्ण

अटल अंतरभूत व्योम mptcp_add_pending_subflow(काष्ठा mptcp_sock *msk,
					     काष्ठा mptcp_subflow_context *subflow)
अणु
	sock_hold(mptcp_subflow_tcp_sock(subflow));
	spin_lock_bh(&msk->join_list_lock);
	list_add_tail(&subflow->node, &msk->join_list);
	spin_unlock_bh(&msk->join_list_lock);
पूर्ण

व्योम mptcp_subflow_process_delegated(काष्ठा sock *ssk);

अटल अंतरभूत व्योम mptcp_subflow_delegate(काष्ठा mptcp_subflow_context *subflow)
अणु
	काष्ठा mptcp_delegated_action *delegated;
	bool schedule;

	/* The implied barrier pairs with mptcp_subflow_delegated_करोne(), and
	 * ensures the below list check sees list updates करोne prior to status
	 * bit changes
	 */
	अगर (!test_and_set_bit(MPTCP_DELEGATE_SEND, &subflow->delegated_status)) अणु
		/* still on delegated list from previous scheduling */
		अगर (!list_empty(&subflow->delegated_node))
			वापस;

		/* the caller held the subflow bh socket lock */
		lockdep_निश्चित_in_softirq();

		delegated = this_cpu_ptr(&mptcp_delegated_actions);
		schedule = list_empty(&delegated->head);
		list_add_tail(&subflow->delegated_node, &delegated->head);
		sock_hold(mptcp_subflow_tcp_sock(subflow));
		अगर (schedule)
			napi_schedule(&delegated->napi);
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा mptcp_subflow_context *
mptcp_subflow_delegated_next(काष्ठा mptcp_delegated_action *delegated)
अणु
	काष्ठा mptcp_subflow_context *ret;

	अगर (list_empty(&delegated->head))
		वापस शून्य;

	ret = list_first_entry(&delegated->head, काष्ठा mptcp_subflow_context, delegated_node);
	list_del_init(&ret->delegated_node);
	वापस ret;
पूर्ण

अटल अंतरभूत bool mptcp_subflow_has_delegated_action(स्थिर काष्ठा mptcp_subflow_context *subflow)
अणु
	वापस test_bit(MPTCP_DELEGATE_SEND, &subflow->delegated_status);
पूर्ण

अटल अंतरभूत व्योम mptcp_subflow_delegated_करोne(काष्ठा mptcp_subflow_context *subflow)
अणु
	/* pairs with mptcp_subflow_delegate, ensures delegate_node is updated beक्रमe
	 * touching the status bit
	 */
	smp_wmb();
	clear_bit(MPTCP_DELEGATE_SEND, &subflow->delegated_status);
पूर्ण

पूर्णांक mptcp_is_enabled(काष्ठा net *net);
अचिन्हित पूर्णांक mptcp_get_add_addr_समयout(काष्ठा net *net);
व्योम mptcp_subflow_fully_established(काष्ठा mptcp_subflow_context *subflow,
				     काष्ठा mptcp_options_received *mp_opt);
bool mptcp_subflow_data_available(काष्ठा sock *sk);
व्योम __init mptcp_subflow_init(व्योम);
व्योम mptcp_subflow_shutकरोwn(काष्ठा sock *sk, काष्ठा sock *ssk, पूर्णांक how);
व्योम mptcp_बंद_ssk(काष्ठा sock *sk, काष्ठा sock *ssk,
		     काष्ठा mptcp_subflow_context *subflow);
व्योम mptcp_subflow_reset(काष्ठा sock *ssk);
व्योम mptcp_sock_graft(काष्ठा sock *sk, काष्ठा socket *parent);
काष्ठा socket *__mptcp_nmpc_socket(स्थिर काष्ठा mptcp_sock *msk);

/* called with sk socket lock held */
पूर्णांक __mptcp_subflow_connect(काष्ठा sock *sk, स्थिर काष्ठा mptcp_addr_info *loc,
			    स्थिर काष्ठा mptcp_addr_info *remote,
			    u8 flags, पूर्णांक अगरindex);
पूर्णांक mptcp_subflow_create_socket(काष्ठा sock *sk, काष्ठा socket **new_sock);
व्योम mptcp_info2sockaddr(स्थिर काष्ठा mptcp_addr_info *info,
			 काष्ठा sockaddr_storage *addr,
			 अचिन्हित लघु family);

अटल अंतरभूत bool mptcp_subflow_active(काष्ठा mptcp_subflow_context *subflow)
अणु
	काष्ठा sock *ssk = mptcp_subflow_tcp_sock(subflow);

	/* can't send if JOIN hasn't completed yet (i.e. is usable क्रम mptcp) */
	अगर (subflow->request_join && !subflow->fully_established)
		वापस false;

	/* only send अगर our side has not बंदd yet */
	वापस ((1 << ssk->sk_state) & (TCPF_ESTABLISHED | TCPF_CLOSE_WAIT));
पूर्ण

अटल अंतरभूत व्योम mptcp_subflow_tcp_fallback(काष्ठा sock *sk,
					      काष्ठा mptcp_subflow_context *ctx)
अणु
	sk->sk_data_पढ़ोy = ctx->tcp_data_पढ़ोy;
	sk->sk_state_change = ctx->tcp_state_change;
	sk->sk_ग_लिखो_space = ctx->tcp_ग_लिखो_space;
	sk->sk_error_report = ctx->tcp_error_report;

	inet_csk(sk)->icsk_af_ops = ctx->icsk_af_ops;
पूर्ण

व्योम __init mptcp_proto_init(व्योम);
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
पूर्णांक __init mptcp_proto_v6_init(व्योम);
#पूर्ण_अगर

काष्ठा sock *mptcp_sk_clone(स्थिर काष्ठा sock *sk,
			    स्थिर काष्ठा mptcp_options_received *mp_opt,
			    काष्ठा request_sock *req);
व्योम mptcp_get_options(स्थिर काष्ठा sk_buff *skb,
		       काष्ठा mptcp_options_received *mp_opt);

व्योम mptcp_finish_connect(काष्ठा sock *sk);
अटल अंतरभूत bool mptcp_is_fully_established(काष्ठा sock *sk)
अणु
	वापस inet_sk_state_load(sk) == TCP_ESTABLISHED &&
	       READ_ONCE(mptcp_sk(sk)->fully_established);
पूर्ण
व्योम mptcp_rcv_space_init(काष्ठा mptcp_sock *msk, स्थिर काष्ठा sock *ssk);
व्योम mptcp_data_पढ़ोy(काष्ठा sock *sk, काष्ठा sock *ssk);
bool mptcp_finish_join(काष्ठा sock *sk);
bool mptcp_schedule_work(काष्ठा sock *sk);
पूर्णांक mptcp_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		     sockptr_t optval, अचिन्हित पूर्णांक optlen);
पूर्णांक mptcp_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		     अक्षर __user *optval, पूर्णांक __user *option);

व्योम __mptcp_check_push(काष्ठा sock *sk, काष्ठा sock *ssk);
व्योम __mptcp_data_acked(काष्ठा sock *sk);
व्योम __mptcp_error_report(काष्ठा sock *sk);
व्योम mptcp_subflow_eof(काष्ठा sock *sk);
bool mptcp_update_rcv_data_fin(काष्ठा mptcp_sock *msk, u64 data_fin_seq, bool use_64bit);
व्योम __mptcp_flush_join_list(काष्ठा mptcp_sock *msk);
अटल अंतरभूत bool mptcp_data_fin_enabled(स्थिर काष्ठा mptcp_sock *msk)
अणु
	वापस READ_ONCE(msk->snd_data_fin_enable) &&
	       READ_ONCE(msk->ग_लिखो_seq) == READ_ONCE(msk->snd_nxt);
पूर्ण

अटल अंतरभूत bool mptcp_propagate_sndbuf(काष्ठा sock *sk, काष्ठा sock *ssk)
अणु
	अगर ((sk->sk_userlocks & SOCK_SNDBUF_LOCK) || ssk->sk_sndbuf <= READ_ONCE(sk->sk_sndbuf))
		वापस false;

	WRITE_ONCE(sk->sk_sndbuf, ssk->sk_sndbuf);
	वापस true;
पूर्ण

अटल अंतरभूत व्योम mptcp_ग_लिखो_space(काष्ठा sock *sk)
अणु
	अगर (sk_stream_is_ग_लिखोable(sk)) अणु
		/* pairs with memory barrier in mptcp_poll */
		smp_mb();
		अगर (test_and_clear_bit(MPTCP_NOSPACE, &mptcp_sk(sk)->flags))
			sk_stream_ग_लिखो_space(sk);
	पूर्ण
पूर्ण

व्योम mptcp_destroy_common(काष्ठा mptcp_sock *msk);

व्योम __init mptcp_token_init(व्योम);
अटल अंतरभूत व्योम mptcp_token_init_request(काष्ठा request_sock *req)
अणु
	mptcp_subflow_rsk(req)->token_node.pprev = शून्य;
पूर्ण

पूर्णांक mptcp_token_new_request(काष्ठा request_sock *req);
व्योम mptcp_token_destroy_request(काष्ठा request_sock *req);
पूर्णांक mptcp_token_new_connect(काष्ठा sock *sk);
व्योम mptcp_token_accept(काष्ठा mptcp_subflow_request_sock *r,
			काष्ठा mptcp_sock *msk);
bool mptcp_token_exists(u32 token);
काष्ठा mptcp_sock *mptcp_token_get_sock(u32 token);
काष्ठा mptcp_sock *mptcp_token_iter_next(स्थिर काष्ठा net *net, दीर्घ *s_slot,
					 दीर्घ *s_num);
व्योम mptcp_token_destroy(काष्ठा mptcp_sock *msk);

व्योम mptcp_crypto_key_sha(u64 key, u32 *token, u64 *idsn);

व्योम mptcp_crypto_hmac_sha(u64 key1, u64 key2, u8 *msg, पूर्णांक len, व्योम *hmac);

व्योम __init mptcp_pm_init(व्योम);
व्योम mptcp_pm_data_init(काष्ठा mptcp_sock *msk);
व्योम mptcp_pm_new_connection(काष्ठा mptcp_sock *msk, स्थिर काष्ठा sock *ssk, पूर्णांक server_side);
व्योम mptcp_pm_fully_established(काष्ठा mptcp_sock *msk, स्थिर काष्ठा sock *ssk, gfp_t gfp);
bool mptcp_pm_allow_new_subflow(काष्ठा mptcp_sock *msk);
व्योम mptcp_pm_connection_बंदd(काष्ठा mptcp_sock *msk);
व्योम mptcp_pm_subflow_established(काष्ठा mptcp_sock *msk);
व्योम mptcp_pm_subflow_बंदd(काष्ठा mptcp_sock *msk, u8 id);
व्योम mptcp_pm_add_addr_received(काष्ठा mptcp_sock *msk,
				स्थिर काष्ठा mptcp_addr_info *addr);
व्योम mptcp_pm_add_addr_echoed(काष्ठा mptcp_sock *msk,
			      काष्ठा mptcp_addr_info *addr);
व्योम mptcp_pm_add_addr_send_ack(काष्ठा mptcp_sock *msk);
व्योम mptcp_pm_nl_addr_send_ack(काष्ठा mptcp_sock *msk);
व्योम mptcp_pm_rm_addr_received(काष्ठा mptcp_sock *msk,
			       स्थिर काष्ठा mptcp_rm_list *rm_list);
व्योम mptcp_pm_mp_prio_received(काष्ठा sock *sk, u8 bkup);
पूर्णांक mptcp_pm_nl_mp_prio_send_ack(काष्ठा mptcp_sock *msk,
				 काष्ठा mptcp_addr_info *addr,
				 u8 bkup);
व्योम mptcp_pm_मुक्त_anno_list(काष्ठा mptcp_sock *msk);
bool mptcp_pm_sport_in_anno_list(काष्ठा mptcp_sock *msk, स्थिर काष्ठा sock *sk);
काष्ठा mptcp_pm_add_entry *
mptcp_pm_del_add_समयr(काष्ठा mptcp_sock *msk,
		       काष्ठा mptcp_addr_info *addr, bool check_id);
काष्ठा mptcp_pm_add_entry *
mptcp_lookup_anno_list_by_saddr(काष्ठा mptcp_sock *msk,
				काष्ठा mptcp_addr_info *addr);

पूर्णांक mptcp_pm_announce_addr(काष्ठा mptcp_sock *msk,
			   स्थिर काष्ठा mptcp_addr_info *addr,
			   bool echo);
पूर्णांक mptcp_pm_हटाओ_addr(काष्ठा mptcp_sock *msk, स्थिर काष्ठा mptcp_rm_list *rm_list);
पूर्णांक mptcp_pm_हटाओ_subflow(काष्ठा mptcp_sock *msk, स्थिर काष्ठा mptcp_rm_list *rm_list);

व्योम mptcp_event(क्रमागत mptcp_event_type type, स्थिर काष्ठा mptcp_sock *msk,
		 स्थिर काष्ठा sock *ssk, gfp_t gfp);
व्योम mptcp_event_addr_announced(स्थिर काष्ठा mptcp_sock *msk, स्थिर काष्ठा mptcp_addr_info *info);
व्योम mptcp_event_addr_हटाओd(स्थिर काष्ठा mptcp_sock *msk, u8 id);

अटल अंतरभूत bool mptcp_pm_should_add_संकेत(काष्ठा mptcp_sock *msk)
अणु
	वापस READ_ONCE(msk->pm.addr_संकेत) & BIT(MPTCP_ADD_ADDR_SIGNAL);
पूर्ण

अटल अंतरभूत bool mptcp_pm_should_add_संकेत_echo(काष्ठा mptcp_sock *msk)
अणु
	वापस READ_ONCE(msk->pm.addr_संकेत) & BIT(MPTCP_ADD_ADDR_ECHO);
पूर्ण

अटल अंतरभूत bool mptcp_pm_should_add_संकेत_ipv6(काष्ठा mptcp_sock *msk)
अणु
	वापस READ_ONCE(msk->pm.addr_संकेत) & BIT(MPTCP_ADD_ADDR_IPV6);
पूर्ण

अटल अंतरभूत bool mptcp_pm_should_add_संकेत_port(काष्ठा mptcp_sock *msk)
अणु
	वापस READ_ONCE(msk->pm.addr_संकेत) & BIT(MPTCP_ADD_ADDR_PORT);
पूर्ण

अटल अंतरभूत bool mptcp_pm_should_rm_संकेत(काष्ठा mptcp_sock *msk)
अणु
	वापस READ_ONCE(msk->pm.addr_संकेत) & BIT(MPTCP_RM_ADDR_SIGNAL);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mptcp_add_addr_len(पूर्णांक family, bool echo, bool port)
अणु
	u8 len = TCPOLEN_MPTCP_ADD_ADDR_BASE;

	अगर (family == AF_INET6)
		len = TCPOLEN_MPTCP_ADD_ADDR6_BASE;
	अगर (!echo)
		len += MPTCPOPT_THMAC_LEN;
	/* account क्रम 2 trailing 'nop' options */
	अगर (port)
		len += TCPOLEN_MPTCP_PORT_LEN + TCPOLEN_MPTCP_PORT_ALIGN;

	वापस len;
पूर्ण

अटल अंतरभूत पूर्णांक mptcp_rm_addr_len(स्थिर काष्ठा mptcp_rm_list *rm_list)
अणु
	अगर (rm_list->nr == 0 || rm_list->nr > MPTCP_RM_IDS_MAX)
		वापस -EINVAL;

	वापस TCPOLEN_MPTCP_RM_ADDR_BASE + roundup(rm_list->nr - 1, 4) + 1;
पूर्ण

bool mptcp_pm_add_addr_संकेत(काष्ठा mptcp_sock *msk, अचिन्हित पूर्णांक reमुख्यing,
			      काष्ठा mptcp_addr_info *saddr, bool *echo, bool *port);
bool mptcp_pm_rm_addr_संकेत(काष्ठा mptcp_sock *msk, अचिन्हित पूर्णांक reमुख्यing,
			     काष्ठा mptcp_rm_list *rm_list);
पूर्णांक mptcp_pm_get_local_id(काष्ठा mptcp_sock *msk, काष्ठा sock_common *skc);

व्योम __init mptcp_pm_nl_init(व्योम);
व्योम mptcp_pm_nl_data_init(काष्ठा mptcp_sock *msk);
व्योम mptcp_pm_nl_work(काष्ठा mptcp_sock *msk);
व्योम mptcp_pm_nl_rm_subflow_received(काष्ठा mptcp_sock *msk,
				     स्थिर काष्ठा mptcp_rm_list *rm_list);
पूर्णांक mptcp_pm_nl_get_local_id(काष्ठा mptcp_sock *msk, काष्ठा sock_common *skc);
अचिन्हित पूर्णांक mptcp_pm_get_add_addr_संकेत_max(काष्ठा mptcp_sock *msk);
अचिन्हित पूर्णांक mptcp_pm_get_add_addr_accept_max(काष्ठा mptcp_sock *msk);
अचिन्हित पूर्णांक mptcp_pm_get_subflows_max(काष्ठा mptcp_sock *msk);
अचिन्हित पूर्णांक mptcp_pm_get_local_addr_max(काष्ठा mptcp_sock *msk);

पूर्णांक mptcp_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		     sockptr_t optval, अचिन्हित पूर्णांक optlen);

व्योम mptcp_sockopt_sync(काष्ठा mptcp_sock *msk, काष्ठा sock *ssk);
व्योम mptcp_sockopt_sync_all(काष्ठा mptcp_sock *msk);

अटल अंतरभूत काष्ठा mptcp_ext *mptcp_get_ext(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा mptcp_ext *)skb_ext_find(skb, SKB_EXT_MPTCP);
पूर्ण

व्योम mptcp_diag_subflow_init(काष्ठा tcp_ulp_ops *ops);

अटल अंतरभूत bool __mptcp_check_fallback(स्थिर काष्ठा mptcp_sock *msk)
अणु
	वापस test_bit(MPTCP_FALLBACK_DONE, &msk->flags);
पूर्ण

अटल अंतरभूत bool mptcp_check_fallback(स्थिर काष्ठा sock *sk)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(sk);
	काष्ठा mptcp_sock *msk = mptcp_sk(subflow->conn);

	वापस __mptcp_check_fallback(msk);
पूर्ण

अटल अंतरभूत व्योम __mptcp_करो_fallback(काष्ठा mptcp_sock *msk)
अणु
	अगर (test_bit(MPTCP_FALLBACK_DONE, &msk->flags)) अणु
		pr_debug("TCP fallback already done (msk=%p)", msk);
		वापस;
	पूर्ण
	set_bit(MPTCP_FALLBACK_DONE, &msk->flags);
पूर्ण

अटल अंतरभूत व्योम mptcp_करो_fallback(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(sk);
	काष्ठा mptcp_sock *msk = mptcp_sk(subflow->conn);

	__mptcp_करो_fallback(msk);
पूर्ण

#घोषणा pr_fallback(a) pr_debug("%s:fallback to TCP (msk=%p)", __func__, a)

अटल अंतरभूत bool subflow_simultaneous_connect(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(sk);
	काष्ठा sock *parent = subflow->conn;

	वापस sk->sk_state == TCP_ESTABLISHED &&
	       !mptcp_sk(parent)->pm.server_side &&
	       !subflow->conn_finished;
पूर्ण

#अगर_घोषित CONFIG_SYN_COOKIES
व्योम subflow_init_req_cookie_join_save(स्थिर काष्ठा mptcp_subflow_request_sock *subflow_req,
				       काष्ठा sk_buff *skb);
bool mptcp_token_join_cookie_init_state(काष्ठा mptcp_subflow_request_sock *subflow_req,
					काष्ठा sk_buff *skb);
व्योम __init mptcp_join_cookie_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम
subflow_init_req_cookie_join_save(स्थिर काष्ठा mptcp_subflow_request_sock *subflow_req,
				  काष्ठा sk_buff *skb) अणुपूर्ण
अटल अंतरभूत bool
mptcp_token_join_cookie_init_state(काष्ठा mptcp_subflow_request_sock *subflow_req,
				   काष्ठा sk_buff *skb)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम mptcp_join_cookie_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __MPTCP_PROTOCOL_H */
