<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2011-2014 Autronica Fire and Security AS
 *
 * Author(s):
 *	2011-2014 Arvid Brodin, arvid.brodin@alten.se
 *
 * Routines क्रम handling Netlink messages क्रम HSR and PRP.
 */

#समावेश "hsr_netlink.h"
#समावेश <linux/kernel.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/genetlink.h>
#समावेश "hsr_main.h"
#समावेश "hsr_device.h"
#समावेश "hsr_framereg.h"

अटल स्थिर काष्ठा nla_policy hsr_policy[IFLA_HSR_MAX + 1] = अणु
	[IFLA_HSR_SLAVE1]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_HSR_SLAVE2]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_HSR_MULTICAST_SPEC]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_HSR_VERSION]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_HSR_SUPERVISION_ADDR]	= अणु .len = ETH_ALEN पूर्ण,
	[IFLA_HSR_SEQ_NR]		= अणु .type = NLA_U16 पूर्ण,
	[IFLA_HSR_PROTOCOL]		= अणु .type = NLA_U8 पूर्ण,
पूर्ण;

/* Here, it seems a netdevice has alपढ़ोy been allocated क्रम us, and the
 * hsr_dev_setup routine has been executed. Nice!
 */
अटल पूर्णांक hsr_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
		       काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
		       काष्ठा netlink_ext_ack *extack)
अणु
	क्रमागत hsr_version proto_version;
	अचिन्हित अक्षर multicast_spec;
	u8 proto = HSR_PROTOCOL_HSR;
	काष्ठा net_device *link[2];

	अगर (!data) अणु
		NL_SET_ERR_MSG_MOD(extack, "No slave devices specified");
		वापस -EINVAL;
	पूर्ण
	अगर (!data[IFLA_HSR_SLAVE1]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Slave1 device not specified");
		वापस -EINVAL;
	पूर्ण
	link[0] = __dev_get_by_index(src_net,
				     nla_get_u32(data[IFLA_HSR_SLAVE1]));
	अगर (!link[0]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Slave1 does not exist");
		वापस -EINVAL;
	पूर्ण
	अगर (!data[IFLA_HSR_SLAVE2]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Slave2 device not specified");
		वापस -EINVAL;
	पूर्ण
	link[1] = __dev_get_by_index(src_net,
				     nla_get_u32(data[IFLA_HSR_SLAVE2]));
	अगर (!link[1]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Slave2 does not exist");
		वापस -EINVAL;
	पूर्ण

	अगर (link[0] == link[1]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Slave1 and Slave2 are same");
		वापस -EINVAL;
	पूर्ण

	अगर (!data[IFLA_HSR_MULTICAST_SPEC])
		multicast_spec = 0;
	अन्यथा
		multicast_spec = nla_get_u8(data[IFLA_HSR_MULTICAST_SPEC]);

	अगर (data[IFLA_HSR_PROTOCOL])
		proto = nla_get_u8(data[IFLA_HSR_PROTOCOL]);

	अगर (proto >= HSR_PROTOCOL_MAX) अणु
		NL_SET_ERR_MSG_MOD(extack, "Unsupported protocol");
		वापस -EINVAL;
	पूर्ण

	अगर (!data[IFLA_HSR_VERSION]) अणु
		proto_version = HSR_V0;
	पूर्ण अन्यथा अणु
		अगर (proto == HSR_PROTOCOL_PRP) अणु
			NL_SET_ERR_MSG_MOD(extack, "PRP version unsupported");
			वापस -EINVAL;
		पूर्ण

		proto_version = nla_get_u8(data[IFLA_HSR_VERSION]);
		अगर (proto_version > HSR_V1) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Only HSR version 0/1 supported");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (proto == HSR_PROTOCOL_PRP)
		proto_version = PRP_V1;

	वापस hsr_dev_finalize(dev, link, multicast_spec, proto_version, extack);
पूर्ण

अटल व्योम hsr_dellink(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	काष्ठा hsr_priv *hsr = netdev_priv(dev);

	del_समयr_sync(&hsr->prune_समयr);
	del_समयr_sync(&hsr->announce_समयr);

	hsr_debugfs_term(hsr);
	hsr_del_ports(hsr);

	hsr_del_self_node(hsr);
	hsr_del_nodes(&hsr->node_db);

	unरेजिस्टर_netdevice_queue(dev, head);
पूर्ण

अटल पूर्णांक hsr_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा hsr_priv *hsr = netdev_priv(dev);
	u8 proto = HSR_PROTOCOL_HSR;
	काष्ठा hsr_port *port;

	port = hsr_port_get_hsr(hsr, HSR_PT_SLAVE_A);
	अगर (port) अणु
		अगर (nla_put_u32(skb, IFLA_HSR_SLAVE1, port->dev->अगरindex))
			जाओ nla_put_failure;
	पूर्ण

	port = hsr_port_get_hsr(hsr, HSR_PT_SLAVE_B);
	अगर (port) अणु
		अगर (nla_put_u32(skb, IFLA_HSR_SLAVE2, port->dev->अगरindex))
			जाओ nla_put_failure;
	पूर्ण

	अगर (nla_put(skb, IFLA_HSR_SUPERVISION_ADDR, ETH_ALEN,
		    hsr->sup_multicast_addr) ||
	    nla_put_u16(skb, IFLA_HSR_SEQ_NR, hsr->sequence_nr))
		जाओ nla_put_failure;
	अगर (hsr->prot_version == PRP_V1)
		proto = HSR_PROTOCOL_PRP;
	अगर (nla_put_u8(skb, IFLA_HSR_PROTOCOL, proto))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल काष्ठा rtnl_link_ops hsr_link_ops __पढ़ो_mostly = अणु
	.kind		= "hsr",
	.maxtype	= IFLA_HSR_MAX,
	.policy		= hsr_policy,
	.priv_size	= माप(काष्ठा hsr_priv),
	.setup		= hsr_dev_setup,
	.newlink	= hsr_newlink,
	.dellink	= hsr_dellink,
	.fill_info	= hsr_fill_info,
पूर्ण;

/* attribute policy */
अटल स्थिर काष्ठा nla_policy hsr_genl_policy[HSR_A_MAX + 1] = अणु
	[HSR_A_NODE_ADDR] = अणु .len = ETH_ALEN पूर्ण,
	[HSR_A_NODE_ADDR_B] = अणु .len = ETH_ALEN पूर्ण,
	[HSR_A_IFINDEX] = अणु .type = NLA_U32 पूर्ण,
	[HSR_A_IF1_AGE] = अणु .type = NLA_U32 पूर्ण,
	[HSR_A_IF2_AGE] = अणु .type = NLA_U32 पूर्ण,
	[HSR_A_IF1_SEQ] = अणु .type = NLA_U16 पूर्ण,
	[HSR_A_IF2_SEQ] = अणु .type = NLA_U16 पूर्ण,
पूर्ण;

अटल काष्ठा genl_family hsr_genl_family;

अटल स्थिर काष्ठा genl_multicast_group hsr_mcgrps[] = अणु
	अणु .name = "hsr-network", पूर्ण,
पूर्ण;

/* This is called अगर क्रम some node with MAC address addr, we only get frames
 * over one of the slave पूर्णांकerfaces. This would indicate an खोलो network ring
 * (i.e. a link has failed somewhere).
 */
व्योम hsr_nl_ringerror(काष्ठा hsr_priv *hsr, अचिन्हित अक्षर addr[ETH_ALEN],
		      काष्ठा hsr_port *port)
अणु
	काष्ठा sk_buff *skb;
	व्योम *msg_head;
	काष्ठा hsr_port *master;
	पूर्णांक res;

	skb = genlmsg_new(NLMSG_GOODSIZE, GFP_ATOMIC);
	अगर (!skb)
		जाओ fail;

	msg_head = genlmsg_put(skb, 0, 0, &hsr_genl_family, 0,
			       HSR_C_RING_ERROR);
	अगर (!msg_head)
		जाओ nla_put_failure;

	res = nla_put(skb, HSR_A_NODE_ADDR, ETH_ALEN, addr);
	अगर (res < 0)
		जाओ nla_put_failure;

	res = nla_put_u32(skb, HSR_A_IFINDEX, port->dev->अगरindex);
	अगर (res < 0)
		जाओ nla_put_failure;

	genlmsg_end(skb, msg_head);
	genlmsg_multicast(&hsr_genl_family, skb, 0, 0, GFP_ATOMIC);

	वापस;

nla_put_failure:
	kमुक्त_skb(skb);

fail:
	rcu_पढ़ो_lock();
	master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
	netdev_warn(master->dev, "Could not send HSR ring error message\n");
	rcu_पढ़ो_unlock();
पूर्ण

/* This is called when we haven't heard from the node with MAC address addr क्रम
 * some समय (just beक्रमe the node is हटाओd from the node table/list).
 */
व्योम hsr_nl_nodeकरोwn(काष्ठा hsr_priv *hsr, अचिन्हित अक्षर addr[ETH_ALEN])
अणु
	काष्ठा sk_buff *skb;
	व्योम *msg_head;
	काष्ठा hsr_port *master;
	पूर्णांक res;

	skb = genlmsg_new(NLMSG_GOODSIZE, GFP_ATOMIC);
	अगर (!skb)
		जाओ fail;

	msg_head = genlmsg_put(skb, 0, 0, &hsr_genl_family, 0, HSR_C_NODE_DOWN);
	अगर (!msg_head)
		जाओ nla_put_failure;

	res = nla_put(skb, HSR_A_NODE_ADDR, ETH_ALEN, addr);
	अगर (res < 0)
		जाओ nla_put_failure;

	genlmsg_end(skb, msg_head);
	genlmsg_multicast(&hsr_genl_family, skb, 0, 0, GFP_ATOMIC);

	वापस;

nla_put_failure:
	kमुक्त_skb(skb);

fail:
	rcu_पढ़ो_lock();
	master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
	netdev_warn(master->dev, "Could not send HSR node down\n");
	rcu_पढ़ो_unlock();
पूर्ण

/* HSR_C_GET_NODE_STATUS lets userspace query the पूर्णांकernal HSR node table
 * about the status of a specअगरic node in the network, defined by its MAC
 * address.
 *
 * Input: hsr अगरindex, node mac address
 * Output: hsr अगरindex, node mac address (copied from request),
 *	   age of latest frame from node over slave 1, slave 2 [ms]
 */
अटल पूर्णांक hsr_get_node_status(काष्ठा sk_buff *skb_in, काष्ठा genl_info *info)
अणु
	/* For receiving */
	काष्ठा nlattr *na;
	काष्ठा net_device *hsr_dev;

	/* For sending */
	काष्ठा sk_buff *skb_out;
	व्योम *msg_head;
	काष्ठा hsr_priv *hsr;
	काष्ठा hsr_port *port;
	अचिन्हित अक्षर hsr_node_addr_b[ETH_ALEN];
	पूर्णांक hsr_node_अगर1_age;
	u16 hsr_node_अगर1_seq;
	पूर्णांक hsr_node_अगर2_age;
	u16 hsr_node_अगर2_seq;
	पूर्णांक addr_b_अगरindex;
	पूर्णांक res;

	अगर (!info)
		जाओ invalid;

	na = info->attrs[HSR_A_IFINDEX];
	अगर (!na)
		जाओ invalid;
	na = info->attrs[HSR_A_NODE_ADDR];
	अगर (!na)
		जाओ invalid;

	rcu_पढ़ो_lock();
	hsr_dev = dev_get_by_index_rcu(genl_info_net(info),
				       nla_get_u32(info->attrs[HSR_A_IFINDEX]));
	अगर (!hsr_dev)
		जाओ rcu_unlock;
	अगर (!is_hsr_master(hsr_dev))
		जाओ rcu_unlock;

	/* Send reply */
	skb_out = genlmsg_new(NLMSG_GOODSIZE, GFP_ATOMIC);
	अगर (!skb_out) अणु
		res = -ENOMEM;
		जाओ fail;
	पूर्ण

	msg_head = genlmsg_put(skb_out, NETLINK_CB(skb_in).portid,
			       info->snd_seq, &hsr_genl_family, 0,
			       HSR_C_SET_NODE_STATUS);
	अगर (!msg_head) अणु
		res = -ENOMEM;
		जाओ nla_put_failure;
	पूर्ण

	res = nla_put_u32(skb_out, HSR_A_IFINDEX, hsr_dev->अगरindex);
	अगर (res < 0)
		जाओ nla_put_failure;

	hsr = netdev_priv(hsr_dev);
	res = hsr_get_node_data(hsr,
				(अचिन्हित अक्षर *)
				nla_data(info->attrs[HSR_A_NODE_ADDR]),
					 hsr_node_addr_b,
					 &addr_b_अगरindex,
					 &hsr_node_अगर1_age,
					 &hsr_node_अगर1_seq,
					 &hsr_node_अगर2_age,
					 &hsr_node_अगर2_seq);
	अगर (res < 0)
		जाओ nla_put_failure;

	res = nla_put(skb_out, HSR_A_NODE_ADDR, ETH_ALEN,
		      nla_data(info->attrs[HSR_A_NODE_ADDR]));
	अगर (res < 0)
		जाओ nla_put_failure;

	अगर (addr_b_अगरindex > -1) अणु
		res = nla_put(skb_out, HSR_A_NODE_ADDR_B, ETH_ALEN,
			      hsr_node_addr_b);
		अगर (res < 0)
			जाओ nla_put_failure;

		res = nla_put_u32(skb_out, HSR_A_ADDR_B_IFINDEX,
				  addr_b_अगरindex);
		अगर (res < 0)
			जाओ nla_put_failure;
	पूर्ण

	res = nla_put_u32(skb_out, HSR_A_IF1_AGE, hsr_node_अगर1_age);
	अगर (res < 0)
		जाओ nla_put_failure;
	res = nla_put_u16(skb_out, HSR_A_IF1_SEQ, hsr_node_अगर1_seq);
	अगर (res < 0)
		जाओ nla_put_failure;
	port = hsr_port_get_hsr(hsr, HSR_PT_SLAVE_A);
	अगर (port)
		res = nla_put_u32(skb_out, HSR_A_IF1_IFINDEX,
				  port->dev->अगरindex);
	अगर (res < 0)
		जाओ nla_put_failure;

	res = nla_put_u32(skb_out, HSR_A_IF2_AGE, hsr_node_अगर2_age);
	अगर (res < 0)
		जाओ nla_put_failure;
	res = nla_put_u16(skb_out, HSR_A_IF2_SEQ, hsr_node_अगर2_seq);
	अगर (res < 0)
		जाओ nla_put_failure;
	port = hsr_port_get_hsr(hsr, HSR_PT_SLAVE_B);
	अगर (port)
		res = nla_put_u32(skb_out, HSR_A_IF2_IFINDEX,
				  port->dev->अगरindex);
	अगर (res < 0)
		जाओ nla_put_failure;

	rcu_पढ़ो_unlock();

	genlmsg_end(skb_out, msg_head);
	genlmsg_unicast(genl_info_net(info), skb_out, info->snd_portid);

	वापस 0;

rcu_unlock:
	rcu_पढ़ो_unlock();
invalid:
	netlink_ack(skb_in, nlmsg_hdr(skb_in), -EINVAL, शून्य);
	वापस 0;

nla_put_failure:
	kमुक्त_skb(skb_out);
	/* Fall through */

fail:
	rcu_पढ़ो_unlock();
	वापस res;
पूर्ण

/* Get a list of MacAddressA of all nodes known to this node (including self).
 */
अटल पूर्णांक hsr_get_node_list(काष्ठा sk_buff *skb_in, काष्ठा genl_info *info)
अणु
	अचिन्हित अक्षर addr[ETH_ALEN];
	काष्ठा net_device *hsr_dev;
	काष्ठा sk_buff *skb_out;
	काष्ठा hsr_priv *hsr;
	bool restart = false;
	काष्ठा nlattr *na;
	व्योम *pos = शून्य;
	व्योम *msg_head;
	पूर्णांक res;

	अगर (!info)
		जाओ invalid;

	na = info->attrs[HSR_A_IFINDEX];
	अगर (!na)
		जाओ invalid;

	rcu_पढ़ो_lock();
	hsr_dev = dev_get_by_index_rcu(genl_info_net(info),
				       nla_get_u32(info->attrs[HSR_A_IFINDEX]));
	अगर (!hsr_dev)
		जाओ rcu_unlock;
	अगर (!is_hsr_master(hsr_dev))
		जाओ rcu_unlock;

restart:
	/* Send reply */
	skb_out = genlmsg_new(GENLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	अगर (!skb_out) अणु
		res = -ENOMEM;
		जाओ fail;
	पूर्ण

	msg_head = genlmsg_put(skb_out, NETLINK_CB(skb_in).portid,
			       info->snd_seq, &hsr_genl_family, 0,
			       HSR_C_SET_NODE_LIST);
	अगर (!msg_head) अणु
		res = -ENOMEM;
		जाओ nla_put_failure;
	पूर्ण

	अगर (!restart) अणु
		res = nla_put_u32(skb_out, HSR_A_IFINDEX, hsr_dev->अगरindex);
		अगर (res < 0)
			जाओ nla_put_failure;
	पूर्ण

	hsr = netdev_priv(hsr_dev);

	अगर (!pos)
		pos = hsr_get_next_node(hsr, शून्य, addr);
	जबतक (pos) अणु
		res = nla_put(skb_out, HSR_A_NODE_ADDR, ETH_ALEN, addr);
		अगर (res < 0) अणु
			अगर (res == -EMSGSIZE) अणु
				genlmsg_end(skb_out, msg_head);
				genlmsg_unicast(genl_info_net(info), skb_out,
						info->snd_portid);
				restart = true;
				जाओ restart;
			पूर्ण
			जाओ nla_put_failure;
		पूर्ण
		pos = hsr_get_next_node(hsr, pos, addr);
	पूर्ण
	rcu_पढ़ो_unlock();

	genlmsg_end(skb_out, msg_head);
	genlmsg_unicast(genl_info_net(info), skb_out, info->snd_portid);

	वापस 0;

rcu_unlock:
	rcu_पढ़ो_unlock();
invalid:
	netlink_ack(skb_in, nlmsg_hdr(skb_in), -EINVAL, शून्य);
	वापस 0;

nla_put_failure:
	nlmsg_मुक्त(skb_out);
	/* Fall through */

fail:
	rcu_पढ़ो_unlock();
	वापस res;
पूर्ण

अटल स्थिर काष्ठा genl_small_ops hsr_ops[] = अणु
	अणु
		.cmd = HSR_C_GET_NODE_STATUS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = 0,
		.करोit = hsr_get_node_status,
		.dumpit = शून्य,
	पूर्ण,
	अणु
		.cmd = HSR_C_GET_NODE_LIST,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = 0,
		.करोit = hsr_get_node_list,
		.dumpit = शून्य,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family hsr_genl_family __ro_after_init = अणु
	.hdrsize = 0,
	.name = "HSR",
	.version = 1,
	.maxattr = HSR_A_MAX,
	.policy = hsr_genl_policy,
	.netnsok = true,
	.module = THIS_MODULE,
	.small_ops = hsr_ops,
	.n_small_ops = ARRAY_SIZE(hsr_ops),
	.mcgrps = hsr_mcgrps,
	.n_mcgrps = ARRAY_SIZE(hsr_mcgrps),
पूर्ण;

पूर्णांक __init hsr_netlink_init(व्योम)
अणु
	पूर्णांक rc;

	rc = rtnl_link_रेजिस्टर(&hsr_link_ops);
	अगर (rc)
		जाओ fail_rtnl_link_रेजिस्टर;

	rc = genl_रेजिस्टर_family(&hsr_genl_family);
	अगर (rc)
		जाओ fail_genl_रेजिस्टर_family;

	hsr_debugfs_create_root();
	वापस 0;

fail_genl_रेजिस्टर_family:
	rtnl_link_unरेजिस्टर(&hsr_link_ops);
fail_rtnl_link_रेजिस्टर:

	वापस rc;
पूर्ण

व्योम __निकास hsr_netlink_निकास(व्योम)
अणु
	genl_unरेजिस्टर_family(&hsr_genl_family);
	rtnl_link_unरेजिस्टर(&hsr_link_ops);
पूर्ण

MODULE_ALIAS_RTNL_LINK("hsr");
