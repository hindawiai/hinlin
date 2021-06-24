<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DECnet       An implementation of the DECnet protocol suite क्रम the LINUX
 *              operating प्रणाली.  DECnet is implemented using the  BSD Socket
 *              पूर्णांकerface as the means of communication with the user level.
 *
 *              DECnet Routing Message Grabulator
 *
 *              (C) 2000 ChyGwyn Limited  -  https://www.chygwyn.com/
 *
 * Author:      Steven Whitehouse <steve@chygwyn.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/spinlock.h>
#समावेश <net/netlink.h>
#समावेश <linux/netfilter_decnet.h>

#समावेश <net/sock.h>
#समावेश <net/flow.h>
#समावेश <net/dn.h>
#समावेश <net/dn_route.h>

अटल काष्ठा sock *dnrmg = शून्य;


अटल काष्ठा sk_buff *dnrmg_build_message(काष्ठा sk_buff *rt_skb, पूर्णांक *errp)
अणु
	काष्ठा sk_buff *skb = शून्य;
	माप_प्रकार size;
	sk_buff_data_t old_tail;
	काष्ठा nlmsghdr *nlh;
	अचिन्हित अक्षर *ptr;
	काष्ठा nf_dn_rपंचांगsg *rपंचांग;

	size = NLMSG_ALIGN(rt_skb->len) +
	       NLMSG_ALIGN(माप(काष्ठा nf_dn_rपंचांगsg));
	skb = nlmsg_new(size, GFP_ATOMIC);
	अगर (!skb) अणु
		*errp = -ENOMEM;
		वापस शून्य;
	पूर्ण
	old_tail = skb->tail;
	nlh = nlmsg_put(skb, 0, 0, 0, size, 0);
	अगर (!nlh) अणु
		kमुक्त_skb(skb);
		*errp = -ENOMEM;
		वापस शून्य;
	पूर्ण
	rपंचांग = (काष्ठा nf_dn_rपंचांगsg *)nlmsg_data(nlh);
	rपंचांग->nfdn_अगरindex = rt_skb->dev->अगरindex;
	ptr = NFDN_RTMSG(rपंचांग);
	skb_copy_from_linear_data(rt_skb, ptr, rt_skb->len);
	nlh->nlmsg_len = skb->tail - old_tail;
	वापस skb;
पूर्ण

अटल व्योम dnrmg_send_peer(काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *skb2;
	पूर्णांक status = 0;
	पूर्णांक group = 0;
	अचिन्हित अक्षर flags = *skb->data;

	चयन (flags & DN_RT_CNTL_MSK) अणु
	हाल DN_RT_PKT_L1RT:
		group = DNRNG_NLGRP_L1;
		अवरोध;
	हाल DN_RT_PKT_L2RT:
		group = DNRNG_NLGRP_L2;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	skb2 = dnrmg_build_message(skb, &status);
	अगर (skb2 == शून्य)
		वापस;
	NETLINK_CB(skb2).dst_group = group;
	netlink_broadcast(dnrmg, skb2, 0, group, GFP_ATOMIC);
पूर्ण


अटल अचिन्हित पूर्णांक dnrmg_hook(व्योम *priv,
			काष्ठा sk_buff *skb,
			स्थिर काष्ठा nf_hook_state *state)
अणु
	dnrmg_send_peer(skb);
	वापस NF_ACCEPT;
पूर्ण


#घोषणा RCV_SKB_FAIL(err) करो अणु netlink_ack(skb, nlh, (err), शून्य); वापस; पूर्ण जबतक (0)

अटल अंतरभूत व्योम dnrmg_receive_user_skb(काष्ठा sk_buff *skb)
अणु
	काष्ठा nlmsghdr *nlh = nlmsg_hdr(skb);

	अगर (skb->len < माप(*nlh) ||
	    nlh->nlmsg_len < माप(*nlh) ||
	    skb->len < nlh->nlmsg_len)
		वापस;

	अगर (!netlink_capable(skb, CAP_NET_ADMIN))
		RCV_SKB_FAIL(-EPERM);

	/* Eventually we might send routing messages too */

	RCV_SKB_FAIL(-EINVAL);
पूर्ण

अटल स्थिर काष्ठा nf_hook_ops dnrmg_ops = अणु
	.hook		= dnrmg_hook,
	.pf		= NFPROTO_DECNET,
	.hooknum	= NF_DN_ROUTE,
	.priority	= NF_DN_PRI_DNRTMSG,
पूर्ण;

अटल पूर्णांक __init dn_rपंचांगsg_init(व्योम)
अणु
	पूर्णांक rv = 0;
	काष्ठा netlink_kernel_cfg cfg = अणु
		.groups	= DNRNG_NLGRP_MAX,
		.input	= dnrmg_receive_user_skb,
	पूर्ण;

	dnrmg = netlink_kernel_create(&init_net, NETLINK_DNRTMSG, &cfg);
	अगर (dnrmg == शून्य) अणु
		prपूर्णांकk(KERN_ERR "dn_rtmsg: Cannot create netlink socket");
		वापस -ENOMEM;
	पूर्ण

	rv = nf_रेजिस्टर_net_hook(&init_net, &dnrmg_ops);
	अगर (rv) अणु
		netlink_kernel_release(dnrmg);
	पूर्ण

	वापस rv;
पूर्ण

अटल व्योम __निकास dn_rपंचांगsg_fini(व्योम)
अणु
	nf_unरेजिस्टर_net_hook(&init_net, &dnrmg_ops);
	netlink_kernel_release(dnrmg);
पूर्ण


MODULE_DESCRIPTION("DECnet Routing Message Grabulator");
MODULE_AUTHOR("Steven Whitehouse <steve@chygwyn.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS_NET_PF_PROTO(PF_NETLINK, NETLINK_DNRTMSG);

module_init(dn_rपंचांगsg_init);
module_निकास(dn_rपंचांगsg_fini);
