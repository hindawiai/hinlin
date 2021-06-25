<शैली गुरु>
/*
 * Copyright (c) 2017 Mellanox Technologies Inc.  All rights reserved.
 * Copyright (c) 2010 Voltaire Inc.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#घोषणा pr_fmt(fmt) "%s:%s: " fmt, KBUILD_MODNAME, __func__

#समावेश <linux/export.h>
#समावेश <net/netlink.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/sock.h>
#समावेश <rdma/rdma_netlink.h>
#समावेश <linux/module.h>
#समावेश "core_priv.h"

अटल काष्ठा अणु
	स्थिर काष्ठा rdma_nl_cbs *cb_table;
	/* Synchronizes between ongoing netlink commands and netlink client
	 * unregistration.
	 */
	काष्ठा rw_semaphore sem;
पूर्ण rdma_nl_types[RDMA_NL_NUM_CLIENTS];

bool rdma_nl_chk_listeners(अचिन्हित पूर्णांक group)
अणु
	काष्ठा rdma_dev_net *rnet = rdma_net_to_dev_net(&init_net);

	वापस netlink_has_listeners(rnet->nl_sock, group);
पूर्ण
EXPORT_SYMBOL(rdma_nl_chk_listeners);

अटल bool is_nl_msg_valid(अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक op)
अणु
	अटल स्थिर अचिन्हित पूर्णांक max_num_ops[RDMA_NL_NUM_CLIENTS] = अणु
		[RDMA_NL_IWCM] = RDMA_NL_IWPM_NUM_OPS,
		[RDMA_NL_LS] = RDMA_NL_LS_NUM_OPS,
		[RDMA_NL_NLDEV] = RDMA_NLDEV_NUM_OPS,
	पूर्ण;

	/*
	 * This BUILD_BUG_ON is पूर्णांकended to catch addition of new
	 * RDMA netlink protocol without updating the array above.
	 */
	BUILD_BUG_ON(RDMA_NL_NUM_CLIENTS != 6);

	अगर (type >= RDMA_NL_NUM_CLIENTS)
		वापस false;

	वापस (op < max_num_ops[type]) ? true : false;
पूर्ण

अटल स्थिर काष्ठा rdma_nl_cbs *
get_cb_table(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक op)
अणु
	स्थिर काष्ठा rdma_nl_cbs *cb_table;

	/*
	 * Currently only NLDEV client is supporting netlink commands in
	 * non init_net net namespace.
	 */
	अगर (sock_net(skb->sk) != &init_net && type != RDMA_NL_NLDEV)
		वापस शून्य;

	cb_table = READ_ONCE(rdma_nl_types[type].cb_table);
	अगर (!cb_table) अणु
		/*
		 * Didn't get valid reference of the table, attempt module
		 * load once.
		 */
		up_पढ़ो(&rdma_nl_types[type].sem);

		request_module("rdma-netlink-subsys-%d", type);

		करोwn_पढ़ो(&rdma_nl_types[type].sem);
		cb_table = READ_ONCE(rdma_nl_types[type].cb_table);
	पूर्ण
	अगर (!cb_table || (!cb_table[op].dump && !cb_table[op].करोit))
		वापस शून्य;
	वापस cb_table;
पूर्ण

व्योम rdma_nl_रेजिस्टर(अचिन्हित पूर्णांक index,
		      स्थिर काष्ठा rdma_nl_cbs cb_table[])
अणु
	अगर (WARN_ON(!is_nl_msg_valid(index, 0)) ||
	    WARN_ON(READ_ONCE(rdma_nl_types[index].cb_table)))
		वापस;

	/* Pairs with the READ_ONCE in is_nl_valid() */
	smp_store_release(&rdma_nl_types[index].cb_table, cb_table);
पूर्ण
EXPORT_SYMBOL(rdma_nl_रेजिस्टर);

व्योम rdma_nl_unरेजिस्टर(अचिन्हित पूर्णांक index)
अणु
	करोwn_ग_लिखो(&rdma_nl_types[index].sem);
	rdma_nl_types[index].cb_table = शून्य;
	up_ग_लिखो(&rdma_nl_types[index].sem);
पूर्ण
EXPORT_SYMBOL(rdma_nl_unरेजिस्टर);

व्योम *ibnl_put_msg(काष्ठा sk_buff *skb, काष्ठा nlmsghdr **nlh, पूर्णांक seq,
		   पूर्णांक len, पूर्णांक client, पूर्णांक op, पूर्णांक flags)
अणु
	*nlh = nlmsg_put(skb, 0, seq, RDMA_NL_GET_TYPE(client, op), len, flags);
	अगर (!*nlh)
		वापस शून्य;
	वापस nlmsg_data(*nlh);
पूर्ण
EXPORT_SYMBOL(ibnl_put_msg);

पूर्णांक ibnl_put_attr(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		  पूर्णांक len, व्योम *data, पूर्णांक type)
अणु
	अगर (nla_put(skb, type, len, data)) अणु
		nlmsg_cancel(skb, nlh);
		वापस -EMSGSIZE;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ibnl_put_attr);

अटल पूर्णांक rdma_nl_rcv_msg(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			   काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक type = nlh->nlmsg_type;
	अचिन्हित पूर्णांक index = RDMA_NL_GET_CLIENT(type);
	अचिन्हित पूर्णांक op = RDMA_NL_GET_OP(type);
	स्थिर काष्ठा rdma_nl_cbs *cb_table;
	पूर्णांक err = -EINVAL;

	अगर (!is_nl_msg_valid(index, op))
		वापस -EINVAL;

	करोwn_पढ़ो(&rdma_nl_types[index].sem);
	cb_table = get_cb_table(skb, index, op);
	अगर (!cb_table)
		जाओ करोne;

	अगर ((cb_table[op].flags & RDMA_NL_ADMIN_PERM) &&
	    !netlink_capable(skb, CAP_NET_ADMIN)) अणु
		err = -EPERM;
		जाओ करोne;
	पूर्ण

	/*
	 * LS responses overload the 0x100 (NLM_F_ROOT) flag.  Don't
	 * mistakenly call the .dump() function.
	 */
	अगर (index == RDMA_NL_LS) अणु
		अगर (cb_table[op].करोit)
			err = cb_table[op].करोit(skb, nlh, extack);
		जाओ करोne;
	पूर्ण
	/* FIXME: Convert IWCM to properly handle करोit callbacks */
	अगर ((nlh->nlmsg_flags & NLM_F_DUMP) || index == RDMA_NL_IWCM) अणु
		काष्ठा netlink_dump_control c = अणु
			.dump = cb_table[op].dump,
		पूर्ण;
		अगर (c.dump)
			err = netlink_dump_start(skb->sk, skb, nlh, &c);
		जाओ करोne;
	पूर्ण

	अगर (cb_table[op].करोit)
		err = cb_table[op].करोit(skb, nlh, extack);
करोne:
	up_पढ़ो(&rdma_nl_types[index].sem);
	वापस err;
पूर्ण

/*
 * This function is similar to netlink_rcv_skb with one exception:
 * It calls to the callback क्रम the netlink messages without NLM_F_REQUEST
 * flag. These messages are पूर्णांकended क्रम RDMA_NL_LS consumer, so it is allowed
 * क्रम that consumer only.
 */
अटल पूर्णांक rdma_nl_rcv_skb(काष्ठा sk_buff *skb, पूर्णांक (*cb)(काष्ठा sk_buff *,
						   काष्ठा nlmsghdr *,
						   काष्ठा netlink_ext_ack *))
अणु
	काष्ठा netlink_ext_ack extack = अणुपूर्ण;
	काष्ठा nlmsghdr *nlh;
	पूर्णांक err;

	जबतक (skb->len >= nlmsg_total_size(0)) अणु
		पूर्णांक msglen;

		nlh = nlmsg_hdr(skb);
		err = 0;

		अगर (nlh->nlmsg_len < NLMSG_HDRLEN || skb->len < nlh->nlmsg_len)
			वापस 0;

		/*
		 * Generally speaking, the only requests are handled
		 * by the kernel, but RDMA_NL_LS is dअगरferent, because it
		 * runs backward netlink scheme. Kernel initiates messages
		 * and रुकोs क्रम reply with data to keep pathrecord cache
		 * in sync.
		 */
		अगर (!(nlh->nlmsg_flags & NLM_F_REQUEST) &&
		    (RDMA_NL_GET_CLIENT(nlh->nlmsg_type) != RDMA_NL_LS))
			जाओ ack;

		/* Skip control messages */
		अगर (nlh->nlmsg_type < NLMSG_MIN_TYPE)
			जाओ ack;

		err = cb(skb, nlh, &extack);
		अगर (err == -EINTR)
			जाओ skip;

ack:
		अगर (nlh->nlmsg_flags & NLM_F_ACK || err)
			netlink_ack(skb, nlh, err, &extack);

skip:
		msglen = NLMSG_ALIGN(nlh->nlmsg_len);
		अगर (msglen > skb->len)
			msglen = skb->len;
		skb_pull(skb, msglen);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rdma_nl_rcv(काष्ठा sk_buff *skb)
अणु
	rdma_nl_rcv_skb(skb, &rdma_nl_rcv_msg);
पूर्ण

पूर्णांक rdma_nl_unicast(काष्ठा net *net, काष्ठा sk_buff *skb, u32 pid)
अणु
	काष्ठा rdma_dev_net *rnet = rdma_net_to_dev_net(net);
	पूर्णांक err;

	err = netlink_unicast(rnet->nl_sock, skb, pid, MSG_DONTWAIT);
	वापस (err < 0) ? err : 0;
पूर्ण
EXPORT_SYMBOL(rdma_nl_unicast);

पूर्णांक rdma_nl_unicast_रुको(काष्ठा net *net, काष्ठा sk_buff *skb, __u32 pid)
अणु
	काष्ठा rdma_dev_net *rnet = rdma_net_to_dev_net(net);
	पूर्णांक err;

	err = netlink_unicast(rnet->nl_sock, skb, pid, 0);
	वापस (err < 0) ? err : 0;
पूर्ण
EXPORT_SYMBOL(rdma_nl_unicast_रुको);

पूर्णांक rdma_nl_multicast(काष्ठा net *net, काष्ठा sk_buff *skb,
		      अचिन्हित पूर्णांक group, gfp_t flags)
अणु
	काष्ठा rdma_dev_net *rnet = rdma_net_to_dev_net(net);

	वापस nlmsg_multicast(rnet->nl_sock, skb, 0, group, flags);
पूर्ण
EXPORT_SYMBOL(rdma_nl_multicast);

व्योम rdma_nl_init(व्योम)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < RDMA_NL_NUM_CLIENTS; idx++)
		init_rwsem(&rdma_nl_types[idx].sem);
पूर्ण

व्योम rdma_nl_निकास(व्योम)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < RDMA_NL_NUM_CLIENTS; idx++)
		WARN(rdma_nl_types[idx].cb_table,
		     "Netlink client %d wasn't released prior to unloading %s\n",
		     idx, KBUILD_MODNAME);
पूर्ण

पूर्णांक rdma_nl_net_init(काष्ठा rdma_dev_net *rnet)
अणु
	काष्ठा net *net = पढ़ो_pnet(&rnet->net);
	काष्ठा netlink_kernel_cfg cfg = अणु
		.input	= rdma_nl_rcv,
	पूर्ण;
	काष्ठा sock *nls;

	nls = netlink_kernel_create(net, NETLINK_RDMA, &cfg);
	अगर (!nls)
		वापस -ENOMEM;

	nls->sk_sndसमयo = 10 * HZ;
	rnet->nl_sock = nls;
	वापस 0;
पूर्ण

व्योम rdma_nl_net_निकास(काष्ठा rdma_dev_net *rnet)
अणु
	netlink_kernel_release(rnet->nl_sock);
पूर्ण

MODULE_ALIAS_NET_PF_PROTO(PF_NETLINK, NETLINK_RDMA);
