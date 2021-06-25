<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <net/netfilter/nf_tproxy.h>
#समावेश <linux/module.h>
#समावेश <net/inet6_hashtables.h>
#समावेश <net/addrconf.h>
#समावेश <net/udp.h>
#समावेश <net/tcp.h>

स्थिर काष्ठा in6_addr *
nf_tproxy_laddr6(काष्ठा sk_buff *skb, स्थिर काष्ठा in6_addr *user_laddr,
	      स्थिर काष्ठा in6_addr *daddr)
अणु
	काष्ठा inet6_dev *indev;
	काष्ठा inet6_अगरaddr *अगरa;
	काष्ठा in6_addr *laddr;

	अगर (!ipv6_addr_any(user_laddr))
		वापस user_laddr;
	laddr = शून्य;

	indev = __in6_dev_get(skb->dev);
	अगर (indev) अणु
		पढ़ो_lock_bh(&indev->lock);
		list_क्रम_each_entry(अगरa, &indev->addr_list, अगर_list) अणु
			अगर (अगरa->flags & (IFA_F_TENTATIVE | IFA_F_DEPRECATED))
				जारी;

			laddr = &अगरa->addr;
			अवरोध;
		पूर्ण
		पढ़ो_unlock_bh(&indev->lock);
	पूर्ण

	वापस laddr ? laddr : daddr;
पूर्ण
EXPORT_SYMBOL_GPL(nf_tproxy_laddr6);

काष्ठा sock *
nf_tproxy_handle_समय_रुको6(काष्ठा sk_buff *skb, पूर्णांक tproto, पूर्णांक thoff,
			 काष्ठा net *net,
			 स्थिर काष्ठा in6_addr *laddr,
			 स्थिर __be16 lport,
			 काष्ठा sock *sk)
अणु
	स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	काष्ठा tcphdr _hdr, *hp;

	hp = skb_header_poपूर्णांकer(skb, thoff, माप(_hdr), &_hdr);
	अगर (hp == शून्य) अणु
		inet_twsk_put(inet_twsk(sk));
		वापस शून्य;
	पूर्ण

	अगर (hp->syn && !hp->rst && !hp->ack && !hp->fin) अणु
		/* SYN to a TIME_WAIT socket, we'd rather redirect it
		 * to a listener socket अगर there's one */
		काष्ठा sock *sk2;

		sk2 = nf_tproxy_get_sock_v6(net, skb, thoff, tproto,
					    &iph->saddr,
					    nf_tproxy_laddr6(skb, laddr, &iph->daddr),
					    hp->source,
					    lport ? lport : hp->dest,
					    skb->dev, NF_TPROXY_LOOKUP_LISTENER);
		अगर (sk2) अणु
			inet_twsk_deschedule_put(inet_twsk(sk));
			sk = sk2;
		पूर्ण
	पूर्ण

	वापस sk;
पूर्ण
EXPORT_SYMBOL_GPL(nf_tproxy_handle_समय_रुको6);

काष्ठा sock *
nf_tproxy_get_sock_v6(काष्ठा net *net, काष्ठा sk_buff *skb, पूर्णांक thoff,
		      स्थिर u8 protocol,
		      स्थिर काष्ठा in6_addr *saddr, स्थिर काष्ठा in6_addr *daddr,
		      स्थिर __be16 sport, स्थिर __be16 dport,
		      स्थिर काष्ठा net_device *in,
		      स्थिर क्रमागत nf_tproxy_lookup_t lookup_type)
अणु
	काष्ठा sock *sk;

	चयन (protocol) अणु
	हाल IPPROTO_TCP: अणु
		काष्ठा tcphdr _hdr, *hp;

		hp = skb_header_poपूर्णांकer(skb, thoff,
					माप(काष्ठा tcphdr), &_hdr);
		अगर (hp == शून्य)
			वापस शून्य;

		चयन (lookup_type) अणु
		हाल NF_TPROXY_LOOKUP_LISTENER:
			sk = inet6_lookup_listener(net, &tcp_hashinfo, skb,
						   thoff + __tcp_hdrlen(hp),
						   saddr, sport,
						   daddr, ntohs(dport),
						   in->अगरindex, 0);

			अगर (sk && !refcount_inc_not_zero(&sk->sk_refcnt))
				sk = शून्य;
			/* NOTE: we वापस listeners even अगर bound to
			 * 0.0.0.0, those are filtered out in
			 * xt_socket, since xt_TPROXY needs 0 bound
			 * listeners too
			 */
			अवरोध;
		हाल NF_TPROXY_LOOKUP_ESTABLISHED:
			sk = __inet6_lookup_established(net, &tcp_hashinfo,
							saddr, sport, daddr, ntohs(dport),
							in->अगरindex, 0);
			अवरोध;
		शेष:
			BUG();
		पूर्ण
		अवरोध;
		पूर्ण
	हाल IPPROTO_UDP:
		sk = udp6_lib_lookup(net, saddr, sport, daddr, dport,
				     in->अगरindex);
		अगर (sk) अणु
			पूर्णांक connected = (sk->sk_state == TCP_ESTABLISHED);
			पूर्णांक wildcard = ipv6_addr_any(&sk->sk_v6_rcv_saddr);

			/* NOTE: we वापस listeners even अगर bound to
			 * 0.0.0.0, those are filtered out in
			 * xt_socket, since xt_TPROXY needs 0 bound
			 * listeners too
			 */
			अगर ((lookup_type == NF_TPROXY_LOOKUP_ESTABLISHED && (!connected || wildcard)) ||
			    (lookup_type == NF_TPROXY_LOOKUP_LISTENER && connected)) अणु
				sock_put(sk);
				sk = शून्य;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		WARN_ON(1);
		sk = शून्य;
	पूर्ण

	pr_debug("tproxy socket lookup: proto %u %pI6:%u -> %pI6:%u, lookup type: %d, sock %p\n",
		 protocol, saddr, ntohs(sport), daddr, ntohs(dport), lookup_type, sk);

	वापस sk;
पूर्ण
EXPORT_SYMBOL_GPL(nf_tproxy_get_sock_v6);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Balazs Scheidler, Krisztian Kovacs");
MODULE_DESCRIPTION("Netfilter IPv6 transparent proxy support");
