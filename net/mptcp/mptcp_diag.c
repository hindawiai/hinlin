<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* MPTCP socket monitoring support
 *
 * Copyright (c) 2020 Red Hat
 *
 * Author: Paolo Abeni <pabeni@redhat.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/net.h>
#समावेश <linux/inet_diag.h>
#समावेश <net/netlink.h>
#समावेश <uapi/linux/mptcp.h>
#समावेश "protocol.h"

अटल पूर्णांक sk_diag_dump(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			काष्ठा netlink_callback *cb,
			स्थिर काष्ठा inet_diag_req_v2 *req,
			काष्ठा nlattr *bc, bool net_admin)
अणु
	अगर (!inet_diag_bc_sk(bc, sk))
		वापस 0;

	वापस inet_sk_diag_fill(sk, inet_csk(sk), skb, cb, req, NLM_F_MULTI,
				 net_admin);
पूर्ण

अटल पूर्णांक mptcp_diag_dump_one(काष्ठा netlink_callback *cb,
			       स्थिर काष्ठा inet_diag_req_v2 *req)
अणु
	काष्ठा sk_buff *in_skb = cb->skb;
	काष्ठा mptcp_sock *msk = शून्य;
	काष्ठा sk_buff *rep;
	पूर्णांक err = -ENOENT;
	काष्ठा net *net;
	काष्ठा sock *sk;

	net = sock_net(in_skb->sk);
	msk = mptcp_token_get_sock(req->id.idiag_cookie[0]);
	अगर (!msk)
		जाओ out_nosk;

	err = -ENOMEM;
	sk = (काष्ठा sock *)msk;
	rep = nlmsg_new(nla_total_size(माप(काष्ठा inet_diag_msg)) +
			inet_diag_msg_attrs_size() +
			nla_total_size(माप(काष्ठा mptcp_info)) +
			nla_total_size(माप(काष्ठा inet_diag_meminfo)) + 64,
			GFP_KERNEL);
	अगर (!rep)
		जाओ out;

	err = inet_sk_diag_fill(sk, inet_csk(sk), rep, cb, req, 0,
				netlink_net_capable(in_skb, CAP_NET_ADMIN));
	अगर (err < 0) अणु
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(rep);
		जाओ out;
	पूर्ण
	err = netlink_unicast(net->diag_nlsk, rep, NETLINK_CB(in_skb).portid,
			      MSG_DONTWAIT);
	अगर (err > 0)
		err = 0;
out:
	sock_put(sk);

out_nosk:
	वापस err;
पूर्ण

अटल व्योम mptcp_diag_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
			    स्थिर काष्ठा inet_diag_req_v2 *r)
अणु
	bool net_admin = netlink_net_capable(cb->skb, CAP_NET_ADMIN);
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा inet_diag_dump_data *cb_data;
	काष्ठा mptcp_sock *msk;
	काष्ठा nlattr *bc;

	cb_data = cb->data;
	bc = cb_data->inet_diag_nla_bc;

	जबतक ((msk = mptcp_token_iter_next(net, &cb->args[0], &cb->args[1])) !=
	       शून्य) अणु
		काष्ठा inet_sock *inet = (काष्ठा inet_sock *)msk;
		काष्ठा sock *sk = (काष्ठा sock *)msk;
		पूर्णांक ret = 0;

		अगर (!(r->idiag_states & (1 << sk->sk_state)))
			जाओ next;
		अगर (r->sdiag_family != AF_UNSPEC &&
		    sk->sk_family != r->sdiag_family)
			जाओ next;
		अगर (r->id.idiag_sport != inet->inet_sport &&
		    r->id.idiag_sport)
			जाओ next;
		अगर (r->id.idiag_dport != inet->inet_dport &&
		    r->id.idiag_dport)
			जाओ next;

		ret = sk_diag_dump(sk, skb, cb, r, bc, net_admin);
next:
		sock_put(sk);
		अगर (ret < 0) अणु
			/* will retry on the same position */
			cb->args[1]--;
			अवरोध;
		पूर्ण
		cond_resched();
	पूर्ण
पूर्ण

अटल व्योम mptcp_diag_get_info(काष्ठा sock *sk, काष्ठा inet_diag_msg *r,
				व्योम *_info)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	काष्ठा mptcp_info *info = _info;
	u32 flags = 0;
	bool slow;
	u8 val;

	r->idiag_rqueue = sk_rmem_alloc_get(sk);
	r->idiag_wqueue = sk_wmem_alloc_get(sk);
	अगर (!info)
		वापस;

	slow = lock_sock_fast(sk);
	info->mptcpi_subflows = READ_ONCE(msk->pm.subflows);
	info->mptcpi_add_addr_संकेत = READ_ONCE(msk->pm.add_addr_संकेतed);
	info->mptcpi_add_addr_accepted = READ_ONCE(msk->pm.add_addr_accepted);
	info->mptcpi_local_addr_used = READ_ONCE(msk->pm.local_addr_used);
	info->mptcpi_subflows_max = mptcp_pm_get_subflows_max(msk);
	val = mptcp_pm_get_add_addr_संकेत_max(msk);
	info->mptcpi_add_addr_संकेत_max = val;
	val = mptcp_pm_get_add_addr_accept_max(msk);
	info->mptcpi_add_addr_accepted_max = val;
	info->mptcpi_local_addr_max = mptcp_pm_get_local_addr_max(msk);
	अगर (test_bit(MPTCP_FALLBACK_DONE, &msk->flags))
		flags |= MPTCP_INFO_FLAG_FALLBACK;
	अगर (READ_ONCE(msk->can_ack))
		flags |= MPTCP_INFO_FLAG_REMOTE_KEY_RECEIVED;
	info->mptcpi_flags = flags;
	info->mptcpi_token = READ_ONCE(msk->token);
	info->mptcpi_ग_लिखो_seq = READ_ONCE(msk->ग_लिखो_seq);
	info->mptcpi_snd_una = READ_ONCE(msk->snd_una);
	info->mptcpi_rcv_nxt = READ_ONCE(msk->ack_seq);
	unlock_sock_fast(sk, slow);
पूर्ण

अटल स्थिर काष्ठा inet_diag_handler mptcp_diag_handler = अणु
	.dump		 = mptcp_diag_dump,
	.dump_one	 = mptcp_diag_dump_one,
	.idiag_get_info  = mptcp_diag_get_info,
	.idiag_type	 = IPPROTO_MPTCP,
	.idiag_info_size = माप(काष्ठा mptcp_info),
पूर्ण;

अटल पूर्णांक __init mptcp_diag_init(व्योम)
अणु
	वापस inet_diag_रेजिस्टर(&mptcp_diag_handler);
पूर्ण

अटल व्योम __निकास mptcp_diag_निकास(व्योम)
अणु
	inet_diag_unरेजिस्टर(&mptcp_diag_handler);
पूर्ण

module_init(mptcp_diag_init);
module_निकास(mptcp_diag_निकास);
MODULE_LICENSE("GPL");
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_NETLINK, NETLINK_SOCK_DIAG, 2-262 /* AF_INET - IPPROTO_MPTCP */);
