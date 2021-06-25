<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/crypto.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/tcp.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/rculist.h>
#समावेश <net/inetpeer.h>
#समावेश <net/tcp.h>

व्योम tcp_fastखोलो_init_key_once(काष्ठा net *net)
अणु
	u8 key[TCP_FASTOPEN_KEY_LENGTH];
	काष्ठा tcp_fastखोलो_context *ctxt;

	rcu_पढ़ो_lock();
	ctxt = rcu_dereference(net->ipv4.tcp_fastखोलो_ctx);
	अगर (ctxt) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	rcu_पढ़ो_unlock();

	/* tcp_fastखोलो_reset_cipher publishes the new context
	 * atomically, so we allow this race happening here.
	 *
	 * All call sites of tcp_fastखोलो_cookie_gen also check
	 * क्रम a valid cookie, so this is an acceptable risk.
	 */
	get_अक्रमom_bytes(key, माप(key));
	tcp_fastखोलो_reset_cipher(net, शून्य, key, शून्य);
पूर्ण

अटल व्योम tcp_fastखोलो_ctx_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा tcp_fastखोलो_context *ctx =
	    container_of(head, काष्ठा tcp_fastखोलो_context, rcu);

	kमुक्त_sensitive(ctx);
पूर्ण

व्योम tcp_fastखोलो_destroy_cipher(काष्ठा sock *sk)
अणु
	काष्ठा tcp_fastखोलो_context *ctx;

	ctx = rcu_dereference_रक्षित(
			inet_csk(sk)->icsk_accept_queue.fastखोलोq.ctx, 1);
	अगर (ctx)
		call_rcu(&ctx->rcu, tcp_fastखोलो_ctx_मुक्त);
पूर्ण

व्योम tcp_fastखोलो_ctx_destroy(काष्ठा net *net)
अणु
	काष्ठा tcp_fastखोलो_context *ctxt;

	spin_lock(&net->ipv4.tcp_fastखोलो_ctx_lock);

	ctxt = rcu_dereference_रक्षित(net->ipv4.tcp_fastखोलो_ctx,
				lockdep_is_held(&net->ipv4.tcp_fastखोलो_ctx_lock));
	rcu_assign_poपूर्णांकer(net->ipv4.tcp_fastखोलो_ctx, शून्य);
	spin_unlock(&net->ipv4.tcp_fastखोलो_ctx_lock);

	अगर (ctxt)
		call_rcu(&ctxt->rcu, tcp_fastखोलो_ctx_मुक्त);
पूर्ण

पूर्णांक tcp_fastखोलो_reset_cipher(काष्ठा net *net, काष्ठा sock *sk,
			      व्योम *primary_key, व्योम *backup_key)
अणु
	काष्ठा tcp_fastखोलो_context *ctx, *octx;
	काष्ठा fastखोलो_queue *q;
	पूर्णांक err = 0;

	ctx = kदो_स्मृति(माप(*ctx), GFP_KERNEL);
	अगर (!ctx) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	ctx->key[0].key[0] = get_unaligned_le64(primary_key);
	ctx->key[0].key[1] = get_unaligned_le64(primary_key + 8);
	अगर (backup_key) अणु
		ctx->key[1].key[0] = get_unaligned_le64(backup_key);
		ctx->key[1].key[1] = get_unaligned_le64(backup_key + 8);
		ctx->num = 2;
	पूर्ण अन्यथा अणु
		ctx->num = 1;
	पूर्ण

	spin_lock(&net->ipv4.tcp_fastखोलो_ctx_lock);
	अगर (sk) अणु
		q = &inet_csk(sk)->icsk_accept_queue.fastखोलोq;
		octx = rcu_dereference_रक्षित(q->ctx,
			lockdep_is_held(&net->ipv4.tcp_fastखोलो_ctx_lock));
		rcu_assign_poपूर्णांकer(q->ctx, ctx);
	पूर्ण अन्यथा अणु
		octx = rcu_dereference_रक्षित(net->ipv4.tcp_fastखोलो_ctx,
			lockdep_is_held(&net->ipv4.tcp_fastखोलो_ctx_lock));
		rcu_assign_poपूर्णांकer(net->ipv4.tcp_fastखोलो_ctx, ctx);
	पूर्ण
	spin_unlock(&net->ipv4.tcp_fastखोलो_ctx_lock);

	अगर (octx)
		call_rcu(&octx->rcu, tcp_fastखोलो_ctx_मुक्त);
out:
	वापस err;
पूर्ण

पूर्णांक tcp_fastखोलो_get_cipher(काष्ठा net *net, काष्ठा inet_connection_sock *icsk,
			    u64 *key)
अणु
	काष्ठा tcp_fastखोलो_context *ctx;
	पूर्णांक n_keys = 0, i;

	rcu_पढ़ो_lock();
	अगर (icsk)
		ctx = rcu_dereference(icsk->icsk_accept_queue.fastखोलोq.ctx);
	अन्यथा
		ctx = rcu_dereference(net->ipv4.tcp_fastखोलो_ctx);
	अगर (ctx) अणु
		n_keys = tcp_fastखोलो_context_len(ctx);
		क्रम (i = 0; i < n_keys; i++) अणु
			put_unaligned_le64(ctx->key[i].key[0], key + (i * 2));
			put_unaligned_le64(ctx->key[i].key[1], key + (i * 2) + 1);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस n_keys;
पूर्ण

अटल bool __tcp_fastखोलो_cookie_gen_cipher(काष्ठा request_sock *req,
					     काष्ठा sk_buff *syn,
					     स्थिर siphash_key_t *key,
					     काष्ठा tcp_fastखोलो_cookie *foc)
अणु
	BUILD_BUG_ON(TCP_FASTOPEN_COOKIE_SIZE != माप(u64));

	अगर (req->rsk_ops->family == AF_INET) अणु
		स्थिर काष्ठा iphdr *iph = ip_hdr(syn);

		foc->val[0] = cpu_to_le64(siphash(&iph->saddr,
					  माप(iph->saddr) +
					  माप(iph->daddr),
					  key));
		foc->len = TCP_FASTOPEN_COOKIE_SIZE;
		वापस true;
	पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (req->rsk_ops->family == AF_INET6) अणु
		स्थिर काष्ठा ipv6hdr *ip6h = ipv6_hdr(syn);

		foc->val[0] = cpu_to_le64(siphash(&ip6h->saddr,
					  माप(ip6h->saddr) +
					  माप(ip6h->daddr),
					  key));
		foc->len = TCP_FASTOPEN_COOKIE_SIZE;
		वापस true;
	पूर्ण
#पूर्ण_अगर
	वापस false;
पूर्ण

/* Generate the fastखोलो cookie by applying SipHash to both the source and
 * destination addresses.
 */
अटल व्योम tcp_fastखोलो_cookie_gen(काष्ठा sock *sk,
				    काष्ठा request_sock *req,
				    काष्ठा sk_buff *syn,
				    काष्ठा tcp_fastखोलो_cookie *foc)
अणु
	काष्ठा tcp_fastखोलो_context *ctx;

	rcu_पढ़ो_lock();
	ctx = tcp_fastखोलो_get_ctx(sk);
	अगर (ctx)
		__tcp_fastखोलो_cookie_gen_cipher(req, syn, &ctx->key[0], foc);
	rcu_पढ़ो_unlock();
पूर्ण

/* If an incoming SYN or SYNACK frame contains a payload and/or FIN,
 * queue this additional data / FIN.
 */
व्योम tcp_fastखोलो_add_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (TCP_SKB_CB(skb)->end_seq == tp->rcv_nxt)
		वापस;

	skb = skb_clone(skb, GFP_ATOMIC);
	अगर (!skb)
		वापस;

	skb_dst_drop(skb);
	/* segs_in has been initialized to 1 in tcp_create_खोलोreq_child().
	 * Hence, reset segs_in to 0 beक्रमe calling tcp_segs_in()
	 * to aव्योम द्विगुन counting.  Also, tcp_segs_in() expects
	 * skb->len to include the tcp_hdrlen.  Hence, it should
	 * be called beक्रमe __skb_pull().
	 */
	tp->segs_in = 0;
	tcp_segs_in(tp, skb);
	__skb_pull(skb, tcp_hdrlen(skb));
	sk_क्रमced_mem_schedule(sk, skb->truesize);
	skb_set_owner_r(skb, sk);

	TCP_SKB_CB(skb)->seq++;
	TCP_SKB_CB(skb)->tcp_flags &= ~TCPHDR_SYN;

	tp->rcv_nxt = TCP_SKB_CB(skb)->end_seq;
	__skb_queue_tail(&sk->sk_receive_queue, skb);
	tp->syn_data_acked = 1;

	/* u64_stats_update_begin(&tp->syncp) not needed here,
	 * as we certainly are not changing upper 32bit value (0)
	 */
	tp->bytes_received = skb->len;

	अगर (TCP_SKB_CB(skb)->tcp_flags & TCPHDR_FIN)
		tcp_fin(sk);
पूर्ण

/* वापसs 0 - no key match, 1 क्रम primary, 2 क्रम backup */
अटल पूर्णांक tcp_fastखोलो_cookie_gen_check(काष्ठा sock *sk,
					 काष्ठा request_sock *req,
					 काष्ठा sk_buff *syn,
					 काष्ठा tcp_fastखोलो_cookie *orig,
					 काष्ठा tcp_fastखोलो_cookie *valid_foc)
अणु
	काष्ठा tcp_fastखोलो_cookie search_foc = अणु .len = -1 पूर्ण;
	काष्ठा tcp_fastखोलो_cookie *foc = valid_foc;
	काष्ठा tcp_fastखोलो_context *ctx;
	पूर्णांक i, ret = 0;

	rcu_पढ़ो_lock();
	ctx = tcp_fastखोलो_get_ctx(sk);
	अगर (!ctx)
		जाओ out;
	क्रम (i = 0; i < tcp_fastखोलो_context_len(ctx); i++) अणु
		__tcp_fastखोलो_cookie_gen_cipher(req, syn, &ctx->key[i], foc);
		अगर (tcp_fastखोलो_cookie_match(foc, orig)) अणु
			ret = i + 1;
			जाओ out;
		पूर्ण
		foc = &search_foc;
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल काष्ठा sock *tcp_fastखोलो_create_child(काष्ठा sock *sk,
					      काष्ठा sk_buff *skb,
					      काष्ठा request_sock *req)
अणु
	काष्ठा tcp_sock *tp;
	काष्ठा request_sock_queue *queue = &inet_csk(sk)->icsk_accept_queue;
	काष्ठा sock *child;
	bool own_req;

	child = inet_csk(sk)->icsk_af_ops->syn_recv_sock(sk, skb, req, शून्य,
							 शून्य, &own_req);
	अगर (!child)
		वापस शून्य;

	spin_lock(&queue->fastखोलोq.lock);
	queue->fastखोलोq.qlen++;
	spin_unlock(&queue->fastखोलोq.lock);

	/* Initialize the child socket. Have to fix some values to take
	 * पूर्णांकo account the child is a Fast Open socket and is created
	 * only out of the bits carried in the SYN packet.
	 */
	tp = tcp_sk(child);

	rcu_assign_poपूर्णांकer(tp->fastखोलो_rsk, req);
	tcp_rsk(req)->tfo_listener = true;

	/* RFC1323: The winकरोw in SYN & SYN/ACK segments is never
	 * scaled. So correct it appropriately.
	 */
	tp->snd_wnd = ntohs(tcp_hdr(skb)->winकरोw);
	tp->max_winकरोw = tp->snd_wnd;

	/* Activate the retrans समयr so that SYNACK can be retransmitted.
	 * The request socket is not added to the ehash
	 * because it's been added to the accept queue directly.
	 */
	inet_csk_reset_xmit_समयr(child, ICSK_TIME_RETRANS,
				  TCP_TIMEOUT_INIT, TCP_RTO_MAX);

	refcount_set(&req->rsk_refcnt, 2);

	/* Now finish processing the fastखोलो child socket. */
	tcp_init_transfer(child, BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB, skb);

	tp->rcv_nxt = TCP_SKB_CB(skb)->seq + 1;

	tcp_fastखोलो_add_skb(child, skb);

	tcp_rsk(req)->rcv_nxt = tp->rcv_nxt;
	tp->rcv_wup = tp->rcv_nxt;
	/* tcp_conn_request() is sending the SYNACK,
	 * and queues the child पूर्णांकo listener accept queue.
	 */
	वापस child;
पूर्ण

अटल bool tcp_fastखोलो_queue_check(काष्ठा sock *sk)
अणु
	काष्ठा fastखोलो_queue *fastखोलोq;

	/* Make sure the listener has enabled fastखोलो, and we करोn't
	 * exceed the max # of pending TFO requests allowed beक्रमe trying
	 * to validating the cookie in order to aव्योम burning CPU cycles
	 * unnecessarily.
	 *
	 * XXX (TFO) - The implication of checking the max_qlen beक्रमe
	 * processing a cookie request is that clients can't dअगरferentiate
	 * between qlen overflow causing Fast Open to be disabled
	 * temporarily vs a server not supporting Fast Open at all.
	 */
	fastखोलोq = &inet_csk(sk)->icsk_accept_queue.fastखोलोq;
	अगर (fastखोलोq->max_qlen == 0)
		वापस false;

	अगर (fastखोलोq->qlen >= fastखोलोq->max_qlen) अणु
		काष्ठा request_sock *req1;
		spin_lock(&fastखोलोq->lock);
		req1 = fastखोलोq->rskq_rst_head;
		अगर (!req1 || समय_after(req1->rsk_समयr.expires, jअगरfies)) अणु
			__NET_INC_STATS(sock_net(sk),
					LINUX_MIB_TCPFASTOPENLISTENOVERFLOW);
			spin_unlock(&fastखोलोq->lock);
			वापस false;
		पूर्ण
		fastखोलोq->rskq_rst_head = req1->dl_next;
		fastखोलोq->qlen--;
		spin_unlock(&fastखोलोq->lock);
		reqsk_put(req1);
	पूर्ण
	वापस true;
पूर्ण

अटल bool tcp_fastखोलो_no_cookie(स्थिर काष्ठा sock *sk,
				   स्थिर काष्ठा dst_entry *dst,
				   पूर्णांक flag)
अणु
	वापस (sock_net(sk)->ipv4.sysctl_tcp_fastखोलो & flag) ||
	       tcp_sk(sk)->fastखोलो_no_cookie ||
	       (dst && dst_metric(dst, RTAX_FASTOPEN_NO_COOKIE));
पूर्ण

/* Returns true अगर we should perक्रमm Fast Open on the SYN. The cookie (foc)
 * may be updated and वापस the client in the SYN-ACK later. E.g., Fast Open
 * cookie request (foc->len == 0).
 */
काष्ठा sock *tcp_try_fastखोलो(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			      काष्ठा request_sock *req,
			      काष्ठा tcp_fastखोलो_cookie *foc,
			      स्थिर काष्ठा dst_entry *dst)
अणु
	bool syn_data = TCP_SKB_CB(skb)->end_seq != TCP_SKB_CB(skb)->seq + 1;
	पूर्णांक tcp_fastखोलो = sock_net(sk)->ipv4.sysctl_tcp_fastखोलो;
	काष्ठा tcp_fastखोलो_cookie valid_foc = अणु .len = -1 पूर्ण;
	काष्ठा sock *child;
	पूर्णांक ret = 0;

	अगर (foc->len == 0) /* Client requests a cookie */
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPFASTOPENCOOKIEREQD);

	अगर (!((tcp_fastखोलो & TFO_SERVER_ENABLE) &&
	      (syn_data || foc->len >= 0) &&
	      tcp_fastखोलो_queue_check(sk))) अणु
		foc->len = -1;
		वापस शून्य;
	पूर्ण

	अगर (syn_data &&
	    tcp_fastखोलो_no_cookie(sk, dst, TFO_SERVER_COOKIE_NOT_REQD))
		जाओ fastखोलो;

	अगर (foc->len == 0) अणु
		/* Client requests a cookie. */
		tcp_fastखोलो_cookie_gen(sk, req, skb, &valid_foc);
	पूर्ण अन्यथा अगर (foc->len > 0) अणु
		ret = tcp_fastखोलो_cookie_gen_check(sk, req, skb, foc,
						    &valid_foc);
		अगर (!ret) अणु
			NET_INC_STATS(sock_net(sk),
				      LINUX_MIB_TCPFASTOPENPASSIVEFAIL);
		पूर्ण अन्यथा अणु
			/* Cookie is valid. Create a (full) child socket to
			 * accept the data in SYN beक्रमe वापसing a SYN-ACK to
			 * ack the data. If we fail to create the socket, fall
			 * back and ack the ISN only but includes the same
			 * cookie.
			 *
			 * Note: Data-less SYN with valid cookie is allowed to
			 * send data in SYN_RECV state.
			 */
fastखोलो:
			child = tcp_fastखोलो_create_child(sk, skb, req);
			अगर (child) अणु
				अगर (ret == 2) अणु
					valid_foc.exp = foc->exp;
					*foc = valid_foc;
					NET_INC_STATS(sock_net(sk),
						      LINUX_MIB_TCPFASTOPENPASSIVEALTKEY);
				पूर्ण अन्यथा अणु
					foc->len = -1;
				पूर्ण
				NET_INC_STATS(sock_net(sk),
					      LINUX_MIB_TCPFASTOPENPASSIVE);
				वापस child;
			पूर्ण
			NET_INC_STATS(sock_net(sk),
				      LINUX_MIB_TCPFASTOPENPASSIVEFAIL);
		पूर्ण
	पूर्ण
	valid_foc.exp = foc->exp;
	*foc = valid_foc;
	वापस शून्य;
पूर्ण

bool tcp_fastखोलो_cookie_check(काष्ठा sock *sk, u16 *mss,
			       काष्ठा tcp_fastखोलो_cookie *cookie)
अणु
	स्थिर काष्ठा dst_entry *dst;

	tcp_fastखोलो_cache_get(sk, mss, cookie);

	/* Firewall blackhole issue check */
	अगर (tcp_fastखोलो_active_should_disable(sk)) अणु
		cookie->len = -1;
		वापस false;
	पूर्ण

	dst = __sk_dst_get(sk);

	अगर (tcp_fastखोलो_no_cookie(sk, dst, TFO_CLIENT_NO_COOKIE)) अणु
		cookie->len = -1;
		वापस true;
	पूर्ण
	अगर (cookie->len > 0)
		वापस true;
	tcp_sk(sk)->fastखोलो_client_fail = TFO_COOKIE_UNAVAILABLE;
	वापस false;
पूर्ण

/* This function checks अगर we want to defer sending SYN until the first
 * ग_लिखो().  We defer under the following conditions:
 * 1. fastखोलो_connect sockopt is set
 * 2. we have a valid cookie
 * Return value: वापस true अगर we want to defer until application ग_लिखोs data
 *               वापस false अगर we want to send out SYN immediately
 */
bool tcp_fastखोलो_defer_connect(काष्ठा sock *sk, पूर्णांक *err)
अणु
	काष्ठा tcp_fastखोलो_cookie cookie = अणु .len = 0 पूर्ण;
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u16 mss;

	अगर (tp->fastखोलो_connect && !tp->fastखोलो_req) अणु
		अगर (tcp_fastखोलो_cookie_check(sk, &mss, &cookie)) अणु
			inet_sk(sk)->defer_connect = 1;
			वापस true;
		पूर्ण

		/* Alloc fastखोलो_req in order क्रम FO option to be included
		 * in SYN
		 */
		tp->fastखोलो_req = kzalloc(माप(*tp->fastखोलो_req),
					   sk->sk_allocation);
		अगर (tp->fastखोलो_req)
			tp->fastखोलो_req->cookie = cookie;
		अन्यथा
			*err = -ENOBUFS;
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL(tcp_fastखोलो_defer_connect);

/*
 * The following code block is to deal with middle box issues with TFO:
 * Middlebox firewall issues can potentially cause server's data being
 * blackholed after a successful 3WHS using TFO.
 * The proposed solution is to disable active TFO globally under the
 * following circumstances:
 *   1. client side TFO socket receives out of order FIN
 *   2. client side TFO socket receives out of order RST
 *   3. client side TFO socket has समयd out three बार consecutively during
 *      or after handshake
 * We disable active side TFO globally क्रम 1hr at first. Then अगर it
 * happens again, we disable it क्रम 2h, then 4h, 8h, ...
 * And we reset the समयout back to 1hr when we see a successful active
 * TFO connection with data exchanges.
 */

/* Disable active TFO and record current jअगरfies and
 * tfo_active_disable_बार
 */
व्योम tcp_fastखोलो_active_disable(काष्ठा sock *sk)
अणु
	काष्ठा net *net = sock_net(sk);

	atomic_inc(&net->ipv4.tfo_active_disable_बार);
	net->ipv4.tfo_active_disable_stamp = jअगरfies;
	NET_INC_STATS(net, LINUX_MIB_TCPFASTOPENBLACKHOLE);
पूर्ण

/* Calculate समयout क्रम tfo active disable
 * Return true अगर we are still in the active TFO disable period
 * Return false अगर समयout alपढ़ोy expired and we should use active TFO
 */
bool tcp_fastखोलो_active_should_disable(काष्ठा sock *sk)
अणु
	अचिन्हित पूर्णांक tfo_bh_समयout = sock_net(sk)->ipv4.sysctl_tcp_fastखोलो_blackhole_समयout;
	पूर्णांक tfo_da_बार = atomic_पढ़ो(&sock_net(sk)->ipv4.tfo_active_disable_बार);
	अचिन्हित दीर्घ समयout;
	पूर्णांक multiplier;

	अगर (!tfo_da_बार)
		वापस false;

	/* Limit timout to max: 2^6 * initial समयout */
	multiplier = 1 << min(tfo_da_बार - 1, 6);
	समयout = multiplier * tfo_bh_समयout * HZ;
	अगर (समय_beक्रमe(jअगरfies, sock_net(sk)->ipv4.tfo_active_disable_stamp + समयout))
		वापस true;

	/* Mark check bit so we can check क्रम successful active TFO
	 * condition and reset tfo_active_disable_बार
	 */
	tcp_sk(sk)->syn_fastखोलो_ch = 1;
	वापस false;
पूर्ण

/* Disable active TFO अगर FIN is the only packet in the ofo queue
 * and no data is received.
 * Also check अगर we can reset tfo_active_disable_बार अगर data is
 * received successfully on a marked active TFO sockets खोलोed on
 * a non-loopback पूर्णांकerface
 */
व्योम tcp_fastखोलो_active_disable_ofo_check(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा dst_entry *dst;
	काष्ठा sk_buff *skb;

	अगर (!tp->syn_fastखोलो)
		वापस;

	अगर (!tp->data_segs_in) अणु
		skb = skb_rb_first(&tp->out_of_order_queue);
		अगर (skb && !skb_rb_next(skb)) अणु
			अगर (TCP_SKB_CB(skb)->tcp_flags & TCPHDR_FIN) अणु
				tcp_fastखोलो_active_disable(sk);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (tp->syn_fastखोलो_ch &&
		   atomic_पढ़ो(&sock_net(sk)->ipv4.tfo_active_disable_बार)) अणु
		dst = sk_dst_get(sk);
		अगर (!(dst && dst->dev && (dst->dev->flags & IFF_LOOPBACK)))
			atomic_set(&sock_net(sk)->ipv4.tfo_active_disable_बार, 0);
		dst_release(dst);
	पूर्ण
पूर्ण

व्योम tcp_fastखोलो_active_detect_blackhole(काष्ठा sock *sk, bool expired)
अणु
	u32 समयouts = inet_csk(sk)->icsk_retransmits;
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	/* Broken middle-boxes may black-hole Fast Open connection during or
	 * even after the handshake. Be extremely conservative and छोड़ो
	 * Fast Open globally after hitting the third consecutive समयout or
	 * exceeding the configured समयout limit.
	 */
	अगर ((tp->syn_fastखोलो || tp->syn_data || tp->syn_data_acked) &&
	    (समयouts == 2 || (समयouts < 2 && expired))) अणु
		tcp_fastखोलो_active_disable(sk);
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPFASTOPENACTIVEFAIL);
	पूर्ण
पूर्ण
