<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Linux NET3: IP/IP protocol decoder modअगरied to support
 *		    भव tunnel पूर्णांकerface
 *
 *	Authors:
 *		Saurabh Mohan (saurabh.mohan@vyatta.com) 05/07/2012
 */

/*
   This version of net/ipv4/ip_vti.c is cloned of net/ipv4/ipip.c

   For comments look at net/ipv4/ip_gre.c --ANK
 */


#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/in.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/init.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/icmpv6.h>

#समावेश <net/sock.h>
#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/xfrm.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>

अटल काष्ठा rtnl_link_ops vti_link_ops __पढ़ो_mostly;

अटल अचिन्हित पूर्णांक vti_net_id __पढ़ो_mostly;
अटल पूर्णांक vti_tunnel_init(काष्ठा net_device *dev);

अटल पूर्णांक vti_input(काष्ठा sk_buff *skb, पूर्णांक nexthdr, __be32 spi,
		     पूर्णांक encap_type, bool update_skb_dev)
अणु
	काष्ठा ip_tunnel *tunnel;
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा ip_tunnel_net *itn = net_generic(net, vti_net_id);

	tunnel = ip_tunnel_lookup(itn, skb->dev->अगरindex, TUNNEL_NO_KEY,
				  iph->saddr, iph->daddr, 0);
	अगर (tunnel) अणु
		अगर (!xfrm4_policy_check(शून्य, XFRM_POLICY_IN, skb))
			जाओ drop;

		XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip4 = tunnel;

		अगर (update_skb_dev)
			skb->dev = tunnel->dev;

		वापस xfrm_input(skb, nexthdr, spi, encap_type);
	पूर्ण

	वापस -EINVAL;
drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक vti_input_proto(काष्ठा sk_buff *skb, पूर्णांक nexthdr, __be32 spi,
			   पूर्णांक encap_type)
अणु
	वापस vti_input(skb, nexthdr, spi, encap_type, false);
पूर्ण

अटल पूर्णांक vti_rcv(काष्ठा sk_buff *skb, __be32 spi, bool update_skb_dev)
अणु
	XFRM_SPI_SKB_CB(skb)->family = AF_INET;
	XFRM_SPI_SKB_CB(skb)->daddroff = दुरत्व(काष्ठा iphdr, daddr);

	वापस vti_input(skb, ip_hdr(skb)->protocol, spi, 0, update_skb_dev);
पूर्ण

अटल पूर्णांक vti_rcv_proto(काष्ठा sk_buff *skb)
अणु
	वापस vti_rcv(skb, 0, false);
पूर्ण

अटल पूर्णांक vti_rcv_cb(काष्ठा sk_buff *skb, पूर्णांक err)
अणु
	अचिन्हित लघु family;
	काष्ठा net_device *dev;
	काष्ठा xfrm_state *x;
	स्थिर काष्ठा xfrm_mode *inner_mode;
	काष्ठा ip_tunnel *tunnel = XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip4;
	u32 orig_mark = skb->mark;
	पूर्णांक ret;

	अगर (!tunnel)
		वापस 1;

	dev = tunnel->dev;

	अगर (err) अणु
		dev->stats.rx_errors++;
		dev->stats.rx_dropped++;

		वापस 0;
	पूर्ण

	x = xfrm_input_state(skb);

	inner_mode = &x->inner_mode;

	अगर (x->sel.family == AF_UNSPEC) अणु
		inner_mode = xfrm_ip2inner_mode(x, XFRM_MODE_SKB_CB(skb)->protocol);
		अगर (inner_mode == शून्य) अणु
			XFRM_INC_STATS(dev_net(skb->dev),
				       LINUX_MIB_XFRMINSTATEMODEERROR);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	family = inner_mode->family;

	skb->mark = be32_to_cpu(tunnel->parms.i_key);
	ret = xfrm_policy_check(शून्य, XFRM_POLICY_IN, skb, family);
	skb->mark = orig_mark;

	अगर (!ret)
		वापस -EPERM;

	skb_scrub_packet(skb, !net_eq(tunnel->net, dev_net(skb->dev)));
	skb->dev = dev;
	dev_sw_netstats_rx_add(dev, skb->len);

	वापस 0;
पूर्ण

अटल bool vti_state_check(स्थिर काष्ठा xfrm_state *x, __be32 dst, __be32 src)
अणु
	xfrm_address_t *daddr = (xfrm_address_t *)&dst;
	xfrm_address_t *saddr = (xfrm_address_t *)&src;

	/* अगर there is no transक्रमm then this tunnel is not functional.
	 * Or अगर the xfrm is not mode tunnel.
	 */
	अगर (!x || x->props.mode != XFRM_MODE_TUNNEL ||
	    x->props.family != AF_INET)
		वापस false;

	अगर (!dst)
		वापस xfrm_addr_equal(saddr, &x->props.saddr, AF_INET);

	अगर (!xfrm_state_addr_check(x, daddr, saddr, AF_INET))
		वापस false;

	वापस true;
पूर्ण

अटल netdev_tx_t vti_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			    काष्ठा flowi *fl)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	काष्ठा ip_tunnel_parm *parms = &tunnel->parms;
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा net_device *tdev;	/* Device to other host */
	पूर्णांक pkt_len = skb->len;
	पूर्णांक err;
	पूर्णांक mtu;

	अगर (!dst) अणु
		चयन (skb->protocol) अणु
		हाल htons(ETH_P_IP): अणु
			काष्ठा rtable *rt;

			fl->u.ip4.flowi4_oअगर = dev->अगरindex;
			fl->u.ip4.flowi4_flags |= FLOWI_FLAG_ANYSRC;
			rt = __ip_route_output_key(dev_net(dev), &fl->u.ip4);
			अगर (IS_ERR(rt)) अणु
				dev->stats.tx_carrier_errors++;
				जाओ tx_error_icmp;
			पूर्ण
			dst = &rt->dst;
			skb_dst_set(skb, dst);
			अवरोध;
		पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
		हाल htons(ETH_P_IPV6):
			fl->u.ip6.flowi6_oअगर = dev->अगरindex;
			fl->u.ip6.flowi6_flags |= FLOWI_FLAG_ANYSRC;
			dst = ip6_route_output(dev_net(dev), शून्य, &fl->u.ip6);
			अगर (dst->error) अणु
				dst_release(dst);
				dst = शून्य;
				dev->stats.tx_carrier_errors++;
				जाओ tx_error_icmp;
			पूर्ण
			skb_dst_set(skb, dst);
			अवरोध;
#पूर्ण_अगर
		शेष:
			dev->stats.tx_carrier_errors++;
			जाओ tx_error_icmp;
		पूर्ण
	पूर्ण

	dst_hold(dst);
	dst = xfrm_lookup_route(tunnel->net, dst, fl, शून्य, 0);
	अगर (IS_ERR(dst)) अणु
		dev->stats.tx_carrier_errors++;
		जाओ tx_error_icmp;
	पूर्ण

	अगर (dst->flags & DST_XFRM_QUEUE)
		जाओ xmit;

	अगर (!vti_state_check(dst->xfrm, parms->iph.daddr, parms->iph.saddr)) अणु
		dev->stats.tx_carrier_errors++;
		dst_release(dst);
		जाओ tx_error_icmp;
	पूर्ण

	tdev = dst->dev;

	अगर (tdev == dev) अणु
		dst_release(dst);
		dev->stats.collisions++;
		जाओ tx_error;
	पूर्ण

	mtu = dst_mtu(dst);
	अगर (skb->len > mtu) अणु
		skb_dst_update_pmtu_no_confirm(skb, mtu);
		अगर (skb->protocol == htons(ETH_P_IP)) अणु
			अगर (!(ip_hdr(skb)->frag_off & htons(IP_DF)))
				जाओ xmit;
			icmp_nकरो_send(skb, ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED,
				      htonl(mtu));
		पूर्ण अन्यथा अणु
			अगर (mtu < IPV6_MIN_MTU)
				mtu = IPV6_MIN_MTU;

			icmpv6_nकरो_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
		पूर्ण

		dst_release(dst);
		जाओ tx_error;
	पूर्ण

xmit:
	skb_scrub_packet(skb, !net_eq(tunnel->net, dev_net(dev)));
	skb_dst_set(skb, dst);
	skb->dev = skb_dst(skb)->dev;

	err = dst_output(tunnel->net, skb->sk, skb);
	अगर (net_xmit_eval(err) == 0)
		err = pkt_len;
	iptunnel_xmit_stats(dev, err);
	वापस NETDEV_TX_OK;

tx_error_icmp:
	dst_link_failure(skb);
tx_error:
	dev->stats.tx_errors++;
	kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

/* This function assumes it is being called from dev_queue_xmit()
 * and that skb is filled properly by that function.
 */
अटल netdev_tx_t vti_tunnel_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	काष्ठा flowi fl;

	अगर (!pskb_inet_may_pull(skb))
		जाओ tx_err;

	स_रखो(&fl, 0, माप(fl));

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		xfrm_decode_session(skb, &fl, AF_INET);
		स_रखो(IPCB(skb), 0, माप(*IPCB(skb)));
		अवरोध;
	हाल htons(ETH_P_IPV6):
		xfrm_decode_session(skb, &fl, AF_INET6);
		स_रखो(IP6CB(skb), 0, माप(*IP6CB(skb)));
		अवरोध;
	शेष:
		जाओ tx_err;
	पूर्ण

	/* override mark with tunnel output key */
	fl.flowi_mark = be32_to_cpu(tunnel->parms.o_key);

	वापस vti_xmit(skb, dev, &fl);

tx_err:
	dev->stats.tx_errors++;
	kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक vti4_err(काष्ठा sk_buff *skb, u32 info)
अणु
	__be32 spi;
	__u32 mark;
	काष्ठा xfrm_state *x;
	काष्ठा ip_tunnel *tunnel;
	काष्ठा ip_esp_hdr *esph;
	काष्ठा ip_auth_hdr *ah ;
	काष्ठा ip_comp_hdr *ipch;
	काष्ठा net *net = dev_net(skb->dev);
	स्थिर काष्ठा iphdr *iph = (स्थिर काष्ठा iphdr *)skb->data;
	पूर्णांक protocol = iph->protocol;
	काष्ठा ip_tunnel_net *itn = net_generic(net, vti_net_id);

	tunnel = ip_tunnel_lookup(itn, skb->dev->अगरindex, TUNNEL_NO_KEY,
				  iph->daddr, iph->saddr, 0);
	अगर (!tunnel)
		वापस -1;

	mark = be32_to_cpu(tunnel->parms.o_key);

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

	x = xfrm_state_lookup(net, mark, (स्थिर xfrm_address_t *)&iph->daddr,
			      spi, protocol, AF_INET);
	अगर (!x)
		वापस 0;

	अगर (icmp_hdr(skb)->type == ICMP_DEST_UNREACH)
		ipv4_update_pmtu(skb, net, info, 0, protocol);
	अन्यथा
		ipv4_redirect(skb, net, 0, protocol);
	xfrm_state_put(x);

	वापस 0;
पूर्ण

अटल पूर्णांक
vti_tunnel_ctl(काष्ठा net_device *dev, काष्ठा ip_tunnel_parm *p, पूर्णांक cmd)
अणु
	पूर्णांक err = 0;

	अगर (cmd == SIOCADDTUNNEL || cmd == SIOCCHGTUNNEL) अणु
		अगर (p->iph.version != 4 || p->iph.protocol != IPPROTO_IPIP ||
		    p->iph.ihl != 5)
			वापस -EINVAL;
	पूर्ण

	अगर (!(p->i_flags & GRE_KEY))
		p->i_key = 0;
	अगर (!(p->o_flags & GRE_KEY))
		p->o_key = 0;

	p->i_flags = VTI_ISVTI;

	err = ip_tunnel_ctl(dev, p, cmd);
	अगर (err)
		वापस err;

	अगर (cmd != SIOCDELTUNNEL) अणु
		p->i_flags |= GRE_KEY;
		p->o_flags |= GRE_KEY;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops vti_netdev_ops = अणु
	.nकरो_init	= vti_tunnel_init,
	.nकरो_uninit	= ip_tunnel_uninit,
	.nकरो_start_xmit	= vti_tunnel_xmit,
	.nकरो_करो_ioctl	= ip_tunnel_ioctl,
	.nकरो_change_mtu	= ip_tunnel_change_mtu,
	.nकरो_get_stats64 = dev_get_tstats64,
	.nकरो_get_अगरlink = ip_tunnel_get_अगरlink,
	.nकरो_tunnel_ctl	= vti_tunnel_ctl,
पूर्ण;

अटल व्योम vti_tunnel_setup(काष्ठा net_device *dev)
अणु
	dev->netdev_ops		= &vti_netdev_ops;
	dev->header_ops		= &ip_tunnel_header_ops;
	dev->type		= ARPHRD_TUNNEL;
	ip_tunnel_setup(dev, vti_net_id);
पूर्ण

अटल पूर्णांक vti_tunnel_init(काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	काष्ठा iphdr *iph = &tunnel->parms.iph;

	स_नकल(dev->dev_addr, &iph->saddr, 4);
	स_नकल(dev->broadcast, &iph->daddr, 4);

	dev->flags		= IFF_NOARP;
	dev->addr_len		= 4;
	dev->features		|= NETIF_F_LLTX;
	netअगर_keep_dst(dev);

	वापस ip_tunnel_init(dev);
पूर्ण

अटल व्योम __net_init vti_fb_tunnel_init(काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	काष्ठा iphdr *iph = &tunnel->parms.iph;

	iph->version		= 4;
	iph->protocol		= IPPROTO_IPIP;
	iph->ihl		= 5;
पूर्ण

अटल काष्ठा xfrm4_protocol vti_esp4_protocol __पढ़ो_mostly = अणु
	.handler	=	vti_rcv_proto,
	.input_handler	=	vti_input_proto,
	.cb_handler	=	vti_rcv_cb,
	.err_handler	=	vti4_err,
	.priority	=	100,
पूर्ण;

अटल काष्ठा xfrm4_protocol vti_ah4_protocol __पढ़ो_mostly = अणु
	.handler	=	vti_rcv_proto,
	.input_handler	=	vti_input_proto,
	.cb_handler	=	vti_rcv_cb,
	.err_handler	=	vti4_err,
	.priority	=	100,
पूर्ण;

अटल काष्ठा xfrm4_protocol vti_ipcomp4_protocol __पढ़ो_mostly = अणु
	.handler	=	vti_rcv_proto,
	.input_handler	=	vti_input_proto,
	.cb_handler	=	vti_rcv_cb,
	.err_handler	=	vti4_err,
	.priority	=	100,
पूर्ण;

#अगर IS_ENABLED(CONFIG_INET_XFRM_TUNNEL)
अटल पूर्णांक vti_rcv_tunnel(काष्ठा sk_buff *skb)
अणु
	XFRM_SPI_SKB_CB(skb)->family = AF_INET;
	XFRM_SPI_SKB_CB(skb)->daddroff = दुरत्व(काष्ठा iphdr, daddr);

	वापस vti_input(skb, IPPROTO_IPIP, ip_hdr(skb)->saddr, 0, false);
पूर्ण

अटल काष्ठा xfrm_tunnel vti_ipip_handler __पढ़ो_mostly = अणु
	.handler	=	vti_rcv_tunnel,
	.cb_handler	=	vti_rcv_cb,
	.err_handler	=	vti4_err,
	.priority	=	0,
पूर्ण;

#अगर IS_ENABLED(CONFIG_IPV6)
अटल काष्ठा xfrm_tunnel vti_ipip6_handler __पढ़ो_mostly = अणु
	.handler	=	vti_rcv_tunnel,
	.cb_handler	=	vti_rcv_cb,
	.err_handler	=	vti4_err,
	.priority	=	0,
पूर्ण;
#पूर्ण_अगर
#पूर्ण_अगर

अटल पूर्णांक __net_init vti_init_net(काष्ठा net *net)
अणु
	पूर्णांक err;
	काष्ठा ip_tunnel_net *itn;

	err = ip_tunnel_init_net(net, vti_net_id, &vti_link_ops, "ip_vti0");
	अगर (err)
		वापस err;
	itn = net_generic(net, vti_net_id);
	अगर (itn->fb_tunnel_dev)
		vti_fb_tunnel_init(itn->fb_tunnel_dev);
	वापस 0;
पूर्ण

अटल व्योम __net_निकास vti_निकास_batch_net(काष्ठा list_head *list_net)
अणु
	ip_tunnel_delete_nets(list_net, vti_net_id, &vti_link_ops);
पूर्ण

अटल काष्ठा pernet_operations vti_net_ops = अणु
	.init = vti_init_net,
	.निकास_batch = vti_निकास_batch_net,
	.id   = &vti_net_id,
	.size = माप(काष्ठा ip_tunnel_net),
पूर्ण;

अटल पूर्णांक vti_tunnel_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			       काष्ठा netlink_ext_ack *extack)
अणु
	वापस 0;
पूर्ण

अटल व्योम vti_netlink_parms(काष्ठा nlattr *data[],
			      काष्ठा ip_tunnel_parm *parms,
			      __u32 *fwmark)
अणु
	स_रखो(parms, 0, माप(*parms));

	parms->iph.protocol = IPPROTO_IPIP;

	अगर (!data)
		वापस;

	parms->i_flags = VTI_ISVTI;

	अगर (data[IFLA_VTI_LINK])
		parms->link = nla_get_u32(data[IFLA_VTI_LINK]);

	अगर (data[IFLA_VTI_IKEY])
		parms->i_key = nla_get_be32(data[IFLA_VTI_IKEY]);

	अगर (data[IFLA_VTI_OKEY])
		parms->o_key = nla_get_be32(data[IFLA_VTI_OKEY]);

	अगर (data[IFLA_VTI_LOCAL])
		parms->iph.saddr = nla_get_in_addr(data[IFLA_VTI_LOCAL]);

	अगर (data[IFLA_VTI_REMOTE])
		parms->iph.daddr = nla_get_in_addr(data[IFLA_VTI_REMOTE]);

	अगर (data[IFLA_VTI_FWMARK])
		*fwmark = nla_get_u32(data[IFLA_VTI_FWMARK]);
पूर्ण

अटल पूर्णांक vti_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
		       काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ip_tunnel_parm parms;
	__u32 fwmark = 0;

	vti_netlink_parms(data, &parms, &fwmark);
	वापस ip_tunnel_newlink(dev, tb, &parms, fwmark);
पूर्ण

अटल पूर्णांक vti_changelink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
			  काष्ठा nlattr *data[],
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);
	__u32 fwmark = t->fwmark;
	काष्ठा ip_tunnel_parm p;

	vti_netlink_parms(data, &p, &fwmark);
	वापस ip_tunnel_changelink(dev, tb, &p, fwmark);
पूर्ण

अटल माप_प्रकार vti_get_size(स्थिर काष्ठा net_device *dev)
अणु
	वापस
		/* IFLA_VTI_LINK */
		nla_total_size(4) +
		/* IFLA_VTI_IKEY */
		nla_total_size(4) +
		/* IFLA_VTI_OKEY */
		nla_total_size(4) +
		/* IFLA_VTI_LOCAL */
		nla_total_size(4) +
		/* IFLA_VTI_REMOTE */
		nla_total_size(4) +
		/* IFLA_VTI_FWMARK */
		nla_total_size(4) +
		0;
पूर्ण

अटल पूर्णांक vti_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);
	काष्ठा ip_tunnel_parm *p = &t->parms;

	अगर (nla_put_u32(skb, IFLA_VTI_LINK, p->link) ||
	    nla_put_be32(skb, IFLA_VTI_IKEY, p->i_key) ||
	    nla_put_be32(skb, IFLA_VTI_OKEY, p->o_key) ||
	    nla_put_in_addr(skb, IFLA_VTI_LOCAL, p->iph.saddr) ||
	    nla_put_in_addr(skb, IFLA_VTI_REMOTE, p->iph.daddr) ||
	    nla_put_u32(skb, IFLA_VTI_FWMARK, t->fwmark))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy vti_policy[IFLA_VTI_MAX + 1] = अणु
	[IFLA_VTI_LINK]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_VTI_IKEY]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_VTI_OKEY]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_VTI_LOCAL]	= अणु .len = माप_field(काष्ठा iphdr, saddr) पूर्ण,
	[IFLA_VTI_REMOTE]	= अणु .len = माप_field(काष्ठा iphdr, daddr) पूर्ण,
	[IFLA_VTI_FWMARK]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल काष्ठा rtnl_link_ops vti_link_ops __पढ़ो_mostly = अणु
	.kind		= "vti",
	.maxtype	= IFLA_VTI_MAX,
	.policy		= vti_policy,
	.priv_size	= माप(काष्ठा ip_tunnel),
	.setup		= vti_tunnel_setup,
	.validate	= vti_tunnel_validate,
	.newlink	= vti_newlink,
	.changelink	= vti_changelink,
	.dellink        = ip_tunnel_dellink,
	.get_size	= vti_get_size,
	.fill_info	= vti_fill_info,
	.get_link_net	= ip_tunnel_get_link_net,
पूर्ण;

अटल पूर्णांक __init vti_init(व्योम)
अणु
	स्थिर अक्षर *msg;
	पूर्णांक err;

	pr_info("IPv4 over IPsec tunneling driver\n");

	msg = "tunnel device";
	err = रेजिस्टर_pernet_device(&vti_net_ops);
	अगर (err < 0)
		जाओ pernet_dev_failed;

	msg = "tunnel protocols";
	err = xfrm4_protocol_रेजिस्टर(&vti_esp4_protocol, IPPROTO_ESP);
	अगर (err < 0)
		जाओ xfrm_proto_esp_failed;
	err = xfrm4_protocol_रेजिस्टर(&vti_ah4_protocol, IPPROTO_AH);
	अगर (err < 0)
		जाओ xfrm_proto_ah_failed;
	err = xfrm4_protocol_रेजिस्टर(&vti_ipcomp4_protocol, IPPROTO_COMP);
	अगर (err < 0)
		जाओ xfrm_proto_comp_failed;

#अगर IS_ENABLED(CONFIG_INET_XFRM_TUNNEL)
	msg = "ipip tunnel";
	err = xfrm4_tunnel_रेजिस्टर(&vti_ipip_handler, AF_INET);
	अगर (err < 0)
		जाओ xfrm_tunnel_ipip_failed;
#अगर IS_ENABLED(CONFIG_IPV6)
	err = xfrm4_tunnel_रेजिस्टर(&vti_ipip6_handler, AF_INET6);
	अगर (err < 0)
		जाओ xfrm_tunnel_ipip6_failed;
#पूर्ण_अगर
#पूर्ण_अगर

	msg = "netlink interface";
	err = rtnl_link_रेजिस्टर(&vti_link_ops);
	अगर (err < 0)
		जाओ rtnl_link_failed;

	वापस err;

rtnl_link_failed:
#अगर IS_ENABLED(CONFIG_INET_XFRM_TUNNEL)
#अगर IS_ENABLED(CONFIG_IPV6)
	xfrm4_tunnel_deरेजिस्टर(&vti_ipip6_handler, AF_INET6);
xfrm_tunnel_ipip6_failed:
#पूर्ण_अगर
	xfrm4_tunnel_deरेजिस्टर(&vti_ipip_handler, AF_INET);
xfrm_tunnel_ipip_failed:
#पूर्ण_अगर
	xfrm4_protocol_deरेजिस्टर(&vti_ipcomp4_protocol, IPPROTO_COMP);
xfrm_proto_comp_failed:
	xfrm4_protocol_deरेजिस्टर(&vti_ah4_protocol, IPPROTO_AH);
xfrm_proto_ah_failed:
	xfrm4_protocol_deरेजिस्टर(&vti_esp4_protocol, IPPROTO_ESP);
xfrm_proto_esp_failed:
	unरेजिस्टर_pernet_device(&vti_net_ops);
pernet_dev_failed:
	pr_err("vti init: failed to register %s\n", msg);
	वापस err;
पूर्ण

अटल व्योम __निकास vti_fini(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&vti_link_ops);
#अगर IS_ENABLED(CONFIG_INET_XFRM_TUNNEL)
#अगर IS_ENABLED(CONFIG_IPV6)
	xfrm4_tunnel_deरेजिस्टर(&vti_ipip6_handler, AF_INET6);
#पूर्ण_अगर
	xfrm4_tunnel_deरेजिस्टर(&vti_ipip_handler, AF_INET);
#पूर्ण_अगर
	xfrm4_protocol_deरेजिस्टर(&vti_ipcomp4_protocol, IPPROTO_COMP);
	xfrm4_protocol_deरेजिस्टर(&vti_ah4_protocol, IPPROTO_AH);
	xfrm4_protocol_deरेजिस्टर(&vti_esp4_protocol, IPPROTO_ESP);
	unरेजिस्टर_pernet_device(&vti_net_ops);
पूर्ण

module_init(vti_init);
module_निकास(vti_fini);
MODULE_LICENSE("GPL");
MODULE_ALIAS_RTNL_LINK("vti");
MODULE_ALIAS_NETDEV("ip_vti0");
