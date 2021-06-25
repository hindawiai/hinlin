<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		ROUTE - implementation of the IP router.
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Alan Cox, <gw4pts@gw4pts.ampr.org>
 *		Linus Torvalds, <Linus.Torvalds@helsinki.fi>
 *		Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 *
 * Fixes:
 *		Alan Cox	:	Verअगरy area fixes.
 *		Alan Cox	:	cli() protects routing changes
 *		Rui Oliveira	:	ICMP routing table updates
 *		(rco@di.uminho.pt)	Routing table insertion and update
 *		Linus Torvalds	:	Rewrote bits to be sensible
 *		Alan Cox	:	Added BSD route gw semantics
 *		Alan Cox	:	Super /proc >4K
 *		Alan Cox	:	MTU in route table
 *		Alan Cox	:	MSS actually. Also added the winकरोw
 *					clamper.
 *		Sam Lantinga	:	Fixed route matching in rt_del()
 *		Alan Cox	:	Routing cache support.
 *		Alan Cox	:	Removed compatibility cruft.
 *		Alan Cox	:	RTF_REJECT support.
 *		Alan Cox	:	TCP irtt support.
 *		Jonathan Naylor	:	Added Metric support.
 *	Miquel van Smoorenburg	:	BSD API fixes.
 *	Miquel van Smoorenburg	:	Metrics.
 *		Alan Cox	:	Use __u32 properly
 *		Alan Cox	:	Aligned routing errors more बंदly with BSD
 *					our प्रणाली is still very dअगरferent.
 *		Alan Cox	:	Faster /proc handling
 *	Alexey Kuznetsov	:	Massive rework to support tree based routing,
 *					routing caches and better behaviour.
 *
 *		Olaf Erb	:	irtt wasn't being copied right.
 *		Bjorn Ekwall	:	Kerneld route support.
 *		Alan Cox	:	Multicast fixed (I hope)
 *		Pavel Krauz	:	Limited broadcast fixed
 *		Mike McLagan	:	Routing by source
 *	Alexey Kuznetsov	:	End of old history. Split to fib.c and
 *					route.c and rewritten from scratch.
 *		Andi Kleen	:	Load-limit warning messages.
 *	Vitaly E. Lavrov	:	Transparent proxy revived after year coma.
 *	Vitaly E. Lavrov	:	Race condition in ip_route_input_slow.
 *	Tobias Ringstrom	:	Uninitialized res.type in ip_route_output_slow.
 *	Vladimir V. Ivanov	:	IP rule info (flowid) is really useful.
 *		Marc Boucher	:	routing by fwmark
 *	Robert Olsson		:	Added rt_cache statistics
 *	Arnalकरो C. Melo		:	Convert proc stuff to seq_file
 *	Eric Dumazet		:	hashed spinlocks and rt_check_expire() fixes.
 *	Ilia Sotnikov		:	Ignore TOS on PMTUD and Redirect
 *	Ilia Sotnikov		:	Removed TOS from hash calculations
 */

#घोषणा pr_fmt(fmt) "IPv4: " fmt

#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/bitops.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/माला.स>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/init.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/igmp.h>
#समावेश <linux/pkt_sched.h>
#समावेश <linux/mroute.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/बार.h>
#समावेश <linux/slab.h>
#समावेश <linux/jhash.h>
#समावेश <net/dst.h>
#समावेश <net/dst_metadata.h>
#समावेश <net/net_namespace.h>
#समावेश <net/protocol.h>
#समावेश <net/ip.h>
#समावेश <net/route.h>
#समावेश <net/inetpeer.h>
#समावेश <net/sock.h>
#समावेश <net/ip_fib.h>
#समावेश <net/nexthop.h>
#समावेश <net/arp.h>
#समावेश <net/tcp.h>
#समावेश <net/icmp.h>
#समावेश <net/xfrm.h>
#समावेश <net/lwtunnel.h>
#समावेश <net/netevent.h>
#समावेश <net/rtnetlink.h>
#अगर_घोषित CONFIG_SYSCTL
#समावेश <linux/sysctl.h>
#पूर्ण_अगर
#समावेश <net/secure_seq.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/l3mdev.h>

#समावेश "fib_lookup.h"

#घोषणा RT_FL_TOS(oldflp4) \
	((oldflp4)->flowi4_tos & (IPTOS_RT_MASK | RTO_ONLINK))

#घोषणा RT_GC_TIMEOUT (300*HZ)

अटल पूर्णांक ip_rt_max_size;
अटल पूर्णांक ip_rt_redirect_number __पढ़ो_mostly	= 9;
अटल पूर्णांक ip_rt_redirect_load __पढ़ो_mostly	= HZ / 50;
अटल पूर्णांक ip_rt_redirect_silence __पढ़ो_mostly	= ((HZ / 50) << (9 + 1));
अटल पूर्णांक ip_rt_error_cost __पढ़ो_mostly	= HZ;
अटल पूर्णांक ip_rt_error_burst __पढ़ो_mostly	= 5 * HZ;
अटल पूर्णांक ip_rt_mtu_expires __पढ़ो_mostly	= 10 * 60 * HZ;
अटल u32 ip_rt_min_pmtu __पढ़ो_mostly		= 512 + 20 + 20;
अटल पूर्णांक ip_rt_min_advmss __पढ़ो_mostly	= 256;

अटल पूर्णांक ip_rt_gc_समयout __पढ़ो_mostly	= RT_GC_TIMEOUT;

/*
 *	Interface to generic destination cache.
 */

INसूचीECT_CALLABLE_SCOPE
काष्ठा dst_entry	*ipv4_dst_check(काष्ठा dst_entry *dst, u32 cookie);
अटल अचिन्हित पूर्णांक	 ipv4_शेष_advmss(स्थिर काष्ठा dst_entry *dst);
INसूचीECT_CALLABLE_SCOPE
अचिन्हित पूर्णांक		ipv4_mtu(स्थिर काष्ठा dst_entry *dst);
अटल काष्ठा dst_entry *ipv4_negative_advice(काष्ठा dst_entry *dst);
अटल व्योम		 ipv4_link_failure(काष्ठा sk_buff *skb);
अटल व्योम		 ip_rt_update_pmtu(काष्ठा dst_entry *dst, काष्ठा sock *sk,
					   काष्ठा sk_buff *skb, u32 mtu,
					   bool confirm_neigh);
अटल व्योम		 ip_करो_redirect(काष्ठा dst_entry *dst, काष्ठा sock *sk,
					काष्ठा sk_buff *skb);
अटल व्योम		ipv4_dst_destroy(काष्ठा dst_entry *dst);

अटल u32 *ipv4_cow_metrics(काष्ठा dst_entry *dst, अचिन्हित दीर्घ old)
अणु
	WARN_ON(1);
	वापस शून्य;
पूर्ण

अटल काष्ठा neighbour *ipv4_neigh_lookup(स्थिर काष्ठा dst_entry *dst,
					   काष्ठा sk_buff *skb,
					   स्थिर व्योम *daddr);
अटल व्योम ipv4_confirm_neigh(स्थिर काष्ठा dst_entry *dst, स्थिर व्योम *daddr);

अटल काष्ठा dst_ops ipv4_dst_ops = अणु
	.family =		AF_INET,
	.check =		ipv4_dst_check,
	.शेष_advmss =	ipv4_शेष_advmss,
	.mtu =			ipv4_mtu,
	.cow_metrics =		ipv4_cow_metrics,
	.destroy =		ipv4_dst_destroy,
	.negative_advice =	ipv4_negative_advice,
	.link_failure =		ipv4_link_failure,
	.update_pmtu =		ip_rt_update_pmtu,
	.redirect =		ip_करो_redirect,
	.local_out =		__ip_local_out,
	.neigh_lookup =		ipv4_neigh_lookup,
	.confirm_neigh =	ipv4_confirm_neigh,
पूर्ण;

#घोषणा ECN_OR_COST(class)	TC_PRIO_##class

स्थिर __u8 ip_tos2prio[16] = अणु
	TC_PRIO_BESTEFFORT,
	ECN_OR_COST(BESTEFFORT),
	TC_PRIO_BESTEFFORT,
	ECN_OR_COST(BESTEFFORT),
	TC_PRIO_BULK,
	ECN_OR_COST(BULK),
	TC_PRIO_BULK,
	ECN_OR_COST(BULK),
	TC_PRIO_INTERACTIVE,
	ECN_OR_COST(INTERACTIVE),
	TC_PRIO_INTERACTIVE,
	ECN_OR_COST(INTERACTIVE),
	TC_PRIO_INTERACTIVE_BULK,
	ECN_OR_COST(INTERACTIVE_BULK),
	TC_PRIO_INTERACTIVE_BULK,
	ECN_OR_COST(INTERACTIVE_BULK)
पूर्ण;
EXPORT_SYMBOL(ip_tos2prio);

अटल DEFINE_PER_CPU(काष्ठा rt_cache_stat, rt_cache_stat);
#घोषणा RT_CACHE_STAT_INC(field) raw_cpu_inc(rt_cache_stat.field)

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम *rt_cache_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	अगर (*pos)
		वापस शून्य;
	वापस SEQ_START_TOKEN;
पूर्ण

अटल व्योम *rt_cache_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस शून्य;
पूर्ण

अटल व्योम rt_cache_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक rt_cache_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN)
		seq_म_लिखो(seq, "%-127s\n",
			   "Iface\tDestination\tGateway \tFlags\t\tRefCnt\tUse\t"
			   "Metric\tSource\t\tMTU\tWindow\tIRTT\tTOS\tHHRef\t"
			   "HHUptod\tSpecDst");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations rt_cache_seq_ops = अणु
	.start  = rt_cache_seq_start,
	.next   = rt_cache_seq_next,
	.stop   = rt_cache_seq_stop,
	.show   = rt_cache_seq_show,
पूर्ण;

अटल व्योम *rt_cpu_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	पूर्णांक cpu;

	अगर (*pos == 0)
		वापस SEQ_START_TOKEN;

	क्रम (cpu = *pos-1; cpu < nr_cpu_ids; ++cpu) अणु
		अगर (!cpu_possible(cpu))
			जारी;
		*pos = cpu+1;
		वापस &per_cpu(rt_cache_stat, cpu);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम *rt_cpu_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	पूर्णांक cpu;

	क्रम (cpu = *pos; cpu < nr_cpu_ids; ++cpu) अणु
		अगर (!cpu_possible(cpu))
			जारी;
		*pos = cpu+1;
		वापस &per_cpu(rt_cache_stat, cpu);
	पूर्ण
	(*pos)++;
	वापस शून्य;

पूर्ण

अटल व्योम rt_cpu_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु

पूर्ण

अटल पूर्णांक rt_cpu_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा rt_cache_stat *st = v;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_म_लिखो(seq, "entries  in_hit in_slow_tot in_slow_mc in_no_route in_brd in_martian_dst in_martian_src  out_hit out_slow_tot out_slow_mc  gc_total gc_ignored gc_goal_miss gc_dst_overflow in_hlist_search out_hlist_search\n");
		वापस 0;
	पूर्ण

	seq_म_लिखो(seq,"%08x  %08x %08x %08x %08x %08x %08x %08x "
		   " %08x %08x %08x %08x %08x %08x %08x %08x %08x \n",
		   dst_entries_get_slow(&ipv4_dst_ops),
		   0, /* st->in_hit */
		   st->in_slow_tot,
		   st->in_slow_mc,
		   st->in_no_route,
		   st->in_brd,
		   st->in_martian_dst,
		   st->in_martian_src,

		   0, /* st->out_hit */
		   st->out_slow_tot,
		   st->out_slow_mc,

		   0, /* st->gc_total */
		   0, /* st->gc_ignored */
		   0, /* st->gc_goal_miss */
		   0, /* st->gc_dst_overflow */
		   0, /* st->in_hlist_search */
		   0  /* st->out_hlist_search */
		);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations rt_cpu_seq_ops = अणु
	.start  = rt_cpu_seq_start,
	.next   = rt_cpu_seq_next,
	.stop   = rt_cpu_seq_stop,
	.show   = rt_cpu_seq_show,
पूर्ण;

#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
अटल पूर्णांक rt_acct_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा ip_rt_acct *dst, *src;
	अचिन्हित पूर्णांक i, j;

	dst = kसुस्मृति(256, माप(काष्ठा ip_rt_acct), GFP_KERNEL);
	अगर (!dst)
		वापस -ENOMEM;

	क्रम_each_possible_cpu(i) अणु
		src = (काष्ठा ip_rt_acct *)per_cpu_ptr(ip_rt_acct, i);
		क्रम (j = 0; j < 256; j++) अणु
			dst[j].o_bytes   += src[j].o_bytes;
			dst[j].o_packets += src[j].o_packets;
			dst[j].i_bytes   += src[j].i_bytes;
			dst[j].i_packets += src[j].i_packets;
		पूर्ण
	पूर्ण

	seq_ग_लिखो(m, dst, 256 * माप(काष्ठा ip_rt_acct));
	kमुक्त(dst);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __net_init ip_rt_करो_proc_init(काष्ठा net *net)
अणु
	काष्ठा proc_dir_entry *pde;

	pde = proc_create_seq("rt_cache", 0444, net->proc_net,
			      &rt_cache_seq_ops);
	अगर (!pde)
		जाओ err1;

	pde = proc_create_seq("rt_cache", 0444, net->proc_net_stat,
			      &rt_cpu_seq_ops);
	अगर (!pde)
		जाओ err2;

#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	pde = proc_create_single("rt_acct", 0, net->proc_net,
			rt_acct_proc_show);
	अगर (!pde)
		जाओ err3;
#पूर्ण_अगर
	वापस 0;

#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
err3:
	हटाओ_proc_entry("rt_cache", net->proc_net_stat);
#पूर्ण_अगर
err2:
	हटाओ_proc_entry("rt_cache", net->proc_net);
err1:
	वापस -ENOMEM;
पूर्ण

अटल व्योम __net_निकास ip_rt_करो_proc_निकास(काष्ठा net *net)
अणु
	हटाओ_proc_entry("rt_cache", net->proc_net_stat);
	हटाओ_proc_entry("rt_cache", net->proc_net);
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	हटाओ_proc_entry("rt_acct", net->proc_net);
#पूर्ण_अगर
पूर्ण

अटल काष्ठा pernet_operations ip_rt_proc_ops __net_initdata =  अणु
	.init = ip_rt_करो_proc_init,
	.निकास = ip_rt_करो_proc_निकास,
पूर्ण;

अटल पूर्णांक __init ip_rt_proc_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&ip_rt_proc_ops);
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक ip_rt_proc_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

अटल अंतरभूत bool rt_is_expired(स्थिर काष्ठा rtable *rth)
अणु
	वापस rth->rt_genid != rt_genid_ipv4(dev_net(rth->dst.dev));
पूर्ण

व्योम rt_cache_flush(काष्ठा net *net)
अणु
	rt_genid_bump_ipv4(net);
पूर्ण

अटल काष्ठा neighbour *ipv4_neigh_lookup(स्थिर काष्ठा dst_entry *dst,
					   काष्ठा sk_buff *skb,
					   स्थिर व्योम *daddr)
अणु
	स्थिर काष्ठा rtable *rt = container_of(dst, काष्ठा rtable, dst);
	काष्ठा net_device *dev = dst->dev;
	काष्ठा neighbour *n;

	rcu_पढ़ो_lock_bh();

	अगर (likely(rt->rt_gw_family == AF_INET)) अणु
		n = ip_neigh_gw4(dev, rt->rt_gw4);
	पूर्ण अन्यथा अगर (rt->rt_gw_family == AF_INET6) अणु
		n = ip_neigh_gw6(dev, &rt->rt_gw6);
        पूर्ण अन्यथा अणु
		__be32 pkey;

		pkey = skb ? ip_hdr(skb)->daddr : *((__be32 *) daddr);
		n = ip_neigh_gw4(dev, pkey);
	पूर्ण

	अगर (!IS_ERR(n) && !refcount_inc_not_zero(&n->refcnt))
		n = शून्य;

	rcu_पढ़ो_unlock_bh();

	वापस n;
पूर्ण

अटल व्योम ipv4_confirm_neigh(स्थिर काष्ठा dst_entry *dst, स्थिर व्योम *daddr)
अणु
	स्थिर काष्ठा rtable *rt = container_of(dst, काष्ठा rtable, dst);
	काष्ठा net_device *dev = dst->dev;
	स्थिर __be32 *pkey = daddr;

	अगर (rt->rt_gw_family == AF_INET) अणु
		pkey = (स्थिर __be32 *)&rt->rt_gw4;
	पूर्ण अन्यथा अगर (rt->rt_gw_family == AF_INET6) अणु
		वापस __ipv6_confirm_neigh_stub(dev, &rt->rt_gw6);
	पूर्ण अन्यथा अगर (!daddr ||
		 (rt->rt_flags &
		  (RTCF_MULTICAST | RTCF_BROADCAST | RTCF_LOCAL))) अणु
		वापस;
	पूर्ण
	__ipv4_confirm_neigh(dev, *(__क्रमce u32 *)pkey);
पूर्ण

/* Hash tables of size 2048..262144 depending on RAM size.
 * Each bucket uses 8 bytes.
 */
अटल u32 ip_idents_mask __पढ़ो_mostly;
अटल atomic_t *ip_idents __पढ़ो_mostly;
अटल u32 *ip_tstamps __पढ़ो_mostly;

/* In order to protect privacy, we add a perturbation to identअगरiers
 * अगर one generator is selकरोm used. This makes hard क्रम an attacker
 * to infer how many packets were sent between two poपूर्णांकs in समय.
 */
u32 ip_idents_reserve(u32 hash, पूर्णांक segs)
अणु
	u32 bucket, old, now = (u32)jअगरfies;
	atomic_t *p_id;
	u32 *p_tstamp;
	u32 delta = 0;

	bucket = hash & ip_idents_mask;
	p_tstamp = ip_tstamps + bucket;
	p_id = ip_idents + bucket;
	old = READ_ONCE(*p_tstamp);

	अगर (old != now && cmpxchg(p_tstamp, old, now) == old)
		delta = pअक्रमom_u32_max(now - old);

	/* If UBSAN reports an error there, please make sure your compiler
	 * supports -fno-strict-overflow beक्रमe reporting it that was a bug
	 * in UBSAN, and it has been fixed in GCC-8.
	 */
	वापस atomic_add_वापस(segs + delta, p_id) - segs;
पूर्ण
EXPORT_SYMBOL(ip_idents_reserve);

व्योम __ip_select_ident(काष्ठा net *net, काष्ठा iphdr *iph, पूर्णांक segs)
अणु
	u32 hash, id;

	/* Note the following code is not safe, but this is okay. */
	अगर (unlikely(siphash_key_is_zero(&net->ipv4.ip_id_key)))
		get_अक्रमom_bytes(&net->ipv4.ip_id_key,
				 माप(net->ipv4.ip_id_key));

	hash = siphash_3u32((__क्रमce u32)iph->daddr,
			    (__क्रमce u32)iph->saddr,
			    iph->protocol,
			    &net->ipv4.ip_id_key);
	id = ip_idents_reserve(hash, segs);
	iph->id = htons(id);
पूर्ण
EXPORT_SYMBOL(__ip_select_ident);

अटल व्योम __build_flow_key(स्थिर काष्ठा net *net, काष्ठा flowi4 *fl4,
			     स्थिर काष्ठा sock *sk,
			     स्थिर काष्ठा iphdr *iph,
			     पूर्णांक oअगर, u8 tos,
			     u8 prot, u32 mark, पूर्णांक flow_flags)
अणु
	अगर (sk) अणु
		स्थिर काष्ठा inet_sock *inet = inet_sk(sk);

		oअगर = sk->sk_bound_dev_अगर;
		mark = sk->sk_mark;
		tos = RT_CONN_FLAGS(sk);
		prot = inet->hdrincl ? IPPROTO_RAW : sk->sk_protocol;
	पूर्ण
	flowi4_init_output(fl4, oअगर, mark, tos,
			   RT_SCOPE_UNIVERSE, prot,
			   flow_flags,
			   iph->daddr, iph->saddr, 0, 0,
			   sock_net_uid(net, sk));
पूर्ण

अटल व्योम build_skb_flow_key(काष्ठा flowi4 *fl4, स्थिर काष्ठा sk_buff *skb,
			       स्थिर काष्ठा sock *sk)
अणु
	स्थिर काष्ठा net *net = dev_net(skb->dev);
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	पूर्णांक oअगर = skb->dev->अगरindex;
	u8 tos = RT_TOS(iph->tos);
	u8 prot = iph->protocol;
	u32 mark = skb->mark;

	__build_flow_key(net, fl4, sk, iph, oअगर, tos, prot, mark, 0);
पूर्ण

अटल व्योम build_sk_flow_key(काष्ठा flowi4 *fl4, स्थिर काष्ठा sock *sk)
अणु
	स्थिर काष्ठा inet_sock *inet = inet_sk(sk);
	स्थिर काष्ठा ip_options_rcu *inet_opt;
	__be32 daddr = inet->inet_daddr;

	rcu_पढ़ो_lock();
	inet_opt = rcu_dereference(inet->inet_opt);
	अगर (inet_opt && inet_opt->opt.srr)
		daddr = inet_opt->opt.faddr;
	flowi4_init_output(fl4, sk->sk_bound_dev_अगर, sk->sk_mark,
			   RT_CONN_FLAGS(sk), RT_SCOPE_UNIVERSE,
			   inet->hdrincl ? IPPROTO_RAW : sk->sk_protocol,
			   inet_sk_flowi_flags(sk),
			   daddr, inet->inet_saddr, 0, 0, sk->sk_uid);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम ip_rt_build_flow_key(काष्ठा flowi4 *fl4, स्थिर काष्ठा sock *sk,
				 स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (skb)
		build_skb_flow_key(fl4, skb, sk);
	अन्यथा
		build_sk_flow_key(fl4, sk);
पूर्ण

अटल DEFINE_SPINLOCK(fnhe_lock);

अटल व्योम fnhe_flush_routes(काष्ठा fib_nh_exception *fnhe)
अणु
	काष्ठा rtable *rt;

	rt = rcu_dereference(fnhe->fnhe_rth_input);
	अगर (rt) अणु
		RCU_INIT_POINTER(fnhe->fnhe_rth_input, शून्य);
		dst_dev_put(&rt->dst);
		dst_release(&rt->dst);
	पूर्ण
	rt = rcu_dereference(fnhe->fnhe_rth_output);
	अगर (rt) अणु
		RCU_INIT_POINTER(fnhe->fnhe_rth_output, शून्य);
		dst_dev_put(&rt->dst);
		dst_release(&rt->dst);
	पूर्ण
पूर्ण

अटल काष्ठा fib_nh_exception *fnhe_oldest(काष्ठा fnhe_hash_bucket *hash)
अणु
	काष्ठा fib_nh_exception *fnhe, *oldest;

	oldest = rcu_dereference(hash->chain);
	क्रम (fnhe = rcu_dereference(oldest->fnhe_next); fnhe;
	     fnhe = rcu_dereference(fnhe->fnhe_next)) अणु
		अगर (समय_beक्रमe(fnhe->fnhe_stamp, oldest->fnhe_stamp))
			oldest = fnhe;
	पूर्ण
	fnhe_flush_routes(oldest);
	वापस oldest;
पूर्ण

अटल अंतरभूत u32 fnhe_hashfun(__be32 daddr)
अणु
	अटल u32 fnhe_hashrnd __पढ़ो_mostly;
	u32 hval;

	net_get_अक्रमom_once(&fnhe_hashrnd, माप(fnhe_hashrnd));
	hval = jhash_1word((__क्रमce u32)daddr, fnhe_hashrnd);
	वापस hash_32(hval, FNHE_HASH_SHIFT);
पूर्ण

अटल व्योम fill_route_from_fnhe(काष्ठा rtable *rt, काष्ठा fib_nh_exception *fnhe)
अणु
	rt->rt_pmtu = fnhe->fnhe_pmtu;
	rt->rt_mtu_locked = fnhe->fnhe_mtu_locked;
	rt->dst.expires = fnhe->fnhe_expires;

	अगर (fnhe->fnhe_gw) अणु
		rt->rt_flags |= RTCF_REसूचीECTED;
		rt->rt_uses_gateway = 1;
		rt->rt_gw_family = AF_INET;
		rt->rt_gw4 = fnhe->fnhe_gw;
	पूर्ण
पूर्ण

अटल व्योम update_or_create_fnhe(काष्ठा fib_nh_common *nhc, __be32 daddr,
				  __be32 gw, u32 pmtu, bool lock,
				  अचिन्हित दीर्घ expires)
अणु
	काष्ठा fnhe_hash_bucket *hash;
	काष्ठा fib_nh_exception *fnhe;
	काष्ठा rtable *rt;
	u32 genid, hval;
	अचिन्हित पूर्णांक i;
	पूर्णांक depth;

	genid = fnhe_genid(dev_net(nhc->nhc_dev));
	hval = fnhe_hashfun(daddr);

	spin_lock_bh(&fnhe_lock);

	hash = rcu_dereference(nhc->nhc_exceptions);
	अगर (!hash) अणु
		hash = kसुस्मृति(FNHE_HASH_SIZE, माप(*hash), GFP_ATOMIC);
		अगर (!hash)
			जाओ out_unlock;
		rcu_assign_poपूर्णांकer(nhc->nhc_exceptions, hash);
	पूर्ण

	hash += hval;

	depth = 0;
	क्रम (fnhe = rcu_dereference(hash->chain); fnhe;
	     fnhe = rcu_dereference(fnhe->fnhe_next)) अणु
		अगर (fnhe->fnhe_daddr == daddr)
			अवरोध;
		depth++;
	पूर्ण

	अगर (fnhe) अणु
		अगर (fnhe->fnhe_genid != genid)
			fnhe->fnhe_genid = genid;
		अगर (gw)
			fnhe->fnhe_gw = gw;
		अगर (pmtu) अणु
			fnhe->fnhe_pmtu = pmtu;
			fnhe->fnhe_mtu_locked = lock;
		पूर्ण
		fnhe->fnhe_expires = max(1UL, expires);
		/* Update all cached dsts too */
		rt = rcu_dereference(fnhe->fnhe_rth_input);
		अगर (rt)
			fill_route_from_fnhe(rt, fnhe);
		rt = rcu_dereference(fnhe->fnhe_rth_output);
		अगर (rt)
			fill_route_from_fnhe(rt, fnhe);
	पूर्ण अन्यथा अणु
		अगर (depth > FNHE_RECLAIM_DEPTH)
			fnhe = fnhe_oldest(hash);
		अन्यथा अणु
			fnhe = kzalloc(माप(*fnhe), GFP_ATOMIC);
			अगर (!fnhe)
				जाओ out_unlock;

			fnhe->fnhe_next = hash->chain;
			rcu_assign_poपूर्णांकer(hash->chain, fnhe);
		पूर्ण
		fnhe->fnhe_genid = genid;
		fnhe->fnhe_daddr = daddr;
		fnhe->fnhe_gw = gw;
		fnhe->fnhe_pmtu = pmtu;
		fnhe->fnhe_mtu_locked = lock;
		fnhe->fnhe_expires = max(1UL, expires);

		/* Exception created; mark the cached routes क्रम the nexthop
		 * stale, so anyone caching it rechecks अगर this exception
		 * applies to them.
		 */
		rt = rcu_dereference(nhc->nhc_rth_input);
		अगर (rt)
			rt->dst.obsolete = DST_OBSOLETE_KILL;

		क्रम_each_possible_cpu(i) अणु
			काष्ठा rtable __rcu **prt;

			prt = per_cpu_ptr(nhc->nhc_pcpu_rth_output, i);
			rt = rcu_dereference(*prt);
			अगर (rt)
				rt->dst.obsolete = DST_OBSOLETE_KILL;
		पूर्ण
	पूर्ण

	fnhe->fnhe_stamp = jअगरfies;

out_unlock:
	spin_unlock_bh(&fnhe_lock);
पूर्ण

अटल व्योम __ip_करो_redirect(काष्ठा rtable *rt, काष्ठा sk_buff *skb, काष्ठा flowi4 *fl4,
			     bool समाप्त_route)
अणु
	__be32 new_gw = icmp_hdr(skb)->un.gateway;
	__be32 old_gw = ip_hdr(skb)->saddr;
	काष्ठा net_device *dev = skb->dev;
	काष्ठा in_device *in_dev;
	काष्ठा fib_result res;
	काष्ठा neighbour *n;
	काष्ठा net *net;

	चयन (icmp_hdr(skb)->code & 7) अणु
	हाल ICMP_REसूची_NET:
	हाल ICMP_REसूची_NETTOS:
	हाल ICMP_REसूची_HOST:
	हाल ICMP_REसूची_HOSTTOS:
		अवरोध;

	शेष:
		वापस;
	पूर्ण

	अगर (rt->rt_gw_family != AF_INET || rt->rt_gw4 != old_gw)
		वापस;

	in_dev = __in_dev_get_rcu(dev);
	अगर (!in_dev)
		वापस;

	net = dev_net(dev);
	अगर (new_gw == old_gw || !IN_DEV_RX_REसूचीECTS(in_dev) ||
	    ipv4_is_multicast(new_gw) || ipv4_is_lbcast(new_gw) ||
	    ipv4_is_zeronet(new_gw))
		जाओ reject_redirect;

	अगर (!IN_DEV_SHARED_MEDIA(in_dev)) अणु
		अगर (!inet_addr_onlink(in_dev, new_gw, old_gw))
			जाओ reject_redirect;
		अगर (IN_DEV_SEC_REसूचीECTS(in_dev) && ip_fib_check_शेष(new_gw, dev))
			जाओ reject_redirect;
	पूर्ण अन्यथा अणु
		अगर (inet_addr_type(net, new_gw) != RTN_UNICAST)
			जाओ reject_redirect;
	पूर्ण

	n = __ipv4_neigh_lookup(rt->dst.dev, new_gw);
	अगर (!n)
		n = neigh_create(&arp_tbl, &new_gw, rt->dst.dev);
	अगर (!IS_ERR(n)) अणु
		अगर (!(n->nud_state & NUD_VALID)) अणु
			neigh_event_send(n, शून्य);
		पूर्ण अन्यथा अणु
			अगर (fib_lookup(net, fl4, &res, 0) == 0) अणु
				काष्ठा fib_nh_common *nhc;

				fib_select_path(net, &res, fl4, skb);
				nhc = FIB_RES_NHC(res);
				update_or_create_fnhe(nhc, fl4->daddr, new_gw,
						0, false,
						jअगरfies + ip_rt_gc_समयout);
			पूर्ण
			अगर (समाप्त_route)
				rt->dst.obsolete = DST_OBSOLETE_KILL;
			call_netevent_notअगरiers(NETEVENT_NEIGH_UPDATE, n);
		पूर्ण
		neigh_release(n);
	पूर्ण
	वापस;

reject_redirect:
#अगर_घोषित CONFIG_IP_ROUTE_VERBOSE
	अगर (IN_DEV_LOG_MARTIANS(in_dev)) अणु
		स्थिर काष्ठा iphdr *iph = (स्थिर काष्ठा iphdr *) skb->data;
		__be32 daddr = iph->daddr;
		__be32 saddr = iph->saddr;

		net_info_ratelimited("Redirect from %pI4 on %s about %pI4 ignored\n"
				     "  Advised path = %pI4 -> %pI4\n",
				     &old_gw, dev->name, &new_gw,
				     &saddr, &daddr);
	पूर्ण
#पूर्ण_अगर
	;
पूर्ण

अटल व्योम ip_करो_redirect(काष्ठा dst_entry *dst, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtable *rt;
	काष्ठा flowi4 fl4;
	स्थिर काष्ठा iphdr *iph = (स्थिर काष्ठा iphdr *) skb->data;
	काष्ठा net *net = dev_net(skb->dev);
	पूर्णांक oअगर = skb->dev->अगरindex;
	u8 tos = RT_TOS(iph->tos);
	u8 prot = iph->protocol;
	u32 mark = skb->mark;

	rt = (काष्ठा rtable *) dst;

	__build_flow_key(net, &fl4, sk, iph, oअगर, tos, prot, mark, 0);
	__ip_करो_redirect(rt, skb, &fl4, true);
पूर्ण

अटल काष्ठा dst_entry *ipv4_negative_advice(काष्ठा dst_entry *dst)
अणु
	काष्ठा rtable *rt = (काष्ठा rtable *)dst;
	काष्ठा dst_entry *ret = dst;

	अगर (rt) अणु
		अगर (dst->obsolete > 0) अणु
			ip_rt_put(rt);
			ret = शून्य;
		पूर्ण अन्यथा अगर ((rt->rt_flags & RTCF_REसूचीECTED) ||
			   rt->dst.expires) अणु
			ip_rt_put(rt);
			ret = शून्य;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Algorithm:
 *	1. The first ip_rt_redirect_number redirects are sent
 *	   with exponential backoff, then we stop sending them at all,
 *	   assuming that the host ignores our redirects.
 *	2. If we did not see packets requiring redirects
 *	   during ip_rt_redirect_silence, we assume that the host
 *	   क्रमgot redirected route and start to send redirects again.
 *
 * This algorithm is much cheaper and more पूर्णांकelligent than dumb load limiting
 * in icmp.c.
 *
 * NOTE. Do not क्रमget to inhibit load limiting क्रम redirects (redundant)
 * and "frag. need" (अवरोधs PMTU discovery) in icmp.c.
 */

व्योम ip_rt_send_redirect(काष्ठा sk_buff *skb)
अणु
	काष्ठा rtable *rt = skb_rtable(skb);
	काष्ठा in_device *in_dev;
	काष्ठा inet_peer *peer;
	काष्ठा net *net;
	पूर्णांक log_martians;
	पूर्णांक vअगर;

	rcu_पढ़ो_lock();
	in_dev = __in_dev_get_rcu(rt->dst.dev);
	अगर (!in_dev || !IN_DEV_TX_REसूचीECTS(in_dev)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	log_martians = IN_DEV_LOG_MARTIANS(in_dev);
	vअगर = l3mdev_master_अगरindex_rcu(rt->dst.dev);
	rcu_पढ़ो_unlock();

	net = dev_net(rt->dst.dev);
	peer = inet_getpeer_v4(net->ipv4.peers, ip_hdr(skb)->saddr, vअगर, 1);
	अगर (!peer) अणु
		icmp_send(skb, ICMP_REसूचीECT, ICMP_REसूची_HOST,
			  rt_nexthop(rt, ip_hdr(skb)->daddr));
		वापस;
	पूर्ण

	/* No redirected packets during ip_rt_redirect_silence;
	 * reset the algorithm.
	 */
	अगर (समय_after(jअगरfies, peer->rate_last + ip_rt_redirect_silence)) अणु
		peer->rate_tokens = 0;
		peer->n_redirects = 0;
	पूर्ण

	/* Too many ignored redirects; करो not send anything
	 * set dst.rate_last to the last seen redirected packet.
	 */
	अगर (peer->n_redirects >= ip_rt_redirect_number) अणु
		peer->rate_last = jअगरfies;
		जाओ out_put_peer;
	पूर्ण

	/* Check क्रम load limit; set rate_last to the latest sent
	 * redirect.
	 */
	अगर (peer->n_redirects == 0 ||
	    समय_after(jअगरfies,
		       (peer->rate_last +
			(ip_rt_redirect_load << peer->n_redirects)))) अणु
		__be32 gw = rt_nexthop(rt, ip_hdr(skb)->daddr);

		icmp_send(skb, ICMP_REसूचीECT, ICMP_REसूची_HOST, gw);
		peer->rate_last = jअगरfies;
		++peer->n_redirects;
#अगर_घोषित CONFIG_IP_ROUTE_VERBOSE
		अगर (log_martians &&
		    peer->n_redirects == ip_rt_redirect_number)
			net_warn_ratelimited("host %pI4/if%d ignores redirects for %pI4 to %pI4\n",
					     &ip_hdr(skb)->saddr, inet_iअगर(skb),
					     &ip_hdr(skb)->daddr, &gw);
#पूर्ण_अगर
	पूर्ण
out_put_peer:
	inet_putpeer(peer);
पूर्ण

अटल पूर्णांक ip_error(काष्ठा sk_buff *skb)
अणु
	काष्ठा rtable *rt = skb_rtable(skb);
	काष्ठा net_device *dev = skb->dev;
	काष्ठा in_device *in_dev;
	काष्ठा inet_peer *peer;
	अचिन्हित दीर्घ now;
	काष्ठा net *net;
	bool send;
	पूर्णांक code;

	अगर (netअगर_is_l3_master(skb->dev)) अणु
		dev = __dev_get_by_index(dev_net(skb->dev), IPCB(skb)->iअगर);
		अगर (!dev)
			जाओ out;
	पूर्ण

	in_dev = __in_dev_get_rcu(dev);

	/* IP on this device is disabled. */
	अगर (!in_dev)
		जाओ out;

	net = dev_net(rt->dst.dev);
	अगर (!IN_DEV_FORWARD(in_dev)) अणु
		चयन (rt->dst.error) अणु
		हाल EHOSTUNREACH:
			__IP_INC_STATS(net, IPSTATS_MIB_INADDRERRORS);
			अवरोध;

		हाल ENETUNREACH:
			__IP_INC_STATS(net, IPSTATS_MIB_INNOROUTES);
			अवरोध;
		पूर्ण
		जाओ out;
	पूर्ण

	चयन (rt->dst.error) अणु
	हाल EINVAL:
	शेष:
		जाओ out;
	हाल EHOSTUNREACH:
		code = ICMP_HOST_UNREACH;
		अवरोध;
	हाल ENETUNREACH:
		code = ICMP_NET_UNREACH;
		__IP_INC_STATS(net, IPSTATS_MIB_INNOROUTES);
		अवरोध;
	हाल EACCES:
		code = ICMP_PKT_FILTERED;
		अवरोध;
	पूर्ण

	peer = inet_getpeer_v4(net->ipv4.peers, ip_hdr(skb)->saddr,
			       l3mdev_master_अगरindex(skb->dev), 1);

	send = true;
	अगर (peer) अणु
		now = jअगरfies;
		peer->rate_tokens += now - peer->rate_last;
		अगर (peer->rate_tokens > ip_rt_error_burst)
			peer->rate_tokens = ip_rt_error_burst;
		peer->rate_last = now;
		अगर (peer->rate_tokens >= ip_rt_error_cost)
			peer->rate_tokens -= ip_rt_error_cost;
		अन्यथा
			send = false;
		inet_putpeer(peer);
	पूर्ण
	अगर (send)
		icmp_send(skb, ICMP_DEST_UNREACH, code, 0);

out:	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल व्योम __ip_rt_update_pmtu(काष्ठा rtable *rt, काष्ठा flowi4 *fl4, u32 mtu)
अणु
	काष्ठा dst_entry *dst = &rt->dst;
	काष्ठा net *net = dev_net(dst->dev);
	काष्ठा fib_result res;
	bool lock = false;
	u32 old_mtu;

	अगर (ip_mtu_locked(dst))
		वापस;

	old_mtu = ipv4_mtu(dst);
	अगर (old_mtu < mtu)
		वापस;

	अगर (mtu < ip_rt_min_pmtu) अणु
		lock = true;
		mtu = min(old_mtu, ip_rt_min_pmtu);
	पूर्ण

	अगर (rt->rt_pmtu == mtu && !lock &&
	    समय_beक्रमe(jअगरfies, dst->expires - ip_rt_mtu_expires / 2))
		वापस;

	rcu_पढ़ो_lock();
	अगर (fib_lookup(net, fl4, &res, 0) == 0) अणु
		काष्ठा fib_nh_common *nhc;

		fib_select_path(net, &res, fl4, शून्य);
		nhc = FIB_RES_NHC(res);
		update_or_create_fnhe(nhc, fl4->daddr, 0, mtu, lock,
				      jअगरfies + ip_rt_mtu_expires);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम ip_rt_update_pmtu(काष्ठा dst_entry *dst, काष्ठा sock *sk,
			      काष्ठा sk_buff *skb, u32 mtu,
			      bool confirm_neigh)
अणु
	काष्ठा rtable *rt = (काष्ठा rtable *) dst;
	काष्ठा flowi4 fl4;

	ip_rt_build_flow_key(&fl4, sk, skb);

	/* Don't make lookup fail क्रम bridged encapsulations */
	अगर (skb && netअगर_is_any_bridge_port(skb->dev))
		fl4.flowi4_oअगर = 0;

	__ip_rt_update_pmtu(rt, &fl4, mtu);
पूर्ण

व्योम ipv4_update_pmtu(काष्ठा sk_buff *skb, काष्ठा net *net, u32 mtu,
		      पूर्णांक oअगर, u8 protocol)
अणु
	स्थिर काष्ठा iphdr *iph = (स्थिर काष्ठा iphdr *)skb->data;
	काष्ठा flowi4 fl4;
	काष्ठा rtable *rt;
	u32 mark = IP4_REPLY_MARK(net, skb->mark);

	__build_flow_key(net, &fl4, शून्य, iph, oअगर,
			 RT_TOS(iph->tos), protocol, mark, 0);
	rt = __ip_route_output_key(net, &fl4);
	अगर (!IS_ERR(rt)) अणु
		__ip_rt_update_pmtu(rt, &fl4, mtu);
		ip_rt_put(rt);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ipv4_update_pmtu);

अटल व्योम __ipv4_sk_update_pmtu(काष्ठा sk_buff *skb, काष्ठा sock *sk, u32 mtu)
अणु
	स्थिर काष्ठा iphdr *iph = (स्थिर काष्ठा iphdr *)skb->data;
	काष्ठा flowi4 fl4;
	काष्ठा rtable *rt;

	__build_flow_key(sock_net(sk), &fl4, sk, iph, 0, 0, 0, 0, 0);

	अगर (!fl4.flowi4_mark)
		fl4.flowi4_mark = IP4_REPLY_MARK(sock_net(sk), skb->mark);

	rt = __ip_route_output_key(sock_net(sk), &fl4);
	अगर (!IS_ERR(rt)) अणु
		__ip_rt_update_pmtu(rt, &fl4, mtu);
		ip_rt_put(rt);
	पूर्ण
पूर्ण

व्योम ipv4_sk_update_pmtu(काष्ठा sk_buff *skb, काष्ठा sock *sk, u32 mtu)
अणु
	स्थिर काष्ठा iphdr *iph = (स्थिर काष्ठा iphdr *)skb->data;
	काष्ठा flowi4 fl4;
	काष्ठा rtable *rt;
	काष्ठा dst_entry *odst = शून्य;
	bool new = false;
	काष्ठा net *net = sock_net(sk);

	bh_lock_sock(sk);

	अगर (!ip_sk_accept_pmtu(sk))
		जाओ out;

	odst = sk_dst_get(sk);

	अगर (sock_owned_by_user(sk) || !odst) अणु
		__ipv4_sk_update_pmtu(skb, sk, mtu);
		जाओ out;
	पूर्ण

	__build_flow_key(net, &fl4, sk, iph, 0, 0, 0, 0, 0);

	rt = (काष्ठा rtable *)odst;
	अगर (odst->obsolete && !odst->ops->check(odst, 0)) अणु
		rt = ip_route_output_flow(sock_net(sk), &fl4, sk);
		अगर (IS_ERR(rt))
			जाओ out;

		new = true;
	पूर्ण

	__ip_rt_update_pmtu((काष्ठा rtable *)xfrm_dst_path(&rt->dst), &fl4, mtu);

	अगर (!dst_check(&rt->dst, 0)) अणु
		अगर (new)
			dst_release(&rt->dst);

		rt = ip_route_output_flow(sock_net(sk), &fl4, sk);
		अगर (IS_ERR(rt))
			जाओ out;

		new = true;
	पूर्ण

	अगर (new)
		sk_dst_set(sk, &rt->dst);

out:
	bh_unlock_sock(sk);
	dst_release(odst);
पूर्ण
EXPORT_SYMBOL_GPL(ipv4_sk_update_pmtu);

व्योम ipv4_redirect(काष्ठा sk_buff *skb, काष्ठा net *net,
		   पूर्णांक oअगर, u8 protocol)
अणु
	स्थिर काष्ठा iphdr *iph = (स्थिर काष्ठा iphdr *)skb->data;
	काष्ठा flowi4 fl4;
	काष्ठा rtable *rt;

	__build_flow_key(net, &fl4, शून्य, iph, oअगर,
			 RT_TOS(iph->tos), protocol, 0, 0);
	rt = __ip_route_output_key(net, &fl4);
	अगर (!IS_ERR(rt)) अणु
		__ip_करो_redirect(rt, skb, &fl4, false);
		ip_rt_put(rt);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ipv4_redirect);

व्योम ipv4_sk_redirect(काष्ठा sk_buff *skb, काष्ठा sock *sk)
अणु
	स्थिर काष्ठा iphdr *iph = (स्थिर काष्ठा iphdr *)skb->data;
	काष्ठा flowi4 fl4;
	काष्ठा rtable *rt;
	काष्ठा net *net = sock_net(sk);

	__build_flow_key(net, &fl4, sk, iph, 0, 0, 0, 0, 0);
	rt = __ip_route_output_key(net, &fl4);
	अगर (!IS_ERR(rt)) अणु
		__ip_करो_redirect(rt, skb, &fl4, false);
		ip_rt_put(rt);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ipv4_sk_redirect);

INसूचीECT_CALLABLE_SCOPE काष्ठा dst_entry *ipv4_dst_check(काष्ठा dst_entry *dst,
							 u32 cookie)
अणु
	काष्ठा rtable *rt = (काष्ठा rtable *) dst;

	/* All IPV4 dsts are created with ->obsolete set to the value
	 * DST_OBSOLETE_FORCE_CHK which क्रमces validation calls करोwn
	 * पूर्णांकo this function always.
	 *
	 * When a PMTU/redirect inक्रमmation update invalidates a route,
	 * this is indicated by setting obsolete to DST_OBSOLETE_KILL or
	 * DST_OBSOLETE_DEAD.
	 */
	अगर (dst->obsolete != DST_OBSOLETE_FORCE_CHK || rt_is_expired(rt))
		वापस शून्य;
	वापस dst;
पूर्ण
EXPORT_INसूचीECT_CALLABLE(ipv4_dst_check);

अटल व्योम ipv4_send_dest_unreach(काष्ठा sk_buff *skb)
अणु
	काष्ठा ip_options opt;
	पूर्णांक res;

	/* Recompile ip options since IPCB may not be valid anymore.
	 * Also check we have a reasonable ipv4 header.
	 */
	अगर (!pskb_network_may_pull(skb, माप(काष्ठा iphdr)) ||
	    ip_hdr(skb)->version != 4 || ip_hdr(skb)->ihl < 5)
		वापस;

	स_रखो(&opt, 0, माप(opt));
	अगर (ip_hdr(skb)->ihl > 5) अणु
		अगर (!pskb_network_may_pull(skb, ip_hdr(skb)->ihl * 4))
			वापस;
		opt.optlen = ip_hdr(skb)->ihl * 4 - माप(काष्ठा iphdr);

		rcu_पढ़ो_lock();
		res = __ip_options_compile(dev_net(skb->dev), &opt, skb, शून्य);
		rcu_पढ़ो_unlock();

		अगर (res)
			वापस;
	पूर्ण
	__icmp_send(skb, ICMP_DEST_UNREACH, ICMP_HOST_UNREACH, 0, &opt);
पूर्ण

अटल व्योम ipv4_link_failure(काष्ठा sk_buff *skb)
अणु
	काष्ठा rtable *rt;

	ipv4_send_dest_unreach(skb);

	rt = skb_rtable(skb);
	अगर (rt)
		dst_set_expires(&rt->dst, 0);
पूर्ण

अटल पूर्णांक ip_rt_bug(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	pr_debug("%s: %pI4 -> %pI4, %s\n",
		 __func__, &ip_hdr(skb)->saddr, &ip_hdr(skb)->daddr,
		 skb->dev ? skb->dev->name : "?");
	kमुक्त_skb(skb);
	WARN_ON(1);
	वापस 0;
पूर्ण

/*
 * We करो not cache source address of outgoing पूर्णांकerface,
 * because it is used only by IP RR, TS and SRR options,
 * so that it out of fast path.
 *
 * BTW remember: "addr" is allowed to be not aligned
 * in IP options!
 */

व्योम ip_rt_get_source(u8 *addr, काष्ठा sk_buff *skb, काष्ठा rtable *rt)
अणु
	__be32 src;

	अगर (rt_is_output_route(rt))
		src = ip_hdr(skb)->saddr;
	अन्यथा अणु
		काष्ठा fib_result res;
		काष्ठा iphdr *iph = ip_hdr(skb);
		काष्ठा flowi4 fl4 = अणु
			.daddr = iph->daddr,
			.saddr = iph->saddr,
			.flowi4_tos = RT_TOS(iph->tos),
			.flowi4_oअगर = rt->dst.dev->अगरindex,
			.flowi4_iअगर = skb->dev->अगरindex,
			.flowi4_mark = skb->mark,
		पूर्ण;

		rcu_पढ़ो_lock();
		अगर (fib_lookup(dev_net(rt->dst.dev), &fl4, &res, 0) == 0)
			src = fib_result_prefsrc(dev_net(rt->dst.dev), &res);
		अन्यथा
			src = inet_select_addr(rt->dst.dev,
					       rt_nexthop(rt, iph->daddr),
					       RT_SCOPE_UNIVERSE);
		rcu_पढ़ो_unlock();
	पूर्ण
	स_नकल(addr, &src, 4);
पूर्ण

#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
अटल व्योम set_class_tag(काष्ठा rtable *rt, u32 tag)
अणु
	अगर (!(rt->dst.tclassid & 0xFFFF))
		rt->dst.tclassid |= tag & 0xFFFF;
	अगर (!(rt->dst.tclassid & 0xFFFF0000))
		rt->dst.tclassid |= tag & 0xFFFF0000;
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक ipv4_शेष_advmss(स्थिर काष्ठा dst_entry *dst)
अणु
	अचिन्हित पूर्णांक header_size = माप(काष्ठा tcphdr) + माप(काष्ठा iphdr);
	अचिन्हित पूर्णांक advmss = max_t(अचिन्हित पूर्णांक, ipv4_mtu(dst) - header_size,
				    ip_rt_min_advmss);

	वापस min(advmss, IPV4_MAX_PMTU - header_size);
पूर्ण

INसूचीECT_CALLABLE_SCOPE अचिन्हित पूर्णांक ipv4_mtu(स्थिर काष्ठा dst_entry *dst)
अणु
	स्थिर काष्ठा rtable *rt = (स्थिर काष्ठा rtable *)dst;
	अचिन्हित पूर्णांक mtu = rt->rt_pmtu;

	अगर (!mtu || समय_after_eq(jअगरfies, rt->dst.expires))
		mtu = dst_metric_raw(dst, RTAX_MTU);

	अगर (mtu)
		वापस mtu;

	mtu = READ_ONCE(dst->dev->mtu);

	अगर (unlikely(ip_mtu_locked(dst))) अणु
		अगर (rt->rt_uses_gateway && mtu > 576)
			mtu = 576;
	पूर्ण

	mtu = min_t(अचिन्हित पूर्णांक, mtu, IP_MAX_MTU);

	वापस mtu - lwtunnel_headroom(dst->lwtstate, mtu);
पूर्ण
EXPORT_INसूचीECT_CALLABLE(ipv4_mtu);

अटल व्योम ip_del_fnhe(काष्ठा fib_nh_common *nhc, __be32 daddr)
अणु
	काष्ठा fnhe_hash_bucket *hash;
	काष्ठा fib_nh_exception *fnhe, __rcu **fnhe_p;
	u32 hval = fnhe_hashfun(daddr);

	spin_lock_bh(&fnhe_lock);

	hash = rcu_dereference_रक्षित(nhc->nhc_exceptions,
					 lockdep_is_held(&fnhe_lock));
	hash += hval;

	fnhe_p = &hash->chain;
	fnhe = rcu_dereference_रक्षित(*fnhe_p, lockdep_is_held(&fnhe_lock));
	जबतक (fnhe) अणु
		अगर (fnhe->fnhe_daddr == daddr) अणु
			rcu_assign_poपूर्णांकer(*fnhe_p, rcu_dereference_रक्षित(
				fnhe->fnhe_next, lockdep_is_held(&fnhe_lock)));
			/* set fnhe_daddr to 0 to ensure it won't bind with
			 * new dsts in rt_bind_exception().
			 */
			fnhe->fnhe_daddr = 0;
			fnhe_flush_routes(fnhe);
			kमुक्त_rcu(fnhe, rcu);
			अवरोध;
		पूर्ण
		fnhe_p = &fnhe->fnhe_next;
		fnhe = rcu_dereference_रक्षित(fnhe->fnhe_next,
						 lockdep_is_held(&fnhe_lock));
	पूर्ण

	spin_unlock_bh(&fnhe_lock);
पूर्ण

अटल काष्ठा fib_nh_exception *find_exception(काष्ठा fib_nh_common *nhc,
					       __be32 daddr)
अणु
	काष्ठा fnhe_hash_bucket *hash = rcu_dereference(nhc->nhc_exceptions);
	काष्ठा fib_nh_exception *fnhe;
	u32 hval;

	अगर (!hash)
		वापस शून्य;

	hval = fnhe_hashfun(daddr);

	क्रम (fnhe = rcu_dereference(hash[hval].chain); fnhe;
	     fnhe = rcu_dereference(fnhe->fnhe_next)) अणु
		अगर (fnhe->fnhe_daddr == daddr) अणु
			अगर (fnhe->fnhe_expires &&
			    समय_after(jअगरfies, fnhe->fnhe_expires)) अणु
				ip_del_fnhe(nhc, daddr);
				अवरोध;
			पूर्ण
			वापस fnhe;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/* MTU selection:
 * 1. mtu on route is locked - use it
 * 2. mtu from nexthop exception
 * 3. mtu from egress device
 */

u32 ip_mtu_from_fib_result(काष्ठा fib_result *res, __be32 daddr)
अणु
	काष्ठा fib_nh_common *nhc = res->nhc;
	काष्ठा net_device *dev = nhc->nhc_dev;
	काष्ठा fib_info *fi = res->fi;
	u32 mtu = 0;

	अगर (dev_net(dev)->ipv4.sysctl_ip_fwd_use_pmtu ||
	    fi->fib_metrics->metrics[RTAX_LOCK - 1] & (1 << RTAX_MTU))
		mtu = fi->fib_mtu;

	अगर (likely(!mtu)) अणु
		काष्ठा fib_nh_exception *fnhe;

		fnhe = find_exception(nhc, daddr);
		अगर (fnhe && !समय_after_eq(jअगरfies, fnhe->fnhe_expires))
			mtu = fnhe->fnhe_pmtu;
	पूर्ण

	अगर (likely(!mtu))
		mtu = min(READ_ONCE(dev->mtu), IP_MAX_MTU);

	वापस mtu - lwtunnel_headroom(nhc->nhc_lwtstate, mtu);
पूर्ण

अटल bool rt_bind_exception(काष्ठा rtable *rt, काष्ठा fib_nh_exception *fnhe,
			      __be32 daddr, स्थिर bool करो_cache)
अणु
	bool ret = false;

	spin_lock_bh(&fnhe_lock);

	अगर (daddr == fnhe->fnhe_daddr) अणु
		काष्ठा rtable __rcu **porig;
		काष्ठा rtable *orig;
		पूर्णांक genid = fnhe_genid(dev_net(rt->dst.dev));

		अगर (rt_is_input_route(rt))
			porig = &fnhe->fnhe_rth_input;
		अन्यथा
			porig = &fnhe->fnhe_rth_output;
		orig = rcu_dereference(*porig);

		अगर (fnhe->fnhe_genid != genid) अणु
			fnhe->fnhe_genid = genid;
			fnhe->fnhe_gw = 0;
			fnhe->fnhe_pmtu = 0;
			fnhe->fnhe_expires = 0;
			fnhe->fnhe_mtu_locked = false;
			fnhe_flush_routes(fnhe);
			orig = शून्य;
		पूर्ण
		fill_route_from_fnhe(rt, fnhe);
		अगर (!rt->rt_gw4) अणु
			rt->rt_gw4 = daddr;
			rt->rt_gw_family = AF_INET;
		पूर्ण

		अगर (करो_cache) अणु
			dst_hold(&rt->dst);
			rcu_assign_poपूर्णांकer(*porig, rt);
			अगर (orig) अणु
				dst_dev_put(&orig->dst);
				dst_release(&orig->dst);
			पूर्ण
			ret = true;
		पूर्ण

		fnhe->fnhe_stamp = jअगरfies;
	पूर्ण
	spin_unlock_bh(&fnhe_lock);

	वापस ret;
पूर्ण

अटल bool rt_cache_route(काष्ठा fib_nh_common *nhc, काष्ठा rtable *rt)
अणु
	काष्ठा rtable *orig, *prev, **p;
	bool ret = true;

	अगर (rt_is_input_route(rt)) अणु
		p = (काष्ठा rtable **)&nhc->nhc_rth_input;
	पूर्ण अन्यथा अणु
		p = (काष्ठा rtable **)raw_cpu_ptr(nhc->nhc_pcpu_rth_output);
	पूर्ण
	orig = *p;

	/* hold dst beक्रमe करोing cmpxchg() to aव्योम race condition
	 * on this dst
	 */
	dst_hold(&rt->dst);
	prev = cmpxchg(p, orig, rt);
	अगर (prev == orig) अणु
		अगर (orig) अणु
			rt_add_uncached_list(orig);
			dst_release(&orig->dst);
		पूर्ण
	पूर्ण अन्यथा अणु
		dst_release(&rt->dst);
		ret = false;
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा uncached_list अणु
	spinlock_t		lock;
	काष्ठा list_head	head;
पूर्ण;

अटल DEFINE_PER_CPU_ALIGNED(काष्ठा uncached_list, rt_uncached_list);

व्योम rt_add_uncached_list(काष्ठा rtable *rt)
अणु
	काष्ठा uncached_list *ul = raw_cpu_ptr(&rt_uncached_list);

	rt->rt_uncached_list = ul;

	spin_lock_bh(&ul->lock);
	list_add_tail(&rt->rt_uncached, &ul->head);
	spin_unlock_bh(&ul->lock);
पूर्ण

व्योम rt_del_uncached_list(काष्ठा rtable *rt)
अणु
	अगर (!list_empty(&rt->rt_uncached)) अणु
		काष्ठा uncached_list *ul = rt->rt_uncached_list;

		spin_lock_bh(&ul->lock);
		list_del(&rt->rt_uncached);
		spin_unlock_bh(&ul->lock);
	पूर्ण
पूर्ण

अटल व्योम ipv4_dst_destroy(काष्ठा dst_entry *dst)
अणु
	काष्ठा rtable *rt = (काष्ठा rtable *)dst;

	ip_dst_metrics_put(dst);
	rt_del_uncached_list(rt);
पूर्ण

व्योम rt_flush_dev(काष्ठा net_device *dev)
अणु
	काष्ठा rtable *rt;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा uncached_list *ul = &per_cpu(rt_uncached_list, cpu);

		spin_lock_bh(&ul->lock);
		list_क्रम_each_entry(rt, &ul->head, rt_uncached) अणु
			अगर (rt->dst.dev != dev)
				जारी;
			rt->dst.dev = blackhole_netdev;
			dev_hold(rt->dst.dev);
			dev_put(dev);
		पूर्ण
		spin_unlock_bh(&ul->lock);
	पूर्ण
पूर्ण

अटल bool rt_cache_valid(स्थिर काष्ठा rtable *rt)
अणु
	वापस	rt &&
		rt->dst.obsolete == DST_OBSOLETE_FORCE_CHK &&
		!rt_is_expired(rt);
पूर्ण

अटल व्योम rt_set_nexthop(काष्ठा rtable *rt, __be32 daddr,
			   स्थिर काष्ठा fib_result *res,
			   काष्ठा fib_nh_exception *fnhe,
			   काष्ठा fib_info *fi, u16 type, u32 itag,
			   स्थिर bool करो_cache)
अणु
	bool cached = false;

	अगर (fi) अणु
		काष्ठा fib_nh_common *nhc = FIB_RES_NHC(*res);

		अगर (nhc->nhc_gw_family && nhc->nhc_scope == RT_SCOPE_LINK) अणु
			rt->rt_uses_gateway = 1;
			rt->rt_gw_family = nhc->nhc_gw_family;
			/* only INET and INET6 are supported */
			अगर (likely(nhc->nhc_gw_family == AF_INET))
				rt->rt_gw4 = nhc->nhc_gw.ipv4;
			अन्यथा
				rt->rt_gw6 = nhc->nhc_gw.ipv6;
		पूर्ण

		ip_dst_init_metrics(&rt->dst, fi->fib_metrics);

#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
		अगर (nhc->nhc_family == AF_INET) अणु
			काष्ठा fib_nh *nh;

			nh = container_of(nhc, काष्ठा fib_nh, nh_common);
			rt->dst.tclassid = nh->nh_tclassid;
		पूर्ण
#पूर्ण_अगर
		rt->dst.lwtstate = lwtstate_get(nhc->nhc_lwtstate);
		अगर (unlikely(fnhe))
			cached = rt_bind_exception(rt, fnhe, daddr, करो_cache);
		अन्यथा अगर (करो_cache)
			cached = rt_cache_route(nhc, rt);
		अगर (unlikely(!cached)) अणु
			/* Routes we पूर्णांकend to cache in nexthop exception or
			 * FIB nexthop have the DST_NOCACHE bit clear.
			 * However, अगर we are unsuccessful at storing this
			 * route पूर्णांकo the cache we really need to set it.
			 */
			अगर (!rt->rt_gw4) अणु
				rt->rt_gw_family = AF_INET;
				rt->rt_gw4 = daddr;
			पूर्ण
			rt_add_uncached_list(rt);
		पूर्ण
	पूर्ण अन्यथा
		rt_add_uncached_list(rt);

#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
#अगर_घोषित CONFIG_IP_MULTIPLE_TABLES
	set_class_tag(rt, res->tclassid);
#पूर्ण_अगर
	set_class_tag(rt, itag);
#पूर्ण_अगर
पूर्ण

काष्ठा rtable *rt_dst_alloc(काष्ठा net_device *dev,
			    अचिन्हित पूर्णांक flags, u16 type,
			    bool nopolicy, bool noxfrm)
अणु
	काष्ठा rtable *rt;

	rt = dst_alloc(&ipv4_dst_ops, dev, 1, DST_OBSOLETE_FORCE_CHK,
		       (nopolicy ? DST_NOPOLICY : 0) |
		       (noxfrm ? DST_NOXFRM : 0));

	अगर (rt) अणु
		rt->rt_genid = rt_genid_ipv4(dev_net(dev));
		rt->rt_flags = flags;
		rt->rt_type = type;
		rt->rt_is_input = 0;
		rt->rt_iअगर = 0;
		rt->rt_pmtu = 0;
		rt->rt_mtu_locked = 0;
		rt->rt_uses_gateway = 0;
		rt->rt_gw_family = 0;
		rt->rt_gw4 = 0;
		INIT_LIST_HEAD(&rt->rt_uncached);

		rt->dst.output = ip_output;
		अगर (flags & RTCF_LOCAL)
			rt->dst.input = ip_local_deliver;
	पूर्ण

	वापस rt;
पूर्ण
EXPORT_SYMBOL(rt_dst_alloc);

काष्ठा rtable *rt_dst_clone(काष्ठा net_device *dev, काष्ठा rtable *rt)
अणु
	काष्ठा rtable *new_rt;

	new_rt = dst_alloc(&ipv4_dst_ops, dev, 1, DST_OBSOLETE_FORCE_CHK,
			   rt->dst.flags);

	अगर (new_rt) अणु
		new_rt->rt_genid = rt_genid_ipv4(dev_net(dev));
		new_rt->rt_flags = rt->rt_flags;
		new_rt->rt_type = rt->rt_type;
		new_rt->rt_is_input = rt->rt_is_input;
		new_rt->rt_iअगर = rt->rt_iअगर;
		new_rt->rt_pmtu = rt->rt_pmtu;
		new_rt->rt_mtu_locked = rt->rt_mtu_locked;
		new_rt->rt_gw_family = rt->rt_gw_family;
		अगर (rt->rt_gw_family == AF_INET)
			new_rt->rt_gw4 = rt->rt_gw4;
		अन्यथा अगर (rt->rt_gw_family == AF_INET6)
			new_rt->rt_gw6 = rt->rt_gw6;
		INIT_LIST_HEAD(&new_rt->rt_uncached);

		new_rt->dst.input = rt->dst.input;
		new_rt->dst.output = rt->dst.output;
		new_rt->dst.error = rt->dst.error;
		new_rt->dst.lastuse = jअगरfies;
		new_rt->dst.lwtstate = lwtstate_get(rt->dst.lwtstate);
	पूर्ण
	वापस new_rt;
पूर्ण
EXPORT_SYMBOL(rt_dst_clone);

/* called in rcu_पढ़ो_lock() section */
पूर्णांक ip_mc_validate_source(काष्ठा sk_buff *skb, __be32 daddr, __be32 saddr,
			  u8 tos, काष्ठा net_device *dev,
			  काष्ठा in_device *in_dev, u32 *itag)
अणु
	पूर्णांक err;

	/* Primary sanity checks. */
	अगर (!in_dev)
		वापस -EINVAL;

	अगर (ipv4_is_multicast(saddr) || ipv4_is_lbcast(saddr) ||
	    skb->protocol != htons(ETH_P_IP))
		वापस -EINVAL;

	अगर (ipv4_is_loopback(saddr) && !IN_DEV_ROUTE_LOCALNET(in_dev))
		वापस -EINVAL;

	अगर (ipv4_is_zeronet(saddr)) अणु
		अगर (!ipv4_is_local_multicast(daddr) &&
		    ip_hdr(skb)->protocol != IPPROTO_IGMP)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		err = fib_validate_source(skb, saddr, 0, tos, 0, dev,
					  in_dev, itag);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/* called in rcu_पढ़ो_lock() section */
अटल पूर्णांक ip_route_input_mc(काष्ठा sk_buff *skb, __be32 daddr, __be32 saddr,
			     u8 tos, काष्ठा net_device *dev, पूर्णांक our)
अणु
	काष्ठा in_device *in_dev = __in_dev_get_rcu(dev);
	अचिन्हित पूर्णांक flags = RTCF_MULTICAST;
	काष्ठा rtable *rth;
	u32 itag = 0;
	पूर्णांक err;

	err = ip_mc_validate_source(skb, daddr, saddr, tos, dev, in_dev, &itag);
	अगर (err)
		वापस err;

	अगर (our)
		flags |= RTCF_LOCAL;

	rth = rt_dst_alloc(dev_net(dev)->loopback_dev, flags, RTN_MULTICAST,
			   IN_DEV_ORCONF(in_dev, NOPOLICY), false);
	अगर (!rth)
		वापस -ENOBUFS;

#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	rth->dst.tclassid = itag;
#पूर्ण_अगर
	rth->dst.output = ip_rt_bug;
	rth->rt_is_input= 1;

#अगर_घोषित CONFIG_IP_MROUTE
	अगर (!ipv4_is_local_multicast(daddr) && IN_DEV_MFORWARD(in_dev))
		rth->dst.input = ip_mr_input;
#पूर्ण_अगर
	RT_CACHE_STAT_INC(in_slow_mc);

	skb_dst_set(skb, &rth->dst);
	वापस 0;
पूर्ण


अटल व्योम ip_handle_martian_source(काष्ठा net_device *dev,
				     काष्ठा in_device *in_dev,
				     काष्ठा sk_buff *skb,
				     __be32 daddr,
				     __be32 saddr)
अणु
	RT_CACHE_STAT_INC(in_martian_src);
#अगर_घोषित CONFIG_IP_ROUTE_VERBOSE
	अगर (IN_DEV_LOG_MARTIANS(in_dev) && net_ratelimit()) अणु
		/*
		 *	RFC1812 recommendation, अगर source is martian,
		 *	the only hपूर्णांक is MAC header.
		 */
		pr_warn("martian source %pI4 from %pI4, on dev %s\n",
			&daddr, &saddr, dev->name);
		अगर (dev->hard_header_len && skb_mac_header_was_set(skb)) अणु
			prपूर्णांक_hex_dump(KERN_WARNING, "ll header: ",
				       DUMP_PREFIX_OFFSET, 16, 1,
				       skb_mac_header(skb),
				       dev->hard_header_len, false);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

/* called in rcu_पढ़ो_lock() section */
अटल पूर्णांक __mkroute_input(काष्ठा sk_buff *skb,
			   स्थिर काष्ठा fib_result *res,
			   काष्ठा in_device *in_dev,
			   __be32 daddr, __be32 saddr, u32 tos)
अणु
	काष्ठा fib_nh_common *nhc = FIB_RES_NHC(*res);
	काष्ठा net_device *dev = nhc->nhc_dev;
	काष्ठा fib_nh_exception *fnhe;
	काष्ठा rtable *rth;
	पूर्णांक err;
	काष्ठा in_device *out_dev;
	bool करो_cache;
	u32 itag = 0;

	/* get a working reference to the output device */
	out_dev = __in_dev_get_rcu(dev);
	अगर (!out_dev) अणु
		net_crit_ratelimited("Bug in ip_route_input_slow(). Please report.\n");
		वापस -EINVAL;
	पूर्ण

	err = fib_validate_source(skb, saddr, daddr, tos, FIB_RES_OIF(*res),
				  in_dev->dev, in_dev, &itag);
	अगर (err < 0) अणु
		ip_handle_martian_source(in_dev->dev, in_dev, skb, daddr,
					 saddr);

		जाओ cleanup;
	पूर्ण

	करो_cache = res->fi && !itag;
	अगर (out_dev == in_dev && err && IN_DEV_TX_REसूचीECTS(out_dev) &&
	    skb->protocol == htons(ETH_P_IP)) अणु
		__be32 gw;

		gw = nhc->nhc_gw_family == AF_INET ? nhc->nhc_gw.ipv4 : 0;
		अगर (IN_DEV_SHARED_MEDIA(out_dev) ||
		    inet_addr_onlink(out_dev, saddr, gw))
			IPCB(skb)->flags |= IPSKB_DOREसूचीECT;
	पूर्ण

	अगर (skb->protocol != htons(ETH_P_IP)) अणु
		/* Not IP (i.e. ARP). Do not create route, अगर it is
		 * invalid क्रम proxy arp. DNAT routes are always valid.
		 *
		 * Proxy arp feature have been extended to allow, ARP
		 * replies back to the same पूर्णांकerface, to support
		 * Private VLAN चयन technologies. See arp.c.
		 */
		अगर (out_dev == in_dev &&
		    IN_DEV_PROXY_ARP_PVLAN(in_dev) == 0) अणु
			err = -EINVAL;
			जाओ cleanup;
		पूर्ण
	पूर्ण

	fnhe = find_exception(nhc, daddr);
	अगर (करो_cache) अणु
		अगर (fnhe)
			rth = rcu_dereference(fnhe->fnhe_rth_input);
		अन्यथा
			rth = rcu_dereference(nhc->nhc_rth_input);
		अगर (rt_cache_valid(rth)) अणु
			skb_dst_set_noref(skb, &rth->dst);
			जाओ out;
		पूर्ण
	पूर्ण

	rth = rt_dst_alloc(out_dev->dev, 0, res->type,
			   IN_DEV_ORCONF(in_dev, NOPOLICY),
			   IN_DEV_ORCONF(out_dev, NOXFRM));
	अगर (!rth) अणु
		err = -ENOBUFS;
		जाओ cleanup;
	पूर्ण

	rth->rt_is_input = 1;
	RT_CACHE_STAT_INC(in_slow_tot);

	rth->dst.input = ip_क्रमward;

	rt_set_nexthop(rth, daddr, res, fnhe, res->fi, res->type, itag,
		       करो_cache);
	lwtunnel_set_redirect(&rth->dst);
	skb_dst_set(skb, &rth->dst);
out:
	err = 0;
 cleanup:
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH
/* To make ICMP packets follow the right flow, the multipath hash is
 * calculated from the inner IP addresses.
 */
अटल व्योम ip_multipath_l3_keys(स्थिर काष्ठा sk_buff *skb,
				 काष्ठा flow_keys *hash_keys)
अणु
	स्थिर काष्ठा iphdr *outer_iph = ip_hdr(skb);
	स्थिर काष्ठा iphdr *key_iph = outer_iph;
	स्थिर काष्ठा iphdr *inner_iph;
	स्थिर काष्ठा icmphdr *icmph;
	काष्ठा iphdr _inner_iph;
	काष्ठा icmphdr _icmph;

	अगर (likely(outer_iph->protocol != IPPROTO_ICMP))
		जाओ out;

	अगर (unlikely((outer_iph->frag_off & htons(IP_OFFSET)) != 0))
		जाओ out;

	icmph = skb_header_poपूर्णांकer(skb, outer_iph->ihl * 4, माप(_icmph),
				   &_icmph);
	अगर (!icmph)
		जाओ out;

	अगर (!icmp_is_err(icmph->type))
		जाओ out;

	inner_iph = skb_header_poपूर्णांकer(skb,
				       outer_iph->ihl * 4 + माप(_icmph),
				       माप(_inner_iph), &_inner_iph);
	अगर (!inner_iph)
		जाओ out;

	key_iph = inner_iph;
out:
	hash_keys->addrs.v4addrs.src = key_iph->saddr;
	hash_keys->addrs.v4addrs.dst = key_iph->daddr;
पूर्ण

/* अगर skb is set it will be used and fl4 can be शून्य */
पूर्णांक fib_multipath_hash(स्थिर काष्ठा net *net, स्थिर काष्ठा flowi4 *fl4,
		       स्थिर काष्ठा sk_buff *skb, काष्ठा flow_keys *flkeys)
अणु
	u32 multipath_hash = fl4 ? fl4->flowi4_multipath_hash : 0;
	काष्ठा flow_keys hash_keys;
	u32 mhash;

	चयन (net->ipv4.sysctl_fib_multipath_hash_policy) अणु
	हाल 0:
		स_रखो(&hash_keys, 0, माप(hash_keys));
		hash_keys.control.addr_type = FLOW_DISSECTOR_KEY_IPV4_ADDRS;
		अगर (skb) अणु
			ip_multipath_l3_keys(skb, &hash_keys);
		पूर्ण अन्यथा अणु
			hash_keys.addrs.v4addrs.src = fl4->saddr;
			hash_keys.addrs.v4addrs.dst = fl4->daddr;
		पूर्ण
		अवरोध;
	हाल 1:
		/* skb is currently provided only when क्रमwarding */
		अगर (skb) अणु
			अचिन्हित पूर्णांक flag = FLOW_DISSECTOR_F_STOP_AT_ENCAP;
			काष्ठा flow_keys keys;

			/* लघु-circuit अगर we alपढ़ोy have L4 hash present */
			अगर (skb->l4_hash)
				वापस skb_get_hash_raw(skb) >> 1;

			स_रखो(&hash_keys, 0, माप(hash_keys));

			अगर (!flkeys) अणु
				skb_flow_dissect_flow_keys(skb, &keys, flag);
				flkeys = &keys;
			पूर्ण

			hash_keys.control.addr_type = FLOW_DISSECTOR_KEY_IPV4_ADDRS;
			hash_keys.addrs.v4addrs.src = flkeys->addrs.v4addrs.src;
			hash_keys.addrs.v4addrs.dst = flkeys->addrs.v4addrs.dst;
			hash_keys.ports.src = flkeys->ports.src;
			hash_keys.ports.dst = flkeys->ports.dst;
			hash_keys.basic.ip_proto = flkeys->basic.ip_proto;
		पूर्ण अन्यथा अणु
			स_रखो(&hash_keys, 0, माप(hash_keys));
			hash_keys.control.addr_type = FLOW_DISSECTOR_KEY_IPV4_ADDRS;
			hash_keys.addrs.v4addrs.src = fl4->saddr;
			hash_keys.addrs.v4addrs.dst = fl4->daddr;
			hash_keys.ports.src = fl4->fl4_sport;
			hash_keys.ports.dst = fl4->fl4_dport;
			hash_keys.basic.ip_proto = fl4->flowi4_proto;
		पूर्ण
		अवरोध;
	हाल 2:
		स_रखो(&hash_keys, 0, माप(hash_keys));
		/* skb is currently provided only when क्रमwarding */
		अगर (skb) अणु
			काष्ठा flow_keys keys;

			skb_flow_dissect_flow_keys(skb, &keys, 0);
			/* Inner can be v4 or v6 */
			अगर (keys.control.addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS) अणु
				hash_keys.control.addr_type = FLOW_DISSECTOR_KEY_IPV4_ADDRS;
				hash_keys.addrs.v4addrs.src = keys.addrs.v4addrs.src;
				hash_keys.addrs.v4addrs.dst = keys.addrs.v4addrs.dst;
			पूर्ण अन्यथा अगर (keys.control.addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS) अणु
				hash_keys.control.addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
				hash_keys.addrs.v6addrs.src = keys.addrs.v6addrs.src;
				hash_keys.addrs.v6addrs.dst = keys.addrs.v6addrs.dst;
				hash_keys.tags.flow_label = keys.tags.flow_label;
				hash_keys.basic.ip_proto = keys.basic.ip_proto;
			पूर्ण अन्यथा अणु
				/* Same as हाल 0 */
				hash_keys.control.addr_type = FLOW_DISSECTOR_KEY_IPV4_ADDRS;
				ip_multipath_l3_keys(skb, &hash_keys);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Same as हाल 0 */
			hash_keys.control.addr_type = FLOW_DISSECTOR_KEY_IPV4_ADDRS;
			hash_keys.addrs.v4addrs.src = fl4->saddr;
			hash_keys.addrs.v4addrs.dst = fl4->daddr;
		पूर्ण
		अवरोध;
	पूर्ण
	mhash = flow_hash_from_keys(&hash_keys);

	अगर (multipath_hash)
		mhash = jhash_2words(mhash, multipath_hash, 0);

	वापस mhash >> 1;
पूर्ण
#पूर्ण_अगर /* CONFIG_IP_ROUTE_MULTIPATH */

अटल पूर्णांक ip_mkroute_input(काष्ठा sk_buff *skb,
			    काष्ठा fib_result *res,
			    काष्ठा in_device *in_dev,
			    __be32 daddr, __be32 saddr, u32 tos,
			    काष्ठा flow_keys *hkeys)
अणु
#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH
	अगर (res->fi && fib_info_num_path(res->fi) > 1) अणु
		पूर्णांक h = fib_multipath_hash(res->fi->fib_net, शून्य, skb, hkeys);

		fib_select_multipath(res, h);
	पूर्ण
#पूर्ण_अगर

	/* create a routing cache entry */
	वापस __mkroute_input(skb, res, in_dev, daddr, saddr, tos);
पूर्ण

/* Implements all the saddr-related checks as ip_route_input_slow(),
 * assuming daddr is valid and the destination is not a local broadcast one.
 * Uses the provided hपूर्णांक instead of perक्रमming a route lookup.
 */
पूर्णांक ip_route_use_hपूर्णांक(काष्ठा sk_buff *skb, __be32 daddr, __be32 saddr,
		      u8 tos, काष्ठा net_device *dev,
		      स्थिर काष्ठा sk_buff *hपूर्णांक)
अणु
	काष्ठा in_device *in_dev = __in_dev_get_rcu(dev);
	काष्ठा rtable *rt = skb_rtable(hपूर्णांक);
	काष्ठा net *net = dev_net(dev);
	पूर्णांक err = -EINVAL;
	u32 tag = 0;

	अगर (ipv4_is_multicast(saddr) || ipv4_is_lbcast(saddr))
		जाओ martian_source;

	अगर (ipv4_is_zeronet(saddr))
		जाओ martian_source;

	अगर (ipv4_is_loopback(saddr) && !IN_DEV_NET_ROUTE_LOCALNET(in_dev, net))
		जाओ martian_source;

	अगर (rt->rt_type != RTN_LOCAL)
		जाओ skip_validate_source;

	tos &= IPTOS_RT_MASK;
	err = fib_validate_source(skb, saddr, daddr, tos, 0, dev, in_dev, &tag);
	अगर (err < 0)
		जाओ martian_source;

skip_validate_source:
	skb_dst_copy(skb, hपूर्णांक);
	वापस 0;

martian_source:
	ip_handle_martian_source(dev, in_dev, skb, daddr, saddr);
	वापस err;
पूर्ण

/* get device क्रम dst_alloc with local routes */
अटल काष्ठा net_device *ip_rt_get_dev(काष्ठा net *net,
					स्थिर काष्ठा fib_result *res)
अणु
	काष्ठा fib_nh_common *nhc = res->fi ? res->nhc : शून्य;
	काष्ठा net_device *dev = शून्य;

	अगर (nhc)
		dev = l3mdev_master_dev_rcu(nhc->nhc_dev);

	वापस dev ? : net->loopback_dev;
पूर्ण

/*
 *	NOTE. We drop all the packets that has local source
 *	addresses, because every properly looped back packet
 *	must have correct destination alपढ़ोy attached by output routine.
 *	Changes in the enक्रमced policies must be applied also to
 *	ip_route_use_hपूर्णांक().
 *
 *	Such approach solves two big problems:
 *	1. Not simplex devices are handled properly.
 *	2. IP spoofing attempts are filtered with 100% of guarantee.
 *	called with rcu_पढ़ो_lock()
 */

अटल पूर्णांक ip_route_input_slow(काष्ठा sk_buff *skb, __be32 daddr, __be32 saddr,
			       u8 tos, काष्ठा net_device *dev,
			       काष्ठा fib_result *res)
अणु
	काष्ठा in_device *in_dev = __in_dev_get_rcu(dev);
	काष्ठा flow_keys *flkeys = शून्य, _flkeys;
	काष्ठा net    *net = dev_net(dev);
	काष्ठा ip_tunnel_info *tun_info;
	पूर्णांक		err = -EINVAL;
	अचिन्हित पूर्णांक	flags = 0;
	u32		itag = 0;
	काष्ठा rtable	*rth;
	काष्ठा flowi4	fl4;
	bool करो_cache = true;

	/* IP on this device is disabled. */

	अगर (!in_dev)
		जाओ out;

	/* Check क्रम the most weird martians, which can be not detected
	 * by fib_lookup.
	 */

	tun_info = skb_tunnel_info(skb);
	अगर (tun_info && !(tun_info->mode & IP_TUNNEL_INFO_TX))
		fl4.flowi4_tun_key.tun_id = tun_info->key.tun_id;
	अन्यथा
		fl4.flowi4_tun_key.tun_id = 0;
	skb_dst_drop(skb);

	अगर (ipv4_is_multicast(saddr) || ipv4_is_lbcast(saddr))
		जाओ martian_source;

	res->fi = शून्य;
	res->table = शून्य;
	अगर (ipv4_is_lbcast(daddr) || (saddr == 0 && daddr == 0))
		जाओ brd_input;

	/* Accept zero addresses only to limited broadcast;
	 * I even करो not know to fix it or not. Waiting क्रम complains :-)
	 */
	अगर (ipv4_is_zeronet(saddr))
		जाओ martian_source;

	अगर (ipv4_is_zeronet(daddr))
		जाओ martian_destination;

	/* Following code try to aव्योम calling IN_DEV_NET_ROUTE_LOCALNET(),
	 * and call it once अगर daddr or/and saddr are loopback addresses
	 */
	अगर (ipv4_is_loopback(daddr)) अणु
		अगर (!IN_DEV_NET_ROUTE_LOCALNET(in_dev, net))
			जाओ martian_destination;
	पूर्ण अन्यथा अगर (ipv4_is_loopback(saddr)) अणु
		अगर (!IN_DEV_NET_ROUTE_LOCALNET(in_dev, net))
			जाओ martian_source;
	पूर्ण

	/*
	 *	Now we are पढ़ोy to route packet.
	 */
	fl4.flowi4_oअगर = 0;
	fl4.flowi4_iअगर = dev->अगरindex;
	fl4.flowi4_mark = skb->mark;
	fl4.flowi4_tos = tos;
	fl4.flowi4_scope = RT_SCOPE_UNIVERSE;
	fl4.flowi4_flags = 0;
	fl4.daddr = daddr;
	fl4.saddr = saddr;
	fl4.flowi4_uid = sock_net_uid(net, शून्य);
	fl4.flowi4_multipath_hash = 0;

	अगर (fib4_rules_early_flow_dissect(net, skb, &fl4, &_flkeys)) अणु
		flkeys = &_flkeys;
	पूर्ण अन्यथा अणु
		fl4.flowi4_proto = 0;
		fl4.fl4_sport = 0;
		fl4.fl4_dport = 0;
	पूर्ण

	err = fib_lookup(net, &fl4, res, 0);
	अगर (err != 0) अणु
		अगर (!IN_DEV_FORWARD(in_dev))
			err = -EHOSTUNREACH;
		जाओ no_route;
	पूर्ण

	अगर (res->type == RTN_BROADCAST) अणु
		अगर (IN_DEV_BFORWARD(in_dev))
			जाओ make_route;
		/* not करो cache अगर bc_क्रमwarding is enabled */
		अगर (IPV4_DEVCONF_ALL(net, BC_FORWARDING))
			करो_cache = false;
		जाओ brd_input;
	पूर्ण

	अगर (res->type == RTN_LOCAL) अणु
		err = fib_validate_source(skb, saddr, daddr, tos,
					  0, dev, in_dev, &itag);
		अगर (err < 0)
			जाओ martian_source;
		जाओ local_input;
	पूर्ण

	अगर (!IN_DEV_FORWARD(in_dev)) अणु
		err = -EHOSTUNREACH;
		जाओ no_route;
	पूर्ण
	अगर (res->type != RTN_UNICAST)
		जाओ martian_destination;

make_route:
	err = ip_mkroute_input(skb, res, in_dev, daddr, saddr, tos, flkeys);
out:	वापस err;

brd_input:
	अगर (skb->protocol != htons(ETH_P_IP))
		जाओ e_inval;

	अगर (!ipv4_is_zeronet(saddr)) अणु
		err = fib_validate_source(skb, saddr, 0, tos, 0, dev,
					  in_dev, &itag);
		अगर (err < 0)
			जाओ martian_source;
	पूर्ण
	flags |= RTCF_BROADCAST;
	res->type = RTN_BROADCAST;
	RT_CACHE_STAT_INC(in_brd);

local_input:
	करो_cache &= res->fi && !itag;
	अगर (करो_cache) अणु
		काष्ठा fib_nh_common *nhc = FIB_RES_NHC(*res);

		rth = rcu_dereference(nhc->nhc_rth_input);
		अगर (rt_cache_valid(rth)) अणु
			skb_dst_set_noref(skb, &rth->dst);
			err = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	rth = rt_dst_alloc(ip_rt_get_dev(net, res),
			   flags | RTCF_LOCAL, res->type,
			   IN_DEV_ORCONF(in_dev, NOPOLICY), false);
	अगर (!rth)
		जाओ e_nobufs;

	rth->dst.output= ip_rt_bug;
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	rth->dst.tclassid = itag;
#पूर्ण_अगर
	rth->rt_is_input = 1;

	RT_CACHE_STAT_INC(in_slow_tot);
	अगर (res->type == RTN_UNREACHABLE) अणु
		rth->dst.input= ip_error;
		rth->dst.error= -err;
		rth->rt_flags	&= ~RTCF_LOCAL;
	पूर्ण

	अगर (करो_cache) अणु
		काष्ठा fib_nh_common *nhc = FIB_RES_NHC(*res);

		rth->dst.lwtstate = lwtstate_get(nhc->nhc_lwtstate);
		अगर (lwtunnel_input_redirect(rth->dst.lwtstate)) अणु
			WARN_ON(rth->dst.input == lwtunnel_input);
			rth->dst.lwtstate->orig_input = rth->dst.input;
			rth->dst.input = lwtunnel_input;
		पूर्ण

		अगर (unlikely(!rt_cache_route(nhc, rth)))
			rt_add_uncached_list(rth);
	पूर्ण
	skb_dst_set(skb, &rth->dst);
	err = 0;
	जाओ out;

no_route:
	RT_CACHE_STAT_INC(in_no_route);
	res->type = RTN_UNREACHABLE;
	res->fi = शून्य;
	res->table = शून्य;
	जाओ local_input;

	/*
	 *	Do not cache martian addresses: they should be logged (RFC1812)
	 */
martian_destination:
	RT_CACHE_STAT_INC(in_martian_dst);
#अगर_घोषित CONFIG_IP_ROUTE_VERBOSE
	अगर (IN_DEV_LOG_MARTIANS(in_dev))
		net_warn_ratelimited("martian destination %pI4 from %pI4, dev %s\n",
				     &daddr, &saddr, dev->name);
#पूर्ण_अगर

e_inval:
	err = -EINVAL;
	जाओ out;

e_nobufs:
	err = -ENOBUFS;
	जाओ out;

martian_source:
	ip_handle_martian_source(dev, in_dev, skb, daddr, saddr);
	जाओ out;
पूर्ण

पूर्णांक ip_route_input_noref(काष्ठा sk_buff *skb, __be32 daddr, __be32 saddr,
			 u8 tos, काष्ठा net_device *dev)
अणु
	काष्ठा fib_result res;
	पूर्णांक err;

	tos &= IPTOS_RT_MASK;
	rcu_पढ़ो_lock();
	err = ip_route_input_rcu(skb, daddr, saddr, tos, dev, &res);
	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण
EXPORT_SYMBOL(ip_route_input_noref);

/* called with rcu_पढ़ो_lock held */
पूर्णांक ip_route_input_rcu(काष्ठा sk_buff *skb, __be32 daddr, __be32 saddr,
		       u8 tos, काष्ठा net_device *dev, काष्ठा fib_result *res)
अणु
	/* Multicast recognition logic is moved from route cache to here.
	 * The problem was that too many Ethernet cards have broken/missing
	 * hardware multicast filters :-( As result the host on multicasting
	 * network acquires a lot of useless route cache entries, sort of
	 * SDR messages from all the world. Now we try to get rid of them.
	 * Really, provided software IP multicast filter is organized
	 * reasonably (at least, hashed), it करोes not result in a slowकरोwn
	 * comparing with route cache reject entries.
	 * Note, that multicast routers are not affected, because
	 * route cache entry is created eventually.
	 */
	अगर (ipv4_is_multicast(daddr)) अणु
		काष्ठा in_device *in_dev = __in_dev_get_rcu(dev);
		पूर्णांक our = 0;
		पूर्णांक err = -EINVAL;

		अगर (!in_dev)
			वापस err;
		our = ip_check_mc_rcu(in_dev, daddr, saddr,
				      ip_hdr(skb)->protocol);

		/* check l3 master अगर no match yet */
		अगर (!our && netअगर_is_l3_slave(dev)) अणु
			काष्ठा in_device *l3_in_dev;

			l3_in_dev = __in_dev_get_rcu(skb->dev);
			अगर (l3_in_dev)
				our = ip_check_mc_rcu(l3_in_dev, daddr, saddr,
						      ip_hdr(skb)->protocol);
		पूर्ण

		अगर (our
#अगर_घोषित CONFIG_IP_MROUTE
			||
		    (!ipv4_is_local_multicast(daddr) &&
		     IN_DEV_MFORWARD(in_dev))
#पूर्ण_अगर
		   ) अणु
			err = ip_route_input_mc(skb, daddr, saddr,
						tos, dev, our);
		पूर्ण
		वापस err;
	पूर्ण

	वापस ip_route_input_slow(skb, daddr, saddr, tos, dev, res);
पूर्ण

/* called with rcu_पढ़ो_lock() */
अटल काष्ठा rtable *__mkroute_output(स्थिर काष्ठा fib_result *res,
				       स्थिर काष्ठा flowi4 *fl4, पूर्णांक orig_oअगर,
				       काष्ठा net_device *dev_out,
				       अचिन्हित पूर्णांक flags)
अणु
	काष्ठा fib_info *fi = res->fi;
	काष्ठा fib_nh_exception *fnhe;
	काष्ठा in_device *in_dev;
	u16 type = res->type;
	काष्ठा rtable *rth;
	bool करो_cache;

	in_dev = __in_dev_get_rcu(dev_out);
	अगर (!in_dev)
		वापस ERR_PTR(-EINVAL);

	अगर (likely(!IN_DEV_ROUTE_LOCALNET(in_dev)))
		अगर (ipv4_is_loopback(fl4->saddr) &&
		    !(dev_out->flags & IFF_LOOPBACK) &&
		    !netअगर_is_l3_master(dev_out))
			वापस ERR_PTR(-EINVAL);

	अगर (ipv4_is_lbcast(fl4->daddr))
		type = RTN_BROADCAST;
	अन्यथा अगर (ipv4_is_multicast(fl4->daddr))
		type = RTN_MULTICAST;
	अन्यथा अगर (ipv4_is_zeronet(fl4->daddr))
		वापस ERR_PTR(-EINVAL);

	अगर (dev_out->flags & IFF_LOOPBACK)
		flags |= RTCF_LOCAL;

	करो_cache = true;
	अगर (type == RTN_BROADCAST) अणु
		flags |= RTCF_BROADCAST | RTCF_LOCAL;
		fi = शून्य;
	पूर्ण अन्यथा अगर (type == RTN_MULTICAST) अणु
		flags |= RTCF_MULTICAST | RTCF_LOCAL;
		अगर (!ip_check_mc_rcu(in_dev, fl4->daddr, fl4->saddr,
				     fl4->flowi4_proto))
			flags &= ~RTCF_LOCAL;
		अन्यथा
			करो_cache = false;
		/* If multicast route करो not exist use
		 * शेष one, but करो not gateway in this हाल.
		 * Yes, it is hack.
		 */
		अगर (fi && res->prefixlen < 4)
			fi = शून्य;
	पूर्ण अन्यथा अगर ((type == RTN_LOCAL) && (orig_oअगर != 0) &&
		   (orig_oअगर != dev_out->अगरindex)) अणु
		/* For local routes that require a particular output पूर्णांकerface
		 * we करो not want to cache the result.  Caching the result
		 * causes incorrect behaviour when there are multiple source
		 * addresses on the पूर्णांकerface, the end result being that अगर the
		 * पूर्णांकended recipient is रुकोing on that पूर्णांकerface क्रम the
		 * packet he won't receive it because it will be delivered on
		 * the loopback पूर्णांकerface and the IP_PKTINFO ipi_अगरindex will
		 * be set to the loopback पूर्णांकerface as well.
		 */
		करो_cache = false;
	पूर्ण

	fnhe = शून्य;
	करो_cache &= fi != शून्य;
	अगर (fi) अणु
		काष्ठा fib_nh_common *nhc = FIB_RES_NHC(*res);
		काष्ठा rtable __rcu **prth;

		fnhe = find_exception(nhc, fl4->daddr);
		अगर (!करो_cache)
			जाओ add;
		अगर (fnhe) अणु
			prth = &fnhe->fnhe_rth_output;
		पूर्ण अन्यथा अणु
			अगर (unlikely(fl4->flowi4_flags &
				     FLOWI_FLAG_KNOWN_NH &&
				     !(nhc->nhc_gw_family &&
				       nhc->nhc_scope == RT_SCOPE_LINK))) अणु
				करो_cache = false;
				जाओ add;
			पूर्ण
			prth = raw_cpu_ptr(nhc->nhc_pcpu_rth_output);
		पूर्ण
		rth = rcu_dereference(*prth);
		अगर (rt_cache_valid(rth) && dst_hold_safe(&rth->dst))
			वापस rth;
	पूर्ण

add:
	rth = rt_dst_alloc(dev_out, flags, type,
			   IN_DEV_ORCONF(in_dev, NOPOLICY),
			   IN_DEV_ORCONF(in_dev, NOXFRM));
	अगर (!rth)
		वापस ERR_PTR(-ENOBUFS);

	rth->rt_iअगर = orig_oअगर;

	RT_CACHE_STAT_INC(out_slow_tot);

	अगर (flags & (RTCF_BROADCAST | RTCF_MULTICAST)) अणु
		अगर (flags & RTCF_LOCAL &&
		    !(dev_out->flags & IFF_LOOPBACK)) अणु
			rth->dst.output = ip_mc_output;
			RT_CACHE_STAT_INC(out_slow_mc);
		पूर्ण
#अगर_घोषित CONFIG_IP_MROUTE
		अगर (type == RTN_MULTICAST) अणु
			अगर (IN_DEV_MFORWARD(in_dev) &&
			    !ipv4_is_local_multicast(fl4->daddr)) अणु
				rth->dst.input = ip_mr_input;
				rth->dst.output = ip_mc_output;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	rt_set_nexthop(rth, fl4->daddr, res, fnhe, fi, type, 0, करो_cache);
	lwtunnel_set_redirect(&rth->dst);

	वापस rth;
पूर्ण

/*
 * Major route resolver routine.
 */

काष्ठा rtable *ip_route_output_key_hash(काष्ठा net *net, काष्ठा flowi4 *fl4,
					स्थिर काष्ठा sk_buff *skb)
अणु
	__u8 tos = RT_FL_TOS(fl4);
	काष्ठा fib_result res = अणु
		.type		= RTN_UNSPEC,
		.fi		= शून्य,
		.table		= शून्य,
		.tclassid	= 0,
	पूर्ण;
	काष्ठा rtable *rth;

	fl4->flowi4_iअगर = LOOPBACK_IFINDEX;
	fl4->flowi4_tos = tos & IPTOS_RT_MASK;
	fl4->flowi4_scope = ((tos & RTO_ONLINK) ?
			 RT_SCOPE_LINK : RT_SCOPE_UNIVERSE);

	rcu_पढ़ो_lock();
	rth = ip_route_output_key_hash_rcu(net, fl4, &res, skb);
	rcu_पढ़ो_unlock();

	वापस rth;
पूर्ण
EXPORT_SYMBOL_GPL(ip_route_output_key_hash);

काष्ठा rtable *ip_route_output_key_hash_rcu(काष्ठा net *net, काष्ठा flowi4 *fl4,
					    काष्ठा fib_result *res,
					    स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev_out = शून्य;
	पूर्णांक orig_oअगर = fl4->flowi4_oअगर;
	अचिन्हित पूर्णांक flags = 0;
	काष्ठा rtable *rth;
	पूर्णांक err;

	अगर (fl4->saddr) अणु
		अगर (ipv4_is_multicast(fl4->saddr) ||
		    ipv4_is_lbcast(fl4->saddr) ||
		    ipv4_is_zeronet(fl4->saddr)) अणु
			rth = ERR_PTR(-EINVAL);
			जाओ out;
		पूर्ण

		rth = ERR_PTR(-ENETUNREACH);

		/* I हटाओd check क्रम oअगर == dev_out->oअगर here.
		 * It was wrong क्रम two reasons:
		 * 1. ip_dev_find(net, saddr) can वापस wrong अगरace, अगर saddr
		 *    is asचिन्हित to multiple पूर्णांकerfaces.
		 * 2. Moreover, we are allowed to send packets with saddr
		 *    of another अगरace. --ANK
		 */

		अगर (fl4->flowi4_oअगर == 0 &&
		    (ipv4_is_multicast(fl4->daddr) ||
		     ipv4_is_lbcast(fl4->daddr))) अणु
			/* It is equivalent to inet_addr_type(saddr) == RTN_LOCAL */
			dev_out = __ip_dev_find(net, fl4->saddr, false);
			अगर (!dev_out)
				जाओ out;

			/* Special hack: user can direct multicasts
			 * and limited broadcast via necessary पूर्णांकerface
			 * without fiddling with IP_MULTICAST_IF or IP_PKTINFO.
			 * This hack is not just क्रम fun, it allows
			 * vic,vat and मित्रs to work.
			 * They bind socket to loopback, set ttl to zero
			 * and expect that it will work.
			 * From the viewpoपूर्णांक of routing cache they are broken,
			 * because we are not allowed to build multicast path
			 * with loopback source addr (look, routing cache
			 * cannot know, that ttl is zero, so that packet
			 * will not leave this host and route is valid).
			 * Luckily, this hack is good workaround.
			 */

			fl4->flowi4_oअगर = dev_out->अगरindex;
			जाओ make_route;
		पूर्ण

		अगर (!(fl4->flowi4_flags & FLOWI_FLAG_ANYSRC)) अणु
			/* It is equivalent to inet_addr_type(saddr) == RTN_LOCAL */
			अगर (!__ip_dev_find(net, fl4->saddr, false))
				जाओ out;
		पूर्ण
	पूर्ण


	अगर (fl4->flowi4_oअगर) अणु
		dev_out = dev_get_by_index_rcu(net, fl4->flowi4_oअगर);
		rth = ERR_PTR(-ENODEV);
		अगर (!dev_out)
			जाओ out;

		/* RACE: Check वापस value of inet_select_addr instead. */
		अगर (!(dev_out->flags & IFF_UP) || !__in_dev_get_rcu(dev_out)) अणु
			rth = ERR_PTR(-ENETUNREACH);
			जाओ out;
		पूर्ण
		अगर (ipv4_is_local_multicast(fl4->daddr) ||
		    ipv4_is_lbcast(fl4->daddr) ||
		    fl4->flowi4_proto == IPPROTO_IGMP) अणु
			अगर (!fl4->saddr)
				fl4->saddr = inet_select_addr(dev_out, 0,
							      RT_SCOPE_LINK);
			जाओ make_route;
		पूर्ण
		अगर (!fl4->saddr) अणु
			अगर (ipv4_is_multicast(fl4->daddr))
				fl4->saddr = inet_select_addr(dev_out, 0,
							      fl4->flowi4_scope);
			अन्यथा अगर (!fl4->daddr)
				fl4->saddr = inet_select_addr(dev_out, 0,
							      RT_SCOPE_HOST);
		पूर्ण
	पूर्ण

	अगर (!fl4->daddr) अणु
		fl4->daddr = fl4->saddr;
		अगर (!fl4->daddr)
			fl4->daddr = fl4->saddr = htonl(INADDR_LOOPBACK);
		dev_out = net->loopback_dev;
		fl4->flowi4_oअगर = LOOPBACK_IFINDEX;
		res->type = RTN_LOCAL;
		flags |= RTCF_LOCAL;
		जाओ make_route;
	पूर्ण

	err = fib_lookup(net, fl4, res, 0);
	अगर (err) अणु
		res->fi = शून्य;
		res->table = शून्य;
		अगर (fl4->flowi4_oअगर &&
		    (ipv4_is_multicast(fl4->daddr) ||
		    !netअगर_index_is_l3_master(net, fl4->flowi4_oअगर))) अणु
			/* Apparently, routing tables are wrong. Assume,
			 * that the destination is on link.
			 *
			 * WHY? DW.
			 * Because we are allowed to send to अगरace
			 * even अगर it has NO routes and NO asचिन्हित
			 * addresses. When oअगर is specअगरied, routing
			 * tables are looked up with only one purpose:
			 * to catch अगर destination is gatewayed, rather than
			 * direct. Moreover, अगर MSG_DONTROUTE is set,
			 * we send packet, ignoring both routing tables
			 * and अगरaddr state. --ANK
			 *
			 *
			 * We could make it even अगर oअगर is unknown,
			 * likely IPv6, but we करो not.
			 */

			अगर (fl4->saddr == 0)
				fl4->saddr = inet_select_addr(dev_out, 0,
							      RT_SCOPE_LINK);
			res->type = RTN_UNICAST;
			जाओ make_route;
		पूर्ण
		rth = ERR_PTR(err);
		जाओ out;
	पूर्ण

	अगर (res->type == RTN_LOCAL) अणु
		अगर (!fl4->saddr) अणु
			अगर (res->fi->fib_prefsrc)
				fl4->saddr = res->fi->fib_prefsrc;
			अन्यथा
				fl4->saddr = fl4->daddr;
		पूर्ण

		/* L3 master device is the loopback क्रम that करोमुख्य */
		dev_out = l3mdev_master_dev_rcu(FIB_RES_DEV(*res)) ? :
			net->loopback_dev;

		/* make sure orig_oअगर poपूर्णांकs to fib result device even
		 * though packet rx/tx happens over loopback or l3mdev
		 */
		orig_oअगर = FIB_RES_OIF(*res);

		fl4->flowi4_oअगर = dev_out->अगरindex;
		flags |= RTCF_LOCAL;
		जाओ make_route;
	पूर्ण

	fib_select_path(net, res, fl4, skb);

	dev_out = FIB_RES_DEV(*res);

make_route:
	rth = __mkroute_output(res, fl4, orig_oअगर, dev_out, flags);

out:
	वापस rth;
पूर्ण

अटल काष्ठा dst_ops ipv4_dst_blackhole_ops = अणु
	.family			= AF_INET,
	.शेष_advmss		= ipv4_शेष_advmss,
	.neigh_lookup		= ipv4_neigh_lookup,
	.check			= dst_blackhole_check,
	.cow_metrics		= dst_blackhole_cow_metrics,
	.update_pmtu		= dst_blackhole_update_pmtu,
	.redirect		= dst_blackhole_redirect,
	.mtu			= dst_blackhole_mtu,
पूर्ण;

काष्ठा dst_entry *ipv4_blackhole_route(काष्ठा net *net, काष्ठा dst_entry *dst_orig)
अणु
	काष्ठा rtable *ort = (काष्ठा rtable *) dst_orig;
	काष्ठा rtable *rt;

	rt = dst_alloc(&ipv4_dst_blackhole_ops, शून्य, 1, DST_OBSOLETE_DEAD, 0);
	अगर (rt) अणु
		काष्ठा dst_entry *new = &rt->dst;

		new->__use = 1;
		new->input = dst_discard;
		new->output = dst_discard_out;

		new->dev = net->loopback_dev;
		अगर (new->dev)
			dev_hold(new->dev);

		rt->rt_is_input = ort->rt_is_input;
		rt->rt_iअगर = ort->rt_iअगर;
		rt->rt_pmtu = ort->rt_pmtu;
		rt->rt_mtu_locked = ort->rt_mtu_locked;

		rt->rt_genid = rt_genid_ipv4(net);
		rt->rt_flags = ort->rt_flags;
		rt->rt_type = ort->rt_type;
		rt->rt_uses_gateway = ort->rt_uses_gateway;
		rt->rt_gw_family = ort->rt_gw_family;
		अगर (rt->rt_gw_family == AF_INET)
			rt->rt_gw4 = ort->rt_gw4;
		अन्यथा अगर (rt->rt_gw_family == AF_INET6)
			rt->rt_gw6 = ort->rt_gw6;

		INIT_LIST_HEAD(&rt->rt_uncached);
	पूर्ण

	dst_release(dst_orig);

	वापस rt ? &rt->dst : ERR_PTR(-ENOMEM);
पूर्ण

काष्ठा rtable *ip_route_output_flow(काष्ठा net *net, काष्ठा flowi4 *flp4,
				    स्थिर काष्ठा sock *sk)
अणु
	काष्ठा rtable *rt = __ip_route_output_key(net, flp4);

	अगर (IS_ERR(rt))
		वापस rt;

	अगर (flp4->flowi4_proto) अणु
		flp4->flowi4_oअगर = rt->dst.dev->अगरindex;
		rt = (काष्ठा rtable *)xfrm_lookup_route(net, &rt->dst,
							flowi4_to_flowi(flp4),
							sk, 0);
	पूर्ण

	वापस rt;
पूर्ण
EXPORT_SYMBOL_GPL(ip_route_output_flow);

काष्ठा rtable *ip_route_output_tunnel(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev,
				      काष्ठा net *net, __be32 *saddr,
				      स्थिर काष्ठा ip_tunnel_info *info,
				      u8 protocol, bool use_cache)
अणु
#अगर_घोषित CONFIG_DST_CACHE
	काष्ठा dst_cache *dst_cache;
#पूर्ण_अगर
	काष्ठा rtable *rt = शून्य;
	काष्ठा flowi4 fl4;
	__u8 tos;

#अगर_घोषित CONFIG_DST_CACHE
	dst_cache = (काष्ठा dst_cache *)&info->dst_cache;
	अगर (use_cache) अणु
		rt = dst_cache_get_ip4(dst_cache, saddr);
		अगर (rt)
			वापस rt;
	पूर्ण
#पूर्ण_अगर
	स_रखो(&fl4, 0, माप(fl4));
	fl4.flowi4_mark = skb->mark;
	fl4.flowi4_proto = protocol;
	fl4.daddr = info->key.u.ipv4.dst;
	fl4.saddr = info->key.u.ipv4.src;
	tos = info->key.tos;
	fl4.flowi4_tos = RT_TOS(tos);

	rt = ip_route_output_key(net, &fl4);
	अगर (IS_ERR(rt)) अणु
		netdev_dbg(dev, "no route to %pI4\n", &fl4.daddr);
		वापस ERR_PTR(-ENETUNREACH);
	पूर्ण
	अगर (rt->dst.dev == dev) अणु /* is this necessary? */
		netdev_dbg(dev, "circular route to %pI4\n", &fl4.daddr);
		ip_rt_put(rt);
		वापस ERR_PTR(-ELOOP);
	पूर्ण
#अगर_घोषित CONFIG_DST_CACHE
	अगर (use_cache)
		dst_cache_set_ip4(dst_cache, &rt->dst, fl4.saddr);
#पूर्ण_अगर
	*saddr = fl4.saddr;
	वापस rt;
पूर्ण
EXPORT_SYMBOL_GPL(ip_route_output_tunnel);

/* called with rcu_पढ़ो_lock held */
अटल पूर्णांक rt_fill_info(काष्ठा net *net, __be32 dst, __be32 src,
			काष्ठा rtable *rt, u32 table_id, काष्ठा flowi4 *fl4,
			काष्ठा sk_buff *skb, u32 portid, u32 seq,
			अचिन्हित पूर्णांक flags)
अणु
	काष्ठा rपंचांगsg *r;
	काष्ठा nlmsghdr *nlh;
	अचिन्हित दीर्घ expires = 0;
	u32 error;
	u32 metrics[RTAX_MAX];

	nlh = nlmsg_put(skb, portid, seq, RTM_NEWROUTE, माप(*r), flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	r = nlmsg_data(nlh);
	r->rपंचांग_family	 = AF_INET;
	r->rपंचांग_dst_len	= 32;
	r->rपंचांग_src_len	= 0;
	r->rपंचांग_tos	= fl4 ? fl4->flowi4_tos : 0;
	r->rपंचांग_table	= table_id < 256 ? table_id : RT_TABLE_COMPAT;
	अगर (nla_put_u32(skb, RTA_TABLE, table_id))
		जाओ nla_put_failure;
	r->rपंचांग_type	= rt->rt_type;
	r->rपंचांग_scope	= RT_SCOPE_UNIVERSE;
	r->rपंचांग_protocol = RTPROT_UNSPEC;
	r->rपंचांग_flags	= (rt->rt_flags & ~0xFFFF) | RTM_F_CLONED;
	अगर (rt->rt_flags & RTCF_NOTIFY)
		r->rपंचांग_flags |= RTM_F_NOTIFY;
	अगर (IPCB(skb)->flags & IPSKB_DOREसूचीECT)
		r->rपंचांग_flags |= RTCF_DOREसूचीECT;

	अगर (nla_put_in_addr(skb, RTA_DST, dst))
		जाओ nla_put_failure;
	अगर (src) अणु
		r->rपंचांग_src_len = 32;
		अगर (nla_put_in_addr(skb, RTA_SRC, src))
			जाओ nla_put_failure;
	पूर्ण
	अगर (rt->dst.dev &&
	    nla_put_u32(skb, RTA_OIF, rt->dst.dev->अगरindex))
		जाओ nla_put_failure;
	अगर (rt->dst.lwtstate &&
	    lwtunnel_fill_encap(skb, rt->dst.lwtstate, RTA_ENCAP, RTA_ENCAP_TYPE) < 0)
		जाओ nla_put_failure;
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	अगर (rt->dst.tclassid &&
	    nla_put_u32(skb, RTA_FLOW, rt->dst.tclassid))
		जाओ nla_put_failure;
#पूर्ण_अगर
	अगर (fl4 && !rt_is_input_route(rt) &&
	    fl4->saddr != src) अणु
		अगर (nla_put_in_addr(skb, RTA_PREFSRC, fl4->saddr))
			जाओ nla_put_failure;
	पूर्ण
	अगर (rt->rt_uses_gateway) अणु
		अगर (rt->rt_gw_family == AF_INET &&
		    nla_put_in_addr(skb, RTA_GATEWAY, rt->rt_gw4)) अणु
			जाओ nla_put_failure;
		पूर्ण अन्यथा अगर (rt->rt_gw_family == AF_INET6) अणु
			पूर्णांक alen = माप(काष्ठा in6_addr);
			काष्ठा nlattr *nla;
			काष्ठा rtvia *via;

			nla = nla_reserve(skb, RTA_VIA, alen + 2);
			अगर (!nla)
				जाओ nla_put_failure;

			via = nla_data(nla);
			via->rtvia_family = AF_INET6;
			स_नकल(via->rtvia_addr, &rt->rt_gw6, alen);
		पूर्ण
	पूर्ण

	expires = rt->dst.expires;
	अगर (expires) अणु
		अचिन्हित दीर्घ now = jअगरfies;

		अगर (समय_beक्रमe(now, expires))
			expires -= now;
		अन्यथा
			expires = 0;
	पूर्ण

	स_नकल(metrics, dst_metrics_ptr(&rt->dst), माप(metrics));
	अगर (rt->rt_pmtu && expires)
		metrics[RTAX_MTU - 1] = rt->rt_pmtu;
	अगर (rt->rt_mtu_locked && expires)
		metrics[RTAX_LOCK - 1] |= BIT(RTAX_MTU);
	अगर (rtnetlink_put_metrics(skb, metrics) < 0)
		जाओ nla_put_failure;

	अगर (fl4) अणु
		अगर (fl4->flowi4_mark &&
		    nla_put_u32(skb, RTA_MARK, fl4->flowi4_mark))
			जाओ nla_put_failure;

		अगर (!uid_eq(fl4->flowi4_uid, INVALID_UID) &&
		    nla_put_u32(skb, RTA_UID,
				from_kuid_munged(current_user_ns(),
						 fl4->flowi4_uid)))
			जाओ nla_put_failure;

		अगर (rt_is_input_route(rt)) अणु
#अगर_घोषित CONFIG_IP_MROUTE
			अगर (ipv4_is_multicast(dst) &&
			    !ipv4_is_local_multicast(dst) &&
			    IPV4_DEVCONF_ALL(net, MC_FORWARDING)) अणु
				पूर्णांक err = ipmr_get_route(net, skb,
							 fl4->saddr, fl4->daddr,
							 r, portid);

				अगर (err <= 0) अणु
					अगर (err == 0)
						वापस 0;
					जाओ nla_put_failure;
				पूर्ण
			पूर्ण अन्यथा
#पूर्ण_अगर
				अगर (nla_put_u32(skb, RTA_IIF, fl4->flowi4_iअगर))
					जाओ nla_put_failure;
		पूर्ण
	पूर्ण

	error = rt->dst.error;

	अगर (rtnl_put_cacheinfo(skb, &rt->dst, 0, expires, error) < 0)
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fnhe_dump_bucket(काष्ठा net *net, काष्ठा sk_buff *skb,
			    काष्ठा netlink_callback *cb, u32 table_id,
			    काष्ठा fnhe_hash_bucket *bucket, पूर्णांक genid,
			    पूर्णांक *fa_index, पूर्णांक fa_start, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < FNHE_HASH_SIZE; i++) अणु
		काष्ठा fib_nh_exception *fnhe;

		क्रम (fnhe = rcu_dereference(bucket[i].chain); fnhe;
		     fnhe = rcu_dereference(fnhe->fnhe_next)) अणु
			काष्ठा rtable *rt;
			पूर्णांक err;

			अगर (*fa_index < fa_start)
				जाओ next;

			अगर (fnhe->fnhe_genid != genid)
				जाओ next;

			अगर (fnhe->fnhe_expires &&
			    समय_after(jअगरfies, fnhe->fnhe_expires))
				जाओ next;

			rt = rcu_dereference(fnhe->fnhe_rth_input);
			अगर (!rt)
				rt = rcu_dereference(fnhe->fnhe_rth_output);
			अगर (!rt)
				जाओ next;

			err = rt_fill_info(net, fnhe->fnhe_daddr, 0, rt,
					   table_id, शून्य, skb,
					   NETLINK_CB(cb->skb).portid,
					   cb->nlh->nlmsg_seq, flags);
			अगर (err)
				वापस err;
next:
			(*fa_index)++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक fib_dump_info_fnhe(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
		       u32 table_id, काष्ठा fib_info *fi,
		       पूर्णांक *fa_index, पूर्णांक fa_start, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा net *net = sock_net(cb->skb->sk);
	पूर्णांक nhsel, genid = fnhe_genid(net);

	क्रम (nhsel = 0; nhsel < fib_info_num_path(fi); nhsel++) अणु
		काष्ठा fib_nh_common *nhc = fib_info_nhc(fi, nhsel);
		काष्ठा fnhe_hash_bucket *bucket;
		पूर्णांक err;

		अगर (nhc->nhc_flags & RTNH_F_DEAD)
			जारी;

		rcu_पढ़ो_lock();
		bucket = rcu_dereference(nhc->nhc_exceptions);
		err = 0;
		अगर (bucket)
			err = fnhe_dump_bucket(net, skb, cb, table_id, bucket,
					       genid, fa_index, fa_start,
					       flags);
		rcu_पढ़ो_unlock();
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *inet_rपंचांग_getroute_build_skb(__be32 src, __be32 dst,
						   u8 ip_proto, __be16 sport,
						   __be16 dport)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा iphdr *iph;

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!skb)
		वापस शून्य;

	/* Reserve room क्रम dummy headers, this skb can pass
	 * through good chunk of routing engine.
	 */
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	skb->protocol = htons(ETH_P_IP);
	iph = skb_put(skb, माप(काष्ठा iphdr));
	iph->protocol = ip_proto;
	iph->saddr = src;
	iph->daddr = dst;
	iph->version = 0x4;
	iph->frag_off = 0;
	iph->ihl = 0x5;
	skb_set_transport_header(skb, skb->len);

	चयन (iph->protocol) अणु
	हाल IPPROTO_UDP: अणु
		काष्ठा udphdr *udph;

		udph = skb_put_zero(skb, माप(काष्ठा udphdr));
		udph->source = sport;
		udph->dest = dport;
		udph->len = माप(काष्ठा udphdr);
		udph->check = 0;
		अवरोध;
	पूर्ण
	हाल IPPROTO_TCP: अणु
		काष्ठा tcphdr *tcph;

		tcph = skb_put_zero(skb, माप(काष्ठा tcphdr));
		tcph->source	= sport;
		tcph->dest	= dport;
		tcph->करोff	= माप(काष्ठा tcphdr) / 4;
		tcph->rst = 1;
		tcph->check = ~tcp_v4_check(माप(काष्ठा tcphdr),
					    src, dst, 0);
		अवरोध;
	पूर्ण
	हाल IPPROTO_ICMP: अणु
		काष्ठा icmphdr *icmph;

		icmph = skb_put_zero(skb, माप(काष्ठा icmphdr));
		icmph->type = ICMP_ECHO;
		icmph->code = 0;
	पूर्ण
	पूर्ण

	वापस skb;
पूर्ण

अटल पूर्णांक inet_rपंचांग_valid_getroute_req(काष्ठा sk_buff *skb,
				       स्थिर काष्ठा nlmsghdr *nlh,
				       काष्ठा nlattr **tb,
				       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा rपंचांगsg *rपंचांग;
	पूर्णांक i, err;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*rपंचांग))) अणु
		NL_SET_ERR_MSG(extack,
			       "ipv4: Invalid header for route get request");
		वापस -EINVAL;
	पूर्ण

	अगर (!netlink_strict_get_check(skb))
		वापस nlmsg_parse_deprecated(nlh, माप(*rपंचांग), tb, RTA_MAX,
					      rपंचांग_ipv4_policy, extack);

	rपंचांग = nlmsg_data(nlh);
	अगर ((rपंचांग->rपंचांग_src_len && rपंचांग->rपंचांग_src_len != 32) ||
	    (rपंचांग->rपंचांग_dst_len && rपंचांग->rपंचांग_dst_len != 32) ||
	    rपंचांग->rपंचांग_table || rपंचांग->rपंचांग_protocol ||
	    rपंचांग->rपंचांग_scope || rपंचांग->rपंचांग_type) अणु
		NL_SET_ERR_MSG(extack, "ipv4: Invalid values in header for route get request");
		वापस -EINVAL;
	पूर्ण

	अगर (rपंचांग->rपंचांग_flags & ~(RTM_F_NOTIFY |
			       RTM_F_LOOKUP_TABLE |
			       RTM_F_FIB_MATCH)) अणु
		NL_SET_ERR_MSG(extack, "ipv4: Unsupported rtm_flags for route get request");
		वापस -EINVAL;
	पूर्ण

	err = nlmsg_parse_deprecated_strict(nlh, माप(*rपंचांग), tb, RTA_MAX,
					    rपंचांग_ipv4_policy, extack);
	अगर (err)
		वापस err;

	अगर ((tb[RTA_SRC] && !rपंचांग->rपंचांग_src_len) ||
	    (tb[RTA_DST] && !rपंचांग->rपंचांग_dst_len)) अणु
		NL_SET_ERR_MSG(extack, "ipv4: rtm_src_len and rtm_dst_len must be 32 for IPv4");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i <= RTA_MAX; i++) अणु
		अगर (!tb[i])
			जारी;

		चयन (i) अणु
		हाल RTA_IIF:
		हाल RTA_OIF:
		हाल RTA_SRC:
		हाल RTA_DST:
		हाल RTA_IP_PROTO:
		हाल RTA_SPORT:
		हाल RTA_DPORT:
		हाल RTA_MARK:
		हाल RTA_UID:
			अवरोध;
		शेष:
			NL_SET_ERR_MSG(extack, "ipv4: Unsupported attribute in route get request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक inet_rपंचांग_getroute(काष्ठा sk_buff *in_skb, काष्ठा nlmsghdr *nlh,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(in_skb->sk);
	काष्ठा nlattr *tb[RTA_MAX+1];
	u32 table_id = RT_TABLE_MAIN;
	__be16 sport = 0, dport = 0;
	काष्ठा fib_result res = अणुपूर्ण;
	u8 ip_proto = IPPROTO_UDP;
	काष्ठा rtable *rt = शून्य;
	काष्ठा sk_buff *skb;
	काष्ठा rपंचांगsg *rपंचांग;
	काष्ठा flowi4 fl4 = अणुपूर्ण;
	__be32 dst = 0;
	__be32 src = 0;
	kuid_t uid;
	u32 iअगर;
	पूर्णांक err;
	पूर्णांक mark;

	err = inet_rपंचांग_valid_getroute_req(in_skb, nlh, tb, extack);
	अगर (err < 0)
		वापस err;

	rपंचांग = nlmsg_data(nlh);
	src = tb[RTA_SRC] ? nla_get_in_addr(tb[RTA_SRC]) : 0;
	dst = tb[RTA_DST] ? nla_get_in_addr(tb[RTA_DST]) : 0;
	iअगर = tb[RTA_IIF] ? nla_get_u32(tb[RTA_IIF]) : 0;
	mark = tb[RTA_MARK] ? nla_get_u32(tb[RTA_MARK]) : 0;
	अगर (tb[RTA_UID])
		uid = make_kuid(current_user_ns(), nla_get_u32(tb[RTA_UID]));
	अन्यथा
		uid = (iअगर ? INVALID_UID : current_uid());

	अगर (tb[RTA_IP_PROTO]) अणु
		err = rपंचांग_getroute_parse_ip_proto(tb[RTA_IP_PROTO],
						  &ip_proto, AF_INET, extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[RTA_SPORT])
		sport = nla_get_be16(tb[RTA_SPORT]);

	अगर (tb[RTA_DPORT])
		dport = nla_get_be16(tb[RTA_DPORT]);

	skb = inet_rपंचांग_getroute_build_skb(src, dst, ip_proto, sport, dport);
	अगर (!skb)
		वापस -ENOBUFS;

	fl4.daddr = dst;
	fl4.saddr = src;
	fl4.flowi4_tos = rपंचांग->rपंचांग_tos & IPTOS_RT_MASK;
	fl4.flowi4_oअगर = tb[RTA_OIF] ? nla_get_u32(tb[RTA_OIF]) : 0;
	fl4.flowi4_mark = mark;
	fl4.flowi4_uid = uid;
	अगर (sport)
		fl4.fl4_sport = sport;
	अगर (dport)
		fl4.fl4_dport = dport;
	fl4.flowi4_proto = ip_proto;

	rcu_पढ़ो_lock();

	अगर (iअगर) अणु
		काष्ठा net_device *dev;

		dev = dev_get_by_index_rcu(net, iअगर);
		अगर (!dev) अणु
			err = -ENODEV;
			जाओ errout_rcu;
		पूर्ण

		fl4.flowi4_iअगर = iअगर; /* क्रम rt_fill_info */
		skb->dev	= dev;
		skb->mark	= mark;
		err = ip_route_input_rcu(skb, dst, src,
					 rपंचांग->rपंचांग_tos & IPTOS_RT_MASK, dev,
					 &res);

		rt = skb_rtable(skb);
		अगर (err == 0 && rt->dst.error)
			err = -rt->dst.error;
	पूर्ण अन्यथा अणु
		fl4.flowi4_iअगर = LOOPBACK_IFINDEX;
		skb->dev = net->loopback_dev;
		rt = ip_route_output_key_hash_rcu(net, &fl4, &res, skb);
		err = 0;
		अगर (IS_ERR(rt))
			err = PTR_ERR(rt);
		अन्यथा
			skb_dst_set(skb, &rt->dst);
	पूर्ण

	अगर (err)
		जाओ errout_rcu;

	अगर (rपंचांग->rपंचांग_flags & RTM_F_NOTIFY)
		rt->rt_flags |= RTCF_NOTIFY;

	अगर (rपंचांग->rपंचांग_flags & RTM_F_LOOKUP_TABLE)
		table_id = res.table ? res.table->tb_id : 0;

	/* reset skb क्रम netlink reply msg */
	skb_trim(skb, 0);
	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);
	skb_reset_mac_header(skb);

	अगर (rपंचांग->rपंचांग_flags & RTM_F_FIB_MATCH) अणु
		काष्ठा fib_rt_info fri;

		अगर (!res.fi) अणु
			err = fib_props[res.type].error;
			अगर (!err)
				err = -EHOSTUNREACH;
			जाओ errout_rcu;
		पूर्ण
		fri.fi = res.fi;
		fri.tb_id = table_id;
		fri.dst = res.prefix;
		fri.dst_len = res.prefixlen;
		fri.tos = fl4.flowi4_tos;
		fri.type = rt->rt_type;
		fri.offload = 0;
		fri.trap = 0;
		fri.offload_failed = 0;
		अगर (res.fa_head) अणु
			काष्ठा fib_alias *fa;

			hlist_क्रम_each_entry_rcu(fa, res.fa_head, fa_list) अणु
				u8 slen = 32 - fri.dst_len;

				अगर (fa->fa_slen == slen &&
				    fa->tb_id == fri.tb_id &&
				    fa->fa_tos == fri.tos &&
				    fa->fa_info == res.fi &&
				    fa->fa_type == fri.type) अणु
					fri.offload = fa->offload;
					fri.trap = fa->trap;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		err = fib_dump_info(skb, NETLINK_CB(in_skb).portid,
				    nlh->nlmsg_seq, RTM_NEWROUTE, &fri, 0);
	पूर्ण अन्यथा अणु
		err = rt_fill_info(net, dst, src, rt, table_id, &fl4, skb,
				   NETLINK_CB(in_skb).portid,
				   nlh->nlmsg_seq, 0);
	पूर्ण
	अगर (err < 0)
		जाओ errout_rcu;

	rcu_पढ़ो_unlock();

	err = rtnl_unicast(skb, net, NETLINK_CB(in_skb).portid);

errout_मुक्त:
	वापस err;
errout_rcu:
	rcu_पढ़ो_unlock();
	kमुक्त_skb(skb);
	जाओ errout_मुक्त;
पूर्ण

व्योम ip_rt_multicast_event(काष्ठा in_device *in_dev)
अणु
	rt_cache_flush(dev_net(in_dev->dev));
पूर्ण

#अगर_घोषित CONFIG_SYSCTL
अटल पूर्णांक ip_rt_gc_पूर्णांकerval __पढ़ो_mostly  = 60 * HZ;
अटल पूर्णांक ip_rt_gc_min_पूर्णांकerval __पढ़ो_mostly	= HZ / 2;
अटल पूर्णांक ip_rt_gc_elasticity __पढ़ो_mostly	= 8;
अटल पूर्णांक ip_min_valid_pmtu __पढ़ो_mostly	= IPV4_MIN_MTU;

अटल पूर्णांक ipv4_sysctl_rtcache_flush(काष्ठा ctl_table *__ctl, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा net *net = (काष्ठा net *)__ctl->extra1;

	अगर (ग_लिखो) अणु
		rt_cache_flush(net);
		fnhe_genid_bump(net);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल काष्ठा ctl_table ipv4_route_table[] = अणु
	अणु
		.procname	= "gc_thresh",
		.data		= &ipv4_dst_ops.gc_thresh,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "max_size",
		.data		= &ip_rt_max_size,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		/*  Deprecated. Use gc_min_पूर्णांकerval_ms */

		.procname	= "gc_min_interval",
		.data		= &ip_rt_gc_min_पूर्णांकerval,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "gc_min_interval_ms",
		.data		= &ip_rt_gc_min_पूर्णांकerval,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_ms_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "gc_timeout",
		.data		= &ip_rt_gc_समयout,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "gc_interval",
		.data		= &ip_rt_gc_पूर्णांकerval,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "redirect_load",
		.data		= &ip_rt_redirect_load,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "redirect_number",
		.data		= &ip_rt_redirect_number,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "redirect_silence",
		.data		= &ip_rt_redirect_silence,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "error_cost",
		.data		= &ip_rt_error_cost,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "error_burst",
		.data		= &ip_rt_error_burst,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "gc_elasticity",
		.data		= &ip_rt_gc_elasticity,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "mtu_expires",
		.data		= &ip_rt_mtu_expires,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "min_pmtu",
		.data		= &ip_rt_min_pmtu,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &ip_min_valid_pmtu,
	पूर्ण,
	अणु
		.procname	= "min_adv_mss",
		.data		= &ip_rt_min_advmss,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर अक्षर ipv4_route_flush_procname[] = "flush";

अटल काष्ठा ctl_table ipv4_route_flush_table[] = अणु
	अणु
		.procname	= ipv4_route_flush_procname,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0200,
		.proc_handler	= ipv4_sysctl_rtcache_flush,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल __net_init पूर्णांक sysctl_route_net_init(काष्ठा net *net)
अणु
	काष्ठा ctl_table *tbl;

	tbl = ipv4_route_flush_table;
	अगर (!net_eq(net, &init_net)) अणु
		tbl = kmemdup(tbl, माप(ipv4_route_flush_table), GFP_KERNEL);
		अगर (!tbl)
			जाओ err_dup;

		/* Don't export non-whitelisted sysctls to unprivileged users */
		अगर (net->user_ns != &init_user_ns) अणु
			अगर (tbl[0].procname != ipv4_route_flush_procname)
				tbl[0].procname = शून्य;
		पूर्ण
	पूर्ण
	tbl[0].extra1 = net;

	net->ipv4.route_hdr = रेजिस्टर_net_sysctl(net, "net/ipv4/route", tbl);
	अगर (!net->ipv4.route_hdr)
		जाओ err_reg;
	वापस 0;

err_reg:
	अगर (tbl != ipv4_route_flush_table)
		kमुक्त(tbl);
err_dup:
	वापस -ENOMEM;
पूर्ण

अटल __net_निकास व्योम sysctl_route_net_निकास(काष्ठा net *net)
अणु
	काष्ठा ctl_table *tbl;

	tbl = net->ipv4.route_hdr->ctl_table_arg;
	unरेजिस्टर_net_sysctl_table(net->ipv4.route_hdr);
	BUG_ON(tbl == ipv4_route_flush_table);
	kमुक्त(tbl);
पूर्ण

अटल __net_initdata काष्ठा pernet_operations sysctl_route_ops = अणु
	.init = sysctl_route_net_init,
	.निकास = sysctl_route_net_निकास,
पूर्ण;
#पूर्ण_अगर

अटल __net_init पूर्णांक rt_genid_init(काष्ठा net *net)
अणु
	atomic_set(&net->ipv4.rt_genid, 0);
	atomic_set(&net->fnhe_genid, 0);
	atomic_set(&net->ipv4.dev_addr_genid, get_अक्रमom_पूर्णांक());
	वापस 0;
पूर्ण

अटल __net_initdata काष्ठा pernet_operations rt_genid_ops = अणु
	.init = rt_genid_init,
पूर्ण;

अटल पूर्णांक __net_init ipv4_inetpeer_init(काष्ठा net *net)
अणु
	काष्ठा inet_peer_base *bp = kदो_स्मृति(माप(*bp), GFP_KERNEL);

	अगर (!bp)
		वापस -ENOMEM;
	inet_peer_base_init(bp);
	net->ipv4.peers = bp;
	वापस 0;
पूर्ण

अटल व्योम __net_निकास ipv4_inetpeer_निकास(काष्ठा net *net)
अणु
	काष्ठा inet_peer_base *bp = net->ipv4.peers;

	net->ipv4.peers = शून्य;
	inetpeer_invalidate_tree(bp);
	kमुक्त(bp);
पूर्ण

अटल __net_initdata काष्ठा pernet_operations ipv4_inetpeer_ops = अणु
	.init	=	ipv4_inetpeer_init,
	.निकास	=	ipv4_inetpeer_निकास,
पूर्ण;

#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
काष्ठा ip_rt_acct __percpu *ip_rt_acct __पढ़ो_mostly;
#पूर्ण_अगर /* CONFIG_IP_ROUTE_CLASSID */

पूर्णांक __init ip_rt_init(व्योम)
अणु
	व्योम *idents_hash;
	पूर्णांक cpu;

	/* For modern hosts, this will use 2 MB of memory */
	idents_hash = alloc_large_प्रणाली_hash("IP idents",
					      माप(*ip_idents) + माप(*ip_tstamps),
					      0,
					      16, /* one bucket per 64 KB */
					      HASH_ZERO,
					      शून्य,
					      &ip_idents_mask,
					      2048,
					      256*1024);

	ip_idents = idents_hash;

	pअक्रमom_bytes(ip_idents, (ip_idents_mask + 1) * माप(*ip_idents));

	ip_tstamps = idents_hash + (ip_idents_mask + 1) * माप(*ip_idents);

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा uncached_list *ul = &per_cpu(rt_uncached_list, cpu);

		INIT_LIST_HEAD(&ul->head);
		spin_lock_init(&ul->lock);
	पूर्ण
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	ip_rt_acct = __alloc_percpu(256 * माप(काष्ठा ip_rt_acct), __alignof__(काष्ठा ip_rt_acct));
	अगर (!ip_rt_acct)
		panic("IP: failed to allocate ip_rt_acct\n");
#पूर्ण_अगर

	ipv4_dst_ops.kmem_cachep =
		kmem_cache_create("ip_dst_cache", माप(काष्ठा rtable), 0,
				  SLAB_HWCACHE_ALIGN|SLAB_PANIC, शून्य);

	ipv4_dst_blackhole_ops.kmem_cachep = ipv4_dst_ops.kmem_cachep;

	अगर (dst_entries_init(&ipv4_dst_ops) < 0)
		panic("IP: failed to allocate ipv4_dst_ops counter\n");

	अगर (dst_entries_init(&ipv4_dst_blackhole_ops) < 0)
		panic("IP: failed to allocate ipv4_dst_blackhole_ops counter\n");

	ipv4_dst_ops.gc_thresh = ~0;
	ip_rt_max_size = पूर्णांक_उच्च;

	devinet_init();
	ip_fib_init();

	अगर (ip_rt_proc_init())
		pr_err("Unable to create route proc files\n");
#अगर_घोषित CONFIG_XFRM
	xfrm_init();
	xfrm4_init();
#पूर्ण_अगर
	rtnl_रेजिस्टर(PF_INET, RTM_GETROUTE, inet_rपंचांग_getroute, शून्य,
		      RTNL_FLAG_DOIT_UNLOCKED);

#अगर_घोषित CONFIG_SYSCTL
	रेजिस्टर_pernet_subsys(&sysctl_route_ops);
#पूर्ण_अगर
	रेजिस्टर_pernet_subsys(&rt_genid_ops);
	रेजिस्टर_pernet_subsys(&ipv4_inetpeer_ops);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SYSCTL
/*
 * We really need to sanitize the damn ipv4 init order, then all
 * this nonsense will go away.
 */
व्योम __init ip_अटल_sysctl_init(व्योम)
अणु
	रेजिस्टर_net_sysctl(&init_net, "net/ipv4/route", ipv4_route_table);
पूर्ण
#पूर्ण_अगर
