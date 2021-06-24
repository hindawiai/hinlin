<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2007-2012 Nicira, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/kernel.h>
#समावेश <linux/llc.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/खोलोvचयन.h>
#समावेश <linux/export.h>

#समावेश <net/ip_tunnels.h>
#समावेश <net/rtnetlink.h>

#समावेश "datapath.h"
#समावेश "vport.h"
#समावेश "vport-internal_dev.h"
#समावेश "vport-netdev.h"

अटल काष्ठा vport_ops ovs_netdev_vport_ops;

/* Must be called with rcu_पढ़ो_lock. */
अटल व्योम netdev_port_receive(काष्ठा sk_buff *skb)
अणु
	काष्ठा vport *vport;

	vport = ovs_netdev_get_vport(skb->dev);
	अगर (unlikely(!vport))
		जाओ error;

	अगर (unlikely(skb_warn_अगर_lro(skb)))
		जाओ error;

	/* Make our own copy of the packet.  Otherwise we will mangle the
	 * packet क्रम anyone who came beक्रमe us (e.g. tcpdump via AF_PACKET).
	 */
	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (unlikely(!skb))
		वापस;

	अगर (skb->dev->type == ARPHRD_ETHER)
		skb_push_rcsum(skb, ETH_HLEN);

	ovs_vport_receive(vport, skb, skb_tunnel_info(skb));
	वापस;
error:
	kमुक्त_skb(skb);
पूर्ण

/* Called with rcu_पढ़ो_lock and bottom-halves disabled. */
अटल rx_handler_result_t netdev_frame_hook(काष्ठा sk_buff **pskb)
अणु
	काष्ठा sk_buff *skb = *pskb;

	अगर (unlikely(skb->pkt_type == PACKET_LOOPBACK))
		वापस RX_HANDLER_PASS;

	netdev_port_receive(skb);
	वापस RX_HANDLER_CONSUMED;
पूर्ण

अटल काष्ठा net_device *get_dpdev(स्थिर काष्ठा datapath *dp)
अणु
	काष्ठा vport *local;

	local = ovs_vport_ovsl(dp, OVSP_LOCAL);
	वापस local->dev;
पूर्ण

काष्ठा vport *ovs_netdev_link(काष्ठा vport *vport, स्थिर अक्षर *name)
अणु
	पूर्णांक err;

	vport->dev = dev_get_by_name(ovs_dp_get_net(vport->dp), name);
	अगर (!vport->dev) अणु
		err = -ENODEV;
		जाओ error_मुक्त_vport;
	पूर्ण

	अगर (vport->dev->flags & IFF_LOOPBACK ||
	    (vport->dev->type != ARPHRD_ETHER &&
	     vport->dev->type != ARPHRD_NONE) ||
	    ovs_is_पूर्णांकernal_dev(vport->dev)) अणु
		err = -EINVAL;
		जाओ error_put;
	पूर्ण

	rtnl_lock();
	err = netdev_master_upper_dev_link(vport->dev,
					   get_dpdev(vport->dp),
					   शून्य, शून्य, शून्य);
	अगर (err)
		जाओ error_unlock;

	err = netdev_rx_handler_रेजिस्टर(vport->dev, netdev_frame_hook,
					 vport);
	अगर (err)
		जाओ error_master_upper_dev_unlink;

	dev_disable_lro(vport->dev);
	dev_set_promiscuity(vport->dev, 1);
	vport->dev->priv_flags |= IFF_OVS_DATAPATH;
	rtnl_unlock();

	वापस vport;

error_master_upper_dev_unlink:
	netdev_upper_dev_unlink(vport->dev, get_dpdev(vport->dp));
error_unlock:
	rtnl_unlock();
error_put:
	dev_put(vport->dev);
error_मुक्त_vport:
	ovs_vport_मुक्त(vport);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(ovs_netdev_link);

अटल काष्ठा vport *netdev_create(स्थिर काष्ठा vport_parms *parms)
अणु
	काष्ठा vport *vport;

	vport = ovs_vport_alloc(0, &ovs_netdev_vport_ops, parms);
	अगर (IS_ERR(vport))
		वापस vport;

	वापस ovs_netdev_link(vport, parms->name);
पूर्ण

अटल व्योम vport_netdev_मुक्त(काष्ठा rcu_head *rcu)
अणु
	काष्ठा vport *vport = container_of(rcu, काष्ठा vport, rcu);

	अगर (vport->dev)
		dev_put(vport->dev);
	ovs_vport_मुक्त(vport);
पूर्ण

व्योम ovs_netdev_detach_dev(काष्ठा vport *vport)
अणु
	ASSERT_RTNL();
	vport->dev->priv_flags &= ~IFF_OVS_DATAPATH;
	netdev_rx_handler_unरेजिस्टर(vport->dev);
	netdev_upper_dev_unlink(vport->dev,
				netdev_master_upper_dev_get(vport->dev));
	dev_set_promiscuity(vport->dev, -1);
पूर्ण

अटल व्योम netdev_destroy(काष्ठा vport *vport)
अणु
	rtnl_lock();
	अगर (netअगर_is_ovs_port(vport->dev))
		ovs_netdev_detach_dev(vport);
	rtnl_unlock();

	call_rcu(&vport->rcu, vport_netdev_मुक्त);
पूर्ण

व्योम ovs_netdev_tunnel_destroy(काष्ठा vport *vport)
अणु
	rtnl_lock();
	अगर (netअगर_is_ovs_port(vport->dev))
		ovs_netdev_detach_dev(vport);

	/* We can be invoked by both explicit vport deletion and
	 * underlying netdev deregistration; delete the link only
	 * अगर it's not alपढ़ोy shutting करोwn.
	 */
	अगर (vport->dev->reg_state == NETREG_REGISTERED)
		rtnl_delete_link(vport->dev);
	dev_put(vport->dev);
	vport->dev = शून्य;
	rtnl_unlock();

	call_rcu(&vport->rcu, vport_netdev_मुक्त);
पूर्ण
EXPORT_SYMBOL_GPL(ovs_netdev_tunnel_destroy);

/* Returns null अगर this device is not attached to a datapath. */
काष्ठा vport *ovs_netdev_get_vport(काष्ठा net_device *dev)
अणु
	अगर (likely(netअगर_is_ovs_port(dev)))
		वापस (काष्ठा vport *)
			rcu_dereference_rtnl(dev->rx_handler_data);
	अन्यथा
		वापस शून्य;
पूर्ण

अटल काष्ठा vport_ops ovs_netdev_vport_ops = अणु
	.type		= OVS_VPORT_TYPE_NETDEV,
	.create		= netdev_create,
	.destroy	= netdev_destroy,
	.send		= dev_queue_xmit,
पूर्ण;

पूर्णांक __init ovs_netdev_init(व्योम)
अणु
	वापस ovs_vport_ops_रेजिस्टर(&ovs_netdev_vport_ops);
पूर्ण

व्योम ovs_netdev_निकास(व्योम)
अणु
	ovs_vport_ops_unरेजिस्टर(&ovs_netdev_vport_ops);
पूर्ण
