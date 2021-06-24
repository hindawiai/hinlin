<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	IPV4 GSO/GRO offload support
 *	Linux INET implementation
 *
 *	TCPv4 GSO/GRO support
 */

#समावेश <linux/indirect_call_wrapper.h>
#समावेश <linux/skbuff.h>
#समावेश <net/tcp.h>
#समावेश <net/protocol.h>

अटल व्योम tcp_gso_tstamp(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक ts_seq,
			   अचिन्हित पूर्णांक seq, अचिन्हित पूर्णांक mss)
अणु
	जबतक (skb) अणु
		अगर (beक्रमe(ts_seq, seq + mss)) अणु
			skb_shinfo(skb)->tx_flags |= SKBTX_SW_TSTAMP;
			skb_shinfo(skb)->tskey = ts_seq;
			वापस;
		पूर्ण

		skb = skb->next;
		seq += mss;
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *tcp4_gso_segment(काष्ठा sk_buff *skb,
					netdev_features_t features)
अणु
	अगर (!(skb_shinfo(skb)->gso_type & SKB_GSO_TCPV4))
		वापस ERR_PTR(-EINVAL);

	अगर (!pskb_may_pull(skb, माप(काष्ठा tcphdr)))
		वापस ERR_PTR(-EINVAL);

	अगर (unlikely(skb->ip_summed != CHECKSUM_PARTIAL)) अणु
		स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
		काष्ठा tcphdr *th = tcp_hdr(skb);

		/* Set up checksum pseuकरो header, usually expect stack to
		 * have करोne this alपढ़ोy.
		 */

		th->check = 0;
		skb->ip_summed = CHECKSUM_PARTIAL;
		__tcp_v4_send_check(skb, iph->saddr, iph->daddr);
	पूर्ण

	वापस tcp_gso_segment(skb, features);
पूर्ण

काष्ठा sk_buff *tcp_gso_segment(काष्ठा sk_buff *skb,
				netdev_features_t features)
अणु
	काष्ठा sk_buff *segs = ERR_PTR(-EINVAL);
	अचिन्हित पूर्णांक sum_truesize = 0;
	काष्ठा tcphdr *th;
	अचिन्हित पूर्णांक thlen;
	अचिन्हित पूर्णांक seq;
	__be32 delta;
	अचिन्हित पूर्णांक oldlen;
	अचिन्हित पूर्णांक mss;
	काष्ठा sk_buff *gso_skb = skb;
	__sum16 newcheck;
	bool ooo_okay, copy_deकाष्ठाor;

	th = tcp_hdr(skb);
	thlen = th->करोff * 4;
	अगर (thlen < माप(*th))
		जाओ out;

	अगर (!pskb_may_pull(skb, thlen))
		जाओ out;

	oldlen = (u16)~skb->len;
	__skb_pull(skb, thlen);

	mss = skb_shinfo(skb)->gso_size;
	अगर (unlikely(skb->len <= mss))
		जाओ out;

	अगर (skb_gso_ok(skb, features | NETIF_F_GSO_ROBUST)) अणु
		/* Packet is from an untrusted source, reset gso_segs. */

		skb_shinfo(skb)->gso_segs = DIV_ROUND_UP(skb->len, mss);

		segs = शून्य;
		जाओ out;
	पूर्ण

	copy_deकाष्ठाor = gso_skb->deकाष्ठाor == tcp_wमुक्त;
	ooo_okay = gso_skb->ooo_okay;
	/* All segments but the first should have ooo_okay cleared */
	skb->ooo_okay = 0;

	segs = skb_segment(skb, features);
	अगर (IS_ERR(segs))
		जाओ out;

	/* Only first segment might have ooo_okay set */
	segs->ooo_okay = ooo_okay;

	/* GSO partial and frag_list segmentation only requires splitting
	 * the frame पूर्णांकo an MSS multiple and possibly a reमुख्यder, both
	 * हालs वापस a GSO skb. So update the mss now.
	 */
	अगर (skb_is_gso(segs))
		mss *= skb_shinfo(segs)->gso_segs;

	delta = htonl(oldlen + (thlen + mss));

	skb = segs;
	th = tcp_hdr(skb);
	seq = ntohl(th->seq);

	अगर (unlikely(skb_shinfo(gso_skb)->tx_flags & SKBTX_SW_TSTAMP))
		tcp_gso_tstamp(segs, skb_shinfo(gso_skb)->tskey, seq, mss);

	newcheck = ~csum_fold((__क्रमce __wsum)((__क्रमce u32)th->check +
					       (__क्रमce u32)delta));

	जबतक (skb->next) अणु
		th->fin = th->psh = 0;
		th->check = newcheck;

		अगर (skb->ip_summed == CHECKSUM_PARTIAL)
			gso_reset_checksum(skb, ~th->check);
		अन्यथा
			th->check = gso_make_checksum(skb, ~th->check);

		seq += mss;
		अगर (copy_deकाष्ठाor) अणु
			skb->deकाष्ठाor = gso_skb->deकाष्ठाor;
			skb->sk = gso_skb->sk;
			sum_truesize += skb->truesize;
		पूर्ण
		skb = skb->next;
		th = tcp_hdr(skb);

		th->seq = htonl(seq);
		th->cwr = 0;
	पूर्ण

	/* Following permits TCP Small Queues to work well with GSO :
	 * The callback to TCP stack will be called at the समय last frag
	 * is मुक्तd at TX completion, and not right now when gso_skb
	 * is मुक्तd by GSO engine
	 */
	अगर (copy_deकाष्ठाor) अणु
		पूर्णांक delta;

		swap(gso_skb->sk, skb->sk);
		swap(gso_skb->deकाष्ठाor, skb->deकाष्ठाor);
		sum_truesize += skb->truesize;
		delta = sum_truesize - gso_skb->truesize;
		/* In some pathological हालs, delta can be negative.
		 * We need to either use refcount_add() or refcount_sub_and_test()
		 */
		अगर (likely(delta >= 0))
			refcount_add(delta, &skb->sk->sk_wmem_alloc);
		अन्यथा
			WARN_ON_ONCE(refcount_sub_and_test(-delta, &skb->sk->sk_wmem_alloc));
	पूर्ण

	delta = htonl(oldlen + (skb_tail_poपूर्णांकer(skb) -
				skb_transport_header(skb)) +
		      skb->data_len);
	th->check = ~csum_fold((__क्रमce __wsum)((__क्रमce u32)th->check +
				(__क्रमce u32)delta));
	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		gso_reset_checksum(skb, ~th->check);
	अन्यथा
		th->check = gso_make_checksum(skb, ~th->check);
out:
	वापस segs;
पूर्ण

काष्ठा sk_buff *tcp_gro_receive(काष्ठा list_head *head, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *pp = शून्य;
	काष्ठा sk_buff *p;
	काष्ठा tcphdr *th;
	काष्ठा tcphdr *th2;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक thlen;
	__be32 flags;
	अचिन्हित पूर्णांक mss = 1;
	अचिन्हित पूर्णांक hlen;
	अचिन्हित पूर्णांक off;
	पूर्णांक flush = 1;
	पूर्णांक i;

	off = skb_gro_offset(skb);
	hlen = off + माप(*th);
	th = skb_gro_header_fast(skb, off);
	अगर (skb_gro_header_hard(skb, hlen)) अणु
		th = skb_gro_header_slow(skb, hlen, off);
		अगर (unlikely(!th))
			जाओ out;
	पूर्ण

	thlen = th->करोff * 4;
	अगर (thlen < माप(*th))
		जाओ out;

	hlen = off + thlen;
	अगर (skb_gro_header_hard(skb, hlen)) अणु
		th = skb_gro_header_slow(skb, hlen, off);
		अगर (unlikely(!th))
			जाओ out;
	पूर्ण

	skb_gro_pull(skb, thlen);

	len = skb_gro_len(skb);
	flags = tcp_flag_word(th);

	list_क्रम_each_entry(p, head, list) अणु
		अगर (!NAPI_GRO_CB(p)->same_flow)
			जारी;

		th2 = tcp_hdr(p);

		अगर (*(u32 *)&th->source ^ *(u32 *)&th2->source) अणु
			NAPI_GRO_CB(p)->same_flow = 0;
			जारी;
		पूर्ण

		जाओ found;
	पूर्ण
	p = शून्य;
	जाओ out_check_final;

found:
	/* Include the IP ID check below from the inner most IP hdr */
	flush = NAPI_GRO_CB(p)->flush;
	flush |= (__क्रमce पूर्णांक)(flags & TCP_FLAG_CWR);
	flush |= (__क्रमce पूर्णांक)((flags ^ tcp_flag_word(th2)) &
		  ~(TCP_FLAG_CWR | TCP_FLAG_FIN | TCP_FLAG_PSH));
	flush |= (__क्रमce पूर्णांक)(th->ack_seq ^ th2->ack_seq);
	क्रम (i = माप(*th); i < thlen; i += 4)
		flush |= *(u32 *)((u8 *)th + i) ^
			 *(u32 *)((u8 *)th2 + i);

	/* When we receive our second frame we can made a decision on अगर we
	 * जारी this flow as an atomic flow with a fixed ID or अगर we use
	 * an incrementing ID.
	 */
	अगर (NAPI_GRO_CB(p)->flush_id != 1 ||
	    NAPI_GRO_CB(p)->count != 1 ||
	    !NAPI_GRO_CB(p)->is_atomic)
		flush |= NAPI_GRO_CB(p)->flush_id;
	अन्यथा
		NAPI_GRO_CB(p)->is_atomic = false;

	mss = skb_shinfo(p)->gso_size;

	flush |= (len - 1) >= mss;
	flush |= (ntohl(th2->seq) + skb_gro_len(p)) ^ ntohl(th->seq);
#अगर_घोषित CONFIG_TLS_DEVICE
	flush |= p->decrypted ^ skb->decrypted;
#पूर्ण_अगर

	अगर (flush || skb_gro_receive(p, skb)) अणु
		mss = 1;
		जाओ out_check_final;
	पूर्ण

	tcp_flag_word(th2) |= flags & (TCP_FLAG_FIN | TCP_FLAG_PSH);

out_check_final:
	flush = len < mss;
	flush |= (__क्रमce पूर्णांक)(flags & (TCP_FLAG_URG | TCP_FLAG_PSH |
					TCP_FLAG_RST | TCP_FLAG_SYN |
					TCP_FLAG_FIN));

	अगर (p && (!NAPI_GRO_CB(skb)->same_flow || flush))
		pp = p;

out:
	NAPI_GRO_CB(skb)->flush |= (flush != 0);

	वापस pp;
पूर्ण

पूर्णांक tcp_gro_complete(काष्ठा sk_buff *skb)
अणु
	काष्ठा tcphdr *th = tcp_hdr(skb);

	skb->csum_start = (अचिन्हित अक्षर *)th - skb->head;
	skb->csum_offset = दुरत्व(काष्ठा tcphdr, check);
	skb->ip_summed = CHECKSUM_PARTIAL;

	skb_shinfo(skb)->gso_segs = NAPI_GRO_CB(skb)->count;

	अगर (th->cwr)
		skb_shinfo(skb)->gso_type |= SKB_GSO_TCP_ECN;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tcp_gro_complete);

INसूचीECT_CALLABLE_SCOPE
काष्ठा sk_buff *tcp4_gro_receive(काष्ठा list_head *head, काष्ठा sk_buff *skb)
अणु
	/* Don't bother verifying checksum if we're going to flush anyway. */
	अगर (!NAPI_GRO_CB(skb)->flush &&
	    skb_gro_checksum_validate(skb, IPPROTO_TCP,
				      inet_gro_compute_pseuकरो)) अणु
		NAPI_GRO_CB(skb)->flush = 1;
		वापस शून्य;
	पूर्ण

	वापस tcp_gro_receive(head, skb);
पूर्ण

INसूचीECT_CALLABLE_SCOPE पूर्णांक tcp4_gro_complete(काष्ठा sk_buff *skb, पूर्णांक thoff)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	काष्ठा tcphdr *th = tcp_hdr(skb);

	th->check = ~tcp_v4_check(skb->len - thoff, iph->saddr,
				  iph->daddr, 0);
	skb_shinfo(skb)->gso_type |= SKB_GSO_TCPV4;

	अगर (NAPI_GRO_CB(skb)->is_atomic)
		skb_shinfo(skb)->gso_type |= SKB_GSO_TCP_FIXEDID;

	वापस tcp_gro_complete(skb);
पूर्ण

अटल स्थिर काष्ठा net_offload tcpv4_offload = अणु
	.callbacks = अणु
		.gso_segment	=	tcp4_gso_segment,
		.gro_receive	=	tcp4_gro_receive,
		.gro_complete	=	tcp4_gro_complete,
	पूर्ण,
पूर्ण;

पूर्णांक __init tcpv4_offload_init(व्योम)
अणु
	वापस inet_add_offload(&tcpv4_offload, IPPROTO_TCP);
पूर्ण
