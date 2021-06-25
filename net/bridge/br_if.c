<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Userspace पूर्णांकerface
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Lennert Buytenhek		<buytenh@gnu.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/netpoll.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/slab.h>
#समावेश <net/dsa.h>
#समावेश <net/sock.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/चयनdev.h>
#समावेश <net/net_namespace.h>

#समावेश "br_private.h"

/*
 * Determine initial path cost based on speed.
 * using recommendations from 802.1d standard
 *
 * Since driver might sleep need to not be holding any locks.
 */
अटल पूर्णांक port_cost(काष्ठा net_device *dev)
अणु
	काष्ठा ethtool_link_ksettings ecmd;

	अगर (!__ethtool_get_link_ksettings(dev, &ecmd)) अणु
		चयन (ecmd.base.speed) अणु
		हाल SPEED_10000:
			वापस 2;
		हाल SPEED_1000:
			वापस 4;
		हाल SPEED_100:
			वापस 19;
		हाल SPEED_10:
			वापस 100;
		पूर्ण
	पूर्ण

	/* Old silly heuristics based on name */
	अगर (!म_भेदन(dev->name, "lec", 3))
		वापस 7;

	अगर (!म_भेदन(dev->name, "plip", 4))
		वापस 2500;

	वापस 100;	/* assume old 10Mbps */
पूर्ण


/* Check क्रम port carrier transitions. */
व्योम br_port_carrier_check(काष्ठा net_bridge_port *p, bool *notअगरied)
अणु
	काष्ठा net_device *dev = p->dev;
	काष्ठा net_bridge *br = p->br;

	अगर (!(p->flags & BR_ADMIN_COST) &&
	    netअगर_running(dev) && netअगर_oper_up(dev))
		p->path_cost = port_cost(dev);

	*notअगरied = false;
	अगर (!netअगर_running(br->dev))
		वापस;

	spin_lock_bh(&br->lock);
	अगर (netअगर_running(dev) && netअगर_oper_up(dev)) अणु
		अगर (p->state == BR_STATE_DISABLED) अणु
			br_stp_enable_port(p);
			*notअगरied = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (p->state != BR_STATE_DISABLED) अणु
			br_stp_disable_port(p);
			*notअगरied = true;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&br->lock);
पूर्ण

अटल व्योम br_port_set_promisc(काष्ठा net_bridge_port *p)
अणु
	पूर्णांक err = 0;

	अगर (br_promisc_port(p))
		वापस;

	err = dev_set_promiscuity(p->dev, 1);
	अगर (err)
		वापस;

	br_fdb_unsync_अटल(p->br, p);
	p->flags |= BR_PROMISC;
पूर्ण

अटल व्योम br_port_clear_promisc(काष्ठा net_bridge_port *p)
अणु
	पूर्णांक err;

	/* Check अगर the port is alपढ़ोy non-promisc or अगर it करोesn't
	 * support UNICAST filtering.  Without unicast filtering support
	 * we'll end up re-enabling promisc mode anyway, so just check क्रम
	 * it here.
	 */
	अगर (!br_promisc_port(p) || !(p->dev->priv_flags & IFF_UNICAST_FLT))
		वापस;

	/* Since we'll be clearing the promisc mode, program the port
	 * first so that we करोn't have पूर्णांकerruption in traffic.
	 */
	err = br_fdb_sync_अटल(p->br, p);
	अगर (err)
		वापस;

	dev_set_promiscuity(p->dev, -1);
	p->flags &= ~BR_PROMISC;
पूर्ण

/* When a port is added or हटाओd or when certain port flags
 * change, this function is called to स्वतःmatically manage
 * promiscuity setting of all the bridge ports.  We are always called
 * under RTNL so can skip using rcu primitives.
 */
व्योम br_manage_promisc(काष्ठा net_bridge *br)
अणु
	काष्ठा net_bridge_port *p;
	bool set_all = false;

	/* If vlan filtering is disabled or bridge पूर्णांकerface is placed
	 * पूर्णांकo promiscuous mode, place all ports in promiscuous mode.
	 */
	अगर ((br->dev->flags & IFF_PROMISC) || !br_vlan_enabled(br->dev))
		set_all = true;

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		अगर (set_all) अणु
			br_port_set_promisc(p);
		पूर्ण अन्यथा अणु
			/* If the number of स्वतः-ports is <= 1, then all other
			 * ports will have their output configuration
			 * अटलally specअगरied through fdbs.  Since ingress
			 * on the स्वतः-port becomes क्रमwarding/egress to other
			 * ports and egress configuration is अटलally known,
			 * we can say that ingress configuration of the
			 * स्वतः-port is also अटलally known.
			 * This lets us disable promiscuous mode and ग_लिखो
			 * this config to hw.
			 */
			अगर (br->स्वतः_cnt == 0 ||
			    (br->स्वतः_cnt == 1 && br_स्वतः_port(p)))
				br_port_clear_promisc(p);
			अन्यथा
				br_port_set_promisc(p);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक nbp_backup_change(काष्ठा net_bridge_port *p,
		      काष्ठा net_device *backup_dev)
अणु
	काष्ठा net_bridge_port *old_backup = rtnl_dereference(p->backup_port);
	काष्ठा net_bridge_port *backup_p = शून्य;

	ASSERT_RTNL();

	अगर (backup_dev) अणु
		अगर (!netअगर_is_bridge_port(backup_dev))
			वापस -ENOENT;

		backup_p = br_port_get_rtnl(backup_dev);
		अगर (backup_p->br != p->br)
			वापस -EINVAL;
	पूर्ण

	अगर (p == backup_p)
		वापस -EINVAL;

	अगर (old_backup == backup_p)
		वापस 0;

	/* अगर the backup link is alपढ़ोy set, clear it */
	अगर (old_backup)
		old_backup->backup_redirected_cnt--;

	अगर (backup_p)
		backup_p->backup_redirected_cnt++;
	rcu_assign_poपूर्णांकer(p->backup_port, backup_p);

	वापस 0;
पूर्ण

अटल व्योम nbp_backup_clear(काष्ठा net_bridge_port *p)
अणु
	nbp_backup_change(p, शून्य);
	अगर (p->backup_redirected_cnt) अणु
		काष्ठा net_bridge_port *cur_p;

		list_क्रम_each_entry(cur_p, &p->br->port_list, list) अणु
			काष्ठा net_bridge_port *backup_p;

			backup_p = rtnl_dereference(cur_p->backup_port);
			अगर (backup_p == p)
				nbp_backup_change(cur_p, शून्य);
		पूर्ण
	पूर्ण

	WARN_ON(rcu_access_poपूर्णांकer(p->backup_port) || p->backup_redirected_cnt);
पूर्ण

अटल व्योम nbp_update_port_count(काष्ठा net_bridge *br)
अणु
	काष्ठा net_bridge_port *p;
	u32 cnt = 0;

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		अगर (br_स्वतः_port(p))
			cnt++;
	पूर्ण
	अगर (br->स्वतः_cnt != cnt) अणु
		br->स्वतः_cnt = cnt;
		br_manage_promisc(br);
	पूर्ण
पूर्ण

अटल व्योम nbp_delete_promisc(काष्ठा net_bridge_port *p)
अणु
	/* If port is currently promiscuous, unset promiscuity.
	 * Otherwise, it is a अटल port so हटाओ all addresses
	 * from it.
	 */
	dev_set_allmulti(p->dev, -1);
	अगर (br_promisc_port(p))
		dev_set_promiscuity(p->dev, -1);
	अन्यथा
		br_fdb_unsync_अटल(p->br, p);
पूर्ण

अटल व्योम release_nbp(काष्ठा kobject *kobj)
अणु
	काष्ठा net_bridge_port *p
		= container_of(kobj, काष्ठा net_bridge_port, kobj);
	kमुक्त(p);
पूर्ण

अटल व्योम brport_get_ownership(काष्ठा kobject *kobj, kuid_t *uid, kgid_t *gid)
अणु
	काष्ठा net_bridge_port *p = kobj_to_brport(kobj);

	net_ns_get_ownership(dev_net(p->dev), uid, gid);
पूर्ण

अटल काष्ठा kobj_type brport_ktype = अणु
#अगर_घोषित CONFIG_SYSFS
	.sysfs_ops = &brport_sysfs_ops,
#पूर्ण_अगर
	.release = release_nbp,
	.get_ownership = brport_get_ownership,
पूर्ण;

अटल व्योम destroy_nbp(काष्ठा net_bridge_port *p)
अणु
	काष्ठा net_device *dev = p->dev;

	p->br = शून्य;
	p->dev = शून्य;
	dev_put(dev);

	kobject_put(&p->kobj);
पूर्ण

अटल व्योम destroy_nbp_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा net_bridge_port *p =
			container_of(head, काष्ठा net_bridge_port, rcu);
	destroy_nbp(p);
पूर्ण

अटल अचिन्हित get_max_headroom(काष्ठा net_bridge *br)
अणु
	अचिन्हित max_headroom = 0;
	काष्ठा net_bridge_port *p;

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		अचिन्हित dev_headroom = netdev_get_fwd_headroom(p->dev);

		अगर (dev_headroom > max_headroom)
			max_headroom = dev_headroom;
	पूर्ण

	वापस max_headroom;
पूर्ण

अटल व्योम update_headroom(काष्ठा net_bridge *br, पूर्णांक new_hr)
अणु
	काष्ठा net_bridge_port *p;

	list_क्रम_each_entry(p, &br->port_list, list)
		netdev_set_rx_headroom(p->dev, new_hr);

	br->dev->needed_headroom = new_hr;
पूर्ण

/* Delete port(पूर्णांकerface) from bridge is करोne in two steps.
 * via RCU. First step, marks device as करोwn. That deletes
 * all the समयrs and stops new packets from flowing through.
 *
 * Final cleanup करोesn't occur until after all CPU's finished
 * processing packets.
 *
 * Protected from multiple admin operations by RTNL mutex
 */
अटल व्योम del_nbp(काष्ठा net_bridge_port *p)
अणु
	काष्ठा net_bridge *br = p->br;
	काष्ठा net_device *dev = p->dev;

	sysfs_हटाओ_link(br->अगरobj, p->dev->name);

	nbp_delete_promisc(p);

	spin_lock_bh(&br->lock);
	br_stp_disable_port(p);
	spin_unlock_bh(&br->lock);

	br_mrp_port_del(br, p);
	br_cfm_port_del(br, p);

	br_अगरinfo_notअगरy(RTM_DELLINK, शून्य, p);

	list_del_rcu(&p->list);
	अगर (netdev_get_fwd_headroom(dev) == br->dev->needed_headroom)
		update_headroom(br, get_max_headroom(br));
	netdev_reset_rx_headroom(dev);

	nbp_vlan_flush(p);
	br_fdb_delete_by_port(br, p, 0, 1);
	चयनdev_deferred_process();
	nbp_backup_clear(p);

	nbp_update_port_count(br);

	netdev_upper_dev_unlink(dev, br->dev);

	dev->priv_flags &= ~IFF_BRIDGE_PORT;

	netdev_rx_handler_unरेजिस्टर(dev);

	br_multicast_del_port(p);

	kobject_uevent(&p->kobj, KOBJ_REMOVE);
	kobject_del(&p->kobj);

	br_netpoll_disable(p);

	call_rcu(&p->rcu, destroy_nbp_rcu);
पूर्ण

/* Delete bridge device */
व्योम br_dev_delete(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);
	काष्ठा net_bridge_port *p, *n;

	list_क्रम_each_entry_safe(p, n, &br->port_list, list) अणु
		del_nbp(p);
	पूर्ण

	br_recalculate_neigh_suppress_enabled(br);

	br_fdb_delete_by_port(br, शून्य, 0, 1);

	cancel_delayed_work_sync(&br->gc_work);

	br_sysfs_delbr(br->dev);
	unरेजिस्टर_netdevice_queue(br->dev, head);
पूर्ण

/* find an available port number */
अटल पूर्णांक find_portno(काष्ठा net_bridge *br)
अणु
	पूर्णांक index;
	काष्ठा net_bridge_port *p;
	अचिन्हित दीर्घ *inuse;

	inuse = biपंचांगap_zalloc(BR_MAX_PORTS, GFP_KERNEL);
	अगर (!inuse)
		वापस -ENOMEM;

	set_bit(0, inuse);	/* zero is reserved */
	list_क्रम_each_entry(p, &br->port_list, list) अणु
		set_bit(p->port_no, inuse);
	पूर्ण
	index = find_first_zero_bit(inuse, BR_MAX_PORTS);
	biपंचांगap_मुक्त(inuse);

	वापस (index >= BR_MAX_PORTS) ? -EXFULL : index;
पूर्ण

/* called with RTNL but without bridge lock */
अटल काष्ठा net_bridge_port *new_nbp(काष्ठा net_bridge *br,
				       काष्ठा net_device *dev)
अणु
	काष्ठा net_bridge_port *p;
	पूर्णांक index, err;

	index = find_portno(br);
	अगर (index < 0)
		वापस ERR_PTR(index);

	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (p == शून्य)
		वापस ERR_PTR(-ENOMEM);

	p->br = br;
	dev_hold(dev);
	p->dev = dev;
	p->path_cost = port_cost(dev);
	p->priority = 0x8000 >> BR_PORT_BITS;
	p->port_no = index;
	p->flags = BR_LEARNING | BR_FLOOD | BR_MCAST_FLOOD | BR_BCAST_FLOOD;
	br_init_port(p);
	br_set_state(p, BR_STATE_DISABLED);
	br_stp_port_समयr_init(p);
	err = br_multicast_add_port(p);
	अगर (err) अणु
		dev_put(dev);
		kमुक्त(p);
		p = ERR_PTR(err);
	पूर्ण

	वापस p;
पूर्ण

पूर्णांक br_add_bridge(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा net_device *dev;
	पूर्णांक res;

	dev = alloc_netdev(माप(काष्ठा net_bridge), name, NET_NAME_UNKNOWN,
			   br_dev_setup);

	अगर (!dev)
		वापस -ENOMEM;

	dev_net_set(dev, net);
	dev->rtnl_link_ops = &br_link_ops;

	res = रेजिस्टर_netdev(dev);
	अगर (res)
		मुक्त_netdev(dev);
	वापस res;
पूर्ण

पूर्णांक br_del_bridge(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा net_device *dev;
	पूर्णांक ret = 0;

	rtnl_lock();
	dev = __dev_get_by_name(net, name);
	अगर (dev == शून्य)
		ret =  -ENXIO; 	/* Could not find device */

	अन्यथा अगर (!(dev->priv_flags & IFF_EBRIDGE)) अणु
		/* Attempt to delete non bridge device! */
		ret = -EPERM;
	पूर्ण

	अन्यथा अगर (dev->flags & IFF_UP) अणु
		/* Not shutकरोwn yet. */
		ret = -EBUSY;
	पूर्ण

	अन्यथा
		br_dev_delete(dev, शून्य);

	rtnl_unlock();
	वापस ret;
पूर्ण

/* MTU of the bridge pseuकरो-device: ETH_DATA_LEN or the minimum of the ports */
अटल पूर्णांक br_mtu_min(स्थिर काष्ठा net_bridge *br)
अणु
	स्थिर काष्ठा net_bridge_port *p;
	पूर्णांक ret_mtu = 0;

	list_क्रम_each_entry(p, &br->port_list, list)
		अगर (!ret_mtu || ret_mtu > p->dev->mtu)
			ret_mtu = p->dev->mtu;

	वापस ret_mtu ? ret_mtu : ETH_DATA_LEN;
पूर्ण

व्योम br_mtu_स्वतः_adjust(काष्ठा net_bridge *br)
अणु
	ASSERT_RTNL();

	/* अगर the bridge MTU was manually configured करोn't mess with it */
	अगर (br_opt_get(br, BROPT_MTU_SET_BY_USER))
		वापस;

	/* change to the minimum MTU and clear the flag which was set by
	 * the bridge nकरो_change_mtu callback
	 */
	dev_set_mtu(br->dev, br_mtu_min(br));
	br_opt_toggle(br, BROPT_MTU_SET_BY_USER, false);
पूर्ण

अटल व्योम br_set_gso_limits(काष्ठा net_bridge *br)
अणु
	अचिन्हित पूर्णांक gso_max_size = GSO_MAX_SIZE;
	u16 gso_max_segs = GSO_MAX_SEGS;
	स्थिर काष्ठा net_bridge_port *p;

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		gso_max_size = min(gso_max_size, p->dev->gso_max_size);
		gso_max_segs = min(gso_max_segs, p->dev->gso_max_segs);
	पूर्ण
	br->dev->gso_max_size = gso_max_size;
	br->dev->gso_max_segs = gso_max_segs;
पूर्ण

/*
 * Recomputes features using slave's features
 */
netdev_features_t br_features_recompute(काष्ठा net_bridge *br,
	netdev_features_t features)
अणु
	काष्ठा net_bridge_port *p;
	netdev_features_t mask;

	अगर (list_empty(&br->port_list))
		वापस features;

	mask = features;
	features &= ~NETIF_F_ONE_FOR_ALL;

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		features = netdev_increment_features(features,
						     p->dev->features, mask);
	पूर्ण
	features = netdev_add_tso_features(features, mask);

	वापस features;
पूर्ण

/* called with RTNL */
पूर्णांक br_add_अगर(काष्ठा net_bridge *br, काष्ठा net_device *dev,
	      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_bridge_port *p;
	पूर्णांक err = 0;
	अचिन्हित br_hr, dev_hr;
	bool changed_addr;

	/* Don't allow bridging non-ethernet like devices. */
	अगर ((dev->flags & IFF_LOOPBACK) ||
	    dev->type != ARPHRD_ETHER || dev->addr_len != ETH_ALEN ||
	    !is_valid_ether_addr(dev->dev_addr))
		वापस -EINVAL;

	/* Also करोn't allow bridging of net devices that are DSA masters, since
	 * the bridge layer rx_handler prevents the DSA fake ethertype handler
	 * to be invoked, so we करोn't get the chance to strip off and parse the
	 * DSA चयन tag protocol header (the bridge layer just वापसs
	 * RX_HANDLER_CONSUMED, stopping RX processing क्रम these frames).
	 * The only हाल where that would not be an issue is when bridging can
	 * alपढ़ोy be offloaded, such as when the DSA master is itself a DSA
	 * or plain चयनdev port, and is bridged only with other ports from
	 * the same hardware device.
	 */
	अगर (netdev_uses_dsa(dev)) अणु
		list_क्रम_each_entry(p, &br->port_list, list) अणु
			अगर (!netdev_port_same_parent_id(dev, p->dev)) अणु
				NL_SET_ERR_MSG(extack,
					       "Cannot do software bridging with a DSA master");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	/* No bridging of bridges */
	अगर (dev->netdev_ops->nकरो_start_xmit == br_dev_xmit) अणु
		NL_SET_ERR_MSG(extack,
			       "Can not enslave a bridge to a bridge");
		वापस -ELOOP;
	पूर्ण

	/* Device has master upper dev */
	अगर (netdev_master_upper_dev_get(dev))
		वापस -EBUSY;

	/* No bridging devices that dislike that (e.g. wireless) */
	अगर (dev->priv_flags & IFF_DONT_BRIDGE) अणु
		NL_SET_ERR_MSG(extack,
			       "Device does not allow enslaving to a bridge");
		वापस -EOPNOTSUPP;
	पूर्ण

	p = new_nbp(br, dev);
	अगर (IS_ERR(p))
		वापस PTR_ERR(p);

	call_netdevice_notअगरiers(NETDEV_JOIN, dev);

	err = dev_set_allmulti(dev, 1);
	अगर (err) अणु
		kमुक्त(p);	/* kobject not yet init'd, manually मुक्त */
		जाओ err1;
	पूर्ण

	err = kobject_init_and_add(&p->kobj, &brport_ktype, &(dev->dev.kobj),
				   SYSFS_BRIDGE_PORT_ATTR);
	अगर (err)
		जाओ err2;

	err = br_sysfs_addअगर(p);
	अगर (err)
		जाओ err2;

	err = br_netpoll_enable(p);
	अगर (err)
		जाओ err3;

	err = netdev_rx_handler_रेजिस्टर(dev, br_get_rx_handler(dev), p);
	अगर (err)
		जाओ err4;

	dev->priv_flags |= IFF_BRIDGE_PORT;

	err = netdev_master_upper_dev_link(dev, br->dev, शून्य, शून्य, extack);
	अगर (err)
		जाओ err5;

	err = nbp_चयनdev_mark_set(p);
	अगर (err)
		जाओ err6;

	dev_disable_lro(dev);

	list_add_rcu(&p->list, &br->port_list);

	nbp_update_port_count(br);

	netdev_update_features(br->dev);

	br_hr = br->dev->needed_headroom;
	dev_hr = netdev_get_fwd_headroom(dev);
	अगर (br_hr < dev_hr)
		update_headroom(br, dev_hr);
	अन्यथा
		netdev_set_rx_headroom(dev, br_hr);

	अगर (br_fdb_insert(br, p, dev->dev_addr, 0))
		netdev_err(dev, "failed insert local address bridge forwarding table\n");

	अगर (br->dev->addr_assign_type != NET_ADDR_SET) अणु
		/* Ask क्रम permission to use this MAC address now, even अगर we
		 * करोn't end up choosing it below.
		 */
		err = dev_pre_changeaddr_notअगरy(br->dev, dev->dev_addr, extack);
		अगर (err)
			जाओ err7;
	पूर्ण

	err = nbp_vlan_init(p, extack);
	अगर (err) अणु
		netdev_err(dev, "failed to initialize vlan filtering on this port\n");
		जाओ err7;
	पूर्ण

	spin_lock_bh(&br->lock);
	changed_addr = br_stp_recalculate_bridge_id(br);

	अगर (netअगर_running(dev) && netअगर_oper_up(dev) &&
	    (br->dev->flags & IFF_UP))
		br_stp_enable_port(p);
	spin_unlock_bh(&br->lock);

	br_अगरinfo_notअगरy(RTM_NEWLINK, शून्य, p);

	अगर (changed_addr)
		call_netdevice_notअगरiers(NETDEV_CHANGEADDR, br->dev);

	br_mtu_स्वतः_adjust(br);
	br_set_gso_limits(br);

	kobject_uevent(&p->kobj, KOBJ_ADD);

	वापस 0;

err7:
	list_del_rcu(&p->list);
	br_fdb_delete_by_port(br, p, 0, 1);
	nbp_update_port_count(br);
err6:
	netdev_upper_dev_unlink(dev, br->dev);
err5:
	dev->priv_flags &= ~IFF_BRIDGE_PORT;
	netdev_rx_handler_unरेजिस्टर(dev);
err4:
	br_netpoll_disable(p);
err3:
	sysfs_हटाओ_link(br->अगरobj, p->dev->name);
err2:
	kobject_put(&p->kobj);
	dev_set_allmulti(dev, -1);
err1:
	dev_put(dev);
	वापस err;
पूर्ण

/* called with RTNL */
पूर्णांक br_del_अगर(काष्ठा net_bridge *br, काष्ठा net_device *dev)
अणु
	काष्ठा net_bridge_port *p;
	bool changed_addr;

	p = br_port_get_rtnl(dev);
	अगर (!p || p->br != br)
		वापस -EINVAL;

	/* Since more than one पूर्णांकerface can be attached to a bridge,
	 * there still maybe an alternate path क्रम netconsole to use;
	 * thereक्रमe there is no reason क्रम a NETDEV_RELEASE event.
	 */
	del_nbp(p);

	br_mtu_स्वतः_adjust(br);
	br_set_gso_limits(br);

	spin_lock_bh(&br->lock);
	changed_addr = br_stp_recalculate_bridge_id(br);
	spin_unlock_bh(&br->lock);

	अगर (changed_addr)
		call_netdevice_notअगरiers(NETDEV_CHANGEADDR, br->dev);

	netdev_update_features(br->dev);

	वापस 0;
पूर्ण

व्योम br_port_flags_change(काष्ठा net_bridge_port *p, अचिन्हित दीर्घ mask)
अणु
	काष्ठा net_bridge *br = p->br;

	अगर (mask & BR_AUTO_MASK)
		nbp_update_port_count(br);

	अगर (mask & BR_NEIGH_SUPPRESS)
		br_recalculate_neigh_suppress_enabled(br);
पूर्ण

bool br_port_flag_is_set(स्थिर काष्ठा net_device *dev, अचिन्हित दीर्घ flag)
अणु
	काष्ठा net_bridge_port *p;

	p = br_port_get_rtnl_rcu(dev);
	अगर (!p)
		वापस false;

	वापस p->flags & flag;
पूर्ण
EXPORT_SYMBOL_GPL(br_port_flag_is_set);
