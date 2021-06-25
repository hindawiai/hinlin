<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sock_diag.h>
#समावेश <linux/unix_diag.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/module.h>
#समावेश <linux/uidgid.h>
#समावेश <net/netlink.h>
#समावेश <net/af_unix.h>
#समावेश <net/tcp_states.h>
#समावेश <net/sock.h>

अटल पूर्णांक sk_diag_dump_name(काष्ठा sock *sk, काष्ठा sk_buff *nlskb)
अणु
	/* might or might not have unix_table_lock */
	काष्ठा unix_address *addr = smp_load_acquire(&unix_sk(sk)->addr);

	अगर (!addr)
		वापस 0;

	वापस nla_put(nlskb, UNIX_DIAG_NAME, addr->len - माप(लघु),
		       addr->name->sun_path);
पूर्ण

अटल पूर्णांक sk_diag_dump_vfs(काष्ठा sock *sk, काष्ठा sk_buff *nlskb)
अणु
	काष्ठा dentry *dentry = unix_sk(sk)->path.dentry;

	अगर (dentry) अणु
		काष्ठा unix_diag_vfs uv = अणु
			.udiag_vfs_ino = d_backing_inode(dentry)->i_ino,
			.udiag_vfs_dev = dentry->d_sb->s_dev,
		पूर्ण;

		वापस nla_put(nlskb, UNIX_DIAG_VFS, माप(uv), &uv);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sk_diag_dump_peer(काष्ठा sock *sk, काष्ठा sk_buff *nlskb)
अणु
	काष्ठा sock *peer;
	पूर्णांक ino;

	peer = unix_peer_get(sk);
	अगर (peer) अणु
		unix_state_lock(peer);
		ino = sock_i_ino(peer);
		unix_state_unlock(peer);
		sock_put(peer);

		वापस nla_put_u32(nlskb, UNIX_DIAG_PEER, ino);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sk_diag_dump_icons(काष्ठा sock *sk, काष्ठा sk_buff *nlskb)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा nlattr *attr;
	u32 *buf;
	पूर्णांक i;

	अगर (sk->sk_state == TCP_LISTEN) अणु
		spin_lock(&sk->sk_receive_queue.lock);

		attr = nla_reserve(nlskb, UNIX_DIAG_ICONS,
				   sk->sk_receive_queue.qlen * माप(u32));
		अगर (!attr)
			जाओ errout;

		buf = nla_data(attr);
		i = 0;
		skb_queue_walk(&sk->sk_receive_queue, skb) अणु
			काष्ठा sock *req, *peer;

			req = skb->sk;
			/*
			 * The state lock is outer क्रम the same sk's
			 * queue lock. With the other's queue locked it's
			 * OK to lock the state.
			 */
			unix_state_lock_nested(req);
			peer = unix_sk(req)->peer;
			buf[i++] = (peer ? sock_i_ino(peer) : 0);
			unix_state_unlock(req);
		पूर्ण
		spin_unlock(&sk->sk_receive_queue.lock);
	पूर्ण

	वापस 0;

errout:
	spin_unlock(&sk->sk_receive_queue.lock);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक sk_diag_show_rqlen(काष्ठा sock *sk, काष्ठा sk_buff *nlskb)
अणु
	काष्ठा unix_diag_rqlen rql;

	अगर (sk->sk_state == TCP_LISTEN) अणु
		rql.udiag_rqueue = sk->sk_receive_queue.qlen;
		rql.udiag_wqueue = sk->sk_max_ack_backlog;
	पूर्ण अन्यथा अणु
		rql.udiag_rqueue = (u32) unix_inq_len(sk);
		rql.udiag_wqueue = (u32) unix_outq_len(sk);
	पूर्ण

	वापस nla_put(nlskb, UNIX_DIAG_RQLEN, माप(rql), &rql);
पूर्ण

अटल पूर्णांक sk_diag_dump_uid(काष्ठा sock *sk, काष्ठा sk_buff *nlskb)
अणु
	uid_t uid = from_kuid_munged(sk_user_ns(nlskb->sk), sock_i_uid(sk));
	वापस nla_put(nlskb, UNIX_DIAG_UID, माप(uid_t), &uid);
पूर्ण

अटल पूर्णांक sk_diag_fill(काष्ठा sock *sk, काष्ठा sk_buff *skb, काष्ठा unix_diag_req *req,
		u32 portid, u32 seq, u32 flags, पूर्णांक sk_ino)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा unix_diag_msg *rep;

	nlh = nlmsg_put(skb, portid, seq, SOCK_DIAG_BY_FAMILY, माप(*rep),
			flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	rep = nlmsg_data(nlh);
	rep->udiag_family = AF_UNIX;
	rep->udiag_type = sk->sk_type;
	rep->udiag_state = sk->sk_state;
	rep->pad = 0;
	rep->udiag_ino = sk_ino;
	sock_diag_save_cookie(sk, rep->udiag_cookie);

	अगर ((req->udiag_show & UDIAG_SHOW_NAME) &&
	    sk_diag_dump_name(sk, skb))
		जाओ out_nlmsg_trim;

	अगर ((req->udiag_show & UDIAG_SHOW_VFS) &&
	    sk_diag_dump_vfs(sk, skb))
		जाओ out_nlmsg_trim;

	अगर ((req->udiag_show & UDIAG_SHOW_PEER) &&
	    sk_diag_dump_peer(sk, skb))
		जाओ out_nlmsg_trim;

	अगर ((req->udiag_show & UDIAG_SHOW_ICONS) &&
	    sk_diag_dump_icons(sk, skb))
		जाओ out_nlmsg_trim;

	अगर ((req->udiag_show & UDIAG_SHOW_RQLEN) &&
	    sk_diag_show_rqlen(sk, skb))
		जाओ out_nlmsg_trim;

	अगर ((req->udiag_show & UDIAG_SHOW_MEMINFO) &&
	    sock_diag_put_meminfo(sk, skb, UNIX_DIAG_MEMINFO))
		जाओ out_nlmsg_trim;

	अगर (nla_put_u8(skb, UNIX_DIAG_SHUTDOWN, sk->sk_shutकरोwn))
		जाओ out_nlmsg_trim;

	अगर ((req->udiag_show & UDIAG_SHOW_UID) &&
	    sk_diag_dump_uid(sk, skb))
		जाओ out_nlmsg_trim;

	nlmsg_end(skb, nlh);
	वापस 0;

out_nlmsg_trim:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक sk_diag_dump(काष्ठा sock *sk, काष्ठा sk_buff *skb, काष्ठा unix_diag_req *req,
		u32 portid, u32 seq, u32 flags)
अणु
	पूर्णांक sk_ino;

	unix_state_lock(sk);
	sk_ino = sock_i_ino(sk);
	unix_state_unlock(sk);

	अगर (!sk_ino)
		वापस 0;

	वापस sk_diag_fill(sk, skb, req, portid, seq, flags, sk_ino);
पूर्ण

अटल पूर्णांक unix_diag_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा unix_diag_req *req;
	पूर्णांक num, s_num, slot, s_slot;
	काष्ठा net *net = sock_net(skb->sk);

	req = nlmsg_data(cb->nlh);

	s_slot = cb->args[0];
	num = s_num = cb->args[1];

	spin_lock(&unix_table_lock);
	क्रम (slot = s_slot;
	     slot < ARRAY_SIZE(unix_socket_table);
	     s_num = 0, slot++) अणु
		काष्ठा sock *sk;

		num = 0;
		sk_क्रम_each(sk, &unix_socket_table[slot]) अणु
			अगर (!net_eq(sock_net(sk), net))
				जारी;
			अगर (num < s_num)
				जाओ next;
			अगर (!(req->udiag_states & (1 << sk->sk_state)))
				जाओ next;
			अगर (sk_diag_dump(sk, skb, req,
					 NETLINK_CB(cb->skb).portid,
					 cb->nlh->nlmsg_seq,
					 NLM_F_MULTI) < 0)
				जाओ करोne;
next:
			num++;
		पूर्ण
	पूर्ण
करोne:
	spin_unlock(&unix_table_lock);
	cb->args[0] = slot;
	cb->args[1] = num;

	वापस skb->len;
पूर्ण

अटल काष्ठा sock *unix_lookup_by_ino(अचिन्हित पूर्णांक ino)
अणु
	पूर्णांक i;
	काष्ठा sock *sk;

	spin_lock(&unix_table_lock);
	क्रम (i = 0; i < ARRAY_SIZE(unix_socket_table); i++) अणु
		sk_क्रम_each(sk, &unix_socket_table[i])
			अगर (ino == sock_i_ino(sk)) अणु
				sock_hold(sk);
				spin_unlock(&unix_table_lock);

				वापस sk;
			पूर्ण
	पूर्ण

	spin_unlock(&unix_table_lock);
	वापस शून्य;
पूर्ण

अटल पूर्णांक unix_diag_get_exact(काष्ठा sk_buff *in_skb,
			       स्थिर काष्ठा nlmsghdr *nlh,
			       काष्ठा unix_diag_req *req)
अणु
	पूर्णांक err = -EINVAL;
	काष्ठा sock *sk;
	काष्ठा sk_buff *rep;
	अचिन्हित पूर्णांक extra_len;
	काष्ठा net *net = sock_net(in_skb->sk);

	अगर (req->udiag_ino == 0)
		जाओ out_nosk;

	sk = unix_lookup_by_ino(req->udiag_ino);
	err = -ENOENT;
	अगर (sk == शून्य)
		जाओ out_nosk;
	अगर (!net_eq(sock_net(sk), net))
		जाओ out;

	err = sock_diag_check_cookie(sk, req->udiag_cookie);
	अगर (err)
		जाओ out;

	extra_len = 256;
again:
	err = -ENOMEM;
	rep = nlmsg_new(माप(काष्ठा unix_diag_msg) + extra_len, GFP_KERNEL);
	अगर (!rep)
		जाओ out;

	err = sk_diag_fill(sk, rep, req, NETLINK_CB(in_skb).portid,
			   nlh->nlmsg_seq, 0, req->udiag_ino);
	अगर (err < 0) अणु
		nlmsg_मुक्त(rep);
		extra_len += 256;
		अगर (extra_len >= PAGE_SIZE)
			जाओ out;

		जाओ again;
	पूर्ण
	err = netlink_unicast(net->diag_nlsk, rep, NETLINK_CB(in_skb).portid,
			      MSG_DONTWAIT);
	अगर (err > 0)
		err = 0;
out:
	अगर (sk)
		sock_put(sk);
out_nosk:
	वापस err;
पूर्ण

अटल पूर्णांक unix_diag_handler_dump(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *h)
अणु
	पूर्णांक hdrlen = माप(काष्ठा unix_diag_req);
	काष्ठा net *net = sock_net(skb->sk);

	अगर (nlmsg_len(h) < hdrlen)
		वापस -EINVAL;

	अगर (h->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.dump = unix_diag_dump,
		पूर्ण;
		वापस netlink_dump_start(net->diag_nlsk, skb, h, &c);
	पूर्ण अन्यथा
		वापस unix_diag_get_exact(skb, h, nlmsg_data(h));
पूर्ण

अटल स्थिर काष्ठा sock_diag_handler unix_diag_handler = अणु
	.family = AF_UNIX,
	.dump = unix_diag_handler_dump,
पूर्ण;

अटल पूर्णांक __init unix_diag_init(व्योम)
अणु
	वापस sock_diag_रेजिस्टर(&unix_diag_handler);
पूर्ण

अटल व्योम __निकास unix_diag_निकास(व्योम)
अणु
	sock_diag_unरेजिस्टर(&unix_diag_handler);
पूर्ण

module_init(unix_diag_init);
module_निकास(unix_diag_निकास);
MODULE_LICENSE("GPL");
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_NETLINK, NETLINK_SOCK_DIAG, 1 /* AF_LOCAL */);
