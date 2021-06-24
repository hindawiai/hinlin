<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/net/bond/bond_netlink.c - Netlink पूर्णांकerface क्रम bonding
 * Copyright (c) 2013 Jiri Pirko <jiri@resnulli.us>
 * Copyright (c) 2013 Scott Feldman <sfeldma@cumulusnetworks.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_link.h>
#समावेश <linux/अगर_ether.h>
#समावेश <net/netlink.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/bonding.h>

अटल माप_प्रकार bond_get_slave_size(स्थिर काष्ठा net_device *bond_dev,
				  स्थिर काष्ठा net_device *slave_dev)
अणु
	वापस nla_total_size(माप(u8)) +	/* IFLA_BOND_SLAVE_STATE */
		nla_total_size(माप(u8)) +	/* IFLA_BOND_SLAVE_MII_STATUS */
		nla_total_size(माप(u32)) +	/* IFLA_BOND_SLAVE_LINK_FAILURE_COUNT */
		nla_total_size(MAX_ADDR_LEN) +	/* IFLA_BOND_SLAVE_PERM_HWADDR */
		nla_total_size(माप(u16)) +	/* IFLA_BOND_SLAVE_QUEUE_ID */
		nla_total_size(माप(u16)) +	/* IFLA_BOND_SLAVE_AD_AGGREGATOR_ID */
		nla_total_size(माप(u8)) +	/* IFLA_BOND_SLAVE_AD_ACTOR_OPER_PORT_STATE */
		nla_total_size(माप(u16)) +	/* IFLA_BOND_SLAVE_AD_PARTNER_OPER_PORT_STATE */
		0;
पूर्ण

अटल पूर्णांक bond_fill_slave_info(काष्ठा sk_buff *skb,
				स्थिर काष्ठा net_device *bond_dev,
				स्थिर काष्ठा net_device *slave_dev)
अणु
	काष्ठा slave *slave = bond_slave_get_rtnl(slave_dev);

	अगर (nla_put_u8(skb, IFLA_BOND_SLAVE_STATE, bond_slave_state(slave)))
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, IFLA_BOND_SLAVE_MII_STATUS, slave->link))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, IFLA_BOND_SLAVE_LINK_FAILURE_COUNT,
			slave->link_failure_count))
		जाओ nla_put_failure;

	अगर (nla_put(skb, IFLA_BOND_SLAVE_PERM_HWADDR,
		    slave_dev->addr_len, slave->perm_hwaddr))
		जाओ nla_put_failure;

	अगर (nla_put_u16(skb, IFLA_BOND_SLAVE_QUEUE_ID, slave->queue_id))
		जाओ nla_put_failure;

	अगर (BOND_MODE(slave->bond) == BOND_MODE_8023AD) अणु
		स्थिर काष्ठा aggregator *agg;
		स्थिर काष्ठा port *ad_port;

		ad_port = &SLAVE_AD_INFO(slave)->port;
		agg = SLAVE_AD_INFO(slave)->port.aggregator;
		अगर (agg) अणु
			अगर (nla_put_u16(skb, IFLA_BOND_SLAVE_AD_AGGREGATOR_ID,
					agg->aggregator_identअगरier))
				जाओ nla_put_failure;
			अगर (nla_put_u8(skb,
				       IFLA_BOND_SLAVE_AD_ACTOR_OPER_PORT_STATE,
				       ad_port->actor_oper_port_state))
				जाओ nla_put_failure;
			अगर (nla_put_u16(skb,
					IFLA_BOND_SLAVE_AD_PARTNER_OPER_PORT_STATE,
					ad_port->partner_oper.port_state))
				जाओ nla_put_failure;
		पूर्ण
	पूर्ण

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल स्थिर काष्ठा nla_policy bond_policy[IFLA_BOND_MAX + 1] = अणु
	[IFLA_BOND_MODE]		= अणु .type = NLA_U8 पूर्ण,
	[IFLA_BOND_ACTIVE_SLAVE]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BOND_MIIMON]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BOND_UPDELAY]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BOND_DOWNDELAY]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BOND_USE_CARRIER]		= अणु .type = NLA_U8 पूर्ण,
	[IFLA_BOND_ARP_INTERVAL]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BOND_ARP_IP_TARGET]	= अणु .type = NLA_NESTED पूर्ण,
	[IFLA_BOND_ARP_VALIDATE]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BOND_ARP_ALL_TARGETS]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BOND_PRIMARY]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BOND_PRIMARY_RESELECT]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_BOND_FAIL_OVER_MAC]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_BOND_XMIT_HASH_POLICY]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_BOND_RESEND_IGMP]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BOND_NUM_PEER_NOTIF]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_BOND_ALL_SLAVES_ACTIVE]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_BOND_MIN_LINKS]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BOND_LP_INTERVAL]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BOND_PACKETS_PER_SLAVE]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BOND_AD_LACP_RATE]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_BOND_AD_SELECT]		= अणु .type = NLA_U8 पूर्ण,
	[IFLA_BOND_AD_INFO]		= अणु .type = NLA_NESTED पूर्ण,
	[IFLA_BOND_AD_ACTOR_SYS_PRIO]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_BOND_AD_USER_PORT_KEY]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_BOND_AD_ACTOR_SYSTEM]	= अणु .type = NLA_BINARY,
					    .len  = ETH_ALEN पूर्ण,
	[IFLA_BOND_TLB_DYNAMIC_LB]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_BOND_PEER_NOTIF_DELAY]    = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy bond_slave_policy[IFLA_BOND_SLAVE_MAX + 1] = अणु
	[IFLA_BOND_SLAVE_QUEUE_ID]	= अणु .type = NLA_U16 पूर्ण,
पूर्ण;

अटल पूर्णांक bond_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			 काष्ठा netlink_ext_ack *extack)
अणु
	अगर (tb[IFLA_ADDRESS]) अणु
		अगर (nla_len(tb[IFLA_ADDRESS]) != ETH_ALEN)
			वापस -EINVAL;
		अगर (!is_valid_ether_addr(nla_data(tb[IFLA_ADDRESS])))
			वापस -EADDRNOTAVAIL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bond_slave_changelink(काष्ठा net_device *bond_dev,
				 काष्ठा net_device *slave_dev,
				 काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा bond_opt_value newval;
	पूर्णांक err;

	अगर (!data)
		वापस 0;

	अगर (data[IFLA_BOND_SLAVE_QUEUE_ID]) अणु
		u16 queue_id = nla_get_u16(data[IFLA_BOND_SLAVE_QUEUE_ID]);
		अक्षर queue_id_str[IFNAMSIZ + 7];

		/* queue_id option setting expects slave_name:queue_id */
		snम_लिखो(queue_id_str, माप(queue_id_str), "%s:%u\n",
			 slave_dev->name, queue_id);
		bond_opt_initstr(&newval, queue_id_str);
		err = __bond_opt_set(bond, BOND_OPT_QUEUE_ID, &newval);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bond_changelink(काष्ठा net_device *bond_dev, काष्ठा nlattr *tb[],
			   काष्ठा nlattr *data[],
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा bond_opt_value newval;
	पूर्णांक miimon = 0;
	पूर्णांक err;

	अगर (!data)
		वापस 0;

	अगर (data[IFLA_BOND_MODE]) अणु
		पूर्णांक mode = nla_get_u8(data[IFLA_BOND_MODE]);

		bond_opt_initval(&newval, mode);
		err = __bond_opt_set(bond, BOND_OPT_MODE, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_ACTIVE_SLAVE]) अणु
		पूर्णांक अगरindex = nla_get_u32(data[IFLA_BOND_ACTIVE_SLAVE]);
		काष्ठा net_device *slave_dev;
		अक्षर *active_slave = "";

		अगर (अगरindex != 0) अणु
			slave_dev = __dev_get_by_index(dev_net(bond_dev),
						       अगरindex);
			अगर (!slave_dev)
				वापस -ENODEV;
			active_slave = slave_dev->name;
		पूर्ण
		bond_opt_initstr(&newval, active_slave);
		err = __bond_opt_set(bond, BOND_OPT_ACTIVE_SLAVE, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_MIIMON]) अणु
		miimon = nla_get_u32(data[IFLA_BOND_MIIMON]);

		bond_opt_initval(&newval, miimon);
		err = __bond_opt_set(bond, BOND_OPT_MIIMON, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_UPDELAY]) अणु
		पूर्णांक updelay = nla_get_u32(data[IFLA_BOND_UPDELAY]);

		bond_opt_initval(&newval, updelay);
		err = __bond_opt_set(bond, BOND_OPT_UPDELAY, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_DOWNDELAY]) अणु
		पूर्णांक करोwndelay = nla_get_u32(data[IFLA_BOND_DOWNDELAY]);

		bond_opt_initval(&newval, करोwndelay);
		err = __bond_opt_set(bond, BOND_OPT_DOWNDELAY, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_PEER_NOTIF_DELAY]) अणु
		पूर्णांक delay = nla_get_u32(data[IFLA_BOND_PEER_NOTIF_DELAY]);

		bond_opt_initval(&newval, delay);
		err = __bond_opt_set(bond, BOND_OPT_PEER_NOTIF_DELAY, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_USE_CARRIER]) अणु
		पूर्णांक use_carrier = nla_get_u8(data[IFLA_BOND_USE_CARRIER]);

		bond_opt_initval(&newval, use_carrier);
		err = __bond_opt_set(bond, BOND_OPT_USE_CARRIER, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_ARP_INTERVAL]) अणु
		पूर्णांक arp_पूर्णांकerval = nla_get_u32(data[IFLA_BOND_ARP_INTERVAL]);

		अगर (arp_पूर्णांकerval && miimon) अणु
			netdev_err(bond->dev, "ARP monitoring cannot be used with MII monitoring\n");
			वापस -EINVAL;
		पूर्ण

		bond_opt_initval(&newval, arp_पूर्णांकerval);
		err = __bond_opt_set(bond, BOND_OPT_ARP_INTERVAL, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_ARP_IP_TARGET]) अणु
		काष्ठा nlattr *attr;
		पूर्णांक i = 0, rem;

		bond_option_arp_ip_tarमाला_लो_clear(bond);
		nla_क्रम_each_nested(attr, data[IFLA_BOND_ARP_IP_TARGET], rem) अणु
			__be32 target;

			अगर (nla_len(attr) < माप(target))
				वापस -EINVAL;

			target = nla_get_be32(attr);

			bond_opt_initval(&newval, (__क्रमce u64)target);
			err = __bond_opt_set(bond, BOND_OPT_ARP_TARGETS,
					     &newval);
			अगर (err)
				अवरोध;
			i++;
		पूर्ण
		अगर (i == 0 && bond->params.arp_पूर्णांकerval)
			netdev_warn(bond->dev, "Removing last arp target with arp_interval on\n");
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_ARP_VALIDATE]) अणु
		पूर्णांक arp_validate = nla_get_u32(data[IFLA_BOND_ARP_VALIDATE]);

		अगर (arp_validate && miimon) अणु
			netdev_err(bond->dev, "ARP validating cannot be used with MII monitoring\n");
			वापस -EINVAL;
		पूर्ण

		bond_opt_initval(&newval, arp_validate);
		err = __bond_opt_set(bond, BOND_OPT_ARP_VALIDATE, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_ARP_ALL_TARGETS]) अणु
		पूर्णांक arp_all_tarमाला_लो =
			nla_get_u32(data[IFLA_BOND_ARP_ALL_TARGETS]);

		bond_opt_initval(&newval, arp_all_tarमाला_लो);
		err = __bond_opt_set(bond, BOND_OPT_ARP_ALL_TARGETS, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_PRIMARY]) अणु
		पूर्णांक अगरindex = nla_get_u32(data[IFLA_BOND_PRIMARY]);
		काष्ठा net_device *dev;
		अक्षर *primary = "";

		dev = __dev_get_by_index(dev_net(bond_dev), अगरindex);
		अगर (dev)
			primary = dev->name;

		bond_opt_initstr(&newval, primary);
		err = __bond_opt_set(bond, BOND_OPT_PRIMARY, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_PRIMARY_RESELECT]) अणु
		पूर्णांक primary_reselect =
			nla_get_u8(data[IFLA_BOND_PRIMARY_RESELECT]);

		bond_opt_initval(&newval, primary_reselect);
		err = __bond_opt_set(bond, BOND_OPT_PRIMARY_RESELECT, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_FAIL_OVER_MAC]) अणु
		पूर्णांक fail_over_mac =
			nla_get_u8(data[IFLA_BOND_FAIL_OVER_MAC]);

		bond_opt_initval(&newval, fail_over_mac);
		err = __bond_opt_set(bond, BOND_OPT_FAIL_OVER_MAC, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_XMIT_HASH_POLICY]) अणु
		पूर्णांक xmit_hash_policy =
			nla_get_u8(data[IFLA_BOND_XMIT_HASH_POLICY]);

		bond_opt_initval(&newval, xmit_hash_policy);
		err = __bond_opt_set(bond, BOND_OPT_XMIT_HASH, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_RESEND_IGMP]) अणु
		पूर्णांक resend_igmp =
			nla_get_u32(data[IFLA_BOND_RESEND_IGMP]);

		bond_opt_initval(&newval, resend_igmp);
		err = __bond_opt_set(bond, BOND_OPT_RESEND_IGMP, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_NUM_PEER_NOTIF]) अणु
		पूर्णांक num_peer_notअगर =
			nla_get_u8(data[IFLA_BOND_NUM_PEER_NOTIF]);

		bond_opt_initval(&newval, num_peer_notअगर);
		err = __bond_opt_set(bond, BOND_OPT_NUM_PEER_NOTIF, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_ALL_SLAVES_ACTIVE]) अणु
		पूर्णांक all_slaves_active =
			nla_get_u8(data[IFLA_BOND_ALL_SLAVES_ACTIVE]);

		bond_opt_initval(&newval, all_slaves_active);
		err = __bond_opt_set(bond, BOND_OPT_ALL_SLAVES_ACTIVE, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_MIN_LINKS]) अणु
		पूर्णांक min_links =
			nla_get_u32(data[IFLA_BOND_MIN_LINKS]);

		bond_opt_initval(&newval, min_links);
		err = __bond_opt_set(bond, BOND_OPT_MINLINKS, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_LP_INTERVAL]) अणु
		पूर्णांक lp_पूर्णांकerval =
			nla_get_u32(data[IFLA_BOND_LP_INTERVAL]);

		bond_opt_initval(&newval, lp_पूर्णांकerval);
		err = __bond_opt_set(bond, BOND_OPT_LP_INTERVAL, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_PACKETS_PER_SLAVE]) अणु
		पूर्णांक packets_per_slave =
			nla_get_u32(data[IFLA_BOND_PACKETS_PER_SLAVE]);

		bond_opt_initval(&newval, packets_per_slave);
		err = __bond_opt_set(bond, BOND_OPT_PACKETS_PER_SLAVE, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_AD_LACP_RATE]) अणु
		पूर्णांक lacp_rate =
			nla_get_u8(data[IFLA_BOND_AD_LACP_RATE]);

		bond_opt_initval(&newval, lacp_rate);
		err = __bond_opt_set(bond, BOND_OPT_LACP_RATE, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_AD_SELECT]) अणु
		पूर्णांक ad_select =
			nla_get_u8(data[IFLA_BOND_AD_SELECT]);

		bond_opt_initval(&newval, ad_select);
		err = __bond_opt_set(bond, BOND_OPT_AD_SELECT, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_AD_ACTOR_SYS_PRIO]) अणु
		पूर्णांक actor_sys_prio =
			nla_get_u16(data[IFLA_BOND_AD_ACTOR_SYS_PRIO]);

		bond_opt_initval(&newval, actor_sys_prio);
		err = __bond_opt_set(bond, BOND_OPT_AD_ACTOR_SYS_PRIO, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_AD_USER_PORT_KEY]) अणु
		पूर्णांक port_key =
			nla_get_u16(data[IFLA_BOND_AD_USER_PORT_KEY]);

		bond_opt_initval(&newval, port_key);
		err = __bond_opt_set(bond, BOND_OPT_AD_USER_PORT_KEY, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_AD_ACTOR_SYSTEM]) अणु
		अगर (nla_len(data[IFLA_BOND_AD_ACTOR_SYSTEM]) != ETH_ALEN)
			वापस -EINVAL;

		bond_opt_initval(&newval,
				 nla_get_u64(data[IFLA_BOND_AD_ACTOR_SYSTEM]));
		err = __bond_opt_set(bond, BOND_OPT_AD_ACTOR_SYSTEM, &newval);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_BOND_TLB_DYNAMIC_LB]) अणु
		पूर्णांक dynamic_lb = nla_get_u8(data[IFLA_BOND_TLB_DYNAMIC_LB]);

		bond_opt_initval(&newval, dynamic_lb);
		err = __bond_opt_set(bond, BOND_OPT_TLB_DYNAMIC_LB, &newval);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bond_newlink(काष्ठा net *src_net, काष्ठा net_device *bond_dev,
			काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	err = bond_changelink(bond_dev, tb, data, extack);
	अगर (err < 0)
		वापस err;

	err = रेजिस्टर_netdevice(bond_dev);
	अगर (!err) अणु
		काष्ठा bonding *bond = netdev_priv(bond_dev);

		netअगर_carrier_off(bond_dev);
		bond_work_init_all(bond);
	पूर्ण

	वापस err;
पूर्ण

अटल माप_प्रकार bond_get_size(स्थिर काष्ठा net_device *bond_dev)
अणु
	वापस nla_total_size(माप(u8)) +	/* IFLA_BOND_MODE */
		nla_total_size(माप(u32)) +	/* IFLA_BOND_ACTIVE_SLAVE */
		nla_total_size(माप(u32)) +	/* IFLA_BOND_MIIMON */
		nla_total_size(माप(u32)) +	/* IFLA_BOND_UPDELAY */
		nla_total_size(माप(u32)) +	/* IFLA_BOND_DOWNDELAY */
		nla_total_size(माप(u8)) +	/* IFLA_BOND_USE_CARRIER */
		nla_total_size(माप(u32)) +	/* IFLA_BOND_ARP_INTERVAL */
						/* IFLA_BOND_ARP_IP_TARGET */
		nla_total_size(माप(काष्ठा nlattr)) +
		nla_total_size(माप(u32)) * BOND_MAX_ARP_TARGETS +
		nla_total_size(माप(u32)) +	/* IFLA_BOND_ARP_VALIDATE */
		nla_total_size(माप(u32)) +	/* IFLA_BOND_ARP_ALL_TARGETS */
		nla_total_size(माप(u32)) +	/* IFLA_BOND_PRIMARY */
		nla_total_size(माप(u8)) +	/* IFLA_BOND_PRIMARY_RESELECT */
		nla_total_size(माप(u8)) +	/* IFLA_BOND_FAIL_OVER_MAC */
		nla_total_size(माप(u8)) +	/* IFLA_BOND_XMIT_HASH_POLICY */
		nla_total_size(माप(u32)) +	/* IFLA_BOND_RESEND_IGMP */
		nla_total_size(माप(u8)) +	/* IFLA_BOND_NUM_PEER_NOTIF */
		nla_total_size(माप(u8)) +   /* IFLA_BOND_ALL_SLAVES_ACTIVE */
		nla_total_size(माप(u32)) +	/* IFLA_BOND_MIN_LINKS */
		nla_total_size(माप(u32)) +	/* IFLA_BOND_LP_INTERVAL */
		nla_total_size(माप(u32)) +  /* IFLA_BOND_PACKETS_PER_SLAVE */
		nla_total_size(माप(u8)) +	/* IFLA_BOND_AD_LACP_RATE */
		nla_total_size(माप(u8)) +	/* IFLA_BOND_AD_SELECT */
		nla_total_size(माप(काष्ठा nlattr)) + /* IFLA_BOND_AD_INFO */
		nla_total_size(माप(u16)) + /* IFLA_BOND_AD_INFO_AGGREGATOR */
		nla_total_size(माप(u16)) + /* IFLA_BOND_AD_INFO_NUM_PORTS */
		nla_total_size(माप(u16)) + /* IFLA_BOND_AD_INFO_ACTOR_KEY */
		nla_total_size(माप(u16)) + /* IFLA_BOND_AD_INFO_PARTNER_KEY*/
		nla_total_size(ETH_ALEN) +    /* IFLA_BOND_AD_INFO_PARTNER_MAC*/
		nla_total_size(माप(u16)) + /* IFLA_BOND_AD_ACTOR_SYS_PRIO */
		nla_total_size(माप(u16)) + /* IFLA_BOND_AD_USER_PORT_KEY */
		nla_total_size(ETH_ALEN) + /* IFLA_BOND_AD_ACTOR_SYSTEM */
		nla_total_size(माप(u8)) + /* IFLA_BOND_TLB_DYNAMIC_LB */
		nla_total_size(माप(u32)) +	/* IFLA_BOND_PEER_NOTIF_DELAY */
		0;
पूर्ण

अटल पूर्णांक bond_option_active_slave_get_अगरindex(काष्ठा bonding *bond)
अणु
	स्थिर काष्ठा net_device *slave;
	पूर्णांक अगरindex;

	rcu_पढ़ो_lock();
	slave = bond_option_active_slave_get_rcu(bond);
	अगरindex = slave ? slave->अगरindex : 0;
	rcu_पढ़ो_unlock();
	वापस अगरindex;
पूर्ण

अटल पूर्णांक bond_fill_info(काष्ठा sk_buff *skb,
			  स्थिर काष्ठा net_device *bond_dev)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	अचिन्हित पूर्णांक packets_per_slave;
	पूर्णांक अगरindex, i, tarमाला_लो_added;
	काष्ठा nlattr *tarमाला_लो;
	काष्ठा slave *primary;

	अगर (nla_put_u8(skb, IFLA_BOND_MODE, BOND_MODE(bond)))
		जाओ nla_put_failure;

	अगरindex = bond_option_active_slave_get_अगरindex(bond);
	अगर (अगरindex && nla_put_u32(skb, IFLA_BOND_ACTIVE_SLAVE, अगरindex))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, IFLA_BOND_MIIMON, bond->params.miimon))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, IFLA_BOND_UPDELAY,
			bond->params.updelay * bond->params.miimon))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, IFLA_BOND_DOWNDELAY,
			bond->params.करोwndelay * bond->params.miimon))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, IFLA_BOND_PEER_NOTIF_DELAY,
			bond->params.peer_notअगर_delay * bond->params.miimon))
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, IFLA_BOND_USE_CARRIER, bond->params.use_carrier))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, IFLA_BOND_ARP_INTERVAL, bond->params.arp_पूर्णांकerval))
		जाओ nla_put_failure;

	tarमाला_लो = nla_nest_start_noflag(skb, IFLA_BOND_ARP_IP_TARGET);
	अगर (!tarमाला_लो)
		जाओ nla_put_failure;

	tarमाला_लो_added = 0;
	क्रम (i = 0; i < BOND_MAX_ARP_TARGETS; i++) अणु
		अगर (bond->params.arp_tarमाला_लो[i]) अणु
			अगर (nla_put_be32(skb, i, bond->params.arp_tarमाला_लो[i]))
				जाओ nla_put_failure;
			tarमाला_लो_added = 1;
		पूर्ण
	पूर्ण

	अगर (tarमाला_लो_added)
		nla_nest_end(skb, tarमाला_लो);
	अन्यथा
		nla_nest_cancel(skb, tarमाला_लो);

	अगर (nla_put_u32(skb, IFLA_BOND_ARP_VALIDATE, bond->params.arp_validate))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, IFLA_BOND_ARP_ALL_TARGETS,
			bond->params.arp_all_tarमाला_लो))
		जाओ nla_put_failure;

	primary = rtnl_dereference(bond->primary_slave);
	अगर (primary &&
	    nla_put_u32(skb, IFLA_BOND_PRIMARY, primary->dev->अगरindex))
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, IFLA_BOND_PRIMARY_RESELECT,
		       bond->params.primary_reselect))
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, IFLA_BOND_FAIL_OVER_MAC,
		       bond->params.fail_over_mac))
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, IFLA_BOND_XMIT_HASH_POLICY,
		       bond->params.xmit_policy))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, IFLA_BOND_RESEND_IGMP,
		        bond->params.resend_igmp))
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, IFLA_BOND_NUM_PEER_NOTIF,
		       bond->params.num_peer_notअगर))
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, IFLA_BOND_ALL_SLAVES_ACTIVE,
		       bond->params.all_slaves_active))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, IFLA_BOND_MIN_LINKS,
			bond->params.min_links))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, IFLA_BOND_LP_INTERVAL,
			bond->params.lp_पूर्णांकerval))
		जाओ nla_put_failure;

	packets_per_slave = bond->params.packets_per_slave;
	अगर (nla_put_u32(skb, IFLA_BOND_PACKETS_PER_SLAVE,
			packets_per_slave))
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, IFLA_BOND_AD_LACP_RATE,
		       bond->params.lacp_fast))
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, IFLA_BOND_AD_SELECT,
		       bond->params.ad_select))
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, IFLA_BOND_TLB_DYNAMIC_LB,
		       bond->params.tlb_dynamic_lb))
		जाओ nla_put_failure;

	अगर (BOND_MODE(bond) == BOND_MODE_8023AD) अणु
		काष्ठा ad_info info;

		अगर (capable(CAP_NET_ADMIN)) अणु
			अगर (nla_put_u16(skb, IFLA_BOND_AD_ACTOR_SYS_PRIO,
					bond->params.ad_actor_sys_prio))
				जाओ nla_put_failure;

			अगर (nla_put_u16(skb, IFLA_BOND_AD_USER_PORT_KEY,
					bond->params.ad_user_port_key))
				जाओ nla_put_failure;

			अगर (nla_put(skb, IFLA_BOND_AD_ACTOR_SYSTEM,
				    ETH_ALEN, &bond->params.ad_actor_प्रणाली))
				जाओ nla_put_failure;
		पूर्ण
		अगर (!bond_3ad_get_active_agg_info(bond, &info)) अणु
			काष्ठा nlattr *nest;

			nest = nla_nest_start_noflag(skb, IFLA_BOND_AD_INFO);
			अगर (!nest)
				जाओ nla_put_failure;

			अगर (nla_put_u16(skb, IFLA_BOND_AD_INFO_AGGREGATOR,
					info.aggregator_id))
				जाओ nla_put_failure;
			अगर (nla_put_u16(skb, IFLA_BOND_AD_INFO_NUM_PORTS,
					info.ports))
				जाओ nla_put_failure;
			अगर (nla_put_u16(skb, IFLA_BOND_AD_INFO_ACTOR_KEY,
					info.actor_key))
				जाओ nla_put_failure;
			अगर (nla_put_u16(skb, IFLA_BOND_AD_INFO_PARTNER_KEY,
					info.partner_key))
				जाओ nla_put_failure;
			अगर (nla_put(skb, IFLA_BOND_AD_INFO_PARTNER_MAC,
				    माप(info.partner_प्रणाली),
				    &info.partner_प्रणाली))
				जाओ nla_put_failure;

			nla_nest_end(skb, nest);
		पूर्ण
	पूर्ण

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल माप_प्रकार bond_get_linkxstats_size(स्थिर काष्ठा net_device *dev, पूर्णांक attr)
अणु
	चयन (attr) अणु
	हाल IFLA_STATS_LINK_XSTATS:
	हाल IFLA_STATS_LINK_XSTATS_SLAVE:
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस bond_3ad_stats_size() + nla_total_size(0);
पूर्ण

अटल पूर्णांक bond_fill_linkxstats(काष्ठा sk_buff *skb,
				स्थिर काष्ठा net_device *dev,
				पूर्णांक *prividx, पूर्णांक attr)
अणु
	काष्ठा nlattr *nla __maybe_unused;
	काष्ठा slave *slave = शून्य;
	काष्ठा nlattr *nest, *nest2;
	काष्ठा bonding *bond;

	चयन (attr) अणु
	हाल IFLA_STATS_LINK_XSTATS:
		bond = netdev_priv(dev);
		अवरोध;
	हाल IFLA_STATS_LINK_XSTATS_SLAVE:
		slave = bond_slave_get_rtnl(dev);
		अगर (!slave)
			वापस 0;
		bond = slave->bond;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	nest = nla_nest_start_noflag(skb, LINK_XSTATS_TYPE_BOND);
	अगर (!nest)
		वापस -EMSGSIZE;
	अगर (BOND_MODE(bond) == BOND_MODE_8023AD) अणु
		काष्ठा bond_3ad_stats *stats;

		अगर (slave)
			stats = &SLAVE_AD_INFO(slave)->stats;
		अन्यथा
			stats = &BOND_AD_INFO(bond).stats;

		nest2 = nla_nest_start_noflag(skb, BOND_XSTATS_3AD);
		अगर (!nest2) अणु
			nla_nest_end(skb, nest);
			वापस -EMSGSIZE;
		पूर्ण

		अगर (bond_3ad_stats_fill(skb, stats)) अणु
			nla_nest_cancel(skb, nest2);
			nla_nest_end(skb, nest);
			वापस -EMSGSIZE;
		पूर्ण
		nla_nest_end(skb, nest2);
	पूर्ण
	nla_nest_end(skb, nest);

	वापस 0;
पूर्ण

काष्ठा rtnl_link_ops bond_link_ops __पढ़ो_mostly = अणु
	.kind			= "bond",
	.priv_size		= माप(काष्ठा bonding),
	.setup			= bond_setup,
	.maxtype		= IFLA_BOND_MAX,
	.policy			= bond_policy,
	.validate		= bond_validate,
	.newlink		= bond_newlink,
	.changelink		= bond_changelink,
	.get_size		= bond_get_size,
	.fill_info		= bond_fill_info,
	.get_num_tx_queues	= bond_get_num_tx_queues,
	.get_num_rx_queues	= bond_get_num_tx_queues, /* Use the same number
							     as क्रम TX queues */
	.fill_linkxstats        = bond_fill_linkxstats,
	.get_linkxstats_size    = bond_get_linkxstats_size,
	.slave_maxtype		= IFLA_BOND_SLAVE_MAX,
	.slave_policy		= bond_slave_policy,
	.slave_changelink	= bond_slave_changelink,
	.get_slave_size		= bond_get_slave_size,
	.fill_slave_info	= bond_fill_slave_info,
पूर्ण;

पूर्णांक __init bond_netlink_init(व्योम)
अणु
	वापस rtnl_link_रेजिस्टर(&bond_link_ops);
पूर्ण

व्योम bond_netlink_fini(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&bond_link_ops);
पूर्ण

MODULE_ALIAS_RTNL_LINK("bond");
