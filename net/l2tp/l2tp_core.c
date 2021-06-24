<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* L2TP core.
 *
 * Copyright (c) 2008,2009,2010 Katalix Systems Ltd
 *
 * This file contains some code of the original L2TPv2 pppol2tp
 * driver, which has the following copyright:
 *
 * Authors:	Martijn van Oosterhout <kleptog@svana.org>
 *		James Chapman (jchapman@katalix.com)
 * Contributors:
 *		Michal Ostrowski <mostrows@speakeasy.net>
 *		Arnalकरो Carvalho de Melo <acme@xconectiva.com.br>
 *		David S. Miller (davem@redhat.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/list.h>
#समावेश <linux/rculist.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/jअगरfies.h>

#समावेश <linux/netdevice.h>
#समावेश <linux/net.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/udp.h>
#समावेश <linux/l2tp.h>
#समावेश <linux/hash.h>
#समावेश <linux/sort.h>
#समावेश <linux/file.h>
#समावेश <linux/nsproxy.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/dst.h>
#समावेश <net/ip.h>
#समावेश <net/udp.h>
#समावेश <net/udp_tunnel.h>
#समावेश <net/inet_common.h>
#समावेश <net/xfrm.h>
#समावेश <net/protocol.h>
#समावेश <net/inet6_connection_sock.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/ip6_route.h>
#समावेश <net/ip6_checksum.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/atomic.h>

#समावेश "l2tp_core.h"
#समावेश "trace.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"

#घोषणा L2TP_DRV_VERSION	"V2.0"

/* L2TP header स्थिरants */
#घोषणा L2TP_HDRFLAG_T	   0x8000
#घोषणा L2TP_HDRFLAG_L	   0x4000
#घोषणा L2TP_HDRFLAG_S	   0x0800
#घोषणा L2TP_HDRFLAG_O	   0x0200
#घोषणा L2TP_HDRFLAG_P	   0x0100

#घोषणा L2TP_HDR_VER_MASK  0x000F
#घोषणा L2TP_HDR_VER_2	   0x0002
#घोषणा L2TP_HDR_VER_3	   0x0003

/* L2TPv3 शेष L2-specअगरic sublayer */
#घोषणा L2TP_SLFLAG_S	   0x40000000
#घोषणा L2TP_SL_SEQ_MASK   0x00ffffff

#घोषणा L2TP_HDR_SIZE_MAX		14

/* Default trace flags */
#घोषणा L2TP_DEFAULT_DEBUG_FLAGS	0

/* Private data stored क्रम received packets in the skb.
 */
काष्ठा l2tp_skb_cb अणु
	u32			ns;
	u16			has_seq;
	u16			length;
	अचिन्हित दीर्घ		expires;
पूर्ण;

#घोषणा L2TP_SKB_CB(skb)	((काष्ठा l2tp_skb_cb *)&(skb)->cb[माप(काष्ठा inet_skb_parm)])

अटल काष्ठा workqueue_काष्ठा *l2tp_wq;

/* per-net निजी data क्रम this module */
अटल अचिन्हित पूर्णांक l2tp_net_id;
काष्ठा l2tp_net अणु
	काष्ठा list_head l2tp_tunnel_list;
	/* Lock क्रम ग_लिखो access to l2tp_tunnel_list */
	spinlock_t l2tp_tunnel_list_lock;
	काष्ठा hlist_head l2tp_session_hlist[L2TP_HASH_SIZE_2];
	/* Lock क्रम ग_लिखो access to l2tp_session_hlist */
	spinlock_t l2tp_session_hlist_lock;
पूर्ण;

#अगर IS_ENABLED(CONFIG_IPV6)
अटल bool l2tp_sk_is_v6(काष्ठा sock *sk)
अणु
	वापस sk->sk_family == PF_INET6 &&
	       !ipv6_addr_v4mapped(&sk->sk_v6_daddr);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा l2tp_net *l2tp_pernet(स्थिर काष्ठा net *net)
अणु
	वापस net_generic(net, l2tp_net_id);
पूर्ण

/* Session hash global list क्रम L2TPv3.
 * The session_id SHOULD be अक्रमom according to RFC3931, but several
 * L2TP implementations use incrementing session_ids.  So we करो a real
 * hash on the session_id, rather than a simple biपंचांगask.
 */
अटल अंतरभूत काष्ठा hlist_head *
l2tp_session_id_hash_2(काष्ठा l2tp_net *pn, u32 session_id)
अणु
	वापस &pn->l2tp_session_hlist[hash_32(session_id, L2TP_HASH_BITS_2)];
पूर्ण

/* Session hash list.
 * The session_id SHOULD be अक्रमom according to RFC2661, but several
 * L2TP implementations (Cisco and Microsoft) use incrementing
 * session_ids.  So we करो a real hash on the session_id, rather than a
 * simple biपंचांगask.
 */
अटल अंतरभूत काष्ठा hlist_head *
l2tp_session_id_hash(काष्ठा l2tp_tunnel *tunnel, u32 session_id)
अणु
	वापस &tunnel->session_hlist[hash_32(session_id, L2TP_HASH_BITS)];
पूर्ण

अटल व्योम l2tp_tunnel_मुक्त(काष्ठा l2tp_tunnel *tunnel)
अणु
	trace_मुक्त_tunnel(tunnel);
	sock_put(tunnel->sock);
	/* the tunnel is मुक्तd in the socket deकाष्ठाor */
पूर्ण

अटल व्योम l2tp_session_मुक्त(काष्ठा l2tp_session *session)
अणु
	trace_मुक्त_session(session);
	अगर (session->tunnel)
		l2tp_tunnel_dec_refcount(session->tunnel);
	kमुक्त(session);
पूर्ण

काष्ठा l2tp_tunnel *l2tp_sk_to_tunnel(काष्ठा sock *sk)
अणु
	काष्ठा l2tp_tunnel *tunnel = sk->sk_user_data;

	अगर (tunnel)
		अगर (WARN_ON(tunnel->magic != L2TP_TUNNEL_MAGIC))
			वापस शून्य;

	वापस tunnel;
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_sk_to_tunnel);

व्योम l2tp_tunnel_inc_refcount(काष्ठा l2tp_tunnel *tunnel)
अणु
	refcount_inc(&tunnel->ref_count);
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_tunnel_inc_refcount);

व्योम l2tp_tunnel_dec_refcount(काष्ठा l2tp_tunnel *tunnel)
अणु
	अगर (refcount_dec_and_test(&tunnel->ref_count))
		l2tp_tunnel_मुक्त(tunnel);
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_tunnel_dec_refcount);

व्योम l2tp_session_inc_refcount(काष्ठा l2tp_session *session)
अणु
	refcount_inc(&session->ref_count);
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_session_inc_refcount);

व्योम l2tp_session_dec_refcount(काष्ठा l2tp_session *session)
अणु
	अगर (refcount_dec_and_test(&session->ref_count))
		l2tp_session_मुक्त(session);
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_session_dec_refcount);

/* Lookup a tunnel. A new reference is held on the वापसed tunnel. */
काष्ठा l2tp_tunnel *l2tp_tunnel_get(स्थिर काष्ठा net *net, u32 tunnel_id)
अणु
	स्थिर काष्ठा l2tp_net *pn = l2tp_pernet(net);
	काष्ठा l2tp_tunnel *tunnel;

	rcu_पढ़ो_lock_bh();
	list_क्रम_each_entry_rcu(tunnel, &pn->l2tp_tunnel_list, list) अणु
		अगर (tunnel->tunnel_id == tunnel_id &&
		    refcount_inc_not_zero(&tunnel->ref_count)) अणु
			rcu_पढ़ो_unlock_bh();

			वापस tunnel;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock_bh();

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_tunnel_get);

काष्ठा l2tp_tunnel *l2tp_tunnel_get_nth(स्थिर काष्ठा net *net, पूर्णांक nth)
अणु
	स्थिर काष्ठा l2tp_net *pn = l2tp_pernet(net);
	काष्ठा l2tp_tunnel *tunnel;
	पूर्णांक count = 0;

	rcu_पढ़ो_lock_bh();
	list_क्रम_each_entry_rcu(tunnel, &pn->l2tp_tunnel_list, list) अणु
		अगर (++count > nth &&
		    refcount_inc_not_zero(&tunnel->ref_count)) अणु
			rcu_पढ़ो_unlock_bh();
			वापस tunnel;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock_bh();

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_tunnel_get_nth);

काष्ठा l2tp_session *l2tp_tunnel_get_session(काष्ठा l2tp_tunnel *tunnel,
					     u32 session_id)
अणु
	काष्ठा hlist_head *session_list;
	काष्ठा l2tp_session *session;

	session_list = l2tp_session_id_hash(tunnel, session_id);

	पढ़ो_lock_bh(&tunnel->hlist_lock);
	hlist_क्रम_each_entry(session, session_list, hlist)
		अगर (session->session_id == session_id) अणु
			l2tp_session_inc_refcount(session);
			पढ़ो_unlock_bh(&tunnel->hlist_lock);

			वापस session;
		पूर्ण
	पढ़ो_unlock_bh(&tunnel->hlist_lock);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_tunnel_get_session);

काष्ठा l2tp_session *l2tp_session_get(स्थिर काष्ठा net *net, u32 session_id)
अणु
	काष्ठा hlist_head *session_list;
	काष्ठा l2tp_session *session;

	session_list = l2tp_session_id_hash_2(l2tp_pernet(net), session_id);

	rcu_पढ़ो_lock_bh();
	hlist_क्रम_each_entry_rcu(session, session_list, global_hlist)
		अगर (session->session_id == session_id) अणु
			l2tp_session_inc_refcount(session);
			rcu_पढ़ो_unlock_bh();

			वापस session;
		पूर्ण
	rcu_पढ़ो_unlock_bh();

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_session_get);

काष्ठा l2tp_session *l2tp_session_get_nth(काष्ठा l2tp_tunnel *tunnel, पूर्णांक nth)
अणु
	पूर्णांक hash;
	काष्ठा l2tp_session *session;
	पूर्णांक count = 0;

	पढ़ो_lock_bh(&tunnel->hlist_lock);
	क्रम (hash = 0; hash < L2TP_HASH_SIZE; hash++) अणु
		hlist_क्रम_each_entry(session, &tunnel->session_hlist[hash], hlist) अणु
			अगर (++count > nth) अणु
				l2tp_session_inc_refcount(session);
				पढ़ो_unlock_bh(&tunnel->hlist_lock);
				वापस session;
			पूर्ण
		पूर्ण
	पूर्ण

	पढ़ो_unlock_bh(&tunnel->hlist_lock);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_session_get_nth);

/* Lookup a session by पूर्णांकerface name.
 * This is very inefficient but is only used by management पूर्णांकerfaces.
 */
काष्ठा l2tp_session *l2tp_session_get_by_अगरname(स्थिर काष्ठा net *net,
						स्थिर अक्षर *अगरname)
अणु
	काष्ठा l2tp_net *pn = l2tp_pernet(net);
	पूर्णांक hash;
	काष्ठा l2tp_session *session;

	rcu_पढ़ो_lock_bh();
	क्रम (hash = 0; hash < L2TP_HASH_SIZE_2; hash++) अणु
		hlist_क्रम_each_entry_rcu(session, &pn->l2tp_session_hlist[hash], global_hlist) अणु
			अगर (!म_भेद(session->अगरname, अगरname)) अणु
				l2tp_session_inc_refcount(session);
				rcu_पढ़ो_unlock_bh();

				वापस session;
			पूर्ण
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock_bh();

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_session_get_by_अगरname);

पूर्णांक l2tp_session_रेजिस्टर(काष्ठा l2tp_session *session,
			  काष्ठा l2tp_tunnel *tunnel)
अणु
	काष्ठा l2tp_session *session_walk;
	काष्ठा hlist_head *g_head;
	काष्ठा hlist_head *head;
	काष्ठा l2tp_net *pn;
	पूर्णांक err;

	head = l2tp_session_id_hash(tunnel, session->session_id);

	ग_लिखो_lock_bh(&tunnel->hlist_lock);
	अगर (!tunnel->acpt_newsess) अणु
		err = -ENODEV;
		जाओ err_tlock;
	पूर्ण

	hlist_क्रम_each_entry(session_walk, head, hlist)
		अगर (session_walk->session_id == session->session_id) अणु
			err = -EEXIST;
			जाओ err_tlock;
		पूर्ण

	अगर (tunnel->version == L2TP_HDR_VER_3) अणु
		pn = l2tp_pernet(tunnel->l2tp_net);
		g_head = l2tp_session_id_hash_2(pn, session->session_id);

		spin_lock_bh(&pn->l2tp_session_hlist_lock);

		/* IP encap expects session IDs to be globally unique, जबतक
		 * UDP encap करोesn't.
		 */
		hlist_क्रम_each_entry(session_walk, g_head, global_hlist)
			अगर (session_walk->session_id == session->session_id &&
			    (session_walk->tunnel->encap == L2TP_ENCAPTYPE_IP ||
			     tunnel->encap == L2TP_ENCAPTYPE_IP)) अणु
				err = -EEXIST;
				जाओ err_tlock_pnlock;
			पूर्ण

		l2tp_tunnel_inc_refcount(tunnel);
		hlist_add_head_rcu(&session->global_hlist, g_head);

		spin_unlock_bh(&pn->l2tp_session_hlist_lock);
	पूर्ण अन्यथा अणु
		l2tp_tunnel_inc_refcount(tunnel);
	पूर्ण

	hlist_add_head(&session->hlist, head);
	ग_लिखो_unlock_bh(&tunnel->hlist_lock);

	trace_रेजिस्टर_session(session);

	वापस 0;

err_tlock_pnlock:
	spin_unlock_bh(&pn->l2tp_session_hlist_lock);
err_tlock:
	ग_लिखो_unlock_bh(&tunnel->hlist_lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_session_रेजिस्टर);

/*****************************************************************************
 * Receive data handling
 *****************************************************************************/

/* Queue a skb in order. We come here only अगर the skb has an L2TP sequence
 * number.
 */
अटल व्योम l2tp_recv_queue_skb(काष्ठा l2tp_session *session, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *skbp;
	काष्ठा sk_buff *पंचांगp;
	u32 ns = L2TP_SKB_CB(skb)->ns;

	spin_lock_bh(&session->reorder_q.lock);
	skb_queue_walk_safe(&session->reorder_q, skbp, पंचांगp) अणु
		अगर (L2TP_SKB_CB(skbp)->ns > ns) अणु
			__skb_queue_beक्रमe(&session->reorder_q, skbp, skb);
			atomic_दीर्घ_inc(&session->stats.rx_oos_packets);
			जाओ out;
		पूर्ण
	पूर्ण

	__skb_queue_tail(&session->reorder_q, skb);

out:
	spin_unlock_bh(&session->reorder_q.lock);
पूर्ण

/* Dequeue a single skb.
 */
अटल व्योम l2tp_recv_dequeue_skb(काष्ठा l2tp_session *session, काष्ठा sk_buff *skb)
अणु
	काष्ठा l2tp_tunnel *tunnel = session->tunnel;
	पूर्णांक length = L2TP_SKB_CB(skb)->length;

	/* We're about to requeue the skb, so वापस resources
	 * to its current owner (a socket receive buffer).
	 */
	skb_orphan(skb);

	atomic_दीर्घ_inc(&tunnel->stats.rx_packets);
	atomic_दीर्घ_add(length, &tunnel->stats.rx_bytes);
	atomic_दीर्घ_inc(&session->stats.rx_packets);
	atomic_दीर्घ_add(length, &session->stats.rx_bytes);

	अगर (L2TP_SKB_CB(skb)->has_seq) अणु
		/* Bump our Nr */
		session->nr++;
		session->nr &= session->nr_max;
		trace_session_seqnum_update(session);
	पूर्ण

	/* call निजी receive handler */
	अगर (session->recv_skb)
		(*session->recv_skb)(session, skb, L2TP_SKB_CB(skb)->length);
	अन्यथा
		kमुक्त_skb(skb);
पूर्ण

/* Dequeue skbs from the session's reorder_q, subject to packet order.
 * Skbs that have been in the queue क्रम too दीर्घ are simply discarded.
 */
अटल व्योम l2tp_recv_dequeue(काष्ठा l2tp_session *session)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff *पंचांगp;

	/* If the pkt at the head of the queue has the nr that we
	 * expect to send up next, dequeue it and any other
	 * in-sequence packets behind it.
	 */
start:
	spin_lock_bh(&session->reorder_q.lock);
	skb_queue_walk_safe(&session->reorder_q, skb, पंचांगp) अणु
		काष्ठा l2tp_skb_cb *cb = L2TP_SKB_CB(skb);

		/* If the packet has been pending on the queue क्रम too दीर्घ, discard it */
		अगर (समय_after(jअगरfies, cb->expires)) अणु
			atomic_दीर्घ_inc(&session->stats.rx_seq_discards);
			atomic_दीर्घ_inc(&session->stats.rx_errors);
			trace_session_pkt_expired(session, cb->ns);
			session->reorder_skip = 1;
			__skb_unlink(skb, &session->reorder_q);
			kमुक्त_skb(skb);
			जारी;
		पूर्ण

		अगर (cb->has_seq) अणु
			अगर (session->reorder_skip) अणु
				session->reorder_skip = 0;
				session->nr = cb->ns;
				trace_session_seqnum_reset(session);
			पूर्ण
			अगर (cb->ns != session->nr)
				जाओ out;
		पूर्ण
		__skb_unlink(skb, &session->reorder_q);

		/* Process the skb. We release the queue lock जबतक we
		 * करो so to let other contexts process the queue.
		 */
		spin_unlock_bh(&session->reorder_q.lock);
		l2tp_recv_dequeue_skb(session, skb);
		जाओ start;
	पूर्ण

out:
	spin_unlock_bh(&session->reorder_q.lock);
पूर्ण

अटल पूर्णांक l2tp_seq_check_rx_winकरोw(काष्ठा l2tp_session *session, u32 nr)
अणु
	u32 nws;

	अगर (nr >= session->nr)
		nws = nr - session->nr;
	अन्यथा
		nws = (session->nr_max + 1) - (session->nr - nr);

	वापस nws < session->nr_winकरोw_size;
पूर्ण

/* If packet has sequence numbers, queue it अगर acceptable. Returns 0 अगर
 * acceptable, अन्यथा non-zero.
 */
अटल पूर्णांक l2tp_recv_data_seq(काष्ठा l2tp_session *session, काष्ठा sk_buff *skb)
अणु
	काष्ठा l2tp_skb_cb *cb = L2TP_SKB_CB(skb);

	अगर (!l2tp_seq_check_rx_winकरोw(session, cb->ns)) अणु
		/* Packet sequence number is outside allowed winकरोw.
		 * Discard it.
		 */
		trace_session_pkt_outside_rx_winकरोw(session, cb->ns);
		जाओ discard;
	पूर्ण

	अगर (session->reorder_समयout != 0) अणु
		/* Packet reordering enabled. Add skb to session's
		 * reorder queue, in order of ns.
		 */
		l2tp_recv_queue_skb(session, skb);
		जाओ out;
	पूर्ण

	/* Packet reordering disabled. Discard out-of-sequence packets, जबतक
	 * tracking the number अगर in-sequence packets after the first OOS packet
	 * is seen. After nr_oos_count_max in-sequence packets, reset the
	 * sequence number to re-enable packet reception.
	 */
	अगर (cb->ns == session->nr) अणु
		skb_queue_tail(&session->reorder_q, skb);
	पूर्ण अन्यथा अणु
		u32 nr_oos = cb->ns;
		u32 nr_next = (session->nr_oos + 1) & session->nr_max;

		अगर (nr_oos == nr_next)
			session->nr_oos_count++;
		अन्यथा
			session->nr_oos_count = 0;

		session->nr_oos = nr_oos;
		अगर (session->nr_oos_count > session->nr_oos_count_max) अणु
			session->reorder_skip = 1;
		पूर्ण
		अगर (!session->reorder_skip) अणु
			atomic_दीर्घ_inc(&session->stats.rx_seq_discards);
			trace_session_pkt_oos(session, cb->ns);
			जाओ discard;
		पूर्ण
		skb_queue_tail(&session->reorder_q, skb);
	पूर्ण

out:
	वापस 0;

discard:
	वापस 1;
पूर्ण

/* Do receive processing of L2TP data frames. We handle both L2TPv2
 * and L2TPv3 data frames here.
 *
 * L2TPv2 Data Message Header
 *
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |T|L|x|x|S|x|O|P|x|x|x|x|  Ver  |          Length (opt)         |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |           Tunnel ID           |           Session ID          |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |             Ns (opt)          |             Nr (opt)          |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |      Offset Size (opt)        |    Offset pad... (opt)
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Data frames are marked by T=0. All other fields are the same as
 * those in L2TP control frames.
 *
 * L2TPv3 Data Message Header
 *
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                      L2TP Session Header                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                      L2-Specअगरic Sublayer                     |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                        Tunnel Payload                      ...
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * L2TPv3 Session Header Over IP
 *
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                           Session ID                          |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |               Cookie (optional, maximum 64 bits)...
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *                                                                 |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * L2TPv3 L2-Specअगरic Sublayer Format
 *
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |x|S|x|x|x|x|x|x|              Sequence Number                  |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Cookie value and sublayer क्रमmat are negotiated with the peer when
 * the session is set up. Unlike L2TPv2, we करो not need to parse the
 * packet header to determine अगर optional fields are present.
 *
 * Caller must alपढ़ोy have parsed the frame and determined that it is
 * a data (not control) frame beक्रमe coming here. Fields up to the
 * session-id have alपढ़ोy been parsed and ptr poपूर्णांकs to the data
 * after the session-id.
 */
व्योम l2tp_recv_common(काष्ठा l2tp_session *session, काष्ठा sk_buff *skb,
		      अचिन्हित अक्षर *ptr, अचिन्हित अक्षर *optr, u16 hdrflags,
		      पूर्णांक length)
अणु
	काष्ठा l2tp_tunnel *tunnel = session->tunnel;
	पूर्णांक offset;

	/* Parse and check optional cookie */
	अगर (session->peer_cookie_len > 0) अणु
		अगर (स_भेद(ptr, &session->peer_cookie[0], session->peer_cookie_len)) अणु
			pr_debug_ratelimited("%s: cookie mismatch (%u/%u). Discarding.\n",
					     tunnel->name, tunnel->tunnel_id,
					     session->session_id);
			atomic_दीर्घ_inc(&session->stats.rx_cookie_discards);
			जाओ discard;
		पूर्ण
		ptr += session->peer_cookie_len;
	पूर्ण

	/* Handle the optional sequence numbers. Sequence numbers are
	 * in dअगरferent places क्रम L2TPv2 and L2TPv3.
	 *
	 * If we are the LAC, enable/disable sequence numbers under
	 * the control of the LNS.  If no sequence numbers present but
	 * we were expecting them, discard frame.
	 */
	L2TP_SKB_CB(skb)->has_seq = 0;
	अगर (tunnel->version == L2TP_HDR_VER_2) अणु
		अगर (hdrflags & L2TP_HDRFLAG_S) अणु
			/* Store L2TP info in the skb */
			L2TP_SKB_CB(skb)->ns = ntohs(*(__be16 *)ptr);
			L2TP_SKB_CB(skb)->has_seq = 1;
			ptr += 2;
			/* Skip past nr in the header */
			ptr += 2;

		पूर्ण
	पूर्ण अन्यथा अगर (session->l2specअगरic_type == L2TP_L2SPECTYPE_DEFAULT) अणु
		u32 l2h = ntohl(*(__be32 *)ptr);

		अगर (l2h & 0x40000000) अणु
			/* Store L2TP info in the skb */
			L2TP_SKB_CB(skb)->ns = l2h & 0x00ffffff;
			L2TP_SKB_CB(skb)->has_seq = 1;
		पूर्ण
		ptr += 4;
	पूर्ण

	अगर (L2TP_SKB_CB(skb)->has_seq) अणु
		/* Received a packet with sequence numbers. If we're the LAC,
		 * check अगर we sre sending sequence numbers and अगर not,
		 * configure it so.
		 */
		अगर (!session->lns_mode && !session->send_seq) अणु
			trace_session_seqnum_lns_enable(session);
			session->send_seq = 1;
			l2tp_session_set_header_len(session, tunnel->version);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* No sequence numbers.
		 * If user has configured mandatory sequence numbers, discard.
		 */
		अगर (session->recv_seq) अणु
			pr_debug_ratelimited("%s: recv data has no seq numbers when required. Discarding.\n",
					     session->name);
			atomic_दीर्घ_inc(&session->stats.rx_seq_discards);
			जाओ discard;
		पूर्ण

		/* If we're the LAC and we're sending sequence numbers, the
		 * LNS has requested that we no दीर्घer send sequence numbers.
		 * If we're the LNS and we're sending sequence numbers, the
		 * LAC is broken. Discard the frame.
		 */
		अगर (!session->lns_mode && session->send_seq) अणु
			trace_session_seqnum_lns_disable(session);
			session->send_seq = 0;
			l2tp_session_set_header_len(session, tunnel->version);
		पूर्ण अन्यथा अगर (session->send_seq) अणु
			pr_debug_ratelimited("%s: recv data has no seq numbers when required. Discarding.\n",
					     session->name);
			atomic_दीर्घ_inc(&session->stats.rx_seq_discards);
			जाओ discard;
		पूर्ण
	पूर्ण

	/* Session data offset is defined only क्रम L2TPv2 and is
	 * indicated by an optional 16-bit value in the header.
	 */
	अगर (tunnel->version == L2TP_HDR_VER_2) अणु
		/* If offset bit set, skip it. */
		अगर (hdrflags & L2TP_HDRFLAG_O) अणु
			offset = ntohs(*(__be16 *)ptr);
			ptr += 2 + offset;
		पूर्ण
	पूर्ण

	offset = ptr - optr;
	अगर (!pskb_may_pull(skb, offset))
		जाओ discard;

	__skb_pull(skb, offset);

	/* Prepare skb क्रम adding to the session's reorder_q.  Hold
	 * packets क्रम max reorder_समयout or 1 second अगर not
	 * reordering.
	 */
	L2TP_SKB_CB(skb)->length = length;
	L2TP_SKB_CB(skb)->expires = jअगरfies +
		(session->reorder_समयout ? session->reorder_समयout : HZ);

	/* Add packet to the session's receive queue. Reordering is करोne here, अगर
	 * enabled. Saved L2TP protocol info is stored in skb->sb[].
	 */
	अगर (L2TP_SKB_CB(skb)->has_seq) अणु
		अगर (l2tp_recv_data_seq(session, skb))
			जाओ discard;
	पूर्ण अन्यथा अणु
		/* No sequence numbers. Add the skb to the tail of the
		 * reorder queue. This ensures that it will be
		 * delivered after all previous sequenced skbs.
		 */
		skb_queue_tail(&session->reorder_q, skb);
	पूर्ण

	/* Try to dequeue as many skbs from reorder_q as we can. */
	l2tp_recv_dequeue(session);

	वापस;

discard:
	atomic_दीर्घ_inc(&session->stats.rx_errors);
	kमुक्त_skb(skb);
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_recv_common);

/* Drop skbs from the session's reorder_q
 */
अटल व्योम l2tp_session_queue_purge(काष्ठा l2tp_session *session)
अणु
	काष्ठा sk_buff *skb = शून्य;

	जबतक ((skb = skb_dequeue(&session->reorder_q))) अणु
		atomic_दीर्घ_inc(&session->stats.rx_errors);
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण

/* Internal UDP receive frame. Do the real work of receiving an L2TP data frame
 * here. The skb is not on a list when we get here.
 * Returns 0 अगर the packet was a data packet and was successfully passed on.
 * Returns 1 अगर the packet was not a good data packet and could not be
 * क्रमwarded.  All such packets are passed up to userspace to deal with.
 */
अटल पूर्णांक l2tp_udp_recv_core(काष्ठा l2tp_tunnel *tunnel, काष्ठा sk_buff *skb)
अणु
	काष्ठा l2tp_session *session = शून्य;
	अचिन्हित अक्षर *ptr, *optr;
	u16 hdrflags;
	u32 tunnel_id, session_id;
	u16 version;
	पूर्णांक length;

	/* UDP has verअगरied checksum */

	/* UDP always verअगरies the packet length. */
	__skb_pull(skb, माप(काष्ठा udphdr));

	/* Short packet? */
	अगर (!pskb_may_pull(skb, L2TP_HDR_SIZE_MAX)) अणु
		pr_debug_ratelimited("%s: recv short packet (len=%d)\n",
				     tunnel->name, skb->len);
		जाओ invalid;
	पूर्ण

	/* Poपूर्णांक to L2TP header */
	optr = skb->data;
	ptr = skb->data;

	/* Get L2TP header flags */
	hdrflags = ntohs(*(__be16 *)ptr);

	/* Check protocol version */
	version = hdrflags & L2TP_HDR_VER_MASK;
	अगर (version != tunnel->version) अणु
		pr_debug_ratelimited("%s: recv protocol version mismatch: got %d expected %d\n",
				     tunnel->name, version, tunnel->version);
		जाओ invalid;
	पूर्ण

	/* Get length of L2TP packet */
	length = skb->len;

	/* If type is control packet, it is handled by userspace. */
	अगर (hdrflags & L2TP_HDRFLAG_T)
		जाओ pass;

	/* Skip flags */
	ptr += 2;

	अगर (tunnel->version == L2TP_HDR_VER_2) अणु
		/* If length is present, skip it */
		अगर (hdrflags & L2TP_HDRFLAG_L)
			ptr += 2;

		/* Extract tunnel and session ID */
		tunnel_id = ntohs(*(__be16 *)ptr);
		ptr += 2;
		session_id = ntohs(*(__be16 *)ptr);
		ptr += 2;
	पूर्ण अन्यथा अणु
		ptr += 2;	/* skip reserved bits */
		tunnel_id = tunnel->tunnel_id;
		session_id = ntohl(*(__be32 *)ptr);
		ptr += 4;
	पूर्ण

	/* Find the session context */
	session = l2tp_tunnel_get_session(tunnel, session_id);
	अगर (!session || !session->recv_skb) अणु
		अगर (session)
			l2tp_session_dec_refcount(session);

		/* Not found? Pass to userspace to deal with */
		pr_debug_ratelimited("%s: no session found (%u/%u). Passing up.\n",
				     tunnel->name, tunnel_id, session_id);
		जाओ pass;
	पूर्ण

	अगर (tunnel->version == L2TP_HDR_VER_3 &&
	    l2tp_v3_ensure_opt_in_linear(session, skb, &ptr, &optr))
		जाओ invalid;

	l2tp_recv_common(session, skb, ptr, optr, hdrflags, length);
	l2tp_session_dec_refcount(session);

	वापस 0;

invalid:
	atomic_दीर्घ_inc(&tunnel->stats.rx_invalid);

pass:
	/* Put UDP header back */
	__skb_push(skb, माप(काष्ठा udphdr));

	वापस 1;
पूर्ण

/* UDP encapsulation receive handler. See net/ipv4/udp.c.
 * Return codes:
 * 0 : success.
 * <0: error
 * >0: skb should be passed up to userspace as UDP.
 */
पूर्णांक l2tp_udp_encap_recv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा l2tp_tunnel *tunnel;

	/* Note that this is called from the encap_rcv hook inside an
	 * RCU-रक्षित region, but without the socket being locked.
	 * Hence we use rcu_dereference_sk_user_data to access the
	 * tunnel data काष्ठाure rather the usual l2tp_sk_to_tunnel
	 * accessor function.
	 */
	tunnel = rcu_dereference_sk_user_data(sk);
	अगर (!tunnel)
		जाओ pass_up;
	अगर (WARN_ON(tunnel->magic != L2TP_TUNNEL_MAGIC))
		जाओ pass_up;

	अगर (l2tp_udp_recv_core(tunnel, skb))
		जाओ pass_up;

	वापस 0;

pass_up:
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_udp_encap_recv);

/************************************************************************
 * Transmit handling
 ***********************************************************************/

/* Build an L2TP header क्रम the session पूर्णांकo the buffer provided.
 */
अटल पूर्णांक l2tp_build_l2tpv2_header(काष्ठा l2tp_session *session, व्योम *buf)
अणु
	काष्ठा l2tp_tunnel *tunnel = session->tunnel;
	__be16 *bufp = buf;
	__be16 *optr = buf;
	u16 flags = L2TP_HDR_VER_2;
	u32 tunnel_id = tunnel->peer_tunnel_id;
	u32 session_id = session->peer_session_id;

	अगर (session->send_seq)
		flags |= L2TP_HDRFLAG_S;

	/* Setup L2TP header. */
	*bufp++ = htons(flags);
	*bufp++ = htons(tunnel_id);
	*bufp++ = htons(session_id);
	अगर (session->send_seq) अणु
		*bufp++ = htons(session->ns);
		*bufp++ = 0;
		session->ns++;
		session->ns &= 0xffff;
		trace_session_seqnum_update(session);
	पूर्ण

	वापस bufp - optr;
पूर्ण

अटल पूर्णांक l2tp_build_l2tpv3_header(काष्ठा l2tp_session *session, व्योम *buf)
अणु
	काष्ठा l2tp_tunnel *tunnel = session->tunnel;
	अक्षर *bufp = buf;
	अक्षर *optr = bufp;

	/* Setup L2TP header. The header dअगरfers slightly क्रम UDP and
	 * IP encapsulations. For UDP, there is 4 bytes of flags.
	 */
	अगर (tunnel->encap == L2TP_ENCAPTYPE_UDP) अणु
		u16 flags = L2TP_HDR_VER_3;
		*((__be16 *)bufp) = htons(flags);
		bufp += 2;
		*((__be16 *)bufp) = 0;
		bufp += 2;
	पूर्ण

	*((__be32 *)bufp) = htonl(session->peer_session_id);
	bufp += 4;
	अगर (session->cookie_len) अणु
		स_नकल(bufp, &session->cookie[0], session->cookie_len);
		bufp += session->cookie_len;
	पूर्ण
	अगर (session->l2specअगरic_type == L2TP_L2SPECTYPE_DEFAULT) अणु
		u32 l2h = 0;

		अगर (session->send_seq) अणु
			l2h = 0x40000000 | session->ns;
			session->ns++;
			session->ns &= 0xffffff;
			trace_session_seqnum_update(session);
		पूर्ण

		*((__be32 *)bufp) = htonl(l2h);
		bufp += 4;
	पूर्ण

	वापस bufp - optr;
पूर्ण

/* Queue the packet to IP क्रम output: tunnel socket lock must be held */
अटल पूर्णांक l2tp_xmit_queue(काष्ठा l2tp_tunnel *tunnel, काष्ठा sk_buff *skb, काष्ठा flowi *fl)
अणु
	पूर्णांक err;

	skb->ignore_df = 1;
	skb_dst_drop(skb);
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (l2tp_sk_is_v6(tunnel->sock))
		err = inet6_csk_xmit(tunnel->sock, skb, शून्य);
	अन्यथा
#पूर्ण_अगर
		err = ip_queue_xmit(tunnel->sock, skb, fl);

	वापस err >= 0 ? NET_XMIT_SUCCESS : NET_XMIT_DROP;
पूर्ण

अटल पूर्णांक l2tp_xmit_core(काष्ठा l2tp_session *session, काष्ठा sk_buff *skb, अचिन्हित पूर्णांक *len)
अणु
	काष्ठा l2tp_tunnel *tunnel = session->tunnel;
	अचिन्हित पूर्णांक data_len = skb->len;
	काष्ठा sock *sk = tunnel->sock;
	पूर्णांक headroom, uhlen, udp_len;
	पूर्णांक ret = NET_XMIT_SUCCESS;
	काष्ठा inet_sock *inet;
	काष्ठा udphdr *uh;

	/* Check that there's enough headroom in the skb to insert IP,
	 * UDP and L2TP headers. If not enough, expand it to
	 * make room. Adjust truesize.
	 */
	uhlen = (tunnel->encap == L2TP_ENCAPTYPE_UDP) ? माप(*uh) : 0;
	headroom = NET_SKB_PAD + माप(काष्ठा iphdr) + uhlen + session->hdr_len;
	अगर (skb_cow_head(skb, headroom)) अणु
		kमुक्त_skb(skb);
		वापस NET_XMIT_DROP;
	पूर्ण

	/* Setup L2TP header */
	अगर (tunnel->version == L2TP_HDR_VER_2)
		l2tp_build_l2tpv2_header(session, __skb_push(skb, session->hdr_len));
	अन्यथा
		l2tp_build_l2tpv3_header(session, __skb_push(skb, session->hdr_len));

	/* Reset skb netfilter state */
	स_रखो(&(IPCB(skb)->opt), 0, माप(IPCB(skb)->opt));
	IPCB(skb)->flags &= ~(IPSKB_XFRM_TUNNEL_SIZE | IPSKB_XFRM_TRANSFORMED | IPSKB_REROUTED);
	nf_reset_ct(skb);

	bh_lock_sock(sk);
	अगर (sock_owned_by_user(sk)) अणु
		kमुक्त_skb(skb);
		ret = NET_XMIT_DROP;
		जाओ out_unlock;
	पूर्ण

	/* The user-space may change the connection status क्रम the user-space
	 * provided socket at run समय: we must check it under the socket lock
	 */
	अगर (tunnel->fd >= 0 && sk->sk_state != TCP_ESTABLISHED) अणु
		kमुक्त_skb(skb);
		ret = NET_XMIT_DROP;
		जाओ out_unlock;
	पूर्ण

	/* Report transmitted length beक्रमe we add encap header, which keeps
	 * statistics consistent क्रम both UDP and IP encap tx/rx paths.
	 */
	*len = skb->len;

	inet = inet_sk(sk);
	चयन (tunnel->encap) अणु
	हाल L2TP_ENCAPTYPE_UDP:
		/* Setup UDP header */
		__skb_push(skb, माप(*uh));
		skb_reset_transport_header(skb);
		uh = udp_hdr(skb);
		uh->source = inet->inet_sport;
		uh->dest = inet->inet_dport;
		udp_len = uhlen + session->hdr_len + data_len;
		uh->len = htons(udp_len);

		/* Calculate UDP checksum अगर configured to करो so */
#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (l2tp_sk_is_v6(sk))
			udp6_set_csum(udp_get_no_check6_tx(sk),
				      skb, &inet6_sk(sk)->saddr,
				      &sk->sk_v6_daddr, udp_len);
		अन्यथा
#पूर्ण_अगर
			udp_set_csum(sk->sk_no_check_tx, skb, inet->inet_saddr,
				     inet->inet_daddr, udp_len);
		अवरोध;

	हाल L2TP_ENCAPTYPE_IP:
		अवरोध;
	पूर्ण

	ret = l2tp_xmit_queue(tunnel, skb, &inet->cork.fl);

out_unlock:
	bh_unlock_sock(sk);

	वापस ret;
पूर्ण

/* If caller requires the skb to have a ppp header, the header must be
 * inserted in the skb data beक्रमe calling this function.
 */
पूर्णांक l2tp_xmit_skb(काष्ठा l2tp_session *session, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक len = 0;
	पूर्णांक ret;

	ret = l2tp_xmit_core(session, skb, &len);
	अगर (ret == NET_XMIT_SUCCESS) अणु
		atomic_दीर्घ_inc(&session->tunnel->stats.tx_packets);
		atomic_दीर्घ_add(len, &session->tunnel->stats.tx_bytes);
		atomic_दीर्घ_inc(&session->stats.tx_packets);
		atomic_दीर्घ_add(len, &session->stats.tx_bytes);
	पूर्ण अन्यथा अणु
		atomic_दीर्घ_inc(&session->tunnel->stats.tx_errors);
		atomic_दीर्घ_inc(&session->stats.tx_errors);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_xmit_skb);

/*****************************************************************************
 * Tinnel and session create/destroy.
 *****************************************************************************/

/* Tunnel socket deकाष्ठा hook.
 * The tunnel context is deleted only when all session sockets have been
 * बंदd.
 */
अटल व्योम l2tp_tunnel_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा l2tp_tunnel *tunnel = l2tp_sk_to_tunnel(sk);

	अगर (!tunnel)
		जाओ end;

	/* Disable udp encapsulation */
	चयन (tunnel->encap) अणु
	हाल L2TP_ENCAPTYPE_UDP:
		/* No दीर्घer an encapsulation socket. See net/ipv4/udp.c */
		(udp_sk(sk))->encap_type = 0;
		(udp_sk(sk))->encap_rcv = शून्य;
		(udp_sk(sk))->encap_destroy = शून्य;
		अवरोध;
	हाल L2TP_ENCAPTYPE_IP:
		अवरोध;
	पूर्ण

	/* Remove hooks पूर्णांकo tunnel socket */
	sk->sk_deकाष्ठा = tunnel->old_sk_deकाष्ठा;
	sk->sk_user_data = शून्य;

	/* Call the original deकाष्ठाor */
	अगर (sk->sk_deकाष्ठा)
		(*sk->sk_deकाष्ठा)(sk);

	kमुक्त_rcu(tunnel, rcu);
end:
	वापस;
पूर्ण

/* Remove an l2tp session from l2tp_core's hash lists. */
अटल व्योम l2tp_session_unhash(काष्ठा l2tp_session *session)
अणु
	काष्ठा l2tp_tunnel *tunnel = session->tunnel;

	/* Remove the session from core hashes */
	अगर (tunnel) अणु
		/* Remove from the per-tunnel hash */
		ग_लिखो_lock_bh(&tunnel->hlist_lock);
		hlist_del_init(&session->hlist);
		ग_लिखो_unlock_bh(&tunnel->hlist_lock);

		/* For L2TPv3 we have a per-net hash: हटाओ from there, too */
		अगर (tunnel->version != L2TP_HDR_VER_2) अणु
			काष्ठा l2tp_net *pn = l2tp_pernet(tunnel->l2tp_net);

			spin_lock_bh(&pn->l2tp_session_hlist_lock);
			hlist_del_init_rcu(&session->global_hlist);
			spin_unlock_bh(&pn->l2tp_session_hlist_lock);
			synchronize_rcu();
		पूर्ण
	पूर्ण
पूर्ण

/* When the tunnel is बंदd, all the attached sessions need to go too.
 */
अटल व्योम l2tp_tunnel_बंदall(काष्ठा l2tp_tunnel *tunnel)
अणु
	पूर्णांक hash;
	काष्ठा hlist_node *walk;
	काष्ठा hlist_node *पंचांगp;
	काष्ठा l2tp_session *session;

	ग_लिखो_lock_bh(&tunnel->hlist_lock);
	tunnel->acpt_newsess = false;
	क्रम (hash = 0; hash < L2TP_HASH_SIZE; hash++) अणु
again:
		hlist_क्रम_each_safe(walk, पंचांगp, &tunnel->session_hlist[hash]) अणु
			session = hlist_entry(walk, काष्ठा l2tp_session, hlist);
			hlist_del_init(&session->hlist);

			ग_लिखो_unlock_bh(&tunnel->hlist_lock);
			l2tp_session_delete(session);
			ग_लिखो_lock_bh(&tunnel->hlist_lock);

			/* Now restart from the beginning of this hash
			 * chain.  We always हटाओ a session from the
			 * list so we are guaranteed to make क्रमward
			 * progress.
			 */
			जाओ again;
		पूर्ण
	पूर्ण
	ग_लिखो_unlock_bh(&tunnel->hlist_lock);
पूर्ण

/* Tunnel socket destroy hook क्रम UDP encapsulation */
अटल व्योम l2tp_udp_encap_destroy(काष्ठा sock *sk)
अणु
	काष्ठा l2tp_tunnel *tunnel = l2tp_sk_to_tunnel(sk);

	अगर (tunnel)
		l2tp_tunnel_delete(tunnel);
पूर्ण

/* Workqueue tunnel deletion function */
अटल व्योम l2tp_tunnel_del_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा l2tp_tunnel *tunnel = container_of(work, काष्ठा l2tp_tunnel,
						  del_work);
	काष्ठा sock *sk = tunnel->sock;
	काष्ठा socket *sock = sk->sk_socket;
	काष्ठा l2tp_net *pn;

	l2tp_tunnel_बंदall(tunnel);

	/* If the tunnel socket was created within the kernel, use
	 * the sk API to release it here.
	 */
	अगर (tunnel->fd < 0) अणु
		अगर (sock) अणु
			kernel_sock_shutकरोwn(sock, SHUT_RDWR);
			sock_release(sock);
		पूर्ण
	पूर्ण

	/* Remove the tunnel काष्ठा from the tunnel list */
	pn = l2tp_pernet(tunnel->l2tp_net);
	spin_lock_bh(&pn->l2tp_tunnel_list_lock);
	list_del_rcu(&tunnel->list);
	spin_unlock_bh(&pn->l2tp_tunnel_list_lock);

	/* drop initial ref */
	l2tp_tunnel_dec_refcount(tunnel);

	/* drop workqueue ref */
	l2tp_tunnel_dec_refcount(tunnel);
पूर्ण

/* Create a socket क्रम the tunnel, अगर one isn't set up by
 * userspace. This is used क्रम अटल tunnels where there is no
 * managing L2TP daemon.
 *
 * Since we करोn't want these sockets to keep a namespace alive by
 * themselves, we drop the socket's namespace refcount after creation.
 * These sockets are मुक्तd when the namespace निकासs using the pernet
 * निकास hook.
 */
अटल पूर्णांक l2tp_tunnel_sock_create(काष्ठा net *net,
				   u32 tunnel_id,
				   u32 peer_tunnel_id,
				   काष्ठा l2tp_tunnel_cfg *cfg,
				   काष्ठा socket **sockp)
अणु
	पूर्णांक err = -EINVAL;
	काष्ठा socket *sock = शून्य;
	काष्ठा udp_port_cfg udp_conf;

	चयन (cfg->encap) अणु
	हाल L2TP_ENCAPTYPE_UDP:
		स_रखो(&udp_conf, 0, माप(udp_conf));

#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (cfg->local_ip6 && cfg->peer_ip6) अणु
			udp_conf.family = AF_INET6;
			स_नकल(&udp_conf.local_ip6, cfg->local_ip6,
			       माप(udp_conf.local_ip6));
			स_नकल(&udp_conf.peer_ip6, cfg->peer_ip6,
			       माप(udp_conf.peer_ip6));
			udp_conf.use_udp6_tx_checksums =
			  !cfg->udp6_zero_tx_checksums;
			udp_conf.use_udp6_rx_checksums =
			  !cfg->udp6_zero_rx_checksums;
		पूर्ण अन्यथा
#पूर्ण_अगर
		अणु
			udp_conf.family = AF_INET;
			udp_conf.local_ip = cfg->local_ip;
			udp_conf.peer_ip = cfg->peer_ip;
			udp_conf.use_udp_checksums = cfg->use_udp_checksums;
		पूर्ण

		udp_conf.local_udp_port = htons(cfg->local_udp_port);
		udp_conf.peer_udp_port = htons(cfg->peer_udp_port);

		err = udp_sock_create(net, &udp_conf, &sock);
		अगर (err < 0)
			जाओ out;

		अवरोध;

	हाल L2TP_ENCAPTYPE_IP:
#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (cfg->local_ip6 && cfg->peer_ip6) अणु
			काष्ठा sockaddr_l2tpip6 ip6_addr = अणु0पूर्ण;

			err = sock_create_kern(net, AF_INET6, SOCK_DGRAM,
					       IPPROTO_L2TP, &sock);
			अगर (err < 0)
				जाओ out;

			ip6_addr.l2tp_family = AF_INET6;
			स_नकल(&ip6_addr.l2tp_addr, cfg->local_ip6,
			       माप(ip6_addr.l2tp_addr));
			ip6_addr.l2tp_conn_id = tunnel_id;
			err = kernel_bind(sock, (काष्ठा sockaddr *)&ip6_addr,
					  माप(ip6_addr));
			अगर (err < 0)
				जाओ out;

			ip6_addr.l2tp_family = AF_INET6;
			स_नकल(&ip6_addr.l2tp_addr, cfg->peer_ip6,
			       माप(ip6_addr.l2tp_addr));
			ip6_addr.l2tp_conn_id = peer_tunnel_id;
			err = kernel_connect(sock,
					     (काष्ठा sockaddr *)&ip6_addr,
					     माप(ip6_addr), 0);
			अगर (err < 0)
				जाओ out;
		पूर्ण अन्यथा
#पूर्ण_अगर
		अणु
			काष्ठा sockaddr_l2tpip ip_addr = अणु0पूर्ण;

			err = sock_create_kern(net, AF_INET, SOCK_DGRAM,
					       IPPROTO_L2TP, &sock);
			अगर (err < 0)
				जाओ out;

			ip_addr.l2tp_family = AF_INET;
			ip_addr.l2tp_addr = cfg->local_ip;
			ip_addr.l2tp_conn_id = tunnel_id;
			err = kernel_bind(sock, (काष्ठा sockaddr *)&ip_addr,
					  माप(ip_addr));
			अगर (err < 0)
				जाओ out;

			ip_addr.l2tp_family = AF_INET;
			ip_addr.l2tp_addr = cfg->peer_ip;
			ip_addr.l2tp_conn_id = peer_tunnel_id;
			err = kernel_connect(sock, (काष्ठा sockaddr *)&ip_addr,
					     माप(ip_addr), 0);
			अगर (err < 0)
				जाओ out;
		पूर्ण
		अवरोध;

	शेष:
		जाओ out;
	पूर्ण

out:
	*sockp = sock;
	अगर (err < 0 && sock) अणु
		kernel_sock_shutकरोwn(sock, SHUT_RDWR);
		sock_release(sock);
		*sockp = शून्य;
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा lock_class_key l2tp_socket_class;

पूर्णांक l2tp_tunnel_create(पूर्णांक fd, पूर्णांक version, u32 tunnel_id, u32 peer_tunnel_id,
		       काष्ठा l2tp_tunnel_cfg *cfg, काष्ठा l2tp_tunnel **tunnelp)
अणु
	काष्ठा l2tp_tunnel *tunnel = शून्य;
	पूर्णांक err;
	क्रमागत l2tp_encap_type encap = L2TP_ENCAPTYPE_UDP;

	अगर (cfg)
		encap = cfg->encap;

	tunnel = kzalloc(माप(*tunnel), GFP_KERNEL);
	अगर (!tunnel) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	tunnel->version = version;
	tunnel->tunnel_id = tunnel_id;
	tunnel->peer_tunnel_id = peer_tunnel_id;

	tunnel->magic = L2TP_TUNNEL_MAGIC;
	प्र_लिखो(&tunnel->name[0], "tunl %u", tunnel_id);
	rwlock_init(&tunnel->hlist_lock);
	tunnel->acpt_newsess = true;

	tunnel->encap = encap;

	refcount_set(&tunnel->ref_count, 1);
	tunnel->fd = fd;

	/* Init delete workqueue काष्ठा */
	INIT_WORK(&tunnel->del_work, l2tp_tunnel_del_work);

	INIT_LIST_HEAD(&tunnel->list);

	err = 0;
err:
	अगर (tunnelp)
		*tunnelp = tunnel;

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_tunnel_create);

अटल पूर्णांक l2tp_validate_socket(स्थिर काष्ठा sock *sk, स्थिर काष्ठा net *net,
				क्रमागत l2tp_encap_type encap)
अणु
	अगर (!net_eq(sock_net(sk), net))
		वापस -EINVAL;

	अगर (sk->sk_type != SOCK_DGRAM)
		वापस -EPROTONOSUPPORT;

	अगर (sk->sk_family != PF_INET && sk->sk_family != PF_INET6)
		वापस -EPROTONOSUPPORT;

	अगर ((encap == L2TP_ENCAPTYPE_UDP && sk->sk_protocol != IPPROTO_UDP) ||
	    (encap == L2TP_ENCAPTYPE_IP && sk->sk_protocol != IPPROTO_L2TP))
		वापस -EPROTONOSUPPORT;

	अगर (sk->sk_user_data)
		वापस -EBUSY;

	वापस 0;
पूर्ण

पूर्णांक l2tp_tunnel_रेजिस्टर(काष्ठा l2tp_tunnel *tunnel, काष्ठा net *net,
			 काष्ठा l2tp_tunnel_cfg *cfg)
अणु
	काष्ठा l2tp_tunnel *tunnel_walk;
	काष्ठा l2tp_net *pn;
	काष्ठा socket *sock;
	काष्ठा sock *sk;
	पूर्णांक ret;

	अगर (tunnel->fd < 0) अणु
		ret = l2tp_tunnel_sock_create(net, tunnel->tunnel_id,
					      tunnel->peer_tunnel_id, cfg,
					      &sock);
		अगर (ret < 0)
			जाओ err;
	पूर्ण अन्यथा अणु
		sock = sockfd_lookup(tunnel->fd, &ret);
		अगर (!sock)
			जाओ err;

		ret = l2tp_validate_socket(sock->sk, net, tunnel->encap);
		अगर (ret < 0)
			जाओ err_sock;
	पूर्ण

	tunnel->l2tp_net = net;
	pn = l2tp_pernet(net);

	sk = sock->sk;
	sock_hold(sk);
	tunnel->sock = sk;

	spin_lock_bh(&pn->l2tp_tunnel_list_lock);
	list_क्रम_each_entry(tunnel_walk, &pn->l2tp_tunnel_list, list) अणु
		अगर (tunnel_walk->tunnel_id == tunnel->tunnel_id) अणु
			spin_unlock_bh(&pn->l2tp_tunnel_list_lock);
			sock_put(sk);
			ret = -EEXIST;
			जाओ err_sock;
		पूर्ण
	पूर्ण
	list_add_rcu(&tunnel->list, &pn->l2tp_tunnel_list);
	spin_unlock_bh(&pn->l2tp_tunnel_list_lock);

	अगर (tunnel->encap == L2TP_ENCAPTYPE_UDP) अणु
		काष्ठा udp_tunnel_sock_cfg udp_cfg = अणु
			.sk_user_data = tunnel,
			.encap_type = UDP_ENCAP_L2TPINUDP,
			.encap_rcv = l2tp_udp_encap_recv,
			.encap_destroy = l2tp_udp_encap_destroy,
		पूर्ण;

		setup_udp_tunnel_sock(net, sock, &udp_cfg);
	पूर्ण अन्यथा अणु
		sk->sk_user_data = tunnel;
	पूर्ण

	tunnel->old_sk_deकाष्ठा = sk->sk_deकाष्ठा;
	sk->sk_deकाष्ठा = &l2tp_tunnel_deकाष्ठा;
	lockdep_set_class_and_name(&sk->sk_lock.slock, &l2tp_socket_class,
				   "l2tp_sock");
	sk->sk_allocation = GFP_ATOMIC;

	trace_रेजिस्टर_tunnel(tunnel);

	अगर (tunnel->fd >= 0)
		sockfd_put(sock);

	वापस 0;

err_sock:
	अगर (tunnel->fd < 0)
		sock_release(sock);
	अन्यथा
		sockfd_put(sock);
err:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_tunnel_रेजिस्टर);

/* This function is used by the netlink TUNNEL_DELETE command.
 */
व्योम l2tp_tunnel_delete(काष्ठा l2tp_tunnel *tunnel)
अणु
	अगर (!test_and_set_bit(0, &tunnel->dead)) अणु
		trace_delete_tunnel(tunnel);
		l2tp_tunnel_inc_refcount(tunnel);
		queue_work(l2tp_wq, &tunnel->del_work);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_tunnel_delete);

व्योम l2tp_session_delete(काष्ठा l2tp_session *session)
अणु
	अगर (test_and_set_bit(0, &session->dead))
		वापस;

	trace_delete_session(session);
	l2tp_session_unhash(session);
	l2tp_session_queue_purge(session);
	अगर (session->session_बंद)
		(*session->session_बंद)(session);

	l2tp_session_dec_refcount(session);
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_session_delete);

/* We come here whenever a session's send_seq, cookie_len or
 * l2specअगरic_type parameters are set.
 */
व्योम l2tp_session_set_header_len(काष्ठा l2tp_session *session, पूर्णांक version)
अणु
	अगर (version == L2TP_HDR_VER_2) अणु
		session->hdr_len = 6;
		अगर (session->send_seq)
			session->hdr_len += 4;
	पूर्ण अन्यथा अणु
		session->hdr_len = 4 + session->cookie_len;
		session->hdr_len += l2tp_get_l2specअगरic_len(session);
		अगर (session->tunnel->encap == L2TP_ENCAPTYPE_UDP)
			session->hdr_len += 4;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_session_set_header_len);

काष्ठा l2tp_session *l2tp_session_create(पूर्णांक priv_size, काष्ठा l2tp_tunnel *tunnel, u32 session_id,
					 u32 peer_session_id, काष्ठा l2tp_session_cfg *cfg)
अणु
	काष्ठा l2tp_session *session;

	session = kzalloc(माप(*session) + priv_size, GFP_KERNEL);
	अगर (session) अणु
		session->magic = L2TP_SESSION_MAGIC;
		session->tunnel = tunnel;

		session->session_id = session_id;
		session->peer_session_id = peer_session_id;
		session->nr = 0;
		अगर (tunnel->version == L2TP_HDR_VER_2)
			session->nr_max = 0xffff;
		अन्यथा
			session->nr_max = 0xffffff;
		session->nr_winकरोw_size = session->nr_max / 2;
		session->nr_oos_count_max = 4;

		/* Use NR of first received packet */
		session->reorder_skip = 1;

		प्र_लिखो(&session->name[0], "sess %u/%u",
			tunnel->tunnel_id, session->session_id);

		skb_queue_head_init(&session->reorder_q);

		INIT_HLIST_NODE(&session->hlist);
		INIT_HLIST_NODE(&session->global_hlist);

		अगर (cfg) अणु
			session->pwtype = cfg->pw_type;
			session->send_seq = cfg->send_seq;
			session->recv_seq = cfg->recv_seq;
			session->lns_mode = cfg->lns_mode;
			session->reorder_समयout = cfg->reorder_समयout;
			session->l2specअगरic_type = cfg->l2specअगरic_type;
			session->cookie_len = cfg->cookie_len;
			स_नकल(&session->cookie[0], &cfg->cookie[0], cfg->cookie_len);
			session->peer_cookie_len = cfg->peer_cookie_len;
			स_नकल(&session->peer_cookie[0], &cfg->peer_cookie[0], cfg->peer_cookie_len);
		पूर्ण

		l2tp_session_set_header_len(session, tunnel->version);

		refcount_set(&session->ref_count, 1);

		वापस session;
	पूर्ण

	वापस ERR_PTR(-ENOMEM);
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_session_create);

/*****************************************************************************
 * Init and cleanup
 *****************************************************************************/

अटल __net_init पूर्णांक l2tp_init_net(काष्ठा net *net)
अणु
	काष्ठा l2tp_net *pn = net_generic(net, l2tp_net_id);
	पूर्णांक hash;

	INIT_LIST_HEAD(&pn->l2tp_tunnel_list);
	spin_lock_init(&pn->l2tp_tunnel_list_lock);

	क्रम (hash = 0; hash < L2TP_HASH_SIZE_2; hash++)
		INIT_HLIST_HEAD(&pn->l2tp_session_hlist[hash]);

	spin_lock_init(&pn->l2tp_session_hlist_lock);

	वापस 0;
पूर्ण

अटल __net_निकास व्योम l2tp_निकास_net(काष्ठा net *net)
अणु
	काष्ठा l2tp_net *pn = l2tp_pernet(net);
	काष्ठा l2tp_tunnel *tunnel = शून्य;
	पूर्णांक hash;

	rcu_पढ़ो_lock_bh();
	list_क्रम_each_entry_rcu(tunnel, &pn->l2tp_tunnel_list, list) अणु
		l2tp_tunnel_delete(tunnel);
	पूर्ण
	rcu_पढ़ो_unlock_bh();

	अगर (l2tp_wq)
		flush_workqueue(l2tp_wq);
	rcu_barrier();

	क्रम (hash = 0; hash < L2TP_HASH_SIZE_2; hash++)
		WARN_ON_ONCE(!hlist_empty(&pn->l2tp_session_hlist[hash]));
पूर्ण

अटल काष्ठा pernet_operations l2tp_net_ops = अणु
	.init = l2tp_init_net,
	.निकास = l2tp_निकास_net,
	.id   = &l2tp_net_id,
	.size = माप(काष्ठा l2tp_net),
पूर्ण;

अटल पूर्णांक __init l2tp_init(व्योम)
अणु
	पूर्णांक rc = 0;

	rc = रेजिस्टर_pernet_device(&l2tp_net_ops);
	अगर (rc)
		जाओ out;

	l2tp_wq = alloc_workqueue("l2tp", WQ_UNBOUND, 0);
	अगर (!l2tp_wq) अणु
		pr_err("alloc_workqueue failed\n");
		unरेजिस्टर_pernet_device(&l2tp_net_ops);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	pr_info("L2TP core driver, %s\n", L2TP_DRV_VERSION);

out:
	वापस rc;
पूर्ण

अटल व्योम __निकास l2tp_निकास(व्योम)
अणु
	unरेजिस्टर_pernet_device(&l2tp_net_ops);
	अगर (l2tp_wq) अणु
		destroy_workqueue(l2tp_wq);
		l2tp_wq = शून्य;
	पूर्ण
पूर्ण

module_init(l2tp_init);
module_निकास(l2tp_निकास);

MODULE_AUTHOR("James Chapman <jchapman@katalix.com>");
MODULE_DESCRIPTION("L2TP core");
MODULE_LICENSE("GPL");
MODULE_VERSION(L2TP_DRV_VERSION);
