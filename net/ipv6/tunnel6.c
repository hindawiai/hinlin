<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C)2003,2004 USAGI/WIDE Project
 *
 * Authors	Mitsuru KANDA  <mk@linux-ipv6.org>
 *		YOSHIFUJI Hideaki <yoshfuji@linux-ipv6.org>
 */

#घोषणा pr_fmt(fmt) "IPv6: " fmt

#समावेश <linux/icmpv6.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <net/ipv6.h>
#समावेश <net/protocol.h>
#समावेश <net/xfrm.h>

अटल काष्ठा xfrm6_tunnel __rcu *tunnel6_handlers __पढ़ो_mostly;
अटल काष्ठा xfrm6_tunnel __rcu *tunnel46_handlers __पढ़ो_mostly;
अटल काष्ठा xfrm6_tunnel __rcu *tunnelmpls6_handlers __पढ़ो_mostly;
अटल DEFINE_MUTEX(tunnel6_mutex);

अटल अंतरभूत पूर्णांक xfrm6_tunnel_mpls_supported(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_MPLS);
पूर्ण

पूर्णांक xfrm6_tunnel_रेजिस्टर(काष्ठा xfrm6_tunnel *handler, अचिन्हित लघु family)
अणु
	काष्ठा xfrm6_tunnel __rcu **pprev;
	काष्ठा xfrm6_tunnel *t;
	पूर्णांक ret = -EEXIST;
	पूर्णांक priority = handler->priority;

	mutex_lock(&tunnel6_mutex);

	चयन (family) अणु
	हाल AF_INET6:
		pprev = &tunnel6_handlers;
		अवरोध;
	हाल AF_INET:
		pprev = &tunnel46_handlers;
		अवरोध;
	हाल AF_MPLS:
		pprev = &tunnelmpls6_handlers;
		अवरोध;
	शेष:
		जाओ err;
	पूर्ण

	क्रम (; (t = rcu_dereference_रक्षित(*pprev,
			lockdep_is_held(&tunnel6_mutex))) != शून्य;
	     pprev = &t->next) अणु
		अगर (t->priority > priority)
			अवरोध;
		अगर (t->priority == priority)
			जाओ err;
	पूर्ण

	handler->next = *pprev;
	rcu_assign_poपूर्णांकer(*pprev, handler);

	ret = 0;

err:
	mutex_unlock(&tunnel6_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(xfrm6_tunnel_रेजिस्टर);

पूर्णांक xfrm6_tunnel_deरेजिस्टर(काष्ठा xfrm6_tunnel *handler, अचिन्हित लघु family)
अणु
	काष्ठा xfrm6_tunnel __rcu **pprev;
	काष्ठा xfrm6_tunnel *t;
	पूर्णांक ret = -ENOENT;

	mutex_lock(&tunnel6_mutex);

	चयन (family) अणु
	हाल AF_INET6:
		pprev = &tunnel6_handlers;
		अवरोध;
	हाल AF_INET:
		pprev = &tunnel46_handlers;
		अवरोध;
	हाल AF_MPLS:
		pprev = &tunnelmpls6_handlers;
		अवरोध;
	शेष:
		जाओ err;
	पूर्ण

	क्रम (; (t = rcu_dereference_रक्षित(*pprev,
			lockdep_is_held(&tunnel6_mutex))) != शून्य;
	     pprev = &t->next) अणु
		अगर (t == handler) अणु
			*pprev = handler->next;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

err:
	mutex_unlock(&tunnel6_mutex);

	synchronize_net();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(xfrm6_tunnel_deरेजिस्टर);

#घोषणा क्रम_each_tunnel_rcu(head, handler)		\
	क्रम (handler = rcu_dereference(head);		\
	     handler != शून्य;				\
	     handler = rcu_dereference(handler->next))	\

अटल पूर्णांक tunnelmpls6_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा xfrm6_tunnel *handler;

	अगर (!pskb_may_pull(skb, माप(काष्ठा ipv6hdr)))
		जाओ drop;

	क्रम_each_tunnel_rcu(tunnelmpls6_handlers, handler)
		अगर (!handler->handler(skb))
			वापस 0;

	icmpv6_send(skb, ICMPV6_DEST_UNREACH, ICMPV6_PORT_UNREACH, 0);

drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक tunnel6_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा xfrm6_tunnel *handler;

	अगर (!pskb_may_pull(skb, माप(काष्ठा ipv6hdr)))
		जाओ drop;

	क्रम_each_tunnel_rcu(tunnel6_handlers, handler)
		अगर (!handler->handler(skb))
			वापस 0;

	icmpv6_send(skb, ICMPV6_DEST_UNREACH, ICMPV6_PORT_UNREACH, 0);

drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_INET6_XFRM_TUNNEL)
अटल पूर्णांक tunnel6_rcv_cb(काष्ठा sk_buff *skb, u8 proto, पूर्णांक err)
अणु
	काष्ठा xfrm6_tunnel __rcu *head;
	काष्ठा xfrm6_tunnel *handler;
	पूर्णांक ret;

	head = (proto == IPPROTO_IPV6) ? tunnel6_handlers : tunnel46_handlers;

	क्रम_each_tunnel_rcu(head, handler) अणु
		अगर (handler->cb_handler) अणु
			ret = handler->cb_handler(skb, err);
			अगर (ret <= 0)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा xfrm_input_afinfo tunnel6_input_afinfo = अणु
	.family		=	AF_INET6,
	.is_ipip	=	true,
	.callback	=	tunnel6_rcv_cb,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक tunnel46_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा xfrm6_tunnel *handler;

	अगर (!pskb_may_pull(skb, माप(काष्ठा iphdr)))
		जाओ drop;

	क्रम_each_tunnel_rcu(tunnel46_handlers, handler)
		अगर (!handler->handler(skb))
			वापस 0;

	icmpv6_send(skb, ICMPV6_DEST_UNREACH, ICMPV6_PORT_UNREACH, 0);

drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक tunnel6_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
			u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	काष्ठा xfrm6_tunnel *handler;

	क्रम_each_tunnel_rcu(tunnel6_handlers, handler)
		अगर (!handler->err_handler(skb, opt, type, code, offset, info))
			वापस 0;

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक tunnel46_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
			 u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	काष्ठा xfrm6_tunnel *handler;

	क्रम_each_tunnel_rcu(tunnel46_handlers, handler)
		अगर (!handler->err_handler(skb, opt, type, code, offset, info))
			वापस 0;

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक tunnelmpls6_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
			   u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	काष्ठा xfrm6_tunnel *handler;

	क्रम_each_tunnel_rcu(tunnelmpls6_handlers, handler)
		अगर (!handler->err_handler(skb, opt, type, code, offset, info))
			वापस 0;

	वापस -ENOENT;
पूर्ण

अटल स्थिर काष्ठा inet6_protocol tunnel6_protocol = अणु
	.handler	= tunnel6_rcv,
	.err_handler	= tunnel6_err,
	.flags          = INET6_PROTO_NOPOLICY|INET6_PROTO_FINAL,
पूर्ण;

अटल स्थिर काष्ठा inet6_protocol tunnel46_protocol = अणु
	.handler	= tunnel46_rcv,
	.err_handler	= tunnel46_err,
	.flags          = INET6_PROTO_NOPOLICY|INET6_PROTO_FINAL,
पूर्ण;

अटल स्थिर काष्ठा inet6_protocol tunnelmpls6_protocol = अणु
	.handler	= tunnelmpls6_rcv,
	.err_handler	= tunnelmpls6_err,
	.flags          = INET6_PROTO_NOPOLICY|INET6_PROTO_FINAL,
पूर्ण;

अटल पूर्णांक __init tunnel6_init(व्योम)
अणु
	अगर (inet6_add_protocol(&tunnel6_protocol, IPPROTO_IPV6)) अणु
		pr_err("%s: can't add protocol\n", __func__);
		वापस -EAGAIN;
	पूर्ण
	अगर (inet6_add_protocol(&tunnel46_protocol, IPPROTO_IPIP)) अणु
		pr_err("%s: can't add protocol\n", __func__);
		inet6_del_protocol(&tunnel6_protocol, IPPROTO_IPV6);
		वापस -EAGAIN;
	पूर्ण
	अगर (xfrm6_tunnel_mpls_supported() &&
	    inet6_add_protocol(&tunnelmpls6_protocol, IPPROTO_MPLS)) अणु
		pr_err("%s: can't add protocol\n", __func__);
		inet6_del_protocol(&tunnel6_protocol, IPPROTO_IPV6);
		inet6_del_protocol(&tunnel46_protocol, IPPROTO_IPIP);
		वापस -EAGAIN;
	पूर्ण
#अगर IS_ENABLED(CONFIG_INET6_XFRM_TUNNEL)
	अगर (xfrm_input_रेजिस्टर_afinfo(&tunnel6_input_afinfo)) अणु
		pr_err("%s: can't add input afinfo\n", __func__);
		inet6_del_protocol(&tunnel6_protocol, IPPROTO_IPV6);
		inet6_del_protocol(&tunnel46_protocol, IPPROTO_IPIP);
		अगर (xfrm6_tunnel_mpls_supported())
			inet6_del_protocol(&tunnelmpls6_protocol, IPPROTO_MPLS);
		वापस -EAGAIN;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम __निकास tunnel6_fini(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_INET6_XFRM_TUNNEL)
	अगर (xfrm_input_unरेजिस्टर_afinfo(&tunnel6_input_afinfo))
		pr_err("%s: can't remove input afinfo\n", __func__);
#पूर्ण_अगर
	अगर (inet6_del_protocol(&tunnel46_protocol, IPPROTO_IPIP))
		pr_err("%s: can't remove protocol\n", __func__);
	अगर (inet6_del_protocol(&tunnel6_protocol, IPPROTO_IPV6))
		pr_err("%s: can't remove protocol\n", __func__);
	अगर (xfrm6_tunnel_mpls_supported() &&
	    inet6_del_protocol(&tunnelmpls6_protocol, IPPROTO_MPLS))
		pr_err("%s: can't remove protocol\n", __func__);
पूर्ण

module_init(tunnel6_init);
module_निकास(tunnel6_fini);
MODULE_LICENSE("GPL");
