<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* GTP according to GSM TS 09.60 / 3GPP TS 29.060
 *
 * (C) 2012-2014 by sysmocom - s.f.m.c. GmbH
 * (C) 2016 by Pablo Neira Ayuso <pablo@netfilter.org>
 *
 * Author: Harald Welte <hwelte@sysmocom.de>
 *	   Pablo Neira Ayuso <pablo@netfilter.org>
 *	   Andreas Schultz <aschultz@travelping.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/udp.h>
#समावेश <linux/rculist.h>
#समावेश <linux/jhash.h>
#समावेश <linux/अगर_tunnel.h>
#समावेश <linux/net.h>
#समावेश <linux/file.h>
#समावेश <linux/gtp.h>

#समावेश <net/net_namespace.h>
#समावेश <net/protocol.h>
#समावेश <net/ip.h>
#समावेश <net/udp.h>
#समावेश <net/udp_tunnel.h>
#समावेश <net/icmp.h>
#समावेश <net/xfrm.h>
#समावेश <net/genetlink.h>
#समावेश <net/netns/generic.h>
#समावेश <net/gtp.h>

/* An active session क्रम the subscriber. */
काष्ठा pdp_ctx अणु
	काष्ठा hlist_node	hlist_tid;
	काष्ठा hlist_node	hlist_addr;

	जोड़ अणु
		काष्ठा अणु
			u64	tid;
			u16	flow;
		पूर्ण v0;
		काष्ठा अणु
			u32	i_tei;
			u32	o_tei;
		पूर्ण v1;
	पूर्ण u;
	u8			gtp_version;
	u16			af;

	काष्ठा in_addr		ms_addr_ip4;
	काष्ठा in_addr		peer_addr_ip4;

	काष्ठा sock		*sk;
	काष्ठा net_device       *dev;

	atomic_t		tx_seq;
	काष्ठा rcu_head		rcu_head;
पूर्ण;

/* One instance of the GTP device. */
काष्ठा gtp_dev अणु
	काष्ठा list_head	list;

	काष्ठा sock		*sk0;
	काष्ठा sock		*sk1u;

	काष्ठा net_device	*dev;

	अचिन्हित पूर्णांक		role;
	अचिन्हित पूर्णांक		hash_size;
	काष्ठा hlist_head	*tid_hash;
	काष्ठा hlist_head	*addr_hash;
पूर्ण;

अटल अचिन्हित पूर्णांक gtp_net_id __पढ़ो_mostly;

काष्ठा gtp_net अणु
	काष्ठा list_head gtp_dev_list;
पूर्ण;

अटल u32 gtp_h_initval;

अटल व्योम pdp_context_delete(काष्ठा pdp_ctx *pctx);

अटल अंतरभूत u32 gtp0_hashfn(u64 tid)
अणु
	u32 *tid32 = (u32 *) &tid;
	वापस jhash_2words(tid32[0], tid32[1], gtp_h_initval);
पूर्ण

अटल अंतरभूत u32 gtp1u_hashfn(u32 tid)
अणु
	वापस jhash_1word(tid, gtp_h_initval);
पूर्ण

अटल अंतरभूत u32 ipv4_hashfn(__be32 ip)
अणु
	वापस jhash_1word((__क्रमce u32)ip, gtp_h_initval);
पूर्ण

/* Resolve a PDP context काष्ठाure based on the 64bit TID. */
अटल काष्ठा pdp_ctx *gtp0_pdp_find(काष्ठा gtp_dev *gtp, u64 tid)
अणु
	काष्ठा hlist_head *head;
	काष्ठा pdp_ctx *pdp;

	head = &gtp->tid_hash[gtp0_hashfn(tid) % gtp->hash_size];

	hlist_क्रम_each_entry_rcu(pdp, head, hlist_tid) अणु
		अगर (pdp->gtp_version == GTP_V0 &&
		    pdp->u.v0.tid == tid)
			वापस pdp;
	पूर्ण
	वापस शून्य;
पूर्ण

/* Resolve a PDP context काष्ठाure based on the 32bit TEI. */
अटल काष्ठा pdp_ctx *gtp1_pdp_find(काष्ठा gtp_dev *gtp, u32 tid)
अणु
	काष्ठा hlist_head *head;
	काष्ठा pdp_ctx *pdp;

	head = &gtp->tid_hash[gtp1u_hashfn(tid) % gtp->hash_size];

	hlist_क्रम_each_entry_rcu(pdp, head, hlist_tid) अणु
		अगर (pdp->gtp_version == GTP_V1 &&
		    pdp->u.v1.i_tei == tid)
			वापस pdp;
	पूर्ण
	वापस शून्य;
पूर्ण

/* Resolve a PDP context based on IPv4 address of MS. */
अटल काष्ठा pdp_ctx *ipv4_pdp_find(काष्ठा gtp_dev *gtp, __be32 ms_addr)
अणु
	काष्ठा hlist_head *head;
	काष्ठा pdp_ctx *pdp;

	head = &gtp->addr_hash[ipv4_hashfn(ms_addr) % gtp->hash_size];

	hlist_क्रम_each_entry_rcu(pdp, head, hlist_addr) अणु
		अगर (pdp->af == AF_INET &&
		    pdp->ms_addr_ip4.s_addr == ms_addr)
			वापस pdp;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool gtp_check_ms_ipv4(काष्ठा sk_buff *skb, काष्ठा pdp_ctx *pctx,
				  अचिन्हित पूर्णांक hdrlen, अचिन्हित पूर्णांक role)
अणु
	काष्ठा iphdr *iph;

	अगर (!pskb_may_pull(skb, hdrlen + माप(काष्ठा iphdr)))
		वापस false;

	iph = (काष्ठा iphdr *)(skb->data + hdrlen);

	अगर (role == GTP_ROLE_SGSN)
		वापस iph->daddr == pctx->ms_addr_ip4.s_addr;
	अन्यथा
		वापस iph->saddr == pctx->ms_addr_ip4.s_addr;
पूर्ण

/* Check अगर the inner IP address in this packet is asचिन्हित to any
 * existing mobile subscriber.
 */
अटल bool gtp_check_ms(काष्ठा sk_buff *skb, काष्ठा pdp_ctx *pctx,
			     अचिन्हित पूर्णांक hdrlen, अचिन्हित पूर्णांक role)
अणु
	चयन (ntohs(skb->protocol)) अणु
	हाल ETH_P_IP:
		वापस gtp_check_ms_ipv4(skb, pctx, hdrlen, role);
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक gtp_rx(काष्ठा pdp_ctx *pctx, काष्ठा sk_buff *skb,
			अचिन्हित पूर्णांक hdrlen, अचिन्हित पूर्णांक role)
अणु
	अगर (!gtp_check_ms(skb, pctx, hdrlen, role)) अणु
		netdev_dbg(pctx->dev, "No PDP ctx for this MS\n");
		वापस 1;
	पूर्ण

	/* Get rid of the GTP + UDP headers. */
	अगर (iptunnel_pull_header(skb, hdrlen, skb->protocol,
			 !net_eq(sock_net(pctx->sk), dev_net(pctx->dev)))) अणु
		pctx->dev->stats.rx_length_errors++;
		जाओ err;
	पूर्ण

	netdev_dbg(pctx->dev, "forwarding packet from GGSN to uplink\n");

	/* Now that the UDP and the GTP header have been हटाओd, set up the
	 * new network header. This is required by the upper layer to
	 * calculate the transport header.
	 */
	skb_reset_network_header(skb);

	skb->dev = pctx->dev;

	dev_sw_netstats_rx_add(pctx->dev, skb->len);

	netअगर_rx(skb);
	वापस 0;

err:
	pctx->dev->stats.rx_dropped++;
	वापस -1;
पूर्ण

/* 1 means pass up to the stack, -1 means drop and 0 means decapsulated. */
अटल पूर्णांक gtp0_udp_encap_recv(काष्ठा gtp_dev *gtp, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक hdrlen = माप(काष्ठा udphdr) +
			      माप(काष्ठा gtp0_header);
	काष्ठा gtp0_header *gtp0;
	काष्ठा pdp_ctx *pctx;

	अगर (!pskb_may_pull(skb, hdrlen))
		वापस -1;

	gtp0 = (काष्ठा gtp0_header *)(skb->data + माप(काष्ठा udphdr));

	अगर ((gtp0->flags >> 5) != GTP_V0)
		वापस 1;

	अगर (gtp0->type != GTP_TPDU)
		वापस 1;

	pctx = gtp0_pdp_find(gtp, be64_to_cpu(gtp0->tid));
	अगर (!pctx) अणु
		netdev_dbg(gtp->dev, "No PDP ctx to decap skb=%p\n", skb);
		वापस 1;
	पूर्ण

	वापस gtp_rx(pctx, skb, hdrlen, gtp->role);
पूर्ण

अटल पूर्णांक gtp1u_udp_encap_recv(काष्ठा gtp_dev *gtp, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक hdrlen = माप(काष्ठा udphdr) +
			      माप(काष्ठा gtp1_header);
	काष्ठा gtp1_header *gtp1;
	काष्ठा pdp_ctx *pctx;

	अगर (!pskb_may_pull(skb, hdrlen))
		वापस -1;

	gtp1 = (काष्ठा gtp1_header *)(skb->data + माप(काष्ठा udphdr));

	अगर ((gtp1->flags >> 5) != GTP_V1)
		वापस 1;

	अगर (gtp1->type != GTP_TPDU)
		वापस 1;

	/* From 29.060: "This field shall be present अगर and only अगर any one or
	 * more of the S, PN and E flags are set.".
	 *
	 * If any of the bit is set, then the reमुख्यing ones also have to be
	 * set.
	 */
	अगर (gtp1->flags & GTP1_F_MASK)
		hdrlen += 4;

	/* Make sure the header is larger enough, including extensions. */
	अगर (!pskb_may_pull(skb, hdrlen))
		वापस -1;

	gtp1 = (काष्ठा gtp1_header *)(skb->data + माप(काष्ठा udphdr));

	pctx = gtp1_pdp_find(gtp, ntohl(gtp1->tid));
	अगर (!pctx) अणु
		netdev_dbg(gtp->dev, "No PDP ctx to decap skb=%p\n", skb);
		वापस 1;
	पूर्ण

	वापस gtp_rx(pctx, skb, hdrlen, gtp->role);
पूर्ण

अटल व्योम __gtp_encap_destroy(काष्ठा sock *sk)
अणु
	काष्ठा gtp_dev *gtp;

	lock_sock(sk);
	gtp = sk->sk_user_data;
	अगर (gtp) अणु
		अगर (gtp->sk0 == sk)
			gtp->sk0 = शून्य;
		अन्यथा
			gtp->sk1u = शून्य;
		udp_sk(sk)->encap_type = 0;
		rcu_assign_sk_user_data(sk, शून्य);
		sock_put(sk);
	पूर्ण
	release_sock(sk);
पूर्ण

अटल व्योम gtp_encap_destroy(काष्ठा sock *sk)
अणु
	rtnl_lock();
	__gtp_encap_destroy(sk);
	rtnl_unlock();
पूर्ण

अटल व्योम gtp_encap_disable_sock(काष्ठा sock *sk)
अणु
	अगर (!sk)
		वापस;

	__gtp_encap_destroy(sk);
पूर्ण

अटल व्योम gtp_encap_disable(काष्ठा gtp_dev *gtp)
अणु
	gtp_encap_disable_sock(gtp->sk0);
	gtp_encap_disable_sock(gtp->sk1u);
पूर्ण

/* UDP encapsulation receive handler. See net/ipv4/udp.c.
 * Return codes: 0: success, <0: error, >0: pass up to userspace UDP socket.
 */
अटल पूर्णांक gtp_encap_recv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा gtp_dev *gtp;
	पूर्णांक ret = 0;

	gtp = rcu_dereference_sk_user_data(sk);
	अगर (!gtp)
		वापस 1;

	netdev_dbg(gtp->dev, "encap_recv sk=%p\n", sk);

	चयन (udp_sk(sk)->encap_type) अणु
	हाल UDP_ENCAP_GTP0:
		netdev_dbg(gtp->dev, "received GTP0 packet\n");
		ret = gtp0_udp_encap_recv(gtp, skb);
		अवरोध;
	हाल UDP_ENCAP_GTP1U:
		netdev_dbg(gtp->dev, "received GTP1U packet\n");
		ret = gtp1u_udp_encap_recv(gtp, skb);
		अवरोध;
	शेष:
		ret = -1; /* Shouldn't happen. */
	पूर्ण

	चयन (ret) अणु
	हाल 1:
		netdev_dbg(gtp->dev, "pass up to the process\n");
		अवरोध;
	हाल 0:
		अवरोध;
	हाल -1:
		netdev_dbg(gtp->dev, "GTP packet has been dropped\n");
		kमुक्त_skb(skb);
		ret = 0;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक gtp_dev_init(काष्ठा net_device *dev)
अणु
	काष्ठा gtp_dev *gtp = netdev_priv(dev);

	gtp->dev = dev;

	dev->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
	अगर (!dev->tstats)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम gtp_dev_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा gtp_dev *gtp = netdev_priv(dev);

	gtp_encap_disable(gtp);
	मुक्त_percpu(dev->tstats);
पूर्ण

अटल काष्ठा rtable *ip4_route_output_gtp(काष्ठा flowi4 *fl4,
					   स्थिर काष्ठा sock *sk,
					   __be32 daddr)
अणु
	स_रखो(fl4, 0, माप(*fl4));
	fl4->flowi4_oअगर		= sk->sk_bound_dev_अगर;
	fl4->daddr		= daddr;
	fl4->saddr		= inet_sk(sk)->inet_saddr;
	fl4->flowi4_tos		= RT_CONN_FLAGS(sk);
	fl4->flowi4_proto	= sk->sk_protocol;

	वापस ip_route_output_key(sock_net(sk), fl4);
पूर्ण

अटल अंतरभूत व्योम gtp0_push_header(काष्ठा sk_buff *skb, काष्ठा pdp_ctx *pctx)
अणु
	पूर्णांक payload_len = skb->len;
	काष्ठा gtp0_header *gtp0;

	gtp0 = skb_push(skb, माप(*gtp0));

	gtp0->flags	= 0x1e; /* v0, GTP-non-prime. */
	gtp0->type	= GTP_TPDU;
	gtp0->length	= htons(payload_len);
	gtp0->seq	= htons((atomic_inc_वापस(&pctx->tx_seq) - 1) % 0xffff);
	gtp0->flow	= htons(pctx->u.v0.flow);
	gtp0->number	= 0xff;
	gtp0->spare[0]	= gtp0->spare[1] = gtp0->spare[2] = 0xff;
	gtp0->tid	= cpu_to_be64(pctx->u.v0.tid);
पूर्ण

अटल अंतरभूत व्योम gtp1_push_header(काष्ठा sk_buff *skb, काष्ठा pdp_ctx *pctx)
अणु
	पूर्णांक payload_len = skb->len;
	काष्ठा gtp1_header *gtp1;

	gtp1 = skb_push(skb, माप(*gtp1));

	/* Bits    8  7  6  5  4  3  2	1
	 *	  +--+--+--+--+--+--+--+--+
	 *	  |version |PT| 0| E| S|PN|
	 *	  +--+--+--+--+--+--+--+--+
	 *	    0  0  1  1	1  0  0  0
	 */
	gtp1->flags	= 0x30; /* v1, GTP-non-prime. */
	gtp1->type	= GTP_TPDU;
	gtp1->length	= htons(payload_len);
	gtp1->tid	= htonl(pctx->u.v1.o_tei);

	/* TODO: Suppport क्रम extension header, sequence number and N-PDU.
	 *	 Update the length field अगर any of them is available.
	 */
पूर्ण

काष्ठा gtp_pktinfo अणु
	काष्ठा sock		*sk;
	काष्ठा iphdr		*iph;
	काष्ठा flowi4		fl4;
	काष्ठा rtable		*rt;
	काष्ठा pdp_ctx		*pctx;
	काष्ठा net_device	*dev;
	__be16			gtph_port;
पूर्ण;

अटल व्योम gtp_push_header(काष्ठा sk_buff *skb, काष्ठा gtp_pktinfo *pktinfo)
अणु
	चयन (pktinfo->pctx->gtp_version) अणु
	हाल GTP_V0:
		pktinfo->gtph_port = htons(GTP0_PORT);
		gtp0_push_header(skb, pktinfo->pctx);
		अवरोध;
	हाल GTP_V1:
		pktinfo->gtph_port = htons(GTP1U_PORT);
		gtp1_push_header(skb, pktinfo->pctx);
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम gtp_set_pktinfo_ipv4(काष्ठा gtp_pktinfo *pktinfo,
					काष्ठा sock *sk, काष्ठा iphdr *iph,
					काष्ठा pdp_ctx *pctx, काष्ठा rtable *rt,
					काष्ठा flowi4 *fl4,
					काष्ठा net_device *dev)
अणु
	pktinfo->sk	= sk;
	pktinfo->iph	= iph;
	pktinfo->pctx	= pctx;
	pktinfo->rt	= rt;
	pktinfo->fl4	= *fl4;
	pktinfo->dev	= dev;
पूर्ण

अटल पूर्णांक gtp_build_skb_ip4(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			     काष्ठा gtp_pktinfo *pktinfo)
अणु
	काष्ठा gtp_dev *gtp = netdev_priv(dev);
	काष्ठा pdp_ctx *pctx;
	काष्ठा rtable *rt;
	काष्ठा flowi4 fl4;
	काष्ठा iphdr *iph;
	__be16 df;
	पूर्णांक mtu;

	/* Read the IP destination address and resolve the PDP context.
	 * Prepend PDP header with TEI/TID from PDP ctx.
	 */
	iph = ip_hdr(skb);
	अगर (gtp->role == GTP_ROLE_SGSN)
		pctx = ipv4_pdp_find(gtp, iph->saddr);
	अन्यथा
		pctx = ipv4_pdp_find(gtp, iph->daddr);

	अगर (!pctx) अणु
		netdev_dbg(dev, "no PDP ctx found for %pI4, skip\n",
			   &iph->daddr);
		वापस -ENOENT;
	पूर्ण
	netdev_dbg(dev, "found PDP context %p\n", pctx);

	rt = ip4_route_output_gtp(&fl4, pctx->sk, pctx->peer_addr_ip4.s_addr);
	अगर (IS_ERR(rt)) अणु
		netdev_dbg(dev, "no route to SSGN %pI4\n",
			   &pctx->peer_addr_ip4.s_addr);
		dev->stats.tx_carrier_errors++;
		जाओ err;
	पूर्ण

	अगर (rt->dst.dev == dev) अणु
		netdev_dbg(dev, "circular route to SSGN %pI4\n",
			   &pctx->peer_addr_ip4.s_addr);
		dev->stats.collisions++;
		जाओ err_rt;
	पूर्ण

	/* This is similar to tnl_update_pmtu(). */
	df = iph->frag_off;
	अगर (df) अणु
		mtu = dst_mtu(&rt->dst) - dev->hard_header_len -
			माप(काष्ठा iphdr) - माप(काष्ठा udphdr);
		चयन (pctx->gtp_version) अणु
		हाल GTP_V0:
			mtu -= माप(काष्ठा gtp0_header);
			अवरोध;
		हाल GTP_V1:
			mtu -= माप(काष्ठा gtp1_header);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		mtu = dst_mtu(&rt->dst);
	पूर्ण

	rt->dst.ops->update_pmtu(&rt->dst, शून्य, skb, mtu, false);

	अगर (!skb_is_gso(skb) && (iph->frag_off & htons(IP_DF)) &&
	    mtu < ntohs(iph->tot_len)) अणु
		netdev_dbg(dev, "packet too big, fragmentation needed\n");
		icmp_nकरो_send(skb, ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED,
			      htonl(mtu));
		जाओ err_rt;
	पूर्ण

	gtp_set_pktinfo_ipv4(pktinfo, pctx->sk, iph, pctx, rt, &fl4, dev);
	gtp_push_header(skb, pktinfo);

	वापस 0;
err_rt:
	ip_rt_put(rt);
err:
	वापस -EBADMSG;
पूर्ण

अटल netdev_tx_t gtp_dev_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक proto = ntohs(skb->protocol);
	काष्ठा gtp_pktinfo pktinfo;
	पूर्णांक err;

	/* Ensure there is sufficient headroom. */
	अगर (skb_cow_head(skb, dev->needed_headroom))
		जाओ tx_err;

	skb_reset_inner_headers(skb);

	/* PDP context lookups in gtp_build_skb_*() need rcu पढ़ो-side lock. */
	rcu_पढ़ो_lock();
	चयन (proto) अणु
	हाल ETH_P_IP:
		err = gtp_build_skb_ip4(skb, dev, &pktinfo);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (err < 0)
		जाओ tx_err;

	चयन (proto) अणु
	हाल ETH_P_IP:
		netdev_dbg(pktinfo.dev, "gtp -> IP src: %pI4 dst: %pI4\n",
			   &pktinfo.iph->saddr, &pktinfo.iph->daddr);
		udp_tunnel_xmit_skb(pktinfo.rt, pktinfo.sk, skb,
				    pktinfo.fl4.saddr, pktinfo.fl4.daddr,
				    pktinfo.iph->tos,
				    ip4_dst_hoplimit(&pktinfo.rt->dst),
				    0,
				    pktinfo.gtph_port, pktinfo.gtph_port,
				    !net_eq(sock_net(pktinfo.pctx->sk),
					    dev_net(dev)),
				    false);
		अवरोध;
	पूर्ण

	वापस NETDEV_TX_OK;
tx_err:
	dev->stats.tx_errors++;
	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा net_device_ops gtp_netdev_ops = अणु
	.nकरो_init		= gtp_dev_init,
	.nकरो_uninit		= gtp_dev_uninit,
	.nकरो_start_xmit		= gtp_dev_xmit,
	.nकरो_get_stats64	= dev_get_tstats64,
पूर्ण;

अटल स्थिर काष्ठा device_type gtp_type = अणु
	.name = "gtp",
पूर्ण;

अटल व्योम gtp_link_setup(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक max_gtp_header_len = माप(काष्ठा iphdr) +
					  माप(काष्ठा udphdr) +
					  माप(काष्ठा gtp0_header);

	dev->netdev_ops		= &gtp_netdev_ops;
	dev->needs_मुक्त_netdev	= true;
	SET_NETDEV_DEVTYPE(dev, &gtp_type);

	dev->hard_header_len = 0;
	dev->addr_len = 0;
	dev->mtu = ETH_DATA_LEN - max_gtp_header_len;

	/* Zero header length. */
	dev->type = ARPHRD_NONE;
	dev->flags = IFF_POINTOPOINT | IFF_NOARP | IFF_MULTICAST;

	dev->priv_flags	|= IFF_NO_QUEUE;
	dev->features	|= NETIF_F_LLTX;
	netअगर_keep_dst(dev);

	dev->needed_headroom	= LL_MAX_HEADER + max_gtp_header_len;
पूर्ण

अटल पूर्णांक gtp_hashtable_new(काष्ठा gtp_dev *gtp, पूर्णांक hsize);
अटल पूर्णांक gtp_encap_enable(काष्ठा gtp_dev *gtp, काष्ठा nlattr *data[]);

अटल व्योम gtp_deकाष्ठाor(काष्ठा net_device *dev)
अणु
	काष्ठा gtp_dev *gtp = netdev_priv(dev);

	kमुक्त(gtp->addr_hash);
	kमुक्त(gtp->tid_hash);
पूर्ण

अटल पूर्णांक gtp_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
		       काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा gtp_dev *gtp;
	काष्ठा gtp_net *gn;
	पूर्णांक hashsize, err;

	अगर (!data[IFLA_GTP_FD0] && !data[IFLA_GTP_FD1])
		वापस -EINVAL;

	gtp = netdev_priv(dev);

	अगर (!data[IFLA_GTP_PDP_HASHSIZE]) अणु
		hashsize = 1024;
	पूर्ण अन्यथा अणु
		hashsize = nla_get_u32(data[IFLA_GTP_PDP_HASHSIZE]);
		अगर (!hashsize)
			hashsize = 1024;
	पूर्ण

	err = gtp_hashtable_new(gtp, hashsize);
	अगर (err < 0)
		वापस err;

	err = gtp_encap_enable(gtp, data);
	अगर (err < 0)
		जाओ out_hashtable;

	err = रेजिस्टर_netdevice(dev);
	अगर (err < 0) अणु
		netdev_dbg(dev, "failed to register new netdev %d\n", err);
		जाओ out_encap;
	पूर्ण

	gn = net_generic(dev_net(dev), gtp_net_id);
	list_add_rcu(&gtp->list, &gn->gtp_dev_list);
	dev->priv_deकाष्ठाor = gtp_deकाष्ठाor;

	netdev_dbg(dev, "registered new GTP interface\n");

	वापस 0;

out_encap:
	gtp_encap_disable(gtp);
out_hashtable:
	kमुक्त(gtp->addr_hash);
	kमुक्त(gtp->tid_hash);
	वापस err;
पूर्ण

अटल व्योम gtp_dellink(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	काष्ठा gtp_dev *gtp = netdev_priv(dev);
	काष्ठा pdp_ctx *pctx;
	पूर्णांक i;

	क्रम (i = 0; i < gtp->hash_size; i++)
		hlist_क्रम_each_entry_rcu(pctx, &gtp->tid_hash[i], hlist_tid)
			pdp_context_delete(pctx);

	list_del_rcu(&gtp->list);
	unरेजिस्टर_netdevice_queue(dev, head);
पूर्ण

अटल स्थिर काष्ठा nla_policy gtp_policy[IFLA_GTP_MAX + 1] = अणु
	[IFLA_GTP_FD0]			= अणु .type = NLA_U32 पूर्ण,
	[IFLA_GTP_FD1]			= अणु .type = NLA_U32 पूर्ण,
	[IFLA_GTP_PDP_HASHSIZE]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_GTP_ROLE]			= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक gtp_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			काष्ठा netlink_ext_ack *extack)
अणु
	अगर (!data)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल माप_प्रकार gtp_get_size(स्थिर काष्ठा net_device *dev)
अणु
	वापस nla_total_size(माप(__u32)) + /* IFLA_GTP_PDP_HASHSIZE */
		nla_total_size(माप(__u32)); /* IFLA_GTP_ROLE */
पूर्ण

अटल पूर्णांक gtp_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा gtp_dev *gtp = netdev_priv(dev);

	अगर (nla_put_u32(skb, IFLA_GTP_PDP_HASHSIZE, gtp->hash_size))
		जाओ nla_put_failure;
	अगर (nla_put_u32(skb, IFLA_GTP_ROLE, gtp->role))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल काष्ठा rtnl_link_ops gtp_link_ops __पढ़ो_mostly = अणु
	.kind		= "gtp",
	.maxtype	= IFLA_GTP_MAX,
	.policy		= gtp_policy,
	.priv_size	= माप(काष्ठा gtp_dev),
	.setup		= gtp_link_setup,
	.validate	= gtp_validate,
	.newlink	= gtp_newlink,
	.dellink	= gtp_dellink,
	.get_size	= gtp_get_size,
	.fill_info	= gtp_fill_info,
पूर्ण;

अटल पूर्णांक gtp_hashtable_new(काष्ठा gtp_dev *gtp, पूर्णांक hsize)
अणु
	पूर्णांक i;

	gtp->addr_hash = kदो_स्मृति_array(hsize, माप(काष्ठा hlist_head),
				       GFP_KERNEL | __GFP_NOWARN);
	अगर (gtp->addr_hash == शून्य)
		वापस -ENOMEM;

	gtp->tid_hash = kदो_स्मृति_array(hsize, माप(काष्ठा hlist_head),
				      GFP_KERNEL | __GFP_NOWARN);
	अगर (gtp->tid_hash == शून्य)
		जाओ err1;

	gtp->hash_size = hsize;

	क्रम (i = 0; i < hsize; i++) अणु
		INIT_HLIST_HEAD(&gtp->addr_hash[i]);
		INIT_HLIST_HEAD(&gtp->tid_hash[i]);
	पूर्ण
	वापस 0;
err1:
	kमुक्त(gtp->addr_hash);
	वापस -ENOMEM;
पूर्ण

अटल काष्ठा sock *gtp_encap_enable_socket(पूर्णांक fd, पूर्णांक type,
					    काष्ठा gtp_dev *gtp)
अणु
	काष्ठा udp_tunnel_sock_cfg tuncfg = अणुशून्यपूर्ण;
	काष्ठा socket *sock;
	काष्ठा sock *sk;
	पूर्णांक err;

	pr_debug("enable gtp on %d, %d\n", fd, type);

	sock = sockfd_lookup(fd, &err);
	अगर (!sock) अणु
		pr_debug("gtp socket fd=%d not found\n", fd);
		वापस शून्य;
	पूर्ण

	sk = sock->sk;
	अगर (sk->sk_protocol != IPPROTO_UDP ||
	    sk->sk_type != SOCK_DGRAM ||
	    (sk->sk_family != AF_INET && sk->sk_family != AF_INET6)) अणु
		pr_debug("socket fd=%d not UDP\n", fd);
		sk = ERR_PTR(-EINVAL);
		जाओ out_sock;
	पूर्ण

	lock_sock(sk);
	अगर (sk->sk_user_data) अणु
		sk = ERR_PTR(-EBUSY);
		जाओ out_rel_sock;
	पूर्ण

	sock_hold(sk);

	tuncfg.sk_user_data = gtp;
	tuncfg.encap_type = type;
	tuncfg.encap_rcv = gtp_encap_recv;
	tuncfg.encap_destroy = gtp_encap_destroy;

	setup_udp_tunnel_sock(sock_net(sock->sk), sock, &tuncfg);

out_rel_sock:
	release_sock(sock->sk);
out_sock:
	sockfd_put(sock);
	वापस sk;
पूर्ण

अटल पूर्णांक gtp_encap_enable(काष्ठा gtp_dev *gtp, काष्ठा nlattr *data[])
अणु
	काष्ठा sock *sk1u = शून्य;
	काष्ठा sock *sk0 = शून्य;
	अचिन्हित पूर्णांक role = GTP_ROLE_GGSN;

	अगर (data[IFLA_GTP_FD0]) अणु
		u32 fd0 = nla_get_u32(data[IFLA_GTP_FD0]);

		sk0 = gtp_encap_enable_socket(fd0, UDP_ENCAP_GTP0, gtp);
		अगर (IS_ERR(sk0))
			वापस PTR_ERR(sk0);
	पूर्ण

	अगर (data[IFLA_GTP_FD1]) अणु
		u32 fd1 = nla_get_u32(data[IFLA_GTP_FD1]);

		sk1u = gtp_encap_enable_socket(fd1, UDP_ENCAP_GTP1U, gtp);
		अगर (IS_ERR(sk1u)) अणु
			gtp_encap_disable_sock(sk0);
			वापस PTR_ERR(sk1u);
		पूर्ण
	पूर्ण

	अगर (data[IFLA_GTP_ROLE]) अणु
		role = nla_get_u32(data[IFLA_GTP_ROLE]);
		अगर (role > GTP_ROLE_SGSN) अणु
			gtp_encap_disable_sock(sk0);
			gtp_encap_disable_sock(sk1u);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	gtp->sk0 = sk0;
	gtp->sk1u = sk1u;
	gtp->role = role;

	वापस 0;
पूर्ण

अटल काष्ठा gtp_dev *gtp_find_dev(काष्ठा net *src_net, काष्ठा nlattr *nla[])
अणु
	काष्ठा gtp_dev *gtp = शून्य;
	काष्ठा net_device *dev;
	काष्ठा net *net;

	/* Examine the link attributes and figure out which network namespace
	 * we are talking about.
	 */
	अगर (nla[GTPA_NET_NS_FD])
		net = get_net_ns_by_fd(nla_get_u32(nla[GTPA_NET_NS_FD]));
	अन्यथा
		net = get_net(src_net);

	अगर (IS_ERR(net))
		वापस शून्य;

	/* Check अगर there's an existing gtpX device to configure */
	dev = dev_get_by_index_rcu(net, nla_get_u32(nla[GTPA_LINK]));
	अगर (dev && dev->netdev_ops == &gtp_netdev_ops)
		gtp = netdev_priv(dev);

	put_net(net);
	वापस gtp;
पूर्ण

अटल व्योम ipv4_pdp_fill(काष्ठा pdp_ctx *pctx, काष्ठा genl_info *info)
अणु
	pctx->gtp_version = nla_get_u32(info->attrs[GTPA_VERSION]);
	pctx->af = AF_INET;
	pctx->peer_addr_ip4.s_addr =
		nla_get_be32(info->attrs[GTPA_PEER_ADDRESS]);
	pctx->ms_addr_ip4.s_addr =
		nla_get_be32(info->attrs[GTPA_MS_ADDRESS]);

	चयन (pctx->gtp_version) अणु
	हाल GTP_V0:
		/* According to TS 09.60, sections 7.5.1 and 7.5.2, the flow
		 * label needs to be the same क्रम uplink and करोwnlink packets,
		 * so let's annotate this.
		 */
		pctx->u.v0.tid = nla_get_u64(info->attrs[GTPA_TID]);
		pctx->u.v0.flow = nla_get_u16(info->attrs[GTPA_FLOW]);
		अवरोध;
	हाल GTP_V1:
		pctx->u.v1.i_tei = nla_get_u32(info->attrs[GTPA_I_TEI]);
		pctx->u.v1.o_tei = nla_get_u32(info->attrs[GTPA_O_TEI]);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा pdp_ctx *gtp_pdp_add(काष्ठा gtp_dev *gtp, काष्ठा sock *sk,
				   काष्ठा genl_info *info)
अणु
	काष्ठा pdp_ctx *pctx, *pctx_tid = शून्य;
	काष्ठा net_device *dev = gtp->dev;
	u32 hash_ms, hash_tid = 0;
	अचिन्हित पूर्णांक version;
	bool found = false;
	__be32 ms_addr;

	ms_addr = nla_get_be32(info->attrs[GTPA_MS_ADDRESS]);
	hash_ms = ipv4_hashfn(ms_addr) % gtp->hash_size;
	version = nla_get_u32(info->attrs[GTPA_VERSION]);

	pctx = ipv4_pdp_find(gtp, ms_addr);
	अगर (pctx)
		found = true;
	अगर (version == GTP_V0)
		pctx_tid = gtp0_pdp_find(gtp,
					 nla_get_u64(info->attrs[GTPA_TID]));
	अन्यथा अगर (version == GTP_V1)
		pctx_tid = gtp1_pdp_find(gtp,
					 nla_get_u32(info->attrs[GTPA_I_TEI]));
	अगर (pctx_tid)
		found = true;

	अगर (found) अणु
		अगर (info->nlhdr->nlmsg_flags & NLM_F_EXCL)
			वापस ERR_PTR(-EEXIST);
		अगर (info->nlhdr->nlmsg_flags & NLM_F_REPLACE)
			वापस ERR_PTR(-EOPNOTSUPP);

		अगर (pctx && pctx_tid)
			वापस ERR_PTR(-EEXIST);
		अगर (!pctx)
			pctx = pctx_tid;

		ipv4_pdp_fill(pctx, info);

		अगर (pctx->gtp_version == GTP_V0)
			netdev_dbg(dev, "GTPv0-U: update tunnel id = %llx (pdp %p)\n",
				   pctx->u.v0.tid, pctx);
		अन्यथा अगर (pctx->gtp_version == GTP_V1)
			netdev_dbg(dev, "GTPv1-U: update tunnel id = %x/%x (pdp %p)\n",
				   pctx->u.v1.i_tei, pctx->u.v1.o_tei, pctx);

		वापस pctx;

	पूर्ण

	pctx = kदो_स्मृति(माप(*pctx), GFP_ATOMIC);
	अगर (pctx == शून्य)
		वापस ERR_PTR(-ENOMEM);

	sock_hold(sk);
	pctx->sk = sk;
	pctx->dev = gtp->dev;
	ipv4_pdp_fill(pctx, info);
	atomic_set(&pctx->tx_seq, 0);

	चयन (pctx->gtp_version) अणु
	हाल GTP_V0:
		/* TS 09.60: "The flow label identअगरies unambiguously a GTP
		 * flow.". We use the tid क्रम this instead, I cannot find a
		 * situation in which this करोesn't unambiguosly identअगरy the
		 * PDP context.
		 */
		hash_tid = gtp0_hashfn(pctx->u.v0.tid) % gtp->hash_size;
		अवरोध;
	हाल GTP_V1:
		hash_tid = gtp1u_hashfn(pctx->u.v1.i_tei) % gtp->hash_size;
		अवरोध;
	पूर्ण

	hlist_add_head_rcu(&pctx->hlist_addr, &gtp->addr_hash[hash_ms]);
	hlist_add_head_rcu(&pctx->hlist_tid, &gtp->tid_hash[hash_tid]);

	चयन (pctx->gtp_version) अणु
	हाल GTP_V0:
		netdev_dbg(dev, "GTPv0-U: new PDP ctx id=%llx ssgn=%pI4 ms=%pI4 (pdp=%p)\n",
			   pctx->u.v0.tid, &pctx->peer_addr_ip4,
			   &pctx->ms_addr_ip4, pctx);
		अवरोध;
	हाल GTP_V1:
		netdev_dbg(dev, "GTPv1-U: new PDP ctx id=%x/%x ssgn=%pI4 ms=%pI4 (pdp=%p)\n",
			   pctx->u.v1.i_tei, pctx->u.v1.o_tei,
			   &pctx->peer_addr_ip4, &pctx->ms_addr_ip4, pctx);
		अवरोध;
	पूर्ण

	वापस pctx;
पूर्ण

अटल व्योम pdp_context_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा pdp_ctx *pctx = container_of(head, काष्ठा pdp_ctx, rcu_head);

	sock_put(pctx->sk);
	kमुक्त(pctx);
पूर्ण

अटल व्योम pdp_context_delete(काष्ठा pdp_ctx *pctx)
अणु
	hlist_del_rcu(&pctx->hlist_tid);
	hlist_del_rcu(&pctx->hlist_addr);
	call_rcu(&pctx->rcu_head, pdp_context_मुक्त);
पूर्ण

अटल पूर्णांक gtp_tunnel_notअगरy(काष्ठा pdp_ctx *pctx, u8 cmd, gfp_t allocation);

अटल पूर्णांक gtp_genl_new_pdp(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	अचिन्हित पूर्णांक version;
	काष्ठा pdp_ctx *pctx;
	काष्ठा gtp_dev *gtp;
	काष्ठा sock *sk;
	पूर्णांक err;

	अगर (!info->attrs[GTPA_VERSION] ||
	    !info->attrs[GTPA_LINK] ||
	    !info->attrs[GTPA_PEER_ADDRESS] ||
	    !info->attrs[GTPA_MS_ADDRESS])
		वापस -EINVAL;

	version = nla_get_u32(info->attrs[GTPA_VERSION]);

	चयन (version) अणु
	हाल GTP_V0:
		अगर (!info->attrs[GTPA_TID] ||
		    !info->attrs[GTPA_FLOW])
			वापस -EINVAL;
		अवरोध;
	हाल GTP_V1:
		अगर (!info->attrs[GTPA_I_TEI] ||
		    !info->attrs[GTPA_O_TEI])
			वापस -EINVAL;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	rtnl_lock();

	gtp = gtp_find_dev(sock_net(skb->sk), info->attrs);
	अगर (!gtp) अणु
		err = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	अगर (version == GTP_V0)
		sk = gtp->sk0;
	अन्यथा अगर (version == GTP_V1)
		sk = gtp->sk1u;
	अन्यथा
		sk = शून्य;

	अगर (!sk) अणु
		err = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	pctx = gtp_pdp_add(gtp, sk, info);
	अगर (IS_ERR(pctx)) अणु
		err = PTR_ERR(pctx);
	पूर्ण अन्यथा अणु
		gtp_tunnel_notअगरy(pctx, GTP_CMD_NEWPDP, GFP_KERNEL);
		err = 0;
	पूर्ण

out_unlock:
	rtnl_unlock();
	वापस err;
पूर्ण

अटल काष्ठा pdp_ctx *gtp_find_pdp_by_link(काष्ठा net *net,
					    काष्ठा nlattr *nla[])
अणु
	काष्ठा gtp_dev *gtp;

	gtp = gtp_find_dev(net, nla);
	अगर (!gtp)
		वापस ERR_PTR(-ENODEV);

	अगर (nla[GTPA_MS_ADDRESS]) अणु
		__be32 ip = nla_get_be32(nla[GTPA_MS_ADDRESS]);

		वापस ipv4_pdp_find(gtp, ip);
	पूर्ण अन्यथा अगर (nla[GTPA_VERSION]) अणु
		u32 gtp_version = nla_get_u32(nla[GTPA_VERSION]);

		अगर (gtp_version == GTP_V0 && nla[GTPA_TID])
			वापस gtp0_pdp_find(gtp, nla_get_u64(nla[GTPA_TID]));
		अन्यथा अगर (gtp_version == GTP_V1 && nla[GTPA_I_TEI])
			वापस gtp1_pdp_find(gtp, nla_get_u32(nla[GTPA_I_TEI]));
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल काष्ठा pdp_ctx *gtp_find_pdp(काष्ठा net *net, काष्ठा nlattr *nla[])
अणु
	काष्ठा pdp_ctx *pctx;

	अगर (nla[GTPA_LINK])
		pctx = gtp_find_pdp_by_link(net, nla);
	अन्यथा
		pctx = ERR_PTR(-EINVAL);

	अगर (!pctx)
		pctx = ERR_PTR(-ENOENT);

	वापस pctx;
पूर्ण

अटल पूर्णांक gtp_genl_del_pdp(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा pdp_ctx *pctx;
	पूर्णांक err = 0;

	अगर (!info->attrs[GTPA_VERSION])
		वापस -EINVAL;

	rcu_पढ़ो_lock();

	pctx = gtp_find_pdp(sock_net(skb->sk), info->attrs);
	अगर (IS_ERR(pctx)) अणु
		err = PTR_ERR(pctx);
		जाओ out_unlock;
	पूर्ण

	अगर (pctx->gtp_version == GTP_V0)
		netdev_dbg(pctx->dev, "GTPv0-U: deleting tunnel id = %llx (pdp %p)\n",
			   pctx->u.v0.tid, pctx);
	अन्यथा अगर (pctx->gtp_version == GTP_V1)
		netdev_dbg(pctx->dev, "GTPv1-U: deleting tunnel id = %x/%x (pdp %p)\n",
			   pctx->u.v1.i_tei, pctx->u.v1.o_tei, pctx);

	gtp_tunnel_notअगरy(pctx, GTP_CMD_DELPDP, GFP_ATOMIC);
	pdp_context_delete(pctx);

out_unlock:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल काष्ठा genl_family gtp_genl_family;

क्रमागत gtp_multicast_groups अणु
	GTP_GENL_MCGRP,
पूर्ण;

अटल स्थिर काष्ठा genl_multicast_group gtp_genl_mcgrps[] = अणु
	[GTP_GENL_MCGRP] = अणु .name = GTP_GENL_MCGRP_NAME पूर्ण,
पूर्ण;

अटल पूर्णांक gtp_genl_fill_info(काष्ठा sk_buff *skb, u32 snd_portid, u32 snd_seq,
			      पूर्णांक flags, u32 type, काष्ठा pdp_ctx *pctx)
अणु
	व्योम *genlh;

	genlh = genlmsg_put(skb, snd_portid, snd_seq, &gtp_genl_family, flags,
			    type);
	अगर (genlh == शून्य)
		जाओ nlmsg_failure;

	अगर (nla_put_u32(skb, GTPA_VERSION, pctx->gtp_version) ||
	    nla_put_u32(skb, GTPA_LINK, pctx->dev->अगरindex) ||
	    nla_put_be32(skb, GTPA_PEER_ADDRESS, pctx->peer_addr_ip4.s_addr) ||
	    nla_put_be32(skb, GTPA_MS_ADDRESS, pctx->ms_addr_ip4.s_addr))
		जाओ nla_put_failure;

	चयन (pctx->gtp_version) अणु
	हाल GTP_V0:
		अगर (nla_put_u64_64bit(skb, GTPA_TID, pctx->u.v0.tid, GTPA_PAD) ||
		    nla_put_u16(skb, GTPA_FLOW, pctx->u.v0.flow))
			जाओ nla_put_failure;
		अवरोध;
	हाल GTP_V1:
		अगर (nla_put_u32(skb, GTPA_I_TEI, pctx->u.v1.i_tei) ||
		    nla_put_u32(skb, GTPA_O_TEI, pctx->u.v1.o_tei))
			जाओ nla_put_failure;
		अवरोध;
	पूर्ण
	genlmsg_end(skb, genlh);
	वापस 0;

nlmsg_failure:
nla_put_failure:
	genlmsg_cancel(skb, genlh);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक gtp_tunnel_notअगरy(काष्ठा pdp_ctx *pctx, u8 cmd, gfp_t allocation)
अणु
	काष्ठा sk_buff *msg;
	पूर्णांक ret;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, allocation);
	अगर (!msg)
		वापस -ENOMEM;

	ret = gtp_genl_fill_info(msg, 0, 0, 0, cmd, pctx);
	अगर (ret < 0) अणु
		nlmsg_मुक्त(msg);
		वापस ret;
	पूर्ण

	ret = genlmsg_multicast_netns(&gtp_genl_family, dev_net(pctx->dev), msg,
				      0, GTP_GENL_MCGRP, GFP_ATOMIC);
	वापस ret;
पूर्ण

अटल पूर्णांक gtp_genl_get_pdp(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा pdp_ctx *pctx = शून्य;
	काष्ठा sk_buff *skb2;
	पूर्णांक err;

	अगर (!info->attrs[GTPA_VERSION])
		वापस -EINVAL;

	rcu_पढ़ो_lock();

	pctx = gtp_find_pdp(sock_net(skb->sk), info->attrs);
	अगर (IS_ERR(pctx)) अणु
		err = PTR_ERR(pctx);
		जाओ err_unlock;
	पूर्ण

	skb2 = genlmsg_new(NLMSG_GOODSIZE, GFP_ATOMIC);
	अगर (skb2 == शून्य) अणु
		err = -ENOMEM;
		जाओ err_unlock;
	पूर्ण

	err = gtp_genl_fill_info(skb2, NETLINK_CB(skb).portid, info->snd_seq,
				 0, info->nlhdr->nlmsg_type, pctx);
	अगर (err < 0)
		जाओ err_unlock_मुक्त;

	rcu_पढ़ो_unlock();
	वापस genlmsg_unicast(genl_info_net(info), skb2, info->snd_portid);

err_unlock_मुक्त:
	kमुक्त_skb(skb2);
err_unlock:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक gtp_genl_dump_pdp(काष्ठा sk_buff *skb,
				काष्ठा netlink_callback *cb)
अणु
	काष्ठा gtp_dev *last_gtp = (काष्ठा gtp_dev *)cb->args[2], *gtp;
	पूर्णांक i, j, bucket = cb->args[0], skip = cb->args[1];
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा pdp_ctx *pctx;
	काष्ठा gtp_net *gn;

	gn = net_generic(net, gtp_net_id);

	अगर (cb->args[4])
		वापस 0;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(gtp, &gn->gtp_dev_list, list) अणु
		अगर (last_gtp && last_gtp != gtp)
			जारी;
		अन्यथा
			last_gtp = शून्य;

		क्रम (i = bucket; i < gtp->hash_size; i++) अणु
			j = 0;
			hlist_क्रम_each_entry_rcu(pctx, &gtp->tid_hash[i],
						 hlist_tid) अणु
				अगर (j >= skip &&
				    gtp_genl_fill_info(skb,
					    NETLINK_CB(cb->skb).portid,
					    cb->nlh->nlmsg_seq,
					    NLM_F_MULTI,
					    cb->nlh->nlmsg_type, pctx)) अणु
					cb->args[0] = i;
					cb->args[1] = j;
					cb->args[2] = (अचिन्हित दीर्घ)gtp;
					जाओ out;
				पूर्ण
				j++;
			पूर्ण
			skip = 0;
		पूर्ण
		bucket = 0;
	पूर्ण
	cb->args[4] = 1;
out:
	rcu_पढ़ो_unlock();
	वापस skb->len;
पूर्ण

अटल स्थिर काष्ठा nla_policy gtp_genl_policy[GTPA_MAX + 1] = अणु
	[GTPA_LINK]		= अणु .type = NLA_U32, पूर्ण,
	[GTPA_VERSION]		= अणु .type = NLA_U32, पूर्ण,
	[GTPA_TID]		= अणु .type = NLA_U64, पूर्ण,
	[GTPA_PEER_ADDRESS]	= अणु .type = NLA_U32, पूर्ण,
	[GTPA_MS_ADDRESS]	= अणु .type = NLA_U32, पूर्ण,
	[GTPA_FLOW]		= अणु .type = NLA_U16, पूर्ण,
	[GTPA_NET_NS_FD]	= अणु .type = NLA_U32, पूर्ण,
	[GTPA_I_TEI]		= अणु .type = NLA_U32, पूर्ण,
	[GTPA_O_TEI]		= अणु .type = NLA_U32, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा genl_small_ops gtp_genl_ops[] = अणु
	अणु
		.cmd = GTP_CMD_NEWPDP,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = gtp_genl_new_pdp,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = GTP_CMD_DELPDP,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = gtp_genl_del_pdp,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = GTP_CMD_GETPDP,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = gtp_genl_get_pdp,
		.dumpit = gtp_genl_dump_pdp,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family gtp_genl_family __ro_after_init = अणु
	.name		= "gtp",
	.version	= 0,
	.hdrsize	= 0,
	.maxattr	= GTPA_MAX,
	.policy = gtp_genl_policy,
	.netnsok	= true,
	.module		= THIS_MODULE,
	.small_ops	= gtp_genl_ops,
	.n_small_ops	= ARRAY_SIZE(gtp_genl_ops),
	.mcgrps		= gtp_genl_mcgrps,
	.n_mcgrps	= ARRAY_SIZE(gtp_genl_mcgrps),
पूर्ण;

अटल पूर्णांक __net_init gtp_net_init(काष्ठा net *net)
अणु
	काष्ठा gtp_net *gn = net_generic(net, gtp_net_id);

	INIT_LIST_HEAD(&gn->gtp_dev_list);
	वापस 0;
पूर्ण

अटल व्योम __net_निकास gtp_net_निकास(काष्ठा net *net)
अणु
	काष्ठा gtp_net *gn = net_generic(net, gtp_net_id);
	काष्ठा gtp_dev *gtp;
	LIST_HEAD(list);

	rtnl_lock();
	list_क्रम_each_entry(gtp, &gn->gtp_dev_list, list)
		gtp_dellink(gtp->dev, &list);

	unरेजिस्टर_netdevice_many(&list);
	rtnl_unlock();
पूर्ण

अटल काष्ठा pernet_operations gtp_net_ops = अणु
	.init	= gtp_net_init,
	.निकास	= gtp_net_निकास,
	.id	= &gtp_net_id,
	.size	= माप(काष्ठा gtp_net),
पूर्ण;

अटल पूर्णांक __init gtp_init(व्योम)
अणु
	पूर्णांक err;

	get_अक्रमom_bytes(&gtp_h_initval, माप(gtp_h_initval));

	err = rtnl_link_रेजिस्टर(&gtp_link_ops);
	अगर (err < 0)
		जाओ error_out;

	err = genl_रेजिस्टर_family(&gtp_genl_family);
	अगर (err < 0)
		जाओ unreg_rtnl_link;

	err = रेजिस्टर_pernet_subsys(&gtp_net_ops);
	अगर (err < 0)
		जाओ unreg_genl_family;

	pr_info("GTP module loaded (pdp ctx size %zd bytes)\n",
		माप(काष्ठा pdp_ctx));
	वापस 0;

unreg_genl_family:
	genl_unरेजिस्टर_family(&gtp_genl_family);
unreg_rtnl_link:
	rtnl_link_unरेजिस्टर(&gtp_link_ops);
error_out:
	pr_err("error loading GTP module loaded\n");
	वापस err;
पूर्ण
late_initcall(gtp_init);

अटल व्योम __निकास gtp_fini(व्योम)
अणु
	genl_unरेजिस्टर_family(&gtp_genl_family);
	rtnl_link_unरेजिस्टर(&gtp_link_ops);
	unरेजिस्टर_pernet_subsys(&gtp_net_ops);

	pr_info("GTP module unloaded\n");
पूर्ण
module_निकास(gtp_fini);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Harald Welte <hwelte@sysmocom.de>");
MODULE_DESCRIPTION("Interface driver for GTP encapsulated traffic");
MODULE_ALIAS_RTNL_LINK("gtp");
MODULE_ALIAS_GENL_FAMILY("gtp");
