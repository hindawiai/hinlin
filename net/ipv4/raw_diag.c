<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>

#समावेश <linux/inet_diag.h>
#समावेश <linux/sock_diag.h>

#समावेश <net/inet_sock.h>
#समावेश <net/raw.h>
#समावेश <net/rawv6.h>

#अगर_घोषित pr_fmt
# undef pr_fmt
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

अटल काष्ठा raw_hashinfo *
raw_get_hashinfo(स्थिर काष्ठा inet_diag_req_v2 *r)
अणु
	अगर (r->sdiag_family == AF_INET) अणु
		वापस &raw_v4_hashinfo;
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (r->sdiag_family == AF_INET6) अणु
		वापस &raw_v6_hashinfo;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		वापस ERR_PTR(-EINVAL);
	पूर्ण
पूर्ण

/*
 * Due to requirement of not अवरोधing user API we can't simply
 * नाम @pad field in inet_diag_req_v2 काष्ठाure, instead
 * use helper to figure it out.
 */

अटल काष्ठा sock *raw_lookup(काष्ठा net *net, काष्ठा sock *from,
			       स्थिर काष्ठा inet_diag_req_v2 *req)
अणु
	काष्ठा inet_diag_req_raw *r = (व्योम *)req;
	काष्ठा sock *sk = शून्य;

	अगर (r->sdiag_family == AF_INET)
		sk = __raw_v4_lookup(net, from, r->sdiag_raw_protocol,
				     r->id.idiag_dst[0],
				     r->id.idiag_src[0],
				     r->id.idiag_अगर, 0);
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा
		sk = __raw_v6_lookup(net, from, r->sdiag_raw_protocol,
				     (स्थिर काष्ठा in6_addr *)r->id.idiag_src,
				     (स्थिर काष्ठा in6_addr *)r->id.idiag_dst,
				     r->id.idiag_अगर, 0);
#पूर्ण_अगर
	वापस sk;
पूर्ण

अटल काष्ठा sock *raw_sock_get(काष्ठा net *net, स्थिर काष्ठा inet_diag_req_v2 *r)
अणु
	काष्ठा raw_hashinfo *hashinfo = raw_get_hashinfo(r);
	काष्ठा sock *sk = शून्य, *s;
	पूर्णांक slot;

	अगर (IS_ERR(hashinfo))
		वापस ERR_CAST(hashinfo);

	पढ़ो_lock(&hashinfo->lock);
	क्रम (slot = 0; slot < RAW_HTABLE_SIZE; slot++) अणु
		sk_क्रम_each(s, &hashinfo->ht[slot]) अणु
			sk = raw_lookup(net, s, r);
			अगर (sk) अणु
				/*
				 * Grab it and keep until we fill
				 * diag meaage to be reported, so
				 * caller should call sock_put then.
				 * We can करो that because we're keeping
				 * hashinfo->lock here.
				 */
				sock_hold(sk);
				जाओ out_unlock;
			पूर्ण
		पूर्ण
	पूर्ण
out_unlock:
	पढ़ो_unlock(&hashinfo->lock);

	वापस sk ? sk : ERR_PTR(-ENOENT);
पूर्ण

अटल पूर्णांक raw_diag_dump_one(काष्ठा netlink_callback *cb,
			     स्थिर काष्ठा inet_diag_req_v2 *r)
अणु
	काष्ठा sk_buff *in_skb = cb->skb;
	काष्ठा sk_buff *rep;
	काष्ठा sock *sk;
	काष्ठा net *net;
	पूर्णांक err;

	net = sock_net(in_skb->sk);
	sk = raw_sock_get(net, r);
	अगर (IS_ERR(sk))
		वापस PTR_ERR(sk);

	rep = nlmsg_new(nla_total_size(माप(काष्ठा inet_diag_msg)) +
			inet_diag_msg_attrs_size() +
			nla_total_size(माप(काष्ठा inet_diag_meminfo)) + 64,
			GFP_KERNEL);
	अगर (!rep) अणु
		sock_put(sk);
		वापस -ENOMEM;
	पूर्ण

	err = inet_sk_diag_fill(sk, शून्य, rep, cb, r, 0,
				netlink_net_capable(in_skb, CAP_NET_ADMIN));
	sock_put(sk);

	अगर (err < 0) अणु
		kमुक्त_skb(rep);
		वापस err;
	पूर्ण

	err = netlink_unicast(net->diag_nlsk, rep,
			      NETLINK_CB(in_skb).portid,
			      MSG_DONTWAIT);
	अगर (err > 0)
		err = 0;
	वापस err;
पूर्ण

अटल पूर्णांक sk_diag_dump(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			काष्ठा netlink_callback *cb,
			स्थिर काष्ठा inet_diag_req_v2 *r,
			काष्ठा nlattr *bc, bool net_admin)
अणु
	अगर (!inet_diag_bc_sk(bc, sk))
		वापस 0;

	वापस inet_sk_diag_fill(sk, शून्य, skb, cb, r, NLM_F_MULTI, net_admin);
पूर्ण

अटल व्योम raw_diag_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
			  स्थिर काष्ठा inet_diag_req_v2 *r)
अणु
	bool net_admin = netlink_net_capable(cb->skb, CAP_NET_ADMIN);
	काष्ठा raw_hashinfo *hashinfo = raw_get_hashinfo(r);
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा inet_diag_dump_data *cb_data;
	पूर्णांक num, s_num, slot, s_slot;
	काष्ठा sock *sk = शून्य;
	काष्ठा nlattr *bc;

	अगर (IS_ERR(hashinfo))
		वापस;

	cb_data = cb->data;
	bc = cb_data->inet_diag_nla_bc;
	s_slot = cb->args[0];
	num = s_num = cb->args[1];

	पढ़ो_lock(&hashinfo->lock);
	क्रम (slot = s_slot; slot < RAW_HTABLE_SIZE; s_num = 0, slot++) अणु
		num = 0;

		sk_क्रम_each(sk, &hashinfo->ht[slot]) अणु
			काष्ठा inet_sock *inet = inet_sk(sk);

			अगर (!net_eq(sock_net(sk), net))
				जारी;
			अगर (num < s_num)
				जाओ next;
			अगर (sk->sk_family != r->sdiag_family)
				जाओ next;
			अगर (r->id.idiag_sport != inet->inet_sport &&
			    r->id.idiag_sport)
				जाओ next;
			अगर (r->id.idiag_dport != inet->inet_dport &&
			    r->id.idiag_dport)
				जाओ next;
			अगर (sk_diag_dump(sk, skb, cb, r, bc, net_admin) < 0)
				जाओ out_unlock;
next:
			num++;
		पूर्ण
	पूर्ण

out_unlock:
	पढ़ो_unlock(&hashinfo->lock);

	cb->args[0] = slot;
	cb->args[1] = num;
पूर्ण

अटल व्योम raw_diag_get_info(काष्ठा sock *sk, काष्ठा inet_diag_msg *r,
			      व्योम *info)
अणु
	r->idiag_rqueue = sk_rmem_alloc_get(sk);
	r->idiag_wqueue = sk_wmem_alloc_get(sk);
पूर्ण

#अगर_घोषित CONFIG_INET_DIAG_DESTROY
अटल पूर्णांक raw_diag_destroy(काष्ठा sk_buff *in_skb,
			    स्थिर काष्ठा inet_diag_req_v2 *r)
अणु
	काष्ठा net *net = sock_net(in_skb->sk);
	काष्ठा sock *sk;
	पूर्णांक err;

	sk = raw_sock_get(net, r);
	अगर (IS_ERR(sk))
		वापस PTR_ERR(sk);
	err = sock_diag_destroy(sk, ECONNABORTED);
	sock_put(sk);
	वापस err;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा inet_diag_handler raw_diag_handler = अणु
	.dump			= raw_diag_dump,
	.dump_one		= raw_diag_dump_one,
	.idiag_get_info		= raw_diag_get_info,
	.idiag_type		= IPPROTO_RAW,
	.idiag_info_size	= 0,
#अगर_घोषित CONFIG_INET_DIAG_DESTROY
	.destroy		= raw_diag_destroy,
#पूर्ण_अगर
पूर्ण;

अटल व्योम __always_unused __check_inet_diag_req_raw(व्योम)
अणु
	/*
	 * Make sure the two काष्ठाures are identical,
	 * except the @pad field.
	 */
#घोषणा __offset_mismatch(m1, m2)			\
	(दुरत्व(काष्ठा inet_diag_req_v2, m1) !=	\
	 दुरत्व(काष्ठा inet_diag_req_raw, m2))

	BUILD_BUG_ON(माप(काष्ठा inet_diag_req_v2) !=
		     माप(काष्ठा inet_diag_req_raw));
	BUILD_BUG_ON(__offset_mismatch(sdiag_family, sdiag_family));
	BUILD_BUG_ON(__offset_mismatch(sdiag_protocol, sdiag_protocol));
	BUILD_BUG_ON(__offset_mismatch(idiag_ext, idiag_ext));
	BUILD_BUG_ON(__offset_mismatch(pad, sdiag_raw_protocol));
	BUILD_BUG_ON(__offset_mismatch(idiag_states, idiag_states));
	BUILD_BUG_ON(__offset_mismatch(id, id));
#अघोषित __offset_mismatch
पूर्ण

अटल पूर्णांक __init raw_diag_init(व्योम)
अणु
	वापस inet_diag_रेजिस्टर(&raw_diag_handler);
पूर्ण

अटल व्योम __निकास raw_diag_निकास(व्योम)
अणु
	inet_diag_unरेजिस्टर(&raw_diag_handler);
पूर्ण

module_init(raw_diag_init);
module_निकास(raw_diag_निकास);
MODULE_LICENSE("GPL");
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_NETLINK, NETLINK_SOCK_DIAG, 2-255 /* AF_INET - IPPROTO_RAW */);
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_NETLINK, NETLINK_SOCK_DIAG, 10-255 /* AF_INET6 - IPPROTO_RAW */);
