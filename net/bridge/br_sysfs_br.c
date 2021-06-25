<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Sysfs attributes of bridge
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Stephen Hemminger		<shemminger@osdl.org>
 */

#समावेश <linux/capability.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/बार.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "br_private.h"

/* IMPORTANT: new bridge options must be added with netlink support only
 *            please करो not add new sysfs entries
 */

#घोषणा to_bridge(cd)	((काष्ठा net_bridge *)netdev_priv(to_net_dev(cd)))

/*
 * Common code क्रम storing bridge parameters.
 */
अटल sमाप_प्रकार store_bridge_parm(काष्ठा device *d,
				 स्थिर अक्षर *buf, माप_प्रकार len,
				 पूर्णांक (*set)(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
					    काष्ठा netlink_ext_ack *extack))
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	काष्ठा netlink_ext_ack extack = अणु0पूर्ण;
	अचिन्हित दीर्घ val;
	अक्षर *endp;
	पूर्णांक err;

	अगर (!ns_capable(dev_net(br->dev)->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	val = simple_म_से_अदीर्घ(buf, &endp, 0);
	अगर (endp == buf)
		वापस -EINVAL;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	err = (*set)(br, val, &extack);
	अगर (!err)
		netdev_state_change(br->dev);
	अगर (extack._msg) अणु
		अगर (err)
			br_err(br, "%s\n", extack._msg);
		अन्यथा
			br_warn(br, "%s\n", extack._msg);
	पूर्ण
	rtnl_unlock();

	वापस err ? err : len;
पूर्ण


अटल sमाप_प्रकार क्रमward_delay_show(काष्ठा device *d,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%lu\n", jअगरfies_to_घड़ी_प्रकार(br->क्रमward_delay));
पूर्ण

अटल पूर्णांक set_क्रमward_delay(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
			     काष्ठा netlink_ext_ack *extack)
अणु
	वापस br_set_क्रमward_delay(br, val);
पूर्ण

अटल sमाप_प्रकार क्रमward_delay_store(काष्ठा device *d,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_क्रमward_delay);
पूर्ण
अटल DEVICE_ATTR_RW(क्रमward_delay);

अटल sमाप_प्रकार hello_समय_show(काष्ठा device *d, काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%lu\n",
		       jअगरfies_to_घड़ी_प्रकार(to_bridge(d)->hello_समय));
पूर्ण

अटल पूर्णांक set_hello_समय(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
			  काष्ठा netlink_ext_ack *extack)
अणु
	वापस br_set_hello_समय(br, val);
पूर्ण

अटल sमाप_प्रकार hello_समय_store(काष्ठा device *d,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_hello_समय);
पूर्ण
अटल DEVICE_ATTR_RW(hello_समय);

अटल sमाप_प्रकार max_age_show(काष्ठा device *d, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%lu\n",
		       jअगरfies_to_घड़ी_प्रकार(to_bridge(d)->max_age));
पूर्ण

अटल पूर्णांक set_max_age(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
		       काष्ठा netlink_ext_ack *extack)
अणु
	वापस br_set_max_age(br, val);
पूर्ण

अटल sमाप_प्रकार max_age_store(काष्ठा device *d, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_max_age);
पूर्ण
अटल DEVICE_ATTR_RW(max_age);

अटल sमाप_प्रकार ageing_समय_show(काष्ठा device *d,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%lu\n", jअगरfies_to_घड़ी_प्रकार(br->ageing_समय));
पूर्ण

अटल पूर्णांक set_ageing_समय(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
			   काष्ठा netlink_ext_ack *extack)
अणु
	वापस br_set_ageing_समय(br, val);
पूर्ण

अटल sमाप_प्रकार ageing_समय_store(काष्ठा device *d,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_ageing_समय);
पूर्ण
अटल DEVICE_ATTR_RW(ageing_समय);

अटल sमाप_प्रकार stp_state_show(काष्ठा device *d,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%d\n", br->stp_enabled);
पूर्ण


अटल पूर्णांक set_stp_state(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
			 काष्ठा netlink_ext_ack *extack)
अणु
	वापस br_stp_set_enabled(br, val, extack);
पूर्ण

अटल sमाप_प्रकार stp_state_store(काष्ठा device *d,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_stp_state);
पूर्ण
अटल DEVICE_ATTR_RW(stp_state);

अटल sमाप_प्रकार group_fwd_mask_show(काष्ठा device *d,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%#x\n", br->group_fwd_mask);
पूर्ण

अटल पूर्णांक set_group_fwd_mask(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
			      काष्ठा netlink_ext_ack *extack)
अणु
	अगर (val & BR_GROUPFWD_RESTRICTED)
		वापस -EINVAL;

	br->group_fwd_mask = val;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार group_fwd_mask_store(काष्ठा device *d,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf,
				    माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_group_fwd_mask);
पूर्ण
अटल DEVICE_ATTR_RW(group_fwd_mask);

अटल sमाप_प्रकार priority_show(काष्ठा device *d, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%d\n",
		       (br->bridge_id.prio[0] << 8) | br->bridge_id.prio[1]);
पूर्ण

अटल पूर्णांक set_priority(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
			काष्ठा netlink_ext_ack *extack)
अणु
	br_stp_set_bridge_priority(br, (u16) val);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार priority_store(काष्ठा device *d, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_priority);
पूर्ण
अटल DEVICE_ATTR_RW(priority);

अटल sमाप_प्रकार root_id_show(काष्ठा device *d, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	वापस br_show_bridge_id(buf, &to_bridge(d)->designated_root);
पूर्ण
अटल DEVICE_ATTR_RO(root_id);

अटल sमाप_प्रकार bridge_id_show(काष्ठा device *d, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	वापस br_show_bridge_id(buf, &to_bridge(d)->bridge_id);
पूर्ण
अटल DEVICE_ATTR_RO(bridge_id);

अटल sमाप_प्रकार root_port_show(काष्ठा device *d, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", to_bridge(d)->root_port);
पूर्ण
अटल DEVICE_ATTR_RO(root_port);

अटल sमाप_प्रकार root_path_cost_show(काष्ठा device *d,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", to_bridge(d)->root_path_cost);
पूर्ण
अटल DEVICE_ATTR_RO(root_path_cost);

अटल sमाप_प्रकार topology_change_show(काष्ठा device *d,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", to_bridge(d)->topology_change);
पूर्ण
अटल DEVICE_ATTR_RO(topology_change);

अटल sमाप_प्रकार topology_change_detected_show(काष्ठा device *d,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%d\n", br->topology_change_detected);
पूर्ण
अटल DEVICE_ATTR_RO(topology_change_detected);

अटल sमाप_प्रकार hello_समयr_show(काष्ठा device *d,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%ld\n", br_समयr_value(&br->hello_समयr));
पूर्ण
अटल DEVICE_ATTR_RO(hello_समयr);

अटल sमाप_प्रकार tcn_समयr_show(काष्ठा device *d, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%ld\n", br_समयr_value(&br->tcn_समयr));
पूर्ण
अटल DEVICE_ATTR_RO(tcn_समयr);

अटल sमाप_प्रकार topology_change_समयr_show(काष्ठा device *d,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%ld\n", br_समयr_value(&br->topology_change_समयr));
पूर्ण
अटल DEVICE_ATTR_RO(topology_change_समयr);

अटल sमाप_प्रकार gc_समयr_show(काष्ठा device *d, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%ld\n", br_समयr_value(&br->gc_work.समयr));
पूर्ण
अटल DEVICE_ATTR_RO(gc_समयr);

अटल sमाप_प्रकार group_addr_show(काष्ठा device *d,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%pM\n", br->group_addr);
पूर्ण

अटल sमाप_प्रकार group_addr_store(काष्ठा device *d,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	u8 new_addr[6];

	अगर (!ns_capable(dev_net(br->dev)->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!mac_pton(buf, new_addr))
		वापस -EINVAL;

	अगर (!is_link_local_ether_addr(new_addr))
		वापस -EINVAL;

	अगर (new_addr[5] == 1 ||		/* 802.3x Pause address */
	    new_addr[5] == 2 ||		/* 802.3ad Slow protocols */
	    new_addr[5] == 3)		/* 802.1X PAE address */
		वापस -EINVAL;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	spin_lock_bh(&br->lock);
	ether_addr_copy(br->group_addr, new_addr);
	spin_unlock_bh(&br->lock);

	br_opt_toggle(br, BROPT_GROUP_ADDR_SET, true);
	br_recalculate_fwd_mask(br);
	netdev_state_change(br->dev);

	rtnl_unlock();

	वापस len;
पूर्ण

अटल DEVICE_ATTR_RW(group_addr);

अटल पूर्णांक set_flush(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
		     काष्ठा netlink_ext_ack *extack)
अणु
	br_fdb_flush(br);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार flush_store(काष्ठा device *d,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_flush);
पूर्ण
अटल DEVICE_ATTR_WO(flush);

अटल sमाप_प्रकार no_linklocal_learn_show(काष्ठा device *d,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%d\n", br_boolopt_get(br, BR_BOOLOPT_NO_LL_LEARN));
पूर्ण

अटल पूर्णांक set_no_linklocal_learn(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
				  काष्ठा netlink_ext_ack *extack)
अणु
	वापस br_boolopt_toggle(br, BR_BOOLOPT_NO_LL_LEARN, !!val, extack);
पूर्ण

अटल sमाप_प्रकार no_linklocal_learn_store(काष्ठा device *d,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_no_linklocal_learn);
पूर्ण
अटल DEVICE_ATTR_RW(no_linklocal_learn);

#अगर_घोषित CONFIG_BRIDGE_IGMP_SNOOPING
अटल sमाप_प्रकार multicast_router_show(काष्ठा device *d,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%d\n", br->multicast_router);
पूर्ण

अटल पूर्णांक set_multicast_router(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
				काष्ठा netlink_ext_ack *extack)
अणु
	वापस br_multicast_set_router(br, val);
पूर्ण

अटल sमाप_प्रकार multicast_router_store(काष्ठा device *d,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_multicast_router);
पूर्ण
अटल DEVICE_ATTR_RW(multicast_router);

अटल sमाप_प्रकार multicast_snooping_show(काष्ठा device *d,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%d\n", br_opt_get(br, BROPT_MULTICAST_ENABLED));
पूर्ण

अटल sमाप_प्रकार multicast_snooping_store(काष्ठा device *d,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, br_multicast_toggle);
पूर्ण
अटल DEVICE_ATTR_RW(multicast_snooping);

अटल sमाप_प्रकार multicast_query_use_अगरaddr_show(काष्ठा device *d,
					       काष्ठा device_attribute *attr,
					       अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%d\n",
		       br_opt_get(br, BROPT_MULTICAST_QUERY_USE_IFADDR));
पूर्ण

अटल पूर्णांक set_query_use_अगरaddr(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
				काष्ठा netlink_ext_ack *extack)
अणु
	br_opt_toggle(br, BROPT_MULTICAST_QUERY_USE_IFADDR, !!val);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
multicast_query_use_अगरaddr_store(काष्ठा device *d,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_query_use_अगरaddr);
पूर्ण
अटल DEVICE_ATTR_RW(multicast_query_use_अगरaddr);

अटल sमाप_प्रकार multicast_querier_show(काष्ठा device *d,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%d\n", br_opt_get(br, BROPT_MULTICAST_QUERIER));
पूर्ण

अटल पूर्णांक set_multicast_querier(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
				 काष्ठा netlink_ext_ack *extack)
अणु
	वापस br_multicast_set_querier(br, val);
पूर्ण

अटल sमाप_प्रकार multicast_querier_store(काष्ठा device *d,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_multicast_querier);
पूर्ण
अटल DEVICE_ATTR_RW(multicast_querier);

अटल sमाप_प्रकार hash_elasticity_show(काष्ठा device *d,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", RHT_ELASTICITY);
पूर्ण

अटल पूर्णांक set_elasticity(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
			  काष्ठा netlink_ext_ack *extack)
अणु
	/* 16 is RHT_ELASTICITY */
	NL_SET_ERR_MSG_MOD(extack,
			   "the hash_elasticity option has been deprecated and is always 16");
	वापस 0;
पूर्ण

अटल sमाप_प्रकार hash_elasticity_store(काष्ठा device *d,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_elasticity);
पूर्ण
अटल DEVICE_ATTR_RW(hash_elasticity);

अटल sमाप_प्रकार hash_max_show(काष्ठा device *d, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%u\n", br->hash_max);
पूर्ण

अटल पूर्णांक set_hash_max(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
			काष्ठा netlink_ext_ack *extack)
अणु
	br->hash_max = val;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार hash_max_store(काष्ठा device *d, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_hash_max);
पूर्ण
अटल DEVICE_ATTR_RW(hash_max);

अटल sमाप_प्रकार multicast_igmp_version_show(काष्ठा device *d,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);

	वापस प्र_लिखो(buf, "%u\n", br->multicast_igmp_version);
पूर्ण

अटल पूर्णांक set_multicast_igmp_version(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
				      काष्ठा netlink_ext_ack *extack)
अणु
	वापस br_multicast_set_igmp_version(br, val);
पूर्ण

अटल sमाप_प्रकार multicast_igmp_version_store(काष्ठा device *d,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_multicast_igmp_version);
पूर्ण
अटल DEVICE_ATTR_RW(multicast_igmp_version);

अटल sमाप_प्रकार multicast_last_member_count_show(काष्ठा device *d,
						काष्ठा device_attribute *attr,
						अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%u\n", br->multicast_last_member_count);
पूर्ण

अटल पूर्णांक set_last_member_count(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
				 काष्ठा netlink_ext_ack *extack)
अणु
	br->multicast_last_member_count = val;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार multicast_last_member_count_store(काष्ठा device *d,
						 काष्ठा device_attribute *attr,
						 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_last_member_count);
पूर्ण
अटल DEVICE_ATTR_RW(multicast_last_member_count);

अटल sमाप_प्रकार multicast_startup_query_count_show(
	काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%u\n", br->multicast_startup_query_count);
पूर्ण

अटल पूर्णांक set_startup_query_count(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
				   काष्ठा netlink_ext_ack *extack)
अणु
	br->multicast_startup_query_count = val;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार multicast_startup_query_count_store(
	काष्ठा device *d, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
	माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_startup_query_count);
पूर्ण
अटल DEVICE_ATTR_RW(multicast_startup_query_count);

अटल sमाप_प्रकार multicast_last_member_पूर्णांकerval_show(
	काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%lu\n",
		       jअगरfies_to_घड़ी_प्रकार(br->multicast_last_member_पूर्णांकerval));
पूर्ण

अटल पूर्णांक set_last_member_पूर्णांकerval(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
				    काष्ठा netlink_ext_ack *extack)
अणु
	br->multicast_last_member_पूर्णांकerval = घड़ी_प्रकार_to_jअगरfies(val);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार multicast_last_member_पूर्णांकerval_store(
	काष्ठा device *d, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
	माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_last_member_पूर्णांकerval);
पूर्ण
अटल DEVICE_ATTR_RW(multicast_last_member_पूर्णांकerval);

अटल sमाप_प्रकार multicast_membership_पूर्णांकerval_show(
	काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%lu\n",
		       jअगरfies_to_घड़ी_प्रकार(br->multicast_membership_पूर्णांकerval));
पूर्ण

अटल पूर्णांक set_membership_पूर्णांकerval(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
				   काष्ठा netlink_ext_ack *extack)
अणु
	br->multicast_membership_पूर्णांकerval = घड़ी_प्रकार_to_jअगरfies(val);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार multicast_membership_पूर्णांकerval_store(
	काष्ठा device *d, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
	माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_membership_पूर्णांकerval);
पूर्ण
अटल DEVICE_ATTR_RW(multicast_membership_पूर्णांकerval);

अटल sमाप_प्रकार multicast_querier_पूर्णांकerval_show(काष्ठा device *d,
					       काष्ठा device_attribute *attr,
					       अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%lu\n",
		       jअगरfies_to_घड़ी_प्रकार(br->multicast_querier_पूर्णांकerval));
पूर्ण

अटल पूर्णांक set_querier_पूर्णांकerval(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
				काष्ठा netlink_ext_ack *extack)
अणु
	br->multicast_querier_पूर्णांकerval = घड़ी_प्रकार_to_jअगरfies(val);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार multicast_querier_पूर्णांकerval_store(काष्ठा device *d,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_querier_पूर्णांकerval);
पूर्ण
अटल DEVICE_ATTR_RW(multicast_querier_पूर्णांकerval);

अटल sमाप_प्रकार multicast_query_पूर्णांकerval_show(काष्ठा device *d,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%lu\n",
		       jअगरfies_to_घड़ी_प्रकार(br->multicast_query_पूर्णांकerval));
पूर्ण

अटल पूर्णांक set_query_पूर्णांकerval(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
			      काष्ठा netlink_ext_ack *extack)
अणु
	br->multicast_query_पूर्णांकerval = घड़ी_प्रकार_to_jअगरfies(val);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार multicast_query_पूर्णांकerval_store(काष्ठा device *d,
					      काष्ठा device_attribute *attr,
					      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_query_पूर्णांकerval);
पूर्ण
अटल DEVICE_ATTR_RW(multicast_query_पूर्णांकerval);

अटल sमाप_प्रकार multicast_query_response_पूर्णांकerval_show(
	काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(
		buf, "%lu\n",
		jअगरfies_to_घड़ी_प्रकार(br->multicast_query_response_पूर्णांकerval));
पूर्ण

अटल पूर्णांक set_query_response_पूर्णांकerval(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
				       काष्ठा netlink_ext_ack *extack)
अणु
	br->multicast_query_response_पूर्णांकerval = घड़ी_प्रकार_to_jअगरfies(val);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार multicast_query_response_पूर्णांकerval_store(
	काष्ठा device *d, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
	माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_query_response_पूर्णांकerval);
पूर्ण
अटल DEVICE_ATTR_RW(multicast_query_response_पूर्णांकerval);

अटल sमाप_प्रकार multicast_startup_query_पूर्णांकerval_show(
	काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(
		buf, "%lu\n",
		jअगरfies_to_घड़ी_प्रकार(br->multicast_startup_query_पूर्णांकerval));
पूर्ण

अटल पूर्णांक set_startup_query_पूर्णांकerval(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
				      काष्ठा netlink_ext_ack *extack)
अणु
	br->multicast_startup_query_पूर्णांकerval = घड़ी_प्रकार_to_jअगरfies(val);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार multicast_startup_query_पूर्णांकerval_store(
	काष्ठा device *d, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
	माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_startup_query_पूर्णांकerval);
पूर्ण
अटल DEVICE_ATTR_RW(multicast_startup_query_पूर्णांकerval);

अटल sमाप_प्रकार multicast_stats_enabled_show(काष्ठा device *d,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);

	वापस प्र_लिखो(buf, "%d\n",
		       br_opt_get(br, BROPT_MULTICAST_STATS_ENABLED));
पूर्ण

अटल पूर्णांक set_stats_enabled(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
			     काष्ठा netlink_ext_ack *extack)
अणु
	br_opt_toggle(br, BROPT_MULTICAST_STATS_ENABLED, !!val);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार multicast_stats_enabled_store(काष्ठा device *d,
					     काष्ठा device_attribute *attr,
					     स्थिर अक्षर *buf,
					     माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_stats_enabled);
पूर्ण
अटल DEVICE_ATTR_RW(multicast_stats_enabled);

#अगर IS_ENABLED(CONFIG_IPV6)
अटल sमाप_प्रकार multicast_mld_version_show(काष्ठा device *d,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);

	वापस प्र_लिखो(buf, "%u\n", br->multicast_mld_version);
पूर्ण

अटल पूर्णांक set_multicast_mld_version(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
				     काष्ठा netlink_ext_ack *extack)
अणु
	वापस br_multicast_set_mld_version(br, val);
पूर्ण

अटल sमाप_प्रकार multicast_mld_version_store(काष्ठा device *d,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_multicast_mld_version);
पूर्ण
अटल DEVICE_ATTR_RW(multicast_mld_version);
#पूर्ण_अगर
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
अटल sमाप_प्रकार nf_call_iptables_show(
	काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%u\n", br_opt_get(br, BROPT_NF_CALL_IPTABLES));
पूर्ण

अटल पूर्णांक set_nf_call_iptables(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
				काष्ठा netlink_ext_ack *extack)
अणु
	br_opt_toggle(br, BROPT_NF_CALL_IPTABLES, !!val);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार nf_call_iptables_store(
	काष्ठा device *d, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
	माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_nf_call_iptables);
पूर्ण
अटल DEVICE_ATTR_RW(nf_call_iptables);

अटल sमाप_प्रकार nf_call_ip6tables_show(
	काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%u\n", br_opt_get(br, BROPT_NF_CALL_IP6TABLES));
पूर्ण

अटल पूर्णांक set_nf_call_ip6tables(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
				 काष्ठा netlink_ext_ack *extack)
अणु
	br_opt_toggle(br, BROPT_NF_CALL_IP6TABLES, !!val);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार nf_call_ip6tables_store(
	काष्ठा device *d, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
	माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_nf_call_ip6tables);
पूर्ण
अटल DEVICE_ATTR_RW(nf_call_ip6tables);

अटल sमाप_प्रकार nf_call_arptables_show(
	काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%u\n", br_opt_get(br, BROPT_NF_CALL_ARPTABLES));
पूर्ण

अटल पूर्णांक set_nf_call_arptables(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
				 काष्ठा netlink_ext_ack *extack)
अणु
	br_opt_toggle(br, BROPT_NF_CALL_ARPTABLES, !!val);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार nf_call_arptables_store(
	काष्ठा device *d, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
	माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_nf_call_arptables);
पूर्ण
अटल DEVICE_ATTR_RW(nf_call_arptables);
#पूर्ण_अगर
#अगर_घोषित CONFIG_BRIDGE_VLAN_FILTERING
अटल sमाप_प्रकार vlan_filtering_show(काष्ठा device *d,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%d\n", br_opt_get(br, BROPT_VLAN_ENABLED));
पूर्ण

अटल sमाप_प्रकार vlan_filtering_store(काष्ठा device *d,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, br_vlan_filter_toggle);
पूर्ण
अटल DEVICE_ATTR_RW(vlan_filtering);

अटल sमाप_प्रकार vlan_protocol_show(काष्ठा device *d,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%#06x\n", ntohs(br->vlan_proto));
पूर्ण

अटल sमाप_प्रकार vlan_protocol_store(काष्ठा device *d,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, br_vlan_set_proto);
पूर्ण
अटल DEVICE_ATTR_RW(vlan_protocol);

अटल sमाप_प्रकार शेष_pvid_show(काष्ठा device *d,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%d\n", br->शेष_pvid);
पूर्ण

अटल sमाप_प्रकार शेष_pvid_store(काष्ठा device *d,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, br_vlan_set_शेष_pvid);
पूर्ण
अटल DEVICE_ATTR_RW(शेष_pvid);

अटल sमाप_प्रकार vlan_stats_enabled_show(काष्ठा device *d,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%u\n", br_opt_get(br, BROPT_VLAN_STATS_ENABLED));
पूर्ण

अटल पूर्णांक set_vlan_stats_enabled(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
				  काष्ठा netlink_ext_ack *extack)
अणु
	वापस br_vlan_set_stats(br, val);
पूर्ण

अटल sमाप_प्रकार vlan_stats_enabled_store(काष्ठा device *d,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_vlan_stats_enabled);
पूर्ण
अटल DEVICE_ATTR_RW(vlan_stats_enabled);

अटल sमाप_प्रकार vlan_stats_per_port_show(काष्ठा device *d,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा net_bridge *br = to_bridge(d);
	वापस प्र_लिखो(buf, "%u\n", br_opt_get(br, BROPT_VLAN_STATS_PER_PORT));
पूर्ण

अटल पूर्णांक set_vlan_stats_per_port(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
				   काष्ठा netlink_ext_ack *extack)
अणु
	वापस br_vlan_set_stats_per_port(br, val);
पूर्ण

अटल sमाप_प्रकार vlan_stats_per_port_store(काष्ठा device *d,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस store_bridge_parm(d, buf, len, set_vlan_stats_per_port);
पूर्ण
अटल DEVICE_ATTR_RW(vlan_stats_per_port);
#पूर्ण_अगर

अटल काष्ठा attribute *bridge_attrs[] = अणु
	&dev_attr_क्रमward_delay.attr,
	&dev_attr_hello_समय.attr,
	&dev_attr_max_age.attr,
	&dev_attr_ageing_समय.attr,
	&dev_attr_stp_state.attr,
	&dev_attr_group_fwd_mask.attr,
	&dev_attr_priority.attr,
	&dev_attr_bridge_id.attr,
	&dev_attr_root_id.attr,
	&dev_attr_root_path_cost.attr,
	&dev_attr_root_port.attr,
	&dev_attr_topology_change.attr,
	&dev_attr_topology_change_detected.attr,
	&dev_attr_hello_समयr.attr,
	&dev_attr_tcn_समयr.attr,
	&dev_attr_topology_change_समयr.attr,
	&dev_attr_gc_समयr.attr,
	&dev_attr_group_addr.attr,
	&dev_attr_flush.attr,
	&dev_attr_no_linklocal_learn.attr,
#अगर_घोषित CONFIG_BRIDGE_IGMP_SNOOPING
	&dev_attr_multicast_router.attr,
	&dev_attr_multicast_snooping.attr,
	&dev_attr_multicast_querier.attr,
	&dev_attr_multicast_query_use_अगरaddr.attr,
	&dev_attr_hash_elasticity.attr,
	&dev_attr_hash_max.attr,
	&dev_attr_multicast_last_member_count.attr,
	&dev_attr_multicast_startup_query_count.attr,
	&dev_attr_multicast_last_member_पूर्णांकerval.attr,
	&dev_attr_multicast_membership_पूर्णांकerval.attr,
	&dev_attr_multicast_querier_पूर्णांकerval.attr,
	&dev_attr_multicast_query_पूर्णांकerval.attr,
	&dev_attr_multicast_query_response_पूर्णांकerval.attr,
	&dev_attr_multicast_startup_query_पूर्णांकerval.attr,
	&dev_attr_multicast_stats_enabled.attr,
	&dev_attr_multicast_igmp_version.attr,
#अगर IS_ENABLED(CONFIG_IPV6)
	&dev_attr_multicast_mld_version.attr,
#पूर्ण_अगर
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
	&dev_attr_nf_call_iptables.attr,
	&dev_attr_nf_call_ip6tables.attr,
	&dev_attr_nf_call_arptables.attr,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BRIDGE_VLAN_FILTERING
	&dev_attr_vlan_filtering.attr,
	&dev_attr_vlan_protocol.attr,
	&dev_attr_शेष_pvid.attr,
	&dev_attr_vlan_stats_enabled.attr,
	&dev_attr_vlan_stats_per_port.attr,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group bridge_group = अणु
	.name = SYSFS_BRIDGE_ATTR,
	.attrs = bridge_attrs,
पूर्ण;

/*
 * Export the क्रमwarding inक्रमmation table as a binary file
 * The records are काष्ठा __fdb_entry.
 *
 * Returns the number of bytes पढ़ो.
 */
अटल sमाप_प्रकार brक्रमward_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			      काष्ठा bin_attribute *bin_attr,
			      अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा net_bridge *br = to_bridge(dev);
	पूर्णांक n;

	/* must पढ़ो whole records */
	अगर (off % माप(काष्ठा __fdb_entry) != 0)
		वापस -EINVAL;

	n =  br_fdb_fillbuf(br, buf,
			    count / माप(काष्ठा __fdb_entry),
			    off / माप(काष्ठा __fdb_entry));

	अगर (n > 0)
		n *= माप(काष्ठा __fdb_entry);

	वापस n;
पूर्ण

अटल काष्ठा bin_attribute bridge_क्रमward = अणु
	.attr = अणु .name = SYSFS_BRIDGE_FDB,
		  .mode = 0444, पूर्ण,
	.पढ़ो = brक्रमward_पढ़ो,
पूर्ण;

/*
 * Add entries in sysfs onto the existing network class device
 * क्रम the bridge.
 *   Adds a attribute group "bridge" containing tuning parameters.
 *   Binary attribute containing the क्रमward table
 *   Sub directory to hold links to पूर्णांकerfaces.
 *
 * Note: the अगरobj exists only to be a subdirectory
 *   to hold links.  The अगरobj exists in same data काष्ठाure
 *   as it's parent the bridge so reference counting works.
 */
पूर्णांक br_sysfs_addbr(काष्ठा net_device *dev)
अणु
	काष्ठा kobject *brobj = &dev->dev.kobj;
	काष्ठा net_bridge *br = netdev_priv(dev);
	पूर्णांक err;

	err = sysfs_create_group(brobj, &bridge_group);
	अगर (err) अणु
		pr_info("%s: can't create group %s/%s\n",
			__func__, dev->name, bridge_group.name);
		जाओ out1;
	पूर्ण

	err = sysfs_create_bin_file(brobj, &bridge_क्रमward);
	अगर (err) अणु
		pr_info("%s: can't create attribute file %s/%s\n",
			__func__, dev->name, bridge_क्रमward.attr.name);
		जाओ out2;
	पूर्ण

	br->अगरobj = kobject_create_and_add(SYSFS_BRIDGE_PORT_SUBसूची, brobj);
	अगर (!br->अगरobj) अणु
		pr_info("%s: can't add kobject (directory) %s/%s\n",
			__func__, dev->name, SYSFS_BRIDGE_PORT_SUBसूची);
		err = -ENOMEM;
		जाओ out3;
	पूर्ण
	वापस 0;
 out3:
	sysfs_हटाओ_bin_file(&dev->dev.kobj, &bridge_क्रमward);
 out2:
	sysfs_हटाओ_group(&dev->dev.kobj, &bridge_group);
 out1:
	वापस err;

पूर्ण

व्योम br_sysfs_delbr(काष्ठा net_device *dev)
अणु
	काष्ठा kobject *kobj = &dev->dev.kobj;
	काष्ठा net_bridge *br = netdev_priv(dev);

	kobject_put(br->अगरobj);
	sysfs_हटाओ_bin_file(kobj, &bridge_क्रमward);
	sysfs_हटाओ_group(kobj, &bridge_group);
पूर्ण
