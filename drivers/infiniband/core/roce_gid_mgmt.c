<शैली गुरु>
/*
 * Copyright (c) 2015, Mellanox Technologies inc.  All rights reserved.
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

#समावेश "core_priv.h"

#समावेश <linux/in.h>
#समावेश <linux/in6.h>

/* For in6_dev_get/in6_dev_put */
#समावेश <net/addrconf.h>
#समावेश <net/bonding.h>

#समावेश <rdma/ib_cache.h>
#समावेश <rdma/ib_addr.h>

अटल काष्ठा workqueue_काष्ठा *gid_cache_wq;

क्रमागत gid_op_type अणु
	GID_DEL = 0,
	GID_ADD
पूर्ण;

काष्ठा update_gid_event_work अणु
	काष्ठा work_काष्ठा work;
	जोड़ ib_gid       gid;
	काष्ठा ib_gid_attr gid_attr;
	क्रमागत gid_op_type gid_op;
पूर्ण;

#घोषणा ROCE_NETDEV_CALLBACK_SZ		3
काष्ठा netdev_event_work_cmd अणु
	roce_netdev_callback	cb;
	roce_netdev_filter	filter;
	काष्ठा net_device	*ndev;
	काष्ठा net_device	*filter_ndev;
पूर्ण;

काष्ठा netdev_event_work अणु
	काष्ठा work_काष्ठा		work;
	काष्ठा netdev_event_work_cmd	cmds[ROCE_NETDEV_CALLBACK_SZ];
पूर्ण;

अटल स्थिर काष्ठा अणु
	bool (*is_supported)(स्थिर काष्ठा ib_device *device, u32 port_num);
	क्रमागत ib_gid_type gid_type;
पूर्ण PORT_CAP_TO_GID_TYPE[] = अणु
	अणुrdma_protocol_roce_eth_encap, IB_GID_TYPE_ROCEपूर्ण,
	अणुrdma_protocol_roce_udp_encap, IB_GID_TYPE_ROCE_UDP_ENCAPपूर्ण,
पूर्ण;

#घोषणा CAP_TO_GID_TABLE_SIZE	ARRAY_SIZE(PORT_CAP_TO_GID_TYPE)

अचिन्हित दीर्घ roce_gid_type_mask_support(काष्ठा ib_device *ib_dev, u32 port)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक ret_flags = 0;

	अगर (!rdma_protocol_roce(ib_dev, port))
		वापस 1UL << IB_GID_TYPE_IB;

	क्रम (i = 0; i < CAP_TO_GID_TABLE_SIZE; i++)
		अगर (PORT_CAP_TO_GID_TYPE[i].is_supported(ib_dev, port))
			ret_flags |= 1UL << PORT_CAP_TO_GID_TYPE[i].gid_type;

	वापस ret_flags;
पूर्ण
EXPORT_SYMBOL(roce_gid_type_mask_support);

अटल व्योम update_gid(क्रमागत gid_op_type gid_op, काष्ठा ib_device *ib_dev,
		       u32 port, जोड़ ib_gid *gid,
		       काष्ठा ib_gid_attr *gid_attr)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ gid_type_mask = roce_gid_type_mask_support(ib_dev, port);

	क्रम (i = 0; i < IB_GID_TYPE_SIZE; i++) अणु
		अगर ((1UL << i) & gid_type_mask) अणु
			gid_attr->gid_type = i;
			चयन (gid_op) अणु
			हाल GID_ADD:
				ib_cache_gid_add(ib_dev, port,
						 gid, gid_attr);
				अवरोध;
			हाल GID_DEL:
				ib_cache_gid_del(ib_dev, port,
						 gid, gid_attr);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

क्रमागत bonding_slave_state अणु
	BONDING_SLAVE_STATE_ACTIVE	= 1UL << 0,
	BONDING_SLAVE_STATE_INACTIVE	= 1UL << 1,
	/* No primary slave or the device isn't a slave in bonding */
	BONDING_SLAVE_STATE_NA		= 1UL << 2,
पूर्ण;

अटल क्रमागत bonding_slave_state is_eth_active_slave_of_bonding_rcu(काष्ठा net_device *dev,
								   काष्ठा net_device *upper)
अणु
	अगर (upper && netअगर_is_bond_master(upper)) अणु
		काष्ठा net_device *pdev =
			bond_option_active_slave_get_rcu(netdev_priv(upper));

		अगर (pdev)
			वापस dev == pdev ? BONDING_SLAVE_STATE_ACTIVE :
				BONDING_SLAVE_STATE_INACTIVE;
	पूर्ण

	वापस BONDING_SLAVE_STATE_NA;
पूर्ण

#घोषणा REQUIRED_BOND_STATES		(BONDING_SLAVE_STATE_ACTIVE |	\
					 BONDING_SLAVE_STATE_NA)
अटल bool
is_eth_port_of_netdev_filter(काष्ठा ib_device *ib_dev, u32 port,
			     काष्ठा net_device *rdma_ndev, व्योम *cookie)
अणु
	काष्ठा net_device *real_dev;
	bool res;

	अगर (!rdma_ndev)
		वापस false;

	rcu_पढ़ो_lock();
	real_dev = rdma_vlan_dev_real_dev(cookie);
	अगर (!real_dev)
		real_dev = cookie;

	res = ((rdma_is_upper_dev_rcu(rdma_ndev, cookie) &&
	       (is_eth_active_slave_of_bonding_rcu(rdma_ndev, real_dev) &
		REQUIRED_BOND_STATES)) ||
	       real_dev == rdma_ndev);

	rcu_पढ़ो_unlock();
	वापस res;
पूर्ण

अटल bool
is_eth_port_inactive_slave_filter(काष्ठा ib_device *ib_dev, u32 port,
				  काष्ठा net_device *rdma_ndev, व्योम *cookie)
अणु
	काष्ठा net_device *master_dev;
	bool res;

	अगर (!rdma_ndev)
		वापस false;

	rcu_पढ़ो_lock();
	master_dev = netdev_master_upper_dev_get_rcu(rdma_ndev);
	res = is_eth_active_slave_of_bonding_rcu(rdma_ndev, master_dev) ==
		BONDING_SLAVE_STATE_INACTIVE;
	rcu_पढ़ो_unlock();

	वापस res;
पूर्ण

/** is_ndev_क्रम_शेष_gid_filter - Check अगर a given netdevice
 * can be considered क्रम शेष GIDs or not.
 * @ib_dev:		IB device to check
 * @port:		Port to consider क्रम adding शेष GID
 * @rdma_ndev:		rdma netdevice poपूर्णांकer
 * @cookie_ndev:	Netdevice to consider to क्रमm a शेष GID
 *
 * is_ndev_क्रम_शेष_gid_filter() वापसs true अगर a given netdevice can be
 * considered क्रम deriving शेष RoCE GID, वापसs false otherwise.
 */
अटल bool
is_ndev_क्रम_शेष_gid_filter(काष्ठा ib_device *ib_dev, u32 port,
			       काष्ठा net_device *rdma_ndev, व्योम *cookie)
अणु
	काष्ठा net_device *cookie_ndev = cookie;
	bool res;

	अगर (!rdma_ndev)
		वापस false;

	rcu_पढ़ो_lock();

	/*
	 * When rdma netdevice is used in bonding, bonding master netdevice
	 * should be considered क्रम शेष GIDs. Thereक्रमe, ignore slave rdma
	 * netdevices when bonding is considered.
	 * Additionally when event(cookie) netdevice is bond master device,
	 * make sure that it the upper netdevice of rdma netdevice.
	 */
	res = ((cookie_ndev == rdma_ndev && !netअगर_is_bond_slave(rdma_ndev)) ||
	       (netअगर_is_bond_master(cookie_ndev) &&
		rdma_is_upper_dev_rcu(rdma_ndev, cookie_ndev)));

	rcu_पढ़ो_unlock();
	वापस res;
पूर्ण

अटल bool pass_all_filter(काष्ठा ib_device *ib_dev, u32 port,
			    काष्ठा net_device *rdma_ndev, व्योम *cookie)
अणु
	वापस true;
पूर्ण

अटल bool upper_device_filter(काष्ठा ib_device *ib_dev, u32 port,
				काष्ठा net_device *rdma_ndev, व्योम *cookie)
अणु
	bool res;

	अगर (!rdma_ndev)
		वापस false;

	अगर (rdma_ndev == cookie)
		वापस true;

	rcu_पढ़ो_lock();
	res = rdma_is_upper_dev_rcu(rdma_ndev, cookie);
	rcu_पढ़ो_unlock();

	वापस res;
पूर्ण

/**
 * is_upper_ndev_bond_master_filter - Check अगर a given netdevice
 * is bond master device of netdevice of the the RDMA device of port.
 * @ib_dev:		IB device to check
 * @port:		Port to consider क्रम adding शेष GID
 * @rdma_ndev:		Poपूर्णांकer to rdma netdevice
 * @cookie:	        Netdevice to consider to क्रमm a शेष GID
 *
 * is_upper_ndev_bond_master_filter() वापसs true अगर a cookie_netdev
 * is bond master device and rdma_ndev is its lower netdevice. It might
 * not have been established as slave device yet.
 */
अटल bool
is_upper_ndev_bond_master_filter(काष्ठा ib_device *ib_dev, u32 port,
				 काष्ठा net_device *rdma_ndev,
				 व्योम *cookie)
अणु
	काष्ठा net_device *cookie_ndev = cookie;
	bool match = false;

	अगर (!rdma_ndev)
		वापस false;

	rcu_पढ़ो_lock();
	अगर (netअगर_is_bond_master(cookie_ndev) &&
	    rdma_is_upper_dev_rcu(rdma_ndev, cookie_ndev))
		match = true;
	rcu_पढ़ो_unlock();
	वापस match;
पूर्ण

अटल व्योम update_gid_ip(क्रमागत gid_op_type gid_op,
			  काष्ठा ib_device *ib_dev,
			  u32 port, काष्ठा net_device *ndev,
			  काष्ठा sockaddr *addr)
अणु
	जोड़ ib_gid gid;
	काष्ठा ib_gid_attr gid_attr;

	rdma_ip2gid(addr, &gid);
	स_रखो(&gid_attr, 0, माप(gid_attr));
	gid_attr.ndev = ndev;

	update_gid(gid_op, ib_dev, port, &gid, &gid_attr);
पूर्ण

अटल व्योम bond_delete_netdev_शेष_gids(काष्ठा ib_device *ib_dev,
					    u32 port,
					    काष्ठा net_device *rdma_ndev,
					    काष्ठा net_device *event_ndev)
अणु
	काष्ठा net_device *real_dev = rdma_vlan_dev_real_dev(event_ndev);
	अचिन्हित दीर्घ gid_type_mask;

	अगर (!rdma_ndev)
		वापस;

	अगर (!real_dev)
		real_dev = event_ndev;

	rcu_पढ़ो_lock();

	अगर (((rdma_ndev != event_ndev &&
	      !rdma_is_upper_dev_rcu(rdma_ndev, event_ndev)) ||
	     is_eth_active_slave_of_bonding_rcu(rdma_ndev, real_dev)
						 ==
	     BONDING_SLAVE_STATE_INACTIVE)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	rcu_पढ़ो_unlock();

	gid_type_mask = roce_gid_type_mask_support(ib_dev, port);

	ib_cache_gid_set_शेष_gid(ib_dev, port, rdma_ndev,
				     gid_type_mask,
				     IB_CACHE_GID_DEFAULT_MODE_DELETE);
पूर्ण

अटल व्योम क्रमागत_netdev_ipv4_ips(काष्ठा ib_device *ib_dev,
				 u32 port, काष्ठा net_device *ndev)
अणु
	स्थिर काष्ठा in_अगरaddr *अगरa;
	काष्ठा in_device *in_dev;
	काष्ठा sin_list अणु
		काष्ठा list_head	list;
		काष्ठा sockaddr_in	ip;
	पूर्ण;
	काष्ठा sin_list *sin_iter;
	काष्ठा sin_list *sin_temp;

	LIST_HEAD(sin_list);
	अगर (ndev->reg_state >= NETREG_UNREGISTERING)
		वापस;

	rcu_पढ़ो_lock();
	in_dev = __in_dev_get_rcu(ndev);
	अगर (!in_dev) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	in_dev_क्रम_each_अगरa_rcu(अगरa, in_dev) अणु
		काष्ठा sin_list *entry = kzalloc(माप(*entry), GFP_ATOMIC);

		अगर (!entry)
			जारी;

		entry->ip.sin_family = AF_INET;
		entry->ip.sin_addr.s_addr = अगरa->अगरa_address;
		list_add_tail(&entry->list, &sin_list);
	पूर्ण

	rcu_पढ़ो_unlock();

	list_क्रम_each_entry_safe(sin_iter, sin_temp, &sin_list, list) अणु
		update_gid_ip(GID_ADD, ib_dev, port, ndev,
			      (काष्ठा sockaddr *)&sin_iter->ip);
		list_del(&sin_iter->list);
		kमुक्त(sin_iter);
	पूर्ण
पूर्ण

अटल व्योम क्रमागत_netdev_ipv6_ips(काष्ठा ib_device *ib_dev,
				 u32 port, काष्ठा net_device *ndev)
अणु
	काष्ठा inet6_अगरaddr *अगरp;
	काष्ठा inet6_dev *in6_dev;
	काष्ठा sin6_list अणु
		काष्ठा list_head	list;
		काष्ठा sockaddr_in6	sin6;
	पूर्ण;
	काष्ठा sin6_list *sin6_iter;
	काष्ठा sin6_list *sin6_temp;
	काष्ठा ib_gid_attr gid_attr = अणु.ndev = ndevपूर्ण;
	LIST_HEAD(sin6_list);

	अगर (ndev->reg_state >= NETREG_UNREGISTERING)
		वापस;

	in6_dev = in6_dev_get(ndev);
	अगर (!in6_dev)
		वापस;

	पढ़ो_lock_bh(&in6_dev->lock);
	list_क्रम_each_entry(अगरp, &in6_dev->addr_list, अगर_list) अणु
		काष्ठा sin6_list *entry = kzalloc(माप(*entry), GFP_ATOMIC);

		अगर (!entry)
			जारी;

		entry->sin6.sin6_family = AF_INET6;
		entry->sin6.sin6_addr = अगरp->addr;
		list_add_tail(&entry->list, &sin6_list);
	पूर्ण
	पढ़ो_unlock_bh(&in6_dev->lock);

	in6_dev_put(in6_dev);

	list_क्रम_each_entry_safe(sin6_iter, sin6_temp, &sin6_list, list) अणु
		जोड़ ib_gid	gid;

		rdma_ip2gid((काष्ठा sockaddr *)&sin6_iter->sin6, &gid);
		update_gid(GID_ADD, ib_dev, port, &gid, &gid_attr);
		list_del(&sin6_iter->list);
		kमुक्त(sin6_iter);
	पूर्ण
पूर्ण

अटल व्योम _add_netdev_ips(काष्ठा ib_device *ib_dev, u32 port,
			    काष्ठा net_device *ndev)
अणु
	क्रमागत_netdev_ipv4_ips(ib_dev, port, ndev);
	अगर (IS_ENABLED(CONFIG_IPV6))
		क्रमागत_netdev_ipv6_ips(ib_dev, port, ndev);
पूर्ण

अटल व्योम add_netdev_ips(काष्ठा ib_device *ib_dev, u32 port,
			   काष्ठा net_device *rdma_ndev, व्योम *cookie)
अणु
	_add_netdev_ips(ib_dev, port, cookie);
पूर्ण

अटल व्योम del_netdev_ips(काष्ठा ib_device *ib_dev, u32 port,
			   काष्ठा net_device *rdma_ndev, व्योम *cookie)
अणु
	ib_cache_gid_del_all_netdev_gids(ib_dev, port, cookie);
पूर्ण

/**
 * del_शेष_gids - Delete शेष GIDs of the event/cookie netdevice
 * @ib_dev:	RDMA device poपूर्णांकer
 * @port:	Port of the RDMA device whose GID table to consider
 * @rdma_ndev:	Unused rdma netdevice
 * @cookie:	Poपूर्णांकer to event netdevice
 *
 * del_शेष_gids() deletes the शेष GIDs of the event/cookie netdevice.
 */
अटल व्योम del_शेष_gids(काष्ठा ib_device *ib_dev, u32 port,
			     काष्ठा net_device *rdma_ndev, व्योम *cookie)
अणु
	काष्ठा net_device *cookie_ndev = cookie;
	अचिन्हित दीर्घ gid_type_mask;

	gid_type_mask = roce_gid_type_mask_support(ib_dev, port);

	ib_cache_gid_set_शेष_gid(ib_dev, port, cookie_ndev, gid_type_mask,
				     IB_CACHE_GID_DEFAULT_MODE_DELETE);
पूर्ण

अटल व्योम add_शेष_gids(काष्ठा ib_device *ib_dev, u32 port,
			     काष्ठा net_device *rdma_ndev, व्योम *cookie)
अणु
	काष्ठा net_device *event_ndev = cookie;
	अचिन्हित दीर्घ gid_type_mask;

	gid_type_mask = roce_gid_type_mask_support(ib_dev, port);
	ib_cache_gid_set_शेष_gid(ib_dev, port, event_ndev, gid_type_mask,
				     IB_CACHE_GID_DEFAULT_MODE_SET);
पूर्ण

अटल व्योम क्रमागत_all_gids_of_dev_cb(काष्ठा ib_device *ib_dev,
				    u32 port,
				    काष्ठा net_device *rdma_ndev,
				    व्योम *cookie)
अणु
	काष्ठा net *net;
	काष्ठा net_device *ndev;

	/* Lock the rtnl to make sure the netdevs करोes not move under
	 * our feet
	 */
	rtnl_lock();
	करोwn_पढ़ो(&net_rwsem);
	क्रम_each_net(net)
		क्रम_each_netdev(net, ndev) अणु
			/*
			 * Filter and add शेष GIDs of the primary netdevice
			 * when not in bonding mode, or add शेष GIDs
			 * of bond master device, when in bonding mode.
			 */
			अगर (is_ndev_क्रम_शेष_gid_filter(ib_dev, port,
							   rdma_ndev, ndev))
				add_शेष_gids(ib_dev, port, rdma_ndev, ndev);

			अगर (is_eth_port_of_netdev_filter(ib_dev, port,
							 rdma_ndev, ndev))
				_add_netdev_ips(ib_dev, port, ndev);
		पूर्ण
	up_पढ़ो(&net_rwsem);
	rtnl_unlock();
पूर्ण

/**
 * rdma_roce_rescan_device - Rescan all of the network devices in the प्रणाली
 * and add their gids, as needed, to the relevant RoCE devices.
 *
 * @ib_dev:         the rdma device
 */
व्योम rdma_roce_rescan_device(काष्ठा ib_device *ib_dev)
अणु
	ib_क्रमागत_roce_netdev(ib_dev, pass_all_filter, शून्य,
			    क्रमागत_all_gids_of_dev_cb, शून्य);
पूर्ण
EXPORT_SYMBOL(rdma_roce_rescan_device);

अटल व्योम callback_क्रम_addr_gid_device_scan(काष्ठा ib_device *device,
					      u32 port,
					      काष्ठा net_device *rdma_ndev,
					      व्योम *cookie)
अणु
	काष्ठा update_gid_event_work *parsed = cookie;

	वापस update_gid(parsed->gid_op, device,
			  port, &parsed->gid,
			  &parsed->gid_attr);
पूर्ण

काष्ठा upper_list अणु
	काष्ठा list_head list;
	काष्ठा net_device *upper;
पूर्ण;

अटल पूर्णांक netdev_upper_walk(काष्ठा net_device *upper,
			     काष्ठा netdev_nested_priv *priv)
अणु
	काष्ठा upper_list *entry = kदो_स्मृति(माप(*entry), GFP_ATOMIC);
	काष्ठा list_head *upper_list = (काष्ठा list_head *)priv->data;

	अगर (!entry)
		वापस 0;

	list_add_tail(&entry->list, upper_list);
	dev_hold(upper);
	entry->upper = upper;

	वापस 0;
पूर्ण

अटल व्योम handle_netdev_upper(काष्ठा ib_device *ib_dev, u32 port,
				व्योम *cookie,
				व्योम (*handle_netdev)(काष्ठा ib_device *ib_dev,
						      u32 port,
						      काष्ठा net_device *ndev))
अणु
	काष्ठा net_device *ndev = cookie;
	काष्ठा netdev_nested_priv priv;
	काष्ठा upper_list *upper_iter;
	काष्ठा upper_list *upper_temp;
	LIST_HEAD(upper_list);

	priv.data = &upper_list;
	rcu_पढ़ो_lock();
	netdev_walk_all_upper_dev_rcu(ndev, netdev_upper_walk, &priv);
	rcu_पढ़ो_unlock();

	handle_netdev(ib_dev, port, ndev);
	list_क्रम_each_entry_safe(upper_iter, upper_temp, &upper_list,
				 list) अणु
		handle_netdev(ib_dev, port, upper_iter->upper);
		dev_put(upper_iter->upper);
		list_del(&upper_iter->list);
		kमुक्त(upper_iter);
	पूर्ण
पूर्ण

अटल व्योम _roce_del_all_netdev_gids(काष्ठा ib_device *ib_dev, u32 port,
				      काष्ठा net_device *event_ndev)
अणु
	ib_cache_gid_del_all_netdev_gids(ib_dev, port, event_ndev);
पूर्ण

अटल व्योम del_netdev_upper_ips(काष्ठा ib_device *ib_dev, u32 port,
				 काष्ठा net_device *rdma_ndev, व्योम *cookie)
अणु
	handle_netdev_upper(ib_dev, port, cookie, _roce_del_all_netdev_gids);
पूर्ण

अटल व्योम add_netdev_upper_ips(काष्ठा ib_device *ib_dev, u32 port,
				 काष्ठा net_device *rdma_ndev, व्योम *cookie)
अणु
	handle_netdev_upper(ib_dev, port, cookie, _add_netdev_ips);
पूर्ण

अटल व्योम del_netdev_शेष_ips_join(काष्ठा ib_device *ib_dev, u32 port,
					काष्ठा net_device *rdma_ndev,
					व्योम *cookie)
अणु
	काष्ठा net_device *master_ndev;

	rcu_पढ़ो_lock();
	master_ndev = netdev_master_upper_dev_get_rcu(rdma_ndev);
	अगर (master_ndev)
		dev_hold(master_ndev);
	rcu_पढ़ो_unlock();

	अगर (master_ndev) अणु
		bond_delete_netdev_शेष_gids(ib_dev, port, rdma_ndev,
						master_ndev);
		dev_put(master_ndev);
	पूर्ण
पूर्ण

/* The following functions operate on all IB devices. netdevice_event and
 * addr_event execute ib_क्रमागत_all_roce_netdevs through a work.
 * ib_क्रमागत_all_roce_netdevs iterates through all IB devices.
 */

अटल व्योम netdevice_event_work_handler(काष्ठा work_काष्ठा *_work)
अणु
	काष्ठा netdev_event_work *work =
		container_of(_work, काष्ठा netdev_event_work, work);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(work->cmds) && work->cmds[i].cb; i++) अणु
		ib_क्रमागत_all_roce_netdevs(work->cmds[i].filter,
					 work->cmds[i].filter_ndev,
					 work->cmds[i].cb,
					 work->cmds[i].ndev);
		dev_put(work->cmds[i].ndev);
		dev_put(work->cmds[i].filter_ndev);
	पूर्ण

	kमुक्त(work);
पूर्ण

अटल पूर्णांक netdevice_queue_work(काष्ठा netdev_event_work_cmd *cmds,
				काष्ठा net_device *ndev)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा netdev_event_work *ndev_work =
		kदो_स्मृति(माप(*ndev_work), GFP_KERNEL);

	अगर (!ndev_work)
		वापस NOTIFY_DONE;

	स_नकल(ndev_work->cmds, cmds, माप(ndev_work->cmds));
	क्रम (i = 0; i < ARRAY_SIZE(ndev_work->cmds) && ndev_work->cmds[i].cb; i++) अणु
		अगर (!ndev_work->cmds[i].ndev)
			ndev_work->cmds[i].ndev = ndev;
		अगर (!ndev_work->cmds[i].filter_ndev)
			ndev_work->cmds[i].filter_ndev = ndev;
		dev_hold(ndev_work->cmds[i].ndev);
		dev_hold(ndev_work->cmds[i].filter_ndev);
	पूर्ण
	INIT_WORK(&ndev_work->work, netdevice_event_work_handler);

	queue_work(gid_cache_wq, &ndev_work->work);

	वापस NOTIFY_DONE;
पूर्ण

अटल स्थिर काष्ठा netdev_event_work_cmd add_cmd = अणु
	.cb	= add_netdev_ips,
	.filter	= is_eth_port_of_netdev_filter
पूर्ण;

अटल स्थिर काष्ठा netdev_event_work_cmd add_cmd_upper_ips = अणु
	.cb	= add_netdev_upper_ips,
	.filter = is_eth_port_of_netdev_filter
पूर्ण;

अटल व्योम
ndev_event_unlink(काष्ठा netdev_notअगरier_changeupper_info *changeupper_info,
		  काष्ठा netdev_event_work_cmd *cmds)
अणु
	अटल स्थिर काष्ठा netdev_event_work_cmd
			upper_ips_del_cmd = अणु
				.cb	= del_netdev_upper_ips,
				.filter	= upper_device_filter
	पूर्ण;

	cmds[0] = upper_ips_del_cmd;
	cmds[0].ndev = changeupper_info->upper_dev;
	cmds[1] = add_cmd;
पूर्ण

अटल स्थिर काष्ठा netdev_event_work_cmd bonding_शेष_add_cmd = अणु
	.cb	= add_शेष_gids,
	.filter	= is_upper_ndev_bond_master_filter
पूर्ण;

अटल व्योम
ndev_event_link(काष्ठा net_device *event_ndev,
		काष्ठा netdev_notअगरier_changeupper_info *changeupper_info,
		काष्ठा netdev_event_work_cmd *cmds)
अणु
	अटल स्थिर काष्ठा netdev_event_work_cmd
			bonding_शेष_del_cmd = अणु
				.cb	= del_शेष_gids,
				.filter	= is_upper_ndev_bond_master_filter
			पूर्ण;
	/*
	 * When a lower netdev is linked to its upper bonding
	 * netdev, delete lower slave netdev's शेष GIDs.
	 */
	cmds[0] = bonding_शेष_del_cmd;
	cmds[0].ndev = event_ndev;
	cmds[0].filter_ndev = changeupper_info->upper_dev;

	/* Now add bonding upper device शेष GIDs */
	cmds[1] = bonding_शेष_add_cmd;
	cmds[1].ndev = changeupper_info->upper_dev;
	cmds[1].filter_ndev = changeupper_info->upper_dev;

	/* Now add bonding upper device IP based GIDs */
	cmds[2] = add_cmd_upper_ips;
	cmds[2].ndev = changeupper_info->upper_dev;
	cmds[2].filter_ndev = changeupper_info->upper_dev;
पूर्ण

अटल व्योम netdevice_event_changeupper(काष्ठा net_device *event_ndev,
		काष्ठा netdev_notअगरier_changeupper_info *changeupper_info,
		काष्ठा netdev_event_work_cmd *cmds)
अणु
	अगर (changeupper_info->linking)
		ndev_event_link(event_ndev, changeupper_info, cmds);
	अन्यथा
		ndev_event_unlink(changeupper_info, cmds);
पूर्ण

अटल स्थिर काष्ठा netdev_event_work_cmd add_शेष_gid_cmd = अणु
	.cb	= add_शेष_gids,
	.filter	= is_ndev_क्रम_शेष_gid_filter,
पूर्ण;

अटल पूर्णांक netdevice_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			   व्योम *ptr)
अणु
	अटल स्थिर काष्ठा netdev_event_work_cmd del_cmd = अणु
		.cb = del_netdev_ips, .filter = pass_all_filterपूर्ण;
	अटल स्थिर काष्ठा netdev_event_work_cmd
			bonding_शेष_del_cmd_join = अणु
				.cb	= del_netdev_शेष_ips_join,
				.filter	= is_eth_port_inactive_slave_filter
			पूर्ण;
	अटल स्थिर काष्ठा netdev_event_work_cmd
			netdev_del_cmd = अणु
				.cb	= del_netdev_ips,
				.filter = is_eth_port_of_netdev_filter
			पूर्ण;
	अटल स्थिर काष्ठा netdev_event_work_cmd bonding_event_ips_del_cmd = अणु
		.cb = del_netdev_upper_ips, .filter = upper_device_filterपूर्ण;
	काष्ठा net_device *ndev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा netdev_event_work_cmd cmds[ROCE_NETDEV_CALLBACK_SZ] = अणु अणुशून्यपूर्ण पूर्ण;

	अगर (ndev->type != ARPHRD_ETHER)
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_REGISTER:
	हाल NETDEV_UP:
		cmds[0] = bonding_शेष_del_cmd_join;
		cmds[1] = add_शेष_gid_cmd;
		cmds[2] = add_cmd;
		अवरोध;

	हाल NETDEV_UNREGISTER:
		अगर (ndev->reg_state < NETREG_UNREGISTERED)
			cmds[0] = del_cmd;
		अन्यथा
			वापस NOTIFY_DONE;
		अवरोध;

	हाल NETDEV_CHANGEADDR:
		cmds[0] = netdev_del_cmd;
		अगर (ndev->reg_state == NETREG_REGISTERED) अणु
			cmds[1] = add_शेष_gid_cmd;
			cmds[2] = add_cmd;
		पूर्ण
		अवरोध;

	हाल NETDEV_CHANGEUPPER:
		netdevice_event_changeupper(ndev,
			container_of(ptr, काष्ठा netdev_notअगरier_changeupper_info, info),
			cmds);
		अवरोध;

	हाल NETDEV_BONDING_FAILOVER:
		cmds[0] = bonding_event_ips_del_cmd;
		/* Add शेष GIDs of the bond device */
		cmds[1] = bonding_शेष_add_cmd;
		/* Add IP based GIDs of the bond device */
		cmds[2] = add_cmd_upper_ips;
		अवरोध;

	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	वापस netdevice_queue_work(cmds, ndev);
पूर्ण

अटल व्योम update_gid_event_work_handler(काष्ठा work_काष्ठा *_work)
अणु
	काष्ठा update_gid_event_work *work =
		container_of(_work, काष्ठा update_gid_event_work, work);

	ib_क्रमागत_all_roce_netdevs(is_eth_port_of_netdev_filter,
				 work->gid_attr.ndev,
				 callback_क्रम_addr_gid_device_scan, work);

	dev_put(work->gid_attr.ndev);
	kमुक्त(work);
पूर्ण

अटल पूर्णांक addr_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
		      काष्ठा sockaddr *sa, काष्ठा net_device *ndev)
अणु
	काष्ठा update_gid_event_work *work;
	क्रमागत gid_op_type gid_op;

	अगर (ndev->type != ARPHRD_ETHER)
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_UP:
		gid_op = GID_ADD;
		अवरोध;

	हाल NETDEV_DOWN:
		gid_op = GID_DEL;
		अवरोध;

	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	work = kदो_स्मृति(माप(*work), GFP_ATOMIC);
	अगर (!work)
		वापस NOTIFY_DONE;

	INIT_WORK(&work->work, update_gid_event_work_handler);

	rdma_ip2gid(sa, &work->gid);
	work->gid_op = gid_op;

	स_रखो(&work->gid_attr, 0, माप(work->gid_attr));
	dev_hold(ndev);
	work->gid_attr.ndev   = ndev;

	queue_work(gid_cache_wq, &work->work);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक inetaddr_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			  व्योम *ptr)
अणु
	काष्ठा sockaddr_in	in;
	काष्ठा net_device	*ndev;
	काष्ठा in_अगरaddr	*अगरa = ptr;

	in.sin_family = AF_INET;
	in.sin_addr.s_addr = अगरa->अगरa_address;
	ndev = अगरa->अगरa_dev->dev;

	वापस addr_event(this, event, (काष्ठा sockaddr *)&in, ndev);
पूर्ण

अटल पूर्णांक inet6addr_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			   व्योम *ptr)
अणु
	काष्ठा sockaddr_in6	in6;
	काष्ठा net_device	*ndev;
	काष्ठा inet6_अगरaddr	*अगरa6 = ptr;

	in6.sin6_family = AF_INET6;
	in6.sin6_addr = अगरa6->addr;
	ndev = अगरa6->idev->dev;

	वापस addr_event(this, event, (काष्ठा sockaddr *)&in6, ndev);
पूर्ण

अटल काष्ठा notअगरier_block nb_netdevice = अणु
	.notअगरier_call = netdevice_event
पूर्ण;

अटल काष्ठा notअगरier_block nb_inetaddr = अणु
	.notअगरier_call = inetaddr_event
पूर्ण;

अटल काष्ठा notअगरier_block nb_inet6addr = अणु
	.notअगरier_call = inet6addr_event
पूर्ण;

पूर्णांक __init roce_gid_mgmt_init(व्योम)
अणु
	gid_cache_wq = alloc_ordered_workqueue("gid-cache-wq", 0);
	अगर (!gid_cache_wq)
		वापस -ENOMEM;

	रेजिस्टर_inetaddr_notअगरier(&nb_inetaddr);
	अगर (IS_ENABLED(CONFIG_IPV6))
		रेजिस्टर_inet6addr_notअगरier(&nb_inet6addr);
	/* We relay on the netdevice notअगरier to क्रमागतerate all
	 * existing devices in the प्रणाली. Register to this notअगरier
	 * last to make sure we will not miss any IP add/del
	 * callbacks.
	 */
	रेजिस्टर_netdevice_notअगरier(&nb_netdevice);

	वापस 0;
पूर्ण

व्योम __निकास roce_gid_mgmt_cleanup(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_IPV6))
		unरेजिस्टर_inet6addr_notअगरier(&nb_inet6addr);
	unरेजिस्टर_inetaddr_notअगरier(&nb_inetaddr);
	unरेजिस्टर_netdevice_notअगरier(&nb_netdevice);
	/* Ensure all gid deletion tasks complete beक्रमe we go करोwn,
	 * to aव्योम any reference to मुक्त'd memory. By the समय
	 * ib-core is हटाओd, all physical devices have been हटाओd,
	 * so no issue with reमुख्यing hardware contexts.
	 */
	destroy_workqueue(gid_cache_wq);
पूर्ण
