<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Copyright (c) 2014 Mahesh Bandewar <maheshb@google.com>
 */

#समावेश "ipvlan.h"

अटल अचिन्हित पूर्णांक ipvlan_netid __पढ़ो_mostly;

काष्ठा ipvlan_netns अणु
	अचिन्हित पूर्णांक ipvl_nf_hook_refcnt;
पूर्ण;

अटल काष्ठा ipvl_addr *ipvlan_skb_to_addr(काष्ठा sk_buff *skb,
					    काष्ठा net_device *dev)
अणु
	काष्ठा ipvl_addr *addr = शून्य;
	काष्ठा ipvl_port *port;
	पूर्णांक addr_type;
	व्योम *lyr3h;

	अगर (!dev || !netअगर_is_ipvlan_port(dev))
		जाओ out;

	port = ipvlan_port_get_rcu(dev);
	अगर (!port || port->mode != IPVLAN_MODE_L3S)
		जाओ out;

	lyr3h = ipvlan_get_L3_hdr(port, skb, &addr_type);
	अगर (!lyr3h)
		जाओ out;

	addr = ipvlan_addr_lookup(port, lyr3h, addr_type, true);
out:
	वापस addr;
पूर्ण

अटल काष्ठा sk_buff *ipvlan_l3_rcv(काष्ठा net_device *dev,
				     काष्ठा sk_buff *skb, u16 proto)
अणु
	काष्ठा ipvl_addr *addr;
	काष्ठा net_device *sdev;

	addr = ipvlan_skb_to_addr(skb, dev);
	अगर (!addr)
		जाओ out;

	sdev = addr->master->dev;
	चयन (proto) अणु
	हाल AF_INET:
	अणु
		काष्ठा iphdr *ip4h = ip_hdr(skb);
		पूर्णांक err;

		err = ip_route_input_noref(skb, ip4h->daddr, ip4h->saddr,
					   ip4h->tos, sdev);
		अगर (unlikely(err))
			जाओ out;
		अवरोध;
	पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
	अणु
		काष्ठा dst_entry *dst;
		काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);
		पूर्णांक flags = RT6_LOOKUP_F_HAS_SADDR;
		काष्ठा flowi6 fl6 = अणु
			.flowi6_iअगर   = sdev->अगरindex,
			.daddr        = ip6h->daddr,
			.saddr        = ip6h->saddr,
			.flowlabel    = ip6_flowinfo(ip6h),
			.flowi6_mark  = skb->mark,
			.flowi6_proto = ip6h->nexthdr,
		पूर्ण;

		skb_dst_drop(skb);
		dst = ip6_route_input_lookup(dev_net(sdev), sdev, &fl6,
					     skb, flags);
		skb_dst_set(skb, dst);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण
out:
	वापस skb;
पूर्ण

अटल स्थिर काष्ठा l3mdev_ops ipvl_l3mdev_ops = अणु
	.l3mdev_l3_rcv = ipvlan_l3_rcv,
पूर्ण;

अटल अचिन्हित पूर्णांक ipvlan_nf_input(व्योम *priv, काष्ठा sk_buff *skb,
				    स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा ipvl_addr *addr;
	अचिन्हित पूर्णांक len;

	addr = ipvlan_skb_to_addr(skb, skb->dev);
	अगर (!addr)
		जाओ out;

	skb->dev = addr->master->dev;
	len = skb->len + ETH_HLEN;
	ipvlan_count_rx(addr->master, len, true, false);
out:
	वापस NF_ACCEPT;
पूर्ण

अटल स्थिर काष्ठा nf_hook_ops ipvl_nfops[] = अणु
	अणु
		.hook     = ipvlan_nf_input,
		.pf       = NFPROTO_IPV4,
		.hooknum  = NF_INET_LOCAL_IN,
		.priority = पूर्णांक_उच्च,
	पूर्ण,
#अगर IS_ENABLED(CONFIG_IPV6)
	अणु
		.hook     = ipvlan_nf_input,
		.pf       = NFPROTO_IPV6,
		.hooknum  = NF_INET_LOCAL_IN,
		.priority = पूर्णांक_उच्च,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक ipvlan_रेजिस्टर_nf_hook(काष्ठा net *net)
अणु
	काष्ठा ipvlan_netns *vnet = net_generic(net, ipvlan_netid);
	पूर्णांक err = 0;

	अगर (!vnet->ipvl_nf_hook_refcnt) अणु
		err = nf_रेजिस्टर_net_hooks(net, ipvl_nfops,
					    ARRAY_SIZE(ipvl_nfops));
		अगर (!err)
			vnet->ipvl_nf_hook_refcnt = 1;
	पूर्ण अन्यथा अणु
		vnet->ipvl_nf_hook_refcnt++;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम ipvlan_unरेजिस्टर_nf_hook(काष्ठा net *net)
अणु
	काष्ठा ipvlan_netns *vnet = net_generic(net, ipvlan_netid);

	अगर (WARN_ON(!vnet->ipvl_nf_hook_refcnt))
		वापस;

	vnet->ipvl_nf_hook_refcnt--;
	अगर (!vnet->ipvl_nf_hook_refcnt)
		nf_unरेजिस्टर_net_hooks(net, ipvl_nfops,
					ARRAY_SIZE(ipvl_nfops));
पूर्ण

व्योम ipvlan_migrate_l3s_hook(काष्ठा net *oldnet, काष्ठा net *newnet)
अणु
	काष्ठा ipvlan_netns *old_vnet;

	ASSERT_RTNL();

	old_vnet = net_generic(oldnet, ipvlan_netid);
	अगर (!old_vnet->ipvl_nf_hook_refcnt)
		वापस;

	ipvlan_रेजिस्टर_nf_hook(newnet);
	ipvlan_unरेजिस्टर_nf_hook(oldnet);
पूर्ण

अटल व्योम ipvlan_ns_निकास(काष्ठा net *net)
अणु
	काष्ठा ipvlan_netns *vnet = net_generic(net, ipvlan_netid);

	अगर (WARN_ON_ONCE(vnet->ipvl_nf_hook_refcnt)) अणु
		vnet->ipvl_nf_hook_refcnt = 0;
		nf_unरेजिस्टर_net_hooks(net, ipvl_nfops,
					ARRAY_SIZE(ipvl_nfops));
	पूर्ण
पूर्ण

अटल काष्ठा pernet_operations ipvlan_net_ops = अणु
	.id   = &ipvlan_netid,
	.size = माप(काष्ठा ipvlan_netns),
	.निकास = ipvlan_ns_निकास,
पूर्ण;

पूर्णांक ipvlan_l3s_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&ipvlan_net_ops);
पूर्ण

व्योम ipvlan_l3s_cleanup(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&ipvlan_net_ops);
पूर्ण

पूर्णांक ipvlan_l3s_रेजिस्टर(काष्ठा ipvl_port *port)
अणु
	काष्ठा net_device *dev = port->dev;
	पूर्णांक ret;

	ASSERT_RTNL();

	ret = ipvlan_रेजिस्टर_nf_hook(पढ़ो_pnet(&port->pnet));
	अगर (!ret) अणु
		dev->l3mdev_ops = &ipvl_l3mdev_ops;
		dev->priv_flags |= IFF_L3MDEV_RX_HANDLER;
	पूर्ण

	वापस ret;
पूर्ण

व्योम ipvlan_l3s_unरेजिस्टर(काष्ठा ipvl_port *port)
अणु
	काष्ठा net_device *dev = port->dev;

	ASSERT_RTNL();

	dev->priv_flags &= ~IFF_L3MDEV_RX_HANDLER;
	ipvlan_unरेजिस्टर_nf_hook(पढ़ो_pnet(&port->pnet));
	dev->l3mdev_ops = शून्य;
पूर्ण
