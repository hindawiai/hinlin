<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	XFRM भव पूर्णांकerface
 *
 *	Copyright (C) 2018 secunet Security Networks AG
 *
 *	Author:
 *	Steffen Klनिश्चित <steffen.klनिश्चित@secunet.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/sockios.h>
#समावेश <linux/icmp.h>
#समावेश <linux/अगर.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/net.h>
#समावेश <linux/in6.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_link.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/init.h>
#समावेश <linux/route.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/slab.h>
#समावेश <linux/hash.h>

#समावेश <linux/uaccess.h>
#समावेश <linux/atomic.h>

#समावेश <net/icmp.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/addrconf.h>
#समावेश <net/xfrm.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <linux/etherdevice.h>

अटल पूर्णांक xfrmi_dev_init(काष्ठा net_device *dev);
अटल व्योम xfrmi_dev_setup(काष्ठा net_device *dev);
अटल काष्ठा rtnl_link_ops xfrmi_link_ops __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक xfrmi_net_id __पढ़ो_mostly;
अटल स्थिर काष्ठा net_device_ops xfrmi_netdev_ops;

#घोषणा XFRMI_HASH_BITS	8
#घोषणा XFRMI_HASH_SIZE	BIT(XFRMI_HASH_BITS)

काष्ठा xfrmi_net अणु
	/* lists क्रम storing पूर्णांकerfaces in use */
	काष्ठा xfrm_अगर __rcu *xfrmi[XFRMI_HASH_SIZE];
पूर्ण;

#घोषणा क्रम_each_xfrmi_rcu(start, xi) \
	क्रम (xi = rcu_dereference(start); xi; xi = rcu_dereference(xi->next))

अटल u32 xfrmi_hash(u32 अगर_id)
अणु
	वापस hash_32(अगर_id, XFRMI_HASH_BITS);
पूर्ण

अटल काष्ठा xfrm_अगर *xfrmi_lookup(काष्ठा net *net, काष्ठा xfrm_state *x)
अणु
	काष्ठा xfrmi_net *xfrmn = net_generic(net, xfrmi_net_id);
	काष्ठा xfrm_अगर *xi;

	क्रम_each_xfrmi_rcu(xfrmn->xfrmi[xfrmi_hash(x->अगर_id)], xi) अणु
		अगर (x->अगर_id == xi->p.अगर_id &&
		    (xi->dev->flags & IFF_UP))
			वापस xi;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा xfrm_अगर *xfrmi_decode_session(काष्ठा sk_buff *skb,
					    अचिन्हित लघु family)
अणु
	काष्ठा net_device *dev;
	पूर्णांक अगरindex = 0;

	अगर (!secpath_exists(skb) || !skb->dev)
		वापस शून्य;

	चयन (family) अणु
	हाल AF_INET6:
		अगरindex = inet6_sdअगर(skb);
		अवरोध;
	हाल AF_INET:
		अगरindex = inet_sdअगर(skb);
		अवरोध;
	पूर्ण

	अगर (अगरindex) अणु
		काष्ठा net *net = xs_net(xfrm_input_state(skb));

		dev = dev_get_by_index_rcu(net, अगरindex);
	पूर्ण अन्यथा अणु
		dev = skb->dev;
	पूर्ण

	अगर (!dev || !(dev->flags & IFF_UP))
		वापस शून्य;
	अगर (dev->netdev_ops != &xfrmi_netdev_ops)
		वापस शून्य;

	वापस netdev_priv(dev);
पूर्ण

अटल व्योम xfrmi_link(काष्ठा xfrmi_net *xfrmn, काष्ठा xfrm_अगर *xi)
अणु
	काष्ठा xfrm_अगर __rcu **xip = &xfrmn->xfrmi[xfrmi_hash(xi->p.अगर_id)];

	rcu_assign_poपूर्णांकer(xi->next , rtnl_dereference(*xip));
	rcu_assign_poपूर्णांकer(*xip, xi);
पूर्ण

अटल व्योम xfrmi_unlink(काष्ठा xfrmi_net *xfrmn, काष्ठा xfrm_अगर *xi)
अणु
	काष्ठा xfrm_अगर __rcu **xip;
	काष्ठा xfrm_अगर *iter;

	क्रम (xip = &xfrmn->xfrmi[xfrmi_hash(xi->p.अगर_id)];
	     (iter = rtnl_dereference(*xip)) != शून्य;
	     xip = &iter->next) अणु
		अगर (xi == iter) अणु
			rcu_assign_poपूर्णांकer(*xip, xi->next);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम xfrmi_dev_मुक्त(काष्ठा net_device *dev)
अणु
	काष्ठा xfrm_अगर *xi = netdev_priv(dev);

	gro_cells_destroy(&xi->gro_cells);
	मुक्त_percpu(dev->tstats);
पूर्ण

अटल पूर्णांक xfrmi_create(काष्ठा net_device *dev)
अणु
	काष्ठा xfrm_अगर *xi = netdev_priv(dev);
	काष्ठा net *net = dev_net(dev);
	काष्ठा xfrmi_net *xfrmn = net_generic(net, xfrmi_net_id);
	पूर्णांक err;

	dev->rtnl_link_ops = &xfrmi_link_ops;
	err = रेजिस्टर_netdevice(dev);
	अगर (err < 0)
		जाओ out;

	xfrmi_link(xfrmn, xi);

	वापस 0;

out:
	वापस err;
पूर्ण

अटल काष्ठा xfrm_अगर *xfrmi_locate(काष्ठा net *net, काष्ठा xfrm_अगर_parms *p)
अणु
	काष्ठा xfrm_अगर __rcu **xip;
	काष्ठा xfrm_अगर *xi;
	काष्ठा xfrmi_net *xfrmn = net_generic(net, xfrmi_net_id);

	क्रम (xip = &xfrmn->xfrmi[xfrmi_hash(p->अगर_id)];
	     (xi = rtnl_dereference(*xip)) != शून्य;
	     xip = &xi->next)
		अगर (xi->p.अगर_id == p->अगर_id)
			वापस xi;

	वापस शून्य;
पूर्ण

अटल व्योम xfrmi_dev_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा xfrm_अगर *xi = netdev_priv(dev);
	काष्ठा xfrmi_net *xfrmn = net_generic(xi->net, xfrmi_net_id);

	xfrmi_unlink(xfrmn, xi);
पूर्ण

अटल व्योम xfrmi_scrub_packet(काष्ठा sk_buff *skb, bool xnet)
अणु
	skb->tstamp = 0;
	skb->pkt_type = PACKET_HOST;
	skb->skb_iअगर = 0;
	skb->ignore_df = 0;
	skb_dst_drop(skb);
	nf_reset_ct(skb);
	nf_reset_trace(skb);

	अगर (!xnet)
		वापस;

	ipvs_reset(skb);
	secpath_reset(skb);
	skb_orphan(skb);
	skb->mark = 0;
पूर्ण

अटल पूर्णांक xfrmi_rcv_cb(काष्ठा sk_buff *skb, पूर्णांक err)
अणु
	स्थिर काष्ठा xfrm_mode *inner_mode;
	काष्ठा net_device *dev;
	काष्ठा xfrm_state *x;
	काष्ठा xfrm_अगर *xi;
	bool xnet;

	अगर (err && !secpath_exists(skb))
		वापस 0;

	x = xfrm_input_state(skb);

	xi = xfrmi_lookup(xs_net(x), x);
	अगर (!xi)
		वापस 1;

	dev = xi->dev;
	skb->dev = dev;

	अगर (err) अणु
		dev->stats.rx_errors++;
		dev->stats.rx_dropped++;

		वापस 0;
	पूर्ण

	xnet = !net_eq(xi->net, dev_net(skb->dev));

	अगर (xnet) अणु
		inner_mode = &x->inner_mode;

		अगर (x->sel.family == AF_UNSPEC) अणु
			inner_mode = xfrm_ip2inner_mode(x, XFRM_MODE_SKB_CB(skb)->protocol);
			अगर (inner_mode == शून्य) अणु
				XFRM_INC_STATS(dev_net(skb->dev),
					       LINUX_MIB_XFRMINSTATEMODEERROR);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		अगर (!xfrm_policy_check(शून्य, XFRM_POLICY_IN, skb,
				       inner_mode->family))
			वापस -EPERM;
	पूर्ण

	xfrmi_scrub_packet(skb, xnet);
	dev_sw_netstats_rx_add(dev, skb->len);

	वापस 0;
पूर्ण

अटल पूर्णांक
xfrmi_xmit2(काष्ठा sk_buff *skb, काष्ठा net_device *dev, काष्ठा flowi *fl)
अणु
	काष्ठा xfrm_अगर *xi = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &xi->dev->stats;
	काष्ठा dst_entry *dst = skb_dst(skb);
	अचिन्हित पूर्णांक length = skb->len;
	काष्ठा net_device *tdev;
	काष्ठा xfrm_state *x;
	पूर्णांक err = -1;
	पूर्णांक mtu;

	dst_hold(dst);
	dst = xfrm_lookup_with_अगरid(xi->net, dst, fl, शून्य, 0, xi->p.अगर_id);
	अगर (IS_ERR(dst)) अणु
		err = PTR_ERR(dst);
		dst = शून्य;
		जाओ tx_err_link_failure;
	पूर्ण

	x = dst->xfrm;
	अगर (!x)
		जाओ tx_err_link_failure;

	अगर (x->अगर_id != xi->p.अगर_id)
		जाओ tx_err_link_failure;

	tdev = dst->dev;

	अगर (tdev == dev) अणु
		stats->collisions++;
		net_warn_ratelimited("%s: Local routing loop detected!\n",
				     dev->name);
		जाओ tx_err_dst_release;
	पूर्ण

	mtu = dst_mtu(dst);
	अगर ((!skb_is_gso(skb) && skb->len > mtu) ||
	    (skb_is_gso(skb) && !skb_gso_validate_network_len(skb, mtu))) अणु
		skb_dst_update_pmtu_no_confirm(skb, mtu);

		अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
			अगर (mtu < IPV6_MIN_MTU)
				mtu = IPV6_MIN_MTU;

			icmpv6_nकरो_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
		पूर्ण अन्यथा अणु
			अगर (!(ip_hdr(skb)->frag_off & htons(IP_DF)))
				जाओ xmit;
			icmp_nकरो_send(skb, ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED,
				      htonl(mtu));
		पूर्ण

		dst_release(dst);
		वापस -EMSGSIZE;
	पूर्ण

xmit:
	xfrmi_scrub_packet(skb, !net_eq(xi->net, dev_net(dev)));
	skb_dst_set(skb, dst);
	skb->dev = tdev;

	err = dst_output(xi->net, skb->sk, skb);
	अगर (net_xmit_eval(err) == 0) अणु
		dev_sw_netstats_tx_add(dev, 1, length);
	पूर्ण अन्यथा अणु
		stats->tx_errors++;
		stats->tx_पातed_errors++;
	पूर्ण

	वापस 0;
tx_err_link_failure:
	stats->tx_carrier_errors++;
	dst_link_failure(skb);
tx_err_dst_release:
	dst_release(dst);
	वापस err;
पूर्ण

अटल netdev_tx_t xfrmi_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा xfrm_अगर *xi = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &xi->dev->stats;
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा flowi fl;
	पूर्णांक ret;

	स_रखो(&fl, 0, माप(fl));

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IPV6):
		xfrm_decode_session(skb, &fl, AF_INET6);
		स_रखो(IP6CB(skb), 0, माप(*IP6CB(skb)));
		अगर (!dst) अणु
			fl.u.ip6.flowi6_oअगर = dev->अगरindex;
			fl.u.ip6.flowi6_flags |= FLOWI_FLAG_ANYSRC;
			dst = ip6_route_output(dev_net(dev), शून्य, &fl.u.ip6);
			अगर (dst->error) अणु
				dst_release(dst);
				stats->tx_carrier_errors++;
				जाओ tx_err;
			पूर्ण
			skb_dst_set(skb, dst);
		पूर्ण
		अवरोध;
	हाल htons(ETH_P_IP):
		xfrm_decode_session(skb, &fl, AF_INET);
		स_रखो(IPCB(skb), 0, माप(*IPCB(skb)));
		अगर (!dst) अणु
			काष्ठा rtable *rt;

			fl.u.ip4.flowi4_oअगर = dev->अगरindex;
			fl.u.ip4.flowi4_flags |= FLOWI_FLAG_ANYSRC;
			rt = __ip_route_output_key(dev_net(dev), &fl.u.ip4);
			अगर (IS_ERR(rt)) अणु
				stats->tx_carrier_errors++;
				जाओ tx_err;
			पूर्ण
			skb_dst_set(skb, &rt->dst);
		पूर्ण
		अवरोध;
	शेष:
		जाओ tx_err;
	पूर्ण

	fl.flowi_oअगर = xi->p.link;

	ret = xfrmi_xmit2(skb, dev, &fl);
	अगर (ret < 0)
		जाओ tx_err;

	वापस NETDEV_TX_OK;

tx_err:
	stats->tx_errors++;
	stats->tx_dropped++;
	kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक xfrmi4_err(काष्ठा sk_buff *skb, u32 info)
अणु
	स्थिर काष्ठा iphdr *iph = (स्थिर काष्ठा iphdr *)skb->data;
	काष्ठा net *net = dev_net(skb->dev);
	पूर्णांक protocol = iph->protocol;
	काष्ठा ip_comp_hdr *ipch;
	काष्ठा ip_esp_hdr *esph;
	काष्ठा ip_auth_hdr *ah ;
	काष्ठा xfrm_state *x;
	काष्ठा xfrm_अगर *xi;
	__be32 spi;

	चयन (protocol) अणु
	हाल IPPROTO_ESP:
		esph = (काष्ठा ip_esp_hdr *)(skb->data+(iph->ihl<<2));
		spi = esph->spi;
		अवरोध;
	हाल IPPROTO_AH:
		ah = (काष्ठा ip_auth_hdr *)(skb->data+(iph->ihl<<2));
		spi = ah->spi;
		अवरोध;
	हाल IPPROTO_COMP:
		ipch = (काष्ठा ip_comp_hdr *)(skb->data+(iph->ihl<<2));
		spi = htonl(ntohs(ipch->cpi));
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	चयन (icmp_hdr(skb)->type) अणु
	हाल ICMP_DEST_UNREACH:
		अगर (icmp_hdr(skb)->code != ICMP_FRAG_NEEDED)
			वापस 0;
	हाल ICMP_REसूचीECT:
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	x = xfrm_state_lookup(net, skb->mark, (स्थिर xfrm_address_t *)&iph->daddr,
			      spi, protocol, AF_INET);
	अगर (!x)
		वापस 0;

	xi = xfrmi_lookup(net, x);
	अगर (!xi) अणु
		xfrm_state_put(x);
		वापस -1;
	पूर्ण

	अगर (icmp_hdr(skb)->type == ICMP_DEST_UNREACH)
		ipv4_update_pmtu(skb, net, info, 0, protocol);
	अन्यथा
		ipv4_redirect(skb, net, 0, protocol);
	xfrm_state_put(x);

	वापस 0;
पूर्ण

अटल पूर्णांक xfrmi6_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
		    u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	स्थिर काष्ठा ipv6hdr *iph = (स्थिर काष्ठा ipv6hdr *)skb->data;
	काष्ठा net *net = dev_net(skb->dev);
	पूर्णांक protocol = iph->nexthdr;
	काष्ठा ip_comp_hdr *ipch;
	काष्ठा ip_esp_hdr *esph;
	काष्ठा ip_auth_hdr *ah;
	काष्ठा xfrm_state *x;
	काष्ठा xfrm_अगर *xi;
	__be32 spi;

	चयन (protocol) अणु
	हाल IPPROTO_ESP:
		esph = (काष्ठा ip_esp_hdr *)(skb->data + offset);
		spi = esph->spi;
		अवरोध;
	हाल IPPROTO_AH:
		ah = (काष्ठा ip_auth_hdr *)(skb->data + offset);
		spi = ah->spi;
		अवरोध;
	हाल IPPROTO_COMP:
		ipch = (काष्ठा ip_comp_hdr *)(skb->data + offset);
		spi = htonl(ntohs(ipch->cpi));
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (type != ICMPV6_PKT_TOOBIG &&
	    type != NDISC_REसूचीECT)
		वापस 0;

	x = xfrm_state_lookup(net, skb->mark, (स्थिर xfrm_address_t *)&iph->daddr,
			      spi, protocol, AF_INET6);
	अगर (!x)
		वापस 0;

	xi = xfrmi_lookup(net, x);
	अगर (!xi) अणु
		xfrm_state_put(x);
		वापस -1;
	पूर्ण

	अगर (type == NDISC_REसूचीECT)
		ip6_redirect(skb, net, skb->dev->अगरindex, 0,
			     sock_net_uid(net, शून्य));
	अन्यथा
		ip6_update_pmtu(skb, net, info, 0, 0, sock_net_uid(net, शून्य));
	xfrm_state_put(x);

	वापस 0;
पूर्ण

अटल पूर्णांक xfrmi_change(काष्ठा xfrm_अगर *xi, स्थिर काष्ठा xfrm_अगर_parms *p)
अणु
	अगर (xi->p.link != p->link)
		वापस -EINVAL;

	xi->p.अगर_id = p->अगर_id;

	वापस 0;
पूर्ण

अटल पूर्णांक xfrmi_update(काष्ठा xfrm_अगर *xi, काष्ठा xfrm_अगर_parms *p)
अणु
	काष्ठा net *net = xi->net;
	काष्ठा xfrmi_net *xfrmn = net_generic(net, xfrmi_net_id);
	पूर्णांक err;

	xfrmi_unlink(xfrmn, xi);
	synchronize_net();
	err = xfrmi_change(xi, p);
	xfrmi_link(xfrmn, xi);
	netdev_state_change(xi->dev);
	वापस err;
पूर्ण

अटल पूर्णांक xfrmi_get_अगरlink(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा xfrm_अगर *xi = netdev_priv(dev);

	वापस xi->p.link;
पूर्ण

अटल स्थिर काष्ठा net_device_ops xfrmi_netdev_ops = अणु
	.nकरो_init	= xfrmi_dev_init,
	.nकरो_uninit	= xfrmi_dev_uninit,
	.nकरो_start_xmit = xfrmi_xmit,
	.nकरो_get_stats64 = dev_get_tstats64,
	.nकरो_get_अगरlink = xfrmi_get_अगरlink,
पूर्ण;

अटल व्योम xfrmi_dev_setup(काष्ठा net_device *dev)
अणु
	dev->netdev_ops 	= &xfrmi_netdev_ops;
	dev->header_ops		= &ip_tunnel_header_ops;
	dev->type		= ARPHRD_NONE;
	dev->mtu		= ETH_DATA_LEN;
	dev->min_mtu		= ETH_MIN_MTU;
	dev->max_mtu		= IP_MAX_MTU;
	dev->flags 		= IFF_NOARP;
	dev->needs_मुक्त_netdev	= true;
	dev->priv_deकाष्ठाor	= xfrmi_dev_मुक्त;
	netअगर_keep_dst(dev);

	eth_broadcast_addr(dev->broadcast);
पूर्ण

#घोषणा XFRMI_FEATURES (NETIF_F_SG |		\
			NETIF_F_FRAGLIST |	\
			NETIF_F_GSO_SOFTWARE |	\
			NETIF_F_HW_CSUM)

अटल पूर्णांक xfrmi_dev_init(काष्ठा net_device *dev)
अणु
	काष्ठा xfrm_अगर *xi = netdev_priv(dev);
	काष्ठा net_device *phydev = __dev_get_by_index(xi->net, xi->p.link);
	पूर्णांक err;

	dev->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
	अगर (!dev->tstats)
		वापस -ENOMEM;

	err = gro_cells_init(&xi->gro_cells, dev);
	अगर (err) अणु
		मुक्त_percpu(dev->tstats);
		वापस err;
	पूर्ण

	dev->features |= NETIF_F_LLTX;
	dev->features |= XFRMI_FEATURES;
	dev->hw_features |= XFRMI_FEATURES;

	अगर (phydev) अणु
		dev->needed_headroom = phydev->needed_headroom;
		dev->needed_tailroom = phydev->needed_tailroom;

		अगर (is_zero_ether_addr(dev->dev_addr))
			eth_hw_addr_inherit(dev, phydev);
		अगर (is_zero_ether_addr(dev->broadcast))
			स_नकल(dev->broadcast, phydev->broadcast,
			       dev->addr_len);
	पूर्ण अन्यथा अणु
		eth_hw_addr_अक्रमom(dev);
		eth_broadcast_addr(dev->broadcast);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xfrmi_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			 काष्ठा netlink_ext_ack *extack)
अणु
	वापस 0;
पूर्ण

अटल व्योम xfrmi_netlink_parms(काष्ठा nlattr *data[],
			       काष्ठा xfrm_अगर_parms *parms)
अणु
	स_रखो(parms, 0, माप(*parms));

	अगर (!data)
		वापस;

	अगर (data[IFLA_XFRM_LINK])
		parms->link = nla_get_u32(data[IFLA_XFRM_LINK]);

	अगर (data[IFLA_XFRM_IF_ID])
		parms->अगर_id = nla_get_u32(data[IFLA_XFRM_IF_ID]);
पूर्ण

अटल पूर्णांक xfrmi_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा xfrm_अगर_parms p;
	काष्ठा xfrm_अगर *xi;
	पूर्णांक err;

	xfrmi_netlink_parms(data, &p);
	xi = xfrmi_locate(net, &p);
	अगर (xi)
		वापस -EEXIST;

	xi = netdev_priv(dev);
	xi->p = p;
	xi->net = net;
	xi->dev = dev;

	err = xfrmi_create(dev);
	वापस err;
पूर्ण

अटल व्योम xfrmi_dellink(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	unरेजिस्टर_netdevice_queue(dev, head);
पूर्ण

अटल पूर्णांक xfrmi_changelink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
			   काष्ठा nlattr *data[],
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा xfrm_अगर *xi = netdev_priv(dev);
	काष्ठा net *net = xi->net;
	काष्ठा xfrm_अगर_parms p;

	xfrmi_netlink_parms(data, &p);
	xi = xfrmi_locate(net, &p);
	अगर (!xi) अणु
		xi = netdev_priv(dev);
	पूर्ण अन्यथा अणु
		अगर (xi->dev != dev)
			वापस -EEXIST;
	पूर्ण

	वापस xfrmi_update(xi, &p);
पूर्ण

अटल माप_प्रकार xfrmi_get_size(स्थिर काष्ठा net_device *dev)
अणु
	वापस
		/* IFLA_XFRM_LINK */
		nla_total_size(4) +
		/* IFLA_XFRM_IF_ID */
		nla_total_size(4) +
		0;
पूर्ण

अटल पूर्णांक xfrmi_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा xfrm_अगर *xi = netdev_priv(dev);
	काष्ठा xfrm_अगर_parms *parm = &xi->p;

	अगर (nla_put_u32(skb, IFLA_XFRM_LINK, parm->link) ||
	    nla_put_u32(skb, IFLA_XFRM_IF_ID, parm->अगर_id))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल काष्ठा net *xfrmi_get_link_net(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा xfrm_अगर *xi = netdev_priv(dev);

	वापस xi->net;
पूर्ण

अटल स्थिर काष्ठा nla_policy xfrmi_policy[IFLA_XFRM_MAX + 1] = अणु
	[IFLA_XFRM_LINK]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_XFRM_IF_ID]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल काष्ठा rtnl_link_ops xfrmi_link_ops __पढ़ो_mostly = अणु
	.kind		= "xfrm",
	.maxtype	= IFLA_XFRM_MAX,
	.policy		= xfrmi_policy,
	.priv_size	= माप(काष्ठा xfrm_अगर),
	.setup		= xfrmi_dev_setup,
	.validate	= xfrmi_validate,
	.newlink	= xfrmi_newlink,
	.dellink	= xfrmi_dellink,
	.changelink	= xfrmi_changelink,
	.get_size	= xfrmi_get_size,
	.fill_info	= xfrmi_fill_info,
	.get_link_net	= xfrmi_get_link_net,
पूर्ण;

अटल व्योम __net_निकास xfrmi_निकास_batch_net(काष्ठा list_head *net_निकास_list)
अणु
	काष्ठा net *net;
	LIST_HEAD(list);

	rtnl_lock();
	list_क्रम_each_entry(net, net_निकास_list, निकास_list) अणु
		काष्ठा xfrmi_net *xfrmn = net_generic(net, xfrmi_net_id);
		काष्ठा xfrm_अगर __rcu **xip;
		काष्ठा xfrm_अगर *xi;
		पूर्णांक i;

		क्रम (i = 0; i < XFRMI_HASH_SIZE; i++) अणु
			क्रम (xip = &xfrmn->xfrmi[i];
			     (xi = rtnl_dereference(*xip)) != शून्य;
			     xip = &xi->next)
				unरेजिस्टर_netdevice_queue(xi->dev, &list);
		पूर्ण
	पूर्ण
	unरेजिस्टर_netdevice_many(&list);
	rtnl_unlock();
पूर्ण

अटल काष्ठा pernet_operations xfrmi_net_ops = अणु
	.निकास_batch = xfrmi_निकास_batch_net,
	.id   = &xfrmi_net_id,
	.size = माप(काष्ठा xfrmi_net),
पूर्ण;

अटल काष्ठा xfrm6_protocol xfrmi_esp6_protocol __पढ़ो_mostly = अणु
	.handler	=	xfrm6_rcv,
	.input_handler	=	xfrm_input,
	.cb_handler	=	xfrmi_rcv_cb,
	.err_handler	=	xfrmi6_err,
	.priority	=	10,
पूर्ण;

अटल काष्ठा xfrm6_protocol xfrmi_ah6_protocol __पढ़ो_mostly = अणु
	.handler	=	xfrm6_rcv,
	.input_handler	=	xfrm_input,
	.cb_handler	=	xfrmi_rcv_cb,
	.err_handler	=	xfrmi6_err,
	.priority	=	10,
पूर्ण;

अटल काष्ठा xfrm6_protocol xfrmi_ipcomp6_protocol __पढ़ो_mostly = अणु
	.handler	=	xfrm6_rcv,
	.input_handler	=	xfrm_input,
	.cb_handler	=	xfrmi_rcv_cb,
	.err_handler	=	xfrmi6_err,
	.priority	=	10,
पूर्ण;

#अगर IS_REACHABLE(CONFIG_INET6_XFRM_TUNNEL)
अटल पूर्णांक xfrmi6_rcv_tunnel(काष्ठा sk_buff *skb)
अणु
	स्थिर xfrm_address_t *saddr;
	__be32 spi;

	saddr = (स्थिर xfrm_address_t *)&ipv6_hdr(skb)->saddr;
	spi = xfrm6_tunnel_spi_lookup(dev_net(skb->dev), saddr);

	वापस xfrm6_rcv_spi(skb, IPPROTO_IPV6, spi, शून्य);
पूर्ण

अटल काष्ठा xfrm6_tunnel xfrmi_ipv6_handler __पढ़ो_mostly = अणु
	.handler	=	xfrmi6_rcv_tunnel,
	.cb_handler	=	xfrmi_rcv_cb,
	.err_handler	=	xfrmi6_err,
	.priority	=	2,
पूर्ण;

अटल काष्ठा xfrm6_tunnel xfrmi_ip6ip_handler __पढ़ो_mostly = अणु
	.handler	=	xfrmi6_rcv_tunnel,
	.cb_handler	=	xfrmi_rcv_cb,
	.err_handler	=	xfrmi6_err,
	.priority	=	2,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा xfrm4_protocol xfrmi_esp4_protocol __पढ़ो_mostly = अणु
	.handler	=	xfrm4_rcv,
	.input_handler	=	xfrm_input,
	.cb_handler	=	xfrmi_rcv_cb,
	.err_handler	=	xfrmi4_err,
	.priority	=	10,
पूर्ण;

अटल काष्ठा xfrm4_protocol xfrmi_ah4_protocol __पढ़ो_mostly = अणु
	.handler	=	xfrm4_rcv,
	.input_handler	=	xfrm_input,
	.cb_handler	=	xfrmi_rcv_cb,
	.err_handler	=	xfrmi4_err,
	.priority	=	10,
पूर्ण;

अटल काष्ठा xfrm4_protocol xfrmi_ipcomp4_protocol __पढ़ो_mostly = अणु
	.handler	=	xfrm4_rcv,
	.input_handler	=	xfrm_input,
	.cb_handler	=	xfrmi_rcv_cb,
	.err_handler	=	xfrmi4_err,
	.priority	=	10,
पूर्ण;

#अगर IS_REACHABLE(CONFIG_INET_XFRM_TUNNEL)
अटल पूर्णांक xfrmi4_rcv_tunnel(काष्ठा sk_buff *skb)
अणु
	वापस xfrm4_rcv_spi(skb, IPPROTO_IPIP, ip_hdr(skb)->saddr);
पूर्ण

अटल काष्ठा xfrm_tunnel xfrmi_ipip_handler __पढ़ो_mostly = अणु
	.handler	=	xfrmi4_rcv_tunnel,
	.cb_handler	=	xfrmi_rcv_cb,
	.err_handler	=	xfrmi4_err,
	.priority	=	3,
पूर्ण;

अटल काष्ठा xfrm_tunnel xfrmi_ipip6_handler __पढ़ो_mostly = अणु
	.handler	=	xfrmi4_rcv_tunnel,
	.cb_handler	=	xfrmi_rcv_cb,
	.err_handler	=	xfrmi4_err,
	.priority	=	2,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init xfrmi4_init(व्योम)
अणु
	पूर्णांक err;

	err = xfrm4_protocol_रेजिस्टर(&xfrmi_esp4_protocol, IPPROTO_ESP);
	अगर (err < 0)
		जाओ xfrm_proto_esp_failed;
	err = xfrm4_protocol_रेजिस्टर(&xfrmi_ah4_protocol, IPPROTO_AH);
	अगर (err < 0)
		जाओ xfrm_proto_ah_failed;
	err = xfrm4_protocol_रेजिस्टर(&xfrmi_ipcomp4_protocol, IPPROTO_COMP);
	अगर (err < 0)
		जाओ xfrm_proto_comp_failed;
#अगर IS_REACHABLE(CONFIG_INET_XFRM_TUNNEL)
	err = xfrm4_tunnel_रेजिस्टर(&xfrmi_ipip_handler, AF_INET);
	अगर (err < 0)
		जाओ xfrm_tunnel_ipip_failed;
	err = xfrm4_tunnel_रेजिस्टर(&xfrmi_ipip6_handler, AF_INET6);
	अगर (err < 0)
		जाओ xfrm_tunnel_ipip6_failed;
#पूर्ण_अगर

	वापस 0;

#अगर IS_REACHABLE(CONFIG_INET_XFRM_TUNNEL)
xfrm_tunnel_ipip6_failed:
	xfrm4_tunnel_deरेजिस्टर(&xfrmi_ipip_handler, AF_INET);
xfrm_tunnel_ipip_failed:
	xfrm4_protocol_deरेजिस्टर(&xfrmi_ipcomp4_protocol, IPPROTO_COMP);
#पूर्ण_अगर
xfrm_proto_comp_failed:
	xfrm4_protocol_deरेजिस्टर(&xfrmi_ah4_protocol, IPPROTO_AH);
xfrm_proto_ah_failed:
	xfrm4_protocol_deरेजिस्टर(&xfrmi_esp4_protocol, IPPROTO_ESP);
xfrm_proto_esp_failed:
	वापस err;
पूर्ण

अटल व्योम xfrmi4_fini(व्योम)
अणु
#अगर IS_REACHABLE(CONFIG_INET_XFRM_TUNNEL)
	xfrm4_tunnel_deरेजिस्टर(&xfrmi_ipip6_handler, AF_INET6);
	xfrm4_tunnel_deरेजिस्टर(&xfrmi_ipip_handler, AF_INET);
#पूर्ण_अगर
	xfrm4_protocol_deरेजिस्टर(&xfrmi_ipcomp4_protocol, IPPROTO_COMP);
	xfrm4_protocol_deरेजिस्टर(&xfrmi_ah4_protocol, IPPROTO_AH);
	xfrm4_protocol_deरेजिस्टर(&xfrmi_esp4_protocol, IPPROTO_ESP);
पूर्ण

अटल पूर्णांक __init xfrmi6_init(व्योम)
अणु
	पूर्णांक err;

	err = xfrm6_protocol_रेजिस्टर(&xfrmi_esp6_protocol, IPPROTO_ESP);
	अगर (err < 0)
		जाओ xfrm_proto_esp_failed;
	err = xfrm6_protocol_रेजिस्टर(&xfrmi_ah6_protocol, IPPROTO_AH);
	अगर (err < 0)
		जाओ xfrm_proto_ah_failed;
	err = xfrm6_protocol_रेजिस्टर(&xfrmi_ipcomp6_protocol, IPPROTO_COMP);
	अगर (err < 0)
		जाओ xfrm_proto_comp_failed;
#अगर IS_REACHABLE(CONFIG_INET6_XFRM_TUNNEL)
	err = xfrm6_tunnel_रेजिस्टर(&xfrmi_ipv6_handler, AF_INET6);
	अगर (err < 0)
		जाओ xfrm_tunnel_ipv6_failed;
	err = xfrm6_tunnel_रेजिस्टर(&xfrmi_ip6ip_handler, AF_INET);
	अगर (err < 0)
		जाओ xfrm_tunnel_ip6ip_failed;
#पूर्ण_अगर

	वापस 0;

#अगर IS_REACHABLE(CONFIG_INET6_XFRM_TUNNEL)
xfrm_tunnel_ip6ip_failed:
	xfrm6_tunnel_deरेजिस्टर(&xfrmi_ipv6_handler, AF_INET6);
xfrm_tunnel_ipv6_failed:
	xfrm6_protocol_deरेजिस्टर(&xfrmi_ipcomp6_protocol, IPPROTO_COMP);
#पूर्ण_अगर
xfrm_proto_comp_failed:
	xfrm6_protocol_deरेजिस्टर(&xfrmi_ah6_protocol, IPPROTO_AH);
xfrm_proto_ah_failed:
	xfrm6_protocol_deरेजिस्टर(&xfrmi_esp6_protocol, IPPROTO_ESP);
xfrm_proto_esp_failed:
	वापस err;
पूर्ण

अटल व्योम xfrmi6_fini(व्योम)
अणु
#अगर IS_REACHABLE(CONFIG_INET6_XFRM_TUNNEL)
	xfrm6_tunnel_deरेजिस्टर(&xfrmi_ip6ip_handler, AF_INET);
	xfrm6_tunnel_deरेजिस्टर(&xfrmi_ipv6_handler, AF_INET6);
#पूर्ण_अगर
	xfrm6_protocol_deरेजिस्टर(&xfrmi_ipcomp6_protocol, IPPROTO_COMP);
	xfrm6_protocol_deरेजिस्टर(&xfrmi_ah6_protocol, IPPROTO_AH);
	xfrm6_protocol_deरेजिस्टर(&xfrmi_esp6_protocol, IPPROTO_ESP);
पूर्ण

अटल स्थिर काष्ठा xfrm_अगर_cb xfrm_अगर_cb = अणु
	.decode_session =	xfrmi_decode_session,
पूर्ण;

अटल पूर्णांक __init xfrmi_init(व्योम)
अणु
	स्थिर अक्षर *msg;
	पूर्णांक err;

	pr_info("IPsec XFRM device driver\n");

	msg = "tunnel device";
	err = रेजिस्टर_pernet_device(&xfrmi_net_ops);
	अगर (err < 0)
		जाओ pernet_dev_failed;

	msg = "xfrm4 protocols";
	err = xfrmi4_init();
	अगर (err < 0)
		जाओ xfrmi4_failed;

	msg = "xfrm6 protocols";
	err = xfrmi6_init();
	अगर (err < 0)
		जाओ xfrmi6_failed;


	msg = "netlink interface";
	err = rtnl_link_रेजिस्टर(&xfrmi_link_ops);
	अगर (err < 0)
		जाओ rtnl_link_failed;

	xfrm_अगर_रेजिस्टर_cb(&xfrm_अगर_cb);

	वापस err;

rtnl_link_failed:
	xfrmi6_fini();
xfrmi6_failed:
	xfrmi4_fini();
xfrmi4_failed:
	unरेजिस्टर_pernet_device(&xfrmi_net_ops);
pernet_dev_failed:
	pr_err("xfrmi init: failed to register %s\n", msg);
	वापस err;
पूर्ण

अटल व्योम __निकास xfrmi_fini(व्योम)
अणु
	xfrm_अगर_unरेजिस्टर_cb();
	rtnl_link_unरेजिस्टर(&xfrmi_link_ops);
	xfrmi4_fini();
	xfrmi6_fini();
	unरेजिस्टर_pernet_device(&xfrmi_net_ops);
पूर्ण

module_init(xfrmi_init);
module_निकास(xfrmi_fini);
MODULE_LICENSE("GPL");
MODULE_ALIAS_RTNL_LINK("xfrm");
MODULE_ALIAS_NETDEV("xfrm0");
MODULE_AUTHOR("Steffen Klassert");
MODULE_DESCRIPTION("XFRM virtual interface");
