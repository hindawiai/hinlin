<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich
 */

#समावेश "hard-interface.h"
#समावेश "main.h"

#समावेश <linux/atomic.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gfp.h>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/list.h>
#समावेश <linux/minmax.h>
#समावेश <linux/mutex.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <net/net_namespace.h>
#समावेश <net/rtnetlink.h>
#समावेश <uapi/linux/batadv_packet.h>

#समावेश "bat_v.h"
#समावेश "bridge_loop_avoidance.h"
#समावेश "distributed-arp-table.h"
#समावेश "gateway_client.h"
#समावेश "log.h"
#समावेश "originator.h"
#समावेश "send.h"
#समावेश "soft-interface.h"
#समावेश "translation-table.h"

/**
 * batadv_hardअगर_release() - release hard पूर्णांकerface from lists and queue क्रम
 *  मुक्त after rcu grace period
 * @ref: kref poपूर्णांकer of the hard पूर्णांकerface
 */
व्योम batadv_hardअगर_release(काष्ठा kref *ref)
अणु
	काष्ठा batadv_hard_अगरace *hard_अगरace;

	hard_अगरace = container_of(ref, काष्ठा batadv_hard_अगरace, refcount);
	dev_put(hard_अगरace->net_dev);

	kमुक्त_rcu(hard_अगरace, rcu);
पूर्ण

/**
 * batadv_hardअगर_get_by_netdev() - Get hard पूर्णांकerface object of a net_device
 * @net_dev: net_device to search क्रम
 *
 * Return: batadv_hard_अगरace of net_dev (with increased refcnt), शून्य on errors
 */
काष्ठा batadv_hard_अगरace *
batadv_hardअगर_get_by_netdev(स्थिर काष्ठा net_device *net_dev)
अणु
	काष्ठा batadv_hard_अगरace *hard_अगरace;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(hard_अगरace, &batadv_hardअगर_list, list) अणु
		अगर (hard_अगरace->net_dev == net_dev &&
		    kref_get_unless_zero(&hard_अगरace->refcount))
			जाओ out;
	पूर्ण

	hard_अगरace = शून्य;

out:
	rcu_पढ़ो_unlock();
	वापस hard_अगरace;
पूर्ण

/**
 * batadv_getlink_net() - वापस link net namespace (of use fallback)
 * @netdev: net_device to check
 * @fallback_net: वापस in हाल get_link_net is not available क्रम @netdev
 *
 * Return: result of rtnl_link_ops->get_link_net or @fallback_net
 */
अटल काष्ठा net *batadv_getlink_net(स्थिर काष्ठा net_device *netdev,
				      काष्ठा net *fallback_net)
अणु
	अगर (!netdev->rtnl_link_ops)
		वापस fallback_net;

	अगर (!netdev->rtnl_link_ops->get_link_net)
		वापस fallback_net;

	वापस netdev->rtnl_link_ops->get_link_net(netdev);
पूर्ण

/**
 * batadv_mutual_parents() - check अगर two devices are each others parent
 * @dev1: 1st net dev
 * @net1: 1st devices netns
 * @dev2: 2nd net dev
 * @net2: 2nd devices netns
 *
 * veth devices come in pairs and each is the parent of the other!
 *
 * Return: true अगर the devices are each others parent, otherwise false
 */
अटल bool batadv_mutual_parents(स्थिर काष्ठा net_device *dev1,
				  काष्ठा net *net1,
				  स्थिर काष्ठा net_device *dev2,
				  काष्ठा net *net2)
अणु
	पूर्णांक dev1_parent_अगरlink = dev_get_अगरlink(dev1);
	पूर्णांक dev2_parent_अगरlink = dev_get_अगरlink(dev2);
	स्थिर काष्ठा net *dev1_parent_net;
	स्थिर काष्ठा net *dev2_parent_net;

	dev1_parent_net = batadv_getlink_net(dev1, net1);
	dev2_parent_net = batadv_getlink_net(dev2, net2);

	अगर (!dev1_parent_अगरlink || !dev2_parent_अगरlink)
		वापस false;

	वापस (dev1_parent_अगरlink == dev2->अगरindex) &&
	       (dev2_parent_अगरlink == dev1->अगरindex) &&
	       net_eq(dev1_parent_net, net2) &&
	       net_eq(dev2_parent_net, net1);
पूर्ण

/**
 * batadv_is_on_baपंचांगan_अगरace() - check अगर a device is a baपंचांगan अगरace descendant
 * @net_dev: the device to check
 *
 * If the user creates any भव device on top of a baपंचांगan-adv पूर्णांकerface, it
 * is important to prevent this new पूर्णांकerface from being used to create a new
 * mesh network (this behaviour would lead to a baपंचांगan-over-baपंचांगan
 * configuration). This function recursively checks all the fathers of the
 * device passed as argument looking क्रम a baपंचांगan-adv soft पूर्णांकerface.
 *
 * Return: true अगर the device is descendant of a baपंचांगan-adv mesh पूर्णांकerface (or
 * अगर it is a baपंचांगan-adv पूर्णांकerface itself), false otherwise
 */
अटल bool batadv_is_on_baपंचांगan_अगरace(स्थिर काष्ठा net_device *net_dev)
अणु
	काष्ठा net *net = dev_net(net_dev);
	काष्ठा net_device *parent_dev;
	काष्ठा net *parent_net;
	bool ret;

	/* check अगर this is a baपंचांगan-adv mesh पूर्णांकerface */
	अगर (batadv_softअगर_is_valid(net_dev))
		वापस true;

	/* no more parents..stop recursion */
	अगर (dev_get_अगरlink(net_dev) == 0 ||
	    dev_get_अगरlink(net_dev) == net_dev->अगरindex)
		वापस false;

	parent_net = batadv_getlink_net(net_dev, net);

	/* recurse over the parent device */
	parent_dev = __dev_get_by_index((काष्ठा net *)parent_net,
					dev_get_अगरlink(net_dev));
	/* अगर we got a शून्य parent_dev there is something broken.. */
	अगर (!parent_dev) अणु
		pr_err("Cannot find parent device\n");
		वापस false;
	पूर्ण

	अगर (batadv_mutual_parents(net_dev, net, parent_dev, parent_net))
		वापस false;

	ret = batadv_is_on_baपंचांगan_अगरace(parent_dev);

	वापस ret;
पूर्ण

अटल bool batadv_is_valid_अगरace(स्थिर काष्ठा net_device *net_dev)
अणु
	अगर (net_dev->flags & IFF_LOOPBACK)
		वापस false;

	अगर (net_dev->type != ARPHRD_ETHER)
		वापस false;

	अगर (net_dev->addr_len != ETH_ALEN)
		वापस false;

	/* no baपंचांगan over baपंचांगan */
	अगर (batadv_is_on_baपंचांगan_अगरace(net_dev))
		वापस false;

	वापस true;
पूर्ण

/**
 * batadv_get_real_netdevice() - check अगर the given netdev काष्ठा is a भव
 *  पूर्णांकerface on top of another 'real' पूर्णांकerface
 * @netdev: the device to check
 *
 * Callers must hold the rtnl semaphore. You may want batadv_get_real_netdev()
 * instead of this.
 *
 * Return: the 'real' net device or the original net device and शून्य in हाल
 *  of an error.
 */
अटल काष्ठा net_device *batadv_get_real_netdevice(काष्ठा net_device *netdev)
अणु
	काष्ठा batadv_hard_अगरace *hard_अगरace = शून्य;
	काष्ठा net_device *real_netdev = शून्य;
	काष्ठा net *real_net;
	काष्ठा net *net;
	पूर्णांक अगरindex;

	ASSERT_RTNL();

	अगर (!netdev)
		वापस शून्य;

	अगर (netdev->अगरindex == dev_get_अगरlink(netdev)) अणु
		dev_hold(netdev);
		वापस netdev;
	पूर्ण

	hard_अगरace = batadv_hardअगर_get_by_netdev(netdev);
	अगर (!hard_अगरace || !hard_अगरace->soft_अगरace)
		जाओ out;

	net = dev_net(hard_अगरace->soft_अगरace);
	अगरindex = dev_get_अगरlink(netdev);
	real_net = batadv_getlink_net(netdev, net);
	real_netdev = dev_get_by_index(real_net, अगरindex);

out:
	अगर (hard_अगरace)
		batadv_hardअगर_put(hard_अगरace);
	वापस real_netdev;
पूर्ण

/**
 * batadv_get_real_netdev() - check अगर the given net_device काष्ठा is a भव
 *  पूर्णांकerface on top of another 'real' पूर्णांकerface
 * @net_device: the device to check
 *
 * Return: the 'real' net device or the original net device and शून्य in हाल
 *  of an error.
 */
काष्ठा net_device *batadv_get_real_netdev(काष्ठा net_device *net_device)
अणु
	काष्ठा net_device *real_netdev;

	rtnl_lock();
	real_netdev = batadv_get_real_netdevice(net_device);
	rtnl_unlock();

	वापस real_netdev;
पूर्ण

/**
 * batadv_is_wext_netdev() - check अगर the given net_device काष्ठा is a
 *  wext wअगरi पूर्णांकerface
 * @net_device: the device to check
 *
 * Return: true अगर the net device is a wext wireless device, false
 *  otherwise.
 */
अटल bool batadv_is_wext_netdev(काष्ठा net_device *net_device)
अणु
	अगर (!net_device)
		वापस false;

#अगर_घोषित CONFIG_WIRELESS_EXT
	/* pre-cfg80211 drivers have to implement WEXT, so it is possible to
	 * check क्रम wireless_handlers != शून्य
	 */
	अगर (net_device->wireless_handlers)
		वापस true;
#पूर्ण_अगर

	वापस false;
पूर्ण

/**
 * batadv_is_cfg80211_netdev() - check अगर the given net_device काष्ठा is a
 *  cfg80211 wअगरi पूर्णांकerface
 * @net_device: the device to check
 *
 * Return: true अगर the net device is a cfg80211 wireless device, false
 *  otherwise.
 */
अटल bool batadv_is_cfg80211_netdev(काष्ठा net_device *net_device)
अणु
	अगर (!net_device)
		वापस false;

	/* cfg80211 drivers have to set ieee80211_ptr */
	अगर (net_device->ieee80211_ptr)
		वापस true;

	वापस false;
पूर्ण

/**
 * batadv_wअगरi_flags_evaluate() - calculate wअगरi flags क्रम net_device
 * @net_device: the device to check
 *
 * Return: batadv_hard_अगरace_wअगरi_flags flags of the device
 */
अटल u32 batadv_wअगरi_flags_evaluate(काष्ठा net_device *net_device)
अणु
	u32 wअगरi_flags = 0;
	काष्ठा net_device *real_netdev;

	अगर (batadv_is_wext_netdev(net_device))
		wअगरi_flags |= BATADV_HARDIF_WIFI_WEXT_सूचीECT;

	अगर (batadv_is_cfg80211_netdev(net_device))
		wअगरi_flags |= BATADV_HARDIF_WIFI_CFG80211_सूचीECT;

	real_netdev = batadv_get_real_netdevice(net_device);
	अगर (!real_netdev)
		वापस wअगरi_flags;

	अगर (real_netdev == net_device)
		जाओ out;

	अगर (batadv_is_wext_netdev(real_netdev))
		wअगरi_flags |= BATADV_HARDIF_WIFI_WEXT_INसूचीECT;

	अगर (batadv_is_cfg80211_netdev(real_netdev))
		wअगरi_flags |= BATADV_HARDIF_WIFI_CFG80211_INसूचीECT;

out:
	dev_put(real_netdev);
	वापस wअगरi_flags;
पूर्ण

/**
 * batadv_is_cfg80211_hardअगर() - check अगर the given hardअगर is a cfg80211 wअगरi
 *  पूर्णांकerface
 * @hard_अगरace: the device to check
 *
 * Return: true अगर the net device is a cfg80211 wireless device, false
 *  otherwise.
 */
bool batadv_is_cfg80211_hardअगर(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	u32 allowed_flags = 0;

	allowed_flags |= BATADV_HARDIF_WIFI_CFG80211_सूचीECT;
	allowed_flags |= BATADV_HARDIF_WIFI_CFG80211_INसूचीECT;

	वापस !!(hard_अगरace->wअगरi_flags & allowed_flags);
पूर्ण

/**
 * batadv_is_wअगरi_hardअगर() - check अगर the given hardअगर is a wअगरi पूर्णांकerface
 * @hard_अगरace: the device to check
 *
 * Return: true अगर the net device is a 802.11 wireless device, false otherwise.
 */
bool batadv_is_wअगरi_hardअगर(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	अगर (!hard_अगरace)
		वापस false;

	वापस hard_अगरace->wअगरi_flags != 0;
पूर्ण

/**
 * batadv_hardअगर_no_broadcast() - check whether (re)broadcast is necessary
 * @अगर_outgoing: the outgoing पूर्णांकerface checked and considered क्रम (re)broadcast
 * @orig_addr: the originator of this packet
 * @orig_neigh: originator address of the क्रमwarder we just got the packet from
 *  (शून्य अगर we originated)
 *
 * Checks whether a packet needs to be (re)broadcasted on the given पूर्णांकerface.
 *
 * Return:
 *	BATADV_HARDIF_BCAST_NORECIPIENT: No neighbor on पूर्णांकerface
 *	BATADV_HARDIF_BCAST_DUPFWD: Just one neighbor, but it is the क्रमwarder
 *	BATADV_HARDIF_BCAST_DUPORIG: Just one neighbor, but it is the originator
 *	BATADV_HARDIF_BCAST_OK: Several neighbors, must broadcast
 */
पूर्णांक batadv_hardअगर_no_broadcast(काष्ठा batadv_hard_अगरace *अगर_outgoing,
			       u8 *orig_addr, u8 *orig_neigh)
अणु
	काष्ठा batadv_hardअगर_neigh_node *hardअगर_neigh;
	काष्ठा hlist_node *first;
	पूर्णांक ret = BATADV_HARDIF_BCAST_OK;

	rcu_पढ़ो_lock();

	/* 0 neighbors -> no (re)broadcast */
	first = rcu_dereference(hlist_first_rcu(&अगर_outgoing->neigh_list));
	अगर (!first) अणु
		ret = BATADV_HARDIF_BCAST_NORECIPIENT;
		जाओ out;
	पूर्ण

	/* >1 neighbors -> (re)brodcast */
	अगर (rcu_dereference(hlist_next_rcu(first)))
		जाओ out;

	hardअगर_neigh = hlist_entry(first, काष्ठा batadv_hardअगर_neigh_node,
				   list);

	/* 1 neighbor, is the originator -> no rebroadcast */
	अगर (orig_addr && batadv_compare_eth(hardअगर_neigh->orig, orig_addr)) अणु
		ret = BATADV_HARDIF_BCAST_DUPORIG;
	/* 1 neighbor, is the one we received from -> no rebroadcast */
	पूर्ण अन्यथा अगर (orig_neigh &&
		   batadv_compare_eth(hardअगर_neigh->orig, orig_neigh)) अणु
		ret = BATADV_HARDIF_BCAST_DUPFWD;
	पूर्ण

out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल काष्ठा batadv_hard_अगरace *
batadv_hardअगर_get_active(स्थिर काष्ठा net_device *soft_अगरace)
अणु
	काष्ठा batadv_hard_अगरace *hard_अगरace;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(hard_अगरace, &batadv_hardअगर_list, list) अणु
		अगर (hard_अगरace->soft_अगरace != soft_अगरace)
			जारी;

		अगर (hard_अगरace->अगर_status == BATADV_IF_ACTIVE &&
		    kref_get_unless_zero(&hard_अगरace->refcount))
			जाओ out;
	पूर्ण

	hard_अगरace = शून्य;

out:
	rcu_पढ़ो_unlock();
	वापस hard_अगरace;
पूर्ण

अटल व्योम batadv_primary_अगर_update_addr(काष्ठा batadv_priv *bat_priv,
					  काष्ठा batadv_hard_अगरace *oldअगर)
अणु
	काष्ठा batadv_hard_अगरace *primary_अगर;

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर)
		जाओ out;

	batadv_dat_init_own_addr(bat_priv, primary_अगर);
	batadv_bla_update_orig_address(bat_priv, primary_अगर, oldअगर);
out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
पूर्ण

अटल व्योम batadv_primary_अगर_select(काष्ठा batadv_priv *bat_priv,
				     काष्ठा batadv_hard_अगरace *new_hard_अगरace)
अणु
	काष्ठा batadv_hard_अगरace *curr_hard_अगरace;

	ASSERT_RTNL();

	अगर (new_hard_अगरace)
		kref_get(&new_hard_अगरace->refcount);

	curr_hard_अगरace = rcu_replace_poपूर्णांकer(bat_priv->primary_अगर,
					      new_hard_अगरace, 1);

	अगर (!new_hard_अगरace)
		जाओ out;

	bat_priv->algo_ops->अगरace.primary_set(new_hard_अगरace);
	batadv_primary_अगर_update_addr(bat_priv, curr_hard_अगरace);

out:
	अगर (curr_hard_अगरace)
		batadv_hardअगर_put(curr_hard_अगरace);
पूर्ण

अटल bool
batadv_hardअगर_is_अगरace_up(स्थिर काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	अगर (hard_अगरace->net_dev->flags & IFF_UP)
		वापस true;

	वापस false;
पूर्ण

अटल व्योम batadv_check_known_mac_addr(स्थिर काष्ठा net_device *net_dev)
अणु
	स्थिर काष्ठा batadv_hard_अगरace *hard_अगरace;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(hard_अगरace, &batadv_hardअगर_list, list) अणु
		अगर (hard_अगरace->अगर_status != BATADV_IF_ACTIVE &&
		    hard_अगरace->अगर_status != BATADV_IF_TO_BE_ACTIVATED)
			जारी;

		अगर (hard_अगरace->net_dev == net_dev)
			जारी;

		अगर (!batadv_compare_eth(hard_अगरace->net_dev->dev_addr,
					net_dev->dev_addr))
			जारी;

		pr_warn("The newly added mac address (%pM) already exists on: %s\n",
			net_dev->dev_addr, hard_अगरace->net_dev->name);
		pr_warn("It is strongly recommended to keep mac addresses unique to avoid problems!\n");
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * batadv_hardअगर_recalc_extra_skbroom() - Recalculate skbuff extra head/tailroom
 * @soft_अगरace: netdev काष्ठा of the mesh पूर्णांकerface
 */
अटल व्योम batadv_hardअगर_recalc_extra_skbroom(काष्ठा net_device *soft_अगरace)
अणु
	स्थिर काष्ठा batadv_hard_अगरace *hard_अगरace;
	अचिन्हित लघु lower_header_len = ETH_HLEN;
	अचिन्हित लघु lower_headroom = 0;
	अचिन्हित लघु lower_tailroom = 0;
	अचिन्हित लघु needed_headroom;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(hard_अगरace, &batadv_hardअगर_list, list) अणु
		अगर (hard_अगरace->अगर_status == BATADV_IF_NOT_IN_USE)
			जारी;

		अगर (hard_अगरace->soft_अगरace != soft_अगरace)
			जारी;

		lower_header_len = max_t(अचिन्हित लघु, lower_header_len,
					 hard_अगरace->net_dev->hard_header_len);

		lower_headroom = max_t(अचिन्हित लघु, lower_headroom,
				       hard_अगरace->net_dev->needed_headroom);

		lower_tailroom = max_t(अचिन्हित लघु, lower_tailroom,
				       hard_अगरace->net_dev->needed_tailroom);
	पूर्ण
	rcu_पढ़ो_unlock();

	needed_headroom = lower_headroom + (lower_header_len - ETH_HLEN);
	needed_headroom += batadv_max_header_len();

	/* fragmentation headers करोn't strip the unicast/... header */
	needed_headroom += माप(काष्ठा batadv_frag_packet);

	soft_अगरace->needed_headroom = needed_headroom;
	soft_अगरace->needed_tailroom = lower_tailroom;
पूर्ण

/**
 * batadv_hardअगर_min_mtu() - Calculate maximum MTU क्रम soft पूर्णांकerface
 * @soft_अगरace: netdev काष्ठा of the soft पूर्णांकerface
 *
 * Return: MTU क्रम the soft-पूर्णांकerface (limited by the minimal MTU of all active
 *  slave पूर्णांकerfaces)
 */
पूर्णांक batadv_hardअगर_min_mtu(काष्ठा net_device *soft_अगरace)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(soft_अगरace);
	स्थिर काष्ठा batadv_hard_अगरace *hard_अगरace;
	पूर्णांक min_mtu = पूर्णांक_उच्च;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(hard_अगरace, &batadv_hardअगर_list, list) अणु
		अगर (hard_अगरace->अगर_status != BATADV_IF_ACTIVE &&
		    hard_अगरace->अगर_status != BATADV_IF_TO_BE_ACTIVATED)
			जारी;

		अगर (hard_अगरace->soft_अगरace != soft_अगरace)
			जारी;

		min_mtu = min_t(पूर्णांक, hard_अगरace->net_dev->mtu, min_mtu);
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (atomic_पढ़ो(&bat_priv->fragmentation) == 0)
		जाओ out;

	/* with fragmentation enabled the maximum size of पूर्णांकernally generated
	 * packets such as translation table exchanges or tvlv containers, etc
	 * has to be calculated
	 */
	min_mtu = min_t(पूर्णांक, min_mtu, BATADV_FRAG_MAX_FRAG_SIZE);
	min_mtu -= माप(काष्ठा batadv_frag_packet);
	min_mtu *= BATADV_FRAG_MAX_FRAGMENTS;

out:
	/* report to the other components the maximum amount of bytes that
	 * baपंचांगan-adv can send over the wire (without considering the payload
	 * overhead). For example, this value is used by TT to compute the
	 * maximum local table size
	 */
	atomic_set(&bat_priv->packet_size_max, min_mtu);

	/* the real soft-पूर्णांकerface MTU is computed by removing the payload
	 * overhead from the maximum amount of bytes that was just computed.
	 *
	 * However baपंचांगan-adv करोes not support MTUs bigger than ETH_DATA_LEN
	 */
	वापस min_t(पूर्णांक, min_mtu - batadv_max_header_len(), ETH_DATA_LEN);
पूर्ण

/**
 * batadv_update_min_mtu() - Adjusts the MTU अगर a new पूर्णांकerface with a smaller
 *  MTU appeared
 * @soft_अगरace: netdev काष्ठा of the soft पूर्णांकerface
 */
व्योम batadv_update_min_mtu(काष्ठा net_device *soft_अगरace)
अणु
	soft_अगरace->mtu = batadv_hardअगर_min_mtu(soft_अगरace);

	/* Check अगर the local translate table should be cleaned up to match a
	 * new (and smaller) MTU.
	 */
	batadv_tt_local_reमाप_प्रकारo_mtu(soft_अगरace);
पूर्ण

अटल व्योम
batadv_hardअगर_activate_पूर्णांकerface(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	काष्ठा batadv_priv *bat_priv;
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;

	अगर (hard_अगरace->अगर_status != BATADV_IF_INACTIVE)
		जाओ out;

	bat_priv = netdev_priv(hard_अगरace->soft_अगरace);

	bat_priv->algo_ops->अगरace.update_mac(hard_अगरace);
	hard_अगरace->अगर_status = BATADV_IF_TO_BE_ACTIVATED;

	/* the first active पूर्णांकerface becomes our primary पूर्णांकerface or
	 * the next active पूर्णांकerface after the old primary पूर्णांकerface was हटाओd
	 */
	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर)
		batadv_primary_अगर_select(bat_priv, hard_अगरace);

	batadv_info(hard_अगरace->soft_अगरace, "Interface activated: %s\n",
		    hard_अगरace->net_dev->name);

	batadv_update_min_mtu(hard_अगरace->soft_अगरace);

	अगर (bat_priv->algo_ops->अगरace.activate)
		bat_priv->algo_ops->अगरace.activate(hard_अगरace);

out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
पूर्ण

अटल व्योम
batadv_hardअगर_deactivate_पूर्णांकerface(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	अगर (hard_अगरace->अगर_status != BATADV_IF_ACTIVE &&
	    hard_अगरace->अगर_status != BATADV_IF_TO_BE_ACTIVATED)
		वापस;

	hard_अगरace->अगर_status = BATADV_IF_INACTIVE;

	batadv_info(hard_अगरace->soft_अगरace, "Interface deactivated: %s\n",
		    hard_अगरace->net_dev->name);

	batadv_update_min_mtu(hard_अगरace->soft_अगरace);
पूर्ण

/**
 * batadv_master_del_slave() - हटाओ hard_अगरace from the current master अगरace
 * @slave: the पूर्णांकerface enslaved in another master
 * @master: the master from which slave has to be हटाओd
 *
 * Invoke nकरो_del_slave on master passing slave as argument. In this way the
 * slave is मुक्त'd and the master can correctly change its पूर्णांकernal state.
 *
 * Return: 0 on success, a negative value representing the error otherwise
 */
अटल पूर्णांक batadv_master_del_slave(काष्ठा batadv_hard_अगरace *slave,
				   काष्ठा net_device *master)
अणु
	पूर्णांक ret;

	अगर (!master)
		वापस 0;

	ret = -EBUSY;
	अगर (master->netdev_ops->nकरो_del_slave)
		ret = master->netdev_ops->nकरो_del_slave(master, slave->net_dev);

	वापस ret;
पूर्ण

/**
 * batadv_hardअगर_enable_पूर्णांकerface() - Enslave hard पूर्णांकerface to soft पूर्णांकerface
 * @hard_अगरace: hard पूर्णांकerface to add to soft पूर्णांकerface
 * @net: the applicable net namespace
 * @अगरace_name: name of the soft पूर्णांकerface
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
पूर्णांक batadv_hardअगर_enable_पूर्णांकerface(काष्ठा batadv_hard_अगरace *hard_अगरace,
				   काष्ठा net *net, स्थिर अक्षर *अगरace_name)
अणु
	काष्ठा batadv_priv *bat_priv;
	काष्ठा net_device *soft_अगरace, *master;
	__be16 ethertype = htons(ETH_P_BATMAN);
	पूर्णांक max_header_len = batadv_max_header_len();
	पूर्णांक ret;

	अगर (hard_अगरace->अगर_status != BATADV_IF_NOT_IN_USE)
		जाओ out;

	kref_get(&hard_अगरace->refcount);

	soft_अगरace = dev_get_by_name(net, अगरace_name);

	अगर (!soft_अगरace) अणु
		soft_अगरace = batadv_softअगर_create(net, अगरace_name);

		अगर (!soft_अगरace) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		/* dev_get_by_name() increases the reference counter क्रम us */
		dev_hold(soft_अगरace);
	पूर्ण

	अगर (!batadv_softअगर_is_valid(soft_अगरace)) अणु
		pr_err("Can't create batman mesh interface %s: already exists as regular interface\n",
		       soft_अगरace->name);
		ret = -EINVAL;
		जाओ err_dev;
	पूर्ण

	/* check अगर the पूर्णांकerface is enslaved in another भव one and
	 * in that हाल unlink it first
	 */
	master = netdev_master_upper_dev_get(hard_अगरace->net_dev);
	ret = batadv_master_del_slave(hard_अगरace, master);
	अगर (ret)
		जाओ err_dev;

	hard_अगरace->soft_अगरace = soft_अगरace;
	bat_priv = netdev_priv(hard_अगरace->soft_अगरace);

	ret = netdev_master_upper_dev_link(hard_अगरace->net_dev,
					   soft_अगरace, शून्य, शून्य, शून्य);
	अगर (ret)
		जाओ err_dev;

	ret = bat_priv->algo_ops->अगरace.enable(hard_अगरace);
	अगर (ret < 0)
		जाओ err_upper;

	hard_अगरace->अगर_status = BATADV_IF_INACTIVE;

	kref_get(&hard_अगरace->refcount);
	hard_अगरace->baपंचांगan_adv_ptype.type = ethertype;
	hard_अगरace->baपंचांगan_adv_ptype.func = batadv_baपंचांगan_skb_recv;
	hard_अगरace->baपंचांगan_adv_ptype.dev = hard_अगरace->net_dev;
	dev_add_pack(&hard_अगरace->baपंचांगan_adv_ptype);

	batadv_info(hard_अगरace->soft_अगरace, "Adding interface: %s\n",
		    hard_अगरace->net_dev->name);

	अगर (atomic_पढ़ो(&bat_priv->fragmentation) &&
	    hard_अगरace->net_dev->mtu < ETH_DATA_LEN + max_header_len)
		batadv_info(hard_अगरace->soft_अगरace,
			    "The MTU of interface %s is too small (%i) to handle the transport of batman-adv packets. Packets going over this interface will be fragmented on layer2 which could impact the performance. Setting the MTU to %i would solve the problem.\n",
			    hard_अगरace->net_dev->name, hard_अगरace->net_dev->mtu,
			    ETH_DATA_LEN + max_header_len);

	अगर (!atomic_पढ़ो(&bat_priv->fragmentation) &&
	    hard_अगरace->net_dev->mtu < ETH_DATA_LEN + max_header_len)
		batadv_info(hard_अगरace->soft_अगरace,
			    "The MTU of interface %s is too small (%i) to handle the transport of batman-adv packets. If you experience problems getting traffic through try increasing the MTU to %i.\n",
			    hard_अगरace->net_dev->name, hard_अगरace->net_dev->mtu,
			    ETH_DATA_LEN + max_header_len);

	अगर (batadv_hardअगर_is_अगरace_up(hard_अगरace))
		batadv_hardअगर_activate_पूर्णांकerface(hard_अगरace);
	अन्यथा
		batadv_err(hard_अगरace->soft_अगरace,
			   "Not using interface %s (retrying later): interface not active\n",
			   hard_अगरace->net_dev->name);

	batadv_hardअगर_recalc_extra_skbroom(soft_अगरace);

	अगर (bat_priv->algo_ops->अगरace.enabled)
		bat_priv->algo_ops->अगरace.enabled(hard_अगरace);

out:
	वापस 0;

err_upper:
	netdev_upper_dev_unlink(hard_अगरace->net_dev, soft_अगरace);
err_dev:
	hard_अगरace->soft_अगरace = शून्य;
	dev_put(soft_अगरace);
err:
	batadv_hardअगर_put(hard_अगरace);
	वापस ret;
पूर्ण

/**
 * batadv_hardअगर_cnt() - get number of पूर्णांकerfaces enslaved to soft पूर्णांकerface
 * @soft_अगरace: soft पूर्णांकerface to check
 *
 * This function is only using RCU क्रम locking - the result can thereक्रमe be
 * off when another function is modअगरying the list at the same समय. The
 * caller can use the rtnl_lock to make sure that the count is accurate.
 *
 * Return: number of connected/enslaved hard पूर्णांकerfaces
 */
अटल माप_प्रकार batadv_hardअगर_cnt(स्थिर काष्ठा net_device *soft_अगरace)
अणु
	काष्ठा batadv_hard_अगरace *hard_अगरace;
	माप_प्रकार count = 0;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(hard_अगरace, &batadv_hardअगर_list, list) अणु
		अगर (hard_अगरace->soft_अगरace != soft_अगरace)
			जारी;

		count++;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस count;
पूर्ण

/**
 * batadv_hardअगर_disable_पूर्णांकerface() - Remove hard पूर्णांकerface from soft पूर्णांकerface
 * @hard_अगरace: hard पूर्णांकerface to be हटाओd
 */
व्योम batadv_hardअगर_disable_पूर्णांकerface(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(hard_अगरace->soft_अगरace);
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;

	batadv_hardअगर_deactivate_पूर्णांकerface(hard_अगरace);

	अगर (hard_अगरace->अगर_status != BATADV_IF_INACTIVE)
		जाओ out;

	batadv_info(hard_अगरace->soft_अगरace, "Removing interface: %s\n",
		    hard_अगरace->net_dev->name);
	dev_हटाओ_pack(&hard_अगरace->baपंचांगan_adv_ptype);
	batadv_hardअगर_put(hard_अगरace);

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (hard_अगरace == primary_अगर) अणु
		काष्ठा batadv_hard_अगरace *new_अगर;

		new_अगर = batadv_hardअगर_get_active(hard_अगरace->soft_अगरace);
		batadv_primary_अगर_select(bat_priv, new_अगर);

		अगर (new_अगर)
			batadv_hardअगर_put(new_अगर);
	पूर्ण

	bat_priv->algo_ops->अगरace.disable(hard_अगरace);
	hard_अगरace->अगर_status = BATADV_IF_NOT_IN_USE;

	/* delete all references to this hard_अगरace */
	batadv_purge_orig_ref(bat_priv);
	batadv_purge_outstanding_packets(bat_priv, hard_अगरace);
	dev_put(hard_अगरace->soft_अगरace);

	netdev_upper_dev_unlink(hard_अगरace->net_dev, hard_अगरace->soft_अगरace);
	batadv_hardअगर_recalc_extra_skbroom(hard_अगरace->soft_अगरace);

	/* nobody uses this पूर्णांकerface anymore */
	अगर (batadv_hardअगर_cnt(hard_अगरace->soft_अगरace) <= 1)
		batadv_gw_check_client_stop(bat_priv);

	hard_अगरace->soft_अगरace = शून्य;
	batadv_hardअगर_put(hard_अगरace);

out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
पूर्ण

अटल काष्ठा batadv_hard_अगरace *
batadv_hardअगर_add_पूर्णांकerface(काष्ठा net_device *net_dev)
अणु
	काष्ठा batadv_hard_अगरace *hard_अगरace;

	ASSERT_RTNL();

	अगर (!batadv_is_valid_अगरace(net_dev))
		जाओ out;

	dev_hold(net_dev);

	hard_अगरace = kzalloc(माप(*hard_अगरace), GFP_ATOMIC);
	अगर (!hard_अगरace)
		जाओ release_dev;

	hard_अगरace->net_dev = net_dev;
	hard_अगरace->soft_अगरace = शून्य;
	hard_अगरace->अगर_status = BATADV_IF_NOT_IN_USE;

	INIT_LIST_HEAD(&hard_अगरace->list);
	INIT_HLIST_HEAD(&hard_अगरace->neigh_list);

	mutex_init(&hard_अगरace->bat_iv.ogm_buff_mutex);
	spin_lock_init(&hard_अगरace->neigh_list_lock);
	kref_init(&hard_अगरace->refcount);

	hard_अगरace->num_bcasts = BATADV_NUM_BCASTS_DEFAULT;
	hard_अगरace->wअगरi_flags = batadv_wअगरi_flags_evaluate(net_dev);
	अगर (batadv_is_wअगरi_hardअगर(hard_अगरace))
		hard_अगरace->num_bcasts = BATADV_NUM_BCASTS_WIRELESS;

	atomic_set(&hard_अगरace->hop_penalty, 0);

	batadv_v_hardअगर_init(hard_अगरace);

	batadv_check_known_mac_addr(hard_अगरace->net_dev);
	kref_get(&hard_अगरace->refcount);
	list_add_tail_rcu(&hard_अगरace->list, &batadv_hardअगर_list);
	batadv_hardअगर_generation++;

	वापस hard_अगरace;

release_dev:
	dev_put(net_dev);
out:
	वापस शून्य;
पूर्ण

अटल व्योम batadv_hardअगर_हटाओ_पूर्णांकerface(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	ASSERT_RTNL();

	/* first deactivate पूर्णांकerface */
	अगर (hard_अगरace->अगर_status != BATADV_IF_NOT_IN_USE)
		batadv_hardअगर_disable_पूर्णांकerface(hard_अगरace);

	अगर (hard_अगरace->अगर_status != BATADV_IF_NOT_IN_USE)
		वापस;

	hard_अगरace->अगर_status = BATADV_IF_TO_BE_REMOVED;
	batadv_hardअगर_put(hard_अगरace);
पूर्ण

/**
 * batadv_hard_अगर_event_softअगर() - Handle events क्रम soft पूर्णांकerfaces
 * @event: NETDEV_* event to handle
 * @net_dev: net_device which generated an event
 *
 * Return: NOTIFY_* result
 */
अटल पूर्णांक batadv_hard_अगर_event_softअगर(अचिन्हित दीर्घ event,
				       काष्ठा net_device *net_dev)
अणु
	काष्ठा batadv_priv *bat_priv;

	चयन (event) अणु
	हाल NETDEV_REGISTER:
		bat_priv = netdev_priv(net_dev);
		batadv_softअगर_create_vlan(bat_priv, BATADV_NO_FLAGS);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक batadv_hard_अगर_event(काष्ठा notअगरier_block *this,
				अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *net_dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा batadv_hard_अगरace *hard_अगरace;
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;
	काष्ठा batadv_priv *bat_priv;

	अगर (batadv_softअगर_is_valid(net_dev))
		वापस batadv_hard_अगर_event_softअगर(event, net_dev);

	hard_अगरace = batadv_hardअगर_get_by_netdev(net_dev);
	अगर (!hard_अगरace && (event == NETDEV_REGISTER ||
			    event == NETDEV_POST_TYPE_CHANGE))
		hard_अगरace = batadv_hardअगर_add_पूर्णांकerface(net_dev);

	अगर (!hard_अगरace)
		जाओ out;

	चयन (event) अणु
	हाल NETDEV_UP:
		batadv_hardअगर_activate_पूर्णांकerface(hard_अगरace);
		अवरोध;
	हाल NETDEV_GOING_DOWN:
	हाल NETDEV_DOWN:
		batadv_hardअगर_deactivate_पूर्णांकerface(hard_अगरace);
		अवरोध;
	हाल NETDEV_UNREGISTER:
	हाल NETDEV_PRE_TYPE_CHANGE:
		list_del_rcu(&hard_अगरace->list);
		batadv_hardअगर_generation++;

		batadv_hardअगर_हटाओ_पूर्णांकerface(hard_अगरace);
		अवरोध;
	हाल NETDEV_CHANGEMTU:
		अगर (hard_अगरace->soft_अगरace)
			batadv_update_min_mtu(hard_अगरace->soft_अगरace);
		अवरोध;
	हाल NETDEV_CHANGEADDR:
		अगर (hard_अगरace->अगर_status == BATADV_IF_NOT_IN_USE)
			जाओ hardअगर_put;

		batadv_check_known_mac_addr(hard_अगरace->net_dev);

		bat_priv = netdev_priv(hard_अगरace->soft_अगरace);
		bat_priv->algo_ops->अगरace.update_mac(hard_अगरace);

		primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
		अगर (!primary_अगर)
			जाओ hardअगर_put;

		अगर (hard_अगरace == primary_अगर)
			batadv_primary_अगर_update_addr(bat_priv, शून्य);
		अवरोध;
	हाल NETDEV_CHANGEUPPER:
		hard_अगरace->wअगरi_flags = batadv_wअगरi_flags_evaluate(net_dev);
		अगर (batadv_is_wअगरi_hardअगर(hard_अगरace))
			hard_अगरace->num_bcasts = BATADV_NUM_BCASTS_WIRELESS;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

hardअगर_put:
	batadv_hardअगर_put(hard_अगरace);
out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
	वापस NOTIFY_DONE;
पूर्ण

काष्ठा notअगरier_block batadv_hard_अगर_notअगरier = अणु
	.notअगरier_call = batadv_hard_अगर_event,
पूर्ण;
