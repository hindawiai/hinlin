<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/socket.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <linux/udp.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <net/fou.h>
#समावेश <net/ip.h>
#समावेश <net/ip6_tunnel.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/protocol.h>
#समावेश <net/udp.h>
#समावेश <net/udp_tunnel.h>

#अगर IS_ENABLED(CONFIG_IPV6_FOU_TUNNEL)

अटल व्योम fou6_build_udp(काष्ठा sk_buff *skb, काष्ठा ip_tunnel_encap *e,
			   काष्ठा flowi6 *fl6, u8 *protocol, __be16 sport)
अणु
	काष्ठा udphdr *uh;

	skb_push(skb, माप(काष्ठा udphdr));
	skb_reset_transport_header(skb);

	uh = udp_hdr(skb);

	uh->dest = e->dport;
	uh->source = sport;
	uh->len = htons(skb->len);
	udp6_set_csum(!(e->flags & TUNNEL_ENCAP_FLAG_CSUM6), skb,
		      &fl6->saddr, &fl6->daddr, skb->len);

	*protocol = IPPROTO_UDP;
पूर्ण

अटल पूर्णांक fou6_build_header(काष्ठा sk_buff *skb, काष्ठा ip_tunnel_encap *e,
			     u8 *protocol, काष्ठा flowi6 *fl6)
अणु
	__be16 sport;
	पूर्णांक err;
	पूर्णांक type = e->flags & TUNNEL_ENCAP_FLAG_CSUM6 ?
		SKB_GSO_UDP_TUNNEL_CSUM : SKB_GSO_UDP_TUNNEL;

	err = __fou_build_header(skb, e, protocol, &sport, type);
	अगर (err)
		वापस err;

	fou6_build_udp(skb, e, fl6, protocol, sport);

	वापस 0;
पूर्ण

अटल पूर्णांक gue6_build_header(काष्ठा sk_buff *skb, काष्ठा ip_tunnel_encap *e,
			     u8 *protocol, काष्ठा flowi6 *fl6)
अणु
	__be16 sport;
	पूर्णांक err;
	पूर्णांक type = e->flags & TUNNEL_ENCAP_FLAG_CSUM6 ?
		SKB_GSO_UDP_TUNNEL_CSUM : SKB_GSO_UDP_TUNNEL;

	err = __gue_build_header(skb, e, protocol, &sport, type);
	अगर (err)
		वापस err;

	fou6_build_udp(skb, e, fl6, protocol, sport);

	वापस 0;
पूर्ण

अटल पूर्णांक gue6_err_proto_handler(पूर्णांक proto, काष्ठा sk_buff *skb,
				  काष्ठा inet6_skb_parm *opt,
				  u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	स्थिर काष्ठा inet6_protocol *ipprot;

	ipprot = rcu_dereference(inet6_protos[proto]);
	अगर (ipprot && ipprot->err_handler) अणु
		अगर (!ipprot->err_handler(skb, opt, type, code, offset, info))
			वापस 0;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक gue6_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
		    u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	पूर्णांक transport_offset = skb_transport_offset(skb);
	काष्ठा guehdr *guehdr;
	माप_प्रकार len, optlen;
	पूर्णांक ret;

	len = माप(काष्ठा udphdr) + माप(काष्ठा guehdr);
	अगर (!pskb_may_pull(skb, transport_offset + len))
		वापस -EINVAL;

	guehdr = (काष्ठा guehdr *)&udp_hdr(skb)[1];

	चयन (guehdr->version) अणु
	हाल 0: /* Full GUE header present */
		अवरोध;
	हाल 1: अणु
		/* Direct encasulation of IPv4 or IPv6 */
		skb_set_transport_header(skb, -(पूर्णांक)माप(काष्ठा icmp6hdr));

		चयन (((काष्ठा iphdr *)guehdr)->version) अणु
		हाल 4:
			ret = gue6_err_proto_handler(IPPROTO_IPIP, skb, opt,
						     type, code, offset, info);
			जाओ out;
		हाल 6:
			ret = gue6_err_proto_handler(IPPROTO_IPV6, skb, opt,
						     type, code, offset, info);
			जाओ out;
		शेष:
			ret = -EOPNOTSUPP;
			जाओ out;
		पूर्ण
	पूर्ण
	शेष: /* Undefined version */
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (guehdr->control)
		वापस -ENOENT;

	optlen = guehdr->hlen << 2;

	अगर (!pskb_may_pull(skb, transport_offset + len + optlen))
		वापस -EINVAL;

	guehdr = (काष्ठा guehdr *)&udp_hdr(skb)[1];
	अगर (validate_gue_flags(guehdr, optlen))
		वापस -EINVAL;

	/* Handling exceptions क्रम direct UDP encapsulation in GUE would lead to
	 * recursion. Besides, this kind of encapsulation can't even be
	 * configured currently. Discard this.
	 */
	अगर (guehdr->proto_ctype == IPPROTO_UDP ||
	    guehdr->proto_ctype == IPPROTO_UDPLITE)
		वापस -EOPNOTSUPP;

	skb_set_transport_header(skb, -(पूर्णांक)माप(काष्ठा icmp6hdr));
	ret = gue6_err_proto_handler(guehdr->proto_ctype, skb,
				     opt, type, code, offset, info);

out:
	skb_set_transport_header(skb, transport_offset);
	वापस ret;
पूर्ण


अटल स्थिर काष्ठा ip6_tnl_encap_ops fou_ip6tun_ops = अणु
	.encap_hlen = fou_encap_hlen,
	.build_header = fou6_build_header,
	.err_handler = gue6_err,
पूर्ण;

अटल स्थिर काष्ठा ip6_tnl_encap_ops gue_ip6tun_ops = अणु
	.encap_hlen = gue_encap_hlen,
	.build_header = gue6_build_header,
	.err_handler = gue6_err,
पूर्ण;

अटल पूर्णांक ip6_tnl_encap_add_fou_ops(व्योम)
अणु
	पूर्णांक ret;

	ret = ip6_tnl_encap_add_ops(&fou_ip6tun_ops, TUNNEL_ENCAP_FOU);
	अगर (ret < 0) अणु
		pr_err("can't add fou6 ops\n");
		वापस ret;
	पूर्ण

	ret = ip6_tnl_encap_add_ops(&gue_ip6tun_ops, TUNNEL_ENCAP_GUE);
	अगर (ret < 0) अणु
		pr_err("can't add gue6 ops\n");
		ip6_tnl_encap_del_ops(&fou_ip6tun_ops, TUNNEL_ENCAP_FOU);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ip6_tnl_encap_del_fou_ops(व्योम)
अणु
	ip6_tnl_encap_del_ops(&fou_ip6tun_ops, TUNNEL_ENCAP_FOU);
	ip6_tnl_encap_del_ops(&gue_ip6tun_ops, TUNNEL_ENCAP_GUE);
पूर्ण

#अन्यथा

अटल पूर्णांक ip6_tnl_encap_add_fou_ops(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम ip6_tnl_encap_del_fou_ops(व्योम)
अणु
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक __init fou6_init(व्योम)
अणु
	पूर्णांक ret;

	ret = ip6_tnl_encap_add_fou_ops();

	वापस ret;
पूर्ण

अटल व्योम __निकास fou6_fini(व्योम)
अणु
	ip6_tnl_encap_del_fou_ops();
पूर्ण

module_init(fou6_init);
module_निकास(fou6_fini);
MODULE_AUTHOR("Tom Herbert <therbert@google.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Foo over UDP (IPv6)");
