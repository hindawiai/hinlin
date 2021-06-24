<शैली गुरु>
/*
 * net/tipc/diag.c: TIPC socket diag
 *
 * Copyright (c) 2018, Ericsson AB
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to enकरोrse or promote products derived from
 *    this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "ASIS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश "core.h"
#समावेश "socket.h"
#समावेश <linux/sock_diag.h>
#समावेश <linux/tipc_sockets_diag.h>

अटल u64 __tipc_diag_gen_cookie(काष्ठा sock *sk)
अणु
	u32 res[2];

	sock_diag_save_cookie(sk, res);
	वापस *((u64 *)res);
पूर्ण

अटल पूर्णांक __tipc_add_sock_diag(काष्ठा sk_buff *skb,
				काष्ठा netlink_callback *cb,
				काष्ठा tipc_sock *tsk)
अणु
	काष्ठा tipc_sock_diag_req *req = nlmsg_data(cb->nlh);
	काष्ठा nlmsghdr *nlh;
	पूर्णांक err;

	nlh = nlmsg_put_answer(skb, cb, SOCK_DIAG_BY_FAMILY, 0,
			       NLM_F_MULTI);
	अगर (!nlh)
		वापस -EMSGSIZE;

	err = tipc_sk_fill_sock_diag(skb, cb, tsk, req->tidiag_states,
				     __tipc_diag_gen_cookie);
	अगर (err)
		वापस err;

	nlmsg_end(skb, nlh);
	वापस 0;
पूर्ण

अटल पूर्णांक tipc_diag_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	वापस tipc_nl_sk_walk(skb, cb, __tipc_add_sock_diag);
पूर्ण

अटल पूर्णांक tipc_sock_diag_handler_dump(काष्ठा sk_buff *skb,
				       काष्ठा nlmsghdr *h)
अणु
	पूर्णांक hdrlen = माप(काष्ठा tipc_sock_diag_req);
	काष्ठा net *net = sock_net(skb->sk);

	अगर (nlmsg_len(h) < hdrlen)
		वापस -EINVAL;

	अगर (h->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.start = tipc_dump_start,
			.dump = tipc_diag_dump,
			.करोne = tipc_dump_करोne,
		पूर्ण;
		netlink_dump_start(net->diag_nlsk, skb, h, &c);
		वापस 0;
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा sock_diag_handler tipc_sock_diag_handler = अणु
	.family = AF_TIPC,
	.dump = tipc_sock_diag_handler_dump,
पूर्ण;

अटल पूर्णांक __init tipc_diag_init(व्योम)
अणु
	वापस sock_diag_रेजिस्टर(&tipc_sock_diag_handler);
पूर्ण

अटल व्योम __निकास tipc_diag_निकास(व्योम)
अणु
	sock_diag_unरेजिस्टर(&tipc_sock_diag_handler);
पूर्ण

module_init(tipc_diag_init);
module_निकास(tipc_diag_निकास);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_NETLINK, NETLINK_SOCK_DIAG, AF_TIPC);
