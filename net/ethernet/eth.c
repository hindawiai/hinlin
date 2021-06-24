<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Ethernet-type device handling.
 *
 * Version:	@(#)eth.c	1.0.7	05/25/93
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Mark Evans, <evansmp@uhura.aston.ac.uk>
 *		Florian  La Roche, <rzsfl@rz.uni-sb.de>
 *		Alan Cox, <gw4pts@gw4pts.ampr.org>
 *
 * Fixes:
 *		Mr Linux	: Arp problems
 *		Alan Cox	: Generic queue tidyup (very tiny here)
 *		Alan Cox	: eth_header ntohs should be htons
 *		Alan Cox	: eth_rebuild_header missing an htons and
 *				  minor other things.
 *		Tegge		: Arp bug fixes.
 *		Florian		: Removed many unnecessary functions, code cleanup
 *				  and changes क्रम new arp and skbuff.
 *		Alan Cox	: Redid header building to reflect new क्रमmat.
 *		Alan Cox	: ARP only when compiled with CONFIG_INET
 *		Greg Page	: 802.2 and SNAP stuff.
 *		Alan Cox	: MAC layer poपूर्णांकers/new क्रमmat.
 *		Paul Gorपंचांगaker	: eth_copy_and_sum shouldn't csum padding.
 *		Alan Cox	: Protect against क्रमwarding explosions with
 *				  older network drivers and IFF_ALLMULTI.
 *	Christer Weinigel	: Better rebuild header message.
 *             Andrew Morton    : 26Feb01: समाप्त ether_setup() - use netdev_boot_setup().
 */
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <linux/ip.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/of_net.h>
#समावेश <linux/pci.h>
#समावेश <net/dst.h>
#समावेश <net/arp.h>
#समावेश <net/sock.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip.h>
#समावेश <net/dsa.h>
#समावेश <net/flow_dissector.h>
#समावेश <net/gro.h>
#समावेश <linux/uaccess.h>
#समावेश <net/pkt_sched.h>

__setup("ether=", netdev_boot_setup);

/**
 * eth_header - create the Ethernet header
 * @skb:	buffer to alter
 * @dev:	source device
 * @type:	Ethernet type field
 * @daddr: destination address (शून्य leave destination address)
 * @saddr: source address (शून्य use device source address)
 * @len:   packet length (<= skb->len)
 *
 *
 * Set the protocol type. For a packet of type ETH_P_802_3/2 we put the length
 * in here instead.
 */
पूर्णांक eth_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
	       अचिन्हित लघु type,
	       स्थिर व्योम *daddr, स्थिर व्योम *saddr, अचिन्हित पूर्णांक len)
अणु
	काष्ठा ethhdr *eth = skb_push(skb, ETH_HLEN);

	अगर (type != ETH_P_802_3 && type != ETH_P_802_2)
		eth->h_proto = htons(type);
	अन्यथा
		eth->h_proto = htons(len);

	/*
	 *      Set the source hardware address.
	 */

	अगर (!saddr)
		saddr = dev->dev_addr;
	स_नकल(eth->h_source, saddr, ETH_ALEN);

	अगर (daddr) अणु
		स_नकल(eth->h_dest, daddr, ETH_ALEN);
		वापस ETH_HLEN;
	पूर्ण

	/*
	 *      Anyway, the loopback-device should never use this function...
	 */

	अगर (dev->flags & (IFF_LOOPBACK | IFF_NOARP)) अणु
		eth_zero_addr(eth->h_dest);
		वापस ETH_HLEN;
	पूर्ण

	वापस -ETH_HLEN;
पूर्ण
EXPORT_SYMBOL(eth_header);

/**
 * eth_get_headlen - determine the length of header क्रम an ethernet frame
 * @dev: poपूर्णांकer to network device
 * @data: poपूर्णांकer to start of frame
 * @len: total length of frame
 *
 * Make a best efक्रमt attempt to pull the length क्रम all of the headers क्रम
 * a given frame in a linear buffer.
 */
u32 eth_get_headlen(स्थिर काष्ठा net_device *dev, स्थिर व्योम *data, u32 len)
अणु
	स्थिर अचिन्हित पूर्णांक flags = FLOW_DISSECTOR_F_PARSE_1ST_FRAG;
	स्थिर काष्ठा ethhdr *eth = (स्थिर काष्ठा ethhdr *)data;
	काष्ठा flow_keys_basic keys;

	/* this should never happen, but better safe than sorry */
	अगर (unlikely(len < माप(*eth)))
		वापस len;

	/* parse any reमुख्यing L2/L3 headers, check क्रम L4 */
	अगर (!skb_flow_dissect_flow_keys_basic(dev_net(dev), शून्य, &keys, data,
					      eth->h_proto, माप(*eth),
					      len, flags))
		वापस max_t(u32, keys.control.thoff, माप(*eth));

	/* parse क्रम any L4 headers */
	वापस min_t(u32, __skb_get_poff(शून्य, data, &keys, len), len);
पूर्ण
EXPORT_SYMBOL(eth_get_headlen);

/**
 * eth_type_trans - determine the packet's protocol ID.
 * @skb: received socket data
 * @dev: receiving network device
 *
 * The rule here is that we
 * assume 802.3 अगर the type field is लघु enough to be a length.
 * This is normal practice and works क्रम any 'now in use' protocol.
 */
__be16 eth_type_trans(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	अचिन्हित लघु _service_access_poपूर्णांक;
	स्थिर अचिन्हित लघु *sap;
	स्थिर काष्ठा ethhdr *eth;

	skb->dev = dev;
	skb_reset_mac_header(skb);

	eth = (काष्ठा ethhdr *)skb->data;
	skb_pull_अंतरभूत(skb, ETH_HLEN);

	अगर (unlikely(!ether_addr_equal_64bits(eth->h_dest,
					      dev->dev_addr))) अणु
		अगर (unlikely(is_multicast_ether_addr_64bits(eth->h_dest))) अणु
			अगर (ether_addr_equal_64bits(eth->h_dest, dev->broadcast))
				skb->pkt_type = PACKET_BROADCAST;
			अन्यथा
				skb->pkt_type = PACKET_MULTICAST;
		पूर्ण अन्यथा अणु
			skb->pkt_type = PACKET_OTHERHOST;
		पूर्ण
	पूर्ण

	/*
	 * Some variants of DSA tagging करोn't have an ethertype field
	 * at all, so we check here whether one of those tagging
	 * variants has been configured on the receiving पूर्णांकerface,
	 * and अगर so, set skb->protocol without looking at the packet.
	 * The DSA tagging protocol may be able to decode some but not all
	 * traffic (क्रम example only क्रम management). In that हाल give it the
	 * option to filter the packets from which it can decode source port
	 * inक्रमmation.
	 */
	अगर (unlikely(netdev_uses_dsa(dev)) && dsa_can_decode(skb, dev))
		वापस htons(ETH_P_XDSA);

	अगर (likely(eth_proto_is_802_3(eth->h_proto)))
		वापस eth->h_proto;

	/*
	 *      This is a magic hack to spot IPX packets. Older Novell अवरोधs
	 *      the protocol design and runs IPX over 802.3 without an 802.2 LLC
	 *      layer. We look क्रम FFFF which isn't a used 802.2 SSAP/DSAP. This
	 *      won't work क्रम fault tolerant netware but करोes क्रम the rest.
	 */
	sap = skb_header_poपूर्णांकer(skb, 0, माप(*sap), &_service_access_poपूर्णांक);
	अगर (sap && *sap == 0xFFFF)
		वापस htons(ETH_P_802_3);

	/*
	 *      Real 802.2 LLC
	 */
	वापस htons(ETH_P_802_2);
पूर्ण
EXPORT_SYMBOL(eth_type_trans);

/**
 * eth_header_parse - extract hardware address from packet
 * @skb: packet to extract header from
 * @haddr: destination buffer
 */
पूर्णांक eth_header_parse(स्थिर काष्ठा sk_buff *skb, अचिन्हित अक्षर *haddr)
अणु
	स्थिर काष्ठा ethhdr *eth = eth_hdr(skb);
	स_नकल(haddr, eth->h_source, ETH_ALEN);
	वापस ETH_ALEN;
पूर्ण
EXPORT_SYMBOL(eth_header_parse);

/**
 * eth_header_cache - fill cache entry from neighbour
 * @neigh: source neighbour
 * @hh: destination cache entry
 * @type: Ethernet type field
 *
 * Create an Ethernet header ढाँचा from the neighbour.
 */
पूर्णांक eth_header_cache(स्थिर काष्ठा neighbour *neigh, काष्ठा hh_cache *hh, __be16 type)
अणु
	काष्ठा ethhdr *eth;
	स्थिर काष्ठा net_device *dev = neigh->dev;

	eth = (काष्ठा ethhdr *)
	    (((u8 *) hh->hh_data) + (HH_DATA_OFF(माप(*eth))));

	अगर (type == htons(ETH_P_802_3))
		वापस -1;

	eth->h_proto = type;
	स_नकल(eth->h_source, dev->dev_addr, ETH_ALEN);
	स_नकल(eth->h_dest, neigh->ha, ETH_ALEN);

	/* Pairs with READ_ONCE() in neigh_resolve_output(),
	 * neigh_hh_output() and neigh_update_hhs().
	 */
	smp_store_release(&hh->hh_len, ETH_HLEN);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(eth_header_cache);

/**
 * eth_header_cache_update - update cache entry
 * @hh: destination cache entry
 * @dev: network device
 * @haddr: new hardware address
 *
 * Called by Address Resolution module to notअगरy changes in address.
 */
व्योम eth_header_cache_update(काष्ठा hh_cache *hh,
			     स्थिर काष्ठा net_device *dev,
			     स्थिर अचिन्हित अक्षर *haddr)
अणु
	स_नकल(((u8 *) hh->hh_data) + HH_DATA_OFF(माप(काष्ठा ethhdr)),
	       haddr, ETH_ALEN);
पूर्ण
EXPORT_SYMBOL(eth_header_cache_update);

/**
 * eth_header_parse_protocol - extract protocol from L2 header
 * @skb: packet to extract protocol from
 */
__be16 eth_header_parse_protocol(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ethhdr *eth = eth_hdr(skb);

	वापस eth->h_proto;
पूर्ण
EXPORT_SYMBOL(eth_header_parse_protocol);

/**
 * eth_prepare_mac_addr_change - prepare क्रम mac change
 * @dev: network device
 * @p: socket address
 */
पूर्णांक eth_prepare_mac_addr_change(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;

	अगर (!(dev->priv_flags & IFF_LIVE_ADDR_CHANGE) && netअगर_running(dev))
		वापस -EBUSY;
	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(eth_prepare_mac_addr_change);

/**
 * eth_commit_mac_addr_change - commit mac change
 * @dev: network device
 * @p: socket address
 */
व्योम eth_commit_mac_addr_change(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;

	स_नकल(dev->dev_addr, addr->sa_data, ETH_ALEN);
पूर्ण
EXPORT_SYMBOL(eth_commit_mac_addr_change);

/**
 * eth_mac_addr - set new Ethernet hardware address
 * @dev: network device
 * @p: socket address
 *
 * Change hardware address of device.
 *
 * This करोesn't change hardware matching, so needs to be overridden
 * क्रम most real devices.
 */
पूर्णांक eth_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	पूर्णांक ret;

	ret = eth_prepare_mac_addr_change(dev, p);
	अगर (ret < 0)
		वापस ret;
	eth_commit_mac_addr_change(dev, p);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(eth_mac_addr);

पूर्णांक eth_validate_addr(काष्ठा net_device *dev)
अणु
	अगर (!is_valid_ether_addr(dev->dev_addr))
		वापस -EADDRNOTAVAIL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(eth_validate_addr);

स्थिर काष्ठा header_ops eth_header_ops ____cacheline_aligned = अणु
	.create		= eth_header,
	.parse		= eth_header_parse,
	.cache		= eth_header_cache,
	.cache_update	= eth_header_cache_update,
	.parse_protocol	= eth_header_parse_protocol,
पूर्ण;

/**
 * ether_setup - setup Ethernet network device
 * @dev: network device
 *
 * Fill in the fields of the device काष्ठाure with Ethernet-generic values.
 */
व्योम ether_setup(काष्ठा net_device *dev)
अणु
	dev->header_ops		= &eth_header_ops;
	dev->type		= ARPHRD_ETHER;
	dev->hard_header_len 	= ETH_HLEN;
	dev->min_header_len	= ETH_HLEN;
	dev->mtu		= ETH_DATA_LEN;
	dev->min_mtu		= ETH_MIN_MTU;
	dev->max_mtu		= ETH_DATA_LEN;
	dev->addr_len		= ETH_ALEN;
	dev->tx_queue_len	= DEFAULT_TX_QUEUE_LEN;
	dev->flags		= IFF_BROADCAST|IFF_MULTICAST;
	dev->priv_flags		|= IFF_TX_SKB_SHARING;

	eth_broadcast_addr(dev->broadcast);

पूर्ण
EXPORT_SYMBOL(ether_setup);

/**
 * alloc_etherdev_mqs - Allocates and sets up an Ethernet device
 * @माप_priv: Size of additional driver-निजी काष्ठाure to be allocated
 *	क्रम this Ethernet device
 * @txqs: The number of TX queues this device has.
 * @rxqs: The number of RX queues this device has.
 *
 * Fill in the fields of the device काष्ठाure with Ethernet-generic
 * values. Basically करोes everything except रेजिस्टरing the device.
 *
 * Conकाष्ठाs a new net device, complete with a निजी data area of
 * size (माप_priv).  A 32-byte (not bit) alignment is enक्रमced क्रम
 * this निजी data area.
 */

काष्ठा net_device *alloc_etherdev_mqs(पूर्णांक माप_priv, अचिन्हित पूर्णांक txqs,
				      अचिन्हित पूर्णांक rxqs)
अणु
	वापस alloc_netdev_mqs(माप_priv, "eth%d", NET_NAME_UNKNOWN,
				ether_setup, txqs, rxqs);
पूर्ण
EXPORT_SYMBOL(alloc_etherdev_mqs);

sमाप_प्रकार sysfs_क्रमmat_mac(अक्षर *buf, स्थिर अचिन्हित अक्षर *addr, पूर्णांक len)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%*phC\n", len, addr);
पूर्ण
EXPORT_SYMBOL(sysfs_क्रमmat_mac);

काष्ठा sk_buff *eth_gro_receive(काष्ठा list_head *head, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा packet_offload *ptype;
	अचिन्हित पूर्णांक hlen, off_eth;
	काष्ठा sk_buff *pp = शून्य;
	काष्ठा ethhdr *eh, *eh2;
	काष्ठा sk_buff *p;
	__be16 type;
	पूर्णांक flush = 1;

	off_eth = skb_gro_offset(skb);
	hlen = off_eth + माप(*eh);
	eh = skb_gro_header_fast(skb, off_eth);
	अगर (skb_gro_header_hard(skb, hlen)) अणु
		eh = skb_gro_header_slow(skb, hlen, off_eth);
		अगर (unlikely(!eh))
			जाओ out;
	पूर्ण

	flush = 0;

	list_क्रम_each_entry(p, head, list) अणु
		अगर (!NAPI_GRO_CB(p)->same_flow)
			जारी;

		eh2 = (काष्ठा ethhdr *)(p->data + off_eth);
		अगर (compare_ether_header(eh, eh2)) अणु
			NAPI_GRO_CB(p)->same_flow = 0;
			जारी;
		पूर्ण
	पूर्ण

	type = eh->h_proto;

	rcu_पढ़ो_lock();
	ptype = gro_find_receive_by_type(type);
	अगर (ptype == शून्य) अणु
		flush = 1;
		जाओ out_unlock;
	पूर्ण

	skb_gro_pull(skb, माप(*eh));
	skb_gro_postpull_rcsum(skb, eh, माप(*eh));

	pp = indirect_call_gro_receive_inet(ptype->callbacks.gro_receive,
					    ipv6_gro_receive, inet_gro_receive,
					    head, skb);

out_unlock:
	rcu_पढ़ो_unlock();
out:
	skb_gro_flush_final(skb, pp, flush);

	वापस pp;
पूर्ण
EXPORT_SYMBOL(eth_gro_receive);

पूर्णांक eth_gro_complete(काष्ठा sk_buff *skb, पूर्णांक nhoff)
अणु
	काष्ठा ethhdr *eh = (काष्ठा ethhdr *)(skb->data + nhoff);
	__be16 type = eh->h_proto;
	काष्ठा packet_offload *ptype;
	पूर्णांक err = -ENOSYS;

	अगर (skb->encapsulation)
		skb_set_inner_mac_header(skb, nhoff);

	rcu_पढ़ो_lock();
	ptype = gro_find_complete_by_type(type);
	अगर (ptype != शून्य)
		err = INसूचीECT_CALL_INET(ptype->callbacks.gro_complete,
					 ipv6_gro_complete, inet_gro_complete,
					 skb, nhoff + माप(*eh));

	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण
EXPORT_SYMBOL(eth_gro_complete);

अटल काष्ठा packet_offload eth_packet_offload __पढ़ो_mostly = अणु
	.type = cpu_to_be16(ETH_P_TEB),
	.priority = 10,
	.callbacks = अणु
		.gro_receive = eth_gro_receive,
		.gro_complete = eth_gro_complete,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init eth_offload_init(व्योम)
अणु
	dev_add_offload(&eth_packet_offload);

	वापस 0;
पूर्ण

fs_initcall(eth_offload_init);

अचिन्हित अक्षर * __weak arch_get_platक्रमm_mac_address(व्योम)
अणु
	वापस शून्य;
पूर्ण

पूर्णांक eth_platक्रमm_get_mac_address(काष्ठा device *dev, u8 *mac_addr)
अणु
	अचिन्हित अक्षर *addr;
	पूर्णांक ret;

	ret = of_get_mac_address(dev->of_node, mac_addr);
	अगर (!ret)
		वापस 0;

	addr = arch_get_platक्रमm_mac_address();
	अगर (!addr)
		वापस -ENODEV;

	ether_addr_copy(mac_addr, addr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(eth_platक्रमm_get_mac_address);

/**
 * nvmem_get_mac_address - Obtain the MAC address from an nvmem cell named
 * 'mac-address' associated with given device.
 *
 * @dev:	Device with which the mac-address cell is associated.
 * @addrbuf:	Buffer to which the MAC address will be copied on success.
 *
 * Returns 0 on success or a negative error number on failure.
 */
पूर्णांक nvmem_get_mac_address(काष्ठा device *dev, व्योम *addrbuf)
अणु
	काष्ठा nvmem_cell *cell;
	स्थिर व्योम *mac;
	माप_प्रकार len;

	cell = nvmem_cell_get(dev, "mac-address");
	अगर (IS_ERR(cell))
		वापस PTR_ERR(cell);

	mac = nvmem_cell_पढ़ो(cell, &len);
	nvmem_cell_put(cell);

	अगर (IS_ERR(mac))
		वापस PTR_ERR(mac);

	अगर (len != ETH_ALEN || !is_valid_ether_addr(mac)) अणु
		kमुक्त(mac);
		वापस -EINVAL;
	पूर्ण

	ether_addr_copy(addrbuf, mac);
	kमुक्त(mac);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nvmem_get_mac_address);
