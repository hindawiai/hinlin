<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2013-2018, The Linux Foundation. All rights reserved.
 *
 * RMNET configuration engine
 */

#समावेश <net/sock.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netdevice.h>
#समावेश "rmnet_config.h"
#समावेश "rmnet_handlers.h"
#समावेश "rmnet_vnd.h"
#समावेश "rmnet_private.h"

/* Local Definitions and Declarations */

अटल स्थिर काष्ठा nla_policy rmnet_policy[IFLA_RMNET_MAX + 1] = अणु
	[IFLA_RMNET_MUX_ID]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_RMNET_FLAGS]	= अणु .len = माप(काष्ठा अगरla_rmnet_flags) पूर्ण,
पूर्ण;

अटल पूर्णांक rmnet_is_real_dev_रेजिस्टरed(स्थिर काष्ठा net_device *real_dev)
अणु
	वापस rcu_access_poपूर्णांकer(real_dev->rx_handler) == rmnet_rx_handler;
पूर्ण

/* Needs rtnl lock */
काष्ठा rmnet_port*
rmnet_get_port_rtnl(स्थिर काष्ठा net_device *real_dev)
अणु
	वापस rtnl_dereference(real_dev->rx_handler_data);
पूर्ण

अटल पूर्णांक rmnet_unरेजिस्टर_real_device(काष्ठा net_device *real_dev)
अणु
	काष्ठा rmnet_port *port = rmnet_get_port_rtnl(real_dev);

	अगर (port->nr_rmnet_devs)
		वापस -EINVAL;

	netdev_rx_handler_unरेजिस्टर(real_dev);

	kमुक्त(port);

	netdev_dbg(real_dev, "Removed from rmnet\n");
	वापस 0;
पूर्ण

अटल पूर्णांक rmnet_रेजिस्टर_real_device(काष्ठा net_device *real_dev,
				      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा rmnet_port *port;
	पूर्णांक rc, entry;

	ASSERT_RTNL();

	अगर (rmnet_is_real_dev_रेजिस्टरed(real_dev)) अणु
		port = rmnet_get_port_rtnl(real_dev);
		अगर (port->rmnet_mode != RMNET_EPMODE_VND) अणु
			NL_SET_ERR_MSG_MOD(extack, "bridge device already exists");
			वापस -EINVAL;
		पूर्ण

		वापस 0;
	पूर्ण

	port = kzalloc(माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;

	port->dev = real_dev;
	rc = netdev_rx_handler_रेजिस्टर(real_dev, rmnet_rx_handler, port);
	अगर (rc) अणु
		kमुक्त(port);
		वापस -EBUSY;
	पूर्ण

	क्रम (entry = 0; entry < RMNET_MAX_LOGICAL_EP; entry++)
		INIT_HLIST_HEAD(&port->muxed_ep[entry]);

	netdev_dbg(real_dev, "registered with rmnet\n");
	वापस 0;
पूर्ण

अटल व्योम rmnet_unरेजिस्टर_bridge(काष्ठा rmnet_port *port)
अणु
	काष्ठा net_device *bridge_dev, *real_dev, *rmnet_dev;
	काष्ठा rmnet_port *real_port;

	अगर (port->rmnet_mode != RMNET_EPMODE_BRIDGE)
		वापस;

	rmnet_dev = port->rmnet_dev;
	अगर (!port->nr_rmnet_devs) अणु
		/* bridge device */
		real_dev = port->bridge_ep;
		bridge_dev = port->dev;

		real_port = rmnet_get_port_rtnl(real_dev);
		real_port->bridge_ep = शून्य;
		real_port->rmnet_mode = RMNET_EPMODE_VND;
	पूर्ण अन्यथा अणु
		/* real device */
		bridge_dev = port->bridge_ep;

		port->bridge_ep = शून्य;
		port->rmnet_mode = RMNET_EPMODE_VND;
	पूर्ण

	netdev_upper_dev_unlink(bridge_dev, rmnet_dev);
	rmnet_unरेजिस्टर_real_device(bridge_dev);
पूर्ण

अटल पूर्णांक rmnet_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			 काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			 काष्ठा netlink_ext_ack *extack)
अणु
	u32 data_क्रमmat = RMNET_FLAGS_INGRESS_DEAGGREGATION;
	काष्ठा net_device *real_dev;
	पूर्णांक mode = RMNET_EPMODE_VND;
	काष्ठा rmnet_endpoपूर्णांक *ep;
	काष्ठा rmnet_port *port;
	पूर्णांक err = 0;
	u16 mux_id;

	अगर (!tb[IFLA_LINK]) अणु
		NL_SET_ERR_MSG_MOD(extack, "link not specified");
		वापस -EINVAL;
	पूर्ण

	real_dev = __dev_get_by_index(src_net, nla_get_u32(tb[IFLA_LINK]));
	अगर (!real_dev) अणु
		NL_SET_ERR_MSG_MOD(extack, "link does not exist");
		वापस -ENODEV;
	पूर्ण

	ep = kzalloc(माप(*ep), GFP_KERNEL);
	अगर (!ep)
		वापस -ENOMEM;

	mux_id = nla_get_u16(data[IFLA_RMNET_MUX_ID]);

	err = rmnet_रेजिस्टर_real_device(real_dev, extack);
	अगर (err)
		जाओ err0;

	port = rmnet_get_port_rtnl(real_dev);
	err = rmnet_vnd_newlink(mux_id, dev, port, real_dev, ep, extack);
	अगर (err)
		जाओ err1;

	err = netdev_upper_dev_link(real_dev, dev, extack);
	अगर (err < 0)
		जाओ err2;

	port->rmnet_mode = mode;
	port->rmnet_dev = dev;

	hlist_add_head_rcu(&ep->hlnode, &port->muxed_ep[mux_id]);

	अगर (data[IFLA_RMNET_FLAGS]) अणु
		काष्ठा अगरla_rmnet_flags *flags;

		flags = nla_data(data[IFLA_RMNET_FLAGS]);
		data_क्रमmat = flags->flags & flags->mask;
	पूर्ण

	netdev_dbg(dev, "data format [0x%08X]\n", data_क्रमmat);
	port->data_क्रमmat = data_क्रमmat;

	वापस 0;

err2:
	unरेजिस्टर_netdevice(dev);
	rmnet_vnd_dellink(mux_id, port, ep);
err1:
	rmnet_unरेजिस्टर_real_device(real_dev);
err0:
	kमुक्त(ep);
	वापस err;
पूर्ण

अटल व्योम rmnet_dellink(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	काष्ठा rmnet_priv *priv = netdev_priv(dev);
	काष्ठा net_device *real_dev, *bridge_dev;
	काष्ठा rmnet_port *real_port, *bridge_port;
	काष्ठा rmnet_endpoपूर्णांक *ep;
	u8 mux_id = priv->mux_id;

	real_dev = priv->real_dev;

	अगर (!rmnet_is_real_dev_रेजिस्टरed(real_dev))
		वापस;

	real_port = rmnet_get_port_rtnl(real_dev);
	bridge_dev = real_port->bridge_ep;
	अगर (bridge_dev) अणु
		bridge_port = rmnet_get_port_rtnl(bridge_dev);
		rmnet_unरेजिस्टर_bridge(bridge_port);
	पूर्ण

	ep = rmnet_get_endpoपूर्णांक(real_port, mux_id);
	अगर (ep) अणु
		hlist_del_init_rcu(&ep->hlnode);
		rmnet_vnd_dellink(mux_id, real_port, ep);
		kमुक्त(ep);
	पूर्ण

	netdev_upper_dev_unlink(real_dev, dev);
	rmnet_unरेजिस्टर_real_device(real_dev);
	unरेजिस्टर_netdevice_queue(dev, head);
पूर्ण

अटल व्योम rmnet_क्रमce_unassociate_device(काष्ठा net_device *real_dev)
अणु
	काष्ठा hlist_node *पंचांगp_ep;
	काष्ठा rmnet_endpoपूर्णांक *ep;
	काष्ठा rmnet_port *port;
	अचिन्हित दीर्घ bkt_ep;
	LIST_HEAD(list);

	port = rmnet_get_port_rtnl(real_dev);

	अगर (port->nr_rmnet_devs) अणु
		/* real device */
		rmnet_unरेजिस्टर_bridge(port);
		hash_क्रम_each_safe(port->muxed_ep, bkt_ep, पंचांगp_ep, ep, hlnode) अणु
			unरेजिस्टर_netdevice_queue(ep->egress_dev, &list);
			netdev_upper_dev_unlink(real_dev, ep->egress_dev);
			rmnet_vnd_dellink(ep->mux_id, port, ep);
			hlist_del_init_rcu(&ep->hlnode);
			kमुक्त(ep);
		पूर्ण
		rmnet_unरेजिस्टर_real_device(real_dev);
		unरेजिस्टर_netdevice_many(&list);
	पूर्ण अन्यथा अणु
		rmnet_unरेजिस्टर_bridge(port);
	पूर्ण
पूर्ण

अटल पूर्णांक rmnet_config_notअगरy_cb(काष्ठा notअगरier_block *nb,
				  अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा net_device *real_dev = netdev_notअगरier_info_to_dev(data);

	अगर (!rmnet_is_real_dev_रेजिस्टरed(real_dev))
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_UNREGISTER:
		netdev_dbg(real_dev, "Kernel unregister\n");
		rmnet_क्रमce_unassociate_device(real_dev);
		अवरोध;
	हाल NETDEV_CHANGEMTU:
		अगर (rmnet_vnd_validate_real_dev_mtu(real_dev))
			वापस NOTIFY_BAD;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block rmnet_dev_notअगरier __पढ़ो_mostly = अणु
	.notअगरier_call = rmnet_config_notअगरy_cb,
पूर्ण;

अटल पूर्णांक rmnet_rtnl_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			       काष्ठा netlink_ext_ack *extack)
अणु
	u16 mux_id;

	अगर (!data || !data[IFLA_RMNET_MUX_ID]) अणु
		NL_SET_ERR_MSG_MOD(extack, "MUX ID not specified");
		वापस -EINVAL;
	पूर्ण

	mux_id = nla_get_u16(data[IFLA_RMNET_MUX_ID]);
	अगर (mux_id > (RMNET_MAX_LOGICAL_EP - 1)) अणु
		NL_SET_ERR_MSG_MOD(extack, "invalid MUX ID");
		वापस -दुस्फल;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmnet_changelink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
			    काष्ठा nlattr *data[],
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा rmnet_priv *priv = netdev_priv(dev);
	काष्ठा net_device *real_dev;
	काष्ठा rmnet_port *port;
	u16 mux_id;

	अगर (!dev)
		वापस -ENODEV;

	real_dev = priv->real_dev;
	अगर (!rmnet_is_real_dev_रेजिस्टरed(real_dev))
		वापस -ENODEV;

	port = rmnet_get_port_rtnl(real_dev);

	अगर (data[IFLA_RMNET_MUX_ID]) अणु
		mux_id = nla_get_u16(data[IFLA_RMNET_MUX_ID]);

		अगर (mux_id != priv->mux_id) अणु
			काष्ठा rmnet_endpoपूर्णांक *ep;

			ep = rmnet_get_endpoपूर्णांक(port, priv->mux_id);
			अगर (!ep)
				वापस -ENODEV;

			अगर (rmnet_get_endpoपूर्णांक(port, mux_id)) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "MUX ID already exists");
				वापस -EINVAL;
			पूर्ण

			hlist_del_init_rcu(&ep->hlnode);
			hlist_add_head_rcu(&ep->hlnode,
					   &port->muxed_ep[mux_id]);

			ep->mux_id = mux_id;
			priv->mux_id = mux_id;
		पूर्ण
	पूर्ण

	अगर (data[IFLA_RMNET_FLAGS]) अणु
		काष्ठा अगरla_rmnet_flags *flags;
		u32 old_data_क्रमmat;

		old_data_क्रमmat = port->data_क्रमmat;
		flags = nla_data(data[IFLA_RMNET_FLAGS]);
		port->data_क्रमmat = flags->flags & flags->mask;

		अगर (rmnet_vnd_update_dev_mtu(port, real_dev)) अणु
			port->data_क्रमmat = old_data_क्रमmat;
			NL_SET_ERR_MSG_MOD(extack, "Invalid MTU on real dev");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल माप_प्रकार rmnet_get_size(स्थिर काष्ठा net_device *dev)
अणु
	वापस
		/* IFLA_RMNET_MUX_ID */
		nla_total_size(2) +
		/* IFLA_RMNET_FLAGS */
		nla_total_size(माप(काष्ठा अगरla_rmnet_flags));
पूर्ण

अटल पूर्णांक rmnet_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा rmnet_priv *priv = netdev_priv(dev);
	काष्ठा net_device *real_dev;
	काष्ठा अगरla_rmnet_flags f;
	काष्ठा rmnet_port *port;

	real_dev = priv->real_dev;

	अगर (nla_put_u16(skb, IFLA_RMNET_MUX_ID, priv->mux_id))
		जाओ nla_put_failure;

	अगर (rmnet_is_real_dev_रेजिस्टरed(real_dev)) अणु
		port = rmnet_get_port_rtnl(real_dev);
		f.flags = port->data_क्रमmat;
	पूर्ण अन्यथा अणु
		f.flags = 0;
	पूर्ण

	f.mask  = ~0;

	अगर (nla_put(skb, IFLA_RMNET_FLAGS, माप(f), &f))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

काष्ठा rtnl_link_ops rmnet_link_ops __पढ़ो_mostly = अणु
	.kind		= "rmnet",
	.maxtype	= __IFLA_RMNET_MAX,
	.priv_size	= माप(काष्ठा rmnet_priv),
	.setup		= rmnet_vnd_setup,
	.validate	= rmnet_rtnl_validate,
	.newlink	= rmnet_newlink,
	.dellink	= rmnet_dellink,
	.get_size	= rmnet_get_size,
	.changelink     = rmnet_changelink,
	.policy		= rmnet_policy,
	.fill_info	= rmnet_fill_info,
पूर्ण;

काष्ठा rmnet_port *rmnet_get_port_rcu(काष्ठा net_device *real_dev)
अणु
	अगर (rmnet_is_real_dev_रेजिस्टरed(real_dev))
		वापस rcu_dereference_bh(real_dev->rx_handler_data);
	अन्यथा
		वापस शून्य;
पूर्ण

काष्ठा rmnet_endpoपूर्णांक *rmnet_get_endpoपूर्णांक(काष्ठा rmnet_port *port, u8 mux_id)
अणु
	काष्ठा rmnet_endpoपूर्णांक *ep;

	hlist_क्रम_each_entry_rcu(ep, &port->muxed_ep[mux_id], hlnode) अणु
		अगर (ep->mux_id == mux_id)
			वापस ep;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक rmnet_add_bridge(काष्ठा net_device *rmnet_dev,
		     काष्ठा net_device *slave_dev,
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा rmnet_priv *priv = netdev_priv(rmnet_dev);
	काष्ठा net_device *real_dev = priv->real_dev;
	काष्ठा rmnet_port *port, *slave_port;
	पूर्णांक err;

	port = rmnet_get_port_rtnl(real_dev);

	/* If there is more than one rmnet dev attached, its probably being
	 * used क्रम muxing. Skip the briding in that हाल
	 */
	अगर (port->nr_rmnet_devs > 1) अणु
		NL_SET_ERR_MSG_MOD(extack, "more than one rmnet dev attached");
		वापस -EINVAL;
	पूर्ण

	अगर (port->rmnet_mode != RMNET_EPMODE_VND) अणु
		NL_SET_ERR_MSG_MOD(extack, "more than one bridge dev attached");
		वापस -EINVAL;
	पूर्ण

	अगर (rmnet_is_real_dev_रेजिस्टरed(slave_dev)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "slave cannot be another rmnet dev");

		वापस -EBUSY;
	पूर्ण

	err = rmnet_रेजिस्टर_real_device(slave_dev, extack);
	अगर (err)
		वापस -EBUSY;

	err = netdev_master_upper_dev_link(slave_dev, rmnet_dev, शून्य, शून्य,
					   extack);
	अगर (err) अणु
		rmnet_unरेजिस्टर_real_device(slave_dev);
		वापस err;
	पूर्ण

	slave_port = rmnet_get_port_rtnl(slave_dev);
	slave_port->rmnet_mode = RMNET_EPMODE_BRIDGE;
	slave_port->bridge_ep = real_dev;
	slave_port->rmnet_dev = rmnet_dev;

	port->rmnet_mode = RMNET_EPMODE_BRIDGE;
	port->bridge_ep = slave_dev;

	netdev_dbg(slave_dev, "registered with rmnet as slave\n");
	वापस 0;
पूर्ण

पूर्णांक rmnet_del_bridge(काष्ठा net_device *rmnet_dev,
		     काष्ठा net_device *slave_dev)
अणु
	काष्ठा rmnet_port *port = rmnet_get_port_rtnl(slave_dev);

	rmnet_unरेजिस्टर_bridge(port);

	netdev_dbg(slave_dev, "removed from rmnet as slave\n");
	वापस 0;
पूर्ण

/* Startup/Shutकरोwn */

अटल पूर्णांक __init rmnet_init(व्योम)
अणु
	पूर्णांक rc;

	rc = रेजिस्टर_netdevice_notअगरier(&rmnet_dev_notअगरier);
	अगर (rc != 0)
		वापस rc;

	rc = rtnl_link_रेजिस्टर(&rmnet_link_ops);
	अगर (rc != 0) अणु
		unरेजिस्टर_netdevice_notअगरier(&rmnet_dev_notअगरier);
		वापस rc;
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम __निकास rmnet_निकास(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&rmnet_link_ops);
	unरेजिस्टर_netdevice_notअगरier(&rmnet_dev_notअगरier);
पूर्ण

module_init(rmnet_init)
module_निकास(rmnet_निकास)
MODULE_ALIAS_RTNL_LINK("rmnet");
MODULE_LICENSE("GPL v2");
