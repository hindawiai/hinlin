<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * File: pn_netlink.c
 *
 * Phonet netlink पूर्णांकerface
 *
 * Copyright (C) 2008 Nokia Corporation.
 *
 * Authors: Sakari Ailus <sakari.ailus@nokia.com>
 *          Remi Denis-Courmont
 */

#समावेश <linux/kernel.h>
#समावेश <linux/netlink.h>
#समावेश <linux/phonet.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <net/phonet/pn_dev.h>

/* Device address handling */

अटल पूर्णांक fill_addr(काष्ठा sk_buff *skb, काष्ठा net_device *dev, u8 addr,
		     u32 portid, u32 seq, पूर्णांक event);

व्योम phonet_address_notअगरy(पूर्णांक event, काष्ठा net_device *dev, u8 addr)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOBUFS;

	skb = nlmsg_new(NLMSG_ALIGN(माप(काष्ठा अगरaddrmsg)) +
			nla_total_size(1), GFP_KERNEL);
	अगर (skb == शून्य)
		जाओ errout;
	err = fill_addr(skb, dev, addr, 0, 0, event);
	अगर (err < 0) अणु
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण
	rtnl_notअगरy(skb, dev_net(dev), 0,
		    RTNLGRP_PHONET_IFADDR, शून्य, GFP_KERNEL);
	वापस;
errout:
	rtnl_set_sk_err(dev_net(dev), RTNLGRP_PHONET_IFADDR, err);
पूर्ण

अटल स्थिर काष्ठा nla_policy अगरa_phonet_policy[IFA_MAX+1] = अणु
	[IFA_LOCAL] = अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल पूर्णांक addr_करोit(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlattr *tb[IFA_MAX+1];
	काष्ठा net_device *dev;
	काष्ठा अगरaddrmsg *अगरm;
	पूर्णांक err;
	u8 pnaddr;

	अगर (!netlink_capable(skb, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!netlink_capable(skb, CAP_SYS_ADMIN))
		वापस -EPERM;

	ASSERT_RTNL();

	err = nlmsg_parse_deprecated(nlh, माप(*अगरm), tb, IFA_MAX,
				     अगरa_phonet_policy, extack);
	अगर (err < 0)
		वापस err;

	अगरm = nlmsg_data(nlh);
	अगर (tb[IFA_LOCAL] == शून्य)
		वापस -EINVAL;
	pnaddr = nla_get_u8(tb[IFA_LOCAL]);
	अगर (pnaddr & 3)
		/* Phonet addresses only have 6 high-order bits */
		वापस -EINVAL;

	dev = __dev_get_by_index(net, अगरm->अगरa_index);
	अगर (dev == शून्य)
		वापस -ENODEV;

	अगर (nlh->nlmsg_type == RTM_NEWADDR)
		err = phonet_address_add(dev, pnaddr);
	अन्यथा
		err = phonet_address_del(dev, pnaddr);
	अगर (!err)
		phonet_address_notअगरy(nlh->nlmsg_type, dev, pnaddr);
	वापस err;
पूर्ण

अटल पूर्णांक fill_addr(काष्ठा sk_buff *skb, काष्ठा net_device *dev, u8 addr,
			u32 portid, u32 seq, पूर्णांक event)
अणु
	काष्ठा अगरaddrmsg *अगरm;
	काष्ठा nlmsghdr *nlh;

	nlh = nlmsg_put(skb, portid, seq, event, माप(*अगरm), 0);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	अगरm = nlmsg_data(nlh);
	अगरm->अगरa_family = AF_PHONET;
	अगरm->अगरa_prefixlen = 0;
	अगरm->अगरa_flags = IFA_F_PERMANENT;
	अगरm->अगरa_scope = RT_SCOPE_LINK;
	अगरm->अगरa_index = dev->अगरindex;
	अगर (nla_put_u8(skb, IFA_LOCAL, addr))
		जाओ nla_put_failure;
	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक getaddr_dumpit(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा phonet_device_list *pndevs;
	काष्ठा phonet_device *pnd;
	पूर्णांक dev_idx = 0, dev_start_idx = cb->args[0];
	पूर्णांक addr_idx = 0, addr_start_idx = cb->args[1];

	pndevs = phonet_device_list(sock_net(skb->sk));
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(pnd, &pndevs->list, list) अणु
		u8 addr;

		अगर (dev_idx > dev_start_idx)
			addr_start_idx = 0;
		अगर (dev_idx++ < dev_start_idx)
			जारी;

		addr_idx = 0;
		क्रम_each_set_bit(addr, pnd->addrs, 64) अणु
			अगर (addr_idx++ < addr_start_idx)
				जारी;

			अगर (fill_addr(skb, pnd->netdev, addr << 2,
					 NETLINK_CB(cb->skb).portid,
					cb->nlh->nlmsg_seq, RTM_NEWADDR) < 0)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	rcu_पढ़ो_unlock();
	cb->args[0] = dev_idx;
	cb->args[1] = addr_idx;

	वापस skb->len;
पूर्ण

/* Routes handling */

अटल पूर्णांक fill_route(काष्ठा sk_buff *skb, काष्ठा net_device *dev, u8 dst,
			u32 portid, u32 seq, पूर्णांक event)
अणु
	काष्ठा rपंचांगsg *rपंचांग;
	काष्ठा nlmsghdr *nlh;

	nlh = nlmsg_put(skb, portid, seq, event, माप(*rपंचांग), 0);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	rपंचांग = nlmsg_data(nlh);
	rपंचांग->rपंचांग_family = AF_PHONET;
	rपंचांग->rपंचांग_dst_len = 6;
	rपंचांग->rपंचांग_src_len = 0;
	rपंचांग->rपंचांग_tos = 0;
	rपंचांग->rपंचांग_table = RT_TABLE_MAIN;
	rपंचांग->rपंचांग_protocol = RTPROT_STATIC;
	rपंचांग->rपंचांग_scope = RT_SCOPE_UNIVERSE;
	rपंचांग->rपंचांग_type = RTN_UNICAST;
	rपंचांग->rपंचांग_flags = 0;
	अगर (nla_put_u8(skb, RTA_DST, dst) ||
	    nla_put_u32(skb, RTA_OIF, dev->अगरindex))
		जाओ nla_put_failure;
	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

व्योम rपंचांग_phonet_notअगरy(पूर्णांक event, काष्ठा net_device *dev, u8 dst)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOBUFS;

	skb = nlmsg_new(NLMSG_ALIGN(माप(काष्ठा अगरaddrmsg)) +
			nla_total_size(1) + nla_total_size(4), GFP_KERNEL);
	अगर (skb == शून्य)
		जाओ errout;
	err = fill_route(skb, dev, dst, 0, 0, event);
	अगर (err < 0) अणु
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण
	rtnl_notअगरy(skb, dev_net(dev), 0,
			  RTNLGRP_PHONET_ROUTE, शून्य, GFP_KERNEL);
	वापस;
errout:
	rtnl_set_sk_err(dev_net(dev), RTNLGRP_PHONET_ROUTE, err);
पूर्ण

अटल स्थिर काष्ठा nla_policy rपंचांग_phonet_policy[RTA_MAX+1] = अणु
	[RTA_DST] = अणु .type = NLA_U8 पूर्ण,
	[RTA_OIF] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक route_करोit(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlattr *tb[RTA_MAX+1];
	काष्ठा net_device *dev;
	काष्ठा rपंचांगsg *rपंचांग;
	पूर्णांक err;
	u8 dst;

	अगर (!netlink_capable(skb, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!netlink_capable(skb, CAP_SYS_ADMIN))
		वापस -EPERM;

	ASSERT_RTNL();

	err = nlmsg_parse_deprecated(nlh, माप(*rपंचांग), tb, RTA_MAX,
				     rपंचांग_phonet_policy, extack);
	अगर (err < 0)
		वापस err;

	rपंचांग = nlmsg_data(nlh);
	अगर (rपंचांग->rपंचांग_table != RT_TABLE_MAIN || rपंचांग->rपंचांग_type != RTN_UNICAST)
		वापस -EINVAL;
	अगर (tb[RTA_DST] == शून्य || tb[RTA_OIF] == शून्य)
		वापस -EINVAL;
	dst = nla_get_u8(tb[RTA_DST]);
	अगर (dst & 3) /* Phonet addresses only have 6 high-order bits */
		वापस -EINVAL;

	dev = __dev_get_by_index(net, nla_get_u32(tb[RTA_OIF]));
	अगर (dev == शून्य)
		वापस -ENODEV;

	अगर (nlh->nlmsg_type == RTM_NEWROUTE)
		err = phonet_route_add(dev, dst);
	अन्यथा
		err = phonet_route_del(dev, dst);
	अगर (!err)
		rपंचांग_phonet_notअगरy(nlh->nlmsg_type, dev, dst);
	वापस err;
पूर्ण

अटल पूर्णांक route_dumpit(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	u8 addr;

	rcu_पढ़ो_lock();
	क्रम (addr = cb->args[0]; addr < 64; addr++) अणु
		काष्ठा net_device *dev = phonet_route_get_rcu(net, addr << 2);

		अगर (!dev)
			जारी;

		अगर (fill_route(skb, dev, addr << 2, NETLINK_CB(cb->skb).portid,
			       cb->nlh->nlmsg_seq, RTM_NEWROUTE) < 0)
			जाओ out;
	पूर्ण

out:
	rcu_पढ़ो_unlock();
	cb->args[0] = addr;

	वापस skb->len;
पूर्ण

पूर्णांक __init phonet_netlink_रेजिस्टर(व्योम)
अणु
	पूर्णांक err = rtnl_रेजिस्टर_module(THIS_MODULE, PF_PHONET, RTM_NEWADDR,
				       addr_करोit, शून्य, 0);
	अगर (err)
		वापस err;

	/* Further rtnl_रेजिस्टर_module() cannot fail */
	rtnl_रेजिस्टर_module(THIS_MODULE, PF_PHONET, RTM_DELADDR,
			     addr_करोit, शून्य, 0);
	rtnl_रेजिस्टर_module(THIS_MODULE, PF_PHONET, RTM_GETADDR,
			     शून्य, getaddr_dumpit, 0);
	rtnl_रेजिस्टर_module(THIS_MODULE, PF_PHONET, RTM_NEWROUTE,
			     route_करोit, शून्य, 0);
	rtnl_रेजिस्टर_module(THIS_MODULE, PF_PHONET, RTM_DELROUTE,
			     route_करोit, शून्य, 0);
	rtnl_रेजिस्टर_module(THIS_MODULE, PF_PHONET, RTM_GETROUTE,
			     शून्य, route_dumpit, 0);
	वापस 0;
पूर्ण
