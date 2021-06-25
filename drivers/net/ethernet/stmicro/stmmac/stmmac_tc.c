<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * Copyright (c) 2018 Synopsys, Inc. and/or its affiliates.
 * sपंचांगmac TC Handling (HW only)
 */

#समावेश <net/pkt_cls.h>
#समावेश <net/tc_act/tc_gact.h>
#समावेश "common.h"
#समावेश "dwmac4.h"
#समावेश "dwmac5.h"
#समावेश "stmmac.h"

अटल व्योम tc_fill_all_pass_entry(काष्ठा sपंचांगmac_tc_entry *entry)
अणु
	स_रखो(entry, 0, माप(*entry));
	entry->in_use = true;
	entry->is_last = true;
	entry->is_frag = false;
	entry->prio = ~0x0;
	entry->handle = 0;
	entry->val.match_data = 0x0;
	entry->val.match_en = 0x0;
	entry->val.af = 1;
	entry->val.dma_ch_no = 0x0;
पूर्ण

अटल काष्ठा sपंचांगmac_tc_entry *tc_find_entry(काष्ठा sपंचांगmac_priv *priv,
					     काष्ठा tc_cls_u32_offload *cls,
					     bool मुक्त)
अणु
	काष्ठा sपंचांगmac_tc_entry *entry, *first = शून्य, *dup = शून्य;
	u32 loc = cls->knode.handle;
	पूर्णांक i;

	क्रम (i = 0; i < priv->tc_entries_max; i++) अणु
		entry = &priv->tc_entries[i];
		अगर (!entry->in_use && !first && मुक्त)
			first = entry;
		अगर ((entry->handle == loc) && !मुक्त && !entry->is_frag)
			dup = entry;
	पूर्ण

	अगर (dup)
		वापस dup;
	अगर (first) अणु
		first->handle = loc;
		first->in_use = true;

		/* Reset HW values */
		स_रखो(&first->val, 0, माप(first->val));
	पूर्ण

	वापस first;
पूर्ण

अटल पूर्णांक tc_fill_actions(काष्ठा sपंचांगmac_tc_entry *entry,
			   काष्ठा sपंचांगmac_tc_entry *frag,
			   काष्ठा tc_cls_u32_offload *cls)
अणु
	काष्ठा sपंचांगmac_tc_entry *action_entry = entry;
	स्थिर काष्ठा tc_action *act;
	काष्ठा tcf_exts *exts;
	पूर्णांक i;

	exts = cls->knode.exts;
	अगर (!tcf_exts_has_actions(exts))
		वापस -EINVAL;
	अगर (frag)
		action_entry = frag;

	tcf_exts_क्रम_each_action(i, act, exts) अणु
		/* Accept */
		अगर (is_tcf_gact_ok(act)) अणु
			action_entry->val.af = 1;
			अवरोध;
		पूर्ण
		/* Drop */
		अगर (is_tcf_gact_shot(act)) अणु
			action_entry->val.rf = 1;
			अवरोध;
		पूर्ण

		/* Unsupported */
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tc_fill_entry(काष्ठा sपंचांगmac_priv *priv,
			 काष्ठा tc_cls_u32_offload *cls)
अणु
	काष्ठा sपंचांगmac_tc_entry *entry, *frag = शून्य;
	काष्ठा tc_u32_sel *sel = cls->knode.sel;
	u32 off, data, mask, real_off, rem;
	u32 prio = cls->common.prio << 16;
	पूर्णांक ret;

	/* Only 1 match per entry */
	अगर (sel->nkeys <= 0 || sel->nkeys > 1)
		वापस -EINVAL;

	off = sel->keys[0].off << sel->offshअगरt;
	data = sel->keys[0].val;
	mask = sel->keys[0].mask;

	चयन (ntohs(cls->common.protocol)) अणु
	हाल ETH_P_ALL:
		अवरोध;
	हाल ETH_P_IP:
		off += ETH_HLEN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (off > priv->tc_off_max)
		वापस -EINVAL;

	real_off = off / 4;
	rem = off % 4;

	entry = tc_find_entry(priv, cls, true);
	अगर (!entry)
		वापस -EINVAL;

	अगर (rem) अणु
		frag = tc_find_entry(priv, cls, true);
		अगर (!frag) अणु
			ret = -EINVAL;
			जाओ err_unuse;
		पूर्ण

		entry->frag_ptr = frag;
		entry->val.match_en = (mask << (rem * 8)) &
			GENMASK(31, rem * 8);
		entry->val.match_data = (data << (rem * 8)) &
			GENMASK(31, rem * 8);
		entry->val.frame_offset = real_off;
		entry->prio = prio;

		frag->val.match_en = (mask >> (rem * 8)) &
			GENMASK(rem * 8 - 1, 0);
		frag->val.match_data = (data >> (rem * 8)) &
			GENMASK(rem * 8 - 1, 0);
		frag->val.frame_offset = real_off + 1;
		frag->prio = prio;
		frag->is_frag = true;
	पूर्ण अन्यथा अणु
		entry->frag_ptr = शून्य;
		entry->val.match_en = mask;
		entry->val.match_data = data;
		entry->val.frame_offset = real_off;
		entry->prio = prio;
	पूर्ण

	ret = tc_fill_actions(entry, frag, cls);
	अगर (ret)
		जाओ err_unuse;

	वापस 0;

err_unuse:
	अगर (frag)
		frag->in_use = false;
	entry->in_use = false;
	वापस ret;
पूर्ण

अटल व्योम tc_unfill_entry(काष्ठा sपंचांगmac_priv *priv,
			    काष्ठा tc_cls_u32_offload *cls)
अणु
	काष्ठा sपंचांगmac_tc_entry *entry;

	entry = tc_find_entry(priv, cls, false);
	अगर (!entry)
		वापस;

	entry->in_use = false;
	अगर (entry->frag_ptr) अणु
		entry = entry->frag_ptr;
		entry->is_frag = false;
		entry->in_use = false;
	पूर्ण
पूर्ण

अटल पूर्णांक tc_config_knode(काष्ठा sपंचांगmac_priv *priv,
			   काष्ठा tc_cls_u32_offload *cls)
अणु
	पूर्णांक ret;

	ret = tc_fill_entry(priv, cls);
	अगर (ret)
		वापस ret;

	ret = sपंचांगmac_rxp_config(priv, priv->hw->pcsr, priv->tc_entries,
			priv->tc_entries_max);
	अगर (ret)
		जाओ err_unfill;

	वापस 0;

err_unfill:
	tc_unfill_entry(priv, cls);
	वापस ret;
पूर्ण

अटल पूर्णांक tc_delete_knode(काष्ठा sपंचांगmac_priv *priv,
			   काष्ठा tc_cls_u32_offload *cls)
अणु
	/* Set entry and fragments as not used */
	tc_unfill_entry(priv, cls);

	वापस sपंचांगmac_rxp_config(priv, priv->hw->pcsr, priv->tc_entries,
				 priv->tc_entries_max);
पूर्ण

अटल पूर्णांक tc_setup_cls_u32(काष्ठा sपंचांगmac_priv *priv,
			    काष्ठा tc_cls_u32_offload *cls)
अणु
	चयन (cls->command) अणु
	हाल TC_CLSU32_REPLACE_KNODE:
		tc_unfill_entry(priv, cls);
		fallthrough;
	हाल TC_CLSU32_NEW_KNODE:
		वापस tc_config_knode(priv, cls);
	हाल TC_CLSU32_DELETE_KNODE:
		वापस tc_delete_knode(priv, cls);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक tc_init(काष्ठा sपंचांगmac_priv *priv)
अणु
	काष्ठा dma_features *dma_cap = &priv->dma_cap;
	अचिन्हित पूर्णांक count;
	पूर्णांक i;

	अगर (dma_cap->l3l4fnum) अणु
		priv->flow_entries_max = dma_cap->l3l4fnum;
		priv->flow_entries = devm_kसुस्मृति(priv->device,
						  dma_cap->l3l4fnum,
						  माप(*priv->flow_entries),
						  GFP_KERNEL);
		अगर (!priv->flow_entries)
			वापस -ENOMEM;

		क्रम (i = 0; i < priv->flow_entries_max; i++)
			priv->flow_entries[i].idx = i;

		dev_info(priv->device, "Enabled Flow TC (entries=%d)\n",
			 priv->flow_entries_max);
	पूर्ण

	अगर (!priv->plat->fpe_cfg) अणु
		priv->plat->fpe_cfg = devm_kzalloc(priv->device,
						   माप(*priv->plat->fpe_cfg),
						   GFP_KERNEL);
		अगर (!priv->plat->fpe_cfg)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		स_रखो(priv->plat->fpe_cfg, 0, माप(*priv->plat->fpe_cfg));
	पूर्ण

	/* Fail silently as we can still use reमुख्यing features, e.g. CBS */
	अगर (!dma_cap->frpsel)
		वापस 0;

	चयन (dma_cap->frpbs) अणु
	हाल 0x0:
		priv->tc_off_max = 64;
		अवरोध;
	हाल 0x1:
		priv->tc_off_max = 128;
		अवरोध;
	हाल 0x2:
		priv->tc_off_max = 256;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dma_cap->frpes) अणु
	हाल 0x0:
		count = 64;
		अवरोध;
	हाल 0x1:
		count = 128;
		अवरोध;
	हाल 0x2:
		count = 256;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Reserve one last filter which lets all pass */
	priv->tc_entries_max = count;
	priv->tc_entries = devm_kसुस्मृति(priv->device,
			count, माप(*priv->tc_entries), GFP_KERNEL);
	अगर (!priv->tc_entries)
		वापस -ENOMEM;

	tc_fill_all_pass_entry(&priv->tc_entries[count - 1]);

	dev_info(priv->device, "Enabling HW TC (entries=%d, max_off=%d)\n",
			priv->tc_entries_max, priv->tc_off_max);

	वापस 0;
पूर्ण

अटल पूर्णांक tc_setup_cbs(काष्ठा sपंचांगmac_priv *priv,
			काष्ठा tc_cbs_qopt_offload *qopt)
अणु
	u32 tx_queues_count = priv->plat->tx_queues_to_use;
	u32 queue = qopt->queue;
	u32 ptr, speed_भाग;
	u32 mode_to_use;
	u64 value;
	पूर्णांक ret;

	/* Queue 0 is not AVB capable */
	अगर (queue <= 0 || queue >= tx_queues_count)
		वापस -EINVAL;
	अगर (!priv->dma_cap.av)
		वापस -EOPNOTSUPP;

	/* Port Transmit Rate and Speed Divider */
	चयन (priv->speed) अणु
	हाल SPEED_10000:
		ptr = 32;
		speed_भाग = 10000000;
		अवरोध;
	हाल SPEED_5000:
		ptr = 32;
		speed_भाग = 5000000;
		अवरोध;
	हाल SPEED_2500:
		ptr = 8;
		speed_भाग = 2500000;
		अवरोध;
	हाल SPEED_1000:
		ptr = 8;
		speed_भाग = 1000000;
		अवरोध;
	हाल SPEED_100:
		ptr = 4;
		speed_भाग = 100000;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	mode_to_use = priv->plat->tx_queues_cfg[queue].mode_to_use;
	अगर (mode_to_use == MTL_QUEUE_DCB && qopt->enable) अणु
		ret = sपंचांगmac_dma_qmode(priv, priv->ioaddr, queue, MTL_QUEUE_AVB);
		अगर (ret)
			वापस ret;

		priv->plat->tx_queues_cfg[queue].mode_to_use = MTL_QUEUE_AVB;
	पूर्ण अन्यथा अगर (!qopt->enable) अणु
		ret = sपंचांगmac_dma_qmode(priv, priv->ioaddr, queue,
				       MTL_QUEUE_DCB);
		अगर (ret)
			वापस ret;

		priv->plat->tx_queues_cfg[queue].mode_to_use = MTL_QUEUE_DCB;
	पूर्ण

	/* Final adjusपंचांगents क्रम HW */
	value = भाग_s64(qopt->idleslope * 1024ll * ptr, speed_भाग);
	priv->plat->tx_queues_cfg[queue].idle_slope = value & GENMASK(31, 0);

	value = भाग_s64(-qopt->sendslope * 1024ll * ptr, speed_भाग);
	priv->plat->tx_queues_cfg[queue].send_slope = value & GENMASK(31, 0);

	value = qopt->hicredit * 1024ll * 8;
	priv->plat->tx_queues_cfg[queue].high_credit = value & GENMASK(31, 0);

	value = qopt->locredit * 1024ll * 8;
	priv->plat->tx_queues_cfg[queue].low_credit = value & GENMASK(31, 0);

	ret = sपंचांगmac_config_cbs(priv, priv->hw,
				priv->plat->tx_queues_cfg[queue].send_slope,
				priv->plat->tx_queues_cfg[queue].idle_slope,
				priv->plat->tx_queues_cfg[queue].high_credit,
				priv->plat->tx_queues_cfg[queue].low_credit,
				queue);
	अगर (ret)
		वापस ret;

	dev_info(priv->device, "CBS queue %d: send %d, idle %d, hi %d, lo %d\n",
			queue, qopt->sendslope, qopt->idleslope,
			qopt->hicredit, qopt->locredit);
	वापस 0;
पूर्ण

अटल पूर्णांक tc_parse_flow_actions(काष्ठा sपंचांगmac_priv *priv,
				 काष्ठा flow_action *action,
				 काष्ठा sपंचांगmac_flow_entry *entry,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा flow_action_entry *act;
	पूर्णांक i;

	अगर (!flow_action_has_entries(action))
		वापस -EINVAL;

	अगर (!flow_action_basic_hw_stats_check(action, extack))
		वापस -EOPNOTSUPP;

	flow_action_क्रम_each(i, act, action) अणु
		चयन (act->id) अणु
		हाल FLOW_ACTION_DROP:
			entry->action |= STMMAC_FLOW_ACTION_DROP;
			वापस 0;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* Nothing to करो, maybe inverse filter ? */
	वापस 0;
पूर्ण

अटल पूर्णांक tc_add_basic_flow(काष्ठा sपंचांगmac_priv *priv,
			     काष्ठा flow_cls_offload *cls,
			     काष्ठा sपंचांगmac_flow_entry *entry)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(cls);
	काष्ठा flow_dissector *dissector = rule->match.dissector;
	काष्ठा flow_match_basic match;

	/* Nothing to करो here */
	अगर (!dissector_uses_key(dissector, FLOW_DISSECTOR_KEY_BASIC))
		वापस -EINVAL;

	flow_rule_match_basic(rule, &match);
	entry->ip_proto = match.key->ip_proto;
	वापस 0;
पूर्ण

अटल पूर्णांक tc_add_ip4_flow(काष्ठा sपंचांगmac_priv *priv,
			   काष्ठा flow_cls_offload *cls,
			   काष्ठा sपंचांगmac_flow_entry *entry)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(cls);
	काष्ठा flow_dissector *dissector = rule->match.dissector;
	bool inv = entry->action & STMMAC_FLOW_ACTION_DROP;
	काष्ठा flow_match_ipv4_addrs match;
	u32 hw_match;
	पूर्णांक ret;

	/* Nothing to करो here */
	अगर (!dissector_uses_key(dissector, FLOW_DISSECTOR_KEY_IPV4_ADDRS))
		वापस -EINVAL;

	flow_rule_match_ipv4_addrs(rule, &match);
	hw_match = ntohl(match.key->src) & ntohl(match.mask->src);
	अगर (hw_match) अणु
		ret = sपंचांगmac_config_l3_filter(priv, priv->hw, entry->idx, true,
					      false, true, inv, hw_match);
		अगर (ret)
			वापस ret;
	पूर्ण

	hw_match = ntohl(match.key->dst) & ntohl(match.mask->dst);
	अगर (hw_match) अणु
		ret = sपंचांगmac_config_l3_filter(priv, priv->hw, entry->idx, true,
					      false, false, inv, hw_match);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tc_add_ports_flow(काष्ठा sपंचांगmac_priv *priv,
			     काष्ठा flow_cls_offload *cls,
			     काष्ठा sपंचांगmac_flow_entry *entry)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(cls);
	काष्ठा flow_dissector *dissector = rule->match.dissector;
	bool inv = entry->action & STMMAC_FLOW_ACTION_DROP;
	काष्ठा flow_match_ports match;
	u32 hw_match;
	bool is_udp;
	पूर्णांक ret;

	/* Nothing to करो here */
	अगर (!dissector_uses_key(dissector, FLOW_DISSECTOR_KEY_PORTS))
		वापस -EINVAL;

	चयन (entry->ip_proto) अणु
	हाल IPPROTO_TCP:
		is_udp = false;
		अवरोध;
	हाल IPPROTO_UDP:
		is_udp = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	flow_rule_match_ports(rule, &match);

	hw_match = ntohs(match.key->src) & ntohs(match.mask->src);
	अगर (hw_match) अणु
		ret = sपंचांगmac_config_l4_filter(priv, priv->hw, entry->idx, true,
					      is_udp, true, inv, hw_match);
		अगर (ret)
			वापस ret;
	पूर्ण

	hw_match = ntohs(match.key->dst) & ntohs(match.mask->dst);
	अगर (hw_match) अणु
		ret = sपंचांगmac_config_l4_filter(priv, priv->hw, entry->idx, true,
					      is_udp, false, inv, hw_match);
		अगर (ret)
			वापस ret;
	पूर्ण

	entry->is_l4 = true;
	वापस 0;
पूर्ण

अटल काष्ठा sपंचांगmac_flow_entry *tc_find_flow(काष्ठा sपंचांगmac_priv *priv,
					      काष्ठा flow_cls_offload *cls,
					      bool get_मुक्त)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->flow_entries_max; i++) अणु
		काष्ठा sपंचांगmac_flow_entry *entry = &priv->flow_entries[i];

		अगर (entry->cookie == cls->cookie)
			वापस entry;
		अगर (get_मुक्त && (entry->in_use == false))
			वापस entry;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा अणु
	पूर्णांक (*fn)(काष्ठा sपंचांगmac_priv *priv, काष्ठा flow_cls_offload *cls,
		  काष्ठा sपंचांगmac_flow_entry *entry);
पूर्ण tc_flow_parsers[] = अणु
	अणु .fn = tc_add_basic_flow पूर्ण,
	अणु .fn = tc_add_ip4_flow पूर्ण,
	अणु .fn = tc_add_ports_flow पूर्ण,
पूर्ण;

अटल पूर्णांक tc_add_flow(काष्ठा sपंचांगmac_priv *priv,
		       काष्ठा flow_cls_offload *cls)
अणु
	काष्ठा sपंचांगmac_flow_entry *entry = tc_find_flow(priv, cls, false);
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(cls);
	पूर्णांक i, ret;

	अगर (!entry) अणु
		entry = tc_find_flow(priv, cls, true);
		अगर (!entry)
			वापस -ENOENT;
	पूर्ण

	ret = tc_parse_flow_actions(priv, &rule->action, entry,
				    cls->common.extack);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(tc_flow_parsers); i++) अणु
		ret = tc_flow_parsers[i].fn(priv, cls, entry);
		अगर (!ret) अणु
			entry->in_use = true;
			जारी;
		पूर्ण
	पूर्ण

	अगर (!entry->in_use)
		वापस -EINVAL;

	entry->cookie = cls->cookie;
	वापस 0;
पूर्ण

अटल पूर्णांक tc_del_flow(काष्ठा sपंचांगmac_priv *priv,
		       काष्ठा flow_cls_offload *cls)
अणु
	काष्ठा sपंचांगmac_flow_entry *entry = tc_find_flow(priv, cls, false);
	पूर्णांक ret;

	अगर (!entry || !entry->in_use)
		वापस -ENOENT;

	अगर (entry->is_l4) अणु
		ret = sपंचांगmac_config_l4_filter(priv, priv->hw, entry->idx, false,
					      false, false, false, 0);
	पूर्ण अन्यथा अणु
		ret = sपंचांगmac_config_l3_filter(priv, priv->hw, entry->idx, false,
					      false, false, false, 0);
	पूर्ण

	entry->in_use = false;
	entry->cookie = 0;
	entry->is_l4 = false;
	वापस ret;
पूर्ण

#घोषणा VLAN_PRIO_FULL_MASK (0x07)

अटल पूर्णांक tc_add_vlan_flow(काष्ठा sपंचांगmac_priv *priv,
			    काष्ठा flow_cls_offload *cls)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(cls);
	काष्ठा flow_dissector *dissector = rule->match.dissector;
	पूर्णांक tc = tc_classid_to_hwtc(priv->dev, cls->classid);
	काष्ठा flow_match_vlan match;

	/* Nothing to करो here */
	अगर (!dissector_uses_key(dissector, FLOW_DISSECTOR_KEY_VLAN))
		वापस -EINVAL;

	अगर (tc < 0) अणु
		netdev_err(priv->dev, "Invalid traffic class\n");
		वापस -EINVAL;
	पूर्ण

	flow_rule_match_vlan(rule, &match);

	अगर (match.mask->vlan_priority) अणु
		u32 prio;

		अगर (match.mask->vlan_priority != VLAN_PRIO_FULL_MASK) अणु
			netdev_err(priv->dev, "Only full mask is supported for VLAN priority");
			वापस -EINVAL;
		पूर्ण

		prio = BIT(match.key->vlan_priority);
		sपंचांगmac_rx_queue_prio(priv, priv->hw, prio, tc);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tc_del_vlan_flow(काष्ठा sपंचांगmac_priv *priv,
			    काष्ठा flow_cls_offload *cls)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(cls);
	काष्ठा flow_dissector *dissector = rule->match.dissector;
	पूर्णांक tc = tc_classid_to_hwtc(priv->dev, cls->classid);

	/* Nothing to करो here */
	अगर (!dissector_uses_key(dissector, FLOW_DISSECTOR_KEY_VLAN))
		वापस -EINVAL;

	अगर (tc < 0) अणु
		netdev_err(priv->dev, "Invalid traffic class\n");
		वापस -EINVAL;
	पूर्ण

	sपंचांगmac_rx_queue_prio(priv, priv->hw, 0, tc);

	वापस 0;
पूर्ण

अटल पूर्णांक tc_add_flow_cls(काष्ठा sपंचांगmac_priv *priv,
			   काष्ठा flow_cls_offload *cls)
अणु
	पूर्णांक ret;

	ret = tc_add_flow(priv, cls);
	अगर (!ret)
		वापस ret;

	वापस tc_add_vlan_flow(priv, cls);
पूर्ण

अटल पूर्णांक tc_del_flow_cls(काष्ठा sपंचांगmac_priv *priv,
			   काष्ठा flow_cls_offload *cls)
अणु
	पूर्णांक ret;

	ret = tc_del_flow(priv, cls);
	अगर (!ret)
		वापस ret;

	वापस tc_del_vlan_flow(priv, cls);
पूर्ण

अटल पूर्णांक tc_setup_cls(काष्ठा sपंचांगmac_priv *priv,
			काष्ठा flow_cls_offload *cls)
अणु
	पूर्णांक ret = 0;

	/* When RSS is enabled, the filtering will be bypassed */
	अगर (priv->rss.enable)
		वापस -EBUSY;

	चयन (cls->command) अणु
	हाल FLOW_CLS_REPLACE:
		ret = tc_add_flow_cls(priv, cls);
		अवरोध;
	हाल FLOW_CLS_DESTROY:
		ret = tc_del_flow_cls(priv, cls);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tc_setup_taprio(काष्ठा sपंचांगmac_priv *priv,
			   काष्ठा tc_taprio_qopt_offload *qopt)
अणु
	u32 size, wid = priv->dma_cap.estwid, dep = priv->dma_cap.estdep;
	काष्ठा plat_sपंचांगmacenet_data *plat = priv->plat;
	काष्ठा बारpec64 समय, current_समय;
	kसमय_प्रकार current_समय_ns;
	bool fpe = false;
	पूर्णांक i, ret = 0;
	u64 ctr;

	अगर (!priv->dma_cap.estsel)
		वापस -EOPNOTSUPP;

	चयन (wid) अणु
	हाल 0x1:
		wid = 16;
		अवरोध;
	हाल 0x2:
		wid = 20;
		अवरोध;
	हाल 0x3:
		wid = 24;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (dep) अणु
	हाल 0x1:
		dep = 64;
		अवरोध;
	हाल 0x2:
		dep = 128;
		अवरोध;
	हाल 0x3:
		dep = 256;
		अवरोध;
	हाल 0x4:
		dep = 512;
		अवरोध;
	हाल 0x5:
		dep = 1024;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!qopt->enable)
		जाओ disable;
	अगर (qopt->num_entries >= dep)
		वापस -EINVAL;
	अगर (!qopt->base_समय)
		वापस -दुस्फल;
	अगर (!qopt->cycle_समय)
		वापस -दुस्फल;

	अगर (!plat->est) अणु
		plat->est = devm_kzalloc(priv->device, माप(*plat->est),
					 GFP_KERNEL);
		अगर (!plat->est)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		स_रखो(plat->est, 0, माप(*plat->est));
	पूर्ण

	size = qopt->num_entries;

	priv->plat->est->gcl_size = size;
	priv->plat->est->enable = qopt->enable;

	क्रम (i = 0; i < size; i++) अणु
		s64 delta_ns = qopt->entries[i].पूर्णांकerval;
		u32 gates = qopt->entries[i].gate_mask;

		अगर (delta_ns > GENMASK(wid, 0))
			वापस -दुस्फल;
		अगर (gates > GENMASK(31 - wid, 0))
			वापस -दुस्फल;

		चयन (qopt->entries[i].command) अणु
		हाल TC_TAPRIO_CMD_SET_GATES:
			अगर (fpe)
				वापस -EINVAL;
			अवरोध;
		हाल TC_TAPRIO_CMD_SET_AND_HOLD:
			gates |= BIT(0);
			fpe = true;
			अवरोध;
		हाल TC_TAPRIO_CMD_SET_AND_RELEASE:
			gates &= ~BIT(0);
			fpe = true;
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण

		priv->plat->est->gcl[i] = delta_ns | (gates << wid);
	पूर्ण

	/* Adjust क्रम real प्रणाली समय */
	priv->ptp_घड़ी_ops.समय_लो64(&priv->ptp_घड़ी_ops, &current_समय);
	current_समय_ns = बारpec64_to_kसमय(current_समय);
	अगर (kसमय_after(qopt->base_समय, current_समय_ns)) अणु
		समय = kसमय_प्रकारo_बारpec64(qopt->base_समय);
	पूर्ण अन्यथा अणु
		kसमय_प्रकार base_समय;
		s64 n;

		n = भाग64_s64(kसमय_sub_ns(current_समय_ns, qopt->base_समय),
			      qopt->cycle_समय);
		base_समय = kसमय_add_ns(qopt->base_समय,
					 (n + 1) * qopt->cycle_समय);

		समय = kसमय_प्रकारo_बारpec64(base_समय);
	पूर्ण

	priv->plat->est->btr[0] = (u32)समय.tv_nsec;
	priv->plat->est->btr[1] = (u32)समय.tv_sec;

	ctr = qopt->cycle_समय;
	priv->plat->est->ctr[0] = करो_भाग(ctr, NSEC_PER_SEC);
	priv->plat->est->ctr[1] = (u32)ctr;

	अगर (fpe && !priv->dma_cap.fpesel)
		वापस -EOPNOTSUPP;

	/* Actual FPE रेजिस्टर configuration will be करोne after FPE handshake
	 * is success.
	 */
	priv->plat->fpe_cfg->enable = fpe;

	ret = sपंचांगmac_est_configure(priv, priv->ioaddr, priv->plat->est,
				   priv->plat->clk_ptp_rate);
	अगर (ret) अणु
		netdev_err(priv->dev, "failed to configure EST\n");
		जाओ disable;
	पूर्ण

	netdev_info(priv->dev, "configured EST\n");

	अगर (fpe) अणु
		sपंचांगmac_fpe_handshake(priv, true);
		netdev_info(priv->dev, "start FPE handshake\n");
	पूर्ण

	वापस 0;

disable:
	priv->plat->est->enable = false;
	sपंचांगmac_est_configure(priv, priv->ioaddr, priv->plat->est,
			     priv->plat->clk_ptp_rate);

	priv->plat->fpe_cfg->enable = false;
	sपंचांगmac_fpe_configure(priv, priv->ioaddr,
			     priv->plat->tx_queues_to_use,
			     priv->plat->rx_queues_to_use,
			     false);
	netdev_info(priv->dev, "disabled FPE\n");

	sपंचांगmac_fpe_handshake(priv, false);
	netdev_info(priv->dev, "stop FPE handshake\n");

	वापस ret;
पूर्ण

अटल पूर्णांक tc_setup_etf(काष्ठा sपंचांगmac_priv *priv,
			काष्ठा tc_etf_qopt_offload *qopt)
अणु
	अगर (!priv->dma_cap.tbssel)
		वापस -EOPNOTSUPP;
	अगर (qopt->queue >= priv->plat->tx_queues_to_use)
		वापस -EINVAL;
	अगर (!(priv->tx_queue[qopt->queue].tbs & STMMAC_TBS_AVAIL))
		वापस -EINVAL;

	अगर (qopt->enable)
		priv->tx_queue[qopt->queue].tbs |= STMMAC_TBS_EN;
	अन्यथा
		priv->tx_queue[qopt->queue].tbs &= ~STMMAC_TBS_EN;

	netdev_info(priv->dev, "%s ETF for Queue %d\n",
		    qopt->enable ? "enabled" : "disabled", qopt->queue);
	वापस 0;
पूर्ण

स्थिर काष्ठा sपंचांगmac_tc_ops dwmac510_tc_ops = अणु
	.init = tc_init,
	.setup_cls_u32 = tc_setup_cls_u32,
	.setup_cbs = tc_setup_cbs,
	.setup_cls = tc_setup_cls,
	.setup_taprio = tc_setup_taprio,
	.setup_etf = tc_setup_etf,
पूर्ण;
