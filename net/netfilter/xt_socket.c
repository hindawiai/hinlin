<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Transparent proxy support क्रम Linux/iptables
 *
 * Copyright (C) 2007-2008 BalaBit IT Ltd.
 * Author: Krisztian Kovacs
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <net/tcp.h>
#समावेश <net/udp.h>
#समावेश <net/icmp.h>
#समावेश <net/sock.h>
#समावेश <net/inet_sock.h>
#समावेश <net/netfilter/ipv4/nf_defrag_ipv4.h>

#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <net/inet6_hashtables.h>
#समावेश <net/netfilter/ipv6/nf_defrag_ipv6.h>
#पूर्ण_अगर

#समावेश <net/netfilter/nf_socket.h>
#समावेश <linux/netfilter/xt_socket.h>

/* "socket" match based redirection (no specअगरic rule)
 * ===================================================
 *
 * There are connections with dynamic endpoपूर्णांकs (e.g. FTP data
 * connection) that the user is unable to add explicit rules
 * क्रम. These are taken care of by a generic "socket" rule. It is
 * assumed that the proxy application is trusted to खोलो such
 * connections without explicit iptables rule (except of course the
 * generic 'socket' rule). In this हाल the following sockets are
 * matched in preference order:
 *
 *   - match: अगर there's a fully established connection matching the
 *     _packet_ tuple
 *
 *   - match: अगर there's a non-zero bound listener (possibly with a
 *     non-local address) We करोn't accept zero-bound listeners, since
 *     then local services could पूर्णांकercept traffic going through the
 *     box.
 */
अटल bool
socket_match(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par,
	     स्थिर काष्ठा xt_socket_mtinfo1 *info)
अणु
	काष्ठा sk_buff *pskb = (काष्ठा sk_buff *)skb;
	काष्ठा sock *sk = skb->sk;

	अगर (sk && !net_eq(xt_net(par), sock_net(sk)))
		sk = शून्य;

	अगर (!sk)
		sk = nf_sk_lookup_slow_v4(xt_net(par), skb, xt_in(par));

	अगर (sk) अणु
		bool wildcard;
		bool transparent = true;

		/* Ignore sockets listening on INADDR_ANY,
		 * unless XT_SOCKET_NOWILDCARD is set
		 */
		wildcard = (!(info->flags & XT_SOCKET_NOWILDCARD) &&
			    sk_fullsock(sk) &&
			    inet_sk(sk)->inet_rcv_saddr == 0);

		/* Ignore non-transparent sockets,
		 * अगर XT_SOCKET_TRANSPARENT is used
		 */
		अगर (info->flags & XT_SOCKET_TRANSPARENT)
			transparent = inet_sk_transparent(sk);

		अगर (info->flags & XT_SOCKET_RESTORESKMARK && !wildcard &&
		    transparent && sk_fullsock(sk))
			pskb->mark = sk->sk_mark;

		अगर (sk != skb->sk)
			sock_gen_put(sk);

		अगर (wildcard || !transparent)
			sk = शून्य;
	पूर्ण

	वापस sk != शून्य;
पूर्ण

अटल bool
socket_mt4_v0(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	अटल काष्ठा xt_socket_mtinfo1 xt_info_v0 = अणु
		.flags = 0,
	पूर्ण;

	वापस socket_match(skb, par, &xt_info_v0);
पूर्ण

अटल bool
socket_mt4_v1_v2_v3(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	वापस socket_match(skb, par, par->matchinfo);
पूर्ण

#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
अटल bool
socket_mt6_v1_v2_v3(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_socket_mtinfo1 *info = (काष्ठा xt_socket_mtinfo1 *) par->matchinfo;
	काष्ठा sk_buff *pskb = (काष्ठा sk_buff *)skb;
	काष्ठा sock *sk = skb->sk;

	अगर (sk && !net_eq(xt_net(par), sock_net(sk)))
		sk = शून्य;

	अगर (!sk)
		sk = nf_sk_lookup_slow_v6(xt_net(par), skb, xt_in(par));

	अगर (sk) अणु
		bool wildcard;
		bool transparent = true;

		/* Ignore sockets listening on INADDR_ANY
		 * unless XT_SOCKET_NOWILDCARD is set
		 */
		wildcard = (!(info->flags & XT_SOCKET_NOWILDCARD) &&
			    sk_fullsock(sk) &&
			    ipv6_addr_any(&sk->sk_v6_rcv_saddr));

		/* Ignore non-transparent sockets,
		 * अगर XT_SOCKET_TRANSPARENT is used
		 */
		अगर (info->flags & XT_SOCKET_TRANSPARENT)
			transparent = inet_sk_transparent(sk);

		अगर (info->flags & XT_SOCKET_RESTORESKMARK && !wildcard &&
		    transparent && sk_fullsock(sk))
			pskb->mark = sk->sk_mark;

		अगर (sk != skb->sk)
			sock_gen_put(sk);

		अगर (wildcard || !transparent)
			sk = शून्य;
	पूर्ण

	वापस sk != शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक socket_mt_enable_defrag(काष्ठा net *net, पूर्णांक family)
अणु
	चयन (family) अणु
	हाल NFPROTO_IPV4:
		वापस nf_defrag_ipv4_enable(net);
#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
	हाल NFPROTO_IPV6:
		वापस nf_defrag_ipv6_enable(net);
#पूर्ण_अगर
	पूर्ण
	WARN_ONCE(1, "Unknown family %d\n", family);
	वापस 0;
पूर्ण

अटल पूर्णांक socket_mt_v1_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_socket_mtinfo1 *info = (काष्ठा xt_socket_mtinfo1 *) par->matchinfo;
	पूर्णांक err;

	err = socket_mt_enable_defrag(par->net, par->family);
	अगर (err)
		वापस err;

	अगर (info->flags & ~XT_SOCKET_FLAGS_V1) अणु
		pr_info_ratelimited("unknown flags 0x%x\n",
				    info->flags & ~XT_SOCKET_FLAGS_V1);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक socket_mt_v2_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_socket_mtinfo2 *info = (काष्ठा xt_socket_mtinfo2 *) par->matchinfo;
	पूर्णांक err;

	err = socket_mt_enable_defrag(par->net, par->family);
	अगर (err)
		वापस err;

	अगर (info->flags & ~XT_SOCKET_FLAGS_V2) अणु
		pr_info_ratelimited("unknown flags 0x%x\n",
				    info->flags & ~XT_SOCKET_FLAGS_V2);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक socket_mt_v3_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_socket_mtinfo3 *info =
				    (काष्ठा xt_socket_mtinfo3 *)par->matchinfo;
	पूर्णांक err;

	err = socket_mt_enable_defrag(par->net, par->family);
	अगर (err)
		वापस err;
	अगर (info->flags & ~XT_SOCKET_FLAGS_V3) अणु
		pr_info_ratelimited("unknown flags 0x%x\n",
				    info->flags & ~XT_SOCKET_FLAGS_V3);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम socket_mt_destroy(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	अगर (par->family == NFPROTO_IPV4)
		nf_defrag_ipv4_disable(par->net);
	अन्यथा अगर (par->family == NFPROTO_IPV6)
		nf_defrag_ipv4_disable(par->net);
पूर्ण

अटल काष्ठा xt_match socket_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "socket",
		.revision	= 0,
		.family		= NFPROTO_IPV4,
		.match		= socket_mt4_v0,
		.hooks		= (1 << NF_INET_PRE_ROUTING) |
				  (1 << NF_INET_LOCAL_IN),
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "socket",
		.revision	= 1,
		.family		= NFPROTO_IPV4,
		.match		= socket_mt4_v1_v2_v3,
		.destroy	= socket_mt_destroy,
		.checkentry	= socket_mt_v1_check,
		.matchsize	= माप(काष्ठा xt_socket_mtinfo1),
		.hooks		= (1 << NF_INET_PRE_ROUTING) |
				  (1 << NF_INET_LOCAL_IN),
		.me		= THIS_MODULE,
	पूर्ण,
#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
	अणु
		.name		= "socket",
		.revision	= 1,
		.family		= NFPROTO_IPV6,
		.match		= socket_mt6_v1_v2_v3,
		.checkentry	= socket_mt_v1_check,
		.matchsize	= माप(काष्ठा xt_socket_mtinfo1),
		.destroy	= socket_mt_destroy,
		.hooks		= (1 << NF_INET_PRE_ROUTING) |
				  (1 << NF_INET_LOCAL_IN),
		.me		= THIS_MODULE,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.name		= "socket",
		.revision	= 2,
		.family		= NFPROTO_IPV4,
		.match		= socket_mt4_v1_v2_v3,
		.checkentry	= socket_mt_v2_check,
		.destroy	= socket_mt_destroy,
		.matchsize	= माप(काष्ठा xt_socket_mtinfo1),
		.hooks		= (1 << NF_INET_PRE_ROUTING) |
				  (1 << NF_INET_LOCAL_IN),
		.me		= THIS_MODULE,
	पूर्ण,
#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
	अणु
		.name		= "socket",
		.revision	= 2,
		.family		= NFPROTO_IPV6,
		.match		= socket_mt6_v1_v2_v3,
		.checkentry	= socket_mt_v2_check,
		.destroy	= socket_mt_destroy,
		.matchsize	= माप(काष्ठा xt_socket_mtinfo1),
		.hooks		= (1 << NF_INET_PRE_ROUTING) |
				  (1 << NF_INET_LOCAL_IN),
		.me		= THIS_MODULE,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.name		= "socket",
		.revision	= 3,
		.family		= NFPROTO_IPV4,
		.match		= socket_mt4_v1_v2_v3,
		.checkentry	= socket_mt_v3_check,
		.destroy	= socket_mt_destroy,
		.matchsize	= माप(काष्ठा xt_socket_mtinfo1),
		.hooks		= (1 << NF_INET_PRE_ROUTING) |
				  (1 << NF_INET_LOCAL_IN),
		.me		= THIS_MODULE,
	पूर्ण,
#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
	अणु
		.name		= "socket",
		.revision	= 3,
		.family		= NFPROTO_IPV6,
		.match		= socket_mt6_v1_v2_v3,
		.checkentry	= socket_mt_v3_check,
		.destroy	= socket_mt_destroy,
		.matchsize	= माप(काष्ठा xt_socket_mtinfo1),
		.hooks		= (1 << NF_INET_PRE_ROUTING) |
				  (1 << NF_INET_LOCAL_IN),
		.me		= THIS_MODULE,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init socket_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_matches(socket_mt_reg, ARRAY_SIZE(socket_mt_reg));
पूर्ण

अटल व्योम __निकास socket_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(socket_mt_reg, ARRAY_SIZE(socket_mt_reg));
पूर्ण

module_init(socket_mt_init);
module_निकास(socket_mt_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Krisztian Kovacs, Balazs Scheidler");
MODULE_DESCRIPTION("x_tables socket match module");
MODULE_ALIAS("ipt_socket");
MODULE_ALIAS("ip6t_socket");
