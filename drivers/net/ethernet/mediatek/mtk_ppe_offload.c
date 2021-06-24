<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2020 Felix Fietkau <nbd@nbd.name>
 */

#समावेश <linux/अगर_ether.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/ip.h>
#समावेश <net/flow_offload.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/dsa.h>
#समावेश "mtk_eth_soc.h"

काष्ठा mtk_flow_data अणु
	काष्ठा ethhdr eth;

	जोड़ अणु
		काष्ठा अणु
			__be32 src_addr;
			__be32 dst_addr;
		पूर्ण v4;
	पूर्ण;

	__be16 src_port;
	__be16 dst_port;

	काष्ठा अणु
		u16 id;
		__be16 proto;
		u8 num;
	पूर्ण vlan;
	काष्ठा अणु
		u16 sid;
		u8 num;
	पूर्ण pppoe;
पूर्ण;

काष्ठा mtk_flow_entry अणु
	काष्ठा rhash_head node;
	अचिन्हित दीर्घ cookie;
	u16 hash;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params mtk_flow_ht_params = अणु
	.head_offset = दुरत्व(काष्ठा mtk_flow_entry, node),
	.key_offset = दुरत्व(काष्ठा mtk_flow_entry, cookie),
	.key_len = माप(अचिन्हित दीर्घ),
	.स्वतःmatic_shrinking = true,
पूर्ण;

अटल u32
mtk_eth_बारtamp(काष्ठा mtk_eth *eth)
अणु
	वापस mtk_r32(eth, 0x0010) & MTK_FOE_IB1_BIND_TIMESTAMP;
पूर्ण

अटल पूर्णांक
mtk_flow_set_ipv4_addr(काष्ठा mtk_foe_entry *foe, काष्ठा mtk_flow_data *data,
		       bool egress)
अणु
	वापस mtk_foe_entry_set_ipv4_tuple(foe, egress,
					    data->v4.src_addr, data->src_port,
					    data->v4.dst_addr, data->dst_port);
पूर्ण

अटल व्योम
mtk_flow_offload_mangle_eth(स्थिर काष्ठा flow_action_entry *act, व्योम *eth)
अणु
	व्योम *dest = eth + act->mangle.offset;
	स्थिर व्योम *src = &act->mangle.val;

	अगर (act->mangle.offset > 8)
		वापस;

	अगर (act->mangle.mask == 0xffff) अणु
		src += 2;
		dest += 2;
	पूर्ण

	स_नकल(dest, src, act->mangle.mask ? 2 : 4);
पूर्ण


अटल पूर्णांक
mtk_flow_mangle_ports(स्थिर काष्ठा flow_action_entry *act,
		      काष्ठा mtk_flow_data *data)
अणु
	u32 val = ntohl(act->mangle.val);

	चयन (act->mangle.offset) अणु
	हाल 0:
		अगर (act->mangle.mask == ~htonl(0xffff))
			data->dst_port = cpu_to_be16(val);
		अन्यथा
			data->src_port = cpu_to_be16(val >> 16);
		अवरोध;
	हाल 2:
		data->dst_port = cpu_to_be16(val);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mtk_flow_mangle_ipv4(स्थिर काष्ठा flow_action_entry *act,
		     काष्ठा mtk_flow_data *data)
अणु
	__be32 *dest;

	चयन (act->mangle.offset) अणु
	हाल दुरत्व(काष्ठा iphdr, saddr):
		dest = &data->v4.src_addr;
		अवरोध;
	हाल दुरत्व(काष्ठा iphdr, daddr):
		dest = &data->v4.dst_addr;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	स_नकल(dest, &act->mangle.val, माप(u32));

	वापस 0;
पूर्ण

अटल पूर्णांक
mtk_flow_get_dsa_port(काष्ठा net_device **dev)
अणु
#अगर IS_ENABLED(CONFIG_NET_DSA)
	काष्ठा dsa_port *dp;

	dp = dsa_port_from_netdev(*dev);
	अगर (IS_ERR(dp))
		वापस -ENODEV;

	अगर (dp->cpu_dp->tag_ops->proto != DSA_TAG_PROTO_MTK)
		वापस -ENODEV;

	*dev = dp->cpu_dp->master;

	वापस dp->index;
#अन्यथा
	वापस -ENODEV;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक
mtk_flow_set_output_device(काष्ठा mtk_eth *eth, काष्ठा mtk_foe_entry *foe,
			   काष्ठा net_device *dev)
अणु
	पूर्णांक pse_port, dsa_port;

	dsa_port = mtk_flow_get_dsa_port(&dev);
	अगर (dsa_port >= 0)
		mtk_foe_entry_set_dsa(foe, dsa_port);

	अगर (dev == eth->netdev[0])
		pse_port = 1;
	अन्यथा अगर (dev == eth->netdev[1])
		pse_port = 2;
	अन्यथा
		वापस -EOPNOTSUPP;

	mtk_foe_entry_set_pse_port(foe, pse_port);

	वापस 0;
पूर्ण

अटल पूर्णांक
mtk_flow_offload_replace(काष्ठा mtk_eth *eth, काष्ठा flow_cls_offload *f)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा flow_action_entry *act;
	काष्ठा mtk_flow_data data = अणुपूर्ण;
	काष्ठा mtk_foe_entry foe;
	काष्ठा net_device *odev = शून्य;
	काष्ठा mtk_flow_entry *entry;
	पूर्णांक offload_type = 0;
	u16 addr_type = 0;
	u32 बारtamp;
	u8 l4proto = 0;
	पूर्णांक err = 0;
	पूर्णांक hash;
	पूर्णांक i;

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_META)) अणु
		काष्ठा flow_match_meta match;

		flow_rule_match_meta(rule, &match);
	पूर्ण अन्यथा अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_CONTROL)) अणु
		काष्ठा flow_match_control match;

		flow_rule_match_control(rule, &match);
		addr_type = match.key->addr_type;
	पूर्ण अन्यथा अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) अणु
		काष्ठा flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		l4proto = match.key->ip_proto;
	पूर्ण अन्यथा अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	flow_action_क्रम_each(i, act, &rule->action) अणु
		चयन (act->id) अणु
		हाल FLOW_ACTION_MANGLE:
			अगर (act->mangle.htype == FLOW_ACT_MANGLE_HDR_TYPE_ETH)
				mtk_flow_offload_mangle_eth(act, &data.eth);
			अवरोध;
		हाल FLOW_ACTION_REसूचीECT:
			odev = act->dev;
			अवरोध;
		हाल FLOW_ACTION_CSUM:
			अवरोध;
		हाल FLOW_ACTION_VLAN_PUSH:
			अगर (data.vlan.num == 1 ||
			    act->vlan.proto != htons(ETH_P_8021Q))
				वापस -EOPNOTSUPP;

			data.vlan.id = act->vlan.vid;
			data.vlan.proto = act->vlan.proto;
			data.vlan.num++;
			अवरोध;
		हाल FLOW_ACTION_VLAN_POP:
			अवरोध;
		हाल FLOW_ACTION_PPPOE_PUSH:
			अगर (data.pppoe.num == 1)
				वापस -EOPNOTSUPP;

			data.pppoe.sid = act->pppoe.sid;
			data.pppoe.num++;
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	चयन (addr_type) अणु
	हाल FLOW_DISSECTOR_KEY_IPV4_ADDRS:
		offload_type = MTK_PPE_PKT_TYPE_IPV4_HNAPT;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!is_valid_ether_addr(data.eth.h_source) ||
	    !is_valid_ether_addr(data.eth.h_dest))
		वापस -EINVAL;

	err = mtk_foe_entry_prepare(&foe, offload_type, l4proto, 0,
				    data.eth.h_source,
				    data.eth.h_dest);
	अगर (err)
		वापस err;

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS)) अणु
		काष्ठा flow_match_ports ports;

		flow_rule_match_ports(rule, &ports);
		data.src_port = ports.key->src;
		data.dst_port = ports.key->dst;
	पूर्ण अन्यथा अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS) अणु
		काष्ठा flow_match_ipv4_addrs addrs;

		flow_rule_match_ipv4_addrs(rule, &addrs);

		data.v4.src_addr = addrs.key->src;
		data.v4.dst_addr = addrs.key->dst;

		mtk_flow_set_ipv4_addr(&foe, &data, false);
	पूर्ण

	flow_action_क्रम_each(i, act, &rule->action) अणु
		अगर (act->id != FLOW_ACTION_MANGLE)
			जारी;

		चयन (act->mangle.htype) अणु
		हाल FLOW_ACT_MANGLE_HDR_TYPE_TCP:
		हाल FLOW_ACT_MANGLE_HDR_TYPE_UDP:
			err = mtk_flow_mangle_ports(act, &data);
			अवरोध;
		हाल FLOW_ACT_MANGLE_HDR_TYPE_IP4:
			err = mtk_flow_mangle_ipv4(act, &data);
			अवरोध;
		हाल FLOW_ACT_MANGLE_HDR_TYPE_ETH:
			/* handled earlier */
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (err)
			वापस err;
	पूर्ण

	अगर (addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS) अणु
		err = mtk_flow_set_ipv4_addr(&foe, &data, true);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data.vlan.num == 1) अणु
		अगर (data.vlan.proto != htons(ETH_P_8021Q))
			वापस -EOPNOTSUPP;

		mtk_foe_entry_set_vlan(&foe, data.vlan.id);
	पूर्ण
	अगर (data.pppoe.num == 1)
		mtk_foe_entry_set_pppoe(&foe, data.pppoe.sid);

	err = mtk_flow_set_output_device(eth, &foe, odev);
	अगर (err)
		वापस err;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	entry->cookie = f->cookie;
	बारtamp = mtk_eth_बारtamp(eth);
	hash = mtk_foe_entry_commit(&eth->ppe, &foe, बारtamp);
	अगर (hash < 0) अणु
		err = hash;
		जाओ मुक्त;
	पूर्ण

	entry->hash = hash;
	err = rhashtable_insert_fast(&eth->flow_table, &entry->node,
				     mtk_flow_ht_params);
	अगर (err < 0)
		जाओ clear_flow;

	वापस 0;
clear_flow:
	mtk_foe_entry_clear(&eth->ppe, hash);
मुक्त:
	kमुक्त(entry);
	वापस err;
पूर्ण

अटल पूर्णांक
mtk_flow_offload_destroy(काष्ठा mtk_eth *eth, काष्ठा flow_cls_offload *f)
अणु
	काष्ठा mtk_flow_entry *entry;

	entry = rhashtable_lookup(&eth->flow_table, &f->cookie,
				  mtk_flow_ht_params);
	अगर (!entry)
		वापस -ENOENT;

	mtk_foe_entry_clear(&eth->ppe, entry->hash);
	rhashtable_हटाओ_fast(&eth->flow_table, &entry->node,
			       mtk_flow_ht_params);
	kमुक्त(entry);

	वापस 0;
पूर्ण

अटल पूर्णांक
mtk_flow_offload_stats(काष्ठा mtk_eth *eth, काष्ठा flow_cls_offload *f)
अणु
	काष्ठा mtk_flow_entry *entry;
	पूर्णांक बारtamp;
	u32 idle;

	entry = rhashtable_lookup(&eth->flow_table, &f->cookie,
				  mtk_flow_ht_params);
	अगर (!entry)
		वापस -ENOENT;

	बारtamp = mtk_foe_entry_बारtamp(&eth->ppe, entry->hash);
	अगर (बारtamp < 0)
		वापस -ETIMEDOUT;

	idle = mtk_eth_बारtamp(eth) - बारtamp;
	f->stats.lastused = jअगरfies - idle * HZ;

	वापस 0;
पूर्ण

अटल DEFINE_MUTEX(mtk_flow_offload_mutex);

अटल पूर्णांक
mtk_eth_setup_tc_block_cb(क्रमागत tc_setup_type type, व्योम *type_data, व्योम *cb_priv)
अणु
	काष्ठा flow_cls_offload *cls = type_data;
	काष्ठा net_device *dev = cb_priv;
	काष्ठा mtk_mac *mac = netdev_priv(dev);
	काष्ठा mtk_eth *eth = mac->hw;
	पूर्णांक err;

	अगर (!tc_can_offload(dev))
		वापस -EOPNOTSUPP;

	अगर (type != TC_SETUP_CLSFLOWER)
		वापस -EOPNOTSUPP;

	mutex_lock(&mtk_flow_offload_mutex);
	चयन (cls->command) अणु
	हाल FLOW_CLS_REPLACE:
		err = mtk_flow_offload_replace(eth, cls);
		अवरोध;
	हाल FLOW_CLS_DESTROY:
		err = mtk_flow_offload_destroy(eth, cls);
		अवरोध;
	हाल FLOW_CLS_STATS:
		err = mtk_flow_offload_stats(eth, cls);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	mutex_unlock(&mtk_flow_offload_mutex);

	वापस err;
पूर्ण

अटल पूर्णांक
mtk_eth_setup_tc_block(काष्ठा net_device *dev, काष्ठा flow_block_offload *f)
अणु
	काष्ठा mtk_mac *mac = netdev_priv(dev);
	काष्ठा mtk_eth *eth = mac->hw;
	अटल LIST_HEAD(block_cb_list);
	काष्ठा flow_block_cb *block_cb;
	flow_setup_cb_t *cb;

	अगर (!eth->ppe.foe_table)
		वापस -EOPNOTSUPP;

	अगर (f->binder_type != FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS)
		वापस -EOPNOTSUPP;

	cb = mtk_eth_setup_tc_block_cb;
	f->driver_block_list = &block_cb_list;

	चयन (f->command) अणु
	हाल FLOW_BLOCK_BIND:
		block_cb = flow_block_cb_lookup(f->block, cb, dev);
		अगर (block_cb) अणु
			flow_block_cb_incref(block_cb);
			वापस 0;
		पूर्ण
		block_cb = flow_block_cb_alloc(cb, dev, dev, शून्य);
		अगर (IS_ERR(block_cb))
			वापस PTR_ERR(block_cb);

		flow_block_cb_add(block_cb, f);
		list_add_tail(&block_cb->driver_list, &block_cb_list);
		वापस 0;
	हाल FLOW_BLOCK_UNBIND:
		block_cb = flow_block_cb_lookup(f->block, cb, dev);
		अगर (!block_cb)
			वापस -ENOENT;

		अगर (flow_block_cb_decref(block_cb)) अणु
			flow_block_cb_हटाओ(block_cb, f);
			list_del(&block_cb->driver_list);
		पूर्ण
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

पूर्णांक mtk_eth_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
		     व्योम *type_data)
अणु
	अगर (type == TC_SETUP_FT)
		वापस mtk_eth_setup_tc_block(dev, type_data);

	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक mtk_eth_offload_init(काष्ठा mtk_eth *eth)
अणु
	अगर (!eth->ppe.foe_table)
		वापस 0;

	वापस rhashtable_init(&eth->flow_table, &mtk_flow_ht_params);
पूर्ण
