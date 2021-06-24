<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* L2TP पूर्णांकernal definitions.
 *
 * Copyright (c) 2008,2009 Katalix Systems Ltd
 */
#समावेश <linux/refcount.h>

#अगर_अघोषित _L2TP_CORE_H_
#घोषणा _L2TP_CORE_H_

#समावेश <net/dst.h>
#समावेश <net/sock.h>

#अगर_घोषित CONFIG_XFRM
#समावेश <net/xfrm.h>
#पूर्ण_अगर

/* Ranकरोm numbers used क्रम पूर्णांकernal consistency checks of tunnel and session काष्ठाures */
#घोषणा L2TP_TUNNEL_MAGIC	0x42114DDA
#घोषणा L2TP_SESSION_MAGIC	0x0C04EB7D

/* Per tunnel session hash table size */
#घोषणा L2TP_HASH_BITS	4
#घोषणा L2TP_HASH_SIZE	BIT(L2TP_HASH_BITS)

/* System-wide session hash table size */
#घोषणा L2TP_HASH_BITS_2	8
#घोषणा L2TP_HASH_SIZE_2	BIT(L2TP_HASH_BITS_2)

काष्ठा sk_buff;

काष्ठा l2tp_stats अणु
	atomic_दीर्घ_t		tx_packets;
	atomic_दीर्घ_t		tx_bytes;
	atomic_दीर्घ_t		tx_errors;
	atomic_दीर्घ_t		rx_packets;
	atomic_दीर्घ_t		rx_bytes;
	atomic_दीर्घ_t		rx_seq_discards;
	atomic_दीर्घ_t		rx_oos_packets;
	atomic_दीर्घ_t		rx_errors;
	atomic_दीर्घ_t		rx_cookie_discards;
	atomic_दीर्घ_t		rx_invalid;
पूर्ण;

काष्ठा l2tp_tunnel;

/* L2TP session configuration */
काष्ठा l2tp_session_cfg अणु
	क्रमागत l2tp_pwtype	pw_type;
	अचिन्हित पूर्णांक		recv_seq:1;	/* expect receive packets with sequence numbers? */
	अचिन्हित पूर्णांक		send_seq:1;	/* send packets with sequence numbers? */
	अचिन्हित पूर्णांक		lns_mode:1;	/* behave as LNS?
						 * LAC enables sequence numbers under LNS control.
						 */
	u16			l2specअगरic_type; /* Layer 2 specअगरic type */
	u8			cookie[8];	/* optional cookie */
	पूर्णांक			cookie_len;	/* 0, 4 or 8 bytes */
	u8			peer_cookie[8];	/* peer's cookie */
	पूर्णांक			peer_cookie_len; /* 0, 4 or 8 bytes */
	पूर्णांक			reorder_समयout; /* configured reorder समयout (in jअगरfies) */
	अक्षर			*अगरname;
पूर्ण;

/* Represents a session (pseuकरोwire) instance.
 * Tracks runसमय state including cookies, dataplane packet sequencing, and IO statistics.
 * Is linked पूर्णांकo a per-tunnel session hashlist; and in the हाल of an L2TPv3 session पूर्णांकo
 * an additional per-net ("global") hashlist.
 */
#घोषणा L2TP_SESSION_NAME_MAX 32
काष्ठा l2tp_session अणु
	पूर्णांक			magic;		/* should be L2TP_SESSION_MAGIC */
	दीर्घ			dead;

	काष्ठा l2tp_tunnel	*tunnel;	/* back poपूर्णांकer to tunnel context */
	u32			session_id;
	u32			peer_session_id;
	u8			cookie[8];
	पूर्णांक			cookie_len;
	u8			peer_cookie[8];
	पूर्णांक			peer_cookie_len;
	u16			l2specअगरic_type;
	u16			hdr_len;
	u32			nr;		/* session NR state (receive) */
	u32			ns;		/* session NR state (send) */
	काष्ठा sk_buff_head	reorder_q;	/* receive reorder queue */
	u32			nr_max;		/* max NR. Depends on tunnel */
	u32			nr_winकरोw_size;	/* NR winकरोw size */
	u32			nr_oos;		/* NR of last OOS packet */
	पूर्णांक			nr_oos_count;	/* क्रम OOS recovery */
	पूर्णांक			nr_oos_count_max;
	काष्ठा hlist_node	hlist;		/* hash list node */
	refcount_t		ref_count;

	अक्षर			name[L2TP_SESSION_NAME_MAX]; /* क्रम logging */
	अक्षर			अगरname[IFNAMSIZ];
	अचिन्हित पूर्णांक		recv_seq:1;	/* expect receive packets with sequence numbers? */
	अचिन्हित पूर्णांक		send_seq:1;	/* send packets with sequence numbers? */
	अचिन्हित पूर्णांक		lns_mode:1;	/* behave as LNS?
						 * LAC enables sequence numbers under LNS control.
						 */
	पूर्णांक			reorder_समयout; /* configured reorder समयout (in jअगरfies) */
	पूर्णांक			reorder_skip;	/* set अगर skip to next nr */
	क्रमागत l2tp_pwtype	pwtype;
	काष्ठा l2tp_stats	stats;
	काष्ठा hlist_node	global_hlist;	/* global hash list node */

	/* Session receive handler क्रम data packets.
	 * Each pseuकरोwire implementation should implement this callback in order to
	 * handle incoming packets.  Packets are passed to the pseuकरोwire handler after
	 * reordering, अगर data sequence numbers are enabled क्रम the session.
	 */
	व्योम (*recv_skb)(काष्ठा l2tp_session *session, काष्ठा sk_buff *skb, पूर्णांक data_len);

	/* Session बंद handler.
	 * Each pseuकरोwire implementation may implement this callback in order to carry
	 * out pseuकरोwire-specअगरic shutकरोwn actions.
	 * The callback is called by core after unhashing the session and purging its
	 * reorder queue.
	 */
	व्योम (*session_बंद)(काष्ठा l2tp_session *session);

	/* Session show handler.
	 * Pseuकरोwire-specअगरic implementation of debugfs session rendering.
	 * The callback is called by l2tp_debugfs.c after rendering core session
	 * inक्रमmation.
	 */
	व्योम (*show)(काष्ठा seq_file *m, व्योम *priv);

	u8			priv[];		/* निजी data */
पूर्ण;

/* L2TP tunnel configuration */
काष्ठा l2tp_tunnel_cfg अणु
	क्रमागत l2tp_encap_type	encap;

	/* Used only क्रम kernel-created sockets */
	काष्ठा in_addr		local_ip;
	काष्ठा in_addr		peer_ip;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा in6_addr		*local_ip6;
	काष्ठा in6_addr		*peer_ip6;
#पूर्ण_अगर
	u16			local_udp_port;
	u16			peer_udp_port;
	अचिन्हित पूर्णांक		use_udp_checksums:1,
				udp6_zero_tx_checksums:1,
				udp6_zero_rx_checksums:1;
पूर्ण;

/* Represents a tunnel instance.
 * Tracks runसमय state including IO statistics.
 * Holds the tunnel socket (either passed from userspace or directly created by the kernel).
 * Maपूर्णांकains a hashlist of sessions beदीर्घing to the tunnel instance.
 * Is linked पूर्णांकo a per-net list of tunnels.
 */
#घोषणा L2TP_TUNNEL_NAME_MAX 20
काष्ठा l2tp_tunnel अणु
	पूर्णांक			magic;		/* Should be L2TP_TUNNEL_MAGIC */

	अचिन्हित दीर्घ		dead;

	काष्ठा rcu_head rcu;
	rwlock_t		hlist_lock;	/* protect session_hlist */
	bool			acpt_newsess;	/* indicates whether this tunnel accepts
						 * new sessions. Protected by hlist_lock.
						 */
	काष्ठा hlist_head	session_hlist[L2TP_HASH_SIZE];
						/* hashed list of sessions, hashed by id */
	u32			tunnel_id;
	u32			peer_tunnel_id;
	पूर्णांक			version;	/* 2=>L2TPv2, 3=>L2TPv3 */

	अक्षर			name[L2TP_TUNNEL_NAME_MAX]; /* क्रम logging */
	क्रमागत l2tp_encap_type	encap;
	काष्ठा l2tp_stats	stats;

	काष्ठा list_head	list;		/* list node on per-namespace list of tunnels */
	काष्ठा net		*l2tp_net;	/* the net we beदीर्घ to */

	refcount_t		ref_count;
	व्योम (*old_sk_deकाष्ठा)(काष्ठा sock *sk);
	काष्ठा sock		*sock;		/* parent socket */
	पूर्णांक			fd;		/* parent fd, अगर tunnel socket was created
						 * by userspace
						 */

	काष्ठा work_काष्ठा	del_work;
पूर्ण;

/* Pseuकरोwire ops callbacks क्रम use with the l2tp genetlink पूर्णांकerface */
काष्ठा l2tp_nl_cmd_ops अणु
	/* The pseuकरोwire session create callback is responsible क्रम creating a session
	 * instance क्रम a specअगरic pseuकरोwire type.
	 * It must call l2tp_session_create and l2tp_session_रेजिस्टर to रेजिस्टर the
	 * session instance, as well as carry out any pseuकरोwire-specअगरic initialisation.
	 * It must वापस >= 0 on success, or an appropriate negative त्रुटि_सं value on failure.
	 */
	पूर्णांक (*session_create)(काष्ठा net *net, काष्ठा l2tp_tunnel *tunnel,
			      u32 session_id, u32 peer_session_id,
			      काष्ठा l2tp_session_cfg *cfg);

	/* The pseuकरोwire session delete callback is responsible क्रम initiating the deletion
	 * of a session instance.
	 * It must call l2tp_session_delete, as well as carry out any pseuकरोwire-specअगरic
	 * tearकरोwn actions.
	 */
	व्योम (*session_delete)(काष्ठा l2tp_session *session);
पूर्ण;

अटल अंतरभूत व्योम *l2tp_session_priv(काष्ठा l2tp_session *session)
अणु
	वापस &session->priv[0];
पूर्ण

/* Tunnel and session refcounts */
व्योम l2tp_tunnel_inc_refcount(काष्ठा l2tp_tunnel *tunnel);
व्योम l2tp_tunnel_dec_refcount(काष्ठा l2tp_tunnel *tunnel);
व्योम l2tp_session_inc_refcount(काष्ठा l2tp_session *session);
व्योम l2tp_session_dec_refcount(काष्ठा l2tp_session *session);

/* Tunnel and session lookup.
 * These functions take a reference on the instances they वापस, so
 * the caller must ensure that the reference is dropped appropriately.
 */
काष्ठा l2tp_tunnel *l2tp_tunnel_get(स्थिर काष्ठा net *net, u32 tunnel_id);
काष्ठा l2tp_tunnel *l2tp_tunnel_get_nth(स्थिर काष्ठा net *net, पूर्णांक nth);
काष्ठा l2tp_session *l2tp_tunnel_get_session(काष्ठा l2tp_tunnel *tunnel,
					     u32 session_id);

काष्ठा l2tp_session *l2tp_session_get(स्थिर काष्ठा net *net, u32 session_id);
काष्ठा l2tp_session *l2tp_session_get_nth(काष्ठा l2tp_tunnel *tunnel, पूर्णांक nth);
काष्ठा l2tp_session *l2tp_session_get_by_अगरname(स्थिर काष्ठा net *net,
						स्थिर अक्षर *अगरname);

/* Tunnel and session lअगरeसमय management.
 * Creation of a new instance is a two-step process: create, then रेजिस्टर.
 * Deकाष्ठाion is triggered using the *_delete functions, and completes asynchronously.
 */
पूर्णांक l2tp_tunnel_create(पूर्णांक fd, पूर्णांक version, u32 tunnel_id,
		       u32 peer_tunnel_id, काष्ठा l2tp_tunnel_cfg *cfg,
		       काष्ठा l2tp_tunnel **tunnelp);
पूर्णांक l2tp_tunnel_रेजिस्टर(काष्ठा l2tp_tunnel *tunnel, काष्ठा net *net,
			 काष्ठा l2tp_tunnel_cfg *cfg);
व्योम l2tp_tunnel_delete(काष्ठा l2tp_tunnel *tunnel);

काष्ठा l2tp_session *l2tp_session_create(पूर्णांक priv_size,
					 काष्ठा l2tp_tunnel *tunnel,
					 u32 session_id, u32 peer_session_id,
					 काष्ठा l2tp_session_cfg *cfg);
पूर्णांक l2tp_session_रेजिस्टर(काष्ठा l2tp_session *session,
			  काष्ठा l2tp_tunnel *tunnel);
व्योम l2tp_session_delete(काष्ठा l2tp_session *session);

/* Receive path helpers.  If data sequencing is enabled क्रम the session these
 * functions handle queuing and reordering prior to passing packets to the
 * pseuकरोwire code to be passed to userspace.
 */
व्योम l2tp_recv_common(काष्ठा l2tp_session *session, काष्ठा sk_buff *skb,
		      अचिन्हित अक्षर *ptr, अचिन्हित अक्षर *optr, u16 hdrflags,
		      पूर्णांक length);
पूर्णांक l2tp_udp_encap_recv(काष्ठा sock *sk, काष्ठा sk_buff *skb);

/* Transmit path helpers क्रम sending packets over the tunnel socket. */
व्योम l2tp_session_set_header_len(काष्ठा l2tp_session *session, पूर्णांक version);
पूर्णांक l2tp_xmit_skb(काष्ठा l2tp_session *session, काष्ठा sk_buff *skb);

/* Pseuकरोwire management.
 * Pseuकरोwires should रेजिस्टर with l2tp core on module init, and unरेजिस्टर
 * on module निकास.
 */
पूर्णांक l2tp_nl_रेजिस्टर_ops(क्रमागत l2tp_pwtype pw_type, स्थिर काष्ठा l2tp_nl_cmd_ops *ops);
व्योम l2tp_nl_unरेजिस्टर_ops(क्रमागत l2tp_pwtype pw_type);

/* IOCTL helper क्रम IP encap modules. */
पूर्णांक l2tp_ioctl(काष्ठा sock *sk, पूर्णांक cmd, अचिन्हित दीर्घ arg);

/* Extract the tunnel काष्ठाure from a socket's sk_user_data poपूर्णांकer,
 * validating the tunnel magic feather.
 */
काष्ठा l2tp_tunnel *l2tp_sk_to_tunnel(काष्ठा sock *sk);

अटल अंतरभूत पूर्णांक l2tp_get_l2specअगरic_len(काष्ठा l2tp_session *session)
अणु
	चयन (session->l2specअगरic_type) अणु
	हाल L2TP_L2SPECTYPE_DEFAULT:
		वापस 4;
	हाल L2TP_L2SPECTYPE_NONE:
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u32 l2tp_tunnel_dst_mtu(स्थिर काष्ठा l2tp_tunnel *tunnel)
अणु
	काष्ठा dst_entry *dst;
	u32 mtu;

	dst = sk_dst_get(tunnel->sock);
	अगर (!dst)
		वापस 0;

	mtu = dst_mtu(dst);
	dst_release(dst);

	वापस mtu;
पूर्ण

#अगर_घोषित CONFIG_XFRM
अटल अंतरभूत bool l2tp_tunnel_uses_xfrm(स्थिर काष्ठा l2tp_tunnel *tunnel)
अणु
	काष्ठा sock *sk = tunnel->sock;

	वापस sk && (rcu_access_poपूर्णांकer(sk->sk_policy[0]) ||
		      rcu_access_poपूर्णांकer(sk->sk_policy[1]));
पूर्ण
#अन्यथा
अटल अंतरभूत bool l2tp_tunnel_uses_xfrm(स्थिर काष्ठा l2tp_tunnel *tunnel)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक l2tp_v3_ensure_opt_in_linear(काष्ठा l2tp_session *session, काष्ठा sk_buff *skb,
					       अचिन्हित अक्षर **ptr, अचिन्हित अक्षर **optr)
अणु
	पूर्णांक opt_len = session->peer_cookie_len + l2tp_get_l2specअगरic_len(session);

	अगर (opt_len > 0) अणु
		पूर्णांक off = *ptr - *optr;

		अगर (!pskb_may_pull(skb, off + opt_len))
			वापस -1;

		अगर (skb->data != *optr) अणु
			*optr = skb->data;
			*ptr = skb->data + off;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा MODULE_ALIAS_L2TP_PWTYPE(type) \
	MODULE_ALIAS("net-l2tp-type-" __stringअगरy(type))

#पूर्ण_अगर /* _L2TP_CORE_H_ */
