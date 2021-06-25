<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* xfrm6_protocol.c - Generic xfrm protocol multiplexer क्रम ipv6.
 *
 * Copyright (C) 2013 secunet Security Networks AG
 *
 * Author:
 * Steffen Klनिश्चित <steffen.klनिश्चित@secunet.com>
 *
 * Based on:
 * net/ipv4/xfrm4_protocol.c
 */

#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/icmpv6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/ipv6.h>
#समावेश <net/protocol.h>
#समावेश <net/xfrm.h>

अटल काष्ठा xfrm6_protocol __rcu *esp6_handlers __पढ़ो_mostly;
अटल काष्ठा xfrm6_protocol __rcu *ah6_handlers __पढ़ो_mostly;
अटल काष्ठा xfrm6_protocol __rcu *ipcomp6_handlers __पढ़ो_mostly;
अटल DEFINE_MUTEX(xfrm6_protocol_mutex);

अटल अंतरभूत काष्ठा xfrm6_protocol __rcu **proto_handlers(u8 protocol)
अणु
	चयन (protocol) अणु
	हाल IPPROTO_ESP:
		वापस &esp6_handlers;
	हाल IPPROTO_AH:
		वापस &ah6_handlers;
	हाल IPPROTO_COMP:
		वापस &ipcomp6_handlers;
	पूर्ण

	वापस शून्य;
पूर्ण

#घोषणा क्रम_each_protocol_rcu(head, handler)		\
	क्रम (handler = rcu_dereference(head);		\
	     handler != शून्य;				\
	     handler = rcu_dereference(handler->next))	\

अटल पूर्णांक xfrm6_rcv_cb(काष्ठा sk_buff *skb, u8 protocol, पूर्णांक err)
अणु
	पूर्णांक ret;
	काष्ठा xfrm6_protocol *handler;
	काष्ठा xfrm6_protocol __rcu **head = proto_handlers(protocol);

	अगर (!head)
		वापस 0;

	क्रम_each_protocol_rcu(*proto_handlers(protocol), handler)
		अगर ((ret = handler->cb_handler(skb, err)) <= 0)
			वापस ret;

	वापस 0;
पूर्ण

पूर्णांक xfrm6_rcv_encap(काष्ठा sk_buff *skb, पूर्णांक nexthdr, __be32 spi,
		    पूर्णांक encap_type)
अणु
	पूर्णांक ret;
	काष्ठा xfrm6_protocol *handler;
	काष्ठा xfrm6_protocol __rcu **head = proto_handlers(nexthdr);

	XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip6 = शून्य;
	XFRM_SPI_SKB_CB(skb)->family = AF_INET6;
	XFRM_SPI_SKB_CB(skb)->daddroff = दुरत्व(काष्ठा ipv6hdr, daddr);

	अगर (!head)
		जाओ out;

	अगर (!skb_dst(skb)) अणु
		स्थिर काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);
		पूर्णांक flags = RT6_LOOKUP_F_HAS_SADDR;
		काष्ठा dst_entry *dst;
		काष्ठा flowi6 fl6 = अणु
			.flowi6_iअगर   = skb->dev->अगरindex,
			.daddr        = ip6h->daddr,
			.saddr        = ip6h->saddr,
			.flowlabel    = ip6_flowinfo(ip6h),
			.flowi6_mark  = skb->mark,
			.flowi6_proto = ip6h->nexthdr,
		पूर्ण;

		dst = ip6_route_input_lookup(dev_net(skb->dev), skb->dev, &fl6,
					     skb, flags);
		अगर (dst->error)
			जाओ drop;
		skb_dst_set(skb, dst);
	पूर्ण

	क्रम_each_protocol_rcu(*head, handler)
		अगर ((ret = handler->input_handler(skb, nexthdr, spi, encap_type)) != -EINVAL)
			वापस ret;

out:
	icmpv6_send(skb, ICMPV6_DEST_UNREACH, ICMPV6_PORT_UNREACH, 0);

drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(xfrm6_rcv_encap);

अटल पूर्णांक xfrm6_esp_rcv(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;
	काष्ठा xfrm6_protocol *handler;

	XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip6 = शून्य;

	क्रम_each_protocol_rcu(esp6_handlers, handler)
		अगर ((ret = handler->handler(skb)) != -EINVAL)
			वापस ret;

	icmpv6_send(skb, ICMPV6_DEST_UNREACH, ICMPV6_PORT_UNREACH, 0);

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm6_esp_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
			  u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	काष्ठा xfrm6_protocol *handler;

	क्रम_each_protocol_rcu(esp6_handlers, handler)
		अगर (!handler->err_handler(skb, opt, type, code, offset, info))
			वापस 0;

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक xfrm6_ah_rcv(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;
	काष्ठा xfrm6_protocol *handler;

	XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip6 = शून्य;

	क्रम_each_protocol_rcu(ah6_handlers, handler)
		अगर ((ret = handler->handler(skb)) != -EINVAL)
			वापस ret;

	icmpv6_send(skb, ICMPV6_DEST_UNREACH, ICMPV6_PORT_UNREACH, 0);

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm6_ah_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
			 u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	काष्ठा xfrm6_protocol *handler;

	क्रम_each_protocol_rcu(ah6_handlers, handler)
		अगर (!handler->err_handler(skb, opt, type, code, offset, info))
			वापस 0;

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक xfrm6_ipcomp_rcv(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;
	काष्ठा xfrm6_protocol *handler;

	XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip6 = शून्य;

	क्रम_each_protocol_rcu(ipcomp6_handlers, handler)
		अगर ((ret = handler->handler(skb)) != -EINVAL)
			वापस ret;

	icmpv6_send(skb, ICMPV6_DEST_UNREACH, ICMPV6_PORT_UNREACH, 0);

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm6_ipcomp_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
			     u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	काष्ठा xfrm6_protocol *handler;

	क्रम_each_protocol_rcu(ipcomp6_handlers, handler)
		अगर (!handler->err_handler(skb, opt, type, code, offset, info))
			वापस 0;

	वापस -ENOENT;
पूर्ण

अटल स्थिर काष्ठा inet6_protocol esp6_protocol = अणु
	.handler	=	xfrm6_esp_rcv,
	.err_handler	=	xfrm6_esp_err,
	.flags		=	INET6_PROTO_NOPOLICY,
पूर्ण;

अटल स्थिर काष्ठा inet6_protocol ah6_protocol = अणु
	.handler	=	xfrm6_ah_rcv,
	.err_handler	=	xfrm6_ah_err,
	.flags		=	INET6_PROTO_NOPOLICY,
पूर्ण;

अटल स्थिर काष्ठा inet6_protocol ipcomp6_protocol = अणु
	.handler	=	xfrm6_ipcomp_rcv,
	.err_handler	=	xfrm6_ipcomp_err,
	.flags		=	INET6_PROTO_NOPOLICY,
पूर्ण;

अटल स्थिर काष्ठा xfrm_input_afinfo xfrm6_input_afinfo = अणु
	.family		=	AF_INET6,
	.callback	=	xfrm6_rcv_cb,
पूर्ण;

अटल अंतरभूत स्थिर काष्ठा inet6_protocol *netproto(अचिन्हित अक्षर protocol)
अणु
	चयन (protocol) अणु
	हाल IPPROTO_ESP:
		वापस &esp6_protocol;
	हाल IPPROTO_AH:
		वापस &ah6_protocol;
	हाल IPPROTO_COMP:
		वापस &ipcomp6_protocol;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक xfrm6_protocol_रेजिस्टर(काष्ठा xfrm6_protocol *handler,
			    अचिन्हित अक्षर protocol)
अणु
	काष्ठा xfrm6_protocol __rcu **pprev;
	काष्ठा xfrm6_protocol *t;
	bool add_netproto = false;
	पूर्णांक ret = -EEXIST;
	पूर्णांक priority = handler->priority;

	अगर (!proto_handlers(protocol) || !netproto(protocol))
		वापस -EINVAL;

	mutex_lock(&xfrm6_protocol_mutex);

	अगर (!rcu_dereference_रक्षित(*proto_handlers(protocol),
				       lockdep_is_held(&xfrm6_protocol_mutex)))
		add_netproto = true;

	क्रम (pprev = proto_handlers(protocol);
	     (t = rcu_dereference_रक्षित(*pprev,
			lockdep_is_held(&xfrm6_protocol_mutex))) != शून्य;
	     pprev = &t->next) अणु
		अगर (t->priority < priority)
			अवरोध;
		अगर (t->priority == priority)
			जाओ err;
	पूर्ण

	handler->next = *pprev;
	rcu_assign_poपूर्णांकer(*pprev, handler);

	ret = 0;

err:
	mutex_unlock(&xfrm6_protocol_mutex);

	अगर (add_netproto) अणु
		अगर (inet6_add_protocol(netproto(protocol), protocol)) अणु
			pr_err("%s: can't add protocol\n", __func__);
			ret = -EAGAIN;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(xfrm6_protocol_रेजिस्टर);

पूर्णांक xfrm6_protocol_deरेजिस्टर(काष्ठा xfrm6_protocol *handler,
			      अचिन्हित अक्षर protocol)
अणु
	काष्ठा xfrm6_protocol __rcu **pprev;
	काष्ठा xfrm6_protocol *t;
	पूर्णांक ret = -ENOENT;

	अगर (!proto_handlers(protocol) || !netproto(protocol))
		वापस -EINVAL;

	mutex_lock(&xfrm6_protocol_mutex);

	क्रम (pprev = proto_handlers(protocol);
	     (t = rcu_dereference_रक्षित(*pprev,
			lockdep_is_held(&xfrm6_protocol_mutex))) != शून्य;
	     pprev = &t->next) अणु
		अगर (t == handler) अणु
			*pprev = handler->next;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!rcu_dereference_रक्षित(*proto_handlers(protocol),
				       lockdep_is_held(&xfrm6_protocol_mutex))) अणु
		अगर (inet6_del_protocol(netproto(protocol), protocol) < 0) अणु
			pr_err("%s: can't remove protocol\n", __func__);
			ret = -EAGAIN;
		पूर्ण
	पूर्ण

	mutex_unlock(&xfrm6_protocol_mutex);

	synchronize_net();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(xfrm6_protocol_deरेजिस्टर);

पूर्णांक __init xfrm6_protocol_init(व्योम)
अणु
	वापस xfrm_input_रेजिस्टर_afinfo(&xfrm6_input_afinfo);
पूर्ण

व्योम xfrm6_protocol_fini(व्योम)
अणु
	xfrm_input_unरेजिस्टर_afinfo(&xfrm6_input_afinfo);
पूर्ण
