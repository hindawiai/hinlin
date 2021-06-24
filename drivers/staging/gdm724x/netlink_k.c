<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2012 GCT Semiconductor, Inc. All rights reserved. */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/netlink.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <net/sock.h>

#समावेश "netlink_k.h"

अटल DEFINE_MUTEX(netlink_mutex);

#घोषणा ND_MAX_GROUP		30
#घोषणा ND_IFINDEX_LEN		माप(पूर्णांक)
#घोषणा ND_NLMSG_SPACE(len)	(NLMSG_SPACE(len) + ND_IFINDEX_LEN)
#घोषणा ND_NLMSG_DATA(nlh)	((व्योम *)((अक्षर *)NLMSG_DATA(nlh) + \
						  ND_IFINDEX_LEN))
#घोषणा ND_NLMSG_S_LEN(len)	(len + ND_IFINDEX_LEN)
#घोषणा ND_NLMSG_R_LEN(nlh)	(nlh->nlmsg_len - ND_IFINDEX_LEN)
#घोषणा ND_NLMSG_IFIDX(nlh)	NLMSG_DATA(nlh)
#घोषणा ND_MAX_MSG_LEN		(1024 * 32)

अटल व्योम (*rcv_cb)(काष्ठा net_device *dev, u16 type, व्योम *msg, पूर्णांक len);

अटल व्योम netlink_rcv_cb(काष्ठा sk_buff *skb)
अणु
	काष्ठा nlmsghdr	*nlh;
	काष्ठा net_device *dev;
	u32 mlen;
	व्योम *msg;
	पूर्णांक अगरindex;

	अगर (!rcv_cb) अणु
		pr_err("nl cb - unregistered\n");
		वापस;
	पूर्ण

	अगर (skb->len < NLMSG_HDRLEN) अणु
		pr_err("nl cb - invalid skb length\n");
		वापस;
	पूर्ण

	nlh = (काष्ठा nlmsghdr *)skb->data;

	अगर (skb->len < nlh->nlmsg_len || nlh->nlmsg_len > ND_MAX_MSG_LEN) अणु
		pr_err("nl cb - invalid length (%d,%d)\n",
		       skb->len, nlh->nlmsg_len);
		वापस;
	पूर्ण

	स_नकल(&अगरindex, ND_NLMSG_IFIDX(nlh), ND_IFINDEX_LEN);
	msg = ND_NLMSG_DATA(nlh);
	mlen = ND_NLMSG_R_LEN(nlh);

	dev = dev_get_by_index(&init_net, अगरindex);
	अगर (dev) अणु
		rcv_cb(dev, nlh->nlmsg_type, msg, mlen);
		dev_put(dev);
	पूर्ण अन्यथा अणु
		pr_err("nl cb - dev (%d) not found\n", अगरindex);
	पूर्ण
पूर्ण

अटल व्योम netlink_rcv(काष्ठा sk_buff *skb)
अणु
	mutex_lock(&netlink_mutex);
	netlink_rcv_cb(skb);
	mutex_unlock(&netlink_mutex);
पूर्ण

काष्ठा sock *netlink_init(पूर्णांक unit,
			  व्योम (*cb)(काष्ठा net_device *dev, u16 type,
				     व्योम *msg, पूर्णांक len))
अणु
	काष्ठा sock *sock;
	काष्ठा netlink_kernel_cfg cfg = अणु
		.input  = netlink_rcv,
	पूर्ण;

	sock = netlink_kernel_create(&init_net, unit, &cfg);

	अगर (sock)
		rcv_cb = cb;

	वापस sock;
पूर्ण

पूर्णांक netlink_send(काष्ठा sock *sock, पूर्णांक group, u16 type, व्योम *msg, पूर्णांक len,
		 काष्ठा net_device *dev)
अणु
	अटल u32 seq;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा nlmsghdr *nlh;
	पूर्णांक ret = 0;

	अगर (group > ND_MAX_GROUP)
		वापस -EINVAL;

	अगर (!netlink_has_listeners(sock, group + 1))
		वापस -ESRCH;

	skb = alloc_skb(NLMSG_SPACE(len), GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOMEM;

	seq++;

	nlh = nlmsg_put(skb, 0, seq, type, len, 0);
	स_नकल(NLMSG_DATA(nlh), msg, len);
	NETLINK_CB(skb).portid = 0;
	NETLINK_CB(skb).dst_group = 0;

	ret = netlink_broadcast(sock, skb, 0, group + 1, GFP_ATOMIC);
	अगर (!ret)
		वापस len;

	अगर (ret != -ESRCH)
		netdev_err(dev, "nl broadcast g=%d, t=%d, l=%d, r=%d\n",
			   group, type, len, ret);
	अन्यथा अगर (netlink_has_listeners(sock, group + 1))
		वापस -EAGAIN;

	वापस ret;
पूर्ण
