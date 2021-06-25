<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vsock sock_diag(7) module
 *
 * Copyright (C) 2017 Red Hat, Inc.
 * Author: Stefan Hajnoczi <stefanha@redhat.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/sock_diag.h>
#समावेश <linux/vm_sockets_diag.h>
#समावेश <net/af_vsock.h>

अटल पूर्णांक sk_diag_fill(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			u32 portid, u32 seq, u32 flags)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);
	काष्ठा vsock_diag_msg *rep;
	काष्ठा nlmsghdr *nlh;

	nlh = nlmsg_put(skb, portid, seq, SOCK_DIAG_BY_FAMILY, माप(*rep),
			flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	rep = nlmsg_data(nlh);
	rep->vdiag_family = AF_VSOCK;

	/* Lock order dictates that sk_lock is acquired beक्रमe
	 * vsock_table_lock, so we cannot lock here.  Simply करोn't take
	 * sk_lock; sk is guaranteed to stay alive since vsock_table_lock is
	 * held.
	 */
	rep->vdiag_type = sk->sk_type;
	rep->vdiag_state = sk->sk_state;
	rep->vdiag_shutकरोwn = sk->sk_shutकरोwn;
	rep->vdiag_src_cid = vsk->local_addr.svm_cid;
	rep->vdiag_src_port = vsk->local_addr.svm_port;
	rep->vdiag_dst_cid = vsk->remote_addr.svm_cid;
	rep->vdiag_dst_port = vsk->remote_addr.svm_port;
	rep->vdiag_ino = sock_i_ino(sk);

	sock_diag_save_cookie(sk, rep->vdiag_cookie);

	वापस 0;
पूर्ण

अटल पूर्णांक vsock_diag_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा vsock_diag_req *req;
	काष्ठा vsock_sock *vsk;
	अचिन्हित पूर्णांक bucket;
	अचिन्हित पूर्णांक last_i;
	अचिन्हित पूर्णांक table;
	काष्ठा net *net;
	अचिन्हित पूर्णांक i;

	req = nlmsg_data(cb->nlh);
	net = sock_net(skb->sk);

	/* State saved between calls: */
	table = cb->args[0];
	bucket = cb->args[1];
	i = last_i = cb->args[2];

	/* TODO VMCI pending sockets? */

	spin_lock_bh(&vsock_table_lock);

	/* Bind table (locally created sockets) */
	अगर (table == 0) अणु
		जबतक (bucket < ARRAY_SIZE(vsock_bind_table)) अणु
			काष्ठा list_head *head = &vsock_bind_table[bucket];

			i = 0;
			list_क्रम_each_entry(vsk, head, bound_table) अणु
				काष्ठा sock *sk = sk_vsock(vsk);

				अगर (!net_eq(sock_net(sk), net))
					जारी;
				अगर (i < last_i)
					जाओ next_bind;
				अगर (!(req->vdiag_states & (1 << sk->sk_state)))
					जाओ next_bind;
				अगर (sk_diag_fill(sk, skb,
						 NETLINK_CB(cb->skb).portid,
						 cb->nlh->nlmsg_seq,
						 NLM_F_MULTI) < 0)
					जाओ करोne;
next_bind:
				i++;
			पूर्ण
			last_i = 0;
			bucket++;
		पूर्ण

		table++;
		bucket = 0;
	पूर्ण

	/* Connected table (accepted connections) */
	जबतक (bucket < ARRAY_SIZE(vsock_connected_table)) अणु
		काष्ठा list_head *head = &vsock_connected_table[bucket];

		i = 0;
		list_क्रम_each_entry(vsk, head, connected_table) अणु
			काष्ठा sock *sk = sk_vsock(vsk);

			/* Skip sockets we've alपढ़ोy seen above */
			अगर (__vsock_in_bound_table(vsk))
				जारी;

			अगर (!net_eq(sock_net(sk), net))
				जारी;
			अगर (i < last_i)
				जाओ next_connected;
			अगर (!(req->vdiag_states & (1 << sk->sk_state)))
				जाओ next_connected;
			अगर (sk_diag_fill(sk, skb,
					 NETLINK_CB(cb->skb).portid,
					 cb->nlh->nlmsg_seq,
					 NLM_F_MULTI) < 0)
				जाओ करोne;
next_connected:
			i++;
		पूर्ण
		last_i = 0;
		bucket++;
	पूर्ण

करोne:
	spin_unlock_bh(&vsock_table_lock);

	cb->args[0] = table;
	cb->args[1] = bucket;
	cb->args[2] = i;

	वापस skb->len;
पूर्ण

अटल पूर्णांक vsock_diag_handler_dump(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *h)
अणु
	पूर्णांक hdrlen = माप(काष्ठा vsock_diag_req);
	काष्ठा net *net = sock_net(skb->sk);

	अगर (nlmsg_len(h) < hdrlen)
		वापस -EINVAL;

	अगर (h->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.dump = vsock_diag_dump,
		पूर्ण;
		वापस netlink_dump_start(net->diag_nlsk, skb, h, &c);
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा sock_diag_handler vsock_diag_handler = अणु
	.family = AF_VSOCK,
	.dump = vsock_diag_handler_dump,
पूर्ण;

अटल पूर्णांक __init vsock_diag_init(व्योम)
अणु
	वापस sock_diag_रेजिस्टर(&vsock_diag_handler);
पूर्ण

अटल व्योम __निकास vsock_diag_निकास(व्योम)
अणु
	sock_diag_unरेजिस्टर(&vsock_diag_handler);
पूर्ण

module_init(vsock_diag_init);
module_निकास(vsock_diag_निकास);
MODULE_LICENSE("GPL");
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_NETLINK, NETLINK_SOCK_DIAG,
			       40 /* AF_VSOCK */);
