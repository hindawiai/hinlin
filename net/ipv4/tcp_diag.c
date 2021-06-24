<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * tcp_diag.c	Module क्रम monitoring TCP transport protocols sockets.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 */

#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/sock_diag.h>
#समावेश <linux/inet_diag.h>

#समावेश <linux/tcp.h>

#समावेश <net/netlink.h>
#समावेश <net/tcp.h>

अटल व्योम tcp_diag_get_info(काष्ठा sock *sk, काष्ठा inet_diag_msg *r,
			      व्योम *_info)
अणु
	काष्ठा tcp_info *info = _info;

	अगर (inet_sk_state_load(sk) == TCP_LISTEN) अणु
		r->idiag_rqueue = READ_ONCE(sk->sk_ack_backlog);
		r->idiag_wqueue = READ_ONCE(sk->sk_max_ack_backlog);
	पूर्ण अन्यथा अगर (sk->sk_type == SOCK_STREAM) अणु
		स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);

		r->idiag_rqueue = max_t(पूर्णांक, READ_ONCE(tp->rcv_nxt) -
					     READ_ONCE(tp->copied_seq), 0);
		r->idiag_wqueue = READ_ONCE(tp->ग_लिखो_seq) - tp->snd_una;
	पूर्ण
	अगर (info)
		tcp_get_info(sk, info);
पूर्ण

#अगर_घोषित CONFIG_TCP_MD5SIG
अटल व्योम tcp_diag_md5sig_fill(काष्ठा tcp_diag_md5sig *info,
				 स्थिर काष्ठा tcp_md5sig_key *key)
अणु
	info->tcpm_family = key->family;
	info->tcpm_prefixlen = key->prefixlen;
	info->tcpm_keylen = key->keylen;
	स_नकल(info->tcpm_key, key->key, key->keylen);

	अगर (key->family == AF_INET)
		info->tcpm_addr[0] = key->addr.a4.s_addr;
	#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा अगर (key->family == AF_INET6)
		स_नकल(&info->tcpm_addr, &key->addr.a6,
		       माप(info->tcpm_addr));
	#पूर्ण_अगर
पूर्ण

अटल पूर्णांक tcp_diag_put_md5sig(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा tcp_md5sig_info *md5sig)
अणु
	स्थिर काष्ठा tcp_md5sig_key *key;
	काष्ठा tcp_diag_md5sig *info;
	काष्ठा nlattr *attr;
	पूर्णांक md5sig_count = 0;

	hlist_क्रम_each_entry_rcu(key, &md5sig->head, node)
		md5sig_count++;
	अगर (md5sig_count == 0)
		वापस 0;

	attr = nla_reserve(skb, INET_DIAG_MD5SIG,
			   md5sig_count * माप(काष्ठा tcp_diag_md5sig));
	अगर (!attr)
		वापस -EMSGSIZE;

	info = nla_data(attr);
	स_रखो(info, 0, md5sig_count * माप(काष्ठा tcp_diag_md5sig));
	hlist_क्रम_each_entry_rcu(key, &md5sig->head, node) अणु
		tcp_diag_md5sig_fill(info++, key);
		अगर (--md5sig_count == 0)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tcp_diag_put_ulp(काष्ठा sk_buff *skb, काष्ठा sock *sk,
			    स्थिर काष्ठा tcp_ulp_ops *ulp_ops)
अणु
	काष्ठा nlattr *nest;
	पूर्णांक err;

	nest = nla_nest_start_noflag(skb, INET_DIAG_ULP_INFO);
	अगर (!nest)
		वापस -EMSGSIZE;

	err = nla_put_string(skb, INET_ULP_INFO_NAME, ulp_ops->name);
	अगर (err)
		जाओ nla_failure;

	अगर (ulp_ops->get_info)
		err = ulp_ops->get_info(sk, skb);
	अगर (err)
		जाओ nla_failure;

	nla_nest_end(skb, nest);
	वापस 0;

nla_failure:
	nla_nest_cancel(skb, nest);
	वापस err;
पूर्ण

अटल पूर्णांक tcp_diag_get_aux(काष्ठा sock *sk, bool net_admin,
			    काष्ठा sk_buff *skb)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	पूर्णांक err = 0;

#अगर_घोषित CONFIG_TCP_MD5SIG
	अगर (net_admin) अणु
		काष्ठा tcp_md5sig_info *md5sig;

		rcu_पढ़ो_lock();
		md5sig = rcu_dereference(tcp_sk(sk)->md5sig_info);
		अगर (md5sig)
			err = tcp_diag_put_md5sig(skb, md5sig);
		rcu_पढ़ो_unlock();
		अगर (err < 0)
			वापस err;
	पूर्ण
#पूर्ण_अगर

	अगर (net_admin) अणु
		स्थिर काष्ठा tcp_ulp_ops *ulp_ops;

		ulp_ops = icsk->icsk_ulp_ops;
		अगर (ulp_ops)
			err = tcp_diag_put_ulp(skb, sk, ulp_ops);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल माप_प्रकार tcp_diag_get_aux_size(काष्ठा sock *sk, bool net_admin)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	माप_प्रकार size = 0;

#अगर_घोषित CONFIG_TCP_MD5SIG
	अगर (net_admin && sk_fullsock(sk)) अणु
		स्थिर काष्ठा tcp_md5sig_info *md5sig;
		स्थिर काष्ठा tcp_md5sig_key *key;
		माप_प्रकार md5sig_count = 0;

		rcu_पढ़ो_lock();
		md5sig = rcu_dereference(tcp_sk(sk)->md5sig_info);
		अगर (md5sig) अणु
			hlist_क्रम_each_entry_rcu(key, &md5sig->head, node)
				md5sig_count++;
		पूर्ण
		rcu_पढ़ो_unlock();
		size += nla_total_size(md5sig_count *
				       माप(काष्ठा tcp_diag_md5sig));
	पूर्ण
#पूर्ण_अगर

	अगर (net_admin && sk_fullsock(sk)) अणु
		स्थिर काष्ठा tcp_ulp_ops *ulp_ops;

		ulp_ops = icsk->icsk_ulp_ops;
		अगर (ulp_ops) अणु
			size += nla_total_size(0) +
				nla_total_size(TCP_ULP_NAME_MAX);
			अगर (ulp_ops->get_info_size)
				size += ulp_ops->get_info_size(sk);
		पूर्ण
	पूर्ण
	वापस size;
पूर्ण

अटल व्योम tcp_diag_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
			  स्थिर काष्ठा inet_diag_req_v2 *r)
अणु
	inet_diag_dump_icsk(&tcp_hashinfo, skb, cb, r);
पूर्ण

अटल पूर्णांक tcp_diag_dump_one(काष्ठा netlink_callback *cb,
			     स्थिर काष्ठा inet_diag_req_v2 *req)
अणु
	वापस inet_diag_dump_one_icsk(&tcp_hashinfo, cb, req);
पूर्ण

#अगर_घोषित CONFIG_INET_DIAG_DESTROY
अटल पूर्णांक tcp_diag_destroy(काष्ठा sk_buff *in_skb,
			    स्थिर काष्ठा inet_diag_req_v2 *req)
अणु
	काष्ठा net *net = sock_net(in_skb->sk);
	काष्ठा sock *sk = inet_diag_find_one_icsk(net, &tcp_hashinfo, req);
	पूर्णांक err;

	अगर (IS_ERR(sk))
		वापस PTR_ERR(sk);

	err = sock_diag_destroy(sk, ECONNABORTED);

	sock_gen_put(sk);

	वापस err;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा inet_diag_handler tcp_diag_handler = अणु
	.dump			= tcp_diag_dump,
	.dump_one		= tcp_diag_dump_one,
	.idiag_get_info		= tcp_diag_get_info,
	.idiag_get_aux		= tcp_diag_get_aux,
	.idiag_get_aux_size	= tcp_diag_get_aux_size,
	.idiag_type		= IPPROTO_TCP,
	.idiag_info_size	= माप(काष्ठा tcp_info),
#अगर_घोषित CONFIG_INET_DIAG_DESTROY
	.destroy		= tcp_diag_destroy,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init tcp_diag_init(व्योम)
अणु
	वापस inet_diag_रेजिस्टर(&tcp_diag_handler);
पूर्ण

अटल व्योम __निकास tcp_diag_निकास(व्योम)
अणु
	inet_diag_unरेजिस्टर(&tcp_diag_handler);
पूर्ण

module_init(tcp_diag_init);
module_निकास(tcp_diag_निकास);
MODULE_LICENSE("GPL");
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_NETLINK, NETLINK_SOCK_DIAG, 2-6 /* AF_INET - IPPROTO_TCP */);
