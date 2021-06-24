<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008-2009 Patrick McHardy <kaber@trash.net>
 * Copyright (c) 2016 Pablo Neira Ayuso <pablo@netfilter.org>
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_offload.h>
/* For layer 4 checksum field offset. */
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <net/sctp/checksum.h>

अटल bool nft_payload_rebuild_vlan_hdr(स्थिर काष्ठा sk_buff *skb, पूर्णांक mac_off,
					 काष्ठा vlan_ethhdr *veth)
अणु
	अगर (skb_copy_bits(skb, mac_off, veth, ETH_HLEN))
		वापस false;

	veth->h_vlan_proto = skb->vlan_proto;
	veth->h_vlan_TCI = htons(skb_vlan_tag_get(skb));
	veth->h_vlan_encapsulated_proto = skb->protocol;

	वापस true;
पूर्ण

/* add vlan header पूर्णांकo the user buffer क्रम अगर tag was हटाओd by offloads */
अटल bool
nft_payload_copy_vlan(u32 *d, स्थिर काष्ठा sk_buff *skb, u8 offset, u8 len)
अणु
	पूर्णांक mac_off = skb_mac_header(skb) - skb->data;
	u8 *vlanh, *dst_u8 = (u8 *) d;
	काष्ठा vlan_ethhdr veth;
	u8 vlan_hlen = 0;

	अगर ((skb->protocol == htons(ETH_P_8021AD) ||
	     skb->protocol == htons(ETH_P_8021Q)) &&
	    offset >= VLAN_ETH_HLEN && offset < VLAN_ETH_HLEN + VLAN_HLEN)
		vlan_hlen += VLAN_HLEN;

	vlanh = (u8 *) &veth;
	अगर (offset < VLAN_ETH_HLEN + vlan_hlen) अणु
		u8 ethlen = len;

		अगर (vlan_hlen &&
		    skb_copy_bits(skb, mac_off, &veth, VLAN_ETH_HLEN) < 0)
			वापस false;
		अन्यथा अगर (!nft_payload_rebuild_vlan_hdr(skb, mac_off, &veth))
			वापस false;

		अगर (offset + len > VLAN_ETH_HLEN + vlan_hlen)
			ethlen -= offset + len - VLAN_ETH_HLEN + vlan_hlen;

		स_नकल(dst_u8, vlanh + offset - vlan_hlen, ethlen);

		len -= ethlen;
		अगर (len == 0)
			वापस true;

		dst_u8 += ethlen;
		offset = ETH_HLEN + vlan_hlen;
	पूर्ण अन्यथा अणु
		offset -= VLAN_HLEN + vlan_hlen;
	पूर्ण

	वापस skb_copy_bits(skb, offset + mac_off, dst_u8, len) == 0;
पूर्ण

व्योम nft_payload_eval(स्थिर काष्ठा nft_expr *expr,
		      काष्ठा nft_regs *regs,
		      स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_payload *priv = nft_expr_priv(expr);
	स्थिर काष्ठा sk_buff *skb = pkt->skb;
	u32 *dest = &regs->data[priv->dreg];
	पूर्णांक offset;

	अगर (priv->len % NFT_REG32_SIZE)
		dest[priv->len / NFT_REG32_SIZE] = 0;

	चयन (priv->base) अणु
	हाल NFT_PAYLOAD_LL_HEADER:
		अगर (!skb_mac_header_was_set(skb))
			जाओ err;

		अगर (skb_vlan_tag_present(skb)) अणु
			अगर (!nft_payload_copy_vlan(dest, skb,
						   priv->offset, priv->len))
				जाओ err;
			वापस;
		पूर्ण
		offset = skb_mac_header(skb) - skb->data;
		अवरोध;
	हाल NFT_PAYLOAD_NETWORK_HEADER:
		offset = skb_network_offset(skb);
		अवरोध;
	हाल NFT_PAYLOAD_TRANSPORT_HEADER:
		अगर (!pkt->tprot_set)
			जाओ err;
		offset = pkt->xt.thoff;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	offset += priv->offset;

	अगर (skb_copy_bits(skb, offset, dest, priv->len) < 0)
		जाओ err;
	वापस;
err:
	regs->verdict.code = NFT_BREAK;
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_payload_policy[NFTA_PAYLOAD_MAX + 1] = अणु
	[NFTA_PAYLOAD_SREG]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_PAYLOAD_DREG]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_PAYLOAD_BASE]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_PAYLOAD_OFFSET]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_PAYLOAD_LEN]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_PAYLOAD_CSUM_TYPE]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_PAYLOAD_CSUM_OFFSET]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_PAYLOAD_CSUM_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_payload_init(स्थिर काष्ठा nft_ctx *ctx,
			    स्थिर काष्ठा nft_expr *expr,
			    स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_payload *priv = nft_expr_priv(expr);

	priv->base   = ntohl(nla_get_be32(tb[NFTA_PAYLOAD_BASE]));
	priv->offset = ntohl(nla_get_be32(tb[NFTA_PAYLOAD_OFFSET]));
	priv->len    = ntohl(nla_get_be32(tb[NFTA_PAYLOAD_LEN]));

	वापस nft_parse_रेजिस्टर_store(ctx, tb[NFTA_PAYLOAD_DREG],
					&priv->dreg, शून्य, NFT_DATA_VALUE,
					priv->len);
पूर्ण

अटल पूर्णांक nft_payload_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_payload *priv = nft_expr_priv(expr);

	अगर (nft_dump_रेजिस्टर(skb, NFTA_PAYLOAD_DREG, priv->dreg) ||
	    nla_put_be32(skb, NFTA_PAYLOAD_BASE, htonl(priv->base)) ||
	    nla_put_be32(skb, NFTA_PAYLOAD_OFFSET, htonl(priv->offset)) ||
	    nla_put_be32(skb, NFTA_PAYLOAD_LEN, htonl(priv->len)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल bool nft_payload_offload_mask(काष्ठा nft_offload_reg *reg,
				     u32 priv_len, u32 field_len)
अणु
	अचिन्हित पूर्णांक reमुख्यder, delta, k;
	काष्ठा nft_data mask = अणुपूर्ण;
	__be32 reमुख्यder_mask;

	अगर (priv_len == field_len) अणु
		स_रखो(&reg->mask, 0xff, priv_len);
		वापस true;
	पूर्ण अन्यथा अगर (priv_len > field_len) अणु
		वापस false;
	पूर्ण

	स_रखो(&mask, 0xff, field_len);
	reमुख्यder = priv_len % माप(u32);
	अगर (reमुख्यder) अणु
		k = priv_len / माप(u32);
		delta = field_len - priv_len;
		reमुख्यder_mask = htonl(~((1 << (delta * BITS_PER_BYTE)) - 1));
		mask.data[k] = (__क्रमce u32)reमुख्यder_mask;
	पूर्ण

	स_नकल(&reg->mask, &mask, field_len);

	वापस true;
पूर्ण

अटल पूर्णांक nft_payload_offload_ll(काष्ठा nft_offload_ctx *ctx,
				  काष्ठा nft_flow_rule *flow,
				  स्थिर काष्ठा nft_payload *priv)
अणु
	काष्ठा nft_offload_reg *reg = &ctx->regs[priv->dreg];

	चयन (priv->offset) अणु
	हाल दुरत्व(काष्ठा ethhdr, h_source):
		अगर (!nft_payload_offload_mask(reg, priv->len, ETH_ALEN))
			वापस -EOPNOTSUPP;

		NFT_OFFLOAD_MATCH(FLOW_DISSECTOR_KEY_ETH_ADDRS, eth_addrs,
				  src, ETH_ALEN, reg);
		अवरोध;
	हाल दुरत्व(काष्ठा ethhdr, h_dest):
		अगर (!nft_payload_offload_mask(reg, priv->len, ETH_ALEN))
			वापस -EOPNOTSUPP;

		NFT_OFFLOAD_MATCH(FLOW_DISSECTOR_KEY_ETH_ADDRS, eth_addrs,
				  dst, ETH_ALEN, reg);
		अवरोध;
	हाल दुरत्व(काष्ठा ethhdr, h_proto):
		अगर (!nft_payload_offload_mask(reg, priv->len, माप(__be16)))
			वापस -EOPNOTSUPP;

		NFT_OFFLOAD_MATCH(FLOW_DISSECTOR_KEY_BASIC, basic,
				  n_proto, माप(__be16), reg);
		nft_offload_set_dependency(ctx, NFT_OFFLOAD_DEP_NETWORK);
		अवरोध;
	हाल दुरत्व(काष्ठा vlan_ethhdr, h_vlan_TCI):
		अगर (!nft_payload_offload_mask(reg, priv->len, माप(__be16)))
			वापस -EOPNOTSUPP;

		NFT_OFFLOAD_MATCH_FLAGS(FLOW_DISSECTOR_KEY_VLAN, vlan,
					vlan_tci, माप(__be16), reg,
					NFT_OFFLOAD_F_NETWORK2HOST);
		अवरोध;
	हाल दुरत्व(काष्ठा vlan_ethhdr, h_vlan_encapsulated_proto):
		अगर (!nft_payload_offload_mask(reg, priv->len, माप(__be16)))
			वापस -EOPNOTSUPP;

		NFT_OFFLOAD_MATCH(FLOW_DISSECTOR_KEY_VLAN, vlan,
				  vlan_tpid, माप(__be16), reg);
		nft_offload_set_dependency(ctx, NFT_OFFLOAD_DEP_NETWORK);
		अवरोध;
	हाल दुरत्व(काष्ठा vlan_ethhdr, h_vlan_TCI) + माप(काष्ठा vlan_hdr):
		अगर (!nft_payload_offload_mask(reg, priv->len, माप(__be16)))
			वापस -EOPNOTSUPP;

		NFT_OFFLOAD_MATCH_FLAGS(FLOW_DISSECTOR_KEY_CVLAN, cvlan,
					vlan_tci, माप(__be16), reg,
					NFT_OFFLOAD_F_NETWORK2HOST);
		अवरोध;
	हाल दुरत्व(काष्ठा vlan_ethhdr, h_vlan_encapsulated_proto) +
							माप(काष्ठा vlan_hdr):
		अगर (!nft_payload_offload_mask(reg, priv->len, माप(__be16)))
			वापस -EOPNOTSUPP;

		NFT_OFFLOAD_MATCH(FLOW_DISSECTOR_KEY_CVLAN, cvlan,
				  vlan_tpid, माप(__be16), reg);
		nft_offload_set_dependency(ctx, NFT_OFFLOAD_DEP_NETWORK);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nft_payload_offload_ip(काष्ठा nft_offload_ctx *ctx,
				  काष्ठा nft_flow_rule *flow,
				  स्थिर काष्ठा nft_payload *priv)
अणु
	काष्ठा nft_offload_reg *reg = &ctx->regs[priv->dreg];

	चयन (priv->offset) अणु
	हाल दुरत्व(काष्ठा iphdr, saddr):
		अगर (!nft_payload_offload_mask(reg, priv->len,
					      माप(काष्ठा in_addr)))
			वापस -EOPNOTSUPP;

		NFT_OFFLOAD_MATCH(FLOW_DISSECTOR_KEY_IPV4_ADDRS, ipv4, src,
				  माप(काष्ठा in_addr), reg);
		nft_flow_rule_set_addr_type(flow, FLOW_DISSECTOR_KEY_IPV4_ADDRS);
		अवरोध;
	हाल दुरत्व(काष्ठा iphdr, daddr):
		अगर (!nft_payload_offload_mask(reg, priv->len,
					      माप(काष्ठा in_addr)))
			वापस -EOPNOTSUPP;

		NFT_OFFLOAD_MATCH(FLOW_DISSECTOR_KEY_IPV4_ADDRS, ipv4, dst,
				  माप(काष्ठा in_addr), reg);
		nft_flow_rule_set_addr_type(flow, FLOW_DISSECTOR_KEY_IPV4_ADDRS);
		अवरोध;
	हाल दुरत्व(काष्ठा iphdr, protocol):
		अगर (!nft_payload_offload_mask(reg, priv->len, माप(__u8)))
			वापस -EOPNOTSUPP;

		NFT_OFFLOAD_MATCH(FLOW_DISSECTOR_KEY_BASIC, basic, ip_proto,
				  माप(__u8), reg);
		nft_offload_set_dependency(ctx, NFT_OFFLOAD_DEP_TRANSPORT);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nft_payload_offload_ip6(काष्ठा nft_offload_ctx *ctx,
				  काष्ठा nft_flow_rule *flow,
				  स्थिर काष्ठा nft_payload *priv)
अणु
	काष्ठा nft_offload_reg *reg = &ctx->regs[priv->dreg];

	चयन (priv->offset) अणु
	हाल दुरत्व(काष्ठा ipv6hdr, saddr):
		अगर (!nft_payload_offload_mask(reg, priv->len,
					      माप(काष्ठा in6_addr)))
			वापस -EOPNOTSUPP;

		NFT_OFFLOAD_MATCH(FLOW_DISSECTOR_KEY_IPV6_ADDRS, ipv6, src,
				  माप(काष्ठा in6_addr), reg);
		nft_flow_rule_set_addr_type(flow, FLOW_DISSECTOR_KEY_IPV6_ADDRS);
		अवरोध;
	हाल दुरत्व(काष्ठा ipv6hdr, daddr):
		अगर (!nft_payload_offload_mask(reg, priv->len,
					      माप(काष्ठा in6_addr)))
			वापस -EOPNOTSUPP;

		NFT_OFFLOAD_MATCH(FLOW_DISSECTOR_KEY_IPV6_ADDRS, ipv6, dst,
				  माप(काष्ठा in6_addr), reg);
		nft_flow_rule_set_addr_type(flow, FLOW_DISSECTOR_KEY_IPV6_ADDRS);
		अवरोध;
	हाल दुरत्व(काष्ठा ipv6hdr, nexthdr):
		अगर (!nft_payload_offload_mask(reg, priv->len, माप(__u8)))
			वापस -EOPNOTSUPP;

		NFT_OFFLOAD_MATCH(FLOW_DISSECTOR_KEY_BASIC, basic, ip_proto,
				  माप(__u8), reg);
		nft_offload_set_dependency(ctx, NFT_OFFLOAD_DEP_TRANSPORT);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nft_payload_offload_nh(काष्ठा nft_offload_ctx *ctx,
				  काष्ठा nft_flow_rule *flow,
				  स्थिर काष्ठा nft_payload *priv)
अणु
	पूर्णांक err;

	चयन (ctx->dep.l3num) अणु
	हाल htons(ETH_P_IP):
		err = nft_payload_offload_ip(ctx, flow, priv);
		अवरोध;
	हाल htons(ETH_P_IPV6):
		err = nft_payload_offload_ip6(ctx, flow, priv);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक nft_payload_offload_tcp(काष्ठा nft_offload_ctx *ctx,
				   काष्ठा nft_flow_rule *flow,
				   स्थिर काष्ठा nft_payload *priv)
अणु
	काष्ठा nft_offload_reg *reg = &ctx->regs[priv->dreg];

	चयन (priv->offset) अणु
	हाल दुरत्व(काष्ठा tcphdr, source):
		अगर (!nft_payload_offload_mask(reg, priv->len, माप(__be16)))
			वापस -EOPNOTSUPP;

		NFT_OFFLOAD_MATCH(FLOW_DISSECTOR_KEY_PORTS, tp, src,
				  माप(__be16), reg);
		अवरोध;
	हाल दुरत्व(काष्ठा tcphdr, dest):
		अगर (!nft_payload_offload_mask(reg, priv->len, माप(__be16)))
			वापस -EOPNOTSUPP;

		NFT_OFFLOAD_MATCH(FLOW_DISSECTOR_KEY_PORTS, tp, dst,
				  माप(__be16), reg);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nft_payload_offload_udp(काष्ठा nft_offload_ctx *ctx,
				   काष्ठा nft_flow_rule *flow,
				   स्थिर काष्ठा nft_payload *priv)
अणु
	काष्ठा nft_offload_reg *reg = &ctx->regs[priv->dreg];

	चयन (priv->offset) अणु
	हाल दुरत्व(काष्ठा udphdr, source):
		अगर (!nft_payload_offload_mask(reg, priv->len, माप(__be16)))
			वापस -EOPNOTSUPP;

		NFT_OFFLOAD_MATCH(FLOW_DISSECTOR_KEY_PORTS, tp, src,
				  माप(__be16), reg);
		अवरोध;
	हाल दुरत्व(काष्ठा udphdr, dest):
		अगर (!nft_payload_offload_mask(reg, priv->len, माप(__be16)))
			वापस -EOPNOTSUPP;

		NFT_OFFLOAD_MATCH(FLOW_DISSECTOR_KEY_PORTS, tp, dst,
				  माप(__be16), reg);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nft_payload_offload_th(काष्ठा nft_offload_ctx *ctx,
				  काष्ठा nft_flow_rule *flow,
				  स्थिर काष्ठा nft_payload *priv)
अणु
	पूर्णांक err;

	चयन (ctx->dep.protonum) अणु
	हाल IPPROTO_TCP:
		err = nft_payload_offload_tcp(ctx, flow, priv);
		अवरोध;
	हाल IPPROTO_UDP:
		err = nft_payload_offload_udp(ctx, flow, priv);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक nft_payload_offload(काष्ठा nft_offload_ctx *ctx,
			       काष्ठा nft_flow_rule *flow,
			       स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_payload *priv = nft_expr_priv(expr);
	पूर्णांक err;

	चयन (priv->base) अणु
	हाल NFT_PAYLOAD_LL_HEADER:
		err = nft_payload_offload_ll(ctx, flow, priv);
		अवरोध;
	हाल NFT_PAYLOAD_NETWORK_HEADER:
		err = nft_payload_offload_nh(ctx, flow, priv);
		अवरोध;
	हाल NFT_PAYLOAD_TRANSPORT_HEADER:
		err = nft_payload_offload_th(ctx, flow, priv);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल स्थिर काष्ठा nft_expr_ops nft_payload_ops = अणु
	.type		= &nft_payload_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_payload)),
	.eval		= nft_payload_eval,
	.init		= nft_payload_init,
	.dump		= nft_payload_dump,
	.offload	= nft_payload_offload,
पूर्ण;

स्थिर काष्ठा nft_expr_ops nft_payload_fast_ops = अणु
	.type		= &nft_payload_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_payload)),
	.eval		= nft_payload_eval,
	.init		= nft_payload_init,
	.dump		= nft_payload_dump,
	.offload	= nft_payload_offload,
पूर्ण;

अटल अंतरभूत व्योम nft_csum_replace(__sum16 *sum, __wsum fsum, __wsum tsum)
अणु
	*sum = csum_fold(csum_add(csum_sub(~csum_unfold(*sum), fsum), tsum));
	अगर (*sum == 0)
		*sum = CSUM_MANGLED_0;
पूर्ण

अटल bool nft_payload_udp_checksum(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक thoff)
अणु
	काष्ठा udphdr *uh, _uh;

	uh = skb_header_poपूर्णांकer(skb, thoff, माप(_uh), &_uh);
	अगर (!uh)
		वापस false;

	वापस (__क्रमce bool)uh->check;
पूर्ण

अटल पूर्णांक nft_payload_l4csum_offset(स्थिर काष्ठा nft_pktinfo *pkt,
				     काष्ठा sk_buff *skb,
				     अचिन्हित पूर्णांक *l4csum_offset)
अणु
	चयन (pkt->tprot) अणु
	हाल IPPROTO_TCP:
		*l4csum_offset = दुरत्व(काष्ठा tcphdr, check);
		अवरोध;
	हाल IPPROTO_UDP:
		अगर (!nft_payload_udp_checksum(skb, pkt->xt.thoff))
			वापस -1;
		fallthrough;
	हाल IPPROTO_UDPLITE:
		*l4csum_offset = दुरत्व(काष्ठा udphdr, check);
		अवरोध;
	हाल IPPROTO_ICMPV6:
		*l4csum_offset = दुरत्व(काष्ठा icmp6hdr, icmp6_cksum);
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	*l4csum_offset += pkt->xt.thoff;
	वापस 0;
पूर्ण

अटल पूर्णांक nft_payload_csum_sctp(काष्ठा sk_buff *skb, पूर्णांक offset)
अणु
	काष्ठा sctphdr *sh;

	अगर (skb_ensure_writable(skb, offset + माप(*sh)))
		वापस -1;

	sh = (काष्ठा sctphdr *)(skb->data + offset);
	sh->checksum = sctp_compute_cksum(skb, offset);
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	वापस 0;
पूर्ण

अटल पूर्णांक nft_payload_l4csum_update(स्थिर काष्ठा nft_pktinfo *pkt,
				     काष्ठा sk_buff *skb,
				     __wsum fsum, __wsum tsum)
अणु
	पूर्णांक l4csum_offset;
	__sum16 sum;

	/* If we cannot determine layer 4 checksum offset or this packet करोesn't
	 * require layer 4 checksum recalculation, skip this packet.
	 */
	अगर (nft_payload_l4csum_offset(pkt, skb, &l4csum_offset) < 0)
		वापस 0;

	अगर (skb_copy_bits(skb, l4csum_offset, &sum, माप(sum)) < 0)
		वापस -1;

	/* Checksum mangling क्रम an arbitrary amount of bytes, based on
	 * inet_proto_csum_replace*() functions.
	 */
	अगर (skb->ip_summed != CHECKSUM_PARTIAL) अणु
		nft_csum_replace(&sum, fsum, tsum);
		अगर (skb->ip_summed == CHECKSUM_COMPLETE) अणु
			skb->csum = ~csum_add(csum_sub(~(skb->csum), fsum),
					      tsum);
		पूर्ण
	पूर्ण अन्यथा अणु
		sum = ~csum_fold(csum_add(csum_sub(csum_unfold(sum), fsum),
					  tsum));
	पूर्ण

	अगर (skb_ensure_writable(skb, l4csum_offset + माप(sum)) ||
	    skb_store_bits(skb, l4csum_offset, &sum, माप(sum)) < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक nft_payload_csum_inet(काष्ठा sk_buff *skb, स्थिर u32 *src,
				 __wsum fsum, __wsum tsum, पूर्णांक csum_offset)
अणु
	__sum16 sum;

	अगर (skb_copy_bits(skb, csum_offset, &sum, माप(sum)) < 0)
		वापस -1;

	nft_csum_replace(&sum, fsum, tsum);
	अगर (skb_ensure_writable(skb, csum_offset + माप(sum)) ||
	    skb_store_bits(skb, csum_offset, &sum, माप(sum)) < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम nft_payload_set_eval(स्थिर काष्ठा nft_expr *expr,
				 काष्ठा nft_regs *regs,
				 स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_payload_set *priv = nft_expr_priv(expr);
	काष्ठा sk_buff *skb = pkt->skb;
	स्थिर u32 *src = &regs->data[priv->sreg];
	पूर्णांक offset, csum_offset;
	__wsum fsum, tsum;

	चयन (priv->base) अणु
	हाल NFT_PAYLOAD_LL_HEADER:
		अगर (!skb_mac_header_was_set(skb))
			जाओ err;
		offset = skb_mac_header(skb) - skb->data;
		अवरोध;
	हाल NFT_PAYLOAD_NETWORK_HEADER:
		offset = skb_network_offset(skb);
		अवरोध;
	हाल NFT_PAYLOAD_TRANSPORT_HEADER:
		अगर (!pkt->tprot_set)
			जाओ err;
		offset = pkt->xt.thoff;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	csum_offset = offset + priv->csum_offset;
	offset += priv->offset;

	अगर ((priv->csum_type == NFT_PAYLOAD_CSUM_INET || priv->csum_flags) &&
	    (priv->base != NFT_PAYLOAD_TRANSPORT_HEADER ||
	     skb->ip_summed != CHECKSUM_PARTIAL)) अणु
		fsum = skb_checksum(skb, offset, priv->len, 0);
		tsum = csum_partial(src, priv->len, 0);

		अगर (priv->csum_type == NFT_PAYLOAD_CSUM_INET &&
		    nft_payload_csum_inet(skb, src, fsum, tsum, csum_offset))
			जाओ err;

		अगर (priv->csum_flags &&
		    nft_payload_l4csum_update(pkt, skb, fsum, tsum) < 0)
			जाओ err;
	पूर्ण

	अगर (skb_ensure_writable(skb, max(offset + priv->len, 0)) ||
	    skb_store_bits(skb, offset, src, priv->len) < 0)
		जाओ err;

	अगर (priv->csum_type == NFT_PAYLOAD_CSUM_SCTP &&
	    pkt->tprot == IPPROTO_SCTP &&
	    skb->ip_summed != CHECKSUM_PARTIAL) अणु
		अगर (nft_payload_csum_sctp(skb, pkt->xt.thoff))
			जाओ err;
	पूर्ण

	वापस;
err:
	regs->verdict.code = NFT_BREAK;
पूर्ण

अटल पूर्णांक nft_payload_set_init(स्थिर काष्ठा nft_ctx *ctx,
				स्थिर काष्ठा nft_expr *expr,
				स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_payload_set *priv = nft_expr_priv(expr);

	priv->base        = ntohl(nla_get_be32(tb[NFTA_PAYLOAD_BASE]));
	priv->offset      = ntohl(nla_get_be32(tb[NFTA_PAYLOAD_OFFSET]));
	priv->len         = ntohl(nla_get_be32(tb[NFTA_PAYLOAD_LEN]));

	अगर (tb[NFTA_PAYLOAD_CSUM_TYPE])
		priv->csum_type =
			ntohl(nla_get_be32(tb[NFTA_PAYLOAD_CSUM_TYPE]));
	अगर (tb[NFTA_PAYLOAD_CSUM_OFFSET])
		priv->csum_offset =
			ntohl(nla_get_be32(tb[NFTA_PAYLOAD_CSUM_OFFSET]));
	अगर (tb[NFTA_PAYLOAD_CSUM_FLAGS]) अणु
		u32 flags;

		flags = ntohl(nla_get_be32(tb[NFTA_PAYLOAD_CSUM_FLAGS]));
		अगर (flags & ~NFT_PAYLOAD_L4CSUM_PSEUDOHDR)
			वापस -EINVAL;

		priv->csum_flags = flags;
	पूर्ण

	चयन (priv->csum_type) अणु
	हाल NFT_PAYLOAD_CSUM_NONE:
	हाल NFT_PAYLOAD_CSUM_INET:
		अवरोध;
	हाल NFT_PAYLOAD_CSUM_SCTP:
		अगर (priv->base != NFT_PAYLOAD_TRANSPORT_HEADER)
			वापस -EINVAL;

		अगर (priv->csum_offset != दुरत्व(काष्ठा sctphdr, checksum))
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस nft_parse_रेजिस्टर_load(tb[NFTA_PAYLOAD_SREG], &priv->sreg,
				       priv->len);
पूर्ण

अटल पूर्णांक nft_payload_set_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_payload_set *priv = nft_expr_priv(expr);

	अगर (nft_dump_रेजिस्टर(skb, NFTA_PAYLOAD_SREG, priv->sreg) ||
	    nla_put_be32(skb, NFTA_PAYLOAD_BASE, htonl(priv->base)) ||
	    nla_put_be32(skb, NFTA_PAYLOAD_OFFSET, htonl(priv->offset)) ||
	    nla_put_be32(skb, NFTA_PAYLOAD_LEN, htonl(priv->len)) ||
	    nla_put_be32(skb, NFTA_PAYLOAD_CSUM_TYPE, htonl(priv->csum_type)) ||
	    nla_put_be32(skb, NFTA_PAYLOAD_CSUM_OFFSET,
			 htonl(priv->csum_offset)) ||
	    nla_put_be32(skb, NFTA_PAYLOAD_CSUM_FLAGS, htonl(priv->csum_flags)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल स्थिर काष्ठा nft_expr_ops nft_payload_set_ops = अणु
	.type		= &nft_payload_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_payload_set)),
	.eval		= nft_payload_set_eval,
	.init		= nft_payload_set_init,
	.dump		= nft_payload_set_dump,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops *
nft_payload_select_ops(स्थिर काष्ठा nft_ctx *ctx,
		       स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	क्रमागत nft_payload_bases base;
	अचिन्हित पूर्णांक offset, len;

	अगर (tb[NFTA_PAYLOAD_BASE] == शून्य ||
	    tb[NFTA_PAYLOAD_OFFSET] == शून्य ||
	    tb[NFTA_PAYLOAD_LEN] == शून्य)
		वापस ERR_PTR(-EINVAL);

	base = ntohl(nla_get_be32(tb[NFTA_PAYLOAD_BASE]));
	चयन (base) अणु
	हाल NFT_PAYLOAD_LL_HEADER:
	हाल NFT_PAYLOAD_NETWORK_HEADER:
	हाल NFT_PAYLOAD_TRANSPORT_HEADER:
		अवरोध;
	शेष:
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	अगर (tb[NFTA_PAYLOAD_SREG] != शून्य) अणु
		अगर (tb[NFTA_PAYLOAD_DREG] != शून्य)
			वापस ERR_PTR(-EINVAL);
		वापस &nft_payload_set_ops;
	पूर्ण

	अगर (tb[NFTA_PAYLOAD_DREG] == शून्य)
		वापस ERR_PTR(-EINVAL);

	offset = ntohl(nla_get_be32(tb[NFTA_PAYLOAD_OFFSET]));
	len    = ntohl(nla_get_be32(tb[NFTA_PAYLOAD_LEN]));

	अगर (len <= 4 && is_घातer_of_2(len) && IS_ALIGNED(offset, len) &&
	    base != NFT_PAYLOAD_LL_HEADER)
		वापस &nft_payload_fast_ops;
	अन्यथा
		वापस &nft_payload_ops;
पूर्ण

काष्ठा nft_expr_type nft_payload_type __पढ़ो_mostly = अणु
	.name		= "payload",
	.select_ops	= nft_payload_select_ops,
	.policy		= nft_payload_policy,
	.maxattr	= NFTA_PAYLOAD_MAX,
	.owner		= THIS_MODULE,
पूर्ण;
