<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IP Payload Compression Protocol (IPComp) - RFC3173.
 *
 * Copyright (c) 2003 James Morris <jmorris@पूर्णांकercode.com.au>
 *
 * Toकरो:
 *   - Tunable compression parameters.
 *   - Compression stats.
 *   - Adaptive compression.
 */
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/ip.h>
#समावेश <net/xfrm.h>
#समावेश <net/icmp.h>
#समावेश <net/ipcomp.h>
#समावेश <net/protocol.h>
#समावेश <net/sock.h>

अटल पूर्णांक ipcomp4_err(काष्ठा sk_buff *skb, u32 info)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	__be32 spi;
	स्थिर काष्ठा iphdr *iph = (स्थिर काष्ठा iphdr *)skb->data;
	काष्ठा ip_comp_hdr *ipch = (काष्ठा ip_comp_hdr *)(skb->data+(iph->ihl<<2));
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

	spi = htonl(ntohs(ipch->cpi));
	x = xfrm_state_lookup(net, skb->mark, (स्थिर xfrm_address_t *)&iph->daddr,
			      spi, IPPROTO_COMP, AF_INET);
	अगर (!x)
		वापस 0;

	अगर (icmp_hdr(skb)->type == ICMP_DEST_UNREACH)
		ipv4_update_pmtu(skb, net, info, 0, IPPROTO_COMP);
	अन्यथा
		ipv4_redirect(skb, net, 0, IPPROTO_COMP);
	xfrm_state_put(x);

	वापस 0;
पूर्ण

/* We always hold one tunnel user reference to indicate a tunnel */
अटल काष्ठा xfrm_state *ipcomp_tunnel_create(काष्ठा xfrm_state *x)
अणु
	काष्ठा net *net = xs_net(x);
	काष्ठा xfrm_state *t;

	t = xfrm_state_alloc(net);
	अगर (!t)
		जाओ out;

	t->id.proto = IPPROTO_IPIP;
	t->id.spi = x->props.saddr.a4;
	t->id.daddr.a4 = x->id.daddr.a4;
	स_नकल(&t->sel, &x->sel, माप(t->sel));
	t->props.family = AF_INET;
	t->props.mode = x->props.mode;
	t->props.saddr.a4 = x->props.saddr.a4;
	t->props.flags = x->props.flags;
	t->props.extra_flags = x->props.extra_flags;
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

/*
 * Must be रक्षित by xfrm_cfg_mutex.  State and tunnel user references are
 * always incremented on success.
 */
अटल पूर्णांक ipcomp_tunnel_attach(काष्ठा xfrm_state *x)
अणु
	काष्ठा net *net = xs_net(x);
	पूर्णांक err = 0;
	काष्ठा xfrm_state *t;
	u32 mark = x->mark.v & x->mark.m;

	t = xfrm_state_lookup(net, mark, (xfrm_address_t *)&x->id.daddr.a4,
			      x->props.saddr.a4, IPPROTO_IPIP, AF_INET);
	अगर (!t) अणु
		t = ipcomp_tunnel_create(x);
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

अटल पूर्णांक ipcomp4_init_state(काष्ठा xfrm_state *x)
अणु
	पूर्णांक err = -EINVAL;

	x->props.header_len = 0;
	चयन (x->props.mode) अणु
	हाल XFRM_MODE_TRANSPORT:
		अवरोध;
	हाल XFRM_MODE_TUNNEL:
		x->props.header_len += माप(काष्ठा iphdr);
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	err = ipcomp_init_state(x);
	अगर (err)
		जाओ out;

	अगर (x->props.mode == XFRM_MODE_TUNNEL) अणु
		err = ipcomp_tunnel_attach(x);
		अगर (err)
			जाओ out;
	पूर्ण

	err = 0;
out:
	वापस err;
पूर्ण

अटल पूर्णांक ipcomp4_rcv_cb(काष्ठा sk_buff *skb, पूर्णांक err)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा xfrm_type ipcomp_type = अणु
	.description	= "IPCOMP4",
	.owner		= THIS_MODULE,
	.proto	     	= IPPROTO_COMP,
	.init_state	= ipcomp4_init_state,
	.deकाष्ठाor	= ipcomp_destroy,
	.input		= ipcomp_input,
	.output		= ipcomp_output
पूर्ण;

अटल काष्ठा xfrm4_protocol ipcomp4_protocol = अणु
	.handler	=	xfrm4_rcv,
	.input_handler	=	xfrm_input,
	.cb_handler	=	ipcomp4_rcv_cb,
	.err_handler	=	ipcomp4_err,
	.priority	=	0,
पूर्ण;

अटल पूर्णांक __init ipcomp4_init(व्योम)
अणु
	अगर (xfrm_रेजिस्टर_type(&ipcomp_type, AF_INET) < 0) अणु
		pr_info("%s: can't add xfrm type\n", __func__);
		वापस -EAGAIN;
	पूर्ण
	अगर (xfrm4_protocol_रेजिस्टर(&ipcomp4_protocol, IPPROTO_COMP) < 0) अणु
		pr_info("%s: can't add protocol\n", __func__);
		xfrm_unरेजिस्टर_type(&ipcomp_type, AF_INET);
		वापस -EAGAIN;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास ipcomp4_fini(व्योम)
अणु
	अगर (xfrm4_protocol_deरेजिस्टर(&ipcomp4_protocol, IPPROTO_COMP) < 0)
		pr_info("%s: can't remove protocol\n", __func__);
	xfrm_unरेजिस्टर_type(&ipcomp_type, AF_INET);
पूर्ण

module_init(ipcomp4_init);
module_निकास(ipcomp4_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("IP Payload Compression Protocol (IPComp/IPv4) - RFC3173");
MODULE_AUTHOR("James Morris <jmorris@intercode.com.au>");

MODULE_ALIAS_XFRM_TYPE(AF_INET, XFRM_PROTO_COMP);
