<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		IPv4 Forwarding Inक्रमmation Base: FIB frontend.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 */

#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/bitops.h>
#समावेश <linux/capability.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_addr.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/cache.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>

#समावेश <net/ip.h>
#समावेश <net/protocol.h>
#समावेश <net/route.h>
#समावेश <net/tcp.h>
#समावेश <net/sock.h>
#समावेश <net/arp.h>
#समावेश <net/ip_fib.h>
#समावेश <net/nexthop.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/xfrm.h>
#समावेश <net/l3mdev.h>
#समावेश <net/lwtunnel.h>
#समावेश <trace/events/fib.h>

#अगर_अघोषित CONFIG_IP_MULTIPLE_TABLES

अटल पूर्णांक __net_init fib4_rules_init(काष्ठा net *net)
अणु
	काष्ठा fib_table *local_table, *मुख्य_table;

	मुख्य_table  = fib_trie_table(RT_TABLE_MAIN, शून्य);
	अगर (!मुख्य_table)
		वापस -ENOMEM;

	local_table = fib_trie_table(RT_TABLE_LOCAL, मुख्य_table);
	अगर (!local_table)
		जाओ fail;

	hlist_add_head_rcu(&local_table->tb_hlist,
				&net->ipv4.fib_table_hash[TABLE_LOCAL_INDEX]);
	hlist_add_head_rcu(&मुख्य_table->tb_hlist,
				&net->ipv4.fib_table_hash[TABLE_MAIN_INDEX]);
	वापस 0;

fail:
	fib_मुक्त_table(मुख्य_table);
	वापस -ENOMEM;
पूर्ण
#अन्यथा

काष्ठा fib_table *fib_new_table(काष्ठा net *net, u32 id)
अणु
	काष्ठा fib_table *tb, *alias = शून्य;
	अचिन्हित पूर्णांक h;

	अगर (id == 0)
		id = RT_TABLE_MAIN;
	tb = fib_get_table(net, id);
	अगर (tb)
		वापस tb;

	अगर (id == RT_TABLE_LOCAL && !net->ipv4.fib_has_custom_rules)
		alias = fib_new_table(net, RT_TABLE_MAIN);

	tb = fib_trie_table(id, alias);
	अगर (!tb)
		वापस शून्य;

	चयन (id) अणु
	हाल RT_TABLE_MAIN:
		rcu_assign_poपूर्णांकer(net->ipv4.fib_मुख्य, tb);
		अवरोध;
	हाल RT_TABLE_DEFAULT:
		rcu_assign_poपूर्णांकer(net->ipv4.fib_शेष, tb);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	h = id & (FIB_TABLE_HASHSZ - 1);
	hlist_add_head_rcu(&tb->tb_hlist, &net->ipv4.fib_table_hash[h]);
	वापस tb;
पूर्ण
EXPORT_SYMBOL_GPL(fib_new_table);

/* caller must hold either rtnl or rcu पढ़ो lock */
काष्ठा fib_table *fib_get_table(काष्ठा net *net, u32 id)
अणु
	काष्ठा fib_table *tb;
	काष्ठा hlist_head *head;
	अचिन्हित पूर्णांक h;

	अगर (id == 0)
		id = RT_TABLE_MAIN;
	h = id & (FIB_TABLE_HASHSZ - 1);

	head = &net->ipv4.fib_table_hash[h];
	hlist_क्रम_each_entry_rcu(tb, head, tb_hlist,
				 lockdep_rtnl_is_held()) अणु
		अगर (tb->tb_id == id)
			वापस tb;
	पूर्ण
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_IP_MULTIPLE_TABLES */

अटल व्योम fib_replace_table(काष्ठा net *net, काष्ठा fib_table *old,
			      काष्ठा fib_table *new)
अणु
#अगर_घोषित CONFIG_IP_MULTIPLE_TABLES
	चयन (new->tb_id) अणु
	हाल RT_TABLE_MAIN:
		rcu_assign_poपूर्णांकer(net->ipv4.fib_मुख्य, new);
		अवरोध;
	हाल RT_TABLE_DEFAULT:
		rcu_assign_poपूर्णांकer(net->ipv4.fib_शेष, new);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

#पूर्ण_अगर
	/* replace the old table in the hlist */
	hlist_replace_rcu(&old->tb_hlist, &new->tb_hlist);
पूर्ण

पूर्णांक fib_unmerge(काष्ठा net *net)
अणु
	काष्ठा fib_table *old, *new, *मुख्य_table;

	/* attempt to fetch local table अगर it has been allocated */
	old = fib_get_table(net, RT_TABLE_LOCAL);
	अगर (!old)
		वापस 0;

	new = fib_trie_unmerge(old);
	अगर (!new)
		वापस -ENOMEM;

	/* table is alपढ़ोy unmerged */
	अगर (new == old)
		वापस 0;

	/* replace merged table with clean table */
	fib_replace_table(net, old, new);
	fib_मुक्त_table(old);

	/* attempt to fetch मुख्य table अगर it has been allocated */
	मुख्य_table = fib_get_table(net, RT_TABLE_MAIN);
	अगर (!मुख्य_table)
		वापस 0;

	/* flush local entries from मुख्य table */
	fib_table_flush_बाह्यal(मुख्य_table);

	वापस 0;
पूर्ण

व्योम fib_flush(काष्ठा net *net)
अणु
	पूर्णांक flushed = 0;
	अचिन्हित पूर्णांक h;

	क्रम (h = 0; h < FIB_TABLE_HASHSZ; h++) अणु
		काष्ठा hlist_head *head = &net->ipv4.fib_table_hash[h];
		काष्ठा hlist_node *पंचांगp;
		काष्ठा fib_table *tb;

		hlist_क्रम_each_entry_safe(tb, पंचांगp, head, tb_hlist)
			flushed += fib_table_flush(net, tb, false);
	पूर्ण

	अगर (flushed)
		rt_cache_flush(net);
पूर्ण

/*
 * Find address type as अगर only "dev" was present in the प्रणाली. If
 * on_dev is शून्य then all पूर्णांकerfaces are taken पूर्णांकo consideration.
 */
अटल अंतरभूत अचिन्हित पूर्णांक __inet_dev_addr_type(काष्ठा net *net,
						स्थिर काष्ठा net_device *dev,
						__be32 addr, u32 tb_id)
अणु
	काष्ठा flowi4		fl4 = अणु .daddr = addr पूर्ण;
	काष्ठा fib_result	res;
	अचिन्हित पूर्णांक ret = RTN_BROADCAST;
	काष्ठा fib_table *table;

	अगर (ipv4_is_zeronet(addr) || ipv4_is_lbcast(addr))
		वापस RTN_BROADCAST;
	अगर (ipv4_is_multicast(addr))
		वापस RTN_MULTICAST;

	rcu_पढ़ो_lock();

	table = fib_get_table(net, tb_id);
	अगर (table) अणु
		ret = RTN_UNICAST;
		अगर (!fib_table_lookup(table, &fl4, &res, FIB_LOOKUP_NOREF)) अणु
			काष्ठा fib_nh_common *nhc = fib_info_nhc(res.fi, 0);

			अगर (!dev || dev == nhc->nhc_dev)
				ret = res.type;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अचिन्हित पूर्णांक inet_addr_type_table(काष्ठा net *net, __be32 addr, u32 tb_id)
अणु
	वापस __inet_dev_addr_type(net, शून्य, addr, tb_id);
पूर्ण
EXPORT_SYMBOL(inet_addr_type_table);

अचिन्हित पूर्णांक inet_addr_type(काष्ठा net *net, __be32 addr)
अणु
	वापस __inet_dev_addr_type(net, शून्य, addr, RT_TABLE_LOCAL);
पूर्ण
EXPORT_SYMBOL(inet_addr_type);

अचिन्हित पूर्णांक inet_dev_addr_type(काष्ठा net *net, स्थिर काष्ठा net_device *dev,
				__be32 addr)
अणु
	u32 rt_table = l3mdev_fib_table(dev) ? : RT_TABLE_LOCAL;

	वापस __inet_dev_addr_type(net, dev, addr, rt_table);
पूर्ण
EXPORT_SYMBOL(inet_dev_addr_type);

/* inet_addr_type with dev == शून्य but using the table from a dev
 * अगर one is associated
 */
अचिन्हित पूर्णांक inet_addr_type_dev_table(काष्ठा net *net,
				      स्थिर काष्ठा net_device *dev,
				      __be32 addr)
अणु
	u32 rt_table = l3mdev_fib_table(dev) ? : RT_TABLE_LOCAL;

	वापस __inet_dev_addr_type(net, शून्य, addr, rt_table);
पूर्ण
EXPORT_SYMBOL(inet_addr_type_dev_table);

__be32 fib_compute_spec_dst(काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = skb->dev;
	काष्ठा in_device *in_dev;
	काष्ठा fib_result res;
	काष्ठा rtable *rt;
	काष्ठा net *net;
	पूर्णांक scope;

	rt = skb_rtable(skb);
	अगर ((rt->rt_flags & (RTCF_BROADCAST | RTCF_MULTICAST | RTCF_LOCAL)) ==
	    RTCF_LOCAL)
		वापस ip_hdr(skb)->daddr;

	in_dev = __in_dev_get_rcu(dev);

	net = dev_net(dev);

	scope = RT_SCOPE_UNIVERSE;
	अगर (!ipv4_is_zeronet(ip_hdr(skb)->saddr)) अणु
		bool vmark = in_dev && IN_DEV_SRC_VMARK(in_dev);
		काष्ठा flowi4 fl4 = अणु
			.flowi4_iअगर = LOOPBACK_IFINDEX,
			.flowi4_oअगर = l3mdev_master_अगरindex_rcu(dev),
			.daddr = ip_hdr(skb)->saddr,
			.flowi4_tos = ip_hdr(skb)->tos & IPTOS_RT_MASK,
			.flowi4_scope = scope,
			.flowi4_mark = vmark ? skb->mark : 0,
		पूर्ण;
		अगर (!fib_lookup(net, &fl4, &res, 0))
			वापस fib_result_prefsrc(net, &res);
	पूर्ण अन्यथा अणु
		scope = RT_SCOPE_LINK;
	पूर्ण

	वापस inet_select_addr(dev, ip_hdr(skb)->saddr, scope);
पूर्ण

bool fib_info_nh_uses_dev(काष्ठा fib_info *fi, स्थिर काष्ठा net_device *dev)
अणु
	bool dev_match = false;
#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH
	अगर (unlikely(fi->nh)) अणु
		dev_match = nexthop_uses_dev(fi->nh, dev);
	पूर्ण अन्यथा अणु
		पूर्णांक ret;

		क्रम (ret = 0; ret < fib_info_num_path(fi); ret++) अणु
			स्थिर काष्ठा fib_nh_common *nhc = fib_info_nhc(fi, ret);

			अगर (nhc_l3mdev_matches_dev(nhc, dev)) अणु
				dev_match = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
#अन्यथा
	अगर (fib_info_nhc(fi, 0)->nhc_dev == dev)
		dev_match = true;
#पूर्ण_अगर

	वापस dev_match;
पूर्ण
EXPORT_SYMBOL_GPL(fib_info_nh_uses_dev);

/* Given (packet source, input पूर्णांकerface) and optional (dst, oअगर, tos):
 * - (मुख्य) check, that source is valid i.e. not broadcast or our local
 *   address.
 * - figure out what "logical" पूर्णांकerface this packet arrived
 *   and calculate "specific destination" address.
 * - check, that packet arrived from expected physical पूर्णांकerface.
 * called with rcu_पढ़ो_lock()
 */
अटल पूर्णांक __fib_validate_source(काष्ठा sk_buff *skb, __be32 src, __be32 dst,
				 u8 tos, पूर्णांक oअगर, काष्ठा net_device *dev,
				 पूर्णांक rpf, काष्ठा in_device *idev, u32 *itag)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा flow_keys flkeys;
	पूर्णांक ret, no_addr;
	काष्ठा fib_result res;
	काष्ठा flowi4 fl4;
	bool dev_match;

	fl4.flowi4_oअगर = 0;
	fl4.flowi4_iअगर = l3mdev_master_अगरindex_rcu(dev);
	अगर (!fl4.flowi4_iअगर)
		fl4.flowi4_iअगर = oअगर ? : LOOPBACK_IFINDEX;
	fl4.daddr = src;
	fl4.saddr = dst;
	fl4.flowi4_tos = tos;
	fl4.flowi4_scope = RT_SCOPE_UNIVERSE;
	fl4.flowi4_tun_key.tun_id = 0;
	fl4.flowi4_flags = 0;
	fl4.flowi4_uid = sock_net_uid(net, शून्य);
	fl4.flowi4_multipath_hash = 0;

	no_addr = idev->अगरa_list == शून्य;

	fl4.flowi4_mark = IN_DEV_SRC_VMARK(idev) ? skb->mark : 0;
	अगर (!fib4_rules_early_flow_dissect(net, skb, &fl4, &flkeys)) अणु
		fl4.flowi4_proto = 0;
		fl4.fl4_sport = 0;
		fl4.fl4_dport = 0;
	पूर्ण

	अगर (fib_lookup(net, &fl4, &res, 0))
		जाओ last_resort;
	अगर (res.type != RTN_UNICAST &&
	    (res.type != RTN_LOCAL || !IN_DEV_ACCEPT_LOCAL(idev)))
		जाओ e_inval;
	fib_combine_itag(itag, &res);

	dev_match = fib_info_nh_uses_dev(res.fi, dev);
	/* This is not common, loopback packets retain skb_dst so normally they
	 * would not even hit this slow path.
	 */
	dev_match = dev_match || (res.type == RTN_LOCAL &&
				  dev == net->loopback_dev);
	अगर (dev_match) अणु
		ret = FIB_RES_NHC(res)->nhc_scope >= RT_SCOPE_HOST;
		वापस ret;
	पूर्ण
	अगर (no_addr)
		जाओ last_resort;
	अगर (rpf == 1)
		जाओ e_rpf;
	fl4.flowi4_oअगर = dev->अगरindex;

	ret = 0;
	अगर (fib_lookup(net, &fl4, &res, FIB_LOOKUP_IGNORE_LINKSTATE) == 0) अणु
		अगर (res.type == RTN_UNICAST)
			ret = FIB_RES_NHC(res)->nhc_scope >= RT_SCOPE_HOST;
	पूर्ण
	वापस ret;

last_resort:
	अगर (rpf)
		जाओ e_rpf;
	*itag = 0;
	वापस 0;

e_inval:
	वापस -EINVAL;
e_rpf:
	वापस -EXDEV;
पूर्ण

/* Ignore rp_filter क्रम packets रक्षित by IPsec. */
पूर्णांक fib_validate_source(काष्ठा sk_buff *skb, __be32 src, __be32 dst,
			u8 tos, पूर्णांक oअगर, काष्ठा net_device *dev,
			काष्ठा in_device *idev, u32 *itag)
अणु
	पूर्णांक r = secpath_exists(skb) ? 0 : IN_DEV_RPFILTER(idev);
	काष्ठा net *net = dev_net(dev);

	अगर (!r && !fib_num_tclassid_users(net) &&
	    (dev->अगरindex != oअगर || !IN_DEV_TX_REसूचीECTS(idev))) अणु
		अगर (IN_DEV_ACCEPT_LOCAL(idev))
			जाओ ok;
		/* with custom local routes in place, checking local addresses
		 * only will be too optimistic, with custom rules, checking
		 * local addresses only can be too strict, e.g. due to vrf
		 */
		अगर (net->ipv4.fib_has_custom_local_routes ||
		    fib4_has_custom_rules(net))
			जाओ full_check;
		अगर (inet_lookup_अगरaddr_rcu(net, src))
			वापस -EINVAL;

ok:
		*itag = 0;
		वापस 0;
	पूर्ण

full_check:
	वापस __fib_validate_source(skb, src, dst, tos, oअगर, dev, r, idev, itag);
पूर्ण

अटल अंतरभूत __be32 sk_extract_addr(काष्ठा sockaddr *addr)
अणु
	वापस ((काष्ठा sockaddr_in *) addr)->sin_addr.s_addr;
पूर्ण

अटल पूर्णांक put_rtax(काष्ठा nlattr *mx, पूर्णांक len, पूर्णांक type, u32 value)
अणु
	काष्ठा nlattr *nla;

	nla = (काष्ठा nlattr *) ((अक्षर *) mx + len);
	nla->nla_type = type;
	nla->nla_len = nla_attr_size(4);
	*(u32 *) nla_data(nla) = value;

	वापस len + nla_total_size(4);
पूर्ण

अटल पूर्णांक rtentry_to_fib_config(काष्ठा net *net, पूर्णांक cmd, काष्ठा rtentry *rt,
				 काष्ठा fib_config *cfg)
अणु
	__be32 addr;
	पूर्णांक plen;

	स_रखो(cfg, 0, माप(*cfg));
	cfg->fc_nlinfo.nl_net = net;

	अगर (rt->rt_dst.sa_family != AF_INET)
		वापस -EAFNOSUPPORT;

	/*
	 * Check mask क्रम validity:
	 * a) it must be contiguous.
	 * b) destination must have all host bits clear.
	 * c) अगर application क्रमgot to set correct family (AF_INET),
	 *    reject request unless it is असलolutely clear i.e.
	 *    both family and mask are zero.
	 */
	plen = 32;
	addr = sk_extract_addr(&rt->rt_dst);
	अगर (!(rt->rt_flags & RTF_HOST)) अणु
		__be32 mask = sk_extract_addr(&rt->rt_genmask);

		अगर (rt->rt_genmask.sa_family != AF_INET) अणु
			अगर (mask || rt->rt_genmask.sa_family)
				वापस -EAFNOSUPPORT;
		पूर्ण

		अगर (bad_mask(mask, addr))
			वापस -EINVAL;

		plen = inet_mask_len(mask);
	पूर्ण

	cfg->fc_dst_len = plen;
	cfg->fc_dst = addr;

	अगर (cmd != SIOCDELRT) अणु
		cfg->fc_nlflags = NLM_F_CREATE;
		cfg->fc_protocol = RTPROT_BOOT;
	पूर्ण

	अगर (rt->rt_metric)
		cfg->fc_priority = rt->rt_metric - 1;

	अगर (rt->rt_flags & RTF_REJECT) अणु
		cfg->fc_scope = RT_SCOPE_HOST;
		cfg->fc_type = RTN_UNREACHABLE;
		वापस 0;
	पूर्ण

	cfg->fc_scope = RT_SCOPE_NOWHERE;
	cfg->fc_type = RTN_UNICAST;

	अगर (rt->rt_dev) अणु
		अक्षर *colon;
		काष्ठा net_device *dev;
		अक्षर devname[IFNAMSIZ];

		अगर (copy_from_user(devname, rt->rt_dev, IFNAMSIZ-1))
			वापस -EFAULT;

		devname[IFNAMSIZ-1] = 0;
		colon = म_अक्षर(devname, ':');
		अगर (colon)
			*colon = 0;
		dev = __dev_get_by_name(net, devname);
		अगर (!dev)
			वापस -ENODEV;
		cfg->fc_oअगर = dev->अगरindex;
		cfg->fc_table = l3mdev_fib_table(dev);
		अगर (colon) अणु
			स्थिर काष्ठा in_अगरaddr *अगरa;
			काष्ठा in_device *in_dev;

			in_dev = __in_dev_get_rtnl(dev);
			अगर (!in_dev)
				वापस -ENODEV;

			*colon = ':';

			rcu_पढ़ो_lock();
			in_dev_क्रम_each_अगरa_rcu(अगरa, in_dev) अणु
				अगर (म_भेद(अगरa->अगरa_label, devname) == 0)
					अवरोध;
			पूर्ण
			rcu_पढ़ो_unlock();

			अगर (!अगरa)
				वापस -ENODEV;
			cfg->fc_prefsrc = अगरa->अगरa_local;
		पूर्ण
	पूर्ण

	addr = sk_extract_addr(&rt->rt_gateway);
	अगर (rt->rt_gateway.sa_family == AF_INET && addr) अणु
		अचिन्हित पूर्णांक addr_type;

		cfg->fc_gw4 = addr;
		cfg->fc_gw_family = AF_INET;
		addr_type = inet_addr_type_table(net, addr, cfg->fc_table);
		अगर (rt->rt_flags & RTF_GATEWAY &&
		    addr_type == RTN_UNICAST)
			cfg->fc_scope = RT_SCOPE_UNIVERSE;
	पूर्ण

	अगर (cmd == SIOCDELRT)
		वापस 0;

	अगर (rt->rt_flags & RTF_GATEWAY && !cfg->fc_gw_family)
		वापस -EINVAL;

	अगर (cfg->fc_scope == RT_SCOPE_NOWHERE)
		cfg->fc_scope = RT_SCOPE_LINK;

	अगर (rt->rt_flags & (RTF_MTU | RTF_WINDOW | RTF_IRTT)) अणु
		काष्ठा nlattr *mx;
		पूर्णांक len = 0;

		mx = kसुस्मृति(3, nla_total_size(4), GFP_KERNEL);
		अगर (!mx)
			वापस -ENOMEM;

		अगर (rt->rt_flags & RTF_MTU)
			len = put_rtax(mx, len, RTAX_ADVMSS, rt->rt_mtu - 40);

		अगर (rt->rt_flags & RTF_WINDOW)
			len = put_rtax(mx, len, RTAX_WINDOW, rt->rt_winकरोw);

		अगर (rt->rt_flags & RTF_IRTT)
			len = put_rtax(mx, len, RTAX_RTT, rt->rt_irtt << 3);

		cfg->fc_mx = mx;
		cfg->fc_mx_len = len;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Handle IP routing ioctl calls.
 * These are used to manipulate the routing tables
 */
पूर्णांक ip_rt_ioctl(काष्ठा net *net, अचिन्हित पूर्णांक cmd, काष्ठा rtentry *rt)
अणु
	काष्ठा fib_config cfg;
	पूर्णांक err;

	चयन (cmd) अणु
	हाल SIOCADDRT:		/* Add a route */
	हाल SIOCDELRT:		/* Delete a route */
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			वापस -EPERM;

		rtnl_lock();
		err = rtentry_to_fib_config(net, cmd, rt, &cfg);
		अगर (err == 0) अणु
			काष्ठा fib_table *tb;

			अगर (cmd == SIOCDELRT) अणु
				tb = fib_get_table(net, cfg.fc_table);
				अगर (tb)
					err = fib_table_delete(net, tb, &cfg,
							       शून्य);
				अन्यथा
					err = -ESRCH;
			पूर्ण अन्यथा अणु
				tb = fib_new_table(net, cfg.fc_table);
				अगर (tb)
					err = fib_table_insert(net, tb,
							       &cfg, शून्य);
				अन्यथा
					err = -ENOBUFS;
			पूर्ण

			/* allocated by rtentry_to_fib_config() */
			kमुक्त(cfg.fc_mx);
		पूर्ण
		rtnl_unlock();
		वापस err;
	पूर्ण
	वापस -EINVAL;
पूर्ण

स्थिर काष्ठा nla_policy rपंचांग_ipv4_policy[RTA_MAX + 1] = अणु
	[RTA_UNSPEC]		= अणु .strict_start_type = RTA_DPORT + 1 पूर्ण,
	[RTA_DST]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_SRC]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_IIF]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_OIF]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_GATEWAY]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_PRIORITY]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_PREFSRC]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_METRICS]		= अणु .type = NLA_NESTED पूर्ण,
	[RTA_MULTIPATH]		= अणु .len = माप(काष्ठा rtnexthop) पूर्ण,
	[RTA_FLOW]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_ENCAP_TYPE]	= अणु .type = NLA_U16 पूर्ण,
	[RTA_ENCAP]		= अणु .type = NLA_NESTED पूर्ण,
	[RTA_UID]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_MARK]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_TABLE]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_IP_PROTO]		= अणु .type = NLA_U8 पूर्ण,
	[RTA_SPORT]		= अणु .type = NLA_U16 पूर्ण,
	[RTA_DPORT]		= अणु .type = NLA_U16 पूर्ण,
	[RTA_NH_ID]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

पूर्णांक fib_gw_from_via(काष्ठा fib_config *cfg, काष्ठा nlattr *nla,
		    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा rtvia *via;
	पूर्णांक alen;

	अगर (nla_len(nla) < दुरत्व(काष्ठा rtvia, rtvia_addr)) अणु
		NL_SET_ERR_MSG(extack, "Invalid attribute length for RTA_VIA");
		वापस -EINVAL;
	पूर्ण

	via = nla_data(nla);
	alen = nla_len(nla) - दुरत्व(काष्ठा rtvia, rtvia_addr);

	चयन (via->rtvia_family) अणु
	हाल AF_INET:
		अगर (alen != माप(__be32)) अणु
			NL_SET_ERR_MSG(extack, "Invalid IPv4 address in RTA_VIA");
			वापस -EINVAL;
		पूर्ण
		cfg->fc_gw_family = AF_INET;
		cfg->fc_gw4 = *((__be32 *)via->rtvia_addr);
		अवरोध;
	हाल AF_INET6:
#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (alen != माप(काष्ठा in6_addr)) अणु
			NL_SET_ERR_MSG(extack, "Invalid IPv6 address in RTA_VIA");
			वापस -EINVAL;
		पूर्ण
		cfg->fc_gw_family = AF_INET6;
		cfg->fc_gw6 = *((काष्ठा in6_addr *)via->rtvia_addr);
#अन्यथा
		NL_SET_ERR_MSG(extack, "IPv6 support not enabled in kernel");
		वापस -EINVAL;
#पूर्ण_अगर
		अवरोध;
	शेष:
		NL_SET_ERR_MSG(extack, "Unsupported address family in RTA_VIA");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rपंचांग_to_fib_config(काष्ठा net *net, काष्ठा sk_buff *skb,
			     काष्ठा nlmsghdr *nlh, काष्ठा fib_config *cfg,
			     काष्ठा netlink_ext_ack *extack)
अणु
	bool has_gw = false, has_via = false;
	काष्ठा nlattr *attr;
	पूर्णांक err, reमुख्यing;
	काष्ठा rपंचांगsg *rपंचांग;

	err = nlmsg_validate_deprecated(nlh, माप(*rपंचांग), RTA_MAX,
					rपंचांग_ipv4_policy, extack);
	अगर (err < 0)
		जाओ errout;

	स_रखो(cfg, 0, माप(*cfg));

	rपंचांग = nlmsg_data(nlh);
	cfg->fc_dst_len = rपंचांग->rपंचांग_dst_len;
	cfg->fc_tos = rपंचांग->rपंचांग_tos;
	cfg->fc_table = rपंचांग->rपंचांग_table;
	cfg->fc_protocol = rपंचांग->rपंचांग_protocol;
	cfg->fc_scope = rपंचांग->rपंचांग_scope;
	cfg->fc_type = rपंचांग->rपंचांग_type;
	cfg->fc_flags = rपंचांग->rपंचांग_flags;
	cfg->fc_nlflags = nlh->nlmsg_flags;

	cfg->fc_nlinfo.portid = NETLINK_CB(skb).portid;
	cfg->fc_nlinfo.nlh = nlh;
	cfg->fc_nlinfo.nl_net = net;

	अगर (cfg->fc_type > RTN_MAX) अणु
		NL_SET_ERR_MSG(extack, "Invalid route type");
		err = -EINVAL;
		जाओ errout;
	पूर्ण

	nlmsg_क्रम_each_attr(attr, nlh, माप(काष्ठा rपंचांगsg), reमुख्यing) अणु
		चयन (nla_type(attr)) अणु
		हाल RTA_DST:
			cfg->fc_dst = nla_get_be32(attr);
			अवरोध;
		हाल RTA_OIF:
			cfg->fc_oअगर = nla_get_u32(attr);
			अवरोध;
		हाल RTA_GATEWAY:
			has_gw = true;
			cfg->fc_gw4 = nla_get_be32(attr);
			अगर (cfg->fc_gw4)
				cfg->fc_gw_family = AF_INET;
			अवरोध;
		हाल RTA_VIA:
			has_via = true;
			err = fib_gw_from_via(cfg, attr, extack);
			अगर (err)
				जाओ errout;
			अवरोध;
		हाल RTA_PRIORITY:
			cfg->fc_priority = nla_get_u32(attr);
			अवरोध;
		हाल RTA_PREFSRC:
			cfg->fc_prefsrc = nla_get_be32(attr);
			अवरोध;
		हाल RTA_METRICS:
			cfg->fc_mx = nla_data(attr);
			cfg->fc_mx_len = nla_len(attr);
			अवरोध;
		हाल RTA_MULTIPATH:
			err = lwtunnel_valid_encap_type_attr(nla_data(attr),
							     nla_len(attr),
							     extack);
			अगर (err < 0)
				जाओ errout;
			cfg->fc_mp = nla_data(attr);
			cfg->fc_mp_len = nla_len(attr);
			अवरोध;
		हाल RTA_FLOW:
			cfg->fc_flow = nla_get_u32(attr);
			अवरोध;
		हाल RTA_TABLE:
			cfg->fc_table = nla_get_u32(attr);
			अवरोध;
		हाल RTA_ENCAP:
			cfg->fc_encap = attr;
			अवरोध;
		हाल RTA_ENCAP_TYPE:
			cfg->fc_encap_type = nla_get_u16(attr);
			err = lwtunnel_valid_encap_type(cfg->fc_encap_type,
							extack);
			अगर (err < 0)
				जाओ errout;
			अवरोध;
		हाल RTA_NH_ID:
			cfg->fc_nh_id = nla_get_u32(attr);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (cfg->fc_nh_id) अणु
		अगर (cfg->fc_oअगर || cfg->fc_gw_family ||
		    cfg->fc_encap || cfg->fc_mp) अणु
			NL_SET_ERR_MSG(extack,
				       "Nexthop specification and nexthop id are mutually exclusive");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (has_gw && has_via) अणु
		NL_SET_ERR_MSG(extack,
			       "Nexthop configuration can not contain both GATEWAY and VIA");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
errout:
	वापस err;
पूर्ण

अटल पूर्णांक inet_rपंचांग_delroute(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा fib_config cfg;
	काष्ठा fib_table *tb;
	पूर्णांक err;

	err = rपंचांग_to_fib_config(net, skb, nlh, &cfg, extack);
	अगर (err < 0)
		जाओ errout;

	अगर (cfg.fc_nh_id && !nexthop_find_by_id(net, cfg.fc_nh_id)) अणु
		NL_SET_ERR_MSG(extack, "Nexthop id does not exist");
		err = -EINVAL;
		जाओ errout;
	पूर्ण

	tb = fib_get_table(net, cfg.fc_table);
	अगर (!tb) अणु
		NL_SET_ERR_MSG(extack, "FIB table does not exist");
		err = -ESRCH;
		जाओ errout;
	पूर्ण

	err = fib_table_delete(net, tb, &cfg, extack);
errout:
	वापस err;
पूर्ण

अटल पूर्णांक inet_rपंचांग_newroute(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा fib_config cfg;
	काष्ठा fib_table *tb;
	पूर्णांक err;

	err = rपंचांग_to_fib_config(net, skb, nlh, &cfg, extack);
	अगर (err < 0)
		जाओ errout;

	tb = fib_new_table(net, cfg.fc_table);
	अगर (!tb) अणु
		err = -ENOBUFS;
		जाओ errout;
	पूर्ण

	err = fib_table_insert(net, tb, &cfg, extack);
	अगर (!err && cfg.fc_type == RTN_LOCAL)
		net->ipv4.fib_has_custom_local_routes = true;
errout:
	वापस err;
पूर्ण

पूर्णांक ip_valid_fib_dump_req(काष्ठा net *net, स्थिर काष्ठा nlmsghdr *nlh,
			  काष्ठा fib_dump_filter *filter,
			  काष्ठा netlink_callback *cb)
अणु
	काष्ठा netlink_ext_ack *extack = cb->extack;
	काष्ठा nlattr *tb[RTA_MAX + 1];
	काष्ठा rपंचांगsg *rपंचांग;
	पूर्णांक err, i;

	ASSERT_RTNL();

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*rपंचांग))) अणु
		NL_SET_ERR_MSG(extack, "Invalid header for FIB dump request");
		वापस -EINVAL;
	पूर्ण

	rपंचांग = nlmsg_data(nlh);
	अगर (rपंचांग->rपंचांग_dst_len || rपंचांग->rपंचांग_src_len  || rपंचांग->rपंचांग_tos   ||
	    rपंचांग->rपंचांग_scope) अणु
		NL_SET_ERR_MSG(extack, "Invalid values in header for FIB dump request");
		वापस -EINVAL;
	पूर्ण

	अगर (rपंचांग->rपंचांग_flags & ~(RTM_F_CLONED | RTM_F_PREFIX)) अणु
		NL_SET_ERR_MSG(extack, "Invalid flags for FIB dump request");
		वापस -EINVAL;
	पूर्ण
	अगर (rपंचांग->rपंचांग_flags & RTM_F_CLONED)
		filter->dump_routes = false;
	अन्यथा
		filter->dump_exceptions = false;

	filter->flags    = rपंचांग->rपंचांग_flags;
	filter->protocol = rपंचांग->rपंचांग_protocol;
	filter->rt_type  = rपंचांग->rपंचांग_type;
	filter->table_id = rपंचांग->rपंचांग_table;

	err = nlmsg_parse_deprecated_strict(nlh, माप(*rपंचांग), tb, RTA_MAX,
					    rपंचांग_ipv4_policy, extack);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i <= RTA_MAX; ++i) अणु
		पूर्णांक अगरindex;

		अगर (!tb[i])
			जारी;

		चयन (i) अणु
		हाल RTA_TABLE:
			filter->table_id = nla_get_u32(tb[i]);
			अवरोध;
		हाल RTA_OIF:
			अगरindex = nla_get_u32(tb[i]);
			filter->dev = __dev_get_by_index(net, अगरindex);
			अगर (!filter->dev)
				वापस -ENODEV;
			अवरोध;
		शेष:
			NL_SET_ERR_MSG(extack, "Unsupported attribute in dump request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (filter->flags || filter->protocol || filter->rt_type ||
	    filter->table_id || filter->dev) अणु
		filter->filter_set = 1;
		cb->answer_flags = NLM_F_DUMP_FILTERED;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ip_valid_fib_dump_req);

अटल पूर्णांक inet_dump_fib(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा fib_dump_filter filter = अणु .dump_routes = true,
					  .dump_exceptions = true पूर्ण;
	स्थिर काष्ठा nlmsghdr *nlh = cb->nlh;
	काष्ठा net *net = sock_net(skb->sk);
	अचिन्हित पूर्णांक h, s_h;
	अचिन्हित पूर्णांक e = 0, s_e;
	काष्ठा fib_table *tb;
	काष्ठा hlist_head *head;
	पूर्णांक dumped = 0, err;

	अगर (cb->strict_check) अणु
		err = ip_valid_fib_dump_req(net, nlh, &filter, cb);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अगर (nlmsg_len(nlh) >= माप(काष्ठा rपंचांगsg)) अणु
		काष्ठा rपंचांगsg *rपंचांग = nlmsg_data(nlh);

		filter.flags = rपंचांग->rपंचांग_flags & (RTM_F_PREFIX | RTM_F_CLONED);
	पूर्ण

	/* ipv4 करोes not use prefix flag */
	अगर (filter.flags & RTM_F_PREFIX)
		वापस skb->len;

	अगर (filter.table_id) अणु
		tb = fib_get_table(net, filter.table_id);
		अगर (!tb) अणु
			अगर (rtnl_msg_family(cb->nlh) != PF_INET)
				वापस skb->len;

			NL_SET_ERR_MSG(cb->extack, "ipv4: FIB table does not exist");
			वापस -ENOENT;
		पूर्ण

		rcu_पढ़ो_lock();
		err = fib_table_dump(tb, skb, cb, &filter);
		rcu_पढ़ो_unlock();
		वापस skb->len ? : err;
	पूर्ण

	s_h = cb->args[0];
	s_e = cb->args[1];

	rcu_पढ़ो_lock();

	क्रम (h = s_h; h < FIB_TABLE_HASHSZ; h++, s_e = 0) अणु
		e = 0;
		head = &net->ipv4.fib_table_hash[h];
		hlist_क्रम_each_entry_rcu(tb, head, tb_hlist) अणु
			अगर (e < s_e)
				जाओ next;
			अगर (dumped)
				स_रखो(&cb->args[2], 0, माप(cb->args) -
						 2 * माप(cb->args[0]));
			err = fib_table_dump(tb, skb, cb, &filter);
			अगर (err < 0) अणु
				अगर (likely(skb->len))
					जाओ out;

				जाओ out_err;
			पूर्ण
			dumped = 1;
next:
			e++;
		पूर्ण
	पूर्ण
out:
	err = skb->len;
out_err:
	rcu_पढ़ो_unlock();

	cb->args[1] = e;
	cb->args[0] = h;

	वापस err;
पूर्ण

/* Prepare and feed पूर्णांकra-kernel routing request.
 * Really, it should be netlink message, but :-( netlink
 * can be not configured, so that we feed it directly
 * to fib engine. It is legal, because all events occur
 * only when netlink is alपढ़ोy locked.
 */
अटल व्योम fib_magic(पूर्णांक cmd, पूर्णांक type, __be32 dst, पूर्णांक dst_len,
		      काष्ठा in_अगरaddr *अगरa, u32 rt_priority)
अणु
	काष्ठा net *net = dev_net(अगरa->अगरa_dev->dev);
	u32 tb_id = l3mdev_fib_table(अगरa->अगरa_dev->dev);
	काष्ठा fib_table *tb;
	काष्ठा fib_config cfg = अणु
		.fc_protocol = RTPROT_KERNEL,
		.fc_type = type,
		.fc_dst = dst,
		.fc_dst_len = dst_len,
		.fc_priority = rt_priority,
		.fc_prefsrc = अगरa->अगरa_local,
		.fc_oअगर = अगरa->अगरa_dev->dev->अगरindex,
		.fc_nlflags = NLM_F_CREATE | NLM_F_APPEND,
		.fc_nlinfo = अणु
			.nl_net = net,
		पूर्ण,
	पूर्ण;

	अगर (!tb_id)
		tb_id = (type == RTN_UNICAST) ? RT_TABLE_MAIN : RT_TABLE_LOCAL;

	tb = fib_new_table(net, tb_id);
	अगर (!tb)
		वापस;

	cfg.fc_table = tb->tb_id;

	अगर (type != RTN_LOCAL)
		cfg.fc_scope = RT_SCOPE_LINK;
	अन्यथा
		cfg.fc_scope = RT_SCOPE_HOST;

	अगर (cmd == RTM_NEWROUTE)
		fib_table_insert(net, tb, &cfg, शून्य);
	अन्यथा
		fib_table_delete(net, tb, &cfg, शून्य);
पूर्ण

व्योम fib_add_अगरaddr(काष्ठा in_अगरaddr *अगरa)
अणु
	काष्ठा in_device *in_dev = अगरa->अगरa_dev;
	काष्ठा net_device *dev = in_dev->dev;
	काष्ठा in_अगरaddr *prim = अगरa;
	__be32 mask = अगरa->अगरa_mask;
	__be32 addr = अगरa->अगरa_local;
	__be32 prefix = अगरa->अगरa_address & mask;

	अगर (अगरa->अगरa_flags & IFA_F_SECONDARY) अणु
		prim = inet_अगरa_byprefix(in_dev, prefix, mask);
		अगर (!prim) अणु
			pr_warn("%s: bug: prim == NULL\n", __func__);
			वापस;
		पूर्ण
	पूर्ण

	fib_magic(RTM_NEWROUTE, RTN_LOCAL, addr, 32, prim, 0);

	अगर (!(dev->flags & IFF_UP))
		वापस;

	/* Add broadcast address, अगर it is explicitly asचिन्हित. */
	अगर (अगरa->अगरa_broadcast && अगरa->अगरa_broadcast != htonl(0xFFFFFFFF))
		fib_magic(RTM_NEWROUTE, RTN_BROADCAST, अगरa->अगरa_broadcast, 32,
			  prim, 0);

	अगर (!ipv4_is_zeronet(prefix) && !(अगरa->अगरa_flags & IFA_F_SECONDARY) &&
	    (prefix != addr || अगरa->अगरa_prefixlen < 32)) अणु
		अगर (!(अगरa->अगरa_flags & IFA_F_NOPREFIXROUTE))
			fib_magic(RTM_NEWROUTE,
				  dev->flags & IFF_LOOPBACK ? RTN_LOCAL : RTN_UNICAST,
				  prefix, अगरa->अगरa_prefixlen, prim,
				  अगरa->अगरa_rt_priority);

		/* Add network specअगरic broadcasts, when it takes a sense */
		अगर (अगरa->अगरa_prefixlen < 31) अणु
			fib_magic(RTM_NEWROUTE, RTN_BROADCAST, prefix, 32,
				  prim, 0);
			fib_magic(RTM_NEWROUTE, RTN_BROADCAST, prefix | ~mask,
				  32, prim, 0);
		पूर्ण
	पूर्ण
पूर्ण

व्योम fib_modअगरy_prefix_metric(काष्ठा in_अगरaddr *अगरa, u32 new_metric)
अणु
	__be32 prefix = अगरa->अगरa_address & अगरa->अगरa_mask;
	काष्ठा in_device *in_dev = अगरa->अगरa_dev;
	काष्ठा net_device *dev = in_dev->dev;

	अगर (!(dev->flags & IFF_UP) ||
	    अगरa->अगरa_flags & (IFA_F_SECONDARY | IFA_F_NOPREFIXROUTE) ||
	    ipv4_is_zeronet(prefix) ||
	    (prefix == अगरa->अगरa_local && अगरa->अगरa_prefixlen == 32))
		वापस;

	/* add the new */
	fib_magic(RTM_NEWROUTE,
		  dev->flags & IFF_LOOPBACK ? RTN_LOCAL : RTN_UNICAST,
		  prefix, अगरa->अगरa_prefixlen, अगरa, new_metric);

	/* delete the old */
	fib_magic(RTM_DELROUTE,
		  dev->flags & IFF_LOOPBACK ? RTN_LOCAL : RTN_UNICAST,
		  prefix, अगरa->अगरa_prefixlen, अगरa, अगरa->अगरa_rt_priority);
पूर्ण

/* Delete primary or secondary address.
 * Optionally, on secondary address promotion consider the addresses
 * from subnet iprim as deleted, even अगर they are in device list.
 * In this हाल the secondary अगरa can be in device list.
 */
व्योम fib_del_अगरaddr(काष्ठा in_अगरaddr *अगरa, काष्ठा in_अगरaddr *iprim)
अणु
	काष्ठा in_device *in_dev = अगरa->अगरa_dev;
	काष्ठा net_device *dev = in_dev->dev;
	काष्ठा in_अगरaddr *अगरa1;
	काष्ठा in_अगरaddr *prim = अगरa, *prim1 = शून्य;
	__be32 brd = अगरa->अगरa_address | ~अगरa->अगरa_mask;
	__be32 any = अगरa->अगरa_address & अगरa->अगरa_mask;
#घोषणा LOCAL_OK	1
#घोषणा BRD_OK		2
#घोषणा BRD0_OK		4
#घोषणा BRD1_OK		8
	अचिन्हित पूर्णांक ok = 0;
	पूर्णांक subnet = 0;		/* Primary network */
	पूर्णांक gone = 1;		/* Address is missing */
	पूर्णांक same_prefsrc = 0;	/* Another primary with same IP */

	अगर (अगरa->अगरa_flags & IFA_F_SECONDARY) अणु
		prim = inet_अगरa_byprefix(in_dev, any, अगरa->अगरa_mask);
		अगर (!prim) अणु
			/* अगर the device has been deleted, we करोn't perक्रमm
			 * address promotion
			 */
			अगर (!in_dev->dead)
				pr_warn("%s: bug: prim == NULL\n", __func__);
			वापस;
		पूर्ण
		अगर (iprim && iprim != prim) अणु
			pr_warn("%s: bug: iprim != prim\n", __func__);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (!ipv4_is_zeronet(any) &&
		   (any != अगरa->अगरa_local || अगरa->अगरa_prefixlen < 32)) अणु
		अगर (!(अगरa->अगरa_flags & IFA_F_NOPREFIXROUTE))
			fib_magic(RTM_DELROUTE,
				  dev->flags & IFF_LOOPBACK ? RTN_LOCAL : RTN_UNICAST,
				  any, अगरa->अगरa_prefixlen, prim, 0);
		subnet = 1;
	पूर्ण

	अगर (in_dev->dead)
		जाओ no_promotions;

	/* Deletion is more complicated than add.
	 * We should take care of not to delete too much :-)
	 *
	 * Scan address list to be sure that addresses are really gone.
	 */
	rcu_पढ़ो_lock();
	in_dev_क्रम_each_अगरa_rcu(अगरa1, in_dev) अणु
		अगर (अगरa1 == अगरa) अणु
			/* promotion, keep the IP */
			gone = 0;
			जारी;
		पूर्ण
		/* Ignore IFAs from our subnet */
		अगर (iprim && अगरa1->अगरa_mask == iprim->अगरa_mask &&
		    inet_अगरa_match(अगरa1->अगरa_address, iprim))
			जारी;

		/* Ignore अगरa1 अगर it uses dअगरferent primary IP (prefsrc) */
		अगर (अगरa1->अगरa_flags & IFA_F_SECONDARY) अणु
			/* Another address from our subnet? */
			अगर (अगरa1->अगरa_mask == prim->अगरa_mask &&
			    inet_अगरa_match(अगरa1->अगरa_address, prim))
				prim1 = prim;
			अन्यथा अणु
				/* We reached the secondaries, so
				 * same_prefsrc should be determined.
				 */
				अगर (!same_prefsrc)
					जारी;
				/* Search new prim1 अगर अगरa1 is not
				 * using the current prim1
				 */
				अगर (!prim1 ||
				    अगरa1->अगरa_mask != prim1->अगरa_mask ||
				    !inet_अगरa_match(अगरa1->अगरa_address, prim1))
					prim1 = inet_अगरa_byprefix(in_dev,
							अगरa1->अगरa_address,
							अगरa1->अगरa_mask);
				अगर (!prim1)
					जारी;
				अगर (prim1->अगरa_local != prim->अगरa_local)
					जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (prim->अगरa_local != अगरa1->अगरa_local)
				जारी;
			prim1 = अगरa1;
			अगर (prim != prim1)
				same_prefsrc = 1;
		पूर्ण
		अगर (अगरa->अगरa_local == अगरa1->अगरa_local)
			ok |= LOCAL_OK;
		अगर (अगरa->अगरa_broadcast == अगरa1->अगरa_broadcast)
			ok |= BRD_OK;
		अगर (brd == अगरa1->अगरa_broadcast)
			ok |= BRD1_OK;
		अगर (any == अगरa1->अगरa_broadcast)
			ok |= BRD0_OK;
		/* primary has network specअगरic broadcasts */
		अगर (prim1 == अगरa1 && अगरa1->अगरa_prefixlen < 31) अणु
			__be32 brd1 = अगरa1->अगरa_address | ~अगरa1->अगरa_mask;
			__be32 any1 = अगरa1->अगरa_address & अगरa1->अगरa_mask;

			अगर (!ipv4_is_zeronet(any1)) अणु
				अगर (अगरa->अगरa_broadcast == brd1 ||
				    अगरa->अगरa_broadcast == any1)
					ok |= BRD_OK;
				अगर (brd == brd1 || brd == any1)
					ok |= BRD1_OK;
				अगर (any == brd1 || any == any1)
					ok |= BRD0_OK;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

no_promotions:
	अगर (!(ok & BRD_OK))
		fib_magic(RTM_DELROUTE, RTN_BROADCAST, अगरa->अगरa_broadcast, 32,
			  prim, 0);
	अगर (subnet && अगरa->अगरa_prefixlen < 31) अणु
		अगर (!(ok & BRD1_OK))
			fib_magic(RTM_DELROUTE, RTN_BROADCAST, brd, 32,
				  prim, 0);
		अगर (!(ok & BRD0_OK))
			fib_magic(RTM_DELROUTE, RTN_BROADCAST, any, 32,
				  prim, 0);
	पूर्ण
	अगर (!(ok & LOCAL_OK)) अणु
		अचिन्हित पूर्णांक addr_type;

		fib_magic(RTM_DELROUTE, RTN_LOCAL, अगरa->अगरa_local, 32, prim, 0);

		/* Check, that this local address finally disappeared. */
		addr_type = inet_addr_type_dev_table(dev_net(dev), dev,
						     अगरa->अगरa_local);
		अगर (gone && addr_type != RTN_LOCAL) अणु
			/* And the last, but not the least thing.
			 * We must flush stray FIB entries.
			 *
			 * First of all, we scan fib_info list searching
			 * क्रम stray nexthop entries, then ignite fib_flush.
			 */
			अगर (fib_sync_करोwn_addr(dev, अगरa->अगरa_local))
				fib_flush(dev_net(dev));
		पूर्ण
	पूर्ण
#अघोषित LOCAL_OK
#अघोषित BRD_OK
#अघोषित BRD0_OK
#अघोषित BRD1_OK
पूर्ण

अटल व्योम nl_fib_lookup(काष्ठा net *net, काष्ठा fib_result_nl *frn)
अणु

	काष्ठा fib_result       res;
	काष्ठा flowi4           fl4 = अणु
		.flowi4_mark = frn->fl_mark,
		.daddr = frn->fl_addr,
		.flowi4_tos = frn->fl_tos,
		.flowi4_scope = frn->fl_scope,
	पूर्ण;
	काष्ठा fib_table *tb;

	rcu_पढ़ो_lock();

	tb = fib_get_table(net, frn->tb_id_in);

	frn->err = -ENOENT;
	अगर (tb) अणु
		local_bh_disable();

		frn->tb_id = tb->tb_id;
		frn->err = fib_table_lookup(tb, &fl4, &res, FIB_LOOKUP_NOREF);

		अगर (!frn->err) अणु
			frn->prefixlen = res.prefixlen;
			frn->nh_sel = res.nh_sel;
			frn->type = res.type;
			frn->scope = res.scope;
		पूर्ण
		local_bh_enable();
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम nl_fib_input(काष्ठा sk_buff *skb)
अणु
	काष्ठा net *net;
	काष्ठा fib_result_nl *frn;
	काष्ठा nlmsghdr *nlh;
	u32 portid;

	net = sock_net(skb->sk);
	nlh = nlmsg_hdr(skb);
	अगर (skb->len < nlmsg_total_size(माप(*frn)) ||
	    skb->len < nlh->nlmsg_len ||
	    nlmsg_len(nlh) < माप(*frn))
		वापस;

	skb = netlink_skb_clone(skb, GFP_KERNEL);
	अगर (!skb)
		वापस;
	nlh = nlmsg_hdr(skb);

	frn = (काष्ठा fib_result_nl *) nlmsg_data(nlh);
	nl_fib_lookup(net, frn);

	portid = NETLINK_CB(skb).portid;      /* netlink portid */
	NETLINK_CB(skb).portid = 0;        /* from kernel */
	NETLINK_CB(skb).dst_group = 0;  /* unicast */
	netlink_unicast(net->ipv4.fibnl, skb, portid, MSG_DONTWAIT);
पूर्ण

अटल पूर्णांक __net_init nl_fib_lookup_init(काष्ठा net *net)
अणु
	काष्ठा sock *sk;
	काष्ठा netlink_kernel_cfg cfg = अणु
		.input	= nl_fib_input,
	पूर्ण;

	sk = netlink_kernel_create(net, NETLINK_FIB_LOOKUP, &cfg);
	अगर (!sk)
		वापस -EAFNOSUPPORT;
	net->ipv4.fibnl = sk;
	वापस 0;
पूर्ण

अटल व्योम nl_fib_lookup_निकास(काष्ठा net *net)
अणु
	netlink_kernel_release(net->ipv4.fibnl);
	net->ipv4.fibnl = शून्य;
पूर्ण

अटल व्योम fib_disable_ip(काष्ठा net_device *dev, अचिन्हित दीर्घ event,
			   bool क्रमce)
अणु
	अगर (fib_sync_करोwn_dev(dev, event, क्रमce))
		fib_flush(dev_net(dev));
	अन्यथा
		rt_cache_flush(dev_net(dev));
	arp_अगरकरोwn(dev);
पूर्ण

अटल पूर्णांक fib_inetaddr_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा in_अगरaddr *अगरa = (काष्ठा in_अगरaddr *)ptr;
	काष्ठा net_device *dev = अगरa->अगरa_dev->dev;
	काष्ठा net *net = dev_net(dev);

	चयन (event) अणु
	हाल NETDEV_UP:
		fib_add_अगरaddr(अगरa);
#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH
		fib_sync_up(dev, RTNH_F_DEAD);
#पूर्ण_अगर
		atomic_inc(&net->ipv4.dev_addr_genid);
		rt_cache_flush(dev_net(dev));
		अवरोध;
	हाल NETDEV_DOWN:
		fib_del_अगरaddr(अगरa, शून्य);
		atomic_inc(&net->ipv4.dev_addr_genid);
		अगर (!अगरa->अगरa_dev->अगरa_list) अणु
			/* Last address was deleted from this पूर्णांकerface.
			 * Disable IP.
			 */
			fib_disable_ip(dev, event, true);
		पूर्ण अन्यथा अणु
			rt_cache_flush(dev_net(dev));
		पूर्ण
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक fib_netdev_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा netdev_notअगरier_changeupper_info *upper_info = ptr;
	काष्ठा netdev_notअगरier_info_ext *info_ext = ptr;
	काष्ठा in_device *in_dev;
	काष्ठा net *net = dev_net(dev);
	काष्ठा in_अगरaddr *अगरa;
	अचिन्हित पूर्णांक flags;

	अगर (event == NETDEV_UNREGISTER) अणु
		fib_disable_ip(dev, event, true);
		rt_flush_dev(dev);
		वापस NOTIFY_DONE;
	पूर्ण

	in_dev = __in_dev_get_rtnl(dev);
	अगर (!in_dev)
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_UP:
		in_dev_क्रम_each_अगरa_rtnl(अगरa, in_dev) अणु
			fib_add_अगरaddr(अगरa);
		पूर्ण
#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH
		fib_sync_up(dev, RTNH_F_DEAD);
#पूर्ण_अगर
		atomic_inc(&net->ipv4.dev_addr_genid);
		rt_cache_flush(net);
		अवरोध;
	हाल NETDEV_DOWN:
		fib_disable_ip(dev, event, false);
		अवरोध;
	हाल NETDEV_CHANGE:
		flags = dev_get_flags(dev);
		अगर (flags & (IFF_RUNNING | IFF_LOWER_UP))
			fib_sync_up(dev, RTNH_F_LINKDOWN);
		अन्यथा
			fib_sync_करोwn_dev(dev, event, false);
		rt_cache_flush(net);
		अवरोध;
	हाल NETDEV_CHANGEMTU:
		fib_sync_mtu(dev, info_ext->ext.mtu);
		rt_cache_flush(net);
		अवरोध;
	हाल NETDEV_CHANGEUPPER:
		upper_info = ptr;
		/* flush all routes अगर dev is linked to or unlinked from
		 * an L3 master device (e.g., VRF)
		 */
		अगर (upper_info->upper_dev &&
		    netअगर_is_l3_master(upper_info->upper_dev))
			fib_disable_ip(dev, NETDEV_DOWN, true);
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block fib_inetaddr_notअगरier = अणु
	.notअगरier_call = fib_inetaddr_event,
पूर्ण;

अटल काष्ठा notअगरier_block fib_netdev_notअगरier = अणु
	.notअगरier_call = fib_netdev_event,
पूर्ण;

अटल पूर्णांक __net_init ip_fib_net_init(काष्ठा net *net)
अणु
	पूर्णांक err;
	माप_प्रकार size = माप(काष्ठा hlist_head) * FIB_TABLE_HASHSZ;

	err = fib4_notअगरier_init(net);
	अगर (err)
		वापस err;

	/* Aव्योम false sharing : Use at least a full cache line */
	size = max_t(माप_प्रकार, size, L1_CACHE_BYTES);

	net->ipv4.fib_table_hash = kzalloc(size, GFP_KERNEL);
	अगर (!net->ipv4.fib_table_hash) अणु
		err = -ENOMEM;
		जाओ err_table_hash_alloc;
	पूर्ण

	err = fib4_rules_init(net);
	अगर (err < 0)
		जाओ err_rules_init;
	वापस 0;

err_rules_init:
	kमुक्त(net->ipv4.fib_table_hash);
err_table_hash_alloc:
	fib4_notअगरier_निकास(net);
	वापस err;
पूर्ण

अटल व्योम ip_fib_net_निकास(काष्ठा net *net)
अणु
	पूर्णांक i;

	rtnl_lock();
#अगर_घोषित CONFIG_IP_MULTIPLE_TABLES
	RCU_INIT_POINTER(net->ipv4.fib_मुख्य, शून्य);
	RCU_INIT_POINTER(net->ipv4.fib_शेष, शून्य);
#पूर्ण_अगर
	/* Destroy the tables in reverse order to guarantee that the
	 * local table, ID 255, is destroyed beक्रमe the मुख्य table, ID
	 * 254. This is necessary as the local table may contain
	 * references to data contained in the मुख्य table.
	 */
	क्रम (i = FIB_TABLE_HASHSZ - 1; i >= 0; i--) अणु
		काष्ठा hlist_head *head = &net->ipv4.fib_table_hash[i];
		काष्ठा hlist_node *पंचांगp;
		काष्ठा fib_table *tb;

		hlist_क्रम_each_entry_safe(tb, पंचांगp, head, tb_hlist) अणु
			hlist_del(&tb->tb_hlist);
			fib_table_flush(net, tb, true);
			fib_मुक्त_table(tb);
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_IP_MULTIPLE_TABLES
	fib4_rules_निकास(net);
#पूर्ण_अगर
	rtnl_unlock();
	kमुक्त(net->ipv4.fib_table_hash);
	fib4_notअगरier_निकास(net);
पूर्ण

अटल पूर्णांक __net_init fib_net_init(काष्ठा net *net)
अणु
	पूर्णांक error;

#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	net->ipv4.fib_num_tclassid_users = 0;
#पूर्ण_अगर
	error = ip_fib_net_init(net);
	अगर (error < 0)
		जाओ out;
	error = nl_fib_lookup_init(net);
	अगर (error < 0)
		जाओ out_nlfl;
	error = fib_proc_init(net);
	अगर (error < 0)
		जाओ out_proc;
out:
	वापस error;

out_proc:
	nl_fib_lookup_निकास(net);
out_nlfl:
	ip_fib_net_निकास(net);
	जाओ out;
पूर्ण

अटल व्योम __net_निकास fib_net_निकास(काष्ठा net *net)
अणु
	fib_proc_निकास(net);
	nl_fib_lookup_निकास(net);
	ip_fib_net_निकास(net);
पूर्ण

अटल काष्ठा pernet_operations fib_net_ops = अणु
	.init = fib_net_init,
	.निकास = fib_net_निकास,
पूर्ण;

व्योम __init ip_fib_init(व्योम)
अणु
	fib_trie_init();

	रेजिस्टर_pernet_subsys(&fib_net_ops);

	रेजिस्टर_netdevice_notअगरier(&fib_netdev_notअगरier);
	रेजिस्टर_inetaddr_notअगरier(&fib_inetaddr_notअगरier);

	rtnl_रेजिस्टर(PF_INET, RTM_NEWROUTE, inet_rपंचांग_newroute, शून्य, 0);
	rtnl_रेजिस्टर(PF_INET, RTM_DELROUTE, inet_rपंचांग_delroute, शून्य, 0);
	rtnl_रेजिस्टर(PF_INET, RTM_GETROUTE, शून्य, inet_dump_fib, 0);
पूर्ण
