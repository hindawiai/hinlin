<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2014-2019 aQuantia Corporation. */

/* File aq_filters.c: RX filters related functions. */

#समावेश "aq_filters.h"

अटल bool __must_check
aq_rule_is_approve(काष्ठा ethtool_rx_flow_spec *fsp)
अणु
	अगर (fsp->flow_type & FLOW_MAC_EXT)
		वापस false;

	चयन (fsp->flow_type & ~FLOW_EXT) अणु
	हाल ETHER_FLOW:
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
	हाल SCTP_V4_FLOW:
	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW:
	हाल SCTP_V6_FLOW:
	हाल IPV4_FLOW:
	हाल IPV6_FLOW:
		वापस true;
	हाल IP_USER_FLOW:
		चयन (fsp->h_u.usr_ip4_spec.proto) अणु
		हाल IPPROTO_TCP:
		हाल IPPROTO_UDP:
		हाल IPPROTO_SCTP:
		हाल IPPROTO_IP:
			वापस true;
		शेष:
			वापस false;
			पूर्ण
	हाल IPV6_USER_FLOW:
		चयन (fsp->h_u.usr_ip6_spec.l4_proto) अणु
		हाल IPPROTO_TCP:
		हाल IPPROTO_UDP:
		हाल IPPROTO_SCTP:
		हाल IPPROTO_IP:
			वापस true;
		शेष:
			वापस false;
			पूर्ण
	शेष:
		वापस false;
	पूर्ण

	वापस false;
पूर्ण

अटल bool __must_check
aq_match_filter(काष्ठा ethtool_rx_flow_spec *fsp1,
		काष्ठा ethtool_rx_flow_spec *fsp2)
अणु
	अगर (fsp1->flow_type != fsp2->flow_type ||
	    स_भेद(&fsp1->h_u, &fsp2->h_u, माप(fsp2->h_u)) ||
	    स_भेद(&fsp1->h_ext, &fsp2->h_ext, माप(fsp2->h_ext)) ||
	    स_भेद(&fsp1->m_u, &fsp2->m_u, माप(fsp2->m_u)) ||
	    स_भेद(&fsp1->m_ext, &fsp2->m_ext, माप(fsp2->m_ext)))
		वापस false;

	वापस true;
पूर्ण

अटल bool __must_check
aq_rule_alपढ़ोy_exists(काष्ठा aq_nic_s *aq_nic,
		       काष्ठा ethtool_rx_flow_spec *fsp)
अणु
	काष्ठा aq_rx_filter *rule;
	काष्ठा hlist_node *aq_node2;
	काष्ठा aq_hw_rx_fltrs_s *rx_fltrs = aq_get_hw_rx_fltrs(aq_nic);

	hlist_क्रम_each_entry_safe(rule, aq_node2,
				  &rx_fltrs->filter_list, aq_node) अणु
		अगर (rule->aq_fsp.location == fsp->location)
			जारी;
		अगर (aq_match_filter(&rule->aq_fsp, fsp)) अणु
			netdev_err(aq_nic->ndev,
				   "ethtool: This filter is already set\n");
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक aq_check_approve_fl3l4(काष्ठा aq_nic_s *aq_nic,
				  काष्ठा aq_hw_rx_fltrs_s *rx_fltrs,
				  काष्ठा ethtool_rx_flow_spec *fsp)
अणु
	u32 last_location = AQ_RX_LAST_LOC_FL3L4 -
			    aq_nic->aq_hw_rx_fltrs.fl3l4.reserved_count;

	अगर (fsp->location < AQ_RX_FIRST_LOC_FL3L4 ||
	    fsp->location > last_location) अणु
		netdev_err(aq_nic->ndev,
			   "ethtool: location must be in range [%d, %d]",
			   AQ_RX_FIRST_LOC_FL3L4, last_location);
		वापस -EINVAL;
	पूर्ण
	अगर (rx_fltrs->fl3l4.is_ipv6 && rx_fltrs->fl3l4.active_ipv4) अणु
		rx_fltrs->fl3l4.is_ipv6 = false;
		netdev_err(aq_nic->ndev,
			   "ethtool: mixing ipv4 and ipv6 is not allowed");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (!rx_fltrs->fl3l4.is_ipv6 && rx_fltrs->fl3l4.active_ipv6) अणु
		rx_fltrs->fl3l4.is_ipv6 = true;
		netdev_err(aq_nic->ndev,
			   "ethtool: mixing ipv4 and ipv6 is not allowed");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (rx_fltrs->fl3l4.is_ipv6		      &&
		   fsp->location != AQ_RX_FIRST_LOC_FL3L4 + 4 &&
		   fsp->location != AQ_RX_FIRST_LOC_FL3L4) अणु
		netdev_err(aq_nic->ndev,
			   "ethtool: The specified location for ipv6 must be %d or %d",
			   AQ_RX_FIRST_LOC_FL3L4, AQ_RX_FIRST_LOC_FL3L4 + 4);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __must_check
aq_check_approve_fl2(काष्ठा aq_nic_s *aq_nic,
		     काष्ठा aq_hw_rx_fltrs_s *rx_fltrs,
		     काष्ठा ethtool_rx_flow_spec *fsp)
अणु
	u32 last_location = AQ_RX_LAST_LOC_FETHERT -
			    aq_nic->aq_hw_rx_fltrs.fet_reserved_count;

	अगर (fsp->location < AQ_RX_FIRST_LOC_FETHERT ||
	    fsp->location > last_location) अणु
		netdev_err(aq_nic->ndev,
			   "ethtool: location must be in range [%d, %d]",
			   AQ_RX_FIRST_LOC_FETHERT,
			   last_location);
		वापस -EINVAL;
	पूर्ण

	अगर (be16_to_cpu(fsp->m_ext.vlan_tci) == VLAN_PRIO_MASK &&
	    fsp->m_u.ether_spec.h_proto == 0U) अणु
		netdev_err(aq_nic->ndev,
			   "ethtool: proto (ether_type) parameter must be specified");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __must_check
aq_check_approve_fvlan(काष्ठा aq_nic_s *aq_nic,
		       काष्ठा aq_hw_rx_fltrs_s *rx_fltrs,
		       काष्ठा ethtool_rx_flow_spec *fsp)
अणु
	काष्ठा aq_nic_cfg_s *cfg = &aq_nic->aq_nic_cfg;

	अगर (fsp->location < AQ_RX_FIRST_LOC_FVLANID ||
	    fsp->location > AQ_RX_LAST_LOC_FVLANID) अणु
		netdev_err(aq_nic->ndev,
			   "ethtool: location must be in range [%d, %d]",
			   AQ_RX_FIRST_LOC_FVLANID,
			   AQ_RX_LAST_LOC_FVLANID);
		वापस -EINVAL;
	पूर्ण

	अगर ((aq_nic->ndev->features & NETIF_F_HW_VLAN_CTAG_FILTER) &&
	    (!test_bit(be16_to_cpu(fsp->h_ext.vlan_tci) & VLAN_VID_MASK,
		       aq_nic->active_vlans))) अणु
		netdev_err(aq_nic->ndev,
			   "ethtool: unknown vlan-id specified");
		वापस -EINVAL;
	पूर्ण

	अगर (fsp->ring_cookie > cfg->num_rss_queues * cfg->tcs) अणु
		netdev_err(aq_nic->ndev,
			   "ethtool: queue number must be in range [0, %d]",
			   cfg->num_rss_queues * cfg->tcs - 1);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __must_check
aq_check_filter(काष्ठा aq_nic_s *aq_nic,
		काष्ठा ethtool_rx_flow_spec *fsp)
अणु
	पूर्णांक err = 0;
	काष्ठा aq_hw_rx_fltrs_s *rx_fltrs = aq_get_hw_rx_fltrs(aq_nic);

	अगर (fsp->flow_type & FLOW_EXT) अणु
		अगर (be16_to_cpu(fsp->m_ext.vlan_tci) == VLAN_VID_MASK) अणु
			err = aq_check_approve_fvlan(aq_nic, rx_fltrs, fsp);
		पूर्ण अन्यथा अगर (be16_to_cpu(fsp->m_ext.vlan_tci) == VLAN_PRIO_MASK) अणु
			err = aq_check_approve_fl2(aq_nic, rx_fltrs, fsp);
		पूर्ण अन्यथा अणु
			netdev_err(aq_nic->ndev,
				   "ethtool: invalid vlan mask 0x%x specified",
				   be16_to_cpu(fsp->m_ext.vlan_tci));
			err = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (fsp->flow_type & ~FLOW_EXT) अणु
		हाल ETHER_FLOW:
			err = aq_check_approve_fl2(aq_nic, rx_fltrs, fsp);
			अवरोध;
		हाल TCP_V4_FLOW:
		हाल UDP_V4_FLOW:
		हाल SCTP_V4_FLOW:
		हाल IPV4_FLOW:
		हाल IP_USER_FLOW:
			rx_fltrs->fl3l4.is_ipv6 = false;
			err = aq_check_approve_fl3l4(aq_nic, rx_fltrs, fsp);
			अवरोध;
		हाल TCP_V6_FLOW:
		हाल UDP_V6_FLOW:
		हाल SCTP_V6_FLOW:
		हाल IPV6_FLOW:
		हाल IPV6_USER_FLOW:
			rx_fltrs->fl3l4.is_ipv6 = true;
			err = aq_check_approve_fl3l4(aq_nic, rx_fltrs, fsp);
			अवरोध;
		शेष:
			netdev_err(aq_nic->ndev,
				   "ethtool: unknown flow-type specified");
			err = -EINVAL;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल bool __must_check
aq_rule_is_not_support(काष्ठा aq_nic_s *aq_nic,
		       काष्ठा ethtool_rx_flow_spec *fsp)
अणु
	bool rule_is_not_support = false;

	अगर (!(aq_nic->ndev->features & NETIF_F_NTUPLE)) अणु
		netdev_err(aq_nic->ndev,
			   "ethtool: Please, to enable the RX flow control:\n"
			   "ethtool -K %s ntuple on\n", aq_nic->ndev->name);
		rule_is_not_support = true;
	पूर्ण अन्यथा अगर (!aq_rule_is_approve(fsp)) अणु
		netdev_err(aq_nic->ndev,
			   "ethtool: The specified flow type is not supported\n");
		rule_is_not_support = true;
	पूर्ण अन्यथा अगर ((fsp->flow_type & ~FLOW_EXT) != ETHER_FLOW &&
		   (fsp->h_u.tcp_ip4_spec.tos ||
		    fsp->h_u.tcp_ip6_spec.tclass)) अणु
		netdev_err(aq_nic->ndev,
			   "ethtool: The specified tos tclass are not supported\n");
		rule_is_not_support = true;
	पूर्ण अन्यथा अगर (fsp->flow_type & FLOW_MAC_EXT) अणु
		netdev_err(aq_nic->ndev,
			   "ethtool: MAC_EXT is not supported");
		rule_is_not_support = true;
	पूर्ण

	वापस rule_is_not_support;
पूर्ण

अटल bool __must_check
aq_rule_is_not_correct(काष्ठा aq_nic_s *aq_nic,
		       काष्ठा ethtool_rx_flow_spec *fsp)
अणु
	काष्ठा aq_nic_cfg_s *cfg = &aq_nic->aq_nic_cfg;
	bool rule_is_not_correct = false;

	अगर (!aq_nic) अणु
		rule_is_not_correct = true;
	पूर्ण अन्यथा अगर (fsp->location > AQ_RX_MAX_RXNFC_LOC) अणु
		netdev_err(aq_nic->ndev,
			   "ethtool: The specified number %u rule is invalid\n",
			   fsp->location);
		rule_is_not_correct = true;
	पूर्ण अन्यथा अगर (aq_check_filter(aq_nic, fsp)) अणु
		rule_is_not_correct = true;
	पूर्ण अन्यथा अगर (fsp->ring_cookie != RX_CLS_FLOW_DISC) अणु
		अगर (fsp->ring_cookie >= cfg->num_rss_queues * cfg->tcs) अणु
			netdev_err(aq_nic->ndev,
				   "ethtool: The specified action is invalid.\n"
				   "Maximum allowable value action is %u.\n",
				   cfg->num_rss_queues * cfg->tcs - 1);
			rule_is_not_correct = true;
		पूर्ण
	पूर्ण

	वापस rule_is_not_correct;
पूर्ण

अटल पूर्णांक __must_check
aq_check_rule(काष्ठा aq_nic_s *aq_nic,
	      काष्ठा ethtool_rx_flow_spec *fsp)
अणु
	पूर्णांक err = 0;

	अगर (aq_rule_is_not_correct(aq_nic, fsp))
		err = -EINVAL;
	अन्यथा अगर (aq_rule_is_not_support(aq_nic, fsp))
		err = -EOPNOTSUPP;
	अन्यथा अगर (aq_rule_alपढ़ोy_exists(aq_nic, fsp))
		err = -EEXIST;

	वापस err;
पूर्ण

अटल व्योम aq_set_data_fl2(काष्ठा aq_nic_s *aq_nic,
			    काष्ठा aq_rx_filter *aq_rx_fltr,
			    काष्ठा aq_rx_filter_l2 *data, bool add)
अणु
	स्थिर काष्ठा ethtool_rx_flow_spec *fsp = &aq_rx_fltr->aq_fsp;

	स_रखो(data, 0, माप(*data));

	data->location = fsp->location - AQ_RX_FIRST_LOC_FETHERT;

	अगर (fsp->ring_cookie != RX_CLS_FLOW_DISC)
		data->queue = fsp->ring_cookie;
	अन्यथा
		data->queue = -1;

	data->ethertype = be16_to_cpu(fsp->h_u.ether_spec.h_proto);
	data->user_priority_en = be16_to_cpu(fsp->m_ext.vlan_tci)
				 == VLAN_PRIO_MASK;
	data->user_priority = (be16_to_cpu(fsp->h_ext.vlan_tci)
			       & VLAN_PRIO_MASK) >> VLAN_PRIO_SHIFT;
पूर्ण

अटल पूर्णांक aq_add_del_fether(काष्ठा aq_nic_s *aq_nic,
			     काष्ठा aq_rx_filter *aq_rx_fltr, bool add)
अणु
	काष्ठा aq_rx_filter_l2 data;
	काष्ठा aq_hw_s *aq_hw = aq_nic->aq_hw;
	स्थिर काष्ठा aq_hw_ops *aq_hw_ops = aq_nic->aq_hw_ops;

	aq_set_data_fl2(aq_nic, aq_rx_fltr, &data, add);

	अगर (unlikely(!aq_hw_ops->hw_filter_l2_set))
		वापस -EOPNOTSUPP;
	अगर (unlikely(!aq_hw_ops->hw_filter_l2_clear))
		वापस -EOPNOTSUPP;

	अगर (add)
		वापस aq_hw_ops->hw_filter_l2_set(aq_hw, &data);
	अन्यथा
		वापस aq_hw_ops->hw_filter_l2_clear(aq_hw, &data);
पूर्ण

अटल bool aq_fvlan_is_busy(काष्ठा aq_rx_filter_vlan *aq_vlans, पूर्णांक vlan)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < AQ_VLAN_MAX_FILTERS; ++i) अणु
		अगर (aq_vlans[i].enable &&
		    aq_vlans[i].queue != AQ_RX_QUEUE_NOT_ASSIGNED &&
		    aq_vlans[i].vlan_id == vlan) अणु
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

/* Function rebuilds array of vlan filters so that filters with asचिन्हित
 * queue have a precedence over just vlans on the पूर्णांकerface.
 */
अटल व्योम aq_fvlan_rebuild(काष्ठा aq_nic_s *aq_nic,
			     अचिन्हित दीर्घ *active_vlans,
			     काष्ठा aq_rx_filter_vlan *aq_vlans)
अणु
	bool vlan_busy = false;
	पूर्णांक vlan = -1;
	पूर्णांक i;

	क्रम (i = 0; i < AQ_VLAN_MAX_FILTERS; ++i) अणु
		अगर (aq_vlans[i].enable &&
		    aq_vlans[i].queue != AQ_RX_QUEUE_NOT_ASSIGNED)
			जारी;
		करो अणु
			vlan = find_next_bit(active_vlans,
					     VLAN_N_VID,
					     vlan + 1);
			अगर (vlan == VLAN_N_VID) अणु
				aq_vlans[i].enable = 0U;
				aq_vlans[i].queue = AQ_RX_QUEUE_NOT_ASSIGNED;
				aq_vlans[i].vlan_id = 0;
				जारी;
			पूर्ण

			vlan_busy = aq_fvlan_is_busy(aq_vlans, vlan);
			अगर (!vlan_busy) अणु
				aq_vlans[i].enable = 1U;
				aq_vlans[i].queue = AQ_RX_QUEUE_NOT_ASSIGNED;
				aq_vlans[i].vlan_id = vlan;
			पूर्ण
		पूर्ण जबतक (vlan_busy && vlan != VLAN_N_VID);
	पूर्ण
पूर्ण

अटल पूर्णांक aq_set_data_fvlan(काष्ठा aq_nic_s *aq_nic,
			     काष्ठा aq_rx_filter *aq_rx_fltr,
			     काष्ठा aq_rx_filter_vlan *aq_vlans, bool add)
अणु
	स्थिर काष्ठा ethtool_rx_flow_spec *fsp = &aq_rx_fltr->aq_fsp;
	पूर्णांक location = fsp->location - AQ_RX_FIRST_LOC_FVLANID;
	पूर्णांक i;

	स_रखो(&aq_vlans[location], 0, माप(aq_vlans[location]));

	अगर (!add)
		वापस 0;

	/* हटाओ vlan अगर it was in table without queue assignment */
	क्रम (i = 0; i < AQ_VLAN_MAX_FILTERS; ++i) अणु
		अगर (aq_vlans[i].vlan_id ==
		   (be16_to_cpu(fsp->h_ext.vlan_tci) & VLAN_VID_MASK)) अणु
			aq_vlans[i].enable = false;
		पूर्ण
	पूर्ण

	aq_vlans[location].location = location;
	aq_vlans[location].vlan_id = be16_to_cpu(fsp->h_ext.vlan_tci)
				     & VLAN_VID_MASK;
	aq_vlans[location].queue = fsp->ring_cookie & 0x1FU;
	aq_vlans[location].enable = 1U;

	वापस 0;
पूर्ण

पूर्णांक aq_del_fvlan_by_vlan(काष्ठा aq_nic_s *aq_nic, u16 vlan_id)
अणु
	काष्ठा aq_hw_rx_fltrs_s *rx_fltrs = aq_get_hw_rx_fltrs(aq_nic);
	काष्ठा aq_rx_filter *rule = शून्य;
	काष्ठा hlist_node *aq_node2;

	hlist_क्रम_each_entry_safe(rule, aq_node2,
				  &rx_fltrs->filter_list, aq_node) अणु
		अगर (be16_to_cpu(rule->aq_fsp.h_ext.vlan_tci) == vlan_id)
			अवरोध;
	पूर्ण
	अगर (rule && rule->type == aq_rx_filter_vlan &&
	    be16_to_cpu(rule->aq_fsp.h_ext.vlan_tci) == vlan_id) अणु
		काष्ठा ethtool_rxnfc cmd;

		cmd.fs.location = rule->aq_fsp.location;
		वापस aq_del_rxnfc_rule(aq_nic, &cmd);
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक aq_add_del_fvlan(काष्ठा aq_nic_s *aq_nic,
			    काष्ठा aq_rx_filter *aq_rx_fltr, bool add)
अणु
	स्थिर काष्ठा aq_hw_ops *aq_hw_ops = aq_nic->aq_hw_ops;

	अगर (unlikely(!aq_hw_ops->hw_filter_vlan_set))
		वापस -EOPNOTSUPP;

	aq_set_data_fvlan(aq_nic,
			  aq_rx_fltr,
			  aq_nic->aq_hw_rx_fltrs.fl2.aq_vlans,
			  add);

	वापस aq_filters_vlans_update(aq_nic);
पूर्ण

अटल पूर्णांक aq_set_data_fl3l4(काष्ठा aq_nic_s *aq_nic,
			     काष्ठा aq_rx_filter *aq_rx_fltr,
			     काष्ठा aq_rx_filter_l3l4 *data, bool add)
अणु
	काष्ठा aq_hw_rx_fltrs_s *rx_fltrs = aq_get_hw_rx_fltrs(aq_nic);
	स्थिर काष्ठा ethtool_rx_flow_spec *fsp = &aq_rx_fltr->aq_fsp;

	स_रखो(data, 0, माप(*data));

	data->is_ipv6 = rx_fltrs->fl3l4.is_ipv6;
	data->location = HW_ATL_GET_REG_LOCATION_FL3L4(fsp->location);

	अगर (!add) अणु
		अगर (!data->is_ipv6)
			rx_fltrs->fl3l4.active_ipv4 &= ~BIT(data->location);
		अन्यथा
			rx_fltrs->fl3l4.active_ipv6 &=
				~BIT((data->location) / 4);

		वापस 0;
	पूर्ण

	data->cmd |= HW_ATL_RX_ENABLE_FLTR_L3L4;

	चयन (fsp->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल TCP_V6_FLOW:
		data->cmd |= HW_ATL_RX_ENABLE_CMP_PROT_L4;
		अवरोध;
	हाल UDP_V4_FLOW:
	हाल UDP_V6_FLOW:
		data->cmd |= HW_ATL_RX_UDP;
		data->cmd |= HW_ATL_RX_ENABLE_CMP_PROT_L4;
		अवरोध;
	हाल SCTP_V4_FLOW:
	हाल SCTP_V6_FLOW:
		data->cmd |= HW_ATL_RX_SCTP;
		data->cmd |= HW_ATL_RX_ENABLE_CMP_PROT_L4;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!data->is_ipv6) अणु
		data->ip_src[0] =
			ntohl(fsp->h_u.tcp_ip4_spec.ip4src);
		data->ip_dst[0] =
			ntohl(fsp->h_u.tcp_ip4_spec.ip4dst);
		rx_fltrs->fl3l4.active_ipv4 |= BIT(data->location);
	पूर्ण अन्यथा अणु
		पूर्णांक i;

		rx_fltrs->fl3l4.active_ipv6 |= BIT((data->location) / 4);
		क्रम (i = 0; i < HW_ATL_RX_CNT_REG_ADDR_IPV6; ++i) अणु
			data->ip_dst[i] =
				ntohl(fsp->h_u.tcp_ip6_spec.ip6dst[i]);
			data->ip_src[i] =
				ntohl(fsp->h_u.tcp_ip6_spec.ip6src[i]);
		पूर्ण
		data->cmd |= HW_ATL_RX_ENABLE_L3_IPV6;
	पूर्ण
	अगर (fsp->flow_type != IP_USER_FLOW &&
	    fsp->flow_type != IPV6_USER_FLOW) अणु
		अगर (!data->is_ipv6) अणु
			data->p_dst =
				ntohs(fsp->h_u.tcp_ip4_spec.pdst);
			data->p_src =
				ntohs(fsp->h_u.tcp_ip4_spec.psrc);
		पूर्ण अन्यथा अणु
			data->p_dst =
				ntohs(fsp->h_u.tcp_ip6_spec.pdst);
			data->p_src =
				ntohs(fsp->h_u.tcp_ip6_spec.psrc);
		पूर्ण
	पूर्ण
	अगर (data->ip_src[0] && !data->is_ipv6)
		data->cmd |= HW_ATL_RX_ENABLE_CMP_SRC_ADDR_L3;
	अगर (data->ip_dst[0] && !data->is_ipv6)
		data->cmd |= HW_ATL_RX_ENABLE_CMP_DEST_ADDR_L3;
	अगर (data->p_dst)
		data->cmd |= HW_ATL_RX_ENABLE_CMP_DEST_PORT_L4;
	अगर (data->p_src)
		data->cmd |= HW_ATL_RX_ENABLE_CMP_SRC_PORT_L4;
	अगर (fsp->ring_cookie != RX_CLS_FLOW_DISC) अणु
		data->cmd |= HW_ATL_RX_HOST << HW_ATL_RX_ACTION_FL3F4_SHIFT;
		data->cmd |= fsp->ring_cookie << HW_ATL_RX_QUEUE_FL3L4_SHIFT;
		data->cmd |= HW_ATL_RX_ENABLE_QUEUE_L3L4;
	पूर्ण अन्यथा अणु
		data->cmd |= HW_ATL_RX_DISCARD << HW_ATL_RX_ACTION_FL3F4_SHIFT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aq_set_fl3l4(काष्ठा aq_hw_s *aq_hw,
			स्थिर काष्ठा aq_hw_ops *aq_hw_ops,
			काष्ठा aq_rx_filter_l3l4 *data)
अणु
	अगर (unlikely(!aq_hw_ops->hw_filter_l3l4_set))
		वापस -EOPNOTSUPP;

	वापस aq_hw_ops->hw_filter_l3l4_set(aq_hw, data);
पूर्ण

अटल पूर्णांक aq_add_del_fl3l4(काष्ठा aq_nic_s *aq_nic,
			    काष्ठा aq_rx_filter *aq_rx_fltr, bool add)
अणु
	स्थिर काष्ठा aq_hw_ops *aq_hw_ops = aq_nic->aq_hw_ops;
	काष्ठा aq_hw_s *aq_hw = aq_nic->aq_hw;
	काष्ठा aq_rx_filter_l3l4 data;

	अगर (unlikely(aq_rx_fltr->aq_fsp.location < AQ_RX_FIRST_LOC_FL3L4 ||
		     aq_rx_fltr->aq_fsp.location > AQ_RX_LAST_LOC_FL3L4  ||
		     aq_set_data_fl3l4(aq_nic, aq_rx_fltr, &data, add)))
		वापस -EINVAL;

	वापस aq_set_fl3l4(aq_hw, aq_hw_ops, &data);
पूर्ण

अटल पूर्णांक aq_add_del_rule(काष्ठा aq_nic_s *aq_nic,
			   काष्ठा aq_rx_filter *aq_rx_fltr, bool add)
अणु
	पूर्णांक err = -EINVAL;

	अगर (aq_rx_fltr->aq_fsp.flow_type & FLOW_EXT) अणु
		अगर (be16_to_cpu(aq_rx_fltr->aq_fsp.m_ext.vlan_tci)
		    == VLAN_VID_MASK) अणु
			aq_rx_fltr->type = aq_rx_filter_vlan;
			err = aq_add_del_fvlan(aq_nic, aq_rx_fltr, add);
		पूर्ण अन्यथा अगर (be16_to_cpu(aq_rx_fltr->aq_fsp.m_ext.vlan_tci)
			== VLAN_PRIO_MASK) अणु
			aq_rx_fltr->type = aq_rx_filter_ethertype;
			err = aq_add_del_fether(aq_nic, aq_rx_fltr, add);
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (aq_rx_fltr->aq_fsp.flow_type & ~FLOW_EXT) अणु
		हाल ETHER_FLOW:
			aq_rx_fltr->type = aq_rx_filter_ethertype;
			err = aq_add_del_fether(aq_nic, aq_rx_fltr, add);
			अवरोध;
		हाल TCP_V4_FLOW:
		हाल UDP_V4_FLOW:
		हाल SCTP_V4_FLOW:
		हाल IP_USER_FLOW:
		हाल TCP_V6_FLOW:
		हाल UDP_V6_FLOW:
		हाल SCTP_V6_FLOW:
		हाल IPV6_USER_FLOW:
			aq_rx_fltr->type = aq_rx_filter_l3l4;
			err = aq_add_del_fl3l4(aq_nic, aq_rx_fltr, add);
			अवरोध;
		शेष:
			err = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक aq_update_table_filters(काष्ठा aq_nic_s *aq_nic,
				   काष्ठा aq_rx_filter *aq_rx_fltr, u16 index,
				   काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा aq_hw_rx_fltrs_s *rx_fltrs = aq_get_hw_rx_fltrs(aq_nic);
	काष्ठा aq_rx_filter *rule = शून्य, *parent = शून्य;
	काष्ठा hlist_node *aq_node2;
	पूर्णांक err = -EINVAL;

	hlist_क्रम_each_entry_safe(rule, aq_node2,
				  &rx_fltrs->filter_list, aq_node) अणु
		अगर (rule->aq_fsp.location >= index)
			अवरोध;
		parent = rule;
	पूर्ण

	अगर (rule && rule->aq_fsp.location == index) अणु
		err = aq_add_del_rule(aq_nic, rule, false);
		hlist_del(&rule->aq_node);
		kमुक्त(rule);
		--rx_fltrs->active_filters;
	पूर्ण

	अगर (unlikely(!aq_rx_fltr))
		वापस err;

	INIT_HLIST_NODE(&aq_rx_fltr->aq_node);

	अगर (parent)
		hlist_add_behind(&aq_rx_fltr->aq_node, &parent->aq_node);
	अन्यथा
		hlist_add_head(&aq_rx_fltr->aq_node, &rx_fltrs->filter_list);

	++rx_fltrs->active_filters;

	वापस 0;
पूर्ण

u16 aq_get_rxnfc_count_all_rules(काष्ठा aq_nic_s *aq_nic)
अणु
	काष्ठा aq_hw_rx_fltrs_s *rx_fltrs = aq_get_hw_rx_fltrs(aq_nic);

	वापस rx_fltrs->active_filters;
पूर्ण

काष्ठा aq_hw_rx_fltrs_s *aq_get_hw_rx_fltrs(काष्ठा aq_nic_s *aq_nic)
अणु
	वापस &aq_nic->aq_hw_rx_fltrs;
पूर्ण

पूर्णांक aq_add_rxnfc_rule(काष्ठा aq_nic_s *aq_nic, स्थिर काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा aq_hw_rx_fltrs_s *rx_fltrs = aq_get_hw_rx_fltrs(aq_nic);
	काष्ठा ethtool_rx_flow_spec *fsp =
		(काष्ठा ethtool_rx_flow_spec *)&cmd->fs;
	काष्ठा aq_rx_filter *aq_rx_fltr;
	पूर्णांक err = 0;

	err = aq_check_rule(aq_nic, fsp);
	अगर (err)
		जाओ err_निकास;

	aq_rx_fltr = kzalloc(माप(*aq_rx_fltr), GFP_KERNEL);
	अगर (unlikely(!aq_rx_fltr)) अणु
		err = -ENOMEM;
		जाओ err_निकास;
	पूर्ण

	स_नकल(&aq_rx_fltr->aq_fsp, fsp, माप(*fsp));

	err = aq_update_table_filters(aq_nic, aq_rx_fltr, fsp->location, शून्य);
	अगर (unlikely(err))
		जाओ err_मुक्त;

	err = aq_add_del_rule(aq_nic, aq_rx_fltr, true);
	अगर (unlikely(err)) अणु
		hlist_del(&aq_rx_fltr->aq_node);
		--rx_fltrs->active_filters;
		जाओ err_मुक्त;
	पूर्ण

	वापस 0;

err_मुक्त:
	kमुक्त(aq_rx_fltr);
err_निकास:
	वापस err;
पूर्ण

पूर्णांक aq_del_rxnfc_rule(काष्ठा aq_nic_s *aq_nic, स्थिर काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा aq_hw_rx_fltrs_s *rx_fltrs = aq_get_hw_rx_fltrs(aq_nic);
	काष्ठा aq_rx_filter *rule = शून्य;
	काष्ठा hlist_node *aq_node2;
	पूर्णांक err = -EINVAL;

	hlist_क्रम_each_entry_safe(rule, aq_node2,
				  &rx_fltrs->filter_list, aq_node) अणु
		अगर (rule->aq_fsp.location == cmd->fs.location)
			अवरोध;
	पूर्ण

	अगर (rule && rule->aq_fsp.location == cmd->fs.location) अणु
		err = aq_add_del_rule(aq_nic, rule, false);
		hlist_del(&rule->aq_node);
		kमुक्त(rule);
		--rx_fltrs->active_filters;
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक aq_get_rxnfc_rule(काष्ठा aq_nic_s *aq_nic, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा aq_hw_rx_fltrs_s *rx_fltrs = aq_get_hw_rx_fltrs(aq_nic);
	काष्ठा ethtool_rx_flow_spec *fsp =
			(काष्ठा ethtool_rx_flow_spec *)&cmd->fs;
	काष्ठा aq_rx_filter *rule = शून्य;
	काष्ठा hlist_node *aq_node2;

	hlist_क्रम_each_entry_safe(rule, aq_node2,
				  &rx_fltrs->filter_list, aq_node)
		अगर (fsp->location <= rule->aq_fsp.location)
			अवरोध;

	अगर (unlikely(!rule || fsp->location != rule->aq_fsp.location))
		वापस -EINVAL;

	स_नकल(fsp, &rule->aq_fsp, माप(*fsp));

	वापस 0;
पूर्ण

पूर्णांक aq_get_rxnfc_all_rules(काष्ठा aq_nic_s *aq_nic, काष्ठा ethtool_rxnfc *cmd,
			   u32 *rule_locs)
अणु
	काष्ठा aq_hw_rx_fltrs_s *rx_fltrs = aq_get_hw_rx_fltrs(aq_nic);
	काष्ठा hlist_node *aq_node2;
	काष्ठा aq_rx_filter *rule;
	पूर्णांक count = 0;

	cmd->data = aq_get_rxnfc_count_all_rules(aq_nic);

	hlist_क्रम_each_entry_safe(rule, aq_node2,
				  &rx_fltrs->filter_list, aq_node) अणु
		अगर (unlikely(count == cmd->rule_cnt))
			वापस -EMSGSIZE;

		rule_locs[count++] = rule->aq_fsp.location;
	पूर्ण

	cmd->rule_cnt = count;

	वापस 0;
पूर्ण

पूर्णांक aq_clear_rxnfc_all_rules(काष्ठा aq_nic_s *aq_nic)
अणु
	काष्ठा aq_hw_rx_fltrs_s *rx_fltrs = aq_get_hw_rx_fltrs(aq_nic);
	काष्ठा hlist_node *aq_node2;
	काष्ठा aq_rx_filter *rule;
	पूर्णांक err = 0;

	hlist_क्रम_each_entry_safe(rule, aq_node2,
				  &rx_fltrs->filter_list, aq_node) अणु
		err = aq_add_del_rule(aq_nic, rule, false);
		अगर (err)
			जाओ err_निकास;
		hlist_del(&rule->aq_node);
		kमुक्त(rule);
		--rx_fltrs->active_filters;
	पूर्ण

err_निकास:
	वापस err;
पूर्ण

पूर्णांक aq_reapply_rxnfc_all_rules(काष्ठा aq_nic_s *aq_nic)
अणु
	काष्ठा aq_hw_rx_fltrs_s *rx_fltrs = aq_get_hw_rx_fltrs(aq_nic);
	काष्ठा hlist_node *aq_node2;
	काष्ठा aq_rx_filter *rule;
	पूर्णांक err = 0;

	hlist_क्रम_each_entry_safe(rule, aq_node2,
				  &rx_fltrs->filter_list, aq_node) अणु
		err = aq_add_del_rule(aq_nic, rule, true);
		अगर (err)
			जाओ err_निकास;
	पूर्ण

err_निकास:
	वापस err;
पूर्ण

पूर्णांक aq_filters_vlans_update(काष्ठा aq_nic_s *aq_nic)
अणु
	स्थिर काष्ठा aq_hw_ops *aq_hw_ops = aq_nic->aq_hw_ops;
	काष्ठा aq_hw_s *aq_hw = aq_nic->aq_hw;
	पूर्णांक hweight = 0;
	पूर्णांक err = 0;
	पूर्णांक i;

	अगर (unlikely(!aq_hw_ops->hw_filter_vlan_set))
		वापस -EOPNOTSUPP;
	अगर (unlikely(!aq_hw_ops->hw_filter_vlan_ctrl))
		वापस -EOPNOTSUPP;

	aq_fvlan_rebuild(aq_nic, aq_nic->active_vlans,
			 aq_nic->aq_hw_rx_fltrs.fl2.aq_vlans);

	अगर (aq_nic->ndev->features & NETIF_F_HW_VLAN_CTAG_FILTER) अणु
		क्रम (i = 0; i < BITS_TO_LONGS(VLAN_N_VID); i++)
			hweight += hweight_दीर्घ(aq_nic->active_vlans[i]);

		err = aq_hw_ops->hw_filter_vlan_ctrl(aq_hw, false);
		अगर (err)
			वापस err;
	पूर्ण

	err = aq_hw_ops->hw_filter_vlan_set(aq_hw,
					    aq_nic->aq_hw_rx_fltrs.fl2.aq_vlans
					   );
	अगर (err)
		वापस err;

	अगर (aq_nic->ndev->features & NETIF_F_HW_VLAN_CTAG_FILTER) अणु
		अगर (hweight <= AQ_VLAN_MAX_FILTERS && hweight > 0) अणु
			err = aq_hw_ops->hw_filter_vlan_ctrl(aq_hw,
				!(aq_nic->packet_filter & IFF_PROMISC));
			aq_nic->aq_nic_cfg.is_vlan_क्रमce_promisc = false;
		पूर्ण अन्यथा अणु
		/* otherwise left in promiscue mode */
			aq_nic->aq_nic_cfg.is_vlan_क्रमce_promisc = true;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक aq_filters_vlan_offload_off(काष्ठा aq_nic_s *aq_nic)
अणु
	स्थिर काष्ठा aq_hw_ops *aq_hw_ops = aq_nic->aq_hw_ops;
	काष्ठा aq_hw_s *aq_hw = aq_nic->aq_hw;
	पूर्णांक err = 0;

	स_रखो(aq_nic->active_vlans, 0, माप(aq_nic->active_vlans));
	aq_fvlan_rebuild(aq_nic, aq_nic->active_vlans,
			 aq_nic->aq_hw_rx_fltrs.fl2.aq_vlans);

	अगर (unlikely(!aq_hw_ops->hw_filter_vlan_set))
		वापस -EOPNOTSUPP;
	अगर (unlikely(!aq_hw_ops->hw_filter_vlan_ctrl))
		वापस -EOPNOTSUPP;

	aq_nic->aq_nic_cfg.is_vlan_क्रमce_promisc = true;
	err = aq_hw_ops->hw_filter_vlan_ctrl(aq_hw, false);
	अगर (err)
		वापस err;
	err = aq_hw_ops->hw_filter_vlan_set(aq_hw,
					    aq_nic->aq_hw_rx_fltrs.fl2.aq_vlans
					   );
	वापस err;
पूर्ण
