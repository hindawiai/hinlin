<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DPAA2 Ethernet Switch flower support
 *
 * Copyright 2021 NXP
 *
 */

#समावेश "dpaa2-switch.h"

अटल पूर्णांक dpaa2_चयन_flower_parse_key(काष्ठा flow_cls_offload *cls,
					 काष्ठा dpsw_acl_key *acl_key)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(cls);
	काष्ठा flow_dissector *dissector = rule->match.dissector;
	काष्ठा netlink_ext_ack *extack = cls->common.extack;
	काष्ठा dpsw_acl_fields *acl_h, *acl_m;

	अगर (dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_VLAN) |
	      BIT(FLOW_DISSECTOR_KEY_PORTS) |
	      BIT(FLOW_DISSECTOR_KEY_IP) |
	      BIT(FLOW_DISSECTOR_KEY_IPV6_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_IPV4_ADDRS))) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Unsupported keys used");
		वापस -EOPNOTSUPP;
	पूर्ण

	acl_h = &acl_key->match;
	acl_m = &acl_key->mask;

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) अणु
		काष्ठा flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		acl_h->l3_protocol = match.key->ip_proto;
		acl_h->l2_ether_type = be16_to_cpu(match.key->n_proto);
		acl_m->l3_protocol = match.mask->ip_proto;
		acl_m->l2_ether_type = be16_to_cpu(match.mask->n_proto);
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ETH_ADDRS)) अणु
		काष्ठा flow_match_eth_addrs match;

		flow_rule_match_eth_addrs(rule, &match);
		ether_addr_copy(acl_h->l2_dest_mac, &match.key->dst[0]);
		ether_addr_copy(acl_h->l2_source_mac, &match.key->src[0]);
		ether_addr_copy(acl_m->l2_dest_mac, &match.mask->dst[0]);
		ether_addr_copy(acl_m->l2_source_mac, &match.mask->src[0]);
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_VLAN)) अणु
		काष्ठा flow_match_vlan match;

		flow_rule_match_vlan(rule, &match);
		acl_h->l2_vlan_id = match.key->vlan_id;
		acl_h->l2_tpid = be16_to_cpu(match.key->vlan_tpid);
		acl_h->l2_pcp_dei = match.key->vlan_priority << 1 |
				    match.key->vlan_dei;

		acl_m->l2_vlan_id = match.mask->vlan_id;
		acl_m->l2_tpid = be16_to_cpu(match.mask->vlan_tpid);
		acl_m->l2_pcp_dei = match.mask->vlan_priority << 1 |
				    match.mask->vlan_dei;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV4_ADDRS)) अणु
		काष्ठा flow_match_ipv4_addrs match;

		flow_rule_match_ipv4_addrs(rule, &match);
		acl_h->l3_source_ip = be32_to_cpu(match.key->src);
		acl_h->l3_dest_ip = be32_to_cpu(match.key->dst);
		acl_m->l3_source_ip = be32_to_cpu(match.mask->src);
		acl_m->l3_dest_ip = be32_to_cpu(match.mask->dst);
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS)) अणु
		काष्ठा flow_match_ports match;

		flow_rule_match_ports(rule, &match);
		acl_h->l4_source_port = be16_to_cpu(match.key->src);
		acl_h->l4_dest_port = be16_to_cpu(match.key->dst);
		acl_m->l4_source_port = be16_to_cpu(match.mask->src);
		acl_m->l4_dest_port = be16_to_cpu(match.mask->dst);
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IP)) अणु
		काष्ठा flow_match_ip match;

		flow_rule_match_ip(rule, &match);
		अगर (match.mask->ttl != 0) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Matching on TTL not supported");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर ((match.mask->tos & 0x3) != 0) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Matching on ECN not supported, only DSCP");
			वापस -EOPNOTSUPP;
		पूर्ण

		acl_h->l3_dscp = match.key->tos >> 2;
		acl_m->l3_dscp = match.mask->tos >> 2;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dpaa2_चयन_acl_entry_add(काष्ठा dpaa2_चयन_acl_tbl *acl_tbl,
			       काष्ठा dpaa2_चयन_acl_entry *entry)
अणु
	काष्ठा dpsw_acl_entry_cfg *acl_entry_cfg = &entry->cfg;
	काष्ठा ethsw_core *ethsw = acl_tbl->ethsw;
	काष्ठा dpsw_acl_key *acl_key = &entry->key;
	काष्ठा device *dev = ethsw->dev;
	u8 *cmd_buff;
	पूर्णांक err;

	cmd_buff = kzalloc(DPAA2_ETHSW_PORT_ACL_CMD_BUF_SIZE, GFP_KERNEL);
	अगर (!cmd_buff)
		वापस -ENOMEM;

	dpsw_acl_prepare_entry_cfg(acl_key, cmd_buff);

	acl_entry_cfg->key_iova = dma_map_single(dev, cmd_buff,
						 DPAA2_ETHSW_PORT_ACL_CMD_BUF_SIZE,
						 DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(dev, acl_entry_cfg->key_iova))) अणु
		dev_err(dev, "DMA mapping failed\n");
		वापस -EFAULT;
	पूर्ण

	err = dpsw_acl_add_entry(ethsw->mc_io, 0, ethsw->dpsw_handle,
				 acl_tbl->id, acl_entry_cfg);

	dma_unmap_single(dev, acl_entry_cfg->key_iova, माप(cmd_buff),
			 DMA_TO_DEVICE);
	अगर (err) अणु
		dev_err(dev, "dpsw_acl_add_entry() failed %d\n", err);
		वापस err;
	पूर्ण

	kमुक्त(cmd_buff);

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_चयन_acl_entry_हटाओ(काष्ठा dpaa2_चयन_acl_tbl *acl_tbl,
					 काष्ठा dpaa2_चयन_acl_entry *entry)
अणु
	काष्ठा dpsw_acl_entry_cfg *acl_entry_cfg = &entry->cfg;
	काष्ठा dpsw_acl_key *acl_key = &entry->key;
	काष्ठा ethsw_core *ethsw = acl_tbl->ethsw;
	काष्ठा device *dev = ethsw->dev;
	u8 *cmd_buff;
	पूर्णांक err;

	cmd_buff = kzalloc(DPAA2_ETHSW_PORT_ACL_CMD_BUF_SIZE, GFP_KERNEL);
	अगर (!cmd_buff)
		वापस -ENOMEM;

	dpsw_acl_prepare_entry_cfg(acl_key, cmd_buff);

	acl_entry_cfg->key_iova = dma_map_single(dev, cmd_buff,
						 DPAA2_ETHSW_PORT_ACL_CMD_BUF_SIZE,
						 DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(dev, acl_entry_cfg->key_iova))) अणु
		dev_err(dev, "DMA mapping failed\n");
		वापस -EFAULT;
	पूर्ण

	err = dpsw_acl_हटाओ_entry(ethsw->mc_io, 0, ethsw->dpsw_handle,
				    acl_tbl->id, acl_entry_cfg);

	dma_unmap_single(dev, acl_entry_cfg->key_iova, माप(cmd_buff),
			 DMA_TO_DEVICE);
	अगर (err) अणु
		dev_err(dev, "dpsw_acl_remove_entry() failed %d\n", err);
		वापस err;
	पूर्ण

	kमुक्त(cmd_buff);

	वापस 0;
पूर्ण

अटल पूर्णांक
dpaa2_चयन_acl_entry_add_to_list(काष्ठा dpaa2_चयन_acl_tbl *acl_tbl,
				   काष्ठा dpaa2_चयन_acl_entry *entry)
अणु
	काष्ठा dpaa2_चयन_acl_entry *पंचांगp;
	काष्ठा list_head *pos, *n;
	पूर्णांक index = 0;

	अगर (list_empty(&acl_tbl->entries)) अणु
		list_add(&entry->list, &acl_tbl->entries);
		वापस index;
	पूर्ण

	list_क्रम_each_safe(pos, n, &acl_tbl->entries) अणु
		पंचांगp = list_entry(pos, काष्ठा dpaa2_चयन_acl_entry, list);
		अगर (entry->prio < पंचांगp->prio)
			अवरोध;
		index++;
	पूर्ण
	list_add(&entry->list, pos->prev);
	वापस index;
पूर्ण

अटल काष्ठा dpaa2_चयन_acl_entry*
dpaa2_चयन_acl_entry_get_by_index(काष्ठा dpaa2_चयन_acl_tbl *acl_tbl,
				    पूर्णांक index)
अणु
	काष्ठा dpaa2_चयन_acl_entry *पंचांगp;
	पूर्णांक i = 0;

	list_क्रम_each_entry(पंचांगp, &acl_tbl->entries, list) अणु
		अगर (i == index)
			वापस पंचांगp;
		++i;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक
dpaa2_चयन_acl_entry_set_precedence(काष्ठा dpaa2_चयन_acl_tbl *acl_tbl,
				      काष्ठा dpaa2_चयन_acl_entry *entry,
				      पूर्णांक precedence)
अणु
	पूर्णांक err;

	err = dpaa2_चयन_acl_entry_हटाओ(acl_tbl, entry);
	अगर (err)
		वापस err;

	entry->cfg.precedence = precedence;
	वापस dpaa2_चयन_acl_entry_add(acl_tbl, entry);
पूर्ण

अटल पूर्णांक dpaa2_चयन_acl_tbl_add_entry(काष्ठा dpaa2_चयन_acl_tbl *acl_tbl,
					  काष्ठा dpaa2_चयन_acl_entry *entry)
अणु
	काष्ठा dpaa2_चयन_acl_entry *पंचांगp;
	पूर्णांक index, i, precedence, err;

	/* Add the new ACL entry to the linked list and get its index */
	index = dpaa2_चयन_acl_entry_add_to_list(acl_tbl, entry);

	/* Move up in priority the ACL entries to make space
	 * क्रम the new filter.
	 */
	precedence = DPAA2_ETHSW_PORT_MAX_ACL_ENTRIES - acl_tbl->num_rules - 1;
	क्रम (i = 0; i < index; i++) अणु
		पंचांगp = dpaa2_चयन_acl_entry_get_by_index(acl_tbl, i);

		err = dpaa2_चयन_acl_entry_set_precedence(acl_tbl, पंचांगp,
							    precedence);
		अगर (err)
			वापस err;

		precedence++;
	पूर्ण

	/* Add the new entry to hardware */
	entry->cfg.precedence = precedence;
	err = dpaa2_चयन_acl_entry_add(acl_tbl, entry);
	acl_tbl->num_rules++;

	वापस err;
पूर्ण

अटल काष्ठा dpaa2_चयन_acl_entry *
dpaa2_चयन_acl_tbl_find_entry_by_cookie(काष्ठा dpaa2_चयन_acl_tbl *acl_tbl,
					  अचिन्हित दीर्घ cookie)
अणु
	काष्ठा dpaa2_चयन_acl_entry *पंचांगp, *n;

	list_क्रम_each_entry_safe(पंचांगp, n, &acl_tbl->entries, list) अणु
		अगर (पंचांगp->cookie == cookie)
			वापस पंचांगp;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक
dpaa2_चयन_acl_entry_get_index(काष्ठा dpaa2_चयन_acl_tbl *acl_tbl,
				 काष्ठा dpaa2_चयन_acl_entry *entry)
अणु
	काष्ठा dpaa2_चयन_acl_entry *पंचांगp, *n;
	पूर्णांक index = 0;

	list_क्रम_each_entry_safe(पंचांगp, n, &acl_tbl->entries, list) अणु
		अगर (पंचांगp->cookie == entry->cookie)
			वापस index;
		index++;
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक
dpaa2_चयन_acl_tbl_हटाओ_entry(काष्ठा dpaa2_चयन_acl_tbl *acl_tbl,
				  काष्ठा dpaa2_चयन_acl_entry *entry)
अणु
	काष्ठा dpaa2_चयन_acl_entry *पंचांगp;
	पूर्णांक index, i, precedence, err;

	index = dpaa2_चयन_acl_entry_get_index(acl_tbl, entry);

	/* Remove from hardware the ACL entry */
	err = dpaa2_चयन_acl_entry_हटाओ(acl_tbl, entry);
	अगर (err)
		वापस err;

	acl_tbl->num_rules--;

	/* Remove it from the list also */
	list_del(&entry->list);

	/* Move करोwn in priority the entries over the deleted one */
	precedence = entry->cfg.precedence;
	क्रम (i = index - 1; i >= 0; i--) अणु
		पंचांगp = dpaa2_चयन_acl_entry_get_by_index(acl_tbl, i);
		err = dpaa2_चयन_acl_entry_set_precedence(acl_tbl, पंचांगp,
							    precedence);
		अगर (err)
			वापस err;

		precedence--;
	पूर्ण

	kमुक्त(entry);

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_चयन_tc_parse_action(काष्ठा ethsw_core *ethsw,
					काष्ठा flow_action_entry *cls_act,
					काष्ठा dpsw_acl_result *dpsw_act,
					काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err = 0;

	चयन (cls_act->id) अणु
	हाल FLOW_ACTION_TRAP:
		dpsw_act->action = DPSW_ACL_ACTION_REसूचीECT_TO_CTRL_IF;
		अवरोध;
	हाल FLOW_ACTION_REसूचीECT:
		अगर (!dpaa2_चयन_port_dev_check(cls_act->dev)) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Destination not a DPAA2 switch port");
			वापस -EOPNOTSUPP;
		पूर्ण

		dpsw_act->अगर_id = dpaa2_चयन_get_index(ethsw, cls_act->dev);
		dpsw_act->action = DPSW_ACL_ACTION_REसूचीECT;
		अवरोध;
	हाल FLOW_ACTION_DROP:
		dpsw_act->action = DPSW_ACL_ACTION_DROP;
		अवरोध;
	शेष:
		NL_SET_ERR_MSG_MOD(extack,
				   "Action not supported");
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

out:
	वापस err;
पूर्ण

पूर्णांक dpaa2_चयन_cls_flower_replace(काष्ठा dpaa2_चयन_acl_tbl *acl_tbl,
				    काष्ठा flow_cls_offload *cls)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(cls);
	काष्ठा netlink_ext_ack *extack = cls->common.extack;
	काष्ठा ethsw_core *ethsw = acl_tbl->ethsw;
	काष्ठा dpaa2_चयन_acl_entry *acl_entry;
	काष्ठा flow_action_entry *act;
	पूर्णांक err;

	अगर (!flow_offload_has_one_action(&rule->action)) अणु
		NL_SET_ERR_MSG(extack, "Only singular actions are supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (dpaa2_चयन_acl_tbl_is_full(acl_tbl)) अणु
		NL_SET_ERR_MSG(extack, "Maximum filter capacity reached");
		वापस -ENOMEM;
	पूर्ण

	acl_entry = kzalloc(माप(*acl_entry), GFP_KERNEL);
	अगर (!acl_entry)
		वापस -ENOMEM;

	err = dpaa2_चयन_flower_parse_key(cls, &acl_entry->key);
	अगर (err)
		जाओ मुक्त_acl_entry;

	act = &rule->action.entries[0];
	err = dpaa2_चयन_tc_parse_action(ethsw, act,
					   &acl_entry->cfg.result, extack);
	अगर (err)
		जाओ मुक्त_acl_entry;

	acl_entry->prio = cls->common.prio;
	acl_entry->cookie = cls->cookie;

	err = dpaa2_चयन_acl_tbl_add_entry(acl_tbl, acl_entry);
	अगर (err)
		जाओ मुक्त_acl_entry;

	वापस 0;

मुक्त_acl_entry:
	kमुक्त(acl_entry);

	वापस err;
पूर्ण

पूर्णांक dpaa2_चयन_cls_flower_destroy(काष्ठा dpaa2_चयन_acl_tbl *acl_tbl,
				    काष्ठा flow_cls_offload *cls)
अणु
	काष्ठा dpaa2_चयन_acl_entry *entry;

	entry = dpaa2_चयन_acl_tbl_find_entry_by_cookie(acl_tbl, cls->cookie);
	अगर (!entry)
		वापस 0;

	वापस dpaa2_चयन_acl_tbl_हटाओ_entry(acl_tbl, entry);
पूर्ण

पूर्णांक dpaa2_चयन_cls_matchall_replace(काष्ठा dpaa2_चयन_acl_tbl *acl_tbl,
				      काष्ठा tc_cls_matchall_offload *cls)
अणु
	काष्ठा netlink_ext_ack *extack = cls->common.extack;
	काष्ठा ethsw_core *ethsw = acl_tbl->ethsw;
	काष्ठा dpaa2_चयन_acl_entry *acl_entry;
	काष्ठा flow_action_entry *act;
	पूर्णांक err;

	अगर (!flow_offload_has_one_action(&cls->rule->action)) अणु
		NL_SET_ERR_MSG(extack, "Only singular actions are supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (dpaa2_चयन_acl_tbl_is_full(acl_tbl)) अणु
		NL_SET_ERR_MSG(extack, "Maximum filter capacity reached");
		वापस -ENOMEM;
	पूर्ण

	acl_entry = kzalloc(माप(*acl_entry), GFP_KERNEL);
	अगर (!acl_entry)
		वापस -ENOMEM;

	act = &cls->rule->action.entries[0];
	err = dpaa2_चयन_tc_parse_action(ethsw, act,
					   &acl_entry->cfg.result, extack);
	अगर (err)
		जाओ मुक्त_acl_entry;

	acl_entry->prio = cls->common.prio;
	acl_entry->cookie = cls->cookie;

	err = dpaa2_चयन_acl_tbl_add_entry(acl_tbl, acl_entry);
	अगर (err)
		जाओ मुक्त_acl_entry;

	वापस 0;

मुक्त_acl_entry:
	kमुक्त(acl_entry);

	वापस err;
पूर्ण

पूर्णांक dpaa2_चयन_cls_matchall_destroy(काष्ठा dpaa2_चयन_acl_tbl *acl_tbl,
				      काष्ठा tc_cls_matchall_offload *cls)
अणु
	काष्ठा dpaa2_चयन_acl_entry *entry;

	entry = dpaa2_चयन_acl_tbl_find_entry_by_cookie(acl_tbl, cls->cookie);
	अगर (!entry)
		वापस 0;

	वापस  dpaa2_चयन_acl_tbl_हटाओ_entry(acl_tbl, entry);
पूर्ण
