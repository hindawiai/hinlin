<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2014 Nicira, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/net.h>
#समावेश <linux/rculist.h>
#समावेश <linux/udp.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/module.h>

#समावेश <net/geneve.h>
#समावेश <net/icmp.h>
#समावेश <net/ip.h>
#समावेश <net/route.h>
#समावेश <net/udp.h>
#समावेश <net/xfrm.h>

#समावेश "datapath.h"
#समावेश "vport.h"
#समावेश "vport-netdev.h"

अटल काष्ठा vport_ops ovs_geneve_vport_ops;
/**
 * काष्ठा geneve_port - Keeps track of खोलो UDP ports
 * @dst_port: destination port.
 */
काष्ठा geneve_port अणु
	u16 dst_port;
पूर्ण;

अटल अंतरभूत काष्ठा geneve_port *geneve_vport(स्थिर काष्ठा vport *vport)
अणु
	वापस vport_priv(vport);
पूर्ण

अटल पूर्णांक geneve_get_options(स्थिर काष्ठा vport *vport,
			      काष्ठा sk_buff *skb)
अणु
	काष्ठा geneve_port *geneve_port = geneve_vport(vport);

	अगर (nla_put_u16(skb, OVS_TUNNEL_ATTR_DST_PORT, geneve_port->dst_port))
		वापस -EMSGSIZE;
	वापस 0;
पूर्ण

अटल काष्ठा vport *geneve_tnl_create(स्थिर काष्ठा vport_parms *parms)
अणु
	काष्ठा net *net = ovs_dp_get_net(parms->dp);
	काष्ठा nlattr *options = parms->options;
	काष्ठा geneve_port *geneve_port;
	काष्ठा net_device *dev;
	काष्ठा vport *vport;
	काष्ठा nlattr *a;
	u16 dst_port;
	पूर्णांक err;

	अगर (!options) अणु
		err = -EINVAL;
		जाओ error;
	पूर्ण

	a = nla_find_nested(options, OVS_TUNNEL_ATTR_DST_PORT);
	अगर (a && nla_len(a) == माप(u16)) अणु
		dst_port = nla_get_u16(a);
	पूर्ण अन्यथा अणु
		/* Require destination port from userspace. */
		err = -EINVAL;
		जाओ error;
	पूर्ण

	vport = ovs_vport_alloc(माप(काष्ठा geneve_port),
				&ovs_geneve_vport_ops, parms);
	अगर (IS_ERR(vport))
		वापस vport;

	geneve_port = geneve_vport(vport);
	geneve_port->dst_port = dst_port;

	rtnl_lock();
	dev = geneve_dev_create_fb(net, parms->name, NET_NAME_USER, dst_port);
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
		जाओ error;
	पूर्ण

	rtnl_unlock();
	वापस vport;
error:
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा vport *geneve_create(स्थिर काष्ठा vport_parms *parms)
अणु
	काष्ठा vport *vport;

	vport = geneve_tnl_create(parms);
	अगर (IS_ERR(vport))
		वापस vport;

	वापस ovs_netdev_link(vport, parms->name);
पूर्ण

अटल काष्ठा vport_ops ovs_geneve_vport_ops = अणु
	.type		= OVS_VPORT_TYPE_GENEVE,
	.create		= geneve_create,
	.destroy	= ovs_netdev_tunnel_destroy,
	.get_options	= geneve_get_options,
	.send		= dev_queue_xmit,
पूर्ण;

अटल पूर्णांक __init ovs_geneve_tnl_init(व्योम)
अणु
	वापस ovs_vport_ops_रेजिस्टर(&ovs_geneve_vport_ops);
पूर्ण

अटल व्योम __निकास ovs_geneve_tnl_निकास(व्योम)
अणु
	ovs_vport_ops_unरेजिस्टर(&ovs_geneve_vport_ops);
पूर्ण

module_init(ovs_geneve_tnl_init);
module_निकास(ovs_geneve_tnl_निकास);

MODULE_DESCRIPTION("OVS: Geneve switching port");
MODULE_LICENSE("GPL");
MODULE_ALIAS("vport-type-5");
