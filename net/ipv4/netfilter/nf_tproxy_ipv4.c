<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007-2008 BalaBit IT Ltd.
 * Author: Krisztian Kovacs
 */

#समावेश <net/netfilter/nf_tproxy.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <net/inet_sock.h>
#समावेश <linux/ip.h>
#समावेश <net/checksum.h>
#समावेश <net/udp.h>
#समावेश <net/tcp.h>
#समावेश <linux/inetdevice.h>

काष्ठा sock *
nf_tproxy_handle_समय_रुको4(काष्ठा net *net, काष्ठा sk_buff *skb,
			 __be32 laddr, __be16 lport, काष्ठा sock *sk)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	काष्ठा tcphdr _hdr, *hp;

	hp = skb_header_poपूर्णांकer(skb, ip_hdrlen(skb), माप(_hdr), &_hdr);
	अगर (hp == शून्य) अणु
		inet_twsk_put(inet_twsk(sk));
		वापस शून्य;
	पूर्ण

	अगर (hp->syn && !hp->rst && !hp->ack && !hp->fin) अणु
		/* SYN to a TIME_WAIT socket, we'd rather redirect it
		 * to a listener socket अगर there's one */
		काष्ठा sock *sk2;

		sk2 = nf_tproxy_get_sock_v4(net, skb, iph->protocol,
					    iph->saddr, laddr ? laddr : iph->daddr,
					    hp->source, lport ? lport : hp->dest,
					    skb->dev, NF_TPROXY_LOOKUP_LISTENER);
		अगर (sk2) अणु
			inet_twsk_deschedule_put(inet_twsk(sk));
			sk = sk2;
		पूर्ण
	पूर्ण

	वापस sk;
पूर्ण
EXPORT_SYMBOL_GPL(nf_tproxy_handle_समय_रुको4);

__be32 nf_tproxy_laddr4(काष्ठा sk_buff *skb, __be32 user_laddr, __be32 daddr)
अणु
	स्थिर काष्ठा in_अगरaddr *अगरa;
	काष्ठा in_device *indev;
	__be32 laddr;

	अगर (user_laddr)
		वापस user_laddr;

	laddr = 0;
	indev = __in_dev_get_rcu(skb->dev);

	in_dev_क्रम_each_अगरa_rcu(अगरa, indev) अणु
		अगर (अगरa->अगरa_flags & IFA_F_SECONDARY)
			जारी;

		laddr = अगरa->अगरa_local;
		अवरोध;
	पूर्ण

	वापस laddr ? laddr : daddr;
पूर्ण
EXPORT_SYMBOL_GPL(nf_tproxy_laddr4);

काष्ठा sock *
nf_tproxy_get_sock_v4(काष्ठा net *net, काष्ठा sk_buff *skb,
		      स्थिर u8 protocol,
		      स्थिर __be32 saddr, स्थिर __be32 daddr,
		      स्थिर __be16 sport, स्थिर __be16 dport,
		      स्थिर काष्ठा net_device *in,
		      स्थिर क्रमागत nf_tproxy_lookup_t lookup_type)
अणु
	काष्ठा sock *sk;

	चयन (protocol) अणु
	हाल IPPROTO_TCP: अणु
		काष्ठा tcphdr _hdr, *hp;

		hp = skb_header_poपूर्णांकer(skb, ip_hdrlen(skb),
					माप(काष्ठा tcphdr), &_hdr);
		अगर (hp == शून्य)
			वापस शून्य;

		चयन (lookup_type) अणु
		हाल NF_TPROXY_LOOKUP_LISTENER:
			sk = inet_lookup_listener(net, &tcp_hashinfo, skb,
						    ip_hdrlen(skb) +
						      __tcp_hdrlen(hp),
						    saddr, sport,
						    daddr, dport,
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
			sk = inet_lookup_established(net, &tcp_hashinfo,
						    saddr, sport, daddr, dport,
						    in->अगरindex);
			अवरोध;
		शेष:
			BUG();
		पूर्ण
		अवरोध;
		पूर्ण
	हाल IPPROTO_UDP:
		sk = udp4_lib_lookup(net, saddr, sport, daddr, dport,
				     in->अगरindex);
		अगर (sk) अणु
			पूर्णांक connected = (sk->sk_state == TCP_ESTABLISHED);
			पूर्णांक wildcard = (inet_sk(sk)->inet_rcv_saddr == 0);

			/* NOTE: we वापस listeners even अगर bound to
			 * 0.0.0.0, those are filtered out in
			 * xt_socket, since xt_TPROXY needs 0 bound
			 * listeners too
			 */
			अगर ((lookup_type == NF_TPROXY_LOOKUP_ESTABLISHED &&
			      (!connected || wildcard)) ||
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

	pr_debug("tproxy socket lookup: proto %u %08x:%u -> %08x:%u, lookup type: %d, sock %p\n",
		 protocol, ntohl(saddr), ntohs(sport), ntohl(daddr), ntohs(dport), lookup_type, sk);

	वापस sk;
पूर्ण
EXPORT_SYMBOL_GPL(nf_tproxy_get_sock_v4);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Balazs Scheidler, Krisztian Kovacs");
MODULE_DESCRIPTION("Netfilter IPv4 transparent proxy support");
