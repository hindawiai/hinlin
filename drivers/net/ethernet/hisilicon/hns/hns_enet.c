<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2014-2015 Hisilicon Limited.
 */

#समावेश <linux/clk.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/skbuff.h>

#समावेश "hnae.h"
#समावेश "hns_enet.h"
#समावेश "hns_dsaf_mac.h"

#घोषणा NIC_MAX_Q_PER_VF 16
#घोषणा HNS_NIC_TX_TIMEOUT (5 * HZ)

#घोषणा SERVICE_TIMER_HZ (1 * HZ)

#घोषणा RCB_IRQ_NOT_INITED 0
#घोषणा RCB_IRQ_INITED 1
#घोषणा HNS_BUFFER_SIZE_2048 2048

#घोषणा BD_MAX_SEND_SIZE 8191
#घोषणा SKB_TMP_LEN(SKB) \
	(((SKB)->transport_header - (SKB)->mac_header) + tcp_hdrlen(SKB))

अटल व्योम fill_v2_desc_hw(काष्ठा hnae_ring *ring, व्योम *priv, पूर्णांक size,
			    पूर्णांक send_sz, dma_addr_t dma, पूर्णांक frag_end,
			    पूर्णांक buf_num, क्रमागत hns_desc_type type, पूर्णांक mtu)
अणु
	काष्ठा hnae_desc *desc = &ring->desc[ring->next_to_use];
	काष्ठा hnae_desc_cb *desc_cb = &ring->desc_cb[ring->next_to_use];
	काष्ठा iphdr *iphdr;
	काष्ठा ipv6hdr *ipv6hdr;
	काष्ठा sk_buff *skb;
	__be16 protocol;
	u8 bn_pid = 0;
	u8 rrcfv = 0;
	u8 ip_offset = 0;
	u8 tvsvsn = 0;
	u16 mss = 0;
	u8 l4_len = 0;
	u16 paylen = 0;

	desc_cb->priv = priv;
	desc_cb->length = size;
	desc_cb->dma = dma;
	desc_cb->type = type;

	desc->addr = cpu_to_le64(dma);
	desc->tx.send_size = cpu_to_le16((u16)send_sz);

	/* config bd buffer end */
	hnae_set_bit(rrcfv, HNSV2_TXD_VLD_B, 1);
	hnae_set_field(bn_pid, HNSV2_TXD_BUFNUM_M, 0, buf_num - 1);

	/* fill port_id in the tx bd क्रम sending management pkts */
	hnae_set_field(bn_pid, HNSV2_TXD_PORTID_M,
		       HNSV2_TXD_PORTID_S, ring->q->handle->dport_id);

	अगर (type == DESC_TYPE_SKB) अणु
		skb = (काष्ठा sk_buff *)priv;

		अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
			skb_reset_mac_len(skb);
			protocol = skb->protocol;
			ip_offset = ETH_HLEN;

			अगर (protocol == htons(ETH_P_8021Q)) अणु
				ip_offset += VLAN_HLEN;
				protocol = vlan_get_protocol(skb);
				skb->protocol = protocol;
			पूर्ण

			अगर (skb->protocol == htons(ETH_P_IP)) अणु
				iphdr = ip_hdr(skb);
				hnae_set_bit(rrcfv, HNSV2_TXD_L3CS_B, 1);
				hnae_set_bit(rrcfv, HNSV2_TXD_L4CS_B, 1);

				/* check क्रम tcp/udp header */
				अगर (iphdr->protocol == IPPROTO_TCP &&
				    skb_is_gso(skb)) अणु
					hnae_set_bit(tvsvsn,
						     HNSV2_TXD_TSE_B, 1);
					l4_len = tcp_hdrlen(skb);
					mss = skb_shinfo(skb)->gso_size;
					paylen = skb->len - SKB_TMP_LEN(skb);
				पूर्ण
			पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
				hnae_set_bit(tvsvsn, HNSV2_TXD_IPV6_B, 1);
				ipv6hdr = ipv6_hdr(skb);
				hnae_set_bit(rrcfv, HNSV2_TXD_L4CS_B, 1);

				/* check क्रम tcp/udp header */
				अगर (ipv6hdr->nexthdr == IPPROTO_TCP &&
				    skb_is_gso(skb) && skb_is_gso_v6(skb)) अणु
					hnae_set_bit(tvsvsn,
						     HNSV2_TXD_TSE_B, 1);
					l4_len = tcp_hdrlen(skb);
					mss = skb_shinfo(skb)->gso_size;
					paylen = skb->len - SKB_TMP_LEN(skb);
				पूर्ण
			पूर्ण
			desc->tx.ip_offset = ip_offset;
			desc->tx.tse_vlan_snap_v6_sctp_nth = tvsvsn;
			desc->tx.mss = cpu_to_le16(mss);
			desc->tx.l4_len = l4_len;
			desc->tx.paylen = cpu_to_le16(paylen);
		पूर्ण
	पूर्ण

	hnae_set_bit(rrcfv, HNSV2_TXD_FE_B, frag_end);

	desc->tx.bn_pid = bn_pid;
	desc->tx.ra_ri_cs_fe_vld = rrcfv;

	ring_ptr_move_fw(ring, next_to_use);
पूर्ण

अटल व्योम fill_v2_desc(काष्ठा hnae_ring *ring, व्योम *priv,
			 पूर्णांक size, dma_addr_t dma, पूर्णांक frag_end,
			 पूर्णांक buf_num, क्रमागत hns_desc_type type, पूर्णांक mtu)
अणु
	fill_v2_desc_hw(ring, priv, size, size, dma, frag_end,
			buf_num, type, mtu);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id hns_enet_acpi_match[] = अणु
	अणु "HISI00C1", 0 पूर्ण,
	अणु "HISI00C2", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, hns_enet_acpi_match);

अटल व्योम fill_desc(काष्ठा hnae_ring *ring, व्योम *priv,
		      पूर्णांक size, dma_addr_t dma, पूर्णांक frag_end,
		      पूर्णांक buf_num, क्रमागत hns_desc_type type, पूर्णांक mtu)
अणु
	काष्ठा hnae_desc *desc = &ring->desc[ring->next_to_use];
	काष्ठा hnae_desc_cb *desc_cb = &ring->desc_cb[ring->next_to_use];
	काष्ठा sk_buff *skb;
	__be16 protocol;
	u32 ip_offset;
	u32 asid_bufnum_pid = 0;
	u32 flag_ipoffset = 0;

	desc_cb->priv = priv;
	desc_cb->length = size;
	desc_cb->dma = dma;
	desc_cb->type = type;

	desc->addr = cpu_to_le64(dma);
	desc->tx.send_size = cpu_to_le16((u16)size);

	/*config bd buffer end */
	flag_ipoffset |= 1 << HNS_TXD_VLD_B;

	asid_bufnum_pid |= buf_num << HNS_TXD_BUFNUM_S;

	अगर (type == DESC_TYPE_SKB) अणु
		skb = (काष्ठा sk_buff *)priv;

		अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
			protocol = skb->protocol;
			ip_offset = ETH_HLEN;

			/*अगर it is a SW VLAN check the next protocol*/
			अगर (protocol == htons(ETH_P_8021Q)) अणु
				ip_offset += VLAN_HLEN;
				protocol = vlan_get_protocol(skb);
				skb->protocol = protocol;
			पूर्ण

			अगर (skb->protocol == htons(ETH_P_IP)) अणु
				flag_ipoffset |= 1 << HNS_TXD_L3CS_B;
				/* check क्रम tcp/udp header */
				flag_ipoffset |= 1 << HNS_TXD_L4CS_B;

			पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
				/* ipv6 has not l3 cs, check क्रम L4 header */
				flag_ipoffset |= 1 << HNS_TXD_L4CS_B;
			पूर्ण

			flag_ipoffset |= ip_offset << HNS_TXD_IPOFFSET_S;
		पूर्ण
	पूर्ण

	flag_ipoffset |= frag_end << HNS_TXD_FE_B;

	desc->tx.asid_bufnum_pid = cpu_to_le16(asid_bufnum_pid);
	desc->tx.flag_ipoffset = cpu_to_le32(flag_ipoffset);

	ring_ptr_move_fw(ring, next_to_use);
पूर्ण

अटल व्योम unfill_desc(काष्ठा hnae_ring *ring)
अणु
	ring_ptr_move_bw(ring, next_to_use);
पूर्ण

अटल पूर्णांक hns_nic_maybe_stop_tx(
	काष्ठा sk_buff **out_skb, पूर्णांक *bnum, काष्ठा hnae_ring *ring)
अणु
	काष्ठा sk_buff *skb = *out_skb;
	काष्ठा sk_buff *new_skb = शून्य;
	पूर्णांक buf_num;

	/* no. of segments (plus a header) */
	buf_num = skb_shinfo(skb)->nr_frags + 1;

	अगर (unlikely(buf_num > ring->max_desc_num_per_pkt)) अणु
		अगर (ring_space(ring) < 1)
			वापस -EBUSY;

		new_skb = skb_copy(skb, GFP_ATOMIC);
		अगर (!new_skb)
			वापस -ENOMEM;

		dev_kमुक्त_skb_any(skb);
		*out_skb = new_skb;
		buf_num = 1;
	पूर्ण अन्यथा अगर (buf_num > ring_space(ring)) अणु
		वापस -EBUSY;
	पूर्ण

	*bnum = buf_num;
	वापस 0;
पूर्ण

अटल पूर्णांक hns_nic_maybe_stop_tso(
	काष्ठा sk_buff **out_skb, पूर्णांक *bnum, काष्ठा hnae_ring *ring)
अणु
	पूर्णांक i;
	पूर्णांक size;
	पूर्णांक buf_num;
	पूर्णांक frag_num;
	काष्ठा sk_buff *skb = *out_skb;
	काष्ठा sk_buff *new_skb = शून्य;
	skb_frag_t *frag;

	size = skb_headlen(skb);
	buf_num = (size + BD_MAX_SEND_SIZE - 1) / BD_MAX_SEND_SIZE;

	frag_num = skb_shinfo(skb)->nr_frags;
	क्रम (i = 0; i < frag_num; i++) अणु
		frag = &skb_shinfo(skb)->frags[i];
		size = skb_frag_size(frag);
		buf_num += (size + BD_MAX_SEND_SIZE - 1) / BD_MAX_SEND_SIZE;
	पूर्ण

	अगर (unlikely(buf_num > ring->max_desc_num_per_pkt)) अणु
		buf_num = (skb->len + BD_MAX_SEND_SIZE - 1) / BD_MAX_SEND_SIZE;
		अगर (ring_space(ring) < buf_num)
			वापस -EBUSY;
		/* manual split the send packet */
		new_skb = skb_copy(skb, GFP_ATOMIC);
		अगर (!new_skb)
			वापस -ENOMEM;
		dev_kमुक्त_skb_any(skb);
		*out_skb = new_skb;

	पूर्ण अन्यथा अगर (ring_space(ring) < buf_num) अणु
		वापस -EBUSY;
	पूर्ण

	*bnum = buf_num;
	वापस 0;
पूर्ण

अटल व्योम fill_tso_desc(काष्ठा hnae_ring *ring, व्योम *priv,
			  पूर्णांक size, dma_addr_t dma, पूर्णांक frag_end,
			  पूर्णांक buf_num, क्रमागत hns_desc_type type, पूर्णांक mtu)
अणु
	पूर्णांक frag_buf_num;
	पूर्णांक मापlast;
	पूर्णांक k;

	frag_buf_num = (size + BD_MAX_SEND_SIZE - 1) / BD_MAX_SEND_SIZE;
	मापlast = size % BD_MAX_SEND_SIZE;
	मापlast = मापlast ? मापlast : BD_MAX_SEND_SIZE;

	/* when the frag size is bigger than hardware, split this frag */
	क्रम (k = 0; k < frag_buf_num; k++)
		fill_v2_desc_hw(ring, priv, k == 0 ? size : 0,
				(k == frag_buf_num - 1) ?
					मापlast : BD_MAX_SEND_SIZE,
				dma + BD_MAX_SEND_SIZE * k,
				frag_end && (k == frag_buf_num - 1) ? 1 : 0,
				buf_num,
				(type == DESC_TYPE_SKB && !k) ?
					DESC_TYPE_SKB : DESC_TYPE_PAGE,
				mtu);
पूर्ण

netdev_tx_t hns_nic_net_xmit_hw(काष्ठा net_device *ndev,
				काष्ठा sk_buff *skb,
				काष्ठा hns_nic_ring_data *ring_data)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hnae_ring *ring = ring_data->ring;
	काष्ठा device *dev = ring_to_dev(ring);
	काष्ठा netdev_queue *dev_queue;
	skb_frag_t *frag;
	पूर्णांक buf_num;
	पूर्णांक seg_num;
	dma_addr_t dma;
	पूर्णांक size, next_to_use;
	पूर्णांक i;

	चयन (priv->ops.maybe_stop_tx(&skb, &buf_num, ring)) अणु
	हाल -EBUSY:
		ring->stats.tx_busy++;
		जाओ out_net_tx_busy;
	हाल -ENOMEM:
		ring->stats.sw_err_cnt++;
		netdev_err(ndev, "no memory to xmit!\n");
		जाओ out_err_tx_ok;
	शेष:
		अवरोध;
	पूर्ण

	/* no. of segments (plus a header) */
	seg_num = skb_shinfo(skb)->nr_frags + 1;
	next_to_use = ring->next_to_use;

	/* fill the first part */
	size = skb_headlen(skb);
	dma = dma_map_single(dev, skb->data, size, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, dma)) अणु
		netdev_err(ndev, "TX head DMA map failed\n");
		ring->stats.sw_err_cnt++;
		जाओ out_err_tx_ok;
	पूर्ण
	priv->ops.fill_desc(ring, skb, size, dma, seg_num == 1 ? 1 : 0,
			    buf_num, DESC_TYPE_SKB, ndev->mtu);

	/* fill the fragments */
	क्रम (i = 1; i < seg_num; i++) अणु
		frag = &skb_shinfo(skb)->frags[i - 1];
		size = skb_frag_size(frag);
		dma = skb_frag_dma_map(dev, frag, 0, size, DMA_TO_DEVICE);
		अगर (dma_mapping_error(dev, dma)) अणु
			netdev_err(ndev, "TX frag(%d) DMA map failed\n", i);
			ring->stats.sw_err_cnt++;
			जाओ out_map_frag_fail;
		पूर्ण
		priv->ops.fill_desc(ring, skb_frag_page(frag), size, dma,
				    seg_num - 1 == i ? 1 : 0, buf_num,
				    DESC_TYPE_PAGE, ndev->mtu);
	पूर्ण

	/*complete translate all packets*/
	dev_queue = netdev_get_tx_queue(ndev, skb->queue_mapping);
	netdev_tx_sent_queue(dev_queue, skb->len);

	netअगर_trans_update(ndev);
	ndev->stats.tx_bytes += skb->len;
	ndev->stats.tx_packets++;

	wmb(); /* commit all data beक्रमe submit */
	निश्चित(skb->queue_mapping < priv->ae_handle->q_num);
	hnae_queue_xmit(priv->ae_handle->qs[skb->queue_mapping], buf_num);

	वापस NETDEV_TX_OK;

out_map_frag_fail:

	जबतक (ring->next_to_use != next_to_use) अणु
		unfill_desc(ring);
		अगर (ring->next_to_use != next_to_use)
			dma_unmap_page(dev,
				       ring->desc_cb[ring->next_to_use].dma,
				       ring->desc_cb[ring->next_to_use].length,
				       DMA_TO_DEVICE);
		अन्यथा
			dma_unmap_single(dev,
					 ring->desc_cb[next_to_use].dma,
					 ring->desc_cb[next_to_use].length,
					 DMA_TO_DEVICE);
	पूर्ण

out_err_tx_ok:

	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;

out_net_tx_busy:

	netअगर_stop_subqueue(ndev, skb->queue_mapping);

	/* Herbert's original patch had:
	 *  smp_mb__after_netअगर_stop_queue();
	 * but since that करोesn't exist yet, just खोलो code it.
	 */
	smp_mb();
	वापस NETDEV_TX_BUSY;
पूर्ण

अटल व्योम hns_nic_reuse_page(काष्ठा sk_buff *skb, पूर्णांक i,
			       काष्ठा hnae_ring *ring, पूर्णांक pull_len,
			       काष्ठा hnae_desc_cb *desc_cb)
अणु
	काष्ठा hnae_desc *desc;
	u32 truesize;
	पूर्णांक size;
	पूर्णांक last_offset;
	bool twobufs;

	twobufs = ((PAGE_SIZE < 8192) &&
		hnae_buf_size(ring) == HNS_BUFFER_SIZE_2048);

	desc = &ring->desc[ring->next_to_clean];
	size = le16_to_cpu(desc->rx.size);

	अगर (twobufs) अणु
		truesize = hnae_buf_size(ring);
	पूर्ण अन्यथा अणु
		truesize = ALIGN(size, L1_CACHE_BYTES);
		last_offset = hnae_page_size(ring) - hnae_buf_size(ring);
	पूर्ण

	skb_add_rx_frag(skb, i, desc_cb->priv, desc_cb->page_offset + pull_len,
			size - pull_len, truesize);

	 /* aव्योम re-using remote pages,flag शेष unreuse */
	अगर (unlikely(page_to_nid(desc_cb->priv) != numa_node_id()))
		वापस;

	अगर (twobufs) अणु
		/* अगर we are only owner of page we can reuse it */
		अगर (likely(page_count(desc_cb->priv) == 1)) अणु
			/* flip page offset to other buffer */
			desc_cb->page_offset ^= truesize;

			desc_cb->reuse_flag = 1;
			/* bump ref count on page beक्रमe it is given*/
			get_page(desc_cb->priv);
		पूर्ण
		वापस;
	पूर्ण

	/* move offset up to the next cache line */
	desc_cb->page_offset += truesize;

	अगर (desc_cb->page_offset <= last_offset) अणु
		desc_cb->reuse_flag = 1;
		/* bump ref count on page beक्रमe it is given*/
		get_page(desc_cb->priv);
	पूर्ण
पूर्ण

अटल व्योम get_v2rx_desc_bnum(u32 bnum_flag, पूर्णांक *out_bnum)
अणु
	*out_bnum = hnae_get_field(bnum_flag,
				   HNS_RXD_BUFNUM_M, HNS_RXD_BUFNUM_S) + 1;
पूर्ण

अटल व्योम get_rx_desc_bnum(u32 bnum_flag, पूर्णांक *out_bnum)
अणु
	*out_bnum = hnae_get_field(bnum_flag,
				   HNS_RXD_BUFNUM_M, HNS_RXD_BUFNUM_S);
पूर्ण

अटल व्योम hns_nic_rx_checksum(काष्ठा hns_nic_ring_data *ring_data,
				काष्ठा sk_buff *skb, u32 flag)
अणु
	काष्ठा net_device *netdev = ring_data->napi.dev;
	u32 l3id;
	u32 l4id;

	/* check अगर RX checksum offload is enabled */
	अगर (unlikely(!(netdev->features & NETIF_F_RXCSUM)))
		वापस;

	/* In hardware, we only support checksum क्रम the following protocols:
	 * 1) IPv4,
	 * 2) TCP(over IPv4 or IPv6),
	 * 3) UDP(over IPv4 or IPv6),
	 * 4) SCTP(over IPv4 or IPv6)
	 * but we support many L3(IPv4, IPv6, MPLS, PPPoE etc) and L4(TCP,
	 * UDP, GRE, SCTP, IGMP, ICMP etc.) protocols.
	 *
	 * Hardware limitation:
	 * Our present hardware RX Descriptor lacks L3/L4 checksum "Status &
	 * Error" bit (which usually can be used to indicate whether checksum
	 * was calculated by the hardware and अगर there was any error encountered
	 * during checksum calculation).
	 *
	 * Software workaround:
	 * We करो get info within the RX descriptor about the kind of L3/L4
	 * protocol coming in the packet and the error status. These errors
	 * might not just be checksum errors but could be related to version,
	 * length of IPv4, UDP, TCP etc.
	 * Because there is no-way of knowing अगर it is a L3/L4 error due to bad
	 * checksum or any other L3/L4 error, we will not (cannot) convey
	 * checksum status क्रम such हालs to upper stack and will not मुख्यtain
	 * the RX L3/L4 checksum counters as well.
	 */

	l3id = hnae_get_field(flag, HNS_RXD_L3ID_M, HNS_RXD_L3ID_S);
	l4id = hnae_get_field(flag, HNS_RXD_L4ID_M, HNS_RXD_L4ID_S);

	/*  check L3 protocol क्रम which checksum is supported */
	अगर ((l3id != HNS_RX_FLAG_L3ID_IPV4) && (l3id != HNS_RX_FLAG_L3ID_IPV6))
		वापस;

	/* check क्रम any(not just checksum)flagged L3 protocol errors */
	अगर (unlikely(hnae_get_bit(flag, HNS_RXD_L3E_B)))
		वापस;

	/* we करो not support checksum of fragmented packets */
	अगर (unlikely(hnae_get_bit(flag, HNS_RXD_FRAG_B)))
		वापस;

	/*  check L4 protocol क्रम which checksum is supported */
	अगर ((l4id != HNS_RX_FLAG_L4ID_TCP) &&
	    (l4id != HNS_RX_FLAG_L4ID_UDP) &&
	    (l4id != HNS_RX_FLAG_L4ID_SCTP))
		वापस;

	/* check क्रम any(not just checksum)flagged L4 protocol errors */
	अगर (unlikely(hnae_get_bit(flag, HNS_RXD_L4E_B)))
		वापस;

	/* now, this has to be a packet with valid RX checksum */
	skb->ip_summed = CHECKSUM_UNNECESSARY;
पूर्ण

अटल पूर्णांक hns_nic_poll_rx_skb(काष्ठा hns_nic_ring_data *ring_data,
			       काष्ठा sk_buff **out_skb, पूर्णांक *out_bnum)
अणु
	काष्ठा hnae_ring *ring = ring_data->ring;
	काष्ठा net_device *ndev = ring_data->napi.dev;
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);
	काष्ठा sk_buff *skb;
	काष्ठा hnae_desc *desc;
	काष्ठा hnae_desc_cb *desc_cb;
	अचिन्हित अक्षर *va;
	पूर्णांक bnum, length, i;
	पूर्णांक pull_len;
	u32 bnum_flag;

	desc = &ring->desc[ring->next_to_clean];
	desc_cb = &ring->desc_cb[ring->next_to_clean];

	prefetch(desc);

	va = (अचिन्हित अक्षर *)desc_cb->buf + desc_cb->page_offset;

	/* prefetch first cache line of first page */
	net_prefetch(va);

	skb = *out_skb = napi_alloc_skb(&ring_data->napi,
					HNS_RX_HEAD_SIZE);
	अगर (unlikely(!skb)) अणु
		ring->stats.sw_err_cnt++;
		वापस -ENOMEM;
	पूर्ण

	prefetchw(skb->data);
	length = le16_to_cpu(desc->rx.pkt_len);
	bnum_flag = le32_to_cpu(desc->rx.ipoff_bnum_pid_flag);
	priv->ops.get_rxd_bnum(bnum_flag, &bnum);
	*out_bnum = bnum;

	अगर (length <= HNS_RX_HEAD_SIZE) अणु
		स_नकल(__skb_put(skb, length), va, ALIGN(length, माप(दीर्घ)));

		/* we can reuse buffer as-is, just make sure it is local */
		अगर (likely(page_to_nid(desc_cb->priv) == numa_node_id()))
			desc_cb->reuse_flag = 1;
		अन्यथा /* this page cannot be reused so discard it */
			put_page(desc_cb->priv);

		ring_ptr_move_fw(ring, next_to_clean);

		अगर (unlikely(bnum != 1)) अणु /* check err*/
			*out_bnum = 1;
			जाओ out_bnum_err;
		पूर्ण
	पूर्ण अन्यथा अणु
		ring->stats.seg_pkt_cnt++;

		pull_len = eth_get_headlen(ndev, va, HNS_RX_HEAD_SIZE);
		स_नकल(__skb_put(skb, pull_len), va,
		       ALIGN(pull_len, माप(दीर्घ)));

		hns_nic_reuse_page(skb, 0, ring, pull_len, desc_cb);
		ring_ptr_move_fw(ring, next_to_clean);

		अगर (unlikely(bnum >= (पूर्णांक)MAX_SKB_FRAGS)) अणु /* check err*/
			*out_bnum = 1;
			जाओ out_bnum_err;
		पूर्ण
		क्रम (i = 1; i < bnum; i++) अणु
			desc = &ring->desc[ring->next_to_clean];
			desc_cb = &ring->desc_cb[ring->next_to_clean];

			hns_nic_reuse_page(skb, i, ring, 0, desc_cb);
			ring_ptr_move_fw(ring, next_to_clean);
		पूर्ण
	पूर्ण

	/* check except process, मुक्त skb and jump the desc */
	अगर (unlikely((!bnum) || (bnum > ring->max_desc_num_per_pkt))) अणु
out_bnum_err:
		*out_bnum = *out_bnum ? *out_bnum : 1; /* ntc moved,cannot 0*/
		netdev_err(ndev, "invalid bnum(%d,%d,%d,%d),%016llx,%016llx\n",
			   bnum, ring->max_desc_num_per_pkt,
			   length, (पूर्णांक)MAX_SKB_FRAGS,
			   ((u64 *)desc)[0], ((u64 *)desc)[1]);
		ring->stats.err_bd_num++;
		dev_kमुक्त_skb_any(skb);
		वापस -गलत_तर्क;
	पूर्ण

	bnum_flag = le32_to_cpu(desc->rx.ipoff_bnum_pid_flag);

	अगर (unlikely(!hnae_get_bit(bnum_flag, HNS_RXD_VLD_B))) अणु
		netdev_err(ndev, "no valid bd,%016llx,%016llx\n",
			   ((u64 *)desc)[0], ((u64 *)desc)[1]);
		ring->stats.non_vld_descs++;
		dev_kमुक्त_skb_any(skb);
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely((!desc->rx.pkt_len) ||
		     hnae_get_bit(bnum_flag, HNS_RXD_DROP_B))) अणु
		ring->stats.err_pkt_len++;
		dev_kमुक्त_skb_any(skb);
		वापस -EFAULT;
	पूर्ण

	अगर (unlikely(hnae_get_bit(bnum_flag, HNS_RXD_L2E_B))) अणु
		ring->stats.l2_err++;
		dev_kमुक्त_skb_any(skb);
		वापस -EFAULT;
	पूर्ण

	ring->stats.rx_pkts++;
	ring->stats.rx_bytes += skb->len;

	/* indicate to upper stack अगर our hardware has alपढ़ोy calculated
	 * the RX checksum
	 */
	hns_nic_rx_checksum(ring_data, skb, bnum_flag);

	वापस 0;
पूर्ण

अटल व्योम
hns_nic_alloc_rx_buffers(काष्ठा hns_nic_ring_data *ring_data, पूर्णांक cleand_count)
अणु
	पूर्णांक i, ret;
	काष्ठा hnae_desc_cb res_cbs;
	काष्ठा hnae_desc_cb *desc_cb;
	काष्ठा hnae_ring *ring = ring_data->ring;
	काष्ठा net_device *ndev = ring_data->napi.dev;

	क्रम (i = 0; i < cleand_count; i++) अणु
		desc_cb = &ring->desc_cb[ring->next_to_use];
		अगर (desc_cb->reuse_flag) अणु
			ring->stats.reuse_pg_cnt++;
			hnae_reuse_buffer(ring, ring->next_to_use);
		पूर्ण अन्यथा अणु
			ret = hnae_reserve_buffer_map(ring, &res_cbs);
			अगर (ret) अणु
				ring->stats.sw_err_cnt++;
				netdev_err(ndev, "hnae reserve buffer map failed.\n");
				अवरोध;
			पूर्ण
			hnae_replace_buffer(ring, ring->next_to_use, &res_cbs);
		पूर्ण

		ring_ptr_move_fw(ring, next_to_use);
	पूर्ण

	wmb(); /* make all data has been ग_लिखो beक्रमe submit */
	ग_लिखोl_relaxed(i, ring->io_base + RCB_REG_HEAD);
पूर्ण

/* वापस error number क्रम error or number of desc left to take
 */
अटल व्योम hns_nic_rx_up_pro(काष्ठा hns_nic_ring_data *ring_data,
			      काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *ndev = ring_data->napi.dev;

	skb->protocol = eth_type_trans(skb, ndev);
	napi_gro_receive(&ring_data->napi, skb);
पूर्ण

अटल पूर्णांक hns_desc_unused(काष्ठा hnae_ring *ring)
अणु
	पूर्णांक ntc = ring->next_to_clean;
	पूर्णांक ntu = ring->next_to_use;

	वापस ((ntc >= ntu) ? 0 : ring->desc_num) + ntc - ntu;
पूर्ण

#घोषणा HNS_LOWEST_LATENCY_RATE		27	/* 27 MB/s */
#घोषणा HNS_LOW_LATENCY_RATE			80	/* 80 MB/s */

#घोषणा HNS_COAL_BDNUM			3

अटल u32 hns_coal_rx_bdnum(काष्ठा hnae_ring *ring)
अणु
	bool coal_enable = ring->q->handle->coal_adapt_en;

	अगर (coal_enable &&
	    ring->coal_last_rx_bytes > HNS_LOWEST_LATENCY_RATE)
		वापस HNS_COAL_BDNUM;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम hns_update_rx_rate(काष्ठा hnae_ring *ring)
अणु
	bool coal_enable = ring->q->handle->coal_adapt_en;
	u32 समय_passed_ms;
	u64 total_bytes;

	अगर (!coal_enable ||
	    समय_beक्रमe(jअगरfies, ring->coal_last_jअगरfies + (HZ >> 4)))
		वापस;

	/* ring->stats.rx_bytes overflowed */
	अगर (ring->coal_last_rx_bytes > ring->stats.rx_bytes) अणु
		ring->coal_last_rx_bytes = ring->stats.rx_bytes;
		ring->coal_last_jअगरfies = jअगरfies;
		वापस;
	पूर्ण

	total_bytes = ring->stats.rx_bytes - ring->coal_last_rx_bytes;
	समय_passed_ms = jअगरfies_to_msecs(jअगरfies - ring->coal_last_jअगरfies);
	करो_भाग(total_bytes, समय_passed_ms);
	ring->coal_rx_rate = total_bytes >> 10;

	ring->coal_last_rx_bytes = ring->stats.rx_bytes;
	ring->coal_last_jअगरfies = jअगरfies;
पूर्ण

/**
 * smooth_alg - smoothing algrithm क्रम adjusting coalesce parameter
 * @new_param: new value
 * @old_param: old value
 **/
अटल u32 smooth_alg(u32 new_param, u32 old_param)
अणु
	u32 gap = (new_param > old_param) ? new_param - old_param
					  : old_param - new_param;

	अगर (gap > 8)
		gap >>= 3;

	अगर (new_param > old_param)
		वापस old_param + gap;
	अन्यथा
		वापस old_param - gap;
पूर्ण

/**
 * hns_nic_adp_coalesce - self adapte coalesce according to rx rate
 * @ring_data: poपूर्णांकer to hns_nic_ring_data
 **/
अटल व्योम hns_nic_adpt_coalesce(काष्ठा hns_nic_ring_data *ring_data)
अणु
	काष्ठा hnae_ring *ring = ring_data->ring;
	काष्ठा hnae_handle *handle = ring->q->handle;
	u32 new_coal_param, old_coal_param = ring->coal_param;

	अगर (ring->coal_rx_rate < HNS_LOWEST_LATENCY_RATE)
		new_coal_param = HNAE_LOWEST_LATENCY_COAL_PARAM;
	अन्यथा अगर (ring->coal_rx_rate < HNS_LOW_LATENCY_RATE)
		new_coal_param = HNAE_LOW_LATENCY_COAL_PARAM;
	अन्यथा
		new_coal_param = HNAE_BULK_LATENCY_COAL_PARAM;

	अगर (new_coal_param == old_coal_param &&
	    new_coal_param == handle->coal_param)
		वापस;

	new_coal_param = smooth_alg(new_coal_param, old_coal_param);
	ring->coal_param = new_coal_param;

	/**
	 * Because all ring in one port has one coalesce param, when one ring
	 * calculate its own coalesce param, it cannot ग_लिखो to hardware at
	 * once. There are three conditions as follows:
	 *       1. current ring's coalesce param is larger than the hardware.
	 *       2. or ring which adapt last समय can change again.
	 *       3. समयout.
	 */
	अगर (new_coal_param == handle->coal_param) अणु
		handle->coal_last_jअगरfies = jअगरfies;
		handle->coal_ring_idx = ring_data->queue_index;
	पूर्ण अन्यथा अगर (new_coal_param > handle->coal_param ||
		   handle->coal_ring_idx == ring_data->queue_index ||
		   समय_after(jअगरfies, handle->coal_last_jअगरfies + (HZ >> 4))) अणु
		handle->dev->ops->set_coalesce_usecs(handle,
					new_coal_param);
		handle->dev->ops->set_coalesce_frames(handle,
					1, new_coal_param);
		handle->coal_param = new_coal_param;
		handle->coal_ring_idx = ring_data->queue_index;
		handle->coal_last_jअगरfies = jअगरfies;
	पूर्ण
पूर्ण

अटल पूर्णांक hns_nic_rx_poll_one(काष्ठा hns_nic_ring_data *ring_data,
			       पूर्णांक budget, व्योम *v)
अणु
	काष्ठा hnae_ring *ring = ring_data->ring;
	काष्ठा sk_buff *skb;
	पूर्णांक num, bnum;
#घोषणा RCB_NOF_ALLOC_RX_BUFF_ONCE 16
	पूर्णांक recv_pkts, recv_bds, clean_count, err;
	पूर्णांक unused_count = hns_desc_unused(ring);

	num = पढ़ोl_relaxed(ring->io_base + RCB_REG_FBDNUM);
	rmb(); /* make sure num taken effect beक्रमe the other data is touched */

	recv_pkts = 0, recv_bds = 0, clean_count = 0;
	num -= unused_count;

	जबतक (recv_pkts < budget && recv_bds < num) अणु
		/* reuse or पुनः_स्मृति buffers */
		अगर (clean_count + unused_count >= RCB_NOF_ALLOC_RX_BUFF_ONCE) अणु
			hns_nic_alloc_rx_buffers(ring_data,
						 clean_count + unused_count);
			clean_count = 0;
			unused_count = hns_desc_unused(ring);
		पूर्ण

		/* poll one pkt */
		err = hns_nic_poll_rx_skb(ring_data, &skb, &bnum);
		अगर (unlikely(!skb)) /* this fault cannot be repaired */
			जाओ out;

		recv_bds += bnum;
		clean_count += bnum;
		अगर (unlikely(err)) अणु  /* करो jump the err */
			recv_pkts++;
			जारी;
		पूर्ण

		/* करो update ip stack process*/
		((व्योम (*)(काष्ठा hns_nic_ring_data *, काष्ठा sk_buff *))v)(
							ring_data, skb);
		recv_pkts++;
	पूर्ण

out:
	/* make all data has been ग_लिखो beक्रमe submit */
	अगर (clean_count + unused_count > 0)
		hns_nic_alloc_rx_buffers(ring_data,
					 clean_count + unused_count);

	वापस recv_pkts;
पूर्ण

अटल bool hns_nic_rx_fini_pro(काष्ठा hns_nic_ring_data *ring_data)
अणु
	काष्ठा hnae_ring *ring = ring_data->ring;
	पूर्णांक num;
	bool rx_stopped;

	hns_update_rx_rate(ring);

	/* क्रम hardware bug fixed */
	ring_data->ring->q->handle->dev->ops->toggle_ring_irq(ring, 0);
	num = पढ़ोl_relaxed(ring->io_base + RCB_REG_FBDNUM);

	अगर (num <= hns_coal_rx_bdnum(ring)) अणु
		अगर (ring->q->handle->coal_adapt_en)
			hns_nic_adpt_coalesce(ring_data);

		rx_stopped = true;
	पूर्ण अन्यथा अणु
		ring_data->ring->q->handle->dev->ops->toggle_ring_irq(
			ring_data->ring, 1);

		rx_stopped = false;
	पूर्ण

	वापस rx_stopped;
पूर्ण

अटल bool hns_nic_rx_fini_pro_v2(काष्ठा hns_nic_ring_data *ring_data)
अणु
	काष्ठा hnae_ring *ring = ring_data->ring;
	पूर्णांक num;

	hns_update_rx_rate(ring);
	num = पढ़ोl_relaxed(ring->io_base + RCB_REG_FBDNUM);

	अगर (num <= hns_coal_rx_bdnum(ring)) अणु
		अगर (ring->q->handle->coal_adapt_en)
			hns_nic_adpt_coalesce(ring_data);

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत व्योम hns_nic_reclaim_one_desc(काष्ठा hnae_ring *ring,
					    पूर्णांक *bytes, पूर्णांक *pkts)
अणु
	काष्ठा hnae_desc_cb *desc_cb = &ring->desc_cb[ring->next_to_clean];

	(*pkts) += (desc_cb->type == DESC_TYPE_SKB);
	(*bytes) += desc_cb->length;
	/* desc_cb will be cleaned, after hnae_मुक्त_buffer_detach*/
	hnae_मुक्त_buffer_detach(ring, ring->next_to_clean);

	ring_ptr_move_fw(ring, next_to_clean);
पूर्ण

अटल पूर्णांक is_valid_clean_head(काष्ठा hnae_ring *ring, पूर्णांक h)
अणु
	पूर्णांक u = ring->next_to_use;
	पूर्णांक c = ring->next_to_clean;

	अगर (unlikely(h > ring->desc_num))
		वापस 0;

	निश्चित(u > 0 && u < ring->desc_num);
	निश्चित(c > 0 && c < ring->desc_num);
	निश्चित(u != c && h != c); /* must be checked beक्रमe call this func */

	वापस u > c ? (h > c && h <= u) : (h > c || h <= u);
पूर्ण

/* reclaim all desc in one budget
 * वापस error or number of desc left
 */
अटल पूर्णांक hns_nic_tx_poll_one(काष्ठा hns_nic_ring_data *ring_data,
			       पूर्णांक budget, व्योम *v)
अणु
	काष्ठा hnae_ring *ring = ring_data->ring;
	काष्ठा net_device *ndev = ring_data->napi.dev;
	काष्ठा netdev_queue *dev_queue;
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);
	पूर्णांक head;
	पूर्णांक bytes, pkts;

	head = पढ़ोl_relaxed(ring->io_base + RCB_REG_HEAD);
	rmb(); /* make sure head is पढ़ोy beक्रमe touch any data */

	अगर (is_ring_empty(ring) || head == ring->next_to_clean)
		वापस 0; /* no data to poll */

	अगर (!is_valid_clean_head(ring, head)) अणु
		netdev_err(ndev, "wrong head (%d, %d-%d)\n", head,
			   ring->next_to_use, ring->next_to_clean);
		ring->stats.io_err_cnt++;
		वापस -EIO;
	पूर्ण

	bytes = 0;
	pkts = 0;
	जबतक (head != ring->next_to_clean) अणु
		hns_nic_reclaim_one_desc(ring, &bytes, &pkts);
		/* issue prefetch क्रम next Tx descriptor */
		prefetch(&ring->desc_cb[ring->next_to_clean]);
	पूर्ण
	/* update tx ring statistics. */
	ring->stats.tx_pkts += pkts;
	ring->stats.tx_bytes += bytes;

	dev_queue = netdev_get_tx_queue(ndev, ring_data->queue_index);
	netdev_tx_completed_queue(dev_queue, pkts, bytes);

	अगर (unlikely(priv->link && !netअगर_carrier_ok(ndev)))
		netअगर_carrier_on(ndev);

	अगर (unlikely(pkts && netअगर_carrier_ok(ndev) &&
		     (ring_space(ring) >= ring->max_desc_num_per_pkt * 2))) अणु
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();
		अगर (netअगर_tx_queue_stopped(dev_queue) &&
		    !test_bit(NIC_STATE_DOWN, &priv->state)) अणु
			netअगर_tx_wake_queue(dev_queue);
			ring->stats.restart_queue++;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल bool hns_nic_tx_fini_pro(काष्ठा hns_nic_ring_data *ring_data)
अणु
	काष्ठा hnae_ring *ring = ring_data->ring;
	पूर्णांक head;

	ring_data->ring->q->handle->dev->ops->toggle_ring_irq(ring, 0);

	head = पढ़ोl_relaxed(ring->io_base + RCB_REG_HEAD);

	अगर (head != ring->next_to_clean) अणु
		ring_data->ring->q->handle->dev->ops->toggle_ring_irq(
			ring_data->ring, 1);

		वापस false;
	पूर्ण अन्यथा अणु
		वापस true;
	पूर्ण
पूर्ण

अटल bool hns_nic_tx_fini_pro_v2(काष्ठा hns_nic_ring_data *ring_data)
अणु
	काष्ठा hnae_ring *ring = ring_data->ring;
	पूर्णांक head = पढ़ोl_relaxed(ring->io_base + RCB_REG_HEAD);

	अगर (head == ring->next_to_clean)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम hns_nic_tx_clr_all_bufs(काष्ठा hns_nic_ring_data *ring_data)
अणु
	काष्ठा hnae_ring *ring = ring_data->ring;
	काष्ठा net_device *ndev = ring_data->napi.dev;
	काष्ठा netdev_queue *dev_queue;
	पूर्णांक head;
	पूर्णांक bytes, pkts;

	head = ring->next_to_use; /* ntu :soft setted ring position*/
	bytes = 0;
	pkts = 0;
	जबतक (head != ring->next_to_clean)
		hns_nic_reclaim_one_desc(ring, &bytes, &pkts);

	dev_queue = netdev_get_tx_queue(ndev, ring_data->queue_index);
	netdev_tx_reset_queue(dev_queue);
पूर्ण

अटल पूर्णांक hns_nic_common_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	पूर्णांक clean_complete = 0;
	काष्ठा hns_nic_ring_data *ring_data =
		container_of(napi, काष्ठा hns_nic_ring_data, napi);
	काष्ठा hnae_ring *ring = ring_data->ring;

	clean_complete += ring_data->poll_one(
				ring_data, budget - clean_complete,
				ring_data->ex_process);

	अगर (clean_complete < budget) अणु
		अगर (ring_data->fini_process(ring_data)) अणु
			napi_complete(napi);
			ring->q->handle->dev->ops->toggle_ring_irq(ring, 0);
		पूर्ण अन्यथा अणु
			वापस budget;
		पूर्ण
	पूर्ण

	वापस clean_complete;
पूर्ण

अटल irqवापस_t hns_irq_handle(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा hns_nic_ring_data *ring_data = (काष्ठा hns_nic_ring_data *)dev;

	ring_data->ring->q->handle->dev->ops->toggle_ring_irq(
		ring_data->ring, 1);
	napi_schedule(&ring_data->napi);

	वापस IRQ_HANDLED;
पूर्ण

/**
 *hns_nic_adjust_link - adjust net work mode by the phy stat or new param
 *@ndev: net device
 */
अटल व्योम hns_nic_adjust_link(काष्ठा net_device *ndev)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hnae_handle *h = priv->ae_handle;
	पूर्णांक state = 1;

	/* If there is no phy, करो not need adjust link */
	अगर (ndev->phydev) अणु
		/* When phy link करोwn, करो nothing */
		अगर (ndev->phydev->link == 0)
			वापस;

		अगर (h->dev->ops->need_adjust_link(h, ndev->phydev->speed,
						  ndev->phydev->duplex)) अणु
			/* because Hi161X chip करोn't support to change gmac
			 * speed and duplex with traffic. Delay 200ms to
			 * make sure there is no more data in chip FIFO.
			 */
			netअगर_carrier_off(ndev);
			msleep(200);
			h->dev->ops->adjust_link(h, ndev->phydev->speed,
						 ndev->phydev->duplex);
			netअगर_carrier_on(ndev);
		पूर्ण
	पूर्ण

	state = state && h->dev->ops->get_status(h);

	अगर (state != priv->link) अणु
		अगर (state) अणु
			netअगर_carrier_on(ndev);
			netअगर_tx_wake_all_queues(ndev);
			netdev_info(ndev, "link up\n");
		पूर्ण अन्यथा अणु
			netअगर_carrier_off(ndev);
			netdev_info(ndev, "link down\n");
		पूर्ण
		priv->link = state;
	पूर्ण
पूर्ण

/**
 *hns_nic_init_phy - init phy
 *@ndev: net device
 *@h: ae handle
 * Return 0 on success, negative on failure
 */
पूर्णांक hns_nic_init_phy(काष्ठा net_device *ndev, काष्ठा hnae_handle *h)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(supported) = अणु 0, पूर्ण;
	काष्ठा phy_device *phy_dev = h->phy_dev;
	पूर्णांक ret;

	अगर (!h->phy_dev)
		वापस 0;

	ethtool_convert_legacy_u32_to_link_mode(supported, h->अगर_support);
	linkmode_and(phy_dev->supported, phy_dev->supported, supported);
	linkmode_copy(phy_dev->advertising, phy_dev->supported);

	अगर (h->phy_अगर == PHY_INTERFACE_MODE_XGMII)
		phy_dev->स्वतःneg = false;

	अगर (h->phy_अगर != PHY_INTERFACE_MODE_XGMII) अणु
		phy_dev->dev_flags = 0;

		ret = phy_connect_direct(ndev, phy_dev, hns_nic_adjust_link,
					 h->phy_अगर);
	पूर्ण अन्यथा अणु
		ret = phy_attach_direct(ndev, phy_dev, 0, h->phy_अगर);
	पूर्ण
	अगर (unlikely(ret))
		वापस -ENODEV;

	phy_attached_info(phy_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक hns_nic_ring_खोलो(काष्ठा net_device *netdev, पूर्णांक idx)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae_handle *h = priv->ae_handle;

	napi_enable(&priv->ring_data[idx].napi);

	enable_irq(priv->ring_data[idx].ring->irq);
	h->dev->ops->toggle_ring_irq(priv->ring_data[idx].ring, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक hns_nic_net_set_mac_address(काष्ठा net_device *ndev, व्योम *p)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hnae_handle *h = priv->ae_handle;
	काष्ठा sockaddr *mac_addr = p;
	पूर्णांक ret;

	अगर (!mac_addr || !is_valid_ether_addr((स्थिर u8 *)mac_addr->sa_data))
		वापस -EADDRNOTAVAIL;

	ret = h->dev->ops->set_mac_addr(h, mac_addr->sa_data);
	अगर (ret) अणु
		netdev_err(ndev, "set_mac_address fail, ret=%d!\n", ret);
		वापस ret;
	पूर्ण

	स_नकल(ndev->dev_addr, mac_addr->sa_data, ndev->addr_len);

	वापस 0;
पूर्ण

अटल व्योम hns_nic_update_stats(काष्ठा net_device *netdev)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae_handle *h = priv->ae_handle;

	h->dev->ops->update_stats(h, &netdev->stats);
पूर्ण

/* set mac addr अगर it is configed. or leave it to the AE driver */
अटल व्योम hns_init_mac_addr(काष्ठा net_device *ndev)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);

	अगर (!device_get_mac_address(priv->dev, ndev->dev_addr, ETH_ALEN)) अणु
		eth_hw_addr_अक्रमom(ndev);
		dev_warn(priv->dev, "No valid mac, use random mac %pM",
			 ndev->dev_addr);
	पूर्ण
पूर्ण

अटल व्योम hns_nic_ring_बंद(काष्ठा net_device *netdev, पूर्णांक idx)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae_handle *h = priv->ae_handle;

	h->dev->ops->toggle_ring_irq(priv->ring_data[idx].ring, 1);
	disable_irq(priv->ring_data[idx].ring->irq);

	napi_disable(&priv->ring_data[idx].napi);
पूर्ण

अटल पूर्णांक hns_nic_init_affinity_mask(पूर्णांक q_num, पूर्णांक ring_idx,
				      काष्ठा hnae_ring *ring, cpumask_t *mask)
अणु
	पूर्णांक cpu;

	/* Dअगरferent irq balance between 16core and 32core.
	 * The cpu mask set by ring index according to the ring flag
	 * which indicate the ring is tx or rx.
	 */
	अगर (q_num == num_possible_cpus()) अणु
		अगर (is_tx_ring(ring))
			cpu = ring_idx;
		अन्यथा
			cpu = ring_idx - q_num;
	पूर्ण अन्यथा अणु
		अगर (is_tx_ring(ring))
			cpu = ring_idx * 2;
		अन्यथा
			cpu = (ring_idx - q_num) * 2 + 1;
	पूर्ण

	cpumask_clear(mask);
	cpumask_set_cpu(cpu, mask);

	वापस cpu;
पूर्ण

अटल व्योम hns_nic_मुक्त_irq(पूर्णांक q_num, काष्ठा hns_nic_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < q_num * 2; i++) अणु
		अगर (priv->ring_data[i].ring->irq_init_flag == RCB_IRQ_INITED) अणु
			irq_set_affinity_hपूर्णांक(priv->ring_data[i].ring->irq,
					      शून्य);
			मुक्त_irq(priv->ring_data[i].ring->irq,
				 &priv->ring_data[i]);
			priv->ring_data[i].ring->irq_init_flag =
				RCB_IRQ_NOT_INITED;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक hns_nic_init_irq(काष्ठा hns_nic_priv *priv)
अणु
	काष्ठा hnae_handle *h = priv->ae_handle;
	काष्ठा hns_nic_ring_data *rd;
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक cpu;

	क्रम (i = 0; i < h->q_num * 2; i++) अणु
		rd = &priv->ring_data[i];

		अगर (rd->ring->irq_init_flag == RCB_IRQ_INITED)
			अवरोध;

		snम_लिखो(rd->ring->ring_name, RCB_RING_NAME_LEN,
			 "%s-%s%d", priv->netdev->name,
			 (is_tx_ring(rd->ring) ? "tx" : "rx"), rd->queue_index);

		rd->ring->ring_name[RCB_RING_NAME_LEN - 1] = '\0';

		irq_set_status_flags(rd->ring->irq, IRQ_NOAUTOEN);
		ret = request_irq(rd->ring->irq,
				  hns_irq_handle, 0, rd->ring->ring_name, rd);
		अगर (ret) अणु
			netdev_err(priv->netdev, "request irq(%d) fail\n",
				   rd->ring->irq);
			जाओ out_मुक्त_irq;
		पूर्ण

		cpu = hns_nic_init_affinity_mask(h->q_num, i,
						 rd->ring, &rd->mask);

		अगर (cpu_online(cpu))
			irq_set_affinity_hपूर्णांक(rd->ring->irq,
					      &rd->mask);

		rd->ring->irq_init_flag = RCB_IRQ_INITED;
	पूर्ण

	वापस 0;

out_मुक्त_irq:
	hns_nic_मुक्त_irq(h->q_num, priv);
	वापस ret;
पूर्ण

अटल पूर्णांक hns_nic_net_up(काष्ठा net_device *ndev)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hnae_handle *h = priv->ae_handle;
	पूर्णांक i, j;
	पूर्णांक ret;

	अगर (!test_bit(NIC_STATE_DOWN, &priv->state))
		वापस 0;

	ret = hns_nic_init_irq(priv);
	अगर (ret != 0) अणु
		netdev_err(ndev, "hns init irq failed! ret=%d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < h->q_num * 2; i++) अणु
		ret = hns_nic_ring_खोलो(ndev, i);
		अगर (ret)
			जाओ out_has_some_queues;
	पूर्ण

	ret = h->dev->ops->set_mac_addr(h, ndev->dev_addr);
	अगर (ret)
		जाओ out_set_mac_addr_err;

	ret = h->dev->ops->start ? h->dev->ops->start(h) : 0;
	अगर (ret)
		जाओ out_start_err;

	अगर (ndev->phydev)
		phy_start(ndev->phydev);

	clear_bit(NIC_STATE_DOWN, &priv->state);
	(व्योम)mod_समयr(&priv->service_समयr, jअगरfies + SERVICE_TIMER_HZ);

	वापस 0;

out_start_err:
	netअगर_stop_queue(ndev);
out_set_mac_addr_err:
out_has_some_queues:
	क्रम (j = i - 1; j >= 0; j--)
		hns_nic_ring_बंद(ndev, j);

	hns_nic_मुक्त_irq(h->q_num, priv);
	set_bit(NIC_STATE_DOWN, &priv->state);

	वापस ret;
पूर्ण

अटल व्योम hns_nic_net_करोwn(काष्ठा net_device *ndev)
अणु
	पूर्णांक i;
	काष्ठा hnae_ae_ops *ops;
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);

	अगर (test_and_set_bit(NIC_STATE_DOWN, &priv->state))
		वापस;

	(व्योम)del_समयr_sync(&priv->service_समयr);
	netअगर_tx_stop_all_queues(ndev);
	netअगर_carrier_off(ndev);
	netअगर_tx_disable(ndev);
	priv->link = 0;

	अगर (ndev->phydev)
		phy_stop(ndev->phydev);

	ops = priv->ae_handle->dev->ops;

	अगर (ops->stop)
		ops->stop(priv->ae_handle);

	netअगर_tx_stop_all_queues(ndev);

	क्रम (i = priv->ae_handle->q_num - 1; i >= 0; i--) अणु
		hns_nic_ring_बंद(ndev, i);
		hns_nic_ring_बंद(ndev, i + priv->ae_handle->q_num);

		/* clean tx buffers*/
		hns_nic_tx_clr_all_bufs(priv->ring_data + i);
	पूर्ण
पूर्ण

व्योम hns_nic_net_reset(काष्ठा net_device *ndev)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hnae_handle *handle = priv->ae_handle;

	जबतक (test_and_set_bit(NIC_STATE_RESETTING, &priv->state))
		usleep_range(1000, 2000);

	(व्योम)hnae_reinit_handle(handle);

	clear_bit(NIC_STATE_RESETTING, &priv->state);
पूर्ण

व्योम hns_nic_net_reinit(काष्ठा net_device *netdev)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(netdev);
	क्रमागत hnae_port_type type = priv->ae_handle->port_type;

	netअगर_trans_update(priv->netdev);
	जबतक (test_and_set_bit(NIC_STATE_REINITING, &priv->state))
		usleep_range(1000, 2000);

	hns_nic_net_करोwn(netdev);

	/* Only करो hns_nic_net_reset in debug mode
	 * because of hardware limitation.
	 */
	अगर (type == HNAE_PORT_DEBUG)
		hns_nic_net_reset(netdev);

	(व्योम)hns_nic_net_up(netdev);
	clear_bit(NIC_STATE_REINITING, &priv->state);
पूर्ण

अटल पूर्णांक hns_nic_net_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hnae_handle *h = priv->ae_handle;
	पूर्णांक ret;

	अगर (test_bit(NIC_STATE_TESTING, &priv->state))
		वापस -EBUSY;

	priv->link = 0;
	netअगर_carrier_off(ndev);

	ret = netअगर_set_real_num_tx_queues(ndev, h->q_num);
	अगर (ret < 0) अणु
		netdev_err(ndev, "netif_set_real_num_tx_queues fail, ret=%d!\n",
			   ret);
		वापस ret;
	पूर्ण

	ret = netअगर_set_real_num_rx_queues(ndev, h->q_num);
	अगर (ret < 0) अणु
		netdev_err(ndev,
			   "netif_set_real_num_rx_queues fail, ret=%d!\n", ret);
		वापस ret;
	पूर्ण

	ret = hns_nic_net_up(ndev);
	अगर (ret) अणु
		netdev_err(ndev,
			   "hns net up fail, ret=%d!\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns_nic_net_stop(काष्ठा net_device *ndev)
अणु
	hns_nic_net_करोwn(ndev);

	वापस 0;
पूर्ण

अटल व्योम hns_tx_समयout_reset(काष्ठा hns_nic_priv *priv);
#घोषणा HNS_TX_TIMEO_LIMIT (40 * HZ)
अटल व्योम hns_nic_net_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);

	अगर (ndev->watchकरोg_समयo < HNS_TX_TIMEO_LIMIT) अणु
		ndev->watchकरोg_समयo *= 2;
		netdev_info(ndev, "watchdog_timo changed to %d.\n",
			    ndev->watchकरोg_समयo);
	पूर्ण अन्यथा अणु
		ndev->watchकरोg_समयo = HNS_NIC_TX_TIMEOUT;
		hns_tx_समयout_reset(priv);
	पूर्ण
पूर्ण

अटल netdev_tx_t hns_nic_net_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *ndev)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);

	निश्चित(skb->queue_mapping < priv->ae_handle->q_num);

	वापस hns_nic_net_xmit_hw(ndev, skb,
				   &tx_ring_data(priv, skb->queue_mapping));
पूर्ण

अटल व्योम hns_nic_drop_rx_fetch(काष्ठा hns_nic_ring_data *ring_data,
				  काष्ठा sk_buff *skb)
अणु
	dev_kमुक्त_skb_any(skb);
पूर्ण

#घोषणा HNS_LB_TX_RING	0
अटल काष्ठा sk_buff *hns_assemble_skb(काष्ठा net_device *ndev)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ethhdr *ethhdr;
	पूर्णांक frame_len;

	/* allocate test skb */
	skb = alloc_skb(64, GFP_KERNEL);
	अगर (!skb)
		वापस शून्य;

	skb_put(skb, 64);
	skb->dev = ndev;
	स_रखो(skb->data, 0xFF, skb->len);

	/* must be tcp/ip package */
	ethhdr = (काष्ठा ethhdr *)skb->data;
	ethhdr->h_proto = htons(ETH_P_IP);

	frame_len = skb->len & (~1ul);
	स_रखो(&skb->data[frame_len / 2], 0xAA,
	       frame_len / 2 - 1);

	skb->queue_mapping = HNS_LB_TX_RING;

	वापस skb;
पूर्ण

अटल पूर्णांक hns_enable_serdes_lb(काष्ठा net_device *ndev)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hnae_handle *h = priv->ae_handle;
	काष्ठा hnae_ae_ops *ops = h->dev->ops;
	पूर्णांक speed, duplex;
	पूर्णांक ret;

	ret = ops->set_loopback(h, MAC_INTERNALLOOP_SERDES, 1);
	अगर (ret)
		वापस ret;

	ret = ops->start ? ops->start(h) : 0;
	अगर (ret)
		वापस ret;

	/* link adjust duplex*/
	अगर (h->phy_अगर != PHY_INTERFACE_MODE_XGMII)
		speed = 1000;
	अन्यथा
		speed = 10000;
	duplex = 1;

	ops->adjust_link(h, speed, duplex);

	/* रुको h/w पढ़ोy */
	mdelay(300);

	वापस 0;
पूर्ण

अटल व्योम hns_disable_serdes_lb(काष्ठा net_device *ndev)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hnae_handle *h = priv->ae_handle;
	काष्ठा hnae_ae_ops *ops = h->dev->ops;

	ops->stop(h);
	ops->set_loopback(h, MAC_INTERNALLOOP_SERDES, 0);
पूर्ण

/**
 *hns_nic_clear_all_rx_fetch - clear the chip fetched descriptions. The
 *function as follows:
 *    1. अगर one rx ring has found the page_offset is not equal 0 between head
 *       and tail, it means that the chip fetched the wrong descs क्रम the ring
 *       which buffer size is 4096.
 *    2. we set the chip serdes loopback and set rss indirection to the ring.
 *    3. स्थिरruct 64-bytes ip broadcast packages, रुको the associated rx ring
 *       receiving all packages and it will fetch new descriptions.
 *    4. recover to the original state.
 *
 *@ndev: net device
 */
अटल पूर्णांक hns_nic_clear_all_rx_fetch(काष्ठा net_device *ndev)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hnae_handle *h = priv->ae_handle;
	काष्ठा hnae_ae_ops *ops = h->dev->ops;
	काष्ठा hns_nic_ring_data *rd;
	काष्ठा hnae_ring *ring;
	काष्ठा sk_buff *skb;
	u32 *org_indir;
	u32 *cur_indir;
	पूर्णांक indir_size;
	पूर्णांक head, tail;
	पूर्णांक fetch_num;
	पूर्णांक i, j;
	bool found;
	पूर्णांक retry_बार;
	पूर्णांक ret = 0;

	/* alloc indir memory */
	indir_size = ops->get_rss_indir_size(h) * माप(*org_indir);
	org_indir = kzalloc(indir_size, GFP_KERNEL);
	अगर (!org_indir)
		वापस -ENOMEM;

	/* store the original indirection */
	ops->get_rss(h, org_indir, शून्य, शून्य);

	cur_indir = kzalloc(indir_size, GFP_KERNEL);
	अगर (!cur_indir) अणु
		ret = -ENOMEM;
		जाओ cur_indir_alloc_err;
	पूर्ण

	/* set loopback */
	अगर (hns_enable_serdes_lb(ndev)) अणु
		ret = -EINVAL;
		जाओ enable_serdes_lb_err;
	पूर्ण

	/* क्रमeach every rx ring to clear fetch desc */
	क्रम (i = 0; i < h->q_num; i++) अणु
		ring = &h->qs[i]->rx_ring;
		head = पढ़ोl_relaxed(ring->io_base + RCB_REG_HEAD);
		tail = पढ़ोl_relaxed(ring->io_base + RCB_REG_TAIL);
		found = false;
		fetch_num = ring_dist(ring, head, tail);

		जबतक (head != tail) अणु
			अगर (ring->desc_cb[head].page_offset != 0) अणु
				found = true;
				अवरोध;
			पूर्ण

			head++;
			अगर (head == ring->desc_num)
				head = 0;
		पूर्ण

		अगर (found) अणु
			क्रम (j = 0; j < indir_size / माप(*org_indir); j++)
				cur_indir[j] = i;
			ops->set_rss(h, cur_indir, शून्य, 0);

			क्रम (j = 0; j < fetch_num; j++) अणु
				/* alloc one skb and init */
				skb = hns_assemble_skb(ndev);
				अगर (!skb) अणु
					ret = -ENOMEM;
					जाओ out;
				पूर्ण
				rd = &tx_ring_data(priv, skb->queue_mapping);
				hns_nic_net_xmit_hw(ndev, skb, rd);

				retry_बार = 0;
				जबतक (retry_बार++ < 10) अणु
					mdelay(10);
					/* clean rx */
					rd = &rx_ring_data(priv, i);
					अगर (rd->poll_one(rd, fetch_num,
							 hns_nic_drop_rx_fetch))
						अवरोध;
				पूर्ण

				retry_बार = 0;
				जबतक (retry_बार++ < 10) अणु
					mdelay(10);
					/* clean tx ring 0 send package */
					rd = &tx_ring_data(priv,
							   HNS_LB_TX_RING);
					अगर (rd->poll_one(rd, fetch_num, शून्य))
						अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

out:
	/* restore everything */
	ops->set_rss(h, org_indir, शून्य, 0);
	hns_disable_serdes_lb(ndev);
enable_serdes_lb_err:
	kमुक्त(cur_indir);
cur_indir_alloc_err:
	kमुक्त(org_indir);

	वापस ret;
पूर्ण

अटल पूर्णांक hns_nic_change_mtu(काष्ठा net_device *ndev, पूर्णांक new_mtu)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hnae_handle *h = priv->ae_handle;
	bool अगर_running = netअगर_running(ndev);
	पूर्णांक ret;

	/* MTU < 68 is an error and causes problems on some kernels */
	अगर (new_mtu < 68)
		वापस -EINVAL;

	/* MTU no change */
	अगर (new_mtu == ndev->mtu)
		वापस 0;

	अगर (!h->dev->ops->set_mtu)
		वापस -ENOTSUPP;

	अगर (अगर_running) अणु
		(व्योम)hns_nic_net_stop(ndev);
		msleep(100);
	पूर्ण

	अगर (priv->enet_ver != AE_VERSION_1 &&
	    ndev->mtu <= BD_SIZE_2048_MAX_MTU &&
	    new_mtu > BD_SIZE_2048_MAX_MTU) अणु
		/* update desc */
		hnae_reinit_all_ring_desc(h);

		/* clear the package which the chip has fetched */
		ret = hns_nic_clear_all_rx_fetch(ndev);

		/* the page offset must be consist with desc */
		hnae_reinit_all_ring_page_off(h);

		अगर (ret) अणु
			netdev_err(ndev, "clear the fetched desc fail\n");
			जाओ out;
		पूर्ण
	पूर्ण

	ret = h->dev->ops->set_mtu(h, new_mtu);
	अगर (ret) अणु
		netdev_err(ndev, "set mtu fail, return value %d\n",
			   ret);
		जाओ out;
	पूर्ण

	/* finally, set new mtu to netdevice */
	ndev->mtu = new_mtu;

out:
	अगर (अगर_running) अणु
		अगर (hns_nic_net_खोलो(ndev)) अणु
			netdev_err(ndev, "hns net open fail\n");
			ret = -EINVAL;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hns_nic_set_features(काष्ठा net_device *netdev,
				netdev_features_t features)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(netdev);

	चयन (priv->enet_ver) अणु
	हाल AE_VERSION_1:
		अगर (features & (NETIF_F_TSO | NETIF_F_TSO6))
			netdev_info(netdev, "enet v1 do not support tso!\n");
		अवरोध;
	शेष:
		अगर (features & (NETIF_F_TSO | NETIF_F_TSO6)) अणु
			priv->ops.fill_desc = fill_tso_desc;
			priv->ops.maybe_stop_tx = hns_nic_maybe_stop_tso;
			/* The chip only support 7*4096 */
			netअगर_set_gso_max_size(netdev, 7 * 4096);
		पूर्ण अन्यथा अणु
			priv->ops.fill_desc = fill_v2_desc;
			priv->ops.maybe_stop_tx = hns_nic_maybe_stop_tx;
		पूर्ण
		अवरोध;
	पूर्ण
	netdev->features = features;
	वापस 0;
पूर्ण

अटल netdev_features_t hns_nic_fix_features(
		काष्ठा net_device *netdev, netdev_features_t features)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(netdev);

	चयन (priv->enet_ver) अणु
	हाल AE_VERSION_1:
		features &= ~(NETIF_F_TSO | NETIF_F_TSO6 |
				NETIF_F_HW_VLAN_CTAG_FILTER);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस features;
पूर्ण

अटल पूर्णांक hns_nic_uc_sync(काष्ठा net_device *netdev, स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae_handle *h = priv->ae_handle;

	अगर (h->dev->ops->add_uc_addr)
		वापस h->dev->ops->add_uc_addr(h, addr);

	वापस 0;
पूर्ण

अटल पूर्णांक hns_nic_uc_unsync(काष्ठा net_device *netdev,
			     स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae_handle *h = priv->ae_handle;

	अगर (h->dev->ops->rm_uc_addr)
		वापस h->dev->ops->rm_uc_addr(h, addr);

	वापस 0;
पूर्ण

/**
 * hns_set_multicast_list - set mutl mac address
 * @ndev: net device
 *
 * वापस व्योम
 */
अटल व्योम hns_set_multicast_list(काष्ठा net_device *ndev)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hnae_handle *h = priv->ae_handle;
	काष्ठा netdev_hw_addr *ha = शून्य;

	अगर (!h)	अणु
		netdev_err(ndev, "hnae handle is null\n");
		वापस;
	पूर्ण

	अगर (h->dev->ops->clr_mc_addr)
		अगर (h->dev->ops->clr_mc_addr(h))
			netdev_err(ndev, "clear multicast address fail\n");

	अगर (h->dev->ops->set_mc_addr) अणु
		netdev_क्रम_each_mc_addr(ha, ndev)
			अगर (h->dev->ops->set_mc_addr(h, ha->addr))
				netdev_err(ndev, "set multicast fail\n");
	पूर्ण
पूर्ण

अटल व्योम hns_nic_set_rx_mode(काष्ठा net_device *ndev)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hnae_handle *h = priv->ae_handle;

	अगर (h->dev->ops->set_promisc_mode) अणु
		अगर (ndev->flags & IFF_PROMISC)
			h->dev->ops->set_promisc_mode(h, 1);
		अन्यथा
			h->dev->ops->set_promisc_mode(h, 0);
	पूर्ण

	hns_set_multicast_list(ndev);

	अगर (__dev_uc_sync(ndev, hns_nic_uc_sync, hns_nic_uc_unsync))
		netdev_err(ndev, "sync uc address fail\n");
पूर्ण

अटल व्योम hns_nic_get_stats64(काष्ठा net_device *ndev,
				काष्ठा rtnl_link_stats64 *stats)
अणु
	पूर्णांक idx;
	u64 tx_bytes = 0;
	u64 rx_bytes = 0;
	u64 tx_pkts = 0;
	u64 rx_pkts = 0;
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hnae_handle *h = priv->ae_handle;

	क्रम (idx = 0; idx < h->q_num; idx++) अणु
		tx_bytes += h->qs[idx]->tx_ring.stats.tx_bytes;
		tx_pkts += h->qs[idx]->tx_ring.stats.tx_pkts;
		rx_bytes += h->qs[idx]->rx_ring.stats.rx_bytes;
		rx_pkts += h->qs[idx]->rx_ring.stats.rx_pkts;
	पूर्ण

	stats->tx_bytes = tx_bytes;
	stats->tx_packets = tx_pkts;
	stats->rx_bytes = rx_bytes;
	stats->rx_packets = rx_pkts;

	stats->rx_errors = ndev->stats.rx_errors;
	stats->multicast = ndev->stats.multicast;
	stats->rx_length_errors = ndev->stats.rx_length_errors;
	stats->rx_crc_errors = ndev->stats.rx_crc_errors;
	stats->rx_missed_errors = ndev->stats.rx_missed_errors;

	stats->tx_errors = ndev->stats.tx_errors;
	stats->rx_dropped = ndev->stats.rx_dropped;
	stats->tx_dropped = ndev->stats.tx_dropped;
	stats->collisions = ndev->stats.collisions;
	stats->rx_over_errors = ndev->stats.rx_over_errors;
	stats->rx_frame_errors = ndev->stats.rx_frame_errors;
	stats->rx_fअगरo_errors = ndev->stats.rx_fअगरo_errors;
	stats->tx_पातed_errors = ndev->stats.tx_पातed_errors;
	stats->tx_carrier_errors = ndev->stats.tx_carrier_errors;
	stats->tx_fअगरo_errors = ndev->stats.tx_fअगरo_errors;
	stats->tx_heartbeat_errors = ndev->stats.tx_heartbeat_errors;
	stats->tx_winकरोw_errors = ndev->stats.tx_winकरोw_errors;
	stats->rx_compressed = ndev->stats.rx_compressed;
	stats->tx_compressed = ndev->stats.tx_compressed;
पूर्ण

अटल u16
hns_nic_select_queue(काष्ठा net_device *ndev, काष्ठा sk_buff *skb,
		     काष्ठा net_device *sb_dev)
अणु
	काष्ठा ethhdr *eth_hdr = (काष्ठा ethhdr *)skb->data;
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);

	/* fix hardware broadcast/multicast packets queue loopback */
	अगर (!AE_IS_VER1(priv->enet_ver) &&
	    is_multicast_ether_addr(eth_hdr->h_dest))
		वापस 0;
	अन्यथा
		वापस netdev_pick_tx(ndev, skb, शून्य);
पूर्ण

अटल स्थिर काष्ठा net_device_ops hns_nic_netdev_ops = अणु
	.nकरो_खोलो = hns_nic_net_खोलो,
	.nकरो_stop = hns_nic_net_stop,
	.nकरो_start_xmit = hns_nic_net_xmit,
	.nकरो_tx_समयout = hns_nic_net_समयout,
	.nकरो_set_mac_address = hns_nic_net_set_mac_address,
	.nकरो_change_mtu = hns_nic_change_mtu,
	.nकरो_करो_ioctl = phy_करो_ioctl_running,
	.nकरो_set_features = hns_nic_set_features,
	.nकरो_fix_features = hns_nic_fix_features,
	.nकरो_get_stats64 = hns_nic_get_stats64,
	.nकरो_set_rx_mode = hns_nic_set_rx_mode,
	.nकरो_select_queue = hns_nic_select_queue,
पूर्ण;

अटल व्योम hns_nic_update_link_status(काष्ठा net_device *netdev)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(netdev);

	काष्ठा hnae_handle *h = priv->ae_handle;

	अगर (h->phy_dev) अणु
		अगर (h->phy_अगर != PHY_INTERFACE_MODE_XGMII)
			वापस;

		(व्योम)genphy_पढ़ो_status(h->phy_dev);
	पूर्ण
	hns_nic_adjust_link(netdev);
पूर्ण

/* क्रम dumping key regs*/
अटल व्योम hns_nic_dump(काष्ठा hns_nic_priv *priv)
अणु
	काष्ठा hnae_handle *h = priv->ae_handle;
	काष्ठा hnae_ae_ops *ops = h->dev->ops;
	u32 *data, reg_num, i;

	अगर (ops->get_regs_len && ops->get_regs) अणु
		reg_num = ops->get_regs_len(priv->ae_handle);
		reg_num = (reg_num + 3ul) & ~3ul;
		data = kसुस्मृति(reg_num, माप(u32), GFP_KERNEL);
		अगर (data) अणु
			ops->get_regs(priv->ae_handle, data);
			क्रम (i = 0; i < reg_num; i += 4)
				pr_info("0x%08x: 0x%08x 0x%08x 0x%08x 0x%08x\n",
					i, data[i], data[i + 1],
					data[i + 2], data[i + 3]);
			kमुक्त(data);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < h->q_num; i++) अणु
		pr_info("tx_queue%d_next_to_clean:%d\n",
			i, h->qs[i]->tx_ring.next_to_clean);
		pr_info("tx_queue%d_next_to_use:%d\n",
			i, h->qs[i]->tx_ring.next_to_use);
		pr_info("rx_queue%d_next_to_clean:%d\n",
			i, h->qs[i]->rx_ring.next_to_clean);
		pr_info("rx_queue%d_next_to_use:%d\n",
			i, h->qs[i]->rx_ring.next_to_use);
	पूर्ण
पूर्ण

/* क्रम resetting subtask */
अटल व्योम hns_nic_reset_subtask(काष्ठा hns_nic_priv *priv)
अणु
	क्रमागत hnae_port_type type = priv->ae_handle->port_type;

	अगर (!test_bit(NIC_STATE2_RESET_REQUESTED, &priv->state))
		वापस;
	clear_bit(NIC_STATE2_RESET_REQUESTED, &priv->state);

	/* If we're alपढ़ोy करोwn, removing or resetting, just bail */
	अगर (test_bit(NIC_STATE_DOWN, &priv->state) ||
	    test_bit(NIC_STATE_REMOVING, &priv->state) ||
	    test_bit(NIC_STATE_RESETTING, &priv->state))
		वापस;

	hns_nic_dump(priv);
	netdev_info(priv->netdev, "try to reset %s port!\n",
		    (type == HNAE_PORT_DEBUG ? "debug" : "service"));

	rtnl_lock();
	/* put off any impending NetWatchDogTimeout */
	netअगर_trans_update(priv->netdev);
	hns_nic_net_reinit(priv->netdev);

	rtnl_unlock();
पूर्ण

/* क्रम करोing service complete*/
अटल व्योम hns_nic_service_event_complete(काष्ठा hns_nic_priv *priv)
अणु
	WARN_ON(!test_bit(NIC_STATE_SERVICE_SCHED, &priv->state));
	/* make sure to commit the things */
	smp_mb__beक्रमe_atomic();
	clear_bit(NIC_STATE_SERVICE_SCHED, &priv->state);
पूर्ण

अटल व्योम hns_nic_service_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hns_nic_priv *priv
		= container_of(work, काष्ठा hns_nic_priv, service_task);
	काष्ठा hnae_handle *h = priv->ae_handle;

	hns_nic_reset_subtask(priv);
	hns_nic_update_link_status(priv->netdev);
	h->dev->ops->update_led_status(h);
	hns_nic_update_stats(priv->netdev);

	hns_nic_service_event_complete(priv);
पूर्ण

अटल व्योम hns_nic_task_schedule(काष्ठा hns_nic_priv *priv)
अणु
	अगर (!test_bit(NIC_STATE_DOWN, &priv->state) &&
	    !test_bit(NIC_STATE_REMOVING, &priv->state) &&
	    !test_and_set_bit(NIC_STATE_SERVICE_SCHED, &priv->state))
		(व्योम)schedule_work(&priv->service_task);
पूर्ण

अटल व्योम hns_nic_service_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा hns_nic_priv *priv = from_समयr(priv, t, service_समयr);

	(व्योम)mod_समयr(&priv->service_समयr, jअगरfies + SERVICE_TIMER_HZ);

	hns_nic_task_schedule(priv);
पूर्ण

/**
 * hns_tx_समयout_reset - initiate reset due to Tx समयout
 * @priv: driver निजी काष्ठा
 **/
अटल व्योम hns_tx_समयout_reset(काष्ठा hns_nic_priv *priv)
अणु
	/* Do the reset outside of पूर्णांकerrupt context */
	अगर (!test_bit(NIC_STATE_DOWN, &priv->state)) अणु
		set_bit(NIC_STATE2_RESET_REQUESTED, &priv->state);
		netdev_warn(priv->netdev,
			    "initiating reset due to tx timeout(%llu,0x%lx)\n",
			    priv->tx_समयout_count, priv->state);
		priv->tx_समयout_count++;
		hns_nic_task_schedule(priv);
	पूर्ण
पूर्ण

अटल पूर्णांक hns_nic_init_ring_data(काष्ठा hns_nic_priv *priv)
अणु
	काष्ठा hnae_handle *h = priv->ae_handle;
	काष्ठा hns_nic_ring_data *rd;
	bool is_ver1 = AE_IS_VER1(priv->enet_ver);
	पूर्णांक i;

	अगर (h->q_num > NIC_MAX_Q_PER_VF) अणु
		netdev_err(priv->netdev, "too much queue (%d)\n", h->q_num);
		वापस -EINVAL;
	पूर्ण

	priv->ring_data = kzalloc(array3_size(h->q_num,
					      माप(*priv->ring_data), 2),
				  GFP_KERNEL);
	अगर (!priv->ring_data)
		वापस -ENOMEM;

	क्रम (i = 0; i < h->q_num; i++) अणु
		rd = &priv->ring_data[i];
		rd->queue_index = i;
		rd->ring = &h->qs[i]->tx_ring;
		rd->poll_one = hns_nic_tx_poll_one;
		rd->fini_process = is_ver1 ? hns_nic_tx_fini_pro :
			hns_nic_tx_fini_pro_v2;

		netअगर_napi_add(priv->netdev, &rd->napi,
			       hns_nic_common_poll, NAPI_POLL_WEIGHT);
		rd->ring->irq_init_flag = RCB_IRQ_NOT_INITED;
	पूर्ण
	क्रम (i = h->q_num; i < h->q_num * 2; i++) अणु
		rd = &priv->ring_data[i];
		rd->queue_index = i - h->q_num;
		rd->ring = &h->qs[i - h->q_num]->rx_ring;
		rd->poll_one = hns_nic_rx_poll_one;
		rd->ex_process = hns_nic_rx_up_pro;
		rd->fini_process = is_ver1 ? hns_nic_rx_fini_pro :
			hns_nic_rx_fini_pro_v2;

		netअगर_napi_add(priv->netdev, &rd->napi,
			       hns_nic_common_poll, NAPI_POLL_WEIGHT);
		rd->ring->irq_init_flag = RCB_IRQ_NOT_INITED;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hns_nic_uninit_ring_data(काष्ठा hns_nic_priv *priv)
अणु
	काष्ठा hnae_handle *h = priv->ae_handle;
	पूर्णांक i;

	क्रम (i = 0; i < h->q_num * 2; i++) अणु
		netअगर_napi_del(&priv->ring_data[i].napi);
		अगर (priv->ring_data[i].ring->irq_init_flag == RCB_IRQ_INITED) अणु
			(व्योम)irq_set_affinity_hपूर्णांक(
				priv->ring_data[i].ring->irq,
				शून्य);
			मुक्त_irq(priv->ring_data[i].ring->irq,
				 &priv->ring_data[i]);
		पूर्ण

		priv->ring_data[i].ring->irq_init_flag = RCB_IRQ_NOT_INITED;
	पूर्ण
	kमुक्त(priv->ring_data);
पूर्ण

अटल व्योम hns_nic_set_priv_ops(काष्ठा net_device *netdev)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae_handle *h = priv->ae_handle;

	अगर (AE_IS_VER1(priv->enet_ver)) अणु
		priv->ops.fill_desc = fill_desc;
		priv->ops.get_rxd_bnum = get_rx_desc_bnum;
		priv->ops.maybe_stop_tx = hns_nic_maybe_stop_tx;
	पूर्ण अन्यथा अणु
		priv->ops.get_rxd_bnum = get_v2rx_desc_bnum;
		अगर ((netdev->features & NETIF_F_TSO) ||
		    (netdev->features & NETIF_F_TSO6)) अणु
			priv->ops.fill_desc = fill_tso_desc;
			priv->ops.maybe_stop_tx = hns_nic_maybe_stop_tso;
			/* This chip only support 7*4096 */
			netअगर_set_gso_max_size(netdev, 7 * 4096);
		पूर्ण अन्यथा अणु
			priv->ops.fill_desc = fill_v2_desc;
			priv->ops.maybe_stop_tx = hns_nic_maybe_stop_tx;
		पूर्ण
		/* enable tso when init
		 * control tso on/off through TSE bit in bd
		 */
		h->dev->ops->set_tso_stats(h, 1);
	पूर्ण
पूर्ण

अटल पूर्णांक hns_nic_try_get_ae(काष्ठा net_device *ndev)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hnae_handle *h;
	पूर्णांक ret;

	h = hnae_get_handle(&priv->netdev->dev,
			    priv->fwnode, priv->port_id, शून्य);
	अगर (IS_ERR_OR_शून्य(h)) अणु
		ret = -ENODEV;
		dev_dbg(priv->dev, "has not handle, register notifier!\n");
		जाओ out;
	पूर्ण
	priv->ae_handle = h;

	ret = hns_nic_init_phy(ndev, h);
	अगर (ret) अणु
		dev_err(priv->dev, "probe phy device fail!\n");
		जाओ out_init_phy;
	पूर्ण

	ret = hns_nic_init_ring_data(priv);
	अगर (ret) अणु
		ret = -ENOMEM;
		जाओ out_init_ring_data;
	पूर्ण

	hns_nic_set_priv_ops(ndev);

	ret = रेजिस्टर_netdev(ndev);
	अगर (ret) अणु
		dev_err(priv->dev, "probe register netdev fail!\n");
		जाओ out_reg_ndev_fail;
	पूर्ण
	वापस 0;

out_reg_ndev_fail:
	hns_nic_uninit_ring_data(priv);
	priv->ring_data = शून्य;
out_init_phy:
out_init_ring_data:
	hnae_put_handle(priv->ae_handle);
	priv->ae_handle = शून्य;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक hns_nic_notअगरier_action(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा hns_nic_priv *priv =
		container_of(nb, काष्ठा hns_nic_priv, notअगरier_block);

	निश्चित(action == HNAE_AE_REGISTER);

	अगर (!hns_nic_try_get_ae(priv->netdev)) अणु
		hnae_unरेजिस्टर_notअगरier(&priv->notअगरier_block);
		priv->notअगरier_block.notअगरier_call = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hns_nic_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा net_device *ndev;
	काष्ठा hns_nic_priv *priv;
	u32 port_id;
	पूर्णांक ret;

	ndev = alloc_etherdev_mq(माप(काष्ठा hns_nic_priv), NIC_MAX_Q_PER_VF);
	अगर (!ndev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ndev);

	priv = netdev_priv(ndev);
	priv->dev = dev;
	priv->netdev = ndev;

	अगर (dev_of_node(dev)) अणु
		काष्ठा device_node *ae_node;

		अगर (of_device_is_compatible(dev->of_node,
					    "hisilicon,hns-nic-v1"))
			priv->enet_ver = AE_VERSION_1;
		अन्यथा
			priv->enet_ver = AE_VERSION_2;

		ae_node = of_parse_phandle(dev->of_node, "ae-handle", 0);
		अगर (!ae_node) अणु
			ret = -ENODEV;
			dev_err(dev, "not find ae-handle\n");
			जाओ out_पढ़ो_prop_fail;
		पूर्ण
		priv->fwnode = &ae_node->fwnode;
	पूर्ण अन्यथा अगर (is_acpi_node(dev->fwnode)) अणु
		काष्ठा fwnode_reference_args args;

		अगर (acpi_dev_found(hns_enet_acpi_match[0].id))
			priv->enet_ver = AE_VERSION_1;
		अन्यथा अगर (acpi_dev_found(hns_enet_acpi_match[1].id))
			priv->enet_ver = AE_VERSION_2;
		अन्यथा अणु
			ret = -ENXIO;
			जाओ out_पढ़ो_prop_fail;
		पूर्ण

		/* try to find port-idx-in-ae first */
		ret = acpi_node_get_property_reference(dev->fwnode,
						       "ae-handle", 0, &args);
		अगर (ret) अणु
			dev_err(dev, "not find ae-handle\n");
			जाओ out_पढ़ो_prop_fail;
		पूर्ण
		अगर (!is_acpi_device_node(args.fwnode)) अणु
			ret = -EINVAL;
			जाओ out_पढ़ो_prop_fail;
		पूर्ण
		priv->fwnode = args.fwnode;
	पूर्ण अन्यथा अणु
		dev_err(dev, "cannot read cfg data from OF or acpi\n");
		ret = -ENXIO;
		जाओ out_पढ़ो_prop_fail;
	पूर्ण

	ret = device_property_पढ़ो_u32(dev, "port-idx-in-ae", &port_id);
	अगर (ret) अणु
		/* only क्रम old code compatible */
		ret = device_property_पढ़ो_u32(dev, "port-id", &port_id);
		अगर (ret)
			जाओ out_पढ़ो_prop_fail;
		/* क्रम old dts, we need to caculate the port offset */
		port_id = port_id < HNS_SRV_OFFSET ? port_id + HNS_DEBUG_OFFSET
			: port_id - HNS_SRV_OFFSET;
	पूर्ण
	priv->port_id = port_id;

	hns_init_mac_addr(ndev);

	ndev->watchकरोg_समयo = HNS_NIC_TX_TIMEOUT;
	ndev->priv_flags |= IFF_UNICAST_FLT;
	ndev->netdev_ops = &hns_nic_netdev_ops;
	hns_ethtool_set_ops(ndev);

	ndev->features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
		NETIF_F_RXCSUM | NETIF_F_SG | NETIF_F_GSO |
		NETIF_F_GRO;
	ndev->vlan_features |=
		NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM | NETIF_F_RXCSUM;
	ndev->vlan_features |= NETIF_F_SG | NETIF_F_GSO | NETIF_F_GRO;

	/* MTU range: 68 - 9578 (v1) or 9706 (v2) */
	ndev->min_mtu = MAC_MIN_MTU;
	चयन (priv->enet_ver) अणु
	हाल AE_VERSION_2:
		ndev->features |= NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_NTUPLE;
		ndev->hw_features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
			NETIF_F_RXCSUM | NETIF_F_SG | NETIF_F_GSO |
			NETIF_F_GRO | NETIF_F_TSO | NETIF_F_TSO6;
		ndev->vlan_features |= NETIF_F_TSO | NETIF_F_TSO6;
		ndev->max_mtu = MAC_MAX_MTU_V2 -
				(ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN);
		अवरोध;
	शेष:
		ndev->max_mtu = MAC_MAX_MTU -
				(ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN);
		अवरोध;
	पूर्ण

	SET_NETDEV_DEV(ndev, dev);

	अगर (!dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64)))
		dev_dbg(dev, "set mask to 64bit\n");
	अन्यथा
		dev_err(dev, "set mask to 64bit fail!\n");

	/* carrier off reporting is important to ethtool even BEFORE खोलो */
	netअगर_carrier_off(ndev);

	समयr_setup(&priv->service_समयr, hns_nic_service_समयr, 0);
	INIT_WORK(&priv->service_task, hns_nic_service_task);

	set_bit(NIC_STATE_SERVICE_INITED, &priv->state);
	clear_bit(NIC_STATE_SERVICE_SCHED, &priv->state);
	set_bit(NIC_STATE_DOWN, &priv->state);

	अगर (hns_nic_try_get_ae(priv->netdev)) अणु
		priv->notअगरier_block.notअगरier_call = hns_nic_notअगरier_action;
		ret = hnae_रेजिस्टर_notअगरier(&priv->notअगरier_block);
		अगर (ret) अणु
			dev_err(dev, "register notifier fail!\n");
			जाओ out_notअगरy_fail;
		पूर्ण
		dev_dbg(dev, "has not handle, register notifier!\n");
	पूर्ण

	वापस 0;

out_notअगरy_fail:
	(व्योम)cancel_work_sync(&priv->service_task);
out_पढ़ो_prop_fail:
	/* safe क्रम ACPI FW */
	of_node_put(to_of_node(priv->fwnode));
	मुक्त_netdev(ndev);
	वापस ret;
पूर्ण

अटल पूर्णांक hns_nic_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);

	अगर (ndev->reg_state != NETREG_UNINITIALIZED)
		unरेजिस्टर_netdev(ndev);

	अगर (priv->ring_data)
		hns_nic_uninit_ring_data(priv);
	priv->ring_data = शून्य;

	अगर (ndev->phydev)
		phy_disconnect(ndev->phydev);

	अगर (!IS_ERR_OR_शून्य(priv->ae_handle))
		hnae_put_handle(priv->ae_handle);
	priv->ae_handle = शून्य;
	अगर (priv->notअगरier_block.notअगरier_call)
		hnae_unरेजिस्टर_notअगरier(&priv->notअगरier_block);
	priv->notअगरier_block.notअगरier_call = शून्य;

	set_bit(NIC_STATE_REMOVING, &priv->state);
	(व्योम)cancel_work_sync(&priv->service_task);

	/* safe क्रम ACPI FW */
	of_node_put(to_of_node(priv->fwnode));

	मुक्त_netdev(ndev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id hns_enet_of_match[] = अणु
	अणु.compatible = "hisilicon,hns-nic-v1",पूर्ण,
	अणु.compatible = "hisilicon,hns-nic-v2",पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, hns_enet_of_match);

अटल काष्ठा platक्रमm_driver hns_nic_dev_driver = अणु
	.driver = अणु
		.name = "hns-nic",
		.of_match_table = hns_enet_of_match,
		.acpi_match_table = ACPI_PTR(hns_enet_acpi_match),
	पूर्ण,
	.probe = hns_nic_dev_probe,
	.हटाओ = hns_nic_dev_हटाओ,
पूर्ण;

module_platक्रमm_driver(hns_nic_dev_driver);

MODULE_DESCRIPTION("HISILICON HNS Ethernet driver");
MODULE_AUTHOR("Hisilicon, Inc.");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:hns-nic");
