<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  IPv6 Syncookies implementation क्रम the Linux kernel
 *
 *  Authors:
 *  Glenn Grअगरfin	<ggrअगरfin.kernel@gmail.com>
 *
 *  Based on IPv4 implementation by Andi Kleen
 *  linux/net/ipv4/syncookies.c
 */

#समावेश <linux/tcp.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/siphash.h>
#समावेश <linux/kernel.h>
#समावेश <net/secure_seq.h>
#समावेश <net/ipv6.h>
#समावेश <net/tcp.h>

#घोषणा COOKIEBITS 24	/* Upper bits store count */
#घोषणा COOKIEMASK (((__u32)1 << COOKIEBITS) - 1)

अटल siphash_key_t syncookie6_secret[2] __पढ़ो_mostly;

/* RFC 2460, Section 8.3:
 * [ipv6 tcp] MSS must be computed as the maximum packet size minus 60 [..]
 *
 * Due to IPV6_MIN_MTU=1280 the lowest possible MSS is 1220, which allows
 * using higher values than ipv4 tcp syncookies.
 * The other values are chosen based on ethernet (1500 and 9k MTU), plus
 * one that accounts क्रम common encap (PPPoe) overhead. Table must be sorted.
 */
अटल __u16 स्थिर msstab[] = अणु
	1280 - 60, /* IPV6_MIN_MTU - 60 */
	1480 - 60,
	1500 - 60,
	9000 - 60,
पूर्ण;

अटल u32 cookie_hash(स्थिर काष्ठा in6_addr *saddr,
		       स्थिर काष्ठा in6_addr *daddr,
		       __be16 sport, __be16 dport, u32 count, पूर्णांक c)
अणु
	स्थिर काष्ठा अणु
		काष्ठा in6_addr saddr;
		काष्ठा in6_addr daddr;
		u32 count;
		__be16 sport;
		__be16 dport;
	पूर्ण __aligned(SIPHASH_ALIGNMENT) combined = अणु
		.saddr = *saddr,
		.daddr = *daddr,
		.count = count,
		.sport = sport,
		.dport = dport
	पूर्ण;

	net_get_अक्रमom_once(syncookie6_secret, माप(syncookie6_secret));
	वापस siphash(&combined, दुरत्वend(typeof(combined), dport),
		       &syncookie6_secret[c]);
पूर्ण

अटल __u32 secure_tcp_syn_cookie(स्थिर काष्ठा in6_addr *saddr,
				   स्थिर काष्ठा in6_addr *daddr,
				   __be16 sport, __be16 dport, __u32 sseq,
				   __u32 data)
अणु
	u32 count = tcp_cookie_समय();
	वापस (cookie_hash(saddr, daddr, sport, dport, 0, 0) +
		sseq + (count << COOKIEBITS) +
		((cookie_hash(saddr, daddr, sport, dport, count, 1) + data)
		& COOKIEMASK));
पूर्ण

अटल __u32 check_tcp_syn_cookie(__u32 cookie, स्थिर काष्ठा in6_addr *saddr,
				  स्थिर काष्ठा in6_addr *daddr, __be16 sport,
				  __be16 dport, __u32 sseq)
अणु
	__u32 dअगरf, count = tcp_cookie_समय();

	cookie -= cookie_hash(saddr, daddr, sport, dport, 0, 0) + sseq;

	dअगरf = (count - (cookie >> COOKIEBITS)) & ((__u32) -1 >> COOKIEBITS);
	अगर (dअगरf >= MAX_SYNCOOKIE_AGE)
		वापस (__u32)-1;

	वापस (cookie -
		cookie_hash(saddr, daddr, sport, dport, count - dअगरf, 1))
		& COOKIEMASK;
पूर्ण

u32 __cookie_v6_init_sequence(स्थिर काष्ठा ipv6hdr *iph,
			      स्थिर काष्ठा tcphdr *th, __u16 *mssp)
अणु
	पूर्णांक mssind;
	स्थिर __u16 mss = *mssp;

	क्रम (mssind = ARRAY_SIZE(msstab) - 1; mssind ; mssind--)
		अगर (mss >= msstab[mssind])
			अवरोध;

	*mssp = msstab[mssind];

	वापस secure_tcp_syn_cookie(&iph->saddr, &iph->daddr, th->source,
				     th->dest, ntohl(th->seq), mssind);
पूर्ण
EXPORT_SYMBOL_GPL(__cookie_v6_init_sequence);

__u32 cookie_v6_init_sequence(स्थिर काष्ठा sk_buff *skb, __u16 *mssp)
अणु
	स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	स्थिर काष्ठा tcphdr *th = tcp_hdr(skb);

	वापस __cookie_v6_init_sequence(iph, th, mssp);
पूर्ण

पूर्णांक __cookie_v6_check(स्थिर काष्ठा ipv6hdr *iph, स्थिर काष्ठा tcphdr *th,
		      __u32 cookie)
अणु
	__u32 seq = ntohl(th->seq) - 1;
	__u32 mssind = check_tcp_syn_cookie(cookie, &iph->saddr, &iph->daddr,
					    th->source, th->dest, seq);

	वापस mssind < ARRAY_SIZE(msstab) ? msstab[mssind] : 0;
पूर्ण
EXPORT_SYMBOL_GPL(__cookie_v6_check);

काष्ठा sock *cookie_v6_check(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_options_received tcp_opt;
	काष्ठा inet_request_sock *ireq;
	काष्ठा tcp_request_sock *treq;
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	स्थिर काष्ठा tcphdr *th = tcp_hdr(skb);
	__u32 cookie = ntohl(th->ack_seq) - 1;
	काष्ठा sock *ret = sk;
	काष्ठा request_sock *req;
	पूर्णांक full_space, mss;
	काष्ठा dst_entry *dst;
	__u8 rcv_wscale;
	u32 tsoff = 0;

	अगर (!sock_net(sk)->ipv4.sysctl_tcp_syncookies || !th->ack || th->rst)
		जाओ out;

	अगर (tcp_synq_no_recent_overflow(sk))
		जाओ out;

	mss = __cookie_v6_check(ipv6_hdr(skb), th, cookie);
	अगर (mss == 0) अणु
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_SYNCOOKIESFAILED);
		जाओ out;
	पूर्ण

	__NET_INC_STATS(sock_net(sk), LINUX_MIB_SYNCOOKIESRECV);

	/* check क्रम बारtamp cookie support */
	स_रखो(&tcp_opt, 0, माप(tcp_opt));
	tcp_parse_options(sock_net(sk), skb, &tcp_opt, 0, शून्य);

	अगर (tcp_opt.saw_tstamp && tcp_opt.rcv_tsecr) अणु
		tsoff = secure_tcpv6_ts_off(sock_net(sk),
					    ipv6_hdr(skb)->daddr.s6_addr32,
					    ipv6_hdr(skb)->saddr.s6_addr32);
		tcp_opt.rcv_tsecr -= tsoff;
	पूर्ण

	अगर (!cookie_बारtamp_decode(sock_net(sk), &tcp_opt))
		जाओ out;

	ret = शून्य;
	req = cookie_tcp_reqsk_alloc(&tcp6_request_sock_ops, sk, skb);
	अगर (!req)
		जाओ out;

	ireq = inet_rsk(req);
	treq = tcp_rsk(req);
	treq->tfo_listener = false;

	अगर (security_inet_conn_request(sk, skb, req))
		जाओ out_मुक्त;

	req->mss = mss;
	ireq->ir_rmt_port = th->source;
	ireq->ir_num = ntohs(th->dest);
	ireq->ir_v6_rmt_addr = ipv6_hdr(skb)->saddr;
	ireq->ir_v6_loc_addr = ipv6_hdr(skb)->daddr;
	अगर (ipv6_opt_accepted(sk, skb, &TCP_SKB_CB(skb)->header.h6) ||
	    np->rxopt.bits.rxinfo || np->rxopt.bits.rxoinfo ||
	    np->rxopt.bits.rxhlim || np->rxopt.bits.rxohlim) अणु
		refcount_inc(&skb->users);
		ireq->pktopts = skb;
	पूर्ण

	ireq->ir_iअगर = inet_request_bound_dev_अगर(sk, skb);
	/* So that link locals have meaning */
	अगर (!sk->sk_bound_dev_अगर &&
	    ipv6_addr_type(&ireq->ir_v6_rmt_addr) & IPV6_ADDR_LINKLOCAL)
		ireq->ir_iअगर = tcp_v6_iअगर(skb);

	ireq->ir_mark = inet_request_mark(sk, skb);

	req->num_retrans = 0;
	ireq->snd_wscale	= tcp_opt.snd_wscale;
	ireq->sack_ok		= tcp_opt.sack_ok;
	ireq->wscale_ok		= tcp_opt.wscale_ok;
	ireq->tstamp_ok		= tcp_opt.saw_tstamp;
	req->ts_recent		= tcp_opt.saw_tstamp ? tcp_opt.rcv_tsval : 0;
	treq->snt_synack	= 0;
	treq->rcv_isn = ntohl(th->seq) - 1;
	treq->snt_isn = cookie;
	treq->ts_off = 0;
	treq->txhash = net_tx_rndhash();
	अगर (IS_ENABLED(CONFIG_SMC))
		ireq->smc_ok = 0;

	/*
	 * We need to lookup the dst_entry to get the correct winकरोw size.
	 * This is taken from tcp_v6_syn_recv_sock.  Somebody please enlighten
	 * me अगर there is a preferred way.
	 */
	अणु
		काष्ठा in6_addr *final_p, final;
		काष्ठा flowi6 fl6;
		स_रखो(&fl6, 0, माप(fl6));
		fl6.flowi6_proto = IPPROTO_TCP;
		fl6.daddr = ireq->ir_v6_rmt_addr;
		final_p = fl6_update_dst(&fl6, rcu_dereference(np->opt), &final);
		fl6.saddr = ireq->ir_v6_loc_addr;
		fl6.flowi6_oअगर = ireq->ir_iअगर;
		fl6.flowi6_mark = ireq->ir_mark;
		fl6.fl6_dport = ireq->ir_rmt_port;
		fl6.fl6_sport = inet_sk(sk)->inet_sport;
		fl6.flowi6_uid = sk->sk_uid;
		security_req_classअगरy_flow(req, flowi6_to_flowi_common(&fl6));

		dst = ip6_dst_lookup_flow(sock_net(sk), sk, &fl6, final_p);
		अगर (IS_ERR(dst))
			जाओ out_मुक्त;
	पूर्ण

	req->rsk_winकरोw_clamp = tp->winकरोw_clamp ? :dst_metric(dst, RTAX_WINDOW);
	/* limit the winकरोw selection अगर the user enक्रमce a smaller rx buffer */
	full_space = tcp_full_space(sk);
	अगर (sk->sk_userlocks & SOCK_RCVBUF_LOCK &&
	    (req->rsk_winकरोw_clamp > full_space || req->rsk_winकरोw_clamp == 0))
		req->rsk_winकरोw_clamp = full_space;

	tcp_select_initial_winकरोw(sk, full_space, req->mss,
				  &req->rsk_rcv_wnd, &req->rsk_winकरोw_clamp,
				  ireq->wscale_ok, &rcv_wscale,
				  dst_metric(dst, RTAX_INITRWND));

	ireq->rcv_wscale = rcv_wscale;
	ireq->ecn_ok = cookie_ecn_ok(&tcp_opt, sock_net(sk), dst);

	ret = tcp_get_cookie_sock(sk, skb, req, dst, tsoff);
out:
	वापस ret;
out_मुक्त:
	reqsk_मुक्त(req);
	वापस शून्य;
पूर्ण
