<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	VLAN netlink control पूर्णांकerface
 *
 * 	Copyright (c) 2007 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/module.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netlink.h>
#समावेश <net/rtnetlink.h>
#समावेश "vlan.h"


अटल स्थिर काष्ठा nla_policy vlan_policy[IFLA_VLAN_MAX + 1] = अणु
	[IFLA_VLAN_ID]		= अणु .type = NLA_U16 पूर्ण,
	[IFLA_VLAN_FLAGS]	= अणु .len = माप(काष्ठा अगरla_vlan_flags) पूर्ण,
	[IFLA_VLAN_EGRESS_QOS]	= अणु .type = NLA_NESTED पूर्ण,
	[IFLA_VLAN_INGRESS_QOS] = अणु .type = NLA_NESTED पूर्ण,
	[IFLA_VLAN_PROTOCOL]	= अणु .type = NLA_U16 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy vlan_map_policy[IFLA_VLAN_QOS_MAX + 1] = अणु
	[IFLA_VLAN_QOS_MAPPING] = अणु .len = माप(काष्ठा अगरla_vlan_qos_mapping) पूर्ण,
पूर्ण;


अटल अंतरभूत पूर्णांक vlan_validate_qos_map(काष्ठा nlattr *attr)
अणु
	अगर (!attr)
		वापस 0;
	वापस nla_validate_nested_deprecated(attr, IFLA_VLAN_QOS_MAX,
					      vlan_map_policy, शून्य);
पूर्ण

अटल पूर्णांक vlan_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा अगरla_vlan_flags *flags;
	u16 id;
	पूर्णांक err;

	अगर (tb[IFLA_ADDRESS]) अणु
		अगर (nla_len(tb[IFLA_ADDRESS]) != ETH_ALEN) अणु
			NL_SET_ERR_MSG_MOD(extack, "Invalid link address");
			वापस -EINVAL;
		पूर्ण
		अगर (!is_valid_ether_addr(nla_data(tb[IFLA_ADDRESS]))) अणु
			NL_SET_ERR_MSG_MOD(extack, "Invalid link address");
			वापस -EADDRNOTAVAIL;
		पूर्ण
	पूर्ण

	अगर (!data) अणु
		NL_SET_ERR_MSG_MOD(extack, "VLAN properties not specified");
		वापस -EINVAL;
	पूर्ण

	अगर (data[IFLA_VLAN_PROTOCOL]) अणु
		चयन (nla_get_be16(data[IFLA_VLAN_PROTOCOL])) अणु
		हाल htons(ETH_P_8021Q):
		हाल htons(ETH_P_8021AD):
			अवरोध;
		शेष:
			NL_SET_ERR_MSG_MOD(extack, "Invalid VLAN protocol");
			वापस -EPROTONOSUPPORT;
		पूर्ण
	पूर्ण

	अगर (data[IFLA_VLAN_ID]) अणु
		id = nla_get_u16(data[IFLA_VLAN_ID]);
		अगर (id >= VLAN_VID_MASK) अणु
			NL_SET_ERR_MSG_MOD(extack, "Invalid VLAN id");
			वापस -दुस्फल;
		पूर्ण
	पूर्ण
	अगर (data[IFLA_VLAN_FLAGS]) अणु
		flags = nla_data(data[IFLA_VLAN_FLAGS]);
		अगर ((flags->flags & flags->mask) &
		    ~(VLAN_FLAG_REORDER_HDR | VLAN_FLAG_GVRP |
		      VLAN_FLAG_LOOSE_BINDING | VLAN_FLAG_MVRP |
		      VLAN_FLAG_BRIDGE_BINDING)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Invalid VLAN flags");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	err = vlan_validate_qos_map(data[IFLA_VLAN_INGRESS_QOS]);
	अगर (err < 0) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid ingress QOS map");
		वापस err;
	पूर्ण
	err = vlan_validate_qos_map(data[IFLA_VLAN_EGRESS_QOS]);
	अगर (err < 0) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid egress QOS map");
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vlan_changelink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
			   काष्ठा nlattr *data[],
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा अगरla_vlan_flags *flags;
	काष्ठा अगरla_vlan_qos_mapping *m;
	काष्ठा nlattr *attr;
	पूर्णांक rem, err;

	अगर (data[IFLA_VLAN_FLAGS]) अणु
		flags = nla_data(data[IFLA_VLAN_FLAGS]);
		err = vlan_dev_change_flags(dev, flags->flags, flags->mask);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (data[IFLA_VLAN_INGRESS_QOS]) अणु
		nla_क्रम_each_nested(attr, data[IFLA_VLAN_INGRESS_QOS], rem) अणु
			m = nla_data(attr);
			vlan_dev_set_ingress_priority(dev, m->to, m->from);
		पूर्ण
	पूर्ण
	अगर (data[IFLA_VLAN_EGRESS_QOS]) अणु
		nla_क्रम_each_nested(attr, data[IFLA_VLAN_EGRESS_QOS], rem) अणु
			m = nla_data(attr);
			err = vlan_dev_set_egress_priority(dev, m->from, m->to);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vlan_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);
	काष्ठा net_device *real_dev;
	अचिन्हित पूर्णांक max_mtu;
	__be16 proto;
	पूर्णांक err;

	अगर (!data[IFLA_VLAN_ID]) अणु
		NL_SET_ERR_MSG_MOD(extack, "VLAN id not specified");
		वापस -EINVAL;
	पूर्ण

	अगर (!tb[IFLA_LINK]) अणु
		NL_SET_ERR_MSG_MOD(extack, "link not specified");
		वापस -EINVAL;
	पूर्ण

	real_dev = __dev_get_by_index(src_net, nla_get_u32(tb[IFLA_LINK]));
	अगर (!real_dev) अणु
		NL_SET_ERR_MSG_MOD(extack, "link does not exist");
		वापस -ENODEV;
	पूर्ण

	अगर (data[IFLA_VLAN_PROTOCOL])
		proto = nla_get_be16(data[IFLA_VLAN_PROTOCOL]);
	अन्यथा
		proto = htons(ETH_P_8021Q);

	vlan->vlan_proto = proto;
	vlan->vlan_id	 = nla_get_u16(data[IFLA_VLAN_ID]);
	vlan->real_dev	 = real_dev;
	dev->priv_flags |= (real_dev->priv_flags & IFF_XMIT_DST_RELEASE);
	vlan->flags	 = VLAN_FLAG_REORDER_HDR;

	err = vlan_check_real_dev(real_dev, vlan->vlan_proto, vlan->vlan_id,
				  extack);
	अगर (err < 0)
		वापस err;

	max_mtu = netअगर_reduces_vlan_mtu(real_dev) ? real_dev->mtu - VLAN_HLEN :
						     real_dev->mtu;
	अगर (!tb[IFLA_MTU])
		dev->mtu = max_mtu;
	अन्यथा अगर (dev->mtu > max_mtu)
		वापस -EINVAL;

	err = vlan_changelink(dev, tb, data, extack);
	अगर (!err)
		err = रेजिस्टर_vlan_dev(dev, extack);
	अगर (err)
		vlan_dev_uninit(dev);
	वापस err;
पूर्ण

अटल अंतरभूत माप_प्रकार vlan_qos_map_size(अचिन्हित पूर्णांक n)
अणु
	अगर (n == 0)
		वापस 0;
	/* IFLA_VLAN_अणुEGRESS,INGRESSपूर्ण_QOS + n * IFLA_VLAN_QOS_MAPPING */
	वापस nla_total_size(माप(काष्ठा nlattr)) +
	       nla_total_size(माप(काष्ठा अगरla_vlan_qos_mapping)) * n;
पूर्ण

अटल माप_प्रकार vlan_get_size(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);

	वापस nla_total_size(2) +	/* IFLA_VLAN_PROTOCOL */
	       nla_total_size(2) +	/* IFLA_VLAN_ID */
	       nla_total_size(माप(काष्ठा अगरla_vlan_flags)) + /* IFLA_VLAN_FLAGS */
	       vlan_qos_map_size(vlan->nr_ingress_mappings) +
	       vlan_qos_map_size(vlan->nr_egress_mappings);
पूर्ण

अटल पूर्णांक vlan_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);
	काष्ठा vlan_priority_tci_mapping *pm;
	काष्ठा अगरla_vlan_flags f;
	काष्ठा अगरla_vlan_qos_mapping m;
	काष्ठा nlattr *nest;
	अचिन्हित पूर्णांक i;

	अगर (nla_put_be16(skb, IFLA_VLAN_PROTOCOL, vlan->vlan_proto) ||
	    nla_put_u16(skb, IFLA_VLAN_ID, vlan->vlan_id))
		जाओ nla_put_failure;
	अगर (vlan->flags) अणु
		f.flags = vlan->flags;
		f.mask  = ~0;
		अगर (nla_put(skb, IFLA_VLAN_FLAGS, माप(f), &f))
			जाओ nla_put_failure;
	पूर्ण
	अगर (vlan->nr_ingress_mappings) अणु
		nest = nla_nest_start_noflag(skb, IFLA_VLAN_INGRESS_QOS);
		अगर (nest == शून्य)
			जाओ nla_put_failure;

		क्रम (i = 0; i < ARRAY_SIZE(vlan->ingress_priority_map); i++) अणु
			अगर (!vlan->ingress_priority_map[i])
				जारी;

			m.from = i;
			m.to   = vlan->ingress_priority_map[i];
			अगर (nla_put(skb, IFLA_VLAN_QOS_MAPPING,
				    माप(m), &m))
				जाओ nla_put_failure;
		पूर्ण
		nla_nest_end(skb, nest);
	पूर्ण

	अगर (vlan->nr_egress_mappings) अणु
		nest = nla_nest_start_noflag(skb, IFLA_VLAN_EGRESS_QOS);
		अगर (nest == शून्य)
			जाओ nla_put_failure;

		क्रम (i = 0; i < ARRAY_SIZE(vlan->egress_priority_map); i++) अणु
			क्रम (pm = vlan->egress_priority_map[i]; pm;
			     pm = pm->next) अणु
				अगर (!pm->vlan_qos)
					जारी;

				m.from = pm->priority;
				m.to   = (pm->vlan_qos >> 13) & 0x7;
				अगर (nla_put(skb, IFLA_VLAN_QOS_MAPPING,
					    माप(m), &m))
					जाओ nla_put_failure;
			पूर्ण
		पूर्ण
		nla_nest_end(skb, nest);
	पूर्ण
	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल काष्ठा net *vlan_get_link_net(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा net_device *real_dev = vlan_dev_priv(dev)->real_dev;

	वापस dev_net(real_dev);
पूर्ण

काष्ठा rtnl_link_ops vlan_link_ops __पढ़ो_mostly = अणु
	.kind		= "vlan",
	.maxtype	= IFLA_VLAN_MAX,
	.policy		= vlan_policy,
	.priv_size	= माप(काष्ठा vlan_dev_priv),
	.setup		= vlan_setup,
	.validate	= vlan_validate,
	.newlink	= vlan_newlink,
	.changelink	= vlan_changelink,
	.dellink	= unरेजिस्टर_vlan_dev,
	.get_size	= vlan_get_size,
	.fill_info	= vlan_fill_info,
	.get_link_net	= vlan_get_link_net,
पूर्ण;

पूर्णांक __init vlan_netlink_init(व्योम)
अणु
	वापस rtnl_link_रेजिस्टर(&vlan_link_ops);
पूर्ण

व्योम __निकास vlan_netlink_fini(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&vlan_link_ops);
पूर्ण

MODULE_ALIAS_RTNL_LINK("vlan");
