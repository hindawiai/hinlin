<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>

#समावेश <net/sock.h>
#समावेश <linux/netlink.h>
#समावेश <linux/sock_diag.h>
#समावेश <linux/netlink_diag.h>
#समावेश <linux/rhashtable.h>

#समावेश "af_netlink.h"

अटल पूर्णांक sk_diag_dump_groups(काष्ठा sock *sk, काष्ठा sk_buff *nlskb)
अणु
	काष्ठा netlink_sock *nlk = nlk_sk(sk);

	अगर (nlk->groups == शून्य)
		वापस 0;

	वापस nla_put(nlskb, NETLINK_DIAG_GROUPS, NLGRPSZ(nlk->ngroups),
		       nlk->groups);
पूर्ण

अटल पूर्णांक sk_diag_put_flags(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा netlink_sock *nlk = nlk_sk(sk);
	u32 flags = 0;

	अगर (nlk->cb_running)
		flags |= NDIAG_FLAG_CB_RUNNING;
	अगर (nlk->flags & NETLINK_F_RECV_PKTINFO)
		flags |= NDIAG_FLAG_PKTINFO;
	अगर (nlk->flags & NETLINK_F_BROADCAST_SEND_ERROR)
		flags |= NDIAG_FLAG_BROADCAST_ERROR;
	अगर (nlk->flags & NETLINK_F_RECV_NO_ENOBUFS)
		flags |= NDIAG_FLAG_NO_ENOBUFS;
	अगर (nlk->flags & NETLINK_F_LISTEN_ALL_NSID)
		flags |= NDIAG_FLAG_LISTEN_ALL_NSID;
	अगर (nlk->flags & NETLINK_F_CAP_ACK)
		flags |= NDIAG_FLAG_CAP_ACK;

	वापस nla_put_u32(skb, NETLINK_DIAG_FLAGS, flags);
पूर्ण

अटल पूर्णांक sk_diag_fill(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			काष्ठा netlink_diag_req *req,
			u32 portid, u32 seq, u32 flags, पूर्णांक sk_ino)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा netlink_diag_msg *rep;
	काष्ठा netlink_sock *nlk = nlk_sk(sk);

	nlh = nlmsg_put(skb, portid, seq, SOCK_DIAG_BY_FAMILY, माप(*rep),
			flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	rep = nlmsg_data(nlh);
	rep->ndiag_family	= AF_NETLINK;
	rep->ndiag_type		= sk->sk_type;
	rep->ndiag_protocol	= sk->sk_protocol;
	rep->ndiag_state	= sk->sk_state;

	rep->ndiag_ino		= sk_ino;
	rep->ndiag_portid	= nlk->portid;
	rep->ndiag_dst_portid	= nlk->dst_portid;
	rep->ndiag_dst_group	= nlk->dst_group;
	sock_diag_save_cookie(sk, rep->ndiag_cookie);

	अगर ((req->ndiag_show & NDIAG_SHOW_GROUPS) &&
	    sk_diag_dump_groups(sk, skb))
		जाओ out_nlmsg_trim;

	अगर ((req->ndiag_show & NDIAG_SHOW_MEMINFO) &&
	    sock_diag_put_meminfo(sk, skb, NETLINK_DIAG_MEMINFO))
		जाओ out_nlmsg_trim;

	अगर ((req->ndiag_show & NDIAG_SHOW_FLAGS) &&
	    sk_diag_put_flags(sk, skb))
		जाओ out_nlmsg_trim;

	nlmsg_end(skb, nlh);
	वापस 0;

out_nlmsg_trim:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक __netlink_diag_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
				पूर्णांक protocol, पूर्णांक s_num)
अणु
	काष्ठा rhashtable_iter *hti = (व्योम *)cb->args[2];
	काष्ठा netlink_table *tbl = &nl_table[protocol];
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा netlink_diag_req *req;
	काष्ठा netlink_sock *nlsk;
	काष्ठा sock *sk;
	पूर्णांक num = 2;
	पूर्णांक ret = 0;

	req = nlmsg_data(cb->nlh);

	अगर (s_num > 1)
		जाओ mc_list;

	num--;

	अगर (!hti) अणु
		hti = kदो_स्मृति(माप(*hti), GFP_KERNEL);
		अगर (!hti)
			वापस -ENOMEM;

		cb->args[2] = (दीर्घ)hti;
	पूर्ण

	अगर (!s_num)
		rhashtable_walk_enter(&tbl->hash, hti);

	rhashtable_walk_start(hti);

	जबतक ((nlsk = rhashtable_walk_next(hti))) अणु
		अगर (IS_ERR(nlsk)) अणु
			ret = PTR_ERR(nlsk);
			अगर (ret == -EAGAIN) अणु
				ret = 0;
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		sk = (काष्ठा sock *)nlsk;

		अगर (!net_eq(sock_net(sk), net))
			जारी;

		अगर (sk_diag_fill(sk, skb, req,
				 NETLINK_CB(cb->skb).portid,
				 cb->nlh->nlmsg_seq,
				 NLM_F_MULTI,
				 sock_i_ino(sk)) < 0) अणु
			ret = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	rhashtable_walk_stop(hti);

	अगर (ret)
		जाओ करोne;

	rhashtable_walk_निकास(hti);
	num++;

mc_list:
	पढ़ो_lock(&nl_table_lock);
	sk_क्रम_each_bound(sk, &tbl->mc_list) अणु
		अगर (sk_hashed(sk))
			जारी;
		अगर (!net_eq(sock_net(sk), net))
			जारी;
		अगर (num < s_num) अणु
			num++;
			जारी;
		पूर्ण

		अगर (sk_diag_fill(sk, skb, req,
				 NETLINK_CB(cb->skb).portid,
				 cb->nlh->nlmsg_seq,
				 NLM_F_MULTI,
				 sock_i_ino(sk)) < 0) अणु
			ret = 1;
			अवरोध;
		पूर्ण
		num++;
	पूर्ण
	पढ़ो_unlock(&nl_table_lock);

करोne:
	cb->args[0] = num;

	वापस ret;
पूर्ण

अटल पूर्णांक netlink_diag_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा netlink_diag_req *req;
	पूर्णांक s_num = cb->args[0];
	पूर्णांक err = 0;

	req = nlmsg_data(cb->nlh);

	अगर (req->sdiag_protocol == NDIAG_PROTO_ALL) अणु
		पूर्णांक i;

		क्रम (i = cb->args[1]; i < MAX_LINKS; i++) अणु
			err = __netlink_diag_dump(skb, cb, i, s_num);
			अगर (err)
				अवरोध;
			s_num = 0;
		पूर्ण
		cb->args[1] = i;
	पूर्ण अन्यथा अणु
		अगर (req->sdiag_protocol >= MAX_LINKS)
			वापस -ENOENT;

		err = __netlink_diag_dump(skb, cb, req->sdiag_protocol, s_num);
	पूर्ण

	वापस err < 0 ? err : skb->len;
पूर्ण

अटल पूर्णांक netlink_diag_dump_करोne(काष्ठा netlink_callback *cb)
अणु
	काष्ठा rhashtable_iter *hti = (व्योम *)cb->args[2];

	अगर (cb->args[0] == 1)
		rhashtable_walk_निकास(hti);

	kमुक्त(hti);

	वापस 0;
पूर्ण

अटल पूर्णांक netlink_diag_handler_dump(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *h)
अणु
	पूर्णांक hdrlen = माप(काष्ठा netlink_diag_req);
	काष्ठा net *net = sock_net(skb->sk);

	अगर (nlmsg_len(h) < hdrlen)
		वापस -EINVAL;

	अगर (h->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.dump = netlink_diag_dump,
			.करोne = netlink_diag_dump_करोne,
		पूर्ण;
		वापस netlink_dump_start(net->diag_nlsk, skb, h, &c);
	पूर्ण अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा sock_diag_handler netlink_diag_handler = अणु
	.family = AF_NETLINK,
	.dump = netlink_diag_handler_dump,
पूर्ण;

अटल पूर्णांक __init netlink_diag_init(व्योम)
अणु
	वापस sock_diag_रेजिस्टर(&netlink_diag_handler);
पूर्ण

अटल व्योम __निकास netlink_diag_निकास(व्योम)
अणु
	sock_diag_unरेजिस्टर(&netlink_diag_handler);
पूर्ण

module_init(netlink_diag_init);
module_निकास(netlink_diag_निकास);
MODULE_LICENSE("GPL");
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_NETLINK, NETLINK_SOCK_DIAG, 16 /* AF_NETLINK */);
