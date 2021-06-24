<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright(c) 2004-2005 Intel Corporation. All rights reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/in.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/inet.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <linux/nsproxy.h>

#समावेश <net/bonding.h>

#घोषणा to_bond(cd)	((काष्ठा bonding *)(netdev_priv(to_net_dev(cd))))

/* "show" function क्रम the bond_masters attribute.
 * The class parameter is ignored.
 */
अटल sमाप_प्रकार bonding_show_bonds(काष्ठा class *cls,
				  काष्ठा class_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा bond_net *bn =
		container_of(attr, काष्ठा bond_net, class_attr_bonding_masters);
	पूर्णांक res = 0;
	काष्ठा bonding *bond;

	rtnl_lock();

	list_क्रम_each_entry(bond, &bn->dev_list, bond_list) अणु
		अगर (res > (PAGE_SIZE - IFNAMSIZ)) अणु
			/* not enough space क्रम another पूर्णांकerface name */
			अगर ((PAGE_SIZE - res) > 10)
				res = PAGE_SIZE - 10;
			res += प्र_लिखो(buf + res, "++more++ ");
			अवरोध;
		पूर्ण
		res += प्र_लिखो(buf + res, "%s ", bond->dev->name);
	पूर्ण
	अगर (res)
		buf[res-1] = '\n'; /* eat the leftover space */

	rtnl_unlock();
	वापस res;
पूर्ण

अटल काष्ठा net_device *bond_get_by_name(काष्ठा bond_net *bn, स्थिर अक्षर *अगरname)
अणु
	काष्ठा bonding *bond;

	list_क्रम_each_entry(bond, &bn->dev_list, bond_list) अणु
		अगर (म_भेदन(bond->dev->name, अगरname, IFNAMSIZ) == 0)
			वापस bond->dev;
	पूर्ण
	वापस शून्य;
पूर्ण

/* "store" function क्रम the bond_masters attribute.  This is what
 * creates and deletes entire bonds.
 *
 * The class parameter is ignored.
 */
अटल sमाप_प्रकार bonding_store_bonds(काष्ठा class *cls,
				   काष्ठा class_attribute *attr,
				   स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	काष्ठा bond_net *bn =
		container_of(attr, काष्ठा bond_net, class_attr_bonding_masters);
	अक्षर command[IFNAMSIZ + 1] = अणु0, पूर्ण;
	अक्षर *अगरname;
	पूर्णांक rv, res = count;

	माला_पूछो(buffer, "%16s", command); /* IFNAMSIZ*/
	अगरname = command + 1;
	अगर ((म_माप(command) <= 1) ||
	    !dev_valid_name(अगरname))
		जाओ err_no_cmd;

	अगर (command[0] == '+') अणु
		pr_info("%s is being created...\n", अगरname);
		rv = bond_create(bn->net, अगरname);
		अगर (rv) अणु
			अगर (rv == -EEXIST)
				pr_info("%s already exists\n", अगरname);
			अन्यथा
				pr_info("%s creation failed\n", अगरname);
			res = rv;
		पूर्ण
	पूर्ण अन्यथा अगर (command[0] == '-') अणु
		काष्ठा net_device *bond_dev;

		rtnl_lock();
		bond_dev = bond_get_by_name(bn, अगरname);
		अगर (bond_dev) अणु
			pr_info("%s is being deleted...\n", अगरname);
			unरेजिस्टर_netdevice(bond_dev);
		पूर्ण अन्यथा अणु
			pr_err("unable to delete non-existent %s\n", अगरname);
			res = -ENODEV;
		पूर्ण
		rtnl_unlock();
	पूर्ण अन्यथा
		जाओ err_no_cmd;

	/* Always वापस either count or an error.  If you वापस 0, you'll
	 * get called क्रमever, which is bad.
	 */
	वापस res;

err_no_cmd:
	pr_err("no command found in bonding_masters - use +ifname or -ifname\n");
	वापस -EPERM;
पूर्ण

/* class attribute क्रम bond_masters file.  This ends up in /sys/class/net */
अटल स्थिर काष्ठा class_attribute class_attr_bonding_masters = अणु
	.attr = अणु
		.name = "bonding_masters",
		.mode = 0644,
	पूर्ण,
	.show = bonding_show_bonds,
	.store = bonding_store_bonds,
पूर्ण;

/* Generic "store" method क्रम bonding sysfs option setting */
अटल sमाप_प्रकार bonding_sysfs_store_option(काष्ठा device *d,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	काष्ठा bonding *bond = to_bond(d);
	स्थिर काष्ठा bond_option *opt;
	अक्षर *buffer_clone;
	पूर्णांक ret;

	opt = bond_opt_get_by_name(attr->attr.name);
	अगर (WARN_ON(!opt))
		वापस -ENOENT;
	buffer_clone = kstrndup(buffer, count, GFP_KERNEL);
	अगर (!buffer_clone)
		वापस -ENOMEM;
	ret = bond_opt_tryset_rtnl(bond, opt->id, buffer_clone);
	अगर (!ret)
		ret = count;
	kमुक्त(buffer_clone);

	वापस ret;
पूर्ण

/* Show the slaves in the current bond. */
अटल sमाप_प्रकार bonding_show_slaves(काष्ठा device *d,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);
	काष्ठा list_head *iter;
	काष्ठा slave *slave;
	पूर्णांक res = 0;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	bond_क्रम_each_slave(bond, slave, iter) अणु
		अगर (res > (PAGE_SIZE - IFNAMSIZ)) अणु
			/* not enough space क्रम another पूर्णांकerface name */
			अगर ((PAGE_SIZE - res) > 10)
				res = PAGE_SIZE - 10;
			res += प्र_लिखो(buf + res, "++more++ ");
			अवरोध;
		पूर्ण
		res += प्र_लिखो(buf + res, "%s ", slave->dev->name);
	पूर्ण

	rtnl_unlock();

	अगर (res)
		buf[res-1] = '\n'; /* eat the leftover space */

	वापस res;
पूर्ण
अटल DEVICE_ATTR(slaves, 0644, bonding_show_slaves,
		   bonding_sysfs_store_option);

/* Show the bonding mode. */
अटल sमाप_प्रकार bonding_show_mode(काष्ठा device *d,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);
	स्थिर काष्ठा bond_opt_value *val;

	val = bond_opt_get_val(BOND_OPT_MODE, BOND_MODE(bond));

	वापस प्र_लिखो(buf, "%s %d\n", val->string, BOND_MODE(bond));
पूर्ण
अटल DEVICE_ATTR(mode, 0644, bonding_show_mode, bonding_sysfs_store_option);

/* Show the bonding transmit hash method. */
अटल sमाप_प्रकार bonding_show_xmit_hash(काष्ठा device *d,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);
	स्थिर काष्ठा bond_opt_value *val;

	val = bond_opt_get_val(BOND_OPT_XMIT_HASH, bond->params.xmit_policy);

	वापस प्र_लिखो(buf, "%s %d\n", val->string, bond->params.xmit_policy);
पूर्ण
अटल DEVICE_ATTR(xmit_hash_policy, 0644,
		   bonding_show_xmit_hash, bonding_sysfs_store_option);

/* Show arp_validate. */
अटल sमाप_प्रकार bonding_show_arp_validate(काष्ठा device *d,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);
	स्थिर काष्ठा bond_opt_value *val;

	val = bond_opt_get_val(BOND_OPT_ARP_VALIDATE,
			       bond->params.arp_validate);

	वापस प्र_लिखो(buf, "%s %d\n", val->string, bond->params.arp_validate);
पूर्ण
अटल DEVICE_ATTR(arp_validate, 0644, bonding_show_arp_validate,
		   bonding_sysfs_store_option);

/* Show arp_all_tarमाला_लो. */
अटल sमाप_प्रकार bonding_show_arp_all_tarमाला_लो(काष्ठा device *d,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);
	स्थिर काष्ठा bond_opt_value *val;

	val = bond_opt_get_val(BOND_OPT_ARP_ALL_TARGETS,
			       bond->params.arp_all_tarमाला_लो);
	वापस प्र_लिखो(buf, "%s %d\n",
		       val->string, bond->params.arp_all_tarमाला_लो);
पूर्ण
अटल DEVICE_ATTR(arp_all_tarमाला_लो, 0644,
		   bonding_show_arp_all_tarमाला_लो, bonding_sysfs_store_option);

/* Show fail_over_mac. */
अटल sमाप_प्रकार bonding_show_fail_over_mac(काष्ठा device *d,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);
	स्थिर काष्ठा bond_opt_value *val;

	val = bond_opt_get_val(BOND_OPT_FAIL_OVER_MAC,
			       bond->params.fail_over_mac);

	वापस प्र_लिखो(buf, "%s %d\n", val->string, bond->params.fail_over_mac);
पूर्ण
अटल DEVICE_ATTR(fail_over_mac, 0644,
		   bonding_show_fail_over_mac, bonding_sysfs_store_option);

/* Show the arp समयr पूर्णांकerval. */
अटल sमाप_प्रकार bonding_show_arp_पूर्णांकerval(काष्ठा device *d,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);

	वापस प्र_लिखो(buf, "%d\n", bond->params.arp_पूर्णांकerval);
पूर्ण
अटल DEVICE_ATTR(arp_पूर्णांकerval, 0644,
		   bonding_show_arp_पूर्णांकerval, bonding_sysfs_store_option);

/* Show the arp tarमाला_लो. */
अटल sमाप_प्रकार bonding_show_arp_tarमाला_लो(काष्ठा device *d,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);
	पूर्णांक i, res = 0;

	क्रम (i = 0; i < BOND_MAX_ARP_TARGETS; i++) अणु
		अगर (bond->params.arp_tarमाला_लो[i])
			res += प्र_लिखो(buf + res, "%pI4 ",
				       &bond->params.arp_tarमाला_लो[i]);
	पूर्ण
	अगर (res)
		buf[res-1] = '\n'; /* eat the leftover space */

	वापस res;
पूर्ण
अटल DEVICE_ATTR(arp_ip_target, 0644,
		   bonding_show_arp_tarमाला_लो, bonding_sysfs_store_option);

/* Show the up and करोwn delays. */
अटल sमाप_प्रकार bonding_show_करोwndelay(काष्ठा device *d,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);

	वापस प्र_लिखो(buf, "%d\n", bond->params.करोwndelay * bond->params.miimon);
पूर्ण
अटल DEVICE_ATTR(करोwndelay, 0644,
		   bonding_show_करोwndelay, bonding_sysfs_store_option);

अटल sमाप_प्रकार bonding_show_updelay(काष्ठा device *d,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);

	वापस प्र_लिखो(buf, "%d\n", bond->params.updelay * bond->params.miimon);

पूर्ण
अटल DEVICE_ATTR(updelay, 0644,
		   bonding_show_updelay, bonding_sysfs_store_option);

अटल sमाप_प्रकार bonding_show_peer_notअगर_delay(काष्ठा device *d,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);

	वापस प्र_लिखो(buf, "%d\n",
		       bond->params.peer_notअगर_delay * bond->params.miimon);
पूर्ण
अटल DEVICE_ATTR(peer_notअगर_delay, 0644,
		   bonding_show_peer_notअगर_delay, bonding_sysfs_store_option);

/* Show the LACP पूर्णांकerval. */
अटल sमाप_प्रकार bonding_show_lacp(काष्ठा device *d,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);
	स्थिर काष्ठा bond_opt_value *val;

	val = bond_opt_get_val(BOND_OPT_LACP_RATE, bond->params.lacp_fast);

	वापस प्र_लिखो(buf, "%s %d\n", val->string, bond->params.lacp_fast);
पूर्ण
अटल DEVICE_ATTR(lacp_rate, 0644,
		   bonding_show_lacp, bonding_sysfs_store_option);

अटल sमाप_प्रकार bonding_show_min_links(काष्ठा device *d,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);

	वापस प्र_लिखो(buf, "%u\n", bond->params.min_links);
पूर्ण
अटल DEVICE_ATTR(min_links, 0644,
		   bonding_show_min_links, bonding_sysfs_store_option);

अटल sमाप_प्रकार bonding_show_ad_select(काष्ठा device *d,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);
	स्थिर काष्ठा bond_opt_value *val;

	val = bond_opt_get_val(BOND_OPT_AD_SELECT, bond->params.ad_select);

	वापस प्र_लिखो(buf, "%s %d\n", val->string, bond->params.ad_select);
पूर्ण
अटल DEVICE_ATTR(ad_select, 0644,
		   bonding_show_ad_select, bonding_sysfs_store_option);

/* Show the number of peer notअगरications to send after a failover event. */
अटल sमाप_प्रकार bonding_show_num_peer_notअगर(काष्ठा device *d,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);
	वापस प्र_लिखो(buf, "%d\n", bond->params.num_peer_notअगर);
पूर्ण
अटल DEVICE_ATTR(num_grat_arp, 0644,
		   bonding_show_num_peer_notअगर, bonding_sysfs_store_option);
अटल DEVICE_ATTR(num_unsol_na, 0644,
		   bonding_show_num_peer_notअगर, bonding_sysfs_store_option);

/* Show the MII monitor पूर्णांकerval. */
अटल sमाप_प्रकार bonding_show_miimon(काष्ठा device *d,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);

	वापस प्र_लिखो(buf, "%d\n", bond->params.miimon);
पूर्ण
अटल DEVICE_ATTR(miimon, 0644,
		   bonding_show_miimon, bonding_sysfs_store_option);

/* Show the primary slave. */
अटल sमाप_प्रकार bonding_show_primary(काष्ठा device *d,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);
	काष्ठा slave *primary;
	पूर्णांक count = 0;

	rcu_पढ़ो_lock();
	primary = rcu_dereference(bond->primary_slave);
	अगर (primary)
		count = प्र_लिखो(buf, "%s\n", primary->dev->name);
	rcu_पढ़ो_unlock();

	वापस count;
पूर्ण
अटल DEVICE_ATTR(primary, 0644,
		   bonding_show_primary, bonding_sysfs_store_option);

/* Show the primary_reselect flag. */
अटल sमाप_प्रकार bonding_show_primary_reselect(काष्ठा device *d,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);
	स्थिर काष्ठा bond_opt_value *val;

	val = bond_opt_get_val(BOND_OPT_PRIMARY_RESELECT,
			       bond->params.primary_reselect);

	वापस प्र_लिखो(buf, "%s %d\n",
		       val->string, bond->params.primary_reselect);
पूर्ण
अटल DEVICE_ATTR(primary_reselect, 0644,
		   bonding_show_primary_reselect, bonding_sysfs_store_option);

/* Show the use_carrier flag. */
अटल sमाप_प्रकार bonding_show_carrier(काष्ठा device *d,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);

	वापस प्र_लिखो(buf, "%d\n", bond->params.use_carrier);
पूर्ण
अटल DEVICE_ATTR(use_carrier, 0644,
		   bonding_show_carrier, bonding_sysfs_store_option);


/* Show currently active_slave. */
अटल sमाप_प्रकार bonding_show_active_slave(काष्ठा device *d,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);
	काष्ठा net_device *slave_dev;
	पूर्णांक count = 0;

	rcu_पढ़ो_lock();
	slave_dev = bond_option_active_slave_get_rcu(bond);
	अगर (slave_dev)
		count = प्र_लिखो(buf, "%s\n", slave_dev->name);
	rcu_पढ़ो_unlock();

	वापस count;
पूर्ण
अटल DEVICE_ATTR(active_slave, 0644,
		   bonding_show_active_slave, bonding_sysfs_store_option);

/* Show link status of the bond पूर्णांकerface. */
अटल sमाप_प्रकार bonding_show_mii_status(काष्ठा device *d,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);
	bool active = netअगर_carrier_ok(bond->dev);

	वापस प्र_लिखो(buf, "%s\n", active ? "up" : "down");
पूर्ण
अटल DEVICE_ATTR(mii_status, 0444, bonding_show_mii_status, शून्य);

/* Show current 802.3ad aggregator ID. */
अटल sमाप_प्रकार bonding_show_ad_aggregator(काष्ठा device *d,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	पूर्णांक count = 0;
	काष्ठा bonding *bond = to_bond(d);

	अगर (BOND_MODE(bond) == BOND_MODE_8023AD) अणु
		काष्ठा ad_info ad_info;
		count = प्र_लिखो(buf, "%d\n",
				bond_3ad_get_active_agg_info(bond, &ad_info)
				?  0 : ad_info.aggregator_id);
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR(ad_aggregator, 0444, bonding_show_ad_aggregator, शून्य);


/* Show number of active 802.3ad ports. */
अटल sमाप_प्रकार bonding_show_ad_num_ports(काष्ठा device *d,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	पूर्णांक count = 0;
	काष्ठा bonding *bond = to_bond(d);

	अगर (BOND_MODE(bond) == BOND_MODE_8023AD) अणु
		काष्ठा ad_info ad_info;
		count = प्र_लिखो(buf, "%d\n",
				bond_3ad_get_active_agg_info(bond, &ad_info)
				?  0 : ad_info.ports);
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR(ad_num_ports, 0444, bonding_show_ad_num_ports, शून्य);


/* Show current 802.3ad actor key. */
अटल sमाप_प्रकार bonding_show_ad_actor_key(काष्ठा device *d,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	पूर्णांक count = 0;
	काष्ठा bonding *bond = to_bond(d);

	अगर (BOND_MODE(bond) == BOND_MODE_8023AD && capable(CAP_NET_ADMIN)) अणु
		काष्ठा ad_info ad_info;
		count = प्र_लिखो(buf, "%d\n",
				bond_3ad_get_active_agg_info(bond, &ad_info)
				?  0 : ad_info.actor_key);
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR(ad_actor_key, 0444, bonding_show_ad_actor_key, शून्य);


/* Show current 802.3ad partner key. */
अटल sमाप_प्रकार bonding_show_ad_partner_key(काष्ठा device *d,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	पूर्णांक count = 0;
	काष्ठा bonding *bond = to_bond(d);

	अगर (BOND_MODE(bond) == BOND_MODE_8023AD && capable(CAP_NET_ADMIN)) अणु
		काष्ठा ad_info ad_info;
		count = प्र_लिखो(buf, "%d\n",
				bond_3ad_get_active_agg_info(bond, &ad_info)
				?  0 : ad_info.partner_key);
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR(ad_partner_key, 0444, bonding_show_ad_partner_key, शून्य);


/* Show current 802.3ad partner mac. */
अटल sमाप_प्रकार bonding_show_ad_partner_mac(काष्ठा device *d,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	पूर्णांक count = 0;
	काष्ठा bonding *bond = to_bond(d);

	अगर (BOND_MODE(bond) == BOND_MODE_8023AD && capable(CAP_NET_ADMIN)) अणु
		काष्ठा ad_info ad_info;
		अगर (!bond_3ad_get_active_agg_info(bond, &ad_info))
			count = प्र_लिखो(buf, "%pM\n", ad_info.partner_प्रणाली);
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR(ad_partner_mac, 0444, bonding_show_ad_partner_mac, शून्य);

/* Show the queue_ids of the slaves in the current bond. */
अटल sमाप_प्रकार bonding_show_queue_id(काष्ठा device *d,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);
	काष्ठा list_head *iter;
	काष्ठा slave *slave;
	पूर्णांक res = 0;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	bond_क्रम_each_slave(bond, slave, iter) अणु
		अगर (res > (PAGE_SIZE - IFNAMSIZ - 6)) अणु
			/* not enough space क्रम another पूर्णांकerface_name:queue_id pair */
			अगर ((PAGE_SIZE - res) > 10)
				res = PAGE_SIZE - 10;
			res += प्र_लिखो(buf + res, "++more++ ");
			अवरोध;
		पूर्ण
		res += प्र_लिखो(buf + res, "%s:%d ",
			       slave->dev->name, slave->queue_id);
	पूर्ण
	अगर (res)
		buf[res-1] = '\n'; /* eat the leftover space */

	rtnl_unlock();

	वापस res;
पूर्ण
अटल DEVICE_ATTR(queue_id, 0644, bonding_show_queue_id,
		   bonding_sysfs_store_option);


/* Show the all_slaves_active flag. */
अटल sमाप_प्रकार bonding_show_slaves_active(काष्ठा device *d,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);

	वापस प्र_लिखो(buf, "%d\n", bond->params.all_slaves_active);
पूर्ण
अटल DEVICE_ATTR(all_slaves_active, 0644,
		   bonding_show_slaves_active, bonding_sysfs_store_option);

/* Show the number of IGMP membership reports to send on link failure */
अटल sमाप_प्रकार bonding_show_resend_igmp(काष्ठा device *d,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);

	वापस प्र_लिखो(buf, "%d\n", bond->params.resend_igmp);
पूर्ण
अटल DEVICE_ATTR(resend_igmp, 0644,
		   bonding_show_resend_igmp, bonding_sysfs_store_option);


अटल sमाप_प्रकार bonding_show_lp_पूर्णांकerval(काष्ठा device *d,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);

	वापस प्र_लिखो(buf, "%d\n", bond->params.lp_पूर्णांकerval);
पूर्ण
अटल DEVICE_ATTR(lp_पूर्णांकerval, 0644,
		   bonding_show_lp_पूर्णांकerval, bonding_sysfs_store_option);

अटल sमाप_प्रकार bonding_show_tlb_dynamic_lb(काष्ठा device *d,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);
	वापस प्र_लिखो(buf, "%d\n", bond->params.tlb_dynamic_lb);
पूर्ण
अटल DEVICE_ATTR(tlb_dynamic_lb, 0644,
		   bonding_show_tlb_dynamic_lb, bonding_sysfs_store_option);

अटल sमाप_प्रकार bonding_show_packets_per_slave(काष्ठा device *d,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);
	अचिन्हित पूर्णांक packets_per_slave = bond->params.packets_per_slave;

	वापस प्र_लिखो(buf, "%u\n", packets_per_slave);
पूर्ण
अटल DEVICE_ATTR(packets_per_slave, 0644,
		   bonding_show_packets_per_slave, bonding_sysfs_store_option);

अटल sमाप_प्रकार bonding_show_ad_actor_sys_prio(काष्ठा device *d,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);

	अगर (BOND_MODE(bond) == BOND_MODE_8023AD && capable(CAP_NET_ADMIN))
		वापस प्र_लिखो(buf, "%hu\n", bond->params.ad_actor_sys_prio);

	वापस 0;
पूर्ण
अटल DEVICE_ATTR(ad_actor_sys_prio, 0644,
		   bonding_show_ad_actor_sys_prio, bonding_sysfs_store_option);

अटल sमाप_प्रकार bonding_show_ad_actor_प्रणाली(काष्ठा device *d,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);

	अगर (BOND_MODE(bond) == BOND_MODE_8023AD && capable(CAP_NET_ADMIN))
		वापस प्र_लिखो(buf, "%pM\n", bond->params.ad_actor_प्रणाली);

	वापस 0;
पूर्ण

अटल DEVICE_ATTR(ad_actor_प्रणाली, 0644,
		   bonding_show_ad_actor_प्रणाली, bonding_sysfs_store_option);

अटल sमाप_प्रकार bonding_show_ad_user_port_key(काष्ठा device *d,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	काष्ठा bonding *bond = to_bond(d);

	अगर (BOND_MODE(bond) == BOND_MODE_8023AD && capable(CAP_NET_ADMIN))
		वापस प्र_लिखो(buf, "%hu\n", bond->params.ad_user_port_key);

	वापस 0;
पूर्ण
अटल DEVICE_ATTR(ad_user_port_key, 0644,
		   bonding_show_ad_user_port_key, bonding_sysfs_store_option);

अटल काष्ठा attribute *per_bond_attrs[] = अणु
	&dev_attr_slaves.attr,
	&dev_attr_mode.attr,
	&dev_attr_fail_over_mac.attr,
	&dev_attr_arp_validate.attr,
	&dev_attr_arp_all_tarमाला_लो.attr,
	&dev_attr_arp_पूर्णांकerval.attr,
	&dev_attr_arp_ip_target.attr,
	&dev_attr_करोwndelay.attr,
	&dev_attr_updelay.attr,
	&dev_attr_peer_notअगर_delay.attr,
	&dev_attr_lacp_rate.attr,
	&dev_attr_ad_select.attr,
	&dev_attr_xmit_hash_policy.attr,
	&dev_attr_num_grat_arp.attr,
	&dev_attr_num_unsol_na.attr,
	&dev_attr_miimon.attr,
	&dev_attr_primary.attr,
	&dev_attr_primary_reselect.attr,
	&dev_attr_use_carrier.attr,
	&dev_attr_active_slave.attr,
	&dev_attr_mii_status.attr,
	&dev_attr_ad_aggregator.attr,
	&dev_attr_ad_num_ports.attr,
	&dev_attr_ad_actor_key.attr,
	&dev_attr_ad_partner_key.attr,
	&dev_attr_ad_partner_mac.attr,
	&dev_attr_queue_id.attr,
	&dev_attr_all_slaves_active.attr,
	&dev_attr_resend_igmp.attr,
	&dev_attr_min_links.attr,
	&dev_attr_lp_पूर्णांकerval.attr,
	&dev_attr_packets_per_slave.attr,
	&dev_attr_tlb_dynamic_lb.attr,
	&dev_attr_ad_actor_sys_prio.attr,
	&dev_attr_ad_actor_प्रणाली.attr,
	&dev_attr_ad_user_port_key.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group bonding_group = अणु
	.name = "bonding",
	.attrs = per_bond_attrs,
पूर्ण;

/* Initialize sysfs.  This sets up the bonding_masters file in
 * /sys/class/net.
 */
पूर्णांक bond_create_sysfs(काष्ठा bond_net *bn)
अणु
	पूर्णांक ret;

	bn->class_attr_bonding_masters = class_attr_bonding_masters;
	sysfs_attr_init(&bn->class_attr_bonding_masters.attr);

	ret = netdev_class_create_file_ns(&bn->class_attr_bonding_masters,
					  bn->net);
	/* Permit multiple loads of the module by ignoring failures to
	 * create the bonding_masters sysfs file.  Bonding devices
	 * created by second or subsequent loads of the module will
	 * not be listed in, or controllable by, bonding_masters, but
	 * will have the usual "bonding" sysfs directory.
	 *
	 * This is करोne to preserve backwards compatibility क्रम
	 * initscripts/sysconfig, which load bonding multiple बार to
	 * configure multiple bonding devices.
	 */
	अगर (ret == -EEXIST) अणु
		/* Is someone being kinky and naming a device bonding_master? */
		अगर (__dev_get_by_name(bn->net,
				      class_attr_bonding_masters.attr.name))
			pr_err("network device named %s already exists in sysfs\n",
			       class_attr_bonding_masters.attr.name);
		ret = 0;
	पूर्ण

	वापस ret;

पूर्ण

/* Remove /sys/class/net/bonding_masters. */
व्योम bond_destroy_sysfs(काष्ठा bond_net *bn)
अणु
	netdev_class_हटाओ_file_ns(&bn->class_attr_bonding_masters, bn->net);
पूर्ण

/* Initialize sysfs क्रम each bond.  This sets up and रेजिस्टरs
 * the 'bondctl' directory क्रम each inभागidual bond under /sys/class/net.
 */
व्योम bond_prepare_sysfs_group(काष्ठा bonding *bond)
अणु
	bond->dev->sysfs_groups[0] = &bonding_group;
पूर्ण

