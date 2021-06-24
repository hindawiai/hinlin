<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		The IP fragmentation functionality.
 *
 * Authors:	Fred N. van Kempen <waltje@uWalt.NL.Mugnet.ORG>
 *		Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 * Fixes:
 *		Alan Cox	:	Split from ip.c , see ip_input.c क्रम history.
 *		David S. Miller :	Begin massive cleanup...
 *		Andi Kleen	:	Add sysctls.
 *		xxxx		:	Overlapfrag bug.
 *		Ultima          :       ip_expire() kernel panic.
 *		Bill Hawes	:	Frag accounting and evictor fixes.
 *		John McDonald	:	0 length frag bug.
 *		Alexey Kuznetsov:	SMP races, thपढ़ोing, cleanup.
 *		Patrick McHardy :	LRU queue of frag heads क्रम evictor.
 */

#घोषणा pr_fmt(fmt) "IPv4: " fmt

#समावेश <linux/compiler.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/list.h>
#समावेश <linux/ip.h>
#समावेश <linux/icmp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/jhash.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <net/route.h>
#समावेश <net/dst.h>
#समावेश <net/sock.h>
#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/checksum.h>
#समावेश <net/inetpeer.h>
#समावेश <net/inet_frag.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/inet.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/l3mdev.h>

/* NOTE. Logic of IP defragmentation is parallel to corresponding IPv6
 * code now. If you change something here, _PLEASE_ update ipv6/reassembly.c
 * as well. Or notअगरy me, at least. --ANK
 */
अटल स्थिर अक्षर ip_frag_cache_name[] = "ip4-frags";

/* Describe an entry in the "incomplete datagrams" queue. */
काष्ठा ipq अणु
	काष्ठा inet_frag_queue q;

	u8		ecn; /* RFC3168 support */
	u16		max_df_size; /* largest frag with DF set seen */
	पूर्णांक             iअगर;
	अचिन्हित पूर्णांक    rid;
	काष्ठा inet_peer *peer;
पूर्ण;

अटल u8 ip4_frag_ecn(u8 tos)
अणु
	वापस 1 << (tos & INET_ECN_MASK);
पूर्ण

अटल काष्ठा inet_frags ip4_frags;

अटल पूर्णांक ip_frag_reयंत्र(काष्ठा ipq *qp, काष्ठा sk_buff *skb,
			 काष्ठा sk_buff *prev_tail, काष्ठा net_device *dev);


अटल व्योम ip4_frag_init(काष्ठा inet_frag_queue *q, स्थिर व्योम *a)
अणु
	काष्ठा ipq *qp = container_of(q, काष्ठा ipq, q);
	काष्ठा net *net = q->fqdir->net;

	स्थिर काष्ठा frag_v4_compare_key *key = a;

	q->key.v4 = *key;
	qp->ecn = 0;
	qp->peer = q->fqdir->max_dist ?
		inet_getpeer_v4(net->ipv4.peers, key->saddr, key->vअगर, 1) :
		शून्य;
पूर्ण

अटल व्योम ip4_frag_मुक्त(काष्ठा inet_frag_queue *q)
अणु
	काष्ठा ipq *qp;

	qp = container_of(q, काष्ठा ipq, q);
	अगर (qp->peer)
		inet_putpeer(qp->peer);
पूर्ण


/* Deकाष्ठाion primitives. */

अटल व्योम ipq_put(काष्ठा ipq *ipq)
अणु
	inet_frag_put(&ipq->q);
पूर्ण

/* Kill ipq entry. It is not destroyed immediately,
 * because caller (and someone more) holds reference count.
 */
अटल व्योम ipq_समाप्त(काष्ठा ipq *ipq)
अणु
	inet_frag_समाप्त(&ipq->q);
पूर्ण

अटल bool frag_expire_skip_icmp(u32 user)
अणु
	वापस user == IP_DEFRAG_AF_PACKET ||
	       ip_defrag_user_in_between(user, IP_DEFRAG_CONNTRACK_IN,
					 __IP_DEFRAG_CONNTRACK_IN_END) ||
	       ip_defrag_user_in_between(user, IP_DEFRAG_CONNTRACK_BRIDGE_IN,
					 __IP_DEFRAG_CONNTRACK_BRIDGE_IN);
पूर्ण

/*
 * Oops, a fragment queue समयd out.  Kill it and send an ICMP reply.
 */
अटल व्योम ip_expire(काष्ठा समयr_list *t)
अणु
	काष्ठा inet_frag_queue *frag = from_समयr(frag, t, समयr);
	स्थिर काष्ठा iphdr *iph;
	काष्ठा sk_buff *head = शून्य;
	काष्ठा net *net;
	काष्ठा ipq *qp;
	पूर्णांक err;

	qp = container_of(frag, काष्ठा ipq, q);
	net = qp->q.fqdir->net;

	rcu_पढ़ो_lock();

	अगर (qp->q.fqdir->dead)
		जाओ out_rcu_unlock;

	spin_lock(&qp->q.lock);

	अगर (qp->q.flags & INET_FRAG_COMPLETE)
		जाओ out;

	ipq_समाप्त(qp);
	__IP_INC_STATS(net, IPSTATS_MIB_REASMFAILS);
	__IP_INC_STATS(net, IPSTATS_MIB_REASMTIMEOUT);

	अगर (!(qp->q.flags & INET_FRAG_FIRST_IN))
		जाओ out;

	/* sk_buff::dev and sk_buff::rbnode are जोड़ized. So we
	 * pull the head out of the tree in order to be able to
	 * deal with head->dev.
	 */
	head = inet_frag_pull_head(&qp->q);
	अगर (!head)
		जाओ out;
	head->dev = dev_get_by_index_rcu(net, qp->iअगर);
	अगर (!head->dev)
		जाओ out;


	/* skb has no dst, perक्रमm route lookup again */
	iph = ip_hdr(head);
	err = ip_route_input_noref(head, iph->daddr, iph->saddr,
					   iph->tos, head->dev);
	अगर (err)
		जाओ out;

	/* Only an end host needs to send an ICMP
	 * "Fragment Reassembly Timeout" message, per RFC792.
	 */
	अगर (frag_expire_skip_icmp(qp->q.key.v4.user) &&
	    (skb_rtable(head)->rt_type != RTN_LOCAL))
		जाओ out;

	spin_unlock(&qp->q.lock);
	icmp_send(head, ICMP_TIME_EXCEEDED, ICMP_EXC_FRAGTIME, 0);
	जाओ out_rcu_unlock;

out:
	spin_unlock(&qp->q.lock);
out_rcu_unlock:
	rcu_पढ़ो_unlock();
	kमुक्त_skb(head);
	ipq_put(qp);
पूर्ण

/* Find the correct entry in the "incomplete datagrams" queue क्रम
 * this IP datagram, and create new one, अगर nothing is found.
 */
अटल काष्ठा ipq *ip_find(काष्ठा net *net, काष्ठा iphdr *iph,
			   u32 user, पूर्णांक vअगर)
अणु
	काष्ठा frag_v4_compare_key key = अणु
		.saddr = iph->saddr,
		.daddr = iph->daddr,
		.user = user,
		.vअगर = vअगर,
		.id = iph->id,
		.protocol = iph->protocol,
	पूर्ण;
	काष्ठा inet_frag_queue *q;

	q = inet_frag_find(net->ipv4.fqdir, &key);
	अगर (!q)
		वापस शून्य;

	वापस container_of(q, काष्ठा ipq, q);
पूर्ण

/* Is the fragment too far ahead to be part of ipq? */
अटल पूर्णांक ip_frag_too_far(काष्ठा ipq *qp)
अणु
	काष्ठा inet_peer *peer = qp->peer;
	अचिन्हित पूर्णांक max = qp->q.fqdir->max_dist;
	अचिन्हित पूर्णांक start, end;

	पूर्णांक rc;

	अगर (!peer || !max)
		वापस 0;

	start = qp->rid;
	end = atomic_inc_वापस(&peer->rid);
	qp->rid = end;

	rc = qp->q.fragments_tail && (end - start) > max;

	अगर (rc)
		__IP_INC_STATS(qp->q.fqdir->net, IPSTATS_MIB_REASMFAILS);

	वापस rc;
पूर्ण

अटल पूर्णांक ip_frag_reinit(काष्ठा ipq *qp)
अणु
	अचिन्हित पूर्णांक sum_truesize = 0;

	अगर (!mod_समयr(&qp->q.समयr, jअगरfies + qp->q.fqdir->समयout)) अणु
		refcount_inc(&qp->q.refcnt);
		वापस -ETIMEDOUT;
	पूर्ण

	sum_truesize = inet_frag_rbtree_purge(&qp->q.rb_fragments);
	sub_frag_mem_limit(qp->q.fqdir, sum_truesize);

	qp->q.flags = 0;
	qp->q.len = 0;
	qp->q.meat = 0;
	qp->q.rb_fragments = RB_ROOT;
	qp->q.fragments_tail = शून्य;
	qp->q.last_run_head = शून्य;
	qp->iअगर = 0;
	qp->ecn = 0;

	वापस 0;
पूर्ण

/* Add new segment to existing queue. */
अटल पूर्णांक ip_frag_queue(काष्ठा ipq *qp, काष्ठा sk_buff *skb)
अणु
	काष्ठा net *net = qp->q.fqdir->net;
	पूर्णांक ihl, end, flags, offset;
	काष्ठा sk_buff *prev_tail;
	काष्ठा net_device *dev;
	अचिन्हित पूर्णांक fragsize;
	पूर्णांक err = -ENOENT;
	u8 ecn;

	अगर (qp->q.flags & INET_FRAG_COMPLETE)
		जाओ err;

	अगर (!(IPCB(skb)->flags & IPSKB_FRAG_COMPLETE) &&
	    unlikely(ip_frag_too_far(qp)) &&
	    unlikely(err = ip_frag_reinit(qp))) अणु
		ipq_समाप्त(qp);
		जाओ err;
	पूर्ण

	ecn = ip4_frag_ecn(ip_hdr(skb)->tos);
	offset = ntohs(ip_hdr(skb)->frag_off);
	flags = offset & ~IP_OFFSET;
	offset &= IP_OFFSET;
	offset <<= 3;		/* offset is in 8-byte chunks */
	ihl = ip_hdrlen(skb);

	/* Determine the position of this fragment. */
	end = offset + skb->len - skb_network_offset(skb) - ihl;
	err = -EINVAL;

	/* Is this the final fragment? */
	अगर ((flags & IP_MF) == 0) अणु
		/* If we alपढ़ोy have some bits beyond end
		 * or have dअगरferent end, the segment is corrupted.
		 */
		अगर (end < qp->q.len ||
		    ((qp->q.flags & INET_FRAG_LAST_IN) && end != qp->q.len))
			जाओ discard_qp;
		qp->q.flags |= INET_FRAG_LAST_IN;
		qp->q.len = end;
	पूर्ण अन्यथा अणु
		अगर (end&7) अणु
			end &= ~7;
			अगर (skb->ip_summed != CHECKSUM_UNNECESSARY)
				skb->ip_summed = CHECKSUM_NONE;
		पूर्ण
		अगर (end > qp->q.len) अणु
			/* Some bits beyond end -> corruption. */
			अगर (qp->q.flags & INET_FRAG_LAST_IN)
				जाओ discard_qp;
			qp->q.len = end;
		पूर्ण
	पूर्ण
	अगर (end == offset)
		जाओ discard_qp;

	err = -ENOMEM;
	अगर (!pskb_pull(skb, skb_network_offset(skb) + ihl))
		जाओ discard_qp;

	err = pskb_trim_rcsum(skb, end - offset);
	अगर (err)
		जाओ discard_qp;

	/* Note : skb->rbnode and skb->dev share the same location. */
	dev = skb->dev;
	/* Makes sure compiler wont करो silly aliasing games */
	barrier();

	prev_tail = qp->q.fragments_tail;
	err = inet_frag_queue_insert(&qp->q, skb, offset, end);
	अगर (err)
		जाओ insert_error;

	अगर (dev)
		qp->iअगर = dev->अगरindex;

	qp->q.stamp = skb->tstamp;
	qp->q.meat += skb->len;
	qp->ecn |= ecn;
	add_frag_mem_limit(qp->q.fqdir, skb->truesize);
	अगर (offset == 0)
		qp->q.flags |= INET_FRAG_FIRST_IN;

	fragsize = skb->len + ihl;

	अगर (fragsize > qp->q.max_size)
		qp->q.max_size = fragsize;

	अगर (ip_hdr(skb)->frag_off & htons(IP_DF) &&
	    fragsize > qp->max_df_size)
		qp->max_df_size = fragsize;

	अगर (qp->q.flags == (INET_FRAG_FIRST_IN | INET_FRAG_LAST_IN) &&
	    qp->q.meat == qp->q.len) अणु
		अचिन्हित दीर्घ orefdst = skb->_skb_refdst;

		skb->_skb_refdst = 0UL;
		err = ip_frag_reयंत्र(qp, skb, prev_tail, dev);
		skb->_skb_refdst = orefdst;
		अगर (err)
			inet_frag_समाप्त(&qp->q);
		वापस err;
	पूर्ण

	skb_dst_drop(skb);
	वापस -EINPROGRESS;

insert_error:
	अगर (err == IPFRAG_DUP) अणु
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण
	err = -EINVAL;
	__IP_INC_STATS(net, IPSTATS_MIB_REASM_OVERLAPS);
discard_qp:
	inet_frag_समाप्त(&qp->q);
	__IP_INC_STATS(net, IPSTATS_MIB_REASMFAILS);
err:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल bool ip_frag_coalesce_ok(स्थिर काष्ठा ipq *qp)
अणु
	वापस qp->q.key.v4.user == IP_DEFRAG_LOCAL_DELIVER;
पूर्ण

/* Build a new IP datagram from all its fragments. */
अटल पूर्णांक ip_frag_reयंत्र(काष्ठा ipq *qp, काष्ठा sk_buff *skb,
			 काष्ठा sk_buff *prev_tail, काष्ठा net_device *dev)
अणु
	काष्ठा net *net = qp->q.fqdir->net;
	काष्ठा iphdr *iph;
	व्योम *reयंत्र_data;
	पूर्णांक len, err;
	u8 ecn;

	ipq_समाप्त(qp);

	ecn = ip_frag_ecn_table[qp->ecn];
	अगर (unlikely(ecn == 0xff)) अणु
		err = -EINVAL;
		जाओ out_fail;
	पूर्ण

	/* Make the one we just received the head. */
	reयंत्र_data = inet_frag_reयंत्र_prepare(&qp->q, skb, prev_tail);
	अगर (!reयंत्र_data)
		जाओ out_nomem;

	len = ip_hdrlen(skb) + qp->q.len;
	err = -E2BIG;
	अगर (len > 65535)
		जाओ out_oversize;

	inet_frag_reयंत्र_finish(&qp->q, skb, reयंत्र_data,
			       ip_frag_coalesce_ok(qp));

	skb->dev = dev;
	IPCB(skb)->frag_max_size = max(qp->max_df_size, qp->q.max_size);

	iph = ip_hdr(skb);
	iph->tot_len = htons(len);
	iph->tos |= ecn;

	/* When we set IP_DF on a refragmented skb we must also क्रमce a
	 * call to ip_fragment to aव्योम क्रमwarding a DF-skb of size s जबतक
	 * original sender only sent fragments of size f (where f < s).
	 *
	 * We only set DF/IPSKB_FRAG_PMTU अगर such DF fragment was the largest
	 * frag seen to aव्योम sending tiny DF-fragments in हाल skb was built
	 * from one very small df-fragment and one large non-df frag.
	 */
	अगर (qp->max_df_size == qp->q.max_size) अणु
		IPCB(skb)->flags |= IPSKB_FRAG_PMTU;
		iph->frag_off = htons(IP_DF);
	पूर्ण अन्यथा अणु
		iph->frag_off = 0;
	पूर्ण

	ip_send_check(iph);

	__IP_INC_STATS(net, IPSTATS_MIB_REASMOKS);
	qp->q.rb_fragments = RB_ROOT;
	qp->q.fragments_tail = शून्य;
	qp->q.last_run_head = शून्य;
	वापस 0;

out_nomem:
	net_dbg_ratelimited("queue_glue: no memory for gluing queue %p\n", qp);
	err = -ENOMEM;
	जाओ out_fail;
out_oversize:
	net_info_ratelimited("Oversized IP packet from %pI4\n", &qp->q.key.v4.saddr);
out_fail:
	__IP_INC_STATS(net, IPSTATS_MIB_REASMFAILS);
	वापस err;
पूर्ण

/* Process an incoming IP datagram fragment. */
पूर्णांक ip_defrag(काष्ठा net *net, काष्ठा sk_buff *skb, u32 user)
अणु
	काष्ठा net_device *dev = skb->dev ? : skb_dst(skb)->dev;
	पूर्णांक vअगर = l3mdev_master_अगरindex_rcu(dev);
	काष्ठा ipq *qp;

	__IP_INC_STATS(net, IPSTATS_MIB_REASMREQDS);
	skb_orphan(skb);

	/* Lookup (or create) queue header */
	qp = ip_find(net, ip_hdr(skb), user, vअगर);
	अगर (qp) अणु
		पूर्णांक ret;

		spin_lock(&qp->q.lock);

		ret = ip_frag_queue(qp, skb);

		spin_unlock(&qp->q.lock);
		ipq_put(qp);
		वापस ret;
	पूर्ण

	__IP_INC_STATS(net, IPSTATS_MIB_REASMFAILS);
	kमुक्त_skb(skb);
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL(ip_defrag);

काष्ठा sk_buff *ip_check_defrag(काष्ठा net *net, काष्ठा sk_buff *skb, u32 user)
अणु
	काष्ठा iphdr iph;
	पूर्णांक netoff;
	u32 len;

	अगर (skb->protocol != htons(ETH_P_IP))
		वापस skb;

	netoff = skb_network_offset(skb);

	अगर (skb_copy_bits(skb, netoff, &iph, माप(iph)) < 0)
		वापस skb;

	अगर (iph.ihl < 5 || iph.version != 4)
		वापस skb;

	len = ntohs(iph.tot_len);
	अगर (skb->len < netoff + len || len < (iph.ihl * 4))
		वापस skb;

	अगर (ip_is_fragment(&iph)) अणु
		skb = skb_share_check(skb, GFP_ATOMIC);
		अगर (skb) अणु
			अगर (!pskb_may_pull(skb, netoff + iph.ihl * 4)) अणु
				kमुक्त_skb(skb);
				वापस शून्य;
			पूर्ण
			अगर (pskb_trim_rcsum(skb, netoff + len)) अणु
				kमुक्त_skb(skb);
				वापस शून्य;
			पूर्ण
			स_रखो(IPCB(skb), 0, माप(काष्ठा inet_skb_parm));
			अगर (ip_defrag(net, skb, user))
				वापस शून्य;
			skb_clear_hash(skb);
		पूर्ण
	पूर्ण
	वापस skb;
पूर्ण
EXPORT_SYMBOL(ip_check_defrag);

#अगर_घोषित CONFIG_SYSCTL
अटल पूर्णांक dist_min;

अटल काष्ठा ctl_table ip4_frags_ns_ctl_table[] = अणु
	अणु
		.procname	= "ipfrag_high_thresh",
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
	अणु
		.procname	= "ipfrag_low_thresh",
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
	अणु
		.procname	= "ipfrag_time",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "ipfrag_max_dist",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &dist_min,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/* secret पूर्णांकerval has been deprecated */
अटल पूर्णांक ip4_frags_secret_पूर्णांकerval_unused;
अटल काष्ठा ctl_table ip4_frags_ctl_table[] = अणु
	अणु
		.procname	= "ipfrag_secret_interval",
		.data		= &ip4_frags_secret_पूर्णांकerval_unused,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक __net_init ip4_frags_ns_ctl_रेजिस्टर(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;
	काष्ठा ctl_table_header *hdr;

	table = ip4_frags_ns_ctl_table;
	अगर (!net_eq(net, &init_net)) अणु
		table = kmemdup(table, माप(ip4_frags_ns_ctl_table), GFP_KERNEL);
		अगर (!table)
			जाओ err_alloc;

	पूर्ण
	table[0].data	= &net->ipv4.fqdir->high_thresh;
	table[0].extra1	= &net->ipv4.fqdir->low_thresh;
	table[1].data	= &net->ipv4.fqdir->low_thresh;
	table[1].extra2	= &net->ipv4.fqdir->high_thresh;
	table[2].data	= &net->ipv4.fqdir->समयout;
	table[3].data	= &net->ipv4.fqdir->max_dist;

	hdr = रेजिस्टर_net_sysctl(net, "net/ipv4", table);
	अगर (!hdr)
		जाओ err_reg;

	net->ipv4.frags_hdr = hdr;
	वापस 0;

err_reg:
	अगर (!net_eq(net, &init_net))
		kमुक्त(table);
err_alloc:
	वापस -ENOMEM;
पूर्ण

अटल व्योम __net_निकास ip4_frags_ns_ctl_unरेजिस्टर(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;

	table = net->ipv4.frags_hdr->ctl_table_arg;
	unरेजिस्टर_net_sysctl_table(net->ipv4.frags_hdr);
	kमुक्त(table);
पूर्ण

अटल व्योम __init ip4_frags_ctl_रेजिस्टर(व्योम)
अणु
	रेजिस्टर_net_sysctl(&init_net, "net/ipv4", ip4_frags_ctl_table);
पूर्ण
#अन्यथा
अटल पूर्णांक ip4_frags_ns_ctl_रेजिस्टर(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण

अटल व्योम ip4_frags_ns_ctl_unरेजिस्टर(काष्ठा net *net)
अणु
पूर्ण

अटल व्योम __init ip4_frags_ctl_रेजिस्टर(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __net_init ipv4_frags_init_net(काष्ठा net *net)
अणु
	पूर्णांक res;

	res = fqdir_init(&net->ipv4.fqdir, &ip4_frags, net);
	अगर (res < 0)
		वापस res;
	/* Fragment cache limits.
	 *
	 * The fragment memory accounting code, (tries to) account क्रम
	 * the real memory usage, by measuring both the size of frag
	 * queue काष्ठा (inet_frag_queue (ipv4:ipq/ipv6:frag_queue))
	 * and the SKB's truesize.
	 *
	 * A 64K fragment consumes 129736 bytes (44*2944)+200
	 * (1500 truesize == 2944, माप(काष्ठा ipq) == 200)
	 *
	 * We will commit 4MB at one समय. Should we cross that limit
	 * we will prune करोwn to 3MB, making room क्रम approx 8 big 64K
	 * fragments 8x128k.
	 */
	net->ipv4.fqdir->high_thresh = 4 * 1024 * 1024;
	net->ipv4.fqdir->low_thresh  = 3 * 1024 * 1024;
	/*
	 * Important NOTE! Fragment queue must be destroyed beक्रमe MSL expires.
	 * RFC791 is wrong proposing to proदीर्घate समयr each fragment arrival
	 * by TTL.
	 */
	net->ipv4.fqdir->समयout = IP_FRAG_TIME;

	net->ipv4.fqdir->max_dist = 64;

	res = ip4_frags_ns_ctl_रेजिस्टर(net);
	अगर (res < 0)
		fqdir_निकास(net->ipv4.fqdir);
	वापस res;
पूर्ण

अटल व्योम __net_निकास ipv4_frags_pre_निकास_net(काष्ठा net *net)
अणु
	fqdir_pre_निकास(net->ipv4.fqdir);
पूर्ण

अटल व्योम __net_निकास ipv4_frags_निकास_net(काष्ठा net *net)
अणु
	ip4_frags_ns_ctl_unरेजिस्टर(net);
	fqdir_निकास(net->ipv4.fqdir);
पूर्ण

अटल काष्ठा pernet_operations ip4_frags_ops = अणु
	.init		= ipv4_frags_init_net,
	.pre_निकास	= ipv4_frags_pre_निकास_net,
	.निकास		= ipv4_frags_निकास_net,
पूर्ण;


अटल u32 ip4_key_hashfn(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	वापस jhash2(data,
		      माप(काष्ठा frag_v4_compare_key) / माप(u32), seed);
पूर्ण

अटल u32 ip4_obj_hashfn(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा inet_frag_queue *fq = data;

	वापस jhash2((स्थिर u32 *)&fq->key.v4,
		      माप(काष्ठा frag_v4_compare_key) / माप(u32), seed);
पूर्ण

अटल पूर्णांक ip4_obj_cmpfn(काष्ठा rhashtable_compare_arg *arg, स्थिर व्योम *ptr)
अणु
	स्थिर काष्ठा frag_v4_compare_key *key = arg->key;
	स्थिर काष्ठा inet_frag_queue *fq = ptr;

	वापस !!स_भेद(&fq->key, key, माप(*key));
पूर्ण

अटल स्थिर काष्ठा rhashtable_params ip4_rhash_params = अणु
	.head_offset		= दुरत्व(काष्ठा inet_frag_queue, node),
	.key_offset		= दुरत्व(काष्ठा inet_frag_queue, key),
	.key_len		= माप(काष्ठा frag_v4_compare_key),
	.hashfn			= ip4_key_hashfn,
	.obj_hashfn		= ip4_obj_hashfn,
	.obj_cmpfn		= ip4_obj_cmpfn,
	.स्वतःmatic_shrinking	= true,
पूर्ण;

व्योम __init ipfrag_init(व्योम)
अणु
	ip4_frags.स्थिरructor = ip4_frag_init;
	ip4_frags.deकाष्ठाor = ip4_frag_मुक्त;
	ip4_frags.qsize = माप(काष्ठा ipq);
	ip4_frags.frag_expire = ip_expire;
	ip4_frags.frags_cache_name = ip_frag_cache_name;
	ip4_frags.rhash_params = ip4_rhash_params;
	अगर (inet_frags_init(&ip4_frags))
		panic("IP: failed to allocate ip4_frags cache\n");
	ip4_frags_ctl_रेजिस्टर();
	रेजिस्टर_pernet_subsys(&ip4_frags_ops);
पूर्ण
