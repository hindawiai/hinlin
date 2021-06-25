<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		IPv4 Forwarding Inक्रमmation Base: semantics.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/bitops.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/netlink.h>

#समावेश <net/arp.h>
#समावेश <net/ip.h>
#समावेश <net/protocol.h>
#समावेश <net/route.h>
#समावेश <net/tcp.h>
#समावेश <net/sock.h>
#समावेश <net/ip_fib.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/nexthop.h>
#समावेश <net/netlink.h>
#समावेश <net/rtnh.h>
#समावेश <net/lwtunnel.h>
#समावेश <net/fib_notअगरier.h>
#समावेश <net/addrconf.h>

#समावेश "fib_lookup.h"

अटल DEFINE_SPINLOCK(fib_info_lock);
अटल काष्ठा hlist_head *fib_info_hash;
अटल काष्ठा hlist_head *fib_info_laddrhash;
अटल अचिन्हित पूर्णांक fib_info_hash_size;
अटल अचिन्हित पूर्णांक fib_info_cnt;

#घोषणा DEVINDEX_HASHBITS 8
#घोषणा DEVINDEX_HASHSIZE (1U << DEVINDEX_HASHBITS)
अटल काष्ठा hlist_head fib_info_devhash[DEVINDEX_HASHSIZE];

/* क्रम_nexthops and change_nexthops only used when nexthop object
 * is not set in a fib_info. The logic within can reference fib_nh.
 */
#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH

#घोषणा क्रम_nexthops(fi) अणु						\
	पूर्णांक nhsel; स्थिर काष्ठा fib_nh *nh;				\
	क्रम (nhsel = 0, nh = (fi)->fib_nh;				\
	     nhsel < fib_info_num_path((fi));				\
	     nh++, nhsel++)

#घोषणा change_nexthops(fi) अणु						\
	पूर्णांक nhsel; काष्ठा fib_nh *nexthop_nh;				\
	क्रम (nhsel = 0,	nexthop_nh = (काष्ठा fib_nh *)((fi)->fib_nh);	\
	     nhsel < fib_info_num_path((fi));				\
	     nexthop_nh++, nhsel++)

#अन्यथा /* CONFIG_IP_ROUTE_MULTIPATH */

/* Hope, that gcc will optimize it to get rid of dummy loop */

#घोषणा क्रम_nexthops(fi) अणु						\
	पूर्णांक nhsel; स्थिर काष्ठा fib_nh *nh = (fi)->fib_nh;		\
	क्रम (nhsel = 0; nhsel < 1; nhsel++)

#घोषणा change_nexthops(fi) अणु						\
	पूर्णांक nhsel;							\
	काष्ठा fib_nh *nexthop_nh = (काष्ठा fib_nh *)((fi)->fib_nh);	\
	क्रम (nhsel = 0; nhsel < 1; nhsel++)

#पूर्ण_अगर /* CONFIG_IP_ROUTE_MULTIPATH */

#घोषणा endक्रम_nexthops(fi) पूर्ण


स्थिर काष्ठा fib_prop fib_props[RTN_MAX + 1] = अणु
	[RTN_UNSPEC] = अणु
		.error	= 0,
		.scope	= RT_SCOPE_NOWHERE,
	पूर्ण,
	[RTN_UNICAST] = अणु
		.error	= 0,
		.scope	= RT_SCOPE_UNIVERSE,
	पूर्ण,
	[RTN_LOCAL] = अणु
		.error	= 0,
		.scope	= RT_SCOPE_HOST,
	पूर्ण,
	[RTN_BROADCAST] = अणु
		.error	= 0,
		.scope	= RT_SCOPE_LINK,
	पूर्ण,
	[RTN_ANYCAST] = अणु
		.error	= 0,
		.scope	= RT_SCOPE_LINK,
	पूर्ण,
	[RTN_MULTICAST] = अणु
		.error	= 0,
		.scope	= RT_SCOPE_UNIVERSE,
	पूर्ण,
	[RTN_BLACKHOLE] = अणु
		.error	= -EINVAL,
		.scope	= RT_SCOPE_UNIVERSE,
	पूर्ण,
	[RTN_UNREACHABLE] = अणु
		.error	= -EHOSTUNREACH,
		.scope	= RT_SCOPE_UNIVERSE,
	पूर्ण,
	[RTN_PROHIBIT] = अणु
		.error	= -EACCES,
		.scope	= RT_SCOPE_UNIVERSE,
	पूर्ण,
	[RTN_THROW] = अणु
		.error	= -EAGAIN,
		.scope	= RT_SCOPE_UNIVERSE,
	पूर्ण,
	[RTN_NAT] = अणु
		.error	= -EINVAL,
		.scope	= RT_SCOPE_NOWHERE,
	पूर्ण,
	[RTN_XRESOLVE] = अणु
		.error	= -EINVAL,
		.scope	= RT_SCOPE_NOWHERE,
	पूर्ण,
पूर्ण;

अटल व्योम rt_fibinfo_मुक्त(काष्ठा rtable __rcu **rtp)
अणु
	काष्ठा rtable *rt = rcu_dereference_रक्षित(*rtp, 1);

	अगर (!rt)
		वापस;

	/* Not even needed : RCU_INIT_POINTER(*rtp, शून्य);
	 * because we रुकोed an RCU grace period beक्रमe calling
	 * मुक्त_fib_info_rcu()
	 */

	dst_dev_put(&rt->dst);
	dst_release_immediate(&rt->dst);
पूर्ण

अटल व्योम मुक्त_nh_exceptions(काष्ठा fib_nh_common *nhc)
अणु
	काष्ठा fnhe_hash_bucket *hash;
	पूर्णांक i;

	hash = rcu_dereference_रक्षित(nhc->nhc_exceptions, 1);
	अगर (!hash)
		वापस;
	क्रम (i = 0; i < FNHE_HASH_SIZE; i++) अणु
		काष्ठा fib_nh_exception *fnhe;

		fnhe = rcu_dereference_रक्षित(hash[i].chain, 1);
		जबतक (fnhe) अणु
			काष्ठा fib_nh_exception *next;

			next = rcu_dereference_रक्षित(fnhe->fnhe_next, 1);

			rt_fibinfo_मुक्त(&fnhe->fnhe_rth_input);
			rt_fibinfo_मुक्त(&fnhe->fnhe_rth_output);

			kमुक्त(fnhe);

			fnhe = next;
		पूर्ण
	पूर्ण
	kमुक्त(hash);
पूर्ण

अटल व्योम rt_fibinfo_मुक्त_cpus(काष्ठा rtable __rcu * __percpu *rtp)
अणु
	पूर्णांक cpu;

	अगर (!rtp)
		वापस;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा rtable *rt;

		rt = rcu_dereference_रक्षित(*per_cpu_ptr(rtp, cpu), 1);
		अगर (rt) अणु
			dst_dev_put(&rt->dst);
			dst_release_immediate(&rt->dst);
		पूर्ण
	पूर्ण
	मुक्त_percpu(rtp);
पूर्ण

व्योम fib_nh_common_release(काष्ठा fib_nh_common *nhc)
अणु
	अगर (nhc->nhc_dev)
		dev_put(nhc->nhc_dev);

	lwtstate_put(nhc->nhc_lwtstate);
	rt_fibinfo_मुक्त_cpus(nhc->nhc_pcpu_rth_output);
	rt_fibinfo_मुक्त(&nhc->nhc_rth_input);
	मुक्त_nh_exceptions(nhc);
पूर्ण
EXPORT_SYMBOL_GPL(fib_nh_common_release);

व्योम fib_nh_release(काष्ठा net *net, काष्ठा fib_nh *fib_nh)
अणु
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	अगर (fib_nh->nh_tclassid)
		net->ipv4.fib_num_tclassid_users--;
#पूर्ण_अगर
	fib_nh_common_release(&fib_nh->nh_common);
पूर्ण

/* Release a nexthop info record */
अटल व्योम मुक्त_fib_info_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा fib_info *fi = container_of(head, काष्ठा fib_info, rcu);

	अगर (fi->nh) अणु
		nexthop_put(fi->nh);
	पूर्ण अन्यथा अणु
		change_nexthops(fi) अणु
			fib_nh_release(fi->fib_net, nexthop_nh);
		पूर्ण endक्रम_nexthops(fi);
	पूर्ण

	ip_fib_metrics_put(fi->fib_metrics);

	kमुक्त(fi);
पूर्ण

व्योम मुक्त_fib_info(काष्ठा fib_info *fi)
अणु
	अगर (fi->fib_dead == 0) अणु
		pr_warn("Freeing alive fib_info %p\n", fi);
		वापस;
	पूर्ण
	fib_info_cnt--;

	call_rcu(&fi->rcu, मुक्त_fib_info_rcu);
पूर्ण
EXPORT_SYMBOL_GPL(मुक्त_fib_info);

व्योम fib_release_info(काष्ठा fib_info *fi)
अणु
	spin_lock_bh(&fib_info_lock);
	अगर (fi && --fi->fib_treeref == 0) अणु
		hlist_del(&fi->fib_hash);
		अगर (fi->fib_prefsrc)
			hlist_del(&fi->fib_lhash);
		अगर (fi->nh) अणु
			list_del(&fi->nh_list);
		पूर्ण अन्यथा अणु
			change_nexthops(fi) अणु
				अगर (!nexthop_nh->fib_nh_dev)
					जारी;
				hlist_del(&nexthop_nh->nh_hash);
			पूर्ण endक्रम_nexthops(fi)
		पूर्ण
		fi->fib_dead = 1;
		fib_info_put(fi);
	पूर्ण
	spin_unlock_bh(&fib_info_lock);
पूर्ण

अटल अंतरभूत पूर्णांक nh_comp(काष्ठा fib_info *fi, काष्ठा fib_info *ofi)
अणु
	स्थिर काष्ठा fib_nh *onh;

	अगर (fi->nh || ofi->nh)
		वापस nexthop_cmp(fi->nh, ofi->nh) ? 0 : -1;

	अगर (ofi->fib_nhs == 0)
		वापस 0;

	क्रम_nexthops(fi) अणु
		onh = fib_info_nh(ofi, nhsel);

		अगर (nh->fib_nh_oअगर != onh->fib_nh_oअगर ||
		    nh->fib_nh_gw_family != onh->fib_nh_gw_family ||
		    nh->fib_nh_scope != onh->fib_nh_scope ||
#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH
		    nh->fib_nh_weight != onh->fib_nh_weight ||
#पूर्ण_अगर
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
		    nh->nh_tclassid != onh->nh_tclassid ||
#पूर्ण_अगर
		    lwtunnel_cmp_encap(nh->fib_nh_lws, onh->fib_nh_lws) ||
		    ((nh->fib_nh_flags ^ onh->fib_nh_flags) & ~RTNH_COMPARE_MASK))
			वापस -1;

		अगर (nh->fib_nh_gw_family == AF_INET &&
		    nh->fib_nh_gw4 != onh->fib_nh_gw4)
			वापस -1;

		अगर (nh->fib_nh_gw_family == AF_INET6 &&
		    ipv6_addr_cmp(&nh->fib_nh_gw6, &onh->fib_nh_gw6))
			वापस -1;
	पूर्ण endक्रम_nexthops(fi);
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक fib_devindex_hashfn(अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक mask = DEVINDEX_HASHSIZE - 1;

	वापस (val ^
		(val >> DEVINDEX_HASHBITS) ^
		(val >> (DEVINDEX_HASHBITS * 2))) & mask;
पूर्ण

अटल अचिन्हित पूर्णांक fib_info_hashfn_1(पूर्णांक init_val, u8 protocol, u8 scope,
				      u32 prefsrc, u32 priority)
अणु
	अचिन्हित पूर्णांक val = init_val;

	val ^= (protocol << 8) | scope;
	val ^= prefsrc;
	val ^= priority;

	वापस val;
पूर्ण

अटल अचिन्हित पूर्णांक fib_info_hashfn_result(अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक mask = (fib_info_hash_size - 1);

	वापस (val ^ (val >> 7) ^ (val >> 12)) & mask;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक fib_info_hashfn(काष्ठा fib_info *fi)
अणु
	अचिन्हित पूर्णांक val;

	val = fib_info_hashfn_1(fi->fib_nhs, fi->fib_protocol,
				fi->fib_scope, (__क्रमce u32)fi->fib_prefsrc,
				fi->fib_priority);

	अगर (fi->nh) अणु
		val ^= fib_devindex_hashfn(fi->nh->id);
	पूर्ण अन्यथा अणु
		क्रम_nexthops(fi) अणु
			val ^= fib_devindex_hashfn(nh->fib_nh_oअगर);
		पूर्ण endक्रम_nexthops(fi)
	पूर्ण

	वापस fib_info_hashfn_result(val);
पूर्ण

/* no metrics, only nexthop id */
अटल काष्ठा fib_info *fib_find_info_nh(काष्ठा net *net,
					 स्थिर काष्ठा fib_config *cfg)
अणु
	काष्ठा hlist_head *head;
	काष्ठा fib_info *fi;
	अचिन्हित पूर्णांक hash;

	hash = fib_info_hashfn_1(fib_devindex_hashfn(cfg->fc_nh_id),
				 cfg->fc_protocol, cfg->fc_scope,
				 (__क्रमce u32)cfg->fc_prefsrc,
				 cfg->fc_priority);
	hash = fib_info_hashfn_result(hash);
	head = &fib_info_hash[hash];

	hlist_क्रम_each_entry(fi, head, fib_hash) अणु
		अगर (!net_eq(fi->fib_net, net))
			जारी;
		अगर (!fi->nh || fi->nh->id != cfg->fc_nh_id)
			जारी;
		अगर (cfg->fc_protocol == fi->fib_protocol &&
		    cfg->fc_scope == fi->fib_scope &&
		    cfg->fc_prefsrc == fi->fib_prefsrc &&
		    cfg->fc_priority == fi->fib_priority &&
		    cfg->fc_type == fi->fib_type &&
		    cfg->fc_table == fi->fib_tb_id &&
		    !((cfg->fc_flags ^ fi->fib_flags) & ~RTNH_COMPARE_MASK))
			वापस fi;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा fib_info *fib_find_info(काष्ठा fib_info *nfi)
अणु
	काष्ठा hlist_head *head;
	काष्ठा fib_info *fi;
	अचिन्हित पूर्णांक hash;

	hash = fib_info_hashfn(nfi);
	head = &fib_info_hash[hash];

	hlist_क्रम_each_entry(fi, head, fib_hash) अणु
		अगर (!net_eq(fi->fib_net, nfi->fib_net))
			जारी;
		अगर (fi->fib_nhs != nfi->fib_nhs)
			जारी;
		अगर (nfi->fib_protocol == fi->fib_protocol &&
		    nfi->fib_scope == fi->fib_scope &&
		    nfi->fib_prefsrc == fi->fib_prefsrc &&
		    nfi->fib_priority == fi->fib_priority &&
		    nfi->fib_type == fi->fib_type &&
		    स_भेद(nfi->fib_metrics, fi->fib_metrics,
			   माप(u32) * RTAX_MAX) == 0 &&
		    !((nfi->fib_flags ^ fi->fib_flags) & ~RTNH_COMPARE_MASK) &&
		    nh_comp(fi, nfi) == 0)
			वापस fi;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Check, that the gateway is alपढ़ोy configured.
 * Used only by redirect accept routine.
 */
पूर्णांक ip_fib_check_शेष(__be32 gw, काष्ठा net_device *dev)
अणु
	काष्ठा hlist_head *head;
	काष्ठा fib_nh *nh;
	अचिन्हित पूर्णांक hash;

	spin_lock(&fib_info_lock);

	hash = fib_devindex_hashfn(dev->अगरindex);
	head = &fib_info_devhash[hash];
	hlist_क्रम_each_entry(nh, head, nh_hash) अणु
		अगर (nh->fib_nh_dev == dev &&
		    nh->fib_nh_gw4 == gw &&
		    !(nh->fib_nh_flags & RTNH_F_DEAD)) अणु
			spin_unlock(&fib_info_lock);
			वापस 0;
		पूर्ण
	पूर्ण

	spin_unlock(&fib_info_lock);

	वापस -1;
पूर्ण

माप_प्रकार fib_nlmsg_size(काष्ठा fib_info *fi)
अणु
	माप_प्रकार payload = NLMSG_ALIGN(माप(काष्ठा rपंचांगsg))
			 + nla_total_size(4) /* RTA_TABLE */
			 + nla_total_size(4) /* RTA_DST */
			 + nla_total_size(4) /* RTA_PRIORITY */
			 + nla_total_size(4) /* RTA_PREFSRC */
			 + nla_total_size(TCP_CA_NAME_MAX); /* RTAX_CC_ALGO */
	अचिन्हित पूर्णांक nhs = fib_info_num_path(fi);

	/* space क्रम nested metrics */
	payload += nla_total_size((RTAX_MAX * nla_total_size(4)));

	अगर (fi->nh)
		payload += nla_total_size(4); /* RTA_NH_ID */

	अगर (nhs) अणु
		माप_प्रकार nh_encapsize = 0;
		/* Also handles the special हाल nhs == 1 */

		/* each nexthop is packed in an attribute */
		माप_प्रकार nhsize = nla_total_size(माप(काष्ठा rtnexthop));
		अचिन्हित पूर्णांक i;

		/* may contain flow and gateway attribute */
		nhsize += 2 * nla_total_size(4);

		/* grab encap info */
		क्रम (i = 0; i < fib_info_num_path(fi); i++) अणु
			काष्ठा fib_nh_common *nhc = fib_info_nhc(fi, i);

			अगर (nhc->nhc_lwtstate) अणु
				/* RTA_ENCAP_TYPE */
				nh_encapsize += lwtunnel_get_encap_size(
						nhc->nhc_lwtstate);
				/* RTA_ENCAP */
				nh_encapsize +=  nla_total_size(2);
			पूर्ण
		पूर्ण

		/* all nexthops are packed in a nested attribute */
		payload += nla_total_size((nhs * nhsize) + nh_encapsize);

	पूर्ण

	वापस payload;
पूर्ण

व्योम rपंचांगsg_fib(पूर्णांक event, __be32 key, काष्ठा fib_alias *fa,
	       पूर्णांक dst_len, u32 tb_id, स्थिर काष्ठा nl_info *info,
	       अचिन्हित पूर्णांक nlm_flags)
अणु
	काष्ठा fib_rt_info fri;
	काष्ठा sk_buff *skb;
	u32 seq = info->nlh ? info->nlh->nlmsg_seq : 0;
	पूर्णांक err = -ENOBUFS;

	skb = nlmsg_new(fib_nlmsg_size(fa->fa_info), GFP_KERNEL);
	अगर (!skb)
		जाओ errout;

	fri.fi = fa->fa_info;
	fri.tb_id = tb_id;
	fri.dst = key;
	fri.dst_len = dst_len;
	fri.tos = fa->fa_tos;
	fri.type = fa->fa_type;
	fri.offload = fa->offload;
	fri.trap = fa->trap;
	fri.offload_failed = fa->offload_failed;
	err = fib_dump_info(skb, info->portid, seq, event, &fri, nlm_flags);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in fib_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण
	rtnl_notअगरy(skb, info->nl_net, info->portid, RTNLGRP_IPV4_ROUTE,
		    info->nlh, GFP_KERNEL);
	वापस;
errout:
	अगर (err < 0)
		rtnl_set_sk_err(info->nl_net, RTNLGRP_IPV4_ROUTE, err);
पूर्ण

अटल पूर्णांक fib_detect_death(काष्ठा fib_info *fi, पूर्णांक order,
			    काष्ठा fib_info **last_resort, पूर्णांक *last_idx,
			    पूर्णांक dflt)
अणु
	स्थिर काष्ठा fib_nh_common *nhc = fib_info_nhc(fi, 0);
	काष्ठा neighbour *n;
	पूर्णांक state = NUD_NONE;

	अगर (likely(nhc->nhc_gw_family == AF_INET))
		n = neigh_lookup(&arp_tbl, &nhc->nhc_gw.ipv4, nhc->nhc_dev);
	अन्यथा अगर (nhc->nhc_gw_family == AF_INET6)
		n = neigh_lookup(ipv6_stub->nd_tbl, &nhc->nhc_gw.ipv6,
				 nhc->nhc_dev);
	अन्यथा
		n = शून्य;

	अगर (n) अणु
		state = n->nud_state;
		neigh_release(n);
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
	अगर (state == NUD_REACHABLE)
		वापस 0;
	अगर ((state & NUD_VALID) && order != dflt)
		वापस 0;
	अगर ((state & NUD_VALID) ||
	    (*last_idx < 0 && order > dflt && state != NUD_INCOMPLETE)) अणु
		*last_resort = fi;
		*last_idx = order;
	पूर्ण
	वापस 1;
पूर्ण

पूर्णांक fib_nh_common_init(काष्ठा net *net, काष्ठा fib_nh_common *nhc,
		       काष्ठा nlattr *encap, u16 encap_type,
		       व्योम *cfg, gfp_t gfp_flags,
		       काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	nhc->nhc_pcpu_rth_output = alloc_percpu_gfp(काष्ठा rtable __rcu *,
						    gfp_flags);
	अगर (!nhc->nhc_pcpu_rth_output)
		वापस -ENOMEM;

	अगर (encap) अणु
		काष्ठा lwtunnel_state *lwtstate;

		अगर (encap_type == LWTUNNEL_ENCAP_NONE) अणु
			NL_SET_ERR_MSG(extack, "LWT encap type not specified");
			err = -EINVAL;
			जाओ lwt_failure;
		पूर्ण
		err = lwtunnel_build_state(net, encap_type, encap,
					   nhc->nhc_family, cfg, &lwtstate,
					   extack);
		अगर (err)
			जाओ lwt_failure;

		nhc->nhc_lwtstate = lwtstate_get(lwtstate);
	पूर्ण

	वापस 0;

lwt_failure:
	rt_fibinfo_मुक्त_cpus(nhc->nhc_pcpu_rth_output);
	nhc->nhc_pcpu_rth_output = शून्य;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(fib_nh_common_init);

पूर्णांक fib_nh_init(काष्ठा net *net, काष्ठा fib_nh *nh,
		काष्ठा fib_config *cfg, पूर्णांक nh_weight,
		काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	nh->fib_nh_family = AF_INET;

	err = fib_nh_common_init(net, &nh->nh_common, cfg->fc_encap,
				 cfg->fc_encap_type, cfg, GFP_KERNEL, extack);
	अगर (err)
		वापस err;

	nh->fib_nh_oअगर = cfg->fc_oअगर;
	nh->fib_nh_gw_family = cfg->fc_gw_family;
	अगर (cfg->fc_gw_family == AF_INET)
		nh->fib_nh_gw4 = cfg->fc_gw4;
	अन्यथा अगर (cfg->fc_gw_family == AF_INET6)
		nh->fib_nh_gw6 = cfg->fc_gw6;

	nh->fib_nh_flags = cfg->fc_flags;

#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	nh->nh_tclassid = cfg->fc_flow;
	अगर (nh->nh_tclassid)
		net->ipv4.fib_num_tclassid_users++;
#पूर्ण_अगर
#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH
	nh->fib_nh_weight = nh_weight;
#पूर्ण_अगर
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH

अटल पूर्णांक fib_count_nexthops(काष्ठा rtnexthop *rtnh, पूर्णांक reमुख्यing,
			      काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक nhs = 0;

	जबतक (rtnh_ok(rtnh, reमुख्यing)) अणु
		nhs++;
		rtnh = rtnh_next(rtnh, &reमुख्यing);
	पूर्ण

	/* leftover implies invalid nexthop configuration, discard it */
	अगर (reमुख्यing > 0) अणु
		NL_SET_ERR_MSG(extack,
			       "Invalid nexthop configuration - extra data after nexthops");
		nhs = 0;
	पूर्ण

	वापस nhs;
पूर्ण

/* only called when fib_nh is पूर्णांकegrated पूर्णांकo fib_info */
अटल पूर्णांक fib_get_nhs(काष्ठा fib_info *fi, काष्ठा rtnexthop *rtnh,
		       पूर्णांक reमुख्यing, काष्ठा fib_config *cfg,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = fi->fib_net;
	काष्ठा fib_config fib_cfg;
	काष्ठा fib_nh *nh;
	पूर्णांक ret;

	change_nexthops(fi) अणु
		पूर्णांक attrlen;

		स_रखो(&fib_cfg, 0, माप(fib_cfg));

		अगर (!rtnh_ok(rtnh, reमुख्यing)) अणु
			NL_SET_ERR_MSG(extack,
				       "Invalid nexthop configuration - extra data after nexthop");
			वापस -EINVAL;
		पूर्ण

		अगर (rtnh->rtnh_flags & (RTNH_F_DEAD | RTNH_F_LINKDOWN)) अणु
			NL_SET_ERR_MSG(extack,
				       "Invalid flags for nexthop - can not contain DEAD or LINKDOWN");
			वापस -EINVAL;
		पूर्ण

		fib_cfg.fc_flags = (cfg->fc_flags & ~0xFF) | rtnh->rtnh_flags;
		fib_cfg.fc_oअगर = rtnh->rtnh_अगरindex;

		attrlen = rtnh_attrlen(rtnh);
		अगर (attrlen > 0) अणु
			काष्ठा nlattr *nla, *nlav, *attrs = rtnh_attrs(rtnh);

			nla = nla_find(attrs, attrlen, RTA_GATEWAY);
			nlav = nla_find(attrs, attrlen, RTA_VIA);
			अगर (nla && nlav) अणु
				NL_SET_ERR_MSG(extack,
					       "Nexthop configuration can not contain both GATEWAY and VIA");
				वापस -EINVAL;
			पूर्ण
			अगर (nla) अणु
				fib_cfg.fc_gw4 = nla_get_in_addr(nla);
				अगर (fib_cfg.fc_gw4)
					fib_cfg.fc_gw_family = AF_INET;
			पूर्ण अन्यथा अगर (nlav) अणु
				ret = fib_gw_from_via(&fib_cfg, nlav, extack);
				अगर (ret)
					जाओ errout;
			पूर्ण

			nla = nla_find(attrs, attrlen, RTA_FLOW);
			अगर (nla)
				fib_cfg.fc_flow = nla_get_u32(nla);

			fib_cfg.fc_encap = nla_find(attrs, attrlen, RTA_ENCAP);
			nla = nla_find(attrs, attrlen, RTA_ENCAP_TYPE);
			अगर (nla)
				fib_cfg.fc_encap_type = nla_get_u16(nla);
		पूर्ण

		ret = fib_nh_init(net, nexthop_nh, &fib_cfg,
				  rtnh->rtnh_hops + 1, extack);
		अगर (ret)
			जाओ errout;

		rtnh = rtnh_next(rtnh, &reमुख्यing);
	पूर्ण endक्रम_nexthops(fi);

	ret = -EINVAL;
	nh = fib_info_nh(fi, 0);
	अगर (cfg->fc_oअगर && nh->fib_nh_oअगर != cfg->fc_oअगर) अणु
		NL_SET_ERR_MSG(extack,
			       "Nexthop device index does not match RTA_OIF");
		जाओ errout;
	पूर्ण
	अगर (cfg->fc_gw_family) अणु
		अगर (cfg->fc_gw_family != nh->fib_nh_gw_family ||
		    (cfg->fc_gw_family == AF_INET &&
		     nh->fib_nh_gw4 != cfg->fc_gw4) ||
		    (cfg->fc_gw_family == AF_INET6 &&
		     ipv6_addr_cmp(&nh->fib_nh_gw6, &cfg->fc_gw6))) अणु
			NL_SET_ERR_MSG(extack,
				       "Nexthop gateway does not match RTA_GATEWAY or RTA_VIA");
			जाओ errout;
		पूर्ण
	पूर्ण
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	अगर (cfg->fc_flow && nh->nh_tclassid != cfg->fc_flow) अणु
		NL_SET_ERR_MSG(extack,
			       "Nexthop class id does not match RTA_FLOW");
		जाओ errout;
	पूर्ण
#पूर्ण_अगर
	ret = 0;
errout:
	वापस ret;
पूर्ण

/* only called when fib_nh is पूर्णांकegrated पूर्णांकo fib_info */
अटल व्योम fib_rebalance(काष्ठा fib_info *fi)
अणु
	पूर्णांक total;
	पूर्णांक w;

	अगर (fib_info_num_path(fi) < 2)
		वापस;

	total = 0;
	क्रम_nexthops(fi) अणु
		अगर (nh->fib_nh_flags & RTNH_F_DEAD)
			जारी;

		अगर (ip_ignore_linkकरोwn(nh->fib_nh_dev) &&
		    nh->fib_nh_flags & RTNH_F_LINKDOWN)
			जारी;

		total += nh->fib_nh_weight;
	पूर्ण endक्रम_nexthops(fi);

	w = 0;
	change_nexthops(fi) अणु
		पूर्णांक upper_bound;

		अगर (nexthop_nh->fib_nh_flags & RTNH_F_DEAD) अणु
			upper_bound = -1;
		पूर्ण अन्यथा अगर (ip_ignore_linkकरोwn(nexthop_nh->fib_nh_dev) &&
			   nexthop_nh->fib_nh_flags & RTNH_F_LINKDOWN) अणु
			upper_bound = -1;
		पूर्ण अन्यथा अणु
			w += nexthop_nh->fib_nh_weight;
			upper_bound = DIV_ROUND_CLOSEST_ULL((u64)w << 31,
							    total) - 1;
		पूर्ण

		atomic_set(&nexthop_nh->fib_nh_upper_bound, upper_bound);
	पूर्ण endक्रम_nexthops(fi);
पूर्ण
#अन्यथा /* CONFIG_IP_ROUTE_MULTIPATH */

अटल पूर्णांक fib_get_nhs(काष्ठा fib_info *fi, काष्ठा rtnexthop *rtnh,
		       पूर्णांक reमुख्यing, काष्ठा fib_config *cfg,
		       काष्ठा netlink_ext_ack *extack)
अणु
	NL_SET_ERR_MSG(extack, "Multipath support not enabled in kernel");

	वापस -EINVAL;
पूर्ण

#घोषणा fib_rebalance(fi) करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर /* CONFIG_IP_ROUTE_MULTIPATH */

अटल पूर्णांक fib_encap_match(काष्ठा net *net, u16 encap_type,
			   काष्ठा nlattr *encap,
			   स्थिर काष्ठा fib_nh *nh,
			   स्थिर काष्ठा fib_config *cfg,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा lwtunnel_state *lwtstate;
	पूर्णांक ret, result = 0;

	अगर (encap_type == LWTUNNEL_ENCAP_NONE)
		वापस 0;

	ret = lwtunnel_build_state(net, encap_type, encap, AF_INET,
				   cfg, &lwtstate, extack);
	अगर (!ret) अणु
		result = lwtunnel_cmp_encap(lwtstate, nh->fib_nh_lws);
		lwtstate_मुक्त(lwtstate);
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक fib_nh_match(काष्ठा net *net, काष्ठा fib_config *cfg, काष्ठा fib_info *fi,
		 काष्ठा netlink_ext_ack *extack)
अणु
#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH
	काष्ठा rtnexthop *rtnh;
	पूर्णांक reमुख्यing;
#पूर्ण_अगर

	अगर (cfg->fc_priority && cfg->fc_priority != fi->fib_priority)
		वापस 1;

	अगर (cfg->fc_nh_id) अणु
		अगर (fi->nh && cfg->fc_nh_id == fi->nh->id)
			वापस 0;
		वापस 1;
	पूर्ण

	अगर (cfg->fc_oअगर || cfg->fc_gw_family) अणु
		काष्ठा fib_nh *nh = fib_info_nh(fi, 0);

		अगर (cfg->fc_encap) अणु
			अगर (fib_encap_match(net, cfg->fc_encap_type,
					    cfg->fc_encap, nh, cfg, extack))
				वापस 1;
		पूर्ण
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
		अगर (cfg->fc_flow &&
		    cfg->fc_flow != nh->nh_tclassid)
			वापस 1;
#पूर्ण_अगर
		अगर ((cfg->fc_oअगर && cfg->fc_oअगर != nh->fib_nh_oअगर) ||
		    (cfg->fc_gw_family &&
		     cfg->fc_gw_family != nh->fib_nh_gw_family))
			वापस 1;

		अगर (cfg->fc_gw_family == AF_INET &&
		    cfg->fc_gw4 != nh->fib_nh_gw4)
			वापस 1;

		अगर (cfg->fc_gw_family == AF_INET6 &&
		    ipv6_addr_cmp(&cfg->fc_gw6, &nh->fib_nh_gw6))
			वापस 1;

		वापस 0;
	पूर्ण

#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH
	अगर (!cfg->fc_mp)
		वापस 0;

	rtnh = cfg->fc_mp;
	reमुख्यing = cfg->fc_mp_len;

	क्रम_nexthops(fi) अणु
		पूर्णांक attrlen;

		अगर (!rtnh_ok(rtnh, reमुख्यing))
			वापस -EINVAL;

		अगर (rtnh->rtnh_अगरindex && rtnh->rtnh_अगरindex != nh->fib_nh_oअगर)
			वापस 1;

		attrlen = rtnh_attrlen(rtnh);
		अगर (attrlen > 0) अणु
			काष्ठा nlattr *nla, *nlav, *attrs = rtnh_attrs(rtnh);

			nla = nla_find(attrs, attrlen, RTA_GATEWAY);
			nlav = nla_find(attrs, attrlen, RTA_VIA);
			अगर (nla && nlav) अणु
				NL_SET_ERR_MSG(extack,
					       "Nexthop configuration can not contain both GATEWAY and VIA");
				वापस -EINVAL;
			पूर्ण

			अगर (nla) अणु
				अगर (nh->fib_nh_gw_family != AF_INET ||
				    nla_get_in_addr(nla) != nh->fib_nh_gw4)
					वापस 1;
			पूर्ण अन्यथा अगर (nlav) अणु
				काष्ठा fib_config cfg2;
				पूर्णांक err;

				err = fib_gw_from_via(&cfg2, nlav, extack);
				अगर (err)
					वापस err;

				चयन (nh->fib_nh_gw_family) अणु
				हाल AF_INET:
					अगर (cfg2.fc_gw_family != AF_INET ||
					    cfg2.fc_gw4 != nh->fib_nh_gw4)
						वापस 1;
					अवरोध;
				हाल AF_INET6:
					अगर (cfg2.fc_gw_family != AF_INET6 ||
					    ipv6_addr_cmp(&cfg2.fc_gw6,
							  &nh->fib_nh_gw6))
						वापस 1;
					अवरोध;
				पूर्ण
			पूर्ण

#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
			nla = nla_find(attrs, attrlen, RTA_FLOW);
			अगर (nla && nla_get_u32(nla) != nh->nh_tclassid)
				वापस 1;
#पूर्ण_अगर
		पूर्ण

		rtnh = rtnh_next(rtnh, &reमुख्यing);
	पूर्ण endक्रम_nexthops(fi);
#पूर्ण_अगर
	वापस 0;
पूर्ण

bool fib_metrics_match(काष्ठा fib_config *cfg, काष्ठा fib_info *fi)
अणु
	काष्ठा nlattr *nla;
	पूर्णांक reमुख्यing;

	अगर (!cfg->fc_mx)
		वापस true;

	nla_क्रम_each_attr(nla, cfg->fc_mx, cfg->fc_mx_len, reमुख्यing) अणु
		पूर्णांक type = nla_type(nla);
		u32 fi_val, val;

		अगर (!type)
			जारी;
		अगर (type > RTAX_MAX)
			वापस false;

		अगर (type == RTAX_CC_ALGO) अणु
			अक्षर पंचांगp[TCP_CA_NAME_MAX];
			bool ecn_ca = false;

			nla_strscpy(पंचांगp, nla, माप(पंचांगp));
			val = tcp_ca_get_key_by_name(fi->fib_net, पंचांगp, &ecn_ca);
		पूर्ण अन्यथा अणु
			अगर (nla_len(nla) != माप(u32))
				वापस false;
			val = nla_get_u32(nla);
		पूर्ण

		fi_val = fi->fib_metrics->metrics[type - 1];
		अगर (type == RTAX_FEATURES)
			fi_val &= ~DST_FEATURE_ECN_CA;

		अगर (fi_val != val)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक fib_check_nh_v6_gw(काष्ठा net *net, काष्ठा fib_nh *nh,
			      u32 table, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib6_config cfg = अणु
		.fc_table = table,
		.fc_flags = nh->fib_nh_flags | RTF_GATEWAY,
		.fc_अगरindex = nh->fib_nh_oअगर,
		.fc_gateway = nh->fib_nh_gw6,
	पूर्ण;
	काष्ठा fib6_nh fib6_nh = अणुपूर्ण;
	पूर्णांक err;

	err = ipv6_stub->fib6_nh_init(net, &fib6_nh, &cfg, GFP_KERNEL, extack);
	अगर (!err) अणु
		nh->fib_nh_dev = fib6_nh.fib_nh_dev;
		dev_hold(nh->fib_nh_dev);
		nh->fib_nh_oअगर = nh->fib_nh_dev->अगरindex;
		nh->fib_nh_scope = RT_SCOPE_LINK;

		ipv6_stub->fib6_nh_release(&fib6_nh);
	पूर्ण

	वापस err;
पूर्ण

/*
 * Picture
 * -------
 *
 * Semantics of nexthop is very messy by historical reasons.
 * We have to take पूर्णांकo account, that:
 * a) gateway can be actually local पूर्णांकerface address,
 *    so that gatewayed route is direct.
 * b) gateway must be on-link address, possibly
 *    described not by an अगरaddr, but also by a direct route.
 * c) If both gateway and पूर्णांकerface are specअगरied, they should not
 *    contradict.
 * d) If we use tunnel routes, gateway could be not on-link.
 *
 * Attempt to reconcile all of these (alas, self-contradictory) conditions
 * results in pretty ugly and hairy code with obscure logic.
 *
 * I chose to generalized it instead, so that the size
 * of code करोes not increase practically, but it becomes
 * much more general.
 * Every prefix is asचिन्हित a "scope" value: "host" is local address,
 * "link" is direct route,
 * [ ... "site" ... "interior" ... ]
 * and "universe" is true gateway route with global meaning.
 *
 * Every prefix refers to a set of "nexthop"s (gw, oअगर),
 * where gw must have narrower scope. This recursion stops
 * when gw has LOCAL scope or अगर "nexthop" is declared ONLINK,
 * which means that gw is क्रमced to be on link.
 *
 * Code is still hairy, but now it is apparently logically
 * consistent and very flexible. F.e. as by-product it allows
 * to co-exists in peace independent exterior and पूर्णांकerior
 * routing processes.
 *
 * Normally it looks as following.
 *
 * अणुuniverse prefixपूर्ण  -> (gw, oअगर) [scope link]
 *		  |
 *		  |-> अणुlink prefixपूर्ण -> (gw, oअगर) [scope local]
 *					|
 *					|-> अणुlocal prefixपूर्ण (terminal node)
 */
अटल पूर्णांक fib_check_nh_v4_gw(काष्ठा net *net, काष्ठा fib_nh *nh, u32 table,
			      u8 scope, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *dev;
	काष्ठा fib_result res;
	पूर्णांक err = 0;

	अगर (nh->fib_nh_flags & RTNH_F_ONLINK) अणु
		अचिन्हित पूर्णांक addr_type;

		अगर (scope >= RT_SCOPE_LINK) अणु
			NL_SET_ERR_MSG(extack, "Nexthop has invalid scope");
			वापस -EINVAL;
		पूर्ण
		dev = __dev_get_by_index(net, nh->fib_nh_oअगर);
		अगर (!dev) अणु
			NL_SET_ERR_MSG(extack, "Nexthop device required for onlink");
			वापस -ENODEV;
		पूर्ण
		अगर (!(dev->flags & IFF_UP)) अणु
			NL_SET_ERR_MSG(extack, "Nexthop device is not up");
			वापस -ENETDOWN;
		पूर्ण
		addr_type = inet_addr_type_dev_table(net, dev, nh->fib_nh_gw4);
		अगर (addr_type != RTN_UNICAST) अणु
			NL_SET_ERR_MSG(extack, "Nexthop has invalid gateway");
			वापस -EINVAL;
		पूर्ण
		अगर (!netअगर_carrier_ok(dev))
			nh->fib_nh_flags |= RTNH_F_LINKDOWN;
		nh->fib_nh_dev = dev;
		dev_hold(dev);
		nh->fib_nh_scope = RT_SCOPE_LINK;
		वापस 0;
	पूर्ण
	rcu_पढ़ो_lock();
	अणु
		काष्ठा fib_table *tbl = शून्य;
		काष्ठा flowi4 fl4 = अणु
			.daddr = nh->fib_nh_gw4,
			.flowi4_scope = scope + 1,
			.flowi4_oअगर = nh->fib_nh_oअगर,
			.flowi4_iअगर = LOOPBACK_IFINDEX,
		पूर्ण;

		/* It is not necessary, but requires a bit of thinking */
		अगर (fl4.flowi4_scope < RT_SCOPE_LINK)
			fl4.flowi4_scope = RT_SCOPE_LINK;

		अगर (table && table != RT_TABLE_MAIN)
			tbl = fib_get_table(net, table);

		अगर (tbl)
			err = fib_table_lookup(tbl, &fl4, &res,
					       FIB_LOOKUP_IGNORE_LINKSTATE |
					       FIB_LOOKUP_NOREF);

		/* on error or अगर no table given करो full lookup. This
		 * is needed क्रम example when nexthops are in the local
		 * table rather than the given table
		 */
		अगर (!tbl || err) अणु
			err = fib_lookup(net, &fl4, &res,
					 FIB_LOOKUP_IGNORE_LINKSTATE);
		पूर्ण

		अगर (err) अणु
			NL_SET_ERR_MSG(extack, "Nexthop has invalid gateway");
			जाओ out;
		पूर्ण
	पूर्ण

	err = -EINVAL;
	अगर (res.type != RTN_UNICAST && res.type != RTN_LOCAL) अणु
		NL_SET_ERR_MSG(extack, "Nexthop has invalid gateway");
		जाओ out;
	पूर्ण
	nh->fib_nh_scope = res.scope;
	nh->fib_nh_oअगर = FIB_RES_OIF(res);
	nh->fib_nh_dev = dev = FIB_RES_DEV(res);
	अगर (!dev) अणु
		NL_SET_ERR_MSG(extack,
			       "No egress device for nexthop gateway");
		जाओ out;
	पूर्ण
	dev_hold(dev);
	अगर (!netअगर_carrier_ok(dev))
		nh->fib_nh_flags |= RTNH_F_LINKDOWN;
	err = (dev->flags & IFF_UP) ? 0 : -ENETDOWN;
out:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक fib_check_nh_nongw(काष्ठा net *net, काष्ठा fib_nh *nh,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा in_device *in_dev;
	पूर्णांक err;

	अगर (nh->fib_nh_flags & (RTNH_F_PERVASIVE | RTNH_F_ONLINK)) अणु
		NL_SET_ERR_MSG(extack,
			       "Invalid flags for nexthop - PERVASIVE and ONLINK can not be set");
		वापस -EINVAL;
	पूर्ण

	rcu_पढ़ो_lock();

	err = -ENODEV;
	in_dev = inetdev_by_index(net, nh->fib_nh_oअगर);
	अगर (!in_dev)
		जाओ out;
	err = -ENETDOWN;
	अगर (!(in_dev->dev->flags & IFF_UP)) अणु
		NL_SET_ERR_MSG(extack, "Device for nexthop is not up");
		जाओ out;
	पूर्ण

	nh->fib_nh_dev = in_dev->dev;
	dev_hold(nh->fib_nh_dev);
	nh->fib_nh_scope = RT_SCOPE_HOST;
	अगर (!netअगर_carrier_ok(nh->fib_nh_dev))
		nh->fib_nh_flags |= RTNH_F_LINKDOWN;
	err = 0;
out:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

पूर्णांक fib_check_nh(काष्ठा net *net, काष्ठा fib_nh *nh, u32 table, u8 scope,
		 काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	अगर (nh->fib_nh_gw_family == AF_INET)
		err = fib_check_nh_v4_gw(net, nh, table, scope, extack);
	अन्यथा अगर (nh->fib_nh_gw_family == AF_INET6)
		err = fib_check_nh_v6_gw(net, nh, table, extack);
	अन्यथा
		err = fib_check_nh_nongw(net, nh, extack);

	वापस err;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक fib_laddr_hashfn(__be32 val)
अणु
	अचिन्हित पूर्णांक mask = (fib_info_hash_size - 1);

	वापस ((__क्रमce u32)val ^
		((__क्रमce u32)val >> 7) ^
		((__क्रमce u32)val >> 14)) & mask;
पूर्ण

अटल काष्ठा hlist_head *fib_info_hash_alloc(पूर्णांक bytes)
अणु
	अगर (bytes <= PAGE_SIZE)
		वापस kzalloc(bytes, GFP_KERNEL);
	अन्यथा
		वापस (काष्ठा hlist_head *)
			__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO,
					 get_order(bytes));
पूर्ण

अटल व्योम fib_info_hash_मुक्त(काष्ठा hlist_head *hash, पूर्णांक bytes)
अणु
	अगर (!hash)
		वापस;

	अगर (bytes <= PAGE_SIZE)
		kमुक्त(hash);
	अन्यथा
		मुक्त_pages((अचिन्हित दीर्घ) hash, get_order(bytes));
पूर्ण

अटल व्योम fib_info_hash_move(काष्ठा hlist_head *new_info_hash,
			       काष्ठा hlist_head *new_laddrhash,
			       अचिन्हित पूर्णांक new_size)
अणु
	काष्ठा hlist_head *old_info_hash, *old_laddrhash;
	अचिन्हित पूर्णांक old_size = fib_info_hash_size;
	अचिन्हित पूर्णांक i, bytes;

	spin_lock_bh(&fib_info_lock);
	old_info_hash = fib_info_hash;
	old_laddrhash = fib_info_laddrhash;
	fib_info_hash_size = new_size;

	क्रम (i = 0; i < old_size; i++) अणु
		काष्ठा hlist_head *head = &fib_info_hash[i];
		काष्ठा hlist_node *n;
		काष्ठा fib_info *fi;

		hlist_क्रम_each_entry_safe(fi, n, head, fib_hash) अणु
			काष्ठा hlist_head *dest;
			अचिन्हित पूर्णांक new_hash;

			new_hash = fib_info_hashfn(fi);
			dest = &new_info_hash[new_hash];
			hlist_add_head(&fi->fib_hash, dest);
		पूर्ण
	पूर्ण
	fib_info_hash = new_info_hash;

	क्रम (i = 0; i < old_size; i++) अणु
		काष्ठा hlist_head *lhead = &fib_info_laddrhash[i];
		काष्ठा hlist_node *n;
		काष्ठा fib_info *fi;

		hlist_क्रम_each_entry_safe(fi, n, lhead, fib_lhash) अणु
			काष्ठा hlist_head *ldest;
			अचिन्हित पूर्णांक new_hash;

			new_hash = fib_laddr_hashfn(fi->fib_prefsrc);
			ldest = &new_laddrhash[new_hash];
			hlist_add_head(&fi->fib_lhash, ldest);
		पूर्ण
	पूर्ण
	fib_info_laddrhash = new_laddrhash;

	spin_unlock_bh(&fib_info_lock);

	bytes = old_size * माप(काष्ठा hlist_head *);
	fib_info_hash_मुक्त(old_info_hash, bytes);
	fib_info_hash_मुक्त(old_laddrhash, bytes);
पूर्ण

__be32 fib_info_update_nhc_saddr(काष्ठा net *net, काष्ठा fib_nh_common *nhc,
				 अचिन्हित अक्षर scope)
अणु
	काष्ठा fib_nh *nh;

	अगर (nhc->nhc_family != AF_INET)
		वापस inet_select_addr(nhc->nhc_dev, 0, scope);

	nh = container_of(nhc, काष्ठा fib_nh, nh_common);
	nh->nh_saddr = inet_select_addr(nh->fib_nh_dev, nh->fib_nh_gw4, scope);
	nh->nh_saddr_genid = atomic_पढ़ो(&net->ipv4.dev_addr_genid);

	वापस nh->nh_saddr;
पूर्ण

__be32 fib_result_prefsrc(काष्ठा net *net, काष्ठा fib_result *res)
अणु
	काष्ठा fib_nh_common *nhc = res->nhc;

	अगर (res->fi->fib_prefsrc)
		वापस res->fi->fib_prefsrc;

	अगर (nhc->nhc_family == AF_INET) अणु
		काष्ठा fib_nh *nh;

		nh = container_of(nhc, काष्ठा fib_nh, nh_common);
		अगर (nh->nh_saddr_genid == atomic_पढ़ो(&net->ipv4.dev_addr_genid))
			वापस nh->nh_saddr;
	पूर्ण

	वापस fib_info_update_nhc_saddr(net, nhc, res->fi->fib_scope);
पूर्ण

अटल bool fib_valid_prefsrc(काष्ठा fib_config *cfg, __be32 fib_prefsrc)
अणु
	अगर (cfg->fc_type != RTN_LOCAL || !cfg->fc_dst ||
	    fib_prefsrc != cfg->fc_dst) अणु
		u32 tb_id = cfg->fc_table;
		पूर्णांक rc;

		अगर (tb_id == RT_TABLE_MAIN)
			tb_id = RT_TABLE_LOCAL;

		rc = inet_addr_type_table(cfg->fc_nlinfo.nl_net,
					  fib_prefsrc, tb_id);

		अगर (rc != RTN_LOCAL && tb_id != RT_TABLE_LOCAL) अणु
			rc = inet_addr_type_table(cfg->fc_nlinfo.nl_net,
						  fib_prefsrc, RT_TABLE_LOCAL);
		पूर्ण

		अगर (rc != RTN_LOCAL)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

काष्ठा fib_info *fib_create_info(काष्ठा fib_config *cfg,
				 काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;
	काष्ठा fib_info *fi = शून्य;
	काष्ठा nexthop *nh = शून्य;
	काष्ठा fib_info *ofi;
	पूर्णांक nhs = 1;
	काष्ठा net *net = cfg->fc_nlinfo.nl_net;

	अगर (cfg->fc_type > RTN_MAX)
		जाओ err_inval;

	/* Fast check to catch the most weird हालs */
	अगर (fib_props[cfg->fc_type].scope > cfg->fc_scope) अणु
		NL_SET_ERR_MSG(extack, "Invalid scope");
		जाओ err_inval;
	पूर्ण

	अगर (cfg->fc_flags & (RTNH_F_DEAD | RTNH_F_LINKDOWN)) अणु
		NL_SET_ERR_MSG(extack,
			       "Invalid rtm_flags - can not contain DEAD or LINKDOWN");
		जाओ err_inval;
	पूर्ण

	अगर (cfg->fc_nh_id) अणु
		अगर (!cfg->fc_mx) अणु
			fi = fib_find_info_nh(net, cfg);
			अगर (fi) अणु
				fi->fib_treeref++;
				वापस fi;
			पूर्ण
		पूर्ण

		nh = nexthop_find_by_id(net, cfg->fc_nh_id);
		अगर (!nh) अणु
			NL_SET_ERR_MSG(extack, "Nexthop id does not exist");
			जाओ err_inval;
		पूर्ण
		nhs = 0;
	पूर्ण

#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH
	अगर (cfg->fc_mp) अणु
		nhs = fib_count_nexthops(cfg->fc_mp, cfg->fc_mp_len, extack);
		अगर (nhs == 0)
			जाओ err_inval;
	पूर्ण
#पूर्ण_अगर

	err = -ENOBUFS;
	अगर (fib_info_cnt >= fib_info_hash_size) अणु
		अचिन्हित पूर्णांक new_size = fib_info_hash_size << 1;
		काष्ठा hlist_head *new_info_hash;
		काष्ठा hlist_head *new_laddrhash;
		अचिन्हित पूर्णांक bytes;

		अगर (!new_size)
			new_size = 16;
		bytes = new_size * माप(काष्ठा hlist_head *);
		new_info_hash = fib_info_hash_alloc(bytes);
		new_laddrhash = fib_info_hash_alloc(bytes);
		अगर (!new_info_hash || !new_laddrhash) अणु
			fib_info_hash_मुक्त(new_info_hash, bytes);
			fib_info_hash_मुक्त(new_laddrhash, bytes);
		पूर्ण अन्यथा
			fib_info_hash_move(new_info_hash, new_laddrhash, new_size);

		अगर (!fib_info_hash_size)
			जाओ failure;
	पूर्ण

	fi = kzalloc(काष्ठा_size(fi, fib_nh, nhs), GFP_KERNEL);
	अगर (!fi)
		जाओ failure;
	fi->fib_metrics = ip_fib_metrics_init(fi->fib_net, cfg->fc_mx,
					      cfg->fc_mx_len, extack);
	अगर (IS_ERR(fi->fib_metrics)) अणु
		err = PTR_ERR(fi->fib_metrics);
		kमुक्त(fi);
		वापस ERR_PTR(err);
	पूर्ण

	fib_info_cnt++;
	fi->fib_net = net;
	fi->fib_protocol = cfg->fc_protocol;
	fi->fib_scope = cfg->fc_scope;
	fi->fib_flags = cfg->fc_flags;
	fi->fib_priority = cfg->fc_priority;
	fi->fib_prefsrc = cfg->fc_prefsrc;
	fi->fib_type = cfg->fc_type;
	fi->fib_tb_id = cfg->fc_table;

	fi->fib_nhs = nhs;
	अगर (nh) अणु
		अगर (!nexthop_get(nh)) अणु
			NL_SET_ERR_MSG(extack, "Nexthop has been deleted");
			err = -EINVAL;
		पूर्ण अन्यथा अणु
			err = 0;
			fi->nh = nh;
		पूर्ण
	पूर्ण अन्यथा अणु
		change_nexthops(fi) अणु
			nexthop_nh->nh_parent = fi;
		पूर्ण endक्रम_nexthops(fi)

		अगर (cfg->fc_mp)
			err = fib_get_nhs(fi, cfg->fc_mp, cfg->fc_mp_len, cfg,
					  extack);
		अन्यथा
			err = fib_nh_init(net, fi->fib_nh, cfg, 1, extack);
	पूर्ण

	अगर (err != 0)
		जाओ failure;

	अगर (fib_props[cfg->fc_type].error) अणु
		अगर (cfg->fc_gw_family || cfg->fc_oअगर || cfg->fc_mp) अणु
			NL_SET_ERR_MSG(extack,
				       "Gateway, device and multipath can not be specified for this route type");
			जाओ err_inval;
		पूर्ण
		जाओ link_it;
	पूर्ण अन्यथा अणु
		चयन (cfg->fc_type) अणु
		हाल RTN_UNICAST:
		हाल RTN_LOCAL:
		हाल RTN_BROADCAST:
		हाल RTN_ANYCAST:
		हाल RTN_MULTICAST:
			अवरोध;
		शेष:
			NL_SET_ERR_MSG(extack, "Invalid route type");
			जाओ err_inval;
		पूर्ण
	पूर्ण

	अगर (cfg->fc_scope > RT_SCOPE_HOST) अणु
		NL_SET_ERR_MSG(extack, "Invalid scope");
		जाओ err_inval;
	पूर्ण

	अगर (fi->nh) अणु
		err = fib_check_nexthop(fi->nh, cfg->fc_scope, extack);
		अगर (err)
			जाओ failure;
	पूर्ण अन्यथा अगर (cfg->fc_scope == RT_SCOPE_HOST) अणु
		काष्ठा fib_nh *nh = fi->fib_nh;

		/* Local address is added. */
		अगर (nhs != 1) अणु
			NL_SET_ERR_MSG(extack,
				       "Route with host scope can not have multiple nexthops");
			जाओ err_inval;
		पूर्ण
		अगर (nh->fib_nh_gw_family) अणु
			NL_SET_ERR_MSG(extack,
				       "Route with host scope can not have a gateway");
			जाओ err_inval;
		पूर्ण
		nh->fib_nh_scope = RT_SCOPE_NOWHERE;
		nh->fib_nh_dev = dev_get_by_index(net, nh->fib_nh_oअगर);
		err = -ENODEV;
		अगर (!nh->fib_nh_dev)
			जाओ failure;
	पूर्ण अन्यथा अणु
		पूर्णांक linkकरोwn = 0;

		change_nexthops(fi) अणु
			err = fib_check_nh(cfg->fc_nlinfo.nl_net, nexthop_nh,
					   cfg->fc_table, cfg->fc_scope,
					   extack);
			अगर (err != 0)
				जाओ failure;
			अगर (nexthop_nh->fib_nh_flags & RTNH_F_LINKDOWN)
				linkकरोwn++;
		पूर्ण endक्रम_nexthops(fi)
		अगर (linkकरोwn == fi->fib_nhs)
			fi->fib_flags |= RTNH_F_LINKDOWN;
	पूर्ण

	अगर (fi->fib_prefsrc && !fib_valid_prefsrc(cfg, fi->fib_prefsrc)) अणु
		NL_SET_ERR_MSG(extack, "Invalid prefsrc address");
		जाओ err_inval;
	पूर्ण

	अगर (!fi->nh) अणु
		change_nexthops(fi) अणु
			fib_info_update_nhc_saddr(net, &nexthop_nh->nh_common,
						  fi->fib_scope);
			अगर (nexthop_nh->fib_nh_gw_family == AF_INET6)
				fi->fib_nh_is_v6 = true;
		पूर्ण endक्रम_nexthops(fi)

		fib_rebalance(fi);
	पूर्ण

link_it:
	ofi = fib_find_info(fi);
	अगर (ofi) अणु
		fi->fib_dead = 1;
		मुक्त_fib_info(fi);
		ofi->fib_treeref++;
		वापस ofi;
	पूर्ण

	fi->fib_treeref++;
	refcount_set(&fi->fib_clntref, 1);
	spin_lock_bh(&fib_info_lock);
	hlist_add_head(&fi->fib_hash,
		       &fib_info_hash[fib_info_hashfn(fi)]);
	अगर (fi->fib_prefsrc) अणु
		काष्ठा hlist_head *head;

		head = &fib_info_laddrhash[fib_laddr_hashfn(fi->fib_prefsrc)];
		hlist_add_head(&fi->fib_lhash, head);
	पूर्ण
	अगर (fi->nh) अणु
		list_add(&fi->nh_list, &nh->fi_list);
	पूर्ण अन्यथा अणु
		change_nexthops(fi) अणु
			काष्ठा hlist_head *head;
			अचिन्हित पूर्णांक hash;

			अगर (!nexthop_nh->fib_nh_dev)
				जारी;
			hash = fib_devindex_hashfn(nexthop_nh->fib_nh_dev->अगरindex);
			head = &fib_info_devhash[hash];
			hlist_add_head(&nexthop_nh->nh_hash, head);
		पूर्ण endक्रम_nexthops(fi)
	पूर्ण
	spin_unlock_bh(&fib_info_lock);
	वापस fi;

err_inval:
	err = -EINVAL;

failure:
	अगर (fi) अणु
		fi->fib_dead = 1;
		मुक्त_fib_info(fi);
	पूर्ण

	वापस ERR_PTR(err);
पूर्ण

पूर्णांक fib_nexthop_info(काष्ठा sk_buff *skb, स्थिर काष्ठा fib_nh_common *nhc,
		     u8 rt_family, अचिन्हित अक्षर *flags, bool skip_oअगर)
अणु
	अगर (nhc->nhc_flags & RTNH_F_DEAD)
		*flags |= RTNH_F_DEAD;

	अगर (nhc->nhc_flags & RTNH_F_LINKDOWN) अणु
		*flags |= RTNH_F_LINKDOWN;

		rcu_पढ़ो_lock();
		चयन (nhc->nhc_family) अणु
		हाल AF_INET:
			अगर (ip_ignore_linkकरोwn(nhc->nhc_dev))
				*flags |= RTNH_F_DEAD;
			अवरोध;
		हाल AF_INET6:
			अगर (ip6_ignore_linkकरोwn(nhc->nhc_dev))
				*flags |= RTNH_F_DEAD;
			अवरोध;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	चयन (nhc->nhc_gw_family) अणु
	हाल AF_INET:
		अगर (nla_put_in_addr(skb, RTA_GATEWAY, nhc->nhc_gw.ipv4))
			जाओ nla_put_failure;
		अवरोध;
	हाल AF_INET6:
		/* अगर gateway family करोes not match nexthop family
		 * gateway is encoded as RTA_VIA
		 */
		अगर (rt_family != nhc->nhc_gw_family) अणु
			पूर्णांक alen = माप(काष्ठा in6_addr);
			काष्ठा nlattr *nla;
			काष्ठा rtvia *via;

			nla = nla_reserve(skb, RTA_VIA, alen + 2);
			अगर (!nla)
				जाओ nla_put_failure;

			via = nla_data(nla);
			via->rtvia_family = AF_INET6;
			स_नकल(via->rtvia_addr, &nhc->nhc_gw.ipv6, alen);
		पूर्ण अन्यथा अगर (nla_put_in6_addr(skb, RTA_GATEWAY,
					    &nhc->nhc_gw.ipv6) < 0) अणु
			जाओ nla_put_failure;
		पूर्ण
		अवरोध;
	पूर्ण

	*flags |= (nhc->nhc_flags &
		   (RTNH_F_ONLINK | RTNH_F_OFFLOAD | RTNH_F_TRAP));

	अगर (!skip_oअगर && nhc->nhc_dev &&
	    nla_put_u32(skb, RTA_OIF, nhc->nhc_dev->अगरindex))
		जाओ nla_put_failure;

	अगर (nhc->nhc_lwtstate &&
	    lwtunnel_fill_encap(skb, nhc->nhc_lwtstate,
				RTA_ENCAP, RTA_ENCAP_TYPE) < 0)
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण
EXPORT_SYMBOL_GPL(fib_nexthop_info);

#अगर IS_ENABLED(CONFIG_IP_ROUTE_MULTIPATH) || IS_ENABLED(CONFIG_IPV6)
पूर्णांक fib_add_nexthop(काष्ठा sk_buff *skb, स्थिर काष्ठा fib_nh_common *nhc,
		    पूर्णांक nh_weight, u8 rt_family)
अणु
	स्थिर काष्ठा net_device *dev = nhc->nhc_dev;
	काष्ठा rtnexthop *rtnh;
	अचिन्हित अक्षर flags = 0;

	rtnh = nla_reserve_nohdr(skb, माप(*rtnh));
	अगर (!rtnh)
		जाओ nla_put_failure;

	rtnh->rtnh_hops = nh_weight - 1;
	rtnh->rtnh_अगरindex = dev ? dev->अगरindex : 0;

	अगर (fib_nexthop_info(skb, nhc, rt_family, &flags, true) < 0)
		जाओ nla_put_failure;

	rtnh->rtnh_flags = flags;

	/* length of rtnetlink header + attributes */
	rtnh->rtnh_len = nlmsg_get_pos(skb) - (व्योम *)rtnh;

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण
EXPORT_SYMBOL_GPL(fib_add_nexthop);
#पूर्ण_अगर

#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH
अटल पूर्णांक fib_add_multipath(काष्ठा sk_buff *skb, काष्ठा fib_info *fi)
अणु
	काष्ठा nlattr *mp;

	mp = nla_nest_start_noflag(skb, RTA_MULTIPATH);
	अगर (!mp)
		जाओ nla_put_failure;

	अगर (unlikely(fi->nh)) अणु
		अगर (nexthop_mpath_fill_node(skb, fi->nh, AF_INET) < 0)
			जाओ nla_put_failure;
		जाओ mp_end;
	पूर्ण

	क्रम_nexthops(fi) अणु
		अगर (fib_add_nexthop(skb, &nh->nh_common, nh->fib_nh_weight,
				    AF_INET) < 0)
			जाओ nla_put_failure;
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
		अगर (nh->nh_tclassid &&
		    nla_put_u32(skb, RTA_FLOW, nh->nh_tclassid))
			जाओ nla_put_failure;
#पूर्ण_अगर
	पूर्ण endक्रम_nexthops(fi);

mp_end:
	nla_nest_end(skb, mp);

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण
#अन्यथा
अटल पूर्णांक fib_add_multipath(काष्ठा sk_buff *skb, काष्ठा fib_info *fi)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक fib_dump_info(काष्ठा sk_buff *skb, u32 portid, u32 seq, पूर्णांक event,
		  स्थिर काष्ठा fib_rt_info *fri, अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक nhs = fib_info_num_path(fri->fi);
	काष्ठा fib_info *fi = fri->fi;
	u32 tb_id = fri->tb_id;
	काष्ठा nlmsghdr *nlh;
	काष्ठा rपंचांगsg *rपंचांग;

	nlh = nlmsg_put(skb, portid, seq, event, माप(*rपंचांग), flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	rपंचांग = nlmsg_data(nlh);
	rपंचांग->rपंचांग_family = AF_INET;
	rपंचांग->rपंचांग_dst_len = fri->dst_len;
	rपंचांग->rपंचांग_src_len = 0;
	rपंचांग->rपंचांग_tos = fri->tos;
	अगर (tb_id < 256)
		rपंचांग->rपंचांग_table = tb_id;
	अन्यथा
		rपंचांग->rपंचांग_table = RT_TABLE_COMPAT;
	अगर (nla_put_u32(skb, RTA_TABLE, tb_id))
		जाओ nla_put_failure;
	rपंचांग->rपंचांग_type = fri->type;
	rपंचांग->rपंचांग_flags = fi->fib_flags;
	rपंचांग->rपंचांग_scope = fi->fib_scope;
	rपंचांग->rपंचांग_protocol = fi->fib_protocol;

	अगर (rपंचांग->rपंचांग_dst_len &&
	    nla_put_in_addr(skb, RTA_DST, fri->dst))
		जाओ nla_put_failure;
	अगर (fi->fib_priority &&
	    nla_put_u32(skb, RTA_PRIORITY, fi->fib_priority))
		जाओ nla_put_failure;
	अगर (rtnetlink_put_metrics(skb, fi->fib_metrics->metrics) < 0)
		जाओ nla_put_failure;

	अगर (fi->fib_prefsrc &&
	    nla_put_in_addr(skb, RTA_PREFSRC, fi->fib_prefsrc))
		जाओ nla_put_failure;

	अगर (fi->nh) अणु
		अगर (nla_put_u32(skb, RTA_NH_ID, fi->nh->id))
			जाओ nla_put_failure;
		अगर (nexthop_is_blackhole(fi->nh))
			rपंचांग->rपंचांग_type = RTN_BLACKHOLE;
		अगर (!fi->fib_net->ipv4.sysctl_nexthop_compat_mode)
			जाओ offload;
	पूर्ण

	अगर (nhs == 1) अणु
		स्थिर काष्ठा fib_nh_common *nhc = fib_info_nhc(fi, 0);
		अचिन्हित अक्षर flags = 0;

		अगर (fib_nexthop_info(skb, nhc, AF_INET, &flags, false) < 0)
			जाओ nla_put_failure;

		rपंचांग->rपंचांग_flags = flags;
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
		अगर (nhc->nhc_family == AF_INET) अणु
			काष्ठा fib_nh *nh;

			nh = container_of(nhc, काष्ठा fib_nh, nh_common);
			अगर (nh->nh_tclassid &&
			    nla_put_u32(skb, RTA_FLOW, nh->nh_tclassid))
				जाओ nla_put_failure;
		पूर्ण
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		अगर (fib_add_multipath(skb, fi) < 0)
			जाओ nla_put_failure;
	पूर्ण

offload:
	अगर (fri->offload)
		rपंचांग->rपंचांग_flags |= RTM_F_OFFLOAD;
	अगर (fri->trap)
		rपंचांग->rपंचांग_flags |= RTM_F_TRAP;
	अगर (fri->offload_failed)
		rपंचांग->rपंचांग_flags |= RTM_F_OFFLOAD_FAILED;

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

/*
 * Update FIB अगर:
 * - local address disappeared -> we must delete all the entries
 *   referring to it.
 * - device went करोwn -> we must shutकरोwn all nexthops going via it.
 */
पूर्णांक fib_sync_करोwn_addr(काष्ठा net_device *dev, __be32 local)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक hash = fib_laddr_hashfn(local);
	काष्ठा hlist_head *head = &fib_info_laddrhash[hash];
	पूर्णांक tb_id = l3mdev_fib_table(dev) ? : RT_TABLE_MAIN;
	काष्ठा net *net = dev_net(dev);
	काष्ठा fib_info *fi;

	अगर (!fib_info_laddrhash || local == 0)
		वापस 0;

	hlist_क्रम_each_entry(fi, head, fib_lhash) अणु
		अगर (!net_eq(fi->fib_net, net) ||
		    fi->fib_tb_id != tb_id)
			जारी;
		अगर (fi->fib_prefsrc == local) अणु
			fi->fib_flags |= RTNH_F_DEAD;
			ret++;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक call_fib_nh_notअगरiers(काष्ठा fib_nh *nh,
				 क्रमागत fib_event_type event_type)
अणु
	bool ignore_link_करोwn = ip_ignore_linkकरोwn(nh->fib_nh_dev);
	काष्ठा fib_nh_notअगरier_info info = अणु
		.fib_nh = nh,
	पूर्ण;

	चयन (event_type) अणु
	हाल FIB_EVENT_NH_ADD:
		अगर (nh->fib_nh_flags & RTNH_F_DEAD)
			अवरोध;
		अगर (ignore_link_करोwn && nh->fib_nh_flags & RTNH_F_LINKDOWN)
			अवरोध;
		वापस call_fib4_notअगरiers(dev_net(nh->fib_nh_dev), event_type,
					   &info.info);
	हाल FIB_EVENT_NH_DEL:
		अगर ((ignore_link_करोwn && nh->fib_nh_flags & RTNH_F_LINKDOWN) ||
		    (nh->fib_nh_flags & RTNH_F_DEAD))
			वापस call_fib4_notअगरiers(dev_net(nh->fib_nh_dev),
						   event_type, &info.info);
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

/* Update the PMTU of exceptions when:
 * - the new MTU of the first hop becomes smaller than the PMTU
 * - the old MTU was the same as the PMTU, and it limited discovery of
 *   larger MTUs on the path. With that limit उठाओd, we can now
 *   discover larger MTUs
 * A special हाल is locked exceptions, क्रम which the PMTU is smaller
 * than the minimal accepted PMTU:
 * - अगर the new MTU is greater than the PMTU, करोn't make any change
 * - otherwise, unlock and set PMTU
 */
व्योम fib_nhc_update_mtu(काष्ठा fib_nh_common *nhc, u32 new, u32 orig)
अणु
	काष्ठा fnhe_hash_bucket *bucket;
	पूर्णांक i;

	bucket = rcu_dereference_रक्षित(nhc->nhc_exceptions, 1);
	अगर (!bucket)
		वापस;

	क्रम (i = 0; i < FNHE_HASH_SIZE; i++) अणु
		काष्ठा fib_nh_exception *fnhe;

		क्रम (fnhe = rcu_dereference_रक्षित(bucket[i].chain, 1);
		     fnhe;
		     fnhe = rcu_dereference_रक्षित(fnhe->fnhe_next, 1)) अणु
			अगर (fnhe->fnhe_mtu_locked) अणु
				अगर (new <= fnhe->fnhe_pmtu) अणु
					fnhe->fnhe_pmtu = new;
					fnhe->fnhe_mtu_locked = false;
				पूर्ण
			पूर्ण अन्यथा अगर (new < fnhe->fnhe_pmtu ||
				   orig == fnhe->fnhe_pmtu) अणु
				fnhe->fnhe_pmtu = new;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम fib_sync_mtu(काष्ठा net_device *dev, u32 orig_mtu)
अणु
	अचिन्हित पूर्णांक hash = fib_devindex_hashfn(dev->अगरindex);
	काष्ठा hlist_head *head = &fib_info_devhash[hash];
	काष्ठा fib_nh *nh;

	hlist_क्रम_each_entry(nh, head, nh_hash) अणु
		अगर (nh->fib_nh_dev == dev)
			fib_nhc_update_mtu(&nh->nh_common, dev->mtu, orig_mtu);
	पूर्ण
पूर्ण

/* Event              क्रमce Flags           Description
 * NETDEV_CHANGE      0     LINKDOWN        Carrier OFF, not क्रम scope host
 * NETDEV_DOWN        0     LINKDOWN|DEAD   Link करोwn, not क्रम scope host
 * NETDEV_DOWN        1     LINKDOWN|DEAD   Last address हटाओd
 * NETDEV_UNREGISTER  1     LINKDOWN|DEAD   Device हटाओd
 *
 * only used when fib_nh is built पूर्णांकo fib_info
 */
पूर्णांक fib_sync_करोwn_dev(काष्ठा net_device *dev, अचिन्हित दीर्घ event, bool क्रमce)
अणु
	पूर्णांक ret = 0;
	पूर्णांक scope = RT_SCOPE_NOWHERE;
	काष्ठा fib_info *prev_fi = शून्य;
	अचिन्हित पूर्णांक hash = fib_devindex_hashfn(dev->अगरindex);
	काष्ठा hlist_head *head = &fib_info_devhash[hash];
	काष्ठा fib_nh *nh;

	अगर (क्रमce)
		scope = -1;

	hlist_क्रम_each_entry(nh, head, nh_hash) अणु
		काष्ठा fib_info *fi = nh->nh_parent;
		पूर्णांक dead;

		BUG_ON(!fi->fib_nhs);
		अगर (nh->fib_nh_dev != dev || fi == prev_fi)
			जारी;
		prev_fi = fi;
		dead = 0;
		change_nexthops(fi) अणु
			अगर (nexthop_nh->fib_nh_flags & RTNH_F_DEAD)
				dead++;
			अन्यथा अगर (nexthop_nh->fib_nh_dev == dev &&
				 nexthop_nh->fib_nh_scope != scope) अणु
				चयन (event) अणु
				हाल NETDEV_DOWN:
				हाल NETDEV_UNREGISTER:
					nexthop_nh->fib_nh_flags |= RTNH_F_DEAD;
					fallthrough;
				हाल NETDEV_CHANGE:
					nexthop_nh->fib_nh_flags |= RTNH_F_LINKDOWN;
					अवरोध;
				पूर्ण
				call_fib_nh_notअगरiers(nexthop_nh,
						      FIB_EVENT_NH_DEL);
				dead++;
			पूर्ण
#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH
			अगर (event == NETDEV_UNREGISTER &&
			    nexthop_nh->fib_nh_dev == dev) अणु
				dead = fi->fib_nhs;
				अवरोध;
			पूर्ण
#पूर्ण_अगर
		पूर्ण endक्रम_nexthops(fi)
		अगर (dead == fi->fib_nhs) अणु
			चयन (event) अणु
			हाल NETDEV_DOWN:
			हाल NETDEV_UNREGISTER:
				fi->fib_flags |= RTNH_F_DEAD;
				fallthrough;
			हाल NETDEV_CHANGE:
				fi->fib_flags |= RTNH_F_LINKDOWN;
				अवरोध;
			पूर्ण
			ret++;
		पूर्ण

		fib_rebalance(fi);
	पूर्ण

	वापस ret;
पूर्ण

/* Must be invoked inside of an RCU रक्षित region.  */
अटल व्योम fib_select_शेष(स्थिर काष्ठा flowi4 *flp, काष्ठा fib_result *res)
अणु
	काष्ठा fib_info *fi = शून्य, *last_resort = शून्य;
	काष्ठा hlist_head *fa_head = res->fa_head;
	काष्ठा fib_table *tb = res->table;
	u8 slen = 32 - res->prefixlen;
	पूर्णांक order = -1, last_idx = -1;
	काष्ठा fib_alias *fa, *fa1 = शून्य;
	u32 last_prio = res->fi->fib_priority;
	u8 last_tos = 0;

	hlist_क्रम_each_entry_rcu(fa, fa_head, fa_list) अणु
		काष्ठा fib_info *next_fi = fa->fa_info;
		काष्ठा fib_nh_common *nhc;

		अगर (fa->fa_slen != slen)
			जारी;
		अगर (fa->fa_tos && fa->fa_tos != flp->flowi4_tos)
			जारी;
		अगर (fa->tb_id != tb->tb_id)
			जारी;
		अगर (next_fi->fib_priority > last_prio &&
		    fa->fa_tos == last_tos) अणु
			अगर (last_tos)
				जारी;
			अवरोध;
		पूर्ण
		अगर (next_fi->fib_flags & RTNH_F_DEAD)
			जारी;
		last_tos = fa->fa_tos;
		last_prio = next_fi->fib_priority;

		अगर (next_fi->fib_scope != res->scope ||
		    fa->fa_type != RTN_UNICAST)
			जारी;

		nhc = fib_info_nhc(next_fi, 0);
		अगर (!nhc->nhc_gw_family || nhc->nhc_scope != RT_SCOPE_LINK)
			जारी;

		fib_alias_accessed(fa);

		अगर (!fi) अणु
			अगर (next_fi != res->fi)
				अवरोध;
			fa1 = fa;
		पूर्ण अन्यथा अगर (!fib_detect_death(fi, order, &last_resort,
					     &last_idx, fa1->fa_शेष)) अणु
			fib_result_assign(res, fi);
			fa1->fa_शेष = order;
			जाओ out;
		पूर्ण
		fi = next_fi;
		order++;
	पूर्ण

	अगर (order <= 0 || !fi) अणु
		अगर (fa1)
			fa1->fa_शेष = -1;
		जाओ out;
	पूर्ण

	अगर (!fib_detect_death(fi, order, &last_resort, &last_idx,
			      fa1->fa_शेष)) अणु
		fib_result_assign(res, fi);
		fa1->fa_शेष = order;
		जाओ out;
	पूर्ण

	अगर (last_idx >= 0)
		fib_result_assign(res, last_resort);
	fa1->fa_शेष = last_idx;
out:
	वापस;
पूर्ण

/*
 * Dead device goes up. We wake up dead nexthops.
 * It takes sense only on multipath routes.
 *
 * only used when fib_nh is built पूर्णांकo fib_info
 */
पूर्णांक fib_sync_up(काष्ठा net_device *dev, अचिन्हित अक्षर nh_flags)
अणु
	काष्ठा fib_info *prev_fi;
	अचिन्हित पूर्णांक hash;
	काष्ठा hlist_head *head;
	काष्ठा fib_nh *nh;
	पूर्णांक ret;

	अगर (!(dev->flags & IFF_UP))
		वापस 0;

	अगर (nh_flags & RTNH_F_DEAD) अणु
		अचिन्हित पूर्णांक flags = dev_get_flags(dev);

		अगर (flags & (IFF_RUNNING | IFF_LOWER_UP))
			nh_flags |= RTNH_F_LINKDOWN;
	पूर्ण

	prev_fi = शून्य;
	hash = fib_devindex_hashfn(dev->अगरindex);
	head = &fib_info_devhash[hash];
	ret = 0;

	hlist_क्रम_each_entry(nh, head, nh_hash) अणु
		काष्ठा fib_info *fi = nh->nh_parent;
		पूर्णांक alive;

		BUG_ON(!fi->fib_nhs);
		अगर (nh->fib_nh_dev != dev || fi == prev_fi)
			जारी;

		prev_fi = fi;
		alive = 0;
		change_nexthops(fi) अणु
			अगर (!(nexthop_nh->fib_nh_flags & nh_flags)) अणु
				alive++;
				जारी;
			पूर्ण
			अगर (!nexthop_nh->fib_nh_dev ||
			    !(nexthop_nh->fib_nh_dev->flags & IFF_UP))
				जारी;
			अगर (nexthop_nh->fib_nh_dev != dev ||
			    !__in_dev_get_rtnl(dev))
				जारी;
			alive++;
			nexthop_nh->fib_nh_flags &= ~nh_flags;
			call_fib_nh_notअगरiers(nexthop_nh, FIB_EVENT_NH_ADD);
		पूर्ण endक्रम_nexthops(fi)

		अगर (alive > 0) अणु
			fi->fib_flags &= ~nh_flags;
			ret++;
		पूर्ण

		fib_rebalance(fi);
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH
अटल bool fib_good_nh(स्थिर काष्ठा fib_nh *nh)
अणु
	पूर्णांक state = NUD_REACHABLE;

	अगर (nh->fib_nh_scope == RT_SCOPE_LINK) अणु
		काष्ठा neighbour *n;

		rcu_पढ़ो_lock_bh();

		अगर (likely(nh->fib_nh_gw_family == AF_INET))
			n = __ipv4_neigh_lookup_noref(nh->fib_nh_dev,
						   (__क्रमce u32)nh->fib_nh_gw4);
		अन्यथा अगर (nh->fib_nh_gw_family == AF_INET6)
			n = __ipv6_neigh_lookup_noref_stub(nh->fib_nh_dev,
							   &nh->fib_nh_gw6);
		अन्यथा
			n = शून्य;
		अगर (n)
			state = n->nud_state;

		rcu_पढ़ो_unlock_bh();
	पूर्ण

	वापस !!(state & NUD_VALID);
पूर्ण

व्योम fib_select_multipath(काष्ठा fib_result *res, पूर्णांक hash)
अणु
	काष्ठा fib_info *fi = res->fi;
	काष्ठा net *net = fi->fib_net;
	bool first = false;

	अगर (unlikely(res->fi->nh)) अणु
		nexthop_path_fib_result(res, hash);
		वापस;
	पूर्ण

	change_nexthops(fi) अणु
		अगर (net->ipv4.sysctl_fib_multipath_use_neigh) अणु
			अगर (!fib_good_nh(nexthop_nh))
				जारी;
			अगर (!first) अणु
				res->nh_sel = nhsel;
				res->nhc = &nexthop_nh->nh_common;
				first = true;
			पूर्ण
		पूर्ण

		अगर (hash > atomic_पढ़ो(&nexthop_nh->fib_nh_upper_bound))
			जारी;

		res->nh_sel = nhsel;
		res->nhc = &nexthop_nh->nh_common;
		वापस;
	पूर्ण endक्रम_nexthops(fi);
पूर्ण
#पूर्ण_अगर

व्योम fib_select_path(काष्ठा net *net, काष्ठा fib_result *res,
		     काष्ठा flowi4 *fl4, स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (fl4->flowi4_oअगर && !(fl4->flowi4_flags & FLOWI_FLAG_SKIP_NH_OIF))
		जाओ check_saddr;

#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH
	अगर (fib_info_num_path(res->fi) > 1) अणु
		पूर्णांक h = fib_multipath_hash(net, fl4, skb, शून्य);

		fib_select_multipath(res, h);
	पूर्ण
	अन्यथा
#पूर्ण_अगर
	अगर (!res->prefixlen &&
	    res->table->tb_num_शेष > 1 &&
	    res->type == RTN_UNICAST)
		fib_select_शेष(fl4, res);

check_saddr:
	अगर (!fl4->saddr)
		fl4->saddr = fib_result_prefsrc(net, res);
पूर्ण
