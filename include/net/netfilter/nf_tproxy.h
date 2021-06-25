<शैली गुरु>
#अगर_अघोषित _NF_TPROXY_H_
#घोषणा _NF_TPROXY_H_

#समावेश <net/tcp.h>

क्रमागत nf_tproxy_lookup_t अणु
	 NF_TPROXY_LOOKUP_LISTENER,
	 NF_TPROXY_LOOKUP_ESTABLISHED,
पूर्ण;

अटल अंतरभूत bool nf_tproxy_sk_is_transparent(काष्ठा sock *sk)
अणु
	अगर (inet_sk_transparent(sk))
		वापस true;

	sock_gen_put(sk);
	वापस false;
पूर्ण

/* assign a socket to the skb -- consumes sk */
अटल अंतरभूत व्योम nf_tproxy_assign_sock(काष्ठा sk_buff *skb, काष्ठा sock *sk)
अणु
	skb_orphan(skb);
	skb->sk = sk;
	skb->deकाष्ठाor = sock_edemux;
पूर्ण

__be32 nf_tproxy_laddr4(काष्ठा sk_buff *skb, __be32 user_laddr, __be32 daddr);

/**
 * nf_tproxy_handle_समय_रुको4 - handle IPv4 TCP TIME_WAIT reखोलो redirections
 * @skb:	The skb being processed.
 * @laddr:	IPv4 address to redirect to or zero.
 * @lport:	TCP port to redirect to or zero.
 * @sk:		The TIME_WAIT TCP socket found by the lookup.
 *
 * We have to handle SYN packets arriving to TIME_WAIT sockets
 * dअगरferently: instead of reखोलोing the connection we should rather
 * redirect the new connection to the proxy अगर there's a listener
 * socket present.
 *
 * nf_tproxy_handle_समय_रुको4() consumes the socket reference passed in.
 *
 * Returns the listener socket अगर there's one, the TIME_WAIT socket अगर
 * no such listener is found, or शून्य अगर the TCP header is incomplete.
 */
काष्ठा sock *
nf_tproxy_handle_समय_रुको4(काष्ठा net *net, काष्ठा sk_buff *skb,
			    __be32 laddr, __be16 lport, काष्ठा sock *sk);

/*
 * This is used when the user wants to पूर्णांकercept a connection matching
 * an explicit iptables rule. In this हाल the sockets are assumed
 * matching in preference order:
 *
 *   - match: अगर there's a fully established connection matching the
 *     _packet_ tuple, it is वापसed, assuming the redirection
 *     alपढ़ोy took place and we process a packet beदीर्घing to an
 *     established connection
 *
 *   - match: अगर there's a listening socket matching the redirection
 *     (e.g. on-port & on-ip of the connection), it is वापसed,
 *     regardless अगर it was bound to 0.0.0.0 or an explicit
 *     address. The reasoning is that अगर there's an explicit rule, it
 *     करोes not really matter अगर the listener is bound to an पूर्णांकerface
 *     or to 0. The user alपढ़ोy stated that he wants redirection
 *     (since he added the rule).
 *
 * Please note that there's an overlap between what a TPROXY target
 * and a socket match will match. Normally अगर you have both rules the
 * "socket" match will be the first one, effectively all packets
 * beदीर्घing to established connections going through that one.
 */
काष्ठा sock *
nf_tproxy_get_sock_v4(काष्ठा net *net, काष्ठा sk_buff *skb,
		      स्थिर u8 protocol,
		      स्थिर __be32 saddr, स्थिर __be32 daddr,
		      स्थिर __be16 sport, स्थिर __be16 dport,
		      स्थिर काष्ठा net_device *in,
		      स्थिर क्रमागत nf_tproxy_lookup_t lookup_type);

स्थिर काष्ठा in6_addr *
nf_tproxy_laddr6(काष्ठा sk_buff *skb, स्थिर काष्ठा in6_addr *user_laddr,
		 स्थिर काष्ठा in6_addr *daddr);

/**
 * nf_tproxy_handle_समय_रुको6 - handle IPv6 TCP TIME_WAIT reखोलो redirections
 * @skb:	The skb being processed.
 * @tproto:	Transport protocol.
 * @thoff:	Transport protocol header offset.
 * @net:	Network namespace.
 * @laddr:	IPv6 address to redirect to.
 * @lport:	TCP port to redirect to or zero.
 * @sk:		The TIME_WAIT TCP socket found by the lookup.
 *
 * We have to handle SYN packets arriving to TIME_WAIT sockets
 * dअगरferently: instead of reखोलोing the connection we should rather
 * redirect the new connection to the proxy अगर there's a listener
 * socket present.
 *
 * nf_tproxy_handle_समय_रुको6() consumes the socket reference passed in.
 *
 * Returns the listener socket अगर there's one, the TIME_WAIT socket अगर
 * no such listener is found, or शून्य अगर the TCP header is incomplete.
 */
काष्ठा sock *
nf_tproxy_handle_समय_रुको6(काष्ठा sk_buff *skb, पूर्णांक tproto, पूर्णांक thoff,
			    काष्ठा net *net,
			    स्थिर काष्ठा in6_addr *laddr,
			    स्थिर __be16 lport,
			    काष्ठा sock *sk);

काष्ठा sock *
nf_tproxy_get_sock_v6(काष्ठा net *net, काष्ठा sk_buff *skb, पूर्णांक thoff,
		      स्थिर u8 protocol,
		      स्थिर काष्ठा in6_addr *saddr, स्थिर काष्ठा in6_addr *daddr,
		      स्थिर __be16 sport, स्थिर __be16 dport,
		      स्थिर काष्ठा net_device *in,
		      स्थिर क्रमागत nf_tproxy_lookup_t lookup_type);

#पूर्ण_अगर /* _NF_TPROXY_H_ */
