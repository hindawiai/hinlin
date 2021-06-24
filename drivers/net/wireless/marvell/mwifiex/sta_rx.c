<शैली गुरु>
/*
 * NXP Wireless LAN device driver: station RX data handling
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#समावेश <uapi/linux/ipv6.h>
#समावेश <net/ndisc.h>
#समावेश "decl.h"
#समावेश "ioctl.h"
#समावेश "util.h"
#समावेश "fw.h"
#समावेश "main.h"
#समावेश "11n_aggr.h"
#समावेश "11n_rxreorder.h"

/* This function checks अगर a frame is IPv4 ARP or IPv6 Neighbour advertisement
 * frame. If frame has both source and destination mac address as same, this
 * function drops such gratuitous frames.
 */
अटल bool
mwअगरiex_discard_gratuitous_arp(काष्ठा mwअगरiex_निजी *priv,
			       काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा mwअगरiex_arp_eth_header *arp;
	काष्ठा ethhdr *eth;
	काष्ठा ipv6hdr *ipv6;
	काष्ठा icmp6hdr *icmpv6;

	eth = (काष्ठा ethhdr *)skb->data;
	चयन (ntohs(eth->h_proto)) अणु
	हाल ETH_P_ARP:
		arp = (व्योम *)(skb->data + माप(काष्ठा ethhdr));
		अगर (arp->hdr.ar_op == htons(ARPOP_REPLY) ||
		    arp->hdr.ar_op == htons(ARPOP_REQUEST)) अणु
			अगर (!स_भेद(arp->ar_sip, arp->ar_tip, 4))
				वापस true;
		पूर्ण
		अवरोध;
	हाल ETH_P_IPV6:
		ipv6 = (व्योम *)(skb->data + माप(काष्ठा ethhdr));
		icmpv6 = (व्योम *)(skb->data + माप(काष्ठा ethhdr) +
				  माप(काष्ठा ipv6hdr));
		अगर (NDISC_NEIGHBOUR_ADVERTISEMENT == icmpv6->icmp6_type) अणु
			अगर (!स_भेद(&ipv6->saddr, &ipv6->daddr,
				    माप(काष्ठा in6_addr)))
				वापस true;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

/*
 * This function processes the received packet and क्रमwards it
 * to kernel/upper layer.
 *
 * This function parses through the received packet and determines
 * अगर it is a debug packet or normal packet.
 *
 * For non-debug packets, the function chops off unnecessary leading
 * header bytes, reस्थिरructs the packet as an ethernet frame or
 * 802.2/llc/snap frame as required, and sends it to kernel/upper layer.
 *
 * The completion callback is called after processing in complete.
 */
पूर्णांक mwअगरiex_process_rx_packet(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;
	काष्ठा rx_packet_hdr *rx_pkt_hdr;
	काष्ठा rxpd *local_rx_pd;
	पूर्णांक hdr_chop;
	काष्ठा ethhdr *eth;
	u16 rx_pkt_off, rx_pkt_len;
	u8 *offset;
	u8 adj_rx_rate = 0;

	local_rx_pd = (काष्ठा rxpd *) (skb->data);

	rx_pkt_off = le16_to_cpu(local_rx_pd->rx_pkt_offset);
	rx_pkt_len = le16_to_cpu(local_rx_pd->rx_pkt_length);
	rx_pkt_hdr = (व्योम *)local_rx_pd + rx_pkt_off;

	अगर ((!स_भेद(&rx_pkt_hdr->rfc1042_hdr, bridge_tunnel_header,
		     माप(bridge_tunnel_header))) ||
	    (!स_भेद(&rx_pkt_hdr->rfc1042_hdr, rfc1042_header,
		     माप(rfc1042_header)) &&
	     ntohs(rx_pkt_hdr->rfc1042_hdr.snap_type) != ETH_P_AARP &&
	     ntohs(rx_pkt_hdr->rfc1042_hdr.snap_type) != ETH_P_IPX)) अणु
		/*
		 *  Replace the 803 header and rfc1042 header (llc/snap) with an
		 *    EthernetII header, keep the src/dst and snap_type
		 *    (ethertype).
		 *  The firmware only passes up SNAP frames converting
		 *    all RX Data from 802.11 to 802.2/LLC/SNAP frames.
		 *  To create the Ethernet II, just move the src, dst address
		 *    right beक्रमe the snap_type.
		 */
		eth = (काष्ठा ethhdr *)
			((u8 *) &rx_pkt_hdr->eth803_hdr
			 + माप(rx_pkt_hdr->eth803_hdr) +
			 माप(rx_pkt_hdr->rfc1042_hdr)
			 - माप(rx_pkt_hdr->eth803_hdr.h_dest)
			 - माप(rx_pkt_hdr->eth803_hdr.h_source)
			 - माप(rx_pkt_hdr->rfc1042_hdr.snap_type));

		स_नकल(eth->h_source, rx_pkt_hdr->eth803_hdr.h_source,
		       माप(eth->h_source));
		स_नकल(eth->h_dest, rx_pkt_hdr->eth803_hdr.h_dest,
		       माप(eth->h_dest));

		/* Chop off the rxpd + the excess memory from the 802.2/llc/snap
		   header that was हटाओd. */
		hdr_chop = (u8 *) eth - (u8 *) local_rx_pd;
	पूर्ण अन्यथा अणु
		/* Chop off the rxpd */
		hdr_chop = (u8 *) &rx_pkt_hdr->eth803_hdr -
			(u8 *) local_rx_pd;
	पूर्ण

	/* Chop off the leading header bytes so the it poपूर्णांकs to the start of
	   either the reस्थिरructed EthII frame or the 802.2/llc/snap frame */
	skb_pull(skb, hdr_chop);

	अगर (priv->hs2_enabled &&
	    mwअगरiex_discard_gratuitous_arp(priv, skb)) अणु
		mwअगरiex_dbg(priv->adapter, INFO, "Bypassed Gratuitous ARP\n");
		dev_kमुक्त_skb_any(skb);
		वापस 0;
	पूर्ण

	अगर (ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info) &&
	    ntohs(rx_pkt_hdr->eth803_hdr.h_proto) == ETH_P_TDLS) अणु
		offset = (u8 *)local_rx_pd + rx_pkt_off;
		mwअगरiex_process_tdls_action_frame(priv, offset, rx_pkt_len);
	पूर्ण

	/* Only stash RX bitrate क्रम unicast packets. */
	अगर (likely(!is_multicast_ether_addr(rx_pkt_hdr->eth803_hdr.h_dest))) अणु
		priv->rxpd_rate = local_rx_pd->rx_rate;
		priv->rxpd_htinfo = local_rx_pd->ht_info;
	पूर्ण

	अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA ||
	    GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_UAP) अणु
		adj_rx_rate = mwअगरiex_adjust_data_rate(priv,
						       local_rx_pd->rx_rate,
						       local_rx_pd->ht_info);
		mwअगरiex_hist_data_add(priv, adj_rx_rate, local_rx_pd->snr,
				      local_rx_pd->nf);
	पूर्ण

	ret = mwअगरiex_recv_packet(priv, skb);
	अगर (ret == -1)
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "recv packet failed\n");

	वापस ret;
पूर्ण

/*
 * This function processes the received buffer.
 *
 * The function looks पूर्णांकo the RxPD and perक्रमms sanity tests on the
 * received buffer to ensure its a valid packet, beक्रमe processing it
 * further. If the packet is determined to be aggregated, it is
 * de-aggregated accordingly. Non-unicast packets are sent directly to
 * the kernel/upper layers. Unicast packets are handed over to the
 * Rx reordering routine अगर 11n is enabled.
 *
 * The completion callback is called after processing in complete.
 */
पूर्णांक mwअगरiex_process_sta_rx_packet(काष्ठा mwअगरiex_निजी *priv,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	पूर्णांक ret = 0;
	काष्ठा rxpd *local_rx_pd;
	काष्ठा rx_packet_hdr *rx_pkt_hdr;
	u8 ta[ETH_ALEN];
	u16 rx_pkt_type, rx_pkt_offset, rx_pkt_length, seq_num;
	काष्ठा mwअगरiex_sta_node *sta_ptr;

	local_rx_pd = (काष्ठा rxpd *) (skb->data);
	rx_pkt_type = le16_to_cpu(local_rx_pd->rx_pkt_type);
	rx_pkt_offset = le16_to_cpu(local_rx_pd->rx_pkt_offset);
	rx_pkt_length = le16_to_cpu(local_rx_pd->rx_pkt_length);
	seq_num = le16_to_cpu(local_rx_pd->seq_num);

	rx_pkt_hdr = (व्योम *)local_rx_pd + rx_pkt_offset;

	अगर ((rx_pkt_offset + rx_pkt_length) > (u16) skb->len) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "wrong rx packet: len=%d, rx_pkt_offset=%d, rx_pkt_length=%d\n",
			    skb->len, rx_pkt_offset, rx_pkt_length);
		priv->stats.rx_dropped++;
		dev_kमुक्त_skb_any(skb);
		वापस ret;
	पूर्ण

	अगर (rx_pkt_type == PKT_TYPE_MGMT) अणु
		ret = mwअगरiex_process_mgmt_packet(priv, skb);
		अगर (ret)
			mwअगरiex_dbg(adapter, DATA, "Rx of mgmt packet failed");
		dev_kमुक्त_skb_any(skb);
		वापस ret;
	पूर्ण

	/*
	 * If the packet is not an unicast packet then send the packet
	 * directly to os. Don't pass thru rx reordering
	 */
	अगर ((!IS_11N_ENABLED(priv) &&
	     !(ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info) &&
	       !(local_rx_pd->flags & MWIFIEX_RXPD_FLAGS_TDLS_PACKET))) ||
	    !ether_addr_equal_unaligned(priv->curr_addr, rx_pkt_hdr->eth803_hdr.h_dest)) अणु
		mwअगरiex_process_rx_packet(priv, skb);
		वापस ret;
	पूर्ण

	अगर (mwअगरiex_queuing_ra_based(priv) ||
	    (ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info) &&
	     local_rx_pd->flags & MWIFIEX_RXPD_FLAGS_TDLS_PACKET)) अणु
		स_नकल(ta, rx_pkt_hdr->eth803_hdr.h_source, ETH_ALEN);
		अगर (local_rx_pd->flags & MWIFIEX_RXPD_FLAGS_TDLS_PACKET &&
		    local_rx_pd->priority < MAX_NUM_TID) अणु
			sta_ptr = mwअगरiex_get_sta_entry(priv, ta);
			अगर (sta_ptr)
				sta_ptr->rx_seq[local_rx_pd->priority] =
					      le16_to_cpu(local_rx_pd->seq_num);
			mwअगरiex_स्वतः_tdls_update_peer_संकेत(priv, ta,
							     local_rx_pd->snr,
							     local_rx_pd->nf);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (rx_pkt_type != PKT_TYPE_BAR &&
		    local_rx_pd->priority < MAX_NUM_TID)
			priv->rx_seq[local_rx_pd->priority] = seq_num;
		स_नकल(ta, priv->curr_bss_params.bss_descriptor.mac_address,
		       ETH_ALEN);
	पूर्ण

	/* Reorder and send to OS */
	ret = mwअगरiex_11n_rx_reorder_pkt(priv, seq_num, local_rx_pd->priority,
					 ta, (u8) rx_pkt_type, skb);

	अगर (ret || (rx_pkt_type == PKT_TYPE_BAR))
		dev_kमुक्त_skb_any(skb);

	अगर (ret)
		priv->stats.rx_dropped++;

	वापस ret;
पूर्ण
