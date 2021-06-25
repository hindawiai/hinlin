<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  linux/include/linux/sunrpc/xprt.h
 *
 *  Declarations क्रम the RPC transport पूर्णांकerface.
 *
 *  Copyright (C) 1995, 1996 Olaf Kirch <okir@monad.swb.de>
 */

#अगर_अघोषित _LINUX_SUNRPC_XPRT_H
#घोषणा _LINUX_SUNRPC_XPRT_H

#समावेश <linux/uपन.स>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/kref.h>
#समावेश <linux/sunrpc/sched.h>
#समावेश <linux/sunrpc/xdr.h>
#समावेश <linux/sunrpc/msg_prot.h>

#घोषणा RPC_MIN_SLOT_TABLE	(2U)
#घोषणा RPC_DEF_SLOT_TABLE	(16U)
#घोषणा RPC_MAX_SLOT_TABLE_LIMIT	(65536U)
#घोषणा RPC_MAX_SLOT_TABLE	RPC_MAX_SLOT_TABLE_LIMIT

#घोषणा RPC_CWNDSHIFT		(8U)
#घोषणा RPC_CWNDSCALE		(1U << RPC_CWNDSHIFT)
#घोषणा RPC_INITCWND		RPC_CWNDSCALE
#घोषणा RPC_MAXCWND(xprt)	((xprt)->max_reqs << RPC_CWNDSHIFT)
#घोषणा RPCXPRT_CONGESTED(xprt) ((xprt)->cong >= (xprt)->cwnd)

/*
 * This describes a समयout strategy
 */
काष्ठा rpc_समयout अणु
	अचिन्हित दीर्घ		to_initval,		/* initial समयout */
				to_maxval,		/* max समयout */
				to_increment;		/* अगर !exponential */
	अचिन्हित पूर्णांक		to_retries;		/* max # of retries */
	अचिन्हित अक्षर		to_exponential;
पूर्ण;

क्रमागत rpc_display_क्रमmat_t अणु
	RPC_DISPLAY_ADDR = 0,
	RPC_DISPLAY_PORT,
	RPC_DISPLAY_PROTO,
	RPC_DISPLAY_HEX_ADDR,
	RPC_DISPLAY_HEX_PORT,
	RPC_DISPLAY_NETID,
	RPC_DISPLAY_MAX,
पूर्ण;

काष्ठा rpc_task;
काष्ठा rpc_xprt;
काष्ठा seq_file;
काष्ठा svc_serv;
काष्ठा net;

/*
 * This describes a complete RPC request
 */
काष्ठा rpc_rqst अणु
	/*
	 * This is the user-visible part
	 */
	काष्ठा rpc_xprt *	rq_xprt;		/* RPC client */
	काष्ठा xdr_buf		rq_snd_buf;		/* send buffer */
	काष्ठा xdr_buf		rq_rcv_buf;		/* recv buffer */

	/*
	 * This is the निजी part
	 */
	काष्ठा rpc_task *	rq_task;	/* RPC task data */
	काष्ठा rpc_cred *	rq_cred;	/* Bound cred */
	__be32			rq_xid;		/* request XID */
	पूर्णांक			rq_cong;	/* has incremented xprt->cong */
	u32			rq_seqno;	/* gss seq no. used on req. */
	पूर्णांक			rq_enc_pages_num;
	काष्ठा page		**rq_enc_pages;	/* scratch pages क्रम use by
						   gss privacy code */
	व्योम (*rq_release_snd_buf)(काष्ठा rpc_rqst *); /* release rq_enc_pages */

	जोड़ अणु
		काष्ठा list_head	rq_list;	/* Slot allocation list */
		काष्ठा rb_node		rq_recv;	/* Receive queue */
	पूर्ण;

	काष्ठा list_head	rq_xmit;	/* Send queue */
	काष्ठा list_head	rq_xmit2;	/* Send queue */

	व्योम			*rq_buffer;	/* Call XDR encode buffer */
	माप_प्रकार			rq_callsize;
	व्योम			*rq_rbuffer;	/* Reply XDR decode buffer */
	माप_प्रकार			rq_rcvsize;
	माप_प्रकार			rq_xmit_bytes_sent;	/* total bytes sent */
	माप_प्रकार			rq_reply_bytes_recvd;	/* total reply bytes */
							/* received */

	काष्ठा xdr_buf		rq_निजी_buf;		/* The receive buffer
							 * used in the softirq.
							 */
	अचिन्हित दीर्घ		rq_majorसमयo;	/* major समयout alarm */
	अचिन्हित दीर्घ		rq_minorसमयo;	/* minor समयout alarm */
	अचिन्हित दीर्घ		rq_समयout;	/* Current समयout value */
	kसमय_प्रकार			rq_rtt;		/* round-trip समय */
	अचिन्हित पूर्णांक		rq_retries;	/* # of retries */
	अचिन्हित पूर्णांक		rq_connect_cookie;
						/* A cookie used to track the
						   state of the transport
						   connection */
	atomic_t		rq_pin;
	
	/*
	 * Partial send handling
	 */
	u32			rq_bytes_sent;	/* Bytes we have sent */

	kसमय_प्रकार			rq_xसमय;	/* transmit समय stamp */
	पूर्णांक			rq_ntrans;

#अगर defined(CONFIG_SUNRPC_BACKCHANNEL)
	काष्ठा list_head	rq_bc_list;	/* Callback service list */
	अचिन्हित दीर्घ		rq_bc_pa_state;	/* Backchannel pपुनः_स्मृति state */
	काष्ठा list_head	rq_bc_pa_list;	/* Backchannel pपुनः_स्मृति list */
#पूर्ण_अगर /* CONFIG_SUNRPC_BACKCHANEL */
पूर्ण;
#घोषणा rq_svec			rq_snd_buf.head
#घोषणा rq_slen			rq_snd_buf.len

काष्ठा rpc_xprt_ops अणु
	व्योम		(*set_buffer_size)(काष्ठा rpc_xprt *xprt, माप_प्रकार sndsize, माप_प्रकार rcvsize);
	पूर्णांक		(*reserve_xprt)(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task);
	व्योम		(*release_xprt)(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task);
	व्योम		(*alloc_slot)(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task);
	व्योम		(*मुक्त_slot)(काष्ठा rpc_xprt *xprt,
				     काष्ठा rpc_rqst *req);
	व्योम		(*rpcbind)(काष्ठा rpc_task *task);
	व्योम		(*set_port)(काष्ठा rpc_xprt *xprt, अचिन्हित लघु port);
	व्योम		(*connect)(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task);
	पूर्णांक		(*buf_alloc)(काष्ठा rpc_task *task);
	व्योम		(*buf_मुक्त)(काष्ठा rpc_task *task);
	व्योम		(*prepare_request)(काष्ठा rpc_rqst *req);
	पूर्णांक		(*send_request)(काष्ठा rpc_rqst *req);
	व्योम		(*रुको_क्रम_reply_request)(काष्ठा rpc_task *task);
	व्योम		(*समयr)(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task);
	व्योम		(*release_request)(काष्ठा rpc_task *task);
	व्योम		(*बंद)(काष्ठा rpc_xprt *xprt);
	व्योम		(*destroy)(काष्ठा rpc_xprt *xprt);
	व्योम		(*set_connect_समयout)(काष्ठा rpc_xprt *xprt,
					अचिन्हित दीर्घ connect_समयout,
					अचिन्हित दीर्घ reconnect_समयout);
	व्योम		(*prपूर्णांक_stats)(काष्ठा rpc_xprt *xprt, काष्ठा seq_file *seq);
	पूर्णांक		(*enable_swap)(काष्ठा rpc_xprt *xprt);
	व्योम		(*disable_swap)(काष्ठा rpc_xprt *xprt);
	व्योम		(*inject_disconnect)(काष्ठा rpc_xprt *xprt);
	पूर्णांक		(*bc_setup)(काष्ठा rpc_xprt *xprt,
				    अचिन्हित पूर्णांक min_reqs);
	माप_प्रकार		(*bc_maxpayload)(काष्ठा rpc_xprt *xprt);
	अचिन्हित पूर्णांक	(*bc_num_slots)(काष्ठा rpc_xprt *xprt);
	व्योम		(*bc_मुक्त_rqst)(काष्ठा rpc_rqst *rqst);
	व्योम		(*bc_destroy)(काष्ठा rpc_xprt *xprt,
				      अचिन्हित पूर्णांक max_reqs);
पूर्ण;

/*
 * RPC transport identअगरiers
 *
 * To preserve compatibility with the historical use of raw IP protocol
 * id's क्रम transport selection, UDP and TCP identअगरiers are specअगरied
 * with the previous values. No such restriction exists क्रम new transports,
 * except that they may not collide with these values (17 and 6,
 * respectively).
 */
#घोषणा XPRT_TRANSPORT_BC       (1 << 31)
क्रमागत xprt_transports अणु
	XPRT_TRANSPORT_UDP	= IPPROTO_UDP,
	XPRT_TRANSPORT_TCP	= IPPROTO_TCP,
	XPRT_TRANSPORT_BC_TCP	= IPPROTO_TCP | XPRT_TRANSPORT_BC,
	XPRT_TRANSPORT_RDMA	= 256,
	XPRT_TRANSPORT_BC_RDMA	= XPRT_TRANSPORT_RDMA | XPRT_TRANSPORT_BC,
	XPRT_TRANSPORT_LOCAL	= 257,
पूर्ण;

काष्ठा rpc_xprt अणु
	काष्ठा kref		kref;		/* Reference count */
	स्थिर काष्ठा rpc_xprt_ops *ops;		/* transport methods */

	स्थिर काष्ठा rpc_समयout *समयout;	/* समयout parms */
	काष्ठा sockaddr_storage	addr;		/* server address */
	माप_प्रकार			addrlen;	/* size of server address */
	पूर्णांक			prot;		/* IP protocol */

	अचिन्हित दीर्घ		cong;		/* current congestion */
	अचिन्हित दीर्घ		cwnd;		/* congestion winकरोw */

	माप_प्रकार			max_payload;	/* largest RPC payload size,
						   in bytes */

	काष्ठा rpc_रुको_queue	binding;	/* requests रुकोing on rpcbind */
	काष्ठा rpc_रुको_queue	sending;	/* requests रुकोing to send */
	काष्ठा rpc_रुको_queue	pending;	/* requests in flight */
	काष्ठा rpc_रुको_queue	backlog;	/* रुकोing क्रम slot */
	काष्ठा list_head	मुक्त;		/* मुक्त slots */
	अचिन्हित पूर्णांक		max_reqs;	/* max number of slots */
	अचिन्हित पूर्णांक		min_reqs;	/* min number of slots */
	अचिन्हित पूर्णांक		num_reqs;	/* total slots */
	अचिन्हित दीर्घ		state;		/* transport state */
	अचिन्हित अक्षर		resvport   : 1,	/* use a reserved port */
				reuseport  : 1; /* reuse port on reconnect */
	atomic_t		swapper;	/* we're swapping over this
						   transport */
	अचिन्हित पूर्णांक		bind_index;	/* bind function index */

	/*
	 * Multipath
	 */
	काष्ठा list_head	xprt_चयन;

	/*
	 * Connection of transports
	 */
	अचिन्हित दीर्घ		bind_समयout,
				reestablish_समयout;
	अचिन्हित पूर्णांक		connect_cookie;	/* A cookie that माला_लो bumped
						   every समय the transport
						   is reconnected */

	/*
	 * Disconnection of idle transports
	 */
	काष्ठा work_काष्ठा	task_cleanup;
	काष्ठा समयr_list	समयr;
	अचिन्हित दीर्घ		last_used,
				idle_समयout,
				connect_समयout,
				max_reconnect_समयout;

	/*
	 * Send stuff
	 */
	atomic_दीर्घ_t		queuelen;
	spinlock_t		transport_lock;	/* lock transport info */
	spinlock_t		reserve_lock;	/* lock slot table */
	spinlock_t		queue_lock;	/* send/receive queue lock */
	u32			xid;		/* Next XID value to use */
	काष्ठा rpc_task *	snd_task;	/* Task blocked in send */

	काष्ठा list_head	xmit_queue;	/* Send queue */
	atomic_दीर्घ_t		xmit_queuelen;

	काष्ठा svc_xprt		*bc_xprt;	/* NFSv4.1 backchannel */
#अगर defined(CONFIG_SUNRPC_BACKCHANNEL)
	काष्ठा svc_serv		*bc_serv;       /* The RPC service which will */
						/* process the callback */
	अचिन्हित पूर्णांक		bc_alloc_max;
	अचिन्हित पूर्णांक		bc_alloc_count;	/* Total number of pपुनः_स्मृतिs */
	atomic_t		bc_slot_count;	/* Number of allocated slots */
	spinlock_t		bc_pa_lock;	/* Protects the pपुनः_स्मृतिated
						 * items */
	काष्ठा list_head	bc_pa_list;	/* List of pपुनः_स्मृतिated
						 * backchannel rpc_rqst's */
#पूर्ण_अगर /* CONFIG_SUNRPC_BACKCHANNEL */

	काष्ठा rb_root		recv_queue;	/* Receive queue */

	काष्ठा अणु
		अचिन्हित दीर्घ		bind_count,	/* total number of binds */
					connect_count,	/* total number of connects */
					connect_start,	/* connect start बारtamp */
					connect_समय,	/* jअगरfies रुकोing क्रम connect */
					sends,		/* how many complete requests */
					recvs,		/* how many complete requests */
					bad_xids,	/* lookup_rqst didn't find XID */
					max_slots;	/* max rpc_slots used */

		अचिन्हित दीर्घ दीर्घ	req_u,		/* average requests on the wire */
					bklog_u,	/* backlog queue utilization */
					sending_u,	/* send q utilization */
					pending_u;	/* pend q utilization */
	पूर्ण stat;

	काष्ठा net		*xprt_net;
	स्थिर अक्षर		*servername;
	स्थिर अक्षर		*address_strings[RPC_DISPLAY_MAX];
#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
	काष्ठा dentry		*debugfs;		/* debugfs directory */
	atomic_t		inject_disconnect;
#पूर्ण_अगर
	काष्ठा rcu_head		rcu;
पूर्ण;

#अगर defined(CONFIG_SUNRPC_BACKCHANNEL)
/*
 * Backchannel flags
 */
#घोषणा	RPC_BC_PA_IN_USE	0x0001		/* Pपुनः_स्मृतिated backchannel */
						/* buffer in use */
#पूर्ण_अगर /* CONFIG_SUNRPC_BACKCHANNEL */

#अगर defined(CONFIG_SUNRPC_BACKCHANNEL)
अटल अंतरभूत पूर्णांक bc_pपुनः_स्मृति(काष्ठा rpc_rqst *req)
अणु
	वापस test_bit(RPC_BC_PA_IN_USE, &req->rq_bc_pa_state);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक bc_pपुनः_स्मृति(काष्ठा rpc_rqst *req)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SUNRPC_BACKCHANNEL */

#घोषणा XPRT_CREATE_INFINITE_SLOTS	(1U)
#घोषणा XPRT_CREATE_NO_IDLE_TIMEOUT	(1U << 1)

काष्ठा xprt_create अणु
	पूर्णांक			ident;		/* XPRT_TRANSPORT identअगरier */
	काष्ठा net *		net;
	काष्ठा sockaddr *	srcaddr;	/* optional local address */
	काष्ठा sockaddr *	dstaddr;	/* remote peer address */
	माप_प्रकार			addrlen;
	स्थिर अक्षर		*servername;
	काष्ठा svc_xprt		*bc_xprt;	/* NFSv4.1 backchannel */
	काष्ठा rpc_xprt_चयन	*bc_xps;
	अचिन्हित पूर्णांक		flags;
पूर्ण;

काष्ठा xprt_class अणु
	काष्ठा list_head	list;
	पूर्णांक			ident;		/* XPRT_TRANSPORT identअगरier */
	काष्ठा rpc_xprt *	(*setup)(काष्ठा xprt_create *);
	काष्ठा module		*owner;
	अक्षर			name[32];
	स्थिर अक्षर *		netid[];
पूर्ण;

/*
 * Generic पूर्णांकernal transport functions
 */
काष्ठा rpc_xprt		*xprt_create_transport(काष्ठा xprt_create *args);
व्योम			xprt_connect(काष्ठा rpc_task *task);
अचिन्हित दीर्घ		xprt_reconnect_delay(स्थिर काष्ठा rpc_xprt *xprt);
व्योम			xprt_reconnect_backoff(काष्ठा rpc_xprt *xprt,
					       अचिन्हित दीर्घ init_to);
व्योम			xprt_reserve(काष्ठा rpc_task *task);
व्योम			xprt_retry_reserve(काष्ठा rpc_task *task);
पूर्णांक			xprt_reserve_xprt(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task);
पूर्णांक			xprt_reserve_xprt_cong(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task);
व्योम			xprt_alloc_slot(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task);
व्योम			xprt_मुक्त_slot(काष्ठा rpc_xprt *xprt,
				       काष्ठा rpc_rqst *req);
व्योम			xprt_request_prepare(काष्ठा rpc_rqst *req);
bool			xprt_prepare_transmit(काष्ठा rpc_task *task);
व्योम			xprt_request_enqueue_transmit(काष्ठा rpc_task *task);
व्योम			xprt_request_enqueue_receive(काष्ठा rpc_task *task);
व्योम			xprt_request_रुको_receive(काष्ठा rpc_task *task);
व्योम			xprt_request_dequeue_xprt(काष्ठा rpc_task *task);
bool			xprt_request_need_retransmit(काष्ठा rpc_task *task);
व्योम			xprt_transmit(काष्ठा rpc_task *task);
व्योम			xprt_end_transmit(काष्ठा rpc_task *task);
पूर्णांक			xprt_adjust_समयout(काष्ठा rpc_rqst *req);
व्योम			xprt_release_xprt(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task);
व्योम			xprt_release_xprt_cong(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task);
व्योम			xprt_release(काष्ठा rpc_task *task);
काष्ठा rpc_xprt *	xprt_get(काष्ठा rpc_xprt *xprt);
व्योम			xprt_put(काष्ठा rpc_xprt *xprt);
काष्ठा rpc_xprt *	xprt_alloc(काष्ठा net *net, माप_प्रकार size,
				अचिन्हित पूर्णांक num_pपुनः_स्मृति,
				अचिन्हित पूर्णांक max_req);
व्योम			xprt_मुक्त(काष्ठा rpc_xprt *);
व्योम			xprt_add_backlog(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task);
bool			xprt_wake_up_backlog(काष्ठा rpc_xprt *xprt, काष्ठा rpc_rqst *req);

अटल अंतरभूत पूर्णांक
xprt_enable_swap(काष्ठा rpc_xprt *xprt)
अणु
	वापस xprt->ops->enable_swap(xprt);
पूर्ण

अटल अंतरभूत व्योम
xprt_disable_swap(काष्ठा rpc_xprt *xprt)
अणु
	xprt->ops->disable_swap(xprt);
पूर्ण

/*
 * Transport चयन helper functions
 */
पूर्णांक			xprt_रेजिस्टर_transport(काष्ठा xprt_class *type);
पूर्णांक			xprt_unरेजिस्टर_transport(काष्ठा xprt_class *type);
पूर्णांक			xprt_find_transport_ident(स्थिर अक्षर *);
व्योम			xprt_रुको_क्रम_reply_request_def(काष्ठा rpc_task *task);
व्योम			xprt_रुको_क्रम_reply_request_rtt(काष्ठा rpc_task *task);
व्योम			xprt_wake_pending_tasks(काष्ठा rpc_xprt *xprt, पूर्णांक status);
व्योम			xprt_रुको_क्रम_buffer_space(काष्ठा rpc_xprt *xprt);
bool			xprt_ग_लिखो_space(काष्ठा rpc_xprt *xprt);
व्योम			xprt_adjust_cwnd(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task, पूर्णांक result);
काष्ठा rpc_rqst *	xprt_lookup_rqst(काष्ठा rpc_xprt *xprt, __be32 xid);
व्योम			xprt_update_rtt(काष्ठा rpc_task *task);
व्योम			xprt_complete_rqst(काष्ठा rpc_task *task, पूर्णांक copied);
व्योम			xprt_pin_rqst(काष्ठा rpc_rqst *req);
व्योम			xprt_unpin_rqst(काष्ठा rpc_rqst *req);
व्योम			xprt_release_rqst_cong(काष्ठा rpc_task *task);
bool			xprt_request_get_cong(काष्ठा rpc_xprt *xprt, काष्ठा rpc_rqst *req);
व्योम			xprt_disconnect_करोne(काष्ठा rpc_xprt *xprt);
व्योम			xprt_क्रमce_disconnect(काष्ठा rpc_xprt *xprt);
व्योम			xprt_conditional_disconnect(काष्ठा rpc_xprt *xprt, अचिन्हित पूर्णांक cookie);

bool			xprt_lock_connect(काष्ठा rpc_xprt *, काष्ठा rpc_task *, व्योम *);
व्योम			xprt_unlock_connect(काष्ठा rpc_xprt *, व्योम *);

/*
 * Reserved bit positions in xprt->state
 */
#घोषणा XPRT_LOCKED		(0)
#घोषणा XPRT_CONNECTED		(1)
#घोषणा XPRT_CONNECTING		(2)
#घोषणा XPRT_CLOSE_WAIT		(3)
#घोषणा XPRT_BOUND		(4)
#घोषणा XPRT_BINDING		(5)
#घोषणा XPRT_CLOSING		(6)
#घोषणा XPRT_CONGESTED		(9)
#घोषणा XPRT_CWND_WAIT		(10)
#घोषणा XPRT_WRITE_SPACE	(11)

अटल अंतरभूत व्योम xprt_set_connected(काष्ठा rpc_xprt *xprt)
अणु
	set_bit(XPRT_CONNECTED, &xprt->state);
पूर्ण

अटल अंतरभूत व्योम xprt_clear_connected(काष्ठा rpc_xprt *xprt)
अणु
	clear_bit(XPRT_CONNECTED, &xprt->state);
पूर्ण

अटल अंतरभूत पूर्णांक xprt_connected(काष्ठा rpc_xprt *xprt)
अणु
	वापस test_bit(XPRT_CONNECTED, &xprt->state);
पूर्ण

अटल अंतरभूत पूर्णांक xprt_test_and_set_connected(काष्ठा rpc_xprt *xprt)
अणु
	वापस test_and_set_bit(XPRT_CONNECTED, &xprt->state);
पूर्ण

अटल अंतरभूत पूर्णांक xprt_test_and_clear_connected(काष्ठा rpc_xprt *xprt)
अणु
	वापस test_and_clear_bit(XPRT_CONNECTED, &xprt->state);
पूर्ण

अटल अंतरभूत व्योम xprt_clear_connecting(काष्ठा rpc_xprt *xprt)
अणु
	smp_mb__beक्रमe_atomic();
	clear_bit(XPRT_CONNECTING, &xprt->state);
	smp_mb__after_atomic();
पूर्ण

अटल अंतरभूत पूर्णांक xprt_connecting(काष्ठा rpc_xprt *xprt)
अणु
	वापस test_bit(XPRT_CONNECTING, &xprt->state);
पूर्ण

अटल अंतरभूत पूर्णांक xprt_test_and_set_connecting(काष्ठा rpc_xprt *xprt)
अणु
	वापस test_and_set_bit(XPRT_CONNECTING, &xprt->state);
पूर्ण

अटल अंतरभूत व्योम xprt_set_bound(काष्ठा rpc_xprt *xprt)
अणु
	test_and_set_bit(XPRT_BOUND, &xprt->state);
पूर्ण

अटल अंतरभूत पूर्णांक xprt_bound(काष्ठा rpc_xprt *xprt)
अणु
	वापस test_bit(XPRT_BOUND, &xprt->state);
पूर्ण

अटल अंतरभूत व्योम xprt_clear_bound(काष्ठा rpc_xprt *xprt)
अणु
	clear_bit(XPRT_BOUND, &xprt->state);
पूर्ण

अटल अंतरभूत व्योम xprt_clear_binding(काष्ठा rpc_xprt *xprt)
अणु
	smp_mb__beक्रमe_atomic();
	clear_bit(XPRT_BINDING, &xprt->state);
	smp_mb__after_atomic();
पूर्ण

अटल अंतरभूत पूर्णांक xprt_test_and_set_binding(काष्ठा rpc_xprt *xprt)
अणु
	वापस test_and_set_bit(XPRT_BINDING, &xprt->state);
पूर्ण

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
बाह्य अचिन्हित पूर्णांक rpc_inject_disconnect;
अटल अंतरभूत व्योम xprt_inject_disconnect(काष्ठा rpc_xprt *xprt)
अणु
	अगर (!rpc_inject_disconnect)
		वापस;
	अगर (atomic_dec_वापस(&xprt->inject_disconnect))
		वापस;
	atomic_set(&xprt->inject_disconnect, rpc_inject_disconnect);
	xprt->ops->inject_disconnect(xprt);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम xprt_inject_disconnect(काष्ठा rpc_xprt *xprt)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_SUNRPC_XPRT_H */
