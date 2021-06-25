<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HWSIM IEEE 802.15.4 पूर्णांकerface
 *
 * (C) 2018 Mojatau, Alexander Aring <aring@mojatau.com>
 * Copyright 2007-2012 Siemens AG
 *
 * Based on fakelb, original Written by:
 * Sergey Lapin <slapin@ossfans.org>
 * Dmitry Eremin-Solenikov <dbaryshkov@gmail.com>
 * Alexander Smirnov <alex.bluesman.smirnov@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/समयr.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/device.h>
#समावेश <linux/spinlock.h>
#समावेश <net/mac802154.h>
#समावेश <net/cfg802154.h>
#समावेश <net/genetlink.h>
#समावेश "mac802154_hwsim.h"

MODULE_DESCRIPTION("Software simulator of IEEE 802.15.4 radio(s) for mac802154");
MODULE_LICENSE("GPL");

अटल LIST_HEAD(hwsim_phys);
अटल DEFINE_MUTEX(hwsim_phys_lock);

अटल काष्ठा platक्रमm_device *mac802154hwsim_dev;

/* MAC802154_HWSIM netlink family */
अटल काष्ठा genl_family hwsim_genl_family;

अटल पूर्णांक hwsim_radio_idx;

क्रमागत hwsim_multicast_groups अणु
	HWSIM_MCGRP_CONFIG,
पूर्ण;

अटल स्थिर काष्ठा genl_multicast_group hwsim_mcgrps[] = अणु
	[HWSIM_MCGRP_CONFIG] = अणु .name = "config", पूर्ण,
पूर्ण;

काष्ठा hwsim_pib अणु
	u8 page;
	u8 channel;

	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा hwsim_edge_info अणु
	u8 lqi;

	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा hwsim_edge अणु
	काष्ठा hwsim_phy *endpoपूर्णांक;
	काष्ठा hwsim_edge_info __rcu *info;

	काष्ठा list_head list;
	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा hwsim_phy अणु
	काष्ठा ieee802154_hw *hw;
	u32 idx;

	काष्ठा hwsim_pib __rcu *pib;

	bool suspended;
	काष्ठा list_head edges;

	काष्ठा list_head list;
पूर्ण;

अटल पूर्णांक hwsim_add_one(काष्ठा genl_info *info, काष्ठा device *dev,
			 bool init);
अटल व्योम hwsim_del(काष्ठा hwsim_phy *phy);

अटल पूर्णांक hwsim_hw_ed(काष्ठा ieee802154_hw *hw, u8 *level)
अणु
	*level = 0xbe;

	वापस 0;
पूर्ण

अटल पूर्णांक hwsim_hw_channel(काष्ठा ieee802154_hw *hw, u8 page, u8 channel)
अणु
	काष्ठा hwsim_phy *phy = hw->priv;
	काष्ठा hwsim_pib *pib, *pib_old;

	pib = kzalloc(माप(*pib), GFP_KERNEL);
	अगर (!pib)
		वापस -ENOMEM;

	pib->page = page;
	pib->channel = channel;

	pib_old = rtnl_dereference(phy->pib);
	rcu_assign_poपूर्णांकer(phy->pib, pib);
	kमुक्त_rcu(pib_old, rcu);
	वापस 0;
पूर्ण

अटल पूर्णांक hwsim_hw_xmit(काष्ठा ieee802154_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा hwsim_phy *current_phy = hw->priv;
	काष्ठा hwsim_pib *current_pib, *endpoपूर्णांक_pib;
	काष्ठा hwsim_edge_info *einfo;
	काष्ठा hwsim_edge *e;

	WARN_ON(current_phy->suspended);

	rcu_पढ़ो_lock();
	current_pib = rcu_dereference(current_phy->pib);
	list_क्रम_each_entry_rcu(e, &current_phy->edges, list) अणु
		/* Can be changed later in rx_irqsafe, but this is only a
		 * perक्रमmance tweak. Received radio should drop the frame
		 * in mac802154 stack anyway... so we करोn't need to be
		 * 100% of locking here to check on suspended
		 */
		अगर (e->endpoपूर्णांक->suspended)
			जारी;

		endpoपूर्णांक_pib = rcu_dereference(e->endpoपूर्णांक->pib);
		अगर (current_pib->page == endpoपूर्णांक_pib->page &&
		    current_pib->channel == endpoपूर्णांक_pib->channel) अणु
			काष्ठा sk_buff *newskb = pskb_copy(skb, GFP_ATOMIC);

			einfo = rcu_dereference(e->info);
			अगर (newskb)
				ieee802154_rx_irqsafe(e->endpoपूर्णांक->hw, newskb,
						      einfo->lqi);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	ieee802154_xmit_complete(hw, skb, false);
	वापस 0;
पूर्ण

अटल पूर्णांक hwsim_hw_start(काष्ठा ieee802154_hw *hw)
अणु
	काष्ठा hwsim_phy *phy = hw->priv;

	phy->suspended = false;
	वापस 0;
पूर्ण

अटल व्योम hwsim_hw_stop(काष्ठा ieee802154_hw *hw)
अणु
	काष्ठा hwsim_phy *phy = hw->priv;

	phy->suspended = true;
पूर्ण

अटल पूर्णांक
hwsim_set_promiscuous_mode(काष्ठा ieee802154_hw *hw, स्थिर bool on)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ieee802154_ops hwsim_ops = अणु
	.owner = THIS_MODULE,
	.xmit_async = hwsim_hw_xmit,
	.ed = hwsim_hw_ed,
	.set_channel = hwsim_hw_channel,
	.start = hwsim_hw_start,
	.stop = hwsim_hw_stop,
	.set_promiscuous_mode = hwsim_set_promiscuous_mode,
पूर्ण;

अटल पूर्णांक hwsim_new_radio_nl(काष्ठा sk_buff *msg, काष्ठा genl_info *info)
अणु
	वापस hwsim_add_one(info, &mac802154hwsim_dev->dev, false);
पूर्ण

अटल पूर्णांक hwsim_del_radio_nl(काष्ठा sk_buff *msg, काष्ठा genl_info *info)
अणु
	काष्ठा hwsim_phy *phy, *पंचांगp;
	s64 idx = -1;

	अगर (!info->attrs[MAC802154_HWSIM_ATTR_RADIO_ID])
		वापस -EINVAL;

	idx = nla_get_u32(info->attrs[MAC802154_HWSIM_ATTR_RADIO_ID]);

	mutex_lock(&hwsim_phys_lock);
	list_क्रम_each_entry_safe(phy, पंचांगp, &hwsim_phys, list) अणु
		अगर (idx == phy->idx) अणु
			hwsim_del(phy);
			mutex_unlock(&hwsim_phys_lock);
			वापस 0;
		पूर्ण
	पूर्ण
	mutex_unlock(&hwsim_phys_lock);

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक append_radio_msg(काष्ठा sk_buff *skb, काष्ठा hwsim_phy *phy)
अणु
	काष्ठा nlattr *nl_edges, *nl_edge;
	काष्ठा hwsim_edge_info *einfo;
	काष्ठा hwsim_edge *e;
	पूर्णांक ret;

	ret = nla_put_u32(skb, MAC802154_HWSIM_ATTR_RADIO_ID, phy->idx);
	अगर (ret < 0)
		वापस ret;

	rcu_पढ़ो_lock();
	अगर (list_empty(&phy->edges)) अणु
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण

	nl_edges = nla_nest_start_noflag(skb,
					 MAC802154_HWSIM_ATTR_RADIO_EDGES);
	अगर (!nl_edges) अणु
		rcu_पढ़ो_unlock();
		वापस -ENOBUFS;
	पूर्ण

	list_क्रम_each_entry_rcu(e, &phy->edges, list) अणु
		nl_edge = nla_nest_start_noflag(skb,
						MAC802154_HWSIM_ATTR_RADIO_EDGE);
		अगर (!nl_edge) अणु
			rcu_पढ़ो_unlock();
			nla_nest_cancel(skb, nl_edges);
			वापस -ENOBUFS;
		पूर्ण

		ret = nla_put_u32(skb, MAC802154_HWSIM_EDGE_ATTR_ENDPOINT_ID,
				  e->endpoपूर्णांक->idx);
		अगर (ret < 0) अणु
			rcu_पढ़ो_unlock();
			nla_nest_cancel(skb, nl_edge);
			nla_nest_cancel(skb, nl_edges);
			वापस ret;
		पूर्ण

		einfo = rcu_dereference(e->info);
		ret = nla_put_u8(skb, MAC802154_HWSIM_EDGE_ATTR_LQI,
				 einfo->lqi);
		अगर (ret < 0) अणु
			rcu_पढ़ो_unlock();
			nla_nest_cancel(skb, nl_edge);
			nla_nest_cancel(skb, nl_edges);
			वापस ret;
		पूर्ण

		nla_nest_end(skb, nl_edge);
	पूर्ण
	rcu_पढ़ो_unlock();

	nla_nest_end(skb, nl_edges);

	वापस 0;
पूर्ण

अटल पूर्णांक hwsim_get_radio(काष्ठा sk_buff *skb, काष्ठा hwsim_phy *phy,
			   u32 portid, u32 seq,
			   काष्ठा netlink_callback *cb, पूर्णांक flags)
अणु
	व्योम *hdr;
	पूर्णांक res;

	hdr = genlmsg_put(skb, portid, seq, &hwsim_genl_family, flags,
			  MAC802154_HWSIM_CMD_GET_RADIO);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (cb)
		genl_dump_check_consistent(cb, hdr);

	res = append_radio_msg(skb, phy);
	अगर (res < 0)
		जाओ out_err;

	genlmsg_end(skb, hdr);
	वापस 0;

out_err:
	genlmsg_cancel(skb, hdr);
	वापस res;
पूर्ण

अटल पूर्णांक hwsim_get_radio_nl(काष्ठा sk_buff *msg, काष्ठा genl_info *info)
अणु
	काष्ठा hwsim_phy *phy;
	काष्ठा sk_buff *skb;
	पूर्णांक idx, res = -ENODEV;

	अगर (!info->attrs[MAC802154_HWSIM_ATTR_RADIO_ID])
		वापस -EINVAL;
	idx = nla_get_u32(info->attrs[MAC802154_HWSIM_ATTR_RADIO_ID]);

	mutex_lock(&hwsim_phys_lock);
	list_क्रम_each_entry(phy, &hwsim_phys, list) अणु
		अगर (phy->idx != idx)
			जारी;

		skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
		अगर (!skb) अणु
			res = -ENOMEM;
			जाओ out_err;
		पूर्ण

		res = hwsim_get_radio(skb, phy, info->snd_portid,
				      info->snd_seq, शून्य, 0);
		अगर (res < 0) अणु
			nlmsg_मुक्त(skb);
			जाओ out_err;
		पूर्ण

		res = genlmsg_reply(skb, info);
		अवरोध;
	पूर्ण

out_err:
	mutex_unlock(&hwsim_phys_lock);

	वापस res;
पूर्ण

अटल पूर्णांक hwsim_dump_radio_nl(काष्ठा sk_buff *skb,
			       काष्ठा netlink_callback *cb)
अणु
	पूर्णांक idx = cb->args[0];
	काष्ठा hwsim_phy *phy;
	पूर्णांक res;

	mutex_lock(&hwsim_phys_lock);

	अगर (idx == hwsim_radio_idx)
		जाओ करोne;

	list_क्रम_each_entry(phy, &hwsim_phys, list) अणु
		अगर (phy->idx < idx)
			जारी;

		res = hwsim_get_radio(skb, phy, NETLINK_CB(cb->skb).portid,
				      cb->nlh->nlmsg_seq, cb, NLM_F_MULTI);
		अगर (res < 0)
			अवरोध;

		idx = phy->idx + 1;
	पूर्ण

	cb->args[0] = idx;

करोne:
	mutex_unlock(&hwsim_phys_lock);
	वापस skb->len;
पूर्ण

/* caller need to held hwsim_phys_lock */
अटल काष्ठा hwsim_phy *hwsim_get_radio_by_id(uपूर्णांक32_t idx)
अणु
	काष्ठा hwsim_phy *phy;

	list_क्रम_each_entry(phy, &hwsim_phys, list) अणु
		अगर (phy->idx == idx)
			वापस phy;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा nla_policy hwsim_edge_policy[MAC802154_HWSIM_EDGE_ATTR_MAX + 1] = अणु
	[MAC802154_HWSIM_EDGE_ATTR_ENDPOINT_ID] = अणु .type = NLA_U32 पूर्ण,
	[MAC802154_HWSIM_EDGE_ATTR_LQI] = अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल काष्ठा hwsim_edge *hwsim_alloc_edge(काष्ठा hwsim_phy *endpoपूर्णांक, u8 lqi)
अणु
	काष्ठा hwsim_edge_info *einfo;
	काष्ठा hwsim_edge *e;

	e = kzalloc(माप(*e), GFP_KERNEL);
	अगर (!e)
		वापस शून्य;

	einfo = kzalloc(माप(*einfo), GFP_KERNEL);
	अगर (!einfo) अणु
		kमुक्त(e);
		वापस शून्य;
	पूर्ण

	einfo->lqi = 0xff;
	rcu_assign_poपूर्णांकer(e->info, einfo);
	e->endpoपूर्णांक = endpoपूर्णांक;

	वापस e;
पूर्ण

अटल व्योम hwsim_मुक्त_edge(काष्ठा hwsim_edge *e)
अणु
	काष्ठा hwsim_edge_info *einfo;

	rcu_पढ़ो_lock();
	einfo = rcu_dereference(e->info);
	rcu_पढ़ो_unlock();

	kमुक्त_rcu(einfo, rcu);
	kमुक्त_rcu(e, rcu);
पूर्ण

अटल पूर्णांक hwsim_new_edge_nl(काष्ठा sk_buff *msg, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr *edge_attrs[MAC802154_HWSIM_EDGE_ATTR_MAX + 1];
	काष्ठा hwsim_phy *phy_v0, *phy_v1;
	काष्ठा hwsim_edge *e;
	u32 v0, v1;

	अगर (!info->attrs[MAC802154_HWSIM_ATTR_RADIO_ID] &&
	    !info->attrs[MAC802154_HWSIM_ATTR_RADIO_EDGE])
		वापस -EINVAL;

	अगर (nla_parse_nested_deprecated(edge_attrs, MAC802154_HWSIM_EDGE_ATTR_MAX, info->attrs[MAC802154_HWSIM_ATTR_RADIO_EDGE], hwsim_edge_policy, शून्य))
		वापस -EINVAL;

	अगर (!edge_attrs[MAC802154_HWSIM_EDGE_ATTR_ENDPOINT_ID])
		वापस -EINVAL;

	v0 = nla_get_u32(info->attrs[MAC802154_HWSIM_ATTR_RADIO_ID]);
	v1 = nla_get_u32(edge_attrs[MAC802154_HWSIM_EDGE_ATTR_ENDPOINT_ID]);

	अगर (v0 == v1)
		वापस -EINVAL;

	mutex_lock(&hwsim_phys_lock);
	phy_v0 = hwsim_get_radio_by_id(v0);
	अगर (!phy_v0) अणु
		mutex_unlock(&hwsim_phys_lock);
		वापस -ENOENT;
	पूर्ण

	phy_v1 = hwsim_get_radio_by_id(v1);
	अगर (!phy_v1) अणु
		mutex_unlock(&hwsim_phys_lock);
		वापस -ENOENT;
	पूर्ण

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(e, &phy_v0->edges, list) अणु
		अगर (e->endpoपूर्णांक->idx == v1) अणु
			mutex_unlock(&hwsim_phys_lock);
			rcu_पढ़ो_unlock();
			वापस -EEXIST;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	e = hwsim_alloc_edge(phy_v1, 0xff);
	अगर (!e) अणु
		mutex_unlock(&hwsim_phys_lock);
		वापस -ENOMEM;
	पूर्ण
	list_add_rcu(&e->list, &phy_v0->edges);
	/* रुको until changes are करोne under hwsim_phys_lock lock
	 * should prevent of calling this function twice जबतक
	 * edges list has not the changes yet.
	 */
	synchronize_rcu();
	mutex_unlock(&hwsim_phys_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक hwsim_del_edge_nl(काष्ठा sk_buff *msg, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr *edge_attrs[MAC802154_HWSIM_EDGE_ATTR_MAX + 1];
	काष्ठा hwsim_phy *phy_v0;
	काष्ठा hwsim_edge *e;
	u32 v0, v1;

	अगर (!info->attrs[MAC802154_HWSIM_ATTR_RADIO_ID] &&
	    !info->attrs[MAC802154_HWSIM_ATTR_RADIO_EDGE])
		वापस -EINVAL;

	अगर (nla_parse_nested_deprecated(edge_attrs, MAC802154_HWSIM_EDGE_ATTR_MAX, info->attrs[MAC802154_HWSIM_ATTR_RADIO_EDGE], hwsim_edge_policy, शून्य))
		वापस -EINVAL;

	अगर (!edge_attrs[MAC802154_HWSIM_EDGE_ATTR_ENDPOINT_ID])
		वापस -EINVAL;

	v0 = nla_get_u32(info->attrs[MAC802154_HWSIM_ATTR_RADIO_ID]);
	v1 = nla_get_u32(edge_attrs[MAC802154_HWSIM_EDGE_ATTR_ENDPOINT_ID]);

	mutex_lock(&hwsim_phys_lock);
	phy_v0 = hwsim_get_radio_by_id(v0);
	अगर (!phy_v0) अणु
		mutex_unlock(&hwsim_phys_lock);
		वापस -ENOENT;
	पूर्ण

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(e, &phy_v0->edges, list) अणु
		अगर (e->endpoपूर्णांक->idx == v1) अणु
			rcu_पढ़ो_unlock();
			list_del_rcu(&e->list);
			hwsim_मुक्त_edge(e);
			/* same again - रुको until list changes are करोne */
			synchronize_rcu();
			mutex_unlock(&hwsim_phys_lock);
			वापस 0;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	mutex_unlock(&hwsim_phys_lock);

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक hwsim_set_edge_lqi(काष्ठा sk_buff *msg, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr *edge_attrs[MAC802154_HWSIM_EDGE_ATTR_MAX + 1];
	काष्ठा hwsim_edge_info *einfo;
	काष्ठा hwsim_phy *phy_v0;
	काष्ठा hwsim_edge *e;
	u32 v0, v1;
	u8 lqi;

	अगर (!info->attrs[MAC802154_HWSIM_ATTR_RADIO_ID] &&
	    !info->attrs[MAC802154_HWSIM_ATTR_RADIO_EDGE])
		वापस -EINVAL;

	अगर (nla_parse_nested_deprecated(edge_attrs, MAC802154_HWSIM_EDGE_ATTR_MAX, info->attrs[MAC802154_HWSIM_ATTR_RADIO_EDGE], hwsim_edge_policy, शून्य))
		वापस -EINVAL;

	अगर (!edge_attrs[MAC802154_HWSIM_EDGE_ATTR_ENDPOINT_ID] &&
	    !edge_attrs[MAC802154_HWSIM_EDGE_ATTR_LQI])
		वापस -EINVAL;

	v0 = nla_get_u32(info->attrs[MAC802154_HWSIM_ATTR_RADIO_ID]);
	v1 = nla_get_u32(edge_attrs[MAC802154_HWSIM_EDGE_ATTR_ENDPOINT_ID]);
	lqi = nla_get_u8(edge_attrs[MAC802154_HWSIM_EDGE_ATTR_LQI]);

	mutex_lock(&hwsim_phys_lock);
	phy_v0 = hwsim_get_radio_by_id(v0);
	अगर (!phy_v0) अणु
		mutex_unlock(&hwsim_phys_lock);
		वापस -ENOENT;
	पूर्ण

	einfo = kzalloc(माप(*einfo), GFP_KERNEL);
	अगर (!einfo) अणु
		mutex_unlock(&hwsim_phys_lock);
		वापस -ENOMEM;
	पूर्ण

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(e, &phy_v0->edges, list) अणु
		अगर (e->endpoपूर्णांक->idx == v1) अणु
			einfo->lqi = lqi;
			rcu_assign_poपूर्णांकer(e->info, einfo);
			rcu_पढ़ो_unlock();
			mutex_unlock(&hwsim_phys_lock);
			वापस 0;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	kमुक्त(einfo);
	mutex_unlock(&hwsim_phys_lock);

	वापस -ENOENT;
पूर्ण

/* MAC802154_HWSIM netlink policy */

अटल स्थिर काष्ठा nla_policy hwsim_genl_policy[MAC802154_HWSIM_ATTR_MAX + 1] = अणु
	[MAC802154_HWSIM_ATTR_RADIO_ID] = अणु .type = NLA_U32 पूर्ण,
	[MAC802154_HWSIM_ATTR_RADIO_EDGE] = अणु .type = NLA_NESTED पूर्ण,
	[MAC802154_HWSIM_ATTR_RADIO_EDGES] = अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

/* Generic Netlink operations array */
अटल स्थिर काष्ठा genl_small_ops hwsim_nl_ops[] = अणु
	अणु
		.cmd = MAC802154_HWSIM_CMD_NEW_RADIO,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = hwsim_new_radio_nl,
		.flags = GENL_UNS_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = MAC802154_HWSIM_CMD_DEL_RADIO,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = hwsim_del_radio_nl,
		.flags = GENL_UNS_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = MAC802154_HWSIM_CMD_GET_RADIO,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = hwsim_get_radio_nl,
		.dumpit = hwsim_dump_radio_nl,
	पूर्ण,
	अणु
		.cmd = MAC802154_HWSIM_CMD_NEW_EDGE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = hwsim_new_edge_nl,
		.flags = GENL_UNS_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = MAC802154_HWSIM_CMD_DEL_EDGE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = hwsim_del_edge_nl,
		.flags = GENL_UNS_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = MAC802154_HWSIM_CMD_SET_EDGE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = hwsim_set_edge_lqi,
		.flags = GENL_UNS_ADMIN_PERM,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family hwsim_genl_family __ro_after_init = अणु
	.name = "MAC802154_HWSIM",
	.version = 1,
	.maxattr = MAC802154_HWSIM_ATTR_MAX,
	.policy = hwsim_genl_policy,
	.module = THIS_MODULE,
	.small_ops = hwsim_nl_ops,
	.n_small_ops = ARRAY_SIZE(hwsim_nl_ops),
	.mcgrps = hwsim_mcgrps,
	.n_mcgrps = ARRAY_SIZE(hwsim_mcgrps),
पूर्ण;

अटल व्योम hwsim_mcast_config_msg(काष्ठा sk_buff *mcast_skb,
				   काष्ठा genl_info *info)
अणु
	अगर (info)
		genl_notअगरy(&hwsim_genl_family, mcast_skb, info,
			    HWSIM_MCGRP_CONFIG, GFP_KERNEL);
	अन्यथा
		genlmsg_multicast(&hwsim_genl_family, mcast_skb, 0,
				  HWSIM_MCGRP_CONFIG, GFP_KERNEL);
पूर्ण

अटल व्योम hwsim_mcast_new_radio(काष्ठा genl_info *info, काष्ठा hwsim_phy *phy)
अणु
	काष्ठा sk_buff *mcast_skb;
	व्योम *data;

	mcast_skb = genlmsg_new(GENLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!mcast_skb)
		वापस;

	data = genlmsg_put(mcast_skb, 0, 0, &hwsim_genl_family, 0,
			   MAC802154_HWSIM_CMD_NEW_RADIO);
	अगर (!data)
		जाओ out_err;

	अगर (append_radio_msg(mcast_skb, phy) < 0)
		जाओ out_err;

	genlmsg_end(mcast_skb, data);

	hwsim_mcast_config_msg(mcast_skb, info);
	वापस;

out_err:
	genlmsg_cancel(mcast_skb, data);
	nlmsg_मुक्त(mcast_skb);
पूर्ण

अटल व्योम hwsim_edge_unsubscribe_me(काष्ठा hwsim_phy *phy)
अणु
	काष्ठा hwsim_phy *पंचांगp;
	काष्ठा hwsim_edge *e;

	rcu_पढ़ो_lock();
	/* going to all phy edges and हटाओ phy from it */
	list_क्रम_each_entry(पंचांगp, &hwsim_phys, list) अणु
		list_क्रम_each_entry_rcu(e, &पंचांगp->edges, list) अणु
			अगर (e->endpoपूर्णांक->idx == phy->idx) अणु
				list_del_rcu(&e->list);
				hwsim_मुक्त_edge(e);
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	synchronize_rcu();
पूर्ण

अटल पूर्णांक hwsim_subscribe_all_others(काष्ठा hwsim_phy *phy)
अणु
	काष्ठा hwsim_phy *sub;
	काष्ठा hwsim_edge *e;

	list_क्रम_each_entry(sub, &hwsim_phys, list) अणु
		e = hwsim_alloc_edge(sub, 0xff);
		अगर (!e)
			जाओ me_fail;

		list_add_rcu(&e->list, &phy->edges);
	पूर्ण

	list_क्रम_each_entry(sub, &hwsim_phys, list) अणु
		e = hwsim_alloc_edge(phy, 0xff);
		अगर (!e)
			जाओ sub_fail;

		list_add_rcu(&e->list, &sub->edges);
	पूर्ण

	वापस 0;

me_fail:
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(e, &phy->edges, list) अणु
		list_del_rcu(&e->list);
		hwsim_मुक्त_edge(e);
	पूर्ण
	rcu_पढ़ो_unlock();
sub_fail:
	hwsim_edge_unsubscribe_me(phy);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक hwsim_add_one(काष्ठा genl_info *info, काष्ठा device *dev,
			 bool init)
अणु
	काष्ठा ieee802154_hw *hw;
	काष्ठा hwsim_phy *phy;
	काष्ठा hwsim_pib *pib;
	पूर्णांक idx;
	पूर्णांक err;

	idx = hwsim_radio_idx++;

	hw = ieee802154_alloc_hw(माप(*phy), &hwsim_ops);
	अगर (!hw)
		वापस -ENOMEM;

	phy = hw->priv;
	phy->hw = hw;

	/* 868 MHz BPSK	802.15.4-2003 */
	hw->phy->supported.channels[0] |= 1;
	/* 915 MHz BPSK	802.15.4-2003 */
	hw->phy->supported.channels[0] |= 0x7fe;
	/* 2.4 GHz O-QPSK 802.15.4-2003 */
	hw->phy->supported.channels[0] |= 0x7FFF800;
	/* 868 MHz ASK 802.15.4-2006 */
	hw->phy->supported.channels[1] |= 1;
	/* 915 MHz ASK 802.15.4-2006 */
	hw->phy->supported.channels[1] |= 0x7fe;
	/* 868 MHz O-QPSK 802.15.4-2006 */
	hw->phy->supported.channels[2] |= 1;
	/* 915 MHz O-QPSK 802.15.4-2006 */
	hw->phy->supported.channels[2] |= 0x7fe;
	/* 2.4 GHz CSS 802.15.4a-2007 */
	hw->phy->supported.channels[3] |= 0x3fff;
	/* UWB Sub-gigahertz 802.15.4a-2007 */
	hw->phy->supported.channels[4] |= 1;
	/* UWB Low band 802.15.4a-2007 */
	hw->phy->supported.channels[4] |= 0x1e;
	/* UWB High band 802.15.4a-2007 */
	hw->phy->supported.channels[4] |= 0xffe0;
	/* 750 MHz O-QPSK 802.15.4c-2009 */
	hw->phy->supported.channels[5] |= 0xf;
	/* 750 MHz MPSK 802.15.4c-2009 */
	hw->phy->supported.channels[5] |= 0xf0;
	/* 950 MHz BPSK 802.15.4d-2009 */
	hw->phy->supported.channels[6] |= 0x3ff;
	/* 950 MHz GFSK 802.15.4d-2009 */
	hw->phy->supported.channels[6] |= 0x3ffc00;

	ieee802154_अक्रमom_extended_addr(&hw->phy->perm_extended_addr);

	/* hwsim phy channel 13 as शेष */
	hw->phy->current_channel = 13;
	pib = kzalloc(माप(*pib), GFP_KERNEL);
	अगर (!pib) अणु
		err = -ENOMEM;
		जाओ err_pib;
	पूर्ण

	rcu_assign_poपूर्णांकer(phy->pib, pib);
	phy->idx = idx;
	INIT_LIST_HEAD(&phy->edges);

	hw->flags = IEEE802154_HW_PROMISCUOUS;
	hw->parent = dev;

	err = ieee802154_रेजिस्टर_hw(hw);
	अगर (err)
		जाओ err_reg;

	mutex_lock(&hwsim_phys_lock);
	अगर (init) अणु
		err = hwsim_subscribe_all_others(phy);
		अगर (err < 0) अणु
			mutex_unlock(&hwsim_phys_lock);
			जाओ err_subscribe;
		पूर्ण
	पूर्ण
	list_add_tail(&phy->list, &hwsim_phys);
	mutex_unlock(&hwsim_phys_lock);

	hwsim_mcast_new_radio(info, phy);

	वापस idx;

err_subscribe:
	ieee802154_unरेजिस्टर_hw(phy->hw);
err_reg:
	kमुक्त(pib);
err_pib:
	ieee802154_मुक्त_hw(phy->hw);
	वापस err;
पूर्ण

अटल व्योम hwsim_del(काष्ठा hwsim_phy *phy)
अणु
	काष्ठा hwsim_pib *pib;

	hwsim_edge_unsubscribe_me(phy);

	list_del(&phy->list);

	rcu_पढ़ो_lock();
	pib = rcu_dereference(phy->pib);
	rcu_पढ़ो_unlock();

	kमुक्त_rcu(pib, rcu);

	ieee802154_unरेजिस्टर_hw(phy->hw);
	ieee802154_मुक्त_hw(phy->hw);
पूर्ण

अटल पूर्णांक hwsim_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hwsim_phy *phy, *पंचांगp;
	पूर्णांक err, i;

	क्रम (i = 0; i < 2; i++) अणु
		err = hwsim_add_one(शून्य, &pdev->dev, true);
		अगर (err < 0)
			जाओ err_slave;
	पूर्ण

	dev_info(&pdev->dev, "Added 2 mac802154 hwsim hardware radios\n");
	वापस 0;

err_slave:
	mutex_lock(&hwsim_phys_lock);
	list_क्रम_each_entry_safe(phy, पंचांगp, &hwsim_phys, list)
		hwsim_del(phy);
	mutex_unlock(&hwsim_phys_lock);
	वापस err;
पूर्ण

अटल पूर्णांक hwsim_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hwsim_phy *phy, *पंचांगp;

	mutex_lock(&hwsim_phys_lock);
	list_क्रम_each_entry_safe(phy, पंचांगp, &hwsim_phys, list)
		hwsim_del(phy);
	mutex_unlock(&hwsim_phys_lock);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mac802154hwsim_driver = अणु
	.probe = hwsim_probe,
	.हटाओ = hwsim_हटाओ,
	.driver = अणु
			.name = "mac802154_hwsim",
	पूर्ण,
पूर्ण;

अटल __init पूर्णांक hwsim_init_module(व्योम)
अणु
	पूर्णांक rc;

	rc = genl_रेजिस्टर_family(&hwsim_genl_family);
	अगर (rc)
		वापस rc;

	mac802154hwsim_dev = platक्रमm_device_रेजिस्टर_simple("mac802154_hwsim",
							     -1, शून्य, 0);
	अगर (IS_ERR(mac802154hwsim_dev)) अणु
		rc = PTR_ERR(mac802154hwsim_dev);
		जाओ platक्रमm_dev;
	पूर्ण

	rc = platक्रमm_driver_रेजिस्टर(&mac802154hwsim_driver);
	अगर (rc < 0)
		जाओ platक्रमm_drv;

	वापस 0;

platक्रमm_drv:
	platक्रमm_device_unरेजिस्टर(mac802154hwsim_dev);
platक्रमm_dev:
	genl_unरेजिस्टर_family(&hwsim_genl_family);
	वापस rc;
पूर्ण

अटल __निकास व्योम hwsim_हटाओ_module(व्योम)
अणु
	genl_unरेजिस्टर_family(&hwsim_genl_family);
	platक्रमm_driver_unरेजिस्टर(&mac802154hwsim_driver);
	platक्रमm_device_unरेजिस्टर(mac802154hwsim_dev);
पूर्ण

module_init(hwsim_init_module);
module_निकास(hwsim_हटाओ_module);
