<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Connection state tracking क्रम netfilter.  This is separated from,
   but required by, the NAT layer; it can also be used by an iptables
   extension. */

/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2006 Netfilter Core Team <coreteam@netfilter.org>
 * (C) 2003,2004 USAGI/WIDE Project <http://www.linux-ipv6.org>
 * (C) 2005-2012 Patrick McHardy <kaber@trash.net>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/slab.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/jhash.h>
#समावेश <linux/siphash.h>
#समावेश <linux/err.h>
#समावेश <linux/percpu.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/socket.h>
#समावेश <linux/mm.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/rculist_nulls.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_l4proto.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_seqadj.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_extend.h>
#समावेश <net/netfilter/nf_conntrack_acct.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>
#समावेश <net/netfilter/nf_conntrack_बारtamp.h>
#समावेश <net/netfilter/nf_conntrack_समयout.h>
#समावेश <net/netfilter/nf_conntrack_labels.h>
#समावेश <net/netfilter/nf_conntrack_synproxy.h>
#समावेश <net/netfilter/nf_nat.h>
#समावेश <net/netfilter/nf_nat_helper.h>
#समावेश <net/netns/hash.h>
#समावेश <net/ip.h>

#समावेश "nf_internals.h"

बाह्य अचिन्हित पूर्णांक nf_conntrack_net_id;

__cacheline_aligned_in_smp spinlock_t nf_conntrack_locks[CONNTRACK_LOCKS];
EXPORT_SYMBOL_GPL(nf_conntrack_locks);

__cacheline_aligned_in_smp DEFINE_SPINLOCK(nf_conntrack_expect_lock);
EXPORT_SYMBOL_GPL(nf_conntrack_expect_lock);

काष्ठा hlist_nulls_head *nf_conntrack_hash __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nf_conntrack_hash);

काष्ठा conntrack_gc_work अणु
	काष्ठा delayed_work	dwork;
	u32			last_bucket;
	bool			निकासing;
	bool			early_drop;
	दीर्घ			next_gc_run;
पूर्ण;

अटल __पढ़ो_mostly काष्ठा kmem_cache *nf_conntrack_cachep;
अटल DEFINE_SPINLOCK(nf_conntrack_locks_all_lock);
अटल __पढ़ो_mostly bool nf_conntrack_locks_all;

/* every gc cycle scans at most 1/GC_MAX_BUCKETS_DIV part of table */
#घोषणा GC_MAX_BUCKETS_DIV	128u
/* upper bound of full table scan */
#घोषणा GC_MAX_SCAN_JIFFIES	(16u * HZ)
/* desired ratio of entries found to be expired */
#घोषणा GC_EVICT_RATIO	50u

अटल काष्ठा conntrack_gc_work conntrack_gc_work;

बाह्य अचिन्हित पूर्णांक nf_conntrack_net_id;

व्योम nf_conntrack_lock(spinlock_t *lock) __acquires(lock)
अणु
	/* 1) Acquire the lock */
	spin_lock(lock);

	/* 2) पढ़ो nf_conntrack_locks_all, with ACQUIRE semantics
	 * It pairs with the smp_store_release() in nf_conntrack_all_unlock()
	 */
	अगर (likely(smp_load_acquire(&nf_conntrack_locks_all) == false))
		वापस;

	/* fast path failed, unlock */
	spin_unlock(lock);

	/* Slow path 1) get global lock */
	spin_lock(&nf_conntrack_locks_all_lock);

	/* Slow path 2) get the lock we want */
	spin_lock(lock);

	/* Slow path 3) release the global lock */
	spin_unlock(&nf_conntrack_locks_all_lock);
पूर्ण
EXPORT_SYMBOL_GPL(nf_conntrack_lock);

अटल व्योम nf_conntrack_द्विगुन_unlock(अचिन्हित पूर्णांक h1, अचिन्हित पूर्णांक h2)
अणु
	h1 %= CONNTRACK_LOCKS;
	h2 %= CONNTRACK_LOCKS;
	spin_unlock(&nf_conntrack_locks[h1]);
	अगर (h1 != h2)
		spin_unlock(&nf_conntrack_locks[h2]);
पूर्ण

/* वापस true अगर we need to recompute hashes (in हाल hash table was resized) */
अटल bool nf_conntrack_द्विगुन_lock(काष्ठा net *net, अचिन्हित पूर्णांक h1,
				     अचिन्हित पूर्णांक h2, अचिन्हित पूर्णांक sequence)
अणु
	h1 %= CONNTRACK_LOCKS;
	h2 %= CONNTRACK_LOCKS;
	अगर (h1 <= h2) अणु
		nf_conntrack_lock(&nf_conntrack_locks[h1]);
		अगर (h1 != h2)
			spin_lock_nested(&nf_conntrack_locks[h2],
					 SINGLE_DEPTH_NESTING);
	पूर्ण अन्यथा अणु
		nf_conntrack_lock(&nf_conntrack_locks[h2]);
		spin_lock_nested(&nf_conntrack_locks[h1],
				 SINGLE_DEPTH_NESTING);
	पूर्ण
	अगर (पढ़ो_seqcount_retry(&nf_conntrack_generation, sequence)) अणु
		nf_conntrack_द्विगुन_unlock(h1, h2);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम nf_conntrack_all_lock(व्योम)
	__acquires(&nf_conntrack_locks_all_lock)
अणु
	पूर्णांक i;

	spin_lock(&nf_conntrack_locks_all_lock);

	nf_conntrack_locks_all = true;

	क्रम (i = 0; i < CONNTRACK_LOCKS; i++) अणु
		spin_lock(&nf_conntrack_locks[i]);

		/* This spin_unlock provides the "release" to ensure that
		 * nf_conntrack_locks_all==true is visible to everyone that
		 * acquired spin_lock(&nf_conntrack_locks[]).
		 */
		spin_unlock(&nf_conntrack_locks[i]);
	पूर्ण
पूर्ण

अटल व्योम nf_conntrack_all_unlock(व्योम)
	__releases(&nf_conntrack_locks_all_lock)
अणु
	/* All prior stores must be complete beक्रमe we clear
	 * 'nf_conntrack_locks_all'. Otherwise nf_conntrack_lock()
	 * might observe the false value but not the entire
	 * critical section.
	 * It pairs with the smp_load_acquire() in nf_conntrack_lock()
	 */
	smp_store_release(&nf_conntrack_locks_all, false);
	spin_unlock(&nf_conntrack_locks_all_lock);
पूर्ण

अचिन्हित पूर्णांक nf_conntrack_htable_size __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nf_conntrack_htable_size);

अचिन्हित पूर्णांक nf_conntrack_max __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nf_conntrack_max);
seqcount_spinlock_t nf_conntrack_generation __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक nf_conntrack_hash_rnd __पढ़ो_mostly;

अटल u32 hash_conntrack_raw(स्थिर काष्ठा nf_conntrack_tuple *tuple,
			      स्थिर काष्ठा net *net)
अणु
	अचिन्हित पूर्णांक n;
	u32 seed;

	get_अक्रमom_once(&nf_conntrack_hash_rnd, माप(nf_conntrack_hash_rnd));

	/* The direction must be ignored, so we hash everything up to the
	 * destination ports (which is a multiple of 4) and treat the last
	 * three bytes manually.
	 */
	seed = nf_conntrack_hash_rnd ^ net_hash_mix(net);
	n = (माप(tuple->src) + माप(tuple->dst.u3)) / माप(u32);
	वापस jhash2((u32 *)tuple, n, seed ^
		      (((__क्रमce __u16)tuple->dst.u.all << 16) |
		      tuple->dst.protonum));
पूर्ण

अटल u32 scale_hash(u32 hash)
अणु
	वापस reciprocal_scale(hash, nf_conntrack_htable_size);
पूर्ण

अटल u32 __hash_conntrack(स्थिर काष्ठा net *net,
			    स्थिर काष्ठा nf_conntrack_tuple *tuple,
			    अचिन्हित पूर्णांक size)
अणु
	वापस reciprocal_scale(hash_conntrack_raw(tuple, net), size);
पूर्ण

अटल u32 hash_conntrack(स्थिर काष्ठा net *net,
			  स्थिर काष्ठा nf_conntrack_tuple *tuple)
अणु
	वापस scale_hash(hash_conntrack_raw(tuple, net));
पूर्ण

अटल bool nf_ct_get_tuple_ports(स्थिर काष्ठा sk_buff *skb,
				  अचिन्हित पूर्णांक dataoff,
				  काष्ठा nf_conntrack_tuple *tuple)
अणु	काष्ठा अणु
		__be16 sport;
		__be16 dport;
	पूर्ण _inet_hdr, *inet_hdr;

	/* Actually only need first 4 bytes to get ports. */
	inet_hdr = skb_header_poपूर्णांकer(skb, dataoff, माप(_inet_hdr), &_inet_hdr);
	अगर (!inet_hdr)
		वापस false;

	tuple->src.u.udp.port = inet_hdr->sport;
	tuple->dst.u.udp.port = inet_hdr->dport;
	वापस true;
पूर्ण

अटल bool
nf_ct_get_tuple(स्थिर काष्ठा sk_buff *skb,
		अचिन्हित पूर्णांक nhoff,
		अचिन्हित पूर्णांक dataoff,
		u_पूर्णांक16_t l3num,
		u_पूर्णांक8_t protonum,
		काष्ठा net *net,
		काष्ठा nf_conntrack_tuple *tuple)
अणु
	अचिन्हित पूर्णांक size;
	स्थिर __be32 *ap;
	__be32 _addrs[8];

	स_रखो(tuple, 0, माप(*tuple));

	tuple->src.l3num = l3num;
	चयन (l3num) अणु
	हाल NFPROTO_IPV4:
		nhoff += दुरत्व(काष्ठा iphdr, saddr);
		size = 2 * माप(__be32);
		अवरोध;
	हाल NFPROTO_IPV6:
		nhoff += दुरत्व(काष्ठा ipv6hdr, saddr);
		size = माप(_addrs);
		अवरोध;
	शेष:
		वापस true;
	पूर्ण

	ap = skb_header_poपूर्णांकer(skb, nhoff, size, _addrs);
	अगर (!ap)
		वापस false;

	चयन (l3num) अणु
	हाल NFPROTO_IPV4:
		tuple->src.u3.ip = ap[0];
		tuple->dst.u3.ip = ap[1];
		अवरोध;
	हाल NFPROTO_IPV6:
		स_नकल(tuple->src.u3.ip6, ap, माप(tuple->src.u3.ip6));
		स_नकल(tuple->dst.u3.ip6, ap + 4, माप(tuple->dst.u3.ip6));
		अवरोध;
	पूर्ण

	tuple->dst.protonum = protonum;
	tuple->dst.dir = IP_CT_सूची_ORIGINAL;

	चयन (protonum) अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल IPPROTO_ICMPV6:
		वापस icmpv6_pkt_to_tuple(skb, dataoff, net, tuple);
#पूर्ण_अगर
	हाल IPPROTO_ICMP:
		वापस icmp_pkt_to_tuple(skb, dataoff, net, tuple);
#अगर_घोषित CONFIG_NF_CT_PROTO_GRE
	हाल IPPROTO_GRE:
		वापस gre_pkt_to_tuple(skb, dataoff, net, tuple);
#पूर्ण_अगर
	हाल IPPROTO_TCP:
	हाल IPPROTO_UDP: /* fallthrough */
		वापस nf_ct_get_tuple_ports(skb, dataoff, tuple);
#अगर_घोषित CONFIG_NF_CT_PROTO_UDPLITE
	हाल IPPROTO_UDPLITE:
		वापस nf_ct_get_tuple_ports(skb, dataoff, tuple);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_SCTP
	हाल IPPROTO_SCTP:
		वापस nf_ct_get_tuple_ports(skb, dataoff, tuple);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_DCCP
	हाल IPPROTO_DCCP:
		वापस nf_ct_get_tuple_ports(skb, dataoff, tuple);
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक ipv4_get_l4proto(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक nhoff,
			    u_पूर्णांक8_t *protonum)
अणु
	पूर्णांक dataoff = -1;
	स्थिर काष्ठा iphdr *iph;
	काष्ठा iphdr _iph;

	iph = skb_header_poपूर्णांकer(skb, nhoff, माप(_iph), &_iph);
	अगर (!iph)
		वापस -1;

	/* Conntrack defragments packets, we might still see fragments
	 * inside ICMP packets though.
	 */
	अगर (iph->frag_off & htons(IP_OFFSET))
		वापस -1;

	dataoff = nhoff + (iph->ihl << 2);
	*protonum = iph->protocol;

	/* Check bogus IP headers */
	अगर (dataoff > skb->len) अणु
		pr_debug("bogus IPv4 packet: nhoff %u, ihl %u, skblen %u\n",
			 nhoff, iph->ihl << 2, skb->len);
		वापस -1;
	पूर्ण
	वापस dataoff;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक ipv6_get_l4proto(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक nhoff,
			    u8 *protonum)
अणु
	पूर्णांक protoff = -1;
	अचिन्हित पूर्णांक extoff = nhoff + माप(काष्ठा ipv6hdr);
	__be16 frag_off;
	u8 nexthdr;

	अगर (skb_copy_bits(skb, nhoff + दुरत्व(काष्ठा ipv6hdr, nexthdr),
			  &nexthdr, माप(nexthdr)) != 0) अणु
		pr_debug("can't get nexthdr\n");
		वापस -1;
	पूर्ण
	protoff = ipv6_skip_exthdr(skb, extoff, &nexthdr, &frag_off);
	/*
	 * (protoff == skb->len) means the packet has not data, just
	 * IPv6 and possibly extensions headers, but it is tracked anyway
	 */
	अगर (protoff < 0 || (frag_off & htons(~0x7)) != 0) अणु
		pr_debug("can't find proto in pkt\n");
		वापस -1;
	पूर्ण

	*protonum = nexthdr;
	वापस protoff;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक get_l4proto(स्थिर काष्ठा sk_buff *skb,
		       अचिन्हित पूर्णांक nhoff, u8 pf, u8 *l4num)
अणु
	चयन (pf) अणु
	हाल NFPROTO_IPV4:
		वापस ipv4_get_l4proto(skb, nhoff, l4num);
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल NFPROTO_IPV6:
		वापस ipv6_get_l4proto(skb, nhoff, l4num);
#पूर्ण_अगर
	शेष:
		*l4num = 0;
		अवरोध;
	पूर्ण
	वापस -1;
पूर्ण

bool nf_ct_get_tuplepr(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक nhoff,
		       u_पूर्णांक16_t l3num,
		       काष्ठा net *net, काष्ठा nf_conntrack_tuple *tuple)
अणु
	u8 protonum;
	पूर्णांक protoff;

	protoff = get_l4proto(skb, nhoff, l3num, &protonum);
	अगर (protoff <= 0)
		वापस false;

	वापस nf_ct_get_tuple(skb, nhoff, protoff, l3num, protonum, net, tuple);
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_get_tuplepr);

bool
nf_ct_invert_tuple(काष्ठा nf_conntrack_tuple *inverse,
		   स्थिर काष्ठा nf_conntrack_tuple *orig)
अणु
	स_रखो(inverse, 0, माप(*inverse));

	inverse->src.l3num = orig->src.l3num;

	चयन (orig->src.l3num) अणु
	हाल NFPROTO_IPV4:
		inverse->src.u3.ip = orig->dst.u3.ip;
		inverse->dst.u3.ip = orig->src.u3.ip;
		अवरोध;
	हाल NFPROTO_IPV6:
		inverse->src.u3.in6 = orig->dst.u3.in6;
		inverse->dst.u3.in6 = orig->src.u3.in6;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	inverse->dst.dir = !orig->dst.dir;

	inverse->dst.protonum = orig->dst.protonum;

	चयन (orig->dst.protonum) अणु
	हाल IPPROTO_ICMP:
		वापस nf_conntrack_invert_icmp_tuple(inverse, orig);
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल IPPROTO_ICMPV6:
		वापस nf_conntrack_invert_icmpv6_tuple(inverse, orig);
#पूर्ण_अगर
	पूर्ण

	inverse->src.u.all = orig->dst.u.all;
	inverse->dst.u.all = orig->src.u.all;
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_invert_tuple);

/* Generate a almost-unique pseuकरो-id क्रम a given conntrack.
 *
 * पूर्णांकentionally करोesn't re-use any of the seeds used क्रम hash
 * table location, we assume id माला_लो exposed to userspace.
 *
 * Following nf_conn items करो not change throughout lअगरeसमय
 * of the nf_conn:
 *
 * 1. nf_conn address
 * 2. nf_conn->master address (normally शून्य)
 * 3. the associated net namespace
 * 4. the original direction tuple
 */
u32 nf_ct_get_id(स्थिर काष्ठा nf_conn *ct)
अणु
	अटल __पढ़ो_mostly siphash_key_t ct_id_seed;
	अचिन्हित दीर्घ a, b, c, d;

	net_get_अक्रमom_once(&ct_id_seed, माप(ct_id_seed));

	a = (अचिन्हित दीर्घ)ct;
	b = (अचिन्हित दीर्घ)ct->master;
	c = (अचिन्हित दीर्घ)nf_ct_net(ct);
	d = (अचिन्हित दीर्घ)siphash(&ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple,
				   माप(ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple),
				   &ct_id_seed);
#अगर_घोषित CONFIG_64BIT
	वापस siphash_4u64((u64)a, (u64)b, (u64)c, (u64)d, &ct_id_seed);
#अन्यथा
	वापस siphash_4u32((u32)a, (u32)b, (u32)c, (u32)d, &ct_id_seed);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_get_id);

अटल व्योम
clean_from_lists(काष्ठा nf_conn *ct)
अणु
	pr_debug("clean_from_lists(%p)\n", ct);
	hlist_nulls_del_rcu(&ct->tuplehash[IP_CT_सूची_ORIGINAL].hnnode);
	hlist_nulls_del_rcu(&ct->tuplehash[IP_CT_सूची_REPLY].hnnode);

	/* Destroy all pending expectations */
	nf_ct_हटाओ_expectations(ct);
पूर्ण

/* must be called with local_bh_disable */
अटल व्योम nf_ct_add_to_dying_list(काष्ठा nf_conn *ct)
अणु
	काष्ठा ct_pcpu *pcpu;

	/* add this conntrack to the (per cpu) dying list */
	ct->cpu = smp_processor_id();
	pcpu = per_cpu_ptr(nf_ct_net(ct)->ct.pcpu_lists, ct->cpu);

	spin_lock(&pcpu->lock);
	hlist_nulls_add_head(&ct->tuplehash[IP_CT_सूची_ORIGINAL].hnnode,
			     &pcpu->dying);
	spin_unlock(&pcpu->lock);
पूर्ण

/* must be called with local_bh_disable */
अटल व्योम nf_ct_add_to_unconfirmed_list(काष्ठा nf_conn *ct)
अणु
	काष्ठा ct_pcpu *pcpu;

	/* add this conntrack to the (per cpu) unconfirmed list */
	ct->cpu = smp_processor_id();
	pcpu = per_cpu_ptr(nf_ct_net(ct)->ct.pcpu_lists, ct->cpu);

	spin_lock(&pcpu->lock);
	hlist_nulls_add_head(&ct->tuplehash[IP_CT_सूची_ORIGINAL].hnnode,
			     &pcpu->unconfirmed);
	spin_unlock(&pcpu->lock);
पूर्ण

/* must be called with local_bh_disable */
अटल व्योम nf_ct_del_from_dying_or_unconfirmed_list(काष्ठा nf_conn *ct)
अणु
	काष्ठा ct_pcpu *pcpu;

	/* We overload first tuple to link पूर्णांकo unconfirmed or dying list.*/
	pcpu = per_cpu_ptr(nf_ct_net(ct)->ct.pcpu_lists, ct->cpu);

	spin_lock(&pcpu->lock);
	BUG_ON(hlist_nulls_unhashed(&ct->tuplehash[IP_CT_सूची_ORIGINAL].hnnode));
	hlist_nulls_del_rcu(&ct->tuplehash[IP_CT_सूची_ORIGINAL].hnnode);
	spin_unlock(&pcpu->lock);
पूर्ण

#घोषणा NFCT_ALIGN(len)	(((len) + NFCT_INFOMASK) & ~NFCT_INFOMASK)

/* Released via destroy_conntrack() */
काष्ठा nf_conn *nf_ct_पंचांगpl_alloc(काष्ठा net *net,
				 स्थिर काष्ठा nf_conntrack_zone *zone,
				 gfp_t flags)
अणु
	काष्ठा nf_conn *पंचांगpl, *p;

	अगर (ARCH_KMALLOC_MINALIGN <= NFCT_INFOMASK) अणु
		पंचांगpl = kzalloc(माप(*पंचांगpl) + NFCT_INFOMASK, flags);
		अगर (!पंचांगpl)
			वापस शून्य;

		p = पंचांगpl;
		पंचांगpl = (काष्ठा nf_conn *)NFCT_ALIGN((अचिन्हित दीर्घ)p);
		अगर (पंचांगpl != p) अणु
			पंचांगpl = (काष्ठा nf_conn *)NFCT_ALIGN((अचिन्हित दीर्घ)p);
			पंचांगpl->proto.पंचांगpl_padto = (अक्षर *)पंचांगpl - (अक्षर *)p;
		पूर्ण
	पूर्ण अन्यथा अणु
		पंचांगpl = kzalloc(माप(*पंचांगpl), flags);
		अगर (!पंचांगpl)
			वापस शून्य;
	पूर्ण

	पंचांगpl->status = IPS_TEMPLATE;
	ग_लिखो_pnet(&पंचांगpl->ct_net, net);
	nf_ct_zone_add(पंचांगpl, zone);
	atomic_set(&पंचांगpl->ct_general.use, 0);

	वापस पंचांगpl;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_पंचांगpl_alloc);

व्योम nf_ct_पंचांगpl_मुक्त(काष्ठा nf_conn *पंचांगpl)
अणु
	nf_ct_ext_destroy(पंचांगpl);

	अगर (ARCH_KMALLOC_MINALIGN <= NFCT_INFOMASK)
		kमुक्त((अक्षर *)पंचांगpl - पंचांगpl->proto.पंचांगpl_padto);
	अन्यथा
		kमुक्त(पंचांगpl);
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_पंचांगpl_मुक्त);

अटल व्योम destroy_gre_conntrack(काष्ठा nf_conn *ct)
अणु
#अगर_घोषित CONFIG_NF_CT_PROTO_GRE
	काष्ठा nf_conn *master = ct->master;

	अगर (master)
		nf_ct_gre_keymap_destroy(master);
#पूर्ण_अगर
पूर्ण

अटल व्योम
destroy_conntrack(काष्ठा nf_conntrack *nfct)
अणु
	काष्ठा nf_conn *ct = (काष्ठा nf_conn *)nfct;

	pr_debug("destroy_conntrack(%p)\n", ct);
	WARN_ON(atomic_पढ़ो(&nfct->use) != 0);

	अगर (unlikely(nf_ct_is_ढाँचा(ct))) अणु
		nf_ct_पंचांगpl_मुक्त(ct);
		वापस;
	पूर्ण

	अगर (unlikely(nf_ct_protonum(ct) == IPPROTO_GRE))
		destroy_gre_conntrack(ct);

	local_bh_disable();
	/* Expectations will have been हटाओd in clean_from_lists,
	 * except TFTP can create an expectation on the first packet,
	 * beक्रमe connection is in the list, so we need to clean here,
	 * too.
	 */
	nf_ct_हटाओ_expectations(ct);

	nf_ct_del_from_dying_or_unconfirmed_list(ct);

	local_bh_enable();

	अगर (ct->master)
		nf_ct_put(ct->master);

	pr_debug("destroy_conntrack: returning ct=%p to slab\n", ct);
	nf_conntrack_मुक्त(ct);
पूर्ण

अटल व्योम nf_ct_delete_from_lists(काष्ठा nf_conn *ct)
अणु
	काष्ठा net *net = nf_ct_net(ct);
	अचिन्हित पूर्णांक hash, reply_hash;
	अचिन्हित पूर्णांक sequence;

	nf_ct_helper_destroy(ct);

	local_bh_disable();
	करो अणु
		sequence = पढ़ो_seqcount_begin(&nf_conntrack_generation);
		hash = hash_conntrack(net,
				      &ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple);
		reply_hash = hash_conntrack(net,
					   &ct->tuplehash[IP_CT_सूची_REPLY].tuple);
	पूर्ण जबतक (nf_conntrack_द्विगुन_lock(net, hash, reply_hash, sequence));

	clean_from_lists(ct);
	nf_conntrack_द्विगुन_unlock(hash, reply_hash);

	nf_ct_add_to_dying_list(ct);

	local_bh_enable();
पूर्ण

bool nf_ct_delete(काष्ठा nf_conn *ct, u32 portid, पूर्णांक report)
अणु
	काष्ठा nf_conn_tstamp *tstamp;
	काष्ठा net *net;

	अगर (test_and_set_bit(IPS_DYING_BIT, &ct->status))
		वापस false;

	tstamp = nf_conn_tstamp_find(ct);
	अगर (tstamp && tstamp->stop == 0)
		tstamp->stop = kसमय_get_real_ns();

	अगर (nf_conntrack_event_report(IPCT_DESTROY, ct,
				    portid, report) < 0) अणु
		/* destroy event was not delivered. nf_ct_put will
		 * be करोne by event cache worker on redelivery.
		 */
		nf_ct_delete_from_lists(ct);
		nf_conntrack_ecache_work(nf_ct_net(ct), NFCT_ECACHE_DESTROY_FAIL);
		वापस false;
	पूर्ण

	net = nf_ct_net(ct);
	अगर (nf_conntrack_ecache_dwork_pending(net))
		nf_conntrack_ecache_work(net, NFCT_ECACHE_DESTROY_SENT);
	nf_ct_delete_from_lists(ct);
	nf_ct_put(ct);
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_delete);

अटल अंतरभूत bool
nf_ct_key_equal(काष्ठा nf_conntrack_tuple_hash *h,
		स्थिर काष्ठा nf_conntrack_tuple *tuple,
		स्थिर काष्ठा nf_conntrack_zone *zone,
		स्थिर काष्ठा net *net)
अणु
	काष्ठा nf_conn *ct = nf_ct_tuplehash_to_ctrack(h);

	/* A conntrack can be recreated with the equal tuple,
	 * so we need to check that the conntrack is confirmed
	 */
	वापस nf_ct_tuple_equal(tuple, &h->tuple) &&
	       nf_ct_zone_equal(ct, zone, NF_CT_सूचीECTION(h)) &&
	       nf_ct_is_confirmed(ct) &&
	       net_eq(net, nf_ct_net(ct));
पूर्ण

अटल अंतरभूत bool
nf_ct_match(स्थिर काष्ठा nf_conn *ct1, स्थिर काष्ठा nf_conn *ct2)
अणु
	वापस nf_ct_tuple_equal(&ct1->tuplehash[IP_CT_सूची_ORIGINAL].tuple,
				 &ct2->tuplehash[IP_CT_सूची_ORIGINAL].tuple) &&
	       nf_ct_tuple_equal(&ct1->tuplehash[IP_CT_सूची_REPLY].tuple,
				 &ct2->tuplehash[IP_CT_सूची_REPLY].tuple) &&
	       nf_ct_zone_equal(ct1, nf_ct_zone(ct2), IP_CT_सूची_ORIGINAL) &&
	       nf_ct_zone_equal(ct1, nf_ct_zone(ct2), IP_CT_सूची_REPLY) &&
	       net_eq(nf_ct_net(ct1), nf_ct_net(ct2));
पूर्ण

/* caller must hold rcu पढ़ोlock and none of the nf_conntrack_locks */
अटल व्योम nf_ct_gc_expired(काष्ठा nf_conn *ct)
अणु
	अगर (!atomic_inc_not_zero(&ct->ct_general.use))
		वापस;

	अगर (nf_ct_should_gc(ct))
		nf_ct_समाप्त(ct);

	nf_ct_put(ct);
पूर्ण

/*
 * Warning :
 * - Caller must take a reference on वापसed object
 *   and recheck nf_ct_tuple_equal(tuple, &h->tuple)
 */
अटल काष्ठा nf_conntrack_tuple_hash *
____nf_conntrack_find(काष्ठा net *net, स्थिर काष्ठा nf_conntrack_zone *zone,
		      स्थिर काष्ठा nf_conntrack_tuple *tuple, u32 hash)
अणु
	काष्ठा nf_conntrack_tuple_hash *h;
	काष्ठा hlist_nulls_head *ct_hash;
	काष्ठा hlist_nulls_node *n;
	अचिन्हित पूर्णांक bucket, hsize;

begin:
	nf_conntrack_get_ht(&ct_hash, &hsize);
	bucket = reciprocal_scale(hash, hsize);

	hlist_nulls_क्रम_each_entry_rcu(h, n, &ct_hash[bucket], hnnode) अणु
		काष्ठा nf_conn *ct;

		ct = nf_ct_tuplehash_to_ctrack(h);
		अगर (nf_ct_is_expired(ct)) अणु
			nf_ct_gc_expired(ct);
			जारी;
		पूर्ण

		अगर (nf_ct_key_equal(h, tuple, zone, net))
			वापस h;
	पूर्ण
	/*
	 * अगर the nulls value we got at the end of this lookup is
	 * not the expected one, we must restart lookup.
	 * We probably met an item that was moved to another chain.
	 */
	अगर (get_nulls_value(n) != bucket) अणु
		NF_CT_STAT_INC_ATOMIC(net, search_restart);
		जाओ begin;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Find a connection corresponding to a tuple. */
अटल काष्ठा nf_conntrack_tuple_hash *
__nf_conntrack_find_get(काष्ठा net *net, स्थिर काष्ठा nf_conntrack_zone *zone,
			स्थिर काष्ठा nf_conntrack_tuple *tuple, u32 hash)
अणु
	काष्ठा nf_conntrack_tuple_hash *h;
	काष्ठा nf_conn *ct;

	rcu_पढ़ो_lock();

	h = ____nf_conntrack_find(net, zone, tuple, hash);
	अगर (h) अणु
		/* We have a candidate that matches the tuple we're पूर्णांकerested
		 * in, try to obtain a reference and re-check tuple
		 */
		ct = nf_ct_tuplehash_to_ctrack(h);
		अगर (likely(atomic_inc_not_zero(&ct->ct_general.use))) अणु
			अगर (likely(nf_ct_key_equal(h, tuple, zone, net)))
				जाओ found;

			/* TYPESAFE_BY_RCU recycled the candidate */
			nf_ct_put(ct);
		पूर्ण

		h = शून्य;
	पूर्ण
found:
	rcu_पढ़ो_unlock();

	वापस h;
पूर्ण

काष्ठा nf_conntrack_tuple_hash *
nf_conntrack_find_get(काष्ठा net *net, स्थिर काष्ठा nf_conntrack_zone *zone,
		      स्थिर काष्ठा nf_conntrack_tuple *tuple)
अणु
	वापस __nf_conntrack_find_get(net, zone, tuple,
				       hash_conntrack_raw(tuple, net));
पूर्ण
EXPORT_SYMBOL_GPL(nf_conntrack_find_get);

अटल व्योम __nf_conntrack_hash_insert(काष्ठा nf_conn *ct,
				       अचिन्हित पूर्णांक hash,
				       अचिन्हित पूर्णांक reply_hash)
अणु
	hlist_nulls_add_head_rcu(&ct->tuplehash[IP_CT_सूची_ORIGINAL].hnnode,
			   &nf_conntrack_hash[hash]);
	hlist_nulls_add_head_rcu(&ct->tuplehash[IP_CT_सूची_REPLY].hnnode,
			   &nf_conntrack_hash[reply_hash]);
पूर्ण

पूर्णांक
nf_conntrack_hash_check_insert(काष्ठा nf_conn *ct)
अणु
	स्थिर काष्ठा nf_conntrack_zone *zone;
	काष्ठा net *net = nf_ct_net(ct);
	अचिन्हित पूर्णांक hash, reply_hash;
	काष्ठा nf_conntrack_tuple_hash *h;
	काष्ठा hlist_nulls_node *n;
	अचिन्हित पूर्णांक sequence;

	zone = nf_ct_zone(ct);

	local_bh_disable();
	करो अणु
		sequence = पढ़ो_seqcount_begin(&nf_conntrack_generation);
		hash = hash_conntrack(net,
				      &ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple);
		reply_hash = hash_conntrack(net,
					   &ct->tuplehash[IP_CT_सूची_REPLY].tuple);
	पूर्ण जबतक (nf_conntrack_द्विगुन_lock(net, hash, reply_hash, sequence));

	/* See अगर there's one in the list alपढ़ोy, including reverse */
	hlist_nulls_क्रम_each_entry(h, n, &nf_conntrack_hash[hash], hnnode)
		अगर (nf_ct_key_equal(h, &ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple,
				    zone, net))
			जाओ out;

	hlist_nulls_क्रम_each_entry(h, n, &nf_conntrack_hash[reply_hash], hnnode)
		अगर (nf_ct_key_equal(h, &ct->tuplehash[IP_CT_सूची_REPLY].tuple,
				    zone, net))
			जाओ out;

	smp_wmb();
	/* The caller holds a reference to this object */
	atomic_set(&ct->ct_general.use, 2);
	__nf_conntrack_hash_insert(ct, hash, reply_hash);
	nf_conntrack_द्विगुन_unlock(hash, reply_hash);
	NF_CT_STAT_INC(net, insert);
	local_bh_enable();
	वापस 0;

out:
	nf_conntrack_द्विगुन_unlock(hash, reply_hash);
	local_bh_enable();
	वापस -EEXIST;
पूर्ण
EXPORT_SYMBOL_GPL(nf_conntrack_hash_check_insert);

व्योम nf_ct_acct_add(काष्ठा nf_conn *ct, u32 dir, अचिन्हित पूर्णांक packets,
		    अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा nf_conn_acct *acct;

	acct = nf_conn_acct_find(ct);
	अगर (acct) अणु
		काष्ठा nf_conn_counter *counter = acct->counter;

		atomic64_add(packets, &counter[dir].packets);
		atomic64_add(bytes, &counter[dir].bytes);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_acct_add);

अटल व्योम nf_ct_acct_merge(काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo,
			     स्थिर काष्ठा nf_conn *loser_ct)
अणु
	काष्ठा nf_conn_acct *acct;

	acct = nf_conn_acct_find(loser_ct);
	अगर (acct) अणु
		काष्ठा nf_conn_counter *counter = acct->counter;
		अचिन्हित पूर्णांक bytes;

		/* u32 should be fine since we must have seen one packet. */
		bytes = atomic64_पढ़ो(&counter[CTINFO2सूची(ctinfo)].bytes);
		nf_ct_acct_update(ct, CTINFO2सूची(ctinfo), bytes);
	पूर्ण
पूर्ण

अटल व्योम __nf_conntrack_insert_prepare(काष्ठा nf_conn *ct)
अणु
	काष्ठा nf_conn_tstamp *tstamp;

	atomic_inc(&ct->ct_general.use);
	ct->status |= IPS_CONFIRMED;

	/* set conntrack बारtamp, अगर enabled. */
	tstamp = nf_conn_tstamp_find(ct);
	अगर (tstamp)
		tstamp->start = kसमय_get_real_ns();
पूर्ण

/* caller must hold locks to prevent concurrent changes */
अटल पूर्णांक __nf_ct_resolve_clash(काष्ठा sk_buff *skb,
				 काष्ठा nf_conntrack_tuple_hash *h)
अणु
	/* This is the conntrack entry alपढ़ोy in hashes that won race. */
	काष्ठा nf_conn *ct = nf_ct_tuplehash_to_ctrack(h);
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *loser_ct;

	loser_ct = nf_ct_get(skb, &ctinfo);

	अगर (nf_ct_is_dying(ct))
		वापस NF_DROP;

	अगर (((ct->status & IPS_NAT_DONE_MASK) == 0) ||
	    nf_ct_match(ct, loser_ct)) अणु
		काष्ठा net *net = nf_ct_net(ct);

		nf_conntrack_get(&ct->ct_general);

		nf_ct_acct_merge(ct, ctinfo, loser_ct);
		nf_ct_add_to_dying_list(loser_ct);
		nf_conntrack_put(&loser_ct->ct_general);
		nf_ct_set(skb, ct, ctinfo);

		NF_CT_STAT_INC(net, clash_resolve);
		वापस NF_ACCEPT;
	पूर्ण

	वापस NF_DROP;
पूर्ण

/**
 * nf_ct_resolve_clash_harder - attempt to insert clashing conntrack entry
 *
 * @skb: skb that causes the collision
 * @repl_idx: hash slot क्रम reply direction
 *
 * Called when origin or reply direction had a clash.
 * The skb can be handled without packet drop provided the reply direction
 * is unique or there the existing entry has the identical tuple in both
 * directions.
 *
 * Caller must hold conntrack table locks to prevent concurrent updates.
 *
 * Returns NF_DROP अगर the clash could not be handled.
 */
अटल पूर्णांक nf_ct_resolve_clash_harder(काष्ठा sk_buff *skb, u32 repl_idx)
अणु
	काष्ठा nf_conn *loser_ct = (काष्ठा nf_conn *)skb_nfct(skb);
	स्थिर काष्ठा nf_conntrack_zone *zone;
	काष्ठा nf_conntrack_tuple_hash *h;
	काष्ठा hlist_nulls_node *n;
	काष्ठा net *net;

	zone = nf_ct_zone(loser_ct);
	net = nf_ct_net(loser_ct);

	/* Reply direction must never result in a clash, unless both origin
	 * and reply tuples are identical.
	 */
	hlist_nulls_क्रम_each_entry(h, n, &nf_conntrack_hash[repl_idx], hnnode) अणु
		अगर (nf_ct_key_equal(h,
				    &loser_ct->tuplehash[IP_CT_सूची_REPLY].tuple,
				    zone, net))
			वापस __nf_ct_resolve_clash(skb, h);
	पूर्ण

	/* We want the clashing entry to go away real soon: 1 second समयout. */
	loser_ct->समयout = nfct_समय_stamp + HZ;

	/* IPS_NAT_CLASH हटाओs the entry स्वतःmatically on the first
	 * reply.  Also prevents UDP tracker from moving the entry to
	 * ASSURED state, i.e. the entry can always be evicted under
	 * pressure.
	 */
	loser_ct->status |= IPS_FIXED_TIMEOUT | IPS_NAT_CLASH;

	__nf_conntrack_insert_prepare(loser_ct);

	/* fake add क्रम ORIGINAL dir: we want lookups to only find the entry
	 * alपढ़ोy in the table.  This also hides the clashing entry from
	 * ctnetlink iteration, i.e. conntrack -L won't show them.
	 */
	hlist_nulls_add_fake(&loser_ct->tuplehash[IP_CT_सूची_ORIGINAL].hnnode);

	hlist_nulls_add_head_rcu(&loser_ct->tuplehash[IP_CT_सूची_REPLY].hnnode,
				 &nf_conntrack_hash[repl_idx]);

	NF_CT_STAT_INC(net, clash_resolve);
	वापस NF_ACCEPT;
पूर्ण

/**
 * nf_ct_resolve_clash - attempt to handle clash without packet drop
 *
 * @skb: skb that causes the clash
 * @h: tuplehash of the clashing entry alपढ़ोy in table
 * @reply_hash: hash slot क्रम reply direction
 *
 * A conntrack entry can be inserted to the connection tracking table
 * अगर there is no existing entry with an identical tuple.
 *
 * If there is one, @skb (and the assocated, unconfirmed conntrack) has
 * to be dropped.  In हाल @skb is retransmitted, next conntrack lookup
 * will find the alपढ़ोy-existing entry.
 *
 * The major problem with such packet drop is the extra delay added by
 * the packet loss -- it will take some समय क्रम a retransmit to occur
 * (or the sender to समय out when रुकोing क्रम a reply).
 *
 * This function attempts to handle the situation without packet drop.
 *
 * If @skb has no NAT transक्रमmation or अगर the colliding entries are
 * exactly the same, only the to-be-confirmed conntrack entry is discarded
 * and @skb is associated with the conntrack entry alपढ़ोy in the table.
 *
 * Failing that, the new, unconfirmed conntrack is still added to the table
 * provided that the collision only occurs in the ORIGINAL direction.
 * The new entry will be added only in the non-clashing REPLY direction,
 * so packets in the ORIGINAL direction will जारी to match the existing
 * entry.  The new entry will also have a fixed समयout so it expires --
 * due to the collision, it will only see reply traffic.
 *
 * Returns NF_DROP अगर the clash could not be resolved.
 */
अटल __cold noअंतरभूत पूर्णांक
nf_ct_resolve_clash(काष्ठा sk_buff *skb, काष्ठा nf_conntrack_tuple_hash *h,
		    u32 reply_hash)
अणु
	/* This is the conntrack entry alपढ़ोy in hashes that won race. */
	काष्ठा nf_conn *ct = nf_ct_tuplehash_to_ctrack(h);
	स्थिर काष्ठा nf_conntrack_l4proto *l4proto;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *loser_ct;
	काष्ठा net *net;
	पूर्णांक ret;

	loser_ct = nf_ct_get(skb, &ctinfo);
	net = nf_ct_net(loser_ct);

	l4proto = nf_ct_l4proto_find(nf_ct_protonum(ct));
	अगर (!l4proto->allow_clash)
		जाओ drop;

	ret = __nf_ct_resolve_clash(skb, h);
	अगर (ret == NF_ACCEPT)
		वापस ret;

	ret = nf_ct_resolve_clash_harder(skb, reply_hash);
	अगर (ret == NF_ACCEPT)
		वापस ret;

drop:
	nf_ct_add_to_dying_list(loser_ct);
	NF_CT_STAT_INC(net, drop);
	NF_CT_STAT_INC(net, insert_failed);
	वापस NF_DROP;
पूर्ण

/* Confirm a connection given skb; places it in hash table */
पूर्णांक
__nf_conntrack_confirm(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा nf_conntrack_zone *zone;
	अचिन्हित पूर्णांक hash, reply_hash;
	काष्ठा nf_conntrack_tuple_hash *h;
	काष्ठा nf_conn *ct;
	काष्ठा nf_conn_help *help;
	काष्ठा hlist_nulls_node *n;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा net *net;
	अचिन्हित पूर्णांक sequence;
	पूर्णांक ret = NF_DROP;

	ct = nf_ct_get(skb, &ctinfo);
	net = nf_ct_net(ct);

	/* ipt_REJECT uses nf_conntrack_attach to attach related
	   ICMP/TCP RST packets in other direction.  Actual packet
	   which created connection will be IP_CT_NEW or क्रम an
	   expected connection, IP_CT_RELATED. */
	अगर (CTINFO2सूची(ctinfo) != IP_CT_सूची_ORIGINAL)
		वापस NF_ACCEPT;

	zone = nf_ct_zone(ct);
	local_bh_disable();

	करो अणु
		sequence = पढ़ो_seqcount_begin(&nf_conntrack_generation);
		/* reuse the hash saved beक्रमe */
		hash = *(अचिन्हित दीर्घ *)&ct->tuplehash[IP_CT_सूची_REPLY].hnnode.pprev;
		hash = scale_hash(hash);
		reply_hash = hash_conntrack(net,
					   &ct->tuplehash[IP_CT_सूची_REPLY].tuple);

	पूर्ण जबतक (nf_conntrack_द्विगुन_lock(net, hash, reply_hash, sequence));

	/* We're not in hash table, and we refuse to set up related
	 * connections क्रम unconfirmed conns.  But packet copies and
	 * REJECT will give spurious warnings here.
	 */

	/* Another skb with the same unconfirmed conntrack may
	 * win the race. This may happen क्रम bridge(br_flood)
	 * or broadcast/multicast packets करो skb_clone with
	 * unconfirmed conntrack.
	 */
	अगर (unlikely(nf_ct_is_confirmed(ct))) अणु
		WARN_ON_ONCE(1);
		nf_conntrack_द्विगुन_unlock(hash, reply_hash);
		local_bh_enable();
		वापस NF_DROP;
	पूर्ण

	pr_debug("Confirming conntrack %p\n", ct);
	/* We have to check the DYING flag after unlink to prevent
	 * a race against nf_ct_get_next_corpse() possibly called from
	 * user context, अन्यथा we insert an alपढ़ोy 'dead' hash, blocking
	 * further use of that particular connection -JM.
	 */
	nf_ct_del_from_dying_or_unconfirmed_list(ct);

	अगर (unlikely(nf_ct_is_dying(ct))) अणु
		nf_ct_add_to_dying_list(ct);
		NF_CT_STAT_INC(net, insert_failed);
		जाओ dying;
	पूर्ण

	/* See अगर there's one in the list alपढ़ोy, including reverse:
	   NAT could have grabbed it without realizing, since we're
	   not in the hash.  If there is, we lost race. */
	hlist_nulls_क्रम_each_entry(h, n, &nf_conntrack_hash[hash], hnnode)
		अगर (nf_ct_key_equal(h, &ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple,
				    zone, net))
			जाओ out;

	hlist_nulls_क्रम_each_entry(h, n, &nf_conntrack_hash[reply_hash], hnnode)
		अगर (nf_ct_key_equal(h, &ct->tuplehash[IP_CT_सूची_REPLY].tuple,
				    zone, net))
			जाओ out;

	/* Timer relative to confirmation समय, not original
	   setting समय, otherwise we'd get समयr wrap in
	   weird delay हालs. */
	ct->समयout += nfct_समय_stamp;

	__nf_conntrack_insert_prepare(ct);

	/* Since the lookup is lockless, hash insertion must be करोne after
	 * starting the समयr and setting the CONFIRMED bit. The RCU barriers
	 * guarantee that no other CPU can find the conntrack beक्रमe the above
	 * stores are visible.
	 */
	__nf_conntrack_hash_insert(ct, hash, reply_hash);
	nf_conntrack_द्विगुन_unlock(hash, reply_hash);
	local_bh_enable();

	help = nfct_help(ct);
	अगर (help && help->helper)
		nf_conntrack_event_cache(IPCT_HELPER, ct);

	nf_conntrack_event_cache(master_ct(ct) ?
				 IPCT_RELATED : IPCT_NEW, ct);
	वापस NF_ACCEPT;

out:
	ret = nf_ct_resolve_clash(skb, h, reply_hash);
dying:
	nf_conntrack_द्विगुन_unlock(hash, reply_hash);
	local_bh_enable();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__nf_conntrack_confirm);

/* Returns true अगर a connection correspondings to the tuple (required
   क्रम NAT). */
पूर्णांक
nf_conntrack_tuple_taken(स्थिर काष्ठा nf_conntrack_tuple *tuple,
			 स्थिर काष्ठा nf_conn *ignored_conntrack)
अणु
	काष्ठा net *net = nf_ct_net(ignored_conntrack);
	स्थिर काष्ठा nf_conntrack_zone *zone;
	काष्ठा nf_conntrack_tuple_hash *h;
	काष्ठा hlist_nulls_head *ct_hash;
	अचिन्हित पूर्णांक hash, hsize;
	काष्ठा hlist_nulls_node *n;
	काष्ठा nf_conn *ct;

	zone = nf_ct_zone(ignored_conntrack);

	rcu_पढ़ो_lock();
 begin:
	nf_conntrack_get_ht(&ct_hash, &hsize);
	hash = __hash_conntrack(net, tuple, hsize);

	hlist_nulls_क्रम_each_entry_rcu(h, n, &ct_hash[hash], hnnode) अणु
		ct = nf_ct_tuplehash_to_ctrack(h);

		अगर (ct == ignored_conntrack)
			जारी;

		अगर (nf_ct_is_expired(ct)) अणु
			nf_ct_gc_expired(ct);
			जारी;
		पूर्ण

		अगर (nf_ct_key_equal(h, tuple, zone, net)) अणु
			/* Tuple is taken alपढ़ोy, so caller will need to find
			 * a new source port to use.
			 *
			 * Only exception:
			 * If the *original tuples* are identical, then both
			 * conntracks refer to the same flow.
			 * This is a rare situation, it can occur e.g. when
			 * more than one UDP packet is sent from same socket
			 * in dअगरferent thपढ़ोs.
			 *
			 * Let nf_ct_resolve_clash() deal with this later.
			 */
			अगर (nf_ct_tuple_equal(&ignored_conntrack->tuplehash[IP_CT_सूची_ORIGINAL].tuple,
					      &ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple) &&
					      nf_ct_zone_equal(ct, zone, IP_CT_सूची_ORIGINAL))
				जारी;

			NF_CT_STAT_INC_ATOMIC(net, found);
			rcu_पढ़ो_unlock();
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (get_nulls_value(n) != hash) अणु
		NF_CT_STAT_INC_ATOMIC(net, search_restart);
		जाओ begin;
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nf_conntrack_tuple_taken);

#घोषणा NF_CT_EVICTION_RANGE	8

/* There's a small race here where we may मुक्त a just-assured
   connection.  Too bad: we're in trouble anyway. */
अटल अचिन्हित पूर्णांक early_drop_list(काष्ठा net *net,
				    काष्ठा hlist_nulls_head *head)
अणु
	काष्ठा nf_conntrack_tuple_hash *h;
	काष्ठा hlist_nulls_node *n;
	अचिन्हित पूर्णांक drops = 0;
	काष्ठा nf_conn *पंचांगp;

	hlist_nulls_क्रम_each_entry_rcu(h, n, head, hnnode) अणु
		पंचांगp = nf_ct_tuplehash_to_ctrack(h);

		अगर (test_bit(IPS_OFFLOAD_BIT, &पंचांगp->status))
			जारी;

		अगर (nf_ct_is_expired(पंचांगp)) अणु
			nf_ct_gc_expired(पंचांगp);
			जारी;
		पूर्ण

		अगर (test_bit(IPS_ASSURED_BIT, &पंचांगp->status) ||
		    !net_eq(nf_ct_net(पंचांगp), net) ||
		    nf_ct_is_dying(पंचांगp))
			जारी;

		अगर (!atomic_inc_not_zero(&पंचांगp->ct_general.use))
			जारी;

		/* समाप्त only अगर still in same netns -- might have moved due to
		 * SLAB_TYPESAFE_BY_RCU rules.
		 *
		 * We steal the समयr reference.  If that fails समयr has
		 * alपढ़ोy fired or someone अन्यथा deleted it. Just drop ref
		 * and move to next entry.
		 */
		अगर (net_eq(nf_ct_net(पंचांगp), net) &&
		    nf_ct_is_confirmed(पंचांगp) &&
		    nf_ct_delete(पंचांगp, 0, 0))
			drops++;

		nf_ct_put(पंचांगp);
	पूर्ण

	वापस drops;
पूर्ण

अटल noअंतरभूत पूर्णांक early_drop(काष्ठा net *net, अचिन्हित पूर्णांक hash)
अणु
	अचिन्हित पूर्णांक i, bucket;

	क्रम (i = 0; i < NF_CT_EVICTION_RANGE; i++) अणु
		काष्ठा hlist_nulls_head *ct_hash;
		अचिन्हित पूर्णांक hsize, drops;

		rcu_पढ़ो_lock();
		nf_conntrack_get_ht(&ct_hash, &hsize);
		अगर (!i)
			bucket = reciprocal_scale(hash, hsize);
		अन्यथा
			bucket = (bucket + 1) % hsize;

		drops = early_drop_list(net, &ct_hash[bucket]);
		rcu_पढ़ो_unlock();

		अगर (drops) अणु
			NF_CT_STAT_ADD_ATOMIC(net, early_drop, drops);
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool gc_worker_skip_ct(स्थिर काष्ठा nf_conn *ct)
अणु
	वापस !nf_ct_is_confirmed(ct) || nf_ct_is_dying(ct);
पूर्ण

अटल bool gc_worker_can_early_drop(स्थिर काष्ठा nf_conn *ct)
अणु
	स्थिर काष्ठा nf_conntrack_l4proto *l4proto;

	अगर (!test_bit(IPS_ASSURED_BIT, &ct->status))
		वापस true;

	l4proto = nf_ct_l4proto_find(nf_ct_protonum(ct));
	अगर (l4proto->can_early_drop && l4proto->can_early_drop(ct))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम gc_worker(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित पूर्णांक min_पूर्णांकerval = max(HZ / GC_MAX_BUCKETS_DIV, 1u);
	अचिन्हित पूर्णांक i, goal, buckets = 0, expired_count = 0;
	अचिन्हित पूर्णांक nf_conntrack_max95 = 0;
	काष्ठा conntrack_gc_work *gc_work;
	अचिन्हित पूर्णांक ratio, scanned = 0;
	अचिन्हित दीर्घ next_run;

	gc_work = container_of(work, काष्ठा conntrack_gc_work, dwork.work);

	goal = nf_conntrack_htable_size / GC_MAX_BUCKETS_DIV;
	i = gc_work->last_bucket;
	अगर (gc_work->early_drop)
		nf_conntrack_max95 = nf_conntrack_max / 100u * 95u;

	करो अणु
		काष्ठा nf_conntrack_tuple_hash *h;
		काष्ठा hlist_nulls_head *ct_hash;
		काष्ठा hlist_nulls_node *n;
		अचिन्हित पूर्णांक hashsz;
		काष्ठा nf_conn *पंचांगp;

		i++;
		rcu_पढ़ो_lock();

		nf_conntrack_get_ht(&ct_hash, &hashsz);
		अगर (i >= hashsz)
			i = 0;

		hlist_nulls_क्रम_each_entry_rcu(h, n, &ct_hash[i], hnnode) अणु
			काष्ठा nf_conntrack_net *cnet;
			काष्ठा net *net;

			पंचांगp = nf_ct_tuplehash_to_ctrack(h);

			scanned++;
			अगर (test_bit(IPS_OFFLOAD_BIT, &पंचांगp->status)) अणु
				nf_ct_offload_समयout(पंचांगp);
				जारी;
			पूर्ण

			अगर (nf_ct_is_expired(पंचांगp)) अणु
				nf_ct_gc_expired(पंचांगp);
				expired_count++;
				जारी;
			पूर्ण

			अगर (nf_conntrack_max95 == 0 || gc_worker_skip_ct(पंचांगp))
				जारी;

			net = nf_ct_net(पंचांगp);
			cnet = net_generic(net, nf_conntrack_net_id);
			अगर (atomic_पढ़ो(&cnet->count) < nf_conntrack_max95)
				जारी;

			/* need to take reference to aव्योम possible races */
			अगर (!atomic_inc_not_zero(&पंचांगp->ct_general.use))
				जारी;

			अगर (gc_worker_skip_ct(पंचांगp)) अणु
				nf_ct_put(पंचांगp);
				जारी;
			पूर्ण

			अगर (gc_worker_can_early_drop(पंचांगp))
				nf_ct_समाप्त(पंचांगp);

			nf_ct_put(पंचांगp);
		पूर्ण

		/* could check get_nulls_value() here and restart अगर ct
		 * was moved to another chain.  But given gc is best-efक्रमt
		 * we will just जारी with next hash slot.
		 */
		rcu_पढ़ो_unlock();
		cond_resched();
	पूर्ण जबतक (++buckets < goal);

	अगर (gc_work->निकासing)
		वापस;

	/*
	 * Eviction will normally happen from the packet path, and not
	 * from this gc worker.
	 *
	 * This worker is only here to reap expired entries when प्रणाली went
	 * idle after a busy period.
	 *
	 * The heuristics below are supposed to balance conflicting goals:
	 *
	 * 1. Minimize समय until we notice a stale entry
	 * 2. Maximize scan पूर्णांकervals to not waste cycles
	 *
	 * Normally, expire ratio will be बंद to 0.
	 *
	 * As soon as a sizeable fraction of the entries have expired
	 * increase scan frequency.
	 */
	ratio = scanned ? expired_count * 100 / scanned : 0;
	अगर (ratio > GC_EVICT_RATIO) अणु
		gc_work->next_gc_run = min_पूर्णांकerval;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक max = GC_MAX_SCAN_JIFFIES / GC_MAX_BUCKETS_DIV;

		BUILD_BUG_ON((GC_MAX_SCAN_JIFFIES / GC_MAX_BUCKETS_DIV) == 0);

		gc_work->next_gc_run += min_पूर्णांकerval;
		अगर (gc_work->next_gc_run > max)
			gc_work->next_gc_run = max;
	पूर्ण

	next_run = gc_work->next_gc_run;
	gc_work->last_bucket = i;
	gc_work->early_drop = false;
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &gc_work->dwork, next_run);
पूर्ण

अटल व्योम conntrack_gc_work_init(काष्ठा conntrack_gc_work *gc_work)
अणु
	INIT_DEFERRABLE_WORK(&gc_work->dwork, gc_worker);
	gc_work->next_gc_run = HZ;
	gc_work->निकासing = false;
पूर्ण

अटल काष्ठा nf_conn *
__nf_conntrack_alloc(काष्ठा net *net,
		     स्थिर काष्ठा nf_conntrack_zone *zone,
		     स्थिर काष्ठा nf_conntrack_tuple *orig,
		     स्थिर काष्ठा nf_conntrack_tuple *repl,
		     gfp_t gfp, u32 hash)
अणु
	काष्ठा nf_conntrack_net *cnet = net_generic(net, nf_conntrack_net_id);
	अचिन्हित पूर्णांक ct_count;
	काष्ठा nf_conn *ct;

	/* We करोn't want any race condition at early drop stage */
	ct_count = atomic_inc_वापस(&cnet->count);

	अगर (nf_conntrack_max && unlikely(ct_count > nf_conntrack_max)) अणु
		अगर (!early_drop(net, hash)) अणु
			अगर (!conntrack_gc_work.early_drop)
				conntrack_gc_work.early_drop = true;
			atomic_dec(&cnet->count);
			net_warn_ratelimited("nf_conntrack: table full, dropping packet\n");
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण

	/*
	 * Do not use kmem_cache_zalloc(), as this cache uses
	 * SLAB_TYPESAFE_BY_RCU.
	 */
	ct = kmem_cache_alloc(nf_conntrack_cachep, gfp);
	अगर (ct == शून्य)
		जाओ out;

	spin_lock_init(&ct->lock);
	ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple = *orig;
	ct->tuplehash[IP_CT_सूची_ORIGINAL].hnnode.pprev = शून्य;
	ct->tuplehash[IP_CT_सूची_REPLY].tuple = *repl;
	/* save hash क्रम reusing when confirming */
	*(अचिन्हित दीर्घ *)(&ct->tuplehash[IP_CT_सूची_REPLY].hnnode.pprev) = hash;
	ct->status = 0;
	ct->समयout = 0;
	ग_लिखो_pnet(&ct->ct_net, net);
	स_रखो(&ct->__nfct_init_offset, 0,
	       दुरत्व(काष्ठा nf_conn, proto) -
	       दुरत्व(काष्ठा nf_conn, __nfct_init_offset));

	nf_ct_zone_add(ct, zone);

	/* Because we use RCU lookups, we set ct_general.use to zero beक्रमe
	 * this is inserted in any list.
	 */
	atomic_set(&ct->ct_general.use, 0);
	वापस ct;
out:
	atomic_dec(&cnet->count);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

काष्ठा nf_conn *nf_conntrack_alloc(काष्ठा net *net,
				   स्थिर काष्ठा nf_conntrack_zone *zone,
				   स्थिर काष्ठा nf_conntrack_tuple *orig,
				   स्थिर काष्ठा nf_conntrack_tuple *repl,
				   gfp_t gfp)
अणु
	वापस __nf_conntrack_alloc(net, zone, orig, repl, gfp, 0);
पूर्ण
EXPORT_SYMBOL_GPL(nf_conntrack_alloc);

व्योम nf_conntrack_मुक्त(काष्ठा nf_conn *ct)
अणु
	काष्ठा net *net = nf_ct_net(ct);
	काष्ठा nf_conntrack_net *cnet;

	/* A मुक्तd object has refcnt == 0, that's
	 * the golden rule क्रम SLAB_TYPESAFE_BY_RCU
	 */
	WARN_ON(atomic_पढ़ो(&ct->ct_general.use) != 0);

	nf_ct_ext_destroy(ct);
	kmem_cache_मुक्त(nf_conntrack_cachep, ct);
	cnet = net_generic(net, nf_conntrack_net_id);

	smp_mb__beक्रमe_atomic();
	atomic_dec(&cnet->count);
पूर्ण
EXPORT_SYMBOL_GPL(nf_conntrack_मुक्त);


/* Allocate a new conntrack: we वापस -ENOMEM अगर classअगरication
   failed due to stress.  Otherwise it really is unclassअगरiable. */
अटल noअंतरभूत काष्ठा nf_conntrack_tuple_hash *
init_conntrack(काष्ठा net *net, काष्ठा nf_conn *पंचांगpl,
	       स्थिर काष्ठा nf_conntrack_tuple *tuple,
	       काष्ठा sk_buff *skb,
	       अचिन्हित पूर्णांक dataoff, u32 hash)
अणु
	काष्ठा nf_conn *ct;
	काष्ठा nf_conn_help *help;
	काष्ठा nf_conntrack_tuple repl_tuple;
	काष्ठा nf_conntrack_ecache *ecache;
	काष्ठा nf_conntrack_expect *exp = शून्य;
	स्थिर काष्ठा nf_conntrack_zone *zone;
	काष्ठा nf_conn_समयout *समयout_ext;
	काष्ठा nf_conntrack_zone पंचांगp;
	काष्ठा nf_conntrack_net *cnet;

	अगर (!nf_ct_invert_tuple(&repl_tuple, tuple)) अणु
		pr_debug("Can't invert tuple.\n");
		वापस शून्य;
	पूर्ण

	zone = nf_ct_zone_पंचांगpl(पंचांगpl, skb, &पंचांगp);
	ct = __nf_conntrack_alloc(net, zone, tuple, &repl_tuple, GFP_ATOMIC,
				  hash);
	अगर (IS_ERR(ct))
		वापस (काष्ठा nf_conntrack_tuple_hash *)ct;

	अगर (!nf_ct_add_synproxy(ct, पंचांगpl)) अणु
		nf_conntrack_मुक्त(ct);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	समयout_ext = पंचांगpl ? nf_ct_समयout_find(पंचांगpl) : शून्य;

	अगर (समयout_ext)
		nf_ct_समयout_ext_add(ct, rcu_dereference(समयout_ext->समयout),
				      GFP_ATOMIC);

	nf_ct_acct_ext_add(ct, GFP_ATOMIC);
	nf_ct_tstamp_ext_add(ct, GFP_ATOMIC);
	nf_ct_labels_ext_add(ct);

	ecache = पंचांगpl ? nf_ct_ecache_find(पंचांगpl) : शून्य;
	nf_ct_ecache_ext_add(ct, ecache ? ecache->cपंचांगask : 0,
				 ecache ? ecache->expmask : 0,
			     GFP_ATOMIC);

	local_bh_disable();
	cnet = net_generic(net, nf_conntrack_net_id);
	अगर (cnet->expect_count) अणु
		spin_lock(&nf_conntrack_expect_lock);
		exp = nf_ct_find_expectation(net, zone, tuple);
		अगर (exp) अणु
			pr_debug("expectation arrives ct=%p exp=%p\n",
				 ct, exp);
			/* Welcome, Mr. Bond.  We've been expecting you... */
			__set_bit(IPS_EXPECTED_BIT, &ct->status);
			/* exp->master safe, refcnt bumped in nf_ct_find_expectation */
			ct->master = exp->master;
			अगर (exp->helper) अणु
				help = nf_ct_helper_ext_add(ct, GFP_ATOMIC);
				अगर (help)
					rcu_assign_poपूर्णांकer(help->helper, exp->helper);
			पूर्ण

#अगर_घोषित CONFIG_NF_CONNTRACK_MARK
			ct->mark = exp->master->mark;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_SECMARK
			ct->secmark = exp->master->secmark;
#पूर्ण_अगर
			NF_CT_STAT_INC(net, expect_new);
		पूर्ण
		spin_unlock(&nf_conntrack_expect_lock);
	पूर्ण
	अगर (!exp)
		__nf_ct_try_assign_helper(ct, पंचांगpl, GFP_ATOMIC);

	/* Now it is inserted पूर्णांकo the unconfirmed list, bump refcount */
	nf_conntrack_get(&ct->ct_general);
	nf_ct_add_to_unconfirmed_list(ct);

	local_bh_enable();

	अगर (exp) अणु
		अगर (exp->expectfn)
			exp->expectfn(ct, exp);
		nf_ct_expect_put(exp);
	पूर्ण

	वापस &ct->tuplehash[IP_CT_सूची_ORIGINAL];
पूर्ण

/* On success, वापसs 0, sets skb->_nfct | ctinfo */
अटल पूर्णांक
resolve_normal_ct(काष्ठा nf_conn *पंचांगpl,
		  काष्ठा sk_buff *skb,
		  अचिन्हित पूर्णांक dataoff,
		  u_पूर्णांक8_t protonum,
		  स्थिर काष्ठा nf_hook_state *state)
अणु
	स्थिर काष्ठा nf_conntrack_zone *zone;
	काष्ठा nf_conntrack_tuple tuple;
	काष्ठा nf_conntrack_tuple_hash *h;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conntrack_zone पंचांगp;
	काष्ठा nf_conn *ct;
	u32 hash;

	अगर (!nf_ct_get_tuple(skb, skb_network_offset(skb),
			     dataoff, state->pf, protonum, state->net,
			     &tuple)) अणु
		pr_debug("Can't get tuple\n");
		वापस 0;
	पूर्ण

	/* look क्रम tuple match */
	zone = nf_ct_zone_पंचांगpl(पंचांगpl, skb, &पंचांगp);
	hash = hash_conntrack_raw(&tuple, state->net);
	h = __nf_conntrack_find_get(state->net, zone, &tuple, hash);
	अगर (!h) अणु
		h = init_conntrack(state->net, पंचांगpl, &tuple,
				   skb, dataoff, hash);
		अगर (!h)
			वापस 0;
		अगर (IS_ERR(h))
			वापस PTR_ERR(h);
	पूर्ण
	ct = nf_ct_tuplehash_to_ctrack(h);

	/* It exists; we have (non-exclusive) reference. */
	अगर (NF_CT_सूचीECTION(h) == IP_CT_सूची_REPLY) अणु
		ctinfo = IP_CT_ESTABLISHED_REPLY;
	पूर्ण अन्यथा अणु
		/* Once we've had two way comms, always ESTABLISHED. */
		अगर (test_bit(IPS_SEEN_REPLY_BIT, &ct->status)) अणु
			pr_debug("normal packet for %p\n", ct);
			ctinfo = IP_CT_ESTABLISHED;
		पूर्ण अन्यथा अगर (test_bit(IPS_EXPECTED_BIT, &ct->status)) अणु
			pr_debug("related packet for %p\n", ct);
			ctinfo = IP_CT_RELATED;
		पूर्ण अन्यथा अणु
			pr_debug("new packet for %p\n", ct);
			ctinfo = IP_CT_NEW;
		पूर्ण
	पूर्ण
	nf_ct_set(skb, ct, ctinfo);
	वापस 0;
पूर्ण

/*
 * icmp packets need special treaपंचांगent to handle error messages that are
 * related to a connection.
 *
 * Callers need to check अगर skb has a conntrack asचिन्हित when this
 * helper वापसs; in such हाल skb beदीर्घs to an alपढ़ोy known connection.
 */
अटल अचिन्हित पूर्णांक __cold
nf_conntrack_handle_icmp(काष्ठा nf_conn *पंचांगpl,
			 काष्ठा sk_buff *skb,
			 अचिन्हित पूर्णांक dataoff,
			 u8 protonum,
			 स्थिर काष्ठा nf_hook_state *state)
अणु
	पूर्णांक ret;

	अगर (state->pf == NFPROTO_IPV4 && protonum == IPPROTO_ICMP)
		ret = nf_conntrack_icmpv4_error(पंचांगpl, skb, dataoff, state);
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा अगर (state->pf == NFPROTO_IPV6 && protonum == IPPROTO_ICMPV6)
		ret = nf_conntrack_icmpv6_error(पंचांगpl, skb, dataoff, state);
#पूर्ण_अगर
	अन्यथा
		वापस NF_ACCEPT;

	अगर (ret <= 0)
		NF_CT_STAT_INC_ATOMIC(state->net, error);

	वापस ret;
पूर्ण

अटल पूर्णांक generic_packet(काष्ठा nf_conn *ct, काष्ठा sk_buff *skb,
			  क्रमागत ip_conntrack_info ctinfo)
अणु
	स्थिर अचिन्हित पूर्णांक *समयout = nf_ct_समयout_lookup(ct);

	अगर (!समयout)
		समयout = &nf_generic_pernet(nf_ct_net(ct))->समयout;

	nf_ct_refresh_acct(ct, ctinfo, skb, *समयout);
	वापस NF_ACCEPT;
पूर्ण

/* Returns verdict क्रम packet, or -1 क्रम invalid. */
अटल पूर्णांक nf_conntrack_handle_packet(काष्ठा nf_conn *ct,
				      काष्ठा sk_buff *skb,
				      अचिन्हित पूर्णांक dataoff,
				      क्रमागत ip_conntrack_info ctinfo,
				      स्थिर काष्ठा nf_hook_state *state)
अणु
	चयन (nf_ct_protonum(ct)) अणु
	हाल IPPROTO_TCP:
		वापस nf_conntrack_tcp_packet(ct, skb, dataoff,
					       ctinfo, state);
	हाल IPPROTO_UDP:
		वापस nf_conntrack_udp_packet(ct, skb, dataoff,
					       ctinfo, state);
	हाल IPPROTO_ICMP:
		वापस nf_conntrack_icmp_packet(ct, skb, ctinfo, state);
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल IPPROTO_ICMPV6:
		वापस nf_conntrack_icmpv6_packet(ct, skb, ctinfo, state);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_UDPLITE
	हाल IPPROTO_UDPLITE:
		वापस nf_conntrack_udplite_packet(ct, skb, dataoff,
						   ctinfo, state);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_SCTP
	हाल IPPROTO_SCTP:
		वापस nf_conntrack_sctp_packet(ct, skb, dataoff,
						ctinfo, state);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_DCCP
	हाल IPPROTO_DCCP:
		वापस nf_conntrack_dccp_packet(ct, skb, dataoff,
						ctinfo, state);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_GRE
	हाल IPPROTO_GRE:
		वापस nf_conntrack_gre_packet(ct, skb, dataoff,
					       ctinfo, state);
#पूर्ण_अगर
	पूर्ण

	वापस generic_packet(ct, skb, ctinfo);
पूर्ण

अचिन्हित पूर्णांक
nf_conntrack_in(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_hook_state *state)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct, *पंचांगpl;
	u_पूर्णांक8_t protonum;
	पूर्णांक dataoff, ret;

	पंचांगpl = nf_ct_get(skb, &ctinfo);
	अगर (पंचांगpl || ctinfo == IP_CT_UNTRACKED) अणु
		/* Previously seen (loopback or untracked)?  Ignore. */
		अगर ((पंचांगpl && !nf_ct_is_ढाँचा(पंचांगpl)) ||
		     ctinfo == IP_CT_UNTRACKED)
			वापस NF_ACCEPT;
		skb->_nfct = 0;
	पूर्ण

	/* rcu_पढ़ो_lock()ed by nf_hook_thresh */
	dataoff = get_l4proto(skb, skb_network_offset(skb), state->pf, &protonum);
	अगर (dataoff <= 0) अणु
		pr_debug("not prepared to track yet or error occurred\n");
		NF_CT_STAT_INC_ATOMIC(state->net, invalid);
		ret = NF_ACCEPT;
		जाओ out;
	पूर्ण

	अगर (protonum == IPPROTO_ICMP || protonum == IPPROTO_ICMPV6) अणु
		ret = nf_conntrack_handle_icmp(पंचांगpl, skb, dataoff,
					       protonum, state);
		अगर (ret <= 0) अणु
			ret = -ret;
			जाओ out;
		पूर्ण
		/* ICMP[v6] protocol trackers may assign one conntrack. */
		अगर (skb->_nfct)
			जाओ out;
	पूर्ण
repeat:
	ret = resolve_normal_ct(पंचांगpl, skb, dataoff,
				protonum, state);
	अगर (ret < 0) अणु
		/* Too stressed to deal. */
		NF_CT_STAT_INC_ATOMIC(state->net, drop);
		ret = NF_DROP;
		जाओ out;
	पूर्ण

	ct = nf_ct_get(skb, &ctinfo);
	अगर (!ct) अणु
		/* Not valid part of a connection */
		NF_CT_STAT_INC_ATOMIC(state->net, invalid);
		ret = NF_ACCEPT;
		जाओ out;
	पूर्ण

	ret = nf_conntrack_handle_packet(ct, skb, dataoff, ctinfo, state);
	अगर (ret <= 0) अणु
		/* Invalid: inverse of the वापस code tells
		 * the netfilter core what to करो */
		pr_debug("nf_conntrack_in: Can't track with proto module\n");
		nf_conntrack_put(&ct->ct_general);
		skb->_nfct = 0;
		NF_CT_STAT_INC_ATOMIC(state->net, invalid);
		अगर (ret == -NF_DROP)
			NF_CT_STAT_INC_ATOMIC(state->net, drop);
		/* Special हाल: TCP tracker reports an attempt to reखोलो a
		 * बंदd/पातed connection. We have to go back and create a
		 * fresh conntrack.
		 */
		अगर (ret == -NF_REPEAT)
			जाओ repeat;
		ret = -ret;
		जाओ out;
	पूर्ण

	अगर (ctinfo == IP_CT_ESTABLISHED_REPLY &&
	    !test_and_set_bit(IPS_SEEN_REPLY_BIT, &ct->status))
		nf_conntrack_event_cache(IPCT_REPLY, ct);
out:
	अगर (पंचांगpl)
		nf_ct_put(पंचांगpl);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nf_conntrack_in);

/* Alter reply tuple (maybe alter helper).  This is क्रम NAT, and is
   implicitly racy: see __nf_conntrack_confirm */
व्योम nf_conntrack_alter_reply(काष्ठा nf_conn *ct,
			      स्थिर काष्ठा nf_conntrack_tuple *newreply)
अणु
	काष्ठा nf_conn_help *help = nfct_help(ct);

	/* Should be unconfirmed, so not in hash table yet */
	WARN_ON(nf_ct_is_confirmed(ct));

	pr_debug("Altering reply tuple of %p to ", ct);
	nf_ct_dump_tuple(newreply);

	ct->tuplehash[IP_CT_सूची_REPLY].tuple = *newreply;
	अगर (ct->master || (help && !hlist_empty(&help->expectations)))
		वापस;

	rcu_पढ़ो_lock();
	__nf_ct_try_assign_helper(ct, शून्य, GFP_ATOMIC);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(nf_conntrack_alter_reply);

/* Refresh conntrack क्रम this many jअगरfies and करो accounting अगर करो_acct is 1 */
व्योम __nf_ct_refresh_acct(काष्ठा nf_conn *ct,
			  क्रमागत ip_conntrack_info ctinfo,
			  स्थिर काष्ठा sk_buff *skb,
			  u32 extra_jअगरfies,
			  bool करो_acct)
अणु
	/* Only update अगर this is not a fixed समयout */
	अगर (test_bit(IPS_FIXED_TIMEOUT_BIT, &ct->status))
		जाओ acct;

	/* If not in hash table, समयr will not be active yet */
	अगर (nf_ct_is_confirmed(ct))
		extra_jअगरfies += nfct_समय_stamp;

	अगर (READ_ONCE(ct->समयout) != extra_jअगरfies)
		WRITE_ONCE(ct->समयout, extra_jअगरfies);
acct:
	अगर (करो_acct)
		nf_ct_acct_update(ct, CTINFO2सूची(ctinfo), skb->len);
पूर्ण
EXPORT_SYMBOL_GPL(__nf_ct_refresh_acct);

bool nf_ct_समाप्त_acct(काष्ठा nf_conn *ct,
		     क्रमागत ip_conntrack_info ctinfo,
		     स्थिर काष्ठा sk_buff *skb)
अणु
	nf_ct_acct_update(ct, CTINFO2सूची(ctinfo), skb->len);

	वापस nf_ct_delete(ct, 0, 0);
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_समाप्त_acct);

#अगर IS_ENABLED(CONFIG_NF_CT_NETLINK)

#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nfnetlink_conntrack.h>
#समावेश <linux/mutex.h>

/* Generic function क्रम tcp/udp/sctp/dccp and alike. */
पूर्णांक nf_ct_port_tuple_to_nlattr(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा nf_conntrack_tuple *tuple)
अणु
	अगर (nla_put_be16(skb, CTA_PROTO_SRC_PORT, tuple->src.u.tcp.port) ||
	    nla_put_be16(skb, CTA_PROTO_DST_PORT, tuple->dst.u.tcp.port))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_port_tuple_to_nlattr);

स्थिर काष्ठा nla_policy nf_ct_port_nla_policy[CTA_PROTO_MAX+1] = अणु
	[CTA_PROTO_SRC_PORT]  = अणु .type = NLA_U16 पूर्ण,
	[CTA_PROTO_DST_PORT]  = अणु .type = NLA_U16 पूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(nf_ct_port_nla_policy);

पूर्णांक nf_ct_port_nlattr_to_tuple(काष्ठा nlattr *tb[],
			       काष्ठा nf_conntrack_tuple *t,
			       u_पूर्णांक32_t flags)
अणु
	अगर (flags & CTA_FILTER_FLAG(CTA_PROTO_SRC_PORT)) अणु
		अगर (!tb[CTA_PROTO_SRC_PORT])
			वापस -EINVAL;

		t->src.u.tcp.port = nla_get_be16(tb[CTA_PROTO_SRC_PORT]);
	पूर्ण

	अगर (flags & CTA_FILTER_FLAG(CTA_PROTO_DST_PORT)) अणु
		अगर (!tb[CTA_PROTO_DST_PORT])
			वापस -EINVAL;

		t->dst.u.tcp.port = nla_get_be16(tb[CTA_PROTO_DST_PORT]);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_port_nlattr_to_tuple);

अचिन्हित पूर्णांक nf_ct_port_nlattr_tuple_size(व्योम)
अणु
	अटल अचिन्हित पूर्णांक size __पढ़ो_mostly;

	अगर (!size)
		size = nla_policy_len(nf_ct_port_nla_policy, CTA_PROTO_MAX + 1);

	वापस size;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_port_nlattr_tuple_size);
#पूर्ण_अगर

/* Used by ipt_REJECT and ip6t_REJECT. */
अटल व्योम nf_conntrack_attach(काष्ठा sk_buff *nskb, स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा nf_conn *ct;
	क्रमागत ip_conntrack_info ctinfo;

	/* This ICMP is in reverse direction to the packet which caused it */
	ct = nf_ct_get(skb, &ctinfo);
	अगर (CTINFO2सूची(ctinfo) == IP_CT_सूची_ORIGINAL)
		ctinfo = IP_CT_RELATED_REPLY;
	अन्यथा
		ctinfo = IP_CT_RELATED;

	/* Attach to new skbuff, and increment count */
	nf_ct_set(nskb, ct, ctinfo);
	nf_conntrack_get(skb_nfct(nskb));
पूर्ण

अटल पूर्णांक __nf_conntrack_update(काष्ठा net *net, काष्ठा sk_buff *skb,
				 काष्ठा nf_conn *ct,
				 क्रमागत ip_conntrack_info ctinfo)
अणु
	काष्ठा nf_conntrack_tuple_hash *h;
	काष्ठा nf_conntrack_tuple tuple;
	काष्ठा nf_nat_hook *nat_hook;
	अचिन्हित पूर्णांक status;
	पूर्णांक dataoff;
	u16 l3num;
	u8 l4num;

	l3num = nf_ct_l3num(ct);

	dataoff = get_l4proto(skb, skb_network_offset(skb), l3num, &l4num);
	अगर (dataoff <= 0)
		वापस -1;

	अगर (!nf_ct_get_tuple(skb, skb_network_offset(skb), dataoff, l3num,
			     l4num, net, &tuple))
		वापस -1;

	अगर (ct->status & IPS_SRC_NAT) अणु
		स_नकल(tuple.src.u3.all,
		       ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.src.u3.all,
		       माप(tuple.src.u3.all));
		tuple.src.u.all =
			ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.src.u.all;
	पूर्ण

	अगर (ct->status & IPS_DST_NAT) अणु
		स_नकल(tuple.dst.u3.all,
		       ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.dst.u3.all,
		       माप(tuple.dst.u3.all));
		tuple.dst.u.all =
			ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.dst.u.all;
	पूर्ण

	h = nf_conntrack_find_get(net, nf_ct_zone(ct), &tuple);
	अगर (!h)
		वापस 0;

	/* Store status bits of the conntrack that is clashing to re-करो NAT
	 * mangling according to what it has been करोne alपढ़ोy to this packet.
	 */
	status = ct->status;

	nf_ct_put(ct);
	ct = nf_ct_tuplehash_to_ctrack(h);
	nf_ct_set(skb, ct, ctinfo);

	nat_hook = rcu_dereference(nf_nat_hook);
	अगर (!nat_hook)
		वापस 0;

	अगर (status & IPS_SRC_NAT &&
	    nat_hook->manip_pkt(skb, ct, NF_NAT_MANIP_SRC,
				IP_CT_सूची_ORIGINAL) == NF_DROP)
		वापस -1;

	अगर (status & IPS_DST_NAT &&
	    nat_hook->manip_pkt(skb, ct, NF_NAT_MANIP_DST,
				IP_CT_सूची_ORIGINAL) == NF_DROP)
		वापस -1;

	वापस 0;
पूर्ण

/* This packet is coming from userspace via nf_queue, complete the packet
 * processing after the helper invocation in nf_confirm().
 */
अटल पूर्णांक nf_confirm_cthelper(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			       क्रमागत ip_conntrack_info ctinfo)
अणु
	स्थिर काष्ठा nf_conntrack_helper *helper;
	स्थिर काष्ठा nf_conn_help *help;
	पूर्णांक protoff;

	help = nfct_help(ct);
	अगर (!help)
		वापस 0;

	helper = rcu_dereference(help->helper);
	अगर (!(helper->flags & NF_CT_HELPER_F_USERSPACE))
		वापस 0;

	चयन (nf_ct_l3num(ct)) अणु
	हाल NFPROTO_IPV4:
		protoff = skb_network_offset(skb) + ip_hdrlen(skb);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल NFPROTO_IPV6: अणु
		__be16 frag_off;
		u8 pnum;

		pnum = ipv6_hdr(skb)->nexthdr;
		protoff = ipv6_skip_exthdr(skb, माप(काष्ठा ipv6hdr), &pnum,
					   &frag_off);
		अगर (protoff < 0 || (frag_off & htons(~0x7)) != 0)
			वापस 0;
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	शेष:
		वापस 0;
	पूर्ण

	अगर (test_bit(IPS_SEQ_ADJUST_BIT, &ct->status) &&
	    !nf_is_loopback_packet(skb)) अणु
		अगर (!nf_ct_seq_adjust(skb, ct, ctinfo, protoff)) अणु
			NF_CT_STAT_INC_ATOMIC(nf_ct_net(ct), drop);
			वापस -1;
		पूर्ण
	पूर्ण

	/* We've seen it coming out the other side: confirm it */
	वापस nf_conntrack_confirm(skb) == NF_DROP ? - 1 : 0;
पूर्ण

अटल पूर्णांक nf_conntrack_update(काष्ठा net *net, काष्ठा sk_buff *skb)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;
	पूर्णांक err;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (!ct)
		वापस 0;

	अगर (!nf_ct_is_confirmed(ct)) अणु
		err = __nf_conntrack_update(net, skb, ct, ctinfo);
		अगर (err < 0)
			वापस err;

		ct = nf_ct_get(skb, &ctinfo);
	पूर्ण

	वापस nf_confirm_cthelper(skb, ct, ctinfo);
पूर्ण

अटल bool nf_conntrack_get_tuple_skb(काष्ठा nf_conntrack_tuple *dst_tuple,
				       स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा nf_conntrack_tuple *src_tuple;
	स्थिर काष्ठा nf_conntrack_tuple_hash *hash;
	काष्ठा nf_conntrack_tuple srctuple;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (ct) अणु
		src_tuple = nf_ct_tuple(ct, CTINFO2सूची(ctinfo));
		स_नकल(dst_tuple, src_tuple, माप(*dst_tuple));
		वापस true;
	पूर्ण

	अगर (!nf_ct_get_tuplepr(skb, skb_network_offset(skb),
			       NFPROTO_IPV4, dev_net(skb->dev),
			       &srctuple))
		वापस false;

	hash = nf_conntrack_find_get(dev_net(skb->dev),
				     &nf_ct_zone_dflt,
				     &srctuple);
	अगर (!hash)
		वापस false;

	ct = nf_ct_tuplehash_to_ctrack(hash);
	src_tuple = nf_ct_tuple(ct, !hash->tuple.dst.dir);
	स_नकल(dst_tuple, src_tuple, माप(*dst_tuple));
	nf_ct_put(ct);

	वापस true;
पूर्ण

/* Bring out ya dead! */
अटल काष्ठा nf_conn *
get_next_corpse(पूर्णांक (*iter)(काष्ठा nf_conn *i, व्योम *data),
		व्योम *data, अचिन्हित पूर्णांक *bucket)
अणु
	काष्ठा nf_conntrack_tuple_hash *h;
	काष्ठा nf_conn *ct;
	काष्ठा hlist_nulls_node *n;
	spinlock_t *lockp;

	क्रम (; *bucket < nf_conntrack_htable_size; (*bucket)++) अणु
		lockp = &nf_conntrack_locks[*bucket % CONNTRACK_LOCKS];
		local_bh_disable();
		nf_conntrack_lock(lockp);
		अगर (*bucket < nf_conntrack_htable_size) अणु
			hlist_nulls_क्रम_each_entry(h, n, &nf_conntrack_hash[*bucket], hnnode) अणु
				अगर (NF_CT_सूचीECTION(h) != IP_CT_सूची_REPLY)
					जारी;
				/* All nf_conn objects are added to hash table twice, one
				 * क्रम original direction tuple, once क्रम the reply tuple.
				 *
				 * Exception: In the IPS_NAT_CLASH हाल, only the reply
				 * tuple is added (the original tuple alपढ़ोy existed क्रम
				 * a dअगरferent object).
				 *
				 * We only need to call the iterator once क्रम each
				 * conntrack, so we just use the 'reply' direction
				 * tuple जबतक iterating.
				 */
				ct = nf_ct_tuplehash_to_ctrack(h);
				अगर (iter(ct, data))
					जाओ found;
			पूर्ण
		पूर्ण
		spin_unlock(lockp);
		local_bh_enable();
		cond_resched();
	पूर्ण

	वापस शून्य;
found:
	atomic_inc(&ct->ct_general.use);
	spin_unlock(lockp);
	local_bh_enable();
	वापस ct;
पूर्ण

अटल व्योम nf_ct_iterate_cleanup(पूर्णांक (*iter)(काष्ठा nf_conn *i, व्योम *data),
				  व्योम *data, u32 portid, पूर्णांक report)
अणु
	अचिन्हित पूर्णांक bucket = 0, sequence;
	काष्ठा nf_conn *ct;

	might_sleep();

	क्रम (;;) अणु
		sequence = पढ़ो_seqcount_begin(&nf_conntrack_generation);

		जबतक ((ct = get_next_corpse(iter, data, &bucket)) != शून्य) अणु
			/* Time to push up daises... */

			nf_ct_delete(ct, portid, report);
			nf_ct_put(ct);
			cond_resched();
		पूर्ण

		अगर (!पढ़ो_seqcount_retry(&nf_conntrack_generation, sequence))
			अवरोध;
		bucket = 0;
	पूर्ण
पूर्ण

काष्ठा iter_data अणु
	पूर्णांक (*iter)(काष्ठा nf_conn *i, व्योम *data);
	व्योम *data;
	काष्ठा net *net;
पूर्ण;

अटल पूर्णांक iter_net_only(काष्ठा nf_conn *i, व्योम *data)
अणु
	काष्ठा iter_data *d = data;

	अगर (!net_eq(d->net, nf_ct_net(i)))
		वापस 0;

	वापस d->iter(i, d->data);
पूर्ण

अटल व्योम
__nf_ct_unconfirmed_destroy(काष्ठा net *net)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा nf_conntrack_tuple_hash *h;
		काष्ठा hlist_nulls_node *n;
		काष्ठा ct_pcpu *pcpu;

		pcpu = per_cpu_ptr(net->ct.pcpu_lists, cpu);

		spin_lock_bh(&pcpu->lock);
		hlist_nulls_क्रम_each_entry(h, n, &pcpu->unconfirmed, hnnode) अणु
			काष्ठा nf_conn *ct;

			ct = nf_ct_tuplehash_to_ctrack(h);

			/* we cannot call iter() on unconfirmed list, the
			 * owning cpu can पुनः_स्मृतिate ct->ext at any समय.
			 */
			set_bit(IPS_DYING_BIT, &ct->status);
		पूर्ण
		spin_unlock_bh(&pcpu->lock);
		cond_resched();
	पूर्ण
पूर्ण

व्योम nf_ct_unconfirmed_destroy(काष्ठा net *net)
अणु
	काष्ठा nf_conntrack_net *cnet = net_generic(net, nf_conntrack_net_id);

	might_sleep();

	अगर (atomic_पढ़ो(&cnet->count) > 0) अणु
		__nf_ct_unconfirmed_destroy(net);
		nf_queue_nf_hook_drop(net);
		synchronize_net();
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_unconfirmed_destroy);

व्योम nf_ct_iterate_cleanup_net(काष्ठा net *net,
			       पूर्णांक (*iter)(काष्ठा nf_conn *i, व्योम *data),
			       व्योम *data, u32 portid, पूर्णांक report)
अणु
	काष्ठा nf_conntrack_net *cnet = net_generic(net, nf_conntrack_net_id);
	काष्ठा iter_data d;

	might_sleep();

	अगर (atomic_पढ़ो(&cnet->count) == 0)
		वापस;

	d.iter = iter;
	d.data = data;
	d.net = net;

	nf_ct_iterate_cleanup(iter_net_only, &d, portid, report);
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_iterate_cleanup_net);

/**
 * nf_ct_iterate_destroy - destroy unconfirmed conntracks and iterate table
 * @iter: callback to invoke क्रम each conntrack
 * @data: data to pass to @iter
 *
 * Like nf_ct_iterate_cleanup, but first marks conntracks on the
 * unconfirmed list as dying (so they will not be inserted पूर्णांकo
 * मुख्य table).
 *
 * Can only be called in module निकास path.
 */
व्योम
nf_ct_iterate_destroy(पूर्णांक (*iter)(काष्ठा nf_conn *i, व्योम *data), व्योम *data)
अणु
	काष्ठा net *net;

	करोwn_पढ़ो(&net_rwsem);
	क्रम_each_net(net) अणु
		काष्ठा nf_conntrack_net *cnet = net_generic(net, nf_conntrack_net_id);

		अगर (atomic_पढ़ो(&cnet->count) == 0)
			जारी;
		__nf_ct_unconfirmed_destroy(net);
		nf_queue_nf_hook_drop(net);
	पूर्ण
	up_पढ़ो(&net_rwsem);

	/* Need to रुको क्रम netns cleanup worker to finish, अगर its
	 * running -- it might have deleted a net namespace from
	 * the global list, so our __nf_ct_unconfirmed_destroy() might
	 * not have affected all namespaces.
	 */
	net_ns_barrier();

	/* a conntrack could have been unlinked from unconfirmed list
	 * beक्रमe we grabbed pcpu lock in __nf_ct_unconfirmed_destroy().
	 * This makes sure its inserted पूर्णांकo conntrack table.
	 */
	synchronize_net();

	nf_ct_iterate_cleanup(iter, data, 0, 0);
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_iterate_destroy);

अटल पूर्णांक समाप्त_all(काष्ठा nf_conn *i, व्योम *data)
अणु
	वापस net_eq(nf_ct_net(i), data);
पूर्ण

व्योम nf_conntrack_cleanup_start(व्योम)
अणु
	conntrack_gc_work.निकासing = true;
	RCU_INIT_POINTER(ip_ct_attach, शून्य);
पूर्ण

व्योम nf_conntrack_cleanup_end(व्योम)
अणु
	RCU_INIT_POINTER(nf_ct_hook, शून्य);
	cancel_delayed_work_sync(&conntrack_gc_work.dwork);
	kvमुक्त(nf_conntrack_hash);

	nf_conntrack_proto_fini();
	nf_conntrack_seqadj_fini();
	nf_conntrack_labels_fini();
	nf_conntrack_helper_fini();
	nf_conntrack_समयout_fini();
	nf_conntrack_ecache_fini();
	nf_conntrack_tstamp_fini();
	nf_conntrack_acct_fini();
	nf_conntrack_expect_fini();

	kmem_cache_destroy(nf_conntrack_cachep);
पूर्ण

/*
 * Mishearing the voices in his head, our hero wonders how he's
 * supposed to समाप्त the mall.
 */
व्योम nf_conntrack_cleanup_net(काष्ठा net *net)
अणु
	LIST_HEAD(single);

	list_add(&net->निकास_list, &single);
	nf_conntrack_cleanup_net_list(&single);
पूर्ण

व्योम nf_conntrack_cleanup_net_list(काष्ठा list_head *net_निकास_list)
अणु
	पूर्णांक busy;
	काष्ठा net *net;

	/*
	 * This makes sure all current packets have passed through
	 *  netfilter framework.  Roll on, two-stage module
	 *  delete...
	 */
	synchronize_net();
i_see_dead_people:
	busy = 0;
	list_क्रम_each_entry(net, net_निकास_list, निकास_list) अणु
		काष्ठा nf_conntrack_net *cnet = net_generic(net, nf_conntrack_net_id);

		nf_ct_iterate_cleanup(समाप्त_all, net, 0, 0);
		अगर (atomic_पढ़ो(&cnet->count) != 0)
			busy = 1;
	पूर्ण
	अगर (busy) अणु
		schedule();
		जाओ i_see_dead_people;
	पूर्ण

	list_क्रम_each_entry(net, net_निकास_list, निकास_list) अणु
		nf_conntrack_proto_pernet_fini(net);
		nf_conntrack_ecache_pernet_fini(net);
		nf_conntrack_expect_pernet_fini(net);
		मुक्त_percpu(net->ct.stat);
		मुक्त_percpu(net->ct.pcpu_lists);
	पूर्ण
पूर्ण

व्योम *nf_ct_alloc_hashtable(अचिन्हित पूर्णांक *sizep, पूर्णांक nulls)
अणु
	काष्ठा hlist_nulls_head *hash;
	अचिन्हित पूर्णांक nr_slots, i;

	अगर (*sizep > (अच_पूर्णांक_उच्च / माप(काष्ठा hlist_nulls_head)))
		वापस शून्य;

	BUILD_BUG_ON(माप(काष्ठा hlist_nulls_head) != माप(काष्ठा hlist_head));
	nr_slots = *sizep = roundup(*sizep, PAGE_SIZE / माप(काष्ठा hlist_nulls_head));

	hash = kvसुस्मृति(nr_slots, माप(काष्ठा hlist_nulls_head), GFP_KERNEL);

	अगर (hash && nulls)
		क्रम (i = 0; i < nr_slots; i++)
			INIT_HLIST_शून्यS_HEAD(&hash[i], i);

	वापस hash;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_alloc_hashtable);

पूर्णांक nf_conntrack_hash_resize(अचिन्हित पूर्णांक hashsize)
अणु
	पूर्णांक i, bucket;
	अचिन्हित पूर्णांक old_size;
	काष्ठा hlist_nulls_head *hash, *old_hash;
	काष्ठा nf_conntrack_tuple_hash *h;
	काष्ठा nf_conn *ct;

	अगर (!hashsize)
		वापस -EINVAL;

	hash = nf_ct_alloc_hashtable(&hashsize, 1);
	अगर (!hash)
		वापस -ENOMEM;

	old_size = nf_conntrack_htable_size;
	अगर (old_size == hashsize) अणु
		kvमुक्त(hash);
		वापस 0;
	पूर्ण

	local_bh_disable();
	nf_conntrack_all_lock();
	ग_लिखो_seqcount_begin(&nf_conntrack_generation);

	/* Lookups in the old hash might happen in parallel, which means we
	 * might get false negatives during connection lookup. New connections
	 * created because of a false negative won't make it पूर्णांकo the hash
	 * though since that required taking the locks.
	 */

	क्रम (i = 0; i < nf_conntrack_htable_size; i++) अणु
		जबतक (!hlist_nulls_empty(&nf_conntrack_hash[i])) अणु
			h = hlist_nulls_entry(nf_conntrack_hash[i].first,
					      काष्ठा nf_conntrack_tuple_hash, hnnode);
			ct = nf_ct_tuplehash_to_ctrack(h);
			hlist_nulls_del_rcu(&h->hnnode);
			bucket = __hash_conntrack(nf_ct_net(ct),
						  &h->tuple, hashsize);
			hlist_nulls_add_head_rcu(&h->hnnode, &hash[bucket]);
		पूर्ण
	पूर्ण
	old_size = nf_conntrack_htable_size;
	old_hash = nf_conntrack_hash;

	nf_conntrack_hash = hash;
	nf_conntrack_htable_size = hashsize;

	ग_लिखो_seqcount_end(&nf_conntrack_generation);
	nf_conntrack_all_unlock();
	local_bh_enable();

	synchronize_net();
	kvमुक्त(old_hash);
	वापस 0;
पूर्ण

पूर्णांक nf_conntrack_set_hashsize(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	अचिन्हित पूर्णांक hashsize;
	पूर्णांक rc;

	अगर (current->nsproxy->net_ns != &init_net)
		वापस -EOPNOTSUPP;

	/* On boot, we can set this without any fancy locking. */
	अगर (!nf_conntrack_hash)
		वापस param_set_uपूर्णांक(val, kp);

	rc = kstrtouपूर्णांक(val, 0, &hashsize);
	अगर (rc)
		वापस rc;

	वापस nf_conntrack_hash_resize(hashsize);
पूर्ण

अटल __always_अंतरभूत अचिन्हित पूर्णांक total_extension_size(व्योम)
अणु
	/* remember to add new extensions below */
	BUILD_BUG_ON(NF_CT_EXT_NUM > 9);

	वापस माप(काष्ठा nf_ct_ext) +
	       माप(काष्ठा nf_conn_help)
#अगर IS_ENABLED(CONFIG_NF_NAT)
		+ माप(काष्ठा nf_conn_nat)
#पूर्ण_अगर
		+ माप(काष्ठा nf_conn_seqadj)
		+ माप(काष्ठा nf_conn_acct)
#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS
		+ माप(काष्ठा nf_conntrack_ecache)
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMESTAMP
		+ माप(काष्ठा nf_conn_tstamp)
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
		+ माप(काष्ठा nf_conn_समयout)
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_LABELS
		+ माप(काष्ठा nf_conn_labels)
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_NETFILTER_SYNPROXY)
		+ माप(काष्ठा nf_conn_synproxy)
#पूर्ण_अगर
	;
पूर्ण;

पूर्णांक nf_conntrack_init_start(व्योम)
अणु
	अचिन्हित दीर्घ nr_pages = totalram_pages();
	पूर्णांक max_factor = 8;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक i;

	/* काष्ठा nf_ct_ext uses u8 to store offsets/size */
	BUILD_BUG_ON(total_extension_size() > 255u);

	seqcount_spinlock_init(&nf_conntrack_generation,
			       &nf_conntrack_locks_all_lock);

	क्रम (i = 0; i < CONNTRACK_LOCKS; i++)
		spin_lock_init(&nf_conntrack_locks[i]);

	अगर (!nf_conntrack_htable_size) अणु
		/* Idea from tcp.c: use 1/16384 of memory.
		 * On i386: 32MB machine has 512 buckets.
		 * >= 1GB machines have 16384 buckets.
		 * >= 4GB machines have 65536 buckets.
		 */
		nf_conntrack_htable_size
			= (((nr_pages << PAGE_SHIFT) / 16384)
			   / माप(काष्ठा hlist_head));
		अगर (nr_pages > (4 * (1024 * 1024 * 1024 / PAGE_SIZE)))
			nf_conntrack_htable_size = 65536;
		अन्यथा अगर (nr_pages > (1024 * 1024 * 1024 / PAGE_SIZE))
			nf_conntrack_htable_size = 16384;
		अगर (nf_conntrack_htable_size < 32)
			nf_conntrack_htable_size = 32;

		/* Use a max. factor of four by शेष to get the same max as
		 * with the old काष्ठा list_heads. When a table size is given
		 * we use the old value of 8 to aव्योम reducing the max.
		 * entries. */
		max_factor = 4;
	पूर्ण

	nf_conntrack_hash = nf_ct_alloc_hashtable(&nf_conntrack_htable_size, 1);
	अगर (!nf_conntrack_hash)
		वापस -ENOMEM;

	nf_conntrack_max = max_factor * nf_conntrack_htable_size;

	nf_conntrack_cachep = kmem_cache_create("nf_conntrack",
						माप(काष्ठा nf_conn),
						NFCT_INFOMASK + 1,
						SLAB_TYPESAFE_BY_RCU | SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!nf_conntrack_cachep)
		जाओ err_cachep;

	ret = nf_conntrack_expect_init();
	अगर (ret < 0)
		जाओ err_expect;

	ret = nf_conntrack_acct_init();
	अगर (ret < 0)
		जाओ err_acct;

	ret = nf_conntrack_tstamp_init();
	अगर (ret < 0)
		जाओ err_tstamp;

	ret = nf_conntrack_ecache_init();
	अगर (ret < 0)
		जाओ err_ecache;

	ret = nf_conntrack_समयout_init();
	अगर (ret < 0)
		जाओ err_समयout;

	ret = nf_conntrack_helper_init();
	अगर (ret < 0)
		जाओ err_helper;

	ret = nf_conntrack_labels_init();
	अगर (ret < 0)
		जाओ err_labels;

	ret = nf_conntrack_seqadj_init();
	अगर (ret < 0)
		जाओ err_seqadj;

	ret = nf_conntrack_proto_init();
	अगर (ret < 0)
		जाओ err_proto;

	conntrack_gc_work_init(&conntrack_gc_work);
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &conntrack_gc_work.dwork, HZ);

	वापस 0;

err_proto:
	nf_conntrack_seqadj_fini();
err_seqadj:
	nf_conntrack_labels_fini();
err_labels:
	nf_conntrack_helper_fini();
err_helper:
	nf_conntrack_समयout_fini();
err_समयout:
	nf_conntrack_ecache_fini();
err_ecache:
	nf_conntrack_tstamp_fini();
err_tstamp:
	nf_conntrack_acct_fini();
err_acct:
	nf_conntrack_expect_fini();
err_expect:
	kmem_cache_destroy(nf_conntrack_cachep);
err_cachep:
	kvमुक्त(nf_conntrack_hash);
	वापस ret;
पूर्ण

अटल काष्ठा nf_ct_hook nf_conntrack_hook = अणु
	.update		= nf_conntrack_update,
	.destroy	= destroy_conntrack,
	.get_tuple_skb  = nf_conntrack_get_tuple_skb,
पूर्ण;

व्योम nf_conntrack_init_end(व्योम)
अणु
	/* For use by REJECT target */
	RCU_INIT_POINTER(ip_ct_attach, nf_conntrack_attach);
	RCU_INIT_POINTER(nf_ct_hook, &nf_conntrack_hook);
पूर्ण

/*
 * We need to use special "null" values, not used in hash table
 */
#घोषणा UNCONFIRMED_शून्यS_VAL	((1<<30)+0)
#घोषणा DYING_शून्यS_VAL		((1<<30)+1)

पूर्णांक nf_conntrack_init_net(काष्ठा net *net)
अणु
	काष्ठा nf_conntrack_net *cnet = net_generic(net, nf_conntrack_net_id);
	पूर्णांक ret = -ENOMEM;
	पूर्णांक cpu;

	BUILD_BUG_ON(IP_CT_UNTRACKED == IP_CT_NUMBER);
	BUILD_BUG_ON_NOT_POWER_OF_2(CONNTRACK_LOCKS);
	atomic_set(&cnet->count, 0);

	net->ct.pcpu_lists = alloc_percpu(काष्ठा ct_pcpu);
	अगर (!net->ct.pcpu_lists)
		जाओ err_stat;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा ct_pcpu *pcpu = per_cpu_ptr(net->ct.pcpu_lists, cpu);

		spin_lock_init(&pcpu->lock);
		INIT_HLIST_शून्यS_HEAD(&pcpu->unconfirmed, UNCONFIRMED_शून्यS_VAL);
		INIT_HLIST_शून्यS_HEAD(&pcpu->dying, DYING_शून्यS_VAL);
	पूर्ण

	net->ct.stat = alloc_percpu(काष्ठा ip_conntrack_stat);
	अगर (!net->ct.stat)
		जाओ err_pcpu_lists;

	ret = nf_conntrack_expect_pernet_init(net);
	अगर (ret < 0)
		जाओ err_expect;

	nf_conntrack_acct_pernet_init(net);
	nf_conntrack_tstamp_pernet_init(net);
	nf_conntrack_ecache_pernet_init(net);
	nf_conntrack_helper_pernet_init(net);
	nf_conntrack_proto_pernet_init(net);

	वापस 0;

err_expect:
	मुक्त_percpu(net->ct.stat);
err_pcpu_lists:
	मुक्त_percpu(net->ct.pcpu_lists);
err_stat:
	वापस ret;
पूर्ण
