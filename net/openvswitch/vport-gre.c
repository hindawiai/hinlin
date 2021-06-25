<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2007-2014 Nicira, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/अगर.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <linux/अगर_tunnel.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/in.h>
#समावेश <linux/in_route.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/jhash.h>
#समावेश <linux/list.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/rculist.h>
#समावेश <net/route.h>
#समावेश <net/xfrm.h>

#समावेश <net/icmp.h>
#समावेश <net/ip.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/gre.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/protocol.h>

#समावेश "datapath.h"
#समावेश "vport.h"
#समावेश "vport-netdev.h"

अटल काष्ठा vport_ops ovs_gre_vport_ops;

अटल काष्ठा vport *gre_tnl_create(स्थिर काष्ठा vport_parms *parms)
अणु
	काष्ठा net *net = ovs_dp_get_net(parms->dp);
	काष्ठा net_device *dev;
	काष्ठा vport *vport;
	पूर्णांक err;

	vport = ovs_vport_alloc(0, &ovs_gre_vport_ops, parms);
	अगर (IS_ERR(vport))
		वापस vport;

	rtnl_lock();
	dev = gretap_fb_dev_create(net, parms->name, NET_NAME_USER);
	अगर (IS_ERR(dev)) अणु
		rtnl_unlock();
		ovs_vport_मुक्त(vport);
		वापस ERR_CAST(dev);
	पूर्ण

	err = dev_change_flags(dev, dev->flags | IFF_UP, शून्य);
	अगर (err < 0) अणु
		rtnl_delete_link(dev);
		rtnl_unlock();
		ovs_vport_मुक्त(vport);
		वापस ERR_PTR(err);
	पूर्ण

	rtnl_unlock();
	वापस vport;
पूर्ण

अटल काष्ठा vport *gre_create(स्थिर काष्ठा vport_parms *parms)
अणु
	काष्ठा vport *vport;

	vport = gre_tnl_create(parms);
	अगर (IS_ERR(vport))
		वापस vport;

	वापस ovs_netdev_link(vport, parms->name);
पूर्ण

अटल काष्ठा vport_ops ovs_gre_vport_ops = अणु
	.type		= OVS_VPORT_TYPE_GRE,
	.create		= gre_create,
	.send		= dev_queue_xmit,
	.destroy	= ovs_netdev_tunnel_destroy,
पूर्ण;

अटल पूर्णांक __init ovs_gre_tnl_init(व्योम)
अणु
	वापस ovs_vport_ops_रेजिस्टर(&ovs_gre_vport_ops);
पूर्ण

अटल व्योम __निकास ovs_gre_tnl_निकास(व्योम)
अणु
	ovs_vport_ops_unरेजिस्टर(&ovs_gre_vport_ops);
पूर्ण

module_init(ovs_gre_tnl_init);
module_निकास(ovs_gre_tnl_निकास);

MODULE_DESCRIPTION("OVS: GRE switching port");
MODULE_LICENSE("GPL");
MODULE_ALIAS("vport-type-3");
