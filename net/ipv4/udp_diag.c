<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * udp_diag.c	Module क्रम monitoring UDP transport protocols sockets.
 *
 * Authors:	Pavel Emelyanov, <xemul@parallels.com>
 */


#समावेश <linux/module.h>
#समावेश <linux/inet_diag.h>
#समावेश <linux/udp.h>
#समावेश <net/udp.h>
#समावेश <net/udplite.h>
#समावेश <linux/sock_diag.h>

अटल पूर्णांक sk_diag_dump(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			काष्ठा netlink_callback *cb,
			स्थिर काष्ठा inet_diag_req_v2 *req,
			काष्ठा nlattr *bc, bool net_admin)
अणु
	अगर (!inet_diag_bc_sk(bc, sk))
		वापस 0;

	वापस inet_sk_diag_fill(sk, शून्य, skb, cb, req, NLM_F_MULTI,
				 net_admin);
पूर्ण

अटल पूर्णांक udp_dump_one(काष्ठा udp_table *tbl,
			काष्ठा netlink_callback *cb,
			स्थिर काष्ठा inet_diag_req_v2 *req)
अणु
	काष्ठा sk_buff *in_skb = cb->skb;
	पूर्णांक err;
	काष्ठा sock *sk = शून्य;
	काष्ठा sk_buff *rep;
	काष्ठा net *net = sock_net(in_skb->sk);

	rcu_पढ़ो_lock();
	अगर (req->sdiag_family == AF_INET)
		/* src and dst are swapped क्रम historical reasons */
		sk = __udp4_lib_lookup(net,
				req->id.idiag_src[0], req->id.idiag_sport,
				req->id.idiag_dst[0], req->id.idiag_dport,
				req->id.idiag_अगर, 0, tbl, शून्य);
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा अगर (req->sdiag_family == AF_INET6)
		sk = __udp6_lib_lookup(net,
				(काष्ठा in6_addr *)req->id.idiag_src,
				req->id.idiag_sport,
				(काष्ठा in6_addr *)req->id.idiag_dst,
				req->id.idiag_dport,
				req->id.idiag_अगर, 0, tbl, शून्य);
#पूर्ण_अगर
	अगर (sk && !refcount_inc_not_zero(&sk->sk_refcnt))
		sk = शून्य;
	rcu_पढ़ो_unlock();
	err = -ENOENT;
	अगर (!sk)
		जाओ out_nosk;

	err = sock_diag_check_cookie(sk, req->id.idiag_cookie);
	अगर (err)
		जाओ out;

	err = -ENOMEM;
	rep = nlmsg_new(nla_total_size(माप(काष्ठा inet_diag_msg)) +
			inet_diag_msg_attrs_size() +
			nla_total_size(माप(काष्ठा inet_diag_meminfo)) + 64,
			GFP_KERNEL);
	अगर (!rep)
		जाओ out;

	err = inet_sk_diag_fill(sk, शून्य, rep, cb, req, 0,
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
	अगर (sk)
		sock_put(sk);
out_nosk:
	वापस err;
पूर्ण

अटल व्योम udp_dump(काष्ठा udp_table *table, काष्ठा sk_buff *skb,
		     काष्ठा netlink_callback *cb,
		     स्थिर काष्ठा inet_diag_req_v2 *r)
अणु
	bool net_admin = netlink_net_capable(cb->skb, CAP_NET_ADMIN);
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा inet_diag_dump_data *cb_data;
	पूर्णांक num, s_num, slot, s_slot;
	काष्ठा nlattr *bc;

	cb_data = cb->data;
	bc = cb_data->inet_diag_nla_bc;
	s_slot = cb->args[0];
	num = s_num = cb->args[1];

	क्रम (slot = s_slot; slot <= table->mask; s_num = 0, slot++) अणु
		काष्ठा udp_hslot *hslot = &table->hash[slot];
		काष्ठा sock *sk;

		num = 0;

		अगर (hlist_empty(&hslot->head))
			जारी;

		spin_lock_bh(&hslot->lock);
		sk_क्रम_each(sk, &hslot->head) अणु
			काष्ठा inet_sock *inet = inet_sk(sk);

			अगर (!net_eq(sock_net(sk), net))
				जारी;
			अगर (num < s_num)
				जाओ next;
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

			अगर (sk_diag_dump(sk, skb, cb, r, bc, net_admin) < 0) अणु
				spin_unlock_bh(&hslot->lock);
				जाओ करोne;
			पूर्ण
next:
			num++;
		पूर्ण
		spin_unlock_bh(&hslot->lock);
	पूर्ण
करोne:
	cb->args[0] = slot;
	cb->args[1] = num;
पूर्ण

अटल व्योम udp_diag_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
			  स्थिर काष्ठा inet_diag_req_v2 *r)
अणु
	udp_dump(&udp_table, skb, cb, r);
पूर्ण

अटल पूर्णांक udp_diag_dump_one(काष्ठा netlink_callback *cb,
			     स्थिर काष्ठा inet_diag_req_v2 *req)
अणु
	वापस udp_dump_one(&udp_table, cb, req);
पूर्ण

अटल व्योम udp_diag_get_info(काष्ठा sock *sk, काष्ठा inet_diag_msg *r,
		व्योम *info)
अणु
	r->idiag_rqueue = udp_rqueue_get(sk);
	r->idiag_wqueue = sk_wmem_alloc_get(sk);
पूर्ण

#अगर_घोषित CONFIG_INET_DIAG_DESTROY
अटल पूर्णांक __udp_diag_destroy(काष्ठा sk_buff *in_skb,
			      स्थिर काष्ठा inet_diag_req_v2 *req,
			      काष्ठा udp_table *tbl)
अणु
	काष्ठा net *net = sock_net(in_skb->sk);
	काष्ठा sock *sk;
	पूर्णांक err;

	rcu_पढ़ो_lock();

	अगर (req->sdiag_family == AF_INET)
		sk = __udp4_lib_lookup(net,
				req->id.idiag_dst[0], req->id.idiag_dport,
				req->id.idiag_src[0], req->id.idiag_sport,
				req->id.idiag_अगर, 0, tbl, शून्य);
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा अगर (req->sdiag_family == AF_INET6) अणु
		अगर (ipv6_addr_v4mapped((काष्ठा in6_addr *)req->id.idiag_dst) &&
		    ipv6_addr_v4mapped((काष्ठा in6_addr *)req->id.idiag_src))
			sk = __udp4_lib_lookup(net,
					req->id.idiag_dst[3], req->id.idiag_dport,
					req->id.idiag_src[3], req->id.idiag_sport,
					req->id.idiag_अगर, 0, tbl, शून्य);

		अन्यथा
			sk = __udp6_lib_lookup(net,
					(काष्ठा in6_addr *)req->id.idiag_dst,
					req->id.idiag_dport,
					(काष्ठा in6_addr *)req->id.idiag_src,
					req->id.idiag_sport,
					req->id.idiag_अगर, 0, tbl, शून्य);
	पूर्ण
#पूर्ण_अगर
	अन्यथा अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण

	अगर (sk && !refcount_inc_not_zero(&sk->sk_refcnt))
		sk = शून्य;

	rcu_पढ़ो_unlock();

	अगर (!sk)
		वापस -ENOENT;

	अगर (sock_diag_check_cookie(sk, req->id.idiag_cookie)) अणु
		sock_put(sk);
		वापस -ENOENT;
	पूर्ण

	err = sock_diag_destroy(sk, ECONNABORTED);

	sock_put(sk);

	वापस err;
पूर्ण

अटल पूर्णांक udp_diag_destroy(काष्ठा sk_buff *in_skb,
			    स्थिर काष्ठा inet_diag_req_v2 *req)
अणु
	वापस __udp_diag_destroy(in_skb, req, &udp_table);
पूर्ण

अटल पूर्णांक udplite_diag_destroy(काष्ठा sk_buff *in_skb,
				स्थिर काष्ठा inet_diag_req_v2 *req)
अणु
	वापस __udp_diag_destroy(in_skb, req, &udplite_table);
पूर्ण

#पूर्ण_अगर

अटल स्थिर काष्ठा inet_diag_handler udp_diag_handler = अणु
	.dump		 = udp_diag_dump,
	.dump_one	 = udp_diag_dump_one,
	.idiag_get_info  = udp_diag_get_info,
	.idiag_type	 = IPPROTO_UDP,
	.idiag_info_size = 0,
#अगर_घोषित CONFIG_INET_DIAG_DESTROY
	.destroy	 = udp_diag_destroy,
#पूर्ण_अगर
पूर्ण;

अटल व्योम udplite_diag_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
			      स्थिर काष्ठा inet_diag_req_v2 *r)
अणु
	udp_dump(&udplite_table, skb, cb, r);
पूर्ण

अटल पूर्णांक udplite_diag_dump_one(काष्ठा netlink_callback *cb,
				 स्थिर काष्ठा inet_diag_req_v2 *req)
अणु
	वापस udp_dump_one(&udplite_table, cb, req);
पूर्ण

अटल स्थिर काष्ठा inet_diag_handler udplite_diag_handler = अणु
	.dump		 = udplite_diag_dump,
	.dump_one	 = udplite_diag_dump_one,
	.idiag_get_info  = udp_diag_get_info,
	.idiag_type	 = IPPROTO_UDPLITE,
	.idiag_info_size = 0,
#अगर_घोषित CONFIG_INET_DIAG_DESTROY
	.destroy	 = udplite_diag_destroy,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init udp_diag_init(व्योम)
अणु
	पूर्णांक err;

	err = inet_diag_रेजिस्टर(&udp_diag_handler);
	अगर (err)
		जाओ out;
	err = inet_diag_रेजिस्टर(&udplite_diag_handler);
	अगर (err)
		जाओ out_lite;
out:
	वापस err;
out_lite:
	inet_diag_unरेजिस्टर(&udp_diag_handler);
	जाओ out;
पूर्ण

अटल व्योम __निकास udp_diag_निकास(व्योम)
अणु
	inet_diag_unरेजिस्टर(&udplite_diag_handler);
	inet_diag_unरेजिस्टर(&udp_diag_handler);
पूर्ण

module_init(udp_diag_init);
module_निकास(udp_diag_निकास);
MODULE_LICENSE("GPL");
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_NETLINK, NETLINK_SOCK_DIAG, 2-17 /* AF_INET - IPPROTO_UDP */);
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_NETLINK, NETLINK_SOCK_DIAG, 2-136 /* AF_INET - IPPROTO_UDPLITE */);
