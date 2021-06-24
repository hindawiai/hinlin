<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_MROUTE6_H
#घोषणा __LINUX_MROUTE6_H


#समावेश <linux/pim.h>
#समावेश <linux/skbuff.h>	/* क्रम काष्ठा sk_buff_head */
#समावेश <net/net_namespace.h>
#समावेश <uapi/linux/mroute6.h>
#समावेश <linux/mroute_base.h>
#समावेश <linux/sockptr.h>
#समावेश <net/fib_rules.h>

#अगर_घोषित CONFIG_IPV6_MROUTE
अटल अंतरभूत पूर्णांक ip6_mroute_opt(पूर्णांक opt)
अणु
	वापस (opt >= MRT6_BASE) && (opt <= MRT6_MAX);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक ip6_mroute_opt(पूर्णांक opt)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

काष्ठा sock;

#अगर_घोषित CONFIG_IPV6_MROUTE
बाह्य पूर्णांक ip6_mroute_setsockopt(काष्ठा sock *, पूर्णांक, sockptr_t, अचिन्हित पूर्णांक);
बाह्य पूर्णांक ip6_mroute_माला_लोockopt(काष्ठा sock *, पूर्णांक, अक्षर __user *, पूर्णांक __user *);
बाह्य पूर्णांक ip6_mr_input(काष्ठा sk_buff *skb);
बाह्य पूर्णांक ip6mr_ioctl(काष्ठा sock *sk, पूर्णांक cmd, व्योम __user *arg);
बाह्य पूर्णांक ip6mr_compat_ioctl(काष्ठा sock *sk, अचिन्हित पूर्णांक cmd, व्योम __user *arg);
बाह्य पूर्णांक ip6_mr_init(व्योम);
बाह्य व्योम ip6_mr_cleanup(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक ip6_mroute_setsockopt(काष्ठा sock *sock, पूर्णांक optname,
		sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	वापस -ENOPROTOOPT;
पूर्ण

अटल अंतरभूत
पूर्णांक ip6_mroute_माला_लोockopt(काष्ठा sock *sock,
			  पूर्णांक optname, अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	वापस -ENOPROTOOPT;
पूर्ण

अटल अंतरभूत
पूर्णांक ip6mr_ioctl(काष्ठा sock *sk, पूर्णांक cmd, व्योम __user *arg)
अणु
	वापस -ENOIOCTLCMD;
पूर्ण

अटल अंतरभूत पूर्णांक ip6_mr_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ip6_mr_cleanup(व्योम)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_IPV6_MROUTE_MULTIPLE_TABLES
bool ip6mr_rule_शेष(स्थिर काष्ठा fib_rule *rule);
#अन्यथा
अटल अंतरभूत bool ip6mr_rule_शेष(स्थिर काष्ठा fib_rule *rule)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

#घोषणा VIFF_STATIC 0x8000

काष्ठा mfc6_cache_cmp_arg अणु
	काष्ठा in6_addr mf6c_mcastgrp;
	काष्ठा in6_addr mf6c_origin;
पूर्ण;

काष्ठा mfc6_cache अणु
	काष्ठा mr_mfc _c;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा in6_addr mf6c_mcastgrp;
			काष्ठा in6_addr mf6c_origin;
		पूर्ण;
		काष्ठा mfc6_cache_cmp_arg cmparg;
	पूर्ण;
पूर्ण;

#घोषणा MFC_ASSERT_THRESH (3*HZ)		/* Maximal freq. of निश्चितs */

काष्ठा rपंचांगsg;
बाह्य पूर्णांक ip6mr_get_route(काष्ठा net *net, काष्ठा sk_buff *skb,
			   काष्ठा rपंचांगsg *rपंचांग, u32 portid);

#अगर_घोषित CONFIG_IPV6_MROUTE
bool mroute6_is_socket(काष्ठा net *net, काष्ठा sk_buff *skb);
बाह्य पूर्णांक ip6mr_sk_करोne(काष्ठा sock *sk);
#अन्यथा
अटल अंतरभूत bool mroute6_is_socket(काष्ठा net *net, काष्ठा sk_buff *skb)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत पूर्णांक ip6mr_sk_करोne(काष्ठा sock *sk)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
