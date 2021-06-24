<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	IPv6 fragment reassembly
 *	Linux INET6 implementation
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>
 *
 *	Based on: net/ipv4/ip_fragment.c
 */

/*
 *	Fixes:
 *	Andi Kleen	Make it work with multiple hosts.
 *			More RFC compliance.
 *
 *      Horst von Bअक्रम Add missing #समावेश <linux/माला.स>
 *	Alexey Kuznetsov	SMP races, thपढ़ोing, cleanup.
 *	Patrick McHardy		LRU queue of frag heads क्रम evictor.
 *	Mitsuru KANDA @USAGI	Register inet6_protocolअणुपूर्ण.
 *	David Stevens and
 *	YOSHIFUJI,H. @USAGI	Always हटाओ fragment header to
 *				calculate ICV correctly.
 */

#घोषणा pr_fmt(fmt) "IPv6: " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/net.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/in6.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/jhash.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>

#समावेश <net/sock.h>
#समावेश <net/snmp.h>

#समावेश <net/ipv6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/protocol.h>
#समावेश <net/transp_v6.h>
#समावेश <net/rawv6.h>
#समावेश <net/ndisc.h>
#समावेश <net/addrconf.h>
#समावेश <net/ipv6_frag.h>
#समावेश <net/inet_ecn.h>

अटल स्थिर अक्षर ip6_frag_cache_name[] = "ip6-frags";

अटल u8 ip6_frag_ecn(स्थिर काष्ठा ipv6hdr *ipv6h)
अणु
	वापस 1 << (ipv6_get_dsfield(ipv6h) & INET_ECN_MASK);
पूर्ण

अटल काष्ठा inet_frags ip6_frags;

अटल पूर्णांक ip6_frag_reयंत्र(काष्ठा frag_queue *fq, काष्ठा sk_buff *skb,
			  काष्ठा sk_buff *prev_tail, काष्ठा net_device *dev);

अटल व्योम ip6_frag_expire(काष्ठा समयr_list *t)
अणु
	काष्ठा inet_frag_queue *frag = from_समयr(frag, t, समयr);
	काष्ठा frag_queue *fq;

	fq = container_of(frag, काष्ठा frag_queue, q);

	ip6frag_expire_frag_queue(fq->q.fqdir->net, fq);
पूर्ण

अटल काष्ठा frag_queue *
fq_find(काष्ठा net *net, __be32 id, स्थिर काष्ठा ipv6hdr *hdr, पूर्णांक iअगर)
अणु
	काष्ठा frag_v6_compare_key key = अणु
		.id = id,
		.saddr = hdr->saddr,
		.daddr = hdr->daddr,
		.user = IP6_DEFRAG_LOCAL_DELIVER,
		.iअगर = iअगर,
	पूर्ण;
	काष्ठा inet_frag_queue *q;

	अगर (!(ipv6_addr_type(&hdr->daddr) & (IPV6_ADDR_MULTICAST |
					    IPV6_ADDR_LINKLOCAL)))
		key.iअगर = 0;

	q = inet_frag_find(net->ipv6.fqdir, &key);
	अगर (!q)
		वापस शून्य;

	वापस container_of(q, काष्ठा frag_queue, q);
पूर्ण

अटल पूर्णांक ip6_frag_queue(काष्ठा frag_queue *fq, काष्ठा sk_buff *skb,
			  काष्ठा frag_hdr *fhdr, पूर्णांक nhoff,
			  u32 *prob_offset)
अणु
	काष्ठा net *net = dev_net(skb_dst(skb)->dev);
	पूर्णांक offset, end, fragsize;
	काष्ठा sk_buff *prev_tail;
	काष्ठा net_device *dev;
	पूर्णांक err = -ENOENT;
	u8 ecn;

	अगर (fq->q.flags & INET_FRAG_COMPLETE)
		जाओ err;

	err = -EINVAL;
	offset = ntohs(fhdr->frag_off) & ~0x7;
	end = offset + (ntohs(ipv6_hdr(skb)->payload_len) -
			((u8 *)(fhdr + 1) - (u8 *)(ipv6_hdr(skb) + 1)));

	अगर ((अचिन्हित पूर्णांक)end > IPV6_MAXPLEN) अणु
		*prob_offset = (u8 *)&fhdr->frag_off - skb_network_header(skb);
		/* note that अगर prob_offset is set, the skb is मुक्तd अन्यथाwhere,
		 * we करो not मुक्त it here.
		 */
		वापस -1;
	पूर्ण

	ecn = ip6_frag_ecn(ipv6_hdr(skb));

	अगर (skb->ip_summed == CHECKSUM_COMPLETE) अणु
		स्थिर अचिन्हित अक्षर *nh = skb_network_header(skb);
		skb->csum = csum_sub(skb->csum,
				     csum_partial(nh, (u8 *)(fhdr + 1) - nh,
						  0));
	पूर्ण

	/* Is this the final fragment? */
	अगर (!(fhdr->frag_off & htons(IP6_MF))) अणु
		/* If we alपढ़ोy have some bits beyond end
		 * or have dअगरferent end, the segment is corrupted.
		 */
		अगर (end < fq->q.len ||
		    ((fq->q.flags & INET_FRAG_LAST_IN) && end != fq->q.len))
			जाओ discard_fq;
		fq->q.flags |= INET_FRAG_LAST_IN;
		fq->q.len = end;
	पूर्ण अन्यथा अणु
		/* Check अगर the fragment is rounded to 8 bytes.
		 * Required by the RFC.
		 */
		अगर (end & 0x7) अणु
			/* RFC2460 says always send parameter problem in
			 * this हाल. -DaveM
			 */
			*prob_offset = दुरत्व(काष्ठा ipv6hdr, payload_len);
			वापस -1;
		पूर्ण
		अगर (end > fq->q.len) अणु
			/* Some bits beyond end -> corruption. */
			अगर (fq->q.flags & INET_FRAG_LAST_IN)
				जाओ discard_fq;
			fq->q.len = end;
		पूर्ण
	पूर्ण

	अगर (end == offset)
		जाओ discard_fq;

	err = -ENOMEM;
	/* Poपूर्णांक पूर्णांकo the IP datagram 'data' part. */
	अगर (!pskb_pull(skb, (u8 *) (fhdr + 1) - skb->data))
		जाओ discard_fq;

	err = pskb_trim_rcsum(skb, end - offset);
	अगर (err)
		जाओ discard_fq;

	/* Note : skb->rbnode and skb->dev share the same location. */
	dev = skb->dev;
	/* Makes sure compiler wont करो silly aliasing games */
	barrier();

	prev_tail = fq->q.fragments_tail;
	err = inet_frag_queue_insert(&fq->q, skb, offset, end);
	अगर (err)
		जाओ insert_error;

	अगर (dev)
		fq->iअगर = dev->अगरindex;

	fq->q.stamp = skb->tstamp;
	fq->q.meat += skb->len;
	fq->ecn |= ecn;
	add_frag_mem_limit(fq->q.fqdir, skb->truesize);

	fragsize = -skb_network_offset(skb) + skb->len;
	अगर (fragsize > fq->q.max_size)
		fq->q.max_size = fragsize;

	/* The first fragment.
	 * nhoffset is obtained from the first fragment, of course.
	 */
	अगर (offset == 0) अणु
		fq->nhoffset = nhoff;
		fq->q.flags |= INET_FRAG_FIRST_IN;
	पूर्ण

	अगर (fq->q.flags == (INET_FRAG_FIRST_IN | INET_FRAG_LAST_IN) &&
	    fq->q.meat == fq->q.len) अणु
		अचिन्हित दीर्घ orefdst = skb->_skb_refdst;

		skb->_skb_refdst = 0UL;
		err = ip6_frag_reयंत्र(fq, skb, prev_tail, dev);
		skb->_skb_refdst = orefdst;
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
	__IP6_INC_STATS(net, ip6_dst_idev(skb_dst(skb)),
			IPSTATS_MIB_REASM_OVERLAPS);
discard_fq:
	inet_frag_समाप्त(&fq->q);
	__IP6_INC_STATS(net, ip6_dst_idev(skb_dst(skb)),
			IPSTATS_MIB_REASMFAILS);
err:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

/*
 *	Check अगर this packet is complete.
 *
 *	It is called with locked fq, and caller must check that
 *	queue is eligible क्रम reassembly i.e. it is not COMPLETE,
 *	the last and the first frames arrived and all the bits are here.
 */
अटल पूर्णांक ip6_frag_reयंत्र(काष्ठा frag_queue *fq, काष्ठा sk_buff *skb,
			  काष्ठा sk_buff *prev_tail, काष्ठा net_device *dev)
अणु
	काष्ठा net *net = fq->q.fqdir->net;
	अचिन्हित पूर्णांक nhoff;
	व्योम *reयंत्र_data;
	पूर्णांक payload_len;
	u8 ecn;

	inet_frag_समाप्त(&fq->q);

	ecn = ip_frag_ecn_table[fq->ecn];
	अगर (unlikely(ecn == 0xff))
		जाओ out_fail;

	reयंत्र_data = inet_frag_reयंत्र_prepare(&fq->q, skb, prev_tail);
	अगर (!reयंत्र_data)
		जाओ out_oom;

	payload_len = ((skb->data - skb_network_header(skb)) -
		       माप(काष्ठा ipv6hdr) + fq->q.len -
		       माप(काष्ठा frag_hdr));
	अगर (payload_len > IPV6_MAXPLEN)
		जाओ out_oversize;

	/* We have to हटाओ fragment header from datagram and to relocate
	 * header in order to calculate ICV correctly. */
	nhoff = fq->nhoffset;
	skb_network_header(skb)[nhoff] = skb_transport_header(skb)[0];
	स_हटाओ(skb->head + माप(काष्ठा frag_hdr), skb->head,
		(skb->data - skb->head) - माप(काष्ठा frag_hdr));
	अगर (skb_mac_header_was_set(skb))
		skb->mac_header += माप(काष्ठा frag_hdr);
	skb->network_header += माप(काष्ठा frag_hdr);

	skb_reset_transport_header(skb);

	inet_frag_reयंत्र_finish(&fq->q, skb, reयंत्र_data, true);

	skb->dev = dev;
	ipv6_hdr(skb)->payload_len = htons(payload_len);
	ipv6_change_dsfield(ipv6_hdr(skb), 0xff, ecn);
	IP6CB(skb)->nhoff = nhoff;
	IP6CB(skb)->flags |= IP6SKB_FRAGMENTED;
	IP6CB(skb)->frag_max_size = fq->q.max_size;

	/* Yes, and fold redundant checksum back. 8) */
	skb_postpush_rcsum(skb, skb_network_header(skb),
			   skb_network_header_len(skb));

	rcu_पढ़ो_lock();
	__IP6_INC_STATS(net, __in6_dev_stats_get(dev, skb), IPSTATS_MIB_REASMOKS);
	rcu_पढ़ो_unlock();
	fq->q.rb_fragments = RB_ROOT;
	fq->q.fragments_tail = शून्य;
	fq->q.last_run_head = शून्य;
	वापस 1;

out_oversize:
	net_dbg_ratelimited("ip6_frag_reasm: payload len = %d\n", payload_len);
	जाओ out_fail;
out_oom:
	net_dbg_ratelimited("ip6_frag_reasm: no memory for reassembly\n");
out_fail:
	rcu_पढ़ो_lock();
	__IP6_INC_STATS(net, __in6_dev_stats_get(dev, skb), IPSTATS_MIB_REASMFAILS);
	rcu_पढ़ो_unlock();
	inet_frag_समाप्त(&fq->q);
	वापस -1;
पूर्ण

अटल पूर्णांक ipv6_frag_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा frag_hdr *fhdr;
	काष्ठा frag_queue *fq;
	स्थिर काष्ठा ipv6hdr *hdr = ipv6_hdr(skb);
	काष्ठा net *net = dev_net(skb_dst(skb)->dev);
	u8 nexthdr;
	पूर्णांक iअगर;

	अगर (IP6CB(skb)->flags & IP6SKB_FRAGMENTED)
		जाओ fail_hdr;

	__IP6_INC_STATS(net, ip6_dst_idev(skb_dst(skb)), IPSTATS_MIB_REASMREQDS);

	/* Jumbo payload inhibits frag. header */
	अगर (hdr->payload_len == 0)
		जाओ fail_hdr;

	अगर (!pskb_may_pull(skb, (skb_transport_offset(skb) +
				 माप(काष्ठा frag_hdr))))
		जाओ fail_hdr;

	hdr = ipv6_hdr(skb);
	fhdr = (काष्ठा frag_hdr *)skb_transport_header(skb);

	अगर (!(fhdr->frag_off & htons(IP6_OFFSET | IP6_MF))) अणु
		/* It is not a fragmented frame */
		skb->transport_header += माप(काष्ठा frag_hdr);
		__IP6_INC_STATS(net,
				ip6_dst_idev(skb_dst(skb)), IPSTATS_MIB_REASMOKS);

		IP6CB(skb)->nhoff = (u8 *)fhdr - skb_network_header(skb);
		IP6CB(skb)->flags |= IP6SKB_FRAGMENTED;
		IP6CB(skb)->frag_max_size = ntohs(hdr->payload_len) +
					    माप(काष्ठा ipv6hdr);
		वापस 1;
	पूर्ण

	/* RFC 8200, Section 4.5 Fragment Header:
	 * If the first fragment करोes not include all headers through an
	 * Upper-Layer header, then that fragment should be discarded and
	 * an ICMP Parameter Problem, Code 3, message should be sent to
	 * the source of the fragment, with the Poपूर्णांकer field set to zero.
	 */
	nexthdr = hdr->nexthdr;
	अगर (ipv6frag_thdr_truncated(skb, skb_transport_offset(skb), &nexthdr)) अणु
		__IP6_INC_STATS(net, __in6_dev_get_safely(skb->dev),
				IPSTATS_MIB_INHDRERRORS);
		icmpv6_param_prob(skb, ICMPV6_HDR_INCOMP, 0);
		वापस -1;
	पूर्ण

	iअगर = skb->dev ? skb->dev->अगरindex : 0;
	fq = fq_find(net, fhdr->identअगरication, hdr, iअगर);
	अगर (fq) अणु
		u32 prob_offset = 0;
		पूर्णांक ret;

		spin_lock(&fq->q.lock);

		fq->iअगर = iअगर;
		ret = ip6_frag_queue(fq, skb, fhdr, IP6CB(skb)->nhoff,
				     &prob_offset);

		spin_unlock(&fq->q.lock);
		inet_frag_put(&fq->q);
		अगर (prob_offset) अणु
			__IP6_INC_STATS(net, __in6_dev_get_safely(skb->dev),
					IPSTATS_MIB_INHDRERRORS);
			/* icmpv6_param_prob() calls kमुक्त_skb(skb) */
			icmpv6_param_prob(skb, ICMPV6_HDR_FIELD, prob_offset);
		पूर्ण
		वापस ret;
	पूर्ण

	__IP6_INC_STATS(net, ip6_dst_idev(skb_dst(skb)), IPSTATS_MIB_REASMFAILS);
	kमुक्त_skb(skb);
	वापस -1;

fail_hdr:
	__IP6_INC_STATS(net, __in6_dev_get_safely(skb->dev),
			IPSTATS_MIB_INHDRERRORS);
	icmpv6_param_prob(skb, ICMPV6_HDR_FIELD, skb_network_header_len(skb));
	वापस -1;
पूर्ण

अटल स्थिर काष्ठा inet6_protocol frag_protocol = अणु
	.handler	=	ipv6_frag_rcv,
	.flags		=	INET6_PROTO_NOPOLICY,
पूर्ण;

#अगर_घोषित CONFIG_SYSCTL

अटल काष्ठा ctl_table ip6_frags_ns_ctl_table[] = अणु
	अणु
		.procname	= "ip6frag_high_thresh",
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
	अणु
		.procname	= "ip6frag_low_thresh",
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
	अणु
		.procname	= "ip6frag_time",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/* secret पूर्णांकerval has been deprecated */
अटल पूर्णांक ip6_frags_secret_पूर्णांकerval_unused;
अटल काष्ठा ctl_table ip6_frags_ctl_table[] = अणु
	अणु
		.procname	= "ip6frag_secret_interval",
		.data		= &ip6_frags_secret_पूर्णांकerval_unused,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक __net_init ip6_frags_ns_sysctl_रेजिस्टर(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;
	काष्ठा ctl_table_header *hdr;

	table = ip6_frags_ns_ctl_table;
	अगर (!net_eq(net, &init_net)) अणु
		table = kmemdup(table, माप(ip6_frags_ns_ctl_table), GFP_KERNEL);
		अगर (!table)
			जाओ err_alloc;

	पूर्ण
	table[0].data	= &net->ipv6.fqdir->high_thresh;
	table[0].extra1	= &net->ipv6.fqdir->low_thresh;
	table[1].data	= &net->ipv6.fqdir->low_thresh;
	table[1].extra2	= &net->ipv6.fqdir->high_thresh;
	table[2].data	= &net->ipv6.fqdir->समयout;

	hdr = रेजिस्टर_net_sysctl(net, "net/ipv6", table);
	अगर (!hdr)
		जाओ err_reg;

	net->ipv6.sysctl.frags_hdr = hdr;
	वापस 0;

err_reg:
	अगर (!net_eq(net, &init_net))
		kमुक्त(table);
err_alloc:
	वापस -ENOMEM;
पूर्ण

अटल व्योम __net_निकास ip6_frags_ns_sysctl_unरेजिस्टर(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;

	table = net->ipv6.sysctl.frags_hdr->ctl_table_arg;
	unरेजिस्टर_net_sysctl_table(net->ipv6.sysctl.frags_hdr);
	अगर (!net_eq(net, &init_net))
		kमुक्त(table);
पूर्ण

अटल काष्ठा ctl_table_header *ip6_ctl_header;

अटल पूर्णांक ip6_frags_sysctl_रेजिस्टर(व्योम)
अणु
	ip6_ctl_header = रेजिस्टर_net_sysctl(&init_net, "net/ipv6",
			ip6_frags_ctl_table);
	वापस ip6_ctl_header == शून्य ? -ENOMEM : 0;
पूर्ण

अटल व्योम ip6_frags_sysctl_unरेजिस्टर(व्योम)
अणु
	unरेजिस्टर_net_sysctl_table(ip6_ctl_header);
पूर्ण
#अन्यथा
अटल पूर्णांक ip6_frags_ns_sysctl_रेजिस्टर(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण

अटल व्योम ip6_frags_ns_sysctl_unरेजिस्टर(काष्ठा net *net)
अणु
पूर्ण

अटल पूर्णांक ip6_frags_sysctl_रेजिस्टर(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम ip6_frags_sysctl_unरेजिस्टर(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __net_init ipv6_frags_init_net(काष्ठा net *net)
अणु
	पूर्णांक res;

	res = fqdir_init(&net->ipv6.fqdir, &ip6_frags, net);
	अगर (res < 0)
		वापस res;

	net->ipv6.fqdir->high_thresh = IPV6_FRAG_HIGH_THRESH;
	net->ipv6.fqdir->low_thresh = IPV6_FRAG_LOW_THRESH;
	net->ipv6.fqdir->समयout = IPV6_FRAG_TIMEOUT;

	res = ip6_frags_ns_sysctl_रेजिस्टर(net);
	अगर (res < 0)
		fqdir_निकास(net->ipv6.fqdir);
	वापस res;
पूर्ण

अटल व्योम __net_निकास ipv6_frags_pre_निकास_net(काष्ठा net *net)
अणु
	fqdir_pre_निकास(net->ipv6.fqdir);
पूर्ण

अटल व्योम __net_निकास ipv6_frags_निकास_net(काष्ठा net *net)
अणु
	ip6_frags_ns_sysctl_unरेजिस्टर(net);
	fqdir_निकास(net->ipv6.fqdir);
पूर्ण

अटल काष्ठा pernet_operations ip6_frags_ops = अणु
	.init		= ipv6_frags_init_net,
	.pre_निकास	= ipv6_frags_pre_निकास_net,
	.निकास		= ipv6_frags_निकास_net,
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params ip6_rhash_params = अणु
	.head_offset		= दुरत्व(काष्ठा inet_frag_queue, node),
	.hashfn			= ip6frag_key_hashfn,
	.obj_hashfn		= ip6frag_obj_hashfn,
	.obj_cmpfn		= ip6frag_obj_cmpfn,
	.स्वतःmatic_shrinking	= true,
पूर्ण;

पूर्णांक __init ipv6_frag_init(व्योम)
अणु
	पूर्णांक ret;

	ip6_frags.स्थिरructor = ip6frag_init;
	ip6_frags.deकाष्ठाor = शून्य;
	ip6_frags.qsize = माप(काष्ठा frag_queue);
	ip6_frags.frag_expire = ip6_frag_expire;
	ip6_frags.frags_cache_name = ip6_frag_cache_name;
	ip6_frags.rhash_params = ip6_rhash_params;
	ret = inet_frags_init(&ip6_frags);
	अगर (ret)
		जाओ out;

	ret = inet6_add_protocol(&frag_protocol, IPPROTO_FRAGMENT);
	अगर (ret)
		जाओ err_protocol;

	ret = ip6_frags_sysctl_रेजिस्टर();
	अगर (ret)
		जाओ err_sysctl;

	ret = रेजिस्टर_pernet_subsys(&ip6_frags_ops);
	अगर (ret)
		जाओ err_pernet;

out:
	वापस ret;

err_pernet:
	ip6_frags_sysctl_unरेजिस्टर();
err_sysctl:
	inet6_del_protocol(&frag_protocol, IPPROTO_FRAGMENT);
err_protocol:
	inet_frags_fini(&ip6_frags);
	जाओ out;
पूर्ण

व्योम ipv6_frag_निकास(व्योम)
अणु
	ip6_frags_sysctl_unरेजिस्टर();
	unरेजिस्टर_pernet_subsys(&ip6_frags_ops);
	inet6_del_protocol(&frag_protocol, IPPROTO_FRAGMENT);
	inet_frags_fini(&ip6_frags);
पूर्ण
