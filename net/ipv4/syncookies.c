<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Syncookies implementation क्रम the Linux kernel
 *
 *  Copyright (C) 1997 Andi Kleen
 *  Based on ideas by D.J.Bernstein and Eric Schenk.
 */

#समावेश <linux/tcp.h>
#समावेश <linux/slab.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/siphash.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <net/secure_seq.h>
#समावेश <net/tcp.h>
#समावेश <net/route.h>

अटल siphash_key_t syncookie_secret[2] __पढ़ो_mostly;

#घोषणा COOKIEBITS 24	/* Upper bits store count */
#घोषणा COOKIEMASK (((__u32)1 << COOKIEBITS) - 1)

/* TCP Timestamp: 6 lowest bits of बारtamp sent in the cookie SYN-ACK
 * stores TCP options:
 *
 * MSB                               LSB
 * | 31 ...   6 |  5  |  4   | 3 2 1 0 |
 * |  Timestamp | ECN | SACK | WScale  |
 *
 * When we receive a valid cookie-ACK, we look at the echoed tsval (अगर
 * any) to figure out which TCP options we should use क्रम the rebuilt
 * connection.
 *
 * A WScale setting of '0xf' (which is an invalid scaling value)
 * means that original syn did not include the TCP winकरोw scaling option.
 */
#घोषणा TS_OPT_WSCALE_MASK	0xf
#घोषणा TS_OPT_SACK		BIT(4)
#घोषणा TS_OPT_ECN		BIT(5)
/* There is no TS_OPT_TIMESTAMP:
 * अगर ACK contains बारtamp option, we alपढ़ोy know it was
 * requested/supported by the syn/synack exchange.
 */
#घोषणा TSBITS	6
#घोषणा TSMASK	(((__u32)1 << TSBITS) - 1)

अटल u32 cookie_hash(__be32 saddr, __be32 daddr, __be16 sport, __be16 dport,
		       u32 count, पूर्णांक c)
अणु
	net_get_अक्रमom_once(syncookie_secret, माप(syncookie_secret));
	वापस siphash_4u32((__क्रमce u32)saddr, (__क्रमce u32)daddr,
			    (__क्रमce u32)sport << 16 | (__क्रमce u32)dport,
			    count, &syncookie_secret[c]);
पूर्ण


/*
 * when syncookies are in effect and tcp बारtamps are enabled we encode
 * tcp options in the lower bits of the बारtamp value that will be
 * sent in the syn-ack.
 * Since subsequent बारtamps use the normal tcp_समय_stamp value, we
 * must make sure that the resulting initial बारtamp is <= tcp_समय_stamp.
 */
u64 cookie_init_बारtamp(काष्ठा request_sock *req, u64 now)
अणु
	काष्ठा inet_request_sock *ireq;
	u32 ts, ts_now = tcp_ns_to_ts(now);
	u32 options = 0;

	ireq = inet_rsk(req);

	options = ireq->wscale_ok ? ireq->snd_wscale : TS_OPT_WSCALE_MASK;
	अगर (ireq->sack_ok)
		options |= TS_OPT_SACK;
	अगर (ireq->ecn_ok)
		options |= TS_OPT_ECN;

	ts = ts_now & ~TSMASK;
	ts |= options;
	अगर (ts > ts_now) अणु
		ts >>= TSBITS;
		ts--;
		ts <<= TSBITS;
		ts |= options;
	पूर्ण
	वापस (u64)ts * (NSEC_PER_SEC / TCP_TS_HZ);
पूर्ण


अटल __u32 secure_tcp_syn_cookie(__be32 saddr, __be32 daddr, __be16 sport,
				   __be16 dport, __u32 sseq, __u32 data)
अणु
	/*
	 * Compute the secure sequence number.
	 * The output should be:
	 *   HASH(sec1,saddr,sport,daddr,dport,sec1) + sseq + (count * 2^24)
	 *      + (HASH(sec2,saddr,sport,daddr,dport,count,sec2) % 2^24).
	 * Where sseq is their sequence number and count increases every
	 * minute by 1.
	 * As an extra hack, we add a small "data" value that encodes the
	 * MSS पूर्णांकo the second hash value.
	 */
	u32 count = tcp_cookie_समय();
	वापस (cookie_hash(saddr, daddr, sport, dport, 0, 0) +
		sseq + (count << COOKIEBITS) +
		((cookie_hash(saddr, daddr, sport, dport, count, 1) + data)
		 & COOKIEMASK));
पूर्ण

/*
 * This retrieves the small "data" value from the syncookie.
 * If the syncookie is bad, the data वापसed will be out of
 * range.  This must be checked by the caller.
 *
 * The count value used to generate the cookie must be less than
 * MAX_SYNCOOKIE_AGE minutes in the past.
 * The वापस value (__u32)-1 अगर this test fails.
 */
अटल __u32 check_tcp_syn_cookie(__u32 cookie, __be32 saddr, __be32 daddr,
				  __be16 sport, __be16 dport, __u32 sseq)
अणु
	u32 dअगरf, count = tcp_cookie_समय();

	/* Strip away the layers from the cookie */
	cookie -= cookie_hash(saddr, daddr, sport, dport, 0, 0) + sseq;

	/* Cookie is now reduced to (count * 2^24) ^ (hash % 2^24) */
	dअगरf = (count - (cookie >> COOKIEBITS)) & ((__u32) -1 >> COOKIEBITS);
	अगर (dअगरf >= MAX_SYNCOOKIE_AGE)
		वापस (__u32)-1;

	वापस (cookie -
		cookie_hash(saddr, daddr, sport, dport, count - dअगरf, 1))
		& COOKIEMASK;	/* Leaving the data behind */
पूर्ण

/*
 * MSS Values are chosen based on the 2011 paper
 * 'An Analysis of TCP Maximum Segement Sizes' by S. Alcock and R. Nelson.
 * Values ..
 *  .. lower than 536 are rare (< 0.2%)
 *  .. between 537 and 1299 account क्रम less than < 1.5% of observed values
 *  .. in the 1300-1349 range account क्रम about 15 to 20% of observed mss values
 *  .. exceeding 1460 are very rare (< 0.04%)
 *
 *  1460 is the single most frequently announced mss value (30 to 46% depending
 *  on monitor location).  Table must be sorted.
 */
अटल __u16 स्थिर msstab[] = अणु
	536,
	1300,
	1440,	/* 1440, 1452: PPPoE */
	1460,
पूर्ण;

/*
 * Generate a syncookie.  mssp poपूर्णांकs to the mss, which is वापसed
 * rounded करोwn to the value encoded in the cookie.
 */
u32 __cookie_v4_init_sequence(स्थिर काष्ठा iphdr *iph, स्थिर काष्ठा tcphdr *th,
			      u16 *mssp)
अणु
	पूर्णांक mssind;
	स्थिर __u16 mss = *mssp;

	क्रम (mssind = ARRAY_SIZE(msstab) - 1; mssind ; mssind--)
		अगर (mss >= msstab[mssind])
			अवरोध;
	*mssp = msstab[mssind];

	वापस secure_tcp_syn_cookie(iph->saddr, iph->daddr,
				     th->source, th->dest, ntohl(th->seq),
				     mssind);
पूर्ण
EXPORT_SYMBOL_GPL(__cookie_v4_init_sequence);

__u32 cookie_v4_init_sequence(स्थिर काष्ठा sk_buff *skb, __u16 *mssp)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	स्थिर काष्ठा tcphdr *th = tcp_hdr(skb);

	वापस __cookie_v4_init_sequence(iph, th, mssp);
पूर्ण

/*
 * Check अगर a ack sequence number is a valid syncookie.
 * Return the decoded mss अगर it is, or 0 अगर not.
 */
पूर्णांक __cookie_v4_check(स्थिर काष्ठा iphdr *iph, स्थिर काष्ठा tcphdr *th,
		      u32 cookie)
अणु
	__u32 seq = ntohl(th->seq) - 1;
	__u32 mssind = check_tcp_syn_cookie(cookie, iph->saddr, iph->daddr,
					    th->source, th->dest, seq);

	वापस mssind < ARRAY_SIZE(msstab) ? msstab[mssind] : 0;
पूर्ण
EXPORT_SYMBOL_GPL(__cookie_v4_check);

काष्ठा sock *tcp_get_cookie_sock(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				 काष्ठा request_sock *req,
				 काष्ठा dst_entry *dst, u32 tsoff)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा sock *child;
	bool own_req;

	child = icsk->icsk_af_ops->syn_recv_sock(sk, skb, req, dst,
						 शून्य, &own_req);
	अगर (child) अणु
		refcount_set(&req->rsk_refcnt, 1);
		tcp_sk(child)->tsoffset = tsoff;
		sock_rps_save_rxhash(child, skb);

		अगर (rsk_drop_req(req)) अणु
			reqsk_put(req);
			वापस child;
		पूर्ण

		अगर (inet_csk_reqsk_queue_add(sk, req, child))
			वापस child;

		bh_unlock_sock(child);
		sock_put(child);
	पूर्ण
	__reqsk_मुक्त(req);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(tcp_get_cookie_sock);

/*
 * when syncookies are in effect and tcp बारtamps are enabled we stored
 * additional tcp options in the बारtamp.
 * This extracts these options from the बारtamp echo.
 *
 * वापस false अगर we decode a tcp option that is disabled
 * on the host.
 */
bool cookie_बारtamp_decode(स्थिर काष्ठा net *net,
			     काष्ठा tcp_options_received *tcp_opt)
अणु
	/* echoed बारtamp, lowest bits contain options */
	u32 options = tcp_opt->rcv_tsecr;

	अगर (!tcp_opt->saw_tstamp)  अणु
		tcp_clear_options(tcp_opt);
		वापस true;
	पूर्ण

	अगर (!net->ipv4.sysctl_tcp_बारtamps)
		वापस false;

	tcp_opt->sack_ok = (options & TS_OPT_SACK) ? TCP_SACK_SEEN : 0;

	अगर (tcp_opt->sack_ok && !net->ipv4.sysctl_tcp_sack)
		वापस false;

	अगर ((options & TS_OPT_WSCALE_MASK) == TS_OPT_WSCALE_MASK)
		वापस true; /* no winकरोw scaling */

	tcp_opt->wscale_ok = 1;
	tcp_opt->snd_wscale = options & TS_OPT_WSCALE_MASK;

	वापस net->ipv4.sysctl_tcp_winकरोw_scaling != 0;
पूर्ण
EXPORT_SYMBOL(cookie_बारtamp_decode);

bool cookie_ecn_ok(स्थिर काष्ठा tcp_options_received *tcp_opt,
		   स्थिर काष्ठा net *net, स्थिर काष्ठा dst_entry *dst)
अणु
	bool ecn_ok = tcp_opt->rcv_tsecr & TS_OPT_ECN;

	अगर (!ecn_ok)
		वापस false;

	अगर (net->ipv4.sysctl_tcp_ecn)
		वापस true;

	वापस dst_feature(dst, RTAX_FEATURE_ECN);
पूर्ण
EXPORT_SYMBOL(cookie_ecn_ok);

काष्ठा request_sock *cookie_tcp_reqsk_alloc(स्थिर काष्ठा request_sock_ops *ops,
					    काष्ठा sock *sk,
					    काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_request_sock *treq;
	काष्ठा request_sock *req;

#अगर_घोषित CONFIG_MPTCP
	अगर (sk_is_mptcp(sk))
		ops = &mptcp_subflow_request_sock_ops;
#पूर्ण_अगर

	req = inet_reqsk_alloc(ops, sk, false);
	अगर (!req)
		वापस शून्य;

	treq = tcp_rsk(req);
	treq->syn_tos = TCP_SKB_CB(skb)->ip_dsfield;
#अगर IS_ENABLED(CONFIG_MPTCP)
	treq->is_mptcp = sk_is_mptcp(sk);
	अगर (treq->is_mptcp) अणु
		पूर्णांक err = mptcp_subflow_init_cookie_req(req, sk, skb);

		अगर (err) अणु
			reqsk_मुक्त(req);
			वापस शून्य;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	वापस req;
पूर्ण
EXPORT_SYMBOL_GPL(cookie_tcp_reqsk_alloc);

/* On input, sk is a listener.
 * Output is listener अगर incoming packet would not create a child
 *           शून्य अगर memory could not be allocated.
 */
काष्ठा sock *cookie_v4_check(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा ip_options *opt = &TCP_SKB_CB(skb)->header.h4.opt;
	काष्ठा tcp_options_received tcp_opt;
	काष्ठा inet_request_sock *ireq;
	काष्ठा tcp_request_sock *treq;
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	स्थिर काष्ठा tcphdr *th = tcp_hdr(skb);
	__u32 cookie = ntohl(th->ack_seq) - 1;
	काष्ठा sock *ret = sk;
	काष्ठा request_sock *req;
	पूर्णांक full_space, mss;
	काष्ठा rtable *rt;
	__u8 rcv_wscale;
	काष्ठा flowi4 fl4;
	u32 tsoff = 0;

	अगर (!sock_net(sk)->ipv4.sysctl_tcp_syncookies || !th->ack || th->rst)
		जाओ out;

	अगर (tcp_synq_no_recent_overflow(sk))
		जाओ out;

	mss = __cookie_v4_check(ip_hdr(skb), th, cookie);
	अगर (mss == 0) अणु
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_SYNCOOKIESFAILED);
		जाओ out;
	पूर्ण

	__NET_INC_STATS(sock_net(sk), LINUX_MIB_SYNCOOKIESRECV);

	/* check क्रम बारtamp cookie support */
	स_रखो(&tcp_opt, 0, माप(tcp_opt));
	tcp_parse_options(sock_net(sk), skb, &tcp_opt, 0, शून्य);

	अगर (tcp_opt.saw_tstamp && tcp_opt.rcv_tsecr) अणु
		tsoff = secure_tcp_ts_off(sock_net(sk),
					  ip_hdr(skb)->daddr,
					  ip_hdr(skb)->saddr);
		tcp_opt.rcv_tsecr -= tsoff;
	पूर्ण

	अगर (!cookie_बारtamp_decode(sock_net(sk), &tcp_opt))
		जाओ out;

	ret = शून्य;
	req = cookie_tcp_reqsk_alloc(&tcp_request_sock_ops, sk, skb);
	अगर (!req)
		जाओ out;

	ireq = inet_rsk(req);
	treq = tcp_rsk(req);
	treq->rcv_isn		= ntohl(th->seq) - 1;
	treq->snt_isn		= cookie;
	treq->ts_off		= 0;
	treq->txhash		= net_tx_rndhash();
	req->mss		= mss;
	ireq->ir_num		= ntohs(th->dest);
	ireq->ir_rmt_port	= th->source;
	sk_rcv_saddr_set(req_to_sk(req), ip_hdr(skb)->daddr);
	sk_daddr_set(req_to_sk(req), ip_hdr(skb)->saddr);
	ireq->ir_mark		= inet_request_mark(sk, skb);
	ireq->snd_wscale	= tcp_opt.snd_wscale;
	ireq->sack_ok		= tcp_opt.sack_ok;
	ireq->wscale_ok		= tcp_opt.wscale_ok;
	ireq->tstamp_ok		= tcp_opt.saw_tstamp;
	req->ts_recent		= tcp_opt.saw_tstamp ? tcp_opt.rcv_tsval : 0;
	treq->snt_synack	= 0;
	treq->tfo_listener	= false;

	अगर (IS_ENABLED(CONFIG_SMC))
		ireq->smc_ok = 0;

	ireq->ir_iअगर = inet_request_bound_dev_अगर(sk, skb);

	/* We throwed the options of the initial SYN away, so we hope
	 * the ACK carries the same options again (see RFC1122 4.2.3.8)
	 */
	RCU_INIT_POINTER(ireq->ireq_opt, tcp_v4_save_options(sock_net(sk), skb));

	अगर (security_inet_conn_request(sk, skb, req)) अणु
		reqsk_मुक्त(req);
		जाओ out;
	पूर्ण

	req->num_retrans = 0;

	/*
	 * We need to lookup the route here to get at the correct
	 * winकरोw size. We should better make sure that the winकरोw size
	 * hasn't changed since we received the original syn, but I see
	 * no easy way to करो this.
	 */
	flowi4_init_output(&fl4, ireq->ir_iअगर, ireq->ir_mark,
			   RT_CONN_FLAGS(sk), RT_SCOPE_UNIVERSE, IPPROTO_TCP,
			   inet_sk_flowi_flags(sk),
			   opt->srr ? opt->faddr : ireq->ir_rmt_addr,
			   ireq->ir_loc_addr, th->source, th->dest, sk->sk_uid);
	security_req_classअगरy_flow(req, flowi4_to_flowi_common(&fl4));
	rt = ip_route_output_key(sock_net(sk), &fl4);
	अगर (IS_ERR(rt)) अणु
		reqsk_मुक्त(req);
		जाओ out;
	पूर्ण

	/* Try to reकरो what tcp_v4_send_synack did. */
	req->rsk_winकरोw_clamp = tp->winकरोw_clamp ? :dst_metric(&rt->dst, RTAX_WINDOW);
	/* limit the winकरोw selection अगर the user enक्रमce a smaller rx buffer */
	full_space = tcp_full_space(sk);
	अगर (sk->sk_userlocks & SOCK_RCVBUF_LOCK &&
	    (req->rsk_winकरोw_clamp > full_space || req->rsk_winकरोw_clamp == 0))
		req->rsk_winकरोw_clamp = full_space;

	tcp_select_initial_winकरोw(sk, full_space, req->mss,
				  &req->rsk_rcv_wnd, &req->rsk_winकरोw_clamp,
				  ireq->wscale_ok, &rcv_wscale,
				  dst_metric(&rt->dst, RTAX_INITRWND));

	ireq->rcv_wscale  = rcv_wscale;
	ireq->ecn_ok = cookie_ecn_ok(&tcp_opt, sock_net(sk), &rt->dst);

	ret = tcp_get_cookie_sock(sk, skb, req, &rt->dst, tsoff);
	/* ip_queue_xmit() depends on our flow being setup
	 * Normal sockets get it right from inet_csk_route_child_sock()
	 */
	अगर (ret)
		inet_sk(ret)->cork.fl.u.ip4 = fl4;
out:	वापस ret;
पूर्ण
