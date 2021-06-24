<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 Nicira, Inc.
 * Copyright (c) 2013 Cisco Systems, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/खोलोvचयन.h>
#समावेश <linux/module.h>
#समावेश <net/udp.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/vxlan.h>

#समावेश "datapath.h"
#समावेश "vport.h"
#समावेश "vport-netdev.h"

अटल काष्ठा vport_ops ovs_vxlan_netdev_vport_ops;

अटल पूर्णांक vxlan_get_options(स्थिर काष्ठा vport *vport, काष्ठा sk_buff *skb)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(vport->dev);
	__be16 dst_port = vxlan->cfg.dst_port;

	अगर (nla_put_u16(skb, OVS_TUNNEL_ATTR_DST_PORT, ntohs(dst_port)))
		वापस -EMSGSIZE;

	अगर (vxlan->cfg.flags & VXLAN_F_GBP) अणु
		काष्ठा nlattr *exts;

		exts = nla_nest_start_noflag(skb, OVS_TUNNEL_ATTR_EXTENSION);
		अगर (!exts)
			वापस -EMSGSIZE;

		अगर (vxlan->cfg.flags & VXLAN_F_GBP &&
		    nla_put_flag(skb, OVS_VXLAN_EXT_GBP))
			वापस -EMSGSIZE;

		nla_nest_end(skb, exts);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy exts_policy[OVS_VXLAN_EXT_MAX + 1] = अणु
	[OVS_VXLAN_EXT_GBP]	= अणु .type = NLA_FLAG, पूर्ण,
पूर्ण;

अटल पूर्णांक vxlan_configure_exts(काष्ठा vport *vport, काष्ठा nlattr *attr,
				काष्ठा vxlan_config *conf)
अणु
	काष्ठा nlattr *exts[OVS_VXLAN_EXT_MAX + 1];
	पूर्णांक err;

	अगर (nla_len(attr) < माप(काष्ठा nlattr))
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(exts, OVS_VXLAN_EXT_MAX, attr,
					  exts_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (exts[OVS_VXLAN_EXT_GBP])
		conf->flags |= VXLAN_F_GBP;

	वापस 0;
पूर्ण

अटल काष्ठा vport *vxlan_tnl_create(स्थिर काष्ठा vport_parms *parms)
अणु
	काष्ठा net *net = ovs_dp_get_net(parms->dp);
	काष्ठा nlattr *options = parms->options;
	काष्ठा net_device *dev;
	काष्ठा vport *vport;
	काष्ठा nlattr *a;
	पूर्णांक err;
	काष्ठा vxlan_config conf = अणु
		.no_share = true,
		.flags = VXLAN_F_COLLECT_METADATA | VXLAN_F_UDP_ZERO_CSUM6_RX,
		/* Don't restrict the packets that can be sent by MTU */
		.mtu = IP_MAX_MTU,
	पूर्ण;

	अगर (!options) अणु
		err = -EINVAL;
		जाओ error;
	पूर्ण

	a = nla_find_nested(options, OVS_TUNNEL_ATTR_DST_PORT);
	अगर (a && nla_len(a) == माप(u16)) अणु
		conf.dst_port = htons(nla_get_u16(a));
	पूर्ण अन्यथा अणु
		/* Require destination port from userspace. */
		err = -EINVAL;
		जाओ error;
	पूर्ण

	vport = ovs_vport_alloc(0, &ovs_vxlan_netdev_vport_ops, parms);
	अगर (IS_ERR(vport))
		वापस vport;

	a = nla_find_nested(options, OVS_TUNNEL_ATTR_EXTENSION);
	अगर (a) अणु
		err = vxlan_configure_exts(vport, a, &conf);
		अगर (err) अणु
			ovs_vport_मुक्त(vport);
			जाओ error;
		पूर्ण
	पूर्ण

	rtnl_lock();
	dev = vxlan_dev_create(net, parms->name, NET_NAME_USER, &conf);
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

अटल काष्ठा vport *vxlan_create(स्थिर काष्ठा vport_parms *parms)
अणु
	काष्ठा vport *vport;

	vport = vxlan_tnl_create(parms);
	अगर (IS_ERR(vport))
		वापस vport;

	वापस ovs_netdev_link(vport, parms->name);
पूर्ण

अटल काष्ठा vport_ops ovs_vxlan_netdev_vport_ops = अणु
	.type			= OVS_VPORT_TYPE_VXLAN,
	.create			= vxlan_create,
	.destroy		= ovs_netdev_tunnel_destroy,
	.get_options		= vxlan_get_options,
	.send			= dev_queue_xmit,
पूर्ण;

अटल पूर्णांक __init ovs_vxlan_tnl_init(व्योम)
अणु
	वापस ovs_vport_ops_रेजिस्टर(&ovs_vxlan_netdev_vport_ops);
पूर्ण

अटल व्योम __निकास ovs_vxlan_tnl_निकास(व्योम)
अणु
	ovs_vport_ops_unरेजिस्टर(&ovs_vxlan_netdev_vport_ops);
पूर्ण

module_init(ovs_vxlan_tnl_init);
module_निकास(ovs_vxlan_tnl_निकास);

MODULE_DESCRIPTION("OVS: VXLAN switching port");
MODULE_LICENSE("GPL");
MODULE_ALIAS("vport-type-4");
