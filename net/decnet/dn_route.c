<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DECnet       An implementation of the DECnet protocol suite क्रम the LINUX
 *              operating प्रणाली.  DECnet is implemented using the  BSD Socket
 *              पूर्णांकerface as the means of communication with the user level.
 *
 *              DECnet Routing Functions (Endnode and Router)
 *
 * Authors:     Steve Whitehouse <SteveW@ACM.org>
 *              Eduarकरो Marcelo Serrat <emserrat@geocities.com>
 *
 * Changes:
 *              Steve Whitehouse : Fixes to allow "intra-ethernet" and
 *                                 "return-to-sender" bits on outgoing
 *                                 packets.
 *		Steve Whitehouse : Timeouts क्रम cached routes.
 *              Steve Whitehouse : Use dst cache क्रम input routes too.
 *              Steve Whitehouse : Fixed error values in dn_send_skb.
 *              Steve Whitehouse : Rework routing functions to better fit
 *                                 DECnet routing design
 *              Alexey Kuznetsov : New SMP locking
 *              Steve Whitehouse : More SMP locking changes & dn_cache_dump()
 *              Steve Whitehouse : Prerouting NF hook, now really is prerouting.
 *				   Fixed possible skb leak in rtnetlink funcs.
 *              Steve Whitehouse : Dave Miller's dynamic hash table sizing and
 *                                 Alexey Kuznetsov's finer grained locking
 *                                 from ipv4/route.c.
 *              Steve Whitehouse : Routing is now starting to look like a
 *                                 sensible set of code now, मुख्यly due to
 *                                 my copying the IPv4 routing code. The
 *                                 hooks here are modअगरied and will जारी
 *                                 to evolve क्रम a जबतक.
 *              Steve Whitehouse : Real SMP at last :-) Also new netfilter
 *                                 stuff. Look out raw sockets your days
 *                                 are numbered!
 *              Steve Whitehouse : Added वापस-to-sender functions. Added
 *                                 backlog congestion level वापस codes.
 *		Steve Whitehouse : Fixed bug where routes were set up with
 *                                 no ref count on net devices.
 *              Steve Whitehouse : RCU क्रम the route cache
 *              Steve Whitehouse : Preparations क्रम the flow cache
 *              Steve Whitehouse : Prepare क्रम nonlinear skbs
 */

/******************************************************************************
    (c) 1995-1998 E.M. Serrat		emserrat@geocities.com

*******************************************************************************/

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/inet.h>
#समावेश <linux/route.h>
#समावेश <linux/in_route.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <linux/mm.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/माला.स>
#समावेश <linux/netfilter_decnet.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/बार.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <net/net_namespace.h>
#समावेश <net/netlink.h>
#समावेश <net/neighbour.h>
#समावेश <net/dst.h>
#समावेश <net/flow.h>
#समावेश <net/fib_rules.h>
#समावेश <net/dn.h>
#समावेश <net/dn_dev.h>
#समावेश <net/dn_nsp.h>
#समावेश <net/dn_route.h>
#समावेश <net/dn_neigh.h>
#समावेश <net/dn_fib.h>

काष्ठा dn_rt_hash_bucket अणु
	काष्ठा dn_route __rcu *chain;
	spinlock_t lock;
पूर्ण;

बाह्य काष्ठा neigh_table dn_neigh_table;


अटल अचिन्हित अक्षर dn_hiord_addr[6] = अणु0xAA, 0x00, 0x04, 0x00, 0x00, 0x00पूर्ण;

अटल स्थिर पूर्णांक dn_rt_min_delay = 2 * HZ;
अटल स्थिर पूर्णांक dn_rt_max_delay = 10 * HZ;
अटल स्थिर पूर्णांक dn_rt_mtu_expires = 10 * 60 * HZ;

अटल अचिन्हित दीर्घ dn_rt_deadline;

अटल पूर्णांक dn_dst_gc(काष्ठा dst_ops *ops);
अटल काष्ठा dst_entry *dn_dst_check(काष्ठा dst_entry *, __u32);
अटल अचिन्हित पूर्णांक dn_dst_शेष_advmss(स्थिर काष्ठा dst_entry *dst);
अटल अचिन्हित पूर्णांक dn_dst_mtu(स्थिर काष्ठा dst_entry *dst);
अटल व्योम dn_dst_destroy(काष्ठा dst_entry *);
अटल व्योम dn_dst_अगरकरोwn(काष्ठा dst_entry *, काष्ठा net_device *dev, पूर्णांक how);
अटल काष्ठा dst_entry *dn_dst_negative_advice(काष्ठा dst_entry *);
अटल व्योम dn_dst_link_failure(काष्ठा sk_buff *);
अटल व्योम dn_dst_update_pmtu(काष्ठा dst_entry *dst, काष्ठा sock *sk,
			       काष्ठा sk_buff *skb , u32 mtu,
			       bool confirm_neigh);
अटल व्योम dn_dst_redirect(काष्ठा dst_entry *dst, काष्ठा sock *sk,
			    काष्ठा sk_buff *skb);
अटल काष्ठा neighbour *dn_dst_neigh_lookup(स्थिर काष्ठा dst_entry *dst,
					     काष्ठा sk_buff *skb,
					     स्थिर व्योम *daddr);
अटल पूर्णांक dn_route_input(काष्ठा sk_buff *);
अटल व्योम dn_run_flush(काष्ठा समयr_list *unused);

अटल काष्ठा dn_rt_hash_bucket *dn_rt_hash_table;
अटल अचिन्हित पूर्णांक dn_rt_hash_mask;

अटल काष्ठा समयr_list dn_route_समयr;
अटल DEFINE_TIMER(dn_rt_flush_समयr, dn_run_flush);
पूर्णांक decnet_dst_gc_पूर्णांकerval = 2;

अटल काष्ठा dst_ops dn_dst_ops = अणु
	.family =		PF_DECnet,
	.gc_thresh =		128,
	.gc =			dn_dst_gc,
	.check =		dn_dst_check,
	.शेष_advmss =	dn_dst_शेष_advmss,
	.mtu =			dn_dst_mtu,
	.cow_metrics =		dst_cow_metrics_generic,
	.destroy =		dn_dst_destroy,
	.अगरकरोwn =		dn_dst_अगरकरोwn,
	.negative_advice =	dn_dst_negative_advice,
	.link_failure =		dn_dst_link_failure,
	.update_pmtu =		dn_dst_update_pmtu,
	.redirect =		dn_dst_redirect,
	.neigh_lookup =		dn_dst_neigh_lookup,
पूर्ण;

अटल व्योम dn_dst_destroy(काष्ठा dst_entry *dst)
अणु
	काष्ठा dn_route *rt = (काष्ठा dn_route *) dst;

	अगर (rt->n)
		neigh_release(rt->n);
	dst_destroy_metrics_generic(dst);
पूर्ण

अटल व्योम dn_dst_अगरकरोwn(काष्ठा dst_entry *dst, काष्ठा net_device *dev, पूर्णांक how)
अणु
	अगर (how) अणु
		काष्ठा dn_route *rt = (काष्ठा dn_route *) dst;
		काष्ठा neighbour *n = rt->n;

		अगर (n && n->dev == dev) अणु
			n->dev = dev_net(dev)->loopback_dev;
			dev_hold(n->dev);
			dev_put(dev);
		पूर्ण
	पूर्ण
पूर्ण

अटल __अंतरभूत__ अचिन्हित पूर्णांक dn_hash(__le16 src, __le16 dst)
अणु
	__u16 पंचांगp = (__u16 __क्रमce)(src ^ dst);
	पंचांगp ^= (पंचांगp >> 3);
	पंचांगp ^= (पंचांगp >> 5);
	पंचांगp ^= (पंचांगp >> 10);
	वापस dn_rt_hash_mask & (अचिन्हित पूर्णांक)पंचांगp;
पूर्ण

अटल व्योम dn_dst_check_expire(काष्ठा समयr_list *unused)
अणु
	पूर्णांक i;
	काष्ठा dn_route *rt;
	काष्ठा dn_route __rcu **rtp;
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित दीर्घ expire = 120 * HZ;

	क्रम (i = 0; i <= dn_rt_hash_mask; i++) अणु
		rtp = &dn_rt_hash_table[i].chain;

		spin_lock(&dn_rt_hash_table[i].lock);
		जबतक ((rt = rcu_dereference_रक्षित(*rtp,
						lockdep_is_held(&dn_rt_hash_table[i].lock))) != शून्य) अणु
			अगर (atomic_पढ़ो(&rt->dst.__refcnt) > 1 ||
			    (now - rt->dst.lastuse) < expire) अणु
				rtp = &rt->dn_next;
				जारी;
			पूर्ण
			*rtp = rt->dn_next;
			rt->dn_next = शून्य;
			dst_dev_put(&rt->dst);
			dst_release(&rt->dst);
		पूर्ण
		spin_unlock(&dn_rt_hash_table[i].lock);

		अगर ((jअगरfies - now) > 0)
			अवरोध;
	पूर्ण

	mod_समयr(&dn_route_समयr, now + decnet_dst_gc_पूर्णांकerval * HZ);
पूर्ण

अटल पूर्णांक dn_dst_gc(काष्ठा dst_ops *ops)
अणु
	काष्ठा dn_route *rt;
	काष्ठा dn_route __rcu **rtp;
	पूर्णांक i;
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित दीर्घ expire = 10 * HZ;

	क्रम (i = 0; i <= dn_rt_hash_mask; i++) अणु

		spin_lock_bh(&dn_rt_hash_table[i].lock);
		rtp = &dn_rt_hash_table[i].chain;

		जबतक ((rt = rcu_dereference_रक्षित(*rtp,
						lockdep_is_held(&dn_rt_hash_table[i].lock))) != शून्य) अणु
			अगर (atomic_पढ़ो(&rt->dst.__refcnt) > 1 ||
			    (now - rt->dst.lastuse) < expire) अणु
				rtp = &rt->dn_next;
				जारी;
			पूर्ण
			*rtp = rt->dn_next;
			rt->dn_next = शून्य;
			dst_dev_put(&rt->dst);
			dst_release(&rt->dst);
			अवरोध;
		पूर्ण
		spin_unlock_bh(&dn_rt_hash_table[i].lock);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The decnet standards करोn't impose a particular minimum mtu, what they
 * करो insist on is that the routing layer accepts a datagram of at least
 * 230 bytes दीर्घ. Here we have to subtract the routing header length from
 * 230 to get the minimum acceptable mtu. If there is no neighbour, then we
 * assume the worst and use a दीर्घ header size.
 *
 * We update both the mtu and the advertised mss (i.e. the segment size we
 * advertise to the other end).
 */
अटल व्योम dn_dst_update_pmtu(काष्ठा dst_entry *dst, काष्ठा sock *sk,
			       काष्ठा sk_buff *skb, u32 mtu,
			       bool confirm_neigh)
अणु
	काष्ठा dn_route *rt = (काष्ठा dn_route *) dst;
	काष्ठा neighbour *n = rt->n;
	u32 min_mtu = 230;
	काष्ठा dn_dev *dn;

	dn = n ? rcu_dereference_raw(n->dev->dn_ptr) : शून्य;

	अगर (dn && dn->use_दीर्घ == 0)
		min_mtu -= 6;
	अन्यथा
		min_mtu -= 21;

	अगर (dst_metric(dst, RTAX_MTU) > mtu && mtu >= min_mtu) अणु
		अगर (!(dst_metric_locked(dst, RTAX_MTU))) अणु
			dst_metric_set(dst, RTAX_MTU, mtu);
			dst_set_expires(dst, dn_rt_mtu_expires);
		पूर्ण
		अगर (!(dst_metric_locked(dst, RTAX_ADVMSS))) अणु
			u32 mss = mtu - DN_MAX_NSP_DATA_HEADER;
			u32 existing_mss = dst_metric_raw(dst, RTAX_ADVMSS);
			अगर (!existing_mss || existing_mss > mss)
				dst_metric_set(dst, RTAX_ADVMSS, mss);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dn_dst_redirect(काष्ठा dst_entry *dst, काष्ठा sock *sk,
			    काष्ठा sk_buff *skb)
अणु
पूर्ण

/*
 * When a route has been marked obsolete. (e.g. routing cache flush)
 */
अटल काष्ठा dst_entry *dn_dst_check(काष्ठा dst_entry *dst, __u32 cookie)
अणु
	वापस शून्य;
पूर्ण

अटल काष्ठा dst_entry *dn_dst_negative_advice(काष्ठा dst_entry *dst)
अणु
	dst_release(dst);
	वापस शून्य;
पूर्ण

अटल व्योम dn_dst_link_failure(काष्ठा sk_buff *skb)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक compare_keys(काष्ठा flowidn *fl1, काष्ठा flowidn *fl2)
अणु
	वापस ((fl1->daddr ^ fl2->daddr) |
		(fl1->saddr ^ fl2->saddr) |
		(fl1->flowidn_mark ^ fl2->flowidn_mark) |
		(fl1->flowidn_scope ^ fl2->flowidn_scope) |
		(fl1->flowidn_oअगर ^ fl2->flowidn_oअगर) |
		(fl1->flowidn_iअगर ^ fl2->flowidn_iअगर)) == 0;
पूर्ण

अटल पूर्णांक dn_insert_route(काष्ठा dn_route *rt, अचिन्हित पूर्णांक hash, काष्ठा dn_route **rp)
अणु
	काष्ठा dn_route *rth;
	काष्ठा dn_route __rcu **rthp;
	अचिन्हित दीर्घ now = jअगरfies;

	rthp = &dn_rt_hash_table[hash].chain;

	spin_lock_bh(&dn_rt_hash_table[hash].lock);
	जबतक ((rth = rcu_dereference_रक्षित(*rthp,
						lockdep_is_held(&dn_rt_hash_table[hash].lock))) != शून्य) अणु
		अगर (compare_keys(&rth->fld, &rt->fld)) अणु
			/* Put it first */
			*rthp = rth->dn_next;
			rcu_assign_poपूर्णांकer(rth->dn_next,
					   dn_rt_hash_table[hash].chain);
			rcu_assign_poपूर्णांकer(dn_rt_hash_table[hash].chain, rth);

			dst_hold_and_use(&rth->dst, now);
			spin_unlock_bh(&dn_rt_hash_table[hash].lock);

			dst_release_immediate(&rt->dst);
			*rp = rth;
			वापस 0;
		पूर्ण
		rthp = &rth->dn_next;
	पूर्ण

	rcu_assign_poपूर्णांकer(rt->dn_next, dn_rt_hash_table[hash].chain);
	rcu_assign_poपूर्णांकer(dn_rt_hash_table[hash].chain, rt);

	dst_hold_and_use(&rt->dst, now);
	spin_unlock_bh(&dn_rt_hash_table[hash].lock);
	*rp = rt;
	वापस 0;
पूर्ण

अटल व्योम dn_run_flush(काष्ठा समयr_list *unused)
अणु
	पूर्णांक i;
	काष्ठा dn_route *rt, *next;

	क्रम (i = 0; i < dn_rt_hash_mask; i++) अणु
		spin_lock_bh(&dn_rt_hash_table[i].lock);

		rt = xchg((काष्ठा dn_route **)&dn_rt_hash_table[i].chain, शून्य);
		अगर (!rt)
			जाओ nothing_to_declare;

		क्रम (; rt; rt = next) अणु
			next = rcu_dereference_raw(rt->dn_next);
			RCU_INIT_POINTER(rt->dn_next, शून्य);
			dst_dev_put(&rt->dst);
			dst_release(&rt->dst);
		पूर्ण

nothing_to_declare:
		spin_unlock_bh(&dn_rt_hash_table[i].lock);
	पूर्ण
पूर्ण

अटल DEFINE_SPINLOCK(dn_rt_flush_lock);

व्योम dn_rt_cache_flush(पूर्णांक delay)
अणु
	अचिन्हित दीर्घ now = jअगरfies;
	पूर्णांक user_mode = !in_पूर्णांकerrupt();

	अगर (delay < 0)
		delay = dn_rt_min_delay;

	spin_lock_bh(&dn_rt_flush_lock);

	अगर (del_समयr(&dn_rt_flush_समयr) && delay > 0 && dn_rt_deadline) अणु
		दीर्घ पंचांगo = (दीर्घ)(dn_rt_deadline - now);

		अगर (user_mode && पंचांगo < dn_rt_max_delay - dn_rt_min_delay)
			पंचांगo = 0;

		अगर (delay > पंचांगo)
			delay = पंचांगo;
	पूर्ण

	अगर (delay <= 0) अणु
		spin_unlock_bh(&dn_rt_flush_lock);
		dn_run_flush(शून्य);
		वापस;
	पूर्ण

	अगर (dn_rt_deadline == 0)
		dn_rt_deadline = now + dn_rt_max_delay;

	dn_rt_flush_समयr.expires = now + delay;
	add_समयr(&dn_rt_flush_समयr);
	spin_unlock_bh(&dn_rt_flush_lock);
पूर्ण

/**
 * dn_वापस_लघु - Return a लघु packet to its sender
 * @skb: The packet to वापस
 *
 */
अटल पूर्णांक dn_वापस_लघु(काष्ठा sk_buff *skb)
अणु
	काष्ठा dn_skb_cb *cb;
	अचिन्हित अक्षर *ptr;
	__le16 *src;
	__le16 *dst;

	/* Add back headers */
	skb_push(skb, skb->data - skb_network_header(skb));

	skb = skb_unshare(skb, GFP_ATOMIC);
	अगर (!skb)
		वापस NET_RX_DROP;

	cb = DN_SKB_CB(skb);
	/* Skip packet length and poपूर्णांक to flags */
	ptr = skb->data + 2;
	*ptr++ = (cb->rt_flags & ~DN_RT_F_RQR) | DN_RT_F_RTS;

	dst = (__le16 *)ptr;
	ptr += 2;
	src = (__le16 *)ptr;
	ptr += 2;
	*ptr = 0; /* Zero hop count */

	swap(*src, *dst);

	skb->pkt_type = PACKET_OUTGOING;
	dn_rt_finish_output(skb, शून्य, शून्य);
	वापस NET_RX_SUCCESS;
पूर्ण

/**
 * dn_वापस_दीर्घ - Return a दीर्घ packet to its sender
 * @skb: The दीर्घ क्रमmat packet to वापस
 *
 */
अटल पूर्णांक dn_वापस_दीर्घ(काष्ठा sk_buff *skb)
अणु
	काष्ठा dn_skb_cb *cb;
	अचिन्हित अक्षर *ptr;
	अचिन्हित अक्षर *src_addr, *dst_addr;
	अचिन्हित अक्षर पंचांगp[ETH_ALEN];

	/* Add back all headers */
	skb_push(skb, skb->data - skb_network_header(skb));

	skb = skb_unshare(skb, GFP_ATOMIC);
	अगर (!skb)
		वापस NET_RX_DROP;

	cb = DN_SKB_CB(skb);
	/* Ignore packet length and poपूर्णांक to flags */
	ptr = skb->data + 2;

	/* Skip padding */
	अगर (*ptr & DN_RT_F_PF) अणु
		अक्षर padlen = (*ptr & ~DN_RT_F_PF);
		ptr += padlen;
	पूर्ण

	*ptr++ = (cb->rt_flags & ~DN_RT_F_RQR) | DN_RT_F_RTS;
	ptr += 2;
	dst_addr = ptr;
	ptr += 8;
	src_addr = ptr;
	ptr += 6;
	*ptr = 0; /* Zero hop count */

	/* Swap source and destination */
	स_नकल(पंचांगp, src_addr, ETH_ALEN);
	स_नकल(src_addr, dst_addr, ETH_ALEN);
	स_नकल(dst_addr, पंचांगp, ETH_ALEN);

	skb->pkt_type = PACKET_OUTGOING;
	dn_rt_finish_output(skb, dst_addr, src_addr);
	वापस NET_RX_SUCCESS;
पूर्ण

/**
 * dn_route_rx_packet - Try and find a route क्रम an incoming packet
 * @net: The applicable net namespace
 * @sk: Socket packet transmitted on
 * @skb: The packet to find a route क्रम
 *
 * Returns: result of input function अगर route is found, error code otherwise
 */
अटल पूर्णांक dn_route_rx_packet(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dn_skb_cb *cb;
	पूर्णांक err;

	err = dn_route_input(skb);
	अगर (err == 0)
		वापस dst_input(skb);

	cb = DN_SKB_CB(skb);
	अगर (decnet_debug_level & 4) अणु
		अक्षर *devname = skb->dev ? skb->dev->name : "???";

		prपूर्णांकk(KERN_DEBUG
			"DECnet: dn_route_rx_packet: rt_flags=0x%02x dev=%s len=%d src=0x%04hx dst=0x%04hx err=%d type=%d\n",
			(पूर्णांक)cb->rt_flags, devname, skb->len,
			le16_to_cpu(cb->src), le16_to_cpu(cb->dst),
			err, skb->pkt_type);
	पूर्ण

	अगर ((skb->pkt_type == PACKET_HOST) && (cb->rt_flags & DN_RT_F_RQR)) अणु
		चयन (cb->rt_flags & DN_RT_PKT_MSK) अणु
		हाल DN_RT_PKT_SHORT:
			वापस dn_वापस_लघु(skb);
		हाल DN_RT_PKT_LONG:
			वापस dn_वापस_दीर्घ(skb);
		पूर्ण
	पूर्ण

	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण

अटल पूर्णांक dn_route_rx_दीर्घ(काष्ठा sk_buff *skb)
अणु
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);
	अचिन्हित अक्षर *ptr = skb->data;

	अगर (!pskb_may_pull(skb, 21)) /* 20 क्रम दीर्घ header, 1 क्रम लघुest nsp */
		जाओ drop_it;

	skb_pull(skb, 20);
	skb_reset_transport_header(skb);

	/* Destination info */
	ptr += 2;
	cb->dst = dn_eth2dn(ptr);
	अगर (स_भेद(ptr, dn_hiord_addr, 4) != 0)
		जाओ drop_it;
	ptr += 6;


	/* Source info */
	ptr += 2;
	cb->src = dn_eth2dn(ptr);
	अगर (स_भेद(ptr, dn_hiord_addr, 4) != 0)
		जाओ drop_it;
	ptr += 6;
	/* Other junk */
	ptr++;
	cb->hops = *ptr++; /* Visit Count */

	वापस NF_HOOK(NFPROTO_DECNET, NF_DN_PRE_ROUTING,
		       &init_net, शून्य, skb, skb->dev, शून्य,
		       dn_route_rx_packet);

drop_it:
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण



अटल पूर्णांक dn_route_rx_लघु(काष्ठा sk_buff *skb)
अणु
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);
	अचिन्हित अक्षर *ptr = skb->data;

	अगर (!pskb_may_pull(skb, 6)) /* 5 क्रम लघु header + 1 क्रम लघुest nsp */
		जाओ drop_it;

	skb_pull(skb, 5);
	skb_reset_transport_header(skb);

	cb->dst = *(__le16 *)ptr;
	ptr += 2;
	cb->src = *(__le16 *)ptr;
	ptr += 2;
	cb->hops = *ptr & 0x3f;

	वापस NF_HOOK(NFPROTO_DECNET, NF_DN_PRE_ROUTING,
		       &init_net, शून्य, skb, skb->dev, शून्य,
		       dn_route_rx_packet);

drop_it:
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण

अटल पूर्णांक dn_route_discard(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	/*
	 * I know we drop the packet here, but thats considered success in
	 * this हाल
	 */
	kमुक्त_skb(skb);
	वापस NET_RX_SUCCESS;
पूर्ण

अटल पूर्णांक dn_route_ptp_hello(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	dn_dev_hello(skb);
	dn_neigh_poपूर्णांकopoपूर्णांक_hello(skb);
	वापस NET_RX_SUCCESS;
पूर्ण

पूर्णांक dn_route_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev, काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	काष्ठा dn_skb_cb *cb;
	अचिन्हित अक्षर flags = 0;
	__u16 len = le16_to_cpu(*(__le16 *)skb->data);
	काष्ठा dn_dev *dn = rcu_dereference(dev->dn_ptr);
	अचिन्हित अक्षर padlen = 0;

	अगर (!net_eq(dev_net(dev), &init_net))
		जाओ dump_it;

	अगर (dn == शून्य)
		जाओ dump_it;

	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (!skb)
		जाओ out;

	अगर (!pskb_may_pull(skb, 3))
		जाओ dump_it;

	skb_pull(skb, 2);

	अगर (len > skb->len)
		जाओ dump_it;

	skb_trim(skb, len);

	flags = *skb->data;

	cb = DN_SKB_CB(skb);
	cb->stamp = jअगरfies;
	cb->iअगर = dev->अगरindex;

	/*
	 * If we have padding, हटाओ it.
	 */
	अगर (flags & DN_RT_F_PF) अणु
		padlen = flags & ~DN_RT_F_PF;
		अगर (!pskb_may_pull(skb, padlen + 1))
			जाओ dump_it;
		skb_pull(skb, padlen);
		flags = *skb->data;
	पूर्ण

	skb_reset_network_header(skb);

	/*
	 * Weed out future version DECnet
	 */
	अगर (flags & DN_RT_F_VER)
		जाओ dump_it;

	cb->rt_flags = flags;

	अगर (decnet_debug_level & 1)
		prपूर्णांकk(KERN_DEBUG
			"dn_route_rcv: got 0x%02x from %s [%d %d %d]\n",
			(पूर्णांक)flags, dev->name, len, skb->len,
			padlen);

	अगर (flags & DN_RT_PKT_CNTL) अणु
		अगर (unlikely(skb_linearize(skb)))
			जाओ dump_it;

		चयन (flags & DN_RT_CNTL_MSK) अणु
		हाल DN_RT_PKT_INIT:
			dn_dev_init_pkt(skb);
			अवरोध;
		हाल DN_RT_PKT_VERI:
			dn_dev_veri_pkt(skb);
			अवरोध;
		पूर्ण

		अगर (dn->parms.state != DN_DEV_S_RU)
			जाओ dump_it;

		चयन (flags & DN_RT_CNTL_MSK) अणु
		हाल DN_RT_PKT_HELO:
			वापस NF_HOOK(NFPROTO_DECNET, NF_DN_HELLO,
				       &init_net, शून्य, skb, skb->dev, शून्य,
				       dn_route_ptp_hello);

		हाल DN_RT_PKT_L1RT:
		हाल DN_RT_PKT_L2RT:
			वापस NF_HOOK(NFPROTO_DECNET, NF_DN_ROUTE,
				       &init_net, शून्य, skb, skb->dev, शून्य,
				       dn_route_discard);
		हाल DN_RT_PKT_ERTH:
			वापस NF_HOOK(NFPROTO_DECNET, NF_DN_HELLO,
				       &init_net, शून्य, skb, skb->dev, शून्य,
				       dn_neigh_router_hello);

		हाल DN_RT_PKT_EEDH:
			वापस NF_HOOK(NFPROTO_DECNET, NF_DN_HELLO,
				       &init_net, शून्य, skb, skb->dev, शून्य,
				       dn_neigh_endnode_hello);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (dn->parms.state != DN_DEV_S_RU)
			जाओ dump_it;

		skb_pull(skb, 1); /* Pull flags */

		चयन (flags & DN_RT_PKT_MSK) अणु
		हाल DN_RT_PKT_LONG:
			वापस dn_route_rx_दीर्घ(skb);
		हाल DN_RT_PKT_SHORT:
			वापस dn_route_rx_लघु(skb);
		पूर्ण
	पूर्ण

dump_it:
	kमुक्त_skb(skb);
out:
	वापस NET_RX_DROP;
पूर्ण

अटल पूर्णांक dn_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा dn_route *rt = (काष्ठा dn_route *)dst;
	काष्ठा net_device *dev = dst->dev;
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);

	पूर्णांक err = -EINVAL;

	अगर (rt->n == शून्य)
		जाओ error;

	skb->dev = dev;

	cb->src = rt->rt_saddr;
	cb->dst = rt->rt_daddr;

	/*
	 * Always set the Intra-Ethernet bit on all outgoing packets
	 * originated on this node. Only valid flag from upper layers
	 * is वापस-to-sender-requested. Set hop count to 0 too.
	 */
	cb->rt_flags &= ~DN_RT_F_RQR;
	cb->rt_flags |= DN_RT_F_IE;
	cb->hops = 0;

	वापस NF_HOOK(NFPROTO_DECNET, NF_DN_LOCAL_OUT,
		       &init_net, sk, skb, शून्य, dev,
		       dn_to_neigh_output);

error:
	net_dbg_ratelimited("dn_output: This should not happen\n");

	kमुक्त_skb(skb);

	वापस err;
पूर्ण

अटल पूर्णांक dn_क्रमward(काष्ठा sk_buff *skb)
अणु
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा dn_dev *dn_db = rcu_dereference(dst->dev->dn_ptr);
	काष्ठा dn_route *rt;
	पूर्णांक header_len;
	काष्ठा net_device *dev = skb->dev;

	अगर (skb->pkt_type != PACKET_HOST)
		जाओ drop;

	/* Ensure that we have enough space क्रम headers */
	rt = (काष्ठा dn_route *)skb_dst(skb);
	header_len = dn_db->use_दीर्घ ? 21 : 6;
	अगर (skb_cow(skb, LL_RESERVED_SPACE(rt->dst.dev)+header_len))
		जाओ drop;

	/*
	 * Hop count exceeded.
	 */
	अगर (++cb->hops > 30)
		जाओ drop;

	skb->dev = rt->dst.dev;

	/*
	 * If packet goes out same पूर्णांकerface it came in on, then set
	 * the Intra-Ethernet bit. This has no effect क्रम लघु
	 * packets, so we करोn't need to test क्रम them here.
	 */
	cb->rt_flags &= ~DN_RT_F_IE;
	अगर (rt->rt_flags & RTCF_DOREसूचीECT)
		cb->rt_flags |= DN_RT_F_IE;

	वापस NF_HOOK(NFPROTO_DECNET, NF_DN_FORWARD,
		       &init_net, शून्य, skb, dev, skb->dev,
		       dn_to_neigh_output);

drop:
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण

/*
 * Used to catch bugs. This should never normally get
 * called.
 */
अटल पूर्णांक dn_rt_bug_out(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);

	net_dbg_ratelimited("dn_rt_bug: skb from:%04x to:%04x\n",
			    le16_to_cpu(cb->src), le16_to_cpu(cb->dst));

	kमुक्त_skb(skb);

	वापस NET_RX_DROP;
पूर्ण

अटल पूर्णांक dn_rt_bug(काष्ठा sk_buff *skb)
अणु
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);

	net_dbg_ratelimited("dn_rt_bug: skb from:%04x to:%04x\n",
			    le16_to_cpu(cb->src), le16_to_cpu(cb->dst));

	kमुक्त_skb(skb);

	वापस NET_RX_DROP;
पूर्ण

अटल अचिन्हित पूर्णांक dn_dst_शेष_advmss(स्थिर काष्ठा dst_entry *dst)
अणु
	वापस dn_mss_from_pmtu(dst->dev, dst_mtu(dst));
पूर्ण

अटल अचिन्हित पूर्णांक dn_dst_mtu(स्थिर काष्ठा dst_entry *dst)
अणु
	अचिन्हित पूर्णांक mtu = dst_metric_raw(dst, RTAX_MTU);

	वापस mtu ? : dst->dev->mtu;
पूर्ण

अटल काष्ठा neighbour *dn_dst_neigh_lookup(स्थिर काष्ठा dst_entry *dst,
					     काष्ठा sk_buff *skb,
					     स्थिर व्योम *daddr)
अणु
	वापस __neigh_lookup_त्रुटि_सं(&dn_neigh_table, daddr, dst->dev);
पूर्ण

अटल पूर्णांक dn_rt_set_next_hop(काष्ठा dn_route *rt, काष्ठा dn_fib_res *res)
अणु
	काष्ठा dn_fib_info *fi = res->fi;
	काष्ठा net_device *dev = rt->dst.dev;
	अचिन्हित पूर्णांक mss_metric;
	काष्ठा neighbour *n;

	अगर (fi) अणु
		अगर (DN_FIB_RES_GW(*res) &&
		    DN_FIB_RES_NH(*res).nh_scope == RT_SCOPE_LINK)
			rt->rt_gateway = DN_FIB_RES_GW(*res);
		dst_init_metrics(&rt->dst, fi->fib_metrics, true);
	पूर्ण
	rt->rt_type = res->type;

	अगर (dev != शून्य && rt->n == शून्य) अणु
		n = __neigh_lookup_त्रुटि_सं(&dn_neigh_table, &rt->rt_gateway, dev);
		अगर (IS_ERR(n))
			वापस PTR_ERR(n);
		rt->n = n;
	पूर्ण

	अगर (dst_metric(&rt->dst, RTAX_MTU) > rt->dst.dev->mtu)
		dst_metric_set(&rt->dst, RTAX_MTU, rt->dst.dev->mtu);
	mss_metric = dst_metric_raw(&rt->dst, RTAX_ADVMSS);
	अगर (mss_metric) अणु
		अचिन्हित पूर्णांक mss = dn_mss_from_pmtu(dev, dst_mtu(&rt->dst));
		अगर (mss_metric > mss)
			dst_metric_set(&rt->dst, RTAX_ADVMSS, mss);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dn_match_addr(__le16 addr1, __le16 addr2)
अणु
	__u16 पंचांगp = le16_to_cpu(addr1) ^ le16_to_cpu(addr2);
	पूर्णांक match = 16;
	जबतक (पंचांगp) अणु
		पंचांगp >>= 1;
		match--;
	पूर्ण
	वापस match;
पूर्ण

अटल __le16 dnet_select_source(स्थिर काष्ठा net_device *dev, __le16 daddr, पूर्णांक scope)
अणु
	__le16 saddr = 0;
	काष्ठा dn_dev *dn_db;
	काष्ठा dn_अगरaddr *अगरa;
	पूर्णांक best_match = 0;
	पूर्णांक ret;

	rcu_पढ़ो_lock();
	dn_db = rcu_dereference(dev->dn_ptr);
	क्रम (अगरa = rcu_dereference(dn_db->अगरa_list);
	     अगरa != शून्य;
	     अगरa = rcu_dereference(अगरa->अगरa_next)) अणु
		अगर (अगरa->अगरa_scope > scope)
			जारी;
		अगर (!daddr) अणु
			saddr = अगरa->अगरa_local;
			अवरोध;
		पूर्ण
		ret = dn_match_addr(daddr, अगरa->अगरa_local);
		अगर (ret > best_match)
			saddr = अगरa->अगरa_local;
		अगर (best_match == 0)
			saddr = अगरa->अगरa_local;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस saddr;
पूर्ण

अटल अंतरभूत __le16 __dn_fib_res_prefsrc(काष्ठा dn_fib_res *res)
अणु
	वापस dnet_select_source(DN_FIB_RES_DEV(*res), DN_FIB_RES_GW(*res), res->scope);
पूर्ण

अटल अंतरभूत __le16 dn_fib_rules_map_destination(__le16 daddr, काष्ठा dn_fib_res *res)
अणु
	__le16 mask = dnet_make_mask(res->prefixlen);
	वापस (daddr&~mask)|res->fi->fib_nh->nh_gw;
पूर्ण

अटल पूर्णांक dn_route_output_slow(काष्ठा dst_entry **pprt, स्थिर काष्ठा flowidn *oldflp, पूर्णांक try_hard)
अणु
	काष्ठा flowidn fld = अणु
		.daddr = oldflp->daddr,
		.saddr = oldflp->saddr,
		.flowidn_scope = RT_SCOPE_UNIVERSE,
		.flowidn_mark = oldflp->flowidn_mark,
		.flowidn_iअगर = LOOPBACK_IFINDEX,
		.flowidn_oअगर = oldflp->flowidn_oअगर,
	पूर्ण;
	काष्ठा dn_route *rt = शून्य;
	काष्ठा net_device *dev_out = शून्य, *dev;
	काष्ठा neighbour *neigh = शून्य;
	अचिन्हित पूर्णांक hash;
	अचिन्हित पूर्णांक flags = 0;
	काष्ठा dn_fib_res res = अणु .fi = शून्य, .type = RTN_UNICAST पूर्ण;
	पूर्णांक err;
	पूर्णांक मुक्त_res = 0;
	__le16 gateway = 0;

	अगर (decnet_debug_level & 16)
		prपूर्णांकk(KERN_DEBUG
		       "dn_route_output_slow: dst=%04x src=%04x mark=%d"
		       " iif=%d oif=%d\n", le16_to_cpu(oldflp->daddr),
		       le16_to_cpu(oldflp->saddr),
		       oldflp->flowidn_mark, LOOPBACK_IFINDEX,
		       oldflp->flowidn_oअगर);

	/* If we have an output पूर्णांकerface, verअगरy its a DECnet device */
	अगर (oldflp->flowidn_oअगर) अणु
		dev_out = dev_get_by_index(&init_net, oldflp->flowidn_oअगर);
		err = -ENODEV;
		अगर (dev_out && dev_out->dn_ptr == शून्य) अणु
			dev_put(dev_out);
			dev_out = शून्य;
		पूर्ण
		अगर (dev_out == शून्य)
			जाओ out;
	पूर्ण

	/* If we have a source address, verअगरy that its a local address */
	अगर (oldflp->saddr) अणु
		err = -EADDRNOTAVAIL;

		अगर (dev_out) अणु
			अगर (dn_dev_islocal(dev_out, oldflp->saddr))
				जाओ source_ok;
			dev_put(dev_out);
			जाओ out;
		पूर्ण
		rcu_पढ़ो_lock();
		क्रम_each_netdev_rcu(&init_net, dev) अणु
			अगर (!dev->dn_ptr)
				जारी;
			अगर (!dn_dev_islocal(dev, oldflp->saddr))
				जारी;
			अगर ((dev->flags & IFF_LOOPBACK) &&
			    oldflp->daddr &&
			    !dn_dev_islocal(dev, oldflp->daddr))
				जारी;

			dev_out = dev;
			अवरोध;
		पूर्ण
		rcu_पढ़ो_unlock();
		अगर (dev_out == शून्य)
			जाओ out;
		dev_hold(dev_out);
source_ok:
		;
	पूर्ण

	/* No destination? Assume its local */
	अगर (!fld.daddr) अणु
		fld.daddr = fld.saddr;

		अगर (dev_out)
			dev_put(dev_out);
		err = -EINVAL;
		dev_out = init_net.loopback_dev;
		अगर (!dev_out->dn_ptr)
			जाओ out;
		err = -EADDRNOTAVAIL;
		dev_hold(dev_out);
		अगर (!fld.daddr) अणु
			fld.daddr =
			fld.saddr = dnet_select_source(dev_out, 0,
						       RT_SCOPE_HOST);
			अगर (!fld.daddr)
				जाओ करोne;
		पूर्ण
		fld.flowidn_oअगर = LOOPBACK_IFINDEX;
		res.type = RTN_LOCAL;
		जाओ make_route;
	पूर्ण

	अगर (decnet_debug_level & 16)
		prपूर्णांकk(KERN_DEBUG
		       "dn_route_output_slow: initial checks complete."
		       " dst=%04x src=%04x oif=%d try_hard=%d\n",
		       le16_to_cpu(fld.daddr), le16_to_cpu(fld.saddr),
		       fld.flowidn_oअगर, try_hard);

	/*
	 * N.B. If the kernel is compiled without router support then
	 * dn_fib_lookup() will evaluate to non-zero so this अगर () block
	 * will always be executed.
	 */
	err = -ESRCH;
	अगर (try_hard || (err = dn_fib_lookup(&fld, &res)) != 0) अणु
		काष्ठा dn_dev *dn_db;
		अगर (err != -ESRCH)
			जाओ out;
		/*
		 * Here the fallback is basically the standard algorithm क्रम
		 * routing in endnodes which is described in the DECnet routing
		 * करोcs
		 *
		 * If we are not trying hard, look in neighbour cache.
		 * The result is tested to ensure that अगर a specअगरic output
		 * device/source address was requested, then we honour that
		 * here
		 */
		अगर (!try_hard) अणु
			neigh = neigh_lookup_nodev(&dn_neigh_table, &init_net, &fld.daddr);
			अगर (neigh) अणु
				अगर ((oldflp->flowidn_oअगर &&
				    (neigh->dev->अगरindex != oldflp->flowidn_oअगर)) ||
				    (oldflp->saddr &&
				    (!dn_dev_islocal(neigh->dev,
						     oldflp->saddr)))) अणु
					neigh_release(neigh);
					neigh = शून्य;
				पूर्ण अन्यथा अणु
					अगर (dev_out)
						dev_put(dev_out);
					अगर (dn_dev_islocal(neigh->dev, fld.daddr)) अणु
						dev_out = init_net.loopback_dev;
						res.type = RTN_LOCAL;
					पूर्ण अन्यथा अणु
						dev_out = neigh->dev;
					पूर्ण
					dev_hold(dev_out);
					जाओ select_source;
				पूर्ण
			पूर्ण
		पूर्ण

		/* Not there? Perhaps its a local address */
		अगर (dev_out == शून्य)
			dev_out = dn_dev_get_शेष();
		err = -ENODEV;
		अगर (dev_out == शून्य)
			जाओ out;
		dn_db = rcu_dereference_raw(dev_out->dn_ptr);
		अगर (!dn_db)
			जाओ e_inval;
		/* Possible improvement - check all devices क्रम local addr */
		अगर (dn_dev_islocal(dev_out, fld.daddr)) अणु
			dev_put(dev_out);
			dev_out = init_net.loopback_dev;
			dev_hold(dev_out);
			res.type = RTN_LOCAL;
			जाओ select_source;
		पूर्ण
		/* Not local either.... try sending it to the शेष router */
		neigh = neigh_clone(dn_db->router);
		BUG_ON(neigh && neigh->dev != dev_out);

		/* Ok then, we assume its directly connected and move on */
select_source:
		अगर (neigh)
			gateway = ((काष्ठा dn_neigh *)neigh)->addr;
		अगर (gateway == 0)
			gateway = fld.daddr;
		अगर (fld.saddr == 0) अणु
			fld.saddr = dnet_select_source(dev_out, gateway,
						       res.type == RTN_LOCAL ?
						       RT_SCOPE_HOST :
						       RT_SCOPE_LINK);
			अगर (fld.saddr == 0 && res.type != RTN_LOCAL)
				जाओ e_addr;
		पूर्ण
		fld.flowidn_oअगर = dev_out->अगरindex;
		जाओ make_route;
	पूर्ण
	मुक्त_res = 1;

	अगर (res.type == RTN_NAT)
		जाओ e_inval;

	अगर (res.type == RTN_LOCAL) अणु
		अगर (!fld.saddr)
			fld.saddr = fld.daddr;
		अगर (dev_out)
			dev_put(dev_out);
		dev_out = init_net.loopback_dev;
		dev_hold(dev_out);
		अगर (!dev_out->dn_ptr)
			जाओ e_inval;
		fld.flowidn_oअगर = dev_out->अगरindex;
		अगर (res.fi)
			dn_fib_info_put(res.fi);
		res.fi = शून्य;
		जाओ make_route;
	पूर्ण

	अगर (res.fi->fib_nhs > 1 && fld.flowidn_oअगर == 0)
		dn_fib_select_multipath(&fld, &res);

	/*
	 * We could add some logic to deal with शेष routes here and
	 * get rid of some of the special casing above.
	 */

	अगर (!fld.saddr)
		fld.saddr = DN_FIB_RES_PREFSRC(res);

	अगर (dev_out)
		dev_put(dev_out);
	dev_out = DN_FIB_RES_DEV(res);
	dev_hold(dev_out);
	fld.flowidn_oअगर = dev_out->अगरindex;
	gateway = DN_FIB_RES_GW(res);

make_route:
	अगर (dev_out->flags & IFF_LOOPBACK)
		flags |= RTCF_LOCAL;

	rt = dst_alloc(&dn_dst_ops, dev_out, 0, DST_OBSOLETE_NONE, 0);
	अगर (rt == शून्य)
		जाओ e_nobufs;

	rt->dn_next = शून्य;
	स_रखो(&rt->fld, 0, माप(rt->fld));
	rt->fld.saddr        = oldflp->saddr;
	rt->fld.daddr        = oldflp->daddr;
	rt->fld.flowidn_oअगर  = oldflp->flowidn_oअगर;
	rt->fld.flowidn_iअगर  = 0;
	rt->fld.flowidn_mark = oldflp->flowidn_mark;

	rt->rt_saddr      = fld.saddr;
	rt->rt_daddr      = fld.daddr;
	rt->rt_gateway    = gateway ? gateway : fld.daddr;
	rt->rt_local_src  = fld.saddr;

	rt->rt_dst_map    = fld.daddr;
	rt->rt_src_map    = fld.saddr;

	rt->n = neigh;
	neigh = शून्य;

	rt->dst.lastuse = jअगरfies;
	rt->dst.output  = dn_output;
	rt->dst.input   = dn_rt_bug;
	rt->rt_flags      = flags;
	अगर (flags & RTCF_LOCAL)
		rt->dst.input = dn_nsp_rx;

	err = dn_rt_set_next_hop(rt, &res);
	अगर (err)
		जाओ e_neighbour;

	hash = dn_hash(rt->fld.saddr, rt->fld.daddr);
	/* dn_insert_route() increments dst->__refcnt */
	dn_insert_route(rt, hash, (काष्ठा dn_route **)pprt);

करोne:
	अगर (neigh)
		neigh_release(neigh);
	अगर (मुक्त_res)
		dn_fib_res_put(&res);
	अगर (dev_out)
		dev_put(dev_out);
out:
	वापस err;

e_addr:
	err = -EADDRNOTAVAIL;
	जाओ करोne;
e_inval:
	err = -EINVAL;
	जाओ करोne;
e_nobufs:
	err = -ENOBUFS;
	जाओ करोne;
e_neighbour:
	dst_release_immediate(&rt->dst);
	जाओ e_nobufs;
पूर्ण


/*
 * N.B. The flags may be moved पूर्णांकo the flowi at some future stage.
 */
अटल पूर्णांक __dn_route_output_key(काष्ठा dst_entry **pprt, स्थिर काष्ठा flowidn *flp, पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक hash = dn_hash(flp->saddr, flp->daddr);
	काष्ठा dn_route *rt = शून्य;

	अगर (!(flags & MSG_TRYHARD)) अणु
		rcu_पढ़ो_lock_bh();
		क्रम (rt = rcu_dereference_bh(dn_rt_hash_table[hash].chain); rt;
			rt = rcu_dereference_bh(rt->dn_next)) अणु
			अगर ((flp->daddr == rt->fld.daddr) &&
			    (flp->saddr == rt->fld.saddr) &&
			    (flp->flowidn_mark == rt->fld.flowidn_mark) &&
			    dn_is_output_route(rt) &&
			    (rt->fld.flowidn_oअगर == flp->flowidn_oअगर)) अणु
				dst_hold_and_use(&rt->dst, jअगरfies);
				rcu_पढ़ो_unlock_bh();
				*pprt = &rt->dst;
				वापस 0;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock_bh();
	पूर्ण

	वापस dn_route_output_slow(pprt, flp, flags);
पूर्ण

अटल पूर्णांक dn_route_output_key(काष्ठा dst_entry **pprt, काष्ठा flowidn *flp, पूर्णांक flags)
अणु
	पूर्णांक err;

	err = __dn_route_output_key(pprt, flp, flags);
	अगर (err == 0 && flp->flowidn_proto) अणु
		*pprt = xfrm_lookup(&init_net, *pprt,
				    flowidn_to_flowi(flp), शून्य, 0);
		अगर (IS_ERR(*pprt)) अणु
			err = PTR_ERR(*pprt);
			*pprt = शून्य;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक dn_route_output_sock(काष्ठा dst_entry __rcu **pprt, काष्ठा flowidn *fl, काष्ठा sock *sk, पूर्णांक flags)
अणु
	पूर्णांक err;

	err = __dn_route_output_key(pprt, fl, flags & MSG_TRYHARD);
	अगर (err == 0 && fl->flowidn_proto) अणु
		*pprt = xfrm_lookup(&init_net, *pprt,
				    flowidn_to_flowi(fl), sk, 0);
		अगर (IS_ERR(*pprt)) अणु
			err = PTR_ERR(*pprt);
			*pprt = शून्य;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक dn_route_input_slow(काष्ठा sk_buff *skb)
अणु
	काष्ठा dn_route *rt = शून्य;
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);
	काष्ठा net_device *in_dev = skb->dev;
	काष्ठा net_device *out_dev = शून्य;
	काष्ठा dn_dev *dn_db;
	काष्ठा neighbour *neigh = शून्य;
	अचिन्हित पूर्णांक hash;
	पूर्णांक flags = 0;
	__le16 gateway = 0;
	__le16 local_src = 0;
	काष्ठा flowidn fld = अणु
		.daddr = cb->dst,
		.saddr = cb->src,
		.flowidn_scope = RT_SCOPE_UNIVERSE,
		.flowidn_mark = skb->mark,
		.flowidn_iअगर = skb->dev->अगरindex,
	पूर्ण;
	काष्ठा dn_fib_res res = अणु .fi = शून्य, .type = RTN_UNREACHABLE पूर्ण;
	पूर्णांक err = -EINVAL;
	पूर्णांक मुक्त_res = 0;

	dev_hold(in_dev);

	dn_db = rcu_dereference(in_dev->dn_ptr);
	अगर (!dn_db)
		जाओ out;

	/* Zero source addresses are not allowed */
	अगर (fld.saddr == 0)
		जाओ out;

	/*
	 * In this हाल we've just received a packet from a source
	 * outside ourselves pretending to come from us. We करोn't
	 * allow it any further to prevent routing loops, spoofing and
	 * other nasties. Loopback packets alपढ़ोy have the dst attached
	 * so this only affects packets which have originated अन्यथाwhere.
	 */
	err  = -ENOTUNIQ;
	अगर (dn_dev_islocal(in_dev, cb->src))
		जाओ out;

	err = dn_fib_lookup(&fld, &res);
	अगर (err) अणु
		अगर (err != -ESRCH)
			जाओ out;
		/*
		 * Is the destination us ?
		 */
		अगर (!dn_dev_islocal(in_dev, cb->dst))
			जाओ e_inval;

		res.type = RTN_LOCAL;
	पूर्ण अन्यथा अणु
		__le16 src_map = fld.saddr;
		मुक्त_res = 1;

		out_dev = DN_FIB_RES_DEV(res);
		अगर (out_dev == शून्य) अणु
			net_crit_ratelimited("Bug in dn_route_input_slow() No output device\n");
			जाओ e_inval;
		पूर्ण
		dev_hold(out_dev);

		अगर (res.r)
			src_map = fld.saddr; /* no NAT support क्रम now */

		gateway = DN_FIB_RES_GW(res);
		अगर (res.type == RTN_NAT) अणु
			fld.daddr = dn_fib_rules_map_destination(fld.daddr, &res);
			dn_fib_res_put(&res);
			मुक्त_res = 0;
			अगर (dn_fib_lookup(&fld, &res))
				जाओ e_inval;
			मुक्त_res = 1;
			अगर (res.type != RTN_UNICAST)
				जाओ e_inval;
			flags |= RTCF_DNAT;
			gateway = fld.daddr;
		पूर्ण
		fld.saddr = src_map;
	पूर्ण

	चयन (res.type) अणु
	हाल RTN_UNICAST:
		/*
		 * Forwarding check here, we only check क्रम क्रमwarding
		 * being turned off, अगर you want to only क्रमward पूर्णांकra
		 * area, its up to you to set the routing tables up
		 * correctly.
		 */
		अगर (dn_db->parms.क्रमwarding == 0)
			जाओ e_inval;

		अगर (res.fi->fib_nhs > 1 && fld.flowidn_oअगर == 0)
			dn_fib_select_multipath(&fld, &res);

		/*
		 * Check क्रम out_dev == in_dev. We use the RTCF_DOREसूचीECT
		 * flag as a hपूर्णांक to set the पूर्णांकra-ethernet bit when
		 * क्रमwarding. If we've got NAT in operation, we don't करो
		 * this optimisation.
		 */
		अगर (out_dev == in_dev && !(flags & RTCF_NAT))
			flags |= RTCF_DOREसूचीECT;

		local_src = DN_FIB_RES_PREFSRC(res);
		अवरोध;
	हाल RTN_BLACKHOLE:
	हाल RTN_UNREACHABLE:
		अवरोध;
	हाल RTN_LOCAL:
		flags |= RTCF_LOCAL;
		fld.saddr = cb->dst;
		fld.daddr = cb->src;

		/* Routing tables gave us a gateway */
		अगर (gateway)
			जाओ make_route;

		/* Packet was पूर्णांकra-ethernet, so we know its on-link */
		अगर (cb->rt_flags & DN_RT_F_IE) अणु
			gateway = cb->src;
			जाओ make_route;
		पूर्ण

		/* Use the शेष router अगर there is one */
		neigh = neigh_clone(dn_db->router);
		अगर (neigh) अणु
			gateway = ((काष्ठा dn_neigh *)neigh)->addr;
			जाओ make_route;
		पूर्ण

		/* Close eyes and pray */
		gateway = cb->src;
		जाओ make_route;
	शेष:
		जाओ e_inval;
	पूर्ण

make_route:
	rt = dst_alloc(&dn_dst_ops, out_dev, 1, DST_OBSOLETE_NONE, 0);
	अगर (rt == शून्य)
		जाओ e_nobufs;

	rt->dn_next = शून्य;
	स_रखो(&rt->fld, 0, माप(rt->fld));
	rt->rt_saddr      = fld.saddr;
	rt->rt_daddr      = fld.daddr;
	rt->rt_gateway    = fld.daddr;
	अगर (gateway)
		rt->rt_gateway = gateway;
	rt->rt_local_src  = local_src ? local_src : rt->rt_saddr;

	rt->rt_dst_map    = fld.daddr;
	rt->rt_src_map    = fld.saddr;

	rt->fld.saddr        = cb->src;
	rt->fld.daddr        = cb->dst;
	rt->fld.flowidn_oअगर  = 0;
	rt->fld.flowidn_iअगर  = in_dev->अगरindex;
	rt->fld.flowidn_mark = fld.flowidn_mark;

	rt->n = neigh;
	rt->dst.lastuse = jअगरfies;
	rt->dst.output = dn_rt_bug_out;
	चयन (res.type) अणु
	हाल RTN_UNICAST:
		rt->dst.input = dn_क्रमward;
		अवरोध;
	हाल RTN_LOCAL:
		rt->dst.output = dn_output;
		rt->dst.input = dn_nsp_rx;
		rt->dst.dev = in_dev;
		flags |= RTCF_LOCAL;
		अवरोध;
	शेष:
	हाल RTN_UNREACHABLE:
	हाल RTN_BLACKHOLE:
		rt->dst.input = dst_discard;
	पूर्ण
	rt->rt_flags = flags;

	err = dn_rt_set_next_hop(rt, &res);
	अगर (err)
		जाओ e_neighbour;

	hash = dn_hash(rt->fld.saddr, rt->fld.daddr);
	/* dn_insert_route() increments dst->__refcnt */
	dn_insert_route(rt, hash, &rt);
	skb_dst_set(skb, &rt->dst);

करोne:
	अगर (neigh)
		neigh_release(neigh);
	अगर (मुक्त_res)
		dn_fib_res_put(&res);
	dev_put(in_dev);
	अगर (out_dev)
		dev_put(out_dev);
out:
	वापस err;

e_inval:
	err = -EINVAL;
	जाओ करोne;

e_nobufs:
	err = -ENOBUFS;
	जाओ करोne;

e_neighbour:
	dst_release_immediate(&rt->dst);
	जाओ करोne;
पूर्ण

अटल पूर्णांक dn_route_input(काष्ठा sk_buff *skb)
अणु
	काष्ठा dn_route *rt;
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);
	अचिन्हित पूर्णांक hash = dn_hash(cb->src, cb->dst);

	अगर (skb_dst(skb))
		वापस 0;

	rcu_पढ़ो_lock();
	क्रम (rt = rcu_dereference(dn_rt_hash_table[hash].chain); rt != शून्य;
	    rt = rcu_dereference(rt->dn_next)) अणु
		अगर ((rt->fld.saddr == cb->src) &&
		    (rt->fld.daddr == cb->dst) &&
		    (rt->fld.flowidn_oअगर == 0) &&
		    (rt->fld.flowidn_mark == skb->mark) &&
		    (rt->fld.flowidn_iअगर == cb->iअगर)) अणु
			dst_hold_and_use(&rt->dst, jअगरfies);
			rcu_पढ़ो_unlock();
			skb_dst_set(skb, (काष्ठा dst_entry *)rt);
			वापस 0;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस dn_route_input_slow(skb);
पूर्ण

अटल पूर्णांक dn_rt_fill_info(काष्ठा sk_buff *skb, u32 portid, u32 seq,
			   पूर्णांक event, पूर्णांक noरुको, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा dn_route *rt = (काष्ठा dn_route *)skb_dst(skb);
	काष्ठा rपंचांगsg *r;
	काष्ठा nlmsghdr *nlh;
	दीर्घ expires;

	nlh = nlmsg_put(skb, portid, seq, event, माप(*r), flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	r = nlmsg_data(nlh);
	r->rपंचांग_family = AF_DECnet;
	r->rपंचांग_dst_len = 16;
	r->rपंचांग_src_len = 0;
	r->rपंचांग_tos = 0;
	r->rपंचांग_table = RT_TABLE_MAIN;
	r->rपंचांग_type = rt->rt_type;
	r->rपंचांग_flags = (rt->rt_flags & ~0xFFFF) | RTM_F_CLONED;
	r->rपंचांग_scope = RT_SCOPE_UNIVERSE;
	r->rपंचांग_protocol = RTPROT_UNSPEC;

	अगर (rt->rt_flags & RTCF_NOTIFY)
		r->rपंचांग_flags |= RTM_F_NOTIFY;

	अगर (nla_put_u32(skb, RTA_TABLE, RT_TABLE_MAIN) < 0 ||
	    nla_put_le16(skb, RTA_DST, rt->rt_daddr) < 0)
		जाओ errout;

	अगर (rt->fld.saddr) अणु
		r->rपंचांग_src_len = 16;
		अगर (nla_put_le16(skb, RTA_SRC, rt->fld.saddr) < 0)
			जाओ errout;
	पूर्ण
	अगर (rt->dst.dev &&
	    nla_put_u32(skb, RTA_OIF, rt->dst.dev->अगरindex) < 0)
		जाओ errout;

	/*
	 * Note to self - change this अगर input routes reverse direction when
	 * they deal only with inमाला_दो and not with replies like they करो
	 * currently.
	 */
	अगर (nla_put_le16(skb, RTA_PREFSRC, rt->rt_local_src) < 0)
		जाओ errout;

	अगर (rt->rt_daddr != rt->rt_gateway &&
	    nla_put_le16(skb, RTA_GATEWAY, rt->rt_gateway) < 0)
		जाओ errout;

	अगर (rtnetlink_put_metrics(skb, dst_metrics_ptr(&rt->dst)) < 0)
		जाओ errout;

	expires = rt->dst.expires ? rt->dst.expires - jअगरfies : 0;
	अगर (rtnl_put_cacheinfo(skb, &rt->dst, 0, expires,
			       rt->dst.error) < 0)
		जाओ errout;

	अगर (dn_is_input_route(rt) &&
	    nla_put_u32(skb, RTA_IIF, rt->fld.flowidn_iअगर) < 0)
		जाओ errout;

	nlmsg_end(skb, nlh);
	वापस 0;

errout:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

स्थिर काष्ठा nla_policy rपंचांग_dn_policy[RTA_MAX + 1] = अणु
	[RTA_DST]		= अणु .type = NLA_U16 पूर्ण,
	[RTA_SRC]		= अणु .type = NLA_U16 पूर्ण,
	[RTA_IIF]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_OIF]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_GATEWAY]		= अणु .type = NLA_U16 पूर्ण,
	[RTA_PRIORITY]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_PREFSRC]		= अणु .type = NLA_U16 पूर्ण,
	[RTA_METRICS]		= अणु .type = NLA_NESTED पूर्ण,
	[RTA_MULTIPATH]		= अणु .type = NLA_NESTED पूर्ण,
	[RTA_TABLE]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_MARK]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

/*
 * This is called by both endnodes and routers now.
 */
अटल पूर्णांक dn_cache_getroute(काष्ठा sk_buff *in_skb, काष्ठा nlmsghdr *nlh,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(in_skb->sk);
	काष्ठा rपंचांगsg *rपंचांग = nlmsg_data(nlh);
	काष्ठा dn_route *rt = शून्य;
	काष्ठा dn_skb_cb *cb;
	पूर्णांक err;
	काष्ठा sk_buff *skb;
	काष्ठा flowidn fld;
	काष्ठा nlattr *tb[RTA_MAX+1];

	अगर (!net_eq(net, &init_net))
		वापस -EINVAL;

	err = nlmsg_parse_deprecated(nlh, माप(*rपंचांग), tb, RTA_MAX,
				     rपंचांग_dn_policy, extack);
	अगर (err < 0)
		वापस err;

	स_रखो(&fld, 0, माप(fld));
	fld.flowidn_proto = DNPROTO_NSP;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (skb == शून्य)
		वापस -ENOBUFS;
	skb_reset_mac_header(skb);
	cb = DN_SKB_CB(skb);

	अगर (tb[RTA_SRC])
		fld.saddr = nla_get_le16(tb[RTA_SRC]);

	अगर (tb[RTA_DST])
		fld.daddr = nla_get_le16(tb[RTA_DST]);

	अगर (tb[RTA_IIF])
		fld.flowidn_iअगर = nla_get_u32(tb[RTA_IIF]);

	अगर (fld.flowidn_iअगर) अणु
		काष्ठा net_device *dev;
		dev = __dev_get_by_index(&init_net, fld.flowidn_iअगर);
		अगर (!dev || !dev->dn_ptr) अणु
			kमुक्त_skb(skb);
			वापस -ENODEV;
		पूर्ण
		skb->protocol = htons(ETH_P_DNA_RT);
		skb->dev = dev;
		cb->src = fld.saddr;
		cb->dst = fld.daddr;
		local_bh_disable();
		err = dn_route_input(skb);
		local_bh_enable();
		स_रखो(cb, 0, माप(काष्ठा dn_skb_cb));
		rt = (काष्ठा dn_route *)skb_dst(skb);
		अगर (!err && -rt->dst.error)
			err = rt->dst.error;
	पूर्ण अन्यथा अणु
		अगर (tb[RTA_OIF])
			fld.flowidn_oअगर = nla_get_u32(tb[RTA_OIF]);

		err = dn_route_output_key((काष्ठा dst_entry **)&rt, &fld, 0);
	पूर्ण

	skb->dev = शून्य;
	अगर (err)
		जाओ out_मुक्त;
	skb_dst_set(skb, &rt->dst);
	अगर (rपंचांग->rपंचांग_flags & RTM_F_NOTIFY)
		rt->rt_flags |= RTCF_NOTIFY;

	err = dn_rt_fill_info(skb, NETLINK_CB(in_skb).portid, nlh->nlmsg_seq, RTM_NEWROUTE, 0, 0);
	अगर (err < 0) अणु
		err = -EMSGSIZE;
		जाओ out_मुक्त;
	पूर्ण

	वापस rtnl_unicast(skb, &init_net, NETLINK_CB(in_skb).portid);

out_मुक्त:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

/*
 * For routers, this is called from dn_fib_dump, but क्रम endnodes its
 * called directly from the rtnetlink dispatch table.
 */
पूर्णांक dn_cache_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा dn_route *rt;
	पूर्णांक h, s_h;
	पूर्णांक idx, s_idx;
	काष्ठा rपंचांगsg *rपंचांग;

	अगर (!net_eq(net, &init_net))
		वापस 0;

	अगर (nlmsg_len(cb->nlh) < माप(काष्ठा rपंचांगsg))
		वापस -EINVAL;

	rपंचांग = nlmsg_data(cb->nlh);
	अगर (!(rपंचांग->rपंचांग_flags & RTM_F_CLONED))
		वापस 0;

	s_h = cb->args[0];
	s_idx = idx = cb->args[1];
	क्रम (h = 0; h <= dn_rt_hash_mask; h++) अणु
		अगर (h < s_h)
			जारी;
		अगर (h > s_h)
			s_idx = 0;
		rcu_पढ़ो_lock_bh();
		क्रम (rt = rcu_dereference_bh(dn_rt_hash_table[h].chain), idx = 0;
			rt;
			rt = rcu_dereference_bh(rt->dn_next), idx++) अणु
			अगर (idx < s_idx)
				जारी;
			skb_dst_set(skb, dst_clone(&rt->dst));
			अगर (dn_rt_fill_info(skb, NETLINK_CB(cb->skb).portid,
					cb->nlh->nlmsg_seq, RTM_NEWROUTE,
					1, NLM_F_MULTI) < 0) अणु
				skb_dst_drop(skb);
				rcu_पढ़ो_unlock_bh();
				जाओ करोne;
			पूर्ण
			skb_dst_drop(skb);
		पूर्ण
		rcu_पढ़ो_unlock_bh();
	पूर्ण

करोne:
	cb->args[0] = h;
	cb->args[1] = idx;
	वापस skb->len;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
काष्ठा dn_rt_cache_iter_state अणु
	पूर्णांक bucket;
पूर्ण;

अटल काष्ठा dn_route *dn_rt_cache_get_first(काष्ठा seq_file *seq)
अणु
	काष्ठा dn_route *rt = शून्य;
	काष्ठा dn_rt_cache_iter_state *s = seq->निजी;

	क्रम (s->bucket = dn_rt_hash_mask; s->bucket >= 0; --s->bucket) अणु
		rcu_पढ़ो_lock_bh();
		rt = rcu_dereference_bh(dn_rt_hash_table[s->bucket].chain);
		अगर (rt)
			अवरोध;
		rcu_पढ़ो_unlock_bh();
	पूर्ण
	वापस rt;
पूर्ण

अटल काष्ठा dn_route *dn_rt_cache_get_next(काष्ठा seq_file *seq, काष्ठा dn_route *rt)
अणु
	काष्ठा dn_rt_cache_iter_state *s = seq->निजी;

	rt = rcu_dereference_bh(rt->dn_next);
	जबतक (!rt) अणु
		rcu_पढ़ो_unlock_bh();
		अगर (--s->bucket < 0)
			अवरोध;
		rcu_पढ़ो_lock_bh();
		rt = rcu_dereference_bh(dn_rt_hash_table[s->bucket].chain);
	पूर्ण
	वापस rt;
पूर्ण

अटल व्योम *dn_rt_cache_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा dn_route *rt = dn_rt_cache_get_first(seq);

	अगर (rt) अणु
		जबतक (*pos && (rt = dn_rt_cache_get_next(seq, rt)))
			--*pos;
	पूर्ण
	वापस *pos ? शून्य : rt;
पूर्ण

अटल व्योम *dn_rt_cache_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा dn_route *rt = dn_rt_cache_get_next(seq, v);
	++*pos;
	वापस rt;
पूर्ण

अटल व्योम dn_rt_cache_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v)
		rcu_पढ़ो_unlock_bh();
पूर्ण

अटल पूर्णांक dn_rt_cache_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा dn_route *rt = v;
	अक्षर buf1[DN_ASCBUF_LEN], buf2[DN_ASCBUF_LEN];

	seq_म_लिखो(seq, "%-8s %-7s %-7s %04d %04d %04d\n",
		   rt->dst.dev ? rt->dst.dev->name : "*",
		   dn_addr2asc(le16_to_cpu(rt->rt_daddr), buf1),
		   dn_addr2asc(le16_to_cpu(rt->rt_saddr), buf2),
		   atomic_पढ़ो(&rt->dst.__refcnt),
		   rt->dst.__use, 0);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations dn_rt_cache_seq_ops = अणु
	.start	= dn_rt_cache_seq_start,
	.next	= dn_rt_cache_seq_next,
	.stop	= dn_rt_cache_seq_stop,
	.show	= dn_rt_cache_seq_show,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PROC_FS */

व्योम __init dn_route_init(व्योम)
अणु
	पूर्णांक i, goal, order;

	dn_dst_ops.kmem_cachep =
		kmem_cache_create("dn_dst_cache", माप(काष्ठा dn_route), 0,
				  SLAB_HWCACHE_ALIGN|SLAB_PANIC, शून्य);
	dst_entries_init(&dn_dst_ops);
	समयr_setup(&dn_route_समयr, dn_dst_check_expire, 0);
	dn_route_समयr.expires = jअगरfies + decnet_dst_gc_पूर्णांकerval * HZ;
	add_समयr(&dn_route_समयr);

	goal = totalram_pages() >> (26 - PAGE_SHIFT);

	क्रम (order = 0; (1UL << order) < goal; order++)
		/* NOTHING */;

	/*
	 * Only want 1024 entries max, since the table is very, very unlikely
	 * to be larger than that.
	 */
	जबतक (order && ((((1UL << order) * PAGE_SIZE) /
				माप(काष्ठा dn_rt_hash_bucket)) >= 2048))
		order--;

	करो अणु
		dn_rt_hash_mask = (1UL << order) * PAGE_SIZE /
			माप(काष्ठा dn_rt_hash_bucket);
		जबतक (dn_rt_hash_mask & (dn_rt_hash_mask - 1))
			dn_rt_hash_mask--;
		dn_rt_hash_table = (काष्ठा dn_rt_hash_bucket *)
			__get_मुक्त_pages(GFP_ATOMIC, order);
	पूर्ण जबतक (dn_rt_hash_table == शून्य && --order > 0);

	अगर (!dn_rt_hash_table)
		panic("Failed to allocate DECnet route cache hash table\n");

	prपूर्णांकk(KERN_INFO
		"DECnet: Routing cache hash table of %u buckets, %ldKbytes\n",
		dn_rt_hash_mask,
		(दीर्घ)(dn_rt_hash_mask*माप(काष्ठा dn_rt_hash_bucket))/1024);

	dn_rt_hash_mask--;
	क्रम (i = 0; i <= dn_rt_hash_mask; i++) अणु
		spin_lock_init(&dn_rt_hash_table[i].lock);
		dn_rt_hash_table[i].chain = शून्य;
	पूर्ण

	dn_dst_ops.gc_thresh = (dn_rt_hash_mask + 1);

	proc_create_seq_निजी("decnet_cache", 0444, init_net.proc_net,
			&dn_rt_cache_seq_ops,
			माप(काष्ठा dn_rt_cache_iter_state), शून्य);

#अगर_घोषित CONFIG_DECNET_ROUTER
	rtnl_रेजिस्टर_module(THIS_MODULE, PF_DECnet, RTM_GETROUTE,
			     dn_cache_getroute, dn_fib_dump, 0);
#अन्यथा
	rtnl_रेजिस्टर_module(THIS_MODULE, PF_DECnet, RTM_GETROUTE,
			     dn_cache_getroute, dn_cache_dump, 0);
#पूर्ण_अगर
पूर्ण

व्योम __निकास dn_route_cleanup(व्योम)
अणु
	del_समयr(&dn_route_समयr);
	dn_run_flush(शून्य);

	हटाओ_proc_entry("decnet_cache", init_net.proc_net);
	dst_entries_destroy(&dn_dst_ops);
पूर्ण
