<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IPV6 GSO/GRO offload support
 * Linux INET implementation
 *
 * Copyright (C) 2016 secunet Security Networks AG
 * Author: Steffen Klनिश्चित <steffen.klनिश्चित@secunet.com>
 *
 * ESP GRO support
 */

#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <net/protocol.h>
#समावेश <crypto/aead.h>
#समावेश <crypto/authenc.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <net/ip.h>
#समावेश <net/xfrm.h>
#समावेश <net/esp.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <net/ip6_route.h>
#समावेश <net/ipv6.h>
#समावेश <linux/icmpv6.h>

अटल __u16 esp6_nexthdr_esp_offset(काष्ठा ipv6hdr *ipv6_hdr, पूर्णांक nhlen)
अणु
	पूर्णांक off = माप(काष्ठा ipv6hdr);
	काष्ठा ipv6_opt_hdr *exthdr;

	अगर (likely(ipv6_hdr->nexthdr == NEXTHDR_ESP))
		वापस दुरत्व(काष्ठा ipv6hdr, nexthdr);

	जबतक (off < nhlen) अणु
		exthdr = (व्योम *)ipv6_hdr + off;
		अगर (exthdr->nexthdr == NEXTHDR_ESP)
			वापस off;

		off += ipv6_optlen(exthdr);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *esp6_gro_receive(काष्ठा list_head *head,
					काष्ठा sk_buff *skb)
अणु
	पूर्णांक offset = skb_gro_offset(skb);
	काष्ठा xfrm_offload *xo;
	काष्ठा xfrm_state *x;
	__be32 seq;
	__be32 spi;
	पूर्णांक nhoff;
	पूर्णांक err;

	अगर (!pskb_pull(skb, offset))
		वापस शून्य;

	अगर ((err = xfrm_parse_spi(skb, IPPROTO_ESP, &spi, &seq)) != 0)
		जाओ out;

	xo = xfrm_offload(skb);
	अगर (!xo || !(xo->flags & CRYPTO_DONE)) अणु
		काष्ठा sec_path *sp = secpath_set(skb);

		अगर (!sp)
			जाओ out;

		अगर (sp->len == XFRM_MAX_DEPTH)
			जाओ out_reset;

		x = xfrm_state_lookup(dev_net(skb->dev), skb->mark,
				      (xfrm_address_t *)&ipv6_hdr(skb)->daddr,
				      spi, IPPROTO_ESP, AF_INET6);
		अगर (!x)
			जाओ out_reset;

		skb->mark = xfrm_smark_get(skb->mark, x);

		sp->xvec[sp->len++] = x;
		sp->olen++;

		xo = xfrm_offload(skb);
		अगर (!xo)
			जाओ out_reset;
	पूर्ण

	xo->flags |= XFRM_GRO;

	nhoff = esp6_nexthdr_esp_offset(ipv6_hdr(skb), offset);
	अगर (!nhoff)
		जाओ out;

	IP6CB(skb)->nhoff = nhoff;
	XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip6 = शून्य;
	XFRM_SPI_SKB_CB(skb)->family = AF_INET6;
	XFRM_SPI_SKB_CB(skb)->daddroff = दुरत्व(काष्ठा ipv6hdr, daddr);
	XFRM_SPI_SKB_CB(skb)->seq = seq;

	/* We करोn't need to handle errors from xfrm_input, it करोes all
	 * the error handling and मुक्तs the resources on error. */
	xfrm_input(skb, IPPROTO_ESP, spi, -2);

	वापस ERR_PTR(-EINPROGRESS);
out_reset:
	secpath_reset(skb);
out:
	skb_push(skb, offset);
	NAPI_GRO_CB(skb)->same_flow = 0;
	NAPI_GRO_CB(skb)->flush = 1;

	वापस शून्य;
पूर्ण

अटल व्योम esp6_gso_encap(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	काष्ठा ip_esp_hdr *esph;
	काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	काष्ठा xfrm_offload *xo = xfrm_offload(skb);
	u8 proto = iph->nexthdr;

	skb_push(skb, -skb_network_offset(skb));

	अगर (x->outer_mode.encap == XFRM_MODE_TRANSPORT) अणु
		__be16 frag;

		ipv6_skip_exthdr(skb, माप(काष्ठा ipv6hdr), &proto, &frag);
	पूर्ण

	esph = ip_esp_hdr(skb);
	*skb_mac_header(skb) = IPPROTO_ESP;

	esph->spi = x->id.spi;
	esph->seq_no = htonl(XFRM_SKB_CB(skb)->seq.output.low);

	xo->proto = proto;
पूर्ण

अटल काष्ठा sk_buff *xfrm6_tunnel_gso_segment(काष्ठा xfrm_state *x,
						काष्ठा sk_buff *skb,
						netdev_features_t features)
अणु
	__skb_push(skb, skb->mac_len);
	वापस skb_mac_gso_segment(skb, features);
पूर्ण

अटल काष्ठा sk_buff *xfrm6_transport_gso_segment(काष्ठा xfrm_state *x,
						   काष्ठा sk_buff *skb,
						   netdev_features_t features)
अणु
	स्थिर काष्ठा net_offload *ops;
	काष्ठा sk_buff *segs = ERR_PTR(-EINVAL);
	काष्ठा xfrm_offload *xo = xfrm_offload(skb);

	skb->transport_header += x->props.header_len;
	ops = rcu_dereference(inet6_offloads[xo->proto]);
	अगर (likely(ops && ops->callbacks.gso_segment))
		segs = ops->callbacks.gso_segment(skb, features);

	वापस segs;
पूर्ण

अटल काष्ठा sk_buff *xfrm6_beet_gso_segment(काष्ठा xfrm_state *x,
					      काष्ठा sk_buff *skb,
					      netdev_features_t features)
अणु
	काष्ठा xfrm_offload *xo = xfrm_offload(skb);
	काष्ठा sk_buff *segs = ERR_PTR(-EINVAL);
	स्थिर काष्ठा net_offload *ops;
	u8 proto = xo->proto;

	skb->transport_header += x->props.header_len;

	अगर (x->sel.family != AF_INET6) अणु
		skb->transport_header -=
			(माप(काष्ठा ipv6hdr) - माप(काष्ठा iphdr));

		अगर (proto == IPPROTO_BEETPH) अणु
			काष्ठा ip_beet_phdr *ph =
				(काष्ठा ip_beet_phdr *)skb->data;

			skb->transport_header += ph->hdrlen * 8;
			proto = ph->nexthdr;
		पूर्ण अन्यथा अणु
			skb->transport_header -= IPV4_BEET_PHMAXLEN;
		पूर्ण

		अगर (proto == IPPROTO_TCP)
			skb_shinfo(skb)->gso_type |= SKB_GSO_TCPV6;
	पूर्ण अन्यथा अणु
		__be16 frag;

		skb->transport_header +=
			ipv6_skip_exthdr(skb, 0, &proto, &frag);
	पूर्ण

	__skb_pull(skb, skb_transport_offset(skb));
	ops = rcu_dereference(inet6_offloads[proto]);
	अगर (likely(ops && ops->callbacks.gso_segment))
		segs = ops->callbacks.gso_segment(skb, features);

	वापस segs;
पूर्ण

अटल काष्ठा sk_buff *xfrm6_outer_mode_gso_segment(काष्ठा xfrm_state *x,
						    काष्ठा sk_buff *skb,
						    netdev_features_t features)
अणु
	चयन (x->outer_mode.encap) अणु
	हाल XFRM_MODE_TUNNEL:
		वापस xfrm6_tunnel_gso_segment(x, skb, features);
	हाल XFRM_MODE_TRANSPORT:
		वापस xfrm6_transport_gso_segment(x, skb, features);
	हाल XFRM_MODE_BEET:
		वापस xfrm6_beet_gso_segment(x, skb, features);
	पूर्ण

	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल काष्ठा sk_buff *esp6_gso_segment(काष्ठा sk_buff *skb,
				        netdev_features_t features)
अणु
	काष्ठा xfrm_state *x;
	काष्ठा ip_esp_hdr *esph;
	काष्ठा crypto_aead *aead;
	netdev_features_t esp_features = features;
	काष्ठा xfrm_offload *xo = xfrm_offload(skb);
	काष्ठा sec_path *sp;

	अगर (!xo)
		वापस ERR_PTR(-EINVAL);

	अगर (!(skb_shinfo(skb)->gso_type & SKB_GSO_ESP))
		वापस ERR_PTR(-EINVAL);

	sp = skb_sec_path(skb);
	x = sp->xvec[sp->len - 1];
	aead = x->data;
	esph = ip_esp_hdr(skb);

	अगर (esph->spi != x->id.spi)
		वापस ERR_PTR(-EINVAL);

	अगर (!pskb_may_pull(skb, माप(*esph) + crypto_aead_ivsize(aead)))
		वापस ERR_PTR(-EINVAL);

	__skb_pull(skb, माप(*esph) + crypto_aead_ivsize(aead));

	skb->encap_hdr_csum = 1;

	अगर (!(features & NETIF_F_HW_ESP) || x->xso.dev != skb->dev)
		esp_features = features & ~(NETIF_F_SG | NETIF_F_CSUM_MASK |
					    NETIF_F_SCTP_CRC);
	अन्यथा अगर (!(features & NETIF_F_HW_ESP_TX_CSUM))
		esp_features = features & ~(NETIF_F_CSUM_MASK |
					    NETIF_F_SCTP_CRC);

	xo->flags |= XFRM_GSO_SEGMENT;

	वापस xfrm6_outer_mode_gso_segment(x, skb, esp_features);
पूर्ण

अटल पूर्णांक esp6_input_tail(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	काष्ठा crypto_aead *aead = x->data;
	काष्ठा xfrm_offload *xo = xfrm_offload(skb);

	अगर (!pskb_may_pull(skb, माप(काष्ठा ip_esp_hdr) + crypto_aead_ivsize(aead)))
		वापस -EINVAL;

	अगर (!(xo->flags & CRYPTO_DONE))
		skb->ip_summed = CHECKSUM_NONE;

	वापस esp6_input_करोne2(skb, 0);
पूर्ण

अटल पूर्णांक esp6_xmit(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb,  netdev_features_t features)
अणु
	पूर्णांक len;
	पूर्णांक err;
	पूर्णांक alen;
	पूर्णांक blksize;
	काष्ठा xfrm_offload *xo;
	काष्ठा crypto_aead *aead;
	काष्ठा esp_info esp;
	bool hw_offload = true;
	__u32 seq;

	esp.inplace = true;

	xo = xfrm_offload(skb);

	अगर (!xo)
		वापस -EINVAL;

	अगर (!(features & NETIF_F_HW_ESP) || x->xso.dev != skb->dev) अणु
		xo->flags |= CRYPTO_FALLBACK;
		hw_offload = false;
	पूर्ण

	esp.proto = xo->proto;

	/* skb is pure payload to encrypt */

	aead = x->data;
	alen = crypto_aead_authsize(aead);

	esp.tfclen = 0;
	/* XXX: Add support क्रम tfc padding here. */

	blksize = ALIGN(crypto_aead_blocksize(aead), 4);
	esp.clen = ALIGN(skb->len + 2 + esp.tfclen, blksize);
	esp.plen = esp.clen - skb->len - esp.tfclen;
	esp.tailen = esp.tfclen + esp.plen + alen;

	अगर (!hw_offload || !skb_is_gso(skb)) अणु
		esp.nfrags = esp6_output_head(x, skb, &esp);
		अगर (esp.nfrags < 0)
			वापस esp.nfrags;
	पूर्ण

	seq = xo->seq.low;

	esp.esph = ip_esp_hdr(skb);
	esp.esph->spi = x->id.spi;

	skb_push(skb, -skb_network_offset(skb));

	अगर (xo->flags & XFRM_GSO_SEGMENT) अणु
		esp.esph->seq_no = htonl(seq);

		अगर (!skb_is_gso(skb))
			xo->seq.low++;
		अन्यथा
			xo->seq.low += skb_shinfo(skb)->gso_segs;
	पूर्ण

	esp.seqno = cpu_to_be64(xo->seq.low + ((u64)xo->seq.hi << 32));

	len = skb->len - माप(काष्ठा ipv6hdr);
	अगर (len > IPV6_MAXPLEN)
		len = 0;

	ipv6_hdr(skb)->payload_len = htons(len);

	अगर (hw_offload) अणु
		अगर (!skb_ext_add(skb, SKB_EXT_SEC_PATH))
			वापस -ENOMEM;

		xo = xfrm_offload(skb);
		अगर (!xo)
			वापस -EINVAL;

		xo->flags |= XFRM_XMIT;
		वापस 0;
	पूर्ण

	err = esp6_output_tail(x, skb, &esp);
	अगर (err)
		वापस err;

	secpath_reset(skb);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_offload esp6_offload = अणु
	.callbacks = अणु
		.gro_receive = esp6_gro_receive,
		.gso_segment = esp6_gso_segment,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा xfrm_type_offload esp6_type_offload = अणु
	.description	= "ESP6 OFFLOAD",
	.owner		= THIS_MODULE,
	.proto	     	= IPPROTO_ESP,
	.input_tail	= esp6_input_tail,
	.xmit		= esp6_xmit,
	.encap		= esp6_gso_encap,
पूर्ण;

अटल पूर्णांक __init esp6_offload_init(व्योम)
अणु
	अगर (xfrm_रेजिस्टर_type_offload(&esp6_type_offload, AF_INET6) < 0) अणु
		pr_info("%s: can't add xfrm type offload\n", __func__);
		वापस -EAGAIN;
	पूर्ण

	वापस inet6_add_offload(&esp6_offload, IPPROTO_ESP);
पूर्ण

अटल व्योम __निकास esp6_offload_निकास(व्योम)
अणु
	xfrm_unरेजिस्टर_type_offload(&esp6_type_offload, AF_INET6);
	inet6_del_offload(&esp6_offload, IPPROTO_ESP);
पूर्ण

module_init(esp6_offload_init);
module_निकास(esp6_offload_निकास);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Steffen Klassert <steffen.klassert@secunet.com>");
MODULE_ALIAS_XFRM_OFFLOAD_TYPE(AF_INET6, XFRM_PROTO_ESP);
MODULE_DESCRIPTION("IPV6 GSO/GRO offload support");
