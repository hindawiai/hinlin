<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2012 GCT Semiconductor, Inc. All rights reserved. */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/etherdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/udp.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/in6.h>
#समावेश <linux/tcp.h>
#समावेश <linux/icmp.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <net/ndisc.h>

#समावेश "gdm_lte.h"
#समावेश "netlink_k.h"
#समावेश "hci.h"
#समावेश "hci_packet.h"
#समावेश "gdm_endian.h"

/*
 * Netlink protocol number
 */
#घोषणा NETLINK_LTE 30

/*
 * Default MTU Size
 */
#घोषणा DEFAULT_MTU_SIZE 1500

#घोषणा IP_VERSION_4	4
#घोषणा IP_VERSION_6	6

अटल काष्ठा अणु
	पूर्णांक ref_cnt;
	काष्ठा sock *sock;
पूर्ण lte_event;

अटल काष्ठा device_type wwan_type = अणु
	.name   = "wwan",
पूर्ण;

अटल पूर्णांक gdm_lte_खोलो(काष्ठा net_device *dev)
अणु
	netअगर_start_queue(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक gdm_lte_बंद(काष्ठा net_device *dev)
अणु
	netअगर_stop_queue(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक gdm_lte_set_config(काष्ठा net_device *dev, काष्ठा अगरmap *map)
अणु
	अगर (dev->flags & IFF_UP)
		वापस -EBUSY;
	वापस 0;
पूर्ण

अटल व्योम tx_complete(व्योम *arg)
अणु
	काष्ठा nic *nic = arg;

	अगर (netअगर_queue_stopped(nic->netdev))
		netअगर_wake_queue(nic->netdev);
पूर्ण

अटल पूर्णांक gdm_lte_rx(काष्ठा sk_buff *skb, काष्ठा nic *nic, पूर्णांक nic_type)
अणु
	पूर्णांक ret;

	ret = netअगर_rx_ni(skb);
	अगर (ret == NET_RX_DROP) अणु
		nic->stats.rx_dropped++;
	पूर्ण अन्यथा अणु
		nic->stats.rx_packets++;
		nic->stats.rx_bytes += skb->len + ETH_HLEN;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gdm_lte_emulate_arp(काष्ठा sk_buff *skb_in, u32 nic_type)
अणु
	काष्ठा nic *nic = netdev_priv(skb_in->dev);
	काष्ठा sk_buff *skb_out;
	काष्ठा ethhdr eth;
	काष्ठा vlan_ethhdr vlan_eth;
	काष्ठा arphdr *arp_in;
	काष्ठा arphdr *arp_out;
	काष्ठा arpdata अणु
		u8 ar_sha[ETH_ALEN];
		u8 ar_sip[4];
		u8 ar_tha[ETH_ALEN];
		u8 ar_tip[4];
	पूर्ण;
	काष्ठा arpdata *arp_data_in;
	काष्ठा arpdata *arp_data_out;
	u8 arp_temp[60];
	व्योम *mac_header_data;
	u32 mac_header_len;

	/* Check क्रम skb->len, discard अगर empty */
	अगर (skb_in->len == 0)
		वापस -ENODATA;

	/* Format the mac header so that it can be put to skb */
	अगर (ntohs(((काष्ठा ethhdr *)skb_in->data)->h_proto) == ETH_P_8021Q) अणु
		स_नकल(&vlan_eth, skb_in->data, माप(काष्ठा vlan_ethhdr));
		mac_header_data = &vlan_eth;
		mac_header_len = VLAN_ETH_HLEN;
	पूर्ण अन्यथा अणु
		स_नकल(&eth, skb_in->data, माप(काष्ठा ethhdr));
		mac_header_data = &eth;
		mac_header_len = ETH_HLEN;
	पूर्ण

	/* Get the poपूर्णांकer of the original request */
	arp_in = (काष्ठा arphdr *)(skb_in->data + mac_header_len);
	arp_data_in = (काष्ठा arpdata *)(skb_in->data + mac_header_len +
					माप(काष्ठा arphdr));

	/* Get the poपूर्णांकer of the outgoing response */
	arp_out = (काष्ठा arphdr *)arp_temp;
	arp_data_out = (काष्ठा arpdata *)(arp_temp + माप(काष्ठा arphdr));

	/* Copy the arp header */
	स_नकल(arp_out, arp_in, माप(काष्ठा arphdr));
	arp_out->ar_op = htons(ARPOP_REPLY);

	/* Copy the arp payload: based on 2 bytes of mac and fill the IP */
	arp_data_out->ar_sha[0] = arp_data_in->ar_sha[0];
	arp_data_out->ar_sha[1] = arp_data_in->ar_sha[1];
	स_नकल(&arp_data_out->ar_sha[2], &arp_data_in->ar_tip[0], 4);
	स_नकल(&arp_data_out->ar_sip[0], &arp_data_in->ar_tip[0], 4);
	स_नकल(&arp_data_out->ar_tha[0], &arp_data_in->ar_sha[0], 6);
	स_नकल(&arp_data_out->ar_tip[0], &arp_data_in->ar_sip[0], 4);

	/* Fill the destination mac with source mac of the received packet */
	स_नकल(mac_header_data, mac_header_data + ETH_ALEN, ETH_ALEN);
	/* Fill the source mac with nic's source mac */
	स_नकल(mac_header_data + ETH_ALEN, nic->src_mac_addr, ETH_ALEN);

	/* Alloc skb and reserve align */
	skb_out = dev_alloc_skb(skb_in->len);
	अगर (!skb_out)
		वापस -ENOMEM;
	skb_reserve(skb_out, NET_IP_ALIGN);

	skb_put_data(skb_out, mac_header_data, mac_header_len);
	skb_put_data(skb_out, arp_out, माप(काष्ठा arphdr));
	skb_put_data(skb_out, arp_data_out, माप(काष्ठा arpdata));

	skb_out->protocol = ((काष्ठा ethhdr *)mac_header_data)->h_proto;
	skb_out->dev = skb_in->dev;
	skb_reset_mac_header(skb_out);
	skb_pull(skb_out, ETH_HLEN);

	gdm_lte_rx(skb_out, nic, nic_type);

	वापस 0;
पूर्ण

अटल __sum16 icmp6_checksum(काष्ठा ipv6hdr *ipv6, u16 *ptr, पूर्णांक len)
अणु
	अचिन्हित लघु *w;
	__wsum sum = 0;
	पूर्णांक i;
	u16 pa;

	जोड़ अणु
		काष्ठा अणु
			u8 ph_src[16];
			u8 ph_dst[16];
			u32 ph_len;
			u8 ph_zero[3];
			u8 ph_nxt;
		पूर्ण ph __packed;
		u16 pa[20];
	पूर्ण pseuकरो_header;

	स_रखो(&pseuकरो_header, 0, माप(pseuकरो_header));
	स_नकल(&pseuकरो_header.ph.ph_src, &ipv6->saddr.in6_u.u6_addr8, 16);
	स_नकल(&pseuकरो_header.ph.ph_dst, &ipv6->daddr.in6_u.u6_addr8, 16);
	pseuकरो_header.ph.ph_len = be16_to_cpu(ipv6->payload_len);
	pseuकरो_header.ph.ph_nxt = ipv6->nexthdr;

	w = (u16 *)&pseuकरो_header;
	क्रम (i = 0; i < ARRAY_SIZE(pseuकरो_header.pa); i++) अणु
		pa = pseuकरो_header.pa[i];
		sum = csum_add(sum, csum_unfold((__क्रमce __sum16)pa));
	पूर्ण

	w = ptr;
	जबतक (len > 1) अणु
		sum = csum_add(sum, csum_unfold((__क्रमce __sum16)*w++));
		len -= 2;
	पूर्ण

	वापस csum_fold(sum);
पूर्ण

अटल पूर्णांक gdm_lte_emulate_ndp(काष्ठा sk_buff *skb_in, u32 nic_type)
अणु
	काष्ठा nic *nic = netdev_priv(skb_in->dev);
	काष्ठा sk_buff *skb_out;
	काष्ठा ethhdr eth;
	काष्ठा vlan_ethhdr vlan_eth;
	काष्ठा neighbour_advertisement अणु
		u8 target_address[16];
		u8 type;
		u8 length;
		u8 link_layer_address[6];
	पूर्ण;
	काष्ठा neighbour_advertisement na;
	काष्ठा neighbour_solicitation अणु
		u8 target_address[16];
	पूर्ण;
	काष्ठा neighbour_solicitation *ns;
	काष्ठा ipv6hdr *ipv6_in;
	काष्ठा ipv6hdr ipv6_out;
	काष्ठा icmp6hdr *icmp6_in;
	काष्ठा icmp6hdr icmp6_out;

	व्योम *mac_header_data;
	u32 mac_header_len;

	/* Format the mac header so that it can be put to skb */
	अगर (ntohs(((काष्ठा ethhdr *)skb_in->data)->h_proto) == ETH_P_8021Q) अणु
		स_नकल(&vlan_eth, skb_in->data, माप(काष्ठा vlan_ethhdr));
		अगर (ntohs(vlan_eth.h_vlan_encapsulated_proto) != ETH_P_IPV6)
			वापस -EPROTONOSUPPORT;
		mac_header_data = &vlan_eth;
		mac_header_len = VLAN_ETH_HLEN;
	पूर्ण अन्यथा अणु
		स_नकल(&eth, skb_in->data, माप(काष्ठा ethhdr));
		अगर (ntohs(eth.h_proto) != ETH_P_IPV6)
			वापस -EPROTONOSUPPORT;
		mac_header_data = &eth;
		mac_header_len = ETH_HLEN;
	पूर्ण

	/* Check अगर this is IPv6 ICMP packet */
	ipv6_in = (काष्ठा ipv6hdr *)(skb_in->data + mac_header_len);
	अगर (ipv6_in->version != 6 || ipv6_in->nexthdr != IPPROTO_ICMPV6)
		वापस -EPROTONOSUPPORT;

	/* Check अगर this is NDP packet */
	icmp6_in = (काष्ठा icmp6hdr *)(skb_in->data + mac_header_len +
					माप(काष्ठा ipv6hdr));
	अगर (icmp6_in->icmp6_type == NDISC_ROUTER_SOLICITATION) अणु /* Check RS */
		वापस -EPROTONOSUPPORT;
	पूर्ण अन्यथा अगर (icmp6_in->icmp6_type == NDISC_NEIGHBOUR_SOLICITATION) अणु
		/* Check NS */
		u8 icmp_na[माप(काष्ठा icmp6hdr) +
			माप(काष्ठा neighbour_advertisement)];
		u8 zero_addr8[16] = अणु0,पूर्ण;

		अगर (स_भेद(ipv6_in->saddr.in6_u.u6_addr8, zero_addr8, 16) == 0)
			/* Duplicate Address Detection: Source IP is all zero */
			वापस 0;

		icmp6_out.icmp6_type = NDISC_NEIGHBOUR_ADVERTISEMENT;
		icmp6_out.icmp6_code = 0;
		icmp6_out.icmp6_cksum = 0;
		/* R=0, S=1, O=1 */
		icmp6_out.icmp6_dataun.un_data32[0] = htonl(0x60000000);

		ns = (काष्ठा neighbour_solicitation *)
			(skb_in->data + mac_header_len +
			 माप(काष्ठा ipv6hdr) + माप(काष्ठा icmp6hdr));
		स_नकल(&na.target_address, ns->target_address, 16);
		na.type = 0x02;
		na.length = 1;
		na.link_layer_address[0] = 0x00;
		na.link_layer_address[1] = 0x0a;
		na.link_layer_address[2] = 0x3b;
		na.link_layer_address[3] = 0xaf;
		na.link_layer_address[4] = 0x63;
		na.link_layer_address[5] = 0xc7;

		स_नकल(&ipv6_out, ipv6_in, माप(काष्ठा ipv6hdr));
		स_नकल(ipv6_out.saddr.in6_u.u6_addr8, &na.target_address, 16);
		स_नकल(ipv6_out.daddr.in6_u.u6_addr8,
		       ipv6_in->saddr.in6_u.u6_addr8, 16);
		ipv6_out.payload_len = htons(माप(काष्ठा icmp6hdr) +
				माप(काष्ठा neighbour_advertisement));

		स_नकल(icmp_na, &icmp6_out, माप(काष्ठा icmp6hdr));
		स_नकल(icmp_na + माप(काष्ठा icmp6hdr), &na,
		       माप(काष्ठा neighbour_advertisement));

		icmp6_out.icmp6_cksum = icmp6_checksum(&ipv6_out,
						       (u16 *)icmp_na,
						       माप(icmp_na));
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	/* Fill the destination mac with source mac of the received packet */
	स_नकल(mac_header_data, mac_header_data + ETH_ALEN, ETH_ALEN);
	/* Fill the source mac with nic's source mac */
	स_नकल(mac_header_data + ETH_ALEN, nic->src_mac_addr, ETH_ALEN);

	/* Alloc skb and reserve align */
	skb_out = dev_alloc_skb(skb_in->len);
	अगर (!skb_out)
		वापस -ENOMEM;
	skb_reserve(skb_out, NET_IP_ALIGN);

	skb_put_data(skb_out, mac_header_data, mac_header_len);
	skb_put_data(skb_out, &ipv6_out, माप(काष्ठा ipv6hdr));
	skb_put_data(skb_out, &icmp6_out, माप(काष्ठा icmp6hdr));
	skb_put_data(skb_out, &na, माप(काष्ठा neighbour_advertisement));

	skb_out->protocol = ((काष्ठा ethhdr *)mac_header_data)->h_proto;
	skb_out->dev = skb_in->dev;
	skb_reset_mac_header(skb_out);
	skb_pull(skb_out, ETH_HLEN);

	gdm_lte_rx(skb_out, nic, nic_type);

	वापस 0;
पूर्ण

अटल s32 gdm_lte_tx_nic_type(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा nic *nic = netdev_priv(dev);
	काष्ठा ethhdr *eth;
	काष्ठा vlan_ethhdr *vlan_eth;
	काष्ठा iphdr *ip;
	काष्ठा ipv6hdr *ipv6;
	पूर्णांक mac_proto;
	व्योम *network_data;
	u32 nic_type;

	/* NIC TYPE is based on the nic_id of this net_device */
	nic_type = 0x00000010 | nic->nic_id;

	/* Get ethernet protocol */
	eth = (काष्ठा ethhdr *)skb->data;
	अगर (ntohs(eth->h_proto) == ETH_P_8021Q) अणु
		vlan_eth = (काष्ठा vlan_ethhdr *)skb->data;
		mac_proto = ntohs(vlan_eth->h_vlan_encapsulated_proto);
		network_data = skb->data + VLAN_ETH_HLEN;
		nic_type |= NIC_TYPE_F_VLAN;
	पूर्ण अन्यथा अणु
		mac_proto = ntohs(eth->h_proto);
		network_data = skb->data + ETH_HLEN;
	पूर्ण

	/* Process packet क्रम nic type */
	चयन (mac_proto) अणु
	हाल ETH_P_ARP:
		nic_type |= NIC_TYPE_ARP;
		अवरोध;
	हाल ETH_P_IP:
		nic_type |= NIC_TYPE_F_IPV4;
		ip = network_data;

		/* Check DHCPv4 */
		अगर (ip->protocol == IPPROTO_UDP) अणु
			काष्ठा udphdr *udp =
					network_data + माप(काष्ठा iphdr);
			अगर (ntohs(udp->dest) == 67 || ntohs(udp->dest) == 68)
				nic_type |= NIC_TYPE_F_DHCP;
		पूर्ण
		अवरोध;
	हाल ETH_P_IPV6:
		nic_type |= NIC_TYPE_F_IPV6;
		ipv6 = network_data;

		अगर (ipv6->nexthdr == IPPROTO_ICMPV6) /* Check NDP request */ अणु
			काष्ठा icmp6hdr *icmp6 =
					network_data + माप(काष्ठा ipv6hdr);
			अगर (icmp6->icmp6_type == NDISC_NEIGHBOUR_SOLICITATION)
				nic_type |= NIC_TYPE_ICMPV6;
		पूर्ण अन्यथा अगर (ipv6->nexthdr == IPPROTO_UDP) /* Check DHCPv6 */ अणु
			काष्ठा udphdr *udp =
					network_data + माप(काष्ठा ipv6hdr);
			अगर (ntohs(udp->dest) == 546 || ntohs(udp->dest) == 547)
				nic_type |= NIC_TYPE_F_DHCP;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस nic_type;
पूर्ण

अटल netdev_tx_t gdm_lte_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा nic *nic = netdev_priv(dev);
	u32 nic_type;
	व्योम *data_buf;
	पूर्णांक data_len;
	पूर्णांक idx;
	पूर्णांक ret = 0;

	nic_type = gdm_lte_tx_nic_type(dev, skb);
	अगर (nic_type == 0) अणु
		netdev_err(dev, "tx - invalid nic_type\n");
		वापस -EMEDIUMTYPE;
	पूर्ण

	अगर (nic_type & NIC_TYPE_ARP) अणु
		अगर (gdm_lte_emulate_arp(skb, nic_type) == 0) अणु
			dev_kमुक्त_skb(skb);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (nic_type & NIC_TYPE_ICMPV6) अणु
		अगर (gdm_lte_emulate_ndp(skb, nic_type) == 0) अणु
			dev_kमुक्त_skb(skb);
			वापस 0;
		पूर्ण
	पूर्ण

	/*
	 * Need byte shअगरt (that is, हटाओ VLAN tag) अगर there is one
	 * For the हाल of ARP, this अवरोधs the offset as vlan_ethhdr+4
	 * is treated as ethhdr	However, it shouldn't be a problem as
	 * the response starts from arp_hdr and ethhdr is created by this
	 * driver based on the NIC mac
	 */
	अगर (nic_type & NIC_TYPE_F_VLAN) अणु
		काष्ठा vlan_ethhdr *vlan_eth = (काष्ठा vlan_ethhdr *)skb->data;

		nic->vlan_id = ntohs(vlan_eth->h_vlan_TCI) & VLAN_VID_MASK;
		data_buf = skb->data + (VLAN_ETH_HLEN - ETH_HLEN);
		data_len = skb->len - (VLAN_ETH_HLEN - ETH_HLEN);
	पूर्ण अन्यथा अणु
		nic->vlan_id = 0;
		data_buf = skb->data;
		data_len = skb->len;
	पूर्ण

	/* If it is a ICMPV6 packet, clear all the other bits :
	 * क्रम backward compatibility with the firmware
	 */
	अगर (nic_type & NIC_TYPE_ICMPV6)
		nic_type = NIC_TYPE_ICMPV6;

	/* If it is not a dhcp packet, clear all the flag bits :
	 * original NIC, otherwise the special flag (IPVX | DHCP)
	 */
	अगर (!(nic_type & NIC_TYPE_F_DHCP))
		nic_type &= NIC_TYPE_MASK;

	ret = माला_पूछो(dev->name, "lte%d", &idx);
	अगर (ret != 1) अणु
		dev_kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	ret = nic->phy_dev->send_sdu_func(nic->phy_dev->priv_dev,
					  data_buf, data_len,
					  nic->pdn_table.dft_eps_id, 0,
					  tx_complete, nic, idx,
					  nic_type);

	अगर (ret == TX_NO_BUFFER || ret == TX_NO_SPC) अणु
		netअगर_stop_queue(dev);
		अगर (ret == TX_NO_BUFFER)
			ret = 0;
		अन्यथा
			ret = -ENOSPC;
	पूर्ण अन्यथा अगर (ret == TX_NO_DEV) अणु
		ret = -ENODEV;
	पूर्ण

	/* Updates tx stats */
	अगर (ret) अणु
		nic->stats.tx_dropped++;
	पूर्ण अन्यथा अणु
		nic->stats.tx_packets++;
		nic->stats.tx_bytes += data_len;
	पूर्ण
	dev_kमुक्त_skb(skb);

	वापस 0;
पूर्ण

अटल काष्ठा net_device_stats *gdm_lte_stats(काष्ठा net_device *dev)
अणु
	काष्ठा nic *nic = netdev_priv(dev);

	वापस &nic->stats;
पूर्ण

अटल पूर्णांक gdm_lte_event_send(काष्ठा net_device *dev, अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा phy_dev *phy_dev = ((काष्ठा nic *)netdev_priv(dev))->phy_dev;
	काष्ठा hci_packet *hci = (काष्ठा hci_packet *)buf;
	पूर्णांक length;
	पूर्णांक idx;
	पूर्णांक ret;

	ret = माला_पूछो(dev->name, "lte%d", &idx);
	अगर (ret != 1)
		वापस -EINVAL;

	length = gdm_dev16_to_cpu(phy_dev->get_endian(phy_dev->priv_dev),
				  hci->len) + HCI_HEADER_SIZE;
	वापस netlink_send(lte_event.sock, idx, 0, buf, length, dev);
पूर्ण

अटल व्योम gdm_lte_event_rcv(काष्ठा net_device *dev, u16 type,
			      व्योम *msg, पूर्णांक len)
अणु
	काष्ठा nic *nic = netdev_priv(dev);

	nic->phy_dev->send_hci_func(nic->phy_dev->priv_dev, msg, len, शून्य,
				    शून्य);
पूर्ण

पूर्णांक gdm_lte_event_init(व्योम)
अणु
	अगर (lte_event.ref_cnt == 0)
		lte_event.sock = netlink_init(NETLINK_LTE, gdm_lte_event_rcv);

	अगर (lte_event.sock) अणु
		lte_event.ref_cnt++;
		वापस 0;
	पूर्ण

	pr_err("event init failed\n");
	वापस -ENODATA;
पूर्ण

व्योम gdm_lte_event_निकास(व्योम)
अणु
	अगर (lte_event.sock && --lte_event.ref_cnt == 0) अणु
		sock_release(lte_event.sock->sk_socket);
		lte_event.sock = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक find_dev_index(u32 nic_type)
अणु
	u8 index;

	index = (u8)(nic_type & 0x0000000f);
	अगर (index >= MAX_NIC_TYPE)
		वापस -EINVAL;

	वापस index;
पूर्ण

अटल व्योम gdm_lte_netअगर_rx(काष्ठा net_device *dev, अक्षर *buf,
			     पूर्णांक len, पूर्णांक flagged_nic_type)
अणु
	u32 nic_type;
	काष्ठा nic *nic;
	काष्ठा sk_buff *skb;
	काष्ठा ethhdr eth;
	काष्ठा vlan_ethhdr vlan_eth;
	व्योम *mac_header_data;
	u32 mac_header_len;
	अक्षर ip_version = 0;

	nic_type = flagged_nic_type & NIC_TYPE_MASK;
	nic = netdev_priv(dev);

	अगर (flagged_nic_type & NIC_TYPE_F_DHCP) अणु
		/* Change the destination mac address
		 * with the one requested the IP
		 */
		अगर (flagged_nic_type & NIC_TYPE_F_IPV4) अणु
			काष्ठा dhcp_packet अणु
				u8 op;      /* BOOTREQUEST or BOOTREPLY */
				u8 htype;   /* hardware address type.
					     * 1 = 10mb ethernet
					     */
				u8 hlen;    /* hardware address length */
				u8 hops;    /* used by relay agents only */
				u32 xid;    /* unique id */
				u16 secs;   /* elapsed since client began
					     * acquisition/renewal
					     */
				u16 flags;  /* only one flag so far: */
				#घोषणा BROADCAST_FLAG 0x8000
				/* "I need broadcast replies" */
				u32 ciaddr; /* client IP (अगर client is in
					     * BOUND, RENEW or REBINDING state)
					     */
				u32 yiaddr; /* 'your' (client) IP address */
				/* IP address of next server to use in
				 * bootstrap, वापसed in DHCPOFFER,
				 * DHCPACK by server
				 */
				u32 siaddr_nip;
				u32 gateway_nip; /* relay agent IP address */
				u8 chaddr[16];   /* link-layer client hardware
						  * address (MAC)
						  */
				u8 sname[64];    /* server host name (ASCIZ) */
				u8 file[128];    /* boot file name (ASCIZ) */
				u32 cookie;      /* fixed first four option
						  * bytes (99,130,83,99 dec)
						  */
			पूर्ण __packed;
			व्योम *addr = buf + माप(काष्ठा iphdr) +
				माप(काष्ठा udphdr) +
				दुरत्व(काष्ठा dhcp_packet, chaddr);
			ether_addr_copy(nic->dest_mac_addr, addr);
		पूर्ण
	पूर्ण

	अगर (nic->vlan_id > 0) अणु
		mac_header_data = (व्योम *)&vlan_eth;
		mac_header_len = VLAN_ETH_HLEN;
	पूर्ण अन्यथा अणु
		mac_header_data = (व्योम *)&eth;
		mac_header_len = ETH_HLEN;
	पूर्ण

	/* Format the data so that it can be put to skb */
	ether_addr_copy(mac_header_data, nic->dest_mac_addr);
	स_नकल(mac_header_data + ETH_ALEN, nic->src_mac_addr, ETH_ALEN);

	vlan_eth.h_vlan_TCI = htons(nic->vlan_id);
	vlan_eth.h_vlan_proto = htons(ETH_P_8021Q);

	अगर (nic_type == NIC_TYPE_ARP) अणु
		/* Should be response: Only happens because
		 * there was a request from the host
		 */
		eth.h_proto = htons(ETH_P_ARP);
		vlan_eth.h_vlan_encapsulated_proto = htons(ETH_P_ARP);
	पूर्ण अन्यथा अणु
		ip_version = buf[0] >> 4;
		अगर (ip_version == IP_VERSION_4) अणु
			eth.h_proto = htons(ETH_P_IP);
			vlan_eth.h_vlan_encapsulated_proto = htons(ETH_P_IP);
		पूर्ण अन्यथा अगर (ip_version == IP_VERSION_6) अणु
			eth.h_proto = htons(ETH_P_IPV6);
			vlan_eth.h_vlan_encapsulated_proto = htons(ETH_P_IPV6);
		पूर्ण अन्यथा अणु
			netdev_err(dev, "Unknown IP version %d\n", ip_version);
			वापस;
		पूर्ण
	पूर्ण

	/* Alloc skb and reserve align */
	skb = dev_alloc_skb(len + mac_header_len + NET_IP_ALIGN);
	अगर (!skb)
		वापस;
	skb_reserve(skb, NET_IP_ALIGN);

	skb_put_data(skb, mac_header_data, mac_header_len);
	skb_put_data(skb, buf, len);

	skb->protocol = ((काष्ठा ethhdr *)mac_header_data)->h_proto;
	skb->dev = dev;
	skb_reset_mac_header(skb);
	skb_pull(skb, ETH_HLEN);

	gdm_lte_rx(skb, nic, nic_type);
पूर्ण

अटल व्योम gdm_lte_multi_sdu_pkt(काष्ठा phy_dev *phy_dev, अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा net_device *dev;
	काष्ठा multi_sdu *multi_sdu = (काष्ठा multi_sdu *)buf;
	काष्ठा sdu *sdu = शून्य;
	u8 endian = phy_dev->get_endian(phy_dev->priv_dev);
	u8 *data = (u8 *)multi_sdu->data;
	u16 i = 0;
	u16 num_packet;
	u16 hci_len;
	u16 cmd_evt;
	u32 nic_type;
	पूर्णांक index;

	hci_len = gdm_dev16_to_cpu(endian, multi_sdu->len);
	num_packet = gdm_dev16_to_cpu(endian, multi_sdu->num_packet);

	क्रम (i = 0; i < num_packet; i++) अणु
		sdu = (काष्ठा sdu *)data;

		cmd_evt  = gdm_dev16_to_cpu(endian, sdu->cmd_evt);
		hci_len  = gdm_dev16_to_cpu(endian, sdu->len);
		nic_type = gdm_dev32_to_cpu(endian, sdu->nic_type);

		अगर (cmd_evt != LTE_RX_SDU) अणु
			pr_err("rx sdu wrong hci %04x\n", cmd_evt);
			वापस;
		पूर्ण
		अगर (hci_len < 12) अणु
			pr_err("rx sdu invalid len %d\n", hci_len);
			वापस;
		पूर्ण

		index = find_dev_index(nic_type);
		अगर (index < 0) अणु
			pr_err("rx sdu invalid nic_type :%x\n", nic_type);
			वापस;
		पूर्ण
		dev = phy_dev->dev[index];
		gdm_lte_netअगर_rx(dev, (अक्षर *)sdu->data,
				 (पूर्णांक)(hci_len - 12), nic_type);

		data += ((hci_len + 3) & 0xfffc) + HCI_HEADER_SIZE;
	पूर्ण
पूर्ण

अटल व्योम gdm_lte_pdn_table(काष्ठा net_device *dev, अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा nic *nic = netdev_priv(dev);
	काष्ठा hci_pdn_table_ind *pdn_table = (काष्ठा hci_pdn_table_ind *)buf;
	u8 ed = nic->phy_dev->get_endian(nic->phy_dev->priv_dev);

	अगर (!pdn_table->activate) अणु
		स_रखो(&nic->pdn_table, 0x00, माप(काष्ठा pdn_table));
		netdev_info(dev, "pdn deactivated\n");

		वापस;
	पूर्ण

	nic->pdn_table.activate = pdn_table->activate;
	nic->pdn_table.dft_eps_id = gdm_dev32_to_cpu(ed, pdn_table->dft_eps_id);
	nic->pdn_table.nic_type = gdm_dev32_to_cpu(ed, pdn_table->nic_type);

	netdev_info(dev, "pdn activated, nic_type=0x%x\n",
		    nic->pdn_table.nic_type);
पूर्ण

अटल पूर्णांक gdm_lte_receive_pkt(काष्ठा phy_dev *phy_dev, अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा hci_packet *hci = (काष्ठा hci_packet *)buf;
	काष्ठा hci_pdn_table_ind *pdn_table = (काष्ठा hci_pdn_table_ind *)buf;
	काष्ठा sdu *sdu;
	काष्ठा net_device *dev;
	u8 endian = phy_dev->get_endian(phy_dev->priv_dev);
	पूर्णांक ret = 0;
	u16 cmd_evt;
	u32 nic_type;
	पूर्णांक index;

	अगर (!len)
		वापस ret;

	cmd_evt = gdm_dev16_to_cpu(endian, hci->cmd_evt);

	dev = phy_dev->dev[0];
	अगर (!dev)
		वापस 0;

	चयन (cmd_evt) अणु
	हाल LTE_RX_SDU:
		sdu = (काष्ठा sdu *)hci->data;
		nic_type = gdm_dev32_to_cpu(endian, sdu->nic_type);
		index = find_dev_index(nic_type);
		अगर (index < 0)
			वापस index;
		dev = phy_dev->dev[index];
		gdm_lte_netअगर_rx(dev, hci->data, len, nic_type);
		अवरोध;
	हाल LTE_RX_MULTI_SDU:
		gdm_lte_multi_sdu_pkt(phy_dev, buf, len);
		अवरोध;
	हाल LTE_LINK_ON_OFF_INDICATION:
		netdev_info(dev, "link %s\n",
			    ((काष्ठा hci_connect_ind *)buf)->connect
			    ? "on" : "off");
		अवरोध;
	हाल LTE_PDN_TABLE_IND:
		pdn_table = (काष्ठा hci_pdn_table_ind *)buf;
		nic_type = gdm_dev32_to_cpu(endian, pdn_table->nic_type);
		index = find_dev_index(nic_type);
		अगर (index < 0)
			वापस index;
		dev = phy_dev->dev[index];
		gdm_lte_pdn_table(dev, buf, len);
		fallthrough;
	शेष:
		ret = gdm_lte_event_send(dev, buf, len);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rx_complete(व्योम *arg, व्योम *data, पूर्णांक len, पूर्णांक context)
अणु
	काष्ठा phy_dev *phy_dev = arg;

	वापस gdm_lte_receive_pkt(phy_dev, data, len);
पूर्ण

व्योम start_rx_proc(काष्ठा phy_dev *phy_dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_RX_SUBMIT_COUNT; i++)
		phy_dev->rcv_func(phy_dev->priv_dev,
				rx_complete, phy_dev, USB_COMPLETE);
पूर्ण

अटल स्थिर काष्ठा net_device_ops gdm_netdev_ops = अणु
	.nकरो_खोलो			= gdm_lte_खोलो,
	.nकरो_stop			= gdm_lte_बंद,
	.nकरो_set_config			= gdm_lte_set_config,
	.nकरो_start_xmit			= gdm_lte_tx,
	.nकरो_get_stats			= gdm_lte_stats,
पूर्ण;

अटल u8 gdm_lte_macaddr[ETH_ALEN] = अणु0x00, 0x0a, 0x3b, 0x00, 0x00, 0x00पूर्ण;

अटल व्योम क्रमm_mac_address(u8 *dev_addr, u8 *nic_src, u8 *nic_dest,
			     u8 *mac_address, u8 index)
अणु
	/* Form the dev_addr */
	अगर (!mac_address)
		ether_addr_copy(dev_addr, gdm_lte_macaddr);
	अन्यथा
		ether_addr_copy(dev_addr, mac_address);

	/* The last byte of the mac address
	 * should be less than or equal to 0xFC
	 */
	dev_addr[ETH_ALEN - 1] += index;

	/* Create अक्रमom nic src and copy the first
	 * 3 bytes to be the same as dev_addr
	 */
	eth_अक्रमom_addr(nic_src);
	स_नकल(nic_src, dev_addr, 3);

	/* Copy the nic_dest from dev_addr*/
	ether_addr_copy(nic_dest, dev_addr);
पूर्ण

अटल व्योम validate_mac_address(u8 *mac_address)
अणु
	/* अगर zero address or multicast bit set, restore the शेष value */
	अगर (is_zero_ether_addr(mac_address) || (mac_address[0] & 0x01)) अणु
		pr_err("MAC invalid, restoring default\n");
		स_नकल(mac_address, gdm_lte_macaddr, 6);
	पूर्ण
पूर्ण

पूर्णांक रेजिस्टर_lte_device(काष्ठा phy_dev *phy_dev,
			काष्ठा device *dev, u8 *mac_address)
अणु
	काष्ठा nic *nic;
	काष्ठा net_device *net;
	अक्षर pdn_dev_name[16];
	पूर्णांक ret = 0;
	u8 index;

	validate_mac_address(mac_address);

	क्रम (index = 0; index < MAX_NIC_TYPE; index++) अणु
		/* Create device name lteXpdnX */
		प्र_लिखो(pdn_dev_name, "lte%%dpdn%d", index);

		/* Allocate netdev */
		net = alloc_netdev(माप(काष्ठा nic), pdn_dev_name,
				   NET_NAME_UNKNOWN, ether_setup);
		अगर (!net) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
		net->netdev_ops = &gdm_netdev_ops;
		net->flags &= ~IFF_MULTICAST;
		net->mtu = DEFAULT_MTU_SIZE;

		nic = netdev_priv(net);
		स_रखो(nic, 0, माप(काष्ठा nic));
		nic->netdev = net;
		nic->phy_dev = phy_dev;
		nic->nic_id = index;

		क्रमm_mac_address(net->dev_addr,
				 nic->src_mac_addr,
				 nic->dest_mac_addr,
				 mac_address,
				 index);

		SET_NETDEV_DEV(net, dev);
		SET_NETDEV_DEVTYPE(net, &wwan_type);

		ret = रेजिस्टर_netdev(net);
		अगर (ret)
			जाओ err;

		netअगर_carrier_on(net);

		phy_dev->dev[index] = net;
	पूर्ण

	वापस 0;

err:
	unरेजिस्टर_lte_device(phy_dev);

	वापस ret;
पूर्ण

व्योम unरेजिस्टर_lte_device(काष्ठा phy_dev *phy_dev)
अणु
	काष्ठा net_device *net;
	पूर्णांक index;

	क्रम (index = 0; index < MAX_NIC_TYPE; index++) अणु
		net = phy_dev->dev[index];
		अगर (!net)
			जारी;

		unरेजिस्टर_netdev(net);
		मुक्त_netdev(net);
	पूर्ण
पूर्ण
