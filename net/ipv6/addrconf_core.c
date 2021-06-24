<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IPv6 library code, needed by अटल components when full IPv6 support is
 * not configured or अटल.
 */

#समावेश <linux/export.h>
#समावेश <net/ipv6.h>
#समावेश <net/ipv6_stubs.h>
#समावेश <net/addrconf.h>
#समावेश <net/ip.h>

/* अगर ipv6 module रेजिस्टरs this function is used by xfrm to क्रमce all
 * sockets to relookup their nodes - this is fairly expensive, be
 * careful
 */
व्योम (*__fib6_flush_trees)(काष्ठा net *);
EXPORT_SYMBOL(__fib6_flush_trees);

#घोषणा IPV6_ADDR_SCOPE_TYPE(scope)	((scope) << 16)

अटल अंतरभूत अचिन्हित पूर्णांक ipv6_addr_scope2type(अचिन्हित पूर्णांक scope)
अणु
	चयन (scope) अणु
	हाल IPV6_ADDR_SCOPE_NODELOCAL:
		वापस (IPV6_ADDR_SCOPE_TYPE(IPV6_ADDR_SCOPE_NODELOCAL) |
			IPV6_ADDR_LOOPBACK);
	हाल IPV6_ADDR_SCOPE_LINKLOCAL:
		वापस (IPV6_ADDR_SCOPE_TYPE(IPV6_ADDR_SCOPE_LINKLOCAL) |
			IPV6_ADDR_LINKLOCAL);
	हाल IPV6_ADDR_SCOPE_SITELOCAL:
		वापस (IPV6_ADDR_SCOPE_TYPE(IPV6_ADDR_SCOPE_SITELOCAL) |
			IPV6_ADDR_SITELOCAL);
	पूर्ण
	वापस IPV6_ADDR_SCOPE_TYPE(scope);
पूर्ण

पूर्णांक __ipv6_addr_type(स्थिर काष्ठा in6_addr *addr)
अणु
	__be32 st;

	st = addr->s6_addr32[0];

	/* Consider all addresses with the first three bits dअगरferent of
	   000 and 111 as unicasts.
	 */
	अगर ((st & htonl(0xE0000000)) != htonl(0x00000000) &&
	    (st & htonl(0xE0000000)) != htonl(0xE0000000))
		वापस (IPV6_ADDR_UNICAST |
			IPV6_ADDR_SCOPE_TYPE(IPV6_ADDR_SCOPE_GLOBAL));

	अगर ((st & htonl(0xFF000000)) == htonl(0xFF000000)) अणु
		/* multicast */
		/* addr-select 3.1 */
		वापस (IPV6_ADDR_MULTICAST |
			ipv6_addr_scope2type(IPV6_ADDR_MC_SCOPE(addr)));
	पूर्ण

	अगर ((st & htonl(0xFFC00000)) == htonl(0xFE800000))
		वापस (IPV6_ADDR_LINKLOCAL | IPV6_ADDR_UNICAST |
			IPV6_ADDR_SCOPE_TYPE(IPV6_ADDR_SCOPE_LINKLOCAL));		/* addr-select 3.1 */
	अगर ((st & htonl(0xFFC00000)) == htonl(0xFEC00000))
		वापस (IPV6_ADDR_SITELOCAL | IPV6_ADDR_UNICAST |
			IPV6_ADDR_SCOPE_TYPE(IPV6_ADDR_SCOPE_SITELOCAL));		/* addr-select 3.1 */
	अगर ((st & htonl(0xFE000000)) == htonl(0xFC000000))
		वापस (IPV6_ADDR_UNICAST |
			IPV6_ADDR_SCOPE_TYPE(IPV6_ADDR_SCOPE_GLOBAL));			/* RFC 4193 */

	अगर ((addr->s6_addr32[0] | addr->s6_addr32[1]) == 0) अणु
		अगर (addr->s6_addr32[2] == 0) अणु
			अगर (addr->s6_addr32[3] == 0)
				वापस IPV6_ADDR_ANY;

			अगर (addr->s6_addr32[3] == htonl(0x00000001))
				वापस (IPV6_ADDR_LOOPBACK | IPV6_ADDR_UNICAST |
					IPV6_ADDR_SCOPE_TYPE(IPV6_ADDR_SCOPE_LINKLOCAL));	/* addr-select 3.4 */

			वापस (IPV6_ADDR_COMPATv4 | IPV6_ADDR_UNICAST |
				IPV6_ADDR_SCOPE_TYPE(IPV6_ADDR_SCOPE_GLOBAL));	/* addr-select 3.3 */
		पूर्ण

		अगर (addr->s6_addr32[2] == htonl(0x0000ffff))
			वापस (IPV6_ADDR_MAPPED |
				IPV6_ADDR_SCOPE_TYPE(IPV6_ADDR_SCOPE_GLOBAL));	/* addr-select 3.3 */
	पूर्ण

	वापस (IPV6_ADDR_UNICAST |
		IPV6_ADDR_SCOPE_TYPE(IPV6_ADDR_SCOPE_GLOBAL));	/* addr-select 3.4 */
पूर्ण
EXPORT_SYMBOL(__ipv6_addr_type);

अटल ATOMIC_NOTIFIER_HEAD(inet6addr_chain);
अटल BLOCKING_NOTIFIER_HEAD(inet6addr_validator_chain);

पूर्णांक रेजिस्टर_inet6addr_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_रेजिस्टर(&inet6addr_chain, nb);
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_inet6addr_notअगरier);

पूर्णांक unरेजिस्टर_inet6addr_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_unरेजिस्टर(&inet6addr_chain, nb);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_inet6addr_notअगरier);

पूर्णांक inet6addr_notअगरier_call_chain(अचिन्हित दीर्घ val, व्योम *v)
अणु
	वापस atomic_notअगरier_call_chain(&inet6addr_chain, val, v);
पूर्ण
EXPORT_SYMBOL(inet6addr_notअगरier_call_chain);

पूर्णांक रेजिस्टर_inet6addr_validator_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&inet6addr_validator_chain, nb);
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_inet6addr_validator_notअगरier);

पूर्णांक unरेजिस्टर_inet6addr_validator_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&inet6addr_validator_chain,
						  nb);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_inet6addr_validator_notअगरier);

पूर्णांक inet6addr_validator_notअगरier_call_chain(अचिन्हित दीर्घ val, व्योम *v)
अणु
	वापस blocking_notअगरier_call_chain(&inet6addr_validator_chain, val, v);
पूर्ण
EXPORT_SYMBOL(inet6addr_validator_notअगरier_call_chain);

अटल काष्ठा dst_entry *eafnosupport_ipv6_dst_lookup_flow(काष्ठा net *net,
							   स्थिर काष्ठा sock *sk,
							   काष्ठा flowi6 *fl6,
							   स्थिर काष्ठा in6_addr *final_dst)
अणु
	वापस ERR_PTR(-EAFNOSUPPORT);
पूर्ण

अटल पूर्णांक eafnosupport_ipv6_route_input(काष्ठा sk_buff *skb)
अणु
	वापस -EAFNOSUPPORT;
पूर्ण

अटल काष्ठा fib6_table *eafnosupport_fib6_get_table(काष्ठा net *net, u32 id)
अणु
	वापस शून्य;
पूर्ण

अटल पूर्णांक
eafnosupport_fib6_table_lookup(काष्ठा net *net, काष्ठा fib6_table *table,
			       पूर्णांक oअगर, काष्ठा flowi6 *fl6,
			       काष्ठा fib6_result *res, पूर्णांक flags)
अणु
	वापस -EAFNOSUPPORT;
पूर्ण

अटल पूर्णांक
eafnosupport_fib6_lookup(काष्ठा net *net, पूर्णांक oअगर, काष्ठा flowi6 *fl6,
			 काष्ठा fib6_result *res, पूर्णांक flags)
अणु
	वापस -EAFNOSUPPORT;
पूर्ण

अटल व्योम
eafnosupport_fib6_select_path(स्थिर काष्ठा net *net, काष्ठा fib6_result *res,
			      काष्ठा flowi6 *fl6, पूर्णांक oअगर, bool have_oअगर_match,
			      स्थिर काष्ठा sk_buff *skb, पूर्णांक strict)
अणु
पूर्ण

अटल u32
eafnosupport_ip6_mtu_from_fib6(स्थिर काष्ठा fib6_result *res,
			       स्थिर काष्ठा in6_addr *daddr,
			       स्थिर काष्ठा in6_addr *saddr)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक eafnosupport_fib6_nh_init(काष्ठा net *net, काष्ठा fib6_nh *fib6_nh,
				     काष्ठा fib6_config *cfg, gfp_t gfp_flags,
				     काष्ठा netlink_ext_ack *extack)
अणु
	NL_SET_ERR_MSG(extack, "IPv6 support not enabled in kernel");
	वापस -EAFNOSUPPORT;
पूर्ण

अटल पूर्णांक eafnosupport_ip6_del_rt(काष्ठा net *net, काष्ठा fib6_info *rt,
				   bool skip_notअगरy)
अणु
	वापस -EAFNOSUPPORT;
पूर्ण

अटल पूर्णांक eafnosupport_ipv6_fragment(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb,
				      पूर्णांक (*output)(काष्ठा net *, काष्ठा sock *, काष्ठा sk_buff *))
अणु
	kमुक्त_skb(skb);
	वापस -EAFNOSUPPORT;
पूर्ण

अटल काष्ठा net_device *eafnosupport_ipv6_dev_find(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr,
						     काष्ठा net_device *dev)
अणु
	वापस ERR_PTR(-EAFNOSUPPORT);
पूर्ण

स्थिर काष्ठा ipv6_stub *ipv6_stub __पढ़ो_mostly = &(काष्ठा ipv6_stub) अणु
	.ipv6_dst_lookup_flow = eafnosupport_ipv6_dst_lookup_flow,
	.ipv6_route_input  = eafnosupport_ipv6_route_input,
	.fib6_get_table    = eafnosupport_fib6_get_table,
	.fib6_table_lookup = eafnosupport_fib6_table_lookup,
	.fib6_lookup       = eafnosupport_fib6_lookup,
	.fib6_select_path  = eafnosupport_fib6_select_path,
	.ip6_mtu_from_fib6 = eafnosupport_ip6_mtu_from_fib6,
	.fib6_nh_init	   = eafnosupport_fib6_nh_init,
	.ip6_del_rt	   = eafnosupport_ip6_del_rt,
	.ipv6_fragment	   = eafnosupport_ipv6_fragment,
	.ipv6_dev_find     = eafnosupport_ipv6_dev_find,
पूर्ण;
EXPORT_SYMBOL_GPL(ipv6_stub);

/* IPv6 Wildcard Address and Loopback Address defined by RFC2553 */
स्थिर काष्ठा in6_addr in6addr_loopback = IN6ADDR_LOOPBACK_INIT;
EXPORT_SYMBOL(in6addr_loopback);
स्थिर काष्ठा in6_addr in6addr_any = IN6ADDR_ANY_INIT;
EXPORT_SYMBOL(in6addr_any);
स्थिर काष्ठा in6_addr in6addr_linklocal_allnodes = IN6ADDR_LINKLOCAL_ALLNODES_INIT;
EXPORT_SYMBOL(in6addr_linklocal_allnodes);
स्थिर काष्ठा in6_addr in6addr_linklocal_allrouters = IN6ADDR_LINKLOCAL_ALLROUTERS_INIT;
EXPORT_SYMBOL(in6addr_linklocal_allrouters);
स्थिर काष्ठा in6_addr in6addr_पूर्णांकerfacelocal_allnodes = IN6ADDR_INTERFACELOCAL_ALLNODES_INIT;
EXPORT_SYMBOL(in6addr_पूर्णांकerfacelocal_allnodes);
स्थिर काष्ठा in6_addr in6addr_पूर्णांकerfacelocal_allrouters = IN6ADDR_INTERFACELOCAL_ALLROUTERS_INIT;
EXPORT_SYMBOL(in6addr_पूर्णांकerfacelocal_allrouters);
स्थिर काष्ठा in6_addr in6addr_sitelocal_allrouters = IN6ADDR_SITELOCAL_ALLROUTERS_INIT;
EXPORT_SYMBOL(in6addr_sitelocal_allrouters);

अटल व्योम snmp6_मुक्त_dev(काष्ठा inet6_dev *idev)
अणु
	kमुक्त(idev->stats.icmpv6msgdev);
	kमुक्त(idev->stats.icmpv6dev);
	मुक्त_percpu(idev->stats.ipv6);
पूर्ण

अटल व्योम in6_dev_finish_destroy_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा inet6_dev *idev = container_of(head, काष्ठा inet6_dev, rcu);

	snmp6_मुक्त_dev(idev);
	kमुक्त(idev);
पूर्ण

/* Nobody refers to this device, we may destroy it. */

व्योम in6_dev_finish_destroy(काष्ठा inet6_dev *idev)
अणु
	काष्ठा net_device *dev = idev->dev;

	WARN_ON(!list_empty(&idev->addr_list));
	WARN_ON(rcu_access_poपूर्णांकer(idev->mc_list));
	WARN_ON(समयr_pending(&idev->rs_समयr));

#अगर_घोषित NET_REFCNT_DEBUG
	pr_debug("%s: %s\n", __func__, dev ? dev->name : "NIL");
#पूर्ण_अगर
	dev_put(dev);
	अगर (!idev->dead) अणु
		pr_warn("Freeing alive inet6 device %p\n", idev);
		वापस;
	पूर्ण
	call_rcu(&idev->rcu, in6_dev_finish_destroy_rcu);
पूर्ण
EXPORT_SYMBOL(in6_dev_finish_destroy);
