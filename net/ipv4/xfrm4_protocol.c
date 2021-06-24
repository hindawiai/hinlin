<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* xfrm4_protocol.c - Generic xfrm protocol multiplexer.
 *
 * Copyright (C) 2013 secunet Security Networks AG
 *
 * Author:
 * Steffen Klनिश्चित <steffen.klनिश्चित@secunet.com>
 *
 * Based on:
 * net/ipv4/tunnel4.c
 */

#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/skbuff.h>
#समावेश <net/icmp.h>
#समावेश <net/ip.h>
#समावेश <net/protocol.h>
#समावेश <net/xfrm.h>

अटल काष्ठा xfrm4_protocol __rcu *esp4_handlers __पढ़ो_mostly;
अटल काष्ठा xfrm4_protocol __rcu *ah4_handlers __पढ़ो_mostly;
अटल काष्ठा xfrm4_protocol __rcu *ipcomp4_handlers __पढ़ो_mostly;
अटल DEFINE_MUTEX(xfrm4_protocol_mutex);

अटल अंतरभूत काष्ठा xfrm4_protocol __rcu **proto_handlers(u8 protocol)
अणु
	चयन (protocol) अणु
	हाल IPPROTO_ESP:
		वापस &esp4_handlers;
	हाल IPPROTO_AH:
		वापस &ah4_handlers;
	हाल IPPROTO_COMP:
		वापस &ipcomp4_handlers;
	पूर्ण

	वापस शून्य;
पूर्ण

#घोषणा क्रम_each_protocol_rcu(head, handler)		\
	क्रम (handler = rcu_dereference(head);		\
	     handler != शून्य;				\
	     handler = rcu_dereference(handler->next))	\

अटल पूर्णांक xfrm4_rcv_cb(काष्ठा sk_buff *skb, u8 protocol, पूर्णांक err)
अणु
	पूर्णांक ret;
	काष्ठा xfrm4_protocol *handler;
	काष्ठा xfrm4_protocol __rcu **head = proto_handlers(protocol);

	अगर (!head)
		वापस 0;

	क्रम_each_protocol_rcu(*head, handler)
		अगर ((ret = handler->cb_handler(skb, err)) <= 0)
			वापस ret;

	वापस 0;
पूर्ण

पूर्णांक xfrm4_rcv_encap(काष्ठा sk_buff *skb, पूर्णांक nexthdr, __be32 spi,
		    पूर्णांक encap_type)
अणु
	पूर्णांक ret;
	काष्ठा xfrm4_protocol *handler;
	काष्ठा xfrm4_protocol __rcu **head = proto_handlers(nexthdr);

	XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip4 = शून्य;
	XFRM_SPI_SKB_CB(skb)->family = AF_INET;
	XFRM_SPI_SKB_CB(skb)->daddroff = दुरत्व(काष्ठा iphdr, daddr);

	अगर (!head)
		जाओ out;

	अगर (!skb_dst(skb)) अणु
		स्थिर काष्ठा iphdr *iph = ip_hdr(skb);

		अगर (ip_route_input_noref(skb, iph->daddr, iph->saddr,
					 iph->tos, skb->dev))
			जाओ drop;
	पूर्ण

	क्रम_each_protocol_rcu(*head, handler)
		अगर ((ret = handler->input_handler(skb, nexthdr, spi, encap_type)) != -EINVAL)
			वापस ret;

out:
	icmp_send(skb, ICMP_DEST_UNREACH, ICMP_PORT_UNREACH, 0);

drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(xfrm4_rcv_encap);

अटल पूर्णांक xfrm4_esp_rcv(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;
	काष्ठा xfrm4_protocol *handler;

	XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip4 = शून्य;

	क्रम_each_protocol_rcu(esp4_handlers, handler)
		अगर ((ret = handler->handler(skb)) != -EINVAL)
			वापस ret;

	icmp_send(skb, ICMP_DEST_UNREACH, ICMP_PORT_UNREACH, 0);

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm4_esp_err(काष्ठा sk_buff *skb, u32 info)
अणु
	काष्ठा xfrm4_protocol *handler;

	क्रम_each_protocol_rcu(esp4_handlers, handler)
		अगर (!handler->err_handler(skb, info))
			वापस 0;

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक xfrm4_ah_rcv(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;
	काष्ठा xfrm4_protocol *handler;

	XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip4 = शून्य;

	क्रम_each_protocol_rcu(ah4_handlers, handler)
		अगर ((ret = handler->handler(skb)) != -EINVAL)
			वापस ret;

	icmp_send(skb, ICMP_DEST_UNREACH, ICMP_PORT_UNREACH, 0);

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm4_ah_err(काष्ठा sk_buff *skb, u32 info)
अणु
	काष्ठा xfrm4_protocol *handler;

	क्रम_each_protocol_rcu(ah4_handlers, handler)
		अगर (!handler->err_handler(skb, info))
			वापस 0;

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक xfrm4_ipcomp_rcv(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;
	काष्ठा xfrm4_protocol *handler;

	XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip4 = शून्य;

	क्रम_each_protocol_rcu(ipcomp4_handlers, handler)
		अगर ((ret = handler->handler(skb)) != -EINVAL)
			वापस ret;

	icmp_send(skb, ICMP_DEST_UNREACH, ICMP_PORT_UNREACH, 0);

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm4_ipcomp_err(काष्ठा sk_buff *skb, u32 info)
अणु
	काष्ठा xfrm4_protocol *handler;

	क्रम_each_protocol_rcu(ipcomp4_handlers, handler)
		अगर (!handler->err_handler(skb, info))
			वापस 0;

	वापस -ENOENT;
पूर्ण

अटल स्थिर काष्ठा net_protocol esp4_protocol = अणु
	.handler	=	xfrm4_esp_rcv,
	.err_handler	=	xfrm4_esp_err,
	.no_policy	=	1,
	.netns_ok	=	1,
पूर्ण;

अटल स्थिर काष्ठा net_protocol ah4_protocol = अणु
	.handler	=	xfrm4_ah_rcv,
	.err_handler	=	xfrm4_ah_err,
	.no_policy	=	1,
	.netns_ok	=	1,
पूर्ण;

अटल स्थिर काष्ठा net_protocol ipcomp4_protocol = अणु
	.handler	=	xfrm4_ipcomp_rcv,
	.err_handler	=	xfrm4_ipcomp_err,
	.no_policy	=	1,
	.netns_ok	=	1,
पूर्ण;

अटल स्थिर काष्ठा xfrm_input_afinfo xfrm4_input_afinfo = अणु
	.family		=	AF_INET,
	.callback	=	xfrm4_rcv_cb,
पूर्ण;

अटल अंतरभूत स्थिर काष्ठा net_protocol *netproto(अचिन्हित अक्षर protocol)
अणु
	चयन (protocol) अणु
	हाल IPPROTO_ESP:
		वापस &esp4_protocol;
	हाल IPPROTO_AH:
		वापस &ah4_protocol;
	हाल IPPROTO_COMP:
		वापस &ipcomp4_protocol;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक xfrm4_protocol_रेजिस्टर(काष्ठा xfrm4_protocol *handler,
			    अचिन्हित अक्षर protocol)
अणु
	काष्ठा xfrm4_protocol __rcu **pprev;
	काष्ठा xfrm4_protocol *t;
	bool add_netproto = false;
	पूर्णांक ret = -EEXIST;
	पूर्णांक priority = handler->priority;

	अगर (!proto_handlers(protocol) || !netproto(protocol))
		वापस -EINVAL;

	mutex_lock(&xfrm4_protocol_mutex);

	अगर (!rcu_dereference_रक्षित(*proto_handlers(protocol),
				       lockdep_is_held(&xfrm4_protocol_mutex)))
		add_netproto = true;

	क्रम (pprev = proto_handlers(protocol);
	     (t = rcu_dereference_रक्षित(*pprev,
			lockdep_is_held(&xfrm4_protocol_mutex))) != शून्य;
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
	mutex_unlock(&xfrm4_protocol_mutex);

	अगर (add_netproto) अणु
		अगर (inet_add_protocol(netproto(protocol), protocol)) अणु
			pr_err("%s: can't add protocol\n", __func__);
			ret = -EAGAIN;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(xfrm4_protocol_रेजिस्टर);

पूर्णांक xfrm4_protocol_deरेजिस्टर(काष्ठा xfrm4_protocol *handler,
			      अचिन्हित अक्षर protocol)
अणु
	काष्ठा xfrm4_protocol __rcu **pprev;
	काष्ठा xfrm4_protocol *t;
	पूर्णांक ret = -ENOENT;

	अगर (!proto_handlers(protocol) || !netproto(protocol))
		वापस -EINVAL;

	mutex_lock(&xfrm4_protocol_mutex);

	क्रम (pprev = proto_handlers(protocol);
	     (t = rcu_dereference_रक्षित(*pprev,
			lockdep_is_held(&xfrm4_protocol_mutex))) != शून्य;
	     pprev = &t->next) अणु
		अगर (t == handler) अणु
			*pprev = handler->next;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!rcu_dereference_रक्षित(*proto_handlers(protocol),
				       lockdep_is_held(&xfrm4_protocol_mutex))) अणु
		अगर (inet_del_protocol(netproto(protocol), protocol) < 0) अणु
			pr_err("%s: can't remove protocol\n", __func__);
			ret = -EAGAIN;
		पूर्ण
	पूर्ण

	mutex_unlock(&xfrm4_protocol_mutex);

	synchronize_net();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(xfrm4_protocol_deरेजिस्टर);

व्योम __init xfrm4_protocol_init(व्योम)
अणु
	xfrm_input_रेजिस्टर_afinfo(&xfrm4_input_afinfo);
पूर्ण
EXPORT_SYMBOL(xfrm4_protocol_init);
