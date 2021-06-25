<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा pr_fmt(fmt) "IPsec: " fmt

#समावेश <crypto/algapi.h>
#समावेश <crypto/hash.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <net/ip.h>
#समावेश <net/xfrm.h>
#समावेश <net/ah.h>
#समावेश <linux/crypto.h>
#समावेश <linux/pfkeyv2.h>
#समावेश <linux/scatterlist.h>
#समावेश <net/icmp.h>
#समावेश <net/protocol.h>

काष्ठा ah_skb_cb अणु
	काष्ठा xfrm_skb_cb xfrm;
	व्योम *पंचांगp;
पूर्ण;

#घोषणा AH_SKB_CB(__skb) ((काष्ठा ah_skb_cb *)&((__skb)->cb[0]))

अटल व्योम *ah_alloc_पंचांगp(काष्ठा crypto_ahash *ahash, पूर्णांक nfrags,
			  अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक len;

	len = size + crypto_ahash_digestsize(ahash) +
	      (crypto_ahash_alignmask(ahash) &
	       ~(crypto_tfm_ctx_alignment() - 1));

	len = ALIGN(len, crypto_tfm_ctx_alignment());

	len += माप(काष्ठा ahash_request) + crypto_ahash_reqsize(ahash);
	len = ALIGN(len, __alignof__(काष्ठा scatterlist));

	len += माप(काष्ठा scatterlist) * nfrags;

	वापस kदो_स्मृति(len, GFP_ATOMIC);
पूर्ण

अटल अंतरभूत u8 *ah_पंचांगp_auth(व्योम *पंचांगp, अचिन्हित पूर्णांक offset)
अणु
	वापस पंचांगp + offset;
पूर्ण

अटल अंतरभूत u8 *ah_पंचांगp_icv(काष्ठा crypto_ahash *ahash, व्योम *पंचांगp,
			     अचिन्हित पूर्णांक offset)
अणु
	वापस PTR_ALIGN((u8 *)पंचांगp + offset, crypto_ahash_alignmask(ahash) + 1);
पूर्ण

अटल अंतरभूत काष्ठा ahash_request *ah_पंचांगp_req(काष्ठा crypto_ahash *ahash,
					       u8 *icv)
अणु
	काष्ठा ahash_request *req;

	req = (व्योम *)PTR_ALIGN(icv + crypto_ahash_digestsize(ahash),
				crypto_tfm_ctx_alignment());

	ahash_request_set_tfm(req, ahash);

	वापस req;
पूर्ण

अटल अंतरभूत काष्ठा scatterlist *ah_req_sg(काष्ठा crypto_ahash *ahash,
					     काष्ठा ahash_request *req)
अणु
	वापस (व्योम *)ALIGN((अचिन्हित दीर्घ)(req + 1) +
			     crypto_ahash_reqsize(ahash),
			     __alignof__(काष्ठा scatterlist));
पूर्ण

/* Clear mutable options and find final destination to substitute
 * पूर्णांकo IP header क्रम icv calculation. Options are alपढ़ोy checked
 * क्रम validity, so paranoia is not required. */

अटल पूर्णांक ip_clear_mutable_options(स्थिर काष्ठा iphdr *iph, __be32 *daddr)
अणु
	अचिन्हित अक्षर *optptr = (अचिन्हित अक्षर *)(iph+1);
	पूर्णांक  l = iph->ihl*4 - माप(काष्ठा iphdr);
	पूर्णांक  optlen;

	जबतक (l > 0) अणु
		चयन (*optptr) अणु
		हाल IPOPT_END:
			वापस 0;
		हाल IPOPT_NOOP:
			l--;
			optptr++;
			जारी;
		पूर्ण
		optlen = optptr[1];
		अगर (optlen<2 || optlen>l)
			वापस -EINVAL;
		चयन (*optptr) अणु
		हाल IPOPT_SEC:
		हाल 0x85:	/* Some "Extended Security" crap. */
		हाल IPOPT_CIPSO:
		हाल IPOPT_RA:
		हाल 0x80|21:	/* RFC1770 */
			अवरोध;
		हाल IPOPT_LSRR:
		हाल IPOPT_SSRR:
			अगर (optlen < 6)
				वापस -EINVAL;
			स_नकल(daddr, optptr+optlen-4, 4);
			fallthrough;
		शेष:
			स_रखो(optptr, 0, optlen);
		पूर्ण
		l -= optlen;
		optptr += optlen;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ah_output_करोne(काष्ठा crypto_async_request *base, पूर्णांक err)
अणु
	u8 *icv;
	काष्ठा iphdr *iph;
	काष्ठा sk_buff *skb = base->data;
	काष्ठा xfrm_state *x = skb_dst(skb)->xfrm;
	काष्ठा ah_data *ahp = x->data;
	काष्ठा iphdr *top_iph = ip_hdr(skb);
	काष्ठा ip_auth_hdr *ah = ip_auth_hdr(skb);
	पूर्णांक ihl = ip_hdrlen(skb);

	iph = AH_SKB_CB(skb)->पंचांगp;
	icv = ah_पंचांगp_icv(ahp->ahash, iph, ihl);
	स_नकल(ah->auth_data, icv, ahp->icv_trunc_len);

	top_iph->tos = iph->tos;
	top_iph->ttl = iph->ttl;
	top_iph->frag_off = iph->frag_off;
	अगर (top_iph->ihl != 5) अणु
		top_iph->daddr = iph->daddr;
		स_नकल(top_iph+1, iph+1, top_iph->ihl*4 - माप(काष्ठा iphdr));
	पूर्ण

	kमुक्त(AH_SKB_CB(skb)->पंचांगp);
	xfrm_output_resume(skb->sk, skb, err);
पूर्ण

अटल पूर्णांक ah_output(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;
	पूर्णांक nfrags;
	पूर्णांक ihl;
	u8 *icv;
	काष्ठा sk_buff *trailer;
	काष्ठा crypto_ahash *ahash;
	काष्ठा ahash_request *req;
	काष्ठा scatterlist *sg;
	काष्ठा iphdr *iph, *top_iph;
	काष्ठा ip_auth_hdr *ah;
	काष्ठा ah_data *ahp;
	पूर्णांक seqhi_len = 0;
	__be32 *seqhi;
	पूर्णांक sglists = 0;
	काष्ठा scatterlist *seqhisg;

	ahp = x->data;
	ahash = ahp->ahash;

	अगर ((err = skb_cow_data(skb, 0, &trailer)) < 0)
		जाओ out;
	nfrags = err;

	skb_push(skb, -skb_network_offset(skb));
	ah = ip_auth_hdr(skb);
	ihl = ip_hdrlen(skb);

	अगर (x->props.flags & XFRM_STATE_ESN) अणु
		sglists = 1;
		seqhi_len = माप(*seqhi);
	पूर्ण
	err = -ENOMEM;
	iph = ah_alloc_पंचांगp(ahash, nfrags + sglists, ihl + seqhi_len);
	अगर (!iph)
		जाओ out;
	seqhi = (__be32 *)((अक्षर *)iph + ihl);
	icv = ah_पंचांगp_icv(ahash, seqhi, seqhi_len);
	req = ah_पंचांगp_req(ahash, icv);
	sg = ah_req_sg(ahash, req);
	seqhisg = sg + nfrags;

	स_रखो(ah->auth_data, 0, ahp->icv_trunc_len);

	top_iph = ip_hdr(skb);

	iph->tos = top_iph->tos;
	iph->ttl = top_iph->ttl;
	iph->frag_off = top_iph->frag_off;

	अगर (top_iph->ihl != 5) अणु
		iph->daddr = top_iph->daddr;
		स_नकल(iph+1, top_iph+1, top_iph->ihl*4 - माप(काष्ठा iphdr));
		err = ip_clear_mutable_options(top_iph, &top_iph->daddr);
		अगर (err)
			जाओ out_मुक्त;
	पूर्ण

	ah->nexthdr = *skb_mac_header(skb);
	*skb_mac_header(skb) = IPPROTO_AH;

	top_iph->tos = 0;
	top_iph->tot_len = htons(skb->len);
	top_iph->frag_off = 0;
	top_iph->ttl = 0;
	top_iph->check = 0;

	अगर (x->props.flags & XFRM_STATE_ALIGN4)
		ah->hdrlen  = (XFRM_ALIGN4(माप(*ah) + ahp->icv_trunc_len) >> 2) - 2;
	अन्यथा
		ah->hdrlen  = (XFRM_ALIGN8(माप(*ah) + ahp->icv_trunc_len) >> 2) - 2;

	ah->reserved = 0;
	ah->spi = x->id.spi;
	ah->seq_no = htonl(XFRM_SKB_CB(skb)->seq.output.low);

	sg_init_table(sg, nfrags + sglists);
	err = skb_to_sgvec_nomark(skb, sg, 0, skb->len);
	अगर (unlikely(err < 0))
		जाओ out_मुक्त;

	अगर (x->props.flags & XFRM_STATE_ESN) अणु
		/* Attach seqhi sg right after packet payload */
		*seqhi = htonl(XFRM_SKB_CB(skb)->seq.output.hi);
		sg_set_buf(seqhisg, seqhi, seqhi_len);
	पूर्ण
	ahash_request_set_crypt(req, sg, icv, skb->len + seqhi_len);
	ahash_request_set_callback(req, 0, ah_output_करोne, skb);

	AH_SKB_CB(skb)->पंचांगp = iph;

	err = crypto_ahash_digest(req);
	अगर (err) अणु
		अगर (err == -EINPROGRESS)
			जाओ out;

		अगर (err == -ENOSPC)
			err = NET_XMIT_DROP;
		जाओ out_मुक्त;
	पूर्ण

	स_नकल(ah->auth_data, icv, ahp->icv_trunc_len);

	top_iph->tos = iph->tos;
	top_iph->ttl = iph->ttl;
	top_iph->frag_off = iph->frag_off;
	अगर (top_iph->ihl != 5) अणु
		top_iph->daddr = iph->daddr;
		स_नकल(top_iph+1, iph+1, top_iph->ihl*4 - माप(काष्ठा iphdr));
	पूर्ण

out_मुक्त:
	kमुक्त(iph);
out:
	वापस err;
पूर्ण

अटल व्योम ah_input_करोne(काष्ठा crypto_async_request *base, पूर्णांक err)
अणु
	u8 *auth_data;
	u8 *icv;
	काष्ठा iphdr *work_iph;
	काष्ठा sk_buff *skb = base->data;
	काष्ठा xfrm_state *x = xfrm_input_state(skb);
	काष्ठा ah_data *ahp = x->data;
	काष्ठा ip_auth_hdr *ah = ip_auth_hdr(skb);
	पूर्णांक ihl = ip_hdrlen(skb);
	पूर्णांक ah_hlen = (ah->hdrlen + 2) << 2;

	अगर (err)
		जाओ out;

	work_iph = AH_SKB_CB(skb)->पंचांगp;
	auth_data = ah_पंचांगp_auth(work_iph, ihl);
	icv = ah_पंचांगp_icv(ahp->ahash, auth_data, ahp->icv_trunc_len);

	err = crypto_memneq(icv, auth_data, ahp->icv_trunc_len) ? -EBADMSG : 0;
	अगर (err)
		जाओ out;

	err = ah->nexthdr;

	skb->network_header += ah_hlen;
	स_नकल(skb_network_header(skb), work_iph, ihl);
	__skb_pull(skb, ah_hlen + ihl);

	अगर (x->props.mode == XFRM_MODE_TUNNEL)
		skb_reset_transport_header(skb);
	अन्यथा
		skb_set_transport_header(skb, -ihl);
out:
	kमुक्त(AH_SKB_CB(skb)->पंचांगp);
	xfrm_input_resume(skb, err);
पूर्ण

अटल पूर्णांक ah_input(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ah_hlen;
	पूर्णांक ihl;
	पूर्णांक nexthdr;
	पूर्णांक nfrags;
	u8 *auth_data;
	u8 *icv;
	काष्ठा sk_buff *trailer;
	काष्ठा crypto_ahash *ahash;
	काष्ठा ahash_request *req;
	काष्ठा scatterlist *sg;
	काष्ठा iphdr *iph, *work_iph;
	काष्ठा ip_auth_hdr *ah;
	काष्ठा ah_data *ahp;
	पूर्णांक err = -ENOMEM;
	पूर्णांक seqhi_len = 0;
	__be32 *seqhi;
	पूर्णांक sglists = 0;
	काष्ठा scatterlist *seqhisg;

	अगर (!pskb_may_pull(skb, माप(*ah)))
		जाओ out;

	ah = (काष्ठा ip_auth_hdr *)skb->data;
	ahp = x->data;
	ahash = ahp->ahash;

	nexthdr = ah->nexthdr;
	ah_hlen = (ah->hdrlen + 2) << 2;

	अगर (x->props.flags & XFRM_STATE_ALIGN4) अणु
		अगर (ah_hlen != XFRM_ALIGN4(माप(*ah) + ahp->icv_full_len) &&
		    ah_hlen != XFRM_ALIGN4(माप(*ah) + ahp->icv_trunc_len))
			जाओ out;
	पूर्ण अन्यथा अणु
		अगर (ah_hlen != XFRM_ALIGN8(माप(*ah) + ahp->icv_full_len) &&
		    ah_hlen != XFRM_ALIGN8(माप(*ah) + ahp->icv_trunc_len))
			जाओ out;
	पूर्ण

	अगर (!pskb_may_pull(skb, ah_hlen))
		जाओ out;

	/* We are going to _हटाओ_ AH header to keep sockets happy,
	 * so... Later this can change. */
	अगर (skb_unclone(skb, GFP_ATOMIC))
		जाओ out;

	skb->ip_summed = CHECKSUM_NONE;


	अगर ((err = skb_cow_data(skb, 0, &trailer)) < 0)
		जाओ out;
	nfrags = err;

	ah = (काष्ठा ip_auth_hdr *)skb->data;
	iph = ip_hdr(skb);
	ihl = ip_hdrlen(skb);

	अगर (x->props.flags & XFRM_STATE_ESN) अणु
		sglists = 1;
		seqhi_len = माप(*seqhi);
	पूर्ण

	work_iph = ah_alloc_पंचांगp(ahash, nfrags + sglists, ihl +
				ahp->icv_trunc_len + seqhi_len);
	अगर (!work_iph) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	seqhi = (__be32 *)((अक्षर *)work_iph + ihl);
	auth_data = ah_पंचांगp_auth(seqhi, seqhi_len);
	icv = ah_पंचांगp_icv(ahash, auth_data, ahp->icv_trunc_len);
	req = ah_पंचांगp_req(ahash, icv);
	sg = ah_req_sg(ahash, req);
	seqhisg = sg + nfrags;

	स_नकल(work_iph, iph, ihl);
	स_नकल(auth_data, ah->auth_data, ahp->icv_trunc_len);
	स_रखो(ah->auth_data, 0, ahp->icv_trunc_len);

	iph->ttl = 0;
	iph->tos = 0;
	iph->frag_off = 0;
	iph->check = 0;
	अगर (ihl > माप(*iph)) अणु
		__be32 dummy;
		err = ip_clear_mutable_options(iph, &dummy);
		अगर (err)
			जाओ out_मुक्त;
	पूर्ण

	skb_push(skb, ihl);

	sg_init_table(sg, nfrags + sglists);
	err = skb_to_sgvec_nomark(skb, sg, 0, skb->len);
	अगर (unlikely(err < 0))
		जाओ out_मुक्त;

	अगर (x->props.flags & XFRM_STATE_ESN) अणु
		/* Attach seqhi sg right after packet payload */
		*seqhi = XFRM_SKB_CB(skb)->seq.input.hi;
		sg_set_buf(seqhisg, seqhi, seqhi_len);
	पूर्ण
	ahash_request_set_crypt(req, sg, icv, skb->len + seqhi_len);
	ahash_request_set_callback(req, 0, ah_input_करोne, skb);

	AH_SKB_CB(skb)->पंचांगp = work_iph;

	err = crypto_ahash_digest(req);
	अगर (err) अणु
		अगर (err == -EINPROGRESS)
			जाओ out;

		जाओ out_मुक्त;
	पूर्ण

	err = crypto_memneq(icv, auth_data, ahp->icv_trunc_len) ? -EBADMSG : 0;
	अगर (err)
		जाओ out_मुक्त;

	skb->network_header += ah_hlen;
	स_नकल(skb_network_header(skb), work_iph, ihl);
	__skb_pull(skb, ah_hlen + ihl);
	अगर (x->props.mode == XFRM_MODE_TUNNEL)
		skb_reset_transport_header(skb);
	अन्यथा
		skb_set_transport_header(skb, -ihl);

	err = nexthdr;

out_मुक्त:
	kमुक्त (work_iph);
out:
	वापस err;
पूर्ण

अटल पूर्णांक ah4_err(काष्ठा sk_buff *skb, u32 info)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	स्थिर काष्ठा iphdr *iph = (स्थिर काष्ठा iphdr *)skb->data;
	काष्ठा ip_auth_hdr *ah = (काष्ठा ip_auth_hdr *)(skb->data+(iph->ihl<<2));
	काष्ठा xfrm_state *x;

	चयन (icmp_hdr(skb)->type) अणु
	हाल ICMP_DEST_UNREACH:
		अगर (icmp_hdr(skb)->code != ICMP_FRAG_NEEDED)
			वापस 0;
	हाल ICMP_REसूचीECT:
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	x = xfrm_state_lookup(net, skb->mark, (स्थिर xfrm_address_t *)&iph->daddr,
			      ah->spi, IPPROTO_AH, AF_INET);
	अगर (!x)
		वापस 0;

	अगर (icmp_hdr(skb)->type == ICMP_DEST_UNREACH)
		ipv4_update_pmtu(skb, net, info, 0, IPPROTO_AH);
	अन्यथा
		ipv4_redirect(skb, net, 0, IPPROTO_AH);
	xfrm_state_put(x);

	वापस 0;
पूर्ण

अटल पूर्णांक ah_init_state(काष्ठा xfrm_state *x)
अणु
	काष्ठा ah_data *ahp = शून्य;
	काष्ठा xfrm_algo_desc *aalg_desc;
	काष्ठा crypto_ahash *ahash;

	अगर (!x->aalg)
		जाओ error;

	अगर (x->encap)
		जाओ error;

	ahp = kzalloc(माप(*ahp), GFP_KERNEL);
	अगर (!ahp)
		वापस -ENOMEM;

	ahash = crypto_alloc_ahash(x->aalg->alg_name, 0, 0);
	अगर (IS_ERR(ahash))
		जाओ error;

	ahp->ahash = ahash;
	अगर (crypto_ahash_setkey(ahash, x->aalg->alg_key,
				(x->aalg->alg_key_len + 7) / 8))
		जाओ error;

	/*
	 * Lookup the algorithm description मुख्यtained by xfrm_algo,
	 * verअगरy crypto transक्रमm properties, and store inक्रमmation
	 * we need क्रम AH processing.  This lookup cannot fail here
	 * after a successful crypto_alloc_ahash().
	 */
	aalg_desc = xfrm_aalg_get_byname(x->aalg->alg_name, 0);
	BUG_ON(!aalg_desc);

	अगर (aalg_desc->uinfo.auth.icv_fullbits/8 !=
	    crypto_ahash_digestsize(ahash)) अणु
		pr_info("%s: %s digestsize %u != %hu\n",
			__func__, x->aalg->alg_name,
			crypto_ahash_digestsize(ahash),
			aalg_desc->uinfo.auth.icv_fullbits / 8);
		जाओ error;
	पूर्ण

	ahp->icv_full_len = aalg_desc->uinfo.auth.icv_fullbits/8;
	ahp->icv_trunc_len = x->aalg->alg_trunc_len/8;

	अगर (x->props.flags & XFRM_STATE_ALIGN4)
		x->props.header_len = XFRM_ALIGN4(माप(काष्ठा ip_auth_hdr) +
						  ahp->icv_trunc_len);
	अन्यथा
		x->props.header_len = XFRM_ALIGN8(माप(काष्ठा ip_auth_hdr) +
						  ahp->icv_trunc_len);
	अगर (x->props.mode == XFRM_MODE_TUNNEL)
		x->props.header_len += माप(काष्ठा iphdr);
	x->data = ahp;

	वापस 0;

error:
	अगर (ahp) अणु
		crypto_मुक्त_ahash(ahp->ahash);
		kमुक्त(ahp);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम ah_destroy(काष्ठा xfrm_state *x)
अणु
	काष्ठा ah_data *ahp = x->data;

	अगर (!ahp)
		वापस;

	crypto_मुक्त_ahash(ahp->ahash);
	kमुक्त(ahp);
पूर्ण

अटल पूर्णांक ah4_rcv_cb(काष्ठा sk_buff *skb, पूर्णांक err)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा xfrm_type ah_type =
अणु
	.description	= "AH4",
	.owner		= THIS_MODULE,
	.proto	     	= IPPROTO_AH,
	.flags		= XFRM_TYPE_REPLAY_PROT,
	.init_state	= ah_init_state,
	.deकाष्ठाor	= ah_destroy,
	.input		= ah_input,
	.output		= ah_output
पूर्ण;

अटल काष्ठा xfrm4_protocol ah4_protocol = अणु
	.handler	=	xfrm4_rcv,
	.input_handler	=	xfrm_input,
	.cb_handler	=	ah4_rcv_cb,
	.err_handler	=	ah4_err,
	.priority	=	0,
पूर्ण;

अटल पूर्णांक __init ah4_init(व्योम)
अणु
	अगर (xfrm_रेजिस्टर_type(&ah_type, AF_INET) < 0) अणु
		pr_info("%s: can't add xfrm type\n", __func__);
		वापस -EAGAIN;
	पूर्ण
	अगर (xfrm4_protocol_रेजिस्टर(&ah4_protocol, IPPROTO_AH) < 0) अणु
		pr_info("%s: can't add protocol\n", __func__);
		xfrm_unरेजिस्टर_type(&ah_type, AF_INET);
		वापस -EAGAIN;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास ah4_fini(व्योम)
अणु
	अगर (xfrm4_protocol_deरेजिस्टर(&ah4_protocol, IPPROTO_AH) < 0)
		pr_info("%s: can't remove protocol\n", __func__);
	xfrm_unरेजिस्टर_type(&ah_type, AF_INET);
पूर्ण

module_init(ah4_init);
module_निकास(ah4_fini);
MODULE_LICENSE("GPL");
MODULE_ALIAS_XFRM_TYPE(AF_INET, XFRM_PROTO_AH);
