<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* tunnel4.c: Generic IP tunnel transक्रमmer.
 *
 * Copyright (C) 2003 David S. Miller (davem@redhat.com)
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mpls.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <net/icmp.h>
#समावेश <net/ip.h>
#समावेश <net/protocol.h>
#समावेश <net/xfrm.h>

अटल काष्ठा xfrm_tunnel __rcu *tunnel4_handlers __पढ़ो_mostly;
अटल काष्ठा xfrm_tunnel __rcu *tunnel64_handlers __पढ़ो_mostly;
अटल काष्ठा xfrm_tunnel __rcu *tunnelmpls4_handlers __पढ़ो_mostly;
अटल DEFINE_MUTEX(tunnel4_mutex);

अटल अंतरभूत काष्ठा xfrm_tunnel __rcu **fam_handlers(अचिन्हित लघु family)
अणु
	वापस (family == AF_INET) ? &tunnel4_handlers :
		(family == AF_INET6) ? &tunnel64_handlers :
		&tunnelmpls4_handlers;
पूर्ण

पूर्णांक xfrm4_tunnel_रेजिस्टर(काष्ठा xfrm_tunnel *handler, अचिन्हित लघु family)
अणु
	काष्ठा xfrm_tunnel __rcu **pprev;
	काष्ठा xfrm_tunnel *t;

	पूर्णांक ret = -EEXIST;
	पूर्णांक priority = handler->priority;

	mutex_lock(&tunnel4_mutex);

	क्रम (pprev = fam_handlers(family);
	     (t = rcu_dereference_रक्षित(*pprev,
			lockdep_is_held(&tunnel4_mutex))) != शून्य;
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
	mutex_unlock(&tunnel4_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(xfrm4_tunnel_रेजिस्टर);

पूर्णांक xfrm4_tunnel_deरेजिस्टर(काष्ठा xfrm_tunnel *handler, अचिन्हित लघु family)
अणु
	काष्ठा xfrm_tunnel __rcu **pprev;
	काष्ठा xfrm_tunnel *t;
	पूर्णांक ret = -ENOENT;

	mutex_lock(&tunnel4_mutex);

	क्रम (pprev = fam_handlers(family);
	     (t = rcu_dereference_रक्षित(*pprev,
			lockdep_is_held(&tunnel4_mutex))) != शून्य;
	     pprev = &t->next) अणु
		अगर (t == handler) अणु
			*pprev = handler->next;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&tunnel4_mutex);

	synchronize_net();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(xfrm4_tunnel_deरेजिस्टर);

#घोषणा क्रम_each_tunnel_rcu(head, handler)		\
	क्रम (handler = rcu_dereference(head);		\
	     handler != शून्य;				\
	     handler = rcu_dereference(handler->next))	\

अटल पूर्णांक tunnel4_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा xfrm_tunnel *handler;

	अगर (!pskb_may_pull(skb, माप(काष्ठा iphdr)))
		जाओ drop;

	क्रम_each_tunnel_rcu(tunnel4_handlers, handler)
		अगर (!handler->handler(skb))
			वापस 0;

	icmp_send(skb, ICMP_DEST_UNREACH, ICMP_PORT_UNREACH, 0);

drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_INET_XFRM_TUNNEL)
अटल पूर्णांक tunnel4_rcv_cb(काष्ठा sk_buff *skb, u8 proto, पूर्णांक err)
अणु
	काष्ठा xfrm_tunnel __rcu *head;
	काष्ठा xfrm_tunnel *handler;
	पूर्णांक ret;

	head = (proto == IPPROTO_IPIP) ? tunnel4_handlers : tunnel64_handlers;

	क्रम_each_tunnel_rcu(head, handler) अणु
		अगर (handler->cb_handler) अणु
			ret = handler->cb_handler(skb, err);
			अगर (ret <= 0)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा xfrm_input_afinfo tunnel4_input_afinfo = अणु
	.family		=	AF_INET,
	.is_ipip	=	true,
	.callback	=	tunnel4_rcv_cb,
पूर्ण;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक tunnel64_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा xfrm_tunnel *handler;

	अगर (!pskb_may_pull(skb, माप(काष्ठा ipv6hdr)))
		जाओ drop;

	क्रम_each_tunnel_rcu(tunnel64_handlers, handler)
		अगर (!handler->handler(skb))
			वापस 0;

	icmp_send(skb, ICMP_DEST_UNREACH, ICMP_PORT_UNREACH, 0);

drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_MPLS)
अटल पूर्णांक tunnelmpls4_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा xfrm_tunnel *handler;

	अगर (!pskb_may_pull(skb, माप(काष्ठा mpls_label)))
		जाओ drop;

	क्रम_each_tunnel_rcu(tunnelmpls4_handlers, handler)
		अगर (!handler->handler(skb))
			वापस 0;

	icmp_send(skb, ICMP_DEST_UNREACH, ICMP_PORT_UNREACH, 0);

drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tunnel4_err(काष्ठा sk_buff *skb, u32 info)
अणु
	काष्ठा xfrm_tunnel *handler;

	क्रम_each_tunnel_rcu(tunnel4_handlers, handler)
		अगर (!handler->err_handler(skb, info))
			वापस 0;

	वापस -ENOENT;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक tunnel64_err(काष्ठा sk_buff *skb, u32 info)
अणु
	काष्ठा xfrm_tunnel *handler;

	क्रम_each_tunnel_rcu(tunnel64_handlers, handler)
		अगर (!handler->err_handler(skb, info))
			वापस 0;

	वापस -ENOENT;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_MPLS)
अटल पूर्णांक tunnelmpls4_err(काष्ठा sk_buff *skb, u32 info)
अणु
	काष्ठा xfrm_tunnel *handler;

	क्रम_each_tunnel_rcu(tunnelmpls4_handlers, handler)
		अगर (!handler->err_handler(skb, info))
			वापस 0;

	वापस -ENOENT;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा net_protocol tunnel4_protocol = अणु
	.handler	=	tunnel4_rcv,
	.err_handler	=	tunnel4_err,
	.no_policy	=	1,
	.netns_ok	=	1,
पूर्ण;

#अगर IS_ENABLED(CONFIG_IPV6)
अटल स्थिर काष्ठा net_protocol tunnel64_protocol = अणु
	.handler	=	tunnel64_rcv,
	.err_handler	=	tunnel64_err,
	.no_policy	=	1,
	.netns_ok	=	1,
पूर्ण;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_MPLS)
अटल स्थिर काष्ठा net_protocol tunnelmpls4_protocol = अणु
	.handler	=	tunnelmpls4_rcv,
	.err_handler	=	tunnelmpls4_err,
	.no_policy	=	1,
	.netns_ok	=	1,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init tunnel4_init(व्योम)
अणु
	अगर (inet_add_protocol(&tunnel4_protocol, IPPROTO_IPIP))
		जाओ err;
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (inet_add_protocol(&tunnel64_protocol, IPPROTO_IPV6)) अणु
		inet_del_protocol(&tunnel4_protocol, IPPROTO_IPIP);
		जाओ err;
	पूर्ण
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_MPLS)
	अगर (inet_add_protocol(&tunnelmpls4_protocol, IPPROTO_MPLS)) अणु
		inet_del_protocol(&tunnel4_protocol, IPPROTO_IPIP);
#अगर IS_ENABLED(CONFIG_IPV6)
		inet_del_protocol(&tunnel64_protocol, IPPROTO_IPV6);
#पूर्ण_अगर
		जाओ err;
	पूर्ण
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_INET_XFRM_TUNNEL)
	अगर (xfrm_input_रेजिस्टर_afinfo(&tunnel4_input_afinfo)) अणु
		inet_del_protocol(&tunnel4_protocol, IPPROTO_IPIP);
#अगर IS_ENABLED(CONFIG_IPV6)
		inet_del_protocol(&tunnel64_protocol, IPPROTO_IPV6);
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_MPLS)
		inet_del_protocol(&tunnelmpls4_protocol, IPPROTO_MPLS);
#पूर्ण_अगर
		जाओ err;
	पूर्ण
#पूर्ण_अगर
	वापस 0;

err:
	pr_err("%s: can't add protocol\n", __func__);
	वापस -EAGAIN;
पूर्ण

अटल व्योम __निकास tunnel4_fini(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_INET_XFRM_TUNNEL)
	अगर (xfrm_input_unरेजिस्टर_afinfo(&tunnel4_input_afinfo))
		pr_err("tunnel4 close: can't remove input afinfo\n");
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_MPLS)
	अगर (inet_del_protocol(&tunnelmpls4_protocol, IPPROTO_MPLS))
		pr_err("tunnelmpls4 close: can't remove protocol\n");
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (inet_del_protocol(&tunnel64_protocol, IPPROTO_IPV6))
		pr_err("tunnel64 close: can't remove protocol\n");
#पूर्ण_अगर
	अगर (inet_del_protocol(&tunnel4_protocol, IPPROTO_IPIP))
		pr_err("tunnel4 close: can't remove protocol\n");
पूर्ण

module_init(tunnel4_init);
module_निकास(tunnel4_fini);
MODULE_LICENSE("GPL");
