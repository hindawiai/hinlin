<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* AF_RXRPC पूर्णांकernal definitions
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/atomic.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/win_minmax.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#समावेश <keys/rxrpc-type.h>
#समावेश "protocol.h"

#अगर 0
#घोषणा CHECK_SLAB_OKAY(X)				     \
	BUG_ON(atomic_पढ़ो((X)) >> (माप(atomic_t) - 2) == \
	       (POISON_FREE << 8 | POISON_FREE))
#अन्यथा
#घोषणा CHECK_SLAB_OKAY(X) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा FCRYPT_BSIZE 8
काष्ठा rxrpc_crypt अणु
	जोड़ अणु
		u8	x[FCRYPT_BSIZE];
		__be32	n[2];
	पूर्ण;
पूर्ण __attribute__((aligned(8)));

#घोषणा rxrpc_queue_work(WS)	queue_work(rxrpc_workqueue, (WS))
#घोषणा rxrpc_queue_delayed_work(WS,D)	\
	queue_delayed_work(rxrpc_workqueue, (WS), (D))

काष्ठा key_preparsed_payload;
काष्ठा rxrpc_connection;

/*
 * Mark applied to socket buffers in skb->mark.  skb->priority is used
 * to pass supplementary inक्रमmation.
 */
क्रमागत rxrpc_skb_mark अणु
	RXRPC_SKB_MARK_REJECT_BUSY,	/* Reject with BUSY */
	RXRPC_SKB_MARK_REJECT_ABORT,	/* Reject with ABORT (code in skb->priority) */
पूर्ण;

/*
 * sk_state क्रम RxRPC sockets
 */
क्रमागत अणु
	RXRPC_UNBOUND = 0,
	RXRPC_CLIENT_UNBOUND,		/* Unbound socket used as client */
	RXRPC_CLIENT_BOUND,		/* client local address bound */
	RXRPC_SERVER_BOUND,		/* server local address bound */
	RXRPC_SERVER_BOUND2,		/* second server local address bound */
	RXRPC_SERVER_LISTENING,		/* server listening क्रम connections */
	RXRPC_SERVER_LISTEN_DISABLED,	/* server listening disabled */
	RXRPC_CLOSE,			/* socket is being बंदd */
पूर्ण;

/*
 * Per-network namespace data.
 */
काष्ठा rxrpc_net अणु
	काष्ठा proc_dir_entry	*proc_net;	/* Subdir in /proc/net */
	u32			epoch;		/* Local epoch क्रम detecting local-end reset */
	काष्ठा list_head	calls;		/* List of calls active in this namespace */
	rwlock_t		call_lock;	/* Lock क्रम ->calls */
	atomic_t		nr_calls;	/* Count of allocated calls */

	atomic_t		nr_conns;
	काष्ठा list_head	conn_proc_list;	/* List of conns in this namespace क्रम proc */
	काष्ठा list_head	service_conns;	/* Service conns in this namespace */
	rwlock_t		conn_lock;	/* Lock क्रम ->conn_proc_list, ->service_conns */
	काष्ठा work_काष्ठा	service_conn_reaper;
	काष्ठा समयr_list	service_conn_reap_समयr;

	bool			live;

	bool			समाप्त_all_client_conns;
	atomic_t		nr_client_conns;
	spinlock_t		client_conn_cache_lock; /* Lock क्रम ->*_client_conns */
	spinlock_t		client_conn_discard_lock; /* Prevent multiple discarders */
	काष्ठा list_head	idle_client_conns;
	काष्ठा work_काष्ठा	client_conn_reaper;
	काष्ठा समयr_list	client_conn_reap_समयr;

	काष्ठा list_head	local_endpoपूर्णांकs;
	काष्ठा mutex		local_mutex;	/* Lock क्रम ->local_endpoपूर्णांकs */

	DECLARE_HASHTABLE	(peer_hash, 10);
	spinlock_t		peer_hash_lock;	/* Lock क्रम ->peer_hash */

#घोषणा RXRPC_KEEPALIVE_TIME 20 /* NAT keepalive समय in seconds */
	u8			peer_keepalive_cursor;
	समय64_t		peer_keepalive_base;
	काष्ठा list_head	peer_keepalive[32];
	काष्ठा list_head	peer_keepalive_new;
	काष्ठा समयr_list	peer_keepalive_समयr;
	काष्ठा work_काष्ठा	peer_keepalive_work;
पूर्ण;

/*
 * Service backlog pपुनः_स्मृतिation.
 *
 * This contains circular buffers of pपुनः_स्मृतिated peers, connections and calls
 * क्रम incoming service calls and their head and tail poपूर्णांकers.  This allows
 * calls to be set up in the data_पढ़ोy handler, thereby aव्योमing the need to
 * shuffle packets around so much.
 */
काष्ठा rxrpc_backlog अणु
	अचिन्हित लघु		peer_backlog_head;
	अचिन्हित लघु		peer_backlog_tail;
	अचिन्हित लघु		conn_backlog_head;
	अचिन्हित लघु		conn_backlog_tail;
	अचिन्हित लघु		call_backlog_head;
	अचिन्हित लघु		call_backlog_tail;
#घोषणा RXRPC_BACKLOG_MAX	32
	काष्ठा rxrpc_peer	*peer_backlog[RXRPC_BACKLOG_MAX];
	काष्ठा rxrpc_connection	*conn_backlog[RXRPC_BACKLOG_MAX];
	काष्ठा rxrpc_call	*call_backlog[RXRPC_BACKLOG_MAX];
पूर्ण;

/*
 * RxRPC socket definition
 */
काष्ठा rxrpc_sock अणु
	/* WARNING: sk has to be the first member */
	काष्ठा sock		sk;
	rxrpc_notअगरy_new_call_t	notअगरy_new_call; /* Func to notअगरy of new call */
	rxrpc_discard_new_call_t discard_new_call; /* Func to discard a new call */
	काष्ठा rxrpc_local	*local;		/* local endpoपूर्णांक */
	काष्ठा rxrpc_backlog	*backlog;	/* Pपुनः_स्मृतिation क्रम services */
	spinlock_t		incoming_lock;	/* Incoming call vs service shutकरोwn lock */
	काष्ठा list_head	sock_calls;	/* List of calls owned by this socket */
	काष्ठा list_head	to_be_accepted;	/* calls aरुकोing acceptance */
	काष्ठा list_head	recvmsg_q;	/* Calls aरुकोing recvmsg's attention  */
	rwlock_t		recvmsg_lock;	/* Lock क्रम recvmsg_q */
	काष्ठा key		*key;		/* security क्रम this socket */
	काष्ठा key		*securities;	/* list of server security descriptors */
	काष्ठा rb_root		calls;		/* User ID -> call mapping */
	अचिन्हित दीर्घ		flags;
#घोषणा RXRPC_SOCK_CONNECTED		0	/* connect_srx is set */
	rwlock_t		call_lock;	/* lock क्रम calls */
	u32			min_sec_level;	/* minimum security level */
#घोषणा RXRPC_SECURITY_MAX	RXRPC_SECURITY_ENCRYPT
	bool			exclusive;	/* Exclusive connection क्रम a client socket */
	u16			second_service;	/* Additional service bound to the endpoपूर्णांक */
	काष्ठा अणु
		/* Service upgrade inक्रमmation */
		u16		from;		/* Service ID to upgrade (अगर not 0) */
		u16		to;		/* service ID to upgrade to */
	पूर्ण service_upgrade;
	sa_family_t		family;		/* Protocol family created with */
	काष्ठा sockaddr_rxrpc	srx;		/* Primary Service/local addresses */
	काष्ठा sockaddr_rxrpc	connect_srx;	/* Default client address from connect() */
पूर्ण;

#घोषणा rxrpc_sk(__sk) container_of((__sk), काष्ठा rxrpc_sock, sk)

/*
 * CPU-byteorder normalised Rx packet header.
 */
काष्ठा rxrpc_host_header अणु
	u32		epoch;		/* client boot बारtamp */
	u32		cid;		/* connection and channel ID */
	u32		callNumber;	/* call ID (0 क्रम connection-level packets) */
	u32		seq;		/* sequence number of pkt in call stream */
	u32		serial;		/* serial number of pkt sent to network */
	u8		type;		/* packet type */
	u8		flags;		/* packet flags */
	u8		userStatus;	/* app-layer defined status */
	u8		securityIndex;	/* security protocol ID */
	जोड़ अणु
		u16	_rsvd;		/* reserved */
		u16	cksum;		/* kerberos security checksum */
	पूर्ण;
	u16		serviceId;	/* service ID */
पूर्ण __packed;

/*
 * RxRPC socket buffer निजी variables
 * - max 48 bytes (काष्ठा sk_buff::cb)
 */
काष्ठा rxrpc_skb_priv अणु
	atomic_t	nr_ring_pins;		/* Number of rxtx ring pins */
	u8		nr_subpackets;		/* Number of subpackets */
	u8		rx_flags;		/* Received packet flags */
#घोषणा RXRPC_SKB_INCL_LAST	0x01		/* - Includes last packet */
#घोषणा RXRPC_SKB_TX_BUFFER	0x02		/* - Is transmit buffer */
	जोड़ अणु
		पूर्णांक		reमुख्य;		/* amount of space reमुख्यing क्रम next ग_लिखो */

		/* List of requested ACKs on subpackets */
		अचिन्हित दीर्घ	rx_req_ack[(RXRPC_MAX_NR_JUMBO + BITS_PER_LONG - 1) /
					   BITS_PER_LONG];
	पूर्ण;

	काष्ठा rxrpc_host_header hdr;		/* RxRPC packet header from this packet */
पूर्ण;

#घोषणा rxrpc_skb(__skb) ((काष्ठा rxrpc_skb_priv *) &(__skb)->cb)

/*
 * RxRPC security module पूर्णांकerface
 */
काष्ठा rxrpc_security अणु
	स्थिर अक्षर		*name;		/* name of this service */
	u8			security_index;	/* security type provided */
	u32			no_key_पात;	/* Abort code indicating no key */

	/* Initialise a security service */
	पूर्णांक (*init)(व्योम);

	/* Clean up a security service */
	व्योम (*निकास)(व्योम);

	/* Parse the inक्रमmation from a server key */
	पूर्णांक (*preparse_server_key)(काष्ठा key_preparsed_payload *);

	/* Clean up the preparse buffer after parsing a server key */
	व्योम (*मुक्त_preparse_server_key)(काष्ठा key_preparsed_payload *);

	/* Destroy the payload of a server key */
	व्योम (*destroy_server_key)(काष्ठा key *);

	/* Describe a server key */
	व्योम (*describe_server_key)(स्थिर काष्ठा key *, काष्ठा seq_file *);

	/* initialise a connection's security */
	पूर्णांक (*init_connection_security)(काष्ठा rxrpc_connection *,
					काष्ठा rxrpc_key_token *);

	/* Work out how much data we can store in a packet, given an estimate
	 * of the amount of data reमुख्यing.
	 */
	पूर्णांक (*how_much_data)(काष्ठा rxrpc_call *, माप_प्रकार,
			     माप_प्रकार *, माप_प्रकार *, माप_प्रकार *);

	/* impose security on a packet */
	पूर्णांक (*secure_packet)(काष्ठा rxrpc_call *, काष्ठा sk_buff *, माप_प्रकार);

	/* verअगरy the security on a received packet */
	पूर्णांक (*verअगरy_packet)(काष्ठा rxrpc_call *, काष्ठा sk_buff *,
			     अचिन्हित पूर्णांक, अचिन्हित पूर्णांक, rxrpc_seq_t, u16);

	/* Free crypto request on a call */
	व्योम (*मुक्त_call_crypto)(काष्ठा rxrpc_call *);

	/* Locate the data in a received packet that has been verअगरied. */
	व्योम (*locate_data)(काष्ठा rxrpc_call *, काष्ठा sk_buff *,
			    अचिन्हित पूर्णांक *, अचिन्हित पूर्णांक *);

	/* issue a challenge */
	पूर्णांक (*issue_challenge)(काष्ठा rxrpc_connection *);

	/* respond to a challenge */
	पूर्णांक (*respond_to_challenge)(काष्ठा rxrpc_connection *,
				    काष्ठा sk_buff *,
				    u32 *);

	/* verअगरy a response */
	पूर्णांक (*verअगरy_response)(काष्ठा rxrpc_connection *,
			       काष्ठा sk_buff *,
			       u32 *);

	/* clear connection security */
	व्योम (*clear)(काष्ठा rxrpc_connection *);
पूर्ण;

/*
 * RxRPC local transport endpoपूर्णांक description
 * - owned by a single AF_RXRPC socket
 * - poपूर्णांकed to by transport socket काष्ठा sk_user_data
 */
काष्ठा rxrpc_local अणु
	काष्ठा rcu_head		rcu;
	atomic_t		active_users;	/* Number of users of the local endpoपूर्णांक */
	atomic_t		usage;		/* Number of references to the काष्ठाure */
	काष्ठा rxrpc_net	*rxnet;		/* The network ns in which this resides */
	काष्ठा list_head	link;
	काष्ठा socket		*socket;	/* my UDP socket */
	काष्ठा work_काष्ठा	processor;
	काष्ठा rxrpc_sock __rcu	*service;	/* Service(s) listening on this endpoपूर्णांक */
	काष्ठा rw_semaphore	defrag_sem;	/* control re-enablement of IP DF bit */
	काष्ठा sk_buff_head	reject_queue;	/* packets aरुकोing rejection */
	काष्ठा sk_buff_head	event_queue;	/* endpoपूर्णांक event packets aरुकोing processing */
	काष्ठा rb_root		client_bundles;	/* Client connection bundles by socket params */
	spinlock_t		client_bundles_lock; /* Lock क्रम client_bundles */
	spinlock_t		lock;		/* access lock */
	rwlock_t		services_lock;	/* lock क्रम services list */
	पूर्णांक			debug_id;	/* debug ID क्रम prपूर्णांकks */
	bool			dead;
	bool			service_बंदd;	/* Service socket बंदd */
	काष्ठा sockaddr_rxrpc	srx;		/* local address */
पूर्ण;

/*
 * RxRPC remote transport endpoपूर्णांक definition
 * - matched by local endpoपूर्णांक, remote port, address and protocol type
 */
काष्ठा rxrpc_peer अणु
	काष्ठा rcu_head		rcu;		/* This must be first */
	atomic_t		usage;
	अचिन्हित दीर्घ		hash_key;
	काष्ठा hlist_node	hash_link;
	काष्ठा rxrpc_local	*local;
	काष्ठा hlist_head	error_tarमाला_लो;	/* tarमाला_लो क्रम net error distribution */
	काष्ठा rb_root		service_conns;	/* Service connections */
	काष्ठा list_head	keepalive_link;	/* Link in net->peer_keepalive[] */
	समय64_t		last_tx_at;	/* Last समय packet sent here */
	seqlock_t		service_conn_lock;
	spinlock_t		lock;		/* access lock */
	अचिन्हित पूर्णांक		अगर_mtu;		/* पूर्णांकerface MTU क्रम this peer */
	अचिन्हित पूर्णांक		mtu;		/* network MTU क्रम this peer */
	अचिन्हित पूर्णांक		maxdata;	/* data size (MTU - hdrsize) */
	अचिन्हित लघु		hdrsize;	/* header size (IP + UDP + RxRPC) */
	पूर्णांक			debug_id;	/* debug ID क्रम prपूर्णांकks */
	काष्ठा sockaddr_rxrpc	srx;		/* remote address */

	/* calculated RTT cache */
#घोषणा RXRPC_RTT_CACHE_SIZE 32
	spinlock_t		rtt_input_lock;	/* RTT lock क्रम input routine */
	kसमय_प्रकार			rtt_last_req;	/* Time of last RTT request */
	अचिन्हित पूर्णांक		rtt_count;	/* Number of samples we've got */

	u32			srtt_us;	/* smoothed round trip समय << 3 in usecs */
	u32			mdev_us;	/* medium deviation			*/
	u32			mdev_max_us;	/* maximal mdev क्रम the last rtt period	*/
	u32			rttvar_us;	/* smoothed mdev_max			*/
	u32			rto_j;		/* Retransmission समयout in jअगरfies */
	u8			backoff;	/* Backoff समयout */

	u8			cong_cwnd;	/* Congestion winकरोw size */
पूर्ण;

/*
 * Keys क्रम matching a connection.
 */
काष्ठा rxrpc_conn_proto अणु
	जोड़ अणु
		काष्ठा अणु
			u32	epoch;		/* epoch of this connection */
			u32	cid;		/* connection ID */
		पूर्ण;
		u64		index_key;
	पूर्ण;
पूर्ण;

काष्ठा rxrpc_conn_parameters अणु
	काष्ठा rxrpc_local	*local;		/* Representation of local endpoपूर्णांक */
	काष्ठा rxrpc_peer	*peer;		/* Remote endpoपूर्णांक */
	काष्ठा key		*key;		/* Security details */
	bool			exclusive;	/* T अगर conn is exclusive */
	bool			upgrade;	/* T अगर service ID can be upgraded */
	u16			service_id;	/* Service ID क्रम this connection */
	u32			security_level;	/* Security level selected */
पूर्ण;

/*
 * Bits in the connection flags.
 */
क्रमागत rxrpc_conn_flag अणु
	RXRPC_CONN_HAS_IDR,		/* Has a client conn ID asचिन्हित */
	RXRPC_CONN_IN_SERVICE_CONNS,	/* Conn is in peer->service_conns */
	RXRPC_CONN_DONT_REUSE,		/* Don't reuse this connection */
	RXRPC_CONN_PROBING_FOR_UPGRADE,	/* Probing क्रम service upgrade */
	RXRPC_CONN_FINAL_ACK_0,		/* Need final ACK क्रम channel 0 */
	RXRPC_CONN_FINAL_ACK_1,		/* Need final ACK क्रम channel 1 */
	RXRPC_CONN_FINAL_ACK_2,		/* Need final ACK क्रम channel 2 */
	RXRPC_CONN_FINAL_ACK_3,		/* Need final ACK क्रम channel 3 */
पूर्ण;

#घोषणा RXRPC_CONN_FINAL_ACK_MASK ((1UL << RXRPC_CONN_FINAL_ACK_0) |	\
				   (1UL << RXRPC_CONN_FINAL_ACK_1) |	\
				   (1UL << RXRPC_CONN_FINAL_ACK_2) |	\
				   (1UL << RXRPC_CONN_FINAL_ACK_3))

/*
 * Events that can be उठाओd upon a connection.
 */
क्रमागत rxrpc_conn_event अणु
	RXRPC_CONN_EV_CHALLENGE,	/* Send challenge packet */
पूर्ण;

/*
 * The connection protocol state.
 */
क्रमागत rxrpc_conn_proto_state अणु
	RXRPC_CONN_UNUSED,		/* Connection not yet attempted */
	RXRPC_CONN_CLIENT,		/* Client connection */
	RXRPC_CONN_SERVICE_PREALLOC,	/* Service connection pपुनः_स्मृतिation */
	RXRPC_CONN_SERVICE_UNSECURED,	/* Service unsecured connection */
	RXRPC_CONN_SERVICE_CHALLENGING,	/* Service challenging क्रम security */
	RXRPC_CONN_SERVICE,		/* Service secured connection */
	RXRPC_CONN_REMOTELY_ABORTED,	/* Conn पातed by peer */
	RXRPC_CONN_LOCALLY_ABORTED,	/* Conn पातed locally */
	RXRPC_CONN__NR_STATES
पूर्ण;

/*
 * RxRPC client connection bundle.
 */
काष्ठा rxrpc_bundle अणु
	काष्ठा rxrpc_conn_parameters params;
	atomic_t		usage;
	अचिन्हित पूर्णांक		debug_id;
	bool			try_upgrade;	/* True अगर the bundle is attempting upgrade */
	bool			alloc_conn;	/* True अगर someone's getting a conn */
	लघु			alloc_error;	/* Error from last conn allocation */
	spinlock_t		channel_lock;
	काष्ठा rb_node		local_node;	/* Node in local->client_conns */
	काष्ठा list_head	रुकोing_calls;	/* Calls रुकोing क्रम channels */
	अचिन्हित दीर्घ		avail_chans;	/* Mask of available channels */
	काष्ठा rxrpc_connection	*conns[4];	/* The connections in the bundle (max 4) */
पूर्ण;

/*
 * RxRPC connection definition
 * - matched by अणु local, peer, epoch, conn_id, direction पूर्ण
 * - each connection can only handle four simultaneous calls
 */
काष्ठा rxrpc_connection अणु
	काष्ठा rxrpc_conn_proto	proto;
	काष्ठा rxrpc_conn_parameters params;

	atomic_t		usage;
	काष्ठा rcu_head		rcu;
	काष्ठा list_head	cache_link;

	अचिन्हित अक्षर		act_chans;	/* Mask of active channels */
	काष्ठा rxrpc_channel अणु
		अचिन्हित दीर्घ		final_ack_at;	/* Time at which to issue final ACK */
		काष्ठा rxrpc_call __rcu	*call;		/* Active call */
		अचिन्हित पूर्णांक		call_debug_id;	/* call->debug_id */
		u32			call_id;	/* ID of current call */
		u32			call_counter;	/* Call ID counter */
		u32			last_call;	/* ID of last call */
		u8			last_type;	/* Type of last packet */
		जोड़ अणु
			u32		last_seq;
			u32		last_पात;
		पूर्ण;
	पूर्ण channels[RXRPC_MAXCALLS];

	काष्ठा समयr_list	समयr;		/* Conn event समयr */
	काष्ठा work_काष्ठा	processor;	/* connection event processor */
	काष्ठा rxrpc_bundle	*bundle;	/* Client connection bundle */
	काष्ठा rb_node		service_node;	/* Node in peer->service_conns */
	काष्ठा list_head	proc_link;	/* link in procfs list */
	काष्ठा list_head	link;		/* link in master connection list */
	काष्ठा sk_buff_head	rx_queue;	/* received conn-level packets */

	स्थिर काष्ठा rxrpc_security *security;	/* applied security module */
	जोड़ अणु
		काष्ठा अणु
			काष्ठा crypto_sync_skcipher *cipher;	/* encryption handle */
			काष्ठा rxrpc_crypt csum_iv;	/* packet checksum base */
			u32	nonce;		/* response re-use preventer */
		पूर्ण rxkad;
	पूर्ण;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		events;
	अचिन्हित दीर्घ		idle_बारtamp;	/* Time at which last became idle */
	spinlock_t		state_lock;	/* state-change lock */
	क्रमागत rxrpc_conn_proto_state state;	/* current state of connection */
	u32			पात_code;	/* Abort code of connection पात */
	पूर्णांक			debug_id;	/* debug ID क्रम prपूर्णांकks */
	atomic_t		serial;		/* packet serial number counter */
	अचिन्हित पूर्णांक		hi_serial;	/* highest serial number received */
	u32			service_id;	/* Service ID, possibly upgraded */
	u8			security_ix;	/* security type */
	u8			out_clientflag;	/* RXRPC_CLIENT_INITIATED अगर we are client */
	u8			bundle_shअगरt;	/* Index पूर्णांकo bundle->avail_chans */
	लघु			error;		/* Local error code */
पूर्ण;

अटल अंतरभूत bool rxrpc_to_server(स्थिर काष्ठा rxrpc_skb_priv *sp)
अणु
	वापस sp->hdr.flags & RXRPC_CLIENT_INITIATED;
पूर्ण

अटल अंतरभूत bool rxrpc_to_client(स्थिर काष्ठा rxrpc_skb_priv *sp)
अणु
	वापस !rxrpc_to_server(sp);
पूर्ण

/*
 * Flags in call->flags.
 */
क्रमागत rxrpc_call_flag अणु
	RXRPC_CALL_RELEASED,		/* call has been released - no more message to userspace */
	RXRPC_CALL_HAS_USERID,		/* has a user ID attached */
	RXRPC_CALL_IS_SERVICE,		/* Call is service call */
	RXRPC_CALL_EXPOSED,		/* The call was exposed to the world */
	RXRPC_CALL_RX_LAST,		/* Received the last packet (at rxtx_top) */
	RXRPC_CALL_TX_LAST,		/* Last packet in Tx buffer (at rxtx_top) */
	RXRPC_CALL_SEND_PING,		/* A ping will need to be sent */
	RXRPC_CALL_RETRANS_TIMEOUT,	/* Retransmission due to समयout occurred */
	RXRPC_CALL_BEGAN_RX_TIMER,	/* We began the expect_rx_by समयr */
	RXRPC_CALL_RX_HEARD,		/* The peer responded at least once to this call */
	RXRPC_CALL_RX_UNDERRUN,		/* Got data underrun */
	RXRPC_CALL_DISCONNECTED,	/* The call has been disconnected */
	RXRPC_CALL_KERNEL,		/* The call was made by the kernel */
	RXRPC_CALL_UPGRADE,		/* Service upgrade was requested क्रम the call */
पूर्ण;

/*
 * Events that can be उठाओd on a call.
 */
क्रमागत rxrpc_call_event अणु
	RXRPC_CALL_EV_ACK,		/* need to generate ACK */
	RXRPC_CALL_EV_ABORT,		/* need to generate पात */
	RXRPC_CALL_EV_RESEND,		/* Tx resend required */
	RXRPC_CALL_EV_PING,		/* Ping send required */
	RXRPC_CALL_EV_EXPIRED,		/* Expiry occurred */
	RXRPC_CALL_EV_ACK_LOST,		/* ACK may be lost, send ping */
पूर्ण;

/*
 * The states that a call can be in.
 */
क्रमागत rxrpc_call_state अणु
	RXRPC_CALL_UNINITIALISED,
	RXRPC_CALL_CLIENT_AWAIT_CONN,	/* - client रुकोing क्रम connection to become available */
	RXRPC_CALL_CLIENT_SEND_REQUEST,	/* - client sending request phase */
	RXRPC_CALL_CLIENT_AWAIT_REPLY,	/* - client aरुकोing reply */
	RXRPC_CALL_CLIENT_RECV_REPLY,	/* - client receiving reply phase */
	RXRPC_CALL_SERVER_PREALLOC,	/* - service pपुनः_स्मृतिation */
	RXRPC_CALL_SERVER_SECURING,	/* - server securing request connection */
	RXRPC_CALL_SERVER_RECV_REQUEST,	/* - server receiving request */
	RXRPC_CALL_SERVER_ACK_REQUEST,	/* - server pending ACK of request */
	RXRPC_CALL_SERVER_SEND_REPLY,	/* - server sending reply */
	RXRPC_CALL_SERVER_AWAIT_ACK,	/* - server aरुकोing final ACK */
	RXRPC_CALL_COMPLETE,		/* - call complete */
	NR__RXRPC_CALL_STATES
पूर्ण;

/*
 * Call completion condition (state == RXRPC_CALL_COMPLETE).
 */
क्रमागत rxrpc_call_completion अणु
	RXRPC_CALL_SUCCEEDED,		/* - Normal termination */
	RXRPC_CALL_REMOTELY_ABORTED,	/* - call पातed by peer */
	RXRPC_CALL_LOCALLY_ABORTED,	/* - call पातed locally on error or बंद */
	RXRPC_CALL_LOCAL_ERROR,		/* - call failed due to local error */
	RXRPC_CALL_NETWORK_ERROR,	/* - call terminated by network error */
	NR__RXRPC_CALL_COMPLETIONS
पूर्ण;

/*
 * Call Tx congestion management modes.
 */
क्रमागत rxrpc_congest_mode अणु
	RXRPC_CALL_SLOW_START,
	RXRPC_CALL_CONGEST_AVOIDANCE,
	RXRPC_CALL_PACKET_LOSS,
	RXRPC_CALL_FAST_RETRANSMIT,
	NR__RXRPC_CONGEST_MODES
पूर्ण;

/*
 * RxRPC call definition
 * - matched by अणु connection, call_id पूर्ण
 */
काष्ठा rxrpc_call अणु
	काष्ठा rcu_head		rcu;
	काष्ठा rxrpc_connection	*conn;		/* connection carrying call */
	काष्ठा rxrpc_peer	*peer;		/* Peer record क्रम remote address */
	काष्ठा rxrpc_sock __rcu	*socket;	/* socket responsible */
	काष्ठा rxrpc_net	*rxnet;		/* Network namespace to which call beदीर्घs */
	स्थिर काष्ठा rxrpc_security *security;	/* applied security module */
	काष्ठा mutex		user_mutex;	/* User access mutex */
	अचिन्हित दीर्घ		ack_at;		/* When deferred ACK needs to happen */
	अचिन्हित दीर्घ		ack_lost_at;	/* When ACK is figured as lost */
	अचिन्हित दीर्घ		resend_at;	/* When next resend needs to happen */
	अचिन्हित दीर्घ		ping_at;	/* When next to send a ping */
	अचिन्हित दीर्घ		keepalive_at;	/* When next to send a keepalive ping */
	अचिन्हित दीर्घ		expect_rx_by;	/* When we expect to get a packet by */
	अचिन्हित दीर्घ		expect_req_by;	/* When we expect to get a request DATA packet by */
	अचिन्हित दीर्घ		expect_term_by;	/* When we expect call termination by */
	u32			next_rx_timo;	/* Timeout क्रम next Rx packet (jअगर) */
	u32			next_req_timo;	/* Timeout क्रम next Rx request packet (jअगर) */
	काष्ठा skcipher_request	*cipher_req;	/* Packet cipher request buffer */
	काष्ठा समयr_list	समयr;		/* Combined event समयr */
	काष्ठा work_काष्ठा	processor;	/* Event processor */
	rxrpc_notअगरy_rx_t	notअगरy_rx;	/* kernel service Rx notअगरication function */
	काष्ठा list_head	link;		/* link in master call list */
	काष्ठा list_head	chan_रुको_link;	/* Link in conn->bundle->रुकोing_calls */
	काष्ठा hlist_node	error_link;	/* link in error distribution list */
	काष्ठा list_head	accept_link;	/* Link in rx->acceptq */
	काष्ठा list_head	recvmsg_link;	/* Link in rx->recvmsg_q */
	काष्ठा list_head	sock_link;	/* Link in rx->sock_calls */
	काष्ठा rb_node		sock_node;	/* Node in rx->calls */
	काष्ठा sk_buff		*tx_pending;	/* Tx socket buffer being filled */
	रुको_queue_head_t	रुकोq;		/* Wait queue क्रम channel or Tx */
	s64			tx_total_len;	/* Total length left to be transmitted (or -1) */
	__be32			crypto_buf[2];	/* Temporary packet crypto buffer */
	अचिन्हित दीर्घ		user_call_ID;	/* user-defined call ID */
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		events;
	spinlock_t		lock;
	spinlock_t		notअगरy_lock;	/* Kernel notअगरication lock */
	rwlock_t		state_lock;	/* lock क्रम state transition */
	u32			पात_code;	/* Local/remote पात code */
	पूर्णांक			error;		/* Local error incurred */
	क्रमागत rxrpc_call_state	state;		/* current state of call */
	क्रमागत rxrpc_call_completion completion;	/* Call completion condition */
	atomic_t		usage;
	u16			service_id;	/* service ID */
	u8			security_ix;	/* Security type */
	क्रमागत rxrpc_पूर्णांकerruptibility पूर्णांकerruptibility; /* At what poपूर्णांक call may be पूर्णांकerrupted */
	u32			call_id;	/* call ID on connection  */
	u32			cid;		/* connection ID plus channel index */
	पूर्णांक			debug_id;	/* debug ID क्रम prपूर्णांकks */
	अचिन्हित लघु		rx_pkt_offset;	/* Current recvmsg packet offset */
	अचिन्हित लघु		rx_pkt_len;	/* Current recvmsg packet len */
	bool			rx_pkt_last;	/* Current recvmsg packet is last */

	/* Rx/Tx circular buffer, depending on phase.
	 *
	 * In the Rx phase, packets are annotated with 0 or the number of the
	 * segment of a jumbo packet each buffer refers to.  There can be up to
	 * 47 segments in a maximum-size UDP packet.
	 *
	 * In the Tx phase, packets are annotated with which buffers have been
	 * acked.
	 */
#घोषणा RXRPC_RXTX_BUFF_SIZE	64
#घोषणा RXRPC_RXTX_BUFF_MASK	(RXRPC_RXTX_BUFF_SIZE - 1)
#घोषणा RXRPC_INIT_RX_WINDOW_SIZE 63
	काष्ठा sk_buff		**rxtx_buffer;
	u8			*rxtx_annotations;
#घोषणा RXRPC_TX_ANNO_ACK	0
#घोषणा RXRPC_TX_ANNO_UNACK	1
#घोषणा RXRPC_TX_ANNO_NAK	2
#घोषणा RXRPC_TX_ANNO_RETRANS	3
#घोषणा RXRPC_TX_ANNO_MASK	0x03
#घोषणा RXRPC_TX_ANNO_LAST	0x04
#घोषणा RXRPC_TX_ANNO_RESENT	0x08

#घोषणा RXRPC_RX_ANNO_SUBPACKET	0x3f		/* Subpacket number in jumbogram */
#घोषणा RXRPC_RX_ANNO_VERIFIED	0x80		/* Set अगर verअगरied and decrypted */
	rxrpc_seq_t		tx_hard_ack;	/* Dead slot in buffer; the first transmitted but
						 * not hard-ACK'd packet follows this.
						 */
	rxrpc_seq_t		tx_top;		/* Highest Tx slot allocated. */
	u16			tx_backoff;	/* Delay to insert due to Tx failure */

	/* TCP-style slow-start congestion control [RFC5681].  Since the SMSS
	 * is fixed, we keep these numbers in terms of segments (ie. DATA
	 * packets) rather than bytes.
	 */
#घोषणा RXRPC_TX_SMSS		RXRPC_JUMBO_DATALEN
	u8			cong_cwnd;	/* Congestion winकरोw size */
	u8			cong_extra;	/* Extra to send क्रम congestion management */
	u8			cong_ssthresh;	/* Slow-start threshold */
	क्रमागत rxrpc_congest_mode	cong_mode:8;	/* Congestion management mode */
	u8			cong_dup_acks;	/* Count of ACKs showing missing packets */
	u8			cong_cumul_acks; /* Cumulative ACK count */
	kसमय_प्रकार			cong_tstamp;	/* Last समय cwnd was changed */

	rxrpc_seq_t		rx_hard_ack;	/* Dead slot in buffer; the first received but not
						 * consumed packet follows this.
						 */
	rxrpc_seq_t		rx_top;		/* Highest Rx slot allocated. */
	rxrpc_seq_t		rx_expect_next;	/* Expected next packet sequence number */
	rxrpc_serial_t		rx_serial;	/* Highest serial received क्रम this call */
	u8			rx_winsize;	/* Size of Rx winकरोw */
	u8			tx_winsize;	/* Maximum size of Tx winकरोw */
	bool			tx_phase;	/* T अगर transmission phase, F अगर receive phase */
	u8			nr_jumbo_bad;	/* Number of jumbo dups/exceeds-winकरोws */

	spinlock_t		input_lock;	/* Lock क्रम packet input to this call */

	/* receive-phase ACK management */
	u8			ackr_reason;	/* reason to ACK */
	rxrpc_serial_t		ackr_serial;	/* serial of packet being ACK'd */
	rxrpc_serial_t		ackr_first_seq;	/* first sequence number received */
	rxrpc_seq_t		ackr_prev_seq;	/* previous sequence number received */
	rxrpc_seq_t		ackr_consumed;	/* Highest packet shown consumed */
	rxrpc_seq_t		ackr_seen;	/* Highest packet shown seen */

	/* RTT management */
	rxrpc_serial_t		rtt_serial[4];	/* Serial number of DATA or PING sent */
	kसमय_प्रकार			rtt_sent_at[4];	/* Time packet sent */
	अचिन्हित दीर्घ		rtt_avail;	/* Mask of available slots in bits 0-3,
						 * Mask of pending samples in 8-11 */
#घोषणा RXRPC_CALL_RTT_AVAIL_MASK	0xf
#घोषणा RXRPC_CALL_RTT_PEND_SHIFT	8

	/* transmission-phase ACK management */
	kसमय_प्रकार			acks_latest_ts;	/* Timestamp of latest ACK received */
	rxrpc_seq_t		acks_lowest_nak; /* Lowest NACK in the buffer (or ==tx_hard_ack) */
	rxrpc_seq_t		acks_lost_top;	/* tx_top at the समय lost-ack ping sent */
	rxrpc_serial_t		acks_lost_ping;	/* Serial number of probe ACK */
पूर्ण;

/*
 * Summary of a new ACK and the changes it made to the Tx buffer packet states.
 */
काष्ठा rxrpc_ack_summary अणु
	u8			ack_reason;
	u8			nr_acks;		/* Number of ACKs in packet */
	u8			nr_nacks;		/* Number of NACKs in packet */
	u8			nr_new_acks;		/* Number of new ACKs in packet */
	u8			nr_new_nacks;		/* Number of new NACKs in packet */
	u8			nr_rot_new_acks;	/* Number of rotated new ACKs */
	bool			new_low_nack;		/* T अगर new low NACK found */
	bool			retrans_समयo;		/* T अगर reTx due to समयout happened */
	u8			flight_size;		/* Number of unreceived transmissions */
	/* Place to stash values क्रम tracing */
	क्रमागत rxrpc_congest_mode	mode:8;
	u8			cwnd;
	u8			ssthresh;
	u8			dup_acks;
	u8			cumulative_acks;
पूर्ण;

/*
 * sendmsg() cmsg-specअगरied parameters.
 */
क्रमागत rxrpc_command अणु
	RXRPC_CMD_SEND_DATA,		/* send data message */
	RXRPC_CMD_SEND_ABORT,		/* request पात generation */
	RXRPC_CMD_REJECT_BUSY,		/* [server] reject a call as busy */
	RXRPC_CMD_CHARGE_ACCEPT,	/* [server] अक्षरge accept pपुनः_स्मृतिation */
पूर्ण;

काष्ठा rxrpc_call_params अणु
	s64			tx_total_len;	/* Total Tx data length (अगर send data) */
	अचिन्हित दीर्घ		user_call_ID;	/* User's call ID */
	काष्ठा अणु
		u32		hard;		/* Maximum lअगरeसमय (sec) */
		u32		idle;		/* Max समय since last data packet (msec) */
		u32		normal;		/* Max समय since last call packet (msec) */
	पूर्ण समयouts;
	u8			nr_समयouts;	/* Number of समयouts specअगरied */
	bool			kernel;		/* T अगर kernel is making the call */
	क्रमागत rxrpc_पूर्णांकerruptibility पूर्णांकerruptibility; /* How is पूर्णांकerruptible is the call? */
पूर्ण;

काष्ठा rxrpc_send_params अणु
	काष्ठा rxrpc_call_params call;
	u32			पात_code;	/* Abort code to Tx (अगर पात) */
	क्रमागत rxrpc_command	command : 8;	/* The command to implement */
	bool			exclusive;	/* Shared or exclusive call */
	bool			upgrade;	/* If the connection is upgradeable */
पूर्ण;

#समावेश <trace/events/rxrpc.h>

/*
 * af_rxrpc.c
 */
बाह्य atomic_t rxrpc_n_tx_skbs, rxrpc_n_rx_skbs;
बाह्य काष्ठा workqueue_काष्ठा *rxrpc_workqueue;

/*
 * call_accept.c
 */
पूर्णांक rxrpc_service_pपुनः_स्मृति(काष्ठा rxrpc_sock *, gfp_t);
व्योम rxrpc_discard_pपुनः_स्मृति(काष्ठा rxrpc_sock *);
काष्ठा rxrpc_call *rxrpc_new_incoming_call(काष्ठा rxrpc_local *,
					   काष्ठा rxrpc_sock *,
					   काष्ठा sk_buff *);
व्योम rxrpc_accept_incoming_calls(काष्ठा rxrpc_local *);
पूर्णांक rxrpc_user_अक्षरge_accept(काष्ठा rxrpc_sock *, अचिन्हित दीर्घ);

/*
 * call_event.c
 */
व्योम rxrpc_propose_ACK(काष्ठा rxrpc_call *, u8, u32, bool, bool,
		       क्रमागत rxrpc_propose_ack_trace);
व्योम rxrpc_process_call(काष्ठा work_काष्ठा *);

अटल अंतरभूत व्योम rxrpc_reduce_call_समयr(काष्ठा rxrpc_call *call,
					   अचिन्हित दीर्घ expire_at,
					   अचिन्हित दीर्घ now,
					   क्रमागत rxrpc_समयr_trace why)
अणु
	trace_rxrpc_समयr(call, why, now);
	समयr_reduce(&call->समयr, expire_at);
पूर्ण

/*
 * call_object.c
 */
बाह्य स्थिर अक्षर *स्थिर rxrpc_call_states[];
बाह्य स्थिर अक्षर *स्थिर rxrpc_call_completions[];
बाह्य अचिन्हित पूर्णांक rxrpc_max_call_lअगरeसमय;
बाह्य काष्ठा kmem_cache *rxrpc_call_jar;

काष्ठा rxrpc_call *rxrpc_find_call_by_user_ID(काष्ठा rxrpc_sock *, अचिन्हित दीर्घ);
काष्ठा rxrpc_call *rxrpc_alloc_call(काष्ठा rxrpc_sock *, gfp_t, अचिन्हित पूर्णांक);
काष्ठा rxrpc_call *rxrpc_new_client_call(काष्ठा rxrpc_sock *,
					 काष्ठा rxrpc_conn_parameters *,
					 काष्ठा sockaddr_rxrpc *,
					 काष्ठा rxrpc_call_params *, gfp_t,
					 अचिन्हित पूर्णांक);
व्योम rxrpc_incoming_call(काष्ठा rxrpc_sock *, काष्ठा rxrpc_call *,
			 काष्ठा sk_buff *);
व्योम rxrpc_release_call(काष्ठा rxrpc_sock *, काष्ठा rxrpc_call *);
व्योम rxrpc_release_calls_on_socket(काष्ठा rxrpc_sock *);
bool __rxrpc_queue_call(काष्ठा rxrpc_call *);
bool rxrpc_queue_call(काष्ठा rxrpc_call *);
व्योम rxrpc_see_call(काष्ठा rxrpc_call *);
व्योम rxrpc_get_call(काष्ठा rxrpc_call *, क्रमागत rxrpc_call_trace);
व्योम rxrpc_put_call(काष्ठा rxrpc_call *, क्रमागत rxrpc_call_trace);
व्योम rxrpc_cleanup_call(काष्ठा rxrpc_call *);
व्योम rxrpc_destroy_all_calls(काष्ठा rxrpc_net *);

अटल अंतरभूत bool rxrpc_is_service_call(स्थिर काष्ठा rxrpc_call *call)
अणु
	वापस test_bit(RXRPC_CALL_IS_SERVICE, &call->flags);
पूर्ण

अटल अंतरभूत bool rxrpc_is_client_call(स्थिर काष्ठा rxrpc_call *call)
अणु
	वापस !rxrpc_is_service_call(call);
पूर्ण

/*
 * conn_client.c
 */
बाह्य अचिन्हित पूर्णांक rxrpc_reap_client_connections;
बाह्य अचिन्हित दीर्घ rxrpc_conn_idle_client_expiry;
बाह्य अचिन्हित दीर्घ rxrpc_conn_idle_client_fast_expiry;
बाह्य काष्ठा idr rxrpc_client_conn_ids;

व्योम rxrpc_destroy_client_conn_ids(व्योम);
काष्ठा rxrpc_bundle *rxrpc_get_bundle(काष्ठा rxrpc_bundle *);
व्योम rxrpc_put_bundle(काष्ठा rxrpc_bundle *);
पूर्णांक rxrpc_connect_call(काष्ठा rxrpc_sock *, काष्ठा rxrpc_call *,
		       काष्ठा rxrpc_conn_parameters *, काष्ठा sockaddr_rxrpc *,
		       gfp_t);
व्योम rxrpc_expose_client_call(काष्ठा rxrpc_call *);
व्योम rxrpc_disconnect_client_call(काष्ठा rxrpc_bundle *, काष्ठा rxrpc_call *);
व्योम rxrpc_put_client_conn(काष्ठा rxrpc_connection *);
व्योम rxrpc_discard_expired_client_conns(काष्ठा work_काष्ठा *);
व्योम rxrpc_destroy_all_client_connections(काष्ठा rxrpc_net *);
व्योम rxrpc_clean_up_local_conns(काष्ठा rxrpc_local *);

/*
 * conn_event.c
 */
व्योम rxrpc_process_connection(काष्ठा work_काष्ठा *);
व्योम rxrpc_process_delayed_final_acks(काष्ठा rxrpc_connection *, bool);

/*
 * conn_object.c
 */
बाह्य अचिन्हित पूर्णांक rxrpc_connection_expiry;
बाह्य अचिन्हित पूर्णांक rxrpc_बंदd_conn_expiry;

काष्ठा rxrpc_connection *rxrpc_alloc_connection(gfp_t);
काष्ठा rxrpc_connection *rxrpc_find_connection_rcu(काष्ठा rxrpc_local *,
						   काष्ठा sk_buff *,
						   काष्ठा rxrpc_peer **);
व्योम __rxrpc_disconnect_call(काष्ठा rxrpc_connection *, काष्ठा rxrpc_call *);
व्योम rxrpc_disconnect_call(काष्ठा rxrpc_call *);
व्योम rxrpc_समाप्त_connection(काष्ठा rxrpc_connection *);
bool rxrpc_queue_conn(काष्ठा rxrpc_connection *);
व्योम rxrpc_see_connection(काष्ठा rxrpc_connection *);
काष्ठा rxrpc_connection *rxrpc_get_connection(काष्ठा rxrpc_connection *);
काष्ठा rxrpc_connection *rxrpc_get_connection_maybe(काष्ठा rxrpc_connection *);
व्योम rxrpc_put_service_conn(काष्ठा rxrpc_connection *);
व्योम rxrpc_service_connection_reaper(काष्ठा work_काष्ठा *);
व्योम rxrpc_destroy_all_connections(काष्ठा rxrpc_net *);

अटल अंतरभूत bool rxrpc_conn_is_client(स्थिर काष्ठा rxrpc_connection *conn)
अणु
	वापस conn->out_clientflag;
पूर्ण

अटल अंतरभूत bool rxrpc_conn_is_service(स्थिर काष्ठा rxrpc_connection *conn)
अणु
	वापस !rxrpc_conn_is_client(conn);
पूर्ण

अटल अंतरभूत व्योम rxrpc_put_connection(काष्ठा rxrpc_connection *conn)
अणु
	अगर (!conn)
		वापस;

	अगर (rxrpc_conn_is_client(conn))
		rxrpc_put_client_conn(conn);
	अन्यथा
		rxrpc_put_service_conn(conn);
पूर्ण

अटल अंतरभूत व्योम rxrpc_reduce_conn_समयr(काष्ठा rxrpc_connection *conn,
					   अचिन्हित दीर्घ expire_at)
अणु
	समयr_reduce(&conn->समयr, expire_at);
पूर्ण

/*
 * conn_service.c
 */
काष्ठा rxrpc_connection *rxrpc_find_service_conn_rcu(काष्ठा rxrpc_peer *,
						     काष्ठा sk_buff *);
काष्ठा rxrpc_connection *rxrpc_pपुनः_स्मृति_service_connection(काष्ठा rxrpc_net *, gfp_t);
व्योम rxrpc_new_incoming_connection(काष्ठा rxrpc_sock *, काष्ठा rxrpc_connection *,
				   स्थिर काष्ठा rxrpc_security *, काष्ठा sk_buff *);
व्योम rxrpc_unpublish_service_conn(काष्ठा rxrpc_connection *);

/*
 * input.c
 */
पूर्णांक rxrpc_input_packet(काष्ठा sock *, काष्ठा sk_buff *);

/*
 * insecure.c
 */
बाह्य स्थिर काष्ठा rxrpc_security rxrpc_no_security;

/*
 * key.c
 */
बाह्य काष्ठा key_type key_type_rxrpc;

पूर्णांक rxrpc_request_key(काष्ठा rxrpc_sock *, sockptr_t , पूर्णांक);
पूर्णांक rxrpc_get_server_data_key(काष्ठा rxrpc_connection *, स्थिर व्योम *, समय64_t,
			      u32);

/*
 * local_event.c
 */
बाह्य व्योम rxrpc_process_local_events(काष्ठा rxrpc_local *);

/*
 * local_object.c
 */
काष्ठा rxrpc_local *rxrpc_lookup_local(काष्ठा net *, स्थिर काष्ठा sockaddr_rxrpc *);
काष्ठा rxrpc_local *rxrpc_get_local(काष्ठा rxrpc_local *);
काष्ठा rxrpc_local *rxrpc_get_local_maybe(काष्ठा rxrpc_local *);
व्योम rxrpc_put_local(काष्ठा rxrpc_local *);
काष्ठा rxrpc_local *rxrpc_use_local(काष्ठा rxrpc_local *);
व्योम rxrpc_unuse_local(काष्ठा rxrpc_local *);
व्योम rxrpc_queue_local(काष्ठा rxrpc_local *);
व्योम rxrpc_destroy_all_locals(काष्ठा rxrpc_net *);

अटल अंतरभूत bool __rxrpc_unuse_local(काष्ठा rxrpc_local *local)
अणु
	वापस atomic_dec_वापस(&local->active_users) == 0;
पूर्ण

अटल अंतरभूत bool __rxrpc_use_local(काष्ठा rxrpc_local *local)
अणु
	वापस atomic_fetch_add_unless(&local->active_users, 1, 0) != 0;
पूर्ण

/*
 * misc.c
 */
बाह्य अचिन्हित पूर्णांक rxrpc_max_backlog __पढ़ो_mostly;
बाह्य अचिन्हित दीर्घ rxrpc_requested_ack_delay;
बाह्य अचिन्हित दीर्घ rxrpc_soft_ack_delay;
बाह्य अचिन्हित दीर्घ rxrpc_idle_ack_delay;
बाह्य अचिन्हित पूर्णांक rxrpc_rx_winकरोw_size;
बाह्य अचिन्हित पूर्णांक rxrpc_rx_mtu;
बाह्य अचिन्हित पूर्णांक rxrpc_rx_jumbo_max;

बाह्य स्थिर s8 rxrpc_ack_priority[];

/*
 * net_ns.c
 */
बाह्य अचिन्हित पूर्णांक rxrpc_net_id;
बाह्य काष्ठा pernet_operations rxrpc_net_ops;

अटल अंतरभूत काष्ठा rxrpc_net *rxrpc_net(काष्ठा net *net)
अणु
	वापस net_generic(net, rxrpc_net_id);
पूर्ण

/*
 * output.c
 */
पूर्णांक rxrpc_send_ack_packet(काष्ठा rxrpc_call *, bool, rxrpc_serial_t *);
पूर्णांक rxrpc_send_पात_packet(काष्ठा rxrpc_call *);
पूर्णांक rxrpc_send_data_packet(काष्ठा rxrpc_call *, काष्ठा sk_buff *, bool);
व्योम rxrpc_reject_packets(काष्ठा rxrpc_local *);
व्योम rxrpc_send_keepalive(काष्ठा rxrpc_peer *);

/*
 * peer_event.c
 */
व्योम rxrpc_error_report(काष्ठा sock *);
व्योम rxrpc_peer_keepalive_worker(काष्ठा work_काष्ठा *);

/*
 * peer_object.c
 */
काष्ठा rxrpc_peer *rxrpc_lookup_peer_rcu(काष्ठा rxrpc_local *,
					 स्थिर काष्ठा sockaddr_rxrpc *);
काष्ठा rxrpc_peer *rxrpc_lookup_peer(काष्ठा rxrpc_sock *, काष्ठा rxrpc_local *,
				     काष्ठा sockaddr_rxrpc *, gfp_t);
काष्ठा rxrpc_peer *rxrpc_alloc_peer(काष्ठा rxrpc_local *, gfp_t);
व्योम rxrpc_new_incoming_peer(काष्ठा rxrpc_sock *, काष्ठा rxrpc_local *,
			     काष्ठा rxrpc_peer *);
व्योम rxrpc_destroy_all_peers(काष्ठा rxrpc_net *);
काष्ठा rxrpc_peer *rxrpc_get_peer(काष्ठा rxrpc_peer *);
काष्ठा rxrpc_peer *rxrpc_get_peer_maybe(काष्ठा rxrpc_peer *);
व्योम rxrpc_put_peer(काष्ठा rxrpc_peer *);
व्योम rxrpc_put_peer_locked(काष्ठा rxrpc_peer *);

/*
 * proc.c
 */
बाह्य स्थिर काष्ठा seq_operations rxrpc_call_seq_ops;
बाह्य स्थिर काष्ठा seq_operations rxrpc_connection_seq_ops;
बाह्य स्थिर काष्ठा seq_operations rxrpc_peer_seq_ops;

/*
 * recvmsg.c
 */
व्योम rxrpc_notअगरy_socket(काष्ठा rxrpc_call *);
bool __rxrpc_set_call_completion(काष्ठा rxrpc_call *, क्रमागत rxrpc_call_completion, u32, पूर्णांक);
bool rxrpc_set_call_completion(काष्ठा rxrpc_call *, क्रमागत rxrpc_call_completion, u32, पूर्णांक);
bool __rxrpc_call_completed(काष्ठा rxrpc_call *);
bool rxrpc_call_completed(काष्ठा rxrpc_call *);
bool __rxrpc_पात_call(स्थिर अक्षर *, काष्ठा rxrpc_call *, rxrpc_seq_t, u32, पूर्णांक);
bool rxrpc_पात_call(स्थिर अक्षर *, काष्ठा rxrpc_call *, rxrpc_seq_t, u32, पूर्णांक);
पूर्णांक rxrpc_recvmsg(काष्ठा socket *, काष्ठा msghdr *, माप_प्रकार, पूर्णांक);

/*
 * Abort a call due to a protocol error.
 */
अटल अंतरभूत bool __rxrpc_पात_eproto(काष्ठा rxrpc_call *call,
					काष्ठा sk_buff *skb,
					स्थिर अक्षर *eproto_why,
					स्थिर अक्षर *why,
					u32 पात_code)
अणु
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);

	trace_rxrpc_rx_eproto(call, sp->hdr.serial, eproto_why);
	वापस rxrpc_पात_call(why, call, sp->hdr.seq, पात_code, -EPROTO);
पूर्ण

#घोषणा rxrpc_पात_eproto(call, skb, eproto_why, पात_why, पात_code) \
	__rxrpc_पात_eproto((call), (skb), tracepoपूर्णांक_string(eproto_why), \
			     (पात_why), (पात_code))

/*
 * rtt.c
 */
व्योम rxrpc_peer_add_rtt(काष्ठा rxrpc_call *, क्रमागत rxrpc_rtt_rx_trace, पूर्णांक,
			rxrpc_serial_t, rxrpc_serial_t, kसमय_प्रकार, kसमय_प्रकार);
अचिन्हित दीर्घ rxrpc_get_rto_backoff(काष्ठा rxrpc_peer *, bool);
व्योम rxrpc_peer_init_rtt(काष्ठा rxrpc_peer *);

/*
 * rxkad.c
 */
#अगर_घोषित CONFIG_RXKAD
बाह्य स्थिर काष्ठा rxrpc_security rxkad;
#पूर्ण_अगर

/*
 * security.c
 */
पूर्णांक __init rxrpc_init_security(व्योम);
स्थिर काष्ठा rxrpc_security *rxrpc_security_lookup(u8);
व्योम rxrpc_निकास_security(व्योम);
पूर्णांक rxrpc_init_client_conn_security(काष्ठा rxrpc_connection *);
स्थिर काष्ठा rxrpc_security *rxrpc_get_incoming_security(काष्ठा rxrpc_sock *,
							 काष्ठा sk_buff *);
काष्ठा key *rxrpc_look_up_server_security(काष्ठा rxrpc_connection *,
					  काष्ठा sk_buff *, u32, u32);

/*
 * sendmsg.c
 */
पूर्णांक rxrpc_करो_sendmsg(काष्ठा rxrpc_sock *, काष्ठा msghdr *, माप_प्रकार);

/*
 * server_key.c
 */
बाह्य काष्ठा key_type key_type_rxrpc_s;

पूर्णांक rxrpc_server_keyring(काष्ठा rxrpc_sock *, sockptr_t, पूर्णांक);

/*
 * skbuff.c
 */
व्योम rxrpc_kernel_data_consumed(काष्ठा rxrpc_call *, काष्ठा sk_buff *);
व्योम rxrpc_packet_deकाष्ठाor(काष्ठा sk_buff *);
व्योम rxrpc_new_skb(काष्ठा sk_buff *, क्रमागत rxrpc_skb_trace);
व्योम rxrpc_see_skb(काष्ठा sk_buff *, क्रमागत rxrpc_skb_trace);
व्योम rxrpc_eaten_skb(काष्ठा sk_buff *, क्रमागत rxrpc_skb_trace);
व्योम rxrpc_get_skb(काष्ठा sk_buff *, क्रमागत rxrpc_skb_trace);
व्योम rxrpc_मुक्त_skb(काष्ठा sk_buff *, क्रमागत rxrpc_skb_trace);
व्योम rxrpc_purge_queue(काष्ठा sk_buff_head *);

/*
 * sysctl.c
 */
#अगर_घोषित CONFIG_SYSCTL
बाह्य पूर्णांक __init rxrpc_sysctl_init(व्योम);
बाह्य व्योम rxrpc_sysctl_निकास(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक __init rxrpc_sysctl_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम rxrpc_sysctl_निकास(व्योम) अणुपूर्ण
#पूर्ण_अगर

/*
 * utils.c
 */
पूर्णांक rxrpc_extract_addr_from_skb(काष्ठा sockaddr_rxrpc *, काष्ठा sk_buff *);

अटल अंतरभूत bool beक्रमe(u32 seq1, u32 seq2)
अणु
        वापस (s32)(seq1 - seq2) < 0;
पूर्ण
अटल अंतरभूत bool beक्रमe_eq(u32 seq1, u32 seq2)
अणु
        वापस (s32)(seq1 - seq2) <= 0;
पूर्ण
अटल अंतरभूत bool after(u32 seq1, u32 seq2)
अणु
        वापस (s32)(seq1 - seq2) > 0;
पूर्ण
अटल अंतरभूत bool after_eq(u32 seq1, u32 seq2)
अणु
        वापस (s32)(seq1 - seq2) >= 0;
पूर्ण

/*
 * debug tracing
 */
बाह्य अचिन्हित पूर्णांक rxrpc_debug;

#घोषणा dbgprपूर्णांकk(FMT,...) \
	prपूर्णांकk("[%-6.6s] "FMT"\n", current->comm ,##__VA_ARGS__)

#घोषणा kenter(FMT,...)	dbgprपूर्णांकk("==> %s("FMT")",__func__ ,##__VA_ARGS__)
#घोषणा kleave(FMT,...)	dbgprपूर्णांकk("<== %s()"FMT"",__func__ ,##__VA_ARGS__)
#घोषणा kdebug(FMT,...)	dbgprपूर्णांकk("    "FMT ,##__VA_ARGS__)
#घोषणा kproto(FMT,...)	dbgprपूर्णांकk("### "FMT ,##__VA_ARGS__)
#घोषणा knet(FMT,...)	dbgprपूर्णांकk("@@@ "FMT ,##__VA_ARGS__)


#अगर defined(__KDEBUG)
#घोषणा _enter(FMT,...)	kenter(FMT,##__VA_ARGS__)
#घोषणा _leave(FMT,...)	kleave(FMT,##__VA_ARGS__)
#घोषणा _debug(FMT,...)	kdebug(FMT,##__VA_ARGS__)
#घोषणा _proto(FMT,...)	kproto(FMT,##__VA_ARGS__)
#घोषणा _net(FMT,...)	knet(FMT,##__VA_ARGS__)

#या_अगर defined(CONFIG_AF_RXRPC_DEBUG)
#घोषणा RXRPC_DEBUG_KENTER	0x01
#घोषणा RXRPC_DEBUG_KLEAVE	0x02
#घोषणा RXRPC_DEBUG_KDEBUG	0x04
#घोषणा RXRPC_DEBUG_KPROTO	0x08
#घोषणा RXRPC_DEBUG_KNET	0x10

#घोषणा _enter(FMT,...)					\
करो अणु							\
	अगर (unlikely(rxrpc_debug & RXRPC_DEBUG_KENTER))	\
		kenter(FMT,##__VA_ARGS__);		\
पूर्ण जबतक (0)

#घोषणा _leave(FMT,...)					\
करो अणु							\
	अगर (unlikely(rxrpc_debug & RXRPC_DEBUG_KLEAVE))	\
		kleave(FMT,##__VA_ARGS__);		\
पूर्ण जबतक (0)

#घोषणा _debug(FMT,...)					\
करो अणु							\
	अगर (unlikely(rxrpc_debug & RXRPC_DEBUG_KDEBUG))	\
		kdebug(FMT,##__VA_ARGS__);		\
पूर्ण जबतक (0)

#घोषणा _proto(FMT,...)					\
करो अणु							\
	अगर (unlikely(rxrpc_debug & RXRPC_DEBUG_KPROTO))	\
		kproto(FMT,##__VA_ARGS__);		\
पूर्ण जबतक (0)

#घोषणा _net(FMT,...)					\
करो अणु							\
	अगर (unlikely(rxrpc_debug & RXRPC_DEBUG_KNET))	\
		knet(FMT,##__VA_ARGS__);		\
पूर्ण जबतक (0)

#अन्यथा
#घोषणा _enter(FMT,...)	no_prपूर्णांकk("==> %s("FMT")",__func__ ,##__VA_ARGS__)
#घोषणा _leave(FMT,...)	no_prपूर्णांकk("<== %s()"FMT"",__func__ ,##__VA_ARGS__)
#घोषणा _debug(FMT,...)	no_prपूर्णांकk("    "FMT ,##__VA_ARGS__)
#घोषणा _proto(FMT,...)	no_prपूर्णांकk("### "FMT ,##__VA_ARGS__)
#घोषणा _net(FMT,...)	no_prपूर्णांकk("@@@ "FMT ,##__VA_ARGS__)
#पूर्ण_अगर

/*
 * debug निश्चितion checking
 */
#अगर 1 // defined(__KDEBUGALL)

#घोषणा ASSERT(X)						\
करो अणु								\
	अगर (unlikely(!(X))) अणु					\
		pr_err("Assertion failed\n");			\
		BUG();						\
	पूर्ण							\
पूर्ण जबतक (0)

#घोषणा ASSERTCMP(X, OP, Y)						\
करो अणु									\
	__typeof__(X) _x = (X);						\
	__typeof__(Y) _y = (__typeof__(X))(Y);				\
	अगर (unlikely(!(_x OP _y))) अणु					\
		pr_err("Assertion failed - %lu(0x%lx) %s %lu(0x%lx) is false\n", \
		       (अचिन्हित दीर्घ)_x, (अचिन्हित दीर्घ)_x, #OP,	\
		       (अचिन्हित दीर्घ)_y, (अचिन्हित दीर्घ)_y);		\
		BUG();							\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा ASSERTIF(C, X)						\
करो अणु								\
	अगर (unlikely((C) && !(X))) अणु				\
		pr_err("Assertion failed\n");			\
		BUG();						\
	पूर्ण							\
पूर्ण जबतक (0)

#घोषणा ASSERTIFCMP(C, X, OP, Y)					\
करो अणु									\
	__typeof__(X) _x = (X);						\
	__typeof__(Y) _y = (__typeof__(X))(Y);				\
	अगर (unlikely((C) && !(_x OP _y))) अणु				\
		pr_err("Assertion failed - %lu(0x%lx) %s %lu(0x%lx) is false\n", \
		       (अचिन्हित दीर्घ)_x, (अचिन्हित दीर्घ)_x, #OP,	\
		       (अचिन्हित दीर्घ)_y, (अचिन्हित दीर्घ)_y);		\
		BUG();							\
	पूर्ण								\
पूर्ण जबतक (0)

#अन्यथा

#घोषणा ASSERT(X)				\
करो अणु						\
पूर्ण जबतक (0)

#घोषणा ASSERTCMP(X, OP, Y)			\
करो अणु						\
पूर्ण जबतक (0)

#घोषणा ASSERTIF(C, X)				\
करो अणु						\
पूर्ण जबतक (0)

#घोषणा ASSERTIFCMP(C, X, OP, Y)		\
करो अणु						\
पूर्ण जबतक (0)

#पूर्ण_अगर /* __KDEBUGALL */
