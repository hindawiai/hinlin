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
 *	This file is derived from net/ipv4/ah.c.
 */

#घोषणा pr_fmt(fmt) "IPv6: " fmt

#समावेश <crypto/algapi.h>
#समावेश <crypto/hash.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <net/ip.h>
#समावेश <net/ah.h>
#समावेश <linux/crypto.h>
#समावेश <linux/pfkeyv2.h>
#समावेश <linux/माला.स>
#समावेश <linux/scatterlist.h>
#समावेश <net/ip6_route.h>
#समावेश <net/icmp.h>
#समावेश <net/ipv6.h>
#समावेश <net/protocol.h>
#समावेश <net/xfrm.h>

#घोषणा IPV6HDR_BASELEN 8

काष्ठा पंचांगp_ext अणु
#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
		काष्ठा in6_addr saddr;
#पूर्ण_अगर
		काष्ठा in6_addr daddr;
		अक्षर hdrs[];
पूर्ण;

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

अटल अंतरभूत काष्ठा पंचांगp_ext *ah_पंचांगp_ext(व्योम *base)
अणु
	वापस base + IPV6HDR_BASELEN;
पूर्ण

अटल अंतरभूत u8 *ah_पंचांगp_auth(u8 *पंचांगp, अचिन्हित पूर्णांक offset)
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

अटल bool zero_out_mutable_opts(काष्ठा ipv6_opt_hdr *opthdr)
अणु
	u8 *opt = (u8 *)opthdr;
	पूर्णांक len = ipv6_optlen(opthdr);
	पूर्णांक off = 0;
	पूर्णांक optlen = 0;

	off += 2;
	len -= 2;

	जबतक (len > 0) अणु

		चयन (opt[off]) अणु

		हाल IPV6_TLV_PAD1:
			optlen = 1;
			अवरोध;
		शेष:
			अगर (len < 2)
				जाओ bad;
			optlen = opt[off+1]+2;
			अगर (len < optlen)
				जाओ bad;
			अगर (opt[off] & 0x20)
				स_रखो(&opt[off+2], 0, opt[off+1]);
			अवरोध;
		पूर्ण

		off += optlen;
		len -= optlen;
	पूर्ण
	अगर (len == 0)
		वापस true;

bad:
	वापस false;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
/**
 *	ipv6_rearrange_destopt - rearrange IPv6 destination options header
 *	@iph: IPv6 header
 *	@destopt: destionation options header
 */
अटल व्योम ipv6_rearrange_destopt(काष्ठा ipv6hdr *iph, काष्ठा ipv6_opt_hdr *destopt)
अणु
	u8 *opt = (u8 *)destopt;
	पूर्णांक len = ipv6_optlen(destopt);
	पूर्णांक off = 0;
	पूर्णांक optlen = 0;

	off += 2;
	len -= 2;

	जबतक (len > 0) अणु

		चयन (opt[off]) अणु

		हाल IPV6_TLV_PAD1:
			optlen = 1;
			अवरोध;
		शेष:
			अगर (len < 2)
				जाओ bad;
			optlen = opt[off+1]+2;
			अगर (len < optlen)
				जाओ bad;

			/* Rearrange the source address in @iph and the
			 * addresses in home address option क्रम final source.
			 * See 11.3.2 of RFC 3775 क्रम details.
			 */
			अगर (opt[off] == IPV6_TLV_HAO) अणु
				काष्ठा in6_addr final_addr;
				काष्ठा ipv6_destopt_hao *hao;

				hao = (काष्ठा ipv6_destopt_hao *)&opt[off];
				अगर (hao->length != माप(hao->addr)) अणु
					net_warn_ratelimited("destopt hao: invalid header length: %u\n",
							     hao->length);
					जाओ bad;
				पूर्ण
				final_addr = hao->addr;
				hao->addr = iph->saddr;
				iph->saddr = final_addr;
			पूर्ण
			अवरोध;
		पूर्ण

		off += optlen;
		len -= optlen;
	पूर्ण
	/* Note: ok अगर len == 0 */
bad:
	वापस;
पूर्ण
#अन्यथा
अटल व्योम ipv6_rearrange_destopt(काष्ठा ipv6hdr *iph, काष्ठा ipv6_opt_hdr *destopt) अणुपूर्ण
#पूर्ण_अगर

/**
 *	ipv6_rearrange_rthdr - rearrange IPv6 routing header
 *	@iph: IPv6 header
 *	@rthdr: routing header
 *
 *	Rearrange the destination address in @iph and the addresses in @rthdr
 *	so that they appear in the order they will at the final destination.
 *	See Appendix A2 of RFC 2402 क्रम details.
 */
अटल व्योम ipv6_rearrange_rthdr(काष्ठा ipv6hdr *iph, काष्ठा ipv6_rt_hdr *rthdr)
अणु
	पूर्णांक segments, segments_left;
	काष्ठा in6_addr *addrs;
	काष्ठा in6_addr final_addr;

	segments_left = rthdr->segments_left;
	अगर (segments_left == 0)
		वापस;
	rthdr->segments_left = 0;

	/* The value of rthdr->hdrlen has been verअगरied either by the प्रणाली
	 * call अगर it is locally generated, or by ipv6_rthdr_rcv() क्रम incoming
	 * packets.  So we can assume that it is even and that segments is
	 * greater than or equal to segments_left.
	 *
	 * For the same reason we can assume that this option is of type 0.
	 */
	segments = rthdr->hdrlen >> 1;

	addrs = ((काष्ठा rt0_hdr *)rthdr)->addr;
	final_addr = addrs[segments - 1];

	addrs += segments - segments_left;
	स_हटाओ(addrs + 1, addrs, (segments_left - 1) * माप(*addrs));

	addrs[0] = iph->daddr;
	iph->daddr = final_addr;
पूर्ण

अटल पूर्णांक ipv6_clear_mutable_options(काष्ठा ipv6hdr *iph, पूर्णांक len, पूर्णांक dir)
अणु
	जोड़ अणु
		काष्ठा ipv6hdr *iph;
		काष्ठा ipv6_opt_hdr *opth;
		काष्ठा ipv6_rt_hdr *rth;
		अक्षर *raw;
	पूर्ण exthdr = अणु .iph = iph पूर्ण;
	अक्षर *end = exthdr.raw + len;
	पूर्णांक nexthdr = iph->nexthdr;

	exthdr.iph++;

	जबतक (exthdr.raw < end) अणु
		चयन (nexthdr) अणु
		हाल NEXTHDR_DEST:
			अगर (dir == XFRM_POLICY_OUT)
				ipv6_rearrange_destopt(iph, exthdr.opth);
			fallthrough;
		हाल NEXTHDR_HOP:
			अगर (!zero_out_mutable_opts(exthdr.opth)) अणु
				net_dbg_ratelimited("overrun %sopts\n",
						    nexthdr == NEXTHDR_HOP ?
						    "hop" : "dest");
				वापस -EINVAL;
			पूर्ण
			अवरोध;

		हाल NEXTHDR_ROUTING:
			ipv6_rearrange_rthdr(iph, exthdr.rth);
			अवरोध;

		शेष:
			वापस 0;
		पूर्ण

		nexthdr = exthdr.opth->nexthdr;
		exthdr.raw += ipv6_optlen(exthdr.opth);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ah6_output_करोne(काष्ठा crypto_async_request *base, पूर्णांक err)
अणु
	पूर्णांक extlen;
	u8 *iph_base;
	u8 *icv;
	काष्ठा sk_buff *skb = base->data;
	काष्ठा xfrm_state *x = skb_dst(skb)->xfrm;
	काष्ठा ah_data *ahp = x->data;
	काष्ठा ipv6hdr *top_iph = ipv6_hdr(skb);
	काष्ठा ip_auth_hdr *ah = ip_auth_hdr(skb);
	काष्ठा पंचांगp_ext *iph_ext;

	extlen = skb_network_header_len(skb) - माप(काष्ठा ipv6hdr);
	अगर (extlen)
		extlen += माप(*iph_ext);

	iph_base = AH_SKB_CB(skb)->पंचांगp;
	iph_ext = ah_पंचांगp_ext(iph_base);
	icv = ah_पंचांगp_icv(ahp->ahash, iph_ext, extlen);

	स_नकल(ah->auth_data, icv, ahp->icv_trunc_len);
	स_नकल(top_iph, iph_base, IPV6HDR_BASELEN);

	अगर (extlen) अणु
#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
		स_नकल(&top_iph->saddr, iph_ext, extlen);
#अन्यथा
		स_नकल(&top_iph->daddr, iph_ext, extlen);
#पूर्ण_अगर
	पूर्ण

	kमुक्त(AH_SKB_CB(skb)->पंचांगp);
	xfrm_output_resume(skb->sk, skb, err);
पूर्ण

अटल पूर्णांक ah6_output(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;
	पूर्णांक nfrags;
	पूर्णांक extlen;
	u8 *iph_base;
	u8 *icv;
	u8 nexthdr;
	काष्ठा sk_buff *trailer;
	काष्ठा crypto_ahash *ahash;
	काष्ठा ahash_request *req;
	काष्ठा scatterlist *sg;
	काष्ठा ipv6hdr *top_iph;
	काष्ठा ip_auth_hdr *ah;
	काष्ठा ah_data *ahp;
	काष्ठा पंचांगp_ext *iph_ext;
	पूर्णांक seqhi_len = 0;
	__be32 *seqhi;
	पूर्णांक sglists = 0;
	काष्ठा scatterlist *seqhisg;

	ahp = x->data;
	ahash = ahp->ahash;

	err = skb_cow_data(skb, 0, &trailer);
	अगर (err < 0)
		जाओ out;
	nfrags = err;

	skb_push(skb, -skb_network_offset(skb));
	extlen = skb_network_header_len(skb) - माप(काष्ठा ipv6hdr);
	अगर (extlen)
		extlen += माप(*iph_ext);

	अगर (x->props.flags & XFRM_STATE_ESN) अणु
		sglists = 1;
		seqhi_len = माप(*seqhi);
	पूर्ण
	err = -ENOMEM;
	iph_base = ah_alloc_पंचांगp(ahash, nfrags + sglists, IPV6HDR_BASELEN +
				extlen + seqhi_len);
	अगर (!iph_base)
		जाओ out;

	iph_ext = ah_पंचांगp_ext(iph_base);
	seqhi = (__be32 *)((अक्षर *)iph_ext + extlen);
	icv = ah_पंचांगp_icv(ahash, seqhi, seqhi_len);
	req = ah_पंचांगp_req(ahash, icv);
	sg = ah_req_sg(ahash, req);
	seqhisg = sg + nfrags;

	ah = ip_auth_hdr(skb);
	स_रखो(ah->auth_data, 0, ahp->icv_trunc_len);

	top_iph = ipv6_hdr(skb);
	top_iph->payload_len = htons(skb->len - माप(*top_iph));

	nexthdr = *skb_mac_header(skb);
	*skb_mac_header(skb) = IPPROTO_AH;

	/* When there are no extension headers, we only need to save the first
	 * 8 bytes of the base IP header.
	 */
	स_नकल(iph_base, top_iph, IPV6HDR_BASELEN);

	अगर (extlen) अणु
#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
		स_नकल(iph_ext, &top_iph->saddr, extlen);
#अन्यथा
		स_नकल(iph_ext, &top_iph->daddr, extlen);
#पूर्ण_अगर
		err = ipv6_clear_mutable_options(top_iph,
						 extlen - माप(*iph_ext) +
						 माप(*top_iph),
						 XFRM_POLICY_OUT);
		अगर (err)
			जाओ out_मुक्त;
	पूर्ण

	ah->nexthdr = nexthdr;

	top_iph->priority    = 0;
	top_iph->flow_lbl[0] = 0;
	top_iph->flow_lbl[1] = 0;
	top_iph->flow_lbl[2] = 0;
	top_iph->hop_limit   = 0;

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
	ahash_request_set_callback(req, 0, ah6_output_करोne, skb);

	AH_SKB_CB(skb)->पंचांगp = iph_base;

	err = crypto_ahash_digest(req);
	अगर (err) अणु
		अगर (err == -EINPROGRESS)
			जाओ out;

		अगर (err == -ENOSPC)
			err = NET_XMIT_DROP;
		जाओ out_मुक्त;
	पूर्ण

	स_नकल(ah->auth_data, icv, ahp->icv_trunc_len);
	स_नकल(top_iph, iph_base, IPV6HDR_BASELEN);

	अगर (extlen) अणु
#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
		स_नकल(&top_iph->saddr, iph_ext, extlen);
#अन्यथा
		स_नकल(&top_iph->daddr, iph_ext, extlen);
#पूर्ण_अगर
	पूर्ण

out_मुक्त:
	kमुक्त(iph_base);
out:
	वापस err;
पूर्ण

अटल व्योम ah6_input_करोne(काष्ठा crypto_async_request *base, पूर्णांक err)
अणु
	u8 *auth_data;
	u8 *icv;
	u8 *work_iph;
	काष्ठा sk_buff *skb = base->data;
	काष्ठा xfrm_state *x = xfrm_input_state(skb);
	काष्ठा ah_data *ahp = x->data;
	काष्ठा ip_auth_hdr *ah = ip_auth_hdr(skb);
	पूर्णांक hdr_len = skb_network_header_len(skb);
	पूर्णांक ah_hlen = ipv6_authlen(ah);

	अगर (err)
		जाओ out;

	work_iph = AH_SKB_CB(skb)->पंचांगp;
	auth_data = ah_पंचांगp_auth(work_iph, hdr_len);
	icv = ah_पंचांगp_icv(ahp->ahash, auth_data, ahp->icv_trunc_len);

	err = crypto_memneq(icv, auth_data, ahp->icv_trunc_len) ? -EBADMSG : 0;
	अगर (err)
		जाओ out;

	err = ah->nexthdr;

	skb->network_header += ah_hlen;
	स_नकल(skb_network_header(skb), work_iph, hdr_len);
	__skb_pull(skb, ah_hlen + hdr_len);
	अगर (x->props.mode == XFRM_MODE_TUNNEL)
		skb_reset_transport_header(skb);
	अन्यथा
		skb_set_transport_header(skb, -hdr_len);
out:
	kमुक्त(AH_SKB_CB(skb)->पंचांगp);
	xfrm_input_resume(skb, err);
पूर्ण



अटल पूर्णांक ah6_input(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	/*
	 * Beक्रमe process AH
	 * [IPv6][Ext1][Ext2][AH][Dest][Payload]
	 * |<-------------->| hdr_len
	 *
	 * To erase AH:
	 * Keeping copy of cleared headers. After AH processing,
	 * Moving the poपूर्णांकer of skb->network_header by using skb_pull as दीर्घ
	 * as AH header length. Then copy back the copy as दीर्घ as hdr_len
	 * If destination header following AH exists, copy it पूर्णांकo after [Ext2].
	 *
	 * |<>|[IPv6][Ext1][Ext2][Dest][Payload]
	 * There is offset of AH beक्रमe IPv6 header after the process.
	 */

	u8 *auth_data;
	u8 *icv;
	u8 *work_iph;
	काष्ठा sk_buff *trailer;
	काष्ठा crypto_ahash *ahash;
	काष्ठा ahash_request *req;
	काष्ठा scatterlist *sg;
	काष्ठा ip_auth_hdr *ah;
	काष्ठा ipv6hdr *ip6h;
	काष्ठा ah_data *ahp;
	u16 hdr_len;
	u16 ah_hlen;
	पूर्णांक nexthdr;
	पूर्णांक nfrags;
	पूर्णांक err = -ENOMEM;
	पूर्णांक seqhi_len = 0;
	__be32 *seqhi;
	पूर्णांक sglists = 0;
	काष्ठा scatterlist *seqhisg;

	अगर (!pskb_may_pull(skb, माप(काष्ठा ip_auth_hdr)))
		जाओ out;

	/* We are going to _हटाओ_ AH header to keep sockets happy,
	 * so... Later this can change. */
	अगर (skb_unclone(skb, GFP_ATOMIC))
		जाओ out;

	skb->ip_summed = CHECKSUM_NONE;

	hdr_len = skb_network_header_len(skb);
	ah = (काष्ठा ip_auth_hdr *)skb->data;
	ahp = x->data;
	ahash = ahp->ahash;

	nexthdr = ah->nexthdr;
	ah_hlen = ipv6_authlen(ah);

	अगर (ah_hlen != XFRM_ALIGN8(माप(*ah) + ahp->icv_full_len) &&
	    ah_hlen != XFRM_ALIGN8(माप(*ah) + ahp->icv_trunc_len))
		जाओ out;

	अगर (!pskb_may_pull(skb, ah_hlen))
		जाओ out;

	err = skb_cow_data(skb, 0, &trailer);
	अगर (err < 0)
		जाओ out;
	nfrags = err;

	ah = (काष्ठा ip_auth_hdr *)skb->data;
	ip6h = ipv6_hdr(skb);

	skb_push(skb, hdr_len);

	अगर (x->props.flags & XFRM_STATE_ESN) अणु
		sglists = 1;
		seqhi_len = माप(*seqhi);
	पूर्ण

	work_iph = ah_alloc_पंचांगp(ahash, nfrags + sglists, hdr_len +
				ahp->icv_trunc_len + seqhi_len);
	अगर (!work_iph) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	auth_data = ah_पंचांगp_auth((u8 *)work_iph, hdr_len);
	seqhi = (__be32 *)(auth_data + ahp->icv_trunc_len);
	icv = ah_पंचांगp_icv(ahash, seqhi, seqhi_len);
	req = ah_पंचांगp_req(ahash, icv);
	sg = ah_req_sg(ahash, req);
	seqhisg = sg + nfrags;

	स_नकल(work_iph, ip6h, hdr_len);
	स_नकल(auth_data, ah->auth_data, ahp->icv_trunc_len);
	स_रखो(ah->auth_data, 0, ahp->icv_trunc_len);

	err = ipv6_clear_mutable_options(ip6h, hdr_len, XFRM_POLICY_IN);
	अगर (err)
		जाओ out_मुक्त;

	ip6h->priority    = 0;
	ip6h->flow_lbl[0] = 0;
	ip6h->flow_lbl[1] = 0;
	ip6h->flow_lbl[2] = 0;
	ip6h->hop_limit   = 0;

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
	ahash_request_set_callback(req, 0, ah6_input_करोne, skb);

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
	स_नकल(skb_network_header(skb), work_iph, hdr_len);
	__skb_pull(skb, ah_hlen + hdr_len);

	अगर (x->props.mode == XFRM_MODE_TUNNEL)
		skb_reset_transport_header(skb);
	अन्यथा
		skb_set_transport_header(skb, -hdr_len);

	err = nexthdr;

out_मुक्त:
	kमुक्त(work_iph);
out:
	वापस err;
पूर्ण

अटल पूर्णांक ah6_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
		   u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा ipv6hdr *iph = (काष्ठा ipv6hdr *)skb->data;
	काष्ठा ip_auth_hdr *ah = (काष्ठा ip_auth_hdr *)(skb->data+offset);
	काष्ठा xfrm_state *x;

	अगर (type != ICMPV6_PKT_TOOBIG &&
	    type != NDISC_REसूचीECT)
		वापस 0;

	x = xfrm_state_lookup(net, skb->mark, (xfrm_address_t *)&iph->daddr, ah->spi, IPPROTO_AH, AF_INET6);
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

अटल पूर्णांक ah6_init_state(काष्ठा xfrm_state *x)
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
	 * after a successful crypto_alloc_hash().
	 */
	aalg_desc = xfrm_aalg_get_byname(x->aalg->alg_name, 0);
	BUG_ON(!aalg_desc);

	अगर (aalg_desc->uinfo.auth.icv_fullbits/8 !=
	    crypto_ahash_digestsize(ahash)) अणु
		pr_info("AH: %s digestsize %u != %u\n",
			x->aalg->alg_name, crypto_ahash_digestsize(ahash),
			aalg_desc->uinfo.auth.icv_fullbits/8);
		जाओ error;
	पूर्ण

	ahp->icv_full_len = aalg_desc->uinfo.auth.icv_fullbits/8;
	ahp->icv_trunc_len = x->aalg->alg_trunc_len/8;

	x->props.header_len = XFRM_ALIGN8(माप(काष्ठा ip_auth_hdr) +
					  ahp->icv_trunc_len);
	चयन (x->props.mode) अणु
	हाल XFRM_MODE_BEET:
	हाल XFRM_MODE_TRANSPORT:
		अवरोध;
	हाल XFRM_MODE_TUNNEL:
		x->props.header_len += माप(काष्ठा ipv6hdr);
		अवरोध;
	शेष:
		जाओ error;
	पूर्ण
	x->data = ahp;

	वापस 0;

error:
	अगर (ahp) अणु
		crypto_मुक्त_ahash(ahp->ahash);
		kमुक्त(ahp);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम ah6_destroy(काष्ठा xfrm_state *x)
अणु
	काष्ठा ah_data *ahp = x->data;

	अगर (!ahp)
		वापस;

	crypto_मुक्त_ahash(ahp->ahash);
	kमुक्त(ahp);
पूर्ण

अटल पूर्णांक ah6_rcv_cb(काष्ठा sk_buff *skb, पूर्णांक err)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा xfrm_type ah6_type = अणु
	.description	= "AH6",
	.owner		= THIS_MODULE,
	.proto		= IPPROTO_AH,
	.flags		= XFRM_TYPE_REPLAY_PROT,
	.init_state	= ah6_init_state,
	.deकाष्ठाor	= ah6_destroy,
	.input		= ah6_input,
	.output		= ah6_output,
	.hdr_offset	= xfrm6_find_1stfragopt,
पूर्ण;

अटल काष्ठा xfrm6_protocol ah6_protocol = अणु
	.handler	=	xfrm6_rcv,
	.input_handler	=	xfrm_input,
	.cb_handler	=	ah6_rcv_cb,
	.err_handler	=	ah6_err,
	.priority	=	0,
पूर्ण;

अटल पूर्णांक __init ah6_init(व्योम)
अणु
	अगर (xfrm_रेजिस्टर_type(&ah6_type, AF_INET6) < 0) अणु
		pr_info("%s: can't add xfrm type\n", __func__);
		वापस -EAGAIN;
	पूर्ण

	अगर (xfrm6_protocol_रेजिस्टर(&ah6_protocol, IPPROTO_AH) < 0) अणु
		pr_info("%s: can't add protocol\n", __func__);
		xfrm_unरेजिस्टर_type(&ah6_type, AF_INET6);
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास ah6_fini(व्योम)
अणु
	अगर (xfrm6_protocol_deरेजिस्टर(&ah6_protocol, IPPROTO_AH) < 0)
		pr_info("%s: can't remove protocol\n", __func__);

	xfrm_unरेजिस्टर_type(&ah6_type, AF_INET6);
पूर्ण

module_init(ah6_init);
module_निकास(ah6_fini);

MODULE_LICENSE("GPL");
MODULE_ALIAS_XFRM_TYPE(AF_INET6, XFRM_PROTO_AH);
