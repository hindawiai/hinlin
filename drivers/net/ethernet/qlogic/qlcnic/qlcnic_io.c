<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic qlcnic NIC Driver
 * Copyright (c) 2009-2013 QLogic Corporation
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <net/checksum.h>
#समावेश <linux/prपूर्णांकk.h>

#समावेश "qlcnic.h"

#घोषणा QLCNIC_TX_ETHER_PKT		0x01
#घोषणा QLCNIC_TX_TCP_PKT		0x02
#घोषणा QLCNIC_TX_UDP_PKT		0x03
#घोषणा QLCNIC_TX_IP_PKT		0x04
#घोषणा QLCNIC_TX_TCP_LSO		0x05
#घोषणा QLCNIC_TX_TCP_LSO6		0x06
#घोषणा QLCNIC_TX_ENCAP_PKT		0x07
#घोषणा QLCNIC_TX_ENCAP_LSO		0x08
#घोषणा QLCNIC_TX_TCPV6_PKT		0x0b
#घोषणा QLCNIC_TX_UDPV6_PKT		0x0c

#घोषणा QLCNIC_FLAGS_VLAN_TAGGED	0x10
#घोषणा QLCNIC_FLAGS_VLAN_OOB		0x40

#घोषणा qlcnic_set_tx_vlan_tci(cmd_desc, v)	\
	(cmd_desc)->vlan_TCI = cpu_to_le16(v);
#घोषणा qlcnic_set_cmd_desc_port(cmd_desc, var)	\
	((cmd_desc)->port_ctxid |= ((var) & 0x0F))
#घोषणा qlcnic_set_cmd_desc_ctxid(cmd_desc, var)	\
	((cmd_desc)->port_ctxid |= ((var) << 4 & 0xF0))

#घोषणा qlcnic_set_tx_port(_desc, _port) \
	((_desc)->port_ctxid = ((_port) & 0xf) | (((_port) << 4) & 0xf0))

#घोषणा qlcnic_set_tx_flags_opcode(_desc, _flags, _opcode) \
	((_desc)->flags_opcode |= \
	cpu_to_le16(((_flags) & 0x7f) | (((_opcode) & 0x3f) << 7)))

#घोषणा qlcnic_set_tx_frags_len(_desc, _frags, _len) \
	((_desc)->nfrags__length = \
	cpu_to_le32(((_frags) & 0xff) | (((_len) & 0xffffff) << 8)))

/* owner bits of status_desc */
#घोषणा STATUS_OWNER_HOST	(0x1ULL << 56)
#घोषणा STATUS_OWNER_PHANTOM	(0x2ULL << 56)

/* Status descriptor:
   0-3 port, 4-7 status, 8-11 type, 12-27 total_length
   28-43 reference_handle, 44-47 protocol, 48-52 pkt_offset
   53-55 desc_cnt, 56-57 owner, 58-63 opcode
 */
#घोषणा qlcnic_get_sts_port(sts_data)	\
	((sts_data) & 0x0F)
#घोषणा qlcnic_get_sts_status(sts_data)	\
	(((sts_data) >> 4) & 0x0F)
#घोषणा qlcnic_get_sts_type(sts_data)	\
	(((sts_data) >> 8) & 0x0F)
#घोषणा qlcnic_get_sts_totallength(sts_data)	\
	(((sts_data) >> 12) & 0xFFFF)
#घोषणा qlcnic_get_sts_refhandle(sts_data)	\
	(((sts_data) >> 28) & 0xFFFF)
#घोषणा qlcnic_get_sts_prot(sts_data)	\
	(((sts_data) >> 44) & 0x0F)
#घोषणा qlcnic_get_sts_pkt_offset(sts_data)	\
	(((sts_data) >> 48) & 0x1F)
#घोषणा qlcnic_get_sts_desc_cnt(sts_data)	\
	(((sts_data) >> 53) & 0x7)
#घोषणा qlcnic_get_sts_opcode(sts_data)	\
	(((sts_data) >> 58) & 0x03F)

#घोषणा qlcnic_get_lro_sts_refhandle(sts_data) 	\
	((sts_data) & 0x07FFF)
#घोषणा qlcnic_get_lro_sts_length(sts_data)	\
	(((sts_data) >> 16) & 0x0FFFF)
#घोषणा qlcnic_get_lro_sts_l2_hdr_offset(sts_data)	\
	(((sts_data) >> 32) & 0x0FF)
#घोषणा qlcnic_get_lro_sts_l4_hdr_offset(sts_data)	\
	(((sts_data) >> 40) & 0x0FF)
#घोषणा qlcnic_get_lro_sts_बारtamp(sts_data)	\
	(((sts_data) >> 48) & 0x1)
#घोषणा qlcnic_get_lro_sts_type(sts_data)	\
	(((sts_data) >> 49) & 0x7)
#घोषणा qlcnic_get_lro_sts_push_flag(sts_data)		\
	(((sts_data) >> 52) & 0x1)
#घोषणा qlcnic_get_lro_sts_seq_number(sts_data)		\
	((sts_data) & 0x0FFFFFFFF)
#घोषणा qlcnic_get_lro_sts_mss(sts_data1)		\
	((sts_data1 >> 32) & 0x0FFFF)

#घोषणा qlcnic_83xx_get_lro_sts_mss(sts) ((sts) & 0xffff)

/* opcode field in status_desc */
#घोषणा QLCNIC_SYN_OFFLOAD	0x03
#घोषणा QLCNIC_RXPKT_DESC  	0x04
#घोषणा QLCNIC_OLD_RXPKT_DESC	0x3f
#घोषणा QLCNIC_RESPONSE_DESC	0x05
#घोषणा QLCNIC_LRO_DESC  	0x12

#घोषणा QLCNIC_TCP_HDR_SIZE		20
#घोषणा QLCNIC_TCP_TS_OPTION_SIZE	12
#घोषणा QLCNIC_FETCH_RING_ID(handle)	((handle) >> 63)
#घोषणा QLCNIC_DESC_OWNER_FW		cpu_to_le64(STATUS_OWNER_PHANTOM)

#घोषणा QLCNIC_TCP_TS_HDR_SIZE (QLCNIC_TCP_HDR_SIZE + QLCNIC_TCP_TS_OPTION_SIZE)

/* क्रम status field in status_desc */
#घोषणा STATUS_CKSUM_LOOP	0
#घोषणा STATUS_CKSUM_OK		2

#घोषणा qlcnic_83xx_pktln(sts)		((sts >> 32) & 0x3FFF)
#घोषणा qlcnic_83xx_hndl(sts)		((sts >> 48) & 0x7FFF)
#घोषणा qlcnic_83xx_csum_status(sts)	((sts >> 39) & 7)
#घोषणा qlcnic_83xx_opcode(sts)	((sts >> 42) & 0xF)
#घोषणा qlcnic_83xx_vlan_tag(sts)	(((sts) >> 48) & 0xFFFF)
#घोषणा qlcnic_83xx_lro_pktln(sts)	(((sts) >> 32) & 0x3FFF)
#घोषणा qlcnic_83xx_l2_hdr_off(sts)	(((sts) >> 16) & 0xFF)
#घोषणा qlcnic_83xx_l4_hdr_off(sts)	(((sts) >> 24) & 0xFF)
#घोषणा qlcnic_83xx_pkt_cnt(sts)	(((sts) >> 16) & 0x7)
#घोषणा qlcnic_83xx_is_tstamp(sts)	(((sts) >> 40) & 1)
#घोषणा qlcnic_83xx_is_psh_bit(sts)	(((sts) >> 41) & 1)
#घोषणा qlcnic_83xx_is_ip_align(sts)	(((sts) >> 46) & 1)
#घोषणा qlcnic_83xx_has_vlan_tag(sts)	(((sts) >> 47) & 1)

अटल पूर्णांक qlcnic_process_rcv_ring(काष्ठा qlcnic_host_sds_ring *sds_ring,
				   पूर्णांक max);

अटल काष्ठा sk_buff *qlcnic_process_rxbuf(काष्ठा qlcnic_adapter *,
					    काष्ठा qlcnic_host_rds_ring *,
					    u16, u16);

अटल अंतरभूत u8 qlcnic_mac_hash(u64 mac, u16 vlan)
अणु
	वापस (u8)((mac & 0xff) ^ ((mac >> 40) & 0xff) ^ (vlan & 0xff));
पूर्ण

अटल अंतरभूत u32 qlcnic_get_ref_handle(काष्ठा qlcnic_adapter *adapter,
					u16 handle, u8 ring_id)
अणु
	अगर (qlcnic_83xx_check(adapter))
		वापस handle | (ring_id << 15);
	अन्यथा
		वापस handle;
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_82xx_is_lb_pkt(u64 sts_data)
अणु
	वापस (qlcnic_get_sts_status(sts_data) == STATUS_CKSUM_LOOP) ? 1 : 0;
पूर्ण

अटल व्योम qlcnic_delete_rx_list_mac(काष्ठा qlcnic_adapter *adapter,
				      काष्ठा qlcnic_filter *fil,
				      व्योम *addr, u16 vlan_id)
अणु
	पूर्णांक ret;
	u8 op;

	op = vlan_id ? QLCNIC_MAC_VLAN_ADD : QLCNIC_MAC_ADD;
	ret = qlcnic_sre_macaddr_change(adapter, addr, vlan_id, op);
	अगर (ret)
		वापस;

	op = vlan_id ? QLCNIC_MAC_VLAN_DEL : QLCNIC_MAC_DEL;
	ret = qlcnic_sre_macaddr_change(adapter, addr, vlan_id, op);
	अगर (!ret) अणु
		hlist_del(&fil->fnode);
		adapter->rx_fhash.fnum--;
	पूर्ण
पूर्ण

अटल काष्ठा qlcnic_filter *qlcnic_find_mac_filter(काष्ठा hlist_head *head,
						    व्योम *addr, u16 vlan_id)
अणु
	काष्ठा qlcnic_filter *पंचांगp_fil = शून्य;
	काष्ठा hlist_node *n;

	hlist_क्रम_each_entry_safe(पंचांगp_fil, n, head, fnode) अणु
		अगर (ether_addr_equal(पंचांगp_fil->faddr, addr) &&
		    पंचांगp_fil->vlan_id == vlan_id)
			वापस पंचांगp_fil;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम qlcnic_add_lb_filter(काष्ठा qlcnic_adapter *adapter,
				 काष्ठा sk_buff *skb, पूर्णांक loopback_pkt, u16 vlan_id)
अणु
	काष्ठा ethhdr *phdr = (काष्ठा ethhdr *)(skb->data);
	काष्ठा qlcnic_filter *fil, *पंचांगp_fil;
	काष्ठा hlist_head *head;
	अचिन्हित दीर्घ समय;
	u64 src_addr = 0;
	u8 hindex, op;
	पूर्णांक ret;

	अगर (!qlcnic_sriov_pf_check(adapter) || (vlan_id == 0xffff))
		vlan_id = 0;

	स_नकल(&src_addr, phdr->h_source, ETH_ALEN);
	hindex = qlcnic_mac_hash(src_addr, vlan_id) &
		 (adapter->fhash.fbucket_size - 1);

	अगर (loopback_pkt) अणु
		अगर (adapter->rx_fhash.fnum >= adapter->rx_fhash.fmax)
			वापस;

		head = &(adapter->rx_fhash.fhead[hindex]);

		पंचांगp_fil = qlcnic_find_mac_filter(head, &src_addr, vlan_id);
		अगर (पंचांगp_fil) अणु
			समय = पंचांगp_fil->fसमय;
			अगर (समय_after(jअगरfies, QLCNIC_READD_AGE * HZ + समय))
				पंचांगp_fil->fसमय = jअगरfies;
			वापस;
		पूर्ण

		fil = kzalloc(माप(काष्ठा qlcnic_filter), GFP_ATOMIC);
		अगर (!fil)
			वापस;

		fil->fसमय = jअगरfies;
		स_नकल(fil->faddr, &src_addr, ETH_ALEN);
		fil->vlan_id = vlan_id;
		spin_lock(&adapter->rx_mac_learn_lock);
		hlist_add_head(&(fil->fnode), head);
		adapter->rx_fhash.fnum++;
		spin_unlock(&adapter->rx_mac_learn_lock);
	पूर्ण अन्यथा अणु
		head = &adapter->fhash.fhead[hindex];

		spin_lock(&adapter->mac_learn_lock);

		पंचांगp_fil = qlcnic_find_mac_filter(head, &src_addr, vlan_id);
		अगर (पंचांगp_fil) अणु
			op = vlan_id ? QLCNIC_MAC_VLAN_DEL : QLCNIC_MAC_DEL;
			ret = qlcnic_sre_macaddr_change(adapter,
							(u8 *)&src_addr,
							vlan_id, op);
			अगर (!ret) अणु
				hlist_del(&पंचांगp_fil->fnode);
				adapter->fhash.fnum--;
			पूर्ण

			spin_unlock(&adapter->mac_learn_lock);

			वापस;
		पूर्ण

		spin_unlock(&adapter->mac_learn_lock);

		head = &adapter->rx_fhash.fhead[hindex];

		spin_lock(&adapter->rx_mac_learn_lock);

		पंचांगp_fil = qlcnic_find_mac_filter(head, &src_addr, vlan_id);
		अगर (पंचांगp_fil)
			qlcnic_delete_rx_list_mac(adapter, पंचांगp_fil, &src_addr,
						  vlan_id);

		spin_unlock(&adapter->rx_mac_learn_lock);
	पूर्ण
पूर्ण

व्योम qlcnic_82xx_change_filter(काष्ठा qlcnic_adapter *adapter, u64 *uaddr,
			       u16 vlan_id, काष्ठा qlcnic_host_tx_ring *tx_ring)
अणु
	काष्ठा cmd_desc_type0 *hwdesc;
	काष्ठा qlcnic_nic_req *req;
	काष्ठा qlcnic_mac_req *mac_req;
	काष्ठा qlcnic_vlan_req *vlan_req;
	u32 producer;
	u64 word;

	producer = tx_ring->producer;
	hwdesc = &tx_ring->desc_head[tx_ring->producer];

	req = (काष्ठा qlcnic_nic_req *)hwdesc;
	स_रखो(req, 0, माप(काष्ठा qlcnic_nic_req));
	req->qhdr = cpu_to_le64(QLCNIC_REQUEST << 23);

	word = QLCNIC_MAC_EVENT | ((u64)(adapter->portnum) << 16);
	req->req_hdr = cpu_to_le64(word);

	mac_req = (काष्ठा qlcnic_mac_req *)&(req->words[0]);
	mac_req->op = vlan_id ? QLCNIC_MAC_VLAN_ADD : QLCNIC_MAC_ADD;
	स_नकल(mac_req->mac_addr, uaddr, ETH_ALEN);

	vlan_req = (काष्ठा qlcnic_vlan_req *)&req->words[1];
	vlan_req->vlan_id = cpu_to_le16(vlan_id);

	tx_ring->producer = get_next_index(producer, tx_ring->num_desc);
	smp_mb();
पूर्ण

अटल व्योम qlcnic_send_filter(काष्ठा qlcnic_adapter *adapter,
			       काष्ठा cmd_desc_type0 *first_desc,
			       काष्ठा sk_buff *skb,
			       काष्ठा qlcnic_host_tx_ring *tx_ring)
अणु
	काष्ठा vlan_ethhdr *vh = (काष्ठा vlan_ethhdr *)(skb->data);
	काष्ठा ethhdr *phdr = (काष्ठा ethhdr *)(skb->data);
	u16 protocol = ntohs(skb->protocol);
	काष्ठा qlcnic_filter *fil, *पंचांगp_fil;
	काष्ठा hlist_head *head;
	काष्ठा hlist_node *n;
	u64 src_addr = 0;
	u16 vlan_id = 0;
	u8 hindex, hval;

	अगर (ether_addr_equal(phdr->h_source, adapter->mac_addr))
		वापस;

	अगर (adapter->flags & QLCNIC_VLAN_FILTERING) अणु
		अगर (protocol == ETH_P_8021Q) अणु
			vh = (काष्ठा vlan_ethhdr *)skb->data;
			vlan_id = ntohs(vh->h_vlan_TCI);
		पूर्ण अन्यथा अगर (skb_vlan_tag_present(skb)) अणु
			vlan_id = skb_vlan_tag_get(skb);
		पूर्ण
	पूर्ण

	स_नकल(&src_addr, phdr->h_source, ETH_ALEN);
	hval = qlcnic_mac_hash(src_addr, vlan_id);
	hindex = hval & (adapter->fhash.fbucket_size - 1);
	head = &(adapter->fhash.fhead[hindex]);

	hlist_क्रम_each_entry_safe(पंचांगp_fil, n, head, fnode) अणु
		अगर (ether_addr_equal(पंचांगp_fil->faddr, (u8 *)&src_addr) &&
		    पंचांगp_fil->vlan_id == vlan_id) अणु
			अगर (jअगरfies > (QLCNIC_READD_AGE * HZ + पंचांगp_fil->fसमय))
				qlcnic_change_filter(adapter, &src_addr,
						     vlan_id, tx_ring);
			पंचांगp_fil->fसमय = jअगरfies;
			वापस;
		पूर्ण
	पूर्ण

	अगर (unlikely(adapter->fhash.fnum >= adapter->fhash.fmax)) अणु
		adapter->stats.mac_filter_limit_overrun++;
		वापस;
	पूर्ण

	fil = kzalloc(माप(काष्ठा qlcnic_filter), GFP_ATOMIC);
	अगर (!fil)
		वापस;

	qlcnic_change_filter(adapter, &src_addr, vlan_id, tx_ring);
	fil->fसमय = jअगरfies;
	fil->vlan_id = vlan_id;
	स_नकल(fil->faddr, &src_addr, ETH_ALEN);
	spin_lock(&adapter->mac_learn_lock);
	hlist_add_head(&(fil->fnode), head);
	adapter->fhash.fnum++;
	spin_unlock(&adapter->mac_learn_lock);
पूर्ण

#घोषणा QLCNIC_ENCAP_VXLAN_PKT		BIT_0
#घोषणा QLCNIC_ENCAP_OUTER_L3_IP6	BIT_1
#घोषणा QLCNIC_ENCAP_INNER_L3_IP6	BIT_2
#घोषणा QLCNIC_ENCAP_INNER_L4_UDP	BIT_3
#घोषणा QLCNIC_ENCAP_DO_L3_CSUM		BIT_4
#घोषणा QLCNIC_ENCAP_DO_L4_CSUM		BIT_5

अटल पूर्णांक qlcnic_tx_encap_pkt(काष्ठा qlcnic_adapter *adapter,
			       काष्ठा cmd_desc_type0 *first_desc,
			       काष्ठा sk_buff *skb,
			       काष्ठा qlcnic_host_tx_ring *tx_ring)
अणु
	u8 opcode = 0, inner_hdr_len = 0, outer_hdr_len = 0, total_hdr_len = 0;
	पूर्णांक copied, copy_len, descr_size;
	u32 producer = tx_ring->producer;
	काष्ठा cmd_desc_type0 *hwdesc;
	u16 flags = 0, encap_descr = 0;

	opcode = QLCNIC_TX_ETHER_PKT;
	encap_descr = QLCNIC_ENCAP_VXLAN_PKT;

	अगर (skb_is_gso(skb)) अणु
		inner_hdr_len = skb_inner_transport_header(skb) +
				inner_tcp_hdrlen(skb) -
				skb_inner_mac_header(skb);

		/* VXLAN header size = 8 */
		outer_hdr_len = skb_transport_offset(skb) + 8 +
				माप(काष्ठा udphdr);
		first_desc->outer_hdr_length = outer_hdr_len;
		total_hdr_len = inner_hdr_len + outer_hdr_len;
		encap_descr |= QLCNIC_ENCAP_DO_L3_CSUM |
			       QLCNIC_ENCAP_DO_L4_CSUM;
		first_desc->mss = cpu_to_le16(skb_shinfo(skb)->gso_size);
		first_desc->hdr_length = inner_hdr_len;

		/* Copy inner and outer headers in Tx descriptor(s)
		 * If total_hdr_len > cmd_desc_type0, use multiple
		 * descriptors
		 */
		copied = 0;
		descr_size = (पूर्णांक)माप(काष्ठा cmd_desc_type0);
		जबतक (copied < total_hdr_len) अणु
			copy_len = min(descr_size, (total_hdr_len - copied));
			hwdesc = &tx_ring->desc_head[producer];
			tx_ring->cmd_buf_arr[producer].skb = शून्य;
			skb_copy_from_linear_data_offset(skb, copied,
							 (अक्षर *)hwdesc,
							 copy_len);
			copied += copy_len;
			producer = get_next_index(producer, tx_ring->num_desc);
		पूर्ण

		tx_ring->producer = producer;

		/* Make sure updated tx_ring->producer is visible
		 * क्रम qlcnic_tx_avail()
		 */
		smp_mb();
		adapter->stats.encap_lso_frames++;

		opcode = QLCNIC_TX_ENCAP_LSO;
	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		अगर (inner_ip_hdr(skb)->version == 6) अणु
			अगर (inner_ipv6_hdr(skb)->nexthdr == IPPROTO_UDP)
				encap_descr |= QLCNIC_ENCAP_INNER_L4_UDP;
		पूर्ण अन्यथा अणु
			अगर (inner_ip_hdr(skb)->protocol == IPPROTO_UDP)
				encap_descr |= QLCNIC_ENCAP_INNER_L4_UDP;
		पूर्ण

		adapter->stats.encap_tx_csummed++;
		opcode = QLCNIC_TX_ENCAP_PKT;
	पूर्ण

	/* Prepare first 16 bits of byte offset 16 of Tx descriptor */
	अगर (ip_hdr(skb)->version == 6)
		encap_descr |= QLCNIC_ENCAP_OUTER_L3_IP6;

	/* outer IP header's size in 32bit words size*/
	encap_descr |= (skb_network_header_len(skb) >> 2) << 6;

	/* outer IP header offset */
	encap_descr |= skb_network_offset(skb) << 10;
	first_desc->encap_descr = cpu_to_le16(encap_descr);

	first_desc->tcp_hdr_offset = skb_inner_transport_header(skb) -
				     skb->data;
	first_desc->ip_hdr_offset = skb_inner_network_offset(skb);

	qlcnic_set_tx_flags_opcode(first_desc, flags, opcode);

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_tx_pkt(काष्ठा qlcnic_adapter *adapter,
			 काष्ठा cmd_desc_type0 *first_desc, काष्ठा sk_buff *skb,
			 काष्ठा qlcnic_host_tx_ring *tx_ring)
अणु
	u8 l4proto, opcode = 0, hdr_len = 0, tag_vlan = 0;
	u16 flags = 0, vlan_tci = 0;
	पूर्णांक copied, offset, copy_len, size;
	काष्ठा cmd_desc_type0 *hwdesc;
	काष्ठा vlan_ethhdr *vh;
	u16 protocol = ntohs(skb->protocol);
	u32 producer = tx_ring->producer;

	अगर (protocol == ETH_P_8021Q) अणु
		vh = (काष्ठा vlan_ethhdr *)skb->data;
		flags = QLCNIC_FLAGS_VLAN_TAGGED;
		vlan_tci = ntohs(vh->h_vlan_TCI);
		protocol = ntohs(vh->h_vlan_encapsulated_proto);
		tag_vlan = 1;
	पूर्ण अन्यथा अगर (skb_vlan_tag_present(skb)) अणु
		flags = QLCNIC_FLAGS_VLAN_OOB;
		vlan_tci = skb_vlan_tag_get(skb);
		tag_vlan = 1;
	पूर्ण
	अगर (unlikely(adapter->tx_pvid)) अणु
		अगर (tag_vlan && !(adapter->flags & QLCNIC_TAGGING_ENABLED))
			वापस -EIO;
		अगर (tag_vlan && (adapter->flags & QLCNIC_TAGGING_ENABLED))
			जाओ set_flags;

		flags = QLCNIC_FLAGS_VLAN_OOB;
		vlan_tci = adapter->tx_pvid;
	पूर्ण
set_flags:
	qlcnic_set_tx_vlan_tci(first_desc, vlan_tci);
	qlcnic_set_tx_flags_opcode(first_desc, flags, opcode);

	अगर (*(skb->data) & BIT_0) अणु
		flags |= BIT_0;
		स_नकल(&first_desc->eth_addr, skb->data, ETH_ALEN);
	पूर्ण
	opcode = QLCNIC_TX_ETHER_PKT;
	अगर (skb_is_gso(skb)) अणु
		hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
		first_desc->mss = cpu_to_le16(skb_shinfo(skb)->gso_size);
		first_desc->hdr_length = hdr_len;
		opcode = (protocol == ETH_P_IPV6) ? QLCNIC_TX_TCP_LSO6 :
						    QLCNIC_TX_TCP_LSO;

		/* For LSO, we need to copy the MAC/IP/TCP headers पूर्णांकo
		* the descriptor ring */
		copied = 0;
		offset = 2;

		अगर (flags & QLCNIC_FLAGS_VLAN_OOB) अणु
			first_desc->hdr_length += VLAN_HLEN;
			first_desc->tcp_hdr_offset = VLAN_HLEN;
			first_desc->ip_hdr_offset = VLAN_HLEN;

			/* Only in हाल of TSO on vlan device */
			flags |= QLCNIC_FLAGS_VLAN_TAGGED;

			/* Create a TSO vlan header ढाँचा क्रम firmware */
			hwdesc = &tx_ring->desc_head[producer];
			tx_ring->cmd_buf_arr[producer].skb = शून्य;

			copy_len = min((पूर्णांक)माप(काष्ठा cmd_desc_type0) -
				       offset, hdr_len + VLAN_HLEN);

			vh = (काष्ठा vlan_ethhdr *)((अक्षर *) hwdesc + 2);
			skb_copy_from_linear_data(skb, vh, 12);
			vh->h_vlan_proto = htons(ETH_P_8021Q);
			vh->h_vlan_TCI = htons(vlan_tci);

			skb_copy_from_linear_data_offset(skb, 12,
							 (अक्षर *)vh + 16,
							 copy_len - 16);
			copied = copy_len - VLAN_HLEN;
			offset = 0;
			producer = get_next_index(producer, tx_ring->num_desc);
		पूर्ण

		जबतक (copied < hdr_len) अणु
			size = (पूर्णांक)माप(काष्ठा cmd_desc_type0) - offset;
			copy_len = min(size, (hdr_len - copied));
			hwdesc = &tx_ring->desc_head[producer];
			tx_ring->cmd_buf_arr[producer].skb = शून्य;
			skb_copy_from_linear_data_offset(skb, copied,
							 (अक्षर *)hwdesc +
							 offset, copy_len);
			copied += copy_len;
			offset = 0;
			producer = get_next_index(producer, tx_ring->num_desc);
		पूर्ण

		tx_ring->producer = producer;
		smp_mb();
		adapter->stats.lso_frames++;

	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		अगर (protocol == ETH_P_IP) अणु
			l4proto = ip_hdr(skb)->protocol;

			अगर (l4proto == IPPROTO_TCP)
				opcode = QLCNIC_TX_TCP_PKT;
			अन्यथा अगर (l4proto == IPPROTO_UDP)
				opcode = QLCNIC_TX_UDP_PKT;
		पूर्ण अन्यथा अगर (protocol == ETH_P_IPV6) अणु
			l4proto = ipv6_hdr(skb)->nexthdr;

			अगर (l4proto == IPPROTO_TCP)
				opcode = QLCNIC_TX_TCPV6_PKT;
			अन्यथा अगर (l4proto == IPPROTO_UDP)
				opcode = QLCNIC_TX_UDPV6_PKT;
		पूर्ण
	पूर्ण
	first_desc->tcp_hdr_offset += skb_transport_offset(skb);
	first_desc->ip_hdr_offset += skb_network_offset(skb);
	qlcnic_set_tx_flags_opcode(first_desc, flags, opcode);

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_map_tx_skb(काष्ठा pci_dev *pdev, काष्ठा sk_buff *skb,
			     काष्ठा qlcnic_cmd_buffer *pbuf)
अणु
	काष्ठा qlcnic_skb_frag *nf;
	skb_frag_t *frag;
	पूर्णांक i, nr_frags;
	dma_addr_t map;

	nr_frags = skb_shinfo(skb)->nr_frags;
	nf = &pbuf->frag_array[0];

	map = pci_map_single(pdev, skb->data, skb_headlen(skb),
			     PCI_DMA_TODEVICE);
	अगर (pci_dma_mapping_error(pdev, map))
		जाओ out_err;

	nf->dma = map;
	nf->length = skb_headlen(skb);

	क्रम (i = 0; i < nr_frags; i++) अणु
		frag = &skb_shinfo(skb)->frags[i];
		nf = &pbuf->frag_array[i+1];
		map = skb_frag_dma_map(&pdev->dev, frag, 0, skb_frag_size(frag),
				       DMA_TO_DEVICE);
		अगर (dma_mapping_error(&pdev->dev, map))
			जाओ unwind;

		nf->dma = map;
		nf->length = skb_frag_size(frag);
	पूर्ण

	वापस 0;

unwind:
	जबतक (--i >= 0) अणु
		nf = &pbuf->frag_array[i+1];
		pci_unmap_page(pdev, nf->dma, nf->length, PCI_DMA_TODEVICE);
	पूर्ण

	nf = &pbuf->frag_array[0];
	pci_unmap_single(pdev, nf->dma, skb_headlen(skb), PCI_DMA_TODEVICE);

out_err:
	वापस -ENOMEM;
पूर्ण

अटल व्योम qlcnic_unmap_buffers(काष्ठा pci_dev *pdev, काष्ठा sk_buff *skb,
				 काष्ठा qlcnic_cmd_buffer *pbuf)
अणु
	काष्ठा qlcnic_skb_frag *nf = &pbuf->frag_array[0];
	पूर्णांक i, nr_frags = skb_shinfo(skb)->nr_frags;

	क्रम (i = 0; i < nr_frags; i++) अणु
		nf = &pbuf->frag_array[i+1];
		pci_unmap_page(pdev, nf->dma, nf->length, PCI_DMA_TODEVICE);
	पूर्ण

	nf = &pbuf->frag_array[0];
	pci_unmap_single(pdev, nf->dma, skb_headlen(skb), PCI_DMA_TODEVICE);
	pbuf->skb = शून्य;
पूर्ण

अटल अंतरभूत व्योम qlcnic_clear_cmddesc(u64 *desc)
अणु
	desc[0] = 0ULL;
	desc[2] = 0ULL;
	desc[7] = 0ULL;
पूर्ण

netdev_tx_t qlcnic_xmit_frame(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_host_tx_ring *tx_ring;
	काष्ठा qlcnic_cmd_buffer *pbuf;
	काष्ठा qlcnic_skb_frag *buffrag;
	काष्ठा cmd_desc_type0 *hwdesc, *first_desc;
	काष्ठा pci_dev *pdev;
	काष्ठा ethhdr *phdr;
	पूर्णांक i, k, frag_count, delta = 0;
	u32 producer, num_txd;
	u16 protocol;
	bool l4_is_udp = false;

	अगर (!test_bit(__QLCNIC_DEV_UP, &adapter->state)) अणु
		netअगर_tx_stop_all_queues(netdev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (adapter->flags & QLCNIC_MACSPOOF) अणु
		phdr = (काष्ठा ethhdr *)skb->data;
		अगर (!ether_addr_equal(phdr->h_source, adapter->mac_addr))
			जाओ drop_packet;
	पूर्ण

	tx_ring = &adapter->tx_ring[skb_get_queue_mapping(skb)];
	num_txd = tx_ring->num_desc;

	frag_count = skb_shinfo(skb)->nr_frags + 1;

	/* 14 frags supported क्रम normal packet and
	 * 32 frags supported क्रम TSO packet
	 */
	अगर (!skb_is_gso(skb) && frag_count > QLCNIC_MAX_FRAGS_PER_TX) अणु
		क्रम (i = 0; i < (frag_count - QLCNIC_MAX_FRAGS_PER_TX); i++)
			delta += skb_frag_size(&skb_shinfo(skb)->frags[i]);

		अगर (!__pskb_pull_tail(skb, delta))
			जाओ drop_packet;

		frag_count = 1 + skb_shinfo(skb)->nr_frags;
	पूर्ण

	अगर (unlikely(qlcnic_tx_avail(tx_ring) <= TX_STOP_THRESH)) अणु
		netअगर_tx_stop_queue(tx_ring->txq);
		अगर (qlcnic_tx_avail(tx_ring) > TX_STOP_THRESH) अणु
			netअगर_tx_start_queue(tx_ring->txq);
		पूर्ण अन्यथा अणु
			tx_ring->tx_stats.xmit_off++;
			वापस NETDEV_TX_BUSY;
		पूर्ण
	पूर्ण

	producer = tx_ring->producer;
	pbuf = &tx_ring->cmd_buf_arr[producer];
	pdev = adapter->pdev;
	first_desc = &tx_ring->desc_head[producer];
	hwdesc = &tx_ring->desc_head[producer];
	qlcnic_clear_cmddesc((u64 *)hwdesc);

	अगर (qlcnic_map_tx_skb(pdev, skb, pbuf)) अणु
		adapter->stats.tx_dma_map_error++;
		जाओ drop_packet;
	पूर्ण

	pbuf->skb = skb;
	pbuf->frag_count = frag_count;

	qlcnic_set_tx_frags_len(first_desc, frag_count, skb->len);
	qlcnic_set_tx_port(first_desc, adapter->portnum);

	क्रम (i = 0; i < frag_count; i++) अणु
		k = i % 4;

		अगर ((k == 0) && (i > 0)) अणु
			/* move to next desc.*/
			producer = get_next_index(producer, num_txd);
			hwdesc = &tx_ring->desc_head[producer];
			qlcnic_clear_cmddesc((u64 *)hwdesc);
			tx_ring->cmd_buf_arr[producer].skb = शून्य;
		पूर्ण

		buffrag = &pbuf->frag_array[i];
		hwdesc->buffer_length[k] = cpu_to_le16(buffrag->length);
		चयन (k) अणु
		हाल 0:
			hwdesc->addr_buffer1 = cpu_to_le64(buffrag->dma);
			अवरोध;
		हाल 1:
			hwdesc->addr_buffer2 = cpu_to_le64(buffrag->dma);
			अवरोध;
		हाल 2:
			hwdesc->addr_buffer3 = cpu_to_le64(buffrag->dma);
			अवरोध;
		हाल 3:
			hwdesc->addr_buffer4 = cpu_to_le64(buffrag->dma);
			अवरोध;
		पूर्ण
	पूर्ण

	tx_ring->producer = get_next_index(producer, num_txd);
	smp_mb();

	protocol = ntohs(skb->protocol);
	अगर (protocol == ETH_P_IP)
		l4_is_udp = ip_hdr(skb)->protocol == IPPROTO_UDP;
	अन्यथा अगर (protocol == ETH_P_IPV6)
		l4_is_udp = ipv6_hdr(skb)->nexthdr == IPPROTO_UDP;

	/* Check अगर it is a VXLAN packet */
	अगर (!skb->encapsulation || !l4_is_udp ||
	    !qlcnic_encap_tx_offload(adapter)) अणु
		अगर (unlikely(qlcnic_tx_pkt(adapter, first_desc, skb,
					   tx_ring)))
			जाओ unwind_buff;
	पूर्ण अन्यथा अणु
		अगर (unlikely(qlcnic_tx_encap_pkt(adapter, first_desc,
						 skb, tx_ring)))
			जाओ unwind_buff;
	पूर्ण

	अगर (adapter->drv_mac_learn)
		qlcnic_send_filter(adapter, first_desc, skb, tx_ring);

	tx_ring->tx_stats.tx_bytes += skb->len;
	tx_ring->tx_stats.xmit_called++;

	/* Ensure ग_लिखोs are complete beक्रमe HW fetches Tx descriptors */
	wmb();
	qlcnic_update_cmd_producer(tx_ring);

	वापस NETDEV_TX_OK;

unwind_buff:
	qlcnic_unmap_buffers(pdev, skb, pbuf);
drop_packet:
	adapter->stats.txdropped++;
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

व्योम qlcnic_advert_link_change(काष्ठा qlcnic_adapter *adapter, पूर्णांक linkup)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	अगर (adapter->ahw->linkup && !linkup) अणु
		netdev_info(netdev, "NIC Link is down\n");
		adapter->ahw->linkup = 0;
		netअगर_carrier_off(netdev);
	पूर्ण अन्यथा अगर (!adapter->ahw->linkup && linkup) अणु
		adapter->ahw->linkup = 1;

		/* Do not advertise Link up to the stack अगर device
		 * is in loopback mode
		 */
		अगर (qlcnic_83xx_check(adapter) && adapter->ahw->lb_mode) अणु
			netdev_info(netdev, "NIC Link is up for loopback test\n");
			वापस;
		पूर्ण

		netdev_info(netdev, "NIC Link is up\n");
		netअगर_carrier_on(netdev);
	पूर्ण
पूर्ण

अटल पूर्णांक qlcnic_alloc_rx_skb(काष्ठा qlcnic_adapter *adapter,
			       काष्ठा qlcnic_host_rds_ring *rds_ring,
			       काष्ठा qlcnic_rx_buffer *buffer)
अणु
	काष्ठा sk_buff *skb;
	dma_addr_t dma;
	काष्ठा pci_dev *pdev = adapter->pdev;

	skb = netdev_alloc_skb(adapter->netdev, rds_ring->skb_size);
	अगर (!skb) अणु
		adapter->stats.skb_alloc_failure++;
		वापस -ENOMEM;
	पूर्ण

	skb_reserve(skb, NET_IP_ALIGN);
	dma = pci_map_single(pdev, skb->data,
			     rds_ring->dma_size, PCI_DMA_FROMDEVICE);

	अगर (pci_dma_mapping_error(pdev, dma)) अणु
		adapter->stats.rx_dma_map_error++;
		dev_kमुक्त_skb_any(skb);
		वापस -ENOMEM;
	पूर्ण

	buffer->skb = skb;
	buffer->dma = dma;

	वापस 0;
पूर्ण

अटल व्योम qlcnic_post_rx_buffers_nodb(काष्ठा qlcnic_adapter *adapter,
					काष्ठा qlcnic_host_rds_ring *rds_ring,
					u8 ring_id)
अणु
	काष्ठा rcv_desc *pdesc;
	काष्ठा qlcnic_rx_buffer *buffer;
	पूर्णांक  count = 0;
	uपूर्णांक32_t producer, handle;
	काष्ठा list_head *head;

	अगर (!spin_trylock(&rds_ring->lock))
		वापस;

	producer = rds_ring->producer;
	head = &rds_ring->मुक्त_list;
	जबतक (!list_empty(head)) अणु
		buffer = list_entry(head->next, काष्ठा qlcnic_rx_buffer, list);

		अगर (!buffer->skb) अणु
			अगर (qlcnic_alloc_rx_skb(adapter, rds_ring, buffer))
				अवरोध;
		पूर्ण
		count++;
		list_del(&buffer->list);

		/* make a rcv descriptor  */
		pdesc = &rds_ring->desc_head[producer];
		handle = qlcnic_get_ref_handle(adapter,
					       buffer->ref_handle, ring_id);
		pdesc->reference_handle = cpu_to_le16(handle);
		pdesc->buffer_length = cpu_to_le32(rds_ring->dma_size);
		pdesc->addr_buffer = cpu_to_le64(buffer->dma);
		producer = get_next_index(producer, rds_ring->num_desc);
	पूर्ण
	अगर (count) अणु
		rds_ring->producer = producer;
		ग_लिखोl((producer - 1) & (rds_ring->num_desc - 1),
		       rds_ring->crb_rcv_producer);
	पूर्ण
	spin_unlock(&rds_ring->lock);
पूर्ण

अटल पूर्णांक qlcnic_process_cmd_ring(काष्ठा qlcnic_adapter *adapter,
				   काष्ठा qlcnic_host_tx_ring *tx_ring,
				   पूर्णांक budget)
अणु
	u32 sw_consumer, hw_consumer;
	पूर्णांक i, करोne, count = 0;
	काष्ठा qlcnic_cmd_buffer *buffer;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा qlcnic_skb_frag *frag;

	अगर (!spin_trylock(&tx_ring->tx_clean_lock))
		वापस 1;

	sw_consumer = tx_ring->sw_consumer;
	hw_consumer = le32_to_cpu(*(tx_ring->hw_consumer));

	जबतक (sw_consumer != hw_consumer) अणु
		buffer = &tx_ring->cmd_buf_arr[sw_consumer];
		अगर (buffer->skb) अणु
			frag = &buffer->frag_array[0];
			pci_unmap_single(pdev, frag->dma, frag->length,
					 PCI_DMA_TODEVICE);
			frag->dma = 0ULL;
			क्रम (i = 1; i < buffer->frag_count; i++) अणु
				frag++;
				pci_unmap_page(pdev, frag->dma, frag->length,
					       PCI_DMA_TODEVICE);
				frag->dma = 0ULL;
			पूर्ण
			tx_ring->tx_stats.xmit_finished++;
			dev_kमुक्त_skb_any(buffer->skb);
			buffer->skb = शून्य;
		पूर्ण

		sw_consumer = get_next_index(sw_consumer, tx_ring->num_desc);
		अगर (++count >= budget)
			अवरोध;
	पूर्ण

	tx_ring->sw_consumer = sw_consumer;

	अगर (count && netअगर_running(netdev)) अणु
		smp_mb();
		अगर (netअगर_tx_queue_stopped(tx_ring->txq) &&
		    netअगर_carrier_ok(netdev)) अणु
			अगर (qlcnic_tx_avail(tx_ring) > TX_STOP_THRESH) अणु
				netअगर_tx_wake_queue(tx_ring->txq);
				tx_ring->tx_stats.xmit_on++;
			पूर्ण
		पूर्ण
		adapter->tx_समयo_cnt = 0;
	पूर्ण
	/*
	 * If everything is मुक्तd up to consumer then check अगर the ring is full
	 * If the ring is full then check अगर more needs to be मुक्तd and
	 * schedule the call back again.
	 *
	 * This happens when there are 2 CPUs. One could be मुक्तing and the
	 * other filling it. If the ring is full when we get out of here and
	 * the card has alपढ़ोy पूर्णांकerrupted the host then the host can miss the
	 * पूर्णांकerrupt.
	 *
	 * There is still a possible race condition and the host could miss an
	 * पूर्णांकerrupt. The card has to take care of this.
	 */
	hw_consumer = le32_to_cpu(*(tx_ring->hw_consumer));
	करोne = (sw_consumer == hw_consumer);

	spin_unlock(&tx_ring->tx_clean_lock);

	वापस करोne;
पूर्ण

अटल पूर्णांक qlcnic_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	पूर्णांक tx_complete, work_करोne;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_adapter *adapter;
	काष्ठा qlcnic_host_tx_ring *tx_ring;

	sds_ring = container_of(napi, काष्ठा qlcnic_host_sds_ring, napi);
	adapter = sds_ring->adapter;
	tx_ring = sds_ring->tx_ring;

	tx_complete = qlcnic_process_cmd_ring(adapter, tx_ring,
					      budget);
	work_करोne = qlcnic_process_rcv_ring(sds_ring, budget);

	/* Check अगर we need a repoll */
	अगर (!tx_complete)
		work_करोne = budget;

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(&sds_ring->napi, work_करोne);
		अगर (test_bit(__QLCNIC_DEV_UP, &adapter->state)) अणु
			qlcnic_enable_sds_पूर्णांकr(adapter, sds_ring);
			qlcnic_enable_tx_पूर्णांकr(adapter, tx_ring);
		पूर्ण
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल पूर्णांक qlcnic_tx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा qlcnic_host_tx_ring *tx_ring;
	काष्ठा qlcnic_adapter *adapter;
	पूर्णांक work_करोne;

	tx_ring = container_of(napi, काष्ठा qlcnic_host_tx_ring, napi);
	adapter = tx_ring->adapter;

	work_करोne = qlcnic_process_cmd_ring(adapter, tx_ring, budget);
	अगर (work_करोne) अणु
		napi_complete(&tx_ring->napi);
		अगर (test_bit(__QLCNIC_DEV_UP, &adapter->state))
			qlcnic_enable_tx_पूर्णांकr(adapter, tx_ring);
	पूर्ण अन्यथा अणु
		/* As qlcnic_process_cmd_ring() वापसed 0, we need a repoll*/
		work_करोne = budget;
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल पूर्णांक qlcnic_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_adapter *adapter;
	पूर्णांक work_करोne;

	sds_ring = container_of(napi, काष्ठा qlcnic_host_sds_ring, napi);
	adapter = sds_ring->adapter;

	work_करोne = qlcnic_process_rcv_ring(sds_ring, budget);

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(&sds_ring->napi, work_करोne);
		अगर (test_bit(__QLCNIC_DEV_UP, &adapter->state))
			qlcnic_enable_sds_पूर्णांकr(adapter, sds_ring);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल व्योम qlcnic_handle_linkevent(काष्ठा qlcnic_adapter *adapter,
				    काष्ठा qlcnic_fw_msg *msg)
अणु
	u32 cable_OUI;
	u16 cable_len, link_speed;
	u8  link_status, module, duplex, स्वतःneg, lb_status = 0;
	काष्ठा net_device *netdev = adapter->netdev;

	adapter->ahw->has_link_events = 1;

	cable_OUI = msg->body[1] & 0xffffffff;
	cable_len = (msg->body[1] >> 32) & 0xffff;
	link_speed = (msg->body[1] >> 48) & 0xffff;

	link_status = msg->body[2] & 0xff;
	duplex = (msg->body[2] >> 16) & 0xff;
	स्वतःneg = (msg->body[2] >> 24) & 0xff;
	lb_status = (msg->body[2] >> 32) & 0x3;

	module = (msg->body[2] >> 8) & 0xff;
	अगर (module == LINKEVENT_MODULE_TWINAX_UNSUPPORTED_CABLE)
		dev_info(&netdev->dev,
			 "unsupported cable: OUI 0x%x, length %d\n",
			 cable_OUI, cable_len);
	अन्यथा अगर (module == LINKEVENT_MODULE_TWINAX_UNSUPPORTED_CABLELEN)
		dev_info(&netdev->dev, "unsupported cable length %d\n",
			 cable_len);

	अगर (!link_status && (lb_status == QLCNIC_ILB_MODE ||
	    lb_status == QLCNIC_ELB_MODE))
		adapter->ahw->loopback_state |= QLCNIC_LINKEVENT;

	qlcnic_advert_link_change(adapter, link_status);

	अगर (duplex == LINKEVENT_FULL_DUPLEX)
		adapter->ahw->link_duplex = DUPLEX_FULL;
	अन्यथा
		adapter->ahw->link_duplex = DUPLEX_HALF;

	adapter->ahw->module_type = module;
	adapter->ahw->link_स्वतःneg = स्वतःneg;

	अगर (link_status) अणु
		adapter->ahw->link_speed = link_speed;
	पूर्ण अन्यथा अणु
		adapter->ahw->link_speed = SPEED_UNKNOWN;
		adapter->ahw->link_duplex = DUPLEX_UNKNOWN;
	पूर्ण
पूर्ण

अटल व्योम qlcnic_handle_fw_message(पूर्णांक desc_cnt, पूर्णांक index,
				     काष्ठा qlcnic_host_sds_ring *sds_ring)
अणु
	काष्ठा qlcnic_fw_msg msg;
	काष्ठा status_desc *desc;
	काष्ठा qlcnic_adapter *adapter;
	काष्ठा device *dev;
	पूर्णांक i = 0, opcode, ret;

	जबतक (desc_cnt > 0 && i < 8) अणु
		desc = &sds_ring->desc_head[index];
		msg.words[i++] = le64_to_cpu(desc->status_desc_data[0]);
		msg.words[i++] = le64_to_cpu(desc->status_desc_data[1]);

		index = get_next_index(index, sds_ring->num_desc);
		desc_cnt--;
	पूर्ण

	adapter = sds_ring->adapter;
	dev = &adapter->pdev->dev;
	opcode = qlcnic_get_nic_msg_opcode(msg.body[0]);

	चयन (opcode) अणु
	हाल QLCNIC_C2H_OPCODE_GET_LINKEVENT_RESPONSE:
		qlcnic_handle_linkevent(adapter, &msg);
		अवरोध;
	हाल QLCNIC_C2H_OPCODE_CONFIG_LOOPBACK:
		ret = (u32)(msg.body[1]);
		चयन (ret) अणु
		हाल 0:
			adapter->ahw->loopback_state |= QLCNIC_LB_RESPONSE;
			अवरोध;
		हाल 1:
			dev_info(dev, "loopback already in progress\n");
			adapter->ahw->diag_cnt = -EINPROGRESS;
			अवरोध;
		हाल 2:
			dev_info(dev, "loopback cable is not connected\n");
			adapter->ahw->diag_cnt = -ENODEV;
			अवरोध;
		शेष:
			dev_info(dev,
				 "loopback configure request failed, err %x\n",
				 ret);
			adapter->ahw->diag_cnt = -EIO;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल QLCNIC_C2H_OPCODE_GET_DCB_AEN:
		qlcnic_dcb_aen_handler(adapter->dcb, (व्योम *)&msg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *qlcnic_process_rxbuf(काष्ठा qlcnic_adapter *adapter,
					    काष्ठा qlcnic_host_rds_ring *ring,
					    u16 index, u16 cksum)
अणु
	काष्ठा qlcnic_rx_buffer *buffer;
	काष्ठा sk_buff *skb;

	buffer = &ring->rx_buf_arr[index];
	अगर (unlikely(buffer->skb == शून्य)) अणु
		WARN_ON(1);
		वापस शून्य;
	पूर्ण

	pci_unmap_single(adapter->pdev, buffer->dma, ring->dma_size,
			 PCI_DMA_FROMDEVICE);

	skb = buffer->skb;
	अगर (likely((adapter->netdev->features & NETIF_F_RXCSUM) &&
		   (cksum == STATUS_CKSUM_OK || cksum == STATUS_CKSUM_LOOP))) अणु
		adapter->stats.csummed++;
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण अन्यथा अणु
		skb_checksum_none_निश्चित(skb);
	पूर्ण


	buffer->skb = शून्य;

	वापस skb;
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_check_rx_tagging(काष्ठा qlcnic_adapter *adapter,
					  काष्ठा sk_buff *skb, u16 *vlan_tag)
अणु
	काष्ठा ethhdr *eth_hdr;

	अगर (!__vlan_get_tag(skb, vlan_tag)) अणु
		eth_hdr = (काष्ठा ethhdr *)skb->data;
		स_हटाओ(skb->data + VLAN_HLEN, eth_hdr, ETH_ALEN * 2);
		skb_pull(skb, VLAN_HLEN);
	पूर्ण
	अगर (!adapter->rx_pvid)
		वापस 0;

	अगर (*vlan_tag == adapter->rx_pvid) अणु
		/* Outer vlan tag. Packet should follow non-vlan path */
		*vlan_tag = 0xffff;
		वापस 0;
	पूर्ण
	अगर (adapter->flags & QLCNIC_TAGGING_ENABLED)
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल काष्ठा qlcnic_rx_buffer *
qlcnic_process_rcv(काष्ठा qlcnic_adapter *adapter,
		   काष्ठा qlcnic_host_sds_ring *sds_ring, पूर्णांक ring,
		   u64 sts_data0)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	काष्ठा qlcnic_rx_buffer *buffer;
	काष्ठा sk_buff *skb;
	काष्ठा qlcnic_host_rds_ring *rds_ring;
	पूर्णांक index, length, cksum, pkt_offset, is_lb_pkt;
	u16 vid = 0xffff, t_vid;

	अगर (unlikely(ring >= adapter->max_rds_rings))
		वापस शून्य;

	rds_ring = &recv_ctx->rds_rings[ring];

	index = qlcnic_get_sts_refhandle(sts_data0);
	अगर (unlikely(index >= rds_ring->num_desc))
		वापस शून्य;

	buffer = &rds_ring->rx_buf_arr[index];
	length = qlcnic_get_sts_totallength(sts_data0);
	cksum  = qlcnic_get_sts_status(sts_data0);
	pkt_offset = qlcnic_get_sts_pkt_offset(sts_data0);

	skb = qlcnic_process_rxbuf(adapter, rds_ring, index, cksum);
	अगर (!skb)
		वापस buffer;

	अगर (adapter->rx_mac_learn) अणु
		t_vid = 0;
		is_lb_pkt = qlcnic_82xx_is_lb_pkt(sts_data0);
		qlcnic_add_lb_filter(adapter, skb, is_lb_pkt, t_vid);
	पूर्ण

	अगर (length > rds_ring->skb_size)
		skb_put(skb, rds_ring->skb_size);
	अन्यथा
		skb_put(skb, length);

	अगर (pkt_offset)
		skb_pull(skb, pkt_offset);

	अगर (unlikely(qlcnic_check_rx_tagging(adapter, skb, &vid))) अणु
		adapter->stats.rxdropped++;
		dev_kमुक्त_skb(skb);
		वापस buffer;
	पूर्ण

	skb->protocol = eth_type_trans(skb, netdev);

	अगर (vid != 0xffff)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vid);

	napi_gro_receive(&sds_ring->napi, skb);

	adapter->stats.rx_pkts++;
	adapter->stats.rxbytes += length;

	वापस buffer;
पूर्ण

#घोषणा QLC_TCP_HDR_SIZE            20
#घोषणा QLC_TCP_TS_OPTION_SIZE      12
#घोषणा QLC_TCP_TS_HDR_SIZE         (QLC_TCP_HDR_SIZE + QLC_TCP_TS_OPTION_SIZE)

अटल काष्ठा qlcnic_rx_buffer *
qlcnic_process_lro(काष्ठा qlcnic_adapter *adapter,
		   पूर्णांक ring, u64 sts_data0, u64 sts_data1)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	काष्ठा qlcnic_rx_buffer *buffer;
	काष्ठा sk_buff *skb;
	काष्ठा qlcnic_host_rds_ring *rds_ring;
	काष्ठा iphdr *iph;
	काष्ठा ipv6hdr *ipv6h;
	काष्ठा tcphdr *th;
	bool push, बारtamp;
	पूर्णांक index, l2_hdr_offset, l4_hdr_offset, is_lb_pkt;
	u16 lro_length, length, data_offset, t_vid, vid = 0xffff;
	u32 seq_number;

	अगर (unlikely(ring >= adapter->max_rds_rings))
		वापस शून्य;

	rds_ring = &recv_ctx->rds_rings[ring];

	index = qlcnic_get_lro_sts_refhandle(sts_data0);
	अगर (unlikely(index >= rds_ring->num_desc))
		वापस शून्य;

	buffer = &rds_ring->rx_buf_arr[index];

	बारtamp = qlcnic_get_lro_sts_बारtamp(sts_data0);
	lro_length = qlcnic_get_lro_sts_length(sts_data0);
	l2_hdr_offset = qlcnic_get_lro_sts_l2_hdr_offset(sts_data0);
	l4_hdr_offset = qlcnic_get_lro_sts_l4_hdr_offset(sts_data0);
	push = qlcnic_get_lro_sts_push_flag(sts_data0);
	seq_number = qlcnic_get_lro_sts_seq_number(sts_data1);

	skb = qlcnic_process_rxbuf(adapter, rds_ring, index, STATUS_CKSUM_OK);
	अगर (!skb)
		वापस buffer;

	अगर (adapter->rx_mac_learn) अणु
		t_vid = 0;
		is_lb_pkt = qlcnic_82xx_is_lb_pkt(sts_data0);
		qlcnic_add_lb_filter(adapter, skb, is_lb_pkt, t_vid);
	पूर्ण

	अगर (बारtamp)
		data_offset = l4_hdr_offset + QLC_TCP_TS_HDR_SIZE;
	अन्यथा
		data_offset = l4_hdr_offset + QLC_TCP_HDR_SIZE;

	skb_put(skb, lro_length + data_offset);
	skb_pull(skb, l2_hdr_offset);

	अगर (unlikely(qlcnic_check_rx_tagging(adapter, skb, &vid))) अणु
		adapter->stats.rxdropped++;
		dev_kमुक्त_skb(skb);
		वापस buffer;
	पूर्ण

	skb->protocol = eth_type_trans(skb, netdev);

	अगर (ntohs(skb->protocol) == ETH_P_IPV6) अणु
		ipv6h = (काष्ठा ipv6hdr *)skb->data;
		th = (काष्ठा tcphdr *)(skb->data + माप(काष्ठा ipv6hdr));
		length = (th->करोff << 2) + lro_length;
		ipv6h->payload_len = htons(length);
	पूर्ण अन्यथा अणु
		iph = (काष्ठा iphdr *)skb->data;
		th = (काष्ठा tcphdr *)(skb->data + (iph->ihl << 2));
		length = (iph->ihl << 2) + (th->करोff << 2) + lro_length;
		csum_replace2(&iph->check, iph->tot_len, htons(length));
		iph->tot_len = htons(length);
	पूर्ण

	th->psh = push;
	th->seq = htonl(seq_number);
	length = skb->len;

	अगर (adapter->flags & QLCNIC_FW_LRO_MSS_CAP) अणु
		skb_shinfo(skb)->gso_size = qlcnic_get_lro_sts_mss(sts_data1);
		अगर (skb->protocol == htons(ETH_P_IPV6))
			skb_shinfo(skb)->gso_type = SKB_GSO_TCPV6;
		अन्यथा
			skb_shinfo(skb)->gso_type = SKB_GSO_TCPV4;
	पूर्ण

	अगर (vid != 0xffff)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vid);
	netअगर_receive_skb(skb);

	adapter->stats.lro_pkts++;
	adapter->stats.lrobytes += length;

	वापस buffer;
पूर्ण

अटल पूर्णांक qlcnic_process_rcv_ring(काष्ठा qlcnic_host_sds_ring *sds_ring, पूर्णांक max)
अणु
	काष्ठा qlcnic_host_rds_ring *rds_ring;
	काष्ठा qlcnic_adapter *adapter = sds_ring->adapter;
	काष्ठा list_head *cur;
	काष्ठा status_desc *desc;
	काष्ठा qlcnic_rx_buffer *rxbuf;
	पूर्णांक opcode, desc_cnt, count = 0;
	u64 sts_data0, sts_data1;
	u8 ring;
	u32 consumer = sds_ring->consumer;

	जबतक (count < max) अणु
		desc = &sds_ring->desc_head[consumer];
		sts_data0 = le64_to_cpu(desc->status_desc_data[0]);

		अगर (!(sts_data0 & STATUS_OWNER_HOST))
			अवरोध;

		desc_cnt = qlcnic_get_sts_desc_cnt(sts_data0);
		opcode = qlcnic_get_sts_opcode(sts_data0);
		चयन (opcode) अणु
		हाल QLCNIC_RXPKT_DESC:
		हाल QLCNIC_OLD_RXPKT_DESC:
		हाल QLCNIC_SYN_OFFLOAD:
			ring = qlcnic_get_sts_type(sts_data0);
			rxbuf = qlcnic_process_rcv(adapter, sds_ring, ring,
						   sts_data0);
			अवरोध;
		हाल QLCNIC_LRO_DESC:
			ring = qlcnic_get_lro_sts_type(sts_data0);
			sts_data1 = le64_to_cpu(desc->status_desc_data[1]);
			rxbuf = qlcnic_process_lro(adapter, ring, sts_data0,
						   sts_data1);
			अवरोध;
		हाल QLCNIC_RESPONSE_DESC:
			qlcnic_handle_fw_message(desc_cnt, consumer, sds_ring);
		शेष:
			जाओ skip;
		पूर्ण
		WARN_ON(desc_cnt > 1);

		अगर (likely(rxbuf))
			list_add_tail(&rxbuf->list, &sds_ring->मुक्त_list[ring]);
		अन्यथा
			adapter->stats.null_rxbuf++;
skip:
		क्रम (; desc_cnt > 0; desc_cnt--) अणु
			desc = &sds_ring->desc_head[consumer];
			desc->status_desc_data[0] = QLCNIC_DESC_OWNER_FW;
			consumer = get_next_index(consumer, sds_ring->num_desc);
		पूर्ण
		count++;
	पूर्ण

	क्रम (ring = 0; ring < adapter->max_rds_rings; ring++) अणु
		rds_ring = &adapter->recv_ctx->rds_rings[ring];
		अगर (!list_empty(&sds_ring->मुक्त_list[ring])) अणु
			list_क्रम_each(cur, &sds_ring->मुक्त_list[ring]) अणु
				rxbuf = list_entry(cur, काष्ठा qlcnic_rx_buffer,
						   list);
				qlcnic_alloc_rx_skb(adapter, rds_ring, rxbuf);
			पूर्ण
			spin_lock(&rds_ring->lock);
			list_splice_tail_init(&sds_ring->मुक्त_list[ring],
					      &rds_ring->मुक्त_list);
			spin_unlock(&rds_ring->lock);
		पूर्ण

		qlcnic_post_rx_buffers_nodb(adapter, rds_ring, ring);
	पूर्ण

	अगर (count) अणु
		sds_ring->consumer = consumer;
		ग_लिखोl(consumer, sds_ring->crb_sts_consumer);
	पूर्ण

	वापस count;
पूर्ण

व्योम qlcnic_post_rx_buffers(काष्ठा qlcnic_adapter *adapter,
			    काष्ठा qlcnic_host_rds_ring *rds_ring, u8 ring_id)
अणु
	काष्ठा rcv_desc *pdesc;
	काष्ठा qlcnic_rx_buffer *buffer;
	पूर्णांक count = 0;
	u32 producer, handle;
	काष्ठा list_head *head;

	producer = rds_ring->producer;
	head = &rds_ring->मुक्त_list;

	जबतक (!list_empty(head)) अणु

		buffer = list_entry(head->next, काष्ठा qlcnic_rx_buffer, list);

		अगर (!buffer->skb) अणु
			अगर (qlcnic_alloc_rx_skb(adapter, rds_ring, buffer))
				अवरोध;
		पूर्ण

		count++;
		list_del(&buffer->list);

		/* make a rcv descriptor  */
		pdesc = &rds_ring->desc_head[producer];
		pdesc->addr_buffer = cpu_to_le64(buffer->dma);
		handle = qlcnic_get_ref_handle(adapter, buffer->ref_handle,
					       ring_id);
		pdesc->reference_handle = cpu_to_le16(handle);
		pdesc->buffer_length = cpu_to_le32(rds_ring->dma_size);
		producer = get_next_index(producer, rds_ring->num_desc);
	पूर्ण

	अगर (count) अणु
		rds_ring->producer = producer;
		ग_लिखोl((producer-1) & (rds_ring->num_desc-1),
		       rds_ring->crb_rcv_producer);
	पूर्ण
पूर्ण

अटल व्योम dump_skb(काष्ठा sk_buff *skb, काष्ठा qlcnic_adapter *adapter)
अणु
	अगर (adapter->ahw->msg_enable & NETIF_MSG_DRV) अणु
		अक्षर prefix[30];

		scnम_लिखो(prefix, माप(prefix), "%s: %s: ",
			  dev_name(&adapter->pdev->dev), __func__);

		prपूर्णांक_hex_dump_debug(prefix, DUMP_PREFIX_NONE, 16, 1,
				     skb->data, skb->len, true);
	पूर्ण
पूर्ण

अटल व्योम qlcnic_process_rcv_diag(काष्ठा qlcnic_adapter *adapter, पूर्णांक ring,
				    u64 sts_data0)
अणु
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	काष्ठा sk_buff *skb;
	काष्ठा qlcnic_host_rds_ring *rds_ring;
	पूर्णांक index, length, cksum, pkt_offset;

	अगर (unlikely(ring >= adapter->max_rds_rings))
		वापस;

	rds_ring = &recv_ctx->rds_rings[ring];

	index = qlcnic_get_sts_refhandle(sts_data0);
	length = qlcnic_get_sts_totallength(sts_data0);
	अगर (unlikely(index >= rds_ring->num_desc))
		वापस;

	cksum  = qlcnic_get_sts_status(sts_data0);
	pkt_offset = qlcnic_get_sts_pkt_offset(sts_data0);

	skb = qlcnic_process_rxbuf(adapter, rds_ring, index, cksum);
	अगर (!skb)
		वापस;

	अगर (length > rds_ring->skb_size)
		skb_put(skb, rds_ring->skb_size);
	अन्यथा
		skb_put(skb, length);

	अगर (pkt_offset)
		skb_pull(skb, pkt_offset);

	अगर (!qlcnic_check_loopback_buff(skb->data, adapter->mac_addr))
		adapter->ahw->diag_cnt++;
	अन्यथा
		dump_skb(skb, adapter);

	dev_kमुक्त_skb_any(skb);
	adapter->stats.rx_pkts++;
	adapter->stats.rxbytes += length;

	वापस;
पूर्ण

व्योम qlcnic_82xx_process_rcv_ring_diag(काष्ठा qlcnic_host_sds_ring *sds_ring)
अणु
	काष्ठा qlcnic_adapter *adapter = sds_ring->adapter;
	काष्ठा status_desc *desc;
	u64 sts_data0;
	पूर्णांक ring, opcode, desc_cnt;

	u32 consumer = sds_ring->consumer;

	desc = &sds_ring->desc_head[consumer];
	sts_data0 = le64_to_cpu(desc->status_desc_data[0]);

	अगर (!(sts_data0 & STATUS_OWNER_HOST))
		वापस;

	desc_cnt = qlcnic_get_sts_desc_cnt(sts_data0);
	opcode = qlcnic_get_sts_opcode(sts_data0);
	चयन (opcode) अणु
	हाल QLCNIC_RESPONSE_DESC:
		qlcnic_handle_fw_message(desc_cnt, consumer, sds_ring);
		अवरोध;
	शेष:
		ring = qlcnic_get_sts_type(sts_data0);
		qlcnic_process_rcv_diag(adapter, ring, sts_data0);
		अवरोध;
	पूर्ण

	क्रम (; desc_cnt > 0; desc_cnt--) अणु
		desc = &sds_ring->desc_head[consumer];
		desc->status_desc_data[0] = cpu_to_le64(STATUS_OWNER_PHANTOM);
		consumer = get_next_index(consumer, sds_ring->num_desc);
	पूर्ण

	sds_ring->consumer = consumer;
	ग_लिखोl(consumer, sds_ring->crb_sts_consumer);
पूर्ण

पूर्णांक qlcnic_82xx_napi_add(काष्ठा qlcnic_adapter *adapter,
			 काष्ठा net_device *netdev)
अणु
	पूर्णांक ring;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	काष्ठा qlcnic_host_tx_ring *tx_ring;

	अगर (qlcnic_alloc_sds_rings(recv_ctx, adapter->drv_sds_rings))
		वापस -ENOMEM;

	क्रम (ring = 0; ring < adapter->drv_sds_rings; ring++) अणु
		sds_ring = &recv_ctx->sds_rings[ring];
		अगर (qlcnic_check_multi_tx(adapter) &&
		    !adapter->ahw->diag_test) अणु
			netअगर_napi_add(netdev, &sds_ring->napi, qlcnic_rx_poll,
				       NAPI_POLL_WEIGHT);
		पूर्ण अन्यथा अणु
			अगर (ring == (adapter->drv_sds_rings - 1))
				netअगर_napi_add(netdev, &sds_ring->napi,
					       qlcnic_poll,
					       NAPI_POLL_WEIGHT);
			अन्यथा
				netअगर_napi_add(netdev, &sds_ring->napi,
					       qlcnic_rx_poll,
					       NAPI_POLL_WEIGHT);
		पूर्ण
	पूर्ण

	अगर (qlcnic_alloc_tx_rings(adapter, netdev)) अणु
		qlcnic_मुक्त_sds_rings(recv_ctx);
		वापस -ENOMEM;
	पूर्ण

	अगर (qlcnic_check_multi_tx(adapter) && !adapter->ahw->diag_test) अणु
		क्रम (ring = 0; ring < adapter->drv_tx_rings; ring++) अणु
			tx_ring = &adapter->tx_ring[ring];
			netअगर_tx_napi_add(netdev, &tx_ring->napi, qlcnic_tx_poll,
				       NAPI_POLL_WEIGHT);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम qlcnic_82xx_napi_del(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक ring;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	काष्ठा qlcnic_host_tx_ring *tx_ring;

	क्रम (ring = 0; ring < adapter->drv_sds_rings; ring++) अणु
		sds_ring = &recv_ctx->sds_rings[ring];
		netअगर_napi_del(&sds_ring->napi);
	पूर्ण

	qlcnic_मुक्त_sds_rings(adapter->recv_ctx);

	अगर (qlcnic_check_multi_tx(adapter) && !adapter->ahw->diag_test) अणु
		क्रम (ring = 0; ring < adapter->drv_tx_rings; ring++) अणु
			tx_ring = &adapter->tx_ring[ring];
			netअगर_napi_del(&tx_ring->napi);
		पूर्ण
	पूर्ण

	qlcnic_मुक्त_tx_rings(adapter);
पूर्ण

व्योम qlcnic_82xx_napi_enable(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक ring;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_host_tx_ring *tx_ring;
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;

	अगर (adapter->is_up != QLCNIC_ADAPTER_UP_MAGIC)
		वापस;

	क्रम (ring = 0; ring < adapter->drv_sds_rings; ring++) अणु
		sds_ring = &recv_ctx->sds_rings[ring];
		napi_enable(&sds_ring->napi);
		qlcnic_enable_sds_पूर्णांकr(adapter, sds_ring);
	पूर्ण

	अगर (qlcnic_check_multi_tx(adapter) &&
	    (adapter->flags & QLCNIC_MSIX_ENABLED) &&
	    !adapter->ahw->diag_test) अणु
		क्रम (ring = 0; ring < adapter->drv_tx_rings; ring++) अणु
			tx_ring = &adapter->tx_ring[ring];
			napi_enable(&tx_ring->napi);
			qlcnic_enable_tx_पूर्णांकr(adapter, tx_ring);
		पूर्ण
	पूर्ण
पूर्ण

व्योम qlcnic_82xx_napi_disable(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक ring;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_host_tx_ring *tx_ring;
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;

	अगर (adapter->is_up != QLCNIC_ADAPTER_UP_MAGIC)
		वापस;

	क्रम (ring = 0; ring < adapter->drv_sds_rings; ring++) अणु
		sds_ring = &recv_ctx->sds_rings[ring];
		qlcnic_disable_sds_पूर्णांकr(adapter, sds_ring);
		napi_synchronize(&sds_ring->napi);
		napi_disable(&sds_ring->napi);
	पूर्ण

	अगर ((adapter->flags & QLCNIC_MSIX_ENABLED) &&
	    !adapter->ahw->diag_test &&
	    qlcnic_check_multi_tx(adapter)) अणु
		क्रम (ring = 0; ring < adapter->drv_tx_rings; ring++) अणु
			tx_ring = &adapter->tx_ring[ring];
			qlcnic_disable_tx_पूर्णांकr(adapter, tx_ring);
			napi_synchronize(&tx_ring->napi);
			napi_disable(&tx_ring->napi);
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा QLC_83XX_NORMAL_LB_PKT	(1ULL << 36)
#घोषणा QLC_83XX_LRO_LB_PKT	(1ULL << 46)

अटल अंतरभूत पूर्णांक qlcnic_83xx_is_lb_pkt(u64 sts_data, पूर्णांक lro_pkt)
अणु
	अगर (lro_pkt)
		वापस (sts_data & QLC_83XX_LRO_LB_PKT) ? 1 : 0;
	अन्यथा
		वापस (sts_data & QLC_83XX_NORMAL_LB_PKT) ? 1 : 0;
पूर्ण

#घोषणा QLCNIC_ENCAP_LENGTH_MASK	0x7f

अटल अंतरभूत u8 qlcnic_encap_length(u64 sts_data)
अणु
	वापस sts_data & QLCNIC_ENCAP_LENGTH_MASK;
पूर्ण

अटल काष्ठा qlcnic_rx_buffer *
qlcnic_83xx_process_rcv(काष्ठा qlcnic_adapter *adapter,
			काष्ठा qlcnic_host_sds_ring *sds_ring,
			u8 ring, u64 sts_data[])
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	काष्ठा qlcnic_rx_buffer *buffer;
	काष्ठा sk_buff *skb;
	काष्ठा qlcnic_host_rds_ring *rds_ring;
	पूर्णांक index, length, cksum, is_lb_pkt;
	u16 vid = 0xffff;
	पूर्णांक err;

	अगर (unlikely(ring >= adapter->max_rds_rings))
		वापस शून्य;

	rds_ring = &recv_ctx->rds_rings[ring];

	index = qlcnic_83xx_hndl(sts_data[0]);
	अगर (unlikely(index >= rds_ring->num_desc))
		वापस शून्य;

	buffer = &rds_ring->rx_buf_arr[index];
	length = qlcnic_83xx_pktln(sts_data[0]);
	cksum  = qlcnic_83xx_csum_status(sts_data[1]);
	skb = qlcnic_process_rxbuf(adapter, rds_ring, index, cksum);
	अगर (!skb)
		वापस buffer;

	अगर (length > rds_ring->skb_size)
		skb_put(skb, rds_ring->skb_size);
	अन्यथा
		skb_put(skb, length);

	err = qlcnic_check_rx_tagging(adapter, skb, &vid);

	अगर (adapter->rx_mac_learn) अणु
		is_lb_pkt = qlcnic_83xx_is_lb_pkt(sts_data[1], 0);
		qlcnic_add_lb_filter(adapter, skb, is_lb_pkt, vid);
	पूर्ण

	अगर (unlikely(err)) अणु
		adapter->stats.rxdropped++;
		dev_kमुक्त_skb(skb);
		वापस buffer;
	पूर्ण

	skb->protocol = eth_type_trans(skb, netdev);

	अगर (qlcnic_encap_length(sts_data[1]) &&
	    skb->ip_summed == CHECKSUM_UNNECESSARY) अणु
		skb->csum_level = 1;
		adapter->stats.encap_rx_csummed++;
	पूर्ण

	अगर (vid != 0xffff)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vid);

	napi_gro_receive(&sds_ring->napi, skb);

	adapter->stats.rx_pkts++;
	adapter->stats.rxbytes += length;

	वापस buffer;
पूर्ण

अटल काष्ठा qlcnic_rx_buffer *
qlcnic_83xx_process_lro(काष्ठा qlcnic_adapter *adapter,
			u8 ring, u64 sts_data[])
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	काष्ठा qlcnic_rx_buffer *buffer;
	काष्ठा sk_buff *skb;
	काष्ठा qlcnic_host_rds_ring *rds_ring;
	काष्ठा iphdr *iph;
	काष्ठा ipv6hdr *ipv6h;
	काष्ठा tcphdr *th;
	bool push;
	पूर्णांक l2_hdr_offset, l4_hdr_offset;
	पूर्णांक index, is_lb_pkt;
	u16 lro_length, length, data_offset, gso_size;
	u16 vid = 0xffff;
	पूर्णांक err;

	अगर (unlikely(ring >= adapter->max_rds_rings))
		वापस शून्य;

	rds_ring = &recv_ctx->rds_rings[ring];

	index = qlcnic_83xx_hndl(sts_data[0]);
	अगर (unlikely(index >= rds_ring->num_desc))
		वापस शून्य;

	buffer = &rds_ring->rx_buf_arr[index];

	lro_length = qlcnic_83xx_lro_pktln(sts_data[0]);
	l2_hdr_offset = qlcnic_83xx_l2_hdr_off(sts_data[1]);
	l4_hdr_offset = qlcnic_83xx_l4_hdr_off(sts_data[1]);
	push = qlcnic_83xx_is_psh_bit(sts_data[1]);

	skb = qlcnic_process_rxbuf(adapter, rds_ring, index, STATUS_CKSUM_OK);
	अगर (!skb)
		वापस buffer;

	अगर (qlcnic_83xx_is_tstamp(sts_data[1]))
		data_offset = l4_hdr_offset + QLCNIC_TCP_TS_HDR_SIZE;
	अन्यथा
		data_offset = l4_hdr_offset + QLCNIC_TCP_HDR_SIZE;

	skb_put(skb, lro_length + data_offset);
	skb_pull(skb, l2_hdr_offset);

	err = qlcnic_check_rx_tagging(adapter, skb, &vid);

	अगर (adapter->rx_mac_learn) अणु
		is_lb_pkt = qlcnic_83xx_is_lb_pkt(sts_data[1], 1);
		qlcnic_add_lb_filter(adapter, skb, is_lb_pkt, vid);
	पूर्ण

	अगर (unlikely(err)) अणु
		adapter->stats.rxdropped++;
		dev_kमुक्त_skb(skb);
		वापस buffer;
	पूर्ण

	skb->protocol = eth_type_trans(skb, netdev);
	अगर (ntohs(skb->protocol) == ETH_P_IPV6) अणु
		ipv6h = (काष्ठा ipv6hdr *)skb->data;
		th = (काष्ठा tcphdr *)(skb->data + माप(काष्ठा ipv6hdr));

		length = (th->करोff << 2) + lro_length;
		ipv6h->payload_len = htons(length);
	पूर्ण अन्यथा अणु
		iph = (काष्ठा iphdr *)skb->data;
		th = (काष्ठा tcphdr *)(skb->data + (iph->ihl << 2));
		length = (iph->ihl << 2) + (th->करोff << 2) + lro_length;
		csum_replace2(&iph->check, iph->tot_len, htons(length));
		iph->tot_len = htons(length);
	पूर्ण

	th->psh = push;
	length = skb->len;

	अगर (adapter->flags & QLCNIC_FW_LRO_MSS_CAP) अणु
		gso_size = qlcnic_83xx_get_lro_sts_mss(sts_data[0]);
		skb_shinfo(skb)->gso_size = gso_size;
		अगर (skb->protocol == htons(ETH_P_IPV6))
			skb_shinfo(skb)->gso_type = SKB_GSO_TCPV6;
		अन्यथा
			skb_shinfo(skb)->gso_type = SKB_GSO_TCPV4;
	पूर्ण

	अगर (vid != 0xffff)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vid);

	netअगर_receive_skb(skb);

	adapter->stats.lro_pkts++;
	adapter->stats.lrobytes += length;
	वापस buffer;
पूर्ण

अटल पूर्णांक qlcnic_83xx_process_rcv_ring(काष्ठा qlcnic_host_sds_ring *sds_ring,
					पूर्णांक max)
अणु
	काष्ठा qlcnic_host_rds_ring *rds_ring;
	काष्ठा qlcnic_adapter *adapter = sds_ring->adapter;
	काष्ठा list_head *cur;
	काष्ठा status_desc *desc;
	काष्ठा qlcnic_rx_buffer *rxbuf = शून्य;
	u8 ring;
	u64 sts_data[2];
	पूर्णांक count = 0, opcode;
	u32 consumer = sds_ring->consumer;

	जबतक (count < max) अणु
		desc = &sds_ring->desc_head[consumer];
		sts_data[1] = le64_to_cpu(desc->status_desc_data[1]);
		opcode = qlcnic_83xx_opcode(sts_data[1]);
		अगर (!opcode)
			अवरोध;
		sts_data[0] = le64_to_cpu(desc->status_desc_data[0]);
		ring = QLCNIC_FETCH_RING_ID(sts_data[0]);

		चयन (opcode) अणु
		हाल QLC_83XX_REG_DESC:
			rxbuf = qlcnic_83xx_process_rcv(adapter, sds_ring,
							ring, sts_data);
			अवरोध;
		हाल QLC_83XX_LRO_DESC:
			rxbuf = qlcnic_83xx_process_lro(adapter, ring,
							sts_data);
			अवरोध;
		शेष:
			dev_info(&adapter->pdev->dev,
				 "Unknown opcode: 0x%x\n", opcode);
			जाओ skip;
		पूर्ण

		अगर (likely(rxbuf))
			list_add_tail(&rxbuf->list, &sds_ring->मुक्त_list[ring]);
		अन्यथा
			adapter->stats.null_rxbuf++;
skip:
		desc = &sds_ring->desc_head[consumer];
		/* Reset the descriptor */
		desc->status_desc_data[1] = 0;
		consumer = get_next_index(consumer, sds_ring->num_desc);
		count++;
	पूर्ण
	क्रम (ring = 0; ring < adapter->max_rds_rings; ring++) अणु
		rds_ring = &adapter->recv_ctx->rds_rings[ring];
		अगर (!list_empty(&sds_ring->मुक्त_list[ring])) अणु
			list_क्रम_each(cur, &sds_ring->मुक्त_list[ring]) अणु
				rxbuf = list_entry(cur, काष्ठा qlcnic_rx_buffer,
						   list);
				qlcnic_alloc_rx_skb(adapter, rds_ring, rxbuf);
			पूर्ण
			spin_lock(&rds_ring->lock);
			list_splice_tail_init(&sds_ring->मुक्त_list[ring],
					      &rds_ring->मुक्त_list);
			spin_unlock(&rds_ring->lock);
		पूर्ण
		qlcnic_post_rx_buffers_nodb(adapter, rds_ring, ring);
	पूर्ण
	अगर (count) अणु
		sds_ring->consumer = consumer;
		ग_लिखोl(consumer, sds_ring->crb_sts_consumer);
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक qlcnic_83xx_msix_sriov_vf_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	पूर्णांक tx_complete;
	पूर्णांक work_करोne;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_adapter *adapter;
	काष्ठा qlcnic_host_tx_ring *tx_ring;

	sds_ring = container_of(napi, काष्ठा qlcnic_host_sds_ring, napi);
	adapter = sds_ring->adapter;
	/* tx ring count = 1 */
	tx_ring = adapter->tx_ring;

	tx_complete = qlcnic_process_cmd_ring(adapter, tx_ring, budget);
	work_करोne = qlcnic_83xx_process_rcv_ring(sds_ring, budget);

	/* Check अगर we need a repoll */
	अगर (!tx_complete)
		work_करोne = budget;

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(&sds_ring->napi, work_करोne);
		qlcnic_enable_sds_पूर्णांकr(adapter, sds_ring);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल पूर्णांक qlcnic_83xx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	पूर्णांक tx_complete;
	पूर्णांक work_करोne;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_adapter *adapter;
	काष्ठा qlcnic_host_tx_ring *tx_ring;

	sds_ring = container_of(napi, काष्ठा qlcnic_host_sds_ring, napi);
	adapter = sds_ring->adapter;
	/* tx ring count = 1 */
	tx_ring = adapter->tx_ring;

	tx_complete = qlcnic_process_cmd_ring(adapter, tx_ring, budget);
	work_करोne = qlcnic_83xx_process_rcv_ring(sds_ring, budget);

	/* Check अगर we need a repoll */
	अगर (!tx_complete)
		work_करोne = budget;

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(&sds_ring->napi, work_करोne);
		qlcnic_enable_sds_पूर्णांकr(adapter, sds_ring);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल पूर्णांक qlcnic_83xx_msix_tx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	पूर्णांक work_करोne;
	काष्ठा qlcnic_host_tx_ring *tx_ring;
	काष्ठा qlcnic_adapter *adapter;

	tx_ring = container_of(napi, काष्ठा qlcnic_host_tx_ring, napi);
	adapter = tx_ring->adapter;
	work_करोne = qlcnic_process_cmd_ring(adapter, tx_ring, budget);
	अगर (work_करोne) अणु
		napi_complete(&tx_ring->napi);
		अगर (test_bit(__QLCNIC_DEV_UP , &adapter->state))
			qlcnic_enable_tx_पूर्णांकr(adapter, tx_ring);
	पूर्ण अन्यथा अणु
		/* need a repoll */
		work_करोne = budget;
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल पूर्णांक qlcnic_83xx_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	पूर्णांक work_करोne;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_adapter *adapter;

	sds_ring = container_of(napi, काष्ठा qlcnic_host_sds_ring, napi);
	adapter = sds_ring->adapter;
	work_करोne = qlcnic_83xx_process_rcv_ring(sds_ring, budget);
	अगर (work_करोne < budget) अणु
		napi_complete_करोne(&sds_ring->napi, work_करोne);
		अगर (test_bit(__QLCNIC_DEV_UP, &adapter->state))
			qlcnic_enable_sds_पूर्णांकr(adapter, sds_ring);
	पूर्ण

	वापस work_करोne;
पूर्ण

व्योम qlcnic_83xx_napi_enable(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक ring;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_host_tx_ring *tx_ring;
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;

	अगर (adapter->is_up != QLCNIC_ADAPTER_UP_MAGIC)
		वापस;

	क्रम (ring = 0; ring < adapter->drv_sds_rings; ring++) अणु
		sds_ring = &recv_ctx->sds_rings[ring];
		napi_enable(&sds_ring->napi);
		अगर (adapter->flags & QLCNIC_MSIX_ENABLED)
			qlcnic_enable_sds_पूर्णांकr(adapter, sds_ring);
	पूर्ण

	अगर ((adapter->flags & QLCNIC_MSIX_ENABLED) &&
	    !(adapter->flags & QLCNIC_TX_INTR_SHARED)) अणु
		क्रम (ring = 0; ring < adapter->drv_tx_rings; ring++) अणु
			tx_ring = &adapter->tx_ring[ring];
			napi_enable(&tx_ring->napi);
			qlcnic_enable_tx_पूर्णांकr(adapter, tx_ring);
		पूर्ण
	पूर्ण
पूर्ण

व्योम qlcnic_83xx_napi_disable(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक ring;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	काष्ठा qlcnic_host_tx_ring *tx_ring;

	अगर (adapter->is_up != QLCNIC_ADAPTER_UP_MAGIC)
		वापस;

	क्रम (ring = 0; ring < adapter->drv_sds_rings; ring++) अणु
		sds_ring = &recv_ctx->sds_rings[ring];
		अगर (adapter->flags & QLCNIC_MSIX_ENABLED)
			qlcnic_disable_sds_पूर्णांकr(adapter, sds_ring);
		napi_synchronize(&sds_ring->napi);
		napi_disable(&sds_ring->napi);
	पूर्ण

	अगर ((adapter->flags & QLCNIC_MSIX_ENABLED) &&
	    !(adapter->flags & QLCNIC_TX_INTR_SHARED)) अणु
		क्रम (ring = 0; ring < adapter->drv_tx_rings; ring++) अणु
			tx_ring = &adapter->tx_ring[ring];
			qlcnic_disable_tx_पूर्णांकr(adapter, tx_ring);
			napi_synchronize(&tx_ring->napi);
			napi_disable(&tx_ring->napi);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक qlcnic_83xx_napi_add(काष्ठा qlcnic_adapter *adapter,
			 काष्ठा net_device *netdev)
अणु
	पूर्णांक ring;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_host_tx_ring *tx_ring;
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;

	अगर (qlcnic_alloc_sds_rings(recv_ctx, adapter->drv_sds_rings))
		वापस -ENOMEM;

	क्रम (ring = 0; ring < adapter->drv_sds_rings; ring++) अणु
		sds_ring = &recv_ctx->sds_rings[ring];
		अगर (adapter->flags & QLCNIC_MSIX_ENABLED) अणु
			अगर (!(adapter->flags & QLCNIC_TX_INTR_SHARED))
				netअगर_napi_add(netdev, &sds_ring->napi,
					       qlcnic_83xx_rx_poll,
					       NAPI_POLL_WEIGHT);
			अन्यथा
				netअगर_napi_add(netdev, &sds_ring->napi,
					       qlcnic_83xx_msix_sriov_vf_poll,
					       NAPI_POLL_WEIGHT);

		पूर्ण अन्यथा अणु
			netअगर_napi_add(netdev, &sds_ring->napi,
				       qlcnic_83xx_poll,
				       NAPI_POLL_WEIGHT);
		पूर्ण
	पूर्ण

	अगर (qlcnic_alloc_tx_rings(adapter, netdev)) अणु
		qlcnic_मुक्त_sds_rings(recv_ctx);
		वापस -ENOMEM;
	पूर्ण

	अगर ((adapter->flags & QLCNIC_MSIX_ENABLED) &&
	    !(adapter->flags & QLCNIC_TX_INTR_SHARED)) अणु
		क्रम (ring = 0; ring < adapter->drv_tx_rings; ring++) अणु
			tx_ring = &adapter->tx_ring[ring];
			netअगर_tx_napi_add(netdev, &tx_ring->napi,
				       qlcnic_83xx_msix_tx_poll,
				       NAPI_POLL_WEIGHT);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम qlcnic_83xx_napi_del(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक ring;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	काष्ठा qlcnic_host_tx_ring *tx_ring;

	क्रम (ring = 0; ring < adapter->drv_sds_rings; ring++) अणु
		sds_ring = &recv_ctx->sds_rings[ring];
		netअगर_napi_del(&sds_ring->napi);
	पूर्ण

	qlcnic_मुक्त_sds_rings(adapter->recv_ctx);

	अगर ((adapter->flags & QLCNIC_MSIX_ENABLED) &&
	    !(adapter->flags & QLCNIC_TX_INTR_SHARED)) अणु
		क्रम (ring = 0; ring < adapter->drv_tx_rings; ring++) अणु
			tx_ring = &adapter->tx_ring[ring];
			netअगर_napi_del(&tx_ring->napi);
		पूर्ण
	पूर्ण

	qlcnic_मुक्त_tx_rings(adapter);
पूर्ण

अटल व्योम qlcnic_83xx_process_rcv_diag(काष्ठा qlcnic_adapter *adapter,
					 पूर्णांक ring, u64 sts_data[])
अणु
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	काष्ठा sk_buff *skb;
	काष्ठा qlcnic_host_rds_ring *rds_ring;
	पूर्णांक index, length;

	अगर (unlikely(ring >= adapter->max_rds_rings))
		वापस;

	rds_ring = &recv_ctx->rds_rings[ring];
	index = qlcnic_83xx_hndl(sts_data[0]);
	अगर (unlikely(index >= rds_ring->num_desc))
		वापस;

	length = qlcnic_83xx_pktln(sts_data[0]);

	skb = qlcnic_process_rxbuf(adapter, rds_ring, index, STATUS_CKSUM_OK);
	अगर (!skb)
		वापस;

	अगर (length > rds_ring->skb_size)
		skb_put(skb, rds_ring->skb_size);
	अन्यथा
		skb_put(skb, length);

	अगर (!qlcnic_check_loopback_buff(skb->data, adapter->mac_addr))
		adapter->ahw->diag_cnt++;
	अन्यथा
		dump_skb(skb, adapter);

	dev_kमुक्त_skb_any(skb);
	वापस;
पूर्ण

व्योम qlcnic_83xx_process_rcv_ring_diag(काष्ठा qlcnic_host_sds_ring *sds_ring)
अणु
	काष्ठा qlcnic_adapter *adapter = sds_ring->adapter;
	काष्ठा status_desc *desc;
	u64 sts_data[2];
	पूर्णांक ring, opcode;
	u32 consumer = sds_ring->consumer;

	desc = &sds_ring->desc_head[consumer];
	sts_data[0] = le64_to_cpu(desc->status_desc_data[0]);
	sts_data[1] = le64_to_cpu(desc->status_desc_data[1]);
	opcode = qlcnic_83xx_opcode(sts_data[1]);
	अगर (!opcode)
		वापस;

	ring = QLCNIC_FETCH_RING_ID(sts_data[0]);
	qlcnic_83xx_process_rcv_diag(adapter, ring, sts_data);
	desc = &sds_ring->desc_head[consumer];
	desc->status_desc_data[0] = cpu_to_le64(STATUS_OWNER_PHANTOM);
	consumer = get_next_index(consumer, sds_ring->num_desc);
	sds_ring->consumer = consumer;
	ग_लिखोl(consumer, sds_ring->crb_sts_consumer);
पूर्ण
