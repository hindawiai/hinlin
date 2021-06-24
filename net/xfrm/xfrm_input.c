<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xfrm_input.c
 *
 * Changes:
 * 	YOSHIFUJI Hideaki @USAGI
 * 		Split up af-specअगरic portion
 *
 */

#समावेश <linux/bottom_half.h>
#समावेश <linux/cache.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/percpu.h>
#समावेश <net/dst.h>
#समावेश <net/ip.h>
#समावेश <net/xfrm.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/ip6_tunnel.h>

#समावेश "xfrm_inout.h"

काष्ठा xfrm_trans_tasklet अणु
	काष्ठा tasklet_काष्ठा tasklet;
	काष्ठा sk_buff_head queue;
पूर्ण;

काष्ठा xfrm_trans_cb अणु
	जोड़ अणु
		काष्ठा inet_skb_parm	h4;
#अगर IS_ENABLED(CONFIG_IPV6)
		काष्ठा inet6_skb_parm	h6;
#पूर्ण_अगर
	पूर्ण header;
	पूर्णांक (*finish)(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
	काष्ठा net *net;
पूर्ण;

#घोषणा XFRM_TRANS_SKB_CB(__skb) ((काष्ठा xfrm_trans_cb *)&((__skb)->cb[0]))

अटल DEFINE_SPINLOCK(xfrm_input_afinfo_lock);
अटल काष्ठा xfrm_input_afinfo स्थिर __rcu *xfrm_input_afinfo[2][AF_INET6 + 1];

अटल काष्ठा gro_cells gro_cells;
अटल काष्ठा net_device xfrm_napi_dev;

अटल DEFINE_PER_CPU(काष्ठा xfrm_trans_tasklet, xfrm_trans_tasklet);

पूर्णांक xfrm_input_रेजिस्टर_afinfo(स्थिर काष्ठा xfrm_input_afinfo *afinfo)
अणु
	पूर्णांक err = 0;

	अगर (WARN_ON(afinfo->family > AF_INET6))
		वापस -EAFNOSUPPORT;

	spin_lock_bh(&xfrm_input_afinfo_lock);
	अगर (unlikely(xfrm_input_afinfo[afinfo->is_ipip][afinfo->family]))
		err = -EEXIST;
	अन्यथा
		rcu_assign_poपूर्णांकer(xfrm_input_afinfo[afinfo->is_ipip][afinfo->family], afinfo);
	spin_unlock_bh(&xfrm_input_afinfo_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL(xfrm_input_रेजिस्टर_afinfo);

पूर्णांक xfrm_input_unरेजिस्टर_afinfo(स्थिर काष्ठा xfrm_input_afinfo *afinfo)
अणु
	पूर्णांक err = 0;

	spin_lock_bh(&xfrm_input_afinfo_lock);
	अगर (likely(xfrm_input_afinfo[afinfo->is_ipip][afinfo->family])) अणु
		अगर (unlikely(xfrm_input_afinfo[afinfo->is_ipip][afinfo->family] != afinfo))
			err = -EINVAL;
		अन्यथा
			RCU_INIT_POINTER(xfrm_input_afinfo[afinfo->is_ipip][afinfo->family], शून्य);
	पूर्ण
	spin_unlock_bh(&xfrm_input_afinfo_lock);
	synchronize_rcu();
	वापस err;
पूर्ण
EXPORT_SYMBOL(xfrm_input_unरेजिस्टर_afinfo);

अटल स्थिर काष्ठा xfrm_input_afinfo *xfrm_input_get_afinfo(u8 family, bool is_ipip)
अणु
	स्थिर काष्ठा xfrm_input_afinfo *afinfo;

	अगर (WARN_ON_ONCE(family > AF_INET6))
		वापस शून्य;

	rcu_पढ़ो_lock();
	afinfo = rcu_dereference(xfrm_input_afinfo[is_ipip][family]);
	अगर (unlikely(!afinfo))
		rcu_पढ़ो_unlock();
	वापस afinfo;
पूर्ण

अटल पूर्णांक xfrm_rcv_cb(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक family, u8 protocol,
		       पूर्णांक err)
अणु
	bool is_ipip = (protocol == IPPROTO_IPIP || protocol == IPPROTO_IPV6);
	स्थिर काष्ठा xfrm_input_afinfo *afinfo;
	पूर्णांक ret;

	afinfo = xfrm_input_get_afinfo(family, is_ipip);
	अगर (!afinfo)
		वापस -EAFNOSUPPORT;

	ret = afinfo->callback(skb, protocol, err);
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

काष्ठा sec_path *secpath_set(काष्ठा sk_buff *skb)
अणु
	काष्ठा sec_path *sp, *पंचांगp = skb_ext_find(skb, SKB_EXT_SEC_PATH);

	sp = skb_ext_add(skb, SKB_EXT_SEC_PATH);
	अगर (!sp)
		वापस शून्य;

	अगर (पंचांगp) /* reused existing one (was COW'd अगर needed) */
		वापस sp;

	/* allocated new secpath */
	स_रखो(sp->ovec, 0, माप(sp->ovec));
	sp->olen = 0;
	sp->len = 0;

	वापस sp;
पूर्ण
EXPORT_SYMBOL(secpath_set);

/* Fetch spi and seq from ipsec header */

पूर्णांक xfrm_parse_spi(काष्ठा sk_buff *skb, u8 nexthdr, __be32 *spi, __be32 *seq)
अणु
	पूर्णांक offset, offset_seq;
	पूर्णांक hlen;

	चयन (nexthdr) अणु
	हाल IPPROTO_AH:
		hlen = माप(काष्ठा ip_auth_hdr);
		offset = दुरत्व(काष्ठा ip_auth_hdr, spi);
		offset_seq = दुरत्व(काष्ठा ip_auth_hdr, seq_no);
		अवरोध;
	हाल IPPROTO_ESP:
		hlen = माप(काष्ठा ip_esp_hdr);
		offset = दुरत्व(काष्ठा ip_esp_hdr, spi);
		offset_seq = दुरत्व(काष्ठा ip_esp_hdr, seq_no);
		अवरोध;
	हाल IPPROTO_COMP:
		अगर (!pskb_may_pull(skb, माप(काष्ठा ip_comp_hdr)))
			वापस -EINVAL;
		*spi = htonl(ntohs(*(__be16 *)(skb_transport_header(skb) + 2)));
		*seq = 0;
		वापस 0;
	शेष:
		वापस 1;
	पूर्ण

	अगर (!pskb_may_pull(skb, hlen))
		वापस -EINVAL;

	*spi = *(__be32 *)(skb_transport_header(skb) + offset);
	*seq = *(__be32 *)(skb_transport_header(skb) + offset_seq);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(xfrm_parse_spi);

अटल पूर्णांक xfrm4_हटाओ_beet_encap(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	काष्ठा iphdr *iph;
	पूर्णांक optlen = 0;
	पूर्णांक err = -EINVAL;

	अगर (unlikely(XFRM_MODE_SKB_CB(skb)->protocol == IPPROTO_BEETPH)) अणु
		काष्ठा ip_beet_phdr *ph;
		पूर्णांक phlen;

		अगर (!pskb_may_pull(skb, माप(*ph)))
			जाओ out;

		ph = (काष्ठा ip_beet_phdr *)skb->data;

		phlen = माप(*ph) + ph->padlen;
		optlen = ph->hdrlen * 8 + (IPV4_BEET_PHMAXLEN - phlen);
		अगर (optlen < 0 || optlen & 3 || optlen > 250)
			जाओ out;

		XFRM_MODE_SKB_CB(skb)->protocol = ph->nexthdr;

		अगर (!pskb_may_pull(skb, phlen))
			जाओ out;
		__skb_pull(skb, phlen);
	पूर्ण

	skb_push(skb, माप(*iph));
	skb_reset_network_header(skb);
	skb_mac_header_rebuild(skb);

	xfrm4_beet_make_header(skb);

	iph = ip_hdr(skb);

	iph->ihl += optlen / 4;
	iph->tot_len = htons(skb->len);
	iph->daddr = x->sel.daddr.a4;
	iph->saddr = x->sel.saddr.a4;
	iph->check = 0;
	iph->check = ip_fast_csum(skb_network_header(skb), iph->ihl);
	err = 0;
out:
	वापस err;
पूर्ण

अटल व्योम ipip_ecn_decapsulate(काष्ठा sk_buff *skb)
अणु
	काष्ठा iphdr *inner_iph = ipip_hdr(skb);

	अगर (INET_ECN_is_ce(XFRM_MODE_SKB_CB(skb)->tos))
		IP_ECN_set_ce(inner_iph);
पूर्ण

अटल पूर्णांक xfrm4_हटाओ_tunnel_encap(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err = -EINVAL;

	अगर (XFRM_MODE_SKB_CB(skb)->protocol != IPPROTO_IPIP)
		जाओ out;

	अगर (!pskb_may_pull(skb, माप(काष्ठा iphdr)))
		जाओ out;

	err = skb_unclone(skb, GFP_ATOMIC);
	अगर (err)
		जाओ out;

	अगर (x->props.flags & XFRM_STATE_DECAP_DSCP)
		ipv4_copy_dscp(XFRM_MODE_SKB_CB(skb)->tos, ipip_hdr(skb));
	अगर (!(x->props.flags & XFRM_STATE_NOECN))
		ipip_ecn_decapsulate(skb);

	skb_reset_network_header(skb);
	skb_mac_header_rebuild(skb);
	अगर (skb->mac_len)
		eth_hdr(skb)->h_proto = skb->protocol;

	err = 0;

out:
	वापस err;
पूर्ण

अटल व्योम ipip6_ecn_decapsulate(काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6hdr *inner_iph = ipipv6_hdr(skb);

	अगर (INET_ECN_is_ce(XFRM_MODE_SKB_CB(skb)->tos))
		IP6_ECN_set_ce(skb, inner_iph);
पूर्ण

अटल पूर्णांक xfrm6_हटाओ_tunnel_encap(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err = -EINVAL;

	अगर (XFRM_MODE_SKB_CB(skb)->protocol != IPPROTO_IPV6)
		जाओ out;
	अगर (!pskb_may_pull(skb, माप(काष्ठा ipv6hdr)))
		जाओ out;

	err = skb_unclone(skb, GFP_ATOMIC);
	अगर (err)
		जाओ out;

	अगर (x->props.flags & XFRM_STATE_DECAP_DSCP)
		ipv6_copy_dscp(ipv6_get_dsfield(ipv6_hdr(skb)),
			       ipipv6_hdr(skb));
	अगर (!(x->props.flags & XFRM_STATE_NOECN))
		ipip6_ecn_decapsulate(skb);

	skb_reset_network_header(skb);
	skb_mac_header_rebuild(skb);
	अगर (skb->mac_len)
		eth_hdr(skb)->h_proto = skb->protocol;

	err = 0;

out:
	वापस err;
पूर्ण

अटल पूर्णांक xfrm6_हटाओ_beet_encap(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6hdr *ip6h;
	पूर्णांक size = माप(काष्ठा ipv6hdr);
	पूर्णांक err;

	err = skb_cow_head(skb, size + skb->mac_len);
	अगर (err)
		जाओ out;

	__skb_push(skb, size);
	skb_reset_network_header(skb);
	skb_mac_header_rebuild(skb);

	xfrm6_beet_make_header(skb);

	ip6h = ipv6_hdr(skb);
	ip6h->payload_len = htons(skb->len - size);
	ip6h->daddr = x->sel.daddr.in6;
	ip6h->saddr = x->sel.saddr.in6;
	err = 0;
out:
	वापस err;
पूर्ण

/* Remove encapsulation header.
 *
 * The IP header will be moved over the top of the encapsulation
 * header.
 *
 * On entry, the transport header shall poपूर्णांक to where the IP header
 * should be and the network header shall be set to where the IP
 * header currently is.  skb->data shall poपूर्णांक to the start of the
 * payload.
 */
अटल पूर्णांक
xfrm_inner_mode_encap_हटाओ(काष्ठा xfrm_state *x,
			     स्थिर काष्ठा xfrm_mode *inner_mode,
			     काष्ठा sk_buff *skb)
अणु
	चयन (inner_mode->encap) अणु
	हाल XFRM_MODE_BEET:
		अगर (inner_mode->family == AF_INET)
			वापस xfrm4_हटाओ_beet_encap(x, skb);
		अगर (inner_mode->family == AF_INET6)
			वापस xfrm6_हटाओ_beet_encap(x, skb);
		अवरोध;
	हाल XFRM_MODE_TUNNEL:
		अगर (inner_mode->family == AF_INET)
			वापस xfrm4_हटाओ_tunnel_encap(x, skb);
		अगर (inner_mode->family == AF_INET6)
			वापस xfrm6_हटाओ_tunnel_encap(x, skb);
		अवरोध;
	पूर्ण

	WARN_ON_ONCE(1);
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक xfrm_prepare_input(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा xfrm_mode *inner_mode = &x->inner_mode;

	चयन (x->outer_mode.family) अणु
	हाल AF_INET:
		xfrm4_extract_header(skb);
		अवरोध;
	हाल AF_INET6:
		xfrm6_extract_header(skb);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस -EAFNOSUPPORT;
	पूर्ण

	अगर (x->sel.family == AF_UNSPEC) अणु
		inner_mode = xfrm_ip2inner_mode(x, XFRM_MODE_SKB_CB(skb)->protocol);
		अगर (!inner_mode)
			वापस -EAFNOSUPPORT;
	पूर्ण

	चयन (inner_mode->family) अणु
	हाल AF_INET:
		skb->protocol = htons(ETH_P_IP);
		अवरोध;
	हाल AF_INET6:
		skb->protocol = htons(ETH_P_IPV6);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	वापस xfrm_inner_mode_encap_हटाओ(x, inner_mode, skb);
पूर्ण

/* Remove encapsulation header.
 *
 * The IP header will be moved over the top of the encapsulation header.
 *
 * On entry, skb_transport_header() shall poपूर्णांक to where the IP header
 * should be and skb_network_header() shall be set to where the IP header
 * currently is.  skb->data shall poपूर्णांक to the start of the payload.
 */
अटल पूर्णांक xfrm4_transport_input(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ihl = skb->data - skb_transport_header(skb);

	अगर (skb->transport_header != skb->network_header) अणु
		स_हटाओ(skb_transport_header(skb),
			skb_network_header(skb), ihl);
		skb->network_header = skb->transport_header;
	पूर्ण
	ip_hdr(skb)->tot_len = htons(skb->len + ihl);
	skb_reset_transport_header(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm6_transport_input(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्णांक ihl = skb->data - skb_transport_header(skb);

	अगर (skb->transport_header != skb->network_header) अणु
		स_हटाओ(skb_transport_header(skb),
			skb_network_header(skb), ihl);
		skb->network_header = skb->transport_header;
	पूर्ण
	ipv6_hdr(skb)->payload_len = htons(skb->len + ihl -
					   माप(काष्ठा ipv6hdr));
	skb_reset_transport_header(skb);
	वापस 0;
#अन्यथा
	WARN_ON_ONCE(1);
	वापस -EAFNOSUPPORT;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक xfrm_inner_mode_input(काष्ठा xfrm_state *x,
				 स्थिर काष्ठा xfrm_mode *inner_mode,
				 काष्ठा sk_buff *skb)
अणु
	चयन (inner_mode->encap) अणु
	हाल XFRM_MODE_BEET:
	हाल XFRM_MODE_TUNNEL:
		वापस xfrm_prepare_input(x, skb);
	हाल XFRM_MODE_TRANSPORT:
		अगर (inner_mode->family == AF_INET)
			वापस xfrm4_transport_input(x, skb);
		अगर (inner_mode->family == AF_INET6)
			वापस xfrm6_transport_input(x, skb);
		अवरोध;
	हाल XFRM_MODE_ROUTEOPTIMIZATION:
		WARN_ON_ONCE(1);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक xfrm_input(काष्ठा sk_buff *skb, पूर्णांक nexthdr, __be32 spi, पूर्णांक encap_type)
अणु
	स्थिर काष्ठा xfrm_state_afinfo *afinfo;
	काष्ठा net *net = dev_net(skb->dev);
	स्थिर काष्ठा xfrm_mode *inner_mode;
	पूर्णांक err;
	__be32 seq;
	__be32 seq_hi;
	काष्ठा xfrm_state *x = शून्य;
	xfrm_address_t *daddr;
	u32 mark = skb->mark;
	अचिन्हित पूर्णांक family = AF_UNSPEC;
	पूर्णांक decaps = 0;
	पूर्णांक async = 0;
	bool xfrm_gro = false;
	bool crypto_करोne = false;
	काष्ठा xfrm_offload *xo = xfrm_offload(skb);
	काष्ठा sec_path *sp;

	अगर (encap_type < 0) अणु
		x = xfrm_input_state(skb);

		अगर (unlikely(x->km.state != XFRM_STATE_VALID)) अणु
			अगर (x->km.state == XFRM_STATE_ACQ)
				XFRM_INC_STATS(net, LINUX_MIB_XFRMACQUIREERROR);
			अन्यथा
				XFRM_INC_STATS(net,
					       LINUX_MIB_XFRMINSTATEINVALID);

			अगर (encap_type == -1)
				dev_put(skb->dev);
			जाओ drop;
		पूर्ण

		family = x->outer_mode.family;

		/* An encap_type of -1 indicates async resumption. */
		अगर (encap_type == -1) अणु
			async = 1;
			seq = XFRM_SKB_CB(skb)->seq.input.low;
			जाओ resume;
		पूर्ण

		/* encap_type < -1 indicates a GRO call. */
		encap_type = 0;
		seq = XFRM_SPI_SKB_CB(skb)->seq;

		अगर (xo && (xo->flags & CRYPTO_DONE)) अणु
			crypto_करोne = true;
			family = XFRM_SPI_SKB_CB(skb)->family;

			अगर (!(xo->status & CRYPTO_SUCCESS)) अणु
				अगर (xo->status &
				    (CRYPTO_TRANSPORT_AH_AUTH_FAILED |
				     CRYPTO_TRANSPORT_ESP_AUTH_FAILED |
				     CRYPTO_TUNNEL_AH_AUTH_FAILED |
				     CRYPTO_TUNNEL_ESP_AUTH_FAILED)) अणु

					xfrm_audit_state_icvfail(x, skb,
								 x->type->proto);
					x->stats.पूर्णांकegrity_failed++;
					XFRM_INC_STATS(net, LINUX_MIB_XFRMINSTATEPROTOERROR);
					जाओ drop;
				पूर्ण

				अगर (xo->status & CRYPTO_INVALID_PROTOCOL) अणु
					XFRM_INC_STATS(net, LINUX_MIB_XFRMINSTATEPROTOERROR);
					जाओ drop;
				पूर्ण

				XFRM_INC_STATS(net, LINUX_MIB_XFRMINBUFFERERROR);
				जाओ drop;
			पूर्ण

			अगर ((err = xfrm_parse_spi(skb, nexthdr, &spi, &seq)) != 0) अणु
				XFRM_INC_STATS(net, LINUX_MIB_XFRMINHDRERROR);
				जाओ drop;
			पूर्ण
		पूर्ण

		जाओ lock;
	पूर्ण

	family = XFRM_SPI_SKB_CB(skb)->family;

	/* अगर tunnel is present override skb->mark value with tunnel i_key */
	चयन (family) अणु
	हाल AF_INET:
		अगर (XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip4)
			mark = be32_to_cpu(XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip4->parms.i_key);
		अवरोध;
	हाल AF_INET6:
		अगर (XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip6)
			mark = be32_to_cpu(XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip6->parms.i_key);
		अवरोध;
	पूर्ण

	sp = secpath_set(skb);
	अगर (!sp) अणु
		XFRM_INC_STATS(net, LINUX_MIB_XFRMINERROR);
		जाओ drop;
	पूर्ण

	seq = 0;
	अगर (!spi && (err = xfrm_parse_spi(skb, nexthdr, &spi, &seq)) != 0) अणु
		secpath_reset(skb);
		XFRM_INC_STATS(net, LINUX_MIB_XFRMINHDRERROR);
		जाओ drop;
	पूर्ण

	daddr = (xfrm_address_t *)(skb_network_header(skb) +
				   XFRM_SPI_SKB_CB(skb)->daddroff);
	करो अणु
		sp = skb_sec_path(skb);

		अगर (sp->len == XFRM_MAX_DEPTH) अणु
			secpath_reset(skb);
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINBUFFERERROR);
			जाओ drop;
		पूर्ण

		x = xfrm_state_lookup(net, mark, daddr, spi, nexthdr, family);
		अगर (x == शून्य) अणु
			secpath_reset(skb);
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINNOSTATES);
			xfrm_audit_state_notfound(skb, family, spi, seq);
			जाओ drop;
		पूर्ण

		skb->mark = xfrm_smark_get(skb->mark, x);

		sp->xvec[sp->len++] = x;

		skb_dst_क्रमce(skb);
		अगर (!skb_dst(skb)) अणु
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINERROR);
			जाओ drop;
		पूर्ण

lock:
		spin_lock(&x->lock);

		अगर (unlikely(x->km.state != XFRM_STATE_VALID)) अणु
			अगर (x->km.state == XFRM_STATE_ACQ)
				XFRM_INC_STATS(net, LINUX_MIB_XFRMACQUIREERROR);
			अन्यथा
				XFRM_INC_STATS(net,
					       LINUX_MIB_XFRMINSTATEINVALID);
			जाओ drop_unlock;
		पूर्ण

		अगर ((x->encap ? x->encap->encap_type : 0) != encap_type) अणु
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINSTATEMISMATCH);
			जाओ drop_unlock;
		पूर्ण

		अगर (x->repl->check(x, skb, seq)) अणु
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINSTATESEQERROR);
			जाओ drop_unlock;
		पूर्ण

		अगर (xfrm_state_check_expire(x)) अणु
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINSTATEEXPIRED);
			जाओ drop_unlock;
		पूर्ण

		spin_unlock(&x->lock);

		अगर (xfrm_tunnel_check(skb, x, family)) अणु
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINSTATEMODEERROR);
			जाओ drop;
		पूर्ण

		seq_hi = htonl(xfrm_replay_seqhi(x, seq));

		XFRM_SKB_CB(skb)->seq.input.low = seq;
		XFRM_SKB_CB(skb)->seq.input.hi = seq_hi;

		dev_hold(skb->dev);

		अगर (crypto_करोne)
			nexthdr = x->type_offload->input_tail(x, skb);
		अन्यथा
			nexthdr = x->type->input(x, skb);

		अगर (nexthdr == -EINPROGRESS)
			वापस 0;
resume:
		dev_put(skb->dev);

		spin_lock(&x->lock);
		अगर (nexthdr < 0) अणु
			अगर (nexthdr == -EBADMSG) अणु
				xfrm_audit_state_icvfail(x, skb,
							 x->type->proto);
				x->stats.पूर्णांकegrity_failed++;
			पूर्ण
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINSTATEPROTOERROR);
			जाओ drop_unlock;
		पूर्ण

		/* only the first xfrm माला_लो the encap type */
		encap_type = 0;

		अगर (x->repl->recheck(x, skb, seq)) अणु
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINSTATESEQERROR);
			जाओ drop_unlock;
		पूर्ण

		x->repl->advance(x, seq);

		x->curlft.bytes += skb->len;
		x->curlft.packets++;

		spin_unlock(&x->lock);

		XFRM_MODE_SKB_CB(skb)->protocol = nexthdr;

		inner_mode = &x->inner_mode;

		अगर (x->sel.family == AF_UNSPEC) अणु
			inner_mode = xfrm_ip2inner_mode(x, XFRM_MODE_SKB_CB(skb)->protocol);
			अगर (inner_mode == शून्य) अणु
				XFRM_INC_STATS(net, LINUX_MIB_XFRMINSTATEMODEERROR);
				जाओ drop;
			पूर्ण
		पूर्ण

		अगर (xfrm_inner_mode_input(x, inner_mode, skb)) अणु
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINSTATEMODEERROR);
			जाओ drop;
		पूर्ण

		अगर (x->outer_mode.flags & XFRM_MODE_FLAG_TUNNEL) अणु
			decaps = 1;
			अवरोध;
		पूर्ण

		/*
		 * We need the inner address.  However, we only get here क्रम
		 * transport mode so the outer address is identical.
		 */
		daddr = &x->id.daddr;
		family = x->outer_mode.family;

		err = xfrm_parse_spi(skb, nexthdr, &spi, &seq);
		अगर (err < 0) अणु
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINHDRERROR);
			जाओ drop;
		पूर्ण
		crypto_करोne = false;
	पूर्ण जबतक (!err);

	err = xfrm_rcv_cb(skb, family, x->type->proto, 0);
	अगर (err)
		जाओ drop;

	nf_reset_ct(skb);

	अगर (decaps) अणु
		sp = skb_sec_path(skb);
		अगर (sp)
			sp->olen = 0;
		skb_dst_drop(skb);
		gro_cells_receive(&gro_cells, skb);
		वापस 0;
	पूर्ण अन्यथा अणु
		xo = xfrm_offload(skb);
		अगर (xo)
			xfrm_gro = xo->flags & XFRM_GRO;

		err = -EAFNOSUPPORT;
		rcu_पढ़ो_lock();
		afinfo = xfrm_state_afinfo_get_rcu(x->inner_mode.family);
		अगर (likely(afinfo))
			err = afinfo->transport_finish(skb, xfrm_gro || async);
		rcu_पढ़ो_unlock();
		अगर (xfrm_gro) अणु
			sp = skb_sec_path(skb);
			अगर (sp)
				sp->olen = 0;
			skb_dst_drop(skb);
			gro_cells_receive(&gro_cells, skb);
			वापस err;
		पूर्ण

		वापस err;
	पूर्ण

drop_unlock:
	spin_unlock(&x->lock);
drop:
	xfrm_rcv_cb(skb, family, x && x->type ? x->type->proto : nexthdr, -1);
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(xfrm_input);

पूर्णांक xfrm_input_resume(काष्ठा sk_buff *skb, पूर्णांक nexthdr)
अणु
	वापस xfrm_input(skb, nexthdr, 0, -1);
पूर्ण
EXPORT_SYMBOL(xfrm_input_resume);

अटल व्योम xfrm_trans_reinject(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा xfrm_trans_tasklet *trans = from_tasklet(trans, t, tasklet);
	काष्ठा sk_buff_head queue;
	काष्ठा sk_buff *skb;

	__skb_queue_head_init(&queue);
	skb_queue_splice_init(&trans->queue, &queue);

	जबतक ((skb = __skb_dequeue(&queue)))
		XFRM_TRANS_SKB_CB(skb)->finish(XFRM_TRANS_SKB_CB(skb)->net,
					       शून्य, skb);
पूर्ण

पूर्णांक xfrm_trans_queue_net(काष्ठा net *net, काष्ठा sk_buff *skb,
			 पूर्णांक (*finish)(काष्ठा net *, काष्ठा sock *,
				       काष्ठा sk_buff *))
अणु
	काष्ठा xfrm_trans_tasklet *trans;

	trans = this_cpu_ptr(&xfrm_trans_tasklet);

	अगर (skb_queue_len(&trans->queue) >= netdev_max_backlog)
		वापस -ENOBUFS;

	BUILD_BUG_ON(माप(काष्ठा xfrm_trans_cb) > माप(skb->cb));

	XFRM_TRANS_SKB_CB(skb)->finish = finish;
	XFRM_TRANS_SKB_CB(skb)->net = net;
	__skb_queue_tail(&trans->queue, skb);
	tasklet_schedule(&trans->tasklet);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(xfrm_trans_queue_net);

पूर्णांक xfrm_trans_queue(काष्ठा sk_buff *skb,
		     पूर्णांक (*finish)(काष्ठा net *, काष्ठा sock *,
				   काष्ठा sk_buff *))
अणु
	वापस xfrm_trans_queue_net(dev_net(skb->dev), skb, finish);
पूर्ण
EXPORT_SYMBOL(xfrm_trans_queue);

व्योम __init xfrm_input_init(व्योम)
अणु
	पूर्णांक err;
	पूर्णांक i;

	init_dummy_netdev(&xfrm_napi_dev);
	err = gro_cells_init(&gro_cells, &xfrm_napi_dev);
	अगर (err)
		gro_cells.cells = शून्य;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा xfrm_trans_tasklet *trans;

		trans = &per_cpu(xfrm_trans_tasklet, i);
		__skb_queue_head_init(&trans->queue);
		tasklet_setup(&trans->tasklet, xfrm_trans_reinject);
	पूर्ण
पूर्ण
