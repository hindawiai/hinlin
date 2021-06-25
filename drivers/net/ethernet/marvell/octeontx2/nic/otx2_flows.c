<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell OcteonTx2 RVU Physical Function ethernet driver
 *
 * Copyright (C) 2020 Marvell.
 */

#समावेश <net/ipv6.h>

#समावेश "otx2_common.h"

#घोषणा OTX2_DEFAULT_ACTION	0x1

काष्ठा otx2_flow अणु
	काष्ठा ethtool_rx_flow_spec flow_spec;
	काष्ठा list_head list;
	u32 location;
	u16 entry;
	bool is_vf;
	u8 rss_ctx_id;
	पूर्णांक vf;
पूर्ण;

पूर्णांक otx2_alloc_mcam_entries(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा otx2_flow_config *flow_cfg = pfvf->flow_cfg;
	काष्ठा npc_mcam_alloc_entry_req *req;
	काष्ठा npc_mcam_alloc_entry_rsp *rsp;
	पूर्णांक vf_vlan_max_flows;
	पूर्णांक i;

	mutex_lock(&pfvf->mbox.lock);

	req = otx2_mbox_alloc_msg_npc_mcam_alloc_entry(&pfvf->mbox);
	अगर (!req) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	vf_vlan_max_flows = pfvf->total_vfs * OTX2_PER_VF_VLAN_FLOWS;
	req->contig = false;
	req->count = OTX2_MCAM_COUNT + vf_vlan_max_flows;

	/* Send message to AF */
	अगर (otx2_sync_mbox_msg(&pfvf->mbox)) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस -EINVAL;
	पूर्ण

	rsp = (काष्ठा npc_mcam_alloc_entry_rsp *)otx2_mbox_get_rsp
	       (&pfvf->mbox.mbox, 0, &req->hdr);

	अगर (rsp->count != req->count) अणु
		netdev_info(pfvf->netdev,
			    "Unable to allocate %d MCAM entries, got %d\n",
			    req->count, rsp->count);
		/* support only ntuples here */
		flow_cfg->ntuple_max_flows = rsp->count;
		flow_cfg->ntuple_offset = 0;
		pfvf->flags |= OTX2_FLAG_NTUPLE_SUPPORT;
		flow_cfg->tc_max_flows = flow_cfg->ntuple_max_flows;
		pfvf->flags |= OTX2_FLAG_TC_FLOWER_SUPPORT;
	पूर्ण अन्यथा अणु
		flow_cfg->vf_vlan_offset = 0;
		flow_cfg->ntuple_offset = flow_cfg->vf_vlan_offset +
						vf_vlan_max_flows;
		flow_cfg->tc_flower_offset = flow_cfg->ntuple_offset;
		flow_cfg->unicast_offset = flow_cfg->ntuple_offset +
						OTX2_MAX_NTUPLE_FLOWS;
		flow_cfg->rx_vlan_offset = flow_cfg->unicast_offset +
						OTX2_MAX_UNICAST_FLOWS;
		pfvf->flags |= OTX2_FLAG_NTUPLE_SUPPORT;
		pfvf->flags |= OTX2_FLAG_UCAST_FLTR_SUPPORT;
		pfvf->flags |= OTX2_FLAG_RX_VLAN_SUPPORT;
		pfvf->flags |= OTX2_FLAG_VF_VLAN_SUPPORT;
		pfvf->flags |= OTX2_FLAG_TC_FLOWER_SUPPORT;
	पूर्ण

	क्रम (i = 0; i < rsp->count; i++)
		flow_cfg->entry[i] = rsp->entry_list[i];

	pfvf->flags |= OTX2_FLAG_MCAM_ENTRIES_ALLOC;

	mutex_unlock(&pfvf->mbox.lock);

	वापस 0;
पूर्ण

पूर्णांक otx2_mcam_flow_init(काष्ठा otx2_nic *pf)
अणु
	पूर्णांक err;

	pf->flow_cfg = devm_kzalloc(pf->dev, माप(काष्ठा otx2_flow_config),
				    GFP_KERNEL);
	अगर (!pf->flow_cfg)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&pf->flow_cfg->flow_list);

	pf->flow_cfg->ntuple_max_flows = OTX2_MAX_NTUPLE_FLOWS;
	pf->flow_cfg->tc_max_flows = pf->flow_cfg->ntuple_max_flows;

	err = otx2_alloc_mcam_entries(pf);
	अगर (err)
		वापस err;

	pf->mac_table = devm_kzalloc(pf->dev, माप(काष्ठा otx2_mac_table)
					* OTX2_MAX_UNICAST_FLOWS, GFP_KERNEL);
	अगर (!pf->mac_table)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम otx2_mcam_flow_del(काष्ठा otx2_nic *pf)
अणु
	otx2_destroy_mcam_flows(pf);
पूर्ण

/*  On success adds mcam entry
 *  On failure enable promisous mode
 */
अटल पूर्णांक otx2_करो_add_macfilter(काष्ठा otx2_nic *pf, स्थिर u8 *mac)
अणु
	काष्ठा otx2_flow_config *flow_cfg = pf->flow_cfg;
	काष्ठा npc_install_flow_req *req;
	पूर्णांक err, i;

	अगर (!(pf->flags & OTX2_FLAG_UCAST_FLTR_SUPPORT))
		वापस -ENOMEM;

	/* करोnt have मुक्त mcam entries or uc list is greater than alloted */
	अगर (netdev_uc_count(pf->netdev) > OTX2_MAX_UNICAST_FLOWS)
		वापस -ENOMEM;

	mutex_lock(&pf->mbox.lock);
	req = otx2_mbox_alloc_msg_npc_install_flow(&pf->mbox);
	अगर (!req) अणु
		mutex_unlock(&pf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	/* unicast offset starts with 32 0..31 क्रम ntuple */
	क्रम (i = 0; i <  OTX2_MAX_UNICAST_FLOWS; i++) अणु
		अगर (pf->mac_table[i].inuse)
			जारी;
		ether_addr_copy(pf->mac_table[i].addr, mac);
		pf->mac_table[i].inuse = true;
		pf->mac_table[i].mcam_entry =
			flow_cfg->entry[i + flow_cfg->unicast_offset];
		req->entry =  pf->mac_table[i].mcam_entry;
		अवरोध;
	पूर्ण

	ether_addr_copy(req->packet.dmac, mac);
	eth_broadcast_addr((u8 *)&req->mask.dmac);
	req->features = BIT_ULL(NPC_DMAC);
	req->channel = pf->hw.rx_chan_base;
	req->पूर्णांकf = NIX_INTF_RX;
	req->op = NIX_RX_ACTION_DEFAULT;
	req->set_cntr = 1;

	err = otx2_sync_mbox_msg(&pf->mbox);
	mutex_unlock(&pf->mbox.lock);

	वापस err;
पूर्ण

पूर्णांक otx2_add_macfilter(काष्ठा net_device *netdev, स्थिर u8 *mac)
अणु
	काष्ठा otx2_nic *pf = netdev_priv(netdev);

	वापस otx2_करो_add_macfilter(pf, mac);
पूर्ण

अटल bool otx2_get_mcamentry_क्रम_mac(काष्ठा otx2_nic *pf, स्थिर u8 *mac,
				       पूर्णांक *mcam_entry)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < OTX2_MAX_UNICAST_FLOWS; i++) अणु
		अगर (!pf->mac_table[i].inuse)
			जारी;

		अगर (ether_addr_equal(pf->mac_table[i].addr, mac)) अणु
			*mcam_entry = pf->mac_table[i].mcam_entry;
			pf->mac_table[i].inuse = false;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक otx2_del_macfilter(काष्ठा net_device *netdev, स्थिर u8 *mac)
अणु
	काष्ठा otx2_nic *pf = netdev_priv(netdev);
	काष्ठा npc_delete_flow_req *req;
	पूर्णांक err, mcam_entry;

	/* check करोes mcam entry exists क्रम given mac */
	अगर (!otx2_get_mcamentry_क्रम_mac(pf, mac, &mcam_entry))
		वापस 0;

	mutex_lock(&pf->mbox.lock);
	req = otx2_mbox_alloc_msg_npc_delete_flow(&pf->mbox);
	अगर (!req) अणु
		mutex_unlock(&pf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण
	req->entry = mcam_entry;
	/* Send message to AF */
	err = otx2_sync_mbox_msg(&pf->mbox);
	mutex_unlock(&pf->mbox.lock);

	वापस err;
पूर्ण

अटल काष्ठा otx2_flow *otx2_find_flow(काष्ठा otx2_nic *pfvf, u32 location)
अणु
	काष्ठा otx2_flow *iter;

	list_क्रम_each_entry(iter, &pfvf->flow_cfg->flow_list, list) अणु
		अगर (iter->location == location)
			वापस iter;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम otx2_add_flow_to_list(काष्ठा otx2_nic *pfvf, काष्ठा otx2_flow *flow)
अणु
	काष्ठा list_head *head = &pfvf->flow_cfg->flow_list;
	काष्ठा otx2_flow *iter;

	list_क्रम_each_entry(iter, &pfvf->flow_cfg->flow_list, list) अणु
		अगर (iter->location > flow->location)
			अवरोध;
		head = &iter->list;
	पूर्ण

	list_add(&flow->list, head);
पूर्ण

पूर्णांक otx2_get_flow(काष्ठा otx2_nic *pfvf, काष्ठा ethtool_rxnfc *nfc,
		  u32 location)
अणु
	काष्ठा otx2_flow *iter;

	अगर (location >= pfvf->flow_cfg->ntuple_max_flows)
		वापस -EINVAL;

	list_क्रम_each_entry(iter, &pfvf->flow_cfg->flow_list, list) अणु
		अगर (iter->location == location) अणु
			nfc->fs = iter->flow_spec;
			nfc->rss_context = iter->rss_ctx_id;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

पूर्णांक otx2_get_all_flows(काष्ठा otx2_nic *pfvf, काष्ठा ethtool_rxnfc *nfc,
		       u32 *rule_locs)
अणु
	u32 rule_cnt = nfc->rule_cnt;
	u32 location = 0;
	पूर्णांक idx = 0;
	पूर्णांक err = 0;

	nfc->data = pfvf->flow_cfg->ntuple_max_flows;
	जबतक ((!err || err == -ENOENT) && idx < rule_cnt) अणु
		err = otx2_get_flow(pfvf, nfc, location);
		अगर (!err)
			rule_locs[idx++] = location;
		location++;
	पूर्ण
	nfc->rule_cnt = rule_cnt;

	वापस err;
पूर्ण

अटल पूर्णांक otx2_prepare_ipv4_flow(काष्ठा ethtool_rx_flow_spec *fsp,
				  काष्ठा npc_install_flow_req *req,
				  u32 flow_type)
अणु
	काष्ठा ethtool_usrip4_spec *ipv4_usr_mask = &fsp->m_u.usr_ip4_spec;
	काष्ठा ethtool_usrip4_spec *ipv4_usr_hdr = &fsp->h_u.usr_ip4_spec;
	काष्ठा ethtool_tcpip4_spec *ipv4_l4_mask = &fsp->m_u.tcp_ip4_spec;
	काष्ठा ethtool_tcpip4_spec *ipv4_l4_hdr = &fsp->h_u.tcp_ip4_spec;
	काष्ठा ethtool_ah_espip4_spec *ah_esp_hdr = &fsp->h_u.ah_ip4_spec;
	काष्ठा ethtool_ah_espip4_spec *ah_esp_mask = &fsp->m_u.ah_ip4_spec;
	काष्ठा flow_msg *pmask = &req->mask;
	काष्ठा flow_msg *pkt = &req->packet;

	चयन (flow_type) अणु
	हाल IP_USER_FLOW:
		अगर (ipv4_usr_mask->ip4src) अणु
			स_नकल(&pkt->ip4src, &ipv4_usr_hdr->ip4src,
			       माप(pkt->ip4src));
			स_नकल(&pmask->ip4src, &ipv4_usr_mask->ip4src,
			       माप(pmask->ip4src));
			req->features |= BIT_ULL(NPC_SIP_IPV4);
		पूर्ण
		अगर (ipv4_usr_mask->ip4dst) अणु
			स_नकल(&pkt->ip4dst, &ipv4_usr_hdr->ip4dst,
			       माप(pkt->ip4dst));
			स_नकल(&pmask->ip4dst, &ipv4_usr_mask->ip4dst,
			       माप(pmask->ip4dst));
			req->features |= BIT_ULL(NPC_DIP_IPV4);
		पूर्ण
		अगर (ipv4_usr_mask->tos) अणु
			pkt->tos = ipv4_usr_hdr->tos;
			pmask->tos = ipv4_usr_mask->tos;
			req->features |= BIT_ULL(NPC_TOS);
		पूर्ण
		अगर (ipv4_usr_mask->proto) अणु
			चयन (ipv4_usr_hdr->proto) अणु
			हाल IPPROTO_ICMP:
				req->features |= BIT_ULL(NPC_IPPROTO_ICMP);
				अवरोध;
			हाल IPPROTO_TCP:
				req->features |= BIT_ULL(NPC_IPPROTO_TCP);
				अवरोध;
			हाल IPPROTO_UDP:
				req->features |= BIT_ULL(NPC_IPPROTO_UDP);
				अवरोध;
			हाल IPPROTO_SCTP:
				req->features |= BIT_ULL(NPC_IPPROTO_SCTP);
				अवरोध;
			हाल IPPROTO_AH:
				req->features |= BIT_ULL(NPC_IPPROTO_AH);
				अवरोध;
			हाल IPPROTO_ESP:
				req->features |= BIT_ULL(NPC_IPPROTO_ESP);
				अवरोध;
			शेष:
				वापस -EOPNOTSUPP;
			पूर्ण
		पूर्ण
		pkt->etype = cpu_to_be16(ETH_P_IP);
		pmask->etype = cpu_to_be16(0xFFFF);
		req->features |= BIT_ULL(NPC_ETYPE);
		अवरोध;
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
	हाल SCTP_V4_FLOW:
		pkt->etype = cpu_to_be16(ETH_P_IP);
		pmask->etype = cpu_to_be16(0xFFFF);
		req->features |= BIT_ULL(NPC_ETYPE);
		अगर (ipv4_l4_mask->ip4src) अणु
			स_नकल(&pkt->ip4src, &ipv4_l4_hdr->ip4src,
			       माप(pkt->ip4src));
			स_नकल(&pmask->ip4src, &ipv4_l4_mask->ip4src,
			       माप(pmask->ip4src));
			req->features |= BIT_ULL(NPC_SIP_IPV4);
		पूर्ण
		अगर (ipv4_l4_mask->ip4dst) अणु
			स_नकल(&pkt->ip4dst, &ipv4_l4_hdr->ip4dst,
			       माप(pkt->ip4dst));
			स_नकल(&pmask->ip4dst, &ipv4_l4_mask->ip4dst,
			       माप(pmask->ip4dst));
			req->features |= BIT_ULL(NPC_DIP_IPV4);
		पूर्ण
		अगर (ipv4_l4_mask->tos) अणु
			pkt->tos = ipv4_l4_hdr->tos;
			pmask->tos = ipv4_l4_mask->tos;
			req->features |= BIT_ULL(NPC_TOS);
		पूर्ण
		अगर (ipv4_l4_mask->psrc) अणु
			स_नकल(&pkt->sport, &ipv4_l4_hdr->psrc,
			       माप(pkt->sport));
			स_नकल(&pmask->sport, &ipv4_l4_mask->psrc,
			       माप(pmask->sport));
			अगर (flow_type == UDP_V4_FLOW)
				req->features |= BIT_ULL(NPC_SPORT_UDP);
			अन्यथा अगर (flow_type == TCP_V4_FLOW)
				req->features |= BIT_ULL(NPC_SPORT_TCP);
			अन्यथा
				req->features |= BIT_ULL(NPC_SPORT_SCTP);
		पूर्ण
		अगर (ipv4_l4_mask->pdst) अणु
			स_नकल(&pkt->dport, &ipv4_l4_hdr->pdst,
			       माप(pkt->dport));
			स_नकल(&pmask->dport, &ipv4_l4_mask->pdst,
			       माप(pmask->dport));
			अगर (flow_type == UDP_V4_FLOW)
				req->features |= BIT_ULL(NPC_DPORT_UDP);
			अन्यथा अगर (flow_type == TCP_V4_FLOW)
				req->features |= BIT_ULL(NPC_DPORT_TCP);
			अन्यथा
				req->features |= BIT_ULL(NPC_DPORT_SCTP);
		पूर्ण
		अगर (flow_type == UDP_V4_FLOW)
			req->features |= BIT_ULL(NPC_IPPROTO_UDP);
		अन्यथा अगर (flow_type == TCP_V4_FLOW)
			req->features |= BIT_ULL(NPC_IPPROTO_TCP);
		अन्यथा
			req->features |= BIT_ULL(NPC_IPPROTO_SCTP);
		अवरोध;
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
		pkt->etype = cpu_to_be16(ETH_P_IP);
		pmask->etype = cpu_to_be16(0xFFFF);
		req->features |= BIT_ULL(NPC_ETYPE);
		अगर (ah_esp_mask->ip4src) अणु
			स_नकल(&pkt->ip4src, &ah_esp_hdr->ip4src,
			       माप(pkt->ip4src));
			स_नकल(&pmask->ip4src, &ah_esp_mask->ip4src,
			       माप(pmask->ip4src));
			req->features |= BIT_ULL(NPC_SIP_IPV4);
		पूर्ण
		अगर (ah_esp_mask->ip4dst) अणु
			स_नकल(&pkt->ip4dst, &ah_esp_hdr->ip4dst,
			       माप(pkt->ip4dst));
			स_नकल(&pmask->ip4dst, &ah_esp_mask->ip4dst,
			       माप(pmask->ip4dst));
			req->features |= BIT_ULL(NPC_DIP_IPV4);
		पूर्ण
		अगर (ah_esp_mask->tos) अणु
			pkt->tos = ah_esp_hdr->tos;
			pmask->tos = ah_esp_mask->tos;
			req->features |= BIT_ULL(NPC_TOS);
		पूर्ण

		/* NPC profile करोesn't extract AH/ESP header fields */
		अगर (ah_esp_mask->spi & ah_esp_hdr->spi)
			वापस -EOPNOTSUPP;

		अगर (flow_type == AH_V4_FLOW)
			req->features |= BIT_ULL(NPC_IPPROTO_AH);
		अन्यथा
			req->features |= BIT_ULL(NPC_IPPROTO_ESP);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक otx2_prepare_ipv6_flow(काष्ठा ethtool_rx_flow_spec *fsp,
				  काष्ठा npc_install_flow_req *req,
				  u32 flow_type)
अणु
	काष्ठा ethtool_usrip6_spec *ipv6_usr_mask = &fsp->m_u.usr_ip6_spec;
	काष्ठा ethtool_usrip6_spec *ipv6_usr_hdr = &fsp->h_u.usr_ip6_spec;
	काष्ठा ethtool_tcpip6_spec *ipv6_l4_mask = &fsp->m_u.tcp_ip6_spec;
	काष्ठा ethtool_tcpip6_spec *ipv6_l4_hdr = &fsp->h_u.tcp_ip6_spec;
	काष्ठा ethtool_ah_espip6_spec *ah_esp_hdr = &fsp->h_u.ah_ip6_spec;
	काष्ठा ethtool_ah_espip6_spec *ah_esp_mask = &fsp->m_u.ah_ip6_spec;
	काष्ठा flow_msg *pmask = &req->mask;
	काष्ठा flow_msg *pkt = &req->packet;

	चयन (flow_type) अणु
	हाल IPV6_USER_FLOW:
		अगर (!ipv6_addr_any((काष्ठा in6_addr *)ipv6_usr_mask->ip6src)) अणु
			स_नकल(&pkt->ip6src, &ipv6_usr_hdr->ip6src,
			       माप(pkt->ip6src));
			स_नकल(&pmask->ip6src, &ipv6_usr_mask->ip6src,
			       माप(pmask->ip6src));
			req->features |= BIT_ULL(NPC_SIP_IPV6);
		पूर्ण
		अगर (!ipv6_addr_any((काष्ठा in6_addr *)ipv6_usr_mask->ip6dst)) अणु
			स_नकल(&pkt->ip6dst, &ipv6_usr_hdr->ip6dst,
			       माप(pkt->ip6dst));
			स_नकल(&pmask->ip6dst, &ipv6_usr_mask->ip6dst,
			       माप(pmask->ip6dst));
			req->features |= BIT_ULL(NPC_DIP_IPV6);
		पूर्ण
		pkt->etype = cpu_to_be16(ETH_P_IPV6);
		pmask->etype = cpu_to_be16(0xFFFF);
		req->features |= BIT_ULL(NPC_ETYPE);
		अवरोध;
	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW:
	हाल SCTP_V6_FLOW:
		pkt->etype = cpu_to_be16(ETH_P_IPV6);
		pmask->etype = cpu_to_be16(0xFFFF);
		req->features |= BIT_ULL(NPC_ETYPE);
		अगर (!ipv6_addr_any((काष्ठा in6_addr *)ipv6_l4_mask->ip6src)) अणु
			स_नकल(&pkt->ip6src, &ipv6_l4_hdr->ip6src,
			       माप(pkt->ip6src));
			स_नकल(&pmask->ip6src, &ipv6_l4_mask->ip6src,
			       माप(pmask->ip6src));
			req->features |= BIT_ULL(NPC_SIP_IPV6);
		पूर्ण
		अगर (!ipv6_addr_any((काष्ठा in6_addr *)ipv6_l4_mask->ip6dst)) अणु
			स_नकल(&pkt->ip6dst, &ipv6_l4_hdr->ip6dst,
			       माप(pkt->ip6dst));
			स_नकल(&pmask->ip6dst, &ipv6_l4_mask->ip6dst,
			       माप(pmask->ip6dst));
			req->features |= BIT_ULL(NPC_DIP_IPV6);
		पूर्ण
		अगर (ipv6_l4_mask->psrc) अणु
			स_नकल(&pkt->sport, &ipv6_l4_hdr->psrc,
			       माप(pkt->sport));
			स_नकल(&pmask->sport, &ipv6_l4_mask->psrc,
			       माप(pmask->sport));
			अगर (flow_type == UDP_V6_FLOW)
				req->features |= BIT_ULL(NPC_SPORT_UDP);
			अन्यथा अगर (flow_type == TCP_V6_FLOW)
				req->features |= BIT_ULL(NPC_SPORT_TCP);
			अन्यथा
				req->features |= BIT_ULL(NPC_SPORT_SCTP);
		पूर्ण
		अगर (ipv6_l4_mask->pdst) अणु
			स_नकल(&pkt->dport, &ipv6_l4_hdr->pdst,
			       माप(pkt->dport));
			स_नकल(&pmask->dport, &ipv6_l4_mask->pdst,
			       माप(pmask->dport));
			अगर (flow_type == UDP_V6_FLOW)
				req->features |= BIT_ULL(NPC_DPORT_UDP);
			अन्यथा अगर (flow_type == TCP_V6_FLOW)
				req->features |= BIT_ULL(NPC_DPORT_TCP);
			अन्यथा
				req->features |= BIT_ULL(NPC_DPORT_SCTP);
		पूर्ण
		अगर (flow_type == UDP_V6_FLOW)
			req->features |= BIT_ULL(NPC_IPPROTO_UDP);
		अन्यथा अगर (flow_type == TCP_V6_FLOW)
			req->features |= BIT_ULL(NPC_IPPROTO_TCP);
		अन्यथा
			req->features |= BIT_ULL(NPC_IPPROTO_SCTP);
		अवरोध;
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
		pkt->etype = cpu_to_be16(ETH_P_IPV6);
		pmask->etype = cpu_to_be16(0xFFFF);
		req->features |= BIT_ULL(NPC_ETYPE);
		अगर (!ipv6_addr_any((काष्ठा in6_addr *)ah_esp_hdr->ip6src)) अणु
			स_नकल(&pkt->ip6src, &ah_esp_hdr->ip6src,
			       माप(pkt->ip6src));
			स_नकल(&pmask->ip6src, &ah_esp_mask->ip6src,
			       माप(pmask->ip6src));
			req->features |= BIT_ULL(NPC_SIP_IPV6);
		पूर्ण
		अगर (!ipv6_addr_any((काष्ठा in6_addr *)ah_esp_hdr->ip6dst)) अणु
			स_नकल(&pkt->ip6dst, &ah_esp_hdr->ip6dst,
			       माप(pkt->ip6dst));
			स_नकल(&pmask->ip6dst, &ah_esp_mask->ip6dst,
			       माप(pmask->ip6dst));
			req->features |= BIT_ULL(NPC_DIP_IPV6);
		पूर्ण

		/* NPC profile करोesn't extract AH/ESP header fields */
		अगर ((ah_esp_mask->spi & ah_esp_hdr->spi) ||
		    (ah_esp_mask->tclass & ah_esp_mask->tclass))
			वापस -EOPNOTSUPP;

		अगर (flow_type == AH_V6_FLOW)
			req->features |= BIT_ULL(NPC_IPPROTO_AH);
		अन्यथा
			req->features |= BIT_ULL(NPC_IPPROTO_ESP);
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक otx2_prepare_flow_request(काष्ठा ethtool_rx_flow_spec *fsp,
			      काष्ठा npc_install_flow_req *req)
अणु
	काष्ठा ethhdr *eth_mask = &fsp->m_u.ether_spec;
	काष्ठा ethhdr *eth_hdr = &fsp->h_u.ether_spec;
	काष्ठा flow_msg *pmask = &req->mask;
	काष्ठा flow_msg *pkt = &req->packet;
	u32 flow_type;
	पूर्णांक ret;

	flow_type = fsp->flow_type & ~(FLOW_EXT | FLOW_MAC_EXT | FLOW_RSS);
	चयन (flow_type) अणु
	/* bits not set in mask are करोn't care */
	हाल ETHER_FLOW:
		अगर (!is_zero_ether_addr(eth_mask->h_source)) अणु
			ether_addr_copy(pkt->smac, eth_hdr->h_source);
			ether_addr_copy(pmask->smac, eth_mask->h_source);
			req->features |= BIT_ULL(NPC_SMAC);
		पूर्ण
		अगर (!is_zero_ether_addr(eth_mask->h_dest)) अणु
			ether_addr_copy(pkt->dmac, eth_hdr->h_dest);
			ether_addr_copy(pmask->dmac, eth_mask->h_dest);
			req->features |= BIT_ULL(NPC_DMAC);
		पूर्ण
		अगर (eth_mask->h_proto) अणु
			स_नकल(&pkt->etype, &eth_hdr->h_proto,
			       माप(pkt->etype));
			स_नकल(&pmask->etype, &eth_mask->h_proto,
			       माप(pmask->etype));
			req->features |= BIT_ULL(NPC_ETYPE);
		पूर्ण
		अवरोध;
	हाल IP_USER_FLOW:
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
	हाल SCTP_V4_FLOW:
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
		ret = otx2_prepare_ipv4_flow(fsp, req, flow_type);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल IPV6_USER_FLOW:
	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW:
	हाल SCTP_V6_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
		ret = otx2_prepare_ipv6_flow(fsp, req, flow_type);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (fsp->flow_type & FLOW_EXT) अणु
		अगर (fsp->m_ext.vlan_etype)
			वापस -EINVAL;
		अगर (fsp->m_ext.vlan_tci) अणु
			अगर (fsp->m_ext.vlan_tci != cpu_to_be16(VLAN_VID_MASK))
				वापस -EINVAL;
			अगर (be16_to_cpu(fsp->h_ext.vlan_tci) >= VLAN_N_VID)
				वापस -EINVAL;

			स_नकल(&pkt->vlan_tci, &fsp->h_ext.vlan_tci,
			       माप(pkt->vlan_tci));
			स_नकल(&pmask->vlan_tci, &fsp->m_ext.vlan_tci,
			       माप(pmask->vlan_tci));
			req->features |= BIT_ULL(NPC_OUTER_VID);
		पूर्ण

		/* Not Drop/Direct to queue but use action in शेष entry */
		अगर (fsp->m_ext.data[1] &&
		    fsp->h_ext.data[1] == cpu_to_be32(OTX2_DEFAULT_ACTION))
			req->op = NIX_RX_ACTION_DEFAULT;
	पूर्ण

	अगर (fsp->flow_type & FLOW_MAC_EXT &&
	    !is_zero_ether_addr(fsp->m_ext.h_dest)) अणु
		ether_addr_copy(pkt->dmac, fsp->h_ext.h_dest);
		ether_addr_copy(pmask->dmac, fsp->m_ext.h_dest);
		req->features |= BIT_ULL(NPC_DMAC);
	पूर्ण

	अगर (!req->features)
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल पूर्णांक otx2_add_flow_msg(काष्ठा otx2_nic *pfvf, काष्ठा otx2_flow *flow)
अणु
	u64 ring_cookie = flow->flow_spec.ring_cookie;
	काष्ठा npc_install_flow_req *req;
	पूर्णांक err, vf = 0;

	mutex_lock(&pfvf->mbox.lock);
	req = otx2_mbox_alloc_msg_npc_install_flow(&pfvf->mbox);
	अगर (!req) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	err = otx2_prepare_flow_request(&flow->flow_spec, req);
	अगर (err) अणु
		/* मुक्त the allocated msg above */
		otx2_mbox_reset(&pfvf->mbox.mbox, 0);
		mutex_unlock(&pfvf->mbox.lock);
		वापस err;
	पूर्ण

	req->entry = flow->entry;
	req->पूर्णांकf = NIX_INTF_RX;
	req->set_cntr = 1;
	req->channel = pfvf->hw.rx_chan_base;
	अगर (ring_cookie == RX_CLS_FLOW_DISC) अणु
		req->op = NIX_RX_ACTIONOP_DROP;
	पूर्ण अन्यथा अणु
		/* change to unicast only अगर action of शेष entry is not
		 * requested by user
		 */
		अगर (flow->flow_spec.flow_type & FLOW_RSS) अणु
			req->op = NIX_RX_ACTIONOP_RSS;
			req->index = flow->rss_ctx_id;
		पूर्ण अन्यथा अणु
			req->op = NIX_RX_ACTIONOP_UCAST;
			req->index = ethtool_get_flow_spec_ring(ring_cookie);
		पूर्ण
		vf = ethtool_get_flow_spec_ring_vf(ring_cookie);
		अगर (vf > pci_num_vf(pfvf->pdev)) अणु
			mutex_unlock(&pfvf->mbox.lock);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* ethtool ring_cookie has (VF + 1) क्रम VF */
	अगर (vf) अणु
		req->vf = vf;
		flow->is_vf = true;
		flow->vf = vf;
	पूर्ण

	/* Send message to AF */
	err = otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unlock(&pfvf->mbox.lock);
	वापस err;
पूर्ण

पूर्णांक otx2_add_flow(काष्ठा otx2_nic *pfvf, काष्ठा ethtool_rxnfc *nfc)
अणु
	काष्ठा otx2_flow_config *flow_cfg = pfvf->flow_cfg;
	काष्ठा ethtool_rx_flow_spec *fsp = &nfc->fs;
	काष्ठा otx2_flow *flow;
	bool new = false;
	u32 ring;
	पूर्णांक err;

	ring = ethtool_get_flow_spec_ring(fsp->ring_cookie);
	अगर (!(pfvf->flags & OTX2_FLAG_NTUPLE_SUPPORT))
		वापस -ENOMEM;

	अगर (ring >= pfvf->hw.rx_queues && fsp->ring_cookie != RX_CLS_FLOW_DISC)
		वापस -EINVAL;

	अगर (fsp->location >= flow_cfg->ntuple_max_flows)
		वापस -EINVAL;

	flow = otx2_find_flow(pfvf, fsp->location);
	अगर (!flow) अणु
		flow = kzalloc(माप(*flow), GFP_ATOMIC);
		अगर (!flow)
			वापस -ENOMEM;
		flow->location = fsp->location;
		flow->entry = flow_cfg->entry[flow_cfg->ntuple_offset +
						flow->location];
		new = true;
	पूर्ण
	/* काष्ठा copy */
	flow->flow_spec = *fsp;

	अगर (fsp->flow_type & FLOW_RSS)
		flow->rss_ctx_id = nfc->rss_context;

	err = otx2_add_flow_msg(pfvf, flow);
	अगर (err) अणु
		अगर (new)
			kमुक्त(flow);
		वापस err;
	पूर्ण

	/* add the new flow installed to list */
	अगर (new) अणु
		otx2_add_flow_to_list(pfvf, flow);
		flow_cfg->nr_flows++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक otx2_हटाओ_flow_msg(काष्ठा otx2_nic *pfvf, u16 entry, bool all)
अणु
	काष्ठा npc_delete_flow_req *req;
	पूर्णांक err;

	mutex_lock(&pfvf->mbox.lock);
	req = otx2_mbox_alloc_msg_npc_delete_flow(&pfvf->mbox);
	अगर (!req) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	req->entry = entry;
	अगर (all)
		req->all = 1;

	/* Send message to AF */
	err = otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unlock(&pfvf->mbox.lock);
	वापस err;
पूर्ण

पूर्णांक otx2_हटाओ_flow(काष्ठा otx2_nic *pfvf, u32 location)
अणु
	काष्ठा otx2_flow_config *flow_cfg = pfvf->flow_cfg;
	काष्ठा otx2_flow *flow;
	पूर्णांक err;

	अगर (location >= flow_cfg->ntuple_max_flows)
		वापस -EINVAL;

	flow = otx2_find_flow(pfvf, location);
	अगर (!flow)
		वापस -ENOENT;

	err = otx2_हटाओ_flow_msg(pfvf, flow->entry, false);
	अगर (err)
		वापस err;

	list_del(&flow->list);
	kमुक्त(flow);
	flow_cfg->nr_flows--;

	वापस 0;
पूर्ण

व्योम otx2_rss_ctx_flow_del(काष्ठा otx2_nic *pfvf, पूर्णांक ctx_id)
अणु
	काष्ठा otx2_flow *flow, *पंचांगp;
	पूर्णांक err;

	list_क्रम_each_entry_safe(flow, पंचांगp, &pfvf->flow_cfg->flow_list, list) अणु
		अगर (flow->rss_ctx_id != ctx_id)
			जारी;
		err = otx2_हटाओ_flow(pfvf, flow->location);
		अगर (err)
			netdev_warn(pfvf->netdev,
				    "Can't delete the rule %d associated with this rss group err:%d",
				    flow->location, err);
	पूर्ण
पूर्ण

पूर्णांक otx2_destroy_ntuple_flows(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा otx2_flow_config *flow_cfg = pfvf->flow_cfg;
	काष्ठा npc_delete_flow_req *req;
	काष्ठा otx2_flow *iter, *पंचांगp;
	पूर्णांक err;

	अगर (!(pfvf->flags & OTX2_FLAG_NTUPLE_SUPPORT))
		वापस 0;

	mutex_lock(&pfvf->mbox.lock);
	req = otx2_mbox_alloc_msg_npc_delete_flow(&pfvf->mbox);
	अगर (!req) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	req->start = flow_cfg->entry[flow_cfg->ntuple_offset];
	req->end   = flow_cfg->entry[flow_cfg->ntuple_offset +
				      flow_cfg->ntuple_max_flows - 1];
	err = otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unlock(&pfvf->mbox.lock);

	list_क्रम_each_entry_safe(iter, पंचांगp, &flow_cfg->flow_list, list) अणु
		list_del(&iter->list);
		kमुक्त(iter);
		flow_cfg->nr_flows--;
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक otx2_destroy_mcam_flows(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा otx2_flow_config *flow_cfg = pfvf->flow_cfg;
	काष्ठा npc_mcam_मुक्त_entry_req *req;
	काष्ठा otx2_flow *iter, *पंचांगp;
	पूर्णांक err;

	अगर (!(pfvf->flags & OTX2_FLAG_MCAM_ENTRIES_ALLOC))
		वापस 0;

	/* हटाओ all flows */
	err = otx2_हटाओ_flow_msg(pfvf, 0, true);
	अगर (err)
		वापस err;

	list_क्रम_each_entry_safe(iter, पंचांगp, &flow_cfg->flow_list, list) अणु
		list_del(&iter->list);
		kमुक्त(iter);
		flow_cfg->nr_flows--;
	पूर्ण

	mutex_lock(&pfvf->mbox.lock);
	req = otx2_mbox_alloc_msg_npc_mcam_मुक्त_entry(&pfvf->mbox);
	अगर (!req) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	req->all = 1;
	/* Send message to AF to मुक्त MCAM entries */
	err = otx2_sync_mbox_msg(&pfvf->mbox);
	अगर (err) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस err;
	पूर्ण

	pfvf->flags &= ~OTX2_FLAG_MCAM_ENTRIES_ALLOC;
	mutex_unlock(&pfvf->mbox.lock);

	वापस 0;
पूर्ण

पूर्णांक otx2_install_rxvlan_offload_flow(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा otx2_flow_config *flow_cfg = pfvf->flow_cfg;
	काष्ठा npc_install_flow_req *req;
	पूर्णांक err;

	mutex_lock(&pfvf->mbox.lock);
	req = otx2_mbox_alloc_msg_npc_install_flow(&pfvf->mbox);
	अगर (!req) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	req->entry = flow_cfg->entry[flow_cfg->rx_vlan_offset];
	req->पूर्णांकf = NIX_INTF_RX;
	ether_addr_copy(req->packet.dmac, pfvf->netdev->dev_addr);
	eth_broadcast_addr((u8 *)&req->mask.dmac);
	req->channel = pfvf->hw.rx_chan_base;
	req->op = NIX_RX_ACTION_DEFAULT;
	req->features = BIT_ULL(NPC_OUTER_VID) | BIT_ULL(NPC_DMAC);
	req->vtag0_valid = true;
	req->vtag0_type = NIX_AF_LFX_RX_VTAG_TYPE0;

	/* Send message to AF */
	err = otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unlock(&pfvf->mbox.lock);
	वापस err;
पूर्ण

अटल पूर्णांक otx2_delete_rxvlan_offload_flow(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा otx2_flow_config *flow_cfg = pfvf->flow_cfg;
	काष्ठा npc_delete_flow_req *req;
	पूर्णांक err;

	mutex_lock(&pfvf->mbox.lock);
	req = otx2_mbox_alloc_msg_npc_delete_flow(&pfvf->mbox);
	अगर (!req) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	req->entry = flow_cfg->entry[flow_cfg->rx_vlan_offset];
	/* Send message to AF */
	err = otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unlock(&pfvf->mbox.lock);
	वापस err;
पूर्ण

पूर्णांक otx2_enable_rxvlan(काष्ठा otx2_nic *pf, bool enable)
अणु
	काष्ठा nix_vtag_config *req;
	काष्ठा mbox_msghdr *rsp_hdr;
	पूर्णांक err;

	/* Dont have enough mcam entries */
	अगर (!(pf->flags & OTX2_FLAG_RX_VLAN_SUPPORT))
		वापस -ENOMEM;

	अगर (enable) अणु
		err = otx2_install_rxvlan_offload_flow(pf);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		err = otx2_delete_rxvlan_offload_flow(pf);
		अगर (err)
			वापस err;
	पूर्ण

	mutex_lock(&pf->mbox.lock);
	req = otx2_mbox_alloc_msg_nix_vtag_cfg(&pf->mbox);
	अगर (!req) अणु
		mutex_unlock(&pf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	/* config strip, capture and size */
	req->vtag_size = VTAGSIZE_T4;
	req->cfg_type = 1; /* rx vlan cfg */
	req->rx.vtag_type = NIX_AF_LFX_RX_VTAG_TYPE0;
	req->rx.strip_vtag = enable;
	req->rx.capture_vtag = enable;

	err = otx2_sync_mbox_msg(&pf->mbox);
	अगर (err) अणु
		mutex_unlock(&pf->mbox.lock);
		वापस err;
	पूर्ण

	rsp_hdr = otx2_mbox_get_rsp(&pf->mbox.mbox, 0, &req->hdr);
	अगर (IS_ERR(rsp_hdr)) अणु
		mutex_unlock(&pf->mbox.lock);
		वापस PTR_ERR(rsp_hdr);
	पूर्ण

	mutex_unlock(&pf->mbox.lock);
	वापस rsp_hdr->rc;
पूर्ण
