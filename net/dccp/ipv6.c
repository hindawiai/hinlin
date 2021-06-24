<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	DCCP over IPv6
 *	Linux INET6 implementation
 *
 *	Based on net/dccp6/ipv6.c
 *
 *	Arnalकरो Carvalho de Melo <acme@ghostprotocols.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/xfrm.h>
#समावेश <linux/माला.स>

#समावेश <net/addrconf.h>
#समावेश <net/inet_common.h>
#समावेश <net/inet_hashtables.h>
#समावेश <net/inet_sock.h>
#समावेश <net/inet6_connection_sock.h>
#समावेश <net/inet6_hashtables.h>
#समावेश <net/ip6_route.h>
#समावेश <net/ipv6.h>
#समावेश <net/protocol.h>
#समावेश <net/transp_v6.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/xfrm.h>
#समावेश <net/secure_seq.h>
#समावेश <net/netns/generic.h>
#समावेश <net/sock.h>

#समावेश "dccp.h"
#समावेश "ipv6.h"
#समावेश "feat.h"

काष्ठा dccp_v6_pernet अणु
	काष्ठा sock *v6_ctl_sk;
पूर्ण;

अटल अचिन्हित पूर्णांक dccp_v6_pernet_id __पढ़ो_mostly;

/* The per-net v6_ctl_sk is used क्रम sending RSTs and ACKs */

अटल स्थिर काष्ठा inet_connection_sock_af_ops dccp_ipv6_mapped;
अटल स्थिर काष्ठा inet_connection_sock_af_ops dccp_ipv6_af_ops;

/* add pseuकरो-header to DCCP checksum stored in skb->csum */
अटल अंतरभूत __sum16 dccp_v6_csum_finish(काष्ठा sk_buff *skb,
				      स्थिर काष्ठा in6_addr *saddr,
				      स्थिर काष्ठा in6_addr *daddr)
अणु
	वापस csum_ipv6_magic(saddr, daddr, skb->len, IPPROTO_DCCP, skb->csum);
पूर्ण

अटल अंतरभूत व्योम dccp_v6_send_check(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा dccp_hdr *dh = dccp_hdr(skb);

	dccp_csum_outgoing(skb);
	dh->dccph_checksum = dccp_v6_csum_finish(skb, &np->saddr, &sk->sk_v6_daddr);
पूर्ण

अटल अंतरभूत __u64 dccp_v6_init_sequence(काष्ठा sk_buff *skb)
अणु
	वापस secure_dccpv6_sequence_number(ipv6_hdr(skb)->daddr.s6_addr32,
					     ipv6_hdr(skb)->saddr.s6_addr32,
					     dccp_hdr(skb)->dccph_dport,
					     dccp_hdr(skb)->dccph_sport     );

पूर्ण

अटल पूर्णांक dccp_v6_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
			u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	स्थिर काष्ठा ipv6hdr *hdr = (स्थिर काष्ठा ipv6hdr *)skb->data;
	स्थिर काष्ठा dccp_hdr *dh;
	काष्ठा dccp_sock *dp;
	काष्ठा ipv6_pinfo *np;
	काष्ठा sock *sk;
	पूर्णांक err;
	__u64 seq;
	काष्ठा net *net = dev_net(skb->dev);

	/* Only need dccph_dport & dccph_sport which are the first
	 * 4 bytes in dccp header.
	 * Our caller (icmpv6_notअगरy()) alपढ़ोy pulled 8 bytes क्रम us.
	 */
	BUILD_BUG_ON(दुरत्वend(काष्ठा dccp_hdr, dccph_sport) > 8);
	BUILD_BUG_ON(दुरत्वend(काष्ठा dccp_hdr, dccph_dport) > 8);
	dh = (काष्ठा dccp_hdr *)(skb->data + offset);

	sk = __inet6_lookup_established(net, &dccp_hashinfo,
					&hdr->daddr, dh->dccph_dport,
					&hdr->saddr, ntohs(dh->dccph_sport),
					inet6_iअगर(skb), 0);

	अगर (!sk) अणु
		__ICMP6_INC_STATS(net, __in6_dev_get(skb->dev),
				  ICMP6_MIB_INERRORS);
		वापस -ENOENT;
	पूर्ण

	अगर (sk->sk_state == DCCP_TIME_WAIT) अणु
		inet_twsk_put(inet_twsk(sk));
		वापस 0;
	पूर्ण
	seq = dccp_hdr_seq(dh);
	अगर (sk->sk_state == DCCP_NEW_SYN_RECV) अणु
		dccp_req_err(sk, seq);
		वापस 0;
	पूर्ण

	bh_lock_sock(sk);
	अगर (sock_owned_by_user(sk))
		__NET_INC_STATS(net, LINUX_MIB_LOCKDROPPEDICMPS);

	अगर (sk->sk_state == DCCP_CLOSED)
		जाओ out;

	dp = dccp_sk(sk);
	अगर ((1 << sk->sk_state) & ~(DCCPF_REQUESTING | DCCPF_LISTEN) &&
	    !between48(seq, dp->dccps_awl, dp->dccps_awh)) अणु
		__NET_INC_STATS(net, LINUX_MIB_OUTOFWINDOWICMPS);
		जाओ out;
	पूर्ण

	np = inet6_sk(sk);

	अगर (type == NDISC_REसूचीECT) अणु
		अगर (!sock_owned_by_user(sk)) अणु
			काष्ठा dst_entry *dst = __sk_dst_check(sk, np->dst_cookie);

			अगर (dst)
				dst->ops->redirect(dst, sk, skb);
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (type == ICMPV6_PKT_TOOBIG) अणु
		काष्ठा dst_entry *dst = शून्य;

		अगर (!ip6_sk_accept_pmtu(sk))
			जाओ out;

		अगर (sock_owned_by_user(sk))
			जाओ out;
		अगर ((1 << sk->sk_state) & (DCCPF_LISTEN | DCCPF_CLOSED))
			जाओ out;

		dst = inet6_csk_update_pmtu(sk, ntohl(info));
		अगर (!dst)
			जाओ out;

		अगर (inet_csk(sk)->icsk_pmtu_cookie > dst_mtu(dst))
			dccp_sync_mss(sk, dst_mtu(dst));
		जाओ out;
	पूर्ण

	icmpv6_err_convert(type, code, &err);

	/* Might be क्रम an request_sock */
	चयन (sk->sk_state) अणु
	हाल DCCP_REQUESTING:
	हाल DCCP_RESPOND:  /* Cannot happen.
			       It can, it SYNs are crossed. --ANK */
		अगर (!sock_owned_by_user(sk)) अणु
			__DCCP_INC_STATS(DCCP_MIB_ATTEMPTFAILS);
			sk->sk_err = err;
			/*
			 * Wake people up to see the error
			 * (see connect in sock.c)
			 */
			sk->sk_error_report(sk);
			dccp_करोne(sk);
		पूर्ण अन्यथा
			sk->sk_err_soft = err;
		जाओ out;
	पूर्ण

	अगर (!sock_owned_by_user(sk) && np->recverr) अणु
		sk->sk_err = err;
		sk->sk_error_report(sk);
	पूर्ण अन्यथा
		sk->sk_err_soft = err;

out:
	bh_unlock_sock(sk);
	sock_put(sk);
	वापस 0;
पूर्ण


अटल पूर्णांक dccp_v6_send_response(स्थिर काष्ठा sock *sk, काष्ठा request_sock *req)
अणु
	काष्ठा inet_request_sock *ireq = inet_rsk(req);
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा sk_buff *skb;
	काष्ठा in6_addr *final_p, final;
	काष्ठा flowi6 fl6;
	पूर्णांक err = -1;
	काष्ठा dst_entry *dst;

	स_रखो(&fl6, 0, माप(fl6));
	fl6.flowi6_proto = IPPROTO_DCCP;
	fl6.daddr = ireq->ir_v6_rmt_addr;
	fl6.saddr = ireq->ir_v6_loc_addr;
	fl6.flowlabel = 0;
	fl6.flowi6_oअगर = ireq->ir_iअगर;
	fl6.fl6_dport = ireq->ir_rmt_port;
	fl6.fl6_sport = htons(ireq->ir_num);
	security_req_classअगरy_flow(req, flowi6_to_flowi_common(&fl6));


	rcu_पढ़ो_lock();
	final_p = fl6_update_dst(&fl6, rcu_dereference(np->opt), &final);
	rcu_पढ़ो_unlock();

	dst = ip6_dst_lookup_flow(sock_net(sk), sk, &fl6, final_p);
	अगर (IS_ERR(dst)) अणु
		err = PTR_ERR(dst);
		dst = शून्य;
		जाओ करोne;
	पूर्ण

	skb = dccp_make_response(sk, dst, req);
	अगर (skb != शून्य) अणु
		काष्ठा dccp_hdr *dh = dccp_hdr(skb);
		काष्ठा ipv6_txoptions *opt;

		dh->dccph_checksum = dccp_v6_csum_finish(skb,
							 &ireq->ir_v6_loc_addr,
							 &ireq->ir_v6_rmt_addr);
		fl6.daddr = ireq->ir_v6_rmt_addr;
		rcu_पढ़ो_lock();
		opt = ireq->ipv6_opt;
		अगर (!opt)
			opt = rcu_dereference(np->opt);
		err = ip6_xmit(sk, skb, &fl6, sk->sk_mark, opt, np->tclass,
			       sk->sk_priority);
		rcu_पढ़ो_unlock();
		err = net_xmit_eval(err);
	पूर्ण

करोne:
	dst_release(dst);
	वापस err;
पूर्ण

अटल व्योम dccp_v6_reqsk_deकाष्ठाor(काष्ठा request_sock *req)
अणु
	dccp_feat_list_purge(&dccp_rsk(req)->dreq_featneg);
	kमुक्त(inet_rsk(req)->ipv6_opt);
	kमुक्त_skb(inet_rsk(req)->pktopts);
पूर्ण

अटल व्योम dccp_v6_ctl_send_reset(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *rxskb)
अणु
	स्थिर काष्ठा ipv6hdr *rxip6h;
	काष्ठा sk_buff *skb;
	काष्ठा flowi6 fl6;
	काष्ठा net *net = dev_net(skb_dst(rxskb)->dev);
	काष्ठा dccp_v6_pernet *pn;
	काष्ठा sock *ctl_sk;
	काष्ठा dst_entry *dst;

	अगर (dccp_hdr(rxskb)->dccph_type == DCCP_PKT_RESET)
		वापस;

	अगर (!ipv6_unicast_destination(rxskb))
		वापस;

	pn = net_generic(net, dccp_v6_pernet_id);
	ctl_sk = pn->v6_ctl_sk;
	skb = dccp_ctl_make_reset(ctl_sk, rxskb);
	अगर (skb == शून्य)
		वापस;

	rxip6h = ipv6_hdr(rxskb);
	dccp_hdr(skb)->dccph_checksum = dccp_v6_csum_finish(skb, &rxip6h->saddr,
							    &rxip6h->daddr);

	स_रखो(&fl6, 0, माप(fl6));
	fl6.daddr = rxip6h->saddr;
	fl6.saddr = rxip6h->daddr;

	fl6.flowi6_proto = IPPROTO_DCCP;
	fl6.flowi6_oअगर = inet6_iअगर(rxskb);
	fl6.fl6_dport = dccp_hdr(skb)->dccph_dport;
	fl6.fl6_sport = dccp_hdr(skb)->dccph_sport;
	security_skb_classअगरy_flow(rxskb, flowi6_to_flowi_common(&fl6));

	/* sk = शून्य, but it is safe क्रम now. RST socket required. */
	dst = ip6_dst_lookup_flow(sock_net(ctl_sk), ctl_sk, &fl6, शून्य);
	अगर (!IS_ERR(dst)) अणु
		skb_dst_set(skb, dst);
		ip6_xmit(ctl_sk, skb, &fl6, 0, शून्य, 0, 0);
		DCCP_INC_STATS(DCCP_MIB_OUTSEGS);
		DCCP_INC_STATS(DCCP_MIB_OUTRSTS);
		वापस;
	पूर्ण

	kमुक्त_skb(skb);
पूर्ण

अटल काष्ठा request_sock_ops dccp6_request_sock_ops = अणु
	.family		= AF_INET6,
	.obj_size	= माप(काष्ठा dccp6_request_sock),
	.rtx_syn_ack	= dccp_v6_send_response,
	.send_ack	= dccp_reqsk_send_ack,
	.deकाष्ठाor	= dccp_v6_reqsk_deकाष्ठाor,
	.send_reset	= dccp_v6_ctl_send_reset,
	.syn_ack_समयout = dccp_syn_ack_समयout,
पूर्ण;

अटल पूर्णांक dccp_v6_conn_request(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा request_sock *req;
	काष्ठा dccp_request_sock *dreq;
	काष्ठा inet_request_sock *ireq;
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	स्थिर __be32 service = dccp_hdr_request(skb)->dccph_req_service;
	काष्ठा dccp_skb_cb *dcb = DCCP_SKB_CB(skb);

	अगर (skb->protocol == htons(ETH_P_IP))
		वापस dccp_v4_conn_request(sk, skb);

	अगर (!ipv6_unicast_destination(skb))
		वापस 0;	/* discard, करोn't send a reset here */

	अगर (ipv6_addr_v4mapped(&ipv6_hdr(skb)->saddr)) अणु
		__IP6_INC_STATS(sock_net(sk), शून्य, IPSTATS_MIB_INHDRERRORS);
		वापस 0;
	पूर्ण

	अगर (dccp_bad_service_code(sk, service)) अणु
		dcb->dccpd_reset_code = DCCP_RESET_CODE_BAD_SERVICE_CODE;
		जाओ drop;
	पूर्ण
	/*
	 * There are no SYN attacks on IPv6, yet...
	 */
	dcb->dccpd_reset_code = DCCP_RESET_CODE_TOO_BUSY;
	अगर (inet_csk_reqsk_queue_is_full(sk))
		जाओ drop;

	अगर (sk_acceptq_is_full(sk))
		जाओ drop;

	req = inet_reqsk_alloc(&dccp6_request_sock_ops, sk, true);
	अगर (req == शून्य)
		जाओ drop;

	अगर (dccp_reqsk_init(req, dccp_sk(sk), skb))
		जाओ drop_and_मुक्त;

	dreq = dccp_rsk(req);
	अगर (dccp_parse_options(sk, dreq, skb))
		जाओ drop_and_मुक्त;

	अगर (security_inet_conn_request(sk, skb, req))
		जाओ drop_and_मुक्त;

	ireq = inet_rsk(req);
	ireq->ir_v6_rmt_addr = ipv6_hdr(skb)->saddr;
	ireq->ir_v6_loc_addr = ipv6_hdr(skb)->daddr;
	ireq->ireq_family = AF_INET6;
	ireq->ir_mark = inet_request_mark(sk, skb);

	अगर (ipv6_opt_accepted(sk, skb, IP6CB(skb)) ||
	    np->rxopt.bits.rxinfo || np->rxopt.bits.rxoinfo ||
	    np->rxopt.bits.rxhlim || np->rxopt.bits.rxohlim) अणु
		refcount_inc(&skb->users);
		ireq->pktopts = skb;
	पूर्ण
	ireq->ir_iअगर = sk->sk_bound_dev_अगर;

	/* So that link locals have meaning */
	अगर (!sk->sk_bound_dev_अगर &&
	    ipv6_addr_type(&ireq->ir_v6_rmt_addr) & IPV6_ADDR_LINKLOCAL)
		ireq->ir_iअगर = inet6_iअगर(skb);

	/*
	 * Step 3: Process LISTEN state
	 *
	 *   Set S.ISR, S.GSR, S.SWL, S.SWH from packet or Init Cookie
	 *
	 * Setting S.SWL/S.SWH to is deferred to dccp_create_खोलोreq_child().
	 */
	dreq->dreq_isr	   = dcb->dccpd_seq;
	dreq->dreq_gsr     = dreq->dreq_isr;
	dreq->dreq_iss	   = dccp_v6_init_sequence(skb);
	dreq->dreq_gss     = dreq->dreq_iss;
	dreq->dreq_service = service;

	अगर (dccp_v6_send_response(sk, req))
		जाओ drop_and_मुक्त;

	inet_csk_reqsk_queue_hash_add(sk, req, DCCP_TIMEOUT_INIT);
	reqsk_put(req);
	वापस 0;

drop_and_मुक्त:
	reqsk_मुक्त(req);
drop:
	__DCCP_INC_STATS(DCCP_MIB_ATTEMPTFAILS);
	वापस -1;
पूर्ण

अटल काष्ठा sock *dccp_v6_request_recv_sock(स्थिर काष्ठा sock *sk,
					      काष्ठा sk_buff *skb,
					      काष्ठा request_sock *req,
					      काष्ठा dst_entry *dst,
					      काष्ठा request_sock *req_unhash,
					      bool *own_req)
अणु
	काष्ठा inet_request_sock *ireq = inet_rsk(req);
	काष्ठा ipv6_pinfo *newnp;
	स्थिर काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा ipv6_txoptions *opt;
	काष्ठा inet_sock *newinet;
	काष्ठा dccp6_sock *newdp6;
	काष्ठा sock *newsk;

	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		/*
		 *	v6 mapped
		 */
		newsk = dccp_v4_request_recv_sock(sk, skb, req, dst,
						  req_unhash, own_req);
		अगर (newsk == शून्य)
			वापस शून्य;

		newdp6 = (काष्ठा dccp6_sock *)newsk;
		newinet = inet_sk(newsk);
		newinet->pinet6 = &newdp6->inet6;
		newnp = inet6_sk(newsk);

		स_नकल(newnp, np, माप(काष्ठा ipv6_pinfo));

		newnp->saddr = newsk->sk_v6_rcv_saddr;

		inet_csk(newsk)->icsk_af_ops = &dccp_ipv6_mapped;
		newsk->sk_backlog_rcv = dccp_v4_करो_rcv;
		newnp->pktoptions  = शून्य;
		newnp->opt	   = शून्य;
		newnp->ipv6_mc_list = शून्य;
		newnp->ipv6_ac_list = शून्य;
		newnp->ipv6_fl_list = शून्य;
		newnp->mcast_oअगर   = inet_iअगर(skb);
		newnp->mcast_hops  = ip_hdr(skb)->ttl;

		/*
		 * No need to अक्षरge this sock to the relevant IPv6 refcnt debug socks count
		 * here, dccp_create_खोलोreq_child now करोes this क्रम us, see the comment in
		 * that function क्रम the gory details. -acme
		 */

		/* It is tricky place. Until this moment IPv4 tcp
		   worked with IPv6 icsk.icsk_af_ops.
		   Sync it now.
		 */
		dccp_sync_mss(newsk, inet_csk(newsk)->icsk_pmtu_cookie);

		वापस newsk;
	पूर्ण


	अगर (sk_acceptq_is_full(sk))
		जाओ out_overflow;

	अगर (!dst) अणु
		काष्ठा flowi6 fl6;

		dst = inet6_csk_route_req(sk, &fl6, req, IPPROTO_DCCP);
		अगर (!dst)
			जाओ out;
	पूर्ण

	newsk = dccp_create_खोलोreq_child(sk, req, skb);
	अगर (newsk == शून्य)
		जाओ out_nonewsk;

	/*
	 * No need to अक्षरge this sock to the relevant IPv6 refcnt debug socks
	 * count here, dccp_create_खोलोreq_child now करोes this क्रम us, see the
	 * comment in that function क्रम the gory details. -acme
	 */

	ip6_dst_store(newsk, dst, शून्य, शून्य);
	newsk->sk_route_caps = dst->dev->features & ~(NETIF_F_IP_CSUM |
						      NETIF_F_TSO);
	newdp6 = (काष्ठा dccp6_sock *)newsk;
	newinet = inet_sk(newsk);
	newinet->pinet6 = &newdp6->inet6;
	newnp = inet6_sk(newsk);

	स_नकल(newnp, np, माप(काष्ठा ipv6_pinfo));

	newsk->sk_v6_daddr	= ireq->ir_v6_rmt_addr;
	newnp->saddr		= ireq->ir_v6_loc_addr;
	newsk->sk_v6_rcv_saddr	= ireq->ir_v6_loc_addr;
	newsk->sk_bound_dev_अगर	= ireq->ir_iअगर;

	/* Now IPv6 options...

	   First: no IPv4 options.
	 */
	newinet->inet_opt = शून्य;

	/* Clone RX bits */
	newnp->rxopt.all = np->rxopt.all;

	newnp->ipv6_mc_list = शून्य;
	newnp->ipv6_ac_list = शून्य;
	newnp->ipv6_fl_list = शून्य;
	newnp->pktoptions = शून्य;
	newnp->opt	  = शून्य;
	newnp->mcast_oअगर  = inet6_iअगर(skb);
	newnp->mcast_hops = ipv6_hdr(skb)->hop_limit;

	/*
	 * Clone native IPv6 options from listening socket (अगर any)
	 *
	 * Yes, keeping reference count would be much more clever, but we make
	 * one more one thing there: reattach opपंचांगem to newsk.
	 */
	opt = ireq->ipv6_opt;
	अगर (!opt)
		opt = rcu_dereference(np->opt);
	अगर (opt) अणु
		opt = ipv6_dup_options(newsk, opt);
		RCU_INIT_POINTER(newnp->opt, opt);
	पूर्ण
	inet_csk(newsk)->icsk_ext_hdr_len = 0;
	अगर (opt)
		inet_csk(newsk)->icsk_ext_hdr_len = opt->opt_nflen +
						    opt->opt_flen;

	dccp_sync_mss(newsk, dst_mtu(dst));

	newinet->inet_daddr = newinet->inet_saddr = LOOPBACK4_IPV6;
	newinet->inet_rcv_saddr = LOOPBACK4_IPV6;

	अगर (__inet_inherit_port(sk, newsk) < 0) अणु
		inet_csk_prepare_क्रमced_बंद(newsk);
		dccp_करोne(newsk);
		जाओ out;
	पूर्ण
	*own_req = inet_ehash_nolisten(newsk, req_to_sk(req_unhash), शून्य);
	/* Clone pktoptions received with SYN, अगर we own the req */
	अगर (*own_req && ireq->pktopts) अणु
		newnp->pktoptions = skb_clone(ireq->pktopts, GFP_ATOMIC);
		consume_skb(ireq->pktopts);
		ireq->pktopts = शून्य;
		अगर (newnp->pktoptions)
			skb_set_owner_r(newnp->pktoptions, newsk);
	पूर्ण

	वापस newsk;

out_overflow:
	__NET_INC_STATS(sock_net(sk), LINUX_MIB_LISTENOVERFLOWS);
out_nonewsk:
	dst_release(dst);
out:
	__NET_INC_STATS(sock_net(sk), LINUX_MIB_LISTENDROPS);
	वापस शून्य;
पूर्ण

/* The socket must have it's spinlock held when we get
 * here.
 *
 * We have a potential द्विगुन-lock हाल here, so even when
 * करोing backlog processing we use the BH locking scheme.
 * This is because we cannot sleep with the original spinlock
 * held.
 */
अटल पूर्णांक dccp_v6_करो_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा sk_buff *opt_skb = शून्य;

	/* Imagine: socket is IPv6. IPv4 packet arrives,
	   goes to IPv4 receive handler and backlogged.
	   From backlog it always goes here. Kerboom...
	   Fortunately, dccp_rcv_established and rcv_established
	   handle them correctly, but it is not हाल with
	   dccp_v6_hnd_req and dccp_v6_ctl_send_reset().   --ANK
	 */

	अगर (skb->protocol == htons(ETH_P_IP))
		वापस dccp_v4_करो_rcv(sk, skb);

	अगर (sk_filter(sk, skb))
		जाओ discard;

	/*
	 * socket locking is here क्रम SMP purposes as backlog rcv is currently
	 * called with bh processing disabled.
	 */

	/* Do Stevens' IPV6_PKTOPTIONS.

	   Yes, guys, it is the only place in our code, where we
	   may make it not affecting IPv4.
	   The rest of code is protocol independent,
	   and I करो not like idea to uglअगरy IPv4.

	   Actually, all the idea behind IPV6_PKTOPTIONS
	   looks not very well thought. For now we latch
	   options, received in the last packet, enqueued
	   by tcp. Feel मुक्त to propose better solution.
					       --ANK (980728)
	 */
	अगर (np->rxopt.all)
		opt_skb = skb_clone(skb, GFP_ATOMIC);

	अगर (sk->sk_state == DCCP_OPEN) अणु /* Fast path */
		अगर (dccp_rcv_established(sk, skb, dccp_hdr(skb), skb->len))
			जाओ reset;
		अगर (opt_skb)
			जाओ ipv6_pktoptions;
		वापस 0;
	पूर्ण

	/*
	 *  Step 3: Process LISTEN state
	 *     If S.state == LISTEN,
	 *	 If P.type == Request or P contains a valid Init Cookie option,
	 *	      (* Must scan the packet's options to check क्रम Init
	 *		 Cookies.  Only Init Cookies are processed here,
	 *		 however; other options are processed in Step 8.  This
	 *		 scan need only be perक्रमmed अगर the endpoपूर्णांक uses Init
	 *		 Cookies *)
	 *	      (* Generate a new socket and चयन to that socket *)
	 *	      Set S := new socket क्रम this port pair
	 *	      S.state = RESPOND
	 *	      Choose S.ISS (initial seqno) or set from Init Cookies
	 *	      Initialize S.GAR := S.ISS
	 *	      Set S.ISR, S.GSR, S.SWL, S.SWH from packet or Init Cookies
	 *	      Continue with S.state == RESPOND
	 *	      (* A Response packet will be generated in Step 11 *)
	 *	 Otherwise,
	 *	      Generate Reset(No Connection) unless P.type == Reset
	 *	      Drop packet and वापस
	 *
	 * NOTE: the check क्रम the packet types is करोne in
	 *	 dccp_rcv_state_process
	 */

	अगर (dccp_rcv_state_process(sk, skb, dccp_hdr(skb), skb->len))
		जाओ reset;
	अगर (opt_skb)
		जाओ ipv6_pktoptions;
	वापस 0;

reset:
	dccp_v6_ctl_send_reset(sk, skb);
discard:
	अगर (opt_skb != शून्य)
		__kमुक्त_skb(opt_skb);
	kमुक्त_skb(skb);
	वापस 0;

/* Handling IPV6_PKTOPTIONS skb the similar
 * way it's करोne क्रम net/ipv6/tcp_ipv6.c
 */
ipv6_pktoptions:
	अगर (!((1 << sk->sk_state) & (DCCPF_CLOSED | DCCPF_LISTEN))) अणु
		अगर (np->rxopt.bits.rxinfo || np->rxopt.bits.rxoinfo)
			np->mcast_oअगर = inet6_iअगर(opt_skb);
		अगर (np->rxopt.bits.rxhlim || np->rxopt.bits.rxohlim)
			np->mcast_hops = ipv6_hdr(opt_skb)->hop_limit;
		अगर (np->rxopt.bits.rxflow || np->rxopt.bits.rxtclass)
			np->rcv_flowinfo = ip6_flowinfo(ipv6_hdr(opt_skb));
		अगर (np->repflow)
			np->flow_label = ip6_flowlabel(ipv6_hdr(opt_skb));
		अगर (ipv6_opt_accepted(sk, opt_skb,
				      &DCCP_SKB_CB(opt_skb)->header.h6)) अणु
			skb_set_owner_r(opt_skb, sk);
			स_हटाओ(IP6CB(opt_skb),
				&DCCP_SKB_CB(opt_skb)->header.h6,
				माप(काष्ठा inet6_skb_parm));
			opt_skb = xchg(&np->pktoptions, opt_skb);
		पूर्ण अन्यथा अणु
			__kमुक्त_skb(opt_skb);
			opt_skb = xchg(&np->pktoptions, शून्य);
		पूर्ण
	पूर्ण

	kमुक्त_skb(opt_skb);
	वापस 0;
पूर्ण

अटल पूर्णांक dccp_v6_rcv(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा dccp_hdr *dh;
	bool refcounted;
	काष्ठा sock *sk;
	पूर्णांक min_cov;

	/* Step 1: Check header basics */

	अगर (dccp_invalid_packet(skb))
		जाओ discard_it;

	/* Step 1: If header checksum is incorrect, drop packet and वापस. */
	अगर (dccp_v6_csum_finish(skb, &ipv6_hdr(skb)->saddr,
				     &ipv6_hdr(skb)->daddr)) अणु
		DCCP_WARN("dropped packet with invalid checksum\n");
		जाओ discard_it;
	पूर्ण

	dh = dccp_hdr(skb);

	DCCP_SKB_CB(skb)->dccpd_seq  = dccp_hdr_seq(dh);
	DCCP_SKB_CB(skb)->dccpd_type = dh->dccph_type;

	अगर (dccp_packet_without_ack(skb))
		DCCP_SKB_CB(skb)->dccpd_ack_seq = DCCP_PKT_WITHOUT_ACK_SEQ;
	अन्यथा
		DCCP_SKB_CB(skb)->dccpd_ack_seq = dccp_hdr_ack_seq(skb);

lookup:
	sk = __inet6_lookup_skb(&dccp_hashinfo, skb, __dccp_hdr_len(dh),
			        dh->dccph_sport, dh->dccph_dport,
				inet6_iअगर(skb), 0, &refcounted);
	अगर (!sk) अणु
		dccp_pr_debug("failed to look up flow ID in table and "
			      "get corresponding socket\n");
		जाओ no_dccp_socket;
	पूर्ण

	/*
	 * Step 2:
	 *	... or S.state == TIMEWAIT,
	 *		Generate Reset(No Connection) unless P.type == Reset
	 *		Drop packet and वापस
	 */
	अगर (sk->sk_state == DCCP_TIME_WAIT) अणु
		dccp_pr_debug("sk->sk_state == DCCP_TIME_WAIT: do_time_wait\n");
		inet_twsk_put(inet_twsk(sk));
		जाओ no_dccp_socket;
	पूर्ण

	अगर (sk->sk_state == DCCP_NEW_SYN_RECV) अणु
		काष्ठा request_sock *req = inet_reqsk(sk);
		काष्ठा sock *nsk;

		sk = req->rsk_listener;
		अगर (unlikely(sk->sk_state != DCCP_LISTEN)) अणु
			inet_csk_reqsk_queue_drop_and_put(sk, req);
			जाओ lookup;
		पूर्ण
		sock_hold(sk);
		refcounted = true;
		nsk = dccp_check_req(sk, skb, req);
		अगर (!nsk) अणु
			reqsk_put(req);
			जाओ discard_and_rअन्यथा;
		पूर्ण
		अगर (nsk == sk) अणु
			reqsk_put(req);
		पूर्ण अन्यथा अगर (dccp_child_process(sk, nsk, skb)) अणु
			dccp_v6_ctl_send_reset(sk, skb);
			जाओ discard_and_rअन्यथा;
		पूर्ण अन्यथा अणु
			sock_put(sk);
			वापस 0;
		पूर्ण
	पूर्ण
	/*
	 * RFC 4340, sec. 9.2.1: Minimum Checksum Coverage
	 *	o अगर MinCsCov = 0, only packets with CsCov = 0 are accepted
	 *	o अगर MinCsCov > 0, also accept packets with CsCov >= MinCsCov
	 */
	min_cov = dccp_sk(sk)->dccps_pcrlen;
	अगर (dh->dccph_cscov  &&  (min_cov == 0 || dh->dccph_cscov < min_cov))  अणु
		dccp_pr_debug("Packet CsCov %d does not satisfy MinCsCov %d\n",
			      dh->dccph_cscov, min_cov);
		/* FIXME: send Data Dropped option (see also dccp_v4_rcv) */
		जाओ discard_and_rअन्यथा;
	पूर्ण

	अगर (!xfrm6_policy_check(sk, XFRM_POLICY_IN, skb))
		जाओ discard_and_rअन्यथा;

	वापस __sk_receive_skb(sk, skb, 1, dh->dccph_करोff * 4,
				refcounted) ? -1 : 0;

no_dccp_socket:
	अगर (!xfrm6_policy_check(शून्य, XFRM_POLICY_IN, skb))
		जाओ discard_it;
	/*
	 * Step 2:
	 *	If no socket ...
	 *		Generate Reset(No Connection) unless P.type == Reset
	 *		Drop packet and वापस
	 */
	अगर (dh->dccph_type != DCCP_PKT_RESET) अणु
		DCCP_SKB_CB(skb)->dccpd_reset_code =
					DCCP_RESET_CODE_NO_CONNECTION;
		dccp_v6_ctl_send_reset(sk, skb);
	पूर्ण

discard_it:
	kमुक्त_skb(skb);
	वापस 0;

discard_and_rअन्यथा:
	अगर (refcounted)
		sock_put(sk);
	जाओ discard_it;
पूर्ण

अटल पूर्णांक dccp_v6_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr,
			   पूर्णांक addr_len)
अणु
	काष्ठा sockaddr_in6 *usin = (काष्ठा sockaddr_in6 *)uaddr;
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	काष्ठा in6_addr *saddr = शून्य, *final_p, final;
	काष्ठा ipv6_txoptions *opt;
	काष्ठा flowi6 fl6;
	काष्ठा dst_entry *dst;
	पूर्णांक addr_type;
	पूर्णांक err;

	dp->dccps_role = DCCP_ROLE_CLIENT;

	अगर (addr_len < SIN6_LEN_RFC2133)
		वापस -EINVAL;

	अगर (usin->sin6_family != AF_INET6)
		वापस -EAFNOSUPPORT;

	स_रखो(&fl6, 0, माप(fl6));

	अगर (np->sndflow) अणु
		fl6.flowlabel = usin->sin6_flowinfo & IPV6_FLOWINFO_MASK;
		IP6_ECN_flow_init(fl6.flowlabel);
		अगर (fl6.flowlabel & IPV6_FLOWLABEL_MASK) अणु
			काष्ठा ip6_flowlabel *flowlabel;
			flowlabel = fl6_sock_lookup(sk, fl6.flowlabel);
			अगर (IS_ERR(flowlabel))
				वापस -EINVAL;
			fl6_sock_release(flowlabel);
		पूर्ण
	पूर्ण
	/*
	 * connect() to INADDR_ANY means loopback (BSD'ism).
	 */
	अगर (ipv6_addr_any(&usin->sin6_addr))
		usin->sin6_addr.s6_addr[15] = 1;

	addr_type = ipv6_addr_type(&usin->sin6_addr);

	अगर (addr_type & IPV6_ADDR_MULTICAST)
		वापस -ENETUNREACH;

	अगर (addr_type & IPV6_ADDR_LINKLOCAL) अणु
		अगर (addr_len >= माप(काष्ठा sockaddr_in6) &&
		    usin->sin6_scope_id) अणु
			/* If पूर्णांकerface is set जबतक binding, indices
			 * must coincide.
			 */
			अगर (sk->sk_bound_dev_अगर &&
			    sk->sk_bound_dev_अगर != usin->sin6_scope_id)
				वापस -EINVAL;

			sk->sk_bound_dev_अगर = usin->sin6_scope_id;
		पूर्ण

		/* Connect to link-local address requires an पूर्णांकerface */
		अगर (!sk->sk_bound_dev_अगर)
			वापस -EINVAL;
	पूर्ण

	sk->sk_v6_daddr = usin->sin6_addr;
	np->flow_label = fl6.flowlabel;

	/*
	 * DCCP over IPv4
	 */
	अगर (addr_type == IPV6_ADDR_MAPPED) अणु
		u32 exthdrlen = icsk->icsk_ext_hdr_len;
		काष्ठा sockaddr_in sin;

		SOCK_DEBUG(sk, "connect: ipv4 mapped\n");

		अगर (__ipv6_only_sock(sk))
			वापस -ENETUNREACH;

		sin.sin_family = AF_INET;
		sin.sin_port = usin->sin6_port;
		sin.sin_addr.s_addr = usin->sin6_addr.s6_addr32[3];

		icsk->icsk_af_ops = &dccp_ipv6_mapped;
		sk->sk_backlog_rcv = dccp_v4_करो_rcv;

		err = dccp_v4_connect(sk, (काष्ठा sockaddr *)&sin, माप(sin));
		अगर (err) अणु
			icsk->icsk_ext_hdr_len = exthdrlen;
			icsk->icsk_af_ops = &dccp_ipv6_af_ops;
			sk->sk_backlog_rcv = dccp_v6_करो_rcv;
			जाओ failure;
		पूर्ण
		np->saddr = sk->sk_v6_rcv_saddr;
		वापस err;
	पूर्ण

	अगर (!ipv6_addr_any(&sk->sk_v6_rcv_saddr))
		saddr = &sk->sk_v6_rcv_saddr;

	fl6.flowi6_proto = IPPROTO_DCCP;
	fl6.daddr = sk->sk_v6_daddr;
	fl6.saddr = saddr ? *saddr : np->saddr;
	fl6.flowi6_oअगर = sk->sk_bound_dev_अगर;
	fl6.fl6_dport = usin->sin6_port;
	fl6.fl6_sport = inet->inet_sport;
	security_sk_classअगरy_flow(sk, flowi6_to_flowi_common(&fl6));

	opt = rcu_dereference_रक्षित(np->opt, lockdep_sock_is_held(sk));
	final_p = fl6_update_dst(&fl6, opt, &final);

	dst = ip6_dst_lookup_flow(sock_net(sk), sk, &fl6, final_p);
	अगर (IS_ERR(dst)) अणु
		err = PTR_ERR(dst);
		जाओ failure;
	पूर्ण

	अगर (saddr == शून्य) अणु
		saddr = &fl6.saddr;
		sk->sk_v6_rcv_saddr = *saddr;
	पूर्ण

	/* set the source address */
	np->saddr = *saddr;
	inet->inet_rcv_saddr = LOOPBACK4_IPV6;

	ip6_dst_store(sk, dst, शून्य, शून्य);

	icsk->icsk_ext_hdr_len = 0;
	अगर (opt)
		icsk->icsk_ext_hdr_len = opt->opt_flen + opt->opt_nflen;

	inet->inet_dport = usin->sin6_port;

	dccp_set_state(sk, DCCP_REQUESTING);
	err = inet6_hash_connect(&dccp_death_row, sk);
	अगर (err)
		जाओ late_failure;

	dp->dccps_iss = secure_dccpv6_sequence_number(np->saddr.s6_addr32,
						      sk->sk_v6_daddr.s6_addr32,
						      inet->inet_sport,
						      inet->inet_dport);
	err = dccp_connect(sk);
	अगर (err)
		जाओ late_failure;

	वापस 0;

late_failure:
	dccp_set_state(sk, DCCP_CLOSED);
	__sk_dst_reset(sk);
failure:
	inet->inet_dport = 0;
	sk->sk_route_caps = 0;
	वापस err;
पूर्ण

अटल स्थिर काष्ठा inet_connection_sock_af_ops dccp_ipv6_af_ops = अणु
	.queue_xmit	   = inet6_csk_xmit,
	.send_check	   = dccp_v6_send_check,
	.rebuild_header	   = inet6_sk_rebuild_header,
	.conn_request	   = dccp_v6_conn_request,
	.syn_recv_sock	   = dccp_v6_request_recv_sock,
	.net_header_len	   = माप(काष्ठा ipv6hdr),
	.setsockopt	   = ipv6_setsockopt,
	.माला_लोockopt	   = ipv6_माला_लोockopt,
	.addr2sockaddr	   = inet6_csk_addr2sockaddr,
	.sockaddr_len	   = माप(काष्ठा sockaddr_in6),
पूर्ण;

/*
 *	DCCP over IPv4 via INET6 API
 */
अटल स्थिर काष्ठा inet_connection_sock_af_ops dccp_ipv6_mapped = अणु
	.queue_xmit	   = ip_queue_xmit,
	.send_check	   = dccp_v4_send_check,
	.rebuild_header	   = inet_sk_rebuild_header,
	.conn_request	   = dccp_v6_conn_request,
	.syn_recv_sock	   = dccp_v6_request_recv_sock,
	.net_header_len	   = माप(काष्ठा iphdr),
	.setsockopt	   = ipv6_setsockopt,
	.माला_लोockopt	   = ipv6_माला_लोockopt,
	.addr2sockaddr	   = inet6_csk_addr2sockaddr,
	.sockaddr_len	   = माप(काष्ठा sockaddr_in6),
पूर्ण;

/* NOTE: A lot of things set to zero explicitly by call to
 *       sk_alloc() so need not be करोne here.
 */
अटल पूर्णांक dccp_v6_init_sock(काष्ठा sock *sk)
अणु
	अटल __u8 dccp_v6_ctl_sock_initialized;
	पूर्णांक err = dccp_init_sock(sk, dccp_v6_ctl_sock_initialized);

	अगर (err == 0) अणु
		अगर (unlikely(!dccp_v6_ctl_sock_initialized))
			dccp_v6_ctl_sock_initialized = 1;
		inet_csk(sk)->icsk_af_ops = &dccp_ipv6_af_ops;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम dccp_v6_destroy_sock(काष्ठा sock *sk)
अणु
	dccp_destroy_sock(sk);
	inet6_destroy_sock(sk);
पूर्ण

अटल काष्ठा समयरुको_sock_ops dccp6_समयरुको_sock_ops = अणु
	.twsk_obj_size	= माप(काष्ठा dccp6_समयरुको_sock),
पूर्ण;

अटल काष्ठा proto dccp_v6_prot = अणु
	.name		   = "DCCPv6",
	.owner		   = THIS_MODULE,
	.बंद		   = dccp_बंद,
	.connect	   = dccp_v6_connect,
	.disconnect	   = dccp_disconnect,
	.ioctl		   = dccp_ioctl,
	.init		   = dccp_v6_init_sock,
	.setsockopt	   = dccp_setsockopt,
	.माला_लोockopt	   = dccp_माला_लोockopt,
	.sendmsg	   = dccp_sendmsg,
	.recvmsg	   = dccp_recvmsg,
	.backlog_rcv	   = dccp_v6_करो_rcv,
	.hash		   = inet6_hash,
	.unhash		   = inet_unhash,
	.accept		   = inet_csk_accept,
	.get_port	   = inet_csk_get_port,
	.shutकरोwn	   = dccp_shutकरोwn,
	.destroy	   = dccp_v6_destroy_sock,
	.orphan_count	   = &dccp_orphan_count,
	.max_header	   = MAX_DCCP_HEADER,
	.obj_size	   = माप(काष्ठा dccp6_sock),
	.slab_flags	   = SLAB_TYPESAFE_BY_RCU,
	.rsk_prot	   = &dccp6_request_sock_ops,
	.twsk_prot	   = &dccp6_समयरुको_sock_ops,
	.h.hashinfo	   = &dccp_hashinfo,
पूर्ण;

अटल स्थिर काष्ठा inet6_protocol dccp_v6_protocol = अणु
	.handler	= dccp_v6_rcv,
	.err_handler	= dccp_v6_err,
	.flags		= INET6_PROTO_NOPOLICY | INET6_PROTO_FINAL,
पूर्ण;

अटल स्थिर काष्ठा proto_ops inet6_dccp_ops = अणु
	.family		   = PF_INET6,
	.owner		   = THIS_MODULE,
	.release	   = inet6_release,
	.bind		   = inet6_bind,
	.connect	   = inet_stream_connect,
	.socketpair	   = sock_no_socketpair,
	.accept		   = inet_accept,
	.getname	   = inet6_getname,
	.poll		   = dccp_poll,
	.ioctl		   = inet6_ioctl,
	.gettstamp	   = sock_gettstamp,
	.listen		   = inet_dccp_listen,
	.shutकरोwn	   = inet_shutकरोwn,
	.setsockopt	   = sock_common_setsockopt,
	.माला_लोockopt	   = sock_common_माला_लोockopt,
	.sendmsg	   = inet_sendmsg,
	.recvmsg	   = sock_common_recvmsg,
	.mmap		   = sock_no_mmap,
	.sendpage	   = sock_no_sendpage,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	   = inet6_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा inet_protosw dccp_v6_protosw = अणु
	.type		= SOCK_DCCP,
	.protocol	= IPPROTO_DCCP,
	.prot		= &dccp_v6_prot,
	.ops		= &inet6_dccp_ops,
	.flags		= INET_PROTOSW_ICSK,
पूर्ण;

अटल पूर्णांक __net_init dccp_v6_init_net(काष्ठा net *net)
अणु
	काष्ठा dccp_v6_pernet *pn = net_generic(net, dccp_v6_pernet_id);

	अगर (dccp_hashinfo.bhash == शून्य)
		वापस -ESOCKTNOSUPPORT;

	वापस inet_ctl_sock_create(&pn->v6_ctl_sk, PF_INET6,
				    SOCK_DCCP, IPPROTO_DCCP, net);
पूर्ण

अटल व्योम __net_निकास dccp_v6_निकास_net(काष्ठा net *net)
अणु
	काष्ठा dccp_v6_pernet *pn = net_generic(net, dccp_v6_pernet_id);

	inet_ctl_sock_destroy(pn->v6_ctl_sk);
पूर्ण

अटल व्योम __net_निकास dccp_v6_निकास_batch(काष्ठा list_head *net_निकास_list)
अणु
	inet_twsk_purge(&dccp_hashinfo, AF_INET6);
पूर्ण

अटल काष्ठा pernet_operations dccp_v6_ops = अणु
	.init   = dccp_v6_init_net,
	.निकास   = dccp_v6_निकास_net,
	.निकास_batch = dccp_v6_निकास_batch,
	.id	= &dccp_v6_pernet_id,
	.size   = माप(काष्ठा dccp_v6_pernet),
पूर्ण;

अटल पूर्णांक __init dccp_v6_init(व्योम)
अणु
	पूर्णांक err = proto_रेजिस्टर(&dccp_v6_prot, 1);

	अगर (err)
		जाओ out;

	inet6_रेजिस्टर_protosw(&dccp_v6_protosw);

	err = रेजिस्टर_pernet_subsys(&dccp_v6_ops);
	अगर (err)
		जाओ out_destroy_ctl_sock;

	err = inet6_add_protocol(&dccp_v6_protocol, IPPROTO_DCCP);
	अगर (err)
		जाओ out_unरेजिस्टर_proto;

out:
	वापस err;
out_unरेजिस्टर_proto:
	unरेजिस्टर_pernet_subsys(&dccp_v6_ops);
out_destroy_ctl_sock:
	inet6_unरेजिस्टर_protosw(&dccp_v6_protosw);
	proto_unरेजिस्टर(&dccp_v6_prot);
	जाओ out;
पूर्ण

अटल व्योम __निकास dccp_v6_निकास(व्योम)
अणु
	inet6_del_protocol(&dccp_v6_protocol, IPPROTO_DCCP);
	unरेजिस्टर_pernet_subsys(&dccp_v6_ops);
	inet6_unरेजिस्टर_protosw(&dccp_v6_protosw);
	proto_unरेजिस्टर(&dccp_v6_prot);
पूर्ण

module_init(dccp_v6_init);
module_निकास(dccp_v6_निकास);

/*
 * __stringअगरy करोesn't likes क्रमागतs, so use SOCK_DCCP (6) and IPPROTO_DCCP (33)
 * values directly, Also cover the हाल where the protocol is not specअगरied,
 * i.e. net-pf-PF_INET6-proto-0-type-SOCK_DCCP
 */
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_INET6, 33, 6);
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_INET6, 0, 6);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arnaldo Carvalho de Melo <acme@mandriva.com>");
MODULE_DESCRIPTION("DCCPv6 - Datagram Congestion Controlled Protocol");
