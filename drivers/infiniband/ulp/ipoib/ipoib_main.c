<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 * Copyright (c) 2004 Voltaire, Inc. All rights reserved.
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

#समावेश "ipoib.h"

#समावेश <linux/module.h>

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <linux/अगर_arp.h>	/* For ARPHRD_xxx */

#समावेश <linux/ip.h>
#समावेश <linux/in.h>

#समावेश <linux/jhash.h>
#समावेश <net/arp.h>
#समावेश <net/addrconf.h>
#समावेश <linux/inetdevice.h>
#समावेश <rdma/ib_cache.h>

MODULE_AUTHOR("Roland Dreier");
MODULE_DESCRIPTION("IP-over-InfiniBand net driver");
MODULE_LICENSE("Dual BSD/GPL");

पूर्णांक ipoib_sendq_size __पढ़ो_mostly = IPOIB_TX_RING_SIZE;
पूर्णांक ipoib_recvq_size __पढ़ो_mostly = IPOIB_RX_RING_SIZE;

module_param_named(send_queue_size, ipoib_sendq_size, पूर्णांक, 0444);
MODULE_PARM_DESC(send_queue_size, "Number of descriptors in send queue");
module_param_named(recv_queue_size, ipoib_recvq_size, पूर्णांक, 0444);
MODULE_PARM_DESC(recv_queue_size, "Number of descriptors in receive queue");

#अगर_घोषित CONFIG_INFINIBAND_IPOIB_DEBUG
पूर्णांक ipoib_debug_level;

module_param_named(debug_level, ipoib_debug_level, पूर्णांक, 0644);
MODULE_PARM_DESC(debug_level, "Enable debug tracing if > 0");
#पूर्ण_अगर

काष्ठा ipoib_path_iter अणु
	काष्ठा net_device *dev;
	काष्ठा ipoib_path  path;
पूर्ण;

अटल स्थिर u8 ipv4_bcast_addr[] = अणु
	0x00, 0xff, 0xff, 0xff,
	0xff, 0x12, 0x40, 0x1b,	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,	0xff, 0xff, 0xff, 0xff
पूर्ण;

काष्ठा workqueue_काष्ठा *ipoib_workqueue;

काष्ठा ib_sa_client ipoib_sa_client;

अटल पूर्णांक ipoib_add_one(काष्ठा ib_device *device);
अटल व्योम ipoib_हटाओ_one(काष्ठा ib_device *device, व्योम *client_data);
अटल व्योम ipoib_neigh_reclaim(काष्ठा rcu_head *rp);
अटल काष्ठा net_device *ipoib_get_net_dev_by_params(
		काष्ठा ib_device *dev, u32 port, u16 pkey,
		स्थिर जोड़ ib_gid *gid, स्थिर काष्ठा sockaddr *addr,
		व्योम *client_data);
अटल पूर्णांक ipoib_set_mac(काष्ठा net_device *dev, व्योम *addr);
अटल पूर्णांक ipoib_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr,
		       पूर्णांक cmd);

अटल काष्ठा ib_client ipoib_client = अणु
	.name   = "ipoib",
	.add    = ipoib_add_one,
	.हटाओ = ipoib_हटाओ_one,
	.get_net_dev_by_params = ipoib_get_net_dev_by_params,
पूर्ण;

#अगर_घोषित CONFIG_INFINIBAND_IPOIB_DEBUG
अटल पूर्णांक ipoib_netdev_event(काष्ठा notअगरier_block *this,
			      अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा netdev_notअगरier_info *ni = ptr;
	काष्ठा net_device *dev = ni->dev;

	अगर (dev->netdev_ops->nकरो_खोलो != ipoib_खोलो)
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_REGISTER:
		ipoib_create_debug_files(dev);
		अवरोध;
	हाल NETDEV_CHANGENAME:
		ipoib_delete_debug_files(dev);
		ipoib_create_debug_files(dev);
		अवरोध;
	हाल NETDEV_UNREGISTER:
		ipoib_delete_debug_files(dev);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण
#पूर्ण_अगर

पूर्णांक ipoib_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	ipoib_dbg(priv, "bringing up interface\n");

	netअगर_carrier_off(dev);

	set_bit(IPOIB_FLAG_ADMIN_UP, &priv->flags);

	अगर (ipoib_ib_dev_खोलो(dev)) अणु
		अगर (!test_bit(IPOIB_PKEY_ASSIGNED, &priv->flags))
			वापस 0;
		जाओ err_disable;
	पूर्ण

	ipoib_ib_dev_up(dev);

	अगर (!test_bit(IPOIB_FLAG_SUBINTERFACE, &priv->flags)) अणु
		काष्ठा ipoib_dev_priv *cpriv;

		/* Bring up any child पूर्णांकerfaces too */
		करोwn_पढ़ो(&priv->vlan_rwsem);
		list_क्रम_each_entry(cpriv, &priv->child_पूर्णांकfs, list) अणु
			पूर्णांक flags;

			flags = cpriv->dev->flags;
			अगर (flags & IFF_UP)
				जारी;

			dev_change_flags(cpriv->dev, flags | IFF_UP, शून्य);
		पूर्ण
		up_पढ़ो(&priv->vlan_rwsem);
	पूर्ण अन्यथा अगर (priv->parent) अणु
		काष्ठा ipoib_dev_priv *ppriv = ipoib_priv(priv->parent);

		अगर (!test_bit(IPOIB_FLAG_ADMIN_UP, &ppriv->flags))
			ipoib_dbg(priv, "parent device %s is not up, so child device may be not functioning.\n",
				  ppriv->dev->name);
	पूर्ण
	netअगर_start_queue(dev);

	वापस 0;

err_disable:
	clear_bit(IPOIB_FLAG_ADMIN_UP, &priv->flags);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ipoib_stop(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	ipoib_dbg(priv, "stopping interface\n");

	clear_bit(IPOIB_FLAG_ADMIN_UP, &priv->flags);

	netअगर_stop_queue(dev);

	ipoib_ib_dev_करोwn(dev);
	ipoib_ib_dev_stop(dev);

	अगर (!test_bit(IPOIB_FLAG_SUBINTERFACE, &priv->flags)) अणु
		काष्ठा ipoib_dev_priv *cpriv;

		/* Bring करोwn any child पूर्णांकerfaces too */
		करोwn_पढ़ो(&priv->vlan_rwsem);
		list_क्रम_each_entry(cpriv, &priv->child_पूर्णांकfs, list) अणु
			पूर्णांक flags;

			flags = cpriv->dev->flags;
			अगर (!(flags & IFF_UP))
				जारी;

			dev_change_flags(cpriv->dev, flags & ~IFF_UP, शून्य);
		पूर्ण
		up_पढ़ो(&priv->vlan_rwsem);
	पूर्ण

	वापस 0;
पूर्ण

अटल netdev_features_t ipoib_fix_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	अगर (test_bit(IPOIB_FLAG_ADMIN_CM, &priv->flags))
		features &= ~(NETIF_F_IP_CSUM | NETIF_F_TSO);

	वापस features;
पूर्ण

अटल पूर्णांक ipoib_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	पूर्णांक ret = 0;

	/* dev->mtu > 2K ==> connected mode */
	अगर (ipoib_cm_admin_enabled(dev)) अणु
		अगर (new_mtu > ipoib_cm_max_mtu(dev))
			वापस -EINVAL;

		अगर (new_mtu > priv->mcast_mtu)
			ipoib_warn(priv, "mtu > %d will cause multicast packet drops.\n",
				   priv->mcast_mtu);

		dev->mtu = new_mtu;
		वापस 0;
	पूर्ण

	अगर (new_mtu < (ETH_MIN_MTU + IPOIB_ENCAP_LEN) ||
	    new_mtu > IPOIB_UD_MTU(priv->max_ib_mtu))
		वापस -EINVAL;

	priv->admin_mtu = new_mtu;

	अगर (priv->mcast_mtu < priv->admin_mtu)
		ipoib_dbg(priv, "MTU must be smaller than the underlying "
				"link layer MTU - 4 (%u)\n", priv->mcast_mtu);

	new_mtu = min(priv->mcast_mtu, priv->admin_mtu);

	अगर (priv->rn_ops->nकरो_change_mtu) अणु
		bool carrier_status = netअगर_carrier_ok(dev);

		netअगर_carrier_off(dev);

		/* notअगरy lower level on the real mtu */
		ret = priv->rn_ops->nकरो_change_mtu(dev, new_mtu);

		अगर (carrier_status)
			netअगर_carrier_on(dev);
	पूर्ण अन्यथा अणु
		dev->mtu = new_mtu;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ipoib_get_stats(काष्ठा net_device *dev,
			    काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	अगर (priv->rn_ops->nकरो_get_stats64)
		priv->rn_ops->nकरो_get_stats64(dev, stats);
	अन्यथा
		netdev_stats_to_stats64(stats, &dev->stats);
पूर्ण

/* Called with an RCU पढ़ो lock taken */
अटल bool ipoib_is_dev_match_addr_rcu(स्थिर काष्ठा sockaddr *addr,
					काष्ठा net_device *dev)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा in_device *in_dev;
	काष्ठा sockaddr_in *addr_in = (काष्ठा sockaddr_in *)addr;
	काष्ठा sockaddr_in6 *addr_in6 = (काष्ठा sockaddr_in6 *)addr;
	__be32 ret_addr;

	चयन (addr->sa_family) अणु
	हाल AF_INET:
		in_dev = in_dev_get(dev);
		अगर (!in_dev)
			वापस false;

		ret_addr = inet_confirm_addr(net, in_dev, 0,
					     addr_in->sin_addr.s_addr,
					     RT_SCOPE_HOST);
		in_dev_put(in_dev);
		अगर (ret_addr)
			वापस true;

		अवरोध;
	हाल AF_INET6:
		अगर (IS_ENABLED(CONFIG_IPV6) &&
		    ipv6_chk_addr(net, &addr_in6->sin6_addr, dev, 1))
			वापस true;

		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

/**
 * Find the master net_device on top of the given net_device.
 * @dev: base IPoIB net_device
 *
 * Returns the master net_device with a reference held, or the same net_device
 * अगर no master exists.
 */
अटल काष्ठा net_device *ipoib_get_master_net_dev(काष्ठा net_device *dev)
अणु
	काष्ठा net_device *master;

	rcu_पढ़ो_lock();
	master = netdev_master_upper_dev_get_rcu(dev);
	अगर (master)
		dev_hold(master);
	rcu_पढ़ो_unlock();

	अगर (master)
		वापस master;

	dev_hold(dev);
	वापस dev;
पूर्ण

काष्ठा ipoib_walk_data अणु
	स्थिर काष्ठा sockaddr *addr;
	काष्ठा net_device *result;
पूर्ण;

अटल पूर्णांक ipoib_upper_walk(काष्ठा net_device *upper,
			    काष्ठा netdev_nested_priv *priv)
अणु
	काष्ठा ipoib_walk_data *data = (काष्ठा ipoib_walk_data *)priv->data;
	पूर्णांक ret = 0;

	अगर (ipoib_is_dev_match_addr_rcu(data->addr, upper)) अणु
		dev_hold(upper);
		data->result = upper;
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * Find a net_device matching the given address, which is an upper device of
 * the given net_device.
 * @addr: IP address to look क्रम.
 * @dev: base IPoIB net_device
 *
 * If found, वापसs the net_device with a reference held. Otherwise वापस
 * शून्य.
 */
अटल काष्ठा net_device *ipoib_get_net_dev_match_addr(
		स्थिर काष्ठा sockaddr *addr, काष्ठा net_device *dev)
अणु
	काष्ठा netdev_nested_priv priv;
	काष्ठा ipoib_walk_data data = अणु
		.addr = addr,
	पूर्ण;

	priv.data = (व्योम *)&data;
	rcu_पढ़ो_lock();
	अगर (ipoib_is_dev_match_addr_rcu(addr, dev)) अणु
		dev_hold(dev);
		data.result = dev;
		जाओ out;
	पूर्ण

	netdev_walk_all_upper_dev_rcu(dev, ipoib_upper_walk, &priv);
out:
	rcu_पढ़ो_unlock();
	वापस data.result;
पूर्ण

/* वापसs the number of IPoIB netdevs on top a given ipoib device matching a
 * pkey_index and address, अगर one exists.
 *
 * @found_net_dev: contains a matching net_device अगर the वापस value >= 1,
 * with a reference held. */
अटल पूर्णांक ipoib_match_gid_pkey_addr(काष्ठा ipoib_dev_priv *priv,
				     स्थिर जोड़ ib_gid *gid,
				     u16 pkey_index,
				     स्थिर काष्ठा sockaddr *addr,
				     पूर्णांक nesting,
				     काष्ठा net_device **found_net_dev)
अणु
	काष्ठा ipoib_dev_priv *child_priv;
	काष्ठा net_device *net_dev = शून्य;
	पूर्णांक matches = 0;

	अगर (priv->pkey_index == pkey_index &&
	    (!gid || !स_भेद(gid, &priv->local_gid, माप(*gid)))) अणु
		अगर (!addr) अणु
			net_dev = ipoib_get_master_net_dev(priv->dev);
		पूर्ण अन्यथा अणु
			/* Verअगरy the net_device matches the IP address, as
			 * IPoIB child devices currently share a GID. */
			net_dev = ipoib_get_net_dev_match_addr(addr, priv->dev);
		पूर्ण
		अगर (net_dev) अणु
			अगर (!*found_net_dev)
				*found_net_dev = net_dev;
			अन्यथा
				dev_put(net_dev);
			++matches;
		पूर्ण
	पूर्ण

	/* Check child पूर्णांकerfaces */
	करोwn_पढ़ो_nested(&priv->vlan_rwsem, nesting);
	list_क्रम_each_entry(child_priv, &priv->child_पूर्णांकfs, list) अणु
		matches += ipoib_match_gid_pkey_addr(child_priv, gid,
						    pkey_index, addr,
						    nesting + 1,
						    found_net_dev);
		अगर (matches > 1)
			अवरोध;
	पूर्ण
	up_पढ़ो(&priv->vlan_rwsem);

	वापस matches;
पूर्ण

/* Returns the number of matching net_devs found (between 0 and 2). Also
 * वापस the matching net_device in the @net_dev parameter, holding a
 * reference to the net_device, अगर the number of matches >= 1 */
अटल पूर्णांक __ipoib_get_net_dev_by_params(काष्ठा list_head *dev_list, u32 port,
					 u16 pkey_index,
					 स्थिर जोड़ ib_gid *gid,
					 स्थिर काष्ठा sockaddr *addr,
					 काष्ठा net_device **net_dev)
अणु
	काष्ठा ipoib_dev_priv *priv;
	पूर्णांक matches = 0;

	*net_dev = शून्य;

	list_क्रम_each_entry(priv, dev_list, list) अणु
		अगर (priv->port != port)
			जारी;

		matches += ipoib_match_gid_pkey_addr(priv, gid, pkey_index,
						     addr, 0, net_dev);
		अगर (matches > 1)
			अवरोध;
	पूर्ण

	वापस matches;
पूर्ण

अटल काष्ठा net_device *ipoib_get_net_dev_by_params(
		काष्ठा ib_device *dev, u32 port, u16 pkey,
		स्थिर जोड़ ib_gid *gid, स्थिर काष्ठा sockaddr *addr,
		व्योम *client_data)
अणु
	काष्ठा net_device *net_dev;
	काष्ठा list_head *dev_list = client_data;
	u16 pkey_index;
	पूर्णांक matches;
	पूर्णांक ret;

	अगर (!rdma_protocol_ib(dev, port))
		वापस शून्य;

	ret = ib_find_cached_pkey(dev, port, pkey, &pkey_index);
	अगर (ret)
		वापस शून्य;

	/* See अगर we can find a unique device matching the L2 parameters */
	matches = __ipoib_get_net_dev_by_params(dev_list, port, pkey_index,
						gid, शून्य, &net_dev);

	चयन (matches) अणु
	हाल 0:
		वापस शून्य;
	हाल 1:
		वापस net_dev;
	पूर्ण

	dev_put(net_dev);

	/* Couldn't find a unique device with L2 parameters only. Use L3
	 * address to uniquely match the net device */
	matches = __ipoib_get_net_dev_by_params(dev_list, port, pkey_index,
						gid, addr, &net_dev);
	चयन (matches) अणु
	हाल 0:
		वापस शून्य;
	शेष:
		dev_warn_ratelimited(&dev->dev,
				     "duplicate IP address detected\n");
		fallthrough;
	हाल 1:
		वापस net_dev;
	पूर्ण
पूर्ण

पूर्णांक ipoib_set_mode(काष्ठा net_device *dev, स्थिर अक्षर *buf)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	अगर ((test_bit(IPOIB_FLAG_ADMIN_CM, &priv->flags) &&
	     !म_भेद(buf, "connected\n")) ||
	     (!test_bit(IPOIB_FLAG_ADMIN_CM, &priv->flags) &&
	     !म_भेद(buf, "datagram\n"))) अणु
		वापस 0;
	पूर्ण

	/* flush paths अगर we चयन modes so that connections are restarted */
	अगर (IPOIB_CM_SUPPORTED(dev->dev_addr) && !म_भेद(buf, "connected\n")) अणु
		set_bit(IPOIB_FLAG_ADMIN_CM, &priv->flags);
		ipoib_warn(priv, "enabling connected mode "
			   "will cause multicast packet drops\n");
		netdev_update_features(dev);
		dev_set_mtu(dev, ipoib_cm_max_mtu(dev));
		netअगर_set_real_num_tx_queues(dev, 1);
		rtnl_unlock();
		priv->tx_wr.wr.send_flags &= ~IB_SEND_IP_CSUM;

		ipoib_flush_paths(dev);
		वापस (!rtnl_trylock()) ? -EBUSY : 0;
	पूर्ण

	अगर (!म_भेद(buf, "datagram\n")) अणु
		clear_bit(IPOIB_FLAG_ADMIN_CM, &priv->flags);
		netdev_update_features(dev);
		dev_set_mtu(dev, min(priv->mcast_mtu, dev->mtu));
		netअगर_set_real_num_tx_queues(dev, dev->num_tx_queues);
		rtnl_unlock();
		ipoib_flush_paths(dev);
		वापस (!rtnl_trylock()) ? -EBUSY : 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

काष्ठा ipoib_path *__path_find(काष्ठा net_device *dev, व्योम *gid)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा rb_node *n = priv->path_tree.rb_node;
	काष्ठा ipoib_path *path;
	पूर्णांक ret;

	जबतक (n) अणु
		path = rb_entry(n, काष्ठा ipoib_path, rb_node);

		ret = स_भेद(gid, path->pathrec.dgid.raw,
			     माप (जोड़ ib_gid));

		अगर (ret < 0)
			n = n->rb_left;
		अन्यथा अगर (ret > 0)
			n = n->rb_right;
		अन्यथा
			वापस path;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक __path_add(काष्ठा net_device *dev, काष्ठा ipoib_path *path)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा rb_node **n = &priv->path_tree.rb_node;
	काष्ठा rb_node *pn = शून्य;
	काष्ठा ipoib_path *tpath;
	पूर्णांक ret;

	जबतक (*n) अणु
		pn = *n;
		tpath = rb_entry(pn, काष्ठा ipoib_path, rb_node);

		ret = स_भेद(path->pathrec.dgid.raw, tpath->pathrec.dgid.raw,
			     माप (जोड़ ib_gid));
		अगर (ret < 0)
			n = &pn->rb_left;
		अन्यथा अगर (ret > 0)
			n = &pn->rb_right;
		अन्यथा
			वापस -EEXIST;
	पूर्ण

	rb_link_node(&path->rb_node, pn, n);
	rb_insert_color(&path->rb_node, &priv->path_tree);

	list_add_tail(&path->list, &priv->path_list);

	वापस 0;
पूर्ण

अटल व्योम path_मुक्त(काष्ठा net_device *dev, काष्ठा ipoib_path *path)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = __skb_dequeue(&path->queue)))
		dev_kमुक्त_skb_irq(skb);

	ipoib_dbg(ipoib_priv(dev), "%s\n", __func__);

	/* हटाओ all neigh connected to this path */
	ipoib_del_neighs_by_gid(dev, path->pathrec.dgid.raw);

	अगर (path->ah)
		ipoib_put_ah(path->ah);

	kमुक्त(path);
पूर्ण

#अगर_घोषित CONFIG_INFINIBAND_IPOIB_DEBUG

काष्ठा ipoib_path_iter *ipoib_path_iter_init(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_path_iter *iter;

	iter = kदो_स्मृति(माप(*iter), GFP_KERNEL);
	अगर (!iter)
		वापस शून्य;

	iter->dev = dev;
	स_रखो(iter->path.pathrec.dgid.raw, 0, 16);

	अगर (ipoib_path_iter_next(iter)) अणु
		kमुक्त(iter);
		वापस शून्य;
	पूर्ण

	वापस iter;
पूर्ण

पूर्णांक ipoib_path_iter_next(काष्ठा ipoib_path_iter *iter)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(iter->dev);
	काष्ठा rb_node *n;
	काष्ठा ipoib_path *path;
	पूर्णांक ret = 1;

	spin_lock_irq(&priv->lock);

	n = rb_first(&priv->path_tree);

	जबतक (n) अणु
		path = rb_entry(n, काष्ठा ipoib_path, rb_node);

		अगर (स_भेद(iter->path.pathrec.dgid.raw, path->pathrec.dgid.raw,
			   माप (जोड़ ib_gid)) < 0) अणु
			iter->path = *path;
			ret = 0;
			अवरोध;
		पूर्ण

		n = rb_next(n);
	पूर्ण

	spin_unlock_irq(&priv->lock);

	वापस ret;
पूर्ण

व्योम ipoib_path_iter_पढ़ो(काष्ठा ipoib_path_iter *iter,
			  काष्ठा ipoib_path *path)
अणु
	*path = iter->path;
पूर्ण

#पूर्ण_अगर /* CONFIG_INFINIBAND_IPOIB_DEBUG */

व्योम ipoib_mark_paths_invalid(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ipoib_path *path, *tp;

	spin_lock_irq(&priv->lock);

	list_क्रम_each_entry_safe(path, tp, &priv->path_list, list) अणु
		ipoib_dbg(priv, "mark path LID 0x%08x GID %pI6 invalid\n",
			  be32_to_cpu(sa_path_get_dlid(&path->pathrec)),
			  path->pathrec.dgid.raw);
		अगर (path->ah)
			path->ah->valid = 0;
	पूर्ण

	spin_unlock_irq(&priv->lock);
पूर्ण

अटल व्योम push_pseuकरो_header(काष्ठा sk_buff *skb, स्थिर अक्षर *daddr)
अणु
	काष्ठा ipoib_pseuकरो_header *phdr;

	phdr = skb_push(skb, माप(*phdr));
	स_नकल(phdr->hwaddr, daddr, INFINIBAND_ALEN);
पूर्ण

व्योम ipoib_flush_paths(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ipoib_path *path, *tp;
	LIST_HEAD(हटाओ_list);
	अचिन्हित दीर्घ flags;

	netअगर_tx_lock_bh(dev);
	spin_lock_irqsave(&priv->lock, flags);

	list_splice_init(&priv->path_list, &हटाओ_list);

	list_क्रम_each_entry(path, &हटाओ_list, list)
		rb_erase(&path->rb_node, &priv->path_tree);

	list_क्रम_each_entry_safe(path, tp, &हटाओ_list, list) अणु
		अगर (path->query)
			ib_sa_cancel_query(path->query_id, path->query);
		spin_unlock_irqrestore(&priv->lock, flags);
		netअगर_tx_unlock_bh(dev);
		रुको_क्रम_completion(&path->करोne);
		path_मुक्त(dev, path);
		netअगर_tx_lock_bh(dev);
		spin_lock_irqsave(&priv->lock, flags);
	पूर्ण

	spin_unlock_irqrestore(&priv->lock, flags);
	netअगर_tx_unlock_bh(dev);
पूर्ण

अटल व्योम path_rec_completion(पूर्णांक status,
				काष्ठा sa_path_rec *pathrec,
				व्योम *path_ptr)
अणु
	काष्ठा ipoib_path *path = path_ptr;
	काष्ठा net_device *dev = path->dev;
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ipoib_ah *ah = शून्य;
	काष्ठा ipoib_ah *old_ah = शून्य;
	काष्ठा ipoib_neigh *neigh, *tn;
	काष्ठा sk_buff_head skqueue;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;

	अगर (!status)
		ipoib_dbg(priv, "PathRec LID 0x%04x for GID %pI6\n",
			  be32_to_cpu(sa_path_get_dlid(pathrec)),
			  pathrec->dgid.raw);
	अन्यथा
		ipoib_dbg(priv, "PathRec status %d for GID %pI6\n",
			  status, path->pathrec.dgid.raw);

	skb_queue_head_init(&skqueue);

	अगर (!status) अणु
		काष्ठा rdma_ah_attr av;

		अगर (!ib_init_ah_attr_from_path(priv->ca, priv->port,
					       pathrec, &av, शून्य)) अणु
			ah = ipoib_create_ah(dev, priv->pd, &av);
			rdma_destroy_ah_attr(&av);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);

	अगर (!IS_ERR_OR_शून्य(ah)) अणु
		/*
		 * pathrec.dgid is used as the database key from the LLADDR,
		 * it must reमुख्य unchanged even अगर the SA वापसs a dअगरferent
		 * GID to use in the AH.
		 */
		अगर (स_भेद(pathrec->dgid.raw, path->pathrec.dgid.raw,
			   माप(जोड़ ib_gid))) अणु
			ipoib_dbg(
				priv,
				"%s got PathRec for gid %pI6 while asked for %pI6\n",
				dev->name, pathrec->dgid.raw,
				path->pathrec.dgid.raw);
			स_नकल(pathrec->dgid.raw, path->pathrec.dgid.raw,
			       माप(जोड़ ib_gid));
		पूर्ण

		path->pathrec = *pathrec;

		old_ah   = path->ah;
		path->ah = ah;

		ipoib_dbg(priv, "created address handle %p for LID 0x%04x, SL %d\n",
			  ah, be32_to_cpu(sa_path_get_dlid(pathrec)),
			  pathrec->sl);

		जबतक ((skb = __skb_dequeue(&path->queue)))
			__skb_queue_tail(&skqueue, skb);

		list_क्रम_each_entry_safe(neigh, tn, &path->neigh_list, list) अणु
			अगर (neigh->ah) अणु
				WARN_ON(neigh->ah != old_ah);
				/*
				 * Dropping the ah reference inside
				 * priv->lock is safe here, because we
				 * will hold one more reference from
				 * the original value of path->ah (ie
				 * old_ah).
				 */
				ipoib_put_ah(neigh->ah);
			पूर्ण
			kref_get(&path->ah->ref);
			neigh->ah = path->ah;

			अगर (ipoib_cm_enabled(dev, neigh->daddr)) अणु
				अगर (!ipoib_cm_get(neigh))
					ipoib_cm_set(neigh, ipoib_cm_create_tx(dev,
									       path,
									       neigh));
				अगर (!ipoib_cm_get(neigh)) अणु
					ipoib_neigh_मुक्त(neigh);
					जारी;
				पूर्ण
			पूर्ण

			जबतक ((skb = __skb_dequeue(&neigh->queue)))
				__skb_queue_tail(&skqueue, skb);
		पूर्ण
		path->ah->valid = 1;
	पूर्ण

	path->query = शून्य;
	complete(&path->करोne);

	spin_unlock_irqrestore(&priv->lock, flags);

	अगर (IS_ERR_OR_शून्य(ah))
		ipoib_del_neighs_by_gid(dev, path->pathrec.dgid.raw);

	अगर (old_ah)
		ipoib_put_ah(old_ah);

	जबतक ((skb = __skb_dequeue(&skqueue))) अणु
		पूर्णांक ret;
		skb->dev = dev;
		ret = dev_queue_xmit(skb);
		अगर (ret)
			ipoib_warn(priv, "%s: dev_queue_xmit failed to re-queue packet, ret:%d\n",
				   __func__, ret);
	पूर्ण
पूर्ण

अटल व्योम init_path_rec(काष्ठा ipoib_dev_priv *priv, काष्ठा ipoib_path *path,
			  व्योम *gid)
अणु
	path->dev = priv->dev;

	अगर (rdma_cap_opa_ah(priv->ca, priv->port))
		path->pathrec.rec_type = SA_PATH_REC_TYPE_OPA;
	अन्यथा
		path->pathrec.rec_type = SA_PATH_REC_TYPE_IB;

	स_नकल(path->pathrec.dgid.raw, gid, माप(जोड़ ib_gid));
	path->pathrec.sgid	    = priv->local_gid;
	path->pathrec.pkey	    = cpu_to_be16(priv->pkey);
	path->pathrec.numb_path     = 1;
	path->pathrec.traffic_class = priv->broadcast->mcmember.traffic_class;
पूर्ण

अटल काष्ठा ipoib_path *path_rec_create(काष्ठा net_device *dev, व्योम *gid)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ipoib_path *path;

	अगर (!priv->broadcast)
		वापस शून्य;

	path = kzalloc(माप(*path), GFP_ATOMIC);
	अगर (!path)
		वापस शून्य;

	skb_queue_head_init(&path->queue);

	INIT_LIST_HEAD(&path->neigh_list);

	init_path_rec(priv, path, gid);

	वापस path;
पूर्ण

अटल पूर्णांक path_rec_start(काष्ठा net_device *dev,
			  काष्ठा ipoib_path *path)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	ipoib_dbg(priv, "Start path record lookup for %pI6\n",
		  path->pathrec.dgid.raw);

	init_completion(&path->करोne);

	path->query_id =
		ib_sa_path_rec_get(&ipoib_sa_client, priv->ca, priv->port,
				   &path->pathrec,
				   IB_SA_PATH_REC_DGID		|
				   IB_SA_PATH_REC_SGID		|
				   IB_SA_PATH_REC_NUMB_PATH	|
				   IB_SA_PATH_REC_TRAFFIC_CLASS |
				   IB_SA_PATH_REC_PKEY,
				   1000, GFP_ATOMIC,
				   path_rec_completion,
				   path, &path->query);
	अगर (path->query_id < 0) अणु
		ipoib_warn(priv, "ib_sa_path_rec_get failed: %d\n", path->query_id);
		path->query = शून्य;
		complete(&path->करोne);
		वापस path->query_id;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम neigh_refresh_path(काष्ठा ipoib_neigh *neigh, u8 *daddr,
			       काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ipoib_path *path;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);

	path = __path_find(dev, daddr + 4);
	अगर (!path)
		जाओ out;
	अगर (!path->query)
		path_rec_start(dev, path);
out:
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल काष्ठा ipoib_neigh *neigh_add_path(काष्ठा sk_buff *skb, u8 *daddr,
					  काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा rdma_netdev *rn = netdev_priv(dev);
	काष्ठा ipoib_path *path;
	काष्ठा ipoib_neigh *neigh;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	neigh = ipoib_neigh_alloc(daddr, dev);
	अगर (!neigh) अणु
		spin_unlock_irqrestore(&priv->lock, flags);
		++dev->stats.tx_dropped;
		dev_kमुक्त_skb_any(skb);
		वापस शून्य;
	पूर्ण

	/* To aव्योम race condition, make sure that the
	 * neigh will be added only once.
	 */
	अगर (unlikely(!list_empty(&neigh->list))) अणु
		spin_unlock_irqrestore(&priv->lock, flags);
		वापस neigh;
	पूर्ण

	path = __path_find(dev, daddr + 4);
	अगर (!path) अणु
		path = path_rec_create(dev, daddr + 4);
		अगर (!path)
			जाओ err_path;

		__path_add(dev, path);
	पूर्ण

	list_add_tail(&neigh->list, &path->neigh_list);

	अगर (path->ah && path->ah->valid) अणु
		kref_get(&path->ah->ref);
		neigh->ah = path->ah;

		अगर (ipoib_cm_enabled(dev, neigh->daddr)) अणु
			अगर (!ipoib_cm_get(neigh))
				ipoib_cm_set(neigh, ipoib_cm_create_tx(dev, path, neigh));
			अगर (!ipoib_cm_get(neigh)) अणु
				ipoib_neigh_मुक्त(neigh);
				जाओ err_drop;
			पूर्ण
			अगर (skb_queue_len(&neigh->queue) <
			    IPOIB_MAX_PATH_REC_QUEUE) अणु
				push_pseuकरो_header(skb, neigh->daddr);
				__skb_queue_tail(&neigh->queue, skb);
			पूर्ण अन्यथा अणु
				ipoib_warn(priv, "queue length limit %d. Packet drop.\n",
					   skb_queue_len(&neigh->queue));
				जाओ err_drop;
			पूर्ण
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&priv->lock, flags);
			path->ah->last_send = rn->send(dev, skb, path->ah->ah,
						       IPOIB_QPN(daddr));
			ipoib_neigh_put(neigh);
			वापस शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		neigh->ah  = शून्य;

		अगर (!path->query && path_rec_start(dev, path))
			जाओ err_path;
		अगर (skb_queue_len(&neigh->queue) < IPOIB_MAX_PATH_REC_QUEUE) अणु
			push_pseuकरो_header(skb, neigh->daddr);
			__skb_queue_tail(&neigh->queue, skb);
		पूर्ण अन्यथा अणु
			जाओ err_drop;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&priv->lock, flags);
	ipoib_neigh_put(neigh);
	वापस शून्य;

err_path:
	ipoib_neigh_मुक्त(neigh);
err_drop:
	++dev->stats.tx_dropped;
	dev_kमुक्त_skb_any(skb);

	spin_unlock_irqrestore(&priv->lock, flags);
	ipoib_neigh_put(neigh);

	वापस शून्य;
पूर्ण

अटल व्योम unicast_arp_send(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			     काष्ठा ipoib_pseuकरो_header *phdr)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा rdma_netdev *rn = netdev_priv(dev);
	काष्ठा ipoib_path *path;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);

	/* no broadcast means that all paths are (going to be) not valid */
	अगर (!priv->broadcast)
		जाओ drop_and_unlock;

	path = __path_find(dev, phdr->hwaddr + 4);
	अगर (!path || !path->ah || !path->ah->valid) अणु
		अगर (!path) अणु
			path = path_rec_create(dev, phdr->hwaddr + 4);
			अगर (!path)
				जाओ drop_and_unlock;
			__path_add(dev, path);
		पूर्ण अन्यथा अणु
			/*
			 * make sure there are no changes in the existing
			 * path record
			 */
			init_path_rec(priv, path, phdr->hwaddr + 4);
		पूर्ण
		अगर (!path->query && path_rec_start(dev, path)) अणु
			जाओ drop_and_unlock;
		पूर्ण

		अगर (skb_queue_len(&path->queue) < IPOIB_MAX_PATH_REC_QUEUE) अणु
			push_pseuकरो_header(skb, phdr->hwaddr);
			__skb_queue_tail(&path->queue, skb);
			जाओ unlock;
		पूर्ण अन्यथा अणु
			जाओ drop_and_unlock;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&priv->lock, flags);
	ipoib_dbg(priv, "Send unicast ARP to %08x\n",
		  be32_to_cpu(sa_path_get_dlid(&path->pathrec)));
	path->ah->last_send = rn->send(dev, skb, path->ah->ah,
				       IPOIB_QPN(phdr->hwaddr));
	वापस;

drop_and_unlock:
	++dev->stats.tx_dropped;
	dev_kमुक्त_skb_any(skb);
unlock:
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल netdev_tx_t ipoib_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा rdma_netdev *rn = netdev_priv(dev);
	काष्ठा ipoib_neigh *neigh;
	काष्ठा ipoib_pseuकरो_header *phdr;
	काष्ठा ipoib_header *header;
	अचिन्हित दीर्घ flags;

	phdr = (काष्ठा ipoib_pseuकरो_header *) skb->data;
	skb_pull(skb, माप(*phdr));
	header = (काष्ठा ipoib_header *) skb->data;

	अगर (unlikely(phdr->hwaddr[4] == 0xff)) अणु
		/* multicast, arrange "if" according to probability */
		अगर ((header->proto != htons(ETH_P_IP)) &&
		    (header->proto != htons(ETH_P_IPV6)) &&
		    (header->proto != htons(ETH_P_ARP)) &&
		    (header->proto != htons(ETH_P_RARP)) &&
		    (header->proto != htons(ETH_P_TIPC))) अणु
			/* ethertype not supported by IPoIB */
			++dev->stats.tx_dropped;
			dev_kमुक्त_skb_any(skb);
			वापस NETDEV_TX_OK;
		पूर्ण
		/* Add in the P_Key क्रम multicast*/
		phdr->hwaddr[8] = (priv->pkey >> 8) & 0xff;
		phdr->hwaddr[9] = priv->pkey & 0xff;

		neigh = ipoib_neigh_get(dev, phdr->hwaddr);
		अगर (likely(neigh))
			जाओ send_using_neigh;
		ipoib_mcast_send(dev, phdr->hwaddr, skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* unicast, arrange "switch" according to probability */
	चयन (header->proto) अणु
	हाल htons(ETH_P_IP):
	हाल htons(ETH_P_IPV6):
	हाल htons(ETH_P_TIPC):
		neigh = ipoib_neigh_get(dev, phdr->hwaddr);
		अगर (unlikely(!neigh)) अणु
			neigh = neigh_add_path(skb, phdr->hwaddr, dev);
			अगर (likely(!neigh))
				वापस NETDEV_TX_OK;
		पूर्ण
		अवरोध;
	हाल htons(ETH_P_ARP):
	हाल htons(ETH_P_RARP):
		/* क्रम unicast ARP and RARP should always perक्रमm path find */
		unicast_arp_send(skb, dev, phdr);
		वापस NETDEV_TX_OK;
	शेष:
		/* ethertype not supported by IPoIB */
		++dev->stats.tx_dropped;
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

send_using_neigh:
	/* note we now hold a ref to neigh */
	अगर (ipoib_cm_get(neigh)) अणु
		अगर (ipoib_cm_up(neigh)) अणु
			ipoib_cm_send(dev, skb, ipoib_cm_get(neigh));
			जाओ unref;
		पूर्ण
	पूर्ण अन्यथा अगर (neigh->ah && neigh->ah->valid) अणु
		neigh->ah->last_send = rn->send(dev, skb, neigh->ah->ah,
						IPOIB_QPN(phdr->hwaddr));
		जाओ unref;
	पूर्ण अन्यथा अगर (neigh->ah) अणु
		neigh_refresh_path(neigh, phdr->hwaddr, dev);
	पूर्ण

	अगर (skb_queue_len(&neigh->queue) < IPOIB_MAX_PATH_REC_QUEUE) अणु
		push_pseuकरो_header(skb, phdr->hwaddr);
		spin_lock_irqsave(&priv->lock, flags);
		__skb_queue_tail(&neigh->queue, skb);
		spin_unlock_irqrestore(&priv->lock, flags);
	पूर्ण अन्यथा अणु
		++dev->stats.tx_dropped;
		dev_kमुक्त_skb_any(skb);
	पूर्ण

unref:
	ipoib_neigh_put(neigh);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम ipoib_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा rdma_netdev *rn = netdev_priv(dev);

	अगर (rn->tx_समयout) अणु
		rn->tx_समयout(dev, txqueue);
		वापस;
	पूर्ण
	ipoib_warn(priv, "transmit timeout: latency %d msecs\n",
		   jअगरfies_to_msecs(jअगरfies - dev_trans_start(dev)));
	ipoib_warn(priv,
		   "queue stopped %d, tx_head %u, tx_tail %u, global_tx_head %u, global_tx_tail %u\n",
		   netअगर_queue_stopped(dev), priv->tx_head, priv->tx_tail,
		   priv->global_tx_head, priv->global_tx_tail);

	/* XXX reset QP, etc. */
पूर्ण

अटल पूर्णांक ipoib_hard_header(काष्ठा sk_buff *skb,
			     काष्ठा net_device *dev,
			     अचिन्हित लघु type,
			     स्थिर व्योम *daddr,
			     स्थिर व्योम *saddr,
			     अचिन्हित पूर्णांक len)
अणु
	काष्ठा ipoib_header *header;

	header = skb_push(skb, माप(*header));

	header->proto = htons(type);
	header->reserved = 0;

	/*
	 * we करोn't rely on dst_entry काष्ठाure,  always stuff the
	 * destination address पूर्णांकo skb hard header so we can figure out where
	 * to send the packet later.
	 */
	push_pseuकरो_header(skb, daddr);

	वापस IPOIB_HARD_LEN;
पूर्ण

अटल व्योम ipoib_set_mcast_list(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	अगर (!test_bit(IPOIB_FLAG_OPER_UP, &priv->flags)) अणु
		ipoib_dbg(priv, "IPOIB_FLAG_OPER_UP not set");
		वापस;
	पूर्ण

	queue_work(priv->wq, &priv->restart_task);
पूर्ण

अटल पूर्णांक ipoib_get_अगरlink(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	/* parent पूर्णांकerface */
	अगर (!test_bit(IPOIB_FLAG_SUBINTERFACE, &priv->flags))
		वापस dev->अगरindex;

	/* child/vlan पूर्णांकerface */
	वापस priv->parent->अगरindex;
पूर्ण

अटल u32 ipoib_addr_hash(काष्ठा ipoib_neigh_hash *htbl, u8 *daddr)
अणु
	/*
	 * Use only the address parts that contributes to spपढ़ोing
	 * The subnet prefix is not used as one can not connect to
	 * same remote port (GUID) using the same remote QPN via two
	 * dअगरferent subnets.
	 */
	 /* qpn octets[1:4) & port GUID octets[12:20) */
	u32 *d32 = (u32 *) daddr;
	u32 hv;

	hv = jhash_3words(d32[3], d32[4], IPOIB_QPN_MASK & d32[0], 0);
	वापस hv & htbl->mask;
पूर्ण

काष्ठा ipoib_neigh *ipoib_neigh_get(काष्ठा net_device *dev, u8 *daddr)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ipoib_neigh_table *ntbl = &priv->ntbl;
	काष्ठा ipoib_neigh_hash *htbl;
	काष्ठा ipoib_neigh *neigh = शून्य;
	u32 hash_val;

	rcu_पढ़ो_lock_bh();

	htbl = rcu_dereference_bh(ntbl->htbl);

	अगर (!htbl)
		जाओ out_unlock;

	hash_val = ipoib_addr_hash(htbl, daddr);
	क्रम (neigh = rcu_dereference_bh(htbl->buckets[hash_val]);
	     neigh != शून्य;
	     neigh = rcu_dereference_bh(neigh->hnext)) अणु
		अगर (स_भेद(daddr, neigh->daddr, INFINIBAND_ALEN) == 0) अणु
			/* found, take one ref on behalf of the caller */
			अगर (!atomic_inc_not_zero(&neigh->refcnt)) अणु
				/* deleted */
				neigh = शून्य;
				जाओ out_unlock;
			पूर्ण

			अगर (likely(skb_queue_len(&neigh->queue) < IPOIB_MAX_PATH_REC_QUEUE))
				neigh->alive = jअगरfies;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

out_unlock:
	rcu_पढ़ो_unlock_bh();
	वापस neigh;
पूर्ण

अटल व्योम __ipoib_reap_neigh(काष्ठा ipoib_dev_priv *priv)
अणु
	काष्ठा ipoib_neigh_table *ntbl = &priv->ntbl;
	काष्ठा ipoib_neigh_hash *htbl;
	अचिन्हित दीर्घ neigh_obsolete;
	अचिन्हित दीर्घ dt;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	LIST_HEAD(हटाओ_list);

	spin_lock_irqsave(&priv->lock, flags);

	htbl = rcu_dereference_रक्षित(ntbl->htbl,
					 lockdep_is_held(&priv->lock));

	अगर (!htbl)
		जाओ out_unlock;

	/* neigh is obsolete अगर it was idle क्रम two GC periods */
	dt = 2 * arp_tbl.gc_पूर्णांकerval;
	neigh_obsolete = jअगरfies - dt;

	क्रम (i = 0; i < htbl->size; i++) अणु
		काष्ठा ipoib_neigh *neigh;
		काष्ठा ipoib_neigh __rcu **np = &htbl->buckets[i];

		जबतक ((neigh = rcu_dereference_रक्षित(*np,
							  lockdep_is_held(&priv->lock))) != शून्य) अणु
			/* was the neigh idle क्रम two GC periods */
			अगर (समय_after(neigh_obsolete, neigh->alive)) अणु

				ipoib_check_and_add_mcast_senकरोnly(priv, neigh->daddr + 4, &हटाओ_list);

				rcu_assign_poपूर्णांकer(*np,
						   rcu_dereference_रक्षित(neigh->hnext,
									     lockdep_is_held(&priv->lock)));
				/* हटाओ from path/mc list */
				list_del_init(&neigh->list);
				call_rcu(&neigh->rcu, ipoib_neigh_reclaim);
			पूर्ण अन्यथा अणु
				np = &neigh->hnext;
			पूर्ण

		पूर्ण
	पूर्ण

out_unlock:
	spin_unlock_irqrestore(&priv->lock, flags);
	ipoib_mcast_हटाओ_list(&हटाओ_list);
पूर्ण

अटल व्योम ipoib_reap_neigh(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipoib_dev_priv *priv =
		container_of(work, काष्ठा ipoib_dev_priv, neigh_reap_task.work);

	__ipoib_reap_neigh(priv);

	queue_delayed_work(priv->wq, &priv->neigh_reap_task,
			   arp_tbl.gc_पूर्णांकerval);
पूर्ण


अटल काष्ठा ipoib_neigh *ipoib_neigh_ctor(u8 *daddr,
				      काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_neigh *neigh;

	neigh = kzalloc(माप(*neigh), GFP_ATOMIC);
	अगर (!neigh)
		वापस शून्य;

	neigh->dev = dev;
	स_नकल(&neigh->daddr, daddr, माप(neigh->daddr));
	skb_queue_head_init(&neigh->queue);
	INIT_LIST_HEAD(&neigh->list);
	ipoib_cm_set(neigh, शून्य);
	/* one ref on behalf of the caller */
	atomic_set(&neigh->refcnt, 1);

	वापस neigh;
पूर्ण

काष्ठा ipoib_neigh *ipoib_neigh_alloc(u8 *daddr,
				      काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ipoib_neigh_table *ntbl = &priv->ntbl;
	काष्ठा ipoib_neigh_hash *htbl;
	काष्ठा ipoib_neigh *neigh;
	u32 hash_val;

	htbl = rcu_dereference_रक्षित(ntbl->htbl,
					 lockdep_is_held(&priv->lock));
	अगर (!htbl) अणु
		neigh = शून्य;
		जाओ out_unlock;
	पूर्ण

	/* need to add a new neigh, but maybe some other thपढ़ो succeeded?
	 * recalc hash, maybe hash resize took place so we करो a search
	 */
	hash_val = ipoib_addr_hash(htbl, daddr);
	क्रम (neigh = rcu_dereference_रक्षित(htbl->buckets[hash_val],
					       lockdep_is_held(&priv->lock));
	     neigh != शून्य;
	     neigh = rcu_dereference_रक्षित(neigh->hnext,
					       lockdep_is_held(&priv->lock))) अणु
		अगर (स_भेद(daddr, neigh->daddr, INFINIBAND_ALEN) == 0) अणु
			/* found, take one ref on behalf of the caller */
			अगर (!atomic_inc_not_zero(&neigh->refcnt)) अणु
				/* deleted */
				neigh = शून्य;
				अवरोध;
			पूर्ण
			neigh->alive = jअगरfies;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	neigh = ipoib_neigh_ctor(daddr, dev);
	अगर (!neigh)
		जाओ out_unlock;

	/* one ref on behalf of the hash table */
	atomic_inc(&neigh->refcnt);
	neigh->alive = jअगरfies;
	/* put in hash */
	rcu_assign_poपूर्णांकer(neigh->hnext,
			   rcu_dereference_रक्षित(htbl->buckets[hash_val],
						     lockdep_is_held(&priv->lock)));
	rcu_assign_poपूर्णांकer(htbl->buckets[hash_val], neigh);
	atomic_inc(&ntbl->entries);

out_unlock:

	वापस neigh;
पूर्ण

व्योम ipoib_neigh_dtor(काष्ठा ipoib_neigh *neigh)
अणु
	/* neigh reference count was dropprd to zero */
	काष्ठा net_device *dev = neigh->dev;
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा sk_buff *skb;
	अगर (neigh->ah)
		ipoib_put_ah(neigh->ah);
	जबतक ((skb = __skb_dequeue(&neigh->queue))) अणु
		++dev->stats.tx_dropped;
		dev_kमुक्त_skb_any(skb);
	पूर्ण
	अगर (ipoib_cm_get(neigh))
		ipoib_cm_destroy_tx(ipoib_cm_get(neigh));
	ipoib_dbg(ipoib_priv(dev),
		  "neigh free for %06x %pI6\n",
		  IPOIB_QPN(neigh->daddr),
		  neigh->daddr + 4);
	kमुक्त(neigh);
	अगर (atomic_dec_and_test(&priv->ntbl.entries)) अणु
		अगर (test_bit(IPOIB_NEIGH_TBL_FLUSH, &priv->flags))
			complete(&priv->ntbl.flushed);
	पूर्ण
पूर्ण

अटल व्योम ipoib_neigh_reclaim(काष्ठा rcu_head *rp)
अणु
	/* Called as a result of removal from hash table */
	काष्ठा ipoib_neigh *neigh = container_of(rp, काष्ठा ipoib_neigh, rcu);
	/* note TX context may hold another ref */
	ipoib_neigh_put(neigh);
पूर्ण

व्योम ipoib_neigh_मुक्त(काष्ठा ipoib_neigh *neigh)
अणु
	काष्ठा net_device *dev = neigh->dev;
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ipoib_neigh_table *ntbl = &priv->ntbl;
	काष्ठा ipoib_neigh_hash *htbl;
	काष्ठा ipoib_neigh __rcu **np;
	काष्ठा ipoib_neigh *n;
	u32 hash_val;

	htbl = rcu_dereference_रक्षित(ntbl->htbl,
					lockdep_is_held(&priv->lock));
	अगर (!htbl)
		वापस;

	hash_val = ipoib_addr_hash(htbl, neigh->daddr);
	np = &htbl->buckets[hash_val];
	क्रम (n = rcu_dereference_रक्षित(*np,
					    lockdep_is_held(&priv->lock));
	     n != शून्य;
	     n = rcu_dereference_रक्षित(*np,
					lockdep_is_held(&priv->lock))) अणु
		अगर (n == neigh) अणु
			/* found */
			rcu_assign_poपूर्णांकer(*np,
					   rcu_dereference_रक्षित(neigh->hnext,
								     lockdep_is_held(&priv->lock)));
			/* हटाओ from parent list */
			list_del_init(&neigh->list);
			call_rcu(&neigh->rcu, ipoib_neigh_reclaim);
			वापस;
		पूर्ण अन्यथा अणु
			np = &n->hnext;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ipoib_neigh_hash_init(काष्ठा ipoib_dev_priv *priv)
अणु
	काष्ठा ipoib_neigh_table *ntbl = &priv->ntbl;
	काष्ठा ipoib_neigh_hash *htbl;
	काष्ठा ipoib_neigh __rcu **buckets;
	u32 size;

	clear_bit(IPOIB_NEIGH_TBL_FLUSH, &priv->flags);
	ntbl->htbl = शून्य;
	htbl = kzalloc(माप(*htbl), GFP_KERNEL);
	अगर (!htbl)
		वापस -ENOMEM;
	size = roundup_घात_of_two(arp_tbl.gc_thresh3);
	buckets = kvसुस्मृति(size, माप(*buckets), GFP_KERNEL);
	अगर (!buckets) अणु
		kमुक्त(htbl);
		वापस -ENOMEM;
	पूर्ण
	htbl->size = size;
	htbl->mask = (size - 1);
	htbl->buckets = buckets;
	RCU_INIT_POINTER(ntbl->htbl, htbl);
	htbl->ntbl = ntbl;
	atomic_set(&ntbl->entries, 0);

	/* start garbage collection */
	queue_delayed_work(priv->wq, &priv->neigh_reap_task,
			   arp_tbl.gc_पूर्णांकerval);

	वापस 0;
पूर्ण

अटल व्योम neigh_hash_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा ipoib_neigh_hash *htbl = container_of(head,
						    काष्ठा ipoib_neigh_hash,
						    rcu);
	काष्ठा ipoib_neigh __rcu **buckets = htbl->buckets;
	काष्ठा ipoib_neigh_table *ntbl = htbl->ntbl;

	kvमुक्त(buckets);
	kमुक्त(htbl);
	complete(&ntbl->deleted);
पूर्ण

व्योम ipoib_del_neighs_by_gid(काष्ठा net_device *dev, u8 *gid)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ipoib_neigh_table *ntbl = &priv->ntbl;
	काष्ठा ipoib_neigh_hash *htbl;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/* हटाओ all neigh connected to a given path or mcast */
	spin_lock_irqsave(&priv->lock, flags);

	htbl = rcu_dereference_रक्षित(ntbl->htbl,
					 lockdep_is_held(&priv->lock));

	अगर (!htbl)
		जाओ out_unlock;

	क्रम (i = 0; i < htbl->size; i++) अणु
		काष्ठा ipoib_neigh *neigh;
		काष्ठा ipoib_neigh __rcu **np = &htbl->buckets[i];

		जबतक ((neigh = rcu_dereference_रक्षित(*np,
							  lockdep_is_held(&priv->lock))) != शून्य) अणु
			/* delete neighs beदीर्घ to this parent */
			अगर (!स_भेद(gid, neigh->daddr + 4, माप (जोड़ ib_gid))) अणु
				rcu_assign_poपूर्णांकer(*np,
						   rcu_dereference_रक्षित(neigh->hnext,
									     lockdep_is_held(&priv->lock)));
				/* हटाओ from parent list */
				list_del_init(&neigh->list);
				call_rcu(&neigh->rcu, ipoib_neigh_reclaim);
			पूर्ण अन्यथा अणु
				np = &neigh->hnext;
			पूर्ण

		पूर्ण
	पूर्ण
out_unlock:
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल व्योम ipoib_flush_neighs(काष्ठा ipoib_dev_priv *priv)
अणु
	काष्ठा ipoib_neigh_table *ntbl = &priv->ntbl;
	काष्ठा ipoib_neigh_hash *htbl;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, रुको_flushed = 0;

	init_completion(&priv->ntbl.flushed);
	set_bit(IPOIB_NEIGH_TBL_FLUSH, &priv->flags);

	spin_lock_irqsave(&priv->lock, flags);

	htbl = rcu_dereference_रक्षित(ntbl->htbl,
					lockdep_is_held(&priv->lock));
	अगर (!htbl)
		जाओ out_unlock;

	रुको_flushed = atomic_पढ़ो(&priv->ntbl.entries);
	अगर (!रुको_flushed)
		जाओ मुक्त_htbl;

	क्रम (i = 0; i < htbl->size; i++) अणु
		काष्ठा ipoib_neigh *neigh;
		काष्ठा ipoib_neigh __rcu **np = &htbl->buckets[i];

		जबतक ((neigh = rcu_dereference_रक्षित(*np,
				       lockdep_is_held(&priv->lock))) != शून्य) अणु
			rcu_assign_poपूर्णांकer(*np,
					   rcu_dereference_रक्षित(neigh->hnext,
								     lockdep_is_held(&priv->lock)));
			/* हटाओ from path/mc list */
			list_del_init(&neigh->list);
			call_rcu(&neigh->rcu, ipoib_neigh_reclaim);
		पूर्ण
	पूर्ण

मुक्त_htbl:
	rcu_assign_poपूर्णांकer(ntbl->htbl, शून्य);
	call_rcu(&htbl->rcu, neigh_hash_मुक्त_rcu);

out_unlock:
	spin_unlock_irqrestore(&priv->lock, flags);
	अगर (रुको_flushed)
		रुको_क्रम_completion(&priv->ntbl.flushed);
पूर्ण

अटल व्योम ipoib_neigh_hash_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	ipoib_dbg(priv, "%s\n", __func__);
	init_completion(&priv->ntbl.deleted);

	cancel_delayed_work_sync(&priv->neigh_reap_task);

	ipoib_flush_neighs(priv);

	रुको_क्रम_completion(&priv->ntbl.deleted);
पूर्ण

अटल व्योम ipoib_napi_add(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	netअगर_napi_add(dev, &priv->recv_napi, ipoib_rx_poll, IPOIB_NUM_WC);
	netअगर_napi_add(dev, &priv->send_napi, ipoib_tx_poll, MAX_SEND_CQE);
पूर्ण

अटल व्योम ipoib_napi_del(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	netअगर_napi_del(&priv->recv_napi);
	netअगर_napi_del(&priv->send_napi);
पूर्ण

अटल व्योम ipoib_dev_uninit_शेष(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	ipoib_transport_dev_cleanup(dev);

	ipoib_napi_del(dev);

	ipoib_cm_dev_cleanup(dev);

	kमुक्त(priv->rx_ring);
	vमुक्त(priv->tx_ring);

	priv->rx_ring = शून्य;
	priv->tx_ring = शून्य;
पूर्ण

अटल पूर्णांक ipoib_dev_init_शेष(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	ipoib_napi_add(dev);

	/* Allocate RX/TX "rings" to hold queued skbs */
	priv->rx_ring =	kसुस्मृति(ipoib_recvq_size,
				       माप(*priv->rx_ring),
				       GFP_KERNEL);
	अगर (!priv->rx_ring)
		जाओ out;

	priv->tx_ring = vzalloc(array_size(ipoib_sendq_size,
					   माप(*priv->tx_ring)));
	अगर (!priv->tx_ring) अणु
		pr_warn("%s: failed to allocate TX ring (%d entries)\n",
			priv->ca->name, ipoib_sendq_size);
		जाओ out_rx_ring_cleanup;
	पूर्ण

	/* priv->tx_head, tx_tail and global_tx_tail/head are alपढ़ोy 0 */

	अगर (ipoib_transport_dev_init(dev, priv->ca)) अणु
		pr_warn("%s: ipoib_transport_dev_init failed\n",
			priv->ca->name);
		जाओ out_tx_ring_cleanup;
	पूर्ण

	/* after qp created set dev address */
	priv->dev->dev_addr[1] = (priv->qp->qp_num >> 16) & 0xff;
	priv->dev->dev_addr[2] = (priv->qp->qp_num >>  8) & 0xff;
	priv->dev->dev_addr[3] = (priv->qp->qp_num) & 0xff;

	वापस 0;

out_tx_ring_cleanup:
	vमुक्त(priv->tx_ring);

out_rx_ring_cleanup:
	kमुक्त(priv->rx_ring);

out:
	ipoib_napi_del(dev);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक ipoib_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr,
		       पूर्णांक cmd)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	अगर (!priv->rn_ops->nकरो_करो_ioctl)
		वापस -EOPNOTSUPP;

	वापस priv->rn_ops->nकरो_करो_ioctl(dev, अगरr, cmd);
पूर्ण

अटल पूर्णांक ipoib_dev_init(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	पूर्णांक ret = -ENOMEM;

	priv->qp = शून्य;

	/*
	 * the various IPoIB tasks assume they will never race against
	 * themselves, so always use a single thपढ़ो workqueue
	 */
	priv->wq = alloc_ordered_workqueue("ipoib_wq", WQ_MEM_RECLAIM);
	अगर (!priv->wq) अणु
		pr_warn("%s: failed to allocate device WQ\n", dev->name);
		जाओ out;
	पूर्ण

	/* create pd, which used both क्रम control and datapath*/
	priv->pd = ib_alloc_pd(priv->ca, 0);
	अगर (IS_ERR(priv->pd)) अणु
		pr_warn("%s: failed to allocate PD\n", priv->ca->name);
		जाओ clean_wq;
	पूर्ण

	ret = priv->rn_ops->nकरो_init(dev);
	अगर (ret) अणु
		pr_warn("%s failed to init HW resource\n", dev->name);
		जाओ out_मुक्त_pd;
	पूर्ण

	ret = ipoib_neigh_hash_init(priv);
	अगर (ret) अणु
		pr_warn("%s failed to init neigh hash\n", dev->name);
		जाओ out_dev_uninit;
	पूर्ण

	अगर (dev->flags & IFF_UP) अणु
		अगर (ipoib_ib_dev_खोलो(dev)) अणु
			pr_warn("%s failed to open device\n", dev->name);
			ret = -ENODEV;
			जाओ out_hash_uninit;
		पूर्ण
	पूर्ण

	वापस 0;

out_hash_uninit:
	ipoib_neigh_hash_uninit(dev);

out_dev_uninit:
	ipoib_ib_dev_cleanup(dev);

out_मुक्त_pd:
	अगर (priv->pd) अणु
		ib_dealloc_pd(priv->pd);
		priv->pd = शून्य;
	पूर्ण

clean_wq:
	अगर (priv->wq) अणु
		destroy_workqueue(priv->wq);
		priv->wq = शून्य;
	पूर्ण

out:
	वापस ret;
पूर्ण

/*
 * This must be called beक्रमe करोing an unरेजिस्टर_netdev on a parent device to
 * shutकरोwn the IB event handler.
 */
अटल व्योम ipoib_parent_unरेजिस्टर_pre(काष्ठा net_device *ndev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(ndev);

	/*
	 * ipoib_set_mac checks netअगर_running beक्रमe pushing work, clearing
	 * running ensures the it will not add more work.
	 */
	rtnl_lock();
	dev_change_flags(priv->dev, priv->dev->flags & ~IFF_UP, शून्य);
	rtnl_unlock();

	/* ipoib_event() cannot be running once this वापसs */
	ib_unरेजिस्टर_event_handler(&priv->event_handler);

	/*
	 * Work on the queue grअसल the rtnl lock, so this cannot be करोne जबतक
	 * also holding it.
	 */
	flush_workqueue(ipoib_workqueue);
पूर्ण

अटल व्योम ipoib_set_dev_features(काष्ठा ipoib_dev_priv *priv)
अणु
	priv->hca_caps = priv->ca->attrs.device_cap_flags;

	अगर (priv->hca_caps & IB_DEVICE_UD_IP_CSUM) अणु
		priv->dev->hw_features |= NETIF_F_IP_CSUM | NETIF_F_RXCSUM;

		अगर (priv->hca_caps & IB_DEVICE_UD_TSO)
			priv->dev->hw_features |= NETIF_F_TSO;

		priv->dev->features |= priv->dev->hw_features;
	पूर्ण
पूर्ण

अटल पूर्णांक ipoib_parent_init(काष्ठा net_device *ndev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(ndev);
	काष्ठा ib_port_attr attr;
	पूर्णांक result;

	result = ib_query_port(priv->ca, priv->port, &attr);
	अगर (result) अणु
		pr_warn("%s: ib_query_port %d failed\n", priv->ca->name,
			priv->port);
		वापस result;
	पूर्ण
	priv->max_ib_mtu = rdma_mtu_from_attr(priv->ca, priv->port, &attr);

	result = ib_query_pkey(priv->ca, priv->port, 0, &priv->pkey);
	अगर (result) अणु
		pr_warn("%s: ib_query_pkey port %d failed (ret = %d)\n",
			priv->ca->name, priv->port, result);
		वापस result;
	पूर्ण

	result = rdma_query_gid(priv->ca, priv->port, 0, &priv->local_gid);
	अगर (result) अणु
		pr_warn("%s: rdma_query_gid port %d failed (ret = %d)\n",
			priv->ca->name, priv->port, result);
		वापस result;
	पूर्ण
	स_नकल(priv->dev->dev_addr + 4, priv->local_gid.raw,
	       माप(जोड़ ib_gid));

	SET_NETDEV_DEV(priv->dev, priv->ca->dev.parent);
	priv->dev->dev_port = priv->port - 1;
	/* Let's set this one too क्रम backwards compatibility. */
	priv->dev->dev_id = priv->port - 1;

	वापस 0;
पूर्ण

अटल व्योम ipoib_child_init(काष्ठा net_device *ndev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(ndev);
	काष्ठा ipoib_dev_priv *ppriv = ipoib_priv(priv->parent);

	priv->max_ib_mtu = ppriv->max_ib_mtu;
	set_bit(IPOIB_FLAG_SUBINTERFACE, &priv->flags);
	अगर (स_प्रथम_inv(priv->dev->dev_addr, 0, INFINIBAND_ALEN))
		स_नकल(&priv->local_gid, priv->dev->dev_addr + 4,
		       माप(priv->local_gid));
	अन्यथा अणु
		स_नकल(priv->dev->dev_addr, ppriv->dev->dev_addr,
		       INFINIBAND_ALEN);
		स_नकल(&priv->local_gid, &ppriv->local_gid,
		       माप(priv->local_gid));
	पूर्ण
पूर्ण

अटल पूर्णांक ipoib_nकरो_init(काष्ठा net_device *ndev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(ndev);
	पूर्णांक rc;
	काष्ठा rdma_netdev *rn = netdev_priv(ndev);

	अगर (priv->parent) अणु
		ipoib_child_init(ndev);
	पूर्ण अन्यथा अणु
		rc = ipoib_parent_init(ndev);
		अगर (rc)
			वापस rc;
	पूर्ण

	/* MTU will be reset when mcast join happens */
	ndev->mtu = IPOIB_UD_MTU(priv->max_ib_mtu);
	priv->mcast_mtu = priv->admin_mtu = ndev->mtu;
	rn->mtu = priv->mcast_mtu;
	ndev->max_mtu = IPOIB_CM_MTU;

	ndev->neigh_priv_len = माप(काष्ठा ipoib_neigh);

	/*
	 * Set the full membership bit, so that we join the right
	 * broadcast group, etc.
	 */
	priv->pkey |= 0x8000;

	ndev->broadcast[8] = priv->pkey >> 8;
	ndev->broadcast[9] = priv->pkey & 0xff;
	set_bit(IPOIB_FLAG_DEV_ADDR_SET, &priv->flags);

	ipoib_set_dev_features(priv);

	rc = ipoib_dev_init(ndev);
	अगर (rc) अणु
		pr_warn("%s: failed to initialize device: %s port %d (ret = %d)\n",
			priv->ca->name, priv->dev->name, priv->port, rc);
		वापस rc;
	पूर्ण

	अगर (priv->parent) अणु
		काष्ठा ipoib_dev_priv *ppriv = ipoib_priv(priv->parent);

		dev_hold(priv->parent);

		करोwn_ग_लिखो(&ppriv->vlan_rwsem);
		list_add_tail(&priv->list, &ppriv->child_पूर्णांकfs);
		up_ग_लिखो(&ppriv->vlan_rwsem);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ipoib_nकरो_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	ASSERT_RTNL();

	/*
	 * ipoib_हटाओ_one guarantees the children are हटाओd beक्रमe the
	 * parent, and that is the only place where a parent can be हटाओd.
	 */
	WARN_ON(!list_empty(&priv->child_पूर्णांकfs));

	अगर (priv->parent) अणु
		काष्ठा ipoib_dev_priv *ppriv = ipoib_priv(priv->parent);

		करोwn_ग_लिखो(&ppriv->vlan_rwsem);
		list_del(&priv->list);
		up_ग_लिखो(&ppriv->vlan_rwsem);
	पूर्ण

	ipoib_neigh_hash_uninit(dev);

	ipoib_ib_dev_cleanup(dev);

	/* no more works over the priv->wq */
	अगर (priv->wq) अणु
		/* See ipoib_mcast_carrier_on_task() */
		WARN_ON(test_bit(IPOIB_FLAG_OPER_UP, &priv->flags));
		flush_workqueue(priv->wq);
		destroy_workqueue(priv->wq);
		priv->wq = शून्य;
	पूर्ण

	अगर (priv->parent)
		dev_put(priv->parent);
पूर्ण

अटल पूर्णांक ipoib_set_vf_link_state(काष्ठा net_device *dev, पूर्णांक vf, पूर्णांक link_state)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	वापस ib_set_vf_link_state(priv->ca, vf, priv->port, link_state);
पूर्ण

अटल पूर्णांक ipoib_get_vf_config(काष्ठा net_device *dev, पूर्णांक vf,
			       काष्ठा अगरla_vf_info *ivf)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	पूर्णांक err;

	err = ib_get_vf_config(priv->ca, vf, priv->port, ivf);
	अगर (err)
		वापस err;

	ivf->vf = vf;
	स_नकल(ivf->mac, dev->dev_addr, dev->addr_len);

	वापस 0;
पूर्ण

अटल पूर्णांक ipoib_set_vf_guid(काष्ठा net_device *dev, पूर्णांक vf, u64 guid, पूर्णांक type)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	अगर (type != IFLA_VF_IB_NODE_GUID && type != IFLA_VF_IB_PORT_GUID)
		वापस -EINVAL;

	वापस ib_set_vf_guid(priv->ca, vf, priv->port, guid, type);
पूर्ण

अटल पूर्णांक ipoib_get_vf_guid(काष्ठा net_device *dev, पूर्णांक vf,
			     काष्ठा अगरla_vf_guid *node_guid,
			     काष्ठा अगरla_vf_guid *port_guid)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	वापस ib_get_vf_guid(priv->ca, vf, priv->port, node_guid, port_guid);
पूर्ण

अटल पूर्णांक ipoib_get_vf_stats(काष्ठा net_device *dev, पूर्णांक vf,
			      काष्ठा अगरla_vf_stats *vf_stats)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	वापस ib_get_vf_stats(priv->ca, vf, priv->port, vf_stats);
पूर्ण

अटल स्थिर काष्ठा header_ops ipoib_header_ops = अणु
	.create	= ipoib_hard_header,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops ipoib_netdev_ops_pf = अणु
	.nकरो_init		 = ipoib_nकरो_init,
	.nकरो_uninit		 = ipoib_nकरो_uninit,
	.nकरो_खोलो		 = ipoib_खोलो,
	.nकरो_stop		 = ipoib_stop,
	.nकरो_change_mtu		 = ipoib_change_mtu,
	.nकरो_fix_features	 = ipoib_fix_features,
	.nकरो_start_xmit		 = ipoib_start_xmit,
	.nकरो_tx_समयout		 = ipoib_समयout,
	.nकरो_set_rx_mode	 = ipoib_set_mcast_list,
	.nकरो_get_अगरlink		 = ipoib_get_अगरlink,
	.nकरो_set_vf_link_state	 = ipoib_set_vf_link_state,
	.nकरो_get_vf_config	 = ipoib_get_vf_config,
	.nकरो_get_vf_stats	 = ipoib_get_vf_stats,
	.nकरो_get_vf_guid	 = ipoib_get_vf_guid,
	.nकरो_set_vf_guid	 = ipoib_set_vf_guid,
	.nकरो_set_mac_address	 = ipoib_set_mac,
	.nकरो_get_stats64	 = ipoib_get_stats,
	.nकरो_करो_ioctl		 = ipoib_ioctl,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops ipoib_netdev_ops_vf = अणु
	.nकरो_init		 = ipoib_nकरो_init,
	.nकरो_uninit		 = ipoib_nकरो_uninit,
	.nकरो_खोलो		 = ipoib_खोलो,
	.nकरो_stop		 = ipoib_stop,
	.nकरो_change_mtu		 = ipoib_change_mtu,
	.nकरो_fix_features	 = ipoib_fix_features,
	.nकरो_start_xmit	 	 = ipoib_start_xmit,
	.nकरो_tx_समयout		 = ipoib_समयout,
	.nकरो_set_rx_mode	 = ipoib_set_mcast_list,
	.nकरो_get_अगरlink		 = ipoib_get_अगरlink,
	.nकरो_get_stats64	 = ipoib_get_stats,
	.nकरो_करो_ioctl		 = ipoib_ioctl,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops ipoib_netdev_शेष_pf = अणु
	.nकरो_init		 = ipoib_dev_init_शेष,
	.nकरो_uninit		 = ipoib_dev_uninit_शेष,
	.nकरो_खोलो		 = ipoib_ib_dev_खोलो_शेष,
	.nकरो_stop		 = ipoib_ib_dev_stop_शेष,
पूर्ण;

व्योम ipoib_setup_common(काष्ठा net_device *dev)
अणु
	dev->header_ops		 = &ipoib_header_ops;
	dev->netdev_ops          = &ipoib_netdev_शेष_pf;

	ipoib_set_ethtool_ops(dev);

	dev->watchकरोg_समयo	 = HZ;

	dev->flags		|= IFF_BROADCAST | IFF_MULTICAST;

	dev->hard_header_len	 = IPOIB_HARD_LEN;
	dev->addr_len		 = INFINIBAND_ALEN;
	dev->type		 = ARPHRD_INFINIBAND;
	dev->tx_queue_len	 = ipoib_sendq_size * 2;
	dev->features		 = (NETIF_F_VLAN_CHALLENGED	|
				    NETIF_F_HIGHDMA);
	netअगर_keep_dst(dev);

	स_नकल(dev->broadcast, ipv4_bcast_addr, INFINIBAND_ALEN);

	/*
	 * unरेजिस्टर_netdev always मुक्तs the netdev, we use this mode
	 * consistently to unअगरy all the various unरेजिस्टर paths, including
	 * those connected to rtnl_link_ops which require it.
	 */
	dev->needs_मुक्त_netdev = true;
पूर्ण

अटल व्योम ipoib_build_priv(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	priv->dev = dev;
	spin_lock_init(&priv->lock);
	init_rwsem(&priv->vlan_rwsem);
	mutex_init(&priv->mcast_mutex);

	INIT_LIST_HEAD(&priv->path_list);
	INIT_LIST_HEAD(&priv->child_पूर्णांकfs);
	INIT_LIST_HEAD(&priv->dead_ahs);
	INIT_LIST_HEAD(&priv->multicast_list);

	INIT_DELAYED_WORK(&priv->mcast_task,   ipoib_mcast_join_task);
	INIT_WORK(&priv->carrier_on_task, ipoib_mcast_carrier_on_task);
	INIT_WORK(&priv->flush_light,   ipoib_ib_dev_flush_light);
	INIT_WORK(&priv->flush_normal,   ipoib_ib_dev_flush_normal);
	INIT_WORK(&priv->flush_heavy,   ipoib_ib_dev_flush_heavy);
	INIT_WORK(&priv->restart_task, ipoib_mcast_restart_task);
	INIT_DELAYED_WORK(&priv->ah_reap_task, ipoib_reap_ah);
	INIT_DELAYED_WORK(&priv->neigh_reap_task, ipoib_reap_neigh);
पूर्ण

अटल काष्ठा net_device *ipoib_alloc_netdev(काष्ठा ib_device *hca, u32 port,
					     स्थिर अक्षर *name)
अणु
	काष्ठा net_device *dev;

	dev = rdma_alloc_netdev(hca, port, RDMA_NETDEV_IPOIB, name,
				NET_NAME_UNKNOWN, ipoib_setup_common);
	अगर (!IS_ERR(dev) || PTR_ERR(dev) != -EOPNOTSUPP)
		वापस dev;

	dev = alloc_netdev(माप(काष्ठा rdma_netdev), name, NET_NAME_UNKNOWN,
			   ipoib_setup_common);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);
	वापस dev;
पूर्ण

पूर्णांक ipoib_पूर्णांकf_init(काष्ठा ib_device *hca, u32 port, स्थिर अक्षर *name,
		    काष्ठा net_device *dev)
अणु
	काष्ठा rdma_netdev *rn = netdev_priv(dev);
	काष्ठा ipoib_dev_priv *priv;
	पूर्णांक rc;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->ca = hca;
	priv->port = port;

	rc = rdma_init_netdev(hca, port, RDMA_NETDEV_IPOIB, name,
			      NET_NAME_UNKNOWN, ipoib_setup_common, dev);
	अगर (rc) अणु
		अगर (rc != -EOPNOTSUPP)
			जाओ out;

		rn->send = ipoib_send;
		rn->attach_mcast = ipoib_mcast_attach;
		rn->detach_mcast = ipoib_mcast_detach;
		rn->hca = hca;
	पूर्ण

	priv->rn_ops = dev->netdev_ops;

	अगर (hca->attrs.device_cap_flags & IB_DEVICE_VIRTUAL_FUNCTION)
		dev->netdev_ops	= &ipoib_netdev_ops_vf;
	अन्यथा
		dev->netdev_ops	= &ipoib_netdev_ops_pf;

	rn->clnt_priv = priv;
	/*
	 * Only the child रेजिस्टर_netdev flows can handle priv_deकाष्ठाor
	 * being set, so we क्रमce it to शून्य here and handle manually until it
	 * is safe to turn on.
	 */
	priv->next_priv_deकाष्ठाor = dev->priv_deकाष्ठाor;
	dev->priv_deकाष्ठाor = शून्य;

	ipoib_build_priv(dev);

	वापस 0;

out:
	kमुक्त(priv);
	वापस rc;
पूर्ण

काष्ठा net_device *ipoib_पूर्णांकf_alloc(काष्ठा ib_device *hca, u32 port,
				    स्थिर अक्षर *name)
अणु
	काष्ठा net_device *dev;
	पूर्णांक rc;

	dev = ipoib_alloc_netdev(hca, port, name);
	अगर (IS_ERR(dev))
		वापस dev;

	rc = ipoib_पूर्णांकf_init(hca, port, name, dev);
	अगर (rc) अणु
		मुक्त_netdev(dev);
		वापस ERR_PTR(rc);
	पूर्ण

	/*
	 * Upon success the caller must ensure ipoib_पूर्णांकf_मुक्त is called or
	 * रेजिस्टर_netdevice succeed'd and priv_deकाष्ठाor is set to
	 * ipoib_पूर्णांकf_मुक्त.
	 */
	वापस dev;
पूर्ण

व्योम ipoib_पूर्णांकf_मुक्त(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा rdma_netdev *rn = netdev_priv(dev);

	dev->priv_deकाष्ठाor = priv->next_priv_deकाष्ठाor;
	अगर (dev->priv_deकाष्ठाor)
		dev->priv_deकाष्ठाor(dev);

	/*
	 * There are some error flows around रेजिस्टर_netdev failing that may
	 * attempt to call priv_deकाष्ठाor twice, prevent that from happening.
	 */
	dev->priv_deकाष्ठाor = शून्य;

	/* unरेजिस्टर/destroy is very complicated. Make bugs more obvious. */
	rn->clnt_priv = शून्य;

	kमुक्त(priv);
पूर्ण

अटल sमाप_प्रकार show_pkey(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_device *ndev = to_net_dev(dev);
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(ndev);

	वापस sysfs_emit(buf, "0x%04x\n", priv->pkey);
पूर्ण
अटल DEVICE_ATTR(pkey, S_IRUGO, show_pkey, शून्य);

अटल sमाप_प्रकार show_umcast(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_device *ndev = to_net_dev(dev);
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(ndev);

	वापस sysfs_emit(buf, "%d\n",
			  test_bit(IPOIB_FLAG_UMCAST, &priv->flags));
पूर्ण

व्योम ipoib_set_umcast(काष्ठा net_device *ndev, पूर्णांक umcast_val)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(ndev);

	अगर (umcast_val > 0) अणु
		set_bit(IPOIB_FLAG_UMCAST, &priv->flags);
		ipoib_warn(priv, "ignoring multicast groups joined directly "
				"by userspace\n");
	पूर्ण अन्यथा
		clear_bit(IPOIB_FLAG_UMCAST, &priv->flags);
पूर्ण

अटल sमाप_प्रकार set_umcast(काष्ठा device *dev,
			  काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ umcast_val = simple_म_से_अदीर्घ(buf, शून्य, 0);

	ipoib_set_umcast(to_net_dev(dev), umcast_val);

	वापस count;
पूर्ण
अटल DEVICE_ATTR(umcast, S_IWUSR | S_IRUGO, show_umcast, set_umcast);

पूर्णांक ipoib_add_umcast_attr(काष्ठा net_device *dev)
अणु
	वापस device_create_file(&dev->dev, &dev_attr_umcast);
पूर्ण

अटल व्योम set_base_guid(काष्ठा ipoib_dev_priv *priv, जोड़ ib_gid *gid)
अणु
	काष्ठा ipoib_dev_priv *child_priv;
	काष्ठा net_device *netdev = priv->dev;

	netअगर_addr_lock_bh(netdev);

	स_नकल(&priv->local_gid.global.पूर्णांकerface_id,
	       &gid->global.पूर्णांकerface_id,
	       माप(gid->global.पूर्णांकerface_id));
	स_नकल(netdev->dev_addr + 4, &priv->local_gid, माप(priv->local_gid));
	clear_bit(IPOIB_FLAG_DEV_ADDR_SET, &priv->flags);

	netअगर_addr_unlock_bh(netdev);

	अगर (!test_bit(IPOIB_FLAG_SUBINTERFACE, &priv->flags)) अणु
		करोwn_पढ़ो(&priv->vlan_rwsem);
		list_क्रम_each_entry(child_priv, &priv->child_पूर्णांकfs, list)
			set_base_guid(child_priv, gid);
		up_पढ़ो(&priv->vlan_rwsem);
	पूर्ण
पूर्ण

अटल पूर्णांक ipoib_check_lladdr(काष्ठा net_device *dev,
			      काष्ठा sockaddr_storage *ss)
अणु
	जोड़ ib_gid *gid = (जोड़ ib_gid *)(ss->__data + 4);
	पूर्णांक ret = 0;

	netअगर_addr_lock_bh(dev);

	/* Make sure the QPN, reserved and subnet prefix match the current
	 * lladdr, it also makes sure the lladdr is unicast.
	 */
	अगर (स_भेद(dev->dev_addr, ss->__data,
		   4 + माप(gid->global.subnet_prefix)) ||
	    gid->global.पूर्णांकerface_id == 0)
		ret = -EINVAL;

	netअगर_addr_unlock_bh(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक ipoib_set_mac(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा sockaddr_storage *ss = addr;
	पूर्णांक ret;

	अगर (!(dev->priv_flags & IFF_LIVE_ADDR_CHANGE) && netअगर_running(dev))
		वापस -EBUSY;

	ret = ipoib_check_lladdr(dev, ss);
	अगर (ret)
		वापस ret;

	set_base_guid(priv, (जोड़ ib_gid *)(ss->__data + 4));

	queue_work(ipoib_workqueue, &priv->flush_light);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार create_child(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक pkey;
	पूर्णांक ret;

	अगर (माला_पूछो(buf, "%i", &pkey) != 1)
		वापस -EINVAL;

	अगर (pkey <= 0 || pkey > 0xffff || pkey == 0x8000)
		वापस -EINVAL;

	ret = ipoib_vlan_add(to_net_dev(dev), pkey);

	वापस ret ? ret : count;
पूर्ण
अटल DEVICE_ATTR(create_child, S_IWUSR, शून्य, create_child);

अटल sमाप_प्रकार delete_child(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक pkey;
	पूर्णांक ret;

	अगर (माला_पूछो(buf, "%i", &pkey) != 1)
		वापस -EINVAL;

	अगर (pkey < 0 || pkey > 0xffff)
		वापस -EINVAL;

	ret = ipoib_vlan_delete(to_net_dev(dev), pkey);

	वापस ret ? ret : count;

पूर्ण
अटल DEVICE_ATTR(delete_child, S_IWUSR, शून्य, delete_child);

पूर्णांक ipoib_add_pkey_attr(काष्ठा net_device *dev)
अणु
	वापस device_create_file(&dev->dev, &dev_attr_pkey);
पूर्ण

/*
 * We erroneously exposed the अगरace's port number in the dev_id
 * sysfs field दीर्घ after dev_port was पूर्णांकroduced क्रम that purpose[1],
 * and we need to stop everyone from relying on that.
 * Let's overload the shower routine क्रम the dev_id file here
 * to gently bring the issue up.
 *
 * [1] https://www.spinics.net/lists/netdev/msg272123.hपंचांगl
 */
अटल sमाप_प्रकार dev_id_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_device *ndev = to_net_dev(dev);

	/*
	 * ndev->dev_port will be equal to 0 in old kernel prior to commit
	 * 9b8b2a323008 ("IB/ipoib: Use dev_port to expose network पूर्णांकerface
	 * port numbers") Zero was chosen as special हाल क्रम user space
	 * applications to fallback and query dev_id to check अगर it has
	 * dअगरferent value or not.
	 *
	 * Don't prपूर्णांक warning in such scenario.
	 *
	 * https://github.com/प्रणालीd/प्रणालीd/blob/master/src/udev/udev-builtin-net_id.c#L358
	 */
	अगर (ndev->dev_port && ndev->dev_id == ndev->dev_port)
		netdev_info_once(ndev,
			"\"%s\" wants to know my dev_id. Should it look at dev_port instead? See Documentation/ABI/testing/sysfs-class-net for more info.\n",
			current->comm);

	वापस sysfs_emit(buf, "%#x\n", ndev->dev_id);
पूर्ण
अटल DEVICE_ATTR_RO(dev_id);

अटल पूर्णांक ipoib_पूर्णांकercept_dev_id_attr(काष्ठा net_device *dev)
अणु
	device_हटाओ_file(&dev->dev, &dev_attr_dev_id);
	वापस device_create_file(&dev->dev, &dev_attr_dev_id);
पूर्ण

अटल काष्ठा net_device *ipoib_add_port(स्थिर अक्षर *क्रमmat,
					 काष्ठा ib_device *hca, u32 port)
अणु
	काष्ठा rtnl_link_ops *ops = ipoib_get_link_ops();
	काष्ठा rdma_netdev_alloc_params params;
	काष्ठा ipoib_dev_priv *priv;
	काष्ठा net_device *ndev;
	पूर्णांक result;

	ndev = ipoib_पूर्णांकf_alloc(hca, port, क्रमmat);
	अगर (IS_ERR(ndev)) अणु
		pr_warn("%s, %d: ipoib_intf_alloc failed %ld\n", hca->name, port,
			PTR_ERR(ndev));
		वापस ndev;
	पूर्ण
	priv = ipoib_priv(ndev);

	INIT_IB_EVENT_HANDLER(&priv->event_handler,
			      priv->ca, ipoib_event);
	ib_रेजिस्टर_event_handler(&priv->event_handler);

	/* call event handler to ensure pkey in sync */
	queue_work(ipoib_workqueue, &priv->flush_heavy);

	ndev->rtnl_link_ops = ipoib_get_link_ops();

	result = रेजिस्टर_netdev(ndev);
	अगर (result) अणु
		pr_warn("%s: couldn't register ipoib port %d; error %d\n",
			hca->name, port, result);

		ipoib_parent_unरेजिस्टर_pre(ndev);
		ipoib_पूर्णांकf_मुक्त(ndev);
		मुक्त_netdev(ndev);

		वापस ERR_PTR(result);
	पूर्ण

	अगर (hca->ops.rdma_netdev_get_params) अणु
		पूर्णांक rc = hca->ops.rdma_netdev_get_params(hca, port,
						     RDMA_NETDEV_IPOIB,
						     &params);

		अगर (!rc && ops->priv_size < params.माप_priv)
			ops->priv_size = params.माप_priv;
	पूर्ण
	/*
	 * We cannot set priv_deकाष्ठाor beक्रमe रेजिस्टर_netdev because we
	 * need priv to be always valid during the error flow to execute
	 * ipoib_parent_unरेजिस्टर_pre(). Instead handle it manually and only
	 * enter priv_deकाष्ठाor mode once we are completely रेजिस्टरed.
	 */
	ndev->priv_deकाष्ठाor = ipoib_पूर्णांकf_मुक्त;

	अगर (ipoib_पूर्णांकercept_dev_id_attr(ndev))
		जाओ sysfs_failed;
	अगर (ipoib_cm_add_mode_attr(ndev))
		जाओ sysfs_failed;
	अगर (ipoib_add_pkey_attr(ndev))
		जाओ sysfs_failed;
	अगर (ipoib_add_umcast_attr(ndev))
		जाओ sysfs_failed;
	अगर (device_create_file(&ndev->dev, &dev_attr_create_child))
		जाओ sysfs_failed;
	अगर (device_create_file(&ndev->dev, &dev_attr_delete_child))
		जाओ sysfs_failed;

	वापस ndev;

sysfs_failed:
	ipoib_parent_unरेजिस्टर_pre(ndev);
	unरेजिस्टर_netdev(ndev);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल पूर्णांक ipoib_add_one(काष्ठा ib_device *device)
अणु
	काष्ठा list_head *dev_list;
	काष्ठा net_device *dev;
	काष्ठा ipoib_dev_priv *priv;
	अचिन्हित पूर्णांक p;
	पूर्णांक count = 0;

	dev_list = kदो_स्मृति(माप(*dev_list), GFP_KERNEL);
	अगर (!dev_list)
		वापस -ENOMEM;

	INIT_LIST_HEAD(dev_list);

	rdma_क्रम_each_port (device, p) अणु
		अगर (!rdma_protocol_ib(device, p))
			जारी;
		dev = ipoib_add_port("ib%d", device, p);
		अगर (!IS_ERR(dev)) अणु
			priv = ipoib_priv(dev);
			list_add_tail(&priv->list, dev_list);
			count++;
		पूर्ण
	पूर्ण

	अगर (!count) अणु
		kमुक्त(dev_list);
		वापस -EOPNOTSUPP;
	पूर्ण

	ib_set_client_data(device, &ipoib_client, dev_list);
	वापस 0;
पूर्ण

अटल व्योम ipoib_हटाओ_one(काष्ठा ib_device *device, व्योम *client_data)
अणु
	काष्ठा ipoib_dev_priv *priv, *पंचांगp, *cpriv, *tcpriv;
	काष्ठा list_head *dev_list = client_data;

	list_क्रम_each_entry_safe(priv, पंचांगp, dev_list, list) अणु
		LIST_HEAD(head);
		ipoib_parent_unरेजिस्टर_pre(priv->dev);

		rtnl_lock();

		list_क्रम_each_entry_safe(cpriv, tcpriv, &priv->child_पूर्णांकfs,
					 list)
			unरेजिस्टर_netdevice_queue(cpriv->dev, &head);
		unरेजिस्टर_netdevice_queue(priv->dev, &head);
		unरेजिस्टर_netdevice_many(&head);

		rtnl_unlock();
	पूर्ण

	kमुक्त(dev_list);
पूर्ण

#अगर_घोषित CONFIG_INFINIBAND_IPOIB_DEBUG
अटल काष्ठा notअगरier_block ipoib_netdev_notअगरier = अणु
	.notअगरier_call = ipoib_netdev_event,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init ipoib_init_module(व्योम)
अणु
	पूर्णांक ret;

	ipoib_recvq_size = roundup_घात_of_two(ipoib_recvq_size);
	ipoib_recvq_size = min(ipoib_recvq_size, IPOIB_MAX_QUEUE_SIZE);
	ipoib_recvq_size = max(ipoib_recvq_size, IPOIB_MIN_QUEUE_SIZE);

	ipoib_sendq_size = roundup_घात_of_two(ipoib_sendq_size);
	ipoib_sendq_size = min(ipoib_sendq_size, IPOIB_MAX_QUEUE_SIZE);
	ipoib_sendq_size = max3(ipoib_sendq_size, 2 * MAX_SEND_CQE, IPOIB_MIN_QUEUE_SIZE);
#अगर_घोषित CONFIG_INFINIBAND_IPOIB_CM
	ipoib_max_conn_qp = min(ipoib_max_conn_qp, IPOIB_CM_MAX_CONN_QP);
	ipoib_max_conn_qp = max(ipoib_max_conn_qp, 0);
#पूर्ण_अगर

	/*
	 * When copying small received packets, we only copy from the
	 * linear data part of the SKB, so we rely on this condition.
	 */
	BUILD_BUG_ON(IPOIB_CM_COPYBREAK > IPOIB_CM_HEAD_SIZE);

	ipoib_रेजिस्टर_debugfs();

	/*
	 * We create a global workqueue here that is used क्रम all flush
	 * operations.  However, अगर you attempt to flush a workqueue
	 * from a task on that same workqueue, it deadlocks the प्रणाली.
	 * We want to be able to flush the tasks associated with a
	 * specअगरic net device, so we also create a workqueue क्रम each
	 * netdevice.  We queue up the tasks क्रम that device only on
	 * its निजी workqueue, and we only queue up flush events
	 * on our global flush workqueue.  This aव्योमs the deadlocks.
	 */
	ipoib_workqueue = alloc_ordered_workqueue("ipoib_flush", 0);
	अगर (!ipoib_workqueue) अणु
		ret = -ENOMEM;
		जाओ err_fs;
	पूर्ण

	ib_sa_रेजिस्टर_client(&ipoib_sa_client);

	ret = ib_रेजिस्टर_client(&ipoib_client);
	अगर (ret)
		जाओ err_sa;

	ret = ipoib_netlink_init();
	अगर (ret)
		जाओ err_client;

#अगर_घोषित CONFIG_INFINIBAND_IPOIB_DEBUG
	रेजिस्टर_netdevice_notअगरier(&ipoib_netdev_notअगरier);
#पूर्ण_अगर
	वापस 0;

err_client:
	ib_unरेजिस्टर_client(&ipoib_client);

err_sa:
	ib_sa_unरेजिस्टर_client(&ipoib_sa_client);
	destroy_workqueue(ipoib_workqueue);

err_fs:
	ipoib_unरेजिस्टर_debugfs();

	वापस ret;
पूर्ण

अटल व्योम __निकास ipoib_cleanup_module(व्योम)
अणु
#अगर_घोषित CONFIG_INFINIBAND_IPOIB_DEBUG
	unरेजिस्टर_netdevice_notअगरier(&ipoib_netdev_notअगरier);
#पूर्ण_अगर
	ipoib_netlink_fini();
	ib_unरेजिस्टर_client(&ipoib_client);
	ib_sa_unरेजिस्टर_client(&ipoib_sa_client);
	ipoib_unरेजिस्टर_debugfs();
	destroy_workqueue(ipoib_workqueue);
पूर्ण

module_init(ipoib_init_module);
module_निकास(ipoib_cleanup_module);
