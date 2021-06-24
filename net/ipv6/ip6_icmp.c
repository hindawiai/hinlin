<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/export.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/mutex.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/spinlock.h>

#समावेश <net/ipv6.h>

#अगर IS_ENABLED(CONFIG_IPV6)

#अगर !IS_BUILTIN(CONFIG_IPV6)

अटल ip6_icmp_send_t __rcu *ip6_icmp_send;

पूर्णांक inet6_रेजिस्टर_icmp_sender(ip6_icmp_send_t *fn)
अणु
	वापस (cmpxchg((ip6_icmp_send_t **)&ip6_icmp_send, शून्य, fn) == शून्य) ?
		0 : -EBUSY;
पूर्ण
EXPORT_SYMBOL(inet6_रेजिस्टर_icmp_sender);

पूर्णांक inet6_unरेजिस्टर_icmp_sender(ip6_icmp_send_t *fn)
अणु
	पूर्णांक ret;

	ret = (cmpxchg((ip6_icmp_send_t **)&ip6_icmp_send, fn, शून्य) == fn) ?
	      0 : -EINVAL;

	synchronize_net();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(inet6_unरेजिस्टर_icmp_sender);

व्योम __icmpv6_send(काष्ठा sk_buff *skb, u8 type, u8 code, __u32 info,
		   स्थिर काष्ठा inet6_skb_parm *parm)
अणु
	ip6_icmp_send_t *send;

	rcu_पढ़ो_lock();
	send = rcu_dereference(ip6_icmp_send);
	अगर (send)
		send(skb, type, code, info, शून्य, parm);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(__icmpv6_send);
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_NF_NAT)
#समावेश <net/netfilter/nf_conntrack.h>
व्योम icmpv6_nकरो_send(काष्ठा sk_buff *skb_in, u8 type, u8 code, __u32 info)
अणु
	काष्ठा inet6_skb_parm parm = अणु 0 पूर्ण;
	काष्ठा sk_buff *cloned_skb = शून्य;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा in6_addr orig_ip;
	काष्ठा nf_conn *ct;

	ct = nf_ct_get(skb_in, &ctinfo);
	अगर (!ct || !(ct->status & IPS_SRC_NAT)) अणु
		__icmpv6_send(skb_in, type, code, info, &parm);
		वापस;
	पूर्ण

	अगर (skb_shared(skb_in))
		skb_in = cloned_skb = skb_clone(skb_in, GFP_ATOMIC);

	अगर (unlikely(!skb_in || skb_network_header(skb_in) < skb_in->head ||
	    (skb_network_header(skb_in) + माप(काष्ठा ipv6hdr)) >
	    skb_tail_poपूर्णांकer(skb_in) || skb_ensure_writable(skb_in,
	    skb_network_offset(skb_in) + माप(काष्ठा ipv6hdr))))
		जाओ out;

	orig_ip = ipv6_hdr(skb_in)->saddr;
	ipv6_hdr(skb_in)->saddr = ct->tuplehash[0].tuple.src.u3.in6;
	__icmpv6_send(skb_in, type, code, info, &parm);
	ipv6_hdr(skb_in)->saddr = orig_ip;
out:
	consume_skb(cloned_skb);
पूर्ण
EXPORT_SYMBOL(icmpv6_nकरो_send);
#पूर्ण_अगर
#पूर्ण_अगर
