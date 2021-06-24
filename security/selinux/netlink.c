<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Netlink event notअगरications क्रम SELinux.
 *
 * Author: James Morris <jmorris@redhat.com>
 *
 * Copyright (C) 2004 Red Hat, Inc., James Morris <jmorris@redhat.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/selinux_netlink.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netlink.h>

#समावेश "security.h"

अटल काष्ठा sock *selnl __ro_after_init;

अटल पूर्णांक selnl_msglen(पूर्णांक msgtype)
अणु
	पूर्णांक ret = 0;

	चयन (msgtype) अणु
	हाल SELNL_MSG_SETENFORCE:
		ret = माप(काष्ठा selnl_msg_setenक्रमce);
		अवरोध;

	हाल SELNL_MSG_POLICYLOAD:
		ret = माप(काष्ठा selnl_msg_policyload);
		अवरोध;

	शेष:
		BUG();
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम selnl_add_payload(काष्ठा nlmsghdr *nlh, पूर्णांक len, पूर्णांक msgtype, व्योम *data)
अणु
	चयन (msgtype) अणु
	हाल SELNL_MSG_SETENFORCE: अणु
		काष्ठा selnl_msg_setenक्रमce *msg = nlmsg_data(nlh);

		स_रखो(msg, 0, len);
		msg->val = *((पूर्णांक *)data);
		अवरोध;
	पूर्ण

	हाल SELNL_MSG_POLICYLOAD: अणु
		काष्ठा selnl_msg_policyload *msg = nlmsg_data(nlh);

		स_रखो(msg, 0, len);
		msg->seqno = *((u32 *)data);
		अवरोध;
	पूर्ण

	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल व्योम selnl_notअगरy(पूर्णांक msgtype, व्योम *data)
अणु
	पूर्णांक len;
	sk_buff_data_t पंचांगp;
	काष्ठा sk_buff *skb;
	काष्ठा nlmsghdr *nlh;

	len = selnl_msglen(msgtype);

	skb = nlmsg_new(len, GFP_USER);
	अगर (!skb)
		जाओ oom;

	पंचांगp = skb->tail;
	nlh = nlmsg_put(skb, 0, 0, msgtype, len, 0);
	अगर (!nlh)
		जाओ out_kमुक्त_skb;
	selnl_add_payload(nlh, len, msgtype, data);
	nlh->nlmsg_len = skb->tail - पंचांगp;
	NETLINK_CB(skb).dst_group = SELNLGRP_AVC;
	netlink_broadcast(selnl, skb, 0, SELNLGRP_AVC, GFP_USER);
out:
	वापस;

out_kमुक्त_skb:
	kमुक्त_skb(skb);
oom:
	pr_err("SELinux:  OOM in %s\n", __func__);
	जाओ out;
पूर्ण

व्योम selnl_notअगरy_setenक्रमce(पूर्णांक val)
अणु
	selnl_notअगरy(SELNL_MSG_SETENFORCE, &val);
पूर्ण

व्योम selnl_notअगरy_policyload(u32 seqno)
अणु
	selnl_notअगरy(SELNL_MSG_POLICYLOAD, &seqno);
पूर्ण

अटल पूर्णांक __init selnl_init(व्योम)
अणु
	काष्ठा netlink_kernel_cfg cfg = अणु
		.groups	= SELNLGRP_MAX,
		.flags	= NL_CFG_F_NONROOT_RECV,
	पूर्ण;

	selnl = netlink_kernel_create(&init_net, NETLINK_SELINUX, &cfg);
	अगर (selnl == शून्य)
		panic("SELinux:  Cannot create netlink socket.");
	वापस 0;
पूर्ण

__initcall(selnl_init);
