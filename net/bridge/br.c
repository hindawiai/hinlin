<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Generic parts
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Lennert Buytenhek		<buytenh@gnu.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/llc.h>
#समावेश <net/llc.h>
#समावेश <net/stp.h>
#समावेश <net/चयनdev.h>

#समावेश "br_private.h"

/*
 * Handle changes in state of network devices enslaved to a bridge.
 *
 * Note: करोn't care about up/करोwn अगर bridge itself is करोwn, because
 *     port state is checked when bridge is brought up.
 */
अटल पूर्णांक br_device_event(काष्ठा notअगरier_block *unused, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा netlink_ext_ack *extack = netdev_notअगरier_info_to_extack(ptr);
	काष्ठा netdev_notअगरier_pre_changeaddr_info *prechaddr_info;
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा net_bridge_port *p;
	काष्ठा net_bridge *br;
	bool notअगरied = false;
	bool changed_addr;
	पूर्णांक err;

	अगर (dev->priv_flags & IFF_EBRIDGE) अणु
		err = br_vlan_bridge_event(dev, event, ptr);
		अगर (err)
			वापस notअगरier_from_त्रुटि_सं(err);

		अगर (event == NETDEV_REGISTER) अणु
			/* रेजिस्टर of bridge completed, add sysfs entries */
			err = br_sysfs_addbr(dev);
			अगर (err)
				वापस notअगरier_from_त्रुटि_सं(err);

			वापस NOTIFY_DONE;
		पूर्ण
	पूर्ण

	/* not a port of a bridge */
	p = br_port_get_rtnl(dev);
	अगर (!p)
		वापस NOTIFY_DONE;

	br = p->br;

	चयन (event) अणु
	हाल NETDEV_CHANGEMTU:
		br_mtu_स्वतः_adjust(br);
		अवरोध;

	हाल NETDEV_PRE_CHANGEADDR:
		अगर (br->dev->addr_assign_type == NET_ADDR_SET)
			अवरोध;
		prechaddr_info = ptr;
		err = dev_pre_changeaddr_notअगरy(br->dev,
						prechaddr_info->dev_addr,
						extack);
		अगर (err)
			वापस notअगरier_from_त्रुटि_सं(err);
		अवरोध;

	हाल NETDEV_CHANGEADDR:
		spin_lock_bh(&br->lock);
		br_fdb_changeaddr(p, dev->dev_addr);
		changed_addr = br_stp_recalculate_bridge_id(br);
		spin_unlock_bh(&br->lock);

		अगर (changed_addr)
			call_netdevice_notअगरiers(NETDEV_CHANGEADDR, br->dev);

		अवरोध;

	हाल NETDEV_CHANGE:
		br_port_carrier_check(p, &notअगरied);
		अवरोध;

	हाल NETDEV_FEAT_CHANGE:
		netdev_update_features(br->dev);
		अवरोध;

	हाल NETDEV_DOWN:
		spin_lock_bh(&br->lock);
		अगर (br->dev->flags & IFF_UP) अणु
			br_stp_disable_port(p);
			notअगरied = true;
		पूर्ण
		spin_unlock_bh(&br->lock);
		अवरोध;

	हाल NETDEV_UP:
		अगर (netअगर_running(br->dev) && netअगर_oper_up(dev)) अणु
			spin_lock_bh(&br->lock);
			br_stp_enable_port(p);
			notअगरied = true;
			spin_unlock_bh(&br->lock);
		पूर्ण
		अवरोध;

	हाल NETDEV_UNREGISTER:
		br_del_अगर(br, dev);
		अवरोध;

	हाल NETDEV_CHANGENAME:
		err = br_sysfs_नामअगर(p);
		अगर (err)
			वापस notअगरier_from_त्रुटि_सं(err);
		अवरोध;

	हाल NETDEV_PRE_TYPE_CHANGE:
		/* Forbid underlying device to change its type. */
		वापस NOTIFY_BAD;

	हाल NETDEV_RESEND_IGMP:
		/* Propagate to master device */
		call_netdevice_notअगरiers(event, br->dev);
		अवरोध;
	पूर्ण

	अगर (event != NETDEV_UNREGISTER)
		br_vlan_port_event(p, event);

	/* Events that may cause spanning tree to refresh */
	अगर (!notअगरied && (event == NETDEV_CHANGEADDR || event == NETDEV_UP ||
			  event == NETDEV_CHANGE || event == NETDEV_DOWN))
		br_अगरinfo_notअगरy(RTM_NEWLINK, शून्य, p);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block br_device_notअगरier = अणु
	.notअगरier_call = br_device_event
पूर्ण;

/* called with RTNL or RCU */
अटल पूर्णांक br_चयनdev_event(काष्ठा notअगरier_block *unused,
			      अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = चयनdev_notअगरier_info_to_dev(ptr);
	काष्ठा net_bridge_port *p;
	काष्ठा net_bridge *br;
	काष्ठा चयनdev_notअगरier_fdb_info *fdb_info;
	पूर्णांक err = NOTIFY_DONE;

	p = br_port_get_rtnl_rcu(dev);
	अगर (!p)
		जाओ out;

	br = p->br;

	चयन (event) अणु
	हाल SWITCHDEV_FDB_ADD_TO_BRIDGE:
		fdb_info = ptr;
		err = br_fdb_बाह्यal_learn_add(br, p, fdb_info->addr,
						fdb_info->vid, false);
		अगर (err) अणु
			err = notअगरier_from_त्रुटि_सं(err);
			अवरोध;
		पूर्ण
		br_fdb_offloaded_set(br, p, fdb_info->addr,
				     fdb_info->vid, true);
		अवरोध;
	हाल SWITCHDEV_FDB_DEL_TO_BRIDGE:
		fdb_info = ptr;
		err = br_fdb_बाह्यal_learn_del(br, p, fdb_info->addr,
						fdb_info->vid, false);
		अगर (err)
			err = notअगरier_from_त्रुटि_सं(err);
		अवरोध;
	हाल SWITCHDEV_FDB_OFFLOADED:
		fdb_info = ptr;
		br_fdb_offloaded_set(br, p, fdb_info->addr,
				     fdb_info->vid, fdb_info->offloaded);
		अवरोध;
	हाल SWITCHDEV_FDB_FLUSH_TO_BRIDGE:
		fdb_info = ptr;
		/* Don't delete अटल entries */
		br_fdb_delete_by_port(br, p, fdb_info->vid, 0);
		अवरोध;
	पूर्ण

out:
	वापस err;
पूर्ण

अटल काष्ठा notअगरier_block br_चयनdev_notअगरier = अणु
	.notअगरier_call = br_चयनdev_event,
पूर्ण;

/* br_boolopt_toggle - change user-controlled boolean option
 *
 * @br: bridge device
 * @opt: id of the option to change
 * @on: new option value
 * @extack: extack क्रम error messages
 *
 * Changes the value of the respective boolean option to @on taking care of
 * any पूर्णांकernal option value mapping and configuration.
 */
पूर्णांक br_boolopt_toggle(काष्ठा net_bridge *br, क्रमागत br_boolopt_id opt, bool on,
		      काष्ठा netlink_ext_ack *extack)
अणु
	चयन (opt) अणु
	हाल BR_BOOLOPT_NO_LL_LEARN:
		br_opt_toggle(br, BROPT_NO_LL_LEARN, on);
		अवरोध;
	शेष:
		/* shouldn't be called with unsupported options */
		WARN_ON(1);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक br_boolopt_get(स्थिर काष्ठा net_bridge *br, क्रमागत br_boolopt_id opt)
अणु
	चयन (opt) अणु
	हाल BR_BOOLOPT_NO_LL_LEARN:
		वापस br_opt_get(br, BROPT_NO_LL_LEARN);
	शेष:
		/* shouldn't be called with unsupported options */
		WARN_ON(1);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक br_boolopt_multi_toggle(काष्ठा net_bridge *br,
			    काष्ठा br_boolopt_multi *bm,
			    काष्ठा netlink_ext_ack *extack)
अणु
	अचिन्हित दीर्घ biपंचांगap = bm->opपंचांगask;
	पूर्णांक err = 0;
	पूर्णांक opt_id;

	क्रम_each_set_bit(opt_id, &biपंचांगap, BR_BOOLOPT_MAX) अणु
		bool on = !!(bm->optval & BIT(opt_id));

		err = br_boolopt_toggle(br, opt_id, on, extack);
		अगर (err) अणु
			br_debug(br, "boolopt multi-toggle error: option: %d current: %d new: %d error: %d\n",
				 opt_id, br_boolopt_get(br, opt_id), on, err);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

व्योम br_boolopt_multi_get(स्थिर काष्ठा net_bridge *br,
			  काष्ठा br_boolopt_multi *bm)
अणु
	u32 optval = 0;
	पूर्णांक opt_id;

	क्रम (opt_id = 0; opt_id < BR_BOOLOPT_MAX; opt_id++)
		optval |= (br_boolopt_get(br, opt_id) << opt_id);

	bm->optval = optval;
	bm->opपंचांगask = GENMASK((BR_BOOLOPT_MAX - 1), 0);
पूर्ण

/* निजी bridge options, controlled by the kernel */
व्योम br_opt_toggle(काष्ठा net_bridge *br, क्रमागत net_bridge_opts opt, bool on)
अणु
	bool cur = !!br_opt_get(br, opt);

	br_debug(br, "toggle option: %d state: %d -> %d\n",
		 opt, cur, on);

	अगर (cur == on)
		वापस;

	अगर (on)
		set_bit(opt, &br->options);
	अन्यथा
		clear_bit(opt, &br->options);
पूर्ण

अटल व्योम __net_निकास br_net_निकास(काष्ठा net *net)
अणु
	काष्ठा net_device *dev;
	LIST_HEAD(list);

	rtnl_lock();
	क्रम_each_netdev(net, dev)
		अगर (dev->priv_flags & IFF_EBRIDGE)
			br_dev_delete(dev, &list);

	unरेजिस्टर_netdevice_many(&list);
	rtnl_unlock();

पूर्ण

अटल काष्ठा pernet_operations br_net_ops = अणु
	.निकास	= br_net_निकास,
पूर्ण;

अटल स्थिर काष्ठा stp_proto br_stp_proto = अणु
	.rcv	= br_stp_rcv,
पूर्ण;

अटल पूर्णांक __init br_init(व्योम)
अणु
	पूर्णांक err;

	BUILD_BUG_ON(माप(काष्ठा br_input_skb_cb) > माप_field(काष्ठा sk_buff, cb));

	err = stp_proto_रेजिस्टर(&br_stp_proto);
	अगर (err < 0) अणु
		pr_err("bridge: can't register sap for STP\n");
		वापस err;
	पूर्ण

	err = br_fdb_init();
	अगर (err)
		जाओ err_out;

	err = रेजिस्टर_pernet_subsys(&br_net_ops);
	अगर (err)
		जाओ err_out1;

	err = br_nf_core_init();
	अगर (err)
		जाओ err_out2;

	err = रेजिस्टर_netdevice_notअगरier(&br_device_notअगरier);
	अगर (err)
		जाओ err_out3;

	err = रेजिस्टर_चयनdev_notअगरier(&br_चयनdev_notअगरier);
	अगर (err)
		जाओ err_out4;

	err = br_netlink_init();
	अगर (err)
		जाओ err_out5;

	brioctl_set(br_ioctl_deviceless_stub);

#अगर IS_ENABLED(CONFIG_ATM_LANE)
	br_fdb_test_addr_hook = br_fdb_test_addr;
#पूर्ण_अगर

#अगर IS_MODULE(CONFIG_BRIDGE_NETFILTER)
	pr_info("bridge: filtering via arp/ip/ip6tables is no longer available "
		"by default. Update your scripts to load br_netfilter if you "
		"need this.\n");
#पूर्ण_अगर

	वापस 0;

err_out5:
	unरेजिस्टर_चयनdev_notअगरier(&br_चयनdev_notअगरier);
err_out4:
	unरेजिस्टर_netdevice_notअगरier(&br_device_notअगरier);
err_out3:
	br_nf_core_fini();
err_out2:
	unरेजिस्टर_pernet_subsys(&br_net_ops);
err_out1:
	br_fdb_fini();
err_out:
	stp_proto_unरेजिस्टर(&br_stp_proto);
	वापस err;
पूर्ण

अटल व्योम __निकास br_deinit(व्योम)
अणु
	stp_proto_unरेजिस्टर(&br_stp_proto);
	br_netlink_fini();
	unरेजिस्टर_चयनdev_notअगरier(&br_चयनdev_notअगरier);
	unरेजिस्टर_netdevice_notअगरier(&br_device_notअगरier);
	brioctl_set(शून्य);
	unरेजिस्टर_pernet_subsys(&br_net_ops);

	rcu_barrier(); /* Wait क्रम completion of call_rcu()'s */

	br_nf_core_fini();
#अगर IS_ENABLED(CONFIG_ATM_LANE)
	br_fdb_test_addr_hook = शून्य;
#पूर्ण_अगर
	br_fdb_fini();
पूर्ण

module_init(br_init)
module_निकास(br_deinit)
MODULE_LICENSE("GPL");
MODULE_VERSION(BR_VERSION);
MODULE_ALIAS_RTNL_LINK("bridge");
