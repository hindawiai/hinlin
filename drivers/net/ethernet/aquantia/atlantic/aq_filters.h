<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (C) 2014-2017 aQuantia Corporation. */

/* File aq_filters.h: RX filters related functions. */

#अगर_अघोषित AQ_FILTERS_H
#घोषणा AQ_FILTERS_H

#समावेश "aq_nic.h"

क्रमागत aq_rx_filter_type अणु
	aq_rx_filter_ethertype,
	aq_rx_filter_vlan,
	aq_rx_filter_l3l4
पूर्ण;

काष्ठा aq_rx_filter अणु
	काष्ठा hlist_node aq_node;
	क्रमागत aq_rx_filter_type type;
	काष्ठा ethtool_rx_flow_spec aq_fsp;
पूर्ण;

u16 aq_get_rxnfc_count_all_rules(काष्ठा aq_nic_s *aq_nic);
काष्ठा aq_hw_rx_fltrs_s *aq_get_hw_rx_fltrs(काष्ठा aq_nic_s *aq_nic);
पूर्णांक aq_add_rxnfc_rule(काष्ठा aq_nic_s *aq_nic, स्थिर काष्ठा ethtool_rxnfc *cmd);
पूर्णांक aq_del_rxnfc_rule(काष्ठा aq_nic_s *aq_nic, स्थिर काष्ठा ethtool_rxnfc *cmd);
पूर्णांक aq_get_rxnfc_rule(काष्ठा aq_nic_s *aq_nic, काष्ठा ethtool_rxnfc *cmd);
पूर्णांक aq_get_rxnfc_all_rules(काष्ठा aq_nic_s *aq_nic, काष्ठा ethtool_rxnfc *cmd,
			   u32 *rule_locs);
पूर्णांक aq_del_fvlan_by_vlan(काष्ठा aq_nic_s *aq_nic, u16 vlan_id);
पूर्णांक aq_clear_rxnfc_all_rules(काष्ठा aq_nic_s *aq_nic);
पूर्णांक aq_reapply_rxnfc_all_rules(काष्ठा aq_nic_s *aq_nic);
पूर्णांक aq_filters_vlans_update(काष्ठा aq_nic_s *aq_nic);
पूर्णांक aq_filters_vlan_offload_off(काष्ठा aq_nic_s *aq_nic);

#पूर्ण_अगर /* AQ_FILTERS_H */
