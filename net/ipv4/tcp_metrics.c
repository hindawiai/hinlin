<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/rcupdate.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/cache.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/tcp.h>
#समावेश <linux/hash.h>
#समावेश <linux/tcp_metrics.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <net/inet_connection_sock.h>
#समावेश <net/net_namespace.h>
#समावेश <net/request_sock.h>
#समावेश <net/inetpeer.h>
#समावेश <net/sock.h>
#समावेश <net/ipv6.h>
#समावेश <net/dst.h>
#समावेश <net/tcp.h>
#समावेश <net/genetlink.h>

अटल काष्ठा tcp_metrics_block *__tcp_get_metrics(स्थिर काष्ठा inetpeer_addr *saddr,
						   स्थिर काष्ठा inetpeer_addr *daddr,
						   काष्ठा net *net, अचिन्हित पूर्णांक hash);

काष्ठा tcp_fastखोलो_metrics अणु
	u16	mss;
	u16	syn_loss:10,		/* Recurring Fast Open SYN losses */
		try_exp:2;		/* Request w/ exp. option (once) */
	अचिन्हित दीर्घ	last_syn_loss;	/* Last Fast Open SYN loss */
	काष्ठा	tcp_fastखोलो_cookie	cookie;
पूर्ण;

/* TCP_METRIC_MAX includes 2 extra fields क्रम userspace compatibility
 * Kernel only stores RTT and RTTVAR in usec resolution
 */
#घोषणा TCP_METRIC_MAX_KERNEL (TCP_METRIC_MAX - 2)

काष्ठा tcp_metrics_block अणु
	काष्ठा tcp_metrics_block __rcu	*tcpm_next;
	possible_net_t			tcpm_net;
	काष्ठा inetpeer_addr		tcpm_saddr;
	काष्ठा inetpeer_addr		tcpm_daddr;
	अचिन्हित दीर्घ			tcpm_stamp;
	u32				tcpm_lock;
	u32				tcpm_vals[TCP_METRIC_MAX_KERNEL + 1];
	काष्ठा tcp_fastखोलो_metrics	tcpm_fastखोलो;

	काष्ठा rcu_head			rcu_head;
पूर्ण;

अटल अंतरभूत काष्ठा net *पंचांग_net(काष्ठा tcp_metrics_block *पंचांग)
अणु
	वापस पढ़ो_pnet(&पंचांग->tcpm_net);
पूर्ण

अटल bool tcp_metric_locked(काष्ठा tcp_metrics_block *पंचांग,
			      क्रमागत tcp_metric_index idx)
अणु
	वापस पंचांग->tcpm_lock & (1 << idx);
पूर्ण

अटल u32 tcp_metric_get(काष्ठा tcp_metrics_block *पंचांग,
			  क्रमागत tcp_metric_index idx)
अणु
	वापस पंचांग->tcpm_vals[idx];
पूर्ण

अटल व्योम tcp_metric_set(काष्ठा tcp_metrics_block *पंचांग,
			   क्रमागत tcp_metric_index idx,
			   u32 val)
अणु
	पंचांग->tcpm_vals[idx] = val;
पूर्ण

अटल bool addr_same(स्थिर काष्ठा inetpeer_addr *a,
		      स्थिर काष्ठा inetpeer_addr *b)
अणु
	वापस inetpeer_addr_cmp(a, b) == 0;
पूर्ण

काष्ठा tcpm_hash_bucket अणु
	काष्ठा tcp_metrics_block __rcu	*chain;
पूर्ण;

अटल काष्ठा tcpm_hash_bucket	*tcp_metrics_hash __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक		tcp_metrics_hash_log __पढ़ो_mostly;

अटल DEFINE_SPINLOCK(tcp_metrics_lock);

अटल व्योम tcpm_suck_dst(काष्ठा tcp_metrics_block *पंचांग,
			  स्थिर काष्ठा dst_entry *dst,
			  bool fastखोलो_clear)
अणु
	u32 msval;
	u32 val;

	पंचांग->tcpm_stamp = jअगरfies;

	val = 0;
	अगर (dst_metric_locked(dst, RTAX_RTT))
		val |= 1 << TCP_METRIC_RTT;
	अगर (dst_metric_locked(dst, RTAX_RTTVAR))
		val |= 1 << TCP_METRIC_RTTVAR;
	अगर (dst_metric_locked(dst, RTAX_SSTHRESH))
		val |= 1 << TCP_METRIC_SSTHRESH;
	अगर (dst_metric_locked(dst, RTAX_CWND))
		val |= 1 << TCP_METRIC_CWND;
	अगर (dst_metric_locked(dst, RTAX_REORDERING))
		val |= 1 << TCP_METRIC_REORDERING;
	पंचांग->tcpm_lock = val;

	msval = dst_metric_raw(dst, RTAX_RTT);
	पंचांग->tcpm_vals[TCP_METRIC_RTT] = msval * USEC_PER_MSEC;

	msval = dst_metric_raw(dst, RTAX_RTTVAR);
	पंचांग->tcpm_vals[TCP_METRIC_RTTVAR] = msval * USEC_PER_MSEC;
	पंचांग->tcpm_vals[TCP_METRIC_SSTHRESH] = dst_metric_raw(dst, RTAX_SSTHRESH);
	पंचांग->tcpm_vals[TCP_METRIC_CWND] = dst_metric_raw(dst, RTAX_CWND);
	पंचांग->tcpm_vals[TCP_METRIC_REORDERING] = dst_metric_raw(dst, RTAX_REORDERING);
	अगर (fastखोलो_clear) अणु
		पंचांग->tcpm_fastखोलो.mss = 0;
		पंचांग->tcpm_fastखोलो.syn_loss = 0;
		पंचांग->tcpm_fastखोलो.try_exp = 0;
		पंचांग->tcpm_fastखोलो.cookie.exp = false;
		पंचांग->tcpm_fastखोलो.cookie.len = 0;
	पूर्ण
पूर्ण

#घोषणा TCP_METRICS_TIMEOUT		(60 * 60 * HZ)

अटल व्योम tcpm_check_stamp(काष्ठा tcp_metrics_block *पंचांग, काष्ठा dst_entry *dst)
अणु
	अगर (पंचांग && unlikely(समय_after(jअगरfies, पंचांग->tcpm_stamp + TCP_METRICS_TIMEOUT)))
		tcpm_suck_dst(पंचांग, dst, false);
पूर्ण

#घोषणा TCP_METRICS_RECLAIM_DEPTH	5
#घोषणा TCP_METRICS_RECLAIM_PTR		(काष्ठा tcp_metrics_block *) 0x1UL

#घोषणा deref_locked(p)	\
	rcu_dereference_रक्षित(p, lockdep_is_held(&tcp_metrics_lock))

अटल काष्ठा tcp_metrics_block *tcpm_new(काष्ठा dst_entry *dst,
					  काष्ठा inetpeer_addr *saddr,
					  काष्ठा inetpeer_addr *daddr,
					  अचिन्हित पूर्णांक hash)
अणु
	काष्ठा tcp_metrics_block *पंचांग;
	काष्ठा net *net;
	bool reclaim = false;

	spin_lock_bh(&tcp_metrics_lock);
	net = dev_net(dst->dev);

	/* While रुकोing क्रम the spin-lock the cache might have been populated
	 * with this entry and so we have to check again.
	 */
	पंचांग = __tcp_get_metrics(saddr, daddr, net, hash);
	अगर (पंचांग == TCP_METRICS_RECLAIM_PTR) अणु
		reclaim = true;
		पंचांग = शून्य;
	पूर्ण
	अगर (पंचांग) अणु
		tcpm_check_stamp(पंचांग, dst);
		जाओ out_unlock;
	पूर्ण

	अगर (unlikely(reclaim)) अणु
		काष्ठा tcp_metrics_block *oldest;

		oldest = deref_locked(tcp_metrics_hash[hash].chain);
		क्रम (पंचांग = deref_locked(oldest->tcpm_next); पंचांग;
		     पंचांग = deref_locked(पंचांग->tcpm_next)) अणु
			अगर (समय_beक्रमe(पंचांग->tcpm_stamp, oldest->tcpm_stamp))
				oldest = पंचांग;
		पूर्ण
		पंचांग = oldest;
	पूर्ण अन्यथा अणु
		पंचांग = kदो_स्मृति(माप(*पंचांग), GFP_ATOMIC);
		अगर (!पंचांग)
			जाओ out_unlock;
	पूर्ण
	ग_लिखो_pnet(&पंचांग->tcpm_net, net);
	पंचांग->tcpm_saddr = *saddr;
	पंचांग->tcpm_daddr = *daddr;

	tcpm_suck_dst(पंचांग, dst, true);

	अगर (likely(!reclaim)) अणु
		पंचांग->tcpm_next = tcp_metrics_hash[hash].chain;
		rcu_assign_poपूर्णांकer(tcp_metrics_hash[hash].chain, पंचांग);
	पूर्ण

out_unlock:
	spin_unlock_bh(&tcp_metrics_lock);
	वापस पंचांग;
पूर्ण

अटल काष्ठा tcp_metrics_block *tcp_get_encode(काष्ठा tcp_metrics_block *पंचांग, पूर्णांक depth)
अणु
	अगर (पंचांग)
		वापस पंचांग;
	अगर (depth > TCP_METRICS_RECLAIM_DEPTH)
		वापस TCP_METRICS_RECLAIM_PTR;
	वापस शून्य;
पूर्ण

अटल काष्ठा tcp_metrics_block *__tcp_get_metrics(स्थिर काष्ठा inetpeer_addr *saddr,
						   स्थिर काष्ठा inetpeer_addr *daddr,
						   काष्ठा net *net, अचिन्हित पूर्णांक hash)
अणु
	काष्ठा tcp_metrics_block *पंचांग;
	पूर्णांक depth = 0;

	क्रम (पंचांग = rcu_dereference(tcp_metrics_hash[hash].chain); पंचांग;
	     पंचांग = rcu_dereference(पंचांग->tcpm_next)) अणु
		अगर (addr_same(&पंचांग->tcpm_saddr, saddr) &&
		    addr_same(&पंचांग->tcpm_daddr, daddr) &&
		    net_eq(पंचांग_net(पंचांग), net))
			अवरोध;
		depth++;
	पूर्ण
	वापस tcp_get_encode(पंचांग, depth);
पूर्ण

अटल काष्ठा tcp_metrics_block *__tcp_get_metrics_req(काष्ठा request_sock *req,
						       काष्ठा dst_entry *dst)
अणु
	काष्ठा tcp_metrics_block *पंचांग;
	काष्ठा inetpeer_addr saddr, daddr;
	अचिन्हित पूर्णांक hash;
	काष्ठा net *net;

	saddr.family = req->rsk_ops->family;
	daddr.family = req->rsk_ops->family;
	चयन (daddr.family) अणु
	हाल AF_INET:
		inetpeer_set_addr_v4(&saddr, inet_rsk(req)->ir_loc_addr);
		inetpeer_set_addr_v4(&daddr, inet_rsk(req)->ir_rmt_addr);
		hash = ipv4_addr_hash(inet_rsk(req)->ir_rmt_addr);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		inetpeer_set_addr_v6(&saddr, &inet_rsk(req)->ir_v6_loc_addr);
		inetpeer_set_addr_v6(&daddr, &inet_rsk(req)->ir_v6_rmt_addr);
		hash = ipv6_addr_hash(&inet_rsk(req)->ir_v6_rmt_addr);
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस शून्य;
	पूर्ण

	net = dev_net(dst->dev);
	hash ^= net_hash_mix(net);
	hash = hash_32(hash, tcp_metrics_hash_log);

	क्रम (पंचांग = rcu_dereference(tcp_metrics_hash[hash].chain); पंचांग;
	     पंचांग = rcu_dereference(पंचांग->tcpm_next)) अणु
		अगर (addr_same(&पंचांग->tcpm_saddr, &saddr) &&
		    addr_same(&पंचांग->tcpm_daddr, &daddr) &&
		    net_eq(पंचांग_net(पंचांग), net))
			अवरोध;
	पूर्ण
	tcpm_check_stamp(पंचांग, dst);
	वापस पंचांग;
पूर्ण

अटल काष्ठा tcp_metrics_block *tcp_get_metrics(काष्ठा sock *sk,
						 काष्ठा dst_entry *dst,
						 bool create)
अणु
	काष्ठा tcp_metrics_block *पंचांग;
	काष्ठा inetpeer_addr saddr, daddr;
	अचिन्हित पूर्णांक hash;
	काष्ठा net *net;

	अगर (sk->sk_family == AF_INET) अणु
		inetpeer_set_addr_v4(&saddr, inet_sk(sk)->inet_saddr);
		inetpeer_set_addr_v4(&daddr, inet_sk(sk)->inet_daddr);
		hash = ipv4_addr_hash(inet_sk(sk)->inet_daddr);
	पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा अगर (sk->sk_family == AF_INET6) अणु
		अगर (ipv6_addr_v4mapped(&sk->sk_v6_daddr)) अणु
			inetpeer_set_addr_v4(&saddr, inet_sk(sk)->inet_saddr);
			inetpeer_set_addr_v4(&daddr, inet_sk(sk)->inet_daddr);
			hash = ipv4_addr_hash(inet_sk(sk)->inet_daddr);
		पूर्ण अन्यथा अणु
			inetpeer_set_addr_v6(&saddr, &sk->sk_v6_rcv_saddr);
			inetpeer_set_addr_v6(&daddr, &sk->sk_v6_daddr);
			hash = ipv6_addr_hash(&sk->sk_v6_daddr);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अन्यथा
		वापस शून्य;

	net = dev_net(dst->dev);
	hash ^= net_hash_mix(net);
	hash = hash_32(hash, tcp_metrics_hash_log);

	पंचांग = __tcp_get_metrics(&saddr, &daddr, net, hash);
	अगर (पंचांग == TCP_METRICS_RECLAIM_PTR)
		पंचांग = शून्य;
	अगर (!पंचांग && create)
		पंचांग = tcpm_new(dst, &saddr, &daddr, hash);
	अन्यथा
		tcpm_check_stamp(पंचांग, dst);

	वापस पंचांग;
पूर्ण

/* Save metrics learned by this TCP session.  This function is called
 * only, when TCP finishes successfully i.e. when it enters TIME-WAIT
 * or goes from LAST-ACK to CLOSE.
 */
व्योम tcp_update_metrics(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा dst_entry *dst = __sk_dst_get(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा net *net = sock_net(sk);
	काष्ठा tcp_metrics_block *पंचांग;
	अचिन्हित दीर्घ rtt;
	u32 val;
	पूर्णांक m;

	sk_dst_confirm(sk);
	अगर (net->ipv4.sysctl_tcp_nometrics_save || !dst)
		वापस;

	rcu_पढ़ो_lock();
	अगर (icsk->icsk_backoff || !tp->srtt_us) अणु
		/* This session failed to estimate rtt. Why?
		 * Probably, no packets वापसed in समय.  Reset our
		 * results.
		 */
		पंचांग = tcp_get_metrics(sk, dst, false);
		अगर (पंचांग && !tcp_metric_locked(पंचांग, TCP_METRIC_RTT))
			tcp_metric_set(पंचांग, TCP_METRIC_RTT, 0);
		जाओ out_unlock;
	पूर्ण अन्यथा
		पंचांग = tcp_get_metrics(sk, dst, true);

	अगर (!पंचांग)
		जाओ out_unlock;

	rtt = tcp_metric_get(पंचांग, TCP_METRIC_RTT);
	m = rtt - tp->srtt_us;

	/* If newly calculated rtt larger than stored one, store new
	 * one. Otherwise, use EWMA. Remember, rtt overestimation is
	 * always better than underestimation.
	 */
	अगर (!tcp_metric_locked(पंचांग, TCP_METRIC_RTT)) अणु
		अगर (m <= 0)
			rtt = tp->srtt_us;
		अन्यथा
			rtt -= (m >> 3);
		tcp_metric_set(पंचांग, TCP_METRIC_RTT, rtt);
	पूर्ण

	अगर (!tcp_metric_locked(पंचांग, TCP_METRIC_RTTVAR)) अणु
		अचिन्हित दीर्घ var;

		अगर (m < 0)
			m = -m;

		/* Scale deviation to rttvar fixed poपूर्णांक */
		m >>= 1;
		अगर (m < tp->mdev_us)
			m = tp->mdev_us;

		var = tcp_metric_get(पंचांग, TCP_METRIC_RTTVAR);
		अगर (m >= var)
			var = m;
		अन्यथा
			var -= (var - m) >> 2;

		tcp_metric_set(पंचांग, TCP_METRIC_RTTVAR, var);
	पूर्ण

	अगर (tcp_in_initial_slowstart(tp)) अणु
		/* Slow start still did not finish. */
		अगर (!net->ipv4.sysctl_tcp_no_ssthresh_metrics_save &&
		    !tcp_metric_locked(पंचांग, TCP_METRIC_SSTHRESH)) अणु
			val = tcp_metric_get(पंचांग, TCP_METRIC_SSTHRESH);
			अगर (val && (tp->snd_cwnd >> 1) > val)
				tcp_metric_set(पंचांग, TCP_METRIC_SSTHRESH,
					       tp->snd_cwnd >> 1);
		पूर्ण
		अगर (!tcp_metric_locked(पंचांग, TCP_METRIC_CWND)) अणु
			val = tcp_metric_get(पंचांग, TCP_METRIC_CWND);
			अगर (tp->snd_cwnd > val)
				tcp_metric_set(पंचांग, TCP_METRIC_CWND,
					       tp->snd_cwnd);
		पूर्ण
	पूर्ण अन्यथा अगर (!tcp_in_slow_start(tp) &&
		   icsk->icsk_ca_state == TCP_CA_Open) अणु
		/* Cong. aव्योमance phase, cwnd is reliable. */
		अगर (!net->ipv4.sysctl_tcp_no_ssthresh_metrics_save &&
		    !tcp_metric_locked(पंचांग, TCP_METRIC_SSTHRESH))
			tcp_metric_set(पंचांग, TCP_METRIC_SSTHRESH,
				       max(tp->snd_cwnd >> 1, tp->snd_ssthresh));
		अगर (!tcp_metric_locked(पंचांग, TCP_METRIC_CWND)) अणु
			val = tcp_metric_get(पंचांग, TCP_METRIC_CWND);
			tcp_metric_set(पंचांग, TCP_METRIC_CWND, (val + tp->snd_cwnd) >> 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Else slow start did not finish, cwnd is non-sense,
		 * ssthresh may be also invalid.
		 */
		अगर (!tcp_metric_locked(पंचांग, TCP_METRIC_CWND)) अणु
			val = tcp_metric_get(पंचांग, TCP_METRIC_CWND);
			tcp_metric_set(पंचांग, TCP_METRIC_CWND,
				       (val + tp->snd_ssthresh) >> 1);
		पूर्ण
		अगर (!net->ipv4.sysctl_tcp_no_ssthresh_metrics_save &&
		    !tcp_metric_locked(पंचांग, TCP_METRIC_SSTHRESH)) अणु
			val = tcp_metric_get(पंचांग, TCP_METRIC_SSTHRESH);
			अगर (val && tp->snd_ssthresh > val)
				tcp_metric_set(पंचांग, TCP_METRIC_SSTHRESH,
					       tp->snd_ssthresh);
		पूर्ण
		अगर (!tcp_metric_locked(पंचांग, TCP_METRIC_REORDERING)) अणु
			val = tcp_metric_get(पंचांग, TCP_METRIC_REORDERING);
			अगर (val < tp->reordering &&
			    tp->reordering != net->ipv4.sysctl_tcp_reordering)
				tcp_metric_set(पंचांग, TCP_METRIC_REORDERING,
					       tp->reordering);
		पूर्ण
	पूर्ण
	पंचांग->tcpm_stamp = jअगरfies;
out_unlock:
	rcu_पढ़ो_unlock();
पूर्ण

/* Initialize metrics on socket. */

व्योम tcp_init_metrics(काष्ठा sock *sk)
अणु
	काष्ठा dst_entry *dst = __sk_dst_get(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा net *net = sock_net(sk);
	काष्ठा tcp_metrics_block *पंचांग;
	u32 val, crtt = 0; /* cached RTT scaled by 8 */

	sk_dst_confirm(sk);
	अगर (!dst)
		जाओ reset;

	rcu_पढ़ो_lock();
	पंचांग = tcp_get_metrics(sk, dst, true);
	अगर (!पंचांग) अणु
		rcu_पढ़ो_unlock();
		जाओ reset;
	पूर्ण

	अगर (tcp_metric_locked(पंचांग, TCP_METRIC_CWND))
		tp->snd_cwnd_clamp = tcp_metric_get(पंचांग, TCP_METRIC_CWND);

	val = net->ipv4.sysctl_tcp_no_ssthresh_metrics_save ?
	      0 : tcp_metric_get(पंचांग, TCP_METRIC_SSTHRESH);
	अगर (val) अणु
		tp->snd_ssthresh = val;
		अगर (tp->snd_ssthresh > tp->snd_cwnd_clamp)
			tp->snd_ssthresh = tp->snd_cwnd_clamp;
	पूर्ण अन्यथा अणु
		/* ssthresh may have been reduced unnecessarily during.
		 * 3WHS. Restore it back to its initial शेष.
		 */
		tp->snd_ssthresh = TCP_INFINITE_SSTHRESH;
	पूर्ण
	val = tcp_metric_get(पंचांग, TCP_METRIC_REORDERING);
	अगर (val && tp->reordering != val)
		tp->reordering = val;

	crtt = tcp_metric_get(पंचांग, TCP_METRIC_RTT);
	rcu_पढ़ो_unlock();
reset:
	/* The initial RTT measurement from the SYN/SYN-ACK is not ideal
	 * to seed the RTO क्रम later data packets because SYN packets are
	 * small. Use the per-dst cached values to seed the RTO but keep
	 * the RTT estimator variables पूर्णांकact (e.g., srtt, mdev, rttvar).
	 * Later the RTO will be updated immediately upon obtaining the first
	 * data RTT sample (tcp_rtt_estimator()). Hence the cached RTT only
	 * influences the first RTO but not later RTT estimation.
	 *
	 * But अगर RTT is not available from the SYN (due to retransmits or
	 * syn cookies) or the cache, क्रमce a conservative 3secs समयout.
	 *
	 * A bit of theory. RTT is समय passed after "normal" sized packet
	 * is sent until it is ACKed. In normal circumstances sending small
	 * packets क्रमce peer to delay ACKs and calculation is correct too.
	 * The algorithm is adaptive and, provided we follow specs, it
	 * NEVER underestimate RTT. BUT! If peer tries to make some clever
	 * tricks sort of "quick acks" क्रम समय दीर्घ enough to decrease RTT
	 * to low value, and then abruptly stops to करो it and starts to delay
	 * ACKs, रुको क्रम troubles.
	 */
	अगर (crtt > tp->srtt_us) अणु
		/* Set RTO like tcp_rtt_estimator(), but from cached RTT. */
		crtt /= 8 * USEC_PER_SEC / HZ;
		inet_csk(sk)->icsk_rto = crtt + max(2 * crtt, tcp_rto_min(sk));
	पूर्ण अन्यथा अगर (tp->srtt_us == 0) अणु
		/* RFC6298: 5.7 We've failed to get a valid RTT sample from
		 * 3WHS. This is most likely due to retransmission,
		 * including spurious one. Reset the RTO back to 3secs
		 * from the more aggressive 1sec to aव्योम more spurious
		 * retransmission.
		 */
		tp->rttvar_us = jअगरfies_to_usecs(TCP_TIMEOUT_FALLBACK);
		tp->mdev_us = tp->mdev_max_us = tp->rttvar_us;

		inet_csk(sk)->icsk_rto = TCP_TIMEOUT_FALLBACK;
	पूर्ण
पूर्ण

bool tcp_peer_is_proven(काष्ठा request_sock *req, काष्ठा dst_entry *dst)
अणु
	काष्ठा tcp_metrics_block *पंचांग;
	bool ret;

	अगर (!dst)
		वापस false;

	rcu_पढ़ो_lock();
	पंचांग = __tcp_get_metrics_req(req, dst);
	अगर (पंचांग && tcp_metric_get(पंचांग, TCP_METRIC_RTT))
		ret = true;
	अन्यथा
		ret = false;
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल DEFINE_SEQLOCK(fastखोलो_seqlock);

व्योम tcp_fastखोलो_cache_get(काष्ठा sock *sk, u16 *mss,
			    काष्ठा tcp_fastखोलो_cookie *cookie)
अणु
	काष्ठा tcp_metrics_block *पंचांग;

	rcu_पढ़ो_lock();
	पंचांग = tcp_get_metrics(sk, __sk_dst_get(sk), false);
	अगर (पंचांग) अणु
		काष्ठा tcp_fastखोलो_metrics *tfom = &पंचांग->tcpm_fastखोलो;
		अचिन्हित पूर्णांक seq;

		करो अणु
			seq = पढ़ो_seqbegin(&fastखोलो_seqlock);
			अगर (tfom->mss)
				*mss = tfom->mss;
			*cookie = tfom->cookie;
			अगर (cookie->len <= 0 && tfom->try_exp == 1)
				cookie->exp = true;
		पूर्ण जबतक (पढ़ो_seqretry(&fastखोलो_seqlock, seq));
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

व्योम tcp_fastखोलो_cache_set(काष्ठा sock *sk, u16 mss,
			    काष्ठा tcp_fastखोलो_cookie *cookie, bool syn_lost,
			    u16 try_exp)
अणु
	काष्ठा dst_entry *dst = __sk_dst_get(sk);
	काष्ठा tcp_metrics_block *पंचांग;

	अगर (!dst)
		वापस;
	rcu_पढ़ो_lock();
	पंचांग = tcp_get_metrics(sk, dst, true);
	अगर (पंचांग) अणु
		काष्ठा tcp_fastखोलो_metrics *tfom = &पंचांग->tcpm_fastखोलो;

		ग_लिखो_seqlock_bh(&fastखोलो_seqlock);
		अगर (mss)
			tfom->mss = mss;
		अगर (cookie && cookie->len > 0)
			tfom->cookie = *cookie;
		अन्यथा अगर (try_exp > tfom->try_exp &&
			 tfom->cookie.len <= 0 && !tfom->cookie.exp)
			tfom->try_exp = try_exp;
		अगर (syn_lost) अणु
			++tfom->syn_loss;
			tfom->last_syn_loss = jअगरfies;
		पूर्ण अन्यथा
			tfom->syn_loss = 0;
		ग_लिखो_sequnlock_bh(&fastखोलो_seqlock);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल काष्ठा genl_family tcp_metrics_nl_family;

अटल स्थिर काष्ठा nla_policy tcp_metrics_nl_policy[TCP_METRICS_ATTR_MAX + 1] = अणु
	[TCP_METRICS_ATTR_ADDR_IPV4]	= अणु .type = NLA_U32, पूर्ण,
	[TCP_METRICS_ATTR_ADDR_IPV6]	= अणु .type = NLA_BINARY,
					    .len = माप(काष्ठा in6_addr), पूर्ण,
	/* Following attributes are not received क्रम GET/DEL,
	 * we keep them क्रम reference
	 */
#अगर 0
	[TCP_METRICS_ATTR_AGE]		= अणु .type = NLA_MSECS, पूर्ण,
	[TCP_METRICS_ATTR_TW_TSVAL]	= अणु .type = NLA_U32, पूर्ण,
	[TCP_METRICS_ATTR_TW_TS_STAMP]	= अणु .type = NLA_S32, पूर्ण,
	[TCP_METRICS_ATTR_VALS]		= अणु .type = NLA_NESTED, पूर्ण,
	[TCP_METRICS_ATTR_FOPEN_MSS]	= अणु .type = NLA_U16, पूर्ण,
	[TCP_METRICS_ATTR_FOPEN_SYN_DROPS]	= अणु .type = NLA_U16, पूर्ण,
	[TCP_METRICS_ATTR_FOPEN_SYN_DROP_TS]	= अणु .type = NLA_MSECS, पूर्ण,
	[TCP_METRICS_ATTR_FOPEN_COOKIE]	= अणु .type = NLA_BINARY,
					    .len = TCP_FASTOPEN_COOKIE_MAX, पूर्ण,
#पूर्ण_अगर
पूर्ण;

/* Add attributes, caller cancels its header on failure */
अटल पूर्णांक tcp_metrics_fill_info(काष्ठा sk_buff *msg,
				 काष्ठा tcp_metrics_block *पंचांग)
अणु
	काष्ठा nlattr *nest;
	पूर्णांक i;

	चयन (पंचांग->tcpm_daddr.family) अणु
	हाल AF_INET:
		अगर (nla_put_in_addr(msg, TCP_METRICS_ATTR_ADDR_IPV4,
				    inetpeer_get_addr_v4(&पंचांग->tcpm_daddr)) < 0)
			जाओ nla_put_failure;
		अगर (nla_put_in_addr(msg, TCP_METRICS_ATTR_SADDR_IPV4,
				    inetpeer_get_addr_v4(&पंचांग->tcpm_saddr)) < 0)
			जाओ nla_put_failure;
		अवरोध;
	हाल AF_INET6:
		अगर (nla_put_in6_addr(msg, TCP_METRICS_ATTR_ADDR_IPV6,
				     inetpeer_get_addr_v6(&पंचांग->tcpm_daddr)) < 0)
			जाओ nla_put_failure;
		अगर (nla_put_in6_addr(msg, TCP_METRICS_ATTR_SADDR_IPV6,
				     inetpeer_get_addr_v6(&पंचांग->tcpm_saddr)) < 0)
			जाओ nla_put_failure;
		अवरोध;
	शेष:
		वापस -EAFNOSUPPORT;
	पूर्ण

	अगर (nla_put_msecs(msg, TCP_METRICS_ATTR_AGE,
			  jअगरfies - पंचांग->tcpm_stamp,
			  TCP_METRICS_ATTR_PAD) < 0)
		जाओ nla_put_failure;

	अणु
		पूर्णांक n = 0;

		nest = nla_nest_start_noflag(msg, TCP_METRICS_ATTR_VALS);
		अगर (!nest)
			जाओ nla_put_failure;
		क्रम (i = 0; i < TCP_METRIC_MAX_KERNEL + 1; i++) अणु
			u32 val = पंचांग->tcpm_vals[i];

			अगर (!val)
				जारी;
			अगर (i == TCP_METRIC_RTT) अणु
				अगर (nla_put_u32(msg, TCP_METRIC_RTT_US + 1,
						val) < 0)
					जाओ nla_put_failure;
				n++;
				val = max(val / 1000, 1U);
			पूर्ण
			अगर (i == TCP_METRIC_RTTVAR) अणु
				अगर (nla_put_u32(msg, TCP_METRIC_RTTVAR_US + 1,
						val) < 0)
					जाओ nla_put_failure;
				n++;
				val = max(val / 1000, 1U);
			पूर्ण
			अगर (nla_put_u32(msg, i + 1, val) < 0)
				जाओ nla_put_failure;
			n++;
		पूर्ण
		अगर (n)
			nla_nest_end(msg, nest);
		अन्यथा
			nla_nest_cancel(msg, nest);
	पूर्ण

	अणु
		काष्ठा tcp_fastखोलो_metrics tfom_copy[1], *tfom;
		अचिन्हित पूर्णांक seq;

		करो अणु
			seq = पढ़ो_seqbegin(&fastखोलो_seqlock);
			tfom_copy[0] = पंचांग->tcpm_fastखोलो;
		पूर्ण जबतक (पढ़ो_seqretry(&fastखोलो_seqlock, seq));

		tfom = tfom_copy;
		अगर (tfom->mss &&
		    nla_put_u16(msg, TCP_METRICS_ATTR_FOPEN_MSS,
				tfom->mss) < 0)
			जाओ nla_put_failure;
		अगर (tfom->syn_loss &&
		    (nla_put_u16(msg, TCP_METRICS_ATTR_FOPEN_SYN_DROPS,
				tfom->syn_loss) < 0 ||
		     nla_put_msecs(msg, TCP_METRICS_ATTR_FOPEN_SYN_DROP_TS,
				jअगरfies - tfom->last_syn_loss,
				TCP_METRICS_ATTR_PAD) < 0))
			जाओ nla_put_failure;
		अगर (tfom->cookie.len > 0 &&
		    nla_put(msg, TCP_METRICS_ATTR_FOPEN_COOKIE,
			    tfom->cookie.len, tfom->cookie.val) < 0)
			जाओ nla_put_failure;
	पूर्ण

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक tcp_metrics_dump_info(काष्ठा sk_buff *skb,
				 काष्ठा netlink_callback *cb,
				 काष्ठा tcp_metrics_block *पंचांग)
अणु
	व्योम *hdr;

	hdr = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &tcp_metrics_nl_family, NLM_F_MULTI,
			  TCP_METRICS_CMD_GET);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (tcp_metrics_fill_info(skb, पंचांग) < 0)
		जाओ nla_put_failure;

	genlmsg_end(skb, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(skb, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक tcp_metrics_nl_dump(काष्ठा sk_buff *skb,
			       काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	अचिन्हित पूर्णांक max_rows = 1U << tcp_metrics_hash_log;
	अचिन्हित पूर्णांक row, s_row = cb->args[0];
	पूर्णांक s_col = cb->args[1], col = s_col;

	क्रम (row = s_row; row < max_rows; row++, s_col = 0) अणु
		काष्ठा tcp_metrics_block *पंचांग;
		काष्ठा tcpm_hash_bucket *hb = tcp_metrics_hash + row;

		rcu_पढ़ो_lock();
		क्रम (col = 0, पंचांग = rcu_dereference(hb->chain); पंचांग;
		     पंचांग = rcu_dereference(पंचांग->tcpm_next), col++) अणु
			अगर (!net_eq(पंचांग_net(पंचांग), net))
				जारी;
			अगर (col < s_col)
				जारी;
			अगर (tcp_metrics_dump_info(skb, cb, पंचांग) < 0) अणु
				rcu_पढ़ो_unlock();
				जाओ करोne;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

करोne:
	cb->args[0] = row;
	cb->args[1] = col;
	वापस skb->len;
पूर्ण

अटल पूर्णांक __parse_nl_addr(काष्ठा genl_info *info, काष्ठा inetpeer_addr *addr,
			   अचिन्हित पूर्णांक *hash, पूर्णांक optional, पूर्णांक v4, पूर्णांक v6)
अणु
	काष्ठा nlattr *a;

	a = info->attrs[v4];
	अगर (a) अणु
		inetpeer_set_addr_v4(addr, nla_get_in_addr(a));
		अगर (hash)
			*hash = ipv4_addr_hash(inetpeer_get_addr_v4(addr));
		वापस 0;
	पूर्ण
	a = info->attrs[v6];
	अगर (a) अणु
		काष्ठा in6_addr in6;

		अगर (nla_len(a) != माप(काष्ठा in6_addr))
			वापस -EINVAL;
		in6 = nla_get_in6_addr(a);
		inetpeer_set_addr_v6(addr, &in6);
		अगर (hash)
			*hash = ipv6_addr_hash(inetpeer_get_addr_v6(addr));
		वापस 0;
	पूर्ण
	वापस optional ? 1 : -EAFNOSUPPORT;
पूर्ण

अटल पूर्णांक parse_nl_addr(काष्ठा genl_info *info, काष्ठा inetpeer_addr *addr,
			 अचिन्हित पूर्णांक *hash, पूर्णांक optional)
अणु
	वापस __parse_nl_addr(info, addr, hash, optional,
			       TCP_METRICS_ATTR_ADDR_IPV4,
			       TCP_METRICS_ATTR_ADDR_IPV6);
पूर्ण

अटल पूर्णांक parse_nl_saddr(काष्ठा genl_info *info, काष्ठा inetpeer_addr *addr)
अणु
	वापस __parse_nl_addr(info, addr, शून्य, 0,
			       TCP_METRICS_ATTR_SADDR_IPV4,
			       TCP_METRICS_ATTR_SADDR_IPV6);
पूर्ण

अटल पूर्णांक tcp_metrics_nl_cmd_get(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा tcp_metrics_block *पंचांग;
	काष्ठा inetpeer_addr saddr, daddr;
	अचिन्हित पूर्णांक hash;
	काष्ठा sk_buff *msg;
	काष्ठा net *net = genl_info_net(info);
	व्योम *reply;
	पूर्णांक ret;
	bool src = true;

	ret = parse_nl_addr(info, &daddr, &hash, 0);
	अगर (ret < 0)
		वापस ret;

	ret = parse_nl_saddr(info, &saddr);
	अगर (ret < 0)
		src = false;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	reply = genlmsg_put_reply(msg, info, &tcp_metrics_nl_family, 0,
				  info->genlhdr->cmd);
	अगर (!reply)
		जाओ nla_put_failure;

	hash ^= net_hash_mix(net);
	hash = hash_32(hash, tcp_metrics_hash_log);
	ret = -ESRCH;
	rcu_पढ़ो_lock();
	क्रम (पंचांग = rcu_dereference(tcp_metrics_hash[hash].chain); पंचांग;
	     पंचांग = rcu_dereference(पंचांग->tcpm_next)) अणु
		अगर (addr_same(&पंचांग->tcpm_daddr, &daddr) &&
		    (!src || addr_same(&पंचांग->tcpm_saddr, &saddr)) &&
		    net_eq(पंचांग_net(पंचांग), net)) अणु
			ret = tcp_metrics_fill_info(msg, पंचांग);
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (ret < 0)
		जाओ out_मुक्त;

	genlmsg_end(msg, reply);
	वापस genlmsg_reply(msg, info);

nla_put_failure:
	ret = -EMSGSIZE;

out_मुक्त:
	nlmsg_मुक्त(msg);
	वापस ret;
पूर्ण

अटल व्योम tcp_metrics_flush_all(काष्ठा net *net)
अणु
	अचिन्हित पूर्णांक max_rows = 1U << tcp_metrics_hash_log;
	काष्ठा tcpm_hash_bucket *hb = tcp_metrics_hash;
	काष्ठा tcp_metrics_block *पंचांग;
	अचिन्हित पूर्णांक row;

	क्रम (row = 0; row < max_rows; row++, hb++) अणु
		काष्ठा tcp_metrics_block __rcu **pp;
		bool match;

		spin_lock_bh(&tcp_metrics_lock);
		pp = &hb->chain;
		क्रम (पंचांग = deref_locked(*pp); पंचांग; पंचांग = deref_locked(*pp)) अणु
			match = net ? net_eq(पंचांग_net(पंचांग), net) :
				!refcount_पढ़ो(&पंचांग_net(पंचांग)->ns.count);
			अगर (match) अणु
				*pp = पंचांग->tcpm_next;
				kमुक्त_rcu(पंचांग, rcu_head);
			पूर्ण अन्यथा अणु
				pp = &पंचांग->tcpm_next;
			पूर्ण
		पूर्ण
		spin_unlock_bh(&tcp_metrics_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक tcp_metrics_nl_cmd_del(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा tcpm_hash_bucket *hb;
	काष्ठा tcp_metrics_block *पंचांग;
	काष्ठा tcp_metrics_block __rcu **pp;
	काष्ठा inetpeer_addr saddr, daddr;
	अचिन्हित पूर्णांक hash;
	काष्ठा net *net = genl_info_net(info);
	पूर्णांक ret;
	bool src = true, found = false;

	ret = parse_nl_addr(info, &daddr, &hash, 1);
	अगर (ret < 0)
		वापस ret;
	अगर (ret > 0) अणु
		tcp_metrics_flush_all(net);
		वापस 0;
	पूर्ण
	ret = parse_nl_saddr(info, &saddr);
	अगर (ret < 0)
		src = false;

	hash ^= net_hash_mix(net);
	hash = hash_32(hash, tcp_metrics_hash_log);
	hb = tcp_metrics_hash + hash;
	pp = &hb->chain;
	spin_lock_bh(&tcp_metrics_lock);
	क्रम (पंचांग = deref_locked(*pp); पंचांग; पंचांग = deref_locked(*pp)) अणु
		अगर (addr_same(&पंचांग->tcpm_daddr, &daddr) &&
		    (!src || addr_same(&पंचांग->tcpm_saddr, &saddr)) &&
		    net_eq(पंचांग_net(पंचांग), net)) अणु
			*pp = पंचांग->tcpm_next;
			kमुक्त_rcu(पंचांग, rcu_head);
			found = true;
		पूर्ण अन्यथा अणु
			pp = &पंचांग->tcpm_next;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&tcp_metrics_lock);
	अगर (!found)
		वापस -ESRCH;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा genl_small_ops tcp_metrics_nl_ops[] = अणु
	अणु
		.cmd = TCP_METRICS_CMD_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = tcp_metrics_nl_cmd_get,
		.dumpit = tcp_metrics_nl_dump,
	पूर्ण,
	अणु
		.cmd = TCP_METRICS_CMD_DEL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = tcp_metrics_nl_cmd_del,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family tcp_metrics_nl_family __ro_after_init = अणु
	.hdrsize	= 0,
	.name		= TCP_METRICS_GENL_NAME,
	.version	= TCP_METRICS_GENL_VERSION,
	.maxattr	= TCP_METRICS_ATTR_MAX,
	.policy = tcp_metrics_nl_policy,
	.netnsok	= true,
	.module		= THIS_MODULE,
	.small_ops	= tcp_metrics_nl_ops,
	.n_small_ops	= ARRAY_SIZE(tcp_metrics_nl_ops),
पूर्ण;

अटल अचिन्हित पूर्णांक tcpmhash_entries;
अटल पूर्णांक __init set_tcpmhash_entries(अक्षर *str)
अणु
	sमाप_प्रकार ret;

	अगर (!str)
		वापस 0;

	ret = kstrtouपूर्णांक(str, 0, &tcpmhash_entries);
	अगर (ret)
		वापस 0;

	वापस 1;
पूर्ण
__setup("tcpmhash_entries=", set_tcpmhash_entries);

अटल पूर्णांक __net_init tcp_net_metrics_init(काष्ठा net *net)
अणु
	माप_प्रकार size;
	अचिन्हित पूर्णांक slots;

	अगर (!net_eq(net, &init_net))
		वापस 0;

	slots = tcpmhash_entries;
	अगर (!slots) अणु
		अगर (totalram_pages() >= 128 * 1024)
			slots = 16 * 1024;
		अन्यथा
			slots = 8 * 1024;
	पूर्ण

	tcp_metrics_hash_log = order_base_2(slots);
	size = माप(काष्ठा tcpm_hash_bucket) << tcp_metrics_hash_log;

	tcp_metrics_hash = kvzalloc(size, GFP_KERNEL);
	अगर (!tcp_metrics_hash)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम __net_निकास tcp_net_metrics_निकास_batch(काष्ठा list_head *net_निकास_list)
अणु
	tcp_metrics_flush_all(शून्य);
पूर्ण

अटल __net_initdata काष्ठा pernet_operations tcp_net_metrics_ops = अणु
	.init		=	tcp_net_metrics_init,
	.निकास_batch	=	tcp_net_metrics_निकास_batch,
पूर्ण;

व्योम __init tcp_metrics_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_pernet_subsys(&tcp_net_metrics_ops);
	अगर (ret < 0)
		panic("Could not allocate the tcp_metrics hash table\n");

	ret = genl_रेजिस्टर_family(&tcp_metrics_nl_family);
	अगर (ret < 0)
		panic("Could not register tcp_metrics generic netlink\n");
पूर्ण
