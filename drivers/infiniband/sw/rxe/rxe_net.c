<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/udp_tunnel.h>
#समावेश <net/sch_generic.h>
#समावेश <linux/netfilter.h>
#समावेश <rdma/ib_addr.h>

#समावेश "rxe.h"
#समावेश "rxe_net.h"
#समावेश "rxe_loc.h"

अटल काष्ठा rxe_recv_sockets recv_sockets;

पूर्णांक rxe_mcast_add(काष्ठा rxe_dev *rxe, जोड़ ib_gid *mgid)
अणु
	पूर्णांक err;
	अचिन्हित अक्षर ll_addr[ETH_ALEN];

	ipv6_eth_mc_map((काष्ठा in6_addr *)mgid->raw, ll_addr);
	err = dev_mc_add(rxe->ndev, ll_addr);

	वापस err;
पूर्ण

पूर्णांक rxe_mcast_delete(काष्ठा rxe_dev *rxe, जोड़ ib_gid *mgid)
अणु
	पूर्णांक err;
	अचिन्हित अक्षर ll_addr[ETH_ALEN];

	ipv6_eth_mc_map((काष्ठा in6_addr *)mgid->raw, ll_addr);
	err = dev_mc_del(rxe->ndev, ll_addr);

	वापस err;
पूर्ण

अटल काष्ठा dst_entry *rxe_find_route4(काष्ठा net_device *ndev,
				  काष्ठा in_addr *saddr,
				  काष्ठा in_addr *daddr)
अणु
	काष्ठा rtable *rt;
	काष्ठा flowi4 fl = अणु अणु 0 पूर्ण पूर्ण;

	स_रखो(&fl, 0, माप(fl));
	fl.flowi4_oअगर = ndev->अगरindex;
	स_नकल(&fl.saddr, saddr, माप(*saddr));
	स_नकल(&fl.daddr, daddr, माप(*daddr));
	fl.flowi4_proto = IPPROTO_UDP;

	rt = ip_route_output_key(&init_net, &fl);
	अगर (IS_ERR(rt)) अणु
		pr_err_ratelimited("no route to %pI4\n", &daddr->s_addr);
		वापस शून्य;
	पूर्ण

	वापस &rt->dst;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल काष्ठा dst_entry *rxe_find_route6(काष्ठा net_device *ndev,
					 काष्ठा in6_addr *saddr,
					 काष्ठा in6_addr *daddr)
अणु
	काष्ठा dst_entry *ndst;
	काष्ठा flowi6 fl6 = अणु अणु 0 पूर्ण पूर्ण;

	स_रखो(&fl6, 0, माप(fl6));
	fl6.flowi6_oअगर = ndev->अगरindex;
	स_नकल(&fl6.saddr, saddr, माप(*saddr));
	स_नकल(&fl6.daddr, daddr, माप(*daddr));
	fl6.flowi6_proto = IPPROTO_UDP;

	ndst = ipv6_stub->ipv6_dst_lookup_flow(sock_net(recv_sockets.sk6->sk),
					       recv_sockets.sk6->sk, &fl6,
					       शून्य);
	अगर (IS_ERR(ndst)) अणु
		pr_err_ratelimited("no route to %pI6\n", daddr);
		वापस शून्य;
	पूर्ण

	अगर (unlikely(ndst->error)) अणु
		pr_err("no route to %pI6\n", daddr);
		जाओ put;
	पूर्ण

	वापस ndst;
put:
	dst_release(ndst);
	वापस शून्य;
पूर्ण

#अन्यथा

अटल काष्ठा dst_entry *rxe_find_route6(काष्ठा net_device *ndev,
					 काष्ठा in6_addr *saddr,
					 काष्ठा in6_addr *daddr)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर

अटल काष्ठा dst_entry *rxe_find_route(काष्ठा net_device *ndev,
					काष्ठा rxe_qp *qp,
					काष्ठा rxe_av *av)
अणु
	काष्ठा dst_entry *dst = शून्य;

	अगर (qp_type(qp) == IB_QPT_RC)
		dst = sk_dst_get(qp->sk->sk);

	अगर (!dst || !dst_check(dst, qp->dst_cookie)) अणु
		अगर (dst)
			dst_release(dst);

		अगर (av->network_type == RXE_NETWORK_TYPE_IPV4) अणु
			काष्ठा in_addr *saddr;
			काष्ठा in_addr *daddr;

			saddr = &av->sgid_addr._sockaddr_in.sin_addr;
			daddr = &av->dgid_addr._sockaddr_in.sin_addr;
			dst = rxe_find_route4(ndev, saddr, daddr);
		पूर्ण अन्यथा अगर (av->network_type == RXE_NETWORK_TYPE_IPV6) अणु
			काष्ठा in6_addr *saddr6;
			काष्ठा in6_addr *daddr6;

			saddr6 = &av->sgid_addr._sockaddr_in6.sin6_addr;
			daddr6 = &av->dgid_addr._sockaddr_in6.sin6_addr;
			dst = rxe_find_route6(ndev, saddr6, daddr6);
#अगर IS_ENABLED(CONFIG_IPV6)
			अगर (dst)
				qp->dst_cookie =
					rt6_get_cookie((काष्ठा rt6_info *)dst);
#पूर्ण_अगर
		पूर्ण

		अगर (dst && (qp_type(qp) == IB_QPT_RC)) अणु
			dst_hold(dst);
			sk_dst_set(qp->sk->sk, dst);
		पूर्ण
	पूर्ण
	वापस dst;
पूर्ण

अटल पूर्णांक rxe_udp_encap_recv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा udphdr *udph;
	काष्ठा rxe_dev *rxe;
	काष्ठा net_device *ndev = skb->dev;
	काष्ठा rxe_pkt_info *pkt = SKB_TO_PKT(skb);

	/* takes a reference on rxe->ib_dev
	 * drop when skb is मुक्तd
	 */
	rxe = rxe_get_dev_from_net(ndev);
	अगर (!rxe && is_vlan_dev(ndev))
		rxe = rxe_get_dev_from_net(vlan_dev_real_dev(ndev));
	अगर (!rxe)
		जाओ drop;

	अगर (skb_linearize(skb)) अणु
		pr_err("skb_linearize failed\n");
		ib_device_put(&rxe->ib_dev);
		जाओ drop;
	पूर्ण

	udph = udp_hdr(skb);
	pkt->rxe = rxe;
	pkt->port_num = 1;
	pkt->hdr = (u8 *)(udph + 1);
	pkt->mask = RXE_GRH_MASK;
	pkt->paylen = be16_to_cpu(udph->len) - माप(*udph);

	rxe_rcv(skb);

	वापस 0;
drop:
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

अटल काष्ठा socket *rxe_setup_udp_tunnel(काष्ठा net *net, __be16 port,
					   bool ipv6)
अणु
	पूर्णांक err;
	काष्ठा socket *sock;
	काष्ठा udp_port_cfg udp_cfg = अणु पूर्ण;
	काष्ठा udp_tunnel_sock_cfg tnl_cfg = अणु पूर्ण;

	अगर (ipv6) अणु
		udp_cfg.family = AF_INET6;
		udp_cfg.ipv6_v6only = 1;
	पूर्ण अन्यथा अणु
		udp_cfg.family = AF_INET;
	पूर्ण

	udp_cfg.local_udp_port = port;

	/* Create UDP socket */
	err = udp_sock_create(net, &udp_cfg, &sock);
	अगर (err < 0) अणु
		pr_err("failed to create udp socket. err = %d\n", err);
		वापस ERR_PTR(err);
	पूर्ण

	tnl_cfg.encap_type = 1;
	tnl_cfg.encap_rcv = rxe_udp_encap_recv;

	/* Setup UDP tunnel */
	setup_udp_tunnel_sock(net, sock, &tnl_cfg);

	वापस sock;
पूर्ण

अटल व्योम rxe_release_udp_tunnel(काष्ठा socket *sk)
अणु
	अगर (sk)
		udp_tunnel_sock_release(sk);
पूर्ण

अटल व्योम prepare_udp_hdr(काष्ठा sk_buff *skb, __be16 src_port,
			    __be16 dst_port)
अणु
	काष्ठा udphdr *udph;

	__skb_push(skb, माप(*udph));
	skb_reset_transport_header(skb);
	udph = udp_hdr(skb);

	udph->dest = dst_port;
	udph->source = src_port;
	udph->len = htons(skb->len);
	udph->check = 0;
पूर्ण

अटल व्योम prepare_ipv4_hdr(काष्ठा dst_entry *dst, काष्ठा sk_buff *skb,
			     __be32 saddr, __be32 daddr, __u8 proto,
			     __u8 tos, __u8 ttl, __be16 df, bool xnet)
अणु
	काष्ठा iphdr *iph;

	skb_scrub_packet(skb, xnet);

	skb_clear_hash(skb);
	skb_dst_set(skb, dst_clone(dst));
	स_रखो(IPCB(skb), 0, माप(*IPCB(skb)));

	skb_push(skb, माप(काष्ठा iphdr));
	skb_reset_network_header(skb);

	iph = ip_hdr(skb);

	iph->version	=	IPVERSION;
	iph->ihl	=	माप(काष्ठा iphdr) >> 2;
	iph->frag_off	=	df;
	iph->protocol	=	proto;
	iph->tos	=	tos;
	iph->daddr	=	daddr;
	iph->saddr	=	saddr;
	iph->ttl	=	ttl;
	__ip_select_ident(dev_net(dst->dev), iph,
			  skb_shinfo(skb)->gso_segs ?: 1);
	iph->tot_len = htons(skb->len);
	ip_send_check(iph);
पूर्ण

अटल व्योम prepare_ipv6_hdr(काष्ठा dst_entry *dst, काष्ठा sk_buff *skb,
			     काष्ठा in6_addr *saddr, काष्ठा in6_addr *daddr,
			     __u8 proto, __u8 prio, __u8 ttl)
अणु
	काष्ठा ipv6hdr *ip6h;

	स_रखो(&(IPCB(skb)->opt), 0, माप(IPCB(skb)->opt));
	IPCB(skb)->flags &= ~(IPSKB_XFRM_TUNNEL_SIZE | IPSKB_XFRM_TRANSFORMED
			    | IPSKB_REROUTED);
	skb_dst_set(skb, dst_clone(dst));

	__skb_push(skb, माप(*ip6h));
	skb_reset_network_header(skb);
	ip6h		  = ipv6_hdr(skb);
	ip6_flow_hdr(ip6h, prio, htonl(0));
	ip6h->payload_len = htons(skb->len);
	ip6h->nexthdr     = proto;
	ip6h->hop_limit   = ttl;
	ip6h->daddr	  = *daddr;
	ip6h->saddr	  = *saddr;
	ip6h->payload_len = htons(skb->len - माप(*ip6h));
पूर्ण

अटल पूर्णांक prepare4(काष्ठा rxe_pkt_info *pkt, काष्ठा sk_buff *skb)
अणु
	काष्ठा rxe_qp *qp = pkt->qp;
	काष्ठा dst_entry *dst;
	bool xnet = false;
	__be16 df = htons(IP_DF);
	काष्ठा rxe_av *av = rxe_get_av(pkt);
	काष्ठा in_addr *saddr = &av->sgid_addr._sockaddr_in.sin_addr;
	काष्ठा in_addr *daddr = &av->dgid_addr._sockaddr_in.sin_addr;

	dst = rxe_find_route(skb->dev, qp, av);
	अगर (!dst) अणु
		pr_err("Host not reachable\n");
		वापस -EHOSTUNREACH;
	पूर्ण

	prepare_udp_hdr(skb, cpu_to_be16(qp->src_port),
			cpu_to_be16(ROCE_V2_UDP_DPORT));

	prepare_ipv4_hdr(dst, skb, saddr->s_addr, daddr->s_addr, IPPROTO_UDP,
			 av->grh.traffic_class, av->grh.hop_limit, df, xnet);

	dst_release(dst);
	वापस 0;
पूर्ण

अटल पूर्णांक prepare6(काष्ठा rxe_pkt_info *pkt, काष्ठा sk_buff *skb)
अणु
	काष्ठा rxe_qp *qp = pkt->qp;
	काष्ठा dst_entry *dst;
	काष्ठा rxe_av *av = rxe_get_av(pkt);
	काष्ठा in6_addr *saddr = &av->sgid_addr._sockaddr_in6.sin6_addr;
	काष्ठा in6_addr *daddr = &av->dgid_addr._sockaddr_in6.sin6_addr;

	dst = rxe_find_route(skb->dev, qp, av);
	अगर (!dst) अणु
		pr_err("Host not reachable\n");
		वापस -EHOSTUNREACH;
	पूर्ण

	prepare_udp_hdr(skb, cpu_to_be16(qp->src_port),
			cpu_to_be16(ROCE_V2_UDP_DPORT));

	prepare_ipv6_hdr(dst, skb, saddr, daddr, IPPROTO_UDP,
			 av->grh.traffic_class,
			 av->grh.hop_limit);

	dst_release(dst);
	वापस 0;
पूर्ण

पूर्णांक rxe_prepare(काष्ठा rxe_pkt_info *pkt, काष्ठा sk_buff *skb, u32 *crc)
अणु
	पूर्णांक err = 0;

	अगर (skb->protocol == htons(ETH_P_IP))
		err = prepare4(pkt, skb);
	अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
		err = prepare6(pkt, skb);

	*crc = rxe_icrc_hdr(pkt, skb);

	अगर (ether_addr_equal(skb->dev->dev_addr, rxe_get_av(pkt)->dmac))
		pkt->mask |= RXE_LOOPBACK_MASK;

	वापस err;
पूर्ण

अटल व्योम rxe_skb_tx_dtor(काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = skb->sk;
	काष्ठा rxe_qp *qp = sk->sk_user_data;
	पूर्णांक skb_out = atomic_dec_वापस(&qp->skb_out);

	अगर (unlikely(qp->need_req_skb &&
		     skb_out < RXE_INFLIGHT_SKBS_PER_QP_LOW))
		rxe_run_task(&qp->req.task, 1);

	rxe_drop_ref(qp);
पूर्ण

पूर्णांक rxe_send(काष्ठा rxe_pkt_info *pkt, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	skb->deकाष्ठाor = rxe_skb_tx_dtor;
	skb->sk = pkt->qp->sk->sk;

	rxe_add_ref(pkt->qp);
	atomic_inc(&pkt->qp->skb_out);

	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		err = ip_local_out(dev_net(skb_dst(skb)->dev), skb->sk, skb);
	पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
		err = ip6_local_out(dev_net(skb_dst(skb)->dev), skb->sk, skb);
	पूर्ण अन्यथा अणु
		pr_err("Unknown layer 3 protocol: %d\n", skb->protocol);
		atomic_dec(&pkt->qp->skb_out);
		rxe_drop_ref(pkt->qp);
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(net_xmit_eval(err))) अणु
		pr_debug("error sending packet: %d\n", err);
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

/* fix up a send packet to match the packets
 * received from UDP beक्रमe looping them back
 */
व्योम rxe_loopback(काष्ठा sk_buff *skb)
अणु
	काष्ठा rxe_pkt_info *pkt = SKB_TO_PKT(skb);

	अगर (skb->protocol == htons(ETH_P_IP))
		skb_pull(skb, माप(काष्ठा iphdr));
	अन्यथा
		skb_pull(skb, माप(काष्ठा ipv6hdr));

	अगर (WARN_ON(!ib_device_try_get(&pkt->rxe->ib_dev)))
		kमुक्त_skb(skb);
	अन्यथा
		rxe_rcv(skb);
पूर्ण

काष्ठा sk_buff *rxe_init_packet(काष्ठा rxe_dev *rxe, काष्ठा rxe_av *av,
				पूर्णांक paylen, काष्ठा rxe_pkt_info *pkt)
अणु
	अचिन्हित पूर्णांक hdr_len;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा net_device *ndev;
	स्थिर काष्ठा ib_gid_attr *attr;
	स्थिर पूर्णांक port_num = 1;

	attr = rdma_get_gid_attr(&rxe->ib_dev, port_num, av->grh.sgid_index);
	अगर (IS_ERR(attr))
		वापस शून्य;

	अगर (av->network_type == RXE_NETWORK_TYPE_IPV4)
		hdr_len = ETH_HLEN + माप(काष्ठा udphdr) +
			माप(काष्ठा iphdr);
	अन्यथा
		hdr_len = ETH_HLEN + माप(काष्ठा udphdr) +
			माप(काष्ठा ipv6hdr);

	rcu_पढ़ो_lock();
	ndev = rdma_पढ़ो_gid_attr_ndev_rcu(attr);
	अगर (IS_ERR(ndev)) अणु
		rcu_पढ़ो_unlock();
		जाओ out;
	पूर्ण
	skb = alloc_skb(paylen + hdr_len + LL_RESERVED_SPACE(ndev),
			GFP_ATOMIC);

	अगर (unlikely(!skb)) अणु
		rcu_पढ़ो_unlock();
		जाओ out;
	पूर्ण

	skb_reserve(skb, hdr_len + LL_RESERVED_SPACE(ndev));

	/* FIXME: hold reference to this netdev until lअगरe of this skb. */
	skb->dev	= ndev;
	rcu_पढ़ो_unlock();

	अगर (av->network_type == RXE_NETWORK_TYPE_IPV4)
		skb->protocol = htons(ETH_P_IP);
	अन्यथा
		skb->protocol = htons(ETH_P_IPV6);

	pkt->rxe	= rxe;
	pkt->port_num	= port_num;
	pkt->hdr	= skb_put_zero(skb, paylen);
	pkt->mask	|= RXE_GRH_MASK;

out:
	rdma_put_gid_attr(attr);
	वापस skb;
पूर्ण

/*
 * this is required by rxe_cfg to match rxe devices in
 * /sys/class/infiniband up with their underlying ethernet devices
 */
स्थिर अक्षर *rxe_parent_name(काष्ठा rxe_dev *rxe, अचिन्हित पूर्णांक port_num)
अणु
	वापस rxe->ndev->name;
पूर्ण

पूर्णांक rxe_net_add(स्थिर अक्षर *ibdev_name, काष्ठा net_device *ndev)
अणु
	पूर्णांक err;
	काष्ठा rxe_dev *rxe = शून्य;

	rxe = ib_alloc_device(rxe_dev, ib_dev);
	अगर (!rxe)
		वापस -ENOMEM;

	rxe->ndev = ndev;

	err = rxe_add(rxe, ndev->mtu, ibdev_name);
	अगर (err) अणु
		ib_dealloc_device(&rxe->ib_dev);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rxe_port_event(काष्ठा rxe_dev *rxe,
			   क्रमागत ib_event_type event)
अणु
	काष्ठा ib_event ev;

	ev.device = &rxe->ib_dev;
	ev.element.port_num = 1;
	ev.event = event;

	ib_dispatch_event(&ev);
पूर्ण

/* Caller must hold net_info_lock */
व्योम rxe_port_up(काष्ठा rxe_dev *rxe)
अणु
	काष्ठा rxe_port *port;

	port = &rxe->port;
	port->attr.state = IB_PORT_ACTIVE;

	rxe_port_event(rxe, IB_EVENT_PORT_ACTIVE);
	dev_info(&rxe->ib_dev.dev, "set active\n");
पूर्ण

/* Caller must hold net_info_lock */
व्योम rxe_port_करोwn(काष्ठा rxe_dev *rxe)
अणु
	काष्ठा rxe_port *port;

	port = &rxe->port;
	port->attr.state = IB_PORT_DOWN;

	rxe_port_event(rxe, IB_EVENT_PORT_ERR);
	rxe_counter_inc(rxe, RXE_CNT_LINK_DOWNED);
	dev_info(&rxe->ib_dev.dev, "set down\n");
पूर्ण

व्योम rxe_set_port_state(काष्ठा rxe_dev *rxe)
अणु
	अगर (netअगर_running(rxe->ndev) && netअगर_carrier_ok(rxe->ndev))
		rxe_port_up(rxe);
	अन्यथा
		rxe_port_करोwn(rxe);
पूर्ण

अटल पूर्णांक rxe_notअगरy(काष्ठा notअगरier_block *not_blk,
		      अचिन्हित दीर्घ event,
		      व्योम *arg)
अणु
	काष्ठा net_device *ndev = netdev_notअगरier_info_to_dev(arg);
	काष्ठा rxe_dev *rxe = rxe_get_dev_from_net(ndev);

	अगर (!rxe)
		वापस NOTIFY_OK;

	चयन (event) अणु
	हाल NETDEV_UNREGISTER:
		ib_unरेजिस्टर_device_queued(&rxe->ib_dev);
		अवरोध;
	हाल NETDEV_UP:
		rxe_port_up(rxe);
		अवरोध;
	हाल NETDEV_DOWN:
		rxe_port_करोwn(rxe);
		अवरोध;
	हाल NETDEV_CHANGEMTU:
		pr_info("%s changed mtu to %d\n", ndev->name, ndev->mtu);
		rxe_set_mtu(rxe, ndev->mtu);
		अवरोध;
	हाल NETDEV_CHANGE:
		rxe_set_port_state(rxe);
		अवरोध;
	हाल NETDEV_REBOOT:
	हाल NETDEV_GOING_DOWN:
	हाल NETDEV_CHANGEADDR:
	हाल NETDEV_CHANGENAME:
	हाल NETDEV_FEAT_CHANGE:
	शेष:
		pr_info("ignoring netdev event = %ld for %s\n",
			event, ndev->name);
		अवरोध;
	पूर्ण

	ib_device_put(&rxe->ib_dev);
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block rxe_net_notअगरier = अणु
	.notअगरier_call = rxe_notअगरy,
पूर्ण;

अटल पूर्णांक rxe_net_ipv4_init(व्योम)
अणु
	recv_sockets.sk4 = rxe_setup_udp_tunnel(&init_net,
				htons(ROCE_V2_UDP_DPORT), false);
	अगर (IS_ERR(recv_sockets.sk4)) अणु
		recv_sockets.sk4 = शून्य;
		pr_err("Failed to create IPv4 UDP tunnel\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rxe_net_ipv6_init(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)

	recv_sockets.sk6 = rxe_setup_udp_tunnel(&init_net,
						htons(ROCE_V2_UDP_DPORT), true);
	अगर (IS_ERR(recv_sockets.sk6)) अणु
		recv_sockets.sk6 = शून्य;
		pr_err("Failed to create IPv6 UDP tunnel\n");
		वापस -1;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

व्योम rxe_net_निकास(व्योम)
अणु
	rxe_release_udp_tunnel(recv_sockets.sk6);
	rxe_release_udp_tunnel(recv_sockets.sk4);
	unरेजिस्टर_netdevice_notअगरier(&rxe_net_notअगरier);
पूर्ण

पूर्णांक rxe_net_init(व्योम)
अणु
	पूर्णांक err;

	recv_sockets.sk6 = शून्य;

	err = rxe_net_ipv4_init();
	अगर (err)
		वापस err;
	err = rxe_net_ipv6_init();
	अगर (err)
		जाओ err_out;
	err = रेजिस्टर_netdevice_notअगरier(&rxe_net_notअगरier);
	अगर (err) अणु
		pr_err("Failed to register netdev notifier\n");
		जाओ err_out;
	पूर्ण
	वापस 0;
err_out:
	rxe_net_निकास();
	वापस err;
पूर्ण
