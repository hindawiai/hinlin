<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#समावेश <linux/prefetch.h>
#समावेश <linux/bpf_trace.h>
#समावेश <net/xdp.h>
#समावेश "i40e.h"
#समावेश "i40e_trace.h"
#समावेश "i40e_prototype.h"
#समावेश "i40e_txrx_common.h"
#समावेश "i40e_xsk.h"

#घोषणा I40E_TXD_CMD (I40E_TX_DESC_CMD_EOP | I40E_TX_DESC_CMD_RS)
/**
 * i40e_fdir - Generate a Flow Director descriptor based on fdata
 * @tx_ring: Tx ring to send buffer on
 * @fdata: Flow director filter data
 * @add: Indicate अगर we are adding a rule or deleting one
 *
 **/
अटल व्योम i40e_fdir(काष्ठा i40e_ring *tx_ring,
		      काष्ठा i40e_fdir_filter *fdata, bool add)
अणु
	काष्ठा i40e_filter_program_desc *fdir_desc;
	काष्ठा i40e_pf *pf = tx_ring->vsi->back;
	u32 flex_ptype, dtype_cmd;
	u16 i;

	/* grab the next descriptor */
	i = tx_ring->next_to_use;
	fdir_desc = I40E_TX_FसूचीDESC(tx_ring, i);

	i++;
	tx_ring->next_to_use = (i < tx_ring->count) ? i : 0;

	flex_ptype = I40E_TXD_FLTR_QW0_QINDEX_MASK &
		     (fdata->q_index << I40E_TXD_FLTR_QW0_QINDEX_SHIFT);

	flex_ptype |= I40E_TXD_FLTR_QW0_FLEXOFF_MASK &
		      (fdata->flex_off << I40E_TXD_FLTR_QW0_FLEXOFF_SHIFT);

	flex_ptype |= I40E_TXD_FLTR_QW0_PCTYPE_MASK &
		      (fdata->pctype << I40E_TXD_FLTR_QW0_PCTYPE_SHIFT);

	/* Use LAN VSI Id अगर not programmed by user */
	flex_ptype |= I40E_TXD_FLTR_QW0_DEST_VSI_MASK &
		      ((u32)(fdata->dest_vsi ? : pf->vsi[pf->lan_vsi]->id) <<
		       I40E_TXD_FLTR_QW0_DEST_VSI_SHIFT);

	dtype_cmd = I40E_TX_DESC_DTYPE_FILTER_PROG;

	dtype_cmd |= add ?
		     I40E_FILTER_PROGRAM_DESC_PCMD_ADD_UPDATE <<
		     I40E_TXD_FLTR_QW1_PCMD_SHIFT :
		     I40E_FILTER_PROGRAM_DESC_PCMD_REMOVE <<
		     I40E_TXD_FLTR_QW1_PCMD_SHIFT;

	dtype_cmd |= I40E_TXD_FLTR_QW1_DEST_MASK &
		     (fdata->dest_ctl << I40E_TXD_FLTR_QW1_DEST_SHIFT);

	dtype_cmd |= I40E_TXD_FLTR_QW1_FD_STATUS_MASK &
		     (fdata->fd_status << I40E_TXD_FLTR_QW1_FD_STATUS_SHIFT);

	अगर (fdata->cnt_index) अणु
		dtype_cmd |= I40E_TXD_FLTR_QW1_CNT_ENA_MASK;
		dtype_cmd |= I40E_TXD_FLTR_QW1_CNTINDEX_MASK &
			     ((u32)fdata->cnt_index <<
			      I40E_TXD_FLTR_QW1_CNTINDEX_SHIFT);
	पूर्ण

	fdir_desc->qindex_flex_ptype_vsi = cpu_to_le32(flex_ptype);
	fdir_desc->rsvd = cpu_to_le32(0);
	fdir_desc->dtype_cmd_cntindex = cpu_to_le32(dtype_cmd);
	fdir_desc->fd_id = cpu_to_le32(fdata->fd_id);
पूर्ण

#घोषणा I40E_FD_CLEAN_DELAY 10
/**
 * i40e_program_fdir_filter - Program a Flow Director filter
 * @fdir_data: Packet data that will be filter parameters
 * @raw_packet: the pre-allocated packet buffer क्रम FDir
 * @pf: The PF poपूर्णांकer
 * @add: True क्रम add/update, False क्रम हटाओ
 **/
अटल पूर्णांक i40e_program_fdir_filter(काष्ठा i40e_fdir_filter *fdir_data,
				    u8 *raw_packet, काष्ठा i40e_pf *pf,
				    bool add)
अणु
	काष्ठा i40e_tx_buffer *tx_buf, *first;
	काष्ठा i40e_tx_desc *tx_desc;
	काष्ठा i40e_ring *tx_ring;
	काष्ठा i40e_vsi *vsi;
	काष्ठा device *dev;
	dma_addr_t dma;
	u32 td_cmd = 0;
	u16 i;

	/* find existing Fसूची VSI */
	vsi = i40e_find_vsi_by_type(pf, I40E_VSI_Fसूची);
	अगर (!vsi)
		वापस -ENOENT;

	tx_ring = vsi->tx_rings[0];
	dev = tx_ring->dev;

	/* we need two descriptors to add/del a filter and we can रुको */
	क्रम (i = I40E_FD_CLEAN_DELAY; I40E_DESC_UNUSED(tx_ring) < 2; i--) अणु
		अगर (!i)
			वापस -EAGAIN;
		msleep_पूर्णांकerruptible(1);
	पूर्ण

	dma = dma_map_single(dev, raw_packet,
			     I40E_Fसूची_MAX_RAW_PACKET_SIZE, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, dma))
		जाओ dma_fail;

	/* grab the next descriptor */
	i = tx_ring->next_to_use;
	first = &tx_ring->tx_bi[i];
	i40e_fdir(tx_ring, fdir_data, add);

	/* Now program a dummy descriptor */
	i = tx_ring->next_to_use;
	tx_desc = I40E_TX_DESC(tx_ring, i);
	tx_buf = &tx_ring->tx_bi[i];

	tx_ring->next_to_use = ((i + 1) < tx_ring->count) ? i + 1 : 0;

	स_रखो(tx_buf, 0, माप(काष्ठा i40e_tx_buffer));

	/* record length, and DMA address */
	dma_unmap_len_set(tx_buf, len, I40E_Fसूची_MAX_RAW_PACKET_SIZE);
	dma_unmap_addr_set(tx_buf, dma, dma);

	tx_desc->buffer_addr = cpu_to_le64(dma);
	td_cmd = I40E_TXD_CMD | I40E_TX_DESC_CMD_DUMMY;

	tx_buf->tx_flags = I40E_TX_FLAGS_FD_SB;
	tx_buf->raw_buf = (व्योम *)raw_packet;

	tx_desc->cmd_type_offset_bsz =
		build_ctob(td_cmd, 0, I40E_Fसूची_MAX_RAW_PACKET_SIZE, 0);

	/* Force memory ग_लिखोs to complete beक्रमe letting h/w
	 * know there are new descriptors to fetch.
	 */
	wmb();

	/* Mark the data descriptor to be watched */
	first->next_to_watch = tx_desc;

	ग_लिखोl(tx_ring->next_to_use, tx_ring->tail);
	वापस 0;

dma_fail:
	वापस -1;
पूर्ण

/**
 * i40e_create_dummy_packet - Conकाष्ठाs dummy packet क्रम HW
 * @dummy_packet: pपुनः_स्मृतिated space क्रम dummy packet
 * @ipv4: is layer 3 packet of version 4 or 6
 * @l4proto: next level protocol used in data portion of l3
 * @data: filter data
 *
 * Returns address of layer 4 protocol dummy packet.
 **/
अटल अक्षर *i40e_create_dummy_packet(u8 *dummy_packet, bool ipv4, u8 l4proto,
				      काष्ठा i40e_fdir_filter *data)
अणु
	bool is_vlan = !!data->vlan_tag;
	काष्ठा vlan_hdr vlan;
	काष्ठा ipv6hdr ipv6;
	काष्ठा ethhdr eth;
	काष्ठा iphdr ip;
	u8 *पंचांगp;

	अगर (ipv4) अणु
		eth.h_proto = cpu_to_be16(ETH_P_IP);
		ip.protocol = l4proto;
		ip.version = 0x4;
		ip.ihl = 0x5;

		ip.daddr = data->dst_ip;
		ip.saddr = data->src_ip;
	पूर्ण अन्यथा अणु
		eth.h_proto = cpu_to_be16(ETH_P_IPV6);
		ipv6.nexthdr = l4proto;
		ipv6.version = 0x6;

		स_नकल(&ipv6.saddr.in6_u.u6_addr32, data->src_ip6,
		       माप(__be32) * 4);
		स_नकल(&ipv6.daddr.in6_u.u6_addr32, data->dst_ip6,
		       माप(__be32) * 4);
	पूर्ण

	अगर (is_vlan) अणु
		vlan.h_vlan_TCI = data->vlan_tag;
		vlan.h_vlan_encapsulated_proto = eth.h_proto;
		eth.h_proto = data->vlan_etype;
	पूर्ण

	पंचांगp = dummy_packet;
	स_नकल(पंचांगp, &eth, माप(eth));
	पंचांगp += माप(eth);

	अगर (is_vlan) अणु
		स_नकल(पंचांगp, &vlan, माप(vlan));
		पंचांगp += माप(vlan);
	पूर्ण

	अगर (ipv4) अणु
		स_नकल(पंचांगp, &ip, माप(ip));
		पंचांगp += माप(ip);
	पूर्ण अन्यथा अणु
		स_नकल(पंचांगp, &ipv6, माप(ipv6));
		पंचांगp += माप(ipv6);
	पूर्ण

	वापस पंचांगp;
पूर्ण

/**
 * i40e_create_dummy_udp_packet - helper function to create UDP packet
 * @raw_packet: pपुनः_स्मृतिated space क्रम dummy packet
 * @ipv4: is layer 3 packet of version 4 or 6
 * @l4proto: next level protocol used in data portion of l3
 * @data: filter data
 *
 * Helper function to populate udp fields.
 **/
अटल व्योम i40e_create_dummy_udp_packet(u8 *raw_packet, bool ipv4, u8 l4proto,
					 काष्ठा i40e_fdir_filter *data)
अणु
	काष्ठा udphdr *udp;
	u8 *पंचांगp;

	पंचांगp = i40e_create_dummy_packet(raw_packet, ipv4, IPPROTO_UDP, data);
	udp = (काष्ठा udphdr *)(पंचांगp);
	udp->dest = data->dst_port;
	udp->source = data->src_port;
पूर्ण

/**
 * i40e_create_dummy_tcp_packet - helper function to create TCP packet
 * @raw_packet: pपुनः_स्मृतिated space क्रम dummy packet
 * @ipv4: is layer 3 packet of version 4 or 6
 * @l4proto: next level protocol used in data portion of l3
 * @data: filter data
 *
 * Helper function to populate tcp fields.
 **/
अटल व्योम i40e_create_dummy_tcp_packet(u8 *raw_packet, bool ipv4, u8 l4proto,
					 काष्ठा i40e_fdir_filter *data)
अणु
	काष्ठा tcphdr *tcp;
	u8 *पंचांगp;
	/* Dummy tcp packet */
	अटल स्थिर अक्षर tcp_packet[] = अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0x50, 0x11, 0x0, 0x72, 0, 0, 0, 0पूर्ण;

	पंचांगp = i40e_create_dummy_packet(raw_packet, ipv4, IPPROTO_TCP, data);

	tcp = (काष्ठा tcphdr *)पंचांगp;
	स_नकल(tcp, tcp_packet, माप(tcp_packet));
	tcp->dest = data->dst_port;
	tcp->source = data->src_port;
पूर्ण

/**
 * i40e_create_dummy_sctp_packet - helper function to create SCTP packet
 * @raw_packet: pपुनः_स्मृतिated space क्रम dummy packet
 * @ipv4: is layer 3 packet of version 4 or 6
 * @l4proto: next level protocol used in data portion of l3
 * @data: filter data
 *
 * Helper function to populate sctp fields.
 **/
अटल व्योम i40e_create_dummy_sctp_packet(u8 *raw_packet, bool ipv4,
					  u8 l4proto,
					  काष्ठा i40e_fdir_filter *data)
अणु
	काष्ठा sctphdr *sctp;
	u8 *पंचांगp;

	पंचांगp = i40e_create_dummy_packet(raw_packet, ipv4, IPPROTO_SCTP, data);

	sctp = (काष्ठा sctphdr *)पंचांगp;
	sctp->dest = data->dst_port;
	sctp->source = data->src_port;
पूर्ण

/**
 * i40e_prepare_fdir_filter - Prepare and program fdir filter
 * @pf: physical function to attach filter to
 * @fd_data: filter data
 * @add: add or delete filter
 * @packet_addr: address of dummy packet, used in filtering
 * @payload_offset: offset from dummy packet address to user defined data
 * @pctype: Packet type क्रम which filter is used
 *
 * Helper function to offset data of dummy packet, program it and
 * handle errors.
 **/
अटल पूर्णांक i40e_prepare_fdir_filter(काष्ठा i40e_pf *pf,
				    काष्ठा i40e_fdir_filter *fd_data,
				    bool add, अक्षर *packet_addr,
				    पूर्णांक payload_offset, u8 pctype)
अणु
	पूर्णांक ret;

	अगर (fd_data->flex_filter) अणु
		u8 *payload;
		__be16 pattern = fd_data->flex_word;
		u16 off = fd_data->flex_offset;

		payload = packet_addr + payload_offset;

		/* If user provided vlan, offset payload by vlan header length */
		अगर (!!fd_data->vlan_tag)
			payload += VLAN_HLEN;

		*((__क्रमce __be16 *)(payload + off)) = pattern;
	पूर्ण

	fd_data->pctype = pctype;
	ret = i40e_program_fdir_filter(fd_data, packet_addr, pf, add);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "PCTYPE:%d, Filter command send failed for fd_id:%d (ret = %d)\n",
			 fd_data->pctype, fd_data->fd_id, ret);
		/* Free the packet buffer since it wasn't added to the ring */
		वापस -EOPNOTSUPP;
	पूर्ण अन्यथा अगर (I40E_DEBUG_FD & pf->hw.debug_mask) अणु
		अगर (add)
			dev_info(&pf->pdev->dev,
				 "Filter OK for PCTYPE %d loc = %d\n",
				 fd_data->pctype, fd_data->fd_id);
		अन्यथा
			dev_info(&pf->pdev->dev,
				 "Filter deleted for PCTYPE %d loc = %d\n",
				 fd_data->pctype, fd_data->fd_id);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * i40e_change_filter_num - Prepare and program fdir filter
 * @ipv4: is layer 3 packet of version 4 or 6
 * @add: add or delete filter
 * @ipv4_filter_num: field to update
 * @ipv6_filter_num: field to update
 *
 * Update filter number field क्रम pf.
 **/
अटल व्योम i40e_change_filter_num(bool ipv4, bool add, u16 *ipv4_filter_num,
				   u16 *ipv6_filter_num)
अणु
	अगर (add) अणु
		अगर (ipv4)
			(*ipv4_filter_num)++;
		अन्यथा
			(*ipv6_filter_num)++;
	पूर्ण अन्यथा अणु
		अगर (ipv4)
			(*ipv4_filter_num)--;
		अन्यथा
			(*ipv6_filter_num)--;
	पूर्ण
पूर्ण

#घोषणा IP_HEADER_OFFSET		14
#घोषणा I40E_UDPIP_DUMMY_PACKET_LEN	42
#घोषणा I40E_UDPIP6_DUMMY_PACKET_LEN	62
/**
 * i40e_add_del_fdir_udp - Add/Remove UDP filters
 * @vsi: poपूर्णांकer to the targeted VSI
 * @fd_data: the flow director data required क्रम the FDir descriptor
 * @add: true adds a filter, false हटाओs it
 * @ipv4: true is v4, false is v6
 *
 * Returns 0 अगर the filters were successfully added or हटाओd
 **/
अटल पूर्णांक i40e_add_del_fdir_udp(काष्ठा i40e_vsi *vsi,
				 काष्ठा i40e_fdir_filter *fd_data,
				 bool add,
				 bool ipv4)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	u8 *raw_packet;
	पूर्णांक ret;

	raw_packet = kzalloc(I40E_Fसूची_MAX_RAW_PACKET_SIZE, GFP_KERNEL);
	अगर (!raw_packet)
		वापस -ENOMEM;

	i40e_create_dummy_udp_packet(raw_packet, ipv4, IPPROTO_UDP, fd_data);

	अगर (ipv4)
		ret = i40e_prepare_fdir_filter
			(pf, fd_data, add, raw_packet,
			 I40E_UDPIP_DUMMY_PACKET_LEN,
			 I40E_FILTER_PCTYPE_NONF_IPV4_UDP);
	अन्यथा
		ret = i40e_prepare_fdir_filter
			(pf, fd_data, add, raw_packet,
			 I40E_UDPIP6_DUMMY_PACKET_LEN,
			 I40E_FILTER_PCTYPE_NONF_IPV6_UDP);

	अगर (ret) अणु
		kमुक्त(raw_packet);
		वापस ret;
	पूर्ण

	i40e_change_filter_num(ipv4, add, &pf->fd_udp4_filter_cnt,
			       &pf->fd_udp6_filter_cnt);

	वापस 0;
पूर्ण

#घोषणा I40E_TCPIP_DUMMY_PACKET_LEN	54
#घोषणा I40E_TCPIP6_DUMMY_PACKET_LEN	74
/**
 * i40e_add_del_fdir_tcp - Add/Remove TCPv4 filters
 * @vsi: poपूर्णांकer to the targeted VSI
 * @fd_data: the flow director data required क्रम the FDir descriptor
 * @add: true adds a filter, false हटाओs it
 * @ipv4: true is v4, false is v6
 *
 * Returns 0 अगर the filters were successfully added or हटाओd
 **/
अटल पूर्णांक i40e_add_del_fdir_tcp(काष्ठा i40e_vsi *vsi,
				 काष्ठा i40e_fdir_filter *fd_data,
				 bool add,
				 bool ipv4)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	u8 *raw_packet;
	पूर्णांक ret;

	raw_packet = kzalloc(I40E_Fसूची_MAX_RAW_PACKET_SIZE, GFP_KERNEL);
	अगर (!raw_packet)
		वापस -ENOMEM;

	i40e_create_dummy_tcp_packet(raw_packet, ipv4, IPPROTO_TCP, fd_data);
	अगर (ipv4)
		ret = i40e_prepare_fdir_filter
			(pf, fd_data, add, raw_packet,
			 I40E_TCPIP_DUMMY_PACKET_LEN,
			 I40E_FILTER_PCTYPE_NONF_IPV4_TCP);
	अन्यथा
		ret = i40e_prepare_fdir_filter
			(pf, fd_data, add, raw_packet,
			 I40E_TCPIP6_DUMMY_PACKET_LEN,
			 I40E_FILTER_PCTYPE_NONF_IPV6_TCP);

	अगर (ret) अणु
		kमुक्त(raw_packet);
		वापस ret;
	पूर्ण

	i40e_change_filter_num(ipv4, add, &pf->fd_tcp4_filter_cnt,
			       &pf->fd_tcp6_filter_cnt);

	अगर (add) अणु
		अगर ((pf->flags & I40E_FLAG_FD_ATR_ENABLED) &&
		    I40E_DEBUG_FD & pf->hw.debug_mask)
			dev_info(&pf->pdev->dev, "Forcing ATR off, sideband rules for TCP/IPv4 flow being applied\n");
		set_bit(__I40E_FD_ATR_AUTO_DISABLED, pf->state);
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा I40E_SCTPIP_DUMMY_PACKET_LEN	46
#घोषणा I40E_SCTPIP6_DUMMY_PACKET_LEN	66
/**
 * i40e_add_del_fdir_sctp - Add/Remove SCTPv4 Flow Director filters क्रम
 * a specअगरic flow spec
 * @vsi: poपूर्णांकer to the targeted VSI
 * @fd_data: the flow director data required क्रम the FDir descriptor
 * @add: true adds a filter, false हटाओs it
 * @ipv4: true is v4, false is v6
 *
 * Returns 0 अगर the filters were successfully added or हटाओd
 **/
अटल पूर्णांक i40e_add_del_fdir_sctp(काष्ठा i40e_vsi *vsi,
				  काष्ठा i40e_fdir_filter *fd_data,
				  bool add,
				  bool ipv4)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	u8 *raw_packet;
	पूर्णांक ret;

	raw_packet = kzalloc(I40E_Fसूची_MAX_RAW_PACKET_SIZE, GFP_KERNEL);
	अगर (!raw_packet)
		वापस -ENOMEM;

	i40e_create_dummy_sctp_packet(raw_packet, ipv4, IPPROTO_SCTP, fd_data);

	अगर (ipv4)
		ret = i40e_prepare_fdir_filter
			(pf, fd_data, add, raw_packet,
			 I40E_SCTPIP_DUMMY_PACKET_LEN,
			 I40E_FILTER_PCTYPE_NONF_IPV4_SCTP);
	अन्यथा
		ret = i40e_prepare_fdir_filter
			(pf, fd_data, add, raw_packet,
			 I40E_SCTPIP6_DUMMY_PACKET_LEN,
			 I40E_FILTER_PCTYPE_NONF_IPV6_SCTP);

	अगर (ret) अणु
		kमुक्त(raw_packet);
		वापस ret;
	पूर्ण

	i40e_change_filter_num(ipv4, add, &pf->fd_sctp4_filter_cnt,
			       &pf->fd_sctp6_filter_cnt);

	वापस 0;
पूर्ण

#घोषणा I40E_IP_DUMMY_PACKET_LEN	34
#घोषणा I40E_IP6_DUMMY_PACKET_LEN	54
/**
 * i40e_add_del_fdir_ip - Add/Remove IPv4 Flow Director filters क्रम
 * a specअगरic flow spec
 * @vsi: poपूर्णांकer to the targeted VSI
 * @fd_data: the flow director data required क्रम the FDir descriptor
 * @add: true adds a filter, false हटाओs it
 * @ipv4: true is v4, false is v6
 *
 * Returns 0 अगर the filters were successfully added or हटाओd
 **/
अटल पूर्णांक i40e_add_del_fdir_ip(काष्ठा i40e_vsi *vsi,
				काष्ठा i40e_fdir_filter *fd_data,
				bool add,
				bool ipv4)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक payload_offset;
	u8 *raw_packet;
	पूर्णांक iter_start;
	पूर्णांक iter_end;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (ipv4) अणु
		iter_start = I40E_FILTER_PCTYPE_NONF_IPV4_OTHER;
		iter_end = I40E_FILTER_PCTYPE_FRAG_IPV4;
	पूर्ण अन्यथा अणु
		iter_start = I40E_FILTER_PCTYPE_NONF_IPV6_OTHER;
		iter_end = I40E_FILTER_PCTYPE_FRAG_IPV6;
	पूर्ण

	क्रम (i = iter_start; i <= iter_end; i++) अणु
		raw_packet = kzalloc(I40E_Fसूची_MAX_RAW_PACKET_SIZE, GFP_KERNEL);
		अगर (!raw_packet)
			वापस -ENOMEM;

		/* IPv6 no header option dअगरfers from IPv4 */
		(व्योम)i40e_create_dummy_packet
			(raw_packet, ipv4, (ipv4) ? IPPROTO_IP : IPPROTO_NONE,
			 fd_data);

		payload_offset = (ipv4) ? I40E_IP_DUMMY_PACKET_LEN :
			I40E_IP6_DUMMY_PACKET_LEN;
		ret = i40e_prepare_fdir_filter(pf, fd_data, add, raw_packet,
					       payload_offset, i);
		अगर (ret)
			जाओ err;
	पूर्ण

	i40e_change_filter_num(ipv4, add, &pf->fd_ip4_filter_cnt,
			       &pf->fd_ip6_filter_cnt);

	वापस 0;
err:
	kमुक्त(raw_packet);
	वापस ret;
पूर्ण

/**
 * i40e_add_del_fdir - Build raw packets to add/del fdir filter
 * @vsi: poपूर्णांकer to the targeted VSI
 * @input: filter to add or delete
 * @add: true adds a filter, false हटाओs it
 *
 **/
पूर्णांक i40e_add_del_fdir(काष्ठा i40e_vsi *vsi,
		      काष्ठा i40e_fdir_filter *input, bool add)
अणु
	क्रमागत ip_ver अणु ipv6 = 0, ipv4 = 1 पूर्ण;
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक ret;

	चयन (input->flow_type & ~FLOW_EXT) अणु
	हाल TCP_V4_FLOW:
		ret = i40e_add_del_fdir_tcp(vsi, input, add, ipv4);
		अवरोध;
	हाल UDP_V4_FLOW:
		ret = i40e_add_del_fdir_udp(vsi, input, add, ipv4);
		अवरोध;
	हाल SCTP_V4_FLOW:
		ret = i40e_add_del_fdir_sctp(vsi, input, add, ipv4);
		अवरोध;
	हाल TCP_V6_FLOW:
		ret = i40e_add_del_fdir_tcp(vsi, input, add, ipv6);
		अवरोध;
	हाल UDP_V6_FLOW:
		ret = i40e_add_del_fdir_udp(vsi, input, add, ipv6);
		अवरोध;
	हाल SCTP_V6_FLOW:
		ret = i40e_add_del_fdir_sctp(vsi, input, add, ipv6);
		अवरोध;
	हाल IP_USER_FLOW:
		चयन (input->ipl4_proto) अणु
		हाल IPPROTO_TCP:
			ret = i40e_add_del_fdir_tcp(vsi, input, add, ipv4);
			अवरोध;
		हाल IPPROTO_UDP:
			ret = i40e_add_del_fdir_udp(vsi, input, add, ipv4);
			अवरोध;
		हाल IPPROTO_SCTP:
			ret = i40e_add_del_fdir_sctp(vsi, input, add, ipv4);
			अवरोध;
		हाल IPPROTO_IP:
			ret = i40e_add_del_fdir_ip(vsi, input, add, ipv4);
			अवरोध;
		शेष:
			/* We cannot support masking based on protocol */
			dev_info(&pf->pdev->dev, "Unsupported IPv4 protocol 0x%02x\n",
				 input->ipl4_proto);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल IPV6_USER_FLOW:
		चयन (input->ipl4_proto) अणु
		हाल IPPROTO_TCP:
			ret = i40e_add_del_fdir_tcp(vsi, input, add, ipv6);
			अवरोध;
		हाल IPPROTO_UDP:
			ret = i40e_add_del_fdir_udp(vsi, input, add, ipv6);
			अवरोध;
		हाल IPPROTO_SCTP:
			ret = i40e_add_del_fdir_sctp(vsi, input, add, ipv6);
			अवरोध;
		हाल IPPROTO_IP:
			ret = i40e_add_del_fdir_ip(vsi, input, add, ipv6);
			अवरोध;
		शेष:
			/* We cannot support masking based on protocol */
			dev_info(&pf->pdev->dev, "Unsupported IPv6 protocol 0x%02x\n",
				 input->ipl4_proto);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		dev_info(&pf->pdev->dev, "Unsupported flow type 0x%02x\n",
			 input->flow_type);
		वापस -EINVAL;
	पूर्ण

	/* The buffer allocated here will be normally be मुक्तd by
	 * i40e_clean_fdir_tx_irq() as it reclaims resources after transmit
	 * completion. In the event of an error adding the buffer to the Fसूची
	 * ring, it will immediately be मुक्तd. It may also be मुक्तd by
	 * i40e_clean_tx_ring() when closing the VSI.
	 */
	वापस ret;
पूर्ण

/**
 * i40e_fd_handle_status - check the Programming Status क्रम FD
 * @rx_ring: the Rx ring क्रम this descriptor
 * @qword0_raw: qword0
 * @qword1: qword1 after le_to_cpu
 * @prog_id: the id originally used क्रम programming
 *
 * This is used to verअगरy अगर the FD programming or invalidation
 * requested by SW to the HW is successful or not and take actions accordingly.
 **/
अटल व्योम i40e_fd_handle_status(काष्ठा i40e_ring *rx_ring, u64 qword0_raw,
				  u64 qword1, u8 prog_id)
अणु
	काष्ठा i40e_pf *pf = rx_ring->vsi->back;
	काष्ठा pci_dev *pdev = pf->pdev;
	काष्ठा i40e_16b_rx_wb_qw0 *qw0;
	u32 fcnt_prog, fcnt_avail;
	u32 error;

	qw0 = (काष्ठा i40e_16b_rx_wb_qw0 *)&qword0_raw;
	error = (qword1 & I40E_RX_PROG_STATUS_DESC_QW1_ERROR_MASK) >>
		I40E_RX_PROG_STATUS_DESC_QW1_ERROR_SHIFT;

	अगर (error == BIT(I40E_RX_PROG_STATUS_DESC_FD_TBL_FULL_SHIFT)) अणु
		pf->fd_inv = le32_to_cpu(qw0->hi_dword.fd_id);
		अगर (qw0->hi_dword.fd_id != 0 ||
		    (I40E_DEBUG_FD & pf->hw.debug_mask))
			dev_warn(&pdev->dev, "ntuple filter loc = %d, could not be added\n",
				 pf->fd_inv);

		/* Check अगर the programming error is क्रम ATR.
		 * If so, स्वतः disable ATR and set a state क्रम
		 * flush in progress. Next समय we come here अगर flush is in
		 * progress करो nothing, once flush is complete the state will
		 * be cleared.
		 */
		अगर (test_bit(__I40E_FD_FLUSH_REQUESTED, pf->state))
			वापस;

		pf->fd_add_err++;
		/* store the current atr filter count */
		pf->fd_atr_cnt = i40e_get_current_atr_cnt(pf);

		अगर (qw0->hi_dword.fd_id == 0 &&
		    test_bit(__I40E_FD_SB_AUTO_DISABLED, pf->state)) अणु
			/* These set_bit() calls aren't atomic with the
			 * test_bit() here, but worse हाल we potentially
			 * disable ATR and queue a flush right after SB
			 * support is re-enabled. That shouldn't cause an
			 * issue in practice
			 */
			set_bit(__I40E_FD_ATR_AUTO_DISABLED, pf->state);
			set_bit(__I40E_FD_FLUSH_REQUESTED, pf->state);
		पूर्ण

		/* filter programming failed most likely due to table full */
		fcnt_prog = i40e_get_global_fd_count(pf);
		fcnt_avail = pf->fdir_pf_filter_count;
		/* If ATR is running fcnt_prog can quickly change,
		 * अगर we are very बंद to full, it makes sense to disable
		 * FD ATR/SB and then re-enable it when there is room.
		 */
		अगर (fcnt_prog >= (fcnt_avail - I40E_Fसूची_BUFFER_FULL_MARGIN)) अणु
			अगर ((pf->flags & I40E_FLAG_FD_SB_ENABLED) &&
			    !test_and_set_bit(__I40E_FD_SB_AUTO_DISABLED,
					      pf->state))
				अगर (I40E_DEBUG_FD & pf->hw.debug_mask)
					dev_warn(&pdev->dev, "FD filter space full, new ntuple rules will not be added\n");
		पूर्ण
	पूर्ण अन्यथा अगर (error == BIT(I40E_RX_PROG_STATUS_DESC_NO_FD_ENTRY_SHIFT)) अणु
		अगर (I40E_DEBUG_FD & pf->hw.debug_mask)
			dev_info(&pdev->dev, "ntuple filter fd_id = %d, could not be removed\n",
				 qw0->hi_dword.fd_id);
	पूर्ण
पूर्ण

/**
 * i40e_unmap_and_मुक्त_tx_resource - Release a Tx buffer
 * @ring:      the ring that owns the buffer
 * @tx_buffer: the buffer to मुक्त
 **/
अटल व्योम i40e_unmap_and_मुक्त_tx_resource(काष्ठा i40e_ring *ring,
					    काष्ठा i40e_tx_buffer *tx_buffer)
अणु
	अगर (tx_buffer->skb) अणु
		अगर (tx_buffer->tx_flags & I40E_TX_FLAGS_FD_SB)
			kमुक्त(tx_buffer->raw_buf);
		अन्यथा अगर (ring_is_xdp(ring))
			xdp_वापस_frame(tx_buffer->xdpf);
		अन्यथा
			dev_kमुक्त_skb_any(tx_buffer->skb);
		अगर (dma_unmap_len(tx_buffer, len))
			dma_unmap_single(ring->dev,
					 dma_unmap_addr(tx_buffer, dma),
					 dma_unmap_len(tx_buffer, len),
					 DMA_TO_DEVICE);
	पूर्ण अन्यथा अगर (dma_unmap_len(tx_buffer, len)) अणु
		dma_unmap_page(ring->dev,
			       dma_unmap_addr(tx_buffer, dma),
			       dma_unmap_len(tx_buffer, len),
			       DMA_TO_DEVICE);
	पूर्ण

	tx_buffer->next_to_watch = शून्य;
	tx_buffer->skb = शून्य;
	dma_unmap_len_set(tx_buffer, len, 0);
	/* tx_buffer must be completely set up in the transmit path */
पूर्ण

/**
 * i40e_clean_tx_ring - Free any empty Tx buffers
 * @tx_ring: ring to be cleaned
 **/
व्योम i40e_clean_tx_ring(काष्ठा i40e_ring *tx_ring)
अणु
	अचिन्हित दीर्घ bi_size;
	u16 i;

	अगर (ring_is_xdp(tx_ring) && tx_ring->xsk_pool) अणु
		i40e_xsk_clean_tx_ring(tx_ring);
	पूर्ण अन्यथा अणु
		/* ring alपढ़ोy cleared, nothing to करो */
		अगर (!tx_ring->tx_bi)
			वापस;

		/* Free all the Tx ring sk_buffs */
		क्रम (i = 0; i < tx_ring->count; i++)
			i40e_unmap_and_मुक्त_tx_resource(tx_ring,
							&tx_ring->tx_bi[i]);
	पूर्ण

	bi_size = माप(काष्ठा i40e_tx_buffer) * tx_ring->count;
	स_रखो(tx_ring->tx_bi, 0, bi_size);

	/* Zero out the descriptor ring */
	स_रखो(tx_ring->desc, 0, tx_ring->size);

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;

	अगर (!tx_ring->netdev)
		वापस;

	/* cleanup Tx queue statistics */
	netdev_tx_reset_queue(txring_txq(tx_ring));
पूर्ण

/**
 * i40e_मुक्त_tx_resources - Free Tx resources per queue
 * @tx_ring: Tx descriptor ring क्रम a specअगरic queue
 *
 * Free all transmit software resources
 **/
व्योम i40e_मुक्त_tx_resources(काष्ठा i40e_ring *tx_ring)
अणु
	i40e_clean_tx_ring(tx_ring);
	kमुक्त(tx_ring->tx_bi);
	tx_ring->tx_bi = शून्य;
	kमुक्त(tx_ring->xsk_descs);
	tx_ring->xsk_descs = शून्य;

	अगर (tx_ring->desc) अणु
		dma_मुक्त_coherent(tx_ring->dev, tx_ring->size,
				  tx_ring->desc, tx_ring->dma);
		tx_ring->desc = शून्य;
	पूर्ण
पूर्ण

/**
 * i40e_get_tx_pending - how many tx descriptors not processed
 * @ring: the ring of descriptors
 * @in_sw: use SW variables
 *
 * Since there is no access to the ring head रेजिस्टर
 * in XL710, we need to use our local copies
 **/
u32 i40e_get_tx_pending(काष्ठा i40e_ring *ring, bool in_sw)
अणु
	u32 head, tail;

	अगर (!in_sw) अणु
		head = i40e_get_head(ring);
		tail = पढ़ोl(ring->tail);
	पूर्ण अन्यथा अणु
		head = ring->next_to_clean;
		tail = ring->next_to_use;
	पूर्ण

	अगर (head != tail)
		वापस (head < tail) ?
			tail - head : (tail + ring->count - head);

	वापस 0;
पूर्ण

/**
 * i40e_detect_recover_hung - Function to detect and recover hung_queues
 * @vsi:  poपूर्णांकer to vsi काष्ठा with tx queues
 *
 * VSI has netdev and netdev has TX queues. This function is to check each of
 * those TX queues अगर they are hung, trigger recovery by issuing SW पूर्णांकerrupt.
 **/
व्योम i40e_detect_recover_hung(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_ring *tx_ring = शून्य;
	काष्ठा net_device *netdev;
	अचिन्हित पूर्णांक i;
	पूर्णांक packets;

	अगर (!vsi)
		वापस;

	अगर (test_bit(__I40E_VSI_DOWN, vsi->state))
		वापस;

	netdev = vsi->netdev;
	अगर (!netdev)
		वापस;

	अगर (!netअगर_carrier_ok(netdev))
		वापस;

	क्रम (i = 0; i < vsi->num_queue_pairs; i++) अणु
		tx_ring = vsi->tx_rings[i];
		अगर (tx_ring && tx_ring->desc) अणु
			/* If packet counter has not changed the queue is
			 * likely stalled, so क्रमce an पूर्णांकerrupt क्रम this
			 * queue.
			 *
			 * prev_pkt_ctr would be negative अगर there was no
			 * pending work.
			 */
			packets = tx_ring->stats.packets & पूर्णांक_उच्च;
			अगर (tx_ring->tx_stats.prev_pkt_ctr == packets) अणु
				i40e_क्रमce_wb(vsi, tx_ring->q_vector);
				जारी;
			पूर्ण

			/* Memory barrier between पढ़ो of packet count and call
			 * to i40e_get_tx_pending()
			 */
			smp_rmb();
			tx_ring->tx_stats.prev_pkt_ctr =
			    i40e_get_tx_pending(tx_ring, true) ? packets : -1;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * i40e_clean_tx_irq - Reclaim resources after transmit completes
 * @vsi: the VSI we care about
 * @tx_ring: Tx ring to clean
 * @napi_budget: Used to determine अगर we are in netpoll
 *
 * Returns true अगर there's any budget left (e.g. the clean is finished)
 **/
अटल bool i40e_clean_tx_irq(काष्ठा i40e_vsi *vsi,
			      काष्ठा i40e_ring *tx_ring, पूर्णांक napi_budget)
अणु
	पूर्णांक i = tx_ring->next_to_clean;
	काष्ठा i40e_tx_buffer *tx_buf;
	काष्ठा i40e_tx_desc *tx_head;
	काष्ठा i40e_tx_desc *tx_desc;
	अचिन्हित पूर्णांक total_bytes = 0, total_packets = 0;
	अचिन्हित पूर्णांक budget = vsi->work_limit;

	tx_buf = &tx_ring->tx_bi[i];
	tx_desc = I40E_TX_DESC(tx_ring, i);
	i -= tx_ring->count;

	tx_head = I40E_TX_DESC(tx_ring, i40e_get_head(tx_ring));

	करो अणु
		काष्ठा i40e_tx_desc *eop_desc = tx_buf->next_to_watch;

		/* अगर next_to_watch is not set then there is no work pending */
		अगर (!eop_desc)
			अवरोध;

		/* prevent any other पढ़ोs prior to eop_desc */
		smp_rmb();

		i40e_trace(clean_tx_irq, tx_ring, tx_desc, tx_buf);
		/* we have caught up to head, no work left to करो */
		अगर (tx_head == tx_desc)
			अवरोध;

		/* clear next_to_watch to prevent false hangs */
		tx_buf->next_to_watch = शून्य;

		/* update the statistics क्रम this packet */
		total_bytes += tx_buf->bytecount;
		total_packets += tx_buf->gso_segs;

		/* मुक्त the skb/XDP data */
		अगर (ring_is_xdp(tx_ring))
			xdp_वापस_frame(tx_buf->xdpf);
		अन्यथा
			napi_consume_skb(tx_buf->skb, napi_budget);

		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buf, dma),
				 dma_unmap_len(tx_buf, len),
				 DMA_TO_DEVICE);

		/* clear tx_buffer data */
		tx_buf->skb = शून्य;
		dma_unmap_len_set(tx_buf, len, 0);

		/* unmap reमुख्यing buffers */
		जबतक (tx_desc != eop_desc) अणु
			i40e_trace(clean_tx_irq_unmap,
				   tx_ring, tx_desc, tx_buf);

			tx_buf++;
			tx_desc++;
			i++;
			अगर (unlikely(!i)) अणु
				i -= tx_ring->count;
				tx_buf = tx_ring->tx_bi;
				tx_desc = I40E_TX_DESC(tx_ring, 0);
			पूर्ण

			/* unmap any reमुख्यing paged data */
			अगर (dma_unmap_len(tx_buf, len)) अणु
				dma_unmap_page(tx_ring->dev,
					       dma_unmap_addr(tx_buf, dma),
					       dma_unmap_len(tx_buf, len),
					       DMA_TO_DEVICE);
				dma_unmap_len_set(tx_buf, len, 0);
			पूर्ण
		पूर्ण

		/* move us one more past the eop_desc क्रम start of next pkt */
		tx_buf++;
		tx_desc++;
		i++;
		अगर (unlikely(!i)) अणु
			i -= tx_ring->count;
			tx_buf = tx_ring->tx_bi;
			tx_desc = I40E_TX_DESC(tx_ring, 0);
		पूर्ण

		prefetch(tx_desc);

		/* update budget accounting */
		budget--;
	पूर्ण जबतक (likely(budget));

	i += tx_ring->count;
	tx_ring->next_to_clean = i;
	i40e_update_tx_stats(tx_ring, total_packets, total_bytes);
	i40e_arm_wb(tx_ring, vsi, budget);

	अगर (ring_is_xdp(tx_ring))
		वापस !!budget;

	/* notअगरy netdev of completed buffers */
	netdev_tx_completed_queue(txring_txq(tx_ring),
				  total_packets, total_bytes);

#घोषणा TX_WAKE_THRESHOLD ((s16)(DESC_NEEDED * 2))
	अगर (unlikely(total_packets && netअगर_carrier_ok(tx_ring->netdev) &&
		     (I40E_DESC_UNUSED(tx_ring) >= TX_WAKE_THRESHOLD))) अणु
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();
		अगर (__netअगर_subqueue_stopped(tx_ring->netdev,
					     tx_ring->queue_index) &&
		   !test_bit(__I40E_VSI_DOWN, vsi->state)) अणु
			netअगर_wake_subqueue(tx_ring->netdev,
					    tx_ring->queue_index);
			++tx_ring->tx_stats.restart_queue;
		पूर्ण
	पूर्ण

	वापस !!budget;
पूर्ण

/**
 * i40e_enable_wb_on_itr - Arm hardware to करो a wb, पूर्णांकerrupts are not enabled
 * @vsi: the VSI we care about
 * @q_vector: the vector on which to enable ग_लिखोback
 *
 **/
अटल व्योम i40e_enable_wb_on_itr(काष्ठा i40e_vsi *vsi,
				  काष्ठा i40e_q_vector *q_vector)
अणु
	u16 flags = q_vector->tx.ring[0].flags;
	u32 val;

	अगर (!(flags & I40E_TXR_FLAGS_WB_ON_ITR))
		वापस;

	अगर (q_vector->arm_wb_state)
		वापस;

	अगर (vsi->back->flags & I40E_FLAG_MSIX_ENABLED) अणु
		val = I40E_PFINT_DYN_CTLN_WB_ON_ITR_MASK |
		      I40E_PFINT_DYN_CTLN_ITR_INDX_MASK; /* set noitr */

		wr32(&vsi->back->hw,
		     I40E_PFINT_DYN_CTLN(q_vector->reg_idx),
		     val);
	पूर्ण अन्यथा अणु
		val = I40E_PFINT_DYN_CTL0_WB_ON_ITR_MASK |
		      I40E_PFINT_DYN_CTL0_ITR_INDX_MASK; /* set noitr */

		wr32(&vsi->back->hw, I40E_PFINT_DYN_CTL0, val);
	पूर्ण
	q_vector->arm_wb_state = true;
पूर्ण

/**
 * i40e_क्रमce_wb - Issue SW Interrupt so HW करोes a wb
 * @vsi: the VSI we care about
 * @q_vector: the vector  on which to क्रमce ग_लिखोback
 *
 **/
व्योम i40e_क्रमce_wb(काष्ठा i40e_vsi *vsi, काष्ठा i40e_q_vector *q_vector)
अणु
	अगर (vsi->back->flags & I40E_FLAG_MSIX_ENABLED) अणु
		u32 val = I40E_PFINT_DYN_CTLN_INTENA_MASK |
			  I40E_PFINT_DYN_CTLN_ITR_INDX_MASK | /* set noitr */
			  I40E_PFINT_DYN_CTLN_SWINT_TRIG_MASK |
			  I40E_PFINT_DYN_CTLN_SW_ITR_INDX_ENA_MASK;
			  /* allow 00 to be written to the index */

		wr32(&vsi->back->hw,
		     I40E_PFINT_DYN_CTLN(q_vector->reg_idx), val);
	पूर्ण अन्यथा अणु
		u32 val = I40E_PFINT_DYN_CTL0_INTENA_MASK |
			  I40E_PFINT_DYN_CTL0_ITR_INDX_MASK | /* set noitr */
			  I40E_PFINT_DYN_CTL0_SWINT_TRIG_MASK |
			  I40E_PFINT_DYN_CTL0_SW_ITR_INDX_ENA_MASK;
			/* allow 00 to be written to the index */

		wr32(&vsi->back->hw, I40E_PFINT_DYN_CTL0, val);
	पूर्ण
पूर्ण

अटल अंतरभूत bool i40e_container_is_rx(काष्ठा i40e_q_vector *q_vector,
					काष्ठा i40e_ring_container *rc)
अणु
	वापस &q_vector->rx == rc;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक i40e_itr_भागisor(काष्ठा i40e_q_vector *q_vector)
अणु
	अचिन्हित पूर्णांक भागisor;

	चयन (q_vector->vsi->back->hw.phy.link_info.link_speed) अणु
	हाल I40E_LINK_SPEED_40GB:
		भागisor = I40E_ITR_ADAPTIVE_MIN_INC * 1024;
		अवरोध;
	हाल I40E_LINK_SPEED_25GB:
	हाल I40E_LINK_SPEED_20GB:
		भागisor = I40E_ITR_ADAPTIVE_MIN_INC * 512;
		अवरोध;
	शेष:
	हाल I40E_LINK_SPEED_10GB:
		भागisor = I40E_ITR_ADAPTIVE_MIN_INC * 256;
		अवरोध;
	हाल I40E_LINK_SPEED_1GB:
	हाल I40E_LINK_SPEED_100MB:
		भागisor = I40E_ITR_ADAPTIVE_MIN_INC * 32;
		अवरोध;
	पूर्ण

	वापस भागisor;
पूर्ण

/**
 * i40e_update_itr - update the dynamic ITR value based on statistics
 * @q_vector: काष्ठाure containing पूर्णांकerrupt and ring inक्रमmation
 * @rc: काष्ठाure containing ring perक्रमmance data
 *
 * Stores a new ITR value based on packets and byte
 * counts during the last पूर्णांकerrupt.  The advantage of per पूर्णांकerrupt
 * computation is faster updates and more accurate ITR क्रम the current
 * traffic pattern.  Constants in this function were computed
 * based on theoretical maximum wire speed and thresholds were set based
 * on testing data as well as attempting to minimize response समय
 * जबतक increasing bulk throughput.
 **/
अटल व्योम i40e_update_itr(काष्ठा i40e_q_vector *q_vector,
			    काष्ठा i40e_ring_container *rc)
अणु
	अचिन्हित पूर्णांक avg_wire_size, packets, bytes, itr;
	अचिन्हित दीर्घ next_update = jअगरfies;

	/* If we करोn't have any rings just leave ourselves set क्रम maximum
	 * possible latency so we take ourselves out of the equation.
	 */
	अगर (!rc->ring || !ITR_IS_DYNAMIC(rc->ring->itr_setting))
		वापस;

	/* For Rx we want to push the delay up and शेष to low latency.
	 * क्रम Tx we want to pull the delay करोwn and शेष to high latency.
	 */
	itr = i40e_container_is_rx(q_vector, rc) ?
	      I40E_ITR_ADAPTIVE_MIN_USECS | I40E_ITR_ADAPTIVE_LATENCY :
	      I40E_ITR_ADAPTIVE_MAX_USECS | I40E_ITR_ADAPTIVE_LATENCY;

	/* If we didn't update within up to 1 - 2 jअगरfies we can assume
	 * that either packets are coming in so slow there hasn't been
	 * any work, or that there is so much work that NAPI is dealing
	 * with पूर्णांकerrupt moderation and we करोn't need to करो anything.
	 */
	अगर (समय_after(next_update, rc->next_update))
		जाओ clear_counts;

	/* If itr_countकरोwn is set it means we programmed an ITR within
	 * the last 4 पूर्णांकerrupt cycles. This has a side effect of us
	 * potentially firing an early पूर्णांकerrupt. In order to work around
	 * this we need to throw out any data received क्रम a few
	 * पूर्णांकerrupts following the update.
	 */
	अगर (q_vector->itr_countकरोwn) अणु
		itr = rc->target_itr;
		जाओ clear_counts;
	पूर्ण

	packets = rc->total_packets;
	bytes = rc->total_bytes;

	अगर (i40e_container_is_rx(q_vector, rc)) अणु
		/* If Rx there are 1 to 4 packets and bytes are less than
		 * 9000 assume insufficient data to use bulk rate limiting
		 * approach unless Tx is alपढ़ोy in bulk rate limiting. We
		 * are likely latency driven.
		 */
		अगर (packets && packets < 4 && bytes < 9000 &&
		    (q_vector->tx.target_itr & I40E_ITR_ADAPTIVE_LATENCY)) अणु
			itr = I40E_ITR_ADAPTIVE_LATENCY;
			जाओ adjust_by_size;
		पूर्ण
	पूर्ण अन्यथा अगर (packets < 4) अणु
		/* If we have Tx and Rx ITR maxed and Tx ITR is running in
		 * bulk mode and we are receiving 4 or fewer packets just
		 * reset the ITR_ADAPTIVE_LATENCY bit क्रम latency mode so
		 * that the Rx can relax.
		 */
		अगर (rc->target_itr == I40E_ITR_ADAPTIVE_MAX_USECS &&
		    (q_vector->rx.target_itr & I40E_ITR_MASK) ==
		     I40E_ITR_ADAPTIVE_MAX_USECS)
			जाओ clear_counts;
	पूर्ण अन्यथा अगर (packets > 32) अणु
		/* If we have processed over 32 packets in a single पूर्णांकerrupt
		 * क्रम Tx assume we need to चयन over to "bulk" mode.
		 */
		rc->target_itr &= ~I40E_ITR_ADAPTIVE_LATENCY;
	पूर्ण

	/* We have no packets to actually measure against. This means
	 * either one of the other queues on this vector is active or
	 * we are a Tx queue करोing TSO with too high of an पूर्णांकerrupt rate.
	 *
	 * Between 4 and 56 we can assume that our current पूर्णांकerrupt delay
	 * is only slightly too low. As such we should increase it by a small
	 * fixed amount.
	 */
	अगर (packets < 56) अणु
		itr = rc->target_itr + I40E_ITR_ADAPTIVE_MIN_INC;
		अगर ((itr & I40E_ITR_MASK) > I40E_ITR_ADAPTIVE_MAX_USECS) अणु
			itr &= I40E_ITR_ADAPTIVE_LATENCY;
			itr += I40E_ITR_ADAPTIVE_MAX_USECS;
		पूर्ण
		जाओ clear_counts;
	पूर्ण

	अगर (packets <= 256) अणु
		itr = min(q_vector->tx.current_itr, q_vector->rx.current_itr);
		itr &= I40E_ITR_MASK;

		/* Between 56 and 112 is our "goldilocks" zone where we are
		 * working out "just right". Just report that our current
		 * ITR is good क्रम us.
		 */
		अगर (packets <= 112)
			जाओ clear_counts;

		/* If packet count is 128 or greater we are likely looking
		 * at a slight overrun of the delay we want. Try halving
		 * our delay to see अगर that will cut the number of packets
		 * in half per पूर्णांकerrupt.
		 */
		itr /= 2;
		itr &= I40E_ITR_MASK;
		अगर (itr < I40E_ITR_ADAPTIVE_MIN_USECS)
			itr = I40E_ITR_ADAPTIVE_MIN_USECS;

		जाओ clear_counts;
	पूर्ण

	/* The paths below assume we are dealing with a bulk ITR since
	 * number of packets is greater than 256. We are just going to have
	 * to compute a value and try to bring the count under control,
	 * though क्रम smaller packet sizes there isn't much we can करो as
	 * NAPI polling will likely be kicking in sooner rather than later.
	 */
	itr = I40E_ITR_ADAPTIVE_BULK;

adjust_by_size:
	/* If packet counts are 256 or greater we can assume we have a gross
	 * overestimation of what the rate should be. Instead of trying to fine
	 * tune it just use the क्रमmula below to try and dial in an exact value
	 * give the current packet size of the frame.
	 */
	avg_wire_size = bytes / packets;

	/* The following is a crude approximation of:
	 *  wmem_शेष / (size + overhead) = desired_pkts_per_पूर्णांक
	 *  rate / bits_per_byte / (size + ethernet overhead) = pkt_rate
	 *  (desired_pkt_rate / pkt_rate) * usecs_per_sec = ITR value
	 *
	 * Assuming wmem_शेष is 212992 and overhead is 640 bytes per
	 * packet, (256 skb, 64 headroom, 320 shared info), we can reduce the
	 * क्रमmula करोwn to
	 *
	 *  (170 * (size + 24)) / (size + 640) = ITR
	 *
	 * We first करो some math on the packet size and then finally bitshअगरt
	 * by 8 after rounding up. We also have to account क्रम PCIe link speed
	 * dअगरference as ITR scales based on this.
	 */
	अगर (avg_wire_size <= 60) अणु
		/* Start at 250k पूर्णांकs/sec */
		avg_wire_size = 4096;
	पूर्ण अन्यथा अगर (avg_wire_size <= 380) अणु
		/* 250K पूर्णांकs/sec to 60K पूर्णांकs/sec */
		avg_wire_size *= 40;
		avg_wire_size += 1696;
	पूर्ण अन्यथा अगर (avg_wire_size <= 1084) अणु
		/* 60K पूर्णांकs/sec to 36K पूर्णांकs/sec */
		avg_wire_size *= 15;
		avg_wire_size += 11452;
	पूर्ण अन्यथा अगर (avg_wire_size <= 1980) अणु
		/* 36K पूर्णांकs/sec to 30K पूर्णांकs/sec */
		avg_wire_size *= 5;
		avg_wire_size += 22420;
	पूर्ण अन्यथा अणु
		/* plateau at a limit of 30K पूर्णांकs/sec */
		avg_wire_size = 32256;
	पूर्ण

	/* If we are in low latency mode halve our delay which द्विगुनs the
	 * rate to somewhere between 100K to 16K पूर्णांकs/sec
	 */
	अगर (itr & I40E_ITR_ADAPTIVE_LATENCY)
		avg_wire_size /= 2;

	/* Resultant value is 256 बार larger than it needs to be. This
	 * gives us room to adjust the value as needed to either increase
	 * or decrease the value based on link speeds of 10G, 2.5G, 1G, etc.
	 *
	 * Use addition as we have alपढ़ोy recorded the new latency flag
	 * क्रम the ITR value.
	 */
	itr += DIV_ROUND_UP(avg_wire_size, i40e_itr_भागisor(q_vector)) *
	       I40E_ITR_ADAPTIVE_MIN_INC;

	अगर ((itr & I40E_ITR_MASK) > I40E_ITR_ADAPTIVE_MAX_USECS) अणु
		itr &= I40E_ITR_ADAPTIVE_LATENCY;
		itr += I40E_ITR_ADAPTIVE_MAX_USECS;
	पूर्ण

clear_counts:
	/* ग_लिखो back value */
	rc->target_itr = itr;

	/* next update should occur within next jअगरfy */
	rc->next_update = next_update + 1;

	rc->total_bytes = 0;
	rc->total_packets = 0;
पूर्ण

अटल काष्ठा i40e_rx_buffer *i40e_rx_bi(काष्ठा i40e_ring *rx_ring, u32 idx)
अणु
	वापस &rx_ring->rx_bi[idx];
पूर्ण

/**
 * i40e_reuse_rx_page - page flip buffer and store it back on the ring
 * @rx_ring: rx descriptor ring to store buffers on
 * @old_buff: करोnor buffer to have page reused
 *
 * Synchronizes page क्रम reuse by the adapter
 **/
अटल व्योम i40e_reuse_rx_page(काष्ठा i40e_ring *rx_ring,
			       काष्ठा i40e_rx_buffer *old_buff)
अणु
	काष्ठा i40e_rx_buffer *new_buff;
	u16 nta = rx_ring->next_to_alloc;

	new_buff = i40e_rx_bi(rx_ring, nta);

	/* update, and store next to alloc */
	nta++;
	rx_ring->next_to_alloc = (nta < rx_ring->count) ? nta : 0;

	/* transfer page from old buffer to new buffer */
	new_buff->dma		= old_buff->dma;
	new_buff->page		= old_buff->page;
	new_buff->page_offset	= old_buff->page_offset;
	new_buff->pagecnt_bias	= old_buff->pagecnt_bias;

	rx_ring->rx_stats.page_reuse_count++;

	/* clear contents of buffer_info */
	old_buff->page = शून्य;
पूर्ण

/**
 * i40e_clean_programming_status - clean the programming status descriptor
 * @rx_ring: the rx ring that has this descriptor
 * @qword0_raw: qword0
 * @qword1: qword1 representing status_error_len in CPU ordering
 *
 * Flow director should handle FD_FILTER_STATUS to check its filter programming
 * status being successful or not and take actions accordingly. FCoE should
 * handle its context/filter programming/invalidation status and take actions.
 *
 * Returns an i40e_rx_buffer to reuse अगर the cleanup occurred, otherwise शून्य.
 **/
व्योम i40e_clean_programming_status(काष्ठा i40e_ring *rx_ring, u64 qword0_raw,
				   u64 qword1)
अणु
	u8 id;

	id = (qword1 & I40E_RX_PROG_STATUS_DESC_QW1_PROGID_MASK) >>
		  I40E_RX_PROG_STATUS_DESC_QW1_PROGID_SHIFT;

	अगर (id == I40E_RX_PROG_STATUS_DESC_FD_FILTER_STATUS)
		i40e_fd_handle_status(rx_ring, qword0_raw, qword1, id);
पूर्ण

/**
 * i40e_setup_tx_descriptors - Allocate the Tx descriptors
 * @tx_ring: the tx ring to set up
 *
 * Return 0 on success, negative on error
 **/
पूर्णांक i40e_setup_tx_descriptors(काष्ठा i40e_ring *tx_ring)
अणु
	काष्ठा device *dev = tx_ring->dev;
	पूर्णांक bi_size;

	अगर (!dev)
		वापस -ENOMEM;

	/* warn अगर we are about to overग_लिखो the poपूर्णांकer */
	WARN_ON(tx_ring->tx_bi);
	bi_size = माप(काष्ठा i40e_tx_buffer) * tx_ring->count;
	tx_ring->tx_bi = kzalloc(bi_size, GFP_KERNEL);
	अगर (!tx_ring->tx_bi)
		जाओ err;

	अगर (ring_is_xdp(tx_ring)) अणु
		tx_ring->xsk_descs = kसुस्मृति(I40E_MAX_NUM_DESCRIPTORS, माप(*tx_ring->xsk_descs),
					     GFP_KERNEL);
		अगर (!tx_ring->xsk_descs)
			जाओ err;
	पूर्ण

	u64_stats_init(&tx_ring->syncp);

	/* round up to nearest 4K */
	tx_ring->size = tx_ring->count * माप(काष्ठा i40e_tx_desc);
	/* add u32 क्रम head ग_लिखोback, align after this takes care of
	 * guaranteeing this is at least one cache line in size
	 */
	tx_ring->size += माप(u32);
	tx_ring->size = ALIGN(tx_ring->size, 4096);
	tx_ring->desc = dma_alloc_coherent(dev, tx_ring->size,
					   &tx_ring->dma, GFP_KERNEL);
	अगर (!tx_ring->desc) अणु
		dev_info(dev, "Unable to allocate memory for the Tx descriptor ring, size=%d\n",
			 tx_ring->size);
		जाओ err;
	पूर्ण

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;
	tx_ring->tx_stats.prev_pkt_ctr = -1;
	वापस 0;

err:
	kमुक्त(tx_ring->xsk_descs);
	tx_ring->xsk_descs = शून्य;
	kमुक्त(tx_ring->tx_bi);
	tx_ring->tx_bi = शून्य;
	वापस -ENOMEM;
पूर्ण

पूर्णांक i40e_alloc_rx_bi(काष्ठा i40e_ring *rx_ring)
अणु
	अचिन्हित दीर्घ sz = माप(*rx_ring->rx_bi) * rx_ring->count;

	rx_ring->rx_bi = kzalloc(sz, GFP_KERNEL);
	वापस rx_ring->rx_bi ? 0 : -ENOMEM;
पूर्ण

अटल व्योम i40e_clear_rx_bi(काष्ठा i40e_ring *rx_ring)
अणु
	स_रखो(rx_ring->rx_bi, 0, माप(*rx_ring->rx_bi) * rx_ring->count);
पूर्ण

/**
 * i40e_clean_rx_ring - Free Rx buffers
 * @rx_ring: ring to be cleaned
 **/
व्योम i40e_clean_rx_ring(काष्ठा i40e_ring *rx_ring)
अणु
	u16 i;

	/* ring alपढ़ोy cleared, nothing to करो */
	अगर (!rx_ring->rx_bi)
		वापस;

	अगर (rx_ring->skb) अणु
		dev_kमुक्त_skb(rx_ring->skb);
		rx_ring->skb = शून्य;
	पूर्ण

	अगर (rx_ring->xsk_pool) अणु
		i40e_xsk_clean_rx_ring(rx_ring);
		जाओ skip_मुक्त;
	पूर्ण

	/* Free all the Rx ring sk_buffs */
	क्रम (i = 0; i < rx_ring->count; i++) अणु
		काष्ठा i40e_rx_buffer *rx_bi = i40e_rx_bi(rx_ring, i);

		अगर (!rx_bi->page)
			जारी;

		/* Invalidate cache lines that may have been written to by
		 * device so that we aव्योम corrupting memory.
		 */
		dma_sync_single_range_क्रम_cpu(rx_ring->dev,
					      rx_bi->dma,
					      rx_bi->page_offset,
					      rx_ring->rx_buf_len,
					      DMA_FROM_DEVICE);

		/* मुक्त resources associated with mapping */
		dma_unmap_page_attrs(rx_ring->dev, rx_bi->dma,
				     i40e_rx_pg_size(rx_ring),
				     DMA_FROM_DEVICE,
				     I40E_RX_DMA_ATTR);

		__page_frag_cache_drain(rx_bi->page, rx_bi->pagecnt_bias);

		rx_bi->page = शून्य;
		rx_bi->page_offset = 0;
	पूर्ण

skip_मुक्त:
	अगर (rx_ring->xsk_pool)
		i40e_clear_rx_bi_zc(rx_ring);
	अन्यथा
		i40e_clear_rx_bi(rx_ring);

	/* Zero out the descriptor ring */
	स_रखो(rx_ring->desc, 0, rx_ring->size);

	rx_ring->next_to_alloc = 0;
	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
पूर्ण

/**
 * i40e_मुक्त_rx_resources - Free Rx resources
 * @rx_ring: ring to clean the resources from
 *
 * Free all receive software resources
 **/
व्योम i40e_मुक्त_rx_resources(काष्ठा i40e_ring *rx_ring)
अणु
	i40e_clean_rx_ring(rx_ring);
	अगर (rx_ring->vsi->type == I40E_VSI_MAIN)
		xdp_rxq_info_unreg(&rx_ring->xdp_rxq);
	rx_ring->xdp_prog = शून्य;
	kमुक्त(rx_ring->rx_bi);
	rx_ring->rx_bi = शून्य;

	अगर (rx_ring->desc) अणु
		dma_मुक्त_coherent(rx_ring->dev, rx_ring->size,
				  rx_ring->desc, rx_ring->dma);
		rx_ring->desc = शून्य;
	पूर्ण
पूर्ण

/**
 * i40e_setup_rx_descriptors - Allocate Rx descriptors
 * @rx_ring: Rx descriptor ring (क्रम a specअगरic queue) to setup
 *
 * Returns 0 on success, negative on failure
 **/
पूर्णांक i40e_setup_rx_descriptors(काष्ठा i40e_ring *rx_ring)
अणु
	काष्ठा device *dev = rx_ring->dev;
	पूर्णांक err;

	u64_stats_init(&rx_ring->syncp);

	/* Round up to nearest 4K */
	rx_ring->size = rx_ring->count * माप(जोड़ i40e_rx_desc);
	rx_ring->size = ALIGN(rx_ring->size, 4096);
	rx_ring->desc = dma_alloc_coherent(dev, rx_ring->size,
					   &rx_ring->dma, GFP_KERNEL);

	अगर (!rx_ring->desc) अणु
		dev_info(dev, "Unable to allocate memory for the Rx descriptor ring, size=%d\n",
			 rx_ring->size);
		वापस -ENOMEM;
	पूर्ण

	rx_ring->next_to_alloc = 0;
	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;

	/* XDP RX-queue info only needed क्रम RX rings exposed to XDP */
	अगर (rx_ring->vsi->type == I40E_VSI_MAIN) अणु
		err = xdp_rxq_info_reg(&rx_ring->xdp_rxq, rx_ring->netdev,
				       rx_ring->queue_index, rx_ring->q_vector->napi.napi_id);
		अगर (err < 0)
			वापस err;
	पूर्ण

	rx_ring->xdp_prog = rx_ring->vsi->xdp_prog;

	वापस 0;
पूर्ण

/**
 * i40e_release_rx_desc - Store the new tail and head values
 * @rx_ring: ring to bump
 * @val: new head index
 **/
व्योम i40e_release_rx_desc(काष्ठा i40e_ring *rx_ring, u32 val)
अणु
	rx_ring->next_to_use = val;

	/* update next to alloc since we have filled the ring */
	rx_ring->next_to_alloc = val;

	/* Force memory ग_लिखोs to complete beक्रमe letting h/w
	 * know there are new descriptors to fetch.  (Only
	 * applicable क्रम weak-ordered memory model archs,
	 * such as IA-64).
	 */
	wmb();
	ग_लिखोl(val, rx_ring->tail);
पूर्ण

अटल अचिन्हित पूर्णांक i40e_rx_frame_truesize(काष्ठा i40e_ring *rx_ring,
					   अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक truesize;

#अगर (PAGE_SIZE < 8192)
	truesize = i40e_rx_pg_size(rx_ring) / 2; /* Must be घातer-of-2 */
#अन्यथा
	truesize = rx_ring->rx_offset ?
		SKB_DATA_ALIGN(size + rx_ring->rx_offset) +
		SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)) :
		SKB_DATA_ALIGN(size);
#पूर्ण_अगर
	वापस truesize;
पूर्ण

/**
 * i40e_alloc_mapped_page - recycle or make a new page
 * @rx_ring: ring to use
 * @bi: rx_buffer काष्ठा to modअगरy
 *
 * Returns true अगर the page was successfully allocated or
 * reused.
 **/
अटल bool i40e_alloc_mapped_page(काष्ठा i40e_ring *rx_ring,
				   काष्ठा i40e_rx_buffer *bi)
अणु
	काष्ठा page *page = bi->page;
	dma_addr_t dma;

	/* since we are recycling buffers we should selकरोm need to alloc */
	अगर (likely(page)) अणु
		rx_ring->rx_stats.page_reuse_count++;
		वापस true;
	पूर्ण

	/* alloc new page क्रम storage */
	page = dev_alloc_pages(i40e_rx_pg_order(rx_ring));
	अगर (unlikely(!page)) अणु
		rx_ring->rx_stats.alloc_page_failed++;
		वापस false;
	पूर्ण

	/* map page क्रम use */
	dma = dma_map_page_attrs(rx_ring->dev, page, 0,
				 i40e_rx_pg_size(rx_ring),
				 DMA_FROM_DEVICE,
				 I40E_RX_DMA_ATTR);

	/* अगर mapping failed मुक्त memory back to प्रणाली since
	 * there isn't much point in holding memory we can't use
	 */
	अगर (dma_mapping_error(rx_ring->dev, dma)) अणु
		__मुक्त_pages(page, i40e_rx_pg_order(rx_ring));
		rx_ring->rx_stats.alloc_page_failed++;
		वापस false;
	पूर्ण

	bi->dma = dma;
	bi->page = page;
	bi->page_offset = rx_ring->rx_offset;
	page_ref_add(page, अच_लघु_उच्च - 1);
	bi->pagecnt_bias = अच_लघु_उच्च;

	वापस true;
पूर्ण

/**
 * i40e_alloc_rx_buffers - Replace used receive buffers
 * @rx_ring: ring to place buffers on
 * @cleaned_count: number of buffers to replace
 *
 * Returns false अगर all allocations were successful, true अगर any fail
 **/
bool i40e_alloc_rx_buffers(काष्ठा i40e_ring *rx_ring, u16 cleaned_count)
अणु
	u16 ntu = rx_ring->next_to_use;
	जोड़ i40e_rx_desc *rx_desc;
	काष्ठा i40e_rx_buffer *bi;

	/* करो nothing अगर no valid netdev defined */
	अगर (!rx_ring->netdev || !cleaned_count)
		वापस false;

	rx_desc = I40E_RX_DESC(rx_ring, ntu);
	bi = i40e_rx_bi(rx_ring, ntu);

	करो अणु
		अगर (!i40e_alloc_mapped_page(rx_ring, bi))
			जाओ no_buffers;

		/* sync the buffer क्रम use by the device */
		dma_sync_single_range_क्रम_device(rx_ring->dev, bi->dma,
						 bi->page_offset,
						 rx_ring->rx_buf_len,
						 DMA_FROM_DEVICE);

		/* Refresh the desc even अगर buffer_addrs didn't change
		 * because each ग_लिखो-back erases this info.
		 */
		rx_desc->पढ़ो.pkt_addr = cpu_to_le64(bi->dma + bi->page_offset);

		rx_desc++;
		bi++;
		ntu++;
		अगर (unlikely(ntu == rx_ring->count)) अणु
			rx_desc = I40E_RX_DESC(rx_ring, 0);
			bi = i40e_rx_bi(rx_ring, 0);
			ntu = 0;
		पूर्ण

		/* clear the status bits क्रम the next_to_use descriptor */
		rx_desc->wb.qword1.status_error_len = 0;

		cleaned_count--;
	पूर्ण जबतक (cleaned_count);

	अगर (rx_ring->next_to_use != ntu)
		i40e_release_rx_desc(rx_ring, ntu);

	वापस false;

no_buffers:
	अगर (rx_ring->next_to_use != ntu)
		i40e_release_rx_desc(rx_ring, ntu);

	/* make sure to come back via polling to try again after
	 * allocation failure
	 */
	वापस true;
पूर्ण

/**
 * i40e_rx_checksum - Indicate in skb अगर hw indicated a good cksum
 * @vsi: the VSI we care about
 * @skb: skb currently being received and modअगरied
 * @rx_desc: the receive descriptor
 **/
अटल अंतरभूत व्योम i40e_rx_checksum(काष्ठा i40e_vsi *vsi,
				    काष्ठा sk_buff *skb,
				    जोड़ i40e_rx_desc *rx_desc)
अणु
	काष्ठा i40e_rx_ptype_decoded decoded;
	u32 rx_error, rx_status;
	bool ipv4, ipv6;
	u8 ptype;
	u64 qword;

	qword = le64_to_cpu(rx_desc->wb.qword1.status_error_len);
	ptype = (qword & I40E_RXD_QW1_PTYPE_MASK) >> I40E_RXD_QW1_PTYPE_SHIFT;
	rx_error = (qword & I40E_RXD_QW1_ERROR_MASK) >>
		   I40E_RXD_QW1_ERROR_SHIFT;
	rx_status = (qword & I40E_RXD_QW1_STATUS_MASK) >>
		    I40E_RXD_QW1_STATUS_SHIFT;
	decoded = decode_rx_desc_ptype(ptype);

	skb->ip_summed = CHECKSUM_NONE;

	skb_checksum_none_निश्चित(skb);

	/* Rx csum enabled and ip headers found? */
	अगर (!(vsi->netdev->features & NETIF_F_RXCSUM))
		वापस;

	/* did the hardware decode the packet and checksum? */
	अगर (!(rx_status & BIT(I40E_RX_DESC_STATUS_L3L4P_SHIFT)))
		वापस;

	/* both known and outer_ip must be set क्रम the below code to work */
	अगर (!(decoded.known && decoded.outer_ip))
		वापस;

	ipv4 = (decoded.outer_ip == I40E_RX_PTYPE_OUTER_IP) &&
	       (decoded.outer_ip_ver == I40E_RX_PTYPE_OUTER_IPV4);
	ipv6 = (decoded.outer_ip == I40E_RX_PTYPE_OUTER_IP) &&
	       (decoded.outer_ip_ver == I40E_RX_PTYPE_OUTER_IPV6);

	अगर (ipv4 &&
	    (rx_error & (BIT(I40E_RX_DESC_ERROR_IPE_SHIFT) |
			 BIT(I40E_RX_DESC_ERROR_EIPE_SHIFT))))
		जाओ checksum_fail;

	/* likely incorrect csum अगर alternate IP extension headers found */
	अगर (ipv6 &&
	    rx_status & BIT(I40E_RX_DESC_STATUS_IPV6EXADD_SHIFT))
		/* करोn't increment checksum err here, non-fatal err */
		वापस;

	/* there was some L4 error, count error and punt packet to the stack */
	अगर (rx_error & BIT(I40E_RX_DESC_ERROR_L4E_SHIFT))
		जाओ checksum_fail;

	/* handle packets that were not able to be checksummed due
	 * to arrival speed, in this हाल the stack can compute
	 * the csum.
	 */
	अगर (rx_error & BIT(I40E_RX_DESC_ERROR_PPRS_SHIFT))
		वापस;

	/* If there is an outer header present that might contain a checksum
	 * we need to bump the checksum level by 1 to reflect the fact that
	 * we are indicating we validated the inner checksum.
	 */
	अगर (decoded.tunnel_type >= I40E_RX_PTYPE_TUNNEL_IP_GRENAT)
		skb->csum_level = 1;

	/* Only report checksum unnecessary क्रम TCP, UDP, or SCTP */
	चयन (decoded.inner_prot) अणु
	हाल I40E_RX_PTYPE_INNER_PROT_TCP:
	हाल I40E_RX_PTYPE_INNER_PROT_UDP:
	हाल I40E_RX_PTYPE_INNER_PROT_SCTP:
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		fallthrough;
	शेष:
		अवरोध;
	पूर्ण

	वापस;

checksum_fail:
	vsi->back->hw_csum_rx_error++;
पूर्ण

/**
 * i40e_ptype_to_htype - get a hash type
 * @ptype: the ptype value from the descriptor
 *
 * Returns a hash type to be used by skb_set_hash
 **/
अटल अंतरभूत पूर्णांक i40e_ptype_to_htype(u8 ptype)
अणु
	काष्ठा i40e_rx_ptype_decoded decoded = decode_rx_desc_ptype(ptype);

	अगर (!decoded.known)
		वापस PKT_HASH_TYPE_NONE;

	अगर (decoded.outer_ip == I40E_RX_PTYPE_OUTER_IP &&
	    decoded.payload_layer == I40E_RX_PTYPE_PAYLOAD_LAYER_PAY4)
		वापस PKT_HASH_TYPE_L4;
	अन्यथा अगर (decoded.outer_ip == I40E_RX_PTYPE_OUTER_IP &&
		 decoded.payload_layer == I40E_RX_PTYPE_PAYLOAD_LAYER_PAY3)
		वापस PKT_HASH_TYPE_L3;
	अन्यथा
		वापस PKT_HASH_TYPE_L2;
पूर्ण

/**
 * i40e_rx_hash - set the hash value in the skb
 * @ring: descriptor ring
 * @rx_desc: specअगरic descriptor
 * @skb: skb currently being received and modअगरied
 * @rx_ptype: Rx packet type
 **/
अटल अंतरभूत व्योम i40e_rx_hash(काष्ठा i40e_ring *ring,
				जोड़ i40e_rx_desc *rx_desc,
				काष्ठा sk_buff *skb,
				u8 rx_ptype)
अणु
	u32 hash;
	स्थिर __le64 rss_mask =
		cpu_to_le64((u64)I40E_RX_DESC_FLTSTAT_RSS_HASH <<
			    I40E_RX_DESC_STATUS_FLTSTAT_SHIFT);

	अगर (!(ring->netdev->features & NETIF_F_RXHASH))
		वापस;

	अगर ((rx_desc->wb.qword1.status_error_len & rss_mask) == rss_mask) अणु
		hash = le32_to_cpu(rx_desc->wb.qword0.hi_dword.rss);
		skb_set_hash(skb, hash, i40e_ptype_to_htype(rx_ptype));
	पूर्ण
पूर्ण

/**
 * i40e_process_skb_fields - Populate skb header fields from Rx descriptor
 * @rx_ring: rx descriptor ring packet is being transacted on
 * @rx_desc: poपूर्णांकer to the EOP Rx descriptor
 * @skb: poपूर्णांकer to current skb being populated
 *
 * This function checks the ring, descriptor, and packet inक्रमmation in
 * order to populate the hash, checksum, VLAN, protocol, and
 * other fields within the skb.
 **/
व्योम i40e_process_skb_fields(काष्ठा i40e_ring *rx_ring,
			     जोड़ i40e_rx_desc *rx_desc, काष्ठा sk_buff *skb)
अणु
	u64 qword = le64_to_cpu(rx_desc->wb.qword1.status_error_len);
	u32 rx_status = (qword & I40E_RXD_QW1_STATUS_MASK) >>
			I40E_RXD_QW1_STATUS_SHIFT;
	u32 tsynvalid = rx_status & I40E_RXD_QW1_STATUS_TSYNVALID_MASK;
	u32 tsyn = (rx_status & I40E_RXD_QW1_STATUS_TSYNINDX_MASK) >>
		   I40E_RXD_QW1_STATUS_TSYNINDX_SHIFT;
	u8 rx_ptype = (qword & I40E_RXD_QW1_PTYPE_MASK) >>
		      I40E_RXD_QW1_PTYPE_SHIFT;

	अगर (unlikely(tsynvalid))
		i40e_ptp_rx_hwtstamp(rx_ring->vsi->back, skb, tsyn);

	i40e_rx_hash(rx_ring, rx_desc, skb, rx_ptype);

	i40e_rx_checksum(rx_ring->vsi, skb, rx_desc);

	skb_record_rx_queue(skb, rx_ring->queue_index);

	अगर (qword & BIT(I40E_RX_DESC_STATUS_L2TAG1P_SHIFT)) अणु
		__le16 vlan_tag = rx_desc->wb.qword0.lo_dword.l2tag1;

		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
				       le16_to_cpu(vlan_tag));
	पूर्ण

	/* modअगरies the skb - consumes the enet header */
	skb->protocol = eth_type_trans(skb, rx_ring->netdev);
पूर्ण

/**
 * i40e_cleanup_headers - Correct empty headers
 * @rx_ring: rx descriptor ring packet is being transacted on
 * @skb: poपूर्णांकer to current skb being fixed
 * @rx_desc: poपूर्णांकer to the EOP Rx descriptor
 *
 * In addition अगर skb is not at least 60 bytes we need to pad it so that
 * it is large enough to qualअगरy as a valid Ethernet frame.
 *
 * Returns true अगर an error was encountered and skb was मुक्तd.
 **/
अटल bool i40e_cleanup_headers(काष्ठा i40e_ring *rx_ring, काष्ठा sk_buff *skb,
				 जोड़ i40e_rx_desc *rx_desc)

अणु
	/* ERR_MASK will only have valid bits अगर EOP set, and
	 * what we are करोing here is actually checking
	 * I40E_RX_DESC_ERROR_RXE_SHIFT, since it is the zeroth bit in
	 * the error field
	 */
	अगर (unlikely(i40e_test_staterr(rx_desc,
				       BIT(I40E_RXD_QW1_ERROR_SHIFT)))) अणु
		dev_kमुक्त_skb_any(skb);
		वापस true;
	पूर्ण

	/* अगर eth_skb_pad वापसs an error the skb was मुक्तd */
	अगर (eth_skb_pad(skb))
		वापस true;

	वापस false;
पूर्ण

/**
 * i40e_can_reuse_rx_page - Determine अगर page can be reused क्रम another Rx
 * @rx_buffer: buffer containing the page
 * @rx_buffer_pgcnt: buffer page refcount pre xdp_करो_redirect() call
 *
 * If page is reusable, we have a green light क्रम calling i40e_reuse_rx_page,
 * which will assign the current buffer to the buffer that next_to_alloc is
 * poपूर्णांकing to; otherwise, the DMA mapping needs to be destroyed and
 * page मुक्तd
 */
अटल bool i40e_can_reuse_rx_page(काष्ठा i40e_rx_buffer *rx_buffer,
				   पूर्णांक rx_buffer_pgcnt)
अणु
	अचिन्हित पूर्णांक pagecnt_bias = rx_buffer->pagecnt_bias;
	काष्ठा page *page = rx_buffer->page;

	/* Is any reuse possible? */
	अगर (!dev_page_is_reusable(page))
		वापस false;

#अगर (PAGE_SIZE < 8192)
	/* अगर we are only owner of page we can reuse it */
	अगर (unlikely((rx_buffer_pgcnt - pagecnt_bias) > 1))
		वापस false;
#अन्यथा
#घोषणा I40E_LAST_OFFSET \
	(SKB_WITH_OVERHEAD(PAGE_SIZE) - I40E_RXBUFFER_2048)
	अगर (rx_buffer->page_offset > I40E_LAST_OFFSET)
		वापस false;
#पूर्ण_अगर

	/* If we have drained the page fragment pool we need to update
	 * the pagecnt_bias and page count so that we fully restock the
	 * number of references the driver holds.
	 */
	अगर (unlikely(pagecnt_bias == 1)) अणु
		page_ref_add(page, अच_लघु_उच्च - 1);
		rx_buffer->pagecnt_bias = अच_लघु_उच्च;
	पूर्ण

	वापस true;
पूर्ण

/**
 * i40e_add_rx_frag - Add contents of Rx buffer to sk_buff
 * @rx_ring: rx descriptor ring to transact packets on
 * @rx_buffer: buffer containing page to add
 * @skb: sk_buff to place the data पूर्णांकo
 * @size: packet length from rx_desc
 *
 * This function will add the data contained in rx_buffer->page to the skb.
 * It will just attach the page as a frag to the skb.
 *
 * The function will then update the page offset.
 **/
अटल व्योम i40e_add_rx_frag(काष्ठा i40e_ring *rx_ring,
			     काष्ठा i40e_rx_buffer *rx_buffer,
			     काष्ठा sk_buff *skb,
			     अचिन्हित पूर्णांक size)
अणु
#अगर (PAGE_SIZE < 8192)
	अचिन्हित पूर्णांक truesize = i40e_rx_pg_size(rx_ring) / 2;
#अन्यथा
	अचिन्हित पूर्णांक truesize = SKB_DATA_ALIGN(size + rx_ring->rx_offset);
#पूर्ण_अगर

	skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, rx_buffer->page,
			rx_buffer->page_offset, size, truesize);

	/* page is being used so we must update the page offset */
#अगर (PAGE_SIZE < 8192)
	rx_buffer->page_offset ^= truesize;
#अन्यथा
	rx_buffer->page_offset += truesize;
#पूर्ण_अगर
पूर्ण

/**
 * i40e_get_rx_buffer - Fetch Rx buffer and synchronize data क्रम use
 * @rx_ring: rx descriptor ring to transact packets on
 * @size: size of buffer to add to skb
 * @rx_buffer_pgcnt: buffer page refcount
 *
 * This function will pull an Rx buffer from the ring and synchronize it
 * क्रम use by the CPU.
 */
अटल काष्ठा i40e_rx_buffer *i40e_get_rx_buffer(काष्ठा i40e_ring *rx_ring,
						 स्थिर अचिन्हित पूर्णांक size,
						 पूर्णांक *rx_buffer_pgcnt)
अणु
	काष्ठा i40e_rx_buffer *rx_buffer;

	rx_buffer = i40e_rx_bi(rx_ring, rx_ring->next_to_clean);
	*rx_buffer_pgcnt =
#अगर (PAGE_SIZE < 8192)
		page_count(rx_buffer->page);
#अन्यथा
		0;
#पूर्ण_अगर
	prefetch_page_address(rx_buffer->page);

	/* we are reusing so sync this buffer क्रम CPU use */
	dma_sync_single_range_क्रम_cpu(rx_ring->dev,
				      rx_buffer->dma,
				      rx_buffer->page_offset,
				      size,
				      DMA_FROM_DEVICE);

	/* We have pulled a buffer क्रम use, so decrement pagecnt_bias */
	rx_buffer->pagecnt_bias--;

	वापस rx_buffer;
पूर्ण

/**
 * i40e_स्थिरruct_skb - Allocate skb and populate it
 * @rx_ring: rx descriptor ring to transact packets on
 * @rx_buffer: rx buffer to pull data from
 * @xdp: xdp_buff poपूर्णांकing to the data
 *
 * This function allocates an skb.  It then populates it with the page
 * data from the current receive descriptor, taking care to set up the
 * skb correctly.
 */
अटल काष्ठा sk_buff *i40e_स्थिरruct_skb(काष्ठा i40e_ring *rx_ring,
					  काष्ठा i40e_rx_buffer *rx_buffer,
					  काष्ठा xdp_buff *xdp)
अणु
	अचिन्हित पूर्णांक size = xdp->data_end - xdp->data;
#अगर (PAGE_SIZE < 8192)
	अचिन्हित पूर्णांक truesize = i40e_rx_pg_size(rx_ring) / 2;
#अन्यथा
	अचिन्हित पूर्णांक truesize = SKB_DATA_ALIGN(size);
#पूर्ण_अगर
	अचिन्हित पूर्णांक headlen;
	काष्ठा sk_buff *skb;

	/* prefetch first cache line of first page */
	net_prefetch(xdp->data);

	/* Note, we get here by enabling legacy-rx via:
	 *
	 *    ethtool --set-priv-flags <dev> legacy-rx on
	 *
	 * In this mode, we currently get 0 extra XDP headroom as
	 * opposed to having legacy-rx off, where we process XDP
	 * packets going to stack via i40e_build_skb(). The latter
	 * provides us currently with 192 bytes of headroom.
	 *
	 * For i40e_स्थिरruct_skb() mode it means that the
	 * xdp->data_meta will always poपूर्णांक to xdp->data, since
	 * the helper cannot expand the head. Should this ever
	 * change in future क्रम legacy-rx mode on, then lets also
	 * add xdp->data_meta handling here.
	 */

	/* allocate a skb to store the frags */
	skb = __napi_alloc_skb(&rx_ring->q_vector->napi,
			       I40E_RX_HDR_SIZE,
			       GFP_ATOMIC | __GFP_NOWARN);
	अगर (unlikely(!skb))
		वापस शून्य;

	/* Determine available headroom क्रम copy */
	headlen = size;
	अगर (headlen > I40E_RX_HDR_SIZE)
		headlen = eth_get_headlen(skb->dev, xdp->data,
					  I40E_RX_HDR_SIZE);

	/* align pull length to size of दीर्घ to optimize स_नकल perक्रमmance */
	स_नकल(__skb_put(skb, headlen), xdp->data,
	       ALIGN(headlen, माप(दीर्घ)));

	/* update all of the poपूर्णांकers */
	size -= headlen;
	अगर (size) अणु
		skb_add_rx_frag(skb, 0, rx_buffer->page,
				rx_buffer->page_offset + headlen,
				size, truesize);

		/* buffer is used by skb, update page_offset */
#अगर (PAGE_SIZE < 8192)
		rx_buffer->page_offset ^= truesize;
#अन्यथा
		rx_buffer->page_offset += truesize;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		/* buffer is unused, reset bias back to rx_buffer */
		rx_buffer->pagecnt_bias++;
	पूर्ण

	वापस skb;
पूर्ण

/**
 * i40e_build_skb - Build skb around an existing buffer
 * @rx_ring: Rx descriptor ring to transact packets on
 * @rx_buffer: Rx buffer to pull data from
 * @xdp: xdp_buff poपूर्णांकing to the data
 *
 * This function builds an skb around an existing Rx buffer, taking care
 * to set up the skb correctly and aव्योम any स_नकल overhead.
 */
अटल काष्ठा sk_buff *i40e_build_skb(काष्ठा i40e_ring *rx_ring,
				      काष्ठा i40e_rx_buffer *rx_buffer,
				      काष्ठा xdp_buff *xdp)
अणु
	अचिन्हित पूर्णांक metasize = xdp->data - xdp->data_meta;
#अगर (PAGE_SIZE < 8192)
	अचिन्हित पूर्णांक truesize = i40e_rx_pg_size(rx_ring) / 2;
#अन्यथा
	अचिन्हित पूर्णांक truesize = SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)) +
				SKB_DATA_ALIGN(xdp->data_end -
					       xdp->data_hard_start);
#पूर्ण_अगर
	काष्ठा sk_buff *skb;

	/* Prefetch first cache line of first page. If xdp->data_meta
	 * is unused, this poपूर्णांकs exactly as xdp->data, otherwise we
	 * likely have a consumer accessing first few bytes of meta
	 * data, and then actual data.
	 */
	net_prefetch(xdp->data_meta);

	/* build an skb around the page buffer */
	skb = build_skb(xdp->data_hard_start, truesize);
	अगर (unlikely(!skb))
		वापस शून्य;

	/* update poपूर्णांकers within the skb to store the data */
	skb_reserve(skb, xdp->data - xdp->data_hard_start);
	__skb_put(skb, xdp->data_end - xdp->data);
	अगर (metasize)
		skb_metadata_set(skb, metasize);

	/* buffer is used by skb, update page_offset */
#अगर (PAGE_SIZE < 8192)
	rx_buffer->page_offset ^= truesize;
#अन्यथा
	rx_buffer->page_offset += truesize;
#पूर्ण_अगर

	वापस skb;
पूर्ण

/**
 * i40e_put_rx_buffer - Clean up used buffer and either recycle or मुक्त
 * @rx_ring: rx descriptor ring to transact packets on
 * @rx_buffer: rx buffer to pull data from
 * @rx_buffer_pgcnt: rx buffer page refcount pre xdp_करो_redirect() call
 *
 * This function will clean up the contents of the rx_buffer.  It will
 * either recycle the buffer or unmap it and मुक्त the associated resources.
 */
अटल व्योम i40e_put_rx_buffer(काष्ठा i40e_ring *rx_ring,
			       काष्ठा i40e_rx_buffer *rx_buffer,
			       पूर्णांक rx_buffer_pgcnt)
अणु
	अगर (i40e_can_reuse_rx_page(rx_buffer, rx_buffer_pgcnt)) अणु
		/* hand second half of page back to the ring */
		i40e_reuse_rx_page(rx_ring, rx_buffer);
	पूर्ण अन्यथा अणु
		/* we are not reusing the buffer so unmap it */
		dma_unmap_page_attrs(rx_ring->dev, rx_buffer->dma,
				     i40e_rx_pg_size(rx_ring),
				     DMA_FROM_DEVICE, I40E_RX_DMA_ATTR);
		__page_frag_cache_drain(rx_buffer->page,
					rx_buffer->pagecnt_bias);
		/* clear contents of buffer_info */
		rx_buffer->page = शून्य;
	पूर्ण
पूर्ण

/**
 * i40e_is_non_eop - process handling of non-EOP buffers
 * @rx_ring: Rx ring being processed
 * @rx_desc: Rx descriptor क्रम current buffer
 *
 * If the buffer is an EOP buffer, this function निकासs वापसing false,
 * otherwise वापस true indicating that this is in fact a non-EOP buffer.
 */
अटल bool i40e_is_non_eop(काष्ठा i40e_ring *rx_ring,
			    जोड़ i40e_rx_desc *rx_desc)
अणु
	/* अगर we are the last buffer then there is nothing अन्यथा to करो */
#घोषणा I40E_RXD_खातापूर्ण BIT(I40E_RX_DESC_STATUS_खातापूर्ण_SHIFT)
	अगर (likely(i40e_test_staterr(rx_desc, I40E_RXD_खातापूर्ण)))
		वापस false;

	rx_ring->rx_stats.non_eop_descs++;

	वापस true;
पूर्ण

अटल पूर्णांक i40e_xmit_xdp_ring(काष्ठा xdp_frame *xdpf,
			      काष्ठा i40e_ring *xdp_ring);

पूर्णांक i40e_xmit_xdp_tx_ring(काष्ठा xdp_buff *xdp, काष्ठा i40e_ring *xdp_ring)
अणु
	काष्ठा xdp_frame *xdpf = xdp_convert_buff_to_frame(xdp);

	अगर (unlikely(!xdpf))
		वापस I40E_XDP_CONSUMED;

	वापस i40e_xmit_xdp_ring(xdpf, xdp_ring);
पूर्ण

/**
 * i40e_run_xdp - run an XDP program
 * @rx_ring: Rx ring being processed
 * @xdp: XDP buffer containing the frame
 **/
अटल पूर्णांक i40e_run_xdp(काष्ठा i40e_ring *rx_ring, काष्ठा xdp_buff *xdp)
अणु
	पूर्णांक err, result = I40E_XDP_PASS;
	काष्ठा i40e_ring *xdp_ring;
	काष्ठा bpf_prog *xdp_prog;
	u32 act;

	rcu_पढ़ो_lock();
	xdp_prog = READ_ONCE(rx_ring->xdp_prog);

	अगर (!xdp_prog)
		जाओ xdp_out;

	prefetchw(xdp->data_hard_start); /* xdp_frame ग_लिखो */

	act = bpf_prog_run_xdp(xdp_prog, xdp);
	चयन (act) अणु
	हाल XDP_PASS:
		अवरोध;
	हाल XDP_TX:
		xdp_ring = rx_ring->vsi->xdp_rings[rx_ring->queue_index];
		result = i40e_xmit_xdp_tx_ring(xdp, xdp_ring);
		अगर (result == I40E_XDP_CONSUMED)
			जाओ out_failure;
		अवरोध;
	हाल XDP_REसूचीECT:
		err = xdp_करो_redirect(rx_ring->netdev, xdp, xdp_prog);
		अगर (err)
			जाओ out_failure;
		result = I40E_XDP_REसूची;
		अवरोध;
	शेष:
		bpf_warn_invalid_xdp_action(act);
		fallthrough;
	हाल XDP_ABORTED:
out_failure:
		trace_xdp_exception(rx_ring->netdev, xdp_prog, act);
		fallthrough; /* handle पातs by dropping packet */
	हाल XDP_DROP:
		result = I40E_XDP_CONSUMED;
		अवरोध;
	पूर्ण
xdp_out:
	rcu_पढ़ो_unlock();
	वापस result;
पूर्ण

/**
 * i40e_rx_buffer_flip - adjusted rx_buffer to poपूर्णांक to an unused region
 * @rx_ring: Rx ring
 * @rx_buffer: Rx buffer to adjust
 * @size: Size of adjusपंचांगent
 **/
अटल व्योम i40e_rx_buffer_flip(काष्ठा i40e_ring *rx_ring,
				काष्ठा i40e_rx_buffer *rx_buffer,
				अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक truesize = i40e_rx_frame_truesize(rx_ring, size);

#अगर (PAGE_SIZE < 8192)
	rx_buffer->page_offset ^= truesize;
#अन्यथा
	rx_buffer->page_offset += truesize;
#पूर्ण_अगर
पूर्ण

/**
 * i40e_xdp_ring_update_tail - Updates the XDP Tx ring tail रेजिस्टर
 * @xdp_ring: XDP Tx ring
 *
 * This function updates the XDP Tx ring tail रेजिस्टर.
 **/
व्योम i40e_xdp_ring_update_tail(काष्ठा i40e_ring *xdp_ring)
अणु
	/* Force memory ग_लिखोs to complete beक्रमe letting h/w
	 * know there are new descriptors to fetch.
	 */
	wmb();
	ग_लिखोl_relaxed(xdp_ring->next_to_use, xdp_ring->tail);
पूर्ण

/**
 * i40e_update_rx_stats - Update Rx ring statistics
 * @rx_ring: rx descriptor ring
 * @total_rx_bytes: number of bytes received
 * @total_rx_packets: number of packets received
 *
 * This function updates the Rx ring statistics.
 **/
व्योम i40e_update_rx_stats(काष्ठा i40e_ring *rx_ring,
			  अचिन्हित पूर्णांक total_rx_bytes,
			  अचिन्हित पूर्णांक total_rx_packets)
अणु
	u64_stats_update_begin(&rx_ring->syncp);
	rx_ring->stats.packets += total_rx_packets;
	rx_ring->stats.bytes += total_rx_bytes;
	u64_stats_update_end(&rx_ring->syncp);
	rx_ring->q_vector->rx.total_packets += total_rx_packets;
	rx_ring->q_vector->rx.total_bytes += total_rx_bytes;
पूर्ण

/**
 * i40e_finalize_xdp_rx - Bump XDP Tx tail and/or flush redirect map
 * @rx_ring: Rx ring
 * @xdp_res: Result of the receive batch
 *
 * This function bumps XDP Tx tail and/or flush redirect map, and
 * should be called when a batch of packets has been processed in the
 * napi loop.
 **/
व्योम i40e_finalize_xdp_rx(काष्ठा i40e_ring *rx_ring, अचिन्हित पूर्णांक xdp_res)
अणु
	अगर (xdp_res & I40E_XDP_REसूची)
		xdp_करो_flush_map();

	अगर (xdp_res & I40E_XDP_TX) अणु
		काष्ठा i40e_ring *xdp_ring =
			rx_ring->vsi->xdp_rings[rx_ring->queue_index];

		i40e_xdp_ring_update_tail(xdp_ring);
	पूर्ण
पूर्ण

/**
 * i40e_inc_ntc: Advance the next_to_clean index
 * @rx_ring: Rx ring
 **/
अटल व्योम i40e_inc_ntc(काष्ठा i40e_ring *rx_ring)
अणु
	u32 ntc = rx_ring->next_to_clean + 1;

	ntc = (ntc < rx_ring->count) ? ntc : 0;
	rx_ring->next_to_clean = ntc;
	prefetch(I40E_RX_DESC(rx_ring, ntc));
पूर्ण

/**
 * i40e_clean_rx_irq - Clean completed descriptors from Rx ring - bounce buf
 * @rx_ring: rx descriptor ring to transact packets on
 * @budget: Total limit on number of packets to process
 *
 * This function provides a "bounce buffer" approach to Rx पूर्णांकerrupt
 * processing.  The advantage to this is that on प्रणालीs that have
 * expensive overhead क्रम IOMMU access this provides a means of aव्योमing
 * it by मुख्यtaining the mapping of the page to the प्रणाली.
 *
 * Returns amount of work completed
 **/
अटल पूर्णांक i40e_clean_rx_irq(काष्ठा i40e_ring *rx_ring, पूर्णांक budget)
अणु
	अचिन्हित पूर्णांक total_rx_bytes = 0, total_rx_packets = 0, frame_sz = 0;
	u16 cleaned_count = I40E_DESC_UNUSED(rx_ring);
	अचिन्हित पूर्णांक offset = rx_ring->rx_offset;
	काष्ठा sk_buff *skb = rx_ring->skb;
	अचिन्हित पूर्णांक xdp_xmit = 0;
	bool failure = false;
	काष्ठा xdp_buff xdp;
	पूर्णांक xdp_res = 0;

#अगर (PAGE_SIZE < 8192)
	frame_sz = i40e_rx_frame_truesize(rx_ring, 0);
#पूर्ण_अगर
	xdp_init_buff(&xdp, frame_sz, &rx_ring->xdp_rxq);

	जबतक (likely(total_rx_packets < (अचिन्हित पूर्णांक)budget)) अणु
		काष्ठा i40e_rx_buffer *rx_buffer;
		जोड़ i40e_rx_desc *rx_desc;
		पूर्णांक rx_buffer_pgcnt;
		अचिन्हित पूर्णांक size;
		u64 qword;

		/* वापस some buffers to hardware, one at a समय is too slow */
		अगर (cleaned_count >= I40E_RX_BUFFER_WRITE) अणु
			failure = failure ||
				  i40e_alloc_rx_buffers(rx_ring, cleaned_count);
			cleaned_count = 0;
		पूर्ण

		rx_desc = I40E_RX_DESC(rx_ring, rx_ring->next_to_clean);

		/* status_error_len will always be zero क्रम unused descriptors
		 * because it's cleared in cleanup, and overlaps with hdr_addr
		 * which is always zero because packet split isn't used, अगर the
		 * hardware wrote DD then the length will be non-zero
		 */
		qword = le64_to_cpu(rx_desc->wb.qword1.status_error_len);

		/* This memory barrier is needed to keep us from पढ़ोing
		 * any other fields out of the rx_desc until we have
		 * verअगरied the descriptor has been written back.
		 */
		dma_rmb();

		अगर (i40e_rx_is_programming_status(qword)) अणु
			i40e_clean_programming_status(rx_ring,
						      rx_desc->raw.qword[0],
						      qword);
			rx_buffer = i40e_rx_bi(rx_ring, rx_ring->next_to_clean);
			i40e_inc_ntc(rx_ring);
			i40e_reuse_rx_page(rx_ring, rx_buffer);
			cleaned_count++;
			जारी;
		पूर्ण

		size = (qword & I40E_RXD_QW1_LENGTH_PBUF_MASK) >>
		       I40E_RXD_QW1_LENGTH_PBUF_SHIFT;
		अगर (!size)
			अवरोध;

		i40e_trace(clean_rx_irq, rx_ring, rx_desc, skb);
		rx_buffer = i40e_get_rx_buffer(rx_ring, size, &rx_buffer_pgcnt);

		/* retrieve a buffer from the ring */
		अगर (!skb) अणु
			अचिन्हित अक्षर *hard_start;

			hard_start = page_address(rx_buffer->page) +
				     rx_buffer->page_offset - offset;
			xdp_prepare_buff(&xdp, hard_start, offset, size, true);
#अगर (PAGE_SIZE > 4096)
			/* At larger PAGE_SIZE, frame_sz depend on len size */
			xdp.frame_sz = i40e_rx_frame_truesize(rx_ring, size);
#पूर्ण_अगर
			xdp_res = i40e_run_xdp(rx_ring, &xdp);
		पूर्ण

		अगर (xdp_res) अणु
			अगर (xdp_res & (I40E_XDP_TX | I40E_XDP_REसूची)) अणु
				xdp_xmit |= xdp_res;
				i40e_rx_buffer_flip(rx_ring, rx_buffer, size);
			पूर्ण अन्यथा अणु
				rx_buffer->pagecnt_bias++;
			पूर्ण
			total_rx_bytes += size;
			total_rx_packets++;
		पूर्ण अन्यथा अगर (skb) अणु
			i40e_add_rx_frag(rx_ring, rx_buffer, skb, size);
		पूर्ण अन्यथा अगर (ring_uses_build_skb(rx_ring)) अणु
			skb = i40e_build_skb(rx_ring, rx_buffer, &xdp);
		पूर्ण अन्यथा अणु
			skb = i40e_स्थिरruct_skb(rx_ring, rx_buffer, &xdp);
		पूर्ण

		/* निकास अगर we failed to retrieve a buffer */
		अगर (!xdp_res && !skb) अणु
			rx_ring->rx_stats.alloc_buff_failed++;
			rx_buffer->pagecnt_bias++;
			अवरोध;
		पूर्ण

		i40e_put_rx_buffer(rx_ring, rx_buffer, rx_buffer_pgcnt);
		cleaned_count++;

		i40e_inc_ntc(rx_ring);
		अगर (i40e_is_non_eop(rx_ring, rx_desc))
			जारी;

		अगर (xdp_res || i40e_cleanup_headers(rx_ring, skb, rx_desc)) अणु
			skb = शून्य;
			जारी;
		पूर्ण

		/* probably a little skewed due to removing CRC */
		total_rx_bytes += skb->len;

		/* populate checksum, VLAN, and protocol */
		i40e_process_skb_fields(rx_ring, rx_desc, skb);

		i40e_trace(clean_rx_irq_rx, rx_ring, rx_desc, skb);
		napi_gro_receive(&rx_ring->q_vector->napi, skb);
		skb = शून्य;

		/* update budget accounting */
		total_rx_packets++;
	पूर्ण

	i40e_finalize_xdp_rx(rx_ring, xdp_xmit);
	rx_ring->skb = skb;

	i40e_update_rx_stats(rx_ring, total_rx_bytes, total_rx_packets);

	/* guarantee a trip back through this routine अगर there was a failure */
	वापस failure ? budget : (पूर्णांक)total_rx_packets;
पूर्ण

अटल अंतरभूत u32 i40e_buildreg_itr(स्थिर पूर्णांक type, u16 itr)
अणु
	u32 val;

	/* We करोn't bother with setting the CLEARPBA bit as the data sheet
	 * poपूर्णांकs out करोing so is "meaningless since it was alपढ़ोy
	 * स्वतः-cleared". The स्वतः-clearing happens when the पूर्णांकerrupt is
	 * निश्चितed.
	 *
	 * Hardware errata 28 क्रम also indicates that writing to a
	 * xxINT_DYN_CTLx CSR with INTENA_MSK (bit 31) set to 0 will clear
	 * an event in the PBA anyway so we need to rely on the स्वतःmask
	 * to hold pending events क्रम us until the पूर्णांकerrupt is re-enabled
	 *
	 * The itr value is reported in microseconds, and the रेजिस्टर
	 * value is recorded in 2 microsecond units. For this reason we
	 * only need to shअगरt by the पूर्णांकerval shअगरt - 1 instead of the
	 * full value.
	 */
	itr &= I40E_ITR_MASK;

	val = I40E_PFINT_DYN_CTLN_INTENA_MASK |
	      (type << I40E_PFINT_DYN_CTLN_ITR_INDX_SHIFT) |
	      (itr << (I40E_PFINT_DYN_CTLN_INTERVAL_SHIFT - 1));

	वापस val;
पूर्ण

/* a small macro to लघुen up some दीर्घ lines */
#घोषणा INTREG I40E_PFINT_DYN_CTLN

/* The act of updating the ITR will cause it to immediately trigger. In order
 * to prevent this from throwing off adaptive update statistics we defer the
 * update so that it can only happen so often. So after either Tx or Rx are
 * updated we make the adaptive scheme रुको until either the ITR completely
 * expires via the next_update expiration or we have been through at least
 * 3 पूर्णांकerrupts.
 */
#घोषणा ITR_COUNTDOWN_START 3

/**
 * i40e_update_enable_itr - Update itr and re-enable MSIX पूर्णांकerrupt
 * @vsi: the VSI we care about
 * @q_vector: q_vector क्रम which itr is being updated and पूर्णांकerrupt enabled
 *
 **/
अटल अंतरभूत व्योम i40e_update_enable_itr(काष्ठा i40e_vsi *vsi,
					  काष्ठा i40e_q_vector *q_vector)
अणु
	काष्ठा i40e_hw *hw = &vsi->back->hw;
	u32 पूर्णांकval;

	/* If we करोn't have MSIX, then we only need to re-enable icr0 */
	अगर (!(vsi->back->flags & I40E_FLAG_MSIX_ENABLED)) अणु
		i40e_irq_dynamic_enable_icr0(vsi->back);
		वापस;
	पूर्ण

	/* These will करो nothing अगर dynamic updates are not enabled */
	i40e_update_itr(q_vector, &q_vector->tx);
	i40e_update_itr(q_vector, &q_vector->rx);

	/* This block of logic allows us to get away with only updating
	 * one ITR value with each पूर्णांकerrupt. The idea is to perक्रमm a
	 * pseuकरो-lazy update with the following criteria.
	 *
	 * 1. Rx is given higher priority than Tx अगर both are in same state
	 * 2. If we must reduce an ITR that is given highest priority.
	 * 3. We then give priority to increasing ITR based on amount.
	 */
	अगर (q_vector->rx.target_itr < q_vector->rx.current_itr) अणु
		/* Rx ITR needs to be reduced, this is highest priority */
		पूर्णांकval = i40e_buildreg_itr(I40E_RX_ITR,
					   q_vector->rx.target_itr);
		q_vector->rx.current_itr = q_vector->rx.target_itr;
		q_vector->itr_countकरोwn = ITR_COUNTDOWN_START;
	पूर्ण अन्यथा अगर ((q_vector->tx.target_itr < q_vector->tx.current_itr) ||
		   ((q_vector->rx.target_itr - q_vector->rx.current_itr) <
		    (q_vector->tx.target_itr - q_vector->tx.current_itr))) अणु
		/* Tx ITR needs to be reduced, this is second priority
		 * Tx ITR needs to be increased more than Rx, fourth priority
		 */
		पूर्णांकval = i40e_buildreg_itr(I40E_TX_ITR,
					   q_vector->tx.target_itr);
		q_vector->tx.current_itr = q_vector->tx.target_itr;
		q_vector->itr_countकरोwn = ITR_COUNTDOWN_START;
	पूर्ण अन्यथा अगर (q_vector->rx.current_itr != q_vector->rx.target_itr) अणु
		/* Rx ITR needs to be increased, third priority */
		पूर्णांकval = i40e_buildreg_itr(I40E_RX_ITR,
					   q_vector->rx.target_itr);
		q_vector->rx.current_itr = q_vector->rx.target_itr;
		q_vector->itr_countकरोwn = ITR_COUNTDOWN_START;
	पूर्ण अन्यथा अणु
		/* No ITR update, lowest priority */
		पूर्णांकval = i40e_buildreg_itr(I40E_ITR_NONE, 0);
		अगर (q_vector->itr_countकरोwn)
			q_vector->itr_countकरोwn--;
	पूर्ण

	अगर (!test_bit(__I40E_VSI_DOWN, vsi->state))
		wr32(hw, INTREG(q_vector->reg_idx), पूर्णांकval);
पूर्ण

/**
 * i40e_napi_poll - NAPI polling Rx/Tx cleanup routine
 * @napi: napi काष्ठा with our devices info in it
 * @budget: amount of work driver is allowed to करो this pass, in packets
 *
 * This function will clean all queues associated with a q_vector.
 *
 * Returns the amount of work करोne
 **/
पूर्णांक i40e_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा i40e_q_vector *q_vector =
			       container_of(napi, काष्ठा i40e_q_vector, napi);
	काष्ठा i40e_vsi *vsi = q_vector->vsi;
	काष्ठा i40e_ring *ring;
	bool clean_complete = true;
	bool arm_wb = false;
	पूर्णांक budget_per_ring;
	पूर्णांक work_करोne = 0;

	अगर (test_bit(__I40E_VSI_DOWN, vsi->state)) अणु
		napi_complete(napi);
		वापस 0;
	पूर्ण

	/* Since the actual Tx work is minimal, we can give the Tx a larger
	 * budget and be more aggressive about cleaning up the Tx descriptors.
	 */
	i40e_क्रम_each_ring(ring, q_vector->tx) अणु
		bool wd = ring->xsk_pool ?
			  i40e_clean_xdp_tx_irq(vsi, ring) :
			  i40e_clean_tx_irq(vsi, ring, budget);

		अगर (!wd) अणु
			clean_complete = false;
			जारी;
		पूर्ण
		arm_wb |= ring->arm_wb;
		ring->arm_wb = false;
	पूर्ण

	/* Handle हाल where we are called by netpoll with a budget of 0 */
	अगर (budget <= 0)
		जाओ tx_only;

	/* normally we have 1 Rx ring per q_vector */
	अगर (unlikely(q_vector->num_ringpairs > 1))
		/* We attempt to distribute budget to each Rx queue fairly, but
		 * करोn't allow the budget to go below 1 because that would निकास
		 * polling early.
		 */
		budget_per_ring = max_t(पूर्णांक, budget / q_vector->num_ringpairs, 1);
	अन्यथा
		/* Max of 1 Rx ring in this q_vector so give it the budget */
		budget_per_ring = budget;

	i40e_क्रम_each_ring(ring, q_vector->rx) अणु
		पूर्णांक cleaned = ring->xsk_pool ?
			      i40e_clean_rx_irq_zc(ring, budget_per_ring) :
			      i40e_clean_rx_irq(ring, budget_per_ring);

		work_करोne += cleaned;
		/* अगर we clean as many as budgeted, we must not be करोne */
		अगर (cleaned >= budget_per_ring)
			clean_complete = false;
	पूर्ण

	/* If work not completed, वापस budget and polling will वापस */
	अगर (!clean_complete) अणु
		पूर्णांक cpu_id = smp_processor_id();

		/* It is possible that the पूर्णांकerrupt affinity has changed but,
		 * अगर the cpu is pegged at 100%, polling will never निकास जबतक
		 * traffic जारीs and the पूर्णांकerrupt will be stuck on this
		 * cpu.  We check to make sure affinity is correct beक्रमe we
		 * जारी to poll, otherwise we must stop polling so the
		 * पूर्णांकerrupt can move to the correct cpu.
		 */
		अगर (!cpumask_test_cpu(cpu_id, &q_vector->affinity_mask)) अणु
			/* Tell napi that we are करोne polling */
			napi_complete_करोne(napi, work_करोne);

			/* Force an पूर्णांकerrupt */
			i40e_क्रमce_wb(vsi, q_vector);

			/* Return budget-1 so that polling stops */
			वापस budget - 1;
		पूर्ण
tx_only:
		अगर (arm_wb) अणु
			q_vector->tx.ring[0].tx_stats.tx_क्रमce_wb++;
			i40e_enable_wb_on_itr(vsi, q_vector);
		पूर्ण
		वापस budget;
	पूर्ण

	अगर (vsi->back->flags & I40E_TXR_FLAGS_WB_ON_ITR)
		q_vector->arm_wb_state = false;

	/* Exit the polling mode, but करोn't re-enable पूर्णांकerrupts अगर stack might
	 * poll us due to busy-polling
	 */
	अगर (likely(napi_complete_करोne(napi, work_करोne)))
		i40e_update_enable_itr(vsi, q_vector);

	वापस min(work_करोne, budget - 1);
पूर्ण

/**
 * i40e_atr - Add a Flow Director ATR filter
 * @tx_ring:  ring to add programming descriptor to
 * @skb:      send buffer
 * @tx_flags: send tx flags
 **/
अटल व्योम i40e_atr(काष्ठा i40e_ring *tx_ring, काष्ठा sk_buff *skb,
		     u32 tx_flags)
अणु
	काष्ठा i40e_filter_program_desc *fdir_desc;
	काष्ठा i40e_pf *pf = tx_ring->vsi->back;
	जोड़ अणु
		अचिन्हित अक्षर *network;
		काष्ठा iphdr *ipv4;
		काष्ठा ipv6hdr *ipv6;
	पूर्ण hdr;
	काष्ठा tcphdr *th;
	अचिन्हित पूर्णांक hlen;
	u32 flex_ptype, dtype_cmd;
	पूर्णांक l4_proto;
	u16 i;

	/* make sure ATR is enabled */
	अगर (!(pf->flags & I40E_FLAG_FD_ATR_ENABLED))
		वापस;

	अगर (test_bit(__I40E_FD_ATR_AUTO_DISABLED, pf->state))
		वापस;

	/* अगर sampling is disabled करो nothing */
	अगर (!tx_ring->atr_sample_rate)
		वापस;

	/* Currently only IPv4/IPv6 with TCP is supported */
	अगर (!(tx_flags & (I40E_TX_FLAGS_IPV4 | I40E_TX_FLAGS_IPV6)))
		वापस;

	/* snag network header to get L4 type and address */
	hdr.network = (tx_flags & I40E_TX_FLAGS_UDP_TUNNEL) ?
		      skb_inner_network_header(skb) : skb_network_header(skb);

	/* Note: tx_flags माला_लो modअगरied to reflect inner protocols in
	 * tx_enable_csum function अगर encap is enabled.
	 */
	अगर (tx_flags & I40E_TX_FLAGS_IPV4) अणु
		/* access ihl as u8 to aव्योम unaligned access on ia64 */
		hlen = (hdr.network[0] & 0x0F) << 2;
		l4_proto = hdr.ipv4->protocol;
	पूर्ण अन्यथा अणु
		/* find the start of the innermost ipv6 header */
		अचिन्हित पूर्णांक inner_hlen = hdr.network - skb->data;
		अचिन्हित पूर्णांक h_offset = inner_hlen;

		/* this function updates h_offset to the end of the header */
		l4_proto =
		  ipv6_find_hdr(skb, &h_offset, IPPROTO_TCP, शून्य, शून्य);
		/* hlen will contain our best estimate of the tcp header */
		hlen = h_offset - inner_hlen;
	पूर्ण

	अगर (l4_proto != IPPROTO_TCP)
		वापस;

	th = (काष्ठा tcphdr *)(hdr.network + hlen);

	/* Due to lack of space, no more new filters can be programmed */
	अगर (th->syn && test_bit(__I40E_FD_ATR_AUTO_DISABLED, pf->state))
		वापस;
	अगर (pf->flags & I40E_FLAG_HW_ATR_EVICT_ENABLED) अणु
		/* HW ATR eviction will take care of removing filters on FIN
		 * and RST packets.
		 */
		अगर (th->fin || th->rst)
			वापस;
	पूर्ण

	tx_ring->atr_count++;

	/* sample on all syn/fin/rst packets or once every atr sample rate */
	अगर (!th->fin &&
	    !th->syn &&
	    !th->rst &&
	    (tx_ring->atr_count < tx_ring->atr_sample_rate))
		वापस;

	tx_ring->atr_count = 0;

	/* grab the next descriptor */
	i = tx_ring->next_to_use;
	fdir_desc = I40E_TX_FसूचीDESC(tx_ring, i);

	i++;
	tx_ring->next_to_use = (i < tx_ring->count) ? i : 0;

	flex_ptype = (tx_ring->queue_index << I40E_TXD_FLTR_QW0_QINDEX_SHIFT) &
		      I40E_TXD_FLTR_QW0_QINDEX_MASK;
	flex_ptype |= (tx_flags & I40E_TX_FLAGS_IPV4) ?
		      (I40E_FILTER_PCTYPE_NONF_IPV4_TCP <<
		       I40E_TXD_FLTR_QW0_PCTYPE_SHIFT) :
		      (I40E_FILTER_PCTYPE_NONF_IPV6_TCP <<
		       I40E_TXD_FLTR_QW0_PCTYPE_SHIFT);

	flex_ptype |= tx_ring->vsi->id << I40E_TXD_FLTR_QW0_DEST_VSI_SHIFT;

	dtype_cmd = I40E_TX_DESC_DTYPE_FILTER_PROG;

	dtype_cmd |= (th->fin || th->rst) ?
		     (I40E_FILTER_PROGRAM_DESC_PCMD_REMOVE <<
		      I40E_TXD_FLTR_QW1_PCMD_SHIFT) :
		     (I40E_FILTER_PROGRAM_DESC_PCMD_ADD_UPDATE <<
		      I40E_TXD_FLTR_QW1_PCMD_SHIFT);

	dtype_cmd |= I40E_FILTER_PROGRAM_DESC_DEST_सूचीECT_PACKET_QINDEX <<
		     I40E_TXD_FLTR_QW1_DEST_SHIFT;

	dtype_cmd |= I40E_FILTER_PROGRAM_DESC_FD_STATUS_FD_ID <<
		     I40E_TXD_FLTR_QW1_FD_STATUS_SHIFT;

	dtype_cmd |= I40E_TXD_FLTR_QW1_CNT_ENA_MASK;
	अगर (!(tx_flags & I40E_TX_FLAGS_UDP_TUNNEL))
		dtype_cmd |=
			((u32)I40E_FD_ATR_STAT_IDX(pf->hw.pf_id) <<
			I40E_TXD_FLTR_QW1_CNTINDEX_SHIFT) &
			I40E_TXD_FLTR_QW1_CNTINDEX_MASK;
	अन्यथा
		dtype_cmd |=
			((u32)I40E_FD_ATR_TUNNEL_STAT_IDX(pf->hw.pf_id) <<
			I40E_TXD_FLTR_QW1_CNTINDEX_SHIFT) &
			I40E_TXD_FLTR_QW1_CNTINDEX_MASK;

	अगर (pf->flags & I40E_FLAG_HW_ATR_EVICT_ENABLED)
		dtype_cmd |= I40E_TXD_FLTR_QW1_ATR_MASK;

	fdir_desc->qindex_flex_ptype_vsi = cpu_to_le32(flex_ptype);
	fdir_desc->rsvd = cpu_to_le32(0);
	fdir_desc->dtype_cmd_cntindex = cpu_to_le32(dtype_cmd);
	fdir_desc->fd_id = cpu_to_le32(0);
पूर्ण

/**
 * i40e_tx_prepare_vlan_flags - prepare generic TX VLAN tagging flags क्रम HW
 * @skb:     send buffer
 * @tx_ring: ring to send buffer on
 * @flags:   the tx flags to be set
 *
 * Checks the skb and set up correspondingly several generic transmit flags
 * related to VLAN tagging क्रम the HW, such as VLAN, DCB, etc.
 *
 * Returns error code indicate the frame should be dropped upon error and the
 * otherwise  वापसs 0 to indicate the flags has been set properly.
 **/
अटल अंतरभूत पूर्णांक i40e_tx_prepare_vlan_flags(काष्ठा sk_buff *skb,
					     काष्ठा i40e_ring *tx_ring,
					     u32 *flags)
अणु
	__be16 protocol = skb->protocol;
	u32  tx_flags = 0;

	अगर (protocol == htons(ETH_P_8021Q) &&
	    !(tx_ring->netdev->features & NETIF_F_HW_VLAN_CTAG_TX)) अणु
		/* When HW VLAN acceleration is turned off by the user the
		 * stack sets the protocol to 8021q so that the driver
		 * can take any steps required to support the SW only
		 * VLAN handling.  In our हाल the driver करोesn't need
		 * to take any further steps so just set the protocol
		 * to the encapsulated ethertype.
		 */
		skb->protocol = vlan_get_protocol(skb);
		जाओ out;
	पूर्ण

	/* अगर we have a HW VLAN tag being added, शेष to the HW one */
	अगर (skb_vlan_tag_present(skb)) अणु
		tx_flags |= skb_vlan_tag_get(skb) << I40E_TX_FLAGS_VLAN_SHIFT;
		tx_flags |= I40E_TX_FLAGS_HW_VLAN;
	/* अन्यथा अगर it is a SW VLAN, check the next protocol and store the tag */
	पूर्ण अन्यथा अगर (protocol == htons(ETH_P_8021Q)) अणु
		काष्ठा vlan_hdr *vhdr, _vhdr;

		vhdr = skb_header_poपूर्णांकer(skb, ETH_HLEN, माप(_vhdr), &_vhdr);
		अगर (!vhdr)
			वापस -EINVAL;

		protocol = vhdr->h_vlan_encapsulated_proto;
		tx_flags |= ntohs(vhdr->h_vlan_TCI) << I40E_TX_FLAGS_VLAN_SHIFT;
		tx_flags |= I40E_TX_FLAGS_SW_VLAN;
	पूर्ण

	अगर (!(tx_ring->vsi->back->flags & I40E_FLAG_DCB_ENABLED))
		जाओ out;

	/* Insert 802.1p priority पूर्णांकo VLAN header */
	अगर ((tx_flags & (I40E_TX_FLAGS_HW_VLAN | I40E_TX_FLAGS_SW_VLAN)) ||
	    (skb->priority != TC_PRIO_CONTROL)) अणु
		tx_flags &= ~I40E_TX_FLAGS_VLAN_PRIO_MASK;
		tx_flags |= (skb->priority & 0x7) <<
				I40E_TX_FLAGS_VLAN_PRIO_SHIFT;
		अगर (tx_flags & I40E_TX_FLAGS_SW_VLAN) अणु
			काष्ठा vlan_ethhdr *vhdr;
			पूर्णांक rc;

			rc = skb_cow_head(skb, 0);
			अगर (rc < 0)
				वापस rc;
			vhdr = (काष्ठा vlan_ethhdr *)skb->data;
			vhdr->h_vlan_TCI = htons(tx_flags >>
						 I40E_TX_FLAGS_VLAN_SHIFT);
		पूर्ण अन्यथा अणु
			tx_flags |= I40E_TX_FLAGS_HW_VLAN;
		पूर्ण
	पूर्ण

out:
	*flags = tx_flags;
	वापस 0;
पूर्ण

/**
 * i40e_tso - set up the tso context descriptor
 * @first:    poपूर्णांकer to first Tx buffer क्रम xmit
 * @hdr_len:  ptr to the size of the packet header
 * @cd_type_cmd_tso_mss: Quad Word 1
 *
 * Returns 0 अगर no TSO can happen, 1 अगर tso is going, or error
 **/
अटल पूर्णांक i40e_tso(काष्ठा i40e_tx_buffer *first, u8 *hdr_len,
		    u64 *cd_type_cmd_tso_mss)
अणु
	काष्ठा sk_buff *skb = first->skb;
	u64 cd_cmd, cd_tso_len, cd_mss;
	जोड़ अणु
		काष्ठा iphdr *v4;
		काष्ठा ipv6hdr *v6;
		अचिन्हित अक्षर *hdr;
	पूर्ण ip;
	जोड़ अणु
		काष्ठा tcphdr *tcp;
		काष्ठा udphdr *udp;
		अचिन्हित अक्षर *hdr;
	पूर्ण l4;
	u32 paylen, l4_offset;
	u16 gso_segs, gso_size;
	पूर्णांक err;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0;

	अगर (!skb_is_gso(skb))
		वापस 0;

	err = skb_cow_head(skb, 0);
	अगर (err < 0)
		वापस err;

	ip.hdr = skb_network_header(skb);
	l4.hdr = skb_transport_header(skb);

	/* initialize outer IP header fields */
	अगर (ip.v4->version == 4) अणु
		ip.v4->tot_len = 0;
		ip.v4->check = 0;
	पूर्ण अन्यथा अणु
		ip.v6->payload_len = 0;
	पूर्ण

	अगर (skb_shinfo(skb)->gso_type & (SKB_GSO_GRE |
					 SKB_GSO_GRE_CSUM |
					 SKB_GSO_IPXIP4 |
					 SKB_GSO_IPXIP6 |
					 SKB_GSO_UDP_TUNNEL |
					 SKB_GSO_UDP_TUNNEL_CSUM)) अणु
		अगर (!(skb_shinfo(skb)->gso_type & SKB_GSO_PARTIAL) &&
		    (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_TUNNEL_CSUM)) अणु
			l4.udp->len = 0;

			/* determine offset of outer transport header */
			l4_offset = l4.hdr - skb->data;

			/* हटाओ payload length from outer checksum */
			paylen = skb->len - l4_offset;
			csum_replace_by_dअगरf(&l4.udp->check,
					     (__क्रमce __wsum)htonl(paylen));
		पूर्ण

		/* reset poपूर्णांकers to inner headers */
		ip.hdr = skb_inner_network_header(skb);
		l4.hdr = skb_inner_transport_header(skb);

		/* initialize inner IP header fields */
		अगर (ip.v4->version == 4) अणु
			ip.v4->tot_len = 0;
			ip.v4->check = 0;
		पूर्ण अन्यथा अणु
			ip.v6->payload_len = 0;
		पूर्ण
	पूर्ण

	/* determine offset of inner transport header */
	l4_offset = l4.hdr - skb->data;

	/* हटाओ payload length from inner checksum */
	paylen = skb->len - l4_offset;

	अगर (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4) अणु
		csum_replace_by_dअगरf(&l4.udp->check, (__क्रमce __wsum)htonl(paylen));
		/* compute length of segmentation header */
		*hdr_len = माप(*l4.udp) + l4_offset;
	पूर्ण अन्यथा अणु
		csum_replace_by_dअगरf(&l4.tcp->check, (__क्रमce __wsum)htonl(paylen));
		/* compute length of segmentation header */
		*hdr_len = (l4.tcp->करोff * 4) + l4_offset;
	पूर्ण

	/* pull values out of skb_shinfo */
	gso_size = skb_shinfo(skb)->gso_size;
	gso_segs = skb_shinfo(skb)->gso_segs;

	/* update GSO size and bytecount with header size */
	first->gso_segs = gso_segs;
	first->bytecount += (first->gso_segs - 1) * *hdr_len;

	/* find the field values */
	cd_cmd = I40E_TX_CTX_DESC_TSO;
	cd_tso_len = skb->len - *hdr_len;
	cd_mss = gso_size;
	*cd_type_cmd_tso_mss |= (cd_cmd << I40E_TXD_CTX_QW1_CMD_SHIFT) |
				(cd_tso_len << I40E_TXD_CTX_QW1_TSO_LEN_SHIFT) |
				(cd_mss << I40E_TXD_CTX_QW1_MSS_SHIFT);
	वापस 1;
पूर्ण

/**
 * i40e_tsyn - set up the tsyn context descriptor
 * @tx_ring:  ptr to the ring to send
 * @skb:      ptr to the skb we're sending
 * @tx_flags: the collected send inक्रमmation
 * @cd_type_cmd_tso_mss: Quad Word 1
 *
 * Returns 0 अगर no Tx बारtamp can happen and 1 अगर the बारtamp will happen
 **/
अटल पूर्णांक i40e_tsyn(काष्ठा i40e_ring *tx_ring, काष्ठा sk_buff *skb,
		     u32 tx_flags, u64 *cd_type_cmd_tso_mss)
अणु
	काष्ठा i40e_pf *pf;

	अगर (likely(!(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP)))
		वापस 0;

	/* Tx बारtamps cannot be sampled when करोing TSO */
	अगर (tx_flags & I40E_TX_FLAGS_TSO)
		वापस 0;

	/* only बारtamp the outbound packet अगर the user has requested it and
	 * we are not alपढ़ोy transmitting a packet to be बारtamped
	 */
	pf = i40e_netdev_to_pf(tx_ring->netdev);
	अगर (!(pf->flags & I40E_FLAG_PTP))
		वापस 0;

	अगर (pf->ptp_tx &&
	    !test_and_set_bit_lock(__I40E_PTP_TX_IN_PROGRESS, pf->state)) अणु
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
		pf->ptp_tx_start = jअगरfies;
		pf->ptp_tx_skb = skb_get(skb);
	पूर्ण अन्यथा अणु
		pf->tx_hwtstamp_skipped++;
		वापस 0;
	पूर्ण

	*cd_type_cmd_tso_mss |= (u64)I40E_TX_CTX_DESC_TSYN <<
				I40E_TXD_CTX_QW1_CMD_SHIFT;

	वापस 1;
पूर्ण

/**
 * i40e_tx_enable_csum - Enable Tx checksum offloads
 * @skb: send buffer
 * @tx_flags: poपूर्णांकer to Tx flags currently set
 * @td_cmd: Tx descriptor command bits to set
 * @td_offset: Tx descriptor header offsets to set
 * @tx_ring: Tx descriptor ring
 * @cd_tunneling: ptr to context desc bits
 **/
अटल पूर्णांक i40e_tx_enable_csum(काष्ठा sk_buff *skb, u32 *tx_flags,
			       u32 *td_cmd, u32 *td_offset,
			       काष्ठा i40e_ring *tx_ring,
			       u32 *cd_tunneling)
अणु
	जोड़ अणु
		काष्ठा iphdr *v4;
		काष्ठा ipv6hdr *v6;
		अचिन्हित अक्षर *hdr;
	पूर्ण ip;
	जोड़ अणु
		काष्ठा tcphdr *tcp;
		काष्ठा udphdr *udp;
		अचिन्हित अक्षर *hdr;
	पूर्ण l4;
	अचिन्हित अक्षर *exthdr;
	u32 offset, cmd = 0;
	__be16 frag_off;
	u8 l4_proto = 0;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0;

	ip.hdr = skb_network_header(skb);
	l4.hdr = skb_transport_header(skb);

	/* compute outer L2 header size */
	offset = ((ip.hdr - skb->data) / 2) << I40E_TX_DESC_LENGTH_MACLEN_SHIFT;

	अगर (skb->encapsulation) अणु
		u32 tunnel = 0;
		/* define outer network header type */
		अगर (*tx_flags & I40E_TX_FLAGS_IPV4) अणु
			tunnel |= (*tx_flags & I40E_TX_FLAGS_TSO) ?
				  I40E_TX_CTX_EXT_IP_IPV4 :
				  I40E_TX_CTX_EXT_IP_IPV4_NO_CSUM;

			l4_proto = ip.v4->protocol;
		पूर्ण अन्यथा अगर (*tx_flags & I40E_TX_FLAGS_IPV6) अणु
			पूर्णांक ret;

			tunnel |= I40E_TX_CTX_EXT_IP_IPV6;

			exthdr = ip.hdr + माप(*ip.v6);
			l4_proto = ip.v6->nexthdr;
			ret = ipv6_skip_exthdr(skb, exthdr - skb->data,
					       &l4_proto, &frag_off);
			अगर (ret < 0)
				वापस -1;
		पूर्ण

		/* define outer transport */
		चयन (l4_proto) अणु
		हाल IPPROTO_UDP:
			tunnel |= I40E_TXD_CTX_UDP_TUNNELING;
			*tx_flags |= I40E_TX_FLAGS_UDP_TUNNEL;
			अवरोध;
		हाल IPPROTO_GRE:
			tunnel |= I40E_TXD_CTX_GRE_TUNNELING;
			*tx_flags |= I40E_TX_FLAGS_UDP_TUNNEL;
			अवरोध;
		हाल IPPROTO_IPIP:
		हाल IPPROTO_IPV6:
			*tx_flags |= I40E_TX_FLAGS_UDP_TUNNEL;
			l4.hdr = skb_inner_network_header(skb);
			अवरोध;
		शेष:
			अगर (*tx_flags & I40E_TX_FLAGS_TSO)
				वापस -1;

			skb_checksum_help(skb);
			वापस 0;
		पूर्ण

		/* compute outer L3 header size */
		tunnel |= ((l4.hdr - ip.hdr) / 4) <<
			  I40E_TXD_CTX_QW0_EXT_IPLEN_SHIFT;

		/* चयन IP header poपूर्णांकer from outer to inner header */
		ip.hdr = skb_inner_network_header(skb);

		/* compute tunnel header size */
		tunnel |= ((ip.hdr - l4.hdr) / 2) <<
			  I40E_TXD_CTX_QW0_NATLEN_SHIFT;

		/* indicate अगर we need to offload outer UDP header */
		अगर ((*tx_flags & I40E_TX_FLAGS_TSO) &&
		    !(skb_shinfo(skb)->gso_type & SKB_GSO_PARTIAL) &&
		    (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_TUNNEL_CSUM))
			tunnel |= I40E_TXD_CTX_QW0_L4T_CS_MASK;

		/* record tunnel offload values */
		*cd_tunneling |= tunnel;

		/* चयन L4 header poपूर्णांकer from outer to inner */
		l4.hdr = skb_inner_transport_header(skb);
		l4_proto = 0;

		/* reset type as we transition from outer to inner headers */
		*tx_flags &= ~(I40E_TX_FLAGS_IPV4 | I40E_TX_FLAGS_IPV6);
		अगर (ip.v4->version == 4)
			*tx_flags |= I40E_TX_FLAGS_IPV4;
		अगर (ip.v6->version == 6)
			*tx_flags |= I40E_TX_FLAGS_IPV6;
	पूर्ण

	/* Enable IP checksum offloads */
	अगर (*tx_flags & I40E_TX_FLAGS_IPV4) अणु
		l4_proto = ip.v4->protocol;
		/* the stack computes the IP header alपढ़ोy, the only समय we
		 * need the hardware to recompute it is in the हाल of TSO.
		 */
		cmd |= (*tx_flags & I40E_TX_FLAGS_TSO) ?
		       I40E_TX_DESC_CMD_IIPT_IPV4_CSUM :
		       I40E_TX_DESC_CMD_IIPT_IPV4;
	पूर्ण अन्यथा अगर (*tx_flags & I40E_TX_FLAGS_IPV6) अणु
		cmd |= I40E_TX_DESC_CMD_IIPT_IPV6;

		exthdr = ip.hdr + माप(*ip.v6);
		l4_proto = ip.v6->nexthdr;
		अगर (l4.hdr != exthdr)
			ipv6_skip_exthdr(skb, exthdr - skb->data,
					 &l4_proto, &frag_off);
	पूर्ण

	/* compute inner L3 header size */
	offset |= ((l4.hdr - ip.hdr) / 4) << I40E_TX_DESC_LENGTH_IPLEN_SHIFT;

	/* Enable L4 checksum offloads */
	चयन (l4_proto) अणु
	हाल IPPROTO_TCP:
		/* enable checksum offloads */
		cmd |= I40E_TX_DESC_CMD_L4T_खातापूर्णT_TCP;
		offset |= l4.tcp->करोff << I40E_TX_DESC_LENGTH_L4_FC_LEN_SHIFT;
		अवरोध;
	हाल IPPROTO_SCTP:
		/* enable SCTP checksum offload */
		cmd |= I40E_TX_DESC_CMD_L4T_खातापूर्णT_SCTP;
		offset |= (माप(काष्ठा sctphdr) >> 2) <<
			  I40E_TX_DESC_LENGTH_L4_FC_LEN_SHIFT;
		अवरोध;
	हाल IPPROTO_UDP:
		/* enable UDP checksum offload */
		cmd |= I40E_TX_DESC_CMD_L4T_खातापूर्णT_UDP;
		offset |= (माप(काष्ठा udphdr) >> 2) <<
			  I40E_TX_DESC_LENGTH_L4_FC_LEN_SHIFT;
		अवरोध;
	शेष:
		अगर (*tx_flags & I40E_TX_FLAGS_TSO)
			वापस -1;
		skb_checksum_help(skb);
		वापस 0;
	पूर्ण

	*td_cmd |= cmd;
	*td_offset |= offset;

	वापस 1;
पूर्ण

/**
 * i40e_create_tx_ctx - Build the Tx context descriptor
 * @tx_ring:  ring to create the descriptor on
 * @cd_type_cmd_tso_mss: Quad Word 1
 * @cd_tunneling: Quad Word 0 - bits 0-31
 * @cd_l2tag2: Quad Word 0 - bits 32-63
 **/
अटल व्योम i40e_create_tx_ctx(काष्ठा i40e_ring *tx_ring,
			       स्थिर u64 cd_type_cmd_tso_mss,
			       स्थिर u32 cd_tunneling, स्थिर u32 cd_l2tag2)
अणु
	काष्ठा i40e_tx_context_desc *context_desc;
	पूर्णांक i = tx_ring->next_to_use;

	अगर ((cd_type_cmd_tso_mss == I40E_TX_DESC_DTYPE_CONTEXT) &&
	    !cd_tunneling && !cd_l2tag2)
		वापस;

	/* grab the next descriptor */
	context_desc = I40E_TX_CTXTDESC(tx_ring, i);

	i++;
	tx_ring->next_to_use = (i < tx_ring->count) ? i : 0;

	/* cpu_to_le32 and assign to काष्ठा fields */
	context_desc->tunneling_params = cpu_to_le32(cd_tunneling);
	context_desc->l2tag2 = cpu_to_le16(cd_l2tag2);
	context_desc->rsvd = cpu_to_le16(0);
	context_desc->type_cmd_tso_mss = cpu_to_le64(cd_type_cmd_tso_mss);
पूर्ण

/**
 * __i40e_maybe_stop_tx - 2nd level check क्रम tx stop conditions
 * @tx_ring: the ring to be checked
 * @size:    the size buffer we want to assure is available
 *
 * Returns -EBUSY अगर a stop is needed, अन्यथा 0
 **/
पूर्णांक __i40e_maybe_stop_tx(काष्ठा i40e_ring *tx_ring, पूर्णांक size)
अणु
	netअगर_stop_subqueue(tx_ring->netdev, tx_ring->queue_index);
	/* Memory barrier beक्रमe checking head and tail */
	smp_mb();

	/* Check again in a हाल another CPU has just made room available. */
	अगर (likely(I40E_DESC_UNUSED(tx_ring) < size))
		वापस -EBUSY;

	/* A reprieve! - use start_queue because it करोesn't call schedule */
	netअगर_start_subqueue(tx_ring->netdev, tx_ring->queue_index);
	++tx_ring->tx_stats.restart_queue;
	वापस 0;
पूर्ण

/**
 * __i40e_chk_linearize - Check अगर there are more than 8 buffers per packet
 * @skb:      send buffer
 *
 * Note: Our HW can't DMA more than 8 buffers to build a packet on the wire
 * and so we need to figure out the हालs where we need to linearize the skb.
 *
 * For TSO we need to count the TSO header and segment payload separately.
 * As such we need to check हालs where we have 7 fragments or more as we
 * can potentially require 9 DMA transactions, 1 क्रम the TSO header, 1 क्रम
 * the segment payload in the first descriptor, and another 7 क्रम the
 * fragments.
 **/
bool __i40e_chk_linearize(काष्ठा sk_buff *skb)
अणु
	स्थिर skb_frag_t *frag, *stale;
	पूर्णांक nr_frags, sum;

	/* no need to check अगर number of frags is less than 7 */
	nr_frags = skb_shinfo(skb)->nr_frags;
	अगर (nr_frags < (I40E_MAX_BUFFER_TXD - 1))
		वापस false;

	/* We need to walk through the list and validate that each group
	 * of 6 fragments totals at least gso_size.
	 */
	nr_frags -= I40E_MAX_BUFFER_TXD - 2;
	frag = &skb_shinfo(skb)->frags[0];

	/* Initialize size to the negative value of gso_size minus 1.  We
	 * use this as the worst हाल scenerio in which the frag ahead
	 * of us only provides one byte which is why we are limited to 6
	 * descriptors क्रम a single transmit as the header and previous
	 * fragment are alपढ़ोy consuming 2 descriptors.
	 */
	sum = 1 - skb_shinfo(skb)->gso_size;

	/* Add size of frags 0 through 4 to create our initial sum */
	sum += skb_frag_size(frag++);
	sum += skb_frag_size(frag++);
	sum += skb_frag_size(frag++);
	sum += skb_frag_size(frag++);
	sum += skb_frag_size(frag++);

	/* Walk through fragments adding latest fragment, testing it, and
	 * then removing stale fragments from the sum.
	 */
	क्रम (stale = &skb_shinfo(skb)->frags[0];; stale++) अणु
		पूर्णांक stale_size = skb_frag_size(stale);

		sum += skb_frag_size(frag++);

		/* The stale fragment may present us with a smaller
		 * descriptor than the actual fragment size. To account
		 * क्रम that we need to हटाओ all the data on the front and
		 * figure out what the reमुख्यder would be in the last
		 * descriptor associated with the fragment.
		 */
		अगर (stale_size > I40E_MAX_DATA_PER_TXD) अणु
			पूर्णांक align_pad = -(skb_frag_off(stale)) &
					(I40E_MAX_READ_REQ_SIZE - 1);

			sum -= align_pad;
			stale_size -= align_pad;

			करो अणु
				sum -= I40E_MAX_DATA_PER_TXD_ALIGNED;
				stale_size -= I40E_MAX_DATA_PER_TXD_ALIGNED;
			पूर्ण जबतक (stale_size > I40E_MAX_DATA_PER_TXD);
		पूर्ण

		/* अगर sum is negative we failed to make sufficient progress */
		अगर (sum < 0)
			वापस true;

		अगर (!nr_frags--)
			अवरोध;

		sum -= stale_size;
	पूर्ण

	वापस false;
पूर्ण

/**
 * i40e_tx_map - Build the Tx descriptor
 * @tx_ring:  ring to send buffer on
 * @skb:      send buffer
 * @first:    first buffer info buffer to use
 * @tx_flags: collected send inक्रमmation
 * @hdr_len:  size of the packet header
 * @td_cmd:   the command field in the descriptor
 * @td_offset: offset क्रम checksum or crc
 *
 * Returns 0 on success, -1 on failure to DMA
 **/
अटल अंतरभूत पूर्णांक i40e_tx_map(काष्ठा i40e_ring *tx_ring, काष्ठा sk_buff *skb,
			      काष्ठा i40e_tx_buffer *first, u32 tx_flags,
			      स्थिर u8 hdr_len, u32 td_cmd, u32 td_offset)
अणु
	अचिन्हित पूर्णांक data_len = skb->data_len;
	अचिन्हित पूर्णांक size = skb_headlen(skb);
	skb_frag_t *frag;
	काष्ठा i40e_tx_buffer *tx_bi;
	काष्ठा i40e_tx_desc *tx_desc;
	u16 i = tx_ring->next_to_use;
	u32 td_tag = 0;
	dma_addr_t dma;
	u16 desc_count = 1;

	अगर (tx_flags & I40E_TX_FLAGS_HW_VLAN) अणु
		td_cmd |= I40E_TX_DESC_CMD_IL2TAG1;
		td_tag = (tx_flags & I40E_TX_FLAGS_VLAN_MASK) >>
			 I40E_TX_FLAGS_VLAN_SHIFT;
	पूर्ण

	first->tx_flags = tx_flags;

	dma = dma_map_single(tx_ring->dev, skb->data, size, DMA_TO_DEVICE);

	tx_desc = I40E_TX_DESC(tx_ring, i);
	tx_bi = first;

	क्रम (frag = &skb_shinfo(skb)->frags[0];; frag++) अणु
		अचिन्हित पूर्णांक max_data = I40E_MAX_DATA_PER_TXD_ALIGNED;

		अगर (dma_mapping_error(tx_ring->dev, dma))
			जाओ dma_error;

		/* record length, and DMA address */
		dma_unmap_len_set(tx_bi, len, size);
		dma_unmap_addr_set(tx_bi, dma, dma);

		/* align size to end of page */
		max_data += -dma & (I40E_MAX_READ_REQ_SIZE - 1);
		tx_desc->buffer_addr = cpu_to_le64(dma);

		जबतक (unlikely(size > I40E_MAX_DATA_PER_TXD)) अणु
			tx_desc->cmd_type_offset_bsz =
				build_ctob(td_cmd, td_offset,
					   max_data, td_tag);

			tx_desc++;
			i++;
			desc_count++;

			अगर (i == tx_ring->count) अणु
				tx_desc = I40E_TX_DESC(tx_ring, 0);
				i = 0;
			पूर्ण

			dma += max_data;
			size -= max_data;

			max_data = I40E_MAX_DATA_PER_TXD_ALIGNED;
			tx_desc->buffer_addr = cpu_to_le64(dma);
		पूर्ण

		अगर (likely(!data_len))
			अवरोध;

		tx_desc->cmd_type_offset_bsz = build_ctob(td_cmd, td_offset,
							  size, td_tag);

		tx_desc++;
		i++;
		desc_count++;

		अगर (i == tx_ring->count) अणु
			tx_desc = I40E_TX_DESC(tx_ring, 0);
			i = 0;
		पूर्ण

		size = skb_frag_size(frag);
		data_len -= size;

		dma = skb_frag_dma_map(tx_ring->dev, frag, 0, size,
				       DMA_TO_DEVICE);

		tx_bi = &tx_ring->tx_bi[i];
	पूर्ण

	netdev_tx_sent_queue(txring_txq(tx_ring), first->bytecount);

	i++;
	अगर (i == tx_ring->count)
		i = 0;

	tx_ring->next_to_use = i;

	i40e_maybe_stop_tx(tx_ring, DESC_NEEDED);

	/* ग_लिखो last descriptor with EOP bit */
	td_cmd |= I40E_TX_DESC_CMD_EOP;

	/* We OR these values together to check both against 4 (WB_STRIDE)
	 * below. This is safe since we करोn't re-use desc_count afterwards.
	 */
	desc_count |= ++tx_ring->packet_stride;

	अगर (desc_count >= WB_STRIDE) अणु
		/* ग_लिखो last descriptor with RS bit set */
		td_cmd |= I40E_TX_DESC_CMD_RS;
		tx_ring->packet_stride = 0;
	पूर्ण

	tx_desc->cmd_type_offset_bsz =
			build_ctob(td_cmd, td_offset, size, td_tag);

	skb_tx_बारtamp(skb);

	/* Force memory ग_लिखोs to complete beक्रमe letting h/w know there
	 * are new descriptors to fetch.
	 *
	 * We also use this memory barrier to make certain all of the
	 * status bits have been updated beक्रमe next_to_watch is written.
	 */
	wmb();

	/* set next_to_watch value indicating a packet is present */
	first->next_to_watch = tx_desc;

	/* notअगरy HW of packet */
	अगर (netअगर_xmit_stopped(txring_txq(tx_ring)) || !netdev_xmit_more()) अणु
		ग_लिखोl(i, tx_ring->tail);
	पूर्ण

	वापस 0;

dma_error:
	dev_info(tx_ring->dev, "TX DMA map failed\n");

	/* clear dma mappings क्रम failed tx_bi map */
	क्रम (;;) अणु
		tx_bi = &tx_ring->tx_bi[i];
		i40e_unmap_and_मुक्त_tx_resource(tx_ring, tx_bi);
		अगर (tx_bi == first)
			अवरोध;
		अगर (i == 0)
			i = tx_ring->count;
		i--;
	पूर्ण

	tx_ring->next_to_use = i;

	वापस -1;
पूर्ण

/**
 * i40e_xmit_xdp_ring - transmits an XDP buffer to an XDP Tx ring
 * @xdpf: data to transmit
 * @xdp_ring: XDP Tx ring
 **/
अटल पूर्णांक i40e_xmit_xdp_ring(काष्ठा xdp_frame *xdpf,
			      काष्ठा i40e_ring *xdp_ring)
अणु
	u16 i = xdp_ring->next_to_use;
	काष्ठा i40e_tx_buffer *tx_bi;
	काष्ठा i40e_tx_desc *tx_desc;
	व्योम *data = xdpf->data;
	u32 size = xdpf->len;
	dma_addr_t dma;

	अगर (!unlikely(I40E_DESC_UNUSED(xdp_ring))) अणु
		xdp_ring->tx_stats.tx_busy++;
		वापस I40E_XDP_CONSUMED;
	पूर्ण
	dma = dma_map_single(xdp_ring->dev, data, size, DMA_TO_DEVICE);
	अगर (dma_mapping_error(xdp_ring->dev, dma))
		वापस I40E_XDP_CONSUMED;

	tx_bi = &xdp_ring->tx_bi[i];
	tx_bi->bytecount = size;
	tx_bi->gso_segs = 1;
	tx_bi->xdpf = xdpf;

	/* record length, and DMA address */
	dma_unmap_len_set(tx_bi, len, size);
	dma_unmap_addr_set(tx_bi, dma, dma);

	tx_desc = I40E_TX_DESC(xdp_ring, i);
	tx_desc->buffer_addr = cpu_to_le64(dma);
	tx_desc->cmd_type_offset_bsz = build_ctob(I40E_TX_DESC_CMD_ICRC
						  | I40E_TXD_CMD,
						  0, size, 0);

	/* Make certain all of the status bits have been updated
	 * beक्रमe next_to_watch is written.
	 */
	smp_wmb();

	xdp_ring->xdp_tx_active++;
	i++;
	अगर (i == xdp_ring->count)
		i = 0;

	tx_bi->next_to_watch = tx_desc;
	xdp_ring->next_to_use = i;

	वापस I40E_XDP_TX;
पूर्ण

/**
 * i40e_xmit_frame_ring - Sends buffer on Tx ring
 * @skb:     send buffer
 * @tx_ring: ring to send buffer on
 *
 * Returns NETDEV_TX_OK अगर sent, अन्यथा an error code
 **/
अटल netdev_tx_t i40e_xmit_frame_ring(काष्ठा sk_buff *skb,
					काष्ठा i40e_ring *tx_ring)
अणु
	u64 cd_type_cmd_tso_mss = I40E_TX_DESC_DTYPE_CONTEXT;
	u32 cd_tunneling = 0, cd_l2tag2 = 0;
	काष्ठा i40e_tx_buffer *first;
	u32 td_offset = 0;
	u32 tx_flags = 0;
	__be16 protocol;
	u32 td_cmd = 0;
	u8 hdr_len = 0;
	पूर्णांक tso, count;
	पूर्णांक tsyn;

	/* prefetch the data, we'll need it later */
	prefetch(skb->data);

	i40e_trace(xmit_frame_ring, skb, tx_ring);

	count = i40e_xmit_descriptor_count(skb);
	अगर (i40e_chk_linearize(skb, count)) अणु
		अगर (__skb_linearize(skb)) अणु
			dev_kमुक्त_skb_any(skb);
			वापस NETDEV_TX_OK;
		पूर्ण
		count = i40e_txd_use_count(skb->len);
		tx_ring->tx_stats.tx_linearize++;
	पूर्ण

	/* need: 1 descriptor per page * PAGE_SIZE/I40E_MAX_DATA_PER_TXD,
	 *       + 1 desc क्रम skb_head_len/I40E_MAX_DATA_PER_TXD,
	 *       + 4 desc gap to aव्योम the cache line where head is,
	 *       + 1 desc क्रम context descriptor,
	 * otherwise try next समय
	 */
	अगर (i40e_maybe_stop_tx(tx_ring, count + 4 + 1)) अणु
		tx_ring->tx_stats.tx_busy++;
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* record the location of the first descriptor क्रम this packet */
	first = &tx_ring->tx_bi[tx_ring->next_to_use];
	first->skb = skb;
	first->bytecount = skb->len;
	first->gso_segs = 1;

	/* prepare the xmit flags */
	अगर (i40e_tx_prepare_vlan_flags(skb, tx_ring, &tx_flags))
		जाओ out_drop;

	/* obtain protocol of skb */
	protocol = vlan_get_protocol(skb);

	/* setup IPv4/IPv6 offloads */
	अगर (protocol == htons(ETH_P_IP))
		tx_flags |= I40E_TX_FLAGS_IPV4;
	अन्यथा अगर (protocol == htons(ETH_P_IPV6))
		tx_flags |= I40E_TX_FLAGS_IPV6;

	tso = i40e_tso(first, &hdr_len, &cd_type_cmd_tso_mss);

	अगर (tso < 0)
		जाओ out_drop;
	अन्यथा अगर (tso)
		tx_flags |= I40E_TX_FLAGS_TSO;

	/* Always offload the checksum, since it's in the data descriptor */
	tso = i40e_tx_enable_csum(skb, &tx_flags, &td_cmd, &td_offset,
				  tx_ring, &cd_tunneling);
	अगर (tso < 0)
		जाओ out_drop;

	tsyn = i40e_tsyn(tx_ring, skb, tx_flags, &cd_type_cmd_tso_mss);

	अगर (tsyn)
		tx_flags |= I40E_TX_FLAGS_TSYN;

	/* always enable CRC insertion offload */
	td_cmd |= I40E_TX_DESC_CMD_ICRC;

	i40e_create_tx_ctx(tx_ring, cd_type_cmd_tso_mss,
			   cd_tunneling, cd_l2tag2);

	/* Add Flow Director ATR अगर it's enabled.
	 *
	 * NOTE: this must always be directly beक्रमe the data descriptor.
	 */
	i40e_atr(tx_ring, skb, tx_flags);

	अगर (i40e_tx_map(tx_ring, skb, first, tx_flags, hdr_len,
			td_cmd, td_offset))
		जाओ cleanup_tx_tstamp;

	वापस NETDEV_TX_OK;

out_drop:
	i40e_trace(xmit_frame_ring_drop, first->skb, tx_ring);
	dev_kमुक्त_skb_any(first->skb);
	first->skb = शून्य;
cleanup_tx_tstamp:
	अगर (unlikely(tx_flags & I40E_TX_FLAGS_TSYN)) अणु
		काष्ठा i40e_pf *pf = i40e_netdev_to_pf(tx_ring->netdev);

		dev_kमुक्त_skb_any(pf->ptp_tx_skb);
		pf->ptp_tx_skb = शून्य;
		clear_bit_unlock(__I40E_PTP_TX_IN_PROGRESS, pf->state);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

/**
 * i40e_lan_xmit_frame - Selects the correct VSI and Tx queue to send buffer
 * @skb:    send buffer
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns NETDEV_TX_OK अगर sent, अन्यथा an error code
 **/
netdev_tx_t i40e_lan_xmit_frame(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_ring *tx_ring = vsi->tx_rings[skb->queue_mapping];

	/* hardware can't handle really लघु frames, hardware padding works
	 * beyond this poपूर्णांक
	 */
	अगर (skb_put_padto(skb, I40E_MIN_TX_LEN))
		वापस NETDEV_TX_OK;

	वापस i40e_xmit_frame_ring(skb, tx_ring);
पूर्ण

/**
 * i40e_xdp_xmit - Implements nकरो_xdp_xmit
 * @dev: netdev
 * @n: number of frames
 * @frames: array of XDP buffer poपूर्णांकers
 * @flags: XDP extra info
 *
 * Returns number of frames successfully sent. Failed frames
 * will be मुक्त'ed by XDP core.
 *
 * For error हालs, a negative त्रुटि_सं code is वापसed and no-frames
 * are transmitted (caller must handle मुक्तing frames).
 **/
पूर्णांक i40e_xdp_xmit(काष्ठा net_device *dev, पूर्णांक n, काष्ठा xdp_frame **frames,
		  u32 flags)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(dev);
	अचिन्हित पूर्णांक queue_index = smp_processor_id();
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_ring *xdp_ring;
	पूर्णांक nxmit = 0;
	पूर्णांक i;

	अगर (test_bit(__I40E_VSI_DOWN, vsi->state))
		वापस -ENETDOWN;

	अगर (!i40e_enabled_xdp_vsi(vsi) || queue_index >= vsi->num_queue_pairs ||
	    test_bit(__I40E_CONFIG_BUSY, pf->state))
		वापस -ENXIO;

	अगर (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		वापस -EINVAL;

	xdp_ring = vsi->xdp_rings[queue_index];

	क्रम (i = 0; i < n; i++) अणु
		काष्ठा xdp_frame *xdpf = frames[i];
		पूर्णांक err;

		err = i40e_xmit_xdp_ring(xdpf, xdp_ring);
		अगर (err != I40E_XDP_TX)
			अवरोध;
		nxmit++;
	पूर्ण

	अगर (unlikely(flags & XDP_XMIT_FLUSH))
		i40e_xdp_ring_update_tail(xdp_ring);

	वापस nxmit;
पूर्ण
