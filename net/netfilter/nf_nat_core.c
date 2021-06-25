<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2006 Netfilter Core Team <coreteam@netfilter.org>
 * (C) 2011 Patrick McHardy <kaber@trash.net>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/gfp.h>
#समावेश <net/xfrm.h>
#समावेश <linux/jhash.h>
#समावेश <linux/rtnetlink.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_seqadj.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>
#समावेश <net/netfilter/nf_nat.h>
#समावेश <net/netfilter/nf_nat_helper.h>
#समावेश <uapi/linux/netfilter/nf_nat.h>

#समावेश "nf_internals.h"

अटल spinlock_t nf_nat_locks[CONNTRACK_LOCKS];

अटल DEFINE_MUTEX(nf_nat_proto_mutex);
अटल अचिन्हित पूर्णांक nat_net_id __पढ़ो_mostly;

अटल काष्ठा hlist_head *nf_nat_bysource __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक nf_nat_htable_size __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक nf_nat_hash_rnd __पढ़ो_mostly;

काष्ठा nf_nat_lookup_hook_priv अणु
	काष्ठा nf_hook_entries __rcu *entries;

	काष्ठा rcu_head rcu_head;
पूर्ण;

काष्ठा nf_nat_hooks_net अणु
	काष्ठा nf_hook_ops *nat_hook_ops;
	अचिन्हित पूर्णांक users;
पूर्ण;

काष्ठा nat_net अणु
	काष्ठा nf_nat_hooks_net nat_proto_net[NFPROTO_NUMPROTO];
पूर्ण;

#अगर_घोषित CONFIG_XFRM
अटल व्योम nf_nat_ipv4_decode_session(काष्ठा sk_buff *skb,
				       स्थिर काष्ठा nf_conn *ct,
				       क्रमागत ip_conntrack_dir dir,
				       अचिन्हित दीर्घ statusbit,
				       काष्ठा flowi *fl)
अणु
	स्थिर काष्ठा nf_conntrack_tuple *t = &ct->tuplehash[dir].tuple;
	काष्ठा flowi4 *fl4 = &fl->u.ip4;

	अगर (ct->status & statusbit) अणु
		fl4->daddr = t->dst.u3.ip;
		अगर (t->dst.protonum == IPPROTO_TCP ||
		    t->dst.protonum == IPPROTO_UDP ||
		    t->dst.protonum == IPPROTO_UDPLITE ||
		    t->dst.protonum == IPPROTO_DCCP ||
		    t->dst.protonum == IPPROTO_SCTP)
			fl4->fl4_dport = t->dst.u.all;
	पूर्ण

	statusbit ^= IPS_NAT_MASK;

	अगर (ct->status & statusbit) अणु
		fl4->saddr = t->src.u3.ip;
		अगर (t->dst.protonum == IPPROTO_TCP ||
		    t->dst.protonum == IPPROTO_UDP ||
		    t->dst.protonum == IPPROTO_UDPLITE ||
		    t->dst.protonum == IPPROTO_DCCP ||
		    t->dst.protonum == IPPROTO_SCTP)
			fl4->fl4_sport = t->src.u.all;
	पूर्ण
पूर्ण

अटल व्योम nf_nat_ipv6_decode_session(काष्ठा sk_buff *skb,
				       स्थिर काष्ठा nf_conn *ct,
				       क्रमागत ip_conntrack_dir dir,
				       अचिन्हित दीर्घ statusbit,
				       काष्ठा flowi *fl)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	स्थिर काष्ठा nf_conntrack_tuple *t = &ct->tuplehash[dir].tuple;
	काष्ठा flowi6 *fl6 = &fl->u.ip6;

	अगर (ct->status & statusbit) अणु
		fl6->daddr = t->dst.u3.in6;
		अगर (t->dst.protonum == IPPROTO_TCP ||
		    t->dst.protonum == IPPROTO_UDP ||
		    t->dst.protonum == IPPROTO_UDPLITE ||
		    t->dst.protonum == IPPROTO_DCCP ||
		    t->dst.protonum == IPPROTO_SCTP)
			fl6->fl6_dport = t->dst.u.all;
	पूर्ण

	statusbit ^= IPS_NAT_MASK;

	अगर (ct->status & statusbit) अणु
		fl6->saddr = t->src.u3.in6;
		अगर (t->dst.protonum == IPPROTO_TCP ||
		    t->dst.protonum == IPPROTO_UDP ||
		    t->dst.protonum == IPPROTO_UDPLITE ||
		    t->dst.protonum == IPPROTO_DCCP ||
		    t->dst.protonum == IPPROTO_SCTP)
			fl6->fl6_sport = t->src.u.all;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम __nf_nat_decode_session(काष्ठा sk_buff *skb, काष्ठा flowi *fl)
अणु
	स्थिर काष्ठा nf_conn *ct;
	क्रमागत ip_conntrack_info ctinfo;
	क्रमागत ip_conntrack_dir dir;
	अचिन्हित  दीर्घ statusbit;
	u8 family;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (ct == शून्य)
		वापस;

	family = nf_ct_l3num(ct);
	dir = CTINFO2सूची(ctinfo);
	अगर (dir == IP_CT_सूची_ORIGINAL)
		statusbit = IPS_DST_NAT;
	अन्यथा
		statusbit = IPS_SRC_NAT;

	चयन (family) अणु
	हाल NFPROTO_IPV4:
		nf_nat_ipv4_decode_session(skb, ct, dir, statusbit, fl);
		वापस;
	हाल NFPROTO_IPV6:
		nf_nat_ipv6_decode_session(skb, ct, dir, statusbit, fl);
		वापस;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_XFRM */

/* We keep an extra hash क्रम each conntrack, क्रम fast searching. */
अटल अचिन्हित पूर्णांक
hash_by_src(स्थिर काष्ठा net *n, स्थिर काष्ठा nf_conntrack_tuple *tuple)
अणु
	अचिन्हित पूर्णांक hash;

	get_अक्रमom_once(&nf_nat_hash_rnd, माप(nf_nat_hash_rnd));

	/* Original src, to ensure we map it consistently अगर poss. */
	hash = jhash2((u32 *)&tuple->src, माप(tuple->src) / माप(u32),
		      tuple->dst.protonum ^ nf_nat_hash_rnd ^ net_hash_mix(n));

	वापस reciprocal_scale(hash, nf_nat_htable_size);
पूर्ण

/* Is this tuple alपढ़ोy taken? (not by us) */
अटल पूर्णांक
nf_nat_used_tuple(स्थिर काष्ठा nf_conntrack_tuple *tuple,
		  स्थिर काष्ठा nf_conn *ignored_conntrack)
अणु
	/* Conntrack tracking करोesn't keep track of outgoing tuples; only
	 * incoming ones.  NAT means they करोn't have a fixed mapping,
	 * so we invert the tuple and look क्रम the incoming reply.
	 *
	 * We could keep a separate hash अगर this proves too slow.
	 */
	काष्ठा nf_conntrack_tuple reply;

	nf_ct_invert_tuple(&reply, tuple);
	वापस nf_conntrack_tuple_taken(&reply, ignored_conntrack);
पूर्ण

अटल bool nf_nat_inet_in_range(स्थिर काष्ठा nf_conntrack_tuple *t,
				 स्थिर काष्ठा nf_nat_range2 *range)
अणु
	अगर (t->src.l3num == NFPROTO_IPV4)
		वापस ntohl(t->src.u3.ip) >= ntohl(range->min_addr.ip) &&
		       ntohl(t->src.u3.ip) <= ntohl(range->max_addr.ip);

	वापस ipv6_addr_cmp(&t->src.u3.in6, &range->min_addr.in6) >= 0 &&
	       ipv6_addr_cmp(&t->src.u3.in6, &range->max_addr.in6) <= 0;
पूर्ण

/* Is the manipable part of the tuple between min and max incl? */
अटल bool l4proto_in_range(स्थिर काष्ठा nf_conntrack_tuple *tuple,
			     क्रमागत nf_nat_manip_type maniptype,
			     स्थिर जोड़ nf_conntrack_man_proto *min,
			     स्थिर जोड़ nf_conntrack_man_proto *max)
अणु
	__be16 port;

	चयन (tuple->dst.protonum) अणु
	हाल IPPROTO_ICMP:
	हाल IPPROTO_ICMPV6:
		वापस ntohs(tuple->src.u.icmp.id) >= ntohs(min->icmp.id) &&
		       ntohs(tuple->src.u.icmp.id) <= ntohs(max->icmp.id);
	हाल IPPROTO_GRE: /* all fall though */
	हाल IPPROTO_TCP:
	हाल IPPROTO_UDP:
	हाल IPPROTO_UDPLITE:
	हाल IPPROTO_DCCP:
	हाल IPPROTO_SCTP:
		अगर (maniptype == NF_NAT_MANIP_SRC)
			port = tuple->src.u.all;
		अन्यथा
			port = tuple->dst.u.all;

		वापस ntohs(port) >= ntohs(min->all) &&
		       ntohs(port) <= ntohs(max->all);
	शेष:
		वापस true;
	पूर्ण
पूर्ण

/* If we source map this tuple so reply looks like reply_tuple, will
 * that meet the स्थिरraपूर्णांकs of range.
 */
अटल पूर्णांक in_range(स्थिर काष्ठा nf_conntrack_tuple *tuple,
		    स्थिर काष्ठा nf_nat_range2 *range)
अणु
	/* If we are supposed to map IPs, then we must be in the
	 * range specअगरied, otherwise let this drag us onto a new src IP.
	 */
	अगर (range->flags & NF_NAT_RANGE_MAP_IPS &&
	    !nf_nat_inet_in_range(tuple, range))
		वापस 0;

	अगर (!(range->flags & NF_NAT_RANGE_PROTO_SPECIFIED))
		वापस 1;

	वापस l4proto_in_range(tuple, NF_NAT_MANIP_SRC,
				&range->min_proto, &range->max_proto);
पूर्ण

अटल अंतरभूत पूर्णांक
same_src(स्थिर काष्ठा nf_conn *ct,
	 स्थिर काष्ठा nf_conntrack_tuple *tuple)
अणु
	स्थिर काष्ठा nf_conntrack_tuple *t;

	t = &ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple;
	वापस (t->dst.protonum == tuple->dst.protonum &&
		nf_inet_addr_cmp(&t->src.u3, &tuple->src.u3) &&
		t->src.u.all == tuple->src.u.all);
पूर्ण

/* Only called क्रम SRC manip */
अटल पूर्णांक
find_appropriate_src(काष्ठा net *net,
		     स्थिर काष्ठा nf_conntrack_zone *zone,
		     स्थिर काष्ठा nf_conntrack_tuple *tuple,
		     काष्ठा nf_conntrack_tuple *result,
		     स्थिर काष्ठा nf_nat_range2 *range)
अणु
	अचिन्हित पूर्णांक h = hash_by_src(net, tuple);
	स्थिर काष्ठा nf_conn *ct;

	hlist_क्रम_each_entry_rcu(ct, &nf_nat_bysource[h], nat_bysource) अणु
		अगर (same_src(ct, tuple) &&
		    net_eq(net, nf_ct_net(ct)) &&
		    nf_ct_zone_equal(ct, zone, IP_CT_सूची_ORIGINAL)) अणु
			/* Copy source part from reply tuple. */
			nf_ct_invert_tuple(result,
				       &ct->tuplehash[IP_CT_सूची_REPLY].tuple);
			result->dst = tuple->dst;

			अगर (in_range(result, range))
				वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* For [FUTURE] fragmentation handling, we want the least-used
 * src-ip/dst-ip/proto triple.  Fairness करोesn't come पूर्णांकo it.  Thus
 * अगर the range specअगरies 1.2.3.4 ports 10000-10005 and 1.2.3.5 ports
 * 1-65535, we करोn't करो pro-rata allocation based on ports; we choose
 * the ip with the lowest src-ip/dst-ip/proto usage.
 */
अटल व्योम
find_best_ips_proto(स्थिर काष्ठा nf_conntrack_zone *zone,
		    काष्ठा nf_conntrack_tuple *tuple,
		    स्थिर काष्ठा nf_nat_range2 *range,
		    स्थिर काष्ठा nf_conn *ct,
		    क्रमागत nf_nat_manip_type maniptype)
अणु
	जोड़ nf_inet_addr *var_ipp;
	अचिन्हित पूर्णांक i, max;
	/* Host order */
	u32 minip, maxip, j, dist;
	bool full_range;

	/* No IP mapping?  Do nothing. */
	अगर (!(range->flags & NF_NAT_RANGE_MAP_IPS))
		वापस;

	अगर (maniptype == NF_NAT_MANIP_SRC)
		var_ipp = &tuple->src.u3;
	अन्यथा
		var_ipp = &tuple->dst.u3;

	/* Fast path: only one choice. */
	अगर (nf_inet_addr_cmp(&range->min_addr, &range->max_addr)) अणु
		*var_ipp = range->min_addr;
		वापस;
	पूर्ण

	अगर (nf_ct_l3num(ct) == NFPROTO_IPV4)
		max = माप(var_ipp->ip) / माप(u32) - 1;
	अन्यथा
		max = माप(var_ipp->ip6) / माप(u32) - 1;

	/* Hashing source and destination IPs gives a fairly even
	 * spपढ़ो in practice (अगर there are a small number of IPs
	 * involved, there usually aren't that many connections
	 * anyway).  The consistency means that servers see the same
	 * client coming from the same IP (some Internet Banking sites
	 * like this), even across reboots.
	 */
	j = jhash2((u32 *)&tuple->src.u3, माप(tuple->src.u3) / माप(u32),
		   range->flags & NF_NAT_RANGE_PERSISTENT ?
			0 : (__क्रमce u32)tuple->dst.u3.all[max] ^ zone->id);

	full_range = false;
	क्रम (i = 0; i <= max; i++) अणु
		/* If first bytes of the address are at the maximum, use the
		 * distance. Otherwise use the full range.
		 */
		अगर (!full_range) अणु
			minip = ntohl((__क्रमce __be32)range->min_addr.all[i]);
			maxip = ntohl((__क्रमce __be32)range->max_addr.all[i]);
			dist  = maxip - minip + 1;
		पूर्ण अन्यथा अणु
			minip = 0;
			dist  = ~0;
		पूर्ण

		var_ipp->all[i] = (__क्रमce __u32)
			htonl(minip + reciprocal_scale(j, dist));
		अगर (var_ipp->all[i] != range->max_addr.all[i])
			full_range = true;

		अगर (!(range->flags & NF_NAT_RANGE_PERSISTENT))
			j ^= (__क्रमce u32)tuple->dst.u3.all[i];
	पूर्ण
पूर्ण

/* Alter the per-proto part of the tuple (depending on maniptype), to
 * give a unique tuple in the given range अगर possible.
 *
 * Per-protocol part of tuple is initialized to the incoming packet.
 */
अटल व्योम nf_nat_l4proto_unique_tuple(काष्ठा nf_conntrack_tuple *tuple,
					स्थिर काष्ठा nf_nat_range2 *range,
					क्रमागत nf_nat_manip_type maniptype,
					स्थिर काष्ठा nf_conn *ct)
अणु
	अचिन्हित पूर्णांक range_size, min, max, i, attempts;
	__be16 *keyptr;
	u16 off;
	अटल स्थिर अचिन्हित पूर्णांक max_attempts = 128;

	चयन (tuple->dst.protonum) अणु
	हाल IPPROTO_ICMP:
	हाल IPPROTO_ICMPV6:
		/* id is same क्रम either direction... */
		keyptr = &tuple->src.u.icmp.id;
		अगर (!(range->flags & NF_NAT_RANGE_PROTO_SPECIFIED)) अणु
			min = 0;
			range_size = 65536;
		पूर्ण अन्यथा अणु
			min = ntohs(range->min_proto.icmp.id);
			range_size = ntohs(range->max_proto.icmp.id) -
				     ntohs(range->min_proto.icmp.id) + 1;
		पूर्ण
		जाओ find_मुक्त_id;
#अगर IS_ENABLED(CONFIG_NF_CT_PROTO_GRE)
	हाल IPPROTO_GRE:
		/* If there is no master conntrack we are not PPTP,
		   करो not change tuples */
		अगर (!ct->master)
			वापस;

		अगर (maniptype == NF_NAT_MANIP_SRC)
			keyptr = &tuple->src.u.gre.key;
		अन्यथा
			keyptr = &tuple->dst.u.gre.key;

		अगर (!(range->flags & NF_NAT_RANGE_PROTO_SPECIFIED)) अणु
			min = 1;
			range_size = 65535;
		पूर्ण अन्यथा अणु
			min = ntohs(range->min_proto.gre.key);
			range_size = ntohs(range->max_proto.gre.key) - min + 1;
		पूर्ण
		जाओ find_मुक्त_id;
#पूर्ण_अगर
	हाल IPPROTO_UDP:
	हाल IPPROTO_UDPLITE:
	हाल IPPROTO_TCP:
	हाल IPPROTO_SCTP:
	हाल IPPROTO_DCCP:
		अगर (maniptype == NF_NAT_MANIP_SRC)
			keyptr = &tuple->src.u.all;
		अन्यथा
			keyptr = &tuple->dst.u.all;

		अवरोध;
	शेष:
		वापस;
	पूर्ण

	/* If no range specअगरied... */
	अगर (!(range->flags & NF_NAT_RANGE_PROTO_SPECIFIED)) अणु
		/* If it's dst rewrite, can't change port */
		अगर (maniptype == NF_NAT_MANIP_DST)
			वापस;

		अगर (ntohs(*keyptr) < 1024) अणु
			/* Loose convention: >> 512 is credential passing */
			अगर (ntohs(*keyptr) < 512) अणु
				min = 1;
				range_size = 511 - min + 1;
			पूर्ण अन्यथा अणु
				min = 600;
				range_size = 1023 - min + 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			min = 1024;
			range_size = 65535 - 1024 + 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		min = ntohs(range->min_proto.all);
		max = ntohs(range->max_proto.all);
		अगर (unlikely(max < min))
			swap(max, min);
		range_size = max - min + 1;
	पूर्ण

find_मुक्त_id:
	अगर (range->flags & NF_NAT_RANGE_PROTO_OFFSET)
		off = (ntohs(*keyptr) - ntohs(range->base_proto.all));
	अन्यथा
		off = pअक्रमom_u32();

	attempts = range_size;
	अगर (attempts > max_attempts)
		attempts = max_attempts;

	/* We are in softirq; करोing a search of the entire range risks
	 * soft lockup when all tuples are alपढ़ोy used.
	 *
	 * If we can't find any मुक्त port from first offset, pick a new
	 * one and try again, with ever smaller search winकरोw.
	 */
another_round:
	क्रम (i = 0; i < attempts; i++, off++) अणु
		*keyptr = htons(min + off % range_size);
		अगर (!nf_nat_used_tuple(tuple, ct))
			वापस;
	पूर्ण

	अगर (attempts >= range_size || attempts < 16)
		वापस;
	attempts /= 2;
	off = pअक्रमom_u32();
	जाओ another_round;
पूर्ण

/* Manipulate the tuple पूर्णांकo the range given. For NF_INET_POST_ROUTING,
 * we change the source to map पूर्णांकo the range. For NF_INET_PRE_ROUTING
 * and NF_INET_LOCAL_OUT, we change the destination to map पूर्णांकo the
 * range. It might not be possible to get a unique tuple, but we try.
 * At worst (or अगर we race), we will end up with a final duplicate in
 * __nf_conntrack_confirm and drop the packet. */
अटल व्योम
get_unique_tuple(काष्ठा nf_conntrack_tuple *tuple,
		 स्थिर काष्ठा nf_conntrack_tuple *orig_tuple,
		 स्थिर काष्ठा nf_nat_range2 *range,
		 काष्ठा nf_conn *ct,
		 क्रमागत nf_nat_manip_type maniptype)
अणु
	स्थिर काष्ठा nf_conntrack_zone *zone;
	काष्ठा net *net = nf_ct_net(ct);

	zone = nf_ct_zone(ct);

	/* 1) If this srcip/proto/src-proto-part is currently mapped,
	 * and that same mapping gives a unique tuple within the given
	 * range, use that.
	 *
	 * This is only required क्रम source (ie. NAT/masq) mappings.
	 * So far, we करोn't करो local source mappings, so multiple
	 * manips not an issue.
	 */
	अगर (maniptype == NF_NAT_MANIP_SRC &&
	    !(range->flags & NF_NAT_RANGE_PROTO_RANDOM_ALL)) अणु
		/* try the original tuple first */
		अगर (in_range(orig_tuple, range)) अणु
			अगर (!nf_nat_used_tuple(orig_tuple, ct)) अणु
				*tuple = *orig_tuple;
				वापस;
			पूर्ण
		पूर्ण अन्यथा अगर (find_appropriate_src(net, zone,
						orig_tuple, tuple, range)) अणु
			pr_debug("get_unique_tuple: Found current src map\n");
			अगर (!nf_nat_used_tuple(tuple, ct))
				वापस;
		पूर्ण
	पूर्ण

	/* 2) Select the least-used IP/proto combination in the given range */
	*tuple = *orig_tuple;
	find_best_ips_proto(zone, tuple, range, ct, maniptype);

	/* 3) The per-protocol part of the manip is made to map पूर्णांकo
	 * the range to make a unique tuple.
	 */

	/* Only bother mapping अगर it's not alपढ़ोy in range and unique */
	अगर (!(range->flags & NF_NAT_RANGE_PROTO_RANDOM_ALL)) अणु
		अगर (range->flags & NF_NAT_RANGE_PROTO_SPECIFIED) अणु
			अगर (!(range->flags & NF_NAT_RANGE_PROTO_OFFSET) &&
			    l4proto_in_range(tuple, maniptype,
			          &range->min_proto,
			          &range->max_proto) &&
			    (range->min_proto.all == range->max_proto.all ||
			     !nf_nat_used_tuple(tuple, ct)))
				वापस;
		पूर्ण अन्यथा अगर (!nf_nat_used_tuple(tuple, ct)) अणु
			वापस;
		पूर्ण
	पूर्ण

	/* Last chance: get protocol to try to obtain unique tuple. */
	nf_nat_l4proto_unique_tuple(tuple, range, maniptype, ct);
पूर्ण

काष्ठा nf_conn_nat *nf_ct_nat_ext_add(काष्ठा nf_conn *ct)
अणु
	काष्ठा nf_conn_nat *nat = nfct_nat(ct);
	अगर (nat)
		वापस nat;

	अगर (!nf_ct_is_confirmed(ct))
		nat = nf_ct_ext_add(ct, NF_CT_EXT_NAT, GFP_ATOMIC);

	वापस nat;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_nat_ext_add);

अचिन्हित पूर्णांक
nf_nat_setup_info(काष्ठा nf_conn *ct,
		  स्थिर काष्ठा nf_nat_range2 *range,
		  क्रमागत nf_nat_manip_type maniptype)
अणु
	काष्ठा net *net = nf_ct_net(ct);
	काष्ठा nf_conntrack_tuple curr_tuple, new_tuple;

	/* Can't setup nat info क्रम confirmed ct. */
	अगर (nf_ct_is_confirmed(ct))
		वापस NF_ACCEPT;

	WARN_ON(maniptype != NF_NAT_MANIP_SRC &&
		maniptype != NF_NAT_MANIP_DST);

	अगर (WARN_ON(nf_nat_initialized(ct, maniptype)))
		वापस NF_DROP;

	/* What we've got will look like inverse of reply. Normally
	 * this is what is in the conntrack, except क्रम prior
	 * manipulations (future optimization: अगर num_manips == 0,
	 * orig_tp = ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple)
	 */
	nf_ct_invert_tuple(&curr_tuple,
			   &ct->tuplehash[IP_CT_सूची_REPLY].tuple);

	get_unique_tuple(&new_tuple, &curr_tuple, range, ct, maniptype);

	अगर (!nf_ct_tuple_equal(&new_tuple, &curr_tuple)) अणु
		काष्ठा nf_conntrack_tuple reply;

		/* Alter conntrack table so will recognize replies. */
		nf_ct_invert_tuple(&reply, &new_tuple);
		nf_conntrack_alter_reply(ct, &reply);

		/* Non-atomic: we own this at the moment. */
		अगर (maniptype == NF_NAT_MANIP_SRC)
			ct->status |= IPS_SRC_NAT;
		अन्यथा
			ct->status |= IPS_DST_NAT;

		अगर (nfct_help(ct) && !nfct_seqadj(ct))
			अगर (!nfct_seqadj_ext_add(ct))
				वापस NF_DROP;
	पूर्ण

	अगर (maniptype == NF_NAT_MANIP_SRC) अणु
		अचिन्हित पूर्णांक srchash;
		spinlock_t *lock;

		srchash = hash_by_src(net,
				      &ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple);
		lock = &nf_nat_locks[srchash % CONNTRACK_LOCKS];
		spin_lock_bh(lock);
		hlist_add_head_rcu(&ct->nat_bysource,
				   &nf_nat_bysource[srchash]);
		spin_unlock_bh(lock);
	पूर्ण

	/* It's करोne. */
	अगर (maniptype == NF_NAT_MANIP_DST)
		ct->status |= IPS_DST_NAT_DONE;
	अन्यथा
		ct->status |= IPS_SRC_NAT_DONE;

	वापस NF_ACCEPT;
पूर्ण
EXPORT_SYMBOL(nf_nat_setup_info);

अटल अचिन्हित पूर्णांक
__nf_nat_alloc_null_binding(काष्ठा nf_conn *ct, क्रमागत nf_nat_manip_type manip)
अणु
	/* Force range to this IP; let proto decide mapping क्रम
	 * per-proto parts (hence not IP_NAT_RANGE_PROTO_SPECIFIED).
	 * Use reply in हाल it's alपढ़ोy been mangled (eg local packet).
	 */
	जोड़ nf_inet_addr ip =
		(manip == NF_NAT_MANIP_SRC ?
		ct->tuplehash[IP_CT_सूची_REPLY].tuple.dst.u3 :
		ct->tuplehash[IP_CT_सूची_REPLY].tuple.src.u3);
	काष्ठा nf_nat_range2 range = अणु
		.flags		= NF_NAT_RANGE_MAP_IPS,
		.min_addr	= ip,
		.max_addr	= ip,
	पूर्ण;
	वापस nf_nat_setup_info(ct, &range, manip);
पूर्ण

अचिन्हित पूर्णांक
nf_nat_alloc_null_binding(काष्ठा nf_conn *ct, अचिन्हित पूर्णांक hooknum)
अणु
	वापस __nf_nat_alloc_null_binding(ct, HOOK2MANIP(hooknum));
पूर्ण
EXPORT_SYMBOL_GPL(nf_nat_alloc_null_binding);

/* Do packet manipulations according to nf_nat_setup_info. */
अचिन्हित पूर्णांक nf_nat_packet(काष्ठा nf_conn *ct,
			   क्रमागत ip_conntrack_info ctinfo,
			   अचिन्हित पूर्णांक hooknum,
			   काष्ठा sk_buff *skb)
अणु
	क्रमागत nf_nat_manip_type mtype = HOOK2MANIP(hooknum);
	क्रमागत ip_conntrack_dir dir = CTINFO2सूची(ctinfo);
	अचिन्हित पूर्णांक verdict = NF_ACCEPT;
	अचिन्हित दीर्घ statusbit;

	अगर (mtype == NF_NAT_MANIP_SRC)
		statusbit = IPS_SRC_NAT;
	अन्यथा
		statusbit = IPS_DST_NAT;

	/* Invert अगर this is reply dir. */
	अगर (dir == IP_CT_सूची_REPLY)
		statusbit ^= IPS_NAT_MASK;

	/* Non-atomic: these bits करोn't change. */
	अगर (ct->status & statusbit)
		verdict = nf_nat_manip_pkt(skb, ct, mtype, dir);

	वापस verdict;
पूर्ण
EXPORT_SYMBOL_GPL(nf_nat_packet);

अचिन्हित पूर्णांक
nf_nat_inet_fn(व्योम *priv, काष्ठा sk_buff *skb,
	       स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा nf_conn *ct;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn_nat *nat;
	/* maniptype == SRC क्रम postrouting. */
	क्रमागत nf_nat_manip_type maniptype = HOOK2MANIP(state->hook);

	ct = nf_ct_get(skb, &ctinfo);
	/* Can't track?  It's not due to stress, or conntrack would
	 * have dropped it.  Hence it's the user's responsibilty to
	 * packet filter it out, or implement conntrack/NAT क्रम that
	 * protocol. 8) --RR
	 */
	अगर (!ct)
		वापस NF_ACCEPT;

	nat = nfct_nat(ct);

	चयन (ctinfo) अणु
	हाल IP_CT_RELATED:
	हाल IP_CT_RELATED_REPLY:
		/* Only ICMPs can be IP_CT_IS_REPLY.  Fallthrough */
	हाल IP_CT_NEW:
		/* Seen it beक्रमe?  This can happen क्रम loopback, retrans,
		 * or local packets.
		 */
		अगर (!nf_nat_initialized(ct, maniptype)) अणु
			काष्ठा nf_nat_lookup_hook_priv *lpriv = priv;
			काष्ठा nf_hook_entries *e = rcu_dereference(lpriv->entries);
			अचिन्हित पूर्णांक ret;
			पूर्णांक i;

			अगर (!e)
				जाओ null_bind;

			क्रम (i = 0; i < e->num_hook_entries; i++) अणु
				ret = e->hooks[i].hook(e->hooks[i].priv, skb,
						       state);
				अगर (ret != NF_ACCEPT)
					वापस ret;
				अगर (nf_nat_initialized(ct, maniptype))
					जाओ करो_nat;
			पूर्ण
null_bind:
			ret = nf_nat_alloc_null_binding(ct, state->hook);
			अगर (ret != NF_ACCEPT)
				वापस ret;
		पूर्ण अन्यथा अणु
			pr_debug("Already setup manip %s for ct %p (status bits 0x%lx)\n",
				 maniptype == NF_NAT_MANIP_SRC ? "SRC" : "DST",
				 ct, ct->status);
			अगर (nf_nat_oअगर_changed(state->hook, ctinfo, nat,
					       state->out))
				जाओ oअगर_changed;
		पूर्ण
		अवरोध;
	शेष:
		/* ESTABLISHED */
		WARN_ON(ctinfo != IP_CT_ESTABLISHED &&
			ctinfo != IP_CT_ESTABLISHED_REPLY);
		अगर (nf_nat_oअगर_changed(state->hook, ctinfo, nat, state->out))
			जाओ oअगर_changed;
	पूर्ण
करो_nat:
	वापस nf_nat_packet(ct, ctinfo, state->hook, skb);

oअगर_changed:
	nf_ct_समाप्त_acct(ct, ctinfo, skb);
	वापस NF_DROP;
पूर्ण
EXPORT_SYMBOL_GPL(nf_nat_inet_fn);

काष्ठा nf_nat_proto_clean अणु
	u8	l3proto;
	u8	l4proto;
पूर्ण;

/* समाप्त conntracks with affected NAT section */
अटल पूर्णांक nf_nat_proto_हटाओ(काष्ठा nf_conn *i, व्योम *data)
अणु
	स्थिर काष्ठा nf_nat_proto_clean *clean = data;

	अगर ((clean->l3proto && nf_ct_l3num(i) != clean->l3proto) ||
	    (clean->l4proto && nf_ct_protonum(i) != clean->l4proto))
		वापस 0;

	वापस i->status & IPS_NAT_MASK ? 1 : 0;
पूर्ण

अटल व्योम __nf_nat_cleanup_conntrack(काष्ठा nf_conn *ct)
अणु
	अचिन्हित पूर्णांक h;

	h = hash_by_src(nf_ct_net(ct), &ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple);
	spin_lock_bh(&nf_nat_locks[h % CONNTRACK_LOCKS]);
	hlist_del_rcu(&ct->nat_bysource);
	spin_unlock_bh(&nf_nat_locks[h % CONNTRACK_LOCKS]);
पूर्ण

अटल पूर्णांक nf_nat_proto_clean(काष्ठा nf_conn *ct, व्योम *data)
अणु
	अगर (nf_nat_proto_हटाओ(ct, data))
		वापस 1;

	/* This module is being हटाओd and conntrack has nat null binding.
	 * Remove it from bysource hash, as the table will be मुक्तd soon.
	 *
	 * Else, when the conntrack is destoyed, nf_nat_cleanup_conntrack()
	 * will delete entry from alपढ़ोy-मुक्तd table.
	 */
	अगर (test_and_clear_bit(IPS_SRC_NAT_DONE_BIT, &ct->status))
		__nf_nat_cleanup_conntrack(ct);

	/* करोn't delete conntrack.  Although that would make things a lot
	 * simpler, we'd end up flushing all conntracks on nat rmmod.
	 */
	वापस 0;
पूर्ण

/* No one using conntrack by the समय this called. */
अटल व्योम nf_nat_cleanup_conntrack(काष्ठा nf_conn *ct)
अणु
	अगर (ct->status & IPS_SRC_NAT_DONE)
		__nf_nat_cleanup_conntrack(ct);
पूर्ण

अटल काष्ठा nf_ct_ext_type nat_extend __पढ़ो_mostly = अणु
	.len		= माप(काष्ठा nf_conn_nat),
	.align		= __alignof__(काष्ठा nf_conn_nat),
	.destroy	= nf_nat_cleanup_conntrack,
	.id		= NF_CT_EXT_NAT,
पूर्ण;

#अगर IS_ENABLED(CONFIG_NF_CT_NETLINK)

#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nfnetlink_conntrack.h>

अटल स्थिर काष्ठा nla_policy protonat_nla_policy[CTA_PROTONAT_MAX+1] = अणु
	[CTA_PROTONAT_PORT_MIN]	= अणु .type = NLA_U16 पूर्ण,
	[CTA_PROTONAT_PORT_MAX]	= अणु .type = NLA_U16 पूर्ण,
पूर्ण;

अटल पूर्णांक nf_nat_l4proto_nlattr_to_range(काष्ठा nlattr *tb[],
					  काष्ठा nf_nat_range2 *range)
अणु
	अगर (tb[CTA_PROTONAT_PORT_MIN]) अणु
		range->min_proto.all = nla_get_be16(tb[CTA_PROTONAT_PORT_MIN]);
		range->max_proto.all = range->min_proto.all;
		range->flags |= NF_NAT_RANGE_PROTO_SPECIFIED;
	पूर्ण
	अगर (tb[CTA_PROTONAT_PORT_MAX]) अणु
		range->max_proto.all = nla_get_be16(tb[CTA_PROTONAT_PORT_MAX]);
		range->flags |= NF_NAT_RANGE_PROTO_SPECIFIED;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nfnetlink_parse_nat_proto(काष्ठा nlattr *attr,
				     स्थिर काष्ठा nf_conn *ct,
				     काष्ठा nf_nat_range2 *range)
अणु
	काष्ठा nlattr *tb[CTA_PROTONAT_MAX+1];
	पूर्णांक err;

	err = nla_parse_nested_deprecated(tb, CTA_PROTONAT_MAX, attr,
					  protonat_nla_policy, शून्य);
	अगर (err < 0)
		वापस err;

	वापस nf_nat_l4proto_nlattr_to_range(tb, range);
पूर्ण

अटल स्थिर काष्ठा nla_policy nat_nla_policy[CTA_NAT_MAX+1] = अणु
	[CTA_NAT_V4_MINIP]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_NAT_V4_MAXIP]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_NAT_V6_MINIP]	= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[CTA_NAT_V6_MAXIP]	= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[CTA_NAT_PROTO]		= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक nf_nat_ipv4_nlattr_to_range(काष्ठा nlattr *tb[],
				       काष्ठा nf_nat_range2 *range)
अणु
	अगर (tb[CTA_NAT_V4_MINIP]) अणु
		range->min_addr.ip = nla_get_be32(tb[CTA_NAT_V4_MINIP]);
		range->flags |= NF_NAT_RANGE_MAP_IPS;
	पूर्ण

	अगर (tb[CTA_NAT_V4_MAXIP])
		range->max_addr.ip = nla_get_be32(tb[CTA_NAT_V4_MAXIP]);
	अन्यथा
		range->max_addr.ip = range->min_addr.ip;

	वापस 0;
पूर्ण

अटल पूर्णांक nf_nat_ipv6_nlattr_to_range(काष्ठा nlattr *tb[],
				       काष्ठा nf_nat_range2 *range)
अणु
	अगर (tb[CTA_NAT_V6_MINIP]) अणु
		nla_स_नकल(&range->min_addr.ip6, tb[CTA_NAT_V6_MINIP],
			   माप(काष्ठा in6_addr));
		range->flags |= NF_NAT_RANGE_MAP_IPS;
	पूर्ण

	अगर (tb[CTA_NAT_V6_MAXIP])
		nla_स_नकल(&range->max_addr.ip6, tb[CTA_NAT_V6_MAXIP],
			   माप(काष्ठा in6_addr));
	अन्यथा
		range->max_addr = range->min_addr;

	वापस 0;
पूर्ण

अटल पूर्णांक
nfnetlink_parse_nat(स्थिर काष्ठा nlattr *nat,
		    स्थिर काष्ठा nf_conn *ct, काष्ठा nf_nat_range2 *range)
अणु
	काष्ठा nlattr *tb[CTA_NAT_MAX+1];
	पूर्णांक err;

	स_रखो(range, 0, माप(*range));

	err = nla_parse_nested_deprecated(tb, CTA_NAT_MAX, nat,
					  nat_nla_policy, शून्य);
	अगर (err < 0)
		वापस err;

	चयन (nf_ct_l3num(ct)) अणु
	हाल NFPROTO_IPV4:
		err = nf_nat_ipv4_nlattr_to_range(tb, range);
		अवरोध;
	हाल NFPROTO_IPV6:
		err = nf_nat_ipv6_nlattr_to_range(tb, range);
		अवरोध;
	शेष:
		err = -EPROTONOSUPPORT;
		अवरोध;
	पूर्ण

	अगर (err)
		वापस err;

	अगर (!tb[CTA_NAT_PROTO])
		वापस 0;

	वापस nfnetlink_parse_nat_proto(tb[CTA_NAT_PROTO], ct, range);
पूर्ण

/* This function is called under rcu_पढ़ो_lock() */
अटल पूर्णांक
nfnetlink_parse_nat_setup(काष्ठा nf_conn *ct,
			  क्रमागत nf_nat_manip_type manip,
			  स्थिर काष्ठा nlattr *attr)
अणु
	काष्ठा nf_nat_range2 range;
	पूर्णांक err;

	/* Should not happen, restricted to creating new conntracks
	 * via ctnetlink.
	 */
	अगर (WARN_ON_ONCE(nf_nat_initialized(ct, manip)))
		वापस -EEXIST;

	/* No NAT inक्रमmation has been passed, allocate the null-binding */
	अगर (attr == शून्य)
		वापस __nf_nat_alloc_null_binding(ct, manip) == NF_DROP ? -ENOMEM : 0;

	err = nfnetlink_parse_nat(attr, ct, &range);
	अगर (err < 0)
		वापस err;

	वापस nf_nat_setup_info(ct, &range, manip) == NF_DROP ? -ENOMEM : 0;
पूर्ण
#अन्यथा
अटल पूर्णांक
nfnetlink_parse_nat_setup(काष्ठा nf_conn *ct,
			  क्रमागत nf_nat_manip_type manip,
			  स्थिर काष्ठा nlattr *attr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा nf_ct_helper_expectfn follow_master_nat = अणु
	.name		= "nat-follow-master",
	.expectfn	= nf_nat_follow_master,
पूर्ण;

पूर्णांक nf_nat_रेजिस्टर_fn(काष्ठा net *net, u8 pf, स्थिर काष्ठा nf_hook_ops *ops,
		       स्थिर काष्ठा nf_hook_ops *orig_nat_ops, अचिन्हित पूर्णांक ops_count)
अणु
	काष्ठा nat_net *nat_net = net_generic(net, nat_net_id);
	काष्ठा nf_nat_hooks_net *nat_proto_net;
	काष्ठा nf_nat_lookup_hook_priv *priv;
	अचिन्हित पूर्णांक hooknum = ops->hooknum;
	काष्ठा nf_hook_ops *nat_ops;
	पूर्णांक i, ret;

	अगर (WARN_ON_ONCE(pf >= ARRAY_SIZE(nat_net->nat_proto_net)))
		वापस -EINVAL;

	nat_proto_net = &nat_net->nat_proto_net[pf];

	क्रम (i = 0; i < ops_count; i++) अणु
		अगर (orig_nat_ops[i].hooknum == hooknum) अणु
			hooknum = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (WARN_ON_ONCE(i == ops_count))
		वापस -EINVAL;

	mutex_lock(&nf_nat_proto_mutex);
	अगर (!nat_proto_net->nat_hook_ops) अणु
		WARN_ON(nat_proto_net->users != 0);

		nat_ops = kmemdup(orig_nat_ops, माप(*orig_nat_ops) * ops_count, GFP_KERNEL);
		अगर (!nat_ops) अणु
			mutex_unlock(&nf_nat_proto_mutex);
			वापस -ENOMEM;
		पूर्ण

		क्रम (i = 0; i < ops_count; i++) अणु
			priv = kzalloc(माप(*priv), GFP_KERNEL);
			अगर (priv) अणु
				nat_ops[i].priv = priv;
				जारी;
			पूर्ण
			mutex_unlock(&nf_nat_proto_mutex);
			जबतक (i)
				kमुक्त(nat_ops[--i].priv);
			kमुक्त(nat_ops);
			वापस -ENOMEM;
		पूर्ण

		ret = nf_रेजिस्टर_net_hooks(net, nat_ops, ops_count);
		अगर (ret < 0) अणु
			mutex_unlock(&nf_nat_proto_mutex);
			क्रम (i = 0; i < ops_count; i++)
				kमुक्त(nat_ops[i].priv);
			kमुक्त(nat_ops);
			वापस ret;
		पूर्ण

		nat_proto_net->nat_hook_ops = nat_ops;
	पूर्ण

	nat_ops = nat_proto_net->nat_hook_ops;
	priv = nat_ops[hooknum].priv;
	अगर (WARN_ON_ONCE(!priv)) अणु
		mutex_unlock(&nf_nat_proto_mutex);
		वापस -EOPNOTSUPP;
	पूर्ण

	ret = nf_hook_entries_insert_raw(&priv->entries, ops);
	अगर (ret == 0)
		nat_proto_net->users++;

	mutex_unlock(&nf_nat_proto_mutex);
	वापस ret;
पूर्ण

व्योम nf_nat_unरेजिस्टर_fn(काष्ठा net *net, u8 pf, स्थिर काष्ठा nf_hook_ops *ops,
			  अचिन्हित पूर्णांक ops_count)
अणु
	काष्ठा nat_net *nat_net = net_generic(net, nat_net_id);
	काष्ठा nf_nat_hooks_net *nat_proto_net;
	काष्ठा nf_nat_lookup_hook_priv *priv;
	काष्ठा nf_hook_ops *nat_ops;
	पूर्णांक hooknum = ops->hooknum;
	पूर्णांक i;

	अगर (pf >= ARRAY_SIZE(nat_net->nat_proto_net))
		वापस;

	nat_proto_net = &nat_net->nat_proto_net[pf];

	mutex_lock(&nf_nat_proto_mutex);
	अगर (WARN_ON(nat_proto_net->users == 0))
		जाओ unlock;

	nat_proto_net->users--;

	nat_ops = nat_proto_net->nat_hook_ops;
	क्रम (i = 0; i < ops_count; i++) अणु
		अगर (nat_ops[i].hooknum == hooknum) अणु
			hooknum = i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (WARN_ON_ONCE(i == ops_count))
		जाओ unlock;
	priv = nat_ops[hooknum].priv;
	nf_hook_entries_delete_raw(&priv->entries, ops);

	अगर (nat_proto_net->users == 0) अणु
		nf_unरेजिस्टर_net_hooks(net, nat_ops, ops_count);

		क्रम (i = 0; i < ops_count; i++) अणु
			priv = nat_ops[i].priv;
			kमुक्त_rcu(priv, rcu_head);
		पूर्ण

		nat_proto_net->nat_hook_ops = शून्य;
		kमुक्त(nat_ops);
	पूर्ण
unlock:
	mutex_unlock(&nf_nat_proto_mutex);
पूर्ण

अटल काष्ठा pernet_operations nat_net_ops = अणु
	.id = &nat_net_id,
	.size = माप(काष्ठा nat_net),
पूर्ण;

अटल काष्ठा nf_nat_hook nat_hook = अणु
	.parse_nat_setup	= nfnetlink_parse_nat_setup,
#अगर_घोषित CONFIG_XFRM
	.decode_session		= __nf_nat_decode_session,
#पूर्ण_अगर
	.manip_pkt		= nf_nat_manip_pkt,
पूर्ण;

अटल पूर्णांक __init nf_nat_init(व्योम)
अणु
	पूर्णांक ret, i;

	/* Leave them the same क्रम the moment. */
	nf_nat_htable_size = nf_conntrack_htable_size;
	अगर (nf_nat_htable_size < CONNTRACK_LOCKS)
		nf_nat_htable_size = CONNTRACK_LOCKS;

	nf_nat_bysource = nf_ct_alloc_hashtable(&nf_nat_htable_size, 0);
	अगर (!nf_nat_bysource)
		वापस -ENOMEM;

	ret = nf_ct_extend_रेजिस्टर(&nat_extend);
	अगर (ret < 0) अणु
		kvमुक्त(nf_nat_bysource);
		pr_err("Unable to register extension\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < CONNTRACK_LOCKS; i++)
		spin_lock_init(&nf_nat_locks[i]);

	ret = रेजिस्टर_pernet_subsys(&nat_net_ops);
	अगर (ret < 0) अणु
		nf_ct_extend_unरेजिस्टर(&nat_extend);
		kvमुक्त(nf_nat_bysource);
		वापस ret;
	पूर्ण

	nf_ct_helper_expectfn_रेजिस्टर(&follow_master_nat);

	WARN_ON(nf_nat_hook != शून्य);
	RCU_INIT_POINTER(nf_nat_hook, &nat_hook);

	वापस 0;
पूर्ण

अटल व्योम __निकास nf_nat_cleanup(व्योम)
अणु
	काष्ठा nf_nat_proto_clean clean = अणुपूर्ण;

	nf_ct_iterate_destroy(nf_nat_proto_clean, &clean);

	nf_ct_extend_unरेजिस्टर(&nat_extend);
	nf_ct_helper_expectfn_unरेजिस्टर(&follow_master_nat);
	RCU_INIT_POINTER(nf_nat_hook, शून्य);

	synchronize_net();
	kvमुक्त(nf_nat_bysource);
	unरेजिस्टर_pernet_subsys(&nat_net_ops);
पूर्ण

MODULE_LICENSE("GPL");

module_init(nf_nat_init);
module_निकास(nf_nat_cleanup);
