<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the "ping" module.
 */
#अगर_अघोषित _PING_H
#घोषणा _PING_H

#समावेश <net/icmp.h>
#समावेश <net/netns/hash.h>

/* PING_HTABLE_SIZE must be घातer of 2 */
#घोषणा PING_HTABLE_SIZE 	64
#घोषणा PING_HTABLE_MASK 	(PING_HTABLE_SIZE-1)

#घोषणा ping_portaddr_क्रम_each_entry(__sk, node, list) \
	hlist_nulls_क्रम_each_entry(__sk, node, list, sk_nulls_node)

/*
 * gid_t is either uपूर्णांक or uलघु.  We want to pass it to
 * proc_करोपूर्णांकvec_minmax(), so it must not be larger than MAX_INT
 */
#घोषणा GID_T_MAX (((gid_t)~0U) >> 1)

/* Compatibility glue so we can support IPv6 when it's compiled as a module */
काष्ठा pingv6_ops अणु
	पूर्णांक (*ipv6_recv_error)(काष्ठा sock *sk, काष्ठा msghdr *msg, पूर्णांक len,
			       पूर्णांक *addr_len);
	व्योम (*ip6_datagram_recv_common_ctl)(काष्ठा sock *sk,
					     काष्ठा msghdr *msg,
					     काष्ठा sk_buff *skb);
	व्योम (*ip6_datagram_recv_specअगरic_ctl)(काष्ठा sock *sk,
					       काष्ठा msghdr *msg,
					       काष्ठा sk_buff *skb);
	पूर्णांक (*icmpv6_err_convert)(u8 type, u8 code, पूर्णांक *err);
	व्योम (*ipv6_icmp_error)(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक err,
				__be16 port, u32 info, u8 *payload);
	पूर्णांक (*ipv6_chk_addr)(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr,
			     स्थिर काष्ठा net_device *dev, पूर्णांक strict);
पूर्ण;

काष्ठा ping_iter_state अणु
	काष्ठा seq_net_निजी  p;
	पूर्णांक			bucket;
	sa_family_t		family;
पूर्ण;

बाह्य काष्ठा proto ping_prot;
#अगर IS_ENABLED(CONFIG_IPV6)
बाह्य काष्ठा pingv6_ops pingv6_ops;
#पूर्ण_अगर

काष्ठा pingfakehdr अणु
	काष्ठा icmphdr icmph;
	काष्ठा msghdr *msg;
	sa_family_t family;
	__wsum wcheck;
पूर्ण;

पूर्णांक  ping_get_port(काष्ठा sock *sk, अचिन्हित लघु ident);
पूर्णांक ping_hash(काष्ठा sock *sk);
व्योम ping_unhash(काष्ठा sock *sk);

पूर्णांक  ping_init_sock(काष्ठा sock *sk);
व्योम ping_बंद(काष्ठा sock *sk, दीर्घ समयout);
पूर्णांक  ping_bind(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len);
व्योम ping_err(काष्ठा sk_buff *skb, पूर्णांक offset, u32 info);
पूर्णांक  ping_getfrag(व्योम *from, अक्षर *to, पूर्णांक offset, पूर्णांक fraglen, पूर्णांक odd,
		  काष्ठा sk_buff *);

पूर्णांक  ping_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len, पूर्णांक noblock,
		  पूर्णांक flags, पूर्णांक *addr_len);
पूर्णांक  ping_common_sendmsg(पूर्णांक family, काष्ठा msghdr *msg, माप_प्रकार len,
			 व्योम *user_icmph, माप_प्रकार icmph_len);
पूर्णांक  ping_queue_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb);
bool ping_rcv(काष्ठा sk_buff *skb);

#अगर_घोषित CONFIG_PROC_FS
व्योम *ping_seq_start(काष्ठा seq_file *seq, loff_t *pos, sa_family_t family);
व्योम *ping_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos);
व्योम ping_seq_stop(काष्ठा seq_file *seq, व्योम *v);

पूर्णांक __init ping_proc_init(व्योम);
व्योम ping_proc_निकास(व्योम);
#पूर्ण_अगर

व्योम __init ping_init(व्योम);
पूर्णांक  __init pingv6_init(व्योम);
व्योम pingv6_निकास(व्योम);

#पूर्ण_अगर /* _PING_H */
