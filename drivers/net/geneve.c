<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GENEVE: Generic Network Virtualization Encapsulation
 *
 * Copyright (c) 2015 Red Hat, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/ethtool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/hash.h>
#समावेश <net/ipv6_stubs.h>
#समावेश <net/dst_metadata.h>
#समावेश <net/gro_cells.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/geneve.h>
#समावेश <net/protocol.h>

#घोषणा GENEVE_NETDEV_VER	"0.6"

#घोषणा GENEVE_N_VID		(1u << 24)
#घोषणा GENEVE_VID_MASK		(GENEVE_N_VID - 1)

#घोषणा VNI_HASH_BITS		10
#घोषणा VNI_HASH_SIZE		(1<<VNI_HASH_BITS)

अटल bool log_ecn_error = true;
module_param(log_ecn_error, bool, 0644);
MODULE_PARM_DESC(log_ecn_error, "Log packets received with corrupted ECN");

#घोषणा GENEVE_VER 0
#घोषणा GENEVE_BASE_HLEN (माप(काष्ठा udphdr) + माप(काष्ठा genevehdr))
#घोषणा GENEVE_IPV4_HLEN (ETH_HLEN + माप(काष्ठा iphdr) + GENEVE_BASE_HLEN)
#घोषणा GENEVE_IPV6_HLEN (ETH_HLEN + माप(काष्ठा ipv6hdr) + GENEVE_BASE_HLEN)

/* per-network namespace निजी data क्रम this module */
काष्ठा geneve_net अणु
	काष्ठा list_head	geneve_list;
	काष्ठा list_head	sock_list;
पूर्ण;

अटल अचिन्हित पूर्णांक geneve_net_id;

काष्ठा geneve_dev_node अणु
	काष्ठा hlist_node hlist;
	काष्ठा geneve_dev *geneve;
पूर्ण;

काष्ठा geneve_config अणु
	काष्ठा ip_tunnel_info	info;
	bool			collect_md;
	bool			use_udp6_rx_checksums;
	bool			ttl_inherit;
	क्रमागत अगरla_geneve_df	df;
पूर्ण;

/* Pseuकरो network device */
काष्ठा geneve_dev अणु
	काष्ठा geneve_dev_node hlist4;	/* vni hash table क्रम IPv4 socket */
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा geneve_dev_node hlist6;	/* vni hash table क्रम IPv6 socket */
#पूर्ण_अगर
	काष्ठा net	   *net;	/* netns क्रम packet i/o */
	काष्ठा net_device  *dev;	/* netdev क्रम geneve tunnel */
	काष्ठा geneve_sock __rcu *sock4;	/* IPv4 socket used क्रम geneve tunnel */
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा geneve_sock __rcu *sock6;	/* IPv6 socket used क्रम geneve tunnel */
#पूर्ण_अगर
	काष्ठा list_head   next;	/* geneve's per namespace list */
	काष्ठा gro_cells   gro_cells;
	काष्ठा geneve_config cfg;
पूर्ण;

काष्ठा geneve_sock अणु
	bool			collect_md;
	काष्ठा list_head	list;
	काष्ठा socket		*sock;
	काष्ठा rcu_head		rcu;
	पूर्णांक			refcnt;
	काष्ठा hlist_head	vni_list[VNI_HASH_SIZE];
पूर्ण;

अटल अंतरभूत __u32 geneve_net_vni_hash(u8 vni[3])
अणु
	__u32 vnid;

	vnid = (vni[0] << 16) | (vni[1] << 8) | vni[2];
	वापस hash_32(vnid, VNI_HASH_BITS);
पूर्ण

अटल __be64 vni_to_tunnel_id(स्थिर __u8 *vni)
अणु
#अगर_घोषित __BIG_ENDIAN
	वापस (vni[0] << 16) | (vni[1] << 8) | vni[2];
#अन्यथा
	वापस (__क्रमce __be64)(((__क्रमce u64)vni[0] << 40) |
				((__क्रमce u64)vni[1] << 48) |
				((__क्रमce u64)vni[2] << 56));
#पूर्ण_अगर
पूर्ण

/* Convert 64 bit tunnel ID to 24 bit VNI. */
अटल व्योम tunnel_id_to_vni(__be64 tun_id, __u8 *vni)
अणु
#अगर_घोषित __BIG_ENDIAN
	vni[0] = (__क्रमce __u8)(tun_id >> 16);
	vni[1] = (__क्रमce __u8)(tun_id >> 8);
	vni[2] = (__क्रमce __u8)tun_id;
#अन्यथा
	vni[0] = (__क्रमce __u8)((__क्रमce u64)tun_id >> 40);
	vni[1] = (__क्रमce __u8)((__क्रमce u64)tun_id >> 48);
	vni[2] = (__क्रमce __u8)((__क्रमce u64)tun_id >> 56);
#पूर्ण_अगर
पूर्ण

अटल bool eq_tun_id_and_vni(u8 *tun_id, u8 *vni)
अणु
	वापस !स_भेद(vni, &tun_id[5], 3);
पूर्ण

अटल sa_family_t geneve_get_sk_family(काष्ठा geneve_sock *gs)
अणु
	वापस gs->sock->sk->sk_family;
पूर्ण

अटल काष्ठा geneve_dev *geneve_lookup(काष्ठा geneve_sock *gs,
					__be32 addr, u8 vni[])
अणु
	काष्ठा hlist_head *vni_list_head;
	काष्ठा geneve_dev_node *node;
	__u32 hash;

	/* Find the device क्रम this VNI */
	hash = geneve_net_vni_hash(vni);
	vni_list_head = &gs->vni_list[hash];
	hlist_क्रम_each_entry_rcu(node, vni_list_head, hlist) अणु
		अगर (eq_tun_id_and_vni((u8 *)&node->geneve->cfg.info.key.tun_id, vni) &&
		    addr == node->geneve->cfg.info.key.u.ipv4.dst)
			वापस node->geneve;
	पूर्ण
	वापस शून्य;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल काष्ठा geneve_dev *geneve6_lookup(काष्ठा geneve_sock *gs,
					 काष्ठा in6_addr addr6, u8 vni[])
अणु
	काष्ठा hlist_head *vni_list_head;
	काष्ठा geneve_dev_node *node;
	__u32 hash;

	/* Find the device क्रम this VNI */
	hash = geneve_net_vni_hash(vni);
	vni_list_head = &gs->vni_list[hash];
	hlist_क्रम_each_entry_rcu(node, vni_list_head, hlist) अणु
		अगर (eq_tun_id_and_vni((u8 *)&node->geneve->cfg.info.key.tun_id, vni) &&
		    ipv6_addr_equal(&addr6, &node->geneve->cfg.info.key.u.ipv6.dst))
			वापस node->geneve;
	पूर्ण
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा genevehdr *geneve_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा genevehdr *)(udp_hdr(skb) + 1);
पूर्ण

अटल काष्ठा geneve_dev *geneve_lookup_skb(काष्ठा geneve_sock *gs,
					    काष्ठा sk_buff *skb)
अणु
	अटल u8 zero_vni[3];
	u8 *vni;

	अगर (geneve_get_sk_family(gs) == AF_INET) अणु
		काष्ठा iphdr *iph;
		__be32 addr;

		iph = ip_hdr(skb); /* outer IP header... */

		अगर (gs->collect_md) अणु
			vni = zero_vni;
			addr = 0;
		पूर्ण अन्यथा अणु
			vni = geneve_hdr(skb)->vni;
			addr = iph->saddr;
		पूर्ण

		वापस geneve_lookup(gs, addr, vni);
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (geneve_get_sk_family(gs) == AF_INET6) अणु
		अटल काष्ठा in6_addr zero_addr6;
		काष्ठा ipv6hdr *ip6h;
		काष्ठा in6_addr addr6;

		ip6h = ipv6_hdr(skb); /* outer IPv6 header... */

		अगर (gs->collect_md) अणु
			vni = zero_vni;
			addr6 = zero_addr6;
		पूर्ण अन्यथा अणु
			vni = geneve_hdr(skb)->vni;
			addr6 = ip6h->saddr;
		पूर्ण

		वापस geneve6_lookup(gs, addr6, vni);
#पूर्ण_अगर
	पूर्ण
	वापस शून्य;
पूर्ण

/* geneve receive/decap routine */
अटल व्योम geneve_rx(काष्ठा geneve_dev *geneve, काष्ठा geneve_sock *gs,
		      काष्ठा sk_buff *skb)
अणु
	काष्ठा genevehdr *gnvh = geneve_hdr(skb);
	काष्ठा metadata_dst *tun_dst = शून्य;
	अचिन्हित पूर्णांक len;
	पूर्णांक err = 0;
	व्योम *oiph;

	अगर (ip_tunnel_collect_metadata() || gs->collect_md) अणु
		__be16 flags;

		flags = TUNNEL_KEY | (gnvh->oam ? TUNNEL_OAM : 0) |
			(gnvh->critical ? TUNNEL_CRIT_OPT : 0);

		tun_dst = udp_tun_rx_dst(skb, geneve_get_sk_family(gs), flags,
					 vni_to_tunnel_id(gnvh->vni),
					 gnvh->opt_len * 4);
		अगर (!tun_dst) अणु
			geneve->dev->stats.rx_dropped++;
			जाओ drop;
		पूर्ण
		/* Update tunnel dst according to Geneve options. */
		ip_tunnel_info_opts_set(&tun_dst->u.tun_info,
					gnvh->options, gnvh->opt_len * 4,
					TUNNEL_GENEVE_OPT);
	पूर्ण अन्यथा अणु
		/* Drop packets w/ critical options,
		 * since we करोn't support any...
		 */
		अगर (gnvh->critical) अणु
			geneve->dev->stats.rx_frame_errors++;
			geneve->dev->stats.rx_errors++;
			जाओ drop;
		पूर्ण
	पूर्ण

	skb_reset_mac_header(skb);
	skb->protocol = eth_type_trans(skb, geneve->dev);
	skb_postpull_rcsum(skb, eth_hdr(skb), ETH_HLEN);

	अगर (tun_dst)
		skb_dst_set(skb, &tun_dst->dst);

	/* Ignore packet loops (and multicast echo) */
	अगर (ether_addr_equal(eth_hdr(skb)->h_source, geneve->dev->dev_addr)) अणु
		geneve->dev->stats.rx_errors++;
		जाओ drop;
	पूर्ण

	oiph = skb_network_header(skb);
	skb_reset_network_header(skb);

	अगर (geneve_get_sk_family(gs) == AF_INET)
		err = IP_ECN_decapsulate(oiph, skb);
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा
		err = IP6_ECN_decapsulate(oiph, skb);
#पूर्ण_अगर

	अगर (unlikely(err)) अणु
		अगर (log_ecn_error) अणु
			अगर (geneve_get_sk_family(gs) == AF_INET)
				net_info_ratelimited("non-ECT from %pI4 "
						     "with TOS=%#x\n",
						     &((काष्ठा iphdr *)oiph)->saddr,
						     ((काष्ठा iphdr *)oiph)->tos);
#अगर IS_ENABLED(CONFIG_IPV6)
			अन्यथा
				net_info_ratelimited("non-ECT from %pI6\n",
						     &((काष्ठा ipv6hdr *)oiph)->saddr);
#पूर्ण_अगर
		पूर्ण
		अगर (err > 1) अणु
			++geneve->dev->stats.rx_frame_errors;
			++geneve->dev->stats.rx_errors;
			जाओ drop;
		पूर्ण
	पूर्ण

	len = skb->len;
	err = gro_cells_receive(&geneve->gro_cells, skb);
	अगर (likely(err == NET_RX_SUCCESS))
		dev_sw_netstats_rx_add(geneve->dev, len);

	वापस;
drop:
	/* Consume bad packet */
	kमुक्त_skb(skb);
पूर्ण

/* Setup stats when device is created */
अटल पूर्णांक geneve_init(काष्ठा net_device *dev)
अणु
	काष्ठा geneve_dev *geneve = netdev_priv(dev);
	पूर्णांक err;

	dev->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
	अगर (!dev->tstats)
		वापस -ENOMEM;

	err = gro_cells_init(&geneve->gro_cells, dev);
	अगर (err) अणु
		मुक्त_percpu(dev->tstats);
		वापस err;
	पूर्ण

	err = dst_cache_init(&geneve->cfg.info.dst_cache, GFP_KERNEL);
	अगर (err) अणु
		मुक्त_percpu(dev->tstats);
		gro_cells_destroy(&geneve->gro_cells);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम geneve_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा geneve_dev *geneve = netdev_priv(dev);

	dst_cache_destroy(&geneve->cfg.info.dst_cache);
	gro_cells_destroy(&geneve->gro_cells);
	मुक्त_percpu(dev->tstats);
पूर्ण

/* Callback from net/ipv4/udp.c to receive packets */
अटल पूर्णांक geneve_udp_encap_recv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा genevehdr *geneveh;
	काष्ठा geneve_dev *geneve;
	काष्ठा geneve_sock *gs;
	पूर्णांक opts_len;

	/* Need UDP and Geneve header to be present */
	अगर (unlikely(!pskb_may_pull(skb, GENEVE_BASE_HLEN)))
		जाओ drop;

	/* Return packets with reserved bits set */
	geneveh = geneve_hdr(skb);
	अगर (unlikely(geneveh->ver != GENEVE_VER))
		जाओ drop;

	अगर (unlikely(geneveh->proto_type != htons(ETH_P_TEB)))
		जाओ drop;

	gs = rcu_dereference_sk_user_data(sk);
	अगर (!gs)
		जाओ drop;

	geneve = geneve_lookup_skb(gs, skb);
	अगर (!geneve)
		जाओ drop;

	opts_len = geneveh->opt_len * 4;
	अगर (iptunnel_pull_header(skb, GENEVE_BASE_HLEN + opts_len,
				 htons(ETH_P_TEB),
				 !net_eq(geneve->net, dev_net(geneve->dev)))) अणु
		geneve->dev->stats.rx_dropped++;
		जाओ drop;
	पूर्ण

	geneve_rx(geneve, gs, skb);
	वापस 0;

drop:
	/* Consume bad packet */
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

/* Callback from net/ipvअणु4,6पूर्ण/udp.c to check that we have a tunnel क्रम errors */
अटल पूर्णांक geneve_udp_encap_err_lookup(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा genevehdr *geneveh;
	काष्ठा geneve_sock *gs;
	u8 zero_vni[3] = अणु 0 पूर्ण;
	u8 *vni = zero_vni;

	अगर (!pskb_may_pull(skb, skb_transport_offset(skb) + GENEVE_BASE_HLEN))
		वापस -EINVAL;

	geneveh = geneve_hdr(skb);
	अगर (geneveh->ver != GENEVE_VER)
		वापस -EINVAL;

	अगर (geneveh->proto_type != htons(ETH_P_TEB))
		वापस -EINVAL;

	gs = rcu_dereference_sk_user_data(sk);
	अगर (!gs)
		वापस -ENOENT;

	अगर (geneve_get_sk_family(gs) == AF_INET) अणु
		काष्ठा iphdr *iph = ip_hdr(skb);
		__be32 addr4 = 0;

		अगर (!gs->collect_md) अणु
			vni = geneve_hdr(skb)->vni;
			addr4 = iph->daddr;
		पूर्ण

		वापस geneve_lookup(gs, addr4, vni) ? 0 : -ENOENT;
	पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (geneve_get_sk_family(gs) == AF_INET6) अणु
		काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);
		काष्ठा in6_addr addr6;

		स_रखो(&addr6, 0, माप(काष्ठा in6_addr));

		अगर (!gs->collect_md) अणु
			vni = geneve_hdr(skb)->vni;
			addr6 = ip6h->daddr;
		पूर्ण

		वापस geneve6_lookup(gs, addr6, vni) ? 0 : -ENOENT;
	पूर्ण
#पूर्ण_अगर

	वापस -EPFNOSUPPORT;
पूर्ण

अटल काष्ठा socket *geneve_create_sock(काष्ठा net *net, bool ipv6,
					 __be16 port, bool ipv6_rx_csum)
अणु
	काष्ठा socket *sock;
	काष्ठा udp_port_cfg udp_conf;
	पूर्णांक err;

	स_रखो(&udp_conf, 0, माप(udp_conf));

	अगर (ipv6) अणु
		udp_conf.family = AF_INET6;
		udp_conf.ipv6_v6only = 1;
		udp_conf.use_udp6_rx_checksums = ipv6_rx_csum;
	पूर्ण अन्यथा अणु
		udp_conf.family = AF_INET;
		udp_conf.local_ip.s_addr = htonl(INADDR_ANY);
	पूर्ण

	udp_conf.local_udp_port = port;

	/* Open UDP socket */
	err = udp_sock_create(net, &udp_conf, &sock);
	अगर (err < 0)
		वापस ERR_PTR(err);

	udp_allow_gso(sock->sk);
	वापस sock;
पूर्ण

अटल पूर्णांक geneve_hlen(काष्ठा genevehdr *gh)
अणु
	वापस माप(*gh) + gh->opt_len * 4;
पूर्ण

अटल काष्ठा sk_buff *geneve_gro_receive(काष्ठा sock *sk,
					  काष्ठा list_head *head,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *pp = शून्य;
	काष्ठा sk_buff *p;
	काष्ठा genevehdr *gh, *gh2;
	अचिन्हित पूर्णांक hlen, gh_len, off_gnv;
	स्थिर काष्ठा packet_offload *ptype;
	__be16 type;
	पूर्णांक flush = 1;

	off_gnv = skb_gro_offset(skb);
	hlen = off_gnv + माप(*gh);
	gh = skb_gro_header_fast(skb, off_gnv);
	अगर (skb_gro_header_hard(skb, hlen)) अणु
		gh = skb_gro_header_slow(skb, hlen, off_gnv);
		अगर (unlikely(!gh))
			जाओ out;
	पूर्ण

	अगर (gh->ver != GENEVE_VER || gh->oam)
		जाओ out;
	gh_len = geneve_hlen(gh);

	hlen = off_gnv + gh_len;
	अगर (skb_gro_header_hard(skb, hlen)) अणु
		gh = skb_gro_header_slow(skb, hlen, off_gnv);
		अगर (unlikely(!gh))
			जाओ out;
	पूर्ण

	list_क्रम_each_entry(p, head, list) अणु
		अगर (!NAPI_GRO_CB(p)->same_flow)
			जारी;

		gh2 = (काष्ठा genevehdr *)(p->data + off_gnv);
		अगर (gh->opt_len != gh2->opt_len ||
		    स_भेद(gh, gh2, gh_len)) अणु
			NAPI_GRO_CB(p)->same_flow = 0;
			जारी;
		पूर्ण
	पूर्ण

	type = gh->proto_type;

	rcu_पढ़ो_lock();
	ptype = gro_find_receive_by_type(type);
	अगर (!ptype)
		जाओ out_unlock;

	skb_gro_pull(skb, gh_len);
	skb_gro_postpull_rcsum(skb, gh, gh_len);
	pp = call_gro_receive(ptype->callbacks.gro_receive, head, skb);
	flush = 0;

out_unlock:
	rcu_पढ़ो_unlock();
out:
	skb_gro_flush_final(skb, pp, flush);

	वापस pp;
पूर्ण

अटल पूर्णांक geneve_gro_complete(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			       पूर्णांक nhoff)
अणु
	काष्ठा genevehdr *gh;
	काष्ठा packet_offload *ptype;
	__be16 type;
	पूर्णांक gh_len;
	पूर्णांक err = -ENOSYS;

	gh = (काष्ठा genevehdr *)(skb->data + nhoff);
	gh_len = geneve_hlen(gh);
	type = gh->proto_type;

	rcu_पढ़ो_lock();
	ptype = gro_find_complete_by_type(type);
	अगर (ptype)
		err = ptype->callbacks.gro_complete(skb, nhoff + gh_len);

	rcu_पढ़ो_unlock();

	skb_set_inner_mac_header(skb, nhoff + gh_len);

	वापस err;
पूर्ण

/* Create new listen socket अगर needed */
अटल काष्ठा geneve_sock *geneve_socket_create(काष्ठा net *net, __be16 port,
						bool ipv6, bool ipv6_rx_csum)
अणु
	काष्ठा geneve_net *gn = net_generic(net, geneve_net_id);
	काष्ठा geneve_sock *gs;
	काष्ठा socket *sock;
	काष्ठा udp_tunnel_sock_cfg tunnel_cfg;
	पूर्णांक h;

	gs = kzalloc(माप(*gs), GFP_KERNEL);
	अगर (!gs)
		वापस ERR_PTR(-ENOMEM);

	sock = geneve_create_sock(net, ipv6, port, ipv6_rx_csum);
	अगर (IS_ERR(sock)) अणु
		kमुक्त(gs);
		वापस ERR_CAST(sock);
	पूर्ण

	gs->sock = sock;
	gs->refcnt = 1;
	क्रम (h = 0; h < VNI_HASH_SIZE; ++h)
		INIT_HLIST_HEAD(&gs->vni_list[h]);

	/* Initialize the geneve udp offloads काष्ठाure */
	udp_tunnel_notअगरy_add_rx_port(gs->sock, UDP_TUNNEL_TYPE_GENEVE);

	/* Mark socket as an encapsulation socket */
	स_रखो(&tunnel_cfg, 0, माप(tunnel_cfg));
	tunnel_cfg.sk_user_data = gs;
	tunnel_cfg.encap_type = 1;
	tunnel_cfg.gro_receive = geneve_gro_receive;
	tunnel_cfg.gro_complete = geneve_gro_complete;
	tunnel_cfg.encap_rcv = geneve_udp_encap_recv;
	tunnel_cfg.encap_err_lookup = geneve_udp_encap_err_lookup;
	tunnel_cfg.encap_destroy = शून्य;
	setup_udp_tunnel_sock(net, sock, &tunnel_cfg);
	list_add(&gs->list, &gn->sock_list);
	वापस gs;
पूर्ण

अटल व्योम __geneve_sock_release(काष्ठा geneve_sock *gs)
अणु
	अगर (!gs || --gs->refcnt)
		वापस;

	list_del(&gs->list);
	udp_tunnel_notअगरy_del_rx_port(gs->sock, UDP_TUNNEL_TYPE_GENEVE);
	udp_tunnel_sock_release(gs->sock);
	kमुक्त_rcu(gs, rcu);
पूर्ण

अटल व्योम geneve_sock_release(काष्ठा geneve_dev *geneve)
अणु
	काष्ठा geneve_sock *gs4 = rtnl_dereference(geneve->sock4);
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा geneve_sock *gs6 = rtnl_dereference(geneve->sock6);

	rcu_assign_poपूर्णांकer(geneve->sock6, शून्य);
#पूर्ण_अगर

	rcu_assign_poपूर्णांकer(geneve->sock4, शून्य);
	synchronize_net();

	__geneve_sock_release(gs4);
#अगर IS_ENABLED(CONFIG_IPV6)
	__geneve_sock_release(gs6);
#पूर्ण_अगर
पूर्ण

अटल काष्ठा geneve_sock *geneve_find_sock(काष्ठा geneve_net *gn,
					    sa_family_t family,
					    __be16 dst_port)
अणु
	काष्ठा geneve_sock *gs;

	list_क्रम_each_entry(gs, &gn->sock_list, list) अणु
		अगर (inet_sk(gs->sock->sk)->inet_sport == dst_port &&
		    geneve_get_sk_family(gs) == family) अणु
			वापस gs;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक geneve_sock_add(काष्ठा geneve_dev *geneve, bool ipv6)
अणु
	काष्ठा net *net = geneve->net;
	काष्ठा geneve_net *gn = net_generic(net, geneve_net_id);
	काष्ठा geneve_dev_node *node;
	काष्ठा geneve_sock *gs;
	__u8 vni[3];
	__u32 hash;

	gs = geneve_find_sock(gn, ipv6 ? AF_INET6 : AF_INET, geneve->cfg.info.key.tp_dst);
	अगर (gs) अणु
		gs->refcnt++;
		जाओ out;
	पूर्ण

	gs = geneve_socket_create(net, geneve->cfg.info.key.tp_dst, ipv6,
				  geneve->cfg.use_udp6_rx_checksums);
	अगर (IS_ERR(gs))
		वापस PTR_ERR(gs);

out:
	gs->collect_md = geneve->cfg.collect_md;
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (ipv6) अणु
		rcu_assign_poपूर्णांकer(geneve->sock6, gs);
		node = &geneve->hlist6;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		rcu_assign_poपूर्णांकer(geneve->sock4, gs);
		node = &geneve->hlist4;
	पूर्ण
	node->geneve = geneve;

	tunnel_id_to_vni(geneve->cfg.info.key.tun_id, vni);
	hash = geneve_net_vni_hash(vni);
	hlist_add_head_rcu(&node->hlist, &gs->vni_list[hash]);
	वापस 0;
पूर्ण

अटल पूर्णांक geneve_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा geneve_dev *geneve = netdev_priv(dev);
	bool metadata = geneve->cfg.collect_md;
	bool ipv4, ipv6;
	पूर्णांक ret = 0;

	ipv6 = geneve->cfg.info.mode & IP_TUNNEL_INFO_IPV6 || metadata;
	ipv4 = !ipv6 || metadata;
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (ipv6) अणु
		ret = geneve_sock_add(geneve, true);
		अगर (ret < 0 && ret != -EAFNOSUPPORT)
			ipv4 = false;
	पूर्ण
#पूर्ण_अगर
	अगर (ipv4)
		ret = geneve_sock_add(geneve, false);
	अगर (ret < 0)
		geneve_sock_release(geneve);

	वापस ret;
पूर्ण

अटल पूर्णांक geneve_stop(काष्ठा net_device *dev)
अणु
	काष्ठा geneve_dev *geneve = netdev_priv(dev);

	hlist_del_init_rcu(&geneve->hlist4.hlist);
#अगर IS_ENABLED(CONFIG_IPV6)
	hlist_del_init_rcu(&geneve->hlist6.hlist);
#पूर्ण_अगर
	geneve_sock_release(geneve);
	वापस 0;
पूर्ण

अटल व्योम geneve_build_header(काष्ठा genevehdr *geneveh,
				स्थिर काष्ठा ip_tunnel_info *info)
अणु
	geneveh->ver = GENEVE_VER;
	geneveh->opt_len = info->options_len / 4;
	geneveh->oam = !!(info->key.tun_flags & TUNNEL_OAM);
	geneveh->critical = !!(info->key.tun_flags & TUNNEL_CRIT_OPT);
	geneveh->rsvd1 = 0;
	tunnel_id_to_vni(info->key.tun_id, geneveh->vni);
	geneveh->proto_type = htons(ETH_P_TEB);
	geneveh->rsvd2 = 0;

	अगर (info->key.tun_flags & TUNNEL_GENEVE_OPT)
		ip_tunnel_info_opts_get(geneveh->options, info);
पूर्ण

अटल पूर्णांक geneve_build_skb(काष्ठा dst_entry *dst, काष्ठा sk_buff *skb,
			    स्थिर काष्ठा ip_tunnel_info *info,
			    bool xnet, पूर्णांक ip_hdr_len)
अणु
	bool udp_sum = !!(info->key.tun_flags & TUNNEL_CSUM);
	काष्ठा genevehdr *gnvh;
	पूर्णांक min_headroom;
	पूर्णांक err;

	skb_reset_mac_header(skb);
	skb_scrub_packet(skb, xnet);

	min_headroom = LL_RESERVED_SPACE(dst->dev) + dst->header_len +
		       GENEVE_BASE_HLEN + info->options_len + ip_hdr_len;
	err = skb_cow_head(skb, min_headroom);
	अगर (unlikely(err))
		जाओ मुक्त_dst;

	err = udp_tunnel_handle_offloads(skb, udp_sum);
	अगर (err)
		जाओ मुक्त_dst;

	gnvh = __skb_push(skb, माप(*gnvh) + info->options_len);
	geneve_build_header(gnvh, info);
	skb_set_inner_protocol(skb, htons(ETH_P_TEB));
	वापस 0;

मुक्त_dst:
	dst_release(dst);
	वापस err;
पूर्ण

अटल काष्ठा rtable *geneve_get_v4_rt(काष्ठा sk_buff *skb,
				       काष्ठा net_device *dev,
				       काष्ठा geneve_sock *gs4,
				       काष्ठा flowi4 *fl4,
				       स्थिर काष्ठा ip_tunnel_info *info,
				       __be16 dport, __be16 sport)
अणु
	bool use_cache = ip_tunnel_dst_cache_usable(skb, info);
	काष्ठा geneve_dev *geneve = netdev_priv(dev);
	काष्ठा dst_cache *dst_cache;
	काष्ठा rtable *rt = शून्य;
	__u8 tos;

	अगर (!gs4)
		वापस ERR_PTR(-EIO);

	स_रखो(fl4, 0, माप(*fl4));
	fl4->flowi4_mark = skb->mark;
	fl4->flowi4_proto = IPPROTO_UDP;
	fl4->daddr = info->key.u.ipv4.dst;
	fl4->saddr = info->key.u.ipv4.src;
	fl4->fl4_dport = dport;
	fl4->fl4_sport = sport;

	tos = info->key.tos;
	अगर ((tos == 1) && !geneve->cfg.collect_md) अणु
		tos = ip_tunnel_get_dsfield(ip_hdr(skb), skb);
		use_cache = false;
	पूर्ण
	fl4->flowi4_tos = RT_TOS(tos);

	dst_cache = (काष्ठा dst_cache *)&info->dst_cache;
	अगर (use_cache) अणु
		rt = dst_cache_get_ip4(dst_cache, &fl4->saddr);
		अगर (rt)
			वापस rt;
	पूर्ण
	rt = ip_route_output_key(geneve->net, fl4);
	अगर (IS_ERR(rt)) अणु
		netdev_dbg(dev, "no route to %pI4\n", &fl4->daddr);
		वापस ERR_PTR(-ENETUNREACH);
	पूर्ण
	अगर (rt->dst.dev == dev) अणु /* is this necessary? */
		netdev_dbg(dev, "circular route to %pI4\n", &fl4->daddr);
		ip_rt_put(rt);
		वापस ERR_PTR(-ELOOP);
	पूर्ण
	अगर (use_cache)
		dst_cache_set_ip4(dst_cache, &rt->dst, fl4->saddr);
	वापस rt;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल काष्ठा dst_entry *geneve_get_v6_dst(काष्ठा sk_buff *skb,
					   काष्ठा net_device *dev,
					   काष्ठा geneve_sock *gs6,
					   काष्ठा flowi6 *fl6,
					   स्थिर काष्ठा ip_tunnel_info *info,
					   __be16 dport, __be16 sport)
अणु
	bool use_cache = ip_tunnel_dst_cache_usable(skb, info);
	काष्ठा geneve_dev *geneve = netdev_priv(dev);
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा dst_cache *dst_cache;
	__u8 prio;

	अगर (!gs6)
		वापस ERR_PTR(-EIO);

	स_रखो(fl6, 0, माप(*fl6));
	fl6->flowi6_mark = skb->mark;
	fl6->flowi6_proto = IPPROTO_UDP;
	fl6->daddr = info->key.u.ipv6.dst;
	fl6->saddr = info->key.u.ipv6.src;
	fl6->fl6_dport = dport;
	fl6->fl6_sport = sport;

	prio = info->key.tos;
	अगर ((prio == 1) && !geneve->cfg.collect_md) अणु
		prio = ip_tunnel_get_dsfield(ip_hdr(skb), skb);
		use_cache = false;
	पूर्ण

	fl6->flowlabel = ip6_make_flowinfo(RT_TOS(prio),
					   info->key.label);
	dst_cache = (काष्ठा dst_cache *)&info->dst_cache;
	अगर (use_cache) अणु
		dst = dst_cache_get_ip6(dst_cache, &fl6->saddr);
		अगर (dst)
			वापस dst;
	पूर्ण
	dst = ipv6_stub->ipv6_dst_lookup_flow(geneve->net, gs6->sock->sk, fl6,
					      शून्य);
	अगर (IS_ERR(dst)) अणु
		netdev_dbg(dev, "no route to %pI6\n", &fl6->daddr);
		वापस ERR_PTR(-ENETUNREACH);
	पूर्ण
	अगर (dst->dev == dev) अणु /* is this necessary? */
		netdev_dbg(dev, "circular route to %pI6\n", &fl6->daddr);
		dst_release(dst);
		वापस ERR_PTR(-ELOOP);
	पूर्ण

	अगर (use_cache)
		dst_cache_set_ip6(dst_cache, dst, &fl6->saddr);
	वापस dst;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक geneve_xmit_skb(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			   काष्ठा geneve_dev *geneve,
			   स्थिर काष्ठा ip_tunnel_info *info)
अणु
	bool xnet = !net_eq(geneve->net, dev_net(geneve->dev));
	काष्ठा geneve_sock *gs4 = rcu_dereference(geneve->sock4);
	स्थिर काष्ठा ip_tunnel_key *key = &info->key;
	काष्ठा rtable *rt;
	काष्ठा flowi4 fl4;
	__u8 tos, ttl;
	__be16 df = 0;
	__be16 sport;
	पूर्णांक err;

	अगर (!pskb_inet_may_pull(skb))
		वापस -EINVAL;

	sport = udp_flow_src_port(geneve->net, skb, 1, अच_लघु_उच्च, true);
	rt = geneve_get_v4_rt(skb, dev, gs4, &fl4, info,
			      geneve->cfg.info.key.tp_dst, sport);
	अगर (IS_ERR(rt))
		वापस PTR_ERR(rt);

	err = skb_tunnel_check_pmtu(skb, &rt->dst,
				    GENEVE_IPV4_HLEN + info->options_len,
				    netअगर_is_any_bridge_port(dev));
	अगर (err < 0) अणु
		dst_release(&rt->dst);
		वापस err;
	पूर्ण अन्यथा अगर (err) अणु
		काष्ठा ip_tunnel_info *info;

		info = skb_tunnel_info(skb);
		अगर (info) अणु
			काष्ठा ip_tunnel_info *unclone;

			unclone = skb_tunnel_info_unclone(skb);
			अगर (unlikely(!unclone)) अणु
				dst_release(&rt->dst);
				वापस -ENOMEM;
			पूर्ण

			unclone->key.u.ipv4.dst = fl4.saddr;
			unclone->key.u.ipv4.src = fl4.daddr;
		पूर्ण

		अगर (!pskb_may_pull(skb, ETH_HLEN)) अणु
			dst_release(&rt->dst);
			वापस -EINVAL;
		पूर्ण

		skb->protocol = eth_type_trans(skb, geneve->dev);
		netअगर_rx(skb);
		dst_release(&rt->dst);
		वापस -EMSGSIZE;
	पूर्ण

	अगर (geneve->cfg.collect_md) अणु
		tos = ip_tunnel_ecn_encap(key->tos, ip_hdr(skb), skb);
		ttl = key->ttl;

		df = key->tun_flags & TUNNEL_DONT_FRAGMENT ? htons(IP_DF) : 0;
	पूर्ण अन्यथा अणु
		tos = ip_tunnel_ecn_encap(fl4.flowi4_tos, ip_hdr(skb), skb);
		अगर (geneve->cfg.ttl_inherit)
			ttl = ip_tunnel_get_ttl(ip_hdr(skb), skb);
		अन्यथा
			ttl = key->ttl;
		ttl = ttl ? : ip4_dst_hoplimit(&rt->dst);

		अगर (geneve->cfg.df == GENEVE_DF_SET) अणु
			df = htons(IP_DF);
		पूर्ण अन्यथा अगर (geneve->cfg.df == GENEVE_DF_INHERIT) अणु
			काष्ठा ethhdr *eth = eth_hdr(skb);

			अगर (ntohs(eth->h_proto) == ETH_P_IPV6) अणु
				df = htons(IP_DF);
			पूर्ण अन्यथा अगर (ntohs(eth->h_proto) == ETH_P_IP) अणु
				काष्ठा iphdr *iph = ip_hdr(skb);

				अगर (iph->frag_off & htons(IP_DF))
					df = htons(IP_DF);
			पूर्ण
		पूर्ण
	पूर्ण

	err = geneve_build_skb(&rt->dst, skb, info, xnet, माप(काष्ठा iphdr));
	अगर (unlikely(err))
		वापस err;

	udp_tunnel_xmit_skb(rt, gs4->sock->sk, skb, fl4.saddr, fl4.daddr,
			    tos, ttl, df, sport, geneve->cfg.info.key.tp_dst,
			    !net_eq(geneve->net, dev_net(geneve->dev)),
			    !(info->key.tun_flags & TUNNEL_CSUM));
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक geneve6_xmit_skb(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			    काष्ठा geneve_dev *geneve,
			    स्थिर काष्ठा ip_tunnel_info *info)
अणु
	bool xnet = !net_eq(geneve->net, dev_net(geneve->dev));
	काष्ठा geneve_sock *gs6 = rcu_dereference(geneve->sock6);
	स्थिर काष्ठा ip_tunnel_key *key = &info->key;
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा flowi6 fl6;
	__u8 prio, ttl;
	__be16 sport;
	पूर्णांक err;

	अगर (!pskb_inet_may_pull(skb))
		वापस -EINVAL;

	sport = udp_flow_src_port(geneve->net, skb, 1, अच_लघु_उच्च, true);
	dst = geneve_get_v6_dst(skb, dev, gs6, &fl6, info,
				geneve->cfg.info.key.tp_dst, sport);
	अगर (IS_ERR(dst))
		वापस PTR_ERR(dst);

	err = skb_tunnel_check_pmtu(skb, dst,
				    GENEVE_IPV6_HLEN + info->options_len,
				    netअगर_is_any_bridge_port(dev));
	अगर (err < 0) अणु
		dst_release(dst);
		वापस err;
	पूर्ण अन्यथा अगर (err) अणु
		काष्ठा ip_tunnel_info *info = skb_tunnel_info(skb);

		अगर (info) अणु
			काष्ठा ip_tunnel_info *unclone;

			unclone = skb_tunnel_info_unclone(skb);
			अगर (unlikely(!unclone)) अणु
				dst_release(dst);
				वापस -ENOMEM;
			पूर्ण

			unclone->key.u.ipv6.dst = fl6.saddr;
			unclone->key.u.ipv6.src = fl6.daddr;
		पूर्ण

		अगर (!pskb_may_pull(skb, ETH_HLEN)) अणु
			dst_release(dst);
			वापस -EINVAL;
		पूर्ण

		skb->protocol = eth_type_trans(skb, geneve->dev);
		netअगर_rx(skb);
		dst_release(dst);
		वापस -EMSGSIZE;
	पूर्ण

	अगर (geneve->cfg.collect_md) अणु
		prio = ip_tunnel_ecn_encap(key->tos, ip_hdr(skb), skb);
		ttl = key->ttl;
	पूर्ण अन्यथा अणु
		prio = ip_tunnel_ecn_encap(ip6_tclass(fl6.flowlabel),
					   ip_hdr(skb), skb);
		अगर (geneve->cfg.ttl_inherit)
			ttl = ip_tunnel_get_ttl(ip_hdr(skb), skb);
		अन्यथा
			ttl = key->ttl;
		ttl = ttl ? : ip6_dst_hoplimit(dst);
	पूर्ण
	err = geneve_build_skb(dst, skb, info, xnet, माप(काष्ठा ipv6hdr));
	अगर (unlikely(err))
		वापस err;

	udp_tunnel6_xmit_skb(dst, gs6->sock->sk, skb, dev,
			     &fl6.saddr, &fl6.daddr, prio, ttl,
			     info->key.label, sport, geneve->cfg.info.key.tp_dst,
			     !(info->key.tun_flags & TUNNEL_CSUM));
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल netdev_tx_t geneve_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा geneve_dev *geneve = netdev_priv(dev);
	काष्ठा ip_tunnel_info *info = शून्य;
	पूर्णांक err;

	अगर (geneve->cfg.collect_md) अणु
		info = skb_tunnel_info(skb);
		अगर (unlikely(!info || !(info->mode & IP_TUNNEL_INFO_TX))) अणु
			netdev_dbg(dev, "no tunnel metadata\n");
			dev_kमुक्त_skb(skb);
			dev->stats.tx_dropped++;
			वापस NETDEV_TX_OK;
		पूर्ण
	पूर्ण अन्यथा अणु
		info = &geneve->cfg.info;
	पूर्ण

	rcu_पढ़ो_lock();
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (info->mode & IP_TUNNEL_INFO_IPV6)
		err = geneve6_xmit_skb(skb, dev, geneve, info);
	अन्यथा
#पूर्ण_अगर
		err = geneve_xmit_skb(skb, dev, geneve, info);
	rcu_पढ़ो_unlock();

	अगर (likely(!err))
		वापस NETDEV_TX_OK;

	अगर (err != -EMSGSIZE)
		dev_kमुक्त_skb(skb);

	अगर (err == -ELOOP)
		dev->stats.collisions++;
	अन्यथा अगर (err == -ENETUNREACH)
		dev->stats.tx_carrier_errors++;

	dev->stats.tx_errors++;
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक geneve_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	अगर (new_mtu > dev->max_mtu)
		new_mtu = dev->max_mtu;
	अन्यथा अगर (new_mtu < dev->min_mtu)
		new_mtu = dev->min_mtu;

	dev->mtu = new_mtu;
	वापस 0;
पूर्ण

अटल पूर्णांक geneve_fill_metadata_dst(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा ip_tunnel_info *info = skb_tunnel_info(skb);
	काष्ठा geneve_dev *geneve = netdev_priv(dev);
	__be16 sport;

	अगर (ip_tunnel_info_af(info) == AF_INET) अणु
		काष्ठा rtable *rt;
		काष्ठा flowi4 fl4;

		काष्ठा geneve_sock *gs4 = rcu_dereference(geneve->sock4);
		sport = udp_flow_src_port(geneve->net, skb,
					  1, अच_लघु_उच्च, true);

		rt = geneve_get_v4_rt(skb, dev, gs4, &fl4, info,
				      geneve->cfg.info.key.tp_dst, sport);
		अगर (IS_ERR(rt))
			वापस PTR_ERR(rt);

		ip_rt_put(rt);
		info->key.u.ipv4.src = fl4.saddr;
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (ip_tunnel_info_af(info) == AF_INET6) अणु
		काष्ठा dst_entry *dst;
		काष्ठा flowi6 fl6;

		काष्ठा geneve_sock *gs6 = rcu_dereference(geneve->sock6);
		sport = udp_flow_src_port(geneve->net, skb,
					  1, अच_लघु_उच्च, true);

		dst = geneve_get_v6_dst(skb, dev, gs6, &fl6, info,
					geneve->cfg.info.key.tp_dst, sport);
		अगर (IS_ERR(dst))
			वापस PTR_ERR(dst);

		dst_release(dst);
		info->key.u.ipv6.src = fl6.saddr;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	info->key.tp_src = sport;
	info->key.tp_dst = geneve->cfg.info.key.tp_dst;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops geneve_netdev_ops = अणु
	.nकरो_init		= geneve_init,
	.nकरो_uninit		= geneve_uninit,
	.nकरो_खोलो		= geneve_खोलो,
	.nकरो_stop		= geneve_stop,
	.nकरो_start_xmit		= geneve_xmit,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_change_mtu		= geneve_change_mtu,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_fill_metadata_dst	= geneve_fill_metadata_dst,
पूर्ण;

अटल व्योम geneve_get_drvinfo(काष्ठा net_device *dev,
			       काष्ठा ethtool_drvinfo *drvinfo)
अणु
	strlcpy(drvinfo->version, GENEVE_NETDEV_VER, माप(drvinfo->version));
	strlcpy(drvinfo->driver, "geneve", माप(drvinfo->driver));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops geneve_ethtool_ops = अणु
	.get_drvinfo	= geneve_get_drvinfo,
	.get_link	= ethtool_op_get_link,
पूर्ण;

/* Info क्रम udev, that this is a भव tunnel endpoपूर्णांक */
अटल काष्ठा device_type geneve_type = अणु
	.name = "geneve",
पूर्ण;

/* Calls the nकरो_udp_tunnel_add of the caller in order to
 * supply the listening GENEVE udp ports. Callers are expected
 * to implement the nकरो_udp_tunnel_add.
 */
अटल व्योम geneve_offload_rx_ports(काष्ठा net_device *dev, bool push)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा geneve_net *gn = net_generic(net, geneve_net_id);
	काष्ठा geneve_sock *gs;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(gs, &gn->sock_list, list) अणु
		अगर (push) अणु
			udp_tunnel_push_rx_port(dev, gs->sock,
						UDP_TUNNEL_TYPE_GENEVE);
		पूर्ण अन्यथा अणु
			udp_tunnel_drop_rx_port(dev, gs->sock,
						UDP_TUNNEL_TYPE_GENEVE);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/* Initialize the device काष्ठाure. */
अटल व्योम geneve_setup(काष्ठा net_device *dev)
अणु
	ether_setup(dev);

	dev->netdev_ops = &geneve_netdev_ops;
	dev->ethtool_ops = &geneve_ethtool_ops;
	dev->needs_मुक्त_netdev = true;

	SET_NETDEV_DEVTYPE(dev, &geneve_type);

	dev->features    |= NETIF_F_LLTX;
	dev->features    |= NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_FRAGLIST;
	dev->features    |= NETIF_F_RXCSUM;
	dev->features    |= NETIF_F_GSO_SOFTWARE;

	dev->hw_features |= NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_FRAGLIST;
	dev->hw_features |= NETIF_F_RXCSUM;
	dev->hw_features |= NETIF_F_GSO_SOFTWARE;

	/* MTU range: 68 - (something less than 65535) */
	dev->min_mtu = ETH_MIN_MTU;
	/* The max_mtu calculation करोes not take account of GENEVE
	 * options, to aव्योम excluding potentially valid
	 * configurations. This will be further reduced by IPvX hdr size.
	 */
	dev->max_mtu = IP_MAX_MTU - GENEVE_BASE_HLEN - dev->hard_header_len;

	netअगर_keep_dst(dev);
	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
	dev->priv_flags |= IFF_LIVE_ADDR_CHANGE | IFF_NO_QUEUE;
	eth_hw_addr_अक्रमom(dev);
पूर्ण

अटल स्थिर काष्ठा nla_policy geneve_policy[IFLA_GENEVE_MAX + 1] = अणु
	[IFLA_GENEVE_ID]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_GENEVE_REMOTE]		= अणु .len = माप_field(काष्ठा iphdr, daddr) पूर्ण,
	[IFLA_GENEVE_REMOTE6]		= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[IFLA_GENEVE_TTL]		= अणु .type = NLA_U8 पूर्ण,
	[IFLA_GENEVE_TOS]		= अणु .type = NLA_U8 पूर्ण,
	[IFLA_GENEVE_LABEL]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_GENEVE_PORT]		= अणु .type = NLA_U16 पूर्ण,
	[IFLA_GENEVE_COLLECT_METADATA]	= अणु .type = NLA_FLAG पूर्ण,
	[IFLA_GENEVE_UDP_CSUM]		= अणु .type = NLA_U8 पूर्ण,
	[IFLA_GENEVE_UDP_ZERO_CSUM6_TX]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_GENEVE_UDP_ZERO_CSUM6_RX]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_GENEVE_TTL_INHERIT]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_GENEVE_DF]		= अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल पूर्णांक geneve_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			   काष्ठा netlink_ext_ack *extack)
अणु
	अगर (tb[IFLA_ADDRESS]) अणु
		अगर (nla_len(tb[IFLA_ADDRESS]) != ETH_ALEN) अणु
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_ADDRESS],
					    "Provided link layer address is not Ethernet");
			वापस -EINVAL;
		पूर्ण

		अगर (!is_valid_ether_addr(nla_data(tb[IFLA_ADDRESS]))) अणु
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_ADDRESS],
					    "Provided Ethernet address is not unicast");
			वापस -EADDRNOTAVAIL;
		पूर्ण
	पूर्ण

	अगर (!data) अणु
		NL_SET_ERR_MSG(extack,
			       "Not enough attributes provided to perform the operation");
		वापस -EINVAL;
	पूर्ण

	अगर (data[IFLA_GENEVE_ID]) अणु
		__u32 vni =  nla_get_u32(data[IFLA_GENEVE_ID]);

		अगर (vni >= GENEVE_N_VID) अणु
			NL_SET_ERR_MSG_ATTR(extack, data[IFLA_GENEVE_ID],
					    "Geneve ID must be lower than 16777216");
			वापस -दुस्फल;
		पूर्ण
	पूर्ण

	अगर (data[IFLA_GENEVE_DF]) अणु
		क्रमागत अगरla_geneve_df df = nla_get_u8(data[IFLA_GENEVE_DF]);

		अगर (df < 0 || df > GENEVE_DF_MAX) अणु
			NL_SET_ERR_MSG_ATTR(extack, data[IFLA_GENEVE_DF],
					    "Invalid DF attribute");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा geneve_dev *geneve_find_dev(काष्ठा geneve_net *gn,
					  स्थिर काष्ठा ip_tunnel_info *info,
					  bool *tun_on_same_port,
					  bool *tun_collect_md)
अणु
	काष्ठा geneve_dev *geneve, *t = शून्य;

	*tun_on_same_port = false;
	*tun_collect_md = false;
	list_क्रम_each_entry(geneve, &gn->geneve_list, next) अणु
		अगर (info->key.tp_dst == geneve->cfg.info.key.tp_dst) अणु
			*tun_collect_md = geneve->cfg.collect_md;
			*tun_on_same_port = true;
		पूर्ण
		अगर (info->key.tun_id == geneve->cfg.info.key.tun_id &&
		    info->key.tp_dst == geneve->cfg.info.key.tp_dst &&
		    !स_भेद(&info->key.u, &geneve->cfg.info.key.u, माप(info->key.u)))
			t = geneve;
	पूर्ण
	वापस t;
पूर्ण

अटल bool is_tnl_info_zero(स्थिर काष्ठा ip_tunnel_info *info)
अणु
	वापस !(info->key.tun_id || info->key.tun_flags || info->key.tos ||
		 info->key.ttl || info->key.label || info->key.tp_src ||
		 स_प्रथम_inv(&info->key.u, 0, माप(info->key.u)));
पूर्ण

अटल bool geneve_dst_addr_equal(काष्ठा ip_tunnel_info *a,
				  काष्ठा ip_tunnel_info *b)
अणु
	अगर (ip_tunnel_info_af(a) == AF_INET)
		वापस a->key.u.ipv4.dst == b->key.u.ipv4.dst;
	अन्यथा
		वापस ipv6_addr_equal(&a->key.u.ipv6.dst, &b->key.u.ipv6.dst);
पूर्ण

अटल पूर्णांक geneve_configure(काष्ठा net *net, काष्ठा net_device *dev,
			    काष्ठा netlink_ext_ack *extack,
			    स्थिर काष्ठा geneve_config *cfg)
अणु
	काष्ठा geneve_net *gn = net_generic(net, geneve_net_id);
	काष्ठा geneve_dev *t, *geneve = netdev_priv(dev);
	स्थिर काष्ठा ip_tunnel_info *info = &cfg->info;
	bool tun_collect_md, tun_on_same_port;
	पूर्णांक err, encap_len;

	अगर (cfg->collect_md && !is_tnl_info_zero(info)) अणु
		NL_SET_ERR_MSG(extack,
			       "Device is externally controlled, so attributes (VNI, Port, and so on) must not be specified");
		वापस -EINVAL;
	पूर्ण

	geneve->net = net;
	geneve->dev = dev;

	t = geneve_find_dev(gn, info, &tun_on_same_port, &tun_collect_md);
	अगर (t)
		वापस -EBUSY;

	/* make enough headroom क्रम basic scenario */
	encap_len = GENEVE_BASE_HLEN + ETH_HLEN;
	अगर (!cfg->collect_md && ip_tunnel_info_af(info) == AF_INET) अणु
		encap_len += माप(काष्ठा iphdr);
		dev->max_mtu -= माप(काष्ठा iphdr);
	पूर्ण अन्यथा अणु
		encap_len += माप(काष्ठा ipv6hdr);
		dev->max_mtu -= माप(काष्ठा ipv6hdr);
	पूर्ण
	dev->needed_headroom = encap_len + ETH_HLEN;

	अगर (cfg->collect_md) अणु
		अगर (tun_on_same_port) अणु
			NL_SET_ERR_MSG(extack,
				       "There can be only one externally controlled device on a destination port");
			वापस -EPERM;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (tun_collect_md) अणु
			NL_SET_ERR_MSG(extack,
				       "There already exists an externally controlled device on this destination port");
			वापस -EPERM;
		पूर्ण
	पूर्ण

	dst_cache_reset(&geneve->cfg.info.dst_cache);
	स_नकल(&geneve->cfg, cfg, माप(*cfg));

	err = रेजिस्टर_netdevice(dev);
	अगर (err)
		वापस err;

	list_add(&geneve->next, &gn->geneve_list);
	वापस 0;
पूर्ण

अटल व्योम init_tnl_info(काष्ठा ip_tunnel_info *info, __u16 dst_port)
अणु
	स_रखो(info, 0, माप(*info));
	info->key.tp_dst = htons(dst_port);
पूर्ण

अटल पूर्णांक geneve_nl2info(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			  काष्ठा netlink_ext_ack *extack,
			  काष्ठा geneve_config *cfg, bool changelink)
अणु
	काष्ठा ip_tunnel_info *info = &cfg->info;
	पूर्णांक attrtype;

	अगर (data[IFLA_GENEVE_REMOTE] && data[IFLA_GENEVE_REMOTE6]) अणु
		NL_SET_ERR_MSG(extack,
			       "Cannot specify both IPv4 and IPv6 Remote addresses");
		वापस -EINVAL;
	पूर्ण

	अगर (data[IFLA_GENEVE_REMOTE]) अणु
		अगर (changelink && (ip_tunnel_info_af(info) == AF_INET6)) अणु
			attrtype = IFLA_GENEVE_REMOTE;
			जाओ change_notsup;
		पूर्ण

		info->key.u.ipv4.dst =
			nla_get_in_addr(data[IFLA_GENEVE_REMOTE]);

		अगर (ipv4_is_multicast(info->key.u.ipv4.dst)) अणु
			NL_SET_ERR_MSG_ATTR(extack, data[IFLA_GENEVE_REMOTE],
					    "Remote IPv4 address cannot be Multicast");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (data[IFLA_GENEVE_REMOTE6]) अणु
#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (changelink && (ip_tunnel_info_af(info) == AF_INET)) अणु
			attrtype = IFLA_GENEVE_REMOTE6;
			जाओ change_notsup;
		पूर्ण

		info->mode = IP_TUNNEL_INFO_IPV6;
		info->key.u.ipv6.dst =
			nla_get_in6_addr(data[IFLA_GENEVE_REMOTE6]);

		अगर (ipv6_addr_type(&info->key.u.ipv6.dst) &
		    IPV6_ADDR_LINKLOCAL) अणु
			NL_SET_ERR_MSG_ATTR(extack, data[IFLA_GENEVE_REMOTE6],
					    "Remote IPv6 address cannot be link-local");
			वापस -EINVAL;
		पूर्ण
		अगर (ipv6_addr_is_multicast(&info->key.u.ipv6.dst)) अणु
			NL_SET_ERR_MSG_ATTR(extack, data[IFLA_GENEVE_REMOTE6],
					    "Remote IPv6 address cannot be Multicast");
			वापस -EINVAL;
		पूर्ण
		info->key.tun_flags |= TUNNEL_CSUM;
		cfg->use_udp6_rx_checksums = true;
#अन्यथा
		NL_SET_ERR_MSG_ATTR(extack, data[IFLA_GENEVE_REMOTE6],
				    "IPv6 support not enabled in the kernel");
		वापस -EPFNOSUPPORT;
#पूर्ण_अगर
	पूर्ण

	अगर (data[IFLA_GENEVE_ID]) अणु
		__u32 vni;
		__u8 tvni[3];
		__be64 tunid;

		vni = nla_get_u32(data[IFLA_GENEVE_ID]);
		tvni[0] = (vni & 0x00ff0000) >> 16;
		tvni[1] = (vni & 0x0000ff00) >> 8;
		tvni[2] =  vni & 0x000000ff;

		tunid = vni_to_tunnel_id(tvni);
		अगर (changelink && (tunid != info->key.tun_id)) अणु
			attrtype = IFLA_GENEVE_ID;
			जाओ change_notsup;
		पूर्ण
		info->key.tun_id = tunid;
	पूर्ण

	अगर (data[IFLA_GENEVE_TTL_INHERIT]) अणु
		अगर (nla_get_u8(data[IFLA_GENEVE_TTL_INHERIT]))
			cfg->ttl_inherit = true;
		अन्यथा
			cfg->ttl_inherit = false;
	पूर्ण अन्यथा अगर (data[IFLA_GENEVE_TTL]) अणु
		info->key.ttl = nla_get_u8(data[IFLA_GENEVE_TTL]);
		cfg->ttl_inherit = false;
	पूर्ण

	अगर (data[IFLA_GENEVE_TOS])
		info->key.tos = nla_get_u8(data[IFLA_GENEVE_TOS]);

	अगर (data[IFLA_GENEVE_DF])
		cfg->df = nla_get_u8(data[IFLA_GENEVE_DF]);

	अगर (data[IFLA_GENEVE_LABEL]) अणु
		info->key.label = nla_get_be32(data[IFLA_GENEVE_LABEL]) &
				  IPV6_FLOWLABEL_MASK;
		अगर (info->key.label && (!(info->mode & IP_TUNNEL_INFO_IPV6))) अणु
			NL_SET_ERR_MSG_ATTR(extack, data[IFLA_GENEVE_LABEL],
					    "Label attribute only applies for IPv6 Geneve devices");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (data[IFLA_GENEVE_PORT]) अणु
		अगर (changelink) अणु
			attrtype = IFLA_GENEVE_PORT;
			जाओ change_notsup;
		पूर्ण
		info->key.tp_dst = nla_get_be16(data[IFLA_GENEVE_PORT]);
	पूर्ण

	अगर (data[IFLA_GENEVE_COLLECT_METADATA]) अणु
		अगर (changelink) अणु
			attrtype = IFLA_GENEVE_COLLECT_METADATA;
			जाओ change_notsup;
		पूर्ण
		cfg->collect_md = true;
	पूर्ण

	अगर (data[IFLA_GENEVE_UDP_CSUM]) अणु
		अगर (changelink) अणु
			attrtype = IFLA_GENEVE_UDP_CSUM;
			जाओ change_notsup;
		पूर्ण
		अगर (nla_get_u8(data[IFLA_GENEVE_UDP_CSUM]))
			info->key.tun_flags |= TUNNEL_CSUM;
	पूर्ण

	अगर (data[IFLA_GENEVE_UDP_ZERO_CSUM6_TX]) अणु
#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (changelink) अणु
			attrtype = IFLA_GENEVE_UDP_ZERO_CSUM6_TX;
			जाओ change_notsup;
		पूर्ण
		अगर (nla_get_u8(data[IFLA_GENEVE_UDP_ZERO_CSUM6_TX]))
			info->key.tun_flags &= ~TUNNEL_CSUM;
#अन्यथा
		NL_SET_ERR_MSG_ATTR(extack, data[IFLA_GENEVE_UDP_ZERO_CSUM6_TX],
				    "IPv6 support not enabled in the kernel");
		वापस -EPFNOSUPPORT;
#पूर्ण_अगर
	पूर्ण

	अगर (data[IFLA_GENEVE_UDP_ZERO_CSUM6_RX]) अणु
#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (changelink) अणु
			attrtype = IFLA_GENEVE_UDP_ZERO_CSUM6_RX;
			जाओ change_notsup;
		पूर्ण
		अगर (nla_get_u8(data[IFLA_GENEVE_UDP_ZERO_CSUM6_RX]))
			cfg->use_udp6_rx_checksums = false;
#अन्यथा
		NL_SET_ERR_MSG_ATTR(extack, data[IFLA_GENEVE_UDP_ZERO_CSUM6_RX],
				    "IPv6 support not enabled in the kernel");
		वापस -EPFNOSUPPORT;
#पूर्ण_अगर
	पूर्ण

	वापस 0;
change_notsup:
	NL_SET_ERR_MSG_ATTR(extack, data[attrtype],
			    "Changing VNI, Port, endpoint IP address family, external, and UDP checksum attributes are not supported");
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम geneve_link_config(काष्ठा net_device *dev,
			       काष्ठा ip_tunnel_info *info, काष्ठा nlattr *tb[])
अणु
	काष्ठा geneve_dev *geneve = netdev_priv(dev);
	पूर्णांक ldev_mtu = 0;

	अगर (tb[IFLA_MTU]) अणु
		geneve_change_mtu(dev, nla_get_u32(tb[IFLA_MTU]));
		वापस;
	पूर्ण

	चयन (ip_tunnel_info_af(info)) अणु
	हाल AF_INET: अणु
		काष्ठा flowi4 fl4 = अणु .daddr = info->key.u.ipv4.dst पूर्ण;
		काष्ठा rtable *rt = ip_route_output_key(geneve->net, &fl4);

		अगर (!IS_ERR(rt) && rt->dst.dev) अणु
			ldev_mtu = rt->dst.dev->mtu - GENEVE_IPV4_HLEN;
			ip_rt_put(rt);
		पूर्ण
		अवरोध;
	पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6: अणु
		काष्ठा rt6_info *rt;

		अगर (!__in6_dev_get(dev))
			अवरोध;

		rt = rt6_lookup(geneve->net, &info->key.u.ipv6.dst, शून्य, 0,
				शून्य, 0);

		अगर (rt && rt->dst.dev)
			ldev_mtu = rt->dst.dev->mtu - GENEVE_IPV6_HLEN;
		ip6_rt_put(rt);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	पूर्ण

	अगर (ldev_mtu <= 0)
		वापस;

	geneve_change_mtu(dev, ldev_mtu - info->options_len);
पूर्ण

अटल पूर्णांक geneve_newlink(काष्ठा net *net, काष्ठा net_device *dev,
			  काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा geneve_config cfg = अणु
		.df = GENEVE_DF_UNSET,
		.use_udp6_rx_checksums = false,
		.ttl_inherit = false,
		.collect_md = false,
	पूर्ण;
	पूर्णांक err;

	init_tnl_info(&cfg.info, GENEVE_UDP_PORT);
	err = geneve_nl2info(tb, data, extack, &cfg, false);
	अगर (err)
		वापस err;

	err = geneve_configure(net, dev, extack, &cfg);
	अगर (err)
		वापस err;

	geneve_link_config(dev, &cfg.info, tb);

	वापस 0;
पूर्ण

/* Quiesces the geneve device data path क्रम both TX and RX.
 *
 * On transmit geneve checks क्रम non-शून्य geneve_sock beक्रमe it proceeds.
 * So, अगर we set that socket to शून्य under RCU and रुको क्रम synchronize_net()
 * to complete क्रम the existing set of in-flight packets to be transmitted,
 * then we would have quiesced the transmit data path. All the future packets
 * will get dropped until we unquiesce the data path.
 *
 * On receive geneve dereference the geneve_sock stashed in the socket. So,
 * अगर we set that to शून्य under RCU and रुको क्रम synchronize_net() to
 * complete, then we would have quiesced the receive data path.
 */
अटल व्योम geneve_quiesce(काष्ठा geneve_dev *geneve, काष्ठा geneve_sock **gs4,
			   काष्ठा geneve_sock **gs6)
अणु
	*gs4 = rtnl_dereference(geneve->sock4);
	rcu_assign_poपूर्णांकer(geneve->sock4, शून्य);
	अगर (*gs4)
		rcu_assign_sk_user_data((*gs4)->sock->sk, शून्य);
#अगर IS_ENABLED(CONFIG_IPV6)
	*gs6 = rtnl_dereference(geneve->sock6);
	rcu_assign_poपूर्णांकer(geneve->sock6, शून्य);
	अगर (*gs6)
		rcu_assign_sk_user_data((*gs6)->sock->sk, शून्य);
#अन्यथा
	*gs6 = शून्य;
#पूर्ण_अगर
	synchronize_net();
पूर्ण

/* Resumes the geneve device data path क्रम both TX and RX. */
अटल व्योम geneve_unquiesce(काष्ठा geneve_dev *geneve, काष्ठा geneve_sock *gs4,
			     काष्ठा geneve_sock __maybe_unused *gs6)
अणु
	rcu_assign_poपूर्णांकer(geneve->sock4, gs4);
	अगर (gs4)
		rcu_assign_sk_user_data(gs4->sock->sk, gs4);
#अगर IS_ENABLED(CONFIG_IPV6)
	rcu_assign_poपूर्णांकer(geneve->sock6, gs6);
	अगर (gs6)
		rcu_assign_sk_user_data(gs6->sock->sk, gs6);
#पूर्ण_अगर
	synchronize_net();
पूर्ण

अटल पूर्णांक geneve_changelink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
			     काष्ठा nlattr *data[],
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा geneve_dev *geneve = netdev_priv(dev);
	काष्ठा geneve_sock *gs4, *gs6;
	काष्ठा geneve_config cfg;
	पूर्णांक err;

	/* If the geneve device is configured क्रम metadata (or बाह्यally
	 * controlled, क्रम example, OVS), then nothing can be changed.
	 */
	अगर (geneve->cfg.collect_md)
		वापस -EOPNOTSUPP;

	/* Start with the existing info. */
	स_नकल(&cfg, &geneve->cfg, माप(cfg));
	err = geneve_nl2info(tb, data, extack, &cfg, true);
	अगर (err)
		वापस err;

	अगर (!geneve_dst_addr_equal(&geneve->cfg.info, &cfg.info)) अणु
		dst_cache_reset(&cfg.info.dst_cache);
		geneve_link_config(dev, &cfg.info, tb);
	पूर्ण

	geneve_quiesce(geneve, &gs4, &gs6);
	स_नकल(&geneve->cfg, &cfg, माप(cfg));
	geneve_unquiesce(geneve, gs4, gs6);

	वापस 0;
पूर्ण

अटल व्योम geneve_dellink(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	काष्ठा geneve_dev *geneve = netdev_priv(dev);

	list_del(&geneve->next);
	unरेजिस्टर_netdevice_queue(dev, head);
पूर्ण

अटल माप_प्रकार geneve_get_size(स्थिर काष्ठा net_device *dev)
अणु
	वापस nla_total_size(माप(__u32)) +	/* IFLA_GENEVE_ID */
		nla_total_size(माप(काष्ठा in6_addr)) + /* IFLA_GENEVE_REMOTEअणु6पूर्ण */
		nla_total_size(माप(__u8)) +  /* IFLA_GENEVE_TTL */
		nla_total_size(माप(__u8)) +  /* IFLA_GENEVE_TOS */
		nla_total_size(माप(__u8)) +	/* IFLA_GENEVE_DF */
		nla_total_size(माप(__be32)) +  /* IFLA_GENEVE_LABEL */
		nla_total_size(माप(__be16)) +  /* IFLA_GENEVE_PORT */
		nla_total_size(0) +	 /* IFLA_GENEVE_COLLECT_METADATA */
		nla_total_size(माप(__u8)) + /* IFLA_GENEVE_UDP_CSUM */
		nla_total_size(माप(__u8)) + /* IFLA_GENEVE_UDP_ZERO_CSUM6_TX */
		nla_total_size(माप(__u8)) + /* IFLA_GENEVE_UDP_ZERO_CSUM6_RX */
		nla_total_size(माप(__u8)) + /* IFLA_GENEVE_TTL_INHERIT */
		0;
पूर्ण

अटल पूर्णांक geneve_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा geneve_dev *geneve = netdev_priv(dev);
	काष्ठा ip_tunnel_info *info = &geneve->cfg.info;
	bool ttl_inherit = geneve->cfg.ttl_inherit;
	bool metadata = geneve->cfg.collect_md;
	__u8 पंचांगp_vni[3];
	__u32 vni;

	tunnel_id_to_vni(info->key.tun_id, पंचांगp_vni);
	vni = (पंचांगp_vni[0] << 16) | (पंचांगp_vni[1] << 8) | पंचांगp_vni[2];
	अगर (nla_put_u32(skb, IFLA_GENEVE_ID, vni))
		जाओ nla_put_failure;

	अगर (!metadata && ip_tunnel_info_af(info) == AF_INET) अणु
		अगर (nla_put_in_addr(skb, IFLA_GENEVE_REMOTE,
				    info->key.u.ipv4.dst))
			जाओ nla_put_failure;
		अगर (nla_put_u8(skb, IFLA_GENEVE_UDP_CSUM,
			       !!(info->key.tun_flags & TUNNEL_CSUM)))
			जाओ nla_put_failure;

#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (!metadata) अणु
		अगर (nla_put_in6_addr(skb, IFLA_GENEVE_REMOTE6,
				     &info->key.u.ipv6.dst))
			जाओ nla_put_failure;
		अगर (nla_put_u8(skb, IFLA_GENEVE_UDP_ZERO_CSUM6_TX,
			       !(info->key.tun_flags & TUNNEL_CSUM)))
			जाओ nla_put_failure;
#पूर्ण_अगर
	पूर्ण

	अगर (nla_put_u8(skb, IFLA_GENEVE_TTL, info->key.ttl) ||
	    nla_put_u8(skb, IFLA_GENEVE_TOS, info->key.tos) ||
	    nla_put_be32(skb, IFLA_GENEVE_LABEL, info->key.label))
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, IFLA_GENEVE_DF, geneve->cfg.df))
		जाओ nla_put_failure;

	अगर (nla_put_be16(skb, IFLA_GENEVE_PORT, info->key.tp_dst))
		जाओ nla_put_failure;

	अगर (metadata && nla_put_flag(skb, IFLA_GENEVE_COLLECT_METADATA))
		जाओ nla_put_failure;

#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (nla_put_u8(skb, IFLA_GENEVE_UDP_ZERO_CSUM6_RX,
		       !geneve->cfg.use_udp6_rx_checksums))
		जाओ nla_put_failure;
#पूर्ण_अगर

	अगर (nla_put_u8(skb, IFLA_GENEVE_TTL_INHERIT, ttl_inherit))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल काष्ठा rtnl_link_ops geneve_link_ops __पढ़ो_mostly = अणु
	.kind		= "geneve",
	.maxtype	= IFLA_GENEVE_MAX,
	.policy		= geneve_policy,
	.priv_size	= माप(काष्ठा geneve_dev),
	.setup		= geneve_setup,
	.validate	= geneve_validate,
	.newlink	= geneve_newlink,
	.changelink	= geneve_changelink,
	.dellink	= geneve_dellink,
	.get_size	= geneve_get_size,
	.fill_info	= geneve_fill_info,
पूर्ण;

काष्ठा net_device *geneve_dev_create_fb(काष्ठा net *net, स्थिर अक्षर *name,
					u8 name_assign_type, u16 dst_port)
अणु
	काष्ठा nlattr *tb[IFLA_MAX + 1];
	काष्ठा net_device *dev;
	LIST_HEAD(list_समाप्त);
	पूर्णांक err;
	काष्ठा geneve_config cfg = अणु
		.df = GENEVE_DF_UNSET,
		.use_udp6_rx_checksums = true,
		.ttl_inherit = false,
		.collect_md = true,
	पूर्ण;

	स_रखो(tb, 0, माप(tb));
	dev = rtnl_create_link(net, name, name_assign_type,
			       &geneve_link_ops, tb, शून्य);
	अगर (IS_ERR(dev))
		वापस dev;

	init_tnl_info(&cfg.info, dst_port);
	err = geneve_configure(net, dev, शून्य, &cfg);
	अगर (err) अणु
		मुक्त_netdev(dev);
		वापस ERR_PTR(err);
	पूर्ण

	/* खोलोvचयन users expect packet sizes to be unrestricted,
	 * so set the largest MTU we can.
	 */
	err = geneve_change_mtu(dev, IP_MAX_MTU);
	अगर (err)
		जाओ err;

	err = rtnl_configure_link(dev, शून्य);
	अगर (err < 0)
		जाओ err;

	वापस dev;
err:
	geneve_dellink(dev, &list_समाप्त);
	unरेजिस्टर_netdevice_many(&list_समाप्त);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(geneve_dev_create_fb);

अटल पूर्णांक geneve_netdevice_event(काष्ठा notअगरier_block *unused,
				  अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	अगर (event == NETDEV_UDP_TUNNEL_PUSH_INFO)
		geneve_offload_rx_ports(dev, true);
	अन्यथा अगर (event == NETDEV_UDP_TUNNEL_DROP_INFO)
		geneve_offload_rx_ports(dev, false);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block geneve_notअगरier_block __पढ़ो_mostly = अणु
	.notअगरier_call = geneve_netdevice_event,
पूर्ण;

अटल __net_init पूर्णांक geneve_init_net(काष्ठा net *net)
अणु
	काष्ठा geneve_net *gn = net_generic(net, geneve_net_id);

	INIT_LIST_HEAD(&gn->geneve_list);
	INIT_LIST_HEAD(&gn->sock_list);
	वापस 0;
पूर्ण

अटल व्योम geneve_destroy_tunnels(काष्ठा net *net, काष्ठा list_head *head)
अणु
	काष्ठा geneve_net *gn = net_generic(net, geneve_net_id);
	काष्ठा geneve_dev *geneve, *next;
	काष्ठा net_device *dev, *aux;

	/* gather any geneve devices that were moved पूर्णांकo this ns */
	क्रम_each_netdev_safe(net, dev, aux)
		अगर (dev->rtnl_link_ops == &geneve_link_ops)
			unरेजिस्टर_netdevice_queue(dev, head);

	/* now gather any other geneve devices that were created in this ns */
	list_क्रम_each_entry_safe(geneve, next, &gn->geneve_list, next) अणु
		/* If geneve->dev is in the same netns, it was alपढ़ोy added
		 * to the list by the previous loop.
		 */
		अगर (!net_eq(dev_net(geneve->dev), net))
			unरेजिस्टर_netdevice_queue(geneve->dev, head);
	पूर्ण
पूर्ण

अटल व्योम __net_निकास geneve_निकास_batch_net(काष्ठा list_head *net_list)
अणु
	काष्ठा net *net;
	LIST_HEAD(list);

	rtnl_lock();
	list_क्रम_each_entry(net, net_list, निकास_list)
		geneve_destroy_tunnels(net, &list);

	/* unरेजिस्टर the devices gathered above */
	unरेजिस्टर_netdevice_many(&list);
	rtnl_unlock();

	list_क्रम_each_entry(net, net_list, निकास_list) अणु
		स्थिर काष्ठा geneve_net *gn = net_generic(net, geneve_net_id);

		WARN_ON_ONCE(!list_empty(&gn->sock_list));
	पूर्ण
पूर्ण

अटल काष्ठा pernet_operations geneve_net_ops = अणु
	.init = geneve_init_net,
	.निकास_batch = geneve_निकास_batch_net,
	.id   = &geneve_net_id,
	.size = माप(काष्ठा geneve_net),
पूर्ण;

अटल पूर्णांक __init geneve_init_module(व्योम)
अणु
	पूर्णांक rc;

	rc = रेजिस्टर_pernet_subsys(&geneve_net_ops);
	अगर (rc)
		जाओ out1;

	rc = रेजिस्टर_netdevice_notअगरier(&geneve_notअगरier_block);
	अगर (rc)
		जाओ out2;

	rc = rtnl_link_रेजिस्टर(&geneve_link_ops);
	अगर (rc)
		जाओ out3;

	वापस 0;
out3:
	unरेजिस्टर_netdevice_notअगरier(&geneve_notअगरier_block);
out2:
	unरेजिस्टर_pernet_subsys(&geneve_net_ops);
out1:
	वापस rc;
पूर्ण
late_initcall(geneve_init_module);

अटल व्योम __निकास geneve_cleanup_module(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&geneve_link_ops);
	unरेजिस्टर_netdevice_notअगरier(&geneve_notअगरier_block);
	unरेजिस्टर_pernet_subsys(&geneve_net_ops);
पूर्ण
module_निकास(geneve_cleanup_module);

MODULE_LICENSE("GPL");
MODULE_VERSION(GENEVE_NETDEV_VER);
MODULE_AUTHOR("John W. Linville <linville@tuxdriver.com>");
MODULE_DESCRIPTION("Interface driver for GENEVE encapsulated traffic");
MODULE_ALIAS_RTNL_LINK("geneve");
