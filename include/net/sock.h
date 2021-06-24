<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the AF_INET socket handler.
 *
 * Version:	@(#)sock.h	1.0.4	05/13/93
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Corey Minyard <wf-rch!minyard@relay.EU.net>
 *		Florian La Roche <flla@stud.uni-sb.de>
 *
 * Fixes:
 *		Alan Cox	:	Volatiles in skbuff poपूर्णांकers. See
 *					skbuff comments. May be overकरोne,
 *					better to prove they can be हटाओd
 *					than the reverse.
 *		Alan Cox	:	Added a zapped field क्रम tcp to note
 *					a socket is reset and must stay shut up
 *		Alan Cox	:	New fields क्रम options
 *	Pauline Middelink	:	identd support
 *		Alan Cox	:	Eliminate low level recv/recvfrom
 *		David S. Miller	:	New socket lookup architecture.
 *              Steve Whitehouse:       Default routines क्रम sock_ops
 *              Arnalकरो C. Melo :	हटाओd net_pinfo, tp_pinfo and made
 *              			protinfo be just a व्योम poपूर्णांकer, as the
 *              			protocol specअगरic parts were moved to
 *              			respective headers and ipv4/v6, etc now
 *              			use निजी slabcaches क्रम its socks
 *              Pedro Hortas	:	New flags field क्रम socket options
 */
#अगर_अघोषित _SOCK_H
#घोषणा _SOCK_H

#समावेश <linux/hardirq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/list_nulls.h>
#समावेश <linux/समयr.h>
#समावेश <linux/cache.h>
#समावेश <linux/bitops.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>	/* काष्ठा sk_buff */
#समावेश <linux/mm.h>
#समावेश <linux/security.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/page_counter.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/अटल_key.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/cgroup-defs.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/filter.h>
#समावेश <linux/rculist_nulls.h>
#समावेश <linux/poll.h>
#समावेश <linux/sockptr.h>
#समावेश <linux/indirect_call_wrapper.h>
#समावेश <linux/atomic.h>
#समावेश <linux/refcount.h>
#समावेश <net/dst.h>
#समावेश <net/checksum.h>
#समावेश <net/tcp_states.h>
#समावेश <linux/net_tstamp.h>
#समावेश <net/l3mdev.h>

/*
 * This काष्ठाure really needs to be cleaned up.
 * Most of it is क्रम TCP, and not used by any of
 * the other protocols.
 */

/* Define this to get the SOCK_DBG debugging facility. */
#घोषणा SOCK_DEBUGGING
#अगर_घोषित SOCK_DEBUGGING
#घोषणा SOCK_DEBUG(sk, msg...) करो अणु अगर ((sk) && sock_flag((sk), SOCK_DBG)) \
					prपूर्णांकk(KERN_DEBUG msg); पूर्ण जबतक (0)
#अन्यथा
/* Validate arguments and करो nothing */
अटल अंतरभूत __म_लिखो(2, 3)
व्योम SOCK_DEBUG(स्थिर काष्ठा sock *sk, स्थिर अक्षर *msg, ...)
अणु
पूर्ण
#पूर्ण_अगर

/* This is the per-socket lock.  The spinlock provides a synchronization
 * between user contexts and software पूर्णांकerrupt processing, whereas the
 * mini-semaphore synchronizes multiple users amongst themselves.
 */
प्रकार काष्ठा अणु
	spinlock_t		slock;
	पूर्णांक			owned;
	रुको_queue_head_t	wq;
	/*
	 * We express the mutex-alike socket_lock semantics
	 * to the lock validator by explicitly managing
	 * the slock as a lock variant (in addition to
	 * the slock itself):
	 */
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	काष्ठा lockdep_map dep_map;
#पूर्ण_अगर
पूर्ण socket_lock_t;

काष्ठा sock;
काष्ठा proto;
काष्ठा net;

प्रकार __u32 __bitwise __portpair;
प्रकार __u64 __bitwise __addrpair;

/**
 *	काष्ठा sock_common - minimal network layer representation of sockets
 *	@skc_daddr: Foreign IPv4 addr
 *	@skc_rcv_saddr: Bound local IPv4 addr
 *	@skc_addrpair: 8-byte-aligned __u64 जोड़ of @skc_daddr & @skc_rcv_saddr
 *	@skc_hash: hash value used with various protocol lookup tables
 *	@skc_u16hashes: two u16 hash values used by UDP lookup tables
 *	@skc_dport: placeholder क्रम inet_dport/tw_dport
 *	@skc_num: placeholder क्रम inet_num/tw_num
 *	@skc_portpair: __u32 जोड़ of @skc_dport & @skc_num
 *	@skc_family: network address family
 *	@skc_state: Connection state
 *	@skc_reuse: %SO_REUSEADDR setting
 *	@skc_reuseport: %SO_REUSEPORT setting
 *	@skc_ipv6only: socket is IPV6 only
 *	@skc_net_refcnt: socket is using net ref counting
 *	@skc_bound_dev_अगर: bound device index अगर != 0
 *	@skc_bind_node: bind hash linkage क्रम various protocol lookup tables
 *	@skc_portaddr_node: second hash linkage क्रम UDP/UDP-Lite protocol
 *	@skc_prot: protocol handlers inside a network family
 *	@skc_net: reference to the network namespace of this socket
 *	@skc_v6_daddr: IPV6 destination address
 *	@skc_v6_rcv_saddr: IPV6 source address
 *	@skc_cookie: socket's cookie value
 *	@skc_node: मुख्य hash linkage क्रम various protocol lookup tables
 *	@skc_nulls_node: मुख्य hash linkage क्रम TCP/UDP/UDP-Lite protocol
 *	@skc_tx_queue_mapping: tx queue number क्रम this connection
 *	@skc_rx_queue_mapping: rx queue number क्रम this connection
 *	@skc_flags: place holder क्रम sk_flags
 *		%SO_LINGER (l_onoff), %SO_BROADCAST, %SO_KEEPALIVE,
 *		%SO_OOBINLINE settings, %SO_TIMESTAMPING settings
 *	@skc_listener: connection request listener socket (aka rsk_listener)
 *		[जोड़ with @skc_flags]
 *	@skc_tw_dr: (aka tw_dr) ptr to &काष्ठा inet_समयरुको_death_row
 *		[जोड़ with @skc_flags]
 *	@skc_incoming_cpu: record/match cpu processing incoming packets
 *	@skc_rcv_wnd: (aka rsk_rcv_wnd) TCP receive winकरोw size (possibly scaled)
 *		[जोड़ with @skc_incoming_cpu]
 *	@skc_tw_rcv_nxt: (aka tw_rcv_nxt) TCP winकरोw next expected seq number
 *		[जोड़ with @skc_incoming_cpu]
 *	@skc_refcnt: reference count
 *
 *	This is the minimal network layer representation of sockets, the header
 *	क्रम काष्ठा sock and काष्ठा inet_समयरुको_sock.
 */
काष्ठा sock_common अणु
	/* skc_daddr and skc_rcv_saddr must be grouped on a 8 bytes aligned
	 * address on 64bit arches : cf INET_MATCH()
	 */
	जोड़ अणु
		__addrpair	skc_addrpair;
		काष्ठा अणु
			__be32	skc_daddr;
			__be32	skc_rcv_saddr;
		पूर्ण;
	पूर्ण;
	जोड़  अणु
		अचिन्हित पूर्णांक	skc_hash;
		__u16		skc_u16hashes[2];
	पूर्ण;
	/* skc_dport && skc_num must be grouped as well */
	जोड़ अणु
		__portpair	skc_portpair;
		काष्ठा अणु
			__be16	skc_dport;
			__u16	skc_num;
		पूर्ण;
	पूर्ण;

	अचिन्हित लघु		skc_family;
	अस्थिर अचिन्हित अक्षर	skc_state;
	अचिन्हित अक्षर		skc_reuse:4;
	अचिन्हित अक्षर		skc_reuseport:1;
	अचिन्हित अक्षर		skc_ipv6only:1;
	अचिन्हित अक्षर		skc_net_refcnt:1;
	पूर्णांक			skc_bound_dev_अगर;
	जोड़ अणु
		काष्ठा hlist_node	skc_bind_node;
		काष्ठा hlist_node	skc_portaddr_node;
	पूर्ण;
	काष्ठा proto		*skc_prot;
	possible_net_t		skc_net;

#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा in6_addr		skc_v6_daddr;
	काष्ठा in6_addr		skc_v6_rcv_saddr;
#पूर्ण_अगर

	atomic64_t		skc_cookie;

	/* following fields are padding to क्रमce
	 * offset(काष्ठा sock, sk_refcnt) == 128 on 64bit arches
	 * assuming IPV6 is enabled. We use this padding dअगरferently
	 * क्रम dअगरferent kind of 'sockets'
	 */
	जोड़ अणु
		अचिन्हित दीर्घ	skc_flags;
		काष्ठा sock	*skc_listener; /* request_sock */
		काष्ठा inet_समयरुको_death_row *skc_tw_dr; /* inet_समयरुको_sock */
	पूर्ण;
	/*
	 * fields between करोntcopy_begin/करोntcopy_end
	 * are not copied in sock_copy()
	 */
	/* निजी: */
	पूर्णांक			skc_करोntcopy_begin[0];
	/* खुला: */
	जोड़ अणु
		काष्ठा hlist_node	skc_node;
		काष्ठा hlist_nulls_node skc_nulls_node;
	पूर्ण;
	अचिन्हित लघु		skc_tx_queue_mapping;
#अगर_घोषित CONFIG_SOCK_RX_QUEUE_MAPPING
	अचिन्हित लघु		skc_rx_queue_mapping;
#पूर्ण_अगर
	जोड़ अणु
		पूर्णांक		skc_incoming_cpu;
		u32		skc_rcv_wnd;
		u32		skc_tw_rcv_nxt; /* काष्ठा tcp_समयरुको_sock  */
	पूर्ण;

	refcount_t		skc_refcnt;
	/* निजी: */
	पूर्णांक                     skc_करोntcopy_end[0];
	जोड़ अणु
		u32		skc_rxhash;
		u32		skc_winकरोw_clamp;
		u32		skc_tw_snd_nxt; /* काष्ठा tcp_समयरुको_sock */
	पूर्ण;
	/* खुला: */
पूर्ण;

काष्ठा bpf_local_storage;

/**
  *	काष्ठा sock - network layer representation of sockets
  *	@__sk_common: shared layout with inet_समयरुको_sock
  *	@sk_shutकरोwn: mask of %SEND_SHUTDOWN and/or %RCV_SHUTDOWN
  *	@sk_userlocks: %SO_SNDBUF and %SO_RCVBUF settings
  *	@sk_lock:	synchronizer
  *	@sk_kern_sock: True अगर sock is using kernel lock classes
  *	@sk_rcvbuf: size of receive buffer in bytes
  *	@sk_wq: sock रुको queue and async head
  *	@sk_rx_dst: receive input route used by early demux
  *	@sk_dst_cache: destination cache
  *	@sk_dst_pending_confirm: need to confirm neighbour
  *	@sk_policy: flow policy
  *	@sk_rx_skb_cache: cache copy of recently accessed RX skb
  *	@sk_receive_queue: incoming packets
  *	@sk_wmem_alloc: transmit queue bytes committed
  *	@sk_tsq_flags: TCP Small Queues flags
  *	@sk_ग_लिखो_queue: Packet sending queue
  *	@sk_omem_alloc: "o" is "option" or "other"
  *	@sk_wmem_queued: persistent queue size
  *	@sk_क्रमward_alloc: space allocated क्रमward
  *	@sk_napi_id: id of the last napi context to receive data क्रम sk
  *	@sk_ll_usec: usecs to busypoll when there is no data
  *	@sk_allocation: allocation mode
  *	@sk_pacing_rate: Pacing rate (अगर supported by transport/packet scheduler)
  *	@sk_pacing_status: Pacing status (requested, handled by sch_fq)
  *	@sk_max_pacing_rate: Maximum pacing rate (%SO_MAX_PACING_RATE)
  *	@sk_sndbuf: size of send buffer in bytes
  *	@__sk_flags_offset: empty field used to determine location of bitfield
  *	@sk_padding: unused element क्रम alignment
  *	@sk_no_check_tx: %SO_NO_CHECK setting, set checksum in TX packets
  *	@sk_no_check_rx: allow zero checksum in RX packets
  *	@sk_route_caps: route capabilities (e.g. %NETIF_F_TSO)
  *	@sk_route_nocaps: क्रमbidden route capabilities (e.g NETIF_F_GSO_MASK)
  *	@sk_route_क्रमced_caps: अटल, क्रमced route capabilities
  *		(set in tcp_init_sock())
  *	@sk_gso_type: GSO type (e.g. %SKB_GSO_TCPV4)
  *	@sk_gso_max_size: Maximum GSO segment size to build
  *	@sk_gso_max_segs: Maximum number of GSO segments
  *	@sk_pacing_shअगरt: scaling factor क्रम TCP Small Queues
  *	@sk_lingerसमय: %SO_LINGER l_linger setting
  *	@sk_backlog: always used with the per-socket spinlock held
  *	@sk_callback_lock: used with the callbacks in the end of this काष्ठा
  *	@sk_error_queue: rarely used
  *	@sk_prot_creator: sk_prot of original sock creator (see ipv6_setsockopt,
  *			  IPV6_ADDRFORM क्रम instance)
  *	@sk_err: last error
  *	@sk_err_soft: errors that करोn't cause failure but are the cause of a
  *		      persistent failure not just 'timed out'
  *	@sk_drops: raw/udp drops counter
  *	@sk_ack_backlog: current listen backlog
  *	@sk_max_ack_backlog: listen backlog set in listen()
  *	@sk_uid: user id of owner
  *	@sk_prefer_busy_poll: prefer busypolling over softirq processing
  *	@sk_busy_poll_budget: napi processing budget when busypolling
  *	@sk_priority: %SO_PRIORITY setting
  *	@sk_type: socket type (%SOCK_STREAM, etc)
  *	@sk_protocol: which protocol this socket beदीर्घs in this network family
  *	@sk_peer_pid: &काष्ठा pid क्रम this socket's peer
  *	@sk_peer_cred: %SO_PEERCRED setting
  *	@sk_rcvlowat: %SO_RCVLOWAT setting
  *	@sk_rcvसमयo: %SO_RCVTIMEO setting
  *	@sk_sndसमयo: %SO_SNDTIMEO setting
  *	@sk_txhash: computed flow hash क्रम use on transmit
  *	@sk_filter: socket filtering inकाष्ठाions
  *	@sk_समयr: sock cleanup समयr
  *	@sk_stamp: समय stamp of last packet received
  *	@sk_stamp_seq: lock क्रम accessing sk_stamp on 32 bit architectures only
  *	@sk_tsflags: SO_TIMESTAMPING socket options
  *	@sk_tskey: counter to disambiguate concurrent tstamp requests
  *	@sk_zckey: counter to order MSG_ZEROCOPY notअगरications
  *	@sk_socket: Identd and reporting IO संकेतs
  *	@sk_user_data: RPC layer निजी data
  *	@sk_frag: cached page frag
  *	@sk_peek_off: current peek_offset value
  *	@sk_send_head: front of stuff to transmit
  *	@tcp_rtx_queue: TCP re-transmit queue [जोड़ with @sk_send_head]
  *	@sk_tx_skb_cache: cache copy of recently accessed TX skb
  *	@sk_security: used by security modules
  *	@sk_mark: generic packet mark
  *	@sk_cgrp_data: cgroup data क्रम this cgroup
  *	@sk_memcg: this socket's memory cgroup association
  *	@sk_ग_लिखो_pending: a ग_लिखो to stream socket रुकोs to start
  *	@sk_state_change: callback to indicate change in the state of the sock
  *	@sk_data_पढ़ोy: callback to indicate there is data to be processed
  *	@sk_ग_लिखो_space: callback to indicate there is bf sending space available
  *	@sk_error_report: callback to indicate errors (e.g. %MSG_ERRQUEUE)
  *	@sk_backlog_rcv: callback to process the backlog
  *	@sk_validate_xmit_skb: ptr to an optional validate function
  *	@sk_deकाष्ठा: called at sock मुक्तing समय, i.e. when all refcnt == 0
  *	@sk_reuseport_cb: reuseport group container
  *	@sk_bpf_storage: ptr to cache and control क्रम bpf_sk_storage
  *	@sk_rcu: used during RCU grace period
  *	@sk_घड़ीid: घड़ीid used by समय-based scheduling (SO_TXTIME)
  *	@sk_txसमय_deadline_mode: set deadline mode क्रम SO_TXTIME
  *	@sk_txसमय_report_errors: set report errors mode क्रम SO_TXTIME
  *	@sk_txसमय_unused: unused txसमय flags
  */
काष्ठा sock अणु
	/*
	 * Now काष्ठा inet_समयरुको_sock also uses sock_common, so please just
	 * करोn't add nothing beक्रमe this first member (__sk_common) --acme
	 */
	काष्ठा sock_common	__sk_common;
#घोषणा sk_node			__sk_common.skc_node
#घोषणा sk_nulls_node		__sk_common.skc_nulls_node
#घोषणा sk_refcnt		__sk_common.skc_refcnt
#घोषणा sk_tx_queue_mapping	__sk_common.skc_tx_queue_mapping
#अगर_घोषित CONFIG_SOCK_RX_QUEUE_MAPPING
#घोषणा sk_rx_queue_mapping	__sk_common.skc_rx_queue_mapping
#पूर्ण_अगर

#घोषणा sk_करोntcopy_begin	__sk_common.skc_करोntcopy_begin
#घोषणा sk_करोntcopy_end		__sk_common.skc_करोntcopy_end
#घोषणा sk_hash			__sk_common.skc_hash
#घोषणा sk_portpair		__sk_common.skc_portpair
#घोषणा sk_num			__sk_common.skc_num
#घोषणा sk_dport		__sk_common.skc_dport
#घोषणा sk_addrpair		__sk_common.skc_addrpair
#घोषणा sk_daddr		__sk_common.skc_daddr
#घोषणा sk_rcv_saddr		__sk_common.skc_rcv_saddr
#घोषणा sk_family		__sk_common.skc_family
#घोषणा sk_state		__sk_common.skc_state
#घोषणा sk_reuse		__sk_common.skc_reuse
#घोषणा sk_reuseport		__sk_common.skc_reuseport
#घोषणा sk_ipv6only		__sk_common.skc_ipv6only
#घोषणा sk_net_refcnt		__sk_common.skc_net_refcnt
#घोषणा sk_bound_dev_अगर		__sk_common.skc_bound_dev_अगर
#घोषणा sk_bind_node		__sk_common.skc_bind_node
#घोषणा sk_prot			__sk_common.skc_prot
#घोषणा sk_net			__sk_common.skc_net
#घोषणा sk_v6_daddr		__sk_common.skc_v6_daddr
#घोषणा sk_v6_rcv_saddr	__sk_common.skc_v6_rcv_saddr
#घोषणा sk_cookie		__sk_common.skc_cookie
#घोषणा sk_incoming_cpu		__sk_common.skc_incoming_cpu
#घोषणा sk_flags		__sk_common.skc_flags
#घोषणा sk_rxhash		__sk_common.skc_rxhash

	socket_lock_t		sk_lock;
	atomic_t		sk_drops;
	पूर्णांक			sk_rcvlowat;
	काष्ठा sk_buff_head	sk_error_queue;
	काष्ठा sk_buff		*sk_rx_skb_cache;
	काष्ठा sk_buff_head	sk_receive_queue;
	/*
	 * The backlog queue is special, it is always used with
	 * the per-socket spinlock held and requires low latency
	 * access. Thereक्रमe we special हाल it's implementation.
	 * Note : rmem_alloc is in this काष्ठाure to fill a hole
	 * on 64bit arches, not because its logically part of
	 * backlog.
	 */
	काष्ठा अणु
		atomic_t	rmem_alloc;
		पूर्णांक		len;
		काष्ठा sk_buff	*head;
		काष्ठा sk_buff	*tail;
	पूर्ण sk_backlog;
#घोषणा sk_rmem_alloc sk_backlog.rmem_alloc

	पूर्णांक			sk_क्रमward_alloc;
#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	अचिन्हित पूर्णांक		sk_ll_usec;
	/* ===== mostly पढ़ो cache line ===== */
	अचिन्हित पूर्णांक		sk_napi_id;
#पूर्ण_अगर
	पूर्णांक			sk_rcvbuf;

	काष्ठा sk_filter __rcu	*sk_filter;
	जोड़ अणु
		काष्ठा socket_wq __rcu	*sk_wq;
		/* निजी: */
		काष्ठा socket_wq	*sk_wq_raw;
		/* खुला: */
	पूर्ण;
#अगर_घोषित CONFIG_XFRM
	काष्ठा xfrm_policy __rcu *sk_policy[2];
#पूर्ण_अगर
	काष्ठा dst_entry	*sk_rx_dst;
	काष्ठा dst_entry __rcu	*sk_dst_cache;
	atomic_t		sk_omem_alloc;
	पूर्णांक			sk_sndbuf;

	/* ===== cache line क्रम TX ===== */
	पूर्णांक			sk_wmem_queued;
	refcount_t		sk_wmem_alloc;
	अचिन्हित दीर्घ		sk_tsq_flags;
	जोड़ अणु
		काष्ठा sk_buff	*sk_send_head;
		काष्ठा rb_root	tcp_rtx_queue;
	पूर्ण;
	काष्ठा sk_buff		*sk_tx_skb_cache;
	काष्ठा sk_buff_head	sk_ग_लिखो_queue;
	__s32			sk_peek_off;
	पूर्णांक			sk_ग_लिखो_pending;
	__u32			sk_dst_pending_confirm;
	u32			sk_pacing_status; /* see क्रमागत sk_pacing */
	दीर्घ			sk_sndसमयo;
	काष्ठा समयr_list	sk_समयr;
	__u32			sk_priority;
	__u32			sk_mark;
	अचिन्हित दीर्घ		sk_pacing_rate; /* bytes per second */
	अचिन्हित दीर्घ		sk_max_pacing_rate;
	काष्ठा page_frag	sk_frag;
	netdev_features_t	sk_route_caps;
	netdev_features_t	sk_route_nocaps;
	netdev_features_t	sk_route_क्रमced_caps;
	पूर्णांक			sk_gso_type;
	अचिन्हित पूर्णांक		sk_gso_max_size;
	gfp_t			sk_allocation;
	__u32			sk_txhash;

	/*
	 * Because of non atomicity rules, all
	 * changes are रक्षित by socket lock.
	 */
	u8			sk_padding : 1,
				sk_kern_sock : 1,
				sk_no_check_tx : 1,
				sk_no_check_rx : 1,
				sk_userlocks : 4;
	u8			sk_pacing_shअगरt;
	u16			sk_type;
	u16			sk_protocol;
	u16			sk_gso_max_segs;
	अचिन्हित दीर्घ	        sk_lingerसमय;
	काष्ठा proto		*sk_prot_creator;
	rwlock_t		sk_callback_lock;
	पूर्णांक			sk_err,
				sk_err_soft;
	u32			sk_ack_backlog;
	u32			sk_max_ack_backlog;
	kuid_t			sk_uid;
#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	u8			sk_prefer_busy_poll;
	u16			sk_busy_poll_budget;
#पूर्ण_अगर
	काष्ठा pid		*sk_peer_pid;
	स्थिर काष्ठा cred	*sk_peer_cred;
	दीर्घ			sk_rcvसमयo;
	kसमय_प्रकार			sk_stamp;
#अगर BITS_PER_LONG==32
	seqlock_t		sk_stamp_seq;
#पूर्ण_अगर
	u16			sk_tsflags;
	u8			sk_shutकरोwn;
	u32			sk_tskey;
	atomic_t		sk_zckey;

	u8			sk_घड़ीid;
	u8			sk_txसमय_deadline_mode : 1,
				sk_txसमय_report_errors : 1,
				sk_txसमय_unused : 6;

	काष्ठा socket		*sk_socket;
	व्योम			*sk_user_data;
#अगर_घोषित CONFIG_SECURITY
	व्योम			*sk_security;
#पूर्ण_अगर
	काष्ठा sock_cgroup_data	sk_cgrp_data;
	काष्ठा mem_cgroup	*sk_memcg;
	व्योम			(*sk_state_change)(काष्ठा sock *sk);
	व्योम			(*sk_data_पढ़ोy)(काष्ठा sock *sk);
	व्योम			(*sk_ग_लिखो_space)(काष्ठा sock *sk);
	व्योम			(*sk_error_report)(काष्ठा sock *sk);
	पूर्णांक			(*sk_backlog_rcv)(काष्ठा sock *sk,
						  काष्ठा sk_buff *skb);
#अगर_घोषित CONFIG_SOCK_VALIDATE_XMIT
	काष्ठा sk_buff*		(*sk_validate_xmit_skb)(काष्ठा sock *sk,
							काष्ठा net_device *dev,
							काष्ठा sk_buff *skb);
#पूर्ण_अगर
	व्योम                    (*sk_deकाष्ठा)(काष्ठा sock *sk);
	काष्ठा sock_reuseport __rcu	*sk_reuseport_cb;
#अगर_घोषित CONFIG_BPF_SYSCALL
	काष्ठा bpf_local_storage __rcu	*sk_bpf_storage;
#पूर्ण_अगर
	काष्ठा rcu_head		sk_rcu;
पूर्ण;

क्रमागत sk_pacing अणु
	SK_PACING_NONE		= 0,
	SK_PACING_NEEDED	= 1,
	SK_PACING_FQ		= 2,
पूर्ण;

/* Poपूर्णांकer stored in sk_user_data might not be suitable क्रम copying
 * when cloning the socket. For instance, it can poपूर्णांक to a reference
 * counted object. sk_user_data bottom bit is set अगर poपूर्णांकer must not
 * be copied.
 */
#घोषणा SK_USER_DATA_NOCOPY	1UL
#घोषणा SK_USER_DATA_BPF	2UL	/* Managed by BPF */
#घोषणा SK_USER_DATA_PTRMASK	~(SK_USER_DATA_NOCOPY | SK_USER_DATA_BPF)

/**
 * sk_user_data_is_nocopy - Test अगर sk_user_data poपूर्णांकer must not be copied
 * @sk: socket
 */
अटल अंतरभूत bool sk_user_data_is_nocopy(स्थिर काष्ठा sock *sk)
अणु
	वापस ((uपूर्णांकptr_t)sk->sk_user_data & SK_USER_DATA_NOCOPY);
पूर्ण

#घोषणा __sk_user_data(sk) ((*((व्योम __rcu **)&(sk)->sk_user_data)))

#घोषणा rcu_dereference_sk_user_data(sk)				\
(अणु									\
	व्योम *__पंचांगp = rcu_dereference(__sk_user_data((sk)));		\
	(व्योम *)((uपूर्णांकptr_t)__पंचांगp & SK_USER_DATA_PTRMASK);		\
पूर्ण)
#घोषणा rcu_assign_sk_user_data(sk, ptr)				\
(अणु									\
	uपूर्णांकptr_t __पंचांगp = (uपूर्णांकptr_t)(ptr);				\
	WARN_ON_ONCE(__पंचांगp & ~SK_USER_DATA_PTRMASK);			\
	rcu_assign_poपूर्णांकer(__sk_user_data((sk)), __पंचांगp);		\
पूर्ण)
#घोषणा rcu_assign_sk_user_data_nocopy(sk, ptr)				\
(अणु									\
	uपूर्णांकptr_t __पंचांगp = (uपूर्णांकptr_t)(ptr);				\
	WARN_ON_ONCE(__पंचांगp & ~SK_USER_DATA_PTRMASK);			\
	rcu_assign_poपूर्णांकer(__sk_user_data((sk)),			\
			   __पंचांगp | SK_USER_DATA_NOCOPY);		\
पूर्ण)

/*
 * SK_CAN_REUSE and SK_NO_REUSE on a socket mean that the socket is OK
 * or not whether his port will be reused by someone अन्यथा. SK_FORCE_REUSE
 * on a socket means that the socket will reuse everybody अन्यथा's port
 * without looking at the other's sk_reuse value.
 */

#घोषणा SK_NO_REUSE	0
#घोषणा SK_CAN_REUSE	1
#घोषणा SK_FORCE_REUSE	2

पूर्णांक sk_set_peek_off(काष्ठा sock *sk, पूर्णांक val);

अटल अंतरभूत पूर्णांक sk_peek_offset(काष्ठा sock *sk, पूर्णांक flags)
अणु
	अगर (unlikely(flags & MSG_PEEK)) अणु
		वापस READ_ONCE(sk->sk_peek_off);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sk_peek_offset_bwd(काष्ठा sock *sk, पूर्णांक val)
अणु
	s32 off = READ_ONCE(sk->sk_peek_off);

	अगर (unlikely(off >= 0)) अणु
		off = max_t(s32, off - val, 0);
		WRITE_ONCE(sk->sk_peek_off, off);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sk_peek_offset_fwd(काष्ठा sock *sk, पूर्णांक val)
अणु
	sk_peek_offset_bwd(sk, -val);
पूर्ण

/*
 * Hashed lists helper routines
 */
अटल अंतरभूत काष्ठा sock *sk_entry(स्थिर काष्ठा hlist_node *node)
अणु
	वापस hlist_entry(node, काष्ठा sock, sk_node);
पूर्ण

अटल अंतरभूत काष्ठा sock *__sk_head(स्थिर काष्ठा hlist_head *head)
अणु
	वापस hlist_entry(head->first, काष्ठा sock, sk_node);
पूर्ण

अटल अंतरभूत काष्ठा sock *sk_head(स्थिर काष्ठा hlist_head *head)
अणु
	वापस hlist_empty(head) ? शून्य : __sk_head(head);
पूर्ण

अटल अंतरभूत काष्ठा sock *__sk_nulls_head(स्थिर काष्ठा hlist_nulls_head *head)
अणु
	वापस hlist_nulls_entry(head->first, काष्ठा sock, sk_nulls_node);
पूर्ण

अटल अंतरभूत काष्ठा sock *sk_nulls_head(स्थिर काष्ठा hlist_nulls_head *head)
अणु
	वापस hlist_nulls_empty(head) ? शून्य : __sk_nulls_head(head);
पूर्ण

अटल अंतरभूत काष्ठा sock *sk_next(स्थिर काष्ठा sock *sk)
अणु
	वापस hlist_entry_safe(sk->sk_node.next, काष्ठा sock, sk_node);
पूर्ण

अटल अंतरभूत काष्ठा sock *sk_nulls_next(स्थिर काष्ठा sock *sk)
अणु
	वापस (!is_a_nulls(sk->sk_nulls_node.next)) ?
		hlist_nulls_entry(sk->sk_nulls_node.next,
				  काष्ठा sock, sk_nulls_node) :
		शून्य;
पूर्ण

अटल अंतरभूत bool sk_unhashed(स्थिर काष्ठा sock *sk)
अणु
	वापस hlist_unhashed(&sk->sk_node);
पूर्ण

अटल अंतरभूत bool sk_hashed(स्थिर काष्ठा sock *sk)
अणु
	वापस !sk_unhashed(sk);
पूर्ण

अटल अंतरभूत व्योम sk_node_init(काष्ठा hlist_node *node)
अणु
	node->pprev = शून्य;
पूर्ण

अटल अंतरभूत व्योम sk_nulls_node_init(काष्ठा hlist_nulls_node *node)
अणु
	node->pprev = शून्य;
पूर्ण

अटल अंतरभूत व्योम __sk_del_node(काष्ठा sock *sk)
अणु
	__hlist_del(&sk->sk_node);
पूर्ण

/* NB: equivalent to hlist_del_init_rcu */
अटल अंतरभूत bool __sk_del_node_init(काष्ठा sock *sk)
अणु
	अगर (sk_hashed(sk)) अणु
		__sk_del_node(sk);
		sk_node_init(&sk->sk_node);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* Grab socket reference count. This operation is valid only
   when sk is ALREADY grabbed f.e. it is found in hash table
   or a list and the lookup is made under lock preventing hash table
   modअगरications.
 */

अटल __always_अंतरभूत व्योम sock_hold(काष्ठा sock *sk)
अणु
	refcount_inc(&sk->sk_refcnt);
पूर्ण

/* Ungrab socket in the context, which assumes that socket refcnt
   cannot hit zero, f.e. it is true in context of any socketcall.
 */
अटल __always_अंतरभूत व्योम __sock_put(काष्ठा sock *sk)
अणु
	refcount_dec(&sk->sk_refcnt);
पूर्ण

अटल अंतरभूत bool sk_del_node_init(काष्ठा sock *sk)
अणु
	bool rc = __sk_del_node_init(sk);

	अगर (rc) अणु
		/* paranoid क्रम a जबतक -acme */
		WARN_ON(refcount_पढ़ो(&sk->sk_refcnt) == 1);
		__sock_put(sk);
	पूर्ण
	वापस rc;
पूर्ण
#घोषणा sk_del_node_init_rcu(sk)	sk_del_node_init(sk)

अटल अंतरभूत bool __sk_nulls_del_node_init_rcu(काष्ठा sock *sk)
अणु
	अगर (sk_hashed(sk)) अणु
		hlist_nulls_del_init_rcu(&sk->sk_nulls_node);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत bool sk_nulls_del_node_init_rcu(काष्ठा sock *sk)
अणु
	bool rc = __sk_nulls_del_node_init_rcu(sk);

	अगर (rc) अणु
		/* paranoid क्रम a जबतक -acme */
		WARN_ON(refcount_पढ़ो(&sk->sk_refcnt) == 1);
		__sock_put(sk);
	पूर्ण
	वापस rc;
पूर्ण

अटल अंतरभूत व्योम __sk_add_node(काष्ठा sock *sk, काष्ठा hlist_head *list)
अणु
	hlist_add_head(&sk->sk_node, list);
पूर्ण

अटल अंतरभूत व्योम sk_add_node(काष्ठा sock *sk, काष्ठा hlist_head *list)
अणु
	sock_hold(sk);
	__sk_add_node(sk, list);
पूर्ण

अटल अंतरभूत व्योम sk_add_node_rcu(काष्ठा sock *sk, काष्ठा hlist_head *list)
अणु
	sock_hold(sk);
	अगर (IS_ENABLED(CONFIG_IPV6) && sk->sk_reuseport &&
	    sk->sk_family == AF_INET6)
		hlist_add_tail_rcu(&sk->sk_node, list);
	अन्यथा
		hlist_add_head_rcu(&sk->sk_node, list);
पूर्ण

अटल अंतरभूत व्योम sk_add_node_tail_rcu(काष्ठा sock *sk, काष्ठा hlist_head *list)
अणु
	sock_hold(sk);
	hlist_add_tail_rcu(&sk->sk_node, list);
पूर्ण

अटल अंतरभूत व्योम __sk_nulls_add_node_rcu(काष्ठा sock *sk, काष्ठा hlist_nulls_head *list)
अणु
	hlist_nulls_add_head_rcu(&sk->sk_nulls_node, list);
पूर्ण

अटल अंतरभूत व्योम __sk_nulls_add_node_tail_rcu(काष्ठा sock *sk, काष्ठा hlist_nulls_head *list)
अणु
	hlist_nulls_add_tail_rcu(&sk->sk_nulls_node, list);
पूर्ण

अटल अंतरभूत व्योम sk_nulls_add_node_rcu(काष्ठा sock *sk, काष्ठा hlist_nulls_head *list)
अणु
	sock_hold(sk);
	__sk_nulls_add_node_rcu(sk, list);
पूर्ण

अटल अंतरभूत व्योम __sk_del_bind_node(काष्ठा sock *sk)
अणु
	__hlist_del(&sk->sk_bind_node);
पूर्ण

अटल अंतरभूत व्योम sk_add_bind_node(काष्ठा sock *sk,
					काष्ठा hlist_head *list)
अणु
	hlist_add_head(&sk->sk_bind_node, list);
पूर्ण

#घोषणा sk_क्रम_each(__sk, list) \
	hlist_क्रम_each_entry(__sk, list, sk_node)
#घोषणा sk_क्रम_each_rcu(__sk, list) \
	hlist_क्रम_each_entry_rcu(__sk, list, sk_node)
#घोषणा sk_nulls_क्रम_each(__sk, node, list) \
	hlist_nulls_क्रम_each_entry(__sk, node, list, sk_nulls_node)
#घोषणा sk_nulls_क्रम_each_rcu(__sk, node, list) \
	hlist_nulls_क्रम_each_entry_rcu(__sk, node, list, sk_nulls_node)
#घोषणा sk_क्रम_each_from(__sk) \
	hlist_क्रम_each_entry_from(__sk, sk_node)
#घोषणा sk_nulls_क्रम_each_from(__sk, node) \
	अगर (__sk && (अणु node = &(__sk)->sk_nulls_node; 1; पूर्ण)) \
		hlist_nulls_क्रम_each_entry_from(__sk, node, sk_nulls_node)
#घोषणा sk_क्रम_each_safe(__sk, पंचांगp, list) \
	hlist_क्रम_each_entry_safe(__sk, पंचांगp, list, sk_node)
#घोषणा sk_क्रम_each_bound(__sk, list) \
	hlist_क्रम_each_entry(__sk, list, sk_bind_node)

/**
 * sk_क्रम_each_entry_offset_rcu - iterate over a list at a given काष्ठा offset
 * @tpos:	the type * to use as a loop cursor.
 * @pos:	the &काष्ठा hlist_node to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @offset:	offset of hlist_node within the काष्ठा.
 *
 */
#घोषणा sk_क्रम_each_entry_offset_rcu(tpos, pos, head, offset)		       \
	क्रम (pos = rcu_dereference(hlist_first_rcu(head));		       \
	     pos != शून्य &&						       \
		(अणु tpos = (typeof(*tpos) *)((व्योम *)pos - offset); 1;पूर्ण);       \
	     pos = rcu_dereference(hlist_next_rcu(pos)))

अटल अंतरभूत काष्ठा user_namespace *sk_user_ns(काष्ठा sock *sk)
अणु
	/* Careful only use this in a context where these parameters
	 * can not change and must all be valid, such as recvmsg from
	 * userspace.
	 */
	वापस sk->sk_socket->file->f_cred->user_ns;
पूर्ण

/* Sock flags */
क्रमागत sock_flags अणु
	SOCK_DEAD,
	SOCK_DONE,
	SOCK_URGINLINE,
	SOCK_KEEPOPEN,
	SOCK_LINGER,
	SOCK_DESTROY,
	SOCK_BROADCAST,
	SOCK_TIMESTAMP,
	SOCK_ZAPPED,
	SOCK_USE_WRITE_QUEUE, /* whether to call sk->sk_ग_लिखो_space in sock_wमुक्त */
	SOCK_DBG, /* %SO_DEBUG setting */
	SOCK_RCVTSTAMP, /* %SO_TIMESTAMP setting */
	SOCK_RCVTSTAMPNS, /* %SO_TIMESTAMPNS setting */
	SOCK_LOCALROUTE, /* route locally only, %SO_DONTROUTE setting */
	SOCK_MEMALLOC, /* VM depends on this socket क्रम swapping */
	SOCK_TIMESTAMPING_RX_SOFTWARE,  /* %SOF_TIMESTAMPING_RX_SOFTWARE */
	SOCK_FASYNC, /* fasync() active */
	SOCK_RXQ_OVFL,
	SOCK_ZEROCOPY, /* buffers from userspace */
	SOCK_WIFI_STATUS, /* push wअगरi status to userspace */
	SOCK_NOFCS, /* Tell NIC not to करो the Ethernet FCS.
		     * Will use last 4 bytes of packet sent from
		     * user-space instead.
		     */
	SOCK_FILTER_LOCKED, /* Filter cannot be changed anymore */
	SOCK_SELECT_ERR_QUEUE, /* Wake select on error queue */
	SOCK_RCU_FREE, /* रुको rcu grace period in sk_deकाष्ठा() */
	SOCK_TXTIME,
	SOCK_XDP, /* XDP is attached */
	SOCK_TSTAMP_NEW, /* Indicates 64 bit बारtamps always */
पूर्ण;

#घोषणा SK_FLAGS_TIMESTAMP ((1UL << SOCK_TIMESTAMP) | (1UL << SOCK_TIMESTAMPING_RX_SOFTWARE))

अटल अंतरभूत व्योम sock_copy_flags(काष्ठा sock *nsk, काष्ठा sock *osk)
अणु
	nsk->sk_flags = osk->sk_flags;
पूर्ण

अटल अंतरभूत व्योम sock_set_flag(काष्ठा sock *sk, क्रमागत sock_flags flag)
अणु
	__set_bit(flag, &sk->sk_flags);
पूर्ण

अटल अंतरभूत व्योम sock_reset_flag(काष्ठा sock *sk, क्रमागत sock_flags flag)
अणु
	__clear_bit(flag, &sk->sk_flags);
पूर्ण

अटल अंतरभूत व्योम sock_valbool_flag(काष्ठा sock *sk, क्रमागत sock_flags bit,
				     पूर्णांक valbool)
अणु
	अगर (valbool)
		sock_set_flag(sk, bit);
	अन्यथा
		sock_reset_flag(sk, bit);
पूर्ण

अटल अंतरभूत bool sock_flag(स्थिर काष्ठा sock *sk, क्रमागत sock_flags flag)
अणु
	वापस test_bit(flag, &sk->sk_flags);
पूर्ण

#अगर_घोषित CONFIG_NET
DECLARE_STATIC_KEY_FALSE(meदो_स्मृति_socks_key);
अटल अंतरभूत पूर्णांक sk_meदो_स्मृति_socks(व्योम)
अणु
	वापस अटल_branch_unlikely(&meदो_स्मृति_socks_key);
पूर्ण

व्योम __receive_sock(काष्ठा file *file);
#अन्यथा

अटल अंतरभूत पूर्णांक sk_meदो_स्मृति_socks(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम __receive_sock(काष्ठा file *file)
अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत gfp_t sk_gfp_mask(स्थिर काष्ठा sock *sk, gfp_t gfp_mask)
अणु
	वापस gfp_mask | (sk->sk_allocation & __GFP_MEMALLOC);
पूर्ण

अटल अंतरभूत व्योम sk_acceptq_हटाओd(काष्ठा sock *sk)
अणु
	WRITE_ONCE(sk->sk_ack_backlog, sk->sk_ack_backlog - 1);
पूर्ण

अटल अंतरभूत व्योम sk_acceptq_added(काष्ठा sock *sk)
अणु
	WRITE_ONCE(sk->sk_ack_backlog, sk->sk_ack_backlog + 1);
पूर्ण

/* Note: If you think the test should be:
 *	वापस READ_ONCE(sk->sk_ack_backlog) >= READ_ONCE(sk->sk_max_ack_backlog);
 * Then please take a look at commit 64a146513f8f ("[NET]: Revert incorrect accept queue backlog changes.")
 */
अटल अंतरभूत bool sk_acceptq_is_full(स्थिर काष्ठा sock *sk)
अणु
	वापस READ_ONCE(sk->sk_ack_backlog) > READ_ONCE(sk->sk_max_ack_backlog);
पूर्ण

/*
 * Compute minimal मुक्त ग_लिखो space needed to queue new packets.
 */
अटल अंतरभूत पूर्णांक sk_stream_min_wspace(स्थिर काष्ठा sock *sk)
अणु
	वापस READ_ONCE(sk->sk_wmem_queued) >> 1;
पूर्ण

अटल अंतरभूत पूर्णांक sk_stream_wspace(स्थिर काष्ठा sock *sk)
अणु
	वापस READ_ONCE(sk->sk_sndbuf) - READ_ONCE(sk->sk_wmem_queued);
पूर्ण

अटल अंतरभूत व्योम sk_wmem_queued_add(काष्ठा sock *sk, पूर्णांक val)
अणु
	WRITE_ONCE(sk->sk_wmem_queued, sk->sk_wmem_queued + val);
पूर्ण

व्योम sk_stream_ग_लिखो_space(काष्ठा sock *sk);

/* OOB backlog add */
अटल अंतरभूत व्योम __sk_add_backlog(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	/* करोnt let skb dst not refcounted, we are going to leave rcu lock */
	skb_dst_क्रमce(skb);

	अगर (!sk->sk_backlog.tail)
		WRITE_ONCE(sk->sk_backlog.head, skb);
	अन्यथा
		sk->sk_backlog.tail->next = skb;

	WRITE_ONCE(sk->sk_backlog.tail, skb);
	skb->next = शून्य;
पूर्ण

/*
 * Take पूर्णांकo account size of receive queue and backlog queue
 * Do not take पूर्णांकo account this skb truesize,
 * to allow even a single big packet to come.
 */
अटल अंतरभूत bool sk_rcvqueues_full(स्थिर काष्ठा sock *sk, अचिन्हित पूर्णांक limit)
अणु
	अचिन्हित पूर्णांक qsize = sk->sk_backlog.len + atomic_पढ़ो(&sk->sk_rmem_alloc);

	वापस qsize > limit;
पूर्ण

/* The per-socket spinlock must be held here. */
अटल अंतरभूत __must_check पूर्णांक sk_add_backlog(काष्ठा sock *sk, काष्ठा sk_buff *skb,
					      अचिन्हित पूर्णांक limit)
अणु
	अगर (sk_rcvqueues_full(sk, limit))
		वापस -ENOBUFS;

	/*
	 * If the skb was allocated from pfmeदो_स्मृति reserves, only
	 * allow SOCK_MEMALLOC sockets to use it as this socket is
	 * helping मुक्त memory
	 */
	अगर (skb_pfmeदो_स्मृति(skb) && !sock_flag(sk, SOCK_MEMALLOC))
		वापस -ENOMEM;

	__sk_add_backlog(sk, skb);
	sk->sk_backlog.len += skb->truesize;
	वापस 0;
पूर्ण

पूर्णांक __sk_backlog_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb);

अटल अंतरभूत पूर्णांक sk_backlog_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अगर (sk_meदो_स्मृति_socks() && skb_pfmeदो_स्मृति(skb))
		वापस __sk_backlog_rcv(sk, skb);

	वापस sk->sk_backlog_rcv(sk, skb);
पूर्ण

अटल अंतरभूत व्योम sk_incoming_cpu_update(काष्ठा sock *sk)
अणु
	पूर्णांक cpu = raw_smp_processor_id();

	अगर (unlikely(READ_ONCE(sk->sk_incoming_cpu) != cpu))
		WRITE_ONCE(sk->sk_incoming_cpu, cpu);
पूर्ण

अटल अंतरभूत व्योम sock_rps_record_flow_hash(__u32 hash)
अणु
#अगर_घोषित CONFIG_RPS
	काष्ठा rps_sock_flow_table *sock_flow_table;

	rcu_पढ़ो_lock();
	sock_flow_table = rcu_dereference(rps_sock_flow_table);
	rps_record_sock_flow(sock_flow_table, hash);
	rcu_पढ़ो_unlock();
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम sock_rps_record_flow(स्थिर काष्ठा sock *sk)
अणु
#अगर_घोषित CONFIG_RPS
	अगर (अटल_branch_unlikely(&rfs_needed)) अणु
		/* Reading sk->sk_rxhash might incur an expensive cache line
		 * miss.
		 *
		 * TCP_ESTABLISHED करोes cover almost all states where RFS
		 * might be useful, and is cheaper [1] than testing :
		 *	IPv4: inet_sk(sk)->inet_daddr
		 * 	IPv6: ipv6_addr_any(&sk->sk_v6_daddr)
		 * OR	an additional socket flag
		 * [1] : sk_state and sk_prot are in the same cache line.
		 */
		अगर (sk->sk_state == TCP_ESTABLISHED)
			sock_rps_record_flow_hash(sk->sk_rxhash);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम sock_rps_save_rxhash(काष्ठा sock *sk,
					स्थिर काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_RPS
	अगर (unlikely(sk->sk_rxhash != skb->hash))
		sk->sk_rxhash = skb->hash;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम sock_rps_reset_rxhash(काष्ठा sock *sk)
अणु
#अगर_घोषित CONFIG_RPS
	sk->sk_rxhash = 0;
#पूर्ण_अगर
पूर्ण

#घोषणा sk_रुको_event(__sk, __समयo, __condition, __रुको)		\
	(अणु	पूर्णांक __rc;						\
		release_sock(__sk);					\
		__rc = __condition;					\
		अगर (!__rc) अणु						\
			*(__समयo) = रुको_woken(__रुको,			\
						TASK_INTERRUPTIBLE,	\
						*(__समयo));		\
		पूर्ण							\
		sched_annotate_sleep();					\
		lock_sock(__sk);					\
		__rc = __condition;					\
		__rc;							\
	पूर्ण)

पूर्णांक sk_stream_रुको_connect(काष्ठा sock *sk, दीर्घ *समयo_p);
पूर्णांक sk_stream_रुको_memory(काष्ठा sock *sk, दीर्घ *समयo_p);
व्योम sk_stream_रुको_बंद(काष्ठा sock *sk, दीर्घ समयo_p);
पूर्णांक sk_stream_error(काष्ठा sock *sk, पूर्णांक flags, पूर्णांक err);
व्योम sk_stream_समाप्त_queues(काष्ठा sock *sk);
व्योम sk_set_meदो_स्मृति(काष्ठा sock *sk);
व्योम sk_clear_meदो_स्मृति(काष्ठा sock *sk);

व्योम __sk_flush_backlog(काष्ठा sock *sk);

अटल अंतरभूत bool sk_flush_backlog(काष्ठा sock *sk)
अणु
	अगर (unlikely(READ_ONCE(sk->sk_backlog.tail))) अणु
		__sk_flush_backlog(sk);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक sk_रुको_data(काष्ठा sock *sk, दीर्घ *समयo, स्थिर काष्ठा sk_buff *skb);

काष्ठा request_sock_ops;
काष्ठा समयरुको_sock_ops;
काष्ठा inet_hashinfo;
काष्ठा raw_hashinfo;
काष्ठा smc_hashinfo;
काष्ठा module;
काष्ठा sk_psock;

/*
 * caches using SLAB_TYPESAFE_BY_RCU should let .next poपूर्णांकer from nulls nodes
 * un-modअगरied. Special care is taken when initializing object to zero.
 */
अटल अंतरभूत व्योम sk_prot_clear_nulls(काष्ठा sock *sk, पूर्णांक size)
अणु
	अगर (दुरत्व(काष्ठा sock, sk_node.next) != 0)
		स_रखो(sk, 0, दुरत्व(काष्ठा sock, sk_node.next));
	स_रखो(&sk->sk_node.pprev, 0,
	       size - दुरत्व(काष्ठा sock, sk_node.pprev));
पूर्ण

/* Networking protocol blocks we attach to sockets.
 * socket layer -> transport layer पूर्णांकerface
 */
काष्ठा proto अणु
	व्योम			(*बंद)(काष्ठा sock *sk,
					दीर्घ समयout);
	पूर्णांक			(*pre_connect)(काष्ठा sock *sk,
					काष्ठा sockaddr *uaddr,
					पूर्णांक addr_len);
	पूर्णांक			(*connect)(काष्ठा sock *sk,
					काष्ठा sockaddr *uaddr,
					पूर्णांक addr_len);
	पूर्णांक			(*disconnect)(काष्ठा sock *sk, पूर्णांक flags);

	काष्ठा sock *		(*accept)(काष्ठा sock *sk, पूर्णांक flags, पूर्णांक *err,
					  bool kern);

	पूर्णांक			(*ioctl)(काष्ठा sock *sk, पूर्णांक cmd,
					 अचिन्हित दीर्घ arg);
	पूर्णांक			(*init)(काष्ठा sock *sk);
	व्योम			(*destroy)(काष्ठा sock *sk);
	व्योम			(*shutकरोwn)(काष्ठा sock *sk, पूर्णांक how);
	पूर्णांक			(*setsockopt)(काष्ठा sock *sk, पूर्णांक level,
					पूर्णांक optname, sockptr_t optval,
					अचिन्हित पूर्णांक optlen);
	पूर्णांक			(*माला_लोockopt)(काष्ठा sock *sk, पूर्णांक level,
					पूर्णांक optname, अक्षर __user *optval,
					पूर्णांक __user *option);
	व्योम			(*keepalive)(काष्ठा sock *sk, पूर्णांक valbool);
#अगर_घोषित CONFIG_COMPAT
	पूर्णांक			(*compat_ioctl)(काष्ठा sock *sk,
					अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
#पूर्ण_अगर
	पूर्णांक			(*sendmsg)(काष्ठा sock *sk, काष्ठा msghdr *msg,
					   माप_प्रकार len);
	पूर्णांक			(*recvmsg)(काष्ठा sock *sk, काष्ठा msghdr *msg,
					   माप_प्रकार len, पूर्णांक noblock, पूर्णांक flags,
					   पूर्णांक *addr_len);
	पूर्णांक			(*sendpage)(काष्ठा sock *sk, काष्ठा page *page,
					पूर्णांक offset, माप_प्रकार size, पूर्णांक flags);
	पूर्णांक			(*bind)(काष्ठा sock *sk,
					काष्ठा sockaddr *addr, पूर्णांक addr_len);
	पूर्णांक			(*bind_add)(काष्ठा sock *sk,
					काष्ठा sockaddr *addr, पूर्णांक addr_len);

	पूर्णांक			(*backlog_rcv) (काष्ठा sock *sk,
						काष्ठा sk_buff *skb);
	bool			(*bpf_bypass_माला_लोockopt)(पूर्णांक level,
							 पूर्णांक optname);

	व्योम		(*release_cb)(काष्ठा sock *sk);

	/* Keeping track of sk's, looking them up, and port selection methods. */
	पूर्णांक			(*hash)(काष्ठा sock *sk);
	व्योम			(*unhash)(काष्ठा sock *sk);
	व्योम			(*rehash)(काष्ठा sock *sk);
	पूर्णांक			(*get_port)(काष्ठा sock *sk, अचिन्हित लघु snum);
#अगर_घोषित CONFIG_BPF_SYSCALL
	पूर्णांक			(*psock_update_sk_prot)(काष्ठा sock *sk,
							काष्ठा sk_psock *psock,
							bool restore);
#पूर्ण_अगर

	/* Keeping track of sockets in use */
#अगर_घोषित CONFIG_PROC_FS
	अचिन्हित पूर्णांक		inuse_idx;
#पूर्ण_अगर

	bool			(*stream_memory_मुक्त)(स्थिर काष्ठा sock *sk, पूर्णांक wake);
	bool			(*stream_memory_पढ़ो)(स्थिर काष्ठा sock *sk);
	/* Memory pressure */
	व्योम			(*enter_memory_pressure)(काष्ठा sock *sk);
	व्योम			(*leave_memory_pressure)(काष्ठा sock *sk);
	atomic_दीर्घ_t		*memory_allocated;	/* Current allocated memory. */
	काष्ठा percpu_counter	*sockets_allocated;	/* Current number of sockets. */
	/*
	 * Pressure flag: try to collapse.
	 * Technical note: it is used by multiple contexts non atomically.
	 * All the __sk_mem_schedule() is of this nature: accounting
	 * is strict, actions are advisory and have some latency.
	 */
	अचिन्हित दीर्घ		*memory_pressure;
	दीर्घ			*sysctl_mem;

	पूर्णांक			*sysctl_wmem;
	पूर्णांक			*sysctl_rmem;
	u32			sysctl_wmem_offset;
	u32			sysctl_rmem_offset;

	पूर्णांक			max_header;
	bool			no_स्वतःbind;

	काष्ठा kmem_cache	*slab;
	अचिन्हित पूर्णांक		obj_size;
	slab_flags_t		slab_flags;
	अचिन्हित पूर्णांक		useroffset;	/* Usercopy region offset */
	अचिन्हित पूर्णांक		usersize;	/* Usercopy region size */

	काष्ठा percpu_counter	*orphan_count;

	काष्ठा request_sock_ops	*rsk_prot;
	काष्ठा समयरुको_sock_ops *twsk_prot;

	जोड़ अणु
		काष्ठा inet_hashinfo	*hashinfo;
		काष्ठा udp_table	*udp_table;
		काष्ठा raw_hashinfo	*raw_hash;
		काष्ठा smc_hashinfo	*smc_hash;
	पूर्ण h;

	काष्ठा module		*owner;

	अक्षर			name[32];

	काष्ठा list_head	node;
#अगर_घोषित SOCK_REFCNT_DEBUG
	atomic_t		socks;
#पूर्ण_अगर
	पूर्णांक			(*diag_destroy)(काष्ठा sock *sk, पूर्णांक err);
पूर्ण __अक्रमomize_layout;

पूर्णांक proto_रेजिस्टर(काष्ठा proto *prot, पूर्णांक alloc_slab);
व्योम proto_unरेजिस्टर(काष्ठा proto *prot);
पूर्णांक sock_load_diag_module(पूर्णांक family, पूर्णांक protocol);

#अगर_घोषित SOCK_REFCNT_DEBUG
अटल अंतरभूत व्योम sk_refcnt_debug_inc(काष्ठा sock *sk)
अणु
	atomic_inc(&sk->sk_prot->socks);
पूर्ण

अटल अंतरभूत व्योम sk_refcnt_debug_dec(काष्ठा sock *sk)
अणु
	atomic_dec(&sk->sk_prot->socks);
	prपूर्णांकk(KERN_DEBUG "%s socket %p released, %d are still alive\n",
	       sk->sk_prot->name, sk, atomic_पढ़ो(&sk->sk_prot->socks));
पूर्ण

अटल अंतरभूत व्योम sk_refcnt_debug_release(स्थिर काष्ठा sock *sk)
अणु
	अगर (refcount_पढ़ो(&sk->sk_refcnt) != 1)
		prपूर्णांकk(KERN_DEBUG "Destruction of the %s socket %p delayed, refcnt=%d\n",
		       sk->sk_prot->name, sk, refcount_पढ़ो(&sk->sk_refcnt));
पूर्ण
#अन्यथा /* SOCK_REFCNT_DEBUG */
#घोषणा sk_refcnt_debug_inc(sk) करो अणु पूर्ण जबतक (0)
#घोषणा sk_refcnt_debug_dec(sk) करो अणु पूर्ण जबतक (0)
#घोषणा sk_refcnt_debug_release(sk) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* SOCK_REFCNT_DEBUG */

INसूचीECT_CALLABLE_DECLARE(bool tcp_stream_memory_मुक्त(स्थिर काष्ठा sock *sk, पूर्णांक wake));

अटल अंतरभूत bool __sk_stream_memory_मुक्त(स्थिर काष्ठा sock *sk, पूर्णांक wake)
अणु
	अगर (READ_ONCE(sk->sk_wmem_queued) >= READ_ONCE(sk->sk_sndbuf))
		वापस false;

#अगर_घोषित CONFIG_INET
	वापस sk->sk_prot->stream_memory_मुक्त ?
		INसूचीECT_CALL_1(sk->sk_prot->stream_memory_मुक्त,
			        tcp_stream_memory_मुक्त,
				sk, wake) : true;
#अन्यथा
	वापस sk->sk_prot->stream_memory_मुक्त ?
		sk->sk_prot->stream_memory_मुक्त(sk, wake) : true;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool sk_stream_memory_मुक्त(स्थिर काष्ठा sock *sk)
अणु
	वापस __sk_stream_memory_मुक्त(sk, 0);
पूर्ण

अटल अंतरभूत bool __sk_stream_is_ग_लिखोable(स्थिर काष्ठा sock *sk, पूर्णांक wake)
अणु
	वापस sk_stream_wspace(sk) >= sk_stream_min_wspace(sk) &&
	       __sk_stream_memory_मुक्त(sk, wake);
पूर्ण

अटल अंतरभूत bool sk_stream_is_ग_लिखोable(स्थिर काष्ठा sock *sk)
अणु
	वापस __sk_stream_is_ग_लिखोable(sk, 0);
पूर्ण

अटल अंतरभूत पूर्णांक sk_under_cgroup_hierarchy(काष्ठा sock *sk,
					    काष्ठा cgroup *ancestor)
अणु
#अगर_घोषित CONFIG_SOCK_CGROUP_DATA
	वापस cgroup_is_descendant(sock_cgroup_ptr(&sk->sk_cgrp_data),
				    ancestor);
#अन्यथा
	वापस -ENOTSUPP;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool sk_has_memory_pressure(स्थिर काष्ठा sock *sk)
अणु
	वापस sk->sk_prot->memory_pressure != शून्य;
पूर्ण

अटल अंतरभूत bool sk_under_memory_pressure(स्थिर काष्ठा sock *sk)
अणु
	अगर (!sk->sk_prot->memory_pressure)
		वापस false;

	अगर (mem_cgroup_sockets_enabled && sk->sk_memcg &&
	    mem_cgroup_under_socket_pressure(sk->sk_memcg))
		वापस true;

	वापस !!*sk->sk_prot->memory_pressure;
पूर्ण

अटल अंतरभूत दीर्घ
sk_memory_allocated(स्थिर काष्ठा sock *sk)
अणु
	वापस atomic_दीर्घ_पढ़ो(sk->sk_prot->memory_allocated);
पूर्ण

अटल अंतरभूत दीर्घ
sk_memory_allocated_add(काष्ठा sock *sk, पूर्णांक amt)
अणु
	वापस atomic_दीर्घ_add_वापस(amt, sk->sk_prot->memory_allocated);
पूर्ण

अटल अंतरभूत व्योम
sk_memory_allocated_sub(काष्ठा sock *sk, पूर्णांक amt)
अणु
	atomic_दीर्घ_sub(amt, sk->sk_prot->memory_allocated);
पूर्ण

#घोषणा SK_ALLOC_PERCPU_COUNTER_BATCH 16

अटल अंतरभूत व्योम sk_sockets_allocated_dec(काष्ठा sock *sk)
अणु
	percpu_counter_add_batch(sk->sk_prot->sockets_allocated, -1,
				 SK_ALLOC_PERCPU_COUNTER_BATCH);
पूर्ण

अटल अंतरभूत व्योम sk_sockets_allocated_inc(काष्ठा sock *sk)
अणु
	percpu_counter_add_batch(sk->sk_prot->sockets_allocated, 1,
				 SK_ALLOC_PERCPU_COUNTER_BATCH);
पूर्ण

अटल अंतरभूत u64
sk_sockets_allocated_पढ़ो_positive(काष्ठा sock *sk)
अणु
	वापस percpu_counter_पढ़ो_positive(sk->sk_prot->sockets_allocated);
पूर्ण

अटल अंतरभूत पूर्णांक
proto_sockets_allocated_sum_positive(काष्ठा proto *prot)
अणु
	वापस percpu_counter_sum_positive(prot->sockets_allocated);
पूर्ण

अटल अंतरभूत दीर्घ
proto_memory_allocated(काष्ठा proto *prot)
अणु
	वापस atomic_दीर्घ_पढ़ो(prot->memory_allocated);
पूर्ण

अटल अंतरभूत bool
proto_memory_pressure(काष्ठा proto *prot)
अणु
	अगर (!prot->memory_pressure)
		वापस false;
	वापस !!*prot->memory_pressure;
पूर्ण


#अगर_घोषित CONFIG_PROC_FS
/* Called with local bh disabled */
व्योम sock_prot_inuse_add(काष्ठा net *net, काष्ठा proto *prot, पूर्णांक inc);
पूर्णांक sock_prot_inuse_get(काष्ठा net *net, काष्ठा proto *proto);
पूर्णांक sock_inuse_get(काष्ठा net *net);
#अन्यथा
अटल अंतरभूत व्योम sock_prot_inuse_add(काष्ठा net *net, काष्ठा proto *prot,
		पूर्णांक inc)
अणु
पूर्ण
#पूर्ण_अगर


/* With per-bucket locks this operation is not-atomic, so that
 * this version is not worse.
 */
अटल अंतरभूत पूर्णांक __sk_prot_rehash(काष्ठा sock *sk)
अणु
	sk->sk_prot->unhash(sk);
	वापस sk->sk_prot->hash(sk);
पूर्ण

/* About 10 seconds */
#घोषणा SOCK_DESTROY_TIME (10*HZ)

/* Sockets 0-1023 can't be bound to unless you are superuser */
#घोषणा PROT_SOCK	1024

#घोषणा SHUTDOWN_MASK	3
#घोषणा RCV_SHUTDOWN	1
#घोषणा SEND_SHUTDOWN	2

#घोषणा SOCK_SNDBUF_LOCK	1
#घोषणा SOCK_RCVBUF_LOCK	2
#घोषणा SOCK_BINDADDR_LOCK	4
#घोषणा SOCK_BINDPORT_LOCK	8

काष्ठा socket_alloc अणु
	काष्ठा socket socket;
	काष्ठा inode vfs_inode;
पूर्ण;

अटल अंतरभूत काष्ठा socket *SOCKET_I(काष्ठा inode *inode)
अणु
	वापस &container_of(inode, काष्ठा socket_alloc, vfs_inode)->socket;
पूर्ण

अटल अंतरभूत काष्ठा inode *SOCK_INODE(काष्ठा socket *socket)
अणु
	वापस &container_of(socket, काष्ठा socket_alloc, socket)->vfs_inode;
पूर्ण

/*
 * Functions क्रम memory accounting
 */
पूर्णांक __sk_mem_उठाओ_allocated(काष्ठा sock *sk, पूर्णांक size, पूर्णांक amt, पूर्णांक kind);
पूर्णांक __sk_mem_schedule(काष्ठा sock *sk, पूर्णांक size, पूर्णांक kind);
व्योम __sk_mem_reduce_allocated(काष्ठा sock *sk, पूर्णांक amount);
व्योम __sk_mem_reclaim(काष्ठा sock *sk, पूर्णांक amount);

/* We used to have PAGE_SIZE here, but प्रणालीs with 64KB pages
 * करो not necessarily have 16x समय more memory than 4KB ones.
 */
#घोषणा SK_MEM_QUANTUM 4096
#घोषणा SK_MEM_QUANTUM_SHIFT ilog2(SK_MEM_QUANTUM)
#घोषणा SK_MEM_SEND	0
#घोषणा SK_MEM_RECV	1

/* sysctl_mem values are in pages, we convert them in SK_MEM_QUANTUM units */
अटल अंतरभूत दीर्घ sk_prot_mem_limits(स्थिर काष्ठा sock *sk, पूर्णांक index)
अणु
	दीर्घ val = sk->sk_prot->sysctl_mem[index];

#अगर PAGE_SIZE > SK_MEM_QUANTUM
	val <<= PAGE_SHIFT - SK_MEM_QUANTUM_SHIFT;
#या_अगर PAGE_SIZE < SK_MEM_QUANTUM
	val >>= SK_MEM_QUANTUM_SHIFT - PAGE_SHIFT;
#पूर्ण_अगर
	वापस val;
पूर्ण

अटल अंतरभूत पूर्णांक sk_mem_pages(पूर्णांक amt)
अणु
	वापस (amt + SK_MEM_QUANTUM - 1) >> SK_MEM_QUANTUM_SHIFT;
पूर्ण

अटल अंतरभूत bool sk_has_account(काष्ठा sock *sk)
अणु
	/* वापस true अगर protocol supports memory accounting */
	वापस !!sk->sk_prot->memory_allocated;
पूर्ण

अटल अंतरभूत bool sk_wmem_schedule(काष्ठा sock *sk, पूर्णांक size)
अणु
	अगर (!sk_has_account(sk))
		वापस true;
	वापस size <= sk->sk_क्रमward_alloc ||
		__sk_mem_schedule(sk, size, SK_MEM_SEND);
पूर्ण

अटल अंतरभूत bool
sk_rmem_schedule(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक size)
अणु
	अगर (!sk_has_account(sk))
		वापस true;
	वापस size <= sk->sk_क्रमward_alloc ||
		__sk_mem_schedule(sk, size, SK_MEM_RECV) ||
		skb_pfmeदो_स्मृति(skb);
पूर्ण

अटल अंतरभूत व्योम sk_mem_reclaim(काष्ठा sock *sk)
अणु
	अगर (!sk_has_account(sk))
		वापस;
	अगर (sk->sk_क्रमward_alloc >= SK_MEM_QUANTUM)
		__sk_mem_reclaim(sk, sk->sk_क्रमward_alloc);
पूर्ण

अटल अंतरभूत व्योम sk_mem_reclaim_partial(काष्ठा sock *sk)
अणु
	अगर (!sk_has_account(sk))
		वापस;
	अगर (sk->sk_क्रमward_alloc > SK_MEM_QUANTUM)
		__sk_mem_reclaim(sk, sk->sk_क्रमward_alloc - 1);
पूर्ण

अटल अंतरभूत व्योम sk_mem_अक्षरge(काष्ठा sock *sk, पूर्णांक size)
अणु
	अगर (!sk_has_account(sk))
		वापस;
	sk->sk_क्रमward_alloc -= size;
पूर्ण

अटल अंतरभूत व्योम sk_mem_unअक्षरge(काष्ठा sock *sk, पूर्णांक size)
अणु
	अगर (!sk_has_account(sk))
		वापस;
	sk->sk_क्रमward_alloc += size;

	/* Aव्योम a possible overflow.
	 * TCP send queues can make this happen, अगर sk_mem_reclaim()
	 * is not called and more than 2 GBytes are released at once.
	 *
	 * If we reach 2 MBytes, reclaim 1 MBytes right now, there is
	 * no need to hold that much क्रमward allocation anyway.
	 */
	अगर (unlikely(sk->sk_क्रमward_alloc >= 1 << 21))
		__sk_mem_reclaim(sk, 1 << 20);
पूर्ण

DECLARE_STATIC_KEY_FALSE(tcp_tx_skb_cache_key);
अटल अंतरभूत व्योम sk_wmem_मुक्त_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	sk_wmem_queued_add(sk, -skb->truesize);
	sk_mem_unअक्षरge(sk, skb->truesize);
	अगर (अटल_branch_unlikely(&tcp_tx_skb_cache_key) &&
	    !sk->sk_tx_skb_cache && !skb_cloned(skb)) अणु
		skb_ext_reset(skb);
		skb_zcopy_clear(skb, true);
		sk->sk_tx_skb_cache = skb;
		वापस;
	पूर्ण
	__kमुक्त_skb(skb);
पूर्ण

अटल अंतरभूत व्योम sock_release_ownership(काष्ठा sock *sk)
अणु
	अगर (sk->sk_lock.owned) अणु
		sk->sk_lock.owned = 0;

		/* The sk_lock has mutex_unlock() semantics: */
		mutex_release(&sk->sk_lock.dep_map, _RET_IP_);
	पूर्ण
पूर्ण

/*
 * Macro so as to not evaluate some arguments when
 * lockdep is not enabled.
 *
 * Mark both the sk_lock and the sk_lock.slock as a
 * per-address-family lock class.
 */
#घोषणा sock_lock_init_class_and_name(sk, sname, skey, name, key)	\
करो अणु									\
	sk->sk_lock.owned = 0;						\
	init_रुकोqueue_head(&sk->sk_lock.wq);				\
	spin_lock_init(&(sk)->sk_lock.slock);				\
	debug_check_no_locks_मुक्तd((व्योम *)&(sk)->sk_lock,		\
			माप((sk)->sk_lock));				\
	lockdep_set_class_and_name(&(sk)->sk_lock.slock,		\
				(skey), (sname));				\
	lockdep_init_map(&(sk)->sk_lock.dep_map, (name), (key), 0);	\
पूर्ण जबतक (0)

अटल अंतरभूत bool lockdep_sock_is_held(स्थिर काष्ठा sock *sk)
अणु
	वापस lockdep_is_held(&sk->sk_lock) ||
	       lockdep_is_held(&sk->sk_lock.slock);
पूर्ण

व्योम lock_sock_nested(काष्ठा sock *sk, पूर्णांक subclass);

अटल अंतरभूत व्योम lock_sock(काष्ठा sock *sk)
अणु
	lock_sock_nested(sk, 0);
पूर्ण

व्योम __lock_sock(काष्ठा sock *sk);
व्योम __release_sock(काष्ठा sock *sk);
व्योम release_sock(काष्ठा sock *sk);

/* BH context may only use the following locking पूर्णांकerface. */
#घोषणा bh_lock_sock(__sk)	spin_lock(&((__sk)->sk_lock.slock))
#घोषणा bh_lock_sock_nested(__sk) \
				spin_lock_nested(&((__sk)->sk_lock.slock), \
				SINGLE_DEPTH_NESTING)
#घोषणा bh_unlock_sock(__sk)	spin_unlock(&((__sk)->sk_lock.slock))

bool lock_sock_fast(काष्ठा sock *sk) __acquires(&sk->sk_lock.slock);

/**
 * unlock_sock_fast - complement of lock_sock_fast
 * @sk: socket
 * @slow: slow mode
 *
 * fast unlock socket क्रम user context.
 * If slow mode is on, we call regular release_sock()
 */
अटल अंतरभूत व्योम unlock_sock_fast(काष्ठा sock *sk, bool slow)
	__releases(&sk->sk_lock.slock)
अणु
	अगर (slow) अणु
		release_sock(sk);
		__release(&sk->sk_lock.slock);
	पूर्ण अन्यथा अणु
		spin_unlock_bh(&sk->sk_lock.slock);
	पूर्ण
पूर्ण

/* Used by processes to "lock" a socket state, so that
 * पूर्णांकerrupts and bottom half handlers won't change it
 * from under us. It essentially blocks any incoming
 * packets, so that we won't get any new data or any
 * packets that change the state of the socket.
 *
 * While locked, BH processing will add new packets to
 * the backlog queue.  This queue is processed by the
 * owner of the socket lock right beक्रमe it is released.
 *
 * Since ~2.3.5 it is also exclusive sleep lock serializing
 * accesses from user process context.
 */

अटल अंतरभूत व्योम sock_owned_by_me(स्थिर काष्ठा sock *sk)
अणु
#अगर_घोषित CONFIG_LOCKDEP
	WARN_ON_ONCE(!lockdep_sock_is_held(sk) && debug_locks);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool sock_owned_by_user(स्थिर काष्ठा sock *sk)
अणु
	sock_owned_by_me(sk);
	वापस sk->sk_lock.owned;
पूर्ण

अटल अंतरभूत bool sock_owned_by_user_nocheck(स्थिर काष्ठा sock *sk)
अणु
	वापस sk->sk_lock.owned;
पूर्ण

/* no reclassअगरication जबतक locks are held */
अटल अंतरभूत bool sock_allow_reclassअगरication(स्थिर काष्ठा sock *csk)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)csk;

	वापस !sk->sk_lock.owned && !spin_is_locked(&sk->sk_lock.slock);
पूर्ण

काष्ठा sock *sk_alloc(काष्ठा net *net, पूर्णांक family, gfp_t priority,
		      काष्ठा proto *prot, पूर्णांक kern);
व्योम sk_मुक्त(काष्ठा sock *sk);
व्योम sk_deकाष्ठा(काष्ठा sock *sk);
काष्ठा sock *sk_clone_lock(स्थिर काष्ठा sock *sk, स्थिर gfp_t priority);
व्योम sk_मुक्त_unlock_clone(काष्ठा sock *sk);

काष्ठा sk_buff *sock_wदो_स्मृति(काष्ठा sock *sk, अचिन्हित दीर्घ size, पूर्णांक क्रमce,
			     gfp_t priority);
व्योम __sock_wमुक्त(काष्ठा sk_buff *skb);
व्योम sock_wमुक्त(काष्ठा sk_buff *skb);
काष्ठा sk_buff *sock_oदो_स्मृति(काष्ठा sock *sk, अचिन्हित दीर्घ size,
			     gfp_t priority);
व्योम skb_orphan_partial(काष्ठा sk_buff *skb);
व्योम sock_rमुक्त(काष्ठा sk_buff *skb);
व्योम sock_eमुक्त(काष्ठा sk_buff *skb);
#अगर_घोषित CONFIG_INET
व्योम sock_edemux(काष्ठा sk_buff *skb);
व्योम sock_pमुक्त(काष्ठा sk_buff *skb);
#अन्यथा
#घोषणा sock_edemux sock_eमुक्त
#पूर्ण_अगर

पूर्णांक sock_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक op,
		    sockptr_t optval, अचिन्हित पूर्णांक optlen);

पूर्णांक sock_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक op,
		    अक्षर __user *optval, पूर्णांक __user *optlen);
पूर्णांक sock_gettstamp(काष्ठा socket *sock, व्योम __user *userstamp,
		   bool समयval, bool समय32);
काष्ठा sk_buff *sock_alloc_send_skb(काष्ठा sock *sk, अचिन्हित दीर्घ size,
				    पूर्णांक noblock, पूर्णांक *errcode);
काष्ठा sk_buff *sock_alloc_send_pskb(काष्ठा sock *sk, अचिन्हित दीर्घ header_len,
				     अचिन्हित दीर्घ data_len, पूर्णांक noblock,
				     पूर्णांक *errcode, पूर्णांक max_page_order);
व्योम *sock_kदो_स्मृति(काष्ठा sock *sk, पूर्णांक size, gfp_t priority);
व्योम sock_kमुक्त_s(काष्ठा sock *sk, व्योम *mem, पूर्णांक size);
व्योम sock_kzमुक्त_s(काष्ठा sock *sk, व्योम *mem, पूर्णांक size);
व्योम sk_send_sigurg(काष्ठा sock *sk);

काष्ठा sockcm_cookie अणु
	u64 transmit_समय;
	u32 mark;
	u16 tsflags;
पूर्ण;

अटल अंतरभूत व्योम sockcm_init(काष्ठा sockcm_cookie *sockc,
			       स्थिर काष्ठा sock *sk)
अणु
	*sockc = (काष्ठा sockcm_cookie) अणु .tsflags = sk->sk_tsflags पूर्ण;
पूर्ण

पूर्णांक __sock_cmsg_send(काष्ठा sock *sk, काष्ठा msghdr *msg, काष्ठा cmsghdr *cmsg,
		     काष्ठा sockcm_cookie *sockc);
पूर्णांक sock_cmsg_send(काष्ठा sock *sk, काष्ठा msghdr *msg,
		   काष्ठा sockcm_cookie *sockc);

/*
 * Functions to fill in entries in काष्ठा proto_ops when a protocol
 * करोes not implement a particular function.
 */
पूर्णांक sock_no_bind(काष्ठा socket *, काष्ठा sockaddr *, पूर्णांक);
पूर्णांक sock_no_connect(काष्ठा socket *, काष्ठा sockaddr *, पूर्णांक, पूर्णांक);
पूर्णांक sock_no_socketpair(काष्ठा socket *, काष्ठा socket *);
पूर्णांक sock_no_accept(काष्ठा socket *, काष्ठा socket *, पूर्णांक, bool);
पूर्णांक sock_no_getname(काष्ठा socket *, काष्ठा sockaddr *, पूर्णांक);
पूर्णांक sock_no_ioctl(काष्ठा socket *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
पूर्णांक sock_no_listen(काष्ठा socket *, पूर्णांक);
पूर्णांक sock_no_shutकरोwn(काष्ठा socket *, पूर्णांक);
पूर्णांक sock_no_sendmsg(काष्ठा socket *, काष्ठा msghdr *, माप_प्रकार);
पूर्णांक sock_no_sendmsg_locked(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len);
पूर्णांक sock_no_recvmsg(काष्ठा socket *, काष्ठा msghdr *, माप_प्रकार, पूर्णांक);
पूर्णांक sock_no_mmap(काष्ठा file *file, काष्ठा socket *sock,
		 काष्ठा vm_area_काष्ठा *vma);
sमाप_प्रकार sock_no_sendpage(काष्ठा socket *sock, काष्ठा page *page, पूर्णांक offset,
			 माप_प्रकार size, पूर्णांक flags);
sमाप_प्रकार sock_no_sendpage_locked(काष्ठा sock *sk, काष्ठा page *page,
				पूर्णांक offset, माप_प्रकार size, पूर्णांक flags);

/*
 * Functions to fill in entries in काष्ठा proto_ops when a protocol
 * uses the inet style.
 */
पूर्णांक sock_common_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
				  अक्षर __user *optval, पूर्णांक __user *optlen);
पूर्णांक sock_common_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size,
			पूर्णांक flags);
पूर्णांक sock_common_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			   sockptr_t optval, अचिन्हित पूर्णांक optlen);

व्योम sk_common_release(काष्ठा sock *sk);

/*
 *	Default socket callbacks and setup code
 */

/* Initialise core socket variables */
व्योम sock_init_data(काष्ठा socket *sock, काष्ठा sock *sk);

/*
 * Socket reference counting postulates.
 *
 * * Each user of socket SHOULD hold a reference count.
 * * Each access poपूर्णांक to socket (an hash table bucket, reference from a list,
 *   running समयr, skb in flight MUST hold a reference count.
 * * When reference count hits 0, it means it will never increase back.
 * * When reference count hits 0, it means that no references from
 *   outside exist to this socket and current process on current CPU
 *   is last user and may/should destroy this socket.
 * * sk_मुक्त is called from any context: process, BH, IRQ. When
 *   it is called, socket has no references from outside -> sk_मुक्त
 *   may release descendant resources allocated by the socket, but
 *   to the समय when it is called, socket is NOT referenced by any
 *   hash tables, lists etc.
 * * Packets, delivered from outside (from network or from another process)
 *   and enqueued on receive/error queues SHOULD NOT grab reference count,
 *   when they sit in queue. Otherwise, packets will leak to hole, when
 *   socket is looked up by one cpu and unhasing is made by another CPU.
 *   It is true क्रम udp/raw, netlink (leak to receive and error queues), tcp
 *   (leak to backlog). Packet socket करोes all the processing inside
 *   BR_NETPROTO_LOCK, so that it has not this race condition. UNIX sockets
 *   use separate SMP lock, so that they are prone too.
 */

/* Ungrab socket and destroy it, अगर it was the last reference. */
अटल अंतरभूत व्योम sock_put(काष्ठा sock *sk)
अणु
	अगर (refcount_dec_and_test(&sk->sk_refcnt))
		sk_मुक्त(sk);
पूर्ण
/* Generic version of sock_put(), dealing with all sockets
 * (TCP_TIMEWAIT, TCP_NEW_SYN_RECV, ESTABLISHED...)
 */
व्योम sock_gen_put(काष्ठा sock *sk);

पूर्णांक __sk_receive_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb, स्थिर पूर्णांक nested,
		     अचिन्हित पूर्णांक trim_cap, bool refcounted);
अटल अंतरभूत पूर्णांक sk_receive_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				 स्थिर पूर्णांक nested)
अणु
	वापस __sk_receive_skb(sk, skb, nested, 1, true);
पूर्ण

अटल अंतरभूत व्योम sk_tx_queue_set(काष्ठा sock *sk, पूर्णांक tx_queue)
अणु
	/* sk_tx_queue_mapping accept only upto a 16-bit value */
	अगर (WARN_ON_ONCE((अचिन्हित लघु)tx_queue >= अच_लघु_उच्च))
		वापस;
	sk->sk_tx_queue_mapping = tx_queue;
पूर्ण

#घोषणा NO_QUEUE_MAPPING	अच_लघु_उच्च

अटल अंतरभूत व्योम sk_tx_queue_clear(काष्ठा sock *sk)
अणु
	sk->sk_tx_queue_mapping = NO_QUEUE_MAPPING;
पूर्ण

अटल अंतरभूत पूर्णांक sk_tx_queue_get(स्थिर काष्ठा sock *sk)
अणु
	अगर (sk && sk->sk_tx_queue_mapping != NO_QUEUE_MAPPING)
		वापस sk->sk_tx_queue_mapping;

	वापस -1;
पूर्ण

अटल अंतरभूत व्योम sk_rx_queue_set(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_SOCK_RX_QUEUE_MAPPING
	अगर (skb_rx_queue_recorded(skb)) अणु
		u16 rx_queue = skb_get_rx_queue(skb);

		अगर (WARN_ON_ONCE(rx_queue == NO_QUEUE_MAPPING))
			वापस;

		sk->sk_rx_queue_mapping = rx_queue;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम sk_rx_queue_clear(काष्ठा sock *sk)
अणु
#अगर_घोषित CONFIG_SOCK_RX_QUEUE_MAPPING
	sk->sk_rx_queue_mapping = NO_QUEUE_MAPPING;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक sk_rx_queue_get(स्थिर काष्ठा sock *sk)
अणु
#अगर_घोषित CONFIG_SOCK_RX_QUEUE_MAPPING
	अगर (sk && sk->sk_rx_queue_mapping != NO_QUEUE_MAPPING)
		वापस sk->sk_rx_queue_mapping;
#पूर्ण_अगर

	वापस -1;
पूर्ण

अटल अंतरभूत व्योम sk_set_socket(काष्ठा sock *sk, काष्ठा socket *sock)
अणु
	sk->sk_socket = sock;
पूर्ण

अटल अंतरभूत रुको_queue_head_t *sk_sleep(काष्ठा sock *sk)
अणु
	BUILD_BUG_ON(दुरत्व(काष्ठा socket_wq, रुको) != 0);
	वापस &rcu_dereference_raw(sk->sk_wq)->रुको;
पूर्ण
/* Detach socket from process context.
 * Announce socket dead, detach it from रुको queue and inode.
 * Note that parent inode held reference count on this काष्ठा sock,
 * we करो not release it in this function, because protocol
 * probably wants some additional cleanups or even continuing
 * to work with this socket (TCP).
 */
अटल अंतरभूत व्योम sock_orphan(काष्ठा sock *sk)
अणु
	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	sock_set_flag(sk, SOCK_DEAD);
	sk_set_socket(sk, शून्य);
	sk->sk_wq  = शून्य;
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल अंतरभूत व्योम sock_graft(काष्ठा sock *sk, काष्ठा socket *parent)
अणु
	WARN_ON(parent->sk);
	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	rcu_assign_poपूर्णांकer(sk->sk_wq, &parent->wq);
	parent->sk = sk;
	sk_set_socket(sk, parent);
	sk->sk_uid = SOCK_INODE(parent)->i_uid;
	security_sock_graft(sk, parent);
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

kuid_t sock_i_uid(काष्ठा sock *sk);
अचिन्हित दीर्घ sock_i_ino(काष्ठा sock *sk);

अटल अंतरभूत kuid_t sock_net_uid(स्थिर काष्ठा net *net, स्थिर काष्ठा sock *sk)
अणु
	वापस sk ? sk->sk_uid : make_kuid(net->user_ns, 0);
पूर्ण

अटल अंतरभूत u32 net_tx_rndhash(व्योम)
अणु
	u32 v = pअक्रमom_u32();

	वापस v ?: 1;
पूर्ण

अटल अंतरभूत व्योम sk_set_txhash(काष्ठा sock *sk)
अणु
	/* This pairs with READ_ONCE() in skb_set_hash_from_sk() */
	WRITE_ONCE(sk->sk_txhash, net_tx_rndhash());
पूर्ण

अटल अंतरभूत bool sk_rethink_txhash(काष्ठा sock *sk)
अणु
	अगर (sk->sk_txhash) अणु
		sk_set_txhash(sk);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा dst_entry *
__sk_dst_get(काष्ठा sock *sk)
अणु
	वापस rcu_dereference_check(sk->sk_dst_cache,
				     lockdep_sock_is_held(sk));
पूर्ण

अटल अंतरभूत काष्ठा dst_entry *
sk_dst_get(काष्ठा sock *sk)
अणु
	काष्ठा dst_entry *dst;

	rcu_पढ़ो_lock();
	dst = rcu_dereference(sk->sk_dst_cache);
	अगर (dst && !atomic_inc_not_zero(&dst->__refcnt))
		dst = शून्य;
	rcu_पढ़ो_unlock();
	वापस dst;
पूर्ण

अटल अंतरभूत व्योम __dst_negative_advice(काष्ठा sock *sk)
अणु
	काष्ठा dst_entry *ndst, *dst = __sk_dst_get(sk);

	अगर (dst && dst->ops->negative_advice) अणु
		ndst = dst->ops->negative_advice(dst);

		अगर (ndst != dst) अणु
			rcu_assign_poपूर्णांकer(sk->sk_dst_cache, ndst);
			sk_tx_queue_clear(sk);
			sk->sk_dst_pending_confirm = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम dst_negative_advice(काष्ठा sock *sk)
अणु
	sk_rethink_txhash(sk);
	__dst_negative_advice(sk);
पूर्ण

अटल अंतरभूत व्योम
__sk_dst_set(काष्ठा sock *sk, काष्ठा dst_entry *dst)
अणु
	काष्ठा dst_entry *old_dst;

	sk_tx_queue_clear(sk);
	sk->sk_dst_pending_confirm = 0;
	old_dst = rcu_dereference_रक्षित(sk->sk_dst_cache,
					    lockdep_sock_is_held(sk));
	rcu_assign_poपूर्णांकer(sk->sk_dst_cache, dst);
	dst_release(old_dst);
पूर्ण

अटल अंतरभूत व्योम
sk_dst_set(काष्ठा sock *sk, काष्ठा dst_entry *dst)
अणु
	काष्ठा dst_entry *old_dst;

	sk_tx_queue_clear(sk);
	sk->sk_dst_pending_confirm = 0;
	old_dst = xchg((__क्रमce काष्ठा dst_entry **)&sk->sk_dst_cache, dst);
	dst_release(old_dst);
पूर्ण

अटल अंतरभूत व्योम
__sk_dst_reset(काष्ठा sock *sk)
अणु
	__sk_dst_set(sk, शून्य);
पूर्ण

अटल अंतरभूत व्योम
sk_dst_reset(काष्ठा sock *sk)
अणु
	sk_dst_set(sk, शून्य);
पूर्ण

काष्ठा dst_entry *__sk_dst_check(काष्ठा sock *sk, u32 cookie);

काष्ठा dst_entry *sk_dst_check(काष्ठा sock *sk, u32 cookie);

अटल अंतरभूत व्योम sk_dst_confirm(काष्ठा sock *sk)
अणु
	अगर (!READ_ONCE(sk->sk_dst_pending_confirm))
		WRITE_ONCE(sk->sk_dst_pending_confirm, 1);
पूर्ण

अटल अंतरभूत व्योम sock_confirm_neigh(काष्ठा sk_buff *skb, काष्ठा neighbour *n)
अणु
	अगर (skb_get_dst_pending_confirm(skb)) अणु
		काष्ठा sock *sk = skb->sk;
		अचिन्हित दीर्घ now = jअगरfies;

		/* aव्योम dirtying neighbour */
		अगर (READ_ONCE(n->confirmed) != now)
			WRITE_ONCE(n->confirmed, now);
		अगर (sk && READ_ONCE(sk->sk_dst_pending_confirm))
			WRITE_ONCE(sk->sk_dst_pending_confirm, 0);
	पूर्ण
पूर्ण

bool sk_mc_loop(काष्ठा sock *sk);

अटल अंतरभूत bool sk_can_gso(स्थिर काष्ठा sock *sk)
अणु
	वापस net_gso_ok(sk->sk_route_caps, sk->sk_gso_type);
पूर्ण

व्योम sk_setup_caps(काष्ठा sock *sk, काष्ठा dst_entry *dst);

अटल अंतरभूत व्योम sk_nocaps_add(काष्ठा sock *sk, netdev_features_t flags)
अणु
	sk->sk_route_nocaps |= flags;
	sk->sk_route_caps &= ~flags;
पूर्ण

अटल अंतरभूत पूर्णांक skb_करो_copy_data_nocache(काष्ठा sock *sk, काष्ठा sk_buff *skb,
					   काष्ठा iov_iter *from, अक्षर *to,
					   पूर्णांक copy, पूर्णांक offset)
अणु
	अगर (skb->ip_summed == CHECKSUM_NONE) अणु
		__wsum csum = 0;
		अगर (!csum_and_copy_from_iter_full(to, copy, &csum, from))
			वापस -EFAULT;
		skb->csum = csum_block_add(skb->csum, csum, offset);
	पूर्ण अन्यथा अगर (sk->sk_route_caps & NETIF_F_NOCACHE_COPY) अणु
		अगर (!copy_from_iter_full_nocache(to, copy, from))
			वापस -EFAULT;
	पूर्ण अन्यथा अगर (!copy_from_iter_full(to, copy, from))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक skb_add_data_nocache(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				       काष्ठा iov_iter *from, पूर्णांक copy)
अणु
	पूर्णांक err, offset = skb->len;

	err = skb_करो_copy_data_nocache(sk, skb, from, skb_put(skb, copy),
				       copy, offset);
	अगर (err)
		__skb_trim(skb, offset);

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक skb_copy_to_page_nocache(काष्ठा sock *sk, काष्ठा iov_iter *from,
					   काष्ठा sk_buff *skb,
					   काष्ठा page *page,
					   पूर्णांक off, पूर्णांक copy)
अणु
	पूर्णांक err;

	err = skb_करो_copy_data_nocache(sk, skb, from, page_address(page) + off,
				       copy, skb->len);
	अगर (err)
		वापस err;

	skb->len	     += copy;
	skb->data_len	     += copy;
	skb->truesize	     += copy;
	sk_wmem_queued_add(sk, copy);
	sk_mem_अक्षरge(sk, copy);
	वापस 0;
पूर्ण

/**
 * sk_wmem_alloc_get - वापसs ग_लिखो allocations
 * @sk: socket
 *
 * Return: sk_wmem_alloc minus initial offset of one
 */
अटल अंतरभूत पूर्णांक sk_wmem_alloc_get(स्थिर काष्ठा sock *sk)
अणु
	वापस refcount_पढ़ो(&sk->sk_wmem_alloc) - 1;
पूर्ण

/**
 * sk_rmem_alloc_get - वापसs पढ़ो allocations
 * @sk: socket
 *
 * Return: sk_rmem_alloc
 */
अटल अंतरभूत पूर्णांक sk_rmem_alloc_get(स्थिर काष्ठा sock *sk)
अणु
	वापस atomic_पढ़ो(&sk->sk_rmem_alloc);
पूर्ण

/**
 * sk_has_allocations - check अगर allocations are outstanding
 * @sk: socket
 *
 * Return: true अगर socket has ग_लिखो or पढ़ो allocations
 */
अटल अंतरभूत bool sk_has_allocations(स्थिर काष्ठा sock *sk)
अणु
	वापस sk_wmem_alloc_get(sk) || sk_rmem_alloc_get(sk);
पूर्ण

/**
 * skwq_has_sleeper - check अगर there are any रुकोing processes
 * @wq: काष्ठा socket_wq
 *
 * Return: true अगर socket_wq has रुकोing processes
 *
 * The purpose of the skwq_has_sleeper and sock_poll_रुको is to wrap the memory
 * barrier call. They were added due to the race found within the tcp code.
 *
 * Consider following tcp code paths::
 *
 *   CPU1                CPU2
 *   sys_select          receive packet
 *   ...                 ...
 *   __add_रुको_queue    update tp->rcv_nxt
 *   ...                 ...
 *   tp->rcv_nxt check   sock_def_पढ़ोable
 *   ...                 अणु
 *   schedule               rcu_पढ़ो_lock();
 *                          wq = rcu_dereference(sk->sk_wq);
 *                          अगर (wq && रुकोqueue_active(&wq->रुको))
 *                              wake_up_पूर्णांकerruptible(&wq->रुको)
 *                          ...
 *                       पूर्ण
 *
 * The race क्रम tcp fires when the __add_रुको_queue changes करोne by CPU1 stay
 * in its cache, and so करोes the tp->rcv_nxt update on CPU2 side.  The CPU1
 * could then endup calling schedule and sleep क्रमever अगर there are no more
 * data on the socket.
 *
 */
अटल अंतरभूत bool skwq_has_sleeper(काष्ठा socket_wq *wq)
अणु
	वापस wq && wq_has_sleeper(&wq->रुको);
पूर्ण

/**
 * sock_poll_रुको - place memory barrier behind the poll_रुको call.
 * @filp:           file
 * @sock:           socket to रुको on
 * @p:              poll_table
 *
 * See the comments in the wq_has_sleeper function.
 */
अटल अंतरभूत व्योम sock_poll_रुको(काष्ठा file *filp, काष्ठा socket *sock,
				  poll_table *p)
अणु
	अगर (!poll_करोes_not_रुको(p)) अणु
		poll_रुको(filp, &sock->wq.रुको, p);
		/* We need to be sure we are in sync with the
		 * socket flags modअगरication.
		 *
		 * This memory barrier is paired in the wq_has_sleeper.
		 */
		smp_mb();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम skb_set_hash_from_sk(काष्ठा sk_buff *skb, काष्ठा sock *sk)
अणु
	/* This pairs with WRITE_ONCE() in sk_set_txhash() */
	u32 txhash = READ_ONCE(sk->sk_txhash);

	अगर (txhash) अणु
		skb->l4_hash = 1;
		skb->hash = txhash;
	पूर्ण
पूर्ण

व्योम skb_set_owner_w(काष्ठा sk_buff *skb, काष्ठा sock *sk);

/*
 *	Queue a received datagram अगर it will fit. Stream and sequenced
 *	protocols can't normally use this as they need to fit buffers in
 *	and play with them.
 *
 *	Inlined as it's very लघु and called क्रम pretty much every
 *	packet ever received.
 */
अटल अंतरभूत व्योम skb_set_owner_r(काष्ठा sk_buff *skb, काष्ठा sock *sk)
अणु
	skb_orphan(skb);
	skb->sk = sk;
	skb->deकाष्ठाor = sock_rमुक्त;
	atomic_add(skb->truesize, &sk->sk_rmem_alloc);
	sk_mem_अक्षरge(sk, skb->truesize);
पूर्ण

अटल अंतरभूत __must_check bool skb_set_owner_sk_safe(काष्ठा sk_buff *skb, काष्ठा sock *sk)
अणु
	अगर (sk && refcount_inc_not_zero(&sk->sk_refcnt)) अणु
		skb_orphan(skb);
		skb->deकाष्ठाor = sock_eमुक्त;
		skb->sk = sk;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

व्योम sk_reset_समयr(काष्ठा sock *sk, काष्ठा समयr_list *समयr,
		    अचिन्हित दीर्घ expires);

व्योम sk_stop_समयr(काष्ठा sock *sk, काष्ठा समयr_list *समयr);

व्योम sk_stop_समयr_sync(काष्ठा sock *sk, काष्ठा समयr_list *समयr);

पूर्णांक __sk_queue_drop_skb(काष्ठा sock *sk, काष्ठा sk_buff_head *sk_queue,
			काष्ठा sk_buff *skb, अचिन्हित पूर्णांक flags,
			व्योम (*deकाष्ठाor)(काष्ठा sock *sk,
					   काष्ठा sk_buff *skb));
पूर्णांक __sock_queue_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक sock_queue_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb);

पूर्णांक sock_queue_err_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb);
काष्ठा sk_buff *sock_dequeue_err_skb(काष्ठा sock *sk);

/*
 *	Recover an error report and clear atomically
 */

अटल अंतरभूत पूर्णांक sock_error(काष्ठा sock *sk)
अणु
	पूर्णांक err;

	/* Aव्योम an atomic operation क्रम the common हाल.
	 * This is racy since another cpu/thपढ़ो can change sk_err under us.
	 */
	अगर (likely(data_race(!sk->sk_err)))
		वापस 0;

	err = xchg(&sk->sk_err, 0);
	वापस -err;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ sock_wspace(काष्ठा sock *sk)
अणु
	पूर्णांक amt = 0;

	अगर (!(sk->sk_shutकरोwn & SEND_SHUTDOWN)) अणु
		amt = sk->sk_sndbuf - refcount_पढ़ो(&sk->sk_wmem_alloc);
		अगर (amt < 0)
			amt = 0;
	पूर्ण
	वापस amt;
पूर्ण

/* Note:
 *  We use sk->sk_wq_raw, from contexts knowing this
 *  poपूर्णांकer is not शून्य and cannot disappear/change.
 */
अटल अंतरभूत व्योम sk_set_bit(पूर्णांक nr, काष्ठा sock *sk)
अणु
	अगर ((nr == SOCKWQ_ASYNC_NOSPACE || nr == SOCKWQ_ASYNC_WAITDATA) &&
	    !sock_flag(sk, SOCK_FASYNC))
		वापस;

	set_bit(nr, &sk->sk_wq_raw->flags);
पूर्ण

अटल अंतरभूत व्योम sk_clear_bit(पूर्णांक nr, काष्ठा sock *sk)
अणु
	अगर ((nr == SOCKWQ_ASYNC_NOSPACE || nr == SOCKWQ_ASYNC_WAITDATA) &&
	    !sock_flag(sk, SOCK_FASYNC))
		वापस;

	clear_bit(nr, &sk->sk_wq_raw->flags);
पूर्ण

अटल अंतरभूत व्योम sk_wake_async(स्थिर काष्ठा sock *sk, पूर्णांक how, पूर्णांक band)
अणु
	अगर (sock_flag(sk, SOCK_FASYNC)) अणु
		rcu_पढ़ो_lock();
		sock_wake_async(rcu_dereference(sk->sk_wq), how, band);
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

/* Since sk_अणुr,wपूर्णmem_alloc sums skb->truesize, even a small frame might
 * need माप(sk_buff) + MTU + padding, unless net driver perक्रमm copyअवरोध.
 * Note: क्रम send buffers, TCP works better अगर we can build two skbs at
 * minimum.
 */
#घोषणा TCP_SKB_MIN_TRUESIZE	(2048 + SKB_DATA_ALIGN(माप(काष्ठा sk_buff)))

#घोषणा SOCK_MIN_SNDBUF		(TCP_SKB_MIN_TRUESIZE * 2)
#घोषणा SOCK_MIN_RCVBUF		 TCP_SKB_MIN_TRUESIZE

अटल अंतरभूत व्योम sk_stream_moderate_sndbuf(काष्ठा sock *sk)
अणु
	u32 val;

	अगर (sk->sk_userlocks & SOCK_SNDBUF_LOCK)
		वापस;

	val = min(sk->sk_sndbuf, sk->sk_wmem_queued >> 1);

	WRITE_ONCE(sk->sk_sndbuf, max_t(u32, val, SOCK_MIN_SNDBUF));
पूर्ण

काष्ठा sk_buff *sk_stream_alloc_skb(काष्ठा sock *sk, पूर्णांक size, gfp_t gfp,
				    bool क्रमce_schedule);

/**
 * sk_page_frag - वापस an appropriate page_frag
 * @sk: socket
 *
 * Use the per task page_frag instead of the per socket one क्रम
 * optimization when we know that we're in the normal context and owns
 * everything that's associated with %current.
 *
 * gfpflags_allow_blocking() isn't enough here as direct reclaim may nest
 * inside other socket operations and end up recursing पूर्णांकo sk_page_frag()
 * जबतक it's alपढ़ोy in use.
 *
 * Return: a per task page_frag अगर context allows that,
 * otherwise a per socket one.
 */
अटल अंतरभूत काष्ठा page_frag *sk_page_frag(काष्ठा sock *sk)
अणु
	अगर (gfpflags_normal_context(sk->sk_allocation))
		वापस &current->task_frag;

	वापस &sk->sk_frag;
पूर्ण

bool sk_page_frag_refill(काष्ठा sock *sk, काष्ठा page_frag *pfrag);

/*
 *	Default ग_लिखो policy as shown to user space via poll/select/SIGIO
 */
अटल अंतरभूत bool sock_ग_लिखोable(स्थिर काष्ठा sock *sk)
अणु
	वापस refcount_पढ़ो(&sk->sk_wmem_alloc) < (READ_ONCE(sk->sk_sndbuf) >> 1);
पूर्ण

अटल अंतरभूत gfp_t gfp_any(व्योम)
अणु
	वापस in_softirq() ? GFP_ATOMIC : GFP_KERNEL;
पूर्ण

अटल अंतरभूत दीर्घ sock_rcvसमयo(स्थिर काष्ठा sock *sk, bool noblock)
अणु
	वापस noblock ? 0 : sk->sk_rcvसमयo;
पूर्ण

अटल अंतरभूत दीर्घ sock_sndसमयo(स्थिर काष्ठा sock *sk, bool noblock)
अणु
	वापस noblock ? 0 : sk->sk_sndसमयo;
पूर्ण

अटल अंतरभूत पूर्णांक sock_rcvlowat(स्थिर काष्ठा sock *sk, पूर्णांक रुकोall, पूर्णांक len)
अणु
	पूर्णांक v = रुकोall ? len : min_t(पूर्णांक, READ_ONCE(sk->sk_rcvlowat), len);

	वापस v ?: 1;
पूर्ण

/* Alas, with समयout socket operations are not restartable.
 * Compare this to poll().
 */
अटल अंतरभूत पूर्णांक sock_पूर्णांकr_त्रुटि_सं(दीर्घ समयo)
अणु
	वापस समयo == MAX_SCHEDULE_TIMEOUT ? -ERESTARTSYS : -EINTR;
पूर्ण

काष्ठा sock_skb_cb अणु
	u32 dropcount;
पूर्ण;

/* Store sock_skb_cb at the end of skb->cb[] so protocol families
 * using skb->cb[] would keep using it directly and utilize its
 * alignement guarantee.
 */
#घोषणा SOCK_SKB_CB_OFFSET ((माप_field(काष्ठा sk_buff, cb) - \
			    माप(काष्ठा sock_skb_cb)))

#घोषणा SOCK_SKB_CB(__skb) ((काष्ठा sock_skb_cb *)((__skb)->cb + \
			    SOCK_SKB_CB_OFFSET))

#घोषणा sock_skb_cb_check_size(size) \
	BUILD_BUG_ON((size) > SOCK_SKB_CB_OFFSET)

अटल अंतरभूत व्योम
sock_skb_set_dropcount(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	SOCK_SKB_CB(skb)->dropcount = sock_flag(sk, SOCK_RXQ_OVFL) ?
						atomic_पढ़ो(&sk->sk_drops) : 0;
पूर्ण

अटल अंतरभूत व्योम sk_drops_add(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
	पूर्णांक segs = max_t(u16, 1, skb_shinfo(skb)->gso_segs);

	atomic_add(segs, &sk->sk_drops);
पूर्ण

अटल अंतरभूत kसमय_प्रकार sock_पढ़ो_बारtamp(काष्ठा sock *sk)
अणु
#अगर BITS_PER_LONG==32
	अचिन्हित पूर्णांक seq;
	kसमय_प्रकार kt;

	करो अणु
		seq = पढ़ो_seqbegin(&sk->sk_stamp_seq);
		kt = sk->sk_stamp;
	पूर्ण जबतक (पढ़ो_seqretry(&sk->sk_stamp_seq, seq));

	वापस kt;
#अन्यथा
	वापस READ_ONCE(sk->sk_stamp);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम sock_ग_लिखो_बारtamp(काष्ठा sock *sk, kसमय_प्रकार kt)
अणु
#अगर BITS_PER_LONG==32
	ग_लिखो_seqlock(&sk->sk_stamp_seq);
	sk->sk_stamp = kt;
	ग_लिखो_sequnlock(&sk->sk_stamp_seq);
#अन्यथा
	WRITE_ONCE(sk->sk_stamp, kt);
#पूर्ण_अगर
पूर्ण

व्योम __sock_recv_बारtamp(काष्ठा msghdr *msg, काष्ठा sock *sk,
			   काष्ठा sk_buff *skb);
व्योम __sock_recv_wअगरi_status(काष्ठा msghdr *msg, काष्ठा sock *sk,
			     काष्ठा sk_buff *skb);

अटल अंतरभूत व्योम
sock_recv_बारtamp(काष्ठा msghdr *msg, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	kसमय_प्रकार kt = skb->tstamp;
	काष्ठा skb_shared_hwtstamps *hwtstamps = skb_hwtstamps(skb);

	/*
	 * generate control messages अगर
	 * - receive समय stamping in software requested
	 * - software समय stamp available and wanted
	 * - hardware समय stamps available and wanted
	 */
	अगर (sock_flag(sk, SOCK_RCVTSTAMP) ||
	    (sk->sk_tsflags & SOF_TIMESTAMPING_RX_SOFTWARE) ||
	    (kt && sk->sk_tsflags & SOF_TIMESTAMPING_SOFTWARE) ||
	    (hwtstamps->hwtstamp &&
	     (sk->sk_tsflags & SOF_TIMESTAMPING_RAW_HARDWARE)))
		__sock_recv_बारtamp(msg, sk, skb);
	अन्यथा
		sock_ग_लिखो_बारtamp(sk, kt);

	अगर (sock_flag(sk, SOCK_WIFI_STATUS) && skb->wअगरi_acked_valid)
		__sock_recv_wअगरi_status(msg, sk, skb);
पूर्ण

व्योम __sock_recv_ts_and_drops(काष्ठा msghdr *msg, काष्ठा sock *sk,
			      काष्ठा sk_buff *skb);

#घोषणा SK_DEFAULT_STAMP (-1L * NSEC_PER_SEC)
अटल अंतरभूत व्योम sock_recv_ts_and_drops(काष्ठा msghdr *msg, काष्ठा sock *sk,
					  काष्ठा sk_buff *skb)
अणु
#घोषणा FLAGS_TS_OR_DROPS ((1UL << SOCK_RXQ_OVFL)			| \
			   (1UL << SOCK_RCVTSTAMP))
#घोषणा TSFLAGS_ANY	  (SOF_TIMESTAMPING_SOFTWARE			| \
			   SOF_TIMESTAMPING_RAW_HARDWARE)

	अगर (sk->sk_flags & FLAGS_TS_OR_DROPS || sk->sk_tsflags & TSFLAGS_ANY)
		__sock_recv_ts_and_drops(msg, sk, skb);
	अन्यथा अगर (unlikely(sock_flag(sk, SOCK_TIMESTAMP)))
		sock_ग_लिखो_बारtamp(sk, skb->tstamp);
	अन्यथा अगर (unlikely(sk->sk_stamp == SK_DEFAULT_STAMP))
		sock_ग_लिखो_बारtamp(sk, 0);
पूर्ण

व्योम __sock_tx_बारtamp(__u16 tsflags, __u8 *tx_flags);

/**
 * _sock_tx_बारtamp - checks whether the outgoing packet is to be समय stamped
 * @sk:		socket sending this packet
 * @tsflags:	बारtamping flags to use
 * @tx_flags:	completed with inकाष्ठाions क्रम समय stamping
 * @tskey:      filled in with next sk_tskey (not क्रम TCP, which uses seqno)
 *
 * Note: callers should take care of initial ``*tx_flags`` value (usually 0)
 */
अटल अंतरभूत व्योम _sock_tx_बारtamp(काष्ठा sock *sk, __u16 tsflags,
				      __u8 *tx_flags, __u32 *tskey)
अणु
	अगर (unlikely(tsflags)) अणु
		__sock_tx_बारtamp(tsflags, tx_flags);
		अगर (tsflags & SOF_TIMESTAMPING_OPT_ID && tskey &&
		    tsflags & SOF_TIMESTAMPING_TX_RECORD_MASK)
			*tskey = sk->sk_tskey++;
	पूर्ण
	अगर (unlikely(sock_flag(sk, SOCK_WIFI_STATUS)))
		*tx_flags |= SKBTX_WIFI_STATUS;
पूर्ण

अटल अंतरभूत व्योम sock_tx_बारtamp(काष्ठा sock *sk, __u16 tsflags,
				     __u8 *tx_flags)
अणु
	_sock_tx_बारtamp(sk, tsflags, tx_flags, शून्य);
पूर्ण

अटल अंतरभूत व्योम skb_setup_tx_बारtamp(काष्ठा sk_buff *skb, __u16 tsflags)
अणु
	_sock_tx_बारtamp(skb->sk, tsflags, &skb_shinfo(skb)->tx_flags,
			   &skb_shinfo(skb)->tskey);
पूर्ण

DECLARE_STATIC_KEY_FALSE(tcp_rx_skb_cache_key);
/**
 * sk_eat_skb - Release a skb अगर it is no दीर्घer needed
 * @sk: socket to eat this skb from
 * @skb: socket buffer to eat
 *
 * This routine must be called with पूर्णांकerrupts disabled or with the socket
 * locked so that the sk_buff queue operation is ok.
*/
अटल अंतरभूत व्योम sk_eat_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	__skb_unlink(skb, &sk->sk_receive_queue);
	अगर (अटल_branch_unlikely(&tcp_rx_skb_cache_key) &&
	    !sk->sk_rx_skb_cache) अणु
		sk->sk_rx_skb_cache = skb;
		skb_orphan(skb);
		वापस;
	पूर्ण
	__kमुक्त_skb(skb);
पूर्ण

अटल अंतरभूत
काष्ठा net *sock_net(स्थिर काष्ठा sock *sk)
अणु
	वापस पढ़ो_pnet(&sk->sk_net);
पूर्ण

अटल अंतरभूत
व्योम sock_net_set(काष्ठा sock *sk, काष्ठा net *net)
अणु
	ग_लिखो_pnet(&sk->sk_net, net);
पूर्ण

अटल अंतरभूत bool
skb_sk_is_prefetched(काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_INET
	वापस skb->deकाष्ठाor == sock_pमुक्त;
#अन्यथा
	वापस false;
#पूर्ण_अगर /* CONFIG_INET */
पूर्ण

/* This helper checks अगर a socket is a full socket,
 * ie _not_ a समयरुको or request socket.
 */
अटल अंतरभूत bool sk_fullsock(स्थिर काष्ठा sock *sk)
अणु
	वापस (1 << sk->sk_state) & ~(TCPF_TIME_WAIT | TCPF_NEW_SYN_RECV);
पूर्ण

अटल अंतरभूत bool
sk_is_refcounted(काष्ठा sock *sk)
अणु
	/* Only full sockets have sk->sk_flags. */
	वापस !sk_fullsock(sk) || !sock_flag(sk, SOCK_RCU_FREE);
पूर्ण

/**
 * skb_steal_sock - steal a socket from an sk_buff
 * @skb: sk_buff to steal the socket from
 * @refcounted: is set to true अगर the socket is reference-counted
 */
अटल अंतरभूत काष्ठा sock *
skb_steal_sock(काष्ठा sk_buff *skb, bool *refcounted)
अणु
	अगर (skb->sk) अणु
		काष्ठा sock *sk = skb->sk;

		*refcounted = true;
		अगर (skb_sk_is_prefetched(skb))
			*refcounted = sk_is_refcounted(sk);
		skb->deकाष्ठाor = शून्य;
		skb->sk = शून्य;
		वापस sk;
	पूर्ण
	*refcounted = false;
	वापस शून्य;
पूर्ण

/* Checks अगर this SKB beदीर्घs to an HW offloaded socket
 * and whether any SW fallbacks are required based on dev.
 * Check decrypted mark in हाल skb_orphan() cleared socket.
 */
अटल अंतरभूत काष्ठा sk_buff *sk_validate_xmit_skb(काष्ठा sk_buff *skb,
						   काष्ठा net_device *dev)
अणु
#अगर_घोषित CONFIG_SOCK_VALIDATE_XMIT
	काष्ठा sock *sk = skb->sk;

	अगर (sk && sk_fullsock(sk) && sk->sk_validate_xmit_skb) अणु
		skb = sk->sk_validate_xmit_skb(sk, dev, skb);
#अगर_घोषित CONFIG_TLS_DEVICE
	पूर्ण अन्यथा अगर (unlikely(skb->decrypted)) अणु
		pr_warn_ratelimited("unencrypted skb with no associated socket - dropping\n");
		kमुक्त_skb(skb);
		skb = शून्य;
#पूर्ण_अगर
	पूर्ण
#पूर्ण_अगर

	वापस skb;
पूर्ण

/* This helper checks अगर a socket is a LISTEN or NEW_SYN_RECV
 * SYNACK messages can be attached to either ones (depending on SYNCOOKIE)
 */
अटल अंतरभूत bool sk_listener(स्थिर काष्ठा sock *sk)
अणु
	वापस (1 << sk->sk_state) & (TCPF_LISTEN | TCPF_NEW_SYN_RECV);
पूर्ण

व्योम sock_enable_बारtamp(काष्ठा sock *sk, क्रमागत sock_flags flag);
पूर्णांक sock_recv_errqueue(काष्ठा sock *sk, काष्ठा msghdr *msg, पूर्णांक len, पूर्णांक level,
		       पूर्णांक type);

bool sk_ns_capable(स्थिर काष्ठा sock *sk,
		   काष्ठा user_namespace *user_ns, पूर्णांक cap);
bool sk_capable(स्थिर काष्ठा sock *sk, पूर्णांक cap);
bool sk_net_capable(स्थिर काष्ठा sock *sk, पूर्णांक cap);

व्योम sk_get_meminfo(स्थिर काष्ठा sock *sk, u32 *meminfo);

/* Take पूर्णांकo consideration the size of the काष्ठा sk_buff overhead in the
 * determination of these values, since that is non-स्थिरant across
 * platक्रमms.  This makes socket queueing behavior and perक्रमmance
 * not depend upon such dअगरferences.
 */
#घोषणा _SK_MEM_PACKETS		256
#घोषणा _SK_MEM_OVERHEAD	SKB_TRUESIZE(256)
#घोषणा SK_WMEM_MAX		(_SK_MEM_OVERHEAD * _SK_MEM_PACKETS)
#घोषणा SK_RMEM_MAX		(_SK_MEM_OVERHEAD * _SK_MEM_PACKETS)

बाह्य __u32 sysctl_wmem_max;
बाह्य __u32 sysctl_rmem_max;

बाह्य पूर्णांक sysctl_tstamp_allow_data;
बाह्य पूर्णांक sysctl_opपंचांगem_max;

बाह्य __u32 sysctl_wmem_शेष;
बाह्य __u32 sysctl_rmem_शेष;

DECLARE_STATIC_KEY_FALSE(net_high_order_alloc_disable_key);

अटल अंतरभूत पूर्णांक sk_get_wmem0(स्थिर काष्ठा sock *sk, स्थिर काष्ठा proto *proto)
अणु
	/* Does this proto have per netns sysctl_wmem ? */
	अगर (proto->sysctl_wmem_offset)
		वापस *(पूर्णांक *)((व्योम *)sock_net(sk) + proto->sysctl_wmem_offset);

	वापस *proto->sysctl_wmem;
पूर्ण

अटल अंतरभूत पूर्णांक sk_get_rmem0(स्थिर काष्ठा sock *sk, स्थिर काष्ठा proto *proto)
अणु
	/* Does this proto have per netns sysctl_rmem ? */
	अगर (proto->sysctl_rmem_offset)
		वापस *(पूर्णांक *)((व्योम *)sock_net(sk) + proto->sysctl_rmem_offset);

	वापस *proto->sysctl_rmem;
पूर्ण

/* Default TCP Small queue budget is ~1 ms of data (1sec >> 10)
 * Some wअगरi drivers need to tweak it to get more chunks.
 * They can use this helper from their nकरो_start_xmit()
 */
अटल अंतरभूत व्योम sk_pacing_shअगरt_update(काष्ठा sock *sk, पूर्णांक val)
अणु
	अगर (!sk || !sk_fullsock(sk) || READ_ONCE(sk->sk_pacing_shअगरt) == val)
		वापस;
	WRITE_ONCE(sk->sk_pacing_shअगरt, val);
पूर्ण

/* अगर a socket is bound to a device, check that the given device
 * index is either the same or that the socket is bound to an L3
 * master device and the given device index is also enslaved to
 * that L3 master
 */
अटल अंतरभूत bool sk_dev_equal_l3scope(काष्ठा sock *sk, पूर्णांक dअगर)
अणु
	पूर्णांक mdअगर;

	अगर (!sk->sk_bound_dev_अगर || sk->sk_bound_dev_अगर == dअगर)
		वापस true;

	mdअगर = l3mdev_master_अगरindex_by_index(sock_net(sk), dअगर);
	अगर (mdअगर && mdअगर == sk->sk_bound_dev_अगर)
		वापस true;

	वापस false;
पूर्ण

व्योम sock_def_पढ़ोable(काष्ठा sock *sk);

पूर्णांक sock_bindtoindex(काष्ठा sock *sk, पूर्णांक अगरindex, bool lock_sk);
व्योम sock_enable_बारtamps(काष्ठा sock *sk);
व्योम sock_no_linger(काष्ठा sock *sk);
व्योम sock_set_keepalive(काष्ठा sock *sk);
व्योम sock_set_priority(काष्ठा sock *sk, u32 priority);
व्योम sock_set_rcvbuf(काष्ठा sock *sk, पूर्णांक val);
व्योम sock_set_mark(काष्ठा sock *sk, u32 val);
व्योम sock_set_reuseaddr(काष्ठा sock *sk);
व्योम sock_set_reuseport(काष्ठा sock *sk);
व्योम sock_set_sndसमयo(काष्ठा sock *sk, s64 secs);

पूर्णांक sock_bind_add(काष्ठा sock *sk, काष्ठा sockaddr *addr, पूर्णांक addr_len);

#पूर्ण_अगर	/* _SOCK_H */
