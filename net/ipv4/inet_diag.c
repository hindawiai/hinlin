<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * inet_diag.c	Module क्रम monitoring INET transport protocols sockets.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/cache.h>
#समावेश <linux/init.h>
#समावेश <linux/समय.स>

#समावेश <net/icmp.h>
#समावेश <net/tcp.h>
#समावेश <net/ipv6.h>
#समावेश <net/inet_common.h>
#समावेश <net/inet_connection_sock.h>
#समावेश <net/inet_hashtables.h>
#समावेश <net/inet_समयरुको_sock.h>
#समावेश <net/inet6_hashtables.h>
#समावेश <net/bpf_sk_storage.h>
#समावेश <net/netlink.h>

#समावेश <linux/inet.h>
#समावेश <linux/मानकघोष.स>

#समावेश <linux/inet_diag.h>
#समावेश <linux/sock_diag.h>

अटल स्थिर काष्ठा inet_diag_handler **inet_diag_table;

काष्ठा inet_diag_entry अणु
	स्थिर __be32 *saddr;
	स्थिर __be32 *daddr;
	u16 sport;
	u16 dport;
	u16 family;
	u16 userlocks;
	u32 अगरindex;
	u32 mark;
#अगर_घोषित CONFIG_SOCK_CGROUP_DATA
	u64 cgroup_id;
#पूर्ण_अगर
पूर्ण;

अटल DEFINE_MUTEX(inet_diag_table_mutex);

अटल स्थिर काष्ठा inet_diag_handler *inet_diag_lock_handler(पूर्णांक proto)
अणु
	अगर (proto < 0 || proto >= IPPROTO_MAX) अणु
		mutex_lock(&inet_diag_table_mutex);
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	अगर (!inet_diag_table[proto])
		sock_load_diag_module(AF_INET, proto);

	mutex_lock(&inet_diag_table_mutex);
	अगर (!inet_diag_table[proto])
		वापस ERR_PTR(-ENOENT);

	वापस inet_diag_table[proto];
पूर्ण

अटल व्योम inet_diag_unlock_handler(स्थिर काष्ठा inet_diag_handler *handler)
अणु
	mutex_unlock(&inet_diag_table_mutex);
पूर्ण

व्योम inet_diag_msg_common_fill(काष्ठा inet_diag_msg *r, काष्ठा sock *sk)
अणु
	r->idiag_family = sk->sk_family;

	r->id.idiag_sport = htons(sk->sk_num);
	r->id.idiag_dport = sk->sk_dport;
	r->id.idiag_अगर = sk->sk_bound_dev_अगर;
	sock_diag_save_cookie(sk, r->id.idiag_cookie);

#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (sk->sk_family == AF_INET6) अणु
		*(काष्ठा in6_addr *)r->id.idiag_src = sk->sk_v6_rcv_saddr;
		*(काष्ठा in6_addr *)r->id.idiag_dst = sk->sk_v6_daddr;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
	स_रखो(&r->id.idiag_src, 0, माप(r->id.idiag_src));
	स_रखो(&r->id.idiag_dst, 0, माप(r->id.idiag_dst));

	r->id.idiag_src[0] = sk->sk_rcv_saddr;
	r->id.idiag_dst[0] = sk->sk_daddr;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(inet_diag_msg_common_fill);

अटल माप_प्रकार inet_sk_attr_size(काष्ठा sock *sk,
				स्थिर काष्ठा inet_diag_req_v2 *req,
				bool net_admin)
अणु
	स्थिर काष्ठा inet_diag_handler *handler;
	माप_प्रकार aux = 0;

	handler = inet_diag_table[req->sdiag_protocol];
	अगर (handler && handler->idiag_get_aux_size)
		aux = handler->idiag_get_aux_size(sk, net_admin);

	वापस	  nla_total_size(माप(काष्ठा tcp_info))
		+ nla_total_size(माप(काष्ठा inet_diag_msg))
		+ inet_diag_msg_attrs_size()
		+ nla_total_size(माप(काष्ठा inet_diag_meminfo))
		+ nla_total_size(SK_MEMINFO_VARS * माप(u32))
		+ nla_total_size(TCP_CA_NAME_MAX)
		+ nla_total_size(माप(काष्ठा tcpvegas_info))
		+ aux
		+ 64;
पूर्ण

पूर्णांक inet_diag_msg_attrs_fill(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			     काष्ठा inet_diag_msg *r, पूर्णांक ext,
			     काष्ठा user_namespace *user_ns,
			     bool net_admin)
अणु
	स्थिर काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा inet_diag_sockopt inet_sockopt;

	अगर (nla_put_u8(skb, INET_DIAG_SHUTDOWN, sk->sk_shutकरोwn))
		जाओ errout;

	/* IPv6 dual-stack sockets use inet->tos क्रम IPv4 connections,
	 * hence this needs to be included regardless of socket family.
	 */
	अगर (ext & (1 << (INET_DIAG_TOS - 1)))
		अगर (nla_put_u8(skb, INET_DIAG_TOS, inet->tos) < 0)
			जाओ errout;

#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (r->idiag_family == AF_INET6) अणु
		अगर (ext & (1 << (INET_DIAG_TCLASS - 1)))
			अगर (nla_put_u8(skb, INET_DIAG_TCLASS,
				       inet6_sk(sk)->tclass) < 0)
				जाओ errout;

		अगर (((1 << sk->sk_state) & (TCPF_LISTEN | TCPF_CLOSE)) &&
		    nla_put_u8(skb, INET_DIAG_SKV6ONLY, ipv6_only_sock(sk)))
			जाओ errout;
	पूर्ण
#पूर्ण_अगर

	अगर (net_admin && nla_put_u32(skb, INET_DIAG_MARK, sk->sk_mark))
		जाओ errout;

	अगर (ext & (1 << (INET_DIAG_CLASS_ID - 1)) ||
	    ext & (1 << (INET_DIAG_TCLASS - 1))) अणु
		u32 classid = 0;

#अगर_घोषित CONFIG_SOCK_CGROUP_DATA
		classid = sock_cgroup_classid(&sk->sk_cgrp_data);
#पूर्ण_अगर
		/* Fallback to socket priority अगर class id isn't set.
		 * Classful qdiscs use it as direct reference to class.
		 * For cgroup2 classid is always zero.
		 */
		अगर (!classid)
			classid = sk->sk_priority;

		अगर (nla_put_u32(skb, INET_DIAG_CLASS_ID, classid))
			जाओ errout;
	पूर्ण

#अगर_घोषित CONFIG_SOCK_CGROUP_DATA
	अगर (nla_put_u64_64bit(skb, INET_DIAG_CGROUP_ID,
			      cgroup_id(sock_cgroup_ptr(&sk->sk_cgrp_data)),
			      INET_DIAG_PAD))
		जाओ errout;
#पूर्ण_अगर

	r->idiag_uid = from_kuid_munged(user_ns, sock_i_uid(sk));
	r->idiag_inode = sock_i_ino(sk);

	स_रखो(&inet_sockopt, 0, माप(inet_sockopt));
	inet_sockopt.recverr	= inet->recverr;
	inet_sockopt.is_icsk	= inet->is_icsk;
	inet_sockopt.मुक्तbind	= inet->मुक्तbind;
	inet_sockopt.hdrincl	= inet->hdrincl;
	inet_sockopt.mc_loop	= inet->mc_loop;
	inet_sockopt.transparent = inet->transparent;
	inet_sockopt.mc_all	= inet->mc_all;
	inet_sockopt.nodefrag	= inet->nodefrag;
	inet_sockopt.bind_address_no_port = inet->bind_address_no_port;
	inet_sockopt.recverr_rfc4884 = inet->recverr_rfc4884;
	inet_sockopt.defer_connect = inet->defer_connect;
	अगर (nla_put(skb, INET_DIAG_SOCKOPT, माप(inet_sockopt),
		    &inet_sockopt))
		जाओ errout;

	वापस 0;
errout:
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(inet_diag_msg_attrs_fill);

अटल पूर्णांक inet_diag_parse_attrs(स्थिर काष्ठा nlmsghdr *nlh, पूर्णांक hdrlen,
				 काष्ठा nlattr **req_nlas)
अणु
	काष्ठा nlattr *nla;
	पूर्णांक reमुख्यing;

	nlmsg_क्रम_each_attr(nla, nlh, hdrlen, reमुख्यing) अणु
		पूर्णांक type = nla_type(nla);

		अगर (type == INET_DIAG_REQ_PROTOCOL && nla_len(nla) != माप(u32))
			वापस -EINVAL;

		अगर (type < __INET_DIAG_REQ_MAX)
			req_nlas[type] = nla;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक inet_diag_get_protocol(स्थिर काष्ठा inet_diag_req_v2 *req,
				  स्थिर काष्ठा inet_diag_dump_data *data)
अणु
	अगर (data->req_nlas[INET_DIAG_REQ_PROTOCOL])
		वापस nla_get_u32(data->req_nlas[INET_DIAG_REQ_PROTOCOL]);
	वापस req->sdiag_protocol;
पूर्ण

#घोषणा MAX_DUMP_ALLOC_SIZE (KMALLOC_MAX_SIZE - SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)))

पूर्णांक inet_sk_diag_fill(काष्ठा sock *sk, काष्ठा inet_connection_sock *icsk,
		      काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
		      स्थिर काष्ठा inet_diag_req_v2 *req,
		      u16 nlmsg_flags, bool net_admin)
अणु
	स्थिर काष्ठा tcp_congestion_ops *ca_ops;
	स्थिर काष्ठा inet_diag_handler *handler;
	काष्ठा inet_diag_dump_data *cb_data;
	पूर्णांक ext = req->idiag_ext;
	काष्ठा inet_diag_msg *r;
	काष्ठा nlmsghdr  *nlh;
	काष्ठा nlattr *attr;
	व्योम *info = शून्य;

	cb_data = cb->data;
	handler = inet_diag_table[inet_diag_get_protocol(req, cb_data)];
	BUG_ON(!handler);

	nlh = nlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			cb->nlh->nlmsg_type, माप(*r), nlmsg_flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	r = nlmsg_data(nlh);
	BUG_ON(!sk_fullsock(sk));

	inet_diag_msg_common_fill(r, sk);
	r->idiag_state = sk->sk_state;
	r->idiag_समयr = 0;
	r->idiag_retrans = 0;

	अगर (inet_diag_msg_attrs_fill(sk, skb, r, ext,
				     sk_user_ns(NETLINK_CB(cb->skb).sk),
				     net_admin))
		जाओ errout;

	अगर (ext & (1 << (INET_DIAG_MEMINFO - 1))) अणु
		काष्ठा inet_diag_meminfo minfo = अणु
			.idiag_rmem = sk_rmem_alloc_get(sk),
			.idiag_wmem = READ_ONCE(sk->sk_wmem_queued),
			.idiag_fmem = sk->sk_क्रमward_alloc,
			.idiag_पंचांगem = sk_wmem_alloc_get(sk),
		पूर्ण;

		अगर (nla_put(skb, INET_DIAG_MEMINFO, माप(minfo), &minfo) < 0)
			जाओ errout;
	पूर्ण

	अगर (ext & (1 << (INET_DIAG_SKMEMINFO - 1)))
		अगर (sock_diag_put_meminfo(sk, skb, INET_DIAG_SKMEMINFO))
			जाओ errout;

	/*
	 * RAW sockets might have user-defined protocols asचिन्हित,
	 * so report the one supplied on socket creation.
	 */
	अगर (sk->sk_type == SOCK_RAW) अणु
		अगर (nla_put_u8(skb, INET_DIAG_PROTOCOL, sk->sk_protocol))
			जाओ errout;
	पूर्ण

	अगर (!icsk) अणु
		handler->idiag_get_info(sk, r, शून्य);
		जाओ out;
	पूर्ण

	अगर (icsk->icsk_pending == ICSK_TIME_RETRANS ||
	    icsk->icsk_pending == ICSK_TIME_REO_TIMEOUT ||
	    icsk->icsk_pending == ICSK_TIME_LOSS_PROBE) अणु
		r->idiag_समयr = 1;
		r->idiag_retrans = icsk->icsk_retransmits;
		r->idiag_expires =
			jअगरfies_delta_to_msecs(icsk->icsk_समयout - jअगरfies);
	पूर्ण अन्यथा अगर (icsk->icsk_pending == ICSK_TIME_PROBE0) अणु
		r->idiag_समयr = 4;
		r->idiag_retrans = icsk->icsk_probes_out;
		r->idiag_expires =
			jअगरfies_delta_to_msecs(icsk->icsk_समयout - jअगरfies);
	पूर्ण अन्यथा अगर (समयr_pending(&sk->sk_समयr)) अणु
		r->idiag_समयr = 2;
		r->idiag_retrans = icsk->icsk_probes_out;
		r->idiag_expires =
			jअगरfies_delta_to_msecs(sk->sk_समयr.expires - jअगरfies);
	पूर्ण अन्यथा अणु
		r->idiag_समयr = 0;
		r->idiag_expires = 0;
	पूर्ण

	अगर ((ext & (1 << (INET_DIAG_INFO - 1))) && handler->idiag_info_size) अणु
		attr = nla_reserve_64bit(skb, INET_DIAG_INFO,
					 handler->idiag_info_size,
					 INET_DIAG_PAD);
		अगर (!attr)
			जाओ errout;

		info = nla_data(attr);
	पूर्ण

	अगर (ext & (1 << (INET_DIAG_CONG - 1))) अणु
		पूर्णांक err = 0;

		rcu_पढ़ो_lock();
		ca_ops = READ_ONCE(icsk->icsk_ca_ops);
		अगर (ca_ops)
			err = nla_put_string(skb, INET_DIAG_CONG, ca_ops->name);
		rcu_पढ़ो_unlock();
		अगर (err < 0)
			जाओ errout;
	पूर्ण

	handler->idiag_get_info(sk, r, info);

	अगर (ext & (1 << (INET_DIAG_INFO - 1)) && handler->idiag_get_aux)
		अगर (handler->idiag_get_aux(sk, net_admin, skb) < 0)
			जाओ errout;

	अगर (sk->sk_state < TCP_TIME_WAIT) अणु
		जोड़ tcp_cc_info info;
		माप_प्रकार sz = 0;
		पूर्णांक attr;

		rcu_पढ़ो_lock();
		ca_ops = READ_ONCE(icsk->icsk_ca_ops);
		अगर (ca_ops && ca_ops->get_info)
			sz = ca_ops->get_info(sk, ext, &attr, &info);
		rcu_पढ़ो_unlock();
		अगर (sz && nla_put(skb, attr, sz, &info) < 0)
			जाओ errout;
	पूर्ण

	/* Keep it at the end क्रम potential retry with a larger skb,
	 * or अन्यथा करो best-efक्रमt fitting, which is only करोne क्रम the
	 * first_nlmsg.
	 */
	अगर (cb_data->bpf_stg_diag) अणु
		bool first_nlmsg = ((अचिन्हित अक्षर *)nlh == skb->data);
		अचिन्हित पूर्णांक prev_min_dump_alloc;
		अचिन्हित पूर्णांक total_nla_size = 0;
		अचिन्हित पूर्णांक msg_len;
		पूर्णांक err;

		msg_len = skb_tail_poपूर्णांकer(skb) - (अचिन्हित अक्षर *)nlh;
		err = bpf_sk_storage_diag_put(cb_data->bpf_stg_diag, sk, skb,
					      INET_DIAG_SK_BPF_STORAGES,
					      &total_nla_size);

		अगर (!err)
			जाओ out;

		total_nla_size += msg_len;
		prev_min_dump_alloc = cb->min_dump_alloc;
		अगर (total_nla_size > prev_min_dump_alloc)
			cb->min_dump_alloc = min_t(u32, total_nla_size,
						   MAX_DUMP_ALLOC_SIZE);

		अगर (!first_nlmsg)
			जाओ errout;

		अगर (cb->min_dump_alloc > prev_min_dump_alloc)
			/* Retry with pskb_expand_head() with
			 * __GFP_सूचीECT_RECLAIM
			 */
			जाओ errout;

		WARN_ON_ONCE(total_nla_size <= prev_min_dump_alloc);

		/* Send what we have क्रम this sk
		 * and move on to the next sk in the following
		 * dump()
		 */
	पूर्ण

out:
	nlmsg_end(skb, nlh);
	वापस 0;

errout:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण
EXPORT_SYMBOL_GPL(inet_sk_diag_fill);

अटल पूर्णांक inet_twsk_diag_fill(काष्ठा sock *sk,
			       काष्ठा sk_buff *skb,
			       काष्ठा netlink_callback *cb,
			       u16 nlmsg_flags)
अणु
	काष्ठा inet_समयरुको_sock *tw = inet_twsk(sk);
	काष्ठा inet_diag_msg *r;
	काष्ठा nlmsghdr *nlh;
	दीर्घ पंचांगo;

	nlh = nlmsg_put(skb, NETLINK_CB(cb->skb).portid,
			cb->nlh->nlmsg_seq, cb->nlh->nlmsg_type,
			माप(*r), nlmsg_flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	r = nlmsg_data(nlh);
	BUG_ON(tw->tw_state != TCP_TIME_WAIT);

	inet_diag_msg_common_fill(r, sk);
	r->idiag_retrans      = 0;

	r->idiag_state	      = tw->tw_substate;
	r->idiag_समयr	      = 3;
	पंचांगo = tw->tw_समयr.expires - jअगरfies;
	r->idiag_expires      = jअगरfies_delta_to_msecs(पंचांगo);
	r->idiag_rqueue	      = 0;
	r->idiag_wqueue	      = 0;
	r->idiag_uid	      = 0;
	r->idiag_inode	      = 0;

	nlmsg_end(skb, nlh);
	वापस 0;
पूर्ण

अटल पूर्णांक inet_req_diag_fill(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			      काष्ठा netlink_callback *cb,
			      u16 nlmsg_flags, bool net_admin)
अणु
	काष्ठा request_sock *reqsk = inet_reqsk(sk);
	काष्ठा inet_diag_msg *r;
	काष्ठा nlmsghdr *nlh;
	दीर्घ पंचांगo;

	nlh = nlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			cb->nlh->nlmsg_type, माप(*r), nlmsg_flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	r = nlmsg_data(nlh);
	inet_diag_msg_common_fill(r, sk);
	r->idiag_state = TCP_SYN_RECV;
	r->idiag_समयr = 1;
	r->idiag_retrans = reqsk->num_retrans;

	BUILD_BUG_ON(दुरत्व(काष्ठा inet_request_sock, ir_cookie) !=
		     दुरत्व(काष्ठा sock, sk_cookie));

	पंचांगo = inet_reqsk(sk)->rsk_समयr.expires - jअगरfies;
	r->idiag_expires = jअगरfies_delta_to_msecs(पंचांगo);
	r->idiag_rqueue	= 0;
	r->idiag_wqueue	= 0;
	r->idiag_uid	= 0;
	r->idiag_inode	= 0;

	अगर (net_admin && nla_put_u32(skb, INET_DIAG_MARK,
				     inet_rsk(reqsk)->ir_mark)) अणु
		nlmsg_cancel(skb, nlh);
		वापस -EMSGSIZE;
	पूर्ण

	nlmsg_end(skb, nlh);
	वापस 0;
पूर्ण

अटल पूर्णांक sk_diag_fill(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			काष्ठा netlink_callback *cb,
			स्थिर काष्ठा inet_diag_req_v2 *r,
			u16 nlmsg_flags, bool net_admin)
अणु
	अगर (sk->sk_state == TCP_TIME_WAIT)
		वापस inet_twsk_diag_fill(sk, skb, cb, nlmsg_flags);

	अगर (sk->sk_state == TCP_NEW_SYN_RECV)
		वापस inet_req_diag_fill(sk, skb, cb, nlmsg_flags, net_admin);

	वापस inet_sk_diag_fill(sk, inet_csk(sk), skb, cb, r, nlmsg_flags,
				 net_admin);
पूर्ण

काष्ठा sock *inet_diag_find_one_icsk(काष्ठा net *net,
				     काष्ठा inet_hashinfo *hashinfo,
				     स्थिर काष्ठा inet_diag_req_v2 *req)
अणु
	काष्ठा sock *sk;

	rcu_पढ़ो_lock();
	अगर (req->sdiag_family == AF_INET)
		sk = inet_lookup(net, hashinfo, शून्य, 0, req->id.idiag_dst[0],
				 req->id.idiag_dport, req->id.idiag_src[0],
				 req->id.idiag_sport, req->id.idiag_अगर);
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा अगर (req->sdiag_family == AF_INET6) अणु
		अगर (ipv6_addr_v4mapped((काष्ठा in6_addr *)req->id.idiag_dst) &&
		    ipv6_addr_v4mapped((काष्ठा in6_addr *)req->id.idiag_src))
			sk = inet_lookup(net, hashinfo, शून्य, 0, req->id.idiag_dst[3],
					 req->id.idiag_dport, req->id.idiag_src[3],
					 req->id.idiag_sport, req->id.idiag_अगर);
		अन्यथा
			sk = inet6_lookup(net, hashinfo, शून्य, 0,
					  (काष्ठा in6_addr *)req->id.idiag_dst,
					  req->id.idiag_dport,
					  (काष्ठा in6_addr *)req->id.idiag_src,
					  req->id.idiag_sport,
					  req->id.idiag_अगर);
	पूर्ण
#पूर्ण_अगर
	अन्यथा अणु
		rcu_पढ़ो_unlock();
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (!sk)
		वापस ERR_PTR(-ENOENT);

	अगर (sock_diag_check_cookie(sk, req->id.idiag_cookie)) अणु
		sock_gen_put(sk);
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	वापस sk;
पूर्ण
EXPORT_SYMBOL_GPL(inet_diag_find_one_icsk);

पूर्णांक inet_diag_dump_one_icsk(काष्ठा inet_hashinfo *hashinfo,
			    काष्ठा netlink_callback *cb,
			    स्थिर काष्ठा inet_diag_req_v2 *req)
अणु
	काष्ठा sk_buff *in_skb = cb->skb;
	bool net_admin = netlink_net_capable(in_skb, CAP_NET_ADMIN);
	काष्ठा net *net = sock_net(in_skb->sk);
	काष्ठा sk_buff *rep;
	काष्ठा sock *sk;
	पूर्णांक err;

	sk = inet_diag_find_one_icsk(net, hashinfo, req);
	अगर (IS_ERR(sk))
		वापस PTR_ERR(sk);

	rep = nlmsg_new(inet_sk_attr_size(sk, req, net_admin), GFP_KERNEL);
	अगर (!rep) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	err = sk_diag_fill(sk, rep, cb, req, 0, net_admin);
	अगर (err < 0) अणु
		WARN_ON(err == -EMSGSIZE);
		nlmsg_मुक्त(rep);
		जाओ out;
	पूर्ण
	err = netlink_unicast(net->diag_nlsk, rep, NETLINK_CB(in_skb).portid,
			      MSG_DONTWAIT);
	अगर (err > 0)
		err = 0;

out:
	अगर (sk)
		sock_gen_put(sk);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(inet_diag_dump_one_icsk);

अटल पूर्णांक inet_diag_cmd_exact(पूर्णांक cmd, काष्ठा sk_buff *in_skb,
			       स्थिर काष्ठा nlmsghdr *nlh,
			       पूर्णांक hdrlen,
			       स्थिर काष्ठा inet_diag_req_v2 *req)
अणु
	स्थिर काष्ठा inet_diag_handler *handler;
	काष्ठा inet_diag_dump_data dump_data;
	पूर्णांक err, protocol;

	स_रखो(&dump_data, 0, माप(dump_data));
	err = inet_diag_parse_attrs(nlh, hdrlen, dump_data.req_nlas);
	अगर (err)
		वापस err;

	protocol = inet_diag_get_protocol(req, &dump_data);

	handler = inet_diag_lock_handler(protocol);
	अगर (IS_ERR(handler)) अणु
		err = PTR_ERR(handler);
	पूर्ण अन्यथा अगर (cmd == SOCK_DIAG_BY_FAMILY) अणु
		काष्ठा netlink_callback cb = अणु
			.nlh = nlh,
			.skb = in_skb,
			.data = &dump_data,
		पूर्ण;
		err = handler->dump_one(&cb, req);
	पूर्ण अन्यथा अगर (cmd == SOCK_DESTROY && handler->destroy) अणु
		err = handler->destroy(in_skb, req);
	पूर्ण अन्यथा अणु
		err = -EOPNOTSUPP;
	पूर्ण
	inet_diag_unlock_handler(handler);

	वापस err;
पूर्ण

अटल पूर्णांक bitstring_match(स्थिर __be32 *a1, स्थिर __be32 *a2, पूर्णांक bits)
अणु
	पूर्णांक words = bits >> 5;

	bits &= 0x1f;

	अगर (words) अणु
		अगर (स_भेद(a1, a2, words << 2))
			वापस 0;
	पूर्ण
	अगर (bits) अणु
		__be32 w1, w2;
		__be32 mask;

		w1 = a1[words];
		w2 = a2[words];

		mask = htonl((0xffffffff) << (32 - bits));

		अगर ((w1 ^ w2) & mask)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक inet_diag_bc_run(स्थिर काष्ठा nlattr *_bc,
			    स्थिर काष्ठा inet_diag_entry *entry)
अणु
	स्थिर व्योम *bc = nla_data(_bc);
	पूर्णांक len = nla_len(_bc);

	जबतक (len > 0) अणु
		पूर्णांक yes = 1;
		स्थिर काष्ठा inet_diag_bc_op *op = bc;

		चयन (op->code) अणु
		हाल INET_DIAG_BC_NOP:
			अवरोध;
		हाल INET_DIAG_BC_JMP:
			yes = 0;
			अवरोध;
		हाल INET_DIAG_BC_S_EQ:
			yes = entry->sport == op[1].no;
			अवरोध;
		हाल INET_DIAG_BC_S_GE:
			yes = entry->sport >= op[1].no;
			अवरोध;
		हाल INET_DIAG_BC_S_LE:
			yes = entry->sport <= op[1].no;
			अवरोध;
		हाल INET_DIAG_BC_D_EQ:
			yes = entry->dport == op[1].no;
			अवरोध;
		हाल INET_DIAG_BC_D_GE:
			yes = entry->dport >= op[1].no;
			अवरोध;
		हाल INET_DIAG_BC_D_LE:
			yes = entry->dport <= op[1].no;
			अवरोध;
		हाल INET_DIAG_BC_AUTO:
			yes = !(entry->userlocks & SOCK_BINDPORT_LOCK);
			अवरोध;
		हाल INET_DIAG_BC_S_COND:
		हाल INET_DIAG_BC_D_COND: अणु
			स्थिर काष्ठा inet_diag_hostcond *cond;
			स्थिर __be32 *addr;

			cond = (स्थिर काष्ठा inet_diag_hostcond *)(op + 1);
			अगर (cond->port != -1 &&
			    cond->port != (op->code == INET_DIAG_BC_S_COND ?
					     entry->sport : entry->dport)) अणु
				yes = 0;
				अवरोध;
			पूर्ण

			अगर (op->code == INET_DIAG_BC_S_COND)
				addr = entry->saddr;
			अन्यथा
				addr = entry->daddr;

			अगर (cond->family != AF_UNSPEC &&
			    cond->family != entry->family) अणु
				अगर (entry->family == AF_INET6 &&
				    cond->family == AF_INET) अणु
					अगर (addr[0] == 0 && addr[1] == 0 &&
					    addr[2] == htonl(0xffff) &&
					    bitstring_match(addr + 3,
							    cond->addr,
							    cond->prefix_len))
						अवरोध;
				पूर्ण
				yes = 0;
				अवरोध;
			पूर्ण

			अगर (cond->prefix_len == 0)
				अवरोध;
			अगर (bitstring_match(addr, cond->addr,
					    cond->prefix_len))
				अवरोध;
			yes = 0;
			अवरोध;
		पूर्ण
		हाल INET_DIAG_BC_DEV_COND: अणु
			u32 अगरindex;

			अगरindex = *((स्थिर u32 *)(op + 1));
			अगर (अगरindex != entry->अगरindex)
				yes = 0;
			अवरोध;
		पूर्ण
		हाल INET_DIAG_BC_MARK_COND: अणु
			काष्ठा inet_diag_markcond *cond;

			cond = (काष्ठा inet_diag_markcond *)(op + 1);
			अगर ((entry->mark & cond->mask) != cond->mark)
				yes = 0;
			अवरोध;
		पूर्ण
#अगर_घोषित CONFIG_SOCK_CGROUP_DATA
		हाल INET_DIAG_BC_CGROUP_COND: अणु
			u64 cgroup_id;

			cgroup_id = get_unaligned((स्थिर u64 *)(op + 1));
			अगर (cgroup_id != entry->cgroup_id)
				yes = 0;
			अवरोध;
		पूर्ण
#पूर्ण_अगर
		पूर्ण

		अगर (yes) अणु
			len -= op->yes;
			bc += op->yes;
		पूर्ण अन्यथा अणु
			len -= op->no;
			bc += op->no;
		पूर्ण
	पूर्ण
	वापस len == 0;
पूर्ण

/* This helper is available क्रम all sockets (ESTABLISH, TIMEWAIT, SYN_RECV)
 */
अटल व्योम entry_fill_addrs(काष्ठा inet_diag_entry *entry,
			     स्थिर काष्ठा sock *sk)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (sk->sk_family == AF_INET6) अणु
		entry->saddr = sk->sk_v6_rcv_saddr.s6_addr32;
		entry->daddr = sk->sk_v6_daddr.s6_addr32;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		entry->saddr = &sk->sk_rcv_saddr;
		entry->daddr = &sk->sk_daddr;
	पूर्ण
पूर्ण

पूर्णांक inet_diag_bc_sk(स्थिर काष्ठा nlattr *bc, काष्ठा sock *sk)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा inet_diag_entry entry;

	अगर (!bc)
		वापस 1;

	entry.family = sk->sk_family;
	entry_fill_addrs(&entry, sk);
	entry.sport = inet->inet_num;
	entry.dport = ntohs(inet->inet_dport);
	entry.अगरindex = sk->sk_bound_dev_अगर;
	entry.userlocks = sk_fullsock(sk) ? sk->sk_userlocks : 0;
	अगर (sk_fullsock(sk))
		entry.mark = sk->sk_mark;
	अन्यथा अगर (sk->sk_state == TCP_NEW_SYN_RECV)
		entry.mark = inet_rsk(inet_reqsk(sk))->ir_mark;
	अन्यथा
		entry.mark = 0;
#अगर_घोषित CONFIG_SOCK_CGROUP_DATA
	entry.cgroup_id = sk_fullsock(sk) ?
		cgroup_id(sock_cgroup_ptr(&sk->sk_cgrp_data)) : 0;
#पूर्ण_अगर

	वापस inet_diag_bc_run(bc, &entry);
पूर्ण
EXPORT_SYMBOL_GPL(inet_diag_bc_sk);

अटल पूर्णांक valid_cc(स्थिर व्योम *bc, पूर्णांक len, पूर्णांक cc)
अणु
	जबतक (len >= 0) अणु
		स्थिर काष्ठा inet_diag_bc_op *op = bc;

		अगर (cc > len)
			वापस 0;
		अगर (cc == len)
			वापस 1;
		अगर (op->yes < 4 || op->yes & 3)
			वापस 0;
		len -= op->yes;
		bc  += op->yes;
	पूर्ण
	वापस 0;
पूर्ण

/* data is u32 अगरindex */
अटल bool valid_devcond(स्थिर काष्ठा inet_diag_bc_op *op, पूर्णांक len,
			  पूर्णांक *min_len)
अणु
	/* Check अगरindex space. */
	*min_len += माप(u32);
	अगर (len < *min_len)
		वापस false;

	वापस true;
पूर्ण
/* Validate an inet_diag_hostcond. */
अटल bool valid_hostcond(स्थिर काष्ठा inet_diag_bc_op *op, पूर्णांक len,
			   पूर्णांक *min_len)
अणु
	काष्ठा inet_diag_hostcond *cond;
	पूर्णांक addr_len;

	/* Check hostcond space. */
	*min_len += माप(काष्ठा inet_diag_hostcond);
	अगर (len < *min_len)
		वापस false;
	cond = (काष्ठा inet_diag_hostcond *)(op + 1);

	/* Check address family and address length. */
	चयन (cond->family) अणु
	हाल AF_UNSPEC:
		addr_len = 0;
		अवरोध;
	हाल AF_INET:
		addr_len = माप(काष्ठा in_addr);
		अवरोध;
	हाल AF_INET6:
		addr_len = माप(काष्ठा in6_addr);
		अवरोध;
	शेष:
		वापस false;
	पूर्ण
	*min_len += addr_len;
	अगर (len < *min_len)
		वापस false;

	/* Check prefix length (in bits) vs address length (in bytes). */
	अगर (cond->prefix_len > 8 * addr_len)
		वापस false;

	वापस true;
पूर्ण

/* Validate a port comparison चालक. */
अटल bool valid_port_comparison(स्थिर काष्ठा inet_diag_bc_op *op,
				  पूर्णांक len, पूर्णांक *min_len)
अणु
	/* Port comparisons put the port in a follow-on inet_diag_bc_op. */
	*min_len += माप(काष्ठा inet_diag_bc_op);
	अगर (len < *min_len)
		वापस false;
	वापस true;
पूर्ण

अटल bool valid_markcond(स्थिर काष्ठा inet_diag_bc_op *op, पूर्णांक len,
			   पूर्णांक *min_len)
अणु
	*min_len += माप(काष्ठा inet_diag_markcond);
	वापस len >= *min_len;
पूर्ण

#अगर_घोषित CONFIG_SOCK_CGROUP_DATA
अटल bool valid_cgroupcond(स्थिर काष्ठा inet_diag_bc_op *op, पूर्णांक len,
			     पूर्णांक *min_len)
अणु
	*min_len += माप(u64);
	वापस len >= *min_len;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक inet_diag_bc_audit(स्थिर काष्ठा nlattr *attr,
			      स्थिर काष्ठा sk_buff *skb)
अणु
	bool net_admin = netlink_net_capable(skb, CAP_NET_ADMIN);
	स्थिर व्योम *bytecode, *bc;
	पूर्णांक bytecode_len, len;

	अगर (!attr || nla_len(attr) < माप(काष्ठा inet_diag_bc_op))
		वापस -EINVAL;

	bytecode = bc = nla_data(attr);
	len = bytecode_len = nla_len(attr);

	जबतक (len > 0) अणु
		पूर्णांक min_len = माप(काष्ठा inet_diag_bc_op);
		स्थिर काष्ठा inet_diag_bc_op *op = bc;

		चयन (op->code) अणु
		हाल INET_DIAG_BC_S_COND:
		हाल INET_DIAG_BC_D_COND:
			अगर (!valid_hostcond(bc, len, &min_len))
				वापस -EINVAL;
			अवरोध;
		हाल INET_DIAG_BC_DEV_COND:
			अगर (!valid_devcond(bc, len, &min_len))
				वापस -EINVAL;
			अवरोध;
		हाल INET_DIAG_BC_S_EQ:
		हाल INET_DIAG_BC_S_GE:
		हाल INET_DIAG_BC_S_LE:
		हाल INET_DIAG_BC_D_EQ:
		हाल INET_DIAG_BC_D_GE:
		हाल INET_DIAG_BC_D_LE:
			अगर (!valid_port_comparison(bc, len, &min_len))
				वापस -EINVAL;
			अवरोध;
		हाल INET_DIAG_BC_MARK_COND:
			अगर (!net_admin)
				वापस -EPERM;
			अगर (!valid_markcond(bc, len, &min_len))
				वापस -EINVAL;
			अवरोध;
#अगर_घोषित CONFIG_SOCK_CGROUP_DATA
		हाल INET_DIAG_BC_CGROUP_COND:
			अगर (!valid_cgroupcond(bc, len, &min_len))
				वापस -EINVAL;
			अवरोध;
#पूर्ण_अगर
		हाल INET_DIAG_BC_AUTO:
		हाल INET_DIAG_BC_JMP:
		हाल INET_DIAG_BC_NOP:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		अगर (op->code != INET_DIAG_BC_NOP) अणु
			अगर (op->no < min_len || op->no > len + 4 || op->no & 3)
				वापस -EINVAL;
			अगर (op->no < len &&
			    !valid_cc(bytecode, bytecode_len, len - op->no))
				वापस -EINVAL;
		पूर्ण

		अगर (op->yes < min_len || op->yes > len + 4 || op->yes & 3)
			वापस -EINVAL;
		bc  += op->yes;
		len -= op->yes;
	पूर्ण
	वापस len == 0 ? 0 : -EINVAL;
पूर्ण

अटल व्योम twsk_build_निश्चित(व्योम)
अणु
	BUILD_BUG_ON(दुरत्व(काष्ठा inet_समयरुको_sock, tw_family) !=
		     दुरत्व(काष्ठा sock, sk_family));

	BUILD_BUG_ON(दुरत्व(काष्ठा inet_समयरुको_sock, tw_num) !=
		     दुरत्व(काष्ठा inet_sock, inet_num));

	BUILD_BUG_ON(दुरत्व(काष्ठा inet_समयरुको_sock, tw_dport) !=
		     दुरत्व(काष्ठा inet_sock, inet_dport));

	BUILD_BUG_ON(दुरत्व(काष्ठा inet_समयरुको_sock, tw_rcv_saddr) !=
		     दुरत्व(काष्ठा inet_sock, inet_rcv_saddr));

	BUILD_BUG_ON(दुरत्व(काष्ठा inet_समयरुको_sock, tw_daddr) !=
		     दुरत्व(काष्ठा inet_sock, inet_daddr));

#अगर IS_ENABLED(CONFIG_IPV6)
	BUILD_BUG_ON(दुरत्व(काष्ठा inet_समयरुको_sock, tw_v6_rcv_saddr) !=
		     दुरत्व(काष्ठा sock, sk_v6_rcv_saddr));

	BUILD_BUG_ON(दुरत्व(काष्ठा inet_समयरुको_sock, tw_v6_daddr) !=
		     दुरत्व(काष्ठा sock, sk_v6_daddr));
#पूर्ण_अगर
पूर्ण

व्योम inet_diag_dump_icsk(काष्ठा inet_hashinfo *hashinfo, काष्ठा sk_buff *skb,
			 काष्ठा netlink_callback *cb,
			 स्थिर काष्ठा inet_diag_req_v2 *r)
अणु
	bool net_admin = netlink_net_capable(cb->skb, CAP_NET_ADMIN);
	काष्ठा inet_diag_dump_data *cb_data = cb->data;
	काष्ठा net *net = sock_net(skb->sk);
	u32 idiag_states = r->idiag_states;
	पूर्णांक i, num, s_i, s_num;
	काष्ठा nlattr *bc;
	काष्ठा sock *sk;

	bc = cb_data->inet_diag_nla_bc;
	अगर (idiag_states & TCPF_SYN_RECV)
		idiag_states |= TCPF_NEW_SYN_RECV;
	s_i = cb->args[1];
	s_num = num = cb->args[2];

	अगर (cb->args[0] == 0) अणु
		अगर (!(idiag_states & TCPF_LISTEN) || r->id.idiag_dport)
			जाओ skip_listen_ht;

		क्रम (i = s_i; i < INET_LHTABLE_SIZE; i++) अणु
			काष्ठा inet_listen_hashbucket *ilb;
			काष्ठा hlist_nulls_node *node;

			num = 0;
			ilb = &hashinfo->listening_hash[i];
			spin_lock(&ilb->lock);
			sk_nulls_क्रम_each(sk, node, &ilb->nulls_head) अणु
				काष्ठा inet_sock *inet = inet_sk(sk);

				अगर (!net_eq(sock_net(sk), net))
					जारी;

				अगर (num < s_num) अणु
					num++;
					जारी;
				पूर्ण

				अगर (r->sdiag_family != AF_UNSPEC &&
				    sk->sk_family != r->sdiag_family)
					जाओ next_listen;

				अगर (r->id.idiag_sport != inet->inet_sport &&
				    r->id.idiag_sport)
					जाओ next_listen;

				अगर (!inet_diag_bc_sk(bc, sk))
					जाओ next_listen;

				अगर (inet_sk_diag_fill(sk, inet_csk(sk), skb,
						      cb, r, NLM_F_MULTI,
						      net_admin) < 0) अणु
					spin_unlock(&ilb->lock);
					जाओ करोne;
				पूर्ण

next_listen:
				++num;
			पूर्ण
			spin_unlock(&ilb->lock);

			s_num = 0;
		पूर्ण
skip_listen_ht:
		cb->args[0] = 1;
		s_i = num = s_num = 0;
	पूर्ण

	अगर (!(idiag_states & ~TCPF_LISTEN))
		जाओ out;

#घोषणा SKARR_SZ 16
	क्रम (i = s_i; i <= hashinfo->ehash_mask; i++) अणु
		काष्ठा inet_ehash_bucket *head = &hashinfo->ehash[i];
		spinlock_t *lock = inet_ehash_lockp(hashinfo, i);
		काष्ठा hlist_nulls_node *node;
		काष्ठा sock *sk_arr[SKARR_SZ];
		पूर्णांक num_arr[SKARR_SZ];
		पूर्णांक idx, accum, res;

		अगर (hlist_nulls_empty(&head->chain))
			जारी;

		अगर (i > s_i)
			s_num = 0;

next_chunk:
		num = 0;
		accum = 0;
		spin_lock_bh(lock);
		sk_nulls_क्रम_each(sk, node, &head->chain) अणु
			पूर्णांक state;

			अगर (!net_eq(sock_net(sk), net))
				जारी;
			अगर (num < s_num)
				जाओ next_normal;
			state = (sk->sk_state == TCP_TIME_WAIT) ?
				inet_twsk(sk)->tw_substate : sk->sk_state;
			अगर (!(idiag_states & (1 << state)))
				जाओ next_normal;
			अगर (r->sdiag_family != AF_UNSPEC &&
			    sk->sk_family != r->sdiag_family)
				जाओ next_normal;
			अगर (r->id.idiag_sport != htons(sk->sk_num) &&
			    r->id.idiag_sport)
				जाओ next_normal;
			अगर (r->id.idiag_dport != sk->sk_dport &&
			    r->id.idiag_dport)
				जाओ next_normal;
			twsk_build_निश्चित();

			अगर (!inet_diag_bc_sk(bc, sk))
				जाओ next_normal;

			अगर (!refcount_inc_not_zero(&sk->sk_refcnt))
				जाओ next_normal;

			num_arr[accum] = num;
			sk_arr[accum] = sk;
			अगर (++accum == SKARR_SZ)
				अवरोध;
next_normal:
			++num;
		पूर्ण
		spin_unlock_bh(lock);
		res = 0;
		क्रम (idx = 0; idx < accum; idx++) अणु
			अगर (res >= 0) अणु
				res = sk_diag_fill(sk_arr[idx], skb, cb, r,
						   NLM_F_MULTI, net_admin);
				अगर (res < 0)
					num = num_arr[idx];
			पूर्ण
			sock_gen_put(sk_arr[idx]);
		पूर्ण
		अगर (res < 0)
			अवरोध;
		cond_resched();
		अगर (accum == SKARR_SZ) अणु
			s_num = num + 1;
			जाओ next_chunk;
		पूर्ण
	पूर्ण

करोne:
	cb->args[1] = i;
	cb->args[2] = num;
out:
	;
पूर्ण
EXPORT_SYMBOL_GPL(inet_diag_dump_icsk);

अटल पूर्णांक __inet_diag_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
			    स्थिर काष्ठा inet_diag_req_v2 *r)
अणु
	काष्ठा inet_diag_dump_data *cb_data = cb->data;
	स्थिर काष्ठा inet_diag_handler *handler;
	u32 prev_min_dump_alloc;
	पूर्णांक protocol, err = 0;

	protocol = inet_diag_get_protocol(r, cb_data);

again:
	prev_min_dump_alloc = cb->min_dump_alloc;
	handler = inet_diag_lock_handler(protocol);
	अगर (!IS_ERR(handler))
		handler->dump(skb, cb, r);
	अन्यथा
		err = PTR_ERR(handler);
	inet_diag_unlock_handler(handler);

	/* The skb is not large enough to fit one sk info and
	 * inet_sk_diag_fill() has requested क्रम a larger skb.
	 */
	अगर (!skb->len && cb->min_dump_alloc > prev_min_dump_alloc) अणु
		err = pskb_expand_head(skb, 0, cb->min_dump_alloc, GFP_KERNEL);
		अगर (!err)
			जाओ again;
	पूर्ण

	वापस err ? : skb->len;
पूर्ण

अटल पूर्णांक inet_diag_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	वापस __inet_diag_dump(skb, cb, nlmsg_data(cb->nlh));
पूर्ण

अटल पूर्णांक __inet_diag_dump_start(काष्ठा netlink_callback *cb, पूर्णांक hdrlen)
अणु
	स्थिर काष्ठा nlmsghdr *nlh = cb->nlh;
	काष्ठा inet_diag_dump_data *cb_data;
	काष्ठा sk_buff *skb = cb->skb;
	काष्ठा nlattr *nla;
	पूर्णांक err;

	cb_data = kzalloc(माप(*cb_data), GFP_KERNEL);
	अगर (!cb_data)
		वापस -ENOMEM;

	err = inet_diag_parse_attrs(nlh, hdrlen, cb_data->req_nlas);
	अगर (err) अणु
		kमुक्त(cb_data);
		वापस err;
	पूर्ण
	nla = cb_data->inet_diag_nla_bc;
	अगर (nla) अणु
		err = inet_diag_bc_audit(nla, skb);
		अगर (err) अणु
			kमुक्त(cb_data);
			वापस err;
		पूर्ण
	पूर्ण

	nla = cb_data->inet_diag_nla_bpf_stgs;
	अगर (nla) अणु
		काष्ठा bpf_sk_storage_diag *bpf_stg_diag;

		bpf_stg_diag = bpf_sk_storage_diag_alloc(nla);
		अगर (IS_ERR(bpf_stg_diag)) अणु
			kमुक्त(cb_data);
			वापस PTR_ERR(bpf_stg_diag);
		पूर्ण
		cb_data->bpf_stg_diag = bpf_stg_diag;
	पूर्ण

	cb->data = cb_data;
	वापस 0;
पूर्ण

अटल पूर्णांक inet_diag_dump_start(काष्ठा netlink_callback *cb)
अणु
	वापस __inet_diag_dump_start(cb, माप(काष्ठा inet_diag_req_v2));
पूर्ण

अटल पूर्णांक inet_diag_dump_start_compat(काष्ठा netlink_callback *cb)
अणु
	वापस __inet_diag_dump_start(cb, माप(काष्ठा inet_diag_req));
पूर्ण

अटल पूर्णांक inet_diag_dump_करोne(काष्ठा netlink_callback *cb)
अणु
	काष्ठा inet_diag_dump_data *cb_data = cb->data;

	bpf_sk_storage_diag_मुक्त(cb_data->bpf_stg_diag);
	kमुक्त(cb->data);

	वापस 0;
पूर्ण

अटल पूर्णांक inet_diag_type2proto(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल TCPDIAG_GETSOCK:
		वापस IPPROTO_TCP;
	हाल DCCPDIAG_GETSOCK:
		वापस IPPROTO_DCCP;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक inet_diag_dump_compat(काष्ठा sk_buff *skb,
				 काष्ठा netlink_callback *cb)
अणु
	काष्ठा inet_diag_req *rc = nlmsg_data(cb->nlh);
	काष्ठा inet_diag_req_v2 req;

	req.sdiag_family = AF_UNSPEC; /* compatibility */
	req.sdiag_protocol = inet_diag_type2proto(cb->nlh->nlmsg_type);
	req.idiag_ext = rc->idiag_ext;
	req.idiag_states = rc->idiag_states;
	req.id = rc->id;

	वापस __inet_diag_dump(skb, cb, &req);
पूर्ण

अटल पूर्णांक inet_diag_get_exact_compat(काष्ठा sk_buff *in_skb,
				      स्थिर काष्ठा nlmsghdr *nlh)
अणु
	काष्ठा inet_diag_req *rc = nlmsg_data(nlh);
	काष्ठा inet_diag_req_v2 req;

	req.sdiag_family = rc->idiag_family;
	req.sdiag_protocol = inet_diag_type2proto(nlh->nlmsg_type);
	req.idiag_ext = rc->idiag_ext;
	req.idiag_states = rc->idiag_states;
	req.id = rc->id;

	वापस inet_diag_cmd_exact(SOCK_DIAG_BY_FAMILY, in_skb, nlh,
				   माप(काष्ठा inet_diag_req), &req);
पूर्ण

अटल पूर्णांक inet_diag_rcv_msg_compat(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh)
अणु
	पूर्णांक hdrlen = माप(काष्ठा inet_diag_req);
	काष्ठा net *net = sock_net(skb->sk);

	अगर (nlh->nlmsg_type >= INET_DIAG_GETSOCK_MAX ||
	    nlmsg_len(nlh) < hdrlen)
		वापस -EINVAL;

	अगर (nlh->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.start = inet_diag_dump_start_compat,
			.करोne = inet_diag_dump_करोne,
			.dump = inet_diag_dump_compat,
		पूर्ण;
		वापस netlink_dump_start(net->diag_nlsk, skb, nlh, &c);
	पूर्ण

	वापस inet_diag_get_exact_compat(skb, nlh);
पूर्ण

अटल पूर्णांक inet_diag_handler_cmd(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *h)
अणु
	पूर्णांक hdrlen = माप(काष्ठा inet_diag_req_v2);
	काष्ठा net *net = sock_net(skb->sk);

	अगर (nlmsg_len(h) < hdrlen)
		वापस -EINVAL;

	अगर (h->nlmsg_type == SOCK_DIAG_BY_FAMILY &&
	    h->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.start = inet_diag_dump_start,
			.करोne = inet_diag_dump_करोne,
			.dump = inet_diag_dump,
		पूर्ण;
		वापस netlink_dump_start(net->diag_nlsk, skb, h, &c);
	पूर्ण

	वापस inet_diag_cmd_exact(h->nlmsg_type, skb, h, hdrlen,
				   nlmsg_data(h));
पूर्ण

अटल
पूर्णांक inet_diag_handler_get_info(काष्ठा sk_buff *skb, काष्ठा sock *sk)
अणु
	स्थिर काष्ठा inet_diag_handler *handler;
	काष्ठा nlmsghdr *nlh;
	काष्ठा nlattr *attr;
	काष्ठा inet_diag_msg *r;
	व्योम *info = शून्य;
	पूर्णांक err = 0;

	nlh = nlmsg_put(skb, 0, 0, SOCK_DIAG_BY_FAMILY, माप(*r), 0);
	अगर (!nlh)
		वापस -ENOMEM;

	r = nlmsg_data(nlh);
	स_रखो(r, 0, माप(*r));
	inet_diag_msg_common_fill(r, sk);
	अगर (sk->sk_type == SOCK_DGRAM || sk->sk_type == SOCK_STREAM)
		r->id.idiag_sport = inet_sk(sk)->inet_sport;
	r->idiag_state = sk->sk_state;

	अगर ((err = nla_put_u8(skb, INET_DIAG_PROTOCOL, sk->sk_protocol))) अणु
		nlmsg_cancel(skb, nlh);
		वापस err;
	पूर्ण

	handler = inet_diag_lock_handler(sk->sk_protocol);
	अगर (IS_ERR(handler)) अणु
		inet_diag_unlock_handler(handler);
		nlmsg_cancel(skb, nlh);
		वापस PTR_ERR(handler);
	पूर्ण

	attr = handler->idiag_info_size
		? nla_reserve_64bit(skb, INET_DIAG_INFO,
				    handler->idiag_info_size,
				    INET_DIAG_PAD)
		: शून्य;
	अगर (attr)
		info = nla_data(attr);

	handler->idiag_get_info(sk, r, info);
	inet_diag_unlock_handler(handler);

	nlmsg_end(skb, nlh);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sock_diag_handler inet_diag_handler = अणु
	.family = AF_INET,
	.dump = inet_diag_handler_cmd,
	.get_info = inet_diag_handler_get_info,
	.destroy = inet_diag_handler_cmd,
पूर्ण;

अटल स्थिर काष्ठा sock_diag_handler inet6_diag_handler = अणु
	.family = AF_INET6,
	.dump = inet_diag_handler_cmd,
	.get_info = inet_diag_handler_get_info,
	.destroy = inet_diag_handler_cmd,
पूर्ण;

पूर्णांक inet_diag_रेजिस्टर(स्थिर काष्ठा inet_diag_handler *h)
अणु
	स्थिर __u16 type = h->idiag_type;
	पूर्णांक err = -EINVAL;

	अगर (type >= IPPROTO_MAX)
		जाओ out;

	mutex_lock(&inet_diag_table_mutex);
	err = -EEXIST;
	अगर (!inet_diag_table[type]) अणु
		inet_diag_table[type] = h;
		err = 0;
	पूर्ण
	mutex_unlock(&inet_diag_table_mutex);
out:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(inet_diag_रेजिस्टर);

व्योम inet_diag_unरेजिस्टर(स्थिर काष्ठा inet_diag_handler *h)
अणु
	स्थिर __u16 type = h->idiag_type;

	अगर (type >= IPPROTO_MAX)
		वापस;

	mutex_lock(&inet_diag_table_mutex);
	inet_diag_table[type] = शून्य;
	mutex_unlock(&inet_diag_table_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(inet_diag_unरेजिस्टर);

अटल पूर्णांक __init inet_diag_init(व्योम)
अणु
	स्थिर पूर्णांक inet_diag_table_size = (IPPROTO_MAX *
					  माप(काष्ठा inet_diag_handler *));
	पूर्णांक err = -ENOMEM;

	inet_diag_table = kzalloc(inet_diag_table_size, GFP_KERNEL);
	अगर (!inet_diag_table)
		जाओ out;

	err = sock_diag_रेजिस्टर(&inet_diag_handler);
	अगर (err)
		जाओ out_मुक्त_nl;

	err = sock_diag_रेजिस्टर(&inet6_diag_handler);
	अगर (err)
		जाओ out_मुक्त_inet;

	sock_diag_रेजिस्टर_inet_compat(inet_diag_rcv_msg_compat);
out:
	वापस err;

out_मुक्त_inet:
	sock_diag_unरेजिस्टर(&inet_diag_handler);
out_मुक्त_nl:
	kमुक्त(inet_diag_table);
	जाओ out;
पूर्ण

अटल व्योम __निकास inet_diag_निकास(व्योम)
अणु
	sock_diag_unरेजिस्टर(&inet6_diag_handler);
	sock_diag_unरेजिस्टर(&inet_diag_handler);
	sock_diag_unरेजिस्टर_inet_compat(inet_diag_rcv_msg_compat);
	kमुक्त(inet_diag_table);
पूर्ण

module_init(inet_diag_init);
module_निकास(inet_diag_निकास);
MODULE_LICENSE("GPL");
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_NETLINK, NETLINK_SOCK_DIAG, 2 /* AF_INET */);
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_NETLINK, NETLINK_SOCK_DIAG, 10 /* AF_INET6 */);
