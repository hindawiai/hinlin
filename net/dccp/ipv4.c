<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  net/dccp/ipv4.c
 *
 *  An implementation of the DCCP protocol
 *  Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 */

#समावेश <linux/dccp.h>
#समावेश <linux/icmp.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अक्रमom.h>

#समावेश <net/icmp.h>
#समावेश <net/inet_common.h>
#समावेश <net/inet_hashtables.h>
#समावेश <net/inet_sock.h>
#समावेश <net/protocol.h>
#समावेश <net/sock.h>
#समावेश <net/समयरुको_sock.h>
#समावेश <net/tcp_states.h>
#समावेश <net/xfrm.h>
#समावेश <net/secure_seq.h>
#समावेश <net/netns/generic.h>

#समावेश "ackvec.h"
#समावेश "ccid.h"
#समावेश "dccp.h"
#समावेश "feat.h"

काष्ठा dccp_v4_pernet अणु
	काष्ठा sock *v4_ctl_sk;
पूर्ण;

अटल अचिन्हित पूर्णांक dccp_v4_pernet_id __पढ़ो_mostly;

/*
 * The per-net v4_ctl_sk socket is used क्रम responding to
 * the Out-of-the-blue (OOTB) packets. A control sock will be created
 * क्रम this socket at the initialization समय.
 */

पूर्णांक dccp_v4_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	स्थिर काष्ठा sockaddr_in *usin = (काष्ठा sockaddr_in *)uaddr;
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	__be16 orig_sport, orig_dport;
	__be32 daddr, nexthop;
	काष्ठा flowi4 *fl4;
	काष्ठा rtable *rt;
	पूर्णांक err;
	काष्ठा ip_options_rcu *inet_opt;

	dp->dccps_role = DCCP_ROLE_CLIENT;

	अगर (addr_len < माप(काष्ठा sockaddr_in))
		वापस -EINVAL;

	अगर (usin->sin_family != AF_INET)
		वापस -EAFNOSUPPORT;

	nexthop = daddr = usin->sin_addr.s_addr;

	inet_opt = rcu_dereference_रक्षित(inet->inet_opt,
					     lockdep_sock_is_held(sk));
	अगर (inet_opt != शून्य && inet_opt->opt.srr) अणु
		अगर (daddr == 0)
			वापस -EINVAL;
		nexthop = inet_opt->opt.faddr;
	पूर्ण

	orig_sport = inet->inet_sport;
	orig_dport = usin->sin_port;
	fl4 = &inet->cork.fl.u.ip4;
	rt = ip_route_connect(fl4, nexthop, inet->inet_saddr,
			      RT_CONN_FLAGS(sk), sk->sk_bound_dev_अगर,
			      IPPROTO_DCCP,
			      orig_sport, orig_dport, sk);
	अगर (IS_ERR(rt))
		वापस PTR_ERR(rt);

	अगर (rt->rt_flags & (RTCF_MULTICAST | RTCF_BROADCAST)) अणु
		ip_rt_put(rt);
		वापस -ENETUNREACH;
	पूर्ण

	अगर (inet_opt == शून्य || !inet_opt->opt.srr)
		daddr = fl4->daddr;

	अगर (inet->inet_saddr == 0)
		inet->inet_saddr = fl4->saddr;
	sk_rcv_saddr_set(sk, inet->inet_saddr);
	inet->inet_dport = usin->sin_port;
	sk_daddr_set(sk, daddr);

	inet_csk(sk)->icsk_ext_hdr_len = 0;
	अगर (inet_opt)
		inet_csk(sk)->icsk_ext_hdr_len = inet_opt->opt.optlen;
	/*
	 * Socket identity is still unknown (sport may be zero).
	 * However we set state to DCCP_REQUESTING and not releasing socket
	 * lock select source port, enter ourselves पूर्णांकo the hash tables and
	 * complete initialization after this.
	 */
	dccp_set_state(sk, DCCP_REQUESTING);
	err = inet_hash_connect(&dccp_death_row, sk);
	अगर (err != 0)
		जाओ failure;

	rt = ip_route_newports(fl4, rt, orig_sport, orig_dport,
			       inet->inet_sport, inet->inet_dport, sk);
	अगर (IS_ERR(rt)) अणु
		err = PTR_ERR(rt);
		rt = शून्य;
		जाओ failure;
	पूर्ण
	/* OK, now commit destination to socket.  */
	sk_setup_caps(sk, &rt->dst);

	dp->dccps_iss = secure_dccp_sequence_number(inet->inet_saddr,
						    inet->inet_daddr,
						    inet->inet_sport,
						    inet->inet_dport);
	inet->inet_id = pअक्रमom_u32();

	err = dccp_connect(sk);
	rt = शून्य;
	अगर (err != 0)
		जाओ failure;
out:
	वापस err;
failure:
	/*
	 * This unhashes the socket and releases the local port, अगर necessary.
	 */
	dccp_set_state(sk, DCCP_CLOSED);
	ip_rt_put(rt);
	sk->sk_route_caps = 0;
	inet->inet_dport = 0;
	जाओ out;
पूर्ण
EXPORT_SYMBOL_GPL(dccp_v4_connect);

/*
 * This routine करोes path mtu discovery as defined in RFC1191.
 */
अटल अंतरभूत व्योम dccp_करो_pmtu_discovery(काष्ठा sock *sk,
					  स्थिर काष्ठा iphdr *iph,
					  u32 mtu)
अणु
	काष्ठा dst_entry *dst;
	स्थिर काष्ठा inet_sock *inet = inet_sk(sk);
	स्थिर काष्ठा dccp_sock *dp = dccp_sk(sk);

	/* We are not पूर्णांकerested in DCCP_LISTEN and request_socks (RESPONSEs
	 * send out by Linux are always < 576bytes so they should go through
	 * unfragmented).
	 */
	अगर (sk->sk_state == DCCP_LISTEN)
		वापस;

	dst = inet_csk_update_pmtu(sk, mtu);
	अगर (!dst)
		वापस;

	/* Something is about to be wrong... Remember soft error
	 * क्रम the हाल, अगर this connection will not able to recover.
	 */
	अगर (mtu < dst_mtu(dst) && ip_करोnt_fragment(sk, dst))
		sk->sk_err_soft = EMSGSIZE;

	mtu = dst_mtu(dst);

	अगर (inet->pmtudisc != IP_PMTUDISC_DONT &&
	    ip_sk_accept_pmtu(sk) &&
	    inet_csk(sk)->icsk_pmtu_cookie > mtu) अणु
		dccp_sync_mss(sk, mtu);

		/*
		 * From RFC 4340, sec. 14.1:
		 *
		 *	DCCP-Sync packets are the best choice क्रम upward
		 *	probing, since DCCP-Sync probes करो not risk application
		 *	data loss.
		 */
		dccp_send_sync(sk, dp->dccps_gsr, DCCP_PKT_SYNC);
	पूर्ण /* अन्यथा let the usual retransmit समयr handle it */
पूर्ण

अटल व्योम dccp_करो_redirect(काष्ठा sk_buff *skb, काष्ठा sock *sk)
अणु
	काष्ठा dst_entry *dst = __sk_dst_check(sk, 0);

	अगर (dst)
		dst->ops->redirect(dst, sk, skb);
पूर्ण

व्योम dccp_req_err(काष्ठा sock *sk, u64 seq)
	अणु
	काष्ठा request_sock *req = inet_reqsk(sk);
	काष्ठा net *net = sock_net(sk);

	/*
	 * ICMPs are not backlogged, hence we cannot get an established
	 * socket here.
	 */
	अगर (!between48(seq, dccp_rsk(req)->dreq_iss, dccp_rsk(req)->dreq_gss)) अणु
		__NET_INC_STATS(net, LINUX_MIB_OUTOFWINDOWICMPS);
	पूर्ण अन्यथा अणु
		/*
		 * Still in RESPOND, just हटाओ it silently.
		 * There is no good way to pass the error to the newly
		 * created socket, and POSIX करोes not want network
		 * errors वापसed from accept().
		 */
		inet_csk_reqsk_queue_drop(req->rsk_listener, req);
	पूर्ण
	reqsk_put(req);
पूर्ण
EXPORT_SYMBOL(dccp_req_err);

/*
 * This routine is called by the ICMP module when it माला_लो some sort of error
 * condition. If err < 0 then the socket should be बंदd and the error
 * वापसed to the user. If err > 0 it's just the icmp type << 8 | icmp code.
 * After adjusपंचांगent header poपूर्णांकs to the first 8 bytes of the tcp header. We
 * need to find the appropriate port.
 *
 * The locking strategy used here is very "optimistic". When someone अन्यथा
 * accesses the socket the ICMP is just dropped and क्रम some paths there is no
 * check at all. A more general error queue to queue errors क्रम later handling
 * is probably better.
 */
अटल पूर्णांक dccp_v4_err(काष्ठा sk_buff *skb, u32 info)
अणु
	स्थिर काष्ठा iphdr *iph = (काष्ठा iphdr *)skb->data;
	स्थिर u8 offset = iph->ihl << 2;
	स्थिर काष्ठा dccp_hdr *dh;
	काष्ठा dccp_sock *dp;
	काष्ठा inet_sock *inet;
	स्थिर पूर्णांक type = icmp_hdr(skb)->type;
	स्थिर पूर्णांक code = icmp_hdr(skb)->code;
	काष्ठा sock *sk;
	__u64 seq;
	पूर्णांक err;
	काष्ठा net *net = dev_net(skb->dev);

	/* Only need dccph_dport & dccph_sport which are the first
	 * 4 bytes in dccp header.
	 * Our caller (icmp_socket_deliver()) alपढ़ोy pulled 8 bytes क्रम us.
	 */
	BUILD_BUG_ON(दुरत्वend(काष्ठा dccp_hdr, dccph_sport) > 8);
	BUILD_BUG_ON(दुरत्वend(काष्ठा dccp_hdr, dccph_dport) > 8);
	dh = (काष्ठा dccp_hdr *)(skb->data + offset);

	sk = __inet_lookup_established(net, &dccp_hashinfo,
				       iph->daddr, dh->dccph_dport,
				       iph->saddr, ntohs(dh->dccph_sport),
				       inet_iअगर(skb), 0);
	अगर (!sk) अणु
		__ICMP_INC_STATS(net, ICMP_MIB_INERRORS);
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
	/* If too many ICMPs get dropped on busy
	 * servers this needs to be solved dअगरferently.
	 */
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

	चयन (type) अणु
	हाल ICMP_REसूचीECT:
		अगर (!sock_owned_by_user(sk))
			dccp_करो_redirect(skb, sk);
		जाओ out;
	हाल ICMP_SOURCE_QUENCH:
		/* Just silently ignore these. */
		जाओ out;
	हाल ICMP_PARAMETERPROB:
		err = EPROTO;
		अवरोध;
	हाल ICMP_DEST_UNREACH:
		अगर (code > NR_ICMP_UNREACH)
			जाओ out;

		अगर (code == ICMP_FRAG_NEEDED) अणु /* PMTU discovery (RFC1191) */
			अगर (!sock_owned_by_user(sk))
				dccp_करो_pmtu_discovery(sk, iph, info);
			जाओ out;
		पूर्ण

		err = icmp_err_convert[code].त्रुटि_सं;
		अवरोध;
	हाल ICMP_TIME_EXCEEDED:
		err = EHOSTUNREACH;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	चयन (sk->sk_state) अणु
	हाल DCCP_REQUESTING:
	हाल DCCP_RESPOND:
		अगर (!sock_owned_by_user(sk)) अणु
			__DCCP_INC_STATS(DCCP_MIB_ATTEMPTFAILS);
			sk->sk_err = err;

			sk->sk_error_report(sk);

			dccp_करोne(sk);
		पूर्ण अन्यथा
			sk->sk_err_soft = err;
		जाओ out;
	पूर्ण

	/* If we've alपढ़ोy connected we will keep trying
	 * until we समय out, or the user gives up.
	 *
	 * rfc1122 4.2.3.9 allows to consider as hard errors
	 * only PROTO_UNREACH and PORT_UNREACH (well, FRAG_FAILED too,
	 * but it is obsoleted by pmtu discovery).
	 *
	 * Note, that in modern पूर्णांकernet, where routing is unreliable
	 * and in each dark corner broken firewalls sit, sending अक्रमom
	 * errors ordered by their masters even this two messages finally lose
	 * their original sense (even Linux sends invalid PORT_UNREACHs)
	 *
	 * Now we are in compliance with RFCs.
	 *							--ANK (980905)
	 */

	inet = inet_sk(sk);
	अगर (!sock_owned_by_user(sk) && inet->recverr) अणु
		sk->sk_err = err;
		sk->sk_error_report(sk);
	पूर्ण अन्यथा /* Only an error on समयout */
		sk->sk_err_soft = err;
out:
	bh_unlock_sock(sk);
	sock_put(sk);
	वापस 0;
पूर्ण

अटल अंतरभूत __sum16 dccp_v4_csum_finish(काष्ठा sk_buff *skb,
				      __be32 src, __be32 dst)
अणु
	वापस csum_tcpudp_magic(src, dst, skb->len, IPPROTO_DCCP, skb->csum);
पूर्ण

व्योम dccp_v4_send_check(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा dccp_hdr *dh = dccp_hdr(skb);

	dccp_csum_outgoing(skb);
	dh->dccph_checksum = dccp_v4_csum_finish(skb,
						 inet->inet_saddr,
						 inet->inet_daddr);
पूर्ण
EXPORT_SYMBOL_GPL(dccp_v4_send_check);

अटल अंतरभूत u64 dccp_v4_init_sequence(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस secure_dccp_sequence_number(ip_hdr(skb)->daddr,
					   ip_hdr(skb)->saddr,
					   dccp_hdr(skb)->dccph_dport,
					   dccp_hdr(skb)->dccph_sport);
पूर्ण

/*
 * The three way handshake has completed - we got a valid ACK or DATAACK -
 * now create the new socket.
 *
 * This is the equivalent of TCP's tcp_v4_syn_recv_sock
 */
काष्ठा sock *dccp_v4_request_recv_sock(स्थिर काष्ठा sock *sk,
				       काष्ठा sk_buff *skb,
				       काष्ठा request_sock *req,
				       काष्ठा dst_entry *dst,
				       काष्ठा request_sock *req_unhash,
				       bool *own_req)
अणु
	काष्ठा inet_request_sock *ireq;
	काष्ठा inet_sock *newinet;
	काष्ठा sock *newsk;

	अगर (sk_acceptq_is_full(sk))
		जाओ निकास_overflow;

	newsk = dccp_create_खोलोreq_child(sk, req, skb);
	अगर (newsk == शून्य)
		जाओ निकास_nonewsk;

	newinet		   = inet_sk(newsk);
	ireq		   = inet_rsk(req);
	sk_daddr_set(newsk, ireq->ir_rmt_addr);
	sk_rcv_saddr_set(newsk, ireq->ir_loc_addr);
	newinet->inet_saddr	= ireq->ir_loc_addr;
	RCU_INIT_POINTER(newinet->inet_opt, rcu_dereference(ireq->ireq_opt));
	newinet->mc_index  = inet_iअगर(skb);
	newinet->mc_ttl	   = ip_hdr(skb)->ttl;
	newinet->inet_id   = pअक्रमom_u32();

	अगर (dst == शून्य && (dst = inet_csk_route_child_sock(sk, newsk, req)) == शून्य)
		जाओ put_and_निकास;

	sk_setup_caps(newsk, dst);

	dccp_sync_mss(newsk, dst_mtu(dst));

	अगर (__inet_inherit_port(sk, newsk) < 0)
		जाओ put_and_निकास;
	*own_req = inet_ehash_nolisten(newsk, req_to_sk(req_unhash), शून्य);
	अगर (*own_req)
		ireq->ireq_opt = शून्य;
	अन्यथा
		newinet->inet_opt = शून्य;
	वापस newsk;

निकास_overflow:
	__NET_INC_STATS(sock_net(sk), LINUX_MIB_LISTENOVERFLOWS);
निकास_nonewsk:
	dst_release(dst);
निकास:
	__NET_INC_STATS(sock_net(sk), LINUX_MIB_LISTENDROPS);
	वापस शून्य;
put_and_निकास:
	newinet->inet_opt = शून्य;
	inet_csk_prepare_क्रमced_बंद(newsk);
	dccp_करोne(newsk);
	जाओ निकास;
पूर्ण
EXPORT_SYMBOL_GPL(dccp_v4_request_recv_sock);

अटल काष्ठा dst_entry* dccp_v4_route_skb(काष्ठा net *net, काष्ठा sock *sk,
					   काष्ठा sk_buff *skb)
अणु
	काष्ठा rtable *rt;
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	काष्ठा flowi4 fl4 = अणु
		.flowi4_oअगर = inet_iअगर(skb),
		.daddr = iph->saddr,
		.saddr = iph->daddr,
		.flowi4_tos = RT_CONN_FLAGS(sk),
		.flowi4_proto = sk->sk_protocol,
		.fl4_sport = dccp_hdr(skb)->dccph_dport,
		.fl4_dport = dccp_hdr(skb)->dccph_sport,
	पूर्ण;

	security_skb_classअगरy_flow(skb, flowi4_to_flowi_common(&fl4));
	rt = ip_route_output_flow(net, &fl4, sk);
	अगर (IS_ERR(rt)) अणु
		IP_INC_STATS(net, IPSTATS_MIB_OUTNOROUTES);
		वापस शून्य;
	पूर्ण

	वापस &rt->dst;
पूर्ण

अटल पूर्णांक dccp_v4_send_response(स्थिर काष्ठा sock *sk, काष्ठा request_sock *req)
अणु
	पूर्णांक err = -1;
	काष्ठा sk_buff *skb;
	काष्ठा dst_entry *dst;
	काष्ठा flowi4 fl4;

	dst = inet_csk_route_req(sk, &fl4, req);
	अगर (dst == शून्य)
		जाओ out;

	skb = dccp_make_response(sk, dst, req);
	अगर (skb != शून्य) अणु
		स्थिर काष्ठा inet_request_sock *ireq = inet_rsk(req);
		काष्ठा dccp_hdr *dh = dccp_hdr(skb);

		dh->dccph_checksum = dccp_v4_csum_finish(skb, ireq->ir_loc_addr,
							      ireq->ir_rmt_addr);
		rcu_पढ़ो_lock();
		err = ip_build_and_send_pkt(skb, sk, ireq->ir_loc_addr,
					    ireq->ir_rmt_addr,
					    rcu_dereference(ireq->ireq_opt),
					    inet_sk(sk)->tos);
		rcu_पढ़ो_unlock();
		err = net_xmit_eval(err);
	पूर्ण

out:
	dst_release(dst);
	वापस err;
पूर्ण

अटल व्योम dccp_v4_ctl_send_reset(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *rxskb)
अणु
	पूर्णांक err;
	स्थिर काष्ठा iphdr *rxiph;
	काष्ठा sk_buff *skb;
	काष्ठा dst_entry *dst;
	काष्ठा net *net = dev_net(skb_dst(rxskb)->dev);
	काष्ठा dccp_v4_pernet *pn;
	काष्ठा sock *ctl_sk;

	/* Never send a reset in response to a reset. */
	अगर (dccp_hdr(rxskb)->dccph_type == DCCP_PKT_RESET)
		वापस;

	अगर (skb_rtable(rxskb)->rt_type != RTN_LOCAL)
		वापस;

	pn = net_generic(net, dccp_v4_pernet_id);
	ctl_sk = pn->v4_ctl_sk;
	dst = dccp_v4_route_skb(net, ctl_sk, rxskb);
	अगर (dst == शून्य)
		वापस;

	skb = dccp_ctl_make_reset(ctl_sk, rxskb);
	अगर (skb == शून्य)
		जाओ out;

	rxiph = ip_hdr(rxskb);
	dccp_hdr(skb)->dccph_checksum = dccp_v4_csum_finish(skb, rxiph->saddr,
								 rxiph->daddr);
	skb_dst_set(skb, dst_clone(dst));

	local_bh_disable();
	bh_lock_sock(ctl_sk);
	err = ip_build_and_send_pkt(skb, ctl_sk,
				    rxiph->daddr, rxiph->saddr, शून्य,
				    inet_sk(ctl_sk)->tos);
	bh_unlock_sock(ctl_sk);

	अगर (net_xmit_eval(err) == 0) अणु
		__DCCP_INC_STATS(DCCP_MIB_OUTSEGS);
		__DCCP_INC_STATS(DCCP_MIB_OUTRSTS);
	पूर्ण
	local_bh_enable();
out:
	dst_release(dst);
पूर्ण

अटल व्योम dccp_v4_reqsk_deकाष्ठाor(काष्ठा request_sock *req)
अणु
	dccp_feat_list_purge(&dccp_rsk(req)->dreq_featneg);
	kमुक्त(rcu_dereference_रक्षित(inet_rsk(req)->ireq_opt, 1));
पूर्ण

व्योम dccp_syn_ack_समयout(स्थिर काष्ठा request_sock *req)
अणु
पूर्ण
EXPORT_SYMBOL(dccp_syn_ack_समयout);

अटल काष्ठा request_sock_ops dccp_request_sock_ops __पढ़ो_mostly = अणु
	.family		= PF_INET,
	.obj_size	= माप(काष्ठा dccp_request_sock),
	.rtx_syn_ack	= dccp_v4_send_response,
	.send_ack	= dccp_reqsk_send_ack,
	.deकाष्ठाor	= dccp_v4_reqsk_deकाष्ठाor,
	.send_reset	= dccp_v4_ctl_send_reset,
	.syn_ack_समयout = dccp_syn_ack_समयout,
पूर्ण;

पूर्णांक dccp_v4_conn_request(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा inet_request_sock *ireq;
	काष्ठा request_sock *req;
	काष्ठा dccp_request_sock *dreq;
	स्थिर __be32 service = dccp_hdr_request(skb)->dccph_req_service;
	काष्ठा dccp_skb_cb *dcb = DCCP_SKB_CB(skb);

	/* Never answer to DCCP_PKT_REQUESTs send to broadcast or multicast */
	अगर (skb_rtable(skb)->rt_flags & (RTCF_BROADCAST | RTCF_MULTICAST))
		वापस 0;	/* discard, करोn't send a reset here */

	अगर (dccp_bad_service_code(sk, service)) अणु
		dcb->dccpd_reset_code = DCCP_RESET_CODE_BAD_SERVICE_CODE;
		जाओ drop;
	पूर्ण
	/*
	 * TW buckets are converted to खोलो requests without
	 * limitations, they conserve resources and peer is
	 * evidently real one.
	 */
	dcb->dccpd_reset_code = DCCP_RESET_CODE_TOO_BUSY;
	अगर (inet_csk_reqsk_queue_is_full(sk))
		जाओ drop;

	अगर (sk_acceptq_is_full(sk))
		जाओ drop;

	req = inet_reqsk_alloc(&dccp_request_sock_ops, sk, true);
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
	sk_rcv_saddr_set(req_to_sk(req), ip_hdr(skb)->daddr);
	sk_daddr_set(req_to_sk(req), ip_hdr(skb)->saddr);
	ireq->ir_mark = inet_request_mark(sk, skb);
	ireq->ireq_family = AF_INET;
	ireq->ir_iअगर = sk->sk_bound_dev_अगर;

	/*
	 * Step 3: Process LISTEN state
	 *
	 * Set S.ISR, S.GSR, S.SWL, S.SWH from packet or Init Cookie
	 *
	 * Setting S.SWL/S.SWH to is deferred to dccp_create_खोलोreq_child().
	 */
	dreq->dreq_isr	   = dcb->dccpd_seq;
	dreq->dreq_gsr	   = dreq->dreq_isr;
	dreq->dreq_iss	   = dccp_v4_init_sequence(skb);
	dreq->dreq_gss     = dreq->dreq_iss;
	dreq->dreq_service = service;

	अगर (dccp_v4_send_response(sk, req))
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
EXPORT_SYMBOL_GPL(dccp_v4_conn_request);

पूर्णांक dccp_v4_करो_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dccp_hdr *dh = dccp_hdr(skb);

	अगर (sk->sk_state == DCCP_OPEN) अणु /* Fast path */
		अगर (dccp_rcv_established(sk, skb, dh, skb->len))
			जाओ reset;
		वापस 0;
	पूर्ण

	/*
	 *  Step 3: Process LISTEN state
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

	अगर (dccp_rcv_state_process(sk, skb, dh, skb->len))
		जाओ reset;
	वापस 0;

reset:
	dccp_v4_ctl_send_reset(sk, skb);
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dccp_v4_करो_rcv);

/**
 *	dccp_invalid_packet  -  check क्रम malक्रमmed packets
 *	@skb: Packet to validate
 *
 *	Implements RFC 4340, 8.5:  Step 1: Check header basics
 *	Packets that fail these checks are ignored and करो not receive Resets.
 */
पूर्णांक dccp_invalid_packet(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा dccp_hdr *dh;
	अचिन्हित पूर्णांक cscov;
	u8 dccph_करोff;

	अगर (skb->pkt_type != PACKET_HOST)
		वापस 1;

	/* If the packet is लघुer than 12 bytes, drop packet and वापस */
	अगर (!pskb_may_pull(skb, माप(काष्ठा dccp_hdr))) अणु
		DCCP_WARN("pskb_may_pull failed\n");
		वापस 1;
	पूर्ण

	dh = dccp_hdr(skb);

	/* If P.type is not understood, drop packet and वापस */
	अगर (dh->dccph_type >= DCCP_PKT_INVALID) अणु
		DCCP_WARN("invalid packet type\n");
		वापस 1;
	पूर्ण

	/*
	 * If P.Data Offset is too small क्रम packet type, drop packet and वापस
	 */
	dccph_करोff = dh->dccph_करोff;
	अगर (dccph_करोff < dccp_hdr_len(skb) / माप(u32)) अणु
		DCCP_WARN("P.Data Offset(%u) too small\n", dccph_करोff);
		वापस 1;
	पूर्ण
	/*
	 * If P.Data Offset is too large क्रम packet, drop packet and वापस
	 */
	अगर (!pskb_may_pull(skb, dccph_करोff * माप(u32))) अणु
		DCCP_WARN("P.Data Offset(%u) too large\n", dccph_करोff);
		वापस 1;
	पूर्ण
	dh = dccp_hdr(skb);
	/*
	 * If P.type is not Data, Ack, or DataAck and P.X == 0 (the packet
	 * has लघु sequence numbers), drop packet and वापस
	 */
	अगर ((dh->dccph_type < DCCP_PKT_DATA    ||
	    dh->dccph_type > DCCP_PKT_DATAACK) && dh->dccph_x == 0)  अणु
		DCCP_WARN("P.type (%s) not Data || [Data]Ack, while P.X == 0\n",
			  dccp_packet_name(dh->dccph_type));
		वापस 1;
	पूर्ण

	/*
	 * If P.CsCov is too large क्रम the packet size, drop packet and वापस.
	 * This must come _beक्रमe_ checksumming (not as RFC 4340 suggests).
	 */
	cscov = dccp_csum_coverage(skb);
	अगर (cscov > skb->len) अणु
		DCCP_WARN("P.CsCov %u exceeds packet length %d\n",
			  dh->dccph_cscov, skb->len);
		वापस 1;
	पूर्ण

	/* If header checksum is incorrect, drop packet and वापस.
	 * (This step is completed in the AF-dependent functions.) */
	skb->csum = skb_checksum(skb, 0, cscov, 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dccp_invalid_packet);

/* this is called when real data arrives */
अटल पूर्णांक dccp_v4_rcv(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा dccp_hdr *dh;
	स्थिर काष्ठा iphdr *iph;
	bool refcounted;
	काष्ठा sock *sk;
	पूर्णांक min_cov;

	/* Step 1: Check header basics */

	अगर (dccp_invalid_packet(skb))
		जाओ discard_it;

	iph = ip_hdr(skb);
	/* Step 1: If header checksum is incorrect, drop packet and वापस */
	अगर (dccp_v4_csum_finish(skb, iph->saddr, iph->daddr)) अणु
		DCCP_WARN("dropped packet with invalid checksum\n");
		जाओ discard_it;
	पूर्ण

	dh = dccp_hdr(skb);

	DCCP_SKB_CB(skb)->dccpd_seq  = dccp_hdr_seq(dh);
	DCCP_SKB_CB(skb)->dccpd_type = dh->dccph_type;

	dccp_pr_debug("%8.8s src=%pI4@%-5d dst=%pI4@%-5d seq=%llu",
		      dccp_packet_name(dh->dccph_type),
		      &iph->saddr, ntohs(dh->dccph_sport),
		      &iph->daddr, ntohs(dh->dccph_dport),
		      (अचिन्हित दीर्घ दीर्घ) DCCP_SKB_CB(skb)->dccpd_seq);

	अगर (dccp_packet_without_ack(skb)) अणु
		DCCP_SKB_CB(skb)->dccpd_ack_seq = DCCP_PKT_WITHOUT_ACK_SEQ;
		dccp_pr_debug_cat("\n");
	पूर्ण अन्यथा अणु
		DCCP_SKB_CB(skb)->dccpd_ack_seq = dccp_hdr_ack_seq(skb);
		dccp_pr_debug_cat(", ack=%llu\n", (अचिन्हित दीर्घ दीर्घ)
				  DCCP_SKB_CB(skb)->dccpd_ack_seq);
	पूर्ण

lookup:
	sk = __inet_lookup_skb(&dccp_hashinfo, skb, __dccp_hdr_len(dh),
			       dh->dccph_sport, dh->dccph_dport, 0, &refcounted);
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
			dccp_v4_ctl_send_reset(sk, skb);
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
	अगर (dh->dccph_cscov && (min_cov == 0 || dh->dccph_cscov < min_cov))  अणु
		dccp_pr_debug("Packet CsCov %d does not satisfy MinCsCov %d\n",
			      dh->dccph_cscov, min_cov);
		/* FIXME: "Such packets SHOULD be reported using Data Dropped
		 *         options (Section 11.7) with Drop Code 0, Protocol
		 *         Constraपूर्णांकs."                                     */
		जाओ discard_and_rअन्यथा;
	पूर्ण

	अगर (!xfrm4_policy_check(sk, XFRM_POLICY_IN, skb))
		जाओ discard_and_rअन्यथा;
	nf_reset_ct(skb);

	वापस __sk_receive_skb(sk, skb, 1, dh->dccph_करोff * 4, refcounted);

no_dccp_socket:
	अगर (!xfrm4_policy_check(शून्य, XFRM_POLICY_IN, skb))
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
		dccp_v4_ctl_send_reset(sk, skb);
	पूर्ण

discard_it:
	kमुक्त_skb(skb);
	वापस 0;

discard_and_rअन्यथा:
	अगर (refcounted)
		sock_put(sk);
	जाओ discard_it;
पूर्ण

अटल स्थिर काष्ठा inet_connection_sock_af_ops dccp_ipv4_af_ops = अणु
	.queue_xmit	   = ip_queue_xmit,
	.send_check	   = dccp_v4_send_check,
	.rebuild_header	   = inet_sk_rebuild_header,
	.conn_request	   = dccp_v4_conn_request,
	.syn_recv_sock	   = dccp_v4_request_recv_sock,
	.net_header_len	   = माप(काष्ठा iphdr),
	.setsockopt	   = ip_setsockopt,
	.माला_लोockopt	   = ip_माला_लोockopt,
	.addr2sockaddr	   = inet_csk_addr2sockaddr,
	.sockaddr_len	   = माप(काष्ठा sockaddr_in),
पूर्ण;

अटल पूर्णांक dccp_v4_init_sock(काष्ठा sock *sk)
अणु
	अटल __u8 dccp_v4_ctl_sock_initialized;
	पूर्णांक err = dccp_init_sock(sk, dccp_v4_ctl_sock_initialized);

	अगर (err == 0) अणु
		अगर (unlikely(!dccp_v4_ctl_sock_initialized))
			dccp_v4_ctl_sock_initialized = 1;
		inet_csk(sk)->icsk_af_ops = &dccp_ipv4_af_ops;
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा समयरुको_sock_ops dccp_समयरुको_sock_ops = अणु
	.twsk_obj_size	= माप(काष्ठा inet_समयरुको_sock),
पूर्ण;

अटल काष्ठा proto dccp_v4_prot = अणु
	.name			= "DCCP",
	.owner			= THIS_MODULE,
	.बंद			= dccp_बंद,
	.connect		= dccp_v4_connect,
	.disconnect		= dccp_disconnect,
	.ioctl			= dccp_ioctl,
	.init			= dccp_v4_init_sock,
	.setsockopt		= dccp_setsockopt,
	.माला_लोockopt		= dccp_माला_लोockopt,
	.sendmsg		= dccp_sendmsg,
	.recvmsg		= dccp_recvmsg,
	.backlog_rcv		= dccp_v4_करो_rcv,
	.hash			= inet_hash,
	.unhash			= inet_unhash,
	.accept			= inet_csk_accept,
	.get_port		= inet_csk_get_port,
	.shutकरोwn		= dccp_shutकरोwn,
	.destroy		= dccp_destroy_sock,
	.orphan_count		= &dccp_orphan_count,
	.max_header		= MAX_DCCP_HEADER,
	.obj_size		= माप(काष्ठा dccp_sock),
	.slab_flags		= SLAB_TYPESAFE_BY_RCU,
	.rsk_prot		= &dccp_request_sock_ops,
	.twsk_prot		= &dccp_समयरुको_sock_ops,
	.h.hashinfo		= &dccp_hashinfo,
पूर्ण;

अटल स्थिर काष्ठा net_protocol dccp_v4_protocol = अणु
	.handler	= dccp_v4_rcv,
	.err_handler	= dccp_v4_err,
	.no_policy	= 1,
	.netns_ok	= 1,
	.icmp_strict_tag_validation = 1,
पूर्ण;

अटल स्थिर काष्ठा proto_ops inet_dccp_ops = अणु
	.family		   = PF_INET,
	.owner		   = THIS_MODULE,
	.release	   = inet_release,
	.bind		   = inet_bind,
	.connect	   = inet_stream_connect,
	.socketpair	   = sock_no_socketpair,
	.accept		   = inet_accept,
	.getname	   = inet_getname,
	/* FIXME: work on tcp_poll to नाम it to inet_csk_poll */
	.poll		   = dccp_poll,
	.ioctl		   = inet_ioctl,
	.gettstamp	   = sock_gettstamp,
	/* FIXME: work on inet_listen to नाम it to sock_common_listen */
	.listen		   = inet_dccp_listen,
	.shutकरोwn	   = inet_shutकरोwn,
	.setsockopt	   = sock_common_setsockopt,
	.माला_लोockopt	   = sock_common_माला_लोockopt,
	.sendmsg	   = inet_sendmsg,
	.recvmsg	   = sock_common_recvmsg,
	.mmap		   = sock_no_mmap,
	.sendpage	   = sock_no_sendpage,
पूर्ण;

अटल काष्ठा inet_protosw dccp_v4_protosw = अणु
	.type		= SOCK_DCCP,
	.protocol	= IPPROTO_DCCP,
	.prot		= &dccp_v4_prot,
	.ops		= &inet_dccp_ops,
	.flags		= INET_PROTOSW_ICSK,
पूर्ण;

अटल पूर्णांक __net_init dccp_v4_init_net(काष्ठा net *net)
अणु
	काष्ठा dccp_v4_pernet *pn = net_generic(net, dccp_v4_pernet_id);

	अगर (dccp_hashinfo.bhash == शून्य)
		वापस -ESOCKTNOSUPPORT;

	वापस inet_ctl_sock_create(&pn->v4_ctl_sk, PF_INET,
				    SOCK_DCCP, IPPROTO_DCCP, net);
पूर्ण

अटल व्योम __net_निकास dccp_v4_निकास_net(काष्ठा net *net)
अणु
	काष्ठा dccp_v4_pernet *pn = net_generic(net, dccp_v4_pernet_id);

	inet_ctl_sock_destroy(pn->v4_ctl_sk);
पूर्ण

अटल व्योम __net_निकास dccp_v4_निकास_batch(काष्ठा list_head *net_निकास_list)
अणु
	inet_twsk_purge(&dccp_hashinfo, AF_INET);
पूर्ण

अटल काष्ठा pernet_operations dccp_v4_ops = अणु
	.init	= dccp_v4_init_net,
	.निकास	= dccp_v4_निकास_net,
	.निकास_batch = dccp_v4_निकास_batch,
	.id	= &dccp_v4_pernet_id,
	.size   = माप(काष्ठा dccp_v4_pernet),
पूर्ण;

अटल पूर्णांक __init dccp_v4_init(व्योम)
अणु
	पूर्णांक err = proto_रेजिस्टर(&dccp_v4_prot, 1);

	अगर (err)
		जाओ out;

	inet_रेजिस्टर_protosw(&dccp_v4_protosw);

	err = रेजिस्टर_pernet_subsys(&dccp_v4_ops);
	अगर (err)
		जाओ out_destroy_ctl_sock;

	err = inet_add_protocol(&dccp_v4_protocol, IPPROTO_DCCP);
	अगर (err)
		जाओ out_proto_unरेजिस्टर;

out:
	वापस err;
out_proto_unरेजिस्टर:
	unरेजिस्टर_pernet_subsys(&dccp_v4_ops);
out_destroy_ctl_sock:
	inet_unरेजिस्टर_protosw(&dccp_v4_protosw);
	proto_unरेजिस्टर(&dccp_v4_prot);
	जाओ out;
पूर्ण

अटल व्योम __निकास dccp_v4_निकास(व्योम)
अणु
	inet_del_protocol(&dccp_v4_protocol, IPPROTO_DCCP);
	unरेजिस्टर_pernet_subsys(&dccp_v4_ops);
	inet_unरेजिस्टर_protosw(&dccp_v4_protosw);
	proto_unरेजिस्टर(&dccp_v4_prot);
पूर्ण

module_init(dccp_v4_init);
module_निकास(dccp_v4_निकास);

/*
 * __stringअगरy करोesn't likes क्रमागतs, so use SOCK_DCCP (6) and IPPROTO_DCCP (33)
 * values directly, Also cover the हाल where the protocol is not specअगरied,
 * i.e. net-pf-PF_INET-proto-0-type-SOCK_DCCP
 */
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_INET, 33, 6);
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_INET, 0, 6);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arnaldo Carvalho de Melo <acme@mandriva.com>");
MODULE_DESCRIPTION("DCCP - Datagram Congestion Controlled Protocol");
