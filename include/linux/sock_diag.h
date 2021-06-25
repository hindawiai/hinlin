<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SOCK_DIAG_H__
#घोषणा __SOCK_DIAG_H__

#समावेश <linux/netlink.h>
#समावेश <linux/user_namespace.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <uapi/linux/sock_diag.h>

काष्ठा sk_buff;
काष्ठा nlmsghdr;
काष्ठा sock;

काष्ठा sock_diag_handler अणु
	__u8 family;
	पूर्णांक (*dump)(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh);
	पूर्णांक (*get_info)(काष्ठा sk_buff *skb, काष्ठा sock *sk);
	पूर्णांक (*destroy)(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh);
पूर्ण;

पूर्णांक sock_diag_रेजिस्टर(स्थिर काष्ठा sock_diag_handler *h);
व्योम sock_diag_unरेजिस्टर(स्थिर काष्ठा sock_diag_handler *h);

व्योम sock_diag_रेजिस्टर_inet_compat(पूर्णांक (*fn)(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh));
व्योम sock_diag_unरेजिस्टर_inet_compat(पूर्णांक (*fn)(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh));

u64 __sock_gen_cookie(काष्ठा sock *sk);

अटल अंतरभूत u64 sock_gen_cookie(काष्ठा sock *sk)
अणु
	u64 cookie;

	preempt_disable();
	cookie = __sock_gen_cookie(sk);
	preempt_enable();

	वापस cookie;
पूर्ण

पूर्णांक sock_diag_check_cookie(काष्ठा sock *sk, स्थिर __u32 *cookie);
व्योम sock_diag_save_cookie(काष्ठा sock *sk, __u32 *cookie);

पूर्णांक sock_diag_put_meminfo(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक attr);
पूर्णांक sock_diag_put_filterinfo(bool may_report_filterinfo, काष्ठा sock *sk,
			     काष्ठा sk_buff *skb, पूर्णांक attrtype);

अटल अंतरभूत
क्रमागत sknetlink_groups sock_diag_destroy_group(स्थिर काष्ठा sock *sk)
अणु
	चयन (sk->sk_family) अणु
	हाल AF_INET:
		अगर (sk->sk_type == SOCK_RAW)
			वापस SKNLGRP_NONE;

		चयन (sk->sk_protocol) अणु
		हाल IPPROTO_TCP:
			वापस SKNLGRP_INET_TCP_DESTROY;
		हाल IPPROTO_UDP:
			वापस SKNLGRP_INET_UDP_DESTROY;
		शेष:
			वापस SKNLGRP_NONE;
		पूर्ण
	हाल AF_INET6:
		अगर (sk->sk_type == SOCK_RAW)
			वापस SKNLGRP_NONE;

		चयन (sk->sk_protocol) अणु
		हाल IPPROTO_TCP:
			वापस SKNLGRP_INET6_TCP_DESTROY;
		हाल IPPROTO_UDP:
			वापस SKNLGRP_INET6_UDP_DESTROY;
		शेष:
			वापस SKNLGRP_NONE;
		पूर्ण
	शेष:
		वापस SKNLGRP_NONE;
	पूर्ण
पूर्ण

अटल अंतरभूत
bool sock_diag_has_destroy_listeners(स्थिर काष्ठा sock *sk)
अणु
	स्थिर काष्ठा net *n = sock_net(sk);
	स्थिर क्रमागत sknetlink_groups group = sock_diag_destroy_group(sk);

	वापस group != SKNLGRP_NONE && n->diag_nlsk &&
		netlink_has_listeners(n->diag_nlsk, group);
पूर्ण
व्योम sock_diag_broadcast_destroy(काष्ठा sock *sk);

पूर्णांक sock_diag_destroy(काष्ठा sock *sk, पूर्णांक err);
#पूर्ण_अगर
