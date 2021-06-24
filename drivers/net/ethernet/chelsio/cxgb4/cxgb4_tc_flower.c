<शैली गुरु>
/*
 * This file is part of the Chelsio T4/T5/T6 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2017 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <net/tc_act/tc_mirred.h>
#समावेश <net/tc_act/tc_pedit.h>
#समावेश <net/tc_act/tc_gact.h>
#समावेश <net/tc_act/tc_vlan.h>

#समावेश "cxgb4.h"
#समावेश "cxgb4_filter.h"
#समावेश "cxgb4_tc_flower.h"

#घोषणा STATS_CHECK_PERIOD (HZ / 2)

अटल काष्ठा ch_tc_pedit_fields pedits[] = अणु
	PEDIT_FIELDS(ETH_, DMAC_31_0, 4, dmac, 0),
	PEDIT_FIELDS(ETH_, DMAC_47_32, 2, dmac, 4),
	PEDIT_FIELDS(ETH_, SMAC_15_0, 2, smac, 0),
	PEDIT_FIELDS(ETH_, SMAC_47_16, 4, smac, 2),
	PEDIT_FIELDS(IP4_, SRC, 4, nat_fip, 0),
	PEDIT_FIELDS(IP4_, DST, 4, nat_lip, 0),
	PEDIT_FIELDS(IP6_, SRC_31_0, 4, nat_fip, 0),
	PEDIT_FIELDS(IP6_, SRC_63_32, 4, nat_fip, 4),
	PEDIT_FIELDS(IP6_, SRC_95_64, 4, nat_fip, 8),
	PEDIT_FIELDS(IP6_, SRC_127_96, 4, nat_fip, 12),
	PEDIT_FIELDS(IP6_, DST_31_0, 4, nat_lip, 0),
	PEDIT_FIELDS(IP6_, DST_63_32, 4, nat_lip, 4),
	PEDIT_FIELDS(IP6_, DST_95_64, 4, nat_lip, 8),
	PEDIT_FIELDS(IP6_, DST_127_96, 4, nat_lip, 12),
पूर्ण;

अटल स्थिर काष्ठा cxgb4_naपंचांगode_config cxgb4_naपंचांगode_config_array[] = अणु
	/* Default supported NAT modes */
	अणु
		.chip = CHELSIO_T5,
		.flags = CXGB4_ACTION_NATMODE_NONE,
		.naपंचांगode = NAT_MODE_NONE,
	पूर्ण,
	अणु
		.chip = CHELSIO_T5,
		.flags = CXGB4_ACTION_NATMODE_DIP,
		.naपंचांगode = NAT_MODE_DIP,
	पूर्ण,
	अणु
		.chip = CHELSIO_T5,
		.flags = CXGB4_ACTION_NATMODE_DIP | CXGB4_ACTION_NATMODE_DPORT,
		.naपंचांगode = NAT_MODE_DIP_DP,
	पूर्ण,
	अणु
		.chip = CHELSIO_T5,
		.flags = CXGB4_ACTION_NATMODE_DIP | CXGB4_ACTION_NATMODE_DPORT |
			 CXGB4_ACTION_NATMODE_SIP,
		.naपंचांगode = NAT_MODE_DIP_DP_SIP,
	पूर्ण,
	अणु
		.chip = CHELSIO_T5,
		.flags = CXGB4_ACTION_NATMODE_DIP | CXGB4_ACTION_NATMODE_DPORT |
			 CXGB4_ACTION_NATMODE_SPORT,
		.naपंचांगode = NAT_MODE_DIP_DP_SP,
	पूर्ण,
	अणु
		.chip = CHELSIO_T5,
		.flags = CXGB4_ACTION_NATMODE_SIP | CXGB4_ACTION_NATMODE_SPORT,
		.naपंचांगode = NAT_MODE_SIP_SP,
	पूर्ण,
	अणु
		.chip = CHELSIO_T5,
		.flags = CXGB4_ACTION_NATMODE_DIP | CXGB4_ACTION_NATMODE_SIP |
			 CXGB4_ACTION_NATMODE_SPORT,
		.naपंचांगode = NAT_MODE_DIP_SIP_SP,
	पूर्ण,
	अणु
		.chip = CHELSIO_T5,
		.flags = CXGB4_ACTION_NATMODE_DIP | CXGB4_ACTION_NATMODE_SIP |
			 CXGB4_ACTION_NATMODE_DPORT |
			 CXGB4_ACTION_NATMODE_SPORT,
		.naपंचांगode = NAT_MODE_ALL,
	पूर्ण,
	/* T6+ can ignore L4 ports when they're disabled. */
	अणु
		.chip = CHELSIO_T6,
		.flags = CXGB4_ACTION_NATMODE_SIP,
		.naपंचांगode = NAT_MODE_SIP_SP,
	पूर्ण,
	अणु
		.chip = CHELSIO_T6,
		.flags = CXGB4_ACTION_NATMODE_DIP | CXGB4_ACTION_NATMODE_SPORT,
		.naपंचांगode = NAT_MODE_DIP_DP_SP,
	पूर्ण,
	अणु
		.chip = CHELSIO_T6,
		.flags = CXGB4_ACTION_NATMODE_DIP | CXGB4_ACTION_NATMODE_SIP,
		.naपंचांगode = NAT_MODE_ALL,
	पूर्ण,
पूर्ण;

अटल व्योम cxgb4_action_naपंचांगode_tweak(काष्ठा ch_filter_specअगरication *fs,
				       u8 naपंचांगode_flags)
अणु
	u8 i = 0;

	/* Translate the enabled NAT 4-tuple fields to one of the
	 * hardware supported NAT mode configurations. This ensures
	 * that we pick a valid combination, where the disabled fields
	 * करो not get overwritten to 0.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(cxgb4_naपंचांगode_config_array); i++) अणु
		अगर (cxgb4_naपंचांगode_config_array[i].flags == naपंचांगode_flags) अणु
			fs->nat_mode = cxgb4_naपंचांगode_config_array[i].naपंचांगode;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा ch_tc_flower_entry *allocate_flower_entry(व्योम)
अणु
	काष्ठा ch_tc_flower_entry *new = kzalloc(माप(*new), GFP_KERNEL);
	अगर (new)
		spin_lock_init(&new->lock);
	वापस new;
पूर्ण

/* Must be called with either RTNL or rcu_पढ़ो_lock */
अटल काष्ठा ch_tc_flower_entry *ch_flower_lookup(काष्ठा adapter *adap,
						   अचिन्हित दीर्घ flower_cookie)
अणु
	वापस rhashtable_lookup_fast(&adap->flower_tbl, &flower_cookie,
				      adap->flower_ht_params);
पूर्ण

अटल व्योम cxgb4_process_flow_match(काष्ठा net_device *dev,
				     काष्ठा flow_rule *rule,
				     काष्ठा ch_filter_specअगरication *fs)
अणु
	u16 addr_type = 0;

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_CONTROL)) अणु
		काष्ठा flow_match_control match;

		flow_rule_match_control(rule, &match);
		addr_type = match.key->addr_type;
	पूर्ण अन्यथा अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV4_ADDRS)) अणु
		addr_type = FLOW_DISSECTOR_KEY_IPV4_ADDRS;
	पूर्ण अन्यथा अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV6_ADDRS)) अणु
		addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) अणु
		काष्ठा flow_match_basic match;
		u16 ethtype_key, ethtype_mask;

		flow_rule_match_basic(rule, &match);
		ethtype_key = ntohs(match.key->n_proto);
		ethtype_mask = ntohs(match.mask->n_proto);

		अगर (ethtype_key == ETH_P_ALL) अणु
			ethtype_key = 0;
			ethtype_mask = 0;
		पूर्ण

		अगर (ethtype_key == ETH_P_IPV6)
			fs->type = 1;

		fs->val.ethtype = ethtype_key;
		fs->mask.ethtype = ethtype_mask;
		fs->val.proto = match.key->ip_proto;
		fs->mask.proto = match.mask->ip_proto;
	पूर्ण

	अगर (addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS) अणु
		काष्ठा flow_match_ipv4_addrs match;

		flow_rule_match_ipv4_addrs(rule, &match);
		fs->type = 0;
		स_नकल(&fs->val.lip[0], &match.key->dst, माप(match.key->dst));
		स_नकल(&fs->val.fip[0], &match.key->src, माप(match.key->src));
		स_नकल(&fs->mask.lip[0], &match.mask->dst, माप(match.mask->dst));
		स_नकल(&fs->mask.fip[0], &match.mask->src, माप(match.mask->src));

		/* also initialize nat_lip/fip to same values */
		स_नकल(&fs->nat_lip[0], &match.key->dst, माप(match.key->dst));
		स_नकल(&fs->nat_fip[0], &match.key->src, माप(match.key->src));
	पूर्ण

	अगर (addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS) अणु
		काष्ठा flow_match_ipv6_addrs match;

		flow_rule_match_ipv6_addrs(rule, &match);
		fs->type = 1;
		स_नकल(&fs->val.lip[0], match.key->dst.s6_addr,
		       माप(match.key->dst));
		स_नकल(&fs->val.fip[0], match.key->src.s6_addr,
		       माप(match.key->src));
		स_नकल(&fs->mask.lip[0], match.mask->dst.s6_addr,
		       माप(match.mask->dst));
		स_नकल(&fs->mask.fip[0], match.mask->src.s6_addr,
		       माप(match.mask->src));

		/* also initialize nat_lip/fip to same values */
		स_नकल(&fs->nat_lip[0], match.key->dst.s6_addr,
		       माप(match.key->dst));
		स_नकल(&fs->nat_fip[0], match.key->src.s6_addr,
		       माप(match.key->src));
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS)) अणु
		काष्ठा flow_match_ports match;

		flow_rule_match_ports(rule, &match);
		fs->val.lport = be16_to_cpu(match.key->dst);
		fs->mask.lport = be16_to_cpu(match.mask->dst);
		fs->val.fport = be16_to_cpu(match.key->src);
		fs->mask.fport = be16_to_cpu(match.mask->src);

		/* also initialize nat_lport/fport to same values */
		fs->nat_lport = fs->val.lport;
		fs->nat_fport = fs->val.fport;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IP)) अणु
		काष्ठा flow_match_ip match;

		flow_rule_match_ip(rule, &match);
		fs->val.tos = match.key->tos;
		fs->mask.tos = match.mask->tos;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_KEYID)) अणु
		काष्ठा flow_match_enc_keyid match;

		flow_rule_match_enc_keyid(rule, &match);
		fs->val.vni = be32_to_cpu(match.key->keyid);
		fs->mask.vni = be32_to_cpu(match.mask->keyid);
		अगर (fs->mask.vni) अणु
			fs->val.encap_vld = 1;
			fs->mask.encap_vld = 1;
		पूर्ण
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_VLAN)) अणु
		काष्ठा flow_match_vlan match;
		u16 vlan_tci, vlan_tci_mask;

		flow_rule_match_vlan(rule, &match);
		vlan_tci = match.key->vlan_id | (match.key->vlan_priority <<
					       VLAN_PRIO_SHIFT);
		vlan_tci_mask = match.mask->vlan_id | (match.mask->vlan_priority <<
						     VLAN_PRIO_SHIFT);
		fs->val.ivlan = vlan_tci;
		fs->mask.ivlan = vlan_tci_mask;

		fs->val.ivlan_vld = 1;
		fs->mask.ivlan_vld = 1;

		/* Chelsio adapters use ivlan_vld bit to match vlan packets
		 * as 802.1Q. Also, when vlan tag is present in packets,
		 * ethtype match is used then to match on ethtype of inner
		 * header ie. the header following the vlan header.
		 * So, set the ivlan_vld based on ethtype info supplied by
		 * TC क्रम vlan packets अगर its 802.1Q. And then reset the
		 * ethtype value अन्यथा, hw will try to match the supplied
		 * ethtype value with ethtype of inner header.
		 */
		अगर (fs->val.ethtype == ETH_P_8021Q) अणु
			fs->val.ethtype = 0;
			fs->mask.ethtype = 0;
		पूर्ण
	पूर्ण

	/* Match only packets coming from the ingress port where this
	 * filter will be created.
	 */
	fs->val.iport = netdev2pinfo(dev)->port_id;
	fs->mask.iport = ~0;
पूर्ण

अटल पूर्णांक cxgb4_validate_flow_match(काष्ठा net_device *dev,
				     काष्ठा flow_rule *rule)
अणु
	काष्ठा flow_dissector *dissector = rule->match.dissector;
	u16 ethtype_mask = 0;
	u16 ethtype_key = 0;

	अगर (dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_IPV4_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_IPV6_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_PORTS) |
	      BIT(FLOW_DISSECTOR_KEY_ENC_KEYID) |
	      BIT(FLOW_DISSECTOR_KEY_VLAN) |
	      BIT(FLOW_DISSECTOR_KEY_IP))) अणु
		netdev_warn(dev, "Unsupported key used: 0x%x\n",
			    dissector->used_keys);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) अणु
		काष्ठा flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		ethtype_key = ntohs(match.key->n_proto);
		ethtype_mask = ntohs(match.mask->n_proto);
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IP)) अणु
		u16 eth_ip_type = ethtype_key & ethtype_mask;
		काष्ठा flow_match_ip match;

		अगर (eth_ip_type != ETH_P_IP && eth_ip_type != ETH_P_IPV6) अणु
			netdev_err(dev, "IP Key supported only with IPv4/v6");
			वापस -EINVAL;
		पूर्ण

		flow_rule_match_ip(rule, &match);
		अगर (match.mask->ttl) अणु
			netdev_warn(dev, "ttl match unsupported for offload");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम offload_pedit(काष्ठा ch_filter_specअगरication *fs, u32 val, u32 mask,
			  u8 field)
अणु
	u32 set_val = val & ~mask;
	u32 offset = 0;
	u8 size = 1;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pedits); i++) अणु
		अगर (pedits[i].field == field) अणु
			offset = pedits[i].offset;
			size = pedits[i].size;
			अवरोध;
		पूर्ण
	पूर्ण
	स_नकल((u8 *)fs + offset, &set_val, size);
पूर्ण

अटल व्योम process_pedit_field(काष्ठा ch_filter_specअगरication *fs, u32 val,
				u32 mask, u32 offset, u8 htype,
				u8 *naपंचांगode_flags)
अणु
	चयन (htype) अणु
	हाल FLOW_ACT_MANGLE_HDR_TYPE_ETH:
		चयन (offset) अणु
		हाल PEDIT_ETH_DMAC_31_0:
			fs->newdmac = 1;
			offload_pedit(fs, val, mask, ETH_DMAC_31_0);
			अवरोध;
		हाल PEDIT_ETH_DMAC_47_32_SMAC_15_0:
			अगर (~mask & PEDIT_ETH_DMAC_MASK)
				offload_pedit(fs, val, mask, ETH_DMAC_47_32);
			अन्यथा
				offload_pedit(fs, val >> 16, mask >> 16,
					      ETH_SMAC_15_0);
			अवरोध;
		हाल PEDIT_ETH_SMAC_47_16:
			fs->newsmac = 1;
			offload_pedit(fs, val, mask, ETH_SMAC_47_16);
		पूर्ण
		अवरोध;
	हाल FLOW_ACT_MANGLE_HDR_TYPE_IP4:
		चयन (offset) अणु
		हाल PEDIT_IP4_SRC:
			offload_pedit(fs, val, mask, IP4_SRC);
			*naपंचांगode_flags |= CXGB4_ACTION_NATMODE_SIP;
			अवरोध;
		हाल PEDIT_IP4_DST:
			offload_pedit(fs, val, mask, IP4_DST);
			*naपंचांगode_flags |= CXGB4_ACTION_NATMODE_DIP;
		पूर्ण
		अवरोध;
	हाल FLOW_ACT_MANGLE_HDR_TYPE_IP6:
		चयन (offset) अणु
		हाल PEDIT_IP6_SRC_31_0:
			offload_pedit(fs, val, mask, IP6_SRC_31_0);
			*naपंचांगode_flags |= CXGB4_ACTION_NATMODE_SIP;
			अवरोध;
		हाल PEDIT_IP6_SRC_63_32:
			offload_pedit(fs, val, mask, IP6_SRC_63_32);
			*naपंचांगode_flags |=  CXGB4_ACTION_NATMODE_SIP;
			अवरोध;
		हाल PEDIT_IP6_SRC_95_64:
			offload_pedit(fs, val, mask, IP6_SRC_95_64);
			*naपंचांगode_flags |= CXGB4_ACTION_NATMODE_SIP;
			अवरोध;
		हाल PEDIT_IP6_SRC_127_96:
			offload_pedit(fs, val, mask, IP6_SRC_127_96);
			*naपंचांगode_flags |= CXGB4_ACTION_NATMODE_SIP;
			अवरोध;
		हाल PEDIT_IP6_DST_31_0:
			offload_pedit(fs, val, mask, IP6_DST_31_0);
			*naपंचांगode_flags |= CXGB4_ACTION_NATMODE_DIP;
			अवरोध;
		हाल PEDIT_IP6_DST_63_32:
			offload_pedit(fs, val, mask, IP6_DST_63_32);
			*naपंचांगode_flags |= CXGB4_ACTION_NATMODE_DIP;
			अवरोध;
		हाल PEDIT_IP6_DST_95_64:
			offload_pedit(fs, val, mask, IP6_DST_95_64);
			*naपंचांगode_flags |= CXGB4_ACTION_NATMODE_DIP;
			अवरोध;
		हाल PEDIT_IP6_DST_127_96:
			offload_pedit(fs, val, mask, IP6_DST_127_96);
			*naपंचांगode_flags |= CXGB4_ACTION_NATMODE_DIP;
		पूर्ण
		अवरोध;
	हाल FLOW_ACT_MANGLE_HDR_TYPE_TCP:
		चयन (offset) अणु
		हाल PEDIT_TCP_SPORT_DPORT:
			अगर (~mask & PEDIT_TCP_UDP_SPORT_MASK) अणु
				fs->nat_fport = val;
				*naपंचांगode_flags |= CXGB4_ACTION_NATMODE_SPORT;
			पूर्ण अन्यथा अणु
				fs->nat_lport = val >> 16;
				*naपंचांगode_flags |= CXGB4_ACTION_NATMODE_DPORT;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल FLOW_ACT_MANGLE_HDR_TYPE_UDP:
		चयन (offset) अणु
		हाल PEDIT_UDP_SPORT_DPORT:
			अगर (~mask & PEDIT_TCP_UDP_SPORT_MASK) अणु
				fs->nat_fport = val;
				*naपंचांगode_flags |= CXGB4_ACTION_NATMODE_SPORT;
			पूर्ण अन्यथा अणु
				fs->nat_lport = val >> 16;
				*naपंचांगode_flags |= CXGB4_ACTION_NATMODE_DPORT;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक cxgb4_action_naपंचांगode_validate(काष्ठा adapter *adap, u8 naपंचांगode_flags,
					 काष्ठा netlink_ext_ack *extack)
अणु
	u8 i = 0;

	/* Extract the NAT mode to enable based on what 4-tuple fields
	 * are enabled to be overwritten. This ensures that the
	 * disabled fields करोn't get overwritten to 0.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(cxgb4_naपंचांगode_config_array); i++) अणु
		स्थिर काष्ठा cxgb4_naपंचांगode_config *c;

		c = &cxgb4_naपंचांगode_config_array[i];
		अगर (CHELSIO_CHIP_VERSION(adap->params.chip) >= c->chip &&
		    naपंचांगode_flags == c->flags)
			वापस 0;
	पूर्ण
	NL_SET_ERR_MSG_MOD(extack, "Unsupported NAT mode 4-tuple combination");
	वापस -EOPNOTSUPP;
पूर्ण

व्योम cxgb4_process_flow_actions(काष्ठा net_device *in,
				काष्ठा flow_action *actions,
				काष्ठा ch_filter_specअगरication *fs)
अणु
	काष्ठा flow_action_entry *act;
	u8 naपंचांगode_flags = 0;
	पूर्णांक i;

	flow_action_क्रम_each(i, act, actions) अणु
		चयन (act->id) अणु
		हाल FLOW_ACTION_ACCEPT:
			fs->action = FILTER_PASS;
			अवरोध;
		हाल FLOW_ACTION_DROP:
			fs->action = FILTER_DROP;
			अवरोध;
		हाल FLOW_ACTION_MIRRED:
		हाल FLOW_ACTION_REसूचीECT: अणु
			काष्ठा net_device *out = act->dev;
			काष्ठा port_info *pi = netdev_priv(out);

			fs->action = FILTER_SWITCH;
			fs->eport = pi->port_id;
			पूर्ण
			अवरोध;
		हाल FLOW_ACTION_VLAN_POP:
		हाल FLOW_ACTION_VLAN_PUSH:
		हाल FLOW_ACTION_VLAN_MANGLE: अणु
			u8 prio = act->vlan.prio;
			u16 vid = act->vlan.vid;
			u16 vlan_tci = (prio << VLAN_PRIO_SHIFT) | vid;
			चयन (act->id) अणु
			हाल FLOW_ACTION_VLAN_POP:
				fs->newvlan |= VLAN_REMOVE;
				अवरोध;
			हाल FLOW_ACTION_VLAN_PUSH:
				fs->newvlan |= VLAN_INSERT;
				fs->vlan = vlan_tci;
				अवरोध;
			हाल FLOW_ACTION_VLAN_MANGLE:
				fs->newvlan |= VLAN_REWRITE;
				fs->vlan = vlan_tci;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			पूर्ण
			अवरोध;
		हाल FLOW_ACTION_MANGLE: अणु
			u32 mask, val, offset;
			u8 htype;

			htype = act->mangle.htype;
			mask = act->mangle.mask;
			val = act->mangle.val;
			offset = act->mangle.offset;

			process_pedit_field(fs, val, mask, offset, htype,
					    &naपंचांगode_flags);
			पूर्ण
			अवरोध;
		हाल FLOW_ACTION_QUEUE:
			fs->action = FILTER_PASS;
			fs->dirsteer = 1;
			fs->iq = act->queue.index;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (naपंचांगode_flags)
		cxgb4_action_naपंचांगode_tweak(fs, naपंचांगode_flags);

पूर्ण

अटल bool valid_l4_mask(u32 mask)
अणु
	u16 hi, lo;

	/* Either the upper 16-bits (SPORT) OR the lower
	 * 16-bits (DPORT) can be set, but NOT BOTH.
	 */
	hi = (mask >> 16) & 0xFFFF;
	lo = mask & 0xFFFF;

	वापस hi && lo ? false : true;
पूर्ण

अटल bool valid_pedit_action(काष्ठा net_device *dev,
			       स्थिर काष्ठा flow_action_entry *act,
			       u8 *naपंचांगode_flags)
अणु
	u32 mask, offset;
	u8 htype;

	htype = act->mangle.htype;
	mask = act->mangle.mask;
	offset = act->mangle.offset;

	चयन (htype) अणु
	हाल FLOW_ACT_MANGLE_HDR_TYPE_ETH:
		चयन (offset) अणु
		हाल PEDIT_ETH_DMAC_31_0:
		हाल PEDIT_ETH_DMAC_47_32_SMAC_15_0:
		हाल PEDIT_ETH_SMAC_47_16:
			अवरोध;
		शेष:
			netdev_err(dev, "%s: Unsupported pedit field\n",
				   __func__);
			वापस false;
		पूर्ण
		अवरोध;
	हाल FLOW_ACT_MANGLE_HDR_TYPE_IP4:
		चयन (offset) अणु
		हाल PEDIT_IP4_SRC:
			*naपंचांगode_flags |= CXGB4_ACTION_NATMODE_SIP;
			अवरोध;
		हाल PEDIT_IP4_DST:
			*naपंचांगode_flags |= CXGB4_ACTION_NATMODE_DIP;
			अवरोध;
		शेष:
			netdev_err(dev, "%s: Unsupported pedit field\n",
				   __func__);
			वापस false;
		पूर्ण
		अवरोध;
	हाल FLOW_ACT_MANGLE_HDR_TYPE_IP6:
		चयन (offset) अणु
		हाल PEDIT_IP6_SRC_31_0:
		हाल PEDIT_IP6_SRC_63_32:
		हाल PEDIT_IP6_SRC_95_64:
		हाल PEDIT_IP6_SRC_127_96:
			*naपंचांगode_flags |= CXGB4_ACTION_NATMODE_SIP;
			अवरोध;
		हाल PEDIT_IP6_DST_31_0:
		हाल PEDIT_IP6_DST_63_32:
		हाल PEDIT_IP6_DST_95_64:
		हाल PEDIT_IP6_DST_127_96:
			*naपंचांगode_flags |= CXGB4_ACTION_NATMODE_DIP;
			अवरोध;
		शेष:
			netdev_err(dev, "%s: Unsupported pedit field\n",
				   __func__);
			वापस false;
		पूर्ण
		अवरोध;
	हाल FLOW_ACT_MANGLE_HDR_TYPE_TCP:
		चयन (offset) अणु
		हाल PEDIT_TCP_SPORT_DPORT:
			अगर (!valid_l4_mask(~mask)) अणु
				netdev_err(dev, "%s: Unsupported mask for TCP L4 ports\n",
					   __func__);
				वापस false;
			पूर्ण
			अगर (~mask & PEDIT_TCP_UDP_SPORT_MASK)
				*naपंचांगode_flags |= CXGB4_ACTION_NATMODE_SPORT;
			अन्यथा
				*naपंचांगode_flags |= CXGB4_ACTION_NATMODE_DPORT;
			अवरोध;
		शेष:
			netdev_err(dev, "%s: Unsupported pedit field\n",
				   __func__);
			वापस false;
		पूर्ण
		अवरोध;
	हाल FLOW_ACT_MANGLE_HDR_TYPE_UDP:
		चयन (offset) अणु
		हाल PEDIT_UDP_SPORT_DPORT:
			अगर (!valid_l4_mask(~mask)) अणु
				netdev_err(dev, "%s: Unsupported mask for UDP L4 ports\n",
					   __func__);
				वापस false;
			पूर्ण
			अगर (~mask & PEDIT_TCP_UDP_SPORT_MASK)
				*naपंचांगode_flags |= CXGB4_ACTION_NATMODE_SPORT;
			अन्यथा
				*naपंचांगode_flags |= CXGB4_ACTION_NATMODE_DPORT;
			अवरोध;
		शेष:
			netdev_err(dev, "%s: Unsupported pedit field\n",
				   __func__);
			वापस false;
		पूर्ण
		अवरोध;
	शेष:
		netdev_err(dev, "%s: Unsupported pedit type\n", __func__);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

पूर्णांक cxgb4_validate_flow_actions(काष्ठा net_device *dev,
				काष्ठा flow_action *actions,
				काष्ठा netlink_ext_ack *extack,
				u8 matchall_filter)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा flow_action_entry *act;
	bool act_redir = false;
	bool act_pedit = false;
	bool act_vlan = false;
	u8 naपंचांगode_flags = 0;
	पूर्णांक i;

	अगर (!flow_action_basic_hw_stats_check(actions, extack))
		वापस -EOPNOTSUPP;

	flow_action_क्रम_each(i, act, actions) अणु
		चयन (act->id) अणु
		हाल FLOW_ACTION_ACCEPT:
		हाल FLOW_ACTION_DROP:
			/* Do nothing */
			अवरोध;
		हाल FLOW_ACTION_MIRRED:
		हाल FLOW_ACTION_REसूचीECT: अणु
			काष्ठा net_device *n_dev, *target_dev;
			bool found = false;
			अचिन्हित पूर्णांक i;

			अगर (act->id == FLOW_ACTION_MIRRED &&
			    !matchall_filter) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Egress mirror action is only supported for tc-matchall");
				वापस -EOPNOTSUPP;
			पूर्ण

			target_dev = act->dev;
			क्रम_each_port(adap, i) अणु
				n_dev = adap->port[i];
				अगर (target_dev == n_dev) अणु
					found = true;
					अवरोध;
				पूर्ण
			पूर्ण

			/* If पूर्णांकerface करोesn't beदीर्घ to our hw, then
			 * the provided output port is not valid
			 */
			अगर (!found) अणु
				netdev_err(dev, "%s: Out port invalid\n",
					   __func__);
				वापस -EINVAL;
			पूर्ण
			act_redir = true;
			पूर्ण
			अवरोध;
		हाल FLOW_ACTION_VLAN_POP:
		हाल FLOW_ACTION_VLAN_PUSH:
		हाल FLOW_ACTION_VLAN_MANGLE: अणु
			u16 proto = be16_to_cpu(act->vlan.proto);

			चयन (act->id) अणु
			हाल FLOW_ACTION_VLAN_POP:
				अवरोध;
			हाल FLOW_ACTION_VLAN_PUSH:
			हाल FLOW_ACTION_VLAN_MANGLE:
				अगर (proto != ETH_P_8021Q) अणु
					netdev_err(dev, "%s: Unsupported vlan proto\n",
						   __func__);
					वापस -EOPNOTSUPP;
				पूर्ण
				अवरोध;
			शेष:
				netdev_err(dev, "%s: Unsupported vlan action\n",
					   __func__);
				वापस -EOPNOTSUPP;
			पूर्ण
			act_vlan = true;
			पूर्ण
			अवरोध;
		हाल FLOW_ACTION_MANGLE: अणु
			bool pedit_valid = valid_pedit_action(dev, act,
							      &naपंचांगode_flags);

			अगर (!pedit_valid)
				वापस -EOPNOTSUPP;
			act_pedit = true;
			पूर्ण
			अवरोध;
		हाल FLOW_ACTION_QUEUE:
			/* Do nothing. cxgb4_set_filter will validate */
			अवरोध;
		शेष:
			netdev_err(dev, "%s: Unsupported action\n", __func__);
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	अगर ((act_pedit || act_vlan) && !act_redir) अणु
		netdev_err(dev, "%s: pedit/vlan rewrite invalid without egress redirect\n",
			   __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (act_pedit) अणु
		पूर्णांक ret;

		ret = cxgb4_action_naपंचांगode_validate(adap, naपंचांगode_flags,
						    extack);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cxgb4_tc_flower_hash_prio_add(काष्ठा adapter *adap, u32 tc_prio)
अणु
	spin_lock_bh(&adap->tids.ftid_lock);
	अगर (adap->tids.tc_hash_tids_max_prio < tc_prio)
		adap->tids.tc_hash_tids_max_prio = tc_prio;
	spin_unlock_bh(&adap->tids.ftid_lock);
पूर्ण

अटल व्योम cxgb4_tc_flower_hash_prio_del(काष्ठा adapter *adap, u32 tc_prio)
अणु
	काष्ठा tid_info *t = &adap->tids;
	काष्ठा ch_tc_flower_entry *fe;
	काष्ठा rhashtable_iter iter;
	u32 found = 0;

	spin_lock_bh(&t->ftid_lock);
	/* Bail अगर the current rule is not the one with the max
	 * prio.
	 */
	अगर (t->tc_hash_tids_max_prio != tc_prio)
		जाओ out_unlock;

	/* Search क्रम the next rule having the same or next lower
	 * max prio.
	 */
	rhashtable_walk_enter(&adap->flower_tbl, &iter);
	करो अणु
		rhashtable_walk_start(&iter);

		fe = rhashtable_walk_next(&iter);
		जबतक (!IS_ERR_OR_शून्य(fe)) अणु
			अगर (fe->fs.hash &&
			    fe->fs.tc_prio <= t->tc_hash_tids_max_prio) अणु
				t->tc_hash_tids_max_prio = fe->fs.tc_prio;
				found++;

				/* Bail अगर we found another rule
				 * having the same prio as the
				 * current max one.
				 */
				अगर (fe->fs.tc_prio == tc_prio)
					अवरोध;
			पूर्ण

			fe = rhashtable_walk_next(&iter);
		पूर्ण

		rhashtable_walk_stop(&iter);
	पूर्ण जबतक (fe == ERR_PTR(-EAGAIN));
	rhashtable_walk_निकास(&iter);

	अगर (!found)
		t->tc_hash_tids_max_prio = 0;

out_unlock:
	spin_unlock_bh(&t->ftid_lock);
पूर्ण

पूर्णांक cxgb4_flow_rule_replace(काष्ठा net_device *dev, काष्ठा flow_rule *rule,
			    u32 tc_prio, काष्ठा netlink_ext_ack *extack,
			    काष्ठा ch_filter_specअगरication *fs, u32 *tid)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा filter_ctx ctx;
	u8 inet_family;
	पूर्णांक fidx, ret;

	अगर (cxgb4_validate_flow_actions(dev, &rule->action, extack, 0))
		वापस -EOPNOTSUPP;

	अगर (cxgb4_validate_flow_match(dev, rule))
		वापस -EOPNOTSUPP;

	cxgb4_process_flow_match(dev, rule, fs);
	cxgb4_process_flow_actions(dev, &rule->action, fs);

	fs->hash = is_filter_exact_match(adap, fs);
	inet_family = fs->type ? PF_INET6 : PF_INET;

	/* Get a मुक्त filter entry TID, where we can insert this new
	 * rule. Only insert rule अगर its prio करोesn't conflict with
	 * existing rules.
	 */
	fidx = cxgb4_get_मुक्त_ftid(dev, inet_family, fs->hash,
				   tc_prio);
	अगर (fidx < 0) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "No free LETCAM index available");
		वापस -ENOMEM;
	पूर्ण

	अगर (fidx < adap->tids.nhpftids) अणु
		fs->prio = 1;
		fs->hash = 0;
	पूर्ण

	/* If the rule can be inserted पूर्णांकo HASH region, then ignore
	 * the index to normal FILTER region.
	 */
	अगर (fs->hash)
		fidx = 0;

	fs->tc_prio = tc_prio;

	init_completion(&ctx.completion);
	ret = __cxgb4_set_filter(dev, fidx, fs, &ctx);
	अगर (ret) अणु
		netdev_err(dev, "%s: filter creation err %d\n",
			   __func__, ret);
		वापस ret;
	पूर्ण

	/* Wait क्रम reply */
	ret = रुको_क्रम_completion_समयout(&ctx.completion, 10 * HZ);
	अगर (!ret)
		वापस -ETIMEDOUT;

	/* Check अगर hw वापसed error क्रम filter creation */
	अगर (ctx.result)
		वापस ctx.result;

	*tid = ctx.tid;

	अगर (fs->hash)
		cxgb4_tc_flower_hash_prio_add(adap, tc_prio);

	वापस 0;
पूर्ण

पूर्णांक cxgb4_tc_flower_replace(काष्ठा net_device *dev,
			    काष्ठा flow_cls_offload *cls)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(cls);
	काष्ठा netlink_ext_ack *extack = cls->common.extack;
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा ch_tc_flower_entry *ch_flower;
	काष्ठा ch_filter_specअगरication *fs;
	पूर्णांक ret;

	ch_flower = allocate_flower_entry();
	अगर (!ch_flower) अणु
		netdev_err(dev, "%s: ch_flower alloc failed.\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	fs = &ch_flower->fs;
	fs->hitcnts = 1;
	fs->tc_cookie = cls->cookie;

	ret = cxgb4_flow_rule_replace(dev, rule, cls->common.prio, extack, fs,
				      &ch_flower->filter_id);
	अगर (ret)
		जाओ मुक्त_entry;

	ch_flower->tc_flower_cookie = cls->cookie;
	ret = rhashtable_insert_fast(&adap->flower_tbl, &ch_flower->node,
				     adap->flower_ht_params);
	अगर (ret)
		जाओ del_filter;

	वापस 0;

del_filter:
	अगर (fs->hash)
		cxgb4_tc_flower_hash_prio_del(adap, cls->common.prio);

	cxgb4_del_filter(dev, ch_flower->filter_id, &ch_flower->fs);

मुक्त_entry:
	kमुक्त(ch_flower);
	वापस ret;
पूर्ण

पूर्णांक cxgb4_flow_rule_destroy(काष्ठा net_device *dev, u32 tc_prio,
			    काष्ठा ch_filter_specअगरication *fs, पूर्णांक tid)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);
	u8 hash;
	पूर्णांक ret;

	hash = fs->hash;

	ret = cxgb4_del_filter(dev, tid, fs);
	अगर (ret)
		वापस ret;

	अगर (hash)
		cxgb4_tc_flower_hash_prio_del(adap, tc_prio);

	वापस ret;
पूर्ण

पूर्णांक cxgb4_tc_flower_destroy(काष्ठा net_device *dev,
			    काष्ठा flow_cls_offload *cls)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा ch_tc_flower_entry *ch_flower;
	पूर्णांक ret;

	ch_flower = ch_flower_lookup(adap, cls->cookie);
	अगर (!ch_flower)
		वापस -ENOENT;

	rhashtable_हटाओ_fast(&adap->flower_tbl, &ch_flower->node,
			       adap->flower_ht_params);

	ret = cxgb4_flow_rule_destroy(dev, ch_flower->fs.tc_prio,
				      &ch_flower->fs, ch_flower->filter_id);
	अगर (ret)
		netdev_err(dev, "Flow rule destroy failed for tid: %u, ret: %d",
			   ch_flower->filter_id, ret);

	kमुक्त_rcu(ch_flower, rcu);
	वापस ret;
पूर्ण

अटल व्योम ch_flower_stats_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा adapter *adap = container_of(work, काष्ठा adapter,
					    flower_stats_work);
	काष्ठा ch_tc_flower_entry *flower_entry;
	काष्ठा ch_tc_flower_stats *ofld_stats;
	काष्ठा rhashtable_iter iter;
	u64 packets;
	u64 bytes;
	पूर्णांक ret;

	rhashtable_walk_enter(&adap->flower_tbl, &iter);
	करो अणु
		rhashtable_walk_start(&iter);

		जबतक ((flower_entry = rhashtable_walk_next(&iter)) &&
		       !IS_ERR(flower_entry)) अणु
			ret = cxgb4_get_filter_counters(adap->port[0],
							flower_entry->filter_id,
							&packets, &bytes,
							flower_entry->fs.hash);
			अगर (!ret) अणु
				spin_lock(&flower_entry->lock);
				ofld_stats = &flower_entry->stats;

				अगर (ofld_stats->prev_packet_count != packets) अणु
					ofld_stats->prev_packet_count = packets;
					ofld_stats->last_used = jअगरfies;
				पूर्ण
				spin_unlock(&flower_entry->lock);
			पूर्ण
		पूर्ण

		rhashtable_walk_stop(&iter);

	पूर्ण जबतक (flower_entry == ERR_PTR(-EAGAIN));
	rhashtable_walk_निकास(&iter);
	mod_समयr(&adap->flower_stats_समयr, jअगरfies + STATS_CHECK_PERIOD);
पूर्ण

अटल व्योम ch_flower_stats_cb(काष्ठा समयr_list *t)
अणु
	काष्ठा adapter *adap = from_समयr(adap, t, flower_stats_समयr);

	schedule_work(&adap->flower_stats_work);
पूर्ण

पूर्णांक cxgb4_tc_flower_stats(काष्ठा net_device *dev,
			  काष्ठा flow_cls_offload *cls)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा ch_tc_flower_stats *ofld_stats;
	काष्ठा ch_tc_flower_entry *ch_flower;
	u64 packets;
	u64 bytes;
	पूर्णांक ret;

	ch_flower = ch_flower_lookup(adap, cls->cookie);
	अगर (!ch_flower) अणु
		ret = -ENOENT;
		जाओ err;
	पूर्ण

	ret = cxgb4_get_filter_counters(dev, ch_flower->filter_id,
					&packets, &bytes,
					ch_flower->fs.hash);
	अगर (ret < 0)
		जाओ err;

	spin_lock_bh(&ch_flower->lock);
	ofld_stats = &ch_flower->stats;
	अगर (ofld_stats->packet_count != packets) अणु
		अगर (ofld_stats->prev_packet_count != packets)
			ofld_stats->last_used = jअगरfies;
		flow_stats_update(&cls->stats, bytes - ofld_stats->byte_count,
				  packets - ofld_stats->packet_count, 0,
				  ofld_stats->last_used,
				  FLOW_ACTION_HW_STATS_IMMEDIATE);

		ofld_stats->packet_count = packets;
		ofld_stats->byte_count = bytes;
		ofld_stats->prev_packet_count = packets;
	पूर्ण
	spin_unlock_bh(&ch_flower->lock);
	वापस 0;

err:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rhashtable_params cxgb4_tc_flower_ht_params = अणु
	.nelem_hपूर्णांक = 384,
	.head_offset = दुरत्व(काष्ठा ch_tc_flower_entry, node),
	.key_offset = दुरत्व(काष्ठा ch_tc_flower_entry, tc_flower_cookie),
	.key_len = माप(((काष्ठा ch_tc_flower_entry *)0)->tc_flower_cookie),
	.max_size = 524288,
	.min_size = 512,
	.स्वतःmatic_shrinking = true
पूर्ण;

पूर्णांक cxgb4_init_tc_flower(काष्ठा adapter *adap)
अणु
	पूर्णांक ret;

	अगर (adap->tc_flower_initialized)
		वापस -EEXIST;

	adap->flower_ht_params = cxgb4_tc_flower_ht_params;
	ret = rhashtable_init(&adap->flower_tbl, &adap->flower_ht_params);
	अगर (ret)
		वापस ret;

	INIT_WORK(&adap->flower_stats_work, ch_flower_stats_handler);
	समयr_setup(&adap->flower_stats_समयr, ch_flower_stats_cb, 0);
	mod_समयr(&adap->flower_stats_समयr, jअगरfies + STATS_CHECK_PERIOD);
	adap->tc_flower_initialized = true;
	वापस 0;
पूर्ण

व्योम cxgb4_cleanup_tc_flower(काष्ठा adapter *adap)
अणु
	अगर (!adap->tc_flower_initialized)
		वापस;

	अगर (adap->flower_stats_समयr.function)
		del_समयr_sync(&adap->flower_stats_समयr);
	cancel_work_sync(&adap->flower_stats_work);
	rhashtable_destroy(&adap->flower_tbl);
	adap->tc_flower_initialized = false;
पूर्ण
