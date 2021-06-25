<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright Red Hat Inc. 2017
 *
 * This file is part of the SCTP kernel implementation
 *
 * These functions implement sctp diag support.
 *
 * Please send any bug reports or fixes you make to the
 * email addresched(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    Xin Long <lucien.xin@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/inet_diag.h>
#समावेश <linux/sock_diag.h>
#समावेश <net/sctp/sctp.h>

अटल व्योम sctp_diag_get_info(काष्ठा sock *sk, काष्ठा inet_diag_msg *r,
			       व्योम *info);

/* define some functions to make asoc/ep fill look clean */
अटल व्योम inet_diag_msg_sctpasoc_fill(काष्ठा inet_diag_msg *r,
					काष्ठा sock *sk,
					काष्ठा sctp_association *asoc)
अणु
	जोड़ sctp_addr laddr, paddr;
	काष्ठा dst_entry *dst;
	काष्ठा समयr_list *t3_rtx = &asoc->peer.primary_path->T3_rtx_समयr;

	laddr = list_entry(asoc->base.bind_addr.address_list.next,
			   काष्ठा sctp_sockaddr_entry, list)->a;
	paddr = asoc->peer.primary_path->ipaddr;
	dst = asoc->peer.primary_path->dst;

	r->idiag_family = sk->sk_family;
	r->id.idiag_sport = htons(asoc->base.bind_addr.port);
	r->id.idiag_dport = htons(asoc->peer.port);
	r->id.idiag_अगर = dst ? dst->dev->अगरindex : 0;
	sock_diag_save_cookie(sk, r->id.idiag_cookie);

#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (sk->sk_family == AF_INET6) अणु
		*(काष्ठा in6_addr *)r->id.idiag_src = laddr.v6.sin6_addr;
		*(काष्ठा in6_addr *)r->id.idiag_dst = paddr.v6.sin6_addr;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		स_रखो(&r->id.idiag_src, 0, माप(r->id.idiag_src));
		स_रखो(&r->id.idiag_dst, 0, माप(r->id.idiag_dst));

		r->id.idiag_src[0] = laddr.v4.sin_addr.s_addr;
		r->id.idiag_dst[0] = paddr.v4.sin_addr.s_addr;
	पूर्ण

	r->idiag_state = asoc->state;
	अगर (समयr_pending(t3_rtx)) अणु
		r->idiag_समयr = SCTP_EVENT_TIMEOUT_T3_RTX;
		r->idiag_retrans = asoc->rtx_data_chunks;
		r->idiag_expires = jअगरfies_to_msecs(t3_rtx->expires - jअगरfies);
	पूर्ण अन्यथा अणु
		r->idiag_समयr = 0;
		r->idiag_retrans = 0;
		r->idiag_expires = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक inet_diag_msg_sctpladdrs_fill(काष्ठा sk_buff *skb,
					 काष्ठा list_head *address_list)
अणु
	काष्ठा sctp_sockaddr_entry *laddr;
	पूर्णांक addrlen = माप(काष्ठा sockaddr_storage);
	पूर्णांक addrcnt = 0;
	काष्ठा nlattr *attr;
	व्योम *info = शून्य;

	list_क्रम_each_entry_rcu(laddr, address_list, list)
		addrcnt++;

	attr = nla_reserve(skb, INET_DIAG_LOCALS, addrlen * addrcnt);
	अगर (!attr)
		वापस -EMSGSIZE;

	info = nla_data(attr);
	list_क्रम_each_entry_rcu(laddr, address_list, list) अणु
		स_नकल(info, &laddr->a, माप(laddr->a));
		स_रखो(info + माप(laddr->a), 0, addrlen - माप(laddr->a));
		info += addrlen;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक inet_diag_msg_sctpaddrs_fill(काष्ठा sk_buff *skb,
					काष्ठा sctp_association *asoc)
अणु
	पूर्णांक addrlen = माप(काष्ठा sockaddr_storage);
	काष्ठा sctp_transport *from;
	काष्ठा nlattr *attr;
	व्योम *info = शून्य;

	attr = nla_reserve(skb, INET_DIAG_PEERS,
			   addrlen * asoc->peer.transport_count);
	अगर (!attr)
		वापस -EMSGSIZE;

	info = nla_data(attr);
	list_क्रम_each_entry(from, &asoc->peer.transport_addr_list,
			    transports) अणु
		स_नकल(info, &from->ipaddr, माप(from->ipaddr));
		स_रखो(info + माप(from->ipaddr), 0,
		       addrlen - माप(from->ipaddr));
		info += addrlen;
	पूर्ण

	वापस 0;
पूर्ण

/* sctp asoc/ep fill*/
अटल पूर्णांक inet_sctp_diag_fill(काष्ठा sock *sk, काष्ठा sctp_association *asoc,
			       काष्ठा sk_buff *skb,
			       स्थिर काष्ठा inet_diag_req_v2 *req,
			       काष्ठा user_namespace *user_ns,
			       पूर्णांक portid, u32 seq, u16 nlmsg_flags,
			       स्थिर काष्ठा nlmsghdr *unlh,
			       bool net_admin)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep = sctp_sk(sk)->ep;
	काष्ठा list_head *addr_list;
	काष्ठा inet_diag_msg *r;
	काष्ठा nlmsghdr  *nlh;
	पूर्णांक ext = req->idiag_ext;
	काष्ठा sctp_infox infox;
	व्योम *info = शून्य;

	nlh = nlmsg_put(skb, portid, seq, unlh->nlmsg_type, माप(*r),
			nlmsg_flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	r = nlmsg_data(nlh);
	BUG_ON(!sk_fullsock(sk));

	अगर (asoc) अणु
		inet_diag_msg_sctpasoc_fill(r, sk, asoc);
	पूर्ण अन्यथा अणु
		inet_diag_msg_common_fill(r, sk);
		r->idiag_state = sk->sk_state;
		r->idiag_समयr = 0;
		r->idiag_retrans = 0;
	पूर्ण

	अगर (inet_diag_msg_attrs_fill(sk, skb, r, ext, user_ns, net_admin))
		जाओ errout;

	अगर (ext & (1 << (INET_DIAG_SKMEMINFO - 1))) अणु
		u32 mem[SK_MEMINFO_VARS];
		पूर्णांक amt;

		अगर (asoc && asoc->ep->sndbuf_policy)
			amt = asoc->sndbuf_used;
		अन्यथा
			amt = sk_wmem_alloc_get(sk);
		mem[SK_MEMINFO_WMEM_ALLOC] = amt;
		अगर (asoc && asoc->ep->rcvbuf_policy)
			amt = atomic_पढ़ो(&asoc->rmem_alloc);
		अन्यथा
			amt = sk_rmem_alloc_get(sk);
		mem[SK_MEMINFO_RMEM_ALLOC] = amt;
		mem[SK_MEMINFO_RCVBUF] = sk->sk_rcvbuf;
		mem[SK_MEMINFO_SNDBUF] = sk->sk_sndbuf;
		mem[SK_MEMINFO_FWD_ALLOC] = sk->sk_क्रमward_alloc;
		mem[SK_MEMINFO_WMEM_QUEUED] = sk->sk_wmem_queued;
		mem[SK_MEMINFO_OPTMEM] = atomic_पढ़ो(&sk->sk_omem_alloc);
		mem[SK_MEMINFO_BACKLOG] = READ_ONCE(sk->sk_backlog.len);
		mem[SK_MEMINFO_DROPS] = atomic_पढ़ो(&sk->sk_drops);

		अगर (nla_put(skb, INET_DIAG_SKMEMINFO, माप(mem), &mem) < 0)
			जाओ errout;
	पूर्ण

	अगर (ext & (1 << (INET_DIAG_INFO - 1))) अणु
		काष्ठा nlattr *attr;

		attr = nla_reserve_64bit(skb, INET_DIAG_INFO,
					 माप(काष्ठा sctp_info),
					 INET_DIAG_PAD);
		अगर (!attr)
			जाओ errout;

		info = nla_data(attr);
	पूर्ण
	infox.sctpinfo = (काष्ठा sctp_info *)info;
	infox.asoc = asoc;
	sctp_diag_get_info(sk, r, &infox);

	addr_list = asoc ? &asoc->base.bind_addr.address_list
			 : &ep->base.bind_addr.address_list;
	अगर (inet_diag_msg_sctpladdrs_fill(skb, addr_list))
		जाओ errout;

	अगर (asoc && (ext & (1 << (INET_DIAG_CONG - 1))))
		अगर (nla_put_string(skb, INET_DIAG_CONG, "reno") < 0)
			जाओ errout;

	अगर (asoc && inet_diag_msg_sctpaddrs_fill(skb, asoc))
		जाओ errout;

	nlmsg_end(skb, nlh);
	वापस 0;

errout:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

/* callback and param */
काष्ठा sctp_comm_param अणु
	काष्ठा sk_buff *skb;
	काष्ठा netlink_callback *cb;
	स्थिर काष्ठा inet_diag_req_v2 *r;
	स्थिर काष्ठा nlmsghdr *nlh;
	bool net_admin;
पूर्ण;

अटल माप_प्रकार inet_assoc_attr_size(काष्ठा sctp_association *asoc)
अणु
	पूर्णांक addrlen = माप(काष्ठा sockaddr_storage);
	पूर्णांक addrcnt = 0;
	काष्ठा sctp_sockaddr_entry *laddr;

	list_क्रम_each_entry_rcu(laddr, &asoc->base.bind_addr.address_list,
				list)
		addrcnt++;

	वापस	  nla_total_size(माप(काष्ठा sctp_info))
		+ nla_total_size(addrlen * asoc->peer.transport_count)
		+ nla_total_size(addrlen * addrcnt)
		+ nla_total_size(माप(काष्ठा inet_diag_msg))
		+ inet_diag_msg_attrs_size()
		+ nla_total_size(माप(काष्ठा inet_diag_meminfo))
		+ 64;
पूर्ण

अटल पूर्णांक sctp_tsp_dump_one(काष्ठा sctp_transport *tsp, व्योम *p)
अणु
	काष्ठा sctp_association *assoc = tsp->asoc;
	काष्ठा sock *sk = tsp->asoc->base.sk;
	काष्ठा sctp_comm_param *commp = p;
	काष्ठा sk_buff *in_skb = commp->skb;
	स्थिर काष्ठा inet_diag_req_v2 *req = commp->r;
	स्थिर काष्ठा nlmsghdr *nlh = commp->nlh;
	काष्ठा net *net = sock_net(in_skb->sk);
	काष्ठा sk_buff *rep;
	पूर्णांक err;

	err = sock_diag_check_cookie(sk, req->id.idiag_cookie);
	अगर (err)
		जाओ out;

	err = -ENOMEM;
	rep = nlmsg_new(inet_assoc_attr_size(assoc), GFP_KERNEL);
	अगर (!rep)
		जाओ out;

	lock_sock(sk);
	अगर (sk != assoc->base.sk) अणु
		release_sock(sk);
		sk = assoc->base.sk;
		lock_sock(sk);
	पूर्ण
	err = inet_sctp_diag_fill(sk, assoc, rep, req,
				  sk_user_ns(NETLINK_CB(in_skb).sk),
				  NETLINK_CB(in_skb).portid,
				  nlh->nlmsg_seq, 0, nlh,
				  commp->net_admin);
	release_sock(sk);
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
	वापस err;
पूर्ण

अटल पूर्णांक sctp_sock_dump(काष्ठा sctp_transport *tsp, व्योम *p)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep = tsp->asoc->ep;
	काष्ठा sctp_comm_param *commp = p;
	काष्ठा sock *sk = ep->base.sk;
	काष्ठा sk_buff *skb = commp->skb;
	काष्ठा netlink_callback *cb = commp->cb;
	स्थिर काष्ठा inet_diag_req_v2 *r = commp->r;
	काष्ठा sctp_association *assoc;
	पूर्णांक err = 0;

	lock_sock(sk);
	list_क्रम_each_entry(assoc, &ep->asocs, asocs) अणु
		अगर (cb->args[4] < cb->args[1])
			जाओ next;

		अगर (r->id.idiag_sport != htons(assoc->base.bind_addr.port) &&
		    r->id.idiag_sport)
			जाओ next;
		अगर (r->id.idiag_dport != htons(assoc->peer.port) &&
		    r->id.idiag_dport)
			जाओ next;

		अगर (!cb->args[3] &&
		    inet_sctp_diag_fill(sk, शून्य, skb, r,
					sk_user_ns(NETLINK_CB(cb->skb).sk),
					NETLINK_CB(cb->skb).portid,
					cb->nlh->nlmsg_seq,
					NLM_F_MULTI, cb->nlh,
					commp->net_admin) < 0) अणु
			err = 1;
			जाओ release;
		पूर्ण
		cb->args[3] = 1;

		अगर (inet_sctp_diag_fill(sk, assoc, skb, r,
					sk_user_ns(NETLINK_CB(cb->skb).sk),
					NETLINK_CB(cb->skb).portid,
					cb->nlh->nlmsg_seq, 0, cb->nlh,
					commp->net_admin) < 0) अणु
			err = 1;
			जाओ release;
		पूर्ण
next:
		cb->args[4]++;
	पूर्ण
	cb->args[1] = 0;
	cb->args[3] = 0;
	cb->args[4] = 0;
release:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक sctp_sock_filter(काष्ठा sctp_transport *tsp, व्योम *p)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep = tsp->asoc->ep;
	काष्ठा sctp_comm_param *commp = p;
	काष्ठा sock *sk = ep->base.sk;
	स्थिर काष्ठा inet_diag_req_v2 *r = commp->r;
	काष्ठा sctp_association *assoc =
		list_entry(ep->asocs.next, काष्ठा sctp_association, asocs);

	/* find the ep only once through the transports by this condition */
	अगर (tsp->asoc != assoc)
		वापस 0;

	अगर (r->sdiag_family != AF_UNSPEC && sk->sk_family != r->sdiag_family)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक sctp_ep_dump(काष्ठा sctp_endpoपूर्णांक *ep, व्योम *p)
अणु
	काष्ठा sctp_comm_param *commp = p;
	काष्ठा sock *sk = ep->base.sk;
	काष्ठा sk_buff *skb = commp->skb;
	काष्ठा netlink_callback *cb = commp->cb;
	स्थिर काष्ठा inet_diag_req_v2 *r = commp->r;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा inet_sock *inet = inet_sk(sk);
	पूर्णांक err = 0;

	अगर (!net_eq(sock_net(sk), net))
		जाओ out;

	अगर (cb->args[4] < cb->args[1])
		जाओ next;

	अगर (!(r->idiag_states & TCPF_LISTEN) && !list_empty(&ep->asocs))
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

	अगर (inet_sctp_diag_fill(sk, शून्य, skb, r,
				sk_user_ns(NETLINK_CB(cb->skb).sk),
				NETLINK_CB(cb->skb).portid,
				cb->nlh->nlmsg_seq, NLM_F_MULTI,
				cb->nlh, commp->net_admin) < 0) अणु
		err = 2;
		जाओ out;
	पूर्ण
next:
	cb->args[4]++;
out:
	वापस err;
पूर्ण

/* define the functions क्रम sctp_diag_handler*/
अटल व्योम sctp_diag_get_info(काष्ठा sock *sk, काष्ठा inet_diag_msg *r,
			       व्योम *info)
अणु
	काष्ठा sctp_infox *infox = (काष्ठा sctp_infox *)info;

	अगर (infox->asoc) अणु
		r->idiag_rqueue = atomic_पढ़ो(&infox->asoc->rmem_alloc);
		r->idiag_wqueue = infox->asoc->sndbuf_used;
	पूर्ण अन्यथा अणु
		r->idiag_rqueue = READ_ONCE(sk->sk_ack_backlog);
		r->idiag_wqueue = READ_ONCE(sk->sk_max_ack_backlog);
	पूर्ण
	अगर (infox->sctpinfo)
		sctp_get_sctp_info(sk, infox->asoc, infox->sctpinfo);
पूर्ण

अटल पूर्णांक sctp_diag_dump_one(काष्ठा netlink_callback *cb,
			      स्थिर काष्ठा inet_diag_req_v2 *req)
अणु
	काष्ठा sk_buff *in_skb = cb->skb;
	काष्ठा net *net = sock_net(in_skb->sk);
	स्थिर काष्ठा nlmsghdr *nlh = cb->nlh;
	जोड़ sctp_addr laddr, paddr;
	काष्ठा sctp_comm_param commp = अणु
		.skb = in_skb,
		.r = req,
		.nlh = nlh,
		.net_admin = netlink_net_capable(in_skb, CAP_NET_ADMIN),
	पूर्ण;

	अगर (req->sdiag_family == AF_INET) अणु
		laddr.v4.sin_port = req->id.idiag_sport;
		laddr.v4.sin_addr.s_addr = req->id.idiag_src[0];
		laddr.v4.sin_family = AF_INET;

		paddr.v4.sin_port = req->id.idiag_dport;
		paddr.v4.sin_addr.s_addr = req->id.idiag_dst[0];
		paddr.v4.sin_family = AF_INET;
	पूर्ण अन्यथा अणु
		laddr.v6.sin6_port = req->id.idiag_sport;
		स_नकल(&laddr.v6.sin6_addr, req->id.idiag_src,
		       माप(laddr.v6.sin6_addr));
		laddr.v6.sin6_family = AF_INET6;

		paddr.v6.sin6_port = req->id.idiag_dport;
		स_नकल(&paddr.v6.sin6_addr, req->id.idiag_dst,
		       माप(paddr.v6.sin6_addr));
		paddr.v6.sin6_family = AF_INET6;
	पूर्ण

	वापस sctp_transport_lookup_process(sctp_tsp_dump_one,
					     net, &laddr, &paddr, &commp);
पूर्ण

अटल व्योम sctp_diag_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
			   स्थिर काष्ठा inet_diag_req_v2 *r)
अणु
	u32 idiag_states = r->idiag_states;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा sctp_comm_param commp = अणु
		.skb = skb,
		.cb = cb,
		.r = r,
		.net_admin = netlink_net_capable(cb->skb, CAP_NET_ADMIN),
	पूर्ण;
	पूर्णांक pos = cb->args[2];

	/* eps hashtable dumps
	 * args:
	 * 0 : अगर it will traversal listen sock
	 * 1 : to record the sock pos of this समय's traversal
	 * 4 : to work as a temporary variable to traversal list
	 */
	अगर (cb->args[0] == 0) अणु
		अगर (!(idiag_states & TCPF_LISTEN))
			जाओ skip;
		अगर (sctp_क्रम_each_endpoपूर्णांक(sctp_ep_dump, &commp))
			जाओ करोne;
skip:
		cb->args[0] = 1;
		cb->args[1] = 0;
		cb->args[4] = 0;
	पूर्ण

	/* asocs by transport hashtable dump
	 * args:
	 * 1 : to record the assoc pos of this समय's traversal
	 * 2 : to record the transport pos of this समय's traversal
	 * 3 : to mark अगर we have dumped the ep info of the current asoc
	 * 4 : to work as a temporary variable to traversal list
	 * 5 : to save the sk we get from travelsing the tsp list.
	 */
	अगर (!(idiag_states & ~(TCPF_LISTEN | TCPF_CLOSE)))
		जाओ करोne;

	sctp_क्रम_each_transport(sctp_sock_filter, sctp_sock_dump,
				net, &pos, &commp);
	cb->args[2] = pos;

करोne:
	cb->args[1] = cb->args[4];
	cb->args[4] = 0;
पूर्ण

अटल स्थिर काष्ठा inet_diag_handler sctp_diag_handler = अणु
	.dump		 = sctp_diag_dump,
	.dump_one	 = sctp_diag_dump_one,
	.idiag_get_info  = sctp_diag_get_info,
	.idiag_type	 = IPPROTO_SCTP,
	.idiag_info_size = माप(काष्ठा sctp_info),
पूर्ण;

अटल पूर्णांक __init sctp_diag_init(व्योम)
अणु
	वापस inet_diag_रेजिस्टर(&sctp_diag_handler);
पूर्ण

अटल व्योम __निकास sctp_diag_निकास(व्योम)
अणु
	inet_diag_unरेजिस्टर(&sctp_diag_handler);
पूर्ण

module_init(sctp_diag_init);
module_निकास(sctp_diag_निकास);
MODULE_LICENSE("GPL");
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_NETLINK, NETLINK_SOCK_DIAG, 2-132);
