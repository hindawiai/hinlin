<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* sunvnet.c: Sun LDOM Virtual Network Driver.
 *
 * Copyright (C) 2007, 2008 David S. Miller <davem@davemloft.net>
 * Copyright (C) 2016-2017 Oracle. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/mutex.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/अगर_vlan.h>
#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/sunvnet.h>

#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <linux/icmpv6.h>
#पूर्ण_अगर

#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/route.h>

#समावेश <यंत्र/vपन.स>
#समावेश <यंत्र/ldc.h>

#समावेश "sunvnet_common.h"

/* Heuristic क्रम the number of बार to exponentially backoff and
 * retry sending an LDC trigger when EAGAIN is encountered
 */
#घोषणा	VNET_MAX_RETRIES	10

MODULE_AUTHOR("David S. Miller (davem@davemloft.net)");
MODULE_DESCRIPTION("Sun LDOM virtual network support library");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.1");

अटल पूर्णांक __vnet_tx_trigger(काष्ठा vnet_port *port, u32 start);

अटल अंतरभूत u32 vnet_tx_dring_avail(काष्ठा vio_dring_state *dr)
अणु
	वापस vio_dring_avail(dr, VNET_TX_RING_SIZE);
पूर्ण

अटल पूर्णांक vnet_handle_unknown(काष्ठा vnet_port *port, व्योम *arg)
अणु
	काष्ठा vio_msg_tag *pkt = arg;

	pr_err("Received unknown msg [%02x:%02x:%04x:%08x]\n",
	       pkt->type, pkt->stype, pkt->stype_env, pkt->sid);
	pr_err("Resetting connection\n");

	ldc_disconnect(port->vio.lp);

	वापस -ECONNRESET;
पूर्ण

अटल पूर्णांक vnet_port_alloc_tx_ring(काष्ठा vnet_port *port);

पूर्णांक sunvnet_send_attr_common(काष्ठा vio_driver_state *vio)
अणु
	काष्ठा vnet_port *port = to_vnet_port(vio);
	काष्ठा net_device *dev = VNET_PORT_TO_NET_DEVICE(port);
	काष्ठा vio_net_attr_info pkt;
	पूर्णांक framelen = ETH_FRAME_LEN;
	पूर्णांक i, err;

	err = vnet_port_alloc_tx_ring(to_vnet_port(vio));
	अगर (err)
		वापस err;

	स_रखो(&pkt, 0, माप(pkt));
	pkt.tag.type = VIO_TYPE_CTRL;
	pkt.tag.stype = VIO_SUBTYPE_INFO;
	pkt.tag.stype_env = VIO_ATTR_INFO;
	pkt.tag.sid = vio_send_sid(vio);
	अगर (vio_version_beक्रमe(vio, 1, 2))
		pkt.xfer_mode = VIO_DRING_MODE;
	अन्यथा
		pkt.xfer_mode = VIO_NEW_DRING_MODE;
	pkt.addr_type = VNET_ADDR_ETHERMAC;
	pkt.ack_freq = 0;
	क्रम (i = 0; i < 6; i++)
		pkt.addr |= (u64)dev->dev_addr[i] << ((5 - i) * 8);
	अगर (vio_version_after(vio, 1, 3)) अणु
		अगर (port->rmtu) अणु
			port->rmtu = min(VNET_MAXPACKET, port->rmtu);
			pkt.mtu = port->rmtu;
		पूर्ण अन्यथा अणु
			port->rmtu = VNET_MAXPACKET;
			pkt.mtu = port->rmtu;
		पूर्ण
		अगर (vio_version_after_eq(vio, 1, 6))
			pkt.options = VIO_TX_DRING;
	पूर्ण अन्यथा अगर (vio_version_beक्रमe(vio, 1, 3)) अणु
		pkt.mtu = framelen;
	पूर्ण अन्यथा अणु /* v1.3 */
		pkt.mtu = framelen + VLAN_HLEN;
	पूर्ण

	pkt.cflags = 0;
	अगर (vio_version_after_eq(vio, 1, 7) && port->tso) अणु
		pkt.cflags |= VNET_LSO_IPV4_CAPAB;
		अगर (!port->tsolen)
			port->tsolen = VNET_MAXTSO;
		pkt.ipv4_lso_maxlen = port->tsolen;
	पूर्ण

	pkt.plnk_updt = PHYSLINK_UPDATE_NONE;

	viodbg(HS, "SEND NET ATTR xmode[0x%x] atype[0x%x] addr[%llx] "
	       "ackfreq[%u] plnk_updt[0x%02x] opts[0x%02x] mtu[%llu] "
	       "cflags[0x%04x] lso_max[%u]\n",
	       pkt.xfer_mode, pkt.addr_type,
	       (अचिन्हित दीर्घ दीर्घ)pkt.addr,
	       pkt.ack_freq, pkt.plnk_updt, pkt.options,
	       (अचिन्हित दीर्घ दीर्घ)pkt.mtu, pkt.cflags, pkt.ipv4_lso_maxlen);

	वापस vio_ldc_send(vio, &pkt, माप(pkt));
पूर्ण
EXPORT_SYMBOL_GPL(sunvnet_send_attr_common);

अटल पूर्णांक handle_attr_info(काष्ठा vio_driver_state *vio,
			    काष्ठा vio_net_attr_info *pkt)
अणु
	काष्ठा vnet_port *port = to_vnet_port(vio);
	u64	localmtu;
	u8	xfer_mode;

	viodbg(HS, "GOT NET ATTR xmode[0x%x] atype[0x%x] addr[%llx] "
	       "ackfreq[%u] plnk_updt[0x%02x] opts[0x%02x] mtu[%llu] "
	       " (rmtu[%llu]) cflags[0x%04x] lso_max[%u]\n",
	       pkt->xfer_mode, pkt->addr_type,
	       (अचिन्हित दीर्घ दीर्घ)pkt->addr,
	       pkt->ack_freq, pkt->plnk_updt, pkt->options,
	       (अचिन्हित दीर्घ दीर्घ)pkt->mtu, port->rmtu, pkt->cflags,
	       pkt->ipv4_lso_maxlen);

	pkt->tag.sid = vio_send_sid(vio);

	xfer_mode = pkt->xfer_mode;
	/* क्रम version < 1.2, VIO_DRING_MODE = 0x3 and no biपंचांगask */
	अगर (vio_version_beक्रमe(vio, 1, 2) && xfer_mode == VIO_DRING_MODE)
		xfer_mode = VIO_NEW_DRING_MODE;

	/* MTU negotiation:
	 *	< v1.3 - ETH_FRAME_LEN exactly
	 *	> v1.3 - MIN(pkt.mtu, VNET_MAXPACKET, port->rmtu) and change
	 *			pkt->mtu क्रम ACK
	 *	= v1.3 - ETH_FRAME_LEN + VLAN_HLEN exactly
	 */
	अगर (vio_version_beक्रमe(vio, 1, 3)) अणु
		localmtu = ETH_FRAME_LEN;
	पूर्ण अन्यथा अगर (vio_version_after(vio, 1, 3)) अणु
		localmtu = port->rmtu ? port->rmtu : VNET_MAXPACKET;
		localmtu = min(pkt->mtu, localmtu);
		pkt->mtu = localmtu;
	पूर्ण अन्यथा अणु /* v1.3 */
		localmtu = ETH_FRAME_LEN + VLAN_HLEN;
	पूर्ण
	port->rmtu = localmtu;

	/* LSO negotiation */
	अगर (vio_version_after_eq(vio, 1, 7))
		port->tso &= !!(pkt->cflags & VNET_LSO_IPV4_CAPAB);
	अन्यथा
		port->tso = false;
	अगर (port->tso) अणु
		अगर (!port->tsolen)
			port->tsolen = VNET_MAXTSO;
		port->tsolen = min(port->tsolen, pkt->ipv4_lso_maxlen);
		अगर (port->tsolen < VNET_MINTSO) अणु
			port->tso = false;
			port->tsolen = 0;
			pkt->cflags &= ~VNET_LSO_IPV4_CAPAB;
		पूर्ण
		pkt->ipv4_lso_maxlen = port->tsolen;
	पूर्ण अन्यथा अणु
		pkt->cflags &= ~VNET_LSO_IPV4_CAPAB;
		pkt->ipv4_lso_maxlen = 0;
		port->tsolen = 0;
	पूर्ण

	/* क्रम version >= 1.6, ACK packet mode we support */
	अगर (vio_version_after_eq(vio, 1, 6)) अणु
		pkt->xfer_mode = VIO_NEW_DRING_MODE;
		pkt->options = VIO_TX_DRING;
	पूर्ण

	अगर (!(xfer_mode | VIO_NEW_DRING_MODE) ||
	    pkt->addr_type != VNET_ADDR_ETHERMAC ||
	    pkt->mtu != localmtu) अणु
		viodbg(HS, "SEND NET ATTR NACK\n");

		pkt->tag.stype = VIO_SUBTYPE_NACK;

		(व्योम)vio_ldc_send(vio, pkt, माप(*pkt));

		वापस -ECONNRESET;
	पूर्ण

	viodbg(HS, "SEND NET ATTR ACK xmode[0x%x] atype[0x%x] "
	       "addr[%llx] ackfreq[%u] plnk_updt[0x%02x] opts[0x%02x] "
	       "mtu[%llu] (rmtu[%llu]) cflags[0x%04x] lso_max[%u]\n",
	       pkt->xfer_mode, pkt->addr_type,
	       (अचिन्हित दीर्घ दीर्घ)pkt->addr,
	       pkt->ack_freq, pkt->plnk_updt, pkt->options,
	       (अचिन्हित दीर्घ दीर्घ)pkt->mtu, port->rmtu, pkt->cflags,
	       pkt->ipv4_lso_maxlen);

	pkt->tag.stype = VIO_SUBTYPE_ACK;

	वापस vio_ldc_send(vio, pkt, माप(*pkt));
पूर्ण

अटल पूर्णांक handle_attr_ack(काष्ठा vio_driver_state *vio,
			   काष्ठा vio_net_attr_info *pkt)
अणु
	viodbg(HS, "GOT NET ATTR ACK\n");

	वापस 0;
पूर्ण

अटल पूर्णांक handle_attr_nack(काष्ठा vio_driver_state *vio,
			    काष्ठा vio_net_attr_info *pkt)
अणु
	viodbg(HS, "GOT NET ATTR NACK\n");

	वापस -ECONNRESET;
पूर्ण

पूर्णांक sunvnet_handle_attr_common(काष्ठा vio_driver_state *vio, व्योम *arg)
अणु
	काष्ठा vio_net_attr_info *pkt = arg;

	चयन (pkt->tag.stype) अणु
	हाल VIO_SUBTYPE_INFO:
		वापस handle_attr_info(vio, pkt);

	हाल VIO_SUBTYPE_ACK:
		वापस handle_attr_ack(vio, pkt);

	हाल VIO_SUBTYPE_NACK:
		वापस handle_attr_nack(vio, pkt);

	शेष:
		वापस -ECONNRESET;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(sunvnet_handle_attr_common);

व्योम sunvnet_handshake_complete_common(काष्ठा vio_driver_state *vio)
अणु
	काष्ठा vio_dring_state *dr;

	dr = &vio->drings[VIO_DRIVER_RX_RING];
	dr->rcv_nxt = 1;
	dr->snd_nxt = 1;

	dr = &vio->drings[VIO_DRIVER_TX_RING];
	dr->rcv_nxt = 1;
	dr->snd_nxt = 1;
पूर्ण
EXPORT_SYMBOL_GPL(sunvnet_handshake_complete_common);

/* The hypervisor पूर्णांकerface that implements copying to/from imported
 * memory from another करोमुख्य requires that copies are करोne to 8-byte
 * aligned buffers, and that the lengths of such copies are also 8-byte
 * multiples.
 *
 * So we align skb->data to an 8-byte multiple and pad-out the data
 * area so we can round the copy length up to the next multiple of
 * 8 क्रम the copy.
 *
 * The transmitter माला_दो the actual start of the packet 6 bytes पूर्णांकo
 * the buffer it sends over, so that the IP headers after the ethernet
 * header are aligned properly.  These 6 bytes are not in the descriptor
 * length, they are simply implied.  This offset is represented using
 * the VNET_PACKET_SKIP macro.
 */
अटल काष्ठा sk_buff *alloc_and_align_skb(काष्ठा net_device *dev,
					   अचिन्हित पूर्णांक len)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ addr, off;

	skb = netdev_alloc_skb(dev, len + VNET_PACKET_SKIP + 8 + 8);
	अगर (unlikely(!skb))
		वापस शून्य;

	addr = (अचिन्हित दीर्घ)skb->data;
	off = ((addr + 7UL) & ~7UL) - addr;
	अगर (off)
		skb_reserve(skb, off);

	वापस skb;
पूर्ण

अटल अंतरभूत व्योम vnet_fullcsum_ipv4(काष्ठा sk_buff *skb)
अणु
	काष्ठा iphdr *iph = ip_hdr(skb);
	पूर्णांक offset = skb_transport_offset(skb);

	अगर (skb->protocol != htons(ETH_P_IP))
		वापस;
	अगर (iph->protocol != IPPROTO_TCP &&
	    iph->protocol != IPPROTO_UDP)
		वापस;
	skb->ip_summed = CHECKSUM_NONE;
	skb->csum_level = 1;
	skb->csum = 0;
	अगर (iph->protocol == IPPROTO_TCP) अणु
		काष्ठा tcphdr *ptcp = tcp_hdr(skb);

		ptcp->check = 0;
		skb->csum = skb_checksum(skb, offset, skb->len - offset, 0);
		ptcp->check = csum_tcpudp_magic(iph->saddr, iph->daddr,
						skb->len - offset, IPPROTO_TCP,
						skb->csum);
	पूर्ण अन्यथा अगर (iph->protocol == IPPROTO_UDP) अणु
		काष्ठा udphdr *pudp = udp_hdr(skb);

		pudp->check = 0;
		skb->csum = skb_checksum(skb, offset, skb->len - offset, 0);
		pudp->check = csum_tcpudp_magic(iph->saddr, iph->daddr,
						skb->len - offset, IPPROTO_UDP,
						skb->csum);
	पूर्ण
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल अंतरभूत व्योम vnet_fullcsum_ipv6(काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);
	पूर्णांक offset = skb_transport_offset(skb);

	अगर (skb->protocol != htons(ETH_P_IPV6))
		वापस;
	अगर (ip6h->nexthdr != IPPROTO_TCP &&
	    ip6h->nexthdr != IPPROTO_UDP)
		वापस;
	skb->ip_summed = CHECKSUM_NONE;
	skb->csum_level = 1;
	skb->csum = 0;
	अगर (ip6h->nexthdr == IPPROTO_TCP) अणु
		काष्ठा tcphdr *ptcp = tcp_hdr(skb);

		ptcp->check = 0;
		skb->csum = skb_checksum(skb, offset, skb->len - offset, 0);
		ptcp->check = csum_ipv6_magic(&ip6h->saddr, &ip6h->daddr,
					      skb->len - offset, IPPROTO_TCP,
					      skb->csum);
	पूर्ण अन्यथा अगर (ip6h->nexthdr == IPPROTO_UDP) अणु
		काष्ठा udphdr *pudp = udp_hdr(skb);

		pudp->check = 0;
		skb->csum = skb_checksum(skb, offset, skb->len - offset, 0);
		pudp->check = csum_ipv6_magic(&ip6h->saddr, &ip6h->daddr,
					      skb->len - offset, IPPROTO_UDP,
					      skb->csum);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक vnet_rx_one(काष्ठा vnet_port *port, काष्ठा vio_net_desc *desc)
अणु
	काष्ठा net_device *dev = VNET_PORT_TO_NET_DEVICE(port);
	अचिन्हित पूर्णांक len = desc->size;
	अचिन्हित पूर्णांक copy_len;
	काष्ठा sk_buff *skb;
	पूर्णांक maxlen;
	पूर्णांक err;

	err = -EMSGSIZE;
	अगर (port->tso && port->tsolen > port->rmtu)
		maxlen = port->tsolen;
	अन्यथा
		maxlen = port->rmtu;
	अगर (unlikely(len < ETH_ZLEN || len > maxlen)) अणु
		dev->stats.rx_length_errors++;
		जाओ out_dropped;
	पूर्ण

	skb = alloc_and_align_skb(dev, len);
	err = -ENOMEM;
	अगर (unlikely(!skb)) अणु
		dev->stats.rx_missed_errors++;
		जाओ out_dropped;
	पूर्ण

	copy_len = (len + VNET_PACKET_SKIP + 7U) & ~7U;
	skb_put(skb, copy_len);
	err = ldc_copy(port->vio.lp, LDC_COPY_IN,
		       skb->data, copy_len, 0,
		       desc->cookies, desc->ncookies);
	अगर (unlikely(err < 0)) अणु
		dev->stats.rx_frame_errors++;
		जाओ out_मुक्त_skb;
	पूर्ण

	skb_pull(skb, VNET_PACKET_SKIP);
	skb_trim(skb, len);
	skb->protocol = eth_type_trans(skb, dev);

	अगर (vio_version_after_eq(&port->vio, 1, 8)) अणु
		काष्ठा vio_net_dext *dext = vio_net_ext(desc);

		skb_reset_network_header(skb);

		अगर (dext->flags & VNET_PKT_HCK_IPV4_HDRCKSUM) अणु
			अगर (skb->protocol == ETH_P_IP) अणु
				काष्ठा iphdr *iph = ip_hdr(skb);

				iph->check = 0;
				ip_send_check(iph);
			पूर्ण
		पूर्ण
		अगर ((dext->flags & VNET_PKT_HCK_FULLCKSUM) &&
		    skb->ip_summed == CHECKSUM_NONE) अणु
			अगर (skb->protocol == htons(ETH_P_IP)) अणु
				काष्ठा iphdr *iph = ip_hdr(skb);
				पूर्णांक ihl = iph->ihl * 4;

				skb_set_transport_header(skb, ihl);
				vnet_fullcsum_ipv4(skb);
#अगर IS_ENABLED(CONFIG_IPV6)
			पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
				skb_set_transport_header(skb,
							 माप(काष्ठा ipv6hdr));
				vnet_fullcsum_ipv6(skb);
#पूर्ण_अगर
			पूर्ण
		पूर्ण
		अगर (dext->flags & VNET_PKT_HCK_IPV4_HDRCKSUM_OK) अणु
			skb->ip_summed = CHECKSUM_PARTIAL;
			skb->csum_level = 0;
			अगर (dext->flags & VNET_PKT_HCK_FULLCKSUM_OK)
				skb->csum_level = 1;
		पूर्ण
	पूर्ण

	skb->ip_summed = port->चयन_port ? CHECKSUM_NONE : CHECKSUM_PARTIAL;

	अगर (unlikely(is_multicast_ether_addr(eth_hdr(skb)->h_dest)))
		dev->stats.multicast++;
	dev->stats.rx_packets++;
	dev->stats.rx_bytes += len;
	port->stats.rx_packets++;
	port->stats.rx_bytes += len;
	napi_gro_receive(&port->napi, skb);
	वापस 0;

out_मुक्त_skb:
	kमुक्त_skb(skb);

out_dropped:
	dev->stats.rx_dropped++;
	वापस err;
पूर्ण

अटल पूर्णांक vnet_send_ack(काष्ठा vnet_port *port, काष्ठा vio_dring_state *dr,
			 u32 start, u32 end, u8 vio_dring_state)
अणु
	काष्ठा vio_dring_data hdr = अणु
		.tag = अणु
			.type		= VIO_TYPE_DATA,
			.stype		= VIO_SUBTYPE_ACK,
			.stype_env	= VIO_DRING_DATA,
			.sid		= vio_send_sid(&port->vio),
		पूर्ण,
		.dring_ident		= dr->ident,
		.start_idx		= start,
		.end_idx		= end,
		.state			= vio_dring_state,
	पूर्ण;
	पूर्णांक err, delay;
	पूर्णांक retries = 0;

	hdr.seq = dr->snd_nxt;
	delay = 1;
	करो अणु
		err = vio_ldc_send(&port->vio, &hdr, माप(hdr));
		अगर (err > 0) अणु
			dr->snd_nxt++;
			अवरोध;
		पूर्ण
		udelay(delay);
		अगर ((delay <<= 1) > 128)
			delay = 128;
		अगर (retries++ > VNET_MAX_RETRIES) अणु
			pr_info("ECONNRESET %x:%x:%x:%x:%x:%x\n",
				port->raddr[0], port->raddr[1],
				port->raddr[2], port->raddr[3],
				port->raddr[4], port->raddr[5]);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (err == -EAGAIN);

	अगर (err <= 0 && vio_dring_state == VIO_DRING_STOPPED) अणु
		port->stop_rx_idx = end;
		port->stop_rx = true;
	पूर्ण अन्यथा अणु
		port->stop_rx_idx = 0;
		port->stop_rx = false;
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा vio_net_desc *get_rx_desc(काष्ठा vnet_port *port,
					काष्ठा vio_dring_state *dr,
					u32 index)
अणु
	काष्ठा vio_net_desc *desc = port->vio.desc_buf;
	पूर्णांक err;

	err = ldc_get_dring_entry(port->vio.lp, desc, dr->entry_size,
				  (index * dr->entry_size),
				  dr->cookies, dr->ncookies);
	अगर (err < 0)
		वापस ERR_PTR(err);

	वापस desc;
पूर्ण

अटल पूर्णांक put_rx_desc(काष्ठा vnet_port *port,
		       काष्ठा vio_dring_state *dr,
		       काष्ठा vio_net_desc *desc,
		       u32 index)
अणु
	पूर्णांक err;

	err = ldc_put_dring_entry(port->vio.lp, desc, dr->entry_size,
				  (index * dr->entry_size),
				  dr->cookies, dr->ncookies);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक vnet_walk_rx_one(काष्ठा vnet_port *port,
			    काष्ठा vio_dring_state *dr,
			    u32 index, पूर्णांक *needs_ack)
अणु
	काष्ठा vio_net_desc *desc = get_rx_desc(port, dr, index);
	काष्ठा vio_driver_state *vio = &port->vio;
	पूर्णांक err;

	BUG_ON(!desc);
	अगर (IS_ERR(desc))
		वापस PTR_ERR(desc);

	अगर (desc->hdr.state != VIO_DESC_READY)
		वापस 1;

	dma_rmb();

	viodbg(DATA, "vio_walk_rx_one desc[%02x:%02x:%08x:%08x:%llx:%llx]\n",
	       desc->hdr.state, desc->hdr.ack,
	       desc->size, desc->ncookies,
	       desc->cookies[0].cookie_addr,
	       desc->cookies[0].cookie_size);

	err = vnet_rx_one(port, desc);
	अगर (err == -ECONNRESET)
		वापस err;
	trace_vnet_rx_one(port->vio._local_sid, port->vio._peer_sid,
			  index, desc->hdr.ack);
	desc->hdr.state = VIO_DESC_DONE;
	err = put_rx_desc(port, dr, desc, index);
	अगर (err < 0)
		वापस err;
	*needs_ack = desc->hdr.ack;
	वापस 0;
पूर्ण

अटल पूर्णांक vnet_walk_rx(काष्ठा vnet_port *port, काष्ठा vio_dring_state *dr,
			u32 start, u32 end, पूर्णांक *npkts, पूर्णांक budget)
अणु
	काष्ठा vio_driver_state *vio = &port->vio;
	पूर्णांक ack_start = -1, ack_end = -1;
	bool send_ack = true;

	end = (end == (u32)-1) ? vio_dring_prev(dr, start)
			       : vio_dring_next(dr, end);

	viodbg(DATA, "vnet_walk_rx start[%08x] end[%08x]\n", start, end);

	जबतक (start != end) अणु
		पूर्णांक ack = 0, err = vnet_walk_rx_one(port, dr, start, &ack);

		अगर (err == -ECONNRESET)
			वापस err;
		अगर (err != 0)
			अवरोध;
		(*npkts)++;
		अगर (ack_start == -1)
			ack_start = start;
		ack_end = start;
		start = vio_dring_next(dr, start);
		अगर (ack && start != end) अणु
			err = vnet_send_ack(port, dr, ack_start, ack_end,
					    VIO_DRING_ACTIVE);
			अगर (err == -ECONNRESET)
				वापस err;
			ack_start = -1;
		पूर्ण
		अगर ((*npkts) >= budget) अणु
			send_ack = false;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (unlikely(ack_start == -1)) अणु
		ack_end = vio_dring_prev(dr, start);
		ack_start = ack_end;
	पूर्ण
	अगर (send_ack) अणु
		port->napi_resume = false;
		trace_vnet_tx_send_stopped_ack(port->vio._local_sid,
					       port->vio._peer_sid,
					       ack_end, *npkts);
		वापस vnet_send_ack(port, dr, ack_start, ack_end,
				     VIO_DRING_STOPPED);
	पूर्ण अन्यथा  अणु
		trace_vnet_tx_defer_stopped_ack(port->vio._local_sid,
						port->vio._peer_sid,
						ack_end, *npkts);
		port->napi_resume = true;
		port->napi_stop_idx = ack_end;
		वापस 1;
	पूर्ण
पूर्ण

अटल पूर्णांक vnet_rx(काष्ठा vnet_port *port, व्योम *msgbuf, पूर्णांक *npkts,
		   पूर्णांक budget)
अणु
	काष्ठा vio_dring_data *pkt = msgbuf;
	काष्ठा vio_dring_state *dr = &port->vio.drings[VIO_DRIVER_RX_RING];
	काष्ठा vio_driver_state *vio = &port->vio;

	viodbg(DATA, "vnet_rx stype_env[%04x] seq[%016llx] rcv_nxt[%016llx]\n",
	       pkt->tag.stype_env, pkt->seq, dr->rcv_nxt);

	अगर (unlikely(pkt->tag.stype_env != VIO_DRING_DATA))
		वापस 0;
	अगर (unlikely(pkt->seq != dr->rcv_nxt)) अणु
		pr_err("RX out of sequence seq[0x%llx] rcv_nxt[0x%llx]\n",
		       pkt->seq, dr->rcv_nxt);
		वापस 0;
	पूर्ण

	अगर (!port->napi_resume)
		dr->rcv_nxt++;

	/* XXX Validate pkt->start_idx and pkt->end_idx XXX */

	वापस vnet_walk_rx(port, dr, pkt->start_idx, pkt->end_idx,
			    npkts, budget);
पूर्ण

अटल पूर्णांक idx_is_pending(काष्ठा vio_dring_state *dr, u32 end)
अणु
	u32 idx = dr->cons;
	पूर्णांक found = 0;

	जबतक (idx != dr->prod) अणु
		अगर (idx == end) अणु
			found = 1;
			अवरोध;
		पूर्ण
		idx = vio_dring_next(dr, idx);
	पूर्ण
	वापस found;
पूर्ण

अटल पूर्णांक vnet_ack(काष्ठा vnet_port *port, व्योम *msgbuf)
अणु
	काष्ठा vio_dring_state *dr = &port->vio.drings[VIO_DRIVER_TX_RING];
	काष्ठा vio_dring_data *pkt = msgbuf;
	काष्ठा net_device *dev;
	u32 end;
	काष्ठा vio_net_desc *desc;
	काष्ठा netdev_queue *txq;

	अगर (unlikely(pkt->tag.stype_env != VIO_DRING_DATA))
		वापस 0;

	end = pkt->end_idx;
	dev = VNET_PORT_TO_NET_DEVICE(port);
	netअगर_tx_lock(dev);
	अगर (unlikely(!idx_is_pending(dr, end))) अणु
		netअगर_tx_unlock(dev);
		वापस 0;
	पूर्ण

	/* sync क्रम race conditions with vnet_start_xmit() and tell xmit it
	 * is समय to send a trigger.
	 */
	trace_vnet_rx_stopped_ack(port->vio._local_sid,
				  port->vio._peer_sid, end);
	dr->cons = vio_dring_next(dr, end);
	desc = vio_dring_entry(dr, dr->cons);
	अगर (desc->hdr.state == VIO_DESC_READY && !port->start_cons) अणु
		/* vnet_start_xmit() just populated this dring but missed
		 * sending the "start" LDC message to the consumer.
		 * Send a "start" trigger on its behalf.
		 */
		अगर (__vnet_tx_trigger(port, dr->cons) > 0)
			port->start_cons = false;
		अन्यथा
			port->start_cons = true;
	पूर्ण अन्यथा अणु
		port->start_cons = true;
	पूर्ण
	netअगर_tx_unlock(dev);

	txq = netdev_get_tx_queue(dev, port->q_index);
	अगर (unlikely(netअगर_tx_queue_stopped(txq) &&
		     vnet_tx_dring_avail(dr) >= VNET_TX_WAKEUP_THRESH(dr)))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक vnet_nack(काष्ठा vnet_port *port, व्योम *msgbuf)
अणु
	/* XXX just reset or similar XXX */
	वापस 0;
पूर्ण

अटल पूर्णांक handle_mcast(काष्ठा vnet_port *port, व्योम *msgbuf)
अणु
	काष्ठा vio_net_mcast_info *pkt = msgbuf;
	काष्ठा net_device *dev = VNET_PORT_TO_NET_DEVICE(port);

	अगर (pkt->tag.stype != VIO_SUBTYPE_ACK)
		pr_err("%s: Got unexpected MCAST reply [%02x:%02x:%04x:%08x]\n",
		       dev->name,
		       pkt->tag.type,
		       pkt->tag.stype,
		       pkt->tag.stype_env,
		       pkt->tag.sid);

	वापस 0;
पूर्ण

/* If the queue is stopped, wake it up so that we'll
 * send out another START message at the next TX.
 */
अटल व्योम maybe_tx_wakeup(काष्ठा vnet_port *port)
अणु
	काष्ठा netdev_queue *txq;

	txq = netdev_get_tx_queue(VNET_PORT_TO_NET_DEVICE(port),
				  port->q_index);
	__netअगर_tx_lock(txq, smp_processor_id());
	अगर (likely(netअगर_tx_queue_stopped(txq)))
		netअगर_tx_wake_queue(txq);
	__netअगर_tx_unlock(txq);
पूर्ण

bool sunvnet_port_is_up_common(काष्ठा vnet_port *vnet)
अणु
	काष्ठा vio_driver_state *vio = &vnet->vio;

	वापस !!(vio->hs_state & VIO_HS_COMPLETE);
पूर्ण
EXPORT_SYMBOL_GPL(sunvnet_port_is_up_common);

अटल पूर्णांक vnet_event_napi(काष्ठा vnet_port *port, पूर्णांक budget)
अणु
	काष्ठा net_device *dev = VNET_PORT_TO_NET_DEVICE(port);
	काष्ठा vio_driver_state *vio = &port->vio;
	पूर्णांक tx_wakeup, err;
	पूर्णांक npkts = 0;

	/* we करोn't expect any other bits */
	BUG_ON(port->rx_event & ~(LDC_EVENT_DATA_READY |
				  LDC_EVENT_RESET |
				  LDC_EVENT_UP));

	/* RESET takes precedent over any other event */
	अगर (port->rx_event & LDC_EVENT_RESET) अणु
		/* a link went करोwn */

		अगर (port->vsw == 1) अणु
			netअगर_tx_stop_all_queues(dev);
			netअगर_carrier_off(dev);
		पूर्ण

		vio_link_state_change(vio, LDC_EVENT_RESET);
		vnet_port_reset(port);
		vio_port_up(vio);

		/* If the device is running but its tx queue was
		 * stopped (due to flow control), restart it.
		 * This is necessary since vnet_port_reset()
		 * clears the tx drings and thus we may never get
		 * back a VIO_TYPE_DATA ACK packet - which is
		 * the normal mechanism to restart the tx queue.
		 */
		अगर (netअगर_running(dev))
			maybe_tx_wakeup(port);

		port->rx_event = 0;
		port->stats.event_reset++;
		वापस 0;
	पूर्ण

	अगर (port->rx_event & LDC_EVENT_UP) अणु
		/* a link came up */

		अगर (port->vsw == 1) अणु
			netअगर_carrier_on(port->dev);
			netअगर_tx_start_all_queues(port->dev);
		पूर्ण

		vio_link_state_change(vio, LDC_EVENT_UP);
		port->rx_event = 0;
		port->stats.event_up++;
		वापस 0;
	पूर्ण

	err = 0;
	tx_wakeup = 0;
	जबतक (1) अणु
		जोड़ अणु
			काष्ठा vio_msg_tag tag;
			u64 raw[8];
		पूर्ण msgbuf;

		अगर (port->napi_resume) अणु
			काष्ठा vio_dring_data *pkt =
				(काष्ठा vio_dring_data *)&msgbuf;
			काष्ठा vio_dring_state *dr =
				&port->vio.drings[VIO_DRIVER_RX_RING];

			pkt->tag.type = VIO_TYPE_DATA;
			pkt->tag.stype = VIO_SUBTYPE_INFO;
			pkt->tag.stype_env = VIO_DRING_DATA;
			pkt->seq = dr->rcv_nxt;
			pkt->start_idx = vio_dring_next(dr,
							port->napi_stop_idx);
			pkt->end_idx = -1;
		पूर्ण अन्यथा अणु
			err = ldc_पढ़ो(vio->lp, &msgbuf, माप(msgbuf));
			अगर (unlikely(err < 0)) अणु
				अगर (err == -ECONNRESET)
					vio_conn_reset(vio);
				अवरोध;
			पूर्ण
			अगर (err == 0)
				अवरोध;
			viodbg(DATA, "TAG [%02x:%02x:%04x:%08x]\n",
			       msgbuf.tag.type,
			       msgbuf.tag.stype,
			       msgbuf.tag.stype_env,
			       msgbuf.tag.sid);
			err = vio_validate_sid(vio, &msgbuf.tag);
			अगर (err < 0)
				अवरोध;
		पूर्ण

		अगर (likely(msgbuf.tag.type == VIO_TYPE_DATA)) अणु
			अगर (msgbuf.tag.stype == VIO_SUBTYPE_INFO) अणु
				अगर (!sunvnet_port_is_up_common(port)) अणु
					/* failures like handshake_failure()
					 * may have cleaned up dring, but
					 * NAPI polling may bring us here.
					 */
					err = -ECONNRESET;
					अवरोध;
				पूर्ण
				err = vnet_rx(port, &msgbuf, &npkts, budget);
				अगर (npkts >= budget)
					अवरोध;
				अगर (npkts == 0)
					अवरोध;
			पूर्ण अन्यथा अगर (msgbuf.tag.stype == VIO_SUBTYPE_ACK) अणु
				err = vnet_ack(port, &msgbuf);
				अगर (err > 0)
					tx_wakeup |= err;
			पूर्ण अन्यथा अगर (msgbuf.tag.stype == VIO_SUBTYPE_NACK) अणु
				err = vnet_nack(port, &msgbuf);
			पूर्ण
		पूर्ण अन्यथा अगर (msgbuf.tag.type == VIO_TYPE_CTRL) अणु
			अगर (msgbuf.tag.stype_env == VNET_MCAST_INFO)
				err = handle_mcast(port, &msgbuf);
			अन्यथा
				err = vio_control_pkt_engine(vio, &msgbuf);
			अगर (err)
				अवरोध;
		पूर्ण अन्यथा अणु
			err = vnet_handle_unknown(port, &msgbuf);
		पूर्ण
		अगर (err == -ECONNRESET)
			अवरोध;
	पूर्ण
	अगर (unlikely(tx_wakeup && err != -ECONNRESET))
		maybe_tx_wakeup(port);
	वापस npkts;
पूर्ण

पूर्णांक sunvnet_poll_common(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा vnet_port *port = container_of(napi, काष्ठा vnet_port, napi);
	काष्ठा vio_driver_state *vio = &port->vio;
	पूर्णांक processed = vnet_event_napi(port, budget);

	अगर (processed < budget) अणु
		napi_complete_करोne(napi, processed);
		port->rx_event &= ~LDC_EVENT_DATA_READY;
		vio_set_पूर्णांकr(vio->vdev->rx_ino, HV_INTR_ENABLED);
	पूर्ण
	वापस processed;
पूर्ण
EXPORT_SYMBOL_GPL(sunvnet_poll_common);

व्योम sunvnet_event_common(व्योम *arg, पूर्णांक event)
अणु
	काष्ठा vnet_port *port = arg;
	काष्ठा vio_driver_state *vio = &port->vio;

	port->rx_event |= event;
	vio_set_पूर्णांकr(vio->vdev->rx_ino, HV_INTR_DISABLED);
	napi_schedule(&port->napi);
पूर्ण
EXPORT_SYMBOL_GPL(sunvnet_event_common);

अटल पूर्णांक __vnet_tx_trigger(काष्ठा vnet_port *port, u32 start)
अणु
	काष्ठा vio_dring_state *dr = &port->vio.drings[VIO_DRIVER_TX_RING];
	काष्ठा vio_dring_data hdr = अणु
		.tag = अणु
			.type		= VIO_TYPE_DATA,
			.stype		= VIO_SUBTYPE_INFO,
			.stype_env	= VIO_DRING_DATA,
			.sid		= vio_send_sid(&port->vio),
		पूर्ण,
		.dring_ident		= dr->ident,
		.start_idx		= start,
		.end_idx		= (u32)-1,
	पूर्ण;
	पूर्णांक err, delay;
	पूर्णांक retries = 0;

	अगर (port->stop_rx) अणु
		trace_vnet_tx_pending_stopped_ack(port->vio._local_sid,
						  port->vio._peer_sid,
						  port->stop_rx_idx, -1);
		err = vnet_send_ack(port,
				    &port->vio.drings[VIO_DRIVER_RX_RING],
				    port->stop_rx_idx, -1,
				    VIO_DRING_STOPPED);
		अगर (err <= 0)
			वापस err;
	पूर्ण

	hdr.seq = dr->snd_nxt;
	delay = 1;
	करो अणु
		err = vio_ldc_send(&port->vio, &hdr, माप(hdr));
		अगर (err > 0) अणु
			dr->snd_nxt++;
			अवरोध;
		पूर्ण
		udelay(delay);
		अगर ((delay <<= 1) > 128)
			delay = 128;
		अगर (retries++ > VNET_MAX_RETRIES)
			अवरोध;
	पूर्ण जबतक (err == -EAGAIN);
	trace_vnet_tx_trigger(port->vio._local_sid,
			      port->vio._peer_sid, start, err);

	वापस err;
पूर्ण

अटल काष्ठा sk_buff *vnet_clean_tx_ring(काष्ठा vnet_port *port,
					  अचिन्हित *pending)
अणु
	काष्ठा vio_dring_state *dr = &port->vio.drings[VIO_DRIVER_TX_RING];
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक i, txi;

	*pending = 0;

	txi = dr->prod;
	क्रम (i = 0; i < VNET_TX_RING_SIZE; ++i) अणु
		काष्ठा vio_net_desc *d;

		--txi;
		अगर (txi < 0)
			txi = VNET_TX_RING_SIZE - 1;

		d = vio_dring_entry(dr, txi);

		अगर (d->hdr.state == VIO_DESC_READY) अणु
			(*pending)++;
			जारी;
		पूर्ण
		अगर (port->tx_bufs[txi].skb) अणु
			अगर (d->hdr.state != VIO_DESC_DONE)
				pr_notice("invalid ring buffer state %d\n",
					  d->hdr.state);
			BUG_ON(port->tx_bufs[txi].skb->next);

			port->tx_bufs[txi].skb->next = skb;
			skb = port->tx_bufs[txi].skb;
			port->tx_bufs[txi].skb = शून्य;

			ldc_unmap(port->vio.lp,
				  port->tx_bufs[txi].cookies,
				  port->tx_bufs[txi].ncookies);
		पूर्ण अन्यथा अगर (d->hdr.state == VIO_DESC_FREE) अणु
			अवरोध;
		पूर्ण
		d->hdr.state = VIO_DESC_FREE;
	पूर्ण
	वापस skb;
पूर्ण

अटल अंतरभूत व्योम vnet_मुक्त_skbs(काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *next;

	जबतक (skb) अणु
		next = skb->next;
		skb->next = शून्य;
		dev_kमुक्त_skb(skb);
		skb = next;
	पूर्ण
पूर्ण

व्योम sunvnet_clean_समयr_expire_common(काष्ठा समयr_list *t)
अणु
	काष्ठा vnet_port *port = from_समयr(port, t, clean_समयr);
	काष्ठा sk_buff *मुक्तskbs;
	अचिन्हित pending;

	netअगर_tx_lock(VNET_PORT_TO_NET_DEVICE(port));
	मुक्तskbs = vnet_clean_tx_ring(port, &pending);
	netअगर_tx_unlock(VNET_PORT_TO_NET_DEVICE(port));

	vnet_मुक्त_skbs(मुक्तskbs);

	अगर (pending)
		(व्योम)mod_समयr(&port->clean_समयr,
				jअगरfies + VNET_CLEAN_TIMEOUT);
	 अन्यथा
		del_समयr(&port->clean_समयr);
पूर्ण
EXPORT_SYMBOL_GPL(sunvnet_clean_समयr_expire_common);

अटल अंतरभूत पूर्णांक vnet_skb_map(काष्ठा ldc_channel *lp, काष्ठा sk_buff *skb,
			       काष्ठा ldc_trans_cookie *cookies, पूर्णांक ncookies,
			       अचिन्हित पूर्णांक map_perm)
अणु
	पूर्णांक i, nc, err, blen;

	/* header */
	blen = skb_headlen(skb);
	अगर (blen < ETH_ZLEN)
		blen = ETH_ZLEN;
	blen += VNET_PACKET_SKIP;
	blen += 8 - (blen & 7);

	err = ldc_map_single(lp, skb->data - VNET_PACKET_SKIP, blen, cookies,
			     ncookies, map_perm);
	अगर (err < 0)
		वापस err;
	nc = err;

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		skb_frag_t *f = &skb_shinfo(skb)->frags[i];
		u8 *vaddr;

		अगर (nc < ncookies) अणु
			vaddr = kmap_atomic(skb_frag_page(f));
			blen = skb_frag_size(f);
			blen += 8 - (blen & 7);
			err = ldc_map_single(lp, vaddr + skb_frag_off(f),
					     blen, cookies + nc, ncookies - nc,
					     map_perm);
			kunmap_atomic(vaddr);
		पूर्ण अन्यथा अणु
			err = -EMSGSIZE;
		पूर्ण

		अगर (err < 0) अणु
			ldc_unmap(lp, cookies, nc);
			वापस err;
		पूर्ण
		nc += err;
	पूर्ण
	वापस nc;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *vnet_skb_shape(काष्ठा sk_buff *skb, पूर्णांक ncookies)
अणु
	काष्ठा sk_buff *nskb;
	पूर्णांक i, len, pad, करोcopy;

	len = skb->len;
	pad = 0;
	अगर (len < ETH_ZLEN) अणु
		pad += ETH_ZLEN - skb->len;
		len += pad;
	पूर्ण
	len += VNET_PACKET_SKIP;
	pad += 8 - (len & 7);

	/* make sure we have enough cookies and alignment in every frag */
	करोcopy = skb_shinfo(skb)->nr_frags >= ncookies;
	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		skb_frag_t *f = &skb_shinfo(skb)->frags[i];

		करोcopy |= skb_frag_off(f) & 7;
	पूर्ण
	अगर (((अचिन्हित दीर्घ)skb->data & 7) != VNET_PACKET_SKIP ||
	    skb_tailroom(skb) < pad ||
	    skb_headroom(skb) < VNET_PACKET_SKIP || करोcopy) अणु
		पूर्णांक start = 0, offset;
		__wsum csum;

		len = skb->len > ETH_ZLEN ? skb->len : ETH_ZLEN;
		nskb = alloc_and_align_skb(skb->dev, len);
		अगर (!nskb) अणु
			dev_kमुक्त_skb(skb);
			वापस शून्य;
		पूर्ण
		skb_reserve(nskb, VNET_PACKET_SKIP);

		nskb->protocol = skb->protocol;
		offset = skb_mac_header(skb) - skb->data;
		skb_set_mac_header(nskb, offset);
		offset = skb_network_header(skb) - skb->data;
		skb_set_network_header(nskb, offset);
		offset = skb_transport_header(skb) - skb->data;
		skb_set_transport_header(nskb, offset);

		offset = 0;
		nskb->csum_offset = skb->csum_offset;
		nskb->ip_summed = skb->ip_summed;

		अगर (skb->ip_summed == CHECKSUM_PARTIAL)
			start = skb_checksum_start_offset(skb);
		अगर (start) अणु
			पूर्णांक offset = start + nskb->csum_offset;

			/* copy the headers, no csum here */
			अगर (skb_copy_bits(skb, 0, nskb->data, start)) अणु
				dev_kमुक्त_skb(nskb);
				dev_kमुक्त_skb(skb);
				वापस शून्य;
			पूर्ण

			/* copy the rest, with csum calculation */
			*(__sum16 *)(skb->data + offset) = 0;
			csum = skb_copy_and_csum_bits(skb, start,
						      nskb->data + start,
						      skb->len - start);

			/* add in the header checksums */
			अगर (skb->protocol == htons(ETH_P_IP)) अणु
				काष्ठा iphdr *iph = ip_hdr(nskb);

				अगर (iph->protocol == IPPROTO_TCP ||
				    iph->protocol == IPPROTO_UDP) अणु
					csum = csum_tcpudp_magic(iph->saddr,
								 iph->daddr,
								 skb->len - start,
								 iph->protocol,
								 csum);
				पूर्ण
			पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
				काष्ठा ipv6hdr *ip6h = ipv6_hdr(nskb);

				अगर (ip6h->nexthdr == IPPROTO_TCP ||
				    ip6h->nexthdr == IPPROTO_UDP) अणु
					csum = csum_ipv6_magic(&ip6h->saddr,
							       &ip6h->daddr,
							       skb->len - start,
							       ip6h->nexthdr,
							       csum);
				पूर्ण
			पूर्ण

			/* save the final result */
			*(__sum16 *)(nskb->data + offset) = csum;

			nskb->ip_summed = CHECKSUM_NONE;
		पूर्ण अन्यथा अगर (skb_copy_bits(skb, 0, nskb->data, skb->len)) अणु
			dev_kमुक्त_skb(nskb);
			dev_kमुक्त_skb(skb);
			वापस शून्य;
		पूर्ण
		(व्योम)skb_put(nskb, skb->len);
		अगर (skb_is_gso(skb)) अणु
			skb_shinfo(nskb)->gso_size = skb_shinfo(skb)->gso_size;
			skb_shinfo(nskb)->gso_type = skb_shinfo(skb)->gso_type;
		पूर्ण
		nskb->queue_mapping = skb->queue_mapping;
		dev_kमुक्त_skb(skb);
		skb = nskb;
	पूर्ण
	वापस skb;
पूर्ण

अटल netdev_tx_t
vnet_handle_offloads(काष्ठा vnet_port *port, काष्ठा sk_buff *skb,
		     काष्ठा vnet_port *(*vnet_tx_port)
		     (काष्ठा sk_buff *, काष्ठा net_device *))
अणु
	काष्ठा net_device *dev = VNET_PORT_TO_NET_DEVICE(port);
	काष्ठा vio_dring_state *dr = &port->vio.drings[VIO_DRIVER_TX_RING];
	काष्ठा sk_buff *segs, *curr, *next;
	पूर्णांक maclen, datalen;
	पूर्णांक status;
	पूर्णांक gso_size, gso_type, gso_segs;
	पूर्णांक hlen = skb_transport_header(skb) - skb_mac_header(skb);
	पूर्णांक proto = IPPROTO_IP;

	अगर (skb->protocol == htons(ETH_P_IP))
		proto = ip_hdr(skb)->protocol;
	अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
		proto = ipv6_hdr(skb)->nexthdr;

	अगर (proto == IPPROTO_TCP) अणु
		hlen += tcp_hdr(skb)->करोff * 4;
	पूर्ण अन्यथा अगर (proto == IPPROTO_UDP) अणु
		hlen += माप(काष्ठा udphdr);
	पूर्ण अन्यथा अणु
		pr_err("vnet_handle_offloads GSO with unknown transport "
		       "protocol %d tproto %d\n", skb->protocol, proto);
		hlen = 128; /* XXX */
	पूर्ण
	datalen = port->tsolen - hlen;

	gso_size = skb_shinfo(skb)->gso_size;
	gso_type = skb_shinfo(skb)->gso_type;
	gso_segs = skb_shinfo(skb)->gso_segs;

	अगर (port->tso && gso_size < datalen)
		gso_segs = DIV_ROUND_UP(skb->len - hlen, datalen);

	अगर (unlikely(vnet_tx_dring_avail(dr) < gso_segs)) अणु
		काष्ठा netdev_queue *txq;

		txq  = netdev_get_tx_queue(dev, port->q_index);
		netअगर_tx_stop_queue(txq);
		अगर (vnet_tx_dring_avail(dr) < skb_shinfo(skb)->gso_segs)
			वापस NETDEV_TX_BUSY;
		netअगर_tx_wake_queue(txq);
	पूर्ण

	maclen = skb_network_header(skb) - skb_mac_header(skb);
	skb_pull(skb, maclen);

	अगर (port->tso && gso_size < datalen) अणु
		अगर (skb_unclone(skb, GFP_ATOMIC))
			जाओ out_dropped;

		/* segment to TSO size */
		skb_shinfo(skb)->gso_size = datalen;
		skb_shinfo(skb)->gso_segs = gso_segs;
	पूर्ण
	segs = skb_gso_segment(skb, dev->features & ~NETIF_F_TSO);
	अगर (IS_ERR(segs))
		जाओ out_dropped;

	skb_push(skb, maclen);
	skb_reset_mac_header(skb);

	status = 0;
	skb_list_walk_safe(segs, curr, next) अणु
		skb_mark_not_on_list(curr);
		अगर (port->tso && curr->len > dev->mtu) अणु
			skb_shinfo(curr)->gso_size = gso_size;
			skb_shinfo(curr)->gso_type = gso_type;
			skb_shinfo(curr)->gso_segs =
				DIV_ROUND_UP(curr->len - hlen, gso_size);
		पूर्ण अन्यथा अणु
			skb_shinfo(curr)->gso_size = 0;
		पूर्ण

		skb_push(curr, maclen);
		skb_reset_mac_header(curr);
		स_नकल(skb_mac_header(curr), skb_mac_header(skb),
		       maclen);
		curr->csum_start = skb_transport_header(curr) - curr->head;
		अगर (ip_hdr(curr)->protocol == IPPROTO_TCP)
			curr->csum_offset = दुरत्व(काष्ठा tcphdr, check);
		अन्यथा अगर (ip_hdr(curr)->protocol == IPPROTO_UDP)
			curr->csum_offset = दुरत्व(काष्ठा udphdr, check);

		अगर (!(status & NETDEV_TX_MASK))
			status = sunvnet_start_xmit_common(curr, dev,
							   vnet_tx_port);
		अगर (status & NETDEV_TX_MASK)
			dev_kमुक्त_skb_any(curr);
	पूर्ण

	अगर (!(status & NETDEV_TX_MASK))
		dev_kमुक्त_skb_any(skb);
	वापस status;
out_dropped:
	dev->stats.tx_dropped++;
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

netdev_tx_t
sunvnet_start_xmit_common(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			  काष्ठा vnet_port *(*vnet_tx_port)
			  (काष्ठा sk_buff *, काष्ठा net_device *))
अणु
	काष्ठा vnet_port *port = शून्य;
	काष्ठा vio_dring_state *dr;
	काष्ठा vio_net_desc *d;
	अचिन्हित पूर्णांक len;
	काष्ठा sk_buff *मुक्तskbs = शून्य;
	पूर्णांक i, err, txi;
	अचिन्हित pending = 0;
	काष्ठा netdev_queue *txq;

	rcu_पढ़ो_lock();
	port = vnet_tx_port(skb, dev);
	अगर (unlikely(!port))
		जाओ out_dropped;

	अगर (skb_is_gso(skb) && skb->len > port->tsolen) अणु
		err = vnet_handle_offloads(port, skb, vnet_tx_port);
		rcu_पढ़ो_unlock();
		वापस err;
	पूर्ण

	अगर (!skb_is_gso(skb) && skb->len > port->rmtu) अणु
		अचिन्हित दीर्घ localmtu = port->rmtu - ETH_HLEN;

		अगर (vio_version_after_eq(&port->vio, 1, 3))
			localmtu -= VLAN_HLEN;

		अगर (skb->protocol == htons(ETH_P_IP))
			icmp_nकरो_send(skb, ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED,
				      htonl(localmtu));
#अगर IS_ENABLED(CONFIG_IPV6)
		अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
			icmpv6_nकरो_send(skb, ICMPV6_PKT_TOOBIG, 0, localmtu);
#पूर्ण_अगर
		जाओ out_dropped;
	पूर्ण

	skb = vnet_skb_shape(skb, 2);

	अगर (unlikely(!skb))
		जाओ out_dropped;

	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		अगर (skb->protocol == htons(ETH_P_IP))
			vnet_fullcsum_ipv4(skb);
#अगर IS_ENABLED(CONFIG_IPV6)
		अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
			vnet_fullcsum_ipv6(skb);
#पूर्ण_अगर
	पूर्ण

	dr = &port->vio.drings[VIO_DRIVER_TX_RING];
	i = skb_get_queue_mapping(skb);
	txq = netdev_get_tx_queue(dev, i);
	अगर (unlikely(vnet_tx_dring_avail(dr) < 1)) अणु
		अगर (!netअगर_tx_queue_stopped(txq)) अणु
			netअगर_tx_stop_queue(txq);

			/* This is a hard error, log it. */
			netdev_err(dev, "BUG! Tx Ring full when queue awake!\n");
			dev->stats.tx_errors++;
		पूर्ण
		rcu_पढ़ो_unlock();
		वापस NETDEV_TX_BUSY;
	पूर्ण

	d = vio_dring_cur(dr);

	txi = dr->prod;

	मुक्तskbs = vnet_clean_tx_ring(port, &pending);

	BUG_ON(port->tx_bufs[txi].skb);

	len = skb->len;
	अगर (len < ETH_ZLEN)
		len = ETH_ZLEN;

	err = vnet_skb_map(port->vio.lp, skb, port->tx_bufs[txi].cookies, 2,
			   (LDC_MAP_SHADOW | LDC_MAP_सूचीECT | LDC_MAP_RW));
	अगर (err < 0) अणु
		netdev_info(dev, "tx buffer map error %d\n", err);
		जाओ out_dropped;
	पूर्ण

	port->tx_bufs[txi].skb = skb;
	skb = शून्य;
	port->tx_bufs[txi].ncookies = err;

	/* We करोn't rely on the ACKs to मुक्त the skb in vnet_start_xmit(),
	 * thus it is safe to not set VIO_ACK_ENABLE क्रम each transmission:
	 * the protocol itself करोes not require it as दीर्घ as the peer
	 * sends a VIO_SUBTYPE_ACK क्रम VIO_DRING_STOPPED.
	 *
	 * An ACK क्रम every packet in the ring is expensive as the
	 * sending of LDC messages is slow and affects perक्रमmance.
	 */
	d->hdr.ack = VIO_ACK_DISABLE;
	d->size = len;
	d->ncookies = port->tx_bufs[txi].ncookies;
	क्रम (i = 0; i < d->ncookies; i++)
		d->cookies[i] = port->tx_bufs[txi].cookies[i];
	अगर (vio_version_after_eq(&port->vio, 1, 7)) अणु
		काष्ठा vio_net_dext *dext = vio_net_ext(d);

		स_रखो(dext, 0, माप(*dext));
		अगर (skb_is_gso(port->tx_bufs[txi].skb)) अणु
			dext->ipv4_lso_mss = skb_shinfo(port->tx_bufs[txi].skb)
					     ->gso_size;
			dext->flags |= VNET_PKT_IPV4_LSO;
		पूर्ण
		अगर (vio_version_after_eq(&port->vio, 1, 8) &&
		    !port->चयन_port) अणु
			dext->flags |= VNET_PKT_HCK_IPV4_HDRCKSUM_OK;
			dext->flags |= VNET_PKT_HCK_FULLCKSUM_OK;
		पूर्ण
	पूर्ण

	/* This has to be a non-SMP ग_लिखो barrier because we are writing
	 * to memory which is shared with the peer LDOM.
	 */
	dma_wmb();

	d->hdr.state = VIO_DESC_READY;

	/* Exactly one ldc "start" trigger (क्रम dr->cons) needs to be sent
	 * to notअगरy the consumer that some descriptors are READY.
	 * After that "start" trigger, no additional triggers are needed until
	 * a DRING_STOPPED is received from the consumer. The dr->cons field
	 * (set up by vnet_ack()) has the value of the next dring index
	 * that has not yet been ack-ed. We send a "start" trigger here
	 * अगर, and only अगर, start_cons is true (reset it afterward). Conversely,
	 * vnet_ack() should check अगर the dring corresponding to cons
	 * is marked READY, but start_cons was false.
	 * If so, vnet_ack() should send out the missed "start" trigger.
	 *
	 * Note that the dma_wmb() above makes sure the cookies et al. are
	 * not globally visible beक्रमe the VIO_DESC_READY, and that the
	 * stores are ordered correctly by the compiler. The consumer will
	 * not proceed until the VIO_DESC_READY is visible assuring that
	 * the consumer करोes not observe anything related to descriptors
	 * out of order. The HV trap from the LDC start trigger is the
	 * producer to consumer announcement that work is available to the
	 * consumer
	 */
	अगर (!port->start_cons) अणु /* previous trigger suffices */
		trace_vnet_skip_tx_trigger(port->vio._local_sid,
					   port->vio._peer_sid, dr->cons);
		जाओ ldc_start_करोne;
	पूर्ण

	err = __vnet_tx_trigger(port, dr->cons);
	अगर (unlikely(err < 0)) अणु
		netdev_info(dev, "TX trigger error %d\n", err);
		d->hdr.state = VIO_DESC_FREE;
		skb = port->tx_bufs[txi].skb;
		port->tx_bufs[txi].skb = शून्य;
		dev->stats.tx_carrier_errors++;
		जाओ out_dropped;
	पूर्ण

ldc_start_करोne:
	port->start_cons = false;

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += port->tx_bufs[txi].skb->len;
	port->stats.tx_packets++;
	port->stats.tx_bytes += port->tx_bufs[txi].skb->len;

	dr->prod = (dr->prod + 1) & (VNET_TX_RING_SIZE - 1);
	अगर (unlikely(vnet_tx_dring_avail(dr) < 1)) अणु
		netअगर_tx_stop_queue(txq);
		smp_rmb();
		अगर (vnet_tx_dring_avail(dr) > VNET_TX_WAKEUP_THRESH(dr))
			netअगर_tx_wake_queue(txq);
	पूर्ण

	(व्योम)mod_समयr(&port->clean_समयr, jअगरfies + VNET_CLEAN_TIMEOUT);
	rcu_पढ़ो_unlock();

	vnet_मुक्त_skbs(मुक्तskbs);

	वापस NETDEV_TX_OK;

out_dropped:
	अगर (pending)
		(व्योम)mod_समयr(&port->clean_समयr,
				jअगरfies + VNET_CLEAN_TIMEOUT);
	अन्यथा अगर (port)
		del_समयr(&port->clean_समयr);
	rcu_पढ़ो_unlock();
	dev_kमुक्त_skb(skb);
	vnet_मुक्त_skbs(मुक्तskbs);
	dev->stats.tx_dropped++;
	वापस NETDEV_TX_OK;
पूर्ण
EXPORT_SYMBOL_GPL(sunvnet_start_xmit_common);

व्योम sunvnet_tx_समयout_common(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	/* XXX Implement me XXX */
पूर्ण
EXPORT_SYMBOL_GPL(sunvnet_tx_समयout_common);

पूर्णांक sunvnet_खोलो_common(काष्ठा net_device *dev)
अणु
	netअगर_carrier_on(dev);
	netअगर_tx_start_all_queues(dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sunvnet_खोलो_common);

पूर्णांक sunvnet_बंद_common(काष्ठा net_device *dev)
अणु
	netअगर_tx_stop_all_queues(dev);
	netअगर_carrier_off(dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sunvnet_बंद_common);

अटल काष्ठा vnet_mcast_entry *__vnet_mc_find(काष्ठा vnet *vp, u8 *addr)
अणु
	काष्ठा vnet_mcast_entry *m;

	क्रम (m = vp->mcast_list; m; m = m->next) अणु
		अगर (ether_addr_equal(m->addr, addr))
			वापस m;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम __update_mc_list(काष्ठा vnet *vp, काष्ठा net_device *dev)
अणु
	काष्ठा netdev_hw_addr *ha;

	netdev_क्रम_each_mc_addr(ha, dev) अणु
		काष्ठा vnet_mcast_entry *m;

		m = __vnet_mc_find(vp, ha->addr);
		अगर (m) अणु
			m->hit = 1;
			जारी;
		पूर्ण

		अगर (!m) अणु
			m = kzalloc(माप(*m), GFP_ATOMIC);
			अगर (!m)
				जारी;
			स_नकल(m->addr, ha->addr, ETH_ALEN);
			m->hit = 1;

			m->next = vp->mcast_list;
			vp->mcast_list = m;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __send_mc_list(काष्ठा vnet *vp, काष्ठा vnet_port *port)
अणु
	काष्ठा vio_net_mcast_info info;
	काष्ठा vnet_mcast_entry *m, **pp;
	पूर्णांक n_addrs;

	स_रखो(&info, 0, माप(info));

	info.tag.type = VIO_TYPE_CTRL;
	info.tag.stype = VIO_SUBTYPE_INFO;
	info.tag.stype_env = VNET_MCAST_INFO;
	info.tag.sid = vio_send_sid(&port->vio);
	info.set = 1;

	n_addrs = 0;
	क्रम (m = vp->mcast_list; m; m = m->next) अणु
		अगर (m->sent)
			जारी;
		m->sent = 1;
		स_नकल(&info.mcast_addr[n_addrs * ETH_ALEN],
		       m->addr, ETH_ALEN);
		अगर (++n_addrs == VNET_NUM_MCAST) अणु
			info.count = n_addrs;

			(व्योम)vio_ldc_send(&port->vio, &info,
					   माप(info));
			n_addrs = 0;
		पूर्ण
	पूर्ण
	अगर (n_addrs) अणु
		info.count = n_addrs;
		(व्योम)vio_ldc_send(&port->vio, &info, माप(info));
	पूर्ण

	info.set = 0;

	n_addrs = 0;
	pp = &vp->mcast_list;
	जबतक ((m = *pp) != शून्य) अणु
		अगर (m->hit) अणु
			m->hit = 0;
			pp = &m->next;
			जारी;
		पूर्ण

		स_नकल(&info.mcast_addr[n_addrs * ETH_ALEN],
		       m->addr, ETH_ALEN);
		अगर (++n_addrs == VNET_NUM_MCAST) अणु
			info.count = n_addrs;
			(व्योम)vio_ldc_send(&port->vio, &info,
					   माप(info));
			n_addrs = 0;
		पूर्ण

		*pp = m->next;
		kमुक्त(m);
	पूर्ण
	अगर (n_addrs) अणु
		info.count = n_addrs;
		(व्योम)vio_ldc_send(&port->vio, &info, माप(info));
	पूर्ण
पूर्ण

व्योम sunvnet_set_rx_mode_common(काष्ठा net_device *dev, काष्ठा vnet *vp)
अणु
	काष्ठा vnet_port *port;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(port, &vp->port_list, list) अणु
		अगर (port->चयन_port) अणु
			__update_mc_list(vp, dev);
			__send_mc_list(vp, port);
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(sunvnet_set_rx_mode_common);

पूर्णांक sunvnet_set_mac_addr_common(काष्ठा net_device *dev, व्योम *p)
अणु
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(sunvnet_set_mac_addr_common);

व्योम sunvnet_port_मुक्त_tx_bufs_common(काष्ठा vnet_port *port)
अणु
	काष्ठा vio_dring_state *dr;
	पूर्णांक i;

	dr = &port->vio.drings[VIO_DRIVER_TX_RING];

	अगर (!dr->base)
		वापस;

	क्रम (i = 0; i < VNET_TX_RING_SIZE; i++) अणु
		काष्ठा vio_net_desc *d;
		व्योम *skb = port->tx_bufs[i].skb;

		अगर (!skb)
			जारी;

		d = vio_dring_entry(dr, i);

		ldc_unmap(port->vio.lp,
			  port->tx_bufs[i].cookies,
			  port->tx_bufs[i].ncookies);
		dev_kमुक्त_skb(skb);
		port->tx_bufs[i].skb = शून्य;
		d->hdr.state = VIO_DESC_FREE;
	पूर्ण
	ldc_मुक्त_exp_dring(port->vio.lp, dr->base,
			   (dr->entry_size * dr->num_entries),
			   dr->cookies, dr->ncookies);
	dr->base = शून्य;
	dr->entry_size = 0;
	dr->num_entries = 0;
	dr->pending = 0;
	dr->ncookies = 0;
पूर्ण
EXPORT_SYMBOL_GPL(sunvnet_port_मुक्त_tx_bufs_common);

व्योम vnet_port_reset(काष्ठा vnet_port *port)
अणु
	del_समयr(&port->clean_समयr);
	sunvnet_port_मुक्त_tx_bufs_common(port);
	port->rmtu = 0;
	port->tso = (port->vsw == 0);  /* no tso in vsw, misbehaves in bridge */
	port->tsolen = 0;
पूर्ण
EXPORT_SYMBOL_GPL(vnet_port_reset);

अटल पूर्णांक vnet_port_alloc_tx_ring(काष्ठा vnet_port *port)
अणु
	काष्ठा vio_dring_state *dr;
	अचिन्हित दीर्घ len, elen;
	पूर्णांक i, err, ncookies;
	व्योम *dring;

	dr = &port->vio.drings[VIO_DRIVER_TX_RING];

	elen = माप(काष्ठा vio_net_desc) +
	       माप(काष्ठा ldc_trans_cookie) * 2;
	अगर (vio_version_after_eq(&port->vio, 1, 7))
		elen += माप(काष्ठा vio_net_dext);
	len = VNET_TX_RING_SIZE * elen;

	ncookies = VIO_MAX_RING_COOKIES;
	dring = ldc_alloc_exp_dring(port->vio.lp, len,
				    dr->cookies, &ncookies,
				    (LDC_MAP_SHADOW |
				     LDC_MAP_सूचीECT |
				     LDC_MAP_RW));
	अगर (IS_ERR(dring)) अणु
		err = PTR_ERR(dring);
		जाओ err_out;
	पूर्ण

	dr->base = dring;
	dr->entry_size = elen;
	dr->num_entries = VNET_TX_RING_SIZE;
	dr->prod = 0;
	dr->cons = 0;
	port->start_cons  = true; /* need an initial trigger */
	dr->pending = VNET_TX_RING_SIZE;
	dr->ncookies = ncookies;

	क्रम (i = 0; i < VNET_TX_RING_SIZE; ++i) अणु
		काष्ठा vio_net_desc *d;

		d = vio_dring_entry(dr, i);
		d->hdr.state = VIO_DESC_FREE;
	पूर्ण
	वापस 0;

err_out:
	sunvnet_port_मुक्त_tx_bufs_common(port);

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
व्योम sunvnet_poll_controller_common(काष्ठा net_device *dev, काष्ठा vnet *vp)
अणु
	काष्ठा vnet_port *port;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vp->lock, flags);
	अगर (!list_empty(&vp->port_list)) अणु
		port = list_entry(vp->port_list.next, काष्ठा vnet_port, list);
		napi_schedule(&port->napi);
	पूर्ण
	spin_unlock_irqrestore(&vp->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(sunvnet_poll_controller_common);
#पूर्ण_अगर

व्योम sunvnet_port_add_txq_common(काष्ठा vnet_port *port)
अणु
	काष्ठा vnet *vp = port->vp;
	पूर्णांक smallest = 0;
	पूर्णांक i;

	/* find the first least-used q
	 * When there are more lकरोms than q's, we start to
	 * द्विगुन up on ports per queue.
	 */
	क्रम (i = 0; i < VNET_MAX_TXQS; i++) अणु
		अगर (vp->q_used[i] == 0) अणु
			smallest = i;
			अवरोध;
		पूर्ण
		अगर (vp->q_used[i] < vp->q_used[smallest])
			smallest = i;
	पूर्ण

	vp->nports++;
	vp->q_used[smallest]++;
	port->q_index = smallest;
पूर्ण
EXPORT_SYMBOL_GPL(sunvnet_port_add_txq_common);

व्योम sunvnet_port_rm_txq_common(काष्ठा vnet_port *port)
अणु
	port->vp->nports--;
	port->vp->q_used[port->q_index]--;
	port->q_index = 0;
पूर्ण
EXPORT_SYMBOL_GPL(sunvnet_port_rm_txq_common);
