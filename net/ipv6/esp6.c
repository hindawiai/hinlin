<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C)2002 USAGI/WIDE Project
 *
 * Authors
 *
 *	Mitsuru KANDA @USAGI       : IPv6 Support
 *	Kazunori MIYAZAWA @USAGI   :
 *	Kunihiro Ishiguro <kunihiro@ipinfusion.com>
 *
 *	This file is derived from net/ipv4/esp.c
 */

#घोषणा pr_fmt(fmt) "IPv6: " fmt

#समावेश <crypto/aead.h>
#समावेश <crypto/authenc.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <net/ip.h>
#समावेश <net/xfrm.h>
#समावेश <net/esp.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pfkeyv2.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/ip6_route.h>
#समावेश <net/icmp.h>
#समावेश <net/ipv6.h>
#समावेश <net/protocol.h>
#समावेश <net/udp.h>
#समावेश <linux/icmpv6.h>
#समावेश <net/tcp.h>
#समावेश <net/espपूर्णांकcp.h>
#समावेश <net/inet6_hashtables.h>

#समावेश <linux/highस्मृति.स>

काष्ठा esp_skb_cb अणु
	काष्ठा xfrm_skb_cb xfrm;
	व्योम *पंचांगp;
पूर्ण;

काष्ठा esp_output_extra अणु
	__be32 seqhi;
	u32 esphoff;
पूर्ण;

#घोषणा ESP_SKB_CB(__skb) ((काष्ठा esp_skb_cb *)&((__skb)->cb[0]))

/*
 * Allocate an AEAD request काष्ठाure with extra space क्रम SG and IV.
 *
 * For alignment considerations the upper 32 bits of the sequence number are
 * placed at the front, अगर present. Followed by the IV, the request and finally
 * the SG list.
 *
 * TODO: Use spare space in skb क्रम this where possible.
 */
अटल व्योम *esp_alloc_पंचांगp(काष्ठा crypto_aead *aead, पूर्णांक nfrags, पूर्णांक seqihlen)
अणु
	अचिन्हित पूर्णांक len;

	len = seqihlen;

	len += crypto_aead_ivsize(aead);

	अगर (len) अणु
		len += crypto_aead_alignmask(aead) &
		       ~(crypto_tfm_ctx_alignment() - 1);
		len = ALIGN(len, crypto_tfm_ctx_alignment());
	पूर्ण

	len += माप(काष्ठा aead_request) + crypto_aead_reqsize(aead);
	len = ALIGN(len, __alignof__(काष्ठा scatterlist));

	len += माप(काष्ठा scatterlist) * nfrags;

	वापस kदो_स्मृति(len, GFP_ATOMIC);
पूर्ण

अटल अंतरभूत व्योम *esp_पंचांगp_extra(व्योम *पंचांगp)
अणु
	वापस PTR_ALIGN(पंचांगp, __alignof__(काष्ठा esp_output_extra));
पूर्ण

अटल अंतरभूत u8 *esp_पंचांगp_iv(काष्ठा crypto_aead *aead, व्योम *पंचांगp, पूर्णांक seqhilen)
अणु
	वापस crypto_aead_ivsize(aead) ?
	       PTR_ALIGN((u8 *)पंचांगp + seqhilen,
			 crypto_aead_alignmask(aead) + 1) : पंचांगp + seqhilen;
पूर्ण

अटल अंतरभूत काष्ठा aead_request *esp_पंचांगp_req(काष्ठा crypto_aead *aead, u8 *iv)
अणु
	काष्ठा aead_request *req;

	req = (व्योम *)PTR_ALIGN(iv + crypto_aead_ivsize(aead),
				crypto_tfm_ctx_alignment());
	aead_request_set_tfm(req, aead);
	वापस req;
पूर्ण

अटल अंतरभूत काष्ठा scatterlist *esp_req_sg(काष्ठा crypto_aead *aead,
					     काष्ठा aead_request *req)
अणु
	वापस (व्योम *)ALIGN((अचिन्हित दीर्घ)(req + 1) +
			     crypto_aead_reqsize(aead),
			     __alignof__(काष्ठा scatterlist));
पूर्ण

अटल व्योम esp_ssg_unref(काष्ठा xfrm_state *x, व्योम *पंचांगp)
अणु
	काष्ठा esp_output_extra *extra = esp_पंचांगp_extra(पंचांगp);
	काष्ठा crypto_aead *aead = x->data;
	पूर्णांक extralen = 0;
	u8 *iv;
	काष्ठा aead_request *req;
	काष्ठा scatterlist *sg;

	अगर (x->props.flags & XFRM_STATE_ESN)
		extralen += माप(*extra);

	iv = esp_पंचांगp_iv(aead, पंचांगp, extralen);
	req = esp_पंचांगp_req(aead, iv);

	/* Unref skb_frag_pages in the src scatterlist अगर necessary.
	 * Skip the first sg which comes from skb->data.
	 */
	अगर (req->src != req->dst)
		क्रम (sg = sg_next(req->src); sg; sg = sg_next(sg))
			put_page(sg_page(sg));
पूर्ण

#अगर_घोषित CONFIG_INET6_ESPINTCP
काष्ठा esp_tcp_sk अणु
	काष्ठा sock *sk;
	काष्ठा rcu_head rcu;
पूर्ण;

अटल व्योम esp_मुक्त_tcp_sk(काष्ठा rcu_head *head)
अणु
	काष्ठा esp_tcp_sk *esk = container_of(head, काष्ठा esp_tcp_sk, rcu);

	sock_put(esk->sk);
	kमुक्त(esk);
पूर्ण

अटल काष्ठा sock *esp6_find_tcp_sk(काष्ठा xfrm_state *x)
अणु
	काष्ठा xfrm_encap_पंचांगpl *encap = x->encap;
	काष्ठा esp_tcp_sk *esk;
	__be16 sport, dport;
	काष्ठा sock *nsk;
	काष्ठा sock *sk;

	sk = rcu_dereference(x->encap_sk);
	अगर (sk && sk->sk_state == TCP_ESTABLISHED)
		वापस sk;

	spin_lock_bh(&x->lock);
	sport = encap->encap_sport;
	dport = encap->encap_dport;
	nsk = rcu_dereference_रक्षित(x->encap_sk,
					lockdep_is_held(&x->lock));
	अगर (sk && sk == nsk) अणु
		esk = kदो_स्मृति(माप(*esk), GFP_ATOMIC);
		अगर (!esk) अणु
			spin_unlock_bh(&x->lock);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
		RCU_INIT_POINTER(x->encap_sk, शून्य);
		esk->sk = sk;
		call_rcu(&esk->rcu, esp_मुक्त_tcp_sk);
	पूर्ण
	spin_unlock_bh(&x->lock);

	sk = __inet6_lookup_established(xs_net(x), &tcp_hashinfo, &x->id.daddr.in6,
					dport, &x->props.saddr.in6, ntohs(sport), 0, 0);
	अगर (!sk)
		वापस ERR_PTR(-ENOENT);

	अगर (!tcp_is_ulp_esp(sk)) अणु
		sock_put(sk);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	spin_lock_bh(&x->lock);
	nsk = rcu_dereference_रक्षित(x->encap_sk,
					lockdep_is_held(&x->lock));
	अगर (encap->encap_sport != sport ||
	    encap->encap_dport != dport) अणु
		sock_put(sk);
		sk = nsk ?: ERR_PTR(-EREMCHG);
	पूर्ण अन्यथा अगर (sk == nsk) अणु
		sock_put(sk);
	पूर्ण अन्यथा अणु
		rcu_assign_poपूर्णांकer(x->encap_sk, sk);
	पूर्ण
	spin_unlock_bh(&x->lock);

	वापस sk;
पूर्ण

अटल पूर्णांक esp_output_tcp_finish(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk;
	पूर्णांक err;

	rcu_पढ़ो_lock();

	sk = esp6_find_tcp_sk(x);
	err = PTR_ERR_OR_ZERO(sk);
	अगर (err)
		जाओ out;

	bh_lock_sock(sk);
	अगर (sock_owned_by_user(sk))
		err = espपूर्णांकcp_queue_out(sk, skb);
	अन्यथा
		err = espपूर्णांकcp_push_skb(sk, skb);
	bh_unlock_sock(sk);

out:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक esp_output_tcp_encap_cb(काष्ठा net *net, काष्ठा sock *sk,
				   काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा xfrm_state *x = dst->xfrm;

	वापस esp_output_tcp_finish(x, skb);
पूर्ण

अटल पूर्णांक esp_output_tail_tcp(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	local_bh_disable();
	err = xfrm_trans_queue_net(xs_net(x), skb, esp_output_tcp_encap_cb);
	local_bh_enable();

	/* EINPROGRESS just happens to करो the right thing.  It
	 * actually means that the skb has been consumed and
	 * isn't coming back.
	 */
	वापस err ?: -EINPROGRESS;
पूर्ण
#अन्यथा
अटल पूर्णांक esp_output_tail_tcp(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	kमुक्त_skb(skb);

	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

अटल व्योम esp_output_encap_csum(काष्ठा sk_buff *skb)
अणु
	/* UDP encap with IPv6 requires a valid checksum */
	अगर (*skb_mac_header(skb) == IPPROTO_UDP) अणु
		काष्ठा udphdr *uh = udp_hdr(skb);
		काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);
		पूर्णांक len = ntohs(uh->len);
		अचिन्हित पूर्णांक offset = skb_transport_offset(skb);
		__wsum csum = skb_checksum(skb, offset, skb->len - offset, 0);

		uh->check = csum_ipv6_magic(&ip6h->saddr, &ip6h->daddr,
					    len, IPPROTO_UDP, csum);
		अगर (uh->check == 0)
			uh->check = CSUM_MANGLED_0;
	पूर्ण
पूर्ण

अटल व्योम esp_output_करोne(काष्ठा crypto_async_request *base, पूर्णांक err)
अणु
	काष्ठा sk_buff *skb = base->data;
	काष्ठा xfrm_offload *xo = xfrm_offload(skb);
	व्योम *पंचांगp;
	काष्ठा xfrm_state *x;

	अगर (xo && (xo->flags & XFRM_DEV_RESUME)) अणु
		काष्ठा sec_path *sp = skb_sec_path(skb);

		x = sp->xvec[sp->len - 1];
	पूर्ण अन्यथा अणु
		x = skb_dst(skb)->xfrm;
	पूर्ण

	पंचांगp = ESP_SKB_CB(skb)->पंचांगp;
	esp_ssg_unref(x, पंचांगp);
	kमुक्त(पंचांगp);

	esp_output_encap_csum(skb);

	अगर (xo && (xo->flags & XFRM_DEV_RESUME)) अणु
		अगर (err) अणु
			XFRM_INC_STATS(xs_net(x), LINUX_MIB_XFRMOUTSTATEPROTOERROR);
			kमुक्त_skb(skb);
			वापस;
		पूर्ण

		skb_push(skb, skb->data - skb_mac_header(skb));
		secpath_reset(skb);
		xfrm_dev_resume(skb);
	पूर्ण अन्यथा अणु
		अगर (!err &&
		    x->encap && x->encap->encap_type == TCP_ENCAP_ESPINTCP)
			esp_output_tail_tcp(x, skb);
		अन्यथा
			xfrm_output_resume(skb->sk, skb, err);
	पूर्ण
पूर्ण

/* Move ESP header back पूर्णांकo place. */
अटल व्योम esp_restore_header(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा ip_esp_hdr *esph = (व्योम *)(skb->data + offset);
	व्योम *पंचांगp = ESP_SKB_CB(skb)->पंचांगp;
	__be32 *seqhi = esp_पंचांगp_extra(पंचांगp);

	esph->seq_no = esph->spi;
	esph->spi = *seqhi;
पूर्ण

अटल व्योम esp_output_restore_header(काष्ठा sk_buff *skb)
अणु
	व्योम *पंचांगp = ESP_SKB_CB(skb)->पंचांगp;
	काष्ठा esp_output_extra *extra = esp_पंचांगp_extra(पंचांगp);

	esp_restore_header(skb, skb_transport_offset(skb) + extra->esphoff -
				माप(__be32));
पूर्ण

अटल काष्ठा ip_esp_hdr *esp_output_set_esn(काष्ठा sk_buff *skb,
					     काष्ठा xfrm_state *x,
					     काष्ठा ip_esp_hdr *esph,
					     काष्ठा esp_output_extra *extra)
अणु
	/* For ESN we move the header क्रमward by 4 bytes to
	 * accomodate the high bits.  We will move it back after
	 * encryption.
	 */
	अगर ((x->props.flags & XFRM_STATE_ESN)) अणु
		__u32 seqhi;
		काष्ठा xfrm_offload *xo = xfrm_offload(skb);

		अगर (xo)
			seqhi = xo->seq.hi;
		अन्यथा
			seqhi = XFRM_SKB_CB(skb)->seq.output.hi;

		extra->esphoff = (अचिन्हित अक्षर *)esph -
				 skb_transport_header(skb);
		esph = (काष्ठा ip_esp_hdr *)((अचिन्हित अक्षर *)esph - 4);
		extra->seqhi = esph->spi;
		esph->seq_no = htonl(seqhi);
	पूर्ण

	esph->spi = x->id.spi;

	वापस esph;
पूर्ण

अटल व्योम esp_output_करोne_esn(काष्ठा crypto_async_request *base, पूर्णांक err)
अणु
	काष्ठा sk_buff *skb = base->data;

	esp_output_restore_header(skb);
	esp_output_करोne(base, err);
पूर्ण

अटल काष्ठा ip_esp_hdr *esp6_output_udp_encap(काष्ठा sk_buff *skb,
					       पूर्णांक encap_type,
					       काष्ठा esp_info *esp,
					       __be16 sport,
					       __be16 dport)
अणु
	काष्ठा udphdr *uh;
	__be32 *udpdata32;
	अचिन्हित पूर्णांक len;

	len = skb->len + esp->tailen - skb_transport_offset(skb);
	अगर (len > U16_MAX)
		वापस ERR_PTR(-EMSGSIZE);

	uh = (काष्ठा udphdr *)esp->esph;
	uh->source = sport;
	uh->dest = dport;
	uh->len = htons(len);
	uh->check = 0;

	*skb_mac_header(skb) = IPPROTO_UDP;

	अगर (encap_type == UDP_ENCAP_ESPINUDP_NON_IKE) अणु
		udpdata32 = (__be32 *)(uh + 1);
		udpdata32[0] = udpdata32[1] = 0;
		वापस (काष्ठा ip_esp_hdr *)(udpdata32 + 2);
	पूर्ण

	वापस (काष्ठा ip_esp_hdr *)(uh + 1);
पूर्ण

#अगर_घोषित CONFIG_INET6_ESPINTCP
अटल काष्ठा ip_esp_hdr *esp6_output_tcp_encap(काष्ठा xfrm_state *x,
						काष्ठा sk_buff *skb,
						काष्ठा esp_info *esp)
अणु
	__be16 *lenp = (व्योम *)esp->esph;
	काष्ठा ip_esp_hdr *esph;
	अचिन्हित पूर्णांक len;
	काष्ठा sock *sk;

	len = skb->len + esp->tailen - skb_transport_offset(skb);
	अगर (len > IP_MAX_MTU)
		वापस ERR_PTR(-EMSGSIZE);

	rcu_पढ़ो_lock();
	sk = esp6_find_tcp_sk(x);
	rcu_पढ़ो_unlock();

	अगर (IS_ERR(sk))
		वापस ERR_CAST(sk);

	*lenp = htons(len);
	esph = (काष्ठा ip_esp_hdr *)(lenp + 1);

	वापस esph;
पूर्ण
#अन्यथा
अटल काष्ठा ip_esp_hdr *esp6_output_tcp_encap(काष्ठा xfrm_state *x,
						काष्ठा sk_buff *skb,
						काष्ठा esp_info *esp)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक esp6_output_encap(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb,
			    काष्ठा esp_info *esp)
अणु
	काष्ठा xfrm_encap_पंचांगpl *encap = x->encap;
	काष्ठा ip_esp_hdr *esph;
	__be16 sport, dport;
	पूर्णांक encap_type;

	spin_lock_bh(&x->lock);
	sport = encap->encap_sport;
	dport = encap->encap_dport;
	encap_type = encap->encap_type;
	spin_unlock_bh(&x->lock);

	चयन (encap_type) अणु
	शेष:
	हाल UDP_ENCAP_ESPINUDP:
	हाल UDP_ENCAP_ESPINUDP_NON_IKE:
		esph = esp6_output_udp_encap(skb, encap_type, esp, sport, dport);
		अवरोध;
	हाल TCP_ENCAP_ESPINTCP:
		esph = esp6_output_tcp_encap(x, skb, esp);
		अवरोध;
	पूर्ण

	अगर (IS_ERR(esph))
		वापस PTR_ERR(esph);

	esp->esph = esph;

	वापस 0;
पूर्ण

पूर्णांक esp6_output_head(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb, काष्ठा esp_info *esp)
अणु
	u8 *tail;
	पूर्णांक nfrags;
	पूर्णांक esph_offset;
	काष्ठा page *page;
	काष्ठा sk_buff *trailer;
	पूर्णांक tailen = esp->tailen;

	अगर (x->encap) अणु
		पूर्णांक err = esp6_output_encap(x, skb, esp);

		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (!skb_cloned(skb)) अणु
		अगर (tailen <= skb_tailroom(skb)) अणु
			nfrags = 1;
			trailer = skb;
			tail = skb_tail_poपूर्णांकer(trailer);

			जाओ skip_cow;
		पूर्ण अन्यथा अगर ((skb_shinfo(skb)->nr_frags < MAX_SKB_FRAGS)
			   && !skb_has_frag_list(skb)) अणु
			पूर्णांक allocsize;
			काष्ठा sock *sk = skb->sk;
			काष्ठा page_frag *pfrag = &x->xfrag;

			esp->inplace = false;

			allocsize = ALIGN(tailen, L1_CACHE_BYTES);

			spin_lock_bh(&x->lock);

			अगर (unlikely(!skb_page_frag_refill(allocsize, pfrag, GFP_ATOMIC))) अणु
				spin_unlock_bh(&x->lock);
				जाओ cow;
			पूर्ण

			page = pfrag->page;
			get_page(page);

			tail = page_address(page) + pfrag->offset;

			esp_output_fill_trailer(tail, esp->tfclen, esp->plen, esp->proto);

			nfrags = skb_shinfo(skb)->nr_frags;

			__skb_fill_page_desc(skb, nfrags, page, pfrag->offset,
					     tailen);
			skb_shinfo(skb)->nr_frags = ++nfrags;

			pfrag->offset = pfrag->offset + allocsize;

			spin_unlock_bh(&x->lock);

			nfrags++;

			skb->len += tailen;
			skb->data_len += tailen;
			skb->truesize += tailen;
			अगर (sk && sk_fullsock(sk))
				refcount_add(tailen, &sk->sk_wmem_alloc);

			जाओ out;
		पूर्ण
	पूर्ण

cow:
	esph_offset = (अचिन्हित अक्षर *)esp->esph - skb_transport_header(skb);

	nfrags = skb_cow_data(skb, tailen, &trailer);
	अगर (nfrags < 0)
		जाओ out;
	tail = skb_tail_poपूर्णांकer(trailer);
	esp->esph = (काष्ठा ip_esp_hdr *)(skb_transport_header(skb) + esph_offset);

skip_cow:
	esp_output_fill_trailer(tail, esp->tfclen, esp->plen, esp->proto);
	pskb_put(skb, trailer, tailen);

out:
	वापस nfrags;
पूर्ण
EXPORT_SYMBOL_GPL(esp6_output_head);

पूर्णांक esp6_output_tail(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb, काष्ठा esp_info *esp)
अणु
	u8 *iv;
	पूर्णांक alen;
	व्योम *पंचांगp;
	पूर्णांक ivlen;
	पूर्णांक assoclen;
	पूर्णांक extralen;
	काष्ठा page *page;
	काष्ठा ip_esp_hdr *esph;
	काष्ठा aead_request *req;
	काष्ठा crypto_aead *aead;
	काष्ठा scatterlist *sg, *dsg;
	काष्ठा esp_output_extra *extra;
	पूर्णांक err = -ENOMEM;

	assoclen = माप(काष्ठा ip_esp_hdr);
	extralen = 0;

	अगर (x->props.flags & XFRM_STATE_ESN) अणु
		extralen += माप(*extra);
		assoclen += माप(__be32);
	पूर्ण

	aead = x->data;
	alen = crypto_aead_authsize(aead);
	ivlen = crypto_aead_ivsize(aead);

	पंचांगp = esp_alloc_पंचांगp(aead, esp->nfrags + 2, extralen);
	अगर (!पंचांगp)
		जाओ error;

	extra = esp_पंचांगp_extra(पंचांगp);
	iv = esp_पंचांगp_iv(aead, पंचांगp, extralen);
	req = esp_पंचांगp_req(aead, iv);
	sg = esp_req_sg(aead, req);

	अगर (esp->inplace)
		dsg = sg;
	अन्यथा
		dsg = &sg[esp->nfrags];

	esph = esp_output_set_esn(skb, x, esp->esph, extra);
	esp->esph = esph;

	sg_init_table(sg, esp->nfrags);
	err = skb_to_sgvec(skb, sg,
		           (अचिन्हित अक्षर *)esph - skb->data,
		           assoclen + ivlen + esp->clen + alen);
	अगर (unlikely(err < 0))
		जाओ error_मुक्त;

	अगर (!esp->inplace) अणु
		पूर्णांक allocsize;
		काष्ठा page_frag *pfrag = &x->xfrag;

		allocsize = ALIGN(skb->data_len, L1_CACHE_BYTES);

		spin_lock_bh(&x->lock);
		अगर (unlikely(!skb_page_frag_refill(allocsize, pfrag, GFP_ATOMIC))) अणु
			spin_unlock_bh(&x->lock);
			जाओ error_मुक्त;
		पूर्ण

		skb_shinfo(skb)->nr_frags = 1;

		page = pfrag->page;
		get_page(page);
		/* replace page frags in skb with new page */
		__skb_fill_page_desc(skb, 0, page, pfrag->offset, skb->data_len);
		pfrag->offset = pfrag->offset + allocsize;
		spin_unlock_bh(&x->lock);

		sg_init_table(dsg, skb_shinfo(skb)->nr_frags + 1);
		err = skb_to_sgvec(skb, dsg,
			           (अचिन्हित अक्षर *)esph - skb->data,
			           assoclen + ivlen + esp->clen + alen);
		अगर (unlikely(err < 0))
			जाओ error_मुक्त;
	पूर्ण

	अगर ((x->props.flags & XFRM_STATE_ESN))
		aead_request_set_callback(req, 0, esp_output_करोne_esn, skb);
	अन्यथा
		aead_request_set_callback(req, 0, esp_output_करोne, skb);

	aead_request_set_crypt(req, sg, dsg, ivlen + esp->clen, iv);
	aead_request_set_ad(req, assoclen);

	स_रखो(iv, 0, ivlen);
	स_नकल(iv + ivlen - min(ivlen, 8), (u8 *)&esp->seqno + 8 - min(ivlen, 8),
	       min(ivlen, 8));

	ESP_SKB_CB(skb)->पंचांगp = पंचांगp;
	err = crypto_aead_encrypt(req);

	चयन (err) अणु
	हाल -EINPROGRESS:
		जाओ error;

	हाल -ENOSPC:
		err = NET_XMIT_DROP;
		अवरोध;

	हाल 0:
		अगर ((x->props.flags & XFRM_STATE_ESN))
			esp_output_restore_header(skb);
		esp_output_encap_csum(skb);
	पूर्ण

	अगर (sg != dsg)
		esp_ssg_unref(x, पंचांगp);

	अगर (!err && x->encap && x->encap->encap_type == TCP_ENCAP_ESPINTCP)
		err = esp_output_tail_tcp(x, skb);

error_मुक्त:
	kमुक्त(पंचांगp);
error:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(esp6_output_tail);

अटल पूर्णांक esp6_output(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	पूर्णांक alen;
	पूर्णांक blksize;
	काष्ठा ip_esp_hdr *esph;
	काष्ठा crypto_aead *aead;
	काष्ठा esp_info esp;

	esp.inplace = true;

	esp.proto = *skb_mac_header(skb);
	*skb_mac_header(skb) = IPPROTO_ESP;

	/* skb is pure payload to encrypt */

	aead = x->data;
	alen = crypto_aead_authsize(aead);

	esp.tfclen = 0;
	अगर (x->tfcpad) अणु
		काष्ठा xfrm_dst *dst = (काष्ठा xfrm_dst *)skb_dst(skb);
		u32 padto;

		padto = min(x->tfcpad, xfrm_state_mtu(x, dst->child_mtu_cached));
		अगर (skb->len < padto)
			esp.tfclen = padto - skb->len;
	पूर्ण
	blksize = ALIGN(crypto_aead_blocksize(aead), 4);
	esp.clen = ALIGN(skb->len + 2 + esp.tfclen, blksize);
	esp.plen = esp.clen - skb->len - esp.tfclen;
	esp.tailen = esp.tfclen + esp.plen + alen;

	esp.esph = ip_esp_hdr(skb);

	esp.nfrags = esp6_output_head(x, skb, &esp);
	अगर (esp.nfrags < 0)
		वापस esp.nfrags;

	esph = esp.esph;
	esph->spi = x->id.spi;

	esph->seq_no = htonl(XFRM_SKB_CB(skb)->seq.output.low);
	esp.seqno = cpu_to_be64(XFRM_SKB_CB(skb)->seq.output.low +
			    ((u64)XFRM_SKB_CB(skb)->seq.output.hi << 32));

	skb_push(skb, -skb_network_offset(skb));

	वापस esp6_output_tail(x, skb, &esp);
पूर्ण

अटल अंतरभूत पूर्णांक esp_हटाओ_trailer(काष्ठा sk_buff *skb)
अणु
	काष्ठा xfrm_state *x = xfrm_input_state(skb);
	काष्ठा xfrm_offload *xo = xfrm_offload(skb);
	काष्ठा crypto_aead *aead = x->data;
	पूर्णांक alen, hlen, elen;
	पूर्णांक padlen, trimlen;
	__wsum csumdअगरf;
	u8 nexthdr[2];
	पूर्णांक ret;

	alen = crypto_aead_authsize(aead);
	hlen = माप(काष्ठा ip_esp_hdr) + crypto_aead_ivsize(aead);
	elen = skb->len - hlen;

	अगर (xo && (xo->flags & XFRM_ESP_NO_TRAILER)) अणु
		ret = xo->proto;
		जाओ out;
	पूर्ण

	ret = skb_copy_bits(skb, skb->len - alen - 2, nexthdr, 2);
	BUG_ON(ret);

	ret = -EINVAL;
	padlen = nexthdr[0];
	अगर (padlen + 2 + alen >= elen) अणु
		net_dbg_ratelimited("ipsec esp packet is garbage padlen=%d, elen=%d\n",
				    padlen + 2, elen - alen);
		जाओ out;
	पूर्ण

	trimlen = alen + padlen + 2;
	अगर (skb->ip_summed == CHECKSUM_COMPLETE) अणु
		csumdअगरf = skb_checksum(skb, skb->len - trimlen, trimlen, 0);
		skb->csum = csum_block_sub(skb->csum, csumdअगरf,
					   skb->len - trimlen);
	पूर्ण
	pskb_trim(skb, skb->len - trimlen);

	ret = nexthdr[1];

out:
	वापस ret;
पूर्ण

पूर्णांक esp6_input_करोne2(काष्ठा sk_buff *skb, पूर्णांक err)
अणु
	काष्ठा xfrm_state *x = xfrm_input_state(skb);
	काष्ठा xfrm_offload *xo = xfrm_offload(skb);
	काष्ठा crypto_aead *aead = x->data;
	पूर्णांक hlen = माप(काष्ठा ip_esp_hdr) + crypto_aead_ivsize(aead);
	पूर्णांक hdr_len = skb_network_header_len(skb);

	अगर (!xo || !(xo->flags & CRYPTO_DONE))
		kमुक्त(ESP_SKB_CB(skb)->पंचांगp);

	अगर (unlikely(err))
		जाओ out;

	err = esp_हटाओ_trailer(skb);
	अगर (unlikely(err < 0))
		जाओ out;

	अगर (x->encap) अणु
		स्थिर काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);
		पूर्णांक offset = skb_network_offset(skb) + माप(*ip6h);
		काष्ठा xfrm_encap_पंचांगpl *encap = x->encap;
		u8 nexthdr = ip6h->nexthdr;
		__be16 frag_off, source;
		काष्ठा udphdr *uh;
		काष्ठा tcphdr *th;

		offset = ipv6_skip_exthdr(skb, offset, &nexthdr, &frag_off);
		uh = (व्योम *)(skb->data + offset);
		th = (व्योम *)(skb->data + offset);
		hdr_len += offset;

		चयन (x->encap->encap_type) अणु
		हाल TCP_ENCAP_ESPINTCP:
			source = th->source;
			अवरोध;
		हाल UDP_ENCAP_ESPINUDP:
		हाल UDP_ENCAP_ESPINUDP_NON_IKE:
			source = uh->source;
			अवरोध;
		शेष:
			WARN_ON_ONCE(1);
			err = -EINVAL;
			जाओ out;
		पूर्ण

		/*
		 * 1) अगर the NAT-T peer's IP or port changed then
		 *    advertize the change to the keying daemon.
		 *    This is an inbound SA, so just compare
		 *    SRC ports.
		 */
		अगर (!ipv6_addr_equal(&ip6h->saddr, &x->props.saddr.in6) ||
		    source != encap->encap_sport) अणु
			xfrm_address_t ipaddr;

			स_नकल(&ipaddr.a6, &ip6h->saddr.s6_addr, माप(ipaddr.a6));
			km_new_mapping(x, &ipaddr, source);

			/* XXX: perhaps add an extra
			 * policy check here, to see
			 * अगर we should allow or
			 * reject a packet from a
			 * dअगरferent source
			 * address/port.
			 */
		पूर्ण

		/*
		 * 2) ignore UDP/TCP checksums in हाल
		 *    of NAT-T in Transport Mode, or
		 *    perक्रमm other post-processing fixes
		 *    as per draft-ietf-ipsec-udp-encaps-06,
		 *    section 3.1.2
		 */
		अगर (x->props.mode == XFRM_MODE_TRANSPORT)
			skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण

	skb_postpull_rcsum(skb, skb_network_header(skb),
			   skb_network_header_len(skb));
	skb_pull_rcsum(skb, hlen);
	अगर (x->props.mode == XFRM_MODE_TUNNEL)
		skb_reset_transport_header(skb);
	अन्यथा
		skb_set_transport_header(skb, -hdr_len);

	/* RFC4303: Drop dummy packets without any error */
	अगर (err == IPPROTO_NONE)
		err = -EINVAL;

out:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(esp6_input_करोne2);

अटल व्योम esp_input_करोne(काष्ठा crypto_async_request *base, पूर्णांक err)
अणु
	काष्ठा sk_buff *skb = base->data;

	xfrm_input_resume(skb, esp6_input_करोne2(skb, err));
पूर्ण

अटल व्योम esp_input_restore_header(काष्ठा sk_buff *skb)
अणु
	esp_restore_header(skb, 0);
	__skb_pull(skb, 4);
पूर्ण

अटल व्योम esp_input_set_header(काष्ठा sk_buff *skb, __be32 *seqhi)
अणु
	काष्ठा xfrm_state *x = xfrm_input_state(skb);

	/* For ESN we move the header क्रमward by 4 bytes to
	 * accomodate the high bits.  We will move it back after
	 * decryption.
	 */
	अगर ((x->props.flags & XFRM_STATE_ESN)) अणु
		काष्ठा ip_esp_hdr *esph = skb_push(skb, 4);

		*seqhi = esph->spi;
		esph->spi = esph->seq_no;
		esph->seq_no = XFRM_SKB_CB(skb)->seq.input.hi;
	पूर्ण
पूर्ण

अटल व्योम esp_input_करोne_esn(काष्ठा crypto_async_request *base, पूर्णांक err)
अणु
	काष्ठा sk_buff *skb = base->data;

	esp_input_restore_header(skb);
	esp_input_करोne(base, err);
पूर्ण

अटल पूर्णांक esp6_input(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	काष्ठा crypto_aead *aead = x->data;
	काष्ठा aead_request *req;
	काष्ठा sk_buff *trailer;
	पूर्णांक ivlen = crypto_aead_ivsize(aead);
	पूर्णांक elen = skb->len - माप(काष्ठा ip_esp_hdr) - ivlen;
	पूर्णांक nfrags;
	पूर्णांक assoclen;
	पूर्णांक seqhilen;
	पूर्णांक ret = 0;
	व्योम *पंचांगp;
	__be32 *seqhi;
	u8 *iv;
	काष्ठा scatterlist *sg;

	अगर (!pskb_may_pull(skb, माप(काष्ठा ip_esp_hdr) + ivlen)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (elen <= 0) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	assoclen = माप(काष्ठा ip_esp_hdr);
	seqhilen = 0;

	अगर (x->props.flags & XFRM_STATE_ESN) अणु
		seqhilen += माप(__be32);
		assoclen += seqhilen;
	पूर्ण

	अगर (!skb_cloned(skb)) अणु
		अगर (!skb_is_nonlinear(skb)) अणु
			nfrags = 1;

			जाओ skip_cow;
		पूर्ण अन्यथा अगर (!skb_has_frag_list(skb)) अणु
			nfrags = skb_shinfo(skb)->nr_frags;
			nfrags++;

			जाओ skip_cow;
		पूर्ण
	पूर्ण

	nfrags = skb_cow_data(skb, 0, &trailer);
	अगर (nfrags < 0) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

skip_cow:
	ret = -ENOMEM;
	पंचांगp = esp_alloc_पंचांगp(aead, nfrags, seqhilen);
	अगर (!पंचांगp)
		जाओ out;

	ESP_SKB_CB(skb)->पंचांगp = पंचांगp;
	seqhi = esp_पंचांगp_extra(पंचांगp);
	iv = esp_पंचांगp_iv(aead, पंचांगp, seqhilen);
	req = esp_पंचांगp_req(aead, iv);
	sg = esp_req_sg(aead, req);

	esp_input_set_header(skb, seqhi);

	sg_init_table(sg, nfrags);
	ret = skb_to_sgvec(skb, sg, 0, skb->len);
	अगर (unlikely(ret < 0)) अणु
		kमुक्त(पंचांगp);
		जाओ out;
	पूर्ण

	skb->ip_summed = CHECKSUM_NONE;

	अगर ((x->props.flags & XFRM_STATE_ESN))
		aead_request_set_callback(req, 0, esp_input_करोne_esn, skb);
	अन्यथा
		aead_request_set_callback(req, 0, esp_input_करोne, skb);

	aead_request_set_crypt(req, sg, sg, elen + ivlen, iv);
	aead_request_set_ad(req, assoclen);

	ret = crypto_aead_decrypt(req);
	अगर (ret == -EINPROGRESS)
		जाओ out;

	अगर ((x->props.flags & XFRM_STATE_ESN))
		esp_input_restore_header(skb);

	ret = esp6_input_करोne2(skb, ret);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक esp6_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
		    u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	स्थिर काष्ठा ipv6hdr *iph = (स्थिर काष्ठा ipv6hdr *)skb->data;
	काष्ठा ip_esp_hdr *esph = (काष्ठा ip_esp_hdr *)(skb->data + offset);
	काष्ठा xfrm_state *x;

	अगर (type != ICMPV6_PKT_TOOBIG &&
	    type != NDISC_REसूचीECT)
		वापस 0;

	x = xfrm_state_lookup(net, skb->mark, (स्थिर xfrm_address_t *)&iph->daddr,
			      esph->spi, IPPROTO_ESP, AF_INET6);
	अगर (!x)
		वापस 0;

	अगर (type == NDISC_REसूचीECT)
		ip6_redirect(skb, net, skb->dev->अगरindex, 0,
			     sock_net_uid(net, शून्य));
	अन्यथा
		ip6_update_pmtu(skb, net, info, 0, 0, sock_net_uid(net, शून्य));
	xfrm_state_put(x);

	वापस 0;
पूर्ण

अटल व्योम esp6_destroy(काष्ठा xfrm_state *x)
अणु
	काष्ठा crypto_aead *aead = x->data;

	अगर (!aead)
		वापस;

	crypto_मुक्त_aead(aead);
पूर्ण

अटल पूर्णांक esp_init_aead(काष्ठा xfrm_state *x)
अणु
	अक्षर aead_name[CRYPTO_MAX_ALG_NAME];
	काष्ठा crypto_aead *aead;
	पूर्णांक err;

	err = -ENAMETOOLONG;
	अगर (snम_लिखो(aead_name, CRYPTO_MAX_ALG_NAME, "%s(%s)",
		     x->geniv, x->aead->alg_name) >= CRYPTO_MAX_ALG_NAME)
		जाओ error;

	aead = crypto_alloc_aead(aead_name, 0, 0);
	err = PTR_ERR(aead);
	अगर (IS_ERR(aead))
		जाओ error;

	x->data = aead;

	err = crypto_aead_setkey(aead, x->aead->alg_key,
				 (x->aead->alg_key_len + 7) / 8);
	अगर (err)
		जाओ error;

	err = crypto_aead_setauthsize(aead, x->aead->alg_icv_len / 8);
	अगर (err)
		जाओ error;

error:
	वापस err;
पूर्ण

अटल पूर्णांक esp_init_authenc(काष्ठा xfrm_state *x)
अणु
	काष्ठा crypto_aead *aead;
	काष्ठा crypto_authenc_key_param *param;
	काष्ठा rtattr *rta;
	अक्षर *key;
	अक्षर *p;
	अक्षर authenc_name[CRYPTO_MAX_ALG_NAME];
	अचिन्हित पूर्णांक keylen;
	पूर्णांक err;

	err = -EINVAL;
	अगर (!x->ealg)
		जाओ error;

	err = -ENAMETOOLONG;

	अगर ((x->props.flags & XFRM_STATE_ESN)) अणु
		अगर (snम_लिखो(authenc_name, CRYPTO_MAX_ALG_NAME,
			     "%s%sauthencesn(%s,%s)%s",
			     x->geniv ?: "", x->geniv ? "(" : "",
			     x->aalg ? x->aalg->alg_name : "digest_null",
			     x->ealg->alg_name,
			     x->geniv ? ")" : "") >= CRYPTO_MAX_ALG_NAME)
			जाओ error;
	पूर्ण अन्यथा अणु
		अगर (snम_लिखो(authenc_name, CRYPTO_MAX_ALG_NAME,
			     "%s%sauthenc(%s,%s)%s",
			     x->geniv ?: "", x->geniv ? "(" : "",
			     x->aalg ? x->aalg->alg_name : "digest_null",
			     x->ealg->alg_name,
			     x->geniv ? ")" : "") >= CRYPTO_MAX_ALG_NAME)
			जाओ error;
	पूर्ण

	aead = crypto_alloc_aead(authenc_name, 0, 0);
	err = PTR_ERR(aead);
	अगर (IS_ERR(aead))
		जाओ error;

	x->data = aead;

	keylen = (x->aalg ? (x->aalg->alg_key_len + 7) / 8 : 0) +
		 (x->ealg->alg_key_len + 7) / 8 + RTA_SPACE(माप(*param));
	err = -ENOMEM;
	key = kदो_स्मृति(keylen, GFP_KERNEL);
	अगर (!key)
		जाओ error;

	p = key;
	rta = (व्योम *)p;
	rta->rta_type = CRYPTO_AUTHENC_KEYA_PARAM;
	rta->rta_len = RTA_LENGTH(माप(*param));
	param = RTA_DATA(rta);
	p += RTA_SPACE(माप(*param));

	अगर (x->aalg) अणु
		काष्ठा xfrm_algo_desc *aalg_desc;

		स_नकल(p, x->aalg->alg_key, (x->aalg->alg_key_len + 7) / 8);
		p += (x->aalg->alg_key_len + 7) / 8;

		aalg_desc = xfrm_aalg_get_byname(x->aalg->alg_name, 0);
		BUG_ON(!aalg_desc);

		err = -EINVAL;
		अगर (aalg_desc->uinfo.auth.icv_fullbits / 8 !=
		    crypto_aead_authsize(aead)) अणु
			pr_info("ESP: %s digestsize %u != %u\n",
				x->aalg->alg_name,
				crypto_aead_authsize(aead),
				aalg_desc->uinfo.auth.icv_fullbits / 8);
			जाओ मुक्त_key;
		पूर्ण

		err = crypto_aead_setauthsize(
			aead, x->aalg->alg_trunc_len / 8);
		अगर (err)
			जाओ मुक्त_key;
	पूर्ण

	param->enckeylen = cpu_to_be32((x->ealg->alg_key_len + 7) / 8);
	स_नकल(p, x->ealg->alg_key, (x->ealg->alg_key_len + 7) / 8);

	err = crypto_aead_setkey(aead, key, keylen);

मुक्त_key:
	kमुक्त(key);

error:
	वापस err;
पूर्ण

अटल पूर्णांक esp6_init_state(काष्ठा xfrm_state *x)
अणु
	काष्ठा crypto_aead *aead;
	u32 align;
	पूर्णांक err;

	x->data = शून्य;

	अगर (x->aead)
		err = esp_init_aead(x);
	अन्यथा
		err = esp_init_authenc(x);

	अगर (err)
		जाओ error;

	aead = x->data;

	x->props.header_len = माप(काष्ठा ip_esp_hdr) +
			      crypto_aead_ivsize(aead);
	चयन (x->props.mode) अणु
	हाल XFRM_MODE_BEET:
		अगर (x->sel.family != AF_INET6)
			x->props.header_len += IPV4_BEET_PHMAXLEN +
					       (माप(काष्ठा ipv6hdr) - माप(काष्ठा iphdr));
		अवरोध;
	शेष:
	हाल XFRM_MODE_TRANSPORT:
		अवरोध;
	हाल XFRM_MODE_TUNNEL:
		x->props.header_len += माप(काष्ठा ipv6hdr);
		अवरोध;
	पूर्ण

	अगर (x->encap) अणु
		काष्ठा xfrm_encap_पंचांगpl *encap = x->encap;

		चयन (encap->encap_type) अणु
		शेष:
			err = -EINVAL;
			जाओ error;
		हाल UDP_ENCAP_ESPINUDP:
			x->props.header_len += माप(काष्ठा udphdr);
			अवरोध;
		हाल UDP_ENCAP_ESPINUDP_NON_IKE:
			x->props.header_len += माप(काष्ठा udphdr) + 2 * माप(u32);
			अवरोध;
#अगर_घोषित CONFIG_INET6_ESPINTCP
		हाल TCP_ENCAP_ESPINTCP:
			/* only the length field, TCP encap is करोne by
			 * the socket
			 */
			x->props.header_len += 2;
			अवरोध;
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	align = ALIGN(crypto_aead_blocksize(aead), 4);
	x->props.trailer_len = align + 1 + crypto_aead_authsize(aead);

error:
	वापस err;
पूर्ण

अटल पूर्णांक esp6_rcv_cb(काष्ठा sk_buff *skb, पूर्णांक err)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा xfrm_type esp6_type = अणु
	.description	= "ESP6",
	.owner		= THIS_MODULE,
	.proto		= IPPROTO_ESP,
	.flags		= XFRM_TYPE_REPLAY_PROT,
	.init_state	= esp6_init_state,
	.deकाष्ठाor	= esp6_destroy,
	.input		= esp6_input,
	.output		= esp6_output,
	.hdr_offset	= xfrm6_find_1stfragopt,
पूर्ण;

अटल काष्ठा xfrm6_protocol esp6_protocol = अणु
	.handler	=	xfrm6_rcv,
	.input_handler	=	xfrm_input,
	.cb_handler	=	esp6_rcv_cb,
	.err_handler	=	esp6_err,
	.priority	=	0,
पूर्ण;

अटल पूर्णांक __init esp6_init(व्योम)
अणु
	अगर (xfrm_रेजिस्टर_type(&esp6_type, AF_INET6) < 0) अणु
		pr_info("%s: can't add xfrm type\n", __func__);
		वापस -EAGAIN;
	पूर्ण
	अगर (xfrm6_protocol_रेजिस्टर(&esp6_protocol, IPPROTO_ESP) < 0) अणु
		pr_info("%s: can't add protocol\n", __func__);
		xfrm_unरेजिस्टर_type(&esp6_type, AF_INET6);
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास esp6_fini(व्योम)
अणु
	अगर (xfrm6_protocol_deरेजिस्टर(&esp6_protocol, IPPROTO_ESP) < 0)
		pr_info("%s: can't remove protocol\n", __func__);
	xfrm_unरेजिस्टर_type(&esp6_type, AF_INET6);
पूर्ण

module_init(esp6_init);
module_निकास(esp6_fini);

MODULE_LICENSE("GPL");
MODULE_ALIAS_XFRM_TYPE(AF_INET6, XFRM_PROTO_ESP);
