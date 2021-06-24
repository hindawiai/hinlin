<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* xfrm4_tunnel.c: Generic IP tunnel transक्रमmer.
 *
 * Copyright (C) 2003 David S. Miller (davem@redhat.com)
 */

#घोषणा pr_fmt(fmt) "IPsec: " fmt

#समावेश <linux/skbuff.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <net/xfrm.h>
#समावेश <net/ip.h>
#समावेश <net/protocol.h>

अटल पूर्णांक ipip_output(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	skb_push(skb, -skb_network_offset(skb));
	वापस 0;
पूर्ण

अटल पूर्णांक ipip_xfrm_rcv(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	वापस ip_hdr(skb)->protocol;
पूर्ण

अटल पूर्णांक ipip_init_state(काष्ठा xfrm_state *x)
अणु
	अगर (x->props.mode != XFRM_MODE_TUNNEL)
		वापस -EINVAL;

	अगर (x->encap)
		वापस -EINVAL;

	x->props.header_len = माप(काष्ठा iphdr);

	वापस 0;
पूर्ण

अटल व्योम ipip_destroy(काष्ठा xfrm_state *x)
अणु
पूर्ण

अटल स्थिर काष्ठा xfrm_type ipip_type = अणु
	.description	= "IPIP",
	.owner		= THIS_MODULE,
	.proto	     	= IPPROTO_IPIP,
	.init_state	= ipip_init_state,
	.deकाष्ठाor	= ipip_destroy,
	.input		= ipip_xfrm_rcv,
	.output		= ipip_output
पूर्ण;

अटल पूर्णांक xfrm_tunnel_rcv(काष्ठा sk_buff *skb)
अणु
	वापस xfrm4_rcv_spi(skb, IPPROTO_IPIP, ip_hdr(skb)->saddr);
पूर्ण

अटल पूर्णांक xfrm_tunnel_err(काष्ठा sk_buff *skb, u32 info)
अणु
	वापस -ENOENT;
पूर्ण

अटल काष्ठा xfrm_tunnel xfrm_tunnel_handler __पढ़ो_mostly = अणु
	.handler	=	xfrm_tunnel_rcv,
	.err_handler	=	xfrm_tunnel_err,
	.priority	=	4,
पूर्ण;

#अगर IS_ENABLED(CONFIG_IPV6)
अटल काष्ठा xfrm_tunnel xfrm64_tunnel_handler __पढ़ो_mostly = अणु
	.handler	=	xfrm_tunnel_rcv,
	.err_handler	=	xfrm_tunnel_err,
	.priority	=	3,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init ipip_init(व्योम)
अणु
	अगर (xfrm_रेजिस्टर_type(&ipip_type, AF_INET) < 0) अणु
		pr_info("%s: can't add xfrm type\n", __func__);
		वापस -EAGAIN;
	पूर्ण

	अगर (xfrm4_tunnel_रेजिस्टर(&xfrm_tunnel_handler, AF_INET)) अणु
		pr_info("%s: can't add xfrm handler for AF_INET\n", __func__);
		xfrm_unरेजिस्टर_type(&ipip_type, AF_INET);
		वापस -EAGAIN;
	पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (xfrm4_tunnel_रेजिस्टर(&xfrm64_tunnel_handler, AF_INET6)) अणु
		pr_info("%s: can't add xfrm handler for AF_INET6\n", __func__);
		xfrm4_tunnel_deरेजिस्टर(&xfrm_tunnel_handler, AF_INET);
		xfrm_unरेजिस्टर_type(&ipip_type, AF_INET);
		वापस -EAGAIN;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम __निकास ipip_fini(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (xfrm4_tunnel_deरेजिस्टर(&xfrm64_tunnel_handler, AF_INET6))
		pr_info("%s: can't remove xfrm handler for AF_INET6\n",
			__func__);
#पूर्ण_अगर
	अगर (xfrm4_tunnel_deरेजिस्टर(&xfrm_tunnel_handler, AF_INET))
		pr_info("%s: can't remove xfrm handler for AF_INET\n",
			__func__);
	xfrm_unरेजिस्टर_type(&ipip_type, AF_INET);
पूर्ण

module_init(ipip_init);
module_निकास(ipip_fini);
MODULE_LICENSE("GPL");
MODULE_ALIAS_XFRM_TYPE(AF_INET, XFRM_PROTO_IPIP);
