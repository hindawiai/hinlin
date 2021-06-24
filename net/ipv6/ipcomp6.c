<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IP Payload Compression Protocol (IPComp) क्रम IPv6 - RFC3173
 *
 * Copyright (C)2003 USAGI/WIDE Project
 *
 * Author	Mitsuru KANDA  <mk@linux-ipv6.org>
 */
/*
 * [Memo]
 *
 * Outbound:
 *  The compression of IP datagram MUST be करोne beक्रमe AH/ESP processing,
 *  fragmentation, and the addition of Hop-by-Hop/Routing header.
 *
 * Inbound:
 *  The decompression of IP datagram MUST be करोne after the reassembly,
 *  AH/ESP processing.
 */

#घोषणा pr_fmt(fmt) "IPv6: " fmt

#समावेश <linux/module.h>
#समावेश <net/ip.h>
#समावेश <net/xfrm.h>
#समावेश <net/ipcomp.h>
#समावेश <linux/crypto.h>
#समावेश <linux/err.h>
#समावेश <linux/pfkeyv2.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/percpu.h>
#समावेश <linux/smp.h>
#समावेश <linux/list.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/ip6_route.h>
#समावेश <net/icmp.h>
#समावेश <net/ipv6.h>
#समावेश <net/protocol.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/mutex.h>

अटल पूर्णांक ipcomp6_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
				u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	__be32 spi;
	स्थिर काष्ठा ipv6hdr *iph = (स्थिर काष्ठा ipv6hdr *)skb->data;
	काष्ठा ip_comp_hdr *ipcomph =
		(काष्ठा ip_comp_hdr *)(skb->data + offset);
	काष्ठा xfrm_state *x;

	अगर (type != ICMPV6_PKT_TOOBIG &&
	    type != NDISC_REसूचीECT)
		वापस 0;

	spi = htonl(ntohs(ipcomph->cpi));
	x = xfrm_state_lookup(net, skb->mark, (स्थिर xfrm_address_t *)&iph->daddr,
			      spi, IPPROTO_COMP, AF_INET6);
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

अटल काष्ठा xfrm_state *ipcomp6_tunnel_create(काष्ठा xfrm_state *x)
अणु
	काष्ठा net *net = xs_net(x);
	काष्ठा xfrm_state *t = शून्य;

	t = xfrm_state_alloc(net);
	अगर (!t)
		जाओ out;

	t->id.proto = IPPROTO_IPV6;
	t->id.spi = xfrm6_tunnel_alloc_spi(net, (xfrm_address_t *)&x->props.saddr);
	अगर (!t->id.spi)
		जाओ error;

	स_नकल(t->id.daddr.a6, x->id.daddr.a6, माप(काष्ठा in6_addr));
	स_नकल(&t->sel, &x->sel, माप(t->sel));
	t->props.family = AF_INET6;
	t->props.mode = x->props.mode;
	स_नकल(t->props.saddr.a6, x->props.saddr.a6, माप(काष्ठा in6_addr));
	स_नकल(&t->mark, &x->mark, माप(t->mark));
	t->अगर_id = x->अगर_id;

	अगर (xfrm_init_state(t))
		जाओ error;

	atomic_set(&t->tunnel_users, 1);

out:
	वापस t;

error:
	t->km.state = XFRM_STATE_DEAD;
	xfrm_state_put(t);
	t = शून्य;
	जाओ out;
पूर्ण

अटल पूर्णांक ipcomp6_tunnel_attach(काष्ठा xfrm_state *x)
अणु
	काष्ठा net *net = xs_net(x);
	पूर्णांक err = 0;
	काष्ठा xfrm_state *t = शून्य;
	__be32 spi;
	u32 mark = x->mark.m & x->mark.v;

	spi = xfrm6_tunnel_spi_lookup(net, (xfrm_address_t *)&x->props.saddr);
	अगर (spi)
		t = xfrm_state_lookup(net, mark, (xfrm_address_t *)&x->id.daddr,
					      spi, IPPROTO_IPV6, AF_INET6);
	अगर (!t) अणु
		t = ipcomp6_tunnel_create(x);
		अगर (!t) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
		xfrm_state_insert(t);
		xfrm_state_hold(t);
	पूर्ण
	x->tunnel = t;
	atomic_inc(&t->tunnel_users);

out:
	वापस err;
पूर्ण

अटल पूर्णांक ipcomp6_init_state(काष्ठा xfrm_state *x)
अणु
	पूर्णांक err = -EINVAL;

	x->props.header_len = 0;
	चयन (x->props.mode) अणु
	हाल XFRM_MODE_TRANSPORT:
		अवरोध;
	हाल XFRM_MODE_TUNNEL:
		x->props.header_len += माप(काष्ठा ipv6hdr);
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	err = ipcomp_init_state(x);
	अगर (err)
		जाओ out;

	अगर (x->props.mode == XFRM_MODE_TUNNEL) अणु
		err = ipcomp6_tunnel_attach(x);
		अगर (err)
			जाओ out;
	पूर्ण

	err = 0;
out:
	वापस err;
पूर्ण

अटल पूर्णांक ipcomp6_rcv_cb(काष्ठा sk_buff *skb, पूर्णांक err)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा xfrm_type ipcomp6_type = अणु
	.description	= "IPCOMP6",
	.owner		= THIS_MODULE,
	.proto		= IPPROTO_COMP,
	.init_state	= ipcomp6_init_state,
	.deकाष्ठाor	= ipcomp_destroy,
	.input		= ipcomp_input,
	.output		= ipcomp_output,
	.hdr_offset	= xfrm6_find_1stfragopt,
पूर्ण;

अटल काष्ठा xfrm6_protocol ipcomp6_protocol = अणु
	.handler	= xfrm6_rcv,
	.input_handler	= xfrm_input,
	.cb_handler	= ipcomp6_rcv_cb,
	.err_handler	= ipcomp6_err,
	.priority	= 0,
पूर्ण;

अटल पूर्णांक __init ipcomp6_init(व्योम)
अणु
	अगर (xfrm_रेजिस्टर_type(&ipcomp6_type, AF_INET6) < 0) अणु
		pr_info("%s: can't add xfrm type\n", __func__);
		वापस -EAGAIN;
	पूर्ण
	अगर (xfrm6_protocol_रेजिस्टर(&ipcomp6_protocol, IPPROTO_COMP) < 0) अणु
		pr_info("%s: can't add protocol\n", __func__);
		xfrm_unरेजिस्टर_type(&ipcomp6_type, AF_INET6);
		वापस -EAGAIN;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास ipcomp6_fini(व्योम)
अणु
	अगर (xfrm6_protocol_deरेजिस्टर(&ipcomp6_protocol, IPPROTO_COMP) < 0)
		pr_info("%s: can't remove protocol\n", __func__);
	xfrm_unरेजिस्टर_type(&ipcomp6_type, AF_INET6);
पूर्ण

module_init(ipcomp6_init);
module_निकास(ipcomp6_fini);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("IP Payload Compression Protocol (IPComp) for IPv6 - RFC3173");
MODULE_AUTHOR("Mitsuru KANDA <mk@linux-ipv6.org>");

MODULE_ALIAS_XFRM_TYPE(AF_INET6, XFRM_PROTO_COMP);
