<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Bareudp: UDP  tunnel encasulation क्रम dअगरferent Payload types like
 * MPLS, NSH, IP, etc.
 * Copyright (c) 2019 Nokia, Inc.
 * Authors:  Martin Varghese, <martin.varghese@nokia.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/hash.h>
#समावेश <net/dst_metadata.h>
#समावेश <net/gro_cells.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/protocol.h>
#समावेश <net/ip6_tunnel.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/udp_tunnel.h>
#समावेश <net/bareudp.h>

#घोषणा BAREUDP_BASE_HLEN माप(काष्ठा udphdr)
#घोषणा BAREUDP_IPV4_HLEN (माप(काष्ठा iphdr) + \
			   माप(काष्ठा udphdr))
#घोषणा BAREUDP_IPV6_HLEN (माप(काष्ठा ipv6hdr) + \
			   माप(काष्ठा udphdr))

अटल bool log_ecn_error = true;
module_param(log_ecn_error, bool, 0644);
MODULE_PARM_DESC(log_ecn_error, "Log packets received with corrupted ECN");

/* per-network namespace निजी data क्रम this module */

अटल अचिन्हित पूर्णांक bareudp_net_id;

काष्ठा bareudp_net अणु
	काष्ठा list_head        bareudp_list;
पूर्ण;

/* Pseuकरो network device */
काष्ठा bareudp_dev अणु
	काष्ठा net         *net;        /* netns क्रम packet i/o */
	काष्ठा net_device  *dev;        /* netdev क्रम bareudp tunnel */
	__be16		   ethertype;
	__be16             port;
	u16	           sport_min;
	bool               multi_proto_mode;
	काष्ठा socket      __rcu *sock;
	काष्ठा list_head   next;        /* bareudp node  on namespace list */
	काष्ठा gro_cells   gro_cells;
पूर्ण;

अटल पूर्णांक bareudp_udp_encap_recv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा metadata_dst *tun_dst = शून्य;
	काष्ठा bareudp_dev *bareudp;
	अचिन्हित लघु family;
	अचिन्हित पूर्णांक len;
	__be16 proto;
	व्योम *oiph;
	पूर्णांक err;

	bareudp = rcu_dereference_sk_user_data(sk);
	अगर (!bareudp)
		जाओ drop;

	अगर (skb->protocol ==  htons(ETH_P_IP))
		family = AF_INET;
	अन्यथा
		family = AF_INET6;

	अगर (bareudp->ethertype == htons(ETH_P_IP)) अणु
		काष्ठा iphdr *iphdr;

		iphdr = (काष्ठा iphdr *)(skb->data + BAREUDP_BASE_HLEN);
		अगर (iphdr->version == 4) अणु
			proto = bareudp->ethertype;
		पूर्ण अन्यथा अगर (bareudp->multi_proto_mode && (iphdr->version == 6)) अणु
			proto = htons(ETH_P_IPV6);
		पूर्ण अन्यथा अणु
			bareudp->dev->stats.rx_dropped++;
			जाओ drop;
		पूर्ण
	पूर्ण अन्यथा अगर (bareudp->ethertype == htons(ETH_P_MPLS_UC)) अणु
		काष्ठा iphdr *tunnel_hdr;

		tunnel_hdr = (काष्ठा iphdr *)skb_network_header(skb);
		अगर (tunnel_hdr->version == 4) अणु
			अगर (!ipv4_is_multicast(tunnel_hdr->daddr)) अणु
				proto = bareudp->ethertype;
			पूर्ण अन्यथा अगर (bareudp->multi_proto_mode &&
				   ipv4_is_multicast(tunnel_hdr->daddr)) अणु
				proto = htons(ETH_P_MPLS_MC);
			पूर्ण अन्यथा अणु
				bareudp->dev->stats.rx_dropped++;
				जाओ drop;
			पूर्ण
		पूर्ण अन्यथा अणु
			पूर्णांक addr_type;
			काष्ठा ipv6hdr *tunnel_hdr_v6;

			tunnel_hdr_v6 = (काष्ठा ipv6hdr *)skb_network_header(skb);
			addr_type =
			ipv6_addr_type((काष्ठा in6_addr *)&tunnel_hdr_v6->daddr);
			अगर (!(addr_type & IPV6_ADDR_MULTICAST)) अणु
				proto = bareudp->ethertype;
			पूर्ण अन्यथा अगर (bareudp->multi_proto_mode &&
				   (addr_type & IPV6_ADDR_MULTICAST)) अणु
				proto = htons(ETH_P_MPLS_MC);
			पूर्ण अन्यथा अणु
				bareudp->dev->stats.rx_dropped++;
				जाओ drop;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		proto = bareudp->ethertype;
	पूर्ण

	अगर (iptunnel_pull_header(skb, BAREUDP_BASE_HLEN,
				 proto,
				 !net_eq(bareudp->net,
				 dev_net(bareudp->dev)))) अणु
		bareudp->dev->stats.rx_dropped++;
		जाओ drop;
	पूर्ण
	tun_dst = udp_tun_rx_dst(skb, family, TUNNEL_KEY, 0, 0);
	अगर (!tun_dst) अणु
		bareudp->dev->stats.rx_dropped++;
		जाओ drop;
	पूर्ण
	skb_dst_set(skb, &tun_dst->dst);
	skb->dev = bareudp->dev;
	oiph = skb_network_header(skb);
	skb_reset_network_header(skb);

	अगर (!IS_ENABLED(CONFIG_IPV6) || family == AF_INET)
		err = IP_ECN_decapsulate(oiph, skb);
	अन्यथा
		err = IP6_ECN_decapsulate(oiph, skb);

	अगर (unlikely(err)) अणु
		अगर (log_ecn_error) अणु
			अगर  (!IS_ENABLED(CONFIG_IPV6) || family == AF_INET)
				net_info_ratelimited("non-ECT from %pI4 "
						     "with TOS=%#x\n",
						     &((काष्ठा iphdr *)oiph)->saddr,
						     ((काष्ठा iphdr *)oiph)->tos);
			अन्यथा
				net_info_ratelimited("non-ECT from %pI6\n",
						     &((काष्ठा ipv6hdr *)oiph)->saddr);
		पूर्ण
		अगर (err > 1) अणु
			++bareudp->dev->stats.rx_frame_errors;
			++bareudp->dev->stats.rx_errors;
			जाओ drop;
		पूर्ण
	पूर्ण

	len = skb->len;
	err = gro_cells_receive(&bareudp->gro_cells, skb);
	अगर (likely(err == NET_RX_SUCCESS))
		dev_sw_netstats_rx_add(bareudp->dev, len);

	वापस 0;
drop:
	/* Consume bad packet */
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक bareudp_err_lookup(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक bareudp_init(काष्ठा net_device *dev)
अणु
	काष्ठा bareudp_dev *bareudp = netdev_priv(dev);
	पूर्णांक err;

	dev->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
	अगर (!dev->tstats)
		वापस -ENOMEM;

	err = gro_cells_init(&bareudp->gro_cells, dev);
	अगर (err) अणु
		मुक्त_percpu(dev->tstats);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bareudp_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा bareudp_dev *bareudp = netdev_priv(dev);

	gro_cells_destroy(&bareudp->gro_cells);
	मुक्त_percpu(dev->tstats);
पूर्ण

अटल काष्ठा socket *bareudp_create_sock(काष्ठा net *net, __be16 port)
अणु
	काष्ठा udp_port_cfg udp_conf;
	काष्ठा socket *sock;
	पूर्णांक err;

	स_रखो(&udp_conf, 0, माप(udp_conf));
#अगर IS_ENABLED(CONFIG_IPV6)
	udp_conf.family = AF_INET6;
#अन्यथा
	udp_conf.family = AF_INET;
#पूर्ण_अगर
	udp_conf.local_udp_port = port;
	/* Open UDP socket */
	err = udp_sock_create(net, &udp_conf, &sock);
	अगर (err < 0)
		वापस ERR_PTR(err);

	udp_allow_gso(sock->sk);
	वापस sock;
पूर्ण

/* Create new listen socket अगर needed */
अटल पूर्णांक bareudp_socket_create(काष्ठा bareudp_dev *bareudp, __be16 port)
अणु
	काष्ठा udp_tunnel_sock_cfg tunnel_cfg;
	काष्ठा socket *sock;

	sock = bareudp_create_sock(bareudp->net, port);
	अगर (IS_ERR(sock))
		वापस PTR_ERR(sock);

	/* Mark socket as an encapsulation socket */
	स_रखो(&tunnel_cfg, 0, माप(tunnel_cfg));
	tunnel_cfg.sk_user_data = bareudp;
	tunnel_cfg.encap_type = 1;
	tunnel_cfg.encap_rcv = bareudp_udp_encap_recv;
	tunnel_cfg.encap_err_lookup = bareudp_err_lookup;
	tunnel_cfg.encap_destroy = शून्य;
	setup_udp_tunnel_sock(bareudp->net, sock, &tunnel_cfg);

	rcu_assign_poपूर्णांकer(bareudp->sock, sock);
	वापस 0;
पूर्ण

अटल पूर्णांक bareudp_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा bareudp_dev *bareudp = netdev_priv(dev);
	पूर्णांक ret = 0;

	ret =  bareudp_socket_create(bareudp, bareudp->port);
	वापस ret;
पूर्ण

अटल व्योम bareudp_sock_release(काष्ठा bareudp_dev *bareudp)
अणु
	काष्ठा socket *sock;

	sock = bareudp->sock;
	rcu_assign_poपूर्णांकer(bareudp->sock, शून्य);
	synchronize_net();
	udp_tunnel_sock_release(sock);
पूर्ण

अटल पूर्णांक bareudp_stop(काष्ठा net_device *dev)
अणु
	काष्ठा bareudp_dev *bareudp = netdev_priv(dev);

	bareudp_sock_release(bareudp);
	वापस 0;
पूर्ण

अटल पूर्णांक bareudp_xmit_skb(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			    काष्ठा bareudp_dev *bareudp,
			    स्थिर काष्ठा ip_tunnel_info *info)
अणु
	bool xnet = !net_eq(bareudp->net, dev_net(bareudp->dev));
	bool use_cache = ip_tunnel_dst_cache_usable(skb, info);
	काष्ठा socket *sock = rcu_dereference(bareudp->sock);
	bool udp_sum = !!(info->key.tun_flags & TUNNEL_CSUM);
	स्थिर काष्ठा ip_tunnel_key *key = &info->key;
	काष्ठा rtable *rt;
	__be16 sport, df;
	पूर्णांक min_headroom;
	__u8 tos, ttl;
	__be32 saddr;
	पूर्णांक err;

	अगर (!sock)
		वापस -ESHUTDOWN;

	rt = ip_route_output_tunnel(skb, dev, bareudp->net, &saddr, info,
				    IPPROTO_UDP, use_cache);

	अगर (IS_ERR(rt))
		वापस PTR_ERR(rt);

	skb_tunnel_check_pmtu(skb, &rt->dst,
			      BAREUDP_IPV4_HLEN + info->options_len, false);

	sport = udp_flow_src_port(bareudp->net, skb,
				  bareudp->sport_min, अच_लघु_उच्च,
				  true);
	tos = ip_tunnel_ecn_encap(key->tos, ip_hdr(skb), skb);
	ttl = key->ttl;
	df = key->tun_flags & TUNNEL_DONT_FRAGMENT ? htons(IP_DF) : 0;
	skb_scrub_packet(skb, xnet);

	err = -ENOSPC;
	अगर (!skb_pull(skb, skb_network_offset(skb)))
		जाओ मुक्त_dst;

	min_headroom = LL_RESERVED_SPACE(rt->dst.dev) + rt->dst.header_len +
		BAREUDP_BASE_HLEN + info->options_len + माप(काष्ठा iphdr);

	err = skb_cow_head(skb, min_headroom);
	अगर (unlikely(err))
		जाओ मुक्त_dst;

	err = udp_tunnel_handle_offloads(skb, udp_sum);
	अगर (err)
		जाओ मुक्त_dst;

	skb_set_inner_protocol(skb, bareudp->ethertype);
	udp_tunnel_xmit_skb(rt, sock->sk, skb, saddr, info->key.u.ipv4.dst,
			    tos, ttl, df, sport, bareudp->port,
			    !net_eq(bareudp->net, dev_net(bareudp->dev)),
			    !(info->key.tun_flags & TUNNEL_CSUM));
	वापस 0;

मुक्त_dst:
	dst_release(&rt->dst);
	वापस err;
पूर्ण

अटल पूर्णांक bareudp6_xmit_skb(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			     काष्ठा bareudp_dev *bareudp,
			     स्थिर काष्ठा ip_tunnel_info *info)
अणु
	bool xnet = !net_eq(bareudp->net, dev_net(bareudp->dev));
	bool use_cache = ip_tunnel_dst_cache_usable(skb, info);
	काष्ठा socket *sock  = rcu_dereference(bareudp->sock);
	bool udp_sum = !!(info->key.tun_flags & TUNNEL_CSUM);
	स्थिर काष्ठा ip_tunnel_key *key = &info->key;
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा in6_addr saddr, daddr;
	पूर्णांक min_headroom;
	__u8 prio, ttl;
	__be16 sport;
	पूर्णांक err;

	अगर (!sock)
		वापस -ESHUTDOWN;

	dst = ip6_dst_lookup_tunnel(skb, dev, bareudp->net, sock, &saddr, info,
				    IPPROTO_UDP, use_cache);
	अगर (IS_ERR(dst))
		वापस PTR_ERR(dst);

	skb_tunnel_check_pmtu(skb, dst, BAREUDP_IPV6_HLEN + info->options_len,
			      false);

	sport = udp_flow_src_port(bareudp->net, skb,
				  bareudp->sport_min, अच_लघु_उच्च,
				  true);
	prio = ip_tunnel_ecn_encap(key->tos, ip_hdr(skb), skb);
	ttl = key->ttl;

	skb_scrub_packet(skb, xnet);

	err = -ENOSPC;
	अगर (!skb_pull(skb, skb_network_offset(skb)))
		जाओ मुक्त_dst;

	min_headroom = LL_RESERVED_SPACE(dst->dev) + dst->header_len +
		BAREUDP_BASE_HLEN + info->options_len + माप(काष्ठा ipv6hdr);

	err = skb_cow_head(skb, min_headroom);
	अगर (unlikely(err))
		जाओ मुक्त_dst;

	err = udp_tunnel_handle_offloads(skb, udp_sum);
	अगर (err)
		जाओ मुक्त_dst;

	daddr = info->key.u.ipv6.dst;
	udp_tunnel6_xmit_skb(dst, sock->sk, skb, dev,
			     &saddr, &daddr, prio, ttl,
			     info->key.label, sport, bareudp->port,
			     !(info->key.tun_flags & TUNNEL_CSUM));
	वापस 0;

मुक्त_dst:
	dst_release(dst);
	वापस err;
पूर्ण

अटल bool bareudp_proto_valid(काष्ठा bareudp_dev *bareudp, __be16 proto)
अणु
	अगर (bareudp->ethertype == proto)
		वापस true;

	अगर (!bareudp->multi_proto_mode)
		वापस false;

	अगर (bareudp->ethertype == htons(ETH_P_MPLS_UC) &&
	    proto == htons(ETH_P_MPLS_MC))
		वापस true;

	अगर (bareudp->ethertype == htons(ETH_P_IP) &&
	    proto == htons(ETH_P_IPV6))
		वापस true;

	वापस false;
पूर्ण

अटल netdev_tx_t bareudp_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा bareudp_dev *bareudp = netdev_priv(dev);
	काष्ठा ip_tunnel_info *info = शून्य;
	पूर्णांक err;

	अगर (!bareudp_proto_valid(bareudp, skb->protocol)) अणु
		err = -EINVAL;
		जाओ tx_error;
	पूर्ण

	info = skb_tunnel_info(skb);
	अगर (unlikely(!info || !(info->mode & IP_TUNNEL_INFO_TX))) अणु
		err = -EINVAL;
		जाओ tx_error;
	पूर्ण

	rcu_पढ़ो_lock();
	अगर (IS_ENABLED(CONFIG_IPV6) && info->mode & IP_TUNNEL_INFO_IPV6)
		err = bareudp6_xmit_skb(skb, dev, bareudp, info);
	अन्यथा
		err = bareudp_xmit_skb(skb, dev, bareudp, info);

	rcu_पढ़ो_unlock();

	अगर (likely(!err))
		वापस NETDEV_TX_OK;
tx_error:
	dev_kमुक्त_skb(skb);

	अगर (err == -ELOOP)
		dev->stats.collisions++;
	अन्यथा अगर (err == -ENETUNREACH)
		dev->stats.tx_carrier_errors++;

	dev->stats.tx_errors++;
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक bareudp_fill_metadata_dst(काष्ठा net_device *dev,
				     काष्ठा sk_buff *skb)
अणु
	काष्ठा ip_tunnel_info *info = skb_tunnel_info(skb);
	काष्ठा bareudp_dev *bareudp = netdev_priv(dev);
	bool use_cache;

	use_cache = ip_tunnel_dst_cache_usable(skb, info);

	अगर (!IS_ENABLED(CONFIG_IPV6) || ip_tunnel_info_af(info) == AF_INET) अणु
		काष्ठा rtable *rt;
		__be32 saddr;

		rt = ip_route_output_tunnel(skb, dev, bareudp->net, &saddr,
					    info, IPPROTO_UDP, use_cache);
		अगर (IS_ERR(rt))
			वापस PTR_ERR(rt);

		ip_rt_put(rt);
		info->key.u.ipv4.src = saddr;
	पूर्ण अन्यथा अगर (ip_tunnel_info_af(info) == AF_INET6) अणु
		काष्ठा dst_entry *dst;
		काष्ठा in6_addr saddr;
		काष्ठा socket *sock = rcu_dereference(bareudp->sock);

		dst = ip6_dst_lookup_tunnel(skb, dev, bareudp->net, sock,
					    &saddr, info, IPPROTO_UDP,
					    use_cache);
		अगर (IS_ERR(dst))
			वापस PTR_ERR(dst);

		dst_release(dst);
		info->key.u.ipv6.src = saddr;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	info->key.tp_src = udp_flow_src_port(bareudp->net, skb,
					     bareudp->sport_min,
			अच_लघु_उच्च, true);
	info->key.tp_dst = bareudp->port;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops bareudp_netdev_ops = अणु
	.nकरो_init               = bareudp_init,
	.nकरो_uninit             = bareudp_uninit,
	.nकरो_खोलो               = bareudp_खोलो,
	.nकरो_stop               = bareudp_stop,
	.nकरो_start_xmit         = bareudp_xmit,
	.nकरो_get_stats64        = dev_get_tstats64,
	.nकरो_fill_metadata_dst  = bareudp_fill_metadata_dst,
पूर्ण;

अटल स्थिर काष्ठा nla_policy bareudp_policy[IFLA_BAREUDP_MAX + 1] = अणु
	[IFLA_BAREUDP_PORT]                = अणु .type = NLA_U16 पूर्ण,
	[IFLA_BAREUDP_ETHERTYPE]	   = अणु .type = NLA_U16 पूर्ण,
	[IFLA_BAREUDP_SRCPORT_MIN]         = अणु .type = NLA_U16 पूर्ण,
	[IFLA_BAREUDP_MULTIPROTO_MODE]     = अणु .type = NLA_FLAG पूर्ण,
पूर्ण;

/* Info क्रम udev, that this is a भव tunnel endpoपूर्णांक */
अटल स्थिर काष्ठा device_type bareudp_type = अणु
	.name = "bareudp",
पूर्ण;

/* Initialize the device काष्ठाure. */
अटल व्योम bareudp_setup(काष्ठा net_device *dev)
अणु
	dev->netdev_ops = &bareudp_netdev_ops;
	dev->needs_मुक्त_netdev = true;
	SET_NETDEV_DEVTYPE(dev, &bareudp_type);
	dev->features    |= NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_FRAGLIST;
	dev->features    |= NETIF_F_RXCSUM;
	dev->features    |= NETIF_F_LLTX;
	dev->features    |= NETIF_F_GSO_SOFTWARE;
	dev->hw_features |= NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_FRAGLIST;
	dev->hw_features |= NETIF_F_RXCSUM;
	dev->hw_features |= NETIF_F_GSO_SOFTWARE;
	dev->hard_header_len = 0;
	dev->addr_len = 0;
	dev->mtu = ETH_DATA_LEN;
	dev->min_mtu = IPV4_MIN_MTU;
	dev->max_mtu = IP_MAX_MTU - BAREUDP_BASE_HLEN;
	dev->type = ARPHRD_NONE;
	netअगर_keep_dst(dev);
	dev->priv_flags |= IFF_NO_QUEUE;
	dev->flags = IFF_POINTOPOINT | IFF_NOARP | IFF_MULTICAST;
पूर्ण

अटल पूर्णांक bareudp_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			    काष्ठा netlink_ext_ack *extack)
अणु
	अगर (!data) अणु
		NL_SET_ERR_MSG(extack,
			       "Not enough attributes provided to perform the operation");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bareudp2info(काष्ठा nlattr *data[], काष्ठा bareudp_conf *conf,
			काष्ठा netlink_ext_ack *extack)
अणु
	स_रखो(conf, 0, माप(*conf));

	अगर (!data[IFLA_BAREUDP_PORT]) अणु
		NL_SET_ERR_MSG(extack, "port not specified");
		वापस -EINVAL;
	पूर्ण
	अगर (!data[IFLA_BAREUDP_ETHERTYPE]) अणु
		NL_SET_ERR_MSG(extack, "ethertype not specified");
		वापस -EINVAL;
	पूर्ण

	अगर (data[IFLA_BAREUDP_PORT])
		conf->port =  nla_get_u16(data[IFLA_BAREUDP_PORT]);

	अगर (data[IFLA_BAREUDP_ETHERTYPE])
		conf->ethertype =  nla_get_u16(data[IFLA_BAREUDP_ETHERTYPE]);

	अगर (data[IFLA_BAREUDP_SRCPORT_MIN])
		conf->sport_min =  nla_get_u16(data[IFLA_BAREUDP_SRCPORT_MIN]);

	अगर (data[IFLA_BAREUDP_MULTIPROTO_MODE])
		conf->multi_proto_mode = true;

	वापस 0;
पूर्ण

अटल काष्ठा bareudp_dev *bareudp_find_dev(काष्ठा bareudp_net *bn,
					    स्थिर काष्ठा bareudp_conf *conf)
अणु
	काष्ठा bareudp_dev *bareudp, *t = शून्य;

	list_क्रम_each_entry(bareudp, &bn->bareudp_list, next) अणु
		अगर (conf->port == bareudp->port)
			t = bareudp;
	पूर्ण
	वापस t;
पूर्ण

अटल पूर्णांक bareudp_configure(काष्ठा net *net, काष्ठा net_device *dev,
			     काष्ठा bareudp_conf *conf)
अणु
	काष्ठा bareudp_net *bn = net_generic(net, bareudp_net_id);
	काष्ठा bareudp_dev *t, *bareudp = netdev_priv(dev);
	पूर्णांक err;

	bareudp->net = net;
	bareudp->dev = dev;
	t = bareudp_find_dev(bn, conf);
	अगर (t)
		वापस -EBUSY;

	अगर (conf->multi_proto_mode &&
	    (conf->ethertype != htons(ETH_P_MPLS_UC) &&
	     conf->ethertype != htons(ETH_P_IP)))
		वापस -EINVAL;

	bareudp->port = conf->port;
	bareudp->ethertype = conf->ethertype;
	bareudp->sport_min = conf->sport_min;
	bareudp->multi_proto_mode = conf->multi_proto_mode;

	err = रेजिस्टर_netdevice(dev);
	अगर (err)
		वापस err;

	list_add(&bareudp->next, &bn->bareudp_list);
	वापस 0;
पूर्ण

अटल पूर्णांक bareudp_link_config(काष्ठा net_device *dev,
			       काष्ठा nlattr *tb[])
अणु
	पूर्णांक err;

	अगर (tb[IFLA_MTU]) अणु
		err = dev_set_mtu(dev, nla_get_u32(tb[IFLA_MTU]));
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bareudp_dellink(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	काष्ठा bareudp_dev *bareudp = netdev_priv(dev);

	list_del(&bareudp->next);
	unरेजिस्टर_netdevice_queue(dev, head);
पूर्ण

अटल पूर्णांक bareudp_newlink(काष्ठा net *net, काष्ठा net_device *dev,
			   काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा bareudp_conf conf;
	पूर्णांक err;

	err = bareudp2info(data, &conf, extack);
	अगर (err)
		वापस err;

	err = bareudp_configure(net, dev, &conf);
	अगर (err)
		वापस err;

	err = bareudp_link_config(dev, tb);
	अगर (err)
		जाओ err_unconfig;

	वापस 0;

err_unconfig:
	bareudp_dellink(dev, शून्य);
	वापस err;
पूर्ण

अटल माप_प्रकार bareudp_get_size(स्थिर काष्ठा net_device *dev)
अणु
	वापस  nla_total_size(माप(__be16)) +  /* IFLA_BAREUDP_PORT */
		nla_total_size(माप(__be16)) +  /* IFLA_BAREUDP_ETHERTYPE */
		nla_total_size(माप(__u16))  +  /* IFLA_BAREUDP_SRCPORT_MIN */
		nla_total_size(0)              +  /* IFLA_BAREUDP_MULTIPROTO_MODE */
		0;
पूर्ण

अटल पूर्णांक bareudp_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा bareudp_dev *bareudp = netdev_priv(dev);

	अगर (nla_put_be16(skb, IFLA_BAREUDP_PORT, bareudp->port))
		जाओ nla_put_failure;
	अगर (nla_put_be16(skb, IFLA_BAREUDP_ETHERTYPE, bareudp->ethertype))
		जाओ nla_put_failure;
	अगर (nla_put_u16(skb, IFLA_BAREUDP_SRCPORT_MIN, bareudp->sport_min))
		जाओ nla_put_failure;
	अगर (bareudp->multi_proto_mode &&
	    nla_put_flag(skb, IFLA_BAREUDP_MULTIPROTO_MODE))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल काष्ठा rtnl_link_ops bareudp_link_ops __पढ़ो_mostly = अणु
	.kind           = "bareudp",
	.maxtype        = IFLA_BAREUDP_MAX,
	.policy         = bareudp_policy,
	.priv_size      = माप(काष्ठा bareudp_dev),
	.setup          = bareudp_setup,
	.validate       = bareudp_validate,
	.newlink        = bareudp_newlink,
	.dellink        = bareudp_dellink,
	.get_size       = bareudp_get_size,
	.fill_info      = bareudp_fill_info,
पूर्ण;

काष्ठा net_device *bareudp_dev_create(काष्ठा net *net, स्थिर अक्षर *name,
				      u8 name_assign_type,
				      काष्ठा bareudp_conf *conf)
अणु
	काष्ठा nlattr *tb[IFLA_MAX + 1];
	काष्ठा net_device *dev;
	पूर्णांक err;

	स_रखो(tb, 0, माप(tb));
	dev = rtnl_create_link(net, name, name_assign_type,
			       &bareudp_link_ops, tb, शून्य);
	अगर (IS_ERR(dev))
		वापस dev;

	err = bareudp_configure(net, dev, conf);
	अगर (err) अणु
		मुक्त_netdev(dev);
		वापस ERR_PTR(err);
	पूर्ण
	err = dev_set_mtu(dev, IP_MAX_MTU - BAREUDP_BASE_HLEN);
	अगर (err)
		जाओ err;

	err = rtnl_configure_link(dev, शून्य);
	अगर (err < 0)
		जाओ err;

	वापस dev;
err:
	bareudp_dellink(dev, शून्य);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(bareudp_dev_create);

अटल __net_init पूर्णांक bareudp_init_net(काष्ठा net *net)
अणु
	काष्ठा bareudp_net *bn = net_generic(net, bareudp_net_id);

	INIT_LIST_HEAD(&bn->bareudp_list);
	वापस 0;
पूर्ण

अटल व्योम bareudp_destroy_tunnels(काष्ठा net *net, काष्ठा list_head *head)
अणु
	काष्ठा bareudp_net *bn = net_generic(net, bareudp_net_id);
	काष्ठा bareudp_dev *bareudp, *next;

	list_क्रम_each_entry_safe(bareudp, next, &bn->bareudp_list, next)
		unरेजिस्टर_netdevice_queue(bareudp->dev, head);
पूर्ण

अटल व्योम __net_निकास bareudp_निकास_batch_net(काष्ठा list_head *net_list)
अणु
	काष्ठा net *net;
	LIST_HEAD(list);

	rtnl_lock();
	list_क्रम_each_entry(net, net_list, निकास_list)
		bareudp_destroy_tunnels(net, &list);

	/* unरेजिस्टर the devices gathered above */
	unरेजिस्टर_netdevice_many(&list);
	rtnl_unlock();
पूर्ण

अटल काष्ठा pernet_operations bareudp_net_ops = अणु
	.init = bareudp_init_net,
	.निकास_batch = bareudp_निकास_batch_net,
	.id   = &bareudp_net_id,
	.size = माप(काष्ठा bareudp_net),
पूर्ण;

अटल पूर्णांक __init bareudp_init_module(व्योम)
अणु
	पूर्णांक rc;

	rc = रेजिस्टर_pernet_subsys(&bareudp_net_ops);
	अगर (rc)
		जाओ out1;

	rc = rtnl_link_रेजिस्टर(&bareudp_link_ops);
	अगर (rc)
		जाओ out2;

	वापस 0;
out2:
	unरेजिस्टर_pernet_subsys(&bareudp_net_ops);
out1:
	वापस rc;
पूर्ण
late_initcall(bareudp_init_module);

अटल व्योम __निकास bareudp_cleanup_module(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&bareudp_link_ops);
	unरेजिस्टर_pernet_subsys(&bareudp_net_ops);
पूर्ण
module_निकास(bareudp_cleanup_module);

MODULE_ALIAS_RTNL_LINK("bareudp");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Martin Varghese <martin.varghese@nokia.com>");
MODULE_DESCRIPTION("Interface driver for UDP encapsulated traffic");
